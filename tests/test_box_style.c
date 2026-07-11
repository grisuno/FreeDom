/*
 * test_box_style — CMocka suite for the pure user-agent box model.
 *
 * Covers the per-tag defaults (block/inline/inline-block/list-item/none, the
 * heading ladder, ul/ol padding, blockquote, hr, the zero-margin body), the
 * neutral fallback for unknown/NULL tags, case-insensitivity, the display-keyword
 * parser (every keyword, the inline-* aliases, trimming, fail-closed edges) and
 * the display-name helper.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "box_style.h"

/* em values are doubles; compare with a small tolerance. */
static int dbl_eq(double a, double b) {
    double d = a - b;
    return d < 1e-9 && d > -1e-9;
}

static void assert_edges(bx_edges e, double t, double r, double b, double l) {
    assert_true(dbl_eq(e.top, t));
    assert_true(dbl_eq(e.right, r));
    assert_true(dbl_eq(e.bottom, b));
    assert_true(dbl_eq(e.left, l));
}

static void test_body_has_no_margin(void **state) {
    (void)state;
    bx_box b = bx_default_for_tag("body");
    assert_int_equal(b.display, BX_DISPLAY_BLOCK);
    assert_edges(b.margin, 0.0, 0.0, 0.0, 0.0);  /* the window chrome owns the gutter */
    assert_edges(b.padding, 0.0, 0.0, 0.0, 0.0);
}

static void test_paragraph(void **state) {
    (void)state;
    bx_box b = bx_default_for_tag("p");
    assert_int_equal(b.display, BX_DISPLAY_BLOCK);
    assert_edges(b.margin, 1.0, 0.0, 1.0, 0.0);
}

static void test_heading_ladder(void **state) {
    (void)state;
    assert_int_equal(bx_default_for_tag("h1").display, BX_DISPLAY_BLOCK);
    assert_true(dbl_eq(bx_default_for_tag("h1").margin.top, 0.67));
    assert_true(dbl_eq(bx_default_for_tag("h2").margin.top, 0.83));
    assert_true(dbl_eq(bx_default_for_tag("h3").margin.top, 1.0));
    assert_true(dbl_eq(bx_default_for_tag("h4").margin.top, 1.33));
    assert_true(dbl_eq(bx_default_for_tag("h5").margin.top, 1.67));
    assert_true(dbl_eq(bx_default_for_tag("h6").margin.top, 2.33));
    /* symmetric top/bottom, no horizontal margin */
    bx_box h3 = bx_default_for_tag("h3");
    assert_true(dbl_eq(h3.margin.top, h3.margin.bottom));
    assert_true(dbl_eq(h3.margin.left, 0.0));
    assert_true(dbl_eq(h3.margin.right, 0.0));
}

static void test_lists(void **state) {
    (void)state;
    bx_box ul = bx_default_for_tag("ul");
    assert_int_equal(ul.display, BX_DISPLAY_BLOCK);
    assert_edges(ul.margin, 1.0, 0.0, 1.0, 0.0);
    assert_true(dbl_eq(ul.padding.left, 2.5));   /* room for the markers */
    bx_box ol = bx_default_for_tag("ol");
    assert_true(dbl_eq(ol.padding.left, 2.5));
    assert_int_equal(bx_default_for_tag("li").display, BX_DISPLAY_LIST_ITEM);
}

static void test_blockquote(void **state) {
    (void)state;
    bx_box bq = bx_default_for_tag("blockquote");
    assert_int_equal(bq.display, BX_DISPLAY_BLOCK);
    assert_edges(bq.margin, 1.0, 2.5, 1.0, 2.5);
}

static void test_hr(void **state) {
    (void)state;
    bx_box hr = bx_default_for_tag("hr");
    assert_int_equal(hr.display, BX_DISPLAY_BLOCK);
    assert_edges(hr.margin, 0.5, 0.0, 0.5, 0.0);
}

static void test_inline_and_inline_block(void **state) {
    (void)state;
    assert_int_equal(bx_default_for_tag("span").display, BX_DISPLAY_INLINE);
    assert_int_equal(bx_default_for_tag("a").display, BX_DISPLAY_INLINE);
    assert_int_equal(bx_default_for_tag("strong").display, BX_DISPLAY_INLINE);
    assert_int_equal(bx_default_for_tag("code").display, BX_DISPLAY_INLINE);
    assert_int_equal(bx_default_for_tag("img").display, BX_DISPLAY_INLINE_BLOCK);
    assert_int_equal(bx_default_for_tag("input").display, BX_DISPLAY_INLINE_BLOCK);
    assert_int_equal(bx_default_for_tag("button").display, BX_DISPLAY_INLINE_BLOCK);
}

static void test_display_none_for_non_rendered(void **state) {
    (void)state;
    assert_int_equal(bx_default_for_tag("head").display, BX_DISPLAY_NONE);
    assert_int_equal(bx_default_for_tag("script").display, BX_DISPLAY_NONE);
    assert_int_equal(bx_default_for_tag("style").display, BX_DISPLAY_NONE);
    assert_int_equal(bx_default_for_tag("title").display, BX_DISPLAY_NONE);
    assert_int_equal(bx_default_for_tag("meta").display, BX_DISPLAY_NONE);
}

