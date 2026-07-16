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
#include "css.h"
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
#include "util.h"

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
enum { OP_LOAD = 1, OP_EVAL = 2, OP_QUIT = 3, OP_DECODE_IMAGE = 4, OP_CLICK = 5,
       OP_TICK = 6, OP_SUBMIT = 7, OP_EVENT = 8, OP_MOUSE = 9 };

/* OP_LOAD response tags (child -> parent). While running the page's scripts the child
 * may issue zero or more TAG_SUBREQ subresource requests (XMLHttpRequest/fetch), which
 * the trusted parent fetches under full network policy; the final TAG_RESULT precedes
 * the page result. Only OP_LOAD carries tags (XHR is active only during page load). */
enum { TAG_SUBREQ = 1, TAG_RESULT = 2 };

/* Per-page subresource caps (anti-DoS): a hostile script cannot drive unbounded fetches
 * or amplification through the parent. */
#define TAB_MAX_SUBREQ        128
#define TAB_MAX_SUBRESOURCE   ((size_t)(16u * 1024u * 1024u))  /* matches SF_DEFAULT_MAX_BODY; modern app bundles (e.g. youtube main) exceed 8 MiB */
#define TAB_MAX_JS_JOBS       4096   /* pending-job pump bound (promise microtasks) */

/* Handshake bytes (child -> parent) after the confinement attempt. */
enum { TAB_READY = 0x55, TAB_NO_CONFINE = 0xAA };


/* =========================== child side ============================== */

typedef struct child_state {
    hp_document    *doc;
    dom_index      *idx;
    js_context     *js;
    jd_opaque       jd_op;  /* per-context binding state; lives with child_state */
    jd_click_state *click;  /* owned by child_state, freed on reset */
    uint64_t        session_key;
    fb_buffer       log; /* console capture (Freebug); persists across loads/evals */
    int             rfd;        /* worker read fd  (parent -> child): for subresource replies */
    int             wfd;        /* worker write fd (child -> parent): for subresource requests */
    int             net_active; /* 1 only during a page-load script window (XHR allowed) */
    int             subreq_used;/* subresource requests issued this load (capped) */
    int             last_run_js;       /* render params from the last OP_LOAD */
    int             last_reader;
    int             last_prefers_dark;
    char           *extern_css;        /* fetched <link rel=stylesheet> bodies (Hito 27); */
    size_t          extern_css_len;    /* kept so click/re-derive restyles without refetch */
    pv_view        *preserved_view;    /* pre-script DOM snapshot (fallback when jQuery */
                                        /* corrupts the tree on mutation re-derive) */
} child_state;

static void child_reset_page(child_state *cs) {
    if (cs->js != NULL) { js_context_free(cs->js); cs->js = NULL; }
    if (cs->click != NULL) { jd_click_state_free(cs->click); cs->click = NULL; }
    if (cs->idx != NULL) { dom_free(cs->idx); cs->idx = NULL; }
    if (cs->doc != NULL) { hp_document_free(cs->doc); cs->doc = NULL; }
    free(cs->extern_css);
    cs->extern_css = NULL;
    cs->extern_css_len = 0;
    pv_free(cs->preserved_view);
    cs->preserved_view = NULL;
}

/* jd_fetch_fn: the confined worker has NO network (CLONE_NEWNET + seccomp). An XHR/fetch
 * from page script is proxied to the TRUSTED parent over the existing pipes: write a
 * TAG_SUBREQ frame, block for the parent's reply. The parent re-applies the FULL network
 * policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a
 * compromised worker still cannot reach a blocked host. Refused/over-budget/IO-error =>
 * non-zero (XHR completes with status 0). Only callable inside a page-load script window
 * (net_active) so it never desyncs the OP_EVAL/OP_DECODE_IMAGE response paths. */
static int child_fetch(void *vctx, const char *method, const char *url,
                       const char *body, size_t body_len,
                       int *out_status, char **out_body, size_t *out_body_len,
                       char **out_ctype) {
    child_state *cs = (child_state *)vctx;
    *out_status = 0; *out_body = NULL; *out_body_len = 0; *out_ctype = NULL;
    if (cs == NULL || !cs->net_active) return -1;
    if (cs->subreq_used >= TAB_MAX_SUBREQ) return -1;
    size_t mlen = (method != NULL) ? strlen(method) : 0;
    size_t ulen = (url != NULL) ? strlen(url) : 0;
    if (ulen == 0 || ulen > TAB_MAX_URL || mlen > 16 || body_len > TAB_MAX_SUBRESOURCE)
        return -1;
    cs->subreq_used++;

    uint8_t tag = TAG_SUBREQ;
    if (write_full(cs->wfd, &tag, 1) != 0
     || write_full(cs->wfd, &mlen, sizeof mlen) != 0
     || (mlen != 0 && write_full(cs->wfd, method, mlen) != 0)
     || write_full(cs->wfd, &ulen, sizeof ulen) != 0
     || write_full(cs->wfd, url, ulen) != 0
     || write_full(cs->wfd, &body_len, sizeof body_len) != 0
     || (body_len != 0 && write_full(cs->wfd, body, body_len) != 0))
        return -1;

    int32_t status = 0;
    size_t rlen = 0, clen = 0;
    if (read_full(cs->rfd, &status, sizeof status) != 0
     || read_full(cs->rfd, &rlen, sizeof rlen) != 0
     || rlen > TAB_MAX_SUBRESOURCE)
        return -1;
    if (rlen == (size_t)-1) return -1;
    char *rbody = (char *)malloc(rlen + 1);
    if (rbody == NULL) return -1;
    if (rlen != 0 && read_full(cs->rfd, rbody, rlen) != 0) { free(rbody); return -1; }
    rbody[rlen] = '\0';
    if (read_full(cs->rfd, &clen, sizeof clen) != 0 || clen > 256) { free(rbody); return -1; }
    if (clen == (size_t)-1) { free(rbody); return -1; }
    char *ctype = (char *)malloc(clen + 1);
    if (ctype == NULL) { free(rbody); return -1; }
    if (clen != 0 && read_full(cs->rfd, ctype, clen) != 0) { free(rbody); free(ctype); return -1; }
    ctype[clen] = '\0';

    *out_status = (int)status; *out_body = rbody; *out_body_len = rlen; *out_ctype = ctype;
    return 0;
}

/* Parse + index + fresh JS context bound to the page and the anti-fp env. When
 * run_js, inline <script>s are kept (not stripped) so child_handle_load can execute
 * them; event-handler attributes (on*) are stripped regardless. page_url (may be
 * NULL/empty) backs the page JS's real `location.*`; navigation capture is armed
 * regardless of run_js (a no-JS load simply never records a request). */
