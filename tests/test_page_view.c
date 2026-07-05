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
#include "css.h"
#include "dom.h"
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

/* A lone high byte that is invalid UTF-8 is reinterpreted as Windows-1252 (a
 * superset of Latin-1) and re-emitted as UTF-8, recovering accents from a legacy
 * page rather than dropping them to '?'. 0xE1 -> U+00E1 (a-acute) -> 0xC3 0xA1. */
static void test_append_transcodes_latin1(void **state) {
    (void)state;
    pv_view *v = pv_new();
    const char latin1[] = { 'I', 'm', (char)0xE1, 'g', '\0' }; /* lone 0xE1 = a-acute */
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, latin1, NULL), PV_OK);
    assert_string_equal(pv_at(v, 0)->text, "Im\xC3\xA1g"); /* "Imág" */
    pv_free(v);
}

/* 0xE9 -> U+00E9 (e-acute); a full word of Latin-1 accents round-trips to UTF-8. */
static void test_append_transcodes_word(void **state) {
    (void)state;
    pv_view *v = pv_new();
    const char latin1[] = { 'c', 'a', 'f', (char)0xE9, '\0' }; /* "café" in Latin-1 */
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, latin1, NULL), PV_OK);
    assert_string_equal(pv_at(v, 0)->text, "caf\xC3\xA9");
    pv_free(v);
}

/* Windows-1252 0x80-0x9F carry printable glyphs (unlike Latin-1 C1 controls):
 * 0x93/0x94 are curly double quotes -> U+201C/U+201D (3-byte UTF-8 each). */
static void test_append_transcodes_cp1252_quotes(void **state) {
    (void)state;
    pv_view *v = pv_new();
    const char cp1252[] = { (char)0x93, 'h', 'i', (char)0x94, '\0' };
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, cp1252, NULL), PV_OK);
    assert_string_equal(pv_at(v, 0)->text, "\xE2\x80\x9C" "hi" "\xE2\x80\x9D");
    pv_free(v);
}

/* Undefined Windows-1252 positions (0x81 here) have no glyph and still fail to '?'. */
static void test_append_undefined_cp1252_is_qmark(void **state) {
    (void)state;
    pv_view *v = pv_new();
    const char bad[] = { 'a', (char)0x81, 'b', '\0' };
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, bad, NULL), PV_OK);
    assert_string_equal(pv_at(v, 0)->text, "a?b");
    pv_free(v);
}

/* Valid multi-byte UTF-8 input passes through untouched (no double-encoding). */
static void test_append_valid_utf8_passthrough(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, "caf\xC3\xA9", NULL), PV_OK);
    assert_string_equal(pv_at(v, 0)->text, "caf\xC3\xA9");
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

/* Inline emphasis: <b>/<strong> set bold, <i>/<em> set italic, on the wrapped run
 * only; surrounding text stays plain. Nested b>i is both. */
static void test_build_inline_emphasis(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p>plain<b>bb</b><strong>ss</strong><i>ii</i>"
                             "<em>ee</em><b><i>both</i></b></p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *plain = find_text(v, "plain");
    assert_non_null(plain);
    assert_int_equal(plain->bold, 0);
    assert_int_equal(plain->italic, 0);

    const pv_run *bb = find_text(v, "bb");
    assert_non_null(bb);
    assert_int_equal(bb->bold, 1);
    assert_int_equal(bb->italic, 0);

    const pv_run *ss = find_text(v, "ss");
    assert_non_null(ss);
    assert_int_equal(ss->bold, 1);

    const pv_run *ii = find_text(v, "ii");
    assert_non_null(ii);
    assert_int_equal(ii->bold, 0);
    assert_int_equal(ii->italic, 1);

    const pv_run *ee = find_text(v, "ee");
    assert_non_null(ee);
    assert_int_equal(ee->italic, 1);

    const pv_run *both = find_text(v, "both");
    assert_non_null(both);
    assert_int_equal(both->bold, 1);
    assert_int_equal(both->italic, 1);

    pv_free(v);
    hp_document_free(doc);
}

/* Unordered list: each <li>'s first run is prefixed with a bullet marker and
 * carries list depth 1. */
