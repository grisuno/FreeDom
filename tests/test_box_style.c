/*
 * test_box_style — CMocka suite for the pure user-agent box model.
 *
 * Covers the per-tag defaults (block/inline/inline-block/list-item/none, the
 * heading ladder, ul/ol padding, blockquote, hr, the zero-margin body), the
 * neutral fallback for unknown/NULL tags, case-insensitivity, the display-keyword
 * parser (every keyword, the inline-* aliases, trimming, fail-closed edges) and
 * the display-name helper.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "box_style.h"

/* em values are doubles; compare with a small tolerance. */
static int dbl_eq(double a, double b) {
    double d = a - b;
    return d < 1e-9 && d > -1e-9;
}

static void assert_edges(bx_edges e, double t, double r, double b, double l) {
    assert_true(dbl_eq(e.top, t));
    assert_true(dbl_eq(e.right, r));
    assert_true(dbl_eq(e.bottom, b));
    assert_true(dbl_eq(e.left, l));
}

static void test_body_has_no_margin(void **state) {
    (void)state;
    bx_box b = bx_default_for_tag("body");
    assert_int_equal(b.display, BX_DISPLAY_BLOCK);
    assert_edges(b.margin, 0.0, 0.0, 0.0, 0.0);  /* the window chrome owns the gutter */
    assert_edges(b.padding, 0.0, 0.0, 0.0, 0.0);
}

static void test_paragraph(void **state) {
    (void)state;
    bx_box b = bx_default_for_tag("p");
    assert_int_equal(b.display, BX_DISPLAY_BLOCK);
    assert_edges(b.margin, 1.0, 0.0, 1.0, 0.0);
}

static void test_heading_ladder(void **state) {
    (void)state;
    assert_int_equal(bx_default_for_tag("h1").display, BX_DISPLAY_BLOCK);
    assert_true(dbl_eq(bx_default_for_tag("h1").margin.top, 0.67));
    assert_true(dbl_eq(bx_default_for_tag("h2").margin.top, 0.83));
    assert_true(dbl_eq(bx_default_for_tag("h3").margin.top, 1.0));
    assert_true(dbl_eq(bx_default_for_tag("h4").margin.top, 1.33));
    assert_true(dbl_eq(bx_default_for_tag("h5").margin.top, 1.67));
    assert_true(dbl_eq(bx_default_for_tag("h6").margin.top, 2.33));
    /* symmetric top/bottom, no horizontal margin */
    bx_box h3 = bx_default_for_tag("h3");
    assert_true(dbl_eq(h3.margin.top, h3.margin.bottom));
    assert_true(dbl_eq(h3.margin.left, 0.0));
    assert_true(dbl_eq(h3.margin.right, 0.0));
}

static void test_lists(void **state) {
    (void)state;
    bx_box ul = bx_default_for_tag("ul");
    assert_int_equal(ul.display, BX_DISPLAY_BLOCK);
    assert_edges(ul.margin, 1.0, 0.0, 1.0, 0.0);
    assert_true(dbl_eq(ul.padding.left, 2.5));   /* room for the markers */
    bx_box ol = bx_default_for_tag("ol");
    assert_true(dbl_eq(ol.padding.left, 2.5));
    assert_int_equal(bx_default_for_tag("li").display, BX_DISPLAY_LIST_ITEM);
}

static void test_blockquote(void **state) {
    (void)state;
    bx_box bq = bx_default_for_tag("blockquote");
    assert_int_equal(bq.display, BX_DISPLAY_BLOCK);
    assert_edges(bq.margin, 1.0, 2.5, 1.0, 2.5);
}

static void test_hr(void **state) {
    (void)state;
    bx_box hr = bx_default_for_tag("hr");
    assert_int_equal(hr.display, BX_DISPLAY_BLOCK);
    assert_edges(hr.margin, 0.5, 0.0, 0.5, 0.0);
}

