/*
 * js_dom — implementation of the DOM <-> JS bridge.
 *
 * Installs a frozen, read-only `dom` global into a js_sandbox context. The
 * dom_index lives in the engine's context opaque (unreachable from JS); native
 * functions retrieve it and proxy to the dom queries. Nodes are opaque integer
 * handles validated on every call; no live engine/node object is exposed.
 */

#define _POSIX_C_SOURCE 200809L

#include "js_dom.h"

#include "dom.h"
#include "freebug.h"
#include "js_sandbox.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "quickjs.h"

static jd_opaque *jd_opaque_get(JSContext *ctx) {
    return (jd_opaque *)JS_GetContextOpaque(ctx);
}

static dom_index *jd_idx(JSContext *ctx) {
    jd_opaque *o = jd_opaque_get(ctx);
    return (o != NULL) ? o->idx : NULL;
}


/* Coerces a JS argument to a node handle. Returns -1 with a pending exception
 * if coercion threw; otherwise stores the handle (out-of-range values stay
 * out of range and are rejected later by the dom validators). */
static int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out) {
    int64_t n;
    if (JS_ToInt64(ctx, &n, v) != 0) return -1;
    *out = (n < 0 || n > 0xFFFFFFFELL) ? DOM_NODE_NONE : (dom_node_id)n;
    return 0;
}

static JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h) {
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
        dom_node_id *buf = (dom_node_id *)malloc(total * sizeof *buf);
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

/* --- install --- */

typedef struct jd_method {
    const char *name;
    JSCFunction *fn;
    int          nargs;
} jd_method;

static JSValue m_register_click(JSContext *ctx, JSValueConst this_val,
                                int argc, JSValueConst *argv) {
    (void)this_val; (void)argc;
    dom_node_id h;
    if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION;
    if (!JS_IsFunction(ctx, argv[1])) return JS_UNDEFINED;

    JSValue global = JS_GetGlobalObject(ctx);
    if (JS_IsException(global)) return JS_EXCEPTION;
    JSValue reg = JS_GetPropertyStr(ctx, global, "__clickRegistry");
    if (JS_IsUndefined(reg) || JS_IsNull(reg)) {
        JS_FreeValue(ctx, reg);
        reg = JS_NewObject(ctx);
        if (JS_IsException(reg)) { JS_FreeValue(ctx, global); return JS_EXCEPTION; }
        JS_SetPropertyStr(ctx, global, "__clickRegistry", JS_DupValue(ctx, reg));
    }
    JS_SetPropertyUint32(ctx, reg, (uint32_t)h, JS_DupValue(ctx, argv[1]));
    JS_FreeValue(ctx, reg);
    JS_FreeValue(ctx, global);
    return JS_UNDEFINED;
}

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
        dom_node_id *buf = (dom_node_id *)malloc(total * sizeof *buf);
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

static const jd_method JD_METHODS[] = {
    { "nodeCount",      m_node_count,        0 },
    { "getElementById", m_get_element_by_id, 1 },
    { "getByTag",       m_get_by_tag,        1 },
    { "getByClass",     m_get_by_class,      1 },
    { "tagName",        m_tag_name,          1 },
    { "getAttribute",   m_get_attribute,     2 },
    { "parent",         m_parent,            1 },
    { "firstChild",     m_first_child,       1 },
    { "nextSibling",    m_next_sibling,      1 },
    { "precedes",       m_precedes,          2 },
    { "textContent",    m_text_content,      1 },
    { "setText",        m_set_text,          2 },
    { "getTitle",       m_get_title,         0 },
    { "setTitle",       m_set_title,         1 },
    { "createElement",  m_create_element,    1 },
    { "appendChild",    m_append_child,      2 },
    { "removeChild",    m_remove_child,      2 },
    { "setAttribute",   m_set_attribute,     3 },
    { "removeAttribute", m_remove_attribute, 2 },
    { "setInnerHtml",   m_set_inner_html,    2 },
    { "getInnerHtml",   m_get_inner_html,    1 },
    { "registerClick",  m_register_click,    2 },
    { "querySelector",    m_query_selector,     2 },
    { "querySelectorAll", m_query_selector_all, 2 },
    { "matches",          m_matches,            2 },
    { "closest",          m_closest,            2 },
};

/* A small standard `document` facade over the native handle API, so real page
 * scripts ("document.title = ...", "document.getElementById('x').textContent = ...")
 * work without exposing live engine node objects. Element wrappers carry only the
 * validated integer handle and proxy to the sealed `dom` methods. A no-op console
 * and window=globalThis keep common scripts from dying on a ReferenceError. */
static const char JD_DOCUMENT_SHIM[] =
    "(function(){"
    "  globalThis.__clickRegistry={};"
    "  var __wc={};"                          /* handle -> wrapper: stable node identity (===) */
    "  function wrap(h){"
    "    if (h===null||h===undefined) return null;"
    "    if (h in __wc) return __wc[h];"
    "    var el={_h:h, nodeType:1, ELEMENT_NODE:1, nodeName:'',"
    "      get textContent(){ return dom.textContent(h); },"
    "      set textContent(v){ dom.setText(h, String(v)); },"
    "      getAttribute: function(n){ return dom.getAttribute(h, String(n)); },"
    "      setAttribute: function(n,v){ dom.setAttribute(h, String(n), String(v)); },"
    "      removeAttribute: function(n){ dom.removeAttribute(h, String(n)); },"
    "      hasAttribute: function(n){ return dom.getAttribute(h, String(n))!==null; },"
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
    "      get tagName(){ var t=dom.tagName(h); return t===null?null:String(t).toUpperCase(); },"
    "      get id(){ var v=dom.getAttribute(h,'id'); return v===null?'':v; },"
    "      set id(v){ dom.setAttribute(h,'id',String(v)); },"
    "      get className(){ var v=dom.getAttribute(h,'class'); return v===null?'':v; },"
    "      set className(v){ dom.setAttribute(h,'class',String(v)); },"
    "      set innerHTML(v){ dom.setInnerHtml(h, String(v)); },"
    "      get innerHTML(){ return dom.getInnerHtml(h); },"
    /* A DocumentFragment carries its collected children in __frag; appending the
     * fragment re-parents each child (its contents), never the fragment node. */
    "      appendChild: function(c){ if(c&&c.__frag){ for(var i=0;i<c.__frag.length;i++) dom.appendChild(h,c.__frag[i]._h); c.__frag.length=0; return c; } if(c&&c._h!==undefined) dom.appendChild(h,c._h); return c; },"
    "      removeChild: function(c){ if(c&&c._h!==undefined) dom.removeChild(h,c._h); return c; },"
    "      insertBefore: function(n,ref){ if(n&&n.__frag){ for(var i=0;i<n.__frag.length;i++) dom.appendChild(h,n.__frag[i]._h); n.__frag.length=0; return n; } if(n&&n._h!==undefined) dom.appendChild(h,n._h); return n; },"
    "      replaceChild: function(nw,old){ if(old&&old._h!==undefined) dom.removeChild(h,old._h); if(nw&&nw._h!==undefined) dom.appendChild(h,nw._h); return old; },"
    "      append: function(){ for(var i=0;i<arguments.length;i++){ var a=arguments[i]; if(a&&a.__frag){ for(var j=0;j<a.__frag.length;j++) dom.appendChild(h,a.__frag[j]._h); a.__frag.length=0; } else if(a&&a._h!==undefined) dom.appendChild(h,a._h); } },"
    "      prepend: function(){ for(var i=0;i<arguments.length;i++){ var a=arguments[i]; if(a&&a._h!==undefined) dom.appendChild(h,a._h); } },"
    "      remove: function(){ var p=dom.parent(h); if(p!==null) dom.removeChild(p,h); },"
    "      cloneNode: function(){ var t=dom.tagName(h); if(t===null) return null; return wrap(dom.createElement(String(t))); },"
    "      insertAdjacentHTML: function(){}, insertAdjacentElement: function(){}, insertAdjacentText: function(){},"
    "      get parentNode(){ var p=dom.parent(h); return p===null?null:wrap(p); },"
    "      get parentElement(){ var p=dom.parent(h); return p===null?null:wrap(p); },"
    "      get firstChild(){ var c=dom.firstChild(h); return c===null?null:wrap(c); },"
    "      get firstElementChild(){ var c=dom.firstChild(h); return c===null?null:wrap(c); },"
    "      get nextSibling(){ var s=dom.nextSibling(h); return s===null?null:wrap(s); },"
    "      get nextElementSibling(){ var s=dom.nextSibling(h); return s===null?null:wrap(s); },"
    "      get lastChild(){ var c=dom.firstChild(h),l=null; while(c!==null){ l=c; c=dom.nextSibling(c); } return l===null?null:wrap(l); },"
    "      get lastElementChild(){ var c=dom.firstChild(h),l=null; while(c!==null){ l=c; c=dom.nextSibling(c); } return l===null?null:wrap(l); },"
    "      get children(){ var r=[]; var c=dom.firstChild(h); while(c!==null){ r.push(wrap(c)); c=dom.nextSibling(c); } return r; },"
    "      get childNodes(){ var r=[]; var c=dom.firstChild(h); while(c!==null){ r.push(wrap(c)); c=dom.nextSibling(c); } return r; },"
    "      get childElementCount(){ var n=0; var c=dom.firstChild(h); while(c!==null){ n++; c=dom.nextSibling(c); } return n; },"
    "      hasChildNodes: function(){ return dom.firstChild(h)!==null; },"
    "      contains: function(o){ if(!o||o._h===undefined) return false; for(var p=o._h;p!==null&&p!==undefined;){ if(p===h) return true; p=dom.parent(p); } return false; },"
    "      getElementsByTagName: function(t){ return wrapList(dom.querySelectorAll(h, String(t))); },"
    "      getElementsByClassName: function(c){ return wrapList(dom.querySelectorAll(h, '.'+String(c))); },"
    "      addEventListener: function(t,fn){ if(t==='click'&&typeof fn==='function') dom.registerClick(h, fn); },"
    "      removeEventListener: function(){}, dispatchEvent: function(){ return true; },"
    "      querySelector: function(s){ return wrap(dom.querySelector(h, String(s))); },"
    "      querySelectorAll: function(s){ return wrapList(dom.querySelectorAll(h, String(s))); },"
    "      matches: function(s){ return dom.matches(h, String(s)); },"
    "      webkitMatchesSelector: function(s){ return dom.matches(h, String(s)); },"
    "      closest: function(s){ return wrap(dom.closest(h, String(s))); },"
    "      focus: function(){}, blur: function(){}, click: function(){},"
    "      scrollIntoView: function(){}, getBoundingClientRect: function(){ return {x:0,y:0,top:0,left:0,right:0,bottom:0,width:0,height:0}; },"
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
    "    Object.defineProperty(el,'onclick',{set:function(fn){ if(typeof fn==='function') dom.registerClick(h, fn); },get:function(){return null;}});"
    "    __wc[h]=el;"
    "    return el;"
    "  }"
    "  globalThis.__wrap=wrap;"
    "  function wrapList(hs){ var r=[]; for (var i=0;i<hs.length;i++) r.push(wrap(hs[i])); return r; }"
    "  globalThis.__wrapList=wrapList;"
    "  var loadCbs=[], timers=[];"
    "  globalThis.__queueTimer=function(fn){ if(typeof fn==='function') timers.push(fn); };"
    "  function addL(type,fn){ if(typeof fn==='function' &&"
    "    (type==='load'||type==='DOMContentLoaded'||type==='readystatechange')) loadCbs.push(fn); }"
    "  var d={"
    "    getElementById: function(id){ return wrap(dom.getElementById(String(id))); },"
    "    getElementsByTagName: function(t){ return wrapList(dom.getByTag(String(t))); },"
    "    getElementsByClassName: function(c){ return wrapList(dom.getByClass(String(c))); },"
    "    createElement: function(t){ return wrap(dom.createElement(String(t))); },"
    "    createTextNode: function(t){ return {nodeType:3, textContent:String(t)}; },"
    "    addEventListener: function(type,fn){ addL(String(type),fn); },"
    "    removeEventListener: function(){}, readyState:'loading'"
    "  };"
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
    "  Object.defineProperty(d,'cookie',{get:function(){return '';},set:function(){},enumerable:true});"
    "  Object.defineProperty(d,'referrer',{get:function(){return '';},enumerable:true});"
    "  d.querySelector=function(s){ return wrap(dom.querySelector(-1, String(s))); };"
    "  d.querySelectorAll=function(s){ return wrapList(dom.querySelectorAll(-1, String(s))); };"
    "  d.getElementsByName=function(n){ return wrapList(dom.querySelectorAll(-1, '[name=\"'+String(n).replace(/\"/g,'')+'\"]')); };"
    /* createElementNS: the namespace is ignored (SVG/MathML become plain elements),
     * enough to keep scripts that build namespaced nodes from throwing. */
    "  d.createElementNS=function(ns,t){ return wrap(dom.createElement(String(t))); };"
    "  d.createComment=function(t){ return {nodeType:8, textContent:String(t), data:String(t)}; };"
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
    /* Event/CustomEvent shims so new Event('x')/document.createEvent do not throw. */
    "  function mkEvent(type,opts){ opts=opts||{}; return {type:String(type),bubbles:!!opts.bubbles,"
    "    cancelable:!!opts.cancelable,detail:(opts.detail!==undefined?opts.detail:null),defaultPrevented:false,"
    "    target:null,currentTarget:null,timeStamp:0,"
    "    preventDefault:function(){this.defaultPrevented=true;},stopPropagation:function(){},"
    "    stopImmediatePropagation:function(){},initEvent:function(t){this.type=String(t);},"
    "    initCustomEvent:function(t,b,c,dt){this.type=String(t);this.detail=dt;}}; }"
    "  d.createEvent=function(t){ return mkEvent('',{}); };"
    "  globalThis.__mkEvent=mkEvent;"
    "  Object.defineProperty(d,'hidden',{get:function(){return false;},enumerable:true});"
    "  Object.defineProperty(d,'visibilityState',{get:function(){return 'visible';},enumerable:true});"
    "  d.hasFocus=function(){return true;}; d.currentScript=null;"
    "  d.characterSet='UTF-8'; d.charset='UTF-8'; d.compatMode='CSS1Compat'; d.dir='';"
    "  Object.defineProperty(d,'activeElement',{get:function(){return tagOne('body');},enumerable:true});"
    "  Object.defineProperty(d,'scripts',{get:function(){return wrapList(dom.getByTag('script'));},enumerable:true});"
    "  Object.defineProperty(d,'images',{get:function(){return wrapList(dom.getByTag('img'));},enumerable:true});"
    "  Object.defineProperty(d,'forms',{get:function(){return wrapList(dom.getByTag('form'));},enumerable:true});"
    "  Object.defineProperty(d,'links',{get:function(){return wrapList(dom.querySelectorAll(-1,'a[href]'));},enumerable:true});"
    "  d.dispatchEvent=function(){ return true; };"
    "  d.implementation={ hasFeature:function(){return true;}, createHTMLDocument:function(){return d;} };"
    "  globalThis.document=d;"
    "  if (typeof globalThis.window==='undefined') globalThis.window=globalThis;"
    "  function memStore(){ var m={};"
    "    return { getItem:function(k){k=String(k);return Object.prototype.hasOwnProperty.call(m,k)?m[k]:null;},"
    "      setItem:function(k,v){m[String(k)]=String(v);},"
    "      removeItem:function(k){delete m[String(k)];},"
    "      clear:function(){m={};}, key:function(i){var ks=Object.keys(m);return i<ks.length?ks[i]:null;},"
    "      get length(){return Object.keys(m).length;} }; }"
    "  if (typeof globalThis.localStorage==='undefined') globalThis.localStorage=memStore();"
    "  if (typeof globalThis.sessionStorage==='undefined') globalThis.sessionStorage=memStore();"
    "  if (typeof globalThis.history==='undefined') globalThis.history={length:1,"
    "    state:null,pushState:function(){},replaceState:function(){},back:function(){},"
    "    forward:function(){},go:function(){}};"
    "  if (typeof globalThis.location==='undefined') globalThis.location={href:'',protocol:'https:',"
    "    host:'',hostname:'',pathname:'/',search:'',hash:'',origin:'',"
    "    assign:function(){},replace:function(){},reload:function(){}};"
    "  if (typeof globalThis.console==='undefined')"
    "    globalThis.console={log:function(){},warn:function(){},error:function(){},"
    "      info:function(){},debug:function(){}};"
    "  globalThis.addEventListener=function(type,fn){ addL(String(type),fn); };"
    "  globalThis.removeEventListener=function(){};"
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
    "  globalThis.setTimeout=function(fn,ms){ return tmAdd(fn,ms,0); };"
    "  globalThis.setInterval=function(fn,ms){ return tmAdd(fn,ms,1); };"
    "  globalThis.clearTimeout=tmDel; globalThis.clearInterval=tmDel;"
    /* rAF/rIC feed the same synthetic timer queue; the callback gets a fixed
     * timestamp (identity-safe: no real high-res clock leaks through animation). */
    "  globalThis.requestAnimationFrame=function(fn){ if(typeof fn!=='function') return 0;"
    "    return tmAdd(function(){ fn(0); },0,0); };"
    "  globalThis.cancelAnimationFrame=tmDel;"
    "  globalThis.requestIdleCallback=function(fn){ if(typeof fn!=='function') return 0;"
    "    return tmAdd(function(){ fn({didTimeout:false,timeRemaining:function(){return 0;}}); },0,0); };"
    "  globalThis.cancelIdleCallback=tmDel;"
    "  globalThis.queueMicrotask=function(fn){ if(typeof fn==='function') Promise.resolve().then(fn); };"
    /* Advances the virtual clock and fires everything due, in bounded ROUNDS (a
     * timer may schedule more timers). Intervals re-arm. Returns fired count. */
    "  globalThis.__tickTimers=function(elapsed){"
    "    var e=Number(elapsed)||0, fired=0, rounds=0;"
    "    for (var i=0;i<timers.length;i++) timers[i].due-=e;"
    "    while (rounds<8 && fired<256){"
    "      var due=[], rest=[];"
    "      for (var i=0;i<timers.length;i++) (timers[i].due<=0?due:rest).push(timers[i]);"
    "      if (due.length===0) break;"
    "      timers=rest; rounds++;"
    "      for (var j=0;j<due.length && fired<256;j++){ fired++;"
    "        try{ due[j].f.call(globalThis); }catch(ex){}"
    "        if (due[j].iv>0){ due[j].due=due[j].iv; timers.push(due[j]); }"
    "      }"
    "    }"
    "    return fired;"
    "  };"
    /* Smallest remaining delay (>= 0), or -1 when nothing is pending -- the parent
     * uses it to schedule the next OP_TICK. */
    "  globalThis.__nextTimerMs=function(){"
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
    "  globalThis.__fireDeferred=function(){"
    "    d.readyState='complete';"
    "    for (var i=0;i<loadCbs.length;i++){ try{ loadCbs[i].call(globalThis); }catch(e){} }"
    "    if (typeof globalThis.onload==='function'){ try{ globalThis.onload(); }catch(e){} }"
    "    if (typeof d.onload==='function'){ try{ d.onload(); }catch(e){} }"
    "    globalThis.__tickTimers(0);"
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
    "  var g=globalThis;"
    "  function stubCtor(){ function F(){} return F; }"
    "  ['Node','Element','HTMLElement','HTMLDivElement','HTMLSpanElement','HTMLAnchorElement',"
    "   'HTMLImageElement','HTMLInputElement','HTMLButtonElement','HTMLScriptElement','HTMLStyleElement',"
    "   'HTMLDocument','Document','DocumentFragment','ShadowRoot','CharacterData','Text','Comment','Attr',"
    "   'DOMTokenList','NodeList','HTMLCollection','CSSStyleDeclaration','EventTarget','XMLDocument'].forEach("
    "    function(n){ if(typeof g[n]==='undefined') g[n]=stubCtor(); });"
    "  if(g.Node){ g.Node.ELEMENT_NODE=1; g.Node.TEXT_NODE=3; g.Node.COMMENT_NODE=8;"
    "    g.Node.DOCUMENT_NODE=9; g.Node.DOCUMENT_FRAGMENT_NODE=11; }"
    "  function evCtor(){ return function(type,opts){ return g.__mkEvent?g.__mkEvent(type,opts):{type:String(type)}; }; }"
    "  ['Event','CustomEvent','MouseEvent','KeyboardEvent','PointerEvent','UIEvent','FocusEvent',"
    "   'InputEvent','TouchEvent','WheelEvent','MessageEvent','PopStateEvent','HashChangeEvent',"
    "   'ErrorEvent','ProgressEvent'].forEach(function(n){ if(typeof g[n]==='undefined') g[n]=evCtor(); });"
    "  if(typeof g.matchMedia==='undefined') g.matchMedia=function(q){ return {matches:false,"
    "    media:String(q||''),onchange:null,addListener:function(){},removeListener:function(){},"
    "    addEventListener:function(){},removeEventListener:function(){},dispatchEvent:function(){return false;}}; };"
    "  function observer(){ function O(cb){ this._cb=cb; } O.prototype.observe=function(){};"
    "    O.prototype.unobserve=function(){}; O.prototype.disconnect=function(){};"
    "    O.prototype.takeRecords=function(){return [];}; return O; }"
    "  ['MutationObserver','IntersectionObserver','ResizeObserver','PerformanceObserver'].forEach("
    "    function(n){ if(typeof g[n]==='undefined') g[n]=observer(); });"
    "  if(typeof g.getComputedStyle==='undefined') g.getComputedStyle=function(){"
    "    var o={ getPropertyValue:function(){return '';}, getPropertyPriority:function(){return '';},"
    "      length:0, item:function(){return '';} };"
    "    return new Proxy(o,{ get:function(t,p){ if(p in t) return t[p]; return ''; } }); };"
    "  function ro(name,val){ if(typeof g[name]==='undefined'){ try{ Object.defineProperty(g,name,"
    "    {get:function(){return val;},configurable:true}); }catch(e){ try{ g[name]=val; }catch(e2){} } } }"
    "  ro('innerWidth',1920); ro('innerHeight',1080); ro('outerWidth',1920); ro('outerHeight',1080);"
    "  ro('devicePixelRatio',1); ro('scrollX',0); ro('scrollY',0); ro('pageXOffset',0); ro('pageYOffset',0);"
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
    "  if(typeof g.customElements==='undefined') g.customElements={ define:function(){},"
    "    get:function(){return undefined;}, whenDefined:function(){return Promise.resolve();}, upgrade:function(){} };"
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
    "  var g=globalThis;"
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

/* --- real location + JS-navigation capture (Hito 20e parte 1) --- */

/* Defines a string property on the __locParts data object from a (ptr,len) span.
 * The span is copied into an engine string; a NULL span becomes "". */
static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,
                      const char *p, size_t len) {
    JSValue s = (p != NULL) ? JS_NewStringLen(ctx, p, len) : JS_NewString(ctx, "");
    JS_SetPropertyStr(ctx, obj, name, s); /* consumes s; name copied */
}

