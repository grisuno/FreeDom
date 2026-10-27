/*
 * TDD suite for js_dom (DOM <-> JS bridge).
 *
 * RED state until src/js_dom.c exists: this links and fails on purpose.
 *
 * Build: make test   (cmocka + lexbor + vendored quickjs)
 * ASan:  make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "dom.h"
#include "html_parse.h"
#include "js_dom.h"
#include "js_trusted.h"
#include "js_geom.h"
#include "web_storage.h"
#include "js_sandbox.h"
#include "fb_panes.h"
#include "fb_cmdline.h"
#include "url.h"

static const char HTML[] =
    "<!DOCTYPE html><html><head><title>T</title></head>"
    "<body>"
    "<div id=\"main\" class=\"container box\">"
    "<p class=\"text\">Hello</p>"
    "<p class=\"text muted\">World</p>"
    "<button id=\"go\" class=\"btn\">Go</button>"
    "<form id=\"frm\" action=\"/submit\" method=\"post\">"
    "<input type=\"text\" name=\"q\">"
    "<input type=\"submit\" id=\"sbm\" value=\"Send\">"
    "</form>"
    "</div>"
    "</body></html>";

typedef struct fixture {
    hp_document *doc;
    dom_index   *idx;
    js_context  *ctx;
    jd_opaque    jd_op;
} fixture;

static int setup(void **state) {
    fixture *f = (fixture *)calloc(1, sizeof *f);
    if (f == NULL) return -1;
    if (hp_parse(HTML, sizeof HTML - 1, NULL, &f->doc) != HP_OK) return -1;
    if (dom_build(f->doc, &f->idx) != DOM_OK) return -1;
    if (js_context_new(NULL, &f->ctx) != JS_OK) return -1;
    if (jd_install(f->ctx, f->idx, &f->jd_op) != JD_OK) return -1;
    *state = f;
    return 0;
}

static int teardown(void **state) {
    fixture *f = (fixture *)*state;
    if (f != NULL) {
        js_context_free(f->ctx);
        dom_free(f->idx);
        hp_document_free(f->doc);
        free(f);
    }
    return 0;
}

/* Evaluates src in the fixture context and returns the result string (owned by
 * the caller-provided js_result, freed by the caller). */
static js_status run(fixture *f, const char *src, js_result *r) {
    return js_eval(f->ctx, src, strlen(src), r);
}

#define EXPECT(f, src, expected)                                   \
    do {                                                           \
        js_result _r;                                              \
        assert_int_equal(run((f), (src), &_r), JS_OK);             \
        assert_non_null(_r.value);                                 \
        assert_string_equal(_r.value, (expected));                 \
        js_result_free(&_r);                                       \
    } while (0)

/* --- install --- */

static void test_install_null_args(void **state) {
    (void)state;
    js_context *ctx = NULL;
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    assert_int_equal(jd_install(ctx, NULL, NULL), JD_ERR_NULL_ARG);
    assert_int_equal(jd_install(NULL, NULL, NULL), JD_ERR_NULL_ARG);
    js_context_free(ctx);
}

/* --- queries from JS --- */

static void test_get_element_by_id(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "dom.getElementById('main') !== null", "true");
    EXPECT(f, "dom.tagName(dom.getElementById('main'))", "div");
    EXPECT(f, "dom.tagName(dom.getElementById('go'))", "button");
    EXPECT(f, "dom.getElementById('nope')", "null");
}

static void test_node_count(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "dom.nodeCount() > 0", "true");
}

static void test_by_class_and_tag(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "dom.getByClass('text').length", "2");
    EXPECT(f, "dom.getByClass('btn').length", "1");
    EXPECT(f, "dom.getByTag('p').length", "2");
    EXPECT(f, "dom.getByTag('marquee').length", "0");
}

static void test_navigation(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "dom.tagName(dom.firstChild(dom.getElementById('main')))", "p");
    EXPECT(f,
        "var b=dom.getElementById('go'); dom.tagName(dom.parent(b))", "div");
    EXPECT(f,
        "var p=dom.firstChild(dom.getElementById('main'));"
        "dom.tagName(dom.nextSibling(p))", "p");
}

static void test_attributes(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "dom.getAttribute(dom.getElementById('main'),'class')",
           "container box");
    EXPECT(f, "dom.getAttribute(dom.getElementById('main'),'data-x')", "null");
}

static void test_document_order(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f,
        "dom.precedes(dom.getElementById('main'), dom.getElementById('go'))",
        "true");
}

/* --- robustness: bogus handles never crash, just yield null --- */

static void test_invalid_handles(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "dom.tagName(99999)", "null");
    EXPECT(f, "dom.tagName(-1)", "null");
    EXPECT(f, "dom.firstChild(99999)", "null");
    EXPECT(f, "dom.getAttribute(99999,'id')", "null");
}

/* --- the API cannot be hijacked --- */

static void test_methods_are_frozen(void **state) {
    fixture *f = (fixture *)*state;
    /* Reassigning a method must not take effect (non-writable). */
    EXPECT(f, "try{dom.getElementById=1}catch(e){}; typeof dom.getElementById",
           "function");
    /* The sealed object rejects new properties. */
    EXPECT(f, "try{dom.injected=1}catch(e){}; typeof dom.injected", "undefined");
}

/* --- still no I/O even with dom installed --- */

static void test_no_io_with_dom(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof require + typeof fetch + typeof std",
           "undefinedundefinedundefined");
}

/* --- live DOM (Hito 20b): the `document` shim mutates the tree safely --- */

static void test_document_shim_present(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof document + typeof document.getElementById", "objectfunction");
    EXPECT(f, "document.title", "T");
    EXPECT(f, "document.getElementById('go').textContent", "Go");
}

static void test_query_selector_from_js(void **state) {
    fixture *f = (fixture *)*state;
    /* Real querySelector over the live DOM via the css_select engine. */
    EXPECT(f, "document.querySelector('p.text').textContent", "Hello");
    EXPECT(f, "document.querySelectorAll('p').length", "2");
    EXPECT(f, "document.querySelector('div#main > button').tagName", "BUTTON");
    EXPECT(f, "document.querySelectorAll('p, button').length", "3");
    /* A no-match returns null / empty list, never a throw. */
    EXPECT(f, "document.querySelector('table') === null", "true");
    /* Unsupported constructs fail closed (drop the selector, no throw). */
    EXPECT(f, "document.querySelector('p::before') === null", "true");
    EXPECT(f, "document.querySelectorAll('@#$').length", "0");
}

static void test_element_matches_closest_query_from_js(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "document.getElementById('go').matches('button.btn')", "true");
    EXPECT(f, "document.getElementById('go').matches('p')", "false");
    EXPECT(f, "document.getElementById('go').closest('div.container').id", "main");
    /* Element-scoped querySelector is descendants-only. */
    EXPECT(f, "document.getElementById('main').querySelectorAll('p').length", "2");
    EXPECT(f, "document.getElementById('main').querySelector('div') === null", "true");
}

static void test_node_identity_is_cached(void **state) {
    fixture *f = (fixture *)*state;
    /* Same handle -> same wrapper object, so === works (frameworks rely on it). */
    EXPECT(f, "document.getElementById('go') === document.getElementById('go')", "true");
    EXPECT(f, "document.querySelector('#go') === document.getElementById('go')", "true");
}

static void test_element_traversal(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "document.getElementById('go').parentNode.id", "main");
    EXPECT(f, "document.getElementById('main').children.length", "4");
    EXPECT(f, "document.getElementById('main').firstElementChild.tagName", "P");
    EXPECT(f, "document.getElementById('main').childElementCount", "4");
    EXPECT(f, "document.getElementById('main').contains(document.getElementById('go'))", "true");
}

static void test_classlist_backs_class_attr(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "document.getElementById('go').classList.contains('btn')", "true");
    EXPECT(f, "var e=document.getElementById('go'); e.classList.add('big');"
              "e.classList.contains('big') && e.getAttribute('class')", "btn big");
    EXPECT(f, "var e=document.getElementById('go'); e.classList.remove('btn');"
              "e.classList.contains('btn')", "false");
    EXPECT(f, "var e=document.getElementById('go'); e.classList.toggle('on'); e.classList.contains('on')", "true");
}

static void test_classlist_is_iterable_like_domtokenlist(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var o=[]; for (var c of document.getElementById('go').classList) o.push(c); o.join()", "btn");
    EXPECT(f, "var d=document.implementation.createHTMLDocument(''), fr=document.createDocumentFragment();"
              "[d.getRootNode()===d, fr.getRootNode()===fr].join()", "true,true");
    EXPECT(f, "var e=document.getElementById('go'); e.classList.add('big');"
              "var o=[]; e.classList.forEach(function(c,i){ o.push(i+c); }); o.join()", "0btn,1big");
    EXPECT(f, "var e=document.getElementById('go'); e.classList.value='a b';"
              "[e.classList.value, e.className, [...e.classList].join('+'), e.classList.length].join('|')",
              "a b|a b|a+b|2");
    EXPECT(f, "var e=document.getElementById('go');"
              "[e.classList.contains('zz'), Array.from(e.classList.entries()).length, e.classList[0]].join()",
              "false,2,a");
}

static void test_canvas_element_inherits_html_element(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var c=document.createElement('canvas'); c.style.display='none';"
              "[c instanceof HTMLElement, c instanceof HTMLCanvasElement, c.style.display,"
              " typeof c.addEventListener, typeof c.getContext, c.width].join()",
              "true,true,none,function,function,300");
}

static void test_document_fragment_reparents(void **state) {
    fixture *f = (fixture *)*state;
    /* Fragment collects children; appending it re-parents them into #main. */
    EXPECT(f, "var frag=document.createDocumentFragment();"
              "frag.appendChild(document.createElement('span'));"
              "frag.appendChild(document.createElement('span'));"
              "var m=document.getElementById('main');"
              "m.appendChild(frag);"
              "m.getElementsByTagName('span').length", "2");
}

/* jQuery 1.x support-detection clones a fragment twice and reads .lastChild
 * (b.checkClone). A minimal fragment without cloneNode/lastChild threw "not a
 * function", which aborted the whole jQuery bundle -> "$ is not defined" on every
 * page that ships jQuery (Slashdot). The fragment must be complete enough that the
 * detection completes without throwing (the detected value need not be accurate). */
static void test_fragment_clone_chain_does_not_throw(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof document.createDocumentFragment().cloneNode", "function");
    EXPECT(f, "typeof document.createDocumentFragment().lastChild", "object"); /* null */
    /* The exact jQuery pattern must not throw. */
    EXPECT(f, "var n=document.createElement('div'); n.appendChild(document.createElement('input'));"
              "var i=document.createDocumentFragment(); i.appendChild(n.lastChild);"
              "var ok='ok'; try{ i.cloneNode(true).cloneNode(true).lastChild; }"
              "catch(e){ ok='threw'; } ok", "ok");
    /* Deep clone reproduces children (each is itself cloneable). */
    EXPECT(f, "var i=document.createDocumentFragment();"
              "i.appendChild(document.createElement('span'));"
              "i.cloneNode(true).lastChild.tagName", "SPAN");
    EXPECT(f, "var n=document.createElement('ul');"
              "n.appendChild(document.createElement('li')); n.lastChild.tagName", "LI");
}

static void test_modern_globals_do_not_throw(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof Element + typeof Node + typeof HTMLElement", "functionfunctionfunction");
    EXPECT(f, "Node.ELEMENT_NODE", "1");
    EXPECT(f, "matchMedia('(prefers-color-scheme: dark)').matches", "false");
    EXPECT(f, "typeof (new MutationObserver(function(){})).observe", "function");
    EXPECT(f, "var seen=false; requestAnimationFrame(function(){seen=true;});"
              "__fireDeferred(); seen", "true");
    EXPECT(f, "getComputedStyle(document.body).getPropertyValue('color')", "");
    EXPECT(f, "new Event('x').type", "x");
    EXPECT(f, "document.createElementNS('http://www.w3.org/2000/svg','svg').tagName", "SVG");
    /* SOP by construction: window.open / postMessage stay undefined (no popups). */
    EXPECT(f, "typeof window.open + typeof postMessage", "undefinedundefined");
    /* Normalized viewport (anti-fp): fixed, not the real window size. */
    EXPECT(f, "window.innerWidth", "1920");
}

/* IntersectionObserver fires synthetically (2026-07-19): observe(el) queues ONE
 * delivery with isIntersecting:true / ratio 1 in the deferred phase (setTimeout
 * 0). Every value is a synthetic constant -- zero real geometry or timing leaks
 * -- but scroll-reveal libraries (AOS et al) that keep content at opacity:0
 * until the observer fires now reveal it. disconnect() before the deferred
 * phase suppresses delivery; the other observers stay never-fire. */
static void test_intersection_observer_fires_synthetically(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var hit=0, en=null;"
              "var io=new IntersectionObserver(function(es){hit=es.length; en=es[0];});"
              "io.observe(document.body); __fireDeferred();"
              "'' + hit + ',' + en.isIntersecting + ',' + en.intersectionRatio + ','"
              " + (en.target===document.body)", "1,true,1,true");
    EXPECT(f, "var hit2=0; var io2=new IntersectionObserver(function(){hit2++;});"
              "io2.observe(document.body); io2.disconnect(); __fireDeferred(); hit2", "0");
}

/* 7j slice1 RED: style write-through + getComputedStyle inline + RO/MO synthetic. */
static void test_style_write_through(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var el=document.createElement('div'); el.style.color='red';"
              "el.getAttribute('style')", "color: red;");
    EXPECT(f, "var el=document.createElement('div');"
              "el.setAttribute('style','color: blue'); el.style.color", "blue");
    EXPECT(f, "var el=document.createElement('div'); el.style.backgroundColor='green';"
              "el.style.getPropertyValue('background-color')", "green");
    EXPECT(f, "var el=document.createElement('div');"
              "el.setAttribute('style','display: none'); el.style.display", "none");
}

static void test_get_computed_style_inline(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var el=document.createElement('div');"
              "el.setAttribute('style','color: red; display: none');"
              "getComputedStyle(el).color", "red");
    EXPECT(f, "var el=document.createElement('div');"
              "el.setAttribute('style','color: red');"
              "getComputedStyle(el).getPropertyValue('color')", "red");
    EXPECT(f, "var el=document.createElement('div');"
              "getComputedStyle(el).getPropertyValue('color')", "");
}

static void test_resize_observer_fires_synthetically(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var hit=0, en=null;"
              "var ro=new ResizeObserver(function(es){hit=es.length; en=es[0];});"
              "ro.observe(document.body); __fireDeferred();"
              "'' + hit + ',' + (en.target===document.body)", "1,true");
    EXPECT(f, "var hit2=0; var ro2=new ResizeObserver(function(){hit2++;});"
              "ro2.observe(document.body); ro2.disconnect(); __fireDeferred(); hit2", "0");
}

/* MutationObserver is REAL (spec/js_mutation.md): records come only from actual DOM
 * mutations, in order, and are delivered once per microtask checkpoint (js_pump_jobs). */
static void test_mutation_observer_reports_child_list(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "globalThis.recs=[]; var mo=new MutationObserver(function(r){ recs=recs.concat(r); });"
              "mo.observe(document.body,{childList:true});"
              "globalThis.d=document.createElement('div'); document.body.appendChild(d);"
              "document.body.removeChild(d); recs.length", "0");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "recs.length+','+recs[0].type+','+recs[0].addedNodes.length+','+(recs[0].addedNodes[0]===d)"
              "+','+recs[1].removedNodes.length+','+(recs[1].target===document.body)",
           "2,childList,1,true,1,true");
    EXPECT(f, "globalThis.quiet=0; var mq=new MutationObserver(function(){quiet++;});"
              "mq.observe(document.body,{childList:true}); 0", "0");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "quiet", "0");
    EXPECT(f, "globalThis.gone=0; var mg=new MutationObserver(function(){gone++;});"
              "mg.observe(document.body,{childList:true}); mg.disconnect();"
              "document.body.appendChild(document.createElement('i')); 0", "0");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "gone", "0");
}

/* A page may observe the DOCUMENT (the usual lazy-loading / hydration idiom): the
 * observation is rooted at the document element. The window is not a Node and still throws. */
static void test_mutation_observer_accepts_document_target(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "globalThis.recs=[]; var mo=new MutationObserver(function(r){ recs=recs.concat(r); });"
              "mo.observe(document,{childList:true,subtree:true});"
              "document.body.appendChild(document.createElement('div')); 0", "0");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "''+recs.length+','+recs[0].type", "1,childList");
    EXPECT(f, "var thrown=false; try{ (new MutationObserver(function(){})).observe(window,{childList:true}); }"
              "catch(e){ thrown=(e instanceof TypeError); } thrown", "true");
}

/* The engine never invents library objects: a page without jQuery has no `jQuery`/`$`, so
 * feature detection (`window.jQuery && jQuery.fn`) takes the no-jQuery path, and the SVG
 * interface family exists for `x instanceof SVGElement`. */
static void test_no_invented_jquery_and_svg_interfaces_exist(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof window.jQuery+','+typeof window.$", "undefined,undefined");
    EXPECT(f, "typeof SVGElement+','+typeof SVGSVGElement+','+(SVGSVGElement.prototype instanceof SVGElement)",
           "function,function,true");
}

/* Uncaught errors are page-visible like in a browser (HTML 8.1.5.5): a throwing timer or
 * listener fires `error` on the window with an ErrorEvent, window.onerror sees it first, and an
 * error thrown by the error handler itself never recurses. */
static void test_uncaught_timer_error_fires_window_error_event(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "globalThis.got=[]; window.addEventListener('error',function(e){"
              "got.push((e instanceof ErrorEvent)+':'+e.message+':'+(e.error instanceof TypeError)); });"
              "window.onerror=function(m){ got.push('onerror:'+m); return true; };"
              "setTimeout(function(){ null.x; },0); __fireDeferred(); got.length", "2");
    EXPECT(f, "got[0].indexOf('onerror:')===0 && got[1].indexOf('true:')===0 && got[1].indexOf(':true')>0",
           "true");
    EXPECT(f, "globalThis.n=0; window.addEventListener('error',function(){ n++; throw new Error('again'); });"
              "setTimeout(function(){ null.y; },0); __fireDeferred(); n", "1");
}

/* A promise rejected with no handler by the end of the job checkpoint fires
 * `unhandledrejection` (PromiseRejectionEvent: promise, reason); one handled in time does not. */
/* <template>.content is a DocumentFragment backed by REAL nodes: innerHTML parses into it,
 * siblings and cloneNode(true) keep their links (Svelte/Lit/Vue walk firstChild/nextSibling
 * over template.content.cloneNode(true)), and appending the fragment moves its children. */
static void test_template_content_is_a_real_fragment(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "globalThis.t=document.createElement('template');"
              "t.innerHTML='<div class=\"a\"><span>s</span></div> <!>x';"
              "var c=t.content; [c.nodeType,c.firstChild.className,c.firstChild.nextSibling.nodeType,"
              "c.childNodes.length].join()", "11,a,3,4");
    EXPECT(f, "globalThis.k=t.content.cloneNode(true);"
              "[k.nodeType,k.firstChild.firstChild.nodeName,k.firstChild.nextSibling.nodeType,"
              "t.content.childNodes.length].join()", "11,SPAN,3,4");
    EXPECT(f, "document.body.appendChild(k); [k.childNodes.length,"
              "document.body.innerHTML.indexOf('<span>s</span>')>=0].join()", "0,true");
    EXPECT(f, "var u=document.createElement('template'); u.innerHTML='<p>q</p>'; u.innerHTML", "<p>q</p>");
}

/* PerformanceObserver.supportedEntryTypes is a static array: web-vitals code (GitHub, reddit) calls
 * .includes on it at boot. Freedom emits no performance entries, so it is honestly empty. */
static void test_performance_observer_supported_entry_types(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "[Array.isArray(PerformanceObserver.supportedEntryTypes),"
              "PerformanceObserver.supportedEntryTypes.includes('soft-navigation')].join()", "true,false");
}

/* Document is a ParentNode: its only element child is the root element (GitHub reads
 * document.firstElementChild.classList at boot). */
static void test_document_parentnode_surface(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "[document.firstElementChild===document.documentElement,"
              "document.lastElementChild===document.documentElement,"
              "document.childElementCount,document.children.length,"
              "document.firstElementChild.classList.contains('x')].join()", "true,true,1,1,false");
}

/* element.attributes is iterable (spread / for-of / Array.from), each entry a name/value Attr. */
static void test_attributes_are_iterable(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var e=document.createElement('div'); e.setAttribute('a','1'); e.setAttribute('b','2');"
              "[[...e.attributes].map(function(x){return x.name+'='+x.value;}).join('&'),"
              "Array.from(e.attributes).length].join()", "a=1&b=2,2");
}

/* An element's nodeValue is null (DOM 4.4); only character data carries a string. */
static void test_element_nodevalue_is_null(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "String(document.body.nodeValue)", "null");
    EXPECT(f, "document.createElement('span').nodeName+document.body.nodeName", "SPANBODY");
    EXPECT(f, "document.createTextNode('z').nodeValue", "z");
}

/* localName/namespaceURI/prefix of an element (DOM 4.9): libraries key custom-element and
 * framework lookups on localName; undefined made customElements.whenDefined reject. */
/* element.dataset is a DOMStringMap (HTML 3.2.6.6): Facebook's bootloader feature-tests
 * `el.dataset instanceof window.DOMStringMap`; the missing global made it throw. */
static void test_dataset_is_a_domstringmap(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof DOMStringMap", "function");
    EXPECT(f, "var b=document.getElementById('go'); b.setAttribute('data-foo-bar','1');"
              "[b.dataset instanceof DOMStringMap, b.dataset.fooBar, ({}) instanceof DOMStringMap].join()", "true,1,false");
    EXPECT(f, "try{ new DOMStringMap(); 'no' }catch(e){ e.name }", "TypeError");
}

static void test_element_local_name_namespace(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "document.createElement('span').localName+'|'+document.body.localName", "span|body");
    EXPECT(f, "document.createElement('x-y').localName", "x-y");
    EXPECT(f, "document.createElement('p').namespaceURI", "http://www.w3.org/1999/xhtml");
    EXPECT(f, "String(document.createElement('p').prefix)", "null");
}

static void test_unhandled_rejection_event(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "globalThis.rj=[]; window.addEventListener('unhandledrejection',function(e){"
              "rj.push(String(e.reason)+':'+(e.promise instanceof Promise)+':'+(e instanceof PromiseRejectionEvent)); });"
              "Promise.reject('boom'); var ok=Promise.reject('fine'); ok.catch(function(){}); 0", "0");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "rj.join('|')", "boom:true:true");
}

/* A <script> inserted by script runs when it becomes connected (HTML 4.12.1): an inline one
 * synchronously, one with `src` asynchronously with load/error events -- the base of every lazy
 * JS loader. It runs once, only as a JS type, never from innerHTML, and a throw is reported (error
 * event) instead of propagating into the inserting script. */
static void test_dynamic_inline_script_runs_once_on_insert(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "globalThis.n=0; var s=document.createElement('script'); s.text='n++';"
              "document.body.appendChild(s); document.head.appendChild(s); ''+n", "1");
    EXPECT(f, "globalThis.m=0; var t=document.createElement('script');"
              "t.appendChild(document.createTextNode('m=5')); document.body.appendChild(t); ''+m", "5");
    EXPECT(f, "globalThis.u=0; var x=document.createElement('script'); x.text='u=1'; ''+u", "0");
    EXPECT(f, "globalThis.p=0; var y=document.createElement('script'); y.type='text/plain'; y.text='p=1';"
              "document.body.appendChild(y); ''+p", "0");
    EXPECT(f, "globalThis.h=0; document.body.innerHTML='<script>h=1<\\/script>'; ''+h", "0");
    EXPECT(f, "globalThis.got=0; window.addEventListener('error',function(){got++;});"
              "var z=document.createElement('script'); z.text='throw new Error(\"x\")';"
              "document.body.appendChild(z); ''+got", "1");
}

static void test_dynamic_script_src_loads_async_and_reports_load_or_error(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "globalThis.r2=0; globalThis.loaded=0; var d=document.createElement('script');"
              "d.src='data:text/javascript,globalThis.r2=2'; d.onload=function(){ loaded=1; };"
              "document.head.appendChild(d); ''+r2+loaded", "00");
    EXPECT(f, "__fireDeferred(); ''+r2+loaded", "21");
    EXPECT(f, "globalThis.er=0; var e=document.createElement('script'); e.src='https://x.test/a.js';"
              "e.onerror=function(){ er=1; }; document.head.appendChild(e); __fireDeferred(); ''+er", "1");
}

/* The wrapper's members must survive every way a page reaches them: a custom element (its
 * prototype is replaced by the class prototype), Element.prototype.m.call(el) (what shadow-DOM
 * polyfills do), per-element on* handler slots, and per-element state (style, classList). These
 * hold whatever way the members are stored (they were own closures per node; they are shared
 * prototype members now, because wrapping thousands of nodes dominated GitHub's load time). */
static void test_element_members_survive_prototype_swaps_and_detached_calls(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "class XA extends HTMLElement{ connectedCallback(){ this.setAttribute('data-up','1'); } }"
              "customElements.define('x-a',XA); var x=document.createElement('x-a'); document.body.appendChild(x);"
              "x.setAttribute('id','xa'); x.classList.add('c1'); x.style.color='red';"
              "[x.getAttribute('data-up'), x.id, x.className, x.getAttribute('style'), x instanceof HTMLElement,"
              " typeof x.querySelector, typeof x.onclick].join('|')",
           "1|xa|c1|color: red;|true|function|object");
    EXPECT(f, "var d1=document.createElement('div'); d1.setAttribute('title','T');"
              "[Element.prototype.getAttribute.call(d1,'title'),"
              " HTMLElement.prototype.click===undefined, typeof Node.prototype.appendChild,"
              " Object.getOwnPropertyDescriptor(Node.prototype,'textContent')!==undefined].join('|')",
           "T|false|function|true");
    EXPECT(f, "var a=document.createElement('div'), b=document.createElement('div'); var n=0;"
              "a.onclick=function(){ n++; }; b.onclick=function(){ n+=10; };"
              "a.dispatchEvent(new Event('click')); [n, typeof a.onclick, typeof b.onclick, a.onclick===b.onclick].join('|')",
           "1|function|function|false");
    EXPECT(f, "var s1=document.createElement('div'), s2=document.createElement('div');"
              "s1.style.color='red'; s2.style.color='blue';"
              "[s1.style.color, s2.style.color, s1.style===s1.style, s1.style===s2.style].join('|')",
           "red|blue|true|false");
}

