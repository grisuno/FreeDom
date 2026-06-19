#ifndef FREEDOM_TAB_H
#define FREEDOM_TAB_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#include "page_view.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * tab — a long-lived, sandboxed per-tab worker process.
 *
 * Tab isolation, evolved from the one-shot renderer: each tab is its own forked
 * child, confined with Landlock (no filesystem) + seccomp-bpf before it touches
 * any remote content. The child parses untrusted HTML, builds the inert DOM, and
 * runs untrusted JavaScript in-process against that DOM (js_sandbox + js_dom +
 * js_env, all inside the confinement). The parent never parses or executes the
 * hostile bytes; it drives the child over a private pipe protocol and survives a
 * child crash/exploit, reporting TAB_ERR_DEAD instead of dying.
 *
 * The QuickJS / Lexbor backends stay fully encapsulated (no backend type here).
 * See spec/tab.md for the full contract.
 */

typedef enum tab_status {
    TAB_OK = 0,
    TAB_ERR_NULL_ARG,
    TAB_ERR_SPAWN,     /* pipe()/fork() failed */
    TAB_ERR_CONFINE,   /* child could not confine itself (fail closed) */
    TAB_ERR_IO,        /* IPC framing failure */
    TAB_ERR_TOO_LARGE, /* request/response exceeded the size cap */
    TAB_ERR_DEAD,      /* child is not alive (crashed, killed, or closed) */
    TAB_ERR_RENDER,    /* HTML parse / DOM build failed in the child */
    TAB_ERR_SCRIPT,    /* internal failure running the script (not a JS exception) */
    TAB_ERR_OOM
} tab_status;

/* Opaque parent-side handle to a tab worker. */
typedef struct tab tab;

/* Inert result of loading a page: title + extracted text + structured display
 * list (all owned). text is kept for headless/plain output; view carries the
 * inline runs (headings, links, block breaks) the GUI lays out and paints. */
typedef struct tab_page {
    char    *title;     /* NUL-terminated; may be NULL */
    size_t   title_len; /* excludes the trailing NUL */
    char    *text;      /* NUL-terminated; may be NULL */
    size_t   text_len;
    pv_view *view;      /* owned display list; may be NULL */
} tab_page;

/* Result of evaluating script: the value, or a JS error message. */
typedef struct tab_eval_result {
    char  *value;        /* owned; NUL-terminated; may be NULL */
    size_t value_len;
    int    is_exception; /* nonzero if value holds a JS error message, not a value */
} tab_eval_result;

/* Pixels of a decoded image, produced inside the confined worker. data is owned
 * and holds premultiplied ARGB32 (Cairo's CAIRO_FORMAT_ARGB32 layout: bytes
 * B,G,R,A; stride == width*4). data == NULL means the worker could not decode the
 * bytes (not a PNG, corrupt, or out of bounds): the caller shows the placeholder. */
typedef struct tab_image {
    uint32_t width;
    uint32_t height;
    uint32_t stride;
    uint8_t *data;
    size_t   data_len;  /* stride * height when data != NULL, else 0 */
} tab_image;

#define TAB_MAX_INPUT ((size_t)(32u * 1024u * 1024u))

/* Spawns and confines a tab worker. On TAB_OK, *out must be released with
 * tab_close. Returns TAB_ERR_CONFINE if the child could not sandbox itself. */
tab_status tab_open(tab **out);

/* Loads untrusted HTML into the tab: the child parses it, builds the inert DOM,
 * and arms a fresh JS context bound to that DOM. Replaces any previously loaded
 * page. On TAB_OK, *out is populated and must be released with tab_page_free. */
tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out);

/* Evaluates untrusted JS in the tab's current context (sees the loaded DOM,
 * navigator/screen/performance, canvas/audio). A JS-level error is reported via
 * out->is_exception with TAB_OK; TAB_ERR_* is reserved for transport/worker
 * failures. On TAB_OK, *out must be released with tab_eval_result_free. */
tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out);

/* Decodes image bytes (PNG) inside the confined worker and returns the pixels to
 * the parent, which never decodes hostile image bytes itself. Independent of any
 * loaded page. bytes may be NULL only when len == 0. On TAB_OK, *out is populated
 * and must be released with tab_image_free; out->data == NULL means the worker
 * could not decode (caller shows the placeholder), which is not a transport error.
 * TAB_ERR_* is reserved for transport/worker failures. */
tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out);

/* Nonzero while the worker process is believed alive. */
int tab_alive(const tab *t);

/* The worker's process id (for monitoring), or -1. */
pid_t tab_child_pid(const tab *t);

/* Terminates the worker and frees the handle. Safe on NULL. */
void tab_close(tab *t);

/* Idempotent releasers for the result structs. Safe on NULL / zeroed structs. */
void tab_page_free(tab_page *p);
void tab_eval_result_free(tab_eval_result *r);
void tab_image_free(tab_image *img);

#endif /* FREEDOM_TAB_H */
