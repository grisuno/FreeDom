/*
 * TDD suite for perf_trace (pt_) — pure per-stage render timing accumulator.
 * Red until src/perf_trace.c exists. See spec/perf_trace.md.
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <string.h>
#include <cmocka.h>

#include "perf_trace.h"

static void test_init_all_empty(void **state) {
    (void)state;
    pt_trace t;
    pt_init(&t);
    for (int s = 0; s < PT_STAGE_COUNT; ++s) {
        assert_int_equal((int)pt_count(&t, (pt_stage)s), 0);
        assert_int_equal((int)pt_last_us(&t, (pt_stage)s), 0);
        assert_int_equal((int)pt_min_us(&t, (pt_stage)s), 0);
        assert_int_equal((int)pt_max_us(&t, (pt_stage)s), 0);
        assert_int_equal((int)pt_median_us(&t, (pt_stage)s), 0);
    }
}

static void test_single_record(void **state) {
    (void)state;
    pt_trace t;
    pt_init(&t);
    pt_record(&t, PT_LAYOUT, 1500);
    assert_int_equal((int)pt_count(&t, PT_LAYOUT), 1);
    assert_int_equal((int)pt_last_us(&t, PT_LAYOUT), 1500);
    assert_int_equal((int)pt_min_us(&t, PT_LAYOUT), 1500);
    assert_int_equal((int)pt_max_us(&t, PT_LAYOUT), 1500);
    assert_int_equal((int)pt_median_us(&t, PT_LAYOUT), 1500);
    /* other stages untouched */
    assert_int_equal((int)pt_count(&t, PT_PAINT), 0);
}

static void test_min_max_median(void **state) {
    (void)state;
    pt_trace t;
    pt_init(&t);
    uint64_t vals[] = {100, 500, 300, 700, 200};
    for (size_t i = 0; i < 5; ++i) pt_record(&t, PT_PAINT, vals[i]);
    assert_int_equal((int)pt_count(&t, PT_PAINT), 5);
    assert_int_equal((int)pt_min_us(&t, PT_PAINT), 100);
    assert_int_equal((int)pt_max_us(&t, PT_PAINT), 700);
    assert_int_equal((int)pt_median_us(&t, PT_PAINT), 300);
    assert_int_equal((int)pt_last_us(&t, PT_PAINT), 200);
}

static void test_ring_wraparound_fifo(void **state) {
    (void)state;
    pt_trace t;
    pt_init(&t);
    /* Fill beyond PT_MAX_SAMPLES; oldest samples must be evicted FIFO and
     * count must saturate, never exceeding the cap. */
    for (size_t i = 0; i < PT_MAX_SAMPLES + 10; ++i) {
        pt_record(&t, PT_SHAPE, (uint64_t)(i + 1));
    }
    assert_int_equal((int)pt_count(&t, PT_SHAPE), PT_MAX_SAMPLES);
    /* last recorded value is always reflected regardless of wraparound */
    assert_int_equal((int)pt_last_us(&t, PT_SHAPE), PT_MAX_SAMPLES + 10);
    /* the ring now holds values [11 .. 266] (10 oldest evicted) */
    assert_int_equal((int)pt_min_us(&t, PT_SHAPE), 11);
    assert_int_equal((int)pt_max_us(&t, PT_SHAPE), PT_MAX_SAMPLES + 10);
}

static void test_stage_out_of_range_is_noop(void **state) {
    (void)state;
    pt_trace t;
    pt_init(&t);
    pt_record(&t, (pt_stage)(-1), 123);
    pt_record(&t, (pt_stage)PT_STAGE_COUNT, 123);
    pt_record(&t, (pt_stage)9999, 123);
    for (int s = 0; s < PT_STAGE_COUNT; ++s) {
        assert_int_equal((int)pt_count(&t, (pt_stage)s), 0);
    }
    assert_int_equal((int)pt_count(&t, (pt_stage)(-1)), 0);
    assert_int_equal((int)pt_last_us(&t, (pt_stage)9999), 0);
    assert_int_equal((int)pt_min_us(&t, (pt_stage)9999), 0);
    assert_int_equal((int)pt_max_us(&t, (pt_stage)9999), 0);
    assert_int_equal((int)pt_median_us(&t, (pt_stage)9999), 0);
}

static void test_elapsed_us_normal(void **state) {
    (void)state;
    assert_int_equal((int)pt_elapsed_us(1000, 2500), 1500);
    assert_int_equal((int)pt_elapsed_us(1000, 1000), 0);
}

