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

/* The object the shim sees for one reply (shared by the synchronous host call and the deferred
 * delivery). Fail-closed: rc != 0 is { status:0, body:'' } and never says why. */
static JSValue jd_reply_object(JSContext *ctx, int rc, int status, const char *rbody,
                               size_t rlen, const char *rctype, const char *rhdrs) {
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
        JS_SetPropertyStr(ctx, o, "headers", JS_NewString(ctx, rhdrs ? rhdrs : ""));
    } else { /* fail-closed */
        JS_SetPropertyStr(ctx, o, "status", JS_NewInt32(ctx, 0));
        JS_SetPropertyStr(ctx, o, "body", JS_NewString(ctx, ""));
        JS_SetPropertyStr(ctx, o, "bodyRaw", JS_NULL);
        JS_SetPropertyStr(ctx, o, "contentType", JS_NewString(ctx, ""));
    }
    return o;
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

    const char *rh = (argc > 3 && JS_IsString(argv[3])) ? JS_ToCString(ctx, argv[3]) : NULL;

    int status = 0; char *rbody = NULL; size_t rlen = 0; char *rctype = NULL, *rhdrs = NULL;
    int rc = -1;
    if (fn != NULL && url != NULL)
        rc = fn(fctx, method ? method : "GET", url, body ? body : "", blen, rh,
                &status, &rbody, &rlen, &rctype, &rhdrs);

    JSValue o = jd_reply_object(ctx, rc, status, rbody, rlen, rctype, rhdrs);
    free(rbody); free(rctype); free(rhdrs);
    if (method != NULL) JS_FreeCString(ctx, method);
    if (url != NULL)    JS_FreeCString(ctx, url);
    if (body != NULL)   JS_FreeCString(ctx, body);
    if (rh != NULL)     JS_FreeCString(ctx, rh);
    return o;
}

/* __hostFetchAsync(method, url, body, headers) -> bool: queues the request with the host and
 * returns at once; the reply comes back later through jd_net_deliver. false = not queued. */
static JSValue m_host_fetch_async(JSContext *ctx, JSValueConst this_val,
                                  int argc, JSValueConst *argv, int magic, JSValue *fd) {
    (void)this_val; (void)magic;
    jd_fetch_async_fn fn = (jd_fetch_async_fn)jd_unpack_ptr(ctx, fd[0], fd[1]);
    void *fctx           = jd_unpack_ptr(ctx, fd[2], fd[3]);
    const char *method = (argc > 0) ? JS_ToCString(ctx, argv[0]) : NULL;
    const char *url    = (argc > 1) ? JS_ToCString(ctx, argv[1]) : NULL;
    size_t blen = 0;
    const char *body   = (argc > 2 && !JS_IsUndefined(argv[2]) && !JS_IsNull(argv[2]))
                         ? JS_ToCStringLen(ctx, &blen, argv[2]) : NULL;
    const char *rh = (argc > 3 && JS_IsString(argv[3])) ? JS_ToCString(ctx, argv[3]) : NULL;
    int rc = -1;
    if (fn != NULL && url != NULL)
        rc = fn(fctx, method ? method : "GET", url, body ? body : "", blen, rh);
    if (method != NULL) JS_FreeCString(ctx, method);
    if (url != NULL)    JS_FreeCString(ctx, url);
    if (body != NULL)   JS_FreeCString(ctx, body);
    if (rh != NULL)     JS_FreeCString(ctx, rh);
    return JS_NewBool(ctx, rc == 0);
}

/* XMLHttpRequest + fetch over the single synchronous __hostFetch primitive. The
 * round-trip is synchronous under the hood (the worker blocks on the parent), so XHR
 * callbacks fire right after send(); fetch returns a resolved promise (its .then/await
 * run when the worker pumps the job queue). __hostFetch is captured into a closure and
 * then deleted from the global, so page script cannot call it directly. */
