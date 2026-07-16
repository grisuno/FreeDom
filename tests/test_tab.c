/*
 * TDD suite for tab (Hito 5 - long-lived per-tab worker + JS in the child).
 *
 * tab_open forks a Landlock+seccomp-confined child internally; these tests run
 * in the parent and drive the child over the private pipe protocol. The parent
 * surviving hostile/binary input and a killed child is itself the isolation
 * guarantee.
 *
 * RED state until src/tab.c exists: this links and fails on purpose.
 *
 * Build: make test   ;   ASan: make asan
 */

#define _POSIX_C_SOURCE 200809L

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <cmocka.h>

#include "css.h"
#include "tab.h"

static const char HTML[] =
    "<!DOCTYPE html><html><head><title>Isolated</title></head>"
    "<body><div id=\"main\" class=\"box\"><p>Hola</p>"
    "<script>steal_cookies()</script>"
    "<p onclick=\"evil()\">mundo</p></div></body></html>";

/* --- a confined worker fixture shared by the binding tests --- */

typedef struct fixture { tab *t; } fixture;

static int setup_loaded(void **state) {
    fixture *f = (fixture *)calloc(1, sizeof *f);
    if (f == NULL) return -1;
    if (tab_open(&f->t) != TAB_OK) return -1;
    tab_page p;
    if (tab_load(f->t, HTML, sizeof HTML - 1, &p) != TAB_OK) return -1;
    tab_page_free(&p);
    *state = f;
    return 0;
}

static int teardown(void **state) {
    fixture *f = (fixture *)*state;
    if (f != NULL) {
        tab_close(f->t);
        free(f);
    }
    return 0;
}

/* Evaluates js and asserts the (non-exception) string result. */
static void expect_eval(tab *t, const char *js, const char *expected) {
    tab_eval_result r;
    assert_int_equal(tab_eval(t, js, strlen(js), &r), TAB_OK);
    assert_int_equal(r.is_exception, 0);
    assert_non_null(r.value);
    assert_string_equal(r.value, expected);
    tab_eval_result_free(&r);
}

/* --- lifecycle --- */

static void test_open_close(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    assert_non_null(t);
    assert_true(tab_alive(t));
    assert_true(tab_child_pid(t) > 0);
    tab_close(t);
}

static void test_open_null(void **state) {
    (void)state;
    assert_int_equal(tab_open(NULL), TAB_ERR_NULL_ARG);
}

/* --- load: inert title + text --- */

static void test_load_basic(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, HTML, sizeof HTML - 1, &p), TAB_OK);
    assert_non_null(p.title);
    assert_string_equal(p.title, "Isolated");
    assert_non_null(p.text);
    assert_non_null(strstr(p.text, "Hola"));
    assert_non_null(strstr(p.text, "mundo"));
    tab_page_free(&p);
    tab_close(t);
}

/* The structured display list must survive the IPC round-trip: a heading and a
 * link with its href arrive intact in p.view. */
static void test_load_returns_view_with_link(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>V</title></head><body>"
        "<h1>Head</h1><p>go <a href=\"https://e.example/x\">here</a></p></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.view);

    int saw_heading = 0, saw_link = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->heading == 1 && strcmp(r->text, "Head") == 0) saw_heading = 1;
        if (r->kind == PV_LINK && strcmp(r->text, "here") == 0
            && r->href != NULL && strcmp(r->href, "https://e.example/x") == 0) saw_link = 1;
    }
    assert_true(saw_heading);
    assert_true(saw_link);

    tab_page_free(&p);
    tab_close(t);
}

/* An <img> must survive the IPC round-trip as a PV_IMAGE run carrying its src,
 * alt text, and declared dimensions (so render_policy can later gate it). */
static void test_load_returns_image_run(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>I</title></head><body>"
        "<img src=\"https://e.example/logo.png\" alt=\"Logo\" width=\"200\" height=\"80\">"
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.view);

    int saw_image = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->kind == PV_IMAGE && r->src != NULL
            && strcmp(r->src, "https://e.example/logo.png") == 0) {
            assert_string_equal(r->text, "Logo");
            assert_int_equal(r->img_w, 200);
            assert_int_equal(r->img_h, 80);
            saw_image = 1;
        }
    }
    assert_true(saw_image);

    tab_page_free(&p);
    tab_close(t);
}

/* An author color extracted in the confined child must survive the IPC round-trip
 * as the run's fg_rgb (so the parent can apply it once CSS is enabled). */
static void test_load_carries_author_color(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>C</title></head><body>"
        "<p style=\"color:#3366cc\">tinted</p></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.view);

    int saw_color = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->text != NULL && strcmp(r->text, "tinted") == 0) {
            assert_int_equal(r->fg_rgb, 0x3366cc);
            saw_color = 1;
        }
    }
    assert_true(saw_color);

    tab_page_free(&p);
    tab_close(t);
}

/* Stage 3: the per-item flex values resolved by the worker must survive the IPC
 * round-trip (write_view/read_view), so the GUI's flex layout can honor them. */
static void test_load_carries_flex_item(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>F</title></head><body>"
        "<div style=\"display:flex;flex-direction:column\">"
        "<div style=\"flex:2;order:3\">grow</div>"
        "<div>plain</div></div></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.view);

    int saw_grow = 0, saw_plain = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->text == NULL) continue;
        if (strcmp(r->text, "grow") == 0) {
            assert_int_equal(r->flex_grow, 200);
            assert_int_equal(r->flex_shrink, 100);
            assert_int_equal(r->flex_basis, 0);
            assert_int_equal(r->flex_order, 3);
            assert_int_equal(r->flex_direction, CSS_FD_COLUMN);
            saw_grow = 1;
        }
        if (strcmp(r->text, "plain") == 0) {
            assert_int_equal(r->flex_grow, -1);
            assert_int_equal(r->flex_shrink, -1);
            assert_int_equal(r->flex_basis, CSS_LEN_UNSET);
            assert_int_equal(r->flex_order, CSS_LEN_UNSET);
            assert_int_equal(r->flex_direction, CSS_FD_COLUMN);
            saw_plain = 1;
        }
    }
    assert_true(saw_grow);
    assert_true(saw_plain);

    tab_page_free(&p);
    tab_close(t);
}

/* flex-wrap / row-gap / align-items (CONTAINER) + align-self (ITEM) survive the
 * worker round-trip (write_view/read_view serialize the 4 new fields in the same
 * order on both sides). */
static void test_load_carries_flex_wrap_align_row_gap(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>F</title></head><body>"
        "<div style=\"display:flex;flex-wrap:wrap;row-gap:15px;align-items:center\">"
        "<div style=\"align-self:flex-end\">a</div>"
        "<div>b</div></div></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.view);

    int saw_a = 0, saw_b = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->text == NULL) continue;
        if (strcmp(r->text, "a") == 0) {
            assert_int_equal(r->cont_wrap, CSS_FW_WRAP);
            assert_int_equal(r->cont_row_gap, 15);
            assert_int_equal(r->cont_align_items, CSS_AK_CENTER);
            assert_int_equal(r->flex_align_self, CSS_AK_END);
            saw_a = 1;
        }
        if (strcmp(r->text, "b") == 0) {
            assert_int_equal(r->cont_wrap, CSS_FW_WRAP);
            assert_int_equal(r->cont_row_gap, 15);
            assert_int_equal(r->flex_align_self, CSS_AK_UNSET);
            saw_b = 1;
        }
    }
    assert_true(saw_a);
    assert_true(saw_b);

    tab_page_free(&p);
    tab_close(t);
}

/* float.md over IPC: float_side/float_id/float_clear survive the worker round-trip
 * (write_view/read_view serialize them in the same order on both sides). */
static void test_load_carries_float(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>F</title></head><body>"
        "<div style=\"float:left\">nav</div>"
        "<div style=\"float:right\">side</div>"
        "<div style=\"clear:both\">foot</div>"
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.view);

    int nav_id = -2, side_id = -2, saw_foot = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->text == NULL) continue;
        if (strcmp(r->text, "nav") == 0) {
            assert_int_equal(r->float_side, CSS_FLOAT_LEFT);
            assert_true(r->float_id >= 0);
            nav_id = r->float_id;
        }
        if (strcmp(r->text, "side") == 0) {
            assert_int_equal(r->float_side, CSS_FLOAT_RIGHT);
            side_id = r->float_id;
        }
        if (strcmp(r->text, "foot") == 0) {
            assert_int_equal(r->float_id, -1);
            assert_int_equal(r->float_clear, CSS_CLEAR_BOTH);
            saw_foot = 1;
        }
    }
    assert_true(nav_id >= 0 && side_id >= 0 && nav_id != side_id);
    assert_true(saw_foot);

    tab_page_free(&p);
    tab_close(t);
}

/* visibility/overflow/cursor (box-level) and text-overflow/word-break (run-level)
 * survive the worker round-trip -- write_view/read_view serialize the box-def f[]
 * array and the per-run tail in the same order on both sides. */
static void test_load_carries_visibility_overflow_cursor_and_text_wrap(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>V</title></head><body>"
        "<div style=\"visibility:hidden;overflow-x:hidden;overflow-y:scroll;"
        "cursor:pointer\">solo</div>"
        "<p style=\"text-overflow:ellipsis;white-space:nowrap;word-break:break-all\">wrapme</p>"
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.view);

    int saw_solo = 0, saw_wrap = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->text == NULL) continue;
        if (strcmp(r->text, "solo") == 0) {
            assert_true(r->block_id >= 0);
            const pv_box_def *bx = pv_box_at(p.view, (size_t)r->block_id);
            assert_non_null(bx);
            assert_int_equal(bx->visibility, CSS_VIS_HIDDEN);
            assert_int_equal(bx->overflow_x, CSS_OF_HIDDEN);
            assert_int_equal(bx->overflow_y, CSS_OF_SCROLL);
            assert_int_equal(bx->cursor, CSS_CUR_POINTER);
            saw_solo = 1;
        }
        if (strcmp(r->text, "wrapme") == 0) {
            assert_int_equal(r->text_overflow, CSS_TO_ELLIPSIS);
            assert_int_equal(r->word_break, CSS_WB_BREAK);
            saw_wrap = 1;
        }
    }
    assert_true(saw_solo);
    assert_true(saw_wrap);

    tab_page_free(&p);
    tab_close(t);
}

