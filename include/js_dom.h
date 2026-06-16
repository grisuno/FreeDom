#ifndef FREEDOM_JS_DOM_H
#define FREEDOM_JS_DOM_H

#include "dom.h"
#include "js_sandbox.h"

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

/* Installs the read-only `dom` global into the sandbox, backed by idx.
 * idx must outlive ctx. Intended to be called on a freshly created context,
 * before any untrusted script runs. */
jd_status jd_install(js_context *ctx, const dom_index *idx);

#endif /* FREEDOM_JS_DOM_H */
