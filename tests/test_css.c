/*
 * test_css — CMocka suite for the author-CSS parser + simple cascade.
 *
 * Covers inline declaration parsing (every supported property), <style> block
 * parsing with type/class/id/universal/compound/group selectors, the cascade
 * (specificity, document order, inline-wins), inheritance being the caller's job
 * (resolve returns unset for non-matching), and the security rules (url() dropped,
 * @-rules skipped, unknown ignored, malformed never crashes).
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include "css.h"

/* --- inline declarations --- */

static void test_inline_color_and_bg(void **state) {
    (void)state;
    css_style s = css_parse_inline("color:#ff0000; background-color: #00ff00", 0);
    assert_int_equal(s.color, 0xff0000);
    assert_int_equal(s.background, 0x00ff00);
}

static void test_inline_text_align(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("text-align:center", 0).text_align, CSS_ALIGN_CENTER);
    assert_int_equal(css_parse_inline("text-align: RIGHT", 0).text_align, CSS_ALIGN_RIGHT);
    assert_int_equal(css_parse_inline("text-align:justify", 0).text_align, CSS_ALIGN_JUSTIFY);
    assert_int_equal(css_parse_inline("color:red", 0).text_align, CSS_ALIGN_UNSET);
}

static void test_inline_font_size(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("font-size:32px", 0).font_scale, 200);   /* 32/16 */
    assert_int_equal(css_parse_inline("font-size:2em", 0).font_scale, 200);
    assert_int_equal(css_parse_inline("font-size:150%", 0).font_scale, 150);
    assert_int_equal(css_parse_inline("font-size:large", 0).font_scale, 120);
    assert_int_equal(css_parse_inline("font-size:x-large", 0).font_scale, 150);
    assert_int_equal(css_parse_inline("color:red", 0).font_scale, 0);          /* unset */
}

static void test_inline_line_height(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("line-height:1.5", 0).line_scale, 150);  /* unitless */
    assert_int_equal(css_parse_inline("line-height:2", 0).line_scale, 200);
    assert_int_equal(css_parse_inline("line-height:160%", 0).line_scale, 160); /* percent */
    assert_int_equal(css_parse_inline("line-height:normal", 0).line_scale, 0); /* unset */
    assert_int_equal(css_parse_inline("line-height:24px", 0).line_scale, 150);  /* px: 24/16*100 */
    assert_int_equal(css_parse_inline("line-height:1.5em", 0).line_scale, 150); /* em: 1.5*100 */
    assert_int_equal(css_parse_inline("line-height:2rem", 0).line_scale, 200);  /* rem: 2*100 */
    assert_int_equal(css_parse_inline("color:red", 0).line_scale, 0);          /* unset */
    /* Clamped to the anti-DoS range [CSS_LINE_MIN, CSS_LINE_MAX]. */
    assert_int_equal(css_parse_inline("line-height:99", 0).line_scale, CSS_LINE_MAX);
    assert_int_equal(css_parse_inline("line-height:0.1", 0).line_scale, CSS_LINE_MIN);
}

static void test_inline_font_weight_style(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("font-weight:bold", 0).bold, 1);
    assert_int_equal(css_parse_inline("font-weight:700", 0).bold, 1);
    assert_int_equal(css_parse_inline("font-weight:400", 0).bold, 0);
    assert_int_equal(css_parse_inline("font-weight:normal", 0).bold, 0);
    assert_int_equal(css_parse_inline("color:red", 0).bold, -1);               /* unset */
    assert_int_equal(css_parse_inline("font-style:italic", 0).italic, 1);
    assert_int_equal(css_parse_inline("font-style:normal", 0).italic, 0);
    assert_int_equal(css_parse_inline("color:red", 0).italic, -1);
}

static void test_inline_text_decoration(void **state) {
    (void)state;
    /* Single line keywords. */
    assert_int_equal(css_parse_inline("text-decoration:underline", 0).text_decoration,
                     CSS_DECO_UNDERLINE);
    assert_int_equal(css_parse_inline("text-decoration: line-through", 0).text_decoration,
                     CSS_DECO_LINE_THROUGH);
    assert_int_equal(css_parse_inline("text-decoration:OVERLINE", 0).text_decoration,
                     CSS_DECO_OVERLINE);
    /* The -line longhand is an alias. */
    assert_int_equal(css_parse_inline("text-decoration-line:underline", 0).text_decoration,
                     CSS_DECO_UNDERLINE);
    /* none is an explicit value (0), distinct from unset (-1). */
    assert_int_equal(css_parse_inline("text-decoration:none", 0).text_decoration, 0);
    /* Combined keywords OR together; CSS3 style/color/thickness tokens are ignored. */
    assert_int_equal(css_parse_inline("text-decoration:underline overline", 0).text_decoration,
                     CSS_DECO_UNDERLINE | CSS_DECO_OVERLINE);
    assert_int_equal(css_parse_inline("text-decoration:underline wavy red 2px", 0).text_decoration,
                     CSS_DECO_UNDERLINE);
    /* A value with no line keyword at all (only a color) is dropped -> unset. */
    assert_int_equal(css_parse_inline("text-decoration:red", 0).text_decoration, -1);
    /* An unrelated property leaves it unset. */
    assert_int_equal(css_parse_inline("color:red", 0).text_decoration, -1);
}

/* --- text-presentation extensions (Hito 23b-6) --- */

static void test_font_family(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("font-family:serif", 0).font_family, CSS_FF_SERIF);
    assert_int_equal(css_parse_inline("font-family:monospace", 0).font_family, CSS_FF_MONO);
    /* A concrete name maps to its generic bucket; the first recognised entry wins. */
    assert_int_equal(css_parse_inline("font-family:Arial, Helvetica, sans-serif", 0).font_family,
                     CSS_FF_SANS);
    assert_int_equal(css_parse_inline("font-family:'Courier New', monospace", 0).font_family,
                     CSS_FF_MONO);
    /* Multi-word names compare whole; quotes optional. */
    assert_int_equal(css_parse_inline("font-family:\"Times New Roman\"", 0).font_family,
                     CSS_FF_SERIF);
    /* Unknown families fall through to the next entry, then to unset. */
    assert_int_equal(css_parse_inline("font-family:Frobnozz, cursive", 0).font_family,
                     CSS_FF_CURSIVE);
    assert_int_equal(css_parse_inline("font-family:Frobnozz", 0).font_family, CSS_FF_UNSET);
    /* Never phones home. */
    assert_int_equal(css_parse_inline("font-family:url(evil.woff)", 0).font_family, CSS_FF_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).font_family, CSS_FF_UNSET);
}

static void test_text_transform(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("text-transform:uppercase", 0).text_transform,
                     CSS_TT_UPPERCASE);
    assert_int_equal(css_parse_inline("text-transform:LOWERCASE", 0).text_transform,
                     CSS_TT_LOWERCASE);
    assert_int_equal(css_parse_inline("text-transform:capitalize", 0).text_transform,
                     CSS_TT_CAPITALIZE);
    assert_int_equal(css_parse_inline("text-transform:none", 0).text_transform, CSS_TT_NONE);
    assert_int_equal(css_parse_inline("text-transform:full-width", 0).text_transform,
                     CSS_TT_UNSET);  /* out of scope: fail closed */
    assert_int_equal(css_parse_inline("color:red", 0).text_transform, CSS_TT_UNSET);
}

static void test_letter_word_spacing(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("letter-spacing:2px", 0).letter_spacing, 2);
    assert_int_equal(css_parse_inline("letter-spacing:-1px", 0).letter_spacing, -1);
    assert_int_equal(css_parse_inline("letter-spacing:normal", 0).letter_spacing, 0);
    assert_int_equal(css_parse_inline("word-spacing:4px", 0).word_spacing, 4);
    assert_int_equal(css_parse_inline("word-spacing:1em", 0).word_spacing, 16);
    /* %/calc/bare numbers are dropped (fail closed) -> unset sentinel. */
    assert_int_equal(css_parse_inline("letter-spacing:5%", 0).letter_spacing, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).letter_spacing, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).word_spacing, CSS_LEN_UNSET);
    /* Anti-DoS clamp. */
    assert_int_equal(css_parse_inline("letter-spacing:9999px", 0).letter_spacing, CSS_SPACING_MAX);
}

static void test_text_shadow(void **state) {
    (void)state;
    css_style a = css_parse_inline("text-shadow:2px 3px #ff0000", 0);
    assert_int_equal(a.shadow_dx, 2);
    assert_int_equal(a.shadow_dy, 3);
    assert_int_equal(a.shadow_color, 0xff0000);
    /* Blur radius is accepted then ignored; color may come first. */
    css_style b = css_parse_inline("text-shadow:#00ff00 1px 1px 4px", 0);
    assert_int_equal(b.shadow_dx, 1);
    assert_int_equal(b.shadow_dy, 1);
    assert_int_equal(b.shadow_color, 0x00ff00);
    /* No color -> currentColor default (per CSS spec); still a shadow. */
    css_style c = css_parse_inline("text-shadow:2px 2px", 0);
    assert_int_equal(c.shadow_color, CC_COLOR_CURRENT);
    /* none is explicit (color -1). */
    assert_int_equal(css_parse_inline("text-shadow:none", 0).shadow_color, -1);
    /* Too few offsets / url() -> dropped (unset, color -1). */
    assert_int_equal(css_parse_inline("text-shadow:2px", 0).shadow_color, -1);
    assert_int_equal(css_parse_inline("text-shadow:2px 2px url(x)", 0).shadow_color, -1);
    assert_int_equal(css_parse_inline("color:red", 0).shadow_color, -1);
}

static void test_opacity(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("opacity:0.5", 0).opacity, 50);
    assert_int_equal(css_parse_inline("opacity:1", 0).opacity, 100);
    assert_int_equal(css_parse_inline("opacity:0", 0).opacity, 0);
    assert_int_equal(css_parse_inline("opacity:50%", 0).opacity, 50);
    assert_int_equal(css_parse_inline("opacity:2", 0).opacity, 100);   /* clamp */
    assert_int_equal(css_parse_inline("color:red", 0).opacity, -1);    /* unset */
}

static void test_vertical_align(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("vertical-align:super", 0).valign, CSS_VA_SUPER);
    assert_int_equal(css_parse_inline("vertical-align:sub", 0).valign, CSS_VA_SUB);
    assert_int_equal(css_parse_inline("vertical-align:baseline", 0).valign, CSS_VA_BASELINE);
    assert_int_equal(css_parse_inline("vertical-align:middle", 0).valign, CSS_VA_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).valign, CSS_VA_UNSET);
}

static void test_text_indent(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("text-indent:32px", 0).text_indent, 32);
    assert_int_equal(css_parse_inline("text-indent:2em", 0).text_indent, 32);
    assert_int_equal(css_parse_inline("text-indent:-10px", 0).text_indent, -10);
    assert_int_equal(css_parse_inline("text-indent:5%", 0).text_indent, CSS_LEN_UNSET); /* dropped */
    assert_int_equal(css_parse_inline("color:red", 0).text_indent, CSS_LEN_UNSET);
}

static void test_white_space(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("white-space:nowrap", 0).white_space, CSS_WS_NOWRAP);
    assert_int_equal(css_parse_inline("white-space:pre", 0).white_space, CSS_WS_PRE);
    assert_int_equal(css_parse_inline("white-space:normal", 0).white_space, CSS_WS_NORMAL);
    assert_int_equal(css_parse_inline("white-space:pre-wrap", 0).white_space, CSS_WS_PRE_WRAP);
    /* break-spaces collapses to pre-wrap since 2026-07-10 (wrap distinction only) */
    assert_int_equal(css_parse_inline("white-space:break-spaces", 0).white_space, CSS_WS_PRE_WRAP);
    assert_int_equal(css_parse_inline("color:red", 0).white_space, CSS_WS_UNSET);
}

static void test_list_style_type(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("list-style-type:square", 0).list_style, CSS_LS_SQUARE);
    assert_int_equal(css_parse_inline("list-style-type:decimal", 0).list_style, CSS_LS_DECIMAL);
    assert_int_equal(css_parse_inline("list-style-type:lower-alpha", 0).list_style,
                     CSS_LS_LOWER_ALPHA);
    assert_int_equal(css_parse_inline("list-style-type:none", 0).list_style, CSS_LS_NONE);
    /* The shorthand: the recognised type token wins, image url() is ignored. */
    assert_int_equal(css_parse_inline("list-style:square inside", 0).list_style, CSS_LS_SQUARE);
    assert_int_equal(css_parse_inline("list-style:circle url(dot.png)", 0).list_style,
                     CSS_LS_UNSET);  /* url() drops the whole declaration */
    assert_int_equal(css_parse_inline("color:red", 0).list_style, CSS_LS_UNSET);
}

static void test_text_ext_cascade_and_important(void **state) {
    (void)state;
    /* The new props ride the normal cascade: specificity then inline-wins, and
     * !important raises the tier. */
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(
        "p { text-transform: uppercase; font-family: serif; }"
        "p.lead { text-transform: lowercase !important; }", 0, &sh), CSS_OK);
    const char *cls[] = { "lead" };
    css_style s = css_resolve(sh, "p", NULL, cls, 1, "font-family: monospace", 0);
    assert_int_equal(s.text_transform, CSS_TT_LOWERCASE);  /* !important wins */
    assert_int_equal(s.font_family, CSS_FF_MONO);          /* inline wins */
    css_free(sh);
}

static void test_inline_display(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("display:none", 0).display, CSS_DISP_NONE);
    assert_int_equal(css_parse_inline("display:flex", 0).display, CSS_DISP_FLEX);
    assert_int_equal(css_parse_inline("display:grid", 0).display, CSS_DISP_GRID);
    assert_int_equal(css_parse_inline("display:block", 0).display, CSS_DISP_BLOCK);
    assert_int_equal(css_parse_inline("color:red", 0).display, CSS_DISP_UNSET);
}

/* --- flex/grid container props (Hito 23b-2) --- */

static void test_inline_container_props(void **state) {
    (void)state;
    css_style f = css_parse_inline("display:flex; gap:12px; justify-content:center", 0);
    assert_int_equal(f.display, CSS_DISP_FLEX);
    assert_int_equal(f.gap, 12);
    assert_int_equal(f.justify, CSS_JUSTIFY_CENTER);
    assert_int_equal(f.grid_cols, 0);  /* not a grid */

    css_style g = css_parse_inline("display:grid; grid-template-columns:1fr 1fr 1fr", 0);
    assert_int_equal(g.display, CSS_DISP_GRID);
    assert_int_equal(g.grid_cols, 3);

    /* every justify-content keyword maps to its css_justify. */
    assert_int_equal(css_parse_inline("justify-content:flex-start", 0).justify, CSS_JUSTIFY_START);
    assert_int_equal(css_parse_inline("justify-content:start", 0).justify, CSS_JUSTIFY_START);
    assert_int_equal(css_parse_inline("justify-content:flex-end", 0).justify, CSS_JUSTIFY_END);
    assert_int_equal(css_parse_inline("justify-content:space-between", 0).justify, CSS_JUSTIFY_SPACE_BETWEEN);
    assert_int_equal(css_parse_inline("justify-content:space-around", 0).justify, CSS_JUSTIFY_SPACE_AROUND);
    assert_int_equal(css_parse_inline("justify-content:space-evenly", 0).justify, CSS_JUSTIFY_SPACE_EVENLY);

    /* gap aliases; a two-value gap is row then column (2026-07-10). */
    assert_int_equal(css_parse_inline("grid-gap:8px", 0).gap, 8);
    assert_int_equal(css_parse_inline("column-gap:6px", 0).gap, 6);
    assert_int_equal(css_parse_inline("gap:10px 4px", 0).gap, 4);
    assert_int_equal(css_parse_inline("gap:10px 4px", 0).row_gap, 10);
    assert_int_equal(css_parse_inline("gap:normal", 0).gap, 0);
}

static void test_sheet_container_props(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(
        ".row { display:flex; gap:16px; justify-content:space-between }\n"
        "#g { display:grid; grid-template-columns:1fr 1fr 1fr 1fr }", 0, &sh), CSS_OK);

    const char *row[] = { "row" };
    css_style f = css_resolve(sh, "div", NULL, row, 1, NULL, 0);
    assert_int_equal(f.display, CSS_DISP_FLEX);
    assert_int_equal(f.gap, 16);
    assert_int_equal(f.justify, CSS_JUSTIFY_SPACE_BETWEEN);

    css_style g = css_resolve(sh, "section", "g", NULL, 0, NULL, 0);
    assert_int_equal(g.display, CSS_DISP_GRID);
    assert_int_equal(g.grid_cols, 4);
    css_free(sh);
}

/* The container props go through the full cascade: inline beats the sheet. */
static void test_container_cascade_inline_wins(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(".row{display:flex;gap:4px;justify-content:center}", 0, &sh), CSS_OK);
    const char *row[] = { "row" };
    css_style s = css_resolve(sh, "div", NULL, row, 1,
                              "gap:20px; justify-content:flex-end", 0);
    assert_int_equal(s.display, CSS_DISP_FLEX);   /* from the sheet */
    assert_int_equal(s.gap, 20);                  /* inline wins */
    assert_int_equal(s.justify, CSS_JUSTIFY_END); /* inline wins */
    css_free(sh);
}

/* Fail closed: a bad justify keyword is dropped (unset); grid-template-columns:none
 * is unset; gap and column count are clamped to their anti-DoS bounds. */
static void test_container_fail_closed_and_bounds(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("justify-content:bogus", 0).justify, CSS_JUSTIFY_UNSET);
    assert_int_equal(css_parse_inline("gap:abc", 0).gap, -1);          /* not a number */
    assert_int_equal(css_parse_inline("grid-template-columns:none", 0).grid_cols, 0);
    assert_int_equal(css_parse_inline("gap:999999px", 0).gap, CSS_GAP_MAX); /* clamped */

    /* A declaration value longer than the per-declaration value cap (CSS_URL_MAX,
     * widened 2026-07-16 so a background-image url() with a realistic CDN query
     * string is not itself dropped) is still dropped entirely (fail closed,
     * anti-DoS) — never silently truncated. The short display:grid declaration
     * in the same block still parses. */
    char buf[CSS_URL_MAX + 512];
    int r0 = snprintf(buf, sizeof buf, "display:grid;grid-template-columns:");
    assert_true(r0 > 0 && (size_t)r0 < sizeof buf);
    size_t k = (size_t)r0;
    for (int i = 0; i < CSS_URL_MAX; ++i) {
        size_t space = sizeof buf - k;
        if (space == 0) break;
        int r = snprintf(buf + k, space, "1fr ");
        if (r < 0 || (size_t)r >= space) break;
        k += (size_t)r;
    }
    css_style s = css_parse_inline(buf, 0);
    assert_int_equal(s.display, CSS_DISP_GRID);
    assert_int_equal(s.grid_cols, 0);
}

/* repeat()/minmax() track-count correctness (Hito: CSS layout expansion). Track
 * SIZES still are not resolved (every track lays out equal-width downstream), but
 * the COUNT is now correct instead of naive whitespace tokenization. */
static void test_grid_track_sizes_resolved(void **state) {
    (void)state;
    /* fr weights encode as -(N*100); px as positive px; auto as 0 */
    css_style s = css_parse_inline("grid-template-columns: 2fr 1fr", 0);
    assert_int_equal(s.grid_cols, 2);
    assert_int_equal(s.grid_col_w[0], -200);
    assert_int_equal(s.grid_col_w[1], -100);
    s = css_parse_inline("grid-template-columns: 200px 1fr auto", 0);
    assert_int_equal(s.grid_cols, 3);
    assert_int_equal(s.grid_col_w[0], 200);
    assert_int_equal(s.grid_col_w[1], -100);
    assert_int_equal(s.grid_col_w[2], 0);
    /* minmax takes its max component; repeat replicates the pattern's sizes */
    s = css_parse_inline("grid-template-columns: repeat(2, minmax(100px, 1fr))", 0);
    assert_int_equal(s.grid_cols, 2);
    assert_int_equal(s.grid_col_w[0], -100);
    assert_int_equal(s.grid_col_w[1], -100);
    /* tracks past CSS_GRID_TRACKS_MAX still count but stay auto */
    s = css_parse_inline("grid-template-columns: repeat(12, 2fr)", 0);
    assert_int_equal(s.grid_cols, 12);
    assert_int_equal(s.grid_col_w[0], -200);
    assert_int_equal(s.grid_col_w[CSS_GRID_TRACKS_MAX - 1], -200);
    /* fractional fr and unknown tokens */
    s = css_parse_inline("grid-template-columns: 1.5fr min-content", 0);
    assert_int_equal(s.grid_cols, 2);
    assert_int_equal(s.grid_col_w[0], -150);
    assert_int_equal(s.grid_col_w[1], 0);   /* unknown -> auto share */
}

static void test_grid_repeat_expands_count(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("grid-template-columns: repeat(3, 1fr)", 0).grid_cols, 3);
    assert_int_equal(
        css_parse_inline("grid-template-columns: repeat(2, 100px 1fr)", 0).grid_cols, 4);
    assert_int_equal(
        css_parse_inline("grid-template-columns: 200px repeat(3, 1fr) 100px", 0).grid_cols, 5);
    assert_int_equal(
        css_parse_inline("grid-template-rows: repeat(4, auto)", 0).grid_rows, 4);
}

static void test_grid_minmax_counts_as_one_track(void **state) {
    (void)state;
    assert_int_equal(
        css_parse_inline("grid-template-columns: minmax(100px, 1fr) 1fr", 0).grid_cols, 2);
    assert_int_equal(
        css_parse_inline("grid-template-columns: repeat(2, minmax(50px, 1fr))", 0).grid_cols, 2);
}

static void test_grid_repeat_autofill_fails_closed(void **state) {
    (void)state;
    /* auto-fill/auto-fit need an available width this pure parser does not have:
     * fail closed (unset), never a wrong guess. */
    assert_int_equal(
        css_parse_inline("grid-template-columns: repeat(auto-fill, 100px)", 0).grid_cols, 0);
    assert_int_equal(
        css_parse_inline("grid-template-columns: repeat(auto-fit, minmax(100px,1fr))", 0)
            .grid_cols, 0);
}

