/*
 * tab — implementation: a long-lived, sandboxed per-tab worker process.
 *
 * Evolved from the one-shot renderer. tab_open forks a child that confines
 * itself once (Landlock no-FS, best-effort; seccomp-bpf, mandatory/fail-closed)
 * before touching any content, then serves a request loop over two pipes. Inside
 * the confinement the child parses hostile HTML (html_parse), builds the inert
 * DOM (dom), and runs untrusted JS (js_sandbox) bound to that DOM plus the
 * normalized anti-fp environment (js_dom + js_env). The parent never parses or
 * executes the hostile bytes; it drives the child and survives a child crash,
 * reporting TAB_ERR_DEAD instead of dying with it.
 */

#define _GNU_SOURCE

#include "tab.h"

#include "anti_fp.h"
#include "dom.h"
#include "freebug.h"
#include "html_parse.h"
#include "image_decode.h"
#include "js_dom.h"
#include "js_env.h"
#include "js_sandbox.h"
#include "link_nav.h"
#include "os_sandbox.h"
#include "page_view.h"
#include "request_policy.h"
#include "url.h"

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <linux/close_range.h>
#include <sys/random.h>
#include <sys/wait.h>

/* Defined parent-side below; the re-exec'd worker restores SIGPIPE handling with it. */
static void ignore_sigpipe(void);

/* Fixed, normalized output size; fp_bucket_screen snaps it the same for all. */
#define TAB_SCREEN_W 1920
#define TAB_SCREEN_H 1080

/* Anti-amplification cap on the number of display-list runs the parent will
 * accept from the (possibly exploited) child. Plenty for any real page. */
#define TAB_MAX_RUNS ((size_t)(2u * 1024u * 1024u))

/* Cap on the page URL carried by OP_LOAD (URLs are small; defensive vs a desync). */
#define TAB_MAX_URL ((size_t)(64u * 1024u))

/* Request opcodes (parent -> child). */
enum { OP_LOAD = 1, OP_EVAL = 2, OP_QUIT = 3, OP_DECODE_IMAGE = 4 };

/* Handshake bytes (child -> parent) after the confinement attempt. */
enum { TAB_READY = 0x55, TAB_NO_CONFINE = 0xAA };

/* --- framed pipe I/O (EINTR-safe, all-or-nothing) --- */

static int write_full(int fd, const void *buf, size_t n) {
    const uint8_t *p = (const uint8_t *)buf;
    size_t done = 0;
    while (done < n) {
        ssize_t w = write(fd, p + done, n - done);
        if (w < 0) { if (errno == EINTR) continue; return -1; }
        done += (size_t)w;
    }
    return 0;
}

static int read_full(int fd, void *buf, size_t n) {
    uint8_t *p = (uint8_t *)buf;
    size_t got = 0;
    while (got < n) {
        ssize_t r = read(fd, p + got, n - got);
        if (r < 0) { if (errno == EINTR) continue; return -1; }
        if (r == 0) return -1; /* EOF before n bytes */
        got += (size_t)r;
    }
    return 0;
}

/* =========================== child side ============================== */

typedef struct child_state {
    hp_document *doc;
    dom_index   *idx;
    js_context  *js;
    uint64_t     session_key;
    fb_buffer    log; /* console capture (Freebug); persists across loads/evals */
} child_state;

static void child_reset_page(child_state *cs) {
    if (cs->js  != NULL) { js_context_free(cs->js);  cs->js  = NULL; }
    if (cs->idx != NULL) { dom_free(cs->idx);          cs->idx = NULL; }
    if (cs->doc != NULL) { hp_document_free(cs->doc);  cs->doc = NULL; }
}

/* Parse + index + fresh JS context bound to the page and the anti-fp env. When
 * run_js, inline <script>s are kept (not stripped) so child_handle_load can execute
 * them; event-handler attributes (on*) are stripped regardless. page_url (may be
 * NULL/empty) backs the page JS's real `location.*`; navigation capture is armed
 * regardless of run_js (a no-JS load simply never records a request). */
static int child_load(child_state *cs, const char *html, size_t len, int run_js,
                      const char *page_url) {
    child_reset_page(cs);

    hp_config cfg = hp_config_default();
    cfg.strip_scripts = run_js ? 0 : 1; /* keep scripts only when JS will run */

    hp_document *doc = NULL;
    if (hp_parse(html, len, &cfg, &doc) != HP_OK) return -1;

    dom_index *idx = NULL;
    if (dom_build(doc, &idx) != DOM_OK) { hp_document_free(doc); return -1; }

    js_context *js = NULL;
    if (js_context_new(NULL, &js) != JS_OK) {
        dom_free(idx); hp_document_free(doc); return -1;
    }
    /* Per-origin canvas/audio readback key: combine the per-worker session secret
     * with the page's registrable domain (eTLD+1) so two sites rendered by the same
     * worker get unlinkable poisoning. A URL with no host (file://, empty) yields no
     * registrable domain -> NULL -> a stable per-session namespace key. */
    char rb_host[256], rb_site[256];
    const char *rb_origin = NULL;
    if (page_url != NULL
     && rp_host_of(page_url, rb_host, sizeof rb_host) == 0
     && rp_site_of(rb_host, rb_site, sizeof rb_site) == 0) {
        rb_origin = rb_site;
    }
    uint64_t readback_key = fp_origin_key(cs->session_key, rb_origin);
    if (jd_install(js, idx) != JD_OK
     || je_install(js, TAB_SCREEN_W, TAB_SCREEN_H) != JE_OK
     || je_install_canvas(js, readback_key) != JE_OK) {
        js_context_free(js); dom_free(idx); hp_document_free(doc); return -1;
    }
    /* Capturing console for Freebug: a fresh page starts with an empty transcript;
     * the buffer (stable child_state member) is wired into the new context's runtime
     * opaque. Installed regardless of run_js so the REPL works on any page. */
    fb_buffer_reset(&cs->log);
    (void)jd_install_console(js, &cs->log);
    /* Install a real `location` over the page URL. url_split is https-only; a local
     * file:// (or empty) URL still gets href + navigation capture (parts == NULL). */
    if (page_url != NULL && page_url[0] != '\0') {
        url_parts parts;
        int have = (url_split(page_url, &parts) == URL_OK);
        (void)jd_set_location(js, page_url, have ? &parts : NULL);
    }

    cs->doc = doc; cs->idx = idx; cs->js = js;
    return 0;
}

