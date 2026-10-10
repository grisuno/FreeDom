/*
 * TDD suite for webfont_load (trusted-side @font-face fetch-and-register).
 *
 * The fetcher is a stub (no network): it serves host font bytes read from disk
 * for https URLs, so the EMBEDDED cases run hermetically anywhere. Cases that
 * need real font bytes skip() when no host TrueType file exists (same doctrine
 * as test_text_shape: green either way, strong when fonts exist).
 *
 * Build: make test
 * ASan:  make asan
 */

#define _POSIX_C_SOURCE 200809L

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include "webfont_load.h"
#include "webfont.h"
#include "text_shape.h"
#include "css.h"

typedef struct stub {
    const unsigned char *bytes;
    size_t               nbytes;
    int                  calls;
    int                  fail_first;   /* first call 404s, rest 200 */
    char                 last_url[512];
} stub;

static int stub_fetch(void *ctx, const char *url,
                      int *out_status, char **out_body, size_t *out_len,
                      char **out_ctype) {
    stub *s = (stub *)ctx;
    s->calls++;
    size_t ul = strlen(url);
    if (ul >= sizeof s->last_url) ul = sizeof s->last_url - 1;
    memcpy(s->last_url, url, ul);
    s->last_url[ul] = '\0';
    if (s->fail_first && s->calls == 1) {
        *out_status = 404;
        *out_body = NULL;
        *out_len = 0;
        *out_ctype = NULL;
        return 0;
    }
    *out_status = 200;
    *out_body = (char *)malloc(s->nbytes);
    if (*out_body == NULL) return -1;
    memcpy(*out_body, s->bytes, s->nbytes);
    *out_len = s->nbytes;
    *out_ctype = strdup("font/woff");
    if (*out_ctype == NULL) { free(*out_body); return -1; }
    return 0;
}

static unsigned char *read_host_font(size_t *out_n) {
    static const char *paths[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
    };
    for (size_t i = 0; i < sizeof paths / sizeof *paths; ++i) {
        FILE *f = fopen(paths[i], "rb");
        if (f == NULL) continue;
        if (fseek(f, 0, SEEK_END) != 0) { fclose(f); continue; }
        long sz = ftell(f);
        if (sz <= 0 || (size_t)sz > WF_MAX_FACE_BYTES) { fclose(f); continue; }
        if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); continue; }
        unsigned char *b = (unsigned char *)malloc((size_t)sz);
        if (b == NULL) { fclose(f); return NULL; }
        if (fread(b, 1, (size_t)sz, f) != (size_t)sz) {
            free(b);
            fclose(f);
            continue;
        }
        fclose(f);
        *out_n = (size_t)sz;
        return b;
    }
    return NULL;
}

