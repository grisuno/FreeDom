/* Suite for nav_token (spec/nav_token.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <pthread.h>
#include <stdint.h>

#include "nav_token.h"

static void test_new_defaults(void **state) {
    (void)state;
    nt_token *a = nt_new();
    nt_token *b = nt_new();
    assert_non_null(a);
    assert_non_null(b);
    assert_int_equal(nt_cancelled(a), 0);
    assert_int_equal(nt_foreground(a), 1);
    assert_true(nt_id(a) != 0);
    assert_true(nt_id(b) > nt_id(a));
    nt_unref(&a);
    nt_unref(&b);
    assert_null(a);
    assert_null(b);
    nt_unref(&a); /* idempotent */
}

static void test_null_fails_closed(void **state) {
    (void)state;
    assert_int_equal(nt_cancelled(NULL), 1);
    assert_int_equal(nt_foreground(NULL), 0);
    assert_int_equal(nt_id(NULL), 0);
    assert_null(nt_ref(NULL));
    nt_cancel(NULL);
    nt_set_foreground(NULL, 1);
    nt_unref(NULL);
}

static void test_shared_reference(void **state) {
    (void)state;
    nt_token *tab = nt_new();
    nt_token *job = nt_ref(tab);
    assert_ptr_equal(job, tab);
    nt_set_foreground(tab, 0);
    assert_int_equal(nt_foreground(job), 0);
    nt_cancel(tab);
    nt_unref(&tab);                       /* the job still holds it: no UAF below */
    assert_int_equal(nt_cancelled(job), 1);
    nt_unref(&job);
}

static void test_route(void **state) {
    (void)state;
    nt_token *a = nt_new(), *b = nt_new(), *c = nt_new();
    nt_token *parked[4] = { b, NULL, c, NULL };
    int slot = 7;
    assert_int_equal(nt_route(a, a, parked, 4, &slot), NT_DELIVER);
    assert_int_equal(slot, -1);
    assert_int_equal(nt_route(c, a, parked, 4, &slot), NT_PARK);
    assert_int_equal(slot, 2);
    assert_int_equal(nt_route(b, a, parked, 4, NULL), NT_PARK);
    /* A closed tab: nobody holds the token any more. */
    nt_token *gone = nt_new();
    assert_int_equal(nt_route(gone, a, parked, 4, &slot), NT_DROP);
    assert_int_equal(slot, -1);
    /* Cancelled beats everything, even being the active one. */
    nt_cancel(a);
    assert_int_equal(nt_route(a, a, parked, 4, &slot), NT_DROP);
    assert_int_equal(nt_route(NULL, NULL, parked, 4, &slot), NT_DROP);
    assert_int_equal(nt_route(c, a, NULL, 4, &slot), NT_DROP);
    assert_int_equal(nt_route(c, a, parked, -3, &slot), NT_DROP);
    nt_unref(&a); nt_unref(&b); nt_unref(&c); nt_unref(&gone);
}

static void *hammer(void *arg) {
    nt_token *t = (nt_token *)arg;
    for (int i = 0; i < 20000; ++i) {
        nt_token *r = nt_ref(t);
        (void)nt_cancelled(r);
        (void)nt_foreground(r);
        nt_unref(&r);
    }
    nt_unref(&t);
    return NULL;
}

static void test_concurrent_refcount(void **state) {
    (void)state;
    nt_token *t = nt_new();
    pthread_t th[4];
    for (int i = 0; i < 4; ++i) assert_int_equal(pthread_create(&th[i], NULL, hammer, nt_ref(t)), 0);
    nt_cancel(t);
    for (int i = 0; i < 4; ++i) pthread_join(th[i], NULL);
    assert_int_equal(nt_cancelled(t), 1);
    nt_unref(&t); /* last reference: ASan reports a leak or a double free otherwise */
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_defaults),
        cmocka_unit_test(test_null_fails_closed),
        cmocka_unit_test(test_shared_reference),
        cmocka_unit_test(test_route),
        cmocka_unit_test(test_concurrent_refcount),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
