/*
 * TDD suite for webfont (trusted-side @font-face lookahead scanner).
 *
 * RED state until src/webfont.c exists: this links and fails on purpose.
 *
 * Build: make test   (cmocka, no network, no fonts needed)
 * ASan:  make asan
 * Fuzz:  make fuzz-wf
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include <stdio.h>

#include "webfont.h"

static void test_scan_null_args(void **state) {
    (void)state;
    wf_list l;
    memset(&l, 0, sizeof l);
    assert_int_equal(wf_scan(NULL, 3, &l), -1);
    assert_int_equal(wf_scan("x", 1, NULL), -1);
    assert_int_equal(wf_scan("", 0, &l), 0);
    assert_int_equal(l.count, 0);
    wf_list_free(&l);
    wf_list_free(NULL);
}

static void test_scan_basic_two_formats(void **state) {
    (void)state;
    const char *css =
        "@font-face{font-family:'X';"
        "src:url(a.woff2) format('woff2'),url(a.woff) format('woff');}";
    wf_list l;
    memset(&l, 0, sizeof l);
    assert_int_equal(wf_scan(css, strlen(css), &l), 0);
    assert_int_equal(l.count, 2);
    assert_string_equal(l.refs[0].family, "X");
    assert_string_equal(l.refs[0].url, "a.woff2");
    assert_string_equal(l.refs[0].format, "woff2");
    assert_string_equal(l.refs[1].url, "a.woff");
    assert_string_equal(l.refs[1].format, "woff");
    assert_int_equal(l.refs[0].bold, 0);
    assert_int_equal(l.refs[0].italic, 0);
    wf_list_free(&l);
}

static void test_scan_weight_style(void **state) {
    (void)state;
    const char *css =
        "@font-face{font-family:Y;src:url(b.woff);"
        "font-weight:700;font-style:italic;}";
    wf_list l;
    memset(&l, 0, sizeof l);
    assert_int_equal(wf_scan(css, strlen(css), &l), 0);
    assert_int_equal(l.count, 1);
    assert_string_equal(l.refs[0].family, "Y");
    assert_int_equal(l.refs[0].bold, 1);
    assert_int_equal(l.refs[0].italic, 1);
    wf_list_free(&l);

    const char *css2 =
        "@font-face{font-family:Z;src:url(c.woff);"
        "font-weight:400;font-style:normal;}";
    wf_list l2;
    memset(&l2, 0, sizeof l2);
    assert_int_equal(wf_scan(css2, strlen(css2), &l2), 0);
    assert_int_equal(l2.count, 1);
    assert_int_equal(l2.refs[0].bold, 0);
    assert_int_equal(l2.refs[0].italic, 0);
    wf_list_free(&l2);
}

static void test_scan_local_only_yields_nothing(void **state) {
    (void)state;
    const char *css =
        "@font-face{font-family:W;src:local('W Regular'),local(W-Bold);}";
    wf_list l;
    memset(&l, 0, sizeof l);
    assert_int_equal(wf_scan(css, strlen(css), &l), 0);
    assert_int_equal(l.count, 0);
    wf_list_free(&l);
}

static void test_scan_quoted_family_variants(void **state) {
    (void)state;
    const char *css =
        "@font-face{font-family:\"Q\";src:url(q.woff);}"
        "@font-face{font-family:U;src:url(u.woff);}";
    wf_list l;
    memset(&l, 0, sizeof l);
    assert_int_equal(wf_scan(css, strlen(css), &l), 0);
    assert_int_equal(l.count, 2);
    assert_string_equal(l.refs[0].family, "Q");
    assert_string_equal(l.refs[1].family, "U");
    wf_list_free(&l);
}

static void test_scan_case_and_ws(void **state) {
    (void)state;
    const char *css =
        "@FONT-FACE  { FONT-FAMILY : 'Ci' ; SRC : URL( /f.woff ) FORMAT( 'WOFF' ) ; }";
    wf_list l;
    memset(&l, 0, sizeof l);
    assert_int_equal(wf_scan(css, strlen(css), &l), 0);
    assert_int_equal(l.count, 1);
    assert_string_equal(l.refs[0].family, "Ci");
    assert_string_equal(l.refs[0].url, "/f.woff");
    assert_string_equal(l.refs[0].format, "woff");
    wf_list_free(&l);
}

static void test_scan_hostile_truncations(void **state) {
    (void)state;
    /* Unclosed block, unclosed url(, missing family: never crash, never emit. */
    const char *cases[] = {
        "@font-face{font-family:X;src:url(a.woff",
        "@font-face{font-family:X;src:",
        "@font-face{src:url(a.woff);}",
        "@font-face{}",
        "@font-face",
        "@font-face{font-family:;src:url(a.woff);}",
    };
    for (size_t i = 0; i < sizeof cases / sizeof cases[0]; ++i) {
        wf_list l;
        memset(&l, 0, sizeof l);
        assert_int_equal(wf_scan(cases[i], strlen(cases[i]), &l), 0);
        assert_int_equal(l.count, 0);
        wf_list_free(&l);
    }
}

