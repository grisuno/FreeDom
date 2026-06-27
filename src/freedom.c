/*
 * freedom — Freedom browser entry point (Hito 5+).
 *
 * By default opens the minimal Wayland browser GUI. Use --headless to render a
 * single page to stdout. See spec/freedom.md for the CLI contract and
 * spec/browser.md for the GUI contract.
 */

#define _POSIX_C_SOURCE 200809L

#include "net_realm.h"
#include "render_doc.h"
#include "render_policy.h"
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
    fprintf(fp, "  --download-pdf=PATH: headless render to a vector PDF at PATH (implies --headless)\n");
    fprintf(fp, "  --author-css: apply author CSS (colors/sizing/line-height) in the headless render (local only)\n");
    fprintf(fp, "  --insecure: allow weak TLS certificates (headless only, explicit override)\n");
    fprintf(fp, "  --tor[=host:port]: route via a Tor SOCKS5h proxy (default 127.0.0.1:9050); reaches .onion\n");
    fprintf(fp, "  --i2p[=host:port]: route .i2p via an I2P HTTP proxy (default 127.0.0.1:4444)\n");
    fprintf(fp, "  --torify: also route ordinary clearnet through Tor (implies --tor)\n");
    fprintf(fp, "  --js[=off|allowlist|on]: page-JS policy in the GUI (default allowlist via js.conf)\n");
}

static int is_https_url(const char *s) {
    return strncmp(s, "https://", 8) == 0;
}

static int is_http_url(const char *s) {
    return strncmp(s, "http://", 7) == 0;
}

/* A plain-http overlay URL (an i2p eepsite today): fetched over the network, not a file. */
static int is_overlay_http(const char *s) {
    return is_http_url(s) && nr_realm_allows_http(nr_classify_url(s));
}

static int global_insecure = 0;

/* When non-NULL (set by --download-pdf=PATH), headless mode renders the page to a
 * vector PDF at this path instead of printing to stdout. The path is a trusted
 * local CLI argument, used verbatim. */
static const char *g_pdf_out = NULL;

/* Set by --author-css: apply author CSS (caps.css) in the headless render, so
 * author styling (colors, text-align, font-size, line-height) is visually
 * reviewable without a Wayland window. Local render only; the network image cap
 * stays off, so this never fetches or phones home. Default off (Privacy by Default). */
static int g_author_css = 0;

/* Tor/I2P routing for headless mode (off by default; opt-in via CLI flags). */
static nr_config global_net = { 0, 0, 0 };
static char global_tor_addr[64] = "127.0.0.1:9050";
static char global_i2p_addr[64] = "127.0.0.1:4444";

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

/* True if s holds only ASCII spaces/tabs (or is empty). */
static int is_blank_text(const char *s) {
    for (; *s != '\0'; ++s) {
        if (*s != ' ' && *s != '\t') return 0;
    }
    return 1;
}

/* Writes the render document as deterministic, flowing plain text for a terminal
 * and for an AI agent (content as data, never instruction). Inline runs
 * (paragraphs and links) flow onto one line and break on a block boundary;
 * headings get a leading "#"*level marker, images show their gate decision and
 * source, and notices are prefixed with "! ". It is the same rd_doc the GUI
 * paints. */