static void test_grid_repeat_malformed_fails_closed(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("grid-template-columns: repeat(3 1fr)", 0).grid_cols, 0);
    assert_int_equal(css_parse_inline("grid-template-columns: repeat(0, 1fr)", 0).grid_cols, 0);
    assert_int_equal(css_parse_inline("grid-template-columns: repeat(abc, 1fr)", 0).grid_cols, 0);
}

static void test_grid_repeat_clamped_anti_dos(void **state) {
    (void)state;
    assert_int_equal(
        css_parse_inline("grid-template-columns: repeat(999, 1fr)", 0).grid_cols,
        (int)CSS_GRID_COLS_MAX);
}

static void test_container_unset(void **state) {
    (void)state;
    css_style s = css_parse_inline("color:red", 0);
    assert_int_equal(s.gap, -1);
    assert_int_equal(s.justify, CSS_JUSTIFY_UNSET);
    assert_int_equal(s.grid_cols, 0);
}

/* --- security: never phone home, ignore junk --- */

static void test_url_value_dropped(void **state) {
    (void)state;
    /* A background with url() must NOT fetch, but the colour part IS honoured. */
    assert_int_equal(css_parse_inline("background: url(http://evil/x.png) #112233", 0).background, 0x112233);
    /* A bare url() with no colour still yields -1. */
    assert_int_equal(css_parse_inline("background: url(http://evil/x.png)", 0).background, -1);
    /* A plain color background is fine. */
    assert_int_equal(css_parse_inline("background:#112233", 0).background, 0x112233);
}

static void test_unknown_props_ignored(void **state) {
    (void)state;
    css_style s = css_parse_inline("position:absolute; z-index:9; color:#abcdef; --x:1", 0);
    assert_int_equal(s.color, 0xabcdef);
    assert_int_equal(s.text_align, CSS_ALIGN_UNSET);
}

/* --- linear-gradient backgrounds (2026-07-11) --- */

static void test_linear_gradient_basic(void **state) {
    (void)state;
    css_style s = css_parse_inline("background: linear-gradient(to right, #ff0000, #0000ff)", 0);
    assert_int_equal(s.bg_grad_n, 2);
    assert_int_equal(s.bg_grad_angle, 90);
    assert_int_equal(s.bg_grad_c[0], 0xff0000);
    assert_int_equal(s.bg_grad_c[1], 0x0000ff);
    /* the background shorthand with a gradient resets the color part */
    assert_int_equal(s.background, -1);
}

static void test_linear_gradient_directions(void **state) {
    (void)state;
    /* no direction -> default 180 (to bottom) */
    assert_int_equal(css_parse_inline(
        "background-image: linear-gradient(red, blue)", 0).bg_grad_angle, 180);
    /* angle form, and a negative angle normalizes mod 360 */
    assert_int_equal(css_parse_inline(
        "background-image: linear-gradient(45deg, red, blue)", 0).bg_grad_angle, 45);
    assert_int_equal(css_parse_inline(
        "background-image: linear-gradient(-90deg, red, blue)", 0).bg_grad_angle, 270);
    /* corner keywords, either order */
    assert_int_equal(css_parse_inline(
        "background-image: linear-gradient(to top right, red, blue)", 0).bg_grad_angle, 45);
    assert_int_equal(css_parse_inline(
        "background-image: linear-gradient(to right top, red, blue)", 0).bg_grad_angle, 45);
    assert_int_equal(css_parse_inline(
        "background-image: linear-gradient(to left, red, blue)", 0).bg_grad_angle, 270);
}

static void test_linear_gradient_stops(void **state) {
    (void)state;
    /* stop positions are accepted but ignored (evenly spaced) */
    css_style s = css_parse_inline(
        "background: linear-gradient(to bottom, #111111 0%, #222222 100%)", 0);
    assert_int_equal(s.bg_grad_n, 2);
    assert_int_equal(s.bg_grad_c[0], 0x111111);
    assert_int_equal(s.bg_grad_c[1], 0x222222);
    /* three stops resolve; more than CSS_GRAD_STOPS_MAX keep the first four */
    s = css_parse_inline(
        "background-image: linear-gradient(red, #00ff00, blue)", 0);
    assert_int_equal(s.bg_grad_n, 3);
    assert_int_equal(s.bg_grad_c[1], 0x00ff00);
    s = css_parse_inline(
        "background: linear-gradient(red, blue, green, yellow, white)", 0);
    assert_int_equal(s.bg_grad_n, CSS_GRAD_STOPS_MAX);
}

static void test_linear_gradient_fail_closed(void **state) {
    (void)state;
    /* fewer than 2 stops, junk color, or a non-linear gradient function: all unset */
    assert_int_equal(css_parse_inline("background: linear-gradient(red)", 0).bg_grad_n, 0);
    assert_int_equal(css_parse_inline(
        "background: linear-gradient(red, bogusnothing)", 0).bg_grad_n, 0);
    assert_int_equal(css_parse_inline(
        "background: radial-gradient(red, blue)", 0).bg_grad_n, 0);
    assert_int_equal(css_parse_inline(
        "background-image: repeating-linear-gradient(red, blue)", 0).bg_grad_n, 0);
    assert_int_equal(css_parse_inline(
        "background-image: conic-gradient(red, blue)", 0).bg_grad_n, 0);
    /* url() in background-image never fetches and never becomes a gradient */
    assert_int_equal(css_parse_inline(
        "background-image: url(http://evil/x.png)", 0).bg_grad_n, 0);
    /* the color-extraction path of the background shorthand is unchanged */
    css_style s = css_parse_inline("background: url(http://evil/x.png) #112233", 0);
    assert_int_equal(s.bg_grad_n, 0);
    assert_int_equal(s.background, 0x112233);
}

static void test_background_shorthand_resets_gradient(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(
        "div { background: linear-gradient(red, blue) }\n"
        ".flat { background: #333333 }\n"
        "#grad { background: linear-gradient(to right, #aaaaaa, #bbbbbb) }", 0, &sh), CSS_OK);
    /* higher-specificity plain color CLEARS a lower-tier gradient (shorthand reset) */
    const char *flat[] = { "flat" };
    css_style a = css_resolve(sh, "div", NULL, flat, 1, NULL, 0);
    assert_int_equal(a.background, 0x333333);
    assert_int_equal(a.bg_grad_n, 0);
    /* and a higher-specificity gradient CLEARS a lower-tier color */
    css_style b = css_resolve(sh, "div", "grad", NULL, 0, NULL, 0);
    assert_int_equal(b.bg_grad_n, 2);
    assert_int_equal(b.background, -1);
    css_free(sh);
}

/* --- background-image: url(...) (2026-07-16) --- */

static void test_bg_image_url_basic(void **state) {
    (void)state;
    css_style s = css_parse_inline("background-image: url(hero.jpg)", 0);
    assert_string_equal(s.bg_image_url, "hero.jpg");
    assert_int_equal(s.bg_grad_n, 0);  /* mutually exclusive with the gradient slot */
}

static void test_bg_image_url_quoted(void **state) {
    (void)state;
    assert_string_equal(css_parse_inline(
        "background-image: url('a/b.png')", 0).bg_image_url, "a/b.png");
    assert_string_equal(css_parse_inline(
        "background-image: url(\"a/b.png\")", 0).bg_image_url, "a/b.png");
    /* bare, with internal whitespace trimmed */
    assert_string_equal(css_parse_inline(
        "background-image: url(  hero.jpg  )", 0).bg_image_url, "hero.jpg");
}

static void test_bg_image_url_absolute(void **state) {
    (void)state;
    /* an absolute https URL is captured raw -- css.c never fetches it, resolving
     * and deciding whether to fetch happens downstream (render_doc.c) */
    assert_string_equal(css_parse_inline(
        "background-image: url(https://cdn.example.com/hero.jpg?w=1200)", 0).bg_image_url,
        "https://cdn.example.com/hero.jpg?w=1200");
}

static void test_bg_image_url_none_and_junk_reset(void **state) {
    (void)state;
    assert_string_equal(css_parse_inline("background-image: none", 0).bg_image_url, "");
    assert_string_equal(css_parse_inline(
        "background-image: radial-gradient(red, blue)", 0).bg_image_url, "");
    /* malformed url(...) (unbalanced paren) resets rather than half-capturing */
    assert_string_equal(css_parse_inline(
        "background-image: url(hero.jpg", 0).bg_image_url, "");
    /* multi-layer (comma-separated) is out of v1 scope: fails closed to unset,
     * never silently keeps just the first layer */
    assert_string_equal(css_parse_inline(
        "background-image: url(a.png), url(b.png)", 0).bg_image_url, "");
}

static void test_bg_image_url_overlong_fails_closed(void **state) {
    (void)state;
    char big[CSS_URL_MAX + 64];
    memset(big, 'a', sizeof big - 1);
    big[sizeof big - 1] = '\0';
    char val[sizeof big + 32];
    snprintf(val, sizeof val, "background-image: url(%s.png)", big);
    /* an overlong url() text is dropped, fail closed -- never truncated-and-kept
     * (a truncated URL could resolve to a completely different, attacker-chosen
     * resource) */
    assert_string_equal(css_parse_inline(val, 0).bg_image_url, "");
}

static void test_bg_image_url_gradient_mutually_exclusive(void **state) {
    (void)state;
    /* a valid gradient wins and explicitly clears any image */
    css_style s = css_parse_inline("background-image: linear-gradient(red, blue)", 0);
    assert_int_equal(s.bg_grad_n, 2);
    assert_string_equal(s.bg_image_url, "");
}

static void test_bg_shorthand_captures_url_and_resets_color(void **state) {
    (void)state;
    css_style s = css_parse_inline("background: url(hero.jpg)", 0);
    assert_string_equal(s.bg_image_url, "hero.jpg");
    assert_int_equal(s.background, -1);
    assert_int_equal(s.bg_grad_n, 0);
    /* a plain color shorthand resets a previously-set image the same way it
     * already resets a gradient (cascade winner tracking) */
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(
        "div { background: url(hero.jpg) }\n"
        ".flat { background: #333333 }", 0, &sh), CSS_OK);
    const char *flat[] = { "flat" };
    css_style a = css_resolve(sh, "div", NULL, flat, 1, NULL, 0);
    assert_int_equal(a.background, 0x333333);
    assert_string_equal(a.bg_image_url, "");
    css_free(sh);
}

static void test_bg_size_and_repeat(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline(
        "background-size: cover", 0).bg_size, CSS_BGS_COVER);
    assert_int_equal(css_parse_inline(
        "background-size: contain", 0).bg_size, CSS_BGS_CONTAIN);
    assert_int_equal(css_parse_inline(
        "background-size: auto", 0).bg_size, CSS_BGS_AUTO);
    assert_int_equal(css_parse_inline(
        "background-repeat: repeat-x", 0).bg_repeat, CSS_BGR_REPEAT_X);
    assert_int_equal(css_parse_inline(
        "background-repeat: no-repeat", 0).bg_repeat, CSS_BGR_NO_REPEAT);
}

static void test_malformed_inline_no_crash(void **state) {
    (void)state;
    css_style s = css_parse_inline(";;: ; color ; :red; color::; color:#777;;", 0);
    assert_int_equal(s.color, 0x777777);
}

/* --- custom properties (--name) + var() --- */

static void test_custom_prop_var_basic(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(":root{--brand:#ff6600;} .btn{color:var(--brand);}", 0, &sh),
                     CSS_OK);
    const char *cl[] = { "btn" };
    css_style s = css_resolve(sh, "div", NULL, cl, 1, NULL, 0);
    assert_int_equal(s.color, 0xff6600);
    css_free(sh);
}

static void test_custom_prop_var_fallback_used_when_missing(void **state) {
    (void)state;
    css_style s = css_parse_inline("color: var(--missing, #123456)", 0);
    assert_int_equal(s.color, 0x123456);
}

static void test_custom_prop_var_no_fallback_drops_decl(void **state) {
    (void)state;
    /* No matching custom property and no fallback: the whole declaration is
     * invalid (fail closed), not silently coerced into some default. */
    css_style s = css_parse_inline("color: var(--missing); background: #00ff00", 0);
    assert_int_equal(s.color, -1);
    assert_int_equal(s.background, 0x00ff00);
}

static void test_custom_prop_var_chain(void **state) {
    (void)state;
    /* --b references --a: chained lookups resolve within CSS_VAR_MAX_DEPTH. */
    css_style s = css_parse_inline(
        "--a: #abcdef; --b: var(--a); color: var(--b)", 0);
    assert_int_equal(s.color, 0xabcdef);
}

static void test_custom_prop_var_self_reference_fails_closed(void **state) {
    (void)state;
    /* A cyclic reference never infinite-loops or crashes: it just fails to
     * resolve past CSS_VAR_MAX_DEPTH, dropping the declaration. */
    css_style s = css_parse_inline("--a: var(--a); color: var(--a); background: #010101", 0);
    assert_int_equal(s.color, -1);
    assert_int_equal(s.background, 0x010101);
}

static void test_custom_prop_var_in_shorthand(void **state) {
    (void)state;
    /* var() can resolve just a fragment of a multi-value shorthand. */
    css_style s = css_parse_inline("--gap: 12px; margin: var(--gap) auto", 0);
    assert_int_equal(s.margin_top, 12);
    assert_int_equal(s.margin_bottom, 12);
    assert_int_equal(s.margin_left, CSS_LEN_AUTO);
    assert_int_equal(s.margin_right, CSS_LEN_AUTO);
}

static void test_custom_prop_var_later_declaration_wins(void **state) {
    (void)state;
    /* Global-pool simplification: the LAST --name declaration in the whole
     * stylesheet wins, regardless of which rule declared it. */
    css_sheet *sh = NULL;
    assert_int_equal(
        css_parse(":root{--c:#111111;} .later{--c:#222222;} p{color:var(--c);}", 0, &sh),
        CSS_OK);
    css_style s = css_resolve(sh, "p", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.color, 0x222222);
    css_free(sh);
}

static void test_custom_prop_var_unbalanced_paren_drops(void **state) {
    (void)state;
    css_style s = css_parse_inline("color: var(--a; background:#00ff00", 0);
    assert_int_equal(s.color, -1);
    assert_int_equal(s.background, 0x00ff00);
}

static void test_custom_prop_var_never_phones_home(void **state) {
    (void)state;
    /* A custom property whose value contains url() — colour IS honoured,
     * the URL is never fetched. */
    css_style s = css_parse_inline(
        "--evil: url(http://evil/x.png) #112233; background: var(--evil)", 0);
    assert_int_equal(s.background, 0x112233);
    /* A var() resolved to bare url() with no colour still yields -1. */
    s = css_parse_inline("--bg: url(http://evil/x.png); background: var(--bg)", 0);
    assert_int_equal(s.background, -1);
}

/* --- <style> block parsing + selectors --- */

static void test_sheet_type_selector(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("p { color: #010203; }", 0, &sh), CSS_OK);
    css_style s = css_resolve(sh, "p", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.color, 0x010203);
    /* a different tag does not match. */
    assert_int_equal(css_resolve(sh, "div", NULL, NULL, 0, NULL, 0).color, -1);
    css_free(sh);
}

static void test_sheet_class_and_id(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(".note{color:#111111} #main{color:#222222}", 0, &sh), CSS_OK);
    const char *cl[] = { "note" };
    assert_int_equal(css_resolve(sh, "div", NULL, cl, 1, NULL, 0).color, 0x111111);
    assert_int_equal(css_resolve(sh, "div", "main", NULL, 0, NULL, 0).color, 0x222222);
    css_free(sh);
}

static void test_sheet_universal_and_group(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("* { text-align:center }\n h1, h2 { color:#0000ff }", 0, &sh), CSS_OK);
    assert_int_equal(css_resolve(sh, "span", NULL, NULL, 0, NULL, 0).text_align, CSS_ALIGN_CENTER);
    assert_int_equal(css_resolve(sh, "h2", NULL, NULL, 0, NULL, 0).color, 0x0000ff);
    assert_int_equal(css_resolve(sh, "h3", NULL, NULL, 0, NULL, 0).color, -1);
    css_free(sh);
}

static void test_sheet_compound_selector(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("a.button { color:#0a0b0c }", 0, &sh), CSS_OK);
    const char *btn[] = { "button" };
    const char *other[] = { "link" };
    assert_int_equal(css_resolve(sh, "a", NULL, btn, 1, NULL, 0).color, 0x0a0b0c);
    assert_int_equal(css_resolve(sh, "a", NULL, other, 1, NULL, 0).color, -1);  /* class mismatch */
    assert_int_equal(css_resolve(sh, "p", NULL, btn, 1, NULL, 0).color, -1);    /* tag mismatch */
    css_free(sh);
}

/* Builds one css_element node aliasing the given fields (test-local helper). */
static css_element el_node(const char *tag, const char *id,
                           const char *const *classes, size_t nc,
                           const css_element *parent) {
    css_element e;
    e.tag = tag; e.id = id; e.classes = classes; e.nclasses = nc;
    e.attrs = NULL; e.nattrs = 0; e.parent = parent;
    e.nth = 0; e.nsib = 0; e.prev = NULL;   /* sibling context unknown by default */
    e.nth_of_type = 0; e.nsib_of_type = 0; e.child_count = -1;
    return e;
}

/* Like el_node but with the sibling context (nth/nsib/prev) populated. */
static css_element el_sib_node(const char *tag, int nth, int nsib,
                               const css_element *prev, const css_element *parent) {
    css_element e = el_node(tag, NULL, NULL, 0, parent);
    e.nth = nth; e.nsib = nsib; e.prev = prev;
    e.nth_of_type = 0; e.nsib_of_type = 0; e.child_count = -1;
    return e;
}

/* R2: like el_sib_node but also sets the of-type sibling context. */
static css_element el_type_node(const char *tag, int nth, int nsib,
                                int nth_of_type, int nsib_of_type,
                                int child_count,
                                const css_element *prev, const css_element *parent) {
    css_element e = el_sib_node(tag, nth, nsib, prev, parent);
    e.nth_of_type = nth_of_type; e.nsib_of_type = nsib_of_type;
    e.child_count = child_count;
    return e;
}

/* Like el_node but also carries an attribute list (for [attr] selectors). */
static css_element el_attr_node(const char *tag, const char *id,
                                const char *const *classes, size_t nc,
                                const css_attr *attrs, size_t na,
                                const css_element *parent) {
    css_element e = el_node(tag, id, classes, nc, parent);
    e.attrs = attrs; e.nattrs = na;
    return e;
}

static void test_text_decoration_cascade(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* A sheet rule sets it; the nearest ancestor that declares it wins (like color),
     * and an inline `none` overrides the sheet underline (explicit removal). */
    assert_int_equal(css_parse("a{text-decoration:underline} .q{text-decoration:line-through}",
                               0, &sh), CSS_OK);
    css_element a = el_node("a", NULL, NULL, 0, NULL);
    assert_int_equal(css_resolve_el(sh, &a, NULL, 0).text_decoration, CSS_DECO_UNDERLINE);
    assert_int_equal(css_resolve_el(sh, &a, "text-decoration:none", 0).text_decoration, 0);
    const char *q[] = { "q" };
    css_element span = el_node("span", NULL, q, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &span, NULL, 0).text_decoration, CSS_DECO_LINE_THROUGH);
    /* No declaration anywhere -> unset. */
    css_element p = el_node("p", NULL, NULL, 0, NULL);
    assert_int_equal(css_resolve_el(sh, &p, NULL, 0).text_decoration, -1);
    css_free(sh);
}

static void test_descendant_combinator(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* "div p" now MATCHES a p with a div ancestor (through any depth). */
    assert_int_equal(css_parse("div p { color:#999999 }", 0, &sh), CSS_OK);
    css_element div = el_node("div", NULL, NULL, 0, NULL);
    css_element span = el_node("span", NULL, NULL, 0, &div);
    css_element p = el_node("p", NULL, NULL, 0, &span);   /* p > span > div */
    assert_int_equal(css_resolve_el(sh, &p, NULL, 0).color, 0x999999);
    css_element lone = el_node("p", NULL, NULL, 0, NULL); /* no div ancestor */
    assert_int_equal(css_resolve_el(sh, &lone, NULL, 0).color, -1);
    /* css_resolve (no ancestor context) never matches through a combinator. */
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, -1);
    css_free(sh);
}

static void test_child_combinator(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("div > p { color:#111111 }", 0, &sh), CSS_OK);
    css_element div = el_node("div", NULL, NULL, 0, NULL);
    css_element pc = el_node("p", NULL, NULL, 0, &div);   /* direct child: matches */
    assert_int_equal(css_resolve_el(sh, &pc, NULL, 0).color, 0x111111);
    css_element span = el_node("span", NULL, NULL, 0, &div);
    css_element pg = el_node("p", NULL, NULL, 0, &span);  /* grandchild: child combinator fails */
    assert_int_equal(css_resolve_el(sh, &pg, NULL, 0).color, -1);
    css_free(sh);
}

static void test_combinator_specificity_sum(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* div p (spec 2) beats p (spec 1); #m p (spec 101) beats div p (spec 2). */
    assert_int_equal(css_parse("p{color:#ff0000} div p{color:#00ff00} #m p{color:#0000ff}",
                               0, &sh), CSS_OK);
    css_element div_plain = el_node("div", NULL, NULL, 0, NULL);
    css_element p1 = el_node("p", NULL, NULL, 0, &div_plain);
    assert_int_equal(css_resolve_el(sh, &p1, NULL, 0).color, 0x00ff00); /* div p > p */
    css_element div_m = el_node("div", "m", NULL, 0, NULL);
    css_element p2 = el_node("p", NULL, NULL, 0, &div_m);
    assert_int_equal(css_resolve_el(sh, &p2, NULL, 0).color, 0x0000ff); /* #m p wins */
    css_free(sh);
}

