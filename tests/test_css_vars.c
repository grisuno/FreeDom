/* test_css_vars -- the custom-property table and var() substitution
 * (spec/css_vars.md). */
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include "css_vars.h"

static int set(cvr_table *t, const char *n, const char *v) {
    return cvr_set(t, n, strlen(n), v, strlen(v));
}

static const char *get(const cvr_table *t, const char *n) {
    return cvr_get(t, n, strlen(n));
}

static void test_set_get_overwrite(void **state) {
    (void)state;
    cvr_table t = { 0 };
    assert_int_equal(set(&t, "--a", "1px"), 1);
    assert_string_equal(get(&t, "--a"), "1px");
    assert_int_equal(set(&t, "--a", "2px"), 1);
    assert_string_equal(get(&t, "--a"), "2px");
    assert_int_equal(cvr_count(&t), 1);
    assert_null(get(&t, "--b"));
    cvr_free(&t);
    cvr_free(&t);
}

static void test_names_are_case_sensitive(void **state) {
    (void)state;
    cvr_table t = { 0 };
    assert_int_equal(set(&t, "--Big", "40px"), 1);
    assert_int_equal(set(&t, "--big", "10px"), 1);
    assert_string_equal(get(&t, "--Big"), "40px");
    assert_string_equal(get(&t, "--big"), "10px");
    cvr_free(&t);
}

static void test_bounds_drop_whole(void **state) {
    (void)state;
    cvr_table t = { 0 };
    char name[CVR_NAME_MAX + 8];
    memset(name, 'x', sizeof name);
    name[0] = '-'; name[1] = '-';
    assert_int_equal(cvr_set(&t, name, CVR_NAME_MAX, "1", 1), 0);
    assert_int_equal(cvr_set(&t, name, CVR_NAME_MAX - 1, "1", 1), 1);
    char *val = (char *)malloc(CVR_VALUE_MAX);
    assert_non_null(val);
    memset(val, 'v', CVR_VALUE_MAX);
    assert_int_equal(cvr_set(&t, "--v", 3, val, CVR_VALUE_MAX), 0);
    assert_int_equal(cvr_set(&t, "--v", 3, val, CVR_VALUE_MAX - 1), 1);
    assert_int_equal(set(&t, "-x", "1"), 0);
    assert_int_equal(set(&t, "--", "1"), 0);
    assert_int_equal(set(&t, "--e", ""), 0);
    free(val);
    cvr_free(&t);
}

static void test_grows_to_thousands(void **state) {
    (void)state;
    cvr_table t = { 0 };
    char n[32], v[32];
    for (int i = 0; i < 5000; ++i) {
        snprintf(n, sizeof n, "--v%d", i);
        snprintf(v, sizeof v, "%d", i);
        assert_int_equal(set(&t, n, v), 1);
    }
    assert_int_equal(cvr_count(&t), 5000);
    assert_string_equal(get(&t, "--v0"), "0");
    assert_string_equal(get(&t, "--v4999"), "4999");
    cvr_reset(&t);
    assert_int_equal(cvr_count(&t), 0);
    assert_null(get(&t, "--v7"));
    assert_int_equal(set(&t, "--v7", "again"), 1);
    assert_string_equal(get(&t, "--v7"), "again");
    cvr_free(&t);
}

static void test_collect_strips_important_and_trims(void **state) {
    (void)state;
    cvr_table t = { 0 };
    const char *s = " --a :  red !important ; x--b:1; --c: 2px 3px ;color:--d";
    cvr_collect_decls(&t, s, 0, strlen(s));
    assert_string_equal(get(&t, "--a"), "red");
    assert_null(get(&t, "--b"));
    assert_string_equal(get(&t, "--c"), "2px 3px");
    assert_null(get(&t, "--d"));
    cvr_free(&t);
}

static void test_collect_keeps_semicolon_inside_url(void **state) {
    (void)state;
    cvr_table t = { 0 };
    const char *s = "--i:url(\"data:a;b\");--j:url(data:c;d);--k:'x;y';--l:1";
    cvr_collect_decls(&t, s, 0, strlen(s));
    assert_string_equal(get(&t, "--i"), "url(\"data:a;b\")");
    assert_string_equal(get(&t, "--j"), "url(data:c;d)");
    assert_string_equal(get(&t, "--k"), "'x;y'");
    assert_string_equal(get(&t, "--l"), "1");
    cvr_free(&t);
}

