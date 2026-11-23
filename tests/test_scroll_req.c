/* test_scroll_req -- spec/scroll_req.md (tanda 104). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <cmocka.h>

#include "scroll_req.h"

static srq_view view(double scroll, double max, double h) {
    return (srq_view){ .scroll = scroll, .max_scroll = max, .view_h = h };
}

static void test_to_and_by_clamped(void **state) {
    (void)state;
    srq_view v = view(1000.0, 4000.0, 800.0);
    srq_req r = { .kind = SRQ_TO, .y = 2000.0 };
    double out = -1.0;
    assert_int_equal(srq_target(&r, &v, 0, 0, &out), 0);
    assert_true(out == 2000.0);
    r.y = 1e9;
    assert_int_equal(srq_target(&r, &v, 0, 0, &out), 0);
    assert_true(out == 4000.0);
    r.y = -50.0;
    assert_int_equal(srq_target(&r, &v, 0, 0, &out), 0);
    assert_true(out == 0.0);
    r = (srq_req){ .kind = SRQ_BY, .y = -500.0 };
    assert_int_equal(srq_target(&r, &v, 0, 0, &out), 0);
    assert_true(out == 500.0);
    r.y = 10000.0;
    assert_int_equal(srq_target(&r, &v, 0, 0, &out), 0);
    assert_true(out == 4000.0);
}

static void test_element_blocks(void **state) {
    (void)state;
    srq_view v = view(0.0, 10000.0, 800.0);
    srq_req r = { .kind = SRQ_ELEMENT, .block = SRQ_START };
    double out = -1.0;
    assert_int_equal(srq_target(&r, &v, 3000, 3100, &out), 0);
    assert_true(out == 3000.0);
    r.block = SRQ_END;
    assert_int_equal(srq_target(&r, &v, 3000, 3100, &out), 0);
    assert_true(out == 2300.0);                       /* 3100 - 800 */
    r.block = SRQ_CENTER;
    assert_int_equal(srq_target(&r, &v, 3000, 3100, &out), 0);
    assert_true(out == 2650.0);                       /* 3050 - 400 */
}

/* CSSOM View 4.3: nearest leaves a visible box alone, else aligns the nearer edge. */
static void test_element_nearest(void **state) {
    (void)state;
    srq_req r = { .kind = SRQ_ELEMENT, .block = SRQ_NEAREST };
    double out = -1.0;
    srq_view v = view(1000.0, 10000.0, 800.0);
    assert_int_equal(srq_target(&r, &v, 1200, 1300, &out), 0);
    assert_true(out == 1000.0);                       /* fully visible: no move */
    assert_int_equal(srq_target(&r, &v, 500, 600, &out), 0);
    assert_true(out == 500.0);                        /* above: align top */
    assert_int_equal(srq_target(&r, &v, 3000, 3100, &out), 0);
    assert_true(out == 2300.0);                       /* below: align bottom */
    assert_int_equal(srq_target(&r, &v, 900, 2000, &out), 0);
    assert_true(out == 1000.0);                       /* covers the viewport: no move */
    assert_int_equal(srq_target(&r, &v, 1500, 3000, &out), 0);
    assert_true(out == 1500.0);                       /* taller, sticks out below: top */
}

/* Scroll Snap 1: root scroll-padding shrinks the region, target scroll-margin grows it. */
static void test_padding_and_margin(void **state) {
    (void)state;
    srq_view v = view(0.0, 10000.0, 800.0);
    v.pad_top = 80.0;
    v.pad_bottom = 20.0;
    srq_req r = { .kind = SRQ_ELEMENT, .block = SRQ_START, .margin_top = 16.0, .margin_bottom = 4.0 };
    double out = -1.0;
    assert_int_equal(srq_target(&r, &v, 3000, 3100, &out), 0);
    assert_true(out == 3000.0 - 16.0 - 80.0);
    r.block = SRQ_END;
    assert_int_equal(srq_target(&r, &v, 3000, 3100, &out), 0);
    assert_true(out == 3100.0 + 4.0 + 20.0 - 800.0);
    r.block = SRQ_CENTER;            /* box 2984..3104 (mid 3044) to region 80..780 (mid 430) */
    assert_int_equal(srq_target(&r, &v, 3000, 3100, &out), 0);
    assert_true(out == 3044.0 - 430.0);
    /* padding that leaves no room is ignored */
    v.pad_top = 700.0;
    v.pad_bottom = 200.0;
    r.block = SRQ_START;
    assert_int_equal(srq_target(&r, &v, 3000, 3100, &out), 0);
    assert_true(out == 3000.0 - 16.0);
    /* negative padding is 0; negative margin is honored (it is a length, CSS allows it) */
    v.pad_top = -50.0;
    v.pad_bottom = 0.0;
    r.margin_top = -10.0;
    assert_int_equal(srq_target(&r, &v, 3000, 3100, &out), 0);
    assert_true(out == 3010.0);
}

