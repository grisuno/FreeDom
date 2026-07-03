/*
 * TDD suite for js_env (anti_fp <-> JS environment bridge).
 *
 * RED state until src/js_env.c exists: this links and fails on purpose.
 *
 * Build: make test   (cmocka + vendored quickjs + lexbor for the coexistence test)
 * ASan:  make asan
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
#include "js_sandbox.h"

typedef struct fixture {
    js_context *ctx;
} fixture;

static int setup(void **state) {
    fixture *f = (fixture *)calloc(1, sizeof *f);
    if (f == NULL) return -1;
    if (js_context_new(NULL, &f->ctx) != JS_OK) return -1;
    if (je_install(f->ctx, 1680, 1050) != JE_OK) return -1;
    *state = f;
    return 0;
}

static int teardown(void **state) {
    fixture *f = (fixture *)*state;
    if (f != NULL) {
        js_context_free(f->ctx);
        free(f);
    }
    return 0;
}

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
    assert_int_equal(je_install(NULL, 1920, 1080), JE_ERR_NULL_ARG);

    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    assert_int_equal(je_install(ctx, 1920, 1080), JE_OK);
    js_context_free(ctx);
}

/* --- normalized identity --- */

static void test_navigator_identity(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "navigator.userAgent.indexOf('Firefox') >= 0", "true");
    EXPECT(f, "navigator.userAgent.length > 0", "true");
    EXPECT(f, "navigator.language", "en-US");
    EXPECT(f, "navigator.languages.length", "2");
    EXPECT(f, "navigator.languages[0]", "en-US");
    EXPECT(f, "navigator.languages[1]", "en");
    EXPECT(f, "navigator.platform", "Linux x86_64");
    EXPECT(f, "navigator.vendor === ''", "true");
    EXPECT(f, "navigator.hardwareConcurrency", "2");
    EXPECT(f, "navigator.deviceMemory", "8");
    EXPECT(f, "navigator.webdriver", "false");
    EXPECT(f, "navigator.doNotTrack === null", "true");
}

/* --- screen bucketing: real (1680,1050) snaps to 1600x900 --- */

static void test_screen_bucketed(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "screen.width", "1600");
    EXPECT(f, "screen.height", "900");
    EXPECT(f, "screen.availWidth === screen.width", "true");
    EXPECT(f, "screen.availHeight === screen.height", "true");
    EXPECT(f, "screen.colorDepth", "24");
    EXPECT(f, "screen.pixelDepth", "24");
}

/* --- coarse clocks --- */

static void test_clocks_coarse(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "Date.now() % 100", "0");
    EXPECT(f, "Date.now() > 1700000000000", "true");
    EXPECT(f, "typeof performance.now()", "number");
    EXPECT(f, "performance.now() % 100", "0");
    EXPECT(f, "performance.now() >= 0", "true");
}

/* --- the API cannot be hijacked --- */

static void test_unforgeable(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "try{navigator.userAgent='x'}catch(e){};"
              "navigator.userAgent.indexOf('Firefox') >= 0", "true");
    EXPECT(f, "try{navigator.injected=1}catch(e){}; typeof navigator.injected",
           "undefined");
    EXPECT(f, "try{screen.width=10}catch(e){}; screen.width", "1600");
    /* Date.now cannot be restored to a high-resolution real clock. */
    EXPECT(f, "try{Date.now=function(){return 12345}}catch(e){}; Date.now()%100",
           "0");
}

/* --- screen edge cases never crash, fall to smallest bucket --- */

static void test_screen_edges(void **state) {
    (void)state;
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    assert_int_equal(je_install(ctx, 0, 0), JE_OK);
    js_result r;
    const char *probe = "screen.width > 0";
    assert_int_equal(js_eval(ctx, probe, strlen(probe), &r), JS_OK);
    assert_string_equal(r.value, "true");
    js_result_free(&r);
    js_context_free(ctx);

    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    assert_int_equal(je_install(ctx, -1, -1), JE_OK);
    js_context_free(ctx);
}

/* --- canvas/audio readback poisoning (fp_perturb) --- */

