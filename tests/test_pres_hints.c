/* test_pres_hints -- HTML presentational attributes (spec/pres_hints.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <string.h>
#include <cmocka.h>

#include "pres_hints.h"

typedef struct { const char *name, *value; } kv;

static const char *get(void *ctx, const char *name, size_t *len) {
    for (const kv *p = ctx; p != NULL && p->name != NULL; ++p)
        if (strcmp(p->name, name) == 0) { *len = strlen(p->value); return p->value; }
    return NULL;
}

static css_style fresh(void) {
    css_style cs;
    memset(&cs, 0, sizeof cs);
    cs.width = CSS_LEN_UNSET;
    cs.margin_left = cs.margin_right = CSS_LEN_UNSET;
    cs.background = -1;
    return cs;
}

static void test_dimension(void **state) {
    (void)state;
    int px = -1, pm = -1;
    assert_int_equal(ph_parse_dimension("85%", 3, &px, &pm), 2);
    assert_int_equal(pm, 850);
    assert_int_equal(ph_parse_dimension(" 120", 4, &px, &pm), 1);
    assert_int_equal(px, 120);
    assert_int_equal(ph_parse_dimension("12.5%", 5, &px, &pm), 2);
    assert_int_equal(pm, 125);
    assert_int_equal(ph_parse_dimension("18px", 4, &px, &pm), 1);
    assert_int_equal(px, 18);
    assert_int_equal(ph_parse_dimension("", 0, &px, &pm), 0);
    assert_int_equal(ph_parse_dimension("abc", 3, &px, &pm), 0);
    assert_int_equal(ph_parse_dimension("0", 1, &px, &pm), 0);
    assert_int_equal(ph_parse_dimension("-5", 2, &px, &pm), 0);
    assert_int_equal(ph_parse_dimension("99999999999", 11, &px, &pm), 0);
    assert_int_equal(ph_parse_dimension("5000%", 5, &px, &pm), 0);
    assert_int_equal(ph_parse_dimension(NULL, 3, &px, &pm), 0);
}

/* Given <table width="85%"> inside <center>, the table is 85% wide and centred. */
static void test_table_width_and_centering(void **state) {
    (void)state;
    kv a[] = { { "width", "85%" }, { NULL, NULL } };
    css_style cs = fresh();
    ph_apply("table", get, a, 1, &cs);
    assert_int_equal(cs.pct[CSS_PCT_WIDTH], 850);
    assert_int_equal(cs.width, 0);
    assert_int_equal(cs.margin_left, CSS_LEN_AUTO);
    assert_int_equal(cs.margin_right, CSS_LEN_AUTO);

    kv b[] = { { "align", "CENTER" }, { NULL, NULL } };
    cs = fresh();
    ph_apply("table", get, b, 0, &cs);
    assert_int_equal(cs.margin_left, CSS_LEN_AUTO);
    assert_int_equal(cs.width, CSS_LEN_UNSET);

    /* Not centred, no align: margins stay undeclared. */
    cs = fresh();
    ph_apply("table", get, a, 0, &cs);
    assert_int_equal(cs.margin_left, CSS_LEN_UNSET);
}

/* Given a CSS declaration, the attribute loses -- both halves of the width stay the author's. */
static void test_css_wins(void **state) {
    (void)state;
    kv a[] = { { "width", "85%" }, { "align", "right" }, { "nowrap", "" }, { NULL, NULL } };
    css_style cs = fresh();
    cs.width = 300;
    cs.text_align = CSS_ALIGN_LEFT;
    cs.white_space = CSS_WS_PRE;
    cs.margin_left = 4;
    ph_apply("td", get, a, 1, &cs);
    assert_int_equal(cs.width, 300);
    assert_int_equal(cs.pct[CSS_PCT_WIDTH], 0);
    assert_int_equal(cs.text_align, CSS_ALIGN_LEFT);
    assert_int_equal(cs.white_space, CSS_WS_PRE);
    assert_int_equal(cs.margin_left, 4);

    cs = fresh();
    cs.pct[CSS_PCT_WIDTH] = 500;
    ph_apply("table", get, a, 0, &cs);
    assert_int_equal(cs.pct[CSS_PCT_WIDTH], 500);
}

