/*
 * text_shape (tsh_) — HarfBuzz shaping for the trusted-side painter.
 *
 * Resolves a LOCAL font per generic family bucket (fontconfig), parses it with
 * FreeType (for Cairo glyph rendering) and HarfBuzz (for shaping) from the same
 * in-memory font program so glyph ids agree, then shapes hostile UTF-8 into
 * cairo_glyph_t positions. Trusted-side only; never runs in the confined worker.
 * Fail-closed: any backend/input problem returns a status the painter handles by
 * falling back to the Cairo toy API. See spec/text_shape.md.
 */

#define _POSIX_C_SOURCE 200809L

#include "text_shape.h"
#include "css.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cairo/cairo-ft.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <harfbuzz/hb.h>
#include <fontconfig/fontconfig.h>

/* A single font file should never exceed this (CJK faces are the large case). */
#define TSH_MAX_FONT_BYTES ((long)(128 * 1024 * 1024))

/* One resolved face per (family, bold, italic). family is a CSS_FF_* bucket
 * (0..CSS_FF_FANTASY); idx = family*4 + bold*2 + italic. */
#define TSH_CACHE_SLOTS ((CSS_FF_FANTASY + 1) * 4)

typedef struct tsh_entry {
    int                loaded;  /* 0 untried, 1 ok, -1 failed (don't retry) */
    unsigned char     *bytes;   /* font file contents (owned; FT + hb reference it) */
    long               nbytes;
    FT_Face            ftface;
    cairo_font_face_t *cface;
    hb_blob_t         *blob;
    hb_face_t         *hbface;
    hb_font_t         *hbfont;
} tsh_entry;

static FT_Library   g_ft;
static int          g_init_attempted;
static int          g_backend_ok;
static hb_buffer_t *g_buf;
static tsh_entry    g_cache[TSH_CACHE_SLOTS];

/* Static scratch for the measure/draw convenience wrappers (single-threaded). */
static cairo_glyph_t g_scratch[TSH_MAX_GLYPHS];

static const char *generic_name(int family) {
    switch (family) {
        case CSS_FF_SERIF:   return "serif";
        case CSS_FF_MONO:    return "monospace";
        case CSS_FF_CURSIVE: return "cursive";
        case CSS_FF_FANTASY: return "fantasy";
        default:             return "sans-serif"; /* CSS_FF_SANS / UNSET */
    }
}

static int backend_init(void) {
    if (g_init_attempted) return g_backend_ok;
    g_init_attempted = 1;
    if (FT_Init_FreeType(&g_ft) != 0) { g_backend_ok = 0; return 0; }
    /* FcInit is idempotent; FcFontMatch(NULL,...) inits implicitly anyway. */
    FcInit();
    g_buf = hb_buffer_create();
    if (g_buf == NULL || !hb_buffer_allocation_successful(g_buf)) {
        if (g_buf != NULL) { hb_buffer_destroy(g_buf); g_buf = NULL; }
        FT_Done_FreeType(g_ft);
        g_backend_ok = 0;
        return 0;
    }
    g_backend_ok = 1;
    return 1;
}

static unsigned char *read_font_file(const char *path, long *out_n) {
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) return NULL;
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return NULL; }
    long sz = ftell(fp);
    if (sz <= 0 || sz > TSH_MAX_FONT_BYTES) { fclose(fp); return NULL; }
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return NULL; }
    unsigned char *b = (unsigned char *)malloc((size_t)sz);
    if (b == NULL) { fclose(fp); return NULL; }
    size_t rd = fread(b, 1, (size_t)sz, fp);
    fclose(fp);
    if (rd != (size_t)sz) { free(b); return NULL; }
    *out_n = sz;
    return b;
}

static int load_entry(tsh_entry *e, int family, int bold, int italic) {
    FcPattern *pat = FcNameParse((const FcChar8 *)generic_name(family));
    if (pat == NULL) return 0;
    FcPatternAddInteger(pat, FC_WEIGHT, bold ? FC_WEIGHT_BOLD : FC_WEIGHT_NORMAL);
    FcPatternAddInteger(pat, FC_SLANT, italic ? FC_SLANT_ITALIC : FC_SLANT_ROMAN);
    FcConfigSubstitute(NULL, pat, FcMatchPattern);
    FcDefaultSubstitute(pat);
    FcResult res;
    FcPattern *match = FcFontMatch(NULL, pat, &res);
    FcPatternDestroy(pat);
    if (match == NULL) return 0;

    FcChar8 *file = NULL;
    if (FcPatternGetString(match, FC_FILE, 0, &file) != FcResultMatch || file == NULL) {
        FcPatternDestroy(match);
        return 0;
    }
    int index = 0;
    FcPatternGetInteger(match, FC_INDEX, 0, &index);
    long nbytes = 0;
    unsigned char *bytes = read_font_file((const char *)file, &nbytes);
    FcPatternDestroy(match);
    if (bytes == NULL) return 0;

    FT_Face ft = NULL;
    if (FT_New_Memory_Face(g_ft, bytes, nbytes, index, &ft) != 0) {
        free(bytes);
        return 0;
    }
    cairo_font_face_t *cf = cairo_ft_font_face_create_for_ft_face(ft, 0);
    if (cf == NULL || cairo_font_face_status(cf) != CAIRO_STATUS_SUCCESS) {
        if (cf != NULL) cairo_font_face_destroy(cf);
        FT_Done_Face(ft);
        free(bytes);
        return 0;
    }
    hb_blob_t *blob = hb_blob_create((const char *)bytes, (unsigned)nbytes,
                                     HB_MEMORY_MODE_READONLY, NULL, NULL);
    hb_face_t *hf = hb_face_create(blob, (unsigned)index);
    hb_font_t *hfont = hb_font_create(hf);
    if (hfont == NULL || hf == NULL) {
        if (hfont != NULL) hb_font_destroy(hfont);
        if (hf != NULL) hb_face_destroy(hf);
        hb_blob_destroy(blob);
        cairo_font_face_destroy(cf);
        FT_Done_Face(ft);
        free(bytes);
        return 0;
    }

    e->bytes = bytes; e->nbytes = nbytes; e->ftface = ft; e->cface = cf;
    e->blob = blob; e->hbface = hf; e->hbfont = hfont;
    return 1;
}

