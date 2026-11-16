/* test_table_layout -- automatic table layout (spec/table_layout.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <math.h>
#include <cmocka.h>

#include "table_layout.h"

#define EPS 0.001

static void assert_near(double got, double want) {
    if (fabs(got - want) > EPS) fail_msg("got %.4f, want %.4f", got, want);
}

/* Given an auto table whose content fits, columns are as wide as their widest cell. */
static void test_auto_table_takes_max_content(void **state) {
    (void)state;
    tl_cell c[] = { { 0, 1, 10, 40, -1, 0 }, { 1, 1, 20, 100, -1, 0 },
                    { 0, 1, 10, 60, -1, 0 }, { 1, 1, 20, 80, -1, 0 } };
    double out[2];
    double w = tl_columns(c, 4, 2, 0.0, 1000.0, -1.0, out);
    assert_near(out[0], 60.0);
    assert_near(out[1], 100.0);
    assert_near(w, 160.0);
}

/* Given a declared table width above the content, the surplus goes to the auto columns in
 * proportion to their max-content width; a sized column keeps its width (the HN header:
 * an 18 px logo cell, the nav, the login). */
static void test_declared_table_width_distributes_surplus(void **state) {
    (void)state;
    tl_cell c[] = { { 0, 1, 22, 22, 22, 0 }, { 1, 1, 50, 300, -1, 0 }, { 2, 1, 30, 100, -1, 0 } };
    double out[3];
    double w = tl_columns(c, 3, 3, 0.0, 2000.0, 822.0, out);
    assert_near(w, 822.0);
    assert_near(out[0], 22.0);
    assert_near(out[1], 300.0 + 400.0 * 0.75);
    assert_near(out[2], 100.0 + 400.0 * 0.25);
}

/* Given every column sized, the surplus still has to land somewhere: all share it. */
static void test_surplus_with_no_auto_column(void **state) {
    (void)state;
    tl_cell c[] = { { 0, 1, 10, 100, 100, 0 }, { 1, 1, 10, 300, 300, 0 } };
    double out[2];
    double w = tl_columns(c, 2, 2, 0.0, 2000.0, 800.0, out);
    assert_near(w, 800.0);
    assert_near(out[0], 200.0);
    assert_near(out[1], 600.0);
}

/* Given less room than max-content but more than min-content, each column gets its minimum
 * plus a share of the slack proportional to (max - min). */
static void test_between_min_and_max(void **state) {
    (void)state;
    tl_cell c[] = { { 0, 1, 50, 150, -1, 0 }, { 1, 1, 50, 350, -1, 0 } };
    double out[2];
    double w = tl_columns(c, 2, 2, 0.0, 300.0, -1.0, out);
    assert_near(w, 300.0);
    assert_near(out[0], 50.0 + 200.0 * 0.25);
    assert_near(out[1], 50.0 + 200.0 * 0.75);
}

/* Given an auto table whose minimum exceeds the page, min-content is a floor: the columns
 * keep it and the table overflows (CSS 2.1 17.5.2.2), it is not squeezed a letter per line. */
static void test_overconstrained_shrinks_proportionally(void **state) {
    (void)state;
    tl_cell c[] = { { 0, 1, 300, 300, -1, 0 }, { 1, 1, 100, 100, -1, 0 } };
    double out[2];
    double w = tl_columns(c, 2, 2, 0.0, 200.0, -1.0, out);
    assert_near(w, 400.0);
    assert_near(out[0], 300.0);
    assert_near(out[1], 100.0);
}

/* Given a spanning cell wider than the columns it covers, the excess is spread over them in
 * proportion to their max width (the HN subtext row: colspan=2 over rank and arrow). */
static void test_span_widens_covered_columns(void **state) {
    (void)state;
    tl_cell c[] = { { 0, 1, 30, 30, -1, 0 }, { 1, 1, 10, 10, -1, 0 }, { 2, 1, 40, 200, -1, 0 },
                    { 0, 2, 80, 80, -1, 0 }, { 2, 1, 40, 150, -1, 0 } };
    double out[3];
    double w = tl_columns(c, 5, 3, 0.0, 1000.0, -1.0, out);
    assert_near(out[0], 60.0);
    assert_near(out[1], 20.0);
    assert_near(out[2], 200.0);
    assert_near(w, 280.0);
}

