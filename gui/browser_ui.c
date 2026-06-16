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
#include "ui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

#include <wayland-client.h>
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

    /* xkbcommon state for keyboard input. */
    struct xkb_context *xkb_ctx;
    struct xkb_keymap  *xkb_keymap;
    struct xkb_state   *xkb_state;
} browser_window;

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

#include "secure_fetch.h"
#include "tab.h"

static void do_load(browser_window *w, const char *url) {
    if (url == NULL) return;

    if (strcmp(url, "about:blank") == 0) {
        browser_set_page(&w->bs, "Freedom", "", 0);
        return;
    }

    char *html = NULL;
    size_t html_len = 0;

    if (is_https_url(url)) {
        sf_config cfg = sf_config_default();
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
            browser_set_page(&w->bs, NULL, msg, 1);
            return;
        }
    }

    tab *t = NULL;
    tab_status ts = tab_open(&t);
    if (ts != TAB_OK) {
        browser_set_page(&w->bs, NULL, "Failed to spawn sandboxed tab.", 1);
        free(html);
        return;
    }

    tab_page page;
    memset(&page, 0, sizeof page);
    ts = tab_load(t, html, html_len, &page);
    if (ts != TAB_OK) {
        browser_set_page(&w->bs, NULL, "Failed to render page in sandbox.", 1);
        tab_close(t);
        free(html);
        return;
    }

    browser_set_page(&w->bs, page.title, page.text, 0);
    tab_page_free(&page);
    tab_close(t);
    free(html);
}

/* --- painting --- */

static void toolbar_rects(const browser_window *w,
                          double *back_x, double *fwd_x,
                          double *url_x, double *url_w,
                          double *go_x);

static double toolbar_top(const browser_window *w) {
    return w->use_csd ? UI_TITLEBAR_H : 0.0;
}

static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *close_x) {
    *close_x = w->width - UI_WIN_BTN_W;
    *max_x   = w->width - 2 * UI_WIN_BTN_W;
    *min_x   = w->width - 3 * UI_WIN_BTN_W;
}

static void toolbar_rects(const browser_window *w,
                          double *back_x, double *fwd_x,
                          double *url_x, double *url_w,
                          double *go_x) {
    *back_x = 0.0;
    *fwd_x  = UI_BTN_W;
    *go_x   = (double)w->width - UI_BTN_W;
    *url_x  = UI_BTN_W * 2.0 + UI_MARGIN;
    *url_w  = *go_x - *url_x - UI_MARGIN;
    if (*url_w < 20.0) *url_w = 20.0;
}

static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered) {
    if (s == NULL) return;
    cairo_text_extents_t te;
    cairo_text_extents(cr, s, &te);
    double dx = centered ? x - te.width / 2.0 : x;
    cairo_move_to(cr, dx, y);
    cairo_show_text(cr, s);
}

