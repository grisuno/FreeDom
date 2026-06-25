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
    assert_int_equal(css_parse_inline("line-height:24px", 0).line_scale, 0);   /* absolute: dropped */
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

    /* gap aliases and a two-value gap (first token wins). */
    assert_int_equal(css_parse_inline("grid-gap:8px", 0).gap, 8);
    assert_int_equal(css_parse_inline("column-gap:6px", 0).gap, 6);
    assert_int_equal(css_parse_inline("gap:10px 4px", 0).gap, 10);
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

    /* A declaration value longer than the per-declaration token cap is dropped
     * entirely (fail closed, anti-DoS) — never silently truncated. The short
     * display:grid declaration in the same block still parses. */
    char buf[600];
    size_t k = (size_t)snprintf(buf, sizeof buf, "display:grid;grid-template-columns:");
    for (int i = 0; i < 100 && k + 4 < sizeof buf; ++i)
        k += (size_t)snprintf(buf + k, sizeof buf - k, "1fr ");
    css_style s = css_parse_inline(buf, 0);
    assert_int_equal(s.display, CSS_DISP_GRID);
    assert_int_equal(s.grid_cols, 0);
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
    /* a background with url() must NOT be honored (no fetch surface). */
    css_style s = css_parse_inline("background: url(http://evil/x.png) #112233", 0);
    assert_int_equal(s.background, -1);
    /* but a plain color background is fine. */
    assert_int_equal(css_parse_inline("background:#112233", 0).background, 0x112233);
}

static void test_unknown_props_ignored(void **state) {
    (void)state;
    css_style s = css_parse_inline("position:absolute; z-index:9; color:#abcdef; --x:1", 0);
    assert_int_equal(s.color, 0xabcdef);
    assert_int_equal(s.text_align, CSS_ALIGN_UNSET);
}

static void test_malformed_inline_no_crash(void **state) {
    (void)state;
    css_style s = css_parse_inline(";;: ; color ; :red; color::; color:#777;;", 0);
    assert_int_equal(s.color, 0x777777);
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
    e.tag = tag; e.id = id; e.classes = classes; e.nclasses = nc; e.parent = parent;
    return e;
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

static void test_sibling_combinator_unsupported(void **state) {
    (void)state;
    css_sheet *sh = NULL;
    /* '+' and '~' stay unsupported: those selectors drop, the group survives. */
    assert_int_equal(css_parse("a + b { color:#999999 } a ~ b { color:#777777 } "
                               "b { color:#080808 }", 0, &sh), CSS_OK);
    css_element b = el_node("b", NULL, NULL, 0, NULL);
    assert_int_equal(css_resolve_el(sh, &b, NULL, 0).color, 0x080808);
    css_free(sh);
}

static void test_resolve_el_inline_only(void **state) {
    (void)state;
    /* el == NULL resolves just the inline declarations (no crash, no match). */
    assert_int_equal(css_resolve_el(NULL, NULL, "color:#abcdef", 0).color, 0xabcdef);
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

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_inline_color_and_bg),
        cmocka_unit_test(test_inline_text_align),
        cmocka_unit_test(test_inline_font_size),
        cmocka_unit_test(test_inline_line_height),
        cmocka_unit_test(test_inline_font_weight_style),
        cmocka_unit_test(test_inline_display),
        cmocka_unit_test(test_inline_container_props),
        cmocka_unit_test(test_sheet_container_props),
        cmocka_unit_test(test_container_cascade_inline_wins),
        cmocka_unit_test(test_container_fail_closed_and_bounds),
        cmocka_unit_test(test_container_unset),
        cmocka_unit_test(test_url_value_dropped),
        cmocka_unit_test(test_unknown_props_ignored),
        cmocka_unit_test(test_malformed_inline_no_crash),
        cmocka_unit_test(test_sheet_type_selector),
        cmocka_unit_test(test_sheet_class_and_id),
        cmocka_unit_test(test_sheet_universal_and_group),
        cmocka_unit_test(test_sheet_compound_selector),
        cmocka_unit_test(test_descendant_combinator),
        cmocka_unit_test(test_child_combinator),
        cmocka_unit_test(test_combinator_specificity_sum),
        cmocka_unit_test(test_combinator_class_chain),
        cmocka_unit_test(test_sibling_combinator_unsupported),
        cmocka_unit_test(test_resolve_el_inline_only),
        cmocka_unit_test(test_cascade_specificity),
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
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
