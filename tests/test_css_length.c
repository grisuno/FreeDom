/*
 * test_css_length -- ATDD suite for the canonical CSS <length> resolver.
 * Mirrors the Given/When/Then table in spec/css_length.md section 4.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <cmocka.h>

#include "css_length.h"
#include "css.h"

/* Absolute tolerance for a px comparison. Lengths are doubles all the way to
 * the painter, so exactness is expected; this only absorbs the last ulp of a
 * division like 96/2.54. */
#define EPS 1e-9

static double px_of(const char *value, const cl_ctx *ctx) {
    double px = -12345.0;
    assert_int_equal(cl_resolve(value, ctx, &px), CL_OK);
    return px;
}

static void expect_err(const char *value, const cl_ctx *ctx, cl_status want) {
    double px = -12345.0;
    assert_int_equal(cl_resolve(value, ctx, &px), want);
    assert_true(px == -12345.0);  /* untouched on failure */
}

/* 1 / 2: a unitless zero is a length; a unitless non-zero is not. */
static void test_unitless(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    assert_true(fabs(px_of("0", &c)) < EPS);
    assert_true(fabs(px_of("-0", &c)) < EPS);
    assert_true(fabs(px_of("0.0", &c)) < EPS);
    expect_err("12", &c, CL_ERR_UNIT);
    expect_err("1.5", &c, CL_ERR_UNIT);
}

/* 3 / 4: the absolute family, with 1in == 96px as the anchor. */
static void test_absolute_units(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    assert_true(fabs(px_of("10px", &c) - 10.0) < EPS);
    assert_true(fabs(px_of("10pt", &c) - (10.0 * 96.0 / 72.0)) < EPS);

    /* Six spellings of one inch. */
    assert_true(fabs(px_of("1in",     &c) - 96.0) < EPS);
    assert_true(fabs(px_of("6pc",     &c) - 96.0) < EPS);
    assert_true(fabs(px_of("72pt",    &c) - 96.0) < EPS);
    assert_true(fabs(px_of("2.54cm",  &c) - 96.0) < EPS);
    assert_true(fabs(px_of("25.4mm",  &c) - 96.0) < EPS);
    assert_true(fabs(px_of("101.6Q",  &c) - 96.0) < EPS);
}

/* 5 / 6: em follows the element, rem follows the root -- they are NOT aliases. */
static void test_font_relative_em_rem(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    c.font_size = 20.0;
    c.root_font_size = 10.0;
    assert_true(fabs(px_of("2em",  &c) - 40.0) < EPS);
    assert_true(fabs(px_of("2rem", &c) - 20.0) < EPS);

    /* rem is independent of the element's own size. */
    c.font_size = 100.0;
    assert_true(fabs(px_of("2rem", &c) - 20.0) < EPS);
}

/* 7 / 8: spec fallbacks apply only until a real metric is supplied. */
static void test_font_metric_fallbacks(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    c.font_size = 20.0;

    assert_true(fabs(px_of("1ex",  &c) - 20.0 * CL_FALLBACK_EX_RATIO)  < EPS);
    assert_true(fabs(px_of("1ch",  &c) - 20.0 * CL_FALLBACK_CH_RATIO)  < EPS);
    assert_true(fabs(px_of("1cap", &c) - 20.0 * CL_FALLBACK_CAP_RATIO) < EPS);
    assert_true(fabs(px_of("1ic",  &c) - 20.0 * CL_FALLBACK_IC_RATIO)  < EPS);

    c.x_height = 8.0;
    c.zero_advance = 9.0;
    assert_true(fabs(px_of("1ex", &c) - 8.0) < EPS);
    assert_true(fabs(px_of("1ch", &c) - 9.0) < EPS);
}

/* lh / rlh resolve against the line box, and follow element vs root like em/rem. */
static void test_line_height_units(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    c.line_height = 24.0;
    c.root_line_height = 18.0;
    assert_true(fabs(px_of("2lh",  &c) - 48.0) < EPS);
    assert_true(fabs(px_of("2rlh", &c) - 36.0) < EPS);
}

/* 9 / 10: vmin takes the SHORTER axis and vmax the LONGER one -- the old code
 * aliased vmin to vh and vmax to vw, which is only right for a landscape
 * viewport and silently wrong for a portrait one. */
static void test_viewport_units(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    c.viewport_w = 1920.0;
    c.viewport_h = 1080.0;
    assert_true(fabs(px_of("50vw",   &c) - 960.0) < EPS);
    assert_true(fabs(px_of("50vh",   &c) - 540.0) < EPS);
    assert_true(fabs(px_of("50vmin", &c) - 540.0) < EPS);
    assert_true(fabs(px_of("50vmax", &c) - 960.0) < EPS);

    /* Portrait: the two must swap. An alias table cannot do this. */
    c.viewport_w = 800.0;
    c.viewport_h = 1600.0;
    assert_true(fabs(px_of("50vmin", &c) - 400.0) < EPS);
    assert_true(fabs(px_of("50vmax", &c) - 800.0) < EPS);

    /* Logical axes in horizontal-tb, and the s/l/d viewport variants. */
    assert_true(fabs(px_of("50vi",   &c) - 400.0) < EPS);
    assert_true(fabs(px_of("50vb",   &c) - 800.0) < EPS);
    assert_true(fabs(px_of("50svw",  &c) - 400.0) < EPS);
    assert_true(fabs(px_of("50lvh",  &c) - 800.0) < EPS);
    assert_true(fabs(px_of("50dvmin", &c) - 400.0) < EPS);
}