/* Reads the page URL components from globalThis.__locParts (set natively, so a hostile
 * URL is never interpolated into JS) and installs a real, read-only `location`. The
 * navigating writes only RECORD the raw request into __navReq/__navReplace; they never
 * execute or resolve it. The trusted parent gates the raw string with ln_resolve. */
static const char JD_LOCATION_SHIM[] =
    "(function(){"
    "  var lp = globalThis.__locParts || {};"
    "  function nav(u, replace){ globalThis.__navReq = String(u);"
    "    globalThis.__navReplace = !!replace; }"
    "  var loc = {"
    "    get href(){ return lp.href||''; }, set href(v){ nav(v,false); },"
    "    get protocol(){ return lp.protocol||'https:'; },"
    "    get host(){ return lp.host||''; },"
    "    get hostname(){ return lp.hostname||''; },"
    "    get port(){ return lp.port||''; },"
    "    get pathname(){ return lp.pathname||'/'; },"
    "    get search(){ return lp.search||''; },"
    "    get hash(){ return lp.hash||''; },"
    "    get origin(){ return lp.origin||''; },"
    "    assign: function(u){ nav(u,false); },"
    "    replace: function(u){ nav(u,true); },"
    "    reload: function(){ nav(lp.href||'', true); },"
    "    toString: function(){ return lp.href||''; }"
    "  };"
    "  try{ Object.defineProperty(globalThis,'location',{configurable:true,"
    "    get:function(){return loc;}, set:function(v){ nav(v,false); }}); }catch(e){}"
    "  try{ if(typeof document!=='undefined'){"
    "    Object.defineProperty(document,'location',{configurable:true,enumerable:true,"
    "      get:function(){return loc;}, set:function(v){ nav(v,false); }});"
    "    Object.defineProperty(document,'URL',{configurable:true,enumerable:true,"
    "      get:function(){return lp.href||'';}});"
    "    Object.defineProperty(document,'documentURI',{configurable:true,enumerable:true,"
    "      get:function(){return lp.href||'';}});"
    "  } }catch(e){}"
    "})();";

jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque) {
    if (ctx == NULL || idx == NULL || opaque == NULL) return JD_ERR_NULL_ARG;

    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;

    /* The index and event state are reachable only from native code. */
    memset(opaque, 0, sizeof *opaque);
    opaque->idx = idx;
    JS_SetContextOpaque(jsctx, (void *)opaque);

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
    return url_ok ? JD_OK : JD_ERR_INTERNAL;
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
        const char *s = JS_ToCStringLen(ctx, &sl, argv[i]);
        if (s == NULL) {
            JS_FreeValue(ctx, JS_GetException(ctx)); /* swallow toString error */
            full = cb_append(&msg, &len, &cap, "<unprintable>", 13);
            continue;
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
    "(function(){var c=globalThis.console;"
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

jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts) {
    if (ctx == NULL) return JD_ERR_NULL_ARG;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;

    JSValue global = JS_GetGlobalObject(jsctx);
    if (JS_IsException(global)) return JD_ERR_OOM;

    JSValue lp = JS_NewObject(jsctx);
    if (JS_IsException(lp)) { JS_FreeValue(jsctx, global); return JD_ERR_OOM; }

    jd_lp_set(jsctx, lp, "href", href, (href != NULL) ? strlen(href) : 0);
    if (parts != NULL) {
        jd_lp_set(jsctx, lp, "protocol", parts->protocol, parts->protocol_len);
        jd_lp_set(jsctx, lp, "origin",   parts->origin,   parts->origin_len);
        jd_lp_set(jsctx, lp, "host",     parts->host,     parts->host_len);
        jd_lp_set(jsctx, lp, "hostname", parts->hostname, parts->hostname_len);
        jd_lp_set(jsctx, lp, "port",     parts->port,     parts->port_len);
        jd_lp_set(jsctx, lp, "pathname", parts->pathname, parts->pathname_len);
        jd_lp_set(jsctx, lp, "search",   parts->search,   parts->search_len);
        jd_lp_set(jsctx, lp, "hash",     parts->hash,     parts->hash_len);
    }
    JS_SetPropertyStr(jsctx, global, "__locParts", lp);  /* consumes lp */
    JS_SetPropertyStr(jsctx, global, "__navReq", JS_NewString(jsctx, ""));
    JS_SetPropertyStr(jsctx, global, "__navReplace", JS_NewBool(jsctx, 0));
    JS_FreeValue(jsctx, global);

    JSValue r = JS_Eval(jsctx, JD_LOCATION_SHIM, sizeof JD_LOCATION_SHIM - 1,
                        "<location-shim>", JS_EVAL_TYPE_GLOBAL);
    int ok = !JS_IsException(r);
    JS_FreeValue(jsctx, r);
    return ok ? JD_OK : JD_ERR_INTERNAL;
}

int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace) {
    if (replace != NULL) *replace = 0;
    if (ctx == NULL || buf == NULL || bufsz == 0) return 0;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return 0;

    JSValue global = JS_GetGlobalObject(jsctx);
    if (JS_IsException(global)) return 0;

    buf[0] = '\0';
    int present = 0;
    JSValue req = JS_GetPropertyStr(jsctx, global, "__navReq");
    if (!JS_IsUndefined(req) && !JS_IsNull(req)) {
        const char *s = JS_ToCString(jsctx, req);
        if (s != NULL && s[0] != '\0') {
            size_t n = strlen(s);
            if (n >= bufsz) n = bufsz - 1;
            memcpy(buf, s, n);
            buf[n] = '\0';
            present = 1;
        }
        if (s != NULL) JS_FreeCString(jsctx, s);
    }
    JS_FreeValue(jsctx, req);

    if (present && replace != NULL) {
        JSValue rep = JS_GetPropertyStr(jsctx, global, "__navReplace");
        *replace = JS_ToBool(jsctx, rep) ? 1 : 0;
        JS_FreeValue(jsctx, rep);
    }
    if (present) /* clear so a later op does not re-trigger the same navigation */
        JS_SetPropertyStr(jsctx, global, "__navReq", JS_NewString(jsctx, ""));

    JS_FreeValue(jsctx, global);
    return present;
}