/* A DocumentFragment and a ShadowRoot are EventTargets and observable (GitHub's invoker
 * behaviours call addEventListener on every shadow root and observe it). */
static void test_shadow_root_is_event_target_and_observable(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var h=document.createElement('div'); document.body.appendChild(h);"
              "var sr=h.attachShadow({mode:'open'}); var hit=0;"
              "sr.addEventListener('ping',function(){hit++;}); sr.dispatchEvent(new Event('ping'));"
              "var l=function(){hit+=10;}; sr.addEventListener('pong',l); sr.removeEventListener('pong',l);"
              "sr.dispatchEvent(new Event('pong'));"
              "(new MutationObserver(function(){})).observe(sr,{childList:true,subtree:true});"
              "hit+','+typeof document.createDocumentFragment().addEventListener", "1,function");
}

static void test_mutation_observer_reports_attributes(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var el=document.createElement('div'); el.setAttribute('data-a','1'); document.body.appendChild(el);"
              "globalThis.recs=[]; var mo=new MutationObserver(function(r){ recs=recs.concat(r); });"
              "mo.observe(el,{attributes:true,attributeOldValue:true,attributeFilter:['data-a']});"
              "el.setAttribute('data-a','2'); el.setAttribute('data-b','x'); el.removeAttribute('data-a'); 0", "0");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "recs.length+','+recs[0].attributeName+','+recs[0].oldValue+','+recs[1].oldValue",
           "2,data-a,1,2");
    EXPECT(f, "var noold=document.createElement('p'); document.body.appendChild(noold);"
              "globalThis.r2=[]; var m2=new MutationObserver(function(r){ r2=r; });"
              "m2.observe(noold,{attributes:true}); noold.className='k'; 0", "0");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "r2.length+','+r2[0].oldValue+','+r2[0].attributeName", "1,null,class");
}

static void test_mutation_observer_subtree_character_data_and_take_records(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var host=document.createElement('div'); globalThis.kid=document.createElement('span');"
              "host.appendChild(kid); document.body.appendChild(host);"
              "var t=document.createTextNode('a'); kid.appendChild(t);"
              "globalThis.seen=[]; var mo=new MutationObserver(function(r){ seen=seen.concat(r); });"
              "mo.observe(host,{subtree:true,childList:true,characterData:true,characterDataOldValue:true});"
              "t.data='b'; kid.appendChild(document.createElement('b')); 0", "0");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "seen.length+','+seen[0].type+','+seen[0].oldValue+','+seen[1].type+','+(seen[1].target===kid)",
           "2,characterData,a,childList,true");
    EXPECT(f, "var host2=document.createElement('div'); document.body.appendChild(host2);"
              "globalThis.cnt=0; var m3=new MutationObserver(function(){cnt++;});"
              "m3.observe(host2,{childList:true}); host2.appendChild(document.createElement('u'));"
              "var taken=m3.takeRecords(); taken.length", "1");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "cnt", "0");
    EXPECT(f, "var sub=document.createElement('div'); document.body.appendChild(sub);"
              "globalThis.c4=0; var m4=new MutationObserver(function(){c4++;});"
              "m4.observe(sub,{childList:true}); globalThis.deep=document.createElement('em');"
              "sub.appendChild(deep); 0", "0");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "c4=0; deep.appendChild(document.createElement('s')); 0", "0");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "c4", "0");
}

/* The natives MutationObserver wraps are sealed again once the shims ran: page script
 * cannot replace or redefine a `dom` mutator (it could otherwise silence observers or
 * hijack the bridge). */
static void test_dom_mutators_are_sealed_after_install(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "['setText','appendChild','insertBefore','moveChildren','removeChild','setAttribute',"
              "'removeAttribute','setInnerHtml'].map(function(n){ var d=Object.getOwnPropertyDescriptor(dom,n);"
              "return d.writable||d.configurable?'OPEN:'+n:'ok'; }).join(',')",
           "ok,ok,ok,ok,ok,ok,ok,ok");
    EXPECT(f, "var before=dom.setText; try{ dom.setText=function(){}; }catch(e){} dom.setText===before", "true");
}

/* 7k slice2 RED: attachShadow mirrors into light DOM so pv_build paints it. */
static void test_shadow_mirror_append(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var h=document.createElement('div'); document.body.appendChild(h);"
              "var sr=h.attachShadow({mode:'open'});"
              "var c=document.createElement('span'); c.textContent='hi'; sr.appendChild(c);"
              "h.firstChild===c && sr.host===h && h.shadowRoot===sr && h.textContent", "hi");
}

static void test_shadow_mirror_inner_html(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var h=document.createElement('div'); document.body.appendChild(h);"
              "var sr=h.attachShadow({mode:'open'}); sr.innerHTML='<b>bold</b>';"
              "h.textContent", "bold");
}

/* Lit renders with shadowRoot.insertBefore(importNode(template.content), marker): a fragment
 * argument must expand into the root's children (and mirror into the host), for insertBefore
 * with and without a reference node, and for appendChild. */
static void test_shadow_insert_fragment(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var h=document.createElement('div'); document.body.appendChild(h);"
              "var sr=h.attachShadow({mode:'open'});"
              "var t=document.createElement('template'); t.innerHTML='<p class=a>x</p><label>y</label>';"
              "sr.insertBefore(document.importNode(t.content,true),null);"
              "sr.querySelector('label')!==null && sr.childNodes.length===2 && h.textContent", "xy");
    EXPECT(f, "var h=document.createElement('div'); document.body.appendChild(h);"
              "var sr=h.attachShadow({mode:'open'}); var m=document.createComment('m'); sr.appendChild(m);"
              "var t=document.createElement('template'); t.innerHTML='<i>1</i><i>2</i>';"
              "sr.insertBefore(document.importNode(t.content,true),m);"
              "sr.childNodes.length===3 && sr.firstChild.nodeName==='I' && sr.lastChild===m && h.textContent", "12");
    EXPECT(f, "var h=document.createElement('div'); document.body.appendChild(h);"
              "var sr=h.attachShadow({mode:'open'});"
              "var t=document.createElement('template'); t.innerHTML='<b>z</b>';"
              "sr.appendChild(document.importNode(t.content,true));"
              "sr.querySelector('b')!==null && h.textContent", "z");
    /* Lit's ChildPart: marker.parentNode is the ROOT, and inserting through it lands in the root */
    EXPECT(f, "var h=document.createElement('div'); document.body.appendChild(h);"
              "var sr=h.attachShadow({mode:'open'}); var m=document.createComment(''); sr.insertBefore(m,null);"
              "var d=document.createElement('div'); sr.appendChild(d);"
              "var t=document.createElement('template'); t.innerHTML='<label>y</label>';"
              "m.parentNode.insertBefore(document.importNode(t.content,true),null);"
              "m.parentNode===sr && d.parentNode===sr && d.parentElement===null && sr.querySelector('label')!==null"
              " && h.parentNode===document.body && d.getRootNode()===sr", "true");
    EXPECT(f, "var fr=document.createDocumentFragment(); var a=document.createElement('p'); fr.appendChild(a);"
              "var g=document.createDocumentFragment(); var b=document.createElement('p'); g.appendChild(b);"
              "g.insertBefore(fr,b); g.childNodes.length===2 && g.firstChild===a && fr.childNodes.length===0", "true");
}

/* CEReactions: a custom element inserted into a shadow root is upgraded (and connected) before
 * the insertion call returns, exactly as in the light tree; Lit reads methods off such children
 * in firstUpdated, right after the render. */
static void test_shadow_insert_upgrades_custom_elements(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "class XH extends HTMLElement{ assoc(){return 1;} connectedCallback(){ window.__cc=(window.__cc||0)+1; } }"
              "customElements.define('x-h',XH);"
              "var h=document.createElement('div'); document.body.appendChild(h);"
              "var sr=h.attachShadow({mode:'open'});"
              "var t=document.createElement('template'); t.innerHTML='<div><x-h></x-h></div>';"
              "sr.appendChild(document.importNode(t.content,true));"
              "var x=sr.querySelector('x-h'); typeof x.assoc+','+window.__cc", "function,1");
}

/* <slot>.assignedNodes/assignedElements: the host's light children (never the shadow's own
 * top-level nodes), by slot name; Lit components read them in firstUpdated. */
static void test_slot_assigned_nodes(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var h=document.createElement('div'); document.body.appendChild(h);"
              "var a=document.createElement('b'); var b=document.createElement('i'); b.setAttribute('slot','x');"
              "h.appendChild(a); h.appendChild(b); h.appendChild(document.createTextNode('t'));"
              "var sr=h.attachShadow({mode:'open'});"
              "var s1=document.createElement('slot'); var s2=document.createElement('slot'); s2.setAttribute('name','x');"
              "sr.appendChild(s1); sr.appendChild(s2);"
              "[s1.assignedNodes().length, s1.assignedElements().length, s1.assignedElements()[0]===a,"
              " s2.assignedNodes()[0]===b, s2.assignedElements().length, document.createElement('slot').assignedNodes().length].join()",
           "2,1,true,true,1,0");
}

/* matchMedia evaluates for real against the normalized 1920x1080 desktop
 * identity (the same one innerWidth and the CSS viewport units use); identity
 * signals are always normalized (light, no-preference, hover, fine). Unknown
 * features and junk are false, never a throw. */
static void test_match_media_normalized_viewport(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "matchMedia('(min-width: 768px)').matches", "true");
    EXPECT(f, "matchMedia('(min-width: 48em)').matches", "true");
    EXPECT(f, "matchMedia('(min-width: 2000px)').matches", "false");
    EXPECT(f, "matchMedia('(max-width: 767px)').matches", "false");
    EXPECT(f, "matchMedia('(max-width: 1920px)').matches", "true");
    EXPECT(f, "matchMedia('(min-height: 1080px)').matches", "true");
    EXPECT(f, "matchMedia('(orientation: landscape)').matches", "true");
    EXPECT(f, "matchMedia('(orientation: portrait)').matches", "false");
    EXPECT(f, "matchMedia('screen').matches", "true");
    EXPECT(f, "matchMedia('print').matches", "false");
    EXPECT(f, "matchMedia('screen and (min-width: 600px)').matches", "true");
    EXPECT(f, "matchMedia('(min-width: 600px) and (max-width: 800px)').matches", "false");
    EXPECT(f, "matchMedia('(max-width: 500px), (min-width: 1000px)').matches", "true");
    EXPECT(f, "matchMedia('not print').matches", "true");
    EXPECT(f, "matchMedia('(prefers-color-scheme: dark)').matches", "false");
    EXPECT(f, "matchMedia('(prefers-color-scheme: light)').matches", "true");
    EXPECT(f, "matchMedia('(prefers-reduced-motion: reduce)').matches", "false");
    EXPECT(f, "matchMedia('(hover: hover)').matches", "true");
    EXPECT(f, "matchMedia('(pointer: fine)').matches", "true");
    EXPECT(f, "matchMedia('(pointer: coarse)').matches", "false");
    EXPECT(f, "matchMedia('(min-width: garbage)').matches", "false");
    EXPECT(f, "matchMedia('garbage !!').matches", "false");
    EXPECT(f, "typeof matchMedia('(min-width: 1px)').addEventListener", "function");
}

/* Document node identity: jQuery/Sizzle's setDocument binds its internal document
 * reference only when 9===doc.nodeType && doc.documentElement; without nodeType:9
 * that reference stayed undefined and doc.createElement() threw, aborting the whole
 * library bundle (DuckDuckGo's l.js "cannot read property createElement of
 * undefined"). This locks the contract that unblocked it. */
static void test_document_node_identity(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "document.nodeType", "9");
    EXPECT(f, "document.DOCUMENT_NODE", "9");
    EXPECT(f, "document.nodeName", "#document");
    EXPECT(f, "document.defaultView === window", "true");
    EXPECT(f, "document.documentElement !== null", "true");
    EXPECT(f, "document.documentElement.nodeType", "1");
}

/* element.attributes as a NamedNodeMap-ish view: jQuery's event-bubbling feature
 * detection reads f.attributes['on'+type].expando on a freshly-built element; a
 * missing 'attributes' threw "cannot read property 'onsubmit' of undefined" and
 * aborted the bundle. Named + indexed access, length and getAttributeNames() are
 * backed by the sealed dom methods (this element's own attributes only). */
static void test_element_attributes_named_node_map(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var e=document.createElement('div'); e.setAttribute('onsubmit','t');"
              "e.attributes['onsubmit'].value", "t");
    EXPECT(f, "var e=document.createElement('div'); e.setAttribute('onsubmit','t');"
              "e.attributes['onsubmit'].expando===undefined", "true");
    EXPECT(f, "var e=document.createElement('div'); e.attributes['nope']===undefined", "true");
    EXPECT(f, "var e=document.createElement('a'); e.setAttribute('href','/x');"
              "e.setAttribute('rel','nofollow'); e.attributes.length", "2");
    EXPECT(f, "var e=document.createElement('a'); e.setAttribute('data-x','1');"
              "e.getAttributeNames().indexOf('data-x')>=0", "true");
    EXPECT(f, "var e=document.createElement('a'); e.setAttribute('id','k');"
              "e.attributes[0].name", "id");
}

/* Intl stub: QuickJS-ng builds without ICU, so Intl is otherwise undefined and any
 * locale-aware script (DuckDuckGo's wplv.js: "Intl is not defined") dies. The stub
 * is identity-neutral (fixed en-US-ish behaviour, no real locale/timezone leak). */
static void test_intl_stub_does_not_throw(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof Intl", "object");
    EXPECT(f, "typeof new Intl.NumberFormat().format", "function");
    EXPECT(f, "typeof new Intl.DateTimeFormat('en-US').format(0)", "string");
    EXPECT(f, "new Intl.Collator().compare('a','b')", "-1");
    EXPECT(f, "new Intl.PluralRules().select(1)", "one");
    EXPECT(f, "new Intl.ListFormat().format(['a','b'])", "a, b");
    EXPECT(f, "Intl.NumberFormat('en-US').resolvedOptions().locale", "en-US");
}

/* WHATWG URL: identity-safe, pure string parsing (no network/IO). This was
 * Slashdot's first JS error (ReferenceError: URL is not defined). */
static void test_url_constructor_parses_components(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof URL", "function");
    EXPECT(f, "new URL('https://a.b.com:8443/p/q?x=1&y=2#frag').protocol", "https:");
    EXPECT(f, "new URL('https://a.b.com:8443/p/q?x=1&y=2#frag').hostname", "a.b.com");
    EXPECT(f, "new URL('https://a.b.com:8443/p/q?x=1&y=2#frag').host", "a.b.com:8443");
    EXPECT(f, "new URL('https://a.b.com:8443/p/q?x=1&y=2#frag').port", "8443");
    EXPECT(f, "new URL('https://a.b.com/p/q?x=1&y=2#frag').pathname", "/p/q");
    EXPECT(f, "new URL('https://a.b.com/p?x=1&y=2#frag').search", "?x=1&y=2");
    EXPECT(f, "new URL('https://a.b.com/p?x=1#frag').hash", "#frag");
    EXPECT(f, "new URL('https://a.b.com/p').origin", "https://a.b.com");
    /* A bare path (no host) with no default host defaults to root pathname. */
    EXPECT(f, "new URL('/foo/bar', 'https://h.com/x/y').href",
              "https://h.com/foo/bar");
    EXPECT(f, "new URL('sub/page?z=9', 'https://h.com/a/b').pathname", "/a/sub/page");
    /* searchParams is a live view; toString re-serializes. */
    EXPECT(f, "new URL('https://h.com/?a=1&b=2').searchParams.get('b')", "2");
    /* Relative with no base throws TypeError (WHATWG). */
    EXPECT(f, "var t='ok'; try{ new URL('not a url'); t='no-throw'; }"
              "catch(e){ t=e.constructor.name; } t", "TypeError");
}

/* WHATWG URLSearchParams: identity-safe query parsing/encoding. */
static void test_url_search_params(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof URLSearchParams", "function");
    EXPECT(f, "new URLSearchParams('a=1&b=2&a=3').get('a')", "1");
    EXPECT(f, "new URLSearchParams('a=1&b=2&a=3').getAll('a').join(',')", "1,3");
    EXPECT(f, "new URLSearchParams('?a=1&b=2').has('b')", "true");
    EXPECT(f, "new URLSearchParams('a=1').has('z')", "false");
    /* '+' decodes to space; percent-encoding round-trips. */
    EXPECT(f, "new URLSearchParams('q=hello+world').get('q')", "hello world");
    EXPECT(f, "new URLSearchParams('q=a%20b%26c').get('q')", "a b&c");
    /* Mutation + serialization. */
    EXPECT(f, "var p=new URLSearchParams('a=1'); p.append('a','2'); p.toString()",
              "a=1&a=2");
    EXPECT(f, "var p=new URLSearchParams('a=1&b=2'); p.set('a','9'); p.toString()",
              "a=9&b=2");
    EXPECT(f, "var p=new URLSearchParams('a=1&b=2&c=3'); p.delete('b'); p.toString()",
              "a=1&c=3");
    EXPECT(f, "new URLSearchParams('x y=1&z=q r').toString()", "x+y=1&z=q+r");
    /* Object and array-of-pairs init. */
    EXPECT(f, "new URLSearchParams({a:'1',b:'2'}).toString()", "a=1&b=2");
    EXPECT(f, "new URLSearchParams([['a','1'],['b','2']]).toString()", "a=1&b=2");
    /* Iterable. */
    EXPECT(f, "var o=''; for(var k of new URLSearchParams('a=1&b=2').keys()) o+=k; o", "ab");
}

static void test_settimeout_chains_across_rounds(void **state) {
    fixture *f = (fixture *)*state;
    /* A timer that schedules another timer runs in a later pump round. */
    EXPECT(f, "var n=0; setTimeout(function(){ n++; setTimeout(function(){ n++; }); });"
              "__fireDeferred(); n", "2");
}

static void test_document_title_set_reflects_in_tree(void **state) {
    fixture *f = (fixture *)*state;
    js_result r;
    assert_int_equal(run(f, "document.title='Live'; document.title", &r), JS_OK);
    assert_non_null(r.value);
    assert_string_equal(r.value, "Live");
    js_result_free(&r);
    /* The native tree reflects the JS mutation. */
    size_t len = 0;
    const char *t = dom_document_title(f->idx, &len);
    assert_non_null(t);
    assert_string_equal(t, "Live");
}

static void test_set_text_content_reflects_in_tree(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "document.getElementById('go').textContent='Done';"
              "document.getElementById('go').textContent", "Done");
    dom_node_id go = dom_get_element_by_id(f->idx, "go");
    size_t len = 0;
    const char *t = dom_text_content(f->idx, go, &len);
    assert_non_null(t);
    assert_string_equal(t, "Done");
}

static void test_set_text_content_detach_is_memory_safe(void **state) {
    fixture *f = (fixture *)*state;
    /* Replacing #main's content detaches its <p>/<button> children. Reading a
     * detached child via its still-valid handle must not crash (no UAF). */
    js_result r;
    assert_int_equal(run(f,
        "var g=document.getElementById('go');"
        "document.getElementById('main').textContent='X';"
        "g.tagName+','+(document.getElementById('go')===null)", &r), JS_OK);
    assert_non_null(r.value);
    /* 'go' is detached but alive: the reference taken before reads safely, while the document
     * itself no longer finds it (getElementById only answers with attached elements). */
    assert_string_equal(r.value, "BUTTON,true");
    js_result_free(&r);
    EXPECT(f, "document.getElementById('main').textContent", "X");
}

static void test_document_is_not_io(void **state) {
    fixture *f = (fixture *)*state;
    /* The shim adds no I/O surface; console is a no-op, window is the global. */
    EXPECT(f, "typeof window + (window===globalThis)", "objecttrue");
    EXPECT(f, "typeof XMLHttpRequest + typeof fetch", "undefinedundefined");
}

/* --- live DOM construction (Hito 20c) --- */

static void test_create_append_renders_in_tree(void **state) {
    fixture *f = (fixture *)*state;
    /* createElement + appendChild + textContent builds new content the tree shows. */
    js_result r;
    assert_int_equal(run(f,
        "var s=document.createElement('span'); s.textContent='built';"
        "document.getElementById('main').appendChild(s);"
        "document.getElementById('main').textContent.indexOf('built')>=0", &r), JS_OK);
    assert_non_null(r.value);
    assert_string_equal(r.value, "true");
    js_result_free(&r);
    /* C side: a <span> now exists and #main contains "built". */
    dom_node_id span[4];
    assert_true(dom_get_by_tag(f->idx, "span", span, 4) >= 1);
}

static void test_set_attribute_makes_queryable(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f,
        "var d=document.createElement('div'); d.id='made'; d.className='x y';"
        "document.getElementById('main').appendChild(d);"
        "document.getElementById('made')!==null", "true");
    assert_int_not_equal(dom_get_element_by_id(f->idx, "made"), DOM_NODE_NONE);
}

/* Element-wrapper completeness: dataset / hasAttribute / removeAttribute / src /
 * href -- the missing members that made google.com's startup JS throw. Each idiom
 * below is exactly the shape that previously threw (see Hito 24 FB-error fixes). */
static void test_element_dataset_via_proxy(void **state) {
    fixture *f = (fixture *)*state;
    /* el.dataset.fooBar maps to the data-foo-bar attribute; missing => undefined. */
    EXPECT(f,
        "var e=document.getElementById('go'); e.setAttribute('data-foo-bar','hi');"
        "e.dataset.fooBar + '/' + (e.dataset.nope===undefined)", "hi/true");
    /* The google idiom b.dataset.ved on an element without it must not throw. */
    EXPECT(f, "(document.getElementById('main').dataset.ved)||'none'", "none");
    /* writes round-trip back to the attribute */
    EXPECT(f,
        "var e=document.getElementById('main'); e.dataset.testKey='1';"
        "e.getAttribute('data-test-key')", "1");
}

static void test_element_has_attribute(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "''+document.getElementById('main').hasAttribute('class')", "true");
    EXPECT(f, "''+document.getElementById('main').hasAttribute('data-noaft')", "false");
}

static void test_element_remove_attribute(void **state) {
    fixture *f = (fixture *)*state;
    /* removeAttribute is real (native dom_remove_attribute): the attribute is gone. */
    EXPECT(f,
        "var e=document.getElementById('main'); e.removeAttribute('class');"
        "e.getAttribute('class')===null", "true");
    /* and it must not throw on an absent attribute */
    EXPECT(f, "document.getElementById('go').removeAttribute('zzz'); 'ok'", "ok");
}

static void test_element_src_href_are_strings(void **state) {
    fixture *f = (fixture *)*state;
    /* .src/.href read '' when absent so d.src.substring(...) never hits undefined. */
    EXPECT(f, "document.getElementById('go').src.substring(0,5)", "");
    EXPECT(f, "var e=document.getElementById('go'); e.src='http://x/y'; e.src", "http://x/y");
    EXPECT(f, "document.getElementById('go').href", "");
}

static void test_append_cycle_is_rejected(void **state) {
    fixture *f = (fixture *)*state;
    /* Appending an ancestor under its descendant must be a no-op (no crash/loop). */
    EXPECT(f,
        "document.getElementById('go').appendChild(document.getElementById('main'));"
        "dom.parent(dom.getElementById('main'))!==dom.getElementById('go')", "true");
}

static void test_onload_runs_and_mutates(void **state) {
    fixture *f = (fixture *)*state;
    /* A handler registered for load runs only when __fireDeferred() pumps it. */
    js_result r;
    assert_int_equal(run(f,
        "window.onload=function(){ document.title='loaded'; };"
        "var before=document.title; __fireDeferred();"
        "before+'/'+document.title", &r), JS_OK);
    assert_non_null(r.value);
    assert_string_equal(r.value, "T/loaded");
    js_result_free(&r);
}

static void test_settimeout_flushed_by_pump(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f,
        "setTimeout(function(){ document.getElementById('go').textContent='timed'; });"
        "var b=document.getElementById('go').textContent; __fireDeferred();"
        "b+'/'+document.getElementById('go').textContent", "Go/timed");
}

static void test_inner_html_builds_and_queryable(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f,
        "document.getElementById('main').innerHTML='<p id=\"ih\">hi</p>';"
        "document.getElementById('ih').textContent", "hi");
    dom_node_id ih = dom_get_element_by_id(f->idx, "ih");
    assert_int_not_equal(ih, DOM_NODE_NONE);
}

/* innerHTML GETTER (2026-07-11): serializes the node's children back to markup. */
static void test_inner_html_getter_serializes(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f,
        "document.getElementById('main').innerHTML='<p id=\"gh\">hi</p>';"
        "document.getElementById('main').innerHTML", "<p id=\"gh\">hi</p>");
    /* a text-only child serializes as its text */
    EXPECT(f, "document.getElementById('gh').innerHTML", "hi");
}

/* Identity-safe ambient globals: present (no throws) but leak nothing. */
static void test_storage_is_ephemeral(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "localStorage.setItem('k','v'); localStorage.getItem('k')", "v");
    EXPECT(f, "localStorage.getItem('absent')", "null");
    EXPECT(f, "sessionStorage.setItem('a','1'); sessionStorage.length", "1");
}