static void test_combinator_class_chain(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(".nav .item a { color:#0a0a0a }", 0, &sh), CSS_OK);
    const char *nav[] = { "nav" };
    const char *item[] = { "item" };
    css_element navdiv = el_node("div", NULL, nav, 1, NULL);
    css_element li     = el_node("li", NULL, item, 1, &navdiv);
    css_element a      = el_node("a", NULL, NULL, 0, &li);
    assert_int_equal(css_resolve_el(sh, &a, NULL, 0).color, 0x0a0a0a);
    /* Missing the .nav ancestor -> no match (fail closed). */
    css_element li2 = el_node("li", NULL, item, 1, NULL);
    css_element a2  = el_node("a", NULL, NULL, 0, &li2);
    assert_int_equal(css_resolve_el(sh, &a2, NULL, 0).color, -1);
    css_free(sh);
}

/* --- sibling combinators + pseudo-classes (Hito 23b-9) --- */

static void test_adjacent_sibling_combinator(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("h1 + p { color:#111111 }", 0, &sh), CSS_OK);
    css_element h1 = el_sib_node("h1", 1, 3, NULL, NULL);
    css_element p1 = el_sib_node("p", 2, 3, &h1, NULL);   /* right after the h1 */
    assert_int_equal(css_resolve_el(sh, &p1, NULL, 0).color, 0x111111);
    css_element p2 = el_sib_node("p", 3, 3, &p1, NULL);   /* one further: no match */
    assert_int_equal(css_resolve_el(sh, &p2, NULL, 0).color, -1);
    /* No prev link (unknown sibling context) -> fail closed. */
    css_element lone = el_sib_node("p", 0, 0, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &lone, NULL, 0).color, -1);
    css_free(sh);
}

static void test_general_sibling_combinator(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("h1 ~ p { color:#222222 }", 0, &sh), CSS_OK);
    css_element h1 = el_sib_node("h1", 1, 4, NULL, NULL);
    css_element d  = el_sib_node("div", 2, 4, &h1, NULL);
    css_element p1 = el_sib_node("p", 3, 4, &d, NULL);    /* h1 earlier, not adjacent */
    assert_int_equal(css_resolve_el(sh, &p1, NULL, 0).color, 0x222222);
    /* No h1 anywhere before -> no match. */
    css_element d0 = el_sib_node("div", 1, 2, NULL, NULL);
    css_element p0 = el_sib_node("p", 2, 2, &d0, NULL);
    assert_int_equal(css_resolve_el(sh, &p0, NULL, 0).color, -1);
    css_free(sh);
}

static void test_sibling_mixed_with_child(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* Mixed chain: subject p, adjacent p before it, div parent required. */
    assert_int_equal(css_parse("div > p + p { color:#333333 }", 0, &sh), CSS_OK);
    css_element div = el_node("div", NULL, NULL, 0, NULL);
    css_element pa = el_sib_node("p", 1, 2, NULL, &div);
    css_element pb = el_sib_node("p", 2, 2, &pa, &div);
    assert_int_equal(css_resolve_el(sh, &pb, NULL, 0).color, 0x333333);
    /* Same siblings under a section parent: the child combinator fails. */
    css_element sec = el_node("section", NULL, NULL, 0, NULL);
    css_element qa = el_sib_node("p", 1, 2, NULL, &sec);
    css_element qb = el_sib_node("p", 2, 2, &qa, &sec);
    assert_int_equal(css_resolve_el(sh, &qb, NULL, 0).color, -1);
    css_free(sh);
}

static void test_pseudo_link(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("a:link{text-decoration:none} :any-link{color:#010203}",
                               0, &sh), CSS_OK);
    /* Zero Knowledge: no history, every link is unvisited -> :link matches a[href]. */
    css_attr href[] = { { "href", "https://example.com/" } };
    css_element a = el_attr_node("a", NULL, NULL, 0, href, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &a, NULL, 0).text_decoration, 0);
    assert_int_equal(css_resolve_el(sh, &a, NULL, 0).color, 0x010203);
    /* An <a> without href is not a link; a <span> with href is not either. */
    css_element bare = el_node("a", NULL, NULL, 0, NULL);
    assert_int_equal(css_resolve_el(sh, &bare, NULL, 0).text_decoration, -1);
    css_element span = el_attr_node("span", NULL, NULL, 0, href, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &span, NULL, 0).color, -1);
    css_free(sh);
}

static void test_pseudo_never_match_keeps_group(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* :visited never matches (no history by design); :hover/:focus/:active
     * now always match (PSEUDO_ALWAYS) so that content hidden behind hover
     * becomes visible. The selectors still PARSE, so the comma group and
     * the rest of the sheet survive. The last matching rule wins (same
     * specificity, all 0,0,1,0): a:active. */
    assert_int_equal(css_parse("a:visited, b{color:#040404} a:hover{color:#050505} "
                                "a:focus{color:#060606} a:active{color:#070707}",
                                0, &sh), CSS_OK);
    css_attr href[] = { { "href", "/x" } };
    css_element a = el_attr_node("a", NULL, NULL, 0, href, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &a, NULL, 0).color, 0x070707);
    css_element b = el_node("b", NULL, NULL, 0, NULL);
    assert_int_equal(css_resolve_el(sh, &b, NULL, 0).color, 0x040404);
    css_free(sh);
}

static void test_pseudo_structural(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("li:first-child{color:#0a0000} li:last-child{color:#000a00} "
                               "li:only-child{background:#00000a}", 0, &sh), CSS_OK);
    css_element first = el_sib_node("li", 1, 3, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &first, NULL, 0).color, 0x0a0000);
    css_element last = el_sib_node("li", 3, 3, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &last, NULL, 0).color, 0x000a00);
    css_element only = el_sib_node("li", 1, 1, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &only, NULL, 0).background, 0x00000a);
    /* An only child is first AND last; equal specificity, so the later rule
     * (last-child) wins by document order. */
    assert_int_equal(css_resolve_el(sh, &only, NULL, 0).color, 0x000a00);
    /* Unknown sibling context (nth/nsib = 0) -> fail closed, no match. */
    css_element unk = el_sib_node("li", 0, 0, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &unk, NULL, 0).color, -1);
    css_free(sh);
}

static void test_pseudo_nth_child(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("tr:nth-child(even){background:#0e0e0e} "
                               "tr:nth-child(odd){background:#0d0d0d} "
                               "li:nth-child(3){color:#030303} "
                               "li:nth-child(3n+1){background:#310031} "
                               "li:nth-child(-n+2){color:#0000f2}", 0, &sh), CSS_OK);
    css_element tr2 = el_sib_node("tr", 2, 9, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &tr2, NULL, 0).background, 0x0e0e0e);
    css_element tr7 = el_sib_node("tr", 7, 9, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &tr7, NULL, 0).background, 0x0d0d0d);
    css_element li3 = el_sib_node("li", 3, 9, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &li3, NULL, 0).color, 0x030303);
    css_element li4 = el_sib_node("li", 4, 9, NULL, NULL);   /* 3n+1: 1,4,7 */
    assert_int_equal(css_resolve_el(sh, &li4, NULL, 0).background, 0x310031);
    css_element li1 = el_sib_node("li", 1, 9, NULL, NULL);   /* -n+2: 1,2 */
    assert_int_equal(css_resolve_el(sh, &li1, NULL, 0).color, 0x0000f2);
    css_element li5 = el_sib_node("li", 5, 9, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &li5, NULL, 0).color, -1);
    css_free(sh);
}

static void test_pseudo_nth_last_child(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("li:nth-last-child(2){color:#0c0c0c}", 0, &sh), CSS_OK);
    css_element li = el_sib_node("li", 4, 5, NULL, NULL);   /* 2nd from the end */
    assert_int_equal(css_resolve_el(sh, &li, NULL, 0).color, 0x0c0c0c);
    css_element last = el_sib_node("li", 5, 5, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &last, NULL, 0).color, -1);
    css_free(sh);
}

static void test_pseudo_root_and_form_state(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(":root{background:#0b0b0b} input:checked{color:#0f0f0f} "
                               "input:disabled{color:#1f1f1f} input:enabled{background:#2f2f2f}",
                               0, &sh), CSS_OK);
    css_element html = el_node("html", NULL, NULL, 0, NULL);
    assert_int_equal(css_resolve_el(sh, &html, NULL, 0).background, 0x0b0b0b);
    css_element div = el_node("div", NULL, NULL, 0, NULL);
    assert_int_equal(css_resolve_el(sh, &div, NULL, 0).background, -1);
    css_attr chk[] = { { "checked", "" } };
    css_element in_chk = el_attr_node("input", NULL, NULL, 0, chk, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &in_chk, NULL, 0).color, 0x0f0f0f);
    assert_int_equal(css_resolve_el(sh, &in_chk, NULL, 0).background, 0x2f2f2f); /* enabled */
    css_attr dis[] = { { "disabled", "" } };
    css_element in_dis = el_attr_node("input", NULL, NULL, 0, dis, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &in_dis, NULL, 0).color, 0x1f1f1f);
    assert_int_equal(css_resolve_el(sh, &in_dis, NULL, 0).background, -1); /* not enabled */
    /* :enabled only applies to form controls. */
    css_element span = el_node("span", NULL, NULL, 0, NULL);
    assert_int_equal(css_resolve_el(sh, &span, NULL, 0).background, -1);
    css_free(sh);
}

static void test_pseudo_unknown_drops_selector(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* Unknown pseudo-classes and pseudo-elements drop the selector.
     * R8: ::before/::after are now parsed and match in CSS cascade. */
    assert_int_equal(css_parse("a:foo, i{color:#080808} p::before{color:#090909} "
                                "p:before{color:#0a0a0a} q:not(.x){color:#0b0b0b} "
                                "s:first-of-type{color:#0c0c0c} p{background:#101010}",
                                0, &sh), CSS_OK);
    css_element i = el_node("i", NULL, NULL, 0, NULL);
    assert_int_equal(css_resolve_el(sh, &i, NULL, 0).color, 0x080808);
    css_element p = el_sib_node("p", 1, 1, NULL, NULL);
    /* ::before matches in CSS cascade */
    assert_int_equal(css_resolve_el(sh, &p, NULL, 0).color, 0x090909);
    assert_int_equal(css_resolve_el(sh, &p, NULL, 0).background, 0x101010);
    css_element q = el_node("q", NULL, NULL, 0, NULL);
    assert_int_not_equal(css_resolve_el(sh, &q, NULL, 0).color, -1); /* :not() supported */
    /* single-colon :before is still unknown (pseudo-class, not pseudo-element) */
    css_element s = el_sib_node("s", 1, 1, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &s, NULL, 0).color, -1); /* :first-of-type needs type-info */
    css_free(sh);
}

static void test_pseudo_specificity(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* a:link (1+10) beats a (1) regardless of document order; li:first-child
     * (1+10) ties with li.big (1+10) so document order decides. */
    assert_int_equal(css_parse("a:link{color:#111111} a{color:#222222} "
                               "li:first-child{color:#333333} li.big{color:#444444}",
                               0, &sh), CSS_OK);
    css_attr href[] = { { "href", "/x" } };
    css_element a = el_attr_node("a", NULL, NULL, 0, href, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &a, NULL, 0).color, 0x111111);
    const char *big[] = { "big" };
    css_element li = el_node("li", NULL, big, 1, NULL);
    li.nth = 1; li.nsib = 2;
    assert_int_equal(css_resolve_el(sh, &li, NULL, 0).color, 0x444444);
    css_free(sh);
}

static void test_pseudo_with_sibling_combinator(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* The checked+label idiom: input:checked + label. */
    assert_int_equal(css_parse("input:checked + label{color:#123456}", 0, &sh), CSS_OK);
    css_attr chk[] = { { "checked", "" } };
    css_element in_chk = el_attr_node("input", NULL, NULL, 0, chk, 1, NULL);
    in_chk.nth = 1; in_chk.nsib = 2;
    css_element lab = el_sib_node("label", 2, 2, &in_chk, NULL);
    assert_int_equal(css_resolve_el(sh, &lab, NULL, 0).color, 0x123456);
    css_element in_un = el_attr_node("input", NULL, NULL, 0, NULL, 0, NULL);
    in_un.nth = 1; in_un.nsib = 2;
    css_element lab2 = el_sib_node("label", 2, 2, &in_un, NULL);
    assert_int_equal(css_resolve_el(sh, &lab2, NULL, 0).color, -1);
    css_free(sh);
}

static void test_pseudo_nth_malformed_drops(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* Malformed or oversized An+B drops the selector (fail closed); partner rules
     * survive. */
    assert_int_equal(css_parse("li:nth-child(){color:#111111} "
                               "li:nth-child(2x+1){color:#222222} "
                               "li:nth-child(999999999n+1){color:#333333} "
                               "li:nth-child({color:#444444} "
                               "li{background:#101010}", 0, &sh), CSS_OK);
    css_element li = el_sib_node("li", 1, 1, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &li, NULL, 0).color, -1);
    assert_int_equal(css_resolve_el(sh, &li, NULL, 0).background, 0x101010);
    css_free(sh);
}

/* R2: of-type pseudo-classes */

static void test_pseudo_of_type(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("p:first-of-type{color:#f00000} "
                                "p:last-of-type{color:#0f0000} "
                                "p:only-of-type{color:#00f000}", 0, &sh), CSS_OK);
    /* 3 siblings, all <p> — p1 is first but not last */
    css_element pa = el_type_node("p", 1, 3, 1, 3, -1, NULL, NULL);
    css_element pb = el_type_node("p", 2, 3, 2, 3, -1, &pa, NULL);
    css_element pc = el_type_node("p", 3, 3, 3, 3, -1, &pb, NULL);
    assert_int_equal(css_resolve_el(sh, &pa, NULL, 0).color, 0xf00000); /* first-of-type */
    assert_int_equal(css_resolve_el(sh, &pb, NULL, 0).color, -1);        /* neither */
    assert_int_equal(css_resolve_el(sh, &pc, NULL, 0).color, 0x0f0000); /* last-of-type */
    /* Only one <p> */
    css_element lone = el_type_node("p", 1, 1, 1, 1, -1, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &lone, NULL, 0).color, 0x00f000); /* only-of-type */
    css_free(sh);
}

static void test_pseudo_nth_of_type(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("li:nth-of-type(2n){color:#100000} "
                                "span:nth-of-type(2){color:#200000}", 0, &sh), CSS_OK);
    /* 5 <li> siblings, elem is 4th */
    css_element e = el_type_node("li", 4, 5, 4, 5, -1, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &e, NULL, 0).color, 0x100000);  /* 2n → even → 4 matches */
    /* <span>, 2nd of its type */
    css_element s = el_type_node("span", 2, 5, 2, 2, -1, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &s, NULL, 0).color, 0x200000);  /* nth-of-type(2) matches 2 */
    css_element s3 = el_type_node("span", 2, 5, 3, 3, -1, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &s3, NULL, 0).color, -1);        /* 3 != 2 */
    css_free(sh);
}

static void test_pseudo_empty(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("div:empty{color:#111111}", 0, &sh), CSS_OK);
    css_element empty = el_type_node("div", 1, 1, 0, 0, 0, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &empty, NULL, 0).color, 0x111111);
    css_element haskids = el_type_node("div", 1, 1, 0, 0, 3, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &haskids, NULL, 0).color, -1);
    css_element unknown = el_type_node("div", 1, 1, 0, 0, -1, NULL, NULL);
    assert_int_equal(css_resolve_el(sh, &unknown, NULL, 0).color, -1);  /* unknown → fail closed */
    css_free(sh);
}

static void test_has_parses_and_fails_closed(void **state) {
    (void)state;
    /* :has() with a sub-selector: the rule should parse without error.
     * Since this element has no dom_node (NULL), :has() always fails
     * closed (never matches), so the color does NOT apply. */
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("div:has(.x){color:#050505}"
                                "span:has(img){color:#060606}", 0, &sh), CSS_OK);
    css_element d1 = el_node("div", NULL, (const char *[]){"class","x"}, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &d1, NULL, 0).color, -1);
    css_free(sh);
}

static void test_pseudo_target(void **state) {
    (void)state;
    /* :target is parsed but only matches when target_id is set by caller.
     * The standard CSS cascade path passes NULL, so it never matches. */
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("div:target{color:#999999}", 0, &sh), CSS_OK);
    css_element e = el_node("div", "foo", NULL, 0, NULL);
    assert_int_equal(css_resolve_el(sh, &e, NULL, 0).color, -1);  /* NULL target → no match */
    css_free(sh);
}

static void test_pseudo_lang(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("html:lang(en){color:#333333} "
                                "p:lang(es-mx){color:#444444}", 0, &sh), CSS_OK);
    css_attr lang_en[] = { { "lang", "en" } };
    css_element en = el_attr_node("html", NULL, NULL, 0, lang_en, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &en, NULL, 0).color, 0x333333);
    css_attr lang_en_us[] = { { "lang", "en-US" } };
    css_element en_us = el_attr_node("html", NULL, NULL, 0, lang_en_us, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &en_us, NULL, 0).color, 0x333333); /* en prefix matches */
    css_attr lang_es_mx[] = { { "lang", "es-MX" } };
    css_element es_mx = el_attr_node("p", NULL, NULL, 0, lang_es_mx, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &es_mx, NULL, 0).color, 0x444444);
    /* "fr" does NOT match :lang(en) */
    css_attr lang_fr[] = { { "lang", "fr" } };
    css_element fr = el_attr_node("html", NULL, NULL, 0, lang_fr, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &fr, NULL, 0).color, -1);
    css_free(sh);
}

static void test_resolve_el_inline_only(void **state) {
    (void)state;
    assert_int_equal(css_resolve_el(NULL, NULL, "color:#abcdef", 0).color, 0xabcdef);
}

/* --- attribute selectors (Hito 23b-4) --- */

static void test_attr_presence(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("input[disabled]{color:#101010}", 0, &sh), CSS_OK);
    css_attr with[] = { { "disabled", "" } };
    css_element a = el_attr_node("input", NULL, NULL, 0, with, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &a, NULL, 0).color, 0x101010);
    /* No such attribute -> no match (fail closed). */
    css_element b = el_attr_node("input", NULL, NULL, 0, NULL, 0, NULL);
    assert_int_equal(css_resolve_el(sh, &b, NULL, 0).color, -1);
    css_free(sh);
}

static void test_attr_equals(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("input[type=text]{color:#202020}"
                               "input[type=\"submit\"]{color:#303030}", 0, &sh), CSS_OK);
    css_attr txt[] = { { "type", "text" } };
    css_element a = el_attr_node("input", NULL, NULL, 0, txt, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &a, NULL, 0).color, 0x202020);
    css_attr sub[] = { { "type", "submit" } };
    css_element b = el_attr_node("input", NULL, NULL, 0, sub, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &b, NULL, 0).color, 0x303030);
    /* Different value -> no match; default value match is case-sensitive. */
    css_attr up[] = { { "type", "TEXT" } };
    css_element c = el_attr_node("input", NULL, NULL, 0, up, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &c, NULL, 0).color, -1);
    css_free(sh);
}

static void test_attr_operators(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(
        "[class~=btn]{color:#010101}"            /* word in a space list */
        "[lang|=en]{background:#020202}"          /* exact or dash-prefix */
        "a[href^=\"https://\"]{color:#030303}"    /* prefix */
        "a[href$=\".pdf\"]{background:#040404}"    /* suffix */
        "a[href*=\"track\"]{color:#050505}", 0, &sh), CSS_OK);

    css_attr w[] = { { "class", "big btn round" } };
    css_element word = el_attr_node("span", NULL, NULL, 0, w, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &word, NULL, 0).color, 0x010101);
    css_attr w2[] = { { "class", "button" } };  /* "btn" is not a whole word here */
    css_element noword = el_attr_node("span", NULL, NULL, 0, w2, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &noword, NULL, 0).color, -1);

    css_attr l[] = { { "lang", "en-US" } };
    css_element dash = el_attr_node("p", NULL, NULL, 0, l, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &dash, NULL, 0).background, 0x020202);
    css_attr l2[] = { { "lang", "ending" } };   /* "en" prefix but no '-' boundary */
    css_element nope = el_attr_node("p", NULL, NULL, 0, l2, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &nope, NULL, 0).background, -1);

    css_attr h[] = { { "href", "https://x.test/track/a.pdf" } };
    css_element link = el_attr_node("a", NULL, NULL, 0, h, 1, NULL);
    css_style ls = css_resolve_el(sh, &link, NULL, 0);
    assert_int_equal(ls.color, 0x050505);       /* *=track wins last among colors */
    assert_int_equal(ls.background, 0x040404);  /* $=.pdf */
    css_free(sh);
}

static void test_attr_case_insensitive_flag(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* The trailing " i" makes the value match case-insensitively. */
    assert_int_equal(css_parse("input[type=\"text\" i]{color:#0b0b0b}"
                               "input[type=email s]{color:#0c0c0c}", 0, &sh), CSS_OK);
    css_attr up[] = { { "type", "TeXt" } };
    css_element a = el_attr_node("input", NULL, NULL, 0, up, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &a, NULL, 0).color, 0x0b0b0b);
    css_attr up2[] = { { "type", "EMAIL" } };   /* explicit s: stays case-sensitive */
    css_element b = el_attr_node("input", NULL, NULL, 0, up2, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &b, NULL, 0).color, -1);
    css_free(sh);
}

static void test_attr_name_case_insensitive(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* Attribute names are matched case-insensitively (HTML). */
    assert_int_equal(css_parse("[DATA-X=on]{color:#0d0d0d}", 0, &sh), CSS_OK);
    css_attr at[] = { { "data-x", "on" } };
    css_element a = el_attr_node("div", NULL, NULL, 0, at, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &a, NULL, 0).color, 0x0d0d0d);
    css_free(sh);
}

