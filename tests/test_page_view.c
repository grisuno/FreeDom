/*
 * TDD suite for page_view (Hito 5->6: HTML rendering display list).
 *
 * The pure model (pv_new/pv_append/pv_free) is tested directly; the DOM->list
 * builder (pv_build) is exercised by parsing real HTML with html_parse and
 * asserting on the produced runs.
 *
 * Build: make test   ;   ASan: make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "box_style.h"
#include "flex_layout.h"
#include "html_parse.h"
#include "page_view.h"

/* Parse helper: aborts the test on parse failure. Caller frees *doc. */
static hp_document *parse(const char *html) {
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(html, strlen(html), NULL, &doc), HP_OK);
    assert_non_null(doc);
    return doc;
}

/* Finds the i-th run whose collapsed text equals `text`; NULL if none. */
static const pv_run *find_text(const pv_view *v, const char *text) {
    for (size_t i = 0; i < pv_count(v); ++i) {
        const pv_run *r = pv_at(v, i);
        if (r->text != NULL && strcmp(r->text, text) == 0) return r;
    }
    return NULL;
}

/* Finds the first image run whose src equals `src`; NULL if none. */
static const pv_run *find_image(const pv_view *v, const char *src) {
    for (size_t i = 0; i < pv_count(v); ++i) {
        const pv_run *r = pv_at(v, i);
        if (r->kind == PV_IMAGE && r->src != NULL && strcmp(r->src, src) == 0) return r;
    }
    return NULL;
}

/* --- pure model: pv_new / pv_append / pv_free --- */

static void test_new_is_empty(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_non_null(v);
    assert_int_equal((int)pv_count(v), 0);
    assert_null(pv_at(v, 0));
    pv_free(v);
}

static void test_append_copies_fields(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 2, 1, "hello", NULL), PV_OK);
    assert_int_equal(pv_append(v, PV_LINK, 0, 0, "site", "https://x.example/"), PV_OK);
    assert_int_equal((int)pv_count(v), 2);

    const pv_run *a = pv_at(v, 0);
    assert_int_equal(a->kind, PV_TEXT);
    assert_int_equal(a->heading, 2);
    assert_int_equal(a->block_break, 1);
    assert_string_equal(a->text, "hello");
    assert_null(a->href);

    const pv_run *b = pv_at(v, 1);
    assert_int_equal(b->kind, PV_LINK);
    assert_string_equal(b->text, "site");
    assert_string_equal(b->href, "https://x.example/");

    /* Non-image runs carry no image fields: src NULL, dimensions unknown (-1). */
    assert_null(a->src);
    assert_int_equal(a->img_w, -1);
    assert_int_equal(a->img_h, -1);
    assert_null(b->src);
    pv_free(v);
}

static void test_append_image_copies_fields(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append_image(v, 0, 1, "a logo", "https://x.example/l.png", 200, 80), PV_OK);
    const pv_run *r = pv_at(v, 0);
    assert_non_null(r);
    assert_int_equal(r->kind, PV_IMAGE);
    assert_int_equal(r->block_break, 1);
    assert_string_equal(r->text, "a logo");
    assert_string_equal(r->src, "https://x.example/l.png");
    assert_null(r->href);
    assert_int_equal(r->img_w, 200);
    assert_int_equal(r->img_h, 80);
    pv_free(v);
}

static void test_append_image_null_args(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append_image(NULL, 0, 0, "alt", "https://x/i.png", 1, 1), PV_ERR_NULL_ARG);
    /* A missing src is not representable: src is required for an image run. */
    assert_int_equal(pv_append_image(v, 0, 0, "alt", NULL, 1, 1), PV_ERR_NULL_ARG);
    /* A NULL alt is allowed and stored as the empty string. */
    assert_int_equal(pv_append_image(v, 0, 0, NULL, "https://x/i.png", -1, -1), PV_OK);
    assert_string_equal(pv_at(v, 0)->text, "");
    pv_free(v);
}

static void test_append_sanitizes_utf8(void **state) {
    (void)state;
    pv_view *v = pv_new();
    const char latin1[] = { 'I', 'm', (char)0xE1, 'g', '\0' }; /* lone 0xE1 */
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, latin1, NULL), PV_OK);
    assert_string_equal(pv_at(v, 0)->text, "Im?g");
    pv_free(v);
}

