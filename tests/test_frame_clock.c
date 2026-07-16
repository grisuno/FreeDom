/*
 * TDD suite for frame_clock (fc_) — pure animation frame scheduler.
 * Red until src/frame_clock.c exists. See spec/frame_clock.md.
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "frame_clock.h"

static void test_init_defaults(void **state) {
    (void)state;
    fc_clock c;
    fc_init(&c);
    assert_int_equal(c.active, 0);
    assert_int_equal(fc_interval_ms(&c), 16);
    assert_int_equal(fc_needs_tick(&c), 0);
}

static void test_set_active_and_needs_tick(void **state) {
    (void)state;
    fc_clock c;
    fc_init(&c);
    assert_int_equal(fc_needs_tick(&c), 0);

    fc_set_active(&c, 1);
    assert_int_equal(fc_needs_tick(&c), 1);

    fc_set_active(&c, 0);
    assert_int_equal(fc_needs_tick(&c), 0);
}

static void test_set_active_twice(void **state) {
    (void)state;
    fc_clock c;
    fc_init(&c);
    fc_set_active(&c, 1);
    fc_set_active(&c, 1);  /* idempotent */
    assert_int_equal(fc_needs_tick(&c), 1);
}

static void test_null_safe(void **state) {
    (void)state;
    fc_init(NULL);
    fc_set_active(NULL, 1);
    assert_int_equal(fc_needs_tick(NULL), 0);
    assert_int_equal(fc_interval_ms(NULL), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init_defaults),
        cmocka_unit_test(test_set_active_and_needs_tick),
        cmocka_unit_test(test_set_active_twice),
        cmocka_unit_test(test_null_safe),
    };
    return cmocka_run_group_tests_name("frame_clock", tests, NULL, NULL);
}
