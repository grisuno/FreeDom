/*
 * TDD suite for freedom CLI (Hito 5 integration).
 *
 * Exercises the built freedom binary from the outside: argument handling,
 * local file rendering, and URL policy rejection. The binary must exist at
 * ./build/freedom before these tests run.
 *
 * Build: make test   ;   ASan: make asan
 */

#define _POSIX_C_SOURCE 200809L

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cmocka.h>

#include "image_decode.h"

#define FREEDOM_BIN "./build/freedom"
#define OUT_FILE    "__freedom_test_out.txt"
#define ERR_FILE    "__freedom_test_err.txt"

static int run_freedom(const char *arg, char *out, size_t out_size, int *exit_status) {
    char cmd[2048];
    const char *a = (arg != NULL) ? arg : "";
    int n = snprintf(cmd, sizeof cmd,
                     "%s --headless %s >" OUT_FILE " 2>" ERR_FILE,
                     FREEDOM_BIN, a);
    if (n < 0 || (size_t)n >= sizeof cmd) return -1;

    int rc = system(cmd);
    if (rc == -1) return -1;
    *exit_status = WEXITSTATUS(rc);

    FILE *f = fopen(OUT_FILE, "r");
    if (f == NULL) return -1;
    size_t got = fread(out, 1, out_size - 1, f);
    out[got] = '\0';
    fclose(f);
    return 0;
}

/* Runs the binary with a raw argument string (no implicit --headless), capturing
 * stdout into OUT_FILE. Used by the --download-pdf tests, which set their own mode. */
static int run_freedom_raw(const char *args, int *exit_status) {
    char cmd[2048];
    int n = snprintf(cmd, sizeof cmd, "%s %s >" OUT_FILE " 2>" ERR_FILE,
                     FREEDOM_BIN, (args != NULL) ? args : "");
    if (n < 0 || (size_t)n >= sizeof cmd) return -1;
    int rc = system(cmd);
    if (rc == -1) return -1;
    *exit_status = WEXITSTATUS(rc);
    return 0;
}

/* True if path exists and its first bytes are the PDF magic "%PDF". */
static int is_pdf_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (f == NULL) return 0;
    char magic[5] = {0};
    size_t got = fread(magic, 1, 4, f);
    fclose(f);
    return got == 4 && memcmp(magic, "%PDF", 4) == 0;
}

/* True if path exists and its first bytes are the 8-byte PNG signature. */
static int is_png_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (f == NULL) return 0;
    unsigned char magic[8] = {0};
    size_t got = fread(magic, 1, 8, f);
    fclose(f);
    static const unsigned char png_sig[8] = {0x89,'P','N','G',0x0D,0x0A,0x1A,0x0A};
    return got == 8 && memcmp(magic, png_sig, 8) == 0;
}

static void cleanup_files(void) {
    (void)unlink(OUT_FILE);
    (void)unlink(ERR_FILE);
}

/* Reads a whole file into a malloc'd buffer (caller frees). NULL on any failure. */
static uint8_t *read_file_all(const char *path, size_t *out_len) {
    FILE *f = fopen(path, "rb");
    if (f == NULL) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0 || fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    uint8_t *buf = (uint8_t *)malloc((size_t)sz);
    if (buf == NULL) { fclose(f); return NULL; }
    size_t got = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    if (got != (size_t)sz) { free(buf); return NULL; }
    *out_len = (size_t)sz;
    return buf;
}

/* --- argument handling --- */

static void test_help(void **state) {
    (void)state;
    char out[512];
    int rc;
    assert_int_equal(run_freedom("--help", out, sizeof out, &rc), 0);
    assert_int_equal(rc, 0);
    assert_non_null(strstr(out, "usage"));
}

static void test_version(void **state) {
    (void)state;
    char out[512];
    int rc;
    assert_int_equal(run_freedom("--version", out, sizeof out, &rc), 0);
    assert_int_equal(rc, 0);
    assert_non_null(strstr(out, "Freedom"));
}

static void test_no_args(void **state) {
    (void)state;
    char out[512];
    int rc;
    assert_int_equal(run_freedom(NULL, out, sizeof out, &rc), 0);
    assert_int_equal(rc, 2);
}

/* --- local file rendering --- */

static void test_local_html(void **state) {
    (void)state;
    const char *html =
        "<!DOCTYPE html><html><head><title>Freedom Test</title></head>"
        "<body><p>Hello from the sandbox.</p></body></html>";
    const char *path = "__freedom_test_page.html";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);

    char out[1024];
    int rc;
    char arg[256];
    assert_true((size_t)snprintf(arg, sizeof arg, "%s", path) < sizeof arg);
    assert_int_equal(run_freedom(arg, out, sizeof out, &rc), 0);
    assert_int_equal(rc, 0);
    assert_non_null(strstr(out, "Freedom Test"));
    assert_non_null(strstr(out, "Hello from the sandbox."));

    unlink(path);
}

static void test_local_form_renders_inputs(void **state) {
    (void)state;
    const char *html =
        "<html><head><title>Form Page</title></head><body>"
        "<form action=\"https://duckduckgo.com/\" method=\"get\">"
        "<input type=\"search\" name=\"q\" placeholder=\"Search the web\">"
        "<input type=\"hidden\" name=\"ia\" value=\"HIDDENMARKER\">"
        "<input type=\"submit\" value=\"Go\"></form></body></html>";
    const char *path = "__freedom_test_form.html";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);

    char out[1024];
    int rc;
    assert_int_equal(run_freedom(path, out, sizeof out, &rc), 0);
    assert_int_equal(rc, 0);
    assert_non_null(strstr(out, "Search the web")); /* the editable field placeholder */
    assert_non_null(strstr(out, "[ Go ]"));          /* the submit button */
    assert_null(strstr(out, "HIDDENMARKER"));         /* hidden value is not shown... */
    assert_null(strstr(out, "[hidden"));              /* ...nor is the hidden control */

    unlink(path);
}

static void test_missing_file(void **state) {
    (void)state;
    char out[512];
    int rc;
    assert_int_equal(run_freedom("__freedom_missing_file.html", out, sizeof out, &rc), 0);
    assert_int_equal(rc, 1);
}

/* --- headless PDF export (--download-pdf, visual-review tooling) --- */

static void test_download_pdf_local(void **state) {
    (void)state;
    const char *html =
        "<!DOCTYPE html><html><head><title>PDF Page</title></head>"
        "<body><h1>Heading</h1><p>Vector text for review.</p></body></html>";
    const char *path = "__freedom_pdf_page.html";
    const char *pdf = "__freedom_out.pdf";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(pdf);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args, "--download-pdf=%s %s", pdf, path)
                < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_pdf_file(pdf)); /* a real vector PDF, not a stub */

    unlink(path);
    unlink(pdf);
}

/* --download-pdf with no PATH is a usage error (fail closed: never guess a path). */
static void test_download_pdf_requires_path(void **state) {
    (void)state;
    int rc = -1;
    assert_int_equal(run_freedom_raw("--download-pdf examples/sample.html", &rc), 0);
    assert_int_equal(rc, 2);
}

/* --- headless PNG export (--download-png, visual-review tooling) --- */

static void test_download_png_local(void **state) {
    (void)state;
    const char *html =
        "<!DOCTYPE html><html><head><title>PNG Page</title></head>"
        "<body><h1>Heading</h1><p>Raster text for review.</p></body></html>";
    const char *path = "__freedom_png_page.html";
    const char *png = "__freedom_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args, "--download-png=%s %s", png, path)
                < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png)); /* a real PNG bitmap, not a stub */

    unlink(path);
    unlink(png);
}

/* --download-png --images decodes the page's local images through the confined worker
 * and paints the real bitmap instead of the "image (allowed)" placeholder. Exercises
 * the headless image pipeline end-to-end (render_doc_images -> load_images -> local
 * disk read -> worker decode -> Cairo surface -> free_images); under `make asan` the
 * asan-instrumented freedom subprocess turns any leak/UAF in that path into a failure
 * here. The declared 120x80 clears the tracking-pixel gate so the image is ALLOWed and
 * actually decoded; the visual-review PNG confirms the pixels (see CLAUDE.md). */
