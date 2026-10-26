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

#include <sys/resource.h>

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

#define JS_PROFILE_SLOTS   192
#define JS_PROFILE_KEY_MAX 640

struct js_context {
    JSRuntime      *rt;
    JSContext      *ctx;
    js_mem_state    mem;       /* heap accounting + cap enforcement */
    js_limits       limits;    /* resolved limits in effect for this context */
    struct timespec deadline;  /* armed per-eval when has_deadline != 0 */
    int             has_deadline;
    int             interrupted; /* set by the interrupt handler on timeout */
    /* ES module host (spec/js_sandbox.md 7b): the caller's resolver and loader, and
     * the per-context caps every load is counted against. */
    js_module_resolve_fn mod_resolve;
    js_module_fetch_fn   mod_fetch;
    void                *mod_host;
    size_t               mod_count;
    size_t               mod_bytes;
    /* Realms (spec/js_sandbox.md 7c): extra contexts on rt, freed before ctx. */
    JSContext           *realms[JS_REALM_MAX];
    size_t               nrealms;
    /* Promises rejected with no handler yet (spec/js_sandbox.md 7d): reported through the
     * page's __onUnhandledRejection once the job queue drains, unless a handler arrived. */
    JSValue              rej_promise[JS_REJECT_MAX];
    JSValue              rej_reason[JS_REJECT_MAX];
    size_t               nrej;
    /* Sampling profiler (js_profile_enable): fixed table, zero when off. */
    int                  prof_on;
    struct timespec      prof_last;
    unsigned             prof_total;
    size_t               prof_n;
    struct { char key[JS_PROFILE_KEY_MAX]; unsigned hits; } prof[JS_PROFILE_SLOTS];
    /* Throw tracer (js_throws_enable). */
    int                  thr_on;
    size_t               thr_n;
    struct { char key[JS_PROFILE_KEY_MAX]; unsigned hits; } thr[JS_THROW_SLOTS];
};

/* --- unhandled-rejection tracking --- */

static void rej_remove(js_context *c, size_t i) {
    JS_FreeValue(c->ctx, c->rej_promise[i]);
    JS_FreeValue(c->ctx, c->rej_reason[i]);
    c->nrej--;
    c->rej_promise[i] = c->rej_promise[c->nrej];
    c->rej_reason[i]  = c->rej_reason[c->nrej];
}

static void js_rejection_cb(JSContext *jc, JSValueConst promise, JSValueConst reason,
                            bool is_handled, void *opaque) {
    js_context *c = (js_context *)opaque;
    if (is_handled) {
        for (size_t i = 0; i < c->nrej; ++i)
            if (JS_VALUE_GET_PTR(c->rej_promise[i]) == JS_VALUE_GET_PTR(promise)) {
                rej_remove(c, i);
                return;
            }
        return;
    }
    if (c->nrej >= JS_REJECT_MAX) return;
    c->rej_promise[c->nrej] = JS_DupValue(jc, promise);
    c->rej_reason[c->nrej]  = JS_DupValue(jc, reason);
    c->nrej++;
}

/* Hands each still-unhandled rejection to the page, oldest first. The list is detached
 * before any page code runs, so a handler that rejects again only queues for next time. */
static void rej_report(js_context *c) {
    if (c->nrej == 0) return;
    JSValue ps[JS_REJECT_MAX], rs[JS_REJECT_MAX];
    size_t n = c->nrej;
    memcpy(ps, c->rej_promise, n * sizeof ps[0]);
    memcpy(rs, c->rej_reason,  n * sizeof rs[0]);
    c->nrej = 0;
    JSValue g = JS_GetGlobalObject(c->ctx);
    JSValue fn = JS_GetPropertyStr(c->ctx, g, "__onUnhandledRejection");
    for (size_t i = 0; i < n; ++i) {
        if (JS_IsFunction(c->ctx, fn)) {
            JSValue args[2] = { ps[i], rs[i] };
            JSValue r = JS_Call(c->ctx, fn, JS_UNDEFINED, 2, args);
            if (JS_IsException(r)) JS_FreeValue(c->ctx, JS_GetException(c->ctx));
            JS_FreeValue(c->ctx, r);
        }
        JS_FreeValue(c->ctx, ps[i]);
        JS_FreeValue(c->ctx, rs[i]);
    }
    JS_FreeValue(c->ctx, fn);
    JS_FreeValue(c->ctx, g);
}

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
    if (len == (size_t)-1) return NULL; /* guard: len+1 would overflow to 0 */
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

static long timespec_diff_ms(const struct timespec *a, const struct timespec *b) {
    return (long)((a->tv_sec - b->tv_sec) * 1000L + (a->tv_nsec - b->tv_nsec) / 1000000L);
}

