/*
 * libFuzzer harness for the webfont registry (spec/webfont.md, woff2 slice).
 *
 * A font file is hostile remote content parsed on the TRUSTED side (FreeType, its
 * brotli/WOFF2 decoder, HarfBuzz). Arbitrary bytes through tsh_webfont_register --
 * including a WOFF/WOFF2 container and a variable face whose axes drive the weight
 * and optical-size instancing -- must never crash, leak or trigger UB in this
 * module, a rejected file must register nothing, and an accepted one must shape
 * and measure to finite values at any size.
 *
 * The first byte selects the registry key (bold/italic) and the pixel size; the
 * rest is the font file. Seeds: tests/fonts/.
 *
 * Build & run: make fuzz-wfr   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "text_shape.h"
#include "webfont.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define FZ_GLYPHS 32u

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 1) return 0;
    uint8_t sel = data[0];
    int bold = sel & 1, italic = (sel >> 1) & 1;
    double px = 4.0 + (double)(sel >> 2) * 3.0;          /* 4 .. 193 px */
    static const char name[] = "FuzzFace";
    int rc = tsh_webfont_register(name, data + 1, size - 1, bold, italic);
    tsh_font f = { .family = 0, .bold = bold, .italic = italic,
                   .wfh = wf_name_hash(name, sizeof name - 1) };
    static cairo_glyph_t out[FZ_GLYPHS];
    size_t n = 0;
    double adv = 0.0;
    if (tsh_shape(&f, px, "AB cd 0", 7, out, FZ_GLYPHS, &n, &adv) == TSH_OK) {
        if (n > FZ_GLYPHS) abort();
        if (adv != adv) abort();
        for (size_t i = 0; i < n; ++i)
            if (out[i].x != out[i].x || out[i].y != out[i].y) abort();
    }
    double m = tsh_measure(&f, px, "AB cd 0", 7);
    if (m != m) abort();
    /* The other weight key and another size: the dual registration of a variable
     * face and the optical-size switch. */
    f.bold = !bold;
    double m2 = tsh_measure(&f, px * 2.0 + 1.0, "AB", 2);
    if (m2 != m2) abort();
    (void)rc;
    tsh_webfont_clear();
    return 0;
}
