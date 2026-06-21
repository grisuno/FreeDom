/*
 * zoom — pure page-zoom arithmetic. See include/zoom.h and spec/zoom.md.
 */

#include "zoom.h"

/* Common browser zoom stops. Must be sorted ascending and lie within
 * [ZM_MIN_PCT, ZM_MAX_PCT] (the ends are members so stepping terminates). */
static const int ZM_LADDER[] = {
    50, 67, 75, 90, 100, 110, 125, 150, 175, 200, 250, 300
};
#define ZM_LADDER_N ((int)(sizeof ZM_LADDER / sizeof ZM_LADDER[0]))

int zm_clamp(int pct) {
    if (pct < ZM_MIN_PCT) return ZM_MIN_PCT;
    if (pct > ZM_MAX_PCT) return ZM_MAX_PCT;
    return pct;
}

int zm_zoom_in(int pct) {
    int p = zm_clamp(pct);
    for (int i = 0; i < ZM_LADDER_N; ++i) {
        if (ZM_LADDER[i] > p) return ZM_LADDER[i];
    }
    return ZM_MAX_PCT;
}

int zm_zoom_out(int pct) {
    int p = zm_clamp(pct);
    for (int i = ZM_LADDER_N - 1; i >= 0; --i) {
        if (ZM_LADDER[i] < p) return ZM_LADDER[i];
    }
    return ZM_MIN_PCT;
}

int zm_reset(void) {
    return ZM_DEFAULT_PCT;
}

double zm_scale(int pct) {
    return (double)zm_clamp(pct) / 100.0;
}

double zm_apply(double base_px, int pct) {
    double scaled = base_px * zm_scale(pct);
    if (base_px > 0.0 && scaled < 1.0) return 1.0;
    return scaled;
}