/* Given a spanning cell narrower than its columns, nothing changes; an empty spanned cell
 * (HN's `<td colspan="2"></td>`) must not widen anything. */
static void test_span_narrower_is_inert(void **state) {
    (void)state;
    tl_cell c[] = { { 0, 1, 30, 30, -1, 0 }, { 1, 1, 10, 10, -1, 0 }, { 0, 2, 0, 0, -1, 0 } };
    double out[2];
    double w = tl_columns(c, 3, 2, 0.0, 1000.0, -1.0, out);
    assert_near(out[0], 30.0);
    assert_near(out[1], 10.0);
    assert_near(w, 40.0);
}

/* Given a spanning cell over columns with no content at all, they share its width equally. */
static void test_span_over_empty_columns_splits_evenly(void **state) {
    (void)state;
    tl_cell c[] = { { 0, 2, 100, 100, -1, 0 } };
    double out[2];
    (void)tl_columns(c, 1, 2, 0.0, 1000.0, -1.0, out);
    assert_near(out[0], 50.0);
    assert_near(out[1], 50.0);
}

/* Gaps are part of the table's width and of what a spanning cell already covers. */
static void test_gap_counts(void **state) {
    (void)state;
    tl_cell c[] = { { 0, 1, 40, 40, -1, 0 }, { 1, 1, 40, 40, -1, 0 }, { 0, 2, 90, 90, -1, 0 } };
    double out[2];
    double w = tl_columns(c, 3, 2, 10.0, 1000.0, -1.0, out);
    assert_near(out[0], 40.0);
    assert_near(out[1], 40.0);
    assert_near(w, 90.0);
    w = tl_columns(c, 3, 2, 10.0, 1000.0, 210.0, out);
    assert_near(w, 210.0);
    assert_near(out[0], 100.0);
    assert_near(out[1], 100.0);
}

/* A declared table width below the minimum content cannot squeeze the columns. */
static void test_declared_width_never_below_min(void **state) {
    (void)state;
    tl_cell c[] = { { 0, 1, 120, 200, -1, 0 }, { 1, 1, 80, 100, -1, 0 } };
    double out[2];
    double w = tl_columns(c, 2, 2, 0.0, 1000.0, 50.0, out);
    assert_near(w, 200.0);
    assert_near(out[0], 120.0);
    assert_near(out[1], 80.0);
}

/* A declared cell width is the column's preferred width, but never below its min-content. */
static void test_declared_cell_width(void **state) {
    (void)state;
    tl_cell c[] = { { 0, 1, 10, 300, 100, 0 }, { 1, 1, 150, 150, 20, 0 } };
    double out[2];
    double w = tl_columns(c, 2, 2, 0.0, 1000.0, -1.0, out);
    assert_near(out[0], 100.0);
    assert_near(out[1], 150.0);
    assert_near(w, 250.0);
}

/* Percentage columns (the MediaWiki navbox: label `width:1%`, content `width:100%`) in a
 * sized table: a percentage is a share of the table, floored at the column's min-content and
 * capped so the shares never exceed the table; what a floor overdraws is taken back from the
 * percentage columns that have slack. */
static void test_percent_columns(void **state) {
    (void)state;
    tl_cell c[] = { { 0, 1, 60, 60, -1, 10 }, { 1, 1, 80, 400, -1, 1000 } };
    double out[2];
    double w = tl_columns(c, 2, 2, 0.0, 1000.0, 1000.0, out);
    assert_near(w, 1000.0);
    assert_near(out[0], 60.0);
    assert_near(out[1], 940.0);

    /* A percentage column beside an auto one: the share first, the rest to the auto column. */
    tl_cell d[] = { { 0, 1, 20, 100, -1, 250 }, { 1, 1, 50, 300, -1, 0 } };
    w = tl_columns(d, 2, 2, 0.0, 1000.0, 800.0, out);
    assert_near(w, 800.0);
    assert_near(out[0], 200.0);
    assert_near(out[1], 600.0);

    /* Shares below 100% with no auto column: the remainder is split by share. */
    tl_cell e[] = { { 0, 1, 10, 10, -1, 100 }, { 1, 1, 10, 10, -1, 300 } };
    w = tl_columns(e, 2, 2, 0.0, 1000.0, 400.0, out);
    assert_near(w, 400.0);
    assert_near(out[0], 100.0);
    assert_near(out[1], 300.0);

    /* An auto-width table has no width to take a share of: the percentage is ignored. */
    w = tl_columns(c, 2, 2, 0.0, 1000.0, -1.0, out);
    assert_near(out[0], 60.0);
    assert_near(out[1], 400.0);

    /* Hostile shares never produce a negative or non-finite column. */
    tl_cell h[] = { { 0, 1, 50, 50, -1, -400 }, { 1, 1, 50, 50, -1, 2000000000 } };
    w = tl_columns(h, 2, 2, 0.0, 1000.0, 300.0, out);
    assert_true(isfinite(w) && out[0] >= 0.0 && out[1] >= 0.0);
    assert_near(w, 300.0);
}

