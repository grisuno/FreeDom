/*
 * frame_clock (fc_) — pure animation frame scheduler. Phase R1a.
 * See spec/frame_clock.md.
 */

#include "frame_clock.h"

#define FC_DEFAULT_INTERVAL_MS 16

void fc_init(fc_clock *c) {
    if (!c) return;
    c->active = 0;
    c->interval_ms = FC_DEFAULT_INTERVAL_MS;
}

void fc_set_active(fc_clock *c, int active) {
    if (!c) return;
    c->active = active ? 1 : 0;
}

int fc_needs_tick(const fc_clock *c) {
    if (!c) return 0;
    return c->active;
}

int fc_interval_ms(const fc_clock *c) {
    if (!c) return 0;
    return c->interval_ms;
}
