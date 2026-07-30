/*
 * libFuzzer harness for svg_render: sv_parse turns inline <svg> markup -- bytes
 * straight out of a hostile remote document -- into geometry, and sv_fit maps that
 * geometry onto a destination rect. Both run on the TRUSTED side (the painter
 * calls them, exactly as it calls css_parse), so neither may ever crash, leak,
 * read/write out of bounds, or overflow a pool.
 *
 * Beyond memory safety this asserts the module's structural invariants, because a
 * shape whose pool span points outside the pool would hand the Cairo painter a
 * wild read: every span must lie inside the pool it indexes, every count must be
 * within its cap, and a failed parse must leave the image empty rather than half
 * filled.
 *
 * Build & run: make fuzz-svg   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "svg_render.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    /* sv_image is large by design (fixed pools): the contract says heap. */
    sv_image *im = (sv_image *)calloc(1, sizeof *im);
    if (im == NULL) return 0;

    sv_status st = sv_parse((const char *)data, size, im);

    if (st != SV_OK) {
        /* A rejected parse leaves nothing behind for a caller to walk. */
        if (im->nshape != 0 || im->npt != 0 || im->nseg != 0) abort();
        free(im);
        return 0;
    }

    if (im->nshape > SV_MAX_SHAPES) abort();
    if (im->npt > SV_MAX_POINTS) abort();
    if (im->nseg > SV_MAX_SEGS) abort();
    /* Intrinsic size is always resolved on success (explicit, viewBox, or default). */
    if (!(im->width > 0.0) || !(im->height > 0.0)) abort();

    for (size_t i = 0; i < im->nshape; ++i) {
        const sv_shape *sh = &im->shapes[i];
        if (sh->kind < SV_RECT || sh->kind > SV_TEXT) abort();
        if (sh->opacity < 0 || sh->opacity > 100) abort();
        if (sh->fill_opacity < 0 || sh->fill_opacity > 100) abort();
        if (sh->stroke_opacity < 0 || sh->stroke_opacity > 100) abort();
        /* Colours are either a packed RGB or one of the two sentinels. */
        if (sh->fill < -2 || sh->fill > 0xFFFFFF) abort();
        if (sh->stroke < -2 || sh->stroke > 0xFFFFFF) abort();
        /* Pool spans must stay inside the pool the kind indexes -- this is what
         * keeps the painter's loops in bounds. */
        if (sh->kind == SV_POLYLINE || sh->kind == SV_POLYGON) {
            if (sh->first > im->npt) abort();
            if (sh->count > im->npt - sh->first) abort();
        } else if (sh->kind == SV_PATH) {
            if (sh->first > im->nseg) abort();
            if (sh->count > im->nseg - sh->first) abort();
        } else if (sh->kind == SV_TEXT) {
            /* Always NUL-terminated: the painter hands it to Cairo as a C string. */
            if (memchr(sh->text, '\0', sizeof sh->text) == NULL) abort();
        }
        for (int k = 0; k < 6; ++k)
            if (!isfinite(sh->m[k])) abort();
    }

    for (size_t i = 0; i < im->nseg; ++i) {
        const sv_seg *sg = &im->segs[i];
        if (sg->verb < SV_MOVE || sg->verb > SV_CLOSE) abort();
        for (int k = 0; k < 3; ++k)
            if (!isfinite(sg->x[k]) || !isfinite(sg->y[k])) abort();
    }

    /* sv_fit must stay finite and never divide by zero, for any destination. */
    const double dims[] = { 0.0, 1.0, 1000.0 };
    for (size_t a = 0; a < sizeof dims / sizeof dims[0]; ++a) {
        for (size_t b = 0; b < sizeof dims / sizeof dims[0]; ++b) {
            double sc = 0.0, ox = 0.0, oy = 0.0;
            sv_fit(im, dims[a], dims[b], &sc, &ox, &oy);
            if (!isfinite(sc) || !isfinite(ox) || !isfinite(oy)) abort();
        }
    }

    free(im);
    return 0;
}
