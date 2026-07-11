/*
 * test_js_policy — CMocka suite for the pure js_policy module.
 *
 * Covers the decision matrix (off/allowlist/on x host listed/not) and the
 * CLI/env mode parser, including the fail-closed defaults.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "js_policy.h"

static void test_enabled_matrix(void **state) {
    (void)state;
    /* OFF: never, regardless of allowlist membership. */
    assert_false(jsp_enabled(JSP_OFF, 0));
    assert_false(jsp_enabled(JSP_OFF, 1));
    /* ALLOWLIST: only when the host is listed. */
    assert_false(jsp_enabled(JSP_ALLOWLIST, 0));
    assert_true(jsp_enabled(JSP_ALLOWLIST, 1));
    /* ON: always. */
    assert_true(jsp_enabled(JSP_ON, 0));
    assert_true(jsp_enabled(JSP_ON, 1));
}

static void test_enabled_fail_closed_on_bad_mode(void **state) {
    (void)state;
    assert_false(jsp_enabled((jsp_mode)999, 1));
}

static void test_mode_from_str(void **state) {
    (void)state;
    assert_int_equal(jsp_mode_from_str("off"), JSP_OFF);
    assert_int_equal(jsp_mode_from_str("OFF"), JSP_OFF);
    assert_int_equal(jsp_mode_from_str("0"), JSP_OFF);
    assert_int_equal(jsp_mode_from_str("none"), JSP_OFF);
    assert_int_equal(jsp_mode_from_str("on"), JSP_ON);
    assert_int_equal(jsp_mode_from_str("ON"), JSP_ON);
    assert_int_equal(jsp_mode_from_str("1"), JSP_ON);
    assert_int_equal(jsp_mode_from_str("all"), JSP_ON);
    assert_int_equal(jsp_mode_from_str("allowlist"), JSP_ALLOWLIST);
    assert_int_equal(jsp_mode_from_str("list"), JSP_ALLOWLIST);
    /* NULL and unknown both fall back to the conservative default. */
    assert_int_equal(jsp_mode_from_str(NULL), JSP_ALLOWLIST);
    assert_int_equal(jsp_mode_from_str("wat"), JSP_ALLOWLIST);
}

static void test_mode_str_roundtrip(void **state) {
    (void)state;
    assert_string_equal(jsp_mode_str(JSP_OFF), "off");
    assert_string_equal(jsp_mode_str(JSP_ALLOWLIST), "allowlist");
    assert_string_equal(jsp_mode_str(JSP_ON), "on");
    assert_string_equal(jsp_mode_str((jsp_mode)999), "off");
    /* str -> mode -> str is stable for each canonical name. */
    assert_int_equal(jsp_mode_from_str(jsp_mode_str(JSP_OFF)), JSP_OFF);
    assert_int_equal(jsp_mode_from_str(jsp_mode_str(JSP_ALLOWLIST)), JSP_ALLOWLIST);
    assert_int_equal(jsp_mode_from_str(jsp_mode_str(JSP_ON)), JSP_ON);
}

/* Hito 28: a host is TRUSTED (full author CSS + images, on top of full JS) only
 * when the user declared it twice: JS enabled for it AND explicitly on allow.conf.
 * Either signal alone must fail closed. */
static void test_trusted_requires_both_signals(void **state) {
    (void)state;
    assert_true(jsp_trusted(true, 1));
    assert_false(jsp_trusted(true, 0));  /* JS on (e.g. global JSP_ON) but not allowlisted */
    assert_false(jsp_trusted(false, 1)); /* allowlisted but JS off for this host */
    assert_false(jsp_trusted(false, 0));
    /* Any nonzero allowlist membership value counts as listed (hostblock returns
     * truthy ints, not strictly 1). */
    assert_true(jsp_trusted(true, 42));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_enabled_matrix),
        cmocka_unit_test(test_enabled_fail_closed_on_bad_mode),
        cmocka_unit_test(test_mode_from_str),
        cmocka_unit_test(test_mode_str_roundtrip),
        cmocka_unit_test(test_trusted_requires_both_signals),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
