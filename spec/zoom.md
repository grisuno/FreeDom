# spec: zoom (`zm_`)

Pure, I/O-free page-zoom arithmetic. The GUI keeps a per-window zoom percentage;
this module is the directly auditable surface that decides what the next zoom
level is and how a base pixel size maps to a zoomed one. No Cairo, no Wayland,
no global state, reentrant.

The GUI orchestrator (`gui/browser_ui.c`) owns the state (`browser_window.zoom_pct`)
and the I/O (scaling `theme.body_font` and repainting). It only calls these pure
functions; it never re-implements the ladder.

## Model

Zoom is an integer percentage. Discrete user steps snap to a fixed ladder of
common stops so repeated `Ctrl +` / `Ctrl -` land on predictable values, exactly
like a mainstream browser:

    50, 67, 75, 90, 100, 110, 125, 150, 175, 200, 250, 300

`100` is the default (no scaling). The minimum is `ZM_MIN_PCT = 50`, the maximum
is `ZM_MAX_PCT = 300`. Any percentage handed in is first clamped to that range,
so an out-of-range or off-ladder value (e.g. a corrupted restore) can never
escape the bounds — Secure by Default: the unsafe state is not representable.

## API

| Function | Returns |
| :-- | :-- |
| `int zm_clamp(int pct)` | `pct` clamped to `[ZM_MIN_PCT, ZM_MAX_PCT]`. |
| `int zm_zoom_in(int pct)` | The smallest ladder stop strictly greater than `zm_clamp(pct)`; `ZM_MAX_PCT` if already at/above the top. |
| `int zm_zoom_out(int pct)` | The largest ladder stop strictly less than `zm_clamp(pct)`; `ZM_MIN_PCT` if already at/below the bottom. |
| `int zm_reset(void)` | `ZM_DEFAULT_PCT` (100). |
| `double zm_scale(int pct)` | `zm_clamp(pct) / 100.0` — the multiplicative factor. |
| `double zm_apply(double base_px, int pct)` | `base_px * zm_scale(pct)`; floored to `1.0` when `base_px > 0` so a font can never scale away to nothing. `base_px <= 0` returns `base_px * scale` unfloored. |

## Guarantees

- **Bounded.** Every function clamps its input first; the output of `zm_zoom_in`
  / `zm_zoom_out` / `zm_clamp` / `zm_reset` is always in `[ZM_MIN_PCT, ZM_MAX_PCT]`.
- **Monotone & terminating.** Repeated `zm_zoom_in` is non-decreasing and reaches
  `ZM_MAX_PCT`; repeated `zm_zoom_out` is non-increasing and reaches `ZM_MIN_PCT`.
  Stepping never oscillates and never overshoots the ladder ends.
- **Idempotent at the ends.** `zm_zoom_in(ZM_MAX_PCT) == ZM_MAX_PCT`,
  `zm_zoom_out(ZM_MIN_PCT) == ZM_MIN_PCT`.
- **Snapping.** From an off-ladder value, a single step lands on the nearest stop
  in that direction (e.g. `zm_zoom_in(105) == 110`, `zm_zoom_out(105) == 100`).
- **Pure.** No allocation, no I/O, no global state; safe to call from any thread.

## Out of scope

- Per-site / persisted zoom (window-level only for now; persistence is Hito 10).
- Reflow/layout: scaling the actual glyphs is the GUI's Cairo job. This module
  only yields the level and the factor.
