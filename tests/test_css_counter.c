/* Suite for css_counter (spec/css_counter.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>

#include "css_counter.h"

static unsigned h(const char *s) { return cnt_hash(s, strlen(s)); }

static void test_parse_decls_defaults_and_values(void **state) {
    (void)state;
    cnt_decl d[CNT_MAX_DECL];
    assert_int_equal(cnt_parse_decls("sec", 0, d), 1);
    assert_int_equal((int)d[0].name, (int)h("sec"));
    assert_int_equal(d[0].value, 0);
    assert_int_equal(cnt_parse_decls("a 2 b -3 c", 1, d), 3);
    assert_int_equal(d[0].value, 2);
    assert_int_equal(d[1].value, -3);
    assert_int_equal(d[2].value, 1);
    assert_int_equal(cnt_parse_decls("none", 0, d), 0);
}

static void test_parse_decls_fails_closed(void **state) {
    (void)state;
    cnt_decl d[CNT_MAX_DECL];
    assert_int_equal(cnt_parse_decls("", 0, d), -1);
    assert_int_equal(cnt_parse_decls("1abc", 0, d), -1);
    assert_int_equal(cnt_parse_decls("a b c d e f g h i", 0, d), -1);
    assert_int_equal(cnt_parse_decls("a 99999999999", 0, d), -1);
    assert_int_equal(cnt_parse_decls("inherit 2", 0, d), -1);
    assert_int_equal(cnt_parse_decls("a;b", 0, d), -1);
    assert_int_equal(cnt_parse_decls("a 1.5", 0, d), -1);
}

/* Given MediaWiki's body{counter-reset:h2-section ... h6-section} (five names), when it
 * is parsed, then all five are kept: a real stylesheet with more names than the old cap
 * dropped the whole declaration and every section number restarted. */
static void test_parse_decls_mediawiki_five_names(void **state) {
    (void)state;
    cnt_decl d[16];
    assert_int_equal(cnt_parse_decls("h2-section h3-section h4-section h5-section h6-section", 0, d), 5);
    assert_int_equal((int)d[4].name, (int)h("h6-section"));
}

/* Given counter-set (CSS Lists 3 section 4.3), when it runs after reset and increment,
 * then it overwrites the innermost visible instance; with no instance it creates one at
 * the element's depth, starting at 0 before setting. */
static void test_counter_set_overwrites_or_instantiates(void **state) {
    (void)state;
    char m[64], out[32];
    assert_int_equal(cnt_parse_content("counter(a) \".\" counter(b)", m, sizeof m), 1);
    cnt_state *s = cnt_state_new();
    cnt_decl ra = { h("a"), 0 }, rb = { h("b"), 0 }, ia = { h("a"), 1 }, ib = { h("b"), 1 };
    cnt_decl sb = { h("b"), 0 };
    cnt_reset(s, 1, &ra, 1);
    cnt_reset(s, 1, &rb, 1);                       /* body{counter-reset:a b} */
    cnt_increment(s, 3, &ia, 1);                   /* h2{counter-increment:a; counter-set:b} */
    cnt_set(s, 3, &sb, 1);
    cnt_increment(s, 3, &ib, 1);                   /* h3 */
    cnt_increment(s, 3, &ib, 1);                   /* h3 */
    cnt_resolve(s, m, NULL, NULL, out, sizeof out);
    assert_string_equal(out, "1.2");
    cnt_increment(s, 3, &ia, 1);                   /* next h2 resets b through counter-set */
    cnt_set(s, 3, &sb, 1);
    cnt_increment(s, 3, &ib, 1);
    cnt_resolve(s, m, NULL, NULL, out, sizeof out);
    assert_string_equal(out, "2.1");
    cnt_leave(s, 2);                               /* the body-level instances survive */
    cnt_resolve(s, m, NULL, NULL, out, sizeof out);
    assert_string_equal(out, "2.1");
    cnt_decl sz = { h("z"), 7 };
    cnt_set(s, 4, &sz, 1);                         /* no instance: created, then set */
    assert_int_equal(cnt_parse_content("counter(z)", m, sizeof m), 1);
    cnt_resolve(s, m, NULL, NULL, out, sizeof out);
    assert_string_equal(out, "7");
    cnt_leave(s, 4);
    cnt_resolve(s, m, NULL, NULL, out, sizeof out);
    assert_string_equal(out, "0");
    cnt_state_free(s);
}

