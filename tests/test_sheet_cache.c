/* Suite for sheet_cache (spec/sheet_cache.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freedom_config.h"

#include "sheet_cache.h"

static const char CSS_RED[]  = "p{color:#ff0000}";
static const char CSS_BLUE[] = "p{color:#0000ff}";
static const char CSS_MEDIA[] = "p{color:#ff0000}@media (min-width:1000px){p{color:#00ff00}}";
static const char CSS_ATTR_VAR[] = "[data-t=dark]{--c:#112233}p{color:var(--c)}";
static const char CSS_HAS_VAR[]  = "html:has(.x){--c:#112233}p{color:var(--c)}";

static int p_color(const shc_sheet *s) {
    return css_resolve(shc_css(s), "p", NULL, NULL, 0, NULL, 0).color;
}

static shc_key key_of(const char *text, const css_media *m) {
    shc_key k = { text, strlen(text), m, NULL };
    return k;
}

static shc_stats stats_of(const shc_cache *c) {
    shc_stats st;
    shc_stats_get(c, &st);
    return st;
}

typedef struct matcher_log { int calls; int answer; } matcher_log;

static int log_match(void *ctx, const struct css_sel *sel) {
    (void)sel;
    matcher_log *l = (matcher_log *)ctx;
    ++l->calls;
    return l->answer;
}

static void test_same_key_is_a_hit_and_returns_the_same_sheet(void **state) {
    (void)state;
    shc_cache *c = shc_new(0);
    assert_non_null(c);
    shc_key k = key_of(CSS_RED, NULL);
    shc_sheet *a = shc_acquire(c, &k);
    char copy[sizeof CSS_RED];
    memcpy(copy, CSS_RED, sizeof copy);
    shc_key k2 = key_of(copy, NULL);
    shc_sheet *b = shc_acquire(c, &k2);
    assert_non_null(a);
    assert_ptr_equal(a, b);
    assert_ptr_equal(shc_css(a), shc_css(b));
    assert_int_equal(p_color(b), 0xff0000);
    assert_int_equal((int)stats_of(c).hits, 1);
    assert_int_equal((int)stats_of(c).misses, 1);
    shc_release(a);
    shc_release(b);
    shc_free(c);
}

static void test_one_byte_of_text_changes_the_result(void **state) {
    (void)state;
    shc_cache *c = shc_new(0);
    shc_key k1 = key_of(CSS_RED, NULL), k2 = key_of(CSS_BLUE, NULL);
    assert_int_equal(strlen(CSS_RED), strlen(CSS_BLUE));
    shc_sheet *a = shc_acquire(c, &k1);
    shc_sheet *b = shc_acquire(c, &k2);
    assert_int_equal(p_color(a), 0xff0000);
    assert_int_equal(p_color(b), 0x0000ff);
    assert_int_equal((int)stats_of(c).hits, 0);
    shc_release(a);
    shc_release(b);
    shc_free(c);
}

static void test_media_inputs_are_part_of_the_key(void **state) {
    (void)state;
    shc_cache *c = shc_new(0);
    css_media wide = { 0, 0, 1200, NULL, NULL }, narrow = { 0, 0, 800, NULL, NULL };
    css_media dark = { 1, 0, 1200, NULL, NULL }, print = { 0, 1, 1200, NULL, NULL };
    shc_key kw = key_of(CSS_MEDIA, &wide), kn = key_of(CSS_MEDIA, &narrow);
    shc_key kd = key_of(CSS_MEDIA, &dark), kp = key_of(CSS_MEDIA, &print);
    shc_key k0 = key_of(CSS_MEDIA, NULL);
    shc_sheet *a = shc_acquire(c, &kw);
    shc_sheet *b = shc_acquire(c, &kn);
    assert_int_equal(p_color(a), 0x00ff00);
    assert_int_equal(p_color(b), 0xff0000);
    shc_sheet *d = shc_acquire(c, &kw);
    shc_sheet *e = shc_acquire(c, &kd);
    shc_sheet *f = shc_acquire(c, &kw);
    shc_sheet *g = shc_acquire(c, &kp);
    shc_sheet *h = shc_acquire(c, &kw);
    shc_sheet *i = shc_acquire(c, &k0);
    assert_int_equal((int)stats_of(c).hits, 0);
    shc_sheet *j = shc_acquire(c, &k0);
    assert_int_equal((int)stats_of(c).hits, 1);
    shc_sheet *all[] = { a, b, d, e, f, g, h, i, j };
    for (size_t n = 0; n < sizeof all / sizeof all[0]; ++n) shc_release(all[n]);
    shc_free(c);
}

static void test_root_scope_is_part_of_the_key(void **state) {
    (void)state;
    shc_cache *c = shc_new(0);
    shc_key k = key_of(CSS_RED, NULL);
    shc_sheet *s[8];
    size_t n = 0;
    s[n++] = shc_acquire(c, &k);
    k.root_scope = "";            s[n++] = shc_acquire(c, &k);
    k.root_scope = "dark";        s[n++] = shc_acquire(c, &k);
    k.root_scope = "light";       s[n++] = shc_acquire(c, &k);
    assert_int_equal((int)stats_of(c).hits, 0);
    s[n++] = shc_acquire(c, &k);
    assert_int_equal((int)stats_of(c).hits, 1);
    for (size_t i = 0; i < n; ++i) { assert_non_null(s[i]); shc_release(s[i]); }
    shc_free(c);
}

/* The matcher is the parse's only window on the live DOM: a hit needs the SAME answers. */
static void test_a_hit_replays_the_matcher_and_needs_the_same_answers(void **state) {
    (void)state;
    shc_cache *c = shc_new(0);
    matcher_log log = { 0, 1 };
    css_media m = { 0, 0, 1200, log_match, &log };
    shc_key k = key_of(CSS_ATTR_VAR, &m);
    shc_sheet *a = shc_acquire(c, &k);
    int asked = log.calls;
    assert_true(asked > 0);
    assert_int_equal(p_color(a), 0x112233);
    shc_sheet *b = shc_acquire(c, &k);
    assert_ptr_equal(a, b);
    assert_int_equal(log.calls, 2 * asked);          /* replayed, not re-parsed */
    assert_int_equal((int)stats_of(c).hits, 1);
    log.answer = 0;                                  /* the root lost the attribute */
    shc_sheet *d = shc_acquire(c, &k);
    assert_ptr_not_equal(a, d);
    assert_int_not_equal(p_color(d), 0x112233);
    log.answer = 1;                                  /* ...and got it back */
    shc_sheet *e = shc_acquire(c, &k);
    assert_ptr_not_equal(d, e);
    assert_int_equal(p_color(e), 0x112233);
    assert_int_equal((int)stats_of(c).hits, 1);
    shc_release(a);
    shc_release(b);
    shc_release(d);
    shc_release(e);
    shc_free(c);
}

