#ifndef FREEDOM_JS_DOM_H
#define FREEDOM_JS_DOM_H

#include "dom.h"
#include "freebug.h"
#include "js_geom.h"
#include "js_sandbox.h"
#include "url.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * js_dom — the DOM <-> JS bridge.
 *
 * Exposes a frozen, read-only `dom` global to untrusted script, backed by a
 * dom_index. Nodes are opaque integer handles validated on every call; no live
 * engine object or node object is exposed. The QuickJS backend stays
 * encapsulated: no JS* type appears here.
 *
 * See spec/js_dom.md for the full contract (the JS-visible surface).
 */

typedef enum jd_status {
    JD_OK = 0,
    JD_ERR_NULL_ARG,  /* ctx or idx was NULL */
    JD_ERR_OOM,       /* allocation failed building the global */
    JD_ERR_INTERNAL   /* engine context unreachable or install failed */
} jd_status;

/* Per-context state shared between the binding layer and the trusted caller.
 * Lives in the caller's stack (or struct) and must outlive ctx. The caller
 * zero-initialises it; jd_install wires it into the engine's context opaque. */
typedef struct jd_click_state jd_click_state;

/* Tracks iframes already processed by jd_process_iframes, to avoid re-fetching
 * the same iframe on repeated calls. Lives in jd_opaque (caller's stack), not
 * in a static — eliminates cross-page state leaks. Zero-init => fresh state. */
#define JD_IFRAME_TRACK_MAX 16
typedef struct jd_iframe_track {
    dom_node_id processed[JD_IFRAME_TRACK_MAX];
    size_t      nprocessed;
} jd_iframe_track;

typedef struct jd_opaque {
    dom_index       *idx;
    const jg_table  *geom;  /* laid-out geometry (trusted host only), NULL = none */
    int            (*computed)(void *ctx, dom_node_id h, const char *prop, char *out, size_t cap);
    void            *computed_ctx; /* cascade provider (trusted host only), NULL = none */
    jd_click_state  *click;
    jd_iframe_track  iframe_track;
} jd_opaque;

/* Installs the `dom` global (and a small standard `document` shim) into the sandbox,
 * backed by idx. The bridge is read-mostly: it also exposes memory-safe mutators
 * (textContent / document.title) used by allowlisted page scripts; these mutate the
 * underlying tree, never the index structure, so idx is no longer const. idx must
 * outlive ctx. Intended to be called on a freshly created context, before any
 * untrusted script runs. opaque must outlive ctx. */
jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque);

/* Moves a context installed over a placeholder index (jd_install on a blank document, done
 * while the worker was idle) onto the real page: `from` is the opaque it was installed with,
 * `to` the opaque the page will use (may be the same). The natives read the index through the
 * opaque at CALL time, so repointing it is all the install state there is. Fails (JD_ERR_INTERNAL)
 * when `from` is not the context's current opaque. */
jd_status jd_rebind(js_context *ctx, dom_index *idx, jd_opaque *from, jd_opaque *to);

/* Installs a capturing `console` (log/info/warn/error/debug + no-op group/time/...)
 * that appends each call's formatted message into log, so the developer console
 * ("Freebug") can show page-script output and errors. The buffer pointer is held in
 * the engine runtime opaque (unreachable from script); log must outlive ctx. Pass
 * log == NULL to make console a silent no-op. Call after jd_install (it overrides
 * the no-op console the document shim defines). ctx == NULL => JD_ERR_NULL_ARG. */
jd_status jd_install_console(js_context *ctx, fb_buffer *log);

/* Freebug command-line API ($, $$, inspect, keys, values, getEventListeners,
 * monitorEvents/unmonitorEvents). Installed ONLY into the REPL worker, as non-enumerable
 * globals: page scripts never see them and an existing page global (jQuery's `$`) is
 * never replaced. Read-only helpers over the sealed document facade -- no new capability.
 * spec/freebug_repl.md. */
jd_status jd_install_repl_api(js_context *ctx);

/* Longest external-CSS text handed to rules(): anything beyond is cut, never an error. */
#define JD_REPL_CSS_MAX ((size_t)(4u * 1024u * 1024u))

/* Hands the parent's fetched stylesheet text to the REPL's rules(el). Call it right before
 * jd_install_repl_api (the shim reads and deletes the carrier global, so a page script never
 * sees it). css == NULL clears. ctx == NULL => JD_ERR_NULL_ARG. */
jd_status jd_set_repl_css(js_context *ctx, const char *css, size_t len);

/* Installs navigator.geolocation answering with exactly (lat, lon, accuracy_m): the user's
 * configured place (spec/identity.md), no sensor, no network. Call it ONLY for a trusted host
 * with geolocation set to fixed. Out-of-range or non-finite values are refused with
 * JD_ERR_INTERNAL and nothing is installed. The numbers cross as values, never as source text.
 * ctx == NULL => JD_ERR_NULL_ARG. */