static void test_cookie_and_referrer_leak_nothing(void **state) {
    fixture *f = (fixture *)*state;
    /* Default (untrusted host, jar disabled): cookie set is a no-op; get is always
     * empty; referrer empty; the parent reads nothing back. */
    EXPECT(f, "document.cookie='track=1'; document.cookie", "");
    EXPECT(f, "document.referrer", "");
    char buf[64];
    assert_int_equal(jd_get_cookies(f->ctx, buf, sizeof buf), 0);
    assert_string_equal(buf, "");
}

/* Trusted host (allow.conf AND js.conf): the parent enables + seeds the in-memory
 * session cookie jar via jd_set_cookies, so consent/session JS can read and set
 * document.cookie; the parent folds the result back via jd_get_cookies. Ephemeral --
 * never persisted (process-lifetime only). */
static void test_cookie_jar_enabled_for_trusted_host(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jd_set_cookies(f->ctx, "sid=abc; theme=dark"), JD_OK);
    /* seeded pairs are visible */
    EXPECT(f, "document.cookie", "sid=abc; theme=dark");
    /* a page assignment adds one pair, ignoring attributes (path/SameSite) */
    EXPECT(f, "document.cookie='pref=1; path=/; SameSite=Lax';"
              "document.cookie.indexOf('pref=1')>=0", "true");
    /* assignment updates an existing name */
    EXPECT(f, "document.cookie='sid=xyz'; document.cookie.indexOf('sid=xyz')>=0", "true");
    /* an expiry in the past deletes the cookie */
    EXPECT(f, "document.cookie='theme=dark; expires=Thu, 01 Jan 1970 00:00:00 GMT';"
              "document.cookie.indexOf('theme=')>=0", "false");
    /* max-age<=0 deletes too */
    EXPECT(f, "document.cookie='pref=1; max-age=0';"
              "document.cookie.indexOf('pref=')>=0", "false");
    /* the parent reads the live jar back to fold into its network jar */
    char buf[256];
    int n = jd_get_cookies(f->ctx, buf, sizeof buf);
    assert_true(n > 0);
    assert_non_null(strstr(buf, "sid=xyz"));
    assert_null(strstr(buf, "theme="));
}

static void test_ambient_apis_do_not_throw(void **state) {
    fixture *f = (fixture *)*state;
    /* history/location stubs let detection scripts run without ReferenceErrors. */
    EXPECT(f,
        "history.pushState({},'',''); location.assign('x'); location.replace('y');"
        "typeof history.pushState + typeof location.protocol", "functionstring");
}

/* --- real location + JS navigation capture (Hito 20e parte 1) --- */

/* Installs a real https location on the fixture context from url. */
static void set_https_location(fixture *f, const char *url) {
    url_parts parts;
    assert_int_equal(url_split(url, &parts), URL_OK);
    assert_int_equal(jd_set_location(f->ctx, url, &parts), JD_OK);
}

static void test_location_reads_real_components(void **state) {
    fixture *f = (fixture *)*state;
    set_https_location(f, "https://example.com:8443/p/q?x=1#f");
    EXPECT(f, "location.href", "https://example.com:8443/p/q?x=1#f");
    EXPECT(f, "location.protocol", "https:");
    EXPECT(f, "location.host", "example.com:8443");
    EXPECT(f, "location.hostname", "example.com");
    EXPECT(f, "location.port", "8443");
    EXPECT(f, "location.pathname", "/p/q");
    EXPECT(f, "location.search", "?x=1");
    EXPECT(f, "location.hash", "#f");
    EXPECT(f, "location.origin", "https://example.com:8443");
    /* document.location / document.URL mirror it. */
    EXPECT(f, "document.location.hostname", "example.com");
    EXPECT(f, "document.URL", "https://example.com:8443/p/q?x=1#f");
}

static void test_location_pathname_defaults_slash(void **state) {
    fixture *f = (fixture *)*state;
    set_https_location(f, "https://bare.test");
    EXPECT(f, "location.pathname", "/");   /* empty path presented as "/" */
    EXPECT(f, "location.search", "");
    EXPECT(f, "location.port", "");
}

static void test_location_href_set_captures_raw(void **state) {
    fixture *f = (fixture *)*state;
    set_https_location(f, "https://example.com/a/b");
    js_result r;
    assert_int_equal(run(f, "location.href='/next';", &r), JS_OK);
    js_result_free(&r);
    char buf[256]; int replace = 7;
    assert_int_equal(jd_take_nav_request(f->ctx, buf, sizeof buf, &replace), 1);
    assert_string_equal(buf, "/next");   /* RAW, unresolved: the parent gates it */
    assert_int_equal(replace, 0);
    /* taking it clears it: a second take reports none. */
    assert_int_equal(jd_take_nav_request(f->ctx, buf, sizeof buf, &replace), 0);
}

static void test_location_replace_sets_replace_flag(void **state) {
    fixture *f = (fixture *)*state;
    set_https_location(f, "https://example.com/");
    js_result r;
    assert_int_equal(run(f, "location.replace('https://other.test/x');", &r), JS_OK);
    js_result_free(&r);
    char buf[256]; int replace = 0;
    assert_int_equal(jd_take_nav_request(f->ctx, buf, sizeof buf, &replace), 1);
    assert_string_equal(buf, "https://other.test/x");
    assert_int_equal(replace, 1);
}

static void test_location_assign_and_window_last_wins(void **state) {
    fixture *f = (fixture *)*state;
    set_https_location(f, "https://example.com/");
    js_result r;
    assert_int_equal(run(f, "location.assign('first'); window.location='second';", &r), JS_OK);
    js_result_free(&r);
    char buf[256]; int replace = 1;
    assert_int_equal(jd_take_nav_request(f->ctx, buf, sizeof buf, &replace), 1);
    assert_string_equal(buf, "second");  /* last assignment wins */
    assert_int_equal(replace, 0);
}

static void test_no_nav_request_when_idle(void **state) {
    fixture *f = (fixture *)*state;
    set_https_location(f, "https://example.com/");
    char buf[256]; int replace = 9;
    assert_int_equal(jd_take_nav_request(f->ctx, buf, sizeof buf, &replace), 0);
}

/* A local (file) page has no https parts but still captures navigation requests,
 * so the parent can resolve them against the file base. */
static void test_local_page_captures_nav(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jd_set_location(f->ctx, "file:///docs/index.html", NULL), JD_OK);
    EXPECT(f, "location.href", "file:///docs/index.html");
    js_result r;
    assert_int_equal(run(f, "location.href='sub.html';", &r), JS_OK);
    js_result_free(&r);
    char buf[256]; int replace = 0;
    assert_int_equal(jd_take_nav_request(f->ctx, buf, sizeof buf, &replace), 1);
    assert_string_equal(buf, "sub.html");
}

static void test_set_location_null_ctx(void **state) {
    (void)state;
    char buf[8]; int replace = 0;
    assert_int_equal(jd_set_location(NULL, "https://x", NULL), JD_ERR_NULL_ARG);
    assert_int_equal(jd_take_nav_request(NULL, buf, sizeof buf, &replace), 0);
}

/* --- capturing console (Freebug) --- */

/* Builds a fresh context with dom + capturing console wired to *log. */
static void console_fixture(hp_document **doc, dom_index **idx, js_context **ctx,
                            fb_buffer *log) {
    assert_int_equal(hp_parse(HTML, sizeof HTML - 1, NULL, doc), HP_OK);
    assert_int_equal(dom_build(*doc, idx), DOM_OK);
    assert_int_equal(js_context_new(NULL, ctx), JS_OK);
    /* The opaque must outlive the context (jd_install contract); a stack local here
     * dangled as soon as this helper returned. */
    static jd_opaque op;
    assert_int_equal(jd_install(*ctx, *idx, &op), JD_OK);
    fb_buffer_init(log);
    assert_int_equal(jd_install_console(*ctx, log), JD_OK);
}

static void console_teardown(hp_document *doc, dom_index *idx, js_context *ctx,
                             fb_buffer *log) {
    fb_buffer_free(log);
    js_context_free(ctx);
    dom_free(idx);
    hp_document_free(doc);
}

/* console.error(err) prints the error, not "{}" (JSON of an Error has no own
 * enumerable fields); an element prints as <tag#id>. */
static void test_console_formats_errors_and_elements(void **state) {
    (void)state;
    hp_document *doc; dom_index *idx; js_context *ctx; fb_buffer log;
    console_fixture(&doc, &idx, &ctx, &log);
    const char *src =
        "console.error('Error rendering page: ', new TypeError('boom'));"
        "console.log(document.getElementById('go'), {a:1});";
    js_result r; memset(&r, 0, sizeof r);
    assert_int_equal(js_eval(ctx, src, strlen(src), &r), JS_OK);
    js_result_free(&r);
    assert_int_equal(fb_buffer_count(&log), 2);
    assert_non_null(strstr(fb_buffer_at(&log, 0)->text, "TypeError: boom"));
    assert_string_equal(fb_buffer_at(&log, 1)->text, "<button#go> {\"a\":1}");
    console_teardown(doc, idx, ctx, &log);
}

static void test_console_captures_levels(void **state) {
    (void)state;
    hp_document *doc; dom_index *idx; js_context *ctx; fb_buffer log;
    console_fixture(&doc, &idx, &ctx, &log);

    const char *src =
        "console.log('a', 1, true);"
        "console.info('i');"
        "console.warn('w');"
        "console.error('e');"
        "console.debug('d');";
    js_result r; memset(&r, 0, sizeof r);
    assert_int_equal(js_eval(ctx, src, strlen(src), &r), JS_OK);
    js_result_free(&r);

    assert_int_equal((int)fb_buffer_count(&log), 5);
    assert_int_equal(fb_buffer_at(&log, 0)->level, FB_LOG);
    assert_string_equal(fb_buffer_at(&log, 0)->text, "a 1 true"); /* space-joined args */
    assert_int_equal(fb_buffer_at(&log, 1)->level, FB_INFO);
    assert_string_equal(fb_buffer_at(&log, 1)->text, "i");
    assert_int_equal(fb_buffer_at(&log, 2)->level, FB_WARN);
    assert_int_equal(fb_buffer_at(&log, 3)->level, FB_ERROR);
    assert_int_equal(fb_buffer_at(&log, 4)->level, FB_DEBUG);

    console_teardown(doc, idx, ctx, &log);
}

static void test_console_object_and_throwing_tostring(void **state) {
    (void)state;
    hp_document *doc; dom_index *idx; js_context *ctx; fb_buffer log;
    console_fixture(&doc, &idx, &ctx, &log);

    const char *src =
        "console.log({});"                                  /* -> [object Object] */
        "console.log({toString:function(){throw 'x';}});";  /* swallowed */
    js_result r; memset(&r, 0, sizeof r);
    /* The throwing toString must NOT propagate as an eval error. */
    assert_int_equal(js_eval(ctx, src, strlen(src), &r), JS_OK);
    js_result_free(&r);

    assert_int_equal((int)fb_buffer_count(&log), 2);
    assert_string_equal(fb_buffer_at(&log, 0)->text, "{}");
    /* toString-throwing object: JSON.stringify succeeds (enumerates own props,
     * does NOT call toString) → "{}". */
    assert_string_equal(fb_buffer_at(&log, 1)->text, "{}");

    console_teardown(doc, idx, ctx, &log);
}

/* console methods are plain writable properties (WebIDL namespace members): Sentry-style
 * instrumentation wraps console[level] and a read-only slot threw "'debug' is read-only". */
static void test_console_methods_are_writable(void **state) {
    (void)state;
    hp_document *doc; dom_index *idx; js_context *ctx; fb_buffer log;
    console_fixture(&doc, &idx, &ctx, &log);
    const char *src =
        "var o=console.debug; console.debug=function(){ o.apply(console,arguments); };"
        "'use strict'; console.debug('wrapped');";
    js_result r; memset(&r, 0, sizeof r);
    assert_int_equal(js_eval(ctx, src, strlen(src), &r), JS_OK);
    js_result_free(&r);
    assert_int_equal(fb_buffer_count(&log), 1);
    assert_non_null(strstr(fb_buffer_at(&log, 0)->text, "wrapped"));
    const char *st =
        "(function(){ 'use strict'; try{ console.info=function(){}; return 'ok'; }"
        "catch(e){ return e.message; } })()";
    memset(&r, 0, sizeof r);
    assert_int_equal(js_eval(ctx, st, strlen(st), &r), JS_OK);
    assert_string_equal(r.value, "ok");
    js_result_free(&r);
    console_teardown(doc, idx, ctx, &log);
}

/* An unhandled rejection with a DOMException names it ("SyntaxError: ...") in the console:
 * its stack alone has no header, so the cause was invisible in Freebug. */
static void test_unhandled_rejection_report_carries_the_message(void **state) {
    (void)state;
    hp_document *doc; dom_index *idx; js_context *ctx; fb_buffer log;
    console_fixture(&doc, &idx, &ctx, &log);
    const char *src = "Promise.reject(new DOMException('bad name here','SyntaxError')); 0";
    js_result r; memset(&r, 0, sizeof r);
    assert_int_equal(js_eval(ctx, src, strlen(src), &r), JS_OK);
    js_result_free(&r);
    js_pump_jobs(ctx, 64);
    int found = 0;
    for (size_t i = 0; i < fb_buffer_count(&log); i++)
        if (strstr(fb_buffer_at(&log, i)->text, "SyntaxError: bad name here")) found = 1;
    assert_int_equal(found, 1);
    console_teardown(doc, idx, ctx, &log);
}

static void test_console_null_buffer_is_noop(void **state) {
    (void)state;
    hp_document *doc; dom_index *idx; js_context *ctx;
    assert_int_equal(hp_parse(HTML, sizeof HTML - 1, NULL, &doc), HP_OK);
    assert_int_equal(dom_build(doc, &idx), DOM_OK);
    assert_int_equal(js_context_new(NULL, &ctx), JS_OK);
    jd_opaque op;
    assert_int_equal(jd_install(ctx, idx, &op), JD_OK);
    assert_int_equal(jd_install_console(ctx, NULL), JD_OK); /* silent */

    const char *src = "console.log('x'); console.error('y'); 42";
    js_result r; memset(&r, 0, sizeof r);
    assert_int_equal(js_eval(ctx, src, strlen(src), &r), JS_OK);
    assert_string_equal(r.value, "42"); /* runs fine, just captures nothing */
    js_result_free(&r);

    js_context_free(ctx);
    dom_free(idx);
    hp_document_free(doc);
}

static void test_console_null_ctx(void **state) {
    (void)state;
    fb_buffer log; fb_buffer_init(&log);
    assert_int_equal(jd_install_console(NULL, &log), JD_ERR_NULL_ARG);
    fb_buffer_free(&log);
}

/* --- generic events (Phase 1.1 dispatcher) --- */

static void test_event_add_event_listener_fires(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;

    const char *src =
        "var i = document.getElementsByTagName('input')[0];"
        "i.addEventListener('keydown', function(e){ i.value = e.key || 'no-key'; });"
        "i._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);

    assert_int_equal(jd_fire_event(f->ctx, h, "keydown", "Enter", 13, NULL), 1);
    EXPECT(f, "document.getElementsByTagName('input')[0].value", "Enter");
}

static void test_event_onkeydown_fires(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;

    const char *src =
        "var i = document.getElementsByTagName('input')[0];"
        "i.onkeydown = function(e){ i.value = e.keyCode + ':x'; };"
        "i._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);

    assert_int_equal(jd_fire_event(f->ctx, h, "keydown", "a", 65, NULL), 1);
    EXPECT(f, "document.getElementsByTagName('input')[0].value", "65:x");
}

static void test_event_input_handler_fires_with_value(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;

    const char *src =
        "var i = document.getElementsByTagName('input')[0];"
        "i.addEventListener('input', function(e){ i.dataset.lastVal = e.value || ''; });"
        "i._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);

    assert_int_equal(jd_fire_event(f->ctx, h, "input", NULL, 0, "hello"), 1);
    EXPECT(f, "document.getElementsByTagName('input')[0].dataset.lastVal", "hello");
}

static void test_event_prevent_default_suppresses(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;

    const char *src =
        "var i = document.getElementsByTagName('input')[0];"
        "i.addEventListener('keydown', function(e){ e.preventDefault(); });"
        "i._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);

    assert_int_equal(jd_fire_event(f->ctx, h, "keydown", "Enter", 13, NULL), 0);
}

static void test_event_no_handler_allows_default(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;

    assert_int_equal(jd_fire_event(f->ctx, (dom_node_id)1, "keydown", "x", 88, NULL), 1);
}

static void test_event_null_args(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;

    assert_int_equal(jd_fire_event(NULL, (dom_node_id)1, "keydown", "x", 88, NULL), 1);
    assert_int_equal(jd_fire_event(f->ctx, DOM_NODE_NONE, "keydown", "x", 88, NULL), 1);
    assert_int_equal(jd_fire_event(f->ctx, (dom_node_id)1, NULL, "x", 88, NULL), 1);
}

/* --- focus/blur/scroll events (Phase 1.3 dispatcher) --- */

/* Registers a focus listener via addEventListener and fires it. */
static void test_focus_add_event_listener_fires(void **state) {
    fixture *f = (fixture *)*state;
    const char *src =
        "var i = document.getElementsByTagName('input')[0];"
        "i.addEventListener('focus', function(e){"
        "  i.value = 'focused';"
        "}); i._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);
    assert_int_not_equal(jd_fire_event(f->ctx, h, "focus", NULL, 0, NULL), 0);
    EXPECT(f, "document.getElementsByTagName('input')[0].value", "focused");
}

/* Registers an onblur handler via property setter and fires it. */
static void test_blur_onblur_fires(void **state) {
    fixture *f = (fixture *)*state;
    const char *src =
        "var i = document.getElementsByTagName('input')[0];"
        "i.onblur = function(e){ i.value = 'lost'; };"
        "i._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);
    assert_int_not_equal(jd_fire_event(f->ctx, h, "blur", NULL, 0, NULL), 0);
    EXPECT(f, "document.getElementsByTagName('input')[0].value", "lost");
}

/* Registers a scroll listener via addEventListener and fires it. */
static void test_scroll_add_event_listener_fires(void **state) {
    fixture *f = (fixture *)*state;
    const char *src =
        "var p = document.getElementById('main');"
        "p.addEventListener('scroll', function(e){"
        "  p.textContent = 'scrolled';"
        "}); p._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);
    assert_int_not_equal(jd_fire_event(f->ctx, h, "scroll", NULL, 0, NULL), 0);
    EXPECT(f, "document.getElementById('main').textContent", "scrolled");
}

/* Registers an onscroll handler via property setter and fires it. */
static void test_scroll_onscroll_fires(void **state) {
    fixture *f = (fixture *)*state;
    const char *src =
        "var p = document.getElementById('main');"
        "p.onscroll = function(e){ p.textContent = 's'; };"
        "p._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);
    assert_int_not_equal(jd_fire_event(f->ctx, h, "scroll", NULL, 0, NULL), 0);
    EXPECT(f, "document.getElementById('main').textContent", "s");
}

/* preventDefault on focus/blur/scroll. */
static void test_focus_blur_scroll_prevent_default(void **state) {
    fixture *f = (fixture *)*state;
    const char *src =
        "var i = document.getElementsByTagName('input')[0];"
        "i.addEventListener('focus', function(e){ e.preventDefault(); });"
        "i.addEventListener('blur', function(e){ e.preventDefault(); });"
        "i._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);
    assert_int_equal(jd_fire_event(f->ctx, h, "focus", NULL, 0, NULL), 0);
    assert_int_equal(jd_fire_event(f->ctx, h, "blur", NULL, 0, NULL), 0);

    /* scroll on a different element that has a scroll handler. */
    const char *src2 =
        "var p = document.getElementById('main');"
        "p.addEventListener('scroll', function(e){ e.preventDefault(); });"
        "p._h;";
    assert_int_equal(js_eval(f->ctx, src2, strlen(src2), &r), JS_OK);
    dom_node_id h2 = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h2, DOM_NODE_NONE);
    assert_int_equal(jd_fire_event(f->ctx, h2, "scroll", NULL, 0, NULL), 0);
}

/* No handler = default action allowed. */
static void test_focus_blur_scroll_no_handler_allows_default(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jd_fire_event(f->ctx, (dom_node_id)1, "focus", NULL, 0, NULL), 1);
    assert_int_equal(jd_fire_event(f->ctx, (dom_node_id)1, "blur", NULL, 0, NULL), 1);
    assert_int_equal(jd_fire_event(f->ctx, (dom_node_id)1, "scroll", NULL, 0, NULL), 1);
}

/* Null args. */
static void test_focus_blur_scroll_null_args(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jd_fire_event(NULL, (dom_node_id)1, "focus", NULL, 0, NULL), 1);
    assert_int_equal(jd_fire_event(f->ctx, DOM_NODE_NONE, "focus", NULL, 0, NULL), 1);
    assert_int_equal(jd_fire_event(f->ctx, (dom_node_id)1, NULL, NULL, 0, NULL), 1);
}

/* --- mouse events (Phase 1.2 dispatcher) --- */

/* Registers a mouseover listener via addEventListener and fires it. */
static void test_mouse_add_event_listener_fires(void **state) {
    fixture *f = (fixture *)*state;
    const char *src =
        "var p = document.getElementById('main');"
        "p.addEventListener('mouseover', function(e){"
        "  p.textContent = 'over';"
        "}); p._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);
    assert_int_not_equal(jd_fire_mouse_event(f->ctx, h, "mouseover", 100, 200, 0), 0);
    EXPECT(f, "document.getElementById('main').textContent", "over");
}

/* Registers an onmouseout handler via property setter and fires it. */
static void test_mouse_onmouseout_fires(void **state) {
    fixture *f = (fixture *)*state;
    const char *src =
        "var p = document.getElementById('main');"
        "p.onmouseout = function(e){ p.textContent = 'out'; };"
        "p._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);
    assert_int_not_equal(jd_fire_mouse_event(f->ctx, h, "mouseout", 150, 250, -1), 0);
    EXPECT(f, "document.getElementById('main').textContent", "out");
}

/* Fires a mousemove event with coordinates and verifies the handler sees them. */
static void test_mouse_mousemove_sees_coords(void **state) {
    fixture *f = (fixture *)*state;
    const char *src =
        "var p = document.getElementById('main');"
        "p.addEventListener('mousemove', function(e){"
        "  p.textContent = e.clientX + ',' + e.clientY;"
        "}); p._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);
    assert_int_not_equal(jd_fire_mouse_event(f->ctx, h, "mousemove", 42, 73, 0), 0);
    EXPECT(f, "document.getElementById('main').textContent", "42,73");
}

/* Fires on multiple mouse event types and verifies each triggers separately. */
static void test_mouse_multi_event_fires(void **state) {
    fixture *f = (fixture *)*state;
    const char *src =
        "var p = document.getElementById('main');"
        "var n = 0;"
        "p.addEventListener('mouseover', function(e){ n += 1; });"
        "p.addEventListener('mouseout', function(e){ n += 10; });"
        "p.addEventListener('mousemove', function(e){ n += 100; });"
        "p.addEventListener('mouseenter', function(e){ n += 1000; });"
        "p.addEventListener('mouseleave', function(e){ n += 10000; });"
        "p.addEventListener('wheel', function(e){ n += 100000; });"
        "p._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);

    /* fire events and check n via EXPECT */
    (void)jd_fire_mouse_event(f->ctx, h, "mouseover", 0, 0, 0);
    EXPECT(f, "n", "1");
    (void)jd_fire_mouse_event(f->ctx, h, "mouseout", 0, 0, 0);
    EXPECT(f, "n", "11");
    (void)jd_fire_mouse_event(f->ctx, h, "mousemove", 0, 0, 0);
    EXPECT(f, "n", "111");
    (void)jd_fire_mouse_event(f->ctx, h, "mouseenter", 0, 0, 0);
    EXPECT(f, "n", "1111");
    (void)jd_fire_mouse_event(f->ctx, h, "mouseleave", 0, 0, 0);
    EXPECT(f, "n", "11111");
    (void)jd_fire_mouse_event(f->ctx, h, "wheel", 0, 0, -1);
    EXPECT(f, "n", "111111");
}

/* preventDefault on a mouse event suppresses the default action. */
static void test_mouse_prevent_default_suppresses(void **state) {
    fixture *f = (fixture *)*state;
    const char *src =
        "var p = document.getElementById('main');"
        "p.addEventListener('mousedown', function(e){ e.preventDefault(); });"
        "p._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);
    int def = jd_fire_mouse_event(f->ctx, h, "mousedown", 10, 20, 0);
    assert_int_equal(def, 0);
}

/* No handler = default action allowed. */
static void test_mouse_no_handler_allows_default(void **state) {
    fixture *f = (fixture *)*state;
    int def = jd_fire_mouse_event(f->ctx, (dom_node_id)1, "mouseover", 5, 10, 0);
    assert_int_equal(def, 1);
}

/* Null arguments are fail-open. */
static void test_mouse_null_args(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jd_fire_mouse_event(NULL, (dom_node_id)1, "mouseover", 0, 0, 0), 1);
    assert_int_equal(jd_fire_mouse_event(f->ctx, DOM_NODE_NONE, "mouseover", 0, 0, 0), 1);
    assert_int_equal(jd_fire_mouse_event(f->ctx, (dom_node_id)1, NULL, 0, 0, 0), 1);
}

/* --- click events (Stage 4 dispatcher) --- */

static void test_click_install_null_args(void **state) {
    (void)state;
    assert_int_equal(jd_install_events(NULL, NULL), JD_ERR_NULL_ARG);
}

/* Registers a click listener on a paragraph and fires it from native code. */
static void test_click_add_event_listener_fires(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;
    jd_click_state *cs = jd_click_state_new();
    assert_non_null(cs);
    assert_int_equal(jd_install_events(f->ctx, cs), JD_OK);

    const char *src =
        "var p = document.getElementsByTagName('p')[0];"
        "p.addEventListener('click', function(e){ p.textContent = 'clicked'; });"
        "p._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);

    assert_int_equal(jd_fire_click(f->ctx, h), 1); /* default action allowed */
    EXPECT(f, "document.getElementsByTagName('p')[0].textContent", "clicked");

    jd_click_state_free(cs);
}

