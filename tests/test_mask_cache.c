#include <math.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <cmocka.h>

#include "mask_cache.h"

static mkc_key key_of(int w, int h, double sigma) {
    mkc_key k = { w, h, 3.0, 3.0, (double)w - 6.0, (double)h - 6.0, 4.0, sigma, 0 };
    return k;
}

static void test_empty_misses(void **state) {
    (void)state;
    mkc_cache *c = mkc_new(1 << 20, 8);
    assert_non_null(c);
    mkc_key k = key_of(10, 10, 1.0);
    int stride = -1;
    assert_null(mkc_get(c, &k, &stride));
    assert_int_equal(mkc_count(c), 0);
    assert_int_equal(mkc_bytes(c), 0);
    mkc_free(c);
}

static void test_put_then_get_same_buffer(void **state) {
    (void)state;
    mkc_cache *c = mkc_new(1 << 20, 8);
    mkc_key k = key_of(10, 7, 1.5);
    unsigned char *b = mkc_put(c, &k, 12);
    assert_non_null(b);
    for (int i = 0; i < 12 * 7; ++i) assert_int_equal(b[i], 0);
    memset(b, 0xab, 12 * 7);
    int stride = 0;
    const unsigned char *g = mkc_get(c, &k, &stride);
    assert_ptr_equal(g, b);
    assert_int_equal(stride, 12);
    assert_int_equal(g[12 * 7 - 1], 0xab);
    assert_int_equal(mkc_count(c), 1);
    assert_int_equal(mkc_bytes(c), 12 * 7);
    mkc_free(c);
}

static void test_any_field_differs_misses(void **state) {
    (void)state;
    mkc_cache *c = mkc_new(1 << 20, 16);
    mkc_key k = key_of(20, 20, 2.0);
    assert_non_null(mkc_put(c, &k, 20));
    int stride;
    mkc_key v[9];
    for (int i = 0; i < 9; ++i) v[i] = k;
    v[0].w = 21; v[1].h = 21; v[2].sx += 0.5; v[3].sy += 0.5; v[4].sw += 1.0;
    v[5].sh += 1.0; v[6].sr = 0.0; v[7].sigma = 2.0000001; v[8].inset = 1;
    for (int i = 0; i < 9; ++i) assert_null(mkc_get(c, &v[i], &stride));
    assert_non_null(mkc_get(c, &k, &stride));
    mkc_key n = k;
    n.sigma = NAN;
    assert_non_null(mkc_put(c, &n, 20));
    assert_null(mkc_get(c, &n, &stride));
    mkc_free(c);
}

static void test_lru_eviction_by_bytes(void **state) {
    (void)state;
    mkc_cache *c = mkc_new(200, 16);
    mkc_key a = key_of(10, 10, 1.0), b = key_of(10, 10, 2.0), d = key_of(10, 10, 3.0);
    int stride;
    assert_non_null(mkc_put(c, &a, 10));
    assert_non_null(mkc_put(c, &b, 10));
    assert_non_null(mkc_get(c, &a, &stride));
    assert_non_null(mkc_put(c, &d, 10));
    assert_non_null(mkc_get(c, &a, &stride));
    assert_null(mkc_get(c, &b, &stride));
    assert_non_null(mkc_get(c, &d, &stride));
    assert_true(mkc_bytes(c) <= 200);
    mkc_free(c);
}

static void test_entry_cap(void **state) {
    (void)state;
    mkc_cache *c = mkc_new(1 << 20, 3);
    int stride;
    for (int i = 0; i < 5; ++i) {
        mkc_key k = key_of(8, 8, 1.0 + i);
        assert_non_null(mkc_put(c, &k, 8));
        assert_true(mkc_count(c) <= 3);
    }
    assert_int_equal(mkc_count(c), 3);
    mkc_key first = key_of(8, 8, 1.0), last = key_of(8, 8, 5.0);
    assert_null(mkc_get(c, &first, &stride));
    assert_non_null(mkc_get(c, &last, &stride));
    mkc_free(c);
}

static void test_over_budget_and_invalid_fail_closed(void **state) {
    (void)state;
    mkc_cache *c = mkc_new(100, 4);
    mkc_key small = key_of(5, 5, 1.0);
    assert_non_null(mkc_put(c, &small, 5));
    mkc_key big = key_of(20, 20, 1.0);
    assert_null(mkc_put(c, &big, 20));
    assert_int_equal(mkc_count(c), 1);
    int stride;
    assert_non_null(mkc_get(c, &small, &stride));
    mkc_key bad = key_of(5, 5, 1.0);
    assert_null(mkc_put(c, &bad, 4));
    bad.w = 0;
    assert_null(mkc_put(c, &bad, 5));
    bad = key_of(5, -1, 1.0);
    assert_null(mkc_put(c, &bad, 5));
    mkc_key huge = { 0x7fffffff, 0x7fffffff, 0, 0, 1, 1, 0, 1, 0 };
    assert_null(mkc_put(c, &huge, 0x7fffffff));
    assert_int_equal(mkc_count(c), 1);
    mkc_free(c);
}

static void test_replace_keeps_one_entry(void **state) {
    (void)state;
    mkc_cache *c = mkc_new(1 << 20, 8);
    mkc_key k = key_of(10, 10, 1.0);
    assert_non_null(mkc_put(c, &k, 10));
    assert_non_null(mkc_put(c, &k, 16));
    assert_int_equal(mkc_count(c), 1);
    assert_int_equal(mkc_bytes(c), 160);
    int stride;
    assert_non_null(mkc_get(c, &k, &stride));
    assert_int_equal(stride, 16);
    mkc_free(c);
}

static void test_clear_and_null_safety(void **state) {
    (void)state;
    assert_null(mkc_new(0, 4));
    assert_null(mkc_new(100, 0));
    mkc_free(NULL);
    mkc_clear(NULL);
    assert_int_equal(mkc_bytes(NULL), 0);
    assert_int_equal(mkc_count(NULL), 0);
    mkc_key k = key_of(4, 4, 1.0);
    int stride;
    assert_null(mkc_get(NULL, &k, &stride));
    assert_null(mkc_put(NULL, &k, 4));
    mkc_cache *c = mkc_new(1000, 4);
    assert_null(mkc_get(c, NULL, &stride));
    assert_null(mkc_put(c, NULL, 4));
    assert_non_null(mkc_put(c, &k, 4));
    assert_null(mkc_get(c, &k, NULL));
    mkc_clear(c);
    mkc_clear(c);
    assert_int_equal(mkc_count(c), 0);
    assert_int_equal(mkc_bytes(c), 0);
    assert_null(mkc_get(c, &k, &stride));
    mkc_free(c);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_empty_misses),
        cmocka_unit_test(test_put_then_get_same_buffer),
        cmocka_unit_test(test_any_field_differs_misses),
        cmocka_unit_test(test_lru_eviction_by_bytes),
        cmocka_unit_test(test_entry_cap),
        cmocka_unit_test(test_over_budget_and_invalid_fail_closed),
        cmocka_unit_test(test_replace_keeps_one_entry),
        cmocka_unit_test(test_clear_and_null_safety),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