/* Records the two innermost frames of the running stack ("at f (file:l:c)" lines). */
static void profile_sample(js_context *c, unsigned weight_ms) {
    JSValue err = JS_NewError(c->ctx);
    JSValue st = JS_GetPropertyStr(c->ctx, err, "stack");
    size_t len = 0;
    const char *s = JS_IsString(st) ? JS_ToCStringLen(c->ctx, &len, st) : NULL;
    if (s != NULL) {
        char key[JS_PROFILE_KEY_MAX];
        size_t k = 0;
        int lines = 0;
        for (size_t i = 0; i < len && k + 1 < sizeof key && lines < 2; i++) {
            char ch = s[i];
            if (ch == '\n') { lines++; if (lines < 2 && k + 4 < sizeof key) { memcpy(key + k, " <- ", 4); k += 4; } continue; }
            if (ch == ' ' && (k == 0 || key[k - 1] == ' ')) continue;
            key[k++] = ch;
        }
        key[k] = '\0';
        size_t slot = c->prof_n;
        for (size_t i = 0; i < c->prof_n; i++)
            if (strcmp(c->prof[i].key, key) == 0) { slot = i; break; }
        if (slot == c->prof_n && c->prof_n < JS_PROFILE_SLOTS) {
            memcpy(c->prof[slot].key, key, k + 1);
            c->prof[slot].hits = 0;
            c->prof_n++;
        }
        if (slot < c->prof_n) c->prof[slot].hits += weight_ms;
        c->prof_total += weight_ms;
        JS_FreeCString(c->ctx, s);
    }
    JS_FreeValue(c->ctx, st);
    JS_FreeValue(c->ctx, err);
}

void js_profile_enable(js_context *ctx) {
    if (ctx == NULL) return;
    ctx->prof_on = 1;
    clock_gettime(CLOCK_MONOTONIC, &ctx->prof_last);
}

size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n) {
    if (out == NULL || cap == 0) return 0;
    out[0] = '\0';
    if (ctx == NULL || !ctx->prof_on || ctx->prof_total == 0) return 0;
    size_t n = 0;
    unsigned char used[JS_PROFILE_SLOTS] = {0};
    for (size_t r = 0; r < top_n && r < ctx->prof_n; r++) {
        size_t best = ctx->prof_n;
        for (size_t i = 0; i < ctx->prof_n; i++)
            if (!used[i] && (best == ctx->prof_n || ctx->prof[i].hits > ctx->prof[best].hits)) best = i;
        if (best == ctx->prof_n) break;
        used[best] = 1;
        size_t space = cap - n;
        if (space == 0) break;
        int w = snprintf(out + n, space, "%u%% %s\n", ctx->prof[best].hits * 100u / ctx->prof_total,
                         ctx->prof[best].key);
        if (w < 0 || (size_t)w >= space) { n = cap - 1; break; }
        n += (size_t)w;
    }
    return n;
}

/* Condenses "message + the two innermost frames" of a thrown value into one line. */
static void throw_key(JSContext *ctx, JSValueConst obj, char *key, size_t cap) {
    size_t k = 0;
    key[0] = '\0';
    const char *msg = NULL, *stack = NULL;
    JSValue vstack = JS_UNDEFINED;
    if (JS_IsObject(obj)) {
        JSValue m = JS_GetPropertyStr(ctx, obj, "message");
        if (JS_IsString(m)) msg = JS_ToCString(ctx, m);
        JS_FreeValue(ctx, m);
        vstack = JS_GetPropertyStr(ctx, obj, "stack");
        if (JS_IsString(vstack)) stack = JS_ToCString(ctx, vstack);
    } else if (!JS_IsUndefined(obj)) {
        msg = JS_ToCString(ctx, obj);
    }
    if (JS_HasException(ctx)) JS_FreeValue(ctx, JS_GetException(ctx));   /* a getter threw: ignore */
    if (stack == NULL || stack[0] == '\0') {
        /* A native throw (TypeError from the engine) carries no frames: the live call stack at
         * the throw site is the useful one. */
        if (stack != NULL) JS_FreeCString(ctx, stack);
        JS_FreeValue(ctx, vstack);
        JSValue fresh = JS_NewError(ctx);
        vstack = JS_GetPropertyStr(ctx, fresh, "stack");
        JS_FreeValue(ctx, fresh);
        stack = JS_IsString(vstack) ? JS_ToCString(ctx, vstack) : NULL;
    }
    if (msg != NULL) {
        for (size_t i = 0; msg[i] != '\0' && k + 1 < cap && k < 100; i++)
            key[k++] = (msg[i] == '\n') ? ' ' : msg[i];
    }
    if (stack != NULL && k + 4 < cap) {
        memcpy(key + k, " @ ", 3); k += 3;
        int lines = 0;
        size_t loc_start = (size_t)-1;   /* inside "(url:l:c)": keep only the tail of long URLs */
        for (size_t i = 0; stack[i] != '\0' && k + 1 < cap && lines < 2; i++) {
            char ch = stack[i];
            if (ch == '\n') { lines++; if (lines < 2 && k + 4 < cap) { memcpy(key + k, " <- ", 4); k += 4; } continue; }
            if (ch == ' ' && (k == 0 || key[k - 1] == ' ')) continue;
            if (ch == '(') loc_start = k + 1;
            key[k++] = ch;
            if (ch == ')' && loc_start != (size_t)-1) {
                size_t span = k - 1 - loc_start;
                if (span > 44) {                 /* "(...tail)" */
                    memmove(key + loc_start + 3, key + k - 1 - 41, 41);
                    memcpy(key + loc_start, "...", 3);
                    k = loc_start + 3 + 41;
                    key[k++] = ')';
                }
                loc_start = (size_t)-1;
            }
        }
    }
    key[k] = '\0';
    if (msg != NULL) JS_FreeCString(ctx, msg);
    if (stack != NULL) JS_FreeCString(ctx, stack);
    JS_FreeValue(ctx, vstack);
}

