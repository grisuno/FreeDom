#ifndef FREEDOM_BOX_TREE_H
#define FREEDOM_BOX_TREE_H

#include <stddef.h>

#include "box_style.h"
#include "flex_layout.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * box_tree — pure recursive block/flex/grid layout over a tree of boxes.
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
 * See spec/box_tree.md for the full contract.
 */

/* Anti-DoS caps: recursion depth and children per container. Exceeding either
 * fails closed (BT_ERR_RANGE) instead of overflowing the stack. */
#define BT_MAX_DEPTH    64u
#define BT_MAX_CHILDREN 128u

typedef struct bt_node {
    bx_display      display;     /* BLOCK / FLEX / GRID / NONE; others => block leaf */
    bx_edges        margin;      /* px; used by the parent when placing this node */
    bx_edges        padding;     /* px; inside this node */

    /* container parameters (FLEX / GRID): */
    double          gap;         /* px between children */
    fx_justify      justify;     /* FLEX main-axis distribution */
    size_t          grid_cols;   /* GRID: number of equal columns (>= 1) */

    /* this node as a flex item of its FLEX parent: */
    double          grow, shrink, basis, min_main;

    /* leaf content height in px (ignored for containers; computed): */
    double          content_h;

    struct bt_node *children;    /* array of children (caller-owned), or NULL */
    size_t          child_count;

    /* output: border-box rectangle relative to the PARENT's content-box origin (px).
     * w/h include padding, not margin; x/y are parent-relative. */
    double          x, y, w, h;
} bt_node;

typedef enum bt_status {
    BT_OK = 0,
    BT_ERR_NULL_ARG,  /* root was NULL */
    BT_ERR_RANGE      /* depth/children/columns over the cap, or negative flex/grid gap */
} bt_status;

/* Resolves the whole tree for an available width. root == NULL => BT_ERR_NULL_ARG;
 * avail_w < 0 is treated as 0. Sets root->x = root->y = 0 and fills x/y/w/h on every
 * node (x/y parent-relative, w/h border-box). display:none nodes get a zero rect and
 * take no space. The caller composes absolute coordinates by accumulating parent
 * origins. */
bt_status bt_layout(bt_node *root, double avail_w);

#endif /* FREEDOM_BOX_TREE_H */
