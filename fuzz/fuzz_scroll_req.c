/* fuzz_scroll_req -- spec/scroll_req.md: a hostile wire record either decodes to an
 * in-range request or is refused, and srq_target over arbitrary doubles is always
 * finite and inside [0, max_scroll]. */
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "scroll_req.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    int32_t w[SRQ_WIRE_N];
    double d[7];
    if (size < sizeof w + sizeof d) return 0;
    memcpy(w, data, sizeof w);
    memcpy(d, data + sizeof w, sizeof d);
    srq_req r;
    if (srq_decode(w, 4096, &r) == 0) {
        if (r.kind < SRQ_NONE || r.kind > SRQ_ELEMENT || r.n > 4096 || r.nsub > r.n
            || fabs(r.y) > SRQ_MAX_COORD) abort();
        int32_t back[SRQ_WIRE_N];
        srq_encode(&r, back);
        if (memcmp(back, w, sizeof w) != 0) abort();       /* decode is exact */
    } else if (r.kind != SRQ_NONE) {
        abort();
    }
    /* srq_target on raw doubles (the request side too, not only decoded ones). */
    srq_req q = r;
    q.kind = 1 + (int)(data[0] % 3u);
    q.block = (int)(data[1] % 4u);
    q.y = d[0];
    q.margin_top = d[1];
    srq_view v = { d[2], d[3], d[4], d[5], d[6] };
    double out = -12345.0;
    if (srq_target(&q, &v, d[0] * 0.5, d[1] + d[2], &out) == 0) {
        if (!isfinite(out) || out < 0.0 || out > v.max_scroll) abort();
    } else if (out != -12345.0) {
        abort();
    }
    (void)srq_smooth(&q, data[2] & 1);
    return 0;
}
