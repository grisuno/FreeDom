/*
 * js_native (jn_) -- implementation. Contract: spec/js_native.md.
 */
#include "js_native.h"

#include <stdio.h>
#include <string.h>

#include "css.h"
#include "js_native_internal.h"

/* Longest `property: value` CSS.supports() answers for; anything longer is unsupported. */
#define JN_SUPPORTS_MAX 512

JSValue jn_host_eval(JSContext *c, const char *src, size_t len, const char *name) {
    JSRuntime *rt = JS_GetRuntime(c);
    bool prev = JS_SetHideSource(rt, true);
    JSValue r = JS_Eval(c, src, len, name, JS_EVAL_TYPE_GLOBAL);
    (void)JS_SetHideSource(rt, prev);
    return r;
}

/* __cssOk(decl): 1 when the cascade keeps `decl` ("prop: value") whole. The answer is the
 * parser's own verdict (its drop log), not a second list of property names to keep in sync. */
static JSValue jn_css_ok(JSContext *c, JSValueConst this_val, int argc, JSValueConst *argv) {
    (void)this_val;
    if (argc < 1) return JS_FALSE;
    size_t dl = 0;
    const char *decl = JS_ToCStringLen(c, &dl, argv[0]);
    if (decl == NULL) return JS_EXCEPTION;
    int ok = 0;
    /* A brace or semicolon would let the text close the rule and smuggle a second one. */
    if (dl > 0 && dl <= JN_SUPPORTS_MAX && memchr(decl, '{', dl) == NULL
     && memchr(decl, '}', dl) == NULL && memchr(decl, ';', dl) == NULL) {
        char rule[JN_SUPPORTS_MAX + 8];
        int n = snprintf(rule, sizeof rule, "a{%s}", decl);
        if (n > 0 && (size_t)n < sizeof rule) {
            css_sheet *sheet = NULL;
            css_drop_log log = { NULL, 0, 0, 0 };
            if (css_parse_logged(rule, (size_t)n, NULL, NULL, &sheet, &log) == CSS_OK)
                ok = (log.total == 0);
            css_free(sheet);
        }
    }
    JS_FreeCString(c, decl);
    return JS_NewBool(c, ok);
}

/* The seal factory. Called once per context with the global object and the CSS verdict
 * function; returns run(), which does the work and may be called again later. Every step is
 * idempotent (it only fills what is missing). */
static const char JN_SEAL[] =
"(function(g,cssOk){'use strict';"
" var FT=Function.prototype.toString, OP=Object.prototype, TAG=Symbol.toStringTag;"
" var def=Object.defineProperty, gopd=Object.getOwnPropertyDescriptor, names=Object.getOwnPropertyNames;"
" var NATIVE=/\\{\\n    \\[native code\\]\\n\\}$/;"
" function host(f){ try{ return NATIVE.test(FT.call(f)); }catch(e){ return false; } }"
" function setName(f,n){ try{ def(f,'name',{value:n,configurable:true}); }catch(e){} }"
/* Names: a host function published anonymously takes the key it is published under. */
/* A host function published under a key other than its own name (a generic wrapper `f`, a
 * stub constructor `F`) takes the key too -- once, and never an ECMAScript intrinsic, whose
 * aliases are deliberate (Set.prototype.keys is `values`), nor a real alias of a global. */
" var seen=new WeakSet(), named=new WeakSet(), tagged=new WeakSet(), budget=0;"
" var INTR=new WeakSet(); ['Object','Function','Array','Number','Boolean','String','Symbol','Date','RegExp',"
"  'Error','Promise','Map','Set','WeakMap','WeakSet','WeakRef','ArrayBuffer','SharedArrayBuffer','DataView',"
"  'BigInt','Proxy','Reflect','Math','JSON','Atomics','Iterator','FinalizationRegistry','Intl'].forEach(function(n){"
"   var v=g[n]; if(v&&(typeof v==='object'||typeof v==='function')){ INTR.add(v);"
"    if(v.prototype&&typeof v.prototype==='object') INTR.add(v.prototype); } });"
" function alias(f){ try{ var d=gopd(g,f.name); return !!d&&d.value===f; }catch(e){ return false; } }"
" function nameProps(o){"
"  var ks; try{ ks=names(o); }catch(e){ return; } var strict=INTR.has(o);"
"  for(var i=0;i<ks.length;i++){ var k=ks[i], d;"
"   try{ d=gopd(o,k); }catch(e){ continue; } if(!d) continue;"
"   if(typeof d.value==='function'){ var f=d.value;"
"    if(f.name!==k&&!named.has(f)&&(f.name===''||(!strict&&/^[A-Za-z_$][\\w$]*$/.test(k)&&!alias(f)))&&host(f)){"
"     setName(f,k); named.add(f); } }"
"   else { if(typeof d.get==='function'&&(d.get.name===''||d.get.name==='get')&&host(d.get)) setName(d.get,'get '+k);"
"          if(typeof d.set==='function'&&(d.set.name===''||d.set.name==='set')&&host(d.set)) setName(d.set,'set '+k); } } }"
/* The sets persist across runs: a second run (after the per-page installs) only pays for
 * re-reading the global's own keys and for whatever appeared since the first. */
