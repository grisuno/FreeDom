#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "css_text.h"
#include "css_decl.h"
#include "css.h"

static void test_fontfamily_bucket(void **state)
{
    (void)state;
    assert_int_equal(ct_interp_fontfamily("serif"), CSS_FF_SERIF);
    assert_int_equal(ct_interp_fontfamily("ARIAL"), CSS_FF_SANS);
    assert_int_equal(ct_interp_fontfamily("bogus-family-xyz"), -1);
}

static void test_opacity_shapes(void **state)
{
    (void)state;
    assert_int_equal(ct_interp_opacity("0.5"), 50);
    assert_int_equal(ct_interp_opacity("100%"), 100);
    assert_int_equal(ct_interp_opacity("bogus"), -1);
}

static void test_whitespace_direction(void **state)
{
    (void)state;
    assert_true(ct_interp_whitespace("nowrap") >= 0);
    assert_int_equal(ct_interp_whitespace("bogus"), -1);
    assert_true(ct_interp_direction("rtl") >= 0);
}

static void test_shadow_needs_both_offsets(void **state)
{
    (void)state;
    css_decl d[8];
    assert_int_equal(ct_expand_shadow("1px", d, 8), 0);
    assert_int_equal(ct_expand_shadow("1px 2px red", d, 8), 3);
    assert_int_equal(ct_expand_shadow("none", d, 8), 3);
    assert_int_equal(ct_expand_shadow("url(x) 1px 2px", d, 8), 0);
}

static void test_aspect_ratio(void **state)
{
    (void)state;
    int num = 0, den = 0;
    assert_int_equal(ct_interp_aspect_ratio("16/9", &num, &den), 1);
    assert_true(num > 0 && den > 0);
    num = den = -1;
    assert_int_equal(ct_interp_aspect_ratio("bogus", &num, &den), 1);
    assert_int_equal(num, 0);
    assert_int_equal(den, 0);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_fontfamily_bucket),
        cmocka_unit_test(test_opacity_shapes),
        cmocka_unit_test(test_whitespace_direction),
        cmocka_unit_test(test_shadow_needs_both_offsets),
        cmocka_unit_test(test_aspect_ratio),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
