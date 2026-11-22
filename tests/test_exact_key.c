#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cmocka.h>

#include "exact_key.h"

static void test_same_puts_equal(void **state) {
    (void)state;
    ek_key a, b;
    ek_init(&a);
    ek_init(&b);
    double d = 1000.5;
    int i = 7;
    ek_put(&a, &d, sizeof d);
    ek_put(&a, &i, sizeof i);
    ek_put(&b, &d, sizeof d);
    ek_put(&b, &i, sizeof i);
    assert_int_equal(ek_equal(&a, &b), 1);
    assert_int_equal(ek_equal(&a, &a), 1);
    ek_free(&a);
    ek_free(&b);
}

static void test_byte_or_length_differs(void **state) {
    (void)state;
    ek_key a, b;
    ek_init(&a);
    ek_init(&b);
    ek_put(&a, "abcd", 4);
    ek_put(&b, "abce", 4);
    assert_int_equal(ek_equal(&a, &b), 0);
    ek_reset(&b);
    ek_put(&b, "abc", 3);
    assert_int_equal(ek_equal(&a, &b), 0);
    ek_put(&b, "d", 1);
    assert_int_equal(ek_equal(&a, &b), 1);
    ek_reset(&a);
    ek_reset(&b);
    assert_int_equal(ek_equal(&a, &b), 1);
    ek_free(&a);
    ek_free(&b);
}

static void test_growth_across_many_puts(void **state) {
    (void)state;
    ek_key a, b;
    ek_init(&a);
    ek_init(&b);
    for (int i = 0; i < 5000; ++i) {
        ek_put(&a, &i, sizeof i);
        ek_put(&b, &i, sizeof i);
    }
    assert_int_equal(a.n, 5000 * sizeof(int));
    assert_int_equal(ek_equal(&a, &b), 1);
    int last = 4999, other = 1;
    memcpy(b.b + b.n - sizeof last, &other, sizeof other);
    assert_int_equal(ek_equal(&a, &b), 0);
    (void)last;
    ek_free(&a);
    ek_free(&b);
}

static void test_bad_never_equal(void **state) {
    (void)state;
    ek_key a, b;
    ek_init(&a);
    ek_init(&b);
    ek_put(&a, NULL, 3);
    assert_int_equal(a.bad, 1);
    assert_int_equal(ek_equal(&a, &a), 0);
    assert_int_equal(ek_equal(&a, &b), 0);
    ek_reset(&a);
    assert_int_equal(a.bad, 0);
    assert_int_equal(ek_equal(&a, &b), 1);
    ek_put(&b, "x", (size_t)-1);
    assert_int_equal(b.bad, 1);
    ek_reset(&b);
    unsigned char *big = calloc(EK_MAX_BYTES, 1);
    assert_non_null(big);
    ek_put(&b, big, EK_MAX_BYTES);
    assert_int_equal(b.bad, 0);
    ek_put(&b, big, 1);
    assert_int_equal(b.bad, 1);
    assert_int_equal(ek_equal(&b, &b), 0);
    free(big);
    ek_free(&a);
    ek_free(&b);
}

static void test_swap_and_null_safety(void **state) {
    (void)state;
    ek_key a, b;
    ek_init(&a);
    ek_init(&b);
    ek_put(&a, "left", 4);
    ek_put(&b, "right!", 6);
    unsigned char *pa = a.b;
    ek_swap(&a, &b);
    assert_ptr_equal(b.b, pa);
    assert_int_equal(a.n, 6);
    assert_int_equal(b.n, 4);
    assert_memory_equal(a.b, "right!", 6);
    ek_free(&a);
    ek_free(&a);
    assert_null(a.b);
    assert_int_equal(a.n, 0);
    ek_free(&b);
    ek_init(NULL);
    ek_reset(NULL);
    ek_put(NULL, "x", 1);
    ek_swap(NULL, &a);
    ek_free(NULL);
    assert_int_equal(ek_equal(NULL, &a), 0);
    assert_int_equal(ek_equal(&a, NULL), 0);
    ek_put(&a, NULL, 0);
    assert_int_equal(a.bad, 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_same_puts_equal),
        cmocka_unit_test(test_byte_or_length_differs),
        cmocka_unit_test(test_growth_across_many_puts),
        cmocka_unit_test(test_bad_never_equal),
        cmocka_unit_test(test_swap_and_null_safety),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
