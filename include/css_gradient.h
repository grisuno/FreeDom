#ifndef FREEDOM_CSS_GRADIENT_H
#define FREEDOM_CSS_GRADIENT_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

#include <stddef.h>
#include "css_decl.h"

int cg_expand_bg_image(const char *val, css_decl *dst, int cap,
                       char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap);
int cg_expand_background(const char *val, css_decl *dst, int cap,
                         char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap);

/* Radial-gradient geometry (spec/css_gradient.md 3b). Lengths: >= 0 is per-mille of the box
 * width (x, rx) or height (y, ry); < 0 is -(px) - 1; CG_LEN_UNSET = not given. */
#define CG_LEN_UNSET (-2147483647 - 1)
typedef enum cg_radial_shape { CG_RAD_ELLIPSE = 0, CG_RAD_CIRCLE = 1 } cg_radial_shape;
typedef enum cg_radial_size {
    CG_RS_FARTHEST_CORNER = 0, CG_RS_CLOSEST_SIDE, CG_RS_FARTHEST_SIDE,
    CG_RS_CLOSEST_CORNER, CG_RS_EXPLICIT
} cg_radial_size;
typedef struct cg_radial {
    int shape;   /* cg_radial_shape */
    int size;    /* cg_radial_size */
    int rx, ry;  /* explicit radii (size == CG_RS_EXPLICIT) */
    int cx, cy;  /* centre, default 500 / 500 */
} cg_radial;

/* The first comma segment of a radial-gradient() argument list, when it is a prelude.
 * Returns 1 and fills *out (defaults first) when seg is a valid prelude, 0 when seg is not
 * one (it is a colour stop), -1 when it is malformed (the caller drops the gradient). Pure. */
int cg_parse_radial_prelude(const char *seg, cg_radial *out);

/* A radial length resolved against a box dimension in px. */
double cg_radial_len_px(int enc, double dim);

/* The used geometry of a radial gradient on a w x h box (CSS Images 3 3.2.3): the centre and
 * the two radii, in px relative to the box origin. A circle returns rx == ry. Radii are
 * floored at a hair above zero (the spec paints the last colour for a degenerate size) and
 * never non-finite. Pure. */
void cg_radial_geometry(const cg_radial *r, double w, double h,
                        double *cx, double *cy, double *rx, double *ry);

/* Parses one `linear-gradient(...)` function (the whole text, nothing around it) into its angle
 * (CSS degrees), packed stop colours (alpha rides bits 24..30 as TRANSPARENCY, 0 opaque .. 127
 * clear) and stop positions (per-mille, -1 = evenly spaced); both arrays hold CSS_GRAD_STOPS_MAX
 * entries and the caller initialises positions to -1. Returns the stop count, 0 when the text is
 * not a valid linear gradient. Used by the mask parser, which wants the alpha of each stop. */
int cg_parse_linear(const char *fn, int *angle, int *colors, int *positions);

#endif
