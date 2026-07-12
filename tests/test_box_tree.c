/*
 * test_box_tree — CMocka suite for the pure recursive block/flex/grid layout.
 *
 * Builds small trees by hand (leaf content heights, margins, flex factors) and
 * asserts the resolved rectangles: block stacking with margin collapsing and
 * padding, flex row with grow/justify/gap, grid rows/columns, nesting, display:none
 * skipping, the leaf base case, and the fail-closed edges (NULL, depth/children
 * caps, bad grid columns).
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "box_tree.h"
#include "page_view.h"   /* pv_box_def for Stage 2 positioning tests */

static int dbl_eq(double a, double b) {
    double d = a - b;
    return d < 1e-6 && d > -1e-6;
}

static void assert_rect(const bt_node *n, double x, double y, double w, double h) {
    assert_true(dbl_eq(n->x, x));
    assert_true(dbl_eq(n->y, y));
    assert_true(dbl_eq(n->w, w));
    assert_true(dbl_eq(n->h, h));
}

static void test_null_root(void **state) {
    (void)state;
    assert_int_equal(bt_layout(NULL, 200), BT_ERR_NULL_ARG);
}

static void test_leaf(void **state) {
    (void)state;
    bt_node root = { .display = BX_DISPLAY_BLOCK, .content_h = 50 };
    assert_int_equal(bt_layout(&root, 200), BT_OK);
    assert_rect(&root, 0, 0, 200, 50);
}

static void test_leaf_with_padding(void **state) {
    (void)state;
    bt_node leaf = { .display = BX_DISPLAY_BLOCK, .content_h = 30 };
    bt_node root = {
        .display = BX_DISPLAY_BLOCK,
        .padding = { 10, 10, 10, 10 },
        .children = &leaf, .child_count = 1,
    };
    assert_int_equal(bt_layout(&root, 200), BT_OK);
    /* content width = 200 - 20 = 180; child at the padding origin. */
    assert_rect(&leaf, 10, 10, 180, 30);
    assert_true(dbl_eq(root.h, 50)); /* 10 + 30 + 10 */
    assert_true(dbl_eq(root.w, 200));
}

static void test_block_stacking_with_collapse(void **state) {
    (void)state;
    bt_node kids[2] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 20 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 30, .margin = { .top = 10 } },
    };
    bt_node root = { .display = BX_DISPLAY_BLOCK, .children = kids, .child_count = 2 };
    assert_int_equal(bt_layout(&root, 200), BT_OK);
    assert_rect(&kids[0], 0, 0, 200, 20);
    assert_rect(&kids[1], 0, 30, 200, 30); /* 20 + collapsed top margin 10 */
    assert_true(dbl_eq(root.h, 60));
}

static void test_flex_row_grow(void **state) {
    (void)state;
    bt_node kids[2] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 40, .basis = 100, .grow = 1, .shrink = 1 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 60, .basis = 100, .grow = 1, .shrink = 1 },
    };
    bt_node root = {
        .display = BX_DISPLAY_FLEX, .justify = FX_JUSTIFY_START,
        .children = kids, .child_count = 2,
    };
    assert_int_equal(bt_layout(&root, 300), BT_OK);
    /* free 100 split evenly -> 150 each, laid side by side */
    assert_rect(&kids[0], 0, 0, 150, 40);
    assert_rect(&kids[1], 150, 0, 150, 60);
    assert_true(dbl_eq(root.h, 60));   /* tallest child */
    assert_true(dbl_eq(root.w, 300));
}

static void test_flex_gap_and_justify_center(void **state) {
    (void)state;
    bt_node kids[2] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 20, .basis = 100, .grow = 0, .shrink = 1 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 20, .basis = 100, .grow = 0, .shrink = 1 },
    };
    bt_node root = {
        .display = BX_DISPLAY_FLEX, .justify = FX_JUSTIFY_CENTER, .gap = 20,
        .children = kids, .child_count = 2,
    };
    assert_int_equal(bt_layout(&root, 300), BT_OK);
    /* used = 200 + gap 20 = 220; leftover 80; center start 40 */
    assert_rect(&kids[0], 40, 0, 100, 20);
    assert_rect(&kids[1], 160, 0, 100, 20);
}