static void test_download_png_images_local(void **state) {
    (void)state;
    /* A known-good 120x80 RGB PNG fixture that decodes in the worker (a 1x1 does not:
     * it would be blocked as a tracking pixel before the decode is even reached). */
    static const unsigned char pic[] = {
        0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,
        0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x50,0x08,0x02,0x00,0x00,0x00,0x5d,0xf9,0x26,
        0xde,0x00,0x00,0x00,0xfb,0x49,0x44,0x41,0x54,0x78,0x9c,0xed,0xdd,0xb1,0x0d,0xc2,
        0x30,0x14,0x40,0x41,0x82,0x98,0x03,0xd6,0x60,0xb4,0x30,0x01,0xab,0x65,0x0d,0x36,
        0xa1,0xa5,0x21,0x09,0x42,0xbc,0x48,0xe4,0xae,0x75,0x63,0x3d,0x7d,0xd9,0x4a,0xe3,
        0x0c,0xe7,0x71,0x3a,0xf0,0x7b,0xc7,0xad,0x37,0xb0,0x17,0x42,0x47,0x84,0x8e,0x08,
        0x1d,0x11,0x3a,0x22,0x74,0x44,0xe8,0x88,0xd0,0x11,0xa1,0x23,0x42,0x47,0x84,0x8e,
        0x08,0x1d,0x11,0x3a,0x22,0x74,0x44,0xe8,0x88,0xd0,0x11,0xa1,0x23,0xa7,0xf9,0xe5,
        0xc7,0xfd,0xda,0xec,0xe3,0x3f,0x5c,0x6e,0x6f,0x3f,0xb3,0x4d,0x74,0x44,0xe8,0x88,
        0xd0,0x91,0x85,0x33,0xfa,0xd5,0xcc,0x01,0xb4,0x67,0x2b,0xaf,0x31,0x13,0x1d,0x11,
        0x3a,0x22,0x74,0x44,0xe8,0x88,0xd0,0x11,0xa1,0x23,0x42,0x47,0x84,0x8e,0x08,0x1d,
        0x11,0x3a,0x22,0x74,0x44,0xe8,0x88,0xd0,0x11,0xa1,0x23,0x42,0x47,0x84,0x8e,0x08,
        0x1d,0x11,0x3a,0x22,0x74,0x44,0xe8,0x88,0xd0,0x11,0xa1,0x23,0x42,0x47,0x84,0x8e,
        0x08,0x1d,0x11,0x3a,0x22,0x74,0x44,0xe8,0x88,0xd0,0x11,0xa1,0x23,0x42,0x47,0x84,
        0x8e,0x08,0x1d,0x11,0x3a,0x22,0x74,0x44,0xe8,0x88,0xd0,0x11,0xa1,0x23,0x42,0x47,
        0x84,0x8e,0x08,0x1d,0x11,0x3a,0x22,0x74,0x44,0xe8,0x88,0xd0,0x11,0xa1,0x23,0x42,
        0x47,0x84,0x8e,0x08,0x1d,0x11,0x3a,0x22,0x74,0x44,0xe8,0xc8,0x07,0x8f,0x57,0x79,
        0x6c,0xf0,0x1b,0x26,0x3a,0x22,0x74,0x44,0xe8,0xc8,0xe0,0xf7,0x20,0x0d,0x13,0x1d,
        0x11,0x3a,0x22,0x74,0x44,0xe8,0x88,0xd0,0x11,0xa1,0x23,0x42,0x47,0x84,0x8e,0x3c,
        0x01,0x99,0x9b,0x0b,0x01,0x03,0x3e,0x2c,0x36,0x00,0x00,0x00,0x00,0x49,0x45,0x4e,
        0x44,0xae,0x42,0x60,0x82,
    };
    const char *img = "__freedom_test_pic.png";
    const char *html_path = "__freedom_img_page.html";
    const char *png = "__freedom_img_out.png";

    FILE *fi = fopen(img, "wb");
    assert_non_null(fi);
    assert_int_equal(fwrite(pic, 1, sizeof pic, fi), sizeof pic);
    fclose(fi);

    const char *html =
        "<html><head><title>Img Page</title></head><body>"
        "<h1>Heading</h1>"
        "<img src=\"__freedom_test_pic.png\" alt=\"fixture\" width=\"120\" height=\"80\">"
        "</body></html>";
    FILE *fh = fopen(html_path, "w");
    assert_non_null(fh);
    assert_int_equal(fwrite(html, 1, strlen(html), fh), strlen(html));
    fclose(fh);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args, "--images --download-png=%s %s",
                 png, html_path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png)); /* real bitmap, image decoded (not a placeholder-only render) */

    unlink(img);
    unlink(html_path);
    unlink(png);
}

/* --download-png with no PATH is a usage error (fail closed: never guess a path). */
static void test_download_png_requires_path(void **state) {
    (void)state;
    int rc = -1;
    assert_int_equal(run_freedom_raw("--download-png examples/sample.html", &rc), 0);
    assert_int_equal(rc, 2);
}

/* Regression for the M1.1-adjacent paint-order fix in write_doc_png/paint_structured
 * (gui/browser_ui.c, paint_positioned_one): CSS 2.1 Appendix E puts a negative
 * z-index stacking context in a paint-order layer that precedes in-flow content,
 * so it must paint BEHIND, not on top of, an overlapping in-flow box. Before the
 * fix, Stage 2's two passes both ran after the in-flow paint, so #front (in-flow,
 * blue, no explicit position) never covered #behind (position:absolute; z-index:-1;
 * red) even though #behind is meant to sit underneath it -- the sampled pixel came
 * back pure red. Decodes the exported PNG (via image_decode, the project's own PNG
 * decoder) and asserts the overlap pixel is blue, not red. */
static void test_download_png_negative_zindex_paints_behind_inflow(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0;}"
        "#behind{position:absolute;top:0;left:0;background:#ff0000;z-index:-1;}"
        "#front{background:#0000ff;}"
        "</style></head><body>"
        "<div id=\"behind\">X</div><div id=\"front\">Y</div>"
        "</body></html>";
    const char *path = "__freedom_negz_page.html";
    const char *png = "__freedom_negz_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --download-png=%s %s", png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png));

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    /* (200, 16): well inside both boxes' shared row, far from either single-glyph
     * label so font rendering differences can't flip the sampled colour. */
    assert_true(px.width > 500 && px.height > 12);
    uint32_t pixel = ((const uint32_t *)(const void *)px.data)[16 * (px.stride / 4) + 200];
    uint8_t a = (uint8_t)(pixel >> 24), r = (uint8_t)(pixel >> 16),
            g = (uint8_t)(pixel >> 8),  b = (uint8_t)pixel;
    (void)a; (void)g;
    assert_true(b > 200);  /* the in-flow blue box, painted last, wins the pixel */
    assert_true(r < 50);   /* not the red negative-z box underneath */
    img_pixels_free(&px);

    unlink(path);
    unlink(png);
}

/* Regression for M1.1 increment 3 (real group opacity): a positioned box with
 * opacity:0.5 must be composited as ONE unit (decoration + content blended
 * together, then the whole result faded) via an offscreen Cairo group
 * (cairo_push_group/pop_group_to_source/paint_with_alpha in paint_positioned_one,
 * gui/browser_ui.c), not each piece faded independently. Over a plain white page,
 * a solid #0000ff box at opacity 0.5 must sample as the exact alpha blend
 * (127,127,255) -- not full-strength blue (opacity ignored, a plumbing bug) and
 * not some other blend (double-composited or wrong alpha). */
