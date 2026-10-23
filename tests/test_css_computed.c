#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "css_computed.h"

static const char *get(const css_style *st, double fpx, int icol, const char *p) {
    static char buf[CCM_VALUE_MAX];
    ccm_input in = { st, fpx, icol, NULL };
    (void)ccm_get(&in, p, buf, sizeof buf);
    return buf;
}

static css_style blank(void) {
    css_style s;
    memset(&s, 0, sizeof s);
    s.color = -1; s.background = -1; s.bg_alpha = CSS_LEN_UNSET;
    s.width = s.height = CSS_LEN_UNSET;
    s.margin_top = s.margin_right = s.margin_bottom = s.margin_left = CSS_LEN_UNSET;
    s.pad_top = s.pad_right = s.pad_bottom = s.pad_left = CSS_LEN_UNSET;
    s.opacity = -1; s.bold = -1; s.z_index = CSS_LEN_UNSET;
    return s;
}

static void test_initial_values(void **state) {
    (void)state;
    css_style s = blank();
    assert_string_equal(get(&s, 16, -1, "display"), "inline");
    assert_string_equal(get(&s, 16, -1, "position"), "static");
    assert_string_equal(get(&s, 16, -1, "visibility"), "visible");
    assert_string_equal(get(&s, 16, -1, "opacity"), "1");
    assert_string_equal(get(&s, 16, -1, "color"), "rgb(0, 0, 0)");
    assert_string_equal(get(&s, 16, -1, "background-color"), "rgba(0, 0, 0, 0)");
    assert_string_equal(get(&s, 16, -1, "margin-top"), "0px");
    assert_string_equal(get(&s, 16, -1, "width"), "auto");
    assert_string_equal(get(&s, 16, -1, "z-index"), "auto");
    assert_string_equal(get(&s, 16, -1, "font-weight"), "400");
    s.gap = -1;                                   /* the engine's "unset" sentinel */
    assert_string_equal(get(&s, 16, -1, "gap"), "normal");
    s.gap = 8;
    assert_string_equal(get(&s, 16, -1, "gap"), "8px");
}

static void test_declared_values(void **state) {
    (void)state;
    css_style s = blank();
    s.display = CSS_DISP_FLEX; s.position = CSS_POS_ABSOLUTE;
    s.color = 0x336699; s.background = 0xff0000; s.bg_alpha = 50;
    s.margin_left = 12; s.pad_top = 7; s.width = 240; s.bold = 1; s.opacity = 25;
    s.z_index = -3;
    assert_string_equal(get(&s, 20, -1, "display"), "flex");
    assert_string_equal(get(&s, 20, -1, "position"), "absolute");
    assert_string_equal(get(&s, 20, -1, "color"), "rgb(51, 102, 153)");
    assert_string_equal(get(&s, 20, -1, "background-color"), "rgba(255, 0, 0, 0.5)");
    assert_string_equal(get(&s, 20, -1, "margin-left"), "12px");
    assert_string_equal(get(&s, 20, -1, "padding-top"), "7px");
    assert_string_equal(get(&s, 20, -1, "width"), "240px");
    assert_string_equal(get(&s, 20, -1, "font-weight"), "700");
    assert_string_equal(get(&s, 20, -1, "opacity"), "0.25");
    assert_string_equal(get(&s, 20, -1, "z-index"), "-3");
    assert_string_equal(get(&s, 20, -1, "font-size"), "20px");
}

static void test_ua_display_by_tag(void **state) {
    (void)state;
    css_style s = blank();
    char buf[CCM_VALUE_MAX];
    const char *cases[][2] = { { "p", "block" }, { "div", "block" }, { "span", "inline" },
        { "li", "list-item" }, { "script", "none" }, { "td", "table-cell" }, { "table", "table" },
        { "button", "inline-block" }, { "a", "inline" } };
    for (size_t i = 0; i < sizeof cases / sizeof *cases; ++i) {
        ccm_input in = { &s, 16, -1, cases[i][0] };
        (void)ccm_get(&in, "display", buf, sizeof buf);
        assert_string_equal(buf, cases[i][1]);
    }
    s.display = CSS_DISP_FLEX;                       /* a declared value beats the tag default */
    ccm_input in = { &s, 16, -1, "span" };
    (void)ccm_get(&in, "display", buf, sizeof buf);
    assert_string_equal(buf, "flex");
}

static void test_color_inherits(void **state) {
    (void)state;
    css_style s = blank();
    assert_string_equal(get(&s, 16, 0xabcdef, "color"), "rgb(171, 205, 239)");
    s.color = 0x010203;
    assert_string_equal(get(&s, 16, 0xabcdef, "color"), "rgb(1, 2, 3)");
}

static void test_unknown_property_is_empty(void **state) {
    (void)state;
    css_style s = blank();
    assert_string_equal(get(&s, 16, -1, "not-a-property"), "");
    assert_string_equal(get(&s, 16, -1, ""), "");
    char buf[4];
    ccm_input in = { &s, 16, -1, NULL };
    assert_int_equal(ccm_get(&in, "display", buf, sizeof buf), 0);  /* does not fit: fail closed */
    assert_string_equal(buf, "");
    assert_int_equal(ccm_get(NULL, "display", buf, sizeof buf), 0);
}

static void test_enumeration(void **state) {
    (void)state;
    assert_true(ccm_property_count() >= 40);
    css_style s = blank();
    for (size_t i = 0; i < ccm_property_count(); ++i) {
        const char *n = ccm_property_name(i);
        assert_non_null(n);
        char buf[CCM_VALUE_MAX];
        ccm_input in = { &s, 16, -1, NULL };
        assert_true(ccm_get(&in, n, buf, sizeof buf) > 0);  /* every listed property has a value */
    }
    assert_null(ccm_property_name(ccm_property_count()));
}

int main(void) {
    const struct CMUnitTest t[] = {
        cmocka_unit_test(test_initial_values),
        cmocka_unit_test(test_declared_values),
        cmocka_unit_test(test_ua_display_by_tag),
        cmocka_unit_test(test_color_inherits),
        cmocka_unit_test(test_unknown_property_is_empty),
        cmocka_unit_test(test_enumeration),
    };
    return cmocka_run_group_tests(t, NULL, NULL);
}