static void test_flex_wrap_two_lines(void **state) {
    (void)state;
    /* 3 items of basis 100 in a 250px line: the 3rd (100+10+100+10+100=320 > 250)
     * overflows and starts a new line. */
    bt_node kids[3] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 20, .basis = 100 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 30, .basis = 100 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 15, .basis = 100 },
    };
    bt_node root = {
        .display = BX_DISPLAY_FLEX, .wrap = 1, .gap = 10,
        .children = kids, .child_count = 3,
    };
    assert_int_equal(bt_layout(&root, 250), BT_OK);
    /* line 1: items 0,1 side by side, height = tallest (30). */
    assert_rect(&kids[0], 0,   0, 100, 20);
    assert_rect(&kids[1], 110, 0, 100, 30);
    /* line 2: item 2 alone, below line 1 + cross gap (falls back to `gap` = 10). */
    assert_rect(&kids[2], 0, 40, 100, 15);
    assert_true(dbl_eq(root.h, 55)); /* 30 + 10 + 15 */
}

static void test_flex_nowrap_default_single_line_unchanged(void **state) {
    (void)state;
    /* wrap == 0 (the zero-init default): identical to the pre-wrap behaviour even
     * when items overflow the line (flex_layout shrinks them instead). */
    bt_node kids[3] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 20, .basis = 100, .shrink = 1 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 30, .basis = 100, .shrink = 1 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 15, .basis = 100, .shrink = 1 },
    };
    bt_node root = {
        .display = BX_DISPLAY_FLEX, .gap = 10,
        .children = kids, .child_count = 3,
    };
    assert_int_equal(bt_layout(&root, 250), BT_OK);
    assert_true(dbl_eq(kids[0].y, 0));
    assert_true(dbl_eq(kids[1].y, 0));
    assert_true(dbl_eq(kids[2].y, 0));           /* all on ONE line */
    assert_true(dbl_eq(root.h, 30));             /* tallest of the three */
}

static void test_flex_wrap_reverse_two_lines(void **state) {
    (void)state;
    /* Same 3 items as test_flex_wrap_two_lines, but wrap_reverse = 1: the first
     * line (items 0,1) goes to the BOTTOM, the second line (item 2) at the TOP. */
    bt_node kids[3] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 20, .basis = 100 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 30, .basis = 100 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 15, .basis = 100 },
    };
    bt_node root = {
        .display = BX_DISPLAY_FLEX, .wrap = 1, .wrap_reverse = 1, .gap = 10,
        .children = kids, .child_count = 3,
    };
    assert_int_equal(bt_layout(&root, 250), BT_OK);
    /* Total = 30 + 10 + 15 = 55. Reverse: line 1 (h=15) at top y=0, line 0 (h=30)
     * at bottom y=25 (15+10). item y relative to line base accounts for align. */
    assert_rect(&kids[2], 0,   0, 100, 15);  /* line 1 at top */
    assert_rect(&kids[0], 0,  25, 100, 20);  /* line 0 at bottom */
    assert_rect(&kids[1], 110, 25, 100, 30);
    assert_true(dbl_eq(root.h, 55));
}

static void test_flex_wrap_row_gap_distinct_from_gap(void **state) {
    (void)state;
    bt_node kids[3] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 20, .basis = 200 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 20, .basis = 200 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 20, .basis = 200 },
    };
    bt_node root = {
        .display = BX_DISPLAY_FLEX, .wrap = 1, .gap = 10,
        .has_row_gap = 1, .row_gap = 50,
        .children = kids, .child_count = 3,
    };
    /* 250px line: each item (basis 200) alone on its own line (200+10+200 > 250). */
    assert_int_equal(bt_layout(&root, 250), BT_OK);
    assert_true(dbl_eq(kids[0].y, 0));
    assert_true(dbl_eq(kids[1].y, 70));   /* 20 + row_gap 50, NOT gap 10 */
    assert_true(dbl_eq(kids[2].y, 140));
    assert_true(dbl_eq(root.h, 160));     /* 3*20 + 2*50 */
}

