#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "css_mq.h"

static const cmq_env ENV = { 1000, 1080, 0, 0 };

static int m(const char *q) { return cmq_matches(q, strlen(q), &ENV); }

static void test_range_syntax(void **state) {
    (void)state;
    assert_true(m("(width>=48rem)"));
    assert_false(m("(width>=64rem)"));
    assert_false(m("(width<=767px)"));
    assert_true(m("(width < 1001px)"));
    assert_false(m("(width > 1000px)"));
    assert_true(m("(768px <= width <= 1011px)"));
    assert_false(m("(1001px <= width < 2000px)"));
    assert_true(m("(500px < width)"));
    assert_true(m("(width = 1000px)"));
    assert_true(m("(height>=1000px)"));
    assert_false(m("(height<=639px) and (width>=768px)"));
}

static void test_plain_and_types(void **state) {
    (void)state;
    assert_true(m("screen and (min-width:600px)"));
    assert_true(m("only screen and (max-width: 1200px)"));
    assert_false(m("print"));
    assert_true(m("all"));
    assert_true(m(""));
    assert_true(m("print, (min-width: 40em)"));
    assert_false(m("(min-width: 64em)"));
    assert_true(m("(min-height: 500px)"));
    assert_true(m("(orientation: landscape)"));
    assert_false(m("(orientation: portrait)"));
}

static void test_not_or(void **state) {
    (void)state;
    assert_true(m("not all and (max-width:600px)"));
    assert_false(m("not all and (min-width:600px)"));
    assert_false(m("not (hover:hover)"));
    assert_true(m("not print"));
    assert_true(m("((max-width:500px) or (min-width:900px))"));
    assert_true(m("(max-width:500px) or (min-width:900px)"));
    assert_false(m("((max-width:500px) or (min-width:1900px))"));
    assert_true(m("(min-width:900px) and (not (hover:none))"));
}

static void test_desktop_identity(void **state) {
    (void)state;
    assert_false(m("(prefers-reduced-motion:reduce)"));
    assert_true(m("(prefers-reduced-motion:no-preference)"));
    assert_true(m("(hover)"));
    assert_true(m("(hover:hover)"));
    assert_true(m("(any-hover:hover)"));
    assert_true(m("(pointer:fine)"));
    assert_false(m("(pointer:coarse)"));
    assert_true(m("(color)"));
    assert_false(m("(min-resolution:2dppx)"));
    assert_true(m("(min-resolution:1dppx)"));
    assert_false(m("(-webkit-min-device-pixel-ratio:2)"));
    assert_true(m("(prefers-color-scheme:light)"));
    assert_false(m("(prefers-color-scheme:dark)"));
    assert_true(m("(forced-colors:none)"));
    assert_true(m("(prefers-contrast:no-preference)"));
    cmq_env dark = ENV;
    dark.prefers_dark = 1;
    assert_true(cmq_matches("(prefers-color-scheme:dark)", 27, &dark));
}

static void test_fail_closed(void **state) {
    (void)state;
    assert_false(m("(frobnicate:1)"));
    assert_false(m("(width >> 3px)"));
    assert_false(m("(width >= )"));
    assert_false(m("(scripting:enabled)"));
    assert_false(m("not (frobnicate:1)"));
    assert_false(m("tv"));
    assert_false(m("((((((((((((((((((width>0px))))))))))))))))))"));
    assert_false(cmq_matches(NULL, 0, &ENV));
    assert_false(cmq_matches("(width>0px)", 11, NULL));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_range_syntax),
        cmocka_unit_test(test_plain_and_types),
        cmocka_unit_test(test_not_or),
        cmocka_unit_test(test_desktop_identity),
        cmocka_unit_test(test_fail_closed),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
