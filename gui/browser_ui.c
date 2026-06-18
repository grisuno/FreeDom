/*
 * browser_ui — Wayland + Cairo + xkbcommon GUI for Freedom.
 *
 * Provides a minimal browser window with Back/Forward buttons, URL bar, and
 * scrollable text content. The heavy lifting (navigation state, secure_fetch,
 * tab sandbox) lives in src/browser.c, src/secure_fetch.c and src/tab.c; this
 * file only wires input/output and paints the frame.
 *
 * Visual test only: run on a Wayland session.
 */

#define _GNU_SOURCE

#include "browser.h"
#include "css_color.h"
#include "link_nav.h"
#include "render_doc.h"
#include "render_policy.h"
#include "textfield.h"
#include "ui.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <poll.h>
#include <sys/mman.h>
#include <errno.h>

#include <wayland-client.h>
#include <wayland-cursor.h>
#include <cairo/cairo.h>
#include <fontconfig/fontconfig.h>
#include <xkbcommon/xkbcommon.h>

#include "xdg-shell-client-protocol.h"
#include "xdg-decoration-client-protocol.h"

#define UI_FONT_SIZE   14.0
#define UI_TOOLBAR_H   36.0
#define UI_TITLEBAR_H  30.0
#define UI_BTN_W       48.0
#define UI_WIN_BTN_W   30.0
#define UI_MARGIN      6.0
#define UI_BTN_LEFT    0x110  /* BTN_LEFT */
#define UI_TEXT_MARGIN 8.0

/* Options menu (gear) panel geometry and the pointer cursor size, gathered with
 * the other chrome constants so no value is hardcoded at a call site. The panel is
 * wide enough to edit a User-Agent string. */
#define UI_MENU_W       340.0
#define UI_MENU_ITEM_H  28.0
#define UI_MENU_PAD     6.0
#define UI_CHECK_SZ     16.0
#define UI_MENU_LABEL_H 22.0   /* height of the "User-Agent" section label row */
#define UI_MENU_INPUT_H 26.0   /* height of the editable User-Agent box */
#define UI_HAMBURGER_W  18.0   /* width of the drawn menu-button icon */
#define UI_HAMBURGER_GAP 5.0   /* vertical gap between the three icon bars */
#define UI_CURSOR_SIZE  24     /* themed cursor size in px (XCURSOR_SIZE default) */
#define UI_TOAST_PAD    8.0    /* padding inside the toast banner */

/* Number of heading levels (h1..h6). Index 0 of the scale table is body text. */
#define UI_HEADING_LEVELS 6

/* Form control geometry: inner padding of a text box, the preferred text-box width
 * (clamped to the content width), and the horizontal padding of a button. */
#define UI_INPUT_PAD     6.0
#define UI_INPUT_WIDTH   360.0
#define UI_BUTTON_HPAD   14.0
#define UI_FORM_FIELDS_MAX 64  /* matches FM_MAX_FIELDS; cap gathered controls */

/* Link underline geometry, expressed relative to the run's font so it scales
 * with heading-sized links. Offset below the baseline; thickness in px. */
#define UI_UNDERLINE_OFFSET 0.12
#define UI_UNDERLINE_THICK  1.0

/* Largest text slice measured/drawn at once (one word, or one clipped label).
 * Words longer than this are still placed, just measured up to the cap. */
#define UI_SLICE_MAX 512

/* Presentation theme: every font size, spacing and colour the renderer uses,
 * gathered in one place so no value is hardcoded at a call site. An RGB colour is
 * a 3-element array in [0,1]. The structured content painter and the window
 * chrome both read from a single theme instance (see ui_theme_default). */
typedef struct ui_rgb { double r, g, b; } ui_rgb;

typedef struct ui_theme {
    double body_font;                          /* body text size (px) */
    double heading_scale[UI_HEADING_LEVELS + 1]; /* [level] multiplier; [0] = body */
    double line_spacing;                       /* multiplier of font height per line */
    double paragraph_gap;                      /* extra px above a new paragraph block */
    double content_margin;                     /* left/right/top padding of the content area */
    double image_box_pad;                      /* padding inside an image placeholder box */
    double scroll_step_lines;                  /* wheel/arrow scroll step, in body lines */
    double page_step_lines;                    /* Page Up/Down scroll step, in body lines */

    ui_rgb window_bg;
    ui_rgb content_bg;
    ui_rgb text;
    ui_rgb heading;
    ui_rgb link;
    ui_rgb notice_bg;
    ui_rgb notice_text;
    ui_rgb image_box;       /* placeholder border + label */
    ui_rgb image_blocked;   /* label colour for a blocked image */
    ui_rgb toolbar_bg;
    ui_rgb titlebar_bg;
    ui_rgb chrome_text;
    ui_rgb chrome_text_dim; /* disabled button */
    ui_rgb close_button;
    ui_rgb url_bg_focused;
    ui_rgb url_bg;
    ui_rgb url_border;
    ui_rgb caret;
    ui_rgb link_hover_bg;   /* highlight behind the link under the pointer */
    ui_rgb input_bg;        /* form text input background */
    ui_rgb input_bg_focused;
    ui_rgb input_border;
    ui_rgb input_text;
    ui_rgb input_placeholder;
    ui_rgb button_bg;       /* submit/button control */
    ui_rgb button_text;
    ui_rgb menu_bg;
    ui_rgb menu_border;
    ui_rgb menu_text;
    ui_rgb check_border;
    ui_rgb check_mark;
    ui_rgb toast_bg;
    ui_rgb toast_text;
} ui_theme;

/* The single source of truth for the look of the browser. */
static ui_theme ui_theme_default(void) {
    ui_theme t;
    t.body_font = UI_FONT_SIZE;
    t.heading_scale[0] = 1.0;
    t.heading_scale[1] = 2.0;
    t.heading_scale[2] = 1.6;
    t.heading_scale[3] = 1.35;
    t.heading_scale[4] = 1.2;
    t.heading_scale[5] = 1.1;
    t.heading_scale[6] = 1.05;
    t.line_spacing = 1.3;
    t.paragraph_gap = 8.0;
    t.content_margin = UI_TEXT_MARGIN;
    t.image_box_pad = 6.0;
    t.scroll_step_lines = 3.0;
    t.page_step_lines = 10.0;

    t.window_bg      = (ui_rgb){ 0.96, 0.96, 0.96 };
    t.content_bg     = (ui_rgb){ 1.00, 1.00, 1.00 };
    t.text           = (ui_rgb){ 0.10, 0.10, 0.10 };
    t.heading        = (ui_rgb){ 0.06, 0.08, 0.20 };
    t.link           = (ui_rgb){ 0.10, 0.33, 0.80 };
    t.notice_bg      = (ui_rgb){ 1.00, 0.95, 0.70 };
    t.notice_text    = (ui_rgb){ 0.40, 0.28, 0.00 };
    t.image_box      = (ui_rgb){ 0.45, 0.45, 0.50 };
    t.image_blocked  = (ui_rgb){ 0.70, 0.30, 0.30 };
    t.toolbar_bg     = (ui_rgb){ 0.22, 0.23, 0.25 };
    t.titlebar_bg    = (ui_rgb){ 0.12, 0.12, 0.14 };
    t.chrome_text    = (ui_rgb){ 0.85, 0.85, 0.85 };
    t.chrome_text_dim= (ui_rgb){ 0.45, 0.45, 0.45 };
    t.close_button   = (ui_rgb){ 1.00, 0.55, 0.55 };
    t.url_bg_focused = (ui_rgb){ 1.00, 1.00, 1.00 };
    t.url_bg         = (ui_rgb){ 0.92, 0.92, 0.92 };
    t.url_border     = (ui_rgb){ 0.10, 0.10, 0.10 };
    t.caret          = (ui_rgb){ 0.00, 0.00, 0.00 };
    t.link_hover_bg  = (ui_rgb){ 0.88, 0.93, 1.00 };
    t.input_bg          = (ui_rgb){ 1.00, 1.00, 1.00 };
    t.input_bg_focused  = (ui_rgb){ 1.00, 1.00, 0.96 };
    t.input_border      = (ui_rgb){ 0.55, 0.55, 0.60 };
    t.input_text        = (ui_rgb){ 0.08, 0.08, 0.10 };
    t.input_placeholder = (ui_rgb){ 0.55, 0.55, 0.58 };
    t.button_bg         = (ui_rgb){ 0.22, 0.42, 0.78 };
    t.button_text       = (ui_rgb){ 0.98, 0.98, 1.00 };
    t.menu_bg        = (ui_rgb){ 0.98, 0.98, 0.99 };
    t.menu_border    = (ui_rgb){ 0.55, 0.55, 0.60 };
    t.menu_text      = (ui_rgb){ 0.10, 0.10, 0.12 };
    t.check_border   = (ui_rgb){ 0.35, 0.35, 0.40 };
    t.check_mark     = (ui_rgb){ 0.10, 0.45, 0.20 };
    t.toast_bg       = (ui_rgb){ 0.15, 0.15, 0.18 };
    t.toast_text     = (ui_rgb){ 0.95, 0.95, 0.97 };
    return t;
}

/* Converts a packed 0xRRGGBB author color into a theme RGB triple. */
static ui_rgb rgb_from_packed(int packed) {
    cc_rgb c = cc_unpack(packed);
    return (ui_rgb){ c.r / 255.0, c.g / 255.0, c.b / 255.0 };
}

/* Monotonic millisecond clock for toast timing (caller of the pure browser API). */
static uint64_t now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000u + (uint64_t)ts.tv_nsec / 1000000u;
}

/* The options-menu items, mapped to a render capability by field offset so labels
 * and the toggled flag live in exactly one place (no magic indices). */
typedef struct ui_menu_item {
    const char *label;
    size_t      cap_offset; /* offset of a bool field within rdp_caps */
} ui_menu_item;

static const ui_menu_item UI_MENU_ITEMS[] = {
    { "Load images",         offsetof(rdp_caps, images) },
    { "Author colors (CSS)", offsetof(rdp_caps, css) },
};
#define UI_MENU_COUNT (sizeof UI_MENU_ITEMS / sizeof UI_MENU_ITEMS[0])

static void set_rgb(cairo_t *cr, ui_rgb c) {
    cairo_set_source_rgb(cr, c.r, c.g, c.b);
}

/* Live editable state for one form text control, aliasing a block of the current
 * rd_doc (not owned; valid until the doc is replaced). The field carries the value
 * the user is editing; submission reads it back. */
typedef struct ui_input_state {
    const rd_block *blk;   /* the RD_INPUT block (aliases w->doc) */
    tf_field        field; /* live editable value */
} ui_input_state;

typedef struct browser_window {
    struct wl_display    *display;
    struct wl_registry   *registry;
    struct wl_compositor *compositor;
    struct wl_shm        *shm;
    struct xdg_wm_base   *wm_base;
    struct wl_seat       *seat;
    struct wl_pointer    *pointer;
    struct wl_keyboard   *keyboard;

    struct wl_surface    *surface;
    struct xdg_surface   *xdg_surface;
    struct xdg_toplevel  *xdg_toplevel;

    int width, height;
    int configured;
    int running;
    int redraw_pending;

    struct wl_buffer *buffer;
    void             *shm_data;
    size_t            shm_size;
    cairo_surface_t  *cairo_surface;

    struct zxdg_decoration_manager_v1  *deco_mgr;
    struct zxdg_toplevel_decoration_v1 *deco;
    int use_csd;

    double ptr_x, ptr_y;

    browser_state bs;
    int url_bar_focused;

    ui_theme  theme;
    rd_doc   *doc;      /* structured render of the current page; NULL => text mode */
    rdp_caps  caps;     /* per-page render capabilities (images off by default) */
    double    scroll;   /* content scroll offset in pixels */

    int         menu_open;     /* the options (gear) panel is showing */
    const char *hover_href;    /* link target under the pointer (aliases doc), or NULL */

    /* Live form text controls of the current page (rebuilt with the doc). */
    ui_input_state *inputs;
    size_t          input_count;
    int             focused_input; /* index into inputs, or -1 */

    /* Configurable network User-Agent (session only; empty => SF_DEFAULT_USER_AGENT).
     * navigator.userAgent in JS stays normalised by anti_fp regardless. Edited in
     * the options menu with the shared textfield primitive. */
    tf_field    ua_field;
    int         ua_field_focused;

    /* Cached source of the current page, so a capability toggle re-renders without
     * a network round-trip. cur_top is the https origin (image policy) or NULL. */
    char  *cur_html;
    size_t cur_html_len;
    char  *cur_top;

    uint32_t            pointer_serial; /* last pointer-enter serial, for set_cursor */
    struct wl_cursor_theme *cursor_theme;
    struct wl_cursor       *cursor_default;
    struct wl_cursor       *cursor_hand;
    struct wl_surface      *cursor_surface;

    /* xkbcommon state for keyboard input. */
    struct xkb_context *xkb_ctx;
    struct xkb_keymap  *xkb_keymap;
    struct xkb_state   *xkb_state;
} browser_window;