static void test_flex_cross_axis_align(void **state) {
    (void)state;
    bt_node kids[3] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 40, .basis = 50, .align = BT_ALIGN_START },
        { .display = BX_DISPLAY_BLOCK, .content_h = 10, .basis = 50, .align = BT_ALIGN_CENTER },
        { .display = BX_DISPLAY_BLOCK, .content_h = 10, .basis = 50, .align = BT_ALIGN_END },
    };
    bt_node root = {
        .display = BX_DISPLAY_FLEX, .gap = 0,
        .children = kids, .child_count = 3,
    };
    assert_int_equal(bt_layout(&root, 150), BT_OK);
    /* line height = tallest = 40 (from the START item). */
    assert_true(dbl_eq(kids[0].y, 0));    /* start: no offset */
    assert_true(dbl_eq(kids[1].y, 15));   /* center: (40-10)/2 */
    assert_true(dbl_eq(kids[2].y, 30));   /* end: 40-10 */
}

static void test_grid_row_gap_distinct_from_gap(void **state) {
    (void)state;
    bt_node kids[4] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 10 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 20 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 30 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 40 },
    };
    bt_node root = {
        .display = BX_DISPLAY_GRID, .grid_cols = 2, .gap = 10,
        .has_row_gap = 1, .row_gap = 100,
        .children = kids, .child_count = 4,
    };
    assert_int_equal(bt_layout(&root, 210), BT_OK);
    /* column gap unaffected (still `gap` = 10: col_w = (210-10)/2 = 100). */
    assert_rect(&kids[0], 0,   0,   100, 10);
    assert_rect(&kids[1], 110, 0,   100, 20);
    /* row spacing uses row_gap (100), not gap (10). */
    assert_rect(&kids[2], 0,   120, 100, 30); /* row1 y = 20 + row_gap 100 */
    assert_rect(&kids[3], 110, 120, 100, 40);
    assert_true(dbl_eq(root.h, 160)); /* 20 + 100 + 40 */
}

static void test_grid_without_row_gap_falls_back_to_gap(void **state) {
    (void)state;
    /* has_row_gap == 0 (zero-init default): identical to the pre-row-gap behaviour. */
    bt_node kids[2] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 10 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 20 },
    };
    bt_node root = {
        .display = BX_DISPLAY_GRID, .grid_cols = 1, .gap = 5,
        .children = kids, .child_count = 2,
    };
    assert_int_equal(bt_layout(&root, 100), BT_OK);
    assert_true(dbl_eq(kids[1].y, 15)); /* 10 + gap 5 */
    assert_true(dbl_eq(root.h, 35));
}

static void test_grid(void **state) {
    (void)state;
    bt_node kids[4] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 10 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 20 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 30 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 40 },
    };
    bt_node root = {
        .display = BX_DISPLAY_GRID, .grid_cols = 2, .gap = 10,
        .children = kids, .child_count = 4,
    };
    assert_int_equal(bt_layout(&root, 210), BT_OK);
    /* col_w = (210-10)/2 = 100; col_x = 0,110; rows: maxh 20 then 40 */
    assert_rect(&kids[0], 0,   0,  100, 10);
    assert_rect(&kids[1], 110, 0,  100, 20);
    assert_rect(&kids[2], 0,   30, 100, 30); /* row1 y = 20 + gap 10 */
    assert_rect(&kids[3], 110, 30, 100, 40);
    assert_true(dbl_eq(root.h, 70)); /* 20 + 10 + 40 */
}

static void test_grid_weighted_tracks(void **state) {
    (void)state;
    /* 2fr 1fr over 310px, gap 10: remaining 300 -> 200/100 */
    int track[2] = { -200, -100 };
    bt_node kids[2] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 10 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 10 },
    };
    bt_node root = {
        .display = BX_DISPLAY_GRID, .grid_cols = 2, .gap = 10,
        .grid_track = track, .grid_ntrack = 2,
        .children = kids, .child_count = 2,
    };
    assert_int_equal(bt_layout(&root, 310), BT_OK);
    assert_rect(&kids[0], 0,   0, 200, 10);
    assert_rect(&kids[1], 210, 0, 100, 10);
}

static void test_grid_column_span(void **state) {
    (void)state;
    /* 3 equal columns of 100 (gap 10, avail 320); item0 spans 2 -> width
     * 100+10+100 = 210 at col 0; item1 -> col 2; item2 wraps to row 1 */
    bt_node kids[3] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 10, .grid_span = 2 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 20 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 30 },
    };
    bt_node root = {
        .display = BX_DISPLAY_GRID, .grid_cols = 3, .gap = 10,
        .children = kids, .child_count = 3,
    };
    assert_int_equal(bt_layout(&root, 320), BT_OK);
    assert_rect(&kids[0], 0,   0,  210, 10);
    assert_rect(&kids[1], 220, 0,  100, 20);
    assert_rect(&kids[2], 0,   30, 100, 30);  /* row 1 at maxh 20 + gap 10 */
    assert_true(dbl_eq(root.h, 60));          /* 20 + 10 + 30 */
}

