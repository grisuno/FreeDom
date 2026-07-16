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

    /* (500, 40): well inside both boxes' shared row, far from either single-glyph
     * label so font rendering differences can't flip the sampled colour. */
    assert_true(px.width > 500 && px.height > 40);
    uint32_t pixel = ((const uint32_t *)(const void *)px.data)[40 * (px.stride / 4) + 500];
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
        "#box{position:absolute;top:0;left:0;background:#0000ff;opacity:0.5;}"
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

    /* (500, 30): inside the box's row, far from the single-glyph "X" label. */
    assert_true(px.width > 500 && px.height > 30);
    uint32_t pixel = ((const uint32_t *)(const void *)px.data)[30 * (px.stride / 4) + 500];
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
        "#behind{position:absolute;top:0;left:0;background:#ff8800;}"
        "#front{position:absolute;top:0;left:0;background:#0000ff;"
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

    assert_true(px.width > 900 && px.height > 30);
    uint32_t pixel = ((const uint32_t *)(const void *)px.data)[30 * (px.stride / 4) + 900];
    uint8_t r = (uint8_t)(pixel >> 16), g = (uint8_t)(pixel >> 8), b = (uint8_t)pixel;
    /* multiply(orange, blue) = black. Allow a little slack for antialiasing. */
    assert_true(r <= 10);
    assert_true(g <= 10);
    assert_true(b <= 10);
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
        cmocka_unit_test(test_download_png_inflow_opacity_blends_box_and_row_together),
        cmocka_unit_test(test_download_png_mix_blend_multiply_uses_cairo_operator),
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
