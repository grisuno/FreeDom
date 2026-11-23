/*
 * scroll_req — a page script's scroll request and where it lands (spec/scroll_req.md).
 * Pure: no I/O, no global state.
 */
#include "scroll_req.h"

#include <math.h>
#include <string.h>

static int32_t clamp_coord(double v) {
    if (isnan(v)) return 0;
    if (v >= (double)SRQ_MAX_COORD) return SRQ_MAX_COORD;
    if (v <= -(double)SRQ_MAX_COORD) return -SRQ_MAX_COORD;
    return (int32_t)round(v);
}

static int32_t clamp_count(size_t n) {
    return (n > (size_t)INT32_MAX) ? INT32_MAX : (int32_t)n;
}

void srq_encode(const srq_req *r, int32_t out[SRQ_WIRE_N]) {
    if (r == NULL || out == NULL) return;
    out[0] = (int32_t)r->kind;
    out[1] = (int32_t)r->behavior;
    out[2] = (int32_t)r->block;
    out[3] = clamp_coord(r->y);
    out[4] = clamp_coord(r->margin_top);
    out[5] = clamp_coord(r->margin_bottom);
    out[6] = clamp_count(r->n);
    out[7] = clamp_count(r->nsub);
}

static int coord_ok(int32_t v) {
    return v >= -SRQ_MAX_COORD && v <= SRQ_MAX_COORD;
}

int srq_decode(const int32_t in[SRQ_WIRE_N], size_t max_handles, srq_req *out) {
    if (out != NULL) memset(out, 0, sizeof *out);
    if (in == NULL || out == NULL) return -1;
    int32_t kind = in[0], beh = in[1], blk = in[2], n = in[6], nsub = in[7];
    if (kind < SRQ_NONE || kind > SRQ_ELEMENT) return -1;
    if (beh < SRQ_AUTO || beh > SRQ_SMOOTH) return -1;
    if (blk < SRQ_START || blk > SRQ_NEAREST) return -1;
    if (!coord_ok(in[3]) || !coord_ok(in[4]) || !coord_ok(in[5])) return -1;
    if (n < 0 || nsub < 0 || nsub > n || (size_t)n > max_handles) return -1;
    if ((kind == SRQ_ELEMENT) != (n > 0)) return -1;
    out->kind = (int)kind;
    out->behavior = (int)beh;
    out->block = (int)blk;
    out->y = (double)in[3];
    out->margin_top = (double)in[4];
    out->margin_bottom = (double)in[5];
    out->n = (size_t)n;
    out->nsub = (size_t)nsub;
    return 0;
}

/* The element's scroll for one block alignment inside the optimal viewing region
 * [scroll + pt, scroll + h - pb] (CSSOM View 4.3 "determine the scroll-into-view position"). */
static double element_scroll(int block, double cur, double h, double pt, double pb,
                             double top, double bottom) {
    double region = h - pt - pb;
    double start = top - pt;
    double end = bottom + pb - h;
    switch (block) {
        case SRQ_END:    return end;
        case SRQ_CENTER: return (top + bottom) / 2.0 - (pt + region / 2.0);
        case SRQ_NEAREST: {
            double rtop = cur + pt, rbot = cur + h - pb;
            int above = top < rtop, below = bottom > rbot;
            double size = bottom - top;
            if ((above && below) || (!above && !below)) return cur;
            if ((above && size <= region) || (below && size > region)) return start;
            return end;
        }
        default:         return start;
    }
}

int srq_target(const srq_req *r, const srq_view *v, double el_top, double el_bottom,
               double *out) {
    if (r == NULL || v == NULL || out == NULL) return -1;
    if (r->kind <= SRQ_NONE || r->kind > SRQ_ELEMENT) return -1;
    if (!isfinite(v->scroll) || !isfinite(v->max_scroll) || !isfinite(v->view_h)
     || !isfinite(v->pad_top) || !isfinite(v->pad_bottom) || !isfinite(r->y)
     || !isfinite(r->margin_top) || !isfinite(r->margin_bottom)) return -1;
    if (v->view_h <= 0.0 || v->max_scroll < 0.0) return -1;
    double t;
    if (r->kind == SRQ_TO) {
        t = r->y;
    } else if (r->kind == SRQ_BY) {
        t = v->scroll + r->y;
    } else {
        if (!isfinite(el_top) || !isfinite(el_bottom)) return -1;
        double pt = (v->pad_top > 0.0) ? v->pad_top : 0.0;
        double pb = (v->pad_bottom > 0.0) ? v->pad_bottom : 0.0;
        if (pt + pb >= v->view_h) { pt = 0.0; pb = 0.0; }   /* no room left: ignored */
        double top = el_top - r->margin_top;
        double bottom = el_bottom + r->margin_bottom;
        if (bottom < top) bottom = top;
        t = element_scroll(r->block, v->scroll, v->view_h, pt, pb, top, bottom);
    }
    if (!isfinite(t)) return -1;
    if (t > v->max_scroll) t = v->max_scroll;
    if (t < 0.0) t = 0.0;
    *out = t;
    return 0;
}

int srq_smooth(const srq_req *r, int root_smooth) {
    if (r == NULL) return 0;
    if (r->behavior == SRQ_SMOOTH) return 1;
    return (r->behavior == SRQ_AUTO && root_smooth) ? 1 : 0;
}