/* Installs indexedDB (+ IDBKeyRange and friends) over memory that lives as long as the page:
 * stores, indexes, cursors, key ranges and rollback-capable transactions. Call it ONLY for a
 * trusted host (allow.conf AND js.conf); an untrusted page keeps `indexedDB` undefined. Nothing
 * is written to disk. ctx == NULL => JD_ERR_NULL_ARG. */
jd_status jd_install_indexeddb(js_context *ctx);

jd_status jd_install_geolocation(js_context *ctx, double lat, double lon, double accuracy_m);

/* Installs (or, with geom == NULL, removes) the laid-out geometry that
 * getBoundingClientRect/offset/client/scroll and the real viewport read. The table
 * must be finished and aggregated (jg_aggregate) and must outlive its installation;
 * it is sent by the trusted parent only for an allow.conf AND js.conf host
 * (spec/js_geom.md). Without it every measurement is zero and the viewport stays
 * normalized. ctx == NULL => JD_ERR_NULL_ARG. */
jd_status jd_set_geometry(js_context *ctx, const jg_table *geom);

/* Installs the cascade provider behind dom.computed(h, prop) and the real
 * getComputedStyle (spec/js_computed_style.md). fn writes the computed value of the
 * kebab-case `prop` of element h into out (cap bytes) and returns its length, 0 for
 * an unknown property (out ""); with prop == NULL it writes every supported
 * property name, newline separated. fn == NULL removes it (dom.computed -> null and
 * getComputedStyle falls back to the inline style). Trusted hosts only: the caller
 * is the gate. ctx must outlive the JS context. */
typedef int (*jd_computed_fn)(void *ctx, dom_node_id h, const char *prop, char *out, size_t cap);
jd_status jd_set_computed(js_context *ctx, jd_computed_fn fn, void *fn_ctx);

/* Click-event state. Allocate with jd_click_state_new(), free with
 * jd_click_state_free(). Bound to one context via jd_install_events(). */
jd_click_state *jd_click_state_new(void);
void jd_click_state_free(jd_click_state *s);

/* Installs addEventListener('click', ...) and element.onclick capture on the
 * document element wrapper. state must outlive ctx. Call after jd_install. */
jd_status jd_install_events(js_context *ctx, jd_click_state *state);

/* Fires the click event for node_id. Returns 1 if the default action should still
 * run (no handler registered, or handlers ran without calling preventDefault()),
 * and 0 if a handler called preventDefault(). ctx == NULL => 1 (fail-open for the
 * default action, since no script can prevent it). */
int jd_fire_click(js_context *ctx, dom_node_id node_id);

/* Fires the submit event on the form with node_id. Walks up the DOM from the given
 * node to find the form; dispatches any registered submit handler and returns 0 if
 * preventDefault() was called, 1 if the default (form submission) should proceed.
 * ctx == NULL or no form found => 1 (fail-open: submission proceeds). */
int jd_fire_submit(js_context *ctx, dom_node_id form_node_id);

/* Fires a generic DOM event on node_id. event_type is the event name string
 * (e.g. "keydown", "input", "change", "focus", "blur", "mouseover", "mouseout").
 * key is the KeyboardEvent.key value (may be NULL for non-keyboard events).
 * key_code is the keyCode/charCode value (0 for non-keyboard events).
 * value is the current element value for input/change events (may be NULL).
 * Returns 1 if the default action should proceed, 0 if a handler called
 * preventDefault(). ctx == NULL => 1 (fail-open). */
int jd_fire_event(js_context *ctx, dom_node_id node_id,
                  const char *event_type,
                  const char *key, int key_code,
                  const char *value);

/* Fires a mouse DOM event on node_id. event_type is the event name
 * (e.g. "mouseover", "mouseout", "mousemove", "mouseenter", "mouseleave", "wheel").
 * client_x and client_y are viewport-relative coordinates (pass 0 for wheel events).
 * button is the mouse button: -1 = none/move, 0 = left, 1 = middle, 2 = right.
 * Returns 1 if the default action should proceed, 0 if a handler called
 * preventDefault(). ctx == NULL => 1 (fail-open). */
int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,
                        const char *event_type,
                        int client_x, int client_y, int button);



/* Enables and seeds the page's in-memory session cookie jar (document.cookie). Call ONLY
 * for a trusted host (allow.conf AND js.conf); until called, document.cookie is a no-op
 * ('' on get, ignored on set) so untrusted sites see no cookies (Zero Knowledge). cookies
 * is a "name=value; name=value" string (may be NULL/empty). It is passed as a JS string
 * VALUE, never interpolated into source (the hostile bytes cannot inject code). Call after
 * jd_install. ctx == NULL => JD_ERR_NULL_ARG. */
jd_status jd_set_cookies(js_context *ctx, const char *cookies);

/* Serialises the page's current cookie jar ("name=value; ...") into buf (bounded,
 * NUL-terminated) and returns its length, so the trusted parent can fold JS-set cookies
 * back into its ephemeral network jar. Returns 0 when the jar is disabled/empty or on any
 * error. Never throws into the page. */
int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz);


