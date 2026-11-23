/* Tests for group_index (spec/group_index.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "group_index.h"

static void test_groups_stable_and_excludes_out_of_range(void **state) {
    (void)state;
    const int keys[] = {1, -1, 0, 1, 5, 0};
    size_t offs[3] = {9, 9, 9}, items[6] = {9, 9, 9, 9, 9, 9};
    assert_int_equal(gi_build(keys, 6, 2, offs, items), 4);
    assert_int_equal(offs[0], 0);
    assert_int_equal(offs[1], 2);
    assert_int_equal(offs[2], 4);
    assert_int_equal(items[0], 2);
    assert_int_equal(items[1], 5);
    assert_int_equal(items[2], 0);
    assert_int_equal(items[3], 3);
}

static void test_empty_input(void **state) {
    (void)state;
    size_t offs[4] = {7, 7, 7, 7};
    assert_int_equal(gi_build(NULL, 0, 3, offs, NULL), 0);
    for (int i = 0; i < 4; ++i) assert_int_equal(offs[i], 0);
}

static void test_no_keys(void **state) {
    (void)state;
    const int keys[] = {0, 1};
    size_t offs[1] = {5}, items[2] = {7, 7};
    assert_int_equal(gi_build(keys, 2, 0, offs, items), 0);
    assert_int_equal(offs[0], 0);
    assert_int_equal(items[0], 7);
}

static void test_invalid_arguments(void **state) {
    (void)state;
    const int keys[] = {0};
    size_t offs[2] = {0, 0}, items[1] = {0};
    assert_true(gi_build(keys, 1, 1, NULL, items) == (size_t)-1);
    assert_true(gi_build(NULL, 1, 1, offs, items) == (size_t)-1);
    assert_true(gi_build(keys, 1, 1, offs, NULL) == (size_t)-1);
    assert_true(gi_build(keys, 1, SIZE_MAX, offs, items) == (size_t)-1);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_groups_stable_and_excludes_out_of_range),
        cmocka_unit_test(test_empty_input),
        cmocka_unit_test(test_no_keys),
        cmocka_unit_test(test_invalid_arguments),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
