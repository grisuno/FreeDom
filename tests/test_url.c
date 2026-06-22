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

/* --- url_omnibox --- */

static void test_omnibox_navigate_https(void **state) {
    (void)state;
    char out[URL_MAX_LEN + 1];
    url_omni_kind k = URL_OMNI_SEARCH;
    assert_int_equal(url_omnibox("https://example.com/path?q=1", &k, out, sizeof out), URL_OK);
    assert_int_equal(k, URL_OMNI_NAVIGATE);
    assert_string_equal(out, "https://example.com/path?q=1");
    /* surrounding whitespace is trimmed, not searched */
    assert_int_equal(url_omnibox("  https://example.com  ", &k, out, sizeof out), URL_OK);
    assert_int_equal(k, URL_OMNI_NAVIGATE);
    assert_string_equal(out, "https://example.com");
}

static void test_omnibox_bare_host_gets_https(void **state) {
    (void)state;
    char out[URL_MAX_LEN + 1];
    url_omni_kind k = URL_OMNI_SEARCH;
    assert_int_equal(url_omnibox("example.com", &k, out, sizeof out), URL_OK);
    assert_int_equal(k, URL_OMNI_NAVIGATE);
    assert_string_equal(out, "https://example.com");

    assert_int_equal(url_omnibox("news.ycombinator.com/news", &k, out, sizeof out), URL_OK);
    assert_int_equal(k, URL_OMNI_NAVIGATE);
    assert_string_equal(out, "https://news.ycombinator.com/news");

    assert_int_equal(url_omnibox("localhost:8443/admin", &k, out, sizeof out), URL_OK);
    assert_int_equal(k, URL_OMNI_NAVIGATE);
    assert_string_equal(out, "https://localhost:8443/admin");
}

static void test_omnibox_http_upgraded_to_https(void **state) {
    (void)state;
    char out[URL_MAX_LEN + 1];
    url_omni_kind k = URL_OMNI_SEARCH;
    /* Secure by Default: an http:// URL is navigated as https, never downgraded. */
    assert_int_equal(url_omnibox("http://example.com/x", &k, out, sizeof out), URL_OK);
    assert_int_equal(k, URL_OMNI_NAVIGATE);
    assert_string_equal(out, "https://example.com/x");
}

static void test_omnibox_search_for_queries(void **state) {
    (void)state;
    char out[URL_MAX_LEN + 1];
    url_omni_kind k = URL_OMNI_NAVIGATE;
    /* whitespace => query */
    assert_int_equal(url_omnibox("best linux distro", &k, out, sizeof out), URL_OK);
    assert_int_equal(k, URL_OMNI_SEARCH);
    assert_string_equal(out, URL_SEARCH_ENDPOINT "best+linux+distro");

    /* single word, no dot => query (not a host) */
    assert_int_equal(url_omnibox("freedom", &k, out, sizeof out), URL_OK);
    assert_int_equal(k, URL_OMNI_SEARCH);
    assert_string_equal(out, URL_SEARCH_ENDPOINT "freedom");

    /* reserved characters are percent-encoded */
    assert_int_equal(url_omnibox("a&b=c+d", &k, out, sizeof out), URL_OK);
    assert_int_equal(k, URL_OMNI_SEARCH);
    assert_string_equal(out, URL_SEARCH_ENDPOINT "a%26b%3Dc%2Bd");
}

static void test_omnibox_foreign_scheme_is_searched_not_executed(void **state) {
    (void)state;
    char out[URL_MAX_LEN + 1];
    url_omni_kind k = URL_OMNI_NAVIGATE;
    /* fail-closed: a dangerous scheme is treated as text, never run */
    assert_int_equal(url_omnibox("javascript:alert(1)", &k, out, sizeof out), URL_OK);
    assert_int_equal(k, URL_OMNI_SEARCH);
    assert_int_equal(url_omnibox("file:///etc/passwd", &k, out, sizeof out), URL_OK);
    assert_int_equal(k, URL_OMNI_SEARCH);
    assert_int_equal(url_omnibox("ftp://h.example/x", &k, out, sizeof out), URL_OK);
    assert_int_equal(k, URL_OMNI_SEARCH);
}

static void test_omnibox_nulls_and_empty(void **state) {
    (void)state;
    char out[URL_MAX_LEN + 1];
    url_omni_kind k;
    assert_int_equal(url_omnibox(NULL, &k, out, sizeof out), URL_ERR_NULL_ARG);
    assert_int_equal(url_omnibox("x", NULL, out, sizeof out), URL_ERR_NULL_ARG);
    assert_int_equal(url_omnibox("x", &k, NULL, sizeof out), URL_ERR_NULL_ARG);
    assert_int_equal(url_omnibox("x", &k, out, 0), URL_ERR_NULL_ARG);
    /* empty / whitespace-only input is a (degenerate) empty search, never a crash */
    assert_int_equal(url_omnibox("   ", &k, out, sizeof out), URL_OK);
    assert_int_equal(k, URL_OMNI_SEARCH);
    assert_string_equal(out, URL_SEARCH_ENDPOINT);
}