static void test_format_styles(void **state) {
    (void)state;
    char b[32];
    cnt_format(CNT_DECIMAL, 42, b, sizeof b);            assert_string_equal(b, "42");
    cnt_format(CNT_DECIMAL_ZERO, 7, b, sizeof b);        assert_string_equal(b, "07");
    cnt_format(CNT_DECIMAL_ZERO, -7, b, sizeof b);       assert_string_equal(b, "-07");
    cnt_format(CNT_LOWER_ROMAN, 1994, b, sizeof b);      assert_string_equal(b, "mcmxciv");
    cnt_format(CNT_UPPER_ROMAN, 4, b, sizeof b);         assert_string_equal(b, "IV");
    cnt_format(CNT_UPPER_ROMAN, 4000, b, sizeof b);      assert_string_equal(b, "4000");
    cnt_format(CNT_LOWER_ALPHA, 27, b, sizeof b);        assert_string_equal(b, "aa");
    cnt_format(CNT_UPPER_ALPHA, 0, b, sizeof b);         assert_string_equal(b, "0");
    cnt_format(CNT_NONE, 5, b, sizeof b);                assert_string_equal(b, "");
    cnt_format(CNT_DISC, 5, b, sizeof b);                assert_string_equal(b, "\xE2\x80\xA2");
    assert_int_equal((int)cnt_format(CNT_DECIMAL, 123456, b, 4), 3);
    assert_string_equal(b, "123");
}

static const char *attr_of(void *ctx, const char *name) {
    (void)ctx;
    return strcmp(name, "title") == 0 ? "T!" : NULL;
}

static void test_content_marker_roundtrip(void **state) {
    (void)state;
    char m[256], out[128];
    assert_int_equal(cnt_parse_content("\"x\"", m, sizeof m), 0);
    assert_int_equal(cnt_parse_content("attr(title)", m, sizeof m), 0);
    assert_int_equal(cnt_parse_content("\"(\" counter(c) \")\"", m, sizeof m), 1);
    assert_true(cnt_is_marker(m));
    cnt_state *s = cnt_state_new();
    cnt_decl inc = { h("c"), 4 };
    cnt_increment(s, 1, &inc, 1);
    cnt_resolve(s, m, attr_of, NULL, out, sizeof out);
    assert_string_equal(out, "(4)");
    assert_int_equal(cnt_parse_content("counter(c, upper-roman) attr(title)", m, sizeof m), 1);
    cnt_resolve(s, m, attr_of, NULL, out, sizeof out);
    assert_string_equal(out, "IVT!");
    assert_int_equal(cnt_parse_content("\"\\201C\" counter(c)", m, sizeof m), 1);
    cnt_resolve(s, m, attr_of, NULL, out, sizeof out);
    assert_string_equal(out, "\xE2\x80\x9C" "4");
    cnt_state_free(s);
}

static void test_content_marker_malformed(void **state) {
    (void)state;
    char m[64];
    assert_int_equal(cnt_parse_content("counter(", m, sizeof m), -1);
    assert_int_equal(cnt_parse_content("counter()", m, sizeof m), -1);
    assert_int_equal(cnt_parse_content("counters(c)", m, sizeof m), -1);
    assert_int_equal(cnt_parse_content("counter(c) url(x)", m, sizeof m), -1);
    assert_int_equal(cnt_parse_content("counter(c)", m, 4), -1);
    assert_int_equal(cnt_parse_content("counter(c) \"unterminated", m, sizeof m), -1);
}

