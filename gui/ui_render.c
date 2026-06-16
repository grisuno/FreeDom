/*
 * ui_render — Wayland + Cairo orchestrator (visual; not unit-tested headless).
 *
 * Thin glue: connects to Wayland, creates an xdg-shell window with a wl_shm
 * buffer wrapped in a Cairo surface, and paints the visible, word-wrapped lines
 * computed by the pure core (ui_layout). Scroll via pointer axis; resize and
 * close handled. Wayland only, never X11.
 */

#define _GNU_SOURCE

#include "ui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include <wayland-client.h>
#include <cairo/cairo.h>

#include "xdg-shell-client-protocol.h"
#include "xdg-decoration-client-protocol.h"

#define UI_FONT_SIZE  16.0
#define UI_MARGIN     8.0
#define UI_TITLEBAR_H 30.0   /* client-side titlebar height */
#define UI_BTN_W      30.0   /* min/max/close button width */
#define UI_BTN_LEFT   0x110  /* BTN_LEFT from linux/input-event-codes.h */

/* Rewrites s in place to well-formed UTF-8, replacing any byte that is not part
 * of a valid sequence with '?'. cairo_show_text rejects invalid UTF-8 and then
 * silently stops drawing, so a single bad byte (e.g. a Latin-1 page) would blank
 * the rest of the frame. Mirrors browser.c's sanitizer for the freedom-view tool,
 * which does not route text through browser_set_page. Output length <= input. */
static void sanitize_utf8_inplace(char *s) {
    size_t n = strlen(s);
    size_t i = 0, o = 0;
    while (i < n) {
        unsigned char c = (unsigned char)s[i];
        size_t L = (c < 0x80) ? 1
                 : (c >= 0xC2 && c <= 0xDF) ? 2
                 : (c >= 0xE0 && c <= 0xEF) ? 3
                 : (c >= 0xF0 && c <= 0xF4) ? 4 : 0;
        int ok = (L >= 1 && i + L <= n);
        for (size_t k = 1; ok && k < L; ++k) {
            if (((unsigned char)s[i + k] & 0xC0) != 0x80) ok = 0;
        }
        if (ok && L == 3 && c == 0xE0 && (unsigned char)s[i + 1] < 0xA0) ok = 0;
        if (ok && L == 3 && c == 0xED && (unsigned char)s[i + 1] > 0x9F) ok = 0;
        if (ok && L == 4 && c == 0xF0 && (unsigned char)s[i + 1] < 0x90) ok = 0;
        if (ok && L == 4 && c == 0xF4 && (unsigned char)s[i + 1] > 0x8F) ok = 0;
        if (ok) {
            for (size_t k = 0; k < L; ++k) s[o++] = s[i + k];
            i += L;
        } else {
            s[o++] = '?';
            i += 1;
        }
    }
    s[o] = '\0';
}

typedef struct ui_window {
    struct wl_display    *display;
    struct wl_registry   *registry;
    struct wl_compositor *compositor;
    struct wl_shm        *shm;
    struct xdg_wm_base   *wm_base;
    struct wl_seat       *seat;
    struct wl_pointer    *pointer;

    struct wl_surface    *surface;
    struct xdg_surface   *xdg_surface;
    struct xdg_toplevel  *xdg_toplevel;

    int  width, height;
    int  configured;
    int  running;
    int  need_redraw;

    struct wl_buffer *buffer;
    void             *shm_data;
    size_t            shm_size;
    int               buffer_busy;
    cairo_surface_t  *cairo_surface;

    struct zxdg_decoration_manager_v1   *deco_mgr;
    struct zxdg_toplevel_decoration_v1  *deco;

    int    use_csd;    /* draw our own titlebar/controls (compositor has no SSD) */
    int    maximized;
    double ptr_x, ptr_y;

    const char *title;
    const char *text;
    size_t      text_len;
    size_t      scroll; /* first visible line */
} ui_window;

static void redraw(ui_window *w);

/* Right-aligned control buttons: minimize, maximize, close. */
static void button_rects(const ui_window *w, double *min_x, double *max_x, double *close_x) {
    *close_x = w->width - UI_BTN_W;
    *max_x   = w->width - 2 * UI_BTN_W;
    *min_x   = w->width - 3 * UI_BTN_W;
}

/* --- shm buffer --- */