static void test_attr_quoted_value_with_space(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* A quoted value may contain whitespace without splitting the compound. */
    assert_int_equal(css_parse("[title=\"a b\"]{color:#0e0e0e}", 0, &sh), CSS_OK);
    css_attr ok[] = { { "title", "a b" } };
    css_element a = el_attr_node("div", NULL, NULL, 0, ok, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &a, NULL, 0).color, 0x0e0e0e);
    css_attr no[] = { { "title", "a" } };
    css_element b = el_attr_node("div", NULL, NULL, 0, no, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &b, NULL, 0).color, -1);
    css_free(sh);
}

static void test_attr_specificity_and_compound(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* input[type=text] (1 type + 1 attr = 11) beats input (1). A second attribute
     * and a tag must ALL hold (compound = AND). */
    assert_int_equal(css_parse("input{color:#ff0000}"
                               "input[type=text]{color:#00ff00}"
                               "input[type=text][required]{color:#0000ff}", 0, &sh), CSS_OK);
    css_attr one[] = { { "type", "text" } };
    css_element a = el_attr_node("input", NULL, NULL, 0, one, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &a, NULL, 0).color, 0x00ff00);
    css_attr two[] = { { "type", "text" }, { "required", "" } };
    css_element b = el_attr_node("input", NULL, NULL, 0, two, 2, NULL);
    assert_int_equal(css_resolve_el(sh, &b, NULL, 0).color, 0x0000ff);
    css_free(sh);
}

static void test_attr_in_combinator(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* An attribute constraint on an ANCESTOR compound resolves up the chain. */
    assert_int_equal(css_parse("nav[role=banner] a{color:#abcdef}", 0, &sh), CSS_OK);
    css_attr role[] = { { "role", "banner" } };
    css_element nav = el_attr_node("nav", NULL, NULL, 0, role, 1, NULL);
    css_element a   = el_node("a", NULL, NULL, 0, &nav);
    assert_int_equal(css_resolve_el(sh, &a, NULL, 0).color, 0xabcdef);
    /* Ancestor lacks the attribute -> no match (fail closed). */
    css_element nav2 = el_node("nav", NULL, NULL, 0, NULL);
    css_element a2   = el_node("a", NULL, NULL, 0, &nav2);
    assert_int_equal(css_resolve_el(sh, &a2, NULL, 0).color, -1);
    css_free(sh);
}

static void test_attr_malformed_fail_closed(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* Unbalanced/empty/unknown-operator brackets drop only that selector; the plain
     * rule in the group survives. */
    assert_int_equal(css_parse("input[ {color:#111111}"     /* unbalanced */
                               "input[]{color:#222222}"      /* empty */
                               "p{color:#333333}", 0, &sh), CSS_OK);
    css_element p = el_node("p", NULL, NULL, 0, NULL);
    assert_int_equal(css_resolve_el(sh, &p, NULL, 0).color, 0x333333);
    css_attr none[] = { { "type", "x" } };
    css_element in = el_attr_node("input", NULL, NULL, 0, none, 1, NULL);
    assert_int_equal(css_resolve_el(sh, &in, NULL, 0).color, -1);
    css_free(sh);
}

/* --- !important (Hito 23b-4) --- */

static void test_important_inline_not_dropped(void **state) {
    (void)state;
    /* Previously a value with !important failed to interpret and was dropped. */
    css_style s = css_parse_inline("color:#ff0000 !important", 0);
    assert_int_equal(s.color, 0xff0000);
    /* Whitespace variants and case are accepted; a bare !important is dropped. */
    assert_int_equal(css_parse_inline("color:#00ff00!IMPORTANT", 0).color, 0x00ff00);
    assert_int_equal(css_parse_inline("color: !important", 0).color, -1);
}

static void test_important_beats_specificity(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* An important type rule beats a non-important id rule (tier > specificity). */
    assert_int_equal(css_parse("#x{color:#00ff00} p{color:#ff0000 !important}", 0, &sh), CSS_OK);
    assert_int_equal(css_resolve(sh, "p", "x", NULL, 0, NULL, 0).color, 0xff0000);
    css_free(sh);
}

static void test_important_tier_then_normal_order(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* Among important declarations, the normal cascade (specificity, then order) holds. */
    assert_int_equal(css_parse("p{color:#111111 !important} #x{color:#222222 !important}",
                               0, &sh), CSS_OK);
    assert_int_equal(css_resolve(sh, "p", "x", NULL, 0, NULL, 0).color, 0x222222);
    css_free(sh);
}

static void test_important_inline_beats_sheet_important(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("p{color:#111111 !important}", 0, &sh), CSS_OK);
    /* Inline important wins (inline carries the highest specificity). */
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, "color:#abcabc !important", 0).color,
                     0xabcabc);
    /* But a sheet important beats a NON-important inline. */
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, "color:#abcabc", 0).color, 0x111111);
    css_free(sh);
}

static void test_important_in_shorthand(void **state) {
    (void)state;
    /* !important stamps every side a shorthand expands to. */
    css_style s = css_parse_inline("margin:10px !important", 0);
    assert_int_equal(s.margin_top, 10);
    assert_int_equal(s.margin_left, 10);
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("p{margin:4px} p{margin:9px !important}", 0, &sh), CSS_OK);
    /* The important shorthand wins over a later non-important one too. */
    css_style r = css_resolve(sh, "p", NULL, NULL, 0, NULL, 0);
    assert_int_equal(r.margin_top, 9);
    assert_int_equal(r.margin_right, 9);
    css_free(sh);
}

/* --- cascade --- */

static void test_cascade_specificity(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* id (100) beats class (10) beats type (1) regardless of source order. */
    assert_int_equal(css_parse("#x{color:#0000ff} .c{color:#00ff00} p{color:#ff0000}", 0, &sh), CSS_OK);
    const char *cl[] = { "c" };
    assert_int_equal(css_resolve(sh, "p", "x", cl, 1, NULL, 0).color, 0x0000ff); /* id wins */
    assert_int_equal(css_resolve(sh, "p", NULL, cl, 1, NULL, 0).color, 0x00ff00); /* class wins */
    css_free(sh);
}

/* Regression: CSS_MAX_RULES/CSS_MAX_SELS/CSS_MAX_DECLS used to be 384/512/2048.
 * A real, vendored, minified Bootstrap 4.5.2 stylesheet has ~2100 rules; every
 * rule past #384 (in practice: essentially all of its utility classes, which are
 * generated last) was silently dropped, so ".bg-dark"/".text-success" and friends
 * never matched anything -- with no error anywhere, since the drop is deliberately
 * silent (anti-DoS truncation, not a parse failure). 500 filler rules is well past
 * the OLD cap and well under the current one. */
static void test_large_stylesheet_rules_beyond_old_cap(void **state) {
    (void)state;
    size_t bufsz = 64 * 1024;
    char *buf = (char *)malloc(bufsz);
    assert_non_null(buf);
    size_t off = 0;
    for (int i = 0; i < 500; ++i) {
        size_t space = bufsz - off;
        if (space == 0) break;
        int n = snprintf(buf + off, space, ".f%d{color:#%06x}", i, (unsigned)i);
        assert_true(n > 0 && (size_t)n < space);
        off += (size_t)n;
    }
    {
        size_t space = bufsz - off;
        int n = snprintf(buf + off, space, ".target{color:#123456}");
        assert_true(n > 0 && (size_t)n < space);
        if (n > 0 && (size_t)n < space) off += (size_t)n;
    }

    css_sheet *sh = NULL;
    assert_int_equal(css_parse(buf, off, &sh), CSS_OK);
    const char *cl[] = { "target" };
    assert_int_equal(css_resolve(sh, "div", NULL, cl, 1, NULL, 0).color, 0x123456);
    css_free(sh);
    free(buf);
}

static void test_cascade_document_order(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* equal specificity -> the later rule wins. */
    assert_int_equal(css_parse("p{color:#111111} p{color:#222222}", 0, &sh), CSS_OK);
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0x222222);
    css_free(sh);
}

static void test_cascade_inline_wins(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("#x{color:#111111}", 0, &sh), CSS_OK);
    /* inline beats even an id rule. */
    assert_int_equal(css_resolve(sh, "p", "x", NULL, 0, "color:#abcabc", 0).color, 0xabcabc);
    css_free(sh);
}

static void test_at_rules_skipped(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(
        "@import url(evil.css);\n"
        "@media screen { p { color:#ffffff } }\n"
        "p { color:#123456 }", 0, &sh), CSS_OK);
    /* @import is skipped entirely (no network). @media screen matches the default
     * context, so its rule applies, then the later same-specificity plain rule wins
     * by document order. */
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0x123456);
    css_free(sh);
}

/* --- @media (Hito 23b) --- */

/* @media screen matches the default context; its rules apply. @media print does not. */
static void test_media_screen_and_print(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(
        "@media screen { p { color:#abcdef } }\n"
        "@media print { p { color:#010101 } }", 0, &sh), CSS_OK);
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0xabcdef);
    css_free(sh);

    /* With a print context, the print block applies and the screen block does not. */
    css_media print_ctx = { 0, 1, CSS_MEDIA_DEFAULT_WIDTH };
    assert_int_equal(css_parse_media(
        "@media screen { p { color:#abcdef } }\n"
        "@media print { p { color:#010101 } }", 0, &print_ctx, &sh), CSS_OK);
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0x010101);
    css_free(sh);
}

/* prefers-color-scheme: dark applies only when the context prefers dark. */
static void test_media_prefers_color_scheme(void **state) {
    (void)state;
    const char *css = "@media (prefers-color-scheme: dark) { body { color:#ffffff } }";
    css_sheet *sh = NULL;

    assert_int_equal(css_parse(css, 0, &sh), CSS_OK); /* default = light */
    assert_int_equal(css_resolve(sh, "body", NULL, NULL, 0, NULL, 0).color, -1);
    css_free(sh);

    css_media dark = { 1, 0, CSS_MEDIA_DEFAULT_WIDTH };
    assert_int_equal(css_parse_media(css, 0, &dark, &sh), CSS_OK);
    assert_int_equal(css_resolve(sh, "body", NULL, NULL, 0, NULL, 0).color, 0xffffff);
    css_free(sh);
}

/* min-width / max-width compare against the normalized 1920px width. */
static void test_media_width_queries(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(
        "@media (min-width: 600px) { p { color:#111111 } }\n"
        "@media (min-width: 3000px) { p { color:#222222 } }\n"
        "@media (max-width: 1000px) { div { color:#333333 } }", 0, &sh), CSS_OK);
    /* 1920 >= 600 applies; 1920 >= 3000 does not; so p stays #111111. */
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0x111111);
    /* 1920 <= 1000 is false, so the div rule never applies. */
    assert_int_equal(css_resolve(sh, "div", NULL, NULL, 0, NULL, 0).color, -1);
    css_free(sh);
}

/* "and" requires every part; a comma is OR across the query list. */
static void test_media_and_or(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(
        "@media screen and (min-width: 600px) { p { color:#0a0a0a } }\n"
        "@media screen and (min-width: 5000px) { div { color:#0b0b0b } }\n"
        "@media print, screen { span { color:#0c0c0c } }", 0, &sh), CSS_OK);
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0x0a0a0a);
    assert_int_equal(css_resolve(sh, "div", NULL, NULL, 0, NULL, 0).color, -1); /* and fails */
    assert_int_equal(css_resolve(sh, "span", NULL, NULL, 0, NULL, 0).color, 0x0c0c0c); /* or: screen */
    css_free(sh);
}

/* Fail closed: unknown media type/feature and `not` never apply their rules. */
static void test_media_unknown_fails_closed(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(
        "@media (hover: hover) { p { color:#cccccc } }\n"
        "@media tv { a { color:#dddddd } }\n"
        "@media not screen { b { color:#eeeeee } }\n"
        "h1 { color:#0f0f0f }", 0, &sh), CSS_OK);
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, -1);
    assert_int_equal(css_resolve(sh, "a", NULL, NULL, 0, NULL, 0).color, -1);
    assert_int_equal(css_resolve(sh, "b", NULL, NULL, 0, NULL, 0).color, -1);
    /* a normal rule after the dropped @media blocks still parses. */
    assert_int_equal(css_resolve(sh, "h1", NULL, NULL, 0, NULL, 0).color, 0x0f0f0f);
    css_free(sh);
}

/* --- arg handling --- */

static void test_parse_null_args(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(NULL, 0, &sh), CSS_OK);  /* NULL text = empty sheet */
    assert_non_null(sh);
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, -1);
    css_free(sh);
    assert_int_equal(css_parse("p{}", 0, NULL), CSS_ERR_NULL_ARG);
}

static void test_resolve_null_safe(void **state) {
    (void)state;
    /* NULL sheet and NULL tag are safe; everything unset. */
    css_style s = css_resolve(NULL, NULL, NULL, NULL, 0, NULL, 0);
    assert_int_equal(s.color, -1);
    assert_int_equal(s.text_align, CSS_ALIGN_UNSET);
    assert_int_equal(s.display, CSS_DISP_UNSET);
    assert_int_equal(s.gap, -1);
    assert_int_equal(s.justify, CSS_JUSTIFY_UNSET);
    assert_int_equal(s.grid_cols, 0);
}

/* --- author box model (Hito 23b-3) --- */

static void test_inline_box_longhands(void **state) {
    (void)state;
    css_style s = css_parse_inline(
        "margin-top:10px; margin-right:20px; margin-bottom:30px; margin-left:40px;"
        "padding-top:1px; padding-right:2px; padding-bottom:3px; padding-left:4px;"
        "width:600px; max-width:800px", 0);
    assert_int_equal(s.margin_top, 10);
    assert_int_equal(s.margin_right, 20);
    assert_int_equal(s.margin_bottom, 30);
    assert_int_equal(s.margin_left, 40);
    assert_int_equal(s.pad_top, 1);
    assert_int_equal(s.pad_right, 2);
    assert_int_equal(s.pad_bottom, 3);
    assert_int_equal(s.pad_left, 4);
    assert_int_equal(s.width, 600);
    assert_int_equal(s.max_width, 800);
}

static void test_box_shorthand_expansion(void **state) {
    (void)state;
    /* one value: all four sides. */
    css_style a = css_parse_inline("margin:5px", 0);
    assert_int_equal(a.margin_top, 5);
    assert_int_equal(a.margin_right, 5);
    assert_int_equal(a.margin_bottom, 5);
    assert_int_equal(a.margin_left, 5);
    /* two values: vertical | horizontal. */
    css_style b = css_parse_inline("margin:5px 10px", 0);
    assert_int_equal(b.margin_top, 5);
    assert_int_equal(b.margin_bottom, 5);
    assert_int_equal(b.margin_right, 10);
    assert_int_equal(b.margin_left, 10);
    /* three values: top | horizontal | bottom. */
    css_style c = css_parse_inline("margin:1px 2px 3px", 0);
    assert_int_equal(c.margin_top, 1);
    assert_int_equal(c.margin_right, 2);
    assert_int_equal(c.margin_left, 2);
    assert_int_equal(c.margin_bottom, 3);
    /* four values: top right bottom left (clockwise). */
    css_style d = css_parse_inline("padding:1px 2px 3px 4px", 0);
    assert_int_equal(d.pad_top, 1);
    assert_int_equal(d.pad_right, 2);
    assert_int_equal(d.pad_bottom, 3);
    assert_int_equal(d.pad_left, 4);
}

static void test_box_auto_and_centering(void **state) {
    (void)state;
    css_style s = css_parse_inline("margin:0 auto; max-width:700px", 0);
    assert_int_equal(s.margin_top, 0);
    assert_int_equal(s.margin_bottom, 0);
    assert_int_equal(s.margin_left, CSS_LEN_AUTO);
    assert_int_equal(s.margin_right, CSS_LEN_AUTO);
    assert_int_equal(s.max_width, 700);
    /* margin: 10px auto -> vertical 10, horizontal auto. */
    css_style m = css_parse_inline("margin:10px auto", 0);
    assert_int_equal(m.margin_top, 10);
    assert_int_equal(m.margin_left, CSS_LEN_AUTO);
    /* width:auto -> unset; max-width:none -> unset. */
    assert_int_equal(css_parse_inline("width:auto", 0).width, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("max-width:none", 0).max_width, CSS_LEN_UNSET);
}

static void test_box_units_and_failclosed(void **state) {
    (void)state;
    /* em/rem -> x16 px. */
    assert_int_equal(css_parse_inline("margin-left:2em", 0).margin_left, 32);
    assert_int_equal(css_parse_inline("padding:1rem", 0).pad_top, 16);
    /* bare 0 (no unit) accepted. */
    assert_int_equal(css_parse_inline("margin-top:0", 0).margin_top, 0);
    /* negative margins allowed; negative/auto padding & width dropped (unset). */
    assert_int_equal(css_parse_inline("margin-top:-8px", 0).margin_top, -8);
    assert_int_equal(css_parse_inline("padding-top:-8px", 0).pad_top, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("padding:auto", 0).pad_top, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("width:-8px", 0).width, CSS_LEN_UNSET);
    /* percent / viewport units dropped (no containing block) -> unset. */
    assert_int_equal(css_parse_inline("width:50%", 0).width, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("margin-left:5vw", 0).margin_left, CSS_LEN_UNSET);
    /* unset by default (a declaration that touches only color). */
    css_style def = css_parse_inline("color:#000", 0);
    assert_int_equal(def.margin_top, CSS_LEN_UNSET);
    assert_int_equal(def.pad_left, CSS_LEN_UNSET);
    assert_int_equal(def.width, CSS_LEN_UNSET);
    assert_int_equal(def.max_width, CSS_LEN_UNSET);
}

/* Hito 32: width/max-width percentages are carried SYMBOLICALLY (per-mille in
 * width_pct/max_width_pct; the px channel stays UNSET) and resolved at layout
 * time against the real containing width. Junk still fails closed; every other
 * % length keeps failing closed. */
static void test_width_percent_carried_symbolically(void **state) {
    (void)state;
    css_style s = css_parse_inline("width:99.8%", 0);
    assert_int_equal(s.width, CSS_LEN_UNSET);          /* px channel untouched */
    assert_int_equal(s.width_pct, 998);
    assert_int_equal(css_parse_inline("max-width:50%", 0).max_width_pct, 500);
    assert_int_equal(css_parse_inline("width:100%", 0).width_pct, 1000);
    /* logical alias rides the same slots. */
    assert_int_equal(css_parse_inline("inline-size:25%", 0).width_pct, 250);
    assert_int_equal(css_parse_inline("max-inline-size:75%", 0).max_width_pct, 750);
    /* junk fails closed (unset = 0). */
    assert_int_equal(css_parse_inline("width:-5%", 0).width_pct, 0);
    assert_int_equal(css_parse_inline("width:%", 0).width_pct, 0);
    assert_int_equal(css_parse_inline("width:abc%", 0).width_pct, 0);
    assert_int_equal(css_parse_inline("width:0%", 0).width_pct, 0);
    /* clamp: anything past 1000% saturates instead of overflowing. */
    assert_int_equal(css_parse_inline("width:5000%", 0).width_pct, 10000);
    /* px and pct coexist across properties (each keeps its own channel). */
    css_style t = css_parse_inline("width:600px; max-width:50%", 0);
    assert_int_equal(t.width, 600);
    assert_int_equal(t.width_pct, 0);
    assert_int_equal(t.max_width_pct, 500);
    assert_int_equal(t.max_width, CSS_LEN_UNSET);
    /* other % lengths still fail closed. */
    assert_int_equal(css_parse_inline("margin-left:10%", 0).margin_left, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("min-width:10%", 0).min_width, CSS_LEN_UNSET);
}

static void test_calc_basic_arithmetic(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("width: calc(100px + 50px)", 0).width, 150);
    assert_int_equal(css_parse_inline("width: calc(100px - 30px)", 0).width, 70);
    assert_int_equal(css_parse_inline("width: calc(10px * 3)", 0).width, 30);
    assert_int_equal(css_parse_inline("width: calc(3 * 10px)", 0).width, 30);
    assert_int_equal(css_parse_inline("width: calc(100px / 4)", 0).width, 25);
}

static void test_calc_precedence_and_parens(void **state) {
    (void)state;
    /* * binds tighter than +: 10 + 2*20 = 50, not (10+2)*20 = 240. */
    assert_int_equal(css_parse_inline("width: calc(10px + 2 * 20px)", 0).width, 50);
    assert_int_equal(css_parse_inline("width: calc((10px + 2px) * 3)", 0).width, 36);
}

static void test_calc_units_and_signs(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("margin-left: calc(1em + 8px)", 0).margin_left, 24);
    assert_int_equal(css_parse_inline("margin-left: calc(-1em - 8px)", 0).margin_left, -24);
    /* auto is orthogonal to calc(): margin allows negative results. */
    assert_int_equal(css_parse_inline("padding-left: calc(20px - 30px)", 0).pad_left, CSS_LEN_UNSET);
}

static void test_calc_dimension_errors_fail_closed(void **state) {
    (void)state;
    /* length * length and a dimensionless result are both invalid. */
    assert_int_equal(css_parse_inline("width: calc(10px * 5px)", 0).width, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("width: calc(2 * 3)", 0).width, CSS_LEN_UNSET);
    /* length +/- dimensionless number is invalid. */
    assert_int_equal(css_parse_inline("width: calc(10px + 5)", 0).width, CSS_LEN_UNSET);
    /* division by zero, by a length, unbalanced parens, percent inside calc(). */
    assert_int_equal(css_parse_inline("width: calc(10px / 0)", 0).width, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("width: calc(10px / 2px)", 0).width, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("width: calc(10px + (5px)", 0).width, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("width: calc(100% - 20px)", 0).width, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("width: calc()", 0).width, CSS_LEN_UNSET);
}

static void test_calc_clamped_anti_dos(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("width: calc(99999999999px + 1px)", 0).width, CSS_LEN_MAX);
}

/* calc() must survive being ONE token inside a multi-value shorthand: a naive
 * whitespace splitter would break "calc(10px + 5px)" apart at the internal spaces
 * (into "calc(10px", "+", "5px)") before it ever reached interp_len. Exercises
 * every shorthand tokenizer that can hand a token to something calc-aware
 * (margin/padding, flex, border/outline width, text-shadow, box-shadow). */
