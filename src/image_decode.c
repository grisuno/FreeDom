/*
 * image_decode — implementation: PNG / JPEG / GIF / WebP -> Cairo-native ARGB32.
 *
 * PNG uses libpng's simplified read API (no setjmp; success is a return value).
 * JPEG uses libjpeg with an in-memory source and a longjmp error manager so a
 * malformed stream fails closed instead of calling exit(). GIF uses an own pure-C
 * bounded LZW decoder (no giflib). WebP uses libwebp's WebPDecodeBGRA in-memory
 * API. Output is tightly packed BGRA (Cairo's native CAIRO_FORMAT_ARGB32 byte
 * order); PNG is premultiplied, JPEG is fully opaque (alpha 0xFF). No filesystem,
 * no network: this is the piece that runs inside the confined tab worker. See
 * spec/image_decode.md.
 */

#include "image_decode.h"

#include <setjmp.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>
#include <jpeglib.h>
#include <webp/decode.h>

/* The 8-byte PNG signature, the 3-byte JPEG SOI+marker prefix, and the
 * 12-byte RIFF....WEBP signature (the 4-byte size field at offset 4-7
 * varies per image, so only the first 4 and last 4 bytes are fixed). */
static const uint8_t PNG_MAGIC[8] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };
static const uint8_t JPEG_MAGIC[3] = { 0xff, 0xd8, 0xff };
static const uint8_t WEBP_MAGIC[4] = { 'W', 'E', 'B', 'P' };

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
    if (len >= 6u && memcmp(bytes, "GIF8", 4) == 0 &&
        (bytes[4] == '7' || bytes[4] == '9') && bytes[5] == 'a')
        return IMG_FMT_GIF;
    /* WebP: RIFF + 4-byte size + WEBP. */
    if (len >= 12u && memcmp(bytes, "RIFF", 4) == 0 &&
        memcmp(bytes + 8, WEBP_MAGIC, 4) == 0)
        return IMG_FMT_WEBP;
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

/* --- GIF: own bounded pure-C decoder (spec/image_decode.md §0.2) ------------
 * First frame only. No dependency: LZW is ~100 lines and giflib would be one
 * more hostile-input parser to audit. Every read is bounds-checked; the LZW
 * expansion is capped by the frame area, so a corrupt stream can neither hang
 * nor write out of bounds. */

#define GIF_LZW_MAX_CODES 4096u

typedef struct gif_reader {
    const uint8_t *p;
    size_t len, pos;
} gif_reader;

static int gr_u8(gif_reader *r, uint8_t *out) {
    if (r->pos >= r->len) return 0;
    *out = r->p[r->pos++];
    return 1;
}

static int gr_u16le(gif_reader *r, uint16_t *out) {
    if (r->pos + 2u > r->len) return 0;
    *out = (uint16_t)(r->p[r->pos] | ((uint16_t)r->p[r->pos + 1] << 8));
    r->pos += 2u;
    return 1;
}

static int gr_skip(gif_reader *r, size_t n) {
    if (r->pos + n > r->len) return 0;
    r->pos += n;
    return 1;
}

/* Skips a chain of data sub-blocks up to and including the 0 terminator. */
static int gr_skip_subblocks(gif_reader *r) {
    uint8_t n;
    for (;;) {
        if (!gr_u8(r, &n)) return 0;
        if (n == 0u) return 1;
        if (!gr_skip(r, n)) return 0;
    }
}

/* Bit reader over the LZW data sub-block chain, LSB-first. */
typedef struct gif_bits {
    gif_reader *r;
    uint32_t    acc;
    unsigned    nbits;
    uint8_t     block_left;   /* bytes left in the current sub-block */
    int         ended;        /* saw the 0-length terminator */
} gif_bits;

