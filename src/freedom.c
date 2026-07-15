/*
 * freedom — Freedom browser entry point (Hito 5+).
 *
 * By default opens the minimal Wayland browser GUI. Use --headless to render a
 * single page to stdout. See spec/freedom.md for the CLI contract and
 * spec/browser.md for the GUI contract.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <unistd.h>

#include "dom_debug.h"
#include "freebug.h"
#include "hostblock.h"
#include "js_policy.h"
#include "link_nav.h"
#include "net_realm.h"
#include "prefetch.h"
#include "render_doc.h"
#include "render_policy.h"
#include "request_policy.h"
#include "secure_fetch.h"
#include "tab.h"
#include "media_decoder.h"
#include "tls_impersonate.h"
#include "ui.h"
#include "url.h"

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
    fprintf(fp, "  --download-png=PATH: headless render to a single PNG image at PATH (implies --headless)\n");
    fprintf(fp, "  --author-css: apply author CSS (colors/sizing/line-height) in the headless render (local only)\n");
    fprintf(fp, "  --images: enable image loading in headless render (off by default: Privacy by Default)\n");
    fprintf(fp, "  --user=user:password: HTTP Basic Authentication credentials (headless only)\n");
    fprintf(fp, "  --insecure: allow weak TLS certificates (headless only, explicit override)\n");
    fprintf(fp, "  --tor[=host:port]: route via a Tor SOCKS5h proxy (default 127.0.0.1:9050); reaches .onion\n");
    fprintf(fp, "  --i2p[=host:port]: route .i2p via an I2P HTTP proxy (default 127.0.0.1:4444)\n");
    fprintf(fp, "  --torify: also route ordinary clearnet through Tor (implies --tor)\n");
    fprintf(fp, "  --js[=off|allowlist|on]: page-JS policy (GUI; headless runs JS when this resolves to 'on')\n");
    fprintf(fp, "  --dump-console: headless, run the page's JS and print the captured console (Freebug); implies JS on\n");
    fprintf(fp, "  --dump-dom: headless, print the paint-ready render tree (blocks, boxes, containers) to stdout\n");
    fprintf(fp, "  --dump-css: headless, print the resolved CSS property dump (boxes + block properties) to stdout\n");
    fprintf(fp, "  --dump-layout: headless, print the resolved layout (box rects + positioned boxes) to stdout\n");
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

/* When non-NULL (set by --download-png=PATH), headless mode renders the page to a
 * single full-height PNG bitmap at this path instead of printing to stdout. The
 * path is a trusted local CLI argument, used verbatim. */
static const char *g_png_out = NULL;

/* Set by --author-css: apply author CSS (caps.css) in the headless render, so
 * author styling (colors, text-align, font-size, line-height) is visually
 * reviewable without a Wayland window. Local render only; the network image cap
 * stays off, so this never fetches or phones home. Default off (Privacy by Default). */
static int g_author_css = 0;

/* Set by --images: enable image loading in headless mode (otherwise images are
 * blocked by default: Privacy by Default doctrine). Respects FREEDOM_IMAGES env var. */
static int g_images = 0;

/* Set by --dump-console: after the headless render, print the captured Freebug
 * console (page console.* output + any uncaught script error). Implies running JS. */
static int g_dump_console = 0;

/* Set by --dump-dom: print the paint-ready render tree (dom_debug) to stdout instead
 * of the page render, the agent-readable instrument for diagnosing layout/paint gaps.
 * Honours --author-css (so the box tree is populated); does NOT imply running JS. */
static int g_dump_dom = 0;

/* Set by --dump-css: print the full CSS property dump (dd_format_css) to stdout after
 * the render, showing per-element resolved CSS. Like --dump-dom, it makes the agent
 * diagnose styling gaps without a Wayland window. Honours --author-css. */
static int g_dump_css = 0;

/* Set by --dump-layout: print the resolved layout (in-flow boxes + positioned
 * boxes) to stdout. The layout-side counterpart to --dump-dom: --dump-dom shows
 * the render tree (input to layout), --dump-layout shows the geometry the layout
 * engine produced (output). Honours --author-css. */
static int g_dump_layout = 0;

/* When nonzero, the headless render runs the page's inline JS (tab_load_full run_js).
 * Set by --dump-console and by --js resolving to "on". Default off (Secure by Default). */
static int g_headless_js = 0;