static void test_calc_inside_shorthands(void **state) {
    (void)state;
    css_style m = css_parse_inline("margin: calc(10px + 5px) auto", 0);
    assert_int_equal(m.margin_top, 15);
    assert_int_equal(m.margin_bottom, 15);
    assert_int_equal(m.margin_left, CSS_LEN_AUTO);

    css_style p4 = css_parse_inline("padding: calc(2px * 3) calc(20px / 4)", 0);
    assert_int_equal(p4.pad_top, 6);
    assert_int_equal(p4.pad_bottom, 6);
    assert_int_equal(p4.pad_right, 5);
    assert_int_equal(p4.pad_left, 5);

    css_style f = css_parse_inline("flex: 0 0 calc(100px + 120px)", 0);
    assert_int_equal(f.flex_grow, 0);
    assert_int_equal(f.flex_shrink, 0);
    assert_int_equal(f.flex_basis, 220);

    css_style b = css_parse_inline("border-width: calc(1px + 1px) 3px", 0);
    assert_int_equal(b.border_top_width, 2);
    assert_int_equal(b.border_bottom_width, 2);
    assert_int_equal(b.border_right_width, 3);

    css_style bo = css_parse_inline("border: calc(1px + 2px) solid #ff0000", 0);
    assert_int_equal(bo.border_top_width, 3);
    assert_int_equal(bo.border_top_style, CSS_BST_SOLID);
    assert_int_equal(bo.border_top_color, 0xff0000);

    css_style ts = css_parse_inline("text-shadow: calc(1px + 1px) calc(2px + 2px) red", 0);
    assert_int_equal(ts.shadow_dx, 2);
    assert_int_equal(ts.shadow_dy, 4);

    css_style bs = css_parse_inline("box-shadow: calc(1px + 1px) calc(2px + 2px) 3px", 0);
    assert_int_equal(bs.shadow2_dx, 2);
    assert_int_equal(bs.shadow2_dy, 4);
    assert_int_equal(bs.shadow2_blur, 3);
}

static void test_calc_with_custom_property(void **state) {
    (void)state;
    /* calc() and var() compose: var() substitutes text before calc() is parsed. */
    css_style s = css_parse_inline("--base: 20px; width: calc(var(--base) * 2)", 0);
    assert_int_equal(s.width, 40);
}

static void test_box_clamp_anti_dos(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("width:99999999px", 0).width, CSS_LEN_MAX);
    assert_int_equal(css_parse_inline("margin-top:99999999px", 0).margin_top, CSS_LEN_MAX);
    assert_int_equal(css_parse_inline("margin-top:-99999999px", 0).margin_top, -CSS_LEN_MAX);
}

/* --- box model extensions (min-width, height, min-height, max-height) --- */

static void test_inline_min_width_height(void **state) {
    (void)state;
    css_style s = css_parse_inline("min-width:100px; height:200px", 0);
    assert_int_equal(s.min_width, 100);
    assert_int_equal(s.height, 200);
    /* em/rem -> x16 px. */
    assert_int_equal(css_parse_inline("min-width:5em", 0).min_width, 80);
    assert_int_equal(css_parse_inline("height:2rem", 0).height, 32);
    /* auto/none -> unset. */
    assert_int_equal(css_parse_inline("min-width:auto", 0).min_width, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("height:auto", 0).height, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("min-height:none", 0).min_height, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("max-height:none", 0).max_height, CSS_LEN_UNSET);
    /* Percent dropped -> unset. */
    assert_int_equal(css_parse_inline("min-width:50%", 0).min_width, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("height:50%", 0).height, CSS_LEN_UNSET);
    /* Negative -> unset (non-negative only). */
    assert_int_equal(css_parse_inline("min-width:-8px", 0).min_width, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("height:-8px", 0).height, CSS_LEN_UNSET);
    /* Unset by default. */
    css_style def = css_parse_inline("color:#000", 0);
    assert_int_equal(def.min_width, CSS_LEN_UNSET);
    assert_int_equal(def.height, CSS_LEN_UNSET);
    assert_int_equal(def.min_height, CSS_LEN_UNSET);
    assert_int_equal(def.max_height, CSS_LEN_UNSET);
}

static void test_inline_min_max_height(void **state) {
    (void)state;
    css_style s = css_parse_inline("min-height:50px; max-height:400px", 0);
    assert_int_equal(s.min_height, 50);
    assert_int_equal(s.max_height, 400);
    /* calc() works. */
    assert_int_equal(css_parse_inline("min-height: calc(100px + 50px)", 0).min_height, 150);
    assert_int_equal(css_parse_inline("max-height: calc(200px - 50px)", 0).max_height, 150);
    /* em/rem. */
    assert_int_equal(css_parse_inline("min-height:3em", 0).min_height, 48);
    /* Clamp anti-DoS. */
    assert_int_equal(css_parse_inline("min-height:99999999px", 0).min_height, CSS_LEN_MAX);
}

static void test_box_extension_sheet_cascade(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(
        ".card { min-width:300px; height:200px; min-height:100px; max-height:500px }"
        "#s { height:400px }", 0, &sh), CSS_OK);
    const char *cls[] = { "card" };
    css_style s = css_resolve(sh, "div", NULL, cls, 1, NULL, 0);
    assert_int_equal(s.min_width, 300);
    assert_int_equal(s.height, 200);
    assert_int_equal(s.min_height, 100);
    assert_int_equal(s.max_height, 500);
    /* Inline wins. */
    css_style t = css_resolve(sh, "div", NULL, cls, 1, "height:250px", 0);
    assert_int_equal(t.height, 250);
    css_free(sh);
}

/* --- text-decoration-color / text-decoration-style --- */

static void test_inline_text_decoration_color_style(void **state) {
    (void)state;
    css_style s = css_parse_inline("text-decoration-color:#ff0000", 0);
    assert_int_equal(s.text_decoration_color, 0xff0000);
    assert_int_equal(s.text_decoration_style, CSS_TDS_UNSET);

    css_style t = css_parse_inline("text-decoration-style:wavy", 0);
    assert_int_equal(t.text_decoration_style, CSS_TDS_WAVY);
    assert_int_equal(t.text_decoration_color, -1);

    css_style u = css_parse_inline("text-decoration-color:#00ff00; text-decoration-style:double", 0);
    assert_int_equal(u.text_decoration_color, 0x00ff00);
    assert_int_equal(u.text_decoration_style, CSS_TDS_DOUBLE);

    /* All style keywords. */
    assert_int_equal(css_parse_inline("text-decoration-style:solid", 0).text_decoration_style, CSS_TDS_SOLID);
    assert_int_equal(css_parse_inline("text-decoration-style:dotted", 0).text_decoration_style, CSS_TDS_DOTTED);
    assert_int_equal(css_parse_inline("text-decoration-style:dashed", 0).text_decoration_style, CSS_TDS_DASHED);

    /* Unknown style -> unset. */
    assert_int_equal(css_parse_inline("text-decoration-style:inherit", 0).text_decoration_style, CSS_TDS_UNSET);
    /* Default: color -1, style unset. */
    css_style def = css_parse_inline("color:#000", 0);
    assert_int_equal(def.text_decoration_color, -1);
    assert_int_equal(def.text_decoration_style, CSS_TDS_UNSET);
}

/* --- text-decoration-thickness --- */

static void test_inline_text_decoration_thickness(void **state) {
    (void)state;
    /* from-font -> 0 (the painter treats 0 as "default thickness" via cairo). */
    assert_int_equal(css_parse_inline("text-decoration-thickness:from-font", 0).text_decoration_thickness, 0);
    /* px values. */
    assert_int_equal(css_parse_inline("text-decoration-thickness:1px", 0).text_decoration_thickness, 1);
    assert_int_equal(css_parse_inline("text-decoration-thickness:3px", 0).text_decoration_thickness, 3);
    assert_int_equal(css_parse_inline("text-decoration-thickness:0.5em", 0).text_decoration_thickness, 8);
    /* Negative and percentage dropped (CSS does not allow them). */
    assert_int_equal(css_parse_inline("text-decoration-thickness:-1px", 0).text_decoration_thickness, -1);
    assert_int_equal(css_parse_inline("text-decoration-thickness:50%", 0).text_decoration_thickness, -1);
    /* Default. */
    assert_int_equal(css_parse_inline("color:#000", 0).text_decoration_thickness, -1);
}

/* --- aspect-ratio --- */

static void test_inline_aspect_ratio(void **state) {
    (void)state;
    /* 16/9 -> 16000/9000. */
    css_style a = css_parse_inline("aspect-ratio:16/9", 0);
    assert_int_equal(a.aspect_num, 16000);
    assert_int_equal(a.aspect_den, 9000);
    /* 1.5 -> 1500/1000. */
    css_style b = css_parse_inline("aspect-ratio:1.5", 0);
    assert_int_equal(b.aspect_num, 1500);
    assert_int_equal(b.aspect_den, 1000);
    /* 1 (bare) -> 1000/1000. */
    css_style c = css_parse_inline("aspect-ratio:1", 0);
    assert_int_equal(c.aspect_num, 1000);
    assert_int_equal(c.aspect_den, 1000);
    /* auto -> 0/0 (unset/natural). */
    css_style d = css_parse_inline("aspect-ratio:auto", 0);
    assert_int_equal(d.aspect_num, 0);
    assert_int_equal(d.aspect_den, 0);
    /* Bad value -> 0/0 (dropped). */
    css_style e = css_parse_inline("aspect-ratio:abc", 0);
    assert_int_equal(e.aspect_num, 0);
    assert_int_equal(e.aspect_den, 0);
    /* default. */
    css_style def = css_parse_inline("color:#000", 0);
    assert_int_equal(def.aspect_num, 0);
    assert_int_equal(def.aspect_den, 0);
}

/* --- direction --- */

static void test_inline_direction(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("direction:ltr", 0).direction, CSS_DIR_LTR);
    assert_int_equal(css_parse_inline("direction:rtl", 0).direction, CSS_DIR_RTL);
    assert_int_equal(css_parse_inline("color:red", 0).direction, CSS_DIR_UNSET);
}

/* --- outline-offset --- */

static void test_inline_outline_offset(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("outline-offset:2px", 0).outline_offset, 2);
    assert_int_equal(css_parse_inline("outline-offset:-1px", 0).outline_offset, -1);
    assert_int_equal(css_parse_inline("outline-offset:0", 0).outline_offset, 0);
    assert_int_equal(css_parse_inline("outline-offset:2em", 0).outline_offset, 32);
    assert_int_equal(css_parse_inline("outline-offset:2%", 0).outline_offset, CSS_LEN_UNSET); /* dropped */
    assert_int_equal(css_parse_inline("color:red", 0).outline_offset, CSS_LEN_UNSET);
}

/* --- tab-size --- */

static void test_inline_tab_size(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("tab-size:4", 0).tab_size, 4);
    assert_int_equal(css_parse_inline("tab-size:8", 0).tab_size, 8);
    assert_int_equal(css_parse_inline("tab-size:0", 0).tab_size, 0);  /* 0 -> unset */
    assert_int_equal(css_parse_inline("tab-size:100", 0).tab_size, 64); /* clamp */
    assert_int_equal(css_parse_inline("tab-size:2px", 0).tab_size, 0);  /* units dropped */
    assert_int_equal(css_parse_inline("color:red", 0).tab_size, 0);
}

static void test_box_sheet_cascade_inline_wins(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(".card{max-width:600px;margin:0 auto;padding:24px}", 0, &sh), CSS_OK);
    const char *cls[] = { "card" };
    css_style s = css_resolve(sh, "div", NULL, cls, 1, "padding:40px", 0);
    assert_int_equal(s.max_width, 600);
    assert_int_equal(s.margin_left, CSS_LEN_AUTO);
    assert_int_equal(s.pad_top, 40);   /* inline overrides the sheet */
    assert_int_equal(s.pad_left, 40);
    css_free(sh);
}

/* --- Layout / box decoration (Hito 23b-7) --- */

static void test_position_and_insets(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("position:relative", 0).position, CSS_POS_RELATIVE);
    assert_int_equal(css_parse_inline("position:ABSOLUTE", 0).position, CSS_POS_ABSOLUTE);
    assert_int_equal(css_parse_inline("position:fixed", 0).position, CSS_POS_FIXED);
    assert_int_equal(css_parse_inline("position:sticky", 0).position, CSS_POS_STICKY);
    assert_int_equal(css_parse_inline("position:static", 0).position, CSS_POS_STATIC);
    assert_int_equal(css_parse_inline("position:running", 0).position, CSS_POS_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).position, CSS_POS_UNSET);

    css_style s = css_parse_inline("top:10px; left:-4px; right:auto; bottom:2em", 0);
    assert_int_equal(s.inset_top, 10);
    assert_int_equal(s.inset_left, -4);
    assert_int_equal(s.inset_right, CSS_LEN_AUTO);
    assert_int_equal(s.inset_bottom, 32);             /* 2em x16 */
    assert_int_equal(css_parse_inline("top:50%", 0).inset_top, CSS_LEN_UNSET); /* % dropped */
    assert_int_equal(css_parse_inline("color:red", 0).inset_top, CSS_LEN_UNSET);

    /* inset shorthand (CSS order top right bottom left). */
    css_style i = css_parse_inline("inset:1px 2px 3px 4px", 0);
    assert_int_equal(i.inset_top, 1);  assert_int_equal(i.inset_right, 2);
    assert_int_equal(i.inset_bottom, 3); assert_int_equal(i.inset_left, 4);
    assert_int_equal(css_parse_inline("inset:5px", 0).inset_left, 5);

    assert_int_equal(css_parse_inline("z-index:7", 0).z_index, 7);
    assert_int_equal(css_parse_inline("z-index:-3", 0).z_index, -3);
    assert_int_equal(css_parse_inline("z-index:auto", 0).z_index, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("z-index:1.5", 0).z_index, CSS_LEN_UNSET); /* non-integer */
    assert_int_equal(css_parse_inline("color:red", 0).z_index, CSS_LEN_UNSET);
}

static void test_float_and_clear(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("float:left", 0).float_side, CSS_FLOAT_LEFT);
    assert_int_equal(css_parse_inline("float:RIGHT", 0).float_side, CSS_FLOAT_RIGHT);
    assert_int_equal(css_parse_inline("float:none", 0).float_side, CSS_FLOAT_NONE);
    assert_int_equal(css_parse_inline("float:inline-start", 0).float_side, CSS_FLOAT_UNSET); /* unknown */
    assert_int_equal(css_parse_inline("color:red", 0).float_side, CSS_FLOAT_UNSET);

    assert_int_equal(css_parse_inline("clear:both", 0).clear, CSS_CLEAR_BOTH);
    assert_int_equal(css_parse_inline("clear:left", 0).clear, CSS_CLEAR_LEFT);
    assert_int_equal(css_parse_inline("clear:right", 0).clear, CSS_CLEAR_RIGHT);
    assert_int_equal(css_parse_inline("clear:none", 0).clear, CSS_CLEAR_NONE);
    assert_int_equal(css_parse_inline("clear:all", 0).clear, CSS_CLEAR_UNSET); /* unknown */
    assert_int_equal(css_parse_inline("color:red", 0).clear, CSS_CLEAR_UNSET);

    /* Cascade + inline-wins, like every other box property. */
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(".a{float:left}", 14, &sh), CSS_OK);
    const char *cls[] = { "a" };
    assert_int_equal(css_resolve(sh, "div", NULL, cls, 1, NULL, 0).float_side, CSS_FLOAT_LEFT);
    assert_int_equal(css_resolve(sh, "div", NULL, cls, 1, "float:right", 0).float_side, CSS_FLOAT_RIGHT);
    css_free(sh);
}

static void test_visibility(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("visibility:visible", 0).visibility, CSS_VIS_VISIBLE);
    assert_int_equal(css_parse_inline("visibility:hidden", 0).visibility, CSS_VIS_HIDDEN);
    assert_int_equal(css_parse_inline("visibility:collapse", 0).visibility, CSS_VIS_COLLAPSE);
    assert_int_equal(css_parse_inline("visibility:bogus", 0).visibility, CSS_VIS_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).visibility, CSS_VIS_UNSET);

    css_sheet *sh = NULL;
    assert_int_equal(css_parse(".a{visibility:hidden}", 21, &sh), CSS_OK);
    const char *cls[] = { "a" };
    assert_int_equal(css_resolve(sh, "div", NULL, cls, 1, NULL, 0).visibility, CSS_VIS_HIDDEN);
    assert_int_equal(css_resolve(sh, "div", NULL, cls, 1, "visibility:visible", 0).visibility,
                      CSS_VIS_VISIBLE);
    css_free(sh);
}

static void test_overflow(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("overflow-x:hidden", 0).overflow_x, CSS_OF_HIDDEN);
    assert_int_equal(css_parse_inline("overflow-y:scroll", 0).overflow_y, CSS_OF_SCROLL);
    assert_int_equal(css_parse_inline("overflow-x:auto", 0).overflow_x, CSS_OF_AUTO);
    assert_int_equal(css_parse_inline("overflow-x:visible", 0).overflow_x, CSS_OF_VISIBLE);
    assert_int_equal(css_parse_inline("overflow-x:clip", 0).overflow_x, CSS_OF_HIDDEN);
    assert_int_equal(css_parse_inline("overflow-x:bogus", 0).overflow_x, CSS_OF_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).overflow_x, CSS_OF_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).overflow_y, CSS_OF_UNSET);

    /* Shorthand sets both axes. */
    css_style s = css_parse_inline("overflow:hidden", 0);
    assert_int_equal(s.overflow_x, CSS_OF_HIDDEN);
    assert_int_equal(s.overflow_y, CSS_OF_HIDDEN);
    assert_int_equal(css_parse_inline("overflow:bogus", 0).overflow_x, CSS_OF_UNSET);

    /* Longhand after shorthand in the same declaration block wins that axis. */
    s = css_parse_inline("overflow:hidden;overflow-y:visible", 0);
    assert_int_equal(s.overflow_x, CSS_OF_HIDDEN);
    assert_int_equal(s.overflow_y, CSS_OF_VISIBLE);
}

static void test_cursor(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("cursor:pointer", 0).cursor, CSS_CUR_POINTER);
    assert_int_equal(css_parse_inline("cursor:default", 0).cursor, CSS_CUR_DEFAULT);
    assert_int_equal(css_parse_inline("cursor:not-allowed", 0).cursor, CSS_CUR_NOT_ALLOWED);
    assert_int_equal(css_parse_inline("cursor:zoom-in", 0).cursor, CSS_CUR_ZOOM_IN);
    assert_int_equal(css_parse_inline("cursor:bogus", 0).cursor, CSS_CUR_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).cursor, CSS_CUR_UNSET);

    css_sheet *sh = NULL;
    assert_int_equal(css_parse("a.btn{cursor:pointer}", 21, &sh), CSS_OK);
    const char *cls[] = { "btn" };
    assert_int_equal(css_resolve(sh, "a", NULL, cls, 1, NULL, 0).cursor, CSS_CUR_POINTER);
    css_free(sh);
}

static void test_text_overflow_and_word_break(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("text-overflow:ellipsis", 0).text_overflow, CSS_TO_ELLIPSIS);
    assert_int_equal(css_parse_inline("text-overflow:clip", 0).text_overflow, CSS_TO_CLIP);
    assert_int_equal(css_parse_inline("text-overflow:bogus", 0).text_overflow, CSS_TO_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).text_overflow, CSS_TO_UNSET);

    assert_int_equal(css_parse_inline("word-break:break-all", 0).word_break, CSS_WB_BREAK);
    assert_int_equal(css_parse_inline("word-break:normal", 0).word_break, CSS_WB_NORMAL);
    assert_int_equal(css_parse_inline("word-break:keep-all", 0).word_break, CSS_WB_NORMAL);
    assert_int_equal(css_parse_inline("word-break:bogus", 0).word_break, CSS_WB_UNSET);

    assert_int_equal(css_parse_inline("overflow-wrap:break-word", 0).word_break, CSS_WB_BREAK);
    assert_int_equal(css_parse_inline("overflow-wrap:anywhere", 0).word_break, CSS_WB_BREAK);
    assert_int_equal(css_parse_inline("overflow-wrap:normal", 0).word_break, CSS_WB_NORMAL);
    assert_int_equal(css_parse_inline("word-wrap:break-word", 0).word_break, CSS_WB_BREAK);
    assert_int_equal(css_parse_inline("color:red", 0).word_break, CSS_WB_UNSET);

    /* Inherits like white-space: nearest ancestor wins. */
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("p{word-break:break-all}", 24, &sh), CSS_OK);
    assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).word_break, CSS_WB_BREAK);
    css_free(sh);
}

static void test_box_sizing(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("box-sizing:border-box", 0).box_sizing, CSS_BOXS_BORDER);
    assert_int_equal(css_parse_inline("box-sizing:content-box", 0).box_sizing, CSS_BOXS_CONTENT);
    assert_int_equal(css_parse_inline("box-sizing:padding-box", 0).box_sizing, CSS_BOXS_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).box_sizing, CSS_BOXS_UNSET);
}

static void test_border_shorthand(void **state) {
    (void)state;
    /* border: <width> <style> <color> in any order -> all four sides. */
    css_style s = css_parse_inline("border:2px solid #ff0000", 0);
    assert_int_equal(s.border_top_width, 2);
    assert_int_equal(s.border_right_width, 2);
    assert_int_equal(s.border_bottom_width, 2);
    assert_int_equal(s.border_left_width, 2);
    assert_int_equal(s.border_top_style, CSS_BST_SOLID);
    assert_int_equal(s.border_left_style, CSS_BST_SOLID);
    assert_int_equal(s.border_top_color, 0xff0000);
    assert_int_equal(s.border_bottom_color, 0xff0000);
    /* width keywords + reordered tokens. */
    css_style k = css_parse_inline("border:dashed thick blue", 0);
    assert_int_equal(k.border_top_width, 5);          /* thick */
    assert_int_equal(k.border_top_style, CSS_BST_DASHED);
    assert_int_equal(k.border_top_color, 0x0000ff);
    /* per-side shorthand sets only that side. */
    css_style b = css_parse_inline("border-bottom:1px dotted green", 0);
    assert_int_equal(b.border_bottom_width, 1);
    assert_int_equal(b.border_bottom_style, CSS_BST_DOTTED);
    assert_int_equal(b.border_top_width, CSS_LEN_UNSET);   /* untouched */
    assert_int_equal(b.border_top_style, CSS_BST_UNSET);
    /* omitted longhand stays unset (no initial reset). */
    css_style p = css_parse_inline("border:3px solid", 0);
    assert_int_equal(p.border_top_width, 3);
    assert_int_equal(p.border_top_style, CSS_BST_SOLID);
    assert_int_equal(p.border_top_color, -1);             /* color absent */
}

