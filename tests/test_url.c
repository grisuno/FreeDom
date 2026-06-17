/*
 * test_url — CMocka suite for the pure url module.
 *
 * Covers validation, scheme detection, dot-segment removal and the full
 * reference-resolution matrix (absolute, scheme-relative, absolute-path,
 * relative-path), the secure rejections (http downgrade, foreign schemes), and
 * the bounded-buffer / fail-closed edges.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "url.h"

/* --- url_is_https / url_validate_https --- */

static void test_is_https(void **state) {
    (void)state;
    assert_int_equal(url_is_https("https://example.com"), 1);
    assert_int_equal(url_is_https("HTTPS://EXAMPLE.COM"), 1);
    assert_int_equal(url_is_https("https://example.com/path?q=1#f"), 1);
    assert_int_equal(url_is_https("http://example.com"), 0);
    assert_int_equal(url_is_https("https://"), 0);
    assert_int_equal(url_is_https("https:///nohostslash"), 0);
    assert_int_equal(url_is_https("ftp://x"), 0);
    assert_int_equal(url_is_https("example.com"), 0);
    assert_int_equal(url_is_https(NULL), 0);
}

static void test_validate_https(void **state) {
    (void)state;
    assert_int_equal(url_validate_https(NULL), URL_ERR_NULL_ARG);
    assert_int_equal(url_validate_https("https://example.com/path"), URL_OK);
    assert_int_equal(url_validate_https("HTTPS://EXAMPLE.COM"), URL_OK);
    assert_int_equal(url_validate_https("http://example.com"), URL_ERR_NOT_HTTPS);
    assert_int_equal(url_validate_https("file:///etc/passwd"), URL_ERR_NOT_HTTPS);
    assert_int_equal(url_validate_https("javascript:alert(1)"), URL_ERR_NOT_HTTPS);
    assert_int_equal(url_validate_https("https://"), URL_ERR_NOT_HTTPS);
}

/* --- url_has_scheme --- */

static void test_has_scheme(void **state) {
    (void)state;
    assert_int_equal(url_has_scheme("https://x"), 1);
    assert_int_equal(url_has_scheme("mailto:a@b"), 1);
    assert_int_equal(url_has_scheme("javascript:void(0)"), 1);
    assert_int_equal(url_has_scheme("a+b-c.d:x"), 1);
    assert_int_equal(url_has_scheme("//host/path"), 0);
    assert_int_equal(url_has_scheme("/abs/path"), 0);
    assert_int_equal(url_has_scheme("relative/path"), 0);
    assert_int_equal(url_has_scheme("#fragment"), 0);
    assert_int_equal(url_has_scheme("?query"), 0);
    assert_int_equal(url_has_scheme("3com:x"), 0); /* scheme must start with ALPHA */
    assert_int_equal(url_has_scheme(NULL), 0);
}

/* --- url_authority_len --- */

static void test_authority_len(void **state) {
    (void)state;
    assert_int_equal((int)url_authority_len("https://h.example"), 17);
    assert_int_equal((int)url_authority_len("https://h.example/a/b"), 17);
    assert_int_equal((int)url_authority_len("https://h.example:8443/x"), 22);
}

/* --- url_remove_dot_segments --- */

static void test_remove_dot_segments(void **state) {
    (void)state;
    char out[256];

    assert_int_equal(url_remove_dot_segments("/a/b/c", out, sizeof out), URL_OK);
    assert_string_equal(out, "/a/b/c");

    assert_int_equal(url_remove_dot_segments("/a/./b", out, sizeof out), URL_OK);
    assert_string_equal(out, "/a/b");

    assert_int_equal(url_remove_dot_segments("/a/b/../c", out, sizeof out), URL_OK);
    assert_string_equal(out, "/a/c");

    assert_int_equal(url_remove_dot_segments("/a/b/..", out, sizeof out), URL_OK);
    assert_string_equal(out, "/a/");

    assert_int_equal(url_remove_dot_segments("/../../x", out, sizeof out), URL_OK);
    assert_string_equal(out, "/x"); /* cannot climb above root */

    assert_int_equal(url_remove_dot_segments("/a//b", out, sizeof out), URL_OK);
    assert_string_equal(out, "/a//b"); /* empty segments are preserved, only . and .. collapse */

    assert_int_equal(url_remove_dot_segments("a/b/../c", out, sizeof out), URL_OK);
    assert_string_equal(out, "a/c"); /* relative path keeps relativity */

    assert_int_equal(url_remove_dot_segments("/a/b/", out, sizeof out), URL_OK);
    assert_string_equal(out, "/a/b/"); /* trailing slash preserved */
}

static void test_remove_dot_segments_nulls(void **state) {
    (void)state;
    char out[8];
    assert_int_equal(url_remove_dot_segments(NULL, out, sizeof out), URL_ERR_NULL_ARG);
    assert_int_equal(url_remove_dot_segments("/a", NULL, sizeof out), URL_ERR_NULL_ARG);
    assert_int_equal(url_remove_dot_segments("/a", out, 0), URL_ERR_NULL_ARG);
    assert_int_equal(url_remove_dot_segments("/aaaaaaaaaaaaaa", out, sizeof out), URL_ERR_OVERFLOW);
}

