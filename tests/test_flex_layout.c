/*
 * test_flex_layout — CMocka suite for the pure flexbox/grid solver.
 *
 * Covers grow (equal and weighted), shrink (equal and with min-clamp freezing),
 * gap, every justify-content mode, the negative-field clamping, the equal-column
 * grid solver and row-major cell placement, the fail-closed edges (NULL, range,
 * no-op n/ncols == 0) and the name helper.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "flex_layout.h"

static int dbl_eq(double a, double b) {
    double d = a - b;
    return d < 1e-6 && d > -1e-6;
}

static void assert_item(fx_result r, double pos, double size) {
    assert_true(dbl_eq(r.pos, pos));
    assert_true(dbl_eq(r.size, size));
}

static void test_grow_equal(void **state) {
    (void)state;
    fx_item it[2] = { { 100, 1, 1, 0 }, { 100, 1, 1, 0 } };
    fx_result out[2];
    assert_int_equal(fx_flex_line(it, 2, 300, 0, FX_JUSTIFY_START, out), FX_OK);
    assert_item(out[0], 0.0, 150.0);
    assert_item(out[1], 150.0, 150.0);
}

static void test_grow_weighted(void **state) {
    (void)state;
    fx_item it[2] = { { 100, 1, 1, 0 }, { 100, 3, 1, 0 } };
    fx_result out[2];
    assert_int_equal(fx_flex_line(it, 2, 300, 0, FX_JUSTIFY_START, out), FX_OK);
    assert_item(out[0], 0.0, 125.0);
    assert_item(out[1], 125.0, 175.0);
}

static void test_shrink_equal(void **state) {
    (void)state;
    fx_item it[2] = { { 200, 1, 1, 0 }, { 200, 1, 1, 0 } };
    fx_result out[2];
    assert_int_equal(fx_flex_line(it, 2, 300, 0, FX_JUSTIFY_START, out), FX_OK);
    assert_item(out[0], 0.0, 150.0);
    assert_item(out[1], 150.0, 150.0);
}

static void test_shrink_with_min_clamp(void **state) {
    (void)state;
    /* item0 cannot shrink below 180; it freezes and item1 absorbs the rest. */
    fx_item it[2] = { { 200, 1, 1, 180 }, { 200, 1, 1, 0 } };
    fx_result out[2];
    assert_int_equal(fx_flex_line(it, 2, 300, 0, FX_JUSTIFY_START, out), FX_OK);
    assert_item(out[0], 0.0, 180.0);
    assert_item(out[1], 180.0, 120.0);
}

static void test_gap_start(void **state) {
    (void)state;
    fx_item it[2] = { { 100, 0, 1, 0 }, { 100, 0, 1, 0 } };
    fx_result out[2];
    assert_int_equal(fx_flex_line(it, 2, 300, 20, FX_JUSTIFY_START, out), FX_OK);
    assert_item(out[0], 0.0, 100.0);
    assert_item(out[1], 120.0, 100.0);
}

static void test_justify_center(void **state) {
    (void)state;
    fx_item it[2] = { { 100, 0, 1, 0 }, { 100, 0, 1, 0 } };
    fx_result out[2];
    assert_int_equal(fx_flex_line(it, 2, 300, 20, FX_JUSTIFY_CENTER, out), FX_OK);
    assert_item(out[0], 40.0, 100.0);
    assert_item(out[1], 160.0, 100.0);
}

static void test_justify_end(void **state) {
    (void)state;
    fx_item it[2] = { { 100, 0, 1, 0 }, { 100, 0, 1, 0 } };
    fx_result out[2];
    assert_int_equal(fx_flex_line(it, 2, 300, 20, FX_JUSTIFY_END, out), FX_OK);
    assert_item(out[0], 80.0, 100.0);
    assert_item(out[1], 200.0, 100.0);
}

static void test_justify_space_between(void **state) {
    (void)state;
    fx_item it[2] = { { 100, 0, 1, 0 }, { 100, 0, 1, 0 } };
    fx_result out[2];
    assert_int_equal(fx_flex_line(it, 2, 300, 0, FX_JUSTIFY_SPACE_BETWEEN, out), FX_OK);
    assert_item(out[0], 0.0, 100.0);
    assert_item(out[1], 200.0, 100.0);
}

static void test_justify_space_around(void **state) {
    (void)state;
    fx_item it[2] = { { 100, 0, 1, 0 }, { 100, 0, 1, 0 } };
    fx_result out[2];
    assert_int_equal(fx_flex_line(it, 2, 300, 0, FX_JUSTIFY_SPACE_AROUND, out), FX_OK);
    assert_item(out[0], 25.0, 100.0);
    assert_item(out[1], 175.0, 100.0);
}

static void test_justify_space_evenly(void **state) {
    (void)state;
    fx_item it[3] = { { 50, 0, 1, 0 }, { 50, 0, 1, 0 }, { 50, 0, 1, 0 } };
    fx_result out[3];
    assert_int_equal(fx_flex_line(it, 3, 300, 0, FX_JUSTIFY_SPACE_EVENLY, out), FX_OK);
    assert_item(out[0], 37.5, 50.0);
    assert_item(out[1], 125.0, 50.0);
    assert_item(out[2], 212.5, 50.0);
}