static void test_nested_flex_in_block(void **state) {
    (void)state;
    bt_node fkids[2] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 40, .basis = 100, .grow = 0, .shrink = 1 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 40, .basis = 100, .grow = 0, .shrink = 1 },
    };
    bt_node bkids[2] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 20 },
        { .display = BX_DISPLAY_FLEX, .justify = FX_JUSTIFY_START,
          .children = fkids, .child_count = 2 },
    };
    bt_node root = { .display = BX_DISPLAY_BLOCK, .children = bkids, .child_count = 2 };
    assert_int_equal(bt_layout(&root, 300), BT_OK);

    assert_rect(&bkids[0], 0, 0, 300, 20);     /* first block leaf */
    assert_true(dbl_eq(bkids[1].y, 20));       /* flex container below it */
    assert_true(dbl_eq(bkids[1].h, 40));       /* tallest flex child */
    assert_true(dbl_eq(bkids[1].w, 300));
    /* inner children are relative to the flex container's content origin */
    assert_rect(&fkids[0], 0,   0, 100, 40);
    assert_rect(&fkids[1], 100, 0, 100, 40);
    assert_true(dbl_eq(root.h, 60));
}

static void test_display_none_skipped(void **state) {
    (void)state;
    bt_node kids[3] = {
        { .display = BX_DISPLAY_BLOCK, .content_h = 20 },
        { .display = BX_DISPLAY_NONE,  .content_h = 999 },
        { .display = BX_DISPLAY_BLOCK, .content_h = 30, .margin = { .top = 5 } },
    };
    bt_node root = { .display = BX_DISPLAY_BLOCK, .children = kids, .child_count = 3 };
    assert_int_equal(bt_layout(&root, 200), BT_OK);
    assert_rect(&kids[1], 0, 0, 0, 0);    /* none takes no space */
    assert_rect(&kids[0], 0, 0, 200, 20);
    assert_rect(&kids[2], 0, 25, 200, 30); /* placed right after, skipping none */
    assert_true(dbl_eq(root.h, 55));
}

static void test_grid_bad_columns(void **state) {
    (void)state;
    bt_node leaf = { .display = BX_DISPLAY_BLOCK, .content_h = 10 };
    bt_node root = {
        .display = BX_DISPLAY_GRID, .grid_cols = 0,
        .children = &leaf, .child_count = 1,
    };
    assert_int_equal(bt_layout(&root, 200), BT_ERR_RANGE);
}

static void test_flex_negative_gap(void **state) {
    (void)state;
    bt_node leaf = { .display = BX_DISPLAY_BLOCK, .content_h = 10, .basis = 50 };
    bt_node root = {
        .display = BX_DISPLAY_FLEX, .gap = -1,
        .children = &leaf, .child_count = 1,
    };
    assert_int_equal(bt_layout(&root, 200), BT_ERR_RANGE);
}

static void test_children_cap(void **state) {
    (void)state;
    static bt_node many[BT_MAX_CHILDREN + 1];  /* zeroed => block leaves */
    bt_node root = {
        .display = BX_DISPLAY_BLOCK,
        .children = many, .child_count = BT_MAX_CHILDREN + 1,
    };
    assert_int_equal(bt_layout(&root, 200), BT_ERR_RANGE);
}

static void test_depth_cap(void **state) {
    (void)state;
    static bt_node chain[BT_MAX_DEPTH + 5];
    size_t n = sizeof chain / sizeof chain[0];
    for (size_t i = 0; i < n; ++i) {
        chain[i].display = BX_DISPLAY_BLOCK;
        chain[i].content_h = 1;
        if (i + 1 < n) {
            chain[i].children = &chain[i + 1];
            chain[i].child_count = 1;
        }
    }
    assert_int_equal(bt_layout(&chain[0], 200), BT_ERR_RANGE);
}

/* --- Stage 2: position + z-index (red until bt_resolve_positioning exists) --- */

