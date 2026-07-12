#ifndef FREEDOM_IMAGE_DECODE_H
#define FREEDOM_IMAGE_DECODE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * image_decode — turns raw image bytes into paint-ready pixels.
 *
 * Deterministic, no network and no filesystem: it only reads the input buffer and
 * allocates the output bitmap. Decoding hostile image bytes (libpng + zlib, libjpeg,
 * libwebp) is a classic attack surface, so this code is meant to run inside the
 * confined tab worker (seccomp allowlist + Landlock), never in the parent. The
 * parent fetches the bytes through secure_fetch and paints the result; it never
 * decodes.
 *
 * Scope: PNG, JPEG (baseline + progressive), static GIF (first frame) and WebP
 * (lossless/lossy). Any other format is rejected (IMG_ERR_FORMAT) and the
 * orchestrator shows the placeholder. JPEG is an owner-authorised exception to
 * the PNG-only doctrine, contained by the same sandbox plus libjpeg-specific
 * guards (in-memory source only, longjmp error manager so a bad stream never
 * calls exit(), dimension caps before decode); see spec/image_decode.md §0.1.
 * GIF is decoded by an OWN pure-C LZW decoder (no giflib: fewer dependencies
 * to audit; spec §0.2), bounded and fuzzed like the rest. WebP uses libwebp's
 * in-memory API (WebPDecodeBGRAInto), with dimension caps before full decode.
 * Fails closed on every doubt.
 */

typedef enum img_format {
    IMG_FMT_UNKNOWN = 0,
    IMG_FMT_PNG = 1,
    IMG_FMT_JPEG = 2,
    IMG_FMT_GIF = 3,
    IMG_FMT_WEBP = 4
} img_format;

typedef enum img_status {
    IMG_OK = 0,
    IMG_ERR_NULL_ARG,   /* a required pointer argument was NULL */
    IMG_ERR_FORMAT,     /* bytes are not a PNG (or an unsupported format) */
    IMG_ERR_TRUNCATED,  /* header/IHDR incomplete: not enough bytes */
    IMG_ERR_DIMENSIONS, /* zero, or above the anti-DoS caps */
    IMG_ERR_DECODE,     /* libpng rejected the stream (corrupt / unsupported) */
    IMG_ERR_OOM         /* allocation failed */
} img_status;

/* A decoded bitmap that owns its pixel buffer. The pixel format is Cairo's native
 * premultiplied ARGB32: each pixel is a uint32_t 0xAARRGGBB, i.e. bytes B,G,R,A in
 * little-endian memory, colour premultiplied by alpha. stride == width*4 (tightly
 * packed). This module never includes cairo.h; it only honours that layout so the
 * parent can wrap data in a cairo_surface_t without re-encoding. */
typedef struct img_pixels {
    uint32_t  width;
    uint32_t  height;
    uint32_t  stride;
    uint8_t  *data;
} img_pixels;

/* Anti-DoS bounds. A tiny compressed PNG can declare huge dimensions (a
 * decompression bomb); dimensions are checked against these BEFORE decoding. */
#define IMG_MAX_DIM     8192u
#define IMG_MAX_PIXELS  (16u * 1024u * 1024u)  /* 16 Mpx -> 64 MiB ARGB */

/* Detects the format from the leading magic bytes. NULL or too-short => UNKNOWN. */
img_format img_sniff(const uint8_t *bytes, size_t len);

/* Reads width/height from a PNG IHDR without decompressing anything. bytes/out
 * NULL => IMG_ERR_NULL_ARG; not a PNG => IMG_ERR_FORMAT; too short => IMG_ERR_TRUNCATED. */
img_status img_png_dimensions(const uint8_t *bytes, size_t len,
                              uint32_t *out_w, uint32_t *out_h);

/* 1 iff (w,h) is non-zero and fits the anti-DoS caps (per-side and area, no
 * overflow of width*height*4); 0 otherwise. */
int img_dimensions_ok(uint32_t w, uint32_t h);

/* Aspect-preserving fit: the largest (dw,dh) <= (box_w,box_h) with dw/dh == iw/ih.
 * Degenerate inputs (<= 0) yield (0,0). Pure. */
void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,
             double *out_w, double *out_h);

/* Decodes a PNG into out (premultiplied ARGB32; see img_pixels). Rejects non-PNG,
 * truncated input, out-of-bounds dimensions (before decoding) and corrupt streams.
 * On IMG_OK, *out owns data and must be released with img_pixels_free. On any error
 * *out is zeroed and nothing leaks. Reentrant: no global state. */
img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out);

/* Decodes a JPEG (baseline/progressive) into out (ARGB32, opaque alpha 0xFF). Bounds
 * the declared dimensions BEFORE the full decode (anti-bomb), decodes to RGB and
 * expands to BGRA. Rejects non-JPEG (IMG_ERR_FORMAT), out-of-bounds dimensions, CMYK/
 * YCCK and corrupt streams (IMG_ERR_DECODE, via a longjmp error manager — never calls
 * exit()). Ownership/zeroing/reentrancy as img_decode_png. */
img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out);

/* Decodes the FIRST frame of a GIF87a/GIF89a into out (premultiplied ARGB32; a
 * GCE-transparent index yields 0x00000000). Own bounded LZW decoder (dict <= 4096
 * codes, expansion capped by the frame area — never hangs); global/local palette,
 * 4-pass interlace. Logical-screen dimensions are bounded BEFORE any allocation.
 * Rejects non-GIF, truncated streams, out-of-range LZW codes and palette indexes.
 * Ownership/zeroing/reentrancy as img_decode_png. See spec/image_decode.md §0.2. */
img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out);

/* Decodes a WebP image into out (premultiplied ARGB32). Uses libwebp's
 * in-memory source API (WebPDecodeBGRA). Declared dimensions are bounded
 * BEFORE the full decode (anti decompression bomb). Rejects non-WebP
 * (IMG_ERR_FORMAT), out-of-bounds dimensions (IMG_ERR_DIMENSIONS) and
 * corrupt streams (IMG_ERR_DECODE). Ownership/zeroing/reentrancy as
 * img_decode_png. */
img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out);

/* Generic entry point: sniffs the format and routes to img_decode_png/
 * img_decode_jpeg/img_decode_gif/img_decode_webp; an unrecognised format
 * yields IMG_ERR_FORMAT. This is what the confined worker calls. Fails closed. */
img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out);

/* Releases data and zeroes the struct. Idempotent; safe on NULL and on a zeroed
 * struct. */
void img_pixels_free(img_pixels *p);

/* Stable, short English name of a format for structured/agent output. Never NULL. */
const char *img_format_name(img_format f);

#endif /* FREEDOM_IMAGE_DECODE_H */
