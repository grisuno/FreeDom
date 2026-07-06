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
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "dom.h"
#include "html_parse.h"
#include "js_dom.h"
#include "js_sandbox.h"
#include "url.h"

static const char HTML[] =
    "<!DOCTYPE html><html><head><title>T</title></head>"
    "<body>"
    "<div id=\"main\" class=\"container box\">"
    "<p class=\"text\">Hello</p>"
    "<p class=\"text muted\">World</p>"
    "<button id=\"go\" class=\"btn\">Go</button>"
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
    EXPECT(f, "document.getElementById('main').children.length", "3");
    EXPECT(f, "document.getElementById('main').firstElementChild.tagName", "P");
    EXPECT(f, "document.getElementById('main').childElementCount", "3");
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

/* Identity-safe ambient globals: present (no throws) but leak nothing. */
static void test_storage_is_ephemeral(void **state) {
    fixture *f = (fixture *)*state;
    EXPECT(f, "localStorage.setItem('k','v'); localStorage.getItem('k')", "v");
    EXPECT(f, "localStorage.getItem('absent')", "null");
    EXPECT(f, "sessionStorage.setItem('a','1'); sessionStorage.length", "1");
}

static void test_cookie_and_referrer_leak_nothing(void **state) {
    fixture *f = (fixture *)*state;
    /* cookie set is a no-op; get is always empty; referrer empty. */
    EXPECT(f, "document.cookie='track=1'; document.cookie", "");
    EXPECT(f, "document.referrer", "");
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
    jd_opaque op;
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
    assert_string_equal(fb_buffer_at(&log, 0)->text, "[object Object]");
    assert_string_equal(fb_buffer_at(&log, 1)->text, "<unprintable>");

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
        cmocka_unit_test_setup_teardown(test_storage_is_ephemeral, setup, teardown),
        cmocka_unit_test_setup_teardown(test_cookie_and_referrer_leak_nothing, setup, teardown),
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
        cmocka_unit_test(test_console_object_and_throwing_tostring),
        cmocka_unit_test(test_console_null_buffer_is_noop),
        cmocka_unit_test(test_console_null_ctx),
        cmocka_unit_test(test_click_install_null_args),
        cmocka_unit_test_setup_teardown(test_click_add_event_listener_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_click_onclick_fires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_click_prevent_default, setup, teardown),
        cmocka_unit_test_setup_teardown(test_click_no_handler_allows_default, setup, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
