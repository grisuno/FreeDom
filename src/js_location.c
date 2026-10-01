/*
 * js_location -- the page's real, read-only `location`, the JS-navigation capture
 * (location.href= / assign / replace / reload are only RECORDED; the trusted parent
 * gates them) and the session `history` (pushState/replaceState/popstate, same-origin
 * by url_history_target). Extracted from js_dom (anti-monolith). See spec/js_dom.md
 * 7e and include/js_location.h.
 */

#include "js_dom.h"
#include "js_location_internal.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quickjs.h"
#include "url.h"

/* --- real location + JS-navigation capture (Hito 20e parte 1) --- */

/* Defines a string property on the __locParts data object from a (ptr,len) span.
 * The span is copied into an engine string; a NULL span becomes "". */
static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,
                      const char *p, size_t len) {
    JSValue s = (p != NULL) ? JS_NewStringLen(ctx, p, len) : JS_NewString(ctx, "");
    JS_SetPropertyStr(ctx, obj, name, s); /* consumes s; name copied */
}

/* dom.histTarget(base, ref): the same-origin target of history.pushState/replaceState
 * (url_history_target) as a location-parts object {href, protocol, origin, host,
 * hostname, port, pathname, search, hash}, or null when ref is cross-origin, not
 * resolvable, or carries a control character (it will travel as one line to the
 * parent). A file:// target yields {href} only, like the location it replaces. */
JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    (void)this_val;
    if (argc < 2) return JS_NULL;
    const char *base = JS_ToCString(ctx, argv[0]);
    if (base == NULL) return JS_EXCEPTION;
    const char *ref = JS_ToCString(ctx, argv[1]);
    if (ref == NULL) { JS_FreeCString(ctx, base); return JS_EXCEPTION; }
    char out[URL_MAX_LEN];
    url_status st = url_history_target(base, ref, out, sizeof out);
    JS_FreeCString(ctx, base);
    JS_FreeCString(ctx, ref);
    if (st != URL_OK) return JS_NULL;
    for (const char *c = out; *c != '\0'; ++c)
        if ((unsigned char)*c < 0x20 || *c == 0x7f) return JS_NULL;
    JSValue lp = JS_NewObject(ctx);
    if (JS_IsException(lp)) return lp;
    size_t n = strlen(out);
    url_parts parts;
    jd_lp_set(ctx, lp, "href", out, n);
    if (url_split(out, &parts) == URL_OK) {
        jd_lp_set(ctx, lp, "protocol", parts.protocol, parts.protocol_len);
        jd_lp_set(ctx, lp, "origin",   parts.origin,   parts.origin_len);
        jd_lp_set(ctx, lp, "host",     parts.host,     parts.host_len);
        jd_lp_set(ctx, lp, "hostname", parts.hostname, parts.hostname_len);
        jd_lp_set(ctx, lp, "port",     parts.port,     parts.port_len);
        jd_lp_set(ctx, lp, "pathname", parts.pathname, parts.pathname_len);
        jd_lp_set(ctx, lp, "search",   parts.search,   parts.search_len);
        jd_lp_set(ctx, lp, "hash",     parts.hash,     parts.hash_len);
    }
    return lp;
}

/* Reads the page URL components from globalThis.__locParts (set natively, so a hostile
 * URL is never interpolated into JS) and installs a real, read-only `location`. The
 * navigating writes only RECORD the raw request into __navReq/__navReplace; they never
 * execute or resolve it. The trusted parent gates the raw string with ln_resolve. */
