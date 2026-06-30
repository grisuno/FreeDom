/*
 * box_tree — implementation: pure recursive block/flex/grid layout, plus the
 * Stage 2 out-of-flow positioning pass.
 *
 * One recursive pass resolves the tree. Block containers stack children vertically
 * with adjacent-margin collapsing; flex and grid containers delegate the main-axis
 * distribution to flex_layout and then recurse into each child with its resolved
 * width. Leaves take their content height. No I/O, no global state, no dynamic
 * allocation: per-container scratch lives in fixed-size stack arrays bounded by
 * BT_MAX_CHILDREN, and the recursion budget BT_MAX_DEPTH keeps a hostile tree from
 * overflowing the stack.
 *
 * Stage 2 (bt_resolve_positioning) walks the pv_box_def box tree, assigns
 * depth-first doc_order, and resolves every box with position != STATIC into a
 * final content-box rect against its containing block. Output is sorted by
 * (z_index ASC, doc_order ASC) for the GUI's stacking pass.
 */

#include "box_tree.h"

#include <stddef.h>

/* Inset sentinels. PV_LEN_UNSET comes from page_view.h (= INT_MIN). CSS_LEN_AUTO
 * is INT_MIN + 1 in css.h; we define it locally to keep box_tree.c free of the
 * css.h dependency (the layout cares about the values, not their name). */
#define BT_LEN_AUTO (PV_LEN_UNSET + 1)

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

/* --- Stage 2: position + z-index ----------------------------------------
 *
 * bt_resolve_positioning is a pure, allocation-free pass over the pv_box_def box
 * tree. It walks the tree depth-first (each box's children are the boxes whose
 * parent_id == this box's index; root boxes are those with parent_id == -1),
 * assigns a stable pre-order doc_order to every box, and for each box with
 * position != BT_POS_STATIC computes a final content-box rect:
 *
 *   - RELATIVE / STICKY (sticky fail-closed to relative): keep the in-flow
 *     (box_x[i], box_y[i]) and offset by (inset_left, inset_top). Siblings are
 *     unaffected (the box's own content moves).
 *   - ABSOLUTE: walk the parent_id chain to the nearest positioned ancestor; its
 *     (box_x[a], box_y[a], box_w[a], box_h[a]) is the containing block (or the
 *     viewport if no positioned ancestor exists). Offset by (inset_left,
 *     inset_top).
 *   - FIXED: containing block is the viewport. Offset by (inset_left, inset_top).
 *
 * CSS_LEN_UNSET / CSS_LEN_AUTO on an inset → 0 offset on that axis (the box
 * anchors at the containing block's edge). Only top/left are honored in v1.
 *
 * Output is sorted by (z_index ASC, doc_order ASC) so the GUI can paint in
 * stacking order. CSS_LEN_UNSET on z_index → 0 in the output. NULL geometry
 * arrays are allowed: boxes without an in-flow rect resolve to zero-size at
 * the containing block's origin.
 *
 * Fails closed: out_count == NULL or (boxes == NULL && nbox > 0) →
 * BT_ERR_NULL_ARG; nbox > BT_MAX_POSITIONED → BT_ERR_RANGE (the GUI skips the
 * pass for that frame rather than painting garbage).
 */

/* Recursive doc_order assignment. The box tree is acyclic (each box has at most
 * one parent_id), so the visited bitmap is just a guard against the degenerate
 * case of a cycle from a hostile document. */
static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,
                             char *visited, size_t *next_order,
                             size_t *doc_orders) {
    if (idx >= nbox || visited[idx]) return;
    visited[idx] = 1;
    doc_orders[idx] = (*next_order)++;
    for (size_t i = 0; i < nbox; ++i) {
        if ((size_t)boxes[i].parent_id == idx) {
            assign_doc_order(boxes, nbox, i, visited, next_order, doc_orders);
        }
    }
}

/* Walk the parent_id chain from `start` to find the nearest ancestor with
 * position != STATIC. Returns the ancestor's index, or -1 if none exists
 * (caller falls back to the viewport). Bounded by BT_MAX_DEPTH to keep a
 * hostile tree from looping. */
static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,
                                    size_t start) {
    int cur = (start < nbox) ? (int)boxes[start].parent_id : -1;
    unsigned hops = 0;
    while (cur >= 0 && (size_t)cur < nbox && hops < BT_MAX_DEPTH) {
        if (boxes[cur].position != BT_POS_STATIC) return cur;
        cur = (int)boxes[cur].parent_id;
        hops++;
    }
    return -1;
}

/* Resolves an inset value: PV_LEN_UNSET or BT_LEN_AUTO → 0 (anchor at the
 * containing block's edge); otherwise the px value. */
static double resolve_inset(int v) {
    if (v == PV_LEN_UNSET || v == BT_LEN_AUTO) return 0.0;
    return (double)v;
}

bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,
                                 const double *box_x, const double *box_y,
                                 const double *box_w, const double *box_h,
                                 double viewport_w, double viewport_h,
                                 bt_positioned *out, size_t out_cap,
                                 size_t *out_count) {
    if (out_count == NULL) return BT_ERR_NULL_ARG;
    if (nbox > 0 && boxes == NULL) return BT_ERR_NULL_ARG;
    if (nbox > BT_MAX_POSITIONED) return BT_ERR_RANGE;

    *out_count = 0;
    if (nbox == 0) return BT_OK;

    /* Assign doc_order via depth-first walk from every root box. */
    char visited[BT_MAX_POSITIONED] = {0};
    size_t doc_orders[BT_MAX_POSITIONED] = {0};
    size_t next_order = 0;
    for (size_t i = 0; i < nbox; ++i) {
        if (!visited[i] && boxes[i].parent_id == -1) {
            assign_doc_order(boxes, nbox, i, visited, &next_order, doc_orders);
        }
    }
    /* Orphan boxes (parent_id >= 0 but the chain never reached a root — should
     * not happen for a well-formed box tree, but be safe: assign in document
     * order so they still get a stable doc_order). */
    for (size_t i = 0; i < nbox; ++i) {
        if (!visited[i]) {
            visited[i] = 1;
            doc_orders[i] = next_order++;
        }
    }

    /* Collect positioned boxes. We fill a stack-local buffer of the full count
     * (bounded by BT_MAX_POSITIONED), sort it, then copy the top out_cap
     * entries to out. This way the sort is correct even when count > out_cap:
     * the highest-stacking items always make it into the truncated output. */
    bt_positioned tmp[BT_MAX_POSITIONED];
    size_t tmp_count = 0;
    for (size_t i = 0; i < nbox; ++i) {
        int pos = boxes[i].position;
        /* Only the four non-static values are positioned. 0/1/garbage → skip. */
        if (pos != BT_POS_RELATIVE && pos != BT_POS_ABSOLUTE &&
            pos != BT_POS_FIXED    && pos != BT_POS_STICKY) {
            continue;
        }

        /* Find the containing block. cb_w/cb_h are computed for completeness
         * (the v1 spec honors top/left only, so they don't feed the offset; they
         * are kept here so the `right`/`bottom` extension in a future hito is a
         * one-line change). */
        double cb_x = 0.0, cb_y = 0.0, cb_w = viewport_w, cb_h = viewport_h;
        if (pos == BT_POS_ABSOLUTE) {
            int ancestor = find_positioned_ancestor(boxes, nbox, i);
            if (ancestor >= 0) {
                cb_x = (box_x != NULL) ? box_x[ancestor] : 0.0;
                cb_y = (box_y != NULL) ? box_y[ancestor] : 0.0;
                cb_w = (box_w != NULL) ? box_w[ancestor] : 0.0;
                cb_h = (box_h != NULL) ? box_h[ancestor] : 0.0;
            }
            /* else: viewport (already the default). */
        }
        /* FIXED → viewport (default). RELATIVE/STICKY → in-flow. */
        (void)cb_w;
        (void)cb_h;

        double x, y;
        if (pos == BT_POS_RELATIVE || pos == BT_POS_STICKY) {
            x = (box_x != NULL) ? box_x[i] : 0.0;
            y = (box_y != NULL) ? box_y[i] : 0.0;
        } else {
            x = cb_x;
            y = cb_y;
        }
        x += resolve_inset(boxes[i].inset_left);
        y += resolve_inset(boxes[i].inset_top);

        int z = (boxes[i].z_index == PV_LEN_UNSET) ? 0 : boxes[i].z_index;
        double w = (box_w != NULL) ? box_w[i] : 0.0;
        double h = (box_h != NULL) ? box_h[i] : 0.0;

        tmp[tmp_count].box_index = i;
        tmp[tmp_count].z_index = z;
        tmp[tmp_count].doc_order = doc_orders[i];
        tmp[tmp_count].x = x;
        tmp[tmp_count].y = y;
        tmp[tmp_count].w = w;
        tmp[tmp_count].h = h;
        tmp_count++;
    }

    /* Sort tmp by (z_index ASC, doc_order ASC). Insertion sort — n <= 256, so
     * O(n²) is trivially fast and the code is simpler than qsort with a
     * comparator. */
    for (size_t i = 1; i < tmp_count; ++i) {
        bt_positioned key = tmp[i];
        size_t j = i;
        while (j > 0) {
            bt_positioned *p = &tmp[j - 1];
            if (p->z_index > key.z_index ||
                (p->z_index == key.z_index && p->doc_order > key.doc_order)) {
                *(&tmp[j]) = *p;
                j--;
            } else {
                break;
            }
        }
        tmp[j] = key;
    }

    /* Copy the top out_cap entries to out. */
    size_t to_copy = (tmp_count < out_cap) ? tmp_count : out_cap;
    for (size_t i = 0; i < to_copy; ++i) out[i] = tmp[i];
    *out_count = tmp_count;
    return BT_OK;
}