static void throw_hook_cb(JSContext *ctx, JSValueConst obj, void *opaque) {
    js_context *c = (js_context *)opaque;
    if (c == NULL || !c->thr_on) return;
    if (JS_VALUE_GET_TAG(obj) == JS_TAG_UNINITIALIZED) return;   /* the engine's internal re-throw marker */
    char key[JS_PROFILE_KEY_MAX];
    throw_key(ctx, obj, key, sizeof key);
    if (key[0] == '\0') return;
    size_t slot = c->thr_n;
    for (size_t i = 0; i < c->thr_n; i++)
        if (strcmp(c->thr[i].key, key) == 0) { slot = i; break; }
    if (slot == c->thr_n) {
        if (c->thr_n >= JS_THROW_SLOTS) return;
        size_t kl = strlen(key);
        memcpy(c->thr[slot].key, key, kl + 1);
        c->thr[slot].hits = 0;
        c->thr_n++;
    }
    c->thr[slot].hits++;
}

void js_throws_enable(js_context *ctx) {
    if (ctx == NULL || ctx->rt == NULL) return;
    ctx->thr_on = 1;
    JS_SetThrowHook(ctx->rt, throw_hook_cb, ctx);
}

size_t js_throws_report(js_context *ctx, char *out, size_t cap, size_t top_n) {
    if (out == NULL || cap == 0) return 0;
    out[0] = '\0';
    if (ctx == NULL || !ctx->thr_on || ctx->thr_n == 0) return 0;
    size_t n = 0;
    unsigned char used[JS_THROW_SLOTS] = {0};
    for (size_t r = 0; r < top_n && r < ctx->thr_n; r++) {
        size_t best = ctx->thr_n;
        for (size_t i = 0; i < ctx->thr_n; i++)
            if (!used[i] && (best == ctx->thr_n || ctx->thr[i].hits > ctx->thr[best].hits)) best = i;
        if (best == ctx->thr_n) break;
        used[best] = 1;
        size_t space = cap - n;
        if (space == 0) break;
        int w = snprintf(out + n, space, "%ux %s\n", ctx->thr[best].hits, ctx->thr[best].key);
        if (w < 0 || (size_t)w >= space) { n = cap - 1; break; }
        n += (size_t)w;
    }
    return n;
}

/* __fbProfile(n) / __fbThrows(n): the report text of the context packed in the closure data. */
static JSValue m_fb_report(JSContext *jsctx, JSValueConst this_val, int argc, JSValueConst *argv,
                           int magic, JSValue *fd) {
    (void)this_val;
    int32_t lo = 0, hi = 0, top = 14;
    JS_ToInt32(jsctx, &lo, fd[0]);
    JS_ToInt32(jsctx, &hi, fd[1]);
    if (argc > 0) JS_ToInt32(jsctx, &top, argv[0]);
    if (top < 1) top = 1;
    if (top > 64) top = 64;
    js_context *c = (js_context *)(uintptr_t)(((uint64_t)(uint32_t)hi << 32) | (uint32_t)lo);
    char buf[16384];
    size_t n = (magic == 0) ? js_profile_report(c, buf, sizeof buf, (size_t)top)
                            : js_throws_report(c, buf, sizeof buf, (size_t)top);
    return JS_NewStringLen(jsctx, buf, n);
}

void js_devtools_enable(js_context *ctx) {
    if (ctx == NULL) return;
    js_profile_enable(ctx);
    js_throws_enable(ctx);
}

js_status js_devtools_expose(js_context *ctx) {
    if (ctx == NULL || ctx->ctx == NULL) return JS_ERR_NULL_ARG;
    uint64_t u = (uint64_t)(uintptr_t)ctx;
    static const char *const names[2] = { "__fbProfile", "__fbThrows" };
    JSValue g = JS_GetGlobalObject(ctx->ctx);
    for (int m = 0; m < 2; ++m) {
        JSValue data[2] = { JS_NewInt32(ctx->ctx, (int32_t)(uint32_t)u),
                            JS_NewInt32(ctx->ctx, (int32_t)(uint32_t)(u >> 32)) };
        JSValue fn = JS_NewCFunctionData(ctx->ctx, m_fb_report, 1, m, 2, data);
        JS_DefinePropertyValueStr(ctx->ctx, g, names[m], fn, JS_PROP_CONFIGURABLE | JS_PROP_WRITABLE);
    }
    JS_FreeValue(ctx->ctx, g);
    return JS_OK;
}

/* Returns nonzero to interrupt the engine once the per-eval budget is spent. */
static int js_interrupt_cb(JSRuntime *rt, void *opaque) {
    (void)rt;
    js_context *c = (js_context *)opaque;
    if (c == NULL) return 0;
    struct timespec now;
    if (c->prof_on) {
        clock_gettime(CLOCK_MONOTONIC, &now);
        long dt = timespec_diff_ms(&now, &c->prof_last);
        if (dt >= JS_PROFILE_PERIOD_MS) {
            c->prof_last = now;
            /* The interval is charged to the stack found at its end: a long native call
             * (DOM bridge, regex) shows up under the JS frame that made it. */
            profile_sample(c, dt > 1000 ? 1000u : (unsigned)dt);
        }
    }
    if (!c->has_deadline) return 0;
    clock_gettime(CLOCK_MONOTONIC, &now);
    if (timespec_reached(&now, &c->deadline)) {
        c->interrupted = 1;
        return 1;
    }
    return 0;
}

static int is_ascii_digit(char c) { return c >= '0' && c <= '9'; }

