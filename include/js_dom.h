#ifndef FREEDOM_JS_DOM_H
#define FREEDOM_JS_DOM_H

#include "dom.h"
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

/* Installs the `dom` global (and a small standard `document` shim) into the sandbox,
 * backed by idx. The bridge is read-mostly: it also exposes memory-safe mutators
 * (textContent / document.title) used by allowlisted page scripts; these mutate the
 * underlying tree, never the index structure, so idx is no longer const. idx must
 * outlive ctx. Intended to be called on a freshly created context, before any
 * untrusted script runs. */
jd_status jd_install(js_context *ctx, dom_index *idx);

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

#endif /* FREEDOM_JS_DOM_H */
