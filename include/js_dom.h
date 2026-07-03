#ifndef FREEDOM_JS_DOM_H
#define FREEDOM_JS_DOM_H

#include "dom.h"
#include "freebug.h"
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
typedef struct jd_opaque {
    dom_index       *idx;
    jd_click_state  *click;
} jd_opaque;

/* Installs the `dom` global (and a small standard `document` shim) into the sandbox,
 * backed by idx. The bridge is read-mostly: it also exposes memory-safe mutators
 * (textContent / document.title) used by allowlisted page scripts; these mutate the
 * underlying tree, never the index structure, so idx is no longer const. idx must
 * outlive ctx. Intended to be called on a freshly created context, before any
 * untrusted script runs. opaque must outlive ctx. */
jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque);

/* Installs a capturing `console` (log/info/warn/error/debug + no-op group/time/...)
 * that appends each call's formatted message into log, so the developer console
 * ("Freebug") can show page-script output and errors. The buffer pointer is held in
 * the engine runtime opaque (unreachable from script); log must outlive ctx. Pass
 * log == NULL to make console a silent no-op. Call after jd_install (it overrides
 * the no-op console the document shim defines). ctx == NULL => JD_ERR_NULL_ARG. */
jd_status jd_install_console(js_context *ctx, fb_buffer *log);

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

/* Installs a real, read-only `location` (and document.location / document.URL) over
 * the page's URL, and arms JS-navigation capture: location.href= / assign / replace /
 * reload / window.location= record the RAW requested string (never executed, never
 * resolved here) for the trusted parent to gate. href is the full page URL (may be a
 * file:// URL); parts, if non-NULL, is its url_split decomposition for the component
 * reads (NULL => only href is known, the rest fall back to stub defaults). Call after
 * jd_install, on the page's context. ctx == NULL => JD_ERR_NULL_ARG. */
jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts);

/* Reads and CLEARS the navigation the page's JS requested (globalThis.__navReq). Returns
 * 1 and copies the raw (unresolved) target into buf (bounded, NUL-terminated) with
 * *replace set from location.replace; returns 0 when no (non-empty) request is pending.
 * The caller MUST gate the raw target with ln_resolve before acting (Zero Trust). */
int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace);

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
                           const char *body, size_t body_len,
                           int *out_status, char **out_body, size_t *out_body_len,
                           char **out_ctype);

/* Installs XMLHttpRequest + fetch backed by `fn` (called with `fetch_ctx`). This is the
 * ONLY path that gives page JS network access, and it is gated by the caller: install it
 * ONLY for a host present in BOTH allow.conf AND js.conf (the sovereignty boundary). When
 * not installed, XMLHttpRequest/fetch stay undefined (Same-Origin-by-construction holds
 * for every other site). fn/fetch_ctx must outlive ctx. Call after jd_install, on the
 * page's context. ctx == NULL / fn == NULL => JD_ERR_NULL_ARG. */
jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx);

#endif /* FREEDOM_JS_DOM_H */
