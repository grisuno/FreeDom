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

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_open_close),
        cmocka_unit_test(test_open_null),
        cmocka_unit_test(test_load_basic),
        cmocka_unit_test(test_load_returns_view_with_link),
        cmocka_unit_test(test_load_returns_image_run),
        cmocka_unit_test(test_load_carries_author_color),
        cmocka_unit_test(test_load_carries_form_control),
        cmocka_unit_test(test_load_strips_script),
        cmocka_unit_test(test_load_ex_runs_script_and_mutates),
        cmocka_unit_test(test_load_without_js_does_not_run_script),
        cmocka_unit_test(test_load_null_and_too_large),
        cmocka_unit_test_setup_teardown(test_eval_sees_dom, setup_loaded, teardown),
        cmocka_unit_test_setup_teardown(test_eval_sees_env, setup_loaded, teardown),
        cmocka_unit_test_setup_teardown(test_eval_exception, setup_loaded, teardown),
        cmocka_unit_test_setup_teardown(test_eval_persistent_state, setup_loaded, teardown),
        cmocka_unit_test(test_reload_replaces_page),
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
