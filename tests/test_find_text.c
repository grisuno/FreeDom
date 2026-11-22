/* Suite for find_text (spec/find_text.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>

#include "find_text.h"

static size_t run(const ft_piece *p, size_t n, const char *q, ft_match *m, size_t cap,
                  int *trunc) {
    uint32_t qc[FT_QUERY_MAX];
    size_t qn = ft_compile(q, strlen(q), qc, FT_QUERY_MAX);
    size_t nm = 99;
    assert_int_equal(ft_search(p, n, qc, qn, m, cap, &nm, trunc), FT_OK);
    return nm;
}

static void test_across_gap(void **state) {
    (void)state;
    ft_piece p[] = { { "Hello", 5, 0 }, { "world", 5, 1 } };
    ft_match m[4];
    assert_int_equal(run(p, 2, "hello WORLD", m, 4, NULL), 1);
    assert_int_equal(m[0].start.piece, 0);
    assert_int_equal(m[0].start.off, 0);
    assert_int_equal(m[0].end.piece, 1);
    assert_int_equal(m[0].end.off, 5);
    assert_int_equal(run(p, 2, "helloworld", m, 4, NULL), 0);
}

static void test_across_pieces_without_gap(void **state) {
    (void)state;
    ft_piece p[] = { { "Hel", 3, 0 }, { "lo", 2, 0 } };
    ft_match m[4];
    assert_int_equal(run(p, 2, "hello", m, 4, NULL), 1);
    assert_int_equal(m[0].start.piece, 0);
    assert_int_equal(m[0].end.piece, 1);
    assert_int_equal(m[0].end.off, 2);
    assert_int_equal(run(p, 2, "hel lo", m, 4, NULL), 0);
}

static void test_diacritics_and_case(void **state) {
    (void)state;
    const char *t = "El Ni\xc3\xb1o R\xc3\x89SUM\xc3\xa9 \xd0\x9c\xd0\xb8\xd1\x80";
    ft_piece p[] = { { t, strlen(t), 0 } };
    ft_match m[4];
    assert_int_equal(run(p, 1, "nino resume", m, 4, NULL), 1);
    assert_int_equal(m[0].start.off, 3);
    assert_int_equal(run(p, 1, "\xd0\xbc\xd0\x98\xd0\xa0", m, 4, NULL), 1);
    assert_int_equal(ft_fold('A'), 'a');
    assert_int_equal(ft_fold(0xC9), 'e');
    assert_int_equal(ft_fold(0x0141), 'l');
    assert_int_equal(ft_fold(0x0393), 0x03B3);
    assert_int_equal(ft_fold(0x0401), 0x0451);
    assert_int_equal(ft_fold(0xDF), 0xDF);
}

static void test_whitespace_runs(void **state) {
    (void)state;
    const char *t = "a \t\n b\xc2\xa0" "c";
    ft_piece p[] = { { t, strlen(t), 0 } };
    ft_match m[4];
    assert_int_equal(run(p, 1, "  A   B c ", m, 4, NULL), 1);
    assert_int_equal(m[0].start.off, 0);
    assert_int_equal(m[0].end.off, strlen(t));
    uint32_t qc[8];
    assert_int_equal(ft_compile("   ", 3, qc, 8), 0);
    assert_int_equal(run(p, 1, "", m, 4, NULL), 0);
}

static void test_non_overlapping_and_cap(void **state) {
    (void)state;
    ft_piece p[] = { { "aaaaa", 5, 0 } };
    ft_match m[4];
    int trunc = -1;
    assert_int_equal(run(p, 1, "aa", m, 4, &trunc), 2);
    assert_int_equal(trunc, 0);
    assert_int_equal(m[1].start.off, 2);
    assert_int_equal(run(p, 1, "a", m, 3, &trunc), 3);
    assert_int_equal(trunc, 1);
}

static void test_match_never_starts_on_space(void **state) {
    (void)state;
    ft_piece p[] = { { "x  y", 4, 0 } };
    ft_match m[4];
    assert_int_equal(run(p, 1, "y", m, 4, NULL), 1);
    assert_int_equal(m[0].start.off, 3);
}

static void test_invalid_utf8_bounded(void **state) {
    (void)state;
    const char t[] = { '\xff', '\xfe', 'a', '\xc3' };
    ft_piece p[] = { { t, sizeof t, 0 }, { "\xe2\x82", 2, 0 } };
    ft_match m[4];
    assert_int_equal(run(p, 2, "a", m, 4, NULL), 1);
    assert_int_equal(m[0].start.off, 2);
    assert_int_equal(run(p, 2, "\xef\xbf\xbd", m, 4, NULL), 0);
}

static void test_spans(void **state) {
    (void)state;
    ft_piece p[] = { { "foo", 3, 0 }, { "bar", 3, 1 }, { "baz", 3, 1 }, { "foo", 3, 1 } };
    ft_match m[4];
    assert_int_equal(run(p, 4, "o bar b", m, 4, NULL), 1);
    ft_span s[8];
    size_t ns = ft_spans(p, 4, m, 1, s, 8);
    assert_int_equal(ns, 3);
    assert_int_equal(s[0].piece, 0); assert_int_equal(s[0].start, 2); assert_int_equal(s[0].end, 3);
    assert_int_equal(s[1].piece, 1); assert_int_equal(s[1].start, 0); assert_int_equal(s[1].end, 3);
    assert_int_equal(s[2].piece, 2); assert_int_equal(s[2].start, 0); assert_int_equal(s[2].end, 1);
    assert_int_equal(ft_spans(p, 4, m, 1, s, 2), 2);
    /* a match ending exactly at a piece end does not leave an empty span in the next */
    assert_int_equal(run(p, 4, "foo", m, 4, NULL), 2);
    assert_int_equal(ft_spans(p, 4, m, 2, s, 8), 2);
    assert_int_equal(s[1].match, 1);
    assert_int_equal(s[1].piece, 3);
}