/* Pointer to the rdp_caps bool toggled by options-menu item i. */
static bool *menu_item_flag(browser_window *w, size_t i) {
    return (bool *)((char *)&w->caps + UI_MENU_ITEMS[i].cap_offset);
}

static void redraw(browser_window *w);

/* --- shm buffer (same pattern as ui_render.c) --- */

static void buffer_release(void *data, struct wl_buffer *wl_buffer) {
    (void)wl_buffer;
    (void)data;
}
static const struct wl_buffer_listener buffer_listener = { buffer_release };

static void destroy_buffer(browser_window *w) {
    if (w->cairo_surface) { cairo_surface_destroy(w->cairo_surface); w->cairo_surface = NULL; }
    if (w->buffer) { wl_buffer_destroy(w->buffer); w->buffer = NULL; }
    if (w->shm_data) { munmap(w->shm_data, w->shm_size); w->shm_data = NULL; w->shm_size = 0; }
}

static int ensure_buffer(browser_window *w) {
    int stride = w->width * 4;
    size_t size = (size_t)stride * (size_t)w->height;
    if (w->buffer && w->shm_size == size && w->cairo_surface) return 0;

    destroy_buffer(w);

    int fd = memfd_create("freedom-shm", MFD_CLOEXEC);
    if (fd < 0) return -1;
    if (ftruncate(fd, (off_t)size) < 0) { close(fd); return -1; }

    void *data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) { close(fd); return -1; }

    struct wl_shm_pool *pool = wl_shm_create_pool(w->shm, fd, (int32_t)size);
    w->buffer = wl_shm_pool_create_buffer(pool, 0, w->width, w->height, stride, WL_SHM_FORMAT_ARGB8888);
    wl_shm_pool_destroy(pool);
    close(fd);
    if (w->buffer == NULL) { munmap(data, size); return -1; }
    wl_buffer_add_listener(w->buffer, &buffer_listener, w);

    w->shm_data = data;
    w->shm_size = size;
    w->cairo_surface = cairo_image_surface_create_for_data(
        (unsigned char *)data, CAIRO_FORMAT_ARGB32, w->width, w->height, stride);
    return (cairo_surface_status(w->cairo_surface) == CAIRO_STATUS_SUCCESS) ? 0 : -1;
}

/* --- page loading --- */

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

static int is_https_url(const char *s) {
    return strncmp(s, "https://", 8) == 0;
}

/* Extract hostname from https://host[:port][/path]. Returns 0 on parse failure. */
static int host_from_url(const char *url, char *out, size_t outsz) {
    if (!is_https_url(url)) return 0;
    const char *p = url + 8; /* skip https:// */
    /* Optional userinfo (not expected). */
    const char *at = strchr(p, '@');
    if (at != NULL) p = at + 1;
    const char *slash = strchr(p, '/');
    const char *end = slash != NULL ? slash : p + strlen(p);
    const char *colon = memchr(p, ':', (size_t)(end - p));
    const char *host_end = colon != NULL ? colon : end;
    size_t len = (size_t)(host_end - p);
    if (len == 0 || len >= outsz) return 0;
    memcpy(out, p, len);
    out[len] = '\0';
    return 1;
}

#include "form.h"
#include "secure_fetch.h"
#include "tab.h"

/* An editable control gets a live text field; submit/button/hidden do not. */
static int input_is_editable(int input_type) {
    return input_type == PV_IN_TEXT || input_type == PV_IN_PASSWORD
        || input_type == PV_IN_TEXTAREA;
}

/* Releases the live form-control states (the array; fields are inline). */
static void free_inputs(browser_window *w) {
    free(w->inputs);
    w->inputs = NULL;
    w->input_count = 0;
    w->focused_input = -1;
}

/* Builds the live editable state for the current doc: one entry per editable
 * control, seeded with its declared value. Aliases the doc blocks (not owned). */
static void rebuild_inputs(browser_window *w) {
    free_inputs(w);
    if (w->doc == NULL) return;
    size_t n = rd_count(w->doc);
    size_t editable = 0;
    for (size_t i = 0; i < n; ++i) {
        const rd_block *b = rd_at(w->doc, i);
        if (b->kind == RD_INPUT && input_is_editable(b->input_type)) editable++;
    }
    if (editable == 0) return;
    w->inputs = (ui_input_state *)calloc(editable, sizeof *w->inputs);
    if (w->inputs == NULL) return; /* fail closed: no editable fields, page still shows */
    size_t k = 0;
    for (size_t i = 0; i < n; ++i) {
        const rd_block *b = rd_at(w->doc, i);
        if (b->kind != RD_INPUT || !input_is_editable(b->input_type)) continue;
        ui_input_state *st = &w->inputs[k++];
        st->blk = b;
        tf_init(&st->field);
        if (b->value != NULL) tf_set(&st->field, b->value);
    }
    w->input_count = k;
}

/* The live state for a given doc block, or NULL when it has none. */
static ui_input_state *find_input_state(browser_window *w, const rd_block *blk) {
    for (size_t i = 0; i < w->input_count; ++i)
        if (w->inputs[i].blk == blk) return &w->inputs[i];
    return NULL;
}

/* Releases the structured render of the previous page (text mode resumes). The
 * hovered link and the live form controls alias the doc, so they are cleared too. */
static void clear_doc(browser_window *w) {
    free_inputs(w);
    if (w->doc != NULL) { rd_free(w->doc); w->doc = NULL; }
    w->hover_href = NULL;
}

/* Replaces the cached page source. Takes ownership of html; copies top. */
static void set_cache(browser_window *w, char *html, size_t len, const char *top) {
    free(w->cur_html);
    free(w->cur_top);
    w->cur_html = html;
    w->cur_html_len = len;
    w->cur_top = (top != NULL) ? strdup(top) : NULL;
}

/* Renders the cached page source into the page/doc using the current capabilities.
 * No network: a capability toggle (images/CSS) re-renders from cache. Does nothing
 * when there is no cached source (start/error pages stay in plain-text mode). */
static void render_current(browser_window *w) {
    clear_doc(w);
    if (w->cur_html == NULL) return;

    tab *t = NULL;
    if (tab_open(&t) != TAB_OK) {
        browser_set_page(&w->bs, NULL, "Failed to spawn sandboxed tab.", 1);
        return;
    }

    tab_page page;
    memset(&page, 0, sizeof page);
    if (tab_load(t, w->cur_html, w->cur_html_len, &page) != TAB_OK) {
        browser_set_page(&w->bs, NULL, "Failed to render page in sandbox.", 1);
        tab_close(t);
        return;
    }

    browser_set_page(&w->bs, page.title, page.text, 0);

    /* The top-level URL is the https origin (per-image policy) or NULL for a local
     * file, which fails image loads closed. On failure doc stays NULL and the
     * plain-text painter still shows the extracted text. */
    rd_doc *doc = NULL;
    if (rd_build(page.view, w->caps, w->cur_top, &doc) == RD_OK) {
        w->doc = doc;
    }
    rebuild_inputs(w); /* seed live editable state for this page's controls */

    tab_page_free(&page);
    tab_close(t);
}

static void do_load(browser_window *w, const char *url) {
    if (url == NULL) return;

    /* A fresh navigation: drop the old structured render and scroll to the top.
     * Error/start pages then fall back to the plain-text painter (doc == NULL). */
    clear_doc(w);
    w->scroll = 0.0;
    w->menu_open = 0;
    w->ua_field_focused = 0;
    w->focused_input = -1;

    if (strcmp(url, "about:blank") == 0) {
        set_cache(w, NULL, 0, NULL);
        browser_set_page(&w->bs, "Freedom", "", 0);
        return;
    }

    char *html = NULL;
    size_t html_len = 0;

    if (is_https_url(url)) {
        sf_config cfg = sf_config_default();
        cfg.user_agent = tf_text(&w->ua_field); /* "" => SF_DEFAULT_USER_AGENT */
        char host[256];
        if (host_from_url(url, host, sizeof host) && browser_is_exception(&w->bs, host)) {
            cfg.policy = SF_POLICY_PERMISSIVE;
        }

        sf_response resp;
        memset(&resp, 0, sizeof resp);
        /* Follow redirects (e.g. google.com -> www.google.com); each hop is a
         * fresh request that re-applies the full TLS/PQ/chain policy. */
        sf_status ss = sf_get_follow(url, &cfg, &resp, SF_DEFAULT_MAX_REDIRECTS);
        if (ss != SF_OK) {
            char msg[1024];
            const char *reason = "";
            switch (ss) {
                case SF_ERR_TLS_VERSION:  reason = "TLS version below 1.3"; break;
                case SF_ERR_KEM_NOT_PQ:   reason = "key exchange is not PQ-hybrid"; break;
                case SF_ERR_WEAK_ALGO:    reason = "weak certificate/key algorithm"; break;
                case SF_ERR_CERT_INVALID: reason = "certificate validation failed"; break;
                case SF_ERR_CERT_NOT_PQ:  reason = "strict PQ signature missing"; break;
                case SF_ERR_NETWORK:      reason = "network error"; break;
                case SF_ERR_TOO_MANY_REDIRECTS: reason = "too many redirects"; break;
                default:                  reason = "fetch error"; break;
            }
            char bypass[512];
            bypass[0] = '\0';
            if (ss == SF_ERR_WEAK_ALGO || ss == SF_ERR_CERT_INVALID || ss == SF_ERR_CERT_NOT_PQ) {
                if (host_from_url(url, host, sizeof host)) {
                    snprintf(bypass, sizeof bypass,
                        "\n\nPress Ctrl+Shift+E to add '%s' to the exception list and reload insecurely.\n"
                        "This is stored for the current session only.", host);
                }
            }
            snprintf(msg, sizeof msg,
                     "Failed to load '%s'.\nStatus %d: %s.\n\n"
                     "Freedom rejects TLS < 1.3, a non-PQ-hybrid key exchange, a site\n"
                     "(leaf) certificate with RSA < 3072, any SHA-1 signature in the\n"
                     "chain, and certificates that fail strict validation.\n"
                     "%s",
                     url, (int)ss, reason, bypass);
            set_cache(w, NULL, 0, NULL);
            browser_set_page(&w->bs, NULL, msg, 1);
            sf_response_free(&resp);
            return;
        }
        html = (char *)resp.body;
        html_len = resp.body_len;
        resp.body = NULL;
        sf_response_free(&resp);
    } else {
        html = read_file(url, &html_len);
        if (html == NULL) {
            char msg[256];
            snprintf(msg, sizeof msg, "Cannot read file '%s': %s.", url, strerror(errno));
            set_cache(w, NULL, 0, NULL);
            browser_set_page(&w->bs, NULL, msg, 1);
            return;
        }
    }

    /* Cache the source (image policy uses the https origin) and render it. A later
     * capability toggle re-renders from this cache without a network round-trip. */
    set_cache(w, html, html_len, is_https_url(url) ? url : NULL);
    render_current(w);
}

/* --- painting --- */

static void toolbar_rects(const browser_window *w,
                          double *back_x, double *fwd_x,
                          double *url_x, double *url_w,
                          double *go_x, double *menu_x);

