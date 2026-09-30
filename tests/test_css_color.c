/*
 * test_css_color — CMocka suite for the pure CSS color parser.
 *
 * Covers hex (#rgb/#rgba/#rrggbb/#rrggbbaa), functional rgb()/rgba() with integer
 * and percentage components, hsl()/hsla(), the named-color table, case-insensitivity
 * and whitespace, transparent/currentColor sentinels, the pack/unpack round trip,
 * and the fail-closed edges (bad hex, out-of-range channels, junk, NULL).
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "css_color.h"

static cc_rgb C;

static void test_null_args(void **state) {
    (void)state;
    assert_int_equal(cc_parse(NULL, &C), CC_ERR_NULL_ARG);
    assert_int_equal(cc_parse("#fff", NULL), CC_ERR_NULL_ARG);
}

static void test_hex_short(void **state) {
    (void)state;
    assert_int_equal(cc_parse("#f00", &C), CC_OK);
    assert_int_equal(C.r, 0xff); assert_int_equal(C.g, 0x00); assert_int_equal(C.b, 0x00);

    assert_int_equal(cc_parse("#0F0", &C), CC_OK); /* case-insensitive */
    assert_int_equal(C.r, 0x00); assert_int_equal(C.g, 0xff); assert_int_equal(C.b, 0x00);
}

static void test_hex_short_alpha(void **state) {
    (void)state;
    /* #rgba: alpha validated then dropped, opaque result. */
    assert_int_equal(cc_parse("#1234", &C), CC_OK);
    assert_int_equal(C.r, 0x11); assert_int_equal(C.g, 0x22); assert_int_equal(C.b, 0x33);
}

static void test_hex_long(void **state) {
    (void)state;
    assert_int_equal(cc_parse("#11aaFF", &C), CC_OK);
    assert_int_equal(C.r, 0x11); assert_int_equal(C.g, 0xaa); assert_int_equal(C.b, 0xff);

    assert_int_equal(cc_parse("  #abcdef  ", &C), CC_OK); /* trimmed */
    assert_int_equal(C.r, 0xab); assert_int_equal(C.g, 0xcd); assert_int_equal(C.b, 0xef);
}

static void test_hex_long_alpha(void **state) {
    (void)state;
    assert_int_equal(cc_parse("#102030ff", &C), CC_OK);
    assert_int_equal(C.r, 0x10); assert_int_equal(C.g, 0x20); assert_int_equal(C.b, 0x30);
}

