/*
 * js_dom — implementation of the DOM <-> JS bridge.
 *
 * Installs a frozen, read-only `dom` global into a js_sandbox context. The
 * dom_index lives in the engine's context opaque (unreachable from JS); native
 * functions retrieve it and proxy to the dom queries. Nodes are opaque integer
 * handles validated on every call; no live engine/node object is exposed.
 */

#define _GNU_SOURCE

#include "js_dom.h"

#include "dom.h"
#include "freebug.h"
#include "html_parse.h"
#include "js_sandbox.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "quickjs.h"
#include "web_storage.h"
#include "js_dom_internal.h"

jd_opaque *jd_opaque_get(JSContext *ctx) {
    return (jd_opaque *)JS_GetContextOpaque(ctx);
}

dom_index *jd_idx(JSContext *ctx) {
    jd_opaque *o = jd_opaque_get(ctx);
    return (o != NULL) ? o->idx : NULL;
}


/* Coerces a JS argument to a node handle. Returns -1 with a pending exception
 * if coercion threw; otherwise stores the handle (out-of-range values stay
 * out of range and are rejected later by the dom validators). */
int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out) {
    int64_t n;
    if (JS_ToInt64(ctx, &n, v) != 0) return -1;
    *out = (n < 0 || n > 0xFFFFFFFELL) ? DOM_NODE_NONE : (dom_node_id)n;
    return 0;
}

JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h) {
    return (h == DOM_NODE_NONE) ? JS_NULL : JS_NewInt64(ctx, (int64_t)h);
}

/* --- native methods --- */

static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,
                            int argc, JSValueConst *argv) {
    (void)this_val; (void)argc; (void)argv;
    return JS_NewInt64(ctx, (int64_t)dom_node_count(jd_idx(ctx)));
}

static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val,
                                   int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    const char *s = JS_ToCString(ctx, argv[0]);
    if (s == NULL) return JS_EXCEPTION;
    dom_node_id h = dom_get_element_by_id(jd_idx(ctx), s);
    JS_FreeCString(ctx, s);
    return jd_handle_or_null(ctx, h);
}

/* Shared body for getByTag / getByClass (by_class selected by the flag). */
static JSValue jd_query_list(JSContext *ctx, JSValueConst arg, int by_class) {
    const dom_index *idx = jd_idx(ctx);
    const char *s = JS_ToCString(ctx, arg);
    if (s == NULL) return JS_EXCEPTION;

    size_t total = by_class ? dom_get_by_class(idx, s, NULL, 0)
                            : dom_get_by_tag(idx, s, NULL, 0);

    JSValue arr = JS_NewArray(ctx);
    if (JS_IsException(arr)) { JS_FreeCString(ctx, s); return arr; }

    if (total > 0) {
        dom_node_id *buf = (dom_node_id *)calloc(total, sizeof *buf);
        if (buf == NULL) {
            JS_FreeCString(ctx, s);
            JS_FreeValue(ctx, arr);
            return JS_ThrowOutOfMemory(ctx);
        }
        size_t n = by_class ? dom_get_by_class(idx, s, buf, total)
                            : dom_get_by_tag(idx, s, buf, total);
        if (n > total) n = total;
        for (size_t i = 0; i < n; ++i) {
            JS_SetPropertyUint32(ctx, arr, (uint32_t)i, JS_NewInt64(ctx, (int64_t)buf[i]));
        }
        free(buf);
    }
    JS_FreeCString(ctx, s);
    return arr;
}

static JSValue m_get_by_tag(JSContext *ctx, JSValueConst this_val,
                            int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    return jd_query_list(ctx, argv[0], 0);
}

static JSValue m_get_by_class(JSContext *ctx, JSValueConst this_val,
                              int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    return jd_query_list(ctx, argv[0], 1);
}

static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,
                          int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    size_t len = 0;
    const char *t = dom_tag_name(jd_idx(ctx), h, &len);
    return (t == NULL) ? JS_NULL : JS_NewStringLen(ctx, t, len);
}

static JSValue m_get_attribute(JSContext *ctx, JSValueConst this_val,
                               int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    const char *name = JS_ToCString(ctx, argv[1]);
    if (name == NULL) return JS_EXCEPTION;
    size_t len = 0;
    const char *v = dom_get_attribute(jd_idx(ctx), h, name, &len);
    JS_FreeCString(ctx, name);
    return (v == NULL) ? JS_NULL : JS_NewStringLen(ctx, v, len);
}

static JSValue m_parent(JSContext *ctx, JSValueConst this_val,
                        int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    return jd_handle_or_null(ctx, dom_parent(jd_idx(ctx), h));
}

static JSValue m_first_child(JSContext *ctx, JSValueConst this_val,
                             int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    return jd_handle_or_null(ctx, dom_first_child(jd_idx(ctx), h));
}

/* Node-level navigation (text and comments included, spec/dom.md 9). */
static JSValue m_node_kind(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    return JS_NewInt32(ctx, dom_node_kind(jd_idx(ctx), h));
}

static JSValue m_child_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    return jd_handle_or_null(ctx, dom_child_node(jd_idx(ctx), h, JS_ToBool(ctx, argv[1])));
}

static JSValue m_sibling_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    return jd_handle_or_null(ctx, dom_sibling_node(jd_idx(ctx), h, JS_ToBool(ctx, argv[1])));
}

/* dom.createChar(kind 3|8, text): a detached text/comment node handle. */
static JSValue m_create_char(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    int32_t kind = 0;
    if (JS_ToInt32(ctx, &kind, argv[0]) != 0) return JS_EXCEPTION;
    size_t len = 0;
    const char *t = JS_ToCStringLen(ctx, &len, argv[1]);
    if (t == NULL) return JS_EXCEPTION;
    dom_node_id id = DOM_NODE_NONE;
    dom_status st = dom_create_char_node(jd_idx(ctx), kind, t, len, &id);
    JS_FreeCString(ctx, t);
    if (st == DOM_ERR_OOM) return JS_ThrowOutOfMemory(ctx);
    return jd_handle_or_null(ctx, st == DOM_OK ? id : DOM_NODE_NONE);
}

static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,
                              int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    return jd_handle_or_null(ctx, dom_next_sibling(jd_idx(ctx), h));
}

static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,
                          int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id a, b;
    if (jd_handle(ctx, argv[0], &a) < 0) return JS_EXCEPTION;
    if (jd_handle(ctx, argv[1], &b) < 0) return JS_EXCEPTION;
    return JS_NewBool(ctx, dom_precedes(jd_idx(ctx), a, b));
}

/* --- mutators (live JS): backed by the memory-safe dom_set_* (detach, never free) --- */

static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,
                              int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    size_t len = 0;
    const char *t = dom_text_content(jd_idx(ctx), h, &len);
    return (t == NULL) ? JS_NewString(ctx, "") : JS_NewStringLen(ctx, t, len);
}

static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,
                          int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    size_t len = 0;
    const char *s = JS_ToCStringLen(ctx, &len, argv[1]);
    if (s == NULL) return JS_EXCEPTION;
    dom_status st = dom_set_text_content(jd_idx(ctx), h, s, len);
    JS_FreeCString(ctx, s);
    if (st == DOM_ERR_OOM) return JS_ThrowOutOfMemory(ctx);
    return JS_UNDEFINED;
}

static JSValue m_get_title(JSContext *ctx, JSValueConst this_val,
                           int argc, JSValueConst *argv) {
    (void)this_val; (void)argc; (void)argv;
    size_t len = 0;
    const char *t = dom_document_title(jd_idx(ctx), &len);
    return (t == NULL) ? JS_NewString(ctx, "") : JS_NewStringLen(ctx, t, len);
}

static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,
                           int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    size_t len = 0;
    const char *s = JS_ToCStringLen(ctx, &len, argv[0]);
    if (s == NULL) return JS_EXCEPTION;
    (void)dom_set_document_title(jd_idx(ctx), s, len);
    JS_FreeCString(ctx, s);
    return JS_UNDEFINED;
}

/* --- DOM construction (live JS, Hito 20c) --- */

static JSValue m_create_element(JSContext *ctx, JSValueConst this_val,
                               int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    const char *tag = JS_ToCString(ctx, argv[0]);
    if (tag == NULL) return JS_EXCEPTION;
    dom_node_id id = DOM_NODE_NONE;
    dom_status st = dom_create_element(jd_idx(ctx), tag, &id);
    JS_FreeCString(ctx, tag);
    if (st == DOM_ERR_OOM) return JS_ThrowOutOfMemory(ctx);
    return jd_handle_or_null(ctx, id);
}

static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,
                             int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id p, c;
    if (jd_handle(ctx, argv[0], &p) < 0 || jd_handle(ctx, argv[1], &c) < 0)
        return JS_EXCEPTION;
    return JS_NewBool(ctx, dom_append_child(jd_idx(ctx), p, c) == DOM_OK);
}

/* dom.moveChildren(src, parent, where, ref|null): every child node of src (text
 * included) into parent at where (0 end, 1 start, 2 before ref, 3 after ref). */
static JSValue m_move_children(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    (void)this_val;
    dom_node_id src, parent, ref = DOM_NODE_NONE;
    int32_t where = 0;
    if (argc < 3 || jd_handle(ctx, argv[0], &src) < 0 || jd_handle(ctx, argv[1], &parent) < 0
        || JS_ToInt32(ctx, &where, argv[2]) != 0)
        return JS_EXCEPTION;
    if (argc > 3 && !JS_IsNull(argv[3]) && !JS_IsUndefined(argv[3]) && jd_handle(ctx, argv[3], &ref) < 0)
        return JS_EXCEPTION;
    if (where < DOM_AT_END || where > DOM_AFTER_REF) return JS_FALSE;
    return JS_NewBool(ctx, dom_move_children(jd_idx(ctx), src, parent, (dom_place)where, ref) == DOM_OK);
}

/* dom.cloneNode(h, deep): a detached, indexed clone (text included), or null. */
static JSValue m_clone_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    (void)this_val;
    dom_node_id h, out = DOM_NODE_NONE;
    if (argc < 1 || jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    int deep = (argc > 1) ? JS_ToBool(ctx, argv[1]) : 0;
    if (dom_clone_node(jd_idx(ctx), h, deep, &out) != DOM_OK) return JS_NULL;
    return jd_handle_or_null(ctx, out);
}

/* dom.insertBefore(parent, child, ref|null): ordered insertion (null appends). */
static JSValue m_insert_before(JSContext *ctx, JSValueConst this_val,
                               int argc, JSValueConst *argv) {
    (void)this_val;
    dom_node_id p, c, r = DOM_NODE_NONE;
    if (argc < 2 || jd_handle(ctx, argv[0], &p) < 0 || jd_handle(ctx, argv[1], &c) < 0)
        return JS_EXCEPTION;
    if (argc > 2 && !JS_IsNull(argv[2]) && !JS_IsUndefined(argv[2])
        && jd_handle(ctx, argv[2], &r) < 0)
        return JS_EXCEPTION;
    return JS_NewBool(ctx, dom_insert_before(jd_idx(ctx), p, c, r) == DOM_OK);
}

static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,
                             int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id p, c;
    if (jd_handle(ctx, argv[0], &p) < 0 || jd_handle(ctx, argv[1], &c) < 0)
        return JS_EXCEPTION;
    return JS_NewBool(ctx, dom_remove_child(jd_idx(ctx), p, c) == DOM_OK);
}

static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,
                              int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    const char *name = JS_ToCString(ctx, argv[1]);
    if (name == NULL) return JS_EXCEPTION;
    const char *val = JS_ToCString(ctx, argv[2]);
    if (val == NULL) { JS_FreeCString(ctx, name); return JS_EXCEPTION; }
    dom_status st = dom_set_attribute(jd_idx(ctx), h, name, val);
    JS_FreeCString(ctx, name);
    JS_FreeCString(ctx, val);
    if (st == DOM_ERR_OOM) return JS_ThrowOutOfMemory(ctx);
    return JS_UNDEFINED;
}

static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,
                                  int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    const char *name = JS_ToCString(ctx, argv[1]);
    if (name == NULL) return JS_EXCEPTION;
    (void)dom_remove_attribute(jd_idx(ctx), h, name);
    JS_FreeCString(ctx, name);
    return JS_UNDEFINED;
}

static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,
                                int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    size_t len = 0;
    const char *s = JS_ToCStringLen(ctx, &len, argv[1]);
    if (s == NULL) return JS_EXCEPTION;
    dom_status st = dom_set_inner_html(jd_idx(ctx), h, s, len);
    JS_FreeCString(ctx, s);
    if (st == DOM_ERR_OOM) return JS_ThrowOutOfMemory(ctx);
    return JS_UNDEFINED;
}

/* innerHTML getter (2026-07-11): serializes the node's children (bounded in dom.c;
 * over-cap or invalid handle yields "" -- a getter never throws page scripts dead). */
static JSValue m_get_inner_html(JSContext *ctx, JSValueConst this_val,
                                int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    char *html = NULL;
    size_t len = 0;
    if (dom_get_inner_html(jd_idx(ctx), h, &html, &len) != DOM_OK)
        return JS_NewString(ctx, "");
    JSValue v = JS_NewStringLen(ctx, html, len);
    free(html);
    return v;
}

#include "js_location_internal.h"
#include "js_dom_ext.h"

/* dom.u8len(s): UTF-8 byte length of String(s) -- the unit the localStorage quota is
 * measured in (spec/web_storage.md). Native: a per-character JS loop over a large
 * value is a real cost on every setItem. */
static JSValue m_u8len(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    (void)this_val;
    if (argc < 1) return JS_NewInt64(ctx, 0);
    size_t n = 0;
    const char *s = JS_ToCStringLen(ctx, &n, argv[0]);
    if (s == NULL) return JS_EXCEPTION;
    JS_FreeCString(ctx, s);
    return JS_NewInt64(ctx, (int64_t)n);
}

/* dom.rect(h): [x, y, w, h] of h in document coordinates from the installed
 * layout geometry, or null (no table, or the layout produced no box for h). */
static JSValue m_rect(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    jd_opaque *o = jd_opaque_get(ctx);
    const jg_rect *r = (o != NULL) ? jg_find(o->geom, h) : NULL;
    if (r == NULL) return JS_NULL;
    JSValue a = JS_NewArray(ctx);
    if (JS_IsException(a)) return a;
    const int32_t v[4] = { r->x, r->y, r->w, r->h };
    for (uint32_t i = 0; i < 4; ++i)
        JS_SetPropertyUint32(ctx, a, i, JS_NewInt32(ctx, v[i]));
    return a;
}

/* dom.viewport(): [scroll_x, scroll_y, view_w, view_h, doc_w, doc_h], or null when
 * no geometry is installed (untrusted host: callers keep the normalized values). */
static JSValue m_viewport(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    (void)this_val; (void)argc; (void)argv;
    jd_opaque *o = jd_opaque_get(ctx);
    const jg_table *g = (o != NULL) ? o->geom : NULL;
    if (g == NULL) return JS_NULL;
    JSValue a = JS_NewArray(ctx);
    if (JS_IsException(a)) return a;
    const int32_t v[6] = { g->scroll_x, g->scroll_y, g->view_w, g->view_h, g->doc_w, g->doc_h };
    for (uint32_t i = 0; i < 6; ++i)
        JS_SetPropertyUint32(ctx, a, i, JS_NewInt32(ctx, v[i]));
    return a;
}

/* --- install --- */

typedef struct jd_method {
    const char *name;
    JSCFunction *fn;
    int          nargs;
} jd_method;

/* --- CSS-selector queries (querySelector / matches / closest) --- */

/* dom.querySelector(root, sel): root is a handle or -1 for document scope. */
static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,
                                int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id root;
    if (jd_handle(ctx, argv[0], &root) < 0) return JS_EXCEPTION;
    const char *sel = JS_ToCString(ctx, argv[1]);
    if (sel == NULL) return JS_EXCEPTION;
    dom_node_id h = dom_query_selector(jd_idx(ctx), root, sel);
    JS_FreeCString(ctx, sel);
    return jd_handle_or_null(ctx, h);
}

/* dom.querySelectorAll(root, sel) -> array of handles. */
static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,
                                    int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id root;
    if (jd_handle(ctx, argv[0], &root) < 0) return JS_EXCEPTION;
    const char *sel = JS_ToCString(ctx, argv[1]);
    if (sel == NULL) return JS_EXCEPTION;
    const dom_index *idx = jd_idx(ctx);
    size_t total = dom_query_selector_all(idx, root, sel, NULL, 0);

    JSValue arr = JS_NewArray(ctx);
    if (JS_IsException(arr)) { JS_FreeCString(ctx, sel); return arr; }
    if (total > 0) {
        dom_node_id *buf = (dom_node_id *)calloc(total, sizeof *buf);
        if (buf == NULL) {
            JS_FreeCString(ctx, sel);
            JS_FreeValue(ctx, arr);
            return JS_ThrowOutOfMemory(ctx);
        }
        size_t n = dom_query_selector_all(idx, root, sel, buf, total);
        if (n > total) n = total;
        for (size_t i = 0; i < n; ++i)
            JS_SetPropertyUint32(ctx, arr, (uint32_t)i, JS_NewInt64(ctx, (int64_t)buf[i]));
        free(buf);
    }
    JS_FreeCString(ctx, sel);
    return arr;
}