static int child_load(child_state *cs, const char *html, size_t len, int run_js,
                      int net_allowed, const char *page_url) {
    child_reset_page(cs);
    cs->subreq_used = 0;

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
    cs->click = jd_click_state_new();
    if (cs->click == NULL) {
        js_context_free(js); dom_free(idx); hp_document_free(doc); return -1;
    }
    uint64_t readback_key = fp_origin_key(cs->session_key, rb_origin);
    if (jd_install(js, idx, &cs->jd_op) != JD_OK
     || jd_install_events(js, cs->click) != JD_OK
     || je_install(js, TAB_SCREEN_W, TAB_SCREEN_H) != JE_OK
     || je_install_canvas(js, readback_key) != JE_OK) {
        js_context_free(js); jd_click_state_free(cs->click); cs->click = NULL;
        dom_free(idx); hp_document_free(doc); return -1;
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
    /* Network APIs (XMLHttpRequest/fetch) are installed ONLY when the trusted parent
     * granted net access for this host (allow.conf AND js.conf). Otherwise they stay
     * undefined (Same-Origin-by-construction holds). child_fetch still refuses unless
     * net_active is set during the script window, so install is safe regardless. */
    if (run_js && net_allowed)
        (void)jd_install_xhr(js, child_fetch, cs);

    cs->doc = doc; cs->idx = idx; cs->js = js;
    return 0;
}

/* Writes one length-prefixed string field (the write mirror of read_field): a size_t
 * length then the bytes, with NULL/empty encoded as length 0. */
static int write_field(int fd, const char *s) {
    size_t len = (s != NULL) ? strlen(s) : 0;
    if (write_full(fd, &len, sizeof len) != 0) return -1;
    if (len != 0 && write_full(fd, s, len) != 0) return -1;
    return 0;
}

/* Serialises the display list:
 *   [count]( kind,heading,bold,italic,indent,break, text, href, src, img_w,img_h, fg_rgb,bg_rgb,
 *            text_align,font_scale,line_scale,text_decoration,
 *            font_family,text_transform,letter_spacing,word_spacing,
 *            shadow_dx,shadow_dy,shadow_color,opacity,valign,text_indent,white_space,
 *            text_overflow,word_break,
 *            cont_id,cont_display,cont_gap,cont_justify,cont_cols,
 *            cont_col_w[PV_GRID_TRACKS],grid_span,
 *            flex_grow,flex_shrink,flex_basis,flex_order,flex_direction,cont_item,
 *            cont_wrap,cont_row_gap,cont_align_items,flex_align_self,
 *            float_side,float_id,float_clear,
 *            box_l,box_r,box_w,box_center,box_mt,box_mb,box_w_pct,
 *            block_id,
 *            input_type,form_id,form_method, name, value )*
 * then the box-definition tree (Step D): [nbox]( the 58 box int32 fields )*. block_id on a
 * run says which box it belongs to; boxes[block_id] carries the decoration + parent.
 * with each string length-prefixed (a length of 0 means absent). The fixed-width
 * fields travel for every run so a hostile child cannot desync the stream by
 * varying the per-run layout; non-image runs carry an empty src and -1 dimensions,
 * a run without an author color carries fg_rgb == -1, and non-input runs carry an
 * empty name/value, form_id == -1 and form_method == 0.
 *
 * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the
 * grid array, block B[26]) exactly like the box-def f[] array, NOT one write_full per
 * field: the block literal lists each field once, so read_view mirrors it by index and
 * a desync becomes structurally hard. Adding a field is one entry in the write block +
 * one in the read extraction, like the box def. NO tags/versioning: the worker is the
 * SAME binary as the parent (/proc/self/exe --tab-worker), so write_view and read_view
 * are always the same build -- there is no version skew to tolerate. */
static int write_view(int wfd, const pv_view *v) {
    size_t n = pv_count(v);
    if (write_full(wfd, &n, sizeof n) != 0) return -1;
    for (size_t i = 0; i < n; ++i) {
        const pv_run *r = pv_at(v, i);
        int32_t head[6] = {
            (int32_t)r->kind, (int32_t)r->heading, (int32_t)r->bold,
            (int32_t)r->italic, (int32_t)r->indent, (int32_t)r->block_break,
        };
        /* Block A: fixed-width scalars between the head strings and the grid array
         * (image dims, colors, the whole text-presentation set, container params). */
        int32_t a[36] = {
            (int32_t)r->img_w, (int32_t)r->img_h, (int32_t)r->fg_rgb, (int32_t)r->bg_rgb,
            (int32_t)r->text_align, (int32_t)r->font_scale, (int32_t)r->line_scale,
            (int32_t)r->text_decoration, (int32_t)r->font_family, (int32_t)r->text_transform,
            (int32_t)r->letter_spacing, (int32_t)r->word_spacing,
            (int32_t)r->shadow_dx, (int32_t)r->shadow_dy, (int32_t)r->shadow_color,
            (int32_t)r->opacity, (int32_t)r->valign, (int32_t)r->text_indent,
            (int32_t)r->white_space, (int32_t)r->text_overflow, (int32_t)r->word_break,
            (int32_t)r->text_decoration_color, (int32_t)r->text_decoration_style,
            (int32_t)r->text_decoration_thickness,
            (int32_t)r->tab_size, (int32_t)r->direction, (int32_t)r->font_variant,
            (int32_t)r->list_style_pos, (int32_t)r->image_rendering, (int32_t)r->caret_color,
            (int32_t)r->object_fit,
            (int32_t)r->cont_id, (int32_t)r->cont_display, (int32_t)r->cont_gap,
            (int32_t)r->cont_justify, (int32_t)r->cont_cols,
        };
        int32_t gtw[PV_GRID_TRACKS + 1];
        for (int gk = 0; gk < PV_GRID_TRACKS; ++gk)
            gtw[gk] = (int32_t)r->cont_col_w[gk];
        gtw[PV_GRID_TRACKS] = (int32_t)r->grid_span;
        /* Block B: fixed-width scalars after the grid array (flex item, float, author
         * box model, block/node id, form control). */
        int32_t b[26] = {
            (int32_t)r->flex_grow, (int32_t)r->flex_shrink, (int32_t)r->flex_basis,
            (int32_t)r->flex_order, (int32_t)r->flex_direction, (int32_t)r->cont_item,
            (int32_t)r->cont_wrap, (int32_t)r->cont_row_gap, (int32_t)r->cont_align_items,
            (int32_t)r->flex_align_self,
            (int32_t)r->float_side, (int32_t)r->float_id, (int32_t)r->float_clear,
            (int32_t)r->box_l, (int32_t)r->box_r, (int32_t)r->box_w, (int32_t)r->box_center,
            (int32_t)r->box_mt, (int32_t)r->box_mb, (int32_t)r->box_w_pct,
            (int32_t)r->block_id, (int32_t)r->node_id,
            (int32_t)r->input_type, (int32_t)r->form_id, (int32_t)r->form_method,
            (int32_t)r->checked,
        };
        /* Wire order (unchanged): head, text|href|src|poster, A, grid, B,
         * select_opts|name|value. */
        if (write_full(wfd, head, sizeof head) != 0
         || write_field(wfd, r->text) != 0
         || write_field(wfd, r->href) != 0
         || write_field(wfd, r->src) != 0
         || write_field(wfd, r->poster_src) != 0
         || write_full(wfd, a, sizeof a) != 0
         || write_full(wfd, gtw, sizeof gtw) != 0
         || write_full(wfd, b, sizeof b) != 0
         || write_field(wfd, r->select_opts) != 0
         || write_field(wfd, r->name) != 0
         || write_field(wfd, r->value) != 0)
            return -1;
    }

    /* Box engine (Step D): the box TREE, after the run array. [nbox] then per box the
     * fixed-width fields in the SAME order read_view reconstructs them (the desync
     * gotcha). block_id is per-run above; here boxes[block_id] gives the decoration
     * + parent link. 2026-07-10 batch: 4 author-vertical-dimension fields appended
     * (height/min_h/max_h/min_w) -- the painter uses them in open_box. */
    size_t nb = pv_box_count(v);
    if (write_full(wfd, &nb, sizeof nb) != 0) return -1;
    for (size_t bi = 0; bi < nb; ++bi) {
        const pv_box_def *bd = pv_box_at(v, bi);
        int32_t f[58] = {
            (int32_t)bd->parent_id, (int32_t)bd->box_sizing,
            (int32_t)bd->pad_t, (int32_t)bd->pad_r, (int32_t)bd->pad_b, (int32_t)bd->pad_l,
            (int32_t)bd->bord_tw, (int32_t)bd->bord_rw, (int32_t)bd->bord_bw, (int32_t)bd->bord_lw,
            (int32_t)bd->bord_ts, (int32_t)bd->bord_rs, (int32_t)bd->bord_bs, (int32_t)bd->bord_ls,
            (int32_t)bd->bord_tc, (int32_t)bd->bord_rc, (int32_t)bd->bord_bc, (int32_t)bd->bord_lc,
            (int32_t)bd->border_radius,
            (int32_t)bd->bsh_dx, (int32_t)bd->bsh_dy, (int32_t)bd->bsh_blur,
            (int32_t)bd->bsh_spread, (int32_t)bd->bsh_color, (int32_t)bd->bsh_inset,
            (int32_t)bd->outline_w, (int32_t)bd->outline_style, (int32_t)bd->outline_color,
            (int32_t)bd->box_l, (int32_t)bd->box_r, (int32_t)bd->box_w, (int32_t)bd->box_center,
            (int32_t)bd->bg_rgb,
            /* positioning (appended; read_view reads these at the same indices) */
            (int32_t)bd->position,
            (int32_t)bd->inset_top, (int32_t)bd->inset_right,
            (int32_t)bd->inset_bottom, (int32_t)bd->inset_left,
            (int32_t)bd->z_index,
            /* visibility / overflow / cursor (appended; read_view mirrors this) */
            (int32_t)bd->visibility,
            (int32_t)bd->overflow_x, (int32_t)bd->overflow_y,
            (int32_t)bd->cursor,
            /* outline-offset + aspect-ratio (appended; read_view mirrors this) */
            (int32_t)bd->outline_offset,
            (int32_t)bd->aspect_num, (int32_t)bd->aspect_den,
            /* 2026-07-10 author vertical dimensions (appended; read_view mirrors this) */
            (int32_t)bd->box_h, (int32_t)bd->box_min_h, (int32_t)bd->box_max_h,
            (int32_t)bd->box_min_w,
            /* 2026-07-10 wiring batch: pointer-events (appended; read_view mirrors this) */
            (int32_t)bd->pointer_events,
            /* Hito 32: symbolic per-mille width cap (appended; read_view mirrors this) */
            (int32_t)bd->box_w_pct,
            /* linear-gradient background (2026-07-11; read_view mirrors this) */
            (int32_t)bd->grad_n, (int32_t)bd->grad_angle,
            (int32_t)bd->grad_c0, (int32_t)bd->grad_c1,
            (int32_t)bd->grad_c2, (int32_t)bd->grad_c3,
        };
        if (write_full(wfd, f, sizeof f) != 0) return -1;
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

/* Content-Type gate for an external script's response (anti type-confusion, fail
 * closed for real content types): accept a missing/empty type -- classic-script
 * behaviour -- or one containing "javascript"/"ecmascript"; refuse anything else,
 * so an HTML error page or a JSON body is never evaluated as script. */
static int ctype_is_javascript(const char *ctype) {
    if (ctype == NULL || ctype[0] == '\0') return 1;
    return strcasestr(ctype, "javascript") != NULL
        || strcasestr(ctype, "ecmascript") != NULL;
}

/* Content-Type gate for an external stylesheet (Hito 27), same shape as the script
 * gate: a missing/empty type is accepted, anything else must mention "css" -- an
 * HTML 404 page or a script body is never parsed as a sheet. */
static int ctype_is_css(const char *ctype) {
    if (ctype == NULL || ctype[0] == '\0') return 1;
    return strcasestr(ctype, "css") != NULL;
}

/* Freebug note about an external subresource (script/stylesheet) that was not
 * used (skipped or refused). The raw hostile src is bounded by the message
 * buffer; freebug caps the entry. */
static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                              const char *src) {
    char msg[512];
    int m = snprintf(msg, sizeof msg, "external %s %s: %s", kind, why, src);
    if (m < 0) return;
    size_t ml = ((size_t)m < sizeof msg) ? (size_t)m : sizeof msg - 1;
    (void)fb_buffer_push(log, FB_WARN, msg, ml);
}

/* Cap on the accumulated external stylesheet text (same order as page_view's
 * PV_MAX_STYLE_BYTES): a sheet that would overflow it is dropped WHOLE (fail
 * closed, never truncated mid-rule). */
#define TAB_MAX_EXTERN_CSS ((size_t)(1u << 20))

/* Injects PV_VIDEO runs from DOM-index video elements directly into the view,
 * bypassing the Lexbor tree walk which may miss them due to jQuery corruption
 * of sibling/child pointers. Scans cs->idx for <video> elements with non-empty
 * src and appends the first one found via pv_append_video. Skips if the view
 * already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every pv_build_styled so video survives both the initial load and
 * timer ticks. */
static void inject_video_into_view(child_state *cs, pv_view **vp) {
    if (cs == NULL || cs->idx == NULL || vp == NULL || *vp == NULL) return;
    /* Skip if the view already has a video run (already injected). */
    size_t nviews = pv_count(*vp);
    for (size_t i = 0; i < nviews; i++) {
        const pv_run *r = pv_at(*vp, i);
        if (r != NULL && r->kind == PV_VIDEO) return;
    }
    if (dom_get_by_tag(cs->idx, "video", NULL, 0) == 0) return;
    size_t nvids = dom_get_by_tag(cs->idx, "video", NULL, 0);
    dom_node_id *vids = (dom_node_id *)calloc(nvids, sizeof(dom_node_id));
    if (vids == NULL) return;
    size_t filled = dom_get_by_tag(cs->idx, "video", vids, nvids);
    for (size_t i = 0; i < filled; i++) {
        size_t sl = 0;
        const char *src = dom_get_attribute(cs->idx, vids[i], "src", &sl);
        if (src != NULL && sl > 0) {
            pv_append_video(*vp, 0, 1, NULL, src, NULL, -1, -1);
            break;
        }
    }
    free(vids);
}

/* Fetches the page's <link rel=stylesheet> sheets through the trusted parent
 * (TAG_SUBREQ; the confined worker never touches a socket) and accumulates the
 * accepted bodies into cs->extern_css, newline-separated, in document order.
 * Every failure is fail-open for the PAGE (the sheet is skipped with a Freebug
 * warn and the load continues) and fail-closed for the SHEET (status non-2xx,
 * non-CSS Content-Type or over-budget bodies are never parsed). Caller opens the
 * net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs) {
    size_t nhrefs = 0;
    char **hrefs = hp_extract_stylesheet_hrefs(cs->doc, &nhrefs);
    for (size_t i = 0; i < nhrefs; i++) {
        int st = 0;
        char *body = NULL, *ctype = NULL;
        size_t blen = 0;
        int fr = child_fetch(cs, "GET", hrefs[i], NULL, 0, &st, &body, &blen, &ctype);
        if (fr != 0 || st < 200 || st >= 300 || !ctype_is_css(ctype)) {
            char why[96];
            int why_r;
            if (fr != 0)
                why_r = snprintf(why, sizeof why, "blocked or failed");
            else
                why_r = snprintf(why, sizeof why, "refused (status %d, type %s)",
                                 st, (ctype != NULL && ctype[0] != '\0') ? ctype : "none");
            if (why_r < 0 || (size_t)why_r >= sizeof why) why[sizeof why - 1] = '\0';
            log_external_skip(&cs->log, "stylesheet", why, hrefs[i]);
            free(body);
            free(ctype);
            continue;
        }
        free(ctype);
        if (blen == 0 || blen > TAB_MAX_EXTERN_CSS
            || cs->extern_css_len > TAB_MAX_EXTERN_CSS - blen - 1) {
            if (blen != 0)
                log_external_skip(&cs->log, "stylesheet", "dropped (over budget)", hrefs[i]);
            free(body);
            continue;
        }
        char *grown = (char *)realloc(cs->extern_css, cs->extern_css_len + blen + 2);
        if (grown == NULL) { free(body); continue; }
        cs->extern_css = grown;
        memcpy(cs->extern_css + cs->extern_css_len, body, blen);
        cs->extern_css_len += blen;
        cs->extern_css[cs->extern_css_len++] = '\n';
        cs->extern_css[cs->extern_css_len] = '\0';
        free(body);
    }
    hp_free_stylesheet_hrefs(hrefs, nhrefs);
}

static int32_t child_next_timer_ms(child_state *cs);

static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
                              int run_js, int net, int reader, int prefers_dark,
                              int css, const char *page_url, const char *cookies) {
    cs->last_run_js = run_js;
    cs->last_reader = reader;
    cs->last_prefers_dark = prefers_dark;

    char  *title = NULL, *text = NULL;
    size_t tl = 0, xl = 0;
    pv_view *view = NULL;
    char navbuf[LN_MAX_TARGET];
    navbuf[0] = '\0';
    int32_t nav_replace = 0;
    int ok = (child_load(cs, html, len, run_js, net, page_url) == 0);
    /* Enable + seed document.cookie ONLY for a trusted host (net => allow.conf AND
     * js.conf). Untrusted stays a no-op jar (Zero Knowledge). The cookie bytes are a
     * JS string value, never interpolated into source. */
    if (ok && net && cookies != NULL && cookies[0] != '\0')
        (void)jd_set_cookies(cs->js, cookies);
    if (ok && css) {
        /* External stylesheets (Hito 27) come before the scripts, as a browser
         * fetches them. Independent of run_js: author CSS needs no JS. The parent
         * gates each frame on ITS OWN css grant (GET only), so this window adds
         * nothing a compromised worker could not already request. */
        cs->net_active = 1;
        child_fetch_stylesheets(cs);
        cs->net_active = 0;
    }
    /* Extract inline scripts BEFORE the preserve_view snapshot, so the native
     * video data scanner can read their text and create <iframe> elements in the
     * Lexbor tree while it is still uncorrupted by jQuery's DOM support tests.
     * The iframes are captured by the preserve_view snapshot, survive the jQuery
     * corruption fallback, and are later fetched by jd_process_iframes(). */
    size_t nscripts = 0;
    hp_script *scripts = NULL;
    if (ok) {
        scripts = hp_extract_script_list(cs->doc, &nscripts);
        /* Native (non-JS) extraction of video data from inline scripts: scan for
         * `video[N]='<iframe src=...>'` or `video_data='<iframe src=...>'` and
         * create <iframe> elements in the DOM. This runs BEFORE JS execution, so
         * the iframes are already in the Lexbor tree when the preserve_view
         * snapshot is taken. The JS shim (jd_inject_video_shim) remains as a
         * fallback for pages whose video data is populated by executed scripts. */
        if (nscripts > 0 && cs->idx != NULL) {
            const char **texts = (const char **)calloc(nscripts, sizeof(char *));
            size_t *lens = (size_t *)calloc(nscripts, sizeof(size_t));
            if (texts != NULL && lens != NULL) {
                for (size_t i = 0; i < nscripts; i++) {
                    texts[i] = scripts[i].text;
                    lens[i] = scripts[i].len;
                }
                (void)jd_video_from_scripts(cs->idx, texts, lens, nscripts, page_url);
            }
            free(texts);
            free(lens);
        }
    }
    /* Pre-script DOM snapshot: build the view BEFORE scripts run, for a
     * fallback when the post-script view is smaller (jQuery's DOM support
     * tests can corrupt Lexbor's sibling pointers). The snapshot wins when
     * it has more blocks -- and now includes the <iframe> elements created
     * by the native video extractor above, so video blocks survive the
     * fallback. */
    pv_view *preserve_view = NULL;
    if (ok) {
        (void)pv_build_styled(cs->doc, 0, reader, prefers_dark,
                              cs->extern_css, cs->extern_css_len,
                              &preserve_view);
    }
    if (ok && run_js) {
        /* Open the network window: XHR/fetch (if installed) may now reach the parent.
         * Closed again before deriving the view so a later REPL eval cannot use it. */
        cs->net_active = 1;
        /* Execute the page's inline scripts in the sandboxed context, THEN derive
         * the view, so DOM mutations (document.title / textContent) are reflected.
         * Each <script> is run as its own program, exactly as a browser does: an
         * uncaught error in one is surfaced to the Freebug console but does NOT abort
         * the others (concatenating them would let the first failure kill them all --
         * the root cause of "loads nothing" on script-heavy pages). A single page-wide
         * wall-clock budget is shared across every script and the synthetic load/timer
         * pump, so isolating scripts never multiplies the cap. The DOM bridge is
         * read-mostly (safe mutators), so a script cannot corrupt the tree. */
        /* scripts/nscripts extracted above; reuse the same arrays */
        /* Trusted hosts (allow.conf AND js.conf) get a larger JS budget: they
         * load heavier libraries (jQuery, Bootstrap, etc.) that need more time.
         * Untrusted hosts get the default budget (1s) to limit abuse. */
        uint64_t total_budget = net ? 5000 : JS_DEFAULT_TIME_BUDGET;
        struct timespec t0;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        for (size_t i = 0; i < nscripts; i++) {
            uint64_t rem = budget_remaining_ms(&t0, total_budget);
            if (rem == 0) break; /* page JS budget spent; stop running scripts */
            js_set_time_budget(cs->js, rem);
            const char *code = scripts[i].text;
            size_t code_len  = scripts[i].len;
            char  *ext_body  = NULL;
            /* Name each script so an uncaught error in it reports a meaningful
             * "file": inline ones by document position, external ones by src. */
            char sname[192];
            if (scripts[i].src != NULL) {
                /* External <script src> (Hito 24 EXT): runs ONLY for a doubly-trusted
                 * host (allow.conf AND js.conf => net). The confined worker has no
                 * socket; the bytes come from the TRUSTED parent via the same
                 * TAG_SUBREQ channel as XHR, under the full network policy. Every
                 * failure below is fail-closed: the script simply does not run and
                 * the load continues. */
                if (!net) {
                    log_external_skip(&cs->log, "script",
                        "skipped (host not granted network)", scripts[i].src);
                    continue;
                }
                int st = 0;
                size_t blen = 0;
                char *ctype = NULL;
                int fr = child_fetch(cs, "GET", scripts[i].src, NULL, 0,
                                     &st, &ext_body, &blen, &ctype);
                if (fr != 0 || st < 200 || st >= 300 || !ctype_is_javascript(ctype)) {
                    char why[96];
                    int why_r;
                    if (fr != 0)
                        why_r = snprintf(why, sizeof why, "blocked or failed");
                    else
                        why_r = snprintf(why, sizeof why, "refused (status %d, type %s)",
                                         st, (ctype != NULL && ctype[0] != '\0') ? ctype : "none");
                    if (why_r < 0 || (size_t)why_r >= sizeof why) why[sizeof why - 1] = '\0';
                    log_external_skip(&cs->log, "script", why, scripts[i].src);
                    free(ext_body);
                    free(ctype);
                    continue;
                }
                free(ctype);
                code = ext_body;
                code_len = blen;
                int sn_r = snprintf(sname, sizeof sname, "%s", scripts[i].src);
                if (sn_r < 0 || (size_t)sn_r >= sizeof sname) sname[sizeof sname - 1] = '\0';
            } else {
                int sn_r = snprintf(sname, sizeof sname, "inline #%zu", i + 1);
                if (sn_r < 0 || (size_t)sn_r >= sizeof sname) sname[sizeof sname - 1] = '\0';
            }
            js_set_current_script(cs->js,
                scripts[i].src, scripts[i].type);
            js_result r;
            memset(&r, 0, sizeof r);
            js_status es = js_eval_named(cs->js, code, code_len, sname, &r);
            if (es != JS_OK && r.is_exception && r.value != NULL)
                fb_buffer_push_loc(&cs->log, FB_ERROR, r.value, r.value_len,
                                   r.file, r.line, r.col);
            js_result_free(&r);
            js_set_current_script(cs->js, NULL, NULL);
            free(ext_body);
            /* Drain promise microtasks queued by this script (e.g. fetch().then),
             * so continuations run before the next script / view derivation. */
            (void)js_pump_jobs(cs->js, TAB_MAX_JS_JOBS);
        }
        hp_free_scripts(scripts, nscripts);
        /* Fire synthetic DOMContentLoaded/load handlers + flush queued timers once
         * (bounded; not a real event loop), so onload-wrapped code runs -- under the
         * same remaining page budget. */
        uint64_t rem = budget_remaining_ms(&t0, total_budget);
        if (rem > 0) {
            js_set_time_budget(cs->js, rem);
            static const char fire[] = "if(typeof __fireDeferred==='function')__fireDeferred();";
            js_result fr;
            memset(&fr, 0, sizeof fr);
            (void)js_eval(cs->js, fire, sizeof fire - 1, &fr);
            js_result_free(&fr);
            (void)js_pump_jobs(cs->js, TAB_MAX_JS_JOBS); /* drain deferred promise jobs */
        }
        /* Inject the video shim if the page defines `video[]` / `video_data`
         * (e.g. jkanime.net whose video_min.js is 404). It creates <iframe>
         * elements from the array, which the next step fetches and scans. */
        if (cs->js != NULL)
            jd_inject_video_shim(cs->js);
        /* Process any <iframe src=...> elements created by the page's scripts
         * (including via innerHTML= or the video shim above). Fetch the iframe
         * content (same-origin fetches through the trusted parent), scan for
         * video URLs (.m3u8), and create <video> elements in the DOM for any
         * found. */
        if (cs->idx != NULL)
            jd_process_iframes(cs->js, cs->idx, child_fetch, cs);
        /* Close the network window: no XHR/fetch outside the load script phase. */
        cs->net_active = 0;
        /* Restore the full per-eval budget for any REPL (tab_eval) on this context. */
        js_set_time_budget(cs->js, JS_DEFAULT_TIME_BUDGET);
        /* Capture any navigation the script requested (location.href=/assign/replace/
         * reload). Raw and unresolved: the parent gates it (Zero Trust). */
        int rep = 0;
        (void)jd_take_nav_request(cs->js, navbuf, sizeof navbuf, &rep);
        nav_replace = rep ? 1 : 0;
    } else if (scripts != NULL) {
        /* Scripts were extracted for native video extraction but not executed
         * (run_js == 0). Free them explicitly since hp_free_scripts is inside
         * the run_js branch above. */
        hp_free_scripts(scripts, nscripts);
    }
    if (ok) {
        title = hp_get_title(cs->doc, &tl);
        text  = hp_extract_text(cs->doc, &xl);
        if (title == NULL || text == NULL
            || pv_build_styled(cs->doc, run_js, reader, prefers_dark,
                               cs->extern_css, cs->extern_css_len, &view) != PV_OK) {
            ok = 0;
            child_reset_page(cs);
        } else {
            /* Preserve pre-script DOM: keep the snapshot for the initial load
             * AND for mutation fallback (jQuery's support tests corrupt the tree).
             * Ownership goes to cs->preserved_view; the initial write below uses
             * whichever view is fuller without transferring ownership. */
            if (preserve_view != NULL) {
                pv_free(cs->preserved_view);
                cs->preserved_view = preserve_view;
                preserve_view = NULL;
            }
        }
    }
    /* Decide which view to write. The preserved view (pre-script snapshot)
     * carries all page text; when jQuery corrupts Lexbor, the post-script
     * view has fewer blocks. We inject video into both views so whichever
     * wins carries the .m3u8 block. The duplicate guard in inject_video_into_view
     * ensures the preserved view gets the video only once (initial load). */
    inject_video_into_view(cs, &view);
    inject_video_into_view(cs, &cs->preserved_view);

    pv_view *write_which = view;
    if (ok && view != NULL && cs->preserved_view != NULL
        && pv_count(cs->preserved_view) > pv_count(view)) {
        write_which = cs->preserved_view;
    }

    /* Dump the page's cookie jar so the parent can fold JS-set session cookies back
     * into its network jar (empty when the jar was disabled -- untrusted host). */
    char ckdump[4096];
    size_t cklen = (size_t)jd_get_cookies(cs->js, ckdump, sizeof ckdump);

    /* TAG_RESULT marks the end of any subresource frames: the page result follows. */
    uint8_t rtag = TAG_RESULT;
    int32_t k = ok ? 1 : 0;
    int32_t next_ms = child_next_timer_ms(cs);
    if (write_full(wfd, &rtag, 1) == 0 && write_full(wfd, &k, sizeof k) == 0 && ok) {
        size_t nlen = strlen(navbuf);
        (void)(write_full(wfd, &tl, sizeof tl) == 0
            && (tl == 0 || write_full(wfd, title, tl) == 0)
            && write_full(wfd, &xl, sizeof xl) == 0
            && (xl == 0 || write_full(wfd, text, xl) == 0)
            && write_view(wfd, write_which) == 0
            && write_full(wfd, &nlen, sizeof nlen) == 0
            && (nlen == 0 || write_full(wfd, navbuf, nlen) == 0)
            && write_full(wfd, &nav_replace, sizeof nav_replace) == 0
            && write_console(wfd, &cs->log) == 0
            && write_full(wfd, &next_ms, sizeof next_ms) == 0
            && write_full(wfd, &cklen, sizeof cklen) == 0
            && (cklen == 0 || write_full(wfd, ckdump, cklen) == 0));
    }
    hp_free(title);
    hp_free(text);
    pv_free(view);
}

/* Smallest pending JS timer delay (__nextTimerMs), or -1 when JS is absent, the
 * eval fails, or nothing is pending. Does NOT touch the console transcript. */
static int32_t child_next_timer_ms(child_state *cs) {
    if (cs->js == NULL) return -1;
    static const char q[] = "typeof __nextTimerMs==='function'?__nextTimerMs():-1";
    js_result r;
    if (js_eval(cs->js, q, sizeof q - 1, &r) != JS_OK) return -1;
    int32_t ms = (r.value != NULL) ? (int32_t)atoi(r.value) : -1;
    js_result_free(&r);
    return (ms >= 0) ? ms : -1;
}

/* Fire click handlers for node_id (OP_CLICK) or advance the virtual timer clock
 * (OP_TICK), then re-derive the view so the parent can repaint mutations caused
 * by the handlers. Response format matches the tail of OP_LOAD: [ok:int32]
 * [title_len][title][text_len][text][view][nav_len=''][nav_replace][console]
 * [next_timer_ms:int32]. Neither produces a navigation. */
static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                                  dom_node_id node_id, int32_t elapsed_ms) {
    char  *title = NULL, *text = NULL;
    size_t tl = 0, xl = 0;
    pv_view *view = NULL;
    int ok = 0;
    if (cs->js != NULL && cs->doc != NULL && cs->idx != NULL) {
        if (is_tick) {
            char tick[64];
            int n = snprintf(tick, sizeof tick, "__tickTimers(%d)",
                             (int)(elapsed_ms >= 0 ? elapsed_ms : 0));
            js_result r;
            memset(&r, 0, sizeof r);
            if (n > 0 && (size_t)n < sizeof tick
                && js_eval(cs->js, tick, (size_t)n, &r) == JS_OK) {
                if (r.is_exception && r.value != NULL)
                    fb_buffer_push_loc(&cs->log, FB_ERROR, r.value, r.value_len,
                                       r.file, r.line, r.col);
                js_result_free(&r);
                (void)js_pump_jobs(cs->js, TAB_MAX_JS_JOBS);
            }
        } else {
            (void)jd_fire_click(cs->js, node_id);
        }
        title = hp_get_title(cs->doc, &tl);
        text  = hp_extract_text(cs->doc, &xl);
        if (title != NULL && text != NULL
            && pv_build_styled(cs->doc, cs->last_run_js, cs->last_reader,
                               cs->last_prefers_dark, cs->extern_css,
                               cs->extern_css_len, &view) == PV_OK) {
            ok = 1;
        }
    }

    inject_video_into_view(cs, &view);

    uint8_t rtag = TAG_RESULT;
    int32_t k = ok ? 1 : 0;
    /* Mutation may corrupt the DOM (jQuery's support tests break Lexbor siblings).
     * Fall back to the preserved pre-script view when the rebuilt view is smaller.
     * The preserved view already carries the video injected during initial load. */
    pv_view *write_which = view;
    if (ok && view != NULL && cs->preserved_view != NULL
        && pv_count(cs->preserved_view) > pv_count(view)) {
        write_which = cs->preserved_view;
    }
    int32_t zero32 = 0;
    size_t zero = 0;
    int32_t next_ms = child_next_timer_ms(cs);
    if (write_full(wfd, &rtag, 1) == 0 && write_full(wfd, &k, sizeof k) == 0 && ok) {
        (void)(write_full(wfd, &tl, sizeof tl) == 0
            && (tl == 0 || write_full(wfd, title, tl) == 0)
            && write_full(wfd, &xl, sizeof xl) == 0
            && (xl == 0 || write_full(wfd, text, xl) == 0)
            && write_view(wfd, write_which) == 0
            && write_full(wfd, &zero, sizeof zero) == 0
            && write_full(wfd, &zero32, sizeof zero32) == 0 /* nav_replace = 0 */
            && write_console(wfd, &cs->log) == 0
            && write_full(wfd, &next_ms, sizeof next_ms) == 0);
    }
    hp_free(title);
    hp_free(text);
    pv_free(view);
}

