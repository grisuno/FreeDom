/* test_wl_display — CMocka suite for the pure Wayland socket picker. */
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>

#include "wl_display.h"

static void test_picks_lowest(void **state) {
    (void)state;
    const char *n[] = {"bus", "wayland-10", "wayland-1", "wayland-1.lock"};
    char out[32];
    assert_int_equal(wd_pick(n, 4, out, sizeof out), WD_OK);
    assert_string_equal(out, "wayland-1");
}

static void test_ignores_lock_and_garbage(void **state) {
    (void)state;
    const char *n[] = {"wayland-0.lock", "wayland-", "wayland-x1", "wayland-1a", "xwayland-0"};
    char out[32] = "keep";
    assert_int_equal(wd_pick(n, 5, out, sizeof out), WD_NONE);
    assert_string_equal(out, "keep");
}

static void test_small_cap_fails_closed(void **state) {
    (void)state;
    const char *n[] = {"wayland-1"};
    char out[5] = "k";
    assert_int_equal(wd_pick(n, 1, out, sizeof out), WD_NONE);
    assert_string_equal(out, "k");
}

static void test_null_entry(void **state) {
    (void)state;
    const char *n[] = {NULL, "wayland-0"};
    char out[32];
    assert_int_equal(wd_pick(n, 2, out, sizeof out), WD_OK);
    assert_string_equal(out, "wayland-0");
}

int main(void) {
    const struct CMUnitTest t[] = {
        cmocka_unit_test(test_picks_lowest),
        cmocka_unit_test(test_ignores_lock_and_garbage),
        cmocka_unit_test(test_small_cap_fails_closed),
        cmocka_unit_test(test_null_entry),
    };
    return cmocka_run_group_tests(t, NULL, NULL);
}