static JSValue m_matches(JSContext *ctx, JSValueConst this_val,
                         int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    const char *sel = JS_ToCString(ctx, argv[1]);
    if (sel == NULL) return JS_EXCEPTION;
    int m = dom_matches(jd_idx(ctx), h, sel);
    JS_FreeCString(ctx, sel);
    return JS_NewBool(ctx, m);
}

static JSValue m_closest(JSContext *ctx, JSValueConst this_val,
                         int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    const char *sel = JS_ToCString(ctx, argv[1]);
    if (sel == NULL) return JS_EXCEPTION;
    dom_node_id r = dom_closest(jd_idx(ctx), h, sel);
    JS_FreeCString(ctx, sel);
    return jd_handle_or_null(ctx, r);
}

static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,
                            int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    enum { CAP = 256 };
    const char *names[CAP];
    size_t lens[CAP];
    size_t n = dom_attribute_names(jd_idx(ctx), h, names, lens, CAP);
    if (n > CAP) n = CAP;
    JSValue arr = JS_NewArray(ctx);
    if (JS_IsException(arr)) return arr;
    for (size_t i = 0; i < n; i++) {
        JS_SetPropertyUint32(ctx, arr, (uint32_t)i,
                             JS_NewStringLen(ctx, names[i], lens[i]));
    }
    return arr;
}

static const jd_method JD_METHODS[] = {
    { "attrNames",      m_attr_names,        1 },
    { "nodeCount",      m_node_count,        0 },
    { "getElementById", m_get_element_by_id, 1 },
    { "getByTag",       m_get_by_tag,        1 },
    { "getByClass",     m_get_by_class,      1 },
    { "tagName",        m_tag_name,          1 },
    { "getAttribute",   m_get_attribute,     2 },
    { "parent",         m_parent,            1 },
    { "firstChild",     m_first_child,       1 },
    { "nextSibling",    m_next_sibling,      1 },
    { "nodeKind",       m_node_kind,         1 },
    { "childNode",      m_child_node,        2 },
    { "siblingNode",    m_sibling_node,      2 },
    { "createChar",     m_create_char,       2 },
    { "precedes",       m_precedes,          2 },
    { "textContent",    m_text_content,      1 },
    { "setText",        m_set_text,          2 },
    { "getTitle",       m_get_title,         0 },
    { "setTitle",       m_set_title,         1 },
    { "createElement",  m_create_element,    1 },
    { "appendChild",    m_append_child,      2 },
    { "insertBefore",   m_insert_before,     3 },
    { "cloneNode",      m_clone_node,        2 },
    { "moveChildren",   m_move_children,     4 },
    { "removeChild",    m_remove_child,      2 },
    { "setAttribute",   m_set_attribute,     3 },
    { "removeAttribute", m_remove_attribute, 2 },
    { "setInnerHtml",   m_set_inner_html,    2 },
    { "getInnerHtml",   m_get_inner_html,    1 },
    { "querySelector",    m_query_selector,     2 },
    { "querySelectorAll", m_query_selector_all, 2 },
    { "matches",          m_matches,            2 },
    { "closest",          m_closest,            2 },
    { "rect",             m_rect,               1 },
    { "viewport",         m_viewport,           0 },
    { "histTarget",       jl_m_hist_target,     2 },
    { "u8len",            m_u8len,              1 },
};

/* A small standard `document` facade over the native handle API, so real page
 * scripts ("document.title = ...", "document.getElementById('x').textContent = ...")
 * work without exposing live engine node objects. Element wrappers carry only the
 * validated integer handle and proxy to the sealed `dom` methods. A no-op console
 * and window=globalThis keep common scripts from dying on a ReferenceError. */