static int gb_next_code(gif_bits *b, unsigned width, unsigned *out) {
    while (b->nbits < width) {
        if (b->block_left == 0u) {
            uint8_t n;
            if (b->ended || !gr_u8(b->r, &n)) return 0;
            if (n == 0u) { b->ended = 1; return 0; }
            b->block_left = n;
        }
        uint8_t byte;
        if (!gr_u8(b->r, &byte)) return 0;
        b->block_left--;
        b->acc |= (uint32_t)byte << b->nbits;
        b->nbits += 8u;
    }
    *out = b->acc & ((1u << width) - 1u);
    b->acc >>= width;
    b->nbits -= width;
    return 1;
}

/* Visual row of interlaced-frame row `r` (4-pass GIF interlace). */
static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh) {
    uint32_t pass1 = (fh + 7u) / 8u;          /* rows 0, 8, 16, ... */
    uint32_t pass2 = (fh + 3u) / 8u;          /* rows 4, 12, ... */
    uint32_t pass3 = (fh + 1u) / 4u;          /* rows 2, 6, ... */
    if (r < pass1) return r * 8u;
    r -= pass1;
    if (r < pass2) return r * 8u + 4u;
    r -= pass2;
    if (r < pass3) return r * 4u + 2u;
    r -= pass3;
    return r * 2u + 1u;
}

/* Writes one palette pixel into the canvas at frame-relative index i (clipped to
 * the canvas; transparent index -> 0x00000000, already premultiplied). */
static void gif_put_pixel(uint32_t *canvas, uint32_t cw, uint32_t ch,
                          uint32_t fx0, uint32_t fy0, uint32_t fw, uint32_t fh,
                          int interlaced, uint32_t i,
                          const uint8_t *pal, unsigned pal_n, unsigned idx,
                          int transparent_idx, int *bad_index) {
    if (idx >= pal_n) { *bad_index = 1; return; }
    uint32_t fx = i % fw, fy = i / fw;
    if (interlaced) fy = gif_deinterlace_row(fy, fh);
    uint32_t x = fx0 + fx, y = fy0 + fy;
    if (x >= cw || y >= ch) return;
    uint32_t px;
    if ((int)idx == transparent_idx) {
        px = 0u;
    } else {
        const uint8_t *c = pal + idx * 3u;
        px = 0xff000000u | ((uint32_t)c[0] << 16) | ((uint32_t)c[1] << 8) | c[2];
    }
    canvas[(size_t)y * cw + x] = px;
}