int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      int *line, int *col) {
    if (file_out != NULL && file_cap != 0) file_out[0] = '\0';
    if (line != NULL) *line = 0;
    if (col != NULL) *col = 0;
    if (stack == NULL) return 0;

    /* Work on the first stack line only. */
    const char *nl = strchr(stack, '\n');
    const char *end = (nl != NULL) ? nl : stack + strlen(stack);

    const char *p = stack;
    while (p < end && (*p == ' ' || *p == '\t')) p++;
    if (end - p >= 3 && p[0] == 'a' && p[1] == 't' && p[2] == ' ') p += 3;

    /* The "file:line:col" lives inside the last "(...)" when present. */
    const char *loc = p, *loc_end = end;
    if (loc_end > loc && loc_end[-1] == ')') {
        const char *open = NULL;
        for (const char *s = loc; s < loc_end; s++) if (*s == '(') open = s;
        if (open != NULL) { loc = open + 1; loc_end = loc_end - 1; }
    }
    while (loc < loc_end && (loc_end[-1] == ' ' || loc_end[-1] == '\t')) loc_end--;
    while (loc < loc_end && (*loc == ' ' || *loc == '\t')) loc++;

    /* Parse up to two trailing ":<digits>" groups from the right (file may itself
     * contain ':' as in https://..., so anchor on the rightmost colons). */
    const char *d2 = loc_end;
    while (d2 > loc && is_ascii_digit(d2[-1])) d2--;
    if (d2 == loc_end) return 0;                 /* no trailing digits => no location */
    if (d2 == loc || d2[-1] != ':') return 0;    /* digits not after a ':' */
    const char *colon_a = d2 - 1;

    const char *d1 = colon_a;
    while (d1 > loc && is_ascii_digit(d1[-1])) d1--;
    int have_two = (d1 < colon_a && d1 > loc && d1[-1] == ':');

    int a = 0, b = 0;
    /* Saturate BEFORE multiplying: clamping after overflowed int (UB, found by fuzz-js). */
    for (const char *s = d2; s < loc_end; s++) a = (a >= 100000000) ? 1000000000 : a * 10 + (*s - '0');

    const char *file_end;
    if (have_two) {
        for (const char *s = d1; s < colon_a; s++) b = (b >= 100000000) ? 1000000000 : b * 10 + (*s - '0');
        file_end = d1 - 1;                        /* the ':' before the line number */
        if (line != NULL) *line = b;
        if (col  != NULL) *col  = a;
    } else {
        file_end = colon_a;                       /* only "file:line" present */
        if (line != NULL) *line = a;
    }

    const char *fs = loc, *fe = file_end;
    while (fs < fe && (*fs == ' ' || *fs == '\t')) fs++;
    while (fs < fe && (fe[-1] == ' ' || fe[-1] == '\t')) fe--;
    if (file_out != NULL && file_cap != 0) {
        size_t n = (size_t)(fe - fs);
        if (n > file_cap - 1) n = file_cap - 1;
        if (n != 0) memcpy(file_out, fs, n);
        file_out[n] = '\0';
    }
    return 1;
}

/* Pulls the pending exception into an owned host string and, when the exception is
 * an Error, parses its throw site (file/line/col) out of the .stack. The deadline
 * must be disarmed before calling: formatting an Error may run user toString().
 * Under a memory cap the heap may be exhausted and formatting can fail (NULL): we
 * then fall back to a fixed message (host allocation is not subject to the cap).
 * out_file (owned, may be set to NULL) and out_line/out_col are diagnostics only. */
static char *capture_exception(JSContext *ctx, size_t *out_len,
                               char **out_file, int *out_line, int *out_col) {
    if (out_len  != NULL) *out_len  = 0;
    if (out_file != NULL) *out_file = NULL;
    if (out_line != NULL) *out_line = 0;
    if (out_col  != NULL) *out_col  = 0;

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

    /* Best-effort location: only Error objects carry .stack; a thrown primitive
     * yields undefined (or a getter throws), in which case we leave it unknown. */
    JSValue st = JS_GetPropertyStr(ctx, exc, "stack");
    if (JS_IsException(st)) {
        JS_FreeValue(ctx, JS_GetException(ctx)); /* clear, never propagate */
    } else if (!JS_IsUndefined(st) && !JS_IsNull(st)) {
        const char *ss = JS_ToCString(ctx, st);
        if (ss != NULL) {
            char fbuf[JS_LOC_FILE_MAX];
            int ln = 0, cl = 0;
            if (js_loc_from_stack(ss, fbuf, sizeof fbuf, &ln, &cl)) {
                if (out_file != NULL) *out_file = host_dup(fbuf, strlen(fbuf));
                if (out_line != NULL) *out_line = ln;
                if (out_col  != NULL) *out_col  = cl;
            }
            JS_FreeCString(ctx, ss);
        } else {
            JS_FreeValue(ctx, JS_GetException(ctx)); /* ToCString may have thrown */
        }
    }
    JS_FreeValue(ctx, st);

    JS_FreeValue(ctx, exc);
    return msg;
}

/* --- public: defaults & validator --- */

size_t js_stack_limit_for(size_t soft_stack) {
    size_t cap = soft_stack - soft_stack / 4;      /* 75 %: the bridge's native frames need the rest */
    if (soft_stack == 0 || cap < JS_MIN_STACK_LIMIT) return JS_MIN_STACK_LIMIT;
    return cap > JS_MAX_STACK_LIMIT ? JS_MAX_STACK_LIMIT : cap;
}

