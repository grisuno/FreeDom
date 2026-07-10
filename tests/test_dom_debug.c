/*
 * TDD suite for dom_debug — agent-readable dump of the paint-ready render tree.
 *
 * Pure: builds a pv_view directly, runs rd_build, and asserts on the text dd_format
 * produces. Pins the structural mapping (header counts, per-block kind/tag, container
 * and box annotations) and the bounded/no-overflow contract. No I/O.
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
#include "css.h"
#include "dom_debug.h"
#include "page_view.h"
#include "render_doc.h"
#include "render_policy.h"

static const char TOP[] = "https://example.com/";

static rdp_caps caps_css_on(void) {
    rdp_caps c = rdp_caps_safe();
    c.css = true;          /* box tree + author box/style fields only with caps.css */
    return c;
}

/* Builds an rd_doc from v (taking ownership of neither; caller frees v). */
static rd_doc *build(pv_view *v, rdp_caps caps) {
    rd_doc *d = NULL;
    assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK);
    assert_non_null(d);
    return d;
}

/* --- empty / null --- */

static void test_null_doc_is_empty_header(void **state) {
    (void)state;
    char buf[256];
    size_t n = dd_format(NULL, buf, sizeof buf);
    assert_true(n > 0);
    assert_true(n < sizeof buf);              /* not truncated */
    assert_non_null(strstr(buf, "=== Freedom render tree ==="));
    assert_non_null(strstr(buf, "blocks: 0"));
    assert_non_null(strstr(buf, "boxes: 0"));
    assert_non_null(strstr(buf, "containers: 0"));
}

/* --- structural mapping: kind + tag + href in document order --- */

static void test_heading_paragraph_link(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 2, 1, "Title", NULL), PV_OK);
    assert_int_equal(pv_append(v, PV_TEXT, 0, 1, "body text", NULL), PV_OK);
    assert_int_equal(pv_append(v, PV_LINK, 0, 0, "click", "https://e.example/x"), PV_OK);

    rd_doc *d = build(v, rdp_caps_safe());
    char buf[1024];
    size_t n = dd_format(d, buf, sizeof buf);
    assert_true(n < sizeof buf);

    assert_non_null(strstr(buf, "blocks: 3"));
    assert_non_null(strstr(buf, "heading"));       /* rd_kind_name is lowercase */
    assert_non_null(strstr(buf, "<h2>"));          /* heading level 2 -> tag h2 */
    assert_non_null(strstr(buf, "paragraph"));
    assert_non_null(strstr(buf, "link"));
    assert_non_null(strstr(buf, "<a>"));
    assert_non_null(strstr(buf, "https://e.example/x"));
    assert_non_null(strstr(buf, "Title"));

    /* document order: the heading line precedes the link line */
    char *h = strstr(buf, "heading");
    char *l = strstr(buf, "link");
    assert_true(h != NULL && l != NULL && h < l);

    rd_free(d);
    pv_free(v);
}

/* --- a grid container (a table) annotates its cells: the field that reveals a
 *     collapsed table column --- */

static void test_grid_container_annotation(void **state) {
    (void)state;
    pv_view *v = pv_new();
    for (int i = 0; i < 3; ++i) {
        assert_int_equal(pv_append(v, PV_TEXT, 0, 1, "cell", NULL), PV_OK);
        /* cont_id=7, display=grid, gap=0, justify=start, cols=3 */
        pv_set_container(v, 7, BX_DISPLAY_GRID, 0, FX_JUSTIFY_START, 3, 0, -1, 0);
    }
    rd_doc *d = build(v, rdp_caps_safe());        /* containers carried regardless of caps.css */
    char buf[1024];
    size_t n = dd_format(d, buf, sizeof buf);
    assert_true(n < sizeof buf);

    assert_non_null(strstr(buf, "containers: 1")); /* one distinct cont_id */
    assert_non_null(strstr(buf, "cont=#7"));
    assert_non_null(strstr(buf, "grid"));
    assert_non_null(strstr(buf, "cols=3"));

    rd_free(d);
    pv_free(v);
}

/* --- a box def with a width cap appears in [boxes]; its block carries box=#id --- */

static void test_box_tree_width_cap(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 0, 1, "inside the box", NULL), PV_OK);
    pv_set_block_id(v, 0);

    pv_box_def b;
    memset(&b, 0, sizeof b);
    b.parent_id = -1;
    b.box_w = 300;                 /* the width cap to surface */
    b.bg_rgb = 0xff6600;           /* HN orange, to surface bg */
    b.box_sizing = 0;
    b.bord_tw = b.bord_rw = b.bord_bw = b.bord_lw = PV_LEN_UNSET;
    b.bord_tc = b.bord_rc = b.bord_bc = b.bord_lc = -1;
    b.border_radius = PV_LEN_UNSET;
    b.bsh_color = -1;
    b.outline_w = PV_LEN_UNSET; b.outline_color = -1;
    assert_int_equal(pv_add_box_def(v, &b), PV_OK);

    rd_doc *d = build(v, caps_css_on());          /* box tree only with caps.css */
    assert_true(rd_box_count(d) == 1);

    char buf[1024];
    size_t n = dd_format(d, buf, sizeof buf);
    assert_true(n < sizeof buf);

    assert_non_null(strstr(buf, "boxes: 1"));
    assert_non_null(strstr(buf, "[boxes]"));
    assert_non_null(strstr(buf, "w=300"));
    assert_non_null(strstr(buf, "#ff6600"));
    assert_non_null(strstr(buf, "box=#0"));        /* the block joined box 0 */

    rd_free(d);
    pv_free(v);
}