img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out) {
    if (bytes == NULL || out == NULL) return IMG_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (img_sniff(bytes, len) != IMG_FMT_GIF) return IMG_ERR_FORMAT;

    gif_reader r = { bytes, len, 6u };   /* past "GIF8?a" */
    uint16_t cw16, ch16;
    uint8_t lsd_flags, bg, aspect;
    if (!gr_u16le(&r, &cw16) || !gr_u16le(&r, &ch16) ||
        !gr_u8(&r, &lsd_flags) || !gr_u8(&r, &bg) || !gr_u8(&r, &aspect))
        return IMG_ERR_TRUNCATED;
    uint32_t cw = cw16, ch = ch16;
    if (!img_dimensions_ok(cw, ch)) return IMG_ERR_DIMENSIONS;

    const uint8_t *gct = NULL;
    unsigned gct_n = 0;
    if (lsd_flags & 0x80u) {
        gct_n = 1u << ((lsd_flags & 0x07u) + 1u);
        if (r.pos + (size_t)gct_n * 3u > r.len) return IMG_ERR_TRUNCATED;
        gct = bytes + r.pos;
        r.pos += (size_t)gct_n * 3u;
    }

    int transparent_idx = -1;
    for (;;) {
        uint8_t block;
        if (!gr_u8(&r, &block)) return IMG_ERR_TRUNCATED;
        if (block == 0x3bu) return IMG_ERR_DECODE;   /* trailer before any image */
        if (block == 0x21u) {
            uint8_t label;
            if (!gr_u8(&r, &label)) return IMG_ERR_TRUNCATED;
            if (label == 0xf9u) {
                /* Graphic Control Extension: size(4) flags delay(2) tidx term */
                uint8_t sz, flags, tidx;
                if (!gr_u8(&r, &sz) || sz != 4u) return IMG_ERR_DECODE;
                if (!gr_u8(&r, &flags) || !gr_skip(&r, 2u) || !gr_u8(&r, &tidx))
                    return IMG_ERR_TRUNCATED;
                transparent_idx = (flags & 0x01u) ? (int)tidx : -1;
                if (!gr_skip_subblocks(&r)) return IMG_ERR_TRUNCATED;
            } else {
                if (!gr_skip_subblocks(&r)) return IMG_ERR_TRUNCATED;
            }
            continue;
        }
        if (block != 0x2cu) return IMG_ERR_DECODE;   /* not an Image Descriptor */
        break;
    }

    uint16_t fx16, fy16, fw16, fh16;
    uint8_t id_flags;
    if (!gr_u16le(&r, &fx16) || !gr_u16le(&r, &fy16) ||
        !gr_u16le(&r, &fw16) || !gr_u16le(&r, &fh16) || !gr_u8(&r, &id_flags))
        return IMG_ERR_TRUNCATED;
    uint32_t fw = fw16, fh = fh16;
    if (!img_dimensions_ok(fw, fh)) return IMG_ERR_DIMENSIONS;
    int interlaced = (id_flags & 0x40u) != 0;

    const uint8_t *pal = gct;
    unsigned pal_n = gct_n;
    if (id_flags & 0x80u) {   /* local color table overrides the global one */
        pal_n = 1u << ((id_flags & 0x07u) + 1u);
        if (r.pos + (size_t)pal_n * 3u > r.len) return IMG_ERR_TRUNCATED;
        pal = bytes + r.pos;
        r.pos += (size_t)pal_n * 3u;
    }
    if (pal == NULL || pal_n == 0u) return IMG_ERR_DECODE;

    uint8_t root;
    if (!gr_u8(&r, &root)) return IMG_ERR_TRUNCATED;
    if (root < 2u || root > 11u) return IMG_ERR_DECODE;

    /* canvas starts fully transparent; unfilled pixels stay that way */
    size_t npix = (size_t)cw * ch;
    uint32_t *canvas = (uint32_t *)calloc(npix, 4u);
    if (canvas == NULL) return IMG_ERR_OOM;

    /* LZW dictionary: prefix chain + last byte per code. */
    uint16_t *prefix = (uint16_t *)malloc(GIF_LZW_MAX_CODES * sizeof *prefix);
    uint8_t  *suffix = (uint8_t *)malloc(GIF_LZW_MAX_CODES);
    uint8_t  *stack  = (uint8_t *)malloc(GIF_LZW_MAX_CODES);
    if (prefix == NULL || suffix == NULL || stack == NULL) {
        free(prefix); free(suffix); free(stack); free(canvas);
        return IMG_ERR_OOM;
    }

    unsigned clear = 1u << root, eoi = clear + 1u;
    unsigned next = eoi + 1u, width = root + 1u;
    unsigned prev = GIF_LZW_MAX_CODES;   /* sentinel: no previous code */
    uint32_t emitted = 0;
    uint32_t frame_pixels = fw * fh;
    int bad_index = 0;
    img_status st = IMG_OK;
    gif_bits gb = { &r, 0u, 0u, 0u, 0 };

    for (unsigned c = 0; c < clear; ++c) { prefix[c] = 0xffffu; suffix[c] = (uint8_t)c; }

    while (emitted < frame_pixels) {
        unsigned code;
        if (!gb_next_code(&gb, width, &code)) { st = IMG_ERR_TRUNCATED; break; }
        if (code == clear) {
            next = eoi + 1u;
            width = root + 1u;
            prev = GIF_LZW_MAX_CODES;
            continue;
        }
        if (code == eoi) break;
        if (code > next || code >= GIF_LZW_MAX_CODES ||
            (code == next && prev == GIF_LZW_MAX_CODES)) {
            st = IMG_ERR_DECODE;
            break;
        }

        /* Expand the code's string (KwKwK case: prev + first(prev)) onto the
         * stack; bounded by the dictionary size, so this can never run away. */
        unsigned sp = 0;
        unsigned cur = code;
        uint8_t first;
        if (code == next) {
            /* not yet defined: prev's string + prev's first byte */
            cur = prev;
        }
        while (cur >= clear) {
            if (sp >= GIF_LZW_MAX_CODES) { st = IMG_ERR_DECODE; break; }
            stack[sp++] = suffix[cur];
            cur = prefix[cur];
        }
        if (st != IMG_OK) break;
        first = suffix[cur];

        /* Emit: root byte first, then the stacked bytes in reverse; the KwKwK
         * case (code == next) appends first(prev) once more after the chain. */
        gif_put_pixel(canvas, cw, ch, fx16, fy16, fw, fh, interlaced, emitted++,
                      pal, pal_n, first, transparent_idx, &bad_index);
        while (sp > 0 && emitted < frame_pixels) {
            gif_put_pixel(canvas, cw, ch, fx16, fy16, fw, fh, interlaced, emitted++,
                          pal, pal_n, stack[--sp], transparent_idx, &bad_index);
        }
        if (code == next && emitted < frame_pixels) {
            gif_put_pixel(canvas, cw, ch, fx16, fy16, fw, fh, interlaced, emitted++,
                          pal, pal_n, first, transparent_idx, &bad_index);
        }
        if (bad_index) { st = IMG_ERR_DECODE; break; }

        if (prev != GIF_LZW_MAX_CODES && next < GIF_LZW_MAX_CODES) {
            prefix[next] = (uint16_t)prev;
            suffix[next] = first;
            ++next;
            if (next == (1u << width) && width < 12u) ++width;
        }
        prev = code;
    }

    free(prefix);
    free(suffix);
    free(stack);
    if (st != IMG_OK) {
        free(canvas);
        return st;
    }
    out->width = cw;
    out->height = ch;
    out->stride = cw * 4u;
    out->data = (uint8_t *)canvas;
    return IMG_OK;
}

