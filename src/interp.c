/*
 * interp (ip_) — pure CSS interpolation engine. Phase R1d.
 * See spec/interp.md.
 */

#include "interp.h"
#include <math.h>
#include <float.h>

/* ---- helpers ------------------------------------------------------ */

static double clamp01(double t) {
    if (t < 0.0) return 0.0;
    if (t > 1.0) return 1.0;
    return t;
}

static double sample_bezier_x(double t, double cx1, double cx2) {
    double u = 1.0 - t;
    return 3.0 * u * u * t * cx1 + 3.0 * u * t * t * cx2 + t * t * t;
}

static double sample_bezier_dx(double t, double cx1, double cx2) {
    return 3.0 * cx1 * (1.0 - 4.0 * t + 3.0 * t * t) +
           3.0 * cx2 * (2.0 * t - 3.0 * t * t) +
           3.0 * t * t;
}

static double sample_bezier_y(double t, double cy1, double cy2) {
    double u = 1.0 - t;
    return 3.0 * u * u * t * cy1 + 3.0 * u * t * t * cy2 + t * t * t;
}

/* Newton-Raphson to find t where Bx(t) = x. */
static double solve_bezier_t(double x, double cx1, double cx2) {
    x = clamp01(x);
    if (x <= 0.0) return 0.0;
    if (x >= 1.0) return 1.0;

    double t = x;
    for (int i = 0; i < 8; ++i) {
        double bx = sample_bezier_x(t, cx1, cx2);
        double dx = sample_bezier_dx(t, cx1, cx2);
        if (fabs(dx) < 1e-12) break;
        t = t - (bx - x) / dx;
        if (t < 0.0) t = 0.0;
        if (t > 1.0) t = 1.0;
        if (fabs(bx - x) < 1e-7) break;
    }
    return t;
}

/* ---- ip_ease ------------------------------------------------------ */

double ip_ease(double t, const ip_ease_fn *fn) {
    t = clamp01(t);
    if (!fn) return t;

    switch (fn->kind) {
    case IP_EASE_LINEAR:
        return t;

    case IP_EASE_EASE:
        return ip_ease(t, &(ip_ease_fn){
            .kind = IP_EASE_CUBIC_BEZIER,
            .cx1 = 0.25, .cy1 = 0.1, .cx2 = 0.25, .cy2 = 1.0
        });

    case IP_EASE_EASE_IN:
        return ip_ease(t, &(ip_ease_fn){
            .kind = IP_EASE_CUBIC_BEZIER,
            .cx1 = 0.42, .cy1 = 0.0, .cx2 = 1.0, .cy2 = 1.0
        });

    case IP_EASE_EASE_OUT:
        return ip_ease(t, &(ip_ease_fn){
            .kind = IP_EASE_CUBIC_BEZIER,
            .cx1 = 0.0, .cy1 = 0.0, .cx2 = 0.58, .cy2 = 1.0
        });

    case IP_EASE_EASE_IN_OUT:
        return ip_ease(t, &(ip_ease_fn){
            .kind = IP_EASE_CUBIC_BEZIER,
            .cx1 = 0.42, .cy1 = 0.0, .cx2 = 0.58, .cy2 = 1.0
        });

    case IP_EASE_STEP_START: {
        int n = fn->steps_n > 0 ? fn->steps_n : 1;
        int s = (int)(t * (double)n);
        if (s < n) s = s + 1;
        else s = n;
        return (double)s / (double)n;
    }

    case IP_EASE_STEP_END: {
        int n = fn->steps_n > 0 ? fn->steps_n : 1;
        int s = (int)(t * (double)n);
        if (s > n) s = n;
        return (double)s / (double)n;
    }

    case IP_EASE_STEPS: {
        int n = fn->steps_n > 0 ? fn->steps_n : 1;
        if (fn->steps_dir == 1) {
            /* jump-start */
            int s = (int)(t * (double)n);
            if (s < n) s = s + 1;
            else s = n;
            return (double)s / (double)n;
        } else {
            /* jump-end */
            int s = (int)(t * (double)n);
            if (s > n) s = n;
            return (double)s / (double)n;
        }
    }

    case IP_EASE_CUBIC_BEZIER: {
        double cx1 = clamp01(fn->cx1);
        double cy1 = clamp01(fn->cy1);
        double cx2 = clamp01(fn->cx2);
        double cy2 = clamp01(fn->cy2);
        double bt = solve_bezier_t(t, cx1, cx2);
        return sample_bezier_y(bt, cy1, cy2);
    }

    default:
        return t;
    }
}