/* 11: ASCII case-insensitive unit names. */
static void test_case_insensitive(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    assert_true(fabs(px_of("10PX", &c) - 10.0) < EPS);
    assert_true(fabs(px_of("10Px", &c) - 10.0) < EPS);
    assert_true(fabs(px_of("1IN",  &c) - 96.0) < EPS);
    assert_true(fabs(px_of("101.6q", &c) - 96.0) < EPS);
    assert_true(fabs(px_of("2REM", &c) - 32.0) < EPS);
}

/* 12: the full CSS number grammar, sign included. */
static void test_number_grammar(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    assert_true(fabs(px_of("-5px",  &c) + 5.0)  < EPS);
    assert_true(fabs(px_of("+5px",  &c) - 5.0)  < EPS);
    assert_true(fabs(px_of(".5px",  &c) - 0.5)  < EPS);
    assert_true(fabs(px_of("5.px",  &c) - 5.0)  < EPS);
    assert_true(fabs(px_of("1e2px", &c) - 100.0) < EPS);
    assert_true(fabs(px_of("-1.5e1px", &c) + 15.0) < EPS);
}

/* 13 / 19: percentages and container-query units are not <length>. */
static void test_not_a_length(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    expect_err("50%",  &c, CL_ERR_UNIT);
    expect_err("1cqw", &c, CL_ERR_UNIT);
    expect_err("1cqi", &c, CL_ERR_UNIT);
    expect_err("45deg", &c, CL_ERR_UNIT);
    expect_err("2s",   &c, CL_ERR_UNIT);
    expect_err("96dpi", &c, CL_ERR_UNIT);
}

/* 14 / 15 / 16: whitespace handling and syntax failures. */
static void test_syntax(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    assert_true(fabs(px_of("10px ", &c) - 10.0) < EPS);
    assert_true(fabs(px_of(" 10px", &c) - 10.0) < EPS);
    assert_true(fabs(px_of("\t10px\t", &c) - 10.0) < EPS);

    expect_err("10 px", &c, CL_ERR_SYNTAX);   /* a dimension is ONE token */
    expect_err("10px;", &c, CL_ERR_SYNTAX);
    expect_err("abc",   &c, CL_ERR_SYNTAX);
    expect_err("",      &c, CL_ERR_SYNTAX);
    expect_err("px",    &c, CL_ERR_SYNTAX);
    expect_err("-",     &c, CL_ERR_SYNTAX);
}

/* 17: NULL arguments. */
static void test_null_args(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    double px = 7.0;
    assert_int_equal(cl_resolve(NULL, &c, &px), CL_ERR_NULL_ARG);
    assert_int_equal(cl_resolve("1px", NULL, &px), CL_ERR_NULL_ARG);
    assert_int_equal(cl_resolve("1px", &c, NULL), CL_ERR_NULL_ARG);
    assert_true(px == 7.0);
}

/* 18: non-finite results are rejected; merely huge ones are NOT -- clamping to
 * CSS_LEN_MAX is the emitter's anti-DoS policy, not the unit's business. */
static void test_range(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    expect_err("1e400px", &c, CL_ERR_RANGE);   /* overflows to inf */
    expect_err("-1e400in", &c, CL_ERR_RANGE);
    assert_true(px_of("1e300px", &c) > (double)CSS_LEN_MAX);  /* finite: resolves */

    char big[CL_MAX_TOKEN + 32];
    for (size_t i = 0; i < sizeof big - 1; ++i) big[i] = '1';
    big[sizeof big - 1] = '\0';
    double px = -1.0;
    assert_int_not_equal(cl_resolve(big, &c, &px), CL_OK);
}

/* cl_unit_scale is the same table reached without reassembling text. */
static void test_unit_scale(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    c.font_size = 20.0;
    double s = 0.0;

    assert_int_equal(cl_unit_scale("pt", 0, &c, &s), CL_OK);
    assert_true(fabs(s - 96.0 / 72.0) < EPS);
    assert_int_equal(cl_unit_scale("em", 0, &c, &s), CL_OK);
    assert_true(fabs(s - 20.0) < EPS);
    /* Explicit length, so a unit sitting inside a larger buffer works. */
    assert_int_equal(cl_unit_scale("emXX", 2, &c, &s), CL_OK);
    assert_true(fabs(s - 20.0) < EPS);
    assert_int_equal(cl_unit_scale("%", 0, &c, &s), CL_ERR_UNIT);
    assert_int_equal(cl_unit_scale(NULL, 0, &c, &s), CL_ERR_NULL_ARG);
}

