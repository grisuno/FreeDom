/*
 * TDD suite for js_native (spec/js_native.md): the host platform must describe itself the
 * way a native browser does -- no shim source behind toString, interface tags, navigator
 * fields on Navigator.prototype, a Firefox-consistent plugin list and an honest CSS.supports.
 *
 * The fixture mirrors the worker's install order (src/tab.c child_load) and then seals.
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "dom.h"
#include "html_parse.h"
#include "js_dom.h"
#include "js_env.h"
#include "js_native.h"
#include "js_sandbox.h"

static const char HTML[] =
    "<!DOCTYPE html><html><head><title>T</title></head>"
    "<body><div id=\"main\"><p>Hi</p><a href=\"/x\">l</a></div></body></html>";

typedef struct fixture {
    hp_document *doc;
    dom_index *idx;
    js_context *ctx;
    jd_opaque op;
} fixture;

static int setup(void **state) {
    fixture *f = (fixture *)calloc(1, sizeof *f);
    if (f == NULL) return -1;
    if (hp_parse(HTML, sizeof HTML - 1, NULL, &f->doc) != HP_OK) return -1;
    if (dom_build(f->doc, &f->idx) != DOM_OK) return -1;
    if (js_context_new(NULL, &f->ctx) != JS_OK) return -1;
    if (jd_install(f->ctx, f->idx, &f->op) != JD_OK) return -1;
    if (je_install_identity_trusted(f->ctx, 1920, 1080, NULL, NULL, 1) != JE_OK) return -1;
    if (je_install_canvas(f->ctx, 7) != JE_OK) return -1;
    if (jn_seal(f->ctx) != 0) return -1;
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

#define EXPECT(f, src, expected)                                              \
    do {                                                                      \
        js_result _r;                                                         \
        assert_int_equal(js_eval((f)->ctx, (src), strlen(src), &_r), JS_OK);  \
        assert_non_null(_r.value);                                            \
        assert_string_equal(_r.value, (expected));                            \
        js_result_free(&_r);                                                  \
    } while (0)

#define NATIVE(n) "function " n "() {\n    [native code]\n}"

static void test_null_and_idempotent(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jn_seal(NULL), -1);
    assert_int_equal(jn_seal(f->ctx), 0);
    EXPECT(f, "String(window)", "[object Window]");
}

/* A host function never shows shim source, whatever way it was published. */
static void test_host_functions_look_native(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "Function.prototype.toString.call(setTimeout)", NATIVE("setTimeout"));
    EXPECT(f, "Function.prototype.toString.call(document.createElement)", NATIVE("createElement"));
    EXPECT(f, "Function.prototype.toString.call(document.querySelector)", NATIVE("querySelector"));
    EXPECT(f, "Function.prototype.toString.call(requestAnimationFrame)", NATIVE("requestAnimationFrame"));
    EXPECT(f, "Function.prototype.toString.call(Element.prototype.getAttribute)", NATIVE("getAttribute"));
    EXPECT(f, "Function.prototype.toString.call(addEventListener)", NATIVE("addEventListener"));
    EXPECT(f, "Function.prototype.toString.call(MutationObserver)", NATIVE("MutationObserver"));
    /* The classic library test for a native implementation. */
    EXPECT(f, "/\\{\\s*\\[native code\\]\\s*\\}/.test(''+document.getElementById)", "true");
    /* A closure a host function creates later is host code too. */
    EXPECT(f, "var d=document.createElement('div');/native code/.test(''+d.addEventListener)", "true");
}

/* No global function leaks source: the sweep is the property, not a hand-picked list. */
static void test_no_global_leaks_source(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f,
        "(function(){var bad=[];Object.getOwnPropertyNames(window).forEach(function(k){"
        " var v;try{v=window[k];}catch(e){return;}"
        " if(typeof v==='function'&&!/\\[native code\\]/.test(Function.prototype.toString.call(v)))bad.push(k);"
        " if(typeof v==='function'&&v.prototype){Object.getOwnPropertyNames(v.prototype).forEach(function(m){"
        "  var d=Object.getOwnPropertyDescriptor(v.prototype,m);"
        "  [d.value,d.get,d.set].forEach(function(fn){"
        "   if(typeof fn==='function'&&!/\\[native code\\]/.test(Function.prototype.toString.call(fn)))bad.push(k+'.'+m);});});}"
        "});return bad.slice(0,8).join(',');})()", "");
}

/* Page code keeps its exact source: only the host is hidden. */
static void test_page_functions_keep_source(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "function page(a){return a+1}; page.toString()", "function page(a){return a+1}");
    EXPECT(f, "(function(){return 7}).toString()", "function(){return 7}");
    EXPECT(f, "(()=>1).toString()", "()=>1");
    EXPECT(f, "new Function('a','return a').toString().indexOf('return a')>=0", "true");
    EXPECT(f, "class K{m(){return 2}}; K.toString()", "class K{m(){return 2}}");
    /* A page function published on window is NOT renamed or hidden by a later seal. */
    EXPECT(f, "window.mine=function(){return 3}; 0", "0");
    assert_int_equal(jn_seal(f->ctx), 0);
    EXPECT(f, "'['+mine.name+']'+mine.toString()", "[]function(){return 3}");
    /* Nor is an intrinsic that is deliberately published under two keys. */
    EXPECT(f, "[Set.prototype.keys.name,String.prototype.trimLeft.name,Array.prototype.push.name].join()",
           "values,trimStart,push");
}