static void test_space_between_single_item_is_start(void **state) {
    (void)state;
    fx_item it[1] = { { 100, 0, 1, 0 } };
    fx_result out[1];
    assert_int_equal(fx_flex_line(it, 1, 300, 0, FX_JUSTIFY_SPACE_BETWEEN, out), FX_OK);
    assert_item(out[0], 0.0, 100.0);  /* no divide-by-zero, behaves like start */
}

static void test_negative_fields_clamped(void **state) {
    (void)state;
    /* negative grow on item0 -> treated as 0, so only item1 grows. */
    fx_item it[2] = { { 100, -1, 0, 0 }, { 100, 1, 0, 0 } };
    fx_result out[2];
    assert_int_equal(fx_flex_line(it, 2, 300, 0, FX_JUSTIFY_START, out), FX_OK);
    assert_item(out[0], 0.0, 100.0);
    assert_item(out[1], 100.0, 200.0);
}

static void test_flex_zero_items_is_noop(void **state) {
    (void)state;
    assert_int_equal(fx_flex_line(NULL, 0, 300, 0, FX_JUSTIFY_START, NULL), FX_OK);
}

static void test_flex_errors(void **state) {
    (void)state;
    fx_item it[2] = { { 100, 0, 1, 0 }, { 100, 0, 1, 0 } };
    fx_result out[2];
    assert_int_equal(fx_flex_line(NULL, 2, 300, 0, FX_JUSTIFY_START, out), FX_ERR_NULL_ARG);
    assert_int_equal(fx_flex_line(it, 2, 300, 0, FX_JUSTIFY_START, NULL), FX_ERR_NULL_ARG);
    assert_int_equal(fx_flex_line(it, 2, -1, 0, FX_JUSTIFY_START, out), FX_ERR_RANGE);
    assert_int_equal(fx_flex_line(it, 2, 300, -1, FX_JUSTIFY_START, out), FX_ERR_RANGE);
    assert_int_equal(fx_flex_line(it, (size_t)FX_MAX_ITEMS + 1, 300, 0, FX_JUSTIFY_START, out),
                     FX_ERR_RANGE);
}

static void test_grid_columns(void **state) {
    (void)state;
    double x[3], w[3];
    assert_int_equal(fx_grid_columns(320, 3, 10, x, w), FX_OK);
    assert_true(dbl_eq(w[0], 100.0));
    assert_true(dbl_eq(w[1], 100.0));
    assert_true(dbl_eq(w[2], 100.0));
    assert_true(dbl_eq(x[0], 0.0));
    assert_true(dbl_eq(x[1], 110.0));
    assert_true(dbl_eq(x[2], 220.0));
}

static void test_grid_columns_too_narrow_clamps_to_zero(void **state) {
    (void)state;
    double x[4], w[4];
    assert_int_equal(fx_grid_columns(10, 4, 20, x, w), FX_OK);
    for (int i = 0; i < 4; ++i) assert_true(w[i] >= 0.0);  /* never negative */
}

static void test_grid_columns_edges(void **state) {
    (void)state;
    double x[2], w[2];
    assert_int_equal(fx_grid_columns(320, 0, 10, NULL, NULL), FX_OK);  /* no-op */
    assert_int_equal(fx_grid_columns(-1, 2, 10, x, w), FX_ERR_RANGE);
    assert_int_equal(fx_grid_columns(320, 2, -1, x, w), FX_ERR_RANGE);
    assert_int_equal(fx_grid_columns(320, (size_t)FX_MAX_ITEMS + 1, 10, x, w), FX_ERR_RANGE);
    assert_int_equal(fx_grid_columns(320, 2, 10, NULL, w), FX_ERR_NULL_ARG);
}

static void test_grid_cell(void **state) {
    (void)state;
    size_t r, c;
    fx_grid_cell(0, 3, &r, &c); assert_int_equal(r, 0); assert_int_equal(c, 0);
    fx_grid_cell(7, 3, &r, &c); assert_int_equal(r, 2); assert_int_equal(c, 1);
    fx_grid_cell(5, 5, &r, &c); assert_int_equal(r, 1); assert_int_equal(c, 0);
    fx_grid_cell(3, 0, &r, &c); assert_int_equal(r, 0); assert_int_equal(c, 0); /* no div by zero */
}

/* --- weighted tracks + column spans (2026-07-11) --- */

static void test_grid_weighted_fr(void **state) {
    (void)state;
    /* 2fr 1fr 1fr over 400px, no gap -> 200/100/100 */
    int track[3] = { -200, -100, -100 };
    double x[3], w[3];
    assert_int_equal(fx_grid_columns_weighted(400, 3, 0, track, 3, x, w), FX_OK);
    assert_true(dbl_eq(w[0], 200.0)); assert_true(dbl_eq(w[1], 100.0));
    assert_true(dbl_eq(w[2], 100.0));
    assert_true(dbl_eq(x[0], 0.0)); assert_true(dbl_eq(x[1], 200.0));
    assert_true(dbl_eq(x[2], 300.0));
}