/* HTTP Basic Authentication for headless mode. Set by --user=username:password. */
static char g_auth_user[256] = "";
static char g_auth_pass[256] = "";

/* Tor/I2P routing for headless mode (off by default; opt-in via CLI flags). */
static nr_config global_net = { 0, 0, 0 };
static char global_tor_addr[64] = "127.0.0.1:9050";
static char global_i2p_addr[64] = "127.0.0.1:4444";

static hb_set *g_hosts = NULL;
static hb_set *g_impersonate = NULL; /* impersonate.conf: triple-opt-in TLS-blend hosts */

/* Reads the whole file into a NUL-terminated buffer. Caller frees with free(). */
static char *read_file(const char *path, size_t *out_len) {
    FILE *f = fopen(path, "rb");
    if (f == NULL) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    rewind(f);

    if ((size_t)sz == (size_t)-1) { fclose(f); return NULL; }
    char *buf = (char *)malloc((size_t)sz + 1);
    if (buf == NULL) { fclose(f); return NULL; }
    size_t n = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    buf[n] = '\0';
    if (out_len != NULL) *out_len = n;
    return buf;
}

static void headless_load_hosts(void) {
    g_hosts = hb_new();
    g_impersonate = hb_new();
    if (g_hosts == NULL) return;
    const char *dirs[] = { NULL, "config", NULL };
    /* home_dir must live for the whole function: dirs[2] aliases it and is read in
     * the loop below. A previous inner-block buffer went out of scope while dirs[2]
     * still pointed at it (stack-use-after-scope: the config path was then built from
     * a dangling pointer). */
    char home_dir[512];
    const char *home = getenv("HOME");
    if (home != NULL) {
        snprintf(home_dir, sizeof home_dir, "%s/.config/freedom", home);
        dirs[2] = home_dir;
    }
    const char *env = getenv("FREEDOM_HOSTS_DIR");
    if (env != NULL) dirs[0] = env;
    for (int i = 0; i < 3; ++i) {
        if (dirs[i] == NULL) continue;
        char path[1024];
        int n = snprintf(path, sizeof path, "%s/allow.conf", dirs[i]);
        if (n <= 0 || (size_t)n >= sizeof path) continue;
        size_t len = 0;
        char *txt = read_file(path, &len);
        if (txt != NULL) { hb_load(g_hosts, txt, HB_LIST_ALLOW); free(txt); }
        /* impersonate.conf lives in the same search dirs; load it as an allowlist so
         * hb_is_allowlisted answers the third gate signal (covers subdomains). */
        if (g_impersonate != NULL) {
            n = snprintf(path, sizeof path, "%s/impersonate.conf", dirs[i]);
            if (n > 0 && (size_t)n < sizeof path) {
                char *itxt = read_file(path, NULL);
                if (itxt != NULL) { hb_load(g_impersonate, itxt, HB_LIST_ALLOW); free(itxt); }
            }
        }
    }
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
                {
                    const char *lab = rd_image_label(b->img_decision);
                    const char *fail = (b->img_decision == RDP_IMG_ALLOW && b->img_fail != IMG_FAIL_OK)
                                     ? rd_image_fail_label(b->img_fail) : NULL;
                    printf("\n[%s]", fail ? fail : lab);
                    if (b->text[0] != '\0') printf(" %s", b->text);
                    if (b->href != NULL && b->href[0] != '\0') printf(" <%s>", b->href);
                }
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
                } else if (b->input_type == PV_IN_PROGRESS || b->input_type == PV_IN_METER) {
                    double val_d = (b->value != NULL) ? atof(b->value) : 0.0;
                    double max_d = 1.0;
                    if (b->input_type == PV_IN_PROGRESS) {
                        if (b->text != NULL) max_d = atof(b->text);
                    } else {
                        double min_d = 0.0;
                        if (b->text != NULL) sscanf(b->text, "%lf,%lf", &min_d, &max_d);
                        if (max_d <= min_d) max_d = min_d + 1.0;
                    }
                    if (max_d <= 0.0) max_d = 1.0;
                    if (val_d < 0.0) val_d = 0.0;
                    if (val_d > max_d) val_d = max_d;
                    int pct = (int)((val_d / max_d) * 100.0);
                    if (pct > 100) pct = 100;
                    int bar_width = 20;
                    int filled = (pct * bar_width) / 100;
                    if (filled > bar_width) filled = bar_width;
                    char bar[21];
                    memset(bar, '=', (size_t)filled);
                    memset(bar + filled, ' ', (size_t)(bar_width - filled));
                    bar[bar_width] = '\0';
                    printf("[%s] %d%%\n", bar, pct);
                } else if (b->input_type == PV_IN_LEGEND) {
                    const char *legend = (b->text != NULL && b->text[0] != '\0') ? b->text
                                       : (b->value != NULL ? b->value : "");
                    printf("== %s ==\n", (legend[0] != '\0') ? legend : "(legend)");
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

/* Prints the captured Freebug console (the developer-visible JS transcript) to
 * stdout, one entry per line, prefixed with its level and (for located errors)
 * its source name:line:col. Deterministic order; an empty buffer prints just the
 * header so "nothing logged" is unambiguous. */
static void print_console(const fb_buffer *log) {
    size_t n = fb_buffer_count(log);
    printf("\n=== Freebug console (%zu) ===\n", n);
    for (size_t i = 0; i < n; ++i) {
        const fb_entry *e = fb_buffer_at(log, i);
        if (e->file != NULL && e->file[0] != '\0')
            printf("[%s] %s:%d:%d  %s\n", fb_level_name(e->level),
                   e->file, e->line, e->col, e->text);
        else
            printf("[%s] %s\n", fb_level_name(e->level), e->text);
    }
    if (log->overflow) printf("[notice] console output was truncated (buffer full)\n");
}

/* Prints the paint-ready render tree (dom_debug) to stdout. Two-pass: measure, then
 * allocate exactly and format. The dump is bounded by the document; dd_format never
 * overruns and allocates nothing itself. */
static void print_dom(const rd_doc *doc) {
    size_t need = dd_format(doc, NULL, 0);
    if (need == (size_t)-1) { fprintf(stderr, "freedom: error measuring render tree\n"); return; }
    char *buf = (char *)malloc(need + 1);
    if (buf == NULL) {
        fprintf(stderr, "freedom: out of memory while dumping the render tree\n");
        return;
    }
    dd_format(doc, buf, need + 1);
    fputs(buf, stdout);
    free(buf);
}

/* Prints the CSS property inspector (dd_format_css) to stdout. Same contract as
 * print_dom: two-pass measure-then-allocate. */
static void print_dom_css(const rd_doc *doc) {
    size_t need = dd_format_css(doc, NULL, 0);
    if (need == (size_t)-1) { fprintf(stderr, "freedom: error measuring CSS inspector\n"); return; }
    char *buf = (char *)malloc(need + 1);
    if (buf == NULL) {
        fprintf(stderr, "freedom: out of memory while dumping CSS inspector\n");
        return;
    }
    dd_format_css(doc, buf, need + 1);
    fputs(buf, stdout);
    free(buf);
}

/* Loads html into a fresh tab and prints the structured render of the page.
 * top_url is the page's https origin (for per-image policy decisions) or NULL for
 * a local file. Runs the page's JS when g_headless_js (so --dump-console can show
 * console output/errors). Returns EXIT_OK or EXIT_ERROR; on error no partial output. */
/* tab_fetch_fn for the headless renderer: a policy-checked subresource fetch for page
 * XHR/fetch and external <script src>. ctx is the page's top URL (or NULL for a local
 * file): the RAW url from the worker is resolved against it with ln_resolve, the same
 * gate a click gets (https-only, no downgrade, no foreign scheme), so relative
 * subresources work. Realm-routed (fail-closed); no per-host allowlist here (headless
 * is operator-driven -- enabling --js is the trust signal). The confined worker never
 * touches a socket; this runs in the trusted parent. */
static int headless_fetch(void *ctx, const char *method, const char *url,
                          const char *body, size_t body_len,
                          int *st, char **ob, size_t *ol, char **oct) {
    const char *base = (const char *)ctx;
    ln_result ln;
    *st = 0; *ob = NULL; *ol = 0; *oct = NULL;
    if (url == NULL) return -1;
    if (base != NULL) {
        if (ln_resolve(base, url, &ln) != LN_OK
            || ln.action != LN_NAVIGATE || ln.kind != LN_TARGET_HTTPS) return -1;
        url = ln.target;
    } else if (strncmp(url, "https://", 8) != 0) {
        return -1; /* no base to resolve against: absolute https only */
    }

    sf_config cfg = sf_config_default();
    if (g_hosts != NULL) {
        char host[512];
        if (rp_host_of(url, host, sizeof host) == 0) {
            int allowed = hb_is_allowlisted(g_hosts, host);
            if (allowed) cfg.policy = SF_POLICY_ALLOWLISTED_INSECURE;
            /* Triple opt-in TLS blend: allow.conf AND JS-on AND impersonate.conf. */
            cfg.impersonate = ti_should_impersonate(
                allowed, g_headless_js, hb_is_allowlisted(g_impersonate, host));
        }
    }
    if (global_insecure) { cfg.policy = SF_POLICY_PERMISSIVE; cfg.insecure = 1; }
    if (g_auth_user[0] != '\0') { cfg.username = g_auth_user; cfg.password = g_auth_pass; }
    nr_route route = nr_route_for(url, global_net);
    if (route == NR_ROUTE_BLOCKED) return -1;
    if (route == NR_ROUTE_TOR)      { cfg.proxy_type = SF_PROXY_SOCKS5H; cfg.proxy_address = global_tor_addr; }
    else if (route == NR_ROUTE_I2P) { cfg.proxy_type = SF_PROXY_HTTP;    cfg.proxy_address = global_i2p_addr; }

    sf_response resp;
    memset(&resp, 0, sizeof resp);
    int is_post = (method != NULL && (strcmp(method, "POST") == 0 || strcmp(method, "post") == 0));
    sf_status s = is_post
        ? sf_post(url, &cfg, body, body_len, "application/x-www-form-urlencoded", &resp)
        : sf_get_follow(url, &cfg, &resp, SF_DEFAULT_MAX_REDIRECTS);
    if (s != SF_OK) { sf_response_free(&resp); return -1; }

    if (resp.body_len == (size_t)-1) { sf_response_free(&resp); return -1; }
    char *rb = (char *)malloc(resp.body_len + 1);
    if (rb == NULL) { sf_response_free(&resp); return -1; }
    if (resp.body_len != 0) memcpy(rb, resp.body, resp.body_len);
    rb[resp.body_len] = '\0';
    *st = (int)resp.http_code; *ob = rb; *ol = resp.body_len;
    *oct = (resp.content_type != NULL) ? strdup(resp.content_type) : NULL;
    sf_response_free(&resp);
    return 0;
}

/* out_nav (may be NULL): receives an owned copy of the JS-requested navigation
 * target, if any. The tab layer already resolved and policy-gated it against the
 * page's real URL (ln_resolve); the caller still drives it through the normal
 * fetch path, re-applying the full network policy. */
/* Folds a page's document.cookie jar ("a=1; b=2") back into the ephemeral network
 * jar, one pair at a time, so JS-set session cookies reach the next request. */
static void foldback_cookies(const char *url, const char *jar) {
    if (url == NULL || jar == NULL) return;
    for (const char *p = jar; *p != '\0'; ) {
        while (*p == ' ' || *p == ';') ++p;
        const char *end = p;
        while (*end != '\0' && *end != ';') ++end;
        size_t plen = (size_t)(end - p);
        if (plen > 0 && plen < 700) {
            char pair[768];
            memcpy(pair, p, plen); pair[plen] = '\0';
            sf_cookie_put(url, pair);
        }
        p = end;
    }
}

static int render_page(const char *html, size_t len, const char *top_url,
                       char **out_nav) {
    tab *t = NULL;
    tab_status ts = tab_open(&t);
    if (ts != TAB_OK) {
        fprintf(stderr, "freedom: failed to open tab worker (status %d)\n", (int)ts);
        return EXIT_ERROR;
    }

    /* Page-JS network (XHR/fetch + external <script src>): in headless the operator's
     * --js=on is the trust signal (the GUI gates this per host on allow.conf AND
     * js.conf). The page URL is the resolution base for relative subresources. */
    tab_set_net_allowed(t, g_headless_js);
    /* --author-css also authorizes external <link rel=stylesheet> fetches for a
     * remote page (GET-only at the parent gate; spec/freedom.md §6). */
    tab_set_css_allowed(t, g_author_css);

    /* Hito 29 (lookahead prefetch): pre-scan the HTML and download the external
     * stylesheets/scripts the worker will request in parallel, through the same
     * policy-gated headless_fetch. A miss falls back to the serial path. */
    pf_list scanned;
    scanned.count = 0;
    pf_pool subpool;
    pf_gated_fetch gated = { headless_fetch, (void *)(uintptr_t)top_url, NULL };
    if ((g_headless_js || g_author_css) && pf_scan(html, len, &scanned) == 0) {
        const char *urls[PF_MAX_REFS];
        size_t nurl = 0;
        for (size_t i = 0; i < scanned.count; ++i) {
            int want = (scanned.refs[i].kind == PF_STYLESHEET) ? g_author_css
                                                               : g_headless_js;
            if (want) urls[nurl++] = scanned.refs[i].url;
        }
        if (nurl > 0
            && pf_pool_start(&subpool, urls, nurl, headless_fetch,
                             (void *)(uintptr_t)top_url) == 0)
            gated.pool = &subpool;
    }
    tab_set_fetcher(t, pf_pooled_fetch, &gated);

    /* Session cookies (trusted host only, --js=on here): seed document.cookie from the
     * ephemeral network jar so the page's consent/session JS can read existing cookies. */
    if (g_headless_js && top_url != NULL) {
        char ckhdr[4096];
        if (sf_cookie_header_for(top_url, ckhdr, sizeof ckhdr) > 0)
            tab_set_cookies(t, ckhdr);
    }

    tab_page page;
    memset(&page, 0, sizeof page);
    ts = tab_load_full(t, html, len, top_url, g_headless_js, 0, 0, &page);

    /* The prefetch window ends with the load: rebind the direct fetcher and drop
     * the pool (unconsumed results freed, in-flight fetches joined). */
    tab_set_fetcher(t, headless_fetch, (void *)(uintptr_t)top_url);
    if (gated.pool != NULL) pf_pool_finish(&subpool);
    pf_list_free(&scanned);

    if (ts != TAB_OK) {
        fprintf(stderr, "freedom: failed to load page (status %d)\n", (int)ts);
        tab_close(t);
        return EXIT_ERROR;
    }

    /* Real async timers (2026-07-11): pump up to HL_TICK_MAX virtual ticks so a
     * page that renders via setTimeout/setInterval shows its final state in the
     * export. Each tick advances the worker's virtual clock straight to the next
     * pending timer; the shared per-page JS budget still bounds total work. */
    enum { HL_TICK_MAX = 240 };
    for (int tick = 0; tick < HL_TICK_MAX && page.next_timer_ms >= 0; ++tick) {
        tab_page ticked;
        if (tab_tick(t, page.next_timer_ms, &ticked) != TAB_OK) break;
        tab_page_free(&page);
        page = ticked;
    }

    /* Fold JS-set session cookies back into the ephemeral network jar so a JS-driven
     * consent/redirect hop (followed by fetch_and_render) carries them. */
    if (g_headless_js && top_url != NULL && page.set_cookies != NULL)
        foldback_cookies(top_url, page.set_cookies);

    /* In stdout mode the title leads the output; in PDF mode it is carried inside
     * the document, so stdout stays a single confirmation line. */
    if (g_pdf_out == NULL && g_png_out == NULL && page.title != NULL && page.title_len > 0) {
        printf("%s\n", page.title);
    }

    /* Images stay off by default (Privacy by Default); render_doc prepends the
     * tracking warning when the page declares images. --author-css opts into author
     * styling for the local render only (no network). --images enables image loading
     * AND rendering, including remote fetches (so --download-png --images actually
     * shows images in the bitmap). */
    rdp_caps caps = rdp_caps_safe();
    if (g_author_css) caps.css = true;
    if (g_images || getenv("FREEDOM_IMAGES") != NULL) caps.images = true;
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
    } else if (g_png_out != NULL) {
        /* Headless raster-PNG export for visual review: a single full-height bitmap
         * of the SAME display list the GUI would paint, no Wayland window. */
        if (rs == RD_OK && rd_count(doc) > 0) {
            long img_h = 0;
            if (ui_render_png(doc, g_png_out, &img_h) != UI_OK) {
                fprintf(stderr, "freedom: could not write PNG to '%s'\n", g_png_out);
                out_rc = EXIT_ERROR;
            } else {
                printf("Saved PNG (%ld px): %s\n", img_h, g_png_out);
            }
        } else {
            fprintf(stderr, "freedom: nothing to render to PNG for this page\n");
            out_rc = EXIT_ERROR;
        }
    } else if (rs == RD_OK && rd_count(doc) > 0 && !g_dump_dom && !g_dump_layout && !g_dump_css) {
        print_doc(doc);
    } else if (!g_dump_dom && !g_dump_layout && !g_dump_css && page.text != NULL && page.text_len > 0) {
        printf("\n%s\n", page.text); /* fallback if the display list is empty */
    }

    /* --dump-dom: the agent-readable render tree, printed after any render output
     * (so --dump-dom alone prints just the tree; combined with --download-png it
     * writes the PNG and prints the tree, both MCP-visible). */
    if (g_dump_dom && rs == RD_OK) print_dom(doc);
    /* --dump-layout: the resolved geometry (in-flow boxes + positioned boxes),
     * the layout-side counterpart to --dump-dom. Combined with --download-png it
     * gives both the bitmap and the numbers behind it. */
    if (g_dump_layout && rs == RD_OK) ui_dump_layout(doc);
    /* --dump-css: the resolved CSS property inspector, showing per-element CSS
     * properties as seen by the box engine and painter. */
    if (g_dump_css && rs == RD_OK) print_dom_css(doc);
    rd_free(doc);

    /* Developer console (Freebug): show what the page's JS logged and any error. */
    if (g_dump_console) print_console(&page.console);

    if (out_nav != NULL) {
        *out_nav = (page.nav_url != NULL && page.nav_url[0] != '\0')
                 ? strdup(page.nav_url) : NULL;
    }

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

/* Anti-loop cap on JS-requested navigations followed headless (mirrors the GUI's
 * JS_NAV_MAX): a hostile page cannot chain the renderer through endless hops. */
#define HL_JS_NAV_MAX 10

/* Fetches one url with secure_fetch and renders the result. The response body is
 * consumed directly; no extra copy is made. out_nav as in render_page. */
static int fetch_and_render_one(const char *url, char **out_nav) {
    sf_response resp;
    memset(&resp, 0, sizeof resp);
    if (out_nav != NULL) *out_nav = NULL;

    /* Mirror the GUI: a search-engine SPA whose results are built only by client-side
     * JavaScript we cannot fully run (DuckDuckGo's "duckduckgo.com/?q=...") is
     * transparently redirected to its no-JS server-rendered endpoint (see
     * url_search_rewrite). The rewritten URL becomes the fetch AND the render base. */
    char search_rw[URL_MAX_LEN + 1];
    if (url_search_rewrite(url, search_rw, sizeof search_rw) == URL_OK) url = search_rw;

    sf_config cfg = sf_config_default();
    if (g_hosts != NULL) {
        char host[512];
        if (rp_host_of(url, host, sizeof host) == 0) {
            int allowed = hb_is_allowlisted(g_hosts, host);
            if (allowed) cfg.policy = SF_POLICY_ALLOWLISTED_INSECURE;
            cfg.impersonate = ti_should_impersonate(
                allowed, g_headless_js, hb_is_allowlisted(g_impersonate, host));
        }
    }
    if (global_insecure) { cfg.policy = SF_POLICY_PERMISSIVE; cfg.insecure = 1; }
    if (g_auth_user[0] != '\0') { cfg.username = g_auth_user; cfg.password = g_auth_pass; }

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

    int rc = render_page((const char *)resp.body, resp.body_len, url, out_nav);
    sf_response_free(&resp);
    return rc;
}

/* Fetches and renders url, then follows any JS-requested navigation (location.href=
 * / assign / replace) the same way the GUI does: each hop re-enters the normal fetch
 * path, so the FULL policy re-applies, with a hard anti-loop cap. Without this, a
 * page whose script immediately forwards elsewhere (e.g. a search engine's
 * JS-capability interstitial) renders as an empty husk instead of its destination. */
static int fetch_and_render(const char *url) {
    char *cur = NULL;
    int rc = EXIT_ERROR;
    for (int hop = 0; hop <= HL_JS_NAV_MAX; ++hop) {
        char *nav = NULL;
        rc = fetch_and_render_one((cur != NULL) ? cur : url, g_headless_js ? &nav : NULL);
        free(cur);
        cur = NULL;
        if (nav == NULL) break;
        if (hop == HL_JS_NAV_MAX) { free(nav); break; } /* cap reached: keep last render */
        fprintf(stderr, "freedom: following JS navigation to '%s'\n", nav);
        cur = nav;
    }
    free(cur);
    return rc;
}

static int run_headless(const char *target) {
    headless_load_hosts();
    if (is_https_url(target) || is_overlay_http(target)) {
        return fetch_and_render(target);
    }

    size_t len = 0;
    char *html = read_file(target, &len);
    if (html == NULL) {
        fprintf(stderr, "freedom: cannot read '%s'\n", target);
        return EXIT_ERROR;
    }

    /* A local file has no https origin; image decisions then fail closed, and a
     * JS navigation request has no trusted base, so none is followed. */
    int rc = render_page(html, len, NULL, NULL);
    free(html);
    return rc;
}

int main(int argc, char **argv) {
    /* A per-tab worker is spawned by re-exec'ing this binary (tab.c fork+exec) so it
     * inherits none of the GUI's memory. When invoked as --tab-worker, run the confined
     * worker loop and never return. Similarly, --media-decoder starts the decoder helper
     * (a separate process, sandboxed, that decodes H.264/H.265 TS segments via FFmpeg). */
    if (argc >= 4 && strcmp(argv[1], "--media-decoder") == 0) {
        int out_fd = (int)strtol(argv[2], NULL, 10);
        int cmd_fd = (int)strtol(argv[3], NULL, 10);
        if (out_fd > 0 && cmd_fd > 0)
            media_decoder_run(out_fd, cmd_fd);
        _exit(1);
    }
    tab_worker_dispatch(argc, argv);

    int headless = 0;
    int js_on = 0; /* the --js flag resolved to "on" (headless then runs JS) */
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
        } else if (strncmp(arg, "--download-png=", 15) == 0) {
            /* Bare "--download-png" (no =PATH) falls through to the unknown-option
             * branch below -> usage error: never guess an output path. */
            const char *path = arg + 15;
            if (path[0] == '\0') {
                fprintf(stderr, "freedom: --download-png requires a non-empty PATH\n");
                print_usage(stderr, argv[0]);
                return EXIT_USAGE;
            }
            g_png_out = path;
            headless = 1; /* PNG export is a headless operation (no window) */
        } else if (strcmp(arg, "--author-css") == 0) {
            g_author_css = 1; /* author CSS in the headless render + external sheet fetch */
        } else if (strcmp(arg, "--images") == 0) {
            g_images = 1; /* image loading in the headless render */
        } else if (strncmp(arg, "--user=", 7) == 0) {
            const char *val = arg + 7;
            const char *colon = strchr(val, ':');
            if (colon == NULL || colon == val || *(colon + 1) == '\0') {
                fprintf(stderr, "freedom: --user requires 'username:password'\n");
                return EXIT_USAGE;
            }
            size_t ulen = (size_t)(colon - val);
            if (ulen >= sizeof g_auth_user) ulen = sizeof g_auth_user - 1;
            memcpy(g_auth_user, val, ulen);
            g_auth_user[ulen] = '\0';
            snprintf(g_auth_pass, sizeof g_auth_pass, "%s", colon + 1);
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
            js_on = 1;                                 /* headless: run JS too */
        } else if (strncmp(arg, "--js=", 5) == 0) {
            setenv("FREEDOM_JS", arg + 5, 1);          /* off|allowlist|on */
            js_on = (jsp_mode_from_str(arg + 5) == JSP_ON); /* headless runs JS only on 'on' */
        } else if (strcmp(arg, "--dump-console") == 0) {
            g_dump_console = 1;
            headless = 1;      /* it is a headless diagnostic (no window) */
        } else if (strcmp(arg, "--dump-dom") == 0) {
            g_dump_dom = 1;
            headless = 1;      /* it is a headless diagnostic (no window) */
        } else if (strcmp(arg, "--dump-css") == 0) {
            g_dump_css = 1;
            headless = 1;      /* it is a headless diagnostic (no window) */
        } else if (strcmp(arg, "--dump-layout") == 0) {
            g_dump_layout = 1;
            headless = 1;      /* it is a headless diagnostic (no window) */
        } else if (arg[0] == '-') {
            fprintf(stderr, "freedom: unknown option '%s'\n", arg);
            print_usage(stderr, argv[0]);
            return EXIT_USAGE;
        } else {
            target = arg;
        }
    }

    /* --dump-console always runs JS (a console dump with JS off is pointless), so it
     * forces JS on regardless of any --js flag's order; otherwise headless runs JS
     * only when --js resolved to "on". */
    g_headless_js = g_dump_console || js_on;

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
