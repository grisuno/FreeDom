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
#include "js_sandbox.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "quickjs.h"

static dom_index *jd_idx(JSContext *ctx) {
    return (dom_index *)JS_GetContextOpaque(ctx);
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

/* --- install --- */

typedef struct jd_method {
    const char *name;
    JSCFunction *fn;
    int          nargs;
} jd_method;

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
    { "setInnerHtml",   m_set_inner_html,    2 },
};

/* A small standard `document` facade over the native handle API, so real page
 * scripts ("document.title = ...", "document.getElementById('x').textContent = ...")
 * work without exposing live engine node objects. Element wrappers carry only the
 * validated integer handle and proxy to the sealed `dom` methods. A no-op console
 * and window=globalThis keep common scripts from dying on a ReferenceError. */
static const char JD_DOCUMENT_SHIM[] =
    "(function(){"
    "  function wrap(h){"
    "    if (h===null||h===undefined) return null;"
    "    return {"
    "      _h:h, nodeType:1,"
    "      get textContent(){ return dom.textContent(h); },"
    "      set textContent(v){ dom.setText(h, String(v)); },"
    "      getAttribute: function(n){ return dom.getAttribute(h, String(n)); },"
    "      setAttribute: function(n,v){ dom.setAttribute(h, String(n), String(v)); },"
    "      get tagName(){ var t=dom.tagName(h); return t===null?null:String(t).toUpperCase(); },"
    "      get id(){ var v=dom.getAttribute(h,'id'); return v===null?'':v; },"
    "      set id(v){ dom.setAttribute(h,'id',String(v)); },"
    "      get className(){ var v=dom.getAttribute(h,'class'); return v===null?'':v; },"
    "      set className(v){ dom.setAttribute(h,'class',String(v)); },"
    "      set innerHTML(v){ dom.setInnerHtml(h, String(v)); },"
    "      get innerHTML(){ return ''; },"
    "      appendChild: function(c){ if(c&&c._h!==undefined) dom.appendChild(h,c._h); return c; },"
    "      removeChild: function(c){ if(c&&c._h!==undefined) dom.removeChild(h,c._h); return c; },"
    "      addEventListener: function(){}, removeEventListener: function(){},"
    "      style:{}"
    "    };"
    "  }"
    "  function wrapList(hs){ var r=[]; for (var i=0;i<hs.length;i++) r.push(wrap(hs[i])); return r; }"
    "  var loadCbs=[], timers=[];"
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
    /* Identity-safe ambient surface: no real cookie/referrer leaks, storage is
     * EPHEMERAL in-memory (Zero Knowledge -- never persisted, gone each load). */
    "  Object.defineProperty(d,'cookie',{get:function(){return '';},set:function(){},enumerable:true});"
    "  Object.defineProperty(d,'referrer',{get:function(){return '';},enumerable:true});"
    "  d.querySelector=function(){return null;}; d.querySelectorAll=function(){return [];};"
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
    "  globalThis.setTimeout=function(fn){ if(typeof fn==='function') timers.push(fn); return timers.length; };"
    "  globalThis.setInterval=function(fn){ if(typeof fn==='function') timers.push(fn); return timers.length; };"
    "  globalThis.clearTimeout=function(){}; globalThis.clearInterval=function(){};"
    /* Synthetic, bounded "page loaded" pump: fire load handlers, then flush queued
     * timers ONCE (capped, since this is not a real async event loop). */
    "  globalThis.__fireDeferred=function(){"
    "    d.readyState='complete';"
    "    for (var i=0;i<loadCbs.length;i++){ try{ loadCbs[i].call(globalThis); }catch(e){} }"
    "    if (typeof globalThis.onload==='function'){ try{ globalThis.onload(); }catch(e){} }"
    "    if (typeof d.onload==='function'){ try{ d.onload(); }catch(e){} }"
    "    var n=0; while (timers.length>0 && n<64){ var t=timers.shift(); n++;"
    "      try{ t.call(globalThis); }catch(e){} }"
    "  };"
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

jd_status jd_install(js_context *ctx, dom_index *idx) {
    if (ctx == NULL || idx == NULL) return JD_ERR_NULL_ARG;

    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;

    /* The index is reachable only from native code, never from script. */
    JS_SetContextOpaque(jsctx, (void *)idx);

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
    return shim_ok ? JD_OK : JD_ERR_INTERNAL;
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
