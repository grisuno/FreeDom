#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "text_case.h"
#include "css.h"

static void test_upper_lower_ascii_latin(void **state) {
    (void)state;
    assert_int_equal(tc_upper('a'), 'A');
    assert_int_equal(tc_upper('Z'), 'Z');
    assert_int_equal(tc_lower('Q'), 'q');
    assert_int_equal(tc_upper(0x00E9), 0x00C9);   /* e acute */
    assert_int_equal(tc_lower(0x00D1), 0x00F1);   /* N tilde */
    assert_int_equal(tc_upper(0x00F7), 0x00F7);   /* division sign */
    assert_int_equal(tc_upper(0x00DF), 0x00DF);   /* sharp s stays */
    assert_int_equal(tc_upper(0x0101), 0x0100);   /* a macron */
    assert_int_equal(tc_upper(0x017E), 0x017D);   /* z caron */
    assert_int_equal(tc_upper(0x03B1), 0x0391);   /* alpha */
    assert_int_equal(tc_upper(0x03C2), 0x03A3);   /* final sigma */
    assert_int_equal(tc_upper(0x0436), 0x0416);   /* zhe */
    assert_int_equal(tc_upper(0x0451), 0x0401);   /* io */
    assert_int_equal(tc_lower(0x0416), 0x0436);
    assert_int_equal(tc_upper(0x00FF), 0x0178);   /* y diaeresis: 2 bytes both */
    assert_int_equal(tc_upper(0x4E2D), 0x4E2D);   /* CJK: identity */
    assert_true(tc_is_lower('m'));
    assert_false(tc_is_lower('M'));
    assert_false(tc_is_lower('1'));
}

static void test_transform_keeps_length(void **state) {
    (void)state;
    char out[64];
    const char *s = "\xC3\xA9t\xC3\xA9 stra\xC3\x9F" "e";   /* "été straße" */
    size_t n = strlen(s);
    assert_int_equal(tc_transform(s, n, CSS_TT_UPPERCASE, 1, out, sizeof out), n);
    assert_memory_equal(out, "\xC3\x89T\xC3\x89 STRA\xC3\x9F" "E", n);
    assert_int_equal(tc_transform("hello world", 11, CSS_TT_CAPITALIZE, 1, out, sizeof out), 11);
    assert_memory_equal(out, "Hello World", 11);
    assert_int_equal(tc_transform("ello", 4, CSS_TT_CAPITALIZE, 0, out, sizeof out), 4);
    assert_memory_equal(out, "ello", 4);
    assert_int_equal(tc_transform("ABC", 3, CSS_TT_LOWERCASE, 1, out, sizeof out), 3);
    assert_memory_equal(out, "abc", 3);
    memcpy(out, "zz", 2);
    assert_int_equal(tc_transform("abc", 3, CSS_TT_UPPERCASE, 1, out, 2), 0);
    assert_memory_equal(out, "zz", 2);
    assert_int_equal(tc_transform(NULL, 3, CSS_TT_UPPERCASE, 1, out, 8), 0);
    /* A truncated multi-byte sequence is copied untouched. */
    assert_int_equal(tc_transform("a\xC3", 2, CSS_TT_UPPERCASE, 1, out, 8), 2);
    assert_memory_equal(out, "A\xC3", 2);
}

static void test_smallcaps_runs(void **state) {
    (void)state;
    tc_run r[8];
    assert_int_equal(tc_smallcaps_runs("Small", 5, r, 8), 2);
    assert_int_equal(r[0].off, 0); assert_int_equal(r[0].len, 1); assert_int_equal(r[0].lowered, 0);
    assert_int_equal(r[1].off, 1); assert_int_equal(r[1].len, 4); assert_int_equal(r[1].lowered, 1);
    assert_int_equal(tc_smallcaps_runs("a1b", 3, r, 8), 3);
    assert_int_equal(r[0].lowered, 1); assert_int_equal(r[1].lowered, 0); assert_int_equal(r[2].lowered, 1);
    /* UTF-8 lowercase counts as lowercase; runs end on code point boundaries. */
    assert_int_equal(tc_smallcaps_runs("A\xC3\xA9", 3, r, 8), 2);
    assert_int_equal(r[1].off, 1); assert_int_equal(r[1].len, 2); assert_int_equal(r[1].lowered, 1);
    /* Too few slots: the last run absorbs the rest, nothing is lost. */
    assert_int_equal(tc_smallcaps_runs("aBcD", 4, r, 2), 2);
    assert_int_equal(r[1].off, 1); assert_int_equal(r[1].len, 3);
    assert_int_equal(tc_smallcaps_runs("", 0, r, 8), 0);
    assert_int_equal(tc_smallcaps_runs("x", 1, r, 0), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_upper_lower_ascii_latin),
        cmocka_unit_test(test_transform_keeps_length),
        cmocka_unit_test(test_smallcaps_runs),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
