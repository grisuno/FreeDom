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

/* ---- Corpus-measured gaps -------------------------------------------------
 * Every case below is a declaration --dump-css-drops reported on a real page in
 * tests/parity/pages. The assertion is always the same shape: nothing is dropped
 * AND the resolved style carries the value, because "the parser accepted it" and
 * "the engine uses it" are different claims. */

/* Asserts that `text` parses with an empty drop log, and returns the sheet. */
static css_sheet *parse_nodrop(const char *text) {
    css_drop items[16];
    css_drop_log log;
    css_sheet *sh = parse_logged(text, items, 16, &log);
    if (log.total != 0)
        fail_msg("dropped %s: %s (cause %d)", items[0].prop, items[0].val,
                 items[0].cause);
    return sh;
}

/* Given a stylesheet whose bytes start with a UTF-8 BOM, when parsed, then the BOM
 * is not part of the first selector (CSS Syntax 3 3.2 "Decode bytes": a leading
 * U+FEFF is removed). Measured on ddg-results, where `<style>﻿:root{...}` made
 * the selector unrecognisable as root-scoped, so the whole custom-property palette
 * was never collected and 40 var() declarations died as bad values. */
static void test_leading_bom_is_stripped(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("\xEF\xBB\xBF:root{--pal:7px}p{width:var(--pal)}");
    css_style s = css_resolve(sh, "p", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.width, 7);
    css_free(sh);
}

/* Given `transform` with SEVERAL space-separated functions, when parsed, then the
 * list composes (CSS Transforms 1 3: the value is a function list applied in
 * order) instead of rejecting the declaration. jkanime: `translateY(-50%) scale(0)`
 * 11 times, wikipedia `translate(-50%,-50%) scale(1.1)`. */
static void test_transform_function_list_composes(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{transform:translateX(10px) scale(2)}");
    css_style s = css_resolve(sh, "a", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.transform_tx, 10);
    assert_int_equal(s.transform_sx, 200);
    assert_int_equal(s.transform_sy, 200);
    css_free(sh);
}

/* Function names are CSS identifiers and therefore case-insensitive (Syntax 3 4.2).
 * slashdot ships `skewx(1deg) skewy(1deg) translatex(0px)` lower-cased by a minifier. */
static void test_transform_function_names_are_case_insensitive(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{transform:SKEWX(4deg) translatex(3px)}");
    css_style s = css_resolve(sh, "a", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.transform_skx, 4);
    assert_int_equal(s.transform_tx, 3);
    css_free(sh);
}

/* An <angle> is a number plus any of the four CSS units (Values 4 6.1), and the
 * number may be fractional. `rotate(.5turn)` is 180deg. */
static void test_transform_angle_units(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{transform:rotate(.5turn)}");
    css_style s = css_resolve(sh, "a", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.transform_rotate, 180);
    css_free(sh);
}

/* translate3d/translateZ flatten to their 2D projection rather than failing: a 2D
 * engine renders the z component as nothing, which is what the projection says.
 * jkanime uses `translate3d(0,0,0)` as a compositing hint. */
static void test_transform_3d_flattens(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{transform:translate3d(5px,6px,99px)}");
    css_style s = css_resolve(sh, "a", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.transform_tx, 5);
    assert_int_equal(s.transform_ty, 6);
    css_free(sh);
}

/* transform-origin takes two components and each may be a <length-percentage> or a
 * keyword (Transforms 1 5.1). jkanime declares `0 100%` and `50% 0`; both halves
 * were rejected because a bare `0` is not a keyword and not a percent. */
static void test_transform_origin_number_component(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{transform-origin:0 100%}");
    css_free(sh);
}

/* background-size accepts one or two <length-percentage>|auto components
 * (Backgrounds 3 3.9). ddg ships `44px 12px` 11 times, jkanime a calc() pair. */
static void test_background_size_two_lengths(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{background-size:44px 12px}");
    css_style s = css_resolve(sh, "a", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.bg_size_w, 44);
    assert_int_equal(s.bg_size_h, 12);
    css_free(sh);
}

/* background-position takes a percentage pair; `50% 50%` is the centring idiom and
 * was dropped whole. */
static void test_background_position_percentages(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{background-position:50% 50%}");
    css_free(sh);
}

/* The `flex` shorthand's third component is a <'flex-basis'>, and a percentage is a
 * valid one (Flexbox 1 7.1.1). Bootstrap's `flex: 1 1 0%` is on every column. */
