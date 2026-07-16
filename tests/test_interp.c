/*
 * TDD suite for interp (ip_) — pure CSS interpolation engine.
 * Red until src/interp.c exists. See spec/interp.md.
 *
 * This is Phase R1d of the modern-rendering plan: easing functions,
 * value interpolation, keyframe interpolation, and the animation
 * state machine that tracks elapsed time across iterations/delays.
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <math.h>

#include "interp.h"

/* ------------------------------------------------------------------ */
/*  ip_ease                                                           */
/* ------------------------------------------------------------------ */

static void test_ease_linear(void **state) {
    (void)state;
    ip_ease_fn fn = { .kind = IP_EASE_LINEAR };
    assert_float_equal(ip_ease(0.0, &fn), 0.0, 0.0001);
    assert_float_equal(ip_ease(0.5, &fn), 0.5, 0.0001);
    assert_float_equal(ip_ease(1.0, &fn), 1.0, 0.0001);
}

static void test_ease_endpoints(void **state) {
    (void)state;
    /* All easing functions must map 1→1 (asserted below).
     * 0→0 holds for most, but step-start / steps-start jump at t=0
     * (CSS: first step value is at t=0, not 0). */
    ip_ease_fn fns_always_one[] = {
        { .kind = IP_EASE_LINEAR },
        { .kind = IP_EASE_EASE },
        { .kind = IP_EASE_EASE_IN },
        { .kind = IP_EASE_EASE_OUT },
        { .kind = IP_EASE_EASE_IN_OUT },
        { .kind = IP_EASE_STEP_END, .steps_n = 4 },
        { .kind = IP_EASE_STEPS, .steps_n = 3, .steps_dir = 0 },
        { .kind = IP_EASE_STEPS, .steps_n = 3, .steps_dir = 1 },
        { .kind = IP_EASE_CUBIC_BEZIER, .cx1 = 0.5, .cy1 = 0.0, .cx2 = 0.5, .cy2 = 1.0 },
    };
    for (size_t i = 0; i < sizeof(fns_always_one)/sizeof(fns_always_one[0]); ++i)
        assert_float_equal(ip_ease(1.0, &fns_always_one[i]), 1.0, 0.0001);

    ip_ease_fn fns_0to0[] = {
        { .kind = IP_EASE_LINEAR },
        { .kind = IP_EASE_EASE },
        { .kind = IP_EASE_EASE_IN },
        { .kind = IP_EASE_EASE_OUT },
        { .kind = IP_EASE_EASE_IN_OUT },
        { .kind = IP_EASE_STEP_END, .steps_n = 4 },
        { .kind = IP_EASE_STEPS, .steps_n = 3, .steps_dir = 0 },
        { .kind = IP_EASE_CUBIC_BEZIER, .cx1 = 0.5, .cy1 = 0.0, .cx2 = 0.5, .cy2 = 1.0 },
    };
    for (size_t i = 0; i < sizeof(fns_0to0)/sizeof(fns_0to0[0]); ++i)
        assert_float_equal(ip_ease(0.0, &fns_0to0[i]), 0.0, 0.0001);

    /* step-start: t=0 → 1/n (CSS: first step starts at t=0) */
    assert_float_equal(ip_ease(0.0, &(ip_ease_fn){
        .kind = IP_EASE_STEP_START, .steps_n = 4}), 0.25, 0.0001);
    assert_float_equal(ip_ease(0.0, &(ip_ease_fn){
        .kind = IP_EASE_STEPS, .steps_n = 3, .steps_dir = 1}), 0.3333, 0.0001);

    /* step-start / steps-start at t=1 must still be 1.0 */
    ip_ease_fn fns_start_at_1[] = {
        { .kind = IP_EASE_STEP_START, .steps_n = 4 },
        { .kind = IP_EASE_STEPS, .steps_n = 3, .steps_dir = 1 },
    };
    for (size_t i = 0; i < sizeof(fns_start_at_1)/sizeof(fns_start_at_1[0]); ++i)
        assert_float_equal(ip_ease(1.0, &fns_start_at_1[i]), 1.0, 0.0001);
}