static void test_build_unordered_list(void **state) {
    (void)state;
    hp_document *doc = parse("<body><ul><li>apple</li><li>pear</li></ul></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *a = find_text(v, "\xE2\x80\xA2 apple"); /* "* apple" */
    assert_non_null(a);
    assert_int_equal(a->indent, 1);
    const pv_run *p = find_text(v, "\xE2\x80\xA2 pear");
    assert_non_null(p);
    assert_int_equal(p->indent, 1);

    pv_free(v);
    hp_document_free(doc);
}

/* Ordered list: markers are 1-based ordinals; nested lists deepen the indent. */
static void test_build_ordered_and_nested_list(void **state) {
    (void)state;
    hp_document *doc = parse("<body><ol><li>one</li><li>two<ul><li>sub</li></ul></li></ol></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *one = find_text(v, "1. one");
    assert_non_null(one);
    assert_int_equal(one->indent, 1);
    const pv_run *two = find_text(v, "2. two");
    assert_non_null(two);
    assert_int_equal(two->indent, 1);
    /* The nested <ul> item is a bullet at depth 2. */
    const pv_run *sub = find_text(v, "\xE2\x80\xA2 sub");
    assert_non_null(sub);
    assert_int_equal(sub->indent, 2);

    pv_free(v);
    hp_document_free(doc);
}

/* A table becomes a grid: each cell is one collected text run sharing the table's
 * cont_id, with the column count = widest row. <th> cells are bold. */
static void test_build_table_grid(void **state) {
    (void)state;
    hp_document *doc = parse("<body><table>"
                             "<tr><th>Name</th><th>Age</th></tr>"
                             "<tr><td>Ana</td><td>30</td></tr>"
                             "</table></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *name = find_text(v, "Name");
    assert_non_null(name);
    assert_int_equal(name->cont_display, BX_DISPLAY_GRID);
    assert_int_equal(name->cont_cols, 2);
    assert_int_equal(name->bold, 1); /* th */

    const pv_run *ana = find_text(v, "Ana");
    assert_non_null(ana);
    assert_int_equal(ana->bold, 0); /* td */
    /* All four cells share the one table container id. */
    assert_int_equal(ana->cont_id, name->cont_id);
    assert_true(name->cont_id >= 0);

    const pv_run *age = find_text(v, "Age");
    assert_non_null(age);
    const pv_run *thirty = find_text(v, "30");
    assert_non_null(thirty);
    assert_int_equal(thirty->cont_id, name->cont_id);

    pv_free(v);
    hp_document_free(doc);
}

/* Cell inner markup is flattened into the cell's text and not re-emitted as a
 * separate run; the column count comes from the widest row. */
static void test_build_table_flattens_cell(void **state) {
    (void)state;
    hp_document *doc = parse("<body><table><tr><td>a <b>bold</b> c</td>"
                             "<td>x</td><td>y</td></tr></table></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *cell = find_text(v, "a bold c");
    assert_non_null(cell);
    assert_int_equal(cell->cont_cols, 3);
    /* "bold" is part of the cell text, not its own run. */
    assert_null(find_text(v, "bold"));

    pv_free(v);
    hp_document_free(doc);
}

/* A cell that wraps a nested <table> is a structural CONTAINER, not a collected leaf
 * cell: the inner table's cells are each emitted as their own grid run (against the
 * INNER table), instead of the outer cell flattening the whole subtree into one giant
 * run. This is the Hacker News case (the story list is a <table> nested inside a <td>
 * of the outer page table). */
/* A collected subtree (button label / flattened table cell) must NOT paint the
 * source of a nested <style> or <script> as content. With run_js the parser keeps
 * <script> nodes in the tree (strip_scripts=0), so google.com's markup -- style
 * elements inside buttons, scripts inside table cells -- leaked raw CSS/JS text
 * into labels and cells before this guard. */
static void test_build_collected_text_skips_style_and_script(void **state) {
    (void)state;
    static const char H[] =
        "<body>"
        "<button><style>.x{color:red}</style>Press<span> me</span></button>"
        "<table><tr><td><script>var leak=1;</script>Cell text</td></tr></table>"
        "</body>";
    hp_config c = hp_config_default();
    c.strip_scripts = 0; /* live-JS parse mode: scripts stay in the tree */
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(H, sizeof H - 1, &c, &doc), HP_OK);
    pv_view *v = NULL;
    assert_int_equal(pv_build_ex(doc, 1, &v), PV_OK);

    const pv_run *btn = NULL;
    for (size_t i = 0; i < pv_count(v); ++i)
        if (pv_at(v, i)->kind == PV_INPUT) btn = pv_at(v, i);
    assert_non_null(btn);
    assert_string_equal(btn->text, "Press me");     /* no .x{color:red} in the label */
    assert_non_null(find_text(v, "Cell text"));     /* no var leak=1; in the cell */
    assert_null(find_text(v, "var leak=1; Cell text"));

    pv_free(v);
    hp_document_free(doc);
}

/* A table with a multi-link leaf cell is navigation/layout, not data: its cells
 * are WALKED (links survive as PV_LINK runs, one block per <tr>), not flattened
 * into grid runs. This is the Hacker News case: every story title and subtext
 * link lives inside a <td>, and collection was destroying all of them. */
static void test_build_multilink_table_flows_links(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><table>"
        "<tr><td>1.</td>"
        "<td><a href='https://s.example/story'>Story title</a>"
        " (<a href='https://s.example/from'>site</a>)</td></tr>"
        "<tr><td>2.</td><td><a href='https://s.example/two'>Second</a></td></tr>"
        "</table></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    /* The links survive, as links, with their hrefs. */
    const pv_run *story = find_text(v, "Story title");
    const pv_run *site  = find_text(v, "site");
    assert_non_null(story);
    assert_non_null(site);
    assert_int_equal(story->kind, PV_LINK);
    assert_string_equal(story->href, "https://s.example/story");
    assert_int_equal(site->kind, PV_LINK);
    assert_string_equal(site->href, "https://s.example/from");

    /* Not a grid: the cells were walked, not collected as grid items. */
    assert_int_equal(story->cont_id, -1);

    /* Rank and title share the row's line: rank breaks the block, title does not. */
    const pv_run *rank = find_text(v, "1.");
    assert_non_null(rank);
    assert_int_not_equal(rank->block_break, 0);
    assert_int_equal(story->block_break, 0);
    /* The second row starts its own block. */
    const pv_run *rank2 = find_text(v, "2.");
    assert_non_null(rank2);
    assert_int_not_equal(rank2->block_break, 0);

    /* The cell boundary got a separator run, so "1." and the title do not fuse. */
    size_t rank_i = 0, story_i = 0;
    for (size_t i = 0; i < pv_count(v); ++i) {
        if (pv_at(v, i) == rank) rank_i = i;
        if (pv_at(v, i) == story) story_i = i;
    }
    assert_true(rank_i + 1 < story_i); /* something (the gap run) sits between them */

    pv_free(v);
    hp_document_free(doc);
}

/* A DATA table (no multi-link cell) keeps the grid, and a cell whose subtree has
 * exactly one <a href> is collected as a LINK run: clickable without breaking
 * column alignment (one run per cell is what the grid engine counts). */
static void test_build_single_link_cell_collected_as_link(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><table>"
        "<tr><td><a href='https://a.example/'>Alpha</a></td><td>plain</td></tr>"
        "<tr><td><a href='https://b.example/'>Beta</a></td><td>text</td></tr>"
        "</table></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *alpha = find_text(v, "Alpha");
    const pv_run *plain = find_text(v, "plain");
    assert_non_null(alpha);
    assert_non_null(plain);
    assert_int_equal(alpha->kind, PV_LINK);
    assert_string_equal(alpha->href, "https://a.example/");
    assert_int_equal(plain->kind, PV_TEXT);
    /* Still grid items of the same table (alignment preserved). */
    assert_true(alpha->cont_id >= 0);
    assert_int_equal(alpha->cont_id, plain->cont_id);
    assert_int_equal(alpha->cont_display, BX_DISPLAY_GRID);

    pv_free(v);
    hp_document_free(doc);
}

/* Legacy bgcolor attribute is the background fallback when no CSS background won
 * (like <font color> for the foreground). Hacker News' orange bar and beige page
 * are bgcolor attributes, not CSS. */
static void test_build_bgcolor_attr_fallback(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><table bgcolor='#ff6600'>"
        "<tr><td><a href='https://x.example/a'>one</a>"
        "<a href='https://x.example/b'>two</a></td></tr>"
        "</table></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *one = find_text(v, "one");
    assert_non_null(one);
    assert_int_equal(one->bg_rgb, 0xff6600);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_nested_table_not_flattened(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><table><tr><td>"
        "<table>"
        "<tr><td>1.</td><td>up</td><td>First Story</td></tr>"
        "<tr><td>2.</td><td>up</td><td>Second Story</td></tr>"
        "</table>"
        "</td></tr></table></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    /* Each inner cell is its own run... */
    const pv_run *first = find_text(v, "First Story");
    const pv_run *second = find_text(v, "Second Story");
    assert_non_null(first);
    assert_non_null(second);
    const pv_run *rank1 = find_text(v, "1.");
    assert_non_null(rank1);
    /* ...annotated as a 3-column grid item (the INNER table's column count)... */
    assert_int_equal(first->cont_display, BX_DISPLAY_GRID);
    assert_int_equal(first->cont_cols, 3);
    /* ...all sharing the one inner-table container id. */
    assert_int_equal(first->cont_id, second->cont_id);
    assert_int_equal(rank1->cont_id, first->cont_id);
    assert_true(first->cont_id >= 0);

    /* The two stories were NOT flattened into one run. */
    assert_null(find_text(v, "1. up First Story 2. up Second Story"));

    /* Each table ROW is its own block: the first cell of a row breaks to a new line,
     * the rest of the row share it (so an overflowing table degrades to one row per
     * line, not one blob). */
    assert_int_equal(rank1->block_break, 1);          /* first cell of row 1 breaks */
    const pv_run *up1 = NULL;                          /* 2nd cell of row 1: no break */
    for (size_t i = 0; i < pv_count(v); ++i) {
        const pv_run *r = pv_at(v, i);
        if (r->text != NULL && strcmp(r->text, "up") == 0) { up1 = r; break; }
    }
    assert_non_null(up1);
    assert_int_equal(up1->block_break, 0);
    const pv_run *rank2 = find_text(v, "2.");          /* first cell of row 2 breaks */
    assert_non_null(rank2);
    assert_int_equal(rank2->block_break, 1);

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
    /* An <img> inside an always-skipped container (a control) emits no run. */
    hp_document *doc = parse("<body><button><img src=\"https://e.example/x.png\"></button>"
                            "<p>visible</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    assert_null(find_image(v, "https://e.example/x.png"));
    assert_non_null(find_text(v, "visible"));
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_noscript_shown_when_js_off(void **state) {
    (void)state;
    /* JS off (the default): a no-JS browser renders the <noscript> fallback. */
    hp_document *doc = parse("<body><noscript><p>enable-js-fallback</p></noscript>"
                            "<p>visible</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    assert_non_null(find_text(v, "enable-js-fallback"));
    assert_non_null(find_text(v, "visible"));
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_noscript_hidden_when_js_on(void **state) {
    (void)state;
    /* JS on: the <noscript> fallback is suppressed (the script would run instead). */
    hp_document *doc = parse("<body><noscript><p>enable-js-fallback</p></noscript>"
                            "<p>visible</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build_ex(doc, 1, &v), PV_OK);
    assert_null(find_text(v, "enable-js-fallback"));
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

/* Descendant (`div p`) and child (`nav > a`) combinators from a <style> sheet
 * resolve through the real DOM ancestor chain. */
static void test_build_combinator_selectors(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<head><style>"
        "div p { color:#990000 }"     /* descendant: any p under a div */
        "nav > a { color:#003399 }"   /* child: a whose parent is nav */
        "</style></head><body>"
        "<div><section><p>inside div</p></section></div>" /* p under div (via section) */
        "<p>outside</p>"                                  /* no div ancestor */
        "<nav><a>direct link</a></nav>"                   /* a is a child of nav */
        "<nav><p><a>nested link</a></p></nav>"            /* a is a grandchild of nav */
        "</body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *inside = find_text(v, "inside div");
    assert_non_null(inside);
    assert_int_equal(inside->fg_rgb, 0x990000);  /* descendant matched */

    const pv_run *outside = find_text(v, "outside");
    assert_non_null(outside);
    assert_int_equal(outside->fg_rgb, -1);        /* no div ancestor: no match */

    const pv_run *direct = find_text(v, "direct link");
    assert_non_null(direct);
    assert_int_equal(direct->fg_rgb, 0x003399);  /* child combinator matched */

    const pv_run *nested = find_text(v, "nested link");
    assert_non_null(nested);
    assert_int_equal(nested->fg_rgb, -1);         /* grandchild: child combinator fails */

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

/* Stage 3: each run carries the flex ITEM's own resolved values (the direct child
 * of the container on the run's ancestor chain: grow/shrink/basis x100/px, order)
 * plus the CONTAINER's flex-direction. flex:1 -> 1 1 0. An item without flex
 * properties, an anonymous item (text directly in the container) and content
 * outside any container keep the unset sentinels. */
static void test_build_flex_item_values(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body>"
        "<div style='display:flex'>"
        "<div style='flex:1'>main</div>"
        "<div style='flex:0 0 200px;order:-1'>side</div>"
        "<div>plain</div>"
        "</div>"
        "<div style='display:flex;flex-direction:column'><p>stacked</p></div>"
        "<div style='display:flex'>anon</div>"
        "<p>outside</p>"
        "</body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *m = find_text(v, "main");
    assert_non_null(m);
    assert_int_equal(m->cont_display, BX_DISPLAY_FLEX);
    assert_int_equal(m->flex_grow, 100);
    assert_int_equal(m->flex_shrink, 100);
    assert_int_equal(m->flex_basis, 0);
    assert_int_equal(m->flex_order, CSS_LEN_UNSET);
    assert_int_equal(m->flex_direction, CSS_FD_UNSET);

    const pv_run *s = find_text(v, "side");
    assert_non_null(s);
    assert_int_equal(s->flex_grow, 0);
    assert_int_equal(s->flex_shrink, 0);
    assert_int_equal(s->flex_basis, 200);
    assert_int_equal(s->flex_order, -1);

    const pv_run *pl = find_text(v, "plain");
    assert_non_null(pl);
    assert_int_equal(pl->flex_grow, -1);
    assert_int_equal(pl->flex_shrink, -1);
    assert_int_equal(pl->flex_basis, CSS_LEN_UNSET);
    assert_int_equal(pl->flex_order, CSS_LEN_UNSET);

    const pv_run *st = find_text(v, "stacked");
    assert_non_null(st);
    assert_int_equal(st->flex_direction, CSS_FD_COLUMN);
    assert_int_equal(st->flex_grow, -1);

    const pv_run *an = find_text(v, "anon");
    assert_non_null(an);
    assert_true(an->cont_id >= 0);
    assert_int_equal(an->flex_grow, -1);
    assert_int_equal(an->flex_basis, CSS_LEN_UNSET);

    const pv_run *o = find_text(v, "outside");
    assert_non_null(o);
    assert_int_equal(o->cont_id, -1);
    assert_int_equal(o->flex_grow, -1);
    assert_int_equal(o->flex_direction, CSS_FD_UNSET);

    pv_free(v);
    hp_document_free(doc);
}

/* CSS: whitespace directly inside a flex/grid container creates NO anonymous item
 * (the source newlines between <p> items must not become layout columns). The
 * flowed-table inter-cell separator is unaffected (it carries cont_id == -1). */
static void test_build_flex_whitespace_not_item(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><div style='display:flex'>\n  <p>wa</p>\n  <p>wb</p>\n</div></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    assert_non_null(find_text(v, "wa"));
    assert_non_null(find_text(v, "wb"));
    for (size_t i = 0; i < pv_count(v); ++i) {
        const pv_run *r = pv_at(v, i);
        if (r->cont_id < 0 || r->text == NULL) continue;
        int blank = 1;
        for (const char *c = r->text; *c != '\0'; ++c)
            if (*c != ' ') { blank = 0; break; }
        assert_false(blank);   /* no whitespace-only run inside the container */
    }

    pv_free(v);
    hp_document_free(doc);
}

/* CSS anonymous-box rule: whitespace-only text between BLOCK siblings generates no
 * box at all. Each source newline between <div>s/<p>s used to paint an empty ~26px
 * line (the Wikipedia blank-page bug: 412 such runs = ~11000px of nothing). The
 * pending break moves to the block's first real content instead. */
static void test_build_interblock_whitespace_not_emitted(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><div>\n  <p>alpha</p>\n  <p>beta</p>\n</div>\n<p>gamma</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *a = find_text(v, "alpha");
    const pv_run *b = find_text(v, "beta");
    const pv_run *g = find_text(v, "gamma");
    assert_non_null(a);
    assert_non_null(b);
    assert_non_null(g);
    /* The dropped whitespace left its break pending: each block still opens fresh. */
    assert_true(b->block_break);
    assert_true(g->block_break);
    for (size_t i = 0; i < pv_count(v); ++i) {
        const pv_run *r = pv_at(v, i);
        if (r->text == NULL) continue;
        int blank = 1;
        for (const char *c = r->text; *c != '\0'; ++c)
            if (*c != ' ') { blank = 0; break; }
        assert_false(blank);   /* no whitespace-only run survives in this document */
    }
    pv_free(v);
    hp_document_free(doc);
}

/* The separator space BETWEEN two inline elements is content, not an anonymous box:
 * it flows mid-block (no break) and must keep being emitted. */
static void test_build_inline_whitespace_kept(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p><b>one</b> <i>two</i></p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    int saw_sep = 0;
    for (size_t i = 0; i < pv_count(v); ++i) {
        const pv_run *r = pv_at(v, i);
        if (r->text != NULL && strcmp(r->text, " ") == 0) {
            assert_false(r->block_break);
            saw_sep = 1;
        }
    }
    assert_true(saw_sep);
    pv_free(v);
    hp_document_free(doc);
}

/* Container-item identity: inline fragments of the SAME direct child share one
 * cont_item ordinal (they are one flex/grid item and must flow together in one
 * cell); the next child gets a different ordinal; runs outside carry -1. */
static void test_build_cont_item_identity(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><div style='display:grid;grid-template-columns:1fr'>"
        "<p>lead <a href='https://e.example/f'>free</a> tail</p>"
        "<p>second</p>"
        "</div><p>plain</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *l = find_text(v, "lead ");
    const pv_run *f = find_text(v, "free");
    const pv_run *t = find_text(v, " tail");
    const pv_run *s = find_text(v, "second");
    const pv_run *p = find_text(v, "plain");
    assert_non_null(l);
    assert_non_null(f);
    assert_non_null(t);
    assert_non_null(s);
    assert_non_null(p);

    assert_true(l->cont_id >= 0);
    assert_int_equal(l->cont_id, f->cont_id);
    assert_int_equal(l->cont_id, t->cont_id);
    assert_int_equal(l->cont_id, s->cont_id);
    assert_true(l->cont_item >= 0);
    assert_int_equal(l->cont_item, f->cont_item);   /* same <p> = same item */
    assert_int_equal(l->cont_item, t->cont_item);
    assert_true(s->cont_item >= 0);
    assert_int_not_equal(s->cont_item, l->cont_item); /* next child = next item */
    assert_int_equal(p->cont_item, -1);              /* outside any container */

    pv_free(v);
    hp_document_free(doc);
}

/* Data-table regression lock: each collected cell keeps its OWN item ordinal, so
 * the grid still lays one cell per column (grouping by item must not merge cells). */
static void test_build_table_cells_distinct_items(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><table><tr><td>ca</td><td>cb</td></tr>"
        "<tr><td>cc</td><td>cd</td></tr></table></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *ca = find_text(v, "ca");
    const pv_run *cb = find_text(v, "cb");
    const pv_run *cc = find_text(v, "cc");
    const pv_run *cd = find_text(v, "cd");
    assert_non_null(ca);
    assert_non_null(cb);
    assert_non_null(cc);
    assert_non_null(cd);
    assert_true(ca->cont_id >= 0);
    assert_int_equal(ca->cont_id, cb->cont_id);
    assert_int_equal(ca->cont_id, cd->cont_id);
    assert_true(ca->cont_item >= 0);
    assert_int_not_equal(ca->cont_item, cb->cont_item);
    assert_int_not_equal(cb->cont_item, cc->cont_item);
    assert_int_not_equal(cc->cont_item, cd->cont_item);

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

/* Hito 23b-2: the flex/grid container params now come from the cascade, so a
 * <style> rule (not only inline style=) feeds gap/justify/columns. */
static void test_build_flex_container_from_sheet(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><style>.row{display:flex;gap:16px;justify-content:space-between}</style>"
        "<div class='row'><p>one</p><p>two</p></div></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *one = find_text(v, "one");
    const pv_run *two = find_text(v, "two");
    assert_non_null(one);
    assert_non_null(two);
    assert_int_equal(one->cont_display, BX_DISPLAY_FLEX);
    assert_int_equal(one->cont_gap, 16);
    assert_int_equal(one->cont_justify, FX_JUSTIFY_SPACE_BETWEEN);
    assert_int_equal(one->cont_id, two->cont_id);
    assert_true(one->cont_id >= 0);

    pv_free(v);
    hp_document_free(doc);
}

static void test_build_grid_columns_from_sheet(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><style>#g{display:grid;grid-template-columns:1fr 1fr 1fr 1fr}</style>"
        "<div id='g'><span>a</span><span>b</span></div></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *a = find_text(v, "a");
    assert_non_null(a);
    assert_int_equal(a->cont_display, BX_DISPLAY_GRID);
    assert_int_equal(a->cont_cols, 4);
    assert_true(a->cont_id >= 0);

    pv_free(v);
    hp_document_free(doc);
}

/* The sheet sets the container; an inline style= on the same element overrides one
 * param (cascade: inline wins) while the sheet still supplies the rest. */
static void test_build_container_sheet_inline_cascade(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><style>.row{display:flex;gap:5px;justify-content:center}</style>"
        "<div class='row' style='gap:25px'><p>x</p></div></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *x = find_text(v, "x");
    assert_non_null(x);
    assert_int_equal(x->cont_display, BX_DISPLAY_FLEX);  /* sheet */
    assert_int_equal(x->cont_gap, 25);                   /* inline wins */
    assert_int_equal(x->cont_justify, FX_JUSTIFY_CENTER);/* sheet */

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

/* --- author box model (Hito 23b-3) --- */

/* A wrapper with max-width + margin:0 auto + horizontal padding centers a readable
 * column: its descendant runs all carry the same horizontal box, even from a
 * <style> rule (not just inline style=). */
static void test_build_box_wrapper_centering_from_sheet(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><style>.page{max-width:600px;margin:0 auto;"
        "padding-left:20px;padding-right:20px}</style>"
        "<div class='page'><p>alpha</p><p>beta</p></div></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *alpha = find_text(v, "alpha");
    const pv_run *beta = find_text(v, "beta");
    assert_non_null(alpha);
    assert_non_null(beta);
    assert_int_equal(alpha->box_w, 600);
    assert_int_equal(alpha->box_center, 1);
    assert_int_equal(alpha->box_l, 20);
    assert_int_equal(alpha->box_r, 20);
    /* the wrapper is not the leaf block of these paragraphs, so its vertical
     * margins do not override the leaf's UA margin. */
    assert_int_equal(alpha->box_mt, PV_LEN_UNSET);
    assert_int_equal(beta->box_w, 600);
    assert_int_equal(beta->box_center, 1);

    pv_free(v);
    hp_document_free(doc);
}

/* A leaf block's own box: vertical margins override the UA, horizontal padding +
 * a fixed width inset and cap the content. No centering without margin:auto. */
static void test_build_box_leaf_inline(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><p style='margin-top:50px;margin-bottom:5px;"
        "padding-left:30px;width:400px'>solo</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *solo = find_text(v, "solo");
    assert_non_null(solo);
    assert_int_equal(solo->box_mt, 50);
    assert_int_equal(solo->box_mb, 5);
    assert_int_equal(solo->box_l, 30);
    assert_int_equal(solo->box_r, 0);
    assert_int_equal(solo->box_w, 400);
    assert_int_equal(solo->box_center, 0);

    pv_free(v);
    hp_document_free(doc);
}

/* A run with no author box carries the neutral defaults; pv_set_box fixes the
 * last run and is NULL-safe. */
static void test_box_defaults_and_setter(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p>plain</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *p = find_text(v, "plain");
    assert_non_null(p);
    assert_int_equal(p->box_l, 0);
    assert_int_equal(p->box_r, 0);
    assert_int_equal(p->box_w, 0);
    assert_int_equal(p->box_center, 0);
    assert_int_equal(p->box_mt, PV_LEN_UNSET);
    assert_int_equal(p->box_mb, PV_LEN_UNSET);
    pv_free(v);
    hp_document_free(doc);

    pv_view *w = pv_new();
    assert_int_equal(pv_append(w, PV_TEXT, 0, 0, "x", NULL), PV_OK);
    pv_set_box(w, 12, 8, 500, 1, 40, 4);
    assert_int_equal(pv_at(w, 0)->box_l, 12);
    assert_int_equal(pv_at(w, 0)->box_r, 8);
    assert_int_equal(pv_at(w, 0)->box_w, 500);
    assert_int_equal(pv_at(w, 0)->box_center, 1);
    assert_int_equal(pv_at(w, 0)->box_mt, 40);
    assert_int_equal(pv_at(w, 0)->box_mb, 4);
    pv_set_box(NULL, 0, 0, 0, 0, 0, 0); /* NULL-safe */
    pv_free(w);
}

/* --- box engine (Hito 23b-8 Step A): identity + box decoration on a run --- */

static void test_build_boxdeco_border_padding(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><div style='border:2px solid #ff0000;padding:10px;"
        "box-sizing:border-box'>solo</div></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *solo = find_text(v, "solo");
    assert_non_null(solo);
    assert_true(solo->block_id >= 0);
    const pv_box_def *bx = pv_box_at(v, (size_t)solo->block_id);
    assert_non_null(bx);
    assert_int_equal(bx->bord_tw, 2);
    assert_int_equal(bx->bord_rw, 2);
    assert_int_equal(bx->bord_bw, 2);
    assert_int_equal(bx->bord_lw, 2);
    assert_int_equal(bx->bord_ts, CSS_BST_SOLID);
    assert_int_equal(bx->bord_tc, 0xff0000);
    assert_int_equal(bx->pad_t, 10);
    assert_int_equal(bx->pad_r, 10);
    assert_int_equal(bx->pad_b, 10);
    assert_int_equal(bx->pad_l, 10);
    assert_int_equal(bx->box_sizing, CSS_BOXS_BORDER);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_boxdeco_shadow_outline(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><div style='box-shadow:2px 4px 6px #00ff00;"
        "outline:1px dashed #0000ff'>fx</div></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *fx = find_text(v, "fx");
    assert_non_null(fx);
    assert_true(fx->block_id >= 0);
    const pv_box_def *bx = pv_box_at(v, (size_t)fx->block_id);
    assert_non_null(bx);
    assert_int_equal(bx->bsh_dx, 2);
    assert_int_equal(bx->bsh_dy, 4);
    assert_int_equal(bx->bsh_blur, 6);
    assert_int_equal(bx->bsh_color, 0x00ff00);
    assert_int_equal(bx->outline_w, 1);
    assert_int_equal(bx->outline_style, CSS_BST_DASHED);
    assert_int_equal(bx->outline_color, 0x0000ff);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_boxdeco_defaults_no_box(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p>plain</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *p = find_text(v, "plain");
    assert_non_null(p);
    assert_int_equal(p->block_id, -1);
    /* No box-carrying block -> the box tree is empty (default render byte-identical). */
    assert_int_equal((int)pv_box_count(v), 0);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_boxdeco_sibling_blocks_distinct_ids(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><div style='border:1px solid #111'>aaa</div>"
        "<div style='border:1px solid #222'>bbb</div></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *a = find_text(v, "aaa");
    const pv_run *b = find_text(v, "bbb");
    assert_non_null(a);
    assert_non_null(b);
    assert_true(a->block_id >= 0);
    assert_true(b->block_id >= 0);
    assert_int_not_equal(a->block_id, b->block_id);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_boxdeco_shared_id_within_block(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><div style='border:3px solid #abc;padding:5px'>"
        "<span>one</span> <span>two</span></div></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *one = find_text(v, "one");
    const pv_run *two = find_text(v, "two");
    assert_non_null(one);
    assert_non_null(two);
    assert_true(one->block_id >= 0);
    assert_int_equal(one->block_id, two->block_id);
    const pv_box_def *bx = pv_box_at(v, (size_t)one->block_id);
    assert_non_null(bx);
    assert_int_equal(bx->bord_tw, 3);
    pv_free(v);
    hp_document_free(doc);
}

/* --- box engine (Hito 23b-8 Step D): the box tree (parent_id + box-def list) --- */

/* A child box nests inside its parent box (a run interrupting the parent must not
 * split it): both share the box tree, the child's parent_id points at the outer box,
 * and the outer box is a root (parent_id -1). Decoration lives on the box defs. */
static void test_build_box_tree_nested(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><div style='border:2px solid #1133ff;padding:8px'>"
        "<p>before</p>"
        "<div style='border:1px solid #ff1111'><p>inner</p></div>"
        "<p>after</p>"
        "</div></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *before = find_text(v, "before");
    const pv_run *inner = find_text(v, "inner");
    const pv_run *after = find_text(v, "after");
    assert_non_null(before);
    assert_non_null(inner);
    assert_non_null(after);
    /* before/after belong to the SAME (outer) box; inner is a different box. */
    assert_true(before->block_id >= 0);
    assert_int_equal(before->block_id, after->block_id);
    assert_int_not_equal(before->block_id, inner->block_id);
    /* the box tree carries both, with the parent link. */
    assert_true(pv_box_count(v) >= 2);
    const pv_box_def *outer = pv_box_at(v, (size_t)before->block_id);
    const pv_box_def *inb = pv_box_at(v, (size_t)inner->block_id);
    assert_non_null(outer);
    assert_non_null(inb);
    assert_int_equal(outer->parent_id, -1);
    assert_int_equal(inb->parent_id, before->block_id);
    assert_int_equal(outer->bord_tw, 2);
    assert_int_equal(inb->bord_tw, 1);
    pv_free(v);
    hp_document_free(doc);
}

/* A text-less wrapper (a card whose only child is a body div with the text) owns no
 * run, yet its box def must still exist and be the body box's parent — Step A's
 * per-run decoration could not represent this. */
static void test_build_box_tree_textless_wrapper(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><div style='border:3px solid #00aa00'>"        /* card: no direct text */
        "<div style='padding:9px'><p>body</p></div>"          /* body: has the text */
        "</div></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *body = find_text(v, "body");
    assert_non_null(body);
    assert_true(body->block_id >= 0);
    const pv_box_def *bd = pv_box_at(v, (size_t)body->block_id);
    assert_non_null(bd);
    assert_int_equal(bd->pad_t, 9);
    int card_id = bd->parent_id;
    assert_true(card_id >= 0);
    const pv_box_def *card = pv_box_at(v, (size_t)card_id);
    assert_non_null(card);
    assert_int_equal(card->bord_tw, 3);
    assert_int_equal(card->parent_id, -1);
    pv_free(v);
    hp_document_free(doc);
}

/* A page with no author box has an empty box tree (default render byte-identical). */
static void test_build_box_tree_empty_no_box(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p>plain</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    assert_int_equal((int)pv_box_count(v), 0);
    assert_null(pv_box_at(v, 0));
    pv_free(v);
    hp_document_free(doc);
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

/* --- author CSS from <style> blocks + the new text_align/font_scale fields --- */

/* Attribute selectors and !important resolve through the real html_parse->page_view
 * pipeline (Hito 23b-4). The chain carries each element's attributes, so an attribute
 * selector matches, and an important sheet rule beats a more-specific non-important one. */
static void test_build_attr_selectors_and_important(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<head><style>"
        "a[href^=\"https://\"] { color:#003399 }"   /* prefix attribute selector */
        "input[type=text] { color:#990000 }"         /* exact attribute selector */
        "#x { color:#0a0a0a }"                        /* id (specificity 100) */
        "p { color:#00ff00 !important }"              /* important beats the id rule */
        "</style></head><body>"
        "<a href=\"https://example.test/\">secure</a>"
        "<a href=\"http://example.test/\">plain</a>"
        "<input type=\"text\" value=\"field\">"
        "<p id=\"x\">important wins</p>"
        "</body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *secure = find_text(v, "secure");
    assert_non_null(secure);
    assert_int_equal(secure->fg_rgb, 0x003399);  /* https prefix matched */
    const pv_run *plain = find_text(v, "plain");
    assert_non_null(plain);
    assert_int_equal(plain->fg_rgb, -1);          /* http: no match (fail closed) */

    const pv_run *imp = find_text(v, "important wins");
    assert_non_null(imp);
    assert_int_equal(imp->fg_rgb, 0x00ff00);      /* important type beats non-important id */

    pv_free(v);
    hp_document_free(doc);
}

/* Pseudo-classes + sibling combinators (Hito 23b-9) resolve through the real
 * pipeline: page_view must feed the css engine each element's sibling context
 * (nth/nsib/prev). Covers the Hacker News idiom a:link{text-decoration:none},
 * zebra rows via :nth-child, and the adjacent-sibling combinator. */
static void test_build_pseudo_classes_and_siblings(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<head><style>"
        "a:link { text-decoration:none; color:#123123 }"
        "li:nth-child(even) { color:#0e0e0e }"
        "li:first-child { color:#f10000 }"
        "h2 + p { color:#00ad00 }"
        "a:visited, a:hover { color:#bad000 }"
        "</style></head><body>"
        "<a href=\"https://example.test/\">homelink</a>"
        "<ul><li>uno</li><li>dos</li><li>tres</li><li>cuatro</li></ul>"
        "<h2>head</h2><p>right after</p><p>further down</p>"
        "</body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    /* a:link matches the anchor (ZK: every link unvisited); :visited/:hover never
     * match, so their #bad000 never applies. */
    const pv_run *link = find_text(v, "homelink");
    assert_non_null(link);
    assert_int_equal(link->fg_rgb, 0x123123);
    assert_int_equal(link->text_decoration, 0);   /* explicit none drops underline */

    /* Zebra: li #1 first-child, #2 and #4 even, #3 unstyled. */
    const pv_run *uno = find_text(v, "\xE2\x80\xA2 uno");
    assert_non_null(uno);
    assert_int_equal(uno->fg_rgb, 0xf10000);
    const pv_run *dos = find_text(v, "\xE2\x80\xA2 dos");
    assert_non_null(dos);
    assert_int_equal(dos->fg_rgb, 0x0e0e0e);
    const pv_run *tres = find_text(v, "\xE2\x80\xA2 tres");
    assert_non_null(tres);
    assert_int_equal(tres->fg_rgb, -1);
    const pv_run *cuatro = find_text(v, "\xE2\x80\xA2 cuatro");
    assert_non_null(cuatro);
    assert_int_equal(cuatro->fg_rgb, 0x0e0e0e);

    /* h2 + p styles only the immediately following paragraph. */
    const pv_run *after = find_text(v, "right after");
    assert_non_null(after);
    assert_int_equal(after->fg_rgb, 0x00ad00);
    const pv_run *further = find_text(v, "further down");
    assert_non_null(further);
    assert_int_equal(further->fg_rgb, -1);

    pv_free(v);
    hp_document_free(doc);
}

/* Collected DATA-table cells resolve author styles too (found via --dump-dom:
 * the cell path never called resolve_context, so td{color} / zebra
 * tr:nth-child(even){background} / tr:first-child{font-weight} were silently
 * lost while every non-table run got them). The cell's own style and its
 * row/table ancestors' inherited style must land on the collected run. */
static void test_build_table_cell_author_styles(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<head><style>"
        "td { color:#cc0011 }"
        "tr:nth-child(even) { background:#e8e8e8 }"
        "tr:first-child { font-weight:bold }"
        "</style></head><body>"
        "<table>"
        "<tr><td>alpha</td></tr>"
        "<tr><td>beta</td></tr>"
        "<tr><td>gamma</td></tr>"
        "</table></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *a = find_text(v, "alpha");
    assert_non_null(a);
    assert_int_equal(a->fg_rgb, 0xcc0011);   /* td's own rule */
    assert_int_equal(a->bold, 1);            /* inherited from tr:first-child */
    assert_int_equal(a->bg_rgb, -1);         /* row 1 is odd: no zebra */

    const pv_run *b = find_text(v, "beta");
    assert_non_null(b);
    assert_int_equal(b->fg_rgb, 0xcc0011);
    assert_int_equal(b->bg_rgb, 0xe8e8e8);   /* zebra via tr:nth-child(even) */
    assert_int_equal(b->bold, 0);

    const pv_run *g = find_text(v, "gamma");
    assert_non_null(g);
    assert_int_equal(g->bg_rgb, -1);

    pv_free(v);
    hp_document_free(doc);
}

/* A <style> sheet colors matching elements: a type rule and a class rule. The
 * <style> text itself never leaks as a run (already covered elsewhere). */
static void test_build_style_sheet_color(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><style>p{color:#0a0b0c} .hi{color:#112233}</style>"
        "<p>styled</p><span class='hi'>classed</span></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *p = find_text(v, "styled");
    assert_non_null(p);
    assert_int_equal(p->fg_rgb, 0x0a0b0c);
    const pv_run *c = find_text(v, "classed");
    assert_non_null(c);
    assert_int_equal(c->fg_rgb, 0x112233);
    pv_free(v);
    hp_document_free(doc);
}

/* @media(prefers-color-scheme: dark) in a <style> applies only when pv_build_full is
 * told the user prefers dark (auto dark mode threaded through to the css module). */
static void test_build_prefers_color_scheme(void **state) {
    (void)state;
    const char *html =
        "<body><style>@media (prefers-color-scheme: dark){ p { color:#ffffff } }</style>"
        "<p>auto</p></body>";
    hp_document *doc = parse(html);

    pv_view *light = NULL;
    assert_int_equal(pv_build_full(doc, 0, 0, 0, &light), PV_OK); /* prefers_dark = 0 */
    assert_int_equal(find_text(light, "auto")->fg_rgb, -1);
    pv_free(light);

    pv_view *dark = NULL;
    assert_int_equal(pv_build_full(doc, 0, 0, 1, &dark), PV_OK); /* prefers_dark = 1 */
    assert_int_equal(find_text(dark, "auto")->fg_rgb, 0xffffff);
    pv_free(dark);
    hp_document_free(doc);
}

/* text-align and font-size resolve into the new run fields, from both a <style>
 * sheet and inline style=. */
static void test_build_text_align_and_font_size(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><style>h1{text-align:center;font-size:200%}</style>"
        "<h1>big</h1><p style='text-align:right'>right</p>"
        "<p style='font-size:32px'>large</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *big = find_text(v, "big");
    assert_non_null(big);
    assert_int_equal(big->text_align, CSS_ALIGN_CENTER);
    assert_int_equal(big->font_scale, 200);
    const pv_run *right = find_text(v, "right");
    assert_non_null(right);
    assert_int_equal(right->text_align, CSS_ALIGN_RIGHT);
    const pv_run *large = find_text(v, "large");
    assert_non_null(large);
    assert_int_equal(large->font_scale, 200); /* 32/16 */
    /* Default (no author CSS): both fields unset. */
    const pv_run *plain = find_text(v, "right");
    assert_int_equal(plain->font_scale, 0);
    pv_free(v);
    hp_document_free(doc);
}

/* line-height resolves into line_scale from a <style> sheet and inline style=, and
 * inherits to descendant text (like font-size). */
static void test_build_line_height(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><style>p{line-height:1.8}</style>"
        "<p>sheet <span>inherited</span></p>"
        "<div style='line-height:160%'>inlined</div>"
        "<h2 style='font-size:120%'>nolh</h2></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    assert_int_equal(find_text(v, "sheet ")->line_scale, 180);
    assert_int_equal(find_text(v, "inherited")->line_scale, 180); /* inherited from <p> */
    assert_int_equal(find_text(v, "inlined")->line_scale, 160);
    /* An <h2> is not matched by the p{} rule and sets no line-height: unset. */
    assert_int_equal(find_text(v, "nolh")->line_scale, 0);
    pv_free(v);
    hp_document_free(doc);
}

/* text-decoration resolves into text_decoration from a <style> sheet and inline
 * style=, inherits to descendant text, and an inline `none` drops a link underline. */
static void test_build_text_decoration(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><style>p{text-decoration:line-through} a{text-decoration:underline}</style>"
        "<p>struck <span>inherited</span></p>"
        "<a href='https://e.x/'>linky</a>"
        "<a href='https://e.x/' style='text-decoration:none'>plain</a>"
        "<div style='text-decoration:overline'>over</div>"
        "<h3>plainh</h3></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    assert_int_equal(find_text(v, "struck ")->text_decoration, CSS_DECO_LINE_THROUGH);
    assert_int_equal(find_text(v, "inherited")->text_decoration, CSS_DECO_LINE_THROUGH);
    assert_int_equal(find_text(v, "linky")->text_decoration, CSS_DECO_UNDERLINE);
    assert_int_equal(find_text(v, "plain")->text_decoration, 0); /* none: explicit removal */
    assert_int_equal(find_text(v, "over")->text_decoration, CSS_DECO_OVERLINE);
    /* An <h3> matched by no rule sets none: unset (-1). */
    assert_int_equal(find_text(v, "plainh")->text_decoration, -1);
    pv_free(v);
    hp_document_free(doc);
}

/* font-weight via CSS sets bold; an inline declaration wins over an id rule. */
static void test_build_css_bold_and_inline_wins(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><style>#x{color:#111111} .b{font-weight:bold}</style>"
        "<p id='x' style='color:#abcabc'>t</p>"
        "<p class='b'>strongish</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *t = find_text(v, "t");
    assert_non_null(t);
    assert_int_equal(t->fg_rgb, 0xabcabc); /* inline beats the #x sheet rule */
    const pv_run *s = find_text(v, "strongish");
    assert_non_null(s);
    assert_int_equal(s->bold, 1); /* font-weight:bold from the .b rule */
    pv_free(v);
    hp_document_free(doc);
}

/* display:none (inline or from a sheet) hides the element and its whole subtree. */
static void test_build_display_none_hidden(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><style>.gone{display:none}</style>"
        "<p style='display:none'>secret</p>"
        "<div style='display:none'><span>nested</span></div>"
        "<p class='gone'>classed-hidden</p>"
        "<p>shown</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    assert_null(find_text(v, "secret"));
    assert_null(find_text(v, "nested"));
    assert_null(find_text(v, "classed-hidden"));
    assert_non_null(find_text(v, "shown"));
    pv_free(v);
    hp_document_free(doc);
}

/* External pre-fetched CSS (Hito 27) feeds the same cascade as the document's
 * <style>: an extern rule applies (presentation and display:none alike); at equal
 * specificity the document's own sheet, concatenated after, wins; and a NULL
 * extern is byte-identical to pv_build_full (no-regression lock). page_view stays
 * pure -- the bytes were fetched by the trusted parent, never here. */
static void test_build_styled_external_css(void **state) {
    (void)state;
    hp_document *doc = parse(
        "<body><style>p.own{text-align:right}</style>"
        "<p>centered</p>"
        "<p class='own'>docwins</p>"
        "<p class='gone'>hidden</p></body>");
    static const char EXT[] =
        "p{text-align:center} p.own{text-align:center} .gone{display:none}";
    pv_view *v = NULL;
    assert_int_equal(pv_build_styled(doc, 0, 0, 0, EXT, sizeof EXT - 1, &v), PV_OK);
    assert_int_equal(find_text(v, "centered")->text_align, CSS_ALIGN_CENTER);
    assert_int_equal(find_text(v, "docwins")->text_align, CSS_ALIGN_RIGHT);
    assert_null(find_text(v, "hidden"));
    pv_free(v);

    pv_view *w = NULL;
    assert_int_equal(pv_build_styled(doc, 0, 0, 0, NULL, 0, &w), PV_OK);
    assert_int_equal(find_text(w, "centered")->text_align, CSS_ALIGN_UNSET);
    assert_non_null(find_text(w, "hidden"));
    pv_free(w);
    hp_document_free(doc);
}

/* Reader (distraction-free) mode skips nav/header/footer/aside boilerplate but
 * keeps the main article content; with reader off, the boilerplate is kept. */
static void test_build_reader_skips_boilerplate(void **state) {
    (void)state;
    const char *html =
        "<body><nav>navlink</nav><header>site header</header>"
        "<article><p>main content</p></article>"
        "<aside>related</aside><footer>copyright</footer></body>";
    hp_document *doc = parse(html);

    pv_view *r = NULL;
    assert_int_equal(pv_build_full(doc, 0, 1, 0, &r), PV_OK); /* reader on */
    assert_non_null(find_text(r, "main content"));
    assert_null(find_text(r, "navlink"));
    assert_null(find_text(r, "site header"));
    assert_null(find_text(r, "related"));
    assert_null(find_text(r, "copyright"));
    pv_free(r);

    pv_view *n = NULL;
    assert_int_equal(pv_build_full(doc, 0, 0, 0, &n), PV_OK); /* reader off */
    assert_non_null(find_text(n, "navlink"));
    assert_non_null(find_text(n, "main content"));
    pv_free(n);
    hp_document_free(doc);
}

/* pv_set_text_style sets the fields on the most recent run; NULL/empty safe. */
/* The setter is a no-op when the view is empty or NULL, and it writes to the
 * most recently appended run otherwise. */
static void test_set_node_id_model(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, "hello", NULL), PV_OK);
    pv_set_node_id(v, 42);
    assert_int_equal(pv_at(v, 0)->node_id, 42);
    pv_set_node_id(v, DOM_NODE_NONE);
    assert_int_equal(pv_at(v, 0)->node_id, DOM_NODE_NONE);
    pv_set_node_id(NULL, 7); /* NULL-safe */
    pv_free(v);
}

/* Stage 0 keystone: every emitted run carries the document-order element id of
 * its source element, matching the id that dom_build assigns to the same
 * element. This is what lets the GUI dispatch a click on a painted block back
 * to the worker's live DOM. */
static void test_build_node_id_matches_dom_index(void **state) {
    (void)state;
    hp_document *doc = parse("<html><head></head><body>"
                             "<p id='a'>alpha</p>"
                             "<img src='https://x.example/i.png' alt='pic'>"
                             "<p id='b'><a href='/x'>beta</a></p>"
                             "</body></html>");
    dom_index *idx = NULL;
    assert_int_equal(dom_build(doc, &idx), DOM_OK);
    dom_node_id id_a = dom_get_element_by_id(idx, "a");
    dom_node_id id_b = dom_get_element_by_id(idx, "b");
    assert_int_not_equal(id_a, DOM_NODE_NONE);
    assert_int_not_equal(id_b, DOM_NODE_NONE);

    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *alpha = find_text(v, "alpha");
    const pv_run *pic = find_image(v, "https://x.example/i.png");
    const pv_run *beta = find_text(v, "beta");
    dom_node_id id_img = DOM_NODE_NONE;
    size_t nimg = dom_get_by_tag(idx, "img", &id_img, 1);
    assert_int_equal(nimg, 1);
    dom_node_id id_a_anchor = DOM_NODE_NONE;
    size_t na = dom_get_by_tag(idx, "a", &id_a_anchor, 1);
    assert_int_equal(na, 1);

    assert_non_null(alpha);
    assert_non_null(pic);
    assert_non_null(beta);
    assert_int_equal(alpha->node_id, id_a);
    assert_int_equal(pic->node_id, id_img);
    assert_int_equal(beta->node_id, id_a_anchor);

    pv_free(v);
    dom_free(idx);
    hp_document_free(doc);
}

static void test_set_text_style_model(void **state) {
    (void)state;
    pv_view *v = pv_new();
    pv_set_text_style(v, CSS_ALIGN_CENTER, 150, 140, CSS_DECO_UNDERLINE); /* no-op: empty view */
    assert_int_equal((int)pv_count(v), 0);
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, "x", NULL), PV_OK);
    assert_int_equal(pv_at(v, 0)->text_align, 0); /* default */
    assert_int_equal(pv_at(v, 0)->font_scale, 0);
    assert_int_equal(pv_at(v, 0)->line_scale, 0);
    assert_int_equal(pv_at(v, 0)->text_decoration, -1); /* default unset */
    pv_set_text_style(v, CSS_ALIGN_RIGHT, 175, 160, CSS_DECO_LINE_THROUGH);
    assert_int_equal(pv_at(v, 0)->text_align, CSS_ALIGN_RIGHT);
    assert_int_equal(pv_at(v, 0)->font_scale, 175);
    assert_int_equal(pv_at(v, 0)->line_scale, 160);
    assert_int_equal(pv_at(v, 0)->text_decoration, CSS_DECO_LINE_THROUGH);
    pv_set_text_style(NULL, 0, 0, 0, 0); /* NULL-safe */
    pv_free(v);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_is_empty),
        cmocka_unit_test(test_append_copies_fields),
        cmocka_unit_test(test_append_image_copies_fields),
        cmocka_unit_test(test_append_image_null_args),
        cmocka_unit_test(test_append_transcodes_latin1),
        cmocka_unit_test(test_append_transcodes_word),
        cmocka_unit_test(test_append_transcodes_cp1252_quotes),
        cmocka_unit_test(test_append_undefined_cp1252_is_qmark),
        cmocka_unit_test(test_append_valid_utf8_passthrough),
        cmocka_unit_test(test_append_null_args),
        cmocka_unit_test(test_free_null_and_double),
        cmocka_unit_test(test_build_null_args),
        cmocka_unit_test(test_build_plain_text),
        cmocka_unit_test(test_build_heading_level),
        cmocka_unit_test(test_build_inline_emphasis),
        cmocka_unit_test(test_build_unordered_list),
        cmocka_unit_test(test_build_ordered_and_nested_list),
        cmocka_unit_test(test_build_table_grid),
        cmocka_unit_test(test_build_table_flattens_cell),
        cmocka_unit_test(test_build_collected_text_skips_style_and_script),
        cmocka_unit_test(test_build_multilink_table_flows_links),
        cmocka_unit_test(test_build_single_link_cell_collected_as_link),
        cmocka_unit_test(test_build_bgcolor_attr_fallback),
        cmocka_unit_test(test_build_nested_table_not_flattened),
        cmocka_unit_test(test_build_link_with_href),
        cmocka_unit_test(test_build_block_break_between_paragraphs),
        cmocka_unit_test(test_build_skips_script_and_style),
        cmocka_unit_test(test_build_inline_link_no_break_within_paragraph),
        cmocka_unit_test(test_build_image_with_dims),
        cmocka_unit_test(test_build_image_unknown_dims),
        cmocka_unit_test(test_build_image_px_and_tracking_dims),
        cmocka_unit_test(test_build_image_in_skipped_subtree_ignored),
        cmocka_unit_test(test_build_noscript_shown_when_js_off),
        cmocka_unit_test(test_build_noscript_hidden_when_js_on),
        cmocka_unit_test(test_build_image_without_src_ignored),
        cmocka_unit_test(test_build_empty_document),
        cmocka_unit_test(test_set_color_model),
        cmocka_unit_test(test_build_author_color),
        cmocka_unit_test(test_build_combinator_selectors),
        cmocka_unit_test(test_build_flex_container),
        cmocka_unit_test(test_build_flex_item_values),
        cmocka_unit_test(test_build_flex_whitespace_not_item),
        cmocka_unit_test(test_build_interblock_whitespace_not_emitted),
        cmocka_unit_test(test_build_inline_whitespace_kept),
        cmocka_unit_test(test_build_cont_item_identity),
        cmocka_unit_test(test_build_table_cells_distinct_items),
        cmocka_unit_test(test_build_grid_container),
        cmocka_unit_test(test_build_flex_container_from_sheet),
        cmocka_unit_test(test_build_grid_columns_from_sheet),
        cmocka_unit_test(test_build_container_sheet_inline_cascade),
        cmocka_unit_test(test_container_defaults),
        cmocka_unit_test(test_build_box_wrapper_centering_from_sheet),
        cmocka_unit_test(test_build_box_leaf_inline),
        cmocka_unit_test(test_box_defaults_and_setter),
        cmocka_unit_test(test_build_boxdeco_border_padding),
        cmocka_unit_test(test_build_boxdeco_shadow_outline),
        cmocka_unit_test(test_build_boxdeco_defaults_no_box),
        cmocka_unit_test(test_build_boxdeco_sibling_blocks_distinct_ids),
        cmocka_unit_test(test_build_boxdeco_shared_id_within_block),
        cmocka_unit_test(test_build_box_tree_nested),
        cmocka_unit_test(test_build_box_tree_textless_wrapper),
        cmocka_unit_test(test_build_box_tree_empty_no_box),
        cmocka_unit_test(test_build_search_form_get),
        cmocka_unit_test(test_build_form_post_and_hidden),
        cmocka_unit_test(test_build_textarea_value),
        cmocka_unit_test(test_build_control_without_form),
        cmocka_unit_test(test_build_two_forms_distinct_groups),
        cmocka_unit_test(test_build_style_sheet_color),
        cmocka_unit_test(test_build_attr_selectors_and_important),
        cmocka_unit_test(test_build_pseudo_classes_and_siblings),
        cmocka_unit_test(test_build_table_cell_author_styles),
        cmocka_unit_test(test_build_prefers_color_scheme),
        cmocka_unit_test(test_build_text_align_and_font_size),
        cmocka_unit_test(test_build_line_height),
        cmocka_unit_test(test_build_text_decoration),
        cmocka_unit_test(test_build_css_bold_and_inline_wins),
        cmocka_unit_test(test_build_display_none_hidden),
        cmocka_unit_test(test_build_styled_external_css),
        cmocka_unit_test(test_build_reader_skips_boilerplate),
        cmocka_unit_test(test_set_node_id_model),
        cmocka_unit_test(test_build_node_id_matches_dom_index),
        cmocka_unit_test(test_set_text_style_model),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