/* Container-item identity over IPC: inline fragments of the same direct child
 * share one cont_item ordinal, the next child differs, and the inter-block source
 * whitespace emits no run at all (no blank lines cross the wire). */
static void test_load_carries_cont_item(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>I</title></head><body>"
        "<div style=\"display:grid;grid-template-columns:1fr\">\n"
        "<p>lead <a href=\"https://e.example/f\">free</a> tail</p>\n"
        "<p>second</p>\n"
        "</div></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.view);

    int item_lead = -2, item_free = -3, item_tail = -4, item_second = -5;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->text == NULL) continue;
        if (strcmp(r->text, "lead ") == 0) item_lead = r->cont_item;
        if (strcmp(r->text, "free") == 0) item_free = r->cont_item;
        if (strcmp(r->text, " tail") == 0) item_tail = r->cont_item;
        if (strcmp(r->text, "second") == 0) item_second = r->cont_item;
        int blank = 1;
        for (const char *c = r->text; *c != '\0'; ++c)
            if (*c != ' ') { blank = 0; break; }
        assert_false(blank);   /* inter-block whitespace never crosses the wire */
    }
    assert_true(item_lead >= 0);
    assert_int_equal(item_lead, item_free);
    assert_int_equal(item_lead, item_tail);
    assert_true(item_second >= 0);
    assert_int_not_equal(item_second, item_lead);

    tab_page_free(&p);
    tab_close(t);
}

/* Stage 0 keystone: the document-order element id assigned by the child must
 * survive the IPC round-trip, so the parent can map a painted block back to the
 * worker's live DOM node. */
static void test_load_carries_node_id(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>N</title></head><body>"
        "<p id=\"first\">alpha</p>"
        "<p id=\"second\">beta</p></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.view);

    dom_node_id id_alpha = DOM_NODE_NONE, id_beta = DOM_NODE_NONE;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->text != NULL && strcmp(r->text, "alpha") == 0) {
            assert_int_not_equal(r->node_id, DOM_NODE_NONE);
            id_alpha = r->node_id;
        }
        if (r->text != NULL && strcmp(r->text, "beta") == 0) {
            assert_int_not_equal(r->node_id, DOM_NODE_NONE);
            id_beta = r->node_id;
        }
    }
    assert_int_not_equal(id_alpha, DOM_NODE_NONE);
    assert_int_not_equal(id_beta, DOM_NODE_NONE);
    assert_int_not_equal(id_alpha, id_beta);

    tab_page_free(&p);
    tab_close(t);
}

/* Stage 4 dispatcher: a click on a node with a JS handler mutates the DOM, and the
 * new view is returned over IPC with the mutation reflected. */
static void test_click_runs_handler_and_returns_view(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>C</title></head><body>"
        "<p id=\"target\">before</p>"
        "<script>document.getElementById('target').onclick = function(e){"
        "  document.getElementById('target').textContent = 'after';"
        "};</script></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);
    assert_non_null(p.view);

    dom_node_id target_id = DOM_NODE_NONE;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->text != NULL && strcmp(r->text, "before") == 0) {
            target_id = r->node_id;
        }
    }
    assert_int_not_equal(target_id, DOM_NODE_NONE);
    tab_page_free(&p);

    tab_page p2;
    assert_int_equal(tab_click(t, target_id, &p2), TAB_OK);
    assert_non_null(p2.view);

    int saw_after = 0;
    for (size_t i = 0; i < pv_count(p2.view); ++i) {
        const pv_run *r = pv_at(p2.view, i);
        if (r->text != NULL && strcmp(r->text, "after") == 0) saw_after = 1;
    }
    assert_true(saw_after);

    tab_page_free(&p2);
    tab_close(t);
}

static void test_event_ipc_via_tab_eval(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>E</title></head><body>"
        "<p id=\"status\">waiting</p>"
        "<input id=\"inp\" type=\"text\">"
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);
    assert_non_null(p.view);
    tab_page_free(&p);

    /* Get the input's DOM node_id from JS. */
    tab_eval_result er;
    const char *hjs = "document.getElementById('inp')._h";
    int er_st = tab_eval(t, hjs, strlen(hjs), &er);
    assert_int_equal(er_st, TAB_OK);
    assert_int_equal(er.is_exception, 0);
    dom_node_id h = (dom_node_id)strtoull(er.value, NULL, 10);
    assert_int_not_equal(h, DOM_NODE_NONE);
    tab_eval_result_free(&er);

    /* Register a keydown handler via tab_eval. */
    const char *register_js =
        "var i=document.getElementById('inp');"
        "i.addEventListener('keydown',function(e){"
        "  document.getElementById('status').textContent = e.key||'none';"
        "}); i._h;";
    assert_int_equal(tab_eval(t, register_js, strlen(register_js), &er), TAB_OK);
    assert_int_equal(er.is_exception, 0);
    dom_node_id h2 = (dom_node_id)strtoull(er.value, NULL, 10);
    assert_int_equal(h2, h);
    tab_eval_result_free(&er);

    /* Dispatch a keydown event on the input's DOM handle. */
    tab_page p2;
    tab_status st = tab_dispatch_event(t, h, "keydown", "Enter", 13, NULL, &p2);
    assert_int_equal(st, TAB_OK);
    assert_non_null(p2.view);

    /* Verify handler ran: status.textContent should now be "Enter". */
    int saw = 0;
    for (size_t i = 0; i < pv_count(p2.view); ++i) {
        const pv_run *r = pv_at(p2.view, i);
        if (r->text && strcmp(r->text, "Enter") == 0) { saw = 1; break; }
    }
    assert_true(saw);
    tab_page_free(&p2);
    tab_close(t);
}

/* Dispatches a mouse event (mouseover) via tab_dispatch_mouse and verifies the
 * handler fires and mutates the DOM. Covers the IPC round-trip. */
static void test_mouse_ipc_round_trip(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>M</title></head><body>"
        "<p id=\"status\">waiting</p>"
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);
    assert_non_null(p.view);
    tab_page_free(&p);

    /* Register a mouseover handler via tab_eval. */
    tab_eval_result er;
    const char *register_js =
        "var p=document.getElementById('status');"
        "p.addEventListener('mouseover',function(e){"
        "  p.textContent = 'over';"
        "}); p._h;";
    assert_int_equal(tab_eval(t, register_js, strlen(register_js), &er), TAB_OK);
    assert_int_equal(er.is_exception, 0);
    dom_node_id h = (dom_node_id)strtoull(er.value, NULL, 10);
    assert_int_not_equal(h, DOM_NODE_NONE);
    tab_eval_result_free(&er);

    /* Dispatch a mouseover event on the paragraph. */
    tab_page p2;
    tab_status st = tab_dispatch_mouse(t, h, "mouseover", 42, 73, 0, &p2);
    assert_int_equal(st, TAB_OK);
    assert_non_null(p2.view);

    /* Verify handler ran: status.textContent should now be "over". */
    int saw = 0;
    for (size_t i = 0; i < pv_count(p2.view); ++i) {
        const pv_run *r = pv_at(p2.view, i);
        if (r->text && strcmp(r->text, "over") == 0) { saw = 1; break; }
    }
    assert_true(saw);
    tab_page_free(&p2);
    tab_close(t);
}

/* Dispatches a focus event via tab_dispatch_event (OP_EVENT path) and verifies
 * the handler fires and mutates the DOM. Covers focus/blur/scroll via IPC. */
static void test_focus_ipc_round_trip(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>F</title></head><body>"
        "<input id=\"inp\" type=\"text\">"
        "<p id=\"status\">waiting</p>"
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);
    assert_non_null(p.view);
    tab_page_free(&p);

    /* Register a focus handler on the input via tab_eval. */
    tab_eval_result er;
    const char *register_js =
        "var i=document.getElementById('inp');"
        "i.addEventListener('focus',function(e){"
        "  document.getElementById('status').textContent = 'focused';"
        "}); i._h;";
    assert_int_equal(tab_eval(t, register_js, strlen(register_js), &er), TAB_OK);
    assert_int_equal(er.is_exception, 0);
    dom_node_id h = (dom_node_id)strtoull(er.value, NULL, 10);
    assert_int_not_equal(h, DOM_NODE_NONE);
    tab_eval_result_free(&er);

    /* Dispatch a focus event via tab_dispatch_event. */
    tab_page p2;
    tab_status st = tab_dispatch_event(t, h, "focus", NULL, 0, NULL, &p2);
    assert_int_equal(st, TAB_OK);
    assert_non_null(p2.view);

    int saw = 0;
    for (size_t i = 0; i < pv_count(p2.view); ++i) {
        const pv_run *r = pv_at(p2.view, i);
        if (r->text && strcmp(r->text, "focused") == 0) { saw = 1; break; }
    }
    assert_true(saw);
    tab_page_free(&p2);
    tab_close(t);
}

/* Real async timers (2026-07-11): a setTimeout with a delay does NOT fire on the
 * load pump; the load response reports the smallest pending delay; tab_tick
 * advances the virtual clock, fires it, and the refreshed view shows the
 * mutation. Intervals re-arm (next_timer_ms stays set). */