/* The soft stack of this process in bytes; unlimited is taken as the common 8 MiB, unknown as 0.
 * Read once and kept: getrlimit is not on the confined worker's syscall allowlist, so the worker
 * primes it (js_prime_stack_limit) before it confines itself and every later call is a read. */
static size_t g_soft_stack = (size_t)-1;

static size_t process_soft_stack(void) {
    if (g_soft_stack == (size_t)-1) {
        struct rlimit rl;
        if (getrlimit(RLIMIT_STACK, &rl) != 0) g_soft_stack = 0;
        else if (rl.rlim_cur == RLIM_INFINITY) g_soft_stack = (size_t)8u * 1024u * 1024u;
        else g_soft_stack = (size_t)rl.rlim_cur;
    }
    return g_soft_stack;
}

void js_prime_stack_limit(void) { (void)process_soft_stack(); }

js_limits js_limits_default(void) {
    js_limits l;
    l.max_source_bytes   = JS_DEFAULT_MAX_SOURCE;
    l.memory_limit_bytes = JS_DEFAULT_MEM_LIMIT;
    l.max_stack_bytes    = js_stack_limit_for(process_soft_stack());
    l.time_budget_ms     = JS_DEFAULT_TIME_BUDGET;
    return l;
}

static js_limits limits_resolve(const js_limits *lim) {
    js_limits l = (lim != NULL) ? *lim : js_limits_default();
    if (l.max_source_bytes == 0)   l.max_source_bytes   = JS_DEFAULT_MAX_SOURCE;
    if (l.memory_limit_bytes == 0) l.memory_limit_bytes = JS_DEFAULT_MEM_LIMIT;
    if (l.max_stack_bytes == 0)    l.max_stack_bytes    = js_stack_limit_for(process_soft_stack());
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
    JS_SetHostPromiseRejectionTracker(c->rt, js_rejection_cb, c);

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
    while (ctx->nrej > 0 && ctx->ctx != NULL) rej_remove(ctx, ctx->nrej - 1);
    for (size_t i = 0; i < ctx->nrealms; ++i) JS_FreeContext(ctx->realms[i]);
    ctx->nrealms = 0;
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
    return js_eval_named(ctx, src, len, "<sandbox>", res);
}