static void test_inline_and_inline_block(void **state) {
    (void)state;
    assert_int_equal(bx_default_for_tag("span").display, BX_DISPLAY_INLINE);
    assert_int_equal(bx_default_for_tag("a").display, BX_DISPLAY_INLINE);
    assert_int_equal(bx_default_for_tag("strong").display, BX_DISPLAY_INLINE);
    assert_int_equal(bx_default_for_tag("code").display, BX_DISPLAY_INLINE);
    assert_int_equal(bx_default_for_tag("img").display, BX_DISPLAY_INLINE_BLOCK);
    assert_int_equal(bx_default_for_tag("input").display, BX_DISPLAY_INLINE_BLOCK);
    assert_int_equal(bx_default_for_tag("button").display, BX_DISPLAY_INLINE_BLOCK);
}

static void test_display_none_for_non_rendered(void **state) {
    (void)state;
    assert_int_equal(bx_default_for_tag("head").display, BX_DISPLAY_NONE);
    assert_int_equal(bx_default_for_tag("script").display, BX_DISPLAY_NONE);
    assert_int_equal(bx_default_for_tag("style").display, BX_DISPLAY_NONE);
    assert_int_equal(bx_default_for_tag("title").display, BX_DISPLAY_NONE);
    assert_int_equal(bx_default_for_tag("meta").display, BX_DISPLAY_NONE);
}

static void test_case_insensitive(void **state) {
    (void)state;
    assert_int_equal(bx_default_for_tag("P").display, BX_DISPLAY_BLOCK);
    assert_true(dbl_eq(bx_default_for_tag("P").margin.top, 1.0));
    assert_int_equal(bx_default_for_tag("DiV").display, BX_DISPLAY_BLOCK);
    assert_int_equal(bx_default_for_tag("ImG").display, BX_DISPLAY_INLINE_BLOCK);
}

static void test_unknown_and_null_are_neutral_inline(void **state) {
    (void)state;
    bx_box u = bx_default_for_tag("zorp");
    assert_int_equal(u.display, BX_DISPLAY_INLINE);
    assert_edges(u.margin, 0.0, 0.0, 0.0, 0.0);
    assert_edges(u.padding, 0.0, 0.0, 0.0, 0.0);

    bx_box n = bx_default_for_tag(NULL);
    assert_int_equal(n.display, BX_DISPLAY_INLINE);
    assert_edges(n.margin, 0.0, 0.0, 0.0, 0.0);

    bx_box e = bx_default_for_tag("");
    assert_int_equal(e.display, BX_DISPLAY_INLINE);
}

static void test_div_is_block(void **state) {
    (void)state;
    bx_box d = bx_default_for_tag("div");
    assert_int_equal(d.display, BX_DISPLAY_BLOCK);
    assert_edges(d.margin, 0.0, 0.0, 0.0, 0.0);
}

/* --- bx_ua_of_tag / bx_default_for_ua (spec/box_style.md 4d) --- */

/* The whole point of the code: the structural wrappers a real page is built from
 * carry NO user-agent margin, so none of them may map to the <p> row. */
static void test_ua_structural_wrappers_have_no_margin(void **state) {
    (void)state;
    static const char *const wrappers[] = {
        "div", "section", "header", "article", "footer", "nav", "main", "aside",
        "table", "tbody", "thead", "tfoot", "tr", "td", "th", "form", "fieldset",
        "figcaption", "dt", "address", "details", "summary", "span",
    };
    for (size_t i = 0; i < sizeof wrappers / sizeof wrappers[0]; ++i) {
        assert_int_equal(bx_ua_of_tag(wrappers[i]), BX_UA_NONE);
        bx_box b = bx_default_for_ua(bx_ua_of_tag(wrappers[i]));
        assert_true(dbl_eq(b.margin.top, 0.0));
        assert_true(dbl_eq(b.margin.bottom, 0.0));
    }
}

/* ...while the handful of elements the user-agent sheet DOES space keep their margin
 * through the round trip, at the same value bx_default_for_tag reports. */
