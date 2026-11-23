#ifndef FREEDOM_SCROLL_REQ_H
#define FREEDOM_SCROLL_REQ_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * scroll_req — a page script's request to scroll the window, and where it lands.
 *
 * Pure, I/O-free, no global state. The worker only RECORDS what the script asked
 * (window.scrollTo/scrollBy, Element.scrollIntoView, root scrollTop=); the trusted
 * parent validates the record (srq_decode, fail closed) and the window turns it into a
 * scroll offset against its own layout (srq_target), honoring the root's scroll-padding
 * and the target's scroll-margin. See spec/scroll_req.md.
 */

#define SRQ_MAX_COORD 10000000   /* |px| a record may carry; beyond is a desync */
#define SRQ_WIRE_N    8u         /* int32 fields of one record on the wire */

typedef enum srq_kind {
    SRQ_NONE    = 0,   /* no request */
    SRQ_TO      = 1,   /* absolute y */
    SRQ_BY      = 2,   /* y relative to the current scroll */
    SRQ_ELEMENT = 3    /* bring an element into view (handles travel after the record) */
} srq_kind;

typedef enum srq_behavior { SRQ_AUTO = 0, SRQ_INSTANT = 1, SRQ_SMOOTH = 2 } srq_behavior;

typedef enum srq_block {
    SRQ_START = 0, SRQ_CENTER = 1, SRQ_END = 2, SRQ_NEAREST = 3
} srq_block;

typedef struct srq_req {
    int    kind;           /* srq_kind */
    int    behavior;       /* srq_behavior */
    int    block;          /* srq_block (SRQ_ELEMENT only) */
    double y;              /* SRQ_TO: absolute; SRQ_BY: delta */
    double margin_top;     /* the target's computed scroll-margin-top/bottom, px */
    double margin_bottom;
    size_t n, nsub;        /* SRQ_ELEMENT: handles that follow (anc_collect shape) */
} srq_req;

typedef struct srq_view {
    double scroll;         /* current offset */
    double max_scroll;     /* largest valid offset (>= 0) */
    double view_h;         /* scrollport height (> 0) */
    double pad_top;        /* the root's scroll-padding-top/bottom, px */
    double pad_bottom;
} srq_view;

/* Writes r as SRQ_WIRE_N int32: kind, behavior, block, y, margin_top, margin_bottom, n, nsub.
 * Doubles are rounded and clamped to [-SRQ_MAX_COORD, SRQ_MAX_COORD] (NaN => 0); a NULL
 * argument writes nothing. */
void srq_encode(const srq_req *r, int32_t out[SRQ_WIRE_N]);

/* Reads a record written by srq_encode, validating EVERY field: enums in range, |coords|
 * <= SRQ_MAX_COORD, n <= max_handles, nsub <= n, handles only (and always) for
 * SRQ_ELEMENT. Returns 0 on success, -1 otherwise (*out is then SRQ_NONE when out is not
 * NULL). A record of kind SRQ_NONE with every other field 0 is valid. */
int srq_decode(const int32_t in[SRQ_WIRE_N], size_t max_handles, srq_req *out);

/* The scroll offset r asks for, in [0, v->max_scroll]. el_top/el_bottom are the target's
 * document box (SRQ_ELEMENT only; ignored otherwise). The optimal viewing region is the
 * viewport minus the root's scroll-padding (ignored when it would leave no room); the
 * target's box grows by its scroll-margin. Returns 0 and *out; -1 (*out untouched) on
 * NULL, SRQ_NONE, a non-finite input, view_h <= 0 or max_scroll < 0. */
int srq_target(const srq_req *r, const srq_view *v, double el_top, double el_bottom,
               double *out);

/* 1 when the scroll should animate: SRQ_SMOOTH, or SRQ_AUTO with the root's computed
 * scroll-behavior smooth (root_smooth != 0). 0 otherwise or on NULL. */
int srq_smooth(const srq_req *r, int root_smooth);

#endif /* FREEDOM_SCROLL_REQ_H */