static void test_case_insensitive(void **state) {
    (void)state;
    assert_int_equal(bx_default_for_tag("P").display, BX_DISPLAY_BLOCK);
    assert_true(dbl_eq(bx_default_for_tag("P").margin.top, 1.0));
    assert_int_equal(bx_default_for_tag("DiV").display, BX_DISPLAY_BLOCK);
    assert_int_equal(bx_default_for_tag("ImG").display, BX_DISPLAY_INLINE_BLOCK);
}

static void test_unknown_and_null_are_neutral_inline(void **state) {
    (void)state;
    bx_box u = bx_default_for_tag("zorp");
    assert_int_equal(u.display, BX_DISPLAY_INLINE);
    assert_edges(u.margin, 0.0, 0.0, 0.0, 0.0);
    assert_edges(u.padding, 0.0, 0.0, 0.0, 0.0);

    bx_box n = bx_default_for_tag(NULL);
    assert_int_equal(n.display, BX_DISPLAY_INLINE);
    assert_edges(n.margin, 0.0, 0.0, 0.0, 0.0);

    bx_box e = bx_default_for_tag("");
    assert_int_equal(e.display, BX_DISPLAY_INLINE);
}

static void test_div_is_block(void **state) {
    (void)state;
    bx_box d = bx_default_for_tag("div");
    assert_int_equal(d.display, BX_DISPLAY_BLOCK);
    assert_edges(d.margin, 0.0, 0.0, 0.0, 0.0);
}