static const char JD_XHR_SHIM[] =
    "(function(){"
    "var HF0=__G.__hostFetch; if(typeof HF0!=='function')return;"
    /* Request log for the Freebug Network panel: bounded, closure-held; the REPL shim takes
     * the reader once and deletes the global (a page that asks first only sees its own
     * requests -- no timing, Date is normalized). */
    "var NLOG=[]; function HF(m,u,b,h){ var r; try{ r=HF0(m,u,b,h||''); }catch(e){ r=null; }"
    "  if(NLOG.length<512) NLOG.push({method:String(m),url:String(u),status:r?(r.status|0):0,"
    "    size:r&&r.body?r.body.length:0,type:r&&r.contentType?String(r.contentType):'',ms:-1,"
    "    reqHeaders:String(h||''),respHeaders:r&&r.headers?String(r.headers):''});"
    "  if(r===null) throw new Error('fetch'); return r; }"
    "Object.defineProperty(__G,'__netLog',{value:function(){return NLOG;},configurable:true,writable:true,enumerable:false});"
    /* Deferred requests: HFA queues one with the host and `cb(reply|null)` fires when the host
     * hands the batch back (jd_net_deliver, issue order). Without a host hook it is absent and
     * XHR/fetch keep the synchronous round trip. */
    "var HFA0=__G.__hostFetchAsync, NQ=[]; try{ delete __G.__hostFetchAsync; }catch(e){}"
    "var HAS_ASYNC=(typeof HFA0==='function');"
    "function HFA(m,u,b,h,cb){ var q=false; try{ q=HFA0(m,u,b,h||''); }catch(e){}"
    "  if(q){ NQ.push({cb:cb,m:m,u:u,h:String(h||'')}); return; }"
    "  __G.setTimeout(function(){ cb(null); },0); }"
    "if(HAS_ASYNC) Object.defineProperty(__G,'__netDeliver',{configurable:true,writable:true,enumerable:false,value:function(r){"
    "  var e=NQ.shift(); if(!e) return;"
    "  if(NLOG.length<512) NLOG.push({method:String(e.m),url:String(e.u),status:r?(r.status|0):0,"
    "    size:r&&r.body?r.body.length:0,type:r&&r.contentType?String(r.contentType):'',ms:r?(r.ms|0):0,"
    "    reqHeaders:e.h,respHeaders:r&&r.headers?String(r.headers):''});"
    "  try{ e.cb(r); }catch(x){} }});"
    "function hdrPairs(t){ var m=[]; String(t||'').split('\\n').forEach(function(l){ var p=l.indexOf(':');\n"
    "  if(p>0) m.push([l.slice(0,p).trim(), l.slice(p+1).trim()]); }); return m; }\n"
    "var STATUS_TEXT={200:'OK',201:'Created',202:'Accepted',204:'No Content',206:'Partial Content',301:'Moved Permanently',\n"
    "  302:'Found',303:'See Other',304:'Not Modified',307:'Temporary Redirect',308:'Permanent Redirect',400:'Bad Request',\n"
    "  401:'Unauthorized',403:'Forbidden',404:'Not Found',405:'Method Not Allowed',406:'Not Acceptable',409:'Conflict',\n"
    "  410:'Gone',413:'Payload Too Large',415:'Unsupported Media Type',418:\"I'm a teapot\",422:'Unprocessable Entity',\n"
    "  429:'Too Many Requests',500:'Internal Server Error',501:'Not Implemented',502:'Bad Gateway',503:'Service Unavailable',\n"
    "  504:'Gateway Timeout'};\n"
    "function XETarget(){ this._L={}; }\n"
    "XETarget.prototype.addEventListener=function(t,f){ if(typeof f!=='function'&&!(f&&typeof f.handleEvent==='function')) return;\n"
    "  var a=(this._L[t]=this._L[t]||[]); if(a.indexOf(f)<0) a.push(f); };\n"
    "XETarget.prototype.removeEventListener=function(t,f){ var a=this._L[t]; if(!a) return; var i=a.indexOf(f); if(i>=0) a.splice(i,1); };\n"
    "XETarget.prototype.dispatchEvent=function(e){ var t=e.type, h=this['on'+t];\n"
    "  try{ e.target=this; e.currentTarget=this; }catch(x){}\n"
    "  if(typeof h==='function'){ try{ h.call(this,e); }catch(x){} }\n"
    "  var a=(this._L[t]||[]).slice();\n"
    "  for(var i=0;i<a.length;i++){ try{ typeof a[i]==='function'?a[i].call(this,e):a[i].handleEvent(e); }catch(x){} }\n"
    "  return true; };\n"
    "function pev(type,loaded,total){ var e; try{ e=new ProgressEvent(type,{lengthComputable:total>0,loaded:loaded,total:total}); }\n"
    "  catch(x){ try{ e=new Event(type); }catch(y){ e={type:type}; } e.lengthComputable=total>0; e.loaded=loaded; e.total=total; } return e; }\n"
    "function XUpload(){ XETarget.call(this); }\n"
    "XUpload.prototype=Object.create(XETarget.prototype); XUpload.prototype.constructor=XUpload;\n"
    "function XHR(){ XETarget.call(this); this.readyState=0;this.status=0;this.statusText='';this.responseText='';\n"
    "  this.response='';this.responseType='';this.responseURL='';this.responseXML=null;this.withCredentials=false;this.timeout=0;\n"
    "  this.upload=new XUpload();\n"
    "  this.onreadystatechange=null;this.onload=null;this.onerror=null;this.onloadend=null;this.onloadstart=null;\n"
    "  this.onprogress=null;this.onabort=null;this.ontimeout=null;\n"
    "  this._m='GET';this._u='';this._h='';this._rh={};this._async=true;this._sent=false;this._done=false;this._gen=0; }\n"
    "XHR.prototype=Object.create(XETarget.prototype); XHR.prototype.constructor=XHR;\n"
    "XHR.UNSENT=0;XHR.OPENED=1;XHR.HEADERS_RECEIVED=2;XHR.LOADING=3;XHR.DONE=4;\n"
    "XHR.prototype.UNSENT=0;XHR.prototype.OPENED=1;XHR.prototype.HEADERS_RECEIVED=2;XHR.prototype.LOADING=3;XHR.prototype.DONE=4;\n"
    "function xstate(x,n){ x.readyState=n; x.dispatchEvent(pev('readystatechange',0,0)); }\n"
    "XHR.prototype.open=function(m,u,a){ this._m=String(m||'GET').toUpperCase(); this._u=String(u==null?'':u);\n"
    "  this._async=(a===undefined)?true:!!a; this._rh={}; this._sent=false; this._done=false; this._gen++;\n"
    "  this.status=0; this.statusText=''; this.responseText=''; this.response=''; this._h='';\n"
    "  this.responseURL=this._u; xstate(this,1); };\n"
    "/* Request headers the page sets: repeated names combine with \", \" (XHR spec); the trusted parent\n"
    " * filters the block (identity/framing headers are never forwarded). */\n"
    "XHR.prototype.setRequestHeader=function(k,v){ if(this.readyState!==1||this._sent){ var e=new Error(\"Failed to execute 'setRequestHeader' on 'XMLHttpRequest': The object's state must be OPENED.\");\n"
    "    e.name='InvalidStateError'; throw e; }\n"
    "  k=String(k); v=String(v); var l=k.toLowerCase(); var o=this._rh;\n"
    "  if(Object.prototype.hasOwnProperty.call(o,l)) o[l][1]+=', '+v; else o[l]=[k,v]; };\n"
    "XHR.prototype.getAllResponseHeaders=function(){ if(this.readyState<2) return ''; var out='';\n"
    "  hdrPairs(this._h).forEach(function(p){ out+=p[0].toLowerCase()+': '+p[1]+'\\r\\n'; }); return out; };\n"
    "XHR.prototype.getResponseHeader=function(k){ if(this.readyState<2) return null; k=String(k).toLowerCase(); var v=null;\n"
    "  hdrPairs(this._h).forEach(function(p){ if(p[0].toLowerCase()===k) v=(v===null?'':v+', ')+p[1]; }); return v; };\n"
    "XHR.prototype.overrideMimeType=function(){};\n"
    "XHR.prototype.abort=function(){ if(this._sent&&this._ev){ this._gen++; this._ev=false; this.status=0;\n"
    "    this.responseText=''; this.response=''; this.readyState=4; this.dispatchEvent(pev('readystatechange',0,0));\n"
    "    this.dispatchEvent(pev('abort',0,0)); this.upload.dispatchEvent(pev('abort',0,0));\n"
    "    this.dispatchEvent(pev('loadend',0,0)); }\n"
    "  this._sent=false; this.readyState=0; };\n"
    "/* A SYNC request (or a host without the deferred hook) settles inside send(); only its EVENTS are\n"
    " * deferred. A deferred one stays OPENED until the host hands the batch back, then settles and fires\n"
    " * its events at once. */\n"
    "XHR.prototype.send=function(b){ if(this.readyState!==1||this._sent){ var ie=new Error(\"Failed to execute 'send' on 'XMLHttpRequest': The object's state must be OPENED.\");\n"
    "    ie.name='InvalidStateError'; throw ie; }\n"
    "  var self=this, gen=++this._gen, hs='', o=this._rh; this._sent=true; this._done=false;\n"
    "  for(var k in o) hs+=o[k][0]+': '+o[k][1]+'\\n';\n"
    "  var body=(b==null||this._m==='GET'||this._m==='HEAD')?'':bodyText(b);\n"
    "  var finish=function(r,inline){\n"
    "  var ok=!!r&&(r.status|0)!==0, n=0;\n"
    "  if(ok){ self.status=r.status|0; self.statusText=STATUS_TEXT[self.status]||'';\n"
    "    var hdrs=r.headers||''; if(r.contentType&&!/^content-type:/im.test(hdrs)) hdrs='content-type: '+r.contentType+'\\n'+hdrs;\n"
    "    self._h=hdrs; self.responseText=r.body||''; n=self.responseText.length;\n"
    "    var rt=self.responseType;\n"
    "    if(rt==='arraybuffer'){\n"
    "      if(r.bodyRaw&&r.bodyRaw.buffer&&r.bodyRaw.buffer!==r.bodyRaw){ try{self.response=r.bodyRaw.buffer;}catch(e){self.response=r.bodyRaw;} }\n"
    "      else{ self.response=r.bodyRaw; }\n"
    "    }else if(rt==='json'){ try{ self.response=JSON.parse(self.responseText); }catch(e){ self.response=null; } }\n"
    "    else if(rt==='blob'){ try{ self.response=new Blob([r.bodyRaw||self.responseText],{type:r.contentType||''}); }catch(e){ self.response=null; } }\n"
    "    else if(rt==='document'){ try{ self.response=new DOMParser().parseFromString(self.responseText,'text/html'); self.responseXML=self.response; }catch(e){ self.response=null; } }\n"
    "    else{ self.response=self.responseText; } }\n"
    "  else{ self.status=0; self.statusText=''; }\n"
    "  self.readyState=4; self._done=true; self._ev=true;\n"
    "  var fire=function(){ if(gen!==self._gen) return; self._ev=false;\n"
    "    self.dispatchEvent(pev('loadstart',0,0));\n"
    "    if(body!==''){ self.upload.dispatchEvent(pev('loadstart',0,body.length)); self.upload.dispatchEvent(pev('progress',body.length,body.length));\n"
    "      self.upload.dispatchEvent(pev('load',body.length,body.length)); self.upload.dispatchEvent(pev('loadend',body.length,body.length)); }\n"
    "    if(!ok){ self.readyState=4; self.dispatchEvent(pev('readystatechange',0,0));\n"
    "      self.dispatchEvent(pev('error',0,0)); self.dispatchEvent(pev('loadend',0,0)); return; }\n"
    "    self.readyState=2; self.dispatchEvent(pev('readystatechange',0,0));\n"
    "    self.readyState=3; self.dispatchEvent(pev('readystatechange',0,0)); self.dispatchEvent(pev('progress',n,n));\n"
    "    self.readyState=4; self.dispatchEvent(pev('readystatechange',0,0));\n"
    "    self.dispatchEvent(pev('load',n,n)); self.dispatchEvent(pev('loadend',n,n)); };\n"
    "  if(!inline&&self._async&&typeof __G.setTimeout==='function') __G.setTimeout(fire,0); else fire(); };\n"
    "  if(this._async&&HAS_ASYNC){ this._ev=true;\n"
    "    HFA(this._m,this._u,body,hs,function(r){ if(gen!==self._gen) return; finish(r,true); }); return; }\n"
    "  var r; try{ r=HF(this._m,this._u,body,hs); }catch(e){ r=null; }\n"
    "  finish(r,false); };\n"
    "Object.defineProperty(__G,'XMLHttpRequest',{configurable:true,writable:true,value:XHR});\n"
    "Object.defineProperty(__G,'XMLHttpRequestEventTarget',{configurable:true,writable:true,value:XETarget});\n"
    "Object.defineProperty(__G,'XMLHttpRequestUpload',{configurable:true,writable:true,value:XUpload});\n"
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
    "if(typeof __G.__streamBody==='function') __G.__streamBody(Response);"
    "function mkResponse(r,rq){ var st=r.status|0; var h=new Headers(); if(r.contentType) h.set('content-type',r.contentType);"
    "  String(r.headers||'').split('\\n').forEach(function(l){ var p=l.indexOf(':'); if(p>0){ var k=l.slice(0,p).trim(), v=l.slice(p+1).trim();"
    "    if(k.toLowerCase()==='content-type') return; try{ h.append(k,v); }catch(e){} } });"
    "  return new Response(r.body||'',{status:st,headers:h,url:rq.url,type:'basic',raw:r.bodyRaw||null}); }"
    "__G.fetch=function(input,opt){ var rq; try{ rq=new Request(input,opt); }catch(e){ return Promise.reject(e); }"
    "  if(rq.signal&&rq.signal.aborted) return Promise.reject(abortErr());"
    "  var hs=''; try{ rq.headers.forEach(function(v,k){ hs+=k+': '+v+'\\n'; }); }catch(e){}"
    "  if(HAS_ASYNC) return new Promise(function(res,rej){"
    "    HFA(rq.method,rq.url,bodyText(rq._body),hs,function(r){ if(!r||(r.status|0)===0) return rej(new TypeError('Failed to fetch'));"
    "      if(rq.signal&&rq.signal.aborted) return rej(abortErr()); res(mkResponse(r,rq)); }); });"
    "  var r; try{ r=HF(rq.method,rq.url,bodyText(rq._body),hs); }catch(e){ r=null; }"
    "  if(!r||(r.status|0)===0) return Promise.reject(new TypeError('Failed to fetch'));"
    "  if(rq.signal&&rq.signal.aborted) return Promise.reject(abortErr());"
    "  return Promise.resolve(mkResponse(r,rq)); };"
    /* navigator.sendBeacon: a queued POST over the same gated call, sent after the
     * current task (the page never waits on it); the parent applies the full policy
     * (hostblock included), so a tracker beacon is refused there, not here. */
    "if(typeof __G.navigator==='object'&&__G.navigator!==null){"
    "  var beacons=[];"
    "  var sendB=function(u,data){ var url=String(u==null?'':u); if(!/^https:[/][/]/i.test(url)&&!/^[/.]/.test(url)) return false;"
    "    if(beacons.length>=64) return false;"
    "    beacons.push([url,bodyText(data)]);"
    "    if(beacons.length===1) __G.setTimeout(function(){ var q=beacons.splice(0);"
    "      q.forEach(function(b){ try{ if(HAS_ASYNC) HFA('POST',b[0],b[1],'',function(){}); else HF('POST',b[0],b[1]); }catch(e){} }); },0);"
    "    return true; };"
    /* the real navigator is non-extensible (anti-fp): the method goes on its own
     * extensible prototype, never on Object.prototype */
    "  var nav=__G.navigator, tgt=Object.isExtensible(nav)?nav:Object.getPrototypeOf(nav);"
    /* An ACCESSOR with a setter, not a data property: analytics code patches the method with
     * `navigator.sendBeacon = fn`, and a write to an inherited data property would create an
     * own property on the non-extensible navigator (a strict-mode TypeError). The setter keeps
     * the override in a closure -- the navigator stays non-extensible, no own key appears. */
    "  if(tgt&&tgt!==Object.prototype&&Object.isExtensible(tgt)){"
    "    var cur=sendB;"
    "    Object.defineProperty(tgt,'sendBeacon',{configurable:true,enumerable:true,"
    "      get:function(){return cur;},set:function(v){cur=v;}}); } }"
    "try{delete __G.__hostFetch;}catch(e){}"
    "})();";

jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx) {
    return jd_install_xhr_ex(ctx, fn, fetch_ctx, NULL, NULL);
}

jd_status jd_net_deliver(js_context *ctx, int rc, int status, const char *body, size_t len,
                         const char *ctype, const char *hdrs, int ms) {
    if (ctx == NULL) return JD_ERR_NULL_ARG;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;
    JSValue global = JS_GetGlobalObject(jsctx);
    JSValue f = JS_GetPropertyStr(jsctx, global, "__netDeliver");
    jd_status st = JD_ERR_INTERNAL;
    if (JS_IsFunction(jsctx, f)) {
        JSValue arg = jd_reply_object(jsctx, rc, status, body, len, ctype, hdrs);
        if (!JS_IsException(arg)) JS_SetPropertyStr(jsctx, arg, "ms", JS_NewInt32(jsctx, ms < 0 ? 0 : ms));
        JSValue r = JS_Call(jsctx, f, JS_UNDEFINED, 1, &arg);
        JS_FreeValue(jsctx, arg);
        if (!JS_IsException(r)) st = JD_OK; else JS_FreeValue(jsctx, JS_GetException(jsctx));
        JS_FreeValue(jsctx, r);
    }
    JS_FreeValue(jsctx, f);
    JS_FreeValue(jsctx, global);
    return st;
}

jd_status jd_install_xhr_ex(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx,
                            jd_fetch_async_fn afn, void *afetch_ctx) {
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
    if (afn != NULL) {
        JSValue ad[4];
        jd_pack_ptr(jsctx, &ad[0], (const void *)afn);
        jd_pack_ptr(jsctx, &ad[2], (const void *)afetch_ctx);
        JSValue hfa = JS_NewCFunctionData(jsctx, m_host_fetch_async, 4, 0, 4, ad);
        for (int i = 0; i < 4; ++i) JS_FreeValue(jsctx, ad[i]);
        if (!JS_IsException(hfa)) JS_SetPropertyStr(jsctx, global, "__hostFetchAsync", hfa);
        else JS_FreeValue(jsctx, hfa);
    }
    JS_FreeValue(jsctx, global);

    JSValue r = JS_Eval(jsctx, JD_XHR_SHIM, sizeof JD_XHR_SHIM - 1,
                        "<xhr-shim>", JS_EVAL_TYPE_GLOBAL);
    int ok = !JS_IsException(r);
    JS_FreeValue(jsctx, r);
    return ok ? JD_OK : JD_ERR_INTERNAL;
}