static void test_ease_clamp(void **state) {
    (void)state;
    ip_ease_fn fn = { .kind = IP_EASE_EASE_IN };
    assert_float_equal(ip_ease(-0.5, &fn), 0.0, 0.0001);
    assert_float_equal(ip_ease(2.0, &fn), 1.0, 0.0001);
}

static void test_ease_null_fn(void **state) {
    (void)state;
    assert_float_equal(ip_ease(0.4, NULL), 0.4, 0.0001);
    assert_float_equal(ip_ease(0.0, NULL), 0.0, 0.0001);
    assert_float_equal(ip_ease(1.0, NULL), 1.0, 0.0001);
}

static void test_ease_ease_in_concave(void **state) {
    (void)state;
    ip_ease_fn fn = { .kind = IP_EASE_EASE_IN };
    double v = ip_ease(0.5, &fn);
    assert_true(v > 0.0 && v < 0.5);  /* starts slow, below linear */
}

static void test_ease_ease_out_convex(void **state) {
    (void)state;
    ip_ease_fn fn = { .kind = IP_EASE_EASE_OUT };
    double v = ip_ease(0.5, &fn);
    assert_true(v > 0.5 && v < 1.0);  /* ends fast, above linear */
}

static void test_ease_monotonic(void **state) {
    (void)state;
    ip_ease_fn fns[] = {
        { .kind = IP_EASE_EASE },
        { .kind = IP_EASE_EASE_IN },
        { .kind = IP_EASE_EASE_OUT },
        { .kind = IP_EASE_EASE_IN_OUT },
        { .kind = IP_EASE_CUBIC_BEZIER, .cx1 = 0.42, .cy1 = 0.0, .cx2 = 1.0, .cy2 = 1.0 },
        { .kind = IP_EASE_CUBIC_BEZIER, .cx1 = 0.0, .cy1 = 0.0, .cx2 = 0.58, .cy2 = 1.0 },
    };
    for (size_t fi = 0; fi < sizeof(fns)/sizeof(fns[0]); ++fi) {
        double prev = 0.0;
        for (int i = 0; i <= 100; ++i) {
            double t = i / 100.0;
            double v = ip_ease(t, &fns[fi]);
            assert_true(v >= prev - 0.0001);  /* monotonic: never decreases */
            prev = v;
        }
    }
}

static void test_ease_steps_end(void **state) {
    (void)state;
    ip_ease_fn fn = { .kind = IP_EASE_STEPS, .steps_n = 4, .steps_dir = 0 };
    assert_float_equal(ip_ease(0.0, &fn),  0.0,  0.0001);
    assert_float_equal(ip_ease(0.24, &fn), 0.0,  0.0001);
    assert_float_equal(ip_ease(0.25, &fn), 0.25, 0.0001);
    assert_float_equal(ip_ease(0.49, &fn), 0.25, 0.0001);
    assert_float_equal(ip_ease(0.50, &fn), 0.50, 0.0001);
    assert_float_equal(ip_ease(0.99, &fn), 0.75, 0.0001);
}

static void test_ease_steps_start(void **state) {
    (void)state;
    ip_ease_fn fn = { .kind = IP_EASE_STEPS, .steps_n = 4, .steps_dir = 1 };
    assert_float_equal(ip_ease(0.0, &fn),  0.25, 0.0001);
    assert_float_equal(ip_ease(0.01, &fn), 0.25, 0.0001);
    assert_float_equal(ip_ease(0.25, &fn), 0.50, 0.0001);
    assert_float_equal(ip_ease(0.99, &fn), 1.0,  0.0001);
}

static void test_ease_step_start_end_aliases(void **state) {
    (void)state;
    ip_ease_fn ss = { .kind = IP_EASE_STEP_START, .steps_n = 2 };
    ip_ease_fn se = { .kind = IP_EASE_STEP_END, .steps_n = 2 };
    /* step-start: jump at start */
    assert_float_equal(ip_ease(0.0, &ss), 0.5, 0.0001);
    assert_float_equal(ip_ease(0.4, &ss), 0.5, 0.0001);
    /* step-end: jump at end */
    assert_float_equal(ip_ease(0.0, &se), 0.0, 0.0001);
    assert_float_equal(ip_ease(0.4, &se), 0.0, 0.0001);
}

/* ------------------------------------------------------------------ */
/*  ip_lerp / ip_lerp_color                                          */
/* ------------------------------------------------------------------ */

