/*
 * image_decode — implementation: PNG / JPEG -> Cairo-native ARGB32.
 *
 * PNG uses libpng's simplified read API (no setjmp; success is a return value).
 * JPEG uses libjpeg with an in-memory source and a longjmp error manager so a
 * malformed stream fails closed instead of calling exit(). Output is tightly packed
 * BGRA (Cairo's native CAIRO_FORMAT_ARGB32 byte order); PNG is premultiplied, JPEG
 * is fully opaque (alpha 0xFF, so premultiply is a no-op). No filesystem, no network:
 * this is the piece that runs inside the confined tab worker. See spec/image_decode.md.
 */

#include "image_decode.h"

#include <setjmp.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>
#include <jpeglib.h>

/* The 8-byte PNG signature, and the 3-byte JPEG SOI+marker prefix. */
static const uint8_t PNG_MAGIC[8] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };
static const uint8_t JPEG_MAGIC[3] = { 0xff, 0xd8, 0xff };

/* Bytes needed to read width+height: signature(8) + IHDR len(4) + "IHDR"(4) +
 * width(4) + height(4) = 24, with the type tag at offset 12 and the dimensions at
 * 16/20, all big-endian. */
#define PNG_IHDR_MIN 24u

img_format img_sniff(const uint8_t *bytes, size_t len) {
    if (bytes == NULL) return IMG_FMT_UNKNOWN;
    if (len >= sizeof PNG_MAGIC && memcmp(bytes, PNG_MAGIC, sizeof PNG_MAGIC) == 0)
        return IMG_FMT_PNG;
    if (len >= sizeof JPEG_MAGIC && memcmp(bytes, JPEG_MAGIC, sizeof JPEG_MAGIC) == 0)
        return IMG_FMT_JPEG;
    return IMG_FMT_UNKNOWN;
}

static uint32_t read_be32(const uint8_t *p) {
    return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16)
         | ((uint32_t)p[2] << 8) | (uint32_t)p[3];
}

img_status img_png_dimensions(const uint8_t *bytes, size_t len,
                              uint32_t *out_w, uint32_t *out_h) {
    if (bytes == NULL || out_w == NULL || out_h == NULL) return IMG_ERR_NULL_ARG;
    if (img_sniff(bytes, len) != IMG_FMT_PNG) return IMG_ERR_FORMAT;
    if (len < PNG_IHDR_MIN) return IMG_ERR_TRUNCATED;
    if (memcmp(bytes + 12, "IHDR", 4) != 0) return IMG_ERR_FORMAT;
    *out_w = read_be32(bytes + 16);
    *out_h = read_be32(bytes + 20);
    return IMG_OK;
}

int img_dimensions_ok(uint32_t w, uint32_t h) {
    if (w == 0u || h == 0u) return 0;
    if (w > IMG_MAX_DIM || h > IMG_MAX_DIM) return 0;
    /* w,h <= IMG_MAX_DIM (<= 8192) so the product fits in uint64 with no overflow. */
    if ((uint64_t)w * (uint64_t)h > (uint64_t)IMG_MAX_PIXELS) return 0;
    return 1;
}

void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,
             double *out_w, double *out_h) {
    if (out_w == NULL || out_h == NULL) return;
    *out_w = 0.0;
    *out_h = 0.0;
    if (iw == 0u || ih == 0u || box_w <= 0.0 || box_h <= 0.0) return;
    double sx = box_w / (double)iw;
    double sy = box_h / (double)ih;
    double s = (sx < sy) ? sx : sy;
    *out_w = (double)iw * s;
    *out_h = (double)ih * s;
}

/* Premultiplies straight-alpha BGRA in place: c' = round(c * a / 255). */
static void premultiply(uint8_t *data, size_t pixels) {
    for (size_t i = 0; i < pixels; ++i) {
        uint8_t *p = data + i * 4u;
        unsigned a = p[3];
        if (a == 255u) continue;
        if (a == 0u) { p[0] = p[1] = p[2] = 0u; continue; }
        p[0] = (uint8_t)((p[0] * a + 127u) / 255u);
        p[1] = (uint8_t)((p[1] * a + 127u) / 255u);
        p[2] = (uint8_t)((p[2] * a + 127u) / 255u);
    }
}

img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out) {
    if (bytes == NULL || out == NULL) return IMG_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);

    if (img_sniff(bytes, len) != IMG_FMT_PNG) return IMG_ERR_FORMAT;

    png_image image;
    memset(&image, 0, sizeof image);
    image.version = PNG_IMAGE_VERSION;

    if (png_image_begin_read_from_memory(&image, bytes, len) == 0) {
        png_image_free(&image);
        return IMG_ERR_DECODE;
    }

    /* Bound dimensions BEFORE the full decode (anti decompression bomb). */
    if (!img_dimensions_ok(image.width, image.height)) {
        png_image_free(&image);
        return IMG_ERR_DIMENSIONS;
    }

    image.format = PNG_FORMAT_BGRA; /* memory bytes B,G,R,A; straight alpha */

    uint32_t w = image.width;
    uint32_t h = image.height;
    size_t nbytes = (size_t)w * (size_t)h * 4u; /* bounded: w*h <= IMG_MAX_PIXELS */
    uint8_t *buf = (uint8_t *)malloc(nbytes);
    if (buf == NULL) {
        png_image_free(&image);
        return IMG_ERR_OOM;
    }

    /* row_stride 0 => natural width*channels; background NULL (alpha is kept). */
    if (png_image_finish_read(&image, NULL, buf, 0, NULL) == 0) {
        png_image_free(&image);
        free(buf);
        return IMG_ERR_DECODE;
    }
    png_image_free(&image);

    premultiply(buf, (size_t)w * (size_t)h);

    out->width = w;
    out->height = h;
    out->stride = w * 4u;
    out->data = buf;
    return IMG_OK;
}

/* libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG
 * fails closed (IMG_ERR_DECODE) without tearing the worker down. */
struct jpeg_err_ctx {
    struct jpeg_error_mgr pub;
    jmp_buf jb;
};

static void jpeg_error_longjmp(j_common_ptr cinfo) {
    struct jpeg_err_ctx *e = (struct jpeg_err_ctx *)cinfo->err;
    longjmp(e->jb, 1);
}

/* Swallow libjpeg's warning/trace text; the worker has no business writing to stderr. */
static void jpeg_silence(j_common_ptr cinfo) { (void)cinfo; }

img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out) {
    if (bytes == NULL || out == NULL) return IMG_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (img_sniff(bytes, len) != IMG_FMT_JPEG) return IMG_ERR_FORMAT;

    struct jpeg_decompress_struct cinfo;
    struct jpeg_err_ctx jerr;
    /* Modified after setjmp and read on the error path -> must be volatile (C11
     * 7.13.2.1): otherwise their values after longjmp would be indeterminate. */
    volatile img_status status = IMG_ERR_DECODE;
    uint8_t *volatile buf = NULL;     /* output BGRA bitmap */
    uint8_t *volatile rowbuf = NULL;  /* one decoded RGB scanline */

    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = jpeg_error_longjmp;
    jerr.pub.output_message = jpeg_silence;

    if (setjmp(jerr.jb)) {
        /* libjpeg signalled a fatal error (or we jumped here on a logic failure). */
        jpeg_destroy_decompress(&cinfo);
        free(rowbuf);
        free(buf);
        return status;  /* *out is still zeroed: data is only published on success */
    }

    jpeg_create_decompress(&cinfo);
    jpeg_mem_src(&cinfo, bytes, (unsigned long)len);

    if (jpeg_read_header(&cinfo, TRUE) != JPEG_HEADER_OK) longjmp(jerr.jb, 1);

    /* Bound declared dimensions BEFORE the full decode (anti decompression bomb). */
    if (!img_dimensions_ok(cinfo.image_width, cinfo.image_height)) {
        status = IMG_ERR_DIMENSIONS;
        longjmp(jerr.jb, 1);
    }

    /* Force a single known output: 8-bit RGB (present in every libjpeg, no turbo-only
     * extension). CMYK/YCCK sources cannot convert to RGB and error out here -> reject. */
    cinfo.out_color_space = JCS_RGB;
    jpeg_start_decompress(&cinfo);

    if (cinfo.output_components != 3) longjmp(jerr.jb, 1);

    uint32_t w = cinfo.output_width;
    uint32_t h = cinfo.output_height;
    if (!img_dimensions_ok(w, h)) {  /* defensive: should equal the header dims */
        status = IMG_ERR_DIMENSIONS;
        longjmp(jerr.jb, 1);
    }

    buf = (uint8_t *)malloc((size_t)w * (size_t)h * 4u);
    rowbuf = (uint8_t *)malloc((size_t)w * 3u);
    if (buf == NULL || rowbuf == NULL) { status = IMG_ERR_OOM; longjmp(jerr.jb, 1); }

    while (cinfo.output_scanline < h) {
        JSAMPROW rows[1];
        rows[0] = (JSAMPROW)rowbuf;
        if (jpeg_read_scanlines(&cinfo, rows, 1) != 1) longjmp(jerr.jb, 1);
        uint8_t *dst = buf + (size_t)(cinfo.output_scanline - 1u) * (size_t)w * 4u;
        for (uint32_t x = 0; x < w; ++x) {
            uint8_t r = rowbuf[x * 3u + 0u];
            uint8_t g = rowbuf[x * 3u + 1u];
            uint8_t b = rowbuf[x * 3u + 2u];
            dst[x * 4u + 0u] = b;     /* Cairo ARGB32 little-endian: B,G,R,A */
            dst[x * 4u + 1u] = g;
            dst[x * 4u + 2u] = r;
            dst[x * 4u + 3u] = 0xffu; /* opaque; premultiply is a no-op */
        }
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    free(rowbuf);

    out->width = w;
    out->height = h;
    out->stride = w * 4u;
    out->data = buf;  /* ownership transfers to *out */
    return IMG_OK;
}

img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out) {
    if (bytes == NULL || out == NULL) return IMG_ERR_NULL_ARG;
    switch (img_sniff(bytes, len)) {
        case IMG_FMT_PNG:  return img_decode_png(bytes, len, out);
        case IMG_FMT_JPEG: return img_decode_jpeg(bytes, len, out);
        default:
            memset(out, 0, sizeof *out);
            return IMG_ERR_FORMAT;
    }
}

void img_pixels_free(img_pixels *p) {
    if (p == NULL) return;
    free(p->data);
    p->data = NULL;
    p->width = 0;
    p->height = 0;
    p->stride = 0;
}

const char *img_format_name(img_format f) {
    switch (f) {
        case IMG_FMT_PNG: return "png";
        case IMG_FMT_JPEG: return "jpeg";
        case IMG_FMT_UNKNOWN: return "unknown";
        default: return "unknown";
    }
}