static double toolbar_top(const browser_window *w) {
    return w->use_csd ? UI_TITLEBAR_H : 0.0;
}

/* The content area rectangle below the toolbar, in surface coordinates. The
 * single source of truth for both painting and click hit-testing so they cannot
 * drift apart. */
static void content_geometry(const browser_window *w, double *top, double *height) {
    double t = toolbar_top(w) + UI_TOOLBAR_H;
    double h = (double)w->height - t - 2.0 * w->theme.content_margin;
    if (h < 1.0) h = 1.0;
    *top = t;
    *height = h;
}

static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *close_x) {
    *close_x = w->width - UI_WIN_BTN_W;
    *max_x   = w->width - 2 * UI_WIN_BTN_W;
    *min_x   = w->width - 3 * UI_WIN_BTN_W;
}

static void toolbar_rects(const browser_window *w,
                          double *back_x, double *fwd_x,
                          double *url_x, double *url_w,
                          double *go_x, double *menu_x) {
    *back_x = 0.0;
    *fwd_x  = UI_BTN_W;
    *menu_x = (double)w->width - UI_BTN_W;
    *go_x   = *menu_x - UI_BTN_W;
    *url_x  = UI_BTN_W * 2.0 + UI_MARGIN;
    *url_w  = *go_x - *url_x - UI_MARGIN;
    if (*url_w < 20.0) *url_w = 20.0;
}

/* The options-menu panel rectangle (below the gear button), and its per-item row
 * height. The single source of truth for drawing and hit-testing the panel. */
static void menu_panel_rect(const browser_window *w, double *x, double *y,
                            double *width, double *height, double *item_h) {
    double back_x, fwd_x, url_x, url_w, go_x, menu_x;
    toolbar_rects(w, &back_x, &fwd_x, &url_x, &url_w, &go_x, &menu_x);
    *width  = UI_MENU_W;
    *x      = menu_x + UI_BTN_W - UI_MENU_W; /* right-aligned under the gear */
    if (*x < 0.0) *x = 0.0;
    *y      = toolbar_top(w) + UI_TOOLBAR_H;
    *item_h = UI_MENU_ITEM_H;
    /* Checkbox rows, then the User-Agent section (label + editable box). */
    *height = 2.0 * UI_MENU_PAD + (double)UI_MENU_COUNT * UI_MENU_ITEM_H
            + UI_MENU_LABEL_H + UI_MENU_INPUT_H + UI_MENU_PAD;
}

/* The editable User-Agent box rectangle inside the options panel. The single
 * source of truth for drawing and hit-testing the field. */
static void ua_box_rect(const browser_window *w, double *x, double *y,
                        double *width, double *height) {
    double mx, my, mw, mh, ih;
    menu_panel_rect(w, &mx, &my, &mw, &mh, &ih);
    *x      = mx + UI_MENU_PAD;
    *width  = mw - 2.0 * UI_MENU_PAD;
    *y      = my + UI_MENU_PAD + (double)UI_MENU_COUNT * UI_MENU_ITEM_H + UI_MENU_LABEL_H;
    *height = UI_MENU_INPUT_H;
}

static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered) {
    if (s == NULL) return;
    cairo_text_extents_t te;
    cairo_text_extents(cr, s, &te);
    double dx = centered ? x - te.width / 2.0 : x;
    cairo_move_to(cr, dx, y);
    cairo_show_text(cr, s);
}

/* ===================== structured content layout + paint ==================== */
/*
 * The content area paints an rd_doc (the same structured document the headless
 * mode prints): headings, paragraphs and inline links flow word-by-word into
 * lines, the image-tracking warning is a banner, and each image is a bordered
 * placeholder showing its render_policy decision. Layout runs once per frame into
 * transient arrays so vertical scrolling can be a smooth pixel offset over the
 * real total height. This is visual-only (no headless test) but compiles under
 * the same hardened flags.
 */

typedef struct rc_frag {
    double      x, width, font_size;
    int         bold, underline;
    ui_rgb      color;
    const char *text;     /* slice into a rd_block text (not owned) */
    size_t      len;
    const char *href;     /* link target (aliases the rd_block href, not owned); NULL if not a link */
} rc_frag;

typedef enum rc_rowkind { RC_TEXT = 0, RC_IMAGE, RC_INPUT } rc_rowkind;

typedef struct rc_row {
    rc_rowkind      kind;
    double          top, height, ascent;
    size_t          first, count;  /* RC_TEXT: frag range */
    int             banner;        /* RC_TEXT: draw the notice background */
    const rd_block *blk;           /* RC_IMAGE: source image block */
} rc_row;

typedef struct rc_layout {
    rc_frag *frags; size_t nfrag, capfrag;
    rc_row  *rows;  size_t nrow,  caprow;
    double   total_h;
} rc_layout;

typedef struct rc_state {
    double cur_top, pending_gap, pen_x, line_asc, line_desc;
    int    line_open, banner;
    size_t line_first;
} rc_state;

static void rc_free(rc_layout *L) { free(L->frags); free(L->rows); }

static rc_frag *rc_add_frag(rc_layout *L) {
    if (L->nfrag == L->capfrag) {
        size_t nc = L->capfrag ? L->capfrag * 2 : 64;
        rc_frag *g = (rc_frag *)realloc(L->frags, nc * sizeof *g);
        if (g == NULL) return NULL;
        L->frags = g; L->capfrag = nc;
    }
    return &L->frags[L->nfrag++];
}

static rc_row *rc_add_row(rc_layout *L) {
    if (L->nrow == L->caprow) {
        size_t nc = L->caprow ? L->caprow * 2 : 32;
        rc_row *g = (rc_row *)realloc(L->rows, nc * sizeof *g);
        if (g == NULL) return NULL;
        L->rows = g; L->caprow = nc;
    }
    return &L->rows[L->nrow++];
}

static void content_font(cairo_t *cr, double size, int bold) {
    cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL,
                           bold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, size);
}

static double measure_slice(cairo_t *cr, const char *s, size_t n) {
    char buf[UI_SLICE_MAX];
    if (n >= sizeof buf) n = sizeof buf - 1;
    memcpy(buf, s, n);
    buf[n] = '\0';
    cairo_text_extents_t te;
    cairo_text_extents(cr, buf, &te);
    return te.x_advance;
}

static void draw_slice(cairo_t *cr, const char *s, size_t n) {
    char buf[UI_SLICE_MAX];
    if (n >= sizeof buf) n = sizeof buf - 1;
    memcpy(buf, s, n);
    buf[n] = '\0';
    cairo_show_text(cr, buf);
}

static void block_style(const ui_theme *th, const rd_block *b,
                        double *size, int *bold, int *underline, ui_rgb *color) {
    *bold = 0; *underline = 0; *size = th->body_font; *color = th->text;
    if (b->kind == RD_HEADING) {
        int lv = (b->heading_level >= 1 && b->heading_level <= UI_HEADING_LEVELS)
                 ? b->heading_level : 1;
        *size = th->body_font * th->heading_scale[lv];
        *bold = 1; *color = th->heading;
    } else if (b->kind == RD_LINK) {
        *color = th->link; *underline = 1;
    } else if (b->kind == RD_NOTICE) {
        *color = th->notice_text;
    }
}

static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th) {
    if (!s->line_open) return;
    double h = (s->line_asc + s->line_desc) * th->line_spacing;
    rc_row *r = rc_add_row(L);
    if (r != NULL) {
        r->kind = RC_TEXT; r->top = s->cur_top; r->height = h; r->ascent = s->line_asc;
        r->first = s->line_first; r->count = L->nfrag - s->line_first;
        r->banner = s->banner; r->blk = NULL;
    }
    s->cur_top += h;
    s->line_open = 0; s->pen_x = 0; s->line_asc = 0; s->line_desc = 0;
    s->line_first = L->nfrag;
}

static void open_line(rc_layout *L, rc_state *s) {
    if (s->line_open) return;
    if (L->nrow > 0) s->cur_top += s->pending_gap;  /* no leading gap at the very top */
    s->pending_gap = 0;
    s->line_open = 1;
    s->pen_x = 0;
    s->line_first = L->nfrag;
}

/* Places the words of text into the current inline line, wrapping at content_w.
 * href tags every fragment produced (NULL for non-link runs) so a later hit-test
 * can recover the click target without re-walking the document. */
static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
                      const char *text, double size, int bold, int underline,
                      ui_rgb color, double content_w, const char *href) {
    content_font(cr, size, bold);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    double space_w = measure_slice(cr, " ", 1);

    size_t i = 0, n = strlen(text);
    while (i < n) {
        while (i < n && text[i] == ' ') ++i;
        size_t ws = i;
        while (i < n && text[i] != ' ') ++i;
        size_t wl = i - ws;
        if (wl == 0) break;

        double ww = measure_slice(cr, text + ws, wl);
        open_line(L, s);
        double adv = (s->pen_x > 0.0) ? space_w : 0.0;
        if (s->pen_x > 0.0 && s->pen_x + adv + ww > content_w) {
            flush_line(L, s, th);
            open_line(L, s);
            adv = 0.0;
        }
        s->pen_x += adv;

        rc_frag *f = rc_add_frag(L);
        if (f != NULL) {
            f->x = s->pen_x; f->width = ww; f->font_size = size;
            f->bold = bold; f->underline = underline; f->color = color;
            f->text = text + ws; f->len = wl; f->href = href;
        }
        s->pen_x += ww;
        if (fe.ascent  > s->line_asc)  s->line_asc  = fe.ascent;
        if (fe.descent > s->line_desc) s->line_desc = fe.descent;
    }
}

static void layout_doc(cairo_t *cr, const rd_doc *doc, const ui_theme *th,
                       double content_w, rc_layout *L) {
    memset(L, 0, sizeof *L);
    rc_state s;
    memset(&s, 0, sizeof s);

    for (size_t i = 0; i < rd_count(doc); ++i) {
        const rd_block *b = rd_at(doc, i);
        /* Hidden controls are never painted (their value still submits). */
        if (b->kind == RD_INPUT && b->input_type == PV_IN_HIDDEN) continue;

        int standalone = (b->kind == RD_IMAGE || b->kind == RD_NOTICE
                       || b->kind == RD_HEADING || b->kind == RD_INPUT);
        if (standalone || b->block_break) {
            flush_line(L, &s, th);
            s.pending_gap = th->paragraph_gap;
        }

        if (b->kind == RD_INPUT) {
            content_font(cr, th->body_font, 0);
            cairo_font_extents_t fe;
            cairo_font_extents(cr, &fe);
            double h = fe.height + 2.0 * UI_INPUT_PAD;
            double top = s.cur_top + (L->nrow > 0 ? s.pending_gap : 0.0);
            s.pending_gap = 0;
            rc_row *r = rc_add_row(L);
            if (r != NULL) {
                r->kind = RC_INPUT; r->top = top; r->height = h; r->ascent = fe.ascent;
                r->first = 0; r->count = 0; r->banner = 0; r->blk = b;
            }
            s.cur_top = top + h;
            continue;
        }

        if (b->kind == RD_IMAGE) {
            content_font(cr, th->body_font, 0);
            cairo_font_extents_t fe;
            cairo_font_extents(cr, &fe);
            double h = fe.height + 2.0 * th->image_box_pad;
            double top = s.cur_top + (L->nrow > 0 ? s.pending_gap : 0.0);
            s.pending_gap = 0;
            rc_row *r = rc_add_row(L);
            if (r != NULL) {
                r->kind = RC_IMAGE; r->top = top; r->height = h; r->ascent = fe.ascent;
                r->first = 0; r->count = 0; r->banner = 0; r->blk = b;
            }
            s.cur_top = top + h;
            continue;
        }

        double size; int bold, underline; ui_rgb color;
        block_style(th, b, &size, &bold, &underline, &color);
        /* Author CSS color (already gated by caps.css in render_doc) overrides the
         * theme color while keeping the link underline / heading weight. */
        if (b->fg_rgb >= 0) color = rgb_from_packed(b->fg_rgb);
        const char *href = (b->kind == RD_LINK) ? b->href : NULL;

        if (b->kind == RD_NOTICE) {
            s.banner = 1;
            flow_text(cr, L, &s, th, b->text, size, bold, underline, color, content_w, href);
            flush_line(L, &s, th);
            s.banner = 0;
        } else {
            flow_text(cr, L, &s, th, b->text, size, bold, underline, color, content_w, href);
        }
    }
    flush_line(L, &s, th);
    L->total_h = s.cur_top;
}

