#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <cmocka.h>

#include "fb_panes.h"

static void test_labels_and_names(void **state) {
    (void)state;
    assert_string_equal(fbp_tab_label(FBP_CONSOLE), "Console");
    assert_string_equal(fbp_tab_label(FBP_HTML), "HTML");
    assert_string_equal(fbp_tab_label(FBP_CSS), "CSS");
    assert_string_equal(fbp_tab_label(FBP_SCRIPT), "Script");
    assert_string_equal(fbp_tab_label(FBP_NET), "Net");
    assert_string_equal(fbp_tab_label(-1), "Console");
    assert_string_equal(fbp_tab_label(99), "Console");
    assert_int_equal(fbp_tab_from_name("html"), FBP_HTML);
    assert_int_equal(fbp_tab_from_name("CsS"), FBP_CSS);
    assert_int_equal(fbp_tab_from_name("NET"), FBP_NET);
    assert_int_equal(fbp_tab_from_name("console"), FBP_CONSOLE);
    assert_int_equal(fbp_tab_from_name("htm"), -1);
    assert_int_equal(fbp_tab_from_name("htmlx"), -1);
    assert_int_equal(fbp_tab_from_name(""), -1);
    assert_int_equal(fbp_tab_from_name(NULL), -1);
}

static void test_wrap_is_cyclic_and_total(void **state) {
    (void)state;
    assert_int_equal(fbp_tab_wrap(FBP_CONSOLE, 1), FBP_HTML);
    assert_int_equal(fbp_tab_wrap(FBP_THROWS, 1), FBP_CONSOLE);
    assert_int_equal(fbp_tab_wrap(FBP_CONSOLE, -1), FBP_THROWS);
    assert_int_equal(fbp_tab_wrap(FBP_CSS, 0), FBP_CSS);
    assert_int_equal(fbp_tab_wrap(77, 1), FBP_HTML);   /* invalid counts as the console */
    assert_int_equal(fbp_tab_wrap(-5, -1), FBP_THROWS);
}

static void test_hit_test_inverts_the_layout(void **state) {
    (void)state;
    const double cw = 8.0, pad = 1.5;
    double edge = 0.0;
    for (int t = 0; t < FBP_COUNT; ++t) {
        double x, w;
        fbp_tab_span(t, cw, pad, &x, &w);
        assert_true(w > 0.0);
        assert_true(x == edge);                 /* contiguous, in order */
        assert_int_equal(fbp_tab_at(x + 0.5, cw, pad), t);
        assert_int_equal(fbp_tab_at(x + w / 2.0, cw, pad), t);
        assert_int_equal(fbp_tab_at(x + w - 0.5, cw, pad), t);
        edge = x + w;
    }
    assert_int_equal(fbp_tab_at(edge + 0.5, cw, pad), -1);
    assert_int_equal(fbp_tab_at(-1.0, cw, pad), -1);
    assert_int_equal(fbp_tab_at(0.0, 0.0, pad), -1);     /* degenerate geometry fails closed */
}

static void test_quote_escapes_and_fails_closed(void **state) {
    (void)state;
    char out[64];
    assert_int_equal(fbp_js_quote("a.b", 3, out, sizeof out), 5);
    assert_string_equal(out, "\"a.b\"");
    size_t n = fbp_js_quote("a\"b\\c\nd", 7, out, sizeof out);
    assert_string_equal(out, "\"a\\\"b\\\\c\\nd\"");
    assert_int_equal(n, strlen(out));
    fbp_js_quote("\x01\x7f", 2, out, sizeof out);
    assert_string_equal(out, "\"\\u0001\\u007f\"");
    /* UTF-8 passes through byte for byte. */
    fbp_js_quote("\xc3\xa9", 2, out, sizeof out);
    assert_string_equal(out, "\"\xc3\xa9\"");
    /* An embedded NUL, a too-small buffer and an oversized argument are refused. */
    assert_int_equal(fbp_js_quote("a\0b", 3, out, sizeof out), 0);
    assert_int_equal(fbp_js_quote("abcdef", 6, out, 6), 0);
    assert_int_equal(fbp_js_quote("", 0, out, 2), 0);          /* needs 3 with the NUL */
    char big[FBP_SELECTOR_MAX + 2];
    memset(big, 'a', sizeof big);
    char huge[2 * FBP_SELECTOR_MAX + 16];
    assert_int_equal(fbp_js_quote(big, FBP_SELECTOR_MAX + 1, huge, sizeof huge), 0);
    assert_true(fbp_js_quote(big, FBP_SELECTOR_MAX, huge, sizeof huge) > 0);
    assert_int_equal(fbp_js_quote(NULL, 3, out, sizeof out), 0);
    assert_int_equal(fbp_js_quote("x", 1, NULL, 8), 0);
}

