#ifndef FREEDOM_JS_GEOM_H
#define FREEDOM_JS_GEOM_H

#include <stddef.h>
#include <stdint.h>

#include "dom.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * js_geom — laid-out element geometry handed to a TRUSTED page's JavaScript.
 *
 * Pure, I/O-free, no global state. The trusted parent records one rectangle per
 * element from its final layout (document coordinates, CSS px), the table crosses
 * the IPC boundary as a flat int32 array (OP_GEOM), and the worker aggregates each
 * rect into every ancestor so an element without a box of its own still measures
 * the union of its descendants. Geometry is identity information: it is only ever
 * sent for an allow.conf AND js.conf host. See spec/js_geom.md.
 */

#define JG_MAX_RECTS  65536u      /* rects per table (memory / IPC bound) */
#define JG_MAX_DEPTH  4096u       /* ancestors walked per rect by jg_aggregate */
#define JG_COORD_MAX  (1 << 24)   /* |coordinate| and size bound, px */
#define JG_HEADER_N   6u          /* scroll_x, scroll_y, view_w, view_h, doc_w, doc_h */
#define JG_RECT_N     5u          /* node, x, y, w, h */

typedef struct jg_rect {
    dom_node_id node;
    int32_t     x, y, w, h;       /* document coordinates, px */
} jg_rect;

typedef struct jg_table {
    jg_rect *r;
    size_t   n, cap;
    int32_t  scroll_x, scroll_y;  /* document scroll offset */
    int32_t  view_w, view_h;      /* viewport size */
    int32_t  doc_w, doc_h;        /* document size */
} jg_table;

/* Empty table. */
void jg_init(jg_table *t);

/* Frees the rect array and resets to empty. Idempotent; NULL is a no-op. */
void jg_free(jg_table *t);

/* Appends one rect. DOM_NODE_NONE or a non-finite value is ignored (returns 0);
 * coordinates are clamped to +-JG_COORD_MAX and a negative size becomes 0.
 * Returns -1 on NULL or when JG_MAX_RECTS is reached (the table stays valid). */
int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h);

/* Sorts by node and merges rects of the same node into their bounding box.
 * Returns 0, or -1 on NULL. */
int jg_finish(jg_table *t);

/* The rect of node in a finished table, or NULL. */
const jg_rect *jg_find(const jg_table *t, dom_node_id node);

/* Unions every rect into each of its ancestors (parent(ctx, n) until DOM_NODE_NONE,
 * at most JG_MAX_DEPTH steps, so a cyclic parent function terminates), then
 * finishes the table. Returns 0, or -1 on NULL / exhaustion of JG_MAX_RECTS (the
 * table then holds every rect it could fit, finished). */
int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx);

/* Number of int32 values jg_encode writes: JG_HEADER_N + 1 + n * JG_RECT_N. */
size_t jg_wire_len(const jg_table *t);

/* Serializes into out (cap int32 values). Returns 0, or -1 on NULL / too small. */
int jg_encode(const jg_table *t, int32_t *out, size_t cap);

/* Parses a wire array into out (which must be jg_init'ed or empty; previous
 * contents are freed). Validates the header, the count against n and JG_MAX_RECTS
 * and every value's range; on any failure returns -1 and leaves out empty.
 * The result is finished. */
int jg_decode(const int32_t *in, size_t n, jg_table *out);

/* FNV-1a over the header and every rect: equal tables hash equal. */
uint64_t jg_hash(const jg_table *t);

#endif /* FREEDOM_JS_GEOM_H */
