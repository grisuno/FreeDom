#ifndef FREEDOM_JS_LOCATION_H
#define FREEDOM_JS_LOCATION_H

#include <stddef.h>

#include "js_dom.h"
#include "js_sandbox.h"
#include "url.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * js_location -- real read-only `location`, JS-navigation capture and session
 * `history` for page script (spec/js_dom.md 7e). Navigation and history writes are
 * only RECORDED here; the trusted parent gates every one of them.
 */

/* Installs a real, read-only `location` (and document.location / document.URL) over
 * the page's URL, and arms JS-navigation capture: location.href= / assign / replace /
 * reload / window.location= record the RAW requested string (never executed, never
 * resolved here) for the trusted parent to gate. href is the full page URL (may be a
 * file:// URL); parts, if non-NULL, is its url_split decomposition for the component
 * reads (NULL => only href is known, the rest fall back to stub defaults). Call after
 * jd_install, on the page's context. ctx == NULL => JD_ERR_NULL_ARG. */
jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts);

/* Bound on a document's history entries and on the operations one response carries
 * (spec/js_dom.md 7e). Past it pushState behaves as replaceState. */
#define JD_HIST_MAX 256

/* Drains the history operations page JS performed since the last call: an owned
 * string of lines "P <url>\n" (pushState) / "R <url>\n" (replaceState), URLs absolute
 * and already same-origin-checked by the worker (the parent re-checks), or NULL when
 * there were none. *go (optional) receives the net history.back/forward/go delta,
 * also cleared. */
char *jd_take_history(js_context *ctx, int *go);

/* Moves the page's history to entry index (the parent went Back/Forward within the
 * same document): updates location and dispatches popstate (and hashchange when only
 * the fragment changed) on window. Returns 1 when applied, 0 when index is out of
 * range or no location is installed. */
int jd_pop_state(js_context *ctx, int index);

/* Reads and CLEARS the navigation the page's JS requested (globalThis.__navReq). Returns
 * 1 and copies the raw (unresolved) target into buf (bounded, NUL-terminated) with
 * *replace set from location.replace; returns 0 when no (non-empty) request is pending.
 * The caller MUST gate the raw target with ln_resolve before acting (Zero Trust). */
int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace);

#endif /* FREEDOM_JS_LOCATION_H */
