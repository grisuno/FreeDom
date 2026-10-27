#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <cmocka.h>

#include "fb_cmdline.h"
#include "freebug.h"

static void test_history_walks_and_restores_the_draft(void **state) {
    (void)state;
    fbc_history h;
    fbc_history_init(&h);
    assert_null(fbc_history_prev(&h, "x", 1));
    assert_int_equal(fbc_history_push(&h, "a=1", 3), 0);
    assert_int_equal(fbc_history_push(&h, "b=2", 3), 0);
    assert_int_equal(fbc_history_push(&h, "b=2", 3), 0);      /* same as the newest: ignored */
    assert_int_equal(fbc_history_push(&h, "", 0), 0);          /* empty: ignored */
    assert_int_equal((int)h.n, 2);
    assert_string_equal(fbc_history_prev(&h, "dra", 3), "b=2");
    assert_string_equal(fbc_history_prev(&h, "zzz", 3), "a=1");
    assert_null(fbc_history_prev(&h, "zzz", 3));              /* nothing older */
    assert_string_equal(fbc_history_next(&h), "b=2");
    assert_string_equal(fbc_history_next(&h), "dra");          /* back to the draft, not "zzz" */
    assert_null(fbc_history_next(&h));                         /* already live */
    fbc_history_free(&h);
    fbc_history_free(&h);
}

static void test_history_is_bounded_and_push_returns_to_live(void **state) {
    (void)state;
    fbc_history h;
    fbc_history_init(&h);
    char buf[16];
    for (int i = 0; i < FBC_HIST_MAX + 10; ++i) {
        int n = snprintf(buf, sizeof buf, "e%d", i);
        assert_int_equal(fbc_history_push(&h, buf, (size_t)n), 0);
    }
    assert_int_equal((int)h.n, FBC_HIST_MAX);
    assert_string_equal(fbc_history_prev(&h, "", 0), "e73");
    assert_int_equal(fbc_history_push(&h, "new", 3), 0);
    assert_string_equal(fbc_history_prev(&h, "", 0), "new");
    static char big[FBC_ENTRY_MAX + 1];
    memset(big, 'a', sizeof big);
    assert_int_equal(fbc_history_push(&h, big, sizeof big), -1);
    fbc_history_free(&h);
}

static void test_complete_split(void **state) {
    (void)state;
    char base[FBC_BASE_MAX];
    size_t off = 99;
    assert_int_equal(fbc_complete_split("document.body.chi", 17, base, sizeof base, &off), 3);
    assert_string_equal(base, "document.body");
    assert_int_equal((int)off, 14);
    assert_int_equal(fbc_complete_split("x = win", 7, base, sizeof base, &off), 3);
    assert_string_equal(base, "");
    assert_int_equal((int)off, 4);
    assert_int_equal(fbc_complete_split("a.", 2, base, sizeof base, &off), 0);   /* empty prefix after a dot */
    assert_string_equal(base, "a");
    assert_int_equal(fbc_complete_split("foo(", 4, base, sizeof base, &off), -1); /* nothing typed */
    assert_int_equal(fbc_complete_split("", 0, base, sizeof base, &off), -1);
    assert_int_equal(fbc_complete_split("a..b", 4, base, sizeof base, &off), -1);
    assert_int_equal(fbc_complete_split("a[0].b", 6, base, sizeof base, &off), -1);
    assert_int_equal(fbc_complete_split("1.5", 3, base, sizeof base, &off), -1);  /* a number, not a path */
}

static void test_names_expr_quotes_the_base(void **state) {
    (void)state;
    char out[1024];
    assert_true(fbc_names_expr("document.body", out, sizeof out) > 0);
    assert_non_null(strstr(out, "(\"document.body\")"));
    assert_non_null(strstr(out, "getOwnPropertyDescriptor"));
    assert_int_equal(fbc_names_expr("a\"});alert(1);(\"", out, sizeof out), 0);   /* only path characters */
    assert_int_equal(fbc_names_expr("document", out, 20), 0);
}

static void test_pick_common_prefix_and_list(void **state) {
    (void)state;
    char ins[64], list[256];
    size_t count = 0;
    const char *names = "children\nchildElementCount\nchildNodes\nclassList\nclick";
    size_t n = fbc_complete_pick(names, "chi", 3, ins, sizeof ins, list, sizeof list, &count);
    assert_int_equal((int)count, 3);
    assert_string_equal(ins, "ld");
    assert_int_equal((int)n, 2);
    assert_string_equal(list, "children childElementCount childNodes");
    n = fbc_complete_pick(names, "cli", 3, ins, sizeof ins, list, sizeof list, &count);
    assert_int_equal((int)count, 1);
    assert_string_equal(ins, "ck");
    n = fbc_complete_pick(names, "zz", 2, ins, sizeof ins, list, sizeof list, &count);
    assert_int_equal((int)count, 0);
    assert_int_equal((int)n, 0);
    assert_string_equal(ins, "");
}

static void test_filter(void **state) {
    (void)state;
    assert_true(fbc_filter_passes(FBC_FILTER_ALL, FB_DEBUG));
    assert_true(fbc_filter_passes(FBC_FILTER_ERRORS, FB_ERROR));
    assert_false(fbc_filter_passes(FBC_FILTER_ERRORS, FB_WARN));
    assert_true(fbc_filter_passes(FBC_FILTER_WARNINGS, FB_WARN));
    assert_false(fbc_filter_passes(FBC_FILTER_WARNINGS, FB_LOG));
    assert_true(fbc_filter_passes(FBC_FILTER_LOGS, FB_LOG));
    assert_true(fbc_filter_passes(FBC_FILTER_LOGS, FB_INFO));
    assert_true(fbc_filter_passes(FBC_FILTER_LOGS, FB_DEBUG));
    assert_false(fbc_filter_passes(FBC_FILTER_LOGS, FB_ERROR));
    assert_true(fbc_filter_passes(99, FB_ERROR));       /* unknown filter never hides */
    assert_int_equal(fbc_filter_next(FBC_FILTER_ALL), FBC_FILTER_ERRORS);
    assert_int_equal(fbc_filter_next(FBC_FILTER_LOGS), FBC_FILTER_ALL);
    assert_int_equal(fbc_filter_next(-3), FBC_FILTER_ERRORS);
    assert_string_equal(fbc_filter_label(FBC_FILTER_ERRORS), "Errors");
    assert_string_equal(fbc_filter_label(99), "All");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_history_walks_and_restores_the_draft),
        cmocka_unit_test(test_history_is_bounded_and_push_returns_to_live),
        cmocka_unit_test(test_complete_split),
        cmocka_unit_test(test_names_expr_quotes_the_base),
        cmocka_unit_test(test_pick_common_prefix_and_list),
        cmocka_unit_test(test_filter),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