static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id) {
    child_handle_mutation(wfd, cs, 0, node_id, 0);
}

static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms) {
    child_handle_mutation(wfd, cs, 1, DOM_NODE_NONE, elapsed_ms);
}

/* Handles a generic DOM event (OP_EVENT). Reads: node_id:int32, event_type_len:size_t,
 * event_type, key_len:size_t, key, key_code:int32, value_len:size_t, value.
 * Fires JS handlers via jd_fire_event, re-derives the view. */
/* read_field reads a size-prefixed field from fd; defined below. */
static int read_field(int fd, char **out, size_t *out_len);

static void child_handle_event(int wfd, child_state *cs) {
    if (cs->js == NULL || cs->idx == NULL || cs->doc == NULL) {
        child_handle_mutation(wfd, cs, 0, DOM_NODE_NONE, 0);
        return;
    }
    int32_t nid;
    if (read_full(cs->rfd, &nid, sizeof nid) != 0) {
        child_handle_mutation(wfd, cs, 0, DOM_NODE_NONE, 0);
        return;
    }
    size_t tlen = 0;
    char *etype = NULL;
    if (read_field(cs->rfd, &etype, &tlen) != 0) {
        free(etype);
        child_handle_mutation(wfd, cs, 0, DOM_NODE_NONE, 0);
        return;
    }
    size_t klen = 0;
    char *key = NULL;
    if (read_field(cs->rfd, &key, &klen) != 0) {
        free(etype); free(key);
        child_handle_mutation(wfd, cs, 0, DOM_NODE_NONE, 0);
        return;
    }
    int32_t key_code = 0;
    if (read_full(cs->rfd, &key_code, sizeof key_code) != 0) {
        free(etype); free(key);
        child_handle_mutation(wfd, cs, 0, DOM_NODE_NONE, 0);
        return;
    }
    size_t vlen = 0;
    char *value = NULL;
    if (read_field(cs->rfd, &value, &vlen) != 0) {
        free(etype); free(key); free(value);
        child_handle_mutation(wfd, cs, 0, DOM_NODE_NONE, 0);
        return;
    }

    (void)jd_fire_event(cs->js, (dom_node_id)nid, etype, key, (int)key_code, value);
    free(etype); free(key); free(value);

    /* Re-derive the view (same as mutation path). */
    child_handle_mutation(wfd, cs, 0, (dom_node_id)nid, 0);
}

