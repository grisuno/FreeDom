/* subreq_batch (spec/subreq_async.md): parallelism, issue order, refusals, reuse. */
#define _GNU_SOURCE
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <cmocka.h>

#include "subreq_batch.h"

static pthread_mutex_t lk = PTHREAD_MUTEX_INITIALIZER;
static int now, peak;

static int slow_run(void *ctx, const sqb_req *rq, sqb_res *out) {
    (void)ctx;
    pthread_mutex_lock(&lk); if (++now > peak) peak = now; pthread_mutex_unlock(&lk);
    usleep(80 * 1000);
    pthread_mutex_lock(&lk); --now; pthread_mutex_unlock(&lk);
    if (strstr(rq->url, "fail") != NULL) return -1;
    out->ok = 1; out->status = 200;
    out->body = strdup(rq->url); out->body_len = strlen(rq->url);
    out->ctype = strdup("text/plain"); out->resp_headers = strdup("");
    return 0;
}

static sqb_req mk(const char *u) { sqb_req r = { "GET", u, "", 0, "" }; return r; }

static void test_results_in_issue_order_and_overlap(void **st) {
    (void)st;
    now = peak = 0;
    sqb *b = sqb_new(4, slow_run, NULL);
    assert_non_null(b);
    const char *u[] = { "a", "b", "c", "d" };
    for (int i = 0; i < 4; ++i) { sqb_req r = mk(u[i]); assert_int_equal(sqb_submit(b, 0, &r), 0); }
    sqb_wait_all(b);
    assert_int_equal((int)sqb_count(b), 4);
    for (int i = 0; i < 4; ++i) {
        const sqb_res *r = sqb_result(b, (size_t)i);
        assert_int_equal(r->ok, 1);
        assert_string_equal(r->body, u[i]);
    }
    assert_true(peak >= 3);
    sqb_free(b);
}

static void test_thread_limit_is_respected(void **st) {
    (void)st;
    now = peak = 0;
    sqb *b = sqb_new(2, slow_run, NULL);
    for (int i = 0; i < 6; ++i) { sqb_req r = mk("x"); assert_int_equal(sqb_submit(b, 0, &r), 0); }
    sqb_wait_all(b);
    assert_true(peak <= 2);
    sqb_free(b);
}

static void test_refused_and_failed_keep_their_slot(void **st) {
    (void)st;
    sqb *b = sqb_new(3, slow_run, NULL);
    sqb_req a = mk("ok"), f = mk("fail"), z = mk("never");
    assert_int_equal(sqb_submit(b, 0, &a), 0);
    assert_int_equal(sqb_submit(b, 0, &f), 0);
    assert_int_equal(sqb_submit(b, 1, &z), 0);   /* refused: no fetch */
    sqb_wait_all(b);
    assert_int_equal(sqb_result(b, 0)->ok, 1);
    assert_int_equal(sqb_result(b, 1)->ok, 0);
    assert_int_equal(sqb_result(b, 2)->ok, 0);
    assert_null(sqb_result(b, 2)->body);
    sqb_free(b);
}

static void test_full_batch_refuses_and_reset_reuses(void **st) {
    (void)st;
    sqb *b = sqb_new(8, slow_run, NULL);
    sqb_req r = mk("q");
    for (int i = 0; i < SQB_MAX_JOBS; ++i) assert_int_equal(sqb_submit(b, 1, &r), 0);
    assert_int_equal(sqb_submit(b, 1, &r), -1);
    sqb_reset(b);
    assert_int_equal((int)sqb_count(b), 0);
    assert_int_equal(sqb_submit(b, 0, &r), 0);
    sqb_wait_all(b);
    assert_int_equal(sqb_result(b, 0)->ok, 1);
    sqb_free(b);
}

static void test_null_args_fail_closed(void **st) {
    (void)st;
    assert_null(sqb_new(0, slow_run, NULL));
    assert_null(sqb_new(2, NULL, NULL));
    assert_int_equal(sqb_submit(NULL, 0, NULL), -1);
    assert_int_equal((int)sqb_count(NULL), 0);
    assert_null(sqb_result(NULL, 0));
    sqb_free(NULL);
}


static int varied_run(void *ctx, const sqb_req *rq, sqb_res *out) {
    (void)ctx;
    usleep((useconds_t)atoi(rq->url) * 1000u);
    out->ok = 1; out->status = 200;
    out->body = strdup(rq->url); out->body_len = strlen(rq->url);
    out->ctype = strdup("text/plain"); out->resp_headers = strdup("");
    return 0;
}

