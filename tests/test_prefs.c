/*
 * TDD suite for prefs (Hito 10 - pure user-profile model: preferences,
 * bookmarks, persistent history).
 *
 * RED state until src/prefs.c exists: this fails to link on purpose.
 * Build: make test ; ASan: make asan
 */

#define _POSIX_C_SOURCE 200809L

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "prefs.h"
#include "zoom.h"

/* --- defaults ------------------------------------------------------------ */

static void test_init_defaults(void **state) {
    (void)state;
    prefs_state p;
    prefs_init(&p);
    assert_int_equal(p.theme_mode, 0);
    assert_int_equal(p.force_theme, 0);
    assert_int_equal(p.images, 0);
    assert_int_equal(p.css, 0);
    assert_int_equal(p.reader, 0);
    assert_int_equal(p.js_mode, 1);          /* allowlist */
    assert_int_equal(p.tor, 0);
    assert_int_equal(p.i2p, 0);
    assert_int_equal(p.torify, 0);
    assert_int_equal(p.zoom_pct, 100);
    assert_int_equal(p.remember_history, 1);
    assert_int_equal(p.bookmarks_len, 0);
    assert_int_equal(p.history_len, 0);
    prefs_free(&p);
    prefs_free(&p);   /* idempotent */
    prefs_init(NULL); /* NULL-safe */
    prefs_free(NULL);
}

/* --- round-trip ----------------------------------------------------------- */

static void test_roundtrip(void **state) {
    (void)state;
    prefs_state p;
    prefs_init(&p);
    p.theme_mode = 2;
    p.force_theme = 1;
    p.images = 1;
    p.css = 1;
    p.reader = 1;
    p.js_mode = 2;
    p.tor = 1;
    p.i2p = 1;
    p.torify = 1;
    p.zoom_pct = 125;
    p.remember_history = 0;
    int added = -1;
    assert_int_equal(prefs_bookmark_toggle(&p, "https://example.com/a",
                                           "Example A", &added), PREFS_OK);
    assert_int_equal(added, 1);
    assert_int_equal(prefs_bookmark_toggle(&p, "https://example.org/b",
                                           NULL, &added), PREFS_OK);
    assert_int_equal(prefs_history_add(&p, "https://one.test/"), PREFS_OK);
    assert_int_equal(prefs_history_add(&p, "https://two.test/"), PREFS_OK);

    char *text = NULL;
    size_t len = 0;
    assert_int_equal(prefs_format(&p, &text, &len), PREFS_OK);
    assert_non_null(text);
    assert_int_equal(strlen(text), len);

    prefs_state q;
    prefs_init(&q);
    assert_int_equal(prefs_parse(text, len, &q), PREFS_OK);
    assert_int_equal(q.theme_mode, 2);
    assert_int_equal(q.force_theme, 1);
    assert_int_equal(q.images, 1);
    assert_int_equal(q.css, 1);
    assert_int_equal(q.reader, 1);
    assert_int_equal(q.js_mode, 2);
    assert_int_equal(q.tor, 1);
    assert_int_equal(q.i2p, 1);
    assert_int_equal(q.torify, 1);
    assert_int_equal(q.zoom_pct, 125);
    assert_int_equal(q.remember_history, 0);
    assert_int_equal(q.bookmarks_len, 2);
    assert_string_equal(q.bookmarks[0].url, "https://example.com/a");
    assert_string_equal(q.bookmarks[0].title, "Example A");
    assert_string_equal(q.bookmarks[1].url, "https://example.org/b");
    assert_string_equal(q.bookmarks[1].title, "");
    assert_int_equal(q.history_len, 2);
    assert_string_equal(q.history[0], "https://two.test/");  /* most recent first */
    assert_string_equal(q.history[1], "https://one.test/");

    free(text);
    prefs_free(&p);
    prefs_free(&q);
}

/* --- parse: fail closed / forward compat ---------------------------------- */

static void test_parse_bad_magic(void **state) {
    (void)state;
    prefs_state p;
    prefs_init(&p);
    const char *bad = "not-a-prefs-file 1\ntheme=2\n";
    assert_int_equal(prefs_parse(bad, strlen(bad), &p), PREFS_ERR_FORMAT);
    assert_int_equal(p.theme_mode, 0);  /* untouched defaults */
    const char *badver = "freedom-prefs 999\ntheme=2\n";
    assert_int_equal(prefs_parse(badver, strlen(badver), &p), PREFS_ERR_FORMAT);
    assert_int_equal(p.theme_mode, 0);
    assert_int_equal(prefs_parse("", 0, &p), PREFS_ERR_FORMAT);
    assert_int_equal(prefs_parse(NULL, 0, &p), PREFS_ERR_NULL_ARG);
    assert_int_equal(prefs_parse("freedom-prefs 1\n", 16, NULL), PREFS_ERR_NULL_ARG);
    prefs_free(&p);
}

