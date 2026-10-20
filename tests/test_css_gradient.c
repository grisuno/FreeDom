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


static void test_radial_prelude_github_glow(void **state)
{
    (void)state;
    cg_radial r;
    assert_int_equal(cg_parse_radial_prelude("141.53% 114.68% at 87.46% 55.27%", &r), 1);
    assert_int_equal(r.size, CG_RS_EXPLICIT);
    assert_int_equal(r.shape, CG_RAD_ELLIPSE);
    assert_int_equal(r.rx, 1415);
    assert_int_equal(r.ry, 1147);
    assert_int_equal(r.cx, 875);
    assert_int_equal(r.cy, 553);
}

static void test_radial_prelude_keywords_and_defaults(void **state)
{
    (void)state;
    cg_radial r;
    assert_int_equal(cg_parse_radial_prelude("circle", &r), 1);
    assert_int_equal(r.shape, CG_RAD_CIRCLE);
    assert_int_equal(r.size, CG_RS_FARTHEST_CORNER);
    assert_int_equal(r.cx, 500);
    assert_int_equal(r.cy, 500);
    assert_int_equal(cg_parse_radial_prelude("ellipse closest-side at 20% 30%", &r), 1);
    assert_int_equal(r.size, CG_RS_CLOSEST_SIDE);
    assert_int_equal(r.cx, 200);
    assert_int_equal(r.cy, 300);
    assert_int_equal(cg_parse_radial_prelude("circle farthest-side at right top", &r), 1);
    assert_int_equal(r.size, CG_RS_FARTHEST_SIDE);
    assert_int_equal(r.cx, 1000);
    assert_int_equal(r.cy, 0);
    assert_int_equal(cg_parse_radial_prelude("at center bottom", &r), 1);
    assert_int_equal(r.cx, 500);
    assert_int_equal(r.cy, 1000);
    assert_int_equal(cg_parse_radial_prelude("at 30px", &r), 1);
    assert_int_equal(r.cx, -31);   /* -(30) - 1 */
    assert_int_equal(r.cy, 500);   /* one value centres the other axis */
}

static void test_radial_prelude_px_sizes_and_failures(void **state)
{
    (void)state;
    cg_radial r;
    assert_int_equal(cg_parse_radial_prelude("600px circle at 50% 0", &r), 1);
    assert_int_equal(r.shape, CG_RAD_CIRCLE);
    assert_int_equal(r.rx, -601);
    assert_int_equal(r.cy, 0);
    assert_int_equal(cg_parse_radial_prelude("100px 40px", &r), 1);
    assert_int_equal(r.shape, CG_RAD_ELLIPSE);
    assert_int_equal(r.rx, -101);
    assert_int_equal(r.ry, -41);
    /* A colour stop is not a prelude. */
    assert_int_equal(cg_parse_radial_prelude("red", &r), 0);
    assert_int_equal(cg_parse_radial_prelude("#fff 20%", &r), 0);
    assert_int_equal(cg_parse_radial_prelude("rgba(0,0,0,.5) 10%", &r), 0);
    /* Malformed or hostile: fail closed. */
    assert_int_equal(cg_parse_radial_prelude("circle 10% 20%", &r), -1);   /* a circle takes one length */
    assert_int_equal(cg_parse_radial_prelude("-5px circle", &r), -1);
    assert_int_equal(cg_parse_radial_prelude("at bogus", &r), -1);
    assert_int_equal(cg_parse_radial_prelude("farthest-corner closest-side", &r), -1);
    assert_int_equal(cg_parse_radial_prelude("", &r), 0);
    assert_int_equal(cg_parse_radial_prelude(NULL, &r), 0);
}

static void test_radial_len_resolution(void **state)
{
    (void)state;
    assert_true(cg_radial_len_px(500, 200.0) == 100.0);
    assert_true(cg_radial_len_px(-31, 200.0) == 30.0);
    assert_true(cg_radial_len_px(1415, 100.0) > 141.4 && cg_radial_len_px(1415, 100.0) < 141.6);
}


static int near_d(double a, double b) { return a > b - 1e-6 && a < b + 1e-6; }

static void test_radial_geometry_keywords(void **state)
{
    (void)state;
    cg_radial r;
    double cx, cy, rx, ry;
    /* default: farthest-corner ellipse centred in a 200 x 100 box. */
    assert_int_equal(cg_parse_radial_prelude("ellipse", &r), 1);
    cg_radial_geometry(&r, 200.0, 100.0, &cx, &cy, &rx, &ry);
    assert_true(near_d(cx, 100.0) && near_d(cy, 50.0));
    assert_true(near_d(rx, 100.0 * 1.4142135623730951) && near_d(ry, 50.0 * 1.4142135623730951));
    /* closest-side ellipse: the nearest edge on each axis. */
    assert_int_equal(cg_parse_radial_prelude("closest-side at 25% 50%", &r), 1);
    cg_radial_geometry(&r, 200.0, 100.0, &cx, &cy, &rx, &ry);
    assert_true(near_d(rx, 50.0) && near_d(ry, 50.0));
    /* circle farthest-side: the largest of the four distances. */
    assert_int_equal(cg_parse_radial_prelude("circle farthest-side at 25% 50%", &r), 1);
    cg_radial_geometry(&r, 200.0, 100.0, &cx, &cy, &rx, &ry);
    assert_true(near_d(rx, 150.0) && near_d(ry, 150.0));
    /* circle farthest-corner: the distance to the far corner. */
    assert_int_equal(cg_parse_radial_prelude("circle at 0 0", &r), 1);
    cg_radial_geometry(&r, 30.0, 40.0, &cx, &cy, &rx, &ry);
    assert_true(near_d(rx, 50.0) && near_d(ry, 50.0));
    /* explicit sizes: the github glow, percentages of the box. */
    assert_int_equal(cg_parse_radial_prelude("141.53% 114.68% at 87.46% 55.27%", &r), 1);
    cg_radial_geometry(&r, 1000.0, 200.0, &cx, &cy, &rx, &ry);
    assert_true(near_d(rx, 1415.0) && near_d(ry, 229.4));
    assert_true(near_d(cx, 875.0) && near_d(cy, 110.6));
    /* a circle with a px radius. */
    assert_int_equal(cg_parse_radial_prelude("600px circle at 50% 0", &r), 1);
    cg_radial_geometry(&r, 1000.0, 200.0, &cx, &cy, &rx, &ry);
    assert_true(near_d(rx, 600.0) && near_d(ry, 600.0) && near_d(cx, 500.0) && near_d(cy, 0.0));
    /* degenerate: never zero or non-finite. */
    assert_int_equal(cg_parse_radial_prelude("closest-side at 0 0", &r), 1);
    cg_radial_geometry(&r, 100.0, 100.0, &cx, &cy, &rx, &ry);
    assert_true(rx > 0.0 && ry > 0.0);
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
        cmocka_unit_test(test_radial_prelude_github_glow),
        cmocka_unit_test(test_radial_prelude_keywords_and_defaults),
        cmocka_unit_test(test_radial_prelude_px_sizes_and_failures),
        cmocka_unit_test(test_radial_len_resolution),
        cmocka_unit_test(test_radial_geometry_keywords),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
