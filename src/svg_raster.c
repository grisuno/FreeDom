/* svg_raster -- SVG served as an image, rasterized inside the confined worker.
 * spec/svg_raster.md. */

#include "svg_raster.h"

#include <cairo.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "svg_paint.h"
#include "svg_render.h"

static int sr_ws(uint8_t c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'; }

/* Skips past the first occurrence of the NUL-terminated `end` in b[i, n); returns
 * the index just after it, or n when it never closes. */
static size_t sr_skip_past(const uint8_t *b, size_t i, size_t n, const char *end) {
    size_t el = strlen(end);
    for (; i + el <= n; ++i)
        if (memcmp(b + i, end, el) == 0) return i + el;
    return n;
}

int sr_sniff(const uint8_t *bytes, size_t len) {
    if (bytes == NULL) return 0;
    size_t n = (len < SR_SNIFF_MAX) ? len : SR_SNIFF_MAX;
    size_t i = 0;
    if (n >= 3 && bytes[0] == 0xEF && bytes[1] == 0xBB && bytes[2] == 0xBF) i = 3;
    for (;;) {
        while (i < n && sr_ws(bytes[i])) ++i;
        if (i + 4 > n || bytes[i] != '<') return 0;
        if (bytes[i + 1] == '?') { i = sr_skip_past(bytes, i + 2, n, "?>"); continue; }
        if (i + 4 <= n && memcmp(bytes + i, "<!--", 4) == 0) {
            i = sr_skip_past(bytes, i + 4, n, "-->");
            continue;
        }
        if (bytes[i + 1] == '!') { i = sr_skip_past(bytes, i + 2, n, ">"); continue; }
        if (i + 5 > n) return 0;
        for (int k = 0; k < 3; ++k) {
            uint8_t c = bytes[i + 1 + k];
            if (c >= 'A' && c <= 'Z') c = (uint8_t)(c + 32);
            if (c != (uint8_t)"svg"[k]) return 0;
        }
        uint8_t t = bytes[i + 4];
        return sr_ws(t) || t == '>' || t == '/';
    }
}

img_status sr_rasterize(const uint8_t *bytes, size_t len, img_pixels *out) {
    if (out == NULL) return IMG_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (bytes == NULL) return IMG_ERR_NULL_ARG;
    if (!sr_sniff(bytes, len)) return IMG_ERR_FORMAT;
    if (len > SV_MAX_INPUT) return IMG_ERR_DIMENSIONS;

    sv_image *img = (sv_image *)calloc(1, sizeof *img);
    if (img == NULL) return IMG_ERR_OOM;
    if (sv_parse((const char *)bytes, len, img) != SV_OK) { free(img); return IMG_ERR_DECODE; }

    double w = img->width, h = img->height;
    if (!(w > 0.0) || !(h > 0.0)) { w = SV_DEFAULT_W; h = SV_DEFAULT_H; }
    double longest = (w > h) ? w : h;
    if (longest > (double)SR_MAX_DIM) { w *= (double)SR_MAX_DIM / longest; h *= (double)SR_MAX_DIM / longest; }
    /* The CSS size is rounded to whole px FIRST, so width/scale is exact downstream. */
    uint32_t cw = (uint32_t)ceil(w), ch = (uint32_t)ceil(h);
    if (cw == 0) cw = 1;
    if (ch == 0) ch = 1;
    uint32_t k = 1;
    while (k < IMG_MAX_SCALE && (cw > ch ? cw : ch) * k < SR_MIN_RASTER) ++k;
    uint32_t pw = cw * k, ph = ch * k;
    if (pw == 0) pw = 1;
    if (ph == 0) ph = 1;
    if (!img_dimensions_ok(pw, ph)) { free(img); return IMG_ERR_DIMENSIONS; }

    uint32_t stride = pw * 4u;
    uint8_t *data = (uint8_t *)calloc((size_t)ph, (size_t)stride);
    if (data == NULL) { free(img); return IMG_ERR_OOM; }
    cairo_surface_t *sf = cairo_image_surface_create_for_data(data, CAIRO_FORMAT_ARGB32,
                                                              (int)pw, (int)ph, (int)stride);
    if (cairo_surface_status(sf) != CAIRO_STATUS_SUCCESS) {
        cairo_surface_destroy(sf);
        free(data);
        free(img);
        return IMG_ERR_DECODE;
    }
    cairo_t *cr = cairo_create(sf);
    svp_draw_ex(cr, img, 0.0, 0.0, (double)pw, (double)ph, 0x000000, 0);
    cairo_destroy(cr);
    cairo_surface_flush(sf);
    cairo_surface_destroy(sf);
    free(img);

    out->width = pw;
    out->height = ph;
    out->stride = stride;
    out->data = data;
    out->scale = k;
    return IMG_OK;
}
