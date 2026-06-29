/*
 * TDD suite for browser (Hito 5+ GUI navigation state).
 *
 * Tests the pure state machine: history, URL bar, navigation rules.
 * Build: make test   ;   ASan: make asan
 */

#define _POSIX_C_SOURCE 200809L

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "browser.h"

static void test_init(void **state) {
    (void)state;
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    assert_int_equal(browser_init(&bs), BROWSER_OK);
    assert_string_equal(bs.url_bar, "about:blank");
    assert_false(browser_can_back(&bs));
    assert_false(browser_can_forward(&bs));
    browser_free(&bs);
}

static void test_navigate_history(void **state) {
    (void)state;
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    assert_int_equal(browser_init(&bs), BROWSER_OK);

    assert_int_equal(browser_navigate(&bs, "/a.html"), BROWSER_OK);
    assert_string_equal(browser_current_url(&bs), "/a.html");
    assert_false(browser_can_back(&bs));

    assert_int_equal(browser_navigate(&bs, "/b.html"), BROWSER_OK);
    assert_string_equal(browser_current_url(&bs), "/b.html");
    assert_true(browser_can_back(&bs));

    assert_int_equal(browser_navigate(&bs, "/c.html"), BROWSER_OK);
    assert_string_equal(browser_current_url(&bs), "/c.html");
    assert_true(browser_can_back(&bs));
    assert_false(browser_can_forward(&bs));

    assert_int_equal(browser_back(&bs), BROWSER_OK);
    assert_string_equal(browser_current_url(&bs), "/b.html");
    assert_true(browser_can_back(&bs));
    assert_true(browser_can_forward(&bs));

    assert_int_equal(browser_forward(&bs), BROWSER_OK);
    assert_string_equal(browser_current_url(&bs), "/c.html");

    browser_free(&bs);
}

static void test_navigate_from_middle_discards_future(void **state) {
    (void)state;
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    assert_int_equal(browser_init(&bs), BROWSER_OK);

    browser_navigate(&bs, "/a.html");
    browser_navigate(&bs, "/b.html");
    browser_navigate(&bs, "/c.html");
    browser_back(&bs); /* now at b */

    assert_int_equal(browser_navigate(&bs, "/d.html"), BROWSER_OK);
    assert_string_equal(browser_current_url(&bs), "/d.html");
    assert_false(browser_can_forward(&bs));

    browser_free(&bs);
}

static void test_back_forward_bounds(void **state) {
    (void)state;
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    assert_int_equal(browser_init(&bs), BROWSER_OK);

    assert_int_equal(browser_back(&bs), BROWSER_ERR_NO_BACK);
    assert_int_equal(browser_forward(&bs), BROWSER_ERR_NO_FORWARD);

    browser_navigate(&bs, "/x.html");
    assert_int_equal(browser_forward(&bs), BROWSER_ERR_NO_FORWARD);
    assert_int_equal(browser_back(&bs), BROWSER_ERR_NO_BACK);

    browser_free(&bs);
}

static void test_rejects_invalid_url(void **state) {
    (void)state;
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    assert_int_equal(browser_init(&bs), BROWSER_OK);

    assert_int_equal(browser_navigate(&bs, "http://example.com"), BROWSER_ERR_INVALID_URL);
    assert_int_equal(browser_navigate(&bs, "javascript:alert(1)"), BROWSER_ERR_INVALID_URL);
    assert_int_equal(browser_navigate(&bs, ""), BROWSER_ERR_INVALID_URL);

    browser_free(&bs);
}

static void test_accepts_https_and_file(void **state) {
    (void)state;
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    assert_int_equal(browser_init(&bs), BROWSER_OK);

    assert_int_equal(browser_navigate(&bs, "https://example.com"), BROWSER_OK);
    assert_string_equal(browser_current_url(&bs), "https://example.com");
    assert_int_equal(browser_navigate(&bs, "/tmp/page.html"), BROWSER_OK);
    assert_int_equal(browser_navigate(&bs, "./page.html"), BROWSER_OK);

    browser_free(&bs);
}

static void test_url_bar_editing(void **state) {
    (void)state;
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    assert_int_equal(browser_init(&bs), BROWSER_OK);

    browser_url_bar_clear(&bs);
    assert_string_equal(bs.url_bar, "");

    browser_url_bar_insert(&bs, 'h');
    browser_url_bar_insert(&bs, 'i');
    assert_string_equal(bs.url_bar, "hi");
    assert_int_equal(bs.url_bar_cursor, 2);

    browser_url_bar_move_cursor(&bs, -1);
    browser_url_bar_insert(&bs, 'o');
    assert_string_equal(bs.url_bar, "hoi");

    browser_url_bar_backspace(&bs);
    assert_string_equal(bs.url_bar, "hi");

    browser_url_bar_move_cursor(&bs, 100);
    browser_url_bar_delete(&bs); /* at end: no-op */
    assert_string_equal(bs.url_bar, "hi");

    browser_free(&bs);
}