static void test_lerp_scalar(void **state) {
    (void)state;
    assert_float_equal(ip_lerp(0.0, 100.0, 0.5), 50.0, 0.0001);
    assert_float_equal(ip_lerp(10.0, 20.0, 0.0), 10.0, 0.0001);
    assert_float_equal(ip_lerp(10.0, 20.0, 1.0), 20.0, 0.0001);
    assert_float_equal(ip_lerp(0.0, -100.0, 0.5), -50.0, 0.0001);
}

static void test_lerp_color_rgb(void **state) {
    (void)state;
    /* Red (0xFF0000) → Blue (0x0000FF) at 50% = purple (0x800080) */
    uint32_t got = ip_lerp_color(0xFF0000, 0x0000FF, 0.5);
    assert_int_equal(got, 0x800080);

    /* Black → White at 25% = dark gray */
    got = ip_lerp_color(0x000000, 0xFFFFFF, 0.25);
    assert_int_equal(got, 0x404040);

    /* Same color = identity */
    got = ip_lerp_color(0xAABBCC, 0xAABBCC, 0.3);
    assert_int_equal(got, 0xAABBCC);

    /* t=0 → c1, t=1 → c2 */
    got = ip_lerp_color(0x123456, 0x789ABC, 0.0);
    assert_int_equal(got, 0x123456);
    got = ip_lerp_color(0x123456, 0x789ABC, 1.0);
    assert_int_equal(got, 0x789ABC);
}

static void test_interp_dispatches(void **state) {
    (void)state;
    double v = ip_interp(IP_VAL_SCALAR, 10.0, 20.0, 0.5);
    assert_float_equal(v, 15.0, 0.0001);

    double c = ip_interp(IP_VAL_COLOR, 0xFF0000, 0x0000FF, 0.5);
    assert_int_equal((uint32_t)c, 0x800080);
}

/* ------------------------------------------------------------------ */
/*  ip_kf_interp                                                      */
/* ------------------------------------------------------------------ */

static void test_kf_two_keyframes(void **state) {
    (void)state;
    ip_keyframe kf[] = { {0, 0}, {100, 100} };
    assert_float_equal(ip_kf_interp(IP_VAL_SCALAR, kf, 2, 50.0), 50.0, 0.0001);
    assert_float_equal(ip_kf_interp(IP_VAL_SCALAR, kf, 2, 25.0), 25.0, 0.0001);
}

static void test_kf_three_keyframes(void **state) {
    (void)state;
    ip_keyframe kf[] = { {0, 0}, {50, 200}, {100, 100} };
    assert_float_equal(ip_kf_interp(IP_VAL_SCALAR, kf, 3, 25.0), 100.0, 0.0001);
    assert_float_equal(ip_kf_interp(IP_VAL_SCALAR, kf, 3, 75.0), 150.0, 0.0001);
}

static void test_kf_exact_match(void **state) {
    (void)state;
    ip_keyframe kf[] = { {0, 10}, {50, 60}, {100, 110} };
    assert_float_equal(ip_kf_interp(IP_VAL_SCALAR, kf, 3, 50.0), 60.0, 0.0001);
}

static void test_kf_before_first(void **state) {
    (void)state;
    ip_keyframe kf[] = { {25, 50}, {75, 100} };
    assert_float_equal(ip_kf_interp(IP_VAL_SCALAR, kf, 2, 0.0), 50.0, 0.0001);
}

static void test_kf_after_last(void **state) {
    (void)state;
    ip_keyframe kf[] = { {25, 50}, {75, 100} };
    assert_float_equal(ip_kf_interp(IP_VAL_SCALAR, kf, 2, 100.0), 100.0, 0.0001);
}

static void test_kf_null_or_empty(void **state) {
    (void)state;
    assert_float_equal(ip_kf_interp(IP_VAL_SCALAR, NULL, 0, 50.0), 0.0, 0.0001);
    ip_keyframe kf[] = { {50, 42} };
    /* single keyframe: always returns its value */
    assert_float_equal(ip_kf_interp(IP_VAL_SCALAR, kf, 1, 0.0), 42.0, 0.0001);
    assert_float_equal(ip_kf_interp(IP_VAL_SCALAR, kf, 1, 50.0), 42.0, 0.0001);
    assert_float_equal(ip_kf_interp(IP_VAL_SCALAR, kf, 1, 100.0), 42.0, 0.0001);
}