static const char JD_DOCUMENT_SHIM[] =
    "(function(){"
    "  var __wc={};"                          /* handle -> wrapper: stable node identity (===) */
    /* Layout geometry (spec/js_geom.md): real only when the trusted parent installed
     * a table (dom.viewport() non-null); otherwise every measurement is zero. */
    /* ParentNode/ChildNode insertion: a fragment contributes its collected children
     * (and is emptied); an element wrapper contributes itself. Every insertion is the
     * ordered native dom.insertBefore (ref null = append). */
    "  function nodesOf(a){ if(a&&a.__frag){ var l=a.__frag.slice(); a.__frag.length=0; return l; }"
    "    if(typeof a==='string'){ var t=dom.createChar(3,a); return t===null?[]:[wrap(t)]; }"
    "    return (a&&a._h!==undefined)?[a]:[]; }"
    "  function insAt(p,list,ref){ for(var i=0;i<list.length;i++)"
    "    if(list[i]&&list[i]._h!==undefined) dom.insertBefore(p,list[i]._h,ref); }"
    "  function gRect(h){ return dom.rect(h)||[0,0,0,0]; }"
    "  function mkRect(x,y,w,ht){ var o={x:x,y:y,left:x,top:y,width:w,height:ht,right:x+w,bottom:y+ht};"
    "    o.toJSON=function(){ return {x:x,y:y,left:x,top:y,width:w,height:ht,right:x+w,bottom:y+ht}; };"
    "    return o; }"
    "  function gBox(h){ var r=dom.rect(h), v=dom.viewport(); if(!r||!v) return mkRect(0,0,0,0);"
    "    return mkRect(r[0]-v[0],r[1]-v[1],r[2],r[3]); }"
    /* <html>/<body> report the viewport/document for client/scroll metrics. */
    "  function gRoot(h){ var t=dom.tagName(h); t=t?String(t).toLowerCase():'';"
    "    return (t==='html'||t==='body')?dom.viewport():null; }"
    "  function wrap(h){"
    "    if (h===null||h===undefined) return null;"
    "    if (h in __wc) return __wc[h];"
    /* Text / comment handles get their own wrapper (js_dom_ext __wrapChar). */
    "    var kd=dom.nodeKind(h);"
    "    if ((kd===3||kd===8)&&typeof __G.__wrapChar==='function') return (__wc[h]=__G.__wrapChar(h,kd));"
    "    var el={_h:h, nodeType:1, ELEMENT_NODE:1, nodeName:'',"
    "      get textContent(){ return dom.textContent(h); },"
    /* ownerDocument: needed by jQuery's buildFragment to access document methods
     * from any element's context (elem.ownerDocument.createDocumentFragment()). */
    "      get ownerDocument(){ return document; },"
    "      set textContent(v){ dom.setText(h, String(v)); },"
    "      getAttribute: function(n){ return dom.getAttribute(h, String(n)); },"
    "      setAttribute: function(n,v){ dom.setAttribute(h, String(n), String(v)); },"
    "      removeAttribute: function(n){ dom.removeAttribute(h, String(n)); },"
    "      hasAttribute: function(n){ return dom.getAttribute(h, String(n))!==null; },"
    "      getAttributeNames: function(){ return dom.attrNames(h); },"
    "      hasAttributes: function(){ return dom.attrNames(h).length>0; },"
    /* attributes: a NamedNodeMap-ish view backed by the sealed dom methods.
     * Named access (attrs['onsubmit']) and indexed access (attrs[0]) both return
     * a minimal attr node {name,value,specified}; length/enumeration come from the
     * native attrNames(). jQuery's feature detection reads attrs[name].expando, so
     * a missing 'attributes' aborted the whole library bundle. Identity-safe: only
     * this element's own attributes, never anything else. */
    "      get attributes(){"
    "        function node(nm){ var v=dom.getAttribute(h,nm); if(v===null) return undefined;"
    "          return {name:nm,nodeName:nm,localName:nm,value:v,nodeValue:v,specified:true,expando:undefined}; }"
    "        return new Proxy({}, {"
    "          get:function(t,p){ if(p==='length') return dom.attrNames(h).length;"
    "            if(p==='getNamedItem') return function(nm){ var r=node(String(nm)); return r===undefined?null:r; };"
    "            if(p==='item') return function(i){ var ns=dom.attrNames(h); return i>=0&&i<ns.length?node(ns[i]):null; };"
    "            if(typeof p==='symbol') return undefined;"
    "            if(/^[0-9]+$/.test(p)){ var ns=dom.attrNames(h); var i=+p; return i<ns.length?node(ns[i]):undefined; }"
    "            return node(String(p)); },"
    "          has:function(t,p){ if(typeof p!=='string') return false; return dom.getAttribute(h,p)!==null; },"
    "          ownKeys:function(){ var ns=dom.attrNames(h),k=[]; for(var i=0;i<ns.length;i++) k.push(String(i)); k.push('length'); return k; },"
    "          getOwnPropertyDescriptor:function(t,p){ return {enumerable:/^[0-9]+$/.test(p),configurable:true}; } }); },"
    /* dataset: data-* attributes via a Proxy, so reads like el.dataset.fooBar map to
     * the data-foo-bar attribute (missing => undefined, never a throw). Identity-safe:
     * only this element's own attributes, no enumeration of anything else. */
    "      get dataset(){ return new Proxy({}, {"
    "        get:function(t,p){ if(typeof p!=='string') return undefined;"
    "          var k='data-'+p.replace(/[A-Z]/g,function(m){return '-'+m.toLowerCase();});"
    "          var v=dom.getAttribute(h,k); return v===null?undefined:v; },"
    "        has:function(t,p){ if(typeof p!=='string') return false;"
    "          var k='data-'+p.replace(/[A-Z]/g,function(m){return '-'+m.toLowerCase();});"
    "          return dom.getAttribute(h,k)!==null; },"
    "        set:function(t,p,v){ if(typeof p==='string'){"
    "          var k='data-'+p.replace(/[A-Z]/g,function(m){return '-'+m.toLowerCase();});"
    "          dom.setAttribute(h,k,String(v)); } return true; } }); },"
     /* src/href reflect the attribute as a string ('' when absent) so common idioms
      * (img.src.substring(...), a.href) never read a property of undefined. The raw
      * attribute is returned (not a resolved absolute URL): no base-URL leak into JS. */
     "      get src(){ var v=dom.getAttribute(h,'src'); return v===null?'':v; },"
     "      set src(v){ dom.setAttribute(h,'src',String(v)); },"
     "      get href(){ var v=dom.getAttribute(h,'href'); return v===null?'':v; },"
     "      set href(v){ dom.setAttribute(h,'href',String(v)); },"
     /* Form element properties (jQuery/Bootstrap feature detection needs these).
      * checked/value/type/disabled map to their attributes; defaultChecked/selected
      * fall back to the attribute when the property itself is unset. These are
      * identity-safe: they expose ONLY this element's own attributes, never anything
      * else, and the attribute values come from the document data with provenance. */
     "      get checked(){ var v=dom.getAttribute(h,'checked'); return v!==null; },"
     "      set checked(v){ if(v) dom.setAttribute(h,'checked','checked'); else dom.removeAttribute(h,'checked'); },"
     "      get value(){ var v=dom.getAttribute(h,'value'); return v===null?'':v; },"
     "      set value(v){ dom.setAttribute(h,'value',String(v)); },"
     "      get type(){ var v=dom.getAttribute(h,'type'); return v===null?'text':v; },"
     "      set type(v){ dom.setAttribute(h,'type',String(v)); },"
     "      get disabled(){ var v=dom.getAttribute(h,'disabled'); return v!==null; },"
     "      set disabled(v){ if(v) dom.setAttribute(h,'disabled','disabled'); else dom.removeAttribute(h,'disabled'); },"
     "      get selected(){ var v=dom.getAttribute(h,'selected'); return v!==null; },"
     "      set selected(v){ if(v) dom.setAttribute(h,'selected','selected'); else dom.removeAttribute(h,'selected'); },"
     "      get tagName(){ var t=dom.tagName(h); return t===null?null:String(t).toUpperCase(); },"
    "      get id(){ var v=dom.getAttribute(h,'id'); return v===null?'':v; },"
    "      set id(v){ dom.setAttribute(h,'id',String(v)); },"
    "      get className(){ var v=dom.getAttribute(h,'class'); return v===null?'':v; },"
    "      set className(v){ dom.setAttribute(h,'class',String(v)); },"
     "      set innerHTML(v){ dom.setInnerHtml(h, String(v)); },"
     "      get innerHTML(){ return dom.getInnerHtml(h); },"
     "      get innerText(){ return dom.textContent(h); },"
     "      set innerText(v){ dom.setText(h, String(v)); },"
    /* A DocumentFragment carries its collected children in __frag; appending the
     * fragment re-parents each child (its contents), never the fragment node. */
    "      appendChild: function(c){ insAt(h,nodesOf(c),null); return c; },"
    "      removeChild: function(c){ if(c&&c._h!==undefined) dom.removeChild(h,c._h); return c; },"
    "      insertBefore: function(n,ref){ insAt(h,nodesOf(n),(ref&&ref._h!==undefined)?ref._h:null); return n; },"
    "      replaceChild: function(nw,old){ if(old&&old._h!==undefined&&dom.parent(old._h)===h){"
    "        insAt(h,nodesOf(nw),old._h); dom.removeChild(h,old._h); } return old; },"
    "      append: function(){ for(var i=0;i<arguments.length;i++) insAt(h,nodesOf(arguments[i]),null); },"
    "      prepend: function(){ var f=dom.childNode(h,false);"
    "        for(var i=0;i<arguments.length;i++) insAt(h,nodesOf(arguments[i]),f); },"
    "      before: function(){ var p=dom.parent(h); if(p===null) return;"
    "        for(var i=0;i<arguments.length;i++) insAt(p,nodesOf(arguments[i]),h); },"
    "      after: function(){ var p=dom.parent(h); if(p===null) return; var nx=dom.siblingNode(h,false);"
    "        for(var i=0;i<arguments.length;i++) insAt(p,nodesOf(arguments[i]),nx); },"
    "      replaceWith: function(){ var p=dom.parent(h); if(p===null) return; var nx=dom.siblingNode(h,false);"
    "        dom.removeChild(p,h); for(var i=0;i<arguments.length;i++) insAt(p,nodesOf(arguments[i]),nx); },"
    "      replaceChildren: function(){ var c=dom.childNode(h,false), guard=0;"
    "        while(c!==null&&guard++<100000){ dom.removeChild(h,c); c=dom.childNode(h,false); }"
    "        for(var i=0;i<arguments.length;i++) insAt(h,nodesOf(arguments[i]),null); },"
    "      remove: function(){ var p=dom.parent(h); if(p!==null) dom.removeChild(p,h); },"
     "      cloneNode: function(deep){ var c=dom.cloneNode(h, !!deep); return c===null?null:wrap(c); },"
    "      get parentNode(){ var p=dom.parent(h); return p===null?null:wrap(p); },"
    "      get parentElement(){ var p=dom.parent(h); return p===null?null:wrap(p); },"
    "      get firstChild(){ var c=dom.childNode(h,false); return c===null?null:wrap(c); },"
    "      get firstElementChild(){ var c=dom.firstChild(h); return c===null?null:wrap(c); },"
    "      get nextSibling(){ var s=dom.siblingNode(h,false); return s===null?null:wrap(s); },"
    "      get nextElementSibling(){ var s=dom.nextSibling(h); return s===null?null:wrap(s); },"
    "      get lastChild(){ var c=dom.childNode(h,true); return c===null?null:wrap(c); },"
    "      get lastElementChild(){ var c=dom.firstChild(h),l=null; while(c!==null){ l=c; c=dom.nextSibling(c); } return l===null?null:wrap(l); },"
    "      get children(){ var r=[]; var c=dom.firstChild(h); while(c!==null){ r.push(wrap(c)); c=dom.nextSibling(c); } return r; },"
    "      get childNodes(){ var r=[]; var c=dom.childNode(h,false); while(c!==null){ r.push(wrap(c)); c=dom.siblingNode(c,false); } return r; },"
    "      get childElementCount(){ var n=0; var c=dom.firstChild(h); while(c!==null){ n++; c=dom.nextSibling(c); } return n; },"
    "      hasChildNodes: function(){ return dom.childNode(h,false)!==null; },"
    "      contains: function(o){ if(!o||o._h===undefined) return false; for(var p=o._h;p!==null&&p!==undefined;){ if(p===h) return true; p=dom.parent(p); } return false; },"
     "      getElementsByTagName: function(t){ return wrapList(dom.querySelectorAll(h, String(t))); },"
     "      getElementsByClassName: function(c){ return wrapList(dom.querySelectorAll(h, '.'+String(c))); },"
      "      addEventListener: function(t,fn,o){ __G.__evAdd('n'+h,t,fn,o); },"
      "      removeEventListener: function(t,fn,o){ __G.__evRemove('n'+h,t,fn,o); },"
      "      dispatchEvent: function(ev){ return __G.__evDispatch('n'+h,ev); },"
    "      querySelector: function(s){ return wrap(dom.querySelector(h, String(s))); },"
    "      querySelectorAll: function(s){ return wrapList(dom.querySelectorAll(h, String(s))); },"
    "      matches: function(s){ return dom.matches(h, String(s)); },"
    "      webkitMatchesSelector: function(s){ return dom.matches(h, String(s)); },"
    "      closest: function(s){ return wrap(dom.closest(h, String(s))); },"
    "      focus: function(){}, blur: function(){}, click: function(){},"
     "      scrollIntoView: function(){},"
     "      getBoundingClientRect: function(){ return gBox(h); },"
     "      getClientRects: function(){ return dom.rect(h)?[gBox(h)]:[]; },"
      "      get offsetWidth(){ return gRect(h)[2]; }, get offsetHeight(){ return gRect(h)[3]; },"
      "      get offsetLeft(){ return gRect(h)[0]; }, get offsetTop(){ return gRect(h)[1]; },"
      "      get offsetParent(){ return dom.rect(h)?__G.document.body:null; },"
      "      get clientWidth(){ var v=gRoot(h); return v?v[2]:gRect(h)[2]; },"
      "      get clientHeight(){ var v=gRoot(h); return v?v[3]:gRect(h)[3]; },"
      "      get scrollWidth(){ var v=gRoot(h); return v?v[4]:gRect(h)[2]; },"
      "      get scrollHeight(){ var v=gRoot(h); return v?v[5]:gRect(h)[3]; },"
      "      get scrollLeft(){ var v=gRoot(h); return v?v[0]:0; },"
      "      get scrollTop(){ var v=gRoot(h); return v?v[1]:0; },"
      "      set scrollLeft(v){}, set scrollTop(v){},"
    /* classList backed by the class attribute (identity-safe: only this element). */
    "      get classList(){"
    "        function toks(){ var c=dom.getAttribute(h,'class'); return c?c.split(/\\s+/).filter(Boolean):[]; }"
    "        function put(a){ dom.setAttribute(h,'class',a.join(' ')); }"
    "        return { contains:function(x){ return toks().indexOf(String(x))>=0; },"
    "          add:function(){ var t=toks(); for(var i=0;i<arguments.length;i++){var x=String(arguments[i]); if(t.indexOf(x)<0)t.push(x);} put(t); },"
    "          remove:function(){ var t=toks(); for(var i=0;i<arguments.length;i++){var j=t.indexOf(String(arguments[i])); if(j>=0)t.splice(j,1);} put(t); },"
    "          toggle:function(x,f){ x=String(x); var t=toks(); var has=t.indexOf(x)>=0; var add=(f===undefined)?!has:!!f; if(add&&!has)t.push(x); else if(!add&&has)t.splice(t.indexOf(x),1); put(t); return add; },"
    "          replace:function(a,b){ var t=toks(); var j=t.indexOf(String(a)); if(j>=0){t[j]=String(b);put(t);return true;} return false; },"
    "          get length(){ return toks().length; }, item:function(i){ return toks()[i]||null; },"
    "          toString:function(){ return dom.getAttribute(h,'class')||''; } }; },"
    /* style: a plain settable object (el.style.color='x' works); values are kept
     * but never rendered from JS (author style is gated separately). */
    "      style:{ setProperty:function(k,v){ this[String(k)]=String(v); }, getPropertyValue:function(k){ var v=this[String(k)]; return v===undefined?'':v; }, removeProperty:function(k){ var v=this[String(k)]; delete this[String(k)]; return v===undefined?'':v; }, cssText:'' }"
    "    };"
    "    __G.__evHandlerProps(el,'n'+h,['click','submit','keydown','keyup','keypress','input','change','focus','blur',"
    "      'focusin','focusout','scroll','mousedown','mouseup','mouseover','mouseout','mousemove','mouseenter','mouseleave','wheel']);"
    /* HTMLMediaElement facade for <video>/<audio>: identity-safe stubs so
     * player scripts (canPlayType feature-detection, play/pause, muted/loop
     * reflection, buffered ranges) run without throwing. No network, no real
     * playback in the worker -- actual decoding happens in the trusted-side
     * media pipeline (spec/media_decoder.md); fixed values leak no identity. */
    "    (function(){ var tn=dom.tagName(h); tn=tn?String(tn).toLowerCase():'';"
    "      if(tn!=='video'&&tn!=='audio') return;"
    "      el.play=function(){ el.paused=false; return Promise.resolve(); };"
    "      el.pause=function(){ el.paused=true; };"
    "      el.load=function(){};"
    "      el.canPlayType=function(t){ t=String(t||'').toLowerCase();"
    "        if(t.indexOf('mp4')>=0||t.indexOf('mpegurl')>=0||t.indexOf('mp2t')>=0) return 'probably';"
    "        if(t.indexOf('webm')>=0||t.indexOf('ogg')>=0) return 'maybe'; return ''; };"
    "      el.paused=true; el.ended=false; el.seeking=false; el.currentTime=0;"
    "      el.duration=NaN; el.volume=1; el.playbackRate=1; el.defaultPlaybackRate=1;"
    "      el.readyState=0; el.networkState=0; el.error=null; el.videoWidth=0; el.videoHeight=0;"
    "      el.HAVE_NOTHING=0; el.HAVE_METADATA=1; el.HAVE_CURRENT_DATA=2; el.HAVE_FUTURE_DATA=3; el.HAVE_ENOUGH_DATA=4;"
    "      el.NETWORK_EMPTY=0; el.NETWORK_IDLE=1; el.NETWORK_LOADING=2; el.NETWORK_NO_SOURCE=3;"
    "      var tr={length:0,start:function(){return 0;},end:function(){return 0;}};"
    "      el.buffered=tr; el.played=tr; el.seekable=tr;"
    "      el.textTracks={length:0,onaddtrack:null};"
    "      el.addTextTrack=function(){ return {mode:'disabled',cues:[],addCue:function(){},removeCue:function(){}}; };"
    "      function battr(nm){ Object.defineProperty(el,nm,{get:function(){return dom.getAttribute(h,nm)!==null;},"
    "        set:function(v){ if(v) dom.setAttribute(h,nm,nm); else dom.removeAttribute(h,nm); }}); }"
    "      battr('muted'); battr('autoplay'); battr('loop'); battr('controls'); battr('playsinline');"
    "      Object.defineProperty(el,'poster',{get:function(){var v=dom.getAttribute(h,'poster');return v===null?'':v;},"
    "        set:function(v){ dom.setAttribute(h,'poster',String(v)); }});"
    "      Object.defineProperty(el,'currentSrc',{get:function(){ var v=dom.getAttribute(h,'src');"
    "        if(v!==null) return v; var s=dom.querySelector(h,'source');"
    "        if(s!==null){ var sv=dom.getAttribute(s,'src'); if(sv!==null) return sv; } return ''; }});"
    "      ['play','pause','ended','timeupdate','canplay','canplaythrough','loadedmetadata','loadeddata',"
    "       'durationchange','volumechange','playing','waiting','seeking','seeked','stalled','suspend',"
    "       'abort','emptied','ratechange'].forEach(function(t){ __G.__evHandlerProps(el,'n'+h,[t]); });"
    "    })();"
    /* instanceof HTMLElement/Element/Node/EventTarget hold for every wrapper. */
    "    if(__G.__elProto) Object.setPrototypeOf(el, __G.__elProto);"
    /* <canvas>: width/height reflect the attributes (300x150 by default); getContext
     * gives the software 2D context ('2d' only -- webgl is null, the standard "not
     * supported" answer), buffer area capped at 1 megapixel (worker memory). */
    "    (function(){ var tn=dom.tagName(h); if(!tn||String(tn).toLowerCase()!=='canvas') return;"
    "      function dim(a,d){ var v=parseInt(dom.getAttribute(h,a),10); return (isFinite(v)&&v>=0)?v:d; }"
    "      Object.defineProperty(el,'width',{get:function(){ return dim('width',300); },"
    "        set:function(v){ dom.setAttribute(h,'width',String(Math.max(0,v|0))); }});"
    "      Object.defineProperty(el,'height',{get:function(){ return dim('height',150); },"
    "        set:function(v){ dom.setAttribute(h,'height',String(Math.max(0,v|0))); }});"
    "      var c2=null;"
    "      el.getContext=function(t){ if(String(t)!=='2d') return null;"
    "        if(c2===null&&__G.__CanvasCtx){ var w=el.width, hh=el.height;"
    "          if(w*hh>1048576){ var k=Math.sqrt(1048576/(w*hh)); w=Math.floor(w*k); hh=Math.floor(hh*k); }"
    "          c2=__G.__canvasFill(new __G.__CanvasCtx(w,hh)); c2.canvas=el; }"
    "        return c2; };"
    "      el.toDataURL=function(t){ var c=el.getContext('2d'); return c?c.toDataURL(t):'data:,'; };"
    "      el.toBlob=function(cb){ if(typeof cb==='function') setTimeout(function(){ cb(null); },0); };"
    "    })();"
    /* <template>.content: one DocumentFragment per template, stable identity. */
    "    (function(){ var tn=dom.tagName(h); if(!tn||String(tn).toLowerCase()!=='template') return;"
    "      var tc=null; Object.defineProperty(el,'content',{get:function(){ if(tc===null) tc=mkFrag();"
    "        return tc; }}); })();"
    "    __wc[h]=el;"
    "    return el;"
    "  }"
    "  __G.__wrap=wrap;"
    "  function wrapList(hs){ var r=[]; for (var i=0;i<hs.length;i++) r.push(wrap(hs[i])); return r; }"
    "  __G.__wrapList=wrapList;"
    "  var loadCbs=[], timers=[];"
    "  __G.__queueTimer=function(fn){ if(typeof fn==='function') timers.push(fn); };"
    /* Page-lifecycle listeners keep their own queue, fired once by __fireDeferred.
     * Returns 1 when the type is a lifecycle type (consumed), 0 otherwise. */
    "  function isLoadType(type){ return type==='load'||type==='DOMContentLoaded'||type==='readystatechange'; }"
    /* Each entry remembers its type and target ('w' window / 'd' document) so the
     * listener receives a real event; a {handleEvent} object is a listener too. */
    "  function lcIdx(type,fn,tg){ for(var i=0;i<loadCbs.length;i++){ var c=loadCbs[i];"
    "      if(c.f===fn&&c.t===type&&c.tg===tg) return i; } return -1; }"
    "  function addL(type,fn,tg){ if(!isLoadType(type)) return 0;"
    "    if((typeof fn==='function'||(fn&&typeof fn.handleEvent==='function'))&&lcIdx(type,fn,tg)<0)"
    "      loadCbs.push({f:fn,t:type,tg:tg}); return 1; }"
    "  function delL(type,fn,tg){ if(!isLoadType(type)) return; var i=lcIdx(type,fn,tg); if(i>=0) loadCbs.splice(i,1); }"
    "  var d={"
    "    getElementById: function(id){ return wrap(dom.getElementById(String(id))); },"
    "    getElementsByTagName: function(t){ return wrapList(dom.getByTag(String(t))); },"
    "    getElementsByClassName: function(c){ return wrapList(dom.getByClass(String(c))); },"
    "    createElement: function(t){ return wrap(dom.createElement(String(t))); },"
    "    createElementCustom: function(t){ var el=wrap(dom.createElement(String(t)));"
    "      var ce=g.customElements; if(ce && ce._defs && ce._defs[t]){"
    "        try{ var ctor=ce._defs[t]; if(typeof ctor==='function'){"
    "          var inst=Object.create(ctor.prototype); ctor.call(inst);"
    "          if(typeof inst.connectedCallback==='function'){"
    "            if(!ce._pending) ce._pending=[]; ce._pending.push(inst);"
    "          }"
    "        }}catch(e){}"
    "      } return el;"
    "    },"
    "    createTextNode: function(t){ return wrap(dom.createChar(3,String(t))); },"
    "    addEventListener: function(type,fn,o){ if(!addL(String(type),fn,'d')) __G.__evAdd('d',type,fn,o); },"
    /* Node identity of the document itself: Sizzle/jQuery's setDocument gates on
     * 9===doc.nodeType && doc.documentElement before it binds its internal document
     * reference; without nodeType:9 that reference stays undefined and every later
     * doc.createElement() throws "cannot read property createElement of undefined",
     * aborting the whole library bundle. defaultView is the window it lives in. */
    "    removeEventListener: function(type,fn,o){ delL(String(type),fn,'d'); __G.__evRemove('d',type,fn,o); },"
    "    readyState:'loading',"
    "    write: function(){}, writeln: function(){}, open: function(){}, close: function(){},"
    "    nodeType:9, DOCUMENT_NODE:9, nodeName:'#document', ownerDocument:null,"
    /* createDocumentFragment: jQuery's buildFragment uses this during DOM manipulation.
     * Returns a fragment object (__frag[] accumulates appended children; when the
     * fragment is appended to a real node its children are moved, not the fragment). */
    "    createDocumentFragment: function(){ return {__frag:[], nodeType:11,"
    "      appendChild:function(c){ if(c&&c._h!==undefined) this.__frag.push(c); return c; },"
    "      firstChild:null, lastChild:null, childNodes:[], textContent:'',"
    "      querySelector:function(){return null;}, querySelectorAll:function(){return [];},"
    "      getElementById:function(){return null;}, getElementsByTagName:function(){return [];},"
    "      cloneNode:function(){return {__frag:[],nodeType:11,appendChild:function(c){if(c&&c._h!==undefined)this.__frag.push(c);return c;}};},"
    "      removeChild:function(c){return c;}, replaceChild:function(n,o){return o;},"
    "      insertBefore:function(n,ref){return n;}, hasChildNodes:function(){return false;} } },"
    "  };"
    "  Object.defineProperty(d,'defaultView',{get:function(){return __G;},enumerable:true});"
    "  Object.defineProperty(d,'title',{get:function(){return dom.getTitle();},"
    "    set:function(v){dom.setTitle(String(v));},enumerable:true});"
    "  function tagOne(t){ var a=dom.getByTag(t); return a.length?wrap(a[0]):null; }"
    "  Object.defineProperty(d,'body',{get:function(){return tagOne('body');},enumerable:true});"
    "  Object.defineProperty(d,'head',{get:function(){return tagOne('head');},enumerable:true});"
    "  Object.defineProperty(d,'documentElement',{get:function(){return tagOne('html');},enumerable:true});"
    /* document.fonts: a benign FontFaceSet stub so feature-detecting scripts that call
     * document.fonts.load(...)/ready do not throw -- the literal cause of google.com's
     * "cannot read property 'load' of undefined". Identity-neutral: fixed values, no
     * real font enumeration, never touches the network. */
    "  d.fonts={status:'loaded',size:0,ready:Promise.resolve(),"
    "    load:function(){return Promise.resolve([]);},check:function(){return true;},"
    "    add:function(){},delete:function(){},clear:function(){},forEach:function(){},"
    "    addEventListener:function(){},removeEventListener:function(){}};"
    /* Identity-safe ambient surface: no real cookie/referrer leaks, storage is
     * EPHEMERAL in-memory (Zero Knowledge -- never persisted, gone each load). */
    /* document.cookie: an in-memory session cookie jar, DISABLED by default (__ck
     * null => get returns '' and set is a no-op: identity-safe, Zero Knowledge for
     * every untrusted site). The trusted parent ENABLES and seeds it via jd_set_cookies
     * (globalThis.__ckEnable) only for a host in allow.conf AND js.conf, so a page's
     * consent/session JS (e.g. Google) can read and set cookies. Jar contents never
     * touch disk (the process holds them; gone on exit) and cross back to the parent's
     * ephemeral network jar via jd_get_cookies (globalThis.__ckDump). */
    "  var __ck=null;"
    "  function __ckSer(){ if(__ck===null) return ''; var a=[]; for(var k in __ck) if(Object.prototype.hasOwnProperty.call(__ck,k)) a.push(k+'='+__ck[k]); return a.join('; '); }"
    "  function __ckAssign(v){ if(__ck===null) return; v=String(v); var semi=v.indexOf(';');"
    "    var pair=(semi<0?v:v.substring(0,semi)); var eq=pair.indexOf('='); if(eq<0) return;"
    "    var name=pair.substring(0,eq).replace(/^\\s+|\\s+$/g,''); if(name==='') return;"
    "    var val=pair.substring(eq+1).replace(/^\\s+|\\s+$/g,'');"
    "    var attrs=(semi<0?'':v.substring(semi+1)).toLowerCase(); var del=false;"
    "    var mm=attrs.match(/max-age\\s*=\\s*(-?[0-9]+)/); if(mm&&parseInt(mm[1],10)<=0) del=true;"
    "    var me=attrs.match(/expires\\s*=\\s*([^;]+)/); if(me){ var t=Date.parse(me[1]); if(!isNaN(t)&&t<=Date.now()) del=true; }"
    "    if(del) delete __ck[name]; else __ck[name]=val; }"
    "  __G.__ckEnable=function(seed){ __ck={}; seed=String(seed||'');"
    "    var parts=seed.split(';'); for(var i=0;i<parts.length;i++){ var p=parts[i]; var eq=p.indexOf('=');"
    "      if(eq>0){ var n=p.substring(0,eq).replace(/^\\s+|\\s+$/g,''); if(n) __ck[n]=p.substring(eq+1).replace(/^\\s+|\\s+$/g,''); } } };"
    "  __G.__ckDump=function(){ return __ckSer(); };"
    "  Object.defineProperty(d,'cookie',{get:function(){return __ckSer();},set:function(v){__ckAssign(v);},enumerable:true});"
    "  Object.defineProperty(d,'referrer',{get:function(){return '';},enumerable:true});"
    "  d.querySelector=function(s){ return wrap(dom.querySelector(-1, String(s))); };"
    "  d.querySelectorAll=function(s){ return wrapList(dom.querySelectorAll(-1, String(s))); };"
    "  d.getElementsByName=function(n){ return wrapList(dom.querySelectorAll(-1, '[name=\"'+String(n).replace(/\"/g,'')+'\"]')); };"
    /* createElementNS: the namespace is ignored (SVG/MathML become plain elements),
     * enough to keep scripts that build namespaced nodes from throwing. */
    "  d.createElementNS=function(ns,t){ return wrap(dom.createElement(String(t))); };"
    "  d.createComment=function(t){ return wrap(dom.createChar(8,String(t))); };"
    /* DocumentFragment: collects appended element children in __frag; a real node's
     * appendChild/insertBefore re-parents those children (see wrap()). Complete
     * enough (cloneNode/lastChild/removeChild/insertBefore) that library feature
     * detection does not throw: jQuery clones a fragment twice and reads .lastChild
     * (b.checkClone); a missing cloneNode aborted the whole bundle -> "$ is not
     * defined". cloneNode(deep) returns a fresh fragment via mkFrag (recursively
     * cloneable), deep-cloning each child. */
    "  function mkFrag(){ var kids=[]; var f={nodeType:11, __frag:kids,"
    "    appendChild:function(c){ if(c&&c.__frag){ for(var i=0;i<c.__frag.length;i++) kids.push(c.__frag[i]); c.__frag.length=0; return c; } if(c&&c._h!==undefined) kids.push(c); return c; },"
    "    insertBefore:function(n,ref){ if(n&&n._h!==undefined){ var i=ref?kids.indexOf(ref):-1; if(i<0) kids.push(n); else kids.splice(i,0,n); } return n; },"
    "    removeChild:function(c){ var i=kids.indexOf(c); if(i>=0) kids.splice(i,1); return c; },"
    "    append:function(){ for(var i=0;i<arguments.length;i++){var a=arguments[i]; if(a&&a._h!==undefined) kids.push(a);} },"
    "    prepend:function(){ for(var i=arguments.length-1;i>=0;i--){var a=arguments[i]; if(a&&a._h!==undefined) kids.unshift(a);} },"
    "    cloneNode:function(deep){ var g2=mkFrag(); if(deep){ for(var i=0;i<kids.length;i++){ var k=kids[i]; g2.__frag.push(k&&k.cloneNode?k.cloneNode(true):k); } } return g2; },"
    "    get childNodes(){ return kids.slice(); }, get children(){ return kids.slice(); },"
    "    get firstChild(){ return kids.length?kids[0]:null; },"
    "    get lastChild(){ return kids.length?kids[kids.length-1]:null; },"
    "    get childElementCount(){ return kids.length; }, hasChildNodes:function(){ return kids.length>0; },"
    "    getElementById:function(){return null;},"
    "    querySelector:function(){return null;}, querySelectorAll:function(){return [];} }; return f; }"
    "  d.createDocumentFragment=function(){ return mkFrag(); };"
    "  d.append=function(){ var r=tagOne('html'); if(r) r.append.apply(r,arguments); };"
    "  d.prepend=function(){ var r=tagOne('html'); if(r) r.prepend.apply(r,arguments); };"
    /* Event/CustomEvent shims so new Event('x')/document.createEvent do not throw. */
    /* timeStamp is always 0: no high-resolution clock leaks through events (anti-fp).
     * __sp/__si are the stop-propagation / stop-immediate flags __evDispatch reads. */
    "  function mkEvent(type,opts){ opts=opts||{}; return {type:String(type),bubbles:!!opts.bubbles,"
    "    cancelable:!!opts.cancelable,detail:(opts.detail!==undefined?opts.detail:null),defaultPrevented:false,"
    "    target:null,currentTarget:null,eventPhase:0,isTrusted:false,timeStamp:0,__sp:false,__si:false,__path:[],"
    "    NONE:0,CAPTURING_PHASE:1,AT_TARGET:2,BUBBLING_PHASE:3,"
    "    preventDefault:function(){ if(this.cancelable) this.defaultPrevented=true; },"
    "    stopPropagation:function(){ this.__sp=true; },"
    "    stopImmediatePropagation:function(){ this.__sp=true; this.__si=true; },"
    "    composedPath:function(){ return this.__path.slice(); },"
    "    initEvent:function(t,b,c){ this.type=String(t); this.bubbles=!!b; this.cancelable=!!c; },"
    "    initCustomEvent:function(t,b,c,dt){ this.initEvent(t,b,c); this.detail=dt; }}; }"
    "  d.createEvent=function(t){ return mkEvent('',{}); };"
    "  __G.__mkEvent=mkEvent;"
    "  Object.defineProperty(d,'hidden',{get:function(){return false;},enumerable:true});"
    "  Object.defineProperty(d,'visibilityState',{get:function(){return 'visible';},enumerable:true});"
    "  d.hasFocus=function(){return true;}; d.currentScript=null;"
    "  d.characterSet='UTF-8'; d.charset='UTF-8'; d.compatMode='CSS1Compat'; d.dir='';"
    "  Object.defineProperty(d,'activeElement',{get:function(){return tagOne('body');},enumerable:true});"
    "  Object.defineProperty(d,'scripts',{get:function(){return wrapList(dom.getByTag('script'));},enumerable:true});"
    "  Object.defineProperty(d,'images',{get:function(){return wrapList(dom.getByTag('img'));},enumerable:true});"
    "  Object.defineProperty(d,'forms',{get:function(){return wrapList(dom.getByTag('form'));},enumerable:true});"
    "  Object.defineProperty(d,'links',{get:function(){return wrapList(dom.querySelectorAll(-1,'a[href]'));},enumerable:true});"
    "  d.dispatchEvent=function(ev){ return __G.__evDispatch('d',ev); };"
    "  d.implementation={ hasFeature:function(){return true;}, createHTMLDocument:function(){return d;} };"
    "  __G.document=d;"
    "  if (typeof __G.window==='undefined') __G.window=__G;"
    "  function memStore(){ var m={};"
    "    return { getItem:function(k){k=String(k);return Object.prototype.hasOwnProperty.call(m,k)?m[k]:null;},"
    "      setItem:function(k,v){m[String(k)]=String(v);},"
    "      removeItem:function(k){delete m[String(k)];},"
    "      clear:function(){m={};}, key:function(i){var ks=Object.keys(m);return i<ks.length?ks[i]:null;},"
    "      get length(){return Object.keys(m).length;} }; }"
    "  if (typeof __G.localStorage==='undefined') __G.localStorage=memStore();"
    "  if (typeof __G.sessionStorage==='undefined') __G.sessionStorage=memStore();"
    "  if (typeof __G.history==='undefined') __G.history={length:1,"
    "    state:null,pushState:function(){},replaceState:function(){},back:function(){},"
    "    forward:function(){},go:function(){}};"
    "  if (typeof __G.location==='undefined') __G.location={href:'',protocol:'https:',"
    "    host:'',hostname:'',pathname:'/',search:'',hash:'',origin:'',"
    "    assign:function(){},replace:function(){},reload:function(){}};"
    "  if (typeof __G.console==='undefined')"
    "    __G.console={log:function(){},warn:function(){},error:function(){},"
    "      info:function(){},debug:function(){}};"
    /* Intl: a minimal, identity-neutral stub (QuickJS-ng builds without ICU, so
     * Intl is otherwise undefined and any locale-aware script -- DuckDuckGo's
     * result formatting, date/number rendering -- dies with "Intl is not defined").
     * Everything resolves to a fixed en-US-ish behaviour via the engine's own
     * toLocaleString/toString: no real locale/timezone enumeration leaks (anti-fp). */
    "  if (typeof __G.Intl==='undefined'){ (function(){"
    "    function res(){ return {locale:'en-US',numberingSystem:'latn',calendar:'gregory',timeZone:'UTC'}; }"
    /* BCP 47 case canonicalisation: language lower, 4-letter script title, region upper. */
    "    function canon(t){ return t.split(/[-_]/).map(function(p,i){ if(i===0) return p.toLowerCase();"
    "      if(p.length===2) return p.toUpperCase(); if(p.length===4) return p.charAt(0).toUpperCase()+p.slice(1).toLowerCase();"
    "      return p.toLowerCase(); }).join('-'); }"
    "    function canonList(l){ if(l==null) return []; return (Array.isArray(l)?l:[l]).map(function(x){ return canon(String(x)); }); }"
    "    function NumberFormat(l,o){ if(!(this instanceof NumberFormat)) return new NumberFormat(l,o); this._o=o||{}; }"
    "    NumberFormat.prototype.format=function(n){ try{ return Number(n).toLocaleString('en-US'); }catch(e){ return String(n); } };"
    "    NumberFormat.prototype.formatToParts=function(n){ return [{type:'integer',value:this.format(n)}]; };"
    "    NumberFormat.prototype.resolvedOptions=res;"
    "    function DateTimeFormat(l,o){ if(!(this instanceof DateTimeFormat)) return new DateTimeFormat(l,o); this._o=o||{}; }"
    "    DateTimeFormat.prototype.format=function(d){ try{ return new Date(d).toString(); }catch(e){ return String(d); } };"
    "    DateTimeFormat.prototype.formatToParts=function(d){ return [{type:'literal',value:this.format(d)}]; };"
    "    DateTimeFormat.prototype.resolvedOptions=res;"
    "    function Collator(l,o){ if(!(this instanceof Collator)) return new Collator(l,o); }"
    "    Collator.prototype.compare=function(a,b){ a=String(a); b=String(b); return a<b?-1:(a>b?1:0); };"
    "    Collator.prototype.resolvedOptions=res;"
    "    function PluralRules(l,o){ if(!(this instanceof PluralRules)) return new PluralRules(l,o); }"
    "    PluralRules.prototype.select=function(n){ return Number(n)===1?'one':'other'; };"
    "    PluralRules.prototype.resolvedOptions=res;"
    "    function RelativeTimeFormat(l,o){ if(!(this instanceof RelativeTimeFormat)) return new RelativeTimeFormat(l,o); }"
    "    RelativeTimeFormat.prototype.format=function(v,u){ return String(v)+' '+String(u); };"
    "    RelativeTimeFormat.prototype.formatToParts=function(v,u){ return [{type:'literal',value:this.format(v,u)}]; };"
    "    RelativeTimeFormat.prototype.resolvedOptions=res;"
    "    function ListFormat(l,o){ if(!(this instanceof ListFormat)) return new ListFormat(l,o); }"
    "    ListFormat.prototype.format=function(a){ return (a||[]).join(', '); };"
    "    ListFormat.prototype.resolvedOptions=res;"
    "    __G.Intl={NumberFormat:NumberFormat,DateTimeFormat:DateTimeFormat,Collator:Collator,"
    "      PluralRules:PluralRules,RelativeTimeFormat:RelativeTimeFormat,ListFormat:ListFormat,"
    "      getCanonicalLocales:function(l){ return canonList(l); }};"
    /* supportedLocalesOf on every constructor (formatjs calls it at startup): the
     * requested tags, canonicalised -- formatting itself stays the fixed en-US. */
    "    [NumberFormat,DateTimeFormat,Collator,PluralRules,RelativeTimeFormat,ListFormat].forEach(function(C){"
    "      C.supportedLocalesOf=function(l){ return canonList(l); }; });"
    "    function Locale(tag){ if(!(this instanceof Locale)) return new Locale(tag);"
    "      var t=canon(String(tag)), p=t.split('-'); this.baseName=t; this.language=p[0]||'en';"
    "      this.region=undefined; this.script=undefined;"
    "      for(var i=1;i<p.length;i++){ if(/^[A-Z]{2}$|^[0-9]{3}$/.test(p[i])) this.region=p[i];"
    "        else if(/^[A-Z][a-z]{3}$/.test(p[i])) this.script=p[i]; } }"
    "    Locale.prototype.toString=function(){ return this.baseName; };"
    "    Locale.prototype.maximize=function(){ return this; }; Locale.prototype.minimize=function(){ return this; };"
    "    function DisplayNames(l,o){ if(!(this instanceof DisplayNames)) return new DisplayNames(l,o); this._o=o||{}; }"
    "    DisplayNames.prototype.of=function(code){ return String(code); };"
    "    DisplayNames.prototype.resolvedOptions=res; DisplayNames.supportedLocalesOf=function(l){ return canonList(l); };"
    "    function Segmenter(l,o){ if(!(this instanceof Segmenter)) return new Segmenter(l,o);"
    "      this._g=(o&&o.granularity)||'grapheme'; }"
    "    Segmenter.prototype.segment=function(str){ str=String(str); var g=this._g, out=[];"
    "      if(g==='grapheme'){ var a=Array.from(str), idx=0;"
    "        a.forEach(function(ch){ out.push({segment:ch,index:idx,input:str}); idx+=ch.length; }); }"
    "      else { var re=g==='word'?/\\w+|[^\\w]+/g:/[^.!?]+[.!?]*\\s*/g, m;"
    "        while((m=re.exec(str))!==null){ if(m[0]==='') break; out.push({segment:m[0],index:m.index,input:str,"
    "          isWordLike:g==='word'?/\\w/.test(m[0]):undefined}); } }"
    "      out.containing=function(i){ for(var k=0;k<out.length;k++){ var s=out[k];"
    "        if(i>=s.index&&i<s.index+s.segment.length) return s; } return undefined; };"
    "      return out; };"
    "    Segmenter.prototype.resolvedOptions=res; Segmenter.supportedLocalesOf=function(l){ return canonList(l); };"
    "    __G.Intl.Locale=Locale; __G.Intl.DisplayNames=DisplayNames; __G.Intl.Segmenter=Segmenter;"
    "    __G.Intl.supportedValuesOf=function(){ return []; };"
    "  })(); }"
    "  __G.addEventListener=function(type,fn,o){ if(!addL(String(type),fn,'w')) __G.__evAdd('w',type,fn,o); };"
    "  __G.removeEventListener=function(type,fn,o){ delL(String(type),fn,'w'); __G.__evRemove('w',type,fn,o); };"
    "  __G.dispatchEvent=function(ev){ return __G.__evDispatch('w',ev); };"

    /* Timers with REAL delays (2026-07-11): each entry is {f, due, iv, id} where
     * due is the remaining virtual ms (the trusted parent advances the clock via
     * OP_TICK -> __tickTimers(elapsed); no real clock leaks -- anti-fp) and iv is
     * the setInterval period (0 = one-shot). A missing/invalid delay is 0 (fires
     * on the load pump, the historical behaviour). clearTimeout/clearInterval
     * cancel by id. rAF/rIC keep due 0 (the v1 "frame" is the pump). */
    "  var tmSeq=0;"
    "  function tmAdd(fn,ms,iv){ if(typeof fn!=='function') return 0;"
    "    var d=(typeof ms==='number'&&ms>0)?ms:0;"
    "    timers.push({f:fn,due:d,iv:iv?Math.max(d,16):0,id:++tmSeq}); return tmSeq; }"
    "  function tmDel(id){ for(var i=0;i<timers.length;i++)"
    "    if(timers[i].id===id){ timers.splice(i,1); return; } }"
    "  __G.setTimeout=function(fn,ms){ return tmAdd(fn,ms,0); };"
    "  __G.setInterval=function(fn,ms){ return tmAdd(fn,ms,1); };"
    "  __G.clearTimeout=tmDel; __G.clearInterval=tmDel;"
    /* rAF/rIC feed the same synthetic timer queue; the callback gets a fixed
     * timestamp (identity-safe: no real high-res clock leaks through animation). */
    "  __G.requestAnimationFrame=function(fn){ if(typeof fn!=='function') return 0;"
    "    return tmAdd(function(){ fn(0); },0,0); };"
    "  __G.cancelAnimationFrame=tmDel;"
    "  __G.requestIdleCallback=function(fn){ if(typeof fn!=='function') return 0;"
    "    return tmAdd(function(){ fn({didTimeout:false,timeRemaining:function(){return 0;}}); },0,0); };"
    "  __G.cancelIdleCallback=tmDel;"
    "  __G.queueMicrotask=function(fn){ if(typeof fn==='function') Promise.resolve().then(fn); };"
    /* Advances the virtual clock and fires everything due, in bounded ROUNDS (a
     * timer may schedule more timers). Intervals re-arm. Returns fired count. */
    "  __G.__tickTimers=function(elapsed){"
    "    var e=Number(elapsed)||0, fired=0, rounds=0;"
    "    for (var i=0;i<timers.length;i++) timers[i].due-=e;"
    "    while (rounds<8 && fired<256){"
    "      var due=[], rest=[];"
    "      for (var i=0;i<timers.length;i++) (timers[i].due<=0?due:rest).push(timers[i]);"
    "      if (due.length===0) break;"
    "      timers=rest; rounds++;"
    "      for (var j=0;j<due.length && fired<256;j++){ fired++;"
    "        try{ due[j].f.call(__G); }catch(ex){ try{console.error(ex);}catch(e){} }"
    "        if (due[j].iv>0){ due[j].due=due[j].iv; timers.push(due[j]); }"
    "      }"
    "    }"
    "    return fired;"
    "  };"
    /* Smallest remaining delay (>= 0), or -1 when nothing is pending -- the parent
     * uses it to schedule the next OP_TICK. */
    "  __G.__nextTimerMs=function(){"
    "    var m=-1;"
    "    for (var i=0;i<timers.length;i++){"
    "      var d=timers[i].due>0?timers[i].due:0;"
    "      if (m<0||d<m) m=d;"
    "    }"
    "    return m;"
    "  };"
    /* Synthetic, bounded "page loaded" pump: fire load handlers, then drain the
     * zero-delay timers (rAF loops, chained setTimeout with no delay). Timers with
     * a real delay stay queued for __tickTimers; microtasks are js_pump_jobs'. */
    "  __G.__fireDeferred=function(){"
    "    function fbLogErr(ex){ try{console.error(ex);}catch(e){} }"
    /* Lifecycle order (HTML 8.4.5): readystatechange + DOMContentLoaded on the
     * document, then load on the window (its target is the document). */
    "    function lcEvent(type,cur){ var E=__G.Event, e=(typeof E==='function')?Object.create(E.prototype):{};"
    "      var stop=false, prevented=false;"
    "      var props={type:type,target:d,srcElement:d,currentTarget:cur,eventPhase:2,bubbles:false,"
    "        cancelable:false,isTrusted:true,composed:false,timeStamp:0,returnValue:true};"
    "      for(var k in props) Object.defineProperty(e,k,{value:props[k],writable:true,configurable:true,enumerable:true});"
    "      Object.defineProperty(e,'defaultPrevented',{get:function(){ return prevented; },configurable:true});"
    "      e.preventDefault=function(){ prevented=true; }; e.stopPropagation=function(){};"
    "      e.stopImmediatePropagation=function(){ stop=true; }; e.composedPath=function(){ return [cur]; };"
    "      e.__stopped=function(){ return stop; }; return e; }"
    "    function fireType(type){ var list=loadCbs.slice();"
    "      for (var i=0;i<list.length;i++){ var c=list[i]; if(c.t!==type) continue;"
    "        var cur=c.tg==='w'?__G:d, ev=lcEvent(type,cur);"
    "        try{ if(typeof c.f==='function') c.f.call(cur,ev); else c.f.handleEvent(ev); }catch(e){fbLogErr(e);}"
    "        if(ev.__stopped()) break; } }"
    "    fireType('readystatechange'); fireType('DOMContentLoaded'); fireType('load');"
    "    if (typeof __G.onload==='function'){ try{ __G.onload.call(__G,lcEvent('load',__G)); }catch(e){fbLogErr(e);} }"
    "    if (typeof d.onload==='function'){ try{ d.onload.call(d,lcEvent('load',d)); }catch(e){fbLogErr(e);} }"
    "    __G.__tickTimers(0);"
    "    if (typeof __G.__connectedCallback==='function') __G.__connectedCallback();"
    "  };"
    /* Event propagation (DOM Standard 2.9, spec/js_dom.md 7d). ONE listener registry
     * for elements ('n'+handle), the document ('d') and the window ('w'):
     * LS[key][type] = [{f, c(capture), o(once), rm(removed), on(handler slot)}].
     * The path is computed before dispatch and bounded (hostile deep DOM). */
    "  var LS={}, PATH_MAX=4096;"
    "  var NOBUB={focus:1,blur:1,mouseenter:1,mouseleave:1,scroll:1,load:1};"
    /* 'o'+id keys are standalone event targets (a WebSocket): registered in __objs,
     * dispatched at target only -- they are not in the document tree. */
    "  var OBJS={}; __G.__objRegister=function(id,o){ OBJS[id]=o; };"
    "  function lsObj(k){ if(k==='w') return __G; if(k==='d') return d;"
    "    if(k.charAt(0)==='o') return OBJS[k.slice(1)]||null;"
    "    return __G.__wrap(Number(k.slice(1))); }"
    "  function capOf(o){ return (typeof o==='boolean')?o:!!(o&&typeof o==='object'&&o.capture); }"
    "  function isL(fn){ return typeof fn==='function'||(!!fn&&typeof fn.handleEvent==='function'); }"
    "  function lsArr(k,type,make){ var m=LS[k]; if(!m){ if(!make) return null; m=LS[k]={}; }"
    "    var a=m[type]; if(!a&&make) a=m[type]=[]; return a||null; }"
    "  __G.__evAdd=function(k,type,fn,o){ if(!isL(fn)) return; type=String(type);"
    "    var c=capOf(o), a=lsArr(k,type,true);"
    "    for(var i=0;i<a.length;i++) if(!a[i].on&&a[i].f===fn&&a[i].c===c) return;"
    "    a.push({f:fn,c:c,o:!!(o&&typeof o==='object'&&o.once),rm:false,on:false}); };"
    "  function drop(a,i){ a[i].rm=true; a.splice(i,1); }"
    "  __G.__evRemove=function(k,type,fn,o){ var a=lsArr(k,String(type),false); if(!a) return;"
    "    var c=capOf(o);"
    "    for(var i=0;i<a.length;i++) if(!a[i].on&&a[i].f===fn&&a[i].c===c){ drop(a,i); return; } };"
    /* on<type> handler property: one slot, kept at the position of its first set. */
    "  __G.__evHandlerProps=function(obj,k,types){ types.forEach(function(t){"
    "    Object.defineProperty(obj,'on'+t,{configurable:true,"
    "      get:function(){ var a=lsArr(k,t,false); if(a) for(var i=0;i<a.length;i++) if(a[i].on) return a[i].f; return null; },"
    "      set:function(fn){ var a=lsArr(k,t,true);"
    "        for(var i=0;i<a.length;i++) if(a[i].on){ if(typeof fn==='function') a[i].f=fn; else drop(a,i); return; }"
    "        if(typeof fn==='function') a.push({f:fn,c:false,o:false,rm:false,on:true}); }}); }); };"
    "  __G.__evHandlerProps(__G,'w',['popstate','hashchange','message']);"
    "  function invoke(k,ev,phase){ var a=lsArr(k,ev.type,false); if(!a||!a.length) return;"
    "    var snap=a.slice(), cur=lsObj(k); ev.currentTarget=cur; ev.eventPhase=phase;"
    "    for(var i=0;i<snap.length;i++){ var l=snap[i]; if(l.rm) continue;"
    "      if((phase===1&&!l.c)||(phase===3&&l.c)) continue;"
    "      if(l.o){ var j=a.indexOf(l); if(j>=0) drop(a,j); }"
    "      try{ if(typeof l.f==='function') l.f.call(cur,ev); else l.f.handleEvent(ev); }"
    "      catch(ex){ try{ console.error(ex); }catch(e2){} }"
    "      if(ev.__si) break; } }"
    "  function evPath(k){ var p=[k];"
    "    if(k.charAt(0)==='o') return p;"
    "    if(k.charAt(0)==='n'){ var n=dom.parent(Number(k.slice(1)));"
    "      while(n!==null&&p.length<PATH_MAX){ p.push('n'+n); n=dom.parent(n); }"
    "      p.push('d'); }"
    "    if(k!=='w') p.push('w'); return p; }"
    "  __G.__evDispatch=function(k,ev){"
    "    if(!ev||typeof ev.type!=='string') throw new TypeError('dispatchEvent: not an Event');"
    "    if(typeof ev.__sp!=='boolean'){ ev.__sp=false; ev.__si=false; }"
    "    var path=evPath(k), i;"
    "    ev.target=lsObj(k); ev.__path=path.map(lsObj);"
    "    for(i=path.length-1;i>0&&!ev.__sp;i--) invoke(path[i],ev,1);"
    "    if(!ev.__sp) invoke(path[0],ev,2);"
    "    if(ev.bubbles) for(i=1;i<path.length&&!ev.__sp;i++) invoke(path[i],ev,3);"
    "    ev.eventPhase=0; ev.currentTarget=null;"
    "    return !ev.defaultPrevented; };"
    /* Engine-generated (trusted) event on node n: props carry the input data from
     * the C side (key/keyCode/value/clientX...). Returns 0 if a listener called
     * preventDefault(), 1 otherwise. */
    "  __G.__dispatchEvent=function(n,type,props){"
    "    if(!type) return 1; type=String(type);"
    "    var ev=mkEvent(type,{bubbles:!NOBUB[type],cancelable:true});"
    "    if(props) for(var p in props) if(Object.prototype.hasOwnProperty.call(props,p)) ev[p]=props[p];"
    "    ev.isTrusted=true;"
    "    return __G.__evDispatch('n'+n,ev)?1:0;"
    "  };"
    "})();";