static void test_grid_weighted_fixed_px_reserved_first(void **state) {
    (void)state;
    /* 100px 1fr 1fr over 400px with gap 10: fixed 100 first, gaps 20,
     * remaining 280 split 140/140 */
    int track[3] = { 100, -100, -100 };
    double x[3], w[3];
    assert_int_equal(fx_grid_columns_weighted(400, 3, 10, track, 3, x, w), FX_OK);
    assert_true(dbl_eq(w[0], 100.0)); assert_true(dbl_eq(w[1], 140.0));
    assert_true(dbl_eq(w[2], 140.0));
    assert_true(dbl_eq(x[1], 110.0)); assert_true(dbl_eq(x[2], 260.0));
}

static void test_grid_weighted_all_auto_matches_equal(void **state) {
    (void)state;
    /* auto tracks (0) and a NULL track array must be byte-identical to
     * fx_grid_columns */
    int track[2] = { 0, 0 };
    double x[2], w[2], ex[2], ew[2];
    assert_int_equal(fx_grid_columns(305, 2, 5, ex, ew), FX_OK);
    assert_int_equal(fx_grid_columns_weighted(305, 2, 5, track, 2, x, w), FX_OK);
    assert_true(dbl_eq(w[0], ew[0])); assert_true(dbl_eq(x[1], ex[1]));
    assert_int_equal(fx_grid_columns_weighted(305, 2, 5, NULL, 0, x, w), FX_OK);
    assert_true(dbl_eq(w[1], ew[1])); assert_true(dbl_eq(x[0], ex[0]));
}

static void test_grid_weighted_fixed_overflow_zeroes_fr(void **state) {
    (void)state;
    /* fixed tracks larger than avail: fr tracks get 0, never negative */
    int track[2] = { 500, -100 };
    double x[2], w[2];
    assert_int_equal(fx_grid_columns_weighted(300, 2, 0, track, 2, x, w), FX_OK);
    assert_true(dbl_eq(w[0], 500.0));
    assert_true(dbl_eq(w[1], 0.0));
}

static void test_grid_weighted_errors(void **state) {
    (void)state;
    double x[2], w[2];
    int track[2] = { 0, 0 };
    assert_int_equal(fx_grid_columns_weighted(300, 0, 0, track, 2, x, w), FX_OK); /* no-op */
    assert_int_equal(fx_grid_columns_weighted(-1, 2, 0, track, 2, x, w), FX_ERR_RANGE);
    assert_int_equal(fx_grid_columns_weighted(300, 2, -1, track, 2, x, w), FX_ERR_RANGE);
    assert_int_equal(fx_grid_columns_weighted(300, 2, 0, track, 2, NULL, w), FX_ERR_NULL_ARG);
}

static void test_grid_place_span_basic(void **state) {
    (void)state;
    /* 3 columns; item0 spans 2 -> (0,0); item1 span 1 -> (0,2); item2 span 1 -> (1,0) */
    int span[3] = { 2, 1, 1 };
    size_t row[3], col[3];
    assert_int_equal(fx_grid_place_span(3, 3, span, NULL, row, col), FX_OK);
    assert_int_equal(row[0], 0); assert_int_equal(col[0], 0);
    assert_int_equal(row[1], 0); assert_int_equal(col[1], 2);
    assert_int_equal(row[2], 1); assert_int_equal(col[2], 0);
}

static void test_grid_place_span_wraps_when_it_does_not_fit(void **state) {
    (void)state;
    /* 3 columns; item0 span 1 -> (0,0); item1 span 3 does not fit after col 0 ->
     * jumps to (1,0); item2 -> (2,0) */
    int span[3] = { 1, 3, 1 };
    size_t row[3], col[3];
    assert_int_equal(fx_grid_place_span(3, 3, span, NULL, row, col), FX_OK);
    assert_int_equal(row[0], 0); assert_int_equal(col[0], 0);
    assert_int_equal(row[1], 1); assert_int_equal(col[1], 0);
    assert_int_equal(row[2], 2); assert_int_equal(col[2], 0);
}

static void test_grid_place_span_clamps_and_defaults(void **state) {
    (void)state;
    /* span > ncols clamps to ncols; span <= 0 and NULL spans mean 1 */
    int span[2] = { 9, 0 };
    size_t row[2], col[2];
    assert_int_equal(fx_grid_place_span(2, 3, span, NULL, row, col), FX_OK);
    assert_int_equal(row[0], 0); assert_int_equal(col[0], 0);
    assert_int_equal(row[1], 1); assert_int_equal(col[1], 0);
    assert_int_equal(fx_grid_place_span(2, 3, NULL, NULL, row, col), FX_OK);
    assert_int_equal(row[1], 0); assert_int_equal(col[1], 1);
    /* fail-closed edges */
    assert_int_equal(fx_grid_place_span(0, 3, NULL, NULL, NULL, NULL), FX_OK);   /* no-op */
    assert_int_equal(fx_grid_place_span(2, 0, span, NULL, row, col), FX_ERR_RANGE);
    assert_int_equal(fx_grid_place_span(2, 3, span, NULL, NULL, col), FX_ERR_NULL_ARG);
}

