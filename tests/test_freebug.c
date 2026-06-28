/*
 * test_freebug — CMocka suite for the pure bounded console-log buffer.
 *
 * Covers basic push/read, the three caps (entry count, per-entry truncation,
 * total bytes) all fail-closed with the overflow flag, level clamping, the level
 * name table, reset (array reuse, no leak) and free idempotency. Run under ASan
 * to prove no leak/UAF across reset/free.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <cmocka.h>

#include "freebug.h"

static void test_push_and_read(void **state) {
    (void)state;
    fb_buffer b;
    fb_buffer_init(&b);
    assert_int_equal((int)fb_buffer_count(&b), 0);

    assert_int_equal(fb_buffer_push(&b, FB_LOG, "hello", 5), 1);
    assert_int_equal(fb_buffer_push(&b, FB_ERROR, "boom", 4), 1);
    assert_int_equal((int)fb_buffer_count(&b), 2);

    const fb_entry *e0 = fb_buffer_at(&b, 0);
    const fb_entry *e1 = fb_buffer_at(&b, 1);
    assert_non_null(e0);
    assert_non_null(e1);
    assert_int_equal(e0->level, FB_LOG);
    assert_int_equal((int)e0->len, 5);
    assert_string_equal(e0->text, "hello");
    assert_int_equal(e1->level, FB_ERROR);
    assert_string_equal(e1->text, "boom");

    assert_null(fb_buffer_at(&b, 2));
    assert_null(fb_buffer_at(NULL, 0));
    fb_buffer_free(&b);
}

static void test_empty_and_null_text(void **state) {
    (void)state;
    fb_buffer b;
    fb_buffer_init(&b);
    /* A bare console.log() is a real event: empty string, stored. */
    assert_int_equal(fb_buffer_push(&b, FB_LOG, "", 0), 1);
    assert_int_equal(fb_buffer_push(&b, FB_LOG, NULL, 0), 1);
    assert_int_equal((int)fb_buffer_count(&b), 2);
    assert_string_equal(fb_buffer_at(&b, 0)->text, "");
    assert_string_equal(fb_buffer_at(&b, 1)->text, "");
    fb_buffer_free(&b);
}

static void test_count_cap_fails_closed(void **state) {
    (void)state;
    fb_buffer b;
    fb_buffer_init(&b);
    for (size_t i = 0; i < FB_MAX_ENTRIES; ++i)
        assert_int_equal(fb_buffer_push(&b, FB_LOG, "x", 1), 1);
    assert_int_equal((int)fb_buffer_count(&b), (int)FB_MAX_ENTRIES);
    assert_int_equal(b.overflow, 0);

    /* One past the cap: dropped, count unchanged, overflow raised. */
    assert_int_equal(fb_buffer_push(&b, FB_LOG, "x", 1), 0);
    assert_int_equal((int)fb_buffer_count(&b), (int)FB_MAX_ENTRIES);
    assert_int_equal(b.overflow, 1);
    fb_buffer_free(&b);
}

static void test_entry_truncated_not_dropped(void **state) {
    (void)state;
    fb_buffer b;
    fb_buffer_init(&b);
    size_t big = FB_MAX_ENTRY_BYTES + 1000;
    char *huge = malloc(big);
    assert_non_null(huge);
    memset(huge, 'A', big);

    assert_int_equal(fb_buffer_push(&b, FB_WARN, huge, big), 1);
    const fb_entry *e = fb_buffer_at(&b, 0);
    assert_non_null(e);
    assert_int_equal((int)e->len, (int)FB_MAX_ENTRY_BYTES);
    assert_int_equal((int)strlen(e->text), (int)FB_MAX_ENTRY_BYTES);
    free(huge);
    fb_buffer_free(&b);
}

static void test_total_bytes_cap_fails_closed(void **state) {
    (void)state;
    fb_buffer b;
    fb_buffer_init(&b);
    /* Push max-size entries until the total cap is hit; the over-budget push is
     * dropped whole, prior entries remain readable. */
    char *chunk = malloc(FB_MAX_ENTRY_BYTES);
    assert_non_null(chunk);
    memset(chunk, 'B', FB_MAX_ENTRY_BYTES);

    int dropped = 0;
    for (size_t i = 0; i < FB_MAX_ENTRIES; ++i) {
        int r = fb_buffer_push(&b, FB_LOG, chunk, FB_MAX_ENTRY_BYTES);
        if (r == 0) { dropped = 1; break; }
    }
    assert_int_equal(dropped, 1);          /* total cap kicks in before count cap */
    assert_int_equal(b.overflow, 1);
    assert_true(b.total_bytes <= FB_MAX_TOTAL_BYTES);
    assert_true(fb_buffer_count(&b) > 0);  /* earlier entries kept */
    /* The first stored entry is still intact. */
    assert_int_equal((int)fb_buffer_at(&b, 0)->len, (int)FB_MAX_ENTRY_BYTES);
    free(chunk);
    fb_buffer_free(&b);
}

static void test_level_clamped(void **state) {
    (void)state;
    fb_buffer b;
    fb_buffer_init(&b);
    assert_int_equal(fb_buffer_push(&b, -7, "a", 1), 1);
    assert_int_equal(fb_buffer_push(&b, 9999, "b", 1), 1);
    assert_int_equal(fb_buffer_at(&b, 0)->level, FB_LOG);
    assert_int_equal(fb_buffer_at(&b, 1)->level, FB_LOG);
    fb_buffer_free(&b);
}

