/* sheet_cache -- see include/sheet_cache.h and spec/sheet_cache.md. */
#include "sheet_cache.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "css_select.h"
#include "freedom_config.h"

/* One question the parse asked the root matcher, and the answer it got. */
typedef struct shc_query {
    css_sel *sel;      /* csel_compact_dup: self-contained, owned */
    int      answer;   /* normalized to 0/1 */
} shc_query;

struct shc_sheet {
    css_sheet *css;
    unsigned   refs;
    /* Key copy; meaningful only while the cache retains this sheet. */
    char      *text;
    size_t     len;
    char      *root_scope;
    shc_query *queries;     /* every question the parse asked the root matcher */
    size_t     nqueries;
    int        has_media, has_matcher, has_scope;
    int        prefers_dark, print, width_px;
};

struct shc_cache {
    shc_sheet *entry;
    size_t     max_text;
    shc_stats  stats;
};

/* Records what the root matcher is asked and what it answers. The parse depends on the
 * live DOM through these answers and nothing else, so a later derivation may reuse the
 * sheet iff the matcher still answers every recorded question the same way. */
typedef struct shc_probe {
    int  (*match)(void *ctx, const struct css_sel *sel);
    void  *ctx;
    shc_query *q;
    size_t     n, cap;
    int        lost;   /* a question could not be recorded: the parse is not reusable */
} shc_probe;

static int shc_probe_match(void *ctx, const struct css_sel *sel) {
    shc_probe *p = (shc_probe *)ctx;
    int answer = p->match(p->ctx, sel) != 0;
    if (p->lost) return answer;
    if (p->n >= FC_SHC_MAX_QUERIES) { p->lost = 1; return answer; }
    if (p->n == p->cap) {
        size_t ncap = (p->cap != 0) ? p->cap * 2 : 64;
        shc_query *nq = (shc_query *)realloc(p->q, ncap * sizeof *nq);
        if (nq == NULL) { p->lost = 1; return answer; }
        p->q = nq;
        p->cap = ncap;
    }
    css_sel *copy = csel_compact_dup(sel);
    if (copy == NULL) { p->lost = 1; return answer; }
    p->q[p->n].sel = copy;
    p->q[p->n].answer = answer;
    ++p->n;
    return answer;
}

static void shc_queries_free(shc_query *q, size_t n) {
    for (size_t i = 0; i < n; ++i) free(q[i].sel);
    free(q);
}

static char *shc_dup(const char *src, size_t len) {
    if (len == (size_t)-1) return NULL;
    char *d = (char *)malloc(len + 1);
    if (d == NULL) return NULL;
    if (len != 0) memcpy(d, src, len);
    d[len] = '\0';
    return d;
}

static void shc_sheet_destroy(shc_sheet *s) {
    css_free(s->css);
    free(s->text);
    free(s->root_scope);
    shc_queries_free(s->queries, s->nqueries);
    free(s);
}

shc_cache *shc_new(size_t max_text_bytes) {
    shc_cache *c = (shc_cache *)calloc(1, sizeof *c);
    if (c == NULL) return NULL;
    c->max_text = (max_text_bytes != 0) ? max_text_bytes : FC_SHC_MAX_TEXT_BYTES;
    return c;
}

void shc_release(shc_sheet *s) {
    if (s == NULL || s->refs == 0) return;
    if (--s->refs == 0) shc_sheet_destroy(s);
}

void shc_free(shc_cache *c) {
    if (c == NULL) return;
    shc_release(c->entry);
    free(c);
}

const css_sheet *shc_css(const shc_sheet *s) {
    return (s != NULL) ? s->css : NULL;
}

void shc_stats_get(const shc_cache *c, shc_stats *out) {
    if (out == NULL) return;
    if (c == NULL) { memset(out, 0, sizeof *out); return; }
    *out = c->stats;
}

static int shc_key_matches(const shc_sheet *s, const shc_key *k) {
    const css_media *m = k->media;
    int has_matcher = (m != NULL && m->scope_match != NULL);
    if (s->len != k->len || s->has_media != (m != NULL)) return 0;
    if (m != NULL && (s->prefers_dark != m->prefers_dark || s->print != m->print
                      || s->width_px != m->width_px)) return 0;
    if (s->has_matcher != has_matcher) return 0;
    if (s->has_scope != (k->root_scope != NULL)) return 0;
    if (s->has_scope && strcmp(s->root_scope, k->root_scope) != 0) return 0;
    if (s->len != 0 && memcmp(s->text, k->text, s->len) != 0) return 0;
    /* Last, and only once everything static agrees: replay the matcher. */
    for (size_t i = 0; i < s->nqueries; ++i)
        if ((m->scope_match(m->scope_ctx, s->queries[i].sel) != 0) != s->queries[i].answer)
            return 0;
    return 1;
}

/* Copies the static key into *s. 0 on success; -1 on OOM (the handle keeps owning any
 * partial copy and frees it with the sheet). */
static int shc_key_store(shc_sheet *s, const shc_key *k) {
    const css_media *m = k->media;
    s->text = shc_dup(k->text, k->len);
    if (s->text == NULL) return -1;
    s->len = k->len;
    if (k->root_scope != NULL) {
        s->root_scope = shc_dup(k->root_scope, strlen(k->root_scope));
        if (s->root_scope == NULL) return -1;
        s->has_scope = 1;
    }
    if (m != NULL) {
        s->has_media = 1;
        s->prefers_dark = m->prefers_dark;
        s->print = m->print;
        s->width_px = m->width_px;
    }
    return 0;
}

shc_sheet *shc_acquire(shc_cache *cache, const shc_key *key) {
    if (key == NULL || key->len == (size_t)-1) return NULL;
    if (key->text == NULL && key->len != 0) return NULL;

    if (cache != NULL && cache->entry != NULL && shc_key_matches(cache->entry, key)) {
        ++cache->stats.hits;
        ++cache->entry->refs;
        return cache->entry;
    }

    shc_sheet *s = (shc_sheet *)calloc(1, sizeof *s);
    if (s == NULL) return NULL;
    s->refs = 1;

    shc_probe probe;
    memset(&probe, 0, sizeof probe);
    css_media media;
    const css_media *mp = key->media;
    if (mp != NULL && mp->scope_match != NULL) {
        media = *mp;
        probe.match = mp->scope_match;
        probe.ctx = mp->scope_ctx;
        /* Recording is only worth its copies when the result can be retained. */
        if (cache != NULL && key->len <= cache->max_text) {
            media.scope_match = shc_probe_match;
            media.scope_ctx = &probe;
            mp = &media;
        }
        s->has_matcher = 1;
    }
    (void)css_parse_scoped(key->text, key->len, mp, key->root_scope, &s->css);
    s->queries = probe.q;
    s->nqueries = probe.n;

    int reusable = cache != NULL && key->len <= cache->max_text && !probe.lost;
    if (reusable && shc_key_store(s, key) == 0) {
        shc_release(cache->entry);
        cache->entry = s;
        ++s->refs;
        ++cache->stats.misses;
    } else if (cache != NULL) {
        ++cache->stats.bypasses;
    }
    return s;
}