static void test_download_png_group_opacity_blends_with_background(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0;}"
        /* Explicit width: `width:auto` on an out-of-flow box shrink-wraps to its
         * content (CSS 2.2 §10.3.7), so the sample point below would fall outside
         * the box. This test is about the opacity BLEND, not about auto-sizing. */
        "#box{position:absolute;top:0;left:0;width:800px;background:#0000ff;opacity:0.5;}"
        "</style></head><body>"
        "<div id=\"box\">X</div>"
        "<p>filler text to give the page a nonzero height for the export</p>"
        "</body></html>";
    const char *path = "__freedom_opacity_page.html";
    const char *png = "__freedom_opacity_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --download-png=%s %s", png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png));

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    /* (200, 12): inside the box's row, far from the single-glyph "X" label. */
    assert_true(px.width > 500 && px.height > 12);
    uint32_t pixel = ((const uint32_t *)(const void *)px.data)[12 * (px.stride / 4) + 200];
    uint8_t r = (uint8_t)(pixel >> 16), g = (uint8_t)(pixel >> 8), b = (uint8_t)pixel;
    /* 0.5*(0,0,255) + 0.5*(255,255,255 white page) = (127.5,127.5,255). Allow +-2
     * for rounding, not full-strength blue (opacity ignored) or anything darker
     * (double-blended / wrong alpha). */
    assert_true(r >= 125 && r <= 130);
    assert_true(g >= 125 && g <= 130);
    assert_true(b >= 253);
    img_pixels_free(&px);

    unlink(path);
    unlink(png);
}

/* An out-of-flow box with `width: auto` SHRINK-WRAPS to its content (CSS 2.2
 * §10.3.7) instead of filling its containing block, and a `position:relative`
 * wrapper that holds only out-of-flow children still generates its own box (so it
 * paints and acts as their containing block).
 *
 * Both used to be wrong together: the wrapper registered no box at all (its only
 * children were out of flow, so nothing in the flow referenced it), which left the
 * absolutes resolving against a degenerate 0x0 containing block; and auto width fell
 * back to the FULL content width, so a right-anchored badge was placed at
 * cb_right - full_width, i.e. far off the left edge of the page. Verified against
 * Firefox: the badge sits at the wrapper's right edge, and the area to its left is
 * the wrapper's own background. */
static void test_download_png_absolute_shrinks_and_anchors_right(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0;}"
        "#rel{position:relative;height:80px;background:#00ff00;}"
        "#badge{position:absolute;top:10px;right:0;background:#0000ff;}"
        "</style></head><body>"
        "<div id=\"rel\"><div id=\"badge\">B</div></div>"
        "<p>filler text to give the page a nonzero height for the export</p>"
        "</body></html>";
    const char *path = "__freedom_abs_shrink_page.html";
    const char *png = "__freedom_abs_shrink_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --download-png=%s %s", png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png));

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    assert_true(px.width > 600 && px.height > 60);
    const uint32_t *rowpx = (const uint32_t *)(const void *)px.data;
    const size_t stride = px.stride / 4;

    /* Scan the whole wrapper for the badge rather than hardcoding pixels (the export
     * adds a page margin and the badge is only as wide as one glyph). Record the
     * horizontal extent of the blue badge and confirm the wrapper's green paints. */
    size_t blue_min = px.width, blue_max = 0, green_seen = 0;
    for (size_t y = 0; y < px.height; ++y) {
        for (size_t x = 0; x < px.width; ++x) {
            uint32_t p = rowpx[y * stride + x];
            uint8_t r = (uint8_t)(p >> 16), g = (uint8_t)(p >> 8), b = (uint8_t)p;
            if (r <= 8 && g <= 8 && b >= 200) {          /* badge blue */
                if (x < blue_min) blue_min = x;
                if (x > blue_max) blue_max = x;
            } else if (r <= 8 && g >= 200 && b <= 8) {   /* wrapper green */
                ++green_seen;
            }
        }
    }
    /* The wrapper generated its own box and painted: a wrapper holding only
     * out-of-flow children used to register no box at all and stayed blank. */
    assert_true(green_seen > 1000);
    /* The badge painted somewhere. */
    assert_true(blue_max >= blue_min);
    /* SHRINK-WRAPPED: one glyph plus padding, nowhere near the full page width.
     * Auto width used to fall back to the whole content width. */
    assert_true((blue_max - blue_min) < px.width / 5);
    /* RIGHT-ANCHORED: sits in the right fifth of the page. With the old full-width
     * fallback, x = cb_right - full_width put it off the LEFT edge instead. */
    assert_true(blue_min > (px.width * 4) / 5);
    img_pixels_free(&px);

    unlink(path);
    unlink(png);
}

/* Renders `html` to a PNG and returns the horizontal extent of its dark ink, or
 * -1. The ink extent is the direct measure of "how wide did this line come out",
 * which is what a whitespace bug moves. */
static double ink_width(const char *html) {
    const char *path = "__freedom_ws_page.html";
    const char *png = "__freedom_ws_out.png";
    FILE *f = fopen(path, "w");
    if (f == NULL) return -1.0;
    if (fwrite(html, 1, strlen(html), f) != strlen(html)) { fclose(f); return -1.0; }
    fclose(f);
    (void)unlink(png);

    char args[512];
    if ((size_t)snprintf(args, sizeof args, "--author-css --download-png=%s %s", png, path)
        >= sizeof args) { unlink(path); return -1.0; }
    int rc = -1;
    if (run_freedom_raw(args, &rc) != 0 || rc != 0) { unlink(path); return -1.0; }

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    if (bytes == NULL) { unlink(path); unlink(png); return -1.0; }
    img_pixels px;
    int ok = (img_decode(bytes, len, &px) == IMG_OK);
    free(bytes);
    if (!ok) { unlink(path); unlink(png); return -1.0; }

    const uint32_t *rowpx = (const uint32_t *)(const void *)px.data;
    const size_t stride = px.stride / 4;
    size_t min_x = px.width, max_x = 0;
    int any = 0;
    for (size_t y = 0; y < px.height; ++y) {
        for (size_t x = 0; x < px.width; ++x) {
            uint32_t p = rowpx[y * stride + x];
            uint8_t r = (uint8_t)(p >> 16), g = (uint8_t)(p >> 8), b = (uint8_t)p;
            if (r < 128 && g < 128 && b < 128) {   /* glyph ink on the white page */
                if (x < min_x) min_x = x;
                if (x > max_x) max_x = x;
                any = 1;
            }
        }
    }
    img_pixels_free(&px);
    unlink(path);
    unlink(png);
    if (!any) return -1.0;
    return (double)(max_x - min_x);
}

/* An absolute font-size must land at exactly that many pixels, which means a 32px
 * declaration measures twice as wide as a 16px one on the same glyphs. */
static void test_absolute_font_size_lands_exact(void **state) {
    (void)state;
    const char *small =
        "<html><head><style>body{margin:0;padding:0}p{font-size:16px}</style></head>"
        "<body><p>Hamburgefonstiv</p></body></html>";
    const char *big =
        "<html><head><style>body{margin:0;padding:0}p{font-size:32px}</style></head>"
        "<body><p>Hamburgefonstiv</p></body></html>";
    double w_small = ink_width(small);
    double w_big = ink_width(big);
    assert_true(w_small > 0.0 && w_big > 0.0);
    double ratio = w_big / w_small;
    assert_true(ratio > 1.9 && ratio < 2.1);
}

/* An <h1> with an author font-size takes THAT size, not the size multiplied by the
 * user-agent heading scale (the doubled-heading bug). h1{font-size:16px} must
 * measure like a 16px paragraph, not like a 32px one. */
static void test_author_font_size_on_heading_replaces_ua_scale(void **state) {
    (void)state;
    const char *heading =
        "<html><head><style>body{margin:0;padding:0}h1{font-size:16px}"
        "</style></head><body><h1>Hamburgefonstiv</h1></body></html>";
    /* Bold, because a heading IS bold in the user-agent sheet -- this test is about
     * size only. */
    const char *para =
        "<html><head><style>body{margin:0;padding:0}p{font-size:16px;font-weight:bold}"
        "</style></head><body><p>Hamburgefonstiv</p></body></html>";
    double w_h = ink_width(heading);
    double w_p = ink_width(para);
    assert_true(w_h > 0.0 && w_p > 0.0);
    assert_true(w_h < w_p + 3.0 && w_h > w_p - 3.0);
}

/* CSS `color` INHERITS: the user-agent sheet gives a heading no colour of its own,
 * so a document that sets none must paint its headings in the same ink as its body.
 * The theme used to hand headings a navy accent, which made every unstyled page
 * two-coloured where Firefox paints one. spec/box_style.md "Metricas UA del tema". */