/* Width of a painted text-input box: the preferred width clamped to the content. */
static double input_box_width(double content_w) {
    return (content_w < UI_INPUT_WIDTH) ? content_w : UI_INPUT_WIDTH;
}

/* Width of a painted button: its label plus horizontal padding, clamped. */
static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
                               double content_w) {
    content_font(cr, th->body_font, 0);
    const char *label = (b->text != NULL && b->text[0] != '\0') ? b->text
                        : rd_input_label(b->input_type);
    double bw = measure_slice(cr, label, strlen(label)) + 2.0 * UI_BUTTON_HPAD;
    return (bw > content_w) ? content_w : bw;
}

/* Paints one form control row: a filled button, or a bordered editable text box
 * with its value (masked for passwords), placeholder, and caret when focused. */
static void draw_input_row(cairo_t *cr, browser_window *w, const rd_block *b,
                           double left, double content_w, double ry,
                           double ascent, double height) {
    const ui_theme *th = &w->theme;
    int focused = (w->focused_input >= 0 && (size_t)w->focused_input < w->input_count
                   && w->inputs[w->focused_input].blk == b);

    if (b->input_type == PV_IN_SUBMIT || b->input_type == PV_IN_BUTTON) {
        const char *label = (b->text != NULL && b->text[0] != '\0') ? b->text
                            : rd_input_label(b->input_type);
        double bw = button_box_width(cr, th, b, content_w);
        set_rgb(cr, th->button_bg);
        cairo_rectangle(cr, left, ry, bw, height);
        cairo_fill(cr);
        cairo_save(cr);
        cairo_rectangle(cr, left, ry, bw, height);
        cairo_clip(cr);
        set_rgb(cr, th->button_text);
        content_font(cr, th->body_font, 0);
        cairo_move_to(cr, left + UI_BUTTON_HPAD, ry + ascent + UI_INPUT_PAD);
        draw_slice(cr, label, strlen(label));
        cairo_restore(cr);
        return;
    }

    double bw = input_box_width(content_w);
    set_rgb(cr, focused ? th->input_bg_focused : th->input_bg);
    cairo_rectangle(cr, left, ry, bw, height);
    cairo_fill(cr);
    set_rgb(cr, focused ? th->link : th->input_border);
    cairo_set_line_width(cr, 1.0);
    cairo_rectangle(cr, left, ry, bw, height);
    cairo_stroke(cr);

    ui_input_state *st = find_input_state(w, b);
    const char *val = (st != NULL) ? tf_text(&st->field) : (b->value != NULL ? b->value : "");

    content_font(cr, th->body_font, 0);
    cairo_save(cr);
    cairo_rectangle(cr, left + 2.0, ry + 1.0, bw - 4.0, height - 2.0);
    cairo_clip(cr);
    double tx = left + UI_INPUT_PAD;
    double ty = ry + ascent + UI_INPUT_PAD;

    /* A password is shown as a run of '*' (one per value byte). */
    char maskbuf[TF_CAP];
    const char *shown = val;
    if (b->input_type == PV_IN_PASSWORD) {
        size_t vl = strlen(val);
        if (vl >= sizeof maskbuf) vl = sizeof maskbuf - 1;
        memset(maskbuf, '*', vl);
        maskbuf[vl] = '\0';
        shown = maskbuf;
    }

    if (shown[0] == '\0' && b->text != NULL && b->text[0] != '\0') {
        set_rgb(cr, th->input_placeholder);
        cairo_move_to(cr, tx, ty);
        draw_slice(cr, b->text, strlen(b->text));
    } else {
        set_rgb(cr, th->input_text);
        cairo_move_to(cr, tx, ty);
        draw_slice(cr, shown, strlen(shown));
    }

    if (focused && st != NULL) {
        size_t cur = tf_cursor(&st->field);
        size_t slen = strlen(shown);
        if (cur > slen) cur = slen;
        double cx = tx + measure_slice(cr, shown, cur);
        cairo_font_extents_t fe;
        cairo_font_extents(cr, &fe);
        set_rgb(cr, th->caret);
        cairo_rectangle(cr, cx, ty - fe.ascent, 1.5, fe.height);
        cairo_fill(cr);
    }
    cairo_restore(cr);
}

static void paint_image_placeholder(cairo_t *cr, browser_window *w, const rd_block *blk,
                                    double x, double y, double avail_w) {
    const ui_theme *th = &w->theme;
    const double pad = th->image_box_pad;
    double box_w = avail_w - 2.0 * pad;
    if (box_w < 100.0) box_w = 100.0;
    double box_h = 120.0;

    /* Fondo y borde */
    set_rgb(cr, th->image_box);
    cairo_rectangle(cr, x + pad, y + pad, box_w, box_h);
    cairo_set_line_width(cr, 2.0);
    cairo_stroke(cr);

    /* Texto */
    content_font(cr, th->body_font * 0.85, 0);
    const char *label = rd_image_label(blk->img_decision);
    cairo_text_extents_t te;
    cairo_text_extents(cr, label, &te);

    double tx = x + pad + (box_w - te.width) / 2.0;
    double ty = y + pad + box_h / 2.0 + te.height / 2.0;
    cairo_move_to(cr, tx, ty);
    cairo_show_text(cr, label);

    if (blk->img_decision == RDP_IMG_ALLOW && blk->href) {
        cairo_text_extents(cr, "[img]", &te);
        cairo_move_to(cr, x + pad + 8.0, y + pad + 24.0);
        cairo_show_text(cr, "[img]");
    }
}

/* Hook principal para renderizar imágenes RD_IMAGE.
 * Respeta exactamente la política RDP_IMG_ALLOW sin hardcodes.
 * Usa theme existente. */
static void paint_rd_image(cairo_t *cr, browser_window *w, const rd_block *blk,
                           double x, double y, double max_w) {
    if (blk->img_decision != RDP_IMG_ALLOW || blk->href == NULL) {
        paint_image_placeholder(cr, w, blk, x, y, max_w);
        return;
    }

    /* Raíz del bug: aquí iría la carga real de la imagen + cairo_surface.
     * Por ahora fallback al placeholder (mejor que nada). */
    paint_image_placeholder(cr, w, blk, x, y, max_w);
}

/* Paints the structured document into the content rectangle, honouring scroll. */
static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                             double content_h) {
    const ui_theme *th = &w->theme;
    double left = th->content_margin;
    double content_w = (double)w->width - 2.0 * th->content_margin;
    if (content_w < 1.0) content_w = 1.0;

    rc_layout L;
    layout_doc(cr, w->doc, th, content_w, &L);

    double max_scroll = L.total_h - content_h;
    if (max_scroll < 0.0) max_scroll = 0.0;
    if (w->scroll < 0.0) w->scroll = 0.0;
    if (w->scroll > max_scroll) w->scroll = max_scroll;
    double origin = content_top + th->content_margin - w->scroll;

    for (size_t i = 0; i < L.nrow; ++i) {
        const rc_row *r = &L.rows[i];
        double ry = origin + r->top;
        if (ry + r->height < content_top || ry > content_top + content_h) continue;

        if (r->kind == RC_IMAGE && r->blk != NULL) {
            const rd_block *b = r->blk;
            double img_x = left;
            double img_y = ry;
            int blocked = (b->img_decision != RDP_IMG_ALLOW);
            ui_rgb col = blocked ? th->image_blocked : th->image_box;
            cairo_set_line_width(cr, 1.0);
            set_rgb(cr, col);
            cairo_rectangle(cr, left, ry, content_w, r->height);
            cairo_stroke(cr);

            
            content_font(cr, th->body_font, 0);
            cairo_save(cr);
            cairo_rectangle(cr, left + th->image_box_pad, ry,
                            content_w - 2.0 * th->image_box_pad, r->height);
            cairo_clip(cr);
            cairo_move_to(cr, left + th->image_box_pad, ry + r->ascent + th->image_box_pad);
            char label[1024];
            const char *alt = (b->text != NULL) ? b->text : "";
            snprintf(label, sizeof label, "%s%s%s",
                     rd_image_label(b->img_decision), alt[0] ? " : " : "", alt);
            cairo_show_text(cr, label);
            cairo_restore(cr);
            /* Raíz: usar paint_rd_image para manejar ALLOW vs BLOCKED */
            paint_rd_image(cr, w, b, img_x, img_y, content_w);
            continue;
        }

        if (r->kind == RC_INPUT && r->blk != NULL) {
            draw_input_row(cr, w, r->blk, left, content_w, ry, r->ascent, r->height);
            continue;
        }

        if (r->banner) {
            set_rgb(cr, th->notice_bg);
            cairo_rectangle(cr, 0.0, ry, (double)w->width, r->height);
            cairo_fill(cr);
        }
        double baseline = ry + r->ascent;
        for (size_t k = r->first; k < r->first + r->count && k < L.nfrag; ++k) {
            const rc_frag *f = &L.frags[k];
            /* Highlight the link under the pointer (all fragments of that link share
             * its href pointer into the doc). */
            if (f->href != NULL && f->href == w->hover_href) {
                set_rgb(cr, th->link_hover_bg);
                cairo_rectangle(cr, left + f->x, ry, f->width, r->height);
                cairo_fill(cr);
            }
            content_font(cr, f->font_size, f->bold);
            set_rgb(cr, f->color);
            cairo_move_to(cr, left + f->x, baseline);
            draw_slice(cr, f->text, f->len);
            if (f->underline) {
                double uy = baseline + f->font_size * UI_UNDERLINE_OFFSET;
                cairo_set_line_width(cr, UI_UNDERLINE_THICK);
                cairo_move_to(cr, left + f->x, uy);
                cairo_line_to(cr, left + f->x + f->width, uy);
                cairo_stroke(cr);
            }
        }
    }
    rc_free(&L);
}

/* Returns the link target under the surface point (px, py), or NULL when the
 * point is outside the content area or not over a link fragment. The layout and
 * scroll clamping mirror paint_structured exactly, so the hit matches what is on
 * screen. The returned pointer aliases the current rd_doc (it is not owned) and
 * stays valid until the document is replaced; the caller must resolve it before
 * triggering a load that frees the document. */
static const char *link_at_point(browser_window *w, double px, double py) {
    if (w->doc == NULL || w->cairo_surface == NULL) return NULL;

    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);
    if (py < content_top || py > content_top + content_h) return NULL;

    const ui_theme *th = &w->theme;
    double left = th->content_margin;
    double content_w = (double)w->width - 2.0 * th->content_margin;
    if (content_w < 1.0) content_w = 1.0;

    cairo_t *cr = cairo_create(w->cairo_surface);
    rc_layout L;
    layout_doc(cr, w->doc, th, content_w, &L);

    double max_scroll = L.total_h - content_h;
    if (max_scroll < 0.0) max_scroll = 0.0;
    double scroll = w->scroll;
    if (scroll < 0.0) scroll = 0.0;
    if (scroll > max_scroll) scroll = max_scroll;
    double origin = content_top + th->content_margin - scroll;

    const char *hit = NULL;
    for (size_t i = 0; i < L.nrow && hit == NULL; ++i) {
        const rc_row *r = &L.rows[i];
        if (r->kind != RC_TEXT) continue;
        double ry = origin + r->top;
        if (py < ry || py > ry + r->height) continue;
        for (size_t k = r->first; k < r->first + r->count && k < L.nfrag; ++k) {
            const rc_frag *f = &L.frags[k];
            if (f->href == NULL) continue;
            double fx = left + f->x;
            if (px >= fx && px <= fx + f->width) { hit = f->href; break; }
        }
    }

    rc_free(&L);
    cairo_destroy(cr);
    return hit;
}