/* --- XMLHttpRequest / fetch (parent-gated network; sovereignty boundary) --- */

/* Carry the host fetch fn + its ctx as a function's closure data, each split into
 * 32-bit halves (no assumption about JS number width). The data lives with the
 * function object and is freed with the context: no global state, no leak. */
static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p) {
    uint64_t u = (uint64_t)(uintptr_t)p;
    out2[0] = JS_NewInt32(ctx, (int32_t)(uint32_t)(u & 0xFFFFFFFFu));
    out2[1] = JS_NewInt32(ctx, (int32_t)(uint32_t)(u >> 32));
}
static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi) {
    int32_t l = 0, h = 0;
    JS_ToInt32(ctx, &l, lo);
    JS_ToInt32(ctx, &h, hi);
    uint64_t u = ((uint64_t)(uint32_t)h << 32) | (uint32_t)l;
    return (void *)(uintptr_t)u;
}

/* __hostFetch(method, url, body) -> { status, body, contentType }. The ONLY network
 * primitive exposed to script; it does NOT touch a socket -- it calls the host fetch
 * callback, which proxies to the trusted parent (full network policy re-applied there).
 * Fail-closed: a refused/failed request yields { status:0, body:'', contentType:'' },
 * never an exception that tells the page why. */
static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,
                            int argc, JSValueConst *argv, int magic, JSValue *fd) {
    (void)this_val; (void)magic;
    jd_fetch_fn fn = (jd_fetch_fn)jd_unpack_ptr(ctx, fd[0], fd[1]);
    void *fctx     = jd_unpack_ptr(ctx, fd[2], fd[3]);

    const char *method = (argc > 0) ? JS_ToCString(ctx, argv[0]) : NULL;
    const char *url    = (argc > 1) ? JS_ToCString(ctx, argv[1]) : NULL;
    size_t blen = 0;
    const char *body   = (argc > 2 && !JS_IsUndefined(argv[2]) && !JS_IsNull(argv[2]))
                         ? JS_ToCStringLen(ctx, &blen, argv[2]) : NULL;

    int status = 0; char *rbody = NULL; size_t rlen = 0; char *rctype = NULL;
    int rc = -1;
    if (fn != NULL && url != NULL)
        rc = fn(fctx, method ? method : "GET", url, body ? body : "", blen,
                &status, &rbody, &rlen, &rctype);

    JSValue o = JS_NewObject(ctx);
    if (rc == 0) {
        JS_SetPropertyStr(ctx, o, "status", JS_NewInt32(ctx, status));
        JS_SetPropertyStr(ctx, o, "body", JS_NewStringLen(ctx, rbody ? rbody : "", rlen));
        JS_SetPropertyStr(ctx, o, "contentType", JS_NewString(ctx, rctype ? rctype : ""));
    } else { /* fail-closed */
        JS_SetPropertyStr(ctx, o, "status", JS_NewInt32(ctx, 0));
        JS_SetPropertyStr(ctx, o, "body", JS_NewString(ctx, ""));
        JS_SetPropertyStr(ctx, o, "contentType", JS_NewString(ctx, ""));
    }
    free(rbody); free(rctype);
    if (method != NULL) JS_FreeCString(ctx, method);
    if (url != NULL)    JS_FreeCString(ctx, url);
    if (body != NULL)   JS_FreeCString(ctx, body);
    return o;
}

