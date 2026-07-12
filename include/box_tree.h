#ifndef FREEDOM_BOX_TREE_H
#define FREEDOM_BOX_TREE_H

#include <stddef.h>

#include "box_style.h"
#include "flex_layout.h"
#include "page_view.h"   /* pv_box_def (box tree) */

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * box_tree — pure recursive block/flex/grid layout over a tree of boxes, plus
 * the Stage 2 positioning pass (position + z-index stacking).
 *
 * No I/O, no global state, no dynamic allocation (bounded fixed-size stack
 * scratch): given a nested tree of boxes (each carrying its display, margins and
 * padding in px, flex factors, and, for leaves, its content height) and an
 * available width, it computes every node's position and size. It measures no
 * text, paints nothing, touches no DOM.
 *
 * It closes the path box_style (what each box is) + flex_layout (how one container
 * distributes space) open: here the tree is nested and resolved as a whole. The
 * caller (the GUI orchestrator) builds the tree from the DOM, measuring text with
 * Cairo and converting box_style's em to px; bt_layout only resolves geometry.
 *
 * See spec/box_tree.md (layout) and spec/box_engine.md (box decoration + Stage 2
 * position/z-index) for the full contract.
 */

/* Anti-DoS caps: recursion depth and children per container. Exceeding either
 * fails closed (BT_ERR_RANGE) instead of overflowing the stack. */
#define BT_MAX_DEPTH      64u
#define BT_MAX_CHILDREN   128u
#define BT_MAX_POSITIONED 256u  /* Stage 2: out-of-flow boxes resolved per page */

/* Stage 2: position values for bt_node.position and pv_box_def.position. 0 covers
 * both unset and CSS_POS_STATIC (in-flow); the 1 gap is intentional, mirroring
 * css_position. */
#define BT_POS_STATIC    0
#define BT_POS_RELATIVE  2
#define BT_POS_ABSOLUTE  3
#define BT_POS_FIXED     4
#define BT_POS_STICKY    5

/* Cross-axis alignment of a node as a flex item of its FLEX parent (bt_node.align).
 * 0 (the zero-init default) is START, matching the layout's behaviour before this
 * field existed: every existing caller that never sets it keeps its exact geometry.
 * STRETCH is v1-approximated as START (the engine has no mechanism to force a leaf's
 * content to grow to fill the line -- see spec/box_engine.md). */
#define BT_ALIGN_START   0
#define BT_ALIGN_CENTER  1
#define BT_ALIGN_END     2
#define BT_ALIGN_STRETCH 3

typedef struct bt_node {
    bx_display      display;     /* BLOCK / FLEX / GRID / NONE; others => block leaf */
    bx_edges        margin;      /* px; used by the parent when placing this node */
    bx_edges        padding;     /* px; inside this node */

    /* container parameters (FLEX / GRID): */
    double          gap;         /* px between children (FLEX: main axis; GRID: columns) */
    fx_justify      justify;     /* FLEX main-axis distribution */
    size_t          grid_cols;   /* GRID: number of columns (>= 1) */
    const int      *grid_track;  /* GRID: per-track sizes (0 auto / >0 px / <0 fr x100);
                                  * NULL (zero-init default) = equal columns, unchanged */
    size_t          grid_ntrack; /* valid entries in grid_track (tracks past it are auto) */
    int             wrap;        /* FLEX: nonzero packs items onto multiple lines instead
                                  * of forcing them all onto one (flex-wrap); 0 (default)
                                  * is the original single-line behaviour, unchanged. */
    int             wrap_reverse;/* FLEX: when wrap is active, 1 reverses the cross-axis
                                  * order (lines stack from bottom to top instead of
                                  * top to bottom). 0 (default) is normal wrap. */
    double          row_gap;     /* cross-axis gap: between GRID rows, or between wrapped
                                  * FLEX lines. Only consulted when has_row_gap is set. */
    int             has_row_gap; /* 0 (zero-init default): `gap` serves both axes, exactly
                                  * as before this field existed. 1: use row_gap instead of
                                  * `gap` for the row/cross axis (author `row-gap`). */

    /* this node as a flex item of its FLEX parent: */
    double          grow, shrink, basis, min_main;
    int             align;       /* BT_ALIGN_*: this item's cross-axis alignment within
                                  * its line (already resolved from align-self / the
                                  * container's align-items by the caller). */
    /* this node as a grid item of its GRID parent (2026-07-11): columns it spans
     * (grid-column: span N); <= 0 (zero-init default) = 1 column. Clamped to the
     * columns remaining on its row (CSS auto-placement). */
    int             grid_span;

    /* leaf content height in px (ignored for containers; computed): */
    double          content_h;

    struct bt_node *children;    /* array of children (caller-owned), or NULL */
    size_t          child_count;

    /* output: border-box rectangle relative to the PARENT's content-box origin (px).
     * w/h include padding, not margin; x/y are parent-relative. */
    double          x, y, w, h;
} bt_node;