static void test_tick_fires_delayed_timer(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>T</title></head><body>"
        "<p id=\"t\">waiting</p>"
        "<script>setTimeout(function(){"
        "  document.getElementById('t').textContent = 'ticked';"
        "}, 100);</script></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);
    assert_non_null(p.view);
    /* the delayed timer did not fire on the pump and is reported pending */
    int saw_wait = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->text != NULL && strcmp(r->text, "waiting") == 0) saw_wait = 1;
    }
    assert_true(saw_wait);
    assert_int_equal(p.next_timer_ms, 100);
    tab_page_free(&p);

    tab_page p2;
    assert_int_equal(tab_tick(t, 100, &p2), TAB_OK);
    assert_non_null(p2.view);
    int saw_ticked = 0;
    for (size_t i = 0; i < pv_count(p2.view); ++i) {
        const pv_run *r = pv_at(p2.view, i);
        if (r->text != NULL && strcmp(r->text, "ticked") == 0) saw_ticked = 1;
    }
    assert_true(saw_ticked);
    assert_int_equal(p2.next_timer_ms, -1);   /* nothing pending anymore */
    tab_page_free(&p2);
    tab_close(t);
}

static void test_tick_interval_rearms(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>I</title></head><body>"
        "<p id=\"n\">0</p>"
        "<script>var c=0; setInterval(function(){"
        "  c++; document.getElementById('n').textContent = String(c);"
        "}, 50);</script></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);
    assert_int_equal(p.next_timer_ms, 50);
    tab_page_free(&p);

    tab_page p2;
    assert_int_equal(tab_tick(t, 50, &p2), TAB_OK);
    int saw_one = 0;
    for (size_t i = 0; i < pv_count(p2.view); ++i) {
        const pv_run *r = pv_at(p2.view, i);
        if (r->text != NULL && strcmp(r->text, "1") == 0) saw_one = 1;
    }
    assert_true(saw_one);
    assert_int_equal(p2.next_timer_ms, 50);   /* the interval re-armed */
    tab_page_free(&p2);
    tab_close(t);
}

/* Box-engine identity + decoration resolved in the confined child must survive the
 * IPC round-trip (write_view/read_view symmetry for the new fields). */
static void test_load_carries_box_decoration(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>B</title></head><body>"
        "<div style=\"border:2px solid #ff0000;padding:7px;"
        "box-sizing:border-box\">boxed</div></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.view);

    int saw = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->text != NULL && strcmp(r->text, "boxed") == 0) {
            assert_true(r->block_id >= 0);
            const pv_box_def *bx = pv_box_at(p.view, (size_t)r->block_id);
            assert_non_null(bx);
            assert_int_equal(bx->bord_tw, 2);
            assert_int_equal(bx->bord_tc, 0xff0000);
            assert_int_equal(bx->pad_t, 7);
            assert_int_equal(bx->pad_l, 7);
            assert_int_equal(bx->box_sizing, CSS_BOXS_BORDER);
            saw = 1;
        }
    }
    assert_true(saw);

    tab_page_free(&p);
    tab_close(t);
}

/* The box TREE (Step D) — the box-definition list with its parent links — must
 * survive the IPC round-trip: a nested box parsed in the confined child arrives with
 * its decoration on the box def and its parent_id pointing at the outer box. */
static void test_load_carries_box_tree(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>T</title></head><body>"
        "<div style=\"border:2px solid #ff0000;padding:8px\">"
        "<p>before</p>"
        "<div style=\"border:1px solid #0000ff\"><p>inner</p></div>"
        "<p>after</p>"
        "</div></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.view);

    const pv_run *before = NULL, *inner = NULL;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->text == NULL) continue;
        if (strcmp(r->text, "before") == 0) before = r;
        else if (strcmp(r->text, "inner") == 0) inner = r;
    }
    assert_non_null(before);
    assert_non_null(inner);
    assert_true(before->block_id >= 0);
    assert_int_not_equal(before->block_id, inner->block_id);
    assert_true(pv_box_count(p.view) >= 2);
    const pv_box_def *outer = pv_box_at(p.view, (size_t)before->block_id);
    const pv_box_def *inb = pv_box_at(p.view, (size_t)inner->block_id);
    assert_non_null(outer);
    assert_non_null(inb);
    assert_int_equal(outer->parent_id, -1);
    assert_int_equal(inb->parent_id, before->block_id);
    assert_int_equal(outer->bord_tw, 2);
    assert_int_equal(inb->bord_tw, 1);

    tab_page_free(&p);
    tab_close(t);
}

/* A form control parsed in the confined child must survive the IPC round-trip as a
 * PV_INPUT run carrying its type, name, value, the form action (on href) and the
 * form method (so the parent can paint and submit it). */
static void test_load_carries_form_control(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>F</title></head><body>"
        "<form action=\"https://s.example/q\" method=\"post\">"
        "<input type=\"text\" name=\"query\" value=\"seed\">"
        "<input type=\"submit\" value=\"Find\"></form></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.view);

    int saw_text = 0, saw_submit = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->kind != PV_INPUT) continue;
        if (r->name != NULL && strcmp(r->name, "query") == 0) {
            assert_int_equal(r->input_type, PV_IN_TEXT);
            assert_string_equal(r->value, "seed");
            assert_string_equal(r->href, "https://s.example/q");
            assert_int_equal(r->form_method, PV_METHOD_POST);
            assert_true(r->form_id >= 0);
            saw_text = 1;
        }
        if (r->input_type == PV_IN_SUBMIT && r->text != NULL
            && strcmp(r->text, "Find") == 0) {
            saw_submit = 1;
        }
    }
    assert_true(saw_text);
    assert_true(saw_submit);

    tab_page_free(&p);
    tab_close(t);
}

static void test_load_strips_script(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, HTML, sizeof HTML - 1, &p), TAB_OK);
    assert_null(strstr(p.text, "steal_cookies")); /* script body never inert text */
    tab_page_free(&p);
    tab_close(t);
}

/* Live JS (Hito 20b): with run_js, the page's inline script executes in the worker
 * and its DOM mutations (document.title, textContent) appear in the returned page. */
static void test_load_ex_runs_script_and_mutates(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>Old</title></head><body>"
        "<p id=\"out\">before</p>"
        "<script>document.title='New';"
        "document.getElementById('out').textContent='after';</script>"
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);
    /* title mutated by the script */
    assert_non_null(p.title);
    assert_string_equal(p.title, "New");
    /* textContent mutation visible in the rendered view */
    int saw_after = 0, saw_before = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const char *txt = pv_at(p.view, i)->text;
        if (txt != NULL && strcmp(txt, "after") == 0) saw_after = 1;
        if (txt != NULL && strcmp(txt, "before") == 0) saw_before = 1;
    }
    assert_true(saw_after);
    assert_false(saw_before);
    tab_page_free(&p);
    tab_close(t);
}

/* Session cookies (trusted host): the parent seeds document.cookie from its ephemeral
 * network jar (tab_set_cookies), the page's JS reads and sets cookies, and the worker
 * dumps the jar back (tab_page.set_cookies) for the parent to fold in. In-memory only. */
static void test_load_session_cookies_roundtrip(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>t</title></head><body>"
        "<script>document.title=document.cookie;document.cookie='newpref=42';</script>"
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_net_allowed(t, 1);                 /* trusted host (allow.conf AND js.conf) */
    tab_set_cookies(t, "sid=abc; theme=dark"); /* parent seeded from its network jar */
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://trusted.example/",
                                   1, 0, 0, &p), TAB_OK);
    /* the seed reached document.cookie inside the worker */
    assert_non_null(p.title);
    assert_non_null(strstr(p.title, "sid=abc"));
    /* the JS-set cookie (and the seed) come back for the parent to fold into its jar */
    assert_non_null(p.set_cookies);
    assert_non_null(strstr(p.set_cookies, "newpref=42"));
    assert_non_null(strstr(p.set_cookies, "sid=abc"));
    tab_page_free(&p);
    tab_close(t);
}

/* Untrusted host (net off): the cookie jar stays disabled -- document.cookie is '' even
 * if the parent were to seed it, and nothing is dumped back (Zero Knowledge default). */
static void test_load_no_session_cookies_when_untrusted(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>t</title></head><body>"
        "<script>document.title='['+document.cookie+']';document.cookie='x=1';</script>"
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_net_allowed(t, 0);                 /* untrusted */
    tab_set_cookies(t, "sid=abc");             /* ignored: jar stays disabled */
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://untrusted.example/",
                                   1, 0, 0, &p), TAB_OK);
    assert_non_null(p.title);
    assert_string_equal(p.title, "[]");        /* document.cookie is empty */
    assert_null(p.set_cookies);                /* nothing folded back */
    tab_page_free(&p);
    tab_close(t);
}

/* Live JS construction (Hito 20c): a script builds a node and an onload handler
 * mutates it; both must be reflected in the worker's returned view. */
static void test_load_ex_builds_dom_and_fires_onload(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>t</title></head><body><div id=\"root\"></div>"
        "<script>"
        "var s=document.createElement('p'); s.textContent='created';"
        "document.getElementById('root').appendChild(s);"
        "window.onload=function(){ var q=document.createElement('p');"
        "q.textContent='onloaded'; document.getElementById('root').appendChild(q); };"
        "</script></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);
    int saw_created = 0, saw_onloaded = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const char *txt = pv_at(p.view, i)->text;
        if (txt != NULL && strcmp(txt, "created") == 0) saw_created = 1;
        if (txt != NULL && strcmp(txt, "onloaded") == 0) saw_onloaded = 1;
    }
    assert_true(saw_created);   /* createElement+appendChild rendered */
    assert_true(saw_onloaded);  /* onload handler ran (synthetic pump) */
    tab_page_free(&p);
    tab_close(t);
}

