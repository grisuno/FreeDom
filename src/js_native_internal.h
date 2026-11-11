/*
 * Internal half of js_native (spec/js_native.md): the one way host platform code is
 * evaluated. Not part of the project API -- it names engine types.
 */
#ifndef FREEDOM_JS_NATIVE_INTERNAL_H
#define FREEDOM_JS_NATIVE_INTERNAL_H

#include <stddef.h>

#include "quickjs.h"

/* Evaluates HOST code as a global script. Every function compiled inside this call keeps no
 * source text, so the page sees it as "[native code]". The runtime flag is restored on every
 * path; page code is never compiled under it. Returns what JS_Eval returns (caller frees). */
JSValue jn_host_eval(JSContext *c, const char *src, size_t len, const char *name);

/* One engine value the host keeps for the lifetime of a context, out of the page's reach
 * (it is not a property of anything). JS_UNDEFINED until set; the context frees it.
 * Implemented in js_sandbox.c, which owns the context. NULL for a NULL context. */
struct js_context;
JSValue *js_host_slot(struct js_context *ctx);

#endif /* FREEDOM_JS_NATIVE_INTERNAL_H */