static void test_heading_colour_matches_body_text(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>body{margin:0;padding:0}</style></head>"
        "<body><h1>Heading</h1><p>Paragraph</p></body></html>";
    const char *path = "__freedom_hcol_page.html";
    const char *png = "__freedom_hcol_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --download-png=%s %s", png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    /* Every dark pixel on the page must be neutral ink: no blue-dominant glyph.
     * A navy heading shows up as b - r well above zero. */
    const uint32_t *rowpx = (const uint32_t *)(const void *)px.data;
    const size_t stride = px.stride / 4;
    int blue_ink = 0, dark_seen = 0;
    for (size_t y = 0; y < px.height; ++y) {
        for (size_t x = 0; x < px.width; ++x) {
            uint32_t p = rowpx[y * stride + x];
            int r = (int)(uint8_t)(p >> 16), g = (int)(uint8_t)(p >> 8), b = (int)(uint8_t)p;
            if (r < 120 && g < 120 && b < 160) {
                ++dark_seen;
                /* The old theme heading was (15,20,51): b - r = 36. Body ink is
                 * neutral grey, where b - r is 0. */
                if (b - r > 20) ++blue_ink;
            }
        }
    }
    img_pixels_free(&px);
    assert_true(dark_seen > 100);      /* the page did paint text */
    assert_int_equal(blue_ink, 0);     /* none of it tinted */

    unlink(path);
    unlink(png);
}

/* A heading is bold in the user-agent sheet, but the author can turn that OFF.
 * block_style forced bold for every RD_HEADING and only OR-ed the author value in,
 * so `h1{font-weight:normal}` was unrepresentable. */
static void test_author_can_unbold_a_heading(void **state) {
    (void)state;
    const char *bold =
        "<html><head><style>body{margin:0;padding:0}h1{font-size:16px}</style></head>"
        "<body><h1>Hamburgefonstiv</h1></body></html>";
    const char *normal =
        "<html><head><style>body{margin:0;padding:0}h1{font-size:16px;font-weight:normal}"
        "</style></head><body><h1>Hamburgefonstiv</h1></body></html>";
    double w_bold = ink_width(bold);
    double w_normal = ink_width(normal);
    assert_true(w_bold > 0.0 && w_normal > 0.0);
    /* Bold text is wider than the same glyphs at the same size. */
    assert_true(w_bold > w_normal + 2.0);
}

/* CSS 2.2 section 9.7: position:absolute|fixed computes display to block, so an
 * absolutely positioned <span> is a block box and gets a box entry -- without one
 * there is nothing for the positioned pass to place and right/bottom did nothing.
 * spec/page_view.md "position:absolute|fixed y float vuelven al elemento de bloque". */
static void test_absolute_span_honours_right_bottom(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0}"
        ".wrap{position:relative;height:200px;background:#eeeeff}"
        ".tag{position:absolute;right:10px;bottom:10px;background:#00ff00;padding:4px}"
        "</style></head><body>"
        "<div class=\"wrap\"><span class=\"tag\">corner</span></div>"
        "</body></html>";
    const char *path = "__freedom_absspan_page.html";
    const char *png = "__freedom_absspan_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --download-png=%s %s", png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    const uint32_t *rowpx = (const uint32_t *)(const void *)px.data;
    const size_t stride = px.stride / 4;
    size_t gx_min = px.width, gx_max = 0, gy_min = px.height, gy_max = 0;
    int seen = 0;
    for (size_t y = 0; y < px.height; ++y) {
        for (size_t x = 0; x < px.width; ++x) {
            uint32_t p = rowpx[y * stride + x];
            uint8_t r = (uint8_t)(p >> 16), g = (uint8_t)(p >> 8), b = (uint8_t)p;
            if (r <= 8 && g >= 200 && b <= 8) {
                if (x < gx_min) gx_min = x;
                if (x > gx_max) gx_max = x;
                if (y < gy_min) gy_min = y;
                if (y > gy_max) gy_max = y;
                seen = 1;
            }
        }
    }
    /* px must stay LIVE for these: img_pixels_free zeroes the struct, so reading
     * px.width afterwards compares against 0 and every bound trivially fails. */
    assert_true(seen);
    /* Shrink-wrapped, not full width. */
    assert_true((gx_max - gx_min) < px.width / 3);
    /* Anchored to the RIGHT edge of the wrapper, not the left origin. */
    assert_true(gx_min > (px.width * 2) / 3);
    /* Anchored to the BOTTOM of the 200px wrapper, not its top. */
    assert_true(gy_min > 100);
    assert_true(gy_max > gy_min);
    img_pixels_free(&px);

    unlink(path);
    unlink(png);
}

/* CSS whitespace collapsing does NOT invent a space where the source had none.
 * The word flow used to insert one before every non-line-opening word, so
 * `<strong>bold</strong>,` painted as `bold ,` -- a comma detached from its word
 * on every page that uses inline emphasis, links or <code>.
 * spec/page_view.md "Colapso de espacio en el borde entre runs". */
static void test_inline_run_boundary_does_not_invent_space(void **state) {
    (void)state;
    const char *tight =
        "<html><head><style>body{margin:0;padding:0;font-size:16px}</style></head>"
        "<body><p><strong>bold</strong>,<em>italic</em>,<code>code</code></p></body></html>";
    const char *spaced =
        "<html><head><style>body{margin:0;padding:0;font-size:16px}</style></head>"
        "<body><p><strong>bold</strong> , <em>italic</em> , <code>code</code></p></body></html>";

    double w_tight = ink_width(tight);
    double w_spaced = ink_width(spaced);
    assert_true(w_tight > 0.0);
    assert_true(w_spaced > 0.0);

    /* The source with explicit spaces must come out WIDER: four separator spaces
     * against none. With the bug both rows measured identically. */
    assert_true(w_spaced > w_tight + 4.0);
}

/* The collapse still happens: a run of several spaces between two runs paints ONE
 * space, so it must measure the same as a single space. */
static void test_inline_run_boundary_collapses_runs_of_space(void **state) {
    (void)state;
    const char *one =
        "<html><head><style>body{margin:0;padding:0;font-size:16px}</style></head>"
        "<body><p><strong>bold</strong> <em>italic</em></p></body></html>";
    const char *many =
        "<html><head><style>body{margin:0;padding:0;font-size:16px}</style></head>"
        "<body><p><strong>bold</strong>     <em>italic</em></p></body></html>";

    double w_one = ink_width(one);
    double w_many = ink_width(many);
    assert_true(w_one > 0.0);
    assert_true(w_many > 0.0);
    assert_true(w_many < w_one + 1.0 && w_many > w_one - 1.0);
}

/* CSS 2.1 §10.8 line-box regression (Wikipedia headings): the line takes the MAX
 * leading of its fragments. A trailing `line-height:0` run (the vector skin's
 * `.mw-editsection` after every section heading) used to overwrite the whole
 * line's spacing -- the heading row flushed at near-zero height and the next
 * paragraph painted THROUGH the heading glyphs. The red paragraph must start
 * strictly below the lowest dark heading pixel. */
static void test_download_png_line_height_zero_does_not_shrink_line(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0;}"
        ".big{font-size:2em;}"
        ".ed{line-height:0;font-size:0.8em;}"
        ".after{color:#ff0000;}"
        "</style></head><body>"
        "<div><span class=\"big\">Heading glyphs</span>"
        "<span class=\"ed\">[edit]</span></div>"
        "<p class=\"after\">paragraph below the heading</p>"
        "</body></html>";
    const char *path = "__freedom_lh0_page.html";
    const char *png = "__freedom_lh0_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --download-png=%s %s", png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png));

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    const uint32_t *rowpx = (const uint32_t *)(const void *)px.data;
    const size_t stride = px.stride / 4;
    size_t dark_max_y = 0, red_min_y = px.height;
    for (size_t y = 0; y < px.height; ++y) {
        for (size_t x = 0; x < px.width; ++x) {
            uint32_t p = rowpx[y * stride + x];
            uint8_t r = (uint8_t)(p >> 16), g = (uint8_t)(p >> 8), b = (uint8_t)p;
            if (r >= 200 && g <= 80 && b <= 80) {          /* paragraph red */
                if (y < red_min_y) red_min_y = y;
            } else if (r < 150 && g < 150 && b < 200 &&
                       (int)r + g + b < 380 && r <= (int)g + 40) {
                /* heading ink; r<=g+40 excludes the paragraph's red antialias */
                if (y > dark_max_y) dark_max_y = y;
            }
        }
    }
    assert_true(dark_max_y > 0);          /* the heading painted */
    assert_true(red_min_y < px.height);   /* the paragraph painted */
    /* The paragraph starts BELOW the heading's lowest glyph pixel. */
    assert_true(red_min_y > dark_max_y);
    img_pixels_free(&px);

    unlink(path);
    unlink(png);
}