/* Serialises the display list:
 *   [count]( kind,heading,bold,italic,indent,break, text, href, src, img_w,img_h, fg_rgb,bg_rgb,
 *            text_align,font_scale,line_scale,text_decoration,
 *            font_family,text_transform,letter_spacing,word_spacing,
 *            shadow_dx,shadow_dy,shadow_color,opacity,valign,text_indent,white_space,
 *            cont_id,cont_display,cont_gap,cont_justify,cont_cols,
 *            box_l,box_r,box_w,box_center,box_mt,box_mb,
 *            input_type,form_id,form_method, name, value )*
 * with each string length-prefixed (a length of 0 means absent). The fixed-width
 * fields travel for every run so a hostile child cannot desync the stream by
 * varying the per-run layout; non-image runs carry an empty src and -1 dimensions,
 * a run without an author color carries fg_rgb == -1, and non-input runs carry an
 * empty name/value, form_id == -1 and form_method == 0. */
static int write_view(int wfd, const pv_view *v) {
    size_t n = pv_count(v);
    if (write_full(wfd, &n, sizeof n) != 0) return -1;
    for (size_t i = 0; i < n; ++i) {
        const pv_run *r = pv_at(v, i);
        int32_t kind = (int32_t)r->kind;
        int32_t heading = (int32_t)r->heading;
        int32_t bold = (int32_t)r->bold;
        int32_t italic = (int32_t)r->italic;
        int32_t indent = (int32_t)r->indent;
        int32_t brk = (int32_t)r->block_break;
        int32_t img_w = (int32_t)r->img_w;
        int32_t img_h = (int32_t)r->img_h;
        int32_t fg = (int32_t)r->fg_rgb;
        int32_t bg = (int32_t)r->bg_rgb;
        int32_t talign = (int32_t)r->text_align;
        int32_t fscale = (int32_t)r->font_scale;
        int32_t lscale = (int32_t)r->line_scale;
        int32_t deco = (int32_t)r->text_decoration;
        int32_t ffam = (int32_t)r->font_family;
        int32_t ttrans = (int32_t)r->text_transform;
        int32_t lspc = (int32_t)r->letter_spacing;
        int32_t wspc = (int32_t)r->word_spacing;
        int32_t shdx = (int32_t)r->shadow_dx;
        int32_t shdy = (int32_t)r->shadow_dy;
        int32_t shcol = (int32_t)r->shadow_color;
        int32_t opac = (int32_t)r->opacity;
        int32_t valgn = (int32_t)r->valign;
        int32_t tindent = (int32_t)r->text_indent;
        int32_t wspace = (int32_t)r->white_space;
        int32_t cid = (int32_t)r->cont_id;
        int32_t cdisp = (int32_t)r->cont_display;
        int32_t cgap = (int32_t)r->cont_gap;
        int32_t cjust = (int32_t)r->cont_justify;
        int32_t ccols = (int32_t)r->cont_cols;
        int32_t bl = (int32_t)r->box_l;
        int32_t br = (int32_t)r->box_r;
        int32_t bw = (int32_t)r->box_w;
        int32_t bcenter = (int32_t)r->box_center;
        int32_t bmt = (int32_t)r->box_mt;
        int32_t bmb = (int32_t)r->box_mb;
        int32_t itype = (int32_t)r->input_type;
        int32_t fid = (int32_t)r->form_id;
        int32_t method = (int32_t)r->form_method;
        size_t tlen = (r->text != NULL) ? strlen(r->text) : 0;
        size_t hlen = (r->href != NULL) ? strlen(r->href) : 0;
        size_t slen = (r->src != NULL) ? strlen(r->src) : 0;
        size_t nmlen = (r->name != NULL) ? strlen(r->name) : 0;
        size_t vllen = (r->value != NULL) ? strlen(r->value) : 0;
        if (write_full(wfd, &kind, sizeof kind) != 0) return -1;
        if (write_full(wfd, &heading, sizeof heading) != 0) return -1;
        if (write_full(wfd, &bold, sizeof bold) != 0) return -1;
        if (write_full(wfd, &italic, sizeof italic) != 0) return -1;
        if (write_full(wfd, &indent, sizeof indent) != 0) return -1;
        if (write_full(wfd, &brk, sizeof brk) != 0) return -1;
        if (write_full(wfd, &tlen, sizeof tlen) != 0) return -1;
        if (tlen != 0 && write_full(wfd, r->text, tlen) != 0) return -1;
        if (write_full(wfd, &hlen, sizeof hlen) != 0) return -1;
        if (hlen != 0 && write_full(wfd, r->href, hlen) != 0) return -1;
        if (write_full(wfd, &slen, sizeof slen) != 0) return -1;
        if (slen != 0 && write_full(wfd, r->src, slen) != 0) return -1;
        if (write_full(wfd, &img_w, sizeof img_w) != 0) return -1;
        if (write_full(wfd, &img_h, sizeof img_h) != 0) return -1;
        if (write_full(wfd, &fg, sizeof fg) != 0) return -1;
        if (write_full(wfd, &bg, sizeof bg) != 0) return -1;
        if (write_full(wfd, &talign, sizeof talign) != 0) return -1;
        if (write_full(wfd, &fscale, sizeof fscale) != 0) return -1;
        if (write_full(wfd, &lscale, sizeof lscale) != 0) return -1;
        if (write_full(wfd, &deco, sizeof deco) != 0) return -1;
        if (write_full(wfd, &ffam, sizeof ffam) != 0) return -1;
        if (write_full(wfd, &ttrans, sizeof ttrans) != 0) return -1;
        if (write_full(wfd, &lspc, sizeof lspc) != 0) return -1;
        if (write_full(wfd, &wspc, sizeof wspc) != 0) return -1;
        if (write_full(wfd, &shdx, sizeof shdx) != 0) return -1;
        if (write_full(wfd, &shdy, sizeof shdy) != 0) return -1;
        if (write_full(wfd, &shcol, sizeof shcol) != 0) return -1;
        if (write_full(wfd, &opac, sizeof opac) != 0) return -1;
        if (write_full(wfd, &valgn, sizeof valgn) != 0) return -1;
        if (write_full(wfd, &tindent, sizeof tindent) != 0) return -1;
        if (write_full(wfd, &wspace, sizeof wspace) != 0) return -1;
        if (write_full(wfd, &cid, sizeof cid) != 0) return -1;
        if (write_full(wfd, &cdisp, sizeof cdisp) != 0) return -1;
        if (write_full(wfd, &cgap, sizeof cgap) != 0) return -1;
        if (write_full(wfd, &cjust, sizeof cjust) != 0) return -1;
        if (write_full(wfd, &ccols, sizeof ccols) != 0) return -1;
        if (write_full(wfd, &bl, sizeof bl) != 0) return -1;
        if (write_full(wfd, &br, sizeof br) != 0) return -1;
        if (write_full(wfd, &bw, sizeof bw) != 0) return -1;
        if (write_full(wfd, &bcenter, sizeof bcenter) != 0) return -1;
        if (write_full(wfd, &bmt, sizeof bmt) != 0) return -1;
        if (write_full(wfd, &bmb, sizeof bmb) != 0) return -1;
        if (write_full(wfd, &itype, sizeof itype) != 0) return -1;
        if (write_full(wfd, &fid, sizeof fid) != 0) return -1;
        if (write_full(wfd, &method, sizeof method) != 0) return -1;
        if (write_full(wfd, &nmlen, sizeof nmlen) != 0) return -1;
        if (nmlen != 0 && write_full(wfd, r->name, nmlen) != 0) return -1;
        if (write_full(wfd, &vllen, sizeof vllen) != 0) return -1;
        if (vllen != 0 && write_full(wfd, r->value, vllen) != 0) return -1;
    }
    return 0;
}

