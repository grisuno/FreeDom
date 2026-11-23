/* Tests for doc_title (spec/doc_title.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <string.h>
#include <cmocka.h>

#include "doc_title.h"

static const char *scan(const char *html, size_t cap) {
    static char out[512];
    if (cap > sizeof out) cap = sizeof out;
    memset(out, 'X', sizeof out);
    (void)dt_scan(html, strlen(html), out, cap);
    return out;
}

static void test_entities(void **state) {
    (void)state;
    assert_string_equal(scan("<html><head><title>A &amp; B &lt;c&gt; &quot;d&quot; &#39;e&apos;</title>", 512),
                        "A & B <c> \"d\" 'e'");
    assert_string_equal(scan("<title>&#x41;&#66;&#67 x&nbsp;y</title>", 512), "ABC x\xC2\xA0y");
    assert_string_equal(scan("<title>&bogus; &</title>", 512), "&bogus; &");
}

static void test_skips_raw_text_and_comments(void **state) {
    (void)state;
    assert_string_equal(scan("<script>\"<title>x</title>\"</script><title>Y</title>", 512), "Y");
    assert_string_equal(scan("<style>a{}</style><!-- <title>x</title> --><TITLE>  Z\n z </TITLE>", 512), "Z z");
    assert_string_equal(scan("<template><title>no</title></template><title>yes</title>", 512), "yes");
    assert_string_equal(scan("<noscript><title>no</title></noscript><title  lang=en>ok</title >", 512), "ok");
    assert_string_equal(scan("<titlex>no</titlex><title>t</title>", 512), "t");
}

static void test_absent_or_empty(void **state) {
    (void)state;
    char out[8] = "zz";
    assert_int_equal(dt_scan("<p>hi</p>", 9, out, sizeof out), 0);
    assert_string_equal(out, "");
    assert_int_equal(dt_scan("<title> \t </title>", 18, out, sizeof out), 0);
    assert_string_equal(out, "");
    assert_int_equal(dt_scan(NULL, 3, out, sizeof out), 0);
    assert_int_equal(dt_scan("<title>x", 8, NULL, 4), 0);
    assert_int_equal(dt_scan("<title>x", 8, out, 0), 0);
    assert_int_equal(dt_scan("<title>unterminated", 19, out, sizeof out), 1);
    assert_string_equal(out, "untermi");
}

static void test_utf8_sanitized(void **state) {
    (void)state;
    assert_string_equal(scan("<title>a\xFF" "b&#0;c</title>", 512), "a\xEF\xBF\xBD" "b\xEF\xBF\xBD" "c");
    assert_string_equal(scan("<title>x\xE2\x80\xAEyz&#x202E;w</title>", 512), "xyzw");
    assert_string_equal(scan("<title>a\x01\x7F" "b</title>", 512), "a b");
    assert_string_equal(scan("<title>&#xD800;&#x110000;</title>", 512), "\xEF\xBF\xBD\xEF\xBF\xBD");
    assert_string_equal(scan("<title>\xC3\xB1\xC3\xB1\xC3\xB1</title>", 4), "\xC3\xB1");
}

static void test_scan_bound(void **state) {
    (void)state;
    static char big[DT_SCAN_MAX + 64];
    memset(big, ' ', sizeof big);
    memcpy(big + DT_SCAN_MAX, "<title>far</title>", 18);
    char out[16];
    assert_int_equal(dt_scan(big, sizeof big, out, sizeof out), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_entities),
        cmocka_unit_test(test_skips_raw_text_and_comments),
        cmocka_unit_test(test_absent_or_empty),
        cmocka_unit_test(test_utf8_sanitized),
        cmocka_unit_test(test_scan_bound),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