static void test_ua_spaced_tags_round_trip(void **state) {
    (void)state;
    static const char *const spaced[] = {
        "p", "h1", "h2", "h3", "h4", "h5", "h6", "ul", "ol", "menu",
        "dl", "pre", "blockquote", "figure", "hr",
    };
    for (size_t i = 0; i < sizeof spaced / sizeof spaced[0]; ++i) {
        bx_ua_tag id = bx_ua_of_tag(spaced[i]);
        assert_int_not_equal(id, BX_UA_NONE);
        bx_box viaid  = bx_default_for_ua(id);
        bx_box viatag = bx_default_for_tag(spaced[i]);
        assert_true(dbl_eq(viaid.margin.top, viatag.margin.top));
        assert_true(dbl_eq(viaid.margin.bottom, viatag.margin.bottom));
        assert_true(viaid.margin.top > 0.0);
        assert_int_equal(viaid.display, viatag.display);
    }
}

/* A list item is spacing-free but is NOT the unknown-tag fallback: it has its own
 * code, so a block inside a list can be told apart from a block nobody classified. */
static void test_ua_list_item_is_distinct_but_unspaced(void **state) {
    (void)state;
    assert_int_equal(bx_ua_of_tag("li"), BX_UA_LI);
    bx_box li = bx_default_for_ua(BX_UA_LI);
    assert_int_equal(li.display, BX_DISPLAY_LIST_ITEM);
    assert_edges(li.margin, 0.0, 0.0, 0.0, 0.0);
}

/* --- bx_block_ua_box: the three-way block decision (spec/box_style.md 4f) --- */

/* The margin of a block is the margin of its SOURCE element, whatever kind of run
 * happened to carry it. A <p> holding nothing but an <a> is still a <p>: the anchor
 * is inline-level and CSS 2.1 8.3 gives it no vertical margin to contribute. */
static void test_block_ua_box_is_content_independent(void **state) {
    (void)state;
    bx_box p = bx_block_ua_box(0, 0, BX_UA_P);
    assert_edges(p.margin, 1.0, 0.0, 1.0, 0.0);

    /* Same element, whatever the painter's rd_kind was: the answer comes from ua. */
    bx_box wrapper = bx_block_ua_box(0, 0, BX_UA_NONE);
    assert_edges(wrapper.margin, 0.0, 0.0, 0.0, 0.0);
}

/* A heading's own level picks h1..h6 -- not the block ancestry it was found under. */
static void test_block_ua_box_heading_level_wins(void **state) {
    (void)state;
    bx_box h2 = bx_block_ua_box(2, 0, BX_UA_NONE);
    assert_edges(h2.margin, 0.83, 0.0, 0.83, 0.0);
    /* Even when the ancestor says <p>, the heading level is the authority. */
    bx_box h1_in_p = bx_block_ua_box(1, 0, BX_UA_P);
    assert_edges(h1_in_p.margin, 0.67, 0.0, 0.67, 0.0);
    /* Out-of-range levels clamp into 1..6 rather than inventing a box. */
    assert_edges(bx_block_ua_box(99, 0, BX_UA_NONE).margin, 2.33, 0.0, 2.33, 0.0);
}

/* A block inside a list takes the list item's (zero) box, keeping items tight --
 * the deliberate approximation of 4d. A heading still escapes it. */
static void test_block_ua_box_list_item_wins_over_ancestor(void **state) {
    (void)state;
    bx_box in_list = bx_block_ua_box(0, 1, BX_UA_P);
    assert_edges(in_list.margin, 0.0, 0.0, 0.0, 0.0);
    bx_box heading_in_list = bx_block_ua_box(3, 1, BX_UA_P);
    assert_edges(heading_in_list.margin, 1.0, 0.0, 1.0, 0.0);
}