/* onclick property also registers a handler. */
static void test_click_onclick_fires(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;
    jd_click_state *cs = jd_click_state_new();
    assert_non_null(cs);
    assert_int_equal(jd_install_events(f->ctx, cs), JD_OK);

    const char *src =
        "var b = document.getElementById('go');"
        "b.onclick = function(e){ b.textContent = 'fired'; };"
        "b._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);

    assert_int_equal(jd_fire_click(f->ctx, h), 1);
    EXPECT(f, "document.getElementById('go').textContent", "fired");

    jd_click_state_free(cs);
}

/* preventDefault() stops the default action. */
static void test_click_prevent_default(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;
    jd_click_state *cs = jd_click_state_new();
    assert_non_null(cs);
    assert_int_equal(jd_install_events(f->ctx, cs), JD_OK);

    const char *src =
        "var b = document.getElementById('go');"
        "b.onclick = function(e){ e.preventDefault(); b.textContent = 'prevented'; };"
        "b._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);

    assert_int_equal(jd_fire_click(f->ctx, h), 0); /* default action cancelled */
    EXPECT(f, "document.getElementById('go').textContent", "prevented");

    jd_click_state_free(cs);
}

/* No handler registered => default action allowed, no mutation. */
static void test_click_no_handler_allows_default(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;
    jd_click_state *cs = jd_click_state_new();
    assert_non_null(cs);
    assert_int_equal(jd_install_events(f->ctx, cs), JD_OK);

    assert_int_equal(jd_fire_click(f->ctx, 9999), 1);
    jd_click_state_free(cs);
}

/* --- submit events --- */

/* Registers a submit listener via addEventListener and fires it. */
static void test_submit_add_event_listener_fires(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;

    const char *src =
        "var fm = document.getElementById('frm');"
        "fm.addEventListener('submit', function(e){ fm._submitted = true; });"
        "fm._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);

    assert_int_equal(jd_fire_submit(f->ctx, h), 1); /* default action allowed */
    EXPECT(f, "document.getElementById('frm')._submitted", "true");
}

/* onsubmit property also registers a handler. */
static void test_submit_onsubmit_fires(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;

    const char *src =
        "var fm = document.getElementById('frm');"
        "fm.onsubmit = function(e){ fm._submitted = true; };"
        "fm._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);

    assert_int_equal(jd_fire_submit(f->ctx, h), 1);
    EXPECT(f, "document.getElementById('frm')._submitted", "true");
}

/* preventDefault() stops the default action. */
static void test_submit_prevent_default(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;

    const char *src =
        "var fm = document.getElementById('frm');"
        "fm.onsubmit = function(e){ e.preventDefault(); fm._prevented = true; };"
        "fm._h;";
    js_result r;
    assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);

    assert_int_equal(jd_fire_submit(f->ctx, h), 0); /* default action cancelled */
    EXPECT(f, "document.getElementById('frm')._prevented", "true");
}

/* No handler registered => default action proceeds. */
static void test_submit_no_handler_allows_default(void **state) {
    (void)state;
    fixture *f = (fixture *)*state;

    assert_int_equal(jd_fire_submit(f->ctx, 9999), 1);
}

/* --- event propagation (spec/js_dom.md §7d) --- */

/* Runs src (which must end with an expression yielding a node handle) and returns it. */
static dom_node_id handle_after(fixture *f, const char *src) {
    js_result r;
    assert_int_equal(run(f, src, &r), JS_OK);
    assert_non_null(r.value);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_not_equal(h, DOM_NODE_NONE);
    return h;
}

/* A click on #go bubbles to its ancestor #main with target/currentTarget set. */
static void test_event_click_bubbles_to_ancestor(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "var L=[]; var m=document.getElementById('main'), g=document.getElementById('go');"
        "m.addEventListener('click', function(e){"
        "  L.push((e.target===g)+'/'+(e.currentTarget===m)+'/'+e.eventPhase); });"
        "g._h;");
    assert_int_equal(jd_fire_click(f->ctx, h), 1);
    EXPECT(f, "L.join(',')", "true/true/3");
}

/* Capture on document, then target, then bubble on #main, then window bubble. */
static void test_event_capture_target_bubble_order(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "var L=[]; var m=document.getElementById('main'), g=document.getElementById('go');"
        "window.addEventListener('click', function(){ L.push('wbub'); });"
        "m.addEventListener('click', function(){ L.push('bub'); });"
        "g.addEventListener('click', function(){ L.push('tgt'); });"
        "document.addEventListener('click', function(){ L.push('cap'); }, true);"
        "g._h;");
    assert_int_equal(jd_fire_click(f->ctx, h), 1);
    EXPECT(f, "L.join(',')", "cap,tgt,bub,wbub");
}

/* stopPropagation at the target keeps the ancestor from hearing it. */
static void test_event_stop_propagation(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "var L=[]; var m=document.getElementById('main'), g=document.getElementById('go');"
        "m.addEventListener('click', function(){ L.push('bub'); });"
        "g.addEventListener('click', function(e){ L.push('a'); e.stopPropagation(); });"
        "g.addEventListener('click', function(){ L.push('b'); });"
        "g._h;");
    assert_int_equal(jd_fire_click(f->ctx, h), 1);
    EXPECT(f, "L.join(',')", "a,b");
}

/* stopImmediatePropagation also skips the remaining listeners on the same node. */
static void test_event_stop_immediate_propagation(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "var L=[]; var g=document.getElementById('go');"
        "g.addEventListener('click', function(e){ L.push('a'); e.stopImmediatePropagation(); });"
        "g.addEventListener('click', function(){ L.push('b'); });"
        "g._h;");
    assert_int_equal(jd_fire_click(f->ctx, h), 1);
    EXPECT(f, "L.join(',')", "a");
}

/* Several click listeners on one node all run (the old registry kept only the last). */
static void test_event_multiple_click_listeners(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "var L=[]; var g=document.getElementById('go');"
        "var fa=function(){ L.push('a'); };"
        "g.addEventListener('click', fa); g.addEventListener('click', fa);"
        "g.addEventListener('click', function(){ L.push('b'); });"
        "g._h;");
    assert_int_equal(jd_fire_click(f->ctx, h), 1);
    EXPECT(f, "L.join(',')", "a,b");
}

/* removeEventListener removes exactly the (type, fn, capture) triple. */
static void test_event_remove_listener(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "var L=[]; var g=document.getElementById('go');"
        "var fa=function(){ L.push('a'); }, fb=function(){ L.push('b'); };"
        "g.addEventListener('click', fa); g.addEventListener('click', fb);"
        "g.addEventListener('click', fb, true);"
        "g.removeEventListener('click', fa); g.removeEventListener('click', fb, true);"
        "g._h;");
    assert_int_equal(jd_fire_click(f->ctx, h), 1);
    EXPECT(f, "L.join(',')", "b");
}

/* {once:true} fires a single time. */
static void test_event_once(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "var L=[]; var g=document.getElementById('go');"
        "g.addEventListener('click', function(){ L.push('x'); }, {once:true});"
        "g._h;");
    assert_int_equal(jd_fire_click(f->ctx, h), 1);
    assert_int_equal(jd_fire_click(f->ctx, h), 1);
    EXPECT(f, "L.join(',')", "x");
}

/* preventDefault in a DELEGATED listener (document) cancels the default action. */
static void test_event_delegated_prevent_default(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "document.addEventListener('click', function(e){"
        "  if (e.target.id==='go') e.preventDefault(); });"
        "document.getElementById('go')._h;");
    assert_int_equal(jd_fire_click(f->ctx, h), 0);
}

/* Submit bubbles to document (delegated form handling). */
static void test_event_submit_bubbles_to_document(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "var L=[]; document.addEventListener('submit', function(e){"
        "  L.push(e.target.id); e.preventDefault(); });"
        "document.getElementById('frm')._h;");
    assert_int_equal(jd_fire_submit(f->ctx, h), 0);
    EXPECT(f, "L.join(',')", "frm");
}

/* keydown from the engine bubbles with its key data; isTrusted, timeStamp 0. */
static void test_event_keydown_bubbles_with_data(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "var L=[]; document.getElementById('main').addEventListener('keydown', function(e){"
        "  L.push(e.key+'/'+e.keyCode+'/'+e.isTrusted+'/'+e.timeStamp); });"
        "document.getElementById('go')._h;");
    assert_int_equal(jd_fire_event(f->ctx, h, "keydown", "Enter", 13, NULL), 1);
    EXPECT(f, "L.join(',')", "Enter/13/true/0");
}

/* focus does not bubble, but an ancestor capture listener still sees it. */
static void test_event_focus_does_not_bubble(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "var L=[]; var m=document.getElementById('main');"
        "m.addEventListener('focus', function(){ L.push('bub'); });"
        "m.addEventListener('focus', function(){ L.push('cap'); }, true);"
        "document.getElementById('go')._h;");
    assert_int_equal(jd_fire_event(f->ctx, h, "focus", NULL, 0, NULL), 1);
    EXPECT(f, "L.join(',')", "cap");
}

/* The onclick slot keeps its position and is replaced (not appended) on re-set. */
static void test_event_handler_property_slot(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "var L=[]; var g=document.getElementById('go');"
        "g.onclick=function(){ L.push('on1'); };"
        "g.addEventListener('click', function(){ L.push('ael'); });"
        "g.onclick=function(){ L.push('on2'); };"
        "g._h;");
    assert_int_equal(jd_fire_click(f->ctx, h), 1);
    EXPECT(f, "L.join(',')", "on2,ael");
    EXPECT(f, "typeof document.getElementById('go').onclick", "function");
}

/* Script-created events dispatch through the same path; CustomEvent carries detail. */
static void test_event_script_dispatch_custom_event(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f,
        "var L=[]; var m=document.getElementById('main'), g=document.getElementById('go');"
        "m.addEventListener('ping', function(e){ L.push('m'+e.detail+e.isTrusted); });"
        "g.addEventListener('ping', function(e){ L.push('g'+e.detail); e.preventDefault(); });"
        "var r1=g.dispatchEvent(new CustomEvent('ping',{detail:5,bubbles:true,cancelable:true}));"
        "var r2=g.dispatchEvent(new CustomEvent('ping',{detail:6}));"
        "L.join(',')+'|'+r1+'|'+r2;",
        "g5,m5false,g6|false|true");
}

/* A throwing listener does not stop the next one. */
static void test_event_listener_exception_continues(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "var L=[]; var g=document.getElementById('go');"
        "g.addEventListener('click', function(){ throw new Error('boom'); });"
        "document.addEventListener('click', function(){ L.push('doc'); });"
        "g._h;");
    assert_int_equal(jd_fire_click(f->ctx, h), 1);
    EXPECT(f, "L.join(',')", "doc");
}

/* handleEvent objects are valid listeners. */
static void test_event_handle_event_object(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id h = handle_after(f,
        "var L=[]; var o={handleEvent:function(e){ L.push(e.type); }};"
        "document.getElementById('main').addEventListener('click', o);"
        "document.getElementById('go')._h;");
    assert_int_equal(jd_fire_click(f->ctx, h), 1);
    EXPECT(f, "L.join(',')", "click");
}

/* --- layout geometry (spec/js_geom.md) --- */

static dom_node_id geom_parent(void *ctx, dom_node_id n) {
    return dom_parent((const dom_index *)ctx, n);
}

static dom_node_id js_handle(fixture *f, const char *expr) {
    js_result r;
    assert_int_equal(run(f, expr, &r), JS_OK);
    assert_non_null(r.value);
    dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    return h;
}

/* Without a geometry table every measurement stays zero and the viewport stays
 * normalized: the anti-fingerprinting default for every untrusted host. */
static void test_geom_absent_is_zero(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var r=document.getElementById('go').getBoundingClientRect();"
              "[r.width,r.height,r.top,document.getElementById('go').offsetHeight,"
              "innerWidth,scrollY].join(',')", "0,0,0,0,1920,0");
}

static void test_geom_installed_is_real(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id go = js_handle(f, "document.getElementById('go')._h");
    dom_node_id p1 = js_handle(f, "document.getElementsByTagName('p')[0]._h");
    jg_table t;
    jg_init(&t);
    t.scroll_y = 40; t.view_w = 1000; t.view_h = 700; t.doc_w = 1000; t.doc_h = 3000;
    assert_int_equal(jg_add(&t, go, 10, 100, 200, 50), 0);
    assert_int_equal(jg_add(&t, p1, 0, 20, 300, 20), 0);
    assert_int_equal(jg_aggregate(&t, geom_parent, f->idx), 0);
    assert_int_equal(jd_set_geometry(f->ctx, &t), JD_OK);

    EXPECT(f, "var r=document.getElementById('go').getBoundingClientRect();"
              "[r.left,r.top,r.width,r.height,r.right,r.bottom,r.x,r.y].join(',')",
              "10,60,200,50,210,110,10,60");
    EXPECT(f, "var g=document.getElementById('go');"
              "[g.offsetLeft,g.offsetTop,g.offsetWidth,g.offsetHeight,g.clientWidth,"
              "g.scrollHeight,g.getClientRects().length].join(',')",
              "10,100,200,50,200,50,1");
    /* #main has no rect of its own: it measures the union of its descendants. */
    EXPECT(f, "var m=document.getElementById('main').getBoundingClientRect();"
              "[m.left,m.top,m.width,m.height].join(',')", "0,-20,300,130");
    EXPECT(f, "[innerWidth,innerHeight,scrollX,scrollY,pageYOffset,"
              "document.documentElement.clientWidth,document.documentElement.clientHeight,"
              "document.documentElement.scrollTop,document.body.scrollHeight].join(',')",
              "1000,700,0,40,40,1000,700,40,3000");
    /* An element the layout never produced (e.g. display:none) measures zero. */
    EXPECT(f, "document.getElementsByTagName('input')[0].getBoundingClientRect().width", "0");
    EXPECT(f, "JSON.stringify(document.getElementById('go').getBoundingClientRect().toJSON().height)",
              "50");

    /* Removing the table restores the untrusted default. */
    assert_int_equal(jd_set_geometry(f->ctx, NULL), JD_OK);
    EXPECT(f, "document.getElementById('go').getBoundingClientRect().width+','+innerWidth",
              "0,1920");
    jg_free(&t);
}

/* Freebug command-line API (spec/freebug_repl.md): $, $$, inspect, keys, values,
 * getEventListeners, monitorEvents exist ONLY after jd_install_repl_api (the REPL worker);
 * page scripts never see them, and a page's own `$` (jQuery) is never replaced. */
static void test_repl_api_is_repl_only_and_nondestructive(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof $$+','+typeof inspect+','+typeof keys+','+typeof getEventListeners", "undefined,undefined,undefined,undefined");
    EXPECT(f, "globalThis.$=function(){ return 'page'; }; 0", "0");
    assert_int_equal(jd_install_repl_api(f->ctx), JD_OK);
    EXPECT(f, "$('p')", "page");
    EXPECT(f, "$$('p').length>0 && Array.isArray($$('p'))", "true");
    EXPECT(f, "keys({a:1,b:2}).join()+'|'+values({a:1,b:2}).join()", "a,b|1,2");
    EXPECT(f, "Object.keys(globalThis).indexOf('$$')", "-1");
}

/* rules(el) (spec/freebug_repl.md): the rules that match an element, winning first, with
 * source, specificity, media context and which declarations a stronger rule overrides.
 * External sheet text (the parent's fetched <link> bodies) arrives through jd_set_repl_css. */
/* Web-platform surface (spec/js_platform.md): the guarded globals and element methods a modern
 * page calls without feature detection. */
static void test_platform_interfaces_and_events(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var b=document.getElementById('go'), i=document.querySelector('input');"
              "[b instanceof HTMLButtonElement, b instanceof HTMLElement, i instanceof HTMLInputElement,"
              " i instanceof HTMLButtonElement, document.getElementById('main') instanceof HTMLDivElement].join()",
           "true,true,true,false,true");
    EXPECT(f, "var e=new TransitionEvent('transitionend',{propertyName:'opacity',elapsedTime:2});"
              "[e.type,e.propertyName,e.elapsedTime,String(new StorageEvent('storage').key),e instanceof TransitionEvent,e instanceof Event].join()",
           "transitionend,opacity,2,null,true,true");
    EXPECT(f, "var k=new KeyboardEvent('keydown',{key:'Enter',ctrlKey:true,bubbles:true}), m=new MouseEvent('click',{clientX:7});"
              "[k.key,k.code===''?'e':k.code,k.ctrlKey,k.getModifierState('Control'),k.bubbles,k instanceof UIEvent,"
              " m.clientX,m.pageX,m.button,m instanceof MouseEvent,new CustomEvent('c',{detail:3}).detail,Event.AT_TARGET].join()",
           "Enter,e,true,true,true,true,7,7,0,true,3,2");
    EXPECT(f, "var seen=[]; var b=document.getElementById('go');"
              "b.addEventListener('click',function(e){ seen.push((e instanceof Event)+':'+e.type); });"
              "b.dispatchEvent(new MouseEvent('click',{bubbles:true})); b.dispatchEvent(new Event('click')); seen.join()",
           "true:click,true:click");
    EXPECT(f, "var c=new AbortController(); c.abort('why'); var any=AbortSignal.any([new AbortController().signal,c.signal]);"
              "any.aborted+','+any.reason", "true,why");
    EXPECT(f, "typeof AbortSignal.timeout(50)+','+typeof reportError+','+typeof scheduler.postTask+','+visualViewport.scale",
           "object,function,function,1");
}

static void test_platform_dommatrix_and_imagedata(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "new DOMMatrix().translate(10,20).scale(2).toString()", "matrix(2, 0, 0, 2, 10, 20)");
    EXPECT(f, "var m=new DOMMatrix('matrix(2,0,0,2,10,20)'), p=m.inverse().transformPoint(new DOMPoint(14,24));"
              "p.x+','+p.y+','+m.is2D+','+new DOMMatrix().isIdentity", "2,2,true,true");
    EXPECT(f, "var im=new ImageData(2,3); im.width+','+im.height+','+im.data.length", "2,3,24");
    EXPECT(f, "var t=0; try{ new ImageData(0,5); }catch(e){ t=e.name; } t", "IndexSizeError");
}

static void test_platform_form_controls(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var i=document.querySelector('input'); i.value='hello'; i.setSelectionRange(1,3);"
              "[i.selectionStart,i.selectionEnd,i.selectionDirection].join()", "1,3,none");
    EXPECT(f, "i.select(); i.selectionStart+','+i.selectionEnd", "0,5");
    EXPECT(f, "i.required=true; i.value=''; var n=0; i.addEventListener('invalid',function(){ n++; });"
              "[i.checkValidity(), i.validity.valueMissing, n, document.getElementById('frm').checkValidity()].join()",
           "false,true,1,false");
    EXPECT(f, "i.value='x'; i.setCustomValidity('nope'); [i.validity.customError,i.validationMessage,i.checkValidity()].join()",
           "true,nope,false");
    EXPECT(f, "i.setCustomValidity(''); var s=0; var fm=document.getElementById('frm');"
              "fm.addEventListener('submit',function(e){ s++; e.preventDefault(); }); fm.requestSubmit(); s", "1");
    EXPECT(f, "var e=document.createElement('input'); e.setAttribute('type','email'); e.value='nope';"
              "var a=e.validity.typeMismatch; e.value='a@b.c'; a+','+e.validity.typeMismatch", "true,false");
}

static void test_form_elements_collection(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var fm=document.forms[0]; [fm.elements.length, fm.length, fm.elements.namedItem('q').name,"
              "fm.elements[0].name, fm.elements.q===fm.elements.namedItem('q'), fm.elements.namedItem('zz')].join()",
           "2,2,q,q,true,");
    EXPECT(f, "document.forms[0].elements.namedItem('q').value='sol'; document.forms[0].elements.q.value", "sol");
    set_https_location(f, "https://example.com/a/b");
    {
        js_result r; char buf[256]; int replace = 0;
        assert_int_equal(run(f, "var g=document.createElement('form'); g.setAttribute('method','GET'); g.setAttribute('action','/s');"
                                "var h=document.createElement('input'); h.name='a b'; h.value='x&y'; g.appendChild(h);"
                                "document.body.appendChild(g); g.submit();", &r), JS_OK);
        js_result_free(&r);
        assert_int_equal(jd_take_nav_request(f->ctx, buf, sizeof buf, &replace), 1);
        assert_string_equal(buf, "/s?a+b=x%26y");
        /* a POST form is never turned into a script-driven navigation */
        assert_int_equal(run(f, "document.forms[0].submit();", &r), JS_OK);
        js_result_free(&r);
        assert_int_equal(jd_take_nav_request(f->ctx, buf, sizeof buf, &replace), 0);
    }
}

static void test_shadow_styles_are_scoped(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var host=document.createElement('div'); document.body.appendChild(host);"
              "var sr=host.attachShadow({mode:'open'});"
              "var st=document.createElement('style'); st.textContent=':host{display:none}.a,.b > i{color:red}@media (min-width:1px){:host([open]) p::before{x:y}}';"
              "sr.appendChild(st); var p=document.createElement('p'); p.className='a'; sr.appendChild(p);"
              "__shSync(); [host.getAttribute('data-fzh'), p.getAttribute('data-fzs'), st.textContent].join('|')",
           "1|1|[data-fzh=\"1\"]{display:none}.a[data-fzs=\"1\"],.b > i[data-fzs=\"1\"]{color:red}"
           "@media (min-width:1px){[data-fzh=\"1\"][open] p[data-fzs=\"1\"]::before{x:y}}");
}

static void test_fragment_queries(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var fr=document.createDocumentFragment(), a=document.createElement('div'), b=document.createElement('p');"
              "a.id='x'; b.className='k'; a.appendChild(b); fr.appendChild(a);"
              "[fr.querySelector('.k')===b, fr.querySelectorAll('div,p').length, fr.getElementById('x')===a,"
              "fr.firstElementChild===a, fr.childElementCount, fr.querySelector('.none')].join()",
           "true,2,true,true,1,");
}

/* jQuery's support test does createHTMLDocument("").body.innerHTML=...: it must be a detached
 * document, never the page (it used to wipe the real <body> of every jQuery 3 page). */
static void test_create_html_document_is_detached(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var n0=document.body.children.length; var doc=document.implementation.createHTMLDocument('T');"
              "doc.body.innerHTML='<form></form><form></form>';"
              "[doc.body.childNodes.length, document.body.children.length===n0, doc.body!==document.body, doc.title,"
              " doc.documentElement.tagName, doc.head.tagName, doc.querySelectorAll('form').length,"
              " doc.getElementById('nope')].join()",
           "2,true,true,T,HTML,HEAD,2,");
}

static void test_url_members_shadowed_on_non_anchor(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "'use strict'; var d=document.createElement('div'); d.search=5; d.host='h'; d.hash='x';"
              "var a=document.createElement('a'); a.href='https://e.test/p?q=1#z';"
              "[d.search,d.host,d.hash,a.search,a.hash].join()",
           "5,h,x,?q=1,#z");
}

static void test_slotted_nodes_unrendered_when_slot_hidden(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var h=document.createElement('div'); document.body.appendChild(h);"
              "var sr=h.attachShadow({mode:'open'}); sr.innerHTML='<div hidden><slot name=a></slot></div><slot name=b></slot>';"
              "h.innerHTML='<i slot=a id=x></i><i slot=b id=y></i><i slot=zz id=z></i>';"
              "__shSync(); var m=function(i){ return h.querySelector('#'+i).hasAttribute('data-fzu'); };"
              "[m('x'),m('y'),m('z')].join()",
           "true,false,true");
}

static void test_slotted_nodes_unrendered_through_nested_shadow(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var tip=document.createElement('div'); document.body.appendChild(tip);"
              "var tsr=tip.attachShadow({mode:'open'});"
              "var pop=document.createElement('div'); tsr.appendChild(pop);"
              "var psr=pop.attachShadow({mode:'open'}); psr.innerHTML='<div hidden><slot></slot></div>';"
              "var inner=document.createElement('slot'); inner.setAttribute('name','content'); pop.appendChild(inner);"
              "tip.innerHTML='<span slot=content id=t>Open</span>';"
              "__shSync(); tip.querySelector('#t').hasAttribute('data-fzu')",
           "true");
}

static void test_tree_walker_reverse_navigation(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var r=document.createElement('div'); r.innerHTML='<a id=a><i id=i></i></a><b id=b></b><u id=u></u>';"
              "var w=document.createTreeWalker(r,1); var fw=[]; var n; while((n=w.nextNode())) fw.push(n.id);"
              "var bw=[]; while((n=w.previousNode())) bw.push(n===r?'ROOT':n.id);"
              "w.currentNode=r.querySelector('#u'); var ps=w.previousSibling().id; var lc=document.createTreeWalker(r,1).lastChild().id;"
              "[fw.join(''), bw.join(''), ps, lc].join('|')",
           "aibu|bia|b|u");
}

/* Streams (spec/js_platform.md): ReadableStream/WritableStream/TransformStream and Response.body over
 * the already-received body. Async: the jobs are pumped before the result is read. */
/* navigator.geolocation (spec/identity.md): absent until the host installs it; then it answers
 * with exactly the coordinates the user configured, never a sensor or a lookup. */
/* indexedDB over page memory (spec/js_platform.md): upgrade, stores, indexes, constraint errors,
 * cursors, ranges and rollback. Async: jobs are pumped before the log is read. */
