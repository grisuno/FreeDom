/*
 * wl_display — pick the Wayland socket to connect to when WAYLAND_DISPLAY is unset.
 * wd_pick is pure (no I/O); wd_resolve_env scans $XDG_RUNTIME_DIR and sets the variable.
 */
#ifndef FREEDOM_WL_DISPLAY_H
#define FREEDOM_WL_DISPLAY_H

#include <stddef.h>

#define WD_OK    0
#define WD_NONE (-1)

/* Choose the lowest-numbered "wayland-N" (N = digits only) from names[0..n).
 * Writes it NUL-terminated into out; returns WD_NONE (out untouched) if none
 * qualifies or cap is too small. */
int wd_pick(const char *const *names, size_t n, char *out, size_t cap);

/* If WAYLAND_DISPLAY is unset/empty, set it from the sockets found in XDG_RUNTIME_DIR.
 * Returns WD_OK if the variable is set on return, WD_NONE otherwise. */
int wd_resolve_env(void);

#endif