/* Modern ambient surface (Hito JS-web-moderna): benign, identity-safe globals a
 * real site's scripts touch during startup, so they run without a ReferenceError
 * or "cannot read property of undefined" instead of aborting. Every value is
 * inert: DOM interface constructors are empty (instanceof yields false, harmless);
 * observers never fire (no observation -> no info leak); matchMedia never matches
 * and getComputedStyle returns "" (Zero Knowledge -- no viewport/layout/font
 * leak); the viewport reads a fixed normalized size (matches the 1920 width
 * anti_fp uses for @media, not the real window); window.open returns null and
 * postMessage is a no-op (no popups, single realm). performance/navigator/screen
 * are owned by js_env (anti_fp) and are NOT redefined here. Runs after the
 * document shim (uses __wrap/__wrapList/__mkEvent), each define guarded so it
 * never clobbers an existing global. */
static const char JD_MODERN_SHIM[] =
    "(function(){"
    "  var g=__G;"
    "  function stubCtor(){ function F(){} return F; }"
    "  ['Node','Element','HTMLElement','HTMLDivElement','HTMLSpanElement','HTMLAnchorElement',"
    "   'HTMLImageElement','HTMLInputElement','HTMLButtonElement','HTMLScriptElement','HTMLStyleElement',"
    "   'HTMLFormElement','HTMLSelectElement','HTMLOptionElement','HTMLTextAreaElement','HTMLTableElement',"
    "   'HTMLTableRowElement','HTMLTableCellElement','HTMLParagraphElement','HTMLHeadingElement',"
    "   'HTMLTableSectionElement','HTMLTableColElement','HTMLUListElement','HTMLOListElement','HTMLLIElement',"
    "   'HTMLBRElement','HTMLHRElement','HTMLPreElement','HTMLQuoteElement','HTMLCanvasElement',"
    "   'HTMLAudioElement','HTMLVideoElement','HTMLSourceElement','HTMLIFrameElement','HTMLLabelElement',"
    "   'HTMLFieldSetElement','HTMLLegendElement','HTMLDataListElement','HTMLMeterElement','HTMLProgressElement',"
    "   'HTMLOutputElement','HTMLDetailsElement','HTMLDialogElement','HTMLSlotElement','HTMLTemplateElement',"
    "   'HTMLHeadElement','HTMLBodyElement','HTMLTitleElement','HTMLMetaElement','HTMLLinkElement',"
    "   'HTMLObjectElement','HTMLEmbedElement','HTMLParamElement','HTMLBaseElement','HTMLPictureElement',"
    "   'HTMLTimeElement','HTMLMapElement','HTMLAreaElement','HTMLModElement','HTMLMediaElement',"
    "   'HTMLDListElement','HTMLFrameSetElement','HTMLFrameElement','HTMLDirectoryElement','HTMLFontElement',"
     "   'XMLDocument','HTMLDocument','Document','DocumentFragment','ShadowRoot','CharacterData','Text','Comment','Attr',"
     "   'DOMTokenList','NodeList','HTMLCollection','CSSStyleDeclaration','EventTarget',"
     "   'DocumentType','CDATASection','ProcessingInstruction','Window','NamedNodeMap','Range','StaticRange',"
     "   'Selection','TreeWalker','NodeIterator','Location','History','Navigator','Screen','Storage',"
     "   'StyleSheet','CSSStyleSheet','CSSRule','MediaQueryList','DOMRect','DOMRectReadOnly'].forEach("
    "    function(n){ if(typeof g[n]==='undefined') g[n]=stubCtor(); });"
    /* Interface prototype chains (DOM Standard): HTML*Element -> HTMLElement ->
     * Element -> Node -> EventTarget, Document -> Node, so instanceof answers like a
     * browser. Only stub constructors (no native ones) are re-chained. */
    "  function chainTo(c,p){ if(typeof g[c]==='function'&&typeof g[p]==='function'&&g[c]!==g[p])"
    "    try{ Object.setPrototypeOf(g[c].prototype, g[p].prototype); }catch(e){} }"
    "  chainTo('Node','EventTarget'); chainTo('Element','Node'); chainTo('HTMLElement','Element');"
    "  chainTo('SVGElement','Element'); chainTo('Document','Node'); chainTo('HTMLDocument','Document');"
    "  chainTo('XMLDocument','Document'); chainTo('DocumentFragment','Node'); chainTo('ShadowRoot','DocumentFragment');"
    "  chainTo('CharacterData','Node'); chainTo('Text','CharacterData'); chainTo('Comment','CharacterData');"
    "  chainTo('CDATASection','Text'); chainTo('ProcessingInstruction','CharacterData');"
    "  chainTo('DocumentType','Node'); chainTo('Window','EventTarget'); chainTo('DOMRect','DOMRectReadOnly');"
    /* the global object IS a Window (window instanceof Window) */
    "  if(typeof g.Window==='function') try{ Object.setPrototypeOf(g, g.Window.prototype); }catch(e){}"
    /* DOMException carries name/message (pages throw and inspect it) */
    "  if(typeof g.DOMException==='undefined'){ g.DOMException=function(m,n){ this.message=String(m===undefined?'':m);"
    "      this.name=(n===undefined)?'Error':String(n); };"
    "    g.DOMException.prototype=Object.create(Error.prototype); g.DOMException.prototype.constructor=g.DOMException; }"
    "  Object.getOwnPropertyNames(g).forEach(function(n){"
    "    if(/^HTML.+Element$/.test(n)&&n!=='HTMLElement') chainTo(n,'HTMLElement'); });"
    "  if(typeof g.HTMLElement==='function') g.__elProto=g.HTMLElement.prototype;"
    "  if(typeof g.HTMLDocument==='function'&&g.document)"
    "    try{ Object.setPrototypeOf(g.document, g.HTMLDocument.prototype); }catch(e){}"
    "  if(g.Node){ g.Node.ELEMENT_NODE=1; g.Node.TEXT_NODE=3; g.Node.COMMENT_NODE=8;"
    "    g.Node.DOCUMENT_NODE=9; g.Node.DOCUMENT_FRAGMENT_NODE=11; }"
    "  function evCtor(){ return function(type,opts){ return g.__mkEvent?g.__mkEvent(type,opts):{type:String(type)}; }; }"
    "  ['Event','CustomEvent','MouseEvent','KeyboardEvent','PointerEvent','UIEvent','FocusEvent',"
    "   'InputEvent','TouchEvent','WheelEvent','MessageEvent','PopStateEvent','HashChangeEvent',"
    "   'ErrorEvent','ProgressEvent'].forEach(function(n){ if(typeof g[n]==='undefined') g[n]=evCtor(); });"
    /* new Audio(src): a real wrapped <audio> element, so it carries the full
     * HTMLMediaElement facade (play/pause/canPlayType). No network: creating
     * it never fetches; playback only happens via the trusted-side pipeline. */
    "  if(typeof g.Audio==='undefined') g.Audio=function(src){"
    "    var a=(g.document&&g.document.createElement)?g.document.createElement('audio'):{};"
    "    if(src!==undefined&&a&&a.setAttribute) a.setAttribute('src',String(src));"
    "    return a; };"
    /* matchMedia evaluates for real (2026-07-19) against the normalized
     * 1920x1080 desktop identity (the same one innerWidth and the CSS viewport
     * units use). Identity signals are ALWAYS normalized: light color scheme,
     * no-preference motion, hover-capable fine pointer (the Firefox-desktop
     * identity already on the wire). Unknown features and junk are false,
     * never a throw; listeners accept and never fire (the normalized identity
     * never changes, so zero change events is correct and deterministic). */
    "  if(typeof g.matchMedia==='undefined') g.matchMedia=function(q){"
    "    q=String(q||'');"
    "    function mlen(v){ var n=parseFloat(v); if(!isFinite(n)) return NaN;"
    "      return v.indexOf('em')>=0 ? n*16 : n; }"
    "    function term(t){ t=t.trim();"
    "      if(t===''||t==='all'||t==='screen') return true;"
    "      if(t==='print'||t==='speech') return false;"
    "      if(t.charAt(0)!=='('||t.charAt(t.length-1)!==')') return false;"
    "      var b=t.slice(1,-1), ci=b.indexOf(':'), k, v;"
    "      if(ci<0){ k=b.trim(); v=''; } else { k=b.slice(0,ci).trim(); v=b.slice(ci+1).trim(); }"
    "      if(k==='min-width')  return 1920>=mlen(v);"
    "      if(k==='max-width')  return 1920<=mlen(v);"
    "      if(k==='width')      return mlen(v)===1920;"
    "      if(k==='min-height') return 1080>=mlen(v);"
    "      if(k==='max-height') return 1080<=mlen(v);"
    "      if(k==='height')     return mlen(v)===1080;"
    "      if(k==='orientation') return v==='landscape';"
    "      if(k==='prefers-color-scheme') return v==='light';"
    "      if(k==='prefers-reduced-motion'||k==='prefers-contrast') return v==='no-preference';"
    "      if(k==='hover'||k==='any-hover') return v==='hover';"
    "      if(k==='pointer'||k==='any-pointer') return v==='fine';"
    "      return false; }"
    "    function clause(c){ var parts=c.split(' and ');"
    "      for(var i=0;i<parts.length;i++){ var p=parts[i].trim(), neg=false;"
    "        if(p.indexOf('not ')===0){ neg=true; p=p.slice(4).trim(); }"
    "        var r=term(p); if(neg) r=!r; if(!r) return false; }"
    "      return true; }"
    "    var m=false, cs=q.toLowerCase().replace(/\\s+/g,' ').split(',');"
    "    for(var i=0;i<cs.length;i++){ if(clause(cs[i])){ m=true; break; } }"
    "    return { matches:m, media:q, onchange:null,"
    "      addListener:function(){}, removeListener:function(){},"
    "      addEventListener:function(){}, removeEventListener:function(){},"
    "      dispatchEvent:function(){ return false; } }; };"
  "  /* --- Canvas 2D minimal (v1: fillRect, clearRect, fillStyle, toDataURL) --- */"
  "  function pngEnc(rgba,w,h){"
  "    var g_crc=[];for(var n=0;n<256;n++){var c=n;for(var k=0;k<8;k++)c=(c&1?0xEDB88320^c>>>1:c>>>1);g_crc[n]=c;}"
  "    function crc32(d){var c=0xFFFFFFFF;for(var i=0;i<d.length;i++)c=g_crc[(c^d[i])&0xFF]>>>8^c;return(c^0xFFFFFFFF)>>>0;}"
  "    function u32(v){return[(v>>>24)&0xFF,(v>>>16)&0xFF,(v>>>8)&0xFF,v&0xFF];}"
  "    function chk(t,d){var h=t.charCodeAt(0)|t.charCodeAt(1)<<8|t.charCodeAt(2)<<16|t.charCodeAt(3)<<24;"
  "      var hdr=u32(h);var body=[].concat(Array.from(d).map(function(x){return x}));"
  "      var c=crc32(u32(d.length).concat(hdr).concat(body));"
  "      return u32(d.length).concat(hdr).concat(body).concat(u32(c));}"
  "    var sig=[137,80,78,71,13,10,26,10];"
  "    var ihdr=chk('IHDR',u32(w).concat(u32(h)).concat([8,6,0,0,0]));"
  "    var raw=[];var row=w*4;raw=raw.concat([0x78,0x01]);"
  "    for(var y=0;y<h;y++){"
  "      var off=y*row;var blk=row+1;"
  "      raw.push(y==h-1?1|0x02:0x02);"
  "      raw.push(blk&0xFF);raw.push((blk>>>8)&0xFF);"
  "      raw.push((~blk)&0xFF);raw.push(((~blk)>>>8)&0xFF);"
  "      raw.push(0);"
  "      for(var x=0;x<row;x++)raw.push(rgba[off+x]);"
  "    }"
  "    var a1=1,a2=0;for(var i=0;i<raw.length-2;i++){var b=raw[i+2]&0xFF;a1=(a1+b)%65521;a2=(a2+a1)%65521;}"
  "    raw=raw.concat(u32((a2<<16)|a1));"
  "    var idat=chk('IDAT',raw);"
  "    var iend=chk('IEND',[]);"
  "    var png=sig.concat(ihdr).concat(idat).concat(iend);"
  "    var b='ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/';"
  "    var r='';for(var i=0;i<png.length;i+=3){"
  "      r+=b.charAt(png[i]>>>2);r+=b.charAt(((png[i]&3)<<4)|(png[i+1]>>>4));"
  "      r+=i+1<png.length?b.charAt(((png[i+1]&15)<<2)|(png[i+2]>>>6)):'=';"
  "      r+=i+2<png.length?b.charAt(png[i+2]&63):'=';"
  "    }"
  "    return 'data:image/png;base64,'+r;"
  "  }"
  "  g.__png_encode=pngEnc;"
  "  function CanvasCtx(w,h){"
  "    var buf=new Uint8Array(w*h*4);var fs='#000';"
  "    this.width=w;this.height=h;this._buf=buf;this._w=w;this._h=h;"
  "    Object.defineProperty(this,'fillStyle',{get:function(){return fs;},set:function(v){fs=String(v);},configurable:true});"
  "    this.fillRect=function(x,y,w,h){"
  "      var r=parseInt(fs.slice(1,3),16),g=parseInt(fs.slice(3,5),16),b=parseInt(fs.slice(5,7),16),a=255;"
  "      if(fs.length===9)a=parseInt(fs.slice(7,9),16);if(isNaN(r)){r=g=b=0;}"
  "      for(var py=y;py<y+h&&py<this._h;py++){for(var px=x;px<x+w&&px<this._w;px++){"
  "        var i=(py*this._w+px)*4;buf[i]=r;buf[i+1]=g;buf[i+2]=b;buf[i+3]=a;}}"
  "    ;};"
  "    this.clearRect=function(x,y,w,h){"
  "      for(var py=y;py<y+h&&py<this._h;py++){for(var px=x;px<x+w&&px<this._w;px++){"
  "        var i=(py*this._w+px)*4;buf[i]=buf[i+1]=buf[i+2]=buf[i+3]=0;}}"
  "    ;};"
  "    this.toDataURL=function(type){"
  "      var rb=typeof g.canvas!=='undefined'&&g.canvas.readback?g.canvas.readback:function(x){return x;};"
  "      return __png_encode(rb(buf),this._w,this._h);"
  "    ;};"
  "  }"
  "  g.__CanvasCtx=CanvasCtx;"
  /* The rest of the 2D API as inert operations: pages call them while feature-testing
   * and drawing; pixels only change through fillRect/clearRect. measureText answers a
   * deterministic width from the string length (no font-metric leak, anti-fp). */
  "  g.__canvasFill=function(c){ function nop(){}"
  "    ['beginPath','closePath','moveTo','lineTo','arc','arcTo','rect','fill','stroke','save','restore',"
  "     'translate','rotate','scale','setTransform','transform','resetTransform','drawImage','fillText',"
  "     'strokeText','clip','quadraticCurveTo','bezierCurveTo','ellipse','setLineDash','putImageData',"
  "     'strokeRect','drawFocusIfNeeded','scrollPathIntoView','roundRect','reset']"
  "    .forEach(function(n){ if(typeof c[n]!=='function') c[n]=nop; });"
  "    if(typeof c.measureText!=='function') c.measureText=function(t){ var w=String(t).length*8;"
  "      return {width:w,actualBoundingBoxLeft:0,actualBoundingBoxRight:w,actualBoundingBoxAscent:10,"
  "        actualBoundingBoxDescent:2,fontBoundingBoxAscent:12,fontBoundingBoxDescent:3}; };"
  "    function grad(){ return {addColorStop:nop}; }"
  "    if(typeof c.createLinearGradient!=='function') c.createLinearGradient=grad;"
  "    if(typeof c.createRadialGradient!=='function') c.createRadialGradient=grad;"
  "    if(typeof c.createConicGradient!=='function') c.createConicGradient=grad;"
  "    if(typeof c.createPattern!=='function') c.createPattern=function(){ return {setTransform:nop}; };"
  "    if(typeof c.getLineDash!=='function') c.getLineDash=function(){ return []; };"
  "    if(typeof c.isPointInPath!=='function') c.isPointInPath=function(){ return false; };"
  "    if(typeof c.isPointInStroke!=='function') c.isPointInStroke=function(){ return false; };"
  "    if(typeof c.getTransform!=='function') c.getTransform=function(){ return {a:1,b:0,c:0,d:1,e:0,f:0}; };"
  "    if(typeof c.createImageData!=='function') c.createImageData=function(w,h){"
  "      w=Math.max(0,Math.min(w|0,1024)); h=Math.max(0,Math.min(h|0,1024));"
  "      return {width:w,height:h,data:new Uint8ClampedArray(w*h*4)}; };"
  "    if(typeof c.getImageData!=='function') c.getImageData=function(x,y,w,h){ return c.createImageData(w,h); };"
  "    ['lineWidth','globalAlpha','font','textAlign','textBaseline','strokeStyle','lineCap','lineJoin',"
  "     'shadowBlur','shadowColor','globalCompositeOperation','imageSmoothingEnabled','filter']"
  "    .forEach(function(n){ if(!(n in c)) c[n]=(n==='globalAlpha'?1:n==='lineWidth'?1:''); });"
  "    return c; };"
  "  if(typeof g.HTMLCanvasElement!=='undefined'){"
  "    g.HTMLCanvasElement=function(w,h){this.width=w||300;this.height=h||150;"
  "      this.getContext=function(t){"
  "        if(t==='2d'||t==='2d')return new CanvasCtx(this.width,this.height);return null;};"
  "      this.toDataURL=function(t){var c=new CanvasCtx(this.width,this.height);return c.toDataURL(t);};"
  "    };"
  "  }"
     "  function observer(){ function O(cb){ this._cb=cb; } O.prototype.observe=function(){};"
     "    O.prototype.unobserve=function(){}; O.prototype.disconnect=function(){};"
     "    O.prototype.takeRecords=function(){return [];}; return O; }"
     "  ['MutationObserver','IntersectionObserver','ResizeObserver','PerformanceObserver'].forEach("
    "    function(n){ if(typeof g[n]==='undefined') g[n]=observer(); });"
    /* IntersectionObserver fires synthetically (2026-07-19): one deferred
     * delivery per observe() with isIntersecting:true and constant synthetic
     * geometry (zero real layout/scroll/timing leaks). Scroll-reveal libraries
     * that keep content at opacity:0 until the observer fires now reveal it.
     * The other observers above stay never-fire (no observation, no leak). */
    "  (function(){ function IO(cb){ this._cb=cb; this._live=true; }"
    "    IO.prototype.observe=function(el){ var self=this; if(el===null||el===undefined) return;"
    "      setTimeout(function(){ if(!self._live) return;"
    "        var r={x:0,y:0,top:0,left:0,right:0,bottom:0,width:0,height:0};"
    "        try{ self._cb([{isIntersecting:true,intersectionRatio:1,target:el,time:0,"
    "          boundingClientRect:r,intersectionRect:r,"
    "          rootBounds:{x:0,y:0,top:0,left:0,width:1920,height:1080,right:1920,bottom:1080}}],self);"
    "        }catch(e){} },0); };"
    "    IO.prototype.unobserve=function(){};"
    "    IO.prototype.disconnect=function(){ this._live=false; };"
    "    IO.prototype.takeRecords=function(){ return []; };"
    "    g.IntersectionObserver=IO; })();"
    "  if(typeof g.getComputedStyle==='undefined') g.getComputedStyle=function(){"
    "    var o={ getPropertyValue:function(){return '';}, getPropertyPriority:function(){return '';},"
    "      length:0, item:function(){return '';} };"
    "    return new Proxy(o,{ get:function(t,p){ if(p in t) return t[p]; return ''; } }); };"
    "  function ro(name,val){ if(typeof g[name]==='undefined'){ try{ Object.defineProperty(g,name,"
    "    {get:function(){return val;},configurable:true}); }catch(e){ try{ g[name]=val; }catch(e2){} } } }"
    /* Viewport/scroll: real only with installed geometry (trusted host), else the
     * normalized identity. outer* and devicePixelRatio stay normalized always. */
    "  function vro(name,i,val){ if(typeof g[name]==='undefined'){ try{ Object.defineProperty(g,name,"
    "    {get:function(){ var v=dom.viewport(); return v?v[i]:val; },configurable:true}); }"
    "    catch(e){ try{ g[name]=val; }catch(e2){} } } }"
    "  vro('innerWidth',2,1920); vro('innerHeight',3,1080); ro('outerWidth',1920); ro('outerHeight',1080);"
    "  ro('devicePixelRatio',1); vro('scrollX',0,0); vro('scrollY',1,0); vro('pageXOffset',0,0); vro('pageYOffset',1,0);"
    "  if(typeof g.scrollTo==='undefined') g.scrollTo=function(){};"
    "  if(typeof g.scrollBy==='undefined') g.scrollBy=function(){};"
    "  if(typeof g.scroll==='undefined') g.scroll=function(){};"
    "  if(typeof g.getSelection==='undefined') g.getSelection=function(){ return {toString:function(){return '';},"
    "    rangeCount:0,removeAllRanges:function(){},addRange:function(){}}; };"
    /* NOTE: window.open / postMessage / opener are DELIBERATELY absent (SOP by
     * construction: no popups, no cross-frame messaging). A call fails closed with
     * a ReferenceError; test_eval_no_network_or_cross_origin_api locks this. */
    "  if(typeof g.alert==='undefined') g.alert=function(){};"
    "  if(typeof g.confirm==='undefined') g.confirm=function(){ return false; };"
    "  if(typeof g.prompt==='undefined') g.prompt=function(){ return null; };"
    "  g.self=g; if(typeof g.top==='undefined') g.top=g; if(typeof g.parent==='undefined') g.parent=g;"
    "  if(typeof g.frames==='undefined') g.frames=g; if(typeof g.frameElement==='undefined') g.frameElement=null;"
    "  if(typeof g.closed==='undefined') g.closed=false;"
    "  if(typeof g.CSS==='undefined') g.CSS={ supports:function(){return false;}, escape:function(s){return String(s);} };"
    "  if(typeof g.customElements==='undefined') g.customElements=(function(){"
    "    var defs=[], pending=[];"
    "    return {"
    "      define:function(name,ctor){"
    "        try{ defs[name]=ctor;"
    "          if(typeof ctor==='function'){"
    "            if(typeof ctor.prototype==='object'||typeof ctor.prototype==='function'){"
    "              if(typeof ctor.prototype.connectedCallback==='function'){"
    "                var el=g.document.querySelector(name); if(el) pending.push(el);"
    "              }"
    "            }"
    "          }"
    "        }catch(e){}"
    "      },"
    "      get:function(name){ return defs[name]; },"
    "      whenDefined:function(name){ return Promise.resolve(defs[name]); },"
    "      upgrade:function(root){"
    "        if(!root) root=g.document;"
    "        Object.keys(defs).forEach(function(n){"
    "          var els=root.querySelectorAll(n);"
    "          for(var i=0;i<els.length;i++) pending.push(els[i]);"
    "        });"
    "      },"
    "      _pending: pending,"
    "      _defs: defs"
    "    };"
    "  })();"
    "  if(typeof g.__connectedCallback==='undefined') g.__connectedCallback=function(){"
    "    var ce=g.customElements; if(!ce) return;"
    "    var list=ce._pending; if(!list || list.length===0) return;"
    "    for(var i=0;i<list.length;i++){"
    "      try{ if(typeof list[i].connectedCallback==='function') list[i].connectedCallback(); }catch(e){}"
    "    }"
    "    list.length=0;"
    "  };"
    "  if(typeof g.$==='undefined') (function(){"
    "    function JQ(sel,ctx){ if(!(this instanceof JQ)) return new JQ(sel,ctx);"
    "      this.length=0; if(typeof sel==='function'){ if(g.document.readyState==='complete') sel();"
    "      else g.document.addEventListener('DOMContentLoaded',sel); return; }"
    "      if(typeof sel==='string'){ var nl=(ctx||g.document).querySelectorAll(sel); this.length=nl.length;"
    "      for(var i=0;i<nl.length;i++) this[i]=nl[i]; } else if(sel){ this[0]=sel; this.length=1; } }"
    "    JQ.prototype={ each:function(f){ for(var i=0;i<this.length;i++) f.call(this[i],i,this[i]); return this; },"
    "      on:function(e,f){ this.each(function(){ this.addEventListener(e,f); }); return this; },"
    "      off:function(e,f){ this.each(function(){ this.removeEventListener(e,f); }); return this; },"
    "      attr:function(n,v){ if(v===undefined) return this[0]?this[0].getAttribute(n):null;"
    "      this.each(function(){ this.setAttribute(n,v); }); return this; },"
    "      removeAttr:function(n){ this.each(function(){ this.removeAttribute(n); }); return this; },"
    "      addClass:function(c){ this.each(function(){ if(this.classList) this.classList.add(c); }); return this; },"
    "      removeClass:function(c){ this.each(function(){ if(this.classList) this.classList.remove(c); }); return this; },"
    "      hasClass:function(c){ return this[0]&&this[0].classList?this[0].classList.contains(c):false; },"
    "      toggleClass:function(c){ this.each(function(){ if(this.classList) this.classList.toggle(c); }); return this; },"
    "      val:function(v){ if(v===undefined) return this[0]?(this[0].value||''):'';"
    "      this.each(function(){ this.value=v; }); return this; },"
    "      text:function(t){ if(t===undefined){ var s=''; for(var i=0;i<this.length;i++) s+=this[i].textContent||'';"
    "        return s; } this.each(function(){ this.textContent=t; }); return this; },"
    "      html:function(h){ if(h===undefined) return this[0]?this[0].innerHTML||'':'';"
    "      this.each(function(){ this.innerHTML=h; }); return this; },"
    "      css:function(p,v){ if(typeof p==='string'&&v===undefined){"
    "        if(!this[0]) return null; var cs=g.getComputedStyle(this[0]); return cs[p]||''; }"
    "      if(typeof p==='object') for(var k in p) this.each(function(){ this.style[k]=p[k]; });"
    "      else this.each(function(){ this.style[p]=v; }); return this; },"
    "      find:function(sel){ return new JQ(sel,this[0]); },"
    "      parent:function(){ return this[0]?new JQ(this[0].parentNode):new JQ(''); },"
    "      children:function(s){ var r=new JQ(''); if(!this[0]) return r;"
    "      var c=this[0].children,m=0; for(var i=0;i<c.length;i++){"
    "      if(!s||c[i].matches(s)) r[m]=c[i],m++; } r.length=m; return r; },"
    "      closest:function(s){ if(!this[0]) return new JQ(''); var e=this[0];"
    "      while(e){ if(e.matches&&e.matches(s)) return new JQ(e); e=e.parentElement; } return new JQ(''); },"
    "      is:function(s){ return this[0]&&this[0].matches?this[0].matches(s):false; },"
    "      data:function(k,v){ if(v===undefined){"
    "        return this[0]?this[0].getAttribute('data-'+k)||null:null; }"
    "      this.each(function(){ this.setAttribute('data-'+k,v); }); return this; },"
    "      remove:function(){ this.each(function(){ if(this.parentNode) this.parentNode.removeChild(this); });"
    "        return this; },"
    "      append:function(el){ this.each(function(){ if(typeof el==='string') this.innerHTML+=el;"
    "        else if(el.nodeType) this.appendChild(el); else if(el.length) for(var i=0;i<el.length;i++)"
    "        this.appendChild(el[i]); }); return this; },"
    "      empty:function(){ this.each(function(){ this.innerHTML=''; }); return this; },"
    "      hide:function(){ this.css('display','none'); return this; },"
    "      show:function(){ this.css('display',''); return this; } };"
    "    g.$=JQ; g.jQuery=JQ; })();"
    "  if(typeof g.duckduckgo==='undefined') g.duckduckgo={};"
    "  if(typeof g.__NEXT_DATA__==='undefined') g.__NEXT_DATA__={props:{}};"
    "  if(typeof g.__NEXT_PRELOADREADY==='undefined') g.__NEXT_PRELOADREADY=function(){};"
    "  if(typeof g.locale_data==='undefined') g.locale_data={};"
    /* navigator.permissions.query (Hito 30b): Google bot detection queries this.
     * Identity-safe stub: always resolves to {state:'prompt'}. Never leaks real
     * permission state. */
    "  if(g.navigator&&typeof g.navigator.permissions==='undefined'){"
    "    g.navigator.permissions={query:function(desc){"
    "      var result={state:'prompt',onchange:null};"
    "      result.addEventListener=function(){}; result.removeEventListener=function(){};"
    "      return {then:function(cb){ return cb(result); }};"
    "    }};"
    "  }"
    /* TextEncoder/TextDecoder (define-guarded; QuickJS-ng usually has them). */
    "  if(typeof g.TextEncoder==='undefined'){g.TextEncoder=function(){this.encoding='utf-8';};"
    "    g.TextEncoder.prototype.encode=function(s){s=String(s);"
    "      var n=s.length,b=[],c,c2,cp;for(var i=0;i<n;i++){c=s.charCodeAt(i);"
    "        if(c<0x80){b.push(c);}else if(c<0x800){b.push(0xc0|(c>>6),0x80|(c&0x3f));"
    "        }else if(c<0xd800||c>=0xe000){b.push(0xe0|(c>>12),0x80|((c>>6)&0x3f),0x80|(c&0x3f));"
    "        }else{c2=s.charCodeAt(++i);cp=((c&0x3ff)<<10)|(c2&0x3ff)|0x10000;"
    "          b.push(0xf0|(cp>>18),0x80|((cp>>12)&0x3f),0x80|((cp>>6)&0x3f),0x80|(cp&0x3f));}}"
    "      return new Uint8Array(b);};"
    "    g.TextEncoder.prototype.encodeInto=function(s,dst){var e=this.encode(s);"
    "      var n=Math.min(e.length,dst.length);for(var i=0;i<n;i++)dst[i]=e[i];"
    "      return{read:n,written:n};};}"
    "  if(typeof g.TextDecoder==='undefined'){g.TextDecoder=function(label,opts){"
    "      this.encoding='utf-8';this.fatal=!!(opts&&opts.fatal);this.ignoreBOM=!!(opts&&opts.ignoreBOM);};"
    "    g.TextDecoder.prototype.decode=function(buf,opts){if(!buf)return '';"
    "      var b=new Uint8Array(buf),out='',i=0,n=b.length,c;"
    "      while(i<n){c=b[i];"
    "        if(c<0x80){out+=String.fromCharCode(c);i++;}"
    "        else if(c<0xc0){if(this.fatal)throw new TypeError('invalid utf-8');out+='\ufffd';i++;}"
    "        else if(c<0xe0){if(i+1>=n||(b[i+1]&0xc0)!==0x80){if(this.fatal)throw new TypeError('invalid utf-8');out+='\ufffd';i++;continue;}"
    "          out+=String.fromCharCode(((c&0x1f)<<6)|(b[i+1]&0x3f));i+=2;}"
    "        else if(c<0xf0){if(i+2>=n||(b[i+1]&0xc0)!==0x80||(b[i+2]&0xc0)!==0x80){if(this.fatal)throw new TypeError('invalid utf-8');out+='\ufffd';i++;continue;}"
    "          out+=String.fromCharCode(((c&0x0f)<<12)|((b[i+1]&0x3f)<<6)|(b[i+2]&0x3f));i+=3;}"
    "        else if(c<0xf8){if(i+3>=n||(b[i+1]&0xc0)!==0x80||(b[i+2]&0xc0)!==0x80||(b[i+3]&0xc0)!==0x80){if(this.fatal)throw new TypeError('invalid utf-8');out+='\ufffd';i++;continue;}"
    "          cp=((c&0x07)<<18)|((b[i+1]&0x3f)<<12)|((b[i+2]&0x3f)<<6)|(b[i+3]&0x3f);"
    "          out+=String.fromCharCode(0xd800|(((cp-0x10000)>>10)&0x3ff),0xdc00|(cp&0x3ff));i+=4;}"
    "        else{if(this.fatal)throw new TypeError('invalid utf-8');out+='\ufffd';i++;}}"
    "      return out;};}"
    /* AbortController (needed by fetch/XHR polyfills). */
    "  if(typeof g.AbortController==='undefined'){"
    "    function ASignal(){this.aborted=false;this.reason=undefined;this._listeners=[];}"
    "    ASignal.prototype.addEventListener=function(e,fn){this._listeners.push(fn);};"
    "    ASignal.prototype.removeEventListener=function(e,fn){this._listeners=this._listeners.filter(function(f){return f!==fn;});};"
    "    ASignal.prototype.dispatchEvent=function(e){for(var i=0;i<this._listeners.length;i++)this._listeners[i].call(this,e);return true;};"
    "    g.AbortController=function(){this.signal=new ASignal();this.abort=function(reason){this.signal.aborted=true;"
    "      this.signal.reason=reason||'AbortError';this.signal.dispatchEvent({type:'abort',target:this.signal});};};"
    "    g.AbortSignal=ASignal;}"
    /* Headers (part of the fetch API). */
    "  if(typeof g.Headers==='undefined'){"
    "    g.Headers=function(init){this._m={};if(init&&typeof init==='object'){if(typeof init.forEach==='function'){var t=this;"
    "      init.forEach(function(v,k){t.append(k,v);});}else for(var k in init){if(Object.prototype.hasOwnProperty.call(init,k))this.append(k,init[k]);}}};"
    "    g.Headers.prototype.append=function(k,v){k=k.toLowerCase();if(!this._m[k])this._m[k]=[];this._m[k].push(String(v));};"
    "    g.Headers.prototype['delete']=function(k){delete this._m[k.toLowerCase()];};"
    "    g.Headers.prototype.get=function(k){var a=this._m[k.toLowerCase()];return a?a[0]:null;};"
    "    g.Headers.prototype.has=function(k){return this._m.hasOwnProperty(k.toLowerCase());};"
    "    g.Headers.prototype.set=function(k,v){this._m[k.toLowerCase()]=[String(v)];};"
    "    g.Headers.prototype.forEach=function(cb,t){var m=this._m;Object.keys(m).forEach(function(k){m[k].forEach(function(v){cb.call(t,v,k,m);});});};}"
    /* FormData (form serialisation without JS; also needed by XHR.send). */
    "  if(typeof g.FormData==='undefined'){"
    "    g.FormData=function(form){this._e=[];if(form&&form.elements){var els=form.elements;"
    "      for(var i=0;i<els.length;i++){var el=els[i];if(el.name&&!el.disabled){"
    "        if(el.type==='checkbox'||el.type==='radio'){if(el.checked)this.append(el.name,el.value);}"
    "        else if(el.type==='select-multiple'){for(var j=0;j<el.options.length;j++)if(el.options[j].selected)this.append(el.name,el.options[j].value);}"
    "        else if(el.type==='file'){for(var f=0;f<(el.files||[]).length;f++)this.append(el.name,el.files[f]);}"
    "        else if(el.type!=='submit'&&el.type!=='button'&&el.type!=='reset')this.append(el.name,el.value);}}}};"
    "    g.FormData.prototype.append=function(k,v,f){this._e.push([String(k),v,String(f||'')]);};"
    "    g.FormData.prototype['delete']=function(k){k=String(k);this._e=this._e.filter(function(p){return p[0]!==k;});};"
    "    g.FormData.prototype.get=function(k){k=String(k);for(var i=0;i<this._e.length;i++)if(this._e[i][0]===k)return this._e[i][1];return null;};"
    "    g.FormData.prototype.getAll=function(k){k=String(k);var o=[];for(var i=0;i<this._e.length;i++)if(this._e[i][0]===k)o.push(this._e[i][1]);return o;};"
    "    g.FormData.prototype.has=function(k){return this.get(String(k))!==null;};"
    "    g.FormData.prototype.set=function(k,v){k=String(k);var done=false,o=[];"
    "      for(var i=0;i<this._e.length;i++){if(this._e[i][0]===k){if(!done){o.push([k,v,'']);done=true;}}else o.push(this._e[i]);}"
    "      if(!done)o.push([k,v,'']);this._e=o;};"
    "    g.FormData.prototype.forEach=function(cb,t){for(var i=0;i<this._e.length;i++)cb.call(t,this._e[i][1],this._e[i][0],this);};"
    "    g.FormData.prototype.entries=function(){return this._e.map(function(p){return[p[0],p[1]];})[Symbol.iterator]();};"
    "    g.FormData.prototype.keys=function(){return this._e.map(function(p){return p[0];})[Symbol.iterator]();};"
    "    g.FormData.prototype.values=function(){return this._e.map(function(p){return p[1];})[Symbol.iterator]();};"
    "    g.FormData.prototype[Symbol.iterator]=function(){return this.entries();};}"
    "})();";