/* Total: every representable input yields a box, none of them invented. */
static void test_block_ua_box_is_total(void **state) {
    (void)state;
    for (int ua = 0; ua < BX_UA_COUNT + 2; ++ua) {
        for (int lvl = -1; lvl <= 7; ++lvl) {
            bx_box b = bx_block_ua_box(lvl, lvl & 1, (bx_ua_tag)ua);
            assert_true(b.margin.top >= 0.0);
            assert_true(b.margin.bottom >= 0.0);
        }
    }
}

/* --- bx_table_role_of: the UA sheet's table roles (spec/css.md, CSS 2.1 17.2) --- */

/* With no author display, the role is the one the HTML user-agent sheet assigns to
 * the tag -- which is where every <table> the engine already laid out came from. */
static void test_table_role_from_tag(void **state) {
    (void)state;
    assert_int_equal(bx_table_role_of("table", CSS_DISP_UNSET), BX_TROLE_TABLE);
    assert_int_equal(bx_table_role_of("tr", CSS_DISP_UNSET), BX_TROLE_ROW);
    assert_int_equal(bx_table_role_of("td", CSS_DISP_UNSET), BX_TROLE_CELL);
    assert_int_equal(bx_table_role_of("th", CSS_DISP_UNSET), BX_TROLE_CELL);
    assert_int_equal(bx_table_role_of("tbody", CSS_DISP_UNSET), BX_TROLE_ROW_GROUP);
    assert_int_equal(bx_table_role_of("thead", CSS_DISP_UNSET), BX_TROLE_ROW_GROUP);
    assert_int_equal(bx_table_role_of("tfoot", CSS_DISP_UNSET), BX_TROLE_ROW_GROUP);
    assert_int_equal(bx_table_role_of("caption", CSS_DISP_UNSET), BX_TROLE_CAPTION);
    assert_int_equal(bx_table_role_of("colgroup", CSS_DISP_UNSET), BX_TROLE_COLUMN);
    assert_int_equal(bx_table_role_of("col", CSS_DISP_UNSET), BX_TROLE_COLUMN);
    assert_int_equal(bx_table_role_of("div", CSS_DISP_UNSET), BX_TROLE_NONE);
}

/* A computed display that names a role wins over the tag: that is the whole point --
 * a <div style="display:table-cell"> is a cell, and a <td style="display:block"> is
 * not (CSS 2.1 17.2: the role is the display, the UA sheet merely supplies it). */
static void test_table_role_display_overrides_tag(void **state) {
    (void)state;
    assert_int_equal(bx_table_role_of("div", CSS_DISP_TABLE), BX_TROLE_TABLE);
    assert_int_equal(bx_table_role_of("span", CSS_DISP_TABLE_CELL), BX_TROLE_CELL);
    assert_int_equal(bx_table_role_of("li", CSS_DISP_TABLE_ROW), BX_TROLE_ROW);
    assert_int_equal(bx_table_role_of("td", CSS_DISP_BLOCK), BX_TROLE_NONE);
    assert_int_equal(bx_table_role_of("table", CSS_DISP_FLEX), BX_TROLE_NONE);
    /* display:none is not a table role; the caller drops the element anyway. */
    assert_int_equal(bx_table_role_of("td", CSS_DISP_NONE), BX_TROLE_NONE);
}

/* Total and fail-closed: no tag, no display, nothing invented. */
static void test_table_role_is_total(void **state) {
    (void)state;
    assert_int_equal(bx_table_role_of(NULL, CSS_DISP_UNSET), BX_TROLE_NONE);
    assert_int_equal(bx_table_role_of("", CSS_DISP_UNSET), BX_TROLE_NONE);
    assert_int_equal(bx_table_role_of("zorp", CSS_DISP_UNSET), BX_TROLE_NONE);
    assert_int_equal(bx_table_role_of(NULL, CSS_DISP_TABLE_CELL), BX_TROLE_CELL);
    for (int d = 0; d < CSS_DISP_TABLE_COLUMN + 3; ++d)
        (void)bx_table_role_of("div", (css_display)d);
}