/* innerHTML (Hito 20d): a script replaces a container's markup; the parsed content
 * renders, and ephemeral storage / empty cookie do not break the script. */
static void test_load_ex_inner_html_renders(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>t</title></head><body><div id=\"slot\">old</div>"
        "<script>localStorage.setItem('x','1');"
        "if(document.cookie===''){"
        "document.getElementById('slot').innerHTML='<b>NEWHTML</b>';}"
        "</script></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);
    int saw_new = 0, saw_old = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const char *txt = pv_at(p.view, i)->text;
        if (txt != NULL && strcmp(txt, "NEWHTML") == 0) saw_new = 1;
        if (txt != NULL && strcmp(txt, "old") == 0) saw_old = 1;
    }
    assert_true(saw_new);
    assert_false(saw_old);
    tab_page_free(&p);
    tab_close(t);
}

/* With JS off (the default tab_load), the same script does NOT run: title and text
 * are unchanged (Secure by Default). */
static void test_load_without_js_does_not_run_script(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>Old</title></head><body>"
        "<p id=\"out\">before</p>"
        "<script>document.title='New';"
        "document.getElementById('out').textContent='after';</script>"
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.title);
    assert_string_equal(p.title, "Old");
    int saw_before = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const char *txt = pv_at(p.view, i)->text;
        if (txt != NULL && strcmp(txt, "before") == 0) saw_before = 1;
    }
    assert_true(saw_before);
    tab_page_free(&p);
    tab_close(t);
}

/* Finds a console entry at the given level whose text contains needle. */
static const fb_entry *console_find(const fb_buffer *log, int level, const char *needle) {
    for (size_t i = 0; i < fb_buffer_count(log); ++i) {
        const fb_entry *e = fb_buffer_at(log, i);
        if (e != NULL && e->level == level && strstr(e->text, needle) != NULL) return e;
    }
    return NULL;
}

/* Freebug (FB-1): with run_js, the page's console.* output and any uncaught script
 * error are captured and delivered to the parent in tab_page.console. */
static void test_load_captures_console_and_error(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>t</title></head><body>"
        "<script>console.log('hi', 42); console.warn('careful'); nope_fn();</script>"
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);

    /* console.log args space-joined, captured as FB_LOG. */
    assert_non_null(console_find(&p.console, FB_LOG, "hi 42"));
    /* console.warn captured as FB_WARN. */
    assert_non_null(console_find(&p.console, FB_WARN, "careful"));
    /* The ReferenceError from nope_fn() surfaced as an FB_ERROR entry. */
    assert_non_null(console_find(&p.console, FB_ERROR, "nope_fn"));

    tab_page_free(&p);
    tab_close(t);
}

/* Per-script isolation (browser semantics): an uncaught error in the FIRST inline
 * <script> must NOT abort later scripts. Before this, all scripts were concatenated
 * into one eval, so the first throw killed every following script -- the root cause
 * of "loads nothing" on script-heavy pages (e.g. google.com). The first script's
 * error is still surfaced to the console; the second script still mutates the title. */
static void test_load_isolates_script_errors(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>Old</title></head><body>"
        "<script>throws_undefined_fn();</script>"            /* script #1: throws */
        "<script>document.title='SECOND_RAN';"               /* script #2: must run */
        "console.log('second ok');</script>"
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);

    /* Script #1's error was isolated and reported... */
    assert_non_null(console_find(&p.console, FB_ERROR, "throws_undefined_fn"));
    /* ...and script #2 still executed (title mutated + log emitted). */
    assert_non_null(p.title);
    assert_string_equal(p.title, "SECOND_RAN");
    assert_non_null(console_find(&p.console, FB_LOG, "second ok"));

    tab_page_free(&p);
    tab_close(t);
}

/* FB error locations (Hito 24): an uncaught error reports the inline script name
 * ("inline #N") plus the line and column of its throw site, carried across the IPC
 * pipe into tab_page.console. The 2nd inline script throws on its 2nd line so a
 * non-trivial line number is asserted. */
static void test_load_error_carries_location(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>t</title></head><body>"
        "<script>var ok=1;</script>"                       /* inline #1: clean */
        "<script>var a=2;\nnull.boom;</script>"             /* inline #2: throws on line 2 */
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);

    const fb_entry *e = console_find(&p.console, FB_ERROR, "TypeError");
    assert_non_null(e);
    assert_non_null(e->file);
    assert_string_equal(e->file, "inline #2");
    assert_int_equal(e->line, 2);
    assert_true(e->col > 0);

    tab_page_free(&p);
    tab_close(t);
}

/* Element-wrapper completeness (Hito 24): the exact google.com startup idioms that
 * previously threw -- dataset.X, hasAttribute, removeAttribute, src.substring -- now
 * run clean end-to-end through the worker. Title is set only if all four succeed. */
static void test_load_element_wrapper_idioms(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>old</title></head><body>"
        "<img id=\"m\" src=\"x.png\" data-ved=\"v1\">"
        "<script>"
        "var b=document.getElementById('m');"
        "var ved=b.dataset.ved;"                            /* was: 'ved' of undefined */
        "var has=b.hasAttribute('data-ved');"               /* was: not a function */
        "b.removeAttribute('id');"                          /* was: not a function */
        "var pre=b.src.substring(0,1);"                     /* was: 'substring' of undefined */
        "if(ved==='v1'&&has===true&&pre==='x') document.title='ALL_OK';"
        "</script></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);

    /* No error captured, and every idiom worked (title only set when all pass). */
    assert_null(console_find(&p.console, FB_ERROR, "TypeError"));
    assert_non_null(p.title);
    assert_string_equal(p.title, "ALL_OK");

    tab_page_free(&p);
    tab_close(t);
}

/* document.fonts stub: a feature-detecting script that calls document.fonts.load()/
 * .check() must not throw (this exact call -- document.fonts.load -- is what produced
 * google.com's "cannot read property 'load' of undefined"). The stub is benign. */
static void test_load_document_fonts_stub(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>t</title></head><body>"
        "<script>document.fonts.load('10pt X').catch(function(){});"
        "document.title = document.fonts.check('10pt X') ? 'FONTS_OK' : 'FONTS_BAD';"
        "</script></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK);
    /* No uncaught error, and the script ran to completion. */
    assert_int_equal((int)fb_buffer_count(&p.console), 0);
    assert_non_null(p.title);
    assert_string_equal(p.title, "FONTS_OK");
    tab_page_free(&p);
    tab_close(t);
}

/* Freebug (FB-1): a no-JS load runs no scripts, so the console is empty. */
static void test_load_without_js_has_empty_console(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>t</title></head><body>"
        "<script>console.log('should not run');</script></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_int_equal((int)fb_buffer_count(&p.console), 0);
    tab_page_free(&p);
    tab_close(t);
}

/* Freebug (FB-1): the REPL (tab_eval) returns the value AND the console output the
 * evaluation produced, each eval reporting only its own transcript. */
static void test_eval_captures_console_output(void **state) {
    (void)state;
    static const char H[] = "<html><body><p>x</p></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    tab_page_free(&p);

    tab_eval_result r;
    assert_int_equal(tab_eval(t, "console.log('repl', 2+2); 7", 27, &r), TAB_OK);
    assert_int_equal(r.is_exception, 0);
    assert_string_equal(r.value, "7");
    assert_int_equal((int)fb_buffer_count(&r.console), 1);
    assert_int_equal(fb_buffer_at(&r.console, 0)->level, FB_LOG);
    assert_string_equal(fb_buffer_at(&r.console, 0)->text, "repl 4");
    tab_eval_result_free(&r);

    /* A second eval reports only ITS own console, not the first eval's. */
    assert_int_equal(tab_eval(t, "1+1", 3, &r), TAB_OK);
    assert_string_equal(r.value, "2");
    assert_int_equal((int)fb_buffer_count(&r.console), 0);
    tab_eval_result_free(&r);

    tab_close(t);
}

/* Real location (Hito 20e): the page URL passed to tab_load_full backs a real
 * location object the page's JS can read (no scripts need run for the read). */
static void test_load_full_location_is_real(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>t</title></head><body><p>x</p></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1,
                                   "https://example.com:8443/a/b?q=1#h",
                                   0, 0, 0, &p), TAB_OK);
    tab_page_free(&p);
    expect_eval(t, "location.hostname", "example.com");
    expect_eval(t, "location.port", "8443");
    expect_eval(t, "location.pathname", "/a/b");
    expect_eval(t, "location.protocol", "https:");
    tab_close(t);
}

/* JS navigation (Hito 20e): an allowlisted inline script setting location.href is
 * reported as a gated nav_url (resolved against the page URL by the trusted parent). */
static void test_js_navigation_absolute(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>t</title></head><body>"
        "<script>location.href='https://example.org/landing';</script></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://example.com/",
                                   1, 0, 0, &p), TAB_OK);
    assert_non_null(p.nav_url);
    assert_string_equal(p.nav_url, "https://example.org/landing");
    assert_int_equal(p.nav_replace, 0);
    tab_page_free(&p);
    tab_close(t);
}

static void test_js_navigation_relative_resolved(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>t</title></head><body>"
        "<script>location.replace('/c');</script></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://example.com/a/b",
                                   1, 0, 0, &p), TAB_OK);
    assert_non_null(p.nav_url);
    assert_string_equal(p.nav_url, "https://example.com/c"); /* resolved by parent */
    assert_int_equal(p.nav_replace, 1);                      /* location.replace */
    tab_page_free(&p);
    tab_close(t);
}

/* Fail-closed gate: the parent rejects a downgrade / foreign-scheme / fragment nav,
 * so a hostile or compromised worker cannot drive the browser off-policy. */