/* WHATWG URL + URLSearchParams as a pure-JS ambient surface. No network, no disk,
 * no host API: both are string parsers, so they are safe inside the sandbox and
 * leak no identity. They are two of the most-used modern-web globals; their absence
 * was Slashdot's first JS error (ReferenceError: URL is not defined). Define-guarded
 * (never clobbers a preexisting global) and bounded by the interpreter time budget.
 * URL resolution follows RFC 3986 sec. 5 (the WHATWG basic parser for the http/https
 * subset the browser actually navigates); a relative URL with no absolute base
 * throws TypeError, as the standard requires. */
static const char JD_URL_SHIM[] =
    "(function(){"
    "  var g=__G;"
    "  function encf(s){ return encodeURIComponent(String(s)).replace(/%20/g,'+'); }"
    "  function decf(s){ try{ return decodeURIComponent(String(s).replace(/\\+/g,' ')); }"
    "    catch(e){ return String(s); } }"
    "  if(typeof g.URLSearchParams==='undefined'){"
    "    function USP(init){ this._e=[];"
    "      if(init==null||init===''){}"
    "      else if(typeof init==='string'){"
    "        var q=init.charAt(0)==='?'?init.slice(1):init;"
    "        if(q!==''){ var ps=q.split('&');"
    "          for(var i=0;i<ps.length;i++){ if(ps[i]==='') continue;"
    "            var d=ps[i].indexOf('='),k,v;"
    "            if(d<0){ k=ps[i]; v=''; } else { k=ps[i].slice(0,d); v=ps[i].slice(d+1); }"
    "            this._e.push([decf(k),decf(v)]); } } }"
    "      else if(Array.isArray(init)){"
    "        for(var j=0;j<init.length;j++) this._e.push([String(init[j][0]),String(init[j][1])]); }"
    "      else if(typeof init==='object'){"
    "        for(var key in init){ if(Object.prototype.hasOwnProperty.call(init,key))"
    "          this._e.push([String(key),String(init[key])]); } } }"
    "    USP.prototype.append=function(k,v){ this._e.push([String(k),String(v)]); };"
    "    USP.prototype.delete=function(k){ k=String(k);"
    "      this._e=this._e.filter(function(p){return p[0]!==k;}); };"
    "    USP.prototype.get=function(k){ k=String(k);"
    "      for(var i=0;i<this._e.length;i++) if(this._e[i][0]===k) return this._e[i][1]; return null; };"
    "    USP.prototype.getAll=function(k){ k=String(k); var o=[];"
    "      for(var i=0;i<this._e.length;i++) if(this._e[i][0]===k) o.push(this._e[i][1]); return o; };"
    "    USP.prototype.has=function(k){ return this.get(String(k))!==null; };"
    "    USP.prototype.set=function(k,v){ k=String(k); v=String(v); var done=false,o=[];"
    "      for(var i=0;i<this._e.length;i++){ if(this._e[i][0]===k){ if(!done){o.push([k,v]);done=true;} }"
    "        else o.push(this._e[i]); } if(!done) o.push([k,v]); this._e=o; };"
    "    USP.prototype.sort=function(){ this._e.sort(function(a,b){"
    "      return a[0]<b[0]?-1:(a[0]>b[0]?1:0); }); };"
    "    USP.prototype.forEach=function(cb,t){"
    "      for(var i=0;i<this._e.length;i++) cb.call(t,this._e[i][1],this._e[i][0],this); };"
    "    USP.prototype.keys=function(){ return this._e.map(function(p){return p[0];})[Symbol.iterator](); };"
    "    USP.prototype.values=function(){ return this._e.map(function(p){return p[1];})[Symbol.iterator](); };"
    "    USP.prototype.entries=function(){ return this._e.map(function(p){return [p[0],p[1]];})[Symbol.iterator](); };"
    "    USP.prototype[Symbol.iterator]=function(){ return this.entries(); };"
    "    USP.prototype.toString=function(){ return this._e.map(function(p){"
    "      return encf(p[0])+'='+encf(p[1]); }).join('&'); };"
    "    Object.defineProperty(USP.prototype,'size',{get:function(){return this._e.length;},configurable:true});"
    "    g.URLSearchParams=USP; }"
    "  if(typeof g.URL==='undefined'){"
    "    var SPLIT=/^(?:([^:\\/?#]+):)?(?:\\/\\/([^\\/?#]*))?([^?#]*)(?:\\?([^#]*))?(?:#(.*))?$/;"
    "    function split(u){ var m=SPLIT.exec(String(u));"
    "      return {scheme:m[1],auth:m[2],path:m[3]||'',query:m[4],frag:m[5]}; }"
    "    function removeDots(p){ var inp=p,out='';"
    "      while(inp.length){"
    "        if(inp.slice(0,3)==='../') inp=inp.slice(3);"
    "        else if(inp.slice(0,2)==='./') inp=inp.slice(2);"
    "        else if(inp.slice(0,3)==='/./') inp='/'+inp.slice(3);"
    "        else if(inp==='/.') inp='/';"
    "        else if(inp.slice(0,4)==='/../'){ inp='/'+inp.slice(4); out=out.replace(/\\/?[^\\/]*$/,''); }"
    "        else if(inp==='/..'){ inp='/'; out=out.replace(/\\/?[^\\/]*$/,''); }"
    "        else if(inp==='.'||inp==='..'){ inp=''; }"
    "        else { var m=/^\\/?[^\\/]*/.exec(inp); out+=m[0]; inp=inp.slice(m[0].length); } }"
    "      return out; }"
    "    function merge(B,rp){ if(B.auth!==undefined && B.path===''){ return '/'+rp; }"
    "      var i=B.path.lastIndexOf('/'); return i<0?rp:B.path.slice(0,i+1)+rp; }"
    "    function resolve(baseStr,refStr){ var R=split(refStr),B=baseStr!=null?split(baseStr):null,T={};"
    "      if(R.scheme!==undefined){ T.scheme=R.scheme; T.auth=R.auth; T.path=removeDots(R.path); T.query=R.query; }"
    "      else { if(!B||B.scheme===undefined) return null;"
    "        if(R.auth!==undefined){ T.auth=R.auth; T.path=removeDots(R.path); T.query=R.query; }"
    "        else { if(R.path===''){ T.path=B.path; T.query=R.query!==undefined?R.query:B.query; }"
    "          else { if(R.path.charAt(0)==='/') T.path=removeDots(R.path);"
    "            else T.path=removeDots(merge(B,R.path)); T.query=R.query; } T.auth=B.auth; }"
    "        T.scheme=B.scheme; } T.frag=R.frag; return T; }"
    "    function parseAuth(a){ a=a||''; var user='',pass='',host='',port='';"
    "      var at=a.lastIndexOf('@'); if(at>=0){ var ui=a.slice(0,at); a=a.slice(at+1);"
    "        var c=ui.indexOf(':'); if(c>=0){user=ui.slice(0,c);pass=ui.slice(c+1);}else user=ui; }"
    "      var pm=/:(\\d*)$/.exec(a); if(pm){ port=pm[1]; host=a.slice(0,pm.index); } else host=a;"
    "      return {user:user,pass:pass,host:host,port:port}; }"
    "    function URLc(url,base){"
    "      var T=resolve(base!==undefined&&base!==null?String(base):null,String(url));"
    "      if(T===null) throw new TypeError('Invalid URL: '+String(url));"
    "      var A=parseAuth(T.auth); var path=T.path;"
    "      if(T.auth!==undefined && path==='') path='/';"
    "      this._scheme=T.scheme||''; this._auth=T.auth; this._user=A.user; this._pass=A.pass;"
    "      this._host=A.host; this._port=A.port; this._path=path;"
    "      this._query=T.query; this._frag=T.frag; this._sp=null; }"
    "    function q(u){ if(u._sp){ var s=u._sp.toString(); return s?'?'+s:''; }"
    "      return (u._query!==undefined&&u._query!=='')?'?'+u._query:''; }"
    "    Object.defineProperties(URLc.prototype,{"
    "      protocol:{get:function(){return this._scheme+':';},configurable:true},"
    "      username:{get:function(){return this._user;},configurable:true},"
    "      password:{get:function(){return this._pass;},configurable:true},"
    "      hostname:{get:function(){return this._host;},configurable:true},"
    "      port:{get:function(){return this._port;},configurable:true},"
    "      host:{get:function(){return this._host+(this._port?':'+this._port:'');},configurable:true},"
    "      pathname:{get:function(){return this._path;},configurable:true},"
    "      search:{get:function(){return q(this);},configurable:true},"
    "      hash:{get:function(){return (this._frag!==undefined&&this._frag!=='')?'#'+this._frag:'';},configurable:true},"
    "      origin:{get:function(){ if(this._auth===undefined) return 'null';"
    "        return this._scheme+'://'+this._host+(this._port?':'+this._port:''); },configurable:true},"
    "      searchParams:{get:function(){ if(!this._sp) this._sp=new g.URLSearchParams(this._query||''); return this._sp; },configurable:true},"
    "      href:{get:function(){ var s=this._scheme?this._scheme+':':'';"
    "        if(this._auth!==undefined){ s+='//'; if(this._user){ s+=this._user; if(this._pass) s+=':'+this._pass; s+='@'; }"
    "          s+=this._host+(this._port?':'+this._port:''); }"
    "        s+=this._path+q(this)+((this._frag!==undefined&&this._frag!=='')?'#'+this._frag:''); return s; },configurable:true}"
    "    });"
    "    URLc.prototype.toString=function(){ return this.href; };"
    "    URLc.prototype.toJSON=function(){ return this.href; };"
    "    g.URL=URLc; }"
    "})();";


jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque) {
    if (ctx == NULL || idx == NULL || opaque == NULL) return JD_ERR_NULL_ARG;

    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;

    /* The index and event state are reachable only from native code. */
    memset(opaque, 0, sizeof *opaque);
    opaque->idx = idx;
    JS_SetContextOpaque(jsctx, (void *)opaque);

    /* __G: the real global object, bound BEFORE any shim runs, non-writable and
     * non-configurable. Every shim resolves the global through it, never through the
     * identifier `globalThis`, which page polyfills rebind (openstreetmap.org did:
     * every listener registration then failed). A page cannot replace it (`var __G=`
     * is a silent no-op) nor shadow it (`let __G` is a SyntaxError on a
     * non-configurable global property). */
    {
        JSValue g0 = JS_GetGlobalObject(jsctx);
        if (JS_IsException(g0)) return JD_ERR_OOM;
        int drc = JS_DefinePropertyValueStr(jsctx, g0, "__G", JS_DupValue(jsctx, g0), 0);
        JS_FreeValue(jsctx, g0);
        if (drc < 0) return JD_ERR_INTERNAL;
    }

    JSValue dom = JS_NewObject(jsctx);
    if (JS_IsException(dom)) return JD_ERR_OOM;

    /* Methods are read-only and non-configurable: they cannot be hijacked. */
    for (size_t i = 0; i < sizeof JD_METHODS / sizeof JD_METHODS[0]; ++i) {
        JSValue fn = JS_NewCFunction(jsctx, JD_METHODS[i].fn,
                                     JD_METHODS[i].name, JD_METHODS[i].nargs);
        if (JS_IsException(fn)) { JS_FreeValue(jsctx, dom); return JD_ERR_OOM; }
        JS_DefinePropertyValueStr(jsctx, dom, JD_METHODS[i].name, fn,
                                  JS_PROP_ENUMERABLE);
    }

    /* Seal the object: no new properties can be added from script. */
    JS_PreventExtensions(jsctx, dom);

    JSValue global = JS_GetGlobalObject(jsctx);
    if (JS_IsException(global)) { JS_FreeValue(jsctx, dom); return JD_ERR_OOM; }
    int rc = JS_DefinePropertyValueStr(jsctx, global, "dom", dom,
                                       JS_PROP_ENUMERABLE);
    JS_FreeValue(jsctx, global);
    if (rc < 0) return JD_ERR_INTERNAL;

    /* Install the `document` facade (depends on the `dom` global just defined). */
    JSValue r = JS_Eval(jsctx, JD_DOCUMENT_SHIM, sizeof JD_DOCUMENT_SHIM - 1,
                        "<document-shim>", JS_EVAL_TYPE_GLOBAL);
    int shim_ok = !JS_IsException(r);
    JS_FreeValue(jsctx, r);
    if (!shim_ok) return JD_ERR_INTERNAL;

    /* Install the modern ambient surface (depends on the document shim's helpers). */
    JSValue r2 = JS_Eval(jsctx, JD_MODERN_SHIM, sizeof JD_MODERN_SHIM - 1,
                         "<modern-shim>", JS_EVAL_TYPE_GLOBAL);
    int mod_ok = !JS_IsException(r2);
    JS_FreeValue(jsctx, r2);
    if (!mod_ok) return JD_ERR_INTERNAL;

    /* Install WHATWG URL / URLSearchParams (pure string parsers; no I/O, no net). */
    JSValue r3 = JS_Eval(jsctx, JD_URL_SHIM, sizeof JD_URL_SHIM - 1,
                         "<url-shim>", JS_EVAL_TYPE_GLOBAL);
    int url_ok = !JS_IsException(r3);
    JS_FreeValue(jsctx, r3);
    if (!url_ok) return JD_ERR_INTERNAL;
    /* DOM Standard extras + data APIs: after the interface chains (modern shim) and
     * after URL (object URLs hang off it). */
    return (jdx_install(jsctx) == 0) ? JD_OK : JD_ERR_INTERNAL;
}

