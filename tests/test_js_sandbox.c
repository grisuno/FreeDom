/*
 * TDD suite for js_sandbox (Hito 3).
 *
 * RED state until src/js_sandbox.c exists and the QuickJS-ng backend is
 * vendored: this links and fails on purpose. Implementing the module to satisfy
 * these assertions is the GREEN step.
 *
 * Build: make test   (requires libcmocka-dev + vendored third_party/quickjs)
 * ASan:  make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "js_sandbox.h"

/* --- js_limits_default --- */

static void test_limits_default_is_secure(void **state) {
    (void)state;
    js_limits l = js_limits_default();
    assert_true(l.max_source_bytes > 0);
    assert_true(l.memory_limit_bytes > 0);
    assert_true(l.max_stack_bytes > 0);
    assert_true(l.time_budget_ms > 0);
}

/* --- js_validate_source --- */

static void test_validate_rejects_null(void **state) {
    (void)state;
    assert_int_equal(js_validate_source(NULL, 10, NULL), JS_ERR_NULL_ARG);
}

static void test_validate_rejects_empty(void **state) {
    (void)state;
    assert_int_equal(js_validate_source("x", 0, NULL), JS_ERR_EMPTY);
}

static void test_validate_rejects_oversize(void **state) {
    (void)state;
    js_limits l = js_limits_default();
    l.max_source_bytes = 4;
    assert_int_equal(js_validate_source("12345", 5, &l), JS_ERR_TOO_LARGE);
}

static void test_validate_accepts_within_cap(void **state) {
    (void)state;
    assert_int_equal(js_validate_source("1+1", 3, NULL), JS_OK);
}

/* --- context lifecycle --- */

static void test_context_new_and_free(void **state) {
    (void)state;
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    assert_non_null(ctx);
    js_context_free(ctx);
}

static void test_context_new_null_out(void **state) {
    (void)state;
    assert_int_equal(js_context_new(NULL, NULL), JS_ERR_NULL_ARG);
}

/* --- evaluation: values --- */

static void test_eval_arithmetic(void **state) {
    (void)state;
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    js_result r;
    memset(&r, 0, sizeof r);
    assert_int_equal(js_eval(ctx, "1+2", 3, &r), JS_OK);
    assert_int_equal(r.is_exception, 0);
    assert_non_null(r.value);
    assert_string_equal(r.value, "3");
    js_result_free(&r);
    js_context_free(ctx);
}

static void test_eval_string_concat(void **state) {
    (void)state;
    js_result r;
    memset(&r, 0, sizeof r);
    assert_int_equal(js_eval_once("'a'+'b'", 7, NULL, &r), JS_OK);
    assert_non_null(r.value);
    assert_string_equal(r.value, "ab");
    js_result_free(&r);
}

/* --- errors: syntax vs runtime --- */

static void test_eval_syntax_error(void **state) {
    (void)state;
    js_result r;
    memset(&r, 0, sizeof r);
    assert_int_equal(js_eval_once("][", 2, NULL, &r), JS_ERR_SYNTAX);
    assert_int_equal(r.is_exception, 1);
    js_result_free(&r);
}

static void test_eval_runtime_exception(void **state) {
    (void)state;
    js_result r;
    memset(&r, 0, sizeof r);
    assert_int_equal(js_eval_once("throw new Error('boom')", 23, NULL, &r),
                     JS_ERR_RUNTIME);
    assert_int_equal(r.is_exception, 1);
    assert_non_null(r.value);
    assert_non_null(strstr(r.value, "boom"));
    js_result_free(&r);
}

/* --- sandbox escape resistance --- */

static void test_no_io_globals(void **state) {
    (void)state;
    js_result r;
    memset(&r, 0, sizeof r);
    const char *src =
        "typeof std+typeof os+typeof require+typeof process+typeof fetch";
    assert_int_equal(js_eval_once(src, strlen(src), NULL, &r), JS_OK);
    assert_non_null(r.value);
    assert_string_equal(r.value,
                        "undefinedundefinedundefinedundefinedundefined");
    js_result_free(&r);
}

static void test_filesystem_access_is_reference_error(void **state) {
    (void)state;
    js_result r;
    memset(&r, 0, sizeof r);
    const char *src = "readFile('/etc/passwd')";
    /* readFile is not defined: a clean ReferenceError, not host access. */
    assert_int_equal(js_eval_once(src, strlen(src), NULL, &r), JS_ERR_RUNTIME);
    assert_int_equal(r.is_exception, 1);
    js_result_free(&r);
}