static void test_js_navigation_unsafe_is_blocked(void **state) {
    (void)state;
    static const char DOWNGRADE[] =
        "<html><body><script>location.href='http://evil.test/';</script></body></html>";
    static const char FOREIGN[] =
        "<html><body><script>location.href='javascript:alert(1)';</script></body></html>";
    static const char FRAGMENT[] =
        "<html><body><script>location.href='#section';</script></body></html>";
    const char *cases[] = { DOWNGRADE, FOREIGN, FRAGMENT };
    for (size_t i = 0; i < 3; ++i) {
        tab *t = NULL;
        assert_int_equal(tab_open(&t), TAB_OK);
        tab_page p;
        assert_int_equal(tab_load_full(t, cases[i], strlen(cases[i]),
                                       "https://example.com/", 1, 0, 0, &p), TAB_OK);
        assert_true(p.nav_url == NULL || p.nav_url[0] == '\0'); /* no navigation */
        tab_page_free(&p);
        tab_close(t);
    }
}

/* With JS off the navigating script never runs: no nav request (Secure by Default). */
static void test_no_js_no_navigation(void **state) {
    (void)state;
    static const char H[] =
        "<html><body><script>location.href='https://example.org/';</script></body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://example.com/",
                                   0, 0, 0, &p), TAB_OK);
    assert_true(p.nav_url == NULL || p.nav_url[0] == '\0');
    tab_page_free(&p);
    tab_close(t);
}

static void test_load_null_and_too_large(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(NULL, HTML, 4, &p), TAB_ERR_NULL_ARG);
    assert_int_equal(tab_load(t, HTML, 4, NULL), TAB_ERR_NULL_ARG);
    assert_int_equal(tab_load(t, NULL, 4, &p), TAB_ERR_NULL_ARG);
    /* Length cap checked in the parent before any IPC; child stays alive. */
    assert_int_equal(tab_load(t, "x", TAB_MAX_INPUT + 1, &p), TAB_ERR_TOO_LARGE);
    assert_true(tab_alive(t));
    tab_close(t);
}

/* --- eval: sees the DOM bound in the child --- */

static void test_eval_sees_dom(void **state) {
    fixture *f = (fixture *)*state;
    expect_eval(f->t, "dom.nodeCount() > 0", "true");
    expect_eval(f->t, "dom.getElementById('main') !== null", "true");
    expect_eval(f->t, "dom.tagName(dom.getElementById('main'))", "div");
    expect_eval(f->t, "dom.getAttribute(dom.getElementById('main'),'class')", "box");
}

/* --- eval: sees the normalized anti-fp environment --- */

static void test_eval_sees_env(void **state) {
    fixture *f = (fixture *)*state;
    expect_eval(f->t, "navigator.language", "en-US");
    expect_eval(f->t, "navigator.userAgent.indexOf('Firefox') >= 0", "true");
    expect_eval(f->t, "screen.width === 1920 && screen.height === 1080", "true");
    expect_eval(f->t, "Date.now() % 100", "0");
    expect_eval(f->t, "typeof canvas.readback", "function");
}

/* SOP/CORS confidentiality (gap audit #2): the JS sandbox exposes NO way to make a
 * network request or open a cross-origin browsing context, so it can never READ
 * cross-origin data -- the canonical CORS threat (reading a cross-origin response)
 * is structurally absent, on top of the worker having no network at all (CLONE_NEWNET
 * + seccomp blocks socket/connect). document.cookie is present but empty (Zero
 * Knowledge), so there is nothing to exfiltrate even via the page's own loads. If a
 * future change adds a fetch-like API, this test fires and forces same-origin/CORS
 * enforcement to be added alongside it. */
static void test_eval_no_network_or_cross_origin_api(void **state) {
    fixture *f = (fixture *)*state;
    expect_eval(f->t, "typeof fetch", "undefined");
    expect_eval(f->t, "typeof XMLHttpRequest", "undefined");
    expect_eval(f->t, "typeof WebSocket", "undefined");
    expect_eval(f->t, "typeof EventSource", "undefined");
    expect_eval(f->t, "typeof navigator.sendBeacon", "undefined");
    expect_eval(f->t, "typeof importScripts", "undefined");
    expect_eval(f->t, "typeof Image", "undefined");
    expect_eval(f->t, "typeof postMessage", "undefined");
    expect_eval(f->t, "typeof open", "undefined");          /* no window.open / new window */
    expect_eval(f->t, "typeof document.cookie", "string");  /* present but... */
    expect_eval(f->t, "document.cookie", "");               /* ...empty: nothing to steal */
}

/* --- XMLHttpRequest / fetch: parent-gated network (allow.conf AND js.conf) --- */

/* Stub parent fetcher: returns a fixed 200/"PONG" body, but REFUSES any "blocked.example"
 * host -- standing in for the real parent's hostblock/realm/TLS policy. */
static int stub_fetch(void *ctx, const char *method, const char *url,
                      const char *body, size_t body_len,
                      int *st, char **ob, size_t *ol, char **oct) {
    (void)ctx; (void)method; (void)body; (void)body_len;
    if (url == NULL || strstr(url, "blocked.example") != NULL) return -1; /* policy refusal */
    *ob = strdup("PONG"); *ol = 4;
    *oct = strdup("text/plain");
    if (*ob == NULL || *oct == NULL) { free(*ob); free(*oct); return -1; }
    *st = 200;
    return 0;
}

#define XHR_PAGE(URL) \
    "<!DOCTYPE html><html><head><title>x</title></head><body><script>" \
    "var x=new XMLHttpRequest();x.open('GET','" URL "');x.send();" \
    "document.title=x.status+':'+x.responseText;</script></body></html>"

/* With net allowed (host in allow.conf AND js.conf) the page's XHR reaches the parent
 * fetcher and the response is visible to script. */
static void test_xhr_works_when_net_allowed(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_fetcher(t, stub_fetch, NULL);
    tab_set_net_allowed(t, 1);
    static const char H[] = XHR_PAGE("https://api.test/d");
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://api.test/", 1, 0, 0, &p), TAB_OK);
    assert_non_null(p.title);
    assert_string_equal(p.title, "200:PONG");  /* the XHR body reached the script */
    tab_page_free(&p);
    expect_eval(t, "typeof XMLHttpRequest", "function");
    expect_eval(t, "typeof fetch", "function");
    tab_close(t);
}

/* Default (net not allowed): XHR/fetch stay undefined -- Same-Origin-by-construction holds
 * for every site not in BOTH lists. The script's `new XMLHttpRequest` throws, so the title
 * is never reassigned. */
static void test_xhr_undefined_when_net_not_allowed(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_fetcher(t, stub_fetch, NULL);
    /* net_allowed left at its default (0) */
    static const char H[] = XHR_PAGE("https://api.test/d");
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://api.test/", 1, 0, 0, &p), TAB_OK);
    assert_non_null(p.title);
    assert_string_equal(p.title, "x");          /* script threw: title unchanged */
    tab_page_free(&p);
    expect_eval(t, "typeof XMLHttpRequest", "undefined");
    expect_eval(t, "typeof fetch", "undefined");
    tab_close(t);
}

/* Even with net allowed, the trusted parent refuses a blocked host: the XHR completes with
 * status 0 and an empty body (fail-closed). Proves the gate is the PARENT's, not the page's. */
static void test_xhr_blocked_host_refused_by_parent(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_fetcher(t, stub_fetch, NULL);
    tab_set_net_allowed(t, 1);
    static const char H[] = XHR_PAGE("https://blocked.example/track");
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://api.test/", 1, 0, 0, &p), TAB_OK);
    assert_non_null(p.title);
    assert_string_equal(p.title, "0:");         /* refused: status 0, empty body */
    tab_page_free(&p);
    tab_close(t);
}

/* --- external <script src> (Hito 24 EXT): parent-gated fetch + document order --- */

/* Stub parent fetcher for external scripts: serves JS bodies by URL with a proper
 * JavaScript Content-Type; refuses "blocked.example" (standing in for the parent's
 * policy) and serves one URL with a NON-JS Content-Type (type-confusion guard). */
static int stub_script_fetch(void *ctx, const char *method, const char *url,
                             const char *body, size_t body_len,
                             int *st, char **ob, size_t *ol, char **oct) {
    (void)ctx; (void)body; (void)body_len;
    if (url == NULL || strstr(url, "blocked.example") != NULL) return -1;
    if (method == NULL || strcmp(method, "GET") != 0) return -1;
    const char *js = NULL, *ct = "text/javascript; charset=UTF-8";
    if (strstr(url, "set-title.js") != NULL) {
        js = "document.title='EXT-RAN';";
    } else if (strstr(url, "mid.js") != NULL) {
        js = "mark+='B';";
    } else if (strstr(url, "html-not-js") != NULL) {
        js = "document.title='EVIL';";
        ct = "text/html";                       /* wrong type: must NOT execute */
    } else {
        return -1;
    }
    *ob = strdup(js); *ol = strlen(js);
    *oct = strdup(ct);
    if (*ob == NULL || *oct == NULL) { free(*ob); free(*oct); return -1; }
    *st = 200;
    return 0;
}

#define EXT_PAGE(SRC) \
    "<!DOCTYPE html><html><head><title>x</title></head><body>" \
    "<script src='" SRC "'></script></body></html>"

/* With net granted (allow.conf AND js.conf) an external script's bytes come from the
 * trusted parent and execute: its DOM mutation is visible in the page result. */
static void test_external_script_executes_when_net_allowed(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_fetcher(t, stub_script_fetch, NULL);
    tab_set_net_allowed(t, 1);
    static const char H[] = EXT_PAGE("https://cdn.test/set-title.js");
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://site.test/", 1, 0, 0, &p), TAB_OK);
    assert_non_null(p.title);
    assert_string_equal(p.title, "EXT-RAN");
    tab_page_free(&p);
    tab_close(t);
}