/* --- capturing console (Freebug) --- */

/* Appends src[0..srclen) to *buf (grown on demand), hard-capped at
 * FB_MAX_ENTRY_BYTES total so a hostile console.log of a huge string costs bounded
 * work/memory here too (fb_buffer_push would truncate anyway). Returns 1 when the
 * cap is reached or an allocation fails (caller stops), else 0. */
static int cb_append(char **buf, size_t *len, size_t *cap,
                     const char *src, size_t srclen) {
    if (*len >= FB_MAX_ENTRY_BYTES) return 1;
    size_t room = FB_MAX_ENTRY_BYTES - *len;
    if (srclen > room) srclen = room;
    if (*len + srclen + 1 > *cap) {
        size_t ncap = *cap ? *cap * 2 : 128;
        while (ncap < *len + srclen + 1) ncap *= 2;
        if (ncap > FB_MAX_ENTRY_BYTES + 1) ncap = FB_MAX_ENTRY_BYTES + 1;
        char *g = (char *)realloc(*buf, ncap);
        if (g == NULL) return 1;
        *buf = g; *cap = ncap;
    }
    if (srclen != 0) memcpy(*buf + *len, src, srclen);
    *len += srclen;
    (*buf)[*len] = '\0';
    return (*len >= FB_MAX_ENTRY_BYTES);
}