/* Console section (Freebug): [n:int32] then per entry
 * [level:int32][line:int32][col:int32][flen:size_t][file][elen:size_t][text].
 * n is bounded by FB_MAX_ENTRIES, elen by FB_MAX_ENTRY_BYTES and flen by
 * FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. file is the source name of an error's throw site (developer aid). */
static int write_console(int wfd, const fb_buffer *log) {
    int32_t n = (int32_t)fb_buffer_count(log);
    if (write_full(wfd, &n, sizeof n) != 0) return -1;
    for (int32_t i = 0; i < n; ++i) {
        const fb_entry *e = fb_buffer_at(log, (size_t)i);
        int32_t level = e->level;
        int32_t line  = e->line;
        int32_t col   = e->col;
        size_t  flen  = (e->file != NULL) ? strlen(e->file) : 0;
        size_t  elen  = e->len;
        if (flen > FB_MAX_FILE_BYTES) flen = FB_MAX_FILE_BYTES;
        if (write_full(wfd, &level, sizeof level) != 0
         || write_full(wfd, &line, sizeof line) != 0
         || write_full(wfd, &col, sizeof col) != 0
         || write_full(wfd, &flen, sizeof flen) != 0
         || (flen != 0 && write_full(wfd, e->file, flen) != 0)
         || write_full(wfd, &elen, sizeof elen) != 0
         || (elen != 0 && write_full(wfd, e->text, elen) != 0))
            return -1;
    }
    return 0;
}

/* Response: [ok:int32][title_len][title][text_len][text][view][navreq_len][navreq][nav_replace:int32][console].
 * navreq is the RAW (unresolved) navigation the page's JS requested; the parent gates it
 * with ln_resolve. On any failure the page is reset and ok==0 is reported (no partial state). */
/* Milliseconds of `budget_ms` still left since `start` (CLOCK_MONOTONIC), 0 if spent.
 * Used to share one page-wide JS budget across the inline scripts run individually. */
static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    int64_t elapsed = (int64_t)(now.tv_sec - start->tv_sec) * 1000
                    + (now.tv_nsec - start->tv_nsec) / 1000000;
    if (elapsed < 0) elapsed = 0;
    if ((uint64_t)elapsed >= budget_ms) return 0;
    return budget_ms - (uint64_t)elapsed;
}

static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
                              int run_js, int reader, int prefers_dark, const char *page_url) {
    char  *title = NULL, *text = NULL;
    size_t tl = 0, xl = 0;
    pv_view *view = NULL;
    char navbuf[LN_MAX_TARGET];
    navbuf[0] = '\0';
    int32_t nav_replace = 0;
    int ok = (child_load(cs, html, len, run_js, page_url) == 0);
    if (ok && run_js) {
        /* Execute the page's inline scripts in the sandboxed context, THEN derive
         * the view, so DOM mutations (document.title / textContent) are reflected.
         * Each <script> is run as its own program, exactly as a browser does: an
         * uncaught error in one is surfaced to the Freebug console but does NOT abort
         * the others (concatenating them would let the first failure kill them all --
         * the root cause of "loads nothing" on script-heavy pages). A single page-wide
         * wall-clock budget is shared across every script and the synthetic load/timer
         * pump, so isolating scripts never multiplies the cap. The DOM bridge is
         * read-mostly (safe mutators), so a script cannot corrupt the tree. */
        size_t nscripts = 0;
        hp_script *scripts = hp_extract_script_list(cs->doc, &nscripts);
        struct timespec t0;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        for (size_t i = 0; i < nscripts; i++) {
            uint64_t rem = budget_remaining_ms(&t0, JS_DEFAULT_TIME_BUDGET);
            if (rem == 0) break; /* page JS budget spent; stop running scripts */
            js_set_time_budget(cs->js, rem);
            js_result r;
            memset(&r, 0, sizeof r);
            /* Name each inline <script> so an uncaught error in it reports a
             * meaningful "file" (the page itself is shown in the URL bar). */
            char sname[32];
            snprintf(sname, sizeof sname, "inline #%zu", i + 1);
            js_status es = js_eval_named(cs->js, scripts[i].text, scripts[i].len,
                                         sname, &r);
            if (es != JS_OK && r.is_exception && r.value != NULL)
                fb_buffer_push_loc(&cs->log, FB_ERROR, r.value, r.value_len,
                                   r.file, r.line, r.col);
            js_result_free(&r);
        }
        hp_free_scripts(scripts, nscripts);
        /* Fire synthetic DOMContentLoaded/load handlers + flush queued timers once
         * (bounded; not a real event loop), so onload-wrapped code runs -- under the
         * same remaining page budget. */
        uint64_t rem = budget_remaining_ms(&t0, JS_DEFAULT_TIME_BUDGET);
        if (rem > 0) {
            js_set_time_budget(cs->js, rem);
            static const char fire[] = "if(typeof __fireDeferred==='function')__fireDeferred();";
            js_result fr;
            memset(&fr, 0, sizeof fr);
            (void)js_eval(cs->js, fire, sizeof fire - 1, &fr);
            js_result_free(&fr);
        }
        /* Restore the full per-eval budget for any REPL (tab_eval) on this context. */
        js_set_time_budget(cs->js, JS_DEFAULT_TIME_BUDGET);
        /* Capture any navigation the script requested (location.href=/assign/replace/
         * reload). Raw and unresolved: the parent gates it (Zero Trust). */
        int rep = 0;
        (void)jd_take_nav_request(cs->js, navbuf, sizeof navbuf, &rep);
        nav_replace = rep ? 1 : 0;
    }
    if (ok) {
        title = hp_get_title(cs->doc, &tl);
        text  = hp_extract_text(cs->doc, &xl);
        if (title == NULL || text == NULL
            || pv_build_full(cs->doc, run_js, reader, prefers_dark, &view) != PV_OK) {
            ok = 0;
            child_reset_page(cs);
        }
    }

    int32_t k = ok ? 1 : 0;
    if (write_full(wfd, &k, sizeof k) == 0 && ok) {
        size_t nlen = strlen(navbuf);
        (void)(write_full(wfd, &tl, sizeof tl) == 0
            && (tl == 0 || write_full(wfd, title, tl) == 0)
            && write_full(wfd, &xl, sizeof xl) == 0
            && (xl == 0 || write_full(wfd, text, xl) == 0)
            && write_view(wfd, view) == 0
            && write_full(wfd, &nlen, sizeof nlen) == 0
            && (nlen == 0 || write_full(wfd, navbuf, nlen) == 0)
            && write_full(wfd, &nav_replace, sizeof nav_replace) == 0
            && write_console(wfd, &cs->log) == 0);
    }
    hp_free(title);
    hp_free(text);
    pv_free(view);
}

