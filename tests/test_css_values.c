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
    assert_int_equal(cv_bg_alpha_of("rgba(0,0,0,0)"), 0);
    assert_int_equal(cv_bg_alpha_of("rgba(0,0,0,1)"), 100);
    assert_int_equal(cv_bg_alpha_of("rgba(0,0,0,2)"), 100);
    assert_int_equal(cv_bg_alpha_of("rgba(0,0,0,100%)"), 100);
    assert_int_equal(cv_bg_alpha_of("red"), CSS_LEN_UNSET);
    /* CSS Color 4 section 5.2: #RGBA and #RRGGBBAA carry the alpha in the last
     * digit(s) -- the minifier writes `transparent` as #0000. */
    assert_int_equal(cv_bg_alpha_of("#0000"), 0);
    assert_int_equal(cv_bg_alpha_of("#00f8"), 53);
    assert_int_equal(cv_bg_alpha_of("#00ff0080"), 50);
    assert_int_equal(cv_bg_alpha_of("#00ff00"), CSS_LEN_UNSET);
    assert_int_equal(cv_bg_alpha_of("#fff"), CSS_LEN_UNSET);
    assert_int_equal(cv_bg_alpha_of("url(#a0b1) #0000"), 0);
}

/* Every CSS Color 4/5 function carries its alpha after a slash, and color-mix() mixes the
 * alphas: Tailwind v4 writes `bg-white/10` as color-mix(in oklab, white 10%, transparent). */
static void test_alpha_modern_functions(void **state)
{
    (void)state;
    assert_int_equal(cv_bg_alpha_of("oklab(100% 0 0 / .5)"), 50);
    assert_int_equal(cv_bg_alpha_of("oklch(54.1% .281 293.009 / 25%)"), 25);
    assert_int_equal(cv_bg_alpha_of("lab(50% 10 10 / 0.3)"), 30);
    assert_int_equal(cv_bg_alpha_of("lch(50% 10 10 / 0.3)"), 30);
    assert_int_equal(cv_bg_alpha_of("hwb(0 0% 0% / 40%)"), 40);
    assert_int_equal(cv_bg_alpha_of("color(srgb 1 1 1 / 0.6)"), 60);
    assert_int_equal(cv_bg_alpha_of("oklch(54.1% .281 293.009)"), CSS_LEN_UNSET);
    assert_int_equal(cv_bg_alpha_of("color-mix(in oklab, #fff 10%, transparent)"), 10);
    assert_int_equal(cv_bg_alpha_of("color-mix(in oklab, oklch(98% .01 0) 40%, transparent)"), 40);
    assert_int_equal(cv_bg_alpha_of("color-mix(in srgb, transparent, red 25%)"), 25);
    assert_int_equal(cv_bg_alpha_of("color-mix(in srgb, red, blue)"), CSS_LEN_UNSET);
    assert_int_equal(cv_bg_alpha_of("color-mix(in srgb, #ff000080, blue)"), 75);
    assert_int_equal(cv_bg_alpha_of("color-mix(in srgb, red 20%, blue 20%)"), 40);
    assert_int_equal(cv_bg_alpha_of("color-mix(in srgb, red 0%, blue 0%)"), CSS_LEN_UNSET);
    assert_int_equal(cv_parse_color("color-mix(in srgb, red, blue)"), 0x800080);
    assert_int_equal(cv_parse_color("color-mix(in oklab, #fff 10%, transparent)"), 0xffffff);
    assert_int_equal(cv_parse_color("color-mix(in srgb, red 25%, color-mix(in srgb, blue, blue))"),
                     0x4000bf);
    assert_int_equal(cv_parse_color("color-mix(red, blue)"), -1);
    assert_int_equal(cv_parse_color("color-mix(in srgb, red, junk)"), -1);
    /* the t7 encoding the border/shadow painters read */
    int c = cv_parse_color_t7("color-mix(in oklab, #fff 10%, transparent)");
    assert_true(c >= 0);
    assert_int_equal(c & 0xffffff, 0xffffff);
    assert_true(((c >> 24) & 0x7f) > 110);
}

/* CSS Color 4 slash alpha rides on the rgb()/hsl() names too, not just the
 * legacy rgba()/hsla() aliases. */
static void test_alpha_slash(void **state)
{
    (void)state;
    assert_int_equal(cv_bg_alpha_of("rgb(0 0 0 / 75%)"), 75);
    assert_int_equal(cv_bg_alpha_of("rgb(229 233 240 / 50%)"), 50);
    assert_int_equal(cv_bg_alpha_of("rgb(0 0 0 / 0.5)"), 50);
    assert_int_equal(cv_bg_alpha_of("hsl(0 0% 0% / 50%)"), 50);
    assert_int_equal(cv_bg_alpha_of("rgb(255 0 0)"), CSS_LEN_UNSET);
    assert_int_equal(cv_bg_alpha_of("rgb(0,0,0)"), CSS_LEN_UNSET);
}

static void test_bg_skips_url(void **state)
{
    (void)state;
    assert_true(cv_interp_bg("url(http://x) red") == 0xFF0000);
}


static void test_filter_scale_neutral_when_undeclared(void **state)
{
    (void)state;
    /* brightness/contrast/saturate are multipliers: an UNDECLARED one (0) and 100% are the
     * identity. Treating 0 as "multiply by zero" turned every filter into a black box. */
    assert_true(cv_filter_scale(0) == 1.0);
    assert_true(cv_filter_scale(100) == 1.0);
    assert_true(cv_filter_scale(-5) == 1.0);
    assert_true(cv_filter_scale(150) == 1.5);
    assert_true(cv_filter_scale(25) == 0.25);
    assert_true(cv_filter_scale(100000) == 1000.0);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_parse_named),
        cmocka_unit_test(test_alpha_modern_functions),
        cmocka_unit_test(test_sentinels_ok),
        cmocka_unit_test(test_junk_fails_closed),
        cmocka_unit_test(test_alpha),
        cmocka_unit_test(test_alpha_slash),
        cmocka_unit_test(test_bg_skips_url),
        cmocka_unit_test(test_filter_scale_neutral_when_undeclared),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
