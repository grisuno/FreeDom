/*
 * test_download — CMocka suite for the pure download helpers.
 *
 * Covers the render-vs-download classification (attachment, renderable text
 * types, binary types, NULL/empty), the media-type -> extension map, the
 * hostile-input -> safe-filename derivation (disposition, URL segment, fallback,
 * traversal/control containment, extension synthesis, overflow), the path
 * builder (join, separator rejection, overflow, NULL), and the size cap.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "download.h"

/* --- dl_should_download --- */

static void test_should_attachment_disposition(void **state) {
    (void)state;
    assert_int_equal(dl_should_download("text/html", "attachment; filename=\"x.html\""), 1);
    assert_int_equal(dl_should_download(NULL, "ATTACHMENT"), 1);   /* case-insensitive */
    assert_int_equal(dl_should_download("text/html", "inline"), 0);
}

static void test_should_renderable_types(void **state) {
    (void)state;
    assert_int_equal(dl_should_download("text/html", NULL), 0);
    assert_int_equal(dl_should_download("text/html; charset=utf-8", NULL), 0);
    assert_int_equal(dl_should_download("application/xhtml+xml", NULL), 0);
    assert_int_equal(dl_should_download("text/plain", NULL), 0);
    assert_int_equal(dl_should_download("text/css", NULL), 0);   /* any text subtype renders */
    assert_int_equal(dl_should_download(NULL, NULL), 0);          /* missing type renders */
    assert_int_equal(dl_should_download("", NULL), 0);
}

static void test_should_binary_types(void **state) {
    (void)state;
    assert_int_equal(dl_should_download("application/pdf", NULL), 1);
    assert_int_equal(dl_should_download("application/zip", NULL), 1);
    assert_int_equal(dl_should_download("application/octet-stream", NULL), 1);
    assert_int_equal(dl_should_download("image/png", NULL), 1);
    assert_int_equal(dl_should_download("APPLICATION/PDF ; q=1", NULL), 1); /* ci + params */
}

/* --- dl_ext_for_type --- */

static void test_ext_known_types(void **state) {
    (void)state;
    assert_string_equal(dl_ext_for_type("application/pdf"), ".pdf");
    assert_string_equal(dl_ext_for_type("application/zip"), ".zip");
    assert_string_equal(dl_ext_for_type("application/epub+zip"), ".epub");
    assert_string_equal(dl_ext_for_type("text/plain; charset=utf-8"), ".txt");
    assert_string_equal(dl_ext_for_type("IMAGE/JPEG"), ".jpg");
    assert_string_equal(dl_ext_for_type("image/svg+xml"), ".svg");
    assert_string_equal(dl_ext_for_type("text/html; charset=utf-8"), ".html");
}

static void test_ext_unknown_type(void **state) {
    (void)state;
    assert_string_equal(dl_ext_for_type("application/octet-stream"), "");
    assert_string_equal(dl_ext_for_type(NULL), "");
    assert_string_equal(dl_ext_for_type("weird/thing"), "");
}

/* --- dl_pick_name --- */

static void test_pick_from_disposition_quoted(void **state) {
    (void)state;
    char out[DL_NAME_MAX + 8];
    assert_int_equal(dl_pick_name("https://x.com/dl?id=9",
                                  "attachment; filename=\"Report 2024.pdf\"",
                                  "application/pdf", out, sizeof out), DL_OK);
    assert_string_equal(out, "Report_2024.pdf");
}

static void test_pick_from_disposition_ext_form(void **state) {
    (void)state;
    char out[DL_NAME_MAX + 8];
    assert_int_equal(dl_pick_name(NULL,
                                  "attachment; filename*=UTF-8''na%C3%AFve.pdf",
                                  NULL, out, sizeof out), DL_OK);
    /* part after '' is taken, sanitized (percent bytes kept literally, safe). */
    assert_string_equal(out, "na_C3_AFve.pdf");
}

static void test_pick_from_url_segment(void **state) {
    (void)state;
    char out[DL_NAME_MAX + 8];
    assert_int_equal(dl_pick_name("https://host.tld/path/file.zip?v=2#frag",
                                  NULL, "application/zip", out, sizeof out), DL_OK);
    assert_string_equal(out, "file.zip");
}

static void test_pick_appends_extension_when_missing(void **state) {
    (void)state;
    char out[DL_NAME_MAX + 8];
    /* URL segment has no extension; content_type supplies one. */
    assert_int_equal(dl_pick_name("https://host.tld/download",
                                  NULL, "application/pdf", out, sizeof out), DL_OK);
    assert_string_equal(out, "download.pdf");
}

static void test_pick_keeps_existing_extension(void **state) {
    (void)state;
    char out[DL_NAME_MAX + 8];
    /* already has .pdf -> not doubled even though type matches. */
    assert_int_equal(dl_pick_name("https://host.tld/a/report.pdf",
                                  NULL, "application/pdf", out, sizeof out), DL_OK);
    assert_string_equal(out, "report.pdf");
}

