# Subsystem: include (page 5 of 5)
Previous: [KB_include_p4.md](KB_include_p4.md)

## include/zoom.h
- Doc: zm_clamp: stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser.
- Layer: utility
- Language: h
- Symbols:
  - `zm_clamp` (function, line 26) `int zm_clamp(int pct);`
  - `zm_zoom_in` (function, line 29) `int zm_zoom_in(int pct);`
  - `zm_zoom_out` (function, line 32) `int zm_zoom_out(int pct);`
  - `zm_reset` (function, line 35) `int zm_reset(void);`
  - `zm_scale` (function, line 38) `double zm_scale(int pct);`
  - `zm_apply` (function, line 42) `double zm_apply(double base_px, int pct);`
  - `FREEDOM_ZOOM_H` (macro, line 2) `#define FREEDOM_ZOOM_H`
  - `ZM_MIN_PCT` (macro, line 21) `#define ZM_MIN_PCT`
  - `ZM_MAX_PCT` (macro, line 22) `#define ZM_MAX_PCT`
  - `ZM_DEFAULT_PCT` (macro, line 23) `#define ZM_DEFAULT_PCT`
- Imported by: `gui/browser_ui.c`, `src/prefs.c`, `src/zoom.c`, `tests/test_prefs.c`, `tests/test_zoom.c`