static void test_grid_place_rowspan(void **state) {
    (void)state;
    /* 3 cols x 4 items:
     * item0: rowspan 2 → (row=0,col=0), blocks col 0 of row 1
     * item1: span 1    → (row=0,col=1)
     * item2: rowspan 2 → (row=0,col=2), blocks col 2 of row 1
     * item3: span 1    → cursor at row 1, col 0 blocked, col 1 free → (row=1,col=1) */
    int span[4]      = { 1, 1, 1, 1 };
    int row_span[4]  = { 2, 1, 2, 1 };
    size_t row[4], col[4];
    assert_int_equal(fx_grid_place_span(4, 3, span, row_span, row, col), FX_OK);
    assert_int_equal(row[0], 0); assert_int_equal(col[0], 0);
    assert_int_equal(row[1], 0); assert_int_equal(col[1], 1);
    assert_int_equal(row[2], 0); assert_int_equal(col[2], 2);
    assert_int_equal(row[3], 1); assert_int_equal(col[3], 1);
}

static void test_float_pack_left(void **state) {
    (void)state;
    /* Two left floats pack from the left edge, separated by gap. */
    double w[2] = { 180.0, 400.0 };
    int side[2] = { 0, 0 };
    double x[2];
    assert_int_equal(fx_float_pack(w, side, 2, 712, 10, x), FX_OK);
    assert_true(dbl_eq(x[0], 0.0));
    assert_true(dbl_eq(x[1], 190.0));   /* 180 + 10 gap */
}

static void test_float_pack_left_and_right(void **state) {
    (void)state;
    /* A left main + a right sidebar: main hugs the left, sidebar hugs the right,
     * regardless of document order. */
    double w[2] = { 400.0, 180.0 };
    int side[2] = { 0, 1 };   /* item0 left, item1 right */
    double x[2];
    assert_int_equal(fx_float_pack(w, side, 2, 712, 0, x), FX_OK);
    assert_true(dbl_eq(x[0], 0.0));
    assert_true(dbl_eq(x[1], 532.0));   /* 712 - 180 */
}

static void test_float_pack_two_right(void **state) {
    (void)state;
    /* Two right floats: the first in document order sits furthest right. */
    double w[2] = { 100.0, 100.0 };
    int side[2] = { 1, 1 };
    double x[2];
    assert_int_equal(fx_float_pack(w, side, 2, 500, 10, x), FX_OK);
    assert_true(dbl_eq(x[0], 400.0));   /* 500 - 100 */
    assert_true(dbl_eq(x[1], 290.0));   /* 400 - 10 gap - 100 */
}

/* --- fx_float_insets: text flows BESIDE a float (v3, spec/float.md §6b.2) ------
 *
 * CSS 2.1 §9.5: a float does not move the following block, it SHORTENS the line
 * boxes it overlaps. Freedom used to push that content below the float instead,
 * which collapsed every sidebar/infobox page into one tall single column -- the
 * largest measured divergence from Firefox in the renderer. */

static void test_float_insets_left_overlapping_line(void **state) {
    (void)state;
    /* A 220px left float occupying y in [0, 60). */
    fx_float_rect r[1] = { { 0.0, 60.0, 220.0, 0 } };
    double l = -1.0, rr = -1.0;
    assert_int_equal(fx_float_insets(r, 1, 10.0, 20.0, 968.0, &l, &rr), FX_OK);
    assert_true(l == 220.0);   /* the line starts past the float */
    assert_true(rr == 0.0);    /* nothing steals from the right */
}

static void test_float_insets_line_past_bottom_is_full_width(void **state) {
    (void)state;
    fx_float_rect r[1] = { { 0.0, 60.0, 220.0, 0 } };
    double l = -1.0, rr = -1.0;
    /* A line that starts at the float's bottom no longer overlaps it (the band is
     * half-open), so the line recovers the full container width -- this is what
     * makes the last lines of a long paragraph run edge to edge, as in Firefox. */
    assert_int_equal(fx_float_insets(r, 1, 60.0, 20.0, 968.0, &l, &rr), FX_OK);
    assert_true(l == 0.0);
    assert_true(rr == 0.0);

    /* A line entirely above the float is unaffected too. */
    fx_float_rect below[1] = { { 100.0, 160.0, 220.0, 0 } };
    assert_int_equal(fx_float_insets(below, 1, 0.0, 20.0, 968.0, &l, &rr), FX_OK);
    assert_true(l == 0.0 && rr == 0.0);
}

static void test_float_insets_right(void **state) {
    (void)state;
    /* A 176px right float in a 968px content rect: its inner edge is at 792. */
    fx_float_rect r[1] = { { 0.0, 40.0, 792.0, 1 } };
    double l = -1.0, rr = -1.0;
    assert_int_equal(fx_float_insets(r, 1, 0.0, 20.0, 968.0, &l, &rr), FX_OK);
    assert_true(l == 0.0);
    assert_true(rr == 176.0);
}

