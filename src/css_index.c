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

static int u32_cmp(const void *a, const void *b) {
    uint32_t x = *(const uint32_t *)a, y = *(const uint32_t *)b;
    return (x > y) - (x < y);
}

void cix_free(cix_index *idx) {
    if (idx == NULL) return;
    free(idx->keyed);
    free(idx->universal);
    memset(idx, 0, sizeof *idx);
}

void cix_build(const css_sel *sels, size_t n, cix_index *idx) {
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
        const css_sel *s = &sels[i];
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

static int push_bucket(const cix_index *idx, uint64_t k,
                       uint32_t **buf, size_t *cap, size_t *n) {
    for (size_t i = lower_bound(idx, k); i < idx->nkeyed && idx->keyed[i].key == k; ++i)
        if (!push(buf, cap, n, idx->keyed[i].sel)) return 0;
    return 1;
}

size_t cix_candidates(const cix_index *idx, const css_element *el,
                      uint32_t **buf, size_t *cap) {
    if (idx == NULL || !idx->valid || el == NULL || buf == NULL || cap == NULL)
        return (size_t)-1;
    size_t n = 0;
    for (size_t i = 0; i < idx->nuniversal; ++i)
        if (!push(buf, cap, &n, idx->universal[i])) return (size_t)-1;
    if (el->id != NULL && !push_bucket(idx, key_of_token(KEY_ID, el->id), buf, cap, &n))
        return (size_t)-1;
    if (el->tag != NULL &&
        !push_bucket(idx, key_of(KEY_TAG, el->tag, strlen(el->tag), 1), buf, cap, &n))
        return (size_t)-1;
    for (size_t j = 0; j < el->nclasses; ++j) {
        if (el->classes == NULL || el->classes[j] == NULL) continue;
        if (!push_bucket(idx, key_of_token(KEY_CLASS, el->classes[j]), buf, cap, &n))
            return (size_t)-1;
    }
    if (n > 1) {
        qsort(*buf, n, sizeof **buf, u32_cmp);
        size_t w = 1;
        for (size_t i = 1; i < n; ++i)
            if ((*buf)[i] != (*buf)[w - 1]) (*buf)[w++] = (*buf)[i];
        n = w;
    }
    return n;
}