/* Omnibar selection model: extend builds a selection, ops replace/delete it, and a
 * plain move collapses it. */
static void test_url_bar_selection(void **state) {
    (void)state;
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    assert_int_equal(browser_init(&bs), BROWSER_OK);

    browser_set_url_bar(&bs, "example.com");
    size_t s = 99, l = 99;
    assert_int_equal(browser_url_bar_selection(&bs, &s, &l), 0); /* no selection yet */

    /* Select all, then report the range. */
    browser_url_bar_select_all(&bs);
    assert_int_equal(browser_url_bar_selection(&bs, &s, &l), 1);
    assert_int_equal((int)s, 0);
    assert_int_equal((int)l, 11);

    /* Typing over the selection replaces it. */
    browser_url_bar_insert(&bs, 'x');
    assert_string_equal(bs.url_bar, "x");
    assert_int_equal(browser_url_bar_selection(&bs, &s, &l), 0); /* collapsed */

    /* Build a selection with extend, then backspace deletes exactly it. */
    browser_set_url_bar(&bs, "abcdef");
    browser_url_bar_set_cursor(&bs, 2, 0);          /* cursor at 'c', no selection */
    browser_url_bar_extend_cursor(&bs, 3);          /* select "cde" */
    assert_int_equal(browser_url_bar_selection(&bs, &s, &l), 1);
    assert_int_equal((int)s, 2);
    assert_int_equal((int)l, 3);
    browser_url_bar_backspace(&bs);
    assert_string_equal(bs.url_bar, "abf");
    assert_int_equal((int)bs.url_bar_cursor, 2);

    /* A plain move collapses any selection. */
    browser_url_bar_select_all(&bs);
    browser_url_bar_move_cursor(&bs, -1);
    assert_int_equal(browser_url_bar_selection(&bs, &s, &l), 0);

    /* delete_selection returns 0 with nothing selected, and is NULL-safe. */
    assert_int_equal(browser_url_bar_delete_selection(&bs), 0);
    assert_int_equal(browser_url_bar_selection(NULL, &s, &l), 0);

    browser_free(&bs);
}

static void test_set_page(void **state) {
    (void)state;
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    assert_int_equal(browser_init(&bs), BROWSER_OK);

    assert_int_equal(browser_set_page(&bs, "Title", "Hello", 0), BROWSER_OK);
    assert_string_equal(bs.page_title, "Title");
    assert_string_equal(bs.page_text, "Hello");
    assert_int_equal(bs.loading_error, 0);

    assert_int_equal(browser_set_page(&bs, NULL, "Bad cert", 1), BROWSER_OK);
    assert_string_equal(bs.page_title, "Error");
    assert_string_equal(bs.page_text, "Bad cert");
    assert_int_equal(bs.loading_error, 1);

    browser_free(&bs);
}

/* Page title/text come from hostile documents; legacy encodings (Latin-1) carry
 * bytes that are invalid UTF-8 and poison the cairo text renderer. browser_set_page
 * must store well-formed UTF-8, substituting '?' for any invalid byte. */
static void test_set_page_sanitizes_invalid_utf8(void **state) {
    (void)state;
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    assert_int_equal(browser_init(&bs), BROWSER_OK);

    /* "Im" + 0xE1 (Latin-1 'a-acute', invalid UTF-8) + "genes": the lone high byte
     * is recovered as Windows-1252 and re-emitted as UTF-8 ("Imágenes"). */
    const char latin1_text[] = { 'I', 'm', (char)0xE1, 'g', 'e', 'n', 'e', 's', '\0' };
    const char latin1_title[] = { 'C', 'a', 'f', (char)0xE9, '\0' }; /* "Caf" + 0xE9 */

    assert_int_equal(browser_set_page(&bs, latin1_title, latin1_text, 0), BROWSER_OK);
    assert_string_equal(bs.page_text, "Im\xC3\xA1genes");
    assert_string_equal(bs.page_title, "Caf\xC3\xA9");

    /* Well-formed UTF-8 (2-byte 'a-acute' = 0xC3 0xA1) must pass through intact. */
    const char utf8_text[] = { 'I', 'm', (char)0xC3, (char)0xA1, 'g', 'e', 'n', 'e', 's', '\0' };
    assert_int_equal(browser_set_page(&bs, "ok", utf8_text, 0), BROWSER_OK);
    assert_string_equal(bs.page_text, utf8_text);

    /* A lone 0x80 (Windows-1252 Euro) and a truncated lead 0xE0 (Latin-1 'a-grave')
     * are both decoded, not dropped: "€aà". */
    const char broken[] = { (char)0x80, 'a', (char)0xE0, '\0' };
    assert_int_equal(browser_set_page(&bs, "x", broken, 0), BROWSER_OK);
    assert_string_equal(bs.page_text, "\xE2\x82\xAC" "a" "\xC3\xA0");

    /* An undefined Windows-1252 position (0x81) has no glyph and still fails to '?'. */
    const char undef[] = { 'a', (char)0x81, 'b', '\0' };
    assert_int_equal(browser_set_page(&bs, "x", undef, 0), BROWSER_OK);
    assert_string_equal(bs.page_text, "a?b");

    browser_free(&bs);
}