static void test_resolve_scope_order_and_fallback(void **state) {
    (void)state;
    cvr_table sheet = { 0 }, own = { 0 };
    set(&sheet, "--c", "#111");
    set(&sheet, "--only", "sheet");
    set(&own, "--c", "#222");
    const cvr_scope sc = { &own, &sheet, NULL, NULL };
    char out[64];
    assert_int_equal(cvr_resolve("var(--c) var(--only)", out, sizeof out, &sc), 1);
    assert_string_equal(out, "#222 sheet");
    assert_int_equal(cvr_resolve("var(--nope, rgb(1, 2, 3))", out, sizeof out, &sc), 1);
    assert_string_equal(out, "rgb(1, 2, 3)");
    assert_int_equal(cvr_resolve("var(--nope)", out, sizeof out, &sc), 0);
    assert_int_equal(cvr_resolve("var(--c", out, sizeof out, &sc), 0);
    assert_int_equal(cvr_resolve("var(c)", out, sizeof out, &sc), 0);
    cvr_free(&sheet);
    cvr_free(&own);
}

static void test_resolve_depth_and_cycle(void **state) {
    (void)state;
    cvr_table t = { 0 };
    char n[16], v[32];
    set(&t, "--d0", "ok");
    for (int i = 1; i < CVR_MAX_DEPTH; ++i) {
        snprintf(n, sizeof n, "--d%d", i);
        snprintf(v, sizeof v, "var(--d%d)", i - 1);
        set(&t, n, v);
    }
    const cvr_scope sc = { &t, NULL, NULL, NULL };
    char out[64];
    snprintf(v, sizeof v, "var(--d%d)", CVR_MAX_DEPTH - 1);
    assert_int_equal(cvr_resolve(v, out, sizeof out, &sc), 1);
    assert_string_equal(out, "ok");
    set(&t, "--self", "var(--self)");
    assert_int_equal(cvr_resolve("var(--self)", out, sizeof out, &sc), 0);
    cvr_free(&t);
}

static void test_cycle_takes_fallback(void **state) {
    (void)state;
    /* Wikipedia: `--font-size-medium: var(--font-size-medium, 1rem)` is a cycle,
     * so the property is guaranteed-invalid and a use falls back. */
    cvr_table t = { 0 };
    set(&t, "--m", "var(--m,1rem)");
    const cvr_scope sc = { &t, NULL, NULL, NULL };
    char out[64];
    assert_int_equal(cvr_resolve("calc(var(--m,1rem) + 4px)", out, sizeof out, &sc), 1);
    assert_string_equal(out, "calc(1rem + 4px)");
    cvr_free(&t);
}

static void test_fallback_fanout_is_budgeted(void **state) {
    (void)state;
    /* Both branches retried at every level would be 2^CVR_MAX_DEPTH lookups; the
     * budget ends it. */
    cvr_table t = { 0 };
    set(&t, "--a", "var(--a,var(--a))");
    const cvr_scope sc = { &t, NULL, NULL, NULL };
    char out[64];
    assert_int_equal(cvr_resolve("var(--a)", out, sizeof out, &sc), 0);
    cvr_free(&t);
}

static void test_resolve_overflow_fails(void **state) {
    (void)state;
    cvr_table t = { 0 };
    set(&t, "--a", "0123456789");
    const cvr_scope sc = { &t, NULL, NULL, NULL };
    char out[11];
    assert_int_equal(cvr_resolve("var(--a)", out, sizeof out, &sc), 1);
    assert_int_equal(cvr_resolve("var(--a)x", out, sizeof out, &sc), 0);
    cvr_free(&t);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_set_get_overwrite),
        cmocka_unit_test(test_names_are_case_sensitive),
        cmocka_unit_test(test_bounds_drop_whole),
        cmocka_unit_test(test_grows_to_thousands),
        cmocka_unit_test(test_collect_strips_important_and_trims),
        cmocka_unit_test(test_collect_keeps_semicolon_inside_url),
        cmocka_unit_test(test_resolve_scope_order_and_fallback),
        cmocka_unit_test(test_resolve_depth_and_cycle),
        cmocka_unit_test(test_cycle_takes_fallback),
        cmocka_unit_test(test_fallback_fanout_is_budgeted),
        cmocka_unit_test(test_resolve_overflow_fails),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