static void test_kf_color_interp(void **state) {
    (void)state;
    ip_keyframe kf[] = { {0, (double)0xFF0000}, {100, (double)0x0000FF} };
    double v = ip_kf_interp(IP_VAL_COLOR, kf, 2, 50.0);
    assert_int_equal((uint32_t)v, 0x800080);
}

/* ------------------------------------------------------------------ */
/*  ip_anim — state machine                                           */
/* ------------------------------------------------------------------ */

static ip_ease_fn linear_ease(void) {
    ip_ease_fn fn = { .kind = IP_EASE_LINEAR };
    return fn;
}

static void test_anim_delay_no_fill(void **state) {
    (void)state;
    ip_anim a;
    ip_ease_fn e = linear_ease();
    ip_keyframe kf[] = { {0, 0}, {100, 100} };
    ip_anim_init(&a, IP_VAL_SCALAR, &e, kf, 2, 1000.0, 500.0, 1,
                 IP_DIR_NORMAL, IP_FILL_NONE);

    /* During delay, no change, value is 0 */
    int changed = ip_anim_tick(&a, 200.0);
    assert_int_equal(changed, 0);
    assert_float_equal(ip_anim_current(&a), 0.0, 0.0001);
    assert_int_equal(ip_anim_done(&a), 0);
}

static void test_anim_delay_backwards_fill(void **state) {
    (void)state;
    ip_anim a;
    ip_ease_fn e = linear_ease();
    ip_keyframe kf[] = { {0, 10}, {100, 100} };
    ip_anim_init(&a, IP_VAL_SCALAR, &e, kf, 2, 1000.0, 500.0, 1,
                 IP_DIR_NORMAL, IP_FILL_BACKWARDS);

    int changed = ip_anim_tick(&a, 200.0);
    /* Backwards fill: value = kf[0].val during delay */
    assert_int_equal(changed, 1);
    assert_float_equal(ip_anim_current(&a), 10.0, 0.0001);
}

static void test_anim_active_linear(void **state) {
    (void)state;
    ip_anim a;
    ip_ease_fn e = linear_ease();
    ip_keyframe kf[] = { {0, 0}, {100, 100} };
    ip_anim_init(&a, IP_VAL_SCALAR, &e, kf, 2, 1000.0, 0.0, 1,
                 IP_DIR_NORMAL, IP_FILL_NONE);

    int changed = ip_anim_tick(&a, 250.0);
    assert_int_equal(changed, 1);
    assert_float_equal(ip_anim_current(&a), 25.0, 0.0001);
    assert_int_equal(ip_anim_done(&a), 0);

    /* Finish */
    ip_anim_tick(&a, 750.0);
    assert_float_equal(ip_anim_current(&a), 100.0, 0.0001);
}

static void test_anim_single_iteration_done(void **state) {
    (void)state;
    ip_anim a;
    ip_ease_fn e = linear_ease();
    ip_keyframe kf[] = { {0, 0}, {100, 100} };
    ip_anim_init(&a, IP_VAL_SCALAR, &e, kf, 2, 1000.0, 0.0, 1,
                 IP_DIR_NORMAL, IP_FILL_NONE);

    ip_anim_tick(&a, 1500.0);
    assert_int_equal(ip_anim_done(&a), 1);
    /* done() = 1 tells caller to stop painting. current() returns
     * the stored end value for this boundary frame. */
    assert_float_equal(ip_anim_current(&a), 100.0, 0.0001);
}

static void test_anim_forwards_fill(void **state) {
    (void)state;
    ip_anim a;
    ip_ease_fn e = linear_ease();
    ip_keyframe kf[] = { {0, 0}, {100, 100} };
    ip_anim_init(&a, IP_VAL_SCALAR, &e, kf, 2, 1000.0, 0.0, 1,
                 IP_DIR_NORMAL, IP_FILL_FORWARDS);

    ip_anim_tick(&a, 1500.0);
    assert_int_equal(ip_anim_done(&a), 0);  /* fill forwards: not "done" in display sense */
    assert_float_equal(ip_anim_current(&a), 100.0, 0.0001);  /* stuck at last kf */
}