" function visit(o){"
"  if(o===null||(typeof o!=='object'&&typeof o!=='function')||seen.has(o)||--budget<0) return;"
"  seen.add(o); nameProps(o);"
"  if(typeof o==='function'){ var p; try{ p=o.prototype; }catch(e){}"
"   if(p&&typeof p==='object'&&!seen.has(p)){ seen.add(p); nameProps(p); } }"
"  var pr=Object.getPrototypeOf(o); if(pr&&pr!==OP&&pr!==Function.prototype&&!seen.has(pr)){ seen.add(pr); nameProps(pr); } }"
" function root(o){ if(!o) return; nameProps(o);"
"  var ks; try{ ks=names(o); }catch(e){ return; }"
"  for(var i=0;i<ks.length;i++){ var d; try{ d=gopd(o,ks[i]); }catch(e){ continue; }"
"   if(d&&'value' in d) visit(d.value); }"
"  var pr=Object.getPrototypeOf(o); if(pr&&pr!==OP) visit(pr); }"
" function run(){ budget=60000;"
" root(g);"
" try{ root(g.document); }catch(e){}"
/* Interfaces: prototype[Symbol.toStringTag]. ECMAScript intrinsics keep their own answer. */
" var ES={Object:1,Function:1,Array:1,Number:1,Boolean:1,String:1,Symbol:1,Date:1,RegExp:1,Error:1,"
"  EvalError:1,RangeError:1,ReferenceError:1,SyntaxError:1,TypeError:1,URIError:1,AggregateError:1,"
"  InternalError:1,Proxy:1,WeakRef:1,FinalizationRegistry:1,Iterator:1,BigInt:1,Promise:1,Map:1,Set:1,"
"  WeakMap:1,WeakSet:1,ArrayBuffer:1,SharedArrayBuffer:1,DataView:1,DOMException:0};"
" function tag(o,t){ try{ if(!Object.prototype.hasOwnProperty.call(o,TAG)) def(o,TAG,{value:t,configurable:true}); }catch(e){} }"
" function illegal(n){ var F=function(){ throw new TypeError('Illegal constructor'); }; setName(F,n); return F; }"
" function iface(n){ if(typeof g[n]!=='function'){ try{ def(g,n,{value:illegal(n),writable:true,configurable:true}); }catch(e){ return null; } } return g[n]; }"
" var gk=names(g);"
" for(var i=0;i<gk.length;i++){ var k=gk[i]; if(ES[k]===1||!/^[A-Z]/.test(k)||/^[A-Z0-9_]+$/.test(k)) continue;"
"  var d=gopd(g,k); if(!d||typeof d.value!=='function') continue; var c=d.value, p;"
"  try{ p=c.prototype; }catch(e){ continue; }"
"  if(!p||typeof p!=='object'||tagged.has(c)) continue; tagged.add(c); if(!host(c)) continue;"
"  if(/Array$/.test(k)&&Object.getPrototypeOf(c)!==Function.prototype) continue;"   /* typed arrays */
"  if(c.name===k||c.name==='') tag(p,k); }"
/* Singletons: an instance of its interface, tagged through the interface prototype. */
" function bind(o,n){ if(o===null||o===undefined||(typeof o!=='object'&&typeof o!=='function')) return;"
"  var C=iface(n); if(!C) return; var is=false; try{ is=o instanceof C; }catch(e){}"
"  if(!is){ var pr=Object.getPrototypeOf(o);"
"   if(pr&&pr!==OP&&Object.getPrototypeOf(pr)===OP&&!Object.prototype.hasOwnProperty.call(pr,'constructor')){"
      /* A private prototype (navigator's): it BECOMES the interface prototype. */
