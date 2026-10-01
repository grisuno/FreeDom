/*
 * TDD suite for js_geom (spec/js_geom.md): the pure geometry table a trusted
 * page's JS measures elements with.
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cmocka.h>

#include "js_geom.h"

static void test_empty_table(void **state) {
    (void)state;
    jg_table t;
    jg_init(&t);
    assert_int_equal(t.n, 0);
    assert_int_equal(jg_finish(&t), 0);
    assert_null(jg_find(&t, 3));
    jg_free(&t);
    jg_free(&t);            /* idempotent */
    jg_free(NULL);
}

static void test_add_and_find(void **state) {
    (void)state;
    jg_table t;
    jg_init(&t);
    assert_int_equal(jg_add(&t, 7, 10.4, 20.6, 100.0, 50.0), 0);
    assert_int_equal(jg_add(&t, 2, 0, 0, 5, 5), 0);
    assert_int_equal(jg_finish(&t), 0);
    const jg_rect *r = jg_find(&t, 7);
    assert_non_null(r);
    assert_int_equal(r->x, 10);
    assert_int_equal(r->y, 21);
    assert_int_equal(r->w, 100);
    assert_int_equal(r->h, 50);
    assert_non_null(jg_find(&t, 2));
    assert_null(jg_find(&t, 3));
    jg_free(&t);
}

/* Several fragments of one element merge into their bounding box. */
static void test_same_node_unions(void **state) {
    (void)state;
    jg_table t;
    jg_init(&t);
    jg_add(&t, 4, 10, 10, 20, 10);     /* 10..30 x 10..20 */
    jg_add(&t, 4, 0, 40, 50, 10);      /*  0..50 x 40..50 */
    assert_int_equal(jg_finish(&t), 0);
    assert_int_equal(t.n, 1);
    const jg_rect *r = jg_find(&t, 4);
    assert_non_null(r);
    assert_int_equal(r->x, 0);
    assert_int_equal(r->y, 10);
    assert_int_equal(r->w, 50);
    assert_int_equal(r->h, 40);
    jg_free(&t);
}

static void test_add_rejects_and_clamps(void **state) {
    (void)state;
    jg_table t;
    jg_init(&t);
    assert_int_equal(jg_add(&t, DOM_NODE_NONE, 1, 1, 1, 1), 0);
    assert_int_equal(jg_add(&t, 1, NAN, 1, 1, 1), 0);
    assert_int_equal(jg_add(&t, 1, 1, INFINITY, 1, 1), 0);
    assert_int_equal(t.n, 0);
    assert_int_equal(jg_add(&t, 1, -1e12, 1e12, -5, 1e12), 0);
    jg_finish(&t);
    const jg_rect *r = jg_find(&t, 1);
    assert_non_null(r);
    assert_int_equal(r->x, -JG_COORD_MAX);
    assert_int_equal(r->y, JG_COORD_MAX);
    assert_int_equal(r->w, 0);
    assert_int_equal(r->h, JG_COORD_MAX);
    assert_int_equal(jg_add(NULL, 1, 0, 0, 0, 0), -1);
    jg_free(&t);
}

static void test_capacity_bound(void **state) {
    (void)state;
    jg_table t;
    jg_init(&t);
    for (uint32_t i = 0; i < JG_MAX_RECTS; ++i)
        assert_int_equal(jg_add(&t, (dom_node_id)i, 0, 0, 1, 1), 0);
    assert_int_equal(jg_add(&t, 999999, 0, 0, 1, 1), -1);
    assert_int_equal(t.n, JG_MAX_RECTS);
    jg_free(&t);
}

/* Parent chain: 3 -> 2 -> 1 -> NONE, and 4 -> 2. */
static dom_node_id chain_parent(void *ctx, dom_node_id n) {
    (void)ctx;
    switch (n) {
        case 3: return 2;
        case 4: return 2;
        case 2: return 1;
        default: return DOM_NODE_NONE;
    }
}

/* A boxless wrapper measures the union of its descendants. */
static void test_aggregate_unions_into_ancestors(void **state) {
    (void)state;
    jg_table t;
    jg_init(&t);
    jg_add(&t, 3, 10, 100, 200, 20);
    jg_add(&t, 4, 30, 130, 100, 20);
    jg_add(&t, 1, 0, 0, 1000, 10);
    assert_int_equal(jg_aggregate(&t, chain_parent, NULL), 0);
    const jg_rect *w = jg_find(&t, 2);
    assert_non_null(w);
    assert_int_equal(w->x, 10);
    assert_int_equal(w->y, 100);
    assert_int_equal(w->w, 200);
    assert_int_equal(w->h, 50);
    const jg_rect *root = jg_find(&t, 1);
    assert_non_null(root);
    assert_int_equal(root->y, 0);
    assert_int_equal(root->h, 150);
    assert_int_equal(root->w, 1000);
    /* descendants unchanged */
    assert_int_equal(jg_find(&t, 3)->h, 20);
    jg_free(&t);
}

