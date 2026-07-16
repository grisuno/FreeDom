#ifndef FREEDOM_INTERP_H
#define FREEDOM_INTERP_H

#include <stdint.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * interp (ip_) — pure CSS interpolation engine. Phase R1d of the modern-
 * rendering plan: easing functions, value interpolation, keyframe
 * interpolation, and the animation state machine that tracks elapsed
 * time across iterations, delays, directions and fill modes.
 *
 * No I/O, no Cairo, no allocation. Pure math over validated scalars.
 * The trusted-side frame clock and GUI paint orchestration consume
 * this module. See spec/interp.md.
 */

/* ------------------------------------------------------------------ */
/*  Easing functions                                                   */
/* ------------------------------------------------------------------ */

typedef enum ip_easing {
    IP_EASE_LINEAR = 0,
    IP_EASE_EASE,
    IP_EASE_EASE_IN,
    IP_EASE_EASE_OUT,
    IP_EASE_EASE_IN_OUT,
    IP_EASE_STEP_START,
    IP_EASE_STEP_END,
    IP_EASE_STEPS,
    IP_EASE_CUBIC_BEZIER,
    IP_EASE_COUNT
} ip_easing;

typedef struct ip_ease_fn {
    ip_easing kind;
    int steps_n;
    int steps_dir;    /* 0 = end, 1 = start */
    double cx1, cy1;  /* cubic-bezier control points */
    double cx2, cy2;
} ip_ease_fn;

/* Compute eased t for normalized t ∈ [0,1]. Returns value ∈ [0,1].
 * Clamped: t < 0 → 0, t > 1 → 1. NULL-safe: returns t. */
double ip_ease(double t, const ip_ease_fn *fn);

/* ------------------------------------------------------------------ */
/*  Value interpolation                                                */
/* ------------------------------------------------------------------ */

typedef enum ip_val_kind {
    IP_VAL_SCALAR = 0,
    IP_VAL_COLOR,
    IP_VAL_COUNT
} ip_val_kind;

double   ip_lerp(double a, double b, double t);
uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t);
double   ip_interp(ip_val_kind kind, double a, double b, double t);

/* ------------------------------------------------------------------ */
/*  Keyframe interpolation                                             */
/* ------------------------------------------------------------------ */

#define IP_MAX_KEYFRAMES 16

typedef struct ip_keyframe {
    double pct;   /* 0.0 .. 100.0, sorted ascending */
    double val;   /* scalar or packed 0xRRGGBB color */
} ip_keyframe;

/* Interpolate between the two keyframes bracketing `pct` (0..100).
 * Exact match → that keyframe's value. Before first / after last →
 * clamped to first / last. NULL/empty → 0. */
double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf,
                    int n_kf, double pct);

/* ------------------------------------------------------------------ */
/*  Animation state machine                                            */
/* ------------------------------------------------------------------ */

#define IP_ITERATION_INFINITE (-1)

typedef enum ip_direction {
    IP_DIR_NORMAL = 0,
    IP_DIR_REVERSE,
    IP_DIR_ALTERNATE,
    IP_DIR_ALTERNATE_REVERSE,
} ip_direction;

typedef enum ip_fill_mode {
    IP_FILL_NONE = 0,
    IP_FILL_FORWARDS,
    IP_FILL_BACKWARDS,
    IP_FILL_BOTH,
} ip_fill_mode;

typedef struct ip_anim {
    ip_val_kind val_kind;
    ip_ease_fn ease;
    const ip_keyframe *keyframes;
    int n_keyframes;

    double duration_ms;
    double delay_ms;
    int iteration_count;
    int direction;
    int fill_mode;

    /* Runtime state */
    double elapsed_ms;
    int current_iteration;
    int done;
    double end_value;       /* snapshot at completion time */
} ip_anim;

/* Initialize. kf must outlive the animation. NULL-safe on a. */
void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease,
                  const ip_keyframe *kf, int n_kf,
                  double duration_ms, double delay_ms,
                  int iteration_count, int direction, int fill_mode);

/* Advance time by dt_ms. Returns 1 if the value changed, 0 if
 * unchanged. Negative dt ignored. NULL-safe. */
int ip_anim_tick(ip_anim *a, double dt_ms);

/* Current interpolated value. 0 if no keyframes or fill=none + done. */
double ip_anim_current(const ip_anim *a);

/* 1 if animation has finished (all iterations, no forwards fill). */
int ip_anim_done(const ip_anim *a);

#endif /* FREEDOM_INTERP_H */