/* External scripts execute IN DOCUMENT ORDER interleaved with inline ones: a later
 * inline script sees the external script's effects (exactly as a browser). */
static void test_external_script_document_order(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_fetcher(t, stub_script_fetch, NULL);
    tab_set_net_allowed(t, 1);
    static const char H[] =
        "<!DOCTYPE html><html><head><title>x</title></head><body>"
        "<script>var mark='A';</script>"
        "<script src='https://cdn.test/mid.js'></script>"
        "<script>document.title=mark+'C';</script>"
        "</body></html>";
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://site.test/", 1, 0, 0, &p), TAB_OK);
    assert_non_null(p.title);
    assert_string_equal(p.title, "ABC");
    tab_page_free(&p);
    tab_close(t);
}

/* Without the network grant an external script is SKIPPED (never fetched, never run):
 * the page still loads and a Freebug warn entry records the skip. The "external src
 * never runs" doctrine still holds for every host not in BOTH lists. */
static void test_external_script_skipped_without_net(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_fetcher(t, stub_script_fetch, NULL);
    /* net_allowed left at its default (0) */
    static const char H[] = EXT_PAGE("https://cdn.test/set-title.js");
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://site.test/", 1, 0, 0, &p), TAB_OK);
    assert_non_null(p.title);
    assert_string_equal(p.title, "x");          /* external script never ran */
    int warned = 0;
    for (size_t i = 0; i < fb_buffer_count(&p.console); i++) {
        const fb_entry *e = fb_buffer_at(&p.console, i);
        if (e != NULL && e->level == FB_WARN && strstr(e->text, "external script") != NULL)
            warned = 1;
    }
    assert_int_not_equal(warned, 0);
    tab_page_free(&p);
    tab_close(t);
}

/* A response that is not JavaScript (e.g. an HTML error page) is NOT executed
 * (type-confusion guard, fail closed); the page still loads. */
static void test_external_script_bad_ctype_not_executed(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_fetcher(t, stub_script_fetch, NULL);
    tab_set_net_allowed(t, 1);
    static const char H[] = EXT_PAGE("https://cdn.test/html-not-js");
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://site.test/", 1, 0, 0, &p), TAB_OK);
    assert_non_null(p.title);
    assert_string_equal(p.title, "x");          /* body refused: never evaluated */
    tab_page_free(&p);
    tab_close(t);
}

/* Even with net granted, the trusted parent's refusal (blocked host) means the script
 * never runs -- the gate is the PARENT's policy, not the page's. */
static void test_external_script_blocked_host_refused(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_fetcher(t, stub_script_fetch, NULL);
    tab_set_net_allowed(t, 1);
    static const char H[] = EXT_PAGE("https://blocked.example/x.js");
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://site.test/", 1, 0, 0, &p), TAB_OK);
    assert_non_null(p.title);
    assert_string_equal(p.title, "x");
    tab_page_free(&p);
    tab_close(t);
}

/* --- external stylesheets (Hito 27): parent-gated, worker never touches a socket --- */

/* Observed subresource calls, reset per test: proves "no grant => zero fetches". */
static int g_css_fetch_calls;

/* Stub parent fetcher for stylesheets: serves CSS bodies by URL with a text/css
 * Content-Type; refuses "blocked.example" (standing in for the parent's policy) and
 * serves one URL with a NON-CSS Content-Type (type-confusion guard). */
static int stub_css_fetch(void *ctx, const char *method, const char *url,
                          const char *body, size_t body_len,
                          int *st, char **ob, size_t *ol, char **oct) {
    (void)ctx; (void)body; (void)body_len;
    g_css_fetch_calls++;
    if (url == NULL || strstr(url, "blocked.example") != NULL) return -1;
    if (method == NULL || strcmp(method, "GET") != 0) return -1;
    const char *css = "p{text-align:center}", *ct = "text/css";
    if (strstr(url, "html-not-css") != NULL) ct = "text/html"; /* must NOT parse */
    else if (strstr(url, "center.css") == NULL) return -1;
    *ob = strdup(css); *ol = strlen(css);
    *oct = strdup(ct);
    if (*ob == NULL || *oct == NULL) { free(*ob); free(*oct); return -1; }
    *st = 200;
    return 0;
}

#define CSS_PAGE(HREF) \
    "<!DOCTYPE html><html><head><title>x</title>" \
    "<link rel='stylesheet' href='" HREF "'></head>" \
    "<body><p>styled</p></body></html>"

static const pv_run *view_find_text(const pv_view *v, const char *needle) {
    if (v == NULL) return NULL;
    for (size_t i = 0; i < pv_count(v); ++i) {
        const pv_run *r = pv_at(v, i);
        if (r->text != NULL && strstr(r->text, needle) != NULL) return r;
    }
    return NULL;
}

/* With the css grant, the <link rel=stylesheet> bytes come from the trusted parent
 * and feed the author-CSS cascade -- no JS required (run_js == 0). */
static void test_external_css_applied_when_allowed(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_fetcher(t, stub_css_fetch, NULL);
    tab_set_css_allowed(t, 1);
    g_css_fetch_calls = 0;
    static const char H[] = CSS_PAGE("https://cdn.test/center.css");
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://site.test/", 0, 0, 0, &p), TAB_OK);
    const pv_run *r = view_find_text(p.view, "styled");
    assert_non_null(r);
    assert_int_equal(r->text_align, CSS_ALIGN_CENTER);
    assert_int_equal(g_css_fetch_calls, 1);
    tab_page_free(&p);
    tab_close(t);
}

/* Default (no grant): zero subresource requests and no external styling --
 * Privacy by Default holds, byte-identical to the pre-Hito-27 view. */
static void test_external_css_skipped_without_grant(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_fetcher(t, stub_css_fetch, NULL);
    g_css_fetch_calls = 0;
    static const char H[] = CSS_PAGE("https://cdn.test/center.css");
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://site.test/", 0, 0, 0, &p), TAB_OK);
    const pv_run *r = view_find_text(p.view, "styled");
    assert_non_null(r);
    assert_int_equal(r->text_align, CSS_ALIGN_UNSET);
    assert_int_equal(g_css_fetch_calls, 0);
    tab_page_free(&p);
    tab_close(t);
}

/* A non-CSS Content-Type (an HTML 404 page, a script) is never parsed as a sheet
 * (anti type-confusion, fail closed); the load continues unstyled. */
static void test_external_css_bad_ctype_not_parsed(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_fetcher(t, stub_css_fetch, NULL);
    tab_set_css_allowed(t, 1);
    static const char H[] = CSS_PAGE("https://cdn.test/html-not-css");
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://site.test/", 0, 0, 0, &p), TAB_OK);
    const pv_run *r = view_find_text(p.view, "styled");
    assert_non_null(r);
    assert_int_equal(r->text_align, CSS_ALIGN_UNSET);
    tab_page_free(&p);
    tab_close(t);
}

/* The parent's policy refusal (blocked host) degrades to "no sheet", never a
 * failed load: presentation is fail-open like hostblock, the page stays usable. */
static void test_external_css_blocked_host_refused(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_fetcher(t, stub_css_fetch, NULL);
    tab_set_css_allowed(t, 1);
    static const char H[] = CSS_PAGE("https://blocked.example/e.css");
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://site.test/", 0, 0, 0, &p), TAB_OK);
    const pv_run *r = view_find_text(p.view, "styled");
    assert_non_null(r);
    assert_int_equal(r->text_align, CSS_ALIGN_UNSET);
    tab_page_free(&p);
    tab_close(t);
}

/* The fetched sheet PERSISTS in the worker: a click re-derives the view (OP_CLICK)
 * and the styling survives without a re-fetch. */
static void test_external_css_survives_click_rederive(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_set_fetcher(t, stub_css_fetch, NULL);
    tab_set_css_allowed(t, 1);
    g_css_fetch_calls = 0;
    static const char H[] = CSS_PAGE("https://cdn.test/center.css");
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://site.test/", 0, 0, 0, &p), TAB_OK);
    const pv_run *r = view_find_text(p.view, "styled");
    assert_non_null(r);
    dom_node_id nid = r->node_id;
    tab_page_free(&p);

    tab_page c;
    assert_int_equal(tab_click(t, nid, &c), TAB_OK);
    const pv_run *rc = view_find_text(c.view, "styled");
    assert_non_null(rc);
    assert_int_equal(rc->text_align, CSS_ALIGN_CENTER); /* no re-fetch needed */
    assert_int_equal(g_css_fetch_calls, 1);             /* still just the load's fetch */
    tab_page_free(&c);
    tab_close(t);
}

/* Pure parent-side subresource gate (Zero Trust: the parent decides from ITS flags,
 * never the worker's): net grants any well-formed method, css-only grants exactly
 * "GET", nothing granted (or a malformed method) is refused. */
static void test_subreq_permitted_pure(void **state) {
    (void)state;
    assert_true(tab_subreq_permitted(1, 0, "GET"));
    assert_true(tab_subreq_permitted(1, 0, "POST"));
    assert_true(tab_subreq_permitted(1, 1, "POST"));
    assert_true(tab_subreq_permitted(0, 1, "GET"));
    assert_false(tab_subreq_permitted(0, 1, "POST"));
    assert_false(tab_subreq_permitted(0, 1, "get"));  /* exact token only: fail closed */
    assert_false(tab_subreq_permitted(0, 1, "GET "));
    assert_false(tab_subreq_permitted(0, 0, "GET"));
    assert_false(tab_subreq_permitted(0, 0, "POST"));
    assert_false(tab_subreq_permitted(1, 1, NULL));   /* malformed: always refused */
    assert_false(tab_subreq_permitted(1, 1, ""));
    assert_false(tab_subreq_permitted(0, 1, NULL));
}

