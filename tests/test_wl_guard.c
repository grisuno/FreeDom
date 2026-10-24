#define _DEFAULT_SOURCE
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <cmocka.h>
#include <wayland-client.h>

#include "wl_guard.h"

static long ms_since(const struct timespec *a) {
    struct timespec b;
    clock_gettime(CLOCK_MONOTONIC, &b);
    return (b.tv_sec - a->tv_sec) * 1000 + (b.tv_nsec - a->tv_nsec) / 1000000;
}

/* The helper starts on a live display, tolerates an idle socket, and stops promptly (it polls in
 * 100 ms slices): a hung join would hang the GUI's shutdown. NULL is a no-op everywhere. */
static void test_guard_starts_idles_and_stops_promptly(void **state) {
    (void)state;
    int sv[2];
    assert_int_equal(socketpair(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0, sv), 0);
    struct wl_display *d = wl_display_connect_to_fd(sv[0]);
    assert_non_null(d);
    wl_guard *g = wlg_start(d);
    assert_non_null(g);
    usleep(250 * 1000);                           /* several idle polls */
    struct timespec t0;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    wlg_stop(g);
    assert_true(ms_since(&t0) < 1000);
    wl_display_disconnect(d);                     /* closes sv[0] */
    close(sv[1]);
    wlg_stop(NULL);
    assert_null(wlg_start(NULL));
}

/* A peer that disappears (compositor gone) ends the helper by itself instead of spinning. */
static void test_guard_survives_peer_hangup(void **state) {
    (void)state;
    int sv[2];
    assert_int_equal(socketpair(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0, sv), 0);
    struct wl_display *d = wl_display_connect_to_fd(sv[0]);
    assert_non_null(d);
    wl_guard *g = wlg_start(d);
    assert_non_null(g);
    close(sv[1]);                                 /* hang up */
    usleep(300 * 1000);
    wlg_stop(g);
    wl_display_disconnect(d);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_guard_starts_idles_and_stops_promptly),
        cmocka_unit_test(test_guard_survives_peer_hangup),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
