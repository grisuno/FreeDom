/*
 * test_pdf_export — CMocka suite for the pure PDF-export helpers.
 *
 * Covers the hostile-title -> safe-basename sanitizer (kept vs mapped bytes,
 * underscore collapsing, edge trimming, length bound, fail-closed fallback,
 * traversal/control/NUL/non-ASCII rejection, overflow), the full-path builder
 * (join, trailing slash, traversal containment, overflow, NULL args), and the
 * deterministic pagination (single/multi page, no row splitting, oversized row,
 * gap preservation, invalid args).
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "pdf_export.h"

/* --- pe_safe_basename --- */

static void test_basename_keeps_unreserved(void **state) {
    (void)state;
    char out[PE_NAME_MAX + 1];
    assert_int_equal(pe_safe_basename("Report_v2.final-1", out, sizeof out), PE_OK);
    assert_string_equal(out, "Report_v2.final-1");
}

static void test_basename_maps_spaces_and_reserved(void **state) {
    (void)state;
    char out[64];
    /* spaces, punctuation and symbols -> '_', collapsed. */
    assert_int_equal(pe_safe_basename("Hello, World! (draft)", out, sizeof out), PE_OK);
    assert_string_equal(out, "Hello_World_draft");
}

static void test_basename_rejects_path_separators(void **state) {
    (void)state;
    char out[64];
    /* '/' and '\\' become '_': the result can never contain a separator. */
    assert_int_equal(pe_safe_basename("a/b\\c", out, sizeof out), PE_OK);
    assert_string_equal(out, "a_b_c");
    assert_null(strchr(out, '/'));
    assert_null(strchr(out, '\\'));
}

static void test_basename_neutralizes_traversal(void **state) {
    (void)state;
    char out[64];
    /* "../../etc/passwd": separators -> '_', leading dots trimmed. No "..". */
    assert_int_equal(pe_safe_basename("../../etc/passwd", out, sizeof out), PE_OK);
    assert_string_equal(out, "etc_passwd");
}

static void test_basename_dotdot_only_falls_back(void **state) {
    (void)state;
    char out[64];
    assert_int_equal(pe_safe_basename("..", out, sizeof out), PE_OK);
    assert_string_equal(out, PE_FALLBACK_NAME);
}

static void test_basename_trims_edges(void **state) {
    (void)state;
    char out[64];
    /* leading/trailing '.', '-', '_' are trimmed; interior kept. */
    assert_int_equal(pe_safe_basename("--.hidden.name.--", out, sizeof out), PE_OK);
    assert_string_equal(out, "hidden.name");
}

static void test_basename_collapses_underscores(void **state) {
    (void)state;
    char out[64];
    assert_int_equal(pe_safe_basename("a   ---   b", out, sizeof out), PE_OK);
    assert_string_equal(out, "a_---_b"); /* '_' runs collapse; '-' kept literally */
}

static void test_basename_control_bytes_mapped(void **state) {
    (void)state;
    char out[64];
    /* tab, newline, CR, bell -> '_' (collapsed); flanked by letters. */
    assert_int_equal(pe_safe_basename("x\t\n\r\ay", out, sizeof out), PE_OK);
    assert_string_equal(out, "x_y");
}

static void test_basename_non_ascii_mapped(void **state) {
    (void)state;
    char out[64];
    /* UTF-8 "café" (c a f 0xC3 0xA9): high bytes -> '_' (collapsed), then trailing
     * '_' trimmed. ASCII-only result. */
    assert_int_equal(pe_safe_basename("caf\xC3\xA9", out, sizeof out), PE_OK);
    assert_string_equal(out, "caf");
}

static void test_basename_empty_and_null_fall_back(void **state) {
    (void)state;
    char out[64];
    assert_int_equal(pe_safe_basename("", out, sizeof out), PE_OK);
    assert_string_equal(out, PE_FALLBACK_NAME);
    assert_int_equal(pe_safe_basename(NULL, out, sizeof out), PE_OK);
    assert_string_equal(out, PE_FALLBACK_NAME);
}

static void test_basename_all_separators_fall_back(void **state) {
    (void)state;
    char out[64];
    assert_int_equal(pe_safe_basename("/// \\\\ ...", out, sizeof out), PE_OK);
    assert_string_equal(out, PE_FALLBACK_NAME);
}

