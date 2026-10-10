/*
 * text_shape (tsh_) — HarfBuzz text shaping for the trusted-side painter.
 *
 * Replaces the Cairo "toy" font API (one glyph per byte, no script awareness)
 * with HarfBuzz shaping + cairo_show_glyphs: ligatures, GPOS kerning, contextual
 * forms and correct intra-run direction for complex scripts.
 *
 * TRUST: this is a TRUSTED-SIDE rendering helper. It is linked into and called
 * ONLY by the painter; it is NEVER called from the confined worker (tab/renderer
 * child), which produces inert display lists and never touches a font. The shaped
 * TEXT is hostile remote content (sanitised UTF-8) and is fuzzed (make fuzz-tsh);
 * the FONTS are local system files (fontconfig + FreeType), exactly the files the
 * toy API already opened. No network, no persistence. See spec/text_shape.md.
 *
 * Not thread-safe: a single static scratch buffer and a global face cache serve
 * the single-threaded painter.
 */
#ifndef FREEDOM_TEXT_SHAPE_H
#define FREEDOM_TEXT_SHAPE_H

#include <cairo/cairo.h>
#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is C only"
#endif

/* Font selector: a css_font_family bucket (CSS_FF_*) plus weight/slant flags.
 * The engine matches the generic group only, never an exact author family --
 * unless wfh names a registered @font-face (spec/webfont.md): a wf_name_hash,
 * 0 = none. A set-but-unregistered hash falls back to the bucket (fail-visible,
 * never fail-hard). */
typedef struct tsh_font {
    int family; /* css_font_family bucket */
    int bold;
    int italic;
    unsigned wfh; /* @font-face hash, 0 = local bucket stack */
} tsh_font;

#define TSH_MAX_GLYPHS 4096u       /* anti-DoS cap on one shaped slice */
#define TSH_MAX_TEXT   (1u << 20)  /* 1 MiB cap on one shaped slice    */

typedef enum tsh_status {
    TSH_OK = 0,
    TSH_ERR_UNAVAIL,   /* backend/font unavailable -> caller uses toy fallback */
    TSH_ERR_INPUT,     /* null/oversize/invalid args (fail-closed)             */
    TSH_ERR_OVERFLOW,  /* glyph count would exceed cap (fail-closed)           */
} tsh_status;

/* 1 once a fallback (sans) font resolves; lazily initialises on first call.
 * 0 means no font backend: the caller must use the toy-API path. */
int tsh_ready(void);

/* Shapes [text,len) in font f at px size into out[0..cap). On TSH_OK, *out_n
 * glyphs are written with positions relative to origin (0,0) on the baseline,
 * and *out_adv holds the total pen advance in pixels. Fail-closed on every other
 * status (see spec): the caller must not rely on partial output. len==0 yields
 * TSH_OK with *out_n==0, *out_adv==0. */
tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                     cairo_glyph_t *out, size_t cap, size_t *out_n, double *out_adv);

/* Total advance (px) of [text,len). Returns < 0.0 on any failure so the caller
 * can fall back to the toy-API measurement. */
double tsh_measure(const tsh_font *f, double px, const char *text, size_t len);

/* Shapes and paints [text,len) at (x, baseline) on cr (selects the FT font face
 * matching f+px, uses the current source color). Returns TSH_OK if it painted;
 * any other status means it did nothing and the caller must use the toy draw. */
tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, double baseline, const char *text, size_t len);

/* Registers one fetched @font-face for this document (spec/webfont.md): name
 * is the author family (hashed with wf_name_hash), bytes the validated font
 * program (copied; caller keeps ownership). Re-registering a key replaces it.
 * Returns 0 on success, -1 fail-closed (NULL/empty/oversize args, bad magic,
 * unparseable bytes, table full). Trusted side only; never the worker. */
int tsh_webfont_register(const char *name,
                         const unsigned char *bytes, size_t nbytes,
                         int bold, int italic);

/* Drops every registered webfont (document teardown / navigation). Idempotent,
 * NULL-safe by construction (no args). tsh_shutdown also clears the table. */
void tsh_webfont_clear(void);

/* Releases cached faces / blobs / FreeType library (leak hygiene; tests). */
void tsh_shutdown(void);

#endif /* FREEDOM_TEXT_SHAPE_H */