static void test_names(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "setTimeout.name", "setTimeout");
    EXPECT(f, "document.createElement.name", "createElement");
    EXPECT(f, "Object.getOwnPropertyDescriptor(Navigator.prototype,'userAgent').get.name", "get userAgent");
}

static void test_interface_tags(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "String(window)", "[object Window]");
    EXPECT(f, "String(document)", "[object HTMLDocument]");
    EXPECT(f, "String(navigator)", "[object Navigator]");
    EXPECT(f, "Object.prototype.toString.call(document.body)", "[object HTMLBodyElement]");
    EXPECT(f, "Object.prototype.toString.call(document.createElement('div'))", "[object HTMLDivElement]");
    EXPECT(f, "Object.prototype.toString.call(screen)", "[object Screen]");
    EXPECT(f, "Object.prototype.toString.call(performance)", "[object Performance]");
    EXPECT(f, "Object.prototype.toString.call(history)", "[object History]");
    EXPECT(f, "Object.prototype.toString.call(crypto)", "[object Crypto]");
    /* ECMAScript intrinsics are untouched. */
    EXPECT(f, "[String({}),Object.prototype.toString.call([]),Object.prototype.toString.call(function(){}),"
              "Object.prototype.toString.call(new Date(0)),Object.prototype.toString.call(/a/),"
              "Object.prototype.toString.call(new Error('x'))].join()",
           "[object Object],[object Array],[object Function],[object Date],[object RegExp],[object Error]");
    /* WebIDL shape: not enumerable, so for-in over an element does not list it. */
    EXPECT(f, "Object.getOwnPropertyDescriptor(Navigator.prototype,Symbol.toStringTag).enumerable", "false");
}

static void test_singleton_interfaces(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "[navigator instanceof Navigator, screen instanceof Screen, performance instanceof Performance,"
              " history instanceof History, window instanceof Window, document instanceof HTMLDocument].join()",
           "true,true,true,true,true,true");
}

/* navigator carries nothing itself: every identity field is a Navigator.prototype getter. */
static void test_navigator_shape(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "Object.getOwnPropertyNames(navigator).length", "0");
    EXPECT(f, "['userAgent','webdriver','languages','plugins','platform','hardwareConcurrency']"
              ".every(function(k){return k in Navigator.prototype"
              " && typeof Object.getOwnPropertyDescriptor(Navigator.prototype,k).get==='function'"
              " && Object.getOwnPropertyDescriptor(Navigator.prototype,k).set===undefined;})", "true");
    EXPECT(f, "navigator.userAgent.indexOf('Firefox')>=0 && navigator.webdriver===false", "true");
    /* Assigning does not change the identity (getter without setter). */
    EXPECT(f, "try{navigator.userAgent='x';}catch(e){}; navigator.userAgent.indexOf('Firefox')>=0", "true");
    EXPECT(f, "'use strict';var t=false;try{navigator.webdriver=true;}catch(e){t=true;} t+'|'+navigator.webdriver",
           "true|false");
    EXPECT(f, "navigator.languages===navigator.languages", "true");
}

/* The plugin list is the one the claimed browser reports. */
static void test_firefox_plugins(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "navigator.plugins.length", "5");
    EXPECT(f, "Array.prototype.map.call(navigator.plugins,function(p){return p.name}).join('|')",
           "PDF Viewer|Chrome PDF Viewer|Chromium PDF Viewer|Microsoft Edge PDF Viewer|WebKit built-in PDF");
    EXPECT(f, "navigator.plugins[0].filename+'|'+navigator.plugins[0].description",
           "internal-pdf-viewer|Portable Document Format");
    EXPECT(f, "Array.prototype.map.call(navigator.mimeTypes,function(m){return m.type}).join('|')",
           "application/pdf|text/pdf");
    EXPECT(f, "navigator.pdfViewerEnabled", "true");
    EXPECT(f, "navigator.mimeTypes[0].enabledPlugin===navigator.plugins[0]", "true");
}

static void test_css_supports(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "[CSS.supports('display','grid'),CSS.supports('display','flex'),CSS.supports('color','red'),"
              " CSS.supports('(display: grid)'),CSS.supports('position','sticky'),"
              " CSS.supports('--x','1')].join()", "true,true,true,true,true,true");
    EXPECT(f, "[CSS.supports('frobnicate','1'),CSS.supports('display',''),CSS.supports('(frobnicate: 1)'),"
              " CSS.supports('-webkit-box-reflect','below')].join()", "false,false,false,false");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(test_null_and_idempotent, setup, teardown),
        cmocka_unit_test_setup_teardown(test_host_functions_look_native, setup, teardown),
        cmocka_unit_test_setup_teardown(test_no_global_leaks_source, setup, teardown),
        cmocka_unit_test_setup_teardown(test_page_functions_keep_source, setup, teardown),
        cmocka_unit_test_setup_teardown(test_names, setup, teardown),
        cmocka_unit_test_setup_teardown(test_interface_tags, setup, teardown),
        cmocka_unit_test_setup_teardown(test_singleton_interfaces, setup, teardown),
        cmocka_unit_test_setup_teardown(test_navigator_shape, setup, teardown),
        cmocka_unit_test_setup_teardown(test_firefox_plugins, setup, teardown),
        cmocka_unit_test_setup_teardown(test_css_supports, setup, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