js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        const char *filename, js_result *res) {
    if (ctx == NULL || src == NULL || res == NULL) return JS_ERR_NULL_ARG;
    if (filename == NULL) filename = "<sandbox>";

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
    JSValue compiled = JS_Eval(ctx->ctx, code, len, filename,
                               JS_EVAL_FLAG_COMPILE_ONLY | JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(compiled)) {
        int was_interrupted = ctx->interrupted;
        ctx->has_deadline = 0; /* disarm before formatting the message */
        size_t mlen = 0;
        char *msg = capture_exception(ctx->ctx, &mlen, &res->file, &res->line, &res->col);
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
        char *msg = capture_exception(ctx->ctx, &mlen, &res->file, &res->line, &res->col);
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

int js_pump_jobs(js_context *ctx, int max_jobs) {
    if (ctx == NULL) return 0;
    int ran = 0;
    ctx->interrupted = 0;
    arm_deadline(ctx, ctx->limits.time_budget_ms);
    while (ran < max_jobs && JS_IsJobPending(ctx->rt)) {
        JSContext *jc = NULL;
        int r = JS_ExecutePendingJob(ctx->rt, &jc);
        if (r == 0) break;                    /* queue drained */
        if (r < 0 && jc != NULL)              /* a job threw: swallow, keep draining */
            JS_FreeValue(jc, JS_GetException(jc));
        ran++;
        if (ctx->interrupted) break;          /* time budget hit */
    }
    if (!ctx->interrupted && !JS_IsJobPending(ctx->rt)) rej_report(ctx);
    ctx->has_deadline = 0;
    return ran;
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
    free(res->file);
    res->value = NULL;
    res->file = NULL;
    res->line = 0;
    res->col = 0;
    res->value_len = 0;
    res->is_exception = 0;
    res->status = JS_OK;
}

/* Builds document.currentScript from src/type passed as VALUES: the script's src is
 * page-controlled and is never interpolated into code (it used to be, escaped by hand). */
static const char JS_CURRENT_SCRIPT_FACTORY[] =
    "(function(src,type){ var e={src:src,type:type,nonce:'',async:false,defer:false,"
    "  dataset:{}, tagName:'SCRIPT', nodeName:'SCRIPT', nodeType:1};"
    "  e.getAttribute=function(n){ n=String(n).toLowerCase();"
    "    if(n==='src') return src===''?null:src; if(n==='type') return type===''?null:type;"
    "    return null; };"
    "  e.hasAttribute=function(n){ return e.getAttribute(n)!==null; };"
    "  var real=null; try{ var L=document.getElementsByTagName('script'), cl=document.__fzcl;"
    "    if(!cl){ cl=new Set(); Object.defineProperty(document,'__fzcl',{value:cl,enumerable:false}); }"
    "    for(var i=0;i<L.length;i++){ var s=L[i]; if(cl.has(s._h)) continue;"
    "      if((s.getAttribute('src')||'')===src&&(s.getAttribute('type')||'')===type){ cl.add(s._h); real=s; break; } } }catch(x){}"
    "  document.currentScript=real||e; })";

void js_set_current_script(js_context *ctx, const char *src, const char *type) {
    if (ctx == NULL) return;
    JSContext *jc = ctx->ctx;
    JSValue global = JS_GetGlobalObject(jc);
    if (JS_IsException(global)) return;
    JSValue doc = JS_GetPropertyStr(jc, global, "document");
    if (JS_IsException(doc) || !JS_IsObject(doc)) {
        JS_FreeValue(jc, doc);
        JS_FreeValue(jc, global);
        return;
    }
    if (src == NULL) {
        JS_SetPropertyStr(jc, doc, "currentScript", JS_NULL);
    } else {
        JSValue fn = JS_Eval(jc, JS_CURRENT_SCRIPT_FACTORY, sizeof JS_CURRENT_SCRIPT_FACTORY - 1,
                             "<currentScript>", JS_EVAL_TYPE_GLOBAL);
        if (JS_IsFunction(jc, fn)) {
            JSValue args[2] = { JS_NewString(jc, src),
                                JS_NewString(jc, (type != NULL) ? type : "") };
            JSValue r = JS_Call(jc, fn, global, 2, args);
            if (JS_IsException(r)) JS_FreeValue(jc, JS_GetException(jc));
            JS_FreeValue(jc, r);
            JS_FreeValue(jc, args[0]);
            JS_FreeValue(jc, args[1]);
        } else if (JS_IsException(fn)) {
            JS_FreeValue(jc, JS_GetException(jc));
        }
        JS_FreeValue(jc, fn);
    }
    JS_FreeValue(jc, doc);
    JS_FreeValue(jc, global);
}

void *js_context_raw(js_context *ctx) {
    return (ctx != NULL) ? (void *)ctx->ctx : NULL;
}

/* Longest module URL the resolver may produce (matches url.h's URL_MAX_LEN). */
#define JS_MODULE_URL_MAX 8192u

/* QuickJS normalizer: every specifier goes through the host resolver. A bare
 * specifier or no host is a TypeError (the import fails, the page continues). */
static char *mod_normalize(JSContext *jc, const char *base, const char *name, void *opaque) {
    js_context *c = (js_context *)opaque;
    size_t nlen = strlen(name);
    /* A data: specifier is its own URL and can dwarf any URL limit, so the output buffer
     * grows with the specifier instead of capping it. */
    if (c == NULL || c->mod_resolve == NULL || nlen > JS_MODULE_BYTES_MAX) {
        JS_ThrowTypeError(jc, "Failed to resolve module specifier \"%s\"", name);
        return NULL;
    }
    size_t cap = nlen + JS_MODULE_URL_MAX;
    char *out = (char *)calloc(cap, 1);
    if (out == NULL) { JS_ThrowOutOfMemory(jc); return NULL; }
    if (c->mod_resolve(c->mod_host, base, name, out, cap) != 0) {
        free(out);
        JS_ThrowTypeError(jc, "Failed to resolve module specifier \"%s\"", name);
        return NULL;
    }
    char *r = js_strdup(jc, out);
    free(out);
    return r;
}

/* Sets import.meta.url of a compiled module to its absolute URL. */
static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url) {
    JSModuleDef *m = (JSModuleDef *)JS_VALUE_GET_PTR(compiled);
    JSValue meta = JS_GetImportMeta(jc, m);
    if (!JS_IsException(meta))
        JS_DefinePropertyValueStr(jc, meta, "url", JS_NewString(jc, url), JS_PROP_C_W_E);
    JS_FreeValue(jc, meta);
}

/* QuickJS loader: fetch through the host, count against the caps, compile. */
static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque) {
    js_context *c = (js_context *)opaque;
    if (c == NULL || c->mod_fetch == NULL) {
        JS_ThrowTypeError(jc, "Cannot load module \"%s\"", name);
        return NULL;
    }
    if (c->mod_count >= JS_MODULE_MAX) {
        JS_ThrowTypeError(jc, "Too many modules");
        return NULL;
    }
    size_t len = 0;
    char *src = c->mod_fetch(c->mod_host, name, &len);
    if (src == NULL) {
        JS_ThrowTypeError(jc, "Failed to load module \"%s\"", name);
        return NULL;
    }
    if (len > JS_MODULE_BYTES_MAX - c->mod_bytes || len == (size_t)-1) {
        free(src);
        JS_ThrowTypeError(jc, "Module sources exceed the page budget");
        return NULL;
    }
    char *code = host_dup(src, len);      /* JS_Eval needs NUL termination */
    free(src);
    if (code == NULL) { JS_ThrowOutOfMemory(jc); return NULL; }
    c->mod_count++;
    c->mod_bytes += len;
    JSValue compiled = JS_Eval(jc, code, len, name,
                               JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);
    free(code);
    if (JS_IsException(compiled)) return NULL;
    mod_set_meta(jc, compiled, name);
    JSModuleDef *m = (JSModuleDef *)JS_VALUE_GET_PTR(compiled);
    JS_FreeValue(jc, compiled);
    return m;
}

static char *mod_normalize(JSContext *jc, const char *base, const char *name, void *opaque);
static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque);

void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,
                        js_module_fetch_fn fetch, void *host) {
    if (ctx == NULL) return;
    ctx->mod_resolve = resolve;
    ctx->mod_fetch = fetch;
    ctx->mod_host = host;
    /* A dynamic import() from a CLASSIC script needs the loader too: installing it only in
     * js_eval_module made every code-splitting bundle fail with "could not load module"
     * until some module script had happened to run first. */
    if (resolve != NULL && fetch != NULL)
        JS_SetModuleLoaderFunc(ctx->rt, mod_normalize, mod_loader, ctx);
}

/* Fills res from the pending exception (or the given rejection value, which is
 * thrown first so the one capture path formats both). */