static void test_float_insets_both_sides_take_the_tightest(void **state) {
    (void)state;
    /* Two left floats and one right float all overlapping the line: the left inset
     * is the FARTHEST right edge, the right inset the FARTHEST left one. */
    fx_float_rect r[3] = {
        { 0.0, 80.0, 120.0, 0 },
        { 0.0, 80.0, 220.0, 0 },
        { 0.0, 80.0, 800.0, 1 },
    };
    double l = -1.0, rr = -1.0;
    assert_int_equal(fx_float_insets(r, 3, 10.0, 20.0, 968.0, &l, &rr), FX_OK);
    assert_true(l == 220.0);
    assert_true(rr == 168.0);
}

static void test_float_insets_never_starve_the_line(void **state) {
    (void)state;
    /* A float wider than its container (hostile or just broken CSS) must leave a
     * usable line, never a zero or negative one: fail-open geometry. */
    fx_float_rect wide[1] = { { 0.0, 80.0, 5000.0, 0 } };
    double l = -1.0, rr = -1.0;
    assert_int_equal(fx_float_insets(wide, 1, 0.0, 20.0, 100.0, &l, &rr), FX_OK);
    assert_true(l >= 0.0 && l <= 100.0 - FX_FLOAT_MIN_LINE);

    /* Left and right floats that together overflow the rect still leave room. */
    fx_float_rect both[2] = { { 0.0, 80.0, 90.0, 0 }, { 0.0, 80.0, 10.0, 1 } };
    assert_int_equal(fx_float_insets(both, 2, 0.0, 20.0, 100.0, &l, &rr), FX_OK);
    assert_true(l >= 0.0 && rr >= 0.0);
    assert_true(100.0 - l - rr >= FX_FLOAT_MIN_LINE);

    /* A negative edge (never produced by the packer, but the contract holds) is
     * clamped rather than shifting the line off the left of the content rect. */
    fx_float_rect neg[1] = { { 0.0, 80.0, -50.0, 0 } };
    assert_int_equal(fx_float_insets(neg, 1, 0.0, 20.0, 968.0, &l, &rr), FX_OK);
    assert_true(l == 0.0);
}

static void test_float_insets_edges(void **state) {
    (void)state;
    fx_float_rect r[1] = { { 0.0, 60.0, 220.0, 0 } };
    double l = -1.0, rr = -1.0;
    /* n == 0 writes zero insets and accepts NULL rects. */
    assert_int_equal(fx_float_insets(NULL, 0, 0.0, 20.0, 968.0, &l, &rr), FX_OK);
    assert_true(l == 0.0 && rr == 0.0);
    assert_int_equal(fx_float_insets(NULL, 1, 0.0, 20.0, 968.0, &l, &rr), FX_ERR_NULL_ARG);
    assert_int_equal(fx_float_insets(r, 1, 0.0, 20.0, 968.0, NULL, &rr), FX_ERR_NULL_ARG);
    assert_int_equal(fx_float_insets(r, 1, 0.0, 20.0, 968.0, &l, NULL), FX_ERR_NULL_ARG);
    assert_int_equal(fx_float_insets(r, 1, 0.0, -1.0, 968.0, &l, &rr), FX_ERR_RANGE);
    assert_int_equal(fx_float_insets(r, 1, 0.0, 20.0, -1.0, &l, &rr), FX_ERR_RANGE);
    assert_int_equal(fx_float_insets(r, (size_t)FX_MAX_ITEMS + 1, 0.0, 20.0, 968.0,
                                    &l, &rr), FX_ERR_RANGE);
    /* A zero-height line still consults the float that starts at its y: a line box
     * is measured before its height is known, so h == 0 must not silently opt out. */
    assert_int_equal(fx_float_insets(r, 1, 0.0, 0.0, 968.0, &l, &rr), FX_OK);
    assert_true(l == 220.0);
}

static void test_float_pack_edges(void **state) {
    (void)state;
    double w[2] = { 10, 10 }; int side[2] = { 0, 0 }; double x[2];
    assert_int_equal(fx_float_pack(NULL, NULL, 0, 100, 0, NULL), FX_OK);  /* no-op */
    assert_int_equal(fx_float_pack(NULL, side, 2, 100, 0, x), FX_ERR_NULL_ARG);
    assert_int_equal(fx_float_pack(w, side, 2, -1, 0, x), FX_ERR_RANGE);
    assert_int_equal(fx_float_pack(w, side, (size_t)FX_MAX_ITEMS + 1, 100, 0, x), FX_ERR_RANGE);
    /* Overflowing right float clamps to >= 0, never negative. */
    double wo[1] = { 999 }; int so[1] = { 1 }; double xo[1];
    assert_int_equal(fx_float_pack(wo, so, 1, 100, 0, xo), FX_OK);
    assert_true(xo[0] >= 0.0);
}

/* Hito 32 (band wrap): two consecutive full-width floats (Slashdot's
 * .grid_24 { width:99.8% }) must STACK -- one per row at x = 0 -- instead of
 * being crammed side by side into one row. */
