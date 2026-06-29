#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "hostedit.h"

static void test_make_line_lowercases(void **state) {
    (void)state;
    char out[300];
    assert_int_equal(he_make_line("News.YCombinator.com", out, sizeof out), HE_OK);
    assert_string_equal(out, "news.ycombinator.com\n");
}

static void test_make_line_plain_host(void **state) {
    (void)state;
    char out[64];
    assert_int_equal(he_make_line("example.com", out, sizeof out), HE_OK);
    assert_string_equal(out, "example.com\n");
}

static void test_make_line_rejects_path_scheme_garbage(void **state) {
    (void)state;
    char out[300];
    assert_int_equal(he_make_line("evil.com/../etc", out, sizeof out), HE_ERR_INVALID_HOST);
    assert_int_equal(he_make_line("https://evil.com", out, sizeof out), HE_ERR_INVALID_HOST);
    assert_int_equal(he_make_line("evil.com:8443", out, sizeof out), HE_ERR_INVALID_HOST);
    assert_int_equal(he_make_line("a b.com", out, sizeof out), HE_ERR_INVALID_HOST);
    assert_int_equal(he_make_line("user@host.com", out, sizeof out), HE_ERR_INVALID_HOST);
    assert_int_equal(he_make_line("a\nb.com", out, sizeof out), HE_ERR_INVALID_HOST);
}

static void test_make_line_rejects_bad_labels(void **state) {
    (void)state;
    char out[300];
    assert_int_equal(he_make_line("", out, sizeof out), HE_ERR_INVALID_HOST);
    assert_int_equal(he_make_line("a..b", out, sizeof out), HE_ERR_INVALID_HOST);
    assert_int_equal(he_make_line(".x.com", out, sizeof out), HE_ERR_INVALID_HOST);
    assert_int_equal(he_make_line("x.com.", out, sizeof out), HE_ERR_INVALID_HOST);
    assert_int_equal(he_make_line("-x.com", out, sizeof out), HE_ERR_INVALID_HOST);
    assert_int_equal(he_make_line("x-.com", out, sizeof out), HE_ERR_INVALID_HOST);
}

static void test_make_line_null_and_range(void **state) {
    (void)state;
    char out[8];
    assert_int_equal(he_make_line(NULL, out, sizeof out), HE_ERR_NULL_ARG);
    assert_int_equal(he_make_line("x.com", NULL, 0), HE_ERR_NULL_ARG);
    /* "example.com\n\0" needs 13 bytes; cap 8 is too small. */
    assert_int_equal(he_make_line("example.com", out, sizeof out), HE_ERR_RANGE);
}

static void test_make_line_single_label_ok(void **state) {
    (void)state;
    char out[32];
    assert_int_equal(he_make_line("localhost", out, sizeof out), HE_OK);
    assert_string_equal(out, "localhost\n");
}

static void test_text_has_host(void **state) {
    (void)state;
    const char *text = "# a comment\n0.0.0.0 ads.example\nexample.com\n  News.Site  \n";
    assert_int_equal(he_text_has_host(text, "example.com"), 1);
    assert_int_equal(he_text_has_host(text, "ads.example"), 1);   /* domain token, not the IP */
    assert_int_equal(he_text_has_host(text, "news.site"), 1);     /* case-insensitive */
    assert_int_equal(he_text_has_host(text, "0.0.0.0"), 0);       /* the IP token is ignored */
    assert_int_equal(he_text_has_host(text, "other.com"), 0);
    assert_int_equal(he_text_has_host(text, "example"), 0);       /* not a suffix match */
    assert_int_equal(he_text_has_host(NULL, "x"), 0);
    assert_int_equal(he_text_has_host(text, NULL), 0);
}

static void test_suggest_prefix_first(void **state) {
    (void)state;
    const char *fav = "# favorites\n"
                      "news.ycombinator.com\n"
                      "duckduckgo.com\n"
                      "0.0.0.0 my.duckduckgo.net\n"
                      "example.com\n";
    char res[8][HE_MAX_HOST + 1];
    /* "duck" prefixes duckduckgo.com (pass 1) and is a substring of my.duckduckgo.net
     * (pass 2), so the prefix match comes first. */
    int n = he_suggest(fav, "duck", res, 8);
    assert_int_equal(n, 2);
    assert_string_equal(res[0], "duckduckgo.com");
    assert_string_equal(res[1], "my.duckduckgo.net");
}

static void test_suggest_case_insensitive_and_dedup(void **state) {
    (void)state;
    const char *fav = "Example.com\nexample.com\nfoo.org\n";
    char res[8][HE_MAX_HOST + 1];
    int n = he_suggest(fav, "EXAMP", res, 8);
    assert_int_equal(n, 1);                 /* deduped, lowercased */
    assert_string_equal(res[0], "example.com");
}

static void test_suggest_empty_query_and_cap(void **state) {
    (void)state;
    const char *fav = "a.com\nb.com\nc.com\nd.com\n";
    char res[2][HE_MAX_HOST + 1];
    int n = he_suggest(fav, "", res, 2);    /* "" matches all, capped at 2 */
    assert_int_equal(n, 2);
    assert_string_equal(res[0], "a.com");
    assert_string_equal(res[1], "b.com");
    assert_int_equal(he_suggest(fav, "zzz", res, 2), 0);  /* no match */
    assert_int_equal(he_suggest(NULL, "a", res, 2), 0);
    assert_int_equal(he_suggest(fav, "a", res, 0), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_make_line_lowercases),
        cmocka_unit_test(test_make_line_plain_host),
        cmocka_unit_test(test_make_line_rejects_path_scheme_garbage),
        cmocka_unit_test(test_make_line_rejects_bad_labels),
        cmocka_unit_test(test_make_line_null_and_range),
        cmocka_unit_test(test_make_line_single_label_ok),
        cmocka_unit_test(test_text_has_host),
        cmocka_unit_test(test_suggest_prefix_first),
        cmocka_unit_test(test_suggest_case_insensitive_and_dedup),
        cmocka_unit_test(test_suggest_empty_query_and_cap),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