static void test_parse_too_large(void **state) {
    (void)state;
    prefs_state p;
    prefs_init(&p);
    assert_int_equal(prefs_parse("freedom-prefs 1\n", PREFS_MAX_TEXT + 1, &p),
                     PREFS_ERR_FORMAT);
    prefs_free(&p);
}

static void test_parse_unknown_and_malformed_skipped(void **state) {
    (void)state;
    prefs_state p;
    prefs_init(&p);
    const char *text =
        "freedom-prefs 1\n"
        "futurekey=42\n"
        "zoom=150\n"
        "garbage line without equals\n"
        "b\tonly-two-fields\n"           /* malformed bookmark: skipped */
        "b\thttps://ok.test/\tTitle\n"
        "h\t\n"                          /* empty URL: skipped */
        "h\thttps://visited.test/\n";
    assert_int_equal(prefs_parse(text, strlen(text), &p), PREFS_OK);
    assert_int_equal(p.zoom_pct, 150);
    assert_int_equal(p.bookmarks_len, 1);
    assert_string_equal(p.bookmarks[0].url, "https://ok.test/");
    assert_int_equal(p.history_len, 1);
    assert_string_equal(p.history[0], "https://visited.test/");
    prefs_free(&p);
}

static void test_parse_clamps_out_of_range(void **state) {
    (void)state;
    prefs_state p;
    prefs_init(&p);
    const char *text =
        "freedom-prefs 1\n"
        "theme=99\n"
        "js=7\n"
        "zoom=9999\n"
        "images=5\n"
        "tor=-3\n";
    assert_int_equal(prefs_parse(text, strlen(text), &p), PREFS_OK);
    assert_int_equal(p.theme_mode, 0);            /* out of range -> safe default */
    assert_int_equal(p.js_mode, 1);               /* out of range -> allowlist */
    assert_int_equal(p.zoom_pct, zm_clamp(9999)); /* the ladder owns the bounds */
    assert_int_equal(p.images, 1);                /* nonzero -> 1 */
    assert_int_equal(p.tor, 1);
    prefs_free(&p);
}

/* --- URL validation (fail closed) ------------------------------------------ */

static void test_invalid_urls_rejected(void **state) {
    (void)state;
    prefs_state p;
    prefs_init(&p);
    int added = -1;
    assert_int_equal(prefs_bookmark_toggle(&p, NULL, "t", &added),
                     PREFS_ERR_NULL_ARG);
    assert_int_equal(prefs_bookmark_toggle(&p, "", "t", &added), PREFS_ERR_INVALID);
    assert_int_equal(prefs_bookmark_toggle(&p, "https://a\tb", "t", &added),
                     PREFS_ERR_INVALID);
    assert_int_equal(prefs_bookmark_toggle(&p, "https://a\nb", "t", &added),
                     PREFS_ERR_INVALID);
    assert_int_equal(prefs_bookmark_toggle(&p, "https://a\x01g", "t", &added),
                     PREFS_ERR_INVALID);
    char big[PREFS_MAX_URL + 8];
    memset(big, 'a', sizeof big - 1);
    big[sizeof big - 1] = '\0';
    assert_int_equal(prefs_bookmark_toggle(&p, big, "t", &added), PREFS_ERR_INVALID);
    assert_int_equal(prefs_history_add(&p, "no\x7f" "del"), PREFS_ERR_INVALID);
    assert_int_equal(p.bookmarks_len, 0);
    assert_int_equal(p.history_len, 0);
    /* A local path with a space IS representable (tab-separated format is safe). */
    assert_int_equal(prefs_history_add(&p, "docs/my page.html"), PREFS_OK);
    prefs_free(&p);
}

/* --- hostile titles are cleaned, never fatal -------------------------------- */

static void test_hostile_title_cleaned(void **state) {
    (void)state;
    prefs_state p;
    prefs_init(&p);
    int added = -1;
    assert_int_equal(prefs_bookmark_toggle(&p, "https://x.test/",
                                           "a\tb\nc\x01" "d", &added), PREFS_OK);
    assert_string_equal(p.bookmarks[0].title, "a b c d");

    /* Truncation lands on a UTF-8 boundary: a run of 2-byte chars never keeps
     * a dangling lead byte. */
    char long_title[PREFS_MAX_TITLE * 2 + 4];
    size_t n = 0;
    while (n + 2 < sizeof long_title - 1) {
        long_title[n++] = (char)0xC3;  /* 'á' = C3 A1 */
        long_title[n++] = (char)0xA1;
    }
    long_title[n] = '\0';
    assert_int_equal(prefs_bookmark_toggle(&p, "https://y.test/",
                                           long_title, &added), PREFS_OK);
    const char *kept = p.bookmarks[1].title;
    size_t klen = strlen(kept);
    assert_true(klen <= PREFS_MAX_TITLE);
    assert_true(klen > 0);
    assert_true(klen % 2 == 0);  /* whole 2-byte sequences only */
    prefs_free(&p);
}