static void test_elapsed_us_underflow_guard(void **state) {
    (void)state;
    /* end < start must never underflow to a huge uint64_t */
    assert_int_equal((int)pt_elapsed_us(5000, 1000), 0);
}

static void test_stage_name(void **state) {
    (void)state;
    assert_string_equal(pt_stage_name(PT_FETCH), "fetch");
    assert_string_equal(pt_stage_name(PT_PARSE), "parse");
    assert_string_equal(pt_stage_name(PT_STYLE), "style");
    assert_string_equal(pt_stage_name(PT_IPC), "ipc");
    assert_string_equal(pt_stage_name(PT_RD_BUILD), "rd_build");
    assert_string_equal(pt_stage_name(PT_LAYOUT), "layout");
    assert_string_equal(pt_stage_name(PT_PAINT), "paint");
    assert_string_equal(pt_stage_name(PT_COMMIT), "commit");
    assert_string_equal(pt_stage_name(PT_SHAPE), "shape");
    assert_string_equal(pt_stage_name((pt_stage)9999), "unknown");
}

static void test_format_deterministic_and_only_nonempty_stages(void **state) {
    (void)state;
    pt_trace t;
    pt_init(&t);
    pt_record(&t, PT_FETCH, 2000);
    pt_record(&t, PT_PAINT, 500);

    char buf1[512];
    char buf2[512];
    size_t n1 = pt_format(&t, buf1, sizeof(buf1));
    size_t n2 = pt_format(&t, buf2, sizeof(buf2));
    assert_int_equal((int)n1, (int)n2);
    assert_memory_equal(buf1, buf2, n1);
    assert_true(n1 > 0);
    assert_non_null(strstr(buf1, "stage=fetch"));
    assert_non_null(strstr(buf1, "stage=paint"));
    /* untouched stages must not appear */
    assert_null(strstr(buf1, "stage=layout"));
    assert_null(strstr(buf1, "stage=shape"));
    /* fetch (enum 0) must come before paint (enum later) */
    assert_true(strstr(buf1, "stage=fetch") < strstr(buf1, "stage=paint"));
}

static void test_format_truncates_never_overflows(void **state) {
    (void)state;
    pt_trace t;
    pt_init(&t);
    pt_record(&t, PT_FETCH, 1);
    pt_record(&t, PT_PARSE, 2);
    pt_record(&t, PT_STYLE, 3);

    char tiny[8];
    size_t n = pt_format(&t, tiny, sizeof(tiny));
    assert_true(n < sizeof(tiny));
    assert_int_equal(tiny[n], '\0');
}

static void test_format_null_or_zero_cap(void **state) {
    (void)state;
    pt_trace t;
    pt_init(&t);
    pt_record(&t, PT_FETCH, 1);
    assert_int_equal((int)pt_format(&t, NULL, 100), 0);
    char buf[8];
    assert_int_equal((int)pt_format(&t, buf, 0), 0);
    assert_int_equal((int)pt_format(NULL, buf, sizeof(buf)), 0);
}

static void test_null_safe(void **state) {
    (void)state;
    pt_init(NULL);
    pt_record(NULL, PT_FETCH, 100);
    assert_int_equal((int)pt_count(NULL, PT_FETCH), 0);
    assert_int_equal((int)pt_last_us(NULL, PT_FETCH), 0);
    assert_int_equal((int)pt_min_us(NULL, PT_FETCH), 0);
    assert_int_equal((int)pt_max_us(NULL, PT_FETCH), 0);
    assert_int_equal((int)pt_median_us(NULL, PT_FETCH), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init_all_empty),
        cmocka_unit_test(test_single_record),
        cmocka_unit_test(test_min_max_median),
        cmocka_unit_test(test_ring_wraparound_fifo),
        cmocka_unit_test(test_stage_out_of_range_is_noop),
        cmocka_unit_test(test_elapsed_us_normal),
        cmocka_unit_test(test_elapsed_us_underflow_guard),
        cmocka_unit_test(test_stage_name),
        cmocka_unit_test(test_format_deterministic_and_only_nonempty_stages),
        cmocka_unit_test(test_format_truncates_never_overflows),
        cmocka_unit_test(test_format_null_or_zero_cap),
        cmocka_unit_test(test_null_safe),
    };
    return cmocka_run_group_tests_name("perf_trace", tests, NULL, NULL);
}