static const char JD_LOCATION_SHIM[] =
    "(function(){"
    "  var lp = __G.__locParts || {};"
    "  function nav(u, replace){ __G.__navReq = String(u);"
    "    __G.__navReplace = !!replace; }"
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
    "  try{ Object.defineProperty(__G,'location',{configurable:true,"
    "    get:function(){return loc;}, set:function(v){ nav(v,false); }}); }catch(e){}"
    /* history (spec/js_dom.md 7e): H is this document's entry list, hi the current
     * entry. push/replace resolve through dom.histTarget (same origin or
     * SecurityError), move location in place and record an op for the parent;
     * back/forward/go record a delta the parent applies to its own history. */
    "  var H=[{url:lp.href||'',state:null}], hi=0, HMAX=256, OPMAX=512;"
    "  __G.__histOps=[]; __G.__histGo=0;"
    "  function secErr(){ var e=new Error('The operation is insecure.');"
    "    e.name='SecurityError'; e.code=18; return e; }"
    "  function cloneState(st){ if(st===undefined||st===null) return null;"
    "    try{ return JSON.parse(JSON.stringify(st)); }"
    "    catch(e){ var x=new Error('The object could not be cloned.'); x.name='DataCloneError'; throw x; } }"
    "  function rec(k,u){ var o=__G.__histOps, n=o.length;"
    "    if(k==='R'&&n>0&&o[n-1][0]==='R'){ o[n-1][1]=u; return; }"
    "    if(n<OPMAX) o.push([k,u]); }"
    "  function hop(kind,st,url){"
    "    var p=dom.histTarget(lp.href||'',(url===undefined||url===null)?'':String(url));"
    "    if(!p) throw secErr();"
    "    var cs=cloneState(st);"
    "    if(kind==='P'&&hi+1<HMAX){ H.splice(hi+1); H.push({url:p.href,state:cs}); hi=H.length-1; }"
    "    else { kind='R'; H[hi]={url:p.href,state:cs}; }"
    "    lp=p; __G.__locParts=p; rec(kind,p.href); }"
    "  var hist={ get length(){ return H.length; }, get state(){ return H[hi].state; },"
    "    scrollRestoration:'auto',"
    "    pushState:function(s,t,u){ hop('P',s,u); }, replaceState:function(s,t,u){ hop('R',s,u); },"
    "    back:function(){ __G.__histGo-=1; }, forward:function(){ __G.__histGo+=1; },"
    "    go:function(n){ n=Number(n)|0; if(n===0){ nav(lp.href||'',true); return; }"
    "      __G.__histGo+=n; } };"
    "  try{ Object.defineProperty(__G,'history',{configurable:true,get:function(){return hist;}}); }catch(e){}"
    "  __G.__histPop=function(i){ i=Number(i)|0; if(i<0||i>=H.length) return 0;"
    "    var old=lp.href||''; hi=i; var p=dom.histTarget(old,H[i].url); if(p){ lp=p; __G.__locParts=p; }"
    "    var ev=__G.__mkEvent('popstate',{}); ev.state=H[i].state; ev.isTrusted=true;"
    "    __G.dispatchEvent(ev);"
    "    var nu=lp.href||''; if(old!==nu&&old.split('#')[0]===nu.split('#')[0]){"
    "      var he=__G.__mkEvent('hashchange',{}); he.oldURL=old; he.newURL=nu; he.isTrusted=true;"
    "      __G.dispatchEvent(he); }"
    "    return 1; };"
    "  try{ if(typeof document!=='undefined'){"
    "    Object.defineProperty(document,'location',{configurable:true,enumerable:true,"
    "      get:function(){return loc;}, set:function(v){ nav(v,false); }});"
    "    Object.defineProperty(document,'URL',{configurable:true,enumerable:true,"
    "      get:function(){return lp.href||'';}});"
    "    Object.defineProperty(document,'documentURI',{configurable:true,enumerable:true,"
    "      get:function(){return lp.href||'';}});"
    "  } }catch(e){}"
    "})();";

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

/* Serialises and clears globalThis.__histOps (["P"|"R", url] pairs) into
 * "K url\n" lines, and reads/clears __histGo. Runs as page-independent source: the
 * URLs are read as values, never interpolated. */
static const char JD_TAKE_HISTORY[] =
    "(function(){ var o=__G.__histOps||[], s='';"
    "  for(var i=0;i<o.length;i++) s+=o[i][0]+' '+o[i][1]+'\\n';"
    "  __G.__histOps=[]; var g=__G.__histGo|0; __G.__histGo=0;"
    "  return [s,g]; })()";

char *jd_take_history(js_context *ctx, int *go) {
    if (go != NULL) *go = 0;
    if (ctx == NULL) return NULL;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return NULL;
    JSValue r = JS_Eval(jsctx, JD_TAKE_HISTORY, sizeof JD_TAKE_HISTORY - 1,
                        "<take-history>", JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(r)) {
        JS_FreeValue(jsctx, JS_GetException(jsctx));
        return NULL;
    }
    char *out = NULL;
    JSValue sv = JS_GetPropertyUint32(jsctx, r, 0);
    JSValue gv = JS_GetPropertyUint32(jsctx, r, 1);
    size_t n = 0;
    const char *str = JS_ToCStringLen(jsctx, &n, sv);
    if (str != NULL) {
        if (n != 0 && n != (size_t)-1) {
            out = (char *)malloc(n + 1);
            if (out != NULL) { memcpy(out, str, n); out[n] = '\0'; }
        }
        JS_FreeCString(jsctx, str);
    }
    int32_t g = 0;
    if (go != NULL && JS_ToInt32(jsctx, &g, gv) == 0) *go = (int)g;
    JS_FreeValue(jsctx, sv);
    JS_FreeValue(jsctx, gv);
    JS_FreeValue(jsctx, r);
    return out;
}

int jd_pop_state(js_context *ctx, int index) {
    if (ctx == NULL) return 0;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return 0;
    char src[64];
    int n = snprintf(src, sizeof src,
                     "typeof __histPop==='function'?__histPop(%d):0", index);
    if (n < 0 || (size_t)n >= sizeof src) return 0;
    JSValue r = JS_Eval(jsctx, src, (size_t)n, "<popstate>", JS_EVAL_TYPE_GLOBAL);
    int32_t v = 0;
    if (JS_IsException(r)) JS_FreeValue(jsctx, JS_GetException(jsctx));
    else if (JS_ToInt32(jsctx, &v, r) != 0) v = 0;
    JS_FreeValue(jsctx, r);
    return v == 1 ? 1 : 0;
}