static void buffer_release(void *data, struct wl_buffer *wl_buffer) {
    (void)wl_buffer;
    ((ui_window *)data)->buffer_busy = 0;
}

static const struct wl_buffer_listener buffer_listener = { buffer_release };

static void destroy_buffer(ui_window *w) {
    if (w->cairo_surface) { cairo_surface_destroy(w->cairo_surface); w->cairo_surface = NULL; }
    if (w->buffer) { wl_buffer_destroy(w->buffer); w->buffer = NULL; }
    if (w->shm_data) { munmap(w->shm_data, w->shm_size); w->shm_data = NULL; w->shm_size = 0; }
}

static int ensure_buffer(ui_window *w) {
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
    w->buffer = wl_shm_pool_create_buffer(pool, 0, w->width, w->height, stride,
                                          WL_SHM_FORMAT_ARGB8888);
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

/* --- painting --- */

static void paint(ui_window *w) {
    cairo_t *cr = cairo_create(w->cairo_surface);

    cairo_set_source_rgb(cr, 1, 1, 1); /* white background */
    cairo_paint(cr);

    cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, UI_FONT_SIZE);

    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    cairo_text_extents_t te;
    cairo_text_extents(cr, "M", &te);

    double cell_w = (te.x_advance > 0) ? te.x_advance : (fe.max_x_advance > 0 ? fe.max_x_advance : 8.0);
    double cell_h = (fe.height > 0) ? fe.height : UI_FONT_SIZE;

    double content_top = w->use_csd ? UI_TITLEBAR_H : 0.0;

    /* Client-side titlebar + window controls (when the compositor offers no SSD). */
    if (w->use_csd) {
        double bl = (UI_TITLEBAR_H + fe.ascent - fe.descent) / 2.0; /* baseline */
        cairo_set_source_rgb(cr, 0.15, 0.15, 0.18);
        cairo_rectangle(cr, 0, 0, w->width, UI_TITLEBAR_H);
        cairo_fill(cr);

        cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);
        cairo_move_to(cr, UI_MARGIN, bl);
        cairo_show_text(cr, (w->title != NULL) ? w->title : "Freedom");

        double min_x, max_x, close_x;
        button_rects(w, &min_x, &max_x, &close_x);
        cairo_set_source_rgb(cr, 0.85, 0.85, 0.85);
        cairo_move_to(cr, min_x + UI_BTN_W / 2 - cell_w / 2, bl);
        cairo_show_text(cr, "_");
        cairo_move_to(cr, max_x + UI_BTN_W / 2 - cell_w, bl);
        cairo_show_text(cr, "[]");
        cairo_set_source_rgb(cr, 1.0, 0.55, 0.55);
        cairo_move_to(cr, close_x + UI_BTN_W / 2 - cell_w / 2, bl);
        cairo_show_text(cr, "X");
    }

    size_t max_cols = (size_t)((w->width - 2 * UI_MARGIN) / cell_w);
    if (max_cols == 0) max_cols = 1;
    double content_h = (double)w->height - content_top - 2 * UI_MARGIN;
    size_t viewport_lines = (content_h > 0) ? (size_t)(content_h / cell_h) : 1;
    if (viewport_lines == 0) viewport_lines = 1;

    ui_layout lay;
    if (ui_wrap_text(w->text, w->text_len, max_cols, &lay) != UI_OK) {
        cairo_destroy(cr);
        return;
    }

    w->scroll = ui_clamp_scroll(w->scroll, lay.count, viewport_lines);

    fprintf(stderr, "[ui] paint csd=%d cols=%zu viewport=%zu total_lines=%zu scroll=%zu\n",
            w->use_csd, max_cols, viewport_lines, lay.count, w->scroll);

    /* A line is <= max_cols columns; in UTF-8 a column is up to 4 bytes. */
    size_t linecap = max_cols * 4 + 1;
    char *linebuf = (char *)malloc(linecap);
    if (linebuf != NULL) {
        cairo_set_source_rgb(cr, 0.1, 0.1, 0.1); /* near-black text */
        double y = content_top + UI_MARGIN + fe.ascent;
        for (size_t row = 0; row < viewport_lines; ++row) {
            size_t idx = w->scroll + row;
            if (idx >= lay.count) break;
            size_t n = lay.lines[idx].len;
            if (n > linecap - 1) n = linecap - 1;
            memcpy(linebuf, w->text + lay.lines[idx].offset, n);
            linebuf[n] = '\0';
            sanitize_utf8_inplace(linebuf);
            cairo_move_to(cr, UI_MARGIN, y);
            cairo_show_text(cr, linebuf);
            y += cell_h;
        }
        free(linebuf);
    }

    ui_layout_free(&lay);
    cairo_surface_flush(w->cairo_surface);
    cairo_destroy(cr);
}

