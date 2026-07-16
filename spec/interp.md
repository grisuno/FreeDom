# Spec: `interp` (`ip_`) — CSS interpolation engine

> Phase R1d — Animation & Transition Engine foundation.
> Status: SPEC. Methodology: SDD + TDD (ATDD Dado-Cuando-Entonces).
> Module **pure** (no I/O, no Cairo, no allocation, no time source): easing, value
> interpolation, keyframe-state machine. The trusted-side frame clock and GUI paint
> orchestration consume this module.

## 1. Purpose

CSS animations (`@keyframes` + `animation-*`) and transitions (`transition-*`) need
an engine that, given elapsed time and two or more keyframes, computes the current
interpolated value. This module provides:

1. **Easing functions** (`ip_ease`) — map normalized t ∈ [0,1] → eased t ∈ [0,1].
2. **Value interpolation** (`ip_lerp`, `ip_lerp_color`) — linear interpolation
   between scalars and packed RGB colors.
3. **Keyframe interpolation** (`ip_kf_value`) — given N keyframes at positions
   0..100%, compute the interpolated value at time t.
4. **Animation state machine** (`ip_anim`) — tracks elapsed time, handles
   delay, iterations, direction, fill mode, and returns the current value.

No sockets, no files, no Cairo, no GPU. Pure math over validated scalars.
Directly testable. No fuzz needed (no remote content parsing).

## 2. Easing functions

### API

```c
typedef enum ip_easing {
    IP_EASE_LINEAR = 0,
    IP_EASE_EASE,
    IP_EASE_EASE_IN,
    IP_EASE_EASE_OUT,
    IP_EASE_EASE_IN_OUT,
    IP_EASE_STEP_START,  /* ceil(t*n)/n — jump at start of step */
    IP_EASE_STEP_END,    /* floor(t*n)/n — jump at end of step */
    IP_EASE_STEPS,       /* steps(n, <start|end>) — dir 0=end, 1=start */
    IP_EASE_CUBIC_BEZIER,
    IP_EASE_COUNT
} ip_easing;

typedef struct ip_ease_fn {
    ip_easing kind;
    int  steps_n;          /* for STEPS/STEP_START/STEP_END */
    int  steps_dir;        /* 0=end, 1=start */
    double cx1, cy1;       /* cubic-bezier control points */
    double cx2, cy2;
} ip_ease_fn;

/* Compute eased t for normalized t ∈ [0,1]. Returns value ∈ [0,1].
   Clamped: t<0 → 0, t>1 → 1. NULL-safe: returns t. */
double ip_ease(double t, const ip_ease_fn *fn);
```

### Semantics (Dado-Cuando-Entonces)

- **Dado** `t=0.5`, `IP_EASE_LINEAR` ⇒ `0.5`
- **Dado** `t=0`, cualquier easing ⇒ `0.0`
- **Dado** `t=1`, cualquier easing ⇒ `1.0`
- **Dado** `t=0.5`, `IP_EASE_EASE_IN` ⇒ valor < `0.5` (empieza lento)
- **Dado** `t=0.5`, `IP_EASE_EASE_OUT` ⇒ valor > `0.5` (termina lento)
- **Dado** `t=-0.1` ⇒ `0.0` (clamped)
- **Dado** `t=1.5` ⇒ `1.0` (clamped)
- **Dado** `NULL` fn ⇒ retorna `t` (fall-safe, identidad)
- **Dado** `IP_EASE_STEPS, n=4, dir=end`: `t=0.0→0`, `t=0.24→0`, `t=0.25→0.25`, `t=0.26→0.25`, `t=0.99→0.75`
- **Dado** `IP_EASE_STEPS, n=4, dir=start`: `t=0.0→0.25`, `t=0.01→0.25`, `t=0.25→0.5`, `t=0.99→1`
- **Dado** `IP_EASE_CUBIC_BEZIER(0.42,0,1,1)` = ease-in: `t=0.5 ⇒ ~0.315`
- **Dado** `IP_EASE_CUBIC_BEZIER(0,0,0.58,1)` = ease-out: `t=0.5 ⇒ ~0.685`

