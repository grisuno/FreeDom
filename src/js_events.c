/*
 * js_events.c -- click / submit / input / mouse event entry points from the host.
 * Split out of js_dom.c (anti-monolith clause, CLAUDE.md 3.4); contract in
 * include/js_dom.h and spec/js_dom.md.
 */
#define _GNU_SOURCE

#include "js_dom.h"

#include "dom.h"
#include "freebug.h"
#include "html_parse.h"
#include "js_sandbox.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quickjs.h"
#include "js_dom_internal.h"

/* --- click events (Stage 4 dispatcher keystone) --- */

struct jd_click_state {
    int installed; /* nonzero after jd_install_events succeeds */
};

jd_click_state *jd_click_state_new(void) {
    jd_click_state *s = (jd_click_state *)calloc(1, sizeof *s);
    return s;
}

void jd_click_state_free(jd_click_state *s) {
    free(s);
}

jd_status jd_install_events(js_context *ctx, jd_click_state *state) {
    if (ctx == NULL || state == NULL) return JD_ERR_NULL_ARG;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;
    jd_opaque *o = jd_opaque_get(jsctx);
    if (o == NULL) return JD_ERR_INTERNAL;
    o->click = state;
    state->installed = 1;
    return JD_OK;
}

/* Runs one engine event-dispatch expression and maps its result to the C
 * contract: 1 = default action proceeds, 0 = a listener called preventDefault().
 * Fail-open: an exception or a non-number result lets the action proceed. */
static int jd_eval_default_action(JSContext *jsctx, const char *src, size_t n,
                                  const char *tag) {
    JSValue r = JS_Eval(jsctx, src, n, tag, JS_EVAL_TYPE_GLOBAL);
    int default_action = 1;
    if (!JS_IsException(r)) {
        int32_t v = 1;
        if (JS_ToInt32(jsctx, &v, r) == 0) default_action = (v != 0) ? 1 : 0;
    } else {
        JS_FreeValue(jsctx, JS_GetException(jsctx));
    }
    JS_FreeValue(jsctx, r);
    return default_action;
}

int jd_fire_click(js_context *ctx, dom_node_id node_id) {
    if (ctx == NULL || node_id == DOM_NODE_NONE) return 1;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return 1;
    char src[64];
    int n = snprintf(src, sizeof src, "__dispatchEvent(%u,\"click\",null)", (unsigned)node_id);
    if (n < 0 || (size_t)n >= sizeof src) return 1;
    return jd_eval_default_action(jsctx, src, (size_t)n, "<click-fire>");
}

/* Fires the submit event for form_node_id. Returns 0 if preventDefault() was
 * called, 1 if the default action should proceed. */
int jd_fire_submit(js_context *ctx, dom_node_id form_node_id) {
    if (ctx == NULL || form_node_id == DOM_NODE_NONE) return 1;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return 1;
    char src[64];
    int n = snprintf(src, sizeof src, "__dispatchEvent(%u,\"submit\",null)", (unsigned)form_node_id);
    if (n < 0 || (size_t)n >= sizeof src) return 1;
    return jd_eval_default_action(jsctx, src, (size_t)n, "<submit-fire>");
}

/* Escapes a string for safe interpolation into JS double-quoted string literal:
 * replaces backslash with \\ and double-quote with \". Returns number of bytes
 * written. Truncates if dst is too small (intended for bounded stack buffers). */
static size_t jd_escape_js_str(const char *src, char *dst, size_t dstsz) {
    size_t pos = 0;
    if (dstsz == 0) return 0;
    for (const char *p = src; *p != '\0' && pos + 6 < dstsz; ++p) {
        unsigned char c = (unsigned char)*p;
        if (c < 0x20) {  /* control chars: skip */
            continue;
        } else if (c == '\\' || c == '"') {
            if (pos + 2 >= dstsz) break;
            dst[pos++] = '\\';
            dst[pos++] = c;
        } else {
            dst[pos++] = c;
        }
    }
    dst[pos] = '\0';
    return pos;
}

/* Fires a generic DOM event on node_id by calling
 * __dispatchEvent(node_id, event_type, {key, keyCode, value}).
 * Returns 1 if the default action should proceed, 0 if a handler called
 * preventDefault(). Fail-open: if anything goes wrong, action proceeds.
 * The key and value strings are escaped before interpolation into JS source
 * (defence in depth: the data comes from the trusted GUI, but a hostile
 * keyboard/input value must not be able to inject code). */
int jd_fire_event(js_context *ctx, dom_node_id node_id,
                  const char *event_type,
                  const char *key, int key_code,
                  const char *value) {
    if (ctx == NULL || node_id == DOM_NODE_NONE || event_type == NULL) return 1;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return 1;

    /* Sanitise the event_type string: must be a simple identifier (no injection). */
    for (const char *p = event_type; *p != '\0'; ++p) {
        if (!((*p >= 'a' && *p <= 'z') || *p == '_')) return 1;
    }

    /* Escape key and value strings to prevent JS injection. */
    char escaped_key[128];
    char escaped_val[512];
    if (key != NULL) jd_escape_js_str(key, escaped_key, sizeof escaped_key);
    else escaped_key[0] = '\0';
    if (value != NULL) jd_escape_js_str(value, escaped_val, sizeof escaped_val);
    else escaped_val[0] = '\0';

    /* Build: __dispatchEvent(NODE_ID, "event_type", {key: "...", keyCode: N, value: "..."}) */
    char src[1536];
    int n;
    if (key != NULL && key[0] != '\0' && value != NULL && value[0] != '\0') {
        n = snprintf(src, sizeof src,
            "__dispatchEvent(%u,\"%s\",{key:\"%s\",keyCode:%d,value:\"%s\"})",
            (unsigned)node_id, event_type, escaped_key, key_code, escaped_val);
    } else if (key != NULL && key[0] != '\0') {
        n = snprintf(src, sizeof src,
            "__dispatchEvent(%u,\"%s\",{key:\"%s\",keyCode:%d})",
            (unsigned)node_id, event_type, escaped_key, key_code);
    } else if (value != NULL && value[0] != '\0') {
        n = snprintf(src, sizeof src,
            "__dispatchEvent(%u,\"%s\",{value:\"%s\"})",
            (unsigned)node_id, event_type, escaped_val);
    } else {
        n = snprintf(src, sizeof src,
            "__dispatchEvent(%u,\"%s\",{keyCode:%d})",
            (unsigned)node_id, event_type, key_code);
    }
    if (n < 0 || (size_t)n >= sizeof src) return 1;

    return jd_eval_default_action(jsctx, src, (size_t)n, "<event-fire>");
}

int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,
                        const char *event_type,
                        int client_x, int client_y, int button) {
    if (ctx == NULL || node_id == DOM_NODE_NONE || event_type == NULL) return 1;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return 1;

    /* Sanitise the event_type string. */
    for (const char *p = event_type; *p != '\0'; ++p) {
        if (!((*p >= 'a' && *p <= 'z') || *p == '_')) return 1;
    }

    char src[1536];
    int n = snprintf(src, sizeof src,
        "__dispatchEvent(%u,\"%s\",{clientX:%d,clientY:%d,button:%d})",
        (unsigned)node_id, event_type, client_x, client_y, button);
    if (n < 0 || (size_t)n >= sizeof src) return 1;

    return jd_eval_default_action(jsctx, src, (size_t)n, "<mouse-event>");
}
