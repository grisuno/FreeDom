/*
 * js_trusted — implementation of the trusted-host-only page surfaces.
 * See include/js_trusted.h.
 */

#include "js_trusted.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "quickjs.h"
#include "web_storage.h"

/* window.open for a trusted host (plan B4c): noopener semantics -- returns null, so
 * no cross-window reference (and no SOP channel) ever exists; the raw target is only
 * RECORDED (bounded, control characters dropped: it travels as one line) for the
 * parent, which gates it like a navigation and honours it on a user gesture only. */
static const char JT_OPEN_SHIM[] =
    "(function(){ var q=[]; __G.__openReq=q;"
    "  __G.open=function(u){"
    "    if(u!==undefined&&u!==null&&q.length<4){ var s=String(u);"
    "      if(!/[\\x00-\\x1f\\x7f]/.test(s)) q.push(s); }"
    "    return null; }; })()";

jd_status jt_enable_open(js_context *ctx) {
    if (ctx == NULL) return JD_ERR_NULL_ARG;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;
    JSValue r = JS_Eval(jsctx, JT_OPEN_SHIM, sizeof JT_OPEN_SHIM - 1, "<open-shim>",
                        JS_EVAL_TYPE_GLOBAL);
    int ok = !JS_IsException(r);
    if (!ok) JS_FreeValue(jsctx, JS_GetException(jsctx));
    JS_FreeValue(jsctx, r);
    return ok ? JD_OK : JD_ERR_INTERNAL;
}

static const char JT_TAKE_OPENS[] =
    "(function(){ var q=__G.__openReq; if(!q||!q.length) return '';"
    "  var s=q.join('\\n')+'\\n'; q.length=0; return s; })()";

char *jt_take_opens(js_context *ctx) {
    if (ctx == NULL) return NULL;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return NULL;
    JSValue r = JS_Eval(jsctx, JT_TAKE_OPENS, sizeof JT_TAKE_OPENS - 1, "<take-opens>",
                        JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(r)) { JS_FreeValue(jsctx, JS_GetException(jsctx)); return NULL; }
    char *out = NULL;
    size_t n = 0;
    const char *str = JS_ToCStringLen(jsctx, &n, r);
    if (str != NULL) {
        if (n != 0 && n != (size_t)-1) {
            out = (char *)malloc(n + 1);
            if (out != NULL) { memcpy(out, str, n); out[n] = '\0'; }
        }
        JS_FreeCString(jsctx, str);
    }
    JS_FreeValue(jsctx, r);
    return out;
}

/* WebSocket for a trusted host (spec/js_dom.md 7f). The worker never opens a socket:
 * the object records [kind, id, payload] ops in __wsOps (binary payloads as hex, so a
 * byte survives the UTF-8 string boundary) and the parent's events arrive through
 * __wsEvent as VALUES. Sockets are standalone event targets ('o'+id). */
