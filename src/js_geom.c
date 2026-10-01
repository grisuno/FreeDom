/*
 * js_geom — implementation: pure geometry table for a trusted page's JS.
 * See spec/js_geom.md.
 */

#include "js_geom.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

/* Open-addressing slots of the aggregation index: a power of two >= 2x the
 * rect bound, so the load factor never passes 1/2. */
#define JG_INDEX_SLOTS (2u * JG_MAX_RECTS)
#define JG_SLOT_EMPTY  UINT32_MAX

void jg_init(jg_table *t) {
    if (t != NULL) memset(t, 0, sizeof *t);
}

void jg_free(jg_table *t) {
    if (t == NULL) return;
    free(t->r);
    memset(t, 0, sizeof *t);
}

static int32_t clamp_coord(double v, double lo) {
    if (v < lo) v = lo;
    if (v > (double)JG_COORD_MAX) v = (double)JG_COORD_MAX;
    return (int32_t)lround(v);
}

static int grow(jg_table *t) {
    if (t->n < t->cap) return 0;
    if (t->cap >= JG_MAX_RECTS) return -1;
    size_t ncap = (t->cap == 0) ? 64u : t->cap * 2u;
    if (ncap > JG_MAX_RECTS) ncap = JG_MAX_RECTS;
    jg_rect *nr = (jg_rect *)realloc(t->r, ncap * sizeof *nr);
    if (nr == NULL) return -1;
    t->r = nr;
    t->cap = ncap;
    return 0;
}

static int push(jg_table *t, dom_node_id node, int32_t x, int32_t y, int32_t w, int32_t h) {
    if (grow(t) != 0) return -1;
    jg_rect *r = &t->r[t->n++];
    r->node = node; r->x = x; r->y = y; r->w = w; r->h = h;
    return 0;
}

int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h) {
    if (t == NULL) return -1;
    if (node == DOM_NODE_NONE) return 0;
    if (!isfinite(x) || !isfinite(y) || !isfinite(w) || !isfinite(h)) return 0;
    return push(t, node,
                clamp_coord(x, -(double)JG_COORD_MAX), clamp_coord(y, -(double)JG_COORD_MAX),
                clamp_coord(w, 0.0), clamp_coord(h, 0.0));
}

/* Bounding box of a and b into a; returns 1 if a changed. 64-bit so the sum of
 * two clamped values never overflows; the result is re-clamped. */
static int unite(jg_rect *a, const jg_rect *b) {
    int64_t x0 = a->x < b->x ? a->x : b->x;
    int64_t y0 = a->y < b->y ? a->y : b->y;
    int64_t ax1 = (int64_t)a->x + a->w, bx1 = (int64_t)b->x + b->w;
    int64_t ay1 = (int64_t)a->y + a->h, by1 = (int64_t)b->y + b->h;
    int64_t x1 = ax1 > bx1 ? ax1 : bx1;
    int64_t y1 = ay1 > by1 ? ay1 : by1;
    int64_t w = x1 - x0, h = y1 - y0;
    if (w > JG_COORD_MAX) w = JG_COORD_MAX;
    if (h > JG_COORD_MAX) h = JG_COORD_MAX;
    int changed = (x0 != a->x || y0 != a->y || w != a->w || h != a->h);
    a->x = (int32_t)x0; a->y = (int32_t)y0; a->w = (int32_t)w; a->h = (int32_t)h;
    return changed;
}

static int cmp_node(const void *pa, const void *pb) {
    const jg_rect *a = (const jg_rect *)pa, *b = (const jg_rect *)pb;
    return (a->node > b->node) - (a->node < b->node);
}

int jg_finish(jg_table *t) {
    if (t == NULL) return -1;
    if (t->n < 2) return 0;
    qsort(t->r, t->n, sizeof *t->r, cmp_node);
    size_t w = 0;
    for (size_t i = 1; i < t->n; ++i) {
        if (t->r[i].node == t->r[w].node) (void)unite(&t->r[w], &t->r[i]);
        else t->r[++w] = t->r[i];
    }
    t->n = w + 1;
    return 0;
}

const jg_rect *jg_find(const jg_table *t, dom_node_id node) {
    if (t == NULL || t->n == 0) return NULL;
    jg_rect key = { .node = node };
    return (const jg_rect *)bsearch(&key, t->r, t->n, sizeof *t->r, cmp_node);
}

static uint32_t slot_of(dom_node_id n) {
    uint32_t h = (uint32_t)n * 2654435761u;
    return h & (JG_INDEX_SLOTS - 1u);
}

/* Index of node in t->r via the local hash, inserting an empty-at-rect entry
 * (a copy of seed) when absent. Returns SIZE_MAX when the table is full. */
static size_t index_of(jg_table *t, uint32_t *slots, dom_node_id node, const jg_rect *seed,
                       int *inserted) {
    uint32_t s = slot_of(node);
    for (;;) {
        uint32_t v = slots[s];
        if (v == JG_SLOT_EMPTY) break;
        if (t->r[v].node == node) { *inserted = 0; return v; }
        s = (s + 1u) & (JG_INDEX_SLOTS - 1u);
    }
    if (push(t, node, seed->x, seed->y, seed->w, seed->h) != 0) return SIZE_MAX;
    slots[s] = (uint32_t)(t->n - 1);
    *inserted = 1;
    return t->n - 1;
}

