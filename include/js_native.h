/*
 * js_native (jn_) -- the host platform describes itself the way a native browser does.
 * Contract: spec/js_native.md.
 *
 * The web platform Freedom exposes is largely JavaScript evaluated before the page. A page
 * can tell that apart from a real browser with no special API (Function.prototype.toString,
 * Object.prototype.toString, the shape of navigator). jn_seal closes that gap: host
 * functions report "[native code]", interfaces carry their Symbol.toStringTag, singletons
 * are instances of their interface. It adds no capability.
 */
#ifndef FREEDOM_JS_NATIVE_H
#define FREEDOM_JS_NATIVE_H

#ifdef __cplusplus
#error "Freedom is pure C11; C++ is not supported."
#endif

#include "js_sandbox.h"

/* Seals the host surface of `ctx`. Call once, after every shim is installed and before the
 * first page script; calling it again is harmless. Returns 0, or -1 on a NULL context or an
 * engine failure (the page then simply runs with the unsealed surface). */
int jn_seal(js_context *ctx);

#endif /* FREEDOM_JS_NATIVE_H */