/* Host fetch callback for XMLHttpRequest/fetch. The JS sandbox NEVER touches a socket:
 * this proxies a subresource request to the TRUSTED parent, which re-applies the FULL
 * network policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching.
 * `method` and `url` are the request line (url is the RAW string from the page; the
 * parent resolves/validates it); `body`/`body_len` is the request body (empty for GET).
 * On success returns 0 and sets *out_status (HTTP status, 0 if unknown), *out_body /
 * *out_body_len (response bytes, malloc'd -- the bridge frees with free()), and
 * *out_ctype (Content-Type, malloc'd, may be NULL). Returns non-zero on refusal/error
 * (blocked host, policy failure, over budget): the XHR completes with status 0 and an
 * empty body (fail-closed, never throws to the page in a way that leaks why). */
typedef int (*jd_fetch_fn)(void *ctx, const char *method, const char *url,
                           const char *body, size_t body_len, const char *req_headers,
                           int *out_status, char **out_body, size_t *out_body_len,
                           char **out_ctype, char **out_headers);

/* req_headers: the page-supplied request headers ("Name: value" lines, may be NULL/empty).
 * UNTRUSTED text from the page; the trusted parent re-filters it (rp_sanitize_request_headers)
 * before it can reach a socket. */

/* Installs XMLHttpRequest + fetch backed by `fn` (called with `fetch_ctx`). This is the
 * ONLY path that gives page JS network access, and it is gated by the caller: install it
 * ONLY for a host present in BOTH allow.conf AND js.conf (the sovereignty boundary). When
 * not installed, XMLHttpRequest/fetch stay undefined (Same-Origin-by-construction holds
 * for every other site). fn/fetch_ctx must outlive ctx. Call after jd_install, on the
 * page's context. ctx == NULL / fn == NULL => JD_ERR_NULL_ARG. */
jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx);

/* Deferred variant (spec/subreq_async.md): queues the request with the host and returns 0 AT ONCE
 * (non-zero = refused); the reply is handed back later, in issue order, through jd_net_deliver. */
typedef int (*jd_fetch_async_fn)(void *ctx, const char *method, const char *url,
                                 const char *body, size_t body_len, const char *req_headers);

/* jd_install_xhr plus the deferred hook: async XMLHttpRequest and fetch() use `afn`; sync XHR keeps
 * `fn`. afn == NULL is exactly jd_install_xhr. */
jd_status jd_install_xhr_ex(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx,
                            jd_fetch_async_fn afn, void *afetch_ctx);

/* Hands the OLDEST queued deferred request its reply (rc != 0 = refused/failed, status 0) and runs
 * its callback. `ms` is the parent's measured wall time of the fetch (Freebug's Net panel). The caller drains microtasks afterwards. JD_ERR_INTERNAL when none is queued. */
jd_status jd_net_deliver(js_context *ctx, int rc, int status, const char *body, size_t len,
                         const char *ctype, const char *hdrs, int ms);

/* Injects a JS shim that creates <iframe> elements from a page's `video[]` array
 * (or `video_data` variable) into the DOM, emulating the missing `video_min.js`
 * script. Must be called AFTER all page scripts have run (so video[] exists) and
 * BEFORE jd_process_iframes() (so iframes are in the DOM for it to process).
 * ctx == NULL => JD_ERR_NULL_ARG. */
jd_status jd_inject_video_shim(js_context *ctx);

/* Processes any <iframe> elements in the DOM that were created during JS execution
 * (via createElement/appendChild or innerHTML): for each iframe with a non-empty `src`,
 * fetches the content via `fn` (the same fetch mechanism as XHR), scans the response for
 * video URLs (.m3u8 then .mp4 patterns), and creates <video> elements in the document for
 * any found. Does NOT re-process iframes already processed (tracks them by node_id in
 * jd_opaque.iframe_track, caller stack — not static). Call after every DOM mutation that
 * may have added iframes (innerHTML setter, appendChild). fn/fetch_ctx must outlive ctx.
 * ctx == NULL => no-op. */
void jd_process_iframes(js_context *ctx, dom_index *idx,
                        jd_fetch_fn fn, void *fetch_ctx);

/* Creates <iframe> elements in the DOM from video data (`video[N]` / `video_data`)
 * found in inline script text, WITHOUT executing JS. Runs before the pre-script
 * preserve_view snapshot so video elements survive jQuery corruption fallback.
 * Scans each script for patterns matching video array/data assignments, extracts the
 * iframe src URL, and creates an <iframe> in the DOM. page_url resolves relative URLs
 * (may be NULL). Returns the number of iframes created (0 if none/error). */
size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,
                              const size_t *script_lens, size_t nscripts,
                              const char *page_url);

/* location / history / JS-navigation capture live in their own module. */
#include "js_location.h"

/* Reconciles Custom Elements (spec/js_custom_elements.md): upgrades the elements whose tag was
 * just defined and fires attributeChanged/connected/disconnected callbacks. The embedder calls
 * it after each script, so the page sees the lifecycle a real browser would have run. A context
 * without the facade, or NULL, is a no-op. */
void jd_flush_custom_elements(js_context *ctx);

#endif /* FREEDOM_JS_DOM_H */
