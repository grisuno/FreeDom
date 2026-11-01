#ifndef FREEDOM_SVG_RASTER_H
#define FREEDOM_SVG_RASTER_H

#include <stddef.h>
#include <stdint.h>

#include "image_decode.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * svg_raster -- an SVG document served as an IMAGE turned into paint-ready pixels.
 *
 * Runs where every image decoder runs: inside the confined tab worker. The bytes
 * are parsed by the pure, fuzzed svg_render (whose grammar has no URL form, so the
 * image can fetch nothing) and painted with Cairo onto an in-memory surface. Text
 * shapes are skipped: drawing text would open fontconfig (system files), which the
 * worker must not touch. See spec/svg_raster.md.
 */

#define SR_SNIFF_MAX 1024u   /* bytes inspected by sr_sniff */
#define SR_MAX_DIM   2048u   /* longest side of the raster; larger scales down */
#define SR_MIN_RASTER 128u   /* a smaller SVG is oversampled (up to IMG_MAX_SCALE) */

/* 1 when the first element of the document (after BOM, whitespace, the XML
 * declaration, comments and a doctype) is <svg; 0 otherwise. Pure. */
int sr_sniff(const uint8_t *bytes, size_t len);

/* Rasterizes an SVG document at its intrinsic size (width/height, else the viewBox,
 * else 300x150), scaled uniformly to fit SR_MAX_DIM. An image whose longest side is
 * under SR_MIN_RASTER is drawn at an integer density (out->scale, at most
 * IMG_MAX_SCALE) so it stays sharp when CSS scales it up; its CSS size is
 * width/scale x height/scale. On IMG_OK *out owns the pixels (premultiplied ARGB32,
 * release with img_pixels_free); on any error *out is zeroed. */
img_status sr_rasterize(const uint8_t *bytes, size_t len, img_pixels *out);

#endif /* FREEDOM_SVG_RASTER_H */