static void test_float_pack_wrap_full_width_stack(void **state) {
    (void)state;
    double w[3] = { 998.0, 998.0, 998.0 };
    int side[3] = { 0, 0, 0 };
    double x[3];
    size_t row[3];
    assert_int_equal(fx_float_pack_wrap(w, side, 3, 1000.0, 0, x, row), FX_OK);
    for (size_t i = 0; i < 3; ++i) {
        assert_int_equal((int)row[i], (int)i);
        assert_true(dbl_eq(x[i], 0.0));
    }
}

/* When everything fits in one row the wrap variant must agree with v1. */
static void test_float_pack_wrap_fits_matches_v1(void **state) {
    (void)state;
    double w[4] = { 250.0, 250.0, 250.0, 250.0 };
    int side[4] = { 0, 0, 0, 0 };
    double x[4], xv1[4];
    size_t row[4];
    assert_int_equal(fx_float_pack_wrap(w, side, 4, 1000.0, 0, x, row), FX_OK);
    assert_int_equal(fx_float_pack(w, side, 4, 1000.0, 0, xv1), FX_OK);
    for (size_t i = 0; i < 4; ++i) {
        assert_int_equal((int)row[i], 0);
        assert_true(dbl_eq(x[i], xv1[i]));
    }
    /* Left main + right sidebar share row 0 exactly like v1. */
    double w2[2] = { 300.0, 300.0 };
    int side2[2] = { 0, 1 };
    assert_int_equal(fx_float_pack_wrap(w2, side2, 2, 1000.0, 0, x, row), FX_OK);
    assert_int_equal((int)row[0], 0);
    assert_int_equal((int)row[1], 0);
    assert_true(dbl_eq(x[0], 0.0));
    assert_true(dbl_eq(x[1], 700.0));
}

/* Partial fit: the overflowing item opens the next row and packing resumes there. */
static void test_float_pack_wrap_partial(void **state) {
    (void)state;
    double w[3] = { 600.0, 600.0, 300.0 };
    int side[3] = { 0, 0, 0 };
    double x[3];
    size_t row[3];
    assert_int_equal(fx_float_pack_wrap(w, side, 3, 1000.0, 0, x, row), FX_OK);
    assert_int_equal((int)row[0], 0);
    assert_true(dbl_eq(x[0], 0.0));
    assert_int_equal((int)row[1], 1);       /* 600 + 600 > 1000: wraps */
    assert_true(dbl_eq(x[1], 0.0));
    assert_int_equal((int)row[2], 1);       /* 600 + 300 <= 1000: shares row 1 */
    assert_true(dbl_eq(x[2], 600.0));
    /* An item wider than avail alone still lands clamped at x=0 on its own row. */
    double wo[2] = { 1500.0, 100.0 };
    int so[2] = { 0, 0 };
    assert_int_equal(fx_float_pack_wrap(wo, so, 2, 1000.0, 0, x, row), FX_OK);
    assert_int_equal((int)row[0], 0);
    assert_true(dbl_eq(x[0], 0.0));
    assert_int_equal((int)row[1], 1);
    assert_true(dbl_eq(x[1], 0.0));
}

static void test_float_pack_wrap_errors(void **state) {
    (void)state;
    double w[2] = { 10, 10 }; int side[2] = { 0, 0 }; double x[2]; size_t row[2];
    assert_int_equal(fx_float_pack_wrap(NULL, NULL, 0, 100, 0, NULL, NULL), FX_OK);
    assert_int_equal(fx_float_pack_wrap(NULL, side, 2, 100, 0, x, row), FX_ERR_NULL_ARG);
    assert_int_equal(fx_float_pack_wrap(w, side, 2, 100, 0, x, NULL), FX_ERR_NULL_ARG);
    assert_int_equal(fx_float_pack_wrap(w, side, 2, -1, 0, x, row), FX_ERR_RANGE);
}

static void test_justify_name(void **state) {
    (void)state;
    assert_string_equal(fx_justify_name(FX_JUSTIFY_START), "start");
    assert_string_equal(fx_justify_name(FX_JUSTIFY_END), "end");
    assert_string_equal(fx_justify_name(FX_JUSTIFY_CENTER), "center");
    assert_string_equal(fx_justify_name(FX_JUSTIFY_SPACE_BETWEEN), "space-between");
    assert_string_equal(fx_justify_name(FX_JUSTIFY_SPACE_AROUND), "space-around");
    assert_string_equal(fx_justify_name(FX_JUSTIFY_SPACE_EVENLY), "space-evenly");
    assert_string_equal(fx_justify_name((fx_justify)999), "start");
}


/* CSS Flexbox 4.5: the automatic minimum size of a flex item. `min-width:auto` (the
 * initial value) resolves to the item's content-based minimum, NOT to zero -- an
 * overflowing line stops shrinking its items at their min-content width instead of
 * grinding them down to a sliver where every line holds one character. */
