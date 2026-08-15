/* block_flow (bf_) -- vertical margin collapsing. See spec/block_flow.md. */

#include "block_flow.h"

#include <math.h>

/* A margin the caller could not compute (NaN from a hostile calc(), an infinity
 * from an overflowing unit conversion) contributes NOTHING rather than poisoning
 * every coordinate below it. Every entry point funnels its inputs through here,
 * so there is exactly one place that decides what "absent" means. */
static double finite_or_zero(double v) {
    return isfinite(v) ? v : 0.0;
}

double bf_collapse_n(const double *m, size_t n) {
    if (m == NULL || n == 0) return 0.0;
    /* CSS 2.1 8.3.1: the used margin is the largest POSITIVE adjoining margin
     * with the largest-in-magnitude NEGATIVE one deducted from it. Tracking the
     * two extremes separately is what makes the rule associative, so the n-ary
     * form and repeated binary calls cannot disagree. */
    double pos = 0.0, neg = 0.0;
    for (size_t i = 0; i < n; ++i) {
        double v = finite_or_zero(m[i]);
        if (v > pos) pos = v;
        else if (v < neg) neg = v;
    }
    return pos + neg;
}

double bf_collapse(double a, double b) {
    const double pair[2] = { a, b };
    return bf_collapse_n(pair, 2);
}

int bf_margins_adjoin(double border_px, double padding_px) {
    /* Fail closed: a non-finite edge is treated as PRESENT, so the margins do not
     * collapse. Over-collapsing deletes space the author asked for and fuses two
     * blocks; under-collapsing merely leaves a gap. */
    if (!isfinite(border_px) || !isfinite(padding_px)) return 0;
    return (border_px == 0.0 && padding_px == 0.0) ? 1 : 0;
}