static void test_parse_display_keywords(void **state) {
    (void)state;
    bx_display d;
    assert_int_equal(bx_parse_display("none", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_NONE);
    assert_int_equal(bx_parse_display("block", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_BLOCK);
    assert_int_equal(bx_parse_display("inline", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_INLINE);
    assert_int_equal(bx_parse_display("inline-block", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_INLINE_BLOCK);
    assert_int_equal(bx_parse_display("list-item", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_LIST_ITEM);
    assert_int_equal(bx_parse_display("flex", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_FLEX);
    assert_int_equal(bx_parse_display("grid", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_GRID);
}

static void test_parse_display_inline_aliases(void **state) {
    (void)state;
    bx_display d;
    assert_int_equal(bx_parse_display("inline-flex", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_FLEX);
    assert_int_equal(bx_parse_display("inline-grid", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_GRID);
}

static void test_parse_display_case_and_trim(void **state) {
    (void)state;
    bx_display d;
    assert_int_equal(bx_parse_display("  FLEX  ", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_FLEX);
    assert_int_equal(bx_parse_display("\tGrid\n", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_GRID);
}

static void test_parse_display_errors(void **state) {
    (void)state;
    bx_display d = BX_DISPLAY_BLOCK;
    assert_int_equal(bx_parse_display(NULL, &d), BX_ERR_NULL_ARG);
    assert_int_equal(bx_parse_display("flex", NULL), BX_ERR_NULL_ARG);
    assert_int_equal(bx_parse_display("", &d), BX_ERR_SYNTAX);
    assert_int_equal(bx_parse_display("table", &d), BX_ERR_SYNTAX);
    assert_int_equal(bx_parse_display("flow-root", &d), BX_ERR_SYNTAX);
    assert_int_equal(bx_parse_display("var(--x)", &d), BX_ERR_SYNTAX);
    /* an oversized token must fail closed, not overflow */
    char big[256];
    memset(big, 'a', sizeof big - 1);
    big[sizeof big - 1] = '\0';
    assert_int_equal(bx_parse_display(big, &d), BX_ERR_SYNTAX);
    /* out untouched on error */
    assert_int_equal(d, BX_DISPLAY_BLOCK);
}

static void test_display_name(void **state) {
    (void)state;
    assert_string_equal(bx_display_name(BX_DISPLAY_BLOCK), "block");
    assert_string_equal(bx_display_name(BX_DISPLAY_INLINE), "inline");
    assert_string_equal(bx_display_name(BX_DISPLAY_INLINE_BLOCK), "inline-block");
    assert_string_equal(bx_display_name(BX_DISPLAY_LIST_ITEM), "list-item");
    assert_string_equal(bx_display_name(BX_DISPLAY_FLEX), "flex");
    assert_string_equal(bx_display_name(BX_DISPLAY_GRID), "grid");
    assert_string_equal(bx_display_name(BX_DISPLAY_NONE), "none");
    /* unknown enum value falls back to inline, never NULL */
    assert_string_equal(bx_display_name((bx_display)999), "inline");
}

/* --- bx_place: author box horizontal geometry (Hito 23b-3) --- */

static void test_place_no_box_is_identity(void **state) {
    (void)state;
    bx_hplace p = bx_place(0, 0, 0, 0, 800.0);
    assert_true(dbl_eq(p.x_off, 0.0));
    assert_true(dbl_eq(p.content_w, 800.0));
}

static void test_place_max_width_caps(void **state) {
    (void)state;
    /* cap below available: content shrinks, left-aligned (no centering). */
    bx_hplace p = bx_place(0, 0, 600.0, 0, 800.0);
    assert_true(dbl_eq(p.x_off, 0.0));
    assert_true(dbl_eq(p.content_w, 600.0));
    /* cap above available: never overflows (stays at available). */
    bx_hplace q = bx_place(0, 0, 2000.0, 0, 800.0);
    assert_true(dbl_eq(q.content_w, 800.0));
}

static void test_place_centering(void **state) {
    (void)state;
    /* margin: 0 auto; max-width:600 within 800 -> centered, 100px each side. */
    bx_hplace p = bx_place(0, 0, 600.0, 1, 800.0);
    assert_true(dbl_eq(p.content_w, 600.0));
    assert_true(dbl_eq(p.x_off, 100.0));
    /* centering with no width cap is a no-op (nothing to center). */
    bx_hplace q = bx_place(0, 0, 0, 1, 800.0);
    assert_true(dbl_eq(q.x_off, 0.0));
    assert_true(dbl_eq(q.content_w, 800.0));
}

static void test_place_insets(void **state) {
    (void)state;
    /* padding/left+right margins inset the content and shrink the width. */
    bx_hplace p = bx_place(40.0, 20.0, 0, 0, 800.0);
    assert_true(dbl_eq(p.x_off, 40.0));
    assert_true(dbl_eq(p.content_w, 740.0));  /* 800 - 40 - 20 */
    /* insets compose with a width cap (cap applies to the inner box). */
    bx_hplace q = bx_place(40.0, 20.0, 500.0, 0, 800.0);
    assert_true(dbl_eq(q.x_off, 40.0));
    assert_true(dbl_eq(q.content_w, 500.0));
}

static void test_place_failclosed_bounds(void **state) {
    (void)state;
    /* negative insets clamp to 0; tiny/negative avail floors content_w at 1. */
    bx_hplace p = bx_place(-50.0, -50.0, 0, 0, 800.0);
    assert_true(dbl_eq(p.x_off, 0.0));
    assert_true(dbl_eq(p.content_w, 800.0));
    bx_hplace q = bx_place(0, 0, 0, 0, -10.0);
    assert_true(p.x_off >= 0.0);
    assert_true(q.content_w >= 1.0);
    /* insets exceeding avail still yield content_w >= 1 (never negative). */
    bx_hplace r = bx_place(900.0, 900.0, 0, 0, 800.0);
    assert_true(r.content_w >= 1.0);
}

/* Hito 32: effective width cap combining the px cap with a per-mille cap
 * resolved against the real available width (the tighter one wins). */
static void test_width_cap_pct(void **state) {
    (void)state;
    assert_true(dbl_eq(bx_width_cap(0, 0, 800.0), 0.0));       /* none */
    assert_true(dbl_eq(bx_width_cap(600, 0, 800.0), 600.0));   /* px only */
    assert_true(dbl_eq(bx_width_cap(0, 998, 1000.0), 998.0));  /* 99.8% of 1000 */
    assert_true(dbl_eq(bx_width_cap(0, 500, 800.0), 400.0));   /* 50% of 800 */
    assert_true(dbl_eq(bx_width_cap(300, 500, 800.0), 300.0)); /* px tighter */
    assert_true(dbl_eq(bx_width_cap(700, 500, 800.0), 400.0)); /* pct tighter */
    assert_true(dbl_eq(bx_width_cap(0, 500, 0.0), 0.0));       /* no avail: none */
    assert_true(dbl_eq(bx_width_cap(-5, -3, 800.0), 0.0));     /* junk: none */
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_place_no_box_is_identity),
        cmocka_unit_test(test_place_max_width_caps),
        cmocka_unit_test(test_place_centering),
        cmocka_unit_test(test_place_insets),
        cmocka_unit_test(test_place_failclosed_bounds),
        cmocka_unit_test(test_width_cap_pct),
        cmocka_unit_test(test_body_has_no_margin),
        cmocka_unit_test(test_paragraph),
        cmocka_unit_test(test_heading_ladder),
        cmocka_unit_test(test_lists),
        cmocka_unit_test(test_blockquote),
        cmocka_unit_test(test_hr),
        cmocka_unit_test(test_inline_and_inline_block),
        cmocka_unit_test(test_display_none_for_non_rendered),
        cmocka_unit_test(test_case_insensitive),
        cmocka_unit_test(test_unknown_and_null_are_neutral_inline),
        cmocka_unit_test(test_div_is_block),
        cmocka_unit_test(test_parse_display_keywords),
        cmocka_unit_test(test_parse_display_inline_aliases),
        cmocka_unit_test(test_parse_display_case_and_trim),
        cmocka_unit_test(test_parse_display_errors),
        cmocka_unit_test(test_display_name),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
