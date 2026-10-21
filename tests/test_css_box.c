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

/* line-height (CSS 2.1 10.8.1): a number, a percentage and an em scale with the
 * font; an absolute length does not (it is that many px, and inherits so). */
static void test_lineheight_abs_vs_scale(void **state) {
    (void)state;
    assert_int_equal(cb_interp_lineheight("normal"), 0);
    assert_int_equal(cb_interp_lineheight("1.5"), 150);
    assert_int_equal(cb_interp_lineheight("150%"), 150);
    assert_int_equal(cb_interp_lineheight("1.5em"), 150);
    assert_int_equal(cb_interp_lineheight("22.4px"), CSS_LINE_ABS_BASE + 224);
    assert_int_equal(cb_interp_lineheight("12pt"), CSS_LINE_ABS_BASE + 160);
    assert_int_equal(cb_interp_lineheight("9999px"), CSS_LINE_ABS_BASE + CSS_LINE_ABS_MAX_PX * 10);
    assert_int_equal(cb_interp_lineheight("-2px"), -1);
    assert_int_equal(cb_interp_lineheight("bogus"), -1);
}

/* clip-path: inset(t r b l [round r]) becomes the four EDGES of the clip rectangle, each a
 * px part and a per-mille share of the border box (width for left/right, height for
 * top/bottom): a right inset of r is the edge at 100% - r. */
static void test_clip_inset_edges(void **state)
{
    (void)state;
    int px[4], pm[4];
    assert_int_equal(cb_clip_inset("inset(0)", px, pm), 1);
    int z[4] = {0, 0, 0, 0}, zp[4] = {0, 1000, 1000, 0};
    for (int i = 0; i < 4; ++i) { assert_int_equal(px[i], z[i]); assert_int_equal(pm[i], zp[i]); }

    /* GitHub's hero glow: top inset 135%, sides 0, bottom inset -100%. */
    assert_int_equal(cb_clip_inset("inset(135% 0 -100%)", px, pm), 1);
    assert_int_equal(pm[0], 1350);                       /* top edge */
    assert_int_equal(pm[1], 1000);                       /* right edge = 100% - 0 */
    assert_int_equal(pm[2], 2000);                       /* bottom edge = 100% + 100% */
    assert_int_equal(pm[3], 0);

    assert_int_equal(cb_clip_inset("inset(10px 20px)", px, pm), 1);
    assert_int_equal(px[0], 10);  assert_int_equal(pm[0], 0);
    assert_int_equal(px[1], -20); assert_int_equal(pm[1], 1000);
    assert_int_equal(px[2], -10); assert_int_equal(pm[2], 1000);
    assert_int_equal(px[3], 20);  assert_int_equal(pm[3], 0);

    assert_int_equal(cb_clip_inset("inset(5px round 8px)", px, pm), 1);   /* radius ignored */
    assert_int_equal(px[0], 5);
}

static void test_clip_inset_rejects(void **state)
{
    (void)state;
    int px[4], pm[4];
    assert_int_equal(cb_clip_inset("inset()", px, pm), 0);
    assert_int_equal(cb_clip_inset("inset(abc)", px, pm), 0);
    assert_int_equal(cb_clip_inset("inset(1px 2px 3px 4px 5px)", px, pm), 0);
    assert_int_equal(cb_clip_inset("circle(50%)", px, pm), 0);
    assert_int_equal(cb_clip_inset("inset(1px", px, pm), 0);
    assert_int_equal(cb_clip_inset(NULL, px, pm), 0);
}

/* Many bare area strings each add an " auto " the source did not have: the blanked copy can
 * outgrow the input. It must fail closed, never write past its buffer (fuzz-css crash). */
static void test_grid_rows_many_strings_fail_closed(void **state)
{
    (void)state;
    char val[CSS_GRID_AREAS_MAX];
    size_t n = 0;
    while (n + 4 < sizeof val - 1) { val[n++] = '"'; val[n++] = 'a'; val[n++] = '"'; val[n++] = ' '; }
    val[n] = '\0';
    css_decl dst[CSS_GRID_TRACKS_MAX + 2];
    (void)cb_expand_grid_template_rows(val, dst, (int)(sizeof dst / sizeof dst[0]));
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
        cmocka_unit_test(test_lineheight_abs_vs_scale),
        cmocka_unit_test(test_grid_rows_many_strings_fail_closed),
        cmocka_unit_test(test_clip_inset_edges),
        cmocka_unit_test(test_clip_inset_rejects),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