/* Handles a mouse DOM event (OP_MOUSE). Reads: node_id:int32,
 * event_type_len:size_t, event_type, client_x:int32, client_y:int32,
 * button:int32. Fires JS handlers via jd_fire_mouse_event, re-derives the view. */
static void child_handle_mouse(int wfd, child_state *cs) {
    if (cs->js == NULL || cs->idx == NULL || cs->doc == NULL) {
        child_handle_mutation(wfd, cs, 0, DOM_NODE_NONE, 0);
        return;
    }
    int32_t nid;
    if (read_full(cs->rfd, &nid, sizeof nid) != 0) {
        child_handle_mutation(wfd, cs, 0, DOM_NODE_NONE, 0);
        return;
    }
    size_t tlen = 0;
    char *etype = NULL;
    if (read_field(cs->rfd, &etype, &tlen) != 0) {
        free(etype);
        child_handle_mutation(wfd, cs, 0, DOM_NODE_NONE, 0);
        return;
    }
    int32_t cx = 0, cy = 0, btn = -1;
    if (read_full(cs->rfd, &cx, sizeof cx) != 0
     || read_full(cs->rfd, &cy, sizeof cy) != 0
     || read_full(cs->rfd, &btn, sizeof btn) != 0) {
        free(etype);
        child_handle_mutation(wfd, cs, 0, DOM_NODE_NONE, 0);
        return;
    }
    (void)jd_fire_mouse_event(cs->js, (dom_node_id)nid, etype, (int)cx, (int)cy, (int)btn);
    free(etype);
    child_handle_mutation(wfd, cs, 0, (dom_node_id)nid, 0);
}