static void test_positioning_null_args(void **state) {
    (void)state;
    bt_positioned out[4];
    size_t cnt = 0;
    /* out_count == NULL */
    assert_int_equal(bt_resolve_positioning(NULL, 0, NULL, NULL, NULL, NULL,
                                            800, 600, out, 4, NULL),
                     BT_ERR_NULL_ARG);
    /* boxes == NULL with nbox > 0 */
    assert_int_equal(bt_resolve_positioning(NULL, 1, NULL, NULL, NULL, NULL,
                                            800, 600, out, 4, &cnt),
                     BT_ERR_NULL_ARG);
}

static void test_positioning_static_unchanged(void **state) {
    (void)state;
    /* A static (or unset) box is NOT in the output. */
    pv_box_def boxes[1] = {{ .parent_id = -1, .position = BT_POS_STATIC }};
    double gx[1] = {10}, gy[1] = {20}, gw[1] = {100}, gh[1] = {30};
    bt_positioned out[4];
    size_t cnt = 99;
    assert_int_equal(bt_resolve_positioning(boxes, 1, gx, gy, gw, gh,
                                            800, 600, out, 4, &cnt), BT_OK);
    assert_int_equal(cnt, 0);
}

static void test_positioning_relative_offset(void **state) {
    (void)state;
    /* position:relative, top:10, left:20 → offset by (20, 10). */
    pv_box_def boxes[1] = {{
        .parent_id = -1, .position = BT_POS_RELATIVE,
        .inset_top = 10, .inset_left = 20,
    }};
    double gx[1] = {0}, gy[1] = {0}, gw[1] = {100}, gh[1] = {50};
    bt_positioned out[4];
    size_t cnt = 0;
    assert_int_equal(bt_resolve_positioning(boxes, 1, gx, gy, gw, gh,
                                            800, 600, out, 4, &cnt), BT_OK);
    assert_int_equal(cnt, 1);
    assert_int_equal(out[0].box_index, 0);
    assert_int_equal(out[0].z_index, 0);
    assert_true(dbl_eq(out[0].x, 20));
    assert_true(dbl_eq(out[0].y, 10));
    assert_true(dbl_eq(out[0].w, 100));
    assert_true(dbl_eq(out[0].h, 50));
}

static void test_positioning_absolute_against_ancestor(void **state) {
    (void)state;
    /* Parent (box 0): position:relative at (50, 50, 200, 100).
     * Child (box 1): position:absolute, top:5, left:10 → at (60, 55). */
    pv_box_def boxes[2] = {
        { .parent_id = -1, .position = BT_POS_RELATIVE },
        { .parent_id =  0, .position = BT_POS_ABSOLUTE,
          .inset_top = 5, .inset_left = 10 },
    };
    double gx[2] = {50, 60}, gy[2] = {50, 60}, gw[2] = {200, 80}, gh[2] = {100, 40};
    bt_positioned out[4];
    size_t cnt = 0;
    assert_int_equal(bt_resolve_positioning(boxes, 2, gx, gy, gw, gh,
                                            800, 600, out, 4, &cnt), BT_OK);
    assert_int_equal(cnt, 2);
    /* Box 0 (relative, no insets) stays at (50, 50). */
    assert_true(dbl_eq(out[0].x, 50));
    assert_true(dbl_eq(out[0].y, 50));
    /* Box 1 (absolute) is at parent (50,50) + (10,5) = (60, 55). */
    assert_true(dbl_eq(out[1].x, 60));
    assert_true(dbl_eq(out[1].y, 55));
}

static void test_positioning_absolute_against_viewport(void **state) {
    (void)state;
    /* Absolute with no positioned ancestor → viewport. */
    pv_box_def boxes[1] = {{
        .parent_id = -1, .position = BT_POS_ABSOLUTE,
        .inset_top = 10, .inset_left = 20,
    }};
    double gx[1] = {0}, gy[1] = {0}, gw[1] = {100}, gh[1] = {50};
    bt_positioned out[4];
    size_t cnt = 0;
    assert_int_equal(bt_resolve_positioning(boxes, 1, gx, gy, gw, gh,
                                            800, 600, out, 4, &cnt), BT_OK);
    assert_int_equal(cnt, 1);
    assert_true(dbl_eq(out[0].x, 20));
    assert_true(dbl_eq(out[0].y, 10));
}