static void paint(browser_window *w) {
    cairo_t *cr = cairo_create(w->cairo_surface);
    double ttop = toolbar_top(w);

    /* Background. */
    cairo_set_source_rgb(cr, 0.96, 0.96, 0.96);
    cairo_paint(cr);

    cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, UI_FONT_SIZE);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);

    /* Client-side titlebar (when the compositor offers no SSD). */
    if (w->use_csd) {
        double bl = (UI_TITLEBAR_H + fe.ascent - fe.descent) / 2.0;
        cairo_set_source_rgb(cr, 0.12, 0.12, 0.14);
        cairo_rectangle(cr, 0, 0, w->width, UI_TITLEBAR_H);
        cairo_fill(cr);

        cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);
        cairo_move_to(cr, UI_MARGIN, bl);
        cairo_show_text(cr, (w->bs.page_title != NULL) ? w->bs.page_title : "Freedom");

        double min_x, max_x, close_x;
        window_button_rects(w, &min_x, &max_x, &close_x);
        cairo_set_source_rgb(cr, 0.85, 0.85, 0.85);
        draw_text(cr, "_", min_x + UI_WIN_BTN_W / 2.0, bl, 1);
        draw_text(cr, "[]", max_x + UI_WIN_BTN_W / 2.0, bl, 1);
        cairo_set_source_rgb(cr, 1.0, 0.55, 0.55);
        draw_text(cr, "X", close_x + UI_WIN_BTN_W / 2.0, bl, 1);
    }

    /* Toolbar. */
    cairo_set_source_rgb(cr, 0.22, 0.23, 0.25);
    cairo_rectangle(cr, 0, ttop, w->width, UI_TOOLBAR_H);
    cairo_fill(cr);

    double back_x, fwd_x, url_x, url_w, go_x;
    toolbar_rects(w, &back_x, &fwd_x, &url_x, &url_w, &go_x);
    double bl = ttop + (UI_TOOLBAR_H + fe.ascent - fe.descent) / 2.0;

    /* Buttons. */
    int can_back = browser_can_back(&w->bs);
    int can_fwd  = browser_can_forward(&w->bs);

    cairo_set_source_rgb(cr, can_back ? 0.85 : 0.45, can_back ? 0.85 : 0.45, can_back ? 0.85 : 0.45);
    draw_text(cr, "<", back_x + UI_BTN_W / 2.0, bl, 1);

    cairo_set_source_rgb(cr, can_fwd ? 0.85 : 0.45, can_fwd ? 0.85 : 0.45, can_fwd ? 0.85 : 0.45);
    draw_text(cr, ">", fwd_x + UI_BTN_W / 2.0, bl, 1);

    cairo_set_source_rgb(cr, 0.85, 0.85, 0.85);
    draw_text(cr, "Go", go_x + UI_BTN_W / 2.0, bl, 1);

    /* URL bar. */
    if (w->url_bar_focused) {
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    } else {
        cairo_set_source_rgb(cr, 0.92, 0.92, 0.92);
    }
    cairo_rectangle(cr, url_x, ttop + UI_MARGIN, url_w, UI_TOOLBAR_H - 2 * UI_MARGIN);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
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
            cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
            cairo_rectangle(cr, cx, ty - fe.ascent, 1.5, fe.height);
            cairo_fill(cr);
        }
        cairo_restore(cr);
    }

    /* Content area. */
    double content_top = ttop + UI_TOOLBAR_H;
    double content_h = (double)w->height - content_top - 2 * UI_TEXT_MARGIN;
    if (content_h < 1.0) content_h = 1.0;

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_rectangle(cr, 0, content_top, w->width, (double)w->height - content_top);
    cairo_fill(cr);

    const char *text = w->bs.page_text;
    if (text == NULL) text = "";
    size_t text_len = w->bs.page_text ? strlen(w->bs.page_text) : 0;

    cairo_text_extents_t te;
    cairo_text_extents(cr, "M", &te);
    double cell_w = (te.x_advance > 0) ? te.x_advance : 8.0;
    double cell_h = (fe.height > 0) ? fe.height : UI_FONT_SIZE;

    size_t max_cols = (size_t)((w->width - 2 * UI_TEXT_MARGIN) / cell_w);
    if (max_cols == 0) max_cols = 1;
    size_t viewport_lines = (size_t)(content_h / cell_h);
    if (viewport_lines == 0) viewport_lines = 1;

    static size_t scroll = 0;

    ui_layout lay;
    if (ui_wrap_text(text, text_len, max_cols, &lay) == UI_OK) {
        scroll = ui_clamp_scroll(scroll, lay.count, viewport_lines);

        /* A line is at most max_cols columns; in UTF-8 each column is up to 4
         * bytes, so size for that and copy whole lines (ui_wrap_text already
         * breaks on character boundaries, so no byte cap can split a glyph). */
        size_t linecap = max_cols * 4 + 1;
        char *linebuf = (char *)malloc(linecap);
        if (linebuf != NULL) {
            cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
            double y = content_top + UI_TEXT_MARGIN + fe.ascent;
            for (size_t row = 0; row < viewport_lines; ++row) {
                size_t idx = scroll + row;
                if (idx >= lay.count) break;
                size_t n = lay.lines[idx].len;
                if (n > linecap - 1) n = linecap - 1;
                memcpy(linebuf, text + lay.lines[idx].offset, n);
                linebuf[n] = '\0';
                cairo_move_to(cr, UI_TEXT_MARGIN, y);
                cairo_show_text(cr, linebuf);
                y += cell_h;
            }
            free(linebuf);
        }
        ui_layout_free(&lay);
    }

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