static tsh_entry *get_entry(int family, int bold, int italic) {
    if (!backend_init()) return NULL;
    int fam = (family >= 0 && family <= CSS_FF_FANTASY) ? family : CSS_FF_SANS;
    int idx = fam * 4 + (bold ? 2 : 0) + (italic ? 1 : 0);
    tsh_entry *e = &g_cache[idx];
    if (e->loaded == 1) return e;
    if (e->loaded == -1) return NULL;
    if (load_entry(e, fam, bold, italic)) { e->loaded = 1; return e; }
    e->loaded = -1;
    return NULL;
}

int tsh_ready(void) {
    /* Backend usable iff the default (sans) face resolves. */
    return get_entry(CSS_FF_SANS, 0, 0) != NULL;
}

tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                     cairo_glyph_t *out, size_t cap, size_t *out_n, double *out_adv) {
    if (f == NULL || out == NULL || out_n == NULL || out_adv == NULL) return TSH_ERR_INPUT;
    if (cap == 0) return TSH_ERR_INPUT;
    if (text == NULL && len != 0) return TSH_ERR_INPUT;
    /* px must be finite and positive; px>1e9 catches +inf, !(px>0) catches NaN/<=0. */
    if (!(px > 0.0) || px > 1.0e9) return TSH_ERR_INPUT;
    if (len > (size_t)TSH_MAX_TEXT) return TSH_ERR_INPUT;

    *out_n = 0;
    *out_adv = 0.0;
    if (len == 0) return TSH_OK;

    tsh_entry *e = get_entry(f->family, f->bold, f->italic);
    if (e == NULL) return TSH_ERR_UNAVAIL;

    int scale = (int)(px * 64.0 + 0.5);
    if (scale < 1) scale = 1;
    hb_font_set_scale(e->hbfont, scale, scale);

    hb_buffer_reset(g_buf);
    hb_buffer_add_utf8(g_buf, text, (int)len, 0, (int)len);
    hb_buffer_guess_segment_properties(g_buf);
    hb_shape(e->hbfont, g_buf, NULL, 0);

    unsigned gn = hb_buffer_get_length(g_buf);
    if ((size_t)gn > cap || gn > TSH_MAX_GLYPHS) return TSH_ERR_OVERFLOW;

    const hb_glyph_info_t     *info = hb_buffer_get_glyph_infos(g_buf, NULL);
    const hb_glyph_position_t  *pos  = hb_buffer_get_glyph_positions(g_buf, NULL);
    if ((gn != 0) && (info == NULL || pos == NULL)) return TSH_ERR_UNAVAIL;

    double penx = 0.0, peny = 0.0;
    for (unsigned i = 0; i < gn; ++i) {
        out[i].index = info[i].codepoint;            /* glyph id (matches cface) */
        out[i].x = penx + (double)pos[i].x_offset / 64.0;
        out[i].y = peny - (double)pos[i].y_offset / 64.0;
        penx += (double)pos[i].x_advance / 64.0;
        peny -= (double)pos[i].y_advance / 64.0;
    }
    *out_n = gn;
    *out_adv = penx;
    return TSH_OK;
}

double tsh_measure(const tsh_font *f, double px, const char *text, size_t len) {
    size_t n = 0;
    double adv = 0.0;
    tsh_status st = tsh_shape(f, px, text, len, g_scratch, TSH_MAX_GLYPHS, &n, &adv);
    return (st == TSH_OK) ? adv : -1.0;
}

tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, double baseline, const char *text, size_t len) {
    if (cr == NULL) return TSH_ERR_INPUT;
    size_t n = 0;
    double adv = 0.0;
    tsh_status st = tsh_shape(f, px, text, len, g_scratch, TSH_MAX_GLYPHS, &n, &adv);
    if (st != TSH_OK) return st;
    if (n == 0) return TSH_OK;

    tsh_entry *e = get_entry(f->family, f->bold, f->italic);
    if (e == NULL) return TSH_ERR_UNAVAIL;

    cairo_set_font_face(cr, e->cface);
    cairo_set_font_size(cr, px);
    for (size_t i = 0; i < n; ++i) {
        g_scratch[i].x += x;
        g_scratch[i].y += baseline;
    }
    cairo_show_glyphs(cr, g_scratch, (int)n);
    return TSH_OK;
}

void tsh_shutdown(void) {
    for (int i = 0; i < TSH_CACHE_SLOTS; ++i) {
        tsh_entry *e = &g_cache[i];
        if (e->loaded != 1) { e->loaded = 0; continue; }
        if (e->hbfont != NULL) hb_font_destroy(e->hbfont);
        if (e->hbface != NULL) hb_face_destroy(e->hbface);
        if (e->blob != NULL) hb_blob_destroy(e->blob);
        if (e->cface != NULL) cairo_font_face_destroy(e->cface);
        if (e->ftface != NULL) FT_Done_Face(e->ftface);
        free(e->bytes);
        memset(e, 0, sizeof *e);
    }
    if (g_buf != NULL) { hb_buffer_destroy(g_buf); g_buf = NULL; }
    if (g_backend_ok) FT_Done_FreeType(g_ft);
    g_backend_ok = 0;
    g_init_attempted = 0;
}