/* XMLHttpRequest + fetch over the single synchronous __hostFetch primitive. The
 * round-trip is synchronous under the hood (the worker blocks on the parent), so XHR
 * callbacks fire right after send(); fetch returns a resolved promise (its .then/await
 * run when the worker pumps the job queue). __hostFetch is captured into a closure and
 * then deleted from the global, so page script cannot call it directly. */
static const char JD_XHR_SHIM[] =
    "(function(){"
    "var HF=globalThis.__hostFetch; if(typeof HF!=='function')return;"
    "function fire(o,n){var f=o['on'+n]; if(typeof f==='function'){try{f.call(o);}catch(e){}}}"
    "function XHR(){this.readyState=0;this.status=0;this.statusText='';this.responseText='';"
    "this.response='';this.responseType='';this.responseURL='';this.withCredentials=false;"
    "this.onreadystatechange=null;this.onload=null;this.onerror=null;this.onloadend=null;"
    "this._m='GET';this._u='';this._h='';}"
    "XHR.UNSENT=0;XHR.OPENED=1;XHR.HEADERS_RECEIVED=2;XHR.LOADING=3;XHR.DONE=4;"
    "XHR.prototype.open=function(m,u){this._m=String(m||'GET');this._u=String(u||'');"
    "this.responseURL=this._u;this.readyState=1;fire(this,'readystatechange');};"
    "XHR.prototype.setRequestHeader=function(){};"
    "XHR.prototype.getAllResponseHeaders=function(){return this._h;};"
    "XHR.prototype.getResponseHeader=function(k){k=String(k).toLowerCase();"
    "var ls=this._h.split('\\r\\n');for(var i=0;i<ls.length;i++){var p=ls[i].indexOf(':');"
    "if(p>0&&ls[i].slice(0,p).toLowerCase().trim()===k)return ls[i].slice(p+1).trim();}return null;};"
    "XHR.prototype.abort=function(){};XHR.prototype.overrideMimeType=function(){};"
    "XHR.prototype.send=function(b){var r;try{r=HF(this._m,this._u,(b==null?'':String(b)));}catch(e){r=null;}"
    "if(!r||(r.status|0)===0){this.status=0;this.readyState=4;fire(this,'readystatechange');"
    "fire(this,'error');fire(this,'loadend');return;}"
    "this.status=r.status|0;this.responseText=r.body||'';"
    "this._h=r.contentType?('content-type: '+r.contentType+'\\r\\n'):'';"
    "if(this.responseType==='json'){try{this.response=JSON.parse(this.responseText);}catch(e){this.response=null;}}"
    "else{this.response=this.responseText;}"
    "this.readyState=4;fire(this,'readystatechange');fire(this,'load');fire(this,'loadend');};"
    "Object.defineProperty(globalThis,'XMLHttpRequest',{configurable:true,writable:true,value:XHR});"
    "globalThis.fetch=function(u,opt){opt=opt||{};var r;"
    "try{r=HF(String(opt.method||'GET'),String(u),(opt.body==null?'':String(opt.body)));}catch(e){r=null;}"
    "var st=r?(r.status|0):0;var bt=r?(r.body||''):'';var ct=r?(r.contentType||''):'';"
    "var ok=st>=200&&st<300;"
    "var resp={ok:ok,status:st,statusText:'',url:String(u),redirected:false,type:'basic',bodyUsed:false,"
    "headers:{get:function(k){return(String(k).toLowerCase()==='content-type'&&ct)?ct:null;},"
    "has:function(k){return String(k).toLowerCase()==='content-type'&&!!ct;},forEach:function(){}},"
    "text:function(){return Promise.resolve(bt);},"
    "json:function(){try{return Promise.resolve(JSON.parse(bt));}catch(e){return Promise.reject(e);}},"
    "arrayBuffer:function(){return Promise.resolve(bt);},clone:function(){return resp;}};"
    "return st===0?Promise.reject(new TypeError('Failed to fetch')):Promise.resolve(resp);};"
    "try{delete globalThis.__hostFetch;}catch(e){}"
    "})();";

jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx) {
    if (ctx == NULL || fn == NULL) return JD_ERR_NULL_ARG;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;

    JSValue data[4];
    jd_pack_ptr(jsctx, &data[0], (const void *)fn);
    jd_pack_ptr(jsctx, &data[2], (const void *)fetch_ctx);
    JSValue hf = JS_NewCFunctionData(jsctx, m_host_fetch, 3, 0, 4, data);
    for (int i = 0; i < 4; ++i) JS_FreeValue(jsctx, data[i]);
    if (JS_IsException(hf)) return JD_ERR_OOM;

    JSValue global = JS_GetGlobalObject(jsctx);
    if (JS_IsException(global)) { JS_FreeValue(jsctx, hf); return JD_ERR_OOM; }
    JS_SetPropertyStr(jsctx, global, "__hostFetch", hf); /* consumes hf */
    JS_FreeValue(jsctx, global);

    JSValue r = JS_Eval(jsctx, JD_XHR_SHIM, sizeof JD_XHR_SHIM - 1,
                        "<xhr-shim>", JS_EVAL_TYPE_GLOBAL);
    int ok = !JS_IsException(r);
    JS_FreeValue(jsctx, r);
    return ok ? JD_OK : JD_ERR_INTERNAL;
}

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

int jd_fire_click(js_context *ctx, dom_node_id node_id) {
    if (ctx == NULL || node_id == DOM_NODE_NONE) return 1;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return 1;

    /* Build and run: var e={target:__wrap(n),preventDefault:function(){this.defaultPrevented=true},defaultPrevented:false}; var f=__clickRegistry[n]; if(typeof f==='function'){ f.call(e.target,e); } e.defaultPrevented?0:1; */
    char src[512];
    int n = snprintf(src, sizeof src,
        "(function(){var n=%u;var f=globalThis.__clickRegistry[n];"
        "if(typeof f!=='function')return 1;"
        "var e={target:globalThis.__wrap(n),preventDefault:function(){this.defaultPrevented=true},defaultPrevented:false};"
        "f.call(e.target,e);return e.defaultPrevented?0:1;})();",
        (unsigned)node_id);
    if (n < 0 || (size_t)n >= sizeof src) return 1;

    JSValue r = JS_Eval(jsctx, src, (size_t)n, "<click-fire>", JS_EVAL_TYPE_GLOBAL);
    int default_action = 1;
    if (!JS_IsException(r)) {
        int32_t v = 1;
        JS_ToInt32(jsctx, &v, r);
        default_action = v != 0 ? 1 : 0;
    }
    JS_FreeValue(jsctx, r);
    return default_action;
}
