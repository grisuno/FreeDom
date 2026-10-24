/*
 * wl_guard -- drains the Wayland socket while the GUI thread is busy (spec/wl_guard.md).
 */

#define _DEFAULT_SOURCE

#include "wl_guard.h"

#include <poll.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <unistd.h>

#include <wayland-client.h>

#define WLG_POLL_MS 100

struct wl_guard {
    struct wl_display     *display;
    struct wl_event_queue *idle_queue;   /* never used for objects: always empty */
    pthread_t              thread;
    atomic_int             stop;
};

static void *guard_main(void *arg) {
    wl_guard *g = (wl_guard *)arg;
    int fd = wl_display_get_fd(g->display);
    while (!atomic_load(&g->stop)) {
        struct pollfd pf = { fd, POLLIN, 0 };
        int r = poll(&pf, 1, WLG_POLL_MS);
        if (r <= 0) continue;
        if (pf.revents & (POLLHUP | POLLERR)) break;   /* the display is gone: main loop reports it */
        /* An empty private queue always allows the read; the events land on the proxies' own
         * queues (the default one) and are dispatched by the main thread, never here. */
        if (wl_display_prepare_read_queue(g->display, g->idle_queue) != 0) {
            usleep(1000);
            continue;
        }
        if (wl_display_read_events(g->display) < 0) break;
    }
    return NULL;
}

wl_guard *wlg_start(struct wl_display *display) {
    if (display == NULL) return NULL;
    wl_guard *g = (wl_guard *)calloc(1, sizeof *g);
    if (g == NULL) return NULL;
    g->display = display;
    g->idle_queue = wl_display_create_queue(display);
    if (g->idle_queue == NULL) { free(g); return NULL; }
    atomic_init(&g->stop, 0);
    if (pthread_create(&g->thread, NULL, guard_main, g) != 0) {
        wl_event_queue_destroy(g->idle_queue);
        free(g);
        return NULL;
    }
    return g;
}

void wlg_stop(wl_guard *g) {
    if (g == NULL) return;
    atomic_store(&g->stop, 1);
    pthread_join(g->thread, NULL);
    wl_event_queue_destroy(g->idle_queue);
    free(g);
}
