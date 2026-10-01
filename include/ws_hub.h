#ifndef FREEDOM_WS_HUB_H
#define FREEDOM_WS_HUB_H

#include <poll.h>
#include <stddef.h>

#include "secure_fetch.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * ws_hub — the WebSocket connections of one trusted page, held on the TRUSTED side
 * (the confined worker never touches a socket). Opens asynchronously (a thread per
 * open, result through a socket pair the GUI polls), pumps and reassembles messages, and
 * closes everything when the page changes. Policy (TLS/PQ/realm/identity) is
 * sf_ws_open's; WHETHER to open is the caller's decision. See spec/ws_hub.md.
 */

#define WH_MAX 8   /* == JD_WS_MAX: sockets per page */

/* Event kinds delivered to the page; values match tab_ws_event_kind. */
enum { WH_EV_OPEN = 1, WH_EV_TEXT = 2, WH_EV_BINARY = 3, WH_EV_CLOSE = 4, WH_EV_ERROR = 5 };

/* Abnormal closure code (RFC 6455 7.4.1) reported for a failed or broken socket. */
#define WH_CLOSE_ABNORMAL 1006

typedef void (*wh_emit_fn)(void *ctx, int id, int kind, int code, const char *data, size_t len);

typedef struct wh_hub wh_hub;

/* New empty hub with its notify pipe, or NULL on OOM / pipe failure. */
wh_hub *wh_new(void);

/* Closes every connection and frees the hub. Pending opens finish on their own
 * threads and discard their result. NULL is a no-op. */
void wh_free(wh_hub *h);

/* Read end of the notify channel (a socket pair): poll it for POLLIN and call wh_on_notify. */
int wh_notify_fd(const wh_hub *h);

/* Starts opening url for page socket id on a thread (cfg and all its strings are
 * copied). Returns 0 when started; -1 (nothing started) on a duplicate id, a full
 * hub, NULL args or OOM -- the caller then reports ERROR + CLOSE to the page. */
int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg);

/* Drains finished opens: success => the connection joins the hub and WH_EV_OPEN is
 * emitted; failure => WH_EV_ERROR then WH_EV_CLOSE(WH_CLOSE_ABNORMAL). Results from a
 * previous generation (before wh_close_all) are closed and dropped silently. */
void wh_on_notify(wh_hub *h, wh_emit_fn emit, void *ctx);

/* Sends one message on an OPEN connection. 0, or -1 (unknown id / broken link). */
int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary);

/* The page closed socket id: sends a close frame and frees it (also cancels a
 * pending open for that id: its result will be dropped). */
void wh_close(wh_hub *h, int id);

/* The page is going away: closes everything and bumps the generation. */
void wh_close_all(wh_hub *h);

/* Fills up to cap pollfds (POLLIN) and the matching page ids for the open
 * connections. Returns the count. */
size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap);

/* Reads everything pending on socket id without blocking, emitting each complete
 * message; a close frame emits WH_EV_CLOSE; an error or an oversized message emits
 * WH_EV_ERROR + WH_EV_CLOSE(WH_CLOSE_ABNORMAL). The connection is freed on close. */
void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx);

/* Number of live (open) connections. */
size_t wh_count(const wh_hub *h);

#endif /* FREEDOM_WS_HUB_H */
