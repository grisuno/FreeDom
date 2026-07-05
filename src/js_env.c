/*
 * js_env — implementation of the anti_fp <-> JS environment bridge.
 *
 * Installs frozen, read-only `navigator`, `screen` and `performance` globals and
 * replaces `Date.now` with a coarsened version. Every identity value comes from
 * the pure anti_fp primitives (one audited source of normalized constants); the
 * clocks are floored to a 100 ms grid by fp_coarsen_time_ms. No live engine
 * objects are exposed, properties are non-writable / non-configurable, and the
 * objects are sealed, so untrusted script cannot hijack the surface or restore a
 * high-resolution real clock.
 *
 * The only host I/O is reading the system clock, which is inherent to a clock;
 * anti_fp itself stays pure. The performance.now origin lives in the native
 * function's bound data (per-context, reentrant), not in any global state.
 */

#define _POSIX_C_SOURCE 200809L

#include "js_env.h"

#include "anti_fp.h"
#include "js_sandbox.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "quickjs.h"

/* --- clocks (the only host I/O in this module) --- */

static uint64_t wall_clock_ms(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) != 0) return 0;
    return (uint64_t)ts.tv_sec * 1000u + (uint64_t)ts.tv_nsec / 1000000u;
}

static double monotonic_ms(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) return 0.0;
    return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0;
}

/* --- native clock methods --- */

static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,
                          int argc, JSValueConst *argv) {
    (void)this_val; (void)argc; (void)argv;
    return JS_NewFloat64(ctx, (double)fp_coarsen_time_ms(wall_clock_ms()));
}

/* performance.now: coarsened elapsed since the origin bound at install time, so
 * it never leaks the host uptime. */
static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,
                          int argc, JSValueConst *argv,
                          int magic, JSValueConst *func_data) {
    (void)this_val; (void)argc; (void)argv; (void)magic;
    double origin = 0.0;
    JS_ToFloat64(ctx, &origin, func_data[0]);
    double elapsed = monotonic_ms() - origin;
    if (elapsed < 0.0) elapsed = 0.0;
    return JS_NewFloat64(ctx, (double)fp_coarsen_time_ms((uint64_t)elapsed));
}

/* Inert helpers for the performance surface: a no-op and an empty-array getter.
 * getEntriesByType/mark/measure exist on real pages; returning nothing leaks no
 * timing (Zero Knowledge) while keeping analytics scripts from throwing. */
static JSValue m_noop(JSContext *ctx, JSValueConst this_val,
                      int argc, JSValueConst *argv) {
    (void)ctx; (void)this_val; (void)argc; (void)argv;
    return JS_UNDEFINED;
}

static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,
                             int argc, JSValueConst *argv) {
    (void)this_val; (void)argc; (void)argv;
    return JS_NewArray(ctx);
}

/* --- read-only property helpers --- */

/* Always takes ownership of v: JS_DefinePropertyValueStr consumes it (freeing it
 * even when the define fails). An exception value is an immediate with nothing
 * to free. Callers must never free a value after handing it here. */
static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v) {
    if (JS_IsException(v)) return -1;
    int rc = JS_DefinePropertyValueStr(ctx, obj, name, v, JS_PROP_ENUMERABLE);
    return (rc < 0) ? -1 : 0;
}

static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s) {
    return def_val(ctx, obj, name, JS_NewString(ctx, s));
}

static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n) {
    return def_val(ctx, obj, name, JS_NewInt32(ctx, n));
}

/* navigator.languages: a sealed array built by splitting fp_accept_language()
 * (e.g. "en-US,en") on commas. Returns an exception value on OOM. */
static JSValue build_languages(JSContext *ctx) {
    JSValue arr = JS_NewArray(ctx);
    if (JS_IsException(arr)) return arr;

    const char *langs = fp_accept_language();
    uint32_t idx = 0;
    const char *start = langs;
    for (const char *p = langs;; ++p) {
        if (*p == ',' || *p == '\0') {
            JSValue tok = JS_NewStringLen(ctx, start, (size_t)(p - start));
            if (JS_IsException(tok)) { JS_FreeValue(ctx, arr); return JS_EXCEPTION; }
            if (JS_DefinePropertyValueUint32(ctx, arr, idx++, tok,
                                             JS_PROP_ENUMERABLE) < 0) {
                JS_FreeValue(ctx, arr);
                return JS_EXCEPTION;
            }
            if (*p == '\0') break;
            start = p + 1;
        }
    }
    JS_PreventExtensions(ctx, arr);
    return arr;
}

