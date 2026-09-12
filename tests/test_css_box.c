#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "css_box.h"
#include "css_decl.h"

static void test_interp_len_px(void **state)
{
    (void)state;
    int out = -999;
    assert_int_equal(cb_interp_len("12px", CB_AUTO_REJECT, &out), 1);
    assert_int_equal(out, 12);
}

static void test_interp_len_auto_reject(void **state)
{
    (void)state;
    int out = 0;
    assert_int_equal(cb_interp_len("auto", CB_AUTO_REJECT, &out), 0);
    assert_int_equal(cb_interp_len("auto", CB_AUTO_VALUE, &out), 1);
    assert_int_equal(out, CSS_LEN_AUTO);
}

static void test_interp_len_bare_number_rejected(void **state)
{
    (void)state;
    int out = 0;
    assert_int_equal(cb_interp_len("12", CB_AUTO_REJECT, &out), 0);
    assert_int_equal(cb_interp_len("0", CB_AUTO_REJECT, &out), 1);
}

static void test_emit_len_claims_both_halves(void **state)
{
    (void)state;
    css_decl d[4];
    int n = cb_emit_len(d, 4, P_WIDTH, "200px", CB_AUTO_RESET, 0);
    assert_true(n >= 1);
    assert_int_equal(d[0].prop, P_WIDTH);
    assert_int_equal(d[0].ival, 200);
}

static void test_box4_partial_fails_closed(void **state)
{
    (void)state;
    css_decl d[16];
    assert_int_equal(cb_expand_box4("1px 2px 3px 4px 5px", P_MARGIN_TOP, 0, 1, d, 16), 0);
    assert_true(cb_expand_box4("1px 2px", P_MARGIN_TOP, 0, 1, d, 16) > 0);
}

static void test_align_display_gap(void **state)
{
    (void)state;
    assert_int_equal(cb_interp_align("center"), CSS_ALIGN_CENTER);
    assert_int_equal(cb_interp_align("bogus"), -1);
    assert_true(cb_interp_display("flex") > 0);
    assert_int_equal(cb_interp_display("bogus"), -1);
    assert_int_equal(cb_interp_gap("normal"), 0);
    assert_true(cb_interp_justify("space-between") > 0);
}

static void test_grid_repeat_autofill_dropped(void **state)
{
    (void)state;
    assert_int_equal(cb_interp_gridcols("repeat(auto-fill, 1fr)"), -1);
    assert_true(cb_interp_gridcols("1fr 1fr") >= 2);
}

static void test_fit_content_trim(void **state)
{
    (void)state;
    css_decl d[8];
    int n = cb_emit_len(d, 8, P_WIDTH, "fit-content(200px)", CB_AUTO_RESET, 0);
    assert_true(n >= 1);
    assert_int_equal(d[0].prop, P_WIDTH);
    assert_int_equal(d[0].ival, 200);
    n = cb_emit_len(d, 8, P_WIDTH, "fit-content(  200px  )", CB_AUTO_RESET, 0);
    assert_true(n >= 1);
    assert_int_equal(d[0].ival, 200);
    assert_int_equal(cb_emit_len(d, 8, P_WIDTH, "fit-content()", CB_AUTO_RESET, 0), 0);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_interp_len_px),
        cmocka_unit_test(test_interp_len_auto_reject),
        cmocka_unit_test(test_interp_len_bare_number_rejected),
        cmocka_unit_test(test_emit_len_claims_both_halves),
        cmocka_unit_test(test_box4_partial_fails_closed),
        cmocka_unit_test(test_align_display_gap),
        cmocka_unit_test(test_grid_repeat_autofill_dropped),
        cmocka_unit_test(test_fit_content_trim),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