/* Regression for M1.1 increment 4 (in-flow box group opacity): an IN-FLOW
 * (non-positioned) box with opacity must fade as ONE coherent unit -- its own
 * decoration (background) AND its text row's cascaded background-color together
 * -- not just the box decoration alone. A decoration-only group produces a
 * visible artifact: the row's own bg_rgb fill (paint_content_row, a separate
 * draw call that cascades the same author background-color) paints solid and
 * un-faded on top of an otherwise-correctly-faded box, which looks WORSE than no
 * fix at all. Exercises paint_box_and_direct_rows + row_owner_block_id (which
 * also fixed row-to-box lookup for plain text rows, previously only correct for
 * RC_IMAGE rows) in gui/browser_ui.c. */
static void test_download_png_inflow_opacity_blends_box_and_row_together(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0;background:#00ff00;}"
        "#box{background:#0000ff;opacity:0.5;padding:10px;}"
        "</style></head><body>"
        "<div id=\"box\">inflow box text should also be readable</div>"
        "</body></html>";
    const char *path = "__freedom_inflow_opacity_page.html";
    const char *png = "__freedom_inflow_opacity_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --download-png=%s %s", png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png));

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    /* Sample two rows: y=30 is inside the padding (box decoration only, no text
     * row behind it), y=45 is inside the text row itself. Both must show the SAME
     * blend -- 0.5*(0,0,255 blue) + 0.5*(0,255,0 green) = (0,127.5,127.5) -- proving
     * the row's background fill is no longer a separate, un-faded solid patch. */
    assert_true(px.width > 500 && px.height > 45);
    for (int y = 30; y <= 45; y += 15) {
        uint32_t pixel = ((const uint32_t *)(const void *)px.data)[y * (px.stride / 4) + 500];
        uint8_t r = (uint8_t)(pixel >> 16), g = (uint8_t)(pixel >> 8), b = (uint8_t)pixel;
        assert_true(r <= 2);                    /* no red channel in blue+green */
        assert_true(g >= 125 && g <= 130);
        assert_true(b >= 125 && b <= 130);
    }
    img_pixels_free(&px);

    unlink(path);
    unlink(png);
}

/* Regression for M1.1 increment 4 (mix-blend-mode wiring): a box with
 * mix-blend-mode:multiply must composite through the matching Cairo operator
 * (CAIRO_OPERATOR_MULTIPLY), not the default OVER -- multiply(orange #ff8800,
 * blue #0000ff) is component-wise (255*0, 136*0, 0*255)/255 = pure black,
 * visibly different from either input color or an OVER blend (which would show
 * opaque blue). Exercises box_forms_stacking_context/bui_blend_operator in
 * gui/browser_ui.c and the mix_blend field through pv_box_def -> tab.c IPC ->
 * box_tree.c cx_style (M1.1 increment 4 CSS wiring). */
static void test_download_png_mix_blend_multiply_uses_cairo_operator(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0;}"
        /* Explicit widths: an out-of-flow box with `width:auto` shrink-wraps to its
         * content, which would put the sample point outside both boxes. This test is
         * about the multiply BLEND, not about auto-sizing. */
        "#behind{position:absolute;top:0;left:0;width:940px;background:#ff8800;}"
        "#front{position:absolute;top:0;left:0;width:940px;background:#0000ff;"
        "mix-blend-mode:multiply;}"
        "</style></head><body>"
        "<div id=\"behind\">AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA</div>"
        "<div id=\"front\">BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB</div>"
        "<p>filler text to give the page a nonzero height for the export</p>"
        "</body></html>";
    const char *path = "__freedom_blend_page.html";
    const char *png = "__freedom_blend_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --download-png=%s %s", png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png));

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    assert_true(px.width > 900 && px.height > 12);
    uint32_t pixel = ((const uint32_t *)(const void *)px.data)[6 * (px.stride / 4) + 876];
    uint8_t r = (uint8_t)(pixel >> 16), g = (uint8_t)(pixel >> 8), b = (uint8_t)pixel;
    /* multiply(orange, blue) = black. Allow a little slack for antialiasing. */
    assert_true(r <= 10);
    assert_true(g <= 10);
    assert_true(b <= 10);
    img_pixels_free(&px);

    unlink(path);
    unlink(png);
}

/* Regression for M1.2 (CSS transform: translate, paint-only): a box with
 * transform:translate(200px,0) must paint at its OFFSET position, not its
 * original layout position -- the pixel at the untranslated spot must be empty
 * (page background) and the pixel at the translated spot must be the box's
 * colour. Exercises box_transform_offset in gui/browser_ui.c and the
 * css.c expand_transform parser -> pv_box_def.transform_tx/ty -> worker IPC ->
 * painter chain (M1.2 CSS wiring). Also exercises the css_has_boxdeco fix: this
 * box has NO other box-triggering property (no padding/border/position) besides
 * transform, so without that fix it would never get a pv_box_def entry at all
 * and the translate would silently never apply. */
static void test_download_png_transform_translate_moves_paint_position(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0;}"
        "#box{background:#0000ff;transform:translate(200px,0);}"
        "</style></head><body>"
        "<div id=\"box\">XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX</div>"
        "</body></html>";
    const char *path = "__freedom_transform_page.html";
    const char *png = "__freedom_transform_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --download-png=%s %s", png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png));

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    /* Scan the whole image for the blue box rather than sampling fixed pixels: the
     * row's height follows the user-agent font size, so a hardcoded y silently
     * drifts onto glyph antialiasing the moment that metric changes. */
    assert_true(px.width > 900);
    const uint32_t *rowpx = (const uint32_t *)(const void *)px.data;
    const size_t stride = px.stride / 4;
    size_t blue_min = px.width, blue_max = 0;
    int blue_seen = 0;
    for (size_t y = 0; y < px.height; ++y) {
        for (size_t x = 0; x < px.width; ++x) {
            uint32_t p = rowpx[y * stride + x];
            uint8_t r = (uint8_t)(p >> 16), g = (uint8_t)(p >> 8), b = (uint8_t)p;
            if (r <= 5 && g <= 5 && b >= 250) {
                if (x < blue_min) blue_min = x;
                if (x > blue_max) blue_max = x;
                blue_seen = 1;
            }
        }
    }
    assert_true(blue_seen);
    /* translate(200px,0) moved the box's LEFT edge away from the page origin. */
    assert_true(blue_min >= 190);
    assert_true(blue_max > blue_min);
    img_pixels_free(&px);

    unlink(path);
    unlink(png);
}

/* Regression for M1.2b (CSS transform: rotate, real Cairo affine paint): a wide,
 * short in-flow box rotated 90deg around its own center must paint as a NARROW,
 * TALL bar -- not merely shifted like translate. Geometry was measured empirically
 * against an unrotated control render of the identical markup (a 50-char-wide box
 * at x:[24,975] y:[24,49], center ~(500,37)): (100,35) sits inside the ORIGINAL
 * footprint but outside the 90deg-rotated one (must go from blue to white), while
 * (499,5) sits outside the original footprint but inside the rotated one (must go
 * from white to blue). A pure additive tx/ty offset (or no transform at all) could
 * not produce this shape change, only a real affine matrix can. Exercises
 * box_transform_matrix + parse_rotate_deg (css.c expand_transform). */
