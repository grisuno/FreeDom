/*
 * TDD suite for ui_layout (Hito 4 - pure UI core).
 *
 * Only the pure layout/scroll logic is unit-tested; the Wayland/Cairo
 * orchestrator is tested visually by the user (`make view`).
 *
 * Build: make test   ;   ASan: make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "ui.h"

/* Asserts that line `n` of the layout equals expected (over the source text). */
static void assert_line(const char *text, const ui_layout *lay, size_t n,
                        const char *expected) {
    assert_true(n < lay->count);
    size_t elen = strlen(expected);
    assert_int_equal((int)lay->lines[n].len, (int)elen);
    assert_memory_equal(text + lay->lines[n].offset, expected, elen);
}

static void test_wrap_null_args(void **state) {
    (void)state;
    ui_layout lay;
    assert_int_equal(ui_wrap_text(NULL, 3, 10, &lay), UI_ERR_NULL_ARG);
    assert_int_equal(ui_wrap_text("abc", 3, 10, NULL), UI_ERR_NULL_ARG);
}

static void test_wrap_empty(void **state) {
    (void)state;
    ui_layout lay;
    assert_int_equal(ui_wrap_text("", 0, 10, &lay), UI_OK);
    assert_int_equal((int)lay.count, 0);
    ui_layout_free(&lay);
}

static void test_wrap_short_single_line(void **state) {
    (void)state;
    const char *t = "hello";
    ui_layout lay;
    assert_int_equal(ui_wrap_text(t, strlen(t), 10, &lay), UI_OK);
    assert_int_equal((int)lay.count, 1);
    assert_line(t, &lay, 0, "hello");
    ui_layout_free(&lay);
}

static void test_wrap_breaks_at_space(void **state) {
    (void)state;
    const char *t = "hello world foo";
    ui_layout lay;
    assert_int_equal(ui_wrap_text(t, strlen(t), 11, &lay), UI_OK);
    assert_int_equal((int)lay.count, 2);
    assert_line(t, &lay, 0, "hello world");
    assert_line(t, &lay, 1, "foo");
    ui_layout_free(&lay);
}

static void test_wrap_hard_breaks_long_word(void **state) {
    (void)state;
    const char *t = "abcdefghij";
    ui_layout lay;
    assert_int_equal(ui_wrap_text(t, strlen(t), 4, &lay), UI_OK);
    assert_int_equal((int)lay.count, 3);
    assert_line(t, &lay, 0, "abcd");
    assert_line(t, &lay, 1, "efgh");
    assert_line(t, &lay, 2, "ij");
    ui_layout_free(&lay);
}

static void test_wrap_does_not_split_utf8(void **state) {
    (void)state;
    /* "abc" + U+00E1 (0xC3 0xA1) + "def": 7 columns, 8 bytes. A byte-based hard
     * break at 4 would split the 2-byte character; wrapping must keep it whole. */
    const char t[] = { 'a', 'b', 'c', (char)0xC3, (char)0xA1, 'd', 'e', 'f', '\0' };
    ui_layout lay;
    assert_int_equal(ui_wrap_text(t, strlen(t), 4, &lay), UI_OK);
    assert_int_equal((int)lay.count, 2);
    assert_int_equal((int)lay.lines[0].len, 5); /* a b c + whole 2-byte char */
    assert_line(t, &lay, 0, "abc\xC3\xA1");
    assert_line(t, &lay, 1, "def");
    ui_layout_free(&lay);
}

static void test_wrap_respects_newline(void **state) {
    (void)state;
    const char *t = "a\nb";
    ui_layout lay;
    assert_int_equal(ui_wrap_text(t, strlen(t), 10, &lay), UI_OK);
    assert_int_equal((int)lay.count, 2);
    assert_line(t, &lay, 0, "a");
    assert_line(t, &lay, 1, "b");
    ui_layout_free(&lay);
}

static void test_wrap_zero_cols_is_sanitised(void **state) {
    (void)state;
    const char *t = "ab";
    ui_layout lay;
    assert_int_equal(ui_wrap_text(t, strlen(t), 0, &lay), UI_OK);
    /* max_cols treated as 1: one column per line, no hang. */
    assert_int_equal((int)lay.count, 2);
    assert_line(t, &lay, 0, "a");
    assert_line(t, &lay, 1, "b");
    ui_layout_free(&lay);
}

static void test_clamp_scroll(void **state) {
    (void)state;
    assert_int_equal((int)ui_clamp_scroll(3, 50, 10), 3);
    assert_int_equal((int)ui_clamp_scroll(100, 50, 10), 40); /* 50 - 10 */
    assert_int_equal((int)ui_clamp_scroll(5, 8, 10), 0);     /* viewport >= total */
    assert_int_equal((int)ui_clamp_scroll(0, 0, 0), 0);
}

static void test_layout_free_null_and_double(void **state) {
    (void)state;
    ui_layout_free(NULL);
    ui_layout lay;
    assert_int_equal(ui_wrap_text("x", 1, 5, &lay), UI_OK);
    ui_layout_free(&lay);
    ui_layout_free(&lay); /* idempotent */
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_wrap_null_args),
        cmocka_unit_test(test_wrap_empty),
        cmocka_unit_test(test_wrap_short_single_line),
        cmocka_unit_test(test_wrap_breaks_at_space),
        cmocka_unit_test(test_wrap_hard_breaks_long_word),
        cmocka_unit_test(test_wrap_does_not_split_utf8),
        cmocka_unit_test(test_wrap_respects_newline),
        cmocka_unit_test(test_wrap_zero_cols_is_sanitised),
        cmocka_unit_test(test_clamp_scroll),
        cmocka_unit_test(test_layout_free_null_and_double),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