static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_surface *sf, wl_fixed_t x, wl_fixed_t y) {
    (void)p; (void)s; (void)sf;
    browser_window *w = (browser_window *)d;
    w->ptr_x = wl_fixed_to_double(x);
    w->ptr_y = wl_fixed_to_double(y);
}
static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf) {
    (void)d; (void)p; (void)s; (void)sf;
}
static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y) {
    (void)p; (void)t;
    browser_window *w = (browser_window *)d;
    w->ptr_x = wl_fixed_to_double(x);
    w->ptr_y = wl_fixed_to_double(y);
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

    double back_x, fwd_x, url_x, url_w, go_x;
    toolbar_rects(w, &back_x, &fwd_x, &url_x, &url_w, &go_x);

    if (w->ptr_y >= ttop && w->ptr_y < ttop + UI_TOOLBAR_H) {
        if (w->ptr_x >= go_x) {
            browser_commit_url_bar(&w->bs);
            load_current(w);
        } else if (w->ptr_x >= url_x && w->ptr_x < url_x + url_w) {
            w->url_bar_focused = 1;
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
        w->url_bar_focused = 0;
    }
    redraw(w);
}

static size_t *global_scroll_ptr(void) {
    static size_t scroll = 0;
    return &scroll;
}

static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32_t axis, wl_fixed_t value) {
    (void)p; (void)time;
    if (axis != WL_POINTER_AXIS_VERTICAL_SCROLL) return;
    browser_window *w = (browser_window *)data;
    if (w->ptr_y < UI_TOOLBAR_H) return;

    size_t *scroll = global_scroll_ptr();
    double v = wl_fixed_to_double(value);
    long step = (v > 0) ? 3 : -3;
    if (step < 0 && *scroll < (size_t)(-step)) {
        *scroll = 0;
    } else {
        *scroll = (size_t)((long)*scroll + step);
    }
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

    if (!w->url_bar_focused) {
        size_t *scroll = global_scroll_ptr();
        if (sym == XKB_KEY_Up) { if (*scroll > 0) (*scroll)--; }
        else if (sym == XKB_KEY_Down) { (*scroll)++; }
        else if (sym == XKB_KEY_Page_Up) { if (*scroll > 9) *scroll -= 10; else *scroll = 0; }
        else if (sym == XKB_KEY_Page_Down) { *scroll += 10; }
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
            "Sites whose end-entity certificate uses RSA 2048 are rejected with\n"
            "status 5 (weak algorithm). This is fail-closed by design.", 0);
    }

    /* Make the URL bar ready for typing. */
    w.url_bar_focused = 1;
    browser_url_bar_clear(&w.bs);

    while (w.running && wl_display_dispatch(w.display) != -1) {
        /* events drive redraw */
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
    if (w.wm_base) xdg_wm_base_destroy(w.wm_base);
    if (w.shm) wl_shm_destroy(w.shm);
    if (w.compositor) wl_compositor_destroy(w.compositor);
    if (w.registry) wl_registry_destroy(w.registry);
    wl_display_disconnect(w.display);

    if (w.xkb_keymap) xkb_keymap_unref(w.xkb_keymap);
    if (w.xkb_state) xkb_state_unref(w.xkb_state);
    xkb_context_unref(w.xkb_ctx);

    browser_free(&w.bs);

    /* Release the process-wide font caches so a leak checker sees a clean exit.
     * Cairo holds FcPattern references in its static font cache; drop those
     * first, then let fontconfig free its global config. All cairo objects have
     * already been destroyed above, so this is safe. */
    cairo_debug_reset_static_data();
    FcFini();
    return UI_OK;
}