static int build_navigator(JSContext *ctx, JSValueConst global) {
    JSValue nav = JS_NewObject(ctx);
    if (JS_IsException(nav)) return -1;

    JSValue languages = build_languages(ctx);
    if (JS_IsException(languages)) { JS_FreeValue(ctx, nav); return -1; }

    /* languages is consumed by the first def_val regardless of later failures. */
    int ok = def_val(ctx, nav, "languages", languages) == 0
          && def_str(ctx, nav, "userAgent", fp_user_agent()) == 0
          && def_str(ctx, nav, "language", "en-US") == 0
          && def_str(ctx, nav, "platform", fp_platform()) == 0
          && def_str(ctx, nav, "vendor", fp_vendor()) == 0
          && def_int(ctx, nav, "hardwareConcurrency", fp_hardware_concurrency()) == 0
          && def_int(ctx, nav, "deviceMemory", fp_device_memory_gb()) == 0
          && def_val(ctx, nav, "webdriver", JS_NewBool(ctx, 0)) == 0
          && def_val(ctx, nav, "doNotTrack", JS_NULL) == 0;
    if (!ok) { JS_FreeValue(ctx, nav); return -1; }
    JS_PreventExtensions(ctx, nav);
    return (JS_DefinePropertyValueStr(ctx, global, "navigator", nav,
                                      JS_PROP_ENUMERABLE) < 0) ? -1 : 0;
}

static int build_screen(JSContext *ctx, JSValueConst global, int w, int h) {
    int bw = 0, bh = 0;
    fp_bucket_screen(w, h, &bw, &bh);

    JSValue scr = JS_NewObject(ctx);
    if (JS_IsException(scr)) return -1;

    int ok = def_int(ctx, scr, "width", bw) == 0
          && def_int(ctx, scr, "height", bh) == 0
          && def_int(ctx, scr, "availWidth", bw) == 0
          && def_int(ctx, scr, "availHeight", bh) == 0
          && def_int(ctx, scr, "colorDepth", 24) == 0
          && def_int(ctx, scr, "pixelDepth", 24) == 0;
    if (!ok) { JS_FreeValue(ctx, scr); return -1; }
    JS_PreventExtensions(ctx, scr);
    return (JS_DefinePropertyValueStr(ctx, global, "screen", scr,
                                      JS_PROP_ENUMERABLE) < 0) ? -1 : 0;
}

/* PerformanceTiming (deprecated but still read by real analytics, e.g. google's
 * timing.responseStart). Identity-safe: every field is the SAME fixed epoch, so
 * all deltas are 0 ("loaded instantly") and no real navigation timing leaks. */
static const char *const PERF_TIMING_FIELDS[] = {
    "navigationStart", "unloadEventStart", "unloadEventEnd", "redirectStart",
    "redirectEnd", "fetchStart", "domainLookupStart", "domainLookupEnd",
    "connectStart", "connectEnd", "secureConnectionStart", "requestStart",
    "responseStart", "responseEnd", "domLoading", "domInteractive",
    "domContentLoadedEventStart", "domContentLoadedEventEnd", "domComplete",
    "loadEventStart", "loadEventEnd"
};
#define PERF_ORIGIN_EPOCH 1700000000000.0

static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,
                  JSCFunction *fn) {
    return def_val(ctx, obj, name, JS_NewCFunction(ctx, fn, name, 0));
}

static int build_perf_timing(JSContext *ctx, JSValueConst perf) {
    JSValue timing = JS_NewObject(ctx);
    if (JS_IsException(timing)) return -1;
    for (size_t i = 0; i < sizeof PERF_TIMING_FIELDS / sizeof PERF_TIMING_FIELDS[0]; ++i) {
        if (def_val(ctx, timing, PERF_TIMING_FIELDS[i],
                    JS_NewFloat64(ctx, PERF_ORIGIN_EPOCH)) != 0) {
            JS_FreeValue(ctx, timing);
            return -1;
        }
    }
    JS_PreventExtensions(ctx, timing);
    return def_val(ctx, perf, "timing", timing);
}

static int build_perf_navigation(JSContext *ctx, JSValueConst perf) {
    JSValue nav = JS_NewObject(ctx);
    if (JS_IsException(nav)) return -1;
    if (def_int(ctx, nav, "type", 0) != 0 ||
        def_int(ctx, nav, "redirectCount", 0) != 0) {
        JS_FreeValue(ctx, nav);
        return -1;
    }
    JS_PreventExtensions(ctx, nav);
    return def_val(ctx, perf, "navigation", nav);
}

static int build_performance(JSContext *ctx, JSValueConst global) {
    JSValue perf = JS_NewObject(ctx);
    if (JS_IsException(perf)) return -1;

    JSValue origin = JS_NewFloat64(ctx, monotonic_ms());
    JSValueConst data[1] = { origin };
    JSValue now = JS_NewCFunctionData(ctx, m_perf_now, 0, 0, 1, data);
    JS_FreeValue(ctx, origin); /* JS_NewCFunctionData retains its own copy */

    /* def_val takes ownership of now (consumed even on failure). */
    int ok = def_val(ctx, perf, "now", now) == 0
          && def_val(ctx, perf, "timeOrigin",
                     JS_NewFloat64(ctx, PERF_ORIGIN_EPOCH)) == 0
          && build_perf_timing(ctx, perf) == 0
          && build_perf_navigation(ctx, perf) == 0
          && def_fn(ctx, perf, "getEntries", m_empty_array) == 0
          && def_fn(ctx, perf, "getEntriesByType", m_empty_array) == 0
          && def_fn(ctx, perf, "getEntriesByName", m_empty_array) == 0
          && def_fn(ctx, perf, "mark", m_noop) == 0
          && def_fn(ctx, perf, "measure", m_noop) == 0
          && def_fn(ctx, perf, "clearMarks", m_noop) == 0
          && def_fn(ctx, perf, "clearMeasures", m_noop) == 0
          && def_fn(ctx, perf, "clearResourceTimings", m_noop) == 0
          && def_fn(ctx, perf, "setResourceTimingBufferSize", m_noop) == 0;
    if (!ok) { JS_FreeValue(ctx, perf); return -1; }
    JS_PreventExtensions(ctx, perf);
    return (JS_DefinePropertyValueStr(ctx, global, "performance", perf,
                                      JS_PROP_ENUMERABLE) < 0) ? -1 : 0;
}