static void test_indexeddb_core(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof indexedDB", "undefined");               /* absent until a trusted host installs it */
    assert_int_equal(jd_install_indexeddb(f->ctx), JD_OK);
    EXPECT(f, "globalThis.L=[]; var r=indexedDB.open('db',1);"
              "r.onupgradeneeded=function(e){ L.push('up:'+e.oldVersion+'>'+e.newVersion); var db=r.result;"
              " var s=db.createObjectStore('p',{keyPath:'id'}); s.createIndex('byName','name');"
              " s.put({id:1,name:'b'}); s.put({id:2,name:'a'}); };"
              "r.onsuccess=function(){ var db=r.result, tx=db.transaction('p','readwrite'), st=tx.objectStore('p');"
              " st.add({id:3,name:'c'});"
              " st.getAll().onsuccess=function(e){ L.push('all:'+e.target.result.map(function(x){return x.id;})); };"
              " st.index('byName').get('a').onsuccess=function(e){ L.push('ix:'+e.target.result.id); };"
              " st.add({id:3}).onerror=function(e){ L.push('dup:'+e.target.error.name); e.preventDefault(); };"
              " st.getAll(IDBKeyRange.bound(2,3)).onsuccess=function(e){ L.push('rng:'+e.target.result.length); };"
              " var n=[]; st.openCursor().onsuccess=function(e){ var c=e.target.result; if(c){ n.push(c.key); c.continue(); } else L.push('cur:'+n); };"
              " tx.oncomplete=function(){ L.push('done'); }; }; 0", "0");
    (void)js_pump_jobs(f->ctx, 4096);
    EXPECT(f, "L.join('|')", "up:0>1|all:1,2,3|ix:2|dup:ConstraintError|rng:2|cur:1,2,3|done");
    /* rollback: an uncaught request error aborts the transaction and undoes its writes */
    EXPECT(f, "globalThis.M=[]; var q=indexedDB.open('db',1); q.onsuccess=function(){ var db=q.result, tx=db.transaction('p','readwrite'), st=tx.objectStore('p');"
              " st.put({id:9,name:'z'}); st.add({id:1,name:'dup'}); tx.onabort=function(){ M.push('abort');"
              "  var t2=db.transaction('p'); t2.objectStore('p').count().onsuccess=function(e){ M.push('count:'+e.target.result); }; }; }; 0", "0");
    (void)js_pump_jobs(f->ctx, 4096);
    EXPECT(f, "M.join('|')", "abort|count:3");
    EXPECT(f, "var e1=null; try{ IDBKeyRange.bound(5,1); }catch(x){ e1=x.name; } e1+','+indexedDB.cmp(1,'a')+','+indexedDB.cmp([1,2],[1,3])", "DataError,-1,-1");
}

static void test_geolocation_fixed_coordinates(void **state) {
    fixture *f = (fixture *)*state;
    /* The real navigator (js_env): non-extensible, with an extensible prototype. */
    EXPECT(f, "globalThis.navigator=Object.preventExtensions(Object.create({})); typeof navigator.geolocation", "undefined");
    assert_int_equal(jd_install_geolocation(f->ctx, -34.6037, -58.3816, 50.0), JD_OK);
    EXPECT(f, "typeof globalThis.__geoCfg+','+typeof navigator.geolocation.getCurrentPosition", "undefined,function");
    EXPECT(f, "globalThis.gp=[]; navigator.geolocation.getCurrentPosition(function(p){"
              " gp.push([p.coords.latitude,p.coords.longitude,p.coords.accuracy,p.coords.altitude,typeof p.timestamp].join()); });"
              "var id=navigator.geolocation.watchPosition(function(p){ gp.push('w'+p.coords.latitude); });"
              "navigator.geolocation.clearWatch(id); typeof id", "number");
    (void)js_pump_jobs(f->ctx, 256);
    EXPECT(f, "gp.join('|')", "-34.6037,-58.3816,50,,number");
    EXPECT(f, "var d=Object.getOwnPropertyDescriptor(navigator,'geolocation')||Object.getOwnPropertyDescriptor(Object.getPrototypeOf(navigator),'geolocation');"
              "String(d&&typeof d.get==='function'&&!d.set)", "true");
    assert_int_equal(jd_install_geolocation(f->ctx, 95.0, 0.0, 10.0), JD_ERR_INTERNAL);   /* out of range: refused */
}

static void test_platform_streams(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "globalThis.o1=[]; globalThis.o2=[]; globalThis.o3=[]; globalThis.o4=[];"
              "var rs=new ReadableStream({start:function(c){ c.enqueue('a'); c.enqueue('b'); c.close(); }});"
              "(async function(){ var rd=rs.getReader(), r; while(!(r=await rd.read()).done) o1.push(r.value); o1.push('end'); })();"
              "(async function(){ var rd=new Blob(['h\\u00e9llo']).stream().pipeThrough(new TextDecoderStream()).getReader(), r;"
              " while(!(r=await rd.read()).done) o2.push(r.value); o2.push('true'); })();"
              "(async function(){ var t=new ReadableStream({start:function(c){ c.enqueue('x'); c.enqueue('y'); c.close(); }})"
              "  .pipeThrough(new TransformStream({transform:function(ch,k){ k.enqueue(ch.toUpperCase()); }}));"
              " for await (var v of t) o3.push(v); })();"
              "(async function(){ var got=[]; var ws=new WritableStream({write:function(c){ got.push(c); },close:function(){ got.push('closed'); }});"
              " await new ReadableStream({start:function(c){ c.enqueue(1); c.enqueue(2); c.close(); }}).pipeTo(ws); o4.push(got.join('|'));"
              " var two=new ReadableStream({start:function(c){ c.enqueue('z'); c.close(); }}).tee();"
              " var r1=await two[0].getReader().read(), r2=await two[1].getReader().read(); o4.push(r1.value+r2.value);"
              " var b=await new Blob(['blob!']).stream().getReader().read(); o4.push(new TextDecoder().decode(b.value)); })();"
              "0", "0");
    (void)js_pump_jobs(f->ctx, 4096);
    EXPECT(f, "o1.join()", "a,b,end");
    EXPECT(f, "o2.join()", "h\xc3\xa9llo,true");
    EXPECT(f, "o3.join()", "X,Y");
    EXPECT(f, "o4.join(';')", "1|2|closed;zz;blob!");
    EXPECT(f, "var e=null; try{ var q=new ReadableStream(); q.getReader(); q.getReader(); }catch(x){ e=x.constructor===TypeError; } e", "true");
}

static void test_platform_element_surface(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var d=document.getElementById('main'); d.hidden=true; var h1=d.hasAttribute('hidden'); d.hidden=false;"
              "h1+','+d.hasAttribute('hidden')+','+d.hidden", "true,false,false");
    EXPECT(f, "document.getElementById('go').outerHTML", "<button id=\"go\" class=\"btn\">Go</button>");
    EXPECT(f, "var x=document.getElementById('go'); var a=x.animate([{opacity:0},{opacity:0.5}],{duration:0,fill:'forwards'});"
              "a.finish(); a.playState+','+x.style.opacity+','+x.getAnimations().length", "finished,0.5,0");
    EXPECT(f, "var k=document.getElementById('go'); k.scrollTo(5,7); k.scrollTop+','+k.checkVisibility()", "0,true");   /* scroll offsets stay normalised */
    EXPECT(f, "var q=new DOMParser().parseFromString('<p class=x>hi <b>there</b></p>','text/html');"
              "q.querySelector('.x').textContent+','+q.body.querySelectorAll('b').length+','+typeof new XMLSerializer().serializeToString",
           "hi there,1,function");
    EXPECT(f, "var st=document.createElement('style'); st.textContent='.a{color:red} @media print{.b{margin:0}}';"
              "document.head.appendChild(st); var ss=document.styleSheets[document.styleSheets.length-1];"
              "var i0=ss.insertRule('p{margin:1px}',0);"
              "[document.styleSheets.length,i0,ss.cssRules.length,ss.cssRules[0].selectorText,ss.cssRules[1].style.getPropertyValue('color'),"
              " ss.cssRules[2].type].join()", "1,0,3,p,red,4");
}

static void test_repl_rules_lists_matching_rules_by_cascade(void **state) {
    fixture *f = (fixture *)*state;
    static const char EXT[] = "button{color:black;padding:1px} @media (min-width:99999px){button{color:pink}}";
    assert_int_equal(jd_set_repl_css(f->ctx, EXT, sizeof EXT - 1), JD_OK);
    assert_int_equal(jd_install_repl_api(f->ctx), JD_OK);
    EXPECT(f, "var s=document.createElement('style');"
              "s.textContent='/*c*/ .btn{color:red;margin:0} #go{color:blue} p{color:green} .btn{padding:4px!important}';"
              "document.head.appendChild(s); document.getElementById('go').setAttribute('style','margin:9px');"
              "var R=rules(document.getElementById('go'));"
              "R.map(function(r){ return r.selector+'@'+r.source+'@'+r.specificity; }).join('|')",
           "element.style@inline@0,0,0|#go@style#1@1,0,0|.btn@style#1@0,1,0|.btn@style#1@0,1,0|button@external@0,0,1");
    EXPECT(f, "R[2].declarations.concat(R[3].declarations).map(function(x){"
              "return x.property+':'+x.overridden+(x.important?'!':''); }).join(',')",
           "padding:false!,color:true,margin:true");
    EXPECT(f, "R[0].declarations[0].overridden+','+R[4].declarations[1].overridden", "false,true");
    EXPECT(f, "rules(document.getElementsByTagName('p')[0]).length+','+rules(null).length", "1,0");
    EXPECT(f, "typeof globalThis.__replCss", "undefined");
}

/* The Freebug panels (spec/fb_panes.md) run against the real engine: each tab's expression
 * returns the text its pane shows, from the same REPL command-line API the console uses. */
static void run_pane(fixture *f, int tab, const char *arg, js_result *r) {
    char expr[FBP_EXPR_MAX];
    assert_true(fbp_expr(tab, arg, strlen(arg), expr, sizeof expr) > 0);
    assert_int_equal(run(f, expr, r), JS_OK);
    assert_non_null(r->value);
}

static void test_freebug_html_pane_outlines_the_dom(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jd_install_repl_api(f->ctx), JD_OK);
    js_result r;
    run_pane(f, FBP_HTML, "#main", &r);
    assert_non_null(strstr(r.value, "<div id=\"main\" class=\"container box\">\n"));
    assert_non_null(strstr(r.value, "\n  <p class=\"text\">\n    \"Hello\"\n"));
    assert_non_null(strstr(r.value, "<button id=\"go\" class=\"btn\">"));
    js_result_free(&r);
    run_pane(f, FBP_HTML, "#absent", &r);
    assert_string_equal(r.value, "(no element matches #absent)");
    js_result_free(&r);
    run_pane(f, FBP_HTML, "", &r);                       /* empty = the whole document */
    assert_true(strncmp(r.value, "<html>", 6) == 0);
    js_result_free(&r);
}

static void test_freebug_css_pane_lists_rules_computed_and_box(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jd_install_repl_api(f->ctx), JD_OK);
    EXPECT(f, "var s=document.createElement('style');s.textContent='.btn{color:red} #go{color:blue}';"
              "document.head.appendChild(s); 1", "1");
    js_result r;
    run_pane(f, FBP_CSS, "#go", &r);
    assert_non_null(strstr(r.value, "== matched rules (2) =="));
    assert_non_null(strstr(r.value, "#go  [style#1]  specificity 1,0,0\n    color: blue"));
    assert_non_null(strstr(r.value, "~ color: red"));      /* the losing declaration is marked */
    assert_non_null(strstr(r.value, "== computed =="));
    assert_non_null(strstr(r.value, "== box =="));
    js_result_free(&r);
    run_pane(f, FBP_CSS, "#absent", &r);
    assert_string_equal(r.value, "(no element matches #absent)");
    js_result_free(&r);
}

static void test_freebug_script_pane_lists_and_numbers_source(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jd_install_repl_api(f->ctx), JD_OK);
    EXPECT(f, "var a=document.createElement('script');a.textContent='var x=1;\\nvar y=2;';"
              "document.body.appendChild(a); 1", "1");
    js_result r;
    run_pane(f, FBP_SCRIPT, "", &r);
    assert_non_null(strstr(r.value, "1. inline, 17 chars"));
    js_result_free(&r);
    run_pane(f, FBP_SCRIPT, "1", &r);
    assert_non_null(strstr(r.value, "    1  var x=1;\n    2  var y=2;"));
    js_result_free(&r);
    run_pane(f, FBP_SCRIPT, "9", &r);
    assert_string_equal(r.value, "(no script #9)");
    js_result_free(&r);
}

static void test_freebug_dom_and_storage_panes(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jd_install_repl_api(f->ctx), JD_OK);
    js_result r;
    run_pane(f, FBP_DOM, "#main", &r);
    assert_non_null(strstr(r.value, "<div>  nodeType 1"));
    assert_non_null(strstr(r.value, "class = \"container box\""));
    assert_non_null(strstr(r.value, "path   "));
    assert_non_null(strstr(r.value, "div#main"));
    assert_non_null(strstr(r.value, "== geometry =="));
    js_result_free(&r);
    run_pane(f, FBP_DOM, "#absent", &r);
    assert_string_equal(r.value, "(no element matches #absent)");
    js_result_free(&r);
    run_pane(f, FBP_STORAGE, "", &r);
    assert_non_null(strstr(r.value, "== cookies (script-visible) =="));
    assert_non_null(strstr(r.value, "== localStorage =="));
    js_result_free(&r);
}

/* The completion expression resolves the path the user typed through descriptors: an accessor ON
 * that path is followed (Enter would evaluate it too, and document.body is one), nothing else runs. */
static void test_freebug_completion_follows_typed_accessors_only(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "globalThis.hit=0; globalThis.obj={alpha:1,get trap(){ globalThis.hit=1; return {inner:1}; }}; 0", "0");
    char expr[1024];
    assert_true(fbc_names_expr("obj", expr, sizeof expr) > 0);
    js_result r;
    assert_int_equal(run(f, expr, &r), JS_OK);
    assert_non_null(strstr(r.value, "alpha"));
    assert_non_null(strstr(r.value, "trap"));
    js_result_free(&r);
    assert_true(fbc_names_expr("obj.trap", expr, sizeof expr) > 0);
    assert_int_equal(run(f, expr, &r), JS_OK);
    assert_non_null(strstr(r.value, "inner"));         /* the typed accessor is followed */
    js_result_free(&r);
    EXPECT(f, "String(globalThis.hit)", "1");
    EXPECT(f, "globalThis.hit=0; globalThis.o2={get a(){ globalThis.hit=2; return 1; }, b:2}; 0", "0");
    assert_true(fbc_names_expr("o2", expr, sizeof expr) > 0);
    assert_int_equal(run(f, expr, &r), JS_OK);         /* listing the owner's names runs no getter */
    js_result_free(&r);
    EXPECT(f, "String(globalThis.hit)", "0");
    assert_true(fbc_names_expr("document", expr, sizeof expr) > 0);
    assert_int_equal(run(f, expr, &r), JS_OK);
    assert_non_null(strstr(r.value, "querySelector"));
    js_result_free(&r);
}

static void test_freebug_net_pane_empty_and_selector_is_data(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jd_install_repl_api(f->ctx), JD_OK);
    js_result r;
    run_pane(f, FBP_NET, "", &r);
    assert_string_equal(r.value, "(no requests)");
    js_result_free(&r);
    /* A selector that tries to break out of its literal is only ever a string. */
    run_pane(f, FBP_HTML, "\"});globalThis.__pwn=1;(\"", &r);
    js_result_free(&r);
    EXPECT(f, "typeof globalThis.__pwn", "undefined");
}

static void test_repl_api_inspect_and_event_listeners(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jd_install_repl_api(f->ctx), JD_OK);
    EXPECT(f, "var el=document.getElementById('go'); var i=inspect(el);"
              "i.id+','+(typeof i.tag)+','+(typeof i.attributes)+','+(i.rect===null)", "go,string,object,true");
    EXPECT(f, "function onc(){} el.addEventListener('click',onc,true); el.addEventListener('click',function(){});"
              "var L=getEventListeners(el); L.click.length+','+(L.click[0].listener===onc)+','+L.click[0].useCapture",
           "2,true,true");
    EXPECT(f, "getEventListeners(document.createElement('div')).click===undefined", "true");
    EXPECT(f, "var n=0, old=console.log; console.log=function(){ n++; };"
              "monitorEvents(el,'click'); el.dispatchEvent(new Event('click')); unmonitorEvents(el,'click');"
              "el.dispatchEvent(new Event('click')); console.log=old; n", "1");
}

/* Real ResizeObserver (spec/js_observers.md): on a trusted page it reports the laid-out
 * size on the first measurement, stays quiet while the size is unchanged, and fires again
 * when a new layout changes it. Zero-size targets and targets without a rect never fire. */
static void test_ro_real_reports_size_changes(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id go = js_handle(f, "document.getElementById('go')._h");
    assert_int_equal(jt_enable_observers(f->ctx), JD_OK);
    EXPECT(f, "globalThis.__ro=[];"
              "var ro=new ResizeObserver(function(es){ es.forEach(function(e){"
              "__ro.push(e.target.id+':'+e.contentRect.width+'x'+e.contentRect.height"
              "+':'+e.borderBoxSize[0].inlineSize); }); });"
              "ro.observe(document.getElementById('go')); ro.observe(document.getElementsByTagName('p')[0]);"
              "__ro.length", "0");
    jg_table t;
    jg_init(&t);
    t.scroll_y = 0; t.view_w = 1000; t.view_h = 700; t.doc_w = 1000; t.doc_h = 3000;
    assert_int_equal(jg_add(&t, go, 10, 100, 200, 50), 0);
    assert_int_equal(jg_aggregate(&t, geom_parent, f->idx), 0);
    assert_int_equal(jd_set_geometry(f->ctx, &t), JD_OK);
    assert_int_equal(jt_geometry_changed(f->ctx), JD_OK);
    EXPECT(f, "__ro.join(',')", "go:200x50:200");
    assert_int_equal(jt_geometry_changed(f->ctx), JD_OK);
    EXPECT(f, "__ro.length", "1");
    jg_free(&t);
    jg_init(&t);
    t.scroll_y = 0; t.view_w = 1000; t.view_h = 700; t.doc_w = 1000; t.doc_h = 3000;
    assert_int_equal(jg_add(&t, go, 10, 100, 320, 50), 0);
    assert_int_equal(jg_aggregate(&t, geom_parent, f->idx), 0);
    assert_int_equal(jd_set_geometry(f->ctx, &t), JD_OK);
    assert_int_equal(jt_geometry_changed(f->ctx), JD_OK);
    EXPECT(f, "__ro.length+','+__ro[1]", "2,go:320x50:320");
    jg_free(&t);
}

/* Real IntersectionObserver (spec/js_observers.md): on a trusted page the observer reports
 * the element's laid-out rect against the real viewport (+ rootMargin), and re-evaluates
 * when the parent re-installs geometry after a scroll -- lazy loaders fire on scroll. */
static void test_io_real_follows_scroll(void **state) {
    fixture *f = (fixture *)*state;
    dom_node_id go = js_handle(f, "document.getElementById('go')._h");
    dom_node_id p1 = js_handle(f, "document.getElementsByTagName('p')[0]._h");
    assert_int_equal(jt_enable_observers(f->ctx), JD_OK);
    EXPECT(f, "globalThis.__log=[];"
              "var io=new IntersectionObserver(function(es){ es.forEach(function(e){"
              "__log.push(e.target.nodeName.toLowerCase()+':'+(e.isIntersecting?1:0)); }); },"
              " {rootMargin:'100px'});"
              "io.observe(document.getElementById('go')); io.observe(document.getElementsByTagName('p')[0]);"
              "__log.length", "0");
    jg_table t;
    jg_init(&t);
    t.scroll_y = 0; t.view_w = 1000; t.view_h = 700; t.doc_w = 1000; t.doc_h = 3000;
    assert_int_equal(jg_add(&t, go, 10, 100, 200, 50), 0);
    assert_int_equal(jg_add(&t, p1, 0, 2000, 300, 20), 0);
    assert_int_equal(jg_aggregate(&t, geom_parent, f->idx), 0);
    assert_int_equal(jd_set_geometry(f->ctx, &t), JD_OK);
    assert_int_equal(jt_geometry_changed(f->ctx), JD_OK);
    const char *first = NULL;
    js_result r;
    assert_int_equal(run(f, "__log.join(',')", &r), JS_OK);
    first = r.value;
    assert_true(strstr(first, ":1") != NULL && strstr(first, ":0") != NULL);
    js_result_free(&r);
    assert_int_equal(jt_geometry_changed(f->ctx), JD_OK);
    EXPECT(f, "__log.length", "2");
    jg_free(&t);

    jg_init(&t);
    t.scroll_y = 1800; t.view_w = 1000; t.view_h = 700; t.doc_w = 1000; t.doc_h = 3000;
    assert_int_equal(jg_add(&t, go, 10, 100, 200, 50), 0);
    assert_int_equal(jg_add(&t, p1, 0, 2000, 300, 20), 0);
    assert_int_equal(jg_aggregate(&t, geom_parent, f->idx), 0);
    assert_int_equal(jd_set_geometry(f->ctx, &t), JD_OK);
    assert_int_equal(jt_geometry_changed(f->ctx), JD_OK);
    EXPECT(f, "__log.length", "4");
    jg_free(&t);
}

/* An untrusted page never gets the real observer: geometry stays private. */
static void test_io_untrusted_stays_synthetic(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof IntersectionObserver.prototype.observe+','+(typeof __ioTick)",
              "function,undefined");
}

static void test_geom_null_ctx(void **state) {
    (void)state;
    assert_int_equal(jd_set_geometry(NULL, NULL), JD_ERR_NULL_ARG);
}

/* --- history API (spec/js_dom.md 7e) --- */

static void set_loc(fixture *f, const char *href) {
    url_parts parts;
    assert_int_equal(url_split(href, &parts), URL_OK);
    assert_int_equal(jd_set_location(f->ctx, href, &parts), JD_OK);
}

static void test_history_push_replace_update_location(void **state) {
    fixture *f = (fixture *)*state;
    set_loc(f, "https://a.test/x");
    EXPECT(f, "history.pushState({a:1},'','/p1?k=v');"
              "[location.href,location.pathname,location.search,history.state.a,history.length].join('|')",
              "https://a.test/p1?k=v|/p1|?k=v|1|2");
    EXPECT(f, "history.replaceState(null,'','#frag');"
              "[location.href,location.hash,String(history.state),history.length].join('|')",
              "https://a.test/p1?k=v#frag|#frag|null|2");
    int go = 99;
    char *ops = jd_take_history(f->ctx, &go);
    assert_non_null(ops);
    assert_string_equal(ops, "P https://a.test/p1?k=v\nR https://a.test/p1?k=v#frag\n");
    assert_int_equal(go, 0);
    free(ops);
    /* taking clears */
    ops = jd_take_history(f->ctx, &go);
    assert_null(ops);
}

static void test_history_cross_origin_is_security_error(void **state) {
    fixture *f = (fixture *)*state;
    set_loc(f, "https://a.test/x");
    EXPECT(f, "var n='none'; try{ history.pushState(1,'','https://evil.test/'); }"
              "catch(e){ n=e.name; } n+'|'+location.href+'|'+history.length",
              "SecurityError|https://a.test/x|1");
    int go = 0;
    char *ops = jd_take_history(f->ctx, &go);
    assert_null(ops);
}

static void test_history_popstate_restores_entry(void **state) {
    fixture *f = (fixture *)*state;
    set_loc(f, "https://a.test/x");
    EXPECT(f, "var L=[]; window.addEventListener('popstate',function(e){"
              "  L.push(location.pathname+':'+JSON.stringify(e.state)); });"
              "window.onhashchange=function(e){ L.push('hash'); };"
              "history.pushState({n:1},'','/p1'); history.pushState({n:2},'','/p1#h'); 'ok'", "ok");
    free(jd_take_history(f->ctx, NULL));
    assert_int_equal(jd_pop_state(f->ctx, 1), 1);
    assert_int_equal(jd_pop_state(f->ctx, 0), 1);
    assert_int_equal(jd_pop_state(f->ctx, 7), 0);      /* out of range: ignored */
    EXPECT(f, "L.join(',')+'|'+location.href", "/p1:{\"n\":1},hash,/x:null|https://a.test/x");
    EXPECT(f, "history.length+'|'+String(history.state)", "3|null");
}

static void test_history_go_records_delta(void **state) {
    fixture *f = (fixture *)*state;
    set_loc(f, "https://a.test/x");
    EXPECT(f, "history.back(); history.go(-2); history.forward(); 'ok'", "ok");
    int go = 0;
    char *ops = jd_take_history(f->ctx, &go);
    assert_null(ops);
    assert_int_equal(go, -2);
}

static void test_history_is_bounded(void **state) {
    fixture *f = (fixture *)*state;
    set_loc(f, "https://a.test/x");
    EXPECT(f, "for(var i=0;i<400;i++) history.pushState(i,'','/p'+i);"
              "history.length+'|'+history.state+'|'+location.pathname", "256|399|/p399");
    int go = 0;
    char *ops = jd_take_history(f->ctx, &go);
    assert_non_null(ops);
    size_t lines = 0;
    for (const char *p = ops; *p; ++p) if (*p == '\n') lines++;
    assert_true(lines <= 512);
    free(ops);
}

/* --- WebSocket (spec/js_dom.md 7f) --- */

static void test_ws_absent_until_enabled(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof WebSocket", "undefined");
}

