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
            assert_int_equal(r->bord_tw, 2);
            assert_int_equal(r->bord_tc, 0xff0000);
            assert_int_equal(r->pad_t, 7);
            assert_int_equal(r->pad_l, 7);
            assert_int_equal(r->box_sizing, CSS_BOXS_BORDER);
            saw = 1;
        }
    }
    assert_true(saw);

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
        cmocka_unit_test(test_load_carries_box_decoration),
        cmocka_unit_test(test_load_carries_form_control),
        cmocka_unit_test(test_load_strips_script),
        cmocka_unit_test(test_load_ex_runs_script_and_mutates),
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
