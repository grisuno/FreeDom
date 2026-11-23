#ifndef FREEDOM_VIDEO_CONTROLS_H
#define FREEDOM_VIDEO_CONTROLS_H
#ifdef __cplusplus
#error "Freedom is pure C11"
#endif

/*
 * video_controls (vcl_) — geometry, hit-test and time math of the browser's own
 * player bar (spec/video_controls.md). Pure: no I/O, no clock, no allocation.
 * The painter and the pointer read the SAME geometry.
 */

#include <stddef.h>
#include <stdint.h>

#include "hls.h"

#define VCL_BAR_H          40.0  /* bar height, px */
#define VCL_MIN_W         120.0  /* narrower video rect: no bar */
#define VCL_MIN_H          80.0  /* shorter video rect: no bar */
#define VCL_PAD            10.0
#define VCL_TEXT_W         96.0  /* room for "h:mm:ss / h:mm:ss" */
#define VCL_TRACK_H         4.0
#define VCL_MAX_SEGMENT_S 86400.0 /* one hostile #EXTINF counts at most 24 h */
#define VCL_SEEK_STEP_S    10.0  /* arrow keys */

typedef struct vcl_rect { double x, y, w, h; } vcl_rect;

typedef struct vcl_geom {
    vcl_rect bar;      /* translucent strip at the bottom of the video */
    vcl_rect play;     /* play/pause button */
    vcl_rect track;    /* seek track (thin line, vertically centred in the bar) */
    vcl_rect hit_track;/* the track's clickable band: full bar height */
    double   text_x;   /* time label origin */
    double   text_y;   /* baseline */
} vcl_geom;

typedef enum vcl_hit_kind {
    VCL_HIT_NONE = 0,  /* outside the video rect */
    VCL_HIT_TOGGLE,    /* play button or the video surface */
    VCL_HIT_SEEK,      /* on the track: *frac in [0,1] */
    VCL_HIT_BAR        /* elsewhere on the bar: swallowed */
} vcl_hit_kind;

/* Lays out the bar inside the video rect (x,y,w,h). Returns 1 and fills *g, or 0
 * (and zeroes *g) when the rect is too small or not finite: then there is no bar. */
int vcl_layout(double x, double y, double w, double h, vcl_geom *g);

/* Classifies a pointer at (px,py). g may be NULL (no bar: the surface toggles).
 * *frac (may be NULL) receives the track position for VCL_HIT_SEEK, else 0. */
vcl_hit_kind vcl_hit(const vcl_geom *g, const vcl_rect *video, double px, double py,
                     double *frac);

/* Sanitised duration of one segment: non-finite or negative => 0, capped. */
double vcl_seg_duration(double d);

/* Total duration in seconds (0 for NULL/empty). Always finite. */
double vcl_total(const hls_playlist *pl);

/* Index of the segment containing t (clamped to the playlist) and its start time
 * in *start (may be NULL). NULL/empty playlist => 0 and *start = 0. */
size_t vcl_segment_at(const hls_playlist *pl, double t, double *start);

/* Start time (s) of segment idx (clamped). */
double vcl_segment_start(const hls_playlist *pl, size_t idx);

/* Playback position: base_s + (pts_us - pts0_us)/1e6, clamped to [0,total]. */
double vcl_position(double base_s, int64_t pts0_us, int64_t pts_us, double total);

/* Clamps a seek fraction to [0,1]; NaN => 0. */
double vcl_clamp_frac(double f);

/* Writes "m:ss" (or "h:mm:ss" from one hour) into buf; returns the length, or 0
 * when buf is NULL/too small (buf then holds "" when cap > 0). Negative/NaN => 0:00. */
size_t vcl_format_time(double seconds, char *buf, size_t cap);

#endif /* FREEDOM_VIDEO_CONTROLS_H */
