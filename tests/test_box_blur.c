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

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_box_sizes),
        cmocka_unit_test(test_impulse_conserves_mass_and_is_symmetric),
        cmocka_unit_test(test_zero_sigma_is_identity),
        cmocka_unit_test(test_uniform_interior_unchanged),
        cmocka_unit_test(test_invalid_arguments),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
