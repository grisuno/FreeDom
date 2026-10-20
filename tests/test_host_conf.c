/*
 * test_host_conf -- CMocka suite for the single host-list loader (spec/host_conf.md).
 * Uses real temporary directories: the module's whole job is reading files in order.
 */

#define _DEFAULT_SOURCE
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <cmocka.h>

#include "host_conf.h"

static void write_file(const char *dir, const char *name, const char *text) {
    char path[1200];
    snprintf(path, sizeof path, "%s/%s", dir, name);
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    fputs(text, f);
    fclose(f);
}

static void make_dir(char *buf, size_t cap) {
    snprintf(buf, cap, "/tmp/freedom_hcf_XXXXXX");
    assert_non_null(mkdtemp(buf));
}

static void test_search_order_and_dedup(void **state) {
    (void)state;
    hcf_dirs d;
    hcf_search_dirs("/env", "/home/u", &d);
    assert_int_equal(d.n, 3);
    assert_string_equal(d.path[0], "/env");
    assert_string_equal(d.path[1], "/home/u/.config/freedom");
    assert_string_equal(d.path[2], "config");
    hcf_search_dirs("", NULL, &d);
    assert_int_equal(d.n, 1);
    assert_string_equal(d.path[0], "config");
    hcf_search_dirs("config", "", &d);
    assert_int_equal(d.n, 1);
    hcf_search_dirs(NULL, NULL, NULL);   /* no crash */
}

static void test_filter_is_cumulative_and_allow_wins(void **state) {
    (void)state;
    char a[64], b[64];
    make_dir(a, sizeof a);
    make_dir(b, sizeof b);
    write_file(a, "block.conf", "0.0.0.0 ads.example\n");
    write_file(b, "allow.conf", "ok.ads.example\n");
    hcf_dirs d;
    d.n = 2;
    snprintf(d.path[0], HCF_PATH_MAX, "%s", a);
    snprintf(d.path[1], HCF_PATH_MAX, "%s", b);
    hb_set *s = hcf_load_filter(&d);
    assert_non_null(s);
    assert_int_equal(hb_check(s, "ads.example"), HB_BLOCK);
    assert_int_equal(hb_check(s, "x.ads.example"), HB_BLOCK);
    assert_int_equal(hb_check(s, "ok.ads.example"), HB_ALLOW);
    assert_true(hb_is_allowlisted(s, "ok.ads.example"));
    hb_free(s);
}

static void test_allowlist_reads_named_file(void **state) {
    (void)state;
    char a[64];
    make_dir(a, sizeof a);
    write_file(a, "js.conf", "slashdot.org\n");
    write_file(a, "allow.conf", "other.example\n");
    hcf_dirs d;
    d.n = 1;
    snprintf(d.path[0], HCF_PATH_MAX, "%s", a);
    hb_set *s = hcf_load_allowlist(&d, "js.conf");
    assert_non_null(s);
    assert_true(hb_is_allowlisted(s, "news.slashdot.org"));
    assert_false(hb_is_allowlisted(s, "other.example"));
    hb_free(s);
    assert_null(hcf_load_allowlist(&d, NULL));
    assert_null(hcf_load_allowlist(NULL, "js.conf"));
}

static void test_missing_files_fail_open(void **state) {
    (void)state;
    hcf_dirs d;
    d.n = 1;
    snprintf(d.path[0], HCF_PATH_MAX, "/nonexistent/freedom_hcf");
    hb_set *s = hcf_load_filter(&d);
    assert_non_null(s);
    assert_int_equal(hb_check(s, "anything.example"), HB_ALLOW);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 0);
    hb_free(s);
    assert_null(hcf_load_filter(NULL));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_search_order_and_dedup),
        cmocka_unit_test(test_filter_is_cumulative_and_allow_wins),
        cmocka_unit_test(test_allowlist_reads_named_file),
        cmocka_unit_test(test_missing_files_fail_open),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
