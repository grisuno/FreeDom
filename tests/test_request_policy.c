/*
 * TDD suite for request_policy (Hito 5 - third-party blocking).
 *
 * Pure policy logic: no I/O. Build: make test   ;   ASan: make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <string.h>
#include <stdio.h>
#include <cmocka.h>

#include "request_policy.h"

/* --- rp_host_of --- */

static void test_host_of_basic(void **state) {
    (void)state;
    char h[256];
    assert_int_equal(rp_host_of("https://example.com/path", h, sizeof h), 0);
    assert_string_equal(h, "example.com");
    assert_int_equal(rp_host_of("https://Example.COM:443/x?q=1", h, sizeof h), 0);
    assert_string_equal(h, "example.com"); /* lowercased, port/path stripped */
    assert_int_equal(rp_host_of("http://host.test#frag", h, sizeof h), 0);
    assert_string_equal(h, "host.test");
}

static void test_host_of_invalid(void **state) {
    (void)state;
    char h[256];
    assert_int_equal(rp_host_of("example.com", h, sizeof h), -1); /* no scheme */
    assert_int_equal(rp_host_of("https:///path", h, sizeof h), -1); /* empty host */
    assert_int_equal(rp_host_of(NULL, h, sizeof h), -1);
}

static void test_host_of_overflow(void **state) {
    (void)state;
    char small[4];
    assert_int_equal(rp_host_of("https://example.com/", small, sizeof small), -1);
}

/* --- rp_site_of --- */

static void test_site_of(void **state) {
    (void)state;
    char s[256];
    assert_int_equal(rp_site_of("example.com", s, sizeof s), 0);
    assert_string_equal(s, "example.com");
    assert_int_equal(rp_site_of("www.example.com", s, sizeof s), 0);
    assert_string_equal(s, "example.com");
    assert_int_equal(rp_site_of("a.b.example.com", s, sizeof s), 0);
    assert_string_equal(s, "example.com");
    assert_int_equal(rp_site_of("localhost", s, sizeof s), 0);
    assert_string_equal(s, "localhost");
}

static void test_site_of_multi_suffix(void **state) {
    (void)state;
    char s[256];
    assert_int_equal(rp_site_of("example.co.uk", s, sizeof s), 0);
    assert_string_equal(s, "example.co.uk");
    assert_int_equal(rp_site_of("www.example.co.uk", s, sizeof s), 0);
    assert_string_equal(s, "example.co.uk");
    assert_int_equal(rp_site_of("shop.example.com.br", s, sizeof s), 0);
    assert_string_equal(s, "example.com.br");
}

/* Cases the old heuristic got wrong but the full PSL gets right. */
static void test_site_of_psl(void **state) {
    (void)state;
    char s[256];
    /* PRIVATE section: each github.io subdomain is its own registrable site. */
    assert_int_equal(rp_site_of("blog.github.io", s, sizeof s), 0);
    assert_string_equal(s, "blog.github.io");
    assert_int_equal(rp_site_of("a.blog.github.io", s, sizeof s), 0);
    assert_string_equal(s, "blog.github.io");
    /* Wildcard rule "*.ck": bar.ck is the public suffix. */
    assert_int_equal(rp_site_of("foo.bar.ck", s, sizeof s), 0);
    assert_string_equal(s, "foo.bar.ck");
    /* Exception rule "!www.ck": www.ck IS registrable (suffix is just "ck"). */
    assert_int_equal(rp_site_of("foo.www.ck", s, sizeof s), 0);
    assert_string_equal(s, "www.ck");
    /* New-style gTLD with no second level: site is two labels. */
    assert_int_equal(rp_site_of("shop.example.dev", s, sizeof s), 0);
    assert_string_equal(s, "example.dev");
}

/* --- rp_same_site --- */