static const char JT_WS_SHIM[] =
    "(function(){ var g=__G, seq=0, live={}, nlive=0, MAXS=8, MAXMSG=1048576;"
    "  g.__wsOps=[];"
    "  function err(name,msg){ var e=new Error(msg); e.name=name; return e; }"
    "  function hex(u8){ var s=''; for(var i=0;i<u8.length;i++){ var h=u8[i].toString(16);"
    "    s+=(h.length<2?'0':'')+h; } return s; }"
    "  function WS(url,protocols){"
    "    if(!(this instanceof WS)) throw new TypeError('WebSocket requires new');"
    "    var u; try{ u=new URL(String(url), (g.location&&g.location.href)||undefined); }"
    "    catch(e){ throw err('SyntaxError','Invalid URL'); }"
    "    var pr=u.protocol; if(pr==='https:') pr='wss:'; else if(pr==='http:') pr='ws:';"
    "    if(pr!=='wss:') throw err('SecurityError','Only wss: WebSocket connections are allowed');"
    "    if(nlive>=MAXS) throw err('SecurityError','Too many WebSocket connections');"
    "    var href='wss:'+u.href.slice(u.protocol.length);"
    "    var id=++seq, self=this; nlive++;"
    "    live[id]=this; g.__objRegister(id,this);"
    "    Object.defineProperty(this,'url',{value:href});"
    "    this.readyState=0; this.bufferedAmount=0; this.extensions=''; this.protocol='';"
    "    this.binaryType='blob'; this._id=id;"
    "    g.__evHandlerProps(this,'o'+id,['open','message','error','close']);"
    "    g.__wsOps.push([1,id,href]); }"
    "  WS.CONNECTING=0; WS.OPEN=1; WS.CLOSING=2; WS.CLOSED=3;"
    "  WS.prototype.CONNECTING=0; WS.prototype.OPEN=1; WS.prototype.CLOSING=2; WS.prototype.CLOSED=3;"
    "  WS.prototype.addEventListener=function(t,f,o){ g.__evAdd('o'+this._id,t,f,o); };"
    "  WS.prototype.removeEventListener=function(t,f,o){ g.__evRemove('o'+this._id,t,f,o); };"
    "  WS.prototype.dispatchEvent=function(ev){ return g.__evDispatch('o'+this._id,ev); };"
    "  WS.prototype.send=function(data){"
    "    if(this.readyState===0) throw err('InvalidStateError','WebSocket is not open');"
    "    if(this.readyState!==1) return;"
    "    if(typeof data==='string'){ if(data.length>MAXMSG) throw err('SyntaxError','Message too large');"
    "      g.__wsOps.push([2,this._id,data]); return; }"
    "    var u8=null;"
    "    if(data instanceof ArrayBuffer) u8=new Uint8Array(data);"
    "    else if(data&&ArrayBuffer.isView&&ArrayBuffer.isView(data))"
    "      u8=new Uint8Array(data.buffer,data.byteOffset,data.byteLength);"
    "    if(u8===null){ g.__wsOps.push([2,this._id,String(data)]); return; }"
    "    if(u8.length>MAXMSG) throw err('SyntaxError','Message too large');"
    "    g.__wsOps.push([3,this._id,hex(u8)]); };"
    "  WS.prototype.close=function(){"
    "    if(this.readyState>=2) return; this.readyState=2; g.__wsOps.push([4,this._id,'']); };"
    "  function fire(s,type,props){ var e=g.__mkEvent(type,{}); e.isTrusted=true;"
    "    for(var k in props) e[k]=props[k]; g.__evDispatch('o'+s._id,e); }"
    "  function gone(s){ if(live[s._id]){ delete live[s._id]; nlive--; } }"
    "  g.__wsEvent=function(id,kind,code,data){ var s=live[id]; if(!s) return 0;"
    "    if(kind===1){ s.readyState=1; fire(s,'open',{}); }"
    "    else if(kind===2||kind===3){ if(s.readyState!==1) return 1;"
    "      fire(s,'message',{data:data,origin:s.url.split('/').slice(0,3).join('/')}); }"
    "    else if(kind===5){ fire(s,'error',{}); }"
    "    else if(kind===4){ s.readyState=3; gone(s);"
    "      fire(s,'close',{code:code,reason:String(data||''),wasClean:(code===1000)}); }"
    "    return 1; };"
    "  g.WebSocket=WS; })()";

jd_status jt_enable_ws(js_context *ctx) {
    if (ctx == NULL) return JD_ERR_NULL_ARG;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;
    JSValue r = JS_Eval(jsctx, JT_WS_SHIM, sizeof JT_WS_SHIM - 1, "<ws-shim>",
                        JS_EVAL_TYPE_GLOBAL);
    int ok = !JS_IsException(r);
    if (!ok) JS_FreeValue(jsctx, JS_GetException(jsctx));
    JS_FreeValue(jsctx, r);
    return ok ? JD_OK : JD_ERR_INTERNAL;
}

void jt_ws_ops_free(jt_ws_op *ops, size_t n) {
    if (ops == NULL) return;
    for (size_t i = 0; i < n; ++i) { free(ops[i].data); ops[i].data = NULL; ops[i].len = 0; }
}

