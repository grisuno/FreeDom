/* Suite for the parser drop log (spec/css_drops.md).
 *
 * The log turns "measure what the parser drops" into an engine measurement instead
 * of a grep over strcmp() call sites: a grep sees property NAMES only, and half the
 * expensive historical gaps were a rejected VALUE on a property that was already
 * implemented (a leading-dot number, a percentage inside a shorthand, `pt`), which
 * drops the whole declaration while showing up in no name-based inventory. */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "css.h"

/* Parses `text` with a drop log backed by `items`, asserting the parse succeeded.
 * Returns the sheet (caller frees). */
static css_sheet *parse_logged(const char *text, css_drop *items, size_t cap,
                               css_drop_log *log) {
    css_sheet *sh = NULL;
    css_drop_log l = { items, cap, 0, 0 };
    css_status st = css_parse_logged(text, strlen(text), NULL, NULL, &sh, &l);
    assert_int_equal(st, CSS_OK);
    *log = l;
    return sh;
}

/* Finds the log entry for `prop`, or NULL. */
static const css_drop *find_drop(const css_drop_log *log, const char *prop) {
    for (size_t i = 0; i < log->n; ++i)
        if (strcmp(log->items[i].prop, prop) == 0) return &log->items[i];
    return NULL;
}

/* Given a rule whose property name is not in the dispatch, when parsed with a log,
 * then it is reported once as an unknown property. */
static void test_unknown_property_is_logged(void **state) {
    (void)state;
    css_drop items[8];
    css_drop_log log;
    css_sheet *sh = parse_logged("a{unknown-prop:1}", items, 8, &log);
    assert_int_equal((int)log.total, 1);
    assert_int_equal((int)log.n, 1);
    assert_string_equal(items[0].prop, "unknown-prop");
    assert_string_equal(items[0].val, "1");
    assert_int_equal(items[0].cause, CSS_DROP_UNKNOWN_PROP);
    assert_int_equal(items[0].count, 1);
    css_free(sh);
}

/* Given an implemented property with a value the grammar rejects, then the cause is
 * BAD_VALUE -- the distinction that matters, because the property "exists" and the
 * declaration is lost anyway. */
static void test_bad_value_is_distinguished(void **state) {
    (void)state;
    css_drop items[8];
    css_drop_log log;
    css_sheet *sh = parse_logged("a{color:definitely-not-a-color}", items, 8, &log);
    assert_int_equal((int)log.total, 1);
    assert_int_equal((int)log.n, 1);
    assert_string_equal(items[0].prop, "color");
    assert_int_equal(items[0].cause, CSS_DROP_BAD_VALUE);
    css_free(sh);
}

/* Given a declaration the parser understands, then nothing is logged. */
static void test_accepted_declaration_is_not_logged(void **state) {
    (void)state;
    css_drop items[8];
    css_drop_log log;
    css_sheet *sh = parse_logged("a{color:red;width:10px}", items, 8, &log);
    assert_int_equal((int)log.total, 0);
    assert_int_equal((int)log.n, 0);
    css_free(sh);
}

/* Given the same unknown property in two rules, then it coalesces into one entry
 * with count 2: a real sheet repeats `-ms-flex-pack` hundreds of times and an
 * un-grouped listing is unreadable. */
static void test_repeats_coalesce_by_property_and_cause(void **state) {
    (void)state;
    css_drop items[8];
    css_drop_log log;
    css_sheet *sh = parse_logged("a{zoom:1}\nb{zoom:2}", items, 8, &log);
    assert_int_equal((int)log.total, 2);
    assert_int_equal((int)log.n, 1);
    assert_int_equal(items[0].count, 2);
    /* The sample value is the FIRST occurrence. */
    assert_string_equal(items[0].val, "1");
    css_free(sh);
}

/* The same property name dropped for two different reasons stays two entries: they
 * need different fixes (implement the property vs widen the value grammar). */
static void test_same_property_two_causes_two_entries(void **state) {
    (void)state;
    css_drop items[8];
    css_drop_log log;
    css_sheet *sh = parse_logged("a{color:bogus-one}b{unknown-x:1}", items, 8, &log);
    assert_int_equal((int)log.n, 2);
    assert_non_null(find_drop(&log, "color"));
    assert_non_null(find_drop(&log, "unknown-x"));
    css_free(sh);
}