"    var old=C.prototype; try{ var up=old?Object.getPrototypeOf(old):null; if(up&&up!==OP) Object.setPrototypeOf(pr,up); }catch(e){}"
"    try{ C.prototype=pr; def(pr,'constructor',{value:C,writable:true,configurable:true}); }catch(e){} }"
"   else if(pr===OP&&Object.isExtensible(o)){ try{ Object.setPrototypeOf(o,C.prototype); }catch(e){} } }"
"  tag(C.prototype,n); nameProps(C.prototype);"
"  try{ if(o[TAG]!==n) tag(o,n); }catch(e){} }"
" var S=[['navigator','Navigator'],['screen','Screen'],['performance','Performance'],['history','History'],"
"  ['location','Location'],['crypto','Crypto'],['localStorage','Storage'],['sessionStorage','Storage'],"
"  ['customElements','CustomElementRegistry'],['visualViewport','VisualViewport'],['indexedDB','IDBFactory'],"
"  ['document','HTMLDocument']];"
" for(var j=0;j<S.length;j++){ var v; try{ v=g[S[j][0]]; }catch(e){ continue; } bind(v,S[j][1]); }"
" try{ bind(g.crypto&&g.crypto.subtle,'SubtleCrypto'); }catch(e){}"
" try{ bind(g.screen&&g.screen.orientation,'ScreenOrientation'); }catch(e){}"
" try{ bind(g.performance&&g.performance.timing,'PerformanceTiming'); }catch(e){}"
" try{ bind(g.document&&g.document.implementation,'DOMImplementation'); }catch(e){}"
" try{ bind(g.document&&g.document.fonts,'FontFaceSet'); }catch(e){}"
" try{ if(g.console) tag(g.console,'console'); if(g.CSS) tag(g.CSS,'CSS'); }catch(e){}"
/* The engine tags its global object "global"; a browser's window carries no own tag. */
" var W=iface('Window'); if(W){ tag(W.prototype,'Window'); try{ delete g[TAG]; }catch(e){}"
"  try{ if(g[TAG]!=='Window') def(g,TAG,{value:'Window',configurable:true}); }catch(e){} }"
/* CSS.supports: the cascade's own verdict. */
" if(g.CSS&&!tagged.has(g.CSS)){ tagged.add(g.CSS); var sup=function(a,b){"
"   if(arguments.length>=2){ a=String(a).trim(); b=String(b).trim(); if(!a||!b) return false;"
"    if(a.slice(0,2)==='--') return true; return cssOk(a+':'+b); }"
"   var s=String(a).trim(); if(s.charAt(0)==='('&&s.charAt(s.length-1)===')') s=s.slice(1,-1);"
"   var i=s.indexOf(':'); if(i<=0) return false; return sup(s.slice(0,i),s.slice(i+1)); };"
"  setName(sup,'supports'); try{ def(g.CSS,'supports',{value:sup,writable:true,configurable:true,enumerable:true}); }catch(e){} }"
" } return run; })";

int jn_seal(js_context *ctx) {
    if (ctx == NULL) return -1;
    JSContext *c = (JSContext *)js_context_raw(ctx);
    JSValue *slot = js_host_slot(ctx);
    if (c == NULL || slot == NULL) return -1;

    if (JS_IsUndefined(*slot)) {
        JSValue factory = jn_host_eval(c, JN_SEAL, sizeof JN_SEAL - 1, "<native-seal>");
        if (JS_IsException(factory)) { JS_FreeValue(c, JS_GetException(c)); return -1; }
        JSValue global = JS_GetGlobalObject(c);
        JSValue args[2] = { global, JS_NewCFunction(c, jn_css_ok, "supports", 1) };
        JSValue run = JS_Call(c, factory, JS_UNDEFINED, 2, args);
        JS_FreeValue(c, args[1]);
        JS_FreeValue(c, global);
        JS_FreeValue(c, factory);
        if (JS_IsException(run)) { JS_FreeValue(c, JS_GetException(c)); return -1; }
        *slot = run;                       /* owned by the context, freed with it */
    }
    JSValue r = JS_Call(c, *slot, JS_UNDEFINED, 0, NULL);
    if (JS_IsException(r)) { JS_FreeValue(c, JS_GetException(c)); return -1; }
    JS_FreeValue(c, r);
    return 0;
}
