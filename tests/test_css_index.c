/* test_css_index -- cascade rule index (spec/css_index.md). */
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include "css_index.h"

static css_sel *parse_all(const char *const *src, size_t n) {
    css_sel *s = calloc(n, sizeof *s);
    assert_non_null(s);
    for (size_t i = 0; i < n; ++i) {
        assert_int_equal(csel_parse(src[i], 0, strlen(src[i]), &s[i]), 1);
        s[i].order = (int)i;
    }
    return s;
}

static css_element elem(const char *tag, const char *id,
                        const char *const *cls, size_t ncls) {
    css_element e = { 0 };
    e.tag = tag;
    e.id = id;
    e.classes = cls;
    e.nclasses = ncls;
    e.child_count = -1;
    return e;
}

static int has(const uint32_t *v, size_t n, uint32_t x) {
    for (size_t i = 0; i < n; ++i) if (v[i] == x) return 1;
    return 0;
}

static void test_buckets_and_order(void **state) {
    (void)state;
    const char *src[] = { ".a", "#b", "p", "*", "[x]", "div", ".z", "P", "p.a#b" };
    css_sel *s = parse_all(src, 9);
    cix_index idx;
    cix_build(s, 9, &idx);
    assert_int_equal(idx.valid, 1);
    const char *cls[] = { "a", "a" };
    css_element e = elem("p", NULL, cls, 2);
    uint32_t *buf = NULL;
    size_t cap = 0;
    size_t n = cix_candidates(&idx, &e, &buf, &cap);
    /* .a, p, *, [x], P -- not #b, div, .z, nor p.a#b (keyed by its id). */
    assert_int_equal(n, 5);
    const uint32_t want[] = { 0, 2, 3, 4, 7 };
    for (size_t i = 0; i < 5; ++i) assert_int_equal(buf[i], want[i]);
    free(buf);
    cix_free(&idx);
    free(s);
}

static void test_id_key(void **state) {
    (void)state;
    const char *src[] = { "div.a#b", ".a" };
    css_sel *s = parse_all(src, 2);
    cix_index idx;
    cix_build(s, 2, &idx);
    const char *cls[] = { "a" };
    css_element with = elem("div", "b", cls, 1);
    css_element without = elem("div", NULL, cls, 1);
    uint32_t *buf = NULL;
    size_t cap = 0;
    size_t n = cix_candidates(&idx, &with, &buf, &cap);
    assert_int_equal(n, 2);
    n = cix_candidates(&idx, &without, &buf, &cap);
    assert_int_equal(n, 1);
    assert_int_equal(buf[0], 1);
    free(buf);
    cix_free(&idx);
    free(s);
}

static void test_long_class_folds(void **state) {
    (void)state;
    char name[96];
    memset(name, 'q', 80);
    name[80] = '\0';
    char sel[100];
    snprintf(sel, sizeof sel, ".%s", name);
    const char *src[] = { sel };
    css_sel *s = parse_all(src, 1);
    cix_index idx;
    cix_build(s, 1, &idx);
    const char *cls[] = { name };
    css_element e = elem("div", NULL, cls, 1);
    assert_int_equal(csel_matches(&s[0], &e, NULL, 1, NULL), 1);
    uint32_t *buf = NULL;
    size_t cap = 0;
    assert_int_equal(cix_candidates(&idx, &e, &buf, &cap), 1);
    free(buf);
    cix_free(&idx);
    free(s);
}

/* The property that matters: every selector that matches is a candidate. */
static void test_matching_implies_candidate(void **state) {
    (void)state;
    const char *src[] = {
        "a", "A", ".x", ".y.x", "#i", "#I", "div#i.x", "*", ":root", "[href]",
        "ul > li", "li + li", ".x .y", ":not(.x)", ":is(.x,.y)", "p::before",
        ".y::after", "html", "li:first-child", "*.y", "span", "#i > .x",
    };
    size_t ns = sizeof src / sizeof *src;
    css_sel *s = parse_all(src, ns);
    cix_index idx;
    cix_build(s, ns, &idx);
    const char *c1[] = { "x" };
    const char *c2[] = { "y", "x" };
    const char *c3[] = { "y" };
    css_element root = elem("html", NULL, NULL, 0);
    css_element els[] = {
        elem("a", NULL, NULL, 0), elem("div", "i", c1, 1), elem("li", NULL, c2, 2),
        elem("p", "I", c3, 1), elem("span", NULL, NULL, 0), root,
    };
    uint32_t *buf = NULL;
    size_t cap = 0;
    for (size_t k = 0; k < sizeof els / sizeof *els; ++k) {
        if (k < 5) els[k].parent = &root;
        size_t n = cix_candidates(&idx, &els[k], &buf, &cap);
        assert_true(n != (size_t)-1);
        for (size_t i = 1; i < n; ++i) assert_true(buf[i - 1] < buf[i]);
        for (size_t i = 0; i < ns; ++i)
            if (csel_matches(&s[i], &els[k], NULL, 1, NULL))
                assert_true(has(buf, n, (uint32_t)i));
    }
    free(buf);
    cix_free(&idx);
    free(s);
}

static void test_invalid_index_reports_fallback(void **state) {
    (void)state;
    cix_index idx;
    memset(&idx, 0, sizeof idx);
    css_element e = elem("p", NULL, NULL, 0);
    uint32_t *buf = NULL;
    size_t cap = 0;
    assert_true(cix_candidates(&idx, &e, &buf, &cap) == (size_t)-1);
    cix_free(&idx);
    cix_free(&idx);
    free(buf);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_buckets_and_order),
        cmocka_unit_test(test_id_key),
        cmocka_unit_test(test_long_class_folds),
        cmocka_unit_test(test_matching_implies_candidate),
        cmocka_unit_test(test_invalid_index_reports_fallback),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