/* ---- ip_lerp / ip_lerp_color ------------------------------------- */

double ip_lerp(double a, double b, double t) {
    t = clamp01(t);
    return a + (b - a) * t;
}

uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t) {
    t = clamp01(t);
    int r1 = (int)((c1 >> 16) & 0xff);
    int g1 = (int)((c1 >> 8)  & 0xff);
    int b1 = (int)(c1         & 0xff);
    int r2 = (int)((c2 >> 16) & 0xff);
    int g2 = (int)((c2 >> 8)  & 0xff);
    int b2 = (int)(c2         & 0xff);

    int r = (int)(r1 + (r2 - r1) * t + 0.5);
    int g = (int)(g1 + (g2 - g1) * t + 0.5);
    int b = (int)(b1 + (b2 - b1) * t + 0.5);

    if (r < 0) r = 0;
    if (r > 255) r = 255;
    if (g < 0) g = 0;
    if (g > 255) g = 255;
    if (b < 0) b = 0;
    if (b > 255) b = 255;

    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}

double ip_interp(ip_val_kind kind, double a, double b, double t) {
    switch (kind) {
    case IP_VAL_SCALAR:
        return ip_lerp(a, b, t);
    case IP_VAL_COLOR:
        return (double)ip_lerp_color((uint32_t)a, (uint32_t)b, t);
    default:
        return 0.0;
    }
}

/* ---- ip_kf_interp ------------------------------------------------- */

double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf,
                    int n_kf, double pct) {
    if (!kf || n_kf <= 0) return 0.0;
    if (n_kf == 1) return kf[0].val;

    if (pct <= kf[0].pct) return kf[0].val;
    if (pct >= kf[n_kf - 1].pct) return kf[n_kf - 1].val;

    for (int i = 0; i < n_kf - 1; ++i) {
        if (pct >= kf[i].pct && pct <= kf[i + 1].pct) {
            double span = kf[i + 1].pct - kf[i].pct;
            if (span <= 0.0) return kf[i].val;
            double local_t = (pct - kf[i].pct) / span;
            return ip_interp(val_kind, kf[i].val, kf[i + 1].val, local_t);
        }
    }
    return kf[n_kf - 1].val;
}

/* ---- ip_anim ------------------------------------------------------ */

void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease,
                  const ip_keyframe *kf, int n_kf,
                  double duration_ms, double delay_ms,
                  int iteration_count, int direction, int fill_mode) {
    if (!a) return;
    a->val_kind = vk;
    if (ease) a->ease = *ease;
    else {
        a->ease.kind = IP_EASE_LINEAR;
        a->ease.steps_n = 1;
        a->ease.steps_dir = 0;
        a->ease.cx1 = a->ease.cy1 = a->ease.cx2 = a->ease.cy2 = 0.0;
    }
    a->keyframes = kf;
    a->n_keyframes = n_kf;
    a->duration_ms = duration_ms > 0.0 ? duration_ms : 1.0;
    a->delay_ms = delay_ms >= 0.0 ? delay_ms : 0.0;
    a->iteration_count = iteration_count;
    a->direction = direction;
    a->fill_mode = fill_mode;
    a->elapsed_ms = 0.0;
    a->current_iteration = 0;
    a->done = 0;
    a->end_value = 0.0;
}

static int anim_effective_dir_for(const ip_anim *a, int iter) {
    switch (a->direction) {
    case IP_DIR_NORMAL:            return 0; /* normal */
    case IP_DIR_REVERSE:           return 1; /* reverse */
    case IP_DIR_ALTERNATE:         return (iter % 2);
    case IP_DIR_ALTERNATE_REVERSE:  return (iter % 2) ? 0 : 1;
    default:                       return 0;
    }
}