int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx) {
    if (t == NULL || parent == NULL) return -1;
    if (jg_finish(t) != 0) return -1;
    uint32_t *slots = (uint32_t *)malloc(JG_INDEX_SLOTS * sizeof *slots);
    /* Walked = this node's ancestor chain already contains its rect. */
    unsigned char *walked = (unsigned char *)calloc(JG_MAX_RECTS, 1);
    if (slots == NULL || walked == NULL) { free(slots); free(walked); return -1; }
    memset(slots, 0xFF, JG_INDEX_SLOTS * sizeof *slots);
    for (size_t i = 0; i < t->n; ++i) {
        uint32_t s = slot_of(t->r[i].node);
        while (slots[s] != JG_SLOT_EMPTY) s = (s + 1u) & (JG_INDEX_SLOTS - 1u);
        slots[s] = (uint32_t)i;
    }

    int rc = 0;
    size_t n0 = t->n;
    for (size_t i = 0; i < n0 && rc == 0; ++i) {
        if (walked[i]) continue;
        walked[i] = 1;
        jg_rect cur = t->r[i];
        dom_node_id p = parent(ctx, cur.node);
        for (size_t d = 0; d < JG_MAX_DEPTH && p != DOM_NODE_NONE; ++d) {
            int ins = 0;
            size_t k = index_of(t, slots, p, &cur, &ins);
            if (k == SIZE_MAX) { rc = -1; break; }
            int changed = ins ? 1 : unite(&t->r[k], &cur);
            int was_walked = walked[k];
            walked[k] = 1;
            if (!changed && was_walked) break;   /* chain above already holds it */
            cur = t->r[k];
            p = parent(ctx, p);
        }
    }
    free(slots);
    free(walked);
    (void)jg_finish(t);
    return rc;
}

size_t jg_wire_len(const jg_table *t) {
    return (t == NULL) ? 0 : JG_HEADER_N + 1u + t->n * JG_RECT_N;
}

int jg_encode(const jg_table *t, int32_t *out, size_t cap) {
    if (t == NULL || out == NULL || cap < jg_wire_len(t)) return -1;
    size_t k = 0;
    out[k++] = t->scroll_x; out[k++] = t->scroll_y;
    out[k++] = t->view_w;   out[k++] = t->view_h;
    out[k++] = t->doc_w;    out[k++] = t->doc_h;
    out[k++] = (int32_t)t->n;
    for (size_t i = 0; i < t->n; ++i) {
        out[k++] = (int32_t)t->r[i].node;
        out[k++] = t->r[i].x; out[k++] = t->r[i].y;
        out[k++] = t->r[i].w; out[k++] = t->r[i].h;
    }
    return 0;
}

static int in_range(int32_t v, int32_t lo) {
    return v >= lo && v <= JG_COORD_MAX;
}

int jg_decode(const int32_t *in, size_t n, jg_table *out) {
    if (out == NULL) return -1;
    jg_free(out);
    if (in == NULL || n < JG_HEADER_N + 1u) return -1;
    for (size_t i = 0; i < JG_HEADER_N; ++i)
        if (!in_range(in[i], 0)) return -1;
    int32_t cnt = in[JG_HEADER_N];
    if (cnt < 0 || (uint32_t)cnt > JG_MAX_RECTS) return -1;
    if (n != JG_HEADER_N + 1u + (size_t)cnt * JG_RECT_N) return -1;
    const int32_t *p = in + JG_HEADER_N + 1u;
    for (int32_t i = 0; i < cnt; ++i, p += JG_RECT_N) {
        dom_node_id node = (dom_node_id)(uint32_t)p[0];
        if (node == DOM_NODE_NONE
            || !in_range(p[1], -JG_COORD_MAX) || !in_range(p[2], -JG_COORD_MAX)
            || !in_range(p[3], 0) || !in_range(p[4], 0)
            || push(out, node, p[1], p[2], p[3], p[4]) != 0) {
            jg_free(out);
            return -1;
        }
    }
    out->scroll_x = in[0]; out->scroll_y = in[1];
    out->view_w = in[2];   out->view_h = in[3];
    out->doc_w = in[4];    out->doc_h = in[5];
    return jg_finish(out);
}

static uint64_t fnv(uint64_t h, int32_t v) {
    uint32_t u = (uint32_t)v;
    for (int i = 0; i < 4; ++i) {
        h ^= (u >> (8 * i)) & 0xFFu;
        h *= 1099511628211ull;
    }
    return h;
}

uint64_t jg_hash(const jg_table *t) {
    uint64_t h = 1469598103934665603ull;
    if (t == NULL) return h;
    h = fnv(h, t->scroll_x); h = fnv(h, t->scroll_y);
    h = fnv(h, t->view_w);   h = fnv(h, t->view_h);
    h = fnv(h, t->doc_w);    h = fnv(h, t->doc_h);
    h = fnv(h, (int32_t)t->n);
    for (size_t i = 0; i < t->n; ++i) {
        h = fnv(h, (int32_t)t->r[i].node);
        h = fnv(h, t->r[i].x); h = fnv(h, t->r[i].y);
        h = fnv(h, t->r[i].w); h = fnv(h, t->r[i].h);
    }
    return h;
}