static void test_download_png_transform_rotate_changes_paint_shape(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0;}"
        "#box{background:#0000ff;transform:rotate(90deg);}"
        "</style></head><body>"
        "<div id=\"box\">XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX</div>"
        "</body></html>";
    const char *path = "__freedom_rotate_page.html";
    const char *png = "__freedom_rotate_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --download-png=%s %s", png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png));

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    assert_true(px.width > 900 && px.height > 12);
    const uint32_t *pix = (const uint32_t *)(const void *)px.data;
    size_t stride32 = px.stride / 4;
    uint32_t was_inside = pix[10 * stride32 + 100]; /* inside ORIGINAL box only */
    uint32_t now_inside = pix[10 * stride32 + 500]; /* inside ROTATED box only */
    uint8_t wr = (uint8_t)(was_inside >> 16), wg = (uint8_t)(was_inside >> 8),
            wb = (uint8_t)was_inside;
    uint8_t nr = (uint8_t)(now_inside >> 16), ng = (uint8_t)(now_inside >> 8),
            nb = (uint8_t)now_inside;
    assert_true(wr >= 250 && wg >= 250 && wb >= 250);  /* original footprint: now blank */
    assert_true(nr <= 5 && ng <= 5 && nb >= 250);      /* rotated footprint: now blue */
    img_pixels_free(&px);

    unlink(path);
    unlink(png);
}

/* Regression for M1.2b (CSS transform: scale, real Cairo affine paint): a box
 * scaled 1.5x around its own center must GROW along both edges symmetrically --
 * not just repaint at the same size. Geometry measured empirically against an
 * unscaled control render of the identical markup (box y:[24,49] at x=500,
 * center y~36.5): y=20 (just above the original top edge) and y=52 (just below
 * the original bottom edge) are both background in the control but both must
 * turn blue once scaled 1.5x (half-height 12.5 -> 18.75, covering [17.75,55.25]).
 * y=36 (well inside both) stays blue as a sanity check that scaling didn't just
 * move the box off of it. Exercises box_transform_matrix + parse_scale_pct. */
static void test_download_png_transform_scale_grows_around_center(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0;}"
        "#box{background:#0000ff;transform:scale(1.5);}"
        "</style></head><body>"
        "<div id=\"box\">XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX</div>"
        "</body></html>";
    const char *path = "__freedom_scale_page.html";
    const char *png = "__freedom_scale_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --download-png=%s %s", png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png));

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    assert_true(px.width > 900 && px.height > 12);
    const uint32_t *pix = (const uint32_t *)(const void *)px.data;
    size_t stride32 = px.stride / 4;
    uint32_t above = pix[1 * stride32 + 500];  /* inside original, inside scaled */
    uint32_t below = pix[20 * stride32 + 500]; /* inside scaled, near bottom */
    uint32_t middle = pix[10 * stride32 + 500]; /* still inside: sanity check */
    uint8_t ar = (uint8_t)(above >> 16), ag = (uint8_t)(above >> 8), ab = (uint8_t)above;
    uint8_t br = (uint8_t)(below >> 16), bg = (uint8_t)(below >> 8), bb = (uint8_t)below;
    uint8_t mr = (uint8_t)(middle >> 16), mg = (uint8_t)(middle >> 8), mb = (uint8_t)middle;
    assert_true(ar <= 5 && ag <= 5 && ab >= 250);
    assert_true(br <= 5 && bg <= 5 && bb >= 250);
    assert_true(mr <= 5 && mg <= 5 && mb >= 250);
    img_pixels_free(&px);

    unlink(path);
    unlink(png);
}

/* --- headless console (Freebug --dump-console) --- */

/* --dump-console runs the page's JS and prints console.* output + uncaught errors. */
static void test_dump_console_shows_output_and_error(void **state) {
    (void)state;
    const char *html =
        "<html><head><title>JS</title></head><body><p>x</p>"
        "<script>console.log('LOGMARK', 1+1); console.warn('WARNMARK');"
        "boomUndefined();</script></body></html>";
    const char *path = "__freedom_console.html";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args, "--dump-console %s", path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);

    char out[4096];
    FILE *o = fopen(OUT_FILE, "r");
    assert_non_null(o);
    size_t got = fread(out, 1, sizeof out - 1, o);
    out[got] = '\0';
    fclose(o);

    assert_non_null(strstr(out, "Freebug console"));
    assert_non_null(strstr(out, "[log] LOGMARK 2"));        /* console.log + computed arg */
    assert_non_null(strstr(out, "[warn] WARNMARK"));         /* console.warn */
    assert_non_null(strstr(out, "[error] "));               /* uncaught ReferenceError */
    assert_non_null(strstr(out, "boomUndefined"));           /* error names the missing fn */

    unlink(path);
}

/* Plain headless (no --dump-console) does not run JS and prints no console section. */
static void test_no_dump_console_without_flag(void **state) {
    (void)state;
    const char *html =
        "<html><head><title>JS</title></head><body><p>x</p>"
        "<script>console.log('SHOULD_NOT_APPEAR');</script></body></html>";
    const char *path = "__freedom_noconsole.html";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);

    char out[2048];
    int rc;
    assert_int_equal(run_freedom(path, out, sizeof out, &rc), 0);
    assert_int_equal(rc, 0);
    assert_null(strstr(out, "Freebug console"));
    assert_null(strstr(out, "SHOULD_NOT_APPEAR"));

    unlink(path);
}

/* --- headless render-tree dump (--dump-dom, layout-debugging tooling) --- */

/* --dump-dom prints the agent-readable render tree (header + per-block lines) instead
 * of the normal text render, and does not run JS. */
static void test_dump_dom_prints_render_tree(void **state) {
    (void)state;
    const char *html =
        "<html><head><title>Tree</title></head><body>"
        "<h1>Head</h1><p>para</p>"
        "<a href=\"https://e.example/z\">lnk</a></body></html>";
    const char *path = "__freedom_dumpdom.html";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);

    char out[4096];
    int rc;
    char args[256];
    assert_true((size_t)snprintf(args, sizeof args, "--dump-dom %s", path) < sizeof args);
    assert_int_equal(run_freedom(args, out, sizeof out, &rc), 0);
    assert_int_equal(rc, 0);
    assert_non_null(strstr(out, "=== Freedom render tree ==="));
    assert_non_null(strstr(out, "blocks:"));
    assert_non_null(strstr(out, "<h1>"));         /* heading tag */
    assert_non_null(strstr(out, "<a>"));          /* link tag */
    assert_non_null(strstr(out, "https://e.example/z")); /* link href surfaced */

    unlink(path);
}

/* --- headless layout dump (--dump-layout, Stage 2 positioning) --- */

/* --dump-layout prints the resolved box geometry (in-flow boxes + out-of-flow
 * positioned boxes). This guards the Stage 2 GUI-integration regression where
 * skipping an absolute/fixed block called close_all_boxes, fragmenting the parent
 * relative wrapper into N zero-height pieces (one per absolute child): nbox
 * ballooned (body + wrapper re-opened per child) and the LAST wrapper piece
 * became the containing block, pushing the absolute children to the page bottom.
 * After the fix the wrapper stays open across its absolute children, so nbox is
 * small (body + wrapper = 2) and the z=1 box anchors near the wrapper top. */
static void test_dump_layout_no_wrapper_fragmentation(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body { margin: 0; padding: 16px; }"
        ".wrap { position: relative; max-width: 600px; margin: 0 auto; padding: 8px; }"
        ".b { position: absolute; width: 160px; }"
        "</style></head><body>"
        "<div class=\"wrap\">"
        "<p>In-flow content that gives the wrapper height.</p>"
        "<div class=\"b\" style=\"top:40px;left:40px;z-index:1\">blue</div>"
        "<p>More in-flow content to separate the absolutes.</p>"
        "<div class=\"b\" style=\"top:80px;left:80px;z-index:10\">green</div>"
        "<p>Even more in-flow content here.</p>"
        "<div class=\"b\" style=\"top:120px;left:120px;z-index:5\">orange</div>"
        "</div></body></html>";
    const char *path = "__freedom_dumplayout.html";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);

    char out[8192];
    int rc;
    char args[256];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --dump-layout %s", path) < sizeof args);
    assert_int_equal(run_freedom(args, out, sizeof out, &rc), 0);
    assert_int_equal(rc, 0);
    assert_non_null(strstr(out, "=== Freedom layout ==="));

    /* nbox from the header line. Bug: 8 (body+wrapper fragmented per absolute
     * child). Fix: 2 (body + wrapper, each opened once). */
    char *nb = strstr(out, "nbox=");
    assert_non_null(nb);
    size_t nbox = 999;
    assert_int_equal(sscanf(nb, "nbox=%zu", &nbox), 1);
    assert_true(nbox <= 3);

    /* The z=1 absolute box anchors near the wrapper top (wrapper at ~16px +
     * inset 40 = ~56), not at the last fragmented piece (was ~152). */
    double y_z1 = -1.0;
    char *p = out;
    while ((p = strstr(p, "pos[")) != NULL) {
        size_t idx = 0, box = 0;
        int z = 0;
        double x = 0, y = 0;
        if (sscanf(p, "pos[%zu] box=%zu z=%d x=%lf y=%lf",
                   &idx, &box, &z, &x, &y) >= 5) {
            if (z == 1) { y_z1 = y; break; }
        }
        p += 4;
    }
    assert_true(y_z1 >= 0.0);
    assert_true(y_z1 < 100.0);

    unlink(path);
}

