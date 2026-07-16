#ifndef FREEDOM_FRAME_CLOCK_H
#define FREEDOM_FRAME_CLOCK_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * frame_clock (fc_) — pure animation frame scheduler. Phase R1a.
 * Tracks whether a steady repaint clock should be active. The actual
 * timerfd lives in the trusted-side GUI. No I/O, no allocation.
 * See spec/frame_clock.md.
 */

typedef struct fc_clock {
    int active;
    int interval_ms;
} fc_clock;

void fc_init(fc_clock *c);
void fc_set_active(fc_clock *c, int active);
int  fc_needs_tick(const fc_clock *c);
int  fc_interval_ms(const fc_clock *c);

#endif /* FREEDOM_FRAME_CLOCK_H */