static dom_node_id cyclic_parent(void *ctx, dom_node_id n) {
    (void)ctx;
    return (n == 5) ? 6 : 5;
}

static void test_aggregate_cycle_terminates(void **state) {
    (void)state;
    jg_table t;
    jg_init(&t);
    jg_add(&t, 5, 0, 0, 10, 10);
    assert_int_equal(jg_aggregate(&t, cyclic_parent, NULL), 0);
    assert_non_null(jg_find(&t, 6));
    assert_int_equal(jg_aggregate(NULL, cyclic_parent, NULL), -1);
    assert_int_equal(jg_aggregate(&t, NULL, NULL), -1);
    jg_free(&t);
}

static void test_wire_roundtrip(void **state) {
    (void)state;
    jg_table t, u;
    jg_init(&t);
    jg_init(&u);
    t.scroll_x = 0; t.scroll_y = 40; t.view_w = 1000; t.view_h = 700;
    t.doc_w = 1000; t.doc_h = 3000;
    jg_add(&t, 9, 1, 2, 3, 4);
    jg_add(&t, 1, -5, 6, 7, 8);
    jg_finish(&t);
    size_t n = jg_wire_len(&t);
    assert_int_equal(n, JG_HEADER_N + 1 + 2 * JG_RECT_N);
    int32_t *buf = (int32_t *)calloc(n, sizeof *buf);
    assert_non_null(buf);
    assert_int_equal(jg_encode(&t, buf, n - 1), -1);
    assert_int_equal(jg_encode(&t, buf, n), 0);
    assert_int_equal(jg_decode(buf, n, &u), 0);
    assert_int_equal(u.n, 2);
    assert_int_equal(u.scroll_y, 40);
    assert_int_equal(u.view_h, 700);
    assert_int_equal(u.doc_h, 3000);
    assert_int_equal(jg_find(&u, 1)->x, -5);
    assert_int_equal(jg_hash(&t), jg_hash(&u));
    u.r[0].h += 1;
    assert_true(jg_hash(&t) != jg_hash(&u));
    free(buf);
    jg_free(&t);
    jg_free(&u);
}

static void test_decode_fails_closed(void **state) {
    (void)state;
    jg_table u;
    jg_init(&u);
    int32_t hdr[JG_HEADER_N + 1 + JG_RECT_N] = {0, 0, 1000, 700, 1000, 3000, 1, 4, 0, 0, 5, 5};
    /* too short */
    assert_int_equal(jg_decode(hdr, JG_HEADER_N, &u), -1);
    /* count does not match the length */
    hdr[JG_HEADER_N] = 2;
    assert_int_equal(jg_decode(hdr, sizeof hdr / sizeof hdr[0], &u), -1);
    /* giant count */
    hdr[JG_HEADER_N] = (int32_t)(JG_MAX_RECTS + 1);
    assert_int_equal(jg_decode(hdr, sizeof hdr / sizeof hdr[0], &u), -1);
    /* negative count */
    hdr[JG_HEADER_N] = -1;
    assert_int_equal(jg_decode(hdr, sizeof hdr / sizeof hdr[0], &u), -1);
    /* negative size */
    hdr[JG_HEADER_N] = 1;
    hdr[JG_HEADER_N + 4] = -3;
    assert_int_equal(jg_decode(hdr, sizeof hdr / sizeof hdr[0], &u), -1);
    /* out-of-range viewport */
    hdr[JG_HEADER_N + 4] = 5;
    hdr[2] = -1;
    assert_int_equal(jg_decode(hdr, sizeof hdr / sizeof hdr[0], &u), -1);
    assert_int_equal(u.n, 0);
    /* valid */
    hdr[2] = 1000;
    assert_int_equal(jg_decode(hdr, sizeof hdr / sizeof hdr[0], &u), 0);
    assert_int_equal(u.n, 1);
    assert_int_equal(jg_decode(NULL, 7, &u), -1);
    assert_int_equal(u.n, 0);
    jg_free(&u);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_empty_table),
        cmocka_unit_test(test_add_and_find),
        cmocka_unit_test(test_same_node_unions),
        cmocka_unit_test(test_add_rejects_and_clamps),
        cmocka_unit_test(test_capacity_bound),
        cmocka_unit_test(test_aggregate_unions_into_ancestors),
        cmocka_unit_test(test_aggregate_cycle_terminates),
        cmocka_unit_test(test_wire_roundtrip),
        cmocka_unit_test(test_decode_fails_closed),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