/* The font-relative classifier: em-family yes, rem/rlh and absolutes no. This
 * is what replaces the hand-written whitelist in interp_fontsize_ex. */
static void test_font_relative_classifier(void **state) {
    (void)state;
    assert_true(cl_unit_is_font_relative("em", 0));
    assert_true(cl_unit_is_font_relative("ex", 0));
    assert_true(cl_unit_is_font_relative("ch", 0));
    assert_true(cl_unit_is_font_relative("cap", 0));
    assert_true(cl_unit_is_font_relative("ic", 0));
    assert_true(cl_unit_is_font_relative("lh", 0));

    assert_false(cl_unit_is_font_relative("rem", 0));
    assert_false(cl_unit_is_font_relative("rlh", 0));
    assert_false(cl_unit_is_font_relative("px", 0));
    assert_false(cl_unit_is_font_relative("pt", 0));
    assert_false(cl_unit_is_font_relative("vw", 0));
    assert_false(cl_unit_is_font_relative("%", 0));
    assert_false(cl_unit_is_font_relative(NULL, 0));
}

static void test_is_length_unit(void **state) {
    (void)state;
    assert_true(cl_is_length_unit("px", 0));
    assert_true(cl_is_length_unit("Q", 0));
    assert_true(cl_is_length_unit("rlh", 0));
    assert_true(cl_is_length_unit("dvmax", 0));
    assert_false(cl_is_length_unit("%", 0));
    assert_false(cl_is_length_unit("cqw", 0));
    assert_false(cl_is_length_unit("", 0));
    assert_false(cl_is_length_unit(NULL, 0));
}

/* The initial context is the CSS initial state, and the viewport defaults to
 * the NORMALIZED desktop -- never the real window (anti-fingerprinting). */
static void test_initial_ctx(void **state) {
    (void)state;
    cl_ctx c = cl_ctx_initial();
    assert_true(fabs(c.font_size - CL_INITIAL_FONT_SIZE) < EPS);
    assert_true(fabs(c.root_font_size - CL_INITIAL_FONT_SIZE) < EPS);
    assert_true(fabs(c.viewport_w - (double)CSS_MEDIA_DEFAULT_WIDTH) < EPS);
    assert_true(fabs(c.viewport_h - (double)CSS_MEDIA_DEFAULT_HEIGHT) < EPS);
    assert_true(c.x_height <= 0.0);
    assert_true(c.zero_advance <= 0.0);
}


/* cl_number is the CSS Syntax 4.3.12 grammar, shared by lengths, colour
 * channels, opacity and transform arguments. `.5` is the case that used to be
 * rejected engine-wide. */
static void test_cl_number(void **state) {
    (void)state;
    double v; const char *e;

    assert_true(cl_number(".5", &v, &e));      assert_true(fabs(v - 0.5) < EPS);
    assert_true(cl_number("5.", &v, &e));      assert_true(fabs(v - 5.0) < EPS);
    assert_true(cl_number("-.25", &v, &e));    assert_true(fabs(v + 0.25) < EPS);
    assert_true(cl_number("+1.5", &v, &e));    assert_true(fabs(v - 1.5) < EPS);
    assert_true(cl_number("1e3", &v, &e));     assert_true(fabs(v - 1000.0) < EPS);
    assert_true(cl_number("1E-2", &v, &e));    assert_true(fabs(v - 0.01) < EPS);

    /* endp points at the first unconsumed byte, so a caller can read the unit. */
    assert_true(cl_number(".75em", &v, &e));
    assert_true(fabs(v - 0.75) < EPS);
    assert_string_equal(e, "em");

    /* A malformed exponent is not consumed: "1e" is the number 1 then "e". */
    assert_true(cl_number("1e", &v, &e));
    assert_true(fabs(v - 1.0) < EPS);
    assert_string_equal(e, "e");

    assert_false(cl_number(".", &v, &e));
    assert_false(cl_number("abc", &v, &e));
    assert_false(cl_number("", &v, &e));
    assert_false(cl_number(NULL, &v, &e));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_unitless),
        cmocka_unit_test(test_absolute_units),
        cmocka_unit_test(test_font_relative_em_rem),
        cmocka_unit_test(test_font_metric_fallbacks),
        cmocka_unit_test(test_line_height_units),
        cmocka_unit_test(test_viewport_units),
        cmocka_unit_test(test_case_insensitive),
        cmocka_unit_test(test_number_grammar),
        cmocka_unit_test(test_not_a_length),
        cmocka_unit_test(test_syntax),
        cmocka_unit_test(test_null_args),
        cmocka_unit_test(test_range),
        cmocka_unit_test(test_unit_scale),
        cmocka_unit_test(test_font_relative_classifier),
        cmocka_unit_test(test_is_length_unit),
        cmocka_unit_test(test_initial_ctx),
        cmocka_unit_test(test_cl_number),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