/* console.<level>(...args): join args with single spaces (each via toString),
 * push the line into the runtime's fb_buffer. magic carries the fb_level. A
 * toString that throws is swallowed (its exception cleared) so logging never
 * disturbs the calling script. */
static JSValue m_console(JSContext *ctx, JSValueConst this_val,
                         int argc, JSValueConst *argv, int magic) {
    (void)this_val;
    fb_buffer *log = (fb_buffer *)JS_GetRuntimeOpaque(JS_GetRuntime(ctx));
    if (log == NULL) return JS_UNDEFINED; /* capture disabled: silent no-op */

    char *msg = NULL;
    size_t len = 0, cap = 0;
    int full = 0;
    for (int i = 0; i < argc && !full; ++i) {
        if (i > 0 && cb_append(&msg, &len, &cap, " ", 1)) break;
        size_t sl = 0;
        const char *s = NULL;
        char tagbuf[96];
        /* An Error prints its stack (or "Name: message"): JSON of an Error is "{}"
         * because none of its fields are own-enumerable, which hid every reported
         * failure. An element wrapper prints as <tag#id>. */
        if (JS_IsError(argv[i])) {
            JSValue st = JS_GetPropertyStr(ctx, argv[i], "stack");
            JSValue txt = JS_ToString(ctx, argv[i]);   /* "Name: message" */
            const char *a = JS_IsString(txt) ? JS_ToCString(ctx, txt) : NULL;
            const char *b = JS_IsString(st) ? JS_ToCString(ctx, st) : NULL;
            if (a != NULL) {
                full = cb_append(&msg, &len, &cap, a, strlen(a));
                JS_FreeCString(ctx, a);
            }
            if (b != NULL && !full) {
                full = cb_append(&msg, &len, &cap, "\n", 1)
                    || cb_append(&msg, &len, &cap, b, strlen(b));
                JS_FreeCString(ctx, b);
            } else if (b != NULL) {
                JS_FreeCString(ctx, b);
            }
            if (JS_IsException(txt)) JS_FreeValue(ctx, JS_GetException(ctx));
            JS_FreeValue(ctx, txt);
            JS_FreeValue(ctx, st);
            continue;
        }
        if (JS_IsObject(argv[i])) {
            JSValue hv = JS_GetPropertyStr(ctx, argv[i], "_h");
            int32_t hid = -1;
            if (JS_IsNumber(hv) && JS_ToInt32(ctx, &hid, hv) == 0 && hid >= 0) {
                size_t tl = 0, il = 0;
                const char *tag = dom_tag_name(jd_idx(ctx), (dom_node_id)hid, &tl);
                const char *id = dom_get_attribute(jd_idx(ctx), (dom_node_id)hid, "id", &il);
                int n = snprintf(tagbuf, sizeof tagbuf, "<%.*s%s%.*s>",
                                 (int)(tl < 40 ? tl : 40), tag != NULL ? tag : "?",
                                 (id != NULL && il != 0) ? "#" : "",
                                 (int)(il < 40 ? il : 40), id != NULL ? id : "");
                if (n > 0 && (size_t)n < sizeof tagbuf) {
                    JS_FreeValue(ctx, hv);
                    full = cb_append(&msg, &len, &cap, tagbuf, (size_t)n);
                    continue;
                }
            }
            JS_FreeValue(ctx, hv);
        }
        if (JS_IsObject(argv[i])) {
            JSValue json = JS_JSONStringify(ctx, argv[i], JS_UNDEFINED, JS_UNDEFINED);
            if (!JS_IsException(json)) {
                if (JS_IsString(json)) s = JS_ToCStringLen(ctx, &sl, json);
                JS_FreeValue(ctx, json);
            } else {
                JS_FreeValue(ctx, JS_GetException(ctx));
            }
        }
        if (s == NULL) {
            s = JS_ToCStringLen(ctx, &sl, argv[i]);
            if (s == NULL) {
                JS_FreeValue(ctx, JS_GetException(ctx));
                full = cb_append(&msg, &len, &cap, "<unprintable>", 13);
                continue;
            }
        }
        full = cb_append(&msg, &len, &cap, s, sl);
        JS_FreeCString(ctx, s);
    }
    fb_buffer_push(log, magic, (msg != NULL) ? msg : "", len);
    free(msg);
    return JS_UNDEFINED;
}

/* Non-capturing console methods scripts commonly call: defined as no-ops so they
 * never throw a ReferenceError (they produce no Freebug entry). */
static const char JD_CONSOLE_EXTRA[] =
    "(function(){var c=__G.console;"
    "['assert','group','groupCollapsed','groupEnd','count','countReset',"
    "'time','timeEnd','timeLog','table','clear','dirxml'].forEach("
    "function(k){ if(typeof c[k]!=='function') c[k]=function(){}; });})();";

jd_status jd_install_console(js_context *ctx, fb_buffer *log) {
    if (ctx == NULL) return JD_ERR_NULL_ARG;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;

    /* The buffer is reachable only from native code, never from script. */
    JS_SetRuntimeOpaque(JS_GetRuntime(jsctx), (void *)log);

    JSValue console = JS_NewObject(jsctx);
    if (JS_IsException(console)) return JD_ERR_OOM;

    static const struct { const char *name; int level; } LV[] = {
        { "log",   FB_LOG },   { "info", FB_INFO }, { "warn",  FB_WARN },
        { "error", FB_ERROR }, { "debug", FB_DEBUG }, { "trace", FB_DEBUG },
        { "dir",   FB_LOG },
    };
    for (size_t i = 0; i < sizeof LV / sizeof LV[0]; ++i) {
        JSValue fn = JS_NewCFunctionMagic(jsctx, m_console, LV[i].name, 1,
                                          JS_CFUNC_generic_magic, LV[i].level);
        if (JS_IsException(fn)) { JS_FreeValue(jsctx, console); return JD_ERR_OOM; }
        JS_DefinePropertyValueStr(jsctx, console, LV[i].name, fn, JS_PROP_ENUMERABLE);
    }

    JSValue global = JS_GetGlobalObject(jsctx);
    if (JS_IsException(global)) { JS_FreeValue(jsctx, console); return JD_ERR_OOM; }
    int rc = JS_SetPropertyStr(jsctx, global, "console", console); /* consumes console */
    JS_FreeValue(jsctx, global);
    if (rc < 0) return JD_ERR_INTERNAL;

    JSValue r = JS_Eval(jsctx, JD_CONSOLE_EXTRA, sizeof JD_CONSOLE_EXTRA - 1,
                        "<console-extra>", JS_EVAL_TYPE_GLOBAL);
    int ok = !JS_IsException(r);
    JS_FreeValue(jsctx, r);
    return ok ? JD_OK : JD_ERR_INTERNAL;
}


jd_status jd_set_cookies(js_context *ctx, const char *cookies) {
    if (ctx == NULL) return JD_ERR_NULL_ARG;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;
    /* The cookie string is hostile (from the network jar); it is passed as a JS
     * STRING VALUE, never interpolated into source, so it cannot inject code. */
    JSValue global = JS_GetGlobalObject(jsctx);
    if (JS_IsException(global)) return JD_ERR_OOM;
    JS_SetPropertyStr(jsctx, global, "__ckSeed",
                      JS_NewString(jsctx, (cookies != NULL) ? cookies : ""));
    JS_FreeValue(jsctx, global);
    static const char en[] =
        "if(typeof __ckEnable==='function'){__ckEnable(__G.__ckSeed);"
        "__G.__ckSeed=undefined;}";
    JSValue r = JS_Eval(jsctx, en, sizeof en - 1, "<cookie-seed>", JS_EVAL_TYPE_GLOBAL);
    int ok = !JS_IsException(r);
    JS_FreeValue(jsctx, r);
    return ok ? JD_OK : JD_ERR_INTERNAL;
}

int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz) {
    if (ctx == NULL || buf == NULL || bufsz == 0) return 0;
    if (bufsz > 0) buf[0] = '\0';
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return 0;
    static const char q[] = "(typeof __ckDump==='function')?__ckDump():''";
    JSValue r = JS_Eval(jsctx, q, sizeof q - 1, "<cookie-dump>", JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(r)) { JS_FreeValue(jsctx, JS_GetException(jsctx)); return 0; }
    size_t slen = 0;
    const char *s = JS_ToCStringLen(jsctx, &slen, r);
    int n = 0;
    if (s != NULL) {
        if (slen >= bufsz) slen = bufsz - 1;
        memcpy(buf, s, slen);
        buf[slen] = '\0';
        n = (int)slen;
        JS_FreeCString(jsctx, s);
    }
    JS_FreeValue(jsctx, r);
    return n;
}


jd_status jd_set_geometry(js_context *ctx, const jg_table *geom) {
    if (ctx == NULL) return JD_ERR_NULL_ARG;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;
    jd_opaque *o = jd_opaque_get(jsctx);
    if (o == NULL) return JD_ERR_INTERNAL;
    o->geom = geom;
    return JD_OK;
}