/* --- bookmark toggle ---------------------------------------------------------- */

static void test_bookmark_toggle_and_cap(void **state) {
    (void)state;
    prefs_state p;
    prefs_init(&p);
    int added = -1;
    assert_int_equal(prefs_bookmark_toggle(&p, "https://a.test/", "A", &added),
                     PREFS_OK);
    assert_int_equal(added, 1);
    assert_int_equal(prefs_bookmark_index(&p, "https://a.test/"), 0);
    assert_int_equal(prefs_bookmark_index(&p, "https://other.test/"), -1);
    assert_int_equal(prefs_bookmark_toggle(&p, "https://a.test/", "A", &added),
                     PREFS_OK);
    assert_int_equal(added, 0);
    assert_int_equal(p.bookmarks_len, 0);

    char url[64];
    for (size_t i = 0; i < PREFS_MAX_BOOKMARKS; ++i) {
        snprintf(url, sizeof url, "https://cap.test/%zu", i);
        assert_int_equal(prefs_bookmark_toggle(&p, url, "t", &added), PREFS_OK);
    }
    assert_int_equal(p.bookmarks_len, PREFS_MAX_BOOKMARKS);
    assert_int_equal(prefs_bookmark_toggle(&p, "https://cap.test/full", "t", &added),
                     PREFS_ERR_FULL);
    prefs_free(&p);
}

/* --- history dedup / move-to-front / eviction ---------------------------------- */

static void test_history_dedup_and_evict(void **state) {
    (void)state;
    prefs_state p;
    prefs_init(&p);
    assert_int_equal(prefs_history_add(&p, "https://a.test/"), PREFS_OK);
    assert_int_equal(prefs_history_add(&p, "https://b.test/"), PREFS_OK);
    assert_int_equal(prefs_history_add(&p, "https://b.test/"), PREFS_OK); /* front no-op */
    assert_int_equal(p.history_len, 2);
    assert_int_equal(prefs_history_add(&p, "https://a.test/"), PREFS_OK); /* moves up */
    assert_int_equal(p.history_len, 2);
    assert_string_equal(p.history[0], "https://a.test/");
    assert_string_equal(p.history[1], "https://b.test/");

    char url[64];
    for (size_t i = 0; i < PREFS_MAX_HISTORY + 10; ++i) {
        snprintf(url, sizeof url, "https://h.test/%zu", i);
        assert_int_equal(prefs_history_add(&p, url), PREFS_OK);
    }
    assert_int_equal(p.history_len, PREFS_MAX_HISTORY);
    assert_string_equal(p.history[0], "https://h.test/509"); /* newest kept */
    prefs_free(&p);
}

/* --- omnibox suggestions -------------------------------------------------------- */

