/*
 * js_sandbox — implementation (vendored QuickJS-ng v0.15.1 backend).
 *
 * The sandbox owns one engine runtime + context with no I/O modules: only the
 * compute intrinsics added by JS_NewContext are present (no std/os/require).
 * Hard memory and stack limits are armed on the runtime; a wall-clock budget is
 * enforced through the engine's interrupt handler, so an attacker's infinite
 * loop or unbounded allocation fails closed instead of hanging or OOM-ing the
 * host. The QuickJS API is fully encapsulated here; no JS* type escapes.
 */

#define _POSIX_C_SOURCE 200809L

#include "js_sandbox.h"

#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "quickjs.h"

/* We enforce the heap cap ourselves (not via JS_SetMemoryLimit, whose check
 * runs *inside* QuickJS before our allocator and is therefore unobservable).
 * Leaving QuickJS's own limit at its default (0 == unlimited) makes this the
 * sole enforcer, so a denied allocation is a deterministic, testable signal. */
typedef struct js_mem_state {
    size_t limit;
    size_t used;
    int    hit; /* sticky within one eval: an allocation was denied by the cap */
} js_mem_state;

struct js_context {
    JSRuntime      *rt;
    JSContext      *ctx;
    js_mem_state    mem;       /* heap accounting + cap enforcement */
    js_limits       limits;    /* resolved limits in effect for this context */
    struct timespec deadline;  /* armed per-eval when has_deadline != 0 */
    int             has_deadline;
    int             interrupted; /* set by the interrupt handler on timeout */
};

/* --- bounded allocator (QuickJS backend) --- */

static void *jm_malloc(void *opaque, size_t size) {
    js_mem_state *m = (js_mem_state *)opaque;
    if (m->used + size > m->limit) { m->hit = 1; return NULL; }
    void *p = malloc(size);
    if (p != NULL) m->used += malloc_usable_size(p);
    return p;
}

static void *jm_calloc(void *opaque, size_t count, size_t size) {
    js_mem_state *m = (js_mem_state *)opaque;
    if (size != 0 && count > (size_t)-1 / size) { m->hit = 1; return NULL; }
    size_t total = count * size;
    if (m->used + total > m->limit) { m->hit = 1; return NULL; }
    void *p = calloc(count, size);
    if (p != NULL) m->used += malloc_usable_size(p);
    return p;
}

static void jm_free(void *opaque, void *ptr) {
    js_mem_state *m = (js_mem_state *)opaque;
    if (ptr != NULL) m->used -= malloc_usable_size(ptr);
    free(ptr);
}

static void *jm_realloc(void *opaque, void *ptr, size_t size) {
    js_mem_state *m = (js_mem_state *)opaque;
    size_t old = (ptr != NULL) ? malloc_usable_size(ptr) : 0;
    if (size != 0 && m->used + size - old > m->limit) { m->hit = 1; return NULL; }
    void *p = realloc(ptr, size);
    if (p == NULL && size != 0) return NULL; /* original ptr left untouched */
    m->used = m->used - old + ((p != NULL) ? malloc_usable_size(p) : 0);
    return p;
}

static size_t jm_usable_size(const void *ptr) {
    return malloc_usable_size((void *)ptr);
}

static const JSMallocFunctions FREEDOM_MF = {
    jm_calloc, jm_malloc, jm_free, jm_realloc, jm_usable_size
};

/* --- helpers --- */

static char *host_dup(const char *src, size_t len) {
    char *out = (char *)malloc(len + 1);
    if (out == NULL) return NULL;
    if (len != 0 && src != NULL) memcpy(out, src, len);
    out[len] = '\0';
    return out;
}

static int timespec_reached(const struct timespec *now, const struct timespec *deadline) {
    if (now->tv_sec != deadline->tv_sec) return now->tv_sec > deadline->tv_sec;
    return now->tv_nsec >= deadline->tv_nsec;
}

/* Returns nonzero to interrupt the engine once the per-eval budget is spent. */
static int js_interrupt_cb(JSRuntime *rt, void *opaque) {
    (void)rt;
    js_context *c = (js_context *)opaque;
    if (c == NULL || !c->has_deadline) return 0;
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    if (timespec_reached(&now, &c->deadline)) {
        c->interrupted = 1;
        return 1;
    }
    return 0;
}