img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out) {
    if (bytes == NULL || out == NULL) return IMG_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (img_sniff(bytes, len) != IMG_FMT_WEBP) return IMG_ERR_FORMAT;

    /* WebPGetInfo gives dimensions without full decode (anti-bomb). */
    int iw = 0, ih = 0;
    if (!WebPGetInfo(bytes, len, &iw, &ih)) return IMG_ERR_DECODE;
    uint32_t w = (uint32_t)iw, h = (uint32_t)ih;
    if (!img_dimensions_ok(w, h)) return IMG_ERR_DIMENSIONS;

    /* Decode to BGRA (native Cairo byte order: B,G,R,A in memory). libwebp
     * returns straight alpha; premultiply afterwards. */
    size_t stride = (size_t)w * 4u;
    size_t nbytes = stride * (size_t)h;
    uint8_t *buf = (uint8_t *)malloc(nbytes);
    if (buf == NULL) return IMG_ERR_OOM;

    uint8_t *result = WebPDecodeBGRAInto(bytes, len, buf, nbytes, (int)stride);
    if (result == NULL) {
        free(buf);
        return IMG_ERR_DECODE;
    }

    premultiply(buf, (size_t)w * (size_t)h);

    out->width = w;
    out->height = h;
    out->stride = (uint32_t)stride;
    out->data = buf;
    return IMG_OK;
}

img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out) {
    if (bytes == NULL || out == NULL) return IMG_ERR_NULL_ARG;
    switch (img_sniff(bytes, len)) {
        case IMG_FMT_PNG:  return img_decode_png(bytes, len, out);
        case IMG_FMT_JPEG: return img_decode_jpeg(bytes, len, out);
        case IMG_FMT_GIF:  return img_decode_gif(bytes, len, out);
        case IMG_FMT_WEBP: return img_decode_webp(bytes, len, out);
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
        case IMG_FMT_GIF: return "gif";
        case IMG_FMT_WEBP: return "webp";
        case IMG_FMT_UNKNOWN: return "unknown";
        default: return "unknown";
    }
}