static void test_cell_hints(void **state) {
    (void)state;
    kv a[] = { { "width", "18" }, { "align", "right" }, { "nowrap", "" }, { NULL, NULL } };
    css_style cs = fresh();
    ph_apply("td", get, a, 0, &cs);
    assert_int_equal(cs.width, 18);
    assert_int_equal(cs.pct[CSS_PCT_WIDTH], 0);
    assert_int_equal(cs.text_align, CSS_ALIGN_RIGHT);
    assert_int_equal(cs.white_space, CSS_WS_NOWRAP);
    /* a cell is never centred as a block */
    assert_int_equal(cs.margin_left, CSS_LEN_UNSET);
}

static void test_center_and_block_align(void **state) {
    (void)state;
    kv none[] = { { NULL, NULL } };
    css_style cs = fresh();
    ph_apply("center", get, none, 0, &cs);
    assert_int_equal(cs.text_align, CSS_ALIGN_CENTER);

    kv a[] = { { "align", "center" }, { "width", "50%" }, { NULL, NULL } };
    cs = fresh();
    ph_apply("div", get, a, 0, &cs);
    assert_int_equal(cs.text_align, CSS_ALIGN_CENTER);
    assert_int_equal(cs.width, CSS_LEN_UNSET);     /* width is not a hint on <div> */

    kv bad[] = { { "align", "sideways" }, { NULL, NULL } };
    cs = fresh();
    ph_apply("p", get, bad, 0, &cs);
    assert_int_equal(cs.text_align, CSS_ALIGN_UNSET);

    /* An element with no hints is untouched; span align means nothing. */
    cs = fresh();
    css_style before = cs;
    ph_apply("span", get, a, 1, &cs);
    assert_memory_equal(&cs, &before, sizeof cs);
}

/* bgcolor is the background of table parts and <body>; quirks tables reset text-align. */
static void test_bgcolor_and_quirks(void **state) {
    (void)state;
    kv a[] = { { "bgcolor", "#ff6600" }, { NULL, NULL } };
    css_style cs = fresh();
    ph_apply("td", get, a, 0, &cs);
    assert_int_equal(cs.background, 0xff6600);
    cs = fresh();
    ph_apply("table", get, a, PH_QUIRKS, &cs);
    assert_int_equal(cs.background, 0xff6600);
    assert_int_equal(cs.text_align, CSS_ALIGN_LEFT);
    cs = fresh();
    ph_apply("table", get, a, 0, &cs);
    assert_int_equal(cs.text_align, CSS_ALIGN_UNSET);
    cs = fresh();
    ph_apply("body", get, a, 0, &cs);
    assert_int_equal(cs.background, 0xff6600);
    /* CSS wins; a non-table element ignores it; garbage is ignored. */
    cs = fresh();
    cs.background = 0x112233;
    ph_apply("td", get, a, 0, &cs);
    assert_int_equal(cs.background, 0x112233);
    cs = fresh();
    ph_apply("div", get, a, 0, &cs);
    assert_int_equal(cs.background, -1);
    kv bad[] = { { "bgcolor", "not-a-colour(" }, { NULL, NULL } };
    cs = fresh();
    ph_apply("td", get, bad, 0, &cs);
    assert_int_equal(cs.background, -1);
}

static void test_fail_closed(void **state) {
    (void)state;
    kv a[] = { { "width", "85%" }, { NULL, NULL } };
    css_style cs = fresh();
    css_style before = cs;
    ph_apply(NULL, get, a, 1, &cs);
    ph_apply("table", NULL, a, 1, &cs);
    ph_apply("table", get, a, 1, NULL);
    assert_memory_equal(&cs, &before, sizeof cs);
    kv lng[] = { { "width", "000000000000000000000000000000000000000000085%" }, { NULL, NULL } };
    ph_apply("table", get, lng, 0, &cs);
    assert_int_equal(cs.width, CSS_LEN_UNSET);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_dimension),
        cmocka_unit_test(test_table_width_and_centering),
        cmocka_unit_test(test_css_wins),
        cmocka_unit_test(test_cell_hints),
        cmocka_unit_test(test_center_and_block_align),
        cmocka_unit_test(test_bgcolor_and_quirks),
        cmocka_unit_test(test_fail_closed),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