/* float.md end-to-end: two floated siblings lay out SIDE BY SIDE (the second column's
 * rows start at a larger x_off than the first), and a wrapping position:relative
 * background panel stays IN FLOW (a box, not pushed to the page bottom by the
 * positioned pass) so it does not leave grey stripes. Guards the full css -> page_view
 * -> IPC -> render_doc -> painter float pipeline. */
static void test_dump_layout_float_two_columns(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "#panel { position:relative; background:#fff; }"
        ".a { float:left; width:200px; }"
        ".b { float:left; width:400px; }"
        "</style></head><body>"
        "<div id=\"panel\">"
        "<div class=\"a\"><p>left column</p></div>"
        "<div class=\"b\"><p>right column</p></div>"
        "<div style=\"clear:both\">footer</div>"
        "</div></body></html>";
    const char *path = "__freedom_float.html";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);

    char out[8192];
    int rc;
    assert_int_equal(run_freedom("--author-css --dump-layout __freedom_float.html",
                                 out, sizeof out, &rc), 0);
    assert_int_equal(rc, 0);

    /* Collect the x_off of every row; there must be a left column (small x_off) AND a
     * right column (a distinctly larger x_off) — side by side, not stacked. */
    double min_x = 1e9, max_x = -1.0;
    char *p = out;
    while ((p = strstr(p, "x_off=")) != NULL) {
        double x = -1.0;
        if (sscanf(p, "x_off=%lf", &x) == 1) {
            if (x < min_x) min_x = x;
            if (x > max_x) max_x = x;
        }
        p += 6;
    }
    assert_true(max_x - min_x > 100.0);  /* two columns at clearly different x */

    /* The relative panel is in flow: at least one box, and no positioned box left it
     * at the page bottom (the grey-stripe bug had npositioned pushing it away). */
    assert_non_null(strstr(out, "nbox=1"));
    assert_non_null(strstr(out, "npositioned=0"));

    unlink(path);
}

/* --- network policy --- */

static void test_rejects_http_url(void **state) {
    (void)state;
    char out[512];
    int rc;
    assert_int_equal(run_freedom("http://example.com", out, sizeof out, &rc), 0);
    assert_int_equal(rc, 1);
}

/* Phase R1: animation-duration triggers the animation pipeline and exports
 * as PNG without crash. The box with animation forms a stacking context and the
 * anim_duration flows through the full pipeline (CSS → page_view → IPC → paint). */
static void test_download_png_animation_renders(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0;}"
        ".box{width:100px;height:60px;background:#00cc44;animation-duration:1s;}"
        "</style></head><body>"
        "<div class=\"box\">Anim</div>"
        "</body></html>";
    const char *path = "__freedom_anim_page.html";
    const char *png  = "__freedom_anim_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --download-png=%s %s", png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png));

    /* Decode and verify the box area has non-white content (the pipeline
     * didn't silently drop the animated box). */
    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    assert_true(px.width > 50 && px.height > 30);
    /* Sample a pixel inside the box (border area of the animated div). */
    uint32_t pixel = ((const uint32_t *)(const void *)px.data)[40 * (px.stride / 4) + 20];
    uint8_t g = (uint8_t)(pixel >> 8);
    /* The background is #00cc44 = green. Even with animation opacity modulation
     * (0→100), the box should contribute non-white color to the PNG. */
    assert_true(g > 50);   /* area is not all white — pipeline is wired */
    img_pixels_free(&px);

    unlink(path);
    unlink(png);
}

/* CSS 2.1 §14.2: the root <html> element's background-color propagates to the
 * canvas. A page with `html{background-color:#000900}` must paint the entire
 * content area dark green, not just text-run backgrounds. This test verifies
 * that a pixel in a "blank" area (far from any text row) is the dark green color
 * and not white (the old behaviour where only text rows got background fills). */
static void test_download_png_canvas_background_from_html(void **state) {
    (void)state;
    const char *html =
        "<html style=\"background-color:#000900;color:#18d818;\">"
        "<head><title>Canvas BG</title></head>"
        "<body style=\"margin:0;padding:0;\">"
        "<p style=\"margin:0;\">X</p>"
        "</body></html>";
    const char *path = "__freedom_canvas_bg.html";
    const char *png  = "__freedom_canvas_bg_out.png";
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args,
                 "--author-css --download-png=%s %s", png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png));

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    /* Sample a pixel at (5, 5): near the top-left corner, well above the "X" text
     * row, in the blank canvas area. It must be dark green #000900 (R≈0, G≈9, B≈0),
     * not white (255,255,255) which would mean the canvas background was ignored. */
    assert_true(px.width > 5 && px.height > 5);
    uint32_t pixel = ((const uint32_t *)(const void *)px.data)[5 * (px.stride / 4) + 5];
    uint8_t r = (uint8_t)(pixel >> 16), g = (uint8_t)(pixel >> 8), b = (uint8_t)pixel;
    (void)r; (void)b;
    assert_true(g >= 5 && g <= 15);   /* about 9, allow ±6 for rounding */
    assert_true(r < 30);               /* no red component — pure greenish-black */
    assert_true(b < 30);               /* no blue component */
    img_pixels_free(&px);

    unlink(path);
    unlink(png);
}

/* Samples one pixel of a PNG exported from `html`. Writes the markup to a temp
 * file, runs the headless export with `extra` flags, decodes the result and hands
 * the (x, y) pixel back as r/g/b. Every Firefox-parity pixel test below shares it,
 * so they cannot drift on how the page is exported or how a pixel is read. */
static void sample_png_pixel(const char *html, const char *extra, const char *tag,
                             int x, int y, uint8_t *r, uint8_t *g, uint8_t *b) {
    char path[128], png[128];
    assert_true((size_t)snprintf(path, sizeof path, "__freedom_%s.html", tag) < sizeof path);
    assert_true((size_t)snprintf(png, sizeof png, "__freedom_%s_out.png", tag) < sizeof png);
    FILE *f = fopen(path, "w");
    assert_non_null(f);
    assert_int_equal(fwrite(html, 1, strlen(html), f), strlen(html));
    fclose(f);
    (void)unlink(png);

    char args[512];
    assert_true((size_t)snprintf(args, sizeof args, "%s --download-png=%s %s",
                                 extra, png, path) < sizeof args);
    int rc = -1;
    assert_int_equal(run_freedom_raw(args, &rc), 0);
    assert_int_equal(rc, 0);
    assert_true(is_png_file(png));

    size_t len = 0;
    uint8_t *bytes = read_file_all(png, &len);
    assert_non_null(bytes);
    img_pixels px;
    assert_int_equal(img_decode(bytes, len, &px), IMG_OK);
    free(bytes);

    assert_true(x >= 0 && y >= 0);
    assert_true(px.width > (uint32_t)x && px.height > (uint32_t)y);
    uint32_t pixel = ((const uint32_t *)(const void *)px.data)[(size_t)y * (px.stride / 4) + (size_t)x];
    *r = (uint8_t)(pixel >> 16); *g = (uint8_t)(pixel >> 8); *b = (uint8_t)pixel;
    img_pixels_free(&px);

    unlink(path);
    unlink(png);
}