/* --- visibility/overflow/cursor on a box, and text-overflow/word-break on a run --- */

static void test_visibility_overflow_cursor_and_text_wrap(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 0, 1, "inside the box", NULL), PV_OK);
    pv_set_block_id(v, 0);
    pv_set_text_ext(v, 0, 0, PV_LEN_UNSET, PV_LEN_UNSET, 0, 0, -1, -1, 0,
                    PV_LEN_UNSET, CSS_WS_NOWRAP, CSS_TO_ELLIPSIS, CSS_WB_BREAK,
                    -1, 0, -1);

    pv_box_def b;
    memset(&b, 0, sizeof b);
    b.parent_id = -1;
    b.bg_rgb = -1;
    b.bord_tw = b.bord_rw = b.bord_bw = b.bord_lw = PV_LEN_UNSET;
    b.bord_tc = b.bord_rc = b.bord_bc = b.bord_lc = -1;
    b.border_radius = PV_LEN_UNSET;
    b.bsh_color = -1;
    b.outline_w = PV_LEN_UNSET; b.outline_color = -1;
    b.visibility = CSS_VIS_HIDDEN;
    b.overflow_x = CSS_OF_HIDDEN; b.overflow_y = CSS_OF_SCROLL;
    b.cursor = CSS_CUR_POINTER;
    assert_int_equal(pv_add_box_def(v, &b), PV_OK);

    rd_doc *d = build(v, caps_css_on());
    char buf[1024];
    size_t n = dd_format(d, buf, sizeof buf);
    assert_true(n < sizeof buf);

    assert_non_null(strstr(buf, "visibility=hidden"));
    assert_non_null(strstr(buf, "overflow=hidden/scroll"));
    assert_non_null(strstr(buf, "cursor=pointer"));
    assert_non_null(strstr(buf, "text-overflow=ellipsis"));
    assert_non_null(strstr(buf, "word-break=break"));

    rd_free(d);
    pv_free(v);
}

/* --- with caps.css off there is no box tree (byte-identical render principle) --- */

static void test_no_box_tree_without_css(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 0, 1, "x", NULL), PV_OK);
    pv_set_block_id(v, 0);
    pv_box_def b; memset(&b, 0, sizeof b); b.parent_id = -1; b.bsh_color = -1;
    assert_int_equal(pv_add_box_def(v, &b), PV_OK);

    rd_doc *d = build(v, rdp_caps_safe());         /* css OFF */
    char buf[512];
    dd_format(d, buf, sizeof buf);
    assert_non_null(strstr(buf, "boxes: 0"));
    assert_null(strstr(buf, "[boxes]"));

    rd_free(d);
    pv_free(v);
}

/* --- bounded: tiny cap never overflows, returns full length, NUL-terminates --- */

static void test_truncation_no_overflow(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 1, 1, "a long enough heading to exceed", NULL), PV_OK);
    rd_doc *d = build(v, rdp_caps_safe());

    /* full length first */
    size_t full = dd_format(d, NULL, 0);
    assert_true(full > 8);

    unsigned char guard[64];
    memset(guard, 0xAA, sizeof guard);
    size_t cap = 8;
    size_t n = dd_format(d, (char *)guard, cap);
    assert_int_equal((int)n, (int)full);          /* reports the untruncated length */
    /* NUL within the cap */
    int found_nul = 0;
    for (size_t i = 0; i < cap; ++i) if (guard[i] == '\0') { found_nul = 1; break; }
    assert_true(found_nul);
    /* nothing written past cap-1 */
    for (size_t i = cap; i < sizeof guard; ++i) assert_int_equal(guard[i], 0xAA);

    rd_free(d);
    pv_free(v);
}

/* --- a control byte in hostile text never breaks the one-line-per-block layout --- */

static void test_control_bytes_kept_on_one_line(void **state) {
    (void)state;
    pv_view *v = pv_new();
    /* embedded newline + tab in the text */
    assert_int_equal(pv_append(v, PV_TEXT, 0, 1, "line1\n\tline2", NULL), PV_OK);
    rd_doc *d = build(v, rdp_caps_safe());

    char buf[512];
    dd_format(d, buf, sizeof buf);

    /* locate the block line (after the [blocks] marker) and check it holds no raw
     * newline between the quote and its close: the field is sanitised to one line. */
    char *q = strchr(buf, '"');
    assert_non_null(q);
    char *end = strchr(q + 1, '"');
    assert_non_null(end);
    for (char *p = q + 1; p < end; ++p) {
        assert_true(*p != '\n');
        assert_true(*p != '\t');
    }
    rd_free(d);
    pv_free(v);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_null_doc_is_empty_header),
        cmocka_unit_test(test_heading_paragraph_link),
        cmocka_unit_test(test_grid_container_annotation),
        cmocka_unit_test(test_box_tree_width_cap),
        cmocka_unit_test(test_visibility_overflow_cursor_and_text_wrap),
        cmocka_unit_test(test_no_box_tree_without_css),
        cmocka_unit_test(test_truncation_no_overflow),
        cmocka_unit_test(test_control_bytes_kept_on_one_line),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