static void test_ws_lifecycle_records_ops_and_fires_events(void **state) {
    fixture *f = (fixture *)*state;
    set_loc(f, "https://a.test/x");
    assert_int_equal(jt_enable_ws(f->ctx), JD_OK);
    EXPECT(f, "var L=[]; var s=new WebSocket('/live');"
              "s.onopen=function(){ L.push('open'+s.readyState); };"
              "s.addEventListener('message',function(e){"
              "  L.push(typeof e.data==='string' ? 't:'+e.data : 'b:'+e.data.byteLength+':'+new Uint8Array(e.data)[1]); });"
              "s.onclose=function(e){ L.push('close'+e.code+e.wasClean+s.readyState); };"
              "var err='none'; try{ s.send('early'); }catch(e){ err=e.name; }"
              "[s.url, s.readyState, err, WebSocket.OPEN].join('|')",
              "wss://a.test/live|0|InvalidStateError|1");
    jt_ws_op ops[8];
    size_t n = jt_take_ws(f->ctx, ops, 8);
    assert_int_equal(n, 1);
    assert_int_equal(ops[0].kind, JT_WS_OPEN);
    assert_string_equal(ops[0].data, "wss://a.test/live");
    int id = ops[0].id;
    jt_ws_ops_free(ops, n);

    assert_int_equal(jt_ws_event(f->ctx, id, JT_WSE_OPEN, 0, NULL, 0), 1);
    EXPECT(f, "s.send('hi'); s.send(new Uint8Array([1,255,0])); s.readyState", "1");
    n = jt_take_ws(f->ctx, ops, 8);
    assert_int_equal(n, 2);
    assert_int_equal(ops[0].kind, JT_WS_SEND_TEXT);
    assert_string_equal(ops[0].data, "hi");
    assert_int_equal(ops[1].kind, JT_WS_SEND_BIN);
    assert_int_equal(ops[1].len, 3);
    assert_int_equal((unsigned char)ops[1].data[1], 255);
    assert_int_equal((unsigned char)ops[1].data[2], 0);
    jt_ws_ops_free(ops, n);

    assert_int_equal(jt_ws_event(f->ctx, id, JT_WSE_TEXT, 0, "yo \"q\"", 6), 1);
    assert_int_equal(jt_ws_event(f->ctx, id, JT_WSE_BINARY, 0, "\x00\x07", 2), 1);
    EXPECT(f, "s.close(1000,'bye'); s.readyState", "2");
    n = jt_take_ws(f->ctx, ops, 8);
    assert_int_equal(n, 1);
    assert_int_equal(ops[0].kind, JT_WS_CLOSE);
    jt_ws_ops_free(ops, n);
    assert_int_equal(jt_ws_event(f->ctx, id, JT_WSE_CLOSE, 1000, "bye", 3), 1);
    EXPECT(f, "L.join(',')", "open1,t:yo \"q\",b:2:7,close1000true3");
    assert_int_equal(jt_ws_event(f->ctx, 999, JT_WSE_TEXT, 0, "x", 1), 0);
}

/* --- iframes + cross-window postMessage (spec/frame_broker.md) --- */

static void test_frames_top_document_parent_is_self(void **state) {
    fixture *f = (fixture *)*state;
    set_loc(f, "https://top.test/");
    assert_int_equal(jt_enable_frames(f->ctx, 0), JD_OK);
    EXPECT(f, "[window.parent===window, window.top===window].join()", "true,true");
}

static void test_frames_child_document_posts_to_parent_and_top(void **state) {
    fixture *f = (fixture *)*state;
    set_loc(f, "https://c.test/anchor");
    assert_int_equal(jt_enable_frames(f->ctx, 3), JD_OK);
    EXPECT(f, "[window.parent!==window, window.top!==window].join()", "true,true");
    EXPECT(f, "parent.postMessage({a:1},'https://top.test'); top.postMessage('x','*'); 'ok'", "ok");
    jt_ws_op ops[8];
    size_t n = jt_take_ws(f->ctx, ops, 8);
    assert_int_equal(n, 2);
    assert_int_equal(ops[0].kind, JT_WS_FRAME_POST);
    assert_int_equal(ops[0].id, -1);
    assert_string_equal(ops[0].data, "https://top.test\n{\"a\":1}");
    assert_int_equal(ops[1].id, -2);
    assert_string_equal(ops[1].data, "*\n\"x\"");
    jt_ws_ops_free(ops, n);
}

static void test_frames_blank_iframe_has_writable_document(void **state) {
    fixture *f = (fixture *)*state;
    set_loc(f, "https://top.test/p/");
    assert_int_equal(jt_enable_frames(f->ctx, 0), JD_OK);
    EXPECT(f, "var i=document.createElement('iframe'); document.body.appendChild(i);"
              "var d=i.contentDocument; d.open(); d.write('<!DOCTYPE html><html><body><p id=\\'q\\'>hi</p></body></html>'); d.close();"
              "[d===i.contentWindow.document, d.getElementById('q')&&d.getElementById('q').textContent,"
              " i.contentWindow.parent===window, d.body&&d.body.tagName].join()",
              "true,hi,true,BODY");
    jt_ws_op ops[4];
    assert_int_equal(jt_take_ws(f->ctx, ops, 4), 0);
}

static void test_frames_iframe_discovery_and_child_post(void **state) {
    fixture *f = (fixture *)*state;
    set_loc(f, "https://top.test/p/");
    assert_int_equal(jt_enable_frames(f->ctx, 0), JD_OK);
    EXPECT(f, "var i=document.createElement('iframe'); i.setAttribute('src','/anchor?k=1');"
              "document.body.appendChild(i); typeof i.contentWindow.postMessage", "function");
    jt_ws_op ops[8];
    size_t n = jt_take_ws(f->ctx, ops, 8);
    assert_int_equal(n, 1);
    assert_int_equal(ops[0].kind, JT_WS_FRAME_OPEN);
    assert_true(ops[0].id > 0);
    assert_string_equal(ops[0].data, "https://top.test/anchor?k=1");
    int tok = ops[0].id;
    jt_ws_ops_free(ops, n);

    EXPECT(f, "i.contentWindow.postMessage([1,2],'*'); 'sent'", "sent");
    n = jt_take_ws(f->ctx, ops, 8);
    assert_int_equal(n, 1);
    assert_int_equal(ops[0].kind, JT_WS_FRAME_POST);
    assert_int_equal(ops[0].id, tok);
    assert_string_equal(ops[0].data, "*\n[1,2]");
    jt_ws_ops_free(ops, n);

    EXPECT(f, "i.parentNode.removeChild(i); 'gone'", "gone");
    n = jt_take_ws(f->ctx, ops, 8);
    assert_int_equal(n, 1);
    assert_int_equal(ops[0].kind, JT_WS_FRAME_CLOSE);
    assert_int_equal(ops[0].id, tok);
    jt_ws_ops_free(ops, n);
}

static void test_frames_message_delivery_sets_origin_and_source(void **state) {
    fixture *f = (fixture *)*state;
    set_loc(f, "https://c.test/anchor");
    assert_int_equal(jt_enable_frames(f->ctx, 3), JD_OK);
    EXPECT(f, "var got=[]; window.addEventListener('message',function(e){"
              "got.push(e.data.k+'|'+e.origin+'|'+(e.source===window.parent)); }); 'armed'", "armed");
    const char *m = "https://top.test\np\n{\"k\":2}";
    assert_int_equal(jt_ws_event(f->ctx, 0, JT_WSE_FRAME_MSG, 0, m, strlen(m)), 1);
    EXPECT(f, "got.join(',')", "2|https://top.test|true");
    /* a hostile payload is parsed as data, never evaluated */
    const char *bad = "https://top.test\np\nglobalThis.pwn=1";
    assert_int_equal(jt_ws_event(f->ctx, 0, JT_WSE_FRAME_MSG, 0, bad, strlen(bad)), 0);
    EXPECT(f, "typeof globalThis.pwn", "undefined");
}

static void test_frames_oversize_payload_rejected(void **state) {
    fixture *f = (fixture *)*state;
    set_loc(f, "https://c.test/anchor");
    assert_int_equal(jt_enable_frames(f->ctx, 3), JD_OK);
    EXPECT(f, "var e='none'; try{ parent.postMessage('x'.repeat(2000000),'*'); }catch(x){ e=x.name; } e",
              "DataCloneError");
    jt_ws_op ops[8];
    assert_int_equal(jt_take_ws(f->ctx, ops, 8), 0);
}

static void test_ws_rejects_plaintext_and_caps(void **state) {
    fixture *f = (fixture *)*state;
    set_loc(f, "https://a.test/x");
    assert_int_equal(jt_enable_ws(f->ctx), JD_OK);
    EXPECT(f, "var n='none'; try{ new WebSocket('ws://a.test/s'); }catch(e){ n=e.name; } n",
              "SecurityError");
    EXPECT(f, "var m='none'; try{ for(var i=0;i<9;i++) new WebSocket('wss://c.test/'+i); }"
              "catch(e){ m=e.name+i; } m", "SecurityError8");
    jt_ws_op ops[16];
    size_t n = jt_take_ws(f->ctx, ops, 16);
    assert_int_equal(n, 8);
    jt_ws_ops_free(ops, n);
}

/* --- in-memory localStorage (spec/web_storage.md) --- */

static void test_storage_untrusted_stays_ephemeral(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "localStorage.setItem('a','1'); localStorage.getItem('a')", "1");
    char *out = NULL;
    size_t len = 0;
    assert_int_equal(jt_take_storage(f->ctx, &out, &len), 0);
    assert_null(out);
}

static void test_storage_seeded_and_dirty_snapshot(void **state) {
    fixture *f = (fixture *)*state;
    const char *k[] = { "theme", "n" };
    const char *v[] = { "dark", "5" };
    size_t kl[] = { 5, 1 }, vl[] = { 4, 1 };
    char *seed = NULL;
    size_t sl = 0;
    assert_int_equal(wst_pack(k, kl, v, vl, 2, &seed, &sl), 0);
    assert_int_equal(jt_enable_storage(f->ctx, seed, sl), JD_OK);
    free(seed);
    EXPECT(f, "[localStorage.getItem('theme'), localStorage.length, localStorage.getItem('zz'),"
              " typeof localStorage.key(0)].join('|')", "dark|2||string");
    char *out = NULL;
    size_t len = 0;
    assert_int_equal(jt_take_storage(f->ctx, &out, &len), 0);      /* untouched: not dirty */
    EXPECT(f, "localStorage.setItem('n', 6); localStorage.removeItem('theme');"
              "localStorage.setItem('draft', 'hola \\u00f1'); localStorage.length", "2");
    assert_int_equal(jt_take_storage(f->ctx, &out, &len), 1);
    assert_int_equal(wst_decode_check(out, len), 0);
    wst_db *db = wst_new();
    assert_int_equal(wst_replace(db, "https://a.test", out, len), 0);
    assert_int_equal(wst_origin_bytes(db, "https://a.test"), 1 + 1 + 5 + 7); /* "hola \\u00f1" = 7 UTF-8 bytes */
    wst_free(db);
    free(out);
    assert_int_equal(jt_take_storage(f->ctx, &out, &len), 0);      /* cleared */
    EXPECT(f, "localStorage.clear(); localStorage.length", "0");
    assert_int_equal(jt_take_storage(f->ctx, &out, &len), 1);
    assert_int_equal(len, 4);
    free(out);
}

static void test_storage_quota_exceeded(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jt_enable_storage(f->ctx, NULL, 0), JD_OK);   /* invalid seed: empty */
    EXPECT(f, "var e='none'; var big='x'.repeat(5*1024*1024);"
              "try{ localStorage.setItem('k', big); }catch(x){ e=x.name; }"
              "e+'|'+localStorage.length", "QuotaExceededError|0");
}

/* --- ParentNode/ChildNode mixins, interface prototypes, template.content --- */

static void test_dom_ordered_insertion(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var m=document.getElementById('main'), x=document.createElement('i');"
              "m.prepend(x); var r1=(m.firstElementChild===x);"
              "var y=document.createElement('b'), g=document.getElementById('go');"
              "m.insertBefore(y,g); var r2=(y.nextElementSibling===g);"
              "var z=document.createElement('u'); m.insertBefore(z,null); var r3=(m.lastElementChild===z);"
              "[r1,r2,r3].join(',')", "true,true,true");
}

static void test_dom_childnode_mixins(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var g=document.getElementById('go'), a=document.createElement('a'), b=document.createElement('b'),"
              "  c=document.createElement('s');"
              "g.before(a); g.after(b);"
              "var r1=(a.nextElementSibling===g && g.nextElementSibling===b);"
              "b.replaceWith(c); var r2=(g.nextElementSibling===c && b.parentNode===null);"
              "var m=document.getElementById('main'); var k=document.createElement('em');"
              "m.replaceChildren(k); var r3=(m.children.length===1 && m.firstElementChild===k);"
              "[r1,r2,r3].join(',')", "true,true,true");
}

static void test_dom_interface_prototypes(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var e=document.getElementById('go');"
              "[document instanceof Document, document instanceof Node, e instanceof HTMLElement,"
              " e instanceof Element, e instanceof Node, e instanceof EventTarget,"
              " ({}) instanceof Node, typeof document.prepend].join(',')",
              "true,true,true,true,true,true,false,function");
}

static void test_dom_template_content(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var t=document.createElement('template'), s=document.createElement('span');"
              "s.textContent='stamp'; t.content.appendChild(s);"
              "var c1=t.content.cloneNode(true), c2=t.content.cloneNode(true);"
              "var host=document.getElementById('main'); host.appendChild(c1);"
              "[t.content.nodeType, t.content===t.content, c2.firstChild.textContent,"
              " host.lastElementChild.textContent, host.lastElementChild!==s].join(',')",
              "11,true,stamp,stamp,true");
}

/* document.currentScript is built from VALUES (a hostile src round-trips verbatim)
 * and answers hasAttribute; NULL clears it (a module runs with currentScript null). */
static void test_current_script_values_and_methods(void **state) {
    fixture *f = (fixture *)*state;
    js_set_current_script(f->ctx, "https://x.test/a'\n\"b.js", "text/javascript");
    EXPECT(f, "var c=document.currentScript;"
              "[c.getAttribute('src')===\"https://x.test/a'\\n\\\"b.js\", c.hasAttribute('src'),"
              " c.hasAttribute('data-x'), c.getAttribute('type')].join(',')",
              "true,true,false,text/javascript");
    js_set_current_script(f->ctx, NULL, NULL);
    EXPECT(f, "String(document.currentScript)", "null");
}

/* The executing <script> that exists in the document is handed out as the REAL element (remove(),
 * id, parentNode): x.com's router stream ends every chunk with document.currentScript.remove().
 * Each element is claimed once, so two identical inline scripts resolve in document order. */
static void test_current_script_is_the_real_element(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var a=document.createElement('script'); a.id='s1'; a.setAttribute('type','text/javascript'); document.body.appendChild(a);"
              "var b=document.createElement('script'); b.id='s2'; b.setAttribute('type','text/javascript'); document.body.appendChild(b); 1", "1");
    js_set_current_script(f->ctx, "", "text/javascript");
    EXPECT(f, "var c1=document.currentScript; c1.id+','+typeof c1.remove", "s1,function");
    EXPECT(f, "c1.remove(); !document.getElementById('s1')", "true");
    js_set_current_script(f->ctx, "", "text/javascript");
    EXPECT(f, "document.currentScript.id", "s2");
    js_set_current_script(f->ctx, NULL, NULL);
}

/* --- DOM Standard extras (js_dom_ext) --- */

static void test_ext_tree_navigation(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var g=document.getElementById('go'), m=document.getElementById('main');"
              "var d=document.createElement('div');"
              "[g.getRootNode()===document, g.isConnected, d.isConnected, d.getRootNode()===d,"
              " g.previousElementSibling.textContent, m.previousElementSibling===null,"
              " g.toggleAttribute('hidden'), g.hasAttribute('hidden'), g.toggleAttribute('hidden'),"
              " g.toggleAttribute('hidden', false), g.hasAttribute('hidden')].join(',')",
              "true,true,false,true,World,true,true,true,false,false,false");
}

static void test_ext_compare_document_position(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var m=document.getElementById('main'), g=document.getElementById('go'),"
              "    p=document.getElementsByTagName('p')[0], d=document.createElement('div');"
              "[m.compareDocumentPosition(m), m.compareDocumentPosition(g), g.compareDocumentPosition(m),"
              " p.compareDocumentPosition(g), g.compareDocumentPosition(p),"
              " (m.compareDocumentPosition(d) & 1)].join(',')", "0,20,10,4,2,1");
}

static void test_ext_shadow_root(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var h=document.getElementById('main'); var sr=h.attachShadow({mode:'open'});"
              "var s=document.createElement('slot'); sr.appendChild(s);"
              "var e='none'; try{ h.attachShadow({mode:'open'}); }catch(x){ e=x.name; }"
              "[h.shadowRoot===sr, sr.host===h, sr.mode, sr.firstChild===s, e,"
              " document.getElementById('go').attachShadow({mode:'closed'})!==null,"
              " document.getElementById('go').shadowRoot].join(',')",
              "true,true,open,true,NotSupportedError,true,");
}

static void test_ext_tree_walker_terminates(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var w=document.createTreeWalker(document.getElementById('main'), 1);"
              "var n=0, tags=[]; while(w.nextNode() && n++<100) tags.push(w.currentNode.tagName);"
              "var it=document.createNodeIterator(document.body, NodeFilter.SHOW_ELEMENT,"
              "  {acceptNode:function(x){ return x.tagName==='P'?NodeFilter.FILTER_ACCEPT:NodeFilter.FILTER_SKIP; }});"
              "var k=0, c; while((c=it.nextNode()) && k<100) k++;"
              "tags.length+'|'+tags[0]+'|'+k", "6|P|2");
}

static void test_ext_document_helpers(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var g=document.getElementById('go'); var c=document.importNode(g,true);"
              "var r=document.createRange(); r.selectNodeContents(document.body);"
              "var frag=r.createContextualFragment('<b id=\\\"cf\\\">x</b>');"
              "document.body.appendChild(frag);"
              "[c!==g, c.textContent, document.adoptNode(g)===g, document.getElementById('cf').textContent,"
              " document.elementFromPoint(1,1), typeof r.getBoundingClientRect().width].join(',')",
              "true,Go,true,x,,number");
}

/* A page that rebinds the global identifier `globalThis` (core-js style polyfills;
 * measured on openstreetmap.org) must not break the engine's own shims: they resolve
 * the real global through a tamper-proof binding captured at install. */
static void test_shims_survive_globalthis_rebinding(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var globalThis = { fake: true };"
              "var L=[]; document.addEventListener('click', function(){ L.push('doc'); });"
              "var g=document.getElementById('go'); g.addEventListener('click', function(){ L.push('el'); });"
              "localStorage.setItem('k','v');"
              "'ok'", "ok");
    dom_node_id h = (dom_node_id)0;
    js_result r;
    assert_int_equal(js_eval(f->ctx, "document.getElementById('go')._h", 32, &r), JS_OK);
    h = (dom_node_id)strtoull(r.value, NULL, 10);
    js_result_free(&r);
    assert_int_equal(jd_fire_click(f->ctx, h), 1);
    EXPECT(f, "L.join(',')+'|'+localStorage.getItem('k')", "el,doc|v");
    /* the binding itself cannot be replaced or shadowed */
    EXPECT(f, "var __G = 1; typeof __G", "object");
    /* a top-level `let __G` in a page script is rejected outright (non-configurable
     * global property), so it can never shadow the binding for later scripts */
    js_result lr;
    assert_int_not_equal(js_eval(f->ctx, "let __G = 2;", 12, &lr), JS_OK);
    js_result_free(&lr);
    EXPECT(f, "typeof __G + '|' + (__G.document === document)", "object|true");
}

/* Interfaces web code enumerates (webcomponents polyfills, DocumentType checks) exist
 * with their prototype chains, the global is a Window, and a <canvas> from
 * createElement / createElementNS answers getContext ('2d' only; webgl => null). */
static void test_interfaces_window_and_canvas(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "['DocumentType','CDATASection','ProcessingInstruction','Window','NamedNodeMap',"
              " 'Range','Selection','TreeWalker','NodeIterator','MediaQueryList','DOMRect']"
              ".map(function(n){ return typeof __G[n]; }).join(',')",
              "function,function,function,function,function,function,function,function,function,function,function");
    EXPECT(f, "[window instanceof Window, Object.create(CDATASection.prototype) instanceof Text,"
              " Object.create(DocumentType.prototype) instanceof Node, typeof Image].join(',')",
              "true,true,true,undefined");
    EXPECT(f, "var c=document.createElement('canvas'), x=document.createElementNS('http://www.w3.org/1999/xhtml','canvas');"
              "[typeof c.getContext('2d'), c.getContext('webgl'), typeof x.getContext('2d').fillRect,"
              " typeof document.createElement('div').getContext, c.width, c.height].join(',')",
              "object,,function,undefined,300,150");
}

/* Blob / File / FileReader / object URLs / structuredClone / MessageChannel (all
 * in-page: no network, no cross-window channel). */
static void test_ext_blob_family(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var b=new Blob(['ab', new Uint8Array([99,100])], {type:'text/plain'});"
              "var s=b.slice(1,3); var fl=new File(['xyz'],'n.txt',{type:'text/x'});"
              "var u=URL.createObjectURL(b);"
              "[b.size, b.type, s.size, fl.name, fl.size, fl instanceof Blob, u.indexOf('blob:')===0].join(',')",
              "4,text/plain,2,n.txt,3,true,true");
    EXPECT(f, "var out=[]; b.text().then(function(t){ out.push(t); });"
              "var fr=new FileReader(); fr.onload=function(){ out.push(fr.result); }; fr.readAsText(fl);"
              "'queued'", "queued");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "__tickTimers(0); out.join('|')", "abcd|xyz");
    EXPECT(f, "var o={a:[1,{b:2}],d:new Date(5),m:new Map([[1,2]])}; var c=structuredClone(o);"
              "[c!==o, c.a[1].b, c.d.getTime(), c.m.get(1), c.a!==o.a].join(',')", "true,2,5,2,true");
    EXPECT(f, "var got=[]; var mc=new MessageChannel(); mc.port2.onmessage=function(e){ got.push(e.data.k); };"
              "mc.port1.postMessage({k:7}); __tickTimers(0); got.join(',')", "7");
}

/* insertAdjacent* at the four positions, text included (was a no-op stub). */
static void test_ext_insert_adjacent(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var g=document.getElementById('go'), m=document.getElementById('main');"
              "var e=document.createElement('em'); e.textContent='E';"
              "g.insertAdjacentElement('afterend', e);"
              "g.insertAdjacentHTML('beforeend', ' tail <b>B</b>');"
              "g.insertAdjacentHTML('afterbegin', '<i>I</i> ');"
              "g.insertAdjacentText('beforebegin', 'pre');"
              "[g.textContent, g.nextElementSibling===e, m.textContent.indexOf('preI Go')>=0,"
              " (function(){ try{ g.insertAdjacentElement('bogus', e); return 'none'; }catch(x){ return x.name; } })()].join('|')",
              "I Go tail B|true|true|SyntaxError");
}

/* Interface prototypes carry real methods/accessors that delegate to the wrapper:
 * what Shadow DOM / instrumentation polyfills capture (youtube webcomponents-sd). */
static void test_ext_prototype_delegation(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var m=document.getElementById('main'), x=document.createElement('u'), L=[];"
              "var nativeAdd=EventTarget.prototype.addEventListener;"
              "nativeAdd.call(window,'ping',function(){ L.push('w'); });"
              "window.dispatchEvent(new Event('ping'));"
              "Node.prototype.appendChild.call(m, x);"
              "var d=Object.getOwnPropertyDescriptor(Node.prototype,'textContent');"
              "var p=Object.getOwnPropertyDescriptor(Node.prototype,'parentNode');"
              "[L.join(), m.lastElementChild===x, typeof d.get, p.get.call(x)===m,"
              " typeof Element.prototype.setAttribute, typeof Element.prototype.querySelectorAll].join(',')",
              "w,true,function,true,function,function");
}

/* Intl surface formatjs/Next.js touch at startup (duckduckgo): supportedLocalesOf
 * on every constructor, Locale, DisplayNames, Segmenter -- identity-neutral (en-US). */
static void test_intl_surface(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "[Intl.NumberFormat.supportedLocalesOf(['en-US','fr']).length,"
              " Intl.DateTimeFormat.supportedLocalesOf('en').join(),"
              " typeof Intl.PluralRules.supportedLocalesOf, new Intl.Locale('en-US').language,"
              " new Intl.DisplayNames(['en'],{type:'region'}).of('US'),"
              " [...new Intl.Segmenter('en',{granularity:'grapheme'}).segment('ab')].length,"
              " Intl.getCanonicalLocales('EN-us').join()].join('|')",
              "2|en|function|en|US|2|en-US");
}

/* Lifecycle listeners get a real event object (Bootstrap's EventHandler does
 * Object.defineProperty(event, ...) -- it threw "not an object" on openstreetmap),
 * fired in lifecycle order: DOMContentLoaded before load, handleEvent objects too. */
static void test_lifecycle_listeners_get_event(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var L=[];"
              "window.addEventListener('load', function(e){ Object.defineProperty(e,'x',{value:1});"
              "  L.push(e.type+':'+(e.target===document)+':'+(e.currentTarget===window)+':'+e.x); });"
              "document.addEventListener('DOMContentLoaded', {handleEvent:function(e){ L.push(e.type+':'+(e.target===document)); }});"
              "window.onload=function(e){ L.push('on:'+(e&&e.type)); };"
              "__fireDeferred(); L.join('|')",
              "DOMContentLoaded:true|load:true:true:1|on:load");
}

/* HTML 8.4.5: readyState is 'loading' while scripts run, 'interactive' at the first
 * readystatechange + DOMContentLoaded, 'complete' at the second readystatechange + load.
 * YouTube/reddit gate their bootstrap on readyState and never started while it stayed 'loading'. */
static void test_ready_state_walks_loading_interactive_complete(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var L=[document.readyState];"
              "document.addEventListener('readystatechange', function(){ L.push('rsc:'+document.readyState); });"
              "document.onreadystatechange=function(){ L.push('on:'+document.readyState); };"
              "document.addEventListener('DOMContentLoaded', function(){ L.push('dcl:'+document.readyState); });"
              "window.addEventListener('load', function(){ L.push('load:'+document.readyState); });"
              "__fireDeferred(); L.join('|')+'|end:'+document.readyState",
              "loading|rsc:interactive|on:interactive|dcl:interactive|rsc:complete|on:complete|load:complete|end:complete");
}