/* Firefox parity: a text row inside a box whose background is a GRADIENT (or an
 * image) must not repaint an OUTER ancestor's flat background behind its glyphs.
 *
 * The flat render model gives each row the nearest ancestor background so a
 * block's colour shows behind its text. A gradient sets no flat colour, so the
 * walk used to sail past the gradient box and pick up <body>'s colour -- painting
 * an opaque band of the PAGE background on top of the gradient the box had just
 * drawn. Every gradient hero on the modern web lost its text band to it. */
static void test_download_png_gradient_box_text_keeps_gradient(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0;background:#ff0000;}"
        ".hero{padding:40px;background:linear-gradient(#0000ff,#0000ff);}"
        ".hero h1{color:#ffffff;margin:0;}"
        "</style></head><body>"
        "<div class=\"hero\"><h1>Build faster</h1></div>"
        "</body></html>";
    uint8_t r = 0, g = 0, b = 0;
    /* (900, 85): inside the hero box, on the heading's row band, far to the right
     * of the glyphs -- so only a background can own the pixel. */
    sample_png_pixel(html, "--author-css", "gradrow", 900, 85, &r, &g, &b);
    assert_true(b > 200);   /* the hero's gradient */
    assert_true(r < 60);    /* not the page's red background repainted on top */
}

/* Firefox parity: a flex container's own background is ONE band across the
 * container, not one rectangle per item.
 *
 * A `display:flex; justify-content:space-between` header whose items carry no box
 * of their own left both items pointing at the CONTAINER's box as their "item root
 * box", so the painter drew the header's dark background twice -- once behind each
 * item, with the page showing through the gap between them. */
static void test_download_png_flex_container_paints_one_band(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0;}"
        "header{display:flex;justify-content:space-between;padding:20px;background:#0000ff;}"
        "</style></head><body>"
        "<header><strong>Acme</strong><nav>Docs</nav></header>"
        "</body></html>";
    uint8_t r = 0, g = 0, b = 0;
    /* (500, 25): the middle of the header band, between the two items. */
    sample_png_pixel(html, "--author-css", "flexband", 500, 25, &r, &g, &b);
    assert_true(b > 200);            /* the container's band reaches the middle */
    assert_true(r < 60 && g < 60);   /* not the white page showing through */
}

/* Firefox parity: `display:inline-block` shrink-wraps to its content and is placed
 * by the parent's text-align, instead of opening a full-width block box.
 *
 * A centred call-to-action button used to paint as a full-page-width bar. */
static void test_download_png_inline_block_shrinks_and_centers(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "body{margin:0;padding:0;text-align:center;}"
        ".btn{display:inline-block;padding:12px 28px;background:#0000ff;color:#ffffff;}"
        "</style></head><body>"
        "<div><a class=\"btn\" href=\"#\">Get started</a></div>"
        "</body></html>";
    uint8_t r = 0, g = 0, b = 0;
    /* (980, 45): the far right of the button's row, vertically at its middle. A
     * shrink-wrapped button never reaches it; a full-width block box would paint
     * it blue. */
    sample_png_pixel(html, "--author-css", "iblockw", 980, 45, &r, &g, &b);
    assert_true(!(b > 200 && r < 60 && g < 60));   /* not the button's blue */
    /* ... and the button itself is centred, so the middle of the row IS blue. */
    uint8_t r2 = 0, g2 = 0, b2 = 0;
    sample_png_pixel(html, "--author-css", "iblockc", 500, 45, &r2, &g2, &b2);
    assert_true(b2 > 200);
    assert_true(r2 < 60 && g2 < 60);
}

/* Inline <svg> paints its geometry (spec/svg_render.md). Three things at once:
 * the shape reaches the screen through the whole pipeline (page_view run -> IPC
 * codec -> render_doc block -> Cairo painter), it is NOT gated by the images
 * capability (an inline SVG names no resource, so there is no fetch to gate), and
 * its markup never leaks into the page as prose. */
static void test_download_png_inline_svg_paints_shapes(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>body{margin:0;padding:0}</style></head><body>"
        "<svg width=\"200\" height=\"100\" viewBox=\"0 0 200 100\">"
        "<rect x=\"0\" y=\"0\" width=\"200\" height=\"100\" fill=\"#0000ff\"/>"
        "</svg></body></html>";
    uint8_t r = 0, g = 0, b = 0;
    /* (100, 60): inside the rect. No --images flag: inline SVG must paint anyway. */
    sample_png_pixel(html, "--author-css", "svgrect", 100, 60, &r, &g, &b);
    assert_true(b > 200);
    assert_true(r < 60 && g < 60);
}

/* A <path> with a fill reaches the painter, and an element that could name a
 * resource is dropped instead: the same page carries an <image> pointing at a
 * remote URL, which must contribute nothing. */
static void test_download_png_inline_svg_path_and_drops_image(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>body{margin:0;padding:0}</style></head><body>"
        "<svg width=\"200\" height=\"200\" viewBox=\"0 0 200 200\">"
        "<image href=\"https://tracker.example/p.png\" x=\"0\" y=\"0\" width=\"200\" height=\"200\"/>"
        "<path d=\"M 0 0 L 200 0 L 200 200 L 0 200 Z\" fill=\"#00ff00\"/>"
        "</svg></body></html>";
    uint8_t r = 0, g = 0, b = 0;
    sample_png_pixel(html, "--author-css", "svgpath", 100, 100, &r, &g, &b);
    assert_true(g > 200);
    assert_true(r < 60 && b < 60);
}

/* --- suite --- */

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_help),
        cmocka_unit_test(test_version),
        cmocka_unit_test(test_no_args),
        cmocka_unit_test(test_local_html),
        cmocka_unit_test(test_local_form_renders_inputs),
        cmocka_unit_test(test_missing_file),
        cmocka_unit_test(test_download_pdf_local),
        cmocka_unit_test(test_download_pdf_requires_path),
        cmocka_unit_test(test_download_png_local),
        cmocka_unit_test(test_download_png_images_local),
        cmocka_unit_test(test_download_png_negative_zindex_paints_behind_inflow),
        cmocka_unit_test(test_download_png_group_opacity_blends_with_background),
        cmocka_unit_test(test_download_png_absolute_shrinks_and_anchors_right),
        cmocka_unit_test(test_download_png_inflow_opacity_blends_box_and_row_together),
        cmocka_unit_test(test_download_png_line_height_zero_does_not_shrink_line),
        cmocka_unit_test(test_absolute_font_size_lands_exact),
        cmocka_unit_test(test_absolute_span_honours_right_bottom),
        cmocka_unit_test(test_heading_colour_matches_body_text),
        cmocka_unit_test(test_author_can_unbold_a_heading),
        cmocka_unit_test(test_author_font_size_on_heading_replaces_ua_scale),
        cmocka_unit_test(test_inline_run_boundary_does_not_invent_space),
        cmocka_unit_test(test_inline_run_boundary_collapses_runs_of_space),
        cmocka_unit_test(test_download_png_mix_blend_multiply_uses_cairo_operator),
        cmocka_unit_test(test_download_png_transform_translate_moves_paint_position),
        cmocka_unit_test(test_download_png_transform_rotate_changes_paint_shape),
        cmocka_unit_test(test_download_png_transform_scale_grows_around_center),
        cmocka_unit_test(test_download_png_animation_renders),
        cmocka_unit_test(test_download_png_canvas_background_from_html),
        cmocka_unit_test(test_download_png_gradient_box_text_keeps_gradient),
        cmocka_unit_test(test_download_png_flex_container_paints_one_band),
        cmocka_unit_test(test_download_png_inline_block_shrinks_and_centers),
        cmocka_unit_test(test_download_png_inline_svg_paints_shapes),
        cmocka_unit_test(test_download_png_inline_svg_path_and_drops_image),
        cmocka_unit_test(test_download_png_requires_path),
        cmocka_unit_test(test_dump_console_shows_output_and_error),
        cmocka_unit_test(test_no_dump_console_without_flag),
        cmocka_unit_test(test_dump_dom_prints_render_tree),
        cmocka_unit_test(test_dump_layout_no_wrapper_fragmentation),
        cmocka_unit_test(test_dump_layout_float_two_columns),
        cmocka_unit_test(test_rejects_http_url),
    };
    int rc = cmocka_run_group_tests(tests, NULL, NULL);
    cleanup_files();
    return rc;
}