static void test_step(void **state) {
    (void)state;
    assert_int_equal(ft_step(0, 0, 1), -1);
    assert_int_equal(ft_step(2, 3, 1), 0);
    assert_int_equal(ft_step(0, 3, -1), 2);
    assert_int_equal(ft_step(-1, 3, 1), 0);
    assert_int_equal(ft_step(-1, 3, -1), 2);
    assert_int_equal(ft_step(7, 3, 1), 0);
}

static void test_rejects_bad_input(void **state) {
    (void)state;
    uint32_t q[1] = { 'a' };
    ft_match m[1];
    size_t n = 5;
    assert_int_equal(ft_search(NULL, 1, q, 1, m, 1, &n, NULL), FT_EINVAL);
    assert_int_equal(n, 5);
    ft_piece p[] = { { "a", 1, 0 } };
    assert_int_equal(ft_search(p, 1, q, 1, NULL, 1, &n, NULL), FT_EINVAL);
    assert_int_equal(ft_search(p, 1, q, 1, m, 1, NULL, NULL), FT_EINVAL);
    assert_int_equal(ft_search(p, 1, NULL, 1, m, 1, &n, NULL), FT_EINVAL);
    assert_int_equal(ft_compile(NULL, 3, q, 1), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_across_gap),
        cmocka_unit_test(test_across_pieces_without_gap),
        cmocka_unit_test(test_diacritics_and_case),
        cmocka_unit_test(test_whitespace_runs),
        cmocka_unit_test(test_non_overlapping_and_cap),
        cmocka_unit_test(test_match_never_starts_on_space),
        cmocka_unit_test(test_invalid_utf8_bounded),
        cmocka_unit_test(test_spans),
        cmocka_unit_test(test_step),
        cmocka_unit_test(test_rejects_bad_input),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
