/*
 * TDD suite for js_dom (DOM <-> JS bridge).
 *
 * RED state until src/js_dom.c exists: this links and fails on purpose.
 *
 * Build: make test   (cmocka + lexbor + vendored quickjs)
 * ASan:  make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "dom.h"
#include "html_parse.h"
#include "js_dom.h"
#include "js_sandbox.h"

static const char HTML[] =
    "<!DOCTYPE html><html><head><title>T</title></head>"
    "<body>"
    "<div id=\"main\" class=\"container box\">"
    "<p class=\"text\">Hello</p>"
    "<p class=\"text muted\">World</p>"
    "<button id=\"go\" class=\"btn\">Go</button>"
    "</div>"
    "</body></html>";

typedef struct fixture {
    hp_document *doc;
    dom_index   *idx;
    js_context  *ctx;
} fixture;

static int setup(void **state) {
    fixture *f = (fixture *)calloc(1, sizeof *f);
    if (f == NULL) return -1;
    if (hp_parse(HTML, sizeof HTML - 1, NULL, &f->doc) != HP_OK) return -1;
    if (dom_build(f->doc, &f->idx) != DOM_OK) return -1;
    if (js_context_new(NULL, &f->ctx) != JS_OK) return -1;
    if (jd_install(f->ctx, f->idx) != JD_OK) return -1;
    *state = f;
    return 0;
}

static int teardown(void **state) {
    fixture *f = (fixture *)*state;
    if (f != NULL) {
        js_context_free(f->ctx);
        dom_free(f->idx);
        hp_document_free(f->doc);
        free(f);
    }
    return 0;
}

/* Evaluates src in the fixture context and returns the result string (owned by
 * the caller-provided js_result, freed by the caller). */
static js_status run(fixture *f, const char *src, js_result *r) {
    return js_eval(f->ctx, src, strlen(src), r);
}

#define EXPECT(f, src, expected)                                   \
    do {                                                           \
        js_result _r;                                              \
        assert_int_equal(run((f), (src), &_r), JS_OK);             \
        assert_non_null(_r.value);                                 \
        assert_string_equal(_r.value, (expected));                 \
        js_result_free(&_r);                                       \
    } while (0)

/* --- install --- */

static void test_install_null_args(void **state) {
    (void)state;
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    assert_int_equal(jd_install(ctx, NULL), JD_ERR_NULL_ARG);
    assert_int_equal(jd_install(NULL, NULL), JD_ERR_NULL_ARG);
    js_context_free(ctx);
}

/* --- queries from JS --- */

static void test_get_element_by_id(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "dom.getElementById('main') !== null", "true");
    EXPECT(f, "dom.tagName(dom.getElementById('main'))", "div");
    EXPECT(f, "dom.tagName(dom.getElementById('go'))", "button");
    EXPECT(f, "dom.getElementById('nope')", "null");
}

static void test_node_count(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "dom.nodeCount() > 0", "true");
}

static void test_by_class_and_tag(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "dom.getByClass('text').length", "2");
    EXPECT(f, "dom.getByClass('btn').length", "1");
    EXPECT(f, "dom.getByTag('p').length", "2");
    EXPECT(f, "dom.getByTag('marquee').length", "0");
}

static void test_navigation(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "dom.tagName(dom.firstChild(dom.getElementById('main')))", "p");
    EXPECT(f,
        "var b=dom.getElementById('go'); dom.tagName(dom.parent(b))", "div");
    EXPECT(f,
        "var p=dom.firstChild(dom.getElementById('main'));"
        "dom.tagName(dom.nextSibling(p))", "p");
}

static void test_attributes(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "dom.getAttribute(dom.getElementById('main'),'class')",
           "container box");
    EXPECT(f, "dom.getAttribute(dom.getElementById('main'),'data-x')", "null");
}

static void test_document_order(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f,
        "dom.precedes(dom.getElementById('main'), dom.getElementById('go'))",
        "true");
}

/* --- robustness: bogus handles never crash, just yield null --- */

static void test_invalid_handles(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "dom.tagName(99999)", "null");
    EXPECT(f, "dom.tagName(-1)", "null");
    EXPECT(f, "dom.firstChild(99999)", "null");
    EXPECT(f, "dom.getAttribute(99999,'id')", "null");
}

/* --- the API cannot be hijacked --- */

static void test_methods_are_frozen(void **state) {
    fixture *f = (fixture *)*state;
    /* Reassigning a method must not take effect (non-writable). */
    EXPECT(f, "try{dom.getElementById=1}catch(e){}; typeof dom.getElementById",
           "function");
    /* The sealed object rejects new properties. */
    EXPECT(f, "try{dom.injected=1}catch(e){}; typeof dom.injected", "undefined");
}

/* --- still no I/O even with dom installed --- */

static void test_no_io_with_dom(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof require + typeof fetch + typeof std",
           "undefinedundefinedundefined");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_install_null_args),
        cmocka_unit_test_setup_teardown(test_get_element_by_id, setup, teardown),
        cmocka_unit_test_setup_teardown(test_node_count, setup, teardown),
        cmocka_unit_test_setup_teardown(test_by_class_and_tag, setup, teardown),
        cmocka_unit_test_setup_teardown(test_navigation, setup, teardown),
        cmocka_unit_test_setup_teardown(test_attributes, setup, teardown),
        cmocka_unit_test_setup_teardown(test_document_order, setup, teardown),
        cmocka_unit_test_setup_teardown(test_invalid_handles, setup, teardown),
        cmocka_unit_test_setup_teardown(test_methods_are_frozen, setup, teardown),
        cmocka_unit_test_setup_teardown(test_no_io_with_dom, setup, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