/* A slow request holds back nothing: every finished one is handed over, in issue order among
 * themselves; the slow one keeps running and its index shifts as the others leave
 * (spec/subreq_async.md, "Entrega con plazo"). */
static void test_wait_ready_delivers_finished_out_of_issue_order(void **st) {
    (void)st;
    sqb *b = sqb_new(4, varied_run, NULL);
    const char *u[] = { "600", "10", "20", "10" };
    for (int i = 0; i < 4; ++i) { sqb_req r = mk(u[i]); assert_int_equal(sqb_submit(b, 0, &r), 0); }
    size_t idx[SQB_MAX_JOBS];
    size_t k = sqb_wait_ready(b, 200, idx, SQB_MAX_JOBS);
    assert_int_equal((int)k, 3);
    assert_int_equal((int)idx[0], 1);
    assert_int_equal((int)idx[2], 3);
    assert_string_equal(sqb_result(b, idx[1])->body, "20");
    sqb_remove(b, idx, k);
    assert_int_equal((int)sqb_count(b), 1);
    assert_int_equal((int)sqb_wait_ready(b, 0, idx, SQB_MAX_JOBS), 0);   /* still running, no wait */
    sqb_req r5 = mk("10");
    assert_int_equal(sqb_submit(b, 0, &r5), 0);      /* new work queues BEHIND the survivor */
    k = sqb_wait_ready(b, 3000, idx, SQB_MAX_JOBS);
    assert_int_equal((int)k, 2);
    assert_string_equal(sqb_result(b, idx[0])->body, "600");
    assert_string_equal(sqb_result(b, idx[1])->body, "10");
    size_t bogus[3] = { idx[0], idx[1], 99 };          /* out of range is skipped */
    sqb_remove(b, bogus, 3);
    assert_int_equal((int)sqb_count(b), 0);
    sqb_req rf = mk("x");
    assert_int_equal(sqb_submit(b, 1, &rf), 0);      /* a refusal is finished at once */
    assert_int_equal((int)sqb_wait_ready(b, 0, idx, 1), 1);
    assert_int_equal((int)sqb_wait_ready(NULL, 0, idx, 1), 0);
    assert_int_equal((int)sqb_wait_ready(b, 0, NULL, 1), 0);
    sqb_remove(NULL, idx, 1);
    sqb_free(b);
}


static int g_ctx_freed;
static void count_free(void *c) { (void)c; g_ctx_freed++; }

/* Closing never waits for a hung request (spec/subreq_async.md, "Fetcher estable y abandono"):
 * the running job is detached, and the owned ctx it may still use is freed only after it ends. */
static void test_abandon_and_free_never_wait(void **st) {
    (void)st;
    g_ctx_freed = 0;
    static int dummy;
    sqb *b = sqb_new_owned(2, varied_run, &dummy, count_free);
    assert_non_null(b);
    sqb_req a = mk("10"), slow = mk("600");
    assert_int_equal(sqb_submit(b, 0, &a), 0);
    assert_int_equal(sqb_submit(b, 0, &slow), 0);
    usleep(100 * 1000);
    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    sqb_abandon(b);
    assert_int_equal((int)sqb_count(b), 0);
    sqb_req c = mk("600");
    assert_int_equal(sqb_submit(b, 0, &c), 0);   /* reusable after abandoning */
    sqb_free(b);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    long ms = (long)((t1.tv_sec - t0.tv_sec) * 1000L + (t1.tv_nsec - t0.tv_nsec) / 1000000L);
    assert_true(ms < 100);
    assert_int_equal(g_ctx_freed, 0);             /* abandoned jobs may still use ctx */
    for (int i = 0; i < 200 && g_ctx_freed == 0; ++i) usleep(10 * 1000);
    assert_int_equal(g_ctx_freed, 1);             /* ...freed exactly once, after the last ends */
    sqb_abandon(NULL);
    assert_null(sqb_new_owned(0, varied_run, NULL, NULL));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_results_in_issue_order_and_overlap),
        cmocka_unit_test(test_wait_ready_delivers_finished_out_of_issue_order),
        cmocka_unit_test(test_abandon_and_free_never_wait),
        cmocka_unit_test(test_thread_limit_is_respected),
        cmocka_unit_test(test_refused_and_failed_keep_their_slot),
        cmocka_unit_test(test_full_batch_refuses_and_reset_reuses),
        cmocka_unit_test(test_null_args_fail_closed),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