static void test_canvas_readback(void **state) {
    (void)state;
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    assert_int_equal(je_install_canvas(ctx, 0xABCDEF0123456789ULL), JE_OK);

    /* poisoning is bounded to the LSB, leaves the input intact, and changes
       at least some bytes of a large readback. */
    const char *probe =
        "(function(){var a=new Uint8Array(4096);"
        "for(var i=0;i<a.length;i++)a[i]=128;"
        "var p=canvas.readback(a);"
        "var bounded=1,changed=0,untouched=1;"
        "for(var i=0;i<a.length;i++){var d=p[i]-128;"
        "if(d!==0&&d!==1)bounded=0; if(p[i]!==128)changed++; if(a[i]!==128)untouched=0;}"
        "return (bounded&&untouched&&changed>0)?'ok':'bad';})()";
    js_result r;
    assert_int_equal(js_eval(ctx, probe, strlen(probe), &r), JS_OK);
    assert_string_equal(r.value, "ok");
    js_result_free(&r);

    /* deterministic within a session: same input => same output. */
    const char *det =
        "(function(){var a=new Uint8Array(256);for(var i=0;i<256;i++)a[i]=i;"
        "var p=canvas.readback(a),q=canvas.readback(a),eq=1;"
        "for(var i=0;i<256;i++)if(p[i]!==q[i])eq=0;return eq?'true':'false';})()";
    assert_int_equal(js_eval(ctx, det, strlen(det), &r), JS_OK);
    assert_string_equal(r.value, "true");
    js_result_free(&r);

    /* audio shares the same poisoning seam. */
    const char *au = "typeof audio.readback";
    assert_int_equal(js_eval(ctx, au, strlen(au), &r), JS_OK);
    assert_string_equal(r.value, "function");
    js_result_free(&r);

    js_context_free(ctx);
}

/* checksum of a fixed perturbed readback, for cross-session comparison. */
static void readback_checksum(uint64_t key, char *out, size_t out_size) {
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    assert_int_equal(je_install_canvas(ctx, key), JE_OK);
    const char *probe =
        "(function(){var a=new Uint8Array(1024);for(var i=0;i<1024;i++)a[i]=0;"
        "var p=canvas.readback(a),s=0;"
        "for(var i=0;i<1024;i++)s=((s*31)+p[i])>>>0;return ''+s;})()";
    js_result r;
    assert_int_equal(js_eval(ctx, probe, strlen(probe), &r), JS_OK);
    assert_non_null(r.value);
    snprintf(out, out_size, "%s", r.value);
    js_result_free(&r);
    js_context_free(ctx);
}

static void test_canvas_unlinkable(void **state) {
    (void)state;
    char a[64], b[64];
    readback_checksum(1, a, sizeof a);
    readback_checksum(2, b, sizeof b);
    assert_string_not_equal(a, b); /* different session key => different poison */
}

static void test_canvas_unforgeable(void **state) {
    (void)state;
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    assert_int_equal(je_install_canvas(ctx, 7), JE_OK);
    js_result r;
    const char *p1 = "try{canvas.readback=1}catch(e){}; typeof canvas.readback";
    assert_int_equal(js_eval(ctx, p1, strlen(p1), &r), JS_OK);
    assert_string_equal(r.value, "function");
    js_result_free(&r);
    const char *p2 = "try{canvas.injected=1}catch(e){}; typeof canvas.injected";
    assert_int_equal(js_eval(ctx, p2, strlen(p2), &r), JS_OK);
    assert_string_equal(r.value, "undefined");
    js_result_free(&r);
    js_context_free(ctx);
}

/* --- coexists with js_dom in the same context --- */

static const char HTML[] =
    "<!DOCTYPE html><html><head><title>T</title></head>"
    "<body><div id=\"main\"><p>Hi</p></div></body></html>";

static void test_coexists_with_dom(void **state) {
    (void)state;
    hp_document *doc = NULL;
    dom_index *idx = NULL;
    js_context *ctx = NULL;

    assert_int_equal(hp_parse(HTML, sizeof HTML - 1, NULL, &doc), HP_OK);
    assert_int_equal(dom_build(doc, &idx), DOM_OK);
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    jd_opaque op;
    assert_int_equal(jd_install(ctx, idx, &op), JD_OK);
    assert_int_equal(je_install(ctx, 1920, 1080), JE_OK);

    js_result r;
    const char *q1 = "dom.nodeCount() > 0";
    assert_int_equal(js_eval(ctx, q1, strlen(q1), &r), JS_OK);
    assert_string_equal(r.value, "true");
    js_result_free(&r);

    const char *q2 = "navigator.language";
    assert_int_equal(js_eval(ctx, q2, strlen(q2), &r), JS_OK);
    assert_string_equal(r.value, "en-US");
    js_result_free(&r);

    js_context_free(ctx);
    dom_free(idx);
    hp_document_free(doc);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_install_null_args),
        cmocka_unit_test_setup_teardown(test_navigator_identity, setup, teardown),
        cmocka_unit_test_setup_teardown(test_screen_bucketed, setup, teardown),
        cmocka_unit_test_setup_teardown(test_clocks_coarse, setup, teardown),
        cmocka_unit_test_setup_teardown(test_unforgeable, setup, teardown),
        cmocka_unit_test(test_screen_edges),
        cmocka_unit_test(test_canvas_readback),
        cmocka_unit_test(test_canvas_unlinkable),
        cmocka_unit_test(test_canvas_unforgeable),
        cmocka_unit_test(test_coexists_with_dom),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