/* Resolves a clicked link's raw href against the current page location through
 * the pure navigation policy and, only when it yields a navigable target, records
 * the navigation and performs the load. A same-document fragment or a blocked
 * reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content cannot drive an unsafe load. */
static void follow_link(browser_window *w, const char *href) {
    ln_result res;
    if (ln_resolve(browser_current_url(&w->bs), href, &res) != LN_OK) return;
    if (res.action == LN_BLOCKED) {
        /* Tell the user why an unsafe link did nothing (the toast auto-hides). */
        browser_set_status(&w->bs, ln_block_reason_text(res.reason), now_ms());
        return;
    }
    /* A same-document fragment stays on the page (res.fragment carries the anchor
     * id for a future scroll); only a real target navigates. */
    if (res.action != LN_NAVIGATE) return;
    if (browser_navigate(&w->bs, res.target) != BROWSER_OK) return;
    do_load(w, res.target);
}

/* Returns the painted form control under (px, py), or NULL. Mirrors the layout and
 * scroll clamping of paint_structured so the hit matches what is on screen. The
 * returned block aliases the current rd_doc (not owned). */
static const rd_block *input_at_point(browser_window *w, double px, double py) {
    if (w->doc == NULL || w->cairo_surface == NULL) return NULL;

    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);
    if (py < content_top || py > content_top + content_h) return NULL;

    const ui_theme *th = &w->theme;
    double left = th->content_margin;
    double content_w = (double)w->width - 2.0 * th->content_margin;
    if (content_w < 1.0) content_w = 1.0;

    cairo_t *cr = cairo_create(w->cairo_surface);
    rc_layout L;
    layout_doc(cr, w->doc, th, content_w, &L);

    double max_scroll = L.total_h - content_h;
    if (max_scroll < 0.0) max_scroll = 0.0;
    double scroll = w->scroll;
    if (scroll < 0.0) scroll = 0.0;
    if (scroll > max_scroll) scroll = max_scroll;
    double origin = content_top + th->content_margin - scroll;

    const rd_block *hit = NULL;
    for (size_t i = 0; i < L.nrow && hit == NULL; ++i) {
        const rc_row *r = &L.rows[i];
        if (r->kind != RC_INPUT || r->blk == NULL) continue;
        double ry = origin + r->top;
        if (py < ry || py > ry + r->height) continue;
        const rd_block *b = r->blk;
        double bw = (b->input_type == PV_IN_SUBMIT || b->input_type == PV_IN_BUTTON)
                    ? button_box_width(cr, th, b, content_w)
                    : input_box_width(content_w);
        if (px >= left && px <= left + bw) hit = b;
    }

    rc_free(&L);
    cairo_destroy(cr);
    return hit;
}

/* Sends a POST submission plan through secure_fetch (re-applying the full TLS/PQ
 * policy) and renders the response in place. A redirect is followed as a GET. */
static void do_submit_post(browser_window *w, const fm_plan *plan) {
    clear_doc(w);
    w->scroll = 0.0;
    w->menu_open = 0;
    w->ua_field_focused = 0;
    w->focused_input = -1;

    sf_config cfg = sf_config_default();
    cfg.user_agent = tf_text(&w->ua_field);
    char host[256];
    if (host_from_url(plan->url, host, sizeof host) && browser_is_exception(&w->bs, host))
        cfg.policy = SF_POLICY_PERMISSIVE;

    sf_response resp;
    memset(&resp, 0, sizeof resp);
    sf_status ss = sf_post(plan->url, &cfg, plan->body, plan->body_len,
                           plan->content_type, &resp);
    if (ss != SF_OK) {
        char msg[512];
        snprintf(msg, sizeof msg, "POST to '%.400s' failed (status %d).", plan->url, (int)ss);
        set_cache(w, NULL, 0, NULL);
        browser_set_page(&w->bs, NULL, msg, 1);
        sf_response_free(&resp);
        return;
    }

    /* A POST that redirects (e.g. 303 See Other) is followed as a fresh GET, which
     * re-applies the full policy on the new target (Zero Trust). */
    if (sf_is_redirect_code(resp.http_code) && resp.location != NULL) {
        char next[SF_MAX_URL];
        if (sf_resolve_redirect(plan->url, resp.location, next, sizeof next) == SF_OK) {
            sf_response_free(&resp);
            if (browser_navigate(&w->bs, next) == BROWSER_OK) do_load(w, next);
            return;
        }
    }

    char *html = (char *)resp.body;
    size_t len = resp.body_len;
    resp.body = NULL;
    sf_response_free(&resp);
    if (html == NULL) { html = strdup(""); len = 0; }

    /* Show the POST response in place and reflect the action URL in the bar. No
     * history push: navigating back must not silently replay a POST as a GET. */
    browser_set_url_bar(&w->bs, plan->url);
    set_cache(w, html, len, plan->url);
    render_current(w);
}

/* Submits the form that owns rep (any control of the form supplies the action and
 * method). Gathers the named controls' current values, builds the plan with the
 * pure form module (fail closed to https), and dispatches GET (navigate) or POST.
 * The caller is responsible for the follow-up redraw. */
static void submit_form(browser_window *w, const rd_block *rep) {
    if (w->doc == NULL || rep == NULL) return;
    if (rep->form_id < 0) {
        browser_set_status(&w->bs, "This control is not part of a form.", now_ms());
        return;
    }

    fm_field fields[UI_FORM_FIELDS_MAX];
    size_t nf = 0;
    for (size_t i = 0; i < rd_count(w->doc) && nf < UI_FORM_FIELDS_MAX; ++i) {
        const rd_block *b = rd_at(w->doc, i);
        if (b->kind != RD_INPUT || b->form_id != rep->form_id) continue;
        if (b->name == NULL || b->name[0] == '\0') continue;
        const char *value;
        if (input_is_editable(b->input_type)) {
            ui_input_state *st = find_input_state(w, b);
            value = (st != NULL) ? tf_text(&st->field) : (b->value != NULL ? b->value : "");
        } else if (b->input_type == PV_IN_HIDDEN) {
            value = (b->value != NULL) ? b->value : "";
        } else {
            continue; /* submit/button controls are not value fields (v1) */
        }
        fields[nf].name = b->name;
        fields[nf].value = value;
        nf++;
    }

    const char *base = browser_current_url(&w->bs);
    if (base == NULL) base = ""; /* "" => fm_build blocks (no https base, fail closed) */
    fm_plan plan;
    if (fm_build(base, rep->href, (fm_method)rep->form_method, fields, nf, &plan) != FM_OK) {
        browser_set_status(&w->bs, "Could not build the form submission.", now_ms());
        return;
    }
    if (plan.kind == FM_BLOCKED) {
        const char *why = "Form blocked: insecure target (https required).";
        if (plan.reason == FM_BLOCK_OVERFLOW) why = "Form blocked: data too large.";
        else if (plan.reason == FM_BLOCK_INVALID) why = "Form blocked: invalid fields.";
        browser_set_status(&w->bs, why, now_ms());
        return;
    }
    if (plan.kind == FM_NAVIGATE) {
        if (browser_navigate(&w->bs, plan.url) == BROWSER_OK) do_load(w, plan.url);
        return;
    }
    if (plan.kind == FM_POST_REQUEST) {
        do_submit_post(w, &plan);
    }
}

/* Draws the three-bar "hamburger" icon for the options-menu button, centred in a
 * UI_BTN_W-wide button starting at bx within the toolbar. */
static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop) {
    set_rgb(cr, color);
    cairo_set_line_width(cr, 2.0);
    double cx = bx + (UI_BTN_W - UI_HAMBURGER_W) / 2.0;
    double cy = ttop + (UI_TOOLBAR_H - 2.0 * UI_HAMBURGER_GAP) / 2.0;
    for (int i = 0; i < 3; ++i) {
        double y = cy + (double)i * UI_HAMBURGER_GAP;
        cairo_move_to(cr, cx, y);
        cairo_line_to(cr, cx + UI_HAMBURGER_W, y);
        cairo_stroke(cr);
    }
}

/* Draws the options-menu panel (checkbox per capability) when open. */
static void draw_menu(cairo_t *cr, browser_window *w) {
    if (!w->menu_open) return;
    const ui_theme *th = &w->theme;
    double mx, my, mw, mh, ih;
    menu_panel_rect(w, &mx, &my, &mw, &mh, &ih);

    set_rgb(cr, th->menu_bg);
    cairo_rectangle(cr, mx, my, mw, mh);
    cairo_fill(cr);
    set_rgb(cr, th->menu_border);
    cairo_set_line_width(cr, 1.0);
    cairo_rectangle(cr, mx, my, mw, mh);
    cairo_stroke(cr);

    cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, th->body_font);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);

    for (size_t i = 0; i < UI_MENU_COUNT; ++i) {
        double row_y = my + UI_MENU_PAD + (double)i * ih;
        double box_y = row_y + (ih - UI_CHECK_SZ) / 2.0;
        double box_x = mx + UI_MENU_PAD;

        set_rgb(cr, th->check_border);
        cairo_set_line_width(cr, 1.5);
        cairo_rectangle(cr, box_x, box_y, UI_CHECK_SZ, UI_CHECK_SZ);
        cairo_stroke(cr);

        if (*menu_item_flag(w, i)) {
            set_rgb(cr, th->check_mark);
            cairo_set_line_width(cr, 2.0);
            cairo_move_to(cr, box_x + UI_CHECK_SZ * 0.2, box_y + UI_CHECK_SZ * 0.55);
            cairo_line_to(cr, box_x + UI_CHECK_SZ * 0.42, box_y + UI_CHECK_SZ * 0.78);
            cairo_line_to(cr, box_x + UI_CHECK_SZ * 0.8, box_y + UI_CHECK_SZ * 0.25);
            cairo_stroke(cr);
        }

        set_rgb(cr, th->menu_text);
        double tx = box_x + UI_CHECK_SZ + UI_MENU_PAD;
        double ty = row_y + (ih + fe.ascent - fe.descent) / 2.0;
        cairo_move_to(cr, tx, ty);
        cairo_show_text(cr, UI_MENU_ITEMS[i].label);
    }

    /* User-Agent section: a label and an editable box. The box uses a monospace
     * face for stable caret math (same convention as the URL bar). */
    double label_y = my + UI_MENU_PAD + (double)UI_MENU_COUNT * ih;
    set_rgb(cr, th->menu_text);
    cairo_move_to(cr, mx + UI_MENU_PAD, label_y + (UI_MENU_LABEL_H + fe.ascent - fe.descent) / 2.0);
    cairo_show_text(cr, "User-Agent (network):");

    double bx, by, bw, bh;
    ua_box_rect(w, &bx, &by, &bw, &bh);
    set_rgb(cr, w->ua_field_focused ? th->url_bg_focused : th->url_bg);
    cairo_rectangle(cr, bx, by, bw, bh);
    cairo_fill(cr);
    set_rgb(cr, w->ua_field_focused ? th->link : th->url_border);
    cairo_set_line_width(cr, 1.0);
    cairo_rectangle(cr, bx, by, bw, bh);
    cairo_stroke(cr);

    cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, th->body_font);
    cairo_font_extents_t mfe;
    cairo_font_extents(cr, &mfe);

    cairo_save(cr);
    cairo_rectangle(cr, bx + 2.0, by + 1.0, bw - 4.0, bh - 2.0);
    cairo_clip(cr);

    const char *ua = tf_text(&w->ua_field);
    double tx = bx + UI_MARGIN;
    double ty = by + (bh + mfe.ascent - mfe.descent) / 2.0;
    if (ua[0] == '\0' && !w->ua_field_focused) {
        set_rgb(cr, th->chrome_text_dim);
        cairo_move_to(cr, tx, ty);
        cairo_show_text(cr, SF_DEFAULT_USER_AGENT " (default)");
    } else {
        set_rgb(cr, th->menu_text);
        cairo_move_to(cr, tx, ty);
        cairo_show_text(cr, ua);
    }
    if (w->ua_field_focused) {
        double cx = tx;
        for (size_t i = 0; i < tf_cursor(&w->ua_field); ++i) {
            char tmp[2] = { ua[i], '\0' };
            cairo_text_extents_t te;
            cairo_text_extents(cr, tmp, &te);
            cx += te.x_advance;
        }
        set_rgb(cr, th->caret);
        cairo_rectangle(cr, cx, ty - mfe.ascent, 1.5, mfe.height);
        cairo_fill(cr);
    }
    cairo_restore(cr);
}