/* Response: [ok:int32][is_exception:int32][value_len][value]. ok==0 means a
 * worker-level failure (no page loaded); a JS-level error is ok==1 with the
 * exception flag set. */
static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len) {
    if (cs->js == NULL) {
        int32_t k = 0;
        (void)write_full(wfd, &k, sizeof k);
        return;
    }

    /* Fresh transcript: this eval reports only its own console output. */
    fb_buffer_reset(&cs->log);

    js_result r;
    js_status s = js_eval_named(cs->js, js, len, "<repl>", &r);
    int32_t  ok = 1;
    int32_t  is_exc = (s != JS_OK) ? 1 : 0;
    const char *val = (r.value != NULL) ? r.value : "";
    size_t   vlen = (r.value != NULL) ? r.value_len : 0;

    if (write_full(wfd, &ok, sizeof ok) == 0) {
        (void)(write_full(wfd, &is_exc, sizeof is_exc) == 0
            && write_full(wfd, &vlen, sizeof vlen) == 0
            && (vlen == 0 || write_full(wfd, val, vlen) == 0)
            && write_console(wfd, &cs->log) == 0);
    }
    js_result_free(&r);
}

/* Response: [ok:int32] then, when ok, [w:u32][h:u32][stride:u32][len:size_t][data].
 * Decoding hostile image bytes happens here, inside the confinement; ok==0 means
 * the bytes were not a decodable PNG/JPEG (no partial pixels are sent). */
static void child_handle_decode_image(int wfd, const char *bytes, size_t len) {
    img_pixels px;
    memset(&px, 0, sizeof px);
    int ok = (img_decode((const uint8_t *)bytes, len, &px) == IMG_OK);
    int32_t k = ok ? 1 : 0;
    if (write_full(wfd, &k, sizeof k) == 0 && ok) {
        uint32_t w = px.width, h = px.height, stride = px.stride;
        size_t dlen = (size_t)stride * (size_t)h;
        (void)(write_full(wfd, &w, sizeof w) == 0
            && write_full(wfd, &h, sizeof h) == 0
            && write_full(wfd, &stride, sizeof stride) == 0
            && write_full(wfd, &dlen, sizeof dlen) == 0
            && (dlen == 0 || write_full(wfd, px.data, dlen) == 0));
    }
    img_pixels_free(&px);
}

static uint64_t gen_session_key(void) {
    uint64_t k = 0;
    uint8_t *p = (uint8_t *)&k;
    size_t got = 0;
    while (got < sizeof k) {
        ssize_t r = getrandom(p + got, sizeof k - got, 0);
        if (r < 0) { if (errno == EINTR) continue; break; }
        got += (size_t)r;
    }
    if (got < sizeof k) { /* fallback: still distinct per process start */
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        k ^= ((uint64_t)ts.tv_sec << 20) ^ (uint64_t)ts.tv_nsec
           ^ ((uint64_t)getpid() << 1);
    }
    return k;
}

/* The confined request loop. Runs in the re-exec'd worker image (see
 * tab_worker_dispatch). Never returns to the caller (always _exit). */
