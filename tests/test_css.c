/*
 * test_css — CMocka suite for the author-CSS parser + simple cascade.
 *
 * Covers inline declaration parsing (every supported property), <style> block
 * parsing with type/class/id/universal/compound/group selectors, the cascade
 * (specificity, document order, inline-wins), inheritance being the caller's job
 * (resolve returns unset for non-matching), and the security rules (url() dropped,
 * @-rules skipped, unknown ignored, malformed never crashes).
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "css.h"

/* --- inline declarations --- */

static void test_inline_color_and_bg(void **state) {
    (void)state;
    css_style s = css_parse_inline("color:#ff0000; background-color: #00ff00", 0);
    assert_int_equal(s.color, 0xff0000);
    assert_int_equal(s.background, 0x00ff00);
}

static void test_inline_text_align(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("text-align:center", 0).text_align, CSS_ALIGN_CENTER);
    assert_int_equal(css_parse_inline("text-align: RIGHT", 0).text_align, CSS_ALIGN_RIGHT);
    assert_int_equal(css_parse_inline("text-align:justify", 0).text_align, CSS_ALIGN_JUSTIFY);
    assert_int_equal(css_parse_inline("color:red", 0).text_align, CSS_ALIGN_UNSET);
}

static void test_inline_font_size(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("font-size:32px", 0).font_scale, 200);   /* 32/16 */
    assert_int_equal(css_parse_inline("font-size:2em", 0).font_scale, 200);
    assert_int_equal(css_parse_inline("font-size:150%", 0).font_scale, 150);
    assert_int_equal(css_parse_inline("font-size:large", 0).font_scale, 120);
    assert_int_equal(css_parse_inline("font-size:x-large", 0).font_scale, 150);
    assert_int_equal(css_parse_inline("color:red", 0).font_scale, 0);          /* unset */
}

static void test_inline_font_weight_style(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("font-weight:bold", 0).bold, 1);
    assert_int_equal(css_parse_inline("font-weight:700", 0).bold, 1);
    assert_int_equal(css_parse_inline("font-weight:400", 0).bold, 0);
    assert_int_equal(css_parse_inline("font-weight:normal", 0).bold, 0);
    assert_int_equal(css_parse_inline("color:red", 0).bold, -1);               /* unset */
    assert_int_equal(css_parse_inline("font-style:italic", 0).italic, 1);
    assert_int_equal(css_parse_inline("font-style:normal", 0).italic, 0);
    assert_int_equal(css_parse_inline("color:red", 0).italic, -1);
}

static void test_inline_display(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("display:none", 0).display, CSS_DISP_NONE);
    assert_int_equal(css_parse_inline("display:flex", 0).display, CSS_DISP_FLEX);
    assert_int_equal(css_parse_inline("display:grid", 0).display, CSS_DISP_GRID);
    assert_int_equal(css_parse_inline("display:block", 0).display, CSS_DISP_BLOCK);
    assert_int_equal(css_parse_inline("color:red", 0).display, CSS_DISP_UNSET);
}

/* --- security: never phone home, ignore junk --- */

static void test_url_value_dropped(void **state) {
    (void)state;
    /* a background with url() must NOT be honored (no fetch surface). */
    css_style s = css_parse_inline("background: url(http://evil/x.png) #112233", 0);
    assert_int_equal(s.background, -1);
    /* but a plain color background is fine. */
    assert_int_equal(css_parse_inline("background:#112233", 0).background, 0x112233);
}

static void test_unknown_props_ignored(void **state) {
    (void)state;
    css_style s = css_parse_inline("position:absolute; z-index:9; color:#abcdef; --x:1", 0);
    assert_int_equal(s.color, 0xabcdef);
    assert_int_equal(s.text_align, CSS_ALIGN_UNSET);
}

static void test_malformed_inline_no_crash(void **state) {
    (void)state;
    css_style s = css_parse_inline(";;: ; color ; :red; color::; color:#777;;", 0);
    assert_int_equal(s.color, 0x777777);
}

/* --- <style> block parsing + selectors --- */

static void test_sheet_type_selector(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("p { color: #010203; }", 0, &sh), CSS_OK);
    css_style s = css_resolve(sh, "p", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.color, 0x010203);
    /* a different tag does not match. */
    assert_int_equal(css_resolve(sh, "div", NULL, NULL, 0, NULL, 0).color, -1);
    css_free(sh);
}

static void test_sheet_class_and_id(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(".note{color:#111111} #main{color:#222222}", 0, &sh), CSS_OK);
    const char *cl[] = { "note" };
    assert_int_equal(css_resolve(sh, "div", NULL, cl, 1, NULL, 0).color, 0x111111);
    assert_int_equal(css_resolve(sh, "div", "main", NULL, 0, NULL, 0).color, 0x222222);
    css_free(sh);
}