/* Fires a submit event on the form enclosing node_id. Walks up the DOM to find
 * the <form> element, dispatches the event, and reports whether preventDefault
 * was called. Response: [TAG_RESULT][ok:int32][prevented:int32]. No view
 * re-derivation — the submission is the default action, not a repaint. */
static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id) {
    int prevented = 1; /* fail-closed: if anything goes wrong, submission proceeds */
    int ok = 0;
    if (cs->js != NULL && cs->idx != NULL && node_id != DOM_NODE_NONE) {
        /* Walk up the DOM to find the form. */
        dom_node_id form_id = DOM_NODE_NONE;
        dom_node_id cur = node_id;
        while (cur != DOM_NODE_NONE) {
            size_t tlen = 0;
            const char *tag = dom_tag_name(cs->idx, cur, &tlen);
            if (tag != NULL && tlen == 4
                && tag[0] == 'F' && tag[1] == 'O' && tag[2] == 'R' && tag[3] == 'M') {
                form_id = cur;
                break;
            }
            cur = dom_parent(cs->idx, cur);
        }
        if (form_id != DOM_NODE_NONE) {
            prevented = jd_fire_submit(cs->js, form_id);
            ok = 1;
        }
    }

    uint8_t rtag = TAG_RESULT;
    int32_t k = ok ? 1 : 0;
    int32_t p = prevented ? 1 : 0;
    (void)(write_full(wfd, &rtag, 1) == 0
        && write_full(wfd, &k, sizeof k) == 0
        && write_full(wfd, &p, sizeof p) == 0);
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
    if (s != JS_OK && r.is_exception && r.value != NULL)
        fb_buffer_push_loc(&cs->log, FB_ERROR, r.value, r.value_len,
                           r.file, r.line, r.col);
    (void)js_pump_jobs(cs->js, TAB_MAX_JS_JOBS);
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
    cs.rfd = rfd; cs.wfd = wfd;  /* child_fetch proxies subresource requests over these */

    /* Normalize the timezone to UTC before confinement, for two independent
     * reasons. Anti-fingerprinting (Zero Knowledge): the host timezone is a
     * fingerprinting vector, and QuickJS's Date reads it via localtime_r -- every
     * page's JS must see the same UTC clock. Sandbox correctness: with TZ unset,
     * glibc's first localtime_r lazily openat()s /etc/localtime, and openat is
     * (rightly) not on the seccomp allowlist -- page JS calling
     * Date.getTimezoneOffset() got the worker SIGSYS-killed. "UTC0" is a pure
     * POSIX TZ spec glibc parses without touching the filesystem; the eager
     * tzset() caches it while syscalls are still unrestricted. */
    setenv("TZ", "UTC0", 1);
    tzset();

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
        if (op != OP_LOAD && op != OP_EVAL && op != OP_DECODE_IMAGE &&
            op != OP_CLICK && op != OP_TICK && op != OP_SUBMIT &&
            op != OP_EVENT && op != OP_MOUSE)
            break; /* desync */

        /* OP_CLICK is a short command: just the target node id. */
        if (op == OP_CLICK) {
            int32_t nid = (int32_t)DOM_NODE_NONE;
            if (read_full(rfd, &nid, sizeof nid) != 0) break;
            child_handle_click(wfd, &cs, (dom_node_id)nid);
            continue;
        }

        /* OP_TICK is a short command: the elapsed virtual ms to advance. */
        if (op == OP_TICK) {
            int32_t elapsed = 0;
            if (read_full(rfd, &elapsed, sizeof elapsed) != 0) break;
            child_handle_tick(wfd, &cs, elapsed);
            continue;
        }

        /* OP_SUBMIT is a short command: the element's node_id. */
        if (op == OP_SUBMIT) {
            int32_t nid = (int32_t)DOM_NODE_NONE;
            if (read_full(rfd, &nid, sizeof nid) != 0) break;
            child_handle_submit(wfd, &cs, (dom_node_id)nid);
            continue;
        }

        /* OP_EVENT dispatches a generic DOM event. Reads: node_id, event_type (size+str),
         * key (size+str), key_code, value (size+str). */
        if (op == OP_EVENT) {
            child_handle_event(wfd, &cs);
            continue;
        }

        /* OP_MOUSE dispatches a mouse DOM event. Reads: node_id, event_type (size+str),
         * client_x:int32, client_y:int32, button:int32. */
        if (op == OP_MOUSE) {
            child_handle_mouse(wfd, &cs);
            continue;
        }

        /* OP_LOAD carries five leading flag bytes: run_js (JS policy), net (XHR/fetch
         * allowed: host in allow.conf AND js.conf), reader (distraction-free), dark
         * (prefers-color-scheme) and css (external stylesheet fetch, Hito 27), then
         * the page URL (for the real location), before length+payload. */
        uint8_t run_js = 0, net = 0, reader = 0, dark = 0, css = 0;
        char *url = NULL, *cookies = NULL;
        if (op == OP_LOAD) {
            if (read_full(rfd, &run_js, 1) != 0
             || read_full(rfd, &net, 1) != 0
             || read_full(rfd, &reader, 1) != 0
             || read_full(rfd, &dark, 1) != 0
             || read_full(rfd, &css, 1) != 0) break;
            size_t ulen = 0;
            if (read_full(rfd, &ulen, sizeof ulen) != 0) break;
            if (ulen > TAB_MAX_URL) break; /* defensive: URLs are small */
            if (ulen == (size_t)-1) break;
            url = (char *)malloc(ulen + 1);
            if (url == NULL) break;
            if (ulen != 0 && read_full(rfd, url, ulen) != 0) { free(url); break; }
            url[ulen] = '\0';
            size_t cklen = 0;
            if (read_full(rfd, &cklen, sizeof cklen) != 0) { free(url); break; }
            if (cklen > TAB_MAX_URL * 8) { free(url); break; } /* defensive cap */
            if (cklen == (size_t)-1) { free(url); break; }
            cookies = (char *)malloc(cklen + 1);
            if (cookies == NULL) { free(url); break; }
            if (cklen != 0 && read_full(rfd, cookies, cklen) != 0) { free(cookies); free(url); break; }
            cookies[cklen] = '\0';
        }

        size_t len = 0;
        if (read_full(rfd, &len, sizeof len) != 0) { free(url); break; }
        if (len > TAB_MAX_INPUT) { free(url); break; } /* parent enforces; defensive */
        if (len == (size_t)-1) { free(url); break; }

        char *buf = (char *)malloc(len + 1);
        if (buf == NULL) { free(url); break; }
        if (len != 0 && read_full(rfd, buf, len) != 0) { free(buf); free(url); break; }
        buf[len] = '\0';

        if (op == OP_LOAD)              child_handle_load(wfd, &cs, buf, len, run_js, net, reader, dark, css, url, cookies);
        else if (op == OP_EVAL)         child_handle_eval(wfd, &cs, buf, len);
        else /* OP_DECODE_IMAGE */      child_handle_decode_image(wfd, buf, len);
        free(buf);
        free(url);
        free(cookies);
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
    /* Subresource (XHR/fetch) support: net_allowed gates whether the worker may issue
     * subresource requests this load (set per page: host in allow.conf AND js.conf);
     * css_allowed grants GET-only stylesheet fetches (Hito 27, the author-styles
     * opt-in); fetcher does the policy-checked fetch in the trusted parent. */
    int            net_allowed;
    int            css_allowed;
    char          *cookies_in;   /* seeds document.cookie for the next load (owned) */
    tab_fetch_fn   fetcher;
    void          *fetcher_ctx;
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
    if (r == t->pid) {
        if (getenv("FREEDOM_DEBUG_WORKER") != NULL) {
            if (WIFSIGNALED(st))
                fprintf(stderr, "[worker] killed by signal %d\n", WTERMSIG(st));
            else if (WIFEXITED(st))
                fprintf(stderr, "[worker] exited %d\n", WEXITSTATUS(st));
        }
        t->alive = 0; t->reaped = 1;
    }
    else if (r < 0 && errno == ECHILD) { t->alive = 0; t->reaped = 1; }
    /* r == 0: still running, liveness unchanged. */
}