static void print_doc(const rd_doc *doc) {
    int line_open = 0; /* an inline line is being accumulated */
    for (size_t i = 0; i < rd_count(doc); ++i) {
        const rd_block *b = rd_at(doc, i);
        switch (b->kind) {
            case RD_HEADING: {
                if (line_open) { putchar('\n'); line_open = 0; }
                int level = (b->heading_level >= 1 && b->heading_level <= 6) ? b->heading_level : 1;
                putchar('\n');
                for (int k = 0; k < level; ++k) putchar('#');
                printf(" %s\n", b->text);
                break;
            }
            case RD_IMAGE:
                if (line_open) { putchar('\n'); line_open = 0; }
                printf("\n[%s]", rd_image_label(b->img_decision));
                if (b->text[0] != '\0') printf(" %s", b->text);
                if (b->href != NULL && b->href[0] != '\0') printf(" <%s>", b->href);
                putchar('\n');
                break;
            case RD_NOTICE:
                if (line_open) { putchar('\n'); line_open = 0; }
                printf("\n! %s\n", b->text);
                break;
            case RD_INPUT: {
                /* A hidden control is not shown to the reader. */
                if (b->input_type == PV_IN_HIDDEN) break;
                if (line_open) { putchar('\n'); line_open = 0; }
                if (b->input_type == PV_IN_SUBMIT || b->input_type == PV_IN_BUTTON) {
                    printf("[ %s ]\n", (b->text[0] != '\0') ? b->text : rd_input_label(b->input_type));
                } else {
                    /* An editable field: show its current value, then the placeholder. */
                    printf("[%s: %s]", rd_input_label(b->input_type),
                           (b->value != NULL && b->value[0] != '\0') ? b->value
                           : (b->text[0] != '\0' ? b->text : "____"));
                    putchar('\n');
                }
                break;
            }
            case RD_LINK:
            case RD_PARAGRAPH:
            default:
                /* Inter-block whitespace carries no information in plain text. */
                if (is_blank_text(b->text) && (b->block_break || !line_open)) break;
                if (line_open && b->block_break) { printf("\n\n"); line_open = 0; }
                if (b->kind == RD_LINK && b->href != NULL && b->href[0] != '\0') {
                    printf("%s <%s>", b->text, b->href);
                } else {
                    printf("%s", b->text);
                }
                line_open = 1;
                break;
        }
    }
    if (line_open) putchar('\n');
}

/* Loads html into a fresh tab and prints the structured render of the page.
 * top_url is the page's https origin (for per-image policy decisions) or NULL for
 * a local file. Returns EXIT_OK or EXIT_ERROR; on error no partial page output. */
static int render_page(const char *html, size_t len, const char *top_url) {
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

    /* In stdout mode the title leads the output; in PDF mode it is carried inside
     * the document, so stdout stays a single confirmation line. */
    if (g_pdf_out == NULL && page.title != NULL && page.title_len > 0) {
        printf("%s\n", page.title);
    }

    /* Images stay off by default (Privacy by Default); render_doc prepends the
     * tracking warning when the page declares images. --author-css opts into author
     * styling for the local render only (no network: the image cap stays off). */
    rdp_caps caps = rdp_caps_safe();
    if (g_author_css) caps.css = true;
    rd_doc *doc = NULL;
    rd_status rs = rd_build(page.view, caps, top_url, &doc);
    int out_rc = (rs == RD_OK) ? EXIT_OK : EXIT_ERROR;

    if (g_pdf_out != NULL) {
        /* Headless vector-PDF export for visual review: write the SAME display list
         * the GUI would paint, to a PDF, without a Wayland window. */
        if (rs == RD_OK && rd_count(doc) > 0) {
            long pages = 0;
            if (ui_render_pdf(doc, g_pdf_out, &pages) != UI_OK) {
                fprintf(stderr, "freedom: could not write PDF to '%s'\n", g_pdf_out);
                out_rc = EXIT_ERROR;
            } else {
                printf("Saved PDF (%ld page%s): %s\n",
                       pages, pages == 1 ? "" : "s", g_pdf_out);
            }
        } else {
            fprintf(stderr, "freedom: nothing to render to PDF for this page\n");
            out_rc = EXIT_ERROR;
        }
    } else if (rs == RD_OK && rd_count(doc) > 0) {
        print_doc(doc);
    } else if (page.text != NULL && page.text_len > 0) {
        printf("\n%s\n", page.text); /* fallback if the display list is empty */
    }
    rd_free(doc);

    tab_page_free(&page);
    tab_close(t);
    return out_rc;
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

    /* Socket-level anonymity routing. A .onion/.i2p target whose proxy is not enabled
     * is BLOCKED (fail closed), never leaked over the clearnet. */
    nr_route route = nr_route_for(url, global_net);
    if (route == NR_ROUTE_BLOCKED) {
        fprintf(stderr, "freedom: '%s' is a %s address but its proxy is not enabled "
                "(use --tor/--i2p). Refusing to leak it over clearnet.\n",
                url, nr_realm_name(nr_classify_url(url)));
        sf_response_free(&resp);
        return EXIT_ERROR;
    }
    if (route == NR_ROUTE_TOR) { cfg.proxy_type = SF_PROXY_SOCKS5H; cfg.proxy_address = global_tor_addr; }
    else if (route == NR_ROUTE_I2P) { cfg.proxy_type = SF_PROXY_HTTP; cfg.proxy_address = global_i2p_addr; }
    if (route == NR_ROUTE_TOR || route == NR_ROUTE_I2P)
        cfg.allow_overlay_http = nr_realm_allows_http(nr_classify_url(url));

    /* Follow redirects (e.g. google.com -> www.google.com), re-validating the
     * full policy on every hop. */
    sf_status ss = sf_get_follow(url, &cfg, &resp, SF_DEFAULT_MAX_REDIRECTS);
    if (ss != SF_OK) {
        fprintf(stderr, "freedom: fetch failed for '%s' (status %d: %s)\n",
                url, (int)ss, sf_reason(ss));
        sf_response_free(&resp);
        return EXIT_ERROR;
    }

    int rc = render_page((const char *)resp.body, resp.body_len, url);
    sf_response_free(&resp);
    return rc;
}