static void test_ua_case_insensitive_and_trimmed(void **state) {
    (void)state;
    assert_int_equal(bx_ua_of_tag("P"), BX_UA_P);
    assert_int_equal(bx_ua_of_tag("  BlockQuote \n"), BX_UA_BLOCKQUOTE);
    assert_int_equal(bx_ua_of_tag("H3"), BX_UA_H3);
}

/* Fails closed in both directions: nothing recognisable, no invented spacing. */
static void test_ua_fails_closed(void **state) {
    (void)state;
    assert_int_equal(bx_ua_of_tag(NULL), BX_UA_NONE);
    assert_int_equal(bx_ua_of_tag(""), BX_UA_NONE);
    assert_int_equal(bx_ua_of_tag("zorp"), BX_UA_NONE);
    assert_int_equal(bx_ua_of_tag("this-tag-name-is-far-too-long-to-fit-in-the-buffer"),
                     BX_UA_NONE);

    bx_box none = bx_default_for_ua(BX_UA_NONE);
    assert_edges(none.margin, 0.0, 0.0, 0.0, 0.0);
    bx_box over = bx_default_for_ua((bx_ua_tag)BX_UA_COUNT);
    assert_edges(over.margin, 0.0, 0.0, 0.0, 0.0);
    bx_box way = bx_default_for_ua((bx_ua_tag)9999);
    assert_edges(way.margin, 0.0, 0.0, 0.0, 0.0);
}

/* The table the codes index must stay in step with the enum: every code in range
 * resolves, and no two codes collide on one tag. */
static void test_ua_code_space_is_total(void **state) {
    (void)state;
    for (int i = BX_UA_NONE + 1; i < BX_UA_COUNT; ++i) {
        bx_box b = bx_default_for_ua((bx_ua_tag)i);
        assert_int_not_equal(b.display, BX_DISPLAY_INLINE);
        for (int j = i + 1; j < BX_UA_COUNT; ++j) {
            assert_int_not_equal(i, j);
        }
    }
}

