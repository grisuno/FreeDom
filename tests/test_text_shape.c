/*
 * test_text_shape — CMocka suite for the HarfBuzz shaping helper (tsh_).
 *
 * The shaped TEXT is hostile remote content; the FONTS are local. These tests
 * verify the fail-closed input contract (which needs no font), and the shaping
 * invariants (count/positivity/monotonicity/determinism/consistency) on a host
 * that resolves a font. On a font-less host they assert the fallback contract
 * (TSH_ERR_UNAVAIL / measure < 0), so the suite is green either way.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#include <cmocka.h>

#include "text_shape.h"
#include "css.h"

static const tsh_font SANS = { .family = CSS_FF_SANS, .bold = 0, .italic = 0 };

/* --- fail-closed input contract (no font needed) --- */

static void test_null_and_bad_inputs(void **state) {
    (void)state;
    cairo_glyph_t g[64];
    size_t n = 123; double adv = 7.0;

    /* NULL font */
    assert_int_equal(tsh_shape(NULL, 16.0, "x", 1, g, 64, &n, &adv), TSH_ERR_INPUT);
    /* NULL text with len>0 */
    assert_int_equal(tsh_shape(&SANS, 16.0, NULL, 3, g, 64, &n, &adv), TSH_ERR_INPUT);
    /* NULL out buffer */
    assert_int_equal(tsh_shape(&SANS, 16.0, "x", 1, NULL, 64, &n, &adv), TSH_ERR_INPUT);
    /* NULL out_n / out_adv */
    assert_int_equal(tsh_shape(&SANS, 16.0, "x", 1, g, 64, NULL, &adv), TSH_ERR_INPUT);
    assert_int_equal(tsh_shape(&SANS, 16.0, "x", 1, g, 64, &n, NULL), TSH_ERR_INPUT);
    /* cap 0 */
    assert_int_equal(tsh_shape(&SANS, 16.0, "x", 1, g, 0, &n, &adv), TSH_ERR_INPUT);
    /* non-positive / non-finite px */
    assert_int_equal(tsh_shape(&SANS, 0.0,   "x", 1, g, 64, &n, &adv), TSH_ERR_INPUT);
    assert_int_equal(tsh_shape(&SANS, -3.0,  "x", 1, g, 64, &n, &adv), TSH_ERR_INPUT);
    assert_int_equal(tsh_shape(&SANS, NAN,   "x", 1, g, 64, &n, &adv), TSH_ERR_INPUT);
    assert_int_equal(tsh_shape(&SANS, INFINITY, "x", 1, g, 64, &n, &adv), TSH_ERR_INPUT);
    /* oversize slice */
    assert_int_equal(tsh_shape(&SANS, 16.0, "x", (size_t)TSH_MAX_TEXT + 1, g, 64, &n, &adv),
                     TSH_ERR_INPUT);

    /* measure mirrors the fail-closed contract: < 0 on bad input. */
    assert_true(tsh_measure(NULL, 16.0, "x", 1) < 0.0);
    assert_true(tsh_measure(&SANS, 0.0, "x", 1) < 0.0);
}

static void test_empty_slice_is_ok(void **state) {
    (void)state;
    cairo_glyph_t g[8];
    size_t n = 99; double adv = 99.0;
    /* Empty input is OK regardless of backend: nothing to shape. */
    assert_int_equal(tsh_shape(&SANS, 16.0, "", 0, g, 8, &n, &adv), TSH_OK);
    assert_int_equal((int)n, 0);
    assert_true(adv == 0.0);
    assert_true(tsh_measure(&SANS, 16.0, "", 0) == 0.0);
}

/* --- shaping invariants (real font path; fallback contract otherwise) --- */

static void test_shape_ascii(void **state) {
    (void)state;
    cairo_glyph_t g[64];
    size_t n = 0; double adv = 0.0;
    tsh_status st = tsh_shape(&SANS, 16.0, "ABCD", 4, g, 64, &n, &adv);

    if (!tsh_ready()) {
        assert_int_equal(st, TSH_ERR_UNAVAIL);
        assert_true(tsh_measure(&SANS, 16.0, "ABCD", 4) < 0.0);
        return;
    }
    /* "ABCD" never ligates in a standard font: one glyph per cap. */
    assert_int_equal(st, TSH_OK);
    assert_int_equal((int)n, 4);
    assert_true(adv > 0.0);
    /* Glyph x positions are non-decreasing and bounded by the total advance. */
    for (size_t i = 1; i < n; ++i)
        assert_true(g[i].x >= g[i - 1].x);
    assert_true(g[n - 1].x <= adv + 1.0);
    assert_true(g[0].x >= 0.0);
}

static void test_determinism(void **state) {
    (void)state;
    if (!tsh_ready()) { skip(); }
    cairo_glyph_t a[64], b[64];
    size_t na = 0, nb = 0; double aa = 0.0, ab = 0.0;
    assert_int_equal(tsh_shape(&SANS, 18.0, "Freedom", 7, a, 64, &na, &aa), TSH_OK);
    assert_int_equal(tsh_shape(&SANS, 18.0, "Freedom", 7, b, 64, &nb, &ab), TSH_OK);
    assert_int_equal((int)na, (int)nb);
    assert_true(aa == ab);
    for (size_t i = 0; i < na; ++i) {
        assert_int_equal((int)a[i].index, (int)b[i].index);
        assert_true(a[i].x == b[i].x);
        assert_true(a[i].y == b[i].y);
    }
}

static void test_measure_matches_shape(void **state) {
    (void)state;
    if (!tsh_ready()) { skip(); }
    cairo_glyph_t g[64];
    size_t n = 0; double adv = 0.0;
    assert_int_equal(tsh_shape(&SANS, 20.0, "kerning", 7, g, 64, &n, &adv), TSH_OK);
    double m = tsh_measure(&SANS, 20.0, "kerning", 7);
    assert_true(m >= 0.0);
    /* Same shaper, same slice: measure must equal the shaped total advance. */
    assert_true(fabs(m - adv) < 1e-6);
}

static void test_overflow_cap(void **state) {
    (void)state;
    if (!tsh_ready()) { skip(); }
    cairo_glyph_t g[2];
    size_t n = 123; double adv = 7.0;
    /* 10 non-ligating glyphs cannot fit a cap of 2: fail closed, no OOB write. */
    tsh_status st = tsh_shape(&SANS, 16.0, "ABCDEFGHIJ", 10, g, 2, &n, &adv);
    assert_int_equal(st, TSH_ERR_OVERFLOW);
}

static void test_draw_paints(void **state) {
    (void)state;
    if (!tsh_ready()) { skip(); }
    cairo_surface_t *s = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 200, 40);
    cairo_t *cr = cairo_create(s);
    cairo_set_source_rgb(cr, 0, 0, 0);
    /* Exercises the cairo_show_glyphs path under ASan. */
    tsh_status st = tsh_draw(cr, &SANS, 16.0, 4.0, 24.0, "shape me", 8);
    assert_int_equal(st, TSH_OK);
    cairo_destroy(cr);
    cairo_surface_destroy(s);
}

static int teardown(void **state) {
    (void)state;
    tsh_shutdown();
    return 0;
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_null_and_bad_inputs),
        cmocka_unit_test(test_empty_slice_is_ok),
        cmocka_unit_test(test_shape_ascii),
        cmocka_unit_test(test_determinism),
        cmocka_unit_test(test_measure_matches_shape),
        cmocka_unit_test(test_overflow_cap),
        cmocka_unit_test(test_draw_paints),
    };
    return cmocka_run_group_tests(tests, NULL, teardown);
}