static void test_sheet_universal_and_group(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("* { text-align:center }\n h1, h2 { color:#0000ff }", 0, &sh), CSS_OK);
    assert_int_equal(css_resolve(sh, "span", NULL, NULL, 0, NULL, 0).text_align, CSS_ALIGN_CENTER);
    assert_int_equal(css_resolve(sh, "h2", NULL, NULL, 0, NULL, 0).color, 0x0000ff);
    assert_int_equal(css_resolve(sh, "h3", NULL, NULL, 0, NULL, 0).color, -1);
    css_free(sh);
}

static void test_sheet_compound_selector(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("a.button { color:#0a0b0c }", 0, &sh), CSS_OK);
    const char *btn[] = { "button" };
    const char *other[] = { "link" };
    assert_int_equal(css_resolve(sh, "a", NULL, btn, 1, NULL, 0).color, 0x0a0b0c);
    assert_int_equal(css_resolve(sh, "a", NULL, other, 1, NULL, 0).color, -1);  /* class mismatch */
    assert_int_equal(css_resolve(sh, "p", NULL, btn, 1, NULL, 0).color, -1);    /* tag mismatch */
    css_free(sh);
}

static void test_descendant_selector_unsupported(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* "div p" has a combinator -> that selector is dropped; the next group still works. */
    assert_int_equal(css_parse("div p { color:#999999 } p { color:#080808 }", 0, &sh), CSS_OK);
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0x080808);
    css_free(sh);
}

/* --- cascade --- */

static void test_cascade_specificity(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* id (100) beats class (10) beats type (1) regardless of source order. */
    assert_int_equal(css_parse("#x{color:#0000ff} .c{color:#00ff00} p{color:#ff0000}", 0, &sh), CSS_OK);
    const char *cl[] = { "c" };
    assert_int_equal(css_resolve(sh, "p", "x", cl, 1, NULL, 0).color, 0x0000ff); /* id wins */
    assert_int_equal(css_resolve(sh, "p", NULL, cl, 1, NULL, 0).color, 0x00ff00); /* class wins */
    css_free(sh);
}

static void test_cascade_document_order(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* equal specificity -> the later rule wins. */
    assert_int_equal(css_parse("p{color:#111111} p{color:#222222}", 0, &sh), CSS_OK);
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0x222222);
    css_free(sh);
}

static void test_cascade_inline_wins(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("#x{color:#111111}", 0, &sh), CSS_OK);
    /* inline beats even an id rule. */
    assert_int_equal(css_resolve(sh, "p", "x", NULL, 0, "color:#abcabc", 0).color, 0xabcabc);
    css_free(sh);
}

static void test_at_rules_skipped(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(
        "@import url(evil.css);\n"
        "@media screen { p { color:#ffffff } }\n"
        "p { color:#123456 }", 0, &sh), CSS_OK);
    /* the @media block's inner rule is skipped along with the at-rule; the plain
     * rule still applies. */
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0x123456);
    css_free(sh);
}

/* --- arg handling --- */

static void test_parse_null_args(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(NULL, 0, &sh), CSS_OK);  /* NULL text = empty sheet */
    assert_non_null(sh);
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, -1);
    css_free(sh);
    assert_int_equal(css_parse("p{}", 0, NULL), CSS_ERR_NULL_ARG);
}

static void test_resolve_null_safe(void **state) {
    (void)state;
    /* NULL sheet and NULL tag are safe; everything unset. */
    css_style s = css_resolve(NULL, NULL, NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.color, -1);
    assert_int_equal(s.text_align, CSS_ALIGN_UNSET);
    assert_int_equal(s.display, CSS_DISP_UNSET);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_inline_color_and_bg),
        cmocka_unit_test(test_inline_text_align),
        cmocka_unit_test(test_inline_font_size),
        cmocka_unit_test(test_inline_font_weight_style),
        cmocka_unit_test(test_inline_display),
        cmocka_unit_test(test_url_value_dropped),
        cmocka_unit_test(test_unknown_props_ignored),
        cmocka_unit_test(test_malformed_inline_no_crash),
        cmocka_unit_test(test_sheet_type_selector),
        cmocka_unit_test(test_sheet_class_and_id),
        cmocka_unit_test(test_sheet_universal_and_group),
        cmocka_unit_test(test_sheet_compound_selector),
        cmocka_unit_test(test_descendant_selector_unsupported),
        cmocka_unit_test(test_cascade_specificity),
        cmocka_unit_test(test_cascade_document_order),
        cmocka_unit_test(test_cascade_inline_wins),
        cmocka_unit_test(test_at_rules_skipped),
        cmocka_unit_test(test_parse_null_args),
        cmocka_unit_test(test_resolve_null_safe),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