static void test_parse_display_keywords(void **state) {
    (void)state;
    bx_display d;
    assert_int_equal(bx_parse_display("none", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_NONE);
    assert_int_equal(bx_parse_display("block", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_BLOCK);
    assert_int_equal(bx_parse_display("inline", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_INLINE);
    assert_int_equal(bx_parse_display("inline-block", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_INLINE_BLOCK);
    assert_int_equal(bx_parse_display("list-item", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_LIST_ITEM);
    assert_int_equal(bx_parse_display("flex", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_FLEX);
    assert_int_equal(bx_parse_display("grid", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_GRID);
}

static void test_parse_display_inline_aliases(void **state) {
    (void)state;
    bx_display d;
    assert_int_equal(bx_parse_display("inline-flex", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_FLEX);
    assert_int_equal(bx_parse_display("inline-grid", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_GRID);
}

static void test_parse_display_case_and_trim(void **state) {
    (void)state;
    bx_display d;
    assert_int_equal(bx_parse_display("  FLEX  ", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_FLEX);
    assert_int_equal(bx_parse_display("\tGrid\n", &d), BX_OK);
    assert_int_equal(d, BX_DISPLAY_GRID);
}

static void test_parse_display_errors(void **state) {
    (void)state;
    bx_display d = BX_DISPLAY_BLOCK;
    assert_int_equal(bx_parse_display(NULL, &d), BX_ERR_NULL_ARG);
    assert_int_equal(bx_parse_display("flex", NULL), BX_ERR_NULL_ARG);
    assert_int_equal(bx_parse_display("", &d), BX_ERR_SYNTAX);
    assert_int_equal(bx_parse_display("table", &d), BX_ERR_SYNTAX);
    assert_int_equal(bx_parse_display("flow-root", &d), BX_ERR_SYNTAX);
    assert_int_equal(bx_parse_display("var(--x)", &d), BX_ERR_SYNTAX);
    /* an oversized token must fail closed, not overflow */
    char big[256];
    memset(big, 'a', sizeof big - 1);
    big[sizeof big - 1] = '\0';
    assert_int_equal(bx_parse_display(big, &d), BX_ERR_SYNTAX);
    /* out untouched on error */
    assert_int_equal(d, BX_DISPLAY_BLOCK);
}

static void test_display_name(void **state) {
    (void)state;
    assert_string_equal(bx_display_name(BX_DISPLAY_BLOCK), "block");
    assert_string_equal(bx_display_name(BX_DISPLAY_INLINE), "inline");
    assert_string_equal(bx_display_name(BX_DISPLAY_INLINE_BLOCK), "inline-block");
    assert_string_equal(bx_display_name(BX_DISPLAY_LIST_ITEM), "list-item");
    assert_string_equal(bx_display_name(BX_DISPLAY_FLEX), "flex");
    assert_string_equal(bx_display_name(BX_DISPLAY_GRID), "grid");
    assert_string_equal(bx_display_name(BX_DISPLAY_NONE), "none");
    /* unknown enum value falls back to inline, never NULL */
    assert_string_equal(bx_display_name((bx_display)999), "inline");
}

/* --- bx_place: author box horizontal geometry (Hito 23b-3) --- */

static void test_place_no_box_is_identity(void **state) {
    (void)state;
    bx_hplace p = bx_place(0, 0, 0, 0, 800.0);
    assert_true(dbl_eq(p.x_off, 0.0));
    assert_true(dbl_eq(p.content_w, 800.0));
}

static void test_place_max_width_caps(void **state) {
    (void)state;
    /* cap below available: content shrinks, left-aligned (no centering). */
    bx_hplace p = bx_place(0, 0, 600.0, 0, 800.0);
    assert_true(dbl_eq(p.x_off, 0.0));
    assert_true(dbl_eq(p.content_w, 600.0));
    /* cap above available: never overflows (stays at available). */
    bx_hplace q = bx_place(0, 0, 2000.0, 0, 800.0);
    assert_true(dbl_eq(q.content_w, 800.0));
}

static void test_place_centering(void **state) {
    (void)state;
    /* margin: 0 auto; max-width:600 within 800 -> centered, 100px each side. */
    bx_hplace p = bx_place(0, 0, 600.0, 1, 800.0);
    assert_true(dbl_eq(p.content_w, 600.0));
    assert_true(dbl_eq(p.x_off, 100.0));
    /* centering with no width cap is a no-op (nothing to center). */
    bx_hplace q = bx_place(0, 0, 0, 1, 800.0);
    assert_true(dbl_eq(q.x_off, 0.0));
    assert_true(dbl_eq(q.content_w, 800.0));
}

static void test_place_insets(void **state) {
    (void)state;
    /* padding/left+right margins inset the content and shrink the width. */
    bx_hplace p = bx_place(40.0, 20.0, 0, 0, 800.0);
    assert_true(dbl_eq(p.x_off, 40.0));
    assert_true(dbl_eq(p.content_w, 740.0));  /* 800 - 40 - 20 */
    /* insets compose with a width cap (cap applies to the inner box). */
    bx_hplace q = bx_place(40.0, 20.0, 500.0, 0, 800.0);
    assert_true(dbl_eq(q.x_off, 40.0));
    assert_true(dbl_eq(q.content_w, 500.0));
}

static void test_place_failclosed_bounds(void **state) {
    (void)state;
    /* negative insets clamp to 0; tiny/negative avail floors content_w at 1. */
    bx_hplace p = bx_place(-50.0, -50.0, 0, 0, 800.0);
    assert_true(dbl_eq(p.x_off, 0.0));
    assert_true(dbl_eq(p.content_w, 800.0));
    bx_hplace q = bx_place(0, 0, 0, 0, -10.0);
    assert_true(p.x_off >= 0.0);
    assert_true(q.content_w >= 1.0);
    /* insets exceeding avail still yield content_w >= 1 (never negative). */
    bx_hplace r = bx_place(900.0, 900.0, 0, 0, 800.0);
    assert_true(r.content_w >= 1.0);
}

/* Hito 32: effective width cap combining the px cap with a per-mille cap
 * resolved against the real available width (the tighter one wins). */
/* bx_lp_px: the used value of a <length-percentage> is px + pct/1000 * basis,
 * and nothing else. Unlike bx_width_cap (which picks the TIGHTER of a width and
 * a max-width sharing one slot), this is ADDITIVE: `padding: 10px` and
 * `padding: 5%` are halves of one value, not two competing caps. */
static void test_lp_used_value(void **state) {
    (void)state;
    assert_true(dbl_eq(bx_lp_px(10, 0, 800.0), 10.0));        /* px only */
    assert_true(dbl_eq(bx_lp_px(0, 500, 800.0), 400.0));      /* 50% of 800 */
    assert_true(dbl_eq(bx_lp_px(10, 500, 800.0), 410.0));     /* both halves add */
    assert_true(dbl_eq(bx_lp_px(0, 25, 1000.0), 25.0));       /* 2.5% of 1000 */
    assert_true(dbl_eq(bx_lp_px(-20, 1000, 200.0), 180.0));   /* calc(100% - 20px) */

    /* A percentage-only value leaves the px half at the "not declared"
     * sentinel; treating that as a real length would resolve to INT_MIN. */
    assert_true(dbl_eq(bx_lp_px(CSS_LEN_UNSET, 500, 800.0), 400.0));
    assert_true(dbl_eq(bx_lp_px(CSS_LEN_AUTO, 500, 800.0), 400.0));
    assert_true(dbl_eq(bx_lp_px(CSS_LEN_UNSET, 0, 800.0), 0.0));

    /* An unusable basis contributes nothing, but never discards the px half. */
    assert_true(dbl_eq(bx_lp_px(10, 500, 0.0), 10.0));
    assert_true(dbl_eq(bx_lp_px(10, 500, -5.0), 10.0));
}

/* bx_border_box_h: with the CSS default (content-box) a declared height sizes
 * the CONTENT, so padding and border make the painted box taller. Treating the
 * declared value as the border box made every `height:Npx; padding:...` box
 * exactly padding+border too short. */
static void test_border_box_height(void **state) {
    (void)state;
    /* content-box: the edges add. */
    assert_true(dbl_eq(bx_border_box_h(60.0, 0, 20.0, 20.0, 0.0, 0.0), 100.0));
    assert_true(dbl_eq(bx_border_box_h(60.0, 0, 10.0, 10.0, 1.0, 1.0), 82.0));
    /* border-box: the declared height already includes them. */
    assert_true(dbl_eq(bx_border_box_h(60.0, 1, 20.0, 20.0, 5.0, 5.0), 60.0));
    /* no edges: identity either way. */
    assert_true(dbl_eq(bx_border_box_h(60.0, 0, 0.0, 0.0, 0.0, 0.0), 60.0));
    /* degenerate inputs never produce a negative box. */
    assert_true(dbl_eq(bx_border_box_h(-5.0, 0, 10.0, 10.0, 0.0, 0.0), 20.0));
    assert_true(dbl_eq(bx_border_box_h(10.0, 0, -3.0, -3.0, 0.0, 0.0), 10.0));
}

static void test_width_cap_pct(void **state) {
    (void)state;
    assert_true(dbl_eq(bx_width_cap(0, 0, 800.0), 0.0));       /* none */
    assert_true(dbl_eq(bx_width_cap(600, 0, 800.0), 600.0));   /* px only */
    assert_true(dbl_eq(bx_width_cap(0, 998, 1000.0), 998.0));  /* 99.8% of 1000 */
    assert_true(dbl_eq(bx_width_cap(0, 500, 800.0), 400.0));   /* 50% of 800 */
    assert_true(dbl_eq(bx_width_cap(300, 500, 800.0), 300.0)); /* px tighter */
    assert_true(dbl_eq(bx_width_cap(700, 500, 800.0), 400.0)); /* pct tighter */
    assert_true(dbl_eq(bx_width_cap(0, 500, 0.0), 0.0));       /* no avail: none */
    assert_true(dbl_eq(bx_width_cap(-5, -3, 800.0), 0.0));     /* junk: none */
}

/* 2026-07-11: box-sizing: border-box subtracts the horizontal padding + border
 * from the width cap (bx_place interprets the cap as CONTENT width). */
static void test_content_cap_border_box(void **state) {
    (void)state;
    /* content-box / unset: identity */
    assert_true(dbl_eq(bx_content_cap(300.0, 0, 20.0, 20.0, 2.0, 2.0), 300.0));
    /* no cap: identity regardless of model */
    assert_true(dbl_eq(bx_content_cap(0.0, 1, 20.0, 20.0, 2.0, 2.0), 0.0));
    /* border-box: 300 - 20 - 20 - 2 - 2 = 256 */
    assert_true(dbl_eq(bx_content_cap(300.0, 1, 20.0, 20.0, 2.0, 2.0), 256.0));
    /* narrower than its own edges: clamps to 1, never negative */
    assert_true(dbl_eq(bx_content_cap(30.0, 1, 20.0, 20.0, 2.0, 2.0), 1.0));
    /* negative edges treated as 0 (defensive) */
    assert_true(dbl_eq(bx_content_cap(300.0, 1, -5.0, 20.0, -1.0, 2.0), 278.0));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_place_no_box_is_identity),
        cmocka_unit_test(test_place_max_width_caps),
        cmocka_unit_test(test_place_centering),
        cmocka_unit_test(test_place_insets),
        cmocka_unit_test(test_place_failclosed_bounds),
        cmocka_unit_test(test_width_cap_pct),
        cmocka_unit_test(test_content_cap_border_box),
        cmocka_unit_test(test_body_has_no_margin),
        cmocka_unit_test(test_paragraph),
        cmocka_unit_test(test_heading_ladder),
        cmocka_unit_test(test_lists),
        cmocka_unit_test(test_blockquote),
        cmocka_unit_test(test_hr),
        cmocka_unit_test(test_inline_and_inline_block),
        cmocka_unit_test(test_display_none_for_non_rendered),
        cmocka_unit_test(test_case_insensitive),
        cmocka_unit_test(test_unknown_and_null_are_neutral_inline),
        cmocka_unit_test(test_div_is_block),
        cmocka_unit_test(test_ua_structural_wrappers_have_no_margin),
        cmocka_unit_test(test_ua_spaced_tags_round_trip),
        cmocka_unit_test(test_ua_list_item_is_distinct_but_unspaced),
        cmocka_unit_test(test_block_ua_box_is_content_independent),
        cmocka_unit_test(test_block_ua_box_heading_level_wins),
        cmocka_unit_test(test_block_ua_box_list_item_wins_over_ancestor),
        cmocka_unit_test(test_block_ua_box_is_total),
        cmocka_unit_test(test_table_role_from_tag),
        cmocka_unit_test(test_table_role_display_overrides_tag),
        cmocka_unit_test(test_table_role_is_total),
        cmocka_unit_test(test_ua_case_insensitive_and_trimmed),
        cmocka_unit_test(test_ua_fails_closed),
        cmocka_unit_test(test_ua_code_space_is_total),
        cmocka_unit_test(test_parse_display_keywords),
        cmocka_unit_test(test_parse_display_inline_aliases),
        cmocka_unit_test(test_parse_display_case_and_trim),
        cmocka_unit_test(test_parse_display_errors),
        cmocka_unit_test(test_display_name),
        cmocka_unit_test(test_lp_used_value),
        cmocka_unit_test(test_border_box_height),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