/* Minimal base64 encoder (test-only; data: URL construction). */
static char *test_b64(const unsigned char *in, size_t n) {
    static const char tab[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t o = ((n + 2) / 3) * 4;
    char *s = (char *)malloc(o + 1);
    if (s == NULL) return NULL;
    size_t w = 0;
    for (size_t i = 0; i < n; i += 3) {
        unsigned a = in[i];
        unsigned b = (i + 1 < n) ? in[i + 1] : 0;
        unsigned c = (i + 2 < n) ? in[i + 2] : 0;
        unsigned v = (a << 16) | (b << 8) | c;
        s[w++] = tab[(v >> 18) & 63];
        s[w++] = tab[(v >> 12) & 63];
        s[w++] = (i + 1 < n) ? tab[(v >> 6) & 63] : '=';
        s[w++] = (i + 2 < n) ? tab[v & 63] : '=';
    }
    s[w] = '\0';
    return s;
}

static void test_null_args(void **state) {
    (void)state;
    stub s;
    memset(&s, 0, sizeof s);
    assert_int_equal(wf_load_document(NULL, &s, "https://x/", NULL, 0, "", 0), -1);
    /* No page URL (local file): data:-only mode, empty input registers none. */
    assert_int_equal(
        wf_load_document(stub_fetch, &s, NULL, NULL, 0, "", 0), 0);
    /* Untrusted pages pass no fetcher: nothing happens, nothing registered. */
    assert_int_equal(
        wf_load_document(NULL, NULL, "https://x/", NULL, 0, "", 0), -1);
}

static void test_https_stub_registers(void **state) {
    (void)state;
    size_t n = 0;
    unsigned char *bytes = read_host_font(&n);
    if (bytes == NULL) { skip(); }
    stub s;
    memset(&s, 0, sizeof s);
    s.bytes = bytes;
    s.nbytes = n;
    const char *html =
        "<html><head><style>"
        "@font-face{font-family:'Stub';src:url(https://cdn.example/f.woff) format('woff');}"
        "</style></head><body><p>hi</p></body></html>";
    int rc = wf_load_document(stub_fetch, &s, "https://site.example/",
                              NULL, 0, html, strlen(html));
    assert_int_equal(rc, 1);
    assert_int_equal(s.calls, 1);
    assert_string_equal(s.last_url, "https://cdn.example/f.woff");
    /* The registered face shapes through its hash. */
    tsh_font wf = { .family = CSS_FF_SERIF, .bold = 0, .italic = 0,
                    .wfh = wf_name_hash("Stub", 4) };
    assert_true(tsh_measure(&wf, 16.0, "ABCD", 4) > 0.0);
    tsh_webfont_clear();
    free(bytes);
}

static void test_woff2_never_fetched(void **state) {
    (void)state;
    stub s;
    memset(&s, 0, sizeof s);
    static const unsigned char dummy[8] = { 0, 1, 0, 0, 0, 0, 0, 0 };
    s.bytes = dummy;
    s.nbytes = sizeof dummy;
    const char *html =
        "<html><head><style>"
        "@font-face{font-family:'W2';src:url(https://cdn.example/f.woff2) format('woff2');}"
        "</style></head><body></body></html>";
    assert_int_equal(wf_load_document(stub_fetch, &s, "https://site.example/",
                                      NULL, 0, html, strlen(html)),
                     0);
    assert_int_equal(s.calls, 0);
    tsh_webfont_clear();
}

static void test_fallback_second_url(void **state) {
    (void)state;
    size_t n = 0;
    unsigned char *bytes = read_host_font(&n);
    if (bytes == NULL) { skip(); }
    stub s;
    memset(&s, 0, sizeof s);
    s.bytes = bytes;
    s.nbytes = n;
    s.fail_first = 1;
    const char *html =
        "<html><head><style>"
        "@font-face{font-family:'Fb';src:url(https://cdn.example/a.woff) format('woff'),"
        "url(https://cdn.example/b.woff) format('woff');}"
        "</style></head><body></body></html>";
    int rc = wf_load_document(stub_fetch, &s, "https://site.example/",
                              NULL, 0, html, strlen(html));
    assert_int_equal(rc, 1);
    assert_int_equal(s.calls, 2);
    assert_string_equal(s.last_url, "https://cdn.example/b.woff");
    tsh_webfont_clear();
    free(bytes);
}

static void test_first_wins(void **state) {
    (void)state;
    size_t n = 0;
    unsigned char *bytes = read_host_font(&n);
    if (bytes == NULL) { skip(); }
    stub s;
    memset(&s, 0, sizeof s);
    s.bytes = bytes;
    s.nbytes = n;
    const char *html =
        "<html><head><style>"
        "@font-face{font-family:'Fw';src:url(https://cdn.example/1.woff);}"
        "@font-face{font-family:'Fw';src:url(https://cdn.example/2.woff);}"
        "</style></head><body></body></html>";
    assert_int_equal(wf_load_document(stub_fetch, &s, "https://site.example/",
                                      NULL, 0, html, strlen(html)),
                     1);
    assert_int_equal(s.calls, 1);
    assert_string_equal(s.last_url, "https://cdn.example/1.woff");
    tsh_webfont_clear();
    free(bytes);
}

static void test_extern_sheet_relative_url(void **state) {
    (void)state;
    size_t n = 0;
    unsigned char *bytes = read_host_font(&n);
    if (bytes == NULL) { skip(); }
    stub s;
    memset(&s, 0, sizeof s);
    s.bytes = bytes;
    s.nbytes = n;
    static const char css[] =
        "@font-face{font-family:'Ex';src:url(fonts/e.woff) format('woff');}";
    wf_sheet sheets[1];
    sheets[0].text = css;
    sheets[0].len = sizeof css - 1;
    sheets[0].url = "https://cdn.example/assets/a.css";
    int rc = wf_load_document(stub_fetch, &s, "https://site.example/",
                              sheets, 1, "", 0);
    assert_int_equal(rc, 1);
    assert_string_equal(s.last_url, "https://cdn.example/assets/fonts/e.woff");
    tsh_webfont_clear();
    free(bytes);
}

static void test_data_url_bad_bytes_skipped(void **state) {
    (void)state;
    const char *html =
        "<html><head><style>"
        "@font-face{font-family:'D';src:url(data:font/woff;base64,AAAAAAA);}"
        "</style></head><body></body></html>";
    stub s;
    memset(&s, 0, sizeof s);
    assert_int_equal(wf_load_document(stub_fetch, &s, "https://site.example/",
                                      NULL, 0, html, strlen(html)),
                     0);
    assert_int_equal(s.calls, 0);
    tsh_webfont_clear();
}

static void test_data_url_registers(void **state) {
    (void)state;
    size_t n = 0;
    unsigned char *bytes = read_host_font(&n);
    if (bytes == NULL) { skip(); }
    char *b64 = test_b64(bytes, n);
    assert_non_null(b64);
    size_t hlen = strlen(b64) + 256;
    char *html = (char *)malloc(hlen);
    assert_non_null(html);
    snprintf(html, hlen,
             "<html><head><style>"
             "@font-face{font-family:'Dd';src:url(data:font/woff;base64,%s);}"
             "</style></head><body></body></html>",
             b64);
    stub s;
    memset(&s, 0, sizeof s);
    int rc = wf_load_document(stub_fetch, &s, "https://site.example/",
                              NULL, 0, html, strlen(html));
    assert_int_equal(rc, 1);
    assert_int_equal(s.calls, 0);   /* local decode, no fetch */
    tsh_font wf = { .family = CSS_FF_SERIF, .bold = 0, .italic = 0,
                    .wfh = wf_name_hash("Dd", 2) };
    assert_true(tsh_measure(&wf, 16.0, "A", 1) > 0.0);
    tsh_webfont_clear();
    free(html);
    free(b64);
    free(bytes);
}

/* Local file (page_url NULL) with a trusted fetcher: a data: face registers
 * from the inline <style> with no fetch, while a relative-URL face is skipped
 * (no base to resolve against) without touching the network. */
static void test_null_page_data_only(void **state) {
    (void)state;
    size_t n = 0;
    unsigned char *bytes = read_host_font(&n);
    if (bytes == NULL) { skip(); }
    char *b64 = test_b64(bytes, n);
    free(bytes);
    if (b64 == NULL) { skip(); }
    size_t hlen = strlen(b64) + 320;
    char *html = (char *)malloc(hlen);
    if (html == NULL) { free(b64); skip(); }
    snprintf(html, hlen,
             "<html><head><style>"
             "@font-face{font-family:'Nn';src:url(data:font/woff;base64,%s);}"
             "@font-face{font-family:'Rr';src:url(fonts/r.woff) format('woff');}"
             "</style></head><body></body></html>",
             b64);
    free(b64);
    stub s;
    memset(&s, 0, sizeof s);
    int rc = wf_load_document(stub_fetch, &s, NULL, NULL, 0, html, strlen(html));
    assert_int_equal(rc, 1);
    assert_int_equal(s.calls, 0);   /* local decode only; relative never fetched */
    tsh_font wf = { .family = CSS_FF_SERIF, .bold = 0, .italic = 0,
                    .wfh = wf_name_hash("Nn", 2) };
    assert_true(tsh_measure(&wf, 16.0, "A", 1) > 0.0);
    tsh_webfont_clear();
    free(html);
}

static int teardown(void **state) {
    (void)state;
    tsh_webfont_clear();
    tsh_shutdown();
    return 0;
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_null_args),
        cmocka_unit_test(test_https_stub_registers),
        cmocka_unit_test(test_woff2_never_fetched),
        cmocka_unit_test(test_fallback_second_url),
        cmocka_unit_test(test_first_wins),
        cmocka_unit_test(test_extern_sheet_relative_url),
        cmocka_unit_test(test_data_url_bad_bytes_skipped),
        cmocka_unit_test(test_data_url_registers),
        cmocka_unit_test(test_null_page_data_only),
    };
    return cmocka_run_group_tests(tests, NULL, teardown);
}