static void tab_worker_run(int rfd, int wfd) {
    /* The exec reset SIGPIPE to default; restore SIG_IGN so a write to a dead parent
     * surfaces as EPIPE (graceful loop exit), not a signal. */
    ignore_sigpipe();

    child_state cs;
    memset(&cs, 0, sizeof cs);
    cs.session_key = gen_session_key();

    /* Confine before any content. Namespace isolation and Landlock are best-effort
     * defense in depth (seccomp already excludes open/socket/exec); seccomp is
     * mandatory: if it cannot be installed, report not-confined and exit (fail
     * closed). Namespaces go first: unshare(CLONE_NEWUSER) needs a single-threaded
     * context, which this freshly exec'd image is, and detaching the network/IPC/UTS
     * stacks means even a seccomp bypass finds no network to reach. */
    os_isolate_namespaces();
    os_no_dump();
    os_landlock_restrict(NULL, 0);
    uint8_t hs = (os_harden(OS_VIOLATION_KILL) == OS_OK) ? TAB_READY : TAB_NO_CONFINE;
    if (write_full(wfd, &hs, 1) != 0 || hs != TAB_READY) {
        _exit(hs == TAB_READY ? 0 : 70);
    }

    for (;;) {
        uint8_t op;
        if (read_full(rfd, &op, 1) != 0) break; /* EOF / error => quit */
        if (op == OP_QUIT) break;
        if (op != OP_LOAD && op != OP_EVAL && op != OP_DECODE_IMAGE) break; /* desync */

        /* OP_LOAD carries three leading flag bytes: run_js (JS policy), reader
         * (distraction-free) and dark (prefers-color-scheme), then the page URL
         * (for the real location), before length+payload. */
        uint8_t run_js = 0, reader = 0, dark = 0;
        char *url = NULL;
        if (op == OP_LOAD) {
            if (read_full(rfd, &run_js, 1) != 0
             || read_full(rfd, &reader, 1) != 0
             || read_full(rfd, &dark, 1) != 0) break;
            size_t ulen = 0;
            if (read_full(rfd, &ulen, sizeof ulen) != 0) break;
            if (ulen > TAB_MAX_URL) break; /* defensive: URLs are small */
            url = (char *)malloc(ulen + 1);
            if (url == NULL) break;
            if (ulen != 0 && read_full(rfd, url, ulen) != 0) { free(url); break; }
            url[ulen] = '\0';
        }

        size_t len = 0;
        if (read_full(rfd, &len, sizeof len) != 0) { free(url); break; }
        if (len > TAB_MAX_INPUT) { free(url); break; } /* parent enforces; defensive */

        char *buf = (char *)malloc(len + 1);
        if (buf == NULL) { free(url); break; }
        if (len != 0 && read_full(rfd, buf, len) != 0) { free(buf); free(url); break; }
        buf[len] = '\0';

        if (op == OP_LOAD)              child_handle_load(wfd, &cs, buf, len, run_js, reader, dark, url);
        else if (op == OP_EVAL)         child_handle_eval(wfd, &cs, buf, len);
        else /* OP_DECODE_IMAGE */      child_handle_decode_image(wfd, buf, len);
        free(buf);
        free(url);
    }

    child_reset_page(&cs);
    fb_buffer_free(&cs.log);
    _exit(0);
}

/* --- worker entry dispatch (the re-exec'd image lands here from main) --- */

/* Parses one strictly-decimal, non-negative, sanely-bounded fd. Fail-closed. */
static int parse_worker_fd(const char *s, int *out) {
    if (s == NULL || *s == '\0') return 0;
    long v = 0;
    for (const char *p = s; *p != '\0'; ++p) {
        if (*p < '0' || *p > '9') return 0;
        v = v * 10 + (*p - '0');
        if (v > 1048576) return 0; /* far above any real fd; reject as garbage */
    }
    *out = (int)v;
    return 1;
}

int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd) {
    if (argc < 4 || argv == NULL || rfd == NULL || wfd == NULL) return 0;
    if (argv[1] == NULL || strcmp(argv[1], "--tab-worker") != 0) return 0;
    int a = -1, b = -1;
    if (!parse_worker_fd(argv[2], &a) || !parse_worker_fd(argv[3], &b)) return 0;
    *rfd = a;
    *wfd = b;
    return 1;
}

void tab_worker_dispatch(int argc, char **argv) {
    int rfd = -1, wfd = -1;
    if (!tab_parse_worker_args(argc, (const char *const *)argv, &rfd, &wfd))
        return; /* not a worker invocation: the caller's main() proceeds normally */
    tab_worker_run(rfd, wfd); /* confines, serves the request loop */
    _exit(0);                 /* never returns to main(): no atexit/LSan under seccomp */
}

/* =========================== parent side ============================= */

struct tab {
    pid_t pid;
    int   req_fd;   /* parent writes requests here */
    int   resp_fd;  /* parent reads responses here */
    int   alive;
    int   reaped;   /* the child has been waited on; do not kill/wait again */
};

/* A write to a dead child must not kill the parent with SIGPIPE. Idempotent;
 * no module-level mutable state of our own (the disposition is process-wide). */
static void ignore_sigpipe(void) {
    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &sa, NULL);
}

static void tab_refresh_alive(tab *t) {
    if (t == NULL || t->reaped || t->pid <= 0) return;
    int st;
    pid_t r = waitpid(t->pid, &st, WNOHANG);
    if (r == t->pid)                   { t->alive = 0; t->reaped = 1; }
    else if (r < 0 && errno == ECHILD) { t->alive = 0; t->reaped = 1; }
    /* r == 0: still running, liveness unchanged. */
}

/* Read one length-prefixed owned field from the child, capped against
 * amplification. *out is NUL-terminated. */
static int read_field(int fd, char **out, size_t *out_len) {
    size_t n = 0;
    if (read_full(fd, &n, sizeof n) != 0) return -1;
    if (n > TAB_MAX_INPUT) return -1;
    char *buf = (char *)malloc(n + 1);
    if (buf == NULL) return -1;
    if (n != 0 && read_full(fd, buf, n) != 0) { free(buf); return -1; }
    buf[n] = '\0';
    *out = buf;
    *out_len = n;
    return 0;
}

/* Reads a display list serialised by write_view into a fresh pv_view. The run
 * count and each field are capped against amplification from a hostile child. */