static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,
                          js_status kind) {
    if (use_reason) JS_Throw(ctx->ctx, reason);
    int was_interrupted = ctx->interrupted;
    ctx->has_deadline = 0;
    size_t mlen = 0;
    char *msg = capture_exception(ctx->ctx, &mlen, &res->file, &res->line, &res->col);
    res->value = msg;
    res->value_len = (msg != NULL) ? mlen : 0;
    res->is_exception = 1;
    js_status st = was_interrupted ? JS_ERR_TIMEOUT : ctx->mem.hit ? JS_ERR_MEMORY : kind;
    res->status = st;
    return st;
}

js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,
                         js_result *res) {
    if (res != NULL) memset(res, 0, sizeof *res);
    if (ctx == NULL || src == NULL || res == NULL) return JS_ERR_NULL_ARG;
    if (name == NULL) name = "<module>";
    js_status vs = js_validate_source(src, len, &ctx->limits);
    if (vs != JS_OK) { res->status = vs; return vs; }
    char *code = host_dup(src, len);
    if (code == NULL) { res->status = JS_ERR_OOM; return JS_ERR_OOM; }

    /* The loader is per runtime; (re)installing it here keeps a context that never
     * evaluates a module exactly as it was. */
    JS_SetModuleLoaderFunc(ctx->rt, mod_normalize, mod_loader, ctx);
    ctx->mem.hit = 0;
    arm_deadline(ctx, ctx->limits.time_budget_ms);

    JSValue compiled = JS_Eval(ctx->ctx, code, len, name,
                               JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);
    free(code);
    if (JS_IsException(compiled)) {
        /* Dependencies are resolved and loaded while compiling: only a real
         * SyntaxError is a syntax failure, a failed import is a runtime one. */
        JSValue e = JS_GetException(ctx->ctx);
        JSValue nm = JS_GetPropertyStr(ctx->ctx, e, "name");
        const char *ns = JS_ToCString(ctx->ctx, nm);
        int syntax = (ns != NULL && strcmp(ns, "SyntaxError") == 0);
        if (ns != NULL) JS_FreeCString(ctx->ctx, ns);
        JS_FreeValue(ctx->ctx, nm);
        return mod_fail(ctx, res, e, 1, syntax ? JS_ERR_SYNTAX : JS_ERR_RUNTIME);
    }
    mod_set_meta(ctx->ctx, compiled, name);

    /* Link + evaluate: imports load here. quickjs-ng returns the evaluation promise
     * (top-level await); drain jobs under the same deadline until it settles. */
    JSValue result = JS_EvalFunction(ctx->ctx, compiled);
    if (JS_IsException(result))
        return mod_fail(ctx, res, JS_UNDEFINED, 0, JS_ERR_RUNTIME);
    for (int guard = 0; guard < 4096 && JS_IsJobPending(ctx->rt) && !ctx->interrupted; ++guard) {
        JSContext *jc = NULL;
        int r = JS_ExecutePendingJob(ctx->rt, &jc);
        if (r == 0) break;
        if (r < 0 && jc != NULL) JS_FreeValue(jc, JS_GetException(jc));
    }
    JSPromiseStateEnum ps = JS_PromiseState(ctx->ctx, result);
    if (ps == JS_PROMISE_REJECTED) {
        JSValue reason = JS_PromiseResult(ctx->ctx, result);
        JS_FreeValue(ctx->ctx, result);
        return mod_fail(ctx, res, reason, 1, JS_ERR_RUNTIME);
    }
    int timed_out = ctx->interrupted && ps == JS_PROMISE_PENDING;
    JS_FreeValue(ctx->ctx, result);
    ctx->has_deadline = 0;
    res->status = timed_out ? JS_ERR_TIMEOUT : JS_OK;
    return res->status;
}

/* --- realms (spec/js_sandbox.md 7c) --- */

/* The owning js_context rides in each native's closure data, split into 32-bit
 * halves (no assumption about JS number width). */
static js_context *realm_owner(JSContext *ctx, JSValueConst *data) {
    uint32_t lo = 0, hi = 0;
    if (JS_ToUint32(ctx, &lo, data[0]) != 0 || JS_ToUint32(ctx, &hi, data[1]) != 0) return NULL;
    return (js_context *)(uintptr_t)(((uint64_t)hi << 32) | lo);
}

/* The context whose global object is g: the owner's own or one of its realms. */
static JSContext *realm_of(js_context *c, JSValueConst g) {
    if (!JS_IsObject(g)) return NULL;
    void *want = JS_VALUE_GET_PTR(g);
    for (size_t i = 0; i <= c->nrealms; ++i) {
        JSContext *r = (i < c->nrealms) ? c->realms[i] : c->ctx;
        JSValue rg = JS_GetGlobalObject(r);
        int same = JS_VALUE_GET_PTR(rg) == want;
        JS_FreeValue(r, rg);
        if (same) return r;
    }
    return NULL;
}

static JSValue throw_named(JSContext *ctx, const char *name, const char *msg) {
    JSValue e = JS_NewError(ctx);
    if (JS_IsException(e)) return e;
    JS_DefinePropertyValueStr(ctx, e, "message", JS_NewString(ctx, msg),
                              JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE);
    JS_DefinePropertyValueStr(ctx, e, "name", JS_NewString(ctx, name),
                              JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE);
    return JS_Throw(ctx, e);
}

