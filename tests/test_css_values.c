#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "css_values.h"
#include "css.h"

static void test_parse_named(void **state)
{
    (void)state;
    assert_int_equal(cv_color_ok(cv_parse_color("red")), 1);
    assert_true(cv_parse_color("red") == 0xFF0000);
}

static void test_sentinels_ok(void **state)
{
    (void)state;
    assert_int_equal(cv_color_ok(cv_parse_color("transparent")), 1);
    assert_int_equal(cv_color_ok(cv_parse_color("currentColor")), 1);
    assert_int_equal(cv_color_ok(-1), 0);
}

static void test_junk_fails_closed(void **state)
{
    (void)state;
    assert_int_equal(cv_parse_color("not-a-color"), -1);
    assert_int_equal(cv_parse_color(NULL), -1);
    assert_int_equal(cv_interp_bg(NULL), -1);
    assert_int_equal(cv_bg_alpha_of(NULL), CSS_LEN_UNSET);
}

static void test_alpha(void **state)
{
    (void)state;
    assert_int_equal(cv_bg_alpha_of("rgba(0,0,0,0.5)"), 50);
    assert_int_equal(cv_bg_alpha_of("red"), CSS_LEN_UNSET);
}

static void test_bg_skips_url(void **state)
{
    (void)state;
    assert_true(cv_interp_bg("url(http://x) red") == 0xFF0000);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_parse_named),
        cmocka_unit_test(test_sentinels_ok),
        cmocka_unit_test(test_junk_fails_closed),
        cmocka_unit_test(test_alpha),
        cmocka_unit_test(test_bg_skips_url),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