static void test_border_longhands(void **state) {
    (void)state;
    /* border-width / -style / -color expand 1-4 values (CSS side order). */
    css_style w = css_parse_inline("border-width:1px 2px 3px 4px", 0);
    assert_int_equal(w.border_top_width, 1);  assert_int_equal(w.border_right_width, 2);
    assert_int_equal(w.border_bottom_width, 3); assert_int_equal(w.border_left_width, 4);
    css_style st = css_parse_inline("border-style:solid dashed", 0);
    assert_int_equal(st.border_top_style, CSS_BST_SOLID);
    assert_int_equal(st.border_bottom_style, CSS_BST_SOLID);
    assert_int_equal(st.border_right_style, CSS_BST_DASHED);
    assert_int_equal(st.border_left_style, CSS_BST_DASHED);
    css_style c = css_parse_inline("border-color:red", 0);
    assert_int_equal(c.border_top_color, 0xff0000);
    assert_int_equal(c.border_left_color, 0xff0000);
    /* single per-side longhand. */
    assert_int_equal(css_parse_inline("border-left-width:6px", 0).border_left_width, 6);
    assert_int_equal(css_parse_inline("border-top-style:double", 0).border_top_style, CSS_BST_DOUBLE);
    assert_int_equal(css_parse_inline("border-right-color:#00ff00", 0).border_right_color, 0x00ff00);
    /* radius + fail-closed. */
    assert_int_equal(css_parse_inline("border-radius:8px", 0).border_radius, 8);
    assert_int_equal(css_parse_inline("border-radius:50%", 0).border_radius, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).border_radius, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).border_top_width, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).border_top_color, -1);
}

static void test_box_shadow_and_outline(void **state) {
    (void)state;
    css_style s = css_parse_inline("box-shadow:2px 4px 6px 1px #000000", 0);
    assert_int_equal(s.shadow2_dx, 2);
    assert_int_equal(s.shadow2_dy, 4);
    assert_int_equal(s.shadow2_blur, 6);
    assert_int_equal(s.shadow2_spread, 1);
    assert_int_equal(s.box_shadow_color, 0x000000);
    assert_int_equal(s.box_shadow_inset, 0);
    css_style in = css_parse_inline("box-shadow:inset 1px 2px red", 0);
    assert_int_equal(in.box_shadow_inset, 1);
    assert_int_equal(in.shadow2_dx, 1);
    assert_int_equal(in.box_shadow_color, 0xff0000);
    assert_int_equal(css_parse_inline("box-shadow:none", 0).box_shadow_color, -1);
    assert_int_equal(css_parse_inline("box-shadow:red", 0).box_shadow_inset, -1); /* <2 lengths dropped */
    assert_int_equal(css_parse_inline("box-shadow:url(x)", 0).box_shadow_inset, -1);
    assert_int_equal(css_parse_inline("color:red", 0).box_shadow_inset, -1);
    /* outline (uniform like border). */
    css_style o = css_parse_inline("outline:2px solid blue", 0);
    assert_int_equal(o.outline_width, 2);
    assert_int_equal(o.outline_style, CSS_BST_SOLID);
    assert_int_equal(o.outline_color, 0x0000ff);
    assert_int_equal(css_parse_inline("color:red", 0).outline_width, CSS_LEN_UNSET);
}

static void test_flex_item(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("flex-grow:2", 0).flex_grow, 200);     /* x100 */
    assert_int_equal(css_parse_inline("flex-grow:0.5", 0).flex_grow, 50);
    assert_int_equal(css_parse_inline("flex-shrink:0", 0).flex_shrink, 0);
    assert_int_equal(css_parse_inline("flex-grow:-1", 0).flex_grow, -1);     /* negative dropped -> unset */
    assert_int_equal(css_parse_inline("flex-basis:120px", 0).flex_basis, 120);
    assert_int_equal(css_parse_inline("flex-basis:auto", 0).flex_basis, CSS_LEN_AUTO);
    assert_int_equal(css_parse_inline("flex-basis:content", 0).flex_basis, CSS_LEN_AUTO);
    assert_int_equal(css_parse_inline("flex-basis:10%", 0).flex_basis, CSS_LEN_UNSET);
    /* shorthand. */
    css_style f1 = css_parse_inline("flex:1", 0);
    assert_int_equal(f1.flex_grow, 100); assert_int_equal(f1.flex_shrink, 100);
    assert_int_equal(f1.flex_basis, 0);
    css_style fn = css_parse_inline("flex:none", 0);
    assert_int_equal(fn.flex_grow, 0); assert_int_equal(fn.flex_shrink, 0);
    assert_int_equal(fn.flex_basis, CSS_LEN_AUTO);
    css_style fa = css_parse_inline("flex:auto", 0);
    assert_int_equal(fa.flex_grow, 100); assert_int_equal(fa.flex_basis, CSS_LEN_AUTO);
    css_style fe = css_parse_inline("flex:2 3 10px", 0);
    assert_int_equal(fe.flex_grow, 200); assert_int_equal(fe.flex_shrink, 300);
    assert_int_equal(fe.flex_basis, 10);
    assert_int_equal(css_parse_inline("order:-2", 0).order, -2);
    assert_int_equal(css_parse_inline("order:5", 0).order, 5);
    assert_int_equal(css_parse_inline("color:red", 0).order, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).flex_grow, -1);
    assert_int_equal(css_parse_inline("color:red", 0).flex_basis, CSS_LEN_UNSET);
}

static void test_flex_align(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("align-items:center", 0).align_items, CSS_AK_CENTER);
    assert_int_equal(css_parse_inline("align-items:flex-start", 0).align_items, CSS_AK_START);
    assert_int_equal(css_parse_inline("align-items:stretch", 0).align_items, CSS_AK_STRETCH);
    assert_int_equal(css_parse_inline("align-self:auto", 0).align_self, CSS_AK_AUTO);
    assert_int_equal(css_parse_inline("align-content:space-between", 0).align_content,
                     CSS_AK_SPACE_BETWEEN);
    assert_int_equal(css_parse_inline("justify-items:end", 0).justify_items, CSS_AK_END);
    assert_int_equal(css_parse_inline("flex-direction:column", 0).flex_direction, CSS_FD_COLUMN);
    assert_int_equal(css_parse_inline("flex-direction:column-reverse", 0).flex_direction,
                     CSS_FD_COLUMN_REVERSE);
    assert_int_equal(css_parse_inline("flex-direction:row-reverse", 0).flex_direction,
                     CSS_FD_ROW_REVERSE);
    assert_int_equal(css_parse_inline("flex-wrap:wrap", 0).flex_wrap, CSS_FW_WRAP);
    assert_int_equal(css_parse_inline("flex-wrap:wrap-reverse", 0).flex_wrap, CSS_FW_WRAP_REVERSE);
    assert_int_equal(css_parse_inline("flex-wrap:nowrap", 0).flex_wrap, CSS_FW_NOWRAP);
    assert_int_equal(css_parse_inline("align-items:bogus", 0).align_items, CSS_AK_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).align_items, CSS_AK_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).flex_direction, CSS_FD_UNSET);
}

static void test_grid_extras(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("grid-template-rows:1fr 1fr 1fr", 0).grid_rows, 3);
    assert_int_equal(css_parse_inline("grid-template-rows:none", 0).grid_rows, 0);
    assert_int_equal(css_parse_inline("row-gap:14px", 0).row_gap, 14);
    assert_int_equal(css_parse_inline("color:red", 0).row_gap, -1);
    assert_int_equal(css_parse_inline("grid-auto-flow:column", 0).grid_auto_flow, CSS_GF_COLUMN);
    assert_int_equal(css_parse_inline("grid-auto-flow:row dense", 0).grid_auto_flow, CSS_GF_ROW);
    assert_int_equal(css_parse_inline("grid-column:span 2", 0).grid_col_span, 2);
    assert_int_equal(css_parse_inline("grid-row:span 3", 0).grid_row_span, 3);
    assert_int_equal(css_parse_inline("grid-column:1 / 3", 0).grid_col_span, 0); /* line nums dropped */
    assert_int_equal(css_parse_inline("color:red", 0).grid_col_span, 0);
    /* column-gap still feeds `gap` (unchanged); row-gap is separate. */
    css_style g = css_parse_inline("gap:10px; row-gap:20px", 0);
    assert_int_equal(g.gap, 10);
    assert_int_equal(g.row_gap, 20);
}

static void test_layout_sheet_cascade_and_unset(void **state) {
    (void)state;
    /* A bare element resolves every new layout field to its unset sentinel. */
    css_style u = css_parse_inline("color:red", 0);
    assert_int_equal(u.position, CSS_POS_UNSET);
    assert_int_equal(u.inset_top, CSS_LEN_UNSET);
    assert_int_equal(u.z_index, CSS_LEN_UNSET);
    assert_int_equal(u.box_sizing, CSS_BOXS_UNSET);
    assert_int_equal(u.border_bottom_width, CSS_LEN_UNSET);
    assert_int_equal(u.border_radius, CSS_LEN_UNSET);
    assert_int_equal(u.box_shadow_color, -1);
    assert_int_equal(u.outline_color, -1);
    assert_int_equal(u.flex_grow, -1);
    assert_int_equal(u.flex_basis, CSS_LEN_UNSET);
    assert_int_equal(u.order, CSS_LEN_UNSET);
    assert_int_equal(u.align_items, CSS_AK_UNSET);
    assert_int_equal(u.grid_rows, 0);
    assert_int_equal(u.grid_auto_flow, CSS_GF_UNSET);
    /* Sheet cascade + inline override on a layout property. */
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(".card{position:absolute; border:1px solid red; z-index:2}",
                               0, &sh), CSS_OK);
    const char *cls[] = { "card" };
    css_style s = css_resolve(sh, "div", NULL, cls, 1, "z-index:9", 0);
    assert_int_equal(s.position, CSS_POS_ABSOLUTE);     /* from sheet */
    assert_int_equal(s.border_top_width, 1);
    assert_int_equal(s.border_top_style, CSS_BST_SOLID);
    assert_int_equal(s.z_index, 9);                     /* inline wins */
    css_free(sh);
    /* Anti-DoS clamp on a flex factor and span. */
    assert_int_equal(css_parse_inline("flex-grow:99999", 0).flex_grow, CSS_FLEX_FACTOR_MAX);
    assert_int_equal(css_parse_inline("grid-column:span 99999", 0).grid_col_span,
                     CSS_GRID_SPAN_MAX);
}

/* --- Outline longhands (outline-width/outline-style/outline-color) --- */
static void test_inline_outline_longhands(void **state) {
    (void)state;
    /* outline-width */
    assert_int_equal(css_parse_inline("outline-width:2px", 0).outline_width, 2);
    assert_int_equal(css_parse_inline("outline-width:thin", 0).outline_width, 1);
    assert_int_equal(css_parse_inline("outline-width:medium", 0).outline_width, 3);
    assert_int_equal(css_parse_inline("outline-width:thick", 0).outline_width, 5);
    assert_int_equal(css_parse_inline("outline-width:0", 0).outline_width, 0);
    assert_int_equal(css_parse_inline("outline-width:2em", 0).outline_width, 32);
    assert_int_equal(css_parse_inline("outline-width:auto", 0).outline_width, CSS_LEN_UNSET); /* dropped */
    assert_int_equal(css_parse_inline("outline-width:-1px", 0).outline_width, CSS_LEN_UNSET); /* negative dropped */
    /* outline-style */
    assert_int_equal(css_parse_inline("outline-style:solid", 0).outline_style, CSS_BST_SOLID);
    assert_int_equal(css_parse_inline("outline-style:dashed", 0).outline_style, CSS_BST_DASHED);
    assert_int_equal(css_parse_inline("outline-style:dotted", 0).outline_style, CSS_BST_DOTTED);
    assert_int_equal(css_parse_inline("outline-style:double", 0).outline_style, CSS_BST_DOUBLE);
    assert_int_equal(css_parse_inline("outline-style:groove", 0).outline_style, CSS_BST_GROOVE);
    assert_int_equal(css_parse_inline("outline-style:none", 0).outline_style, CSS_BST_NONE);
    assert_int_equal(css_parse_inline("outline-style:ridge", 0).outline_style, CSS_BST_RIDGE);
    assert_int_equal(css_parse_inline("outline-style:inset", 0).outline_style, CSS_BST_INSET);
    assert_int_equal(css_parse_inline("outline-style:outset", 0).outline_style, CSS_BST_OUTSET);
    assert_int_equal(css_parse_inline("outline-style:auto", 0).outline_style, CSS_BST_UNSET); /* unknown */
    /* outline-color */
    assert_int_equal(css_parse_inline("outline-color:red", 0).outline_color, 0xFF0000);
    assert_int_equal(css_parse_inline("outline-color:#00FF00", 0).outline_color, 0x00FF00);
    assert_int_equal(css_parse_inline("outline-color:rgba(0,0,255,0.5)", 0).outline_color, 0x0000FF);
    assert_int_equal(css_parse_inline("outline-color:auto", 0).outline_color, -1); /* dropped */
    assert_int_equal(css_parse_inline("color:red", 0).outline_color, -1); /* unset */
}

/* --- border-collapse --- */
static void test_inline_border_collapse(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("border-collapse:collapse", 0).border_collapse, CSS_BCOL_COLLAPSE);
    assert_int_equal(css_parse_inline("border-collapse:separate", 0).border_collapse, CSS_BCOL_SEPARATE);
    assert_int_equal(css_parse_inline("border-collapse:auto", 0).border_collapse, CSS_BCOL_UNSET); /* unknown */
    assert_int_equal(css_parse_inline("color:red", 0).border_collapse, CSS_BCOL_UNSET);
}

/* --- border-spacing --- */
static void test_inline_border_spacing(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("border-spacing:2px", 0).border_spacing, 2);
    assert_int_equal(css_parse_inline("border-spacing:0", 0).border_spacing, 0);
    assert_int_equal(css_parse_inline("border-spacing:1em", 0).border_spacing, 16);
    assert_int_equal(css_parse_inline("border-spacing:10 20", 0).border_spacing, 10); /* first value */
    assert_int_equal(css_parse_inline("border-spacing:auto", 0).border_spacing, CSS_LEN_UNSET); /* dropped */
    assert_int_equal(css_parse_inline("color:red", 0).border_spacing, CSS_LEN_UNSET);
}

/* --- empty-cells --- */
static void test_inline_empty_cells(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("empty-cells:show", 0).empty_cells, CSS_EC_SHOW);
    assert_int_equal(css_parse_inline("empty-cells:hide", 0).empty_cells, CSS_EC_HIDE);
    assert_int_equal(css_parse_inline("empty-cells:auto", 0).empty_cells, CSS_EC_UNSET); /* unknown */
    assert_int_equal(css_parse_inline("color:red", 0).empty_cells, CSS_EC_UNSET);
}

/* --- caption-side --- */
static void test_inline_caption_side(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("caption-side:top", 0).caption_side, CSS_CS_TOP);
    assert_int_equal(css_parse_inline("caption-side:bottom", 0).caption_side, CSS_CS_BOTTOM);
    assert_int_equal(css_parse_inline("caption-side:left", 0).caption_side, CSS_CS_UNSET); /* unknown */
    assert_int_equal(css_parse_inline("color:red", 0).caption_side, CSS_CS_UNSET);
}

/* --- table-layout --- */
static void test_inline_table_layout(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("table-layout:auto", 0).table_layout, CSS_TL_AUTO);
    assert_int_equal(css_parse_inline("table-layout:fixed", 0).table_layout, CSS_TL_FIXED);
    assert_int_equal(css_parse_inline("table-layout:collapse", 0).table_layout, CSS_TL_UNSET); /* unknown */
    assert_int_equal(css_parse_inline("color:red", 0).table_layout, CSS_TL_UNSET);
}

/* --- font-variant --- */
static void test_inline_font_variant(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("font-variant:small-caps", 0).font_variant, CSS_FV_SMALL_CAPS);
    assert_int_equal(css_parse_inline("font-variant:normal", 0).font_variant, CSS_FV_NORMAL);
    assert_int_equal(css_parse_inline("font-variant:all-small-caps", 0).font_variant, CSS_FV_UNSET); /* out of scope */
    assert_int_equal(css_parse_inline("color:red", 0).font_variant, CSS_FV_UNSET);
}

/* --- hyphens --- */
static void test_inline_hyphens(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("hyphens:none", 0).hyphens, CSS_HY_NONE);
    assert_int_equal(css_parse_inline("hyphens:manual", 0).hyphens, CSS_HY_MANUAL);
    assert_int_equal(css_parse_inline("hyphens:auto", 0).hyphens, CSS_HY_AUTO);
    assert_int_equal(css_parse_inline("hyphens:all", 0).hyphens, CSS_HY_UNSET); /* unknown */
    assert_int_equal(css_parse_inline("color:red", 0).hyphens, CSS_HY_UNSET);
}

/* --- user-select --- */
static void test_inline_user_select(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("user-select:none", 0).user_select, CSS_US_NONE);
    assert_int_equal(css_parse_inline("user-select:text", 0).user_select, CSS_US_TEXT);
    assert_int_equal(css_parse_inline("user-select:all", 0).user_select, CSS_US_ALL);
    assert_int_equal(css_parse_inline("user-select:auto", 0).user_select, CSS_US_AUTO);
    assert_int_equal(css_parse_inline("user-select:element", 0).user_select, CSS_US_UNSET); /* unknown */
    assert_int_equal(css_parse_inline("color:red", 0).user_select, CSS_US_UNSET);
}

/* --- caret-color --- */
static void test_inline_caret_color(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("caret-color:red", 0).caret_color, 0xFF0000);
    assert_int_equal(css_parse_inline("caret-color:#00FF00", 0).caret_color, 0x00FF00);
    assert_int_equal(css_parse_inline("caret-color:auto", 0).caret_color, CSS_LEN_AUTO);
    assert_int_equal(css_parse_inline("caret-color:blargh", 0).caret_color, -1); /* unknown -> unset */
    assert_int_equal(css_parse_inline("color:red", 0).caret_color, -1);
}

/* --- appearance --- */
static void test_inline_appearance(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("appearance:auto", 0).appearance, CSS_AP_AUTO);
    assert_int_equal(css_parse_inline("appearance:none", 0).appearance, CSS_AP_NONE);
    assert_int_equal(css_parse_inline("appearance:button", 0).appearance, CSS_AP_UNSET); /* unknown */
    assert_int_equal(css_parse_inline("color:red", 0).appearance, CSS_AP_UNSET);
}

/* --- pointer-events --- */
static void test_inline_pointer_events(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("pointer-events:auto", 0).pointer_events, CSS_PE_AUTO);
    assert_int_equal(css_parse_inline("pointer-events:none", 0).pointer_events, CSS_PE_NONE);
    assert_int_equal(css_parse_inline("pointer-events:all", 0).pointer_events, CSS_PE_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).pointer_events, CSS_PE_UNSET);
}

/* --- Table properties cascade from sheet + inline --- */
static void test_table_sheet_cascade(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse("table{border-collapse:collapse;empty-cells:hide;caption-side:bottom;table-layout:fixed}", 0, &sh), CSS_OK);
    css_element el = { "table", NULL, NULL, 0, NULL, 0, NULL, 0, 0, NULL, 0, 0, -1, NULL };
    css_style s = css_resolve_el(sh, &el, "border-spacing:4px", 0);
    assert_int_equal(s.border_collapse, CSS_BCOL_COLLAPSE);
    assert_int_equal(s.empty_cells, CSS_EC_HIDE);
    assert_int_equal(s.caption_side, CSS_CS_BOTTOM);
    assert_int_equal(s.table_layout, CSS_TL_FIXED);
    assert_int_equal(s.border_spacing, 4);
    css_free(sh);
}

/* --- background longhands + background shorthand fix --- */
static void test_inline_bg_repeat(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("background-repeat:repeat", 0).bg_repeat, CSS_BGR_REPEAT);
    assert_int_equal(css_parse_inline("background-repeat:no-repeat", 0).bg_repeat, CSS_BGR_NO_REPEAT);
    assert_int_equal(css_parse_inline("background-repeat:repeat-x", 0).bg_repeat, CSS_BGR_REPEAT_X);
    assert_int_equal(css_parse_inline("background-repeat:repeat-y", 0).bg_repeat, CSS_BGR_REPEAT_Y);
    assert_int_equal(css_parse_inline("background-repeat:space", 0).bg_repeat, CSS_BGR_SPACE);
    assert_int_equal(css_parse_inline("background-repeat:round", 0).bg_repeat, CSS_BGR_ROUND);
    assert_int_equal(css_parse_inline("background-repeat:stretch", 0).bg_repeat, CSS_BGR_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).bg_repeat, CSS_BGR_UNSET);
}

static void test_inline_bg_size(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("background-size:auto", 0).bg_size, CSS_BGS_AUTO);
    assert_int_equal(css_parse_inline("background-size:cover", 0).bg_size, CSS_BGS_COVER);
    assert_int_equal(css_parse_inline("background-size:contain", 0).bg_size, CSS_BGS_CONTAIN);
    assert_int_equal(css_parse_inline("background-size:100px", 0).bg_size, CSS_BGS_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).bg_size, CSS_BGS_UNSET);
}