/* Draws the transient status toast (a banner at the bottom of the window). */
static void draw_toast(cairo_t *cr, browser_window *w) {
    const char *msg = browser_status_text(&w->bs, now_ms());
    if (msg == NULL) return;
    const ui_theme *th = &w->theme;

    cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, th->body_font);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    cairo_text_extents_t te;
    cairo_text_extents(cr, msg, &te);

    double bh = fe.height + 2.0 * UI_TOAST_PAD;
    double bw = te.width + 2.0 * UI_TOAST_PAD;
    double bx = UI_MARGIN;
    double by = (double)w->height - bh - UI_MARGIN;

    set_rgb(cr, th->toast_bg);
    cairo_rectangle(cr, bx, by, bw, bh);
    cairo_fill(cr);
    set_rgb(cr, th->toast_text);
    cairo_move_to(cr, bx + UI_TOAST_PAD, by + UI_TOAST_PAD + fe.ascent);
    cairo_show_text(cr, msg);
}

static void paint(browser_window *w) {
    cairo_t *cr = cairo_create(w->cairo_surface);
    const ui_theme *th = &w->theme;
    double ttop = toolbar_top(w);

    /* Background. */
    set_rgb(cr, th->window_bg);
    cairo_paint(cr);

    /* The chrome (titlebar, toolbar, URL bar) uses a monospace face for stable
     * caret math; page content is painted separately with a proportional face. */
    cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, th->body_font);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);

    /* Client-side titlebar (when the compositor offers no SSD). */
    if (w->use_csd) {
        double bl = (UI_TITLEBAR_H + fe.ascent - fe.descent) / 2.0;
        set_rgb(cr, th->titlebar_bg);
        cairo_rectangle(cr, 0, 0, w->width, UI_TITLEBAR_H);
        cairo_fill(cr);

        set_rgb(cr, th->chrome_text);
        cairo_move_to(cr, UI_MARGIN, bl);
        cairo_show_text(cr, (w->bs.page_title != NULL) ? w->bs.page_title : "Freedom");

        double min_x, max_x, close_x;
        window_button_rects(w, &min_x, &max_x, &close_x);
        set_rgb(cr, th->chrome_text);
        draw_text(cr, "_", min_x + UI_WIN_BTN_W / 2.0, bl, 1);
        draw_text(cr, "[]", max_x + UI_WIN_BTN_W / 2.0, bl, 1);
        set_rgb(cr, th->close_button);
        draw_text(cr, "X", close_x + UI_WIN_BTN_W / 2.0, bl, 1);
    }

    /* Toolbar. */
    set_rgb(cr, th->toolbar_bg);
    cairo_rectangle(cr, 0, ttop, w->width, UI_TOOLBAR_H);
    cairo_fill(cr);

    double back_x, fwd_x, url_x, url_w, go_x, menu_x;
    toolbar_rects(w, &back_x, &fwd_x, &url_x, &url_w, &go_x, &menu_x);
    double bl = ttop + (UI_TOOLBAR_H + fe.ascent - fe.descent) / 2.0;

    /* Buttons. */
    int can_back = browser_can_back(&w->bs);
    int can_fwd  = browser_can_forward(&w->bs);

    set_rgb(cr, can_back ? th->chrome_text : th->chrome_text_dim);
    draw_text(cr, "<", back_x + UI_BTN_W / 2.0, bl, 1);

    set_rgb(cr, can_fwd ? th->chrome_text : th->chrome_text_dim);
    draw_text(cr, ">", fwd_x + UI_BTN_W / 2.0, bl, 1);

    set_rgb(cr, th->chrome_text);
    draw_text(cr, "Go", go_x + UI_BTN_W / 2.0, bl, 1);

    /* Options-menu (gear) button: a three-bar icon. */
    draw_hamburger(cr, th->chrome_text, menu_x, ttop);

    /* URL bar. */
    set_rgb(cr, w->url_bar_focused ? th->url_bg_focused : th->url_bg);
    cairo_rectangle(cr, url_x, ttop + UI_MARGIN, url_w, UI_TOOLBAR_H - 2 * UI_MARGIN);
    cairo_fill(cr);

    set_rgb(cr, th->url_border);
    cairo_rectangle(cr, url_x, ttop + UI_MARGIN, url_w, UI_TOOLBAR_H - 2 * UI_MARGIN);
    cairo_stroke(cr);

    /* URL text + cursor. */
    const char *url = w->bs.url_bar;
    if (url != NULL) {
        char buf[BROWSER_URL_MAX];
        snprintf(buf, sizeof buf, "%s", url);
        cairo_text_extents_t te;
        cairo_text_extents(cr, buf, &te);
        double tx = url_x + UI_MARGIN;
        double ty = bl;

        /* Clip to URL bar interior. */
        cairo_save(cr);
        cairo_rectangle(cr, url_x + 2, ttop + UI_MARGIN + 2, url_w - 4, UI_TOOLBAR_H - 2 * UI_MARGIN - 4);
        cairo_clip(cr);

        cairo_move_to(cr, tx, ty);
        cairo_show_text(cr, buf);

        if (w->url_bar_focused) {
            /* Cursor position. */
            char left[2] = {0};
            double cx = tx;
            for (size_t i = 0; i < w->bs.url_bar_cursor && i < w->bs.url_bar_len; ++i) {
                left[0] = url[i];
                cairo_text_extents(cr, left, &te);
                cx += te.x_advance;
            }
            set_rgb(cr, th->caret);
            cairo_rectangle(cr, cx, ty - fe.ascent, 1.5, fe.height);
            cairo_fill(cr);
        }
        cairo_restore(cr);
    }

    /* Content area. */
    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);

    set_rgb(cr, th->content_bg);
    cairo_rectangle(cr, 0, content_top, w->width, (double)w->height - content_top);
    cairo_fill(cr);

    if (w->doc != NULL) {
        paint_structured(cr, w, content_top, content_h);
    } else {
        /* Plain-text fallback for the start page and error pages: monospace,
         * word-wrapped, scrolled by the same pixel offset (converted to lines). */
        const char *text = w->bs.page_text ? w->bs.page_text : "";
        size_t text_len = strlen(text);

        cairo_text_extents_t te;
        cairo_text_extents(cr, "M", &te);
        double cell_w = (te.x_advance > 0) ? te.x_advance : 8.0;
        double cell_h = (fe.height > 0) ? fe.height : th->body_font;

        size_t max_cols = (size_t)((w->width - 2 * th->content_margin) / cell_w);
        if (max_cols == 0) max_cols = 1;
        size_t viewport_lines = (size_t)(content_h / cell_h);
        if (viewport_lines == 0) viewport_lines = 1;

        ui_layout lay;
        if (ui_wrap_text(text, text_len, max_cols, &lay) == UI_OK) {
            size_t first = (size_t)(w->scroll / cell_h);
            first = ui_clamp_scroll(first, lay.count, viewport_lines);
            w->scroll = (double)first * cell_h;

            /* A line is at most max_cols columns; in UTF-8 each column is up to 4
             * bytes, so size for that and copy whole lines (ui_wrap_text already
             * breaks on character boundaries, so no byte cap can split a glyph). */
            size_t linecap = max_cols * 4 + 1;
            char *linebuf = (char *)malloc(linecap);
            if (linebuf != NULL) {
                set_rgb(cr, th->text);
                double y = content_top + th->content_margin + fe.ascent;
                for (size_t row = 0; row < viewport_lines; ++row) {
                    size_t idx = first + row;
                    if (idx >= lay.count) break;
                    size_t n = lay.lines[idx].len;
                    if (n > linecap - 1) n = linecap - 1;
                    memcpy(linebuf, text + lay.lines[idx].offset, n);
                    linebuf[n] = '\0';
                    cairo_move_to(cr, th->content_margin, y);
                    cairo_show_text(cr, linebuf);
                    y += cell_h;
                }
                free(linebuf);
            }
            ui_layout_free(&lay);
        }
    }

    /* Overlays painted on top of the content. */
    draw_menu(cr, w);
    draw_toast(cr, w);

    cairo_surface_flush(w->cairo_surface);
    cairo_destroy(cr);
}

static void redraw(browser_window *w) {
    if (!w->configured) return;
    if (ensure_buffer(w) != 0) return;
    paint(w);
    wl_surface_attach(w->surface, w->buffer, 0, 0);
    wl_surface_damage_buffer(w->surface, 0, 0, w->width, w->height);
    wl_surface_commit(w->surface);
}

/* --- xdg-shell --- */

static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial) {
    (void)data;
    xdg_wm_base_pong(b, serial);
}
static const struct xdg_wm_base_listener wm_base_listener = { wm_base_ping };

static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial) {
    browser_window *w = (browser_window *)data;
    xdg_surface_ack_configure(s, serial);
    w->configured = 1;
    redraw(w);
}
static const struct xdg_surface_listener xdg_surface_listener = { xdg_surface_configure };

static void toplevel_configure(void *data, struct xdg_toplevel *t,
                               int32_t width, int32_t height, struct wl_array *states) {
    (void)t; (void)states;
    browser_window *w = (browser_window *)data;
    if (width > 0 && height > 0) {
        w->width = width;
        w->height = height;
    }
}
static void toplevel_close(void *data, struct xdg_toplevel *t) {
    (void)t;
    ((browser_window *)data)->running = 0;
}
static const struct xdg_toplevel_listener toplevel_listener = {
    .configure = toplevel_configure,
    .close = toplevel_close,
};

static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode) {
    (void)d;
    browser_window *w = (browser_window *)data;
    w->use_csd = (mode == ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE);
    redraw(w);
}
static const struct zxdg_toplevel_decoration_v1_listener deco_listener = { deco_configure };

/* --- input --- */

/* Applies the hand (over a link) or default arrow cursor for the current pointer
 * enter serial. A no-op when no themed cursor is available (the compositor keeps
 * its own default). */
static void set_cursor(browser_window *w, int hand) {
    if (w->pointer == NULL || w->cursor_surface == NULL) return;
    struct wl_cursor *c = hand ? w->cursor_hand : w->cursor_default;
    if (c == NULL || c->image_count == 0) return;
    struct wl_cursor_image *img = c->images[0];
    struct wl_buffer *buf = wl_cursor_image_get_buffer(img);
    if (buf == NULL) return;
    wl_pointer_set_cursor(w->pointer, w->pointer_serial, w->cursor_surface,
                          (int32_t)img->hotspot_x, (int32_t)img->hotspot_y);
    wl_surface_attach(w->cursor_surface, buf, 0, 0);
    wl_surface_damage(w->cursor_surface, 0, 0, (int32_t)img->width, (int32_t)img->height);
    wl_surface_commit(w->cursor_surface);
}

/* Recomputes which link (if any) is under the pointer; on a change, updates the
 * cursor shape and repaints so the hover highlight follows. */
static void update_hover(browser_window *w) {
    const char *h = (w->doc != NULL && !w->menu_open)
                    ? link_at_point(w, w->ptr_x, w->ptr_y) : NULL;
    if (h == w->hover_href) return;
    int was = (w->hover_href != NULL);
    int now = (h != NULL);
    w->hover_href = h;
    if (was != now) set_cursor(w, now);
    redraw(w);
}

static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_surface *sf, wl_fixed_t x, wl_fixed_t y) {
    (void)p; (void)sf;
    browser_window *w = (browser_window *)d;
    w->pointer_serial = s;
    w->ptr_x = wl_fixed_to_double(x);
    w->ptr_y = wl_fixed_to_double(y);
    set_cursor(w, 0);
    update_hover(w);
}
static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf) {
    (void)p; (void)s; (void)sf;
    browser_window *w = (browser_window *)d;
    if (w->hover_href != NULL) { w->hover_href = NULL; redraw(w); }
}
static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y) {
    (void)p; (void)t;
    browser_window *w = (browser_window *)d;
    w->ptr_x = wl_fixed_to_double(x);
    w->ptr_y = wl_fixed_to_double(y);
    update_hover(w);
}

