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
    EXPECT(f, "var mh=0; var mo=new MutationObserver(function(){mh++;});"
              "mo.observe(document.body,{childList:true}); __fireDeferred(); mh", "1");
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

static void test_mutation_observer_fires_synthetically(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "var mh=0; var mo=new MutationObserver(function(){mh++;});"
              "mo.observe(document.body,{childList:true}); __fireDeferred(); mh", "1");
    EXPECT(f, "var mh2=0; var mo2=new MutationObserver(function(){mh2++;});"
              "mo2.observe(document.body,{childList:true}); mo2.disconnect();"
              "__fireDeferred(); mh2", "0");
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
        "document.getElementById('main').textContent='X';"
        "var g=document.getElementById('go'); g===null?'gone':g.tagName", &r), JS_OK);
    assert_non_null(r.value);
    /* 'go' is detached but alive: its tag still reads safely. */
    assert_string_equal(r.value, "BUTTON");
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

/* Fake host fetch: records what crossed to the parent and answers 200 JSON. */
typedef struct { char method[16]; char url[256]; char body[256]; int calls; } fake_net;
static int fake_fetch(void *ctx, const char *method, const char *url, const char *body,
                      size_t body_len, int *out_status, char **out_body, size_t *out_len,
                      char **out_ctype) {
    fake_net *n = (fake_net *)ctx;
    n->calls++;
    snprintf(n->method, sizeof n->method, "%s", method);
    snprintf(n->url, sizeof n->url, "%s", url);
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
        cmocka_unit_test_setup_teardown(test_mutation_observer_fires_synthetically, setup, teardown),
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
        cmocka_unit_test(test_geom_null_ctx),
        cmocka_unit_test_setup_teardown(test_history_push_replace_update_location, setup, teardown),
        cmocka_unit_test_setup_teardown(test_history_cross_origin_is_security_error, setup, teardown),
        cmocka_unit_test_setup_teardown(test_history_popstate_restores_entry, setup, teardown),
        cmocka_unit_test_setup_teardown(test_history_go_records_delta, setup, teardown),
        cmocka_unit_test_setup_teardown(test_history_is_bounded, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ws_absent_until_enabled, setup, teardown),
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
        cmocka_unit_test_setup_teardown(test_trusted_fetch_request_response, setup, teardown),
        cmocka_unit_test_setup_teardown(test_ext_is_equal_node, setup, teardown),
        cmocka_unit_test_setup_teardown(test_text_nodes_are_real, setup, teardown),
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
        cmocka_unit_test_setup_teardown(test_video_from_scripts_video_data_string, setup, teardown),
        cmocka_unit_test_setup_teardown(test_video_from_scripts_no_video, setup, teardown),
        cmocka_unit_test(test_video_from_scripts_null_args),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
