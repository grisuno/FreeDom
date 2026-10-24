#ifndef FREEDOM_BOX_BLUR_H
#define FREEDOM_BOX_BLUR_H

#ifdef __cplusplus
#error "Freedom is pure C11"
#endif

/* Gaussian blur of an 8-bit alpha mask by three box passes per axis
 * (spec/box_blur.md). Pure: no I/O, one scratch allocation freed before return. */

/* Largest mask bb_blur_a8 accepts (anti-DoS). */
#define BB_MAX_PIXELS (16 * 1024 * 1024)

/* The three odd box widths approximating a Gaussian of standard deviation sigma.
 * Returns 0 (sizes untouched) when sigma is not finite or <= 0, else 1. */
int bb_box_sizes(double sigma, int sizes[3]);

/* Blurs buf (w x h, stride bytes per row) in place. Outside the buffer is 0.
 * Returns 1 when blurred, 0 when sigma <= 0 (nothing to do), -1 on invalid
 * arguments or a mask larger than BB_MAX_PIXELS (buffer untouched). */
int bb_blur_a8(unsigned char *buf, int w, int h, int stride, double sigma);

/* Smallest rectangle of a premultiplied ARGB32 surface that a blur of `sigma` can change: the
 * bounding box of every pixel with non-zero alpha, grown by the blur's reach (the sum of its three
 * box radii) and clamped to the surface. rect = {x0, y0, x1, y1}, x1/y1 exclusive. Returns 0 when
 * no pixel has alpha (nothing to blur), 1 otherwise. Everything outside rect stays 0 after the blur,
 * so blurring just rect is identical to blurring the whole surface. */
int bb_ink_rect(const unsigned char *argb, int w, int h, int stride, double sigma, int rect[4]);

#endif
