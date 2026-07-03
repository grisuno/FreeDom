#ifndef FREEDOM_TAB_H
#define FREEDOM_TAB_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#include "freebug.h"
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
    /* JS-requested navigation (Hito 20e): a resolved, policy-gated https/file target
     * the page's JS asked to navigate to (location.href= / assign / replace / reload),
     * or NULL when none. nav_replace mirrors location.replace (history semantics). The
     * parent already gated the worker's raw request with ln_resolve; the caller still
     * drives it through the normal load path, re-applying ALL network policy. */
    char    *nav_url;
    int      nav_replace;
    /* Console output (console.* calls + any uncaught script exception) captured
     * while loading the page, for the Freebug devtools. Owned; drained from the
     * worker. Empty when JS did not run. Release via tab_page_free. */
    fb_buffer console;
} tab_page;

/* Result of evaluating script: the value, or a JS error message. */
typedef struct tab_eval_result {
    char  *value;        /* owned; NUL-terminated; may be NULL */
    size_t value_len;
    int    is_exception; /* nonzero if value holds a JS error message, not a value */
    /* console.* output produced by THIS evaluation (Freebug REPL transcript).
     * Owned; release via tab_eval_result_free. */
    fb_buffer console;
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

/* Worker process entry. tab_open forks AND re-execs this same binary so the worker
 * inherits none of the parent's address space (no other tabs' content, fresh ASLR).
 * Call tab_worker_dispatch(argc, argv) as the FIRST thing in main(): if argv is the
 * internal "--tab-worker <rfd> <wfd>" invocation it runs the confined worker loop on
 * those pipe fds and never returns (_exit); otherwise it returns and main() proceeds
 * normally. Because the worker re-execs /proc/self/exe, EVERY binary that links tab
 * and reaches tab_open (the app and the test harness) must call this first. */
void tab_worker_dispatch(int argc, char **argv);

/* Pure validator of the worker handoff arguments (the security-relevant surface of
 * the exec): returns nonzero and writes the two fds iff argv is exactly
 * "<prog> --tab-worker <rfd> <wfd>" with both fds non-negative decimal integers
 * within a sane bound. No side effects; fail-closed (any malformation => 0). */
int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd);

/* Spawns and confines a tab worker. On TAB_OK, *out must be released with
 * tab_close. Returns TAB_ERR_CONFINE if the child could not sandbox itself. */
tab_status tab_open(tab **out);

/* Subresource (XMLHttpRequest/fetch) network bridge. The confined worker has no network;
 * when the page's script issues an XHR/fetch the worker proxies the request to the parent,
 * which calls this callback to perform the policy-checked fetch (host blocklist/tracker
 * filter, realm routing, TLS-PQ) -- the worker never touches a socket.
 *   method/url: the request line; url is the RAW string from the page (the callback must
 *     resolve/validate it and refuse cross-policy targets). body/body_len: request body.
 *   On success return 0 and set *out_status (HTTP status), *out_body / *out_body_len
 *     (malloc'd response bytes, tab frees with free()), *out_ctype (malloc'd Content-Type,
 *     may be NULL). Return non-zero to refuse (the page's XHR gets status 0, empty body).
 * The callback runs on the thread calling tab_load_full, synchronously, once per request. */
typedef int (*tab_fetch_fn)(void *ctx, const char *method, const char *url,
                            const char *body, size_t body_len,
                            int *out_status, char **out_body, size_t *out_body_len,
                            char **out_ctype);

/* Installs the subresource fetcher used for XHR/fetch (NULL clears it: requests are then
 * refused). fn/ctx must outlive any tab_load_full call that may trigger a subresource. */
void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx);

/* Grants/revokes page-JS network access (XMLHttpRequest/fetch) for the NEXT load. Set it
 * true ONLY when the page's host is in BOTH allow.conf AND js.conf (the sovereignty
 * boundary); false (default) keeps XHR/fetch undefined (Same-Origin-by-construction). */
void tab_set_net_allowed(tab *t, int allowed);

/* Loads untrusted HTML into the tab: the child parses it, builds the inert DOM,
 * and arms a fresh JS context bound to that DOM. Replaces any previously loaded
 * page. On TAB_OK, *out is populated and must be released with tab_page_free. */
tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out);

/* As tab_load, but run_js carries the page's JS policy (rdp_caps.js): it selects
 * <noscript> handling in the built view (off => fallback shown, on => suppressed)
 * and is where allowlisted page-script execution will hook in (live-DOM milestone).
 * tab_load is tab_load_ex with run_js == 0. */
tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out);

/* As tab_load_ex, plus the page's URL, a distraction-free (reader) flag and the user's
 * color-scheme preference (prefers_dark). page_url (NULL allowed) backs the page JS's
 * real `location.*` AND is the trusted base that gates any JS-requested navigation
 * (ln_resolve): out->nav_url is set only to a resolved, policy-allowed target. reader
 * and prefers_dark are forwarded to pv_build_full: reader drops boilerplate
 * (<nav>/<header>/<footer>/<aside>); prefers_dark gates the author's
 * @media(prefers-color-scheme) rules (auto dark mode). tab_load_ex is tab_load_full
 * with page_url == NULL, reader == 0 and prefers_dark == 0. */
tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
                         int run_js, int reader, int prefers_dark, tab_page *out);

/* Dispatches a click event on the loaded page's node_id. The worker fires any JS
 * click handlers registered for that node and returns the re-derived view, so the
 * caller can repaint DOM mutations caused by the handler. On TAB_OK, *out is
 * populated and must be released with tab_page_free. */
tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out);

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