/* Pulls the pending exception into an owned host string. The deadline must be
 * disarmed before calling: formatting an Error may run user toString(). Under a
 * memory cap the heap may be exhausted and formatting can fail (NULL): we then
 * fall back to a fixed message (host allocation is not subject to the cap). */
static char *capture_exception(JSContext *ctx, size_t *out_len) {
    if (out_len != NULL) *out_len = 0;

    JSValue exc = JS_GetException(ctx);
    size_t clen = 0;
    const char *cmsg = JS_ToCStringLen(ctx, &clen, exc);

    char *msg;
    if (cmsg == NULL) {
        msg = host_dup("out of memory", sizeof "out of memory" - 1);
        if (out_len != NULL && msg != NULL) *out_len = sizeof "out of memory" - 1;
    } else {
        msg = host_dup(cmsg, clen);
        if (out_len != NULL && msg != NULL) *out_len = clen;
        JS_FreeCString(ctx, cmsg);
    }

    JS_FreeValue(ctx, exc);
    return msg;
}

/* --- public: defaults & validator --- */

js_limits js_limits_default(void) {
    js_limits l;
    l.max_source_bytes   = JS_DEFAULT_MAX_SOURCE;
    l.memory_limit_bytes = JS_DEFAULT_MEM_LIMIT;
    l.max_stack_bytes    = JS_DEFAULT_STACK_LIMIT;
    l.time_budget_ms     = JS_DEFAULT_TIME_BUDGET;
    return l;
}

static js_limits limits_resolve(const js_limits *lim) {
    js_limits l = (lim != NULL) ? *lim : js_limits_default();
    if (l.max_source_bytes == 0)   l.max_source_bytes   = JS_DEFAULT_MAX_SOURCE;
    if (l.memory_limit_bytes == 0) l.memory_limit_bytes = JS_DEFAULT_MEM_LIMIT;
    if (l.max_stack_bytes == 0)    l.max_stack_bytes    = JS_DEFAULT_STACK_LIMIT;
    if (l.time_budget_ms == 0)     l.time_budget_ms     = JS_DEFAULT_TIME_BUDGET;
    return l;
}

js_status js_validate_source(const char *src, size_t len, const js_limits *lim) {
    if (src == NULL) return JS_ERR_NULL_ARG;
    size_t cap = (lim != NULL && lim->max_source_bytes != 0)
                     ? lim->max_source_bytes : JS_DEFAULT_MAX_SOURCE;
    if (len == 0) return JS_ERR_EMPTY;
    if (len > cap) return JS_ERR_TOO_LARGE;
    return JS_OK;
}

/* --- public: lifecycle --- */

js_status js_context_new(const js_limits *lim, js_context **out) {
    if (out == NULL) return JS_ERR_NULL_ARG;
    *out = NULL;

    js_limits l = limits_resolve(lim);

    js_context *c = (js_context *)calloc(1, sizeof *c);
    if (c == NULL) return JS_ERR_OOM;

    /* The heap cap must be live before the runtime allocates anything. */
    c->mem.limit = l.memory_limit_bytes;
    c->mem.used = 0;
    c->mem.hit = 0;

    c->rt = JS_NewRuntime2(&FREEDOM_MF, &c->mem);
    if (c->rt == NULL) {
        free(c);
        return JS_ERR_OOM;
    }

    /* Hard limits before any context exists so they cover everything. */
    JS_SetMaxStackSize(c->rt, l.max_stack_bytes);
    JS_SetInterruptHandler(c->rt, js_interrupt_cb, c);

    /* JS_NewContext adds only compute intrinsics: no std/os/require/print. */
    c->ctx = JS_NewContext(c->rt);
    if (c->ctx == NULL) {
        JS_FreeRuntime(c->rt);
        free(c);
        return JS_ERR_OOM;
    }

    c->limits = l;
    c->has_deadline = 0;
    c->interrupted = 0;
    *out = c;
    return JS_OK;
}

void js_context_free(js_context *ctx) {
    if (ctx == NULL) return;
    if (ctx->ctx != NULL) JS_FreeContext(ctx->ctx);
    if (ctx->rt != NULL) JS_FreeRuntime(ctx->rt);
    free(ctx);
}

/* --- public: evaluation --- */

