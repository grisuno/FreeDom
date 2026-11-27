/* Suite for css_nest (spec/css_nest.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include <string.h>

#include "css_nest.h"

static void expect_flat(const char *in, const char *want) {
    char *out = NULL;
    size_t n = 0;
    assert_int_equal(cn_flatten(in, strlen(in), &out, &n), CN_OK);
    assert_non_null(out);
    assert_int_equal(n, strlen(out));
    assert_string_equal(out, want);
    free(out);
}

/* Given flat CSS (rules, @media, @keyframes), then there is no nesting to resolve and
 * the caller keeps its text byte-identical. */
static void test_flat_css_has_no_nesting(void **state) {
    (void)state;
    assert_int_equal(cn_has_nesting("a{b:c}", 6), 0);
    const char *m = "@media (min-width:1px){a{b:c}}@supports (x:y){p{q:r}}";
    assert_int_equal(cn_has_nesting(m, strlen(m)), 0);
    const char *k = "@keyframes k{0%{o:0}to{o:1}}@font-face{font-family:x}";
    assert_int_equal(cn_has_nesting(k, strlen(k)), 0);
    const char *s = "a{content:\"{x}\"}";
    assert_int_equal(cn_has_nesting(s, strlen(s)), 0);
    assert_int_equal(cn_has_nesting(NULL, 3), 0);
    const char *n = "a{b:c;&>p{d:e}}";
    assert_int_equal(cn_has_nesting(n, strlen(n)), 1);
    const char *nm = "@media q{a{@media r{x:1}}}";
    assert_int_equal(cn_has_nesting(nm, strlen(nm)), 1);
}

/* Given ArchWiki's related-articles rule, when flattened, then the parent keeps its own
 * declarations and the nested `& > p` becomes its own rule with & replaced. */
static void test_ampersand_child_rule(void **state) {
    (void)state;
    expect_flat("div.x{float:right;width:25%;& > p{background:#333;color:white}}",
                "div.x{float:right;width:25%}div.x > p{background:#333;color:white}");
    expect_flat("a{&.b{c:d}&:hover{e:f}.dark &{g:h}}",
                "a.b{c:d}a:hover{e:f}.dark a{g:h}");
}

/* Given a nested selector with no &, then it is a descendant of the parent, a leading
 * combinator included. */
static void test_implicit_descendant(void **state) {
    (void)state;
    expect_flat("a{.b{c:d} > e{f:g} + i{j:k}}", "a .b{c:d}a > e{f:g}a + i{j:k}");
}

/* Given selector lists on both sides, then the cross product, parent-major. */
static void test_selector_lists_cross(void **state) {
    (void)state;
    expect_flat("a, b{&:hover, .c &{x:y}}", "a:hover,.c a,b:hover,.c b{x:y}");
    expect_flat("a{:is(b, c) &{x:y}}", ":is(b, c) a{x:y}");
}

/* Given a conditional at-rule inside a style rule, then it is hoisted around the parent
 * and its body is flattened against the same parent; a top-level @media recurses. */
static void test_nested_at_rules(void **state) {
    (void)state;
    expect_flat("a{x:1;@media (w){y:2;b{z:3}}}", "a{x:1}@media (w){a{y:2}a b{z:3}}");
    expect_flat("@media q{a{&.b{c:d}}}", "@media q{a.b{c:d}}");
    expect_flat("a{@supports (d:grid){&>b{c:d}}}", "@supports (d:grid){a>b{c:d}}");
}

/* Given non-conditional at-rules and statements, then they pass through verbatim. */
static void test_passthrough(void **state) {
    (void)state;
    expect_flat("@import url(x.css);@keyframes k{0%{o:0}to{o:1}}a{&.b{c:d}}",
                "@import url(x.css);@keyframes k{0%{o:0}to{o:1}}a.b{c:d}");
}

/* Given strings, escapes, parentheses and custom properties holding braces or
 * semicolons, then none of them opens or splits a block. */