/* --- url_is_file / url_file_path / url_resolve_file --- */

static void test_is_file_and_path(void **state) {
    (void)state;
    assert_int_equal(url_is_file("file:///home/u/a.html"), 1);
    assert_int_equal(url_is_file("FILE:///x"), 1);
    assert_int_equal(url_is_file("file://host/x"), 0); /* needs absolute path (///), not a host */
    assert_int_equal(url_is_file("file:relative"), 0);
    assert_int_equal(url_is_file("https://example.com"), 0);
    assert_int_equal(url_is_file(NULL), 0);
    assert_string_equal(url_file_path("file:///home/u/a.html"), "/home/u/a.html");
    assert_null(url_file_path("https://example.com"));
}

static void test_resolve_file_relative(void **state) {
    (void)state;
    char out[URL_MAX_LEN + 1];
    /* sibling and child resources resolve and stay confined */
    assert_int_equal(url_resolve_file("file:///a/docs/index.html", "logo.png",
                                      out, sizeof out), URL_OK);
    assert_string_equal(out, "file:///a/docs/logo.png");
    assert_int_equal(url_resolve_file("file:///a/docs/index.html", "img/x.png",
                                      out, sizeof out), URL_OK);
    assert_string_equal(out, "file:///a/docs/img/x.png");
    /* a "." / ".." that stays inside is collapsed and allowed */
    assert_int_equal(url_resolve_file("file:///a/docs/index.html", "sub/../logo.png",
                                      out, sizeof out), URL_OK);
    assert_string_equal(out, "file:///a/docs/logo.png");
    /* an absolute path inside the subtree is allowed */
    assert_int_equal(url_resolve_file("file:///a/docs/index.html", "/a/docs/sub/p.png",
                                      out, sizeof out), URL_OK);
    assert_string_equal(out, "file:///a/docs/sub/p.png");
}

static void test_resolve_file_confinement_fail_closed(void **state) {
    (void)state;
    char out[URL_MAX_LEN + 1];
    /* "../" escaping the document directory is rejected */
    assert_int_equal(url_resolve_file("file:///a/docs/index.html", "../secret.png",
                                      out, sizeof out), URL_ERR_NOT_LOCAL);
    assert_int_equal(url_resolve_file("file:///a/docs/index.html", "../../etc/passwd",
                                      out, sizeof out), URL_ERR_NOT_LOCAL);
    /* an absolute path outside the subtree is rejected */
    assert_int_equal(url_resolve_file("file:///a/docs/index.html", "/etc/passwd",
                                      out, sizeof out), URL_ERR_NOT_LOCAL);
    /* a sibling directory sharing a name prefix must not pass the prefix check */
    assert_int_equal(url_resolve_file("file:///a/docs/index.html", "/a/docsEVIL/x.png",
                                      out, sizeof out), URL_ERR_NOT_LOCAL);
    /* a remote / foreign-scheme src on a local page never loads (no phone-home) */
    assert_int_equal(url_resolve_file("file:///a/docs/index.html", "https://tracker/x.png",
                                      out, sizeof out), URL_ERR_NOT_LOCAL);
    assert_int_equal(url_resolve_file("file:///a/docs/index.html", "//evil/x.png",
                                      out, sizeof out), URL_ERR_NOT_LOCAL);
    /* an empty ref and a non-file base both fail closed */
    assert_int_equal(url_resolve_file("file:///a/docs/index.html", "",
                                      out, sizeof out), URL_ERR_NOT_LOCAL);
    assert_int_equal(url_resolve_file("https://example.com/p", "logo.png",
                                      out, sizeof out), URL_ERR_NOT_LOCAL);
}

static void test_resolve_file_nulls(void **state) {
    (void)state;
    char out[URL_MAX_LEN + 1];
    assert_int_equal(url_resolve_file(NULL, "x", out, sizeof out), URL_ERR_NULL_ARG);
    assert_int_equal(url_resolve_file("file:///a/b", NULL, out, sizeof out), URL_ERR_NULL_ARG);
    assert_int_equal(url_resolve_file("file:///a/b", "x", NULL, sizeof out), URL_ERR_NULL_ARG);
    assert_int_equal(url_resolve_file("file:///a/b", "x", out, 0), URL_ERR_NULL_ARG);
}

/* --- url_split (WHATWG-location decomposition) --- */

