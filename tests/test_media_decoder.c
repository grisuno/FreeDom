/*
 * test_media_decoder — pure pacing brain (md_pacer) unit tests.
 *
 * The pacer is a static-inline pure function in include/media_decoder.h, so
 * this suite links nothing beyond the header (no FFmpeg). See
 * spec/media_decoder.md "Pacing".
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "media_decoder.h"

/* First frame anchors the epoch and displays immediately. */
static void test_pacer_first_frame_immediate(void **state) {
    (void)state;
    md_pacer p = {0, 0, 0};
    assert_int_equal(md_pace_due_ms(&p, 1000, 7000000), 1000);
    assert_true(p.primed);
    assert_int_equal(p.epoch_ms, 1000);
    assert_true(p.pts0_us == 7000000);
}

/* Subsequent frames are due at epoch + delta-pts. */
static void test_pacer_paces_by_pts_delta(void **state) {
    (void)state;
    md_pacer p = {0, 0, 0};
    (void)md_pace_due_ms(&p, 1000, 0);
    /* +40ms of pts => due 40ms after epoch, regardless of now. */
    assert_int_equal(md_pace_due_ms(&p, 1001, 40000), 1040);
    assert_int_equal(md_pace_due_ms(&p, 1002, 80000), 1080);
    /* One second of pts => one second of wall clock. */
    assert_int_equal(md_pace_due_ms(&p, 1003, 1000000), 2000);
}

/* A backwards pts (HLS discontinuity) re-anchors to now instead of stalling. */
static void test_pacer_backwards_pts_reanchors(void **state) {
    (void)state;
    md_pacer p = {0, 0, 0};
    (void)md_pace_due_ms(&p, 1000, 5000000);
    uint64_t due = md_pace_due_ms(&p, 3000, 1000000); /* pts jumped back */
    assert_int_equal(due, 3000);
    assert_int_equal(p.epoch_ms, 3000);
    assert_true(p.pts0_us == 1000000);
}

/* Falling more than MD_PACE_MAX_LAG_MS behind re-anchors (catch-up, no
 * fast-forward replay of the accumulated backlog). */
static void test_pacer_lag_reanchors(void **state) {
    (void)state;
    md_pacer p = {0, 0, 0};
    (void)md_pace_due_ms(&p, 1000, 0);
    /* Frame due at 1040, but now is 1040 + MD_PACE_MAX_LAG_MS + 1: too late. */
    uint64_t late_now = 1040 + MD_PACE_MAX_LAG_MS + 1;
    uint64_t due = md_pace_due_ms(&p, late_now, 40000);
    assert_int_equal(due, late_now);
    assert_int_equal(p.epoch_ms, late_now);
    /* Small lag does NOT re-anchor: due stays in the past so the caller
     * drains without resetting the clock. */
    md_pacer q = {0, 0, 0};
    (void)md_pace_due_ms(&q, 1000, 0);
    assert_int_equal(md_pace_due_ms(&q, 1100, 40000), 1040);
}

/* Hostile pts values never overflow into UB or a huge sleep. */
static void test_pacer_hostile_pts_bounded(void **state) {
    (void)state;
    md_pacer p = {0, 0, 0};
    (void)md_pace_due_ms(&p, 1000, 0);
    /* An absurd forward jump caps at the max-step clamp (never a year-long
     * sleep: re-anchors like a discontinuity). */
    uint64_t due = md_pace_due_ms(&p, 1001, INT64_MAX);
    assert_true(due <= 1001 + MD_PACE_MAX_STEP_MS);
    md_pacer q = {0, 0, 0};
    (void)md_pace_due_ms(&q, 1000, INT64_MAX);
    uint64_t due2 = md_pace_due_ms(&q, 1001, INT64_MIN); /* backwards: re-anchor */
    assert_int_equal(due2, 1001);
}

/* NULL pacer is a safe no-op returning now (fail open to "display now"). */
static void test_pacer_null_safe(void **state) {
    (void)state;
    assert_int_equal(md_pace_due_ms(NULL, 1234, 0), 1234);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_pacer_first_frame_immediate),
        cmocka_unit_test(test_pacer_paces_by_pts_delta),
        cmocka_unit_test(test_pacer_backwards_pts_reanchors),
        cmocka_unit_test(test_pacer_lag_reanchors),
        cmocka_unit_test(test_pacer_hostile_pts_bounded),
        cmocka_unit_test(test_pacer_null_safe),
    };
    return cmocka_run_group_tests_name("media_decoder", tests, NULL, NULL);
}
