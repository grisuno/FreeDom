/*
 * pngdiff -- structural render-divergence metric between two page screenshots.
 *
 * Build-time tool for `make parity`. It answers one question: how differently is
 * this page laid out by Freedom versus by a reference browser? Exact pixel parity
 * is not the goal and is not achievable -- the two engines rasterise glyphs
 * differently, resolve fonts differently, and Freedom's PNG export forces a light
 * theme. Comparing colours would therefore report noise. What IS comparable, and
 * what actually breaks on a real page, is STRUCTURE: how tall the document ends up,
 * where ink sits horizontally, and how ink is distributed down the page.
 *
 * Three metrics, all scale-free and background-relative:
 *
 *   h_ratio   Freedom's total height / the reference's. One scalar with very high
 *             signal: a table collapsing to a one-column list, or a heading scale
 *             that is wrong, moves it immediately.
 *   col_mae   Mean absolute error between the two column-ink profiles (fraction of
 *             rows carrying ink at each normalised x). Catches collapsed columns,
 *             wrongly-split widths, a float that did not become a column, an icon
 *             that ballooned to the page width.
 *   row_mae   Mean absolute error between the two CUMULATIVE vertical ink
 *             distributions over normalised y. Catches content that is present but
 *             distributed wrongly down the page (bands of blank space, a block that
 *             flowed below instead of beside).
 *
 * "Ink" is defined per image against that image's own dominant background
 * luminance, so a dark author theme on one side and a forced light theme on the
 * other still compare meaningfully. That is exactly why the metric is structural
 * and not colorimetric.
 *
 * Rows are streamed one at a time through libpng (already a dependency of the
 * build), never held as a full bitmap: a real page render is routinely taller than
 * image_decode's 8192px anti-DoS cap, and memory stays O(width) regardless. Two
 * passes over each file: one to find the background luminance, one to accumulate
 * the profiles.
 *
 * This tool reads only local files that the harness itself just produced. It is not
 * part of the browser's attack surface and never sees remote content.
 *
 * Usage:   pngdiff <freedom.png> <reference.png>
 * Output:  one TSV line -- h_fd h_ff h_ratio col_mae row_mae score
 * Exit:    0 on success, 1 on a read/decode failure (message on stderr).
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>

/* Resolution of the two comparison profiles. Both images are resampled onto these
 * fixed buckets, so renders of differing width or height stay comparable. 200 is
 * fine enough to separate adjacent columns of a real layout and coarse enough that
 * a one-pixel rasterisation difference does not register. */
#define PD_COLS 200u
#define PD_ROWS 200u

/* A pixel counts as ink when its luminance differs from the page background by more
 * than this (0..255). Below it lies antialiasing fringe and subtle background
 * banding, which must not read as content. */
#define PD_INK_DELTA 24.0

typedef struct pd_profile {
    uint32_t width, height;
    double   col[PD_COLS];  /* ink fraction per normalised x */
    double   rowc[PD_ROWS]; /* CUMULATIVE ink fraction by normalised y, ends at 1 */
} pd_profile;

typedef struct pd_reader {
    FILE       *fp;
    png_structp png;
    png_infop   info;
    png_bytep   row;
    uint32_t    width, height;
} pd_reader;

static void pd_reader_close(pd_reader *r) {
    if (r->png != NULL) png_destroy_read_struct(&r->png, &r->info, NULL);
    free(r->row);
    if (r->fp != NULL) fclose(r->fp);
    memset(r, 0, sizeof *r);
}

/* Opens `path` and normalises whatever colour type it carries into 8-bit RGB, so
 * the two passes below can assume three bytes per pixel. Returns 0 on success. */
