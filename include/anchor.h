#ifndef FREEDOM_ANCHOR_H
#define FREEDOM_ANCHOR_H

#include <stddef.h>

#include "dom.h"
#include "js_geom.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * anchor — the indicated part of a document (HTML 7.4.6.4) and where it sits.
 *
 * Pure, I/O-free, no global state. The worker (which owns the DOM) resolves a URL
 * fragment to its target element and collects the handles whose painted geometry
 * locates it; the trusted window (which owns the layout) turns those handles into a
 * document offset through its own geometry table. The fragment is data: it is only
 * ever compared, never interpolated into a selector or a script. See spec/anchor.md.
 */

#define ANC_MAX_FRAGMENT 256u    /* bytes including the NUL (= LN_MAX_FRAGMENT) */
#define ANC_MAX_HANDLES  4096u   /* handles in one OP_ANCHOR reply (IPC bound) */

typedef enum anc_kind {
    ANC_NONE    = 0,   /* nothing indicated: the page does not move */
    ANC_TOP     = 1,   /* the top of the document ("" or "top") */
    ANC_ELEMENT = 2    /* an element (*out) */
} anc_kind;

/* Percent-decodes in into out (URL 1.3): each "%XY" with two hex digits becomes the
 * byte 0xXY, any other '%' is copied as is. Returns the decoded length (excluding
 * the NUL written after it), or (size_t)-1 when an argument is NULL, cap is 0 or the
 * result does not fit (out is then "" when cap > 0). */
size_t anc_percent_decode(const char *in, char *out, size_t cap);

/* The indicated part for fragment (without '#'), HTML 7.4.6.4: "" => ANC_TOP; else the
 * first connected element whose id is fragment, else the first connected <a> whose
 * name is fragment; then the same with the percent-decoded fragment; then ANC_TOP when
 * the decoded fragment is "top" (ASCII case-insensitive); else ANC_NONE. *out is set
 * only for ANC_ELEMENT. NULL arguments or a fragment of ANC_MAX_FRAGMENT bytes or more
 * => ANC_NONE. */
anc_kind anc_resolve(const dom_index *idx, const char *fragment, dom_node_id *out);

/* Writes target and its element subtree in preorder (*nsub handles), then the elements
 * that follow the subtree in tree order, up to cap handles in all (cap is clamped to
 * ANC_MAX_HANDLES). Returns the count written; 0 (and *nsub = 0) on NULL arguments,
 * cap 0 or an invalid target. */
size_t anc_collect(const dom_index *idx, dom_node_id target, dom_node_id *out, size_t cap,
                   size_t *nsub);

/* The document offset of the target from a FINISHED geometry table (jg_finish): the
 * smallest y among the rects of h[0, nsub); when none of them painted, the y of the
 * first of h[nsub, n) that did. 0 and *top on success; -1 (top untouched) when no
 * handle has a rect or an argument is NULL. */
int anc_target_top(const jg_table *g, const dom_node_id *h, size_t n, size_t nsub,
                   double *top);

/* As anc_target_top, plus the target's bottom: the largest y + h among the subtree's rects
 * (= *top when the position came from a following element: an empty target is a point).
 * 0 and both outputs; -1 (outputs untouched) when nothing painted or on NULL. */
int anc_target_box(const jg_table *g, const dom_node_id *h, size_t n, size_t nsub,
                   double *top, double *bottom);

/* The scroll offset that puts top at the top of the viewport, clamped to
 * [0, max_scroll]. Non-finite arguments or max_scroll < 0 => 0. */
double anc_scroll_for(double top, double max_scroll);

#endif /* FREEDOM_ANCHOR_H */