/* Read one length-prefixed owned field from the child, capped against
 * amplification. *out is NUL-terminated. */
static int read_field(int fd, char **out, size_t *out_len) {
    size_t n = 0;
    if (read_full(fd, &n, sizeof n) != 0) return -1;
    if (n > TAB_MAX_INPUT) return -1;
    if (n == (size_t)-1) return -1;
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
        int32_t head[6];
        if (read_full(fd, head, sizeof head) != 0) { pv_free(v); return -1; }
        int32_t kind = head[0], heading = head[1], bold = head[2],
                italic = head[3], indent = head[4], brk = head[5];
        char *text = NULL, *href = NULL, *src = NULL, *poster = NULL, *name = NULL, *value = NULL;
        size_t tl = 0, hl = 0, sl = 0, pl = 0, nl = 0, vl = 0;
        if (read_field(fd, &text, &tl) != 0) { pv_free(v); return -1; }
        if (read_field(fd, &href, &hl) != 0) { free(text); pv_free(v); return -1; }
        if (read_field(fd, &src, &sl) != 0) { free(text); free(href); pv_free(v); return -1; }
        if (read_field(fd, &poster, &pl) != 0) { free(text); free(href); free(src); pv_free(v); return -1; }

        /* Block A + grid array + block B: contiguous fixed-width scalars, same order
         * write_view emits them. Reading each block in one shot (not field by field)
         * makes a wire desync structurally hard -- the arrays list the fields once,
         * exactly like the box-def f[] array below. */
        int32_t a[36], gtw[PV_GRID_TRACKS + 1], b[26];
        if (read_full(fd, a, sizeof a) != 0
         || read_full(fd, gtw, sizeof gtw) != 0
         || read_full(fd, b, sizeof b) != 0) {
            free(text); free(href); free(src); free(poster); pv_free(v); return -1;
        }
        int32_t img_w = a[0], img_h = a[1], fg = a[2], bg = a[3], talign = a[4],
                fscale = a[5], lscale = a[6], deco = a[7], ffam = a[8], ttrans = a[9],
                lspc = a[10], wspc = a[11], shdx = a[12], shdy = a[13], shcol = a[14],
                opac = a[15], valgn = a[16], tindent = a[17], wspace = a[18],
                toverflow = a[19], wbreak = a[20], tdeco_color = a[21], tdeco_style = a[22],
                tdeco_thick = a[23], ttsize = a[24], tdir = a[25], tfvar = a[26],
                tlpos = a[27], tirend = a[28], tcaret = a[29], tobject_fit = a[30],
                cid = a[31], cdisp = a[32], cgap = a[33], cjust = a[34], ccols = a[35];
        int32_t fgrow = b[0], fshrink = b[1], fbasis = b[2], forder = b[3], fdir = b[4],
                citem = b[5], cwrap = b[6], crgap = b[7], calign = b[8], fself = b[9],
                flside = b[10], flid = b[11], flclear = b[12], bl = b[13], br = b[14],
                bw = b[15], bcenter = b[16], bmt = b[17], bmb = b[18], bwpct = b[19],
                blkid = b[20], nodeid = b[21], itype = b[22], fid = b[23], method = b[24],
                ckd = b[25];
        char *opts = NULL;
        size_t ol = 0;
        if (read_field(fd, &opts, &ol) != 0) {
            free(text); free(href); free(src); free(poster); pv_free(v); return -1;
        }
        if (read_field(fd, &name, &nl) != 0) { free(text); free(href); free(src); free(poster); free(opts); pv_free(v); return -1; }
        if (read_field(fd, &value, &vl) != 0) {
            free(text); free(href); free(src); free(poster); free(name); free(opts); pv_free(v); return -1;
        }

        pv_status st;
        if (kind == PV_INPUT) {
            st = pv_append_input(v, heading, brk, (pv_input_type)itype, text,
                                 (nl > 0) ? name : NULL, (vl > 0) ? value : NULL,
                                 (hl > 0) ? href : NULL, (int)fid, (int)method);
        } else if (kind == PV_IMAGE && sl > 0) {
            st = pv_append_image(v, heading, brk, text, src, img_w, img_h);
        } else if (kind == PV_VIDEO && sl > 0) {
            st = pv_append_video(v, heading, brk, text, src,
                                 (pl > 0) ? poster : NULL, img_w, img_h);
        } else {
            pv_kind k = (kind == PV_LINK && hl > 0) ? PV_LINK : PV_TEXT;
            st = pv_append(v, k, heading, brk, text, (hl > 0) ? href : NULL);
        }
        free(text);
        free(href);
        free(src);
        free(poster);
        free(name);
        free(value);
        if (st != PV_OK) { free(opts); pv_free(v); return -1; }
        /* Input-specific: checked and select options from the wire. */
        if (kind == PV_INPUT) {
            pv_set_input_checked(v, (int)ckd);
            if (ol > 0 && opts != NULL)
                pv_set_input_select_opts(v, opts);
        }
        free(opts);
        /* The text extensions ride every run kind (an input's caret_color and an
         * image's image_rendering would vanish inside the old non-input branch). */
        {
            pv_text_ext e;
            pv_text_ext_reset(&e);
            e.font_family = (int)ffam; e.text_transform = (int)ttrans;
            e.letter_spacing = (int)lspc; e.word_spacing = (int)wspc;
            e.shadow_dx = (int)shdx; e.shadow_dy = (int)shdy; e.shadow_color = (int)shcol;
            e.opacity = (int)opac; e.valign = (int)valgn; e.text_indent = (int)tindent;
            e.white_space = (int)wspace;
            e.text_overflow = (int)toverflow; e.word_break = (int)wbreak;
            e.text_decoration_color = (int)tdeco_color;
            e.text_decoration_style = (int)tdeco_style;
            e.text_decoration_thickness = (int)tdeco_thick;
            e.tab_size = (int)ttsize; e.direction = (int)tdir;
            e.font_variant = (int)tfvar; e.list_style_pos = (int)tlpos;
            e.image_rendering = (int)tirend; e.caret_color = (int)tcaret;
            e.object_fit = (int)tobject_fit;
            pv_set_text_ext(v, &e);
        }
        if (kind != PV_INPUT) {
            pv_set_emphasis(v, (int)bold, (int)italic);
            pv_set_indent(v, (int)indent);
            pv_set_color(v, (int)fg);
            pv_set_bgcolor(v, (int)bg);
            pv_set_text_style(v, (int)talign, (int)fscale, (int)lscale, (int)deco);
            pv_set_container(v, (int)cid, (int)cdisp, (int)cgap, (int)cjust, (int)ccols,
                             (int)cwrap, (int)crgap, (int)calign);
            {
                int gw[PV_GRID_TRACKS];
                for (int gk = 0; gk < PV_GRID_TRACKS; ++gk) gw[gk] = (int)gtw[gk];
                pv_set_grid(v, gw, PV_GRID_TRACKS, (int)gtw[PV_GRID_TRACKS]);
            }
            pv_set_flex(v, (int)fgrow, (int)fshrink, (int)fbasis, (int)forder, (int)fdir,
                       (int)fself);
            pv_set_cont_item(v, (int)citem);
            pv_set_float(v, (int)flside, (int)flid, (int)flclear);
            pv_set_box(v, (int)bl, (int)br, (int)bw, (int)bcenter, (int)bmt, (int)bmb);
            pv_set_box_pct(v, (int)bwpct);
            pv_set_block_id(v, (int)blkid);
            pv_set_node_id(v, (dom_node_id)nodeid);
        }
    }

    /* Box engine (Step D): the box tree, same order/shape as write_view. Bounded by
     * TAB_MAX_RUNS against a hostile child inflating the count. 2026-07-10 batch
     * adds 4 author vertical-dim fields at the end (h/min_h/max_h/min_w). */
    size_t nb = 0;
    if (read_full(fd, &nb, sizeof nb) != 0) { pv_free(v); return -1; }
    if (nb > TAB_MAX_RUNS) { pv_free(v); return -1; }
    for (size_t bi = 0; bi < nb; ++bi) {
        int32_t f[58];
        if (read_full(fd, f, sizeof f) != 0) { pv_free(v); return -1; }
        pv_box_def bd = {
            .parent_id = f[0], .box_sizing = f[1],
            .pad_t = f[2], .pad_r = f[3], .pad_b = f[4], .pad_l = f[5],
            .bord_tw = f[6], .bord_rw = f[7], .bord_bw = f[8], .bord_lw = f[9],
            .bord_ts = f[10], .bord_rs = f[11], .bord_bs = f[12], .bord_ls = f[13],
            .bord_tc = f[14], .bord_rc = f[15], .bord_bc = f[16], .bord_lc = f[17],
            .border_radius = f[18],
            .bsh_dx = f[19], .bsh_dy = f[20], .bsh_blur = f[21], .bsh_spread = f[22],
            .bsh_color = f[23], .bsh_inset = f[24],
            .outline_w = f[25], .outline_style = f[26], .outline_color = f[27],
            .box_l = f[28], .box_r = f[29], .box_w = f[30], .box_center = f[31],
            .bg_rgb = f[32],
            .position = f[33],
            .inset_top = f[34], .inset_right = f[35],
            .inset_bottom = f[36], .inset_left = f[37],
            .z_index = f[38],
            .visibility = f[39],
            .overflow_x = f[40], .overflow_y = f[41],
            .cursor = f[42],
            .outline_offset = f[43],
            .aspect_num = f[44], .aspect_den = f[45],
            /* 2026-07-10 batch (4 appended fields). */
            .box_h = f[46], .box_min_h = f[47], .box_max_h = f[48], .box_min_w = f[49],
            /* 2026-07-10 wiring batch: pointer-events. */
            .pointer_events = f[50],
            /* Hito 32: symbolic per-mille width cap. */
            .box_w_pct = f[51],
            /* linear-gradient background (2026-07-11). */
            .grad_n = f[52], .grad_angle = f[53],
            .grad_c0 = f[54], .grad_c1 = f[55], .grad_c2 = f[56], .grad_c3 = f[57],
        };
        if (pv_add_box_def(v, &bd) != PV_OK) { pv_free(v); return -1; }
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
        if (flen == (size_t)-1) return -1;
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
    int rn = snprintf(rbuf, sizeof rbuf, "%d", rfd);
    int wn = snprintf(wbuf, sizeof wbuf, "%d", wfd);
    if (rn < 0 || (size_t)rn >= sizeof rbuf) rbuf[0] = '\0';
    if (wn < 0 || (size_t)wn >= sizeof wbuf) wbuf[0] = '\0';
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

void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx) {
    if (t == NULL) return;
    t->fetcher = fn;
    t->fetcher_ctx = ctx;
}

