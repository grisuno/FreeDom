/*
 * libFuzzer harness for js_dom event dispatch (spec/js_dom.md 7d).
 *
 * Goal: arbitrary bytes run as page script against a real DOM (listeners on
 * elements/document/window, handler properties, dispatchEvent, DOM mutation from
 * inside a listener), followed by every engine-generated event kind on every
 * node, must never crash, leak, or trigger UB on the host.
 *
 * Build & run: make fuzz-jsdom   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "dom.h"
#include "html_parse.h"
#include "js_dom.h"
#include "js_trusted.h"
#include "js_geom.h"
#include "web_storage.h"
#include "js_sandbox.h"
#include "url.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static const char HTML[] =
    "<!DOCTYPE html><html><head><title>T</title></head><body>"
    "<div id=\"main\"><p class=\"a\">x<span id=\"s\">y</span></p>"
    "<button id=\"go\">Go</button>"
    "<form id=\"frm\"><input id=\"q\" name=\"q\"></form></div>"
    "</body></html>";

static dom_node_id fz_dom_parent(void *ctx, dom_node_id n) {
    return dom_parent((const dom_index *)ctx, n);
}

/* Bounds the per-input cost: engine events fired per node kind. */
#define FUZZ_JSDOM_MAX_NODES 64u

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    hp_document *doc = NULL;
    dom_index *idx = NULL;
    js_context *ctx = NULL;
    jd_opaque op;
    memset(&op, 0, sizeof op);

    js_limits lim = js_limits_default();
    lim.memory_limit_bytes = 32u * 1024u * 1024u;
    lim.time_budget_ms = 100;
    lim.max_source_bytes = 1u * 1024u * 1024u;

    if (hp_parse(HTML, sizeof HTML - 1, NULL, &doc) != HP_OK) return 0;
    if (dom_build(doc, &idx) != DOM_OK) goto out;
    if (js_context_new(&lim, &ctx) != JS_OK) goto out;
    if (jd_install(ctx, idx, &op) != JD_OK) goto out;
    {
        /* A real location, so history.pushState/replaceState/popstate run too. */
        static const char loc[] = "https://a.test/dir/page?q=1#h";
        url_parts parts;
        if (url_split(loc, &parts) == URL_OK) (void)jd_set_location(ctx, loc, &parts);
    }
    (void)jt_enable_open(ctx);   /* trusted-host surface: window.open recording */
    (void)jt_enable_ws(ctx);     /* trusted-host surface: WebSocket op recording */
    (void)jt_enable_worker(ctx); /* trusted-host surface: Worker realms */
    {
        /* Trusted-host in-memory localStorage, seeded with odd pairs. */
        const char *k[] = { "a", "\xed\xa0\x80", "" };
        const char *v[] = { "1", "x", "\xf0\x9f\x98\x80" };
        size_t kl[] = { 1, 3, 0 }, vl[] = { 1, 1, 4 };
        char *seed = NULL;
        size_t sl = 0;
        if (wst_pack(k, kl, v, vl, 3, &seed, &sl) == 0) (void)jt_enable_storage(ctx, seed, sl);
        free(seed);
    }

    /* Real geometry on every node, so dom.rect/dom.viewport and every measuring
     * getter run against hostile script too (spec/js_geom.md). */
    jg_table geom;
    jg_init(&geom);
    size_t nn = dom_node_count(idx);
    for (size_t i = 0; i < nn && i < FUZZ_JSDOM_MAX_NODES; i++)
        (void)jg_add(&geom, (dom_node_id)i, (double)i * 3.0, (double)i * 7.0, 10.0, 5.0);
    geom.view_w = 1000; geom.view_h = 700; geom.doc_w = 1000; geom.doc_h = 2000;
    geom.scroll_y = 12;
    (void)jg_aggregate(&geom, fz_dom_parent, idx);
    (void)jd_set_geometry(ctx, &geom);

    js_result r;
    memset(&r, 0, sizeof r);
    (void)js_eval(ctx, (const char *)data, size, &r);
    js_result_free(&r);   /* filled on exception too */
    (void)js_pump_jobs(ctx, 64);

    size_t n = dom_node_count(idx);
    if (n > FUZZ_JSDOM_MAX_NODES) n = FUZZ_JSDOM_MAX_NODES;
    for (size_t i = 0; i < n; i++) {
        dom_node_id id = (dom_node_id)i;
        (void)jd_fire_click(ctx, id);
        (void)jd_fire_submit(ctx, id);
        (void)jd_fire_event(ctx, id, "keydown", "Enter", 13, "v\"\\");
        (void)jd_fire_event(ctx, id, "focus", NULL, 0, NULL);
        (void)jd_fire_mouse_event(ctx, id, "mouseover", 1, 2, 0);
    }
    (void)js_pump_jobs(ctx, 64);
    int go = 0;
    free(jd_take_history(ctx, &go));
    for (int i = -1; i < 4; i++) (void)jd_pop_state(ctx, i);
    free(jt_take_opens(ctx));
    {
        char *snap = NULL;
        size_t snl = 0;
        if (jt_take_storage(ctx, &snap, &snl) && wst_decode_check(snap, snl) != 0)
            __builtin_trap();                 /* the worker must emit what the parent accepts */
        free(snap);
    }
    {
        /* Drain socket ops and push hostile events (every kind, odd payloads) back. */
        jt_ws_op wops[JT_WS_MAX_OPS];
        size_t nw = jt_take_ws(ctx, wops, JT_WS_MAX_OPS);
        for (size_t i = 0; i < nw; i++) {
            (void)jt_ws_event(ctx, wops[i].id, 1, 0, NULL, 0);
            (void)jt_ws_event(ctx, wops[i].id, 2, 0, wops[i].data, wops[i].len);
            (void)jt_ws_event(ctx, wops[i].id, 3, 0, "\x00\xff\x80", 3);
            (void)jt_ws_event(ctx, wops[i].id, 4, 1000, "\xc3\x28", 2);
        }
        jt_ws_ops_free(wops, nw);
        for (int k = -1; k < 8; k++) (void)jt_ws_event(ctx, k, k, k, "x", 1);
        nw = jt_take_ws(ctx, wops, JT_WS_MAX_OPS);
        jt_ws_ops_free(wops, nw);
    }
    free(jd_take_history(ctx, &go));

    js_context_free(ctx);
    ctx = NULL;
    jg_free(&geom);
out:
    js_context_free(ctx);
    dom_free(idx);
    hp_document_free(doc);
    return 0;
}
