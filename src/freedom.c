/*
 * freedom — Freedom browser entry point (Hito 5+).
 *
 * By default opens the minimal Wayland browser GUI. Use --headless to render a
 * single page to stdout. See spec/freedom.md for the CLI contract and
 * spec/browser.md for the GUI contract.
 */

#define _POSIX_C_SOURCE 200809L

#include "secure_fetch.h"
#include "tab.h"
#include "ui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_OK     0
#define EXIT_ERROR  1
#define EXIT_USAGE  2

static void print_usage(FILE *fp, const char *prog) {
    fprintf(fp, "usage: %s [--help] [--version] [--headless] [--insecure] <url-or-file>\n", prog);
    fprintf(fp, "  default: open the Wayland browser GUI\n");
    fprintf(fp, "  --headless: render the page to stdout and exit\n");
    fprintf(fp, "  --insecure: allow weak TLS certificates (headless only, explicit override)\n");
}

static int is_https_url(const char *s) {
    return strncmp(s, "https://", 8) == 0;
}

static int global_insecure = 0;

/* Reads the whole file into a NUL-terminated buffer. Caller frees with free(). */
static char *read_file(const char *path, size_t *out_len) {
    FILE *f = fopen(path, "rb");
    if (f == NULL) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    rewind(f);

    char *buf = (char *)malloc((size_t)sz + 1);
    if (buf == NULL) { fclose(f); return NULL; }
    size_t n = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    buf[n] = '\0';
    if (out_len != NULL) *out_len = n;
    return buf;
}

/* Loads html into a fresh tab and prints title + text. Returns EXIT_OK or
 * EXIT_ERROR; on error no partial output is emitted. */
static int render_page(const char *html, size_t len) {
    tab *t = NULL;
    tab_status ts = tab_open(&t);
    if (ts != TAB_OK) {
        fprintf(stderr, "freedom: failed to open tab worker (status %d)\n", (int)ts);
        return EXIT_ERROR;
    }

    tab_page page;
    memset(&page, 0, sizeof page);
    ts = tab_load(t, html, len, &page);
    if (ts != TAB_OK) {
        fprintf(stderr, "freedom: failed to load page (status %d)\n", (int)ts);
        tab_close(t);
        return EXIT_ERROR;
    }

    if (page.title != NULL && page.title_len > 0) {
        printf("%s\n\n", page.title);
    }
    if (page.text != NULL && page.text_len > 0) {
        printf("%s\n", page.text);
    }

    tab_page_free(&page);
    tab_close(t);
    return EXIT_OK;
}

static const char *sf_reason(sf_status ss) {
    switch (ss) {
        case SF_ERR_TLS_VERSION:  return "TLS version below 1.3";
        case SF_ERR_KEM_NOT_PQ:   return "key exchange is not PQ-hybrid";
        case SF_ERR_WEAK_ALGO:    return "weak certificate/key algorithm (RSA < 3072 / SHA-1)";
        case SF_ERR_CERT_INVALID: return "certificate validation failed";
        case SF_ERR_CERT_NOT_PQ:  return "strict PQ signature missing";
        case SF_ERR_NETWORK:      return "network error";
        case SF_ERR_TOO_MANY_REDIRECTS: return "too many redirects";
        default:                  return "fetch error";
    }
}

/* Fetches url with secure_fetch and renders the result. The response body is
 * consumed directly; no extra copy is made. */
static int fetch_and_render(const char *url) {
    sf_response resp;
    memset(&resp, 0, sizeof resp);

    sf_config cfg = sf_config_default();
    if (global_insecure) cfg.policy = SF_POLICY_PERMISSIVE;

    /* Follow redirects (e.g. google.com -> www.google.com), re-validating the
     * full policy on every hop. */
    sf_status ss = sf_get_follow(url, &cfg, &resp, SF_DEFAULT_MAX_REDIRECTS);
    if (ss != SF_OK) {
        fprintf(stderr, "freedom: fetch failed for '%s' (status %d: %s)\n",
                url, (int)ss, sf_reason(ss));
        sf_response_free(&resp);
        return EXIT_ERROR;
    }

    int rc = render_page((const char *)resp.body, resp.body_len);
    sf_response_free(&resp);
    return rc;
}

static int run_headless(const char *target) {
    if (is_https_url(target)) {
        return fetch_and_render(target);
    }

    size_t len = 0;
    char *html = read_file(target, &len);
    if (html == NULL) {
        fprintf(stderr, "freedom: cannot read '%s'\n", target);
        return EXIT_ERROR;
    }

    int rc = render_page(html, len);
    free(html);
    return rc;
}

int main(int argc, char **argv) {
    int headless = 0;
    const char *target = NULL;

    for (int i = 1; i < argc; ++i) {
        const char *arg = argv[i];
        if (strcmp(arg, "--help") == 0 || strcmp(arg, "-h") == 0) {
            print_usage(stdout, argv[0]);
            return EXIT_OK;
        }
        if (strcmp(arg, "--version") == 0 || strcmp(arg, "-V") == 0) {
            printf("Freedom 0.5.0\n");
            return EXIT_OK;
        }
        if (strcmp(arg, "--headless") == 0 || strcmp(arg, "-H") == 0) {
            headless = 1;
        } else if (strcmp(arg, "--insecure") == 0 || strcmp(arg, "-I") == 0) {
            global_insecure = 1;
        } else if (arg[0] == '-') {
            fprintf(stderr, "freedom: unknown option '%s'\n", arg);
            print_usage(stderr, argv[0]);
            return EXIT_USAGE;
        } else {
            target = arg;
        }
    }

    if (headless) {
        if (target == NULL) {
            print_usage(stderr, argv[0]);
            return EXIT_USAGE;
        }
        return run_headless(target);
    }

    /* GUI mode: optional start URL/file. */
    return (ui_run_browser(target) == UI_OK) ? EXIT_OK : EXIT_ERROR;
}