static void load_current(browser_window *w) {
    const char *url = browser_current_url(&w->bs);
    if (url != NULL) {
        browser_set_url_bar(&w->bs, url);
        do_load(w, url);
    }
}

static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
                       uint32_t button, uint32_t state) {
    (void)p; (void)serial; (void)t;
    browser_window *w = (browser_window *)d;
    if (button != UI_BTN_LEFT || state != WL_POINTER_BUTTON_STATE_PRESSED) return;

    double ttop = toolbar_top(w);

    /* While the options menu is open it captures the click: a hit on a row toggles
     * that capability and re-renders from cache (no network); any click elsewhere
     * dismisses the menu. */
    if (w->menu_open) {
        double mx, my, mw, mh, ih;
        menu_panel_rect(w, &mx, &my, &mw, &mh, &ih);
        int inside = (w->ptr_x >= mx && w->ptr_x < mx + mw
                   && w->ptr_y >= my && w->ptr_y < my + mh);
        if (inside) {
            double bx, by, bw, bh;
            ua_box_rect(w, &bx, &by, &bw, &bh);
            if (w->ptr_x >= bx && w->ptr_x < bx + bw && w->ptr_y >= by && w->ptr_y < by + bh) {
                w->ua_field_focused = 1; /* edit the User-Agent */
                w->url_bar_focused = 0;
            } else {
                w->ua_field_focused = 0;
                if (w->ptr_y >= my + UI_MENU_PAD) {
                    size_t row = (size_t)((w->ptr_y - (my + UI_MENU_PAD)) / ih);
                    if (row < UI_MENU_COUNT) {
                        bool *flag = menu_item_flag(w, row);
                        *flag = !*flag;
                        render_current(w);
                    }
                }
            }
        } else {
            w->menu_open = 0;
            w->ua_field_focused = 0;
        }
        redraw(w);
        return;
    }

    /* Client-side decoration controls. */
    if (w->use_csd && w->ptr_y < UI_TITLEBAR_H) {
        double min_x, max_x, close_x;
        window_button_rects(w, &min_x, &max_x, &close_x);
        if (w->ptr_x >= close_x) {
            w->running = 0;
            return;
        }
        (void)min_x; (void)max_x;
        return;
    }

    double back_x, fwd_x, url_x, url_w, go_x, menu_x;
    toolbar_rects(w, &back_x, &fwd_x, &url_x, &url_w, &go_x, &menu_x);

    if (w->ptr_y >= ttop && w->ptr_y < ttop + UI_TOOLBAR_H) {
        if (w->ptr_x >= menu_x) {
            w->menu_open = 1;
        } else if (w->ptr_x >= go_x && w->ptr_x < menu_x) {
            browser_commit_url_bar(&w->bs);
            load_current(w);
        } else if (w->ptr_x >= url_x && w->ptr_x < url_x + url_w) {
            w->url_bar_focused = 1;
            w->focused_input = -1; /* the URL bar takes the keyboard */
            /* Place cursor roughly by pixel offset. */
            double cx = w->ptr_x - url_x - UI_MARGIN;
            w->bs.url_bar_cursor = 0;
            cairo_t *cr = cairo_create(w->cairo_surface);
            cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
            cairo_set_font_size(cr, UI_FONT_SIZE);
            cairo_text_extents_t te;
            double acc = 0.0;
            for (size_t i = 0; i < w->bs.url_bar_len; ++i) {
                char tmp[2] = { w->bs.url_bar[i], '\0' };
                cairo_text_extents(cr, tmp, &te);
                acc += te.x_advance;
                if (acc >= cx) { w->bs.url_bar_cursor = i; break; }
                w->bs.url_bar_cursor = i + 1;
            }
            cairo_destroy(cr);
        } else if (w->ptr_x >= fwd_x && w->ptr_x < fwd_x + UI_BTN_W) {
            if (browser_forward(&w->bs) == BROWSER_OK) load_current(w);
        } else if (w->ptr_x >= back_x && w->ptr_x < back_x + UI_BTN_W) {
            if (browser_back(&w->bs) == BROWSER_OK) load_current(w);
        } else {
            w->url_bar_focused = 0;
        }
    } else {
        /* Content area. A click first hit-tests the form controls: an editable box
         * takes focus, a submit button submits its form. Otherwise a hyperlink is
         * followed (the security decision lives in the pure ln_resolve). */
        w->url_bar_focused = 0;
        w->focused_input = -1;
        const rd_block *ctl = input_at_point(w, w->ptr_x, w->ptr_y);
        if (ctl != NULL) {
            if (ctl->input_type == PV_IN_SUBMIT) {
                submit_form(w, ctl);
            } else if (input_is_editable(ctl->input_type)) {
                for (size_t i = 0; i < w->input_count; ++i) {
                    if (w->inputs[i].blk == ctl) { w->focused_input = (int)i; break; }
                }
            }
            /* PV_IN_BUTTON (reset/generic) is inert in v1. */
        } else {
            const char *href = link_at_point(w, w->ptr_x, w->ptr_y);
            if (href != NULL) follow_link(w, href);
        }
    }
    redraw(w);
}

/* One body line of scroll, in pixels (the common step unit). */
static double scroll_line_px(const browser_window *w) {
    return w->theme.body_font * w->theme.line_spacing;
}

static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32_t axis, wl_fixed_t value) {
    (void)p; (void)time;
    if (axis != WL_POINTER_AXIS_VERTICAL_SCROLL) return;
    browser_window *w = (browser_window *)data;
    if (w->ptr_y < UI_TOOLBAR_H) return;

    double v = wl_fixed_to_double(value);
    double step = w->theme.scroll_step_lines * scroll_line_px(w);
    w->scroll += (v > 0.0) ? step : -step;
    if (w->scroll < 0.0) w->scroll = 0.0; /* the upper bound is clamped during paint */
    redraw(w);
}

static const struct wl_pointer_listener pointer_listener = {
    .enter = ptr_enter,
    .leave = ptr_leave,
    .motion = ptr_motion,
    .button = ptr_button,
    .axis = ptr_axis,
};

/* --- keyboard with xkbcommon --- */

static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint32_t format, int32_t fd, uint32_t size) {
    (void)kbd;
    browser_window *w = (browser_window *)data;
    if (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) { close(fd); return; }

    char *map_str = (char *)mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (map_str == MAP_FAILED) return;

    if (w->xkb_keymap) xkb_keymap_unref(w->xkb_keymap);
    if (w->xkb_state)  xkb_state_unref(w->xkb_state);

    w->xkb_keymap = xkb_keymap_new_from_string(w->xkb_ctx, map_str,
                                               XKB_KEYMAP_FORMAT_TEXT_V1,
                                               XKB_KEYMAP_COMPILE_NO_FLAGS);
    munmap(map_str, size);
    if (w->xkb_keymap == NULL) return;
    w->xkb_state = xkb_state_new(w->xkb_keymap);
}

static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                           struct wl_surface *sf, struct wl_array *keys) {
    (void)d; (void)kbd; (void)s; (void)sf; (void)keys;
}
static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf) {
    (void)d; (void)kbd; (void)s; (void)sf;
}

static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                         uint32_t time, uint32_t key, uint32_t state) {
    (void)kbd; (void)serial; (void)time;
    browser_window *w = (browser_window *)data;
    if (state != WL_KEYBOARD_KEY_STATE_PRESSED) return;
    if (w->xkb_state == NULL) return;

    xkb_keysym_t sym = xkb_state_key_get_one_sym(w->xkb_state, key + 8);
    char utf8[16];
    int n = xkb_state_key_get_utf8(w->xkb_state, key + 8, utf8, sizeof utf8);

    int ctrl = xkb_state_mod_name_is_active(w->xkb_state, XKB_MOD_NAME_CTRL,
                                            XKB_STATE_MODS_EFFECTIVE);
    int shift = xkb_state_mod_name_is_active(w->xkb_state, XKB_MOD_NAME_SHIFT,
                                             XKB_STATE_MODS_EFFECTIVE);

    /* Ctrl+L focuses and clears the URL bar. */
    if (ctrl && !shift && (sym == XKB_KEY_l || sym == XKB_KEY_L)) {
        w->url_bar_focused = 1;
        browser_url_bar_clear(&w->bs);
        redraw(w);
        return;
    }

    /* Ctrl+Shift+E: add current host to exception list and reload insecurely. */
    if (ctrl && shift && sym == XKB_KEY_E) {
        const char *url = browser_current_url(&w->bs);
        char host[256];
        if (url != NULL && host_from_url(url, host, sizeof host)) {
            browser_add_exception(&w->bs, host);
            load_current(w);
        }
        return;
    }

    /* Ctrl+I toggles loading remote images for this session (Privacy by Default:
     * off), the same capability the options menu exposes. Re-renders from the
     * cached source (no network) so the tracking warning and the per-image
     * placeholders update to the new posture. */
    if (ctrl && !shift && (sym == XKB_KEY_i || sym == XKB_KEY_I)) {
        w->caps.images = !w->caps.images;
        render_current(w);
        redraw(w);
        return;
    }

    /* Editing the configurable User-Agent in the options menu takes priority over
     * the URL bar and page scroll. Enter applies it (used on the next load). */
    if (w->ua_field_focused) {
        if (sym == XKB_KEY_Escape) {
            w->ua_field_focused = 0;
        } else if (sym == XKB_KEY_Return || sym == XKB_KEY_KP_Enter) {
            w->ua_field_focused = 0;
            browser_set_status(&w->bs, "User-Agent set; reload to apply.", now_ms());
        } else if (sym == XKB_KEY_BackSpace) {
            tf_backspace(&w->ua_field);
        } else if (sym == XKB_KEY_Delete || sym == XKB_KEY_KP_Delete) {
            tf_delete(&w->ua_field);
        } else if (sym == XKB_KEY_Left) {
            tf_move(&w->ua_field, -1);
        } else if (sym == XKB_KEY_Right) {
            tf_move(&w->ua_field, 1);
        } else if (sym == XKB_KEY_Home) {
            tf_home(&w->ua_field);
        } else if (sym == XKB_KEY_End) {
            tf_end(&w->ua_field);
        } else if (n > 0) {
            for (int i = 0; i < n; ++i) tf_insert(&w->ua_field, utf8[i]);
        }
        redraw(w);
        return;
    }

    /* A focused page text control (e.g. a search box) captures the keyboard before
     * scroll: typing edits its live value, Enter submits the owning form (the load
     * re-applies the full TLS/PQ policy, Zero Trust), Escape releases focus. Same
     * edit mechanics as the URL bar and the User-Agent box, over the shared
     * textfield primitive. submit_form may reload and rebuild w->inputs, so the
     * block is captured and focus dropped before calling it. */
    if (w->focused_input >= 0 && (size_t)w->focused_input < w->input_count) {
        tf_field *field = &w->inputs[w->focused_input].field;
        if (sym == XKB_KEY_Escape) {
            w->focused_input = -1;
        } else if (sym == XKB_KEY_Return || sym == XKB_KEY_KP_Enter) {
            const rd_block *blk = w->inputs[w->focused_input].blk;
            w->focused_input = -1;
            submit_form(w, blk);
        } else if (sym == XKB_KEY_BackSpace) {
            tf_backspace(field);
        } else if (sym == XKB_KEY_Delete || sym == XKB_KEY_KP_Delete) {
            tf_delete(field);
        } else if (sym == XKB_KEY_Left) {
            tf_move(field, -1);
        } else if (sym == XKB_KEY_Right) {
            tf_move(field, 1);
        } else if (sym == XKB_KEY_Home) {
            tf_home(field);
        } else if (sym == XKB_KEY_End) {
            tf_end(field);
        } else if (n > 0 && (unsigned char)utf8[0] >= 0x20) {
            for (int i = 0; i < n; ++i) tf_insert(field, utf8[i]);
        }
        redraw(w);
        return;
    }

    if (!w->url_bar_focused) {
        double line = scroll_line_px(w);
        if (sym == XKB_KEY_Up) { w->scroll -= line; }
        else if (sym == XKB_KEY_Down) { w->scroll += line; }
        else if (sym == XKB_KEY_Page_Up) { w->scroll -= w->theme.page_step_lines * line; }
        else if (sym == XKB_KEY_Page_Down) { w->scroll += w->theme.page_step_lines * line; }
        if (w->scroll < 0.0) w->scroll = 0.0;
        redraw(w);
        return;
    }

    if (sym == XKB_KEY_Escape) {
        w->url_bar_focused = 0;
    } else if (sym == XKB_KEY_Return || sym == XKB_KEY_KP_Enter) {
        browser_commit_url_bar(&w->bs);
        load_current(w);
        w->url_bar_focused = 0;
    } else if (sym == XKB_KEY_BackSpace) {
        browser_url_bar_backspace(&w->bs);
    } else if (sym == XKB_KEY_Delete || sym == XKB_KEY_KP_Delete) {
        browser_url_bar_delete(&w->bs);
    } else if (sym == XKB_KEY_Left) {
        browser_url_bar_move_cursor(&w->bs, -1);
    } else if (sym == XKB_KEY_Right) {
        browser_url_bar_move_cursor(&w->bs, 1);
    } else if (sym == XKB_KEY_Home) {
        w->bs.url_bar_cursor = 0;
    } else if (sym == XKB_KEY_End) {
        w->bs.url_bar_cursor = w->bs.url_bar_len;
    } else if (n > 0) {
        for (int i = 0; i < n; ++i) {
            browser_url_bar_insert(&w->bs, utf8[i]);
        }
    }
    redraw(w);
}