/* A table's own intrinsic widths: column minima/maxima summed, spans and gaps included. */
static void test_intrinsic(void **state) {
    (void)state;
    tl_cell c[] = { { 0, 1, 30, 100, -1, 0 }, { 1, 1, 20, 50, -1, 0 }, { 0, 2, 80, 80, -1, 0 } };
    double mn = -1.0, mx = -1.0;
    tl_intrinsic(c, 3, 2, 10.0, &mn, &mx);
    assert_near(mn, 80.0);
    assert_near(mx, 160.0);
    tl_intrinsic(c, 3, 0, 0.0, &mn, &mx);
    assert_near(mn, 0.0);
    assert_near(mx, 0.0);
    tl_intrinsic(c, 3, 2, 0.0, NULL, NULL);
}

static void test_fail_closed(void **state) {
    (void)state;
    double out[3] = { -7.0, -7.0, -7.0 };
    tl_cell c[] = { { 0, 1, 10, 20, -1, 0 } };
    assert_true(tl_columns(c, 1, 1, 0.0, 100.0, -1.0, NULL) == 0.0);
    assert_true(tl_columns(c, 1, 0, 0.0, 100.0, -1.0, out) == 0.0);
    assert_true(tl_columns(c, 1, TL_MAX_COLS + 1u, 0.0, 100.0, -1.0, out) == 0.0);
    assert_true(out[0] == -7.0);

    /* Hostile numbers: NaN/inf/negative widths read as 0, an out-of-range column is ignored,
     * an overlong span is clipped, span < 1 is 1. */
    tl_cell bad[] = { { 0, 1, NAN, INFINITY, -1, 0 }, { 5, 1, 900, 900, -1, 0 },
                      { 1, 99, 30, 60, -1, 0 }, { 2, -4, -5, 40, NAN, 0 } };
    double w = tl_columns(bad, 4, 3, NAN, INFINITY, NAN, out);
    assert_true(isfinite(w) && w >= 0.0);
    for (int i = 0; i < 3; ++i) assert_true(isfinite(out[i]) && out[i] >= 0.0);

    /* Finite but absurd numbers (1e308 from a hostile calc()) must not sum to infinity. */
    tl_cell huge[] = { { 0, 1, 1e308, 1e308, 1e308, 0 }, { 1, 1, 1e308, 1e308, -1, 0 } };
    w = tl_columns(huge, 2, 3, 1e308, 1e308, 1e308, out);
    assert_true(isfinite(w) && w >= 0.0);
    for (int i = 0; i < 3; ++i) assert_true(isfinite(out[i]) && out[i] >= 0.0);

    /* No cells at all: zero-width columns, never garbage. */
    w = tl_columns(NULL, 4, 3, 0.0, 500.0, -1.0, out);
    assert_near(w, 0.0);
    w = tl_columns(NULL, 0, 2, 0.0, 500.0, 300.0, out);
    assert_near(w, 300.0);
    assert_near(out[0], 150.0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_auto_table_takes_max_content),
        cmocka_unit_test(test_declared_table_width_distributes_surplus),
        cmocka_unit_test(test_surplus_with_no_auto_column),
        cmocka_unit_test(test_between_min_and_max),
        cmocka_unit_test(test_overconstrained_shrinks_proportionally),
        cmocka_unit_test(test_span_widens_covered_columns),
        cmocka_unit_test(test_span_narrower_is_inert),
        cmocka_unit_test(test_span_over_empty_columns_splits_evenly),
        cmocka_unit_test(test_gap_counts),
        cmocka_unit_test(test_declared_width_never_below_min),
        cmocka_unit_test(test_declared_cell_width),
        cmocka_unit_test(test_percent_columns),
        cmocka_unit_test(test_intrinsic),
        cmocka_unit_test(test_fail_closed),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
