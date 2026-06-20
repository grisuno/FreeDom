/*
 * box_tree — implementation: pure recursive block/flex/grid layout.
 *
 * One recursive pass resolves the tree. Block containers stack children vertically
 * with adjacent-margin collapsing; flex and grid containers delegate the main-axis
 * distribution to flex_layout and then recurse into each child with its resolved
 * width. Leaves take their content height. No I/O, no global state, no dynamic
 * allocation: per-container scratch lives in fixed-size stack arrays bounded by
 * BT_MAX_CHILDREN, and the recursion budget BT_MAX_DEPTH keeps a hostile tree from
 * overflowing the stack.
 */

#include "box_tree.h"

#include <stddef.h>

static bt_status layout_node(bt_node *node, double avail_w, unsigned depth);

/* Block container: stack non-none children vertically, collapsing each child's top
 * margin with the previous child's bottom margin. */
static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,
                              double pl, double pt, double pb, double cw, unsigned depth) {
    double cursor = pt;
    double prev_bottom = 0.0;
    for (size_t i = 0; i < nk; ++i) {
        bt_node *c = kids[i];
        double cavail = cw - c->margin.left - c->margin.right;
        if (cavail < 0.0) cavail = 0.0;
        bt_status r = layout_node(c, cavail, depth + 1);
        if (r != BT_OK) return r;
        double top_gap = (prev_bottom > c->margin.top) ? prev_bottom : c->margin.top;
        c->y = cursor + top_gap;
        c->x = pl + c->margin.left;
        cursor = c->y + c->h;
        prev_bottom = c->margin.bottom;
    }
    node->h = cursor + prev_bottom + pb;
    return BT_OK;
}

/* Flex row: distribute the main axis with flex_layout, place children at the
 * padding origin (align-start), height = padding + tallest child. */
static bt_status layout_flex(bt_node *node, bt_node *const *kids, size_t nk,
                             double pl, double pt, double pb, double cw, unsigned depth) {
    if (node->gap < 0.0) return BT_ERR_RANGE;

    fx_item items[BT_MAX_CHILDREN];
    fx_result res[BT_MAX_CHILDREN];
    for (size_t i = 0; i < nk; ++i) {
        items[i].basis = kids[i]->basis;
        items[i].grow = kids[i]->grow;
        items[i].shrink = kids[i]->shrink;
        items[i].min = kids[i]->min_main;
    }
    if (fx_flex_line(items, nk, cw, node->gap, node->justify, res) != FX_OK)
        return BT_ERR_RANGE;

    double maxh = 0.0;
    for (size_t i = 0; i < nk; ++i) {
        bt_status r = layout_node(kids[i], res[i].size, depth + 1);
        if (r != BT_OK) return r;
        kids[i]->x = pl + res[i].pos;
        kids[i]->y = pt;
        if (kids[i]->h > maxh) maxh = kids[i]->h;
    }
    node->h = pt + maxh + pb;
    return BT_OK;
}

/* Grid: equal columns via flex_layout, row-major placement, per-row max height. */
static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,
                             double pl, double pt, double pb, double cw, unsigned depth) {
    size_t cols = node->grid_cols;
    if (cols == 0 || cols > BT_MAX_CHILDREN || node->gap < 0.0) return BT_ERR_RANGE;

    double col_x[BT_MAX_CHILDREN];
    double col_w[BT_MAX_CHILDREN];
    if (fx_grid_columns(cw, cols, node->gap, col_x, col_w) != FX_OK) return BT_ERR_RANGE;

    size_t nrows = (nk + cols - 1) / cols;
    double rowh[BT_MAX_CHILDREN];
    for (size_t r = 0; r < nrows; ++r) rowh[r] = 0.0;

    for (size_t i = 0; i < nk; ++i) {
        size_t rr, cc;
        fx_grid_cell(i, cols, &rr, &cc);
        bt_status r = layout_node(kids[i], col_w[cc], depth + 1);
        if (r != BT_OK) return r;
        if (kids[i]->h > rowh[rr]) rowh[rr] = kids[i]->h;
    }

    double rowy[BT_MAX_CHILDREN];
    double yy = pt;
    for (size_t r = 0; r < nrows; ++r) {
        rowy[r] = yy;
        yy += rowh[r] + node->gap;
    }
    for (size_t i = 0; i < nk; ++i) {
        size_t rr, cc;
        fx_grid_cell(i, cols, &rr, &cc);
        kids[i]->x = pl + col_x[cc];
        kids[i]->y = rowy[rr];
    }
    /* yy = pt + sum(rowh) + gap*nrows; drop the trailing gap, add bottom padding. */
    node->h = (nrows > 0) ? (yy - node->gap + pb) : (pt + pb);
    return BT_OK;
}

static bt_status layout_node(bt_node *node, double avail_w, unsigned depth) {
    if (depth > BT_MAX_DEPTH) return BT_ERR_RANGE;
    if (avail_w < 0.0) avail_w = 0.0;

    if (node->display == BX_DISPLAY_NONE) {
        node->w = 0.0;
        node->h = 0.0;
        return BT_OK;
    }

    node->w = avail_w;
    double pl = node->padding.left, pr = node->padding.right;
    double pt = node->padding.top, pb = node->padding.bottom;
    double cw = avail_w - pl - pr;
    if (cw < 0.0) cw = 0.0;

    /* Leaf: content height plus vertical padding. */
    if (node->child_count == 0 || node->children == NULL) {
        node->h = node->content_h + pt + pb;
        return BT_OK;
    }
    if (node->child_count > BT_MAX_CHILDREN) return BT_ERR_RANGE;

    /* Collect the rendered (non-none) children; none children get a zero rect. */
    bt_node *kids[BT_MAX_CHILDREN];
    size_t nk = 0;
    for (size_t i = 0; i < node->child_count; ++i) {
        bt_node *c = &node->children[i];
        if (c->display == BX_DISPLAY_NONE) {
            c->x = c->y = c->w = c->h = 0.0;
            continue;
        }
        kids[nk++] = c;
    }

    switch (node->display) {
        case BX_DISPLAY_FLEX:
            return layout_flex(node, kids, nk, pl, pt, pb, cw, depth);
        case BX_DISPLAY_GRID:
            return layout_grid(node, kids, nk, pl, pt, pb, cw, depth);
        default:
            return layout_block(node, kids, nk, pl, pt, pb, cw, depth);
    }
}

bt_status bt_layout(bt_node *root, double avail_w) {
    if (root == NULL) return BT_ERR_NULL_ARG;
    root->x = 0.0;
    root->y = 0.0;
    return layout_node(root, avail_w, 0);
}