static void test_expr_per_tab(void **state) {
    (void)state;
    char out[FBP_EXPR_MAX];
    assert_int_equal(fbp_expr(FBP_CONSOLE, "", 0, out, sizeof out), 0);
    for (int t = FBP_HTML; t < FBP_COUNT; ++t) {
        size_t n = fbp_expr(t, "", 0, out, sizeof out);
        assert_true(n > 0);
        assert_int_equal(n, strlen(out));
        assert_true(strncmp(out, "(function(q){", 13) == 0);
        assert_string_equal(out + n - 4, "(\"\")");
        assert_true(fbp_is_pane(t));
    }
    assert_false(fbp_is_pane(FBP_CONSOLE));
    assert_true(strstr(out, "throws(") != NULL);        /* the last tab built is Throws */
}

/* Profile and Throws read the engine's sampler/tracer through the REPL command-line API, name
 * their tabs for --dump-pane, and fail soft when the API is absent (an untrusted page has none). */
static void test_profile_and_throws_tabs(void **state) {
    (void)state;
    char out[FBP_EXPR_MAX];
    assert_int_equal(fbp_tab_from_name("profile"), FBP_PROFILE);
    assert_int_equal(fbp_tab_from_name("THROWS"), FBP_THROWS);
    assert_string_equal(fbp_tab_label(FBP_PROFILE), "Profile");
    assert_string_equal(fbp_tab_label(FBP_THROWS), "Throws");
    assert_true(fbp_expr(FBP_PROFILE, "", 0, out, sizeof out) > 0);
    assert_non_null(strstr(out, "profile("));
    assert_non_null(strstr(out, "unavailable"));
    assert_true(fbp_expr(FBP_THROWS, "", 0, out, sizeof out) > 0);
    assert_non_null(strstr(out, "throws("));
}

static void test_expr_selector_cannot_escape_the_literal(void **state) {
    (void)state;
    char out[FBP_EXPR_MAX];
    static const char EVIL[] = "\"});alert(1);(\"";
    size_t n = fbp_expr(FBP_HTML, EVIL, sizeof EVIL - 1, out, sizeof out);
    assert_true(n > 0);
    /* The selector appears only inside the escaped literal at the very end. */
    assert_true(strstr(out, "(\"\\\"});alert(1);(\\\"\")") != NULL);
    const char *q = strstr(out, "\"});alert(1)");
    assert_non_null(q);
    assert_true(q > out && q[-1] == '\\');            /* the quote is escaped, never raw */
    assert_true(strstr(q + 1, "\"});alert(1)") == NULL);
    /* Oversized, NUL-bearing and tiny-buffer requests are refused with no expression. */
    char big[FBP_SELECTOR_MAX + 1];
    memset(big, 'a', sizeof big);
    assert_int_equal(fbp_expr(FBP_CSS, big, sizeof big, out, sizeof out), 0);
    assert_int_equal(fbp_expr(FBP_CSS, "a\0b", 3, out, sizeof out), 0);
    assert_int_equal(fbp_expr(FBP_NET, "", 0, out, 40), 0);
    assert_int_equal(fbp_expr(FBP_NET, "", 0, NULL, sizeof out), 0);
    assert_int_equal(fbp_expr(99, "", 0, out, sizeof out), 0);
    assert_int_equal(fbp_expr(FBP_HTML, NULL, 3, out, sizeof out), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_labels_and_names),
        cmocka_unit_test(test_wrap_is_cyclic_and_total),
        cmocka_unit_test(test_profile_and_throws_tabs),
        cmocka_unit_test(test_hit_test_inverts_the_layout),
        cmocka_unit_test(test_quote_escapes_and_fails_closed),
        cmocka_unit_test(test_expr_per_tab),
        cmocka_unit_test(test_expr_selector_cannot_escape_the_literal),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