void tab_set_net_allowed(tab *t, int allowed) {
    if (t == NULL) return;
    t->net_allowed = allowed ? 1 : 0;
}

void tab_set_css_allowed(tab *t, int allowed) {
    if (t == NULL) return;
    t->css_allowed = allowed ? 1 : 0;
}

void tab_set_cookies(tab *t, const char *cookies) {
    if (t == NULL) return;
    free(t->cookies_in);
    t->cookies_in = (cookies != NULL && cookies[0] != '\0') ? strdup(cookies) : NULL;
}

int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method) {
    if (method == NULL || method[0] == '\0') return 0; /* malformed: fail closed */
    if (net_allowed) return 1;
    if (css_allowed && strcmp(method, "GET") == 0) return 1;
    return 0;
}

/* Handles one TAG_SUBREQ frame on the response pipe: reads the worker's subresource
 * request, gates it on the grants the PARENT decided for this load (Zero Trust: a
 * compromised worker forging frames gets a refusal, never a fetch -- net grants any
 * method, css-only grants exactly GET), then runs the policy-checked fetcher (or
 * refuses), and writes the reply [status:int32][body_len][body][ctype_len][ctype].
 * A refused frame is still consumed and answered (status 0), so the protocol never
 * desyncs. Returns 0 on success, -1 on a pipe/protocol error (caller aborts the
 * load). Bytes are capped (anti-amplification). */
static int tab_serve_subreq(tab *t, int net_granted, int css_granted) {
    size_t mlen = 0, ulen = 0, blen = 0;
    char *method = NULL, *url = NULL, *body = NULL;
    if (read_field(t->resp_fd, &method, &mlen) != 0) return -1;
    if (read_field(t->resp_fd, &url, &ulen) != 0) { free(method); return -1; }
    if (read_field(t->resp_fd, &body, &blen) != 0) { free(method); free(url); return -1; }

    int status = 0; char *rbody = NULL; size_t rlen = 0; char *rctype = NULL;
    int ok = 0;
    if (tab_subreq_permitted(net_granted, css_granted, method)
        && t->fetcher != NULL && ulen != 0
        && t->fetcher(t->fetcher_ctx, method, url, body, blen,
                      &status, &rbody, &rlen, &rctype) == 0) {
        ok = 1;
    }
    if (!ok) { status = 0; rlen = 0; }                 /* refused/failed: fail-closed */
    if (rlen > TAB_MAX_SUBRESOURCE) { rlen = 0; status = 0; } /* defensive cap */
    size_t clen = (ok && rctype != NULL) ? strlen(rctype) : 0;
    if (clen > 256) clen = 256;

    /* The reply goes back on req_fd (the worker reads it from its rfd, the same fd it
     * blocks on inside child_fetch). */
    int32_t st32 = (int32_t)status;
    int wok = (write_full(t->req_fd, &st32, sizeof st32) == 0
            && write_full(t->req_fd, &rlen, sizeof rlen) == 0
            && (rlen == 0 || write_full(t->req_fd, rbody, rlen) == 0)
            && write_full(t->req_fd, &clen, sizeof clen) == 0
            && (clen == 0 || write_full(t->req_fd, rctype, clen) == 0));

    free(method); free(url); free(body); free(rbody); free(rctype);
    return wok ? 0 : -1;
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

    /* OP_LOAD framing: [op][run_js:1][net:1][reader:1][dark:1][css:1][url_len][url]
     * [ck_len][cookies][len][html] (the flags, URL and cookie seed precede the payload
     * so the html stays zero-copy). net grants XHR/fetch and is only meaningful with JS
     * on; css grants GET-only external stylesheet fetches (Hito 27); cookies seed
     * document.cookie for a trusted host (empty otherwise). */
    uint8_t op = OP_LOAD, jflag = run_js ? 1 : 0,
            nflag = (run_js && t->net_allowed) ? 1 : 0,
            rflag = reader ? 1 : 0, dflag = prefers_dark ? 1 : 0,
            cflag = t->css_allowed ? 1 : 0;
    const char *ck = (nflag && t->cookies_in != NULL) ? t->cookies_in : "";
    size_t cklen = strlen(ck);
    if (write_full(t->req_fd, &op, 1) != 0
     || write_full(t->req_fd, &jflag, 1) != 0
     || write_full(t->req_fd, &nflag, 1) != 0
     || write_full(t->req_fd, &rflag, 1) != 0
     || write_full(t->req_fd, &dflag, 1) != 0
     || write_full(t->req_fd, &cflag, 1) != 0
     || write_full(t->req_fd, &ulen, sizeof ulen) != 0
     || (ulen != 0 && write_full(t->req_fd, page_url, ulen) != 0)
     || write_full(t->req_fd, &cklen, sizeof cklen) != 0
     || (cklen != 0 && write_full(t->req_fd, ck, cklen) != 0)
     || write_full(t->req_fd, &len, sizeof len) != 0
     || (len != 0 && write_full(t->req_fd, html, len) != 0)) {
        tab_refresh_alive(t);
        return t->alive ? TAB_ERR_IO : TAB_ERR_DEAD;
    }

    /* While the worker runs the page's scripts it may issue subresource (XHR/fetch)
     * requests, each a TAG_SUBREQ frame the trusted parent services in policy. Loop
     * until TAG_RESULT, which precedes the page result. */
    for (;;) {
        uint8_t tag = 0;
        if (read_full(t->resp_fd, &tag, 1) != 0) return io_failure(t);
        if (tag == TAG_RESULT) break;
        if (tag != TAG_SUBREQ) return io_failure(t);   /* desync */
        if (tab_serve_subreq(t, nflag, cflag) != 0) return io_failure(t);
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
    /* Smallest pending JS timer delay (2026-07-11). */
    int32_t next_ms = -1;
    if (read_full(t->resp_fd, &next_ms, sizeof next_ms) != 0) {
        free(title); free(text); free(navreq); pv_free(view);
        fb_buffer_free(&console);
        return io_failure(t);
    }
    /* The page's document.cookie jar after the scripts ran (empty for an untrusted
     * host). The caller folds it back into the ephemeral network jar. */
    char *set_cookies = NULL;
    size_t sclen = 0;
    if (read_field(t->resp_fd, &set_cookies, &sclen) != 0) {
        free(title); free(text); free(navreq); pv_free(view);
        fb_buffer_free(&console);
        return io_failure(t);
    }
    if (set_cookies != NULL && set_cookies[0] == '\0') { free(set_cookies); set_cookies = NULL; }

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
                fb_buffer_free(&console); free(set_cookies);
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
    out->next_timer_ms = (next_ms >= 0) ? (int)next_ms : -1;
    out->set_cookies = set_cookies; /* ownership moves to the caller */
    return TAB_OK;
}

/* Shared request/response for the two short mutation commands (OP_CLICK with the
 * node id / OP_TICK with the elapsed ms): the worker fires handlers, re-derives
 * the view and answers with the OP_LOAD tail (no navigation) + next_timer_ms. */
static tab_status tab_mutation_request(tab *t, uint8_t op, int32_t arg, tab_page *out) {
    tab_refresh_alive(t);
    if (!t->alive) return TAB_ERR_DEAD;

    if (write_full(t->req_fd, &op, 1) != 0
     || write_full(t->req_fd, &arg, sizeof arg) != 0) {
        tab_refresh_alive(t);
        return t->alive ? TAB_ERR_IO : TAB_ERR_DEAD;
    }

    return tab_read_view(t, out);
}

tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out) {
    if (t == NULL || out == NULL) return TAB_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);

    return tab_mutation_request(t, OP_CLICK, (int32_t)node_id, out);
}

tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out) {
    if (t == NULL || out == NULL) return TAB_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    return tab_mutation_request(t, OP_TICK,
                                (int32_t)(elapsed_ms >= 0 ? elapsed_ms : 0), out);
}

/* Dispatches a submit event on the form enclosing node_id. Simple response:
 * [TAG_RESULT][ok:int32][prevented:int32]. No view re-derivation. */
tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented) {
    if (t == NULL || prevented == NULL) return TAB_ERR_NULL_ARG;
    *prevented = 0;
    tab_refresh_alive(t);
    if (!t->alive) return TAB_ERR_DEAD;

    uint8_t op = OP_SUBMIT;
    int32_t arg = (int32_t)node_id;
    if (write_full(t->req_fd, &op, 1) != 0
     || write_full(t->req_fd, &arg, sizeof arg) != 0) {
        tab_refresh_alive(t);
        return t->alive ? TAB_ERR_IO : TAB_ERR_DEAD;
    }

    uint8_t tag = 0;
    if (read_full(t->resp_fd, &tag, 1) != 0) return io_failure(t);
    if (tag != TAG_RESULT) return io_failure(t);

    int32_t ok = 0, p = 1;
    if (read_full(t->resp_fd, &ok, sizeof ok) != 0) return io_failure(t);
    if (read_full(t->resp_fd, &p, sizeof p) != 0) return io_failure(t);
    *prevented = (ok && !p) ? 1 : 0;
    return TAB_OK;
}

/* Sends a generic DOM event to the worker. Wire format:
 * OP_EVENT(1) + node_id:int32 + event_type_len:size_t + event_type +
 * key_len:size_t + key + key_code:int32 + value_len:size_t + value.
 * Returns TAB_OK if the event was dispatched and the worker replied (which
 * includes a re-derived view for repainting). If *out is populated on TAB_OK,
 * it must be released with tab_page_free. */
tab_status tab_dispatch_event(tab *t, dom_node_id node_id,
                              const char *event_type,
                              const char *key, int key_code,
                              const char *value,
                              tab_page *out) {
    if (t == NULL || out == NULL || event_type == NULL) return TAB_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (node_id == DOM_NODE_NONE) return TAB_ERR_NULL_ARG;

    tab_refresh_alive(t);
    if (!t->alive) return TAB_ERR_DEAD;

    size_t tlen = strlen(event_type);
    size_t klen = (key != NULL) ? strlen(key) : 0;
    size_t vlen = (value != NULL) ? strlen(value) : 0;

    uint8_t op = OP_EVENT;
    int32_t nid = (int32_t)node_id;
    int32_t kc = key_code;
    if (write_full(t->req_fd, &op, 1) != 0
     || write_full(t->req_fd, &nid, sizeof nid) != 0
     || write_full(t->req_fd, &tlen, sizeof tlen) != 0
     || (tlen > 0 && write_full(t->req_fd, event_type, tlen) != 0)
     || write_full(t->req_fd, &klen, sizeof klen) != 0
     || (klen > 0 && write_full(t->req_fd, key, klen) != 0)
     || write_full(t->req_fd, &kc, sizeof kc) != 0
     || write_full(t->req_fd, &vlen, sizeof vlen) != 0
     || (vlen > 0 && write_full(t->req_fd, value, vlen) != 0)) {
        tab_refresh_alive(t);
        return t->alive ? TAB_ERR_IO : TAB_ERR_DEAD;
    }

    /* The worker replies with TAG_RESULT + TAG_VIEW (re-derived page view). */
    return tab_read_view(t, out);
}

/* Sends a mouse DOM event to the worker. Wire format:
 * OP_MOUSE(1) + node_id:int32 + event_type_len:size_t + event_type +
 * client_x:int32 + client_y:int32 + button:int32.
 * Returns TAB_OK if the event was dispatched and the worker replied (which
 * includes a re-derived view for repainting). */
tab_status tab_dispatch_mouse(tab *t, dom_node_id node_id,
                              const char *event_type,
                              int client_x, int client_y, int button,
                              tab_page *out) {
    if (t == NULL || out == NULL || event_type == NULL) return TAB_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (node_id == DOM_NODE_NONE) return TAB_ERR_NULL_ARG;

    tab_refresh_alive(t);
    if (!t->alive) return TAB_ERR_DEAD;

    size_t tlen = strlen(event_type);
    if (tlen == 0) return TAB_ERR_NULL_ARG;

    uint8_t op = OP_MOUSE;
    int32_t nid = (int32_t)node_id;
    int32_t cx = client_x, cy = client_y, btn = button;
    if (write_full(t->req_fd, &op, 1) != 0
     || write_full(t->req_fd, &nid, sizeof nid) != 0
     || write_full(t->req_fd, &tlen, sizeof tlen) != 0
     || write_full(t->req_fd, event_type, tlen) != 0
     || write_full(t->req_fd, &cx, sizeof cx) != 0
     || write_full(t->req_fd, &cy, sizeof cy) != 0
     || write_full(t->req_fd, &btn, sizeof btn) != 0) {
        tab_refresh_alive(t);
        return t->alive ? TAB_ERR_IO : TAB_ERR_DEAD;
    }

    return tab_read_view(t, out);
}

/* Reads the TAG_RESULT + TAG_VIEW response into *out (titles + view + console).
 * Used by tab_mutation_request, tab_subreq, tab_dispatch_event. */
tab_status tab_read_view(tab *t, tab_page *out) {
    if (t == NULL || out == NULL) return TAB_ERR_NULL_ARG;
    uint8_t tag = 0;
    if (read_full(t->resp_fd, &tag, 1) != 0) return io_failure(t);
    if (tag != TAG_RESULT) return io_failure(t);

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
    char *navreq = NULL;
    size_t nlen = 0;
    int32_t nav_replace = 0;
    if (read_field(t->resp_fd, &navreq, &nlen) != 0
     || read_full(t->resp_fd, &nav_replace, sizeof nav_replace) != 0) {
        free(title); free(text); free(navreq); pv_free(view);
        return io_failure(t);
    }
    free(navreq);

    fb_buffer console;
    fb_buffer_init(&console);
    if (read_console(t->resp_fd, &console) != 0) {
        free(title); free(text); pv_free(view);
        fb_buffer_free(&console);
        return io_failure(t);
    }
    int32_t next_ms = -1;
    if (read_full(t->resp_fd, &next_ms, sizeof next_ms) != 0) {
        free(title); free(text); pv_free(view);
        fb_buffer_free(&console);
        return io_failure(t);
    }

    out->title = title; out->title_len = tl;
    out->text  = text;  out->text_len  = xl;
    out->view  = view;
    out->nav_url = NULL;
    out->nav_replace = 0;
    out->console = console;
    out->next_timer_ms = (next_ms >= 0) ? (int)next_ms : -1;
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
    free(t->cookies_in);
    free(t);
}

void tab_page_free(tab_page *p) {
    if (p == NULL) return;
    free(p->title);
    free(p->text);
    pv_free(p->view);
    free(p->nav_url);
    free(p->set_cookies);
    fb_buffer_free(&p->console);
    p->title = NULL;
    p->text = NULL;
    p->view = NULL;
    p->nav_url = NULL;
    p->set_cookies = NULL;
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
