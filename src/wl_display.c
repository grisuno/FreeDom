#define _POSIX_C_SOURCE 200809L
#include "wl_display.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define WD_PREFIX     "wayland-"
#define WD_PREFIX_LEN 8u
#define WD_MAX_NAMES  64u
#define WD_NAME_MAX   64u

static int wd_index(const char *name, unsigned long *idx) {
    if (strncmp(name, WD_PREFIX, WD_PREFIX_LEN) != 0) return 0;
    const char *d = name + WD_PREFIX_LEN;
    size_t len = strlen(d);
    if (len == 0 || len > 9) return 0;
    unsigned long v = 0;
    for (size_t i = 0; i < len; i++) {
        if (d[i] < '0' || d[i] > '9') return 0;
        v = v * 10 + (unsigned long)(d[i] - '0');
    }
    *idx = v;
    return 1;
}

int wd_pick(const char *const *names, size_t n, char *out, size_t cap) {
    const char *best = NULL;
    unsigned long best_idx = 0;
    for (size_t i = 0; i < n; i++) {
        unsigned long idx;
        if (names[i] == NULL || !wd_index(names[i], &idx)) continue;
        if (best == NULL || idx < best_idx) { best = names[i]; best_idx = idx; }
    }
    if (best == NULL) return WD_NONE;
    size_t len = strlen(best);
    if (len >= cap) return WD_NONE;
    memcpy(out, best, len + 1);
    return WD_OK;
}

int wd_resolve_env(void) {
    const char *cur = getenv("WAYLAND_DISPLAY");
    if (cur != NULL && cur[0] != '\0') return WD_OK;
    const char *dir = getenv("XDG_RUNTIME_DIR");
    if (dir == NULL || dir[0] == '\0') return WD_NONE;
    DIR *d = opendir(dir);
    if (d == NULL) return WD_NONE;
    static char store[WD_MAX_NAMES][WD_NAME_MAX];
    const char *names[WD_MAX_NAMES];
    size_t n = 0;
    struct dirent *e;
    while (n < WD_MAX_NAMES && (e = readdir(d)) != NULL) {
        size_t len = strlen(e->d_name);
        if (len >= WD_NAME_MAX) continue;
        memcpy(store[n], e->d_name, len + 1);
        names[n] = store[n];
        n++;
    }
    closedir(d);
    char pick[WD_NAME_MAX];
    if (wd_pick(names, n, pick, sizeof pick) != WD_OK) return WD_NONE;
    return setenv("WAYLAND_DISPLAY", pick, 1) == 0 ? WD_OK : WD_NONE;
}
