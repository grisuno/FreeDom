/*
 * TDD suite for ws_hub (spec/ws_hub.md). No network: a URL sf_ws_url_check refuses
 * makes the threaded open fail before any socket is touched, which exercises the
 * whole thread -> pipe -> wh_on_notify -> ERROR + CLOSE cycle.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <poll.h>
#include <time.h>
#include <string.h>
#include <cmocka.h>

#include "ws_hub.h"

typedef struct rec { int n; int id[16]; int kind[16]; int code[16]; } rec;

static void emit(void *ctx, int id, int kind, int code, const char *data, size_t len) {
    (void)data; (void)len;
    rec *r = (rec *)ctx;
    if (r->n < 16) { r->id[r->n] = id; r->kind[r->n] = kind; r->code[r->n] = code; r->n++; }
}

/* Waits (bounded) for the notify pipe and drains it once. */
static void wait_notify(wh_hub *h, rec *r) {
    struct pollfd p = { wh_notify_fd(h), POLLIN, 0 };
    assert_true(poll(&p, 1, 5000) > 0);
    wh_on_notify(h, emit, r);
}

static void test_new_free(void **state) {
    (void)state;
    wh_hub *h = wh_new();
    assert_non_null(h);
    assert_true(wh_notify_fd(h) >= 0);
    assert_int_equal(wh_count(h), 0);
    struct pollfd fds[8];
    int ids[8];
    assert_int_equal(wh_poll_fds(h, fds, ids, 8), 0);
    wh_free(h);
    wh_free(NULL);
}

static void test_failed_open_reports_error_then_close(void **state) {
    (void)state;
    wh_hub *h = wh_new();
    assert_non_null(h);
    assert_int_equal(wh_open_async(h, 3, "ws://plaintext.example/", NULL), 0);
    rec r;
    memset(&r, 0, sizeof r);
    wait_notify(h, &r);
    assert_int_equal(r.n, 2);
    assert_int_equal(r.id[0], 3);
    assert_int_equal(r.kind[0], WH_EV_ERROR);
    assert_int_equal(r.kind[1], WH_EV_CLOSE);
    assert_int_equal(r.code[1], WH_CLOSE_ABNORMAL);
    assert_int_equal(wh_count(h), 0);
    wh_free(h);
}

static void test_duplicate_and_capacity(void **state) {
    (void)state;
    wh_hub *h = wh_new();
    assert_non_null(h);
    for (int i = 1; i <= WH_MAX; ++i)
        assert_int_equal(wh_open_async(h, i, "ws://x.example/", NULL), 0);
    assert_int_equal(wh_open_async(h, 1, "ws://x.example/", NULL), -1);          /* dup */
    assert_int_equal(wh_open_async(h, WH_MAX + 1, "ws://x.example/", NULL), -1); /* full */
    assert_int_equal(wh_open_async(NULL, 1, "ws://x.example/", NULL), -1);
    assert_int_equal(wh_open_async(h, 99, NULL, NULL), -1);
    rec r;
    memset(&r, 0, sizeof r);
    for (int guard = 0; r.n < 2 * WH_MAX && guard < 50; ++guard) wait_notify(h, &r);
    assert_int_equal(r.n, 2 * WH_MAX);
    /* all slots free again */
    assert_int_equal(wh_open_async(h, 42, "ws://x.example/", NULL), 0);
    memset(&r, 0, sizeof r);
    wait_notify(h, &r);
    wh_free(h);
}

static void test_close_all_drops_late_results(void **state) {
    (void)state;
    wh_hub *h = wh_new();
    assert_non_null(h);
    assert_int_equal(wh_open_async(h, 5, "ws://x.example/", NULL), 0);
    wh_close_all(h);
    rec r;
    memset(&r, 0, sizeof r);
    wait_notify(h, &r);
    assert_int_equal(r.n, 0);                 /* stale generation: silent */
    assert_int_equal(wh_open_async(h, 5, "ws://x.example/", NULL), 0);  /* id reusable */
    memset(&r, 0, sizeof r);
    wait_notify(h, &r);
    assert_int_equal(r.n, 2);
    wh_free(h);
}

static void test_close_cancels_pending_open(void **state) {
    (void)state;
    wh_hub *h = wh_new();
    assert_non_null(h);
    assert_int_equal(wh_open_async(h, 6, "ws://x.example/", NULL), 0);
    wh_close(h, 6);
    rec r;
    memset(&r, 0, sizeof r);
    wait_notify(h, &r);
    assert_int_equal(r.n, 0);
    wh_free(h);
}

static void test_send_unknown_and_readable_unknown(void **state) {
    (void)state;
    wh_hub *h = wh_new();
    assert_non_null(h);
    assert_int_equal(wh_send(h, 7, "x", 1, 0), -1);
    assert_int_equal(wh_send(NULL, 7, "x", 1, 0), -1);
    rec r;
    memset(&r, 0, sizeof r);
    wh_on_readable(h, 7, emit, &r);
    assert_int_equal(r.n, 0);
    wh_close(h, 7);
    wh_close_all(NULL);
    wh_free(h);
}

/* wh_free while an open is still running must not crash or leak (the thread owns
 * its own pipe end and result). */
static void test_free_with_pending_open(void **state) {
    (void)state;
    wh_hub *h = wh_new();
    assert_non_null(h);
    assert_int_equal(wh_open_async(h, 1, "ws://x.example/", NULL), 0);
    wh_free(h);
    struct timespec ts = { 0, 50000000L };
    nanosleep(&ts, NULL);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_free),
        cmocka_unit_test(test_failed_open_reports_error_then_close),
        cmocka_unit_test(test_duplicate_and_capacity),
        cmocka_unit_test(test_close_all_drops_late_results),
        cmocka_unit_test(test_close_cancels_pending_open),
        cmocka_unit_test(test_send_unknown_and_readable_unknown),
        cmocka_unit_test(test_free_with_pending_open),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