static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,
                           JSValueConst *argv, int magic, JSValueConst *data) {
    (void)this_val; (void)argc; (void)argv; (void)magic;
    js_context *c = realm_owner(ctx, data);
    if (c == NULL || c->nrealms >= JS_REALM_MAX) return JS_NULL;
    JSContext *r = JS_NewContext(c->rt);       /* compute intrinsics only */
    if (r == NULL) return JS_ThrowOutOfMemory(ctx);
    c->realms[c->nrealms++] = r;
    return JS_GetGlobalObject(r);
}

/* __realmEval(global, code, name): a classic script in that realm. Its exception
 * comes back as an Error of the CALLER's realm (name + message); an uncatchable one
 * (the time budget) is rethrown as is, so the page cannot swallow a timeout. */
static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,
                            JSValueConst *argv, int magic, JSValueConst *data) {
    (void)this_val; (void)argc; (void)magic;
    js_context *c = realm_owner(ctx, data);
    JSContext *r = (c != NULL) ? realm_of(c, argv[0]) : NULL;
    if (r == NULL || r == c->ctx) return JS_ThrowTypeError(ctx, "not a realm global");
    size_t len = 0;
    const char *code = JS_ToCStringLen(ctx, &len, argv[1]);
    if (code == NULL) return JS_EXCEPTION;
    const char *name = JS_ToCString(ctx, argv[2]);
    if (name == NULL) { JS_FreeCString(ctx, code); return JS_EXCEPTION; }
    JSValue v = JS_Eval(r, code, len, name, JS_EVAL_TYPE_GLOBAL);
    JS_FreeCString(ctx, code);
    JS_FreeCString(ctx, name);
    if (!JS_IsException(v)) { JS_FreeValue(r, v); return JS_UNDEFINED; }
    JSValue exc = JS_GetException(r);
    if (JS_IsUncatchableError(exc) || c->interrupted) return JS_Throw(ctx, exc);
    char nbuf[64] = "Error", mbuf[512] = "";
    if (JS_IsObject(exc)) {
        JSValue nv = JS_GetPropertyStr(r, exc, "name"), mv = JS_GetPropertyStr(r, exc, "message");
        const char *ns = JS_ToCString(r, nv), *ms = JS_ToCString(r, mv);
        if (ns != NULL) { snprintf(nbuf, sizeof nbuf, "%s", ns); JS_FreeCString(r, ns); }
        if (ms != NULL) { snprintf(mbuf, sizeof mbuf, "%s", ms); JS_FreeCString(r, ms); }
        JS_FreeValue(r, nv);
        JS_FreeValue(r, mv);
    } else {
        const char *ms = JS_ToCString(r, exc);
        if (ms != NULL) { snprintf(mbuf, sizeof mbuf, "%s", ms); JS_FreeCString(r, ms); }
    }
    JS_FreeValue(r, JS_GetException(r));          /* a throwing getter above */
    JS_FreeValue(r, exc);
    return throw_named(ctx, nbuf, mbuf);
}

/* __realmClone(value, global): structured copy into global's realm through the
 * serializer WITHOUT bytecode -- a function cannot cross (DataCloneError). */
static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,
                             JSValueConst *argv, int magic, JSValueConst *data) {
    (void)this_val; (void)argc; (void)magic;
    js_context *c = realm_owner(ctx, data);
    JSContext *r = (c != NULL) ? realm_of(c, argv[1]) : NULL;
    if (r == NULL) return JS_ThrowTypeError(ctx, "not a realm global");
    size_t len = 0;
    uint8_t *buf = JS_WriteObject(ctx, &len, argv[0], JS_WRITE_OBJ_REFERENCE);
    if (buf == NULL) {
        if (c->interrupted) return JS_EXCEPTION;
        JS_FreeValue(ctx, JS_GetException(ctx));
        return throw_named(ctx, "DataCloneError", "The object could not be cloned.");
    }
    JSValue out = JS_ReadObject(r, buf, len, JS_READ_OBJ_REFERENCE);
    js_free(ctx, buf);
    if (JS_IsException(out)) {
        JS_FreeValue(r, JS_GetException(r));
        return throw_named(ctx, "DataCloneError", "The object could not be cloned.");
    }
    return out;
}

js_status js_install_realms(js_context *ctx) {
    if (ctx == NULL || ctx->ctx == NULL) return JS_ERR_NULL_ARG;
    JSContext *jc = ctx->ctx;
    uint64_t p = (uint64_t)(uintptr_t)ctx;
    static const struct { const char *name; JSCFunctionData *fn; int len; } N[] = {
        { "__realmNew",   m_realm_new,   0 },
        { "__realmEval",  m_realm_eval,  3 },
        { "__realmClone", m_realm_clone, 2 },
    };
    JSValue g = JS_GetGlobalObject(jc);
    for (size_t i = 0; i < sizeof N / sizeof N[0]; ++i) {
        JSValue d[2] = { JS_NewUint32(jc, (uint32_t)p), JS_NewUint32(jc, (uint32_t)(p >> 32)) };
        JSValue f = JS_NewCFunctionData(jc, N[i].fn, N[i].len, 0, 2, d);
        JS_FreeValue(jc, d[0]);
        JS_FreeValue(jc, d[1]);
        if (JS_IsException(f) || JS_DefinePropertyValueStr(jc, g, N[i].name, f,
                                    JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE) < 0) {
            JS_FreeValue(jc, g);
            return JS_ERR_OOM;
        }
    }
    JS_FreeValue(jc, g);
    return JS_OK;
}
