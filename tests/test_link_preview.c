/* Suite for link_preview (spec/link_preview.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include <string.h>

#include "link_preview.h"

static void assert_clean(const lp_preview *p) {
    size_t n = strlen(p->text);
    assert_true(n < LP_TEXT_MAX);
    for (size_t i = 0; i < n; ++i) {
        unsigned char c = (unsigned char)p->text[i];
        assert_true(c >= 0x20 && c < 0x7F);
    }
    assert_true(p->host_off + p->host_len <= n);
}

static void host_is(const lp_preview *p, const char *host) {
    assert_int_equal(p->host_len, strlen(host));
    assert_memory_equal(p->text + p->host_off, host, p->host_len);
}

static void test_null_out(void **state) {
    (void)state;
    assert_int_equal(lp_describe("https://a.org/", "x", NULL), LP_EINVAL);
}

static void test_relative_resolves_to_absolute(void **state) {
    (void)state;
    lp_preview p;
    assert_int_equal(lp_describe("https://news.ycombinator.com/news", "from?site=hackaday.com", &p),
                     LP_OK);
    assert_int_equal(p.kind, LP_NAVIGATE);
    assert_string_equal(p.text, "https://news.ycombinator.com/from?site=hackaday.com");
    host_is(&p, "news.ycombinator.com");
    assert_clean(&p);
}

static void test_userinfo_and_port_not_host(void **state) {
    (void)state;
    lp_preview p;
    assert_int_equal(lp_describe("https://a.org/", "https://paypal.com@evil.example:8443/x", &p),
                     LP_OK);
    assert_int_equal(p.kind, LP_NAVIGATE);
    host_is(&p, "evil.example");
    assert_clean(&p);
}

static void test_javascript_blocked(void **state) {
    (void)state;
    lp_preview p;
    assert_int_equal(lp_describe("https://a.org/", "javascript:alert(1)", &p), LP_OK);
    assert_int_equal(p.kind, LP_BLOCKED);
    assert_memory_equal(p.text, "Blocked (", 9);
    assert_non_null(strstr(p.text, "javascript:alert(1)"));
    assert_int_equal(p.host_len, 0);
    assert_clean(&p);
}

static void test_downgrade_blocked(void **state) {
    (void)state;
    lp_preview p;
    assert_int_equal(lp_describe("https://a.org/", "http://a.org/x", &p), LP_OK);
    assert_int_equal(p.kind, LP_BLOCKED);
    assert_clean(&p);
}

static void test_bidi_and_controls_escaped(void **state) {
    (void)state;
    lp_preview p;
    assert_int_equal(lp_describe("https://a.org/", "https://ex\xe2\x80\xae" "ample.com/\x01\n", &p),
                     LP_OK);
    assert_non_null(strstr(p.text, "%E2%80%AE"));
    assert_clean(&p);
    assert_int_equal(lp_describe("https://a.org/", "javascript:\x1b[2J\xd0\xb0", &p), LP_OK);
    assert_non_null(strstr(p.text, "%1B"));
    assert_non_null(strstr(p.text, "%D0%B0"));
    assert_clean(&p);
}

static void test_fragment_same_document(void **state) {
    (void)state;
    lp_preview p;
    assert_int_equal(lp_describe("https://a.org/p#old", "#top", &p), LP_OK);
    assert_int_equal(p.kind, LP_SAME_DOCUMENT);
    assert_string_equal(p.text, "https://a.org/p#top");
    host_is(&p, "a.org");
    assert_int_equal(lp_describe(NULL, "#top", &p), LP_OK);
    assert_int_equal(p.kind, LP_SAME_DOCUMENT);
    assert_string_equal(p.text, "#top");
    assert_int_equal(p.host_len, 0);
}

static void test_local_file(void **state) {
    (void)state;
    lp_preview p;
    assert_int_equal(lp_describe("/home/u/site/index.html", "b.html", &p), LP_OK);
    assert_int_equal(p.kind, LP_NAVIGATE);
    assert_string_equal(p.text, "file:///home/u/site/b.html");
    assert_int_equal(p.host_len, 0);
}

static void test_long_path_keeps_host(void **state) {
    (void)state;
    size_t n = 7000;   /* under URL_MAX_LEN, far over LP_TEXT_MAX */
    char *href = malloc(n + 32);
    assert_non_null(href);
    strcpy(href, "https://host.example/");
    size_t at = strlen(href);
    memset(href + at, 'a', n);
    strcpy(href + at + n, "TAIL");
    lp_preview p;
    assert_int_equal(lp_describe("https://a.org/", href, &p), LP_OK);
    assert_clean(&p);
    assert_memory_equal(p.text, "https://host.example/", 21);
    assert_non_null(strstr(p.text, "..."));
    host_is(&p, "host.example");
    free(href);
}

static void test_long_blocked_bounded(void **state) {
    (void)state;
    size_t n = 9000;
    char *href = malloc(n + 16);
    assert_non_null(href);
    strcpy(href, "javascript:");
    memset(href + 11, '\xff', n);
    href[11 + n] = '\0';
    lp_preview p;
    assert_int_equal(lp_describe("https://a.org/", href, &p), LP_OK);
    assert_int_equal(p.kind, LP_BLOCKED);
    assert_clean(&p);
    free(href);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_null_out),
        cmocka_unit_test(test_relative_resolves_to_absolute),
        cmocka_unit_test(test_userinfo_and_port_not_host),
        cmocka_unit_test(test_javascript_blocked),
        cmocka_unit_test(test_downgrade_blocked),
        cmocka_unit_test(test_bidi_and_controls_escaped),
        cmocka_unit_test(test_fragment_same_document),
        cmocka_unit_test(test_local_file),
        cmocka_unit_test(test_long_path_keeps_host),
        cmocka_unit_test(test_long_blocked_bounded),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