static void redraw(ui_window *w) {
    if (!w->configured) return;
    if (ensure_buffer(w) != 0) return;

    /* Always repaint and re-commit. We do not gate on buffer release: a single
     * shm buffer can be re-attached, and gating on release deadlocks against
     * compositors that only release once a new buffer arrives. */
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
    ui_window *w = (ui_window *)data;
    xdg_surface_ack_configure(s, serial);
    w->configured = 1;
    redraw(w);
}
static const struct xdg_surface_listener xdg_surface_listener = { xdg_surface_configure };

static void toplevel_configure(void *data, struct xdg_toplevel *t,
                               int32_t width, int32_t height, struct wl_array *states) {
    (void)t; (void)states;
    ui_window *w = (ui_window *)data;
    if (width > 0 && height > 0) {
        w->width = width;
        w->height = height;
    }
}
static void toplevel_close(void *data, struct xdg_toplevel *t) {
    (void)t;
    ((ui_window *)data)->running = 0;
}
static const struct xdg_toplevel_listener toplevel_listener = {
    .configure = toplevel_configure,
    .close = toplevel_close,
};

/* The compositor tells us the actual decoration mode it granted. If it insists
 * on client-side, we draw our own titlebar; if server-side, we let it decorate. */
static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode) {
    (void)d;
    ui_window *w = (ui_window *)data;
    w->use_csd = (mode == ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE);
    fprintf(stderr, "[ui] decoration granted: %s\n", w->use_csd ? "client-side" : "server-side");
    redraw(w);
}
static const struct zxdg_toplevel_decoration_v1_listener deco_listener = { deco_configure };

/* --- input (pointer axis = scroll) --- */

static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_surface *sf, wl_fixed_t x, wl_fixed_t y) {
    (void)p; (void)s; (void)sf;
    ui_window *w = (ui_window *)d;
    w->ptr_x = wl_fixed_to_double(x);
    w->ptr_y = wl_fixed_to_double(y);
}
static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf) {
    (void)d; (void)p; (void)s; (void)sf;
}
static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y) {
    (void)p; (void)t;
    ui_window *w = (ui_window *)d;
    w->ptr_x = wl_fixed_to_double(x);
    w->ptr_y = wl_fixed_to_double(y);
}
/* Left-press on the client-side titlebar: hit-test the controls, else drag. */
static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
                       uint32_t button, uint32_t state) {
    (void)p; (void)t;
    ui_window *w = (ui_window *)d;
    if (button != UI_BTN_LEFT || state != WL_POINTER_BUTTON_STATE_PRESSED) return;
    if (!w->use_csd || w->ptr_y >= UI_TITLEBAR_H) return; /* SSD or content area */

    double min_x, max_x, close_x;
    button_rects(w, &min_x, &max_x, &close_x);

    if (w->ptr_x >= close_x) {
        w->running = 0;
    } else if (w->ptr_x >= max_x) {
        if (w->maximized) xdg_toplevel_unset_maximized(w->xdg_toplevel);
        else              xdg_toplevel_set_maximized(w->xdg_toplevel);
        w->maximized = !w->maximized;
    } else if (w->ptr_x >= min_x) {
        xdg_toplevel_set_minimized(w->xdg_toplevel);
    } else if (w->seat != NULL) {
        xdg_toplevel_move(w->xdg_toplevel, w->seat, serial); /* interactive move */
    }
}
static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32_t axis, wl_fixed_t value) {
    (void)p; (void)time;
    if (axis != WL_POINTER_AXIS_VERTICAL_SCROLL) return;
    ui_window *w = (ui_window *)data;
    double v = wl_fixed_to_double(value);
    long step = (v > 0) ? 3 : -3;
    if (step < 0 && w->scroll < (size_t)(-step)) {
        w->scroll = 0;
    } else {
        w->scroll = (size_t)((long)w->scroll + step);
    }
    fprintf(stderr, "[ui] axis value=%.1f step=%ld -> scroll=%zu\n", v, step, w->scroll);
    redraw(w);
}
static const struct wl_pointer_listener pointer_listener = {
    .enter = ptr_enter,
    .leave = ptr_leave,
    .motion = ptr_motion,
    .button = ptr_button,
    .axis = ptr_axis,
};