static int pd_reader_open(pd_reader *r, const char *path) {
    memset(r, 0, sizeof *r);
    r->fp = fopen(path, "rb");
    if (r->fp == NULL) {
        fprintf(stderr, "pngdiff: cannot open %s\n", path);
        return -1;
    }
    r->png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (r->png == NULL) { pd_reader_close(r); return -1; }
    r->info = png_create_info_struct(r->png);
    if (r->info == NULL) { pd_reader_close(r); return -1; }
    if (setjmp(png_jmpbuf(r->png))) {
        fprintf(stderr, "pngdiff: libpng rejected %s\n", path);
        pd_reader_close(r);
        return -1;
    }
    png_init_io(r->png, r->fp);
    png_read_info(r->png, r->info);

    png_byte color = png_get_color_type(r->png, r->info);
    png_byte depth = png_get_bit_depth(r->png, r->info);
    if (depth == 16) png_set_strip_16(r->png);
    if (color == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(r->png);
    if (color == PNG_COLOR_TYPE_GRAY && depth < 8) png_set_expand_gray_1_2_4_to_8(r->png);
    if (png_get_valid(r->png, r->info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(r->png);
    /* Compose against white rather than dropping alpha: a transparent region of a
     * screenshot is what the viewer would see as page white, and treating it as
     * black would invent ink where the page has none. */
    png_set_background(r->png, &(png_color_16){ 0, 255, 255, 255, 255 },
                       PNG_BACKGROUND_GAMMA_SCREEN, 0, 1.0);
    png_set_strip_alpha(r->png);
    if (color == PNG_COLOR_TYPE_GRAY || color == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(r->png);
    png_read_update_info(r->png, r->info);

    r->width  = png_get_image_width(r->png, r->info);
    r->height = png_get_image_height(r->png, r->info);
    if (r->width == 0 || r->height == 0) {
        fprintf(stderr, "pngdiff: %s has a zero dimension\n", path);
        pd_reader_close(r);
        return -1;
    }
    size_t rowbytes = png_get_rowbytes(r->png, r->info);
    if (rowbytes < (size_t)r->width * 3u) {
        fprintf(stderr, "pngdiff: %s did not normalise to RGB\n", path);
        pd_reader_close(r);
        return -1;
    }
    r->row = (png_bytep)malloc(rowbytes);
    if (r->row == NULL) { pd_reader_close(r); return -1; }
    return 0;
}

static double pd_lum(const png_byte *p) {
    return 0.2126 * (double)p[0] + 0.7152 * (double)p[1] + 0.0722 * (double)p[2];
}

/* Pass 1: the modal luminance IS the page background. Taking the corner pixel
 * instead would misread any page whose top-left is a logo or a coloured header. */
static int pd_background(const char *path, double *out_bg) {
    pd_reader r;
    if (pd_reader_open(&r, path) != 0) return -1;
    /* png_read_row may longjmp on a corrupt stream partway through the image. */
    if (setjmp(png_jmpbuf(r.png))) {
        fprintf(stderr, "pngdiff: truncated image data in %s\n", path);
        pd_reader_close(&r);
        return -1;
    }
    uint64_t hist[256];
    memset(hist, 0, sizeof hist);
    for (uint32_t y = 0; y < r.height; ++y) {
        png_read_row(r.png, r.row, NULL);
        for (uint32_t x = 0; x < r.width; ++x) {
            int b = (int)(pd_lum(&r.row[(size_t)x * 3u]) + 0.5);
            if (b < 0) b = 0;
            if (b > 255) b = 255;
            hist[b]++;
        }
    }
    int best = 0;
    for (int i = 1; i < 256; ++i) if (hist[i] > hist[best]) best = i;
    *out_bg = (double)best;
    pd_reader_close(&r);
    return 0;
}

/* Pass 2: ink profiles against the background found in pass 1. */
static int pd_profile_of(const char *path, pd_profile *out) {
    double bg;
    if (pd_background(path, &bg) != 0) return -1;

    pd_reader r;
    if (pd_reader_open(&r, path) != 0) return -1;
    if (setjmp(png_jmpbuf(r.png))) {
        fprintf(stderr, "pngdiff: truncated image data in %s\n", path);
        pd_reader_close(&r);
        return -1;
    }
    memset(out, 0, sizeof *out);
    out->width  = r.width;
    out->height = r.height;

    uint64_t colhit[PD_COLS];
    double   rowink[PD_ROWS];
    memset(colhit, 0, sizeof colhit);
    memset(rowink, 0, sizeof rowink);
    uint64_t total_ink = 0;

    for (uint32_t y = 0; y < r.height; ++y) {
        png_read_row(r.png, r.row, NULL);
        size_t rb = (size_t)y * PD_ROWS / r.height;   /* < PD_ROWS: y < height */
        for (uint32_t x = 0; x < r.width; ++x) {
            if (fabs(pd_lum(&r.row[(size_t)x * 3u]) - bg) <= PD_INK_DELTA) continue;
            colhit[(size_t)x * PD_COLS / r.width]++;
            rowink[rb] += 1.0;
            total_ink++;
        }
    }

    /* Column profile: fraction of this bucket's cells that carry ink, so a wide
     * image and a narrow one stay comparable. */
    for (size_t i = 0; i < PD_COLS; ++i) {
        double cells = (double)r.width / (double)PD_COLS * (double)r.height;
        out->col[i] = (cells > 0.0) ? (double)colhit[i] / cells : 0.0;
        if (out->col[i] > 1.0) out->col[i] = 1.0;
    }
    /* Vertical profile as a CUMULATIVE distribution: comparing raw per-band ink
     * would punish a one-band vertical shift far more than it deserves, while the
     * cumulative curve measures how far the content actually migrated. A blank page
     * has no distribution to compare, so it stays all-zero. */
    double acc = 0.0;
    for (size_t j = 0; j < PD_ROWS; ++j) {
        acc += rowink[j];
        out->rowc[j] = (total_ink > 0) ? acc / (double)total_ink : 0.0;
    }
    pd_reader_close(&r);
    return 0;
}

static double pd_mae(const double *a, const double *b, size_t n) {
    double s = 0.0;
    for (size_t i = 0; i < n; ++i) s += fabs(a[i] - b[i]);
    return (n > 0) ? s / (double)n : 0.0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: pngdiff <freedom.png> <reference.png>\n");
        return 1;
    }
    pd_profile fd, ff;
    if (pd_profile_of(argv[1], &fd) != 0) return 1;
    if (pd_profile_of(argv[2], &ff) != 0) return 1;

    double h_ratio = (ff.height > 0) ? (double)fd.height / (double)ff.height : 0.0;
    double col_mae = pd_mae(fd.col, ff.col, PD_COLS);
    double row_mae = pd_mae(fd.rowc, ff.rowc, PD_ROWS);

    /* One number to rank pages and to gate regressions. The height term is clamped
     * so a single catastrophic page cannot swamp the whole corpus total; the column
     * profile carries the most weight because horizontal structure is where real
     * layout bugs show up first. Lower is better; 0 means structurally identical. */
    double h_term = fabs(h_ratio - 1.0);
    if (h_term > 1.0) h_term = 1.0;
    double score = 100.0 * (0.40 * h_term + 0.40 * col_mae + 0.20 * row_mae);

    printf("%u\t%u\t%.4f\t%.4f\t%.4f\t%.2f\n",
           fd.height, ff.height, h_ratio, col_mae, row_mae, score);
    return 0;
}
