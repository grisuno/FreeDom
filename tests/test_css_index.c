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

/* --- ancestor filter (spec/css_index.md "Filtro de ancestros") ---------------------------------
 * A selector with ancestor requirements (`.card a`, `nav > ul li`) is rejected WITHOUT being
 * evaluated when the element's ancestors lack a required tag/id/class. The filter only ever says
 * "cannot match": it must never reject a selector that does match. */

static css_element with_bloom(css_element e, const css_element *const *ancestors, size_t n) {
    uint64_t acc = 0;
    for (size_t i = 0; i < n; ++i) acc |= csel_element_feature_bits(ancestors[i]);
    e.anc_bloom = acc;
    e.own_bloom = csel_element_feature_bits(&e);
    e.anc_bloom_valid = 1;
    return e;
}

static void test_anc_filter_rejects_when_a_required_ancestor_is_absent(void **state) {
    (void)state;
    const char *src[] = { "div a", ".card a", "#hdr a", "ul > li a", "a" };
    css_sel *s = parse_all(src, 5);
    const char *card[] = { "card" };
    css_element div_card = elem("div", NULL, card, 1);
    css_element ul = elem("ul", NULL, NULL, 0);
    css_element li = elem("li", NULL, NULL, 0);
    const css_element *anc_all[] = { &div_card, &ul, &li };
    css_element a_in = with_bloom(elem("a", NULL, NULL, 0), anc_all, 3);
    for (size_t i = 0; i < 5; ++i) assert_false(csel_anc_reject(&s[i], &a_in));   /* ids aside, all can match */
    css_element span = elem("span", NULL, NULL, 0);
    const css_element *anc_span[] = { &span };
    css_element a_out = with_bloom(elem("a", NULL, NULL, 0), anc_span, 1);
    assert_true(csel_anc_reject(&s[0], &a_out));      /* needs a div ancestor */
    assert_true(csel_anc_reject(&s[1], &a_out));      /* needs .card */
    assert_true(csel_anc_reject(&s[3], &a_out));      /* needs ul and li */
    assert_false(csel_anc_reject(&s[4], &a_out));     /* no ancestor requirement */
    free(s);
}

static void test_anc_filter_is_off_without_a_bloom_and_ignores_sibling_combinators(void **state) {
    (void)state;
    const char *src[] = { "div a", "h2 + a", "section h2 + a" };
    css_sel *s = parse_all(src, 3);
    css_element bare = elem("a", NULL, NULL, 0);        /* anc_bloom_valid == 0: never rejects */
    assert_false(csel_anc_reject(&s[0], &bare));
    css_element span = elem("span", NULL, NULL, 0);
    const css_element *anc[] = { &span };
    css_element a = with_bloom(elem("a", NULL, NULL, 0), anc, 1);
    assert_false(csel_anc_reject(&s[1], &a));           /* `h2` is a SIBLING of a, not an ancestor */
    assert_false(csel_anc_reject(&s[2], &a));           /* stops at the first + : not provably absent */
    free(s);
}

static void test_anc_filter_long_class_names_fold_the_same_way(void **state) {
    (void)state;
    char longcls[96], sel[128];
    memset(longcls, 'x', sizeof longcls - 1);
    longcls[sizeof longcls - 1] = '\0';
    snprintf(sel, sizeof sel, ".%s a", longcls);
    css_sel s;
    assert_int_equal(csel_parse(sel, 0, strlen(sel), &s), 1);
    const char *cls[] = { longcls };
    css_element host = elem("div", NULL, cls, 1);
    const css_element *anc[] = { &host };
    css_element a = with_bloom(elem("a", NULL, NULL, 0), anc, 1);
    assert_false(csel_anc_reject(&s, &a));              /* the folded names agree: it can match */
}

static void test_anc_filter_never_rejects_a_matching_selector(void **state) {
    (void)state;
    const char *src[] = { ".a .b .c", "div > .b p", "#x p", "body *" , "ul li:first-child p" };
    css_sel *s = parse_all(src, 5);
    const char *ca[] = { "a" }, *cb[] = { "b" }, *cc[] = { "c" };
    css_element body = elem("body", NULL, NULL, 0);
    css_element ea = elem("div", "x", ca, 1);
    css_element eb = elem("div", NULL, cb, 1);
    css_element ul = elem("ul", NULL, NULL, 0);
    css_element li = elem("li", NULL, NULL, 0);
    css_element span = elem("span", NULL, NULL, 0);
    const css_element *anc[] = { &body, &ea, &eb, &ul, &li, &span };
    css_element c = with_bloom(elem("p", NULL, cc, 1), anc, 6);   /* every selector above matches this <p class=c> */
    for (size_t i = 0; i < 5; ++i) assert_false(csel_anc_reject(&s[i], &c));
    free(s);
}

static void test_anc_filter_also_checks_the_subjects_own_tag_id_and_classes(void **state) {
    (void)state;
    const char *src[] = { ".a.b", "p.a", "#i.a", "div" , ".a" };
    css_sel *s = parse_all(src, 5);
    const char *only_a[] = { "a" }, *ab[] = { "a", "b" };
    css_element p_a = with_bloom(elem("p", NULL, only_a, 1), NULL, 0);
    assert_true(csel_anc_reject(&s[0], &p_a));       /* lacks .b */
    assert_false(csel_anc_reject(&s[1], &p_a));      /* p.a */
    assert_true(csel_anc_reject(&s[2], &p_a));       /* lacks #i */
    assert_true(csel_anc_reject(&s[3], &p_a));       /* not a div */
    assert_false(csel_anc_reject(&s[4], &p_a));
    css_element div_ab = with_bloom(elem("div", "i", ab, 2), NULL, 0);
    for (size_t i = 0; i < 5; ++i)
        if (i == 1) assert_true(csel_anc_reject(&s[i], &div_ab));   /* p.a vs a div */
        else assert_false(csel_anc_reject(&s[i], &div_ab));
    free(s);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_buckets_and_order),
        cmocka_unit_test(test_id_key),
        cmocka_unit_test(test_long_class_folds),
        cmocka_unit_test(test_matching_implies_candidate),
        cmocka_unit_test(test_invalid_index_reports_fallback),
        cmocka_unit_test(test_anc_filter_rejects_when_a_required_ancestor_is_absent),
        cmocka_unit_test(test_anc_filter_is_off_without_a_bloom_and_ignores_sibling_combinators),
        cmocka_unit_test(test_anc_filter_long_class_names_fold_the_same_way),
        cmocka_unit_test(test_anc_filter_never_rejects_a_matching_selector),
        cmocka_unit_test(test_anc_filter_also_checks_the_subjects_own_tag_id_and_classes),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
