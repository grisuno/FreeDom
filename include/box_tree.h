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
/* Stage 2: the out-of-flow solver's arrays are indexed BY BOX ID, so this bounds
 * the box count of a whole page, not the number of positioned elements on it. It
 * must therefore stay >= page_view's PV_MAX_BOXES, or a page with more boxes than
 * this makes position_doc bail wholesale and NOTHING out of flow is placed. At 256
 * that cliff was reached by ordinary news front pages. */
#define BT_MAX_POSITIONED 1024u

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
    size_t          grid_rows;   /* GRID: explicit row count from grid-template-rows, 0 = auto */
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
    /* grid-row: span N; 0 (default) = 1 row. */
    int             grid_row_span;
    /* EXPLICIT cell of this grid item (2026-08-14): what `grid-area: <name>`
     * resolved to against the parent's `grid-template-areas`. ONE-BASED, and 0
     * means auto-placement -- the same convention CSS itself uses for grid lines,
     * chosen so that ZERO-INIT means "auto". A -1 sentinel would have made every
     * caller that predates named placement pin its items to cell (0,0), which is
     * exactly the class of bug V-002 exists to prevent. See spec/grid_areas.md. */
    int             grid_row_start, grid_col_start;

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

/* Stage 2b: bt_resolve_positioning plus the STATIC position of each out-of-flow
 * box (static_x/static_y, indexed by box_index; either may be NULL). The static
 * position is where the box would have started in flow (CSS 2.2 §10.3.7/§10.6.4);
 * the GUI's layout pass records it when it skips the block. For an
 * ABSOLUTE/FIXED box:
 *   - left unset/auto  -> x = static_x[i] when provided (else the legacy
 *     containing-block edge). An explicit left wins; right with auto left still
 *     anchors right (R4).
 *   - top  unset/auto  -> y = static_y[i] same rule. An explicit top wins;
 *     bottom with auto top still anchors bottom (R8).
 * bt_resolve_positioning delegates with NULL arrays (legacy behaviour). */
bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,
                                    const double *box_x, const double *box_y,
                                    const double *box_w, const double *box_h,
                                    const double *static_x, const double *static_y,
                                    double viewport_w, double viewport_h,
                                    bt_positioned *out, size_t out_cap,
                                    size_t *out_count);

/* Stage 2b visibility gate: 1 when the box at `bid` or any ancestor on the
 * parent_id chain has visibility HIDDEN/COLLAPSE (the same simplification the
 * in-flow path makes -- a visible re-entry under a hidden ancestor stays
 * hidden). The walk is bounded by nbox links and fails closed (returns 1,
 * hidden) on NULL boxes, an out-of-range bid, a dangling parent link or a
 * parent cycle -- a hostile box tree can never make it loop or read out of
 * bounds. Pure; no allocation. */
int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid);

/* Stage 2d out-of-flow subtree classification (spec/box_engine.md). Both walk
 * the parent_id chain from `bid` (self first) looking for a box whose position
 * is ABSOLUTE or FIXED:
 *   - bt_oof_anchor returns the NEAREST such box: the box a block's content
 *     belongs to for out-of-flow measurement and painting (a nested absolute
 *     box owns its own content).
 *   - bt_oof_root returns the OUTERMOST such box: the box whose static
 *     position the flow records when it skips the subtree.
 * Both return -1 (in flow) when the chain has none, and FAIL OPEN to -1 on
 * NULL boxes, out-of-range/negative bid, a dangling link or a parent cycle --
 * a misclassified hostile chain renders in flow (visible) rather than
 * vanishing. Pure; bounded by nbox links; no allocation. */
int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid);
int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid);

#endif /* FREEDOM_BOX_TREE_H */
