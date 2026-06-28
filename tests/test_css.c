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
    e.tag = tag; e.id = id; e.classes = classes; e.nclasses = nc;
    e.attrs = NULL; e.nattrs = 0; e.parent = parent;
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

static void test_box_clamp_anti_dos(void **state) {
    (void)state;
    assert_int_equal(css_parse_inline("width:99999999px", 0).width, CSS_LEN_MAX);
    assert_int_equal(css_parse_inline("margin-top:99999999px", 0).margin_top, CSS_LEN_MAX);
    assert_int_equal(css_parse_inline("margin-top:-99999999px", 0).margin_top, -CSS_LEN_MAX);
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

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_inline_box_longhands),
        cmocka_unit_test(test_box_shorthand_expansion),
        cmocka_unit_test(test_box_auto_and_centering),
        cmocka_unit_test(test_box_units_and_failclosed),
        cmocka_unit_test(test_box_clamp_anti_dos),
        cmocka_unit_test(test_box_sheet_cascade_inline_wins),
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
