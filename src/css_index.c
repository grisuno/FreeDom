/* css_index -- see include/css_index.h and spec/css_index.md. */
#include "css_index.h"

#include <stdlib.h>
#include <string.h>

enum { KEY_ID = 1, KEY_CLASS = 2, KEY_TAG = 3 };

/* FNV-1a over the kind byte then the name; the tag is hashed lowercased because
 * compound_matches compares it with csel_ci_eq. */
static uint64_t key_of(int kind, const char *s, size_t n, int lower) {
    uint64_t h = 1469598103934665603ull;
    h ^= (uint64_t)(unsigned char)kind;
    h *= 1099511628211ull;
    for (size_t i = 0; i < n; ++i) {
        unsigned char c = (unsigned char)s[i];
        if (lower) c = (unsigned char)csel_lower_ch((char)c);
        h ^= c;
        h *= 1099511628211ull;
    }
    return h;
}

/* An element token in the canonical form csel_ident_eq compares against: as-is
 * when it fits CSS_TOK_MAX, folded otherwise. */
static uint64_t key_of_token(int kind, const char *tok) {
    size_t n = strlen(tok);
    if (n < CSS_TOK_MAX) return key_of(kind, tok, n, 0);
    char f[CSS_TOK_MAX];
    csel_ident_fold(tok, n, f);
    return key_of(kind, f, strlen(f), 0);
}

static int entry_cmp(const void *a, const void *b) {
    const cix_entry *x = a, *y = b;
    if (x->key != y->key) return x->key < y->key ? -1 : 1;
    return (x->sel > y->sel) - (x->sel < y->sel);
}

void cix_free(cix_index *idx) {
    if (idx == NULL) return;
    free(idx->keyed);
    free(idx->universal);
    memset(idx, 0, sizeof *idx);
}

static void build(const css_sel *arr, css_sel *const *ptrs, size_t n, cix_index *idx) {
    const void *sels = ptrs != NULL ? (const void *)ptrs : (const void *)arr;
    if (idx == NULL) return;
    memset(idx, 0, sizeof *idx);
    if (sels == NULL || n == 0 || n > UINT32_MAX) {
        idx->valid = (sels != NULL || n == 0) && n <= UINT32_MAX;
        idx->nsels = idx->valid ? n : 0;
        return;
    }
    cix_entry *keyed = calloc(n, sizeof *keyed);
    uint32_t *uni = calloc(n, sizeof *uni);
    if (keyed == NULL || uni == NULL) { free(keyed); free(uni); return; }
    size_t nk = 0, nu = 0;
    for (size_t i = 0; i < n; ++i) {
        const css_sel *s = ptrs != NULL ? ptrs[i] : &arr[i];
        if (s->nparts <= 0 || s->nparts > CSS_MAX_COMPOUNDS) { uni[nu++] = (uint32_t)i; continue; }
        const css_compound *c = &s->parts[s->nparts - 1];
        uint64_t k;
        if (c->has_id)
            k = key_of(KEY_ID, c->id, strlen(c->id), 0);
        else if (c->ncls > 0)
            k = key_of(KEY_CLASS, c->cls[0], strlen(c->cls[0]), 0);
        else if (c->has_tag)
            k = key_of(KEY_TAG, c->tag, strlen(c->tag), 1);
        else { uni[nu++] = (uint32_t)i; continue; }
        keyed[nk].key = k;
        keyed[nk].sel = (uint32_t)i;
        ++nk;
    }
    qsort(keyed, nk, sizeof *keyed, entry_cmp);
    idx->keyed = keyed;
    idx->nkeyed = nk;
    idx->universal = uni;
    idx->nuniversal = nu;
    idx->nsels = n;
    idx->valid = 1;
}

/* First entry with key >= k. */
static size_t lower_bound(const cix_index *idx, uint64_t k) {
    size_t lo = 0, hi = idx->nkeyed;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        if (idx->keyed[mid].key < k) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

/* One sorted run of selector ordinals: the universal list, or the bucket of one key (entries
 * with equal keys are stored in ascending selector order, see entry_cmp). */
typedef struct {
    const uint32_t  *u;
    const cix_entry *e;
    size_t           i, n;
} cix_run;

static uint32_t run_head(const cix_run *r) { return r->u != NULL ? r->u[r->i] : r->e[r->i].sel; }

static void add_bucket(const cix_index *idx, uint64_t k, cix_run *runs, size_t *nr) {
    size_t lo = lower_bound(idx, k), hi = lo;
    while (hi < idx->nkeyed && idx->keyed[hi].key == k) ++hi;
    if (hi == lo) return;
    runs[*nr] = (cix_run){ NULL, idx->keyed + lo, 0, hi - lo };
    ++*nr;
}

static int push(uint32_t **buf, size_t *cap, size_t *n, uint32_t v) {
    if (*n == *cap) {
        size_t nc = *cap ? *cap * 2 : 64;
        if (nc < *cap || nc > SIZE_MAX / sizeof **buf) return 0;
        uint32_t *g = realloc(*buf, nc * sizeof **buf);
        if (g == NULL) return 0;
        *buf = g;
        *cap = nc;
    }
    (*buf)[(*n)++] = v;
    return 1;
}

/* Candidates in ascending selector order without duplicates: a k-way merge of the (already
 * sorted) universal list and the id, tag and class buckets, so no sort is needed. */
size_t cix_candidates(const cix_index *idx, const css_element *el,
                      uint32_t **buf, size_t *cap) {
    if (idx == NULL || !idx->valid || el == NULL || buf == NULL || cap == NULL)
        return (size_t)-1;
    if (el->nclasses > SIZE_MAX / sizeof(cix_run) - 3) return (size_t)-1;
    cix_run *runs = calloc(el->nclasses + 3, sizeof *runs);
    if (runs == NULL) return (size_t)-1;
    size_t nr = 0;
    if (idx->nuniversal > 0) runs[nr++] = (cix_run){ idx->universal, NULL, 0, idx->nuniversal };
    if (el->id != NULL) add_bucket(idx, key_of_token(KEY_ID, el->id), runs, &nr);
    if (el->tag != NULL) add_bucket(idx, key_of(KEY_TAG, el->tag, strlen(el->tag), 1), runs, &nr);
    for (size_t j = 0; j < el->nclasses; ++j) {
        if (el->classes == NULL || el->classes[j] == NULL) continue;
        add_bucket(idx, key_of_token(KEY_CLASS, el->classes[j]), runs, &nr);
    }
    size_t n = 0;
    int have_last = 0;
    uint32_t last = 0;
    for (;;) {
        size_t best = nr;
        uint32_t bv = 0;
        for (size_t r = 0; r < nr; ++r) {
            if (runs[r].i >= runs[r].n) continue;
            uint32_t v = run_head(&runs[r]);
            if (best == nr || v < bv) { best = r; bv = v; }
        }
        if (best == nr) break;
        ++runs[best].i;
        if (have_last && bv == last) continue;
        if (!push(buf, cap, &n, bv)) { free(runs); return (size_t)-1; }
        last = bv;
        have_last = 1;
    }
    free(runs);
    return n;
}

void cix_build(const css_sel *sels, size_t n, cix_index *idx) { build(sels, NULL, n, idx); }

void cix_build_ptrs(css_sel *const *sels, size_t n, cix_index *idx) { build(NULL, sels, n, idx); }
