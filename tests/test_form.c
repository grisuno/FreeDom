/*
 * test_form — CMocka suite for the pure form-submission builder.
 *
 * Covers the application/x-www-form-urlencoded encoder (space -> '+', reserved
 * bytes -> %XX, empty/nameless fields, overflow), GET plan construction (relative
 * action on an https base, absolute https action, empty action = base, query
 * replacement), POST plan construction (body + content type + query kept), and the
 * fail-closed blocks (http downgrade, foreign scheme, local base, too many fields,
 * NULL name, NULL args).
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "form.h"

/* --- fm_encode --- */

static void test_encode_basic(void **state) {
    (void)state;
    fm_field f[] = { { "q", "hello" }, { "lang", "en" } };
    char out[256];
    size_t len = 0;
    assert_int_equal(fm_encode(f, 2, out, sizeof out, &len), FM_OK);
    assert_string_equal(out, "q=hello&lang=en");
    assert_int_equal(len, strlen("q=hello&lang=en"));
}

static void test_encode_space_and_reserved(void **state) {
    (void)state;
    fm_field f[] = { { "q", "a b&c=d/e?f+g" } };
    char out[256];
    assert_int_equal(fm_encode(f, 1, out, sizeof out, NULL), FM_OK);
    /* space->+, & = / ? + are reserved -> %XX; letters kept. */
    assert_string_equal(out, "q=a+b%26c%3Dd%2Fe%3Ff%2Bg");
}

static void test_encode_unreserved_kept(void **state) {
    (void)state;
    fm_field f[] = { { "k", "AZaz09-_.*" } };
    char out[64];
    assert_int_equal(fm_encode(f, 1, out, sizeof out, NULL), FM_OK);
    assert_string_equal(out, "k=AZaz09-_.*");
}

static void test_encode_empty_and_nameless(void **state) {
    (void)state;
    fm_field f[] = { { "a", NULL }, { NULL, "skip" }, { "b", "" } };
    char out[64];
    assert_int_equal(fm_encode(f, 3, out, sizeof out, NULL), FM_OK);
    assert_string_equal(out, "a=&b=");
}

static void test_encode_overflow_fails_closed(void **state) {
    (void)state;
    fm_field f[] = { { "name", "value" } };
    char out[4];
    assert_int_equal(fm_encode(f, 1, out, sizeof out, NULL), FM_ERR_OVERFLOW);
    assert_string_equal(out, ""); /* no partial encoding */
}

static void test_encode_null_args(void **state) {
    (void)state;
    char out[8];
    assert_int_equal(fm_encode(NULL, 1, out, sizeof out, NULL), FM_ERR_NULL_ARG);
    fm_field f[] = { { "a", "b" } };
    assert_int_equal(fm_encode(f, 1, NULL, 8, NULL), FM_ERR_NULL_ARG);
    assert_int_equal(fm_encode(f, 1, out, 0, NULL), FM_ERR_NULL_ARG);
}

/* --- fm_build GET --- */

static void test_get_relative_action_on_https_base(void **state) {
    (void)state;
    fm_field f[] = { { "q", "freedom browser" } };
    fm_plan p;
    assert_int_equal(fm_build("https://duckduckgo.com/", "/search", FM_GET, f, 1, &p), FM_OK);
    assert_int_equal(p.kind, FM_NAVIGATE);
    assert_string_equal(p.url, "https://duckduckgo.com/search?q=freedom+browser");
    assert_int_equal((int)p.body_len, 0);
    assert_null(p.content_type);
}

static void test_get_absolute_https_action_ignores_base(void **state) {
    (void)state;
    /* A local page can point at a real https search engine. */
    fm_field f[] = { { "q", "x" } };
    fm_plan p;
    assert_int_equal(fm_build("/home/user/test.html", "https://www.google.com/search",
                              FM_GET, f, 1, &p), FM_OK);
    assert_int_equal(p.kind, FM_NAVIGATE);
    assert_string_equal(p.url, "https://www.google.com/search?q=x");
}

static void test_get_empty_action_submits_to_base(void **state) {
    (void)state;
    fm_field f[] = { { "q", "y" } };
    fm_plan p;
    assert_int_equal(fm_build("https://example.com/page", "", FM_GET, f, 1, &p), FM_OK);
    assert_int_equal(p.kind, FM_NAVIGATE);
    assert_string_equal(p.url, "https://example.com/page?q=y");
}

static void test_get_replaces_existing_query(void **state) {
    (void)state;
    fm_field f[] = { { "q", "new" } };
    fm_plan p;
    assert_int_equal(fm_build("https://example.com/", "https://example.com/s?old=1#frag",
                              FM_GET, f, 1, &p), FM_OK);
    assert_int_equal(p.kind, FM_NAVIGATE);
    assert_string_equal(p.url, "https://example.com/s?q=new");
}

static void test_get_action_cleaned_of_whitespace(void **state) {
    (void)state;
    fm_field f[] = { { "q", "z" } };
    fm_plan p;
    assert_int_equal(fm_build("https://example.com/", "  /se\tar\nch  ", FM_GET, f, 1, &p), FM_OK);
    assert_int_equal(p.kind, FM_NAVIGATE);
    assert_string_equal(p.url, "https://example.com/search?q=z");
}

