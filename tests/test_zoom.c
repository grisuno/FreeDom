/*
 * test_zoom — CMocka suite for the pure page-zoom arithmetic.
 *
 * Covers clamping bounds, ladder stepping (snap, monotonicity, idempotent ends),
 * reset, the scale factor and the floored apply.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>

#include "zoom.h"

static void test_clamp_bounds(void **state) {
    (void)state;
    assert_int_equal(zm_clamp(100), 100);
    assert_int_equal(zm_clamp(0), ZM_MIN_PCT);
    assert_int_equal(zm_clamp(-50), ZM_MIN_PCT);
    assert_int_equal(zm_clamp(10000), ZM_MAX_PCT);
    assert_int_equal(zm_clamp(ZM_MIN_PCT), ZM_MIN_PCT);
    assert_int_equal(zm_clamp(ZM_MAX_PCT), ZM_MAX_PCT);
}

static void test_reset_is_default(void **state) {
    (void)state;
    assert_int_equal(zm_reset(), ZM_DEFAULT_PCT);
    assert_int_equal(zm_reset(), 100);
}

static void test_zoom_in_steps_ladder(void **state) {
    (void)state;
    assert_int_equal(zm_zoom_in(100), 110);
    assert_int_equal(zm_zoom_in(110), 125);
    assert_int_equal(zm_zoom_in(90), 100);
    assert_int_equal(zm_zoom_in(50), 67);
}

static void test_zoom_out_steps_ladder(void **state) {
    (void)state;
    assert_int_equal(zm_zoom_out(100), 90);
    assert_int_equal(zm_zoom_out(110), 100);
    assert_int_equal(zm_zoom_out(125), 110);
    assert_int_equal(zm_zoom_out(300), 250);
}

static void test_step_snaps_off_ladder(void **state) {
    (void)state;
    /* 105 is between 100 and 110: one step lands on the next stop each way. */
    assert_int_equal(zm_zoom_in(105), 110);
    assert_int_equal(zm_zoom_out(105), 100);
    /* below the bottom / above the top clamp first, then step. */
    assert_int_equal(zm_zoom_in(10), 67);   /* clamp(10)=50 -> next is 67 */
    assert_int_equal(zm_zoom_out(9999), 250); /* clamp=300 -> prev is 250 */
}

static void test_ends_are_idempotent(void **state) {
    (void)state;
    assert_int_equal(zm_zoom_in(ZM_MAX_PCT), ZM_MAX_PCT);
    assert_int_equal(zm_zoom_out(ZM_MIN_PCT), ZM_MIN_PCT);
    assert_int_equal(zm_zoom_in(400), ZM_MAX_PCT);
    assert_int_equal(zm_zoom_out(10), ZM_MIN_PCT);
}

static void test_repeated_in_reaches_max(void **state) {
    (void)state;
    int pct = ZM_MIN_PCT, prev = -1;
    for (int i = 0; i < 100; ++i) {
        assert_true(pct >= prev);          /* non-decreasing */
        prev = pct;
        pct = zm_zoom_in(pct);
        assert_true(pct >= ZM_MIN_PCT && pct <= ZM_MAX_PCT);
    }
    assert_int_equal(pct, ZM_MAX_PCT);
}

static void test_repeated_out_reaches_min(void **state) {
    (void)state;
    int pct = ZM_MAX_PCT, prev = ZM_MAX_PCT + 1;
    for (int i = 0; i < 100; ++i) {
        assert_true(pct <= prev);          /* non-increasing */
        prev = pct;
        pct = zm_zoom_out(pct);
        assert_true(pct >= ZM_MIN_PCT && pct <= ZM_MAX_PCT);
    }
    assert_int_equal(pct, ZM_MIN_PCT);
}

static void test_scale_factor(void **state) {
    (void)state;
    assert_true(zm_scale(100) == 1.0);
    assert_true(zm_scale(50) == 0.5);
    assert_true(zm_scale(200) == 2.0);
    assert_true(zm_scale(0) == 0.5);       /* clamps first */
    assert_true(zm_scale(10000) == 3.0);
}

static void test_apply_scales_and_floors(void **state) {
    (void)state;
    assert_true(zm_apply(14.0, 100) == 14.0);
    assert_true(zm_apply(14.0, 200) == 28.0);
    assert_true(zm_apply(14.0, 50) == 7.0);
    /* floor: a tiny base at min zoom never drops below 1px when positive. */
    assert_true(zm_apply(1.0, 50) == 1.0);
    assert_true(zm_apply(0.5, 50) == 1.0);
    /* non-positive base is returned scaled, unfloored. */
    assert_true(zm_apply(0.0, 100) == 0.0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_clamp_bounds),
        cmocka_unit_test(test_reset_is_default),
        cmocka_unit_test(test_zoom_in_steps_ladder),
        cmocka_unit_test(test_zoom_out_steps_ladder),
        cmocka_unit_test(test_step_snaps_off_ladder),
        cmocka_unit_test(test_ends_are_idempotent),
        cmocka_unit_test(test_repeated_in_reaches_max),
        cmocka_unit_test(test_repeated_out_reaches_min),
        cmocka_unit_test(test_scale_factor),
        cmocka_unit_test(test_apply_scales_and_floors),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