### Errors / defense

- `steps_n <= 0` ⇒ treat as `steps_n = 1` (defensive, never divide by zero)
- `cx1,cy1,cx2,cy2` outside [0,1] ⇒ clamped (bezier with control points outside valid range produces non-monotonic curves; we clamp to preserve monotonicity for animation timing)
- NaN input ⇒ treat as 0 (clamped)
- Infinite input ⇒ treat as 1 (clamped)

## 3. Value interpolation

### API

```c
typedef enum ip_val_kind {
    IP_VAL_SCALAR = 0,  /* double, lerp */
    IP_VAL_COLOR,       /* packed 0xRRGGBB, interpolate per-channel */
    IP_VAL_COUNT
} ip_val_kind;

/* Interpolate scalar: lerp(a, b, t). t ∈ [0,1], clamped. */
double ip_lerp(double a, double b, double t);

/* Interpolate packed color (0xRRGGBB). Interpolates each channel independently,
   rounds to nearest integer. Alpha is always 0xFF. */
uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t);

/* Generic interpolate: switches on kind. */
double ip_interp(ip_val_kind kind, double a, double b, double t);
```

### Semantics

- `ip_lerp(0, 100, 0.5)` ⇒ `50.0`
- `ip_lerp(10, 20, 0.0)` ⇒ `10.0`
- `ip_lerp(10, 20, 1.0)` ⇒ `20.0`
- `ip_lerp_color(0xFF0000, 0x0000FF, 0.5)` ⇒ `0x800080` (rounded from 127.5)
- `ip_lerp_color(0x000000, 0xFFFFFF, 0.25)` ⇒ `0x404040` (rounded from 63.75)
- `ip_interp(IP_VAL_SCALAR, 0, 100, 0.5)` ⇒ `50.0`
- `ip_interp(IP_VAL_COLOR, 0xFF0000, 0x0000FF, 0.5)` ⇒ `0x800080`

## 4. Keyframe interpolation

### API

```c
#define IP_MAX_KEYFRAMES 16

typedef struct ip_keyframe {
    double pct;   /* 0.0 .. 100.0, must be sorted ascending */
    double val;   /* scalar or packed color */
} ip_keyframe;

/* Find the two keyframes bracketing `pct` (0..100) and interpolate.
   If exactly on a keyframe, returns that keyframe's value.
   Before first keyframe: first value. After last: last value.
   val_kind: IP_VAL_SCALAR or IP_VAL_COLOR.
   kf == NULL or n_kf == 0: returns 0.
   n_kf == 1: returns that keyframe's value. */
double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf, int n_kf, double pct);
```

### Semantics

- **Dado** `kf=[{0,0},{100,100}]`, `pct=50`, `IP_VAL_SCALAR` ⇒ `50.0`
- **Dado** `kf=[{0,0},{50,200},{100,100}]`, `pct=25`, `IP_VAL_SCALAR` ⇒ `100.0` (lerp between kf[0] and kf[1])
- **Dado** `kf=[{0,0xFF0000},{100,0x0000FF}]`, `pct=50`, `IP_VAL_COLOR` ⇒ `0x800080`
- **Dado** `kf=[{25,50},{75,100}]`, `pct=0` ⇒ `50.0` (before first kf, clamp)
- **Dado** `kf=[{25,50},{75,100}]`, `pct=100` ⇒ `100.0` (after last kf, clamp)
- **Dado** `kf=NULL`, `n_kf=0` ⇒ `0.0` (fail-safe)
- **Dado** `kf=[{50,42}]`, any pct ⇒ `42.0` (single keyframe)

## 5. Animation state machine

### API

