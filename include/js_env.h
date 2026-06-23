#ifndef FREEDOM_JS_ENV_H
#define FREEDOM_JS_ENV_H

#include "js_sandbox.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * js_env — the anti_fp <-> JS environment bridge.
 *
 * Installs a frozen, read-only browser environment (`navigator`, `screen`,
 * `performance`) into the sandbox and replaces `Date.now` with a coarsened
 * version, all backed by the pure anti_fp primitives. This is the wiring of the
 * anti-fingerprinting doctrine to the JS surface: every identity value is a
 * normalized constant shared by all Freedom users, and the clocks are coarsened
 * to a 100 ms grid to defeat high-resolution timing.
 *
 * Same Zero-Trust shape as js_dom: no live engine objects, properties are
 * non-writable / non-configurable, the objects are sealed. It does not use the
 * engine context opaque (js_dom owns it), so both bridges coexist in one ctx.
 *
 * See spec/js_env.md for the full contract (the JS-visible surface).
 */

typedef enum je_status {
    JE_OK = 0,
    JE_ERR_NULL_ARG,  /* ctx was NULL */
    JE_ERR_OOM,       /* allocation failed building the globals */
    JE_ERR_INTERNAL   /* engine context unreachable or install failed */
} je_status;

/* Installs `navigator`, `screen` and `performance` (read-only, sealed) and
 * replaces `Date.now` with a coarsened version. screen_w/screen_h are the real
 * output size; they are bucketed via fp_bucket_screen before exposure. Intended
 * to be called on a freshly created context, before any untrusted script runs. */
je_status je_install(js_context *ctx, int screen_w, int screen_h);

/* Installs sealed, read-only `canvas` and `audio` globals, each with a
 * `readback(Uint8Array)` method that returns a new Uint8Array with fp_perturb
 * applied under readback_key. This is the seam where canvas pixel / audio sample
 * readback is poisoned (deterministic within an origin, unlinkable across
 * sessions and across origins) to defeat readback fingerprinting. readback_key
 * is the per-origin key the orchestrator derives with
 * fp_origin_key(session_key, eTLD+1). The input array is never mutated. */
je_status je_install_canvas(js_context *ctx, uint64_t readback_key);

#endif /* FREEDOM_JS_ENV_H */