static int read_view(int fd, pv_view **out) {
    *out = NULL;
    size_t n = 0;
    if (read_full(fd, &n, sizeof n) != 0) return -1;
    if (n > TAB_MAX_RUNS) return -1;

    pv_view *v = pv_new();
    if (v == NULL) return -1;

    for (size_t i = 0; i < n; ++i) {
        int32_t kind = 0, heading = 0, bold = 0, italic = 0, indent = 0, brk = 0;
        int32_t img_w = -1, img_h = -1, fg = -1, bg = -1;
        int32_t talign = 0, fscale = 0, lscale = 0, deco = -1;
        int32_t ffam = 0, ttrans = 0, lspc = PV_LEN_UNSET, wspc = PV_LEN_UNSET;
        int32_t shdx = 0, shdy = 0, shcol = -1, opac = -1, valgn = 0;
        int32_t tindent = PV_LEN_UNSET, wspace = 0;
        int32_t cid = -1, cdisp = 0, cgap = 0, cjust = 0, ccols = 0;
        int32_t bl = 0, br = 0, bw = 0, bcenter = 0;
        int32_t bmt = PV_LEN_UNSET, bmb = PV_LEN_UNSET;
        int32_t itype = 0, fid = -1, method = 0;
        if (read_full(fd, &kind, sizeof kind) != 0
         || read_full(fd, &heading, sizeof heading) != 0
         || read_full(fd, &bold, sizeof bold) != 0
         || read_full(fd, &italic, sizeof italic) != 0
         || read_full(fd, &indent, sizeof indent) != 0
         || read_full(fd, &brk, sizeof brk) != 0) {
            pv_free(v);
            return -1;
        }
        char *text = NULL, *href = NULL, *src = NULL, *name = NULL, *value = NULL;
        size_t tl = 0, hl = 0, sl = 0, nl = 0, vl = 0;
        if (read_field(fd, &text, &tl) != 0) { pv_free(v); return -1; }
        if (read_field(fd, &href, &hl) != 0) { free(text); pv_free(v); return -1; }
        if (read_field(fd, &src, &sl) != 0) { free(text); free(href); pv_free(v); return -1; }
        if (read_full(fd, &img_w, sizeof img_w) != 0
         || read_full(fd, &img_h, sizeof img_h) != 0
         || read_full(fd, &fg, sizeof fg) != 0
         || read_full(fd, &bg, sizeof bg) != 0
         || read_full(fd, &talign, sizeof talign) != 0
         || read_full(fd, &fscale, sizeof fscale) != 0
         || read_full(fd, &lscale, sizeof lscale) != 0
         || read_full(fd, &deco, sizeof deco) != 0
         || read_full(fd, &ffam, sizeof ffam) != 0
         || read_full(fd, &ttrans, sizeof ttrans) != 0
         || read_full(fd, &lspc, sizeof lspc) != 0
         || read_full(fd, &wspc, sizeof wspc) != 0
         || read_full(fd, &shdx, sizeof shdx) != 0
         || read_full(fd, &shdy, sizeof shdy) != 0
         || read_full(fd, &shcol, sizeof shcol) != 0
         || read_full(fd, &opac, sizeof opac) != 0
         || read_full(fd, &valgn, sizeof valgn) != 0
         || read_full(fd, &tindent, sizeof tindent) != 0
         || read_full(fd, &wspace, sizeof wspace) != 0
         || read_full(fd, &cid, sizeof cid) != 0
         || read_full(fd, &cdisp, sizeof cdisp) != 0
         || read_full(fd, &cgap, sizeof cgap) != 0
         || read_full(fd, &cjust, sizeof cjust) != 0
         || read_full(fd, &ccols, sizeof ccols) != 0
         || read_full(fd, &bl, sizeof bl) != 0
         || read_full(fd, &br, sizeof br) != 0
         || read_full(fd, &bw, sizeof bw) != 0
         || read_full(fd, &bcenter, sizeof bcenter) != 0
         || read_full(fd, &bmt, sizeof bmt) != 0
         || read_full(fd, &bmb, sizeof bmb) != 0
         || read_full(fd, &itype, sizeof itype) != 0
         || read_full(fd, &fid, sizeof fid) != 0
         || read_full(fd, &method, sizeof method) != 0) {
            free(text); free(href); free(src); pv_free(v); return -1;
        }
        if (read_field(fd, &name, &nl) != 0) { free(text); free(href); free(src); pv_free(v); return -1; }
        if (read_field(fd, &value, &vl) != 0) {
            free(text); free(href); free(src); free(name); pv_free(v); return -1;
        }

        pv_status st;
        if (kind == PV_INPUT) {
            st = pv_append_input(v, heading, brk, (pv_input_type)itype, text,
                                 (nl > 0) ? name : NULL, (vl > 0) ? value : NULL,
                                 (hl > 0) ? href : NULL, (int)fid, (int)method);
        } else if (kind == PV_IMAGE && sl > 0) {
            st = pv_append_image(v, heading, brk, text, src, img_w, img_h);
        } else {
            pv_kind k = (kind == PV_LINK && hl > 0) ? PV_LINK : PV_TEXT;
            st = pv_append(v, k, heading, brk, text, (hl > 0) ? href : NULL);
        }
        free(text);
        free(href);
        free(src);
        free(name);
        free(value);
        if (st != PV_OK) { pv_free(v); return -1; }
        if (kind != PV_INPUT) {
            pv_set_emphasis(v, (int)bold, (int)italic);
            pv_set_indent(v, (int)indent);
            pv_set_color(v, (int)fg);
            pv_set_bgcolor(v, (int)bg);
            pv_set_text_style(v, (int)talign, (int)fscale, (int)lscale, (int)deco);
            pv_set_text_ext(v, (int)ffam, (int)ttrans, (int)lspc, (int)wspc, (int)shdx,
                            (int)shdy, (int)shcol, (int)opac, (int)valgn, (int)tindent,
                            (int)wspace);
            pv_set_container(v, (int)cid, (int)cdisp, (int)cgap, (int)cjust, (int)ccols);
            pv_set_box(v, (int)bl, (int)br, (int)bw, (int)bcenter, (int)bmt, (int)bmb);
        }
    }

    *out = v;
    return 0;
}

/* Reads the console section written by write_console into out (a zero-initialised
 * fb_buffer). Bounds the entry count and each length against amplification from a
 * hostile child, mirroring the buffer's own caps. */
static int read_console(int fd, fb_buffer *out) {
    int32_t n = 0;
    if (read_full(fd, &n, sizeof n) != 0) return -1;
    if (n < 0 || (size_t)n > FB_MAX_ENTRIES) return -1;
    for (int32_t i = 0; i < n; ++i) {
        int32_t level = 0, line = 0, col = 0;
        size_t  flen = 0, elen = 0;
        if (read_full(fd, &level, sizeof level) != 0
         || read_full(fd, &line, sizeof line) != 0
         || read_full(fd, &col, sizeof col) != 0
         || read_full(fd, &flen, sizeof flen) != 0) return -1;
        if (flen > FB_MAX_FILE_BYTES) return -1;
        char *file = NULL;
        if (flen != 0) {
            file = (char *)malloc(flen + 1);
            if (file == NULL) return -1;
            if (read_full(fd, file, flen) != 0) { free(file); return -1; }
            file[flen] = '\0';
        }
        if (read_full(fd, &elen, sizeof elen) != 0) { free(file); return -1; }
        if (elen > FB_MAX_ENTRY_BYTES) { free(file); return -1; }
        char *txt = NULL;
        if (elen != 0) {
            txt = (char *)malloc(elen);
            if (txt == NULL) { free(file); return -1; }
            if (read_full(fd, txt, elen) != 0) { free(txt); free(file); return -1; }
        }
        (void)fb_buffer_push_loc(out, level, (txt != NULL) ? txt : "", elen,
                                 file, line, col);
        free(txt);
        free(file);
    }
    return 0;
}