static void test_same_site(void **state) {
    (void)state;
    assert_int_equal(rp_same_site("https://example.com/", "https://example.com/a"), 1);
    assert_int_equal(rp_same_site("https://www.example.com/", "https://cdn.example.com/x"), 1);
    assert_int_equal(rp_same_site("https://example.com/", "https://tracker.net/x"), 0);
    assert_int_equal(rp_same_site("https://a.example.co.uk/", "https://b.example.co.uk/"), 1);
    assert_int_equal(rp_same_site("https://example.co.uk/", "https://evil.co.uk/"), 0);
    /* Two different users on a PRIVATE suffix are different sites. */
    assert_int_equal(rp_same_site("https://alice.github.io/", "https://bob.github.io/"), 0);
    assert_int_equal(rp_same_site("https://x.alice.github.io/", "https://alice.github.io/"), 1);
}

/* --- rp_evaluate --- */

static void test_evaluate_allow_same_site(void **state) {
    (void)state;
    assert_int_equal(rp_evaluate("https://example.com/", "https://example.com/a.js"), RP_ALLOW);
    assert_int_equal(rp_evaluate("https://www.example.com/", "https://cdn.example.com/x.css"),
                     RP_ALLOW);
}

static void test_evaluate_block_third_party(void **state) {
    (void)state;
    assert_int_equal(rp_evaluate("https://example.com/", "https://tracker.net/p.gif"),
                     RP_BLOCK_THIRD_PARTY);
    assert_int_equal(rp_evaluate("https://example.co.uk/", "https://ads.evil.co.uk/x"),
                     RP_BLOCK_THIRD_PARTY);
}

static void test_evaluate_block_scheme(void **state) {
    (void)state;
    assert_int_equal(rp_evaluate("https://example.com/", "http://example.com/x"),
                     RP_BLOCK_SCHEME);
    assert_int_equal(rp_evaluate("https://example.com/", "ftp://example.com/x"),
                     RP_BLOCK_SCHEME);
}

static void test_evaluate_block_invalid(void **state) {
    (void)state;
    assert_int_equal(rp_evaluate("https://example.com/", "https:///x"), RP_BLOCK_INVALID);
    assert_int_equal(rp_evaluate("https://example.com/", "javascript:alert(1)"),
                     RP_BLOCK_INVALID);
    assert_int_equal(rp_evaluate("http://example.com/", "https://example.com/x"),
                     RP_BLOCK_INVALID); /* top not https: fail closed */
    assert_int_equal(rp_evaluate(NULL, "https://example.com/x"), RP_BLOCK_INVALID);
    assert_int_equal(rp_evaluate("https://example.com/", NULL), RP_BLOCK_INVALID);
}

/* --- rp_sanitize_request_headers --- */

static void test_hdr_keeps_application_headers(void **state) {
    (void)state;
    char out[512];
    int n = rp_sanitize_request_headers(
        "Accept: text/vnd.reddit.partial+html\nContent-Type: application/json\n"
        "X-Requested-With: XMLHttpRequest\nAuthorization: Bearer abc\n", out, sizeof out);
    assert_int_equal(n, 4);
    assert_string_equal(out,
        "Accept: text/vnd.reddit.partial+html\nContent-Type: application/json\n"
        "X-Requested-With: XMLHttpRequest\nAuthorization: Bearer abc\n");
    assert_true(rp_headers_have(out, "accept"));
    assert_true(rp_headers_have(out, "CONTENT-TYPE"));
    assert_false(rp_headers_have(out, "cookie"));
}

