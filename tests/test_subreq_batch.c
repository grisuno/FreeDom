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

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_results_in_issue_order_and_overlap),
        cmocka_unit_test(test_thread_limit_is_respected),
        cmocka_unit_test(test_refused_and_failed_keep_their_slot),
        cmocka_unit_test(test_full_batch_refuses_and_reset_reuses),
        cmocka_unit_test(test_null_args_fail_closed),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