static int anim_effective_dir(const ip_anim *a) {
    return anim_effective_dir_for(a, a->current_iteration);
}

int ip_anim_tick(ip_anim *a, double dt_ms) {
    if (!a) return 0;
    if (dt_ms <= 0.0) return 0;
    if (a->done) return 0;
    if (a->n_keyframes <= 0) { a->done = 1; return 0; }

    double old_elapsed = a->elapsed_ms;
    a->elapsed_ms += dt_ms;

    /* Still in delay? */
    if (a->elapsed_ms < a->delay_ms) {
        if (a->fill_mode == IP_FILL_BACKWARDS || a->fill_mode == IP_FILL_BOTH)
            return 1; /* value = first kf; changed from init */
        return (old_elapsed < a->delay_ms) ? 0 : 0; /* no change */
    }

    /* Transition from delay to active: always a change. */
    double active = a->elapsed_ms - a->delay_ms;
    double old_active = old_elapsed - a->delay_ms;
    if (old_active < 0.0) old_active = 0.0;

    int old_iter = a->current_iteration;

    if (a->iteration_count != IP_ITERATION_INFINITE) {
        double total = a->duration_ms * (double)a->iteration_count;
        if (active >= total) {
            a->current_iteration = a->iteration_count;
            int last_dir = (a->direction == IP_DIR_REVERSE ||
                            a->direction == IP_DIR_ALTERNATE_REVERSE) ? 1 : 0;
            if (a->direction == IP_DIR_ALTERNATE)
                last_dir = (a->iteration_count - 1) % 2;
            else if (a->direction == IP_DIR_ALTERNATE_REVERSE)
                last_dir = ((a->iteration_count - 1) % 2) ? 0 : 1;
            double end_eased = last_dir ? 0.0 : 1.0;
            a->end_value = ip_kf_interp(a->val_kind, a->keyframes,
                                        a->n_keyframes, end_eased * 100.0);
            a->done = 1;
            return 1;
        }
    }

    a->current_iteration = (int)(active / a->duration_ms);
    return (a->current_iteration != old_iter || old_active < 0.0) ? 1 : 1;
    /* Always return 1 during active phase: the value changes continuously. */
}

double ip_anim_current(const ip_anim *a) {
    if (!a) return 0.0;
    if (a->n_keyframes <= 0) return 0.0;

    /* After completion, return the stored end value (caller uses done()
     * to decide whether to stop painting; fill=none → done()=1). */
    if (a->done) return a->end_value;

    /* Delay phase */
    if (a->elapsed_ms < a->delay_ms) {
        if (a->fill_mode == IP_FILL_BACKWARDS || a->fill_mode == IP_FILL_BOTH)
            return a->keyframes[0].val;
        return 0.0;
    }

    /* Active phase */
    double active = a->elapsed_ms - a->delay_ms;
    double iter_time = fmod(active, a->duration_ms);

    /* Boundary: at exactly the end of an iteration (iter_time ≈ 0,
     * but we're past the first iteration), use end-of-previous-iter. */
    int iter = (int)(active / a->duration_ms);
    if (iter_time < 0.001 && iter > 0) {
        int prev_dir = anim_effective_dir_for(a, iter - 1);
        double prev_eased = prev_dir ? 0.0 : 1.0;
        return ip_kf_interp(a->val_kind, a->keyframes,
                            a->n_keyframes, prev_eased * 100.0);
    }

    double local_t = iter_time / a->duration_ms;
    double eased = ip_ease(local_t, &a->ease);

    int dir = anim_effective_dir(a);
    if (dir) eased = 1.0 - eased;

    return ip_kf_interp(a->val_kind, a->keyframes, a->n_keyframes, eased * 100.0);
}

int ip_anim_done(const ip_anim *a) {
    if (!a) return 1;
    if (a->n_keyframes <= 0) return 1;
    if (!a->done) return 0;
    if (a->fill_mode == IP_FILL_FORWARDS || a->fill_mode == IP_FILL_BOTH)
        return 0;
    return 1;
}