/* CE reactions are processed at the end of EVERY API call, also those made from inside a
 * callback: Polymer stamps its template in connectedCallback and the stamped child's
 * connectedCallback (ytd-page-manager.ready registers PAGE_TOKEN) must have run before the
 * parent's callback goes on. A flush guard that swallowed nested insertions starved YouTube. */
static void test_custom_element_reactions_nest(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var L=[];"
              "class Kid extends HTMLElement{ connectedCallback(){ L.push('kid'); } }"
              "class Par extends HTMLElement{ connectedCallback(){ L.push('par-start');"
              "  var k=document.createElement('x-kid'); this.appendChild(k); L.push('par-end'); } }"
              "customElements.define('x-kid',Kid); customElements.define('x-par',Par);"
              "document.body.appendChild(document.createElement('x-par')); L.join('|')",
              "par-start|kid|par-end");
}

/* Polymer stamps a template: importNode(template.content, true) yields a real fragment that the
 * insertion empties, so the children it carried must be reacted to, not the (now empty) fragment. */
static void test_custom_element_reactions_through_template_fragment(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var L=[];"
              "class Kid extends HTMLElement{ connectedCallback(){ L.push('kid'); } }"
              "class Par extends HTMLElement{ connectedCallback(){ L.push('par-start');"
              "  var t=document.createElement('template'); t.innerHTML='<x-kid></x-kid><b></b>';"
              "  this.appendChild(document.importNode(t.content,true)); L.push('par-end'); } }"
              "customElements.define('x-kid',Kid); customElements.define('x-par',Par);"
              "document.body.appendChild(document.createElement('x-par')); L.join('|')",
              "par-start|kid|par-end");
}

/* With hundreds of definitions (YouTube defines ~900 ytd-* names) a subtree inserted later must
 * still find the custom element deep inside it: the lookup cannot depend on one selector list
 * that names every definition. */
static void test_custom_element_found_in_subtree_with_many_definitions(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var L=[];"
              "for(var i=0;i<400;i++){ (function(i){ customElements.define('x-e'+i, class extends HTMLElement{"
              "  connectedCallback(){ L.push(i); } }); })(i); }"
              "var d=document.createElement('div'); d.innerHTML='<p><x-e399></x-e399><x-e0></x-e0></p>';"
              "document.body.appendChild(d); L.join(',')",
              "399,0");
}

/* HTMLAnchorElement URL decomposition (HTML 4.6.3): YouTube routes on a.pathname and died on
 * "cannot read property 'startsWith' of undefined". Other elements have no such members. */
static void test_anchor_url_decomposition(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var a=document.createElement('a'); a.href='https://ex.test:8080/p/q?x=1#h';"
              "[a.protocol,a.host,a.hostname,a.port,a.pathname,a.search,a.hash,a.origin,"
              " typeof document.createElement('div').pathname].join('|')",
              "https:|ex.test:8080|ex.test|8080|/p/q|?x=1|#h|https://ex.test:8080|undefined");
}

/* Fake host fetch: records what crossed to the parent and answers 200 JSON. */
typedef struct { char method[16]; char url[256]; char body[256]; char headers[256]; int calls; } fake_net;
static int fake_fetch(void *ctx, const char *method, const char *url, const char *body,
                      size_t body_len, const char *req_headers, int *out_status, char **out_body, size_t *out_len,
                      char **out_ctype, char **out_headers) {
    static const char RH[] = "ETag: \"abc\"\nX-Total: 7\nContent-Type: application/json\n";
    if (out_headers != NULL && (*out_headers = (char *)malloc(sizeof RH)) != NULL) memcpy(*out_headers, RH, sizeof RH);
    fake_net *n = (fake_net *)ctx;
    n->calls++;
    snprintf(n->method, sizeof n->method, "%s", method);
    snprintf(n->url, sizeof n->url, "%s", url);
    snprintf(n->headers, sizeof n->headers, "%s", req_headers ? req_headers : "");
    snprintf(n->body, sizeof n->body, "%.*s", (int)(body_len < 255 ? body_len : 255), body ? body : "");
    static const char R[] = "{\"ok\":1}";
    *out_status = 200;
    *out_body = (char *)malloc(sizeof R);
    *out_ctype = (char *)malloc(sizeof "application/json");
    if (*out_body == NULL || *out_ctype == NULL) return -1;
    memcpy(*out_body, R, sizeof R);
    memcpy(*out_ctype, "application/json", sizeof "application/json");
    *out_len = sizeof R - 1;
    return 0;
}

/* Trusted fetch speaks the Fetch Standard's classes: a Request as input (method/body
 * carried), Response instances (blob/clone/headers), Response as a pure container
 * (new Response(blob).text()), an already-aborted signal rejects with AbortError
 * without touching the network. */
static void test_trusted_fetch_request_response(void **state) {
    fixture *f = (fixture *)*state;
    fake_net net; memset(&net, 0, sizeof net);
    assert_int_equal(jd_install_xhr(f->ctx, fake_fetch, &net), JD_OK);
    EXPECT(f, "var out=[]; var rq=new Request('https://a.test/x',{method:'POST',body:'p=1',headers:{'X-A':'1'}});"
              "fetch(rq).then(function(r){ out.push(r instanceof Response, r.status, r.headers.get('content-type'));"
              "  return r.clone().json(); }).then(function(j){ out.push(j.ok); });"
              "new Response(new Blob(['hi'])).text().then(function(t){ out.push(t); });"
              "var ac=new AbortController(); ac.abort();"
              "fetch('https://a.test/y',{signal:ac.signal}).catch(function(e){ out.push(e.name); });"
              "[rq.method, rq.url, rq.headers.get('x-a'), typeof Response.json].join(',')",
              "POST,https://a.test/x,1,function");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "out.join(',')", "true,200,application/json,hi,AbortError,1");
    assert_int_equal(net.calls, 1);
    assert_string_equal(net.method, "POST");
    assert_string_equal(net.body, "p=1");
}

/* isEqualNode (DOM 4.4): same type, name, attribute SET (order-free) and equal
 * children, recursively; isSameNode is identity. Next.js head reconciliation. */
static void test_ext_is_equal_node(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "function mk(h){ var d=document.createElement('div'); d.innerHTML=h; return d.firstElementChild; }"
              "var a=mk('<meta name=\"x\" content=\"1\">'), b=mk('<meta content=\"1\" name=\"x\">'),"
              "    c=mk('<meta name=\"x\" content=\"2\">'), p=mk('<p>t<b>u</b></p>'), q=mk('<p>t<b>u</b></p>'),"
              "    r=mk('<p>t<b>v</b></p>');"
              "[a.isEqualNode(b), a.isEqualNode(c), p.isEqualNode(q), p.isEqualNode(r), a.isEqualNode(null),"
              " a.isSameNode(a), a.isSameNode(b)].join(',')",
              "true,false,true,false,false,true,false");
}

/* Real Text/Comment nodes (spec/dom.md 9, spec/js_dom.md 7h): childNodes/firstChild/
 * siblings see text, createTextNode inserts and renders, data setters write through,
 * append() accepts strings, splitText, TreeWalker SHOW_TEXT. */
static void test_text_nodes_are_real(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var p=document.createElement('p'); p.innerHTML='t<b>u</b><!--c-->v';"
              "var cn=p.childNodes;"
              "[cn.length, cn[0].nodeType, cn[0].data, cn[0].nodeName, cn[2].nodeType, cn[2].data,"
              " p.firstChild===cn[0], cn[0].nextSibling===cn[1], cn[3].previousSibling===cn[2],"
              " p.lastChild.nodeValue, cn[0].parentNode===p, cn[0] instanceof Text, cn[2] instanceof Comment,"
              " p.children.length].join(',')",
              "4,3,t,#text,8,c,true,true,true,v,true,true,true,1");
    EXPECT(f, "var x=document.createTextNode('X'); p.appendChild(x); x.data='Y';"
              "p.append('Z', document.createComment('k')); p.firstChild.textContent='T';"
              "[p.textContent, p.childNodes.length, x.length, p.lastChild.nodeType].join(',')",
              "TuvYZ,7,1,8");
    EXPECT(f, "var s=document.createElement('span'); s.textContent='hello'; var t=s.firstChild;"
              "var tail=t.splitText(2);"
              "[t.data, tail.data, s.childNodes.length, t.nextSibling===tail].join(',')",
              "he,llo,2,true");
    EXPECT(f, "var w=document.createTreeWalker(p, NodeFilter.SHOW_TEXT), out=[];"
              "while(w.nextNode()) out.push(w.currentNode.data); out.join('|')",
              "T|u|v|Y|Z");
    EXPECT(f, "var m=document.getElementById('main'); var tn=document.createTextNode('tail-text');"
              "m.appendChild(tn); [m.textContent.indexOf('tail-text')>=0, m.contains(tn),"
              " tn.compareDocumentPosition(m)&8?1:0].join(',')", "true,true,1");
}

/* navigator.sendBeacon (trusted only): queued POST through the same gated host
 * call, sent after the current task; true when queued, false for a non-URL. */
static void test_trusted_send_beacon(void **state) {
    fixture *f = (fixture *)*state;
    fake_net net; memset(&net, 0, sizeof net);
    /* this fixture has no js_env, so stand in a bare navigator */
    EXPECT(f, "__G.navigator={}; typeof navigator.sendBeacon", "undefined");   /* untrusted */
    assert_int_equal(jd_install_xhr(f->ctx, fake_fetch, &net), JD_OK);
    EXPECT(f, "[navigator.sendBeacon('https://a.test/b', new URLSearchParams({k:'v'})),"
              " navigator.sendBeacon('')].join(',')", "true,false");
    assert_int_equal(net.calls, 0);                          /* not sent inline */
    EXPECT(f, "__tickTimers(0); 1", "1");
    assert_int_equal(net.calls, 1);
    assert_string_equal(net.method, "POST");
    assert_string_equal(net.url, "https://a.test/b");
    assert_string_equal(net.body, "k=v");
}

/* The real navigator is non-extensible (anti-fp), yet analytics code patches it the way it
 * would a normal object: `navigator.sendBeacon = function(){...}` (old.reddit's bootstrap
 * module). A plain data property on the prototype made that strict-mode write throw
 * "object is not extensible"; an accessor with a setter takes the override without
 * making the navigator extensible. */
static void test_trusted_send_beacon_can_be_patched(void **state) {
    fixture *f = (fixture *)*state;
    fake_net net; memset(&net, 0, sizeof net);
    EXPECT(f, "__G.navigator=Object.preventExtensions(Object.create({})); typeof navigator", "object");
    assert_int_equal(jd_install_xhr(f->ctx, fake_fetch, &net), JD_OK);
    EXPECT(f, "(function(){'use strict'; var o=navigator.sendBeacon;"
              " navigator.sendBeacon=function(){return 'patched';};"
              " return navigator.sendBeacon()+','+typeof o;})()", "patched,function");
    /* the navigator itself stays non-extensible, and no own property appeared */
    EXPECT(f, "[Object.isExtensible(navigator),Object.keys(navigator).length].join(',')", "false,0");
}

/* Request headers the page sets reach the host fetch: XHR.setRequestHeader (repeated names
 * combine) and fetch() init.headers / a Request's headers. Before this setRequestHeader was a
 * no-op, so no Accept/Content-Type/CSRF header ever left the page (reddit's login partial
 * answers 406 to a bare Accept). */
static void test_trusted_request_headers_cross_to_host(void **state) {
    fixture *f = (fixture *)*state;
    fake_net net; memset(&net, 0, sizeof net);
    assert_int_equal(jd_install_xhr(f->ctx, fake_fetch, &net), JD_OK);
    EXPECT(f, "(function(){ var x=new XMLHttpRequest(); x.open('GET','https://a.test/p');"
              " x.setRequestHeader('Accept','text/vnd.reddit.partial+html');"
              " x.setRequestHeader('X-T','1'); x.setRequestHeader('x-t','2'); x.send(); return 'sent'; })()", "sent");
    assert_string_equal(net.headers, "Accept: text/vnd.reddit.partial+html\nX-T: 1, 2\n");
    EXPECT(f, "(function(){ fetch('https://a.test/q',{method:'POST',body:'{}',"
              "headers:{'Content-Type':'application/json','X-Csrf':'tok'}}); return 'sent'; })()", "sent");
    assert_non_null(strstr(net.headers, "content-type: application/json"));
    assert_non_null(strstr(net.headers, "x-csrf: tok"));
    EXPECT(f, "(function(){ fetch('https://a.test/r'); return 'sent'; })()", "sent");
    assert_string_equal(net.headers, "");
}

/* XMLHttpRequest is an EventTarget with the whole lifecycle (YouTube's loader calls
 * d.addEventListener("loadend", ...) and died with "not a function"), exposes the response
 * headers, an upload target, and abort(). Events of an async request arrive after send();
 * the result fields are settled by then. */
static void test_trusted_xhr_event_target_and_response_headers(void **state) {
    fixture *f = (fixture *)*state;
    fake_net net; memset(&net, 0, sizeof net);
    assert_int_equal(jd_install_xhr(f->ctx, fake_fetch, &net), JD_OK);
    EXPECT(f, "(function(){ var x=new XMLHttpRequest(); window.__ev=[];"
              " x.addEventListener('loadstart',function(){__ev.push('ls')});"
              " x.addEventListener('readystatechange',function(){__ev.push('rs'+x.readyState)});"
              " x.addEventListener('progress',function(){__ev.push('pr')});"
              " x.addEventListener('load',function(){__ev.push('ld')});"
              " x.onloadend=function(){__ev.push('le')};"
              " x.open('GET','https://a.test/p'); x.send();"
              " return [typeof x.addEventListener, typeof x.upload.addEventListener, x.status, x.readyState,"
              " x.getResponseHeader('X-Total'), x.getResponseHeader('etag'), x.getAllResponseHeaders().indexOf('x-total: 7')>=0,"
              " x.responseText.length>0, __ev.join('+')].join(','); })()",
           "function,function,200,4,7,\"abc\",true,true,rs1");   /* only open()'s rs1 so far: the rest is deferred */
    EXPECT(f, "(function(){ var x=new XMLHttpRequest(), L=[];"
              " x.addEventListener('abort',function(){L.push('abort')}); x.addEventListener('load',function(){L.push('load')});"
              " x.addEventListener('loadend',function(){L.push('end')}); x.open('GET','https://a.test/p'); x.send(); x.abort();"
              " return L.join(',')+':'+x.readyState+':'+x.status; })()", "abort,end:0:0");
    EXPECT(f, "(function(){ var x=new XMLHttpRequest(), L=[]; x.open('GET','https://a.test/p',false);"
              " x.onload=function(){L.push('load:'+x.readyState)}; x.onreadystatechange=function(){L.push('rs'+x.readyState)};"
              " x.send(); return L.join(','); })()", "rs2,rs3,rs4,load:4");
    EXPECT(f, "(function(){ var x=new XMLHttpRequest(); x.open('POST','https://a.test/p'); x.send('a=1');"
              " try{ x.setRequestHeader('X-A','1'); return 'no-throw'; }catch(e){ return e.name; } })()", "InvalidStateError");
}

static void test_trusted_fetch_exposes_response_headers(void **state) {
    fixture *f = (fixture *)*state;
    fake_net net; memset(&net, 0, sizeof net);
    assert_int_equal(jd_install_xhr(f->ctx, fake_fetch, &net), JD_OK);
    EXPECT(f, "(function(){ window.__r=''; fetch('https://a.test/q').then(function(r){"
              " window.__r=[r.status,r.ok,r.headers.get('x-total'),r.headers.get('ETag'),r.headers.get('content-type')].join('|'); });"
              " return 'started'; })()", "started");
    js_pump_jobs(f->ctx, 64);
    EXPECT(f, "__r", "200|true|7|\"abc\"|application/json");
}

/* XMLSerializer.serializeToString serializes elements, text and DocumentFragments. faceplate-partial
 * (reddit's partial loader) feeds it a fragment and used to get "" back. */
static void test_xml_serializer_covers_fragments_and_text(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "(function(){ var p=document.createElement('p'); p.innerHTML='<i>q</i> &amp; r';"
              " return new XMLSerializer().serializeToString(p); })()", "<p><i>q</i> &amp; r</p>");
    EXPECT(f, "(function(){ var fr=document.createDocumentFragment(), a=document.createElement('a'), b=document.createElement('b');"
              " a.setAttribute('href','/x'); fr.appendChild(a); fr.appendChild(document.createTextNode('1 < 2')); fr.appendChild(b);"
              " return new XMLSerializer().serializeToString(fr); })()", "<a href=\"/x\"></a>1 &lt; 2<b></b>");
    EXPECT(f, "new XMLSerializer().serializeToString(document.createTextNode('a<b'))", "a&lt;b");
    EXPECT(f, "new XMLSerializer().serializeToString(null)", "");
}

/* --- Custom Elements v1 (spec/js_custom_elements.md) --- */

/* The constructor runs when the page creates an element it has defined. */
static void test_ce_create_runs_constructor(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "(function(){ class XBox extends HTMLElement { constructor(){ super(); this.delegate={k:1}; } }"
              " customElements.define('x-box', XBox); var e=document.createElement('x-box');"
              " return [e instanceof XBox, e instanceof HTMLElement, e.delegate&&e.delegate.k,"
              " e.tagName.toLowerCase(), customElements.get('x-box')===XBox, e.constructor===XBox].join(','); })()",
           "true,true,1,x-box,true,true");
}

/* An element already in the document is upgraded when its tag gets defined. */
static void test_ce_define_upgrades_existing(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "(function(){ document.getElementById('main').innerHTML='<x-up id=\"u1\" a=\"1\"></x-up>';"
              " var seen=[]; class XUp extends HTMLElement { constructor(){ super(); this.ran=1; }"
              " static get observedAttributes(){ return ['a']; }"
              " attributeChangedCallback(n,o,v){ seen.push(n+':'+o+'>'+v); } }"
              " customElements.define('x-up', XUp); var u=document.getElementById('u1');"
              " return [u.ran, u instanceof XUp, seen.join('|')].join(','); })()", "1,true,a:null>1");
}

/* connected / disconnected follow the element's presence in the document. */
static void test_ce_connected_callbacks(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "(function(){ var log=[]; class XC extends HTMLElement {"
              " connectedCallback(){ log.push('c'); } disconnectedCallback(){ log.push('d'); } }"
              " customElements.define('x-c', XC); var e=document.createElement('x-c'); __ceFlush();"
              " log.push('made'); var m=document.getElementById('main'); m.appendChild(e); __ceFlush();"
              " m.removeChild(e); __ceFlush(); return log.join(','); })()", "made,c,d");
}

static void test_ce_attribute_changed(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "(function(){ var log=[]; class XA extends HTMLElement {"
              " static get observedAttributes(){ return ['v']; }"
              " attributeChangedCallback(n,o,v){ log.push(n+':'+o+'>'+v); } }"
              " customElements.define('x-a', XA); var e=document.createElement('x-a');"
              " document.getElementById('main').appendChild(e); __ceFlush();"
              " e.setAttribute('v','1'); __ceFlush(); e.setAttribute('v','2'); __ceFlush();"
              " e.setAttribute('other','z'); __ceFlush(); return log.join('|'); })()", "v:null>1|v:1>2");
}

/* Insertion, removal and innerHTML reconcile at once: a script that appends an element and
 * reads its state on the next line sees the connectedCallback already done. */
static void test_ce_sync_on_mutation(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "(function(){ var log=[]; class XS extends HTMLElement {"
              " connectedCallback(){ log.push('c'); } disconnectedCallback(){ log.push('d'); } }"
              " customElements.define('x-s', XS); var m=document.getElementById('main');"
              " var e=document.createElement('x-s'); m.appendChild(e); log.push('appended');"
              " m.removeChild(e); log.push('removed');"
              " m.innerHTML='<x-s></x-s>'; log.push('html');"
              " return log.join(','); })()", "c,appended,d,removed,c,html");
}

static void test_ce_define_validation(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "(function(){ var r=[];"
              " try{ customElements.define('nohyphen', class extends HTMLElement{}); }catch(e){ r.push(e.name); }"
              " customElements.define('x-d', class extends HTMLElement{});"
              " try{ customElements.define('x-d', class extends HTMLElement{}); }catch(e){ r.push(e.name); }"
              " try{ new HTMLElement(); }catch(e){ r.push(e.name); }"
              " r.push(customElements.whenDefined('x-d') instanceof Promise);"
              " return r.join(','); })()", "SyntaxError,NotSupportedError,TypeError,true");
}

/* Dedicated Worker in its own realm (spec/js_dom.md 7i). */
static void pump_ticks(fixture *f, int n) {
    for (int i = 0; i < n; ++i) {
        js_pump_jobs(f->ctx, 64);
        EXPECT(f, "__tickTimers(0); 1", "1");
    }
}

static void test_trusted_worker(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "typeof Worker", "undefined");                 /* not without trust */
    assert_int_equal(jt_enable_worker(NULL), JD_ERR_NULL_ARG);
    assert_int_equal(jt_enable_worker(f->ctx), JD_OK);
    EXPECT(f, "[typeof Worker, typeof __realmNew, typeof __realmClone].join()", "function,undefined,undefined");
    EXPECT(f, "var log=[];"
              "var src='self.onmessage=function(e){ postMessage({echo:e.data.n*2, arr:e.data.a instanceof Array,"
              " win:typeof window, doc:typeof document, me:self===this}); };"
              " importScripts(\"data:text/javascript,var imp=5\"); setTimeout(function(){ postMessage(\"imp\"+imp); },0);';"
              "var w=new Worker(URL.createObjectURL(new Blob([src])));"
              "w.onmessage=function(e){ log.push(typeof e.data==='string'?e.data:JSON.stringify(e.data)); };"
              "w.postMessage({n:21,a:[1]});"
              "var bad=new Worker(URL.createObjectURL(new Blob(['throw new TypeError(\"bad\")'])));"
              "bad.onerror=function(e){ log.push('err:'+(e.message.indexOf('bad')>=0)); };"
              "var dw=new Worker('data:text/javascript,postMessage(7)');"
              "dw.addEventListener('message',function(e){ log.push('data:'+e.data); });"
              "var tw=new Worker('data:text/javascript,onmessage=function(){ postMessage(1); }');"
              "tw.onmessage=function(){ log.push('terminated-but-got'); }; tw.terminate(); tw.postMessage(0);"
              "var cw=new Worker('data:text/javascript,close(); postMessage(\"after-close\")');"
              "cw.onmessage=function(e){ log.push(e.data); };"
              "var mw=new Worker('data:text/javascript,1',{type:'module'}); mw.onerror=function(){ log.push('module-err'); };"
              "var nw=new Worker('ftp://x/y'); nw.onerror=function(){ log.push('scheme-err'); };"
              "log.length", "0");                                  /* nothing is delivered inline */
    pump_ticks(f, 6);
    EXPECT(f, "log.slice().sort().join('|')",
              "data:7|err:true|imp5|module-err|scheme-err|"
              "{\"echo\":42,\"arr\":true,\"win\":\"undefined\",\"doc\":\"undefined\",\"me\":true}");
}

/* --- video shim --- */

/* No `video` variable defined: shim is a no-op, no iframe created. */
static void test_video_shim_no_video(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(jd_inject_video_shim(f->ctx), JD_OK);
    assert_int_equal(dom_get_by_tag(f->idx, "iframe", NULL, 0), 0);
}

/* `video[0..2]` defined with absolute iframe src: shim creates iframe from
 * video[1] (default provider, Magi), ignoring video[0] (Desu). */
static void test_video_shim_uses_index_1(void **state) {
    fixture *f = (fixture *)*state;
    js_result r;
    assert_int_equal(js_eval(f->ctx,
        "var video = [];"
        "video[0] = '<iframe src=\"https://srv0.example/vid\"></iframe>';"
        "video[1] = '<iframe src=\"https://srv1.example/vid\"></iframe>';"
        "video[2] = '<iframe src=\"https://srv2.example/vid\"></iframe>';",
        strlen("var video = [];"
        "video[0] = '<iframe src=\"https://srv0.example/vid\"></iframe>';"
        "video[1] = '<iframe src=\"https://srv1.example/vid\"></iframe>';"
        "video[2] = '<iframe src=\"https://srv2.example/vid\"></iframe>';"), &r), JS_OK);
    js_result_free(&r);
    assert_int_equal(jd_inject_video_shim(f->ctx), JD_OK);
    dom_node_id ids[2];
    assert_int_equal(dom_get_by_tag(f->idx, "iframe", ids, 2), 1);
    size_t slen = 0;
    const char *src = dom_get_attribute(f->idx, ids[0], "src", &slen);
    assert_non_null(src);
    assert_string_equal(src, "https://srv1.example/vid");
}

/* `video_data` (prepared by the page) takes precedence over `video[]`: when
 * both exist, the shim creates an iframe from video_data, not video[1]. */
static void test_video_shim_video_data_wins(void **state) {
    fixture *f = (fixture *)*state;
    js_result r;
    assert_int_equal(js_eval(f->ctx,
        "var video = [];"
        "video[0] = '<iframe src=\"https://srv0.example/vid\"></iframe>';"
        "video[1] = '<iframe src=\"https://srv1.example/vid\"></iframe>';"
        "var video_data = '<iframe src=\"https://data.example/vid\"></iframe>';",
        strlen("var video = [];"
        "video[0] = '<iframe src=\"https://srv0.example/vid\"></iframe>';"
        "video[1] = '<iframe src=\"https://srv1.example/vid\"></iframe>';"
        "var video_data = '<iframe src=\"https://data.example/vid\"></iframe>';"), &r), JS_OK);
    js_result_free(&r);
    assert_int_equal(jd_inject_video_shim(f->ctx), JD_OK);
    dom_node_id ids[2];
    assert_int_equal(dom_get_by_tag(f->idx, "iframe", ids, 2), 1);
    size_t slen = 0;
    const char *src = dom_get_attribute(f->idx, ids[0], "src", &slen);
    assert_non_null(src);
    assert_string_equal(src, "https://data.example/vid");
}