static void test_anim_two_iterations(void **state) {
    (void)state;
    ip_anim a;
    ip_ease_fn e = linear_ease();
    ip_keyframe kf[] = { {0, 0}, {100, 100} };
    ip_anim_init(&a, IP_VAL_SCALAR, &e, kf, 2, 1000.0, 0.0, 2,
                 IP_DIR_NORMAL, IP_FILL_NONE);

    /* Iteration 1: 0→100, after 250ms → value 25 */
    ip_anim_tick(&a, 250.0);
    assert_int_equal(ip_anim_done(&a), 0);
    assert_float_equal(ip_anim_current(&a), 25.0, 0.0001);

    /* At exactly 1000ms: boundary between iter 0 and iter 1. */
    ip_anim_tick(&a, 750.0);
    assert_int_equal(ip_anim_done(&a), 0);
    /* Boundary: fmod(0, 1000)=0, iter=1 → use prev-iter end value = 100 */
    assert_float_equal(ip_anim_current(&a), 100.0, 0.0001);

    /* Iteration 2: 0→50 at 250ms in */
    ip_anim_tick(&a, 250.0);
    assert_float_equal(ip_anim_current(&a), 25.0, 0.0001);

    /* Finish both iterations */
    ip_anim_tick(&a, 750.0);
    assert_int_equal(ip_anim_done(&a), 1);
    assert_float_equal(ip_anim_current(&a), 100.0, 0.0001);
}

static void test_anim_infinite(void **state) {
    (void)state;
    ip_anim a;
    ip_ease_fn e = linear_ease();
    ip_keyframe kf[] = { {0, 0}, {100, 100} };
    ip_anim_init(&a, IP_VAL_SCALAR, &e, kf, 2, 1000.0, 0.0, IP_ITERATION_INFINITE,
                 IP_DIR_NORMAL, IP_FILL_NONE);

    /* After many iterations, never done */
    ip_anim_tick(&a, 999999.0);
    assert_int_equal(ip_anim_done(&a), 0);
}

static void test_anim_reverse_direction(void **state) {
    (void)state;
    ip_anim a;
    ip_ease_fn e = linear_ease();
    ip_keyframe kf[] = { {0, 0}, {100, 100} };
    ip_anim_init(&a, IP_VAL_SCALAR, &e, kf, 2, 1000.0, 0.0, 1,
                 IP_DIR_REVERSE, IP_FILL_NONE);

    ip_anim_tick(&a, 250.0);
    /* Reverse: starts at end, goes to start. t=0.25 → 100*(1-0.25)=75 */
    assert_float_equal(ip_anim_current(&a), 75.0, 0.0001);
}

static void test_anim_alternate(void **state) {
    (void)state;
    ip_anim a;
    ip_ease_fn e = linear_ease();
    ip_keyframe kf[] = { {0, 0}, {100, 100} };
    ip_anim_init(&a, IP_VAL_SCALAR, &e, kf, 2, 1000.0, 0.0, 2,
                 IP_DIR_ALTERNATE, IP_FILL_NONE);

    /* Iter 1: normal, 0→100 at t=250 */
    ip_anim_tick(&a, 250.0);
    assert_float_equal(ip_anim_current(&a), 25.0, 0.0001);

    /* Iter 2: reverse, starts at frame end (100) going down */
    ip_anim_tick(&a, 750.0 + 250.0);  /* finish iter1 + 250ms of iter2 */
    assert_float_equal(ip_anim_current(&a), 75.0, 0.0001);  /* 100*(1-0.25)=75 */
}

static void test_anim_alternate_reverse(void **state) {
    (void)state;
    ip_anim a;
    ip_ease_fn e = linear_ease();
    ip_keyframe kf[] = { {0, 0}, {100, 100} };
    ip_anim_init(&a, IP_VAL_SCALAR, &e, kf, 2, 1000.0, 0.0, 1,
                 IP_DIR_ALTERNATE_REVERSE, IP_FILL_NONE);

    /* First iteration is reverse */
    ip_anim_tick(&a, 250.0);
    assert_float_equal(ip_anim_current(&a), 75.0, 0.0001);
}

