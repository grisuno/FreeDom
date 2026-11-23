/* smooth_scroll (sms_) -- spec/smooth_scroll.md. */
#include "smooth_scroll.h"

#include <math.h>
#include <stddef.h>

void sms_init(sms_state *s, double pos) {
    if (s == NULL) return;
    s->from = s->to = s->pos = isfinite(pos) ? pos : 0.0;
    s->t0_ms = 0.0;
    s->dur_ms = 0.0;
    s->active = 0;
}

void sms_jump(sms_state *s, double pos) {
    if (s == NULL || !isfinite(pos)) return;
    s->from = s->to = s->pos = pos;
    s->active = 0;
}

void sms_retarget(sms_state *s, double target, double now_ms, double dur_ms) {
    if (s == NULL || !isfinite(target) || !isfinite(now_ms)) return;
    /* A duration lost to rounding against now (now + dur == now) is no duration. */
    if (!isfinite(dur_ms) || !(now_ms + dur_ms > now_ms) || target == s->pos) {
        sms_jump(s, target);
        return;
    }
    s->from = s->pos;
    s->to = target;
    s->t0_ms = now_ms;
    s->dur_ms = dur_ms;
    s->active = 1;
}

double sms_sample(sms_state *s, double now_ms) {
    if (s == NULL) return 0.0;
    if (!s->active) return s->pos;
    double k = isfinite(now_ms) ? (now_ms - s->t0_ms) / s->dur_ms : 0.0;
    if (!(k > 0.0)) k = 0.0;
    if (k >= 1.0 || (isfinite(now_ms) && now_ms >= s->t0_ms + s->dur_ms)) {
        s->pos = s->to;
        s->active = 0;
        return s->pos;
    }
    double r = 1.0 - k;
    double e = 1.0 - r * r * r;
    /* from + d*e is monotone in e under rounding (each step rounds monotonically); a
     * weighted from*(1-e) + to*e is not. Ends near +-DBL_MAX overflow d: halve it then
     * (an infinite partial sum is clamped below). */
    double d = s->to - s->from;
    double p = isfinite(d) ? s->from + d * e
                           : s->from + 2.0 * ((s->to * 0.5 - s->from * 0.5) * e);
    double lo = s->from < s->to ? s->from : s->to;
    double hi = s->from < s->to ? s->to : s->from;
    s->pos = (p >= lo) ? (p > hi ? hi : p) : lo; /* NaN-safe clamp */
    return s->pos;
}

double sms_goal(const sms_state *s) {
    if (s == NULL) return 0.0;
    return s->active ? s->to : s->pos;
}

int sms_active(const sms_state *s) {
    return s != NULL && s->active;
}