static void test_inline_bg_clip_origin_attachment(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("background-clip:border-box", 0).bg_clip, CSS_BGC_BORDER_BOX);
    assert_int_equal(css_parse_inline("background-clip:padding-box", 0).bg_clip, CSS_BGC_PADDING_BOX);
    assert_int_equal(css_parse_inline("background-clip:content-box", 0).bg_clip, CSS_BGC_CONTENT_BOX);
    assert_int_equal(css_parse_inline("background-clip:text", 0).bg_clip, CSS_BGC_TEXT);
    assert_int_equal(css_parse_inline("background-clip:margin-box", 0).bg_clip, CSS_BGC_UNSET);
    assert_int_equal(css_parse_inline("background-origin:padding-box", 0).bg_origin, CSS_BGO_PADDING_BOX);
    assert_int_equal(css_parse_inline("background-origin:border-box", 0).bg_origin, CSS_BGO_BORDER_BOX);
    assert_int_equal(css_parse_inline("background-origin:content-box", 0).bg_origin, CSS_BGO_CONTENT_BOX);
    assert_int_equal(css_parse_inline("background-origin:margin-box", 0).bg_origin, CSS_BGO_UNSET);
    assert_int_equal(css_parse_inline("background-attachment:scroll", 0).bg_attachment, CSS_BGA_SCROLL);
    assert_int_equal(css_parse_inline("background-attachment:fixed", 0).bg_attachment, CSS_BGA_FIXED);
    assert_int_equal(css_parse_inline("background-attachment:local", 0).bg_attachment, CSS_BGA_LOCAL);
    assert_int_equal(css_parse_inline("background-attachment:auto", 0).bg_attachment, CSS_BGA_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).bg_clip, CSS_BGC_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).bg_origin, CSS_BGO_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).bg_attachment, CSS_BGA_UNSET);
}

static void test_inline_isolation(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("isolation:auto", 0).isolation, CSS_ISO_AUTO);
    assert_int_equal(css_parse_inline("isolation:isolate", 0).isolation, CSS_ISO_ISOLATE);
    assert_int_equal(css_parse_inline("isolation:unset", 0).isolation, CSS_ISO_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).isolation, CSS_ISO_UNSET);
}

static void test_inline_contain(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("contain:none", 0).contain, 0);
    assert_int_equal(css_parse_inline("contain:strict", 0).contain,
        CSS_CONTAIN_SIZE|CSS_CONTAIN_LAYOUT|CSS_CONTAIN_STYLE|CSS_CONTAIN_PAINT);
    assert_int_equal(css_parse_inline("contain:content", 0).contain,
        CSS_CONTAIN_LAYOUT|CSS_CONTAIN_STYLE|CSS_CONTAIN_PAINT);
    assert_int_equal(css_parse_inline("contain:size", 0).contain, CSS_CONTAIN_SIZE);
    assert_int_equal(css_parse_inline("contain:layout style paint", 0).contain,
        CSS_CONTAIN_LAYOUT|CSS_CONTAIN_STYLE|CSS_CONTAIN_PAINT);
    assert_int_equal(css_parse_inline("contain:paint size", 0).contain, CSS_CONTAIN_PAINT|CSS_CONTAIN_SIZE);
    assert_int_equal(css_parse_inline("contain:unknown", 0).contain, 0);
    assert_int_equal(css_parse_inline("color:red", 0).contain, 0);
}

static void test_inline_content_visibility(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("content-visibility:visible", 0).content_visibility, CSS_CV_VISIBLE);
    assert_int_equal(css_parse_inline("content-visibility:auto", 0).content_visibility, CSS_CV_AUTO);
    assert_int_equal(css_parse_inline("content-visibility:hidden", 0).content_visibility, CSS_CV_HIDDEN);
    assert_int_equal(css_parse_inline("content-visibility:show", 0).content_visibility, CSS_CV_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).content_visibility, CSS_CV_UNSET);
}

static void test_inline_image_rendering(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("image-rendering:auto", 0).image_rendering, CSS_IR_AUTO);
    assert_int_equal(css_parse_inline("image-rendering:pixelated", 0).image_rendering, CSS_IR_PIXELATED);
    assert_int_equal(css_parse_inline("image-rendering:crisp-edges", 0).image_rendering, CSS_IR_CRISP_EDGES);
    assert_int_equal(css_parse_inline("image-rendering:optimizeSpeed", 0).image_rendering, CSS_IR_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).image_rendering, CSS_IR_UNSET);
}

static void test_inline_color_scheme(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("color-scheme:normal", 0).color_scheme, CSS_CSH_NORMAL);
    assert_int_equal(css_parse_inline("color-scheme:light", 0).color_scheme, CSS_CSH_LIGHT);
    assert_int_equal(css_parse_inline("color-scheme:dark", 0).color_scheme, CSS_CSH_DARK);
    assert_int_equal(css_parse_inline("color-scheme:light dark", 0).color_scheme, CSS_CSH_LIGHT);
    assert_int_equal(css_parse_inline("color-scheme:auto", 0).color_scheme, CSS_CSH_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).color_scheme, CSS_CSH_UNSET);
}

static void test_inline_accent_color(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("accent-color:red", 0).accent_color, 0xFF0000);
    assert_int_equal(css_parse_inline("accent-color:#00FF00", 0).accent_color, 0x00FF00);
    assert_int_equal(css_parse_inline("accent-color:auto", 0).accent_color, CSS_LEN_AUTO);
    assert_int_equal(css_parse_inline("accent-color:blargh", 0).accent_color, -1);
    assert_int_equal(css_parse_inline("color:red", 0).accent_color, -1);
}

static void test_inline_print_forced_adjust(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("print-color-adjust:economy", 0).print_color_adjust, CSS_PCA_ECONOMY);
    assert_int_equal(css_parse_inline("print-color-adjust:exact", 0).print_color_adjust, CSS_PCA_EXACT);
    assert_int_equal(css_parse_inline("print-color-adjust:auto", 0).print_color_adjust, CSS_PCA_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).print_color_adjust, CSS_PCA_UNSET);
    assert_int_equal(css_parse_inline("forced-color-adjust:auto", 0).forced_color_adjust, CSS_FCA_AUTO);
    assert_int_equal(css_parse_inline("forced-color-adjust:none", 0).forced_color_adjust, CSS_FCA_NONE);
    assert_int_equal(css_parse_inline("forced-color-adjust:preserve", 0).forced_color_adjust, CSS_FCA_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).forced_color_adjust, CSS_FCA_UNSET);
}

/* --- Batch C: mix-blend-mode, object-fit, list-style-position, font-*, etc --- */

static void test_inline_mix_blend_mode(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("mix-blend-mode:normal", 0).mix_blend_mode, CSS_MB_NORMAL);
    assert_int_equal(css_parse_inline("mix-blend-mode:multiply", 0).mix_blend_mode, CSS_MB_MULTIPLY);
    assert_int_equal(css_parse_inline("mix-blend-mode:screen", 0).mix_blend_mode, CSS_MB_SCREEN);
    assert_int_equal(css_parse_inline("mix-blend-mode:overlay", 0).mix_blend_mode, CSS_MB_OVERLAY);
    assert_int_equal(css_parse_inline("mix-blend-mode:darken", 0).mix_blend_mode, CSS_MB_DARKEN);
    assert_int_equal(css_parse_inline("mix-blend-mode:lighten", 0).mix_blend_mode, CSS_MB_LIGHTEN);
    assert_int_equal(css_parse_inline("mix-blend-mode:color-dodge", 0).mix_blend_mode, CSS_MB_COLOR_DODGE);
    assert_int_equal(css_parse_inline("mix-blend-mode:color-burn", 0).mix_blend_mode, CSS_MB_COLOR_BURN);
    assert_int_equal(css_parse_inline("mix-blend-mode:difference", 0).mix_blend_mode, CSS_MB_DIFFERENCE);
    assert_int_equal(css_parse_inline("mix-blend-mode:exclusion", 0).mix_blend_mode, CSS_MB_EXCLUSION);
    assert_int_equal(css_parse_inline("mix-blend-mode:hue", 0).mix_blend_mode, CSS_MB_HUE);
    assert_int_equal(css_parse_inline("mix-blend-mode:saturation", 0).mix_blend_mode, CSS_MB_SATURATION);
    assert_int_equal(css_parse_inline("mix-blend-mode:color", 0).mix_blend_mode, CSS_MB_COLOR);
    assert_int_equal(css_parse_inline("mix-blend-mode:luminosity", 0).mix_blend_mode, CSS_MB_LUMINOSITY);
    assert_int_equal(css_parse_inline("mix-blend-mode:hard-light", 0).mix_blend_mode, CSS_MB_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).mix_blend_mode, CSS_MB_UNSET);
}

/* transform (M1.2, 2D translate only). */
static void test_inline_transform_translate(void **state) {
    (void)state;
    css_style s;

    s = css_parse_inline("transform:translate(10px,20px)", 0);
    assert_int_equal(s.transform_tx, 10);
    assert_int_equal(s.transform_ty, 20);

    s = css_parse_inline("transform:translate(10px)", 0); /* y defaults to 0 */
    assert_int_equal(s.transform_tx, 10);
    assert_int_equal(s.transform_ty, 0);

    s = css_parse_inline("transform:translateX(-15px)", 0);
    assert_int_equal(s.transform_tx, -15);
    assert_int_equal(s.transform_ty, CSS_LEN_UNSET);

    s = css_parse_inline("transform:translateY(7px)", 0);
    assert_int_equal(s.transform_tx, CSS_LEN_UNSET);
    assert_int_equal(s.transform_ty, 7);

    s = css_parse_inline("transform:translate(0,0)", 0); /* explicit zero still "set" */
    assert_int_equal(s.transform_tx, 0);
    assert_int_equal(s.transform_ty, 0);

    /* Unsupported/malformed: fails closed to unset, never a half-applied transform. */
    s = css_parse_inline("transform:none", 0);
    assert_int_equal(s.transform_tx, CSS_LEN_UNSET);
    assert_int_equal(s.transform_ty, CSS_LEN_UNSET);
    s = css_parse_inline("transform:translate(10%,10%)", 0); /* % unsupported */
    assert_int_equal(s.transform_tx, CSS_LEN_UNSET);
    s = css_parse_inline("transform:translateX(1px) translateY(2px)", 0); /* v1: one fn only */
    assert_int_equal(s.transform_tx, CSS_LEN_UNSET);
    s = css_parse_inline("transform:translate(10px,20px,30px)", 0); /* too many args */
    assert_int_equal(s.transform_tx, CSS_LEN_UNSET);
    s = css_parse_inline("color:red", 0);
    assert_int_equal(s.transform_tx, CSS_LEN_UNSET);
    assert_int_equal(s.transform_ty, CSS_LEN_UNSET);
}

/* transform: scale()/scaleX()/scaleY() (M1.2b), percent-of-identity ints. */
static void test_inline_transform_scale(void **state) {
    (void)state;
    css_style s;

    s = css_parse_inline("transform:scale(2)", 0); /* scale(sx) means scale(sx,sx) */
    assert_int_equal(s.transform_sx, 200);
    assert_int_equal(s.transform_sy, 200);

    s = css_parse_inline("transform:scale(1.5,0.5)", 0);
    assert_int_equal(s.transform_sx, 150);
    assert_int_equal(s.transform_sy, 50);

    s = css_parse_inline("transform:scaleX(0.8)", 0);
    assert_int_equal(s.transform_sx, 80);
    assert_int_equal(s.transform_sy, CSS_LEN_UNSET);

    s = css_parse_inline("transform:scaleY(1.25)", 0);
    assert_int_equal(s.transform_sx, CSS_LEN_UNSET);
    assert_int_equal(s.transform_sy, 125);

    s = css_parse_inline("transform:scale(-1)", 0); /* mirror: negative is valid */
    assert_int_equal(s.transform_sx, -100);
    assert_int_equal(s.transform_sy, -100);

    s = css_parse_inline("transform:scale(1)", 0); /* explicit identity still "set" */
    assert_int_equal(s.transform_sx, 100);
    assert_int_equal(s.transform_sy, 100);

    /* Unsupported/malformed: fails closed. */
    s = css_parse_inline("transform:scale(50%)", 0);   /* % unsupported for scale */
    assert_int_equal(s.transform_sx, CSS_LEN_UNSET);
    s = css_parse_inline("transform:scale()", 0);
    assert_int_equal(s.transform_sx, CSS_LEN_UNSET);
    s = css_parse_inline("transform:scaleX(1) scaleY(2)", 0); /* v1: one fn only */
    assert_int_equal(s.transform_sx, CSS_LEN_UNSET);
}

/* transform: rotate() (M1.2b), whole degrees only (deg suffix mandatory, same
 * convention as the linear-gradient angle grammar). */
static void test_inline_transform_rotate(void **state) {
    (void)state;
    css_style s;

    s = css_parse_inline("transform:rotate(45deg)", 0);
    assert_int_equal(s.transform_rotate, 45);

    s = css_parse_inline("transform:rotate(-90deg)", 0);
    assert_int_equal(s.transform_rotate, -90);

    s = css_parse_inline("transform:rotate(0deg)", 0); /* explicit zero still "set" */
    assert_int_equal(s.transform_rotate, 0);

    s = css_parse_inline("transform:rotate(720deg)", 0); /* not normalized mod 360 */
    assert_int_equal(s.transform_rotate, 720);

    /* Unsupported/malformed: fails closed (rad/turn/grad/fractional degrees,
     * matching the pre-existing linear-gradient angle grammar). */
    s = css_parse_inline("transform:rotate(1.5deg)", 0);
    assert_int_equal(s.transform_rotate, CSS_LEN_UNSET);
    s = css_parse_inline("transform:rotate(0.5turn)", 0);
    assert_int_equal(s.transform_rotate, CSS_LEN_UNSET);
    s = css_parse_inline("transform:rotate(1rad)", 0);
    assert_int_equal(s.transform_rotate, CSS_LEN_UNSET);
    s = css_parse_inline("transform:rotate(45)", 0); /* unitless: invalid */
    assert_int_equal(s.transform_rotate, CSS_LEN_UNSET);
    s = css_parse_inline("transform:matrix(1,0,0,1,0,0)", 0); /* still unsupported */
    assert_int_equal(s.transform_rotate, CSS_LEN_UNSET);
    assert_int_equal(s.transform_tx, CSS_LEN_UNSET);
    s = css_parse_inline("transform:skew(10deg)", 0); /* still unsupported */
    assert_int_equal(s.transform_rotate, CSS_LEN_UNSET);
}

/* Independent-cascade combination (M1.2b): translate/scale/rotate are separate
 * cascade slots, so two DIFFERENT rules matching the same element -- neither of
 * which chains functions -- can still combine into one composite transform. */
static void test_inline_transform_independent_cascade_combines(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(
        "#a { transform: translate(5px,6px); }"
        "#a.hot { transform: rotate(30deg); }", 0, &sh), CSS_OK);
    const char *cls[] = { "hot" };
    css_style s = css_resolve(sh, "div", "a", cls, 1, NULL, 0);
    assert_int_equal(s.transform_tx, 5);
    assert_int_equal(s.transform_ty, 6);
    assert_int_equal(s.transform_rotate, 30);
    css_free(sh);
}

static void test_inline_object_fit(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("object-fit:fill", 0).object_fit, CSS_OFI_FILL);
    assert_int_equal(css_parse_inline("object-fit:contain", 0).object_fit, CSS_OFI_CONTAIN);
    assert_int_equal(css_parse_inline("object-fit:cover", 0).object_fit, CSS_OFI_COVER);
    assert_int_equal(css_parse_inline("object-fit:none", 0).object_fit, CSS_OFI_NONE);
    assert_int_equal(css_parse_inline("object-fit:scale-down", 0).object_fit, CSS_OFI_SCALE_DOWN);
    assert_int_equal(css_parse_inline("object-fit:auto", 0).object_fit, CSS_OFI_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).object_fit, CSS_OFI_UNSET);
}

static void test_inline_list_style_pos(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("list-style-position:inside", 0).list_style_pos, CSS_LP_INSIDE);
    assert_int_equal(css_parse_inline("list-style-position:outside", 0).list_style_pos, CSS_LP_OUTSIDE);
    assert_int_equal(css_parse_inline("list-style-position:auto", 0).list_style_pos, CSS_LP_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).list_style_pos, CSS_LP_UNSET);
}

static void test_inline_font_kerning(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("font-kerning:auto", 0).font_kerning, CSS_FK_AUTO);
    assert_int_equal(css_parse_inline("font-kerning:normal", 0).font_kerning, CSS_FK_NORMAL);
    assert_int_equal(css_parse_inline("font-kerning:none", 0).font_kerning, CSS_FK_NONE);
    assert_int_equal(css_parse_inline("font-kerning:initial", 0).font_kerning, CSS_FK_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).font_kerning, CSS_FK_UNSET);
}

static void test_inline_text_rendering(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("text-rendering:auto", 0).text_rendering, CSS_TR_AUTO);
    assert_int_equal(css_parse_inline("text-rendering:optimizeSpeed", 0).text_rendering, CSS_TR_OPTIMIZE_SPEED);
    assert_int_equal(css_parse_inline("text-rendering:optimizeLegibility", 0).text_rendering, CSS_TR_OPTIMIZE_LEGIBILITY);
    assert_int_equal(css_parse_inline("text-rendering:geometricPrecision", 0).text_rendering, CSS_TR_GEOMETRIC_PRECISION);
    assert_int_equal(css_parse_inline("text-rendering:optimizeQuality", 0).text_rendering, CSS_TR_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).text_rendering, CSS_TR_UNSET);
}

static void test_inline_font_stretch(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("font-stretch:normal", 0).font_stretch, CSS_FS_NORMAL);
    assert_int_equal(css_parse_inline("font-stretch:condensed", 0).font_stretch, CSS_FS_CONDENSED);
    assert_int_equal(css_parse_inline("font-stretch:expanded", 0).font_stretch, CSS_FS_EXPANDED);
    assert_int_equal(css_parse_inline("font-stretch:ultra-condensed", 0).font_stretch, CSS_FS_ULTRA_CONDENSED);
    assert_int_equal(css_parse_inline("font-stretch:extra-condensed", 0).font_stretch, CSS_FS_EXTRA_CONDENSED);
    assert_int_equal(css_parse_inline("font-stretch:semi-condensed", 0).font_stretch, CSS_FS_SEMI_CONDENSED);
    assert_int_equal(css_parse_inline("font-stretch:semi-expanded", 0).font_stretch, CSS_FS_SEMI_EXPANDED);
    assert_int_equal(css_parse_inline("font-stretch:extra-expanded", 0).font_stretch, CSS_FS_EXTRA_EXPANDED);
    assert_int_equal(css_parse_inline("font-stretch:ultra-expanded", 0).font_stretch, CSS_FS_ULTRA_EXPANDED);
    assert_int_equal(css_parse_inline("font-stretch:oblique", 0).font_stretch, CSS_FS_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).font_stretch, CSS_FS_UNSET);
}

static void test_inline_resize(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("resize:none", 0).resize, CSS_RS_NONE);
    assert_int_equal(css_parse_inline("resize:both", 0).resize, CSS_RS_BOTH);
    assert_int_equal(css_parse_inline("resize:horizontal", 0).resize, CSS_RS_HORIZONTAL);
    assert_int_equal(css_parse_inline("resize:vertical", 0).resize, CSS_RS_VERTICAL);
    assert_int_equal(css_parse_inline("resize:auto", 0).resize, CSS_RS_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).resize, CSS_RS_UNSET);
}

static void test_inline_scroll_behavior(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("scroll-behavior:auto", 0).scroll_behavior, CSS_SB_AUTO);
    assert_int_equal(css_parse_inline("scroll-behavior:smooth", 0).scroll_behavior, CSS_SB_SMOOTH);
    assert_int_equal(css_parse_inline("scroll-behavior:instant", 0).scroll_behavior, CSS_SB_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).scroll_behavior, CSS_SB_UNSET);
}

static void test_inline_touch_action(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("touch-action:auto", 0).touch_action, CSS_TA_AUTO);
    assert_int_equal(css_parse_inline("touch-action:none", 0).touch_action, CSS_TA_NONE);
    assert_int_equal(css_parse_inline("touch-action:manipulation", 0).touch_action, CSS_TA_MANIPULATION);
    assert_int_equal(css_parse_inline("touch-action:pan-x", 0).touch_action, CSS_TA_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).touch_action, CSS_TA_UNSET);
}

static void test_inline_overscroll_behavior(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("overscroll-behavior:auto", 0).overscroll_behavior, CSS_OS_AUTO);
    assert_int_equal(css_parse_inline("overscroll-behavior:contain", 0).overscroll_behavior, CSS_OS_CONTAIN);
    assert_int_equal(css_parse_inline("overscroll-behavior:none", 0).overscroll_behavior, CSS_OS_NONE);
    assert_int_equal(css_parse_inline("overscroll-behavior:scroll", 0).overscroll_behavior, CSS_OS_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).overscroll_behavior, CSS_OS_UNSET);
}

static void test_inline_backface_visibility(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("backface-visibility:visible", 0).backface_visibility, CSS_BF_VISIBLE);
    assert_int_equal(css_parse_inline("backface-visibility:hidden", 0).backface_visibility, CSS_BF_HIDDEN);
    assert_int_equal(css_parse_inline("backface-visibility:auto", 0).backface_visibility, CSS_BF_UNSET);
    assert_int_equal(css_parse_inline("color:red", 0).backface_visibility, CSS_BF_UNSET);
}

/* --- Math functions min()/max()/clamp() (2026-07-10) --- */
static void test_math_min_max_top_level(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("width:min(600px, 40em)", 0).width, 600);
    assert_int_equal(css_parse_inline("width:max(600px, 40em)", 0).width, 640);
    assert_int_equal(css_parse_inline("margin-left:min(10px)", 0).margin_left, 10);
    /* mixing a length with a bare number fails the declaration (dimensional check) */
    assert_int_equal(css_parse_inline("width:min(600px, 5)", 0).width, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("width:min()", 0).width, CSS_LEN_UNSET);
    /* %/viewport units stay rejected inside math functions too */
    assert_int_equal(css_parse_inline("width:min(50%, 600px)", 0).width, CSS_LEN_UNSET);
}

