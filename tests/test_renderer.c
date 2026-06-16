/*
 * TDD suite for renderer (Hito 5 - out-of-process tab isolation).
 *
 * rd_render_html forks a seccomp-confined child internally; these tests run in
 * the parent and assert the inert result. The parent surviving hostile/binary
 * input is itself the isolation guarantee.
 *
 * Build: make test   ;   ASan: make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "renderer.h"

static const char HTML[] =
    "<!DOCTYPE html><html><head><title>Isolated</title></head>"
    "<body><div id=\"m\" class=\"box\"><p>Hola</p>"
    "<script>steal_cookies()</script>"
    "<p onclick=\"evil()\">mundo</p></div></body></html>";

static void test_render_basic(void **state) {
    (void)state;
    rd_result r;
    assert_int_equal(rd_render_html(HTML, sizeof HTML - 1, &r), RD_OK);
    assert_non_null(r.title);
    assert_string_equal(r.title, "Isolated");
    assert_non_null(r.text);
    assert_non_null(strstr(r.text, "Hola"));
    assert_non_null(strstr(r.text, "mundo"));
    rd_result_free(&r);
}

static void test_render_strips_script(void **state) {
    (void)state;
    rd_result r;
    assert_int_equal(rd_render_html(HTML, sizeof HTML - 1, &r), RD_OK);
    /* The script body never reaches the inert text. */
    assert_null(strstr(r.text, "steal_cookies"));
    rd_result_free(&r);
}

static void test_render_null_args(void **state) {
    (void)state;
    rd_result r;
    assert_int_equal(rd_render_html(NULL, 10, &r), RD_ERR_NULL_ARG);
    assert_int_equal(rd_render_html("x", 1, NULL), RD_ERR_NULL_ARG);
}

static void test_render_too_large(void **state) {
    (void)state;
    rd_result r;
    /* Length cap is checked before any allocation of the body. */
    assert_int_equal(rd_render_html("x", RD_MAX_INPUT + 1, &r), RD_ERR_TOO_LARGE);
}

/* The parent must survive arbitrary/binary input: isolation in action. */
static void test_render_binary_does_not_crash_parent(void **state) {
    (void)state;
    uint8_t junk[1024];
    for (size_t i = 0; i < sizeof junk; ++i) junk[i] = (uint8_t)(i * 37 + 11);
    rd_result r;
    rd_status s = rd_render_html((const char *)junk, sizeof junk, &r);
    assert_true(s == RD_OK || s == RD_ERR_RENDER); /* never a parent crash */
    rd_result_free(&r);
}

/* Each call spawns its own child process: per-render/per-tab isolation. */
static void test_render_multiple_independent(void **state) {
    (void)state;
    for (int i = 0; i < 3; ++i) {
        rd_result r;
        assert_int_equal(rd_render_html(HTML, sizeof HTML - 1, &r), RD_OK);
        assert_string_equal(r.title, "Isolated");
        rd_result_free(&r);
    }
}

static void test_result_free_null_and_double(void **state) {
    (void)state;
    rd_result_free(NULL);
    rd_result r;
    assert_int_equal(rd_render_html(HTML, sizeof HTML - 1, &r), RD_OK);
    rd_result_free(&r);
    rd_result_free(&r); /* idempotent */
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_render_basic),
        cmocka_unit_test(test_render_strips_script),
        cmocka_unit_test(test_render_null_args),
        cmocka_unit_test(test_render_too_large),
        cmocka_unit_test(test_render_binary_does_not_crash_parent),
        cmocka_unit_test(test_render_multiple_independent),
        cmocka_unit_test(test_result_free_null_and_double),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