static void test_level_name(void **state) {
    (void)state;
    assert_string_equal(fb_level_name(FB_LOG), "log");
    assert_string_equal(fb_level_name(FB_INFO), "info");
    assert_string_equal(fb_level_name(FB_WARN), "warn");
    assert_string_equal(fb_level_name(FB_ERROR), "error");
    assert_string_equal(fb_level_name(FB_DEBUG), "debug");
    assert_string_equal(fb_level_name(-1), "log");
    assert_string_equal(fb_level_name(12345), "log");
}

static void test_reset_reuses_and_no_leak(void **state) {
    (void)state;
    fb_buffer b;
    fb_buffer_init(&b);
    for (int i = 0; i < 50; ++i)
        assert_int_equal(fb_buffer_push(&b, FB_LOG, "line", 4), 1);
    /* Force the overflow flag then reset clears it. */
    while (fb_buffer_push(&b, FB_LOG, "x", 1)) { /* fill */ }
    assert_int_equal(b.overflow, 1);

    fb_buffer_reset(&b);
    assert_int_equal((int)fb_buffer_count(&b), 0);
    assert_int_equal((int)b.total_bytes, 0);
    assert_int_equal(b.overflow, 0);
    assert_true(b.cap > 0);                /* array kept for reuse */

    assert_int_equal(fb_buffer_push(&b, FB_INFO, "again", 5), 1);
    assert_string_equal(fb_buffer_at(&b, 0)->text, "again");
    fb_buffer_free(&b);
}

static void test_free_idempotent(void **state) {
    (void)state;
    fb_buffer b;
    fb_buffer_init(&b);
    fb_buffer_push(&b, FB_LOG, "x", 1);
    fb_buffer_free(&b);
    fb_buffer_free(&b);   /* safe twice */
    fb_buffer_free(NULL); /* safe on NULL */
    assert_int_equal((int)fb_buffer_count(&b), 0);
    /* push after free re-initialises lazily */
    assert_int_equal(fb_buffer_push(&b, FB_LOG, "y", 1), 1);
    fb_buffer_free(&b);
}

static void test_push_loc_records_location(void **state) {
    (void)state;
    fb_buffer b;
    fb_buffer_init(&b);
    assert_int_equal(fb_buffer_push_loc(&b, FB_ERROR, "boom", 4, "inline #9", 2, 54), 1);
    /* The plain push records no location. */
    assert_int_equal(fb_buffer_push(&b, FB_LOG, "plain", 5), 1);

    const fb_entry *e0 = fb_buffer_at(&b, 0);
    assert_string_equal(e0->text, "boom");
    assert_non_null(e0->file);
    assert_string_equal(e0->file, "inline #9");
    assert_int_equal(e0->line, 2);
    assert_int_equal(e0->col, 54);

    const fb_entry *e1 = fb_buffer_at(&b, 1);
    assert_null(e1->file);
    assert_int_equal(e1->line, 0);
    assert_int_equal(e1->col, 0);
    fb_buffer_free(&b);
}

static void test_push_loc_null_file_and_negative_nums(void **state) {
    (void)state;
    fb_buffer b;
    fb_buffer_init(&b);
    /* NULL file => no location; negative line/col clamp to 0 (unknown). */
    assert_int_equal(fb_buffer_push_loc(&b, FB_WARN, "w", 1, NULL, -3, -1), 1);
    const fb_entry *e = fb_buffer_at(&b, 0);
    assert_null(e->file);
    assert_int_equal(e->line, 0);
    assert_int_equal(e->col, 0);
    /* reset then free must not leak the file copy (run under ASan). */
    assert_int_equal(fb_buffer_push_loc(&b, FB_LOG, "x", 1, "f", 1, 1), 1);
    fb_buffer_reset(&b);
    assert_int_equal((int)fb_buffer_count(&b), 0);
    fb_buffer_free(&b);
}

static void test_push_loc_file_truncated(void **state) {
    (void)state;
    fb_buffer b;
    fb_buffer_init(&b);
    char big[FB_MAX_FILE_BYTES + 64];
    memset(big, 'a', sizeof big - 1);
    big[sizeof big - 1] = '\0';
    assert_int_equal(fb_buffer_push_loc(&b, FB_ERROR, "x", 1, big, 1, 1), 1);
    const fb_entry *e = fb_buffer_at(&b, 0);
    assert_non_null(e->file);
    assert_int_equal((int)strlen(e->file), (int)FB_MAX_FILE_BYTES);
    fb_buffer_free(&b);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_push_and_read),
        cmocka_unit_test(test_empty_and_null_text),
        cmocka_unit_test(test_count_cap_fails_closed),
        cmocka_unit_test(test_entry_truncated_not_dropped),
        cmocka_unit_test(test_total_bytes_cap_fails_closed),
        cmocka_unit_test(test_level_clamped),
        cmocka_unit_test(test_level_name),
        cmocka_unit_test(test_reset_reuses_and_no_leak),
        cmocka_unit_test(test_free_idempotent),
        cmocka_unit_test(test_push_loc_records_location),
        cmocka_unit_test(test_push_loc_null_file_and_negative_nums),
        cmocka_unit_test(test_push_loc_file_truncated),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