/* A custom property is not a property; declaring one is not a drop. */
static void test_custom_property_is_not_a_drop(void **state) {
    (void)state;
    css_drop items[8];
    css_drop_log log;
    css_sheet *sh = parse_logged(":root{--x:1}", items, 8, &log);
    assert_int_equal((int)log.total, 0);
    assert_int_equal((int)log.n, 0);
    css_free(sh);
}

/* With no room in the log, the parse still runs and `total` still counts: the report
 * must never understate the magnitude just because the listing filled up. */
static void test_full_log_still_counts_total(void **state) {
    (void)state;
    css_drop items[1];
    css_drop_log log;
    css_sheet *sh = parse_logged("a{aa:1}b{bb:2}c{cc:3}", items, 1, &log);
    assert_int_equal((int)log.n, 1);
    assert_int_equal((int)log.total, 3);
    css_free(sh);
}

/* items == NULL disables the listing without disabling the count. */
static void test_null_items_disables_listing(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    css_drop_log log = { NULL, 0, 0, 0 };
    const char *t = "a{aa:1}b{bb:2}";
    assert_int_equal(css_parse_logged(t, strlen(t), NULL, NULL, &sh, &log), CSS_OK);
    assert_int_equal((int)log.n, 0);
    assert_int_equal((int)log.total, 2);
    css_free(sh);
}

/* A hostile value is bounded and sanitised: the report goes to a terminal, so an
 * ANSI escape smuggled through a remote stylesheet must not be able to paint it. */
static void test_long_value_truncates_and_control_bytes_are_stripped(void **state) {
    (void)state;
    char text[1024];
    size_t n = 0;
    n += (size_t)snprintf(text + n, sizeof text - n, "a{unknown-y:");
    for (int i = 0; i < 400 && n < sizeof text - 8; ++i) text[n++] = 'x';
    text[n] = '\0';
    n += (size_t)snprintf(text + n, sizeof text - n, "}");

    css_drop items[4];
    css_drop_log log;
    css_sheet *sh = parse_logged(text, items, 4, &log);
    assert_int_equal((int)log.n, 1);
    assert_true(strlen(items[0].val) < CSS_DROP_VAL_MAX);
    assert_non_null(strstr(items[0].val, "..."));
    css_free(sh);

    const char *esc = "a{unknown-z:\033[31mred}";
    css_drop it2[4];
    css_drop_log log2;
    css_sheet *sh2 = parse_logged(esc, it2, 4, &log2);
    assert_int_equal((int)log2.n, 1);
    assert_null(strchr(it2[0].val, '\033'));
    css_free(sh2);
}

/* The log cannot change the render: the resolved style is identical with and
 * without it. This is the invariant that lets the instrument stay compiled in. */
static void test_log_does_not_change_resolution(void **state) {
    (void)state;
    const char *t = "a{color:#112233;unknown-q:9;width:7px}";
    css_sheet *plain = NULL;
    assert_int_equal(css_parse(t, strlen(t), &plain), CSS_OK);

    css_drop items[8];
    css_drop_log log;
    css_sheet *logged = parse_logged(t, items, 8, &log);

    css_style a = css_resolve(plain, "a", NULL, NULL, 0, NULL, 0);
    css_style b = css_resolve(logged, "a", NULL, NULL, 0, NULL, 0);
    assert_int_equal(a.color, b.color);
    assert_int_equal(a.width, b.width);
    assert_int_equal((int)log.n, 1);
    css_free(plain);
    css_free(logged);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_unknown_property_is_logged),
        cmocka_unit_test(test_bad_value_is_distinguished),
        cmocka_unit_test(test_accepted_declaration_is_not_logged),
        cmocka_unit_test(test_repeats_coalesce_by_property_and_cause),
        cmocka_unit_test(test_same_property_two_causes_two_entries),
        cmocka_unit_test(test_custom_property_is_not_a_drop),
        cmocka_unit_test(test_full_log_still_counts_total),
        cmocka_unit_test(test_null_items_disables_listing),
        cmocka_unit_test(test_long_value_truncates_and_control_bytes_are_stripped),
        cmocka_unit_test(test_log_does_not_change_resolution),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
