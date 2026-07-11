/*
 * libFuzzer harness for text_shape (the HarfBuzz shaping helper).
 *
 * The shaped TEXT is hostile remote content (page text). Arbitrary bytes through
 * tsh_shape / tsh_measure / tsh_draw must never crash, leak or trigger UB, must
 * keep the glyph cap fail-closed, must never write out of bounds, and the
 * measure must agree with the shaped total advance (the layout/paint consistency
 * invariant). Fonts are local; fontconfig's one-time leaks are suppressed
 * (tests/asan.supp via LSAN_OPTIONS in the make target).
 *
 * The first input byte (when present) is consumed to vary the font selector and
 * pixel size; the rest is the shaped text.
 *
 * Build & run: make fuzz-tsh   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "text_shape.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#define FZ_CAP 2048u

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    int family = 0, bold = 0, italic = 0;
    double px = 16.0;
    const char *text = (const char *)data;
    size_t len = size;

    if (size >= 1) {
        uint8_t b = data[0];
        family = b % 6;                          /* 0..5 (CSS_FF_* range) */
        bold   = (b >> 3) & 1;
        italic = (b >> 4) & 1;
        px     = 4.0 + (double)((b >> 5) & 7) * 8.0; /* 4 .. 60 px */
        text   = (const char *)data + 1;
        len    = size - 1;
    }

    tsh_font f = { .family = family, .bold = bold, .italic = italic };
    static cairo_glyph_t out[FZ_CAP];
    size_t n = 0;
    double adv = 0.0;
    tsh_status st = tsh_shape(&f, px, text, len, out, FZ_CAP, &n, &adv);

    if (st == TSH_OK) {
        if (n > FZ_CAP) abort();                 /* cap must hold */
        for (size_t i = 0; i < n; ++i) {
            /* No NaN positions escape (would corrupt the painter). */
            if (out[i].x != out[i].x || out[i].y != out[i].y) abort();
        }
        /* Same shaper, same slice: measure must equal the shaped advance. */
        double m = tsh_measure(&f, px, text, len);
        if (m >= 0.0) {
            double d = m - adv;
            if (d < 0.0) d = -d;
            if (d > 1e-3) abort();
        }
    }

    /* Exercise the cairo_show_glyphs draw path on a persistent tiny surface. */
    static cairo_t *cr;
    if (cr == NULL) {
        cairo_surface_t *s = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 64, 32);
        cr = cairo_create(s);
        cairo_surface_destroy(s); /* cr keeps a reference */
    }
    if (cr != NULL) {
        cairo_set_source_rgb(cr, 0, 0, 0);
        tsh_draw(cr, &f, px, 2.0, 16.0, text, len);
    }
    return 0;
}