static void test_positioning_fixed_against_viewport(void **state) {
    (void)state;
    /* position:fixed → viewport regardless of ancestors. */
    pv_box_def boxes[2] = {
        { .parent_id = -1, .position = BT_POS_RELATIVE },
        { .parent_id =  0, .position = BT_POS_FIXED,
          .inset_top = 5, .inset_left = 10 },
    };
    double gx[2] = {50, 60}, gy[2] = {50, 60}, gw[2] = {200, 80}, gh[2] = {100, 40};
    bt_positioned out[4];
    size_t cnt = 0;
    assert_int_equal(bt_resolve_positioning(boxes, 2, gx, gy, gw, gh,
                                            800, 600, out, 4, &cnt), BT_OK);
    assert_int_equal(cnt, 2);
    /* Box 1 (fixed) at viewport (0,0) + (10,5) = (10, 5), NOT at parent's (50,50). */
    assert_true(dbl_eq(out[1].x, 10));
    assert_true(dbl_eq(out[1].y, 5));
}

static void test_positioning_sticky_treated_as_relative(void **state) {
    (void)state;
    /* position:sticky → relative (fail-closed). */
    pv_box_def boxes[1] = {{
        .parent_id = -1, .position = BT_POS_STICKY,
        .inset_top = 10, .inset_left = 20,
    }};
    double gx[1] = {0}, gy[1] = {0}, gw[1] = {100}, gh[1] = {50};
    bt_positioned out[4];
    size_t cnt = 0;
    assert_int_equal(bt_resolve_positioning(boxes, 1, gx, gy, gw, gh,
                                            800, 600, out, 4, &cnt), BT_OK);
    assert_int_equal(cnt, 1);
    /* Sticky → relative: offset by insets from in-flow position. */
    assert_true(dbl_eq(out[0].x, 20));
    assert_true(dbl_eq(out[0].y, 10));
}

static void test_positioning_stacking_order(void **state) {
    (void)state;
    /* Three relative boxes with z=1, z=10, z=-1 in document order.
     * Stacking: z=-1 (box 2), z=1 (box 0), z=10 (box 1). */
    pv_box_def boxes[3] = {
        { .parent_id = -1, .position = BT_POS_RELATIVE, .z_index =  1 },
        { .parent_id = -1, .position = BT_POS_RELATIVE, .z_index = 10 },
        { .parent_id = -1, .position = BT_POS_RELATIVE, .z_index = -1 },
    };
    double gx[3] = {0,0,0}, gy[3] = {0,0,0}, gw[3] = {100,100,100}, gh[3] = {50,50,50};
    bt_positioned out[4];
    size_t cnt = 0;
    assert_int_equal(bt_resolve_positioning(boxes, 3, gx, gy, gw, gh,
                                            800, 600, out, 4, &cnt), BT_OK);
    assert_int_equal(cnt, 3);
    assert_int_equal(out[0].box_index, 2); assert_int_equal(out[0].z_index, -1);
    assert_int_equal(out[1].box_index, 0); assert_int_equal(out[1].z_index,  1);
    assert_int_equal(out[2].box_index, 1); assert_int_equal(out[2].z_index, 10);
}

static void test_positioning_doc_order_tiebreak(void **state) {
    (void)state;
    /* Two boxes with the same z-index → document order is the tiebreaker. */
    pv_box_def boxes[2] = {
        { .parent_id = -1, .position = BT_POS_RELATIVE, .z_index = 5 },
        { .parent_id = -1, .position = BT_POS_RELATIVE, .z_index = 5 },
    };
    double gx[2] = {0,0}, gy[2] = {0,0}, gw[2] = {100,100}, gh[2] = {50,50};
    bt_positioned out[4];
    size_t cnt = 0;
    assert_int_equal(bt_resolve_positioning(boxes, 2, gx, gy, gw, gh,
                                            800, 600, out, 4, &cnt), BT_OK);
    assert_int_equal(cnt, 2);
    assert_int_equal(out[0].box_index, 0);
    assert_int_equal(out[1].box_index, 1);
    assert_true(out[0].doc_order < out[1].doc_order);
}