static void test_target_rejects(void **state) {
    (void)state;
    srq_view v = view(0.0, 100.0, 50.0);
    srq_req r = { .kind = SRQ_TO, .y = 10.0 };
    double out = 7.0;
    assert_int_equal(srq_target(NULL, &v, 0, 0, &out), -1);
    assert_int_equal(srq_target(&r, NULL, 0, 0, &out), -1);
    assert_int_equal(srq_target(&r, &v, 0, 0, NULL), -1);
    r.kind = SRQ_NONE;
    assert_int_equal(srq_target(&r, &v, 0, 0, &out), -1);
    r.kind = SRQ_TO;
    r.y = NAN;
    assert_int_equal(srq_target(&r, &v, 0, 0, &out), -1);
    r.y = 1.0;
    v.view_h = 0.0;
    assert_int_equal(srq_target(&r, &v, 0, 0, &out), -1);
    v.view_h = 50.0;
    v.max_scroll = -1.0;
    assert_int_equal(srq_target(&r, &v, 0, 0, &out), -1);
    v.max_scroll = 100.0;
    r.kind = SRQ_ELEMENT;
    assert_int_equal(srq_target(&r, &v, INFINITY, 0, &out), -1);
    assert_true(out == 7.0);
}

static void test_encode_decode_roundtrip(void **state) {
    (void)state;
    srq_req r = { .kind = SRQ_ELEMENT, .behavior = SRQ_SMOOTH, .block = SRQ_CENTER,
                  .y = 0.0, .margin_top = 16.4, .margin_bottom = -3.6, .n = 5, .nsub = 2 };
    int32_t w[SRQ_WIRE_N];
    srq_encode(&r, w);
    srq_req d;
    assert_int_equal(srq_decode(w, 4096, &d), 0);
    assert_int_equal(d.kind, SRQ_ELEMENT);
    assert_int_equal(d.behavior, SRQ_SMOOTH);
    assert_int_equal(d.block, SRQ_CENTER);
    assert_true(d.margin_top == 16.0 && d.margin_bottom == -4.0);
    assert_int_equal(d.n, 5);
    assert_int_equal(d.nsub, 2);
    r = (srq_req){ .kind = SRQ_TO, .y = 1e300 };
    srq_encode(&r, w);
    assert_int_equal(srq_decode(w, 0, &d), 0);
    assert_true(d.y == (double)SRQ_MAX_COORD);
    r.y = NAN;
    srq_encode(&r, w);
    assert_int_equal(srq_decode(w, 0, &d), 0);
    assert_true(d.y == 0.0);
    memset(w, 0, sizeof w);
    assert_int_equal(srq_decode(w, 0, &d), 0);       /* the empty record */
    assert_int_equal(d.kind, SRQ_NONE);
}

static void test_decode_rejects(void **state) {
    (void)state;
    srq_req d;
    int32_t ok[SRQ_WIRE_N] = { SRQ_ELEMENT, SRQ_AUTO, SRQ_START, 0, 0, 0, 3, 1 };
    assert_int_equal(srq_decode(ok, 3, &d), 0);
    int32_t w[SRQ_WIRE_N];
    const struct { int field; int32_t v; } bad[] = {
        { 0, 4 }, { 0, -1 }, { 1, 3 }, { 1, -1 }, { 2, 4 }, { 2, -1 },
        { 3, SRQ_MAX_COORD + 1 }, { 3, -SRQ_MAX_COORD - 1 }, { 4, SRQ_MAX_COORD + 1 },
        { 5, -SRQ_MAX_COORD - 1 }, { 6, 4 }, { 6, -1 }, { 7, 4 }, { 7, -1 }, { 6, 0 },
    };
    for (size_t i = 0; i < sizeof bad / sizeof *bad; ++i) {
        memcpy(w, ok, sizeof w);
        w[bad[i].field] = bad[i].v;
        if (bad[i].field == 6 && bad[i].v == 0) w[7] = 0;   /* SRQ_ELEMENT without handles */
        assert_int_equal(srq_decode(w, 3, &d), -1);
        assert_int_equal(d.kind, SRQ_NONE);
    }
    int32_t handles_on_to[SRQ_WIRE_N] = { SRQ_TO, 0, 0, 10, 0, 0, 1, 0 };
    assert_int_equal(srq_decode(handles_on_to, 3, &d), -1);
    assert_int_equal(srq_decode(NULL, 3, &d), -1);
    assert_int_equal(srq_decode(ok, 3, NULL), -1);
}

static void test_smooth(void **state) {
    (void)state;
    srq_req r = { .kind = SRQ_TO, .behavior = SRQ_AUTO };
    assert_int_equal(srq_smooth(&r, 0), 0);
    assert_int_equal(srq_smooth(&r, 1), 1);
    r.behavior = SRQ_INSTANT;
    assert_int_equal(srq_smooth(&r, 1), 0);
    r.behavior = SRQ_SMOOTH;
    assert_int_equal(srq_smooth(&r, 0), 1);
    assert_int_equal(srq_smooth(NULL, 1), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_to_and_by_clamped),
        cmocka_unit_test(test_element_blocks),
        cmocka_unit_test(test_element_nearest),
        cmocka_unit_test(test_padding_and_margin),
        cmocka_unit_test(test_target_rejects),
        cmocka_unit_test(test_encode_decode_roundtrip),
        cmocka_unit_test(test_decode_rejects),
        cmocka_unit_test(test_smooth),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
