#ifndef FREEDOM_ZOOM_H
#define FREEDOM_ZOOM_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * zoom — pure, I/O-free page-zoom arithmetic.
 *
 * Zoom is an integer percentage. User steps snap to a fixed ladder of common
 * stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a
 * mainstream browser. Every function clamps its input to [ZM_MIN_PCT,
 * ZM_MAX_PCT] first, so an out-of-range value (e.g. a corrupted restore) can
 * never escape the bounds. No allocation, no I/O, no global state; reentrant.
 *
 * The GUI owns the state (browser_window.zoom_pct) and the Cairo scaling; it
 * only calls these. See spec/zoom.md.
 */

#define ZM_MIN_PCT     50
#define ZM_MAX_PCT     300
#define ZM_DEFAULT_PCT 100

/* Clamp pct to [ZM_MIN_PCT, ZM_MAX_PCT]. */
int zm_clamp(int pct);

/* Smallest ladder stop strictly greater than zm_clamp(pct); ZM_MAX_PCT if none. */
int zm_zoom_in(int pct);

/* Largest ladder stop strictly less than zm_clamp(pct); ZM_MIN_PCT if none. */
int zm_zoom_out(int pct);

/* The default zoom level (100). */
int zm_reset(void);

/* Multiplicative factor: zm_clamp(pct) / 100.0. */
double zm_scale(int pct);

/* base_px * zm_scale(pct), floored to 1.0 when base_px > 0 so a font can never
 * scale away to nothing. base_px <= 0 returns base_px * scale unfloored. */
double zm_apply(double base_px, int pct);

#endif /* FREEDOM_ZOOM_H */
