/*
 * js_fetch.c -- XMLHttpRequest / fetch over the parent-gated host call (allow∩js only).
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
        /* R7e: raw binary body as Uint8Array for arrayBuffer responseType. */
        JSValue buf = JS_NewArrayBufferCopy(ctx, (const uint8_t *)(rbody ? rbody : ""), rlen);
        if (!JS_IsException(buf)) {
            JS_SetPropertyStr(ctx, o, "bodyRaw", buf);
        } else {
            JS_SetPropertyStr(ctx, o, "bodyRaw", JS_NULL);
            JS_FreeValue(ctx, buf);
        }
        JS_SetPropertyStr(ctx, o, "contentType", JS_NewString(ctx, rctype ? rctype : ""));
    } else { /* fail-closed */
        JS_SetPropertyStr(ctx, o, "status", JS_NewInt32(ctx, 0));
        JS_SetPropertyStr(ctx, o, "body", JS_NewString(ctx, ""));
        JS_SetPropertyStr(ctx, o, "bodyRaw", JS_NULL);
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
    "var HF=__G.__hostFetch; if(typeof HF!=='function')return;"
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
    "if(this.responseType==='arraybuffer'){"
    "  if(r.bodyRaw&&r.bodyRaw.buffer&&r.bodyRaw.buffer!==r.bodyRaw){"
    "    try{this.response=r.bodyRaw.buffer;}catch(e){this.response=r.bodyRaw;}"
    "  }else{this.response=r.bodyRaw;}"
    "}else if(this.responseType==='json'){try{this.response=JSON.parse(this.responseText);}catch(e){this.response=null;}}"
    "else{this.response=this.responseText;}"
    "this.readyState=4;fire(this,'readystatechange');fire(this,'load');fire(this,'loadend');};"
    "Object.defineProperty(__G,'XMLHttpRequest',{configurable:true,writable:true,value:XHR});"
    /* Fetch Standard classes over the same gated host call. Request/Response are
     * data containers; only fetch() reaches HF (and so the parent's full policy). */
    "function bodyText(b){ if(b==null) return '';"
    "  if(typeof b==='string') return b;"
    "  if(typeof URLSearchParams!=='undefined'&&b instanceof URLSearchParams) return b.toString();"
    "  if(typeof Blob!=='undefined'&&b instanceof Blob) return new TextDecoder().decode(b._b);"
    "  if(b instanceof ArrayBuffer) return new TextDecoder().decode(new Uint8Array(b));"
    "  if(ArrayBuffer.isView(b)) return new TextDecoder().decode(new Uint8Array(b.buffer,b.byteOffset,b.byteLength));"
    "  if(typeof FormData!=='undefined'&&b instanceof FormData){ var q=new URLSearchParams();"
    "    b.forEach(function(v,k){ q.append(k,String(v)); }); return q.toString(); }"
    "  return String(b); }"
    "function abortErr(){ var e=new Error('The operation was aborted.'); e.name='AbortError'; return e; }"
    "function Request(input,init){ init=init||{}; var src=(input instanceof Request)?input:null;"
    "  this.url=src?src.url:String(input&&input.href!==undefined?input.href:input);"
    "  this.method=String(init.method||(src?src.method:'GET')).toUpperCase();"
    "  this.headers=new Headers(init.headers||(src?src.headers:undefined));"
    "  this._body=init.body!==undefined?init.body:(src?src._body:null);"
    "  this.signal=init.signal||(src?src.signal:null)||null; this.credentials=init.credentials||'same-origin';"
    "  this.mode=init.mode||'cors'; this.cache=init.cache||'default'; this.redirect=init.redirect||'follow';"
    "  this.referrer=''; this.referrerPolicy='no-referrer'; this.integrity=init.integrity||''; this.keepalive=!!init.keepalive;"
    "  this.bodyUsed=false; }"
    "Request.prototype.clone=function(){ return new Request(this); };"
    "Request.prototype.text=function(){ return Promise.resolve(bodyText(this._body)); };"
    "Request.prototype.json=function(){ return this.text().then(JSON.parse); };"
    "function Response(body,init){ init=init||{}; this.status=init.status===undefined?200:(init.status|0);"
    "  this.statusText=String(init.statusText||''); this.ok=this.status>=200&&this.status<300;"
    "  this.headers=(init.headers instanceof Headers)?init.headers:new Headers(init.headers);"
    "  this.url=init.url||''; this.redirected=false; this.type=init.type||'default'; this.bodyUsed=false;"
    "  this._raw=init.raw||null; this._body=body===undefined?null:body; }"
    "Response.prototype.text=function(){ this.bodyUsed=true; return Promise.resolve(bodyText(this._body)); };"
    "Response.prototype.json=function(){ return this.text().then(JSON.parse); };"
    "Response.prototype.arrayBuffer=function(){ this.bodyUsed=true;"
    "  if(this._raw) return Promise.resolve(this._raw);"
    "  if(typeof Blob!=='undefined'&&this._body instanceof Blob) return this._body.arrayBuffer();"
    "  return Promise.resolve(new TextEncoder().encode(bodyText(this._body)).buffer); };"
    "Response.prototype.bytes=function(){ return this.arrayBuffer().then(function(b){ return new Uint8Array(b); }); };"
    "Response.prototype.blob=function(){ var t=this.headers.get('content-type')||'';"
    "  return this.arrayBuffer().then(function(b){ return new Blob([b],{type:t}); }); };"
    "Response.prototype.clone=function(){ return new Response(this._body,{status:this.status,statusText:this.statusText,"
    "  headers:this.headers,url:this.url,type:this.type,raw:this._raw}); };"
    "Response.error=function(){ return new Response(null,{status:0,type:'error'}); };"
    "Response.json=function(d,init){ init=init||{}; var h=new Headers(init.headers); h.set('content-type','application/json');"
    "  return new Response(JSON.stringify(d),{status:init.status,statusText:init.statusText,headers:h}); };"
    "Response.redirect=function(u,st){ var h=new Headers(); h.set('location',String(u));"
    "  return new Response(null,{status:st||302,headers:h}); };"
    "__G.Request=Request; __G.Response=Response;"
    "__G.fetch=function(input,opt){ var rq; try{ rq=new Request(input,opt); }catch(e){ return Promise.reject(e); }"
    "  if(rq.signal&&rq.signal.aborted) return Promise.reject(abortErr());"
    "  var r; try{ r=HF(rq.method,rq.url,bodyText(rq._body)); }catch(e){ r=null; }"
    "  var st=r?(r.status|0):0; if(st===0) return Promise.reject(new TypeError('Failed to fetch'));"
    "  if(rq.signal&&rq.signal.aborted) return Promise.reject(abortErr());"
    "  var h=new Headers(); if(r.contentType) h.set('content-type',r.contentType);"
    "  return Promise.resolve(new Response(r.body||'',{status:st,headers:h,url:rq.url,type:'basic',raw:r.bodyRaw||null})); };"
    /* navigator.sendBeacon: a queued POST over the same gated call, sent after the
     * current task (the page never waits on it); the parent applies the full policy
     * (hostblock included), so a tracker beacon is refused there, not here. */
    "if(typeof __G.navigator==='object'&&__G.navigator!==null){"
    "  var beacons=[];"
    "  var sendB=function(u,data){ var url=String(u==null?'':u); if(!/^https:[/][/]/i.test(url)&&!/^[/.]/.test(url)) return false;"
    "    if(beacons.length>=64) return false;"
    "    beacons.push([url,bodyText(data)]);"
    "    if(beacons.length===1) __G.setTimeout(function(){ var q=beacons.splice(0);"
    "      q.forEach(function(b){ try{ HF('POST',b[0],b[1]); }catch(e){} }); },0);"
    "    return true; };"
    /* the real navigator is non-extensible (anti-fp): the method goes on its own
     * extensible prototype, never on Object.prototype */
    "  var nav=__G.navigator, tgt=Object.isExtensible(nav)?nav:Object.getPrototypeOf(nav);"
    "  if(tgt&&tgt!==Object.prototype&&Object.isExtensible(tgt))"
    "    Object.defineProperty(tgt,'sendBeacon',{configurable:true,writable:true,value:sendB}); }"
    "try{delete __G.__hostFetch;}catch(e){}"
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