/* Replaces the built-in Date.now with the coarsened version, non-writable and
 * non-configurable so a script cannot restore a high-resolution clock. */
static int override_date_now(JSContext *ctx, JSValueConst global) {
    JSValue date = JS_GetPropertyStr(ctx, global, "Date");
    if (JS_IsException(date) || JS_IsUndefined(date)) {
        JS_FreeValue(ctx, date);
        return -1;
    }
    JSValue fn = JS_NewCFunction(ctx, m_date_now, "now", 0);
    int rc = JS_IsException(fn)
           ? -1
           : JS_DefinePropertyValueStr(ctx, date, "now", fn, 0);
    JS_FreeValue(ctx, date);
    return (rc < 0) ? -1 : 0;
}

/* --- canvas/audio readback poisoning (fp_perturb) --- */

/* Returns a new Uint8Array equal to the input with fp_perturb applied under the
 * session key bound in func_data (split across two doubles). The input array is
 * never mutated: we copy, perturb the copy, and hand back a fresh array. */
static JSValue m_readback(JSContext *ctx, JSValueConst this_val,
                          int argc, JSValueConst *argv,
                          int magic, JSValueConst *func_data) {
    (void)this_val; (void)magic;
    if (argc < 1) return JS_ThrowTypeError(ctx, "readback expects a Uint8Array");

    size_t size = 0;
    uint8_t *data = JS_GetUint8Array(ctx, &size, argv[0]);
    if (data == NULL) return JS_ThrowTypeError(ctx, "readback expects a Uint8Array");

    double hi = 0.0, lo = 0.0;
    JS_ToFloat64(ctx, &hi, func_data[0]);
    JS_ToFloat64(ctx, &lo, func_data[1]);
    uint64_t key = ((uint64_t)(uint32_t)hi << 32) | (uint32_t)lo;

    uint8_t *copy = (uint8_t *)malloc(size ? size : 1);
    if (copy == NULL) return JS_ThrowOutOfMemory(ctx);
    if (size != 0) memcpy(copy, data, size);
    fp_perturb(copy, size, key);

    JSValue out = JS_NewUint8ArrayCopy(ctx, copy, size);
    free(copy);
    return out;
}

static JSValue make_readback(JSContext *ctx, uint64_t key) {
    JSValueConst data[2];
    data[0] = JS_NewFloat64(ctx, (double)(uint32_t)(key >> 32));
    data[1] = JS_NewFloat64(ctx, (double)(uint32_t)(key & 0xFFFFFFFFu));
    /* data are float immediates: JS_NewCFunctionData copies them, nothing to free. */
    return JS_NewCFunctionData(ctx, m_readback, 1, 0, 2, data);
}

static int build_readback_obj(JSContext *ctx, JSValueConst global,
                              const char *name, uint64_t key) {
    JSValue obj = JS_NewObject(ctx);
    if (JS_IsException(obj)) return -1;
    if (def_val(ctx, obj, "readback", make_readback(ctx, key)) != 0) {
        JS_FreeValue(ctx, obj);
        return -1;
    }
    JS_PreventExtensions(ctx, obj);
    return (JS_DefinePropertyValueStr(ctx, global, name, obj, JS_PROP_ENUMERABLE) < 0)
               ? -1 : 0;
}

je_status je_install(js_context *ctx, int screen_w, int screen_h) {
    if (ctx == NULL) return JE_ERR_NULL_ARG;

    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JE_ERR_INTERNAL;

    JSValue global = JS_GetGlobalObject(jsctx);
    if (JS_IsException(global)) return JE_ERR_OOM;

    int ok = build_navigator(jsctx, global) == 0
          && build_screen(jsctx, global, screen_w, screen_h) == 0
          && build_performance(jsctx, global) == 0
          && override_date_now(jsctx, global) == 0;

    JS_FreeValue(jsctx, global);
    return ok ? JE_OK : JE_ERR_OOM;
}

je_status je_install_canvas(js_context *ctx, uint64_t readback_key) {
    if (ctx == NULL) return JE_ERR_NULL_ARG;

    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JE_ERR_INTERNAL;

    JSValue global = JS_GetGlobalObject(jsctx);
    if (JS_IsException(global)) return JE_ERR_OOM;

    int ok = build_readback_obj(jsctx, global, "canvas", readback_key) == 0
          && build_readback_obj(jsctx, global, "audio", readback_key) == 0;

    JS_FreeValue(jsctx, global);
    return ok ? JE_OK : JE_ERR_OOM;
}