static int hex_nibble(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

/* Copies one recorded op payload; a binary op arrives as hex and is decoded. */
static char *ws_payload(int kind, const char *s, size_t n, size_t *out_len) {
    *out_len = 0;
    if (kind == JT_WS_SEND_BIN) {
        if (n % 2 != 0) return NULL;
        char *b = (char *)malloc(n / 2 + 1);
        if (b == NULL) return NULL;
        for (size_t i = 0; i < n; i += 2) {
            int hi = hex_nibble(s[i]), lo = hex_nibble(s[i + 1]);
            if (hi < 0 || lo < 0) { free(b); return NULL; }
            b[i / 2] = (char)((hi << 4) | lo);
        }
        b[n / 2] = '\0';
        *out_len = n / 2;
        return b;
    }
    if (n == (size_t)-1) return NULL;
    char *c = (char *)malloc(n + 1);
    if (c == NULL) return NULL;
    memcpy(c, s, n);
    c[n] = '\0';
    *out_len = n;
    return c;
}

size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap) {
    if (ctx == NULL || ops == NULL || cap == 0) return 0;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return 0;
    JSValue global = JS_GetGlobalObject(jsctx);
    JSValue arr = JS_GetPropertyStr(jsctx, global, "__wsOps");
    size_t k = 0, bytes = 0;
    int64_t len = 0;
    if (JS_IsArray(arr) && JS_GetLength(jsctx, arr, &len) == 0) {
        if (cap > JT_WS_MAX_OPS) cap = JT_WS_MAX_OPS;
        for (int64_t i = 0; i < len && k < cap; ++i) {
            JSValue e = JS_GetPropertyUint32(jsctx, arr, (uint32_t)i);
            JSValue kv = JS_GetPropertyUint32(jsctx, e, 0);
            JSValue iv = JS_GetPropertyUint32(jsctx, e, 1);
            JSValue dv = JS_GetPropertyUint32(jsctx, e, 2);
            int32_t kind = 0, id = 0;
            size_t n = 0;
            const char *str = NULL;
            if (JS_ToInt32(jsctx, &kind, kv) == 0 && JS_ToInt32(jsctx, &id, iv) == 0
                && kind >= JT_WS_OPEN && kind <= JT_WS_CLOSE)
                str = JS_ToCStringLen(jsctx, &n, dv);
            if (str != NULL) {
                size_t plen = 0;
                char *p = (bytes + n <= JT_WS_MAX_BYTES) ? ws_payload(kind, str, n, &plen) : NULL;
                if (p != NULL) {
                    ops[k].kind = kind; ops[k].id = id; ops[k].data = p; ops[k].len = plen;
                    bytes += plen;
                    ++k;
                }
                JS_FreeCString(jsctx, str);
            }
            JS_FreeValue(jsctx, kv); JS_FreeValue(jsctx, iv); JS_FreeValue(jsctx, dv);
            JS_FreeValue(jsctx, e);
        }
        /* Taken (or dropped past the bounds): the queue starts over. */
        JS_SetPropertyStr(jsctx, global, "__wsOps", JS_NewArray(jsctx));
    }
    JS_FreeValue(jsctx, arr);
    JS_FreeValue(jsctx, global);
    return k;
}

int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len) {
    if (ctx == NULL || kind < JT_WSE_OPEN || kind > JT_WSE_ERROR) return 0;
    if (data == NULL) len = 0;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return 0;
    JSValue global = JS_GetGlobalObject(jsctx);
    JSValue fn = JS_GetPropertyStr(jsctx, global, "__wsEvent");
    int delivered = 0;
    if (JS_IsFunction(jsctx, fn)) {
        JSValue payload = (kind == JT_WSE_BINARY)
            ? JS_NewArrayBufferCopy(jsctx, (const uint8_t *)(data != NULL ? data : ""), len)
            : JS_NewStringLen(jsctx, data != NULL ? data : "", len);
        JSValue args[4] = { JS_NewInt32(jsctx, id), JS_NewInt32(jsctx, kind),
                            JS_NewInt32(jsctx, code), payload };
        JSValue r = JS_Call(jsctx, fn, global, 4, args);
        if (JS_IsException(r)) {
            JS_FreeValue(jsctx, JS_GetException(jsctx));
        } else {
            int32_t v = 0;
            if (JS_ToInt32(jsctx, &v, r) == 0) delivered = (v != 0);
        }
        JS_FreeValue(jsctx, r);
        for (int i = 0; i < 4; ++i) JS_FreeValue(jsctx, args[i]);
    }
    JS_FreeValue(jsctx, fn);
    JS_FreeValue(jsctx, global);
    return delivered;
}