/* `video_data` with relative src gets resolved against location.protocol and
 * location.hostname. Only for relative URLs starting with '/'. */
static void test_video_shim_relative_url_resolved(void **state) {
    fixture *f = (fixture *)*state;
    set_https_location(f, "https://anime.test/dragon-ball/1");
    js_result r;
    assert_int_equal(js_eval(f->ctx,
        "var video_data = '<iframe src=\"/jkplayer/umv?e=abc\"></iframe>';",
        strlen("var video_data = '<iframe src=\"/jkplayer/umv?e=abc\"></iframe>';"), &r), JS_OK);
    js_result_free(&r);
    assert_int_equal(jd_inject_video_shim(f->ctx), JD_OK);
    dom_node_id ids[2];
    assert_int_equal(dom_get_by_tag(f->idx, "iframe", ids, 2), 1);
    size_t slen = 0;
    const char *src = dom_get_attribute(f->idx, ids[0], "src", &slen);
    assert_non_null(src);
    assert_string_equal(src, "https://anime.test/jkplayer/umv?e=abc");
}

/* `video[1]` is empty string: no iframe created. */
static void test_video_shim_empty_html(void **state) {
    fixture *f = (fixture *)*state;
    js_result r;
    assert_int_equal(js_eval(f->ctx,
        "var video = []; video[1] = '';",
        strlen("var video = []; video[1] = '';"), &r), JS_OK);
    js_result_free(&r);
    assert_int_equal(jd_inject_video_shim(f->ctx), JD_OK);
    assert_int_equal(dom_get_by_tag(f->idx, "iframe", NULL, 0), 0);
}

/* NULL context returns JD_ERR_NULL_ARG. */
static void test_video_shim_null_ctx(void **state) {
    (void)state;
    assert_int_equal(jd_inject_video_shim(NULL), JD_ERR_NULL_ARG);
}

/* --- C-level video extraction from scripts --- */

/* jkanime-style: video[0..4] with absolute iframe URLs.
 * jd_video_from_scripts creates ONE <iframe> for the best server (video[1]). */
static void test_video_from_scripts_jkanime_style(void **state) {
    fixture *f = (fixture *)*state;
    const char *script =
        "video[0] = '<iframe class=\"pc\" src=\"https://jk/jkplayer/um?e=A\"></iframe>';"
        "video[1] = '<iframe class=\"pc\" src=\"https://jk/jkplayer/umv?e=B\"></iframe>';"
        "video[2] = '<iframe class=\"pc\" src=\"https://jk/jkplayer/um?e=C\"></iframe>';";
    const char *texts[] = {script};
    size_t lens[] = {strlen(script)};
    size_t n = jd_video_from_scripts(f->idx, texts, lens, 1, "https://jkanime.net/one-piece/1");
    /* Should create 1 iframe (video[1], the best candidate). */
    assert_int_equal(n, 1);
    dom_node_id ids[4];
    size_t niframe = dom_get_by_tag(f->idx, "iframe", ids, 4);
    assert_int_equal(niframe, 1);
    /* Verify the iframe is video[1] (Magi server). */
    size_t sl = 0;
    const char *s0 = dom_get_attribute(f->idx, ids[0], "src", &sl);
    assert_non_null(s0);
    assert_string_equal(s0, "https://jk/jkplayer/umv?e=B");
}

/* video_data with variable-to-variable assignment: video_data = video[N].
 * The C extractor falls back to the video[N] pattern for the URL. */
static void test_video_from_scripts_video_data_is_variable(void **state) {
    fixture *f = (fixture *)*state;
    const char *script =
        "video[0] = '<iframe src=\"https://jk/jkplayer/um?e=X\"></iframe>';"
        "video[1] = '<iframe src=\"https://jk/jkplayer/umv?e=Y\"></iframe>';"
        "if(video[1] !== undefined) { var video_data = video[1]; }";
    const char *texts[] = {script};
    size_t lens[] = {strlen(script)};
    size_t n = jd_video_from_scripts(f->idx, texts, lens, 1, "https://jkanime.net/one-piece/1");
    /* video_data = video[1] is not a string literal, but the video[N] scan
     * finds video[1]. Should create 1 iframe (best candidate). */
    assert_int_equal(n, 1);
}

/* jkanime-style with root-relative URLs that get resolved. */
static void test_video_from_scripts_relative_resolved(void **state) {
    fixture *f = (fixture *)*state;
    const char *script =
        "video[1] = '<iframe src=\"/jkplayer/umv?e=ABC\"></iframe>';";
    const char *texts[] = {script};
    size_t lens[] = {strlen(script)};
    size_t n = jd_video_from_scripts(f->idx, texts, lens, 1,
                                      "https://anime.test/dragon-ball/1");
    assert_int_equal(n, 1);
    dom_node_id ids[2];
    assert_int_equal(dom_get_by_tag(f->idx, "iframe", ids, 2), 1);
    size_t sl = 0;
    const char *src = dom_get_attribute(f->idx, ids[0], "src", &sl);
    assert_non_null(src);
    assert_string_equal(src, "https://anime.test/jkplayer/umv?e=ABC");
}

/* video_data = '<iframe ...>' string literal (jkanime's pattern for some pages). */
static void test_video_from_scripts_video_data_string(void **state) {
    fixture *f = (fixture *)*state;
    const char *script =
        "var video_data = '<iframe src=\"https://data.example/vid\"></iframe>';";
    const char *texts[] = {script};
    size_t lens[] = {strlen(script)};
    size_t n = jd_video_from_scripts(f->idx, texts, lens, 1, NULL);
    assert_int_equal(n, 1);
    dom_node_id ids[2];
    assert_int_equal(dom_get_by_tag(f->idx, "iframe", ids, 2), 1);
    size_t sl = 0;
    const char *src = dom_get_attribute(f->idx, ids[0], "src", &sl);
    assert_non_null(src);
    assert_string_equal(src, "https://data.example/vid");
}

/* No video data at all: should create zero iframes. */
static void test_video_from_scripts_no_video(void **state) {
    fixture *f = (fixture *)*state;
    const char *script = "var x = 42;";
    const char *texts[] = {script};
    size_t lens[] = {strlen(script)};
    size_t n = jd_video_from_scripts(f->idx, texts, lens, 1, NULL);
    assert_int_equal(n, 0);
    assert_int_equal(dom_get_by_tag(f->idx, "iframe", NULL, 0), 0);
}

/* NULL args return 0 gracefully. */
static void test_video_from_scripts_null_args(void **state) {
    (void)state;
    const char *s = "video[0] = '<iframe src=\"x\"></iframe>';";
    size_t l = strlen(s);
    const char *txt[] = {s};
    size_t ln[] = {l};
    assert_int_equal(jd_video_from_scripts(NULL, txt, ln, 1, NULL), 0);
    assert_int_equal(jd_video_from_scripts(NULL, NULL, ln, 1, NULL), 0);
    assert_int_equal(jd_video_from_scripts(NULL, txt, NULL, 1, NULL), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_install_null_args),
        cmocka_unit_test_setup_teardown(test_get_element_by_id, setup, teardown),
        cmocka_unit_test_setup_teardown(test_node_count, setup, teardown),
        cmocka_unit_test_setup_teardown(test_by_class_and_tag, setup, teardown),
        cmocka_unit_test_setup_teardown(test_navigation, setup, teardown),
        cmocka_unit_test_setup_teardown(test_attributes, setup, teardown),
        cmocka_unit_test_setup_teardown(test_document_order, setup, teardown),
        cmocka_unit_test_setup_teardown(test_invalid_handles, setup, teardown),
        cmocka_unit_test_setup_teardown(test_methods_are_frozen, setup, teardown),
        cmocka_unit_test_setup_teardown(test_no_io_with_dom, setup, teardown),
        cmocka_unit_test_setup_teardown(test_document_shim_present, setup, teardown),
        cmocka_unit_test_setup_teardown(test_query_selector_from_js, setup, teardown),
        cmocka_unit_test_setup_teardown(test_element_matches_closest_query_from_js, setup, teardown),
        cmocka_unit_test_setup_teardown(test_node_identity_is_cached, setup, teardown),
        cmocka_unit_test_setup_teardown(test_element_traversal, setup, teardown),
        cmocka_unit_test_setup_teardown(test_classlist_backs_class_attr, setup, teardown),
        cmocka_unit_test_setup_teardown(test_document_fragment_reparents, setup, teardown),
        cmocka_unit_test_setup_teardown(test_fragment_clone_chain_does_not_throw, setup, teardown),
        cmocka_unit_test_setup_teardown(test_modern_globals_do_not_throw, setup, teardown),
        cmocka_unit_test_setup_teardown(test_intersection_observer_fires_synthetically, setup, teardown),
        cmocka_unit_test_setup_teardown(test_style_write_through, setup, teardown),
        cmocka_unit_test_setup_teardown(test_get_computed_style_inline, setup, teardown),
        cmocka_unit_test_setup_teardown(test_resize_observer_fires_synthetically, setup, teardown),
        cmocka_unit_test_setup_teardown(test_dom_mutators_are_sealed_after_install, setup, teardown),
        cmocka_unit_test_setup_teardown(test_mutation_observer_reports_child_list, setup, teardown),
        cmocka_unit_test_setup_teardown(test_mutation_observer_reports_attributes, setup, teardown),
        cmocka_unit_test_setup_teardown(test_mutation_observer_subtree_character_data_and_take_records, setup, teardown),
        cmocka_unit_test_setup_teardown(test_mutation_observer_accepts_document_target, setup, teardown),
        cmocka_unit_test_setup_teardown(test_no_invented_jquery_and_svg_interfaces_exist, setup, teardown),
        cmocka_unit_test_setup_teardown(test_uncaught_timer_error_fires_window_error_event, setup, teardown),
        cmocka_unit_test_setup_teardown(test_unhandled_rejection_event, setup, teardown),
        cmocka_unit_test_setup_teardown(test_template_content_is_a_real_fragment, setup, teardown),
        cmocka_unit_test_setup_teardown(test_element_nodevalue_is_null, setup, teardown),
        cmocka_unit_test_setup_teardown(test_element_local_name_namespace, setup, teardown),
        cmocka_unit_test_setup_teardown(test_dataset_is_a_domstringmap, setup, teardown),
        cmocka_unit_test_setup_teardown(test_attributes_are_iterable, setup, teardown),
        cmocka_unit_test_setup_teardown(test_document_parentnode_surface, setup, teardown),
        cmocka_unit_test_setup_teardown(test_performance_observer_supported_entry_types, setup, teardown),
        cmocka_unit_test_setup_teardown(test_shadow_root_is_event_target_and_observable, setup, teardown),
        cmocka_unit_test_setup_teardown(test_element_members_survive_prototype_swaps_and_detached_calls, setup, teardown),
        cmocka_unit_test_setup_teardown(test_dynamic_inline_script_runs_once_on_insert, setup, teardown),
        cmocka_unit_test_setup_teardown(test_dynamic_script_src_loads_async_and_reports_load_or_error, setup, teardown),
        cmocka_unit_test_setup_teardown(test_shadow_mirror_append, setup, teardown),
        cmocka_unit_test_setup_teardown(test_shadow_mirror_inner_html, setup, teardown),
        cmocka_unit_test_setup_teardown(test_shadow_insert_fragment, setup, teardown),
        cmocka_unit_test_setup_teardown(test_slot_assigned_nodes, setup, teardown),
        cmocka_unit_test_setup_teardown(test_shadow_insert_upgrades_custom_elements, setup, teardown),
        cmocka_unit_test_setup_teardown(test_match_media_normalized_viewport, setup, teardown),
        cmocka_unit_test_setup_teardown(test_document_node_identity, setup, teardown),
        cmocka_unit_test_setup_teardown(test_element_attributes_named_node_map, setup, teardown),
        cmocka_unit_test_setup_teardown(test_intl_stub_does_not_throw, setup, teardown),
        cmocka_unit_test_setup_teardown(test_url_constructor_parses_components, setup, teardown),
        cmocka_unit_test_setup_teardown(test_url_search_params, setup, teardown),
        cmocka_unit_test_setup_teardown(test_settimeout_chains_across_rounds, setup, teardown),
        cmocka_unit_test_setup_teardown(test_document_title_set_reflects_in_tree, setup, teardown),
        cmocka_unit_test_setup_teardown(test_set_text_content_reflects_in_tree, setup, teardown),
        cmocka_unit_test_setup_teardown(test_set_text_content_detach_is_memory_safe, setup, teardown),
        cmocka_unit_test_setup_teardown(test_document_is_not_io, setup, teardown),
        cmocka_unit_test_setup_teardown(test_create_append_renders_in_tree, setup, teardown),
        cmocka_unit_test_setup_teardown(test_set_attribute_makes_queryable, setup, teardown),
        cmocka_unit_test_setup_teardown(test_element_dataset_via_proxy, setup, teardown),
        cmocka_unit_test_setup_teardown(test_element_has_attribute, setup, teardown),
        cmocka_unit_test_setup_teardown(test_element_remove_attribute, setup, teardown),
        cmocka_unit_test_setup_teardown(test_element_src_href_are_strings, setup, teardown),
        cmocka_unit_test_setup_teardown(test_append_cycle_is_rejected, setup, teardown),
        cmocka_unit_test_setup_teardown(test_onload_runs_and_mutates, setup, teardown),
        cmocka_unit_test_setup_teardown(test_settimeout_flushed_by_pump, setup, teardown),
        cmocka_unit_test_setup_teardown(test_inner_html_builds_and_queryable, setup, teardown),
        cmocka_unit_test_setup_teardown(test_inner_html_getter_serializes, setup, teardown),
        cmocka_unit_test_setup_teardown(test_storage_is_ephemeral, setup, teardown),
        cmocka_unit_test_setup_teardown(test_cookie_and_referrer_leak_nothing, setup, teardown),
        cmocka_unit_test_setup_teardown(test_cookie_jar_enabled_for_trusted_host, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ambient_apis_do_not_throw, setup, teardown),
        cmocka_unit_test_setup_teardown(test_location_reads_real_components, setup, teardown),
        cmocka_unit_test_setup_teardown(test_location_pathname_defaults_slash, setup, teardown),
        cmocka_unit_test_setup_teardown(test_location_href_set_captures_raw, setup, teardown),
        cmocka_unit_test_setup_teardown(test_location_replace_sets_replace_flag, setup, teardown),
        cmocka_unit_test_setup_teardown(test_location_assign_and_window_last_wins, setup, teardown),
        cmocka_unit_test_setup_teardown(test_no_nav_request_when_idle, setup, teardown),
        cmocka_unit_test_setup_teardown(test_local_page_captures_nav, setup, teardown),
        cmocka_unit_test(test_set_location_null_ctx),
        cmocka_unit_test(test_console_captures_levels),
        cmocka_unit_test(test_console_formats_errors_and_elements),
        cmocka_unit_test(test_console_object_and_throwing_tostring),
        cmocka_unit_test(test_console_methods_are_writable),
        cmocka_unit_test(test_unhandled_rejection_report_carries_the_message),
        cmocka_unit_test(test_console_null_buffer_is_noop),
        cmocka_unit_test(test_console_null_ctx),
        cmocka_unit_test_setup_teardown(test_event_add_event_listener_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_onkeydown_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_input_handler_fires_with_value, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_prevent_default_suppresses, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_no_handler_allows_default, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_null_args, setup, teardown),
        cmocka_unit_test_setup_teardown(test_focus_add_event_listener_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_blur_onblur_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_scroll_add_event_listener_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_scroll_onscroll_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_focus_blur_scroll_prevent_default, setup, teardown),
        cmocka_unit_test_setup_teardown(test_focus_blur_scroll_no_handler_allows_default, setup, teardown),
        cmocka_unit_test_setup_teardown(test_focus_blur_scroll_null_args, setup, teardown),
        cmocka_unit_test_setup_teardown(test_mouse_add_event_listener_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_mouse_onmouseout_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_mouse_mousemove_sees_coords, setup, teardown),
        cmocka_unit_test_setup_teardown(test_mouse_multi_event_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_mouse_prevent_default_suppresses, setup, teardown),
        cmocka_unit_test_setup_teardown(test_mouse_no_handler_allows_default, setup, teardown),
        cmocka_unit_test_setup_teardown(test_mouse_null_args, setup, teardown),
        cmocka_unit_test(test_click_install_null_args),
        cmocka_unit_test_setup_teardown(test_click_add_event_listener_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_click_onclick_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_click_prevent_default, setup, teardown),
        cmocka_unit_test_setup_teardown(test_click_no_handler_allows_default, setup, teardown),
        cmocka_unit_test_setup_teardown(test_submit_add_event_listener_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_submit_onsubmit_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_submit_prevent_default, setup, teardown),
        cmocka_unit_test_setup_teardown(test_submit_no_handler_allows_default, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_click_bubbles_to_ancestor, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_capture_target_bubble_order, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_stop_propagation, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_stop_immediate_propagation, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_multiple_click_listeners, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_remove_listener, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_once, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_delegated_prevent_default, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_submit_bubbles_to_document, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_keydown_bubbles_with_data, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_focus_does_not_bubble, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_handler_property_slot, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_script_dispatch_custom_event, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_listener_exception_continues, setup, teardown),
        cmocka_unit_test_setup_teardown(test_event_handle_event_object, setup, teardown),
        cmocka_unit_test_setup_teardown(test_geom_absent_is_zero, setup, teardown),
        cmocka_unit_test_setup_teardown(test_geom_installed_is_real, setup, teardown),
        cmocka_unit_test_setup_teardown(test_io_real_follows_scroll, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ro_real_reports_size_changes, setup, teardown),
        cmocka_unit_test_setup_teardown(test_repl_api_is_repl_only_and_nondestructive, setup, teardown),
        cmocka_unit_test_setup_teardown(test_freebug_html_pane_outlines_the_dom, setup, teardown),
        cmocka_unit_test_setup_teardown(test_freebug_css_pane_lists_rules_computed_and_box, setup, teardown),
        cmocka_unit_test_setup_teardown(test_freebug_script_pane_lists_and_numbers_source, setup, teardown),
        cmocka_unit_test_setup_teardown(test_freebug_net_pane_empty_and_selector_is_data, setup, teardown),
        cmocka_unit_test_setup_teardown(test_freebug_dom_and_storage_panes, setup, teardown),
        cmocka_unit_test_setup_teardown(test_freebug_completion_follows_typed_accessors_only, setup, teardown),
        cmocka_unit_test_setup_teardown(test_repl_api_inspect_and_event_listeners, setup, teardown),
        cmocka_unit_test_setup_teardown(test_platform_interfaces_and_events, setup, teardown),
        cmocka_unit_test_setup_teardown(test_platform_dommatrix_and_imagedata, setup, teardown),
        cmocka_unit_test_setup_teardown(test_platform_form_controls, setup, teardown),
        cmocka_unit_test_setup_teardown(test_form_elements_collection, setup, teardown),
        cmocka_unit_test_setup_teardown(test_shadow_styles_are_scoped, setup, teardown),
        cmocka_unit_test_setup_teardown(test_fragment_queries, setup, teardown),
        cmocka_unit_test_setup_teardown(test_tree_walker_reverse_navigation, setup, teardown),
        cmocka_unit_test_setup_teardown(test_create_html_document_is_detached, setup, teardown),
        cmocka_unit_test_setup_teardown(test_url_members_shadowed_on_non_anchor, setup, teardown),
        cmocka_unit_test_setup_teardown(test_slotted_nodes_unrendered_when_slot_hidden, setup, teardown),
        cmocka_unit_test_setup_teardown(test_slotted_nodes_unrendered_through_nested_shadow, setup, teardown),
        cmocka_unit_test_setup_teardown(test_indexeddb_core, setup, teardown),
        cmocka_unit_test_setup_teardown(test_geolocation_fixed_coordinates, setup, teardown),
        cmocka_unit_test_setup_teardown(test_platform_streams, setup, teardown),
        cmocka_unit_test_setup_teardown(test_platform_element_surface, setup, teardown),
        cmocka_unit_test_setup_teardown(test_repl_rules_lists_matching_rules_by_cascade, setup, teardown),
        cmocka_unit_test_setup_teardown(test_io_untrusted_stays_synthetic, setup, teardown),
        cmocka_unit_test(test_geom_null_ctx),
        cmocka_unit_test_setup_teardown(test_history_push_replace_update_location, setup, teardown),
        cmocka_unit_test_setup_teardown(test_history_cross_origin_is_security_error, setup, teardown),
        cmocka_unit_test_setup_teardown(test_history_popstate_restores_entry, setup, teardown),
        cmocka_unit_test_setup_teardown(test_history_go_records_delta, setup, teardown),
        cmocka_unit_test_setup_teardown(test_history_is_bounded, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ws_absent_until_enabled, setup, teardown),
        cmocka_unit_test_setup_teardown(test_frames_top_document_parent_is_self, setup, teardown),
        cmocka_unit_test_setup_teardown(test_frames_child_document_posts_to_parent_and_top, setup, teardown),
        cmocka_unit_test_setup_teardown(test_frames_iframe_discovery_and_child_post, setup, teardown),
        cmocka_unit_test_setup_teardown(test_frames_message_delivery_sets_origin_and_source, setup, teardown),
        cmocka_unit_test_setup_teardown(test_frames_oversize_payload_rejected, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ws_lifecycle_records_ops_and_fires_events, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ws_rejects_plaintext_and_caps, setup, teardown),
        cmocka_unit_test_setup_teardown(test_storage_untrusted_stays_ephemeral, setup, teardown),
        cmocka_unit_test_setup_teardown(test_storage_seeded_and_dirty_snapshot, setup, teardown),
        cmocka_unit_test_setup_teardown(test_storage_quota_exceeded, setup, teardown),
        cmocka_unit_test_setup_teardown(test_dom_ordered_insertion, setup, teardown),
        cmocka_unit_test_setup_teardown(test_dom_childnode_mixins, setup, teardown),
        cmocka_unit_test_setup_teardown(test_dom_interface_prototypes, setup, teardown),
        cmocka_unit_test_setup_teardown(test_dom_template_content, setup, teardown),
        cmocka_unit_test_setup_teardown(test_current_script_values_and_methods, setup, teardown),
        cmocka_unit_test_setup_teardown(test_current_script_is_the_real_element, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ext_tree_navigation, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ext_compare_document_position, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ext_shadow_root, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ext_tree_walker_terminates, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ext_document_helpers, setup, teardown),
        cmocka_unit_test_setup_teardown(test_shims_survive_globalthis_rebinding, setup, teardown),
        cmocka_unit_test_setup_teardown(test_interfaces_window_and_canvas, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ext_blob_family, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ext_insert_adjacent, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ext_prototype_delegation, setup, teardown),
        cmocka_unit_test_setup_teardown(test_intl_surface, setup, teardown),
        cmocka_unit_test_setup_teardown(test_lifecycle_listeners_get_event, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ready_state_walks_loading_interactive_complete, setup, teardown),
        cmocka_unit_test_setup_teardown(test_custom_element_reactions_nest, setup, teardown),
        cmocka_unit_test_setup_teardown(test_custom_element_reactions_through_template_fragment, setup, teardown),
        cmocka_unit_test_setup_teardown(test_custom_element_found_in_subtree_with_many_definitions, setup, teardown),
        cmocka_unit_test_setup_teardown(test_anchor_url_decomposition, setup, teardown),
        cmocka_unit_test_setup_teardown(test_trusted_fetch_request_response, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ext_is_equal_node, setup, teardown),
        cmocka_unit_test_setup_teardown(test_text_nodes_are_real, setup, teardown),
        cmocka_unit_test_setup_teardown(test_xml_serializer_covers_fragments_and_text, setup, teardown),
        cmocka_unit_test_setup_teardown(test_trusted_request_headers_cross_to_host, setup, teardown),
        cmocka_unit_test_setup_teardown(test_trusted_xhr_event_target_and_response_headers, setup, teardown),
        cmocka_unit_test_setup_teardown(test_trusted_fetch_exposes_response_headers, setup, teardown),
        cmocka_unit_test_setup_teardown(test_trusted_send_beacon_can_be_patched, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ce_create_runs_constructor, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ce_define_upgrades_existing, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ce_connected_callbacks, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ce_attribute_changed, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ce_sync_on_mutation, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ce_define_validation, setup, teardown),
        cmocka_unit_test_setup_teardown(test_trusted_send_beacon, setup, teardown),
        cmocka_unit_test_setup_teardown(test_trusted_worker, setup, teardown),
        cmocka_unit_test_setup_teardown(test_video_shim_no_video, setup, teardown),
        cmocka_unit_test_setup_teardown(test_video_shim_uses_index_1, setup, teardown),
        cmocka_unit_test_setup_teardown(test_video_shim_video_data_wins, setup, teardown),
        cmocka_unit_test_setup_teardown(test_video_shim_relative_url_resolved, setup, teardown),
        cmocka_unit_test_setup_teardown(test_video_shim_empty_html, setup, teardown),
        cmocka_unit_test(test_video_shim_null_ctx),
        cmocka_unit_test_setup_teardown(test_video_from_scripts_jkanime_style, setup, teardown),
        cmocka_unit_test_setup_teardown(test_video_from_scripts_video_data_is_variable, setup, teardown),
        cmocka_unit_test_setup_teardown(test_video_from_scripts_relative_resolved, setup, teardown),
        cmocka_unit_test_setup_teardown(test_classlist_is_iterable_like_domtokenlist, setup, teardown),
        cmocka_unit_test_setup_teardown(test_canvas_element_inherits_html_element, setup, teardown),
        cmocka_unit_test_setup_teardown(test_frames_blank_iframe_has_writable_document, setup, teardown),
        cmocka_unit_test_setup_teardown(test_video_from_scripts_video_data_string, setup, teardown),
        cmocka_unit_test_setup_teardown(test_video_from_scripts_no_video, setup, teardown),
        cmocka_unit_test(test_video_from_scripts_null_args),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