/* --- url_resolve_https --- */

static void test_resolve_absolute(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(url_resolve_https("https://a.example/", "https://b.example/y",
                                       out, sizeof out), URL_OK);
    assert_string_equal(out, "https://b.example/y");
}

static void test_resolve_rejects_downgrade_and_schemes(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(url_resolve_https("https://a.example/", "http://a.example/",
                                       out, sizeof out), URL_ERR_NOT_HTTPS);
    assert_int_equal(url_resolve_https("https://a.example/", "javascript:alert(1)",
                                       out, sizeof out), URL_ERR_NOT_HTTPS);
    assert_int_equal(url_resolve_https("https://a.example/", "data:text/html,x",
                                       out, sizeof out), URL_ERR_NOT_HTTPS);
    assert_int_equal(url_resolve_https("https://a.example/", "mailto:a@b",
                                       out, sizeof out), URL_ERR_NOT_HTTPS);
    assert_int_equal(url_resolve_https("https://a.example/", "ftp://a.example/",
                                       out, sizeof out), URL_ERR_NOT_HTTPS);
}

static void test_resolve_scheme_relative(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(url_resolve_https("https://a.example/x", "//b.example/y",
                                       out, sizeof out), URL_OK);
    assert_string_equal(out, "https://b.example/y");
}

static void test_resolve_absolute_path(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(url_resolve_https("https://h.example/a/b", "/search?q=1",
                                       out, sizeof out), URL_OK);
    assert_string_equal(out, "https://h.example/search?q=1");

    assert_int_equal(url_resolve_https("https://h.example", "/foo",
                                       out, sizeof out), URL_OK);
    assert_string_equal(out, "https://h.example/foo");
}

static void test_resolve_relative_path(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(url_resolve_https("https://h.example/a/b", "foo",
                                       out, sizeof out), URL_OK);
    assert_string_equal(out, "https://h.example/a/foo");

    assert_int_equal(url_resolve_https("https://h.example", "foo",
                                       out, sizeof out), URL_OK);
    assert_string_equal(out, "https://h.example/foo");
}

static void test_resolve_dot_segments(void **state) {
    (void)state;
    char out[256];
    /* RFC 3986 canonicalisation of the resolved path. */
    assert_int_equal(url_resolve_https("https://h.example/a/b/", "../c",
                                       out, sizeof out), URL_OK);
    assert_string_equal(out, "https://h.example/a/c");

    assert_int_equal(url_resolve_https("https://h.example/a/b", "./d",
                                       out, sizeof out), URL_OK);
    assert_string_equal(out, "https://h.example/a/d");

    assert_int_equal(url_resolve_https("https://h.example/a/b", "/x/../y",
                                       out, sizeof out), URL_OK);
    assert_string_equal(out, "https://h.example/y");
}

static void test_resolve_fail_closed_on_bad_base(void **state) {
    (void)state;
    char out[256];
    /* A base that is not a valid https URL must not be trusted. */
    assert_int_equal(url_resolve_https("http://h.example/", "/x",
                                       out, sizeof out), URL_ERR_NOT_HTTPS);
    assert_int_equal(url_resolve_https("ftp://h.example/", "x",
                                       out, sizeof out), URL_ERR_NOT_HTTPS);
    assert_int_equal(url_resolve_https("https://", "x",
                                       out, sizeof out), URL_ERR_NOT_HTTPS);
}

static void test_resolve_null_and_overflow(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(url_resolve_https(NULL, "/x", out, sizeof out), URL_ERR_NULL_ARG);
    assert_int_equal(url_resolve_https("https://h/", NULL, out, sizeof out), URL_ERR_NULL_ARG);
    assert_int_equal(url_resolve_https("https://h/", "/x", NULL, sizeof out), URL_ERR_NULL_ARG);
    assert_int_equal(url_resolve_https("https://h/", "/x", out, 0), URL_ERR_NULL_ARG);
    assert_int_equal(url_resolve_https("https://h.example/", "", out, sizeof out), URL_ERR_NOT_HTTPS);

    char tiny[12];
    assert_int_equal(url_resolve_https("https://h.example/", "/averylongpath/that/will/not/fit",
                                       tiny, sizeof tiny), URL_ERR_OVERFLOW);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_is_https),
        cmocka_unit_test(test_validate_https),
        cmocka_unit_test(test_has_scheme),
        cmocka_unit_test(test_authority_len),
        cmocka_unit_test(test_remove_dot_segments),
        cmocka_unit_test(test_remove_dot_segments_nulls),
        cmocka_unit_test(test_resolve_absolute),
        cmocka_unit_test(test_resolve_rejects_downgrade_and_schemes),
        cmocka_unit_test(test_resolve_scheme_relative),
        cmocka_unit_test(test_resolve_absolute_path),
        cmocka_unit_test(test_resolve_relative_path),
        cmocka_unit_test(test_resolve_dot_segments),
        cmocka_unit_test(test_resolve_fail_closed_on_bad_base),
        cmocka_unit_test(test_resolve_null_and_overflow),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
