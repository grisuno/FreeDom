/* test_css_import -- @import prelude reader (spec/css_import.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <cmocka.h>

#include "css_import.h"

static ci_import im[8];

static size_t scan(const char *s) { return ci_scan(s, strlen(s), im, 8); }

static void test_plain_url(void **state) {
    (void)state;
    assert_int_equal(scan("@import url(\"/a.css\");"), 1);
    assert_string_equal(im[0].url, "/a.css");
    assert_int_equal(im[0].has_layer, 0);
    assert_string_equal(im[0].media, "");
    assert_string_equal(im[0].supports, "");
    char o[64], c[16];
    assert_int_equal(ci_wrap(&im[0], o, sizeof o, c, sizeof c), 0);
    assert_string_equal(o, "");
    assert_string_equal(c, "");
}

static void test_url_forms(void **state) {
    (void)state;
    assert_int_equal(scan("@import 'a.css'; @import url(b.css); @import url( 'c.css' ) ;"
                          "@import \"d.css\";"), 4);
    assert_string_equal(im[0].url, "a.css");
    assert_string_equal(im[1].url, "b.css");
    assert_string_equal(im[2].url, "c.css");
    assert_string_equal(im[3].url, "d.css");
}

static void test_lobsters_media(void **state) {
    (void)state;
    const char *s =
        "/* system color scheme */\n\n"
        "@import url(\"/assets/light-normal.css\"); /* default */\n"
        "@import url(\"/assets/dark-normal.css\") (prefers-color-scheme: dark) and "
        "(not (prefers-contrast: more));\n";
    assert_int_equal(scan(s), 2);
    assert_string_equal(im[1].url, "/assets/dark-normal.css");
    assert_string_equal(im[1].media,
                        "(prefers-color-scheme: dark) and (not (prefers-contrast: more))");
    char o[256], c[16];
    assert_int_equal(ci_wrap(&im[1], o, sizeof o, c, sizeof c), 0);
    assert_string_equal(o,
        "@media (prefers-color-scheme: dark) and (not (prefers-contrast: more)) {");
    assert_string_equal(c, "}");
}

static void test_layer_supports_media(void **state) {
    (void)state;
    assert_int_equal(scan("@import url(x.css) layer(base) supports(display: grid) screen;"), 1);
    assert_int_equal(im[0].has_layer, 1);
    assert_string_equal(im[0].layer, "base");
    assert_string_equal(im[0].supports, "display: grid");
    assert_string_equal(im[0].media, "screen");
    char o[256], c[16];
    assert_int_equal(ci_wrap(&im[0], o, sizeof o, c, sizeof c), 0);
    assert_string_equal(o, "@layer base {@supports (display: grid) {@media screen {");
    assert_string_equal(c, "}}}");
    assert_int_equal(scan("@import \"y.css\" layer;"), 1);
    assert_int_equal(im[0].has_layer, 1);
    assert_string_equal(im[0].layer, "");
    assert_int_equal(ci_wrap(&im[0], o, sizeof o, c, sizeof c), 0);
    assert_string_equal(o, "@layer {");
    assert_int_equal(ci_wrap(&im[0], o, 4, c, sizeof c), -1);
}

static void test_prelude_skips(void **state) {
    (void)state;
    assert_int_equal(scan("@charset \"utf-8\"; /* c */ @layer a, b; @import \"x.css\";"), 1);
    assert_string_equal(im[0].url, "x.css");
    assert_int_equal(scan("@IMPORT \"u.css\";"), 1);
}

static void test_late_import_ignored(void **state) {
    (void)state;
    assert_int_equal(scan("a{} @import \"x.css\";"), 0);
    assert_int_equal(scan("@import \"a.css\"; b{color:red} @import \"x.css\";"), 1);
    assert_int_equal(scan("@media screen{} @import \"x.css\";"), 0);
}

static void test_malformed_fail_closed(void **state) {
    (void)state;
    assert_int_equal(scan("@import \"a.css\""), 0);                 /* no ';' */
    assert_int_equal(scan("@import \"\"; @import \"b.css\";"), 1);  /* empty url skipped */
    assert_string_equal(im[0].url, "b.css");
    assert_int_equal(scan("@import \"a.css\" screen { x; @import \"b.css\";"), 0);
    assert_int_equal(scan("@import \"a.css\" supports(x}) ; @import \"b.css\";"), 1);
    assert_string_equal(im[0].url, "b.css");
    assert_int_equal(scan("@import foo.css;"), 0);
    assert_int_equal(scan("@import \"a.css\" layer(x) layer(y);"), 0);
    assert_int_equal(scan("@importx \"a.css\";"), 0);
    assert_int_equal(scan("@import url(a b.css);"), 0);
    assert_int_equal(scan("@import \"a;b.css\";"), 1);              /* ';' inside string ok */
    assert_string_equal(im[0].url, "a;b.css");
}

static void test_oversize(void **state) {
    (void)state;
    static char big[CI_URL_MAX + 64];
    memcpy(big, "@import \"", 9);
    memset(big + 9, 'a', CI_URL_MAX);
    memcpy(big + 9 + CI_URL_MAX, "\";", 3);
    assert_int_equal(scan(big), 0);
    static char bigm[CI_COND_MAX + 64];
    int n = snprintf(bigm, sizeof bigm, "@import \"a.css\" ");
    memset(bigm + n, 'm', CI_COND_MAX);
    bigm[n + CI_COND_MAX] = ';';
    bigm[n + CI_COND_MAX + 1] = '\0';
    assert_int_equal(scan(bigm), 0);
}

static void test_cap_and_null(void **state) {
    (void)state;
    assert_int_equal(ci_scan(NULL, 4, im, 8), 0);
    assert_int_equal(ci_scan("@import \"a\";", 12, NULL, 8), 0);
    assert_int_equal(ci_scan("@import \"a\";", 12, im, 0), 0);
    assert_int_equal(ci_scan("@import \"a\";@import \"b\";@import \"c\";", 36, im, 2), 2);
    /* len bounds the read: the second import lies past len */
    assert_int_equal(ci_scan("@import \"a\";@import \"b\";", 12, im, 8), 1);
    char o[8], c[8];
    assert_int_equal(ci_wrap(NULL, o, sizeof o, c, sizeof c), -1);
}

static void test_balanced(void **state) {
    (void)state;
    assert_int_equal(ci_balanced("", 0), 1);
    assert_int_equal(ci_balanced("a{b:c} @media x{d{e:f}}", 23), 1);
    assert_int_equal(ci_balanced("a{content:\"}\"}", 14), 1);
    assert_int_equal(ci_balanced("a{} /* } */", 11), 1);
    assert_int_equal(ci_balanced("a{}}", 4), 0);
    assert_int_equal(ci_balanced("a{", 2), 0);
    assert_int_equal(ci_balanced("a{} /* x", 8), 0);
    assert_int_equal(ci_balanced("a{content:\"x}", 13), 0);
    assert_int_equal(ci_balanced("a{content:\"\\\"\"}", 15), 1);
    assert_int_equal(ci_balanced(NULL, 0), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_plain_url),
        cmocka_unit_test(test_url_forms),
        cmocka_unit_test(test_lobsters_media),
        cmocka_unit_test(test_layer_supports_media),
        cmocka_unit_test(test_prelude_skips),
        cmocka_unit_test(test_late_import_ignored),
        cmocka_unit_test(test_malformed_fail_closed),
        cmocka_unit_test(test_oversize),
        cmocka_unit_test(test_cap_and_null),
        cmocka_unit_test(test_balanced),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
