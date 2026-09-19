# include

*Community 8 | 3 files | cohesion 0.67*

## Definition

This community groups 3 file(s) rooted at `include` with dominant language c (cohesion 0.67). Central symbols: `FREEDOM_INTERP_H`, `IP_ITERATION_INFINITE`, `IP_MAX_KEYFRAMES`, `anim_effective_dir`, `anim_effective_dir_for`, `assert_float_equal`, `ip_anim`, `ip_anim_current`. Core file: `tests/test_interp.c` (37 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/interp.h` | h | utility | 22 | no |
| `src/interp.c` | c | utility | 19 | no |
| `tests/test_interp.c` | c | testing | 37 | no |

## Key Symbols

- `FREEDOM_INTERP_H` (macro, `include/interp.h:2`) `#define FREEDOM_INTERP_H`
- `ip_easing` (enum, `include/interp.h:25`)
- `kind` (type_alias, `include/interp.h:37`) `typedef struct ip_ease_fn { ip_easing kind;`
- `ip_ease_fn` (struct, `include/interp.h:38`)
- `ip_ease` (function, `include/interp.h:48`) `double ip_ease(double t, const ip_ease_fn *fn);` - Compute eased t for normalized t ∈ [0,1]. Returns value ∈ [0,1]. * Clamped: t < 0 → 0, t > 1 → 1. NU
- `ip_val_kind` (enum, `include/interp.h:54`)
- `ip_lerp` (function, `include/interp.h:60`) `double ip_lerp(double a, double b, double t);`
- `ip_lerp_color` (function, `include/interp.h:61`) `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t);`
- `ip_interp` (function, `include/interp.h:62`) `double ip_interp(ip_val_kind kind, double a, double b, double t);`
- `IP_MAX_KEYFRAMES` (macro, `include/interp.h:68`) `#define IP_MAX_KEYFRAMES`
- `pct` (type_alias, `include/interp.h:69`) `typedef struct ip_keyframe { double pct;` - define IP_MAX_KEYFRAMES 16
- `ip_keyframe` (struct, `include/interp.h:70`)
- `ip_kf_interp` (function, `include/interp.h:78`) `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf, int n_kf, doubl` - Interpolate between the two keyframes bracketing `pct` (0..100). Exact match → that keyframe's value
- `IP_ITERATION_INFINITE` (macro, `include/interp.h:85`) `#define IP_ITERATION_INFINITE`
- `ip_direction` (enum, `include/interp.h:87`)
- `ip_fill_mode` (enum, `include/interp.h:94`)
- `val_kind` (type_alias, `include/interp.h:100`) `typedef struct ip_anim { ip_val_kind val_kind;`
- `ip_anim` (struct, `include/interp.h:101`)
- `ip_anim_init` (function, `include/interp.h:121`) `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease, const ip_k` - double duration_ms; double delay_ms; int iteration_count; int direction; int fill_mode; /* Runtime s
- `ip_anim_tick` (function, `include/interp.h:128`) `int ip_anim_tick(ip_anim *a, double dt_ms);` - Advance time by dt_ms. Returns 1 if the value changed, 0 if * unchanged. Negative dt ignored. NULL-s
- `ip_anim_current` (function, `include/interp.h:131`) `double ip_anim_current(const ip_anim *a);` - Advance time by dt_ms. Returns 1 if the value changed, 0 if * unchanged. Negative dt ignored. NULL-s
- `ip_anim_done` (function, `include/interp.h:134`) `int ip_anim_done(const ip_anim *a);` - Advance time by dt_ms. Returns 1 if the value changed, 0 if * unchanged. Negative dt ignored. NULL-s
- `sample_bezier_x` (function, `src/interp.c:18`) `static double sample_bezier_x(double t, double cx1, double cx2)`
- `sample_bezier_dx` (function, `src/interp.c:23`) `static double sample_bezier_dx(double t, double cx1, double cx2)`
- `sample_bezier_y` (function, `src/interp.c:29`) `static double sample_bezier_y(double t, double cy1, double cy2)`
- `solve_bezier_t` (function, `src/interp.c:35`) `static double solve_bezier_t(double x, double cx1, double cx2)` - } static double sample_bezier_dx(double t, double cx1, double cx2) { return 3.0 * cx1 * (1.0 - 4.0 *
- `ip_ease` (function, `src/interp.c:55`) `double ip_ease(double t, const ip_ease_fn *fn)`
- `ip_ease` (function, `src/interp.c:64`) `case IP_EASE_EASE:         return ip_ease(t, &(ip_ease_fn)`
- `ip_ease` (function, `src/interp.c:70`) `case IP_EASE_EASE_IN:         return ip_ease(t, &(ip_ease_fn)`
- `ip_ease` (function, `src/interp.c:76`) `case IP_EASE_EASE_OUT:         return ip_ease(t, &(ip_ease_fn)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- [EXTRACTED] depends_on community 0 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/interp.h.
- [INFERRED] shares_context community 1 <-> 8 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (include) and community 8 (include).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 3 file(s) lack file-level docs (e.g. `include/interp.h`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.67?

## Sources

- `include/interp.h`
- `src/interp.c`
- `tests/test_interp.c`
