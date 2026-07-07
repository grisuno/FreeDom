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
        cmocka_unit_test(test_float_pack_left),
        cmocka_unit_test(test_float_pack_left_and_right),
        cmocka_unit_test(test_float_pack_two_right),
        cmocka_unit_test(test_float_pack_edges),
        cmocka_unit_test(test_justify_name),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
