#ifndef FREEDOM_SVG_PAINT_H
#define FREEDOM_SVG_PAINT_H

#include <cairo.h>

#include "svg_render.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * svg_paint — draws the bounded shape list svg_render produced, with Cairo.
 *
 * The split is the point: everything that touches hostile BYTES is the pure,
 * fuzzed svg_render; this half only turns validated geometry into Cairo calls, on
 * the trusted side, exactly like the painter already draws author boxes and
 * gradients. It resolves no URL and reads no file, because the shape list cannot
 * carry either.
 *
 * See spec/svg_render.md §4.
 */

/* Paints `img` into the rect [x, y, w, h] of `cr`, scaled uniformly and centred
 * ("xMidYMid meet"). current_rgb is the inherited text colour, substituted wherever
 * a shape asked for `currentColor` (packed 0xRRGGBB). The Cairo state is saved and
 * restored around the call, and painting is clipped to the rect, so a hostile
 * transform can never draw outside the box the layout gave the image.
 *
 * No-ops on a NULL argument or a non-positive rect. */
void svp_draw(cairo_t *cr, const sv_image *img,
              double x, double y, double w, double h, int current_rgb);

#endif /* FREEDOM_SVG_PAINT_H */