static int run_headless(const char *target) {
    if (is_https_url(target) || is_overlay_http(target)) {
        return fetch_and_render(target);
    }

    size_t len = 0;
    char *html = read_file(target, &len);
    if (html == NULL) {
        fprintf(stderr, "freedom: cannot read '%s'\n", target);
        return EXIT_ERROR;
    }

    /* A local file has no https origin; image decisions then fail closed. */
    int rc = render_page(html, len, NULL);
    free(html);
    return rc;
}

int main(int argc, char **argv) {
    /* A per-tab worker is spawned by re-exec'ing this binary (tab.c fork+exec) so it
     * inherits none of the GUI's memory. When invoked as one, run the confined worker
     * loop and never return; otherwise this is a no-op and normal startup proceeds. */
    tab_worker_dispatch(argc, argv);

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
        } else if (strncmp(arg, "--download-pdf=", 15) == 0) {
            /* Bare "--download-pdf" (no =PATH) falls through to the unknown-option
             * branch below -> usage error: never guess an output path. */
            const char *path = arg + 15;
            if (path[0] == '\0') {
                fprintf(stderr, "freedom: --download-pdf requires a non-empty PATH\n");
                print_usage(stderr, argv[0]);
                return EXIT_USAGE;
            }
            g_pdf_out = path;
            headless = 1; /* PDF export is a headless operation (no window) */
        } else if (strcmp(arg, "--author-css") == 0) {
            g_author_css = 1; /* apply author CSS in the headless render (local only) */
        } else if (strcmp(arg, "--insecure") == 0 || strcmp(arg, "-I") == 0) {
            global_insecure = 1;
        } else if (strcmp(arg, "--tor") == 0) {
            global_net.tor_enabled = 1;
        } else if (strncmp(arg, "--tor=", 6) == 0) {
            global_net.tor_enabled = 1;
            snprintf(global_tor_addr, sizeof global_tor_addr, "%s", arg + 6);
        } else if (strcmp(arg, "--i2p") == 0) {
            global_net.i2p_enabled = 1;
        } else if (strncmp(arg, "--i2p=", 6) == 0) {
            global_net.i2p_enabled = 1;
            snprintf(global_i2p_addr, sizeof global_i2p_addr, "%s", arg + 6);
        } else if (strcmp(arg, "--torify") == 0) {
            global_net.tor_enabled = 1;
            global_net.torify_clearnet = 1;
        } else if (strcmp(arg, "--js") == 0) {
            setenv("FREEDOM_JS", "on", 1);            /* GUI reads FREEDOM_JS */
        } else if (strncmp(arg, "--js=", 5) == 0) {
            setenv("FREEDOM_JS", arg + 5, 1);          /* off|allowlist|on */
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
