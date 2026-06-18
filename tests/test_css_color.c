/*
 * test_css_color — CMocka suite for the pure CSS color parser.
 *
 * Covers hex (#rgb/#rgba/#rrggbb/#rrggbbaa), functional rgb()/rgba() with integer
 * and percentage components, the named-color table, case-insensitivity and
 * whitespace, the pack/unpack round trip, and the fail-closed edges (bad hex,
 * out-of-range channels, transparent, hsl(), junk, NULL).
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "css_color.h"

static cc_rgb C;

static void test_null_args(void **state) {
    (void)state;
    assert_int_equal(cc_parse(NULL, &C), CC_ERR_NULL_ARG);
    assert_int_equal(cc_parse("#fff", NULL), CC_ERR_NULL_ARG);
}

static void test_hex_short(void **state) {
    (void)state;
    assert_int_equal(cc_parse("#f00", &C), CC_OK);
    assert_int_equal(C.r, 0xff); assert_int_equal(C.g, 0x00); assert_int_equal(C.b, 0x00);

    assert_int_equal(cc_parse("#0F0", &C), CC_OK); /* case-insensitive */
    assert_int_equal(C.r, 0x00); assert_int_equal(C.g, 0xff); assert_int_equal(C.b, 0x00);
}

static void test_hex_short_alpha(void **state) {
    (void)state;
    /* #rgba: alpha validated then dropped, opaque result. */
    assert_int_equal(cc_parse("#1234", &C), CC_OK);
    assert_int_equal(C.r, 0x11); assert_int_equal(C.g, 0x22); assert_int_equal(C.b, 0x33);
}

static void test_hex_long(void **state) {
    (void)state;
    assert_int_equal(cc_parse("#11aaFF", &C), CC_OK);
    assert_int_equal(C.r, 0x11); assert_int_equal(C.g, 0xaa); assert_int_equal(C.b, 0xff);

    assert_int_equal(cc_parse("  #abcdef  ", &C), CC_OK); /* trimmed */
    assert_int_equal(C.r, 0xab); assert_int_equal(C.g, 0xcd); assert_int_equal(C.b, 0xef);
}

static void test_hex_long_alpha(void **state) {
    (void)state;
    assert_int_equal(cc_parse("#102030ff", &C), CC_OK);
    assert_int_equal(C.r, 0x10); assert_int_equal(C.g, 0x20); assert_int_equal(C.b, 0x30);
}

static void test_hex_bad(void **state) {
    (void)state;
    assert_int_equal(cc_parse("#12", &C), CC_ERR_SYNTAX);     /* wrong length */
    assert_int_equal(cc_parse("#ggg", &C), CC_ERR_SYNTAX);    /* non-hex digit */
    assert_int_equal(cc_parse("#1234567", &C), CC_ERR_SYNTAX);/* 7 digits */
    assert_int_equal(cc_parse("#", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("123456", &C), CC_ERR_SYNTAX);  /* missing # */
}

static void test_rgb_integer(void **state) {
    (void)state;
    assert_int_equal(cc_parse("rgb(255,0,128)", &C), CC_OK);
    assert_int_equal(C.r, 255); assert_int_equal(C.g, 0); assert_int_equal(C.b, 128);

    assert_int_equal(cc_parse("RGB( 16 , 32 , 48 )", &C), CC_OK); /* spaces + case */
    assert_int_equal(C.r, 16); assert_int_equal(C.g, 32); assert_int_equal(C.b, 48);
}

static void test_rgba_integer(void **state) {
    (void)state;
    /* alpha parsed then dropped */
    assert_int_equal(cc_parse("rgba(10, 20, 30, 0.5)", &C), CC_OK);
    assert_int_equal(C.r, 10); assert_int_equal(C.g, 20); assert_int_equal(C.b, 30);
}

static void test_rgb_percent(void **state) {
    (void)state;
    assert_int_equal(cc_parse("rgb(100%, 0%, 50%)", &C), CC_OK);
    assert_int_equal(C.r, 255); assert_int_equal(C.g, 0); assert_int_equal(C.b, 128);
}

static void test_rgb_out_of_range(void **state) {
    (void)state;
    assert_int_equal(cc_parse("rgb(256,0,0)", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("rgb(-1,0,0)", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("rgb(101%,0%,0%)", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("rgb(0,0)", &C), CC_ERR_SYNTAX);       /* too few */
    assert_int_equal(cc_parse("rgb(0,0,0,0,0)", &C), CC_ERR_SYNTAX); /* too many */
    assert_int_equal(cc_parse("rgb(0,0,0", &C), CC_ERR_SYNTAX);      /* unterminated */
}

static void test_named(void **state) {
    (void)state;
    assert_int_equal(cc_parse("red", &C), CC_OK);
    assert_int_equal(C.r, 255); assert_int_equal(C.g, 0); assert_int_equal(C.b, 0);

    assert_int_equal(cc_parse("White", &C), CC_OK);
    assert_int_equal(C.r, 255); assert_int_equal(C.g, 255); assert_int_equal(C.b, 255);

    assert_int_equal(cc_parse("BLACK", &C), CC_OK);
    assert_int_equal(C.r, 0); assert_int_equal(C.g, 0); assert_int_equal(C.b, 0);

    assert_int_equal(cc_parse("rebeccapurple", &C), CC_OK);
    assert_int_equal(C.r, 0x66); assert_int_equal(C.g, 0x33); assert_int_equal(C.b, 0x99);

    assert_int_equal(cc_parse("  cornflowerblue ", &C), CC_OK);
    assert_int_equal(C.r, 0x64); assert_int_equal(C.g, 0x95); assert_int_equal(C.b, 0xed);
}

static void test_named_bad(void **state) {
    (void)state;
    assert_int_equal(cc_parse("transparent", &C), CC_ERR_SYNTAX); /* invisible: fail closed */
    assert_int_equal(cc_parse("notacolor", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("reddish", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("   ", &C), CC_ERR_SYNTAX);
}

static void test_unsupported_syntax(void **state) {
    (void)state;
    assert_int_equal(cc_parse("hsl(0,100%,50%)", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("currentColor", &C), CC_ERR_SYNTAX);
    assert_int_equal(cc_parse("var(--x)", &C), CC_ERR_SYNTAX);
}

static void test_pack_unpack(void **state) {
    (void)state;
    cc_rgb a = { 0x12, 0x34, 0x56 };
    int p = cc_pack(a);
    assert_int_equal(p, 0x123456);
    assert_true(p >= 0);
    cc_rgb b = cc_unpack(p);
    assert_int_equal(b.r, a.r); assert_int_equal(b.g, a.g); assert_int_equal(b.b, a.b);

    /* High bits ignored by unpack. */
    cc_rgb c = cc_unpack((int)0x7fabcdef);
    assert_int_equal(c.r, 0xab); assert_int_equal(c.g, 0xcd); assert_int_equal(c.b, 0xef);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_null_args),
        cmocka_unit_test(test_hex_short),
        cmocka_unit_test(test_hex_short_alpha),
        cmocka_unit_test(test_hex_long),
        cmocka_unit_test(test_hex_long_alpha),
        cmocka_unit_test(test_hex_bad),
        cmocka_unit_test(test_rgb_integer),
        cmocka_unit_test(test_rgba_integer),
        cmocka_unit_test(test_rgb_percent),
        cmocka_unit_test(test_rgb_out_of_range),
        cmocka_unit_test(test_named),
        cmocka_unit_test(test_named_bad),
        cmocka_unit_test(test_unsupported_syntax),
        cmocka_unit_test(test_pack_unpack),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
