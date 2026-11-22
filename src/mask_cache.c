#include "mask_cache.h"

#include <stdint.h>
#include <stdlib.h>

/* One retained mask. tick orders recency (larger = more recent); buf NULL = free slot. */
typedef struct mkc_entry {
    mkc_key        key;
    unsigned char *buf;
    size_t         bytes;
    int            stride;
    uint64_t       tick;
} mkc_entry;

struct mkc_cache {
    mkc_entry *e;
    size_t     cap, bytes, budget;
    uint64_t   clock;
};

/* Exact, field by field; a NaN never equals itself, so a NaN key never hits. */
static int key_eq(const mkc_key *a, const mkc_key *b) {
    return a->w == b->w && a->h == b->h && a->sx == b->sx && a->sy == b->sy &&
           a->sw == b->sw && a->sh == b->sh && a->sr == b->sr && a->sigma == b->sigma &&
           a->inset == b->inset;
}

static void drop(mkc_cache *c, mkc_entry *e) {
    if (e->buf == NULL) return;
    free(e->buf);
    c->bytes -= e->bytes;
    e->buf = NULL;
    e->bytes = 0;
}

static mkc_entry *find(mkc_cache *c, const mkc_key *k) {
    for (size_t i = 0; i < c->cap; ++i)
        if (c->e[i].buf != NULL && key_eq(&c->e[i].key, k)) return &c->e[i];
    return NULL;
}

static mkc_entry *oldest(mkc_cache *c) {
    mkc_entry *o = NULL;
    for (size_t i = 0; i < c->cap; ++i)
        if (c->e[i].buf != NULL && (o == NULL || c->e[i].tick < o->tick)) o = &c->e[i];
    return o;
}

mkc_cache *mkc_new(size_t byte_budget, size_t max_entries) {
    if (byte_budget == 0 || max_entries == 0) return NULL;
    mkc_cache *c = (mkc_cache *)calloc(1, sizeof *c);
    if (c == NULL) return NULL;
    c->e = (mkc_entry *)calloc(max_entries, sizeof *c->e);
    if (c->e == NULL) { free(c); return NULL; }
    c->cap = max_entries;
    c->budget = byte_budget;
    return c;
}

void mkc_clear(mkc_cache *c) {
    if (c == NULL) return;
    for (size_t i = 0; i < c->cap; ++i) drop(c, &c->e[i]);
}

void mkc_free(mkc_cache *c) {
    if (c == NULL) return;
    mkc_clear(c);
    free(c->e);
    free(c);
}

const unsigned char *mkc_get(mkc_cache *c, const mkc_key *k, int *stride) {
    if (c == NULL || k == NULL || stride == NULL) return NULL;
    mkc_entry *e = find(c, k);
    if (e == NULL) return NULL;
    e->tick = ++c->clock;
    *stride = e->stride;
    return e->buf;
}

unsigned char *mkc_put(mkc_cache *c, const mkc_key *k, int stride) {
    if (c == NULL || k == NULL || k->w <= 0 || k->h <= 0 || stride < k->w) return NULL;
    if ((size_t)stride > SIZE_MAX / (size_t)k->h) return NULL;
    size_t bytes = (size_t)stride * (size_t)k->h;
    if (bytes > c->budget) return NULL;
    unsigned char *buf = (unsigned char *)calloc(bytes, 1);
    if (buf == NULL) return NULL;
    mkc_entry *slot = find(c, k);
    if (slot != NULL) drop(c, slot);
    while (c->bytes + bytes > c->budget) {
        mkc_entry *o = oldest(c);
        if (o == NULL) break;
        drop(c, o);
    }
    if (slot == NULL)
        for (size_t i = 0; i < c->cap && slot == NULL; ++i)
            if (c->e[i].buf == NULL) slot = &c->e[i];
    if (slot == NULL) {
        slot = oldest(c);
        drop(c, slot);
    }
    slot->key = *k;
    slot->buf = buf;
    slot->bytes = bytes;
    slot->stride = stride;
    slot->tick = ++c->clock;
    c->bytes += bytes;
    return buf;
}

size_t mkc_bytes(const mkc_cache *c) { return c != NULL ? c->bytes : 0; }

size_t mkc_count(const mkc_cache *c) {
    if (c == NULL) return 0;
    size_t n = 0;
    for (size_t i = 0; i < c->cap; ++i) n += (c->e[i].buf != NULL);
    return n;
}