static void test_exceptions(void **state) {
    (void)state;
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    assert_int_equal(browser_init(&bs), BROWSER_OK);

    assert_false(browser_is_exception(&bs, "example.com"));
    assert_int_equal(browser_add_exception(&bs, "example.com"), BROWSER_OK);
    assert_true(browser_is_exception(&bs, "example.com"));
    assert_true(browser_is_exception(&bs, "EXAMPLE.COM")); /* case-insensitive */
    assert_false(browser_is_exception(&bs, "example.org"));

    /* Idempotent. */
    assert_int_equal(browser_add_exception(&bs, "example.com"), BROWSER_OK);
    assert_int_equal(bs.exceptions_len, 1);

    assert_int_equal(browser_add_exception(&bs, NULL), BROWSER_ERR_NULL);
    assert_false(browser_is_exception(&bs, NULL));

    browser_free(&bs);
}

/* The transient status line (toast) is time-bounded and caller-clocked: visible
 * until now_ms reaches the expiry, then gone. NULL/empty clears it, and any real
 * navigation drops a stale toast. */
static void test_status_toast(void **state) {
    (void)state;
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    assert_int_equal(browser_init(&bs), BROWSER_OK);

    assert_null(browser_status_text(&bs, 0)); /* none initially */

    assert_int_equal(browser_set_status(&bs, "blocked: insecure http link", 1000), BROWSER_OK);
    assert_string_equal(browser_status_text(&bs, 1000), "blocked: insecure http link");
    assert_string_equal(browser_status_text(&bs, 1000 + BROWSER_STATUS_DURATION_MS - 1),
                        "blocked: insecure http link");
    assert_null(browser_status_text(&bs, 1000 + BROWSER_STATUS_DURATION_MS)); /* expired */

    /* Empty/NULL clears immediately. */
    assert_int_equal(browser_set_status(&bs, "x", 0), BROWSER_OK);
    assert_non_null(browser_status_text(&bs, 0));
    assert_int_equal(browser_set_status(&bs, NULL, 0), BROWSER_OK);
    assert_null(browser_status_text(&bs, 0));
    assert_int_equal(browser_set_status(&bs, "", 0), BROWSER_OK);
    assert_null(browser_status_text(&bs, 0));

    /* A navigation drops a stale toast. */
    assert_int_equal(browser_set_status(&bs, "still here", 0), BROWSER_OK);
    assert_int_equal(browser_navigate(&bs, "/p.html"), BROWSER_OK);
    assert_null(browser_status_text(&bs, 0));

    assert_int_equal(browser_set_status(NULL, "y", 0), BROWSER_ERR_NULL);

    browser_free(&bs);
}

static void test_status_truncates(void **state) {
    (void)state;
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    assert_int_equal(browser_init(&bs), BROWSER_OK);

    char big[BROWSER_STATUS_MAX + 64];
    memset(big, 'a', sizeof big - 1);
    big[sizeof big - 1] = '\0';
    assert_int_equal(browser_set_status(&bs, big, 0), BROWSER_OK);
    const char *got = browser_status_text(&bs, 0);
    assert_non_null(got);
    assert_int_equal((int)strlen(got), BROWSER_STATUS_MAX - 1);

    browser_free(&bs);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init),
        cmocka_unit_test(test_navigate_history),
        cmocka_unit_test(test_navigate_from_middle_discards_future),
        cmocka_unit_test(test_back_forward_bounds),
        cmocka_unit_test(test_rejects_invalid_url),
        cmocka_unit_test(test_accepts_https_and_file),
        cmocka_unit_test(test_url_bar_editing),
        cmocka_unit_test(test_url_bar_selection),
        cmocka_unit_test(test_set_page),
        cmocka_unit_test(test_set_page_sanitizes_invalid_utf8),
        cmocka_unit_test(test_exceptions),
        cmocka_unit_test(test_status_toast),
        cmocka_unit_test(test_status_truncates),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