/* In-memory localStorage for a trusted host (spec/web_storage.md): a Map with the
 * UTF-8 byte count WST_QUOTA is measured in, and a dirty bit the parent polls. */
static const char JT_STORAGE_SHIM[] =
    "(function(){ var g=__G, m=new Map(), dirty=false, bytes=0, Q=5242880;"
    "  function u8(s){ return dom.u8len(s); }"
    "  g.__lsSeed=function(k,v){ k=String(k); v=String(v);"
    "    if(!m.has(k)){ m.set(k,v); bytes+=u8(k)+u8(v); } };"
    "  var st={"
    "    getItem:function(k){ k=String(k); return m.has(k)?m.get(k):null; },"
    "    setItem:function(k,v){ k=String(k); v=String(v);"
    "      var nb=bytes-(m.has(k)?u8(k)+u8(m.get(k)):0)+u8(k)+u8(v);"
    "      if(nb>Q){ var e=new Error('The quota has been exceeded.');"
    "        e.name='QuotaExceededError'; e.code=22; throw e; }"
    "      m.set(k,v); bytes=nb; dirty=true; },"
    "    removeItem:function(k){ k=String(k);"
    "      if(m.has(k)){ bytes-=u8(k)+u8(m.get(k)); m.delete(k); dirty=true; } },"
    "    clear:function(){ if(m.size){ m.clear(); bytes=0; dirty=true; } },"
    "    key:function(i){ i=Number(i)|0; if(i<0||i>=m.size) return null;"
    "      var j=0, r=null; m.forEach(function(v,k){ if(j++===i) r=k; }); return r; },"
    "    get length(){ return m.size; } };"
    "  g.__lsTake=function(){ if(!dirty) return null; dirty=false; var a=[];"
    "    m.forEach(function(v,k){ a.push(k,v); }); return a; };"
    "  Object.defineProperty(g,'localStorage',{configurable:true,get:function(){return st;}}); })()";

typedef struct jt_seed_ctx { JSContext *js; JSValue fn; JSValue global; } jt_seed_ctx;

static void jt_seed_pair(void *vctx, const char *k, size_t kl, const char *v, size_t vl) {
    jt_seed_ctx *c = (jt_seed_ctx *)vctx;
    JSValue args[2] = { JS_NewStringLen(c->js, k, kl), JS_NewStringLen(c->js, v, vl) };
    JSValue r = JS_Call(c->js, c->fn, c->global, 2, args);
    if (JS_IsException(r)) JS_FreeValue(c->js, JS_GetException(c->js));
    JS_FreeValue(c->js, r);
    JS_FreeValue(c->js, args[0]);
    JS_FreeValue(c->js, args[1]);
}

jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len) {
    if (ctx == NULL) return JD_ERR_NULL_ARG;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;
    JSValue r = JS_Eval(jsctx, JT_STORAGE_SHIM, sizeof JT_STORAGE_SHIM - 1, "<storage-shim>",
                        JS_EVAL_TYPE_GLOBAL);
    int ok = !JS_IsException(r);
    if (!ok) JS_FreeValue(jsctx, JS_GetException(jsctx));
    JS_FreeValue(jsctx, r);
    if (!ok) return JD_ERR_INTERNAL;
    if (blob == NULL || len == 0) return JD_OK;       /* nothing to seed */
    jt_seed_ctx c;
    c.js = jsctx;
    c.global = JS_GetGlobalObject(jsctx);
    c.fn = JS_GetPropertyStr(jsctx, c.global, "__lsSeed");
    if (JS_IsFunction(jsctx, c.fn)) (void)wst_foreach(blob, len, jt_seed_pair, &c);
    JS_FreeValue(jsctx, c.fn);
    JS_FreeValue(jsctx, c.global);
    return JD_OK;
}

