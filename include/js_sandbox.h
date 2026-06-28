#ifndef FREEDOM_JS_SANDBOX_H
#define FREEDOM_JS_SANDBOX_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * js_sandbox — runs untrusted JavaScript in an isolated, bounded context.
 *
 * Second Zero-Trust boundary after parsing: remote script is hostile by
 * default. The sandbox has no host I/O (no filesystem, network, process or OS)
 * and enforces hard memory, stack and time limits, so a malicious script can
 * neither escape isolation, exfiltrate host data, exhaust memory, nor hang the
 * browser.
 *
 * The QuickJS-ng backend is fully encapsulated: no JS* / JSValue type appears
 * here. See spec/js_sandbox.md for the full contract.
 */

typedef enum js_status {
    JS_OK = 0,
    JS_ERR_NULL_ARG,   /* a required pointer argument was NULL */
    JS_ERR_EMPTY,      /* source length was zero */
    JS_ERR_TOO_LARGE,  /* source exceeded max_source_bytes */
    JS_ERR_SYNTAX,     /* compile/parse error */
    JS_ERR_RUNTIME,    /* uncaught JS exception at runtime */
    JS_ERR_TIMEOUT,    /* evaluation exceeded the time budget and was interrupted */
    JS_ERR_MEMORY,     /* engine hit the memory limit (or ran out of memory) */
    JS_ERR_OOM,        /* host allocation failed */
    JS_ERR_INTERNAL    /* backend returned an unexpected state */
} js_status;

/* Per-evaluation resource limits. A field set to 0 receives that field's
 * default: "no limit" is deliberately not representable (secure by default). */
typedef struct js_limits {
    size_t   max_source_bytes;   /* hard cap on script length */
    size_t   memory_limit_bytes; /* engine heap cap */
    size_t   max_stack_bytes;    /* engine stack cap */
    uint64_t time_budget_ms;     /* wall-clock budget for one evaluation */
} js_limits;

/* Opaque isolated sandbox (owns one engine runtime + context). */
typedef struct js_context js_context;

typedef struct js_result {
    js_status status;
    char     *value;     /* owned; textual result, or exception message; may be NULL */
    size_t    value_len; /* bytes in value excluding the trailing NUL */
    int       is_exception; /* nonzero if value holds an error message, not a value */
} js_result;

#define JS_DEFAULT_MAX_SOURCE   ((size_t)(4u * 1024u * 1024u))
#define JS_DEFAULT_MEM_LIMIT    ((size_t)(64u * 1024u * 1024u))
#define JS_DEFAULT_STACK_LIMIT  ((size_t)(256u * 1024u))
#define JS_DEFAULT_TIME_BUDGET  ((uint64_t)1000)

/* Returns limits with the secure defaults applied. */
js_limits js_limits_default(void);

/* --- Pure validator (no engine): NULL / empty / size-cap checks. --- */
js_status js_validate_source(const char *src, size_t len, const js_limits *lim);

/* --- Sandbox lifecycle. --- */

/* Creates an isolated, hardened sandbox (memory/stack/time limits armed; no I/O
 * modules). lim == NULL => js_limits_default().
 * out == NULL => JS_ERR_NULL_ARG. Allocation failure => JS_ERR_OOM.
 * On JS_OK, *out must be released with js_context_free. */
js_status js_context_new(const js_limits *lim, js_context **out);

/* Idempotent; safe on NULL and safe to call twice. */
void js_context_free(js_context *ctx);

/* --- Evaluation. --- */

/* Evaluates untrusted JS in the sandbox; captures the result (or exception) in
 * *res. No host I/O is ever performed.
 * Any NULL argument => JS_ERR_NULL_ARG.
 * On return, *res is populated and must be released with js_result_free. */
js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res);

/* Convenience: new context, evaluate once, free the context. Same error codes
 * as js_eval. lim == NULL => defaults. */
js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res);

/* Adjusts the wall-clock budget armed on each subsequent js_eval. Used to enforce
 * a single page-wide budget across a sequence of evaluations (e.g. a page's inline
 * scripts run one by one): the caller lowers the budget to the time remaining before
 * each call, so isolating scripts into separate evals does not multiply the cap.
 * No-op on a NULL context. Does not affect an evaluation already in progress. */
void js_set_time_budget(js_context *ctx, uint64_t budget_ms);

/* Idempotent; safe on a zero-initialised struct and safe to call twice. */
void js_result_free(js_result *res);

/* Internal seam for binding layers (e.g. js_dom): the underlying engine context
 * as an opaque handle (so this header stays free of backend types), or NULL.
 * Valid only while ctx is alive. Binding modules are the intended consumers. */
void *js_context_raw(js_context *ctx);

#endif /* FREEDOM_JS_SANDBOX_H */
