#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cmocka.h>

#include "box_blur.h"

static long mass(const unsigned char *b, int n) {
    long s = 0;
    for (int i = 0; i < n; ++i) s += b[i];
    return s;
}

static void test_box_sizes(void **state) {
    (void)state;
    int s[3] = { -1, -1, -1 };
    assert_int_equal(bb_box_sizes(0.0, s), 0);
    assert_int_equal(s[0], -1);
    assert_int_equal(bb_box_sizes(-3.0, s), 0);
    assert_int_equal(bb_box_sizes(4.0, s), 1);
    for (int k = 0; k < 3; ++k) {
        assert_true(s[k] >= 1);
        assert_true(s[k] % 2 == 1);
    }
    /* The three variances add up to sigma^2 (box width w has variance (w^2-1)/12). */
    double var = 0.0;
    for (int k = 0; k < 3; ++k) var += ((double)s[k] * s[k] - 1.0) / 12.0;
    assert_true(var > 16.0 * 0.7 && var < 16.0 * 1.3);
}

static void test_impulse_conserves_mass_and_is_symmetric(void **state) {
    (void)state;
    enum { W = 41, H = 41 };
    unsigned char b[W * H];
    memset(b, 0, sizeof b);
    b[20 * W + 20] = 255;
    assert_int_equal(bb_blur_a8(b, W, H, W, 2.0), 1);
    long m = mass(b, W * H);
    assert_true(m > 255 * 98 / 100 - 40 && m < 255 * 102 / 100 + 40);
    assert_true(b[20 * W + 20] < 255);
    assert_true(b[20 * W + 20] > 0);
    assert_int_equal(b[20 * W + 17], b[20 * W + 23]);
    assert_int_equal(b[17 * W + 20], b[23 * W + 20]);
    assert_int_equal(b[0], 0);
}

static void test_zero_sigma_is_identity(void **state) {
    (void)state;
    unsigned char b[64], c[64];
    for (int i = 0; i < 64; ++i) b[i] = c[i] = (unsigned char)(i * 3);
    assert_int_equal(bb_blur_a8(b, 8, 8, 8, 0.0), 0);
    assert_memory_equal(b, c, sizeof b);
}

static void test_uniform_interior_unchanged(void **state) {
    (void)state;
    enum { W = 60, H = 60 };
    unsigned char b[W * H];
    memset(b, 200, sizeof b);
    assert_int_equal(bb_blur_a8(b, W, H, W, 2.0), 1);
    assert_int_equal(b[30 * W + 30], 200);
    /* The edge fades: outside the buffer is transparent. */
    assert_true(b[0] < 200);
}

static void test_invalid_arguments(void **state) {
    (void)state;
    unsigned char b[16];
    assert_int_equal(bb_blur_a8(NULL, 4, 4, 4, 1.0), -1);
    assert_int_equal(bb_blur_a8(b, 0, 4, 4, 1.0), -1);
    assert_int_equal(bb_blur_a8(b, 4, 4, 3, 1.0), -1);
    assert_int_equal(bb_blur_a8(b, 8192, 4096, 8192, 1.0), -1);
}

/* --- ink bounds: blur only where there is something to blur --------------------------------- */

static void put_px(unsigned char *d, int stride, int x, int y, unsigned char a) {
    unsigned char *p = d + (size_t)y * (size_t)stride + (size_t)x * 4u;
    p[0] = p[1] = p[2] = a; p[3] = a;
}

static void test_ink_rect_empty_surface_has_no_ink(void **state) {
    (void)state;
    unsigned char *d = calloc(40u * 30u * 4u, 1);
    int r[4];
    assert_int_equal(bb_ink_rect(d, 40, 30, 160, 5.0, r), 0);
    free(d);
}

static void test_ink_rect_grows_by_the_blur_reach_and_clamps(void **state) {
    (void)state;
    unsigned char *d = calloc(100u * 80u * 4u, 1);
    put_px(d, 400, 50, 40, 255);
    int r[4], sizes[3];
    assert_int_equal(bb_box_sizes(4.0, sizes), 1);
    int reach = sizes[0] / 2 + sizes[1] / 2 + sizes[2] / 2;
    assert_int_equal(bb_ink_rect(d, 100, 80, 400, 4.0, r), 1);
    assert_int_equal(r[0], 50 - reach);
    assert_int_equal(r[1], 40 - reach);
    assert_int_equal(r[2], 50 + reach + 1);
    assert_int_equal(r[3], 40 + reach + 1);
    put_px(d, 400, 0, 0, 255);
    assert_int_equal(bb_ink_rect(d, 100, 80, 400, 4.0, r), 1);
    assert_int_equal(r[0], 0);
    assert_int_equal(r[1], 0);
    free(d);
}

static void test_ink_rect_covers_every_pixel_the_blur_can_touch(void **state) {
    (void)state;
    enum { W = 64, H = 48 };
    unsigned char *a = calloc(W * H, 1), *b = calloc(W * H, 1);
    a[20 * W + 30] = 255;
    memcpy(b, a, W * H);
    assert_int_equal(bb_blur_a8(a, W, H, W, 3.0), 1);
    unsigned char *argb = calloc(W * H * 4u, 1);
    put_px(argb, W * 4, 30, 20, 255);
    int r[4];
    assert_int_equal(bb_ink_rect(argb, W, H, W * 4, 3.0, r), 1);
    for (int y = 0; y < H; ++y)
        for (int x = 0; x < W; ++x)
            if (a[y * W + x] != 0)
                assert_true(x >= r[0] && x < r[2] && y >= r[1] && y < r[3]);
    free(a); free(b); free(argb);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_box_sizes),
        cmocka_unit_test(test_impulse_conserves_mass_and_is_symmetric),
        cmocka_unit_test(test_zero_sigma_is_identity),
        cmocka_unit_test(test_uniform_interior_unchanged),
        cmocka_unit_test(test_invalid_arguments),
        cmocka_unit_test(test_ink_rect_empty_surface_has_no_ink),
        cmocka_unit_test(test_ink_rect_grows_by_the_blur_reach_and_clamps),
        cmocka_unit_test(test_ink_rect_covers_every_pixel_the_blur_can_touch),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