int jt_take_storage(js_context *ctx, char **out, size_t *len) {
    if (out != NULL) *out = NULL;
    if (len != NULL) *len = 0;
    if (ctx == NULL || out == NULL || len == NULL) return 0;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return 0;
    static const char take[] = "typeof __lsTake==='function'?__lsTake():null";
    JSValue arr = JS_Eval(jsctx, take, sizeof take - 1, "<storage-take>", JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(arr)) { JS_FreeValue(jsctx, JS_GetException(jsctx)); return 0; }
    int64_t n = 0;
    if (!JS_IsArray(arr) || JS_GetLength(jsctx, arr, &n) != 0 || n < 0 || (n % 2) != 0
        || (uint64_t)n / 2u > WST_MAX_KEYS) {
        JS_FreeValue(jsctx, arr);
        return 0;
    }
    size_t pairs = (size_t)(n / 2);
    const char **ks = (const char **)calloc(pairs ? pairs : 1, sizeof *ks);
    const char **vs = (const char **)calloc(pairs ? pairs : 1, sizeof *vs);
    size_t *kl = (size_t *)calloc(pairs ? pairs : 1, sizeof *kl);
    size_t *vl = (size_t *)calloc(pairs ? pairs : 1, sizeof *vl);
    int rc = 0;
    size_t got = 0;
    if (ks != NULL && vs != NULL && kl != NULL && vl != NULL) {
        int okp = 1;
        for (size_t i = 0; i < pairs && okp; ++i) {
            JSValue kv = JS_GetPropertyUint32(jsctx, arr, (uint32_t)(2 * i));
            JSValue vv = JS_GetPropertyUint32(jsctx, arr, (uint32_t)(2 * i + 1));
            ks[i] = JS_ToCStringLen(jsctx, &kl[i], kv);
            vs[i] = JS_ToCStringLen(jsctx, &vl[i], vv);
            JS_FreeValue(jsctx, kv);
            JS_FreeValue(jsctx, vv);
            got = i + 1;
            if (ks[i] == NULL || vs[i] == NULL) okp = 0;
        }
        if (okp && wst_pack(ks, kl, vs, vl, pairs, out, len) == 0) rc = 1;
    }
    for (size_t i = 0; ks != NULL && vs != NULL && i < got; ++i) {
        if (ks[i] != NULL) JS_FreeCString(jsctx, ks[i]);
        if (vs[i] != NULL) JS_FreeCString(jsctx, vs[i]);
    }
    free(ks); free(vs); free(kl); free(vl);
    JS_FreeValue(jsctx, arr);
    return rc;
}

/* --- dedicated Worker (spec/js_dom.md 7i) ---
 * Each worker is a realm of this runtime. The realm natives are captured here and
 * deleted from the page global; everything the worker can reach is copied in
 * explicitly (no window, no document). Delivery is always a timer task. */