static void test_flex_percentage_basis(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{flex:1 1 0%}");
    css_style s = css_resolve(sh, "a", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.flex_grow, 100);
    assert_int_equal(s.flex_shrink, 100);
    css_free(sh);
}

/* vertical-align accepts a <length-percentage> baseline shift, not only keywords
 * (CSS 2.1 10.8.1). jkanime's icon font uses `.255em` seven times. */
static void test_vertical_align_length(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{vertical-align:-2px}");
    css_style s = css_resolve(sh, "a", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.valign_shift, -2);
    css_free(sh);
}

/* A CSS-wide keyword is valid on EVERY property including shorthands (Cascade 5
 * 7.3). `font: inherit`, `padding: inherit` and `border-radius: inherit` all
 * appear in the corpus and all died as bad values. */
static void test_css_wide_keyword_on_shorthand(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{font:inherit;padding:inherit;"
                                 "border-radius:inherit;outline:inherit;"
                                 "border-left:inherit;background:inherit}");
    css_free(sh);
}

/* overflow is a two-value shorthand for overflow-x and overflow-y (Overflow 3 3).
 * wikipedia declares `hidden auto`. */
static void test_overflow_two_values(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{overflow:hidden auto}");
    css_style s = css_resolve(sh, "a", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.overflow_x, CSS_OF_HIDDEN);
    assert_int_equal(s.overflow_y, CSS_OF_AUTO);
    css_free(sh);
}

/* `display: flow-root` establishes a block formatting context and is the modern
 * clearfix (Display 3 2.1). `display: -webkit-box` is the legacy flexbox the
 * -webkit-line-clamp idiom requires, so dropping it dropped the clamp with it. */
static void test_display_flow_root_and_webkit_box(void **state) {
    (void)state;
    css_sheet *a = parse_nodrop("a{display:flow-root}");
    assert_int_equal(css_resolve(a, "a", NULL, NULL, 0, NULL, 0).display,
                     CSS_DISP_BLOCK);
    css_free(a);
    css_sheet *b = parse_nodrop("a{display:-webkit-box}");
    assert_int_equal(css_resolve(b, "a", NULL, NULL, 0, NULL, 0).display,
                     CSS_DISP_FLEX);
    css_free(b);
}

/* The intrinsic sizing keywords are values of the <width> type (Sizing 3 5.1).
 * wikipedia's `width: max-content` is how a navbox sizes to its content. */
static void test_intrinsic_sizing_keywords(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{width:max-content;height:min-content;"
                                 "max-width:fit-content}");
    css_style s = css_resolve(sh, "a", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.width, CSS_LEN_MAX_CONTENT);
    assert_int_equal(s.height, CSS_LEN_MIN_CONTENT);
    css_free(sh);
}

/* A vendor prefix on a VALUE is the same aliasing rule as one on a property:
 * `position: -webkit-sticky` is `position: sticky`. */
static void test_vendor_prefixed_value_keyword(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{position:-webkit-sticky}");
    css_style s = css_resolve(sh, "a", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.position, CSS_POS_STICKY);
    css_free(sh);
}

/* The `font` shorthand's size component may carry a `/line-height` (CSS 2.1 15.7).
 * slashdot's `font: normal 24px/1.5` lost the whole declaration. */
static void test_font_shorthand_with_line_height(void **state) {
    (void)state;
    css_sheet *sh = parse_nodrop("a{font:normal 24px/1.5 serif}");
    css_style s = css_resolve(sh, "a", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.font_abs, 24);
    assert_int_equal(s.line_scale, 150);
    css_free(sh);
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
        cmocka_unit_test(test_leading_bom_is_stripped),
        cmocka_unit_test(test_transform_function_list_composes),
        cmocka_unit_test(test_transform_function_names_are_case_insensitive),
        cmocka_unit_test(test_transform_angle_units),
        cmocka_unit_test(test_transform_3d_flattens),
        cmocka_unit_test(test_transform_origin_number_component),
        cmocka_unit_test(test_background_size_two_lengths),
        cmocka_unit_test(test_background_position_percentages),
        cmocka_unit_test(test_flex_percentage_basis),
        cmocka_unit_test(test_vertical_align_length),
        cmocka_unit_test(test_css_wide_keyword_on_shorthand),
        cmocka_unit_test(test_overflow_two_values),
        cmocka_unit_test(test_display_flow_root_and_webkit_box),
        cmocka_unit_test(test_intrinsic_sizing_keywords),
        cmocka_unit_test(test_vendor_prefixed_value_keyword),
        cmocka_unit_test(test_font_shorthand_with_line_height),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
