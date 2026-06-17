/*
 * test_link_nav — CMocka suite for the pure link navigation policy.
 *
 * Covers the full decision matrix: fragments/empty hrefs, https-base resolution
 * (relative/absolute/scheme), the secure rejections (downgrade, foreign schemes),
 * local-file-base resolution (relative/absolute/parent), the no-base case, href
 * cleaning (tab/newline/whitespace), and the fail-closed edges.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "link_nav.h"

static ln_result R; /* reused per assertion for brevity */

/* --- argument handling --- */

static void test_null_out(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("https://h/", "/x", NULL), LN_ERR_NULL_ARG);
}

static void test_null_href_blocked(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("https://h.example/", NULL, &R), LN_OK);
    assert_int_equal(R.action, LN_BLOCKED);
}

/* --- fragments / empty --- */

static void test_fragment_is_same_document(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("https://h.example/a", "#section", &R), LN_OK);
    assert_int_equal(R.action, LN_SAME_DOCUMENT);
    assert_string_equal(R.target, "");

    assert_int_equal(ln_resolve("https://h.example/a", "", &R), LN_OK);
    assert_int_equal(R.action, LN_SAME_DOCUMENT);
}

/* --- https base --- */

static void test_https_absolute(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("https://a.example/", "https://b.example/p", &R), LN_OK);
    assert_int_equal(R.action, LN_NAVIGATE);
    assert_int_equal(R.kind, LN_TARGET_HTTPS);
    assert_string_equal(R.target, "https://b.example/p");
}

static void test_https_relative(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("https://h.example/a/b", "c/d", &R), LN_OK);
    assert_int_equal(R.action, LN_NAVIGATE);
    assert_int_equal(R.kind, LN_TARGET_HTTPS);
    assert_string_equal(R.target, "https://h.example/a/c/d");
}

static void test_https_absolute_path_and_parent(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("https://h.example/a/b", "/x", &R), LN_OK);
    assert_int_equal(R.action, LN_NAVIGATE);
    assert_string_equal(R.target, "https://h.example/x");

    assert_int_equal(ln_resolve("https://h.example/a/b/", "../up", &R), LN_OK);
    assert_int_equal(R.action, LN_NAVIGATE);
    assert_string_equal(R.target, "https://h.example/a/up");
}

static void test_https_blocks_downgrade_and_schemes(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("https://h.example/", "http://h.example/", &R), LN_OK);
    assert_int_equal(R.action, LN_BLOCKED);

    assert_int_equal(ln_resolve("https://h.example/", "javascript:alert(1)", &R), LN_OK);
    assert_int_equal(R.action, LN_BLOCKED);

    assert_int_equal(ln_resolve("https://h.example/", "mailto:a@b.example", &R), LN_OK);
    assert_int_equal(R.action, LN_BLOCKED);

    assert_int_equal(ln_resolve("https://h.example/", "data:text/html,x", &R), LN_OK);
    assert_int_equal(R.action, LN_BLOCKED);
}

static void test_https_scheme_relative(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("https://a.example/x", "//b.example/y", &R), LN_OK);
    assert_int_equal(R.action, LN_NAVIGATE);
    assert_string_equal(R.target, "https://b.example/y");
}

/* --- href cleaning --- */

static void test_href_cleaning(void **state) {
    (void)state;
    /* Surrounding whitespace and embedded tab/newline/CR are stripped. */
    assert_int_equal(ln_resolve("https://h.example/",
                                "  https://b.example/\tpa\nth\r  ", &R), LN_OK);
    assert_int_equal(R.action, LN_NAVIGATE);
    assert_string_equal(R.target, "https://b.example/path");
}

/* --- local file base --- */

static void test_file_relative(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("/home/u/docs/index.html", "sub/page.html", &R), LN_OK);
    assert_int_equal(R.action, LN_NAVIGATE);
    assert_int_equal(R.kind, LN_TARGET_FILE);
    assert_string_equal(R.target, "/home/u/docs/sub/page.html");
}