static void test_hex_bad(void **state) {
    (void)state;
    assert_int_equal(cc_parse("#12", &C), CC_ERR_SYNTAX);     /* wrong length */
    assert_int_equal(cc_parse("#ggg", &C), CC_ERR_SYNTAX);    /* non-hex digit */
    assert_int_equal(cc_parse("#1234567", &C), CC_ERR_SYNTAX);/* 7 digits */
    assert_int_equal(cc_parse("#", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("123456", &C), CC_ERR_SYNTAX);  /* missing # */
}

static void test_rgb_integer(void **state) {
    (void)state;
    assert_int_equal(cc_parse("rgb(255,0,128)", &C), CC_OK);
    assert_int_equal(C.r, 255); assert_int_equal(C.g, 0); assert_int_equal(C.b, 128);

    assert_int_equal(cc_parse("RGB( 16 , 32 , 48 )", &C), CC_OK); /* spaces + case */
    assert_int_equal(C.r, 16); assert_int_equal(C.g, 32); assert_int_equal(C.b, 48);
}

static void test_rgba_integer(void **state) {
    (void)state;
    /* alpha parsed then dropped */
    assert_int_equal(cc_parse("rgba(10, 20, 30, 0.5)", &C), CC_OK);
    assert_int_equal(C.r, 10); assert_int_equal(C.g, 20); assert_int_equal(C.b, 30);
}

static void test_rgb_percent(void **state) {
    (void)state;
    assert_int_equal(cc_parse("rgb(100%, 0%, 50%)", &C), CC_OK);
    assert_int_equal(C.r, 255); assert_int_equal(C.g, 0); assert_int_equal(C.b, 128);
}

static void test_rgb_out_of_range(void **state) {
    (void)state;
    assert_int_equal(cc_parse("rgb(256,0,0)", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("rgb(-1,0,0)", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("rgb(101%,0%,0%)", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("rgb(0,0)", &C), CC_ERR_SYNTAX);       /* too few */
    assert_int_equal(cc_parse("rgb(0,0,0,0,0)", &C), CC_ERR_SYNTAX); /* too many */
    assert_int_equal(cc_parse("rgb(0,0,0", &C), CC_ERR_SYNTAX);      /* unterminated */
}

static void test_named(void **state) {
    (void)state;
    assert_int_equal(cc_parse("red", &C), CC_OK);
    assert_int_equal(C.r, 255); assert_int_equal(C.g, 0); assert_int_equal(C.b, 0);

    assert_int_equal(cc_parse("White", &C), CC_OK);
    assert_int_equal(C.r, 255); assert_int_equal(C.g, 255); assert_int_equal(C.b, 255);

    assert_int_equal(cc_parse("BLACK", &C), CC_OK);
    assert_int_equal(C.r, 0); assert_int_equal(C.g, 0); assert_int_equal(C.b, 0);

    assert_int_equal(cc_parse("rebeccapurple", &C), CC_OK);
    assert_int_equal(C.r, 0x66); assert_int_equal(C.g, 0x33); assert_int_equal(C.b, 0x99);

    assert_int_equal(cc_parse("  cornflowerblue ", &C), CC_OK);
    assert_int_equal(C.r, 0x64); assert_int_equal(C.g, 0x95); assert_int_equal(C.b, 0xed);
}

static void test_named_bad(void **state) {
    (void)state;
    assert_int_equal(cc_parse("notacolor", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("reddish", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("   ", &C), CC_ERR_SYNTAX);
}

static void test_transparent_currentcolor(void **state) {
    (void)state;
    assert_int_equal(cc_parse("transparent", &C), CC_TRANSPARENT);
    assert_int_equal(cc_parse("currentColor", &C), CC_CURRENT_COLOR);
    assert_int_equal(cc_parse("CURRENTCOLOR", &C), CC_CURRENT_COLOR);
    assert_int_equal(cc_parse("  transparent  ", &C), CC_TRANSPARENT);
}

static void test_hsl(void **state) {
    (void)state;
    assert_int_equal(cc_parse("hsl(0,100%,50%)", &C), CC_OK);
    assert_int_equal(C.r, 255); assert_int_equal(C.g, 0); assert_int_equal(C.b, 0);
}

static void test_hsl_120(void **state) {
    (void)state;
    /* hsl(120,100%,50%) = green */
    assert_int_equal(cc_parse("hsl(120,100%,50%)", &C), CC_OK);
    assert_int_equal(C.r, 0); assert_int_equal(C.g, 255); assert_int_equal(C.b, 0);
}

static void test_hsl_240(void **state) {
    (void)state;
    /* hsl(240,100%,50%) = blue */
    assert_int_equal(cc_parse("hsl(240,100%,50%)", &C), CC_OK);
    assert_int_equal(C.r, 0); assert_int_equal(C.g, 0); assert_int_equal(C.b, 255);
}

static void test_hsla(void **state) {
    (void)state;
    assert_int_equal(cc_parse("hsla(0,100%,50%,0.5)", &C), CC_OK);
    assert_int_equal(C.r, 255); assert_int_equal(C.g, 0); assert_int_equal(C.b, 0);
}

static void test_hsl_out_of_range(void **state) {
    (void)state;
    assert_int_equal(cc_parse("hsl(0,50%,150%)", &C), CC_ERR_SYNTAX);     /* L > 100 */
    assert_int_equal(cc_parse("hsl(0,150%,50%)", &C), CC_ERR_SYNTAX);     /* S > 100 */
    assert_int_equal(cc_parse("hsl(0,50)", &C), CC_ERR_SYNTAX);           /* too few */
    assert_int_equal(cc_parse("HSL(0,100%,50%,0,0)", &C), CC_ERR_SYNTAX); /* too many */
}

static void test_unsupported_syntax(void **state) {
    (void)state;
    assert_int_equal(cc_parse("var(--x)", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("color-mix(in srgb, red, blue)", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("hwb(0,100%,0%)", &C), CC_ERR_SYNTAX);
}

/* --- CSS Color 4 section 8-9: oklab/oklch/lab/lch (2026-09-29) ---
 * Tailwind v4 writes its whole palette in oklch(); huggingface.co lost ~765
 * colour declarations to it. References: CSS Color 4 sample values and the
 * Tailwind v4 palette (sRGB fallbacks it publishes). One unit of rounding slack
 * per channel. */
static void expect_near(const char *tok, int r, int g, int b) {
    cc_rgb c;
    assert_int_equal(cc_parse(tok, &c), CC_OK);
    assert_int_in_range(c.r, r > 0 ? r - 1 : 0, r < 255 ? r + 1 : 255);
    assert_int_in_range(c.g, g > 0 ? g - 1 : 0, g < 255 ? g + 1 : 255);
    assert_int_in_range(c.b, b > 0 ? b - 1 : 0, b < 255 ? b + 1 : 255);
}

static void test_oklch_oklab(void **state) {
    (void)state;
    expect_near("oklch(70.7% .022 261.325)", 0x99, 0xa1, 0xaf);   /* tailwind gray-400 */
    expect_near("oklch(62.8% 0.2577 29.23)", 255, 0, 0);
    expect_near("oklch(0% 0 0)", 0, 0, 0);
    expect_near("oklch(1 0 none)", 255, 255, 255);
    expect_near("OKLCH(62.8% 0.2577 29.23deg / 50%)", 255, 0, 0);
    expect_near("oklch(62.8% 64.4% 0.5102turn)", 0, 179, 153);   /* independent reference computation */
    expect_near("oklab(0.628 0.2249 0.1258)", 255, 0, 0);
    expect_near("oklab(62.8% 56.2% 31.5%)", 255, 0, 0);
    /* Out of the sRGB gamut: clamped per channel, still a colour. */
    cc_rgb c;
    assert_int_equal(cc_parse("oklch(70% 0.4 150)", &c), CC_OK);
}

static void test_lab_lch(void **state) {
    (void)state;
    expect_near("lab(54.29 80.8 69.89)", 255, 0, 0);
    expect_near("lab(54.29% 64.6% 55.9%)", 255, 0, 0);
    expect_near("lch(54.29 106.84 40.85)", 255, 0, 0);
    expect_near("lab(100 0 0)", 255, 255, 255);
}

static void test_lab_family_malformed(void **state) {
    (void)state;
    cc_rgb c;
    assert_int_equal(cc_parse("oklch(50% 0.1)", &c), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("oklch(50%, 0.1, 20)", &c), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("oklch(50% 0.1 20 30)", &c), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("oklch(50% 0.1 20deg20)", &c), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("oklch(x 0.1 20)", &c), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("oklab(0.5 0.1 0.1 / )", &c), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("lab(50 0 0", &c), CC_ERR_SYNTAX);
}

static void test_pack_unpack(void **state) {
    (void)state;
    cc_rgb a = { 0x12, 0x34, 0x56 };
    int p = cc_pack(a);
    assert_int_equal(p, 0x123456);
    assert_true(p >= 0);
    cc_rgb b = cc_unpack(p);
    assert_int_equal(b.r, a.r); assert_int_equal(b.g, a.g); assert_int_equal(b.b, a.b);

    /* High bits ignored by unpack. */
    cc_rgb c = cc_unpack((int)0x7fabcdef);
    assert_int_equal(c.r, 0xab); assert_int_equal(c.g, 0xcd); assert_int_equal(c.b, 0xef);
}


/* CSS Color 4: an rgb() channel is a <number> or <percentage> and an hsl()
 * saturation/lightness is a <percentage> -- none of them is restricted to whole
 * digits. Requiring integers dropped the colour, and with it the DECLARATION, which
 * is how a page written by a preprocessor (`hsl(0,0%,15.8333333333%)`, the shape a
 * SASS/LESS colour function emits) lost its entire palette. */
static void test_hsl_fractional_percentages(void **state) {
    (void)state;
    assert_int_equal(cc_parse("hsl(0,0%,15.8333333333%)", &C), CC_OK);
    /* 15.83% of 255 = 40.4 -> 40. An integer-only parser could not see the .83 at
     * all, so the whole declaration vanished. */
    assert_int_equal(C.r, 40); assert_int_equal(C.g, 40); assert_int_equal(C.b, 40);

    assert_int_equal(cc_parse("hsl(0,0%,91.862745098%)", &C), CC_OK);
    assert_int_equal(C.r, 234); assert_int_equal(C.g, 234); assert_int_equal(C.b, 234);
}

/* A fractional hue is a <number> too (and hsl() takes an <angle>, whose bare-number
 * form is degrees). */
static void test_hsl_fractional_hue(void **state) {
    (void)state;
    assert_int_equal(cc_parse("hsl(120.5,100%,50%)", &C), CC_OK);
    assert_int_equal(C.r, 0); assert_int_equal(C.g, 255);
}

/* rgb() channels take fractional numbers and fractional percentages. */
static void test_rgb_fractional(void **state) {
    (void)state;
    assert_int_equal(cc_parse("rgb(127.5, 0, 0)", &C), CC_OK);
    assert_int_equal(C.r, 128); assert_int_equal(C.g, 0); assert_int_equal(C.b, 0);
    assert_int_equal(cc_parse("rgb(50.5%, 0%, 0%)", &C), CC_OK);
    assert_int_equal(C.r, 129);
}

/* A leading-dot number is a valid <number> (CSS Syntax 4.3.12): `.5` must parse. */
static void test_leading_dot_number(void **state) {
    (void)state;
    assert_int_equal(cc_parse("rgba(0, 0, 0, .5)", &C), CC_OK);
    assert_int_equal(cc_parse("hsl(0,.5%,50%)", &C), CC_OK);
}

/* Out-of-range and malformed values still fail closed -- widening the grammar to
 * fractions must not widen it to junk. */
static void test_fractional_still_fails_closed(void **state) {
    (void)state;
    assert_int_not_equal(cc_parse("hsl(0,0%,150.5%)", &C), CC_OK);
    assert_int_not_equal(cc_parse("rgb(300.5, 0, 0)", &C), CC_OK);
    assert_int_not_equal(cc_parse("rgb(1.2.3, 0, 0)", &C), CC_OK);
    assert_int_not_equal(cc_parse("hsl(0,0%,5x%)", &C), CC_OK);
    assert_int_not_equal(cc_parse("rgb(., 0, 0)", &C), CC_OK);
}

/* CSS Color 4 space-separated components with optional slash alpha (spec/css_color.md):
 * the measured overlay/border idiom of real pages (`rgb(0 0 0 / 75%)`). rgb()/rgba()
 * (and hsl()/hsla()) are aliases; arity comes from the alpha, not the name. */
static void test_rgb_space_separated(void **state) {
    (void)state;
    assert_int_equal(cc_parse("rgb(0 0 0 / 75%)", &C), CC_OK);
    assert_int_equal(C.r, 0); assert_int_equal(C.g, 0); assert_int_equal(C.b, 0);

    assert_int_equal(cc_parse("rgb(229 233 240 / 50%)", &C), CC_OK);
    assert_int_equal(C.r, 229); assert_int_equal(C.g, 233); assert_int_equal(C.b, 240);

    assert_int_equal(cc_parse("rgb(255 0 0)", &C), CC_OK);
    assert_int_equal(C.r, 255); assert_int_equal(C.g, 0); assert_int_equal(C.b, 0);

    assert_int_equal(cc_parse("rgba(10 20 30 / 0.5)", &C), CC_OK);
    assert_int_equal(C.r, 10); assert_int_equal(C.g, 20); assert_int_equal(C.b, 30);

    assert_int_equal(cc_parse("RGB(100% 0% 50% / 100%)", &C), CC_OK);
    assert_int_equal(C.r, 255); assert_int_equal(C.g, 0); assert_int_equal(C.b, 128);
}

static void test_hsl_space_separated(void **state) {
    (void)state;
    assert_int_equal(cc_parse("hsl(0 0% 0% / 50%)", &C), CC_OK);
    assert_int_equal(C.r, 0); assert_int_equal(C.g, 0); assert_int_equal(C.b, 0);

    assert_int_equal(cc_parse("hsl(120 100% 50%)", &C), CC_OK);
    assert_int_equal(C.r, 0); assert_int_equal(C.g, 255); assert_int_equal(C.b, 0);

    assert_int_equal(cc_parse("hsla(240 100% 50% / .5)", &C), CC_OK);
    assert_int_equal(C.r, 0); assert_int_equal(C.g, 0); assert_int_equal(C.b, 255);
}

/* Mixing the two grammars, or a dangling slash, still fails closed. */
static void test_space_separated_still_fails_closed(void **state) {
    (void)state;
    assert_int_not_equal(cc_parse("rgb(0, 0, 0 / 50%)", &C), CC_OK);
    assert_int_not_equal(cc_parse("rgb(0 0)", &C), CC_OK);
    assert_int_not_equal(cc_parse("rgb(0 0 0 /)", &C), CC_OK);
    assert_int_not_equal(cc_parse("rgb(0 0 0 // 50%)", &C), CC_OK);
    assert_int_not_equal(cc_parse("rgb(0  0  0  0)", &C), CC_OK);
    assert_int_not_equal(cc_parse("rgb(256 0 0)", &C), CC_OK);
    /* Out-of-range alpha clamps at computed-value time (CSS Color 4), like the
     * legacy `rgba(0,0,0,2)` the parser already accepts: valid, discarded. */
    assert_int_equal(cc_parse("rgb(0 0 0 / 150%)", &C), CC_OK);
    assert_int_not_equal(cc_parse("hsl(0 50% 50% / 0.5 / 0.5)", &C), CC_OK);
    assert_int_not_equal(cc_parse("hsl(0 150% 50%)", &C), CC_OK);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_null_args),
        cmocka_unit_test(test_hex_short),
        cmocka_unit_test(test_hex_short_alpha),
        cmocka_unit_test(test_hex_long),
        cmocka_unit_test(test_hex_long_alpha),
        cmocka_unit_test(test_hex_bad),
        cmocka_unit_test(test_rgb_integer),
        cmocka_unit_test(test_rgba_integer),
        cmocka_unit_test(test_rgb_percent),
        cmocka_unit_test(test_rgb_out_of_range),
        cmocka_unit_test(test_named),
        cmocka_unit_test(test_named_bad),
        cmocka_unit_test(test_transparent_currentcolor),
        cmocka_unit_test(test_hsl),
        cmocka_unit_test(test_hsl_120),
        cmocka_unit_test(test_hsl_240),
        cmocka_unit_test(test_hsla),
        cmocka_unit_test(test_hsl_out_of_range),
        cmocka_unit_test(test_hsl_fractional_percentages),
        cmocka_unit_test(test_hsl_fractional_hue),
        cmocka_unit_test(test_rgb_fractional),
        cmocka_unit_test(test_leading_dot_number),
        cmocka_unit_test(test_fractional_still_fails_closed),
        cmocka_unit_test(test_rgb_space_separated),
        cmocka_unit_test(test_hsl_space_separated),
        cmocka_unit_test(test_space_separated_still_fails_closed),
        cmocka_unit_test(test_unsupported_syntax),
        cmocka_unit_test(test_pack_unpack),
        cmocka_unit_test(test_oklch_oklab),
        cmocka_unit_test(test_lab_lch),
        cmocka_unit_test(test_lab_family_malformed),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