/* Stage 2: one positioned box in the final paint order. The GUI paints the
 * in-flow rc_layout.rows first, then the bt_positioned list in this order (on
 * top of in-flow content). Negative z_index entries are skipped by the GUI in
 * v1 (a two-pass painter would be needed to paint them behind in-flow). */
typedef struct bt_positioned {
    size_t  box_index;   /* index into the pv_box_def array (== block_id) */
    int     z_index;     /* signed, or 0 if CSS_LEN_UNSET */
    size_t  doc_order;   /* depth-first pre-order index, for stable tiebreak */
    double  x, y, w, h;  /* final content-box rect, viewport-relative (px) */
} bt_positioned;

typedef enum bt_status {
    BT_OK = 0,
    BT_ERR_NULL_ARG,  /* root was NULL, or required out pointer was NULL */
    BT_ERR_RANGE      /* depth/children/columns over the cap, or negative flex/grid gap,
                         or nbox > BT_MAX_POSITIONED */
} bt_status;

/* Resolves the whole tree for an available width. root == NULL => BT_ERR_NULL_ARG;
 * avail_w < 0 is treated as 0. Sets root->x = root->y = 0 and fills x/y/w/h on every
 * node (x/y parent-relative, w/h border-box). display:none nodes get a zero rect and
 * take no space. The caller composes absolute coordinates by accumulating parent
 * origins. */
bt_status bt_layout(bt_node *root, double avail_w);

/* Stage 2: resolves out-of-flow positioning for every box in pv_box_def. Walks
 * the box tree (parent_id chain) depth-first, assigns doc_order, then for each
 * box with position != BT_POS_STATIC computes its final content-box rect:
 *
 *   - BT_POS_RELATIVE / BT_POS_STICKY (sticky fail-closed to relative): keep
 *     the in-flow (box_x[i], box_y[i]) and offset by (inset_left, inset_top).
 *     Siblings are unaffected (the box's own content moves).
 *   - BT_POS_ABSOLUTE: walk parent_id to the nearest positioned ancestor; its
 *     (box_x[a], box_y[a], box_w[a], box_h[a]) is the containing block (or the
 *     viewport if none). Offset by (inset_left, inset_top).
 *   - BT_POS_FIXED: containing block is the viewport. Offset by (inset_left,
 *     inset_top).
 *
 * CSS_LEN_UNSET / CSS_LEN_AUTO on an inset → 0 offset on that axis (the box
 * anchors at the containing block's edge). Only top/left are honored in v1
 * (right/bottom are read but ignored; CSS_LEN_AUTO has no shrink-to-fit solver).
 *
 * The output is sorted by (z_index ASC, doc_order ASC). out_count is set to the
 * number of positioned boxes found (may exceed out_cap; truncation fills up to
 * out_cap entries). box_x/y/w/h may be NULL — boxes without an in-flow rect
 * then resolve to zero-size at the containing block's origin.
 *
 * Errors: BT_ERR_NULL_ARG if (boxes == NULL && nbox > 0) or out_count == NULL;
 * BT_ERR_RANGE if nbox > BT_MAX_POSITIONED (fails closed; the caller skips the
 * pass for that frame rather than painting garbage). */
bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,
                                 const double *box_x, const double *box_y,
                                 const double *box_w, const double *box_h,
                                 double viewport_w, double viewport_h,
                                 bt_positioned *out, size_t out_cap,
                                 size_t *out_count);

#endif /* FREEDOM_BOX_TREE_H */