static void test_math_clamp(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("width:clamp(100px, 50px, 300px)", 0).width, 100);
    assert_int_equal(css_parse_inline("width:clamp(100px, 200px, 300px)", 0).width, 200);
    assert_int_equal(css_parse_inline("width:clamp(100px, 500px, 300px)", 0).width, 300);
    /* clamp takes exactly three arguments */
    assert_int_equal(css_parse_inline("width:clamp(1px, 2px)", 0).width, CSS_LEN_UNSET);
    assert_int_equal(css_parse_inline("width:clamp(1px, 2px, 3px, 4px)", 0).width, CSS_LEN_UNSET);
}

static void test_math_nested_in_calc(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("width:calc(min(10px, 2em) * 2)", 0).width, 20);
    assert_int_equal(css_parse_inline("width:clamp(1em, calc(2px + 3px), 10px)", 0).width, 16);
    assert_int_equal(css_parse_inline("width:calc(100px * min(2, 3))", 0).width, 200);
    /* math functions inside a shorthand token (paren-aware splitter) */
    css_style s = css_parse_inline("margin:min(4px, 1em) max(2px, 8px)", 0);
    assert_int_equal(s.margin_top, 4);
    assert_int_equal(s.margin_right, 8);
    assert_int_equal(s.margin_bottom, 4);
    assert_int_equal(s.margin_left, 8);
}

/* --- Logical properties (physical LTR mapping, 2026-07-10) --- */
static void test_logical_margin_padding(void **state) {
    (void)state;
    css_style s = css_parse_inline("margin-inline-start:10px; margin-inline-end:20px", 0);
    assert_int_equal(s.margin_left, 10);
    assert_int_equal(s.margin_right, 20);
    s = css_parse_inline("margin-inline:30px", 0);
    assert_int_equal(s.margin_left, 30);
    assert_int_equal(s.margin_right, 30);
    s = css_parse_inline("margin-inline:1px 2px", 0);
    assert_int_equal(s.margin_left, 1);
    assert_int_equal(s.margin_right, 2);
    s = css_parse_inline("margin-block:5px 6px", 0);
    assert_int_equal(s.margin_top, 5);
    assert_int_equal(s.margin_bottom, 6);
    s = css_parse_inline("padding-inline:7px; padding-block-start:8px", 0);
    assert_int_equal(s.pad_left, 7);
    assert_int_equal(s.pad_right, 7);
    assert_int_equal(s.pad_top, 8);
    s = css_parse_inline("margin-inline:auto", 0);
    assert_int_equal(s.margin_left, CSS_LEN_AUTO);
    assert_int_equal(s.margin_right, CSS_LEN_AUTO);
    /* padding rejects negatives through the logical alias too (fail closed) */
    s = css_parse_inline("padding-inline:-4px", 0);
    assert_int_equal(s.pad_left, CSS_LEN_UNSET);
}

static void test_logical_inset_and_sizes(void **state) {
    (void)state;
    css_style s = css_parse_inline("inset-inline:4px 5px; inset-block:6px 7px", 0);
    assert_int_equal(s.inset_left, 4);
    assert_int_equal(s.inset_right, 5);
    assert_int_equal(s.inset_top, 6);
    assert_int_equal(s.inset_bottom, 7);
    s = css_parse_inline("inset-inline-start:1px; inset-block-end:2px", 0);
    assert_int_equal(s.inset_left, 1);
    assert_int_equal(s.inset_bottom, 2);
    s = css_parse_inline("inline-size:200px; block-size:100px", 0);
    assert_int_equal(s.width, 200);
    assert_int_equal(s.height, 100);
    s = css_parse_inline("min-inline-size:10px; max-inline-size:20px;"
                         "min-block-size:30px; max-block-size:40px", 0);
    assert_int_equal(s.min_width, 10);
    assert_int_equal(s.max_width, 20);
    assert_int_equal(s.min_height, 30);
    assert_int_equal(s.max_height, 40);
}

/* --- place-* shorthands + two-value gap (2026-07-10) --- */
static void test_place_shorthands(void **state) {
    (void)state;
    css_style s = css_parse_inline("place-items:center", 0);
    assert_int_equal(s.align_items, CSS_AK_CENTER);
    assert_int_equal(s.justify_items, CSS_AK_CENTER);
    s = css_parse_inline("place-items:start end", 0);
    assert_int_equal(s.align_items, CSS_AK_START);
    assert_int_equal(s.justify_items, CSS_AK_END);
    s = css_parse_inline("place-content:center space-between", 0);
    assert_int_equal(s.align_content, CSS_AK_CENTER);
    assert_int_equal(s.justify, CSS_JUSTIFY_SPACE_BETWEEN);
    s = css_parse_inline("place-content:center", 0);
    assert_int_equal(s.align_content, CSS_AK_CENTER);
    assert_int_equal(s.justify, CSS_JUSTIFY_CENTER);
    /* the justify-self half has no engine slot: align half still applies */
    s = css_parse_inline("place-self:center stretch", 0);
    assert_int_equal(s.align_self, CSS_AK_CENTER);
    /* an invalid keyword drops the whole shorthand (fail closed) */
    s = css_parse_inline("place-items:blargh", 0);
    assert_int_equal(s.align_items, CSS_AK_UNSET);
    assert_int_equal(s.justify_items, CSS_AK_UNSET);
}

static void test_gap_two_value(void **state) {
    (void)state;
    css_style s = css_parse_inline("gap:10px 20px", 0);
    assert_int_equal(s.row_gap, 10);
    assert_int_equal(s.gap, 20);
    s = css_parse_inline("gap:12px", 0);
    assert_int_equal(s.gap, 12);
    assert_int_equal(s.row_gap, -1);   /* one value keeps the prior semantics */
    s = css_parse_inline("grid-gap:1px 2px", 0);
    assert_int_equal(s.row_gap, 1);
    assert_int_equal(s.gap, 2);
    /* column-gap is a longhand: never takes two values */
    s = css_parse_inline("column-gap:3px 4px", 0);
    assert_int_equal(s.gap, -1);
}

/* --- font shorthand (2026-07-10) --- */
static void test_font_shorthand(void **state) {
    (void)state;
    css_style s = css_parse_inline("font:italic bold 32px/1.5 monospace", 0);
    assert_int_equal(s.italic, 1);
    assert_int_equal(s.bold, 1);
    assert_int_equal(s.font_scale, 200);   /* 32px on the 16px base */
    assert_int_equal(s.line_scale, 150);
    assert_int_equal(s.font_family, CSS_FF_MONO);
    s = css_parse_inline("font:16px sans-serif", 0);
    assert_int_equal(s.font_scale, 100);
    assert_int_equal(s.font_family, CSS_FF_SANS);
    assert_int_equal(s.bold, -1);          /* unmentioned longhands stay unset */
    s = css_parse_inline("font:small-caps 16px serif", 0);
    assert_int_equal(s.font_variant, CSS_FV_SMALL_CAPS);
    assert_int_equal(s.font_family, CSS_FF_SERIF);
    /* size + family are both required; system keywords drop the shorthand */
    assert_int_equal(css_parse_inline("font:caption", 0).font_scale, 0);
    assert_int_equal(css_parse_inline("font:16px", 0).font_scale, 0);
    assert_int_equal(css_parse_inline("font:sans-serif", 0).font_family, CSS_FF_UNSET);
}

/* --- white-space: break-spaces (2026-07-10) --- */
static void test_white_space_break_spaces(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("white-space:break-spaces", 0).white_space, CSS_WS_PRE_WRAP);
}

static void test_filter_blur_and_grayscale(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    assert_int_equal(css_parse(".a{filter:blur(5px)}.b{filter:grayscale(0.8)}"
                                ".c{filter:grayscale(1)}", 0, &sh), CSS_OK);
    const char *ca[] = { "a" };
    css_element ea = el_node("div", NULL, ca, 1, NULL);
    css_style sa = css_resolve_el(sh, &ea, NULL, 0);
    assert_int_equal(sa.filter_blur, 5);
    assert_int_equal(sa.filter_grayscale, 0);

    const char *cb[] = { "b" };
    css_element eb = el_node("div", NULL, cb, 1, NULL);
    css_style sb = css_resolve_el(sh, &eb, NULL, 0);
    assert_int_equal(sb.filter_blur, 0);
    assert_int_equal(sb.filter_grayscale, 80);

    const char *cc[] = { "c" };
    css_element ec = el_node("div", NULL, cc, 1, NULL);
    css_style sc = css_resolve_el(sh, &ec, NULL, 0);
    assert_int_equal(sc.filter_grayscale, 100);

    /* filter:none clears both */
    css_style sn = css_resolve_el(NULL, NULL, "filter:none", 0);
    assert_int_equal(sn.filter_blur, 0);
    css_free(sh);
}

static void test_anim_keyframes_resolved_from_sheet(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* Parse @keyframes + a rule that references it */
    assert_int_equal(css_parse(
        "@keyframes fadeOut { 0% { opacity: 1; } 100% { opacity: 0; } }\n"
        "div { animation-name: fadeOut; animation-duration: 2000ms; "
        "animation-iteration-count: infinite; }",
        0, &sh), CSS_OK);

    /* Resolve for <div>: should find @keyframes and populate anim_kf_* */
    css_style s = css_resolve(sh, "div", NULL, NULL, 0, NULL, 0);
    assert_string_equal(s.anim_name, "fadeOut");
    assert_int_equal(s.anim_duration_ms, 2000);
    assert_int_equal(s.anim_iterations, -1);  /* infinite */
    assert_int_equal(s.anim_nkf, 2);
    assert_int_equal(s.anim_kf_pct[0], 0);    /* 0% */
    assert_int_equal(s.anim_kf_val[0], 100);  /* opacity: 1 → 100 */
    assert_int_equal(s.anim_kf_pct[1], 10000);/* 100% * 100 = 10000 */
    assert_int_equal(s.anim_kf_val[1], 0);    /* opacity: 0 → 0 */

    /* Element without animation-name: no keyframes */
    css_style s2 = css_resolve(sh, "p", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s2.anim_nkf, 0);
    assert_int_equal(s2.anim_duration_ms, 0);

    /* NULL sheet: no crash, no keyframes */
    css_style s3 = css_resolve(NULL, "div", NULL, NULL, 0, NULL, 0);
    assert_int_equal(s3.anim_nkf, 0);

    css_free(sh);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_position_and_insets),
        cmocka_unit_test(test_float_and_clear),
        cmocka_unit_test(test_visibility),
        cmocka_unit_test(test_overflow),
        cmocka_unit_test(test_cursor),
        cmocka_unit_test(test_text_overflow_and_word_break),
        cmocka_unit_test(test_box_sizing),
        cmocka_unit_test(test_border_shorthand),
        cmocka_unit_test(test_border_longhands),
        cmocka_unit_test(test_box_shadow_and_outline),
        cmocka_unit_test(test_flex_item),
        cmocka_unit_test(test_flex_align),
        cmocka_unit_test(test_grid_extras),
        cmocka_unit_test(test_layout_sheet_cascade_and_unset),
        cmocka_unit_test(test_inline_box_longhands),
        cmocka_unit_test(test_box_shorthand_expansion),
        cmocka_unit_test(test_box_auto_and_centering),
        cmocka_unit_test(test_box_units_and_failclosed),
        cmocka_unit_test(test_calc_basic_arithmetic),
        cmocka_unit_test(test_calc_precedence_and_parens),
        cmocka_unit_test(test_calc_units_and_signs),
        cmocka_unit_test(test_calc_dimension_errors_fail_closed),
        cmocka_unit_test(test_width_percent_carried_symbolically),
        cmocka_unit_test(test_calc_clamped_anti_dos),
        cmocka_unit_test(test_calc_inside_shorthands),
        cmocka_unit_test(test_calc_with_custom_property),
        cmocka_unit_test(test_box_clamp_anti_dos),
        cmocka_unit_test(test_inline_min_width_height),
        cmocka_unit_test(test_inline_min_max_height),
        cmocka_unit_test(test_box_extension_sheet_cascade),
        cmocka_unit_test(test_inline_text_decoration_color_style),
        cmocka_unit_test(test_inline_text_decoration_thickness),
        cmocka_unit_test(test_inline_aspect_ratio),
        cmocka_unit_test(test_inline_direction),
        cmocka_unit_test(test_inline_outline_offset),
        cmocka_unit_test(test_inline_tab_size),
        cmocka_unit_test(test_box_sheet_cascade_inline_wins),
        cmocka_unit_test(test_inline_color_and_bg),
        cmocka_unit_test(test_inline_text_align),
        cmocka_unit_test(test_inline_font_size),
        cmocka_unit_test(test_inline_line_height),
        cmocka_unit_test(test_inline_font_weight_style),
        cmocka_unit_test(test_inline_text_decoration),
        cmocka_unit_test(test_text_decoration_cascade),
        cmocka_unit_test(test_font_family),
        cmocka_unit_test(test_text_transform),
        cmocka_unit_test(test_letter_word_spacing),
        cmocka_unit_test(test_text_shadow),
        cmocka_unit_test(test_opacity),
        cmocka_unit_test(test_vertical_align),
        cmocka_unit_test(test_text_indent),
        cmocka_unit_test(test_white_space),
        cmocka_unit_test(test_list_style_type),
        cmocka_unit_test(test_text_ext_cascade_and_important),
        cmocka_unit_test(test_inline_display),
        cmocka_unit_test(test_inline_container_props),
        cmocka_unit_test(test_sheet_container_props),
        cmocka_unit_test(test_container_cascade_inline_wins),
        cmocka_unit_test(test_container_fail_closed_and_bounds),
        cmocka_unit_test(test_grid_track_sizes_resolved),
        cmocka_unit_test(test_grid_repeat_expands_count),
        cmocka_unit_test(test_grid_minmax_counts_as_one_track),
        cmocka_unit_test(test_grid_repeat_autofill_fails_closed),
        cmocka_unit_test(test_grid_repeat_malformed_fails_closed),
        cmocka_unit_test(test_grid_repeat_clamped_anti_dos),
        cmocka_unit_test(test_container_unset),
        cmocka_unit_test(test_url_value_dropped),
        cmocka_unit_test(test_unknown_props_ignored),
        cmocka_unit_test(test_linear_gradient_basic),
        cmocka_unit_test(test_linear_gradient_directions),
        cmocka_unit_test(test_linear_gradient_stops),
        cmocka_unit_test(test_linear_gradient_fail_closed),
        cmocka_unit_test(test_background_shorthand_resets_gradient),
        cmocka_unit_test(test_bg_image_url_basic),
        cmocka_unit_test(test_bg_image_url_quoted),
        cmocka_unit_test(test_bg_image_url_absolute),
        cmocka_unit_test(test_bg_image_url_none_and_junk_reset),
        cmocka_unit_test(test_bg_image_url_overlong_fails_closed),
        cmocka_unit_test(test_bg_image_url_gradient_mutually_exclusive),
        cmocka_unit_test(test_bg_shorthand_captures_url_and_resets_color),
        cmocka_unit_test(test_bg_size_and_repeat),
        cmocka_unit_test(test_malformed_inline_no_crash),
        cmocka_unit_test(test_custom_prop_var_basic),
        cmocka_unit_test(test_custom_prop_var_fallback_used_when_missing),
        cmocka_unit_test(test_custom_prop_var_no_fallback_drops_decl),
        cmocka_unit_test(test_custom_prop_var_chain),
        cmocka_unit_test(test_custom_prop_var_self_reference_fails_closed),
        cmocka_unit_test(test_custom_prop_var_in_shorthand),
        cmocka_unit_test(test_custom_prop_var_later_declaration_wins),
        cmocka_unit_test(test_custom_prop_var_unbalanced_paren_drops),
        cmocka_unit_test(test_custom_prop_var_never_phones_home),
        cmocka_unit_test(test_sheet_type_selector),
        cmocka_unit_test(test_sheet_class_and_id),
        cmocka_unit_test(test_sheet_universal_and_group),
        cmocka_unit_test(test_sheet_compound_selector),
        cmocka_unit_test(test_descendant_combinator),
        cmocka_unit_test(test_child_combinator),
        cmocka_unit_test(test_combinator_specificity_sum),
        cmocka_unit_test(test_combinator_class_chain),
        cmocka_unit_test(test_adjacent_sibling_combinator),
        cmocka_unit_test(test_general_sibling_combinator),
        cmocka_unit_test(test_sibling_mixed_with_child),
        cmocka_unit_test(test_pseudo_link),
        cmocka_unit_test(test_pseudo_never_match_keeps_group),
        cmocka_unit_test(test_pseudo_structural),
        cmocka_unit_test(test_pseudo_nth_child),
        cmocka_unit_test(test_pseudo_nth_last_child),
        cmocka_unit_test(test_pseudo_root_and_form_state),
        cmocka_unit_test(test_pseudo_unknown_drops_selector),
        cmocka_unit_test(test_pseudo_specificity),
        cmocka_unit_test(test_pseudo_with_sibling_combinator),
        cmocka_unit_test(test_pseudo_nth_malformed_drops),
        cmocka_unit_test(test_pseudo_of_type),
        cmocka_unit_test(test_pseudo_nth_of_type),
        cmocka_unit_test(test_pseudo_empty),
        cmocka_unit_test(test_pseudo_target),
        cmocka_unit_test(test_pseudo_lang),
        cmocka_unit_test(test_has_parses_and_fails_closed),
        cmocka_unit_test(test_resolve_el_inline_only),
        cmocka_unit_test(test_attr_presence),
        cmocka_unit_test(test_attr_equals),
        cmocka_unit_test(test_attr_operators),
        cmocka_unit_test(test_attr_case_insensitive_flag),
        cmocka_unit_test(test_attr_name_case_insensitive),
        cmocka_unit_test(test_attr_quoted_value_with_space),
        cmocka_unit_test(test_attr_specificity_and_compound),
        cmocka_unit_test(test_attr_in_combinator),
        cmocka_unit_test(test_attr_malformed_fail_closed),
        cmocka_unit_test(test_important_inline_not_dropped),
        cmocka_unit_test(test_important_beats_specificity),
        cmocka_unit_test(test_important_tier_then_normal_order),
        cmocka_unit_test(test_important_inline_beats_sheet_important),
        cmocka_unit_test(test_important_in_shorthand),
        cmocka_unit_test(test_cascade_specificity),
        cmocka_unit_test(test_large_stylesheet_rules_beyond_old_cap),
        cmocka_unit_test(test_cascade_document_order),
        cmocka_unit_test(test_cascade_inline_wins),
        cmocka_unit_test(test_at_rules_skipped),
        cmocka_unit_test(test_media_screen_and_print),
        cmocka_unit_test(test_media_prefers_color_scheme),
        cmocka_unit_test(test_media_width_queries),
        cmocka_unit_test(test_media_and_or),
        cmocka_unit_test(test_media_unknown_fails_closed),
        cmocka_unit_test(test_parse_null_args),
        cmocka_unit_test(test_resolve_null_safe),
        cmocka_unit_test(test_inline_outline_longhands),
        cmocka_unit_test(test_inline_border_collapse),
        cmocka_unit_test(test_inline_border_spacing),
        cmocka_unit_test(test_inline_empty_cells),
        cmocka_unit_test(test_inline_caption_side),
        cmocka_unit_test(test_inline_table_layout),
        cmocka_unit_test(test_inline_font_variant),
        cmocka_unit_test(test_inline_hyphens),
        cmocka_unit_test(test_inline_user_select),
        cmocka_unit_test(test_inline_caret_color),
        cmocka_unit_test(test_inline_appearance),
        cmocka_unit_test(test_inline_pointer_events),
        cmocka_unit_test(test_table_sheet_cascade),
        cmocka_unit_test(test_inline_bg_repeat),
        cmocka_unit_test(test_inline_bg_size),
        cmocka_unit_test(test_inline_bg_clip_origin_attachment),
        cmocka_unit_test(test_inline_isolation),
        cmocka_unit_test(test_inline_contain),
        cmocka_unit_test(test_inline_content_visibility),
        cmocka_unit_test(test_inline_image_rendering),
        cmocka_unit_test(test_inline_color_scheme),
        cmocka_unit_test(test_inline_accent_color),
        cmocka_unit_test(test_inline_print_forced_adjust),
        cmocka_unit_test(test_inline_mix_blend_mode),
        cmocka_unit_test(test_inline_transform_translate),
        cmocka_unit_test(test_inline_transform_scale),
        cmocka_unit_test(test_inline_transform_rotate),
        cmocka_unit_test(test_inline_transform_independent_cascade_combines),
        cmocka_unit_test(test_inline_object_fit),
        cmocka_unit_test(test_inline_list_style_pos),
        cmocka_unit_test(test_inline_font_kerning),
        cmocka_unit_test(test_inline_text_rendering),
        cmocka_unit_test(test_inline_font_stretch),
        cmocka_unit_test(test_inline_resize),
        cmocka_unit_test(test_inline_scroll_behavior),
        cmocka_unit_test(test_inline_touch_action),
        cmocka_unit_test(test_inline_overscroll_behavior),
        cmocka_unit_test(test_inline_backface_visibility),
        cmocka_unit_test(test_math_min_max_top_level),
        cmocka_unit_test(test_math_clamp),
        cmocka_unit_test(test_math_nested_in_calc),
        cmocka_unit_test(test_logical_margin_padding),
        cmocka_unit_test(test_logical_inset_and_sizes),
        cmocka_unit_test(test_place_shorthands),
        cmocka_unit_test(test_gap_two_value),
        cmocka_unit_test(test_font_shorthand),
        cmocka_unit_test(test_white_space_break_spaces),
        cmocka_unit_test(test_filter_blur_and_grayscale),
        cmocka_unit_test(test_anim_keyframes_resolved_from_sheet),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