/* Asserts a (ptr,len) span equals the expected C string exactly. */
static void assert_span(const char *p, size_t len, const char *expect) {
    assert_int_equal(len, strlen(expect));
    assert_memory_equal(p, expect, len);
}

static void test_split_full_url(void **state) {
    (void)state;
    url_parts u;
    static const char URL[] = "https://example.com:8443/a/b?x=1&y=2#frag";
    assert_int_equal(url_split(URL, &u), URL_OK);
    assert_span(u.href, u.href_len, URL);
    assert_span(u.protocol, u.protocol_len, "https:");
    assert_span(u.origin, u.origin_len, "https://example.com:8443");
    assert_span(u.host, u.host_len, "example.com:8443");
    assert_span(u.hostname, u.hostname_len, "example.com");
    assert_span(u.port, u.port_len, "8443");
    assert_span(u.pathname, u.pathname_len, "/a/b");
    assert_span(u.search, u.search_len, "?x=1&y=2");
    assert_span(u.hash, u.hash_len, "#frag");
    /* every span must alias the input */
    assert_true(u.href == URL);
    assert_true(u.hostname >= URL && u.hostname < URL + sizeof URL);
}

static void test_split_no_port_no_path(void **state) {
    (void)state;
    url_parts u;
    assert_int_equal(url_split("https://example.com", &u), URL_OK);
    assert_span(u.host, u.host_len, "example.com");
    assert_span(u.hostname, u.hostname_len, "example.com");
    assert_int_equal(u.port_len, 0);    /* no explicit port */
    assert_int_equal(u.pathname_len, 0); /* empty path; consumer presents "/" */
    assert_int_equal(u.search_len, 0);
    assert_int_equal(u.hash_len, 0);
    assert_span(u.origin, u.origin_len, "https://example.com");
}

static void test_split_query_without_fragment(void **state) {
    (void)state;
    url_parts u;
    assert_int_equal(url_split("https://h.test/p/q?a=b", &u), URL_OK);
    assert_span(u.pathname, u.pathname_len, "/p/q");
    assert_span(u.search, u.search_len, "?a=b");
    assert_int_equal(u.hash_len, 0);
}

static void test_split_fragment_without_query(void **state) {
    (void)state;
    url_parts u;
    assert_int_equal(url_split("https://h.test/p#sec", &u), URL_OK);
    assert_span(u.pathname, u.pathname_len, "/p");
    assert_int_equal(u.search_len, 0);
    assert_span(u.hash, u.hash_len, "#sec");
}

static void test_split_ipv6_literal_with_port(void **state) {
    (void)state;
    url_parts u;
    assert_int_equal(url_split("https://[2001:db8::1]:443/p", &u), URL_OK);
    assert_span(u.host, u.host_len, "[2001:db8::1]:443");
    assert_span(u.hostname, u.hostname_len, "[2001:db8::1]"); /* brackets kept */
    assert_span(u.port, u.port_len, "443");
    assert_span(u.pathname, u.pathname_len, "/p");
}

static void test_split_fail_closed_non_https(void **state) {
    (void)state;
    url_parts u;
    assert_int_equal(url_split(NULL, &u), URL_ERR_NULL_ARG);
    assert_int_equal(url_split("https://x", NULL), URL_ERR_NULL_ARG);
    assert_int_equal(url_split("http://example.com", &u), URL_ERR_NOT_HTTPS);
    assert_int_equal(url_split("file:///etc/passwd", &u), URL_ERR_NOT_HTTPS);
    assert_int_equal(url_split("javascript:alert(1)", &u), URL_ERR_NOT_HTTPS);
    assert_int_equal(url_split("https://", &u), URL_ERR_NOT_HTTPS); /* empty host */
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
        cmocka_unit_test(test_omnibox_navigate_https),
        cmocka_unit_test(test_omnibox_bare_host_gets_https),
        cmocka_unit_test(test_omnibox_http_upgraded_to_https),
        cmocka_unit_test(test_omnibox_search_for_queries),
        cmocka_unit_test(test_omnibox_foreign_scheme_is_searched_not_executed),
        cmocka_unit_test(test_omnibox_nulls_and_empty),
        cmocka_unit_test(test_is_file_and_path),
        cmocka_unit_test(test_resolve_file_relative),
        cmocka_unit_test(test_resolve_file_confinement_fail_closed),
        cmocka_unit_test(test_resolve_file_nulls),
        cmocka_unit_test(test_split_full_url),
        cmocka_unit_test(test_split_no_port_no_path),
        cmocka_unit_test(test_split_query_without_fragment),
        cmocka_unit_test(test_split_fragment_without_query),
        cmocka_unit_test(test_split_ipv6_literal_with_port),
        cmocka_unit_test(test_split_fail_closed_non_https),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