static void test_auto_min_size_is_min_content(void **state) {
    (void)state;
    /* Nothing declared: the content-based minimum wins, clamped by the base size. */
    assert_float_equal(fx_auto_min_size(40.0, 300.0, -1.0, 0), 40.0, 1e-9);
    /* A base size SMALLER than min-content clamps it (CSS: the content size
     * suggestion is clamped by the specified size suggestion), so an item the author
     * sized small does not get inflated by a long word. */
    assert_float_equal(fx_auto_min_size(120.0, 50.0, -1.0, 0), 50.0, 1e-9);
    /* An explicit author min-width is not `auto`: it wins outright, in both
     * directions. */
    assert_float_equal(fx_auto_min_size(40.0, 300.0, 90.0, 0), 90.0, 1e-9);
    assert_float_equal(fx_auto_min_size(400.0, 300.0, 10.0, 0), 10.0, 1e-9);
    /* A scroll container (overflow other than visible) has an automatic minimum
     * size of ZERO -- that is what makes the near-universal `min-width:0`/
     * `overflow:hidden` truncation idiom work. */
    assert_float_equal(fx_auto_min_size(400.0, 300.0, -1.0, 1), 0.0, 1e-9);
    /* An explicit min-width still applies inside a scroll container. */
    assert_float_equal(fx_auto_min_size(400.0, 300.0, 25.0, 1), 25.0, 1e-9);
    /* Degenerate/negative inputs never yield a negative minimum. */
    assert_float_equal(fx_auto_min_size(-5.0, -5.0, -1.0, 0), 0.0, 1e-9);
}

/* --- CSS Multi-column Layout 3.4: used column-count / column-width --------- */

/* The whole point of the algorithm is that `column-width` is a MINIMUM, not a
 * fixed width: the number of columns falls out of how many fit, so the same
 * stylesheet gives one column on a narrow viewport and three on a wide one. */
static void test_multicol_used_counts(void **state) {
    (void)state;
    int n; double cw;

    /* Neither declared: not a multi-column container at all. */
    assert_int_equal(fx_multicol_used(1000.0, 0, 0.0, 20.0, &n, &cw), FX_OK);
    assert_int_equal(n, 1);
    assert_true(dbl_eq(cw, 1000.0));

    /* column-count only: N columns sharing the width minus the gaps. */
    assert_int_equal(fx_multicol_used(1000.0, 3, 0.0, 20.0, &n, &cw), FX_OK);
    assert_int_equal(n, 3);
    assert_true(dbl_eq(cw, (1000.0 - 2.0 * 20.0) / 3.0));

    /* column-width only: as many as fit, floor((W+G)/(cw+G)). */
    assert_int_equal(fx_multicol_used(1000.0, 0, 300.0, 20.0, &n, &cw), FX_OK);
    assert_int_equal(n, 3);                       /* (1000+20)/(300+20) = 3.18 */
    assert_true(dbl_eq(cw, (1000.0 - 2.0 * 20.0) / 3.0));

    /* A column-width wider than the container still yields one column. */
    assert_int_equal(fx_multicol_used(300.0, 0, 1000.0, 20.0, &n, &cw), FX_OK);
    assert_int_equal(n, 1);
    assert_true(dbl_eq(cw, 300.0));

    /* Both: the count is a CAP on how many fit. */
    assert_int_equal(fx_multicol_used(1000.0, 2, 300.0, 20.0, &n, &cw), FX_OK);
    assert_int_equal(n, 2);
    assert_int_equal(fx_multicol_used(1000.0, 8, 300.0, 20.0, &n, &cw), FX_OK);
    assert_int_equal(n, 3);                       /* only three fit */

    /* Zero gap is legal and must not divide by anything odd. */
    assert_int_equal(fx_multicol_used(900.0, 3, 0.0, 0.0, &n, &cw), FX_OK);
    assert_int_equal(n, 3);
    assert_true(dbl_eq(cw, 300.0));
}

/* Degenerate inputs never produce a zero/negative column or a division blow-up. */
static void test_multicol_used_edges(void **state) {
    (void)state;
    int n; double cw;

    assert_int_equal(fx_multicol_used(1000.0, 3, 0.0, 20.0, NULL, &cw), FX_ERR_NULL_ARG);
    assert_int_equal(fx_multicol_used(1000.0, 3, 0.0, 20.0, &n, NULL), FX_ERR_NULL_ARG);

    /* Gaps that eat the whole container: the column never goes below 1px. */
    assert_int_equal(fx_multicol_used(50.0, 10, 0.0, 40.0, &n, &cw), FX_OK);
    assert_int_equal(n, 10);
    assert_true(cw >= 1.0);

    /* A zero or negative available width degrades to one full-width column. */
    assert_int_equal(fx_multicol_used(0.0, 3, 0.0, 20.0, &n, &cw), FX_OK);
    assert_int_equal(n, 1);

    /* Negative/absurd author values fail closed to a single column. */
    assert_int_equal(fx_multicol_used(1000.0, -4, 0.0, 20.0, &n, &cw), FX_OK);
    assert_int_equal(n, 1);
    assert_int_equal(fx_multicol_used(1000.0, 0, -300.0, 20.0, &n, &cw), FX_OK);
    assert_int_equal(n, 1);
    /* A negative gap is not a gap. */
    assert_int_equal(fx_multicol_used(1000.0, 2, 0.0, -20.0, &n, &cw), FX_OK);
    assert_int_equal(n, 2);
    assert_true(dbl_eq(cw, 500.0));
}