static void test_file_parent(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("examples/rich.html", "../README.md", &R), LN_OK);
    assert_int_equal(R.action, LN_NAVIGATE);
    assert_int_equal(R.kind, LN_TARGET_FILE);
    assert_string_equal(R.target, "README.md");
}

static void test_file_absolute_path(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("/home/u/a.html", "/etc/hosts.html", &R), LN_OK);
    assert_int_equal(R.action, LN_NAVIGATE);
    assert_int_equal(R.kind, LN_TARGET_FILE);
    assert_string_equal(R.target, "/etc/hosts.html");
}

static void test_file_drops_fragment(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("/home/u/a.html", "b.html#sec", &R), LN_OK);
    assert_int_equal(R.action, LN_NAVIGATE);
    assert_int_equal(R.kind, LN_TARGET_FILE);
    assert_string_equal(R.target, "/home/u/b.html");
}

static void test_file_base_to_https(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("/home/u/a.html", "https://h.example/x", &R), LN_OK);
    assert_int_equal(R.action, LN_NAVIGATE);
    assert_int_equal(R.kind, LN_TARGET_HTTPS);
    assert_string_equal(R.target, "https://h.example/x");
}

static void test_file_base_blocks_schemes_and_scheme_relative(void **state) {
    (void)state;
    assert_int_equal(ln_resolve("/home/u/a.html", "http://h.example/", &R), LN_OK);
    assert_int_equal(R.action, LN_BLOCKED);

    assert_int_equal(ln_resolve("/home/u/a.html", "javascript:alert(1)", &R), LN_OK);
    assert_int_equal(R.action, LN_BLOCKED);

    assert_int_equal(ln_resolve("/home/u/a.html", "//h.example/x", &R), LN_OK);
    assert_int_equal(R.action, LN_BLOCKED);
}

/* --- no base --- */

static void test_no_base(void **state) {
    (void)state;
    assert_int_equal(ln_resolve(NULL, "https://h.example/x", &R), LN_OK);
    assert_int_equal(R.action, LN_NAVIGATE);
    assert_int_equal(R.kind, LN_TARGET_HTTPS);
    assert_string_equal(R.target, "https://h.example/x");

    assert_int_equal(ln_resolve(NULL, "relative/path", &R), LN_OK);
    assert_int_equal(R.action, LN_BLOCKED);

    assert_int_equal(ln_resolve(NULL, "http://h.example/", &R), LN_OK);
    assert_int_equal(R.action, LN_BLOCKED);
}

/* --- overflow fails closed --- */

static void test_overflow_blocked(void **state) {
    (void)state;
    char big[LN_MAX_TARGET + 64];
    memcpy(big, "https://h.example/", 18);
    memset(big + 18, 'a', sizeof big - 19);
    big[sizeof big - 1] = '\0';
    assert_int_equal(ln_resolve("https://h.example/", big, &R), LN_OK);
    assert_int_equal(R.action, LN_BLOCKED);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_null_out),
        cmocka_unit_test(test_null_href_blocked),
        cmocka_unit_test(test_fragment_is_same_document),
        cmocka_unit_test(test_https_absolute),
        cmocka_unit_test(test_https_relative),
        cmocka_unit_test(test_https_absolute_path_and_parent),
        cmocka_unit_test(test_https_blocks_downgrade_and_schemes),
        cmocka_unit_test(test_https_scheme_relative),
        cmocka_unit_test(test_href_cleaning),
        cmocka_unit_test(test_file_relative),
        cmocka_unit_test(test_file_parent),
        cmocka_unit_test(test_file_absolute_path),
        cmocka_unit_test(test_file_drops_fragment),
        cmocka_unit_test(test_file_base_to_https),
        cmocka_unit_test(test_file_base_blocks_schemes_and_scheme_relative),
        cmocka_unit_test(test_no_base),
        cmocka_unit_test(test_overflow_blocked),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
