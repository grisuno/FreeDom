/* Tests for smooth_scroll (spec/smooth_scroll.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <math.h>
#include <cmocka.h>

#include "smooth_scroll.h"

static void test_ease_out_curve(void **state) {
    (void)state;
    sms_state s;
    sms_init(&s, 0.0);
    assert_false(sms_active(&s));
    sms_retarget(&s, 300.0, 1000.0, 150.0);
    assert_true(sms_active(&s));
    assert_true(sms_goal(&s) == 300.0);
    assert_true(sms_sample(&s, 1000.0) == 0.0);
    assert_true(fabs(sms_sample(&s, 1075.0) - 262.5) < 1e-9);
    assert_true(sms_active(&s));
    assert_true(sms_sample(&s, 1150.0) == 300.0);
    assert_false(sms_active(&s));
    assert_true(sms_sample(&s, 5000.0) == 300.0);
}

static void test_retarget_accumulates_and_is_continuous(void **state) {
    (void)state;
    sms_state s;
    sms_init(&s, 0.0);
    sms_retarget(&s, 100.0, 0.0, 150.0);
    double mid = sms_sample(&s, 75.0);
    assert_true(mid > 0.0 && mid < 100.0);
    sms_retarget(&s, sms_goal(&s) + 100.0, 75.0, 150.0);
    assert_true(sms_goal(&s) == 200.0);
    assert_true(sms_sample(&s, 75.0) == mid);
    assert_true(sms_sample(&s, 225.0) == 200.0);
}

static void test_upward_monotone_no_overshoot(void **state) {
    (void)state;
    sms_state s;
    sms_init(&s, 500.0);
    sms_retarget(&s, 120.0, 10.0, 150.0);
    double prev = 500.0;
    for (int t = 10; t <= 200; t += 3) {
        double p = sms_sample(&s, (double)t);
        assert_true(p <= prev && p >= 120.0);
        prev = p;
    }
    assert_true(prev == 120.0);
}

static void test_zero_duration_and_same_target_jump(void **state) {
    (void)state;
    sms_state s;
    sms_init(&s, 40.0);
    sms_retarget(&s, 90.0, 0.0, 0.0);
    assert_false(sms_active(&s));
    assert_true(sms_sample(&s, 1.0) == 90.0);
    sms_retarget(&s, 90.0, 5.0, 150.0);
    assert_false(sms_active(&s));
    sms_retarget(&s, 10.0, 0.0, NAN);
    assert_true(sms_sample(&s, 0.0) == 10.0);
}

static void test_clock_backwards_and_jump(void **state) {
    (void)state;
    sms_state s;
    sms_init(&s, 0.0);
    sms_retarget(&s, 50.0, 100.0, 150.0);
    assert_true(sms_sample(&s, 20.0) == 0.0);
    sms_jump(&s, 7.0);
    assert_false(sms_active(&s));
    assert_true(sms_goal(&s) == 7.0);
    assert_true(sms_sample(&s, 1000.0) == 7.0);
}

static void test_non_finite_inputs_ignored(void **state) {
    (void)state;
    sms_state s;
    sms_init(&s, 33.0);
    sms_retarget(&s, NAN, 0.0, 150.0);
    sms_retarget(&s, INFINITY, 0.0, 150.0);
    sms_retarget(&s, 10.0, NAN, 150.0);
    sms_jump(&s, -INFINITY);
    assert_false(sms_active(&s));
    assert_true(sms_goal(&s) == 33.0);
    sms_retarget(&s, 66.0, 0.0, 150.0);
    assert_true(isfinite(sms_sample(&s, NAN)));
    sms_init(NULL, 1.0);
    sms_jump(NULL, 1.0);
    sms_retarget(NULL, 1.0, 0.0, 1.0);
    assert_true(sms_sample(NULL, 0.0) == 0.0);
    assert_true(sms_goal(NULL) == 0.0);
    assert_false(sms_active(NULL));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_ease_out_curve),
        cmocka_unit_test(test_retarget_accumulates_and_is_continuous),
        cmocka_unit_test(test_upward_monotone_no_overshoot),
        cmocka_unit_test(test_zero_duration_and_same_target_jump),
        cmocka_unit_test(test_clock_backwards_and_jump),
        cmocka_unit_test(test_non_finite_inputs_ignored),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