/* Balancing: rows are distributed so every column is about the same height, and
 * a row is never split (the line is this engine's smallest fragmentation unit). */
static void test_multicol_balance(void **state) {
    (void)state;
    /* Twelve rows of 10px into 3 columns -> 4 rows each, column height 40. */
    double h[12];
    for (int i = 0; i < 12; ++i) h[i] = 10.0;
    int col[12];
    double colh[8];
    int ncol = 3;
    assert_int_equal(fx_multicol_balance(h, 12, ncol, col, colh), FX_OK);
    for (int i = 0; i < 12; ++i) assert_int_equal(col[i], i / 4);
    assert_true(dbl_eq(colh[0], 40.0));
    assert_true(dbl_eq(colh[1], 40.0));
    assert_true(dbl_eq(colh[2], 40.0));

    /* One row far taller than the target still occupies exactly one column
     * slot: an unsplittable row cannot be balanced away. */
    double h2[4] = { 100.0, 10.0, 10.0, 10.0 };
    int col2[4];
    double colh2[8];
    assert_int_equal(fx_multicol_balance(h2, 4, 2, col2, colh2), FX_OK);
    assert_int_equal(col2[0], 0);
    assert_true(colh2[0] >= 100.0);

    /* Fewer rows than columns: no column gets two, none is negative. */
    double h3[2] = { 10.0, 10.0 };
    int col3[2];
    double colh3[8];
    assert_int_equal(fx_multicol_balance(h3, 2, 4, col3, colh3), FX_OK);
    assert_int_equal(col3[0], 0);
    assert_true(col3[1] >= 0 && col3[1] < 4);

    assert_int_equal(fx_multicol_balance(NULL, 2, 2, col3, colh3), FX_ERR_NULL_ARG);
    assert_int_equal(fx_multicol_balance(h3, 2, 0, col3, colh3), FX_ERR_RANGE);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_grow_equal),
        cmocka_unit_test(test_grow_weighted),
        cmocka_unit_test(test_shrink_equal),
        cmocka_unit_test(test_shrink_with_min_clamp),
        cmocka_unit_test(test_gap_start),
        cmocka_unit_test(test_justify_center),
        cmocka_unit_test(test_justify_end),
        cmocka_unit_test(test_justify_space_between),
        cmocka_unit_test(test_justify_space_around),
        cmocka_unit_test(test_justify_space_evenly),
        cmocka_unit_test(test_space_between_single_item_is_start),
        cmocka_unit_test(test_negative_fields_clamped),
        cmocka_unit_test(test_flex_zero_items_is_noop),
        cmocka_unit_test(test_flex_errors),
        cmocka_unit_test(test_grid_columns),
        cmocka_unit_test(test_grid_columns_too_narrow_clamps_to_zero),
        cmocka_unit_test(test_grid_columns_edges),
        cmocka_unit_test(test_grid_cell),
        cmocka_unit_test(test_grid_weighted_fr),
        cmocka_unit_test(test_grid_weighted_fixed_px_reserved_first),
        cmocka_unit_test(test_grid_weighted_all_auto_matches_equal),
        cmocka_unit_test(test_grid_weighted_fixed_overflow_zeroes_fr),
        cmocka_unit_test(test_grid_weighted_errors),
        cmocka_unit_test(test_grid_place_span_basic),
        cmocka_unit_test(test_grid_place_span_wraps_when_it_does_not_fit),
        cmocka_unit_test(test_grid_place_span_clamps_and_defaults),
        cmocka_unit_test(test_grid_place_rowspan),
        cmocka_unit_test(test_float_pack_left),
        cmocka_unit_test(test_float_pack_wrap_full_width_stack),
        cmocka_unit_test(test_float_pack_wrap_fits_matches_v1),
        cmocka_unit_test(test_float_pack_wrap_partial),
        cmocka_unit_test(test_float_pack_wrap_errors),
        cmocka_unit_test(test_float_pack_left_and_right),
        cmocka_unit_test(test_float_pack_two_right),
        cmocka_unit_test(test_float_pack_edges),
        cmocka_unit_test(test_justify_name),
        cmocka_unit_test(test_float_insets_left_overlapping_line),
        cmocka_unit_test(test_float_insets_line_past_bottom_is_full_width),
        cmocka_unit_test(test_float_insets_right),
        cmocka_unit_test(test_float_insets_both_sides_take_the_tightest),
        cmocka_unit_test(test_float_insets_never_starve_the_line),
        cmocka_unit_test(test_float_insets_edges),
        cmocka_unit_test(test_auto_min_size_is_min_content),
        cmocka_unit_test(test_multicol_used_counts),
        cmocka_unit_test(test_multicol_used_edges),
        cmocka_unit_test(test_multicol_balance),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
