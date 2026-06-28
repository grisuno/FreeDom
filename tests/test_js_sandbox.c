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

/* --- js_loc_from_stack (pure parser) --- */

static void test_loc_parses_named_frame(void **state) {
    (void)state;
    char file[64]; int line = -1, col = -1;
    /* The real QuickJS-ng top frame form. */
    assert_int_equal(js_loc_from_stack("    at e (inline #9:2:54)\n    at x (a:1:1)",
                                       file, sizeof file, &line, &col), 1);
    assert_string_equal(file, "inline #9");
    assert_int_equal(line, 2);
    assert_int_equal(col, 54);
}

static void test_loc_parses_bare_frame(void **state) {
    (void)state;
    char file[64]; int line = 0, col = 0;
    assert_int_equal(js_loc_from_stack("    at <repl>:7:3", file, sizeof file, &line, &col), 1);
    assert_string_equal(file, "<repl>");
    assert_int_equal(line, 7);
    assert_int_equal(col, 3);
}

static void test_loc_file_may_contain_colons(void **state) {
    (void)state;
    /* A URL-like name (https://...) has its own colons; the two trailing ones win. */
    char file[128]; int line = 0, col = 0;
    assert_int_equal(js_loc_from_stack("    at f (https://h/p:10:200)",
                                       file, sizeof file, &line, &col), 1);
    assert_string_equal(file, "https://h/p");
    assert_int_equal(line, 10);
    assert_int_equal(col, 200);
}

static void test_loc_line_only_sets_col_zero(void **state) {
    (void)state;
    char file[64]; int line = -1, col = -1;
    assert_int_equal(js_loc_from_stack("    at g (foo:42)", file, sizeof file, &line, &col), 1);
    assert_string_equal(file, "foo");
    assert_int_equal(line, 42);
    assert_int_equal(col, 0);
}

static void test_loc_truncates_to_cap(void **state) {
    (void)state;
    char file[8]; int line = 0, col = 0;
    assert_int_equal(js_loc_from_stack("    at z (abcdefghij:1:2)", file, sizeof file, &line, &col), 1);
    assert_int_equal((int)strlen(file), 7); /* cap-1, NUL-terminated */
    assert_int_equal(line, 1);
}

static void test_loc_rejects_garbage_and_null(void **state) {
    (void)state;
    char file[16]; int line = 9, col = 9;
    assert_int_equal(js_loc_from_stack(NULL, file, sizeof file, &line, &col), 0);
    assert_string_equal(file, ""); /* emptied */
    assert_int_equal(line, 0);
    assert_int_equal(col, 0);
    assert_int_equal(js_loc_from_stack("native code, no numbers", file, sizeof file, &line, &col), 0);
    assert_int_equal(js_loc_from_stack("", file, sizeof file, &line, &col), 0);
    /* NULL outputs must be tolerated. */
    assert_int_equal(js_loc_from_stack("    at q (f:1:2)", NULL, 0, NULL, NULL), 1);
}

/* --- js_eval_named: an uncaught error carries its throw site --- */

static void test_eval_named_captures_location(void **state) {
    (void)state;
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    js_result r;
    memset(&r, 0, sizeof r);
    /* Throw on the 2nd line so a non-trivial line number is asserted. */
    const char *src = "var x = 1;\nnull.boom;";
    assert_int_equal(js_eval_named(ctx, src, strlen(src), "myscript", &r), JS_ERR_RUNTIME);
    assert_int_equal(r.is_exception, 1);
    assert_non_null(r.file);
    assert_string_equal(r.file, "myscript");
    assert_int_equal(r.line, 2);
    assert_true(r.col > 0);
    js_result_free(&r);
    /* After free the location is cleared. */
    assert_null(r.file);
    assert_int_equal(r.line, 0);
    js_context_free(ctx);
}

static void test_eval_named_null_filename_defaults(void **state) {
    (void)state;
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    js_result r;
    memset(&r, 0, sizeof r);
    /* NULL filename must behave like js_eval (no crash, sandbox name). */
    assert_int_equal(js_eval_named(ctx, "null.x", 6, NULL, &r), JS_ERR_RUNTIME);
    assert_int_equal(r.is_exception, 1);
    assert_non_null(r.file);
    assert_string_equal(r.file, "<sandbox>");
    js_result_free(&r);
    js_context_free(ctx);
}

static void test_eval_thrown_primitive_has_no_location(void **state) {
    (void)state;
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    js_result r;
    memset(&r, 0, sizeof r);
    /* A thrown non-Error has no .stack: location stays unknown, never crashes. */
    assert_int_equal(js_eval_named(ctx, "throw 'oops';", 13, "s", &r), JS_ERR_RUNTIME);
    assert_int_equal(r.is_exception, 1);
    assert_null(r.file);
    assert_int_equal(r.line, 0);
    assert_int_equal(r.col, 0);
    js_result_free(&r);
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
        cmocka_unit_test(test_loc_parses_named_frame),
        cmocka_unit_test(test_loc_parses_bare_frame),
        cmocka_unit_test(test_loc_file_may_contain_colons),
        cmocka_unit_test(test_loc_line_only_sets_col_zero),
        cmocka_unit_test(test_loc_truncates_to_cap),
        cmocka_unit_test(test_loc_rejects_garbage_and_null),
        cmocka_unit_test(test_eval_named_captures_location),
        cmocka_unit_test(test_eval_named_null_filename_defaults),
        cmocka_unit_test(test_eval_thrown_primitive_has_no_location),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
