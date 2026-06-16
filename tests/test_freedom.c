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

static void test_missing_file(void **state) {
    (void)state;
    char out[512];
    int rc;
    assert_int_equal(run_freedom("__freedom_missing_file.html", out, sizeof out, &rc), 0);
    assert_int_equal(rc, 1);
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
        cmocka_unit_test(test_missing_file),
        cmocka_unit_test(test_rejects_http_url),
    };
    int rc = cmocka_run_group_tests(tests, NULL, NULL);
    cleanup_files();
    return rc;
}