/* Siblings share one counter; an element's reset lives until its PARENT is left. */
static void test_scope_siblings_and_leave(void **state) {
    (void)state;
    char m[64], out[32];
    assert_int_equal(cnt_parse_content("counter(item)", m, sizeof m), 1);
    cnt_state *s = cnt_state_new();
    cnt_decl r = { h("item"), 0 }, i = { h("item"), 1 };
    cnt_reset(s, 1, &r, 1);                       /* body{counter-reset:item} */
    for (int k = 1; k <= 3; ++k) {
        cnt_increment(s, 2, &i, 1);               /* li{counter-increment:item} */
        cnt_resolve(s, m, NULL, NULL, out, sizeof out);
        char want[2] = { (char)('0' + k), 0 };
        assert_string_equal(out, want);
    }
    cnt_leave(s, 1);                              /* left the parent of depth-1 */
    cnt_resolve(s, m, NULL, NULL, out, sizeof out);
    assert_string_equal(out, "0");
    cnt_state_free(s);
}

static void test_scope_nested_counters_join(void **state) {
    (void)state;
    char m[64], out[32];
    assert_int_equal(cnt_parse_content("counters(item, \".\")", m, sizeof m), 1);
    cnt_state *s = cnt_state_new();
    cnt_decl r = { h("item"), 0 }, i = { h("item"), 1 };
    cnt_reset(s, 1, &r, 1);                       /* outer ol */
    cnt_increment(s, 2, &i, 1);                   /* li 1 */
    cnt_increment(s, 2, &i, 1);                   /* li 2 */
    cnt_reset(s, 3, &r, 1);                       /* nested ol inside li 2 */
    cnt_increment(s, 4, &i, 1);                   /* nested li */
    cnt_resolve(s, m, NULL, NULL, out, sizeof out);
    assert_string_equal(out, "2.1");
    cnt_leave(s, 3);                              /* nested ol's children done */
    cnt_leave(s, 3);
    cnt_resolve(s, m, NULL, NULL, out, sizeof out);
    assert_string_equal(out, "2");
    cnt_state_free(s);
}

static void test_reset_by_sibling_replaces_not_nests(void **state) {
    (void)state;
    char m[64], out[32];
    assert_int_equal(cnt_parse_content("counters(c, \"-\")", m, sizeof m), 1);
    cnt_state *s = cnt_state_new();
    cnt_decl r = { h("c"), 0 }, i = { h("c"), 1 };
    cnt_reset(s, 2, &r, 1);
    cnt_increment(s, 2, &i, 1);
    cnt_reset(s, 2, &r, 1);                       /* a sibling at the same depth */
    cnt_increment(s, 3, &i, 1);
    cnt_resolve(s, m, NULL, NULL, out, sizeof out);
    assert_string_equal(out, "1");
    cnt_state_free(s);
}

static void test_state_is_bounded(void **state) {
    (void)state;
    char m[64], out[32];
    assert_int_equal(cnt_parse_content("counter(x)", m, sizeof m), 1);
    cnt_state *s = cnt_state_new();
    for (int k = 0; k < CNT_MAX_INSTANCES + 500; ++k) {
        cnt_decl r = { (unsigned)(k + 1), 0 };
        cnt_reset(s, k + 1, &r, 1);
    }
    cnt_resolve(s, m, NULL, NULL, out, sizeof out);
    assert_string_equal(out, "0");
    cnt_state_free(s);
}

int main(void) {
    const struct CMUnitTest t[] = {
        cmocka_unit_test(test_parse_decls_defaults_and_values),
        cmocka_unit_test(test_parse_decls_fails_closed),
        cmocka_unit_test(test_parse_decls_mediawiki_five_names),
        cmocka_unit_test(test_counter_set_overwrites_or_instantiates),
        cmocka_unit_test(test_format_styles),
        cmocka_unit_test(test_content_marker_roundtrip),
        cmocka_unit_test(test_content_marker_malformed),
        cmocka_unit_test(test_scope_siblings_and_leave),
        cmocka_unit_test(test_scope_nested_counters_join),
        cmocka_unit_test(test_reset_by_sibling_replaces_not_nests),
        cmocka_unit_test(test_state_is_bounded),
    };
    return cmocka_run_group_tests(t, NULL, NULL);
}