/* A structure-dependent root selector is covered by the same replay. */
static void test_structural_root_selector_is_replayed_too(void **state) {
    (void)state;
    shc_cache *c = shc_new(0);
    matcher_log log = { 0, 1 };
    css_media m = { 0, 0, 1200, log_match, &log };
    shc_key k = key_of(CSS_HAS_VAR, &m);
    shc_sheet *a = shc_acquire(c, &k);
    assert_true(log.calls > 0);
    shc_sheet *b = shc_acquire(c, &k);
    assert_ptr_equal(a, b);
    log.answer = 0;
    shc_sheet *d = shc_acquire(c, &k);
    assert_ptr_not_equal(a, d);
    assert_int_not_equal(p_color(d), 0x112233);
    shc_release(a);
    shc_release(b);
    shc_release(d);
    shc_free(c);
}

static void test_matcher_presence_is_part_of_the_key(void **state) {
    (void)state;
    shc_cache *c = shc_new(0);
    matcher_log log = { 0, 0 };
    css_media with = { 0, 0, 1200, log_match, &log }, without = { 0, 0, 1200, NULL, NULL };
    shc_key kw = key_of(CSS_RED, &with), ko = key_of(CSS_RED, &without);
    shc_sheet *a = shc_acquire(c, &kw);
    shc_sheet *b = shc_acquire(c, &ko);
    assert_ptr_not_equal(a, b);
    assert_int_equal((int)stats_of(c).hits, 0);
    shc_release(a);
    shc_release(b);
    shc_free(c);
}

/* More questions than the module records: parsed correctly, never reused. */
static void test_too_many_matcher_questions_are_never_reused(void **state) {
    (void)state;
    size_t rules = (size_t)FC_SHC_MAX_QUERIES + 8;
    size_t cap = rules * 40 + 64, n = 0;
    char *css = (char *)malloc(cap);
    assert_non_null(css);
    for (size_t i = 0; i < rules; ++i)
        n += (size_t)snprintf(css + n, cap - n, "[data-k%zu]{--v%zu:1}", i, i);
    n += (size_t)snprintf(css + n, cap - n, "[data-t]{--c:#112233}p{color:var(--c)}");
    shc_cache *c = shc_new(0);
    matcher_log log = { 0, 1 };
    css_media m = { 0, 0, 1200, log_match, &log };
    shc_key k = { css, n, &m, NULL };
    shc_sheet *a = shc_acquire(c, &k);
    if (log.calls <= (int)FC_SHC_MAX_QUERIES) {
        /* The parser bounds its own custom-property rules below our cap: nothing to test. */
        shc_release(a);
        shc_free(c);
        free(css);
        skip();
    }
    shc_sheet *b = shc_acquire(c, &k);
    assert_ptr_not_equal(a, b);
    assert_int_equal((int)stats_of(c).hits, 0);
    assert_int_equal((int)stats_of(c).bypasses, 2);
    shc_release(a);
    shc_release(b);
    shc_free(c);
    free(css);
}