static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps) {
    ui_window *w = (ui_window *)data;
    fprintf(stderr, "[ui] seat caps: pointer=%s\n",
            (caps & WL_SEAT_CAPABILITY_POINTER) ? "yes" : "no");
    if ((caps & WL_SEAT_CAPABILITY_POINTER) && w->pointer == NULL) {
        w->pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(w->pointer, &pointer_listener, w);
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
    ui_window *w = (ui_window *)data;
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
    registry_global, registry_remove
};

/* --- public orchestrator --- */

ui_status ui_run_text_view(const char *title, const char *text, size_t text_len) {
    if (text == NULL) return UI_ERR_NULL_ARG;

    ui_window w;
    memset(&w, 0, sizeof w);
    w.width = 800;
    w.height = 600;
    w.running = 1;
    w.title = (title != NULL) ? title : "Freedom";
    w.text = text;
    w.text_len = text_len;

    w.display = wl_display_connect(NULL);
    if (w.display == NULL) return UI_ERR_DISPLAY;

    w.registry = wl_display_get_registry(w.display);
    wl_registry_add_listener(w.registry, &registry_listener, &w);
    wl_display_roundtrip(w.display);

    fprintf(stderr, "[ui] globals: compositor=%s shm=%s wm_base=%s seat=%s decoration=%s\n",
            w.compositor ? "y" : "n", w.shm ? "y" : "n", w.wm_base ? "y" : "n",
            w.seat ? "y" : "n", w.deco_mgr ? "y" : "n");

    if (w.compositor == NULL || w.shm == NULL || w.wm_base == NULL) {
        wl_display_disconnect(w.display);
        return UI_ERR_INTERNAL;
    }

    w.surface = wl_compositor_create_surface(w.compositor);
    w.xdg_surface = xdg_wm_base_get_xdg_surface(w.wm_base, w.surface);
    xdg_surface_add_listener(w.xdg_surface, &xdg_surface_listener, &w);
    w.xdg_toplevel = xdg_surface_get_toplevel(w.xdg_surface);
    xdg_toplevel_add_listener(w.xdg_toplevel, &toplevel_listener, &w);
    xdg_toplevel_set_title(w.xdg_toplevel, w.title);
    xdg_toplevel_set_app_id(w.xdg_toplevel, "org.freedom.browser");

    /* Prefer server-side decorations; fall back to drawing our own. If the
     * compositor has no xdg-decoration at all (e.g. weston), use client-side. */
    w.use_csd = (w.deco_mgr == NULL);
    if (w.deco_mgr != NULL) {
        w.deco = zxdg_decoration_manager_v1_get_toplevel_decoration(w.deco_mgr, w.xdg_toplevel);
        zxdg_toplevel_decoration_v1_add_listener(w.deco, &deco_listener, &w);
        zxdg_toplevel_decoration_v1_set_mode(w.deco,
            ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);
    }

    wl_surface_commit(w.surface);

    while (w.running && wl_display_dispatch(w.display) != -1) {
        /* events drive redraw via the configure / axis handlers */
    }

    destroy_buffer(&w);
    if (w.deco) zxdg_toplevel_decoration_v1_destroy(w.deco);
    if (w.deco_mgr) zxdg_decoration_manager_v1_destroy(w.deco_mgr);
    if (w.xdg_toplevel) xdg_toplevel_destroy(w.xdg_toplevel);
    if (w.xdg_surface) xdg_surface_destroy(w.xdg_surface);
    if (w.surface) wl_surface_destroy(w.surface);
    if (w.pointer) wl_pointer_destroy(w.pointer);
    if (w.seat) wl_seat_destroy(w.seat);
    if (w.wm_base) xdg_wm_base_destroy(w.wm_base);
    if (w.shm) wl_shm_destroy(w.shm);
    if (w.compositor) wl_compositor_destroy(w.compositor);
    if (w.registry) wl_registry_destroy(w.registry);
    wl_display_disconnect(w.display);
    return UI_OK;
}