```c
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
    const ip_keyframe *keyframes;  /* borrowed, caller keeps alive */
    int n_keyframes;

    double duration_ms;
    double delay_ms;
    int iteration_count;   /* -1 = infinite */
    int direction;         /* ip_direction */
    int fill_mode;         /* ip_fill_mode */

    /* Runtime state (mutable) */
    double elapsed_ms;
    int current_iteration;
    int done;
} ip_anim;

/* Initialize. kf must outlive the animation or be NULL (0 kf = no-op). */
void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease,
                  const ip_keyframe *kf, int n_kf,
                  double duration_ms, double delay_ms,
                  int iteration_count, int direction, int fill_mode);

/* Advance time by dt_ms. Returns 1 if the current value changed, 0 if
   unchanged (paused, done, or within delay without backwards fill). */
int ip_anim_tick(ip_anim *a, double dt_ms);

/* Get the current interpolated value (packed as double; caller casts to
   uint32_t for colors). If no keyframes, returns 0. If done and no forwards
   fill, returns 0. */
double ip_anim_current(const ip_anim *a);

/* 1 if animation has finished all iterations (not infinite) and fill not forwards/both. */
int ip_anim_done(const ip_anim *a);
```

### State machine (Dado-Cuando-Entonces)

#### Delay phase
- **Dado** `duration=1000, delay=500, iter=1, fill=none`, `tick(200)` ⇒ retorna 0, `current()` ⇒ 0
- **Dado** `duration=1000, delay=500, fill=backwards`, `tick(200)` ⇒ retorna 1, `current()` ⇒ kf[0].val
- **Dado** `duration=1000, delay=500, fill=none`, `tick(600)` ⇒ retorna 1, phase=active

#### Active phase (normal direction)
- **Dado** `duration=1000, kf=[{0,0},{100,100}]`, `tick(0)` ⇒ `current() ≈ 0`
- **Dado** `duration=1000, kf=[{0,0},{100,100}]`, `tick(250)` ⇒ `current() ≈ 25` (linear ease)
- **Dado** `duration=1000, kf=[{0,0},{100,100}]`, `tick(1000)` ⇒ `current() = 100`, iteration ends

#### Iterations
- **Dado** `duration=1000, iter=2, fill=none`, `tick(1000)` ⇒ iteration=2 starts, `current()=0`
- **Dado** `duration=1000, iter=2, fill=none`, `tick(2000)` ⇒ done, `current()=0`
- **Dado** `duration=1000, iter=IP_ITERATION_INFINITE`, `tick(999999)` ⇒ never done, cycles

#### Fill modes
- **Dado** `duration=1000, iter=1, fill=forwards`, `tick(2000)` ⇒ done=1, `current()=kf[last].val`
- **Dado** `duration=1000, iter=1, fill=both`, `tick(0)` still in delay ⇒ `current()=kf[0].val`
- **Dado** `duration=1000, iter=1, fill=none`, `done()` ⇒ 1, `current()` ⇒ 0

#### Direction
- **Dado** `dir=reverse`, `kf=[{0,0},{100,100}]`, `tick(250)` ⇒ `current() ≈ 75` (starts at end)
- **Dado** `dir=alternate, iter=2`, iter 1 normal ⇒ `0→100`, iter 2 reverse ⇒ `100→0`
- **Dado** `dir=alternate_reverse, iter=1` ⇒ starts reverse ⇒ `100→0`

#### Edge cases
- **Dado** `n_kf=0` ⇒ `current()` siempre 0, `tick()` no-op, `done()` siempre 1
- **Dado** `duration=0` ⇒ tratado como `duration=1` (defensive, never divide by zero)
- **Dado** dt_ms negativo ⇒ ignorado (no retrocede el tiempo, `elapsed_ms` no cambia)
- **Dado** `ip_anim_init(NULL, ...)` ⇒ no-op (NULL-safe)

## 6. Out of scope

- `cubic-bezier(x1,y1,x2,y2)` with x1 > 1 or x2 < 0 (multi-bounce curves; CSS allows but rare; clamped to [0,1])
- `steps()` with `jump-both`/`jump-none` keywords (CSS 4; not widely implemented)
- Color interpolation in HSL space (v1 uses RGB only)
- Color with alpha channel (v1 colors are opaque 0xRRGGBB; alpha is separate)
- Transform matrix interpolation (translate/rotate/scale interpolate as independent scalars)
- `animation-play-state: paused` repaints (v1: paused stops the clock; resumed continues)
- Per-element `transition-property: all` with comprehensive property mapping (v1: explicit property list)