static void test_basename_length_bound(void **state) {
    (void)state;
    char in[PE_NAME_MAX + 64];
    memset(in, 'a', sizeof in - 1);
    in[sizeof in - 1] = '\0';
    char out[PE_NAME_MAX + 1];
    assert_int_equal(pe_safe_basename(in, out, sizeof out), PE_OK);
    assert_true(strlen(out) <= PE_NAME_MAX);
    assert_true(strlen(out) > 0);
}

static void test_basename_null_out_and_zero_size(void **state) {
    (void)state;
    char out[8];
    assert_int_equal(pe_safe_basename("x", NULL, sizeof out), PE_ERR_NULL_ARG);
    assert_int_equal(pe_safe_basename("x", out, 0), PE_ERR_NULL_ARG);
}

static void test_basename_overflow_fails_closed(void **state) {
    (void)state;
    char out[3]; /* too small for "page" (fallback) too */
    assert_int_equal(pe_safe_basename("hello", out, sizeof out), PE_ERR_OVERFLOW);
    assert_string_equal(out, ""); /* no partial name */
}

/* --- pe_build_path --- */

static void test_build_path_basic(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(pe_build_path("/home/u/Downloads", "My Page", out, sizeof out), PE_OK);
    assert_string_equal(out, "/home/u/Downloads/My_Page.pdf");
}

static void test_build_path_trailing_slash(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(pe_build_path("/tmp/", "doc", out, sizeof out), PE_OK);
    assert_string_equal(out, "/tmp/doc.pdf"); /* no doubled slash */
}

static void test_build_path_hostile_title_contained(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(pe_build_path("/safe/dir", "../../../etc/passwd", out, sizeof out), PE_OK);
    assert_string_equal(out, "/safe/dir/etc_passwd.pdf");
    /* the only '/' after the dir prefix is the joining one: no traversal. */
    assert_null(strstr(out + strlen("/safe/dir"), ".."));
}

static void test_build_path_empty_title_fallback(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(pe_build_path("/tmp", "", out, sizeof out), PE_OK);
    assert_string_equal(out, "/tmp/page.pdf");
}

static void test_build_path_overflow_fails_closed(void **state) {
    (void)state;
    char out[16];
    assert_int_equal(pe_build_path("/a/very/long/dir", "name", out, sizeof out), PE_ERR_OVERFLOW);
    assert_string_equal(out, "");
}

static void test_build_path_null_args(void **state) {
    (void)state;
    char out[64];
    assert_int_equal(pe_build_path(NULL, "x", out, sizeof out), PE_ERR_NULL_ARG);
    assert_int_equal(pe_build_path("/tmp", "x", NULL, sizeof out), PE_ERR_NULL_ARG);
    assert_int_equal(pe_build_path("/tmp", "x", out, 0), PE_ERR_NULL_ARG);
}

/* --- pe_build_path_ext (PNG and other extensions) --- */

static void test_build_path_ext_png(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(pe_build_path_ext("/home/u/Downloads", "My Page", PE_EXT_PNG,
                                       out, sizeof out), PE_OK);
    assert_string_equal(out, "/home/u/Downloads/My_Page.png");
}

static void test_build_path_ext_null_ext(void **state) {
    (void)state;
    char out[256];
    /* ext == NULL is treated as "" (no extension appended). */
    assert_int_equal(pe_build_path_ext("/tmp", "doc", NULL, out, sizeof out), PE_OK);
    assert_string_equal(out, "/tmp/doc");
}

static void test_build_path_ext_hostile_title_contained(void **state) {
    (void)state;
    char out[256];
    /* The hostile title is sanitised the same way regardless of extension: no
     * traversal escapes the dir. */
    assert_int_equal(pe_build_path_ext("/safe/dir", "../../../etc/passwd",
                                       PE_EXT_PNG, out, sizeof out), PE_OK);
    assert_string_equal(out, "/safe/dir/etc_passwd.png");
    assert_null(strstr(out + strlen("/safe/dir"), ".."));
}

static void test_build_path_ext_overflow_fails_closed(void **state) {
    (void)state;
    char out[16];
    assert_int_equal(pe_build_path_ext("/a/very/long/dir", "name", PE_EXT_PNG,
                                       out, sizeof out), PE_ERR_OVERFLOW);
    assert_string_equal(out, "");
}

/* --- pe_paginate --- */

static void test_paginate_single_page(void **state) {
    (void)state;
    double tops[]    = { 0.0, 100.0, 200.0 };
    double heights[] = { 100.0, 100.0, 100.0 };
    int page[3];
    double y[3];
    size_t pages = pe_paginate(tops, heights, 3, 696.0, page, y);
    assert_int_equal(pages, 1);
    assert_int_equal(page[0], 0);
    assert_int_equal(page[1], 0);
    assert_int_equal(page[2], 0);
    /* gaps preserved (tops are contiguous here). */
    assert_true(y[0] == 0.0 && y[1] == 100.0 && y[2] == 200.0);
}

