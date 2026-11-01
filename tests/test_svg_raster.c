/* tests/test_svg_raster.c -- CMocka suite for SVG-as-image rasterization (sr_).
 * spec/svg_raster.md section 4. */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "svg_raster.h"

static img_status raster(const char *s, img_pixels *px) {
    return sr_rasterize((const uint8_t *)s, strlen(s), px);
}

static uint32_t pixel(const img_pixels *px, uint32_t x, uint32_t y) {
    uint32_t v;
    memcpy(&v, px->data + (size_t)y * px->stride + (size_t)x * 4u, sizeof v);
    return v;
}

static void test_sniff(void **state) {
    (void)state;
    const char *yes[] = {
        "<svg xmlns=\"http://www.w3.org/2000/svg\"/>",
        "\xEF\xBB\xBF  <svg>",
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!-- logo -->\n<svg viewBox=\"0 0 1 1\">",
        "<?xml version=\"1.0\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"x\"><svg>",
        "<SVG>",
    };
    for (size_t i = 0; i < sizeof yes / sizeof *yes; ++i)
        assert_int_equal(sr_sniff((const uint8_t *)yes[i], strlen(yes[i])), 1);
    const char *no[] = { "\x89PNG\r\n\x1a\n", "<html><svg></svg></html>", "", "<!-- unterminated",
                         "<svgfoo>", "   " };
    for (size_t i = 0; i < sizeof no / sizeof *no; ++i)
        assert_int_equal(sr_sniff((const uint8_t *)no[i], strlen(no[i])), 0);
    assert_int_equal(sr_sniff(NULL, 4), 0);
}

static void test_rect_fills_red(void **state) {
    (void)state;
    img_pixels px;
    assert_int_equal(raster("<svg width=\"20\" height=\"10\"><rect width=\"20\" height=\"10\" "
                            "fill=\"red\"/></svg>", &px), IMG_OK);
    /* 20x10 CSS px is under SR_MIN_RASTER: drawn at density 4, 80x40 device px. */
    assert_int_equal(px.scale, 4);
    assert_int_equal(px.width, 80);
    assert_int_equal(px.height, 40);
    assert_int_equal(px.stride, 320);
    assert_int_equal(pixel(&px, 40, 20), 0xFFFF0000u);
    img_pixels_free(&px);
}

static void test_viewbox_sets_size_and_transparent_bg(void **state) {
    (void)state;
    img_pixels px;
    assert_int_equal(raster("<?xml version=\"1.0\"?><!-- c --><svg viewBox=\"0 0 40 20\">"
                            "<circle cx=\"10\" cy=\"10\" r=\"5\" fill=\"#0000ff\"/></svg>", &px),
                     IMG_OK);
    assert_int_equal(px.width / px.scale, 40);
    assert_int_equal(px.height / px.scale, 20);
    assert_int_equal(pixel(&px, 10 * px.scale, 10 * px.scale), 0xFF0000FFu);
    assert_int_equal(pixel(&px, 35 * px.scale, 10 * px.scale), 0u);   /* transparent */
    img_pixels_free(&px);
}

static void test_large_svg_is_not_oversampled(void **state) {
    (void)state;
    img_pixels px;
    assert_int_equal(raster("<svg width=\"200\" height=\"50\"><rect width=\"9\" height=\"9\"/></svg>", &px),
                     IMG_OK);
    assert_int_equal(px.scale, 1);
    assert_int_equal(px.width, 200);
    img_pixels_free(&px);
}

static void test_huge_scales_down(void **state) {
    (void)state;
    img_pixels px;
    assert_int_equal(raster("<svg width=\"100000\" height=\"10\"><rect width=\"100000\" "
                            "height=\"10\"/></svg>", &px), IMG_OK);
    assert_true(px.width <= SR_MAX_DIM);
    assert_true(px.height >= 1);
    img_pixels_free(&px);
}

static void test_garbage_fails_closed(void **state) {
    (void)state;
    img_pixels px;
    memset(&px, 0xAB, sizeof px);
    assert_int_not_equal(raster("not an svg at all", &px), IMG_OK);
    assert_null(px.data);
    assert_int_equal(px.width, 0);
    assert_int_not_equal(sr_rasterize(NULL, 3, &px), IMG_OK);
    assert_int_not_equal(raster("<svg width=\"10\" height=\"10\"></svg>", &px), IMG_OK);
    assert_null(px.data);
}

static void test_text_is_skipped_not_fatal(void **state) {
    (void)state;
    img_pixels px;
    assert_int_equal(raster("<svg width=\"30\" height=\"10\"><rect width=\"5\" height=\"5\"/>"
                            "<text x=\"10\" y=\"8\">Hi</text></svg>", &px), IMG_OK);
    assert_int_equal(pixel(&px, 2 * px.scale, 2 * px.scale), 0xFF000000u);
    assert_int_equal(pixel(&px, 15 * px.scale, 6 * px.scale), 0u);
    img_pixels_free(&px);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_sniff),
        cmocka_unit_test(test_rect_fills_red),
        cmocka_unit_test(test_viewbox_sets_size_and_transparent_bg),
        cmocka_unit_test(test_large_svg_is_not_oversampled),
        cmocka_unit_test(test_huge_scales_down),
        cmocka_unit_test(test_garbage_fails_closed),
        cmocka_unit_test(test_text_is_skipped_not_fatal),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