static void test_strings_parens_custom_props(void **state) {
    (void)state;
    expect_flat("a{content:\"{;}\";&.b{c:d}}", "a{content:\"{;}\"}a.b{c:d}");
    expect_flat("a{background:url(data:image/png;base64,AAA);&.b{c:d}}",
                "a{background:url(data:image/png;base64,AAA)}a.b{c:d}");
    expect_flat("a{--x:{y};&.b{c:d}}", "a{--x:{y}}a.b{c:d}");
    expect_flat("a{content:'\\'{';&.b{c:d}}", "a{content:'\\'{'}a.b{c:d}");
}

/* Given declarations after a nested rule, then they stay with the parent's own rule. */
static void test_declarations_after_nested(void **state) {
    (void)state;
    expect_flat("a{x:1;&.b{c:d}y:2}", "a{x:1;y:2}a.b{c:d}");
    expect_flat("a\n{\n  & > p { c: d; }\n}", "a > p{c: d}");
}

/* Given unbalanced input, then the open block closes at EOF, as the flat parser does. */
static void test_unbalanced_closes_at_eof(void **state) {
    (void)state;
    expect_flat("a{&.b{c:d}", "a.b{c:d}");
    expect_flat("}}a{&.b{c:d}}", "a.b{c:d}");
}

/* Given hostile nesting depth and a selector explosion, then the deep part and the
 * exploding rule are dropped (fail closed) and the rest survives. */
static void test_bounds_fail_closed(void **state) {
    (void)state;
    char deep[512] = "x{y:1;";
    for (int i = 0; i < 20; ++i) strcat(deep, "&>a{");
    strcat(deep, "z:2");
    for (int i = 0; i < 20; ++i) strcat(deep, "}");
    strcat(deep, "}");
    char *out = NULL;
    size_t n = 0;
    assert_int_equal(cn_flatten(deep, strlen(deep), &out, &n), CN_OK);
    assert_non_null(strstr(out, "x{y:1}"));
    assert_null(strstr(out, "z:2"));
    free(out);

    char big[1024] = "";
    strcat(big, "a0,a1,a2,a3,a4,a5,a6,a7,a8,a9{");
    strcat(big, "b0 &,b1 &,b2 &,b3 &,b4 &,b5 &,b6 &,b7 &,b8 &,b9 &{c:d}e:f}");
    assert_int_equal(cn_flatten(big, strlen(big), &out, &n), CN_OK);
    assert_string_equal(out, "a0,a1,a2,a3,a4,a5,a6,a7,a8,a9{e:f}");
    free(out);

    /* an escape as the last byte of an unterminated string (found by fuzz-cnest):
     * the scanners stop at the end of the input, never one byte past it */
    char *tail = (char *)malloc(3);
    assert_non_null(tail);
    memcpy(tail, "\"{\\", 3);
    assert_int_equal(cn_has_nesting(tail, 3), 0);
    assert_int_equal(cn_flatten(tail, 3, &out, &n), CN_OK);
    free(out);
    free(tail);

    assert_int_equal(cn_flatten(NULL, 1, &out, &n), CN_ERR_ARG);
    assert_int_equal(cn_flatten("a", 1, NULL, &n), CN_ERR_ARG);
}

int main(void) {
    const struct CMUnitTest t[] = {
        cmocka_unit_test(test_flat_css_has_no_nesting),
        cmocka_unit_test(test_ampersand_child_rule),
        cmocka_unit_test(test_implicit_descendant),
        cmocka_unit_test(test_selector_lists_cross),
        cmocka_unit_test(test_nested_at_rules),
        cmocka_unit_test(test_passthrough),
        cmocka_unit_test(test_strings_parens_custom_props),
        cmocka_unit_test(test_declarations_after_nested),
        cmocka_unit_test(test_unbalanced_closes_at_eof),
        cmocka_unit_test(test_bounds_fail_closed),
    };
    return cmocka_run_group_tests(t, NULL, NULL);
}
