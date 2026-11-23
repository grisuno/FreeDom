#ifndef FREEDOM_SMOOTH_SCROLL_H
#define FREEDOM_SMOOTH_SCROLL_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * smooth_scroll (sms_) -- pure arithmetic of the page's animated scroll: a cubic ease-out
 * from the current position to a target, re-aimable mid-flight. No I/O, no clock of its
 * own (the caller passes milliseconds). Contract: spec/smooth_scroll.md.
 *
 * Guarantees: pos is always finite and between from and to (never overshoots), monotone
 * within one animation, continuous across a retarget, and exactly `to` once finished.
 * Non-finite inputs leave the state unchanged; NULL is a no-op.
 */

typedef struct sms_state {
    double from;   /* position where the current animation started */
    double to;     /* its target */
    double pos;    /* last sampled position */
    double t0_ms;  /* start time */
    double dur_ms; /* duration */
    int    active; /* 1 while animating */
} sms_state;

void   sms_init(sms_state *s, double pos);
void   sms_jump(sms_state *s, double pos);
void   sms_retarget(sms_state *s, double target, double now_ms, double dur_ms);
double sms_sample(sms_state *s, double now_ms);
double sms_goal(const sms_state *s);
int    sms_active(const sms_state *s);

#endif