static void test_anim_zero_duration(void **state) {
    (void)state;
    ip_anim a;
    ip_ease_fn e = linear_ease();
    ip_keyframe kf[] = { {0, 10}, {100, 20} };
    ip_anim_init(&a, IP_VAL_SCALAR, &e, kf, 2, 0.0, 0.0, 1,
                 IP_DIR_NORMAL, IP_FILL_NONE);

    /* Zero duration: defensive → treat as 1ms */
    ip_anim_tick(&a, 1.0);
    assert_float_equal(ip_anim_current(&a), 20.0, 0.0001);  /* completed */
}

static void test_anim_no_keyframes(void **state) {
    (void)state;
    ip_anim a;
    ip_ease_fn e = linear_ease();
    ip_anim_init(&a, IP_VAL_SCALAR, &e, NULL, 0, 1000.0, 0.0, 1,
                 IP_DIR_NORMAL, IP_FILL_NONE);

    ip_anim_tick(&a, 500.0);
    assert_float_equal(ip_anim_current(&a), 0.0, 0.0001);
    assert_int_equal(ip_anim_done(&a), 1);
}

static void test_anim_negative_dt(void **state) {
    (void)state;
    ip_anim a;
    ip_ease_fn e = linear_ease();
    ip_keyframe kf[] = { {0, 0}, {100, 100} };
    ip_anim_init(&a, IP_VAL_SCALAR, &e, kf, 2, 1000.0, 0.0, 1,
                 IP_DIR_NORMAL, IP_FILL_NONE);

    ip_anim_tick(&a, 250.0);
    /* Negative dt must not go backwards — ignored */
    ip_anim_tick(&a, -500.0);
    assert_float_equal(ip_anim_current(&a), 25.0, 0.0001);
    assert_int_equal(ip_anim_done(&a), 0);
}

static void test_anim_null_init(void **state) {
    (void)state;
    /* NULL anim must not crash */
    ip_anim_init(NULL, IP_VAL_SCALAR, NULL, NULL, 0, 0, 0, 0, 0, 0);
    ip_anim_tick(NULL, 100.0);
    assert_float_equal(ip_anim_current(NULL), 0.0, 0.0001);
    assert_int_equal(ip_anim_done(NULL), 1);
}

/* ------------------------------------------------------------------ */

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_ease_linear),
        cmocka_unit_test(test_ease_endpoints),
        cmocka_unit_test(test_ease_clamp),
        cmocka_unit_test(test_ease_null_fn),
        cmocka_unit_test(test_ease_ease_in_concave),
        cmocka_unit_test(test_ease_ease_out_convex),
        cmocka_unit_test(test_ease_monotonic),
        cmocka_unit_test(test_ease_steps_end),
        cmocka_unit_test(test_ease_steps_start),
        cmocka_unit_test(test_ease_step_start_end_aliases),
        cmocka_unit_test(test_lerp_scalar),
        cmocka_unit_test(test_lerp_color_rgb),
        cmocka_unit_test(test_interp_dispatches),
        cmocka_unit_test(test_kf_two_keyframes),
        cmocka_unit_test(test_kf_three_keyframes),
        cmocka_unit_test(test_kf_exact_match),
        cmocka_unit_test(test_kf_before_first),
        cmocka_unit_test(test_kf_after_last),
        cmocka_unit_test(test_kf_null_or_empty),
        cmocka_unit_test(test_kf_color_interp),
        cmocka_unit_test(test_anim_delay_no_fill),
        cmocka_unit_test(test_anim_delay_backwards_fill),
        cmocka_unit_test(test_anim_active_linear),
        cmocka_unit_test(test_anim_single_iteration_done),
        cmocka_unit_test(test_anim_forwards_fill),
        cmocka_unit_test(test_anim_two_iterations),
        cmocka_unit_test(test_anim_infinite),
        cmocka_unit_test(test_anim_reverse_direction),
        cmocka_unit_test(test_anim_alternate),
        cmocka_unit_test(test_anim_alternate_reverse),
        cmocka_unit_test(test_anim_zero_duration),
        cmocka_unit_test(test_anim_no_keyframes),
        cmocka_unit_test(test_anim_negative_dt),
        cmocka_unit_test(test_anim_null_init),
    };
    return cmocka_run_group_tests_name("interp", tests, NULL, NULL);
}
