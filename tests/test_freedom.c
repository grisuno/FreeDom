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

/* --download-png with no PATH is a usage error (fail closed: never guess a path). */
static void test_download_png_requires_path(void **state) {
    (void)state;
    int rc = -1;
    assert_int_equal(run_freedom_raw("--download-png examples/sample.html", &rc), 0);
    assert_int_equal(rc, 2);
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
        cmocka_unit_test(test_download_png_requires_path),
        cmocka_unit_test(test_dump_console_shows_output_and_error),
        cmocka_unit_test(test_no_dump_console_without_flag),
        cmocka_unit_test(test_dump_dom_prints_render_tree),
        cmocka_unit_test(test_rejects_http_url),
    };
    int rc = cmocka_run_group_tests(tests, NULL, NULL);
    cleanup_files();
    return rc;
}