static void arm_deadline(js_context *ctx, uint64_t budget_ms) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    long add_ns = (long)(budget_ms % 1000u) * 1000000L;
    now.tv_sec += (time_t)(budget_ms / 1000u);
    now.tv_nsec += add_ns;
    if (now.tv_nsec >= 1000000000L) {
        now.tv_sec += 1;
        now.tv_nsec -= 1000000000L;
    }
    ctx->deadline = now;
    ctx->interrupted = 0;
    ctx->has_deadline = 1;
}

void js_set_time_budget(js_context *ctx, uint64_t budget_ms) {
    if (ctx == NULL) return;
    ctx->limits.time_budget_ms = budget_ms;
}

js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res) {
    if (ctx == NULL || src == NULL || res == NULL) return JS_ERR_NULL_ARG;

    memset(res, 0, sizeof *res);

    js_status vs = js_validate_source(src, len, &ctx->limits);
    if (vs != JS_OK) { res->status = vs; return vs; }

    /* JS_Eval requires a NUL-terminated input; the caller's buffer may not be. */
    char *code = host_dup(src, len);
    if (code == NULL) { res->status = JS_ERR_OOM; return JS_ERR_OOM; }

    js_status status;

    ctx->mem.hit = 0;
    arm_deadline(ctx, ctx->limits.time_budget_ms);

    /* Phase 1: compile only, so syntax errors are distinct from runtime ones. */
    JSValue compiled = JS_Eval(ctx->ctx, code, len, "<sandbox>",
                               JS_EVAL_FLAG_COMPILE_ONLY | JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(compiled)) {
        int was_interrupted = ctx->interrupted;
        ctx->has_deadline = 0; /* disarm before formatting the message */
        size_t mlen = 0;
        char *msg = capture_exception(ctx->ctx, &mlen);
        res->value = msg;
        res->value_len = (msg != NULL) ? mlen : 0;
        res->is_exception = 1;
        status = was_interrupted ? JS_ERR_TIMEOUT
               : ctx->mem.hit    ? JS_ERR_MEMORY
                                 : JS_ERR_SYNTAX;
        JS_FreeValue(ctx->ctx, compiled);
        free(code);
        res->status = status;
        return status;
    }

    /* Phase 2: run the compiled program (consumes `compiled`). */
    JSValue result = JS_EvalFunction(ctx->ctx, compiled);
    int was_interrupted = ctx->interrupted;
    ctx->has_deadline = 0; /* disarm before any further JS (toString etc.) */

    if (JS_IsException(result)) {
        size_t mlen = 0;
        char *msg = capture_exception(ctx->ctx, &mlen);
        res->value = msg;
        res->value_len = (msg != NULL) ? mlen : 0;
        res->is_exception = 1;
        status = was_interrupted ? JS_ERR_TIMEOUT
               : ctx->mem.hit    ? JS_ERR_MEMORY
                                 : JS_ERR_RUNTIME;
        JS_FreeValue(ctx->ctx, result);
        free(code);
        res->status = status;
        return status;
    }

    /* Success: stringify the result value into an owned buffer. */
    size_t vlen = 0;
    const char *cval = JS_ToCStringLen(ctx->ctx, &vlen, result);
    if (cval == NULL) {
        /* Could not format the result: heap exhausted, or an exception escaped. */
        js_status fail = ctx->mem.hit ? JS_ERR_MEMORY : JS_ERR_INTERNAL;
        JS_FreeValue(ctx->ctx, result);
        free(code);
        res->status = fail;
        return fail;
    }
    char *val = host_dup(cval, vlen);
    JS_FreeCString(ctx->ctx, cval);
    JS_FreeValue(ctx->ctx, result);
    free(code);

    if (val == NULL) { res->status = JS_ERR_OOM; return JS_ERR_OOM; }
    res->value = val;
    res->value_len = vlen;
    res->is_exception = 0;
    res->status = JS_OK;
    return JS_OK;
}

js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res) {
    if (res == NULL) return JS_ERR_NULL_ARG;
    memset(res, 0, sizeof *res);

    js_context *ctx = NULL;
    js_status s = js_context_new(lim, &ctx);
    if (s != JS_OK) { res->status = s; return s; }

    s = js_eval(ctx, src, len, res);
    js_context_free(ctx);
    return s;
}

void js_result_free(js_result *res) {
    if (res == NULL) return;
    free(res->value);
    res->value = NULL;
    res->value_len = 0;
    res->is_exception = 0;
    res->status = JS_OK;
}

void *js_context_raw(js_context *ctx) {
    return (ctx != NULL) ? (void *)ctx->ctx : NULL;
}