static void test_paginate_breaks_without_splitting(void **state) {
    (void)state;
    double tops[]    = { 0.0, 600.0 };
    double heights[] = { 100.0, 200.0 }; /* second: 600+200=800 > 696 */
    int page[2];
    double y[2];
    size_t pages = pe_paginate(tops, heights, 2, 696.0, page, y);
    assert_int_equal(pages, 2);
    assert_int_equal(page[0], 0);
    assert_true(y[0] == 0.0);
    assert_int_equal(page[1], 1);   /* pushed to a fresh page, not split */
    assert_true(y[1] == 0.0);       /* starts at the top of the new page */
}

static void test_paginate_oversized_row_not_split(void **state) {
    (void)state;
    double tops[]    = { 0.0 };
    double heights[] = { 5000.0 };  /* taller than any page */
    int page[1];
    double y[1];
    size_t pages = pe_paginate(tops, heights, 1, 696.0, page, y);
    assert_int_equal(pages, 1);
    assert_int_equal(page[0], 0);
    assert_true(y[0] == 0.0);       /* own page, overflows, not split */
}

static void test_paginate_preserves_gaps(void **state) {
    (void)state;
    /* a gap between row 0 and row 1 (top jumps by more than height). */
    double tops[]    = { 0.0, 150.0 };
    double heights[] = { 100.0, 100.0 };
    int page[2];
    double y[2];
    size_t pages = pe_paginate(tops, heights, 2, 696.0, page, y);
    assert_int_equal(pages, 1);
    assert_true(y[1] == 150.0);     /* 50px gap kept inside the page */
}

static void test_paginate_invalid_args(void **state) {
    (void)state;
    double tops[]    = { 0.0 };
    double heights[] = { 10.0 };
    int page[1];
    double y[1];
    assert_int_equal(pe_paginate(tops, heights, 0, 696.0, page, y), 0);   /* n == 0 */
    assert_int_equal(pe_paginate(tops, heights, 1, 0.0, page, y), 0);     /* page_h <= 0 */
    assert_int_equal(pe_paginate(NULL, heights, 1, 696.0, page, y), 0);   /* NULL */
    assert_int_equal(pe_paginate(tops, NULL, 1, 696.0, page, y), 0);
    assert_int_equal(pe_paginate(tops, heights, 1, 696.0, NULL, y), 0);
    assert_int_equal(pe_paginate(tops, heights, 1, 696.0, page, NULL), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_basename_keeps_unreserved),
        cmocka_unit_test(test_basename_maps_spaces_and_reserved),
        cmocka_unit_test(test_basename_rejects_path_separators),
        cmocka_unit_test(test_basename_neutralizes_traversal),
        cmocka_unit_test(test_basename_dotdot_only_falls_back),
        cmocka_unit_test(test_basename_trims_edges),
        cmocka_unit_test(test_basename_collapses_underscores),
        cmocka_unit_test(test_basename_control_bytes_mapped),
        cmocka_unit_test(test_basename_non_ascii_mapped),
        cmocka_unit_test(test_basename_empty_and_null_fall_back),
        cmocka_unit_test(test_basename_all_separators_fall_back),
        cmocka_unit_test(test_basename_length_bound),
        cmocka_unit_test(test_basename_null_out_and_zero_size),
        cmocka_unit_test(test_basename_overflow_fails_closed),
        cmocka_unit_test(test_build_path_basic),
        cmocka_unit_test(test_build_path_trailing_slash),
        cmocka_unit_test(test_build_path_hostile_title_contained),
        cmocka_unit_test(test_build_path_ext_png),
        cmocka_unit_test(test_build_path_ext_null_ext),
        cmocka_unit_test(test_build_path_ext_hostile_title_contained),
        cmocka_unit_test(test_build_path_ext_overflow_fails_closed),
        cmocka_unit_test(test_build_path_empty_title_fallback),
        cmocka_unit_test(test_build_path_overflow_fails_closed),
        cmocka_unit_test(test_build_path_null_args),
        cmocka_unit_test(test_paginate_single_page),
        cmocka_unit_test(test_paginate_breaks_without_splitting),
        cmocka_unit_test(test_paginate_oversized_row_not_split),
        cmocka_unit_test(test_paginate_preserves_gaps),
        cmocka_unit_test(test_paginate_invalid_args),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