/* --- resource limits --- */

static void test_infinite_loop_times_out(void **state) {
    (void)state;
    js_limits l = js_limits_default();
    l.time_budget_ms = 100; /* tight budget for a fast test */
    js_result r;
    memset(&r, 0, sizeof r);
    assert_int_equal(js_eval_once("while(true){}", 13, &l, &r), JS_ERR_TIMEOUT);
    js_result_free(&r);
}

/* js_set_time_budget lowers the wall-clock cap armed on subsequent evals, so a
 * caller can enforce a single page-wide budget across many evaluations. A tiny
 * budget interrupts an infinite loop; a NULL context is a safe no-op. */
static void test_set_time_budget_applies(void **state) {
    (void)state;
    js_set_time_budget(NULL, 1000); /* no-op, must not crash */
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK); /* default budget = 1000ms */
    js_set_time_budget(ctx, 50); /* shrink it for a fast test */
    js_result r;
    memset(&r, 0, sizeof r);
    assert_int_equal(js_eval(ctx, "while(true){}", 13, &r), JS_ERR_TIMEOUT);
    js_result_free(&r);
    /* A subsequent eval still honours the lowered budget (it persists on the ctx). */
    memset(&r, 0, sizeof r);
    assert_int_equal(js_eval(ctx, "for(;;){}", 9, &r), JS_ERR_TIMEOUT);
    js_result_free(&r);
    js_context_free(ctx);
}

static void test_memory_limit_is_enforced(void **state) {
    (void)state;
    js_limits l = js_limits_default();
    l.memory_limit_bytes = 8u * 1024u * 1024u; /* 8 MiB */
    js_result r;
    memset(&r, 0, sizeof r);
    /* Unbounded object allocation exhausts the heap and is denied by the cap.
     * (A doubling string instead trips the engine's max-string-length first,
     * which is a normal RangeError, not a memory-exhaustion event.) */
    const char *src = "var a=[];for(;;){a.push([0,1,2,3,4,5,6,7,8,9]);}";
    assert_int_equal(js_eval_once(src, strlen(src), &l, &r), JS_ERR_MEMORY);
    js_result_free(&r);
}

/* --- memory safety --- */

static void test_result_free_on_zeroed(void **state) {
    (void)state;
    js_result r;
    memset(&r, 0, sizeof r);
    js_result_free(&r);  /* must not crash on all-NULL members */
    js_result_free(&r);  /* idempotent */
    js_result_free(NULL); /* NULL is a no-op */
}

static void test_context_free_null_and_double(void **state) {
    (void)state;
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    js_context_free(ctx);
    js_context_free(NULL); /* NULL is a no-op */
}

static void test_eval_null_args(void **state) {
    (void)state;
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    js_result r;
    memset(&r, 0, sizeof r);
    assert_int_equal(js_eval(NULL, "1", 1, &r), JS_ERR_NULL_ARG);
    assert_int_equal(js_eval(ctx, NULL, 1, &r), JS_ERR_NULL_ARG);
    assert_int_equal(js_eval(ctx, "1", 1, NULL), JS_ERR_NULL_ARG);
    js_context_free(ctx);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_limits_default_is_secure),
        cmocka_unit_test(test_validate_rejects_null),
        cmocka_unit_test(test_validate_rejects_empty),
        cmocka_unit_test(test_validate_rejects_oversize),
        cmocka_unit_test(test_validate_accepts_within_cap),
        cmocka_unit_test(test_context_new_and_free),
        cmocka_unit_test(test_context_new_null_out),
        cmocka_unit_test(test_eval_arithmetic),
        cmocka_unit_test(test_eval_string_concat),
        cmocka_unit_test(test_eval_syntax_error),
        cmocka_unit_test(test_eval_runtime_exception),
        cmocka_unit_test(test_no_io_globals),
        cmocka_unit_test(test_filesystem_access_is_reference_error),
        cmocka_unit_test(test_infinite_loop_times_out),
        cmocka_unit_test(test_set_time_budget_applies),
        cmocka_unit_test(test_memory_limit_is_enforced),
        cmocka_unit_test(test_result_free_on_zeroed),
        cmocka_unit_test(test_context_free_null_and_double),
        cmocka_unit_test(test_eval_null_args),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