static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                               uint32_t mods_depressed, uint32_t mods_latched,
                               uint32_t mods_locked, uint32_t group) {
    (void)kbd; (void)s;
    browser_window *w = (browser_window *)data;
    if (w->xkb_state) {
        xkb_state_update_mask(w->xkb_state, mods_depressed, mods_latched, mods_locked, 0, 0, group);
    }
}
static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay) {
    (void)d; (void)kbd; (void)rate; (void)delay;
}

static const struct wl_keyboard_listener keyboard_listener = {
    .keymap = keyboard_keymap,
    .enter = keyboard_enter,
    .leave = keyboard_leave,
    .key = keyboard_key,
    .modifiers = keyboard_modifiers,
    .repeat_info = keyboard_repeat_info,
};

/* --- seat --- */

static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps) {
    browser_window *w = (browser_window *)data;
    if ((caps & WL_SEAT_CAPABILITY_POINTER) && w->pointer == NULL) {
        w->pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(w->pointer, &pointer_listener, w);
    }
    if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) && w->keyboard == NULL) {
        w->keyboard = wl_seat_get_keyboard(seat);
        wl_keyboard_add_listener(w->keyboard, &keyboard_listener, w);
    }
}
static void seat_name(void *d, struct wl_seat *s, const char *name) {
    (void)d; (void)s; (void)name;
}
static const struct wl_seat_listener seat_listener = { seat_caps, seat_name };

/* --- registry --- */

static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                            const char *iface, uint32_t version) {
    (void)version;
    browser_window *w = (browser_window *)data;
    if (strcmp(iface, wl_compositor_interface.name) == 0) {
        w->compositor = wl_registry_bind(reg, name, &wl_compositor_interface, 4);
    } else if (strcmp(iface, wl_shm_interface.name) == 0) {
        w->shm = wl_registry_bind(reg, name, &wl_shm_interface, 1);
    } else if (strcmp(iface, xdg_wm_base_interface.name) == 0) {
        w->wm_base = wl_registry_bind(reg, name, &xdg_wm_base_interface, 1);
        xdg_wm_base_add_listener(w->wm_base, &wm_base_listener, w);
    } else if (strcmp(iface, wl_seat_interface.name) == 0) {
        w->seat = wl_registry_bind(reg, name, &wl_seat_interface, 1);
        wl_seat_add_listener(w->seat, &seat_listener, w);
    } else if (strcmp(iface, zxdg_decoration_manager_v1_interface.name) == 0) {
        w->deco_mgr = wl_registry_bind(reg, name, &zxdg_decoration_manager_v1_interface, 1);
    }
}
static void registry_remove(void *d, struct wl_registry *r, uint32_t name) {
    (void)d; (void)r; (void)name;
}
static const struct wl_registry_listener registry_listener = {
    .global = registry_global,
    .global_remove = registry_remove,
};

/* --- public API --- */

ui_status ui_run_browser(const char *start_url) {
    browser_window w;
    memset(&w, 0, sizeof w);
    w.width = 900;
    w.height = 700;
    w.running = 1;
    w.use_csd = 1;
    w.theme = ui_theme_default();
    w.caps = rdp_caps_safe();   /* Privacy by Default: images/CSS/JS off */
    w.scroll = 0.0;
    w.focused_input = -1;       /* no form control focused */
    tf_init(&w.ua_field);       /* empty => SF_DEFAULT_USER_AGENT */

    if (browser_init(&w.bs) != BROWSER_OK) return UI_ERR_OOM;

    if (start_url != NULL) {
        browser_navigate(&w.bs, start_url);
    }

    w.xkb_ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    if (w.xkb_ctx == NULL) { browser_free(&w.bs); return UI_ERR_OOM; }

    w.display = wl_display_connect(NULL);
    if (w.display == NULL) { browser_free(&w.bs); xkb_context_unref(w.xkb_ctx); return UI_ERR_DISPLAY; }

    w.registry = wl_display_get_registry(w.display);
    wl_registry_add_listener(w.registry, &registry_listener, &w);
    wl_display_roundtrip(w.display);

    if (w.compositor == NULL || w.shm == NULL || w.wm_base == NULL) {
        wl_display_disconnect(w.display);
        browser_free(&w.bs);
        xkb_context_unref(w.xkb_ctx);
        return UI_ERR_INTERNAL;
    }

    w.surface = wl_compositor_create_surface(w.compositor);
    w.xdg_surface = xdg_wm_base_get_xdg_surface(w.wm_base, w.surface);
    xdg_surface_add_listener(w.xdg_surface, &xdg_surface_listener, &w);
    w.xdg_toplevel = xdg_surface_get_toplevel(w.xdg_surface);
    xdg_toplevel_add_listener(w.xdg_toplevel, &toplevel_listener, &w);
    xdg_toplevel_set_title(w.xdg_toplevel, "Freedom");
    xdg_toplevel_set_app_id(w.xdg_toplevel, "org.freedom.browser");

    w.use_csd = 1;
    if (w.deco_mgr != NULL) {
        w.deco = zxdg_decoration_manager_v1_get_toplevel_decoration(w.deco_mgr, w.xdg_toplevel);
        zxdg_toplevel_decoration_v1_add_listener(w.deco, &deco_listener, &w);
        zxdg_toplevel_decoration_v1_set_mode(w.deco,
            ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE);
    }

    /* Themed cursors: a hand over links, the default arrow elsewhere. Best-effort
     * from the system theme (no absolute paths); if unavailable the compositor's
     * own default cursor is used. */
    w.cursor_theme = wl_cursor_theme_load(NULL, UI_CURSOR_SIZE, w.shm);
    if (w.cursor_theme != NULL) {
        w.cursor_default = wl_cursor_theme_get_cursor(w.cursor_theme, "left_ptr");
        w.cursor_hand = wl_cursor_theme_get_cursor(w.cursor_theme, "pointer");
        if (w.cursor_hand == NULL) w.cursor_hand = wl_cursor_theme_get_cursor(w.cursor_theme, "hand2");
        if (w.cursor_hand == NULL) w.cursor_hand = wl_cursor_theme_get_cursor(w.cursor_theme, "hand1");
    }
    w.cursor_surface = wl_compositor_create_surface(w.compositor);

    wl_surface_commit(w.surface);

    /* Initial page. Provide instructions because the strict TLS policy means
       many public sites will be rejected. */
    if (start_url != NULL) {
        do_load(&w, start_url);
    } else {
        browser_set_page(&w.bs, "Freedom",
            "Freedom browser\n\n"
            "Click the URL bar, type an address, and press Enter or click Go.\n"
            "Allowed URLs:\n"
            "  - https://<site>   (TLS 1.3, PQ-hybrid KE, leaf RSA >= 3072 / ECDSA)\n"
            "  - /path/file.html  (local file)\n"
            "\n"
            "Pages render with structure (headings, links, paragraphs) and you can\n"
            "click links to navigate. Remote images and author colors are off by\n"
            "default (Privacy by Default); the menu button at the top right toggles\n"
            "them (or Ctrl+I for images). A page that uses images shows a tracking\n"
            "warning and a placeholder per image. Ctrl+L focuses the URL bar.\n"
            "\n"
            "Sites whose end-entity certificate uses RSA 2048 are rejected with\n"
            "status 5 (weak algorithm). This is fail-closed by design.", 0);
    }

    /* Make the URL bar ready for typing. */
    w.url_bar_focused = 1;
    browser_url_bar_clear(&w.bs);

    /* Event loop using the prepare_read/read_events pattern so a poll timeout can
     * fire the toast's auto-hide without racing the Wayland queue. The timeout is
     * the remaining lifetime of an active toast, or infinite when there is none. */
    while (w.running) {
        while (wl_display_prepare_read(w.display) != 0) {
            wl_display_dispatch_pending(w.display);
        }
        wl_display_flush(w.display);

        uint64_t t = now_ms();
        int timeout = -1;
        if (browser_status_text(&w.bs, t) != NULL) {
            uint64_t exp = w.bs.status_expiry_ms;
            timeout = (exp > t) ? (int)(exp - t) : 0;
        }

        struct pollfd pfd = { .fd = wl_display_get_fd(w.display), .events = POLLIN, .revents = 0 };
        int pr = poll(&pfd, 1, timeout);
        if (pr > 0 && (pfd.revents & POLLIN)) {
            if (wl_display_read_events(w.display) == -1) break;
            if (wl_display_dispatch_pending(w.display) == -1) break;
        } else {
            wl_display_cancel_read(w.display);
            if (pr == 0) redraw(&w);            /* toast expired: repaint to clear it */
            else if (pr > 0) break;             /* POLLHUP/POLLERR: the display is gone */
            else if (errno != EINTR) break;     /* a real poll error */
        }
    }

    destroy_buffer(&w);
    if (w.deco) zxdg_toplevel_decoration_v1_destroy(w.deco);
    if (w.deco_mgr) zxdg_decoration_manager_v1_destroy(w.deco_mgr);
    if (w.xdg_toplevel) xdg_toplevel_destroy(w.xdg_toplevel);
    if (w.xdg_surface) xdg_surface_destroy(w.xdg_surface);
    if (w.surface) wl_surface_destroy(w.surface);
    if (w.keyboard) wl_keyboard_destroy(w.keyboard);
    if (w.pointer) wl_pointer_destroy(w.pointer);
    if (w.seat) wl_seat_destroy(w.seat);
    if (w.cursor_surface) wl_surface_destroy(w.cursor_surface);
    if (w.cursor_theme) wl_cursor_theme_destroy(w.cursor_theme);
    if (w.wm_base) xdg_wm_base_destroy(w.wm_base);
    if (w.shm) wl_shm_destroy(w.shm);
    if (w.compositor) wl_compositor_destroy(w.compositor);
    if (w.registry) wl_registry_destroy(w.registry);
    wl_display_disconnect(w.display);

    if (w.xkb_keymap) xkb_keymap_unref(w.xkb_keymap);
    if (w.xkb_state) xkb_state_unref(w.xkb_state);
    xkb_context_unref(w.xkb_ctx);

    clear_doc(&w);
    free(w.cur_html);
    free(w.cur_top);
    browser_free(&w.bs);

    /* Release the process-wide font caches so a leak checker sees a clean exit.
     * Cairo holds FcPattern references in its static font cache; drop those
     * first, then let fontconfig free its global config. All cairo objects have
     * already been destroyed above, so this is safe. */
    cairo_debug_reset_static_data();
    FcFini();
    return UI_OK;
}