static void test_pick_traversal_contained(void **state) {
    (void)state;
    char out[DL_NAME_MAX + 8];
    /* hostile disposition: separators map to '_', never escapes. */
    assert_int_equal(dl_pick_name("https://x.com/y",
                                  "attachment; filename=\"../../.bashrc\"",
                                  NULL, out, sizeof out), DL_OK);
    assert_null(strchr(out, '/'));
    assert_true(out[0] != '.');
    assert_string_equal(out, "bashrc");
}

static void test_pick_fallback_when_empty(void **state) {
    (void)state;
    char out[DL_NAME_MAX + 8];
    /* no disposition, URL ends in '/', no usable segment -> fallback (+ext). */
    assert_int_equal(dl_pick_name("https://host.tld/dir/", NULL,
                                  "application/zip", out, sizeof out), DL_OK);
    assert_string_equal(out, "download.zip");
    /* everything NULL -> bare fallback. */
    assert_int_equal(dl_pick_name(NULL, NULL, NULL, out, sizeof out), DL_OK);
    assert_string_equal(out, DL_FALLBACK_NAME);
}

static void test_pick_null_out(void **state) {
    (void)state;
    char out[8];
    assert_int_equal(dl_pick_name("https://x/y.pdf", NULL, NULL, NULL, sizeof out), DL_ERR_NULL_ARG);
    assert_int_equal(dl_pick_name("https://x/y.pdf", NULL, NULL, out, 0), DL_ERR_NULL_ARG);
}

static void test_pick_overflow_fails_closed(void **state) {
    (void)state;
    char out[4];
    assert_int_equal(dl_pick_name("https://x/averylongfilename.pdf",
                                  NULL, NULL, out, sizeof out), DL_ERR_OVERFLOW);
    assert_string_equal(out, "");
}

/* --- dl_build_path --- */

static void test_build_path_basic(void **state) {
    (void)state;
    char out[64];
    assert_int_equal(dl_build_path("/home/u/Downloads/freedom", "file.pdf", out, sizeof out), DL_OK);
    assert_string_equal(out, "/home/u/Downloads/freedom/file.pdf");
}

static void test_build_path_trailing_slash(void **state) {
    (void)state;
    char out[64];
    assert_int_equal(dl_build_path("/d/", "x.zip", out, sizeof out), DL_OK);
    assert_string_equal(out, "/d/x.zip");   /* not doubled */
}

static void test_build_path_rejects_separator_in_name(void **state) {
    (void)state;
    char out[64];
    assert_int_equal(dl_build_path("/d", "a/b", out, sizeof out), DL_ERR_OVERFLOW);
    assert_string_equal(out, "");
}

static void test_build_path_overflow(void **state) {
    (void)state;
    char out[8];
    assert_int_equal(dl_build_path("/a/very/long/dir", "name.pdf", out, sizeof out), DL_ERR_OVERFLOW);
    assert_string_equal(out, "");
}

static void test_build_path_null_args(void **state) {
    (void)state;
    char out[64];
    assert_int_equal(dl_build_path(NULL, "x", out, sizeof out), DL_ERR_NULL_ARG);
    assert_int_equal(dl_build_path("/d", NULL, out, sizeof out), DL_ERR_NULL_ARG);
    assert_int_equal(dl_build_path("/d", "x", NULL, sizeof out), DL_ERR_NULL_ARG);
    assert_int_equal(dl_build_path("/d", "x", out, 0), DL_ERR_NULL_ARG);
}

/* --- dl_check_size --- */

static void test_check_size(void **state) {
    (void)state;
    assert_int_equal(dl_check_size(0), DL_OK);
    assert_int_equal(dl_check_size(DL_MAX_BYTES), DL_OK);
    assert_int_equal(dl_check_size((size_t)DL_MAX_BYTES + 1), DL_ERR_TOO_LARGE);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_should_attachment_disposition),
        cmocka_unit_test(test_should_renderable_types),
        cmocka_unit_test(test_should_binary_types),
        cmocka_unit_test(test_ext_known_types),
        cmocka_unit_test(test_ext_unknown_type),
        cmocka_unit_test(test_pick_from_disposition_quoted),
        cmocka_unit_test(test_pick_from_disposition_ext_form),
        cmocka_unit_test(test_pick_from_url_segment),
        cmocka_unit_test(test_pick_appends_extension_when_missing),
        cmocka_unit_test(test_pick_keeps_existing_extension),
        cmocka_unit_test(test_pick_traversal_contained),
        cmocka_unit_test(test_pick_fallback_when_empty),
        cmocka_unit_test(test_pick_null_out),
        cmocka_unit_test(test_pick_overflow_fails_closed),
        cmocka_unit_test(test_build_path_basic),
        cmocka_unit_test(test_build_path_trailing_slash),
        cmocka_unit_test(test_build_path_rejects_separator_in_name),
        cmocka_unit_test(test_build_path_overflow),
        cmocka_unit_test(test_build_path_null_args),
        cmocka_unit_test(test_check_size),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