static void test_positioning_no_insets(void **state) {
    (void)state;
    /* Absolute with no insets → at the containing block's origin. */
    pv_box_def boxes[2] = {
        { .parent_id = -1, .position = BT_POS_RELATIVE },
        { .parent_id =  0, .position = BT_POS_ABSOLUTE },
    };
    double gx[2] = {50,50}, gy[2] = {50,50}, gw[2] = {200,80}, gh[2] = {100,40};
    bt_positioned out[4];
    size_t cnt = 0;
    assert_int_equal(bt_resolve_positioning(boxes, 2, gx, gy, gw, gh,
                                            800, 600, out, 4, &cnt), BT_OK);
    assert_int_equal(cnt, 2);
    assert_true(dbl_eq(out[1].x, 50));
    assert_true(dbl_eq(out[1].y, 50));
}

static void test_positioning_null_geometry(void **state) {
    (void)state;
    /* NULL geometry arrays → zero-size at the containing block's origin. */
    pv_box_def boxes[1] = {{
        .parent_id = -1, .position = BT_POS_RELATIVE,
    }};
    bt_positioned out[4];
    size_t cnt = 0;
    assert_int_equal(bt_resolve_positioning(boxes, 1, NULL, NULL, NULL, NULL,
                                            800, 600, out, 4, &cnt), BT_OK);
    assert_int_equal(cnt, 1);
    assert_true(dbl_eq(out[0].x, 0));
    assert_true(dbl_eq(out[0].y, 0));
    assert_true(dbl_eq(out[0].w, 0));
    assert_true(dbl_eq(out[0].h, 0));
}

static void test_positioning_nbox_cap(void **state) {
    (void)state;
    /* nbox > BT_MAX_POSITIONED fails closed (BT_ERR_RANGE). */
    size_t big_n = BT_MAX_POSITIONED + 1;
    pv_box_def boxes[BT_MAX_POSITIONED + 1];
    double gx[BT_MAX_POSITIONED + 1] = {0};
    bt_positioned out[BT_MAX_POSITIONED + 1];
    size_t cnt = 0;
    for (size_t i = 0; i < big_n; ++i) {
        boxes[i].parent_id = -1;
        boxes[i].position = BT_POS_RELATIVE;
    }
    assert_int_equal(bt_resolve_positioning(boxes, big_n, gx, gx, gx, gx,
                                            800, 600, out, big_n, &cnt),
                     BT_ERR_RANGE);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_null_root),
        cmocka_unit_test(test_leaf),
        cmocka_unit_test(test_leaf_with_padding),
        cmocka_unit_test(test_block_stacking_with_collapse),
        cmocka_unit_test(test_flex_row_grow),
        cmocka_unit_test(test_flex_gap_and_justify_center),
        cmocka_unit_test(test_flex_wrap_two_lines),
        cmocka_unit_test(test_flex_wrap_reverse_two_lines),
        cmocka_unit_test(test_flex_nowrap_default_single_line_unchanged),
        cmocka_unit_test(test_flex_wrap_row_gap_distinct_from_gap),
        cmocka_unit_test(test_flex_cross_axis_align),
        cmocka_unit_test(test_grid_row_gap_distinct_from_gap),
        cmocka_unit_test(test_grid_without_row_gap_falls_back_to_gap),
        cmocka_unit_test(test_grid),
        cmocka_unit_test(test_grid_weighted_tracks),
        cmocka_unit_test(test_grid_column_span),
        cmocka_unit_test(test_nested_flex_in_block),
        cmocka_unit_test(test_display_none_skipped),
        cmocka_unit_test(test_grid_bad_columns),
        cmocka_unit_test(test_flex_negative_gap),
        cmocka_unit_test(test_children_cap),
        cmocka_unit_test(test_depth_cap),
        cmocka_unit_test(test_positioning_null_args),
        cmocka_unit_test(test_positioning_static_unchanged),
        cmocka_unit_test(test_positioning_relative_offset),
        cmocka_unit_test(test_positioning_absolute_against_ancestor),
        cmocka_unit_test(test_positioning_absolute_against_viewport),
        cmocka_unit_test(test_positioning_fixed_against_viewport),
        cmocka_unit_test(test_positioning_sticky_treated_as_relative),
        cmocka_unit_test(test_positioning_stacking_order),
        cmocka_unit_test(test_positioning_doc_order_tiebreak),
        cmocka_unit_test(test_positioning_no_insets),
        cmocka_unit_test(test_positioning_null_geometry),
        cmocka_unit_test(test_positioning_nbox_cap),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
