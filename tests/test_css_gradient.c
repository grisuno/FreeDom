#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "css_gradient.h"
#include "css.h"

static void test_linear_basic(void **state)
{
    (void)state;
    css_decl d[16];
    char urls[4][CSS_URL_MAX];
    size_t nurl = 0;
    int n = cg_expand_bg_image("linear-gradient(red, blue)", d, 16, urls, &nurl, 4);
    assert_true(n > 2);
    assert_int_equal(d[0].prop, P_BG_GRAD_ANGLE);
    assert_int_equal(d[1].prop, P_BG_GRAD_N);
    assert_int_equal(d[1].ival, 2);
}

static void test_junk_drops(void **state)
{
    (void)state;
    css_decl d[16];
    char urls[4][CSS_URL_MAX];
    size_t nurl = 0;
    int n = cg_expand_bg_image("linear-gradient(red)", d, 16, urls, &nurl, 4);
    assert_true(n <= 2);
}

static void test_url_single(void **state)
{
    (void)state;
    css_decl d[16];
    char urls[4][CSS_URL_MAX];
    size_t nurl = 0;
    int n = cg_expand_bg_image("url(http://x/y.png)", d, 16, urls, &nurl, 4);
    assert_true(n >= 1);
    assert_int_equal(nurl, 1);
}

static void test_shorthand_resets(void **state)
{
    (void)state;
    css_decl d[16];
    char urls[4][CSS_URL_MAX];
    size_t nurl = 0;
    int n = cg_expand_background("red", d, 16, urls, &nurl, 4);
    assert_true(n >= 2);
    assert_int_equal(d[0].prop, P_BG);
}

static void test_shorthand_broken_drops(void **state)
{
    (void)state;
    css_decl d[16];
    char urls[4][CSS_URL_MAX];
    size_t nurl = 0;
    int n = cg_expand_background("linear-gradient(red)", d, 16, urls, &nurl, 4);
    assert_int_equal(n, 0);
}

static void test_degree_prelude_edges(void **state)
{
    (void)state;
    css_decl d[16];
    char urls[4][CSS_URL_MAX];
    size_t nurl = 0;
    int n = cg_expand_bg_image("linear-gradient(90deg, red, blue)", d, 16, urls, &nurl, 4);
    assert_true(n > 2);
    assert_int_equal(d[0].prop, P_BG_GRAD_ANGLE);
    assert_int_equal(d[0].ival, 90);
    nurl = 0;
    n = cg_expand_bg_image("linear-gradient(0deg, red, blue)", d, 16, urls, &nurl, 4);
    assert_true(n > 2);
    assert_int_equal(d[0].ival, 0);
    nurl = 0;
    n = cg_expand_bg_image("linear-gradient(19deg, red, blue)", d, 16, urls, &nurl, 4);
    assert_true(n > 2);
    assert_int_equal(d[0].ival, 19);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_linear_basic),
        cmocka_unit_test(test_junk_drops),
        cmocka_unit_test(test_url_single),
        cmocka_unit_test(test_shorthand_resets),
        cmocka_unit_test(test_shorthand_broken_drops),
        cmocka_unit_test(test_degree_prelude_edges),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
