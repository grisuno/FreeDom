/* test_frame_broker -- CMocka suite for the pure iframe tree + postMessage router. */
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "frame_broker.h"

static void test_origin_of(void **state) {
    (void)state;
    char o[FBK_ORIGIN_MAX];
    assert_int_equal(fbk_origin_of("https://Www.Example.com/a?b#c", o, sizeof o), 0);
    assert_string_equal(o, "https://www.example.com");
    assert_int_equal(fbk_origin_of("https://a.com:8443/x", o, sizeof o), 0);
    assert_string_equal(o, "https://a.com:8443");
    assert_int_equal(fbk_origin_of("data:text/html,hi", o, sizeof o), 0);
    assert_string_equal(o, "null");
    assert_int_equal(fbk_origin_of("http://a.com/", o, sizeof o), 0);
    assert_string_equal(o, "null");
    assert_int_equal(fbk_origin_of("https://a.com/", o, 5), -1);
    assert_int_equal(fbk_origin_of(NULL, o, sizeof o), -1);
}

static void build(fbk_table *t, int *a, int *b) {
    assert_int_equal(fbk_init(t, "https://top.com/"), 0);
    assert_int_equal(fbk_add(t, 0, "https://recaptcha.net/anchor", a), 0);
    assert_int_equal(fbk_add(t, 0, "https://other.net/x", b), 0);
}

static void test_parent_top_child_routes(void **state) {
    (void)state;
    fbk_table t; int a, b, d = -9;
    build(&t, &a, &b);
    assert_int_equal(fbk_route(&t, a, FBK_REL_PARENT, 0, "*", 10, &d), FBK_DELIVER);
    assert_int_equal(d, 0);
    assert_int_equal(fbk_route(&t, a, FBK_REL_TOP, 0, "https://top.com", 10, &d), FBK_DELIVER);
    assert_int_equal(d, 0);
    assert_int_equal(fbk_route(&t, 0, FBK_REL_CHILD, a, "https://recaptcha.net", 10, &d), FBK_DELIVER);
    assert_int_equal(d, a);
}

static void test_siblings_not_addressable(void **state) {
    (void)state;
    fbk_table t; int a, b, d;
    build(&t, &a, &b);
    assert_int_equal(fbk_route(&t, a, FBK_REL_CHILD, b, "*", 1, &d), FBK_ERR_FRAME);
    int g;
    assert_int_equal(fbk_add(&t, a, "https://deep.com/", &g), 0);
    assert_int_equal(fbk_route(&t, 0, FBK_REL_CHILD, g, "*", 1, &d), FBK_ERR_FRAME);
}

static void test_target_origin(void **state) {
    (void)state;
    fbk_table t; int a, b, d;
    build(&t, &a, &b);
    assert_int_equal(fbk_route(&t, a, FBK_REL_PARENT, 0, "https://evil.com", 1, &d), FBK_DROP_ORIGIN);
    assert_int_equal(fbk_route(&t, a, FBK_REL_PARENT, 0, "garbage", 1, &d), FBK_DROP_ORIGIN);
    assert_int_equal(fbk_route(&t, a, FBK_REL_PARENT, 0, NULL, 1, &d), FBK_DROP_ORIGIN);
    /* "/" delivers only to the sender's own origin */
    assert_int_equal(fbk_route(&t, a, FBK_REL_PARENT, 0, "/", 1, &d), FBK_DROP_ORIGIN);
    int same;
    assert_int_equal(fbk_add(&t, 0, "https://top.com/other", &same), 0);
    assert_int_equal(fbk_route(&t, 0, FBK_REL_CHILD, same, "/", 1, &d), FBK_DELIVER);
}

static void test_opaque_never_matches_exact(void **state) {
    (void)state;
    fbk_table t; int a, d;
    assert_int_equal(fbk_init(&t, "https://top.com/"), 0);
    assert_int_equal(fbk_add(&t, 0, "data:text/html,x", &a), 0);
    assert_int_equal(fbk_route(&t, 0, FBK_REL_CHILD, a, "null", 1, &d), FBK_DROP_ORIGIN);
    assert_int_equal(fbk_route(&t, 0, FBK_REL_CHILD, a, "*", 1, &d), FBK_DELIVER);
}

static void test_size_and_dead_frames(void **state) {
    (void)state;
    fbk_table t; int a, b, d;
    build(&t, &a, &b);
    assert_int_equal(fbk_route(&t, a, FBK_REL_PARENT, 0, "*", FBK_MAX_MSG + 1, &d), FBK_ERR_SIZE);
    fbk_remove(&t, a);
    assert_int_equal(fbk_route(&t, a, FBK_REL_PARENT, 0, "*", 1, &d), FBK_ERR_FRAME);
    assert_int_equal(fbk_route(&t, 0, FBK_REL_CHILD, a, "*", 1, &d), FBK_ERR_FRAME);
    assert_int_equal(fbk_route(&t, 99, FBK_REL_PARENT, 0, "*", 1, &d), FBK_ERR_FRAME);
    assert_null(fbk_origin(&t, a));
}

static void test_limits_fail_closed(void **state) {
    (void)state;
    fbk_table t; int id = 0, last = 0;
    assert_int_equal(fbk_init(&t, "https://top.com/"), 0);
    for (int i = 0; i < FBK_MAX_DEPTH; ++i)
        assert_int_equal(fbk_add(&t, last, "https://x.com/", &id), 0), last = id;
    assert_int_equal(fbk_add(&t, last, "https://x.com/", &id), -1);   /* too deep */
    assert_int_equal(fbk_add(&t, 42, "https://x.com/", &id), -1);     /* no such parent */
    for (int i = 0; i < FBK_MAX_FRAMES; ++i) (void)fbk_add(&t, 0, "https://y.com/", &id);
    assert_int_equal(fbk_add(&t, 0, "https://y.com/", &id), -1);      /* table full */
}

static void test_remove_subtree_and_top(void **state) {
    (void)state;
    fbk_table t; int a, g, d;
    assert_int_equal(fbk_init(&t, "https://top.com/"), 0);
    assert_int_equal(fbk_add(&t, 0, "https://a.com/", &a), 0);
    assert_int_equal(fbk_add(&t, a, "https://g.com/", &g), 0);
    fbk_remove(&t, a);
    assert_null(fbk_origin(&t, g));
    fbk_remove(&t, 0);                       /* the top cannot be removed */
    assert_non_null(fbk_origin(&t, 0));
    fbk_remove(&t, a);                       /* idempotent */
    assert_int_equal(fbk_route(&t, 0, FBK_REL_PARENT, 0, "*", 1, &d), FBK_ERR_FRAME); /* top has no parent */
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_origin_of),
        cmocka_unit_test(test_parent_top_child_routes),
        cmocka_unit_test(test_siblings_not_addressable),
        cmocka_unit_test(test_target_origin),
        cmocka_unit_test(test_opaque_never_matches_exact),
        cmocka_unit_test(test_size_and_dead_frames),
        cmocka_unit_test(test_limits_fail_closed),
        cmocka_unit_test(test_remove_subtree_and_top),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