static void test_a_bypassed_parse_does_not_evict_the_retained_entry(void **state) {
    (void)state;
    shc_cache *c = shc_new(strlen(CSS_RED));
    shc_key small = key_of(CSS_RED, NULL), big = key_of(CSS_MEDIA, NULL);
    shc_sheet *a = shc_acquire(c, &small);
    shc_sheet *v = shc_acquire(c, &big);
    shc_sheet *b = shc_acquire(c, &small);
    assert_ptr_equal(a, b);
    assert_ptr_not_equal(a, v);
    shc_release(a);
    shc_release(v);
    shc_release(b);
    shc_free(c);
}

static void test_oversized_text_is_parsed_but_not_retained(void **state) {
    (void)state;
    shc_cache *c = shc_new(strlen(CSS_RED) - 1);
    shc_key k = key_of(CSS_RED, NULL);
    shc_sheet *a = shc_acquire(c, &k);
    shc_sheet *b = shc_acquire(c, &k);
    assert_ptr_not_equal(a, b);
    assert_int_equal(p_color(a), 0xff0000);
    assert_int_equal(p_color(b), 0xff0000);
    assert_int_equal((int)stats_of(c).bypasses, 2);
    shc_release(a);
    shc_release(b);
    shc_free(c);
}

static void test_a_reference_outlives_replacement_and_the_cache(void **state) {
    (void)state;
    shc_cache *c = shc_new(0);
    shc_key k1 = key_of(CSS_RED, NULL), k2 = key_of(CSS_BLUE, NULL);
    shc_sheet *a = shc_acquire(c, &k1);
    shc_sheet *b = shc_acquire(c, &k2);
    assert_int_equal(p_color(a), 0xff0000);
    shc_free(c);
    assert_int_equal(p_color(a), 0xff0000);
    assert_int_equal(p_color(b), 0x0000ff);
    shc_release(a);
    shc_release(b);
}

static void test_no_cache_parses_without_retaining(void **state) {
    (void)state;
    shc_key k = key_of(CSS_RED, NULL);
    shc_sheet *a = shc_acquire(NULL, &k);
    shc_sheet *b = shc_acquire(NULL, &k);
    assert_non_null(a);
    assert_ptr_not_equal(a, b);
    assert_int_equal(p_color(a), 0xff0000);
    shc_release(a);
    shc_release(b);
}

static void test_fails_closed_on_bad_arguments(void **state) {
    (void)state;
    shc_cache *c = shc_new(0);
    shc_key k = { NULL, 3, NULL, NULL };
    assert_null(shc_acquire(c, NULL));
    assert_null(shc_acquire(c, &k));
    k.text = CSS_RED; k.len = SIZE_MAX;
    assert_null(shc_acquire(c, &k));
    shc_key empty = { NULL, 0, NULL, NULL };
    shc_sheet *e = shc_acquire(c, &empty);
    assert_non_null(e);
    shc_sheet *e2 = shc_acquire(c, &empty);
    assert_ptr_equal(e, e2);
    shc_release(e);
    shc_release(e2);
    shc_release(NULL);
    assert_null(shc_css(NULL));
    shc_stats st = { 9, 9, 9 };
    shc_stats_get(NULL, &st);
    assert_int_equal((int)(st.hits + st.misses + st.bypasses), 0);
    shc_free(c);
    shc_free(NULL);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_same_key_is_a_hit_and_returns_the_same_sheet),
        cmocka_unit_test(test_one_byte_of_text_changes_the_result),
        cmocka_unit_test(test_media_inputs_are_part_of_the_key),
        cmocka_unit_test(test_root_scope_is_part_of_the_key),
        cmocka_unit_test(test_a_hit_replays_the_matcher_and_needs_the_same_answers),
        cmocka_unit_test(test_structural_root_selector_is_replayed_too),
        cmocka_unit_test(test_matcher_presence_is_part_of_the_key),
        cmocka_unit_test(test_too_many_matcher_questions_are_never_reused),
        cmocka_unit_test(test_a_bypassed_parse_does_not_evict_the_retained_entry),
        cmocka_unit_test(test_oversized_text_is_parsed_but_not_retained),
        cmocka_unit_test(test_a_reference_outlives_replacement_and_the_cache),
        cmocka_unit_test(test_no_cache_parses_without_retaining),
        cmocka_unit_test(test_fails_closed_on_bad_arguments),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
