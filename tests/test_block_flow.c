/*
 * test_block_flow — CMocka suite for vertical margin collapsing (CSS 2.1 §8.3.1).
 *
 * The suite is written against the rule as the spec states it, not against the
 * `max(a, b)` shortcut the layout engine used to inline: every negative-margin
 * case below is one the shortcut gets wrong, and `margin-top: -1px` to overlap
 * adjacent borders is commonplace markup, so those rows are the point of the
 * module. Also covers the non-finite fail-closed edges and bf_margins_adjoin.
 */

#include <math.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>

#include "block_flow.h"

static int dbl_eq(double a, double b) {
    double d = a - b;
    return d < 1e-9 && d > -1e-9;
}

/* Two positive margins collapse to the LARGER, never to their sum: this is the
 * whole reason a paragraph's 1em bottom and the next one's 1em top produce 1em
 * of space and not 2em. */
static void test_two_positive_collapse_to_max(void **state) {
    (void)state;
    assert_true(dbl_eq(bf_collapse(30.0, 0.0), 30.0));
    assert_true(dbl_eq(bf_collapse(0.0, 40.0), 40.0));
    assert_true(dbl_eq(bf_collapse(30.0, 40.0), 40.0));
    assert_true(dbl_eq(bf_collapse(25.0, 25.0), 25.0));
    assert_true(dbl_eq(bf_collapse(0.0, 0.0), 0.0));
}

/* A positive and a negative margin: the negative is DEDUCTED from the positive.
 * max(a, b) would answer 30 here, which is why the shortcut had to go. */
static void test_positive_and_negative_are_summed(void **state) {
    (void)state;
    assert_true(dbl_eq(bf_collapse(30.0, -10.0), 20.0));
    assert_true(dbl_eq(bf_collapse(-10.0, 30.0), 20.0));
    /* A negative that outweighs the positive pulls the next block UP. */
    assert_true(dbl_eq(bf_collapse(10.0, -30.0), -20.0));
}

/* Two negatives: the most negative wins (max of absolute values, deducted).
 * max(a, b) answers -10 here; the rule answers -30. */
static void test_two_negative_take_the_most_negative(void **state) {
    (void)state;
    assert_true(dbl_eq(bf_collapse(-10.0, -30.0), -30.0));
    assert_true(dbl_eq(bf_collapse(-30.0, -10.0), -30.0));
    assert_true(dbl_eq(bf_collapse(-10.0, 0.0), -10.0));
}

/* A non-finite margin is ABSENT, not propagated: a hostile calc() that divides by
 * zero must not poison the geometry of everything below it. */
static void test_non_finite_is_absent(void **state) {
    (void)state;
    assert_true(dbl_eq(bf_collapse(30.0, NAN), 30.0));
    assert_true(dbl_eq(bf_collapse(NAN, 30.0), 30.0));
    assert_true(dbl_eq(bf_collapse(NAN, NAN), 0.0));
    assert_true(dbl_eq(bf_collapse(30.0, INFINITY), 30.0));
    assert_true(dbl_eq(bf_collapse(-INFINITY, -10.0), -10.0));
}

/* The n-ary form is the same rule and agrees with the binary one, so a caller can
 * collapse a chain of empty boxes in one call without changing the answer. */
static void test_collapse_n_matches_binary(void **state) {
    (void)state;
    double pair[2] = { 30.0, -10.0 };
    assert_true(dbl_eq(bf_collapse_n(pair, 2), bf_collapse(30.0, -10.0)));

    double chain[4] = { 10.0, 30.0, -5.0, -20.0 };
    /* max positive 30, most negative -20 => 10. */
    assert_true(dbl_eq(bf_collapse_n(chain, 4), 10.0));

    double all_neg[3] = { -1.0, -7.0, -3.0 };
    assert_true(dbl_eq(bf_collapse_n(all_neg, 3), -7.0));
}

/* Degenerate inputs answer 0, never read memory they were not given. */
static void test_collapse_n_edges(void **state) {
    (void)state;
    double one = 42.0;
    assert_true(dbl_eq(bf_collapse_n(NULL, 0), 0.0));
    assert_true(dbl_eq(bf_collapse_n(NULL, 8), 0.0));
    assert_true(dbl_eq(bf_collapse_n(&one, 0), 0.0));
    assert_true(dbl_eq(bf_collapse_n(&one, 1), 42.0));
}

/* Margins adjoin only when NOTHING separates them; any border or padding stops the
 * collapse. Non-finite fails closed to "does not collapse". */
static void test_margins_adjoin(void **state) {
    (void)state;
    assert_int_equal(bf_margins_adjoin(0.0, 0.0), 1);
    assert_int_equal(bf_margins_adjoin(1.0, 0.0), 0);
    assert_int_equal(bf_margins_adjoin(0.0, 1.0), 0);
    assert_int_equal(bf_margins_adjoin(1.0, 1.0), 0);
    assert_int_equal(bf_margins_adjoin(NAN, 0.0), 0);
    assert_int_equal(bf_margins_adjoin(0.0, INFINITY), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_two_positive_collapse_to_max),
        cmocka_unit_test(test_positive_and_negative_are_summed),
        cmocka_unit_test(test_two_negative_take_the_most_negative),
        cmocka_unit_test(test_non_finite_is_absent),
        cmocka_unit_test(test_collapse_n_matches_binary),
        cmocka_unit_test(test_collapse_n_edges),
        cmocka_unit_test(test_margins_adjoin),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