static const char JT_WORKER_SHIM[] =
    "(function(){ var g=__G, NEW=g.__realmNew, EVAL=g.__realmEval, CLONE=g.__realmClone;"
    "  delete g.__realmNew; delete g.__realmEval; delete g.__realmClone;"
    "  if(typeof NEW!=='function') return;"
    "  function utf8(u8){ return (typeof g.TextDecoder==='function')?new g.TextDecoder().decode(u8)"
    "    :String.fromCharCode.apply(null,Array.prototype.slice.call(u8)); }"
    /* data: per WHATWG (base64 or percent-encoded), decoded synchronously */
    "  function dataText(u){ var i=u.indexOf(','); if(i<0) throw new TypeError('bad data: URL');"
    "    var meta=u.slice(5,i), body=u.slice(i+1), b64=/;base64$/i.test(meta), bytes=[];"
    "    if(b64){ var bin=g.atob(body.replace(/%([0-9a-f]{2})/gi,function(m,h){ return String.fromCharCode(parseInt(h,16)); }).replace(/[ \\t\\n\\f\\r]/g,''));"
    "      for(var k=0;k<bin.length;k++) bytes.push(bin.charCodeAt(k)&255); }"
    "    else for(var j=0;j<body.length;j++){ var c=body.charCodeAt(j);"
    "      if(c===37&&/^[0-9a-f]{2}$/i.test(body.substr(j+1,2))){ bytes.push(parseInt(body.substr(j+1,2),16)); j+=2; }"
    "      else if(c<128) bytes.push(c); else { var e=new g.TextEncoder().encode(body.charAt(j)); for(var q=0;q<e.length;q++) bytes.push(e[q]); } }"
    "    return utf8(new Uint8Array(bytes)); }"
    "  function loadText(url,base){ url=String(url);"
    "    if(/^data:/i.test(url)) return dataText(url);"
    "    if(/^blob:/i.test(url)){ var b=g.__objectUrl&&g.__objectUrl(url);"
    "      if(!b||!b._b) throw new TypeError('blob URL not found'); return utf8(b._b); }"
    "    var abs; try{ abs=new g.URL(url,base).href; }catch(e){ throw new TypeError('invalid worker URL'); }"
    "    if(!/^https:/i.test(abs)||typeof g.XMLHttpRequest!=='function') throw new TypeError('worker script not loadable: '+abs);"
    "    var x=new g.XMLHttpRequest(); x.open('GET',abs,false); x.send();"
    "    if(x.status<200||x.status>=300) throw new TypeError('worker script failed: '+x.status); return x.responseText; }"
    "  function Worker(url,opts){ if(!(this instanceof Worker)) throw new TypeError(\"Constructor Worker requires 'new'\");"
    "    var W=this, dead=false, closed=false, ready=false, inbox=[], LW={}, LG={};"
    "    var base=(g.location&&g.location.href)||'about:blank';"
    "    W.onmessage=null; W.onerror=null; W.onmessageerror=null;"
    "    function listeners(L,t){ return (L[t]||[]).slice(); }"
    "    function fireW(t,ev){ if(dead) return; ev.type=t; ev.target=W; ev.currentTarget=W;"
    "      var h=W['on'+t], any=false; if(typeof h==='function'){ any=true; try{ h.call(W,ev); }catch(e){ console.error(e); } }"
    "      listeners(LW,t).forEach(function(f){ any=true; try{ f.call(W,ev); }catch(e){ console.error(e); } });"
    "      if(t==='error'&&!any) console.error('Uncaught (in worker) '+ev.message); }"
    "    function errorEv(e,file){ var m=(e&&e.message!==undefined)?String((e.name?e.name+': ':'')+e.message):String(e);"
    "      return {message:m,filename:file||String(url),lineno:0,colno:0,error:null,preventDefault:function(){}}; }"
    "    W.addEventListener=function(t,f){ if(typeof f==='function') (LW[t]=LW[t]||[]).push(f); };"
    "    W.removeEventListener=function(t,f){ var a=LW[t]; if(a){ var i=a.indexOf(f); if(i>=0) a.splice(i,1); } };"
    "    W.dispatchEvent=function(ev){ fireW(ev.type,ev); return true; };"
    "    W.terminate=function(){ dead=true; inbox.length=0; };"
    "    if(opts&&opts.type==='module'){ g.setTimeout(function(){ fireW('error',errorEv('module workers are not supported')); },0); return; }"
    "    var G=NEW(); if(G===null){ g.setTimeout(function(){ fireW('error',errorEv('too many workers')); },0); return; }"
    "    function deliverToWorker(data){ if(dead||closed) return; var ev={type:'message',data:data,ports:[],origin:'',target:G,currentTarget:G};"
    "      try{ if(typeof G.onmessage==='function') G.onmessage.call(G,ev);"
    "        listeners(LG,'message').forEach(function(f){ f.call(G,ev); }); }"
    "      catch(e){ fireW('error',errorEv(e)); } }"
    "    W.postMessage=function(d){ if(dead) return; var c=CLONE(d,G);"
    "      g.setTimeout(function(){ if(!ready){ inbox.push(c); return; } deliverToWorker(c); },0); };"
    /* the worker's global scope */
    "    G.self=G; G.onmessage=null; G.onerror=null; G.name=(opts&&opts.name)?String(opts.name):'';"
    "    G.postMessage=function(d){ if(dead||closed) return; var c=CLONE(d,g);"
    "      g.setTimeout(function(){ fireW('message',{data:c,ports:[],origin:'',lastEventId:''}); },0); };"
    "    G.close=function(){ closed=true; };"
    "    G.addEventListener=function(t,f){ if(typeof f==='function') (LG[t]=LG[t]||[]).push(f); };"
    "    G.removeEventListener=function(t,f){ var a=LG[t]; if(a){ var i=a.indexOf(f); if(i>=0) a.splice(i,1); } };"
    "    G.dispatchEvent=function(){ return true; };"
    "    G.importScripts=function(){ for(var i=0;i<arguments.length;i++){ var u=String(arguments[i]);"
    "      EVAL(G,loadText(u,base),u); } };"
    "    function guard(fn,args){ return function(){ if(dead||closed) return;"
    "      try{ if(typeof fn==='function') fn.apply(G,args); else EVAL(G,String(fn),'timer'); }"
    "      catch(e){ fireW('error',errorEv(e)); } }; }"
    "    G.setTimeout=function(fn,ms){ return g.setTimeout(guard(fn,Array.prototype.slice.call(arguments,2)),ms); };"
    "    G.setInterval=function(fn,ms){ return g.setInterval(guard(fn,Array.prototype.slice.call(arguments,2)),ms); };"
    "    G.clearTimeout=g.clearTimeout; G.clearInterval=g.clearInterval; G.console=g.console;"
    "    ['TextEncoder','TextDecoder','Blob','File','FileReader','URL','URLSearchParams','atob','btoa',"
    "     'structuredClone','performance','crypto','fetch','Request','Response','Headers','AbortController',"
    "     'AbortSignal','XMLHttpRequest','FormData','MessageChannel','BroadcastChannel','Event','EventTarget']"
    "    .forEach(function(n){ if(g[n]!==undefined) G[n]=g[n]; });"
    "    var loc; try{ loc=new g.URL(String(url),base); }catch(e){ loc=null; }"
    "    G.location={href:loc?loc.href:String(url),origin:loc?loc.origin:'null',protocol:loc?loc.protocol:'',"
    "      host:loc?loc.host:'',hostname:loc?loc.hostname:'',port:loc?loc.port:'',pathname:loc?loc.pathname:'',"
    "      search:loc?loc.search:'',hash:loc?loc.hash:'',toString:function(){ return this.href; }};"
    "    if(g.navigator) G.navigator={userAgent:g.navigator.userAgent,language:g.navigator.language,"
    "      languages:g.navigator.languages,hardwareConcurrency:g.navigator.hardwareConcurrency,"
    "      platform:g.navigator.platform,onLine:true};"
    "    EVAL(G,'self.queueMicrotask=function(f){ Promise.resolve().then(f); };','<worker-scope>');"
    "    g.setTimeout(function(){ if(dead) return; var src;"
    "      try{ src=loadText(url,base); }catch(e){ fireW('error',errorEv(e)); return; }"
    "      try{ EVAL(G,src,String(url)); }catch(e){ fireW('error',errorEv(e,String(url))); }"
    "      ready=true; var q=inbox.splice(0); q.forEach(deliverToWorker); },0); }"
    "  g.Worker=Worker; })()";

jd_status jt_enable_worker(js_context *ctx) {
    if (ctx == NULL) return JD_ERR_NULL_ARG;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;
    if (js_install_realms(ctx) != JS_OK) return JD_ERR_OOM;
    JSValue r = JS_Eval(jsctx, JT_WORKER_SHIM, sizeof JT_WORKER_SHIM - 1, "<worker-shim>",
                        JS_EVAL_TYPE_GLOBAL);
    int ok = !JS_IsException(r);
    if (!ok) JS_FreeValue(jsctx, JS_GetException(jsctx));
    JS_FreeValue(jsctx, r);
    return ok ? JD_OK : JD_ERR_INTERNAL;
}
