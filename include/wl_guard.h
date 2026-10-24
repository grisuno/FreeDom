#ifndef FREEDOM_WL_GUARD_H
#define FREEDOM_WL_GUARD_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

struct wl_display;

/*
 * wl_guard -- keeps the Wayland connection drained while the GUI thread is busy.
 *
 * A compositor queues events for a client in a small buffer (4 KiB) backed by the socket; a
 * client that does not read for a few seconds while the pointer moves gets DISCONNECTED
 * ("libwayland: Data too big for buffer ... error in client communication"). Freedom blocks its
 * GUI thread on page loads, image fetches and big layouts, so a helper thread reads the socket
 * meanwhile. It uses libwayland's documented multi-thread pattern: wl_display_prepare_read_queue
 * on a PRIVATE (always empty) queue, so the events are only enqueued -- every handler still runs
 * on the GUI thread, in order, when the main loop dispatches. See spec/wl_guard.md.
 */

typedef struct wl_guard wl_guard;

/* Starts the helper for `display` (NULL on failure: the GUI then runs unguarded). */
wl_guard *wlg_start(struct wl_display *display);

/* Stops and joins the helper. Call before wl_display_disconnect. NULL is a no-op. */
void wlg_stop(wl_guard *g);

#endif /* FREEDOM_WL_GUARD_H */