/* --- fm_build POST --- */

static void test_post_builds_body(void **state) {
    (void)state;
    fm_field f[] = { { "user", "a b" }, { "pass", "p&q" } };
    fm_plan p;
    assert_int_equal(fm_build("https://example.com/", "https://example.com/login?ref=1",
                              FM_POST, f, 2, &p), FM_OK);
    assert_int_equal(p.kind, FM_POST_REQUEST);
    assert_string_equal(p.url, "https://example.com/login?ref=1"); /* query kept for POST */
    assert_string_equal(p.body, "user=a+b&pass=p%26q");
    assert_int_equal((int)p.body_len, (int)strlen("user=a+b&pass=p%26q"));
    assert_string_equal(p.content_type, FM_CONTENT_TYPE_URLENCODED);
}

/* --- fail-closed blocks --- */

static void test_block_http_downgrade(void **state) {
    (void)state;
    fm_field f[] = { { "q", "x" } };
    fm_plan p;
    assert_int_equal(fm_build("https://example.com/", "http://example.com/s", FM_GET, f, 1, &p), FM_OK);
    assert_int_equal(p.kind, FM_BLOCKED);
    assert_int_equal(p.reason, FM_BLOCK_INSECURE);
    assert_string_equal(p.url, "");
}

static void test_block_foreign_scheme(void **state) {
    (void)state;
    fm_field f[] = { { "q", "x" } };
    fm_plan p;
    assert_int_equal(fm_build("https://example.com/", "javascript:alert(1)", FM_GET, f, 1, &p), FM_OK);
    assert_int_equal(p.kind, FM_BLOCKED);
    assert_int_equal(p.reason, FM_BLOCK_INSECURE);
}

static void test_block_relative_action_on_local_base(void **state) {
    (void)state;
    fm_field f[] = { { "q", "x" } };
    fm_plan p;
    assert_int_equal(fm_build("/home/user/test.html", "/search", FM_GET, f, 1, &p), FM_OK);
    assert_int_equal(p.kind, FM_BLOCKED);
    assert_int_equal(p.reason, FM_BLOCK_INSECURE);
}

static void test_block_too_many_fields(void **state) {
    (void)state;
    fm_field f[FM_MAX_FIELDS + 1];
    for (size_t i = 0; i <= FM_MAX_FIELDS; ++i) { f[i].name = "k"; f[i].value = "v"; }
    fm_plan p;
    assert_int_equal(fm_build("https://example.com/", "/s", FM_GET, f, FM_MAX_FIELDS + 1, &p), FM_OK);
    assert_int_equal(p.kind, FM_BLOCKED);
    assert_int_equal(p.reason, FM_BLOCK_INVALID);
}

static void test_block_null_field_name(void **state) {
    (void)state;
    fm_field f[] = { { "ok", "1" }, { NULL, "v" } };
    fm_plan p;
    assert_int_equal(fm_build("https://example.com/", "/s", FM_GET, f, 2, &p), FM_OK);
    assert_int_equal(p.kind, FM_BLOCKED);
    assert_int_equal(p.reason, FM_BLOCK_INVALID);
}

static void test_build_null_args(void **state) {
    (void)state;
    fm_plan p;
    assert_int_equal(fm_build(NULL, "/s", FM_GET, NULL, 0, &p), FM_ERR_NULL_ARG);
    assert_int_equal(fm_build("https://example.com/", "/s", FM_GET, NULL, 0, NULL), FM_ERR_NULL_ARG);
}

static void test_get_no_fields_still_navigates(void **state) {
    (void)state;
    fm_plan p;
    assert_int_equal(fm_build("https://example.com/", "/s", FM_GET, NULL, 0, &p), FM_OK);
    assert_int_equal(p.kind, FM_NAVIGATE);
    assert_string_equal(p.url, "https://example.com/s?");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_encode_basic),
        cmocka_unit_test(test_encode_space_and_reserved),
        cmocka_unit_test(test_encode_unreserved_kept),
        cmocka_unit_test(test_encode_empty_and_nameless),
        cmocka_unit_test(test_encode_overflow_fails_closed),
        cmocka_unit_test(test_encode_null_args),
        cmocka_unit_test(test_get_relative_action_on_https_base),
        cmocka_unit_test(test_get_absolute_https_action_ignores_base),
        cmocka_unit_test(test_get_empty_action_submits_to_base),
        cmocka_unit_test(test_get_replaces_existing_query),
        cmocka_unit_test(test_get_action_cleaned_of_whitespace),
        cmocka_unit_test(test_post_builds_body),
        cmocka_unit_test(test_block_http_downgrade),
        cmocka_unit_test(test_block_foreign_scheme),
        cmocka_unit_test(test_block_relative_action_on_local_base),
        cmocka_unit_test(test_block_too_many_fields),
        cmocka_unit_test(test_block_null_field_name),
        cmocka_unit_test(test_build_null_args),
        cmocka_unit_test(test_get_no_fields_still_navigates),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
