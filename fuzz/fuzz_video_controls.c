#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "video_controls.h"

static double take(const uint8_t **p, size_t *n) {
    double d = 0.0;
    if (*n >= sizeof d) { memcpy(&d, *p, sizeof d); *p += sizeof d; *n -= sizeof d; }
    return d;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    const uint8_t *p = data;
    size_t n = size;
    double x = take(&p, &n), y = take(&p, &n), w = take(&p, &n), h = take(&p, &n);
    double px = take(&p, &n), py = take(&p, &n), t = take(&p, &n);
    int64_t a = 0, b = 0;
    if (n >= sizeof a) { memcpy(&a, p, sizeof a); p += sizeof a; n -= sizeof a; }
    if (n >= sizeof b) { memcpy(&b, p, sizeof b); p += sizeof b; n -= sizeof b; }

    vcl_geom g;
    vcl_rect v = { x, y, w, h };
    int has = vcl_layout(x, y, w, h, &g);
    double f = -1.0;
    vcl_hit_kind k = vcl_hit(has ? &g : NULL, &v, px, py, &f);
    if (k == VCL_HIT_SEEK && !(f >= 0.0 && f <= 1.0)) abort();
    if (k != VCL_HIT_SEEK && f != 0.0) abort();

    size_t cnt = n / sizeof(double);
    hls_segment *segs = calloc(cnt ? cnt : 1, sizeof *segs);
    if (segs == NULL) return 0;
    for (size_t i = 0; i < cnt; ++i) segs[i].duration = take(&p, &n);
    hls_playlist pl;
    memset(&pl, 0, sizeof pl);
    pl.segments = segs;
    pl.count = cnt;
    double total = vcl_total(&pl);
    if (!isfinite(total) || total < 0.0) abort();
    double start = -1.0;
    size_t idx = vcl_segment_at(&pl, t, &start);
    if (cnt > 0 && idx >= cnt) abort();
    if (!isfinite(start) || start < 0.0 || start > total + 1e-6 * (1.0 + total)) abort();
    double pos = vcl_position(t, a, b, total);
    if (!isfinite(pos) || pos < 0.0 || pos > total) abort();
    char buf[24];
    size_t len = vcl_format_time(t, buf, sizeof buf);
    if (len != strlen(buf)) abort();
    free(segs);
    return 0;
}