static void test_append_null_args(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(NULL, PV_TEXT, 0, 0, "x", NULL), PV_ERR_NULL_ARG);
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, NULL, NULL), PV_ERR_NULL_ARG);
    pv_free(v);
}

static void test_free_null_and_double(void **state) {
    (void)state;
    pv_free(NULL);
    pv_view *v = pv_new();
    pv_free(v);
}

/* --- builder: pv_build --- */

static void test_build_null_args(void **state) {
    (void)state;
    pv_view *v = NULL;
    assert_int_equal(pv_build(NULL, &v), PV_ERR_NULL_ARG);
    hp_document *doc = parse("<p>x</p>");
    assert_int_equal(pv_build(doc, NULL), PV_ERR_NULL_ARG);
    hp_document_free(doc);
}

static void test_build_plain_text(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p>Hello world</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *r = find_text(v, "Hello world");
    assert_non_null(r);
    assert_int_equal(r->kind, PV_TEXT);
    assert_int_equal(r->heading, 0);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_heading_level(void **state) {
    (void)state;
    hp_document *doc = parse("<body><h2>Title</h2><p>body</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *h = find_text(v, "Title");
    assert_non_null(h);
    assert_int_equal(h->heading, 2);
    const pv_run *p = find_text(v, "body");
    assert_non_null(p);
    assert_int_equal(p->heading, 0);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_link_with_href(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p>see <a href=\"https://e.example/x\">here</a> now</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *link = find_text(v, "here");
    assert_non_null(link);
    assert_int_equal(link->kind, PV_LINK);
    assert_string_equal(link->href, "https://e.example/x");

    const pv_run *before = find_text(v, "see ");
    assert_non_null(before);
    assert_int_equal(before->kind, PV_TEXT);
    assert_null(before->href);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_block_break_between_paragraphs(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p>one</p><p>two</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *two = find_text(v, "two");
    assert_non_null(two);
    assert_int_equal(two->block_break, 1);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_skips_script_and_style(void **state) {
    (void)state;
    /* script is stripped by html_parse; style text must not leak into runs. */
    hp_document *doc = parse("<body><style>p{color:red}</style><p>visible</p>"
                             "<script>var x=1;</script></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    assert_non_null(find_text(v, "visible"));
    assert_null(find_text(v, "p{color:red}"));
    assert_null(find_text(v, "var x=1;"));
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_inline_link_no_break_within_paragraph(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p>a<a href=\"/b\">b</a>c</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    /* "a", link "b", "c" are all in the same block: only the first carries the
     * block break (from entering <p>); the inline link and trailing text do not. */
    const pv_run *b = find_text(v, "b");
    assert_non_null(b);
    assert_int_equal(b->kind, PV_LINK);
    assert_int_equal(b->block_break, 0);
    const pv_run *c = find_text(v, "c");
    assert_non_null(c);
    assert_int_equal(c->block_break, 0);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_image_with_dims(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p>before</p>"
                            "<img src=\"https://e.example/logo.png\" alt=\"Logo\" width=\"200\" height=\"80\">"
                            "<p>after</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *img = find_image(v, "https://e.example/logo.png");
    assert_non_null(img);
    assert_int_equal(img->kind, PV_IMAGE);
    assert_string_equal(img->text, "Logo");
    assert_int_equal(img->img_w, 200);
    assert_int_equal(img->img_h, 80);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_image_unknown_dims(void **state) {
    (void)state;
    /* No width/height attributes => unknown (-1); a non-empty alt is kept. */
    hp_document *doc = parse("<body><img src=\"https://e.example/p.jpg\" alt=\"Photo\"></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *img = find_image(v, "https://e.example/p.jpg");
    assert_non_null(img);
    assert_int_equal(img->img_w, -1);
    assert_int_equal(img->img_h, -1);
    assert_string_equal(img->text, "Photo");
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_image_px_and_tracking_dims(void **state) {
    (void)state;
    /* Leading integer is parsed even with a unit suffix; a 1x1 beacon keeps its
     * declared dimensions so render_policy can classify it as a tracker. */
    hp_document *doc = parse("<body>"
                            "<img src=\"https://e.example/wide.png\" width=\"640px\" height=\"480px\">"
                            "<img src=\"https://t.example/beacon.gif\" width=\"1\" height=\"1\">"
                            "</body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *wide = find_image(v, "https://e.example/wide.png");
    assert_non_null(wide);
    assert_int_equal(wide->img_w, 640);
    assert_int_equal(wide->img_h, 480);
    const pv_run *beacon = find_image(v, "https://t.example/beacon.gif");
    assert_non_null(beacon);
    assert_int_equal(beacon->img_w, 1);
    assert_int_equal(beacon->img_h, 1);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_image_in_skipped_subtree_ignored(void **state) {
    (void)state;
    /* An <img> inside <noscript> is in a non-rendered subtree: no run emitted. */
    hp_document *doc = parse("<body><noscript><img src=\"https://e.example/x.png\"></noscript>"
                            "<p>visible</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    assert_null(find_image(v, "https://e.example/x.png"));
    assert_non_null(find_text(v, "visible"));
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_image_without_src_ignored(void **state) {
    (void)state;
    /* An <img> with no src has nothing to load and nothing to show: skipped. */
    hp_document *doc = parse("<body><img alt=\"orphan\"><p>kept</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    for (size_t i = 0; i < pv_count(v); ++i) {
        assert_int_not_equal(pv_at(v, i)->kind, PV_IMAGE);
    }
    assert_non_null(find_text(v, "kept"));
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_empty_document(void **state) {
    (void)state;
    hp_document *doc = parse("<html><head><title>t</title></head><body></body></html>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    assert_non_null(v);
    /* No visible body text => no runs (title lives outside the body view). */
    assert_int_equal((int)pv_count(v), 0);
    pv_free(v);
    hp_document_free(doc);
}

/* The pure model defaults a run's author color to -1 (none); pv_set_color sets it
 * on the most recent run and is a safe no-op on an empty view. */
static void test_set_color_model(void **state) {
    (void)state;
    pv_view *v = pv_new();
    pv_set_color(v, 0x102030); /* no-op: empty view */
    assert_int_equal((int)pv_count(v), 0);

    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, "x", NULL), PV_OK);
    assert_int_equal(pv_at(v, 0)->fg_rgb, -1); /* default */
    assert_int_equal(pv_at(v, 0)->bg_rgb, -1); /* default */
    pv_set_color(v, 0x123456);
    assert_int_equal(pv_at(v, 0)->fg_rgb, 0x123456);
    pv_set_bgcolor(v, 0x654321);
    assert_int_equal(pv_at(v, 0)->bg_rgb, 0x654321);

    pv_set_color(NULL, 0);    /* NULL-safe */
    pv_set_bgcolor(NULL, 0);  /* NULL-safe */
    pv_free(v);
}

/* pv_build extracts the author foreground color: inline style "color:" and the
 * legacy <font color>; the nearest ancestor that sets a color wins (inheritance);
 * background-color is never mistaken for color; an unparseable value yields -1. */
static void test_build_author_color(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body>"
        "<p style='color:#ff0000'>red text</p>"
        "<p style='background-color:#00ff00'>plain text</p>"
        "<font color='blue'>blue text</font>"
        "<p style='color:bogusvalue'>fallback text</p>"
        "<div style='color:#112233'><span>inherited text</span></div>"
        "<div style='background-color:#abcdef'><span>bg inherited</span></div>"
        "</body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *red = find_text(v, "red text");
    assert_non_null(red);
    assert_int_equal(red->fg_rgb, 0xff0000);
    assert_int_equal(red->bg_rgb, -1); /* no background-color set */

    const pv_run *plain = find_text(v, "plain text");
    assert_non_null(plain);
    assert_int_equal(plain->fg_rgb, -1); /* background-color is not color */
    assert_int_equal(plain->bg_rgb, 0x00ff00); /* author background-color */

    const pv_run *bg_inh = find_text(v, "bg inherited");
    assert_non_null(bg_inh);
    assert_int_equal(bg_inh->bg_rgb, 0xabcdef); /* nearest ancestor background-color */
    assert_int_equal(bg_inh->fg_rgb, -1);

    const pv_run *blue = find_text(v, "blue text");
    assert_non_null(blue);
    assert_int_equal(blue->fg_rgb, 0x0000ff);

    const pv_run *fallback = find_text(v, "fallback text");
    assert_non_null(fallback);
    assert_int_equal(fallback->fg_rgb, -1); /* unparseable value */

    const pv_run *inherited = find_text(v, "inherited text");
    assert_non_null(inherited);
    assert_int_equal(inherited->fg_rgb, 0x112233); /* nearest ancestor with color */

    pv_free(v);
    hp_document_free(doc);
}

/* pv_build records the nearest author flex/grid container per run: its id, display,
 * and parsed gap/justify/columns. Runs of one container share the id; a second
 * container gets a new id; content outside any container has cont_id == -1. */
static void test_build_flex_container(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body>"
        "<div style='display:flex;gap:10px;justify-content:center'>"
        "<p>one</p><p>two</p></div>"
        "<div style='display:flex'><p>second</p></div>"
        "<p>outside</p>"
        "</body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *one = find_text(v, "one");
    const pv_run *two = find_text(v, "two");
    assert_non_null(one);
    assert_non_null(two);
    assert_int_equal(one->cont_display, BX_DISPLAY_FLEX);
    assert_int_equal(one->cont_gap, 10);
    assert_int_equal(one->cont_justify, FX_JUSTIFY_CENTER);
    assert_int_equal(one->cont_id, two->cont_id);   /* same container */
    assert_true(one->cont_id >= 0);

    const pv_run *second = find_text(v, "second");
    assert_non_null(second);
    assert_int_equal(second->cont_display, BX_DISPLAY_FLEX);
    assert_int_not_equal(second->cont_id, one->cont_id); /* a different container */
    assert_int_equal(second->cont_justify, FX_JUSTIFY_START); /* default */

    const pv_run *outside = find_text(v, "outside");
    assert_non_null(outside);
    assert_int_equal(outside->cont_id, -1);  /* no container */

    pv_free(v);
    hp_document_free(doc);
}

static void test_build_grid_container(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><div style='display:grid;grid-template-columns:1fr 1fr 1fr'>"
        "<span>a</span><span>b</span></div></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *a = find_text(v, "a");
    assert_non_null(a);
    assert_int_equal(a->cont_display, BX_DISPLAY_GRID);
    assert_int_equal(a->cont_cols, 3);
    assert_true(a->cont_id >= 0);

    pv_free(v);
    hp_document_free(doc);
}

/* A run with no flex/grid ancestor carries the no-container defaults. */
static void test_container_defaults(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, "x", NULL), PV_OK);
    assert_int_equal(pv_at(v, 0)->cont_id, -1);
    assert_int_equal(pv_at(v, 0)->cont_display, 0);
    pv_set_container(v, 2, BX_DISPLAY_GRID, 8, FX_JUSTIFY_END, 4);
    assert_int_equal(pv_at(v, 0)->cont_id, 2);
    assert_int_equal(pv_at(v, 0)->cont_display, BX_DISPLAY_GRID);
    assert_int_equal(pv_at(v, 0)->cont_cols, 4);
    pv_set_container(NULL, 0, 0, 0, 0, 0); /* NULL-safe */
    pv_free(v);
}

/* Finds the first PV_INPUT run whose name equals `name`; NULL if none. */
static const pv_run *find_input(const pv_view *v, const char *name) {
    for (size_t i = 0; i < pv_count(v); ++i) {
        const pv_run *r = pv_at(v, i);
        if (r->kind == PV_INPUT && r->name != NULL && strcmp(r->name, name) == 0) return r;
    }
    return NULL;
}

/* --- form / input extraction --- */

static void test_build_search_form_get(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><form action=\"/search\" method=\"get\">"
        "<input type=\"search\" name=\"q\" placeholder=\"Search...\">"
        "<input type=\"submit\" value=\"Go\">"
        "</form></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *q = find_input(v, "q");
    assert_non_null(q);
    assert_int_equal(q->input_type, PV_IN_TEXT);
    assert_string_equal(q->text, "Search...");      /* placeholder is the display text */
    assert_string_equal(q->href, "/search");          /* form action carried on href */
    assert_int_equal(q->form_method, PV_METHOD_GET);
    assert_true(q->form_id >= 0);

    /* The submit button shares the same form group and carries its label. */
    int found_submit = 0;
    for (size_t i = 0; i < pv_count(v); ++i) {
        const pv_run *r = pv_at(v, i);
        if (r->kind == PV_INPUT && r->input_type == PV_IN_SUBMIT) {
            assert_string_equal(r->text, "Go");
            assert_int_equal(r->form_id, q->form_id);
            found_submit = 1;
        }
    }
    assert_true(found_submit);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_form_post_and_hidden(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<form action=\"https://site.example/login\" method=\"POST\">"
        "<input type=\"text\" name=\"user\" value=\"bob\">"
        "<input type=\"hidden\" name=\"csrf\" value=\"tok123\">"
        "<button>Log in</button>"
        "</form>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *user = find_input(v, "user");
    assert_non_null(user);
    assert_int_equal(user->form_method, PV_METHOD_POST);
    assert_string_equal(user->value, "bob");
    assert_string_equal(user->href, "https://site.example/login");

    const pv_run *csrf = find_input(v, "csrf");
    assert_non_null(csrf);
    assert_int_equal(csrf->input_type, PV_IN_HIDDEN);
    assert_string_equal(csrf->value, "tok123");

    /* A <button> with no type defaults to submit; its label is its text. */
    int found = 0;
    for (size_t i = 0; i < pv_count(v); ++i) {
        const pv_run *r = pv_at(v, i);
        if (r->kind == PV_INPUT && r->input_type == PV_IN_SUBMIT
            && r->text != NULL && strcmp(r->text, "Log in") == 0) found = 1;
    }
    assert_true(found);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_textarea_value(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<form><textarea name=\"msg\">hello world</textarea></form>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *msg = find_input(v, "msg");
    assert_non_null(msg);
    assert_int_equal(msg->input_type, PV_IN_TEXTAREA);
    assert_string_equal(msg->value, "hello world");
    /* The textarea content must NOT also appear as a plain text run. */
    assert_null(find_text(v, "hello world"));
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_control_without_form(void **state) {
    (void)state;
    hp_document *doc = parse("<input type=\"text\" name=\"loose\">");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *r = find_input(v, "loose");
    assert_non_null(r);
    assert_int_equal(r->form_id, -1);   /* no owning form */
    assert_null(r->href);               /* no action */
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_two_forms_distinct_groups(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<form action=\"/a\"><input name=\"x\"></form>"
        "<form action=\"/b\"><input name=\"y\"></form>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *x = find_input(v, "x");
    const pv_run *y = find_input(v, "y");
    assert_non_null(x);
    assert_non_null(y);
    assert_int_not_equal(x->form_id, y->form_id);
    assert_string_equal(x->href, "/a");
    assert_string_equal(y->href, "/b");
    pv_free(v);
    hp_document_free(doc);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_is_empty),
        cmocka_unit_test(test_append_copies_fields),
        cmocka_unit_test(test_append_image_copies_fields),
        cmocka_unit_test(test_append_image_null_args),
        cmocka_unit_test(test_append_sanitizes_utf8),
        cmocka_unit_test(test_append_null_args),
        cmocka_unit_test(test_free_null_and_double),
        cmocka_unit_test(test_build_null_args),
        cmocka_unit_test(test_build_plain_text),
        cmocka_unit_test(test_build_heading_level),
        cmocka_unit_test(test_build_link_with_href),
        cmocka_unit_test(test_build_block_break_between_paragraphs),
        cmocka_unit_test(test_build_skips_script_and_style),
        cmocka_unit_test(test_build_inline_link_no_break_within_paragraph),
        cmocka_unit_test(test_build_image_with_dims),
        cmocka_unit_test(test_build_image_unknown_dims),
        cmocka_unit_test(test_build_image_px_and_tracking_dims),
        cmocka_unit_test(test_build_image_in_skipped_subtree_ignored),
        cmocka_unit_test(test_build_image_without_src_ignored),
        cmocka_unit_test(test_build_empty_document),
        cmocka_unit_test(test_set_color_model),
        cmocka_unit_test(test_build_author_color),
        cmocka_unit_test(test_build_flex_container),
        cmocka_unit_test(test_build_grid_container),
        cmocka_unit_test(test_container_defaults),
        cmocka_unit_test(test_build_search_form_get),
        cmocka_unit_test(test_build_form_post_and_hidden),
        cmocka_unit_test(test_build_textarea_value),
        cmocka_unit_test(test_build_control_without_form),
        cmocka_unit_test(test_build_two_forms_distinct_groups),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