/* --- Date/timezone: normalized to UTC inside the worker (anti-fp + no openat) --- */

/* Page JS calling Date.getTimezoneOffset() must (a) not kill the worker -- with TZ
 * unset, glibc's lazy localtime_r openat()s /etc/localtime, which seccomp rightly
 * kills -- and (b) always see UTC (offset 0): the host timezone is a fingerprinting
 * vector no page may read (Zero Knowledge). Google's real JS hit exactly this. */
static void test_js_date_timezone_is_utc_and_survives(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    static const char H[] =
        "<!DOCTYPE html><html><head><title>x</title></head><body>"
        "<script>document.title = 'tz:' + new Date(0).getTimezoneOffset()"
        " + ':' + new Date(1e12).getTimezoneOffset();</script>"
        "</body></html>";
    tab_page p;
    assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://site.test/", 1, 0, 0, &p), TAB_OK);
    assert_non_null(p.title);
    assert_string_equal(p.title, "tz:0:0");    /* UTC, and the worker lived to say so */
    tab_page_free(&p);
    assert_int_not_equal(tab_alive(t), 0);
    tab_close(t);
}

/* --- eval: a JS exception is TAB_OK with is_exception set, not a worker error --- */

static void test_eval_exception(void **state) {
    fixture *f = (fixture *)*state;
    tab_eval_result r;
    assert_int_equal(tab_eval(f->t, "throw new Error('boom')", 23, &r), TAB_OK);
    assert_int_not_equal(r.is_exception, 0);
    assert_non_null(r.value);
    assert_non_null(strstr(r.value, "boom"));
    tab_eval_result_free(&r);
}

/* --- eval: state persists across calls within the same worker --- */

static void test_eval_persistent_state(void **state) {
    fixture *f = (fixture *)*state;
    expect_eval(f->t, "globalThis.counter = 41", "41");
    expect_eval(f->t, "++globalThis.counter", "42");
    expect_eval(f->t, "globalThis.counter", "42");
}

/* --- a second load replaces the page; eval sees the new DOM --- */

static void test_reload_replaces_page(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);

    tab_page p;
    assert_int_equal(tab_load(t, HTML, sizeof HTML - 1, &p), TAB_OK);
    tab_page_free(&p);
    expect_eval(t, "dom.getElementById('main') !== null", "true");

    static const char HTML2[] =
        "<!DOCTYPE html><html><head><title>Second</title></head>"
        "<body><span id=\"other\">x</span></body></html>";
    assert_int_equal(tab_load(t, HTML2, sizeof HTML2 - 1, &p), TAB_OK);
    assert_string_equal(p.title, "Second");
    tab_page_free(&p);
    expect_eval(t, "dom.getElementById('other') !== null", "true");
    expect_eval(t, "dom.getElementById('main') === null", "true"); /* old node gone */

    tab_close(t);
}

/* --- eval before any load is a worker error, not a crash --- */

static void test_eval_without_load(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_eval_result r;
    assert_int_equal(tab_eval(t, "1+1", 3, &r), TAB_ERR_SCRIPT);
    assert_true(tab_alive(t));
    tab_close(t);
}

/* --- the parent must survive arbitrary/binary input: isolation in action --- */

static void test_binary_does_not_crash_parent(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    uint8_t junk[1024];
    for (size_t i = 0; i < sizeof junk; ++i) junk[i] = (uint8_t)(i * 37 + 11);
    tab_page p;
    tab_status s = tab_load(t, (const char *)junk, sizeof junk, &p);
    assert_true(s == TAB_OK || s == TAB_ERR_RENDER || s == TAB_ERR_DEAD);
    tab_page_free(&p);
    tab_close(t);
}

/* --- killing the child: the parent survives, reports TAB_ERR_DEAD --- */

static void test_child_death_survived(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, HTML, sizeof HTML - 1, &p), TAB_OK);
    tab_page_free(&p);

    pid_t pid = tab_child_pid(t);
    assert_true(pid > 0);
    assert_int_equal(kill(pid, SIGKILL), 0);

    /* Give the kernel a moment to deliver the signal and reap-on-read. */
    struct timespec ts = { 0, 50 * 1000 * 1000 };
    nanosleep(&ts, NULL);

    tab_eval_result r;
    tab_status s = tab_eval(t, "1+1", 3, &r);
    assert_int_equal(s, TAB_ERR_DEAD); /* parent did not die with the child */
    tab_eval_result_free(&r);
    assert_false(tab_alive(t));
    tab_close(t);
}

/* --- releasers are NULL-safe and idempotent --- */

static void test_free_null_and_double(void **state) {
    (void)state;
    tab_close(NULL);
    tab_page_free(NULL);
    tab_eval_result_free(NULL);

    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, HTML, sizeof HTML - 1, &p), TAB_OK);
    tab_page_free(&p);
    tab_page_free(&p); /* idempotent */

    tab_eval_result r;
    assert_int_equal(tab_eval(t, "1+1", 3, &r), TAB_OK);
    tab_eval_result_free(&r);
    tab_eval_result_free(&r); /* idempotent */
    tab_close(t);
}

/* --- image decode runs inside the confined worker --- */

/* The same 2x2 RGBA PNG used by test_image_decode (see that file for the pixel
 * map). Decoding it here proves libpng works under the worker's seccomp allowlist. */
static const uint8_t PNG_2x2[] = {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x72, 0xb6, 0x0d, 0x24, 0x00, 0x00, 0x00,
    0x13, 0x49, 0x44, 0x41, 0x54, 0x78, 0xda, 0x63, 0xf8, 0xcf, 0xc0, 0xf0,
    0x1f, 0x0c, 0x81, 0x34, 0x08, 0x34, 0x00, 0x00, 0x49, 0x49, 0x09, 0x78,
    0x9c, 0x51, 0x17, 0x92, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44,
    0xae, 0x42, 0x60, 0x82
};

static void test_decode_image_in_sandbox(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);

    tab_image img;
    assert_int_equal(tab_decode_image(t, PNG_2x2, sizeof PNG_2x2, &img), TAB_OK);
    assert_non_null(img.data);
    assert_int_equal(img.width, 2);
    assert_int_equal(img.height, 2);
    assert_int_equal(img.stride, 2u * 4u);
    assert_int_equal(img.data_len, 2u * 4u * 2u);
    /* (0,0) is premultiplied ARGB32 red opaque: B,G,R,A = 0,0,255,255. */
    assert_int_equal(img.data[0], 0x00);
    assert_int_equal(img.data[1], 0x00);
    assert_int_equal(img.data[2], 0xff);
    assert_int_equal(img.data[3], 0xff);
    tab_image_free(&img);
    tab_image_free(&img); /* idempotent */
    tab_close(t);
}

static void test_decode_image_rejects_junk(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);

    const uint8_t junk[32] = {0};
    tab_image img;
    /* Transport succeeds; the worker simply could not decode -> data == NULL. */
    assert_int_equal(tab_decode_image(t, junk, sizeof junk, &img), TAB_OK);
    assert_null(img.data);
    assert_int_equal(img.width, 0);
    tab_image_free(&img);
    tab_close(t);
}

static void test_decode_image_null_args(void **state) {
    (void)state;
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_image img;
    assert_int_equal(tab_decode_image(t, NULL, 4, &img), TAB_ERR_NULL_ARG);
    assert_int_equal(tab_decode_image(NULL, PNG_2x2, sizeof PNG_2x2, &img), TAB_ERR_NULL_ARG);
    assert_int_equal(tab_decode_image(t, PNG_2x2, sizeof PNG_2x2, NULL), TAB_ERR_NULL_ARG);
    tab_image_free(NULL);
    tab_close(t);
}

/* --- pure: worker-handoff argument validation (the exec security surface) --- */

static void test_worker_args_valid(void **state) {
    (void)state;
    const char *argv[] = { "freedom", "--tab-worker", "3", "4", NULL };
    int rfd = -1, wfd = -1;
    assert_true(tab_parse_worker_args(4, argv, &rfd, &wfd));
    assert_int_equal(rfd, 3);
    assert_int_equal(wfd, 4);
}

static void test_worker_args_not_worker(void **state) {
    (void)state;
    const char *argv[] = { "freedom", "https://example.com", NULL };
    int rfd = -1, wfd = -1;
    assert_false(tab_parse_worker_args(2, argv, &rfd, &wfd));
}

static void test_worker_args_malformed(void **state) {
    (void)state;
    int rfd = 0, wfd = 0;
    const char *missing[]  = { "freedom", "--tab-worker", "3", NULL };            /* too few */
    const char *nonnum[]   = { "freedom", "--tab-worker", "3", "x4", NULL };      /* not a number */
    const char *negative[] = { "freedom", "--tab-worker", "-3", "4", NULL };      /* leading '-' */
    const char *huge[]     = { "freedom", "--tab-worker", "3", "99999999", NULL };/* absurd fd */
    const char *empty[]    = { "freedom", "--tab-worker", "", "4", NULL };        /* empty token */
    assert_false(tab_parse_worker_args(3, missing, &rfd, &wfd));
    assert_false(tab_parse_worker_args(4, nonnum, &rfd, &wfd));
    assert_false(tab_parse_worker_args(4, negative, &rfd, &wfd));
    assert_false(tab_parse_worker_args(4, huge, &rfd, &wfd));
    assert_false(tab_parse_worker_args(4, empty, &rfd, &wfd));
}

static void test_worker_args_null_safe(void **state) {
    (void)state;
    int rfd = 0, wfd = 0;
    const char *argv[] = { "freedom", "--tab-worker", "3", "4", NULL };
    assert_false(tab_parse_worker_args(4, NULL, &rfd, &wfd));
    assert_false(tab_parse_worker_args(4, argv, NULL, &wfd));
    assert_false(tab_parse_worker_args(4, argv, &rfd, NULL));
    assert_false(tab_parse_worker_args(0, argv, &rfd, &wfd));
}

