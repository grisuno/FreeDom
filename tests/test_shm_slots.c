#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "shm_slots.h"

static void test_alternates_and_never_paints_a_held_slot(void **state) {
    (void)state;
    ss_state s;
    ss_init(&s);
    int a = ss_pick(&s);
    assert_int_equal(a, 0);
    ss_committed(&s, a);                      /* slot 0 is now the compositor's */
    int b = ss_pick(&s);
    assert_int_equal(b, 1);                   /* paints into the OTHER slot */
    ss_committed(&s, b);
    assert_int_equal(ss_pick(&s), -1);        /* both held: defer, never overwrite */
    assert_int_equal(ss_released(&s, 0), 1);
    assert_int_equal(ss_pick(&s), 0);         /* the released one is free again */
}

static void test_release_of_unknown_or_idle_slot_is_ignored(void **state) {
    (void)state;
    ss_state s;
    ss_init(&s);
    assert_int_equal(ss_released(&s, 0), 0);
    assert_int_equal(ss_released(&s, -1), 0);
    assert_int_equal(ss_released(&s, 7), 0);
    ss_committed(&s, 9);                      /* out of range: no effect */
    assert_int_equal(ss_pick(&s), 0);
}

static void test_repaint_before_commit_reuses_the_same_free_slot(void **state) {
    (void)state;
    ss_state s;
    ss_init(&s);
    assert_int_equal(ss_pick(&s), 0);
    assert_int_equal(ss_pick(&s), 0);         /* painting twice before a commit stays on slot 0 */
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_alternates_and_never_paints_a_held_slot),
        cmocka_unit_test(test_release_of_unknown_or_idle_slot_is_ignored),
        cmocka_unit_test(test_repaint_before_commit_reuses_the_same_free_slot),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
