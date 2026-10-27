#ifndef FREEDOM_JS_TRUSTED_H
#define FREEDOM_JS_TRUSTED_H

#include <stddef.h>

#include "js_dom.h"
#include "js_sandbox.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * js_trusted — the page-script surfaces that exist ONLY for a trusted host
 * (allow.conf AND js.conf): window.open (noopener), WebSocket and the in-memory
 * localStorage. Kept apart from js_dom so the "trusted only" contract lives in one
 * auditable place: the worker installs these solely when the load was granted net,
 * and the confined worker still never touches a socket or the disk -- every one of
 * them only RECORDS operations for the trusted parent. See spec/js_dom.md 7e-7f and
 * spec/web_storage.md.
 */

/* Installs window.open for a TRUSTED host (allow.conf AND js.conf) only (plan B4c).
 * noopener semantics: it returns null (no cross-window reference, so no same-origin
 * channel) and only records up to 4 raw targets per operation for the parent, which
 * gates each like a navigation and honours it on a user gesture only. Untrusted
 * pages never get it (typeof open === 'undefined'). */
jd_status jt_enable_open(js_context *ctx);

/* Replaces the synthetic IntersectionObserver with a REAL one for a TRUSTED host
 * (spec/js_observers.md): it measures each target's laid-out rect (js_geom) against the
 * real viewport plus rootMargin and notifies on every change of state. Untrusted pages
 * keep the synthetic always-intersecting observer and never see geometry. */
jd_status jt_enable_observers(js_context *ctx);

/* The parent installed a new geometry table (layout or scroll changed): re-evaluates
 * every observed target and fires a window 'scroll' event when the scroll moved. A
 * no-op when jt_enable_observers was never called. Bounded by JT_IO_MAX targets. */
jd_status jt_geometry_changed(js_context *ctx);

/* Drains the recorded window.open targets as "url\n" lines, or NULL when none. */
char *jt_take_opens(js_context *ctx);

/* --- WebSocket (spec/js_dom.md 7f): trusted host only --- */

#define JT_WS_MAX          8                               /* sockets per page */
#define JT_WS_MAX_OPS      64                              /* ops per response */
#define JT_WS_MAX_BYTES    ((size_t)(4u * 1024u * 1024u))  /* op payload per response */

typedef enum jt_ws_kind {
    JT_WS_OPEN = 1,       /* data = absolute wss:// URL */
    JT_WS_SEND_TEXT = 2,  /* data = UTF-8 text */
    JT_WS_SEND_BIN = 3,   /* data = raw bytes */
    JT_WS_CLOSE = 4,      /* data empty */
    /* Frame traffic (spec/frame_broker.md) rides the same parent-mediated queue. */
    JT_WS_FRAME_POST = 5, /* id: -1 parent, -2 top, >0 child token; data "targetOrigin\nJSON" */
    JT_WS_FRAME_OPEN = 6, /* id: child token; data = absolute https URL of the <iframe src> */
    JT_WS_FRAME_CLOSE = 7 /* id: child token; the <iframe> left the document or changed src */
} jt_ws_kind;

typedef struct jt_ws_op {
    int    kind;          /* jt_ws_kind */
    int    id;            /* page-local socket id */
    char  *data;          /* owned, NUL-terminated (binary may contain NULs) */
    size_t len;
} jt_ws_op;

typedef enum jt_ws_event_kind {
    JT_WSE_OPEN = 1, JT_WSE_TEXT = 2, JT_WSE_BINARY = 3, JT_WSE_CLOSE = 4, JT_WSE_ERROR = 5,
    JT_WSE_FRAME_MSG = 6  /* data "senderOrigin\nrelation\nJSON"; relation p|t|c<token> */
} jt_ws_event_kind;

/* Installs window.parent/window.top, iframe.contentWindow and cross-window postMessage for a
 * trusted page. frame_id is 0 for the top document and >0 for a document the parent loaded into
 * an iframe (then parent/top are proxies; in the top document both are the window itself). The
 * worker only records ops; the parent routes with frame_broker and re-checks every origin. */
jd_status jt_enable_frames(js_context *ctx, int frame_id);

/* Installs the WebSocket constructor (trusted host only). The worker never opens a
 * socket: the object records operations for the parent (jt_take_ws). */
jd_status jt_enable_ws(js_context *ctx);

/* Drains up to cap recorded operations into ops (each data owned; release with
 * jt_ws_ops_free). Returns the count. Operations past JT_WS_MAX_OPS/JT_WS_MAX_BYTES
 * are dropped and their socket is errored+closed on the page side. */
size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap);
void   jt_ws_ops_free(jt_ws_op *ops, size_t n);

/* Delivers a socket event from the parent: data enters JS as a VALUE (a string for
 * text, an ArrayBuffer for binary, the reason for close), never as source. Returns 1
 * when a live socket with that id received it. */
int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len);

/* --- in-memory localStorage (spec/web_storage.md): trusted host only --- */

/* Replaces localStorage with a store seeded from the parent's snapshot for this
 * origin (web_storage wire format; pairs enter JS as VALUES). Writes mark it dirty and
 * a store past WST_QUOTA throws QuotaExceededError. An invalid snapshot seeds an
 * empty store. Call only for an allow.conf AND js.conf host. */
jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len);

/* When the store changed since the last call, returns 1 with an owned snapshot of
 * the whole store in *out (length *len) and clears the dirty bit; 0 otherwise. */
int jt_take_storage(js_context *ctx, char **out, size_t *len);

/* Dedicated Worker for a trusted (allow∩js) page (spec/js_dom.md 7i): each worker
 * runs in its own realm (js_install_realms) of this context's runtime, inside the
 * same confined process and budget. ctx NULL => JD_ERR_NULL_ARG. */
jd_status jt_enable_worker(js_context *ctx);

#endif /* FREEDOM_JS_TRUSTED_H */