/* Sends [op][len][payload]; classifies a transport failure as dead vs io. */
static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len) {
    if (write_full(t->req_fd, &op, 1) != 0
     || write_full(t->req_fd, &len, sizeof len) != 0
     || (len != 0 && write_full(t->req_fd, payload, len) != 0)) {
        tab_refresh_alive(t);
        return t->alive ? TAB_ERR_IO : TAB_ERR_DEAD;
    }
    return TAB_OK;
}

static tab_status io_failure(tab *t) {
    tab_refresh_alive(t);
    return t->alive ? TAB_ERR_IO : TAB_ERR_DEAD;
}

/* Child half of the fork: re-exec a fresh worker image so it inherits NONE of the
 * parent's address space (no other tabs' content from tab_slots[], fresh ASLR) and
 * none of its descriptors except the two pipe ends. Never returns on success. */
static void exec_worker_child(int rfd, int wfd) {
    /* Mark every descriptor >= 3 close-on-exec, then clear it on just the two pipe
     * ends the worker keeps: the re-exec'd image sees no Wayland socket, no fetch
     * pipe, no other parent fd. (stdio 0..2 stay open for diagnostics.) */
    close_range(3, ~0U, CLOSE_RANGE_CLOEXEC);
    int rf = fcntl(rfd, F_GETFD); if (rf >= 0) fcntl(rfd, F_SETFD, rf & ~FD_CLOEXEC);
    int wf = fcntl(wfd, F_GETFD); if (wf >= 0) fcntl(wfd, F_SETFD, wf & ~FD_CLOEXEC);

    char rbuf[16], wbuf[16];
    snprintf(rbuf, sizeof rbuf, "%d", rfd);
    snprintf(wbuf, sizeof wbuf, "%d", wfd);
    char *const av[] = { (char *)"freedom", (char *)"--tab-worker", rbuf, wbuf, NULL };
    execv("/proc/self/exe", av);
    /* exec failed: the caller _exit()s without a handshake, so the parent's read
     * sees EOF and returns TAB_ERR_CONFINE (fail closed). */
}

tab_status tab_open(tab **out) {
    if (out == NULL) return TAB_ERR_NULL_ARG;
    *out = NULL;

    int req[2], resp[2];
    if (pipe(req) != 0) return TAB_ERR_SPAWN;
    if (pipe(resp) != 0) {
        close(req[0]); close(req[1]);
        return TAB_ERR_SPAWN;
    }

    ignore_sigpipe();

    pid_t pid = fork();
    if (pid < 0) {
        close(req[0]); close(req[1]); close(resp[0]); close(resp[1]);
        return TAB_ERR_SPAWN;
    }
    if (pid == 0) {
        close(req[1]); close(resp[0]);
        exec_worker_child(req[0], resp[1]);
        _exit(127); /* exec failed -> fail closed (no handshake -> TAB_ERR_CONFINE) */
    }

    /* Parent: keep the request-write and response-read ends only. */
    close(req[0]);
    close(resp[1]);

    /* Confirm the child confined itself before trusting it with content. */
    uint8_t hs = 0;
    if (read_full(resp[0], &hs, 1) != 0 || hs != TAB_READY) {
        close(req[1]); close(resp[0]);
        int st; while (waitpid(pid, &st, 0) < 0 && errno == EINTR) { /* retry */ }
        return TAB_ERR_CONFINE;
    }

    tab *t = (tab *)calloc(1, sizeof *t);
    if (t == NULL) {
        close(req[1]); close(resp[0]);
        kill(pid, SIGKILL);
        int st; while (waitpid(pid, &st, 0) < 0 && errno == EINTR) { /* retry */ }
        return TAB_ERR_OOM;
    }
    t->pid = pid;
    t->req_fd = req[1];
    t->resp_fd = resp[0];
    t->alive = 1;
    t->reaped = 0;
    *out = t;
    return TAB_OK;
}

tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out) {
    return tab_load_ex(t, html, len, 0, out); /* JS off by default */
}

tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out) {
    return tab_load_full(t, html, len, NULL, run_js, 0, 0, out);
}

tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
                         int run_js, int reader, int prefers_dark, tab_page *out) {
    if (t == NULL || out == NULL || html == NULL) return TAB_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (len > TAB_MAX_INPUT) return TAB_ERR_TOO_LARGE;
    size_t ulen = (page_url != NULL) ? strlen(page_url) : 0;
    if (ulen > TAB_MAX_URL) return TAB_ERR_TOO_LARGE;

    tab_refresh_alive(t);
    if (!t->alive) return TAB_ERR_DEAD;

    /* OP_LOAD framing: [op][run_js:1][reader:1][dark:1][url_len][url][len][html] (the
     * flags and URL precede the payload so the html stays zero-copy). */
    uint8_t op = OP_LOAD, jflag = run_js ? 1 : 0, rflag = reader ? 1 : 0,
            dflag = prefers_dark ? 1 : 0;
    if (write_full(t->req_fd, &op, 1) != 0
     || write_full(t->req_fd, &jflag, 1) != 0
     || write_full(t->req_fd, &rflag, 1) != 0
     || write_full(t->req_fd, &dflag, 1) != 0
     || write_full(t->req_fd, &ulen, sizeof ulen) != 0
     || (ulen != 0 && write_full(t->req_fd, page_url, ulen) != 0)
     || write_full(t->req_fd, &len, sizeof len) != 0
     || (len != 0 && write_full(t->req_fd, html, len) != 0)) {
        tab_refresh_alive(t);
        return t->alive ? TAB_ERR_IO : TAB_ERR_DEAD;
    }

    int32_t ok = 0;
    if (read_full(t->resp_fd, &ok, sizeof ok) != 0) return io_failure(t);
    if (!ok) return TAB_ERR_RENDER;

    char *title = NULL, *text = NULL;
    size_t tl = 0, xl = 0;
    if (read_field(t->resp_fd, &title, &tl) != 0
     || read_field(t->resp_fd, &text, &xl) != 0) {
        free(title); free(text);
        return io_failure(t);
    }
    pv_view *view = NULL;
    if (read_view(t->resp_fd, &view) != 0) {
        free(title); free(text);
        return io_failure(t);
    }
    /* Raw (unresolved) navigation the page's JS requested + its replace flag. */
    char *navreq = NULL;
    size_t nlen = 0;
    int32_t nav_replace = 0;
    if (read_field(t->resp_fd, &navreq, &nlen) != 0
     || read_full(t->resp_fd, &nav_replace, sizeof nav_replace) != 0) {
        free(title); free(text); free(navreq); pv_free(view);
        return io_failure(t);
    }
    /* Captured console transcript for Freebug. */
    fb_buffer console;
    fb_buffer_init(&console);
    if (read_console(t->resp_fd, &console) != 0) {
        free(title); free(text); free(navreq); pv_free(view);
        fb_buffer_free(&console);
        return io_failure(t);
    }

    /* Gate the raw request HERE (trusted parent, Zero Trust): a compromised worker
     * cannot drive the browser off-policy. ln_resolve allows only https / a local
     * file under a local base; a downgrade / foreign scheme / fragment yields no nav. */
    char *nav_url = NULL;
    if (nlen != 0 && page_url != NULL) {
        ln_result ln;
        if (ln_resolve(page_url, navreq, &ln) == LN_OK && ln.action == LN_NAVIGATE) {
            nav_url = strdup(ln.target);
            if (nav_url == NULL) {
                free(title); free(text); free(navreq); pv_free(view);
                fb_buffer_free(&console);
                return TAB_ERR_OOM;
            }
        }
    }
    free(navreq);

    out->title = title; out->title_len = tl;
    out->text  = text;  out->text_len  = xl;
    out->view  = view;
    out->nav_url = nav_url;
    out->nav_replace = (nav_url != NULL) ? (nav_replace ? 1 : 0) : 0;
    out->console = console; /* ownership moves to the caller (tab_page_free) */
    return TAB_OK;
}

tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out) {
    if (t == NULL || out == NULL || js == NULL) return TAB_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (len > TAB_MAX_INPUT) return TAB_ERR_TOO_LARGE;

    tab_refresh_alive(t);
    if (!t->alive) return TAB_ERR_DEAD;

    tab_status sr = send_request(t, OP_EVAL, js, len);
    if (sr != TAB_OK) return sr;

    int32_t ok = 0;
    if (read_full(t->resp_fd, &ok, sizeof ok) != 0) return io_failure(t);
    if (!ok) return TAB_ERR_SCRIPT; /* no page loaded / worker-level failure */

    int32_t is_exc = 0;
    if (read_full(t->resp_fd, &is_exc, sizeof is_exc) != 0) return io_failure(t);

    char *val = NULL;
    size_t vlen = 0;
    if (read_field(t->resp_fd, &val, &vlen) != 0) return io_failure(t);

    /* Console output produced by this eval (Freebug REPL transcript). */
    fb_buffer console;
    fb_buffer_init(&console);
    if (read_console(t->resp_fd, &console) != 0) {
        free(val); fb_buffer_free(&console);
        return io_failure(t);
    }

    out->value = val;
    out->value_len = vlen;
    out->is_exception = is_exc ? 1 : 0;
    out->console = console; /* ownership moves to the caller (tab_eval_result_free) */
    return TAB_OK;
}

tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out) {
    if (t == NULL || out == NULL || (bytes == NULL && len != 0)) return TAB_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (len > TAB_MAX_INPUT) return TAB_ERR_TOO_LARGE;

    tab_refresh_alive(t);
    if (!t->alive) return TAB_ERR_DEAD;

    tab_status sr = send_request(t, OP_DECODE_IMAGE, (const char *)bytes, len);
    if (sr != TAB_OK) return sr;

    int32_t ok = 0;
    if (read_full(t->resp_fd, &ok, sizeof ok) != 0) return io_failure(t);
    if (!ok) return TAB_OK; /* not decodable: out stays zeroed, caller shows placeholder */

    uint32_t w = 0, h = 0, stride = 0;
    size_t dlen = 0;
    if (read_full(t->resp_fd, &w, sizeof w) != 0
     || read_full(t->resp_fd, &h, sizeof h) != 0
     || read_full(t->resp_fd, &stride, sizeof stride) != 0
     || read_full(t->resp_fd, &dlen, sizeof dlen) != 0) {
        return io_failure(t);
    }
    /* Validate the worker's claims against the same anti-DoS bounds the decoder
     * enforces, so a hostile child cannot desync the stream or over-claim memory
     * (dimensions_ok bounds w,h <= IMG_MAX_DIM, so w*4 and stride*h cannot overflow). */
    if (!img_dimensions_ok(w, h) || stride != w * 4u
     || dlen != (size_t)stride * (size_t)h) {
        return io_failure(t);
    }

    uint8_t *data = (uint8_t *)malloc(dlen);
    if (data == NULL) return TAB_ERR_OOM;
    if (read_full(t->resp_fd, data, dlen) != 0) { free(data); return io_failure(t); }

    out->width = w;
    out->height = h;
    out->stride = stride;
    out->data = data;
    out->data_len = dlen;
    return TAB_OK;
}

int tab_alive(const tab *t) {
    if (t == NULL) return 0;
    tab_refresh_alive((tab *)t);
    return t->alive;
}

pid_t tab_child_pid(const tab *t) {
    return (t != NULL) ? t->pid : -1;
}

void tab_close(tab *t) {
    if (t == NULL) return;
    if (t->req_fd >= 0) close(t->req_fd);   /* EOF => the child quits its loop */
    if (t->resp_fd >= 0) close(t->resp_fd);
    if (t->pid > 0 && !t->reaped) {
        kill(t->pid, SIGKILL); /* defensive: guarantee prompt teardown */
        int st;
        while (waitpid(t->pid, &st, 0) < 0 && errno == EINTR) { /* retry */ }
    }
    free(t);
}

void tab_page_free(tab_page *p) {
    if (p == NULL) return;
    free(p->title);
    free(p->text);
    pv_free(p->view);
    free(p->nav_url);
    fb_buffer_free(&p->console);
    p->title = NULL;
    p->text = NULL;
    p->view = NULL;
    p->nav_url = NULL;
    p->nav_replace = 0;
    p->title_len = 0;
    p->text_len = 0;
}

void tab_eval_result_free(tab_eval_result *r) {
    if (r == NULL) return;
    free(r->value);
    fb_buffer_free(&r->console);
    r->value = NULL;
    r->value_len = 0;
    r->is_exception = 0;
}

void tab_image_free(tab_image *img) {
    if (img == NULL) return;
    free(img->data);
    img->data = NULL;
    img->width = 0;
    img->height = 0;
    img->stride = 0;
    img->data_len = 0;
}