static void test_hdr_drops_forbidden_and_identity(void **state) {
    (void)state;
    char out[512];
    int n = rp_sanitize_request_headers(
        "Host: evil.test\nCookie: a=b\nReferer: https://x/\nUser-Agent: curl\n"
        "Accept-Language: es\nAccept-Encoding: br\nConnection: close\nContent-Length: 0\n"
        "Transfer-Encoding: chunked\nTE: trailers\nUpgrade: websocket\nExpect: 100-continue\n"
        "Date: x\nDNT: 0\nVia: 1.1 x\nOrigin: https://x\nSec-Fetch-Site: none\n"
        "Proxy-Authorization: x\nX-HTTP-Method-Override: DELETE\nAccess-Control-Request-Method: PUT\n"
        "X-Ok: 1\n", out, sizeof out);
    assert_int_equal(n, 1);
    assert_string_equal(out, "X-Ok: 1\n");
}

static void test_hdr_rejects_malformed(void **state) {
    (void)state;
    char out[512];
    assert_int_equal(rp_sanitize_request_headers("Bad Name: v\nNoColon\n: empty\nX-A: ok\n", out, sizeof out), 1);
    assert_string_equal(out, "X-A: ok\n");
    assert_int_equal(rp_sanitize_request_headers("X-A: a\rInjected: b\nX-B: c\x01d\nX-C: fine\n", out, sizeof out), 1);
    assert_string_equal(out, "X-C: fine\n");
    assert_int_equal(rp_sanitize_request_headers("", out, sizeof out), 0);
    assert_string_equal(out, "");
    assert_int_equal(rp_sanitize_request_headers("X-A:   padded value  \n", out, sizeof out), 1);
    assert_string_equal(out, "X-A: padded value\n");
}

static void test_hdr_first_duplicate_wins(void **state) {
    (void)state;
    char out[512];
    assert_int_equal(rp_sanitize_request_headers("X-A: 1\nx-a: 2\nX-B: 3\n", out, sizeof out), 2);
    assert_string_equal(out, "X-A: 1\nX-B: 3\n");
}

static void test_hdr_caps_and_args(void **state) {
    (void)state;
    char out[RP_HDR_MAX_BYTES + 64];
    char big[8192];
    size_t n = 0;
    for (int i = 0; i < 100; ++i) n += (size_t)snprintf(big + n, sizeof big - n, "X-H%d: v\n", i);
    assert_int_equal(rp_sanitize_request_headers(big, out, sizeof out), RP_HDR_MAX_COUNT);
    char longv[RP_HDR_VALUE_MAX + 64];
    memset(longv, 'a', sizeof longv);
    memcpy(longv, "X-L: ", 5);
    longv[sizeof longv - 2] = '\n';
    longv[sizeof longv - 1] = '\0';
    assert_int_equal(rp_sanitize_request_headers(longv, out, sizeof out), 0);
    assert_int_equal(rp_sanitize_request_headers(NULL, out, sizeof out), -1);
    assert_int_equal(rp_sanitize_request_headers("X-A: 1\n", NULL, 8), -1);
    assert_int_equal(rp_sanitize_request_headers("X-A: 1\n", out, 0), -1);
    char tiny[6];
    assert_int_equal(rp_sanitize_request_headers("X-Long-Name: value\nX-B: 1\n", tiny, sizeof tiny), 0);
    assert_string_equal(tiny, "");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_hdr_keeps_application_headers),
        cmocka_unit_test(test_hdr_drops_forbidden_and_identity),
        cmocka_unit_test(test_hdr_rejects_malformed),
        cmocka_unit_test(test_hdr_first_duplicate_wins),
        cmocka_unit_test(test_hdr_caps_and_args),
        cmocka_unit_test(test_host_of_basic),
        cmocka_unit_test(test_host_of_invalid),
        cmocka_unit_test(test_host_of_overflow),
        cmocka_unit_test(test_site_of),
        cmocka_unit_test(test_site_of_multi_suffix),
        cmocka_unit_test(test_site_of_psl),
        cmocka_unit_test(test_same_site),
        cmocka_unit_test(test_evaluate_allow_same_site),
        cmocka_unit_test(test_evaluate_block_third_party),
        cmocka_unit_test(test_evaluate_block_scheme),
        cmocka_unit_test(test_evaluate_block_invalid),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