/* M0.2 codec golden: one load packs a broad spread of run + box fields across BOTH
 * fixed-width run blocks (block A: image/color/text-presentation/container; block B:
 * flex/box-model/input) and the box-def array, with distinctive numeric values. A wire
 * desync in write_view/read_view (a swapped or dropped field) surfaces here as a value
 * read into the wrong slot. Locks the bulk-array refactor: it passes identically before
 * and after, because the wire bytes are unchanged. */
static void test_load_view_codec_full_roundtrip(void **state) {
    (void)state;
    static const char H[] =
        "<html><head><title>C</title></head><body>"
        "<p style=\"color:#112233;background-color:#445566;font-size:150%;"
        "line-height:180%;text-indent:13px;tab-size:4;opacity:0.5;"
        "margin-left:11px;max-width:222px\">alpha</p>"
        "<img src=\"https://e.example/i.png\" width=\"40\" height=\"20\" alt=\"pic\">"
        "<div style=\"display:grid;grid-template-columns:100px 1fr\">"
        "<span style=\"grid-column:span 2\">grid</span></div>"
        "<div style=\"display:flex\"><span style=\"flex:2 0 auto\">flexi</span></div>"
        "<div style=\"border-radius:8px;position:relative;z-index:5;height:77px;"
        "opacity:0.5;mix-blend-mode:multiply;isolation:isolate\">boxy</div>"
        "<form method=\"post\"><input type=\"checkbox\" checked=\"checked\"></form>"
        "</body></html>";
    tab *t = NULL;
    assert_int_equal(tab_open(&t), TAB_OK);
    tab_page p;
    assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK);
    assert_non_null(p.view);

    int saw_alpha = 0, saw_pic = 0, saw_grid = 0, saw_flexi = 0, saw_boxy = 0, saw_input = 0;
    for (size_t i = 0; i < pv_count(p.view); ++i) {
        const pv_run *r = pv_at(p.view, i);
        if (r->kind == PV_IMAGE) {
            assert_int_equal(r->img_w, 40);
            assert_int_equal(r->img_h, 20);
            saw_pic = 1;
            continue;
        }
        if (r->kind == PV_INPUT) {
            assert_int_equal(r->input_type, PV_IN_CHECKBOX);
            assert_int_equal(r->checked, 1);
            assert_int_equal(r->form_method, PV_METHOD_POST);
            assert_true(r->form_id >= 0);
            saw_input = 1;
            continue;
        }
        if (r->text == NULL) continue;
        if (strcmp(r->text, "alpha") == 0) {
            assert_int_equal(r->fg_rgb, 0x112233);
            assert_int_equal(r->bg_rgb, 0x445566);
            assert_int_equal(r->font_scale, 150);
            assert_int_equal(r->line_scale, 180);
            assert_int_equal(r->text_indent, 13);
            assert_int_equal(r->tab_size, 4);
            assert_int_equal(r->opacity, 50);
            assert_int_equal(r->box_l, 11);
            assert_int_equal(r->box_w, 222);
            assert_int_not_equal(r->node_id, DOM_NODE_NONE);
            saw_alpha = 1;
        } else if (strcmp(r->text, "grid") == 0) {
            assert_int_equal(r->cont_cols, 2);
            assert_int_equal(r->cont_col_w[0], 100);   /* 100px fixed track */
            assert_int_equal(r->grid_span, 2);
            saw_grid = 1;
        } else if (strcmp(r->text, "flexi") == 0) {
            assert_int_equal(r->flex_grow, 200);       /* flex:2 -> grow x100 */
            saw_flexi = 1;
        } else if (strcmp(r->text, "boxy") == 0) {
            assert_true(r->block_id >= 0);
            const pv_box_def *bx = pv_box_at(p.view, (size_t)r->block_id);
            assert_non_null(bx);
            assert_int_equal(bx->border_radius, 8);
            assert_int_equal(bx->position, CSS_POS_RELATIVE);
            assert_int_equal(bx->z_index, 5);
            assert_int_equal(bx->box_h, 77);
            assert_int_equal(bx->opacity, 50);
            assert_int_equal(bx->mix_blend, CSS_MB_MULTIPLY);
            assert_int_equal(bx->isolation, CSS_ISO_ISOLATE);
            saw_boxy = 1;
        }
    }
    assert_true(saw_alpha && saw_pic && saw_grid && saw_flexi && saw_boxy && saw_input);

    tab_page_free(&p);
    tab_close(t);
}

int main(int argc, char **argv) {
    /* The worker re-execs /proc/self/exe (this very test binary), so the first thing
     * any tab-linking main() must do is run the worker when invoked as one. */
    tab_worker_dispatch(argc, argv);

    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_worker_args_valid),
        cmocka_unit_test(test_worker_args_not_worker),
        cmocka_unit_test(test_worker_args_malformed),
        cmocka_unit_test(test_worker_args_null_safe),
        cmocka_unit_test(test_open_close),
        cmocka_unit_test(test_open_null),
        cmocka_unit_test(test_load_basic),
        cmocka_unit_test(test_load_returns_view_with_link),
        cmocka_unit_test(test_load_returns_image_run),
        cmocka_unit_test(test_load_carries_author_color),
        cmocka_unit_test(test_load_carries_flex_item),
        cmocka_unit_test(test_load_carries_flex_wrap_align_row_gap),
        cmocka_unit_test(test_load_carries_float),
        cmocka_unit_test(test_load_carries_visibility_overflow_cursor_and_text_wrap),
        cmocka_unit_test(test_load_carries_cont_item),
        cmocka_unit_test(test_load_carries_node_id),
        cmocka_unit_test(test_click_runs_handler_and_returns_view),
        cmocka_unit_test(test_event_ipc_via_tab_eval),
        cmocka_unit_test(test_mouse_ipc_round_trip),
        cmocka_unit_test(test_focus_ipc_round_trip),
        cmocka_unit_test(test_tick_fires_delayed_timer),
        cmocka_unit_test(test_tick_interval_rearms),
        cmocka_unit_test(test_load_carries_box_decoration),
        cmocka_unit_test(test_load_carries_box_tree),
        cmocka_unit_test(test_load_view_codec_full_roundtrip),
        cmocka_unit_test(test_load_carries_form_control),
        cmocka_unit_test(test_load_strips_script),
        cmocka_unit_test(test_load_ex_runs_script_and_mutates),
        cmocka_unit_test(test_load_session_cookies_roundtrip),
        cmocka_unit_test(test_load_no_session_cookies_when_untrusted),
        cmocka_unit_test(test_load_ex_builds_dom_and_fires_onload),
        cmocka_unit_test(test_load_ex_inner_html_renders),
        cmocka_unit_test(test_load_without_js_does_not_run_script),
        cmocka_unit_test(test_load_full_location_is_real),
        cmocka_unit_test(test_js_navigation_absolute),
        cmocka_unit_test(test_js_navigation_relative_resolved),
        cmocka_unit_test(test_js_navigation_unsafe_is_blocked),
        cmocka_unit_test(test_no_js_no_navigation),
        cmocka_unit_test(test_load_null_and_too_large),
        cmocka_unit_test_setup_teardown(test_eval_sees_dom, setup_loaded, teardown),
        cmocka_unit_test_setup_teardown(test_eval_sees_env, setup_loaded, teardown),
        cmocka_unit_test_setup_teardown(test_eval_no_network_or_cross_origin_api, setup_loaded, teardown),
        cmocka_unit_test(test_xhr_works_when_net_allowed),
        cmocka_unit_test(test_xhr_undefined_when_net_not_allowed),
        cmocka_unit_test(test_xhr_blocked_host_refused_by_parent),
        cmocka_unit_test(test_external_script_executes_when_net_allowed),
        cmocka_unit_test(test_external_script_document_order),
        cmocka_unit_test(test_external_script_skipped_without_net),
        cmocka_unit_test(test_external_script_bad_ctype_not_executed),
        cmocka_unit_test(test_external_script_blocked_host_refused),
        cmocka_unit_test(test_external_css_applied_when_allowed),
        cmocka_unit_test(test_external_css_skipped_without_grant),
        cmocka_unit_test(test_external_css_bad_ctype_not_parsed),
        cmocka_unit_test(test_external_css_blocked_host_refused),
        cmocka_unit_test(test_external_css_survives_click_rederive),
        cmocka_unit_test(test_subreq_permitted_pure),
        cmocka_unit_test(test_js_date_timezone_is_utc_and_survives),
        cmocka_unit_test_setup_teardown(test_eval_exception, setup_loaded, teardown),
        cmocka_unit_test_setup_teardown(test_eval_persistent_state, setup_loaded, teardown),
        cmocka_unit_test(test_reload_replaces_page),
        cmocka_unit_test(test_load_captures_console_and_error),
        cmocka_unit_test(test_load_isolates_script_errors),
        cmocka_unit_test(test_load_error_carries_location),
        cmocka_unit_test(test_load_element_wrapper_idioms),
        cmocka_unit_test(test_load_document_fonts_stub),
        cmocka_unit_test(test_load_without_js_has_empty_console),
        cmocka_unit_test(test_eval_captures_console_output),
        cmocka_unit_test(test_eval_without_load),
        cmocka_unit_test(test_binary_does_not_crash_parent),
        cmocka_unit_test(test_child_death_survived),
        cmocka_unit_test(test_decode_image_in_sandbox),
        cmocka_unit_test(test_decode_image_rejects_junk),
        cmocka_unit_test(test_decode_image_null_args),
        cmocka_unit_test(test_free_null_and_double),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