static void test_suggest_priorities(void **state) {
    (void)state;
    prefs_state p;
    prefs_init(&p);
    int added;
    /* bookmark whose URL prefix-matches past scheme + www. */
    assert_int_equal(prefs_bookmark_toggle(&p, "https://www.wikipedia.org/",
                                           "Wikipedia", &added), PREFS_OK);
    /* bookmark matching only by title substring */
    assert_int_equal(prefs_bookmark_toggle(&p, "https://n.example/",
                                           "wiki notes", &added), PREFS_OK);
    /* history entries: one prefix, one substring */
    assert_int_equal(prefs_history_add(&p, "https://wikimedia.org/"), PREFS_OK);
    assert_int_equal(prefs_history_add(&p, "https://es.wikipedia.org/wiki/C"),
                     PREFS_OK);

    char rows[6][254];
    int n = prefs_suggest(&p, "wiki", (char *)rows, sizeof rows[0], 6);
    assert_int_equal(n, 4);
    /* bookmark prefix first (scheme+www skipped), then history prefix (newest
     * first), then substring matches. */
    assert_string_equal(rows[0], "https://www.wikipedia.org/");
    assert_string_equal(rows[1], "https://wikimedia.org/");
    assert_string_equal(rows[2], "https://n.example/");           /* title match */
    assert_string_equal(rows[3], "https://es.wikipedia.org/wiki/C");

    /* Case-insensitive; empty query lists bookmarks first. */
    n = prefs_suggest(&p, "WIKI", (char *)rows, sizeof rows[0], 6);
    assert_int_equal(n, 4);
    n = prefs_suggest(&p, "", (char *)rows, sizeof rows[0], 6);
    assert_int_equal(n, 4);
    assert_string_equal(rows[0], "https://www.wikipedia.org/");

    /* Dedup: a URL both bookmarked and in history appears once. */
    assert_int_equal(prefs_history_add(&p, "https://www.wikipedia.org/"), PREFS_OK);
    n = prefs_suggest(&p, "wikipedia", (char *)rows, sizeof rows[0], 6);
    int seen = 0;
    for (int i = 0; i < n; ++i)
        if (strcmp(rows[i], "https://www.wikipedia.org/") == 0) seen++;
    assert_int_equal(seen, 1);

    /* Rows too small for a URL: that URL is skipped, no overflow. */
    char tiny[6][16];
    n = prefs_suggest(&p, "wiki", (char *)tiny, sizeof tiny[0], 6);
    assert_int_equal(n, 0);

    assert_int_equal(prefs_suggest(NULL, "q", (char *)rows, sizeof rows[0], 6), 0);
    assert_int_equal(prefs_suggest(&p, NULL, (char *)rows, sizeof rows[0], 6), 0);
    assert_int_equal(prefs_suggest(&p, "q", NULL, sizeof rows[0], 6), 0);
    assert_int_equal(prefs_suggest(&p, "q", (char *)rows, sizeof rows[0], 0), 0);
    prefs_free(&p);
}

/* --- bookmarks page: hostile text is escaped -------------------------------------- */

static void test_bookmarks_page_escapes(void **state) {
    (void)state;
    prefs_state p;
    prefs_init(&p);
    int added;
    assert_int_equal(prefs_bookmark_toggle(&p,
        "https://x.test/?a=1&b=<2>", "<script>alert('pwn')</script>", &added),
        PREFS_OK);
    assert_int_equal(prefs_history_add(&p, "https://h.test/\"quoted\""), PREFS_OK);

    char *html = NULL;
    size_t len = 0;
    assert_int_equal(prefs_bookmarks_page(&p, &html, &len), PREFS_OK);
    assert_non_null(html);
    assert_int_equal(strlen(html), len);
    assert_null(strstr(html, "<script>"));           /* never verbatim */
    assert_non_null(strstr(html, "&lt;script&gt;")); /* escaped as text */
    assert_null(strstr(html, "\"quoted\""));         /* quotes escaped in href */
    assert_non_null(strstr(html, "&quot;quoted&quot;"));
    assert_non_null(strstr(html, "a=1&amp;b=&lt;2&gt;"));
    free(html);

    /* Empty state still yields a valid page. */
    prefs_state q;
    prefs_init(&q);
    assert_int_equal(prefs_bookmarks_page(&q, &html, &len), PREFS_OK);
    assert_non_null(strstr(html, "Ctrl+B"));  /* the hint for an empty profile */
    free(html);
    prefs_free(&q);

    assert_int_equal(prefs_bookmarks_page(NULL, &html, &len), PREFS_ERR_NULL_ARG);
    assert_int_equal(prefs_bookmarks_page(&p, NULL, &len), PREFS_ERR_NULL_ARG);
    prefs_free(&p);
}

/* --- format: NULL args -------------------------------------------------------------- */

static void test_format_null_args(void **state) {
    (void)state;
    prefs_state p;
    prefs_init(&p);
    char *text = NULL;
    size_t len = 0;
    assert_int_equal(prefs_format(NULL, &text, &len), PREFS_ERR_NULL_ARG);
    assert_int_equal(prefs_format(&p, NULL, &len), PREFS_ERR_NULL_ARG);
    assert_int_equal(prefs_format(&p, &text, NULL), PREFS_ERR_NULL_ARG);
    prefs_free(&p);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init_defaults),
        cmocka_unit_test(test_roundtrip),
        cmocka_unit_test(test_parse_bad_magic),
        cmocka_unit_test(test_parse_too_large),
        cmocka_unit_test(test_parse_unknown_and_malformed_skipped),
        cmocka_unit_test(test_parse_clamps_out_of_range),
        cmocka_unit_test(test_invalid_urls_rejected),
        cmocka_unit_test(test_hostile_title_cleaned),
        cmocka_unit_test(test_bookmark_toggle_and_cap),
        cmocka_unit_test(test_history_dedup_and_evict),
        cmocka_unit_test(test_suggest_priorities),
        cmocka_unit_test(test_bookmarks_page_escapes),
        cmocka_unit_test(test_format_null_args),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