static void test_scan_overlong_url_dropped(void **state) {
    (void)state;
    char css[2300];
    size_t o = 0;
    o += (size_t)snprintf(css + o, sizeof css - o,
                          "@font-face{font-family:L;src:url(");
    for (int i = 0; i < 1100 && o + 1 < sizeof css; ++i) css[o++] = 'a';
    o += (size_t)snprintf(css + o, sizeof css - o, ");}");
    wf_list l;
    memset(&l, 0, sizeof l);
    assert_int_equal(wf_scan(css, o, &l), 0);
    assert_int_equal(l.count, 0);
    wf_list_free(&l);
}

static void test_supported_format(void **state) {
    (void)state;
    assert_int_equal(wf_supported_format("woff"), 1);
    assert_int_equal(wf_supported_format("WOFF"), 1);
    assert_int_equal(wf_supported_format("truetype"), 1);
    assert_int_equal(wf_supported_format("opentype"), 1);
    assert_int_equal(wf_supported_format(""), 1);
    assert_int_equal(wf_supported_format("woff2"), 0);
    assert_int_equal(wf_supported_format("embedded-opentype"), 0);
    assert_int_equal(wf_supported_format("svg"), 0);
    assert_int_equal(wf_supported_format(NULL), 0);
}

static void test_scan_ignores_other_at_rules(void **state) {
    (void)state;
    const char *css =
        "@media screen{div{color:red;}}"
        "@font-face{font-family:M;src:url(m.woff);}div{margin:0;}";
    wf_list l;
    memset(&l, 0, sizeof l);
    assert_int_equal(wf_scan(css, strlen(css), &l), 0);
    assert_int_equal(l.count, 1);
    assert_string_equal(l.refs[0].family, "M");
    wf_list_free(&l);
}

static void test_data_url_decodes_at_scan(void **state) {
    (void)state;
    /* 4 bytes 00 01 00 00 (TrueType magic) as base64. */
    const char *css =
        "@font-face{font-family:'Db';src:url(data:font/ttf;base64,AAEAAA==);}";
    wf_list l;
    memset(&l, 0, sizeof l);
    assert_int_equal(wf_scan(css, strlen(css), &l), 0);
    assert_int_equal(l.count, 1);
    assert_int_equal(l.refs[0].is_data, 1);
    assert_string_equal(l.refs[0].family, "Db");
    assert_string_equal(l.refs[0].url, "");
    assert_int_equal(l.refs[0].data_len, 4);
    assert_int_equal(l.refs[0].data_bytes[1], 1);
    wf_list_free(&l);
}

static void test_ref_move_transfers_bytes(void **state) {
    (void)state;
    const char *css =
        "@font-face{font-family:'Mv';src:url(data:font/ttf;base64,AAEAAA==);}";
    wf_list l;
    memset(&l, 0, sizeof l);
    assert_int_equal(wf_scan(css, strlen(css), &l), 0);
    assert_int_equal(l.count, 1);
    wf_ref dst;
    memset(&dst, 0, sizeof dst);
    wf_ref_move(&dst, &l.refs[0]);
    assert_int_equal(dst.is_data, 1);
    assert_non_null(dst.data_bytes);
    assert_null(l.refs[0].data_bytes);
    /* Freeing both must not double-free (ASan would abort). */
    free(dst.data_bytes);
    dst.data_bytes = NULL;
    wf_list_free(&l);
}

static void test_name_hash(void **state) {
    (void)state;
    assert_int_equal(wf_name_hash(NULL, 0), 0);
    assert_int_equal(wf_name_hash("", 0), 0);
    assert_true(wf_name_hash("X", 1) != 0);
    /* Case-insensitive: the worker and the parent agree on any capitalisation. */
    assert_int_equal(wf_name_hash("Oswald", 6), wf_name_hash("OSWALD", 6));
    assert_int_equal(wf_name_hash("Oswald", 6), wf_name_hash("oswald", 6));
    assert_true(wf_name_hash("Oswald", 6) != wf_name_hash("Mulish", 6));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_scan_null_args),
        cmocka_unit_test(test_scan_basic_two_formats),
        cmocka_unit_test(test_scan_weight_style),
        cmocka_unit_test(test_scan_local_only_yields_nothing),
        cmocka_unit_test(test_scan_quoted_family_variants),
        cmocka_unit_test(test_scan_case_and_ws),
        cmocka_unit_test(test_scan_hostile_truncations),
        cmocka_unit_test(test_scan_overlong_url_dropped),
        cmocka_unit_test(test_supported_format),
        cmocka_unit_test(test_scan_ignores_other_at_rules),
        cmocka_unit_test(test_data_url_decodes_at_scan),
        cmocka_unit_test(test_ref_move_transfers_bytes),
        cmocka_unit_test(test_name_hash),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
