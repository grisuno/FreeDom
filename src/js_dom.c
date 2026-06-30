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
    { "removeAttribute", m_remove_attribute, 2 },
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
