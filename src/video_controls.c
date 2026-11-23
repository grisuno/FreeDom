#include "video_controls.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

static int finite4(double a, double b, double c, double d) {
    return isfinite(a) && isfinite(b) && isfinite(c) && isfinite(d);
}

static int in_rect(const vcl_rect *r, double px, double py) {
    return px >= r->x && px <= r->x + r->w && py >= r->y && py <= r->y + r->h;
}

int vcl_layout(double x, double y, double w, double h, vcl_geom *g) {
    if (g == NULL) return 0;
    memset(g, 0, sizeof *g);
    if (!finite4(x, y, w, h) || w < VCL_MIN_W || h < VCL_MIN_H) return 0;
    g->bar = (vcl_rect){ x, y + h - VCL_BAR_H, w, VCL_BAR_H };
    double btn = VCL_BAR_H - 2.0 * (VCL_PAD / 2.0);
    g->play = (vcl_rect){ x + VCL_PAD / 2.0, g->bar.y + VCL_PAD / 2.0, btn, btn };
    double tx = g->play.x + g->play.w + VCL_PAD;
    double text_w = (w >= VCL_MIN_W + VCL_TEXT_W) ? VCL_TEXT_W : 0.0;
    double tw = (x + w - VCL_PAD - text_w) - tx;
    if (text_w > 0.0) tw -= VCL_PAD;
    if (tw < 1.0) tw = 1.0;
    g->track = (vcl_rect){ tx, g->bar.y + (VCL_BAR_H - VCL_TRACK_H) / 2.0, tw, VCL_TRACK_H };
    g->hit_track = (vcl_rect){ tx, g->bar.y, tw, VCL_BAR_H };
    g->text_x = x + w - VCL_PAD - text_w;
    g->text_y = g->bar.y + VCL_BAR_H / 2.0 + 4.0;
    return 1;
}

double vcl_clamp_frac(double f) {
    if (!(f > 0.0)) return 0.0; /* NaN and negatives */
    return (f > 1.0) ? 1.0 : f;
}

vcl_hit_kind vcl_hit(const vcl_geom *g, const vcl_rect *video, double px, double py,
                     double *frac) {
    if (frac != NULL) *frac = 0.0;
    if (video == NULL || !isfinite(px) || !isfinite(py) || !in_rect(video, px, py))
        return VCL_HIT_NONE;
    if (g == NULL || g->bar.w <= 0.0 || !in_rect(&g->bar, px, py)) return VCL_HIT_TOGGLE;
    if (in_rect(&g->play, px, py)) return VCL_HIT_TOGGLE;
    if (in_rect(&g->hit_track, px, py)) {
        if (frac != NULL)
            *frac = vcl_clamp_frac(g->track.w > 0.0 ? (px - g->track.x) / g->track.w : 0.0);
        return VCL_HIT_SEEK;
    }
    return VCL_HIT_BAR;
}

double vcl_seg_duration(double d) {
    if (!(d > 0.0)) return 0.0; /* NaN, zero, negative */
    return (d > VCL_MAX_SEGMENT_S) ? VCL_MAX_SEGMENT_S : d; /* also +inf */
}

double vcl_total(const hls_playlist *pl) {
    double t = 0.0;
    if (pl == NULL || pl->segments == NULL) return 0.0;
    for (size_t i = 0; i < pl->count; ++i) t += vcl_seg_duration(pl->segments[i].duration);
    return isfinite(t) ? t : 0.0;
}

size_t vcl_segment_at(const hls_playlist *pl, double t, double *start) {
    if (start != NULL) *start = 0.0;
    if (pl == NULL || pl->segments == NULL || pl->count == 0) return 0;
    if (!(t > 0.0)) return 0;
    double acc = 0.0;
    for (size_t i = 0; i < pl->count; ++i) {
        double d = vcl_seg_duration(pl->segments[i].duration);
        if (t < acc + d || i + 1 == pl->count) {
            if (start != NULL) *start = acc;
            return i;
        }
        acc += d;
    }
    return 0; /* unreachable: the last iteration returns */
}

double vcl_segment_start(const hls_playlist *pl, size_t idx) {
    if (pl == NULL || pl->segments == NULL || pl->count == 0) return 0.0;
    if (idx >= pl->count) idx = pl->count - 1;
    double acc = 0.0;
    for (size_t i = 0; i < idx; ++i) acc += vcl_seg_duration(pl->segments[i].duration);
    return acc;
}

double vcl_position(double base_s, int64_t pts0_us, int64_t pts_us, double total) {
    if (!isfinite(total) || total < 0.0) total = 0.0;
    if (!isfinite(base_s) || base_s < 0.0) base_s = 0.0;
    double p = base_s;
    if (pts_us > pts0_us) p += ((double)pts_us - (double)pts0_us) / 1e6;
    if (!isfinite(p) || p > total) p = total;
    return p;
}

size_t vcl_format_time(double seconds, char *buf, size_t cap) {
    if (buf == NULL || cap == 0) return 0;
    buf[0] = '\0';
    if (!(seconds > 0.0)) seconds = 0.0;
    if (seconds > 359999.0) seconds = 359999.0; /* 99:59:59 */
    unsigned long s = (unsigned long)seconds;
    unsigned long h = s / 3600u, m = (s / 60u) % 60u, r = s % 60u;
    int n = (h > 0) ? snprintf(buf, cap, "%lu:%02lu:%02lu", h, m, r)
                    : snprintf(buf, cap, "%lu:%02lu", m, r);
    if (n < 0 || (size_t)n >= cap) {
        buf[0] = '\0';
        return 0;
    }
    return (size_t)n;
}
