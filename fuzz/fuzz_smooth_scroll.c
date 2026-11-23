/* libFuzzer harness for smooth_scroll (spec/smooth_scroll.md): drives random sequences of
 * jump/retarget/sample with arbitrary doubles (NaN/inf included) and checks the contract's
 * properties after every step. */
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "smooth_scroll.h"

static double take(const uint8_t **d, size_t *n) {
    double v = 0.0;
    if (*n >= sizeof v) { memcpy(&v, *d, sizeof v); *d += sizeof v; *n -= sizeof v; }
    else { *n = 0; }
    return v;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    sms_state s;
    sms_init(&s, take(&data, &size));
    if (!isfinite(s.pos)) abort();
    double clock = 0.0, last = s.pos;
    int mono = 1; /* last was sampled on the forward clock */
    while (size > 0) {
        uint8_t op = data[0]; data++; size--;
        switch (op % 4) {
        case 0: {
            double p = take(&data, &size);
            sms_jump(&s, p);
            if (isfinite(p) && (s.pos != p || sms_active(&s))) abort();
            last = s.pos;
            if (isfinite(p)) mono = 1; /* an ignored jump keeps the old animation */
            break;
        }
        case 1: {
            double tgt = take(&data, &size), dur = take(&data, &size);
            double before = s.pos;
            sms_retarget(&s, tgt, clock, dur);
            if (isfinite(tgt) && sms_sample(&s, clock) != before && !(!sms_active(&s) && s.pos == tgt))
                abort(); /* continuity, or an immediate jump to a finite target */
            last = s.pos;
            if (isfinite(tgt)) mono = 1; /* an ignored retarget keeps the old clock */
            break;
        }
        case 2: {
            double dt = (double)(op >> 2) * 7.0; /* clock moves forward */
            int was = sms_active(&s);
            double from = s.from, to = s.to;
            clock += dt;
            double p = sms_sample(&s, clock);
            if (!isfinite(p)) abort();
            if (was) {
                double lo = from < to ? from : to, hi = from < to ? to : from;
                if (p < lo || p > hi) abort();
                if (mono && ((to >= from && p < last) || (to < from && p > last))) abort();
                if (clock >= s.t0_ms + s.dur_ms && (p != to || sms_active(&s))) abort();
            } else if (p != last) {
                abort();
            }
            last = p; mono = 1;
            break;
        }
        default: {
            double t = take(&data, &size); /* arbitrary clock, even backwards or NaN */
            double p = sms_sample(&s, t);
            if (!isfinite(p)) abort();
            last = p; mono = 0;
            break;
        }
        }
        if (!isfinite(sms_goal(&s))) abort();
    }
    return 0;
}
