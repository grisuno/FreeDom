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
#include "box_style.h"
#include "box_tree.h"
#include "css_color.h"
#include "hostblock.h"
#include "image_decode.h"
#include "link_nav.h"
#include "net_realm.h"
#include "pdf_export.h"
#include "render_doc.h"
#include "render_policy.h"
#include "textfield.h"
#include "ui.h"
#include "url.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <poll.h>
#include <sys/mman.h>
#include <sys/timerfd.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>

#include <wayland-client.h>
#include <wayland-cursor.h>
#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>
#include <fontconfig/fontconfig.h>
#include <xkbcommon/xkbcommon.h>

#include "xdg-shell-client-protocol.h"
#include "xdg-decoration-client-protocol.h"

#define UI_FONT_SIZE   14.0
#define UI_TOOLBAR_H   36.0
#define UI_TITLEBAR_H  30.0
#define UI_TABBAR_H    30.0   /* height of the tab strip (between titlebar and toolbar) */
#define UI_TAB_MIN_W   80.0   /* minimum drawn width of a tab before it shrinks further */
#define UI_TAB_MAX_W   200.0  /* preferred width of a tab when there is room */
#define UI_TAB_NEW_W   30.0   /* width of the trailing "new tab" (+) button */
#define UI_TAB_CLOSE_W 18.0   /* width of a tab's close (x) hot zone at its right edge */
#define UI_BTN_W       48.0
#define UI_WIN_BTN_W   30.0
#define UI_MARGIN      6.0
#define UI_BTN_LEFT    0x110  /* BTN_LEFT */
#define UI_TEXT_MARGIN 20.0   /* left/right/top breathing room around page content */
#define UI_LIST_INDENT 24.0   /* left indent (px) per list nesting level (ul/ol) */

/* Vertical scrollbar in the content area's right gutter. The gutter width is
 * always reserved (subtracted from the content width) so the scroll affordance and
 * the click hit-test share one geometry and never overlap the text. */
#define UI_SCROLLBAR_W   12.0  /* reserved gutter width on the content's right edge */
#define UI_SCROLLBAR_MIN 28.0  /* minimum thumb height so it stays grabbable */
#define UI_SCROLLBAR_PAD 2.0   /* inset of the thumb inside the track */

/* Border band (px) that starts an interactive window resize when dragged, used
 * only with client-side decorations (the compositor handles edges under SSD). */
#define UI_RESIZE_MARGIN 6.0

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
#define UI_TWO_PI       6.28318530717958647692 /* radians of a full circle (busy clock) */

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
    ui_rgb btn_hover_bg;    /* highlight behind the toolbar button under the pointer */
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
    ui_rgb scrollbar_track;
    ui_rgb scrollbar_thumb;
    ui_rgb scrollbar_thumb_hot; /* thumb under the pointer / being dragged */
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
    t.btn_hover_bg   = (ui_rgb){ 0.34, 0.35, 0.38 };
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
    t.scrollbar_track     = (ui_rgb){ 0.90, 0.90, 0.92 };
    t.scrollbar_thumb     = (ui_rgb){ 0.62, 0.62, 0.66 };
    t.scrollbar_thumb_hot = (ui_rgb){ 0.45, 0.45, 0.50 };
    return t;
}

/* Dark reading palette. Shares all the metrics (font sizes, spacing) with the
 * default theme; only the colours change, so the box model stays in one place. */
static ui_theme ui_theme_dark(void) {
    ui_theme t = ui_theme_default();
    t.window_bg      = (ui_rgb){ 0.12, 0.12, 0.13 };
    t.content_bg     = (ui_rgb){ 0.13, 0.13, 0.15 };
    t.text           = (ui_rgb){ 0.85, 0.86, 0.88 };
    t.heading        = (ui_rgb){ 0.78, 0.84, 1.00 };
    t.link           = (ui_rgb){ 0.50, 0.70, 1.00 };
    t.notice_bg      = (ui_rgb){ 0.28, 0.25, 0.10 };
    t.notice_text    = (ui_rgb){ 0.95, 0.90, 0.70 };
    t.image_box      = (ui_rgb){ 0.55, 0.55, 0.60 };
    t.image_blocked  = (ui_rgb){ 0.85, 0.50, 0.50 };
    t.toolbar_bg     = (ui_rgb){ 0.10, 0.10, 0.12 };
    t.titlebar_bg    = (ui_rgb){ 0.06, 0.06, 0.08 };
    t.chrome_text    = (ui_rgb){ 0.85, 0.85, 0.88 };
    t.chrome_text_dim= (ui_rgb){ 0.40, 0.40, 0.45 };
    t.close_button   = (ui_rgb){ 1.00, 0.55, 0.55 };
    t.url_bg_focused = (ui_rgb){ 0.22, 0.22, 0.26 };
    t.url_bg         = (ui_rgb){ 0.17, 0.17, 0.20 };
    t.url_border     = (ui_rgb){ 0.40, 0.40, 0.45 };
    t.caret          = (ui_rgb){ 0.90, 0.90, 0.95 };
    t.link_hover_bg  = (ui_rgb){ 0.18, 0.24, 0.34 };
    t.btn_hover_bg   = (ui_rgb){ 0.20, 0.21, 0.24 };
    t.input_bg          = (ui_rgb){ 0.18, 0.18, 0.21 };
    t.input_bg_focused  = (ui_rgb){ 0.22, 0.22, 0.18 };
    t.input_border      = (ui_rgb){ 0.45, 0.45, 0.50 };
    t.input_text        = (ui_rgb){ 0.88, 0.88, 0.90 };
    t.input_placeholder = (ui_rgb){ 0.50, 0.50, 0.55 };
    t.button_bg         = (ui_rgb){ 0.25, 0.45, 0.80 };
    t.button_text       = (ui_rgb){ 0.98, 0.98, 1.00 };
    t.menu_bg        = (ui_rgb){ 0.16, 0.16, 0.19 };
    t.menu_border    = (ui_rgb){ 0.45, 0.45, 0.50 };
    t.menu_text      = (ui_rgb){ 0.85, 0.85, 0.88 };
    t.check_border   = (ui_rgb){ 0.55, 0.55, 0.60 };
    t.check_mark     = (ui_rgb){ 0.40, 0.85, 0.50 };
    t.toast_bg       = (ui_rgb){ 0.04, 0.04, 0.06 };
    t.toast_text     = (ui_rgb){ 0.95, 0.95, 0.97 };
    t.scrollbar_track     = (ui_rgb){ 0.18, 0.18, 0.21 };
    t.scrollbar_thumb     = (ui_rgb){ 0.38, 0.38, 0.43 };
    t.scrollbar_thumb_hot = (ui_rgb){ 0.55, 0.55, 0.62 };
    return t;
}

/* Sepia reading palette: warm paper background and dark-brown ink, easier on the
 * eyes for long-form text. Shares all the metrics with the default theme; only the
 * colours change. */
static ui_theme ui_theme_sepia(void) {
    ui_theme t = ui_theme_default();
    t.window_bg      = (ui_rgb){ 0.90, 0.85, 0.74 };
    t.content_bg     = (ui_rgb){ 0.96, 0.92, 0.82 };
    t.text           = (ui_rgb){ 0.24, 0.18, 0.10 };
    t.heading        = (ui_rgb){ 0.30, 0.20, 0.10 };
    t.link           = (ui_rgb){ 0.40, 0.26, 0.10 };
    t.notice_bg      = (ui_rgb){ 0.93, 0.86, 0.62 };
    t.notice_text    = (ui_rgb){ 0.40, 0.28, 0.05 };
    t.image_box      = (ui_rgb){ 0.50, 0.42, 0.30 };
    t.image_blocked  = (ui_rgb){ 0.65, 0.32, 0.22 };
    t.toolbar_bg     = (ui_rgb){ 0.42, 0.34, 0.24 };
    t.titlebar_bg    = (ui_rgb){ 0.32, 0.25, 0.16 };
    t.chrome_text    = (ui_rgb){ 0.95, 0.90, 0.80 };
    t.chrome_text_dim= (ui_rgb){ 0.62, 0.55, 0.45 };
    t.url_bg_focused = (ui_rgb){ 0.99, 0.96, 0.88 };
    t.url_bg         = (ui_rgb){ 0.86, 0.80, 0.68 };
    t.url_border     = (ui_rgb){ 0.30, 0.24, 0.14 };
    t.caret          = (ui_rgb){ 0.20, 0.14, 0.06 };
    t.link_hover_bg  = (ui_rgb){ 0.88, 0.80, 0.62 };
    t.btn_hover_bg   = (ui_rgb){ 0.52, 0.43, 0.30 };
    t.input_bg          = (ui_rgb){ 0.98, 0.94, 0.84 };
    t.input_bg_focused  = (ui_rgb){ 1.00, 0.98, 0.90 };
    t.input_border      = (ui_rgb){ 0.55, 0.46, 0.32 };
    t.input_text        = (ui_rgb){ 0.24, 0.18, 0.10 };
    t.input_placeholder = (ui_rgb){ 0.55, 0.46, 0.34 };
    t.button_bg         = (ui_rgb){ 0.50, 0.36, 0.18 };
    t.button_text       = (ui_rgb){ 0.98, 0.94, 0.86 };
    t.menu_bg        = (ui_rgb){ 0.95, 0.90, 0.80 };
    t.menu_border    = (ui_rgb){ 0.55, 0.46, 0.32 };
    t.menu_text      = (ui_rgb){ 0.26, 0.19, 0.10 };
    t.check_border   = (ui_rgb){ 0.45, 0.36, 0.24 };
    t.check_mark     = (ui_rgb){ 0.35, 0.45, 0.20 };
    t.toast_bg       = (ui_rgb){ 0.30, 0.23, 0.14 };
    t.toast_text     = (ui_rgb){ 0.96, 0.92, 0.84 };
    t.scrollbar_track     = (ui_rgb){ 0.84, 0.78, 0.66 };
    t.scrollbar_thumb     = (ui_rgb){ 0.58, 0.48, 0.34 };
    t.scrollbar_thumb_hot = (ui_rgb){ 0.44, 0.35, 0.22 };
    return t;
}

/* Selectable palettes for the options menu. */
typedef enum ui_theme_mode {
    UI_THEME_LIGHT = 0,
    UI_THEME_DARK,
    UI_THEME_SEPIA
} ui_theme_mode;

/* The single place that maps the theme mode to a palette. */
static ui_theme ui_theme_for(int mode) {
    switch (mode) {
        case UI_THEME_DARK:  return ui_theme_dark();
        case UI_THEME_SEPIA: return ui_theme_sepia();
        default:             return ui_theme_default();
    }
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

/* The options-menu items. A capability item toggles a bool in rdp_caps by field
 * offset (labels and the flag live in one place, no magic indices); a theme item
 * selects a palette; the force item ignores author colours. */
typedef enum ui_menu_action {
    UI_MENU_CAP = 0,  /* toggles w->caps.<offset>; needs a re-render from cache */
    UI_MENU_THEME,    /* selects w->theme_mode (theme_val); needs only a repaint */
    UI_MENU_FORCE,    /* toggles w->force_theme; needs only a repaint */
    UI_MENU_TOR,      /* toggles Tor routing (tor_enabled + torify clearnet) */
    UI_MENU_I2P,      /* toggles I2P routing for .i2p */
    UI_MENU_PDF       /* action (not a toggle): export the page to a vector PDF */
} ui_menu_action;

typedef struct ui_menu_item {
    const char    *label;
    ui_menu_action action;
    size_t         cap_offset; /* offset of a bool field within rdp_caps (UI_MENU_CAP) */
    int            theme_val;  /* the ui_theme_mode this item selects (UI_MENU_THEME) */
} ui_menu_item;

static const ui_menu_item UI_MENU_ITEMS[] = {
    { "Dark mode",            UI_MENU_THEME, 0,                          UI_THEME_DARK },
    { "Reading mode (sepia)", UI_MENU_THEME, 0,                          UI_THEME_SEPIA },
    { "Force theme colors",   UI_MENU_FORCE, 0,                          0 },
    { "Load images",          UI_MENU_CAP,   offsetof(rdp_caps, images), 0 },
    { "Author colors (CSS)",  UI_MENU_CAP,   offsetof(rdp_caps, css),    0 },
    { "Tor routing (.onion)", UI_MENU_TOR,   0,                          0 },
    { "I2P routing (.i2p)",   UI_MENU_I2P,   0,                          0 },
    { "Save as PDF (Ctrl+P)", UI_MENU_PDF,   0,                          0 },
};
#define UI_MENU_COUNT (sizeof UI_MENU_ITEMS / sizeof UI_MENU_ITEMS[0])

/* Toolbar control under the pointer, for the hover highlight (the same affordance
 * links already get). */
typedef enum ui_hot {
    UI_HOT_NONE = 0, UI_HOT_BACK, UI_HOT_FWD, UI_HOT_GO, UI_HOT_MENU
} ui_hot;

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

/* Hard cap on the response body of an image subresource (a PNG; the decoder bounds
 * the decoded pixels further). Keeps a hostile server from streaming forever. */
#define UI_IMAGE_MAX_BODY ((size_t)(8u * 1024u * 1024u))

/* A decoded image for one RD_IMAGE block of the current doc. surface owns the
 * pixels (ARGB32) and is NULL when the image was blocked, not fetched, or could
 * not be decoded (the placeholder is drawn instead). nat_w/nat_h are the natural
 * pixel dimensions. The block aliases w->doc (not owned). */
typedef struct ui_image {
    const rd_block  *blk;
    cairo_surface_t *surface;
    int              nat_w, nat_h;
} ui_image;

/* Maximum concurrent tabs. Bounded so the per-tab snapshot array is a fixed,
 * auditable size (no unbounded growth from a hostile page opening tabs; this
 * browser never opens a tab on a page's behalf anyway). */
#define UI_MAX_TABS 16

/* One tab's complete per-page state: everything that must persist when the tab is
 * not the foreground one. The browser_window keeps the ACTIVE tab's copy in its own
 * fields (so the 200+ render/event call sites stay unchanged); tab_save/tab_restore
 * move this set in and out of the slot array on a switch. All owned pointers are
 * transferred by value (no deep copy, no free): exactly one of {live window field,
 * inactive slot} owns each allocation at any time. */
typedef struct tab_ctx {
    browser_state   bs;          /* history, URL bar, page text/title, exceptions */
    rd_doc         *doc;         /* structured render, or NULL (text mode) */
    rdp_caps        caps;        /* per-tab render capabilities (images/CSS/JS) */
    double          scroll, content_total_h;
    ui_input_state *inputs; size_t input_count; int focused_input;
    ui_image       *images; size_t image_count;
    char           *cur_html; size_t cur_html_len; char *cur_top;
    int             loading;
    const char     *hover_href; /* aliases doc; moves with it */
} tab_ctx;

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
    int       theme_mode;  /* ui_theme_mode selected in the options menu */
    int       force_theme; /* ignore author fg/bg colors, use the theme (reading) */
    int       loading;   /* a network request is in flight (busy clock shown) */
    ui_hot    hot;       /* toolbar button under the pointer, or UI_HOT_NONE */
    rd_doc   *doc;      /* structured render of the current page; NULL => text mode */
    rdp_caps  caps;     /* per-page render capabilities (images off by default) */
    hb_set   *hosts;    /* /etc/hosts-format blocklist + allowlist; consulted pre-fetch */
    nr_config net_cfg;  /* Tor/I2P routing (Privacy by Default: opt-in, off by default) */
    char      tor_addr[64];  /* Tor SOCKS5h proxy "host:port" (default 127.0.0.1:9050) */
    char      i2p_addr[64];  /* I2P HTTP proxy "host:port" (default 127.0.0.1:4444) */
    double    scroll;   /* content scroll offset in pixels */
    double    content_total_h;  /* full height of the laid-out content, cached each paint */
    int       maximized;        /* toplevel currently maximized (from xdg states) */
    int       dragging_scroll;  /* the scrollbar thumb is being dragged */
    double    scroll_grab_dy;   /* pointer offset within the thumb at drag start */
    int       pending_g;        /* a 'g' was pressed; a second one scrolls to the top (vim gg) */

    int         menu_open;     /* the options (gear) panel is showing */
    const char *hover_href;    /* link target under the pointer (aliases doc), or NULL */

    /* Live form text controls of the current page (rebuilt with the doc). */
    ui_input_state *inputs;
    size_t          input_count;
    int             focused_input; /* index into inputs, or -1 */

    /* Decoded images of the current page (rebuilt with the doc; one per RD_IMAGE). */
    ui_image       *images;
    size_t          image_count;

    /* Configurable network User-Agent (session only; empty => SF_DEFAULT_USER_AGENT,
     * which IS the anti_fp normalized identity, matching navigator.userAgent). A custom
     * value overrides only the wire header; the JS identity stays normalised. Edited in
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

    /* Key auto-repeat. Wayland delivers one key event per physical press; a held key
     * (e.g. Backspace to clear the URL bar) repeats only if the client re-fires it on
     * a timer. repeat_key is the evdev code currently held (0 => none); rate/delay come
     * from the compositor (keyboard_repeat_info) with sane fallbacks. */
    int      repeat_timer_fd;  /* timerfd in the poll set; -1 if unavailable */
    uint32_t repeat_key;       /* evdev keycode being repeated, or 0 */
    int32_t  repeat_rate;      /* repeats per second (0 disables repeat) */
    int32_t  repeat_delay;     /* ms held before the first repeat */

    /* Clipboard (wl_data_device): paste into the focused text field, copy the address.
     * A selection offer's mime types are scanned as it is introduced (incoming_*); on
     * the selection event the chosen text mime is committed for a later paste. */
    struct wl_data_device_manager *data_device_manager;
    struct wl_data_device         *data_device;
    struct wl_data_offer          *selection_offer;  /* current clipboard offer, or NULL */
    struct wl_data_offer          *incoming_offer;   /* offer being introduced (mime scan) */
    int      selection_offer_has_text;
    int      incoming_offer_has_text;
    char     sel_mime[64];      /* committed selection's preferred text mime */
    char     incoming_mime[64]; /* preferred text mime while scanning the incoming offer */
    struct wl_data_source *copy_source; /* our active copy offer, or NULL */
    char    *copy_text;                 /* text exposed for copy (owned) */
    uint32_t last_serial;               /* latest input-event serial, for set_selection */

    /* Asynchronous network fetch. The blocking sf_get/sf_post runs on a detached
     * worker thread so the event loop stays responsive; the thread posts a completed
     * fetch_job pointer down fetch_pipe, which the loop polls and renders on the main
     * thread (Cairo/Wayland are single-threaded). net_gen is bumped on every new
     * navigation and every tab context change, so a result whose gen no longer matches
     * is discarded -- the active tab is then guaranteed unchanged since the launch. */
    int      fetch_pipe[2];  /* [0] read end (polled), [1] write end (threads) */
    uint64_t net_gen;        /* current navigation generation */

    /* Tabs. The active tab's state lives in the fields above; the other tabs are
     * parked in tab_slots. tab_count >= 1 always; active_tab is in [0, tab_count). */
    tab_ctx tab_slots[UI_MAX_TABS];
    int     tab_count;
    int     active_tab;
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

/* Loads one /etc/hosts-format .conf file (if present and readable) into the given
 * list. A missing file is not an error: the filter fails open, never over-blocking. */
static void load_host_file(hb_set *s, const char *dir, const char *name, hb_list list) {
    char path[1024];
    int n = snprintf(path, sizeof path, "%s/%s", dir, name);
    if (n <= 0 || (size_t)n >= sizeof path) return;
    size_t len = 0;
    char *txt = read_file(path, &len);
    if (txt == NULL) return;
    hb_load(s, txt, list);   /* HB_ERR_OOM only drops extra entries; not fatal here */
    free(txt);
}

/* Builds the host filter from the user's .conf lists. Privacy by Default: block.conf
 * (a /etc/hosts-format blocklist) blocks trackers/ads and their subdomains; allow.conf
 * re-enables specific (sub)domains and wins over the blocklist. Directories are tried
 * in order -- $FREEDOM_HOSTS_DIR, then ~/.config/freedom, then ./config (repo-local) --
 * and each that exists is loaded cumulatively. Returns NULL only on OOM (hb_check
 * then treats every host as allowed). */
static hb_set *build_host_filter(void) {
    hb_set *s = hb_new();
    if (s == NULL) return NULL;

    const char *env = getenv("FREEDOM_HOSTS_DIR");
    if (env != NULL && env[0] != '\0') {
        load_host_file(s, env, "block.conf", HB_LIST_BLOCK);
        load_host_file(s, env, "allow.conf", HB_LIST_ALLOW);
    }

    const char *home = getenv("HOME");
    if (home != NULL && home[0] != '\0') {
        char dir[1024];
        int n = snprintf(dir, sizeof dir, "%s/.config/freedom", home);
        if (n > 0 && (size_t)n < sizeof dir) {
            load_host_file(s, dir, "block.conf", HB_LIST_BLOCK);
            load_host_file(s, dir, "allow.conf", HB_LIST_ALLOW);
        }
    }

    load_host_file(s, "config", "block.conf", HB_LIST_BLOCK);
    load_host_file(s, "config", "allow.conf", HB_LIST_ALLOW);
    return s;
}

/* Copies a proxy "host:port" into dst: if the env value is unset/empty the default is
 * used; the literal "1" also means "use the default" (a convenient on-switch). Returns
 * 1 if the env var was set non-empty (the proxy should be enabled), else 0. */
static int proxy_addr_from_env(const char *envname, const char *deflt,
                               char *dst, size_t dstsz) {
    const char *v = getenv(envname);
    int enabled = (v != NULL && v[0] != '\0');
    const char *addr = (!enabled || strcmp(v, "1") == 0) ? deflt : v;
    snprintf(dst, dstsz, "%s", addr);
    return enabled;
}

/* Builds the Tor/I2P routing config from the environment (Privacy by Default: opt-in,
 * everything off unless explicitly enabled). FREEDOM_TOR_PROXY / FREEDOM_I2P_PROXY set
 * and enable each proxy ("1" => the default port); FREEDOM_TORIFY_CLEARNET=1 routes
 * ordinary clearnet through Tor too. The addresses are always seeded with the defaults
 * so the menu toggles work even when the env vars are absent. */
static void init_net_config(browser_window *w) {
    memset(&w->net_cfg, 0, sizeof w->net_cfg);
    w->net_cfg.tor_enabled = proxy_addr_from_env("FREEDOM_TOR_PROXY", "127.0.0.1:9050",
                                                 w->tor_addr, sizeof w->tor_addr);
    w->net_cfg.i2p_enabled = proxy_addr_from_env("FREEDOM_I2P_PROXY", "127.0.0.1:4444",
                                                 w->i2p_addr, sizeof w->i2p_addr);
    const char *t = getenv("FREEDOM_TORIFY_CLEARNET");
    w->net_cfg.torify_clearnet = (t != NULL && strcmp(t, "1") == 0 && w->net_cfg.tor_enabled);
}

static int is_https_url(const char *s) {
    return strncmp(s, "https://", 8) == 0;
}

static int is_http_url(const char *s) {
    return strncmp(s, "http://", 7) == 0;
}

/* A plain-http URL whose realm self-authenticates (an i2p eepsite today): it is
 * fetched over the network (through the overlay proxy), not read as a local file. */
static int is_overlay_http_url(const char *s) {
    return is_http_url(s) && nr_realm_allows_http(nr_classify_url(s));
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

/* Releases the decoded image surfaces of the current page and the array. */
static void free_images(browser_window *w) {
    for (size_t i = 0; i < w->image_count; ++i) {
        if (w->images[i].surface != NULL) cairo_surface_destroy(w->images[i].surface);
    }
    free(w->images);
    w->images = NULL;
    w->image_count = 0;
}

/* The decoded image for a doc block, or NULL when it has none (blocked / failed). */
static const ui_image *find_image(const browser_window *w, const rd_block *blk) {
    for (size_t i = 0; i < w->image_count; ++i) {
        if (w->images[i].blk == blk) return &w->images[i];
    }
    return NULL;
}

/* On-screen size of a decoded image: fit to the content width, never upscaled past
 * the natural size. Returns 1 and sets dw/dh when a decoded surface exists for the
 * block; 0 otherwise (the caller draws the placeholder). The single source of truth
 * shared by layout (row height) and paint (blit), so they cannot drift apart. */
static int image_display_size(const browser_window *w, const rd_block *blk,
                              double box_w, double *dw, double *dh) {
    const ui_image *im = find_image(w, blk);
    if (im == NULL || im->surface == NULL || im->nat_w <= 0 || im->nat_h <= 0) return 0;
    if (box_w < 1.0) box_w = 1.0;
    double scale = ((double)im->nat_w > box_w) ? box_w / (double)im->nat_w : 1.0;
    *dw = (double)im->nat_w * scale;
    *dh = (double)im->nat_h * scale;
    return 1;
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
    free_images(w);
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

/* Wraps decoded ARGB32 pixels in a Cairo surface the painter can blit. Copies row
 * by row because Cairo may use a wider stride than the tightly packed worker buffer.
 * Returns NULL on failure. */
static cairo_surface_t *surface_from_pixels(const tab_image *img) {
    if (img->data == NULL || img->width == 0 || img->height == 0) return NULL;
    cairo_surface_t *s = cairo_image_surface_create(
        CAIRO_FORMAT_ARGB32, (int)img->width, (int)img->height);
    if (cairo_surface_status(s) != CAIRO_STATUS_SUCCESS) {
        cairo_surface_destroy(s);
        return NULL;
    }
    cairo_surface_flush(s);
    unsigned char *dst = cairo_image_surface_get_data(s);
    int dstride = cairo_image_surface_get_stride(s);
    size_t rowbytes = (size_t)img->width * 4u;
    for (uint32_t y = 0; y < img->height; ++y) {
        memcpy(dst + (size_t)y * (size_t)dstride,
               img->data + (size_t)y * (size_t)img->stride, rowbytes);
    }
    cairo_surface_mark_dirty(s);
    return s;
}

/* Applies the realm route for url to cfg (proxy type + address). Returns the route;
 * NR_ROUTE_BLOCKED means the caller must NOT fetch (fail closed). */
static nr_route apply_route(const browser_window *w, const char *url, sf_config *cfg) {
    nr_route r = nr_route_for(url, w->net_cfg);
    if (r == NR_ROUTE_TOR) {
        cfg->proxy_type = SF_PROXY_SOCKS5H;
        cfg->proxy_address = w->tor_addr;
    } else if (r == NR_ROUTE_I2P) {
        cfg->proxy_type = SF_PROXY_HTTP;
        cfg->proxy_address = w->i2p_addr;
    }
    /* An overlay realm routed through its proxy may use plain http (the overlay
     * authenticates + encrypts by address). Only i2p opts in today; onion stays https. */
    if (r == NR_ROUTE_TOR || r == NR_ROUTE_I2P)
        cfg->allow_overlay_http = nr_realm_allows_http(nr_classify_url(url));
    return r;
}

/* Downgrade reasons reported by fetch_follow_navigable via *downgraded. */
enum { DOWNGRADE_NONE = 0, DOWNGRADE_CLASSICAL_KE = 1, DOWNGRADE_ALLOWLISTED = 2 };

/* Fetches url (following redirects) under cfg's policy, applying two navigability
 * fallbacks in order of decreasing security:
 *   1) If the only obstacle is a non-PQ key exchange (SF_ERR_KEM_NOT_PQ), retry with
 *      the classical-KE fallback (TLS 1.3 + full cert validation kept). Applies to
 *      every host; *downgraded = DOWNGRADE_CLASSICAL_KE on success.
 *   2) If the host is on the user's allowlist (allowlisted != 0) and still fails,
 *      retry with the allowlist override: TLS 1.2, classical KE, weak-but-valid cert.
 *      The chain is still authenticated, so this reaches the real site over older
 *      crypto, not an impostor. *downgraded = DOWNGRADE_ALLOWLISTED on success. This
 *      is the user's sovereign escape hatch -- secure by default, not a dictatorship.
 * A non-allowlisted host that fails Freedom's standard stays fatal (fail closed).
 * cfg->policy is restored before returning. */
static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                                        sf_response *out, int *downgraded,
                                        int allowlisted) {
    *downgraded = DOWNGRADE_NONE;
    sf_status s = sf_get_follow(url, cfg, out, SF_DEFAULT_MAX_REDIRECTS);
    if (s == SF_OK) return s;

    if (s == SF_ERR_KEM_NOT_PQ) {
        sf_response_free(out);
        sf_policy saved = cfg->policy;
        cfg->policy = SF_POLICY_ALLOW_CLASSICAL_KE;
        s = sf_get_follow(url, cfg, out, SF_DEFAULT_MAX_REDIRECTS);
        cfg->policy = saved;
        if (s == SF_OK) { *downgraded = DOWNGRADE_CLASSICAL_KE; return s; }
    }

    if (allowlisted) {
        sf_response_free(out);
        sf_policy saved = cfg->policy;
        cfg->policy = SF_POLICY_ALLOWLISTED_INSECURE;
        s = sf_get_follow(url, cfg, out, SF_DEFAULT_MAX_REDIRECTS);
        cfg->policy = saved;
        if (s == SF_OK) { *downgraded = DOWNGRADE_ALLOWLISTED; return s; }
    }
    return s;
}

/* Like fetch_follow_navigable, but for a POST (sf_post does not follow redirects:
 * the caller inspects out->http_code/out->location). The SAME two navigability
 * fallbacks apply in the SAME order, so a POST is never sent under weaker rules than
 * a GET (Zero Trust). cfg->policy is restored before returning. */
static sf_status fetch_post_navigable(const char *url, sf_config *cfg,
                                      const void *body, size_t body_len,
                                      const char *content_type, sf_response *out,
                                      int *downgraded, int allowlisted) {
    *downgraded = DOWNGRADE_NONE;
    sf_status s = sf_post(url, cfg, body, body_len, content_type, out);
    if (s == SF_OK) return s;

    if (s == SF_ERR_KEM_NOT_PQ) {
        sf_response_free(out);
        sf_policy saved = cfg->policy;
        cfg->policy = SF_POLICY_ALLOW_CLASSICAL_KE;
        s = sf_post(url, cfg, body, body_len, content_type, out);
        cfg->policy = saved;
        if (s == SF_OK) { *downgraded = DOWNGRADE_CLASSICAL_KE; return s; }
    }

    if (allowlisted) {
        sf_response_free(out);
        sf_policy saved = cfg->policy;
        cfg->policy = SF_POLICY_ALLOWLISTED_INSECURE;
        s = sf_post(url, cfg, body, body_len, content_type, out);
        cfg->policy = saved;
        if (s == SF_OK) { *downgraded = DOWNGRADE_ALLOWLISTED; return s; }
    }
    return s;
}

/* Outcome of the pre-fetch gates shared by GET (do_load) and POST (do_submit_post).
 * Both MUST pass through the SAME host filter, per-host exception, allowlist override
 * and Tor/I2P realm route before any socket opens -- otherwise a POST could reach the
 * network under laxer rules than a GET, or leak a .onion lookup over clearnet. */
typedef struct fetch_prep {
    int  allowlisted;  /* host is explicitly on allow.conf (sovereign override eligible) */
    char err[768];     /* when prepare_fetch returns 0: the ready-to-show block reason */
} fetch_prep;

/* Builds cfg for url and applies the pre-fetch gates. Returns nonzero when the fetch
 * may proceed (cfg and pr->allowlisted are then set); returns 0 when the request is
 * blocked, with pr->err holding the user-facing reason (host filter or realm fail-
 * closed). Pure orchestration over already-tested validators (hostblock, net_realm). */
static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                         fetch_prep *pr) {
    memset(pr, 0, sizeof *pr);
    *cfg = sf_config_default();
    cfg->user_agent = tf_text(&w->ua_field); /* "" => SF_DEFAULT_USER_AGENT */

    char host[256];
    int have_host = host_from_url(url, host, sizeof host);

    /* Privacy by Default: consult the host filter before opening any socket. The
     * allowlist wins, so a re-enabled subdomain of a blocked domain still loads. */
    if (have_host && hb_check(w->hosts, host) == HB_BLOCK) {
        snprintf(pr->err, sizeof pr->err,
            "Blocked '%s' by the host filter.\n\n"
            "This domain (or a parent of it) is on your blocklist (block.conf).\n"
            "To see a specific subdomain, add it to allow.conf -- the allowlist\n"
            "wins over the blocklist and covers its subdomains -- then reload.\n\n"
            "Lists are read from $FREEDOM_HOSTS_DIR, ~/.config/freedom, or ./config\n"
            "in /etc/hosts format (one domain per line, or '0.0.0.0 domain').",
            host);
        return 0;
    }

    if (have_host && browser_is_exception(&w->bs, host))
        cfg->policy = SF_POLICY_PERMISSIVE;

    /* The user's sovereign override: a host explicitly on allow.conf may be navigated
     * below Freedom's standard (TLS 1.2, classical KE, weak cert) if strict fails. */
    pr->allowlisted = have_host && hb_is_allowlisted(w->hosts, host);

    /* Socket-level anonymity routing (Tor/I2P). A .onion/.i2p host with its proxy
     * disabled is BLOCKED, never leaked over clearnet (fail closed). */
    nr_route route = apply_route(w, url, cfg);
    if (route == NR_ROUTE_BLOCKED) {
        nr_realm realm = nr_classify_url(url);
        snprintf(pr->err, sizeof pr->err,
            "Blocked '%s': it is a %s address but %s routing is not enabled.\n\n"
            "Freedom never leaks a %s lookup over the clearnet (fail closed). Enable\n"
            "%s in the menu (or set %s) and make sure a local %s proxy is running,\n"
            "then reload.",
            url, nr_realm_name(realm),
            (realm == NR_I2P) ? "I2P" : "Tor",
            nr_realm_name(realm),
            (realm == NR_I2P) ? "I2P routing" : "Tor routing",
            (realm == NR_I2P) ? "FREEDOM_I2P_PROXY" : "FREEDOM_TOR_PROXY",
            (realm == NR_I2P) ? "I2P (e.g. i2pd)" : "Tor");
        return 0;
    }
    return 1;
}

/* A network request handed to the fetch thread. It owns deep copies of every input
 * string (the window's buffers may change while the fetch runs), and is filled with
 * the result before being posted back to the main thread, which owns it from then on.
 * The thread NEVER touches the browser_window -- only this self-contained job. */
typedef struct fetch_job {
    int       write_fd;     /* fetch_pipe[1]: where the thread posts itself when done */
    uint64_t  gen;          /* navigation generation; stale results are discarded */
    int       is_post;

    /* Input (owned). cfg is rebuilt from these on the thread. */
    char         *url;
    char         *user_agent;    /* may be NULL => sf default */
    char         *proxy_address; /* may be NULL */
    sf_proxy_type proxy_type;
    int           allow_overlay_http;
    sf_policy     policy;
    int           allowlisted;
    void         *body;          /* POST body (owned), or NULL */
    size_t        body_len;
    char         *content_type;  /* POST content type (owned), or NULL */

    /* Output (filled by the thread). */
    sf_status status;
    int       downgraded;        /* DOWNGRADE_* */
    char     *html;              /* response body (owned), or NULL */
    size_t    html_len;
    long      http_code;
    char     *location;          /* POST redirect target (owned), or NULL */
} fetch_job;

static void fetch_job_free(fetch_job *j) {
    if (j == NULL) return;
    free(j->url);
    free(j->user_agent);
    free(j->proxy_address);
    free(j->body);
    free(j->content_type);
    free(j->html);
    free(j->location);
    free(j);
}

/* Worker body: runs the (blocking) policy-enforcing fetch, then posts the job pointer
 * back to the event loop. Pure with respect to the window: it reads/writes only the
 * job and writes one pointer to the pipe. */
static void *fetch_thread(void *arg) {
    fetch_job *j = (fetch_job *)arg;

    sf_config cfg = sf_config_default();
    cfg.user_agent = j->user_agent; /* NULL => sf default */
    cfg.proxy_type = j->proxy_type;
    cfg.proxy_address = j->proxy_address;
    cfg.allow_overlay_http = j->allow_overlay_http;
    cfg.policy = j->policy;

    sf_response resp;
    memset(&resp, 0, sizeof resp);
    sf_status s = j->is_post
        ? fetch_post_navigable(j->url, &cfg, j->body, j->body_len, j->content_type,
                               &resp, &j->downgraded, j->allowlisted)
        : fetch_follow_navigable(j->url, &cfg, &resp, &j->downgraded, j->allowlisted);

    j->status = s;
    if (s == SF_OK) {
        j->html = (char *)resp.body; resp.body = NULL; /* move ownership to the job */
        j->html_len = resp.body_len;
        j->http_code = resp.http_code;
        j->location = (resp.location != NULL) ? strdup(resp.location) : NULL;
    }
    sf_response_free(&resp);

    ssize_t wr = write(j->write_fd, &j, sizeof j);
    if (wr != (ssize_t)sizeof j) fetch_job_free(j); /* pipe gone (shutdown): no reader */
    return NULL;
}

/* Spawns a detached worker to fetch url under cfg (already gated by prepare_fetch).
 * The caller has bumped w->net_gen for this navigation; the job snapshots it. Returns
 * nonzero on success. On failure nothing is launched and the caller shows an error. */
static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
                        int allowlisted, int is_post, const void *body, size_t body_len,
                        const char *content_type) {
    if (w->fetch_pipe[1] < 0) return 0;
    fetch_job *j = (fetch_job *)calloc(1, sizeof *j);
    if (j == NULL) return 0;

    j->write_fd = w->fetch_pipe[1];
    j->gen = w->net_gen;
    j->is_post = is_post;
    j->proxy_type = cfg->proxy_type;
    j->allow_overlay_http = cfg->allow_overlay_http;
    j->policy = cfg->policy;
    j->allowlisted = allowlisted;
    j->url = strdup(url);
    j->user_agent = (cfg->user_agent != NULL) ? strdup(cfg->user_agent) : NULL;
    j->proxy_address = (cfg->proxy_address != NULL) ? strdup(cfg->proxy_address) : NULL;
    if (is_post) {
        j->content_type = (content_type != NULL) ? strdup(content_type) : NULL;
        if (body_len > 0) {
            j->body = malloc(body_len);
            if (j->body != NULL) { memcpy(j->body, body, body_len); j->body_len = body_len; }
        }
    }
    /* Bail if any required copy failed (an OOM mid-setup must not fetch a truncated body). */
    if (j->url == NULL ||
        (cfg->user_agent != NULL && j->user_agent == NULL) ||
        (cfg->proxy_address != NULL && j->proxy_address == NULL) ||
        (is_post && content_type != NULL && j->content_type == NULL) ||
        (is_post && body_len > 0 && j->body == NULL)) {
        fetch_job_free(j);
        return 0;
    }

    pthread_t th;
    if (pthread_create(&th, NULL, fetch_thread, j) != 0) {
        fetch_job_free(j);
        return 0;
    }
    pthread_detach(th);
    return 1;
}

/* Fetches and decodes every allowed image of the current doc into w->images (one
 * entry per RD_IMAGE block). Each fetch re-applies the full TLS/PQ/chain policy
 * through secure_fetch (Zero Trust); decoding happens inside the still-open confined
 * worker t, so the parent never decodes hostile image bytes. A blocked, policy-
 * rejected, failed or non-PNG image keeps surface == NULL and the placeholder is
 * drawn. Synchronous: image loads block this render (acceptable for v1; async fetch
 * is future work). */
static void load_images(browser_window *w, tab *t) {
    if (w->doc == NULL) return;
    size_t n = rd_count(w->doc);
    size_t nimg = 0;
    for (size_t i = 0; i < n; ++i)
        if (rd_at(w->doc, i)->kind == RD_IMAGE) nimg++;
    if (nimg == 0) return;

    w->images = (ui_image *)calloc(nimg, sizeof *w->images);
    if (w->images == NULL) return; /* fail closed: no images, page still shows */

    size_t k = 0;
    for (size_t i = 0; i < n; ++i) {
        const rd_block *b = rd_at(w->doc, i);
        if (b->kind != RD_IMAGE) continue;
        ui_image *slot = &w->images[k++];
        slot->blk = b;

        /* render_doc already applied render_policy: only an ALLOW image with a src is
         * fetched. cur_top is the https origin; resolution fails closed without it. */
        if (b->img_decision != RDP_IMG_ALLOW || b->href == NULL || w->cur_top == NULL)
            continue;

        char abs[URL_MAX_LEN];
        if (url_resolve_https(w->cur_top, b->href, abs, sizeof abs) != URL_OK)
            continue;

        sf_config cfg = sf_config_default();
        cfg.user_agent = tf_text(&w->ua_field);
        cfg.max_body_bytes = UI_IMAGE_MAX_BODY;

        /* Route the image like the page: a .onion/.i2p image with its proxy off is
         * skipped, never leaked over clearnet (fail closed). */
        if (apply_route(w, abs, &cfg) == NR_ROUTE_BLOCKED) continue;

        sf_response resp;
        memset(&resp, 0, sizeof resp);
        int img_downgraded = 0; /* page-level toast already warns; per-image is moot */
        char ihost[256];
        int img_allow = host_from_url(abs, ihost, sizeof ihost)
                        && hb_is_allowlisted(w->hosts, ihost);
        if (fetch_follow_navigable(abs, &cfg, &resp, &img_downgraded, img_allow) != SF_OK) {
            sf_response_free(&resp);
            continue;
        }

        tab_image img;
        tab_status ds = tab_decode_image(t, resp.body, resp.body_len, &img);
        sf_response_free(&resp);
        if (ds != TAB_OK || img.data == NULL) { tab_image_free(&img); continue; }

        slot->surface = surface_from_pixels(&img);
        if (slot->surface != NULL) {
            slot->nat_w = (int)img.width;
            slot->nat_h = (int)img.height;
        }
        tab_image_free(&img);
    }
    w->image_count = k;
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
    load_images(w, t); /* fetch + decode allowed images in the still-open worker */

    tab_page_free(&page);
    tab_close(t);
}

/* Marks a request in flight and paints a frame so the spinner appears at once. The
 * fetch now runs on a worker thread, so the event loop keeps animating the spinner
 * and stays responsive until deliver_fetch_result lands the page. */
static void show_busy(browser_window *w) {
    w->loading = 1;
    redraw(w);
    if (w->display != NULL) wl_display_flush(w->display);
}

/* Replaces the page with the standard "Failed to load" diagnostic for status ss on
 * url. allowlisted tailors the hint (already retried vs. how to override). Shared by
 * the GET and POST async-result handlers so the message stays in one place. */
static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                             int allowlisted) {
    char host[256];
    const char *reason = "";
    switch (ss) {
        case SF_ERR_TLS_VERSION:  reason = "TLS version below 1.3"; break;
        case SF_ERR_KEM_NOT_PQ:   reason = "key exchange is not PQ-hybrid"; break;
        case SF_ERR_WEAK_ALGO:    reason = "weak certificate/key algorithm"; break;
        case SF_ERR_CERT_INVALID: reason = "TLS handshake/cert validation failed (site may not support TLS 1.3)"; break;
        case SF_ERR_CERT_NOT_PQ:  reason = "strict PQ signature missing"; break;
        case SF_ERR_NETWORK:      reason = "network error"; break;
        case SF_ERR_TOO_MANY_REDIRECTS: reason = "too many redirects"; break;
        default:                  reason = "fetch error"; break;
    }
    char bypass[768];
    bypass[0] = '\0';
    if (allowlisted) {
        if (host_from_url(url, host, sizeof host))
            snprintf(bypass, sizeof bypass,
                "\n\n'%s' is on your allowlist, so Freedom already retried it accepting\n"
                "TLS 1.2 and weak-but-valid crypto. This failure is real: the certificate\n"
                "is untrusted/expired, the network failed, or TLS is below 1.2.", host);
    } else if (ss == SF_ERR_TLS_VERSION || ss == SF_ERR_WEAK_ALGO
               || ss == SF_ERR_CERT_INVALID || ss == SF_ERR_CERT_NOT_PQ
               || ss == SF_ERR_KEM_NOT_PQ) {
        if (host_from_url(url, host, sizeof host))
            snprintf(bypass, sizeof bypass,
                "\n\nThis site is below Freedom's security standard. To navigate it\n"
                "anyway, add '%s' to allow.conf -- your sovereign per-host override:\n"
                "TLS 1.2, a classical key exchange, and weak-but-valid certificates\n"
                "are then accepted for this host (with a warning). The chain is still\n"
                "authenticated, so you reach the real site, not an impostor.\n"
                "Ctrl+Shift+E relaxes only a weak certificate for this session.", host);
    }
    char msg[1536];
    snprintf(msg, sizeof msg,
             "Failed to load '%s'.\nStatus %d: %s.\n\n"
             "Freedom rejects TLS < 1.3, a site (leaf) certificate with RSA\n"
             "< 3072, any SHA-1 signature in the chain, and certificates that\n"
             "fail strict validation. A host that cannot do a post-quantum key\n"
             "exchange is loaded over classical TLS 1.3 with a warning, not\n"
             "blocked.\n%s",
             url, (int)ss, reason, bypass);
    clear_doc(w);
    set_cache(w, NULL, 0, NULL);
    browser_set_page(&w->bs, NULL, msg, 1);
}

/* Starts a navigation. Network loads are ASYNCHRONOUS: prepare_fetch (pure, fast)
 * runs here, then fetch_launch hands the blocking transfer to a worker thread and we
 * return immediately -- the event loop stays responsive and the previous page stays
 * on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local files are synchronous (no network). Every call bumps net_gen so an older
 * in-flight fetch is discarded when it completes. */
static void do_load(browser_window *w, const char *url) {
    if (url == NULL) return;
    w->net_gen++;        /* new navigation: supersede any in-flight fetch */
    w->menu_open = 0;

    if (strcmp(url, "about:blank") == 0) {
        clear_doc(w);
        w->scroll = 0.0; w->ua_field_focused = 0; w->focused_input = -1;
        w->loading = 0;
        set_cache(w, NULL, 0, NULL);
        browser_set_page(&w->bs, "Freedom", "", 0);
        return;
    }

    if (is_https_url(url) || is_overlay_http_url(url)) {
        /* Pre-fetch gates (host filter, exception, allowlist, Tor/I2P route) are
         * shared with the POST path so the two can never diverge (Zero Trust). */
        sf_config cfg;
        fetch_prep pr;
        if (!prepare_fetch(w, url, &cfg, &pr)) {
            clear_doc(w);
            w->scroll = 0.0; w->ua_field_focused = 0; w->focused_input = -1;
            w->loading = 0;
            set_cache(w, NULL, 0, NULL);
            browser_set_page(&w->bs, NULL, pr.err, 1);
            return;
        }
        if (!fetch_launch(w, url, &cfg, pr.allowlisted, 0, NULL, 0, NULL)) {
            clear_doc(w);
            w->scroll = 0.0; w->loading = 0;
            set_cache(w, NULL, 0, NULL);
            browser_set_page(&w->bs, NULL,
                "Could not start the request (out of resources).", 1);
            return;
        }
        show_busy(w); /* spinner on; the old page stays visible until the result lands */
        return;
    }

    /* Local file: synchronous (no network, instant). */
    clear_doc(w);
    w->scroll = 0.0; w->ua_field_focused = 0; w->focused_input = -1;
    w->loading = 0;
    size_t html_len = 0;
    char *html = read_file(url, &html_len);
    if (html == NULL) {
        char msg[256];
        snprintf(msg, sizeof msg, "Cannot read file '%s': %s.", url, strerror(errno));
        set_cache(w, NULL, 0, NULL);
        browser_set_page(&w->bs, NULL, msg, 1);
        return;
    }
    set_cache(w, html, html_len, NULL);
    render_current(w);
}

/* --- tabs --- */

/* Parks the active tab's live state into its slot (a shallow move: the slot and the
 * live fields briefly alias the same allocations; the live fields are overwritten
 * by tab_restore before anything is freed). */
static void tab_save(browser_window *w) {
    tab_ctx *c = &w->tab_slots[w->active_tab];
    c->bs = w->bs;
    c->doc = w->doc;
    c->caps = w->caps;
    c->scroll = w->scroll;
    c->content_total_h = w->content_total_h;
    c->inputs = w->inputs; c->input_count = w->input_count; c->focused_input = w->focused_input;
    c->images = w->images; c->image_count = w->image_count;
    c->cur_html = w->cur_html; c->cur_html_len = w->cur_html_len; c->cur_top = w->cur_top;
    c->loading = w->loading;
    c->hover_href = w->hover_href;
}

/* Loads the active tab's slot into the live fields (the inverse move). */
static void tab_restore(browser_window *w) {
    tab_ctx *c = &w->tab_slots[w->active_tab];
    w->bs = c->bs;
    w->doc = c->doc;
    w->caps = c->caps;
    w->scroll = c->scroll;
    w->content_total_h = c->content_total_h;
    w->inputs = c->inputs; w->input_count = c->input_count; w->focused_input = c->focused_input;
    w->images = c->images; w->image_count = c->image_count;
    w->cur_html = c->cur_html; w->cur_html_len = c->cur_html_len; w->cur_top = c->cur_top;
    w->loading = c->loading;
    w->hover_href = c->hover_href;
}

/* Frees the LIVE page's owned state (used when closing the foreground tab). */
static void free_live_page(browser_window *w) {
    clear_doc(w);                 /* inputs, images, doc, hover_href */
    free(w->cur_html); w->cur_html = NULL;
    free(w->cur_top);  w->cur_top = NULL;
    browser_free(&w->bs);
    memset(&w->bs, 0, sizeof w->bs);
}

/* Frees a parked (inactive) tab's owned state. */
static void tab_ctx_release(tab_ctx *c) {
    if (c->images != NULL) {
        for (size_t i = 0; i < c->image_count; ++i)
            if (c->images[i].surface != NULL) cairo_surface_destroy(c->images[i].surface);
        free(c->images);
    }
    free(c->inputs);
    if (c->doc != NULL) rd_free(c->doc);
    free(c->cur_html);
    free(c->cur_top);
    browser_free(&c->bs);
    memset(c, 0, sizeof *c);
}

/* Brings tab idx to the foreground (no network: the cached doc is restored). */
static void tab_switch(browser_window *w, int idx) {
    if (idx < 0 || idx >= w->tab_count || idx == w->active_tab) return;
    /* Single-load model: leaving a tab abandons its in-flight fetch (the discarded
     * result is dropped by the generation check). Concurrent per-tab loading is future
     * work. Clear the spinner now so the parked tab does not show it on return. */
    w->net_gen++;
    w->loading = 0;
    tab_save(w);
    w->active_tab = idx;
    tab_restore(w);
    w->menu_open = 0;
    w->url_bar_focused = 0;
    const char *u = browser_current_url(&w->bs);
    browser_set_url_bar(&w->bs, (u != NULL) ? u : "");
    redraw(w);
}

/* Opens a new tab after the active one and loads url (the start page when NULL). */
static void tab_new(browser_window *w, const char *url) {
    if (w->tab_count >= UI_MAX_TABS) {
        browser_set_status(&w->bs, "Tab limit reached.", now_ms());
        redraw(w);
        return;
    }
    w->loading = 0; /* clear the current tab's spinner before parking it (its fetch,
                     * if any, is abandoned: do_load below bumps the generation) */
    tab_save(w);
    int idx = w->active_tab + 1;
    for (int i = w->tab_count; i > idx; --i) w->tab_slots[i] = w->tab_slots[i - 1];
    memset(&w->tab_slots[idx], 0, sizeof w->tab_slots[idx]); /* drop the stale duplicate */
    w->tab_count++;
    w->active_tab = idx;

    /* Blank live page, then load. */
    w->doc = NULL; w->hover_href = NULL;
    w->inputs = NULL; w->input_count = 0; w->focused_input = -1;
    w->images = NULL; w->image_count = 0;
    w->cur_html = NULL; w->cur_html_len = 0; w->cur_top = NULL;
    w->scroll = 0.0; w->content_total_h = 0.0; w->loading = 0;
    w->caps = rdp_caps_safe();
    memset(&w->bs, 0, sizeof w->bs);
    if (browser_init(&w->bs) != BROWSER_OK) { browser_set_page(&w->bs, "Freedom", "", 0); }
    w->url_bar_focused = 1;
    do_load(w, (url != NULL) ? url : "docs/index.html");
    browser_url_bar_clear(&w->bs);
    redraw(w);
}

/* Closes tab idx. Never closes the last tab (always keeps one). */
static void uitab_close(browser_window *w, int idx) {
    if (w->tab_count <= 1 || idx < 0 || idx >= w->tab_count) return;

    if (idx == w->active_tab) {
        /* The active tab may have a fetch in flight; abandon it so its result is not
         * later painted onto whichever tab becomes active. Closing a BACKGROUND tab
         * leaves the active tab's load untouched (its generation still matches). */
        w->net_gen++;
        free_live_page(w);
    } else {
        tab_ctx_release(&w->tab_slots[idx]);
    }
    for (int i = idx; i < w->tab_count - 1; ++i) w->tab_slots[i] = w->tab_slots[i + 1];
    memset(&w->tab_slots[w->tab_count - 1], 0, sizeof w->tab_slots[0]);
    w->tab_count--;

    if (idx == w->active_tab) {
        if (w->active_tab >= w->tab_count) w->active_tab = w->tab_count - 1;
        tab_restore(w);
        const char *u = browser_current_url(&w->bs);
        browser_set_url_bar(&w->bs, (u != NULL) ? u : "");
        w->menu_open = 0; w->url_bar_focused = 0;
    } else if (idx < w->active_tab) {
        w->active_tab--;
    }
    redraw(w);
}

/* Width of one tab: the strip (minus the trailing + button) split evenly, clamped to
 * a readable maximum and a grabbable floor (many tabs shrink, they never vanish). */
static double tab_width(const browser_window *w) {
    double avail = (double)w->width - UI_TAB_NEW_W;
    if (avail < 1.0) avail = 1.0;
    double tw = avail / (double)w->tab_count;
    if (tw > UI_TAB_MAX_W) tw = UI_TAB_MAX_W;
    if (tw < 36.0) tw = 36.0;
    return tw;
}

/* X of the "new tab" (+) button: right after the last tab, clamped to the reserved
 * slot at the right edge. */
static double newtab_x(const browser_window *w) {
    double after = (double)w->tab_count * tab_width(w);
    double maxx = (double)w->width - UI_TAB_NEW_W;
    return (after < maxx) ? after : maxx;
}

/* Title shown on a tab: the page title, else the URL, else a placeholder. */
static const char *tab_title(const browser_window *w, int i) {
    const browser_state *bs = (i == w->active_tab) ? &w->bs : &w->tab_slots[i].bs;
    if (bs->page_title != NULL && bs->page_title[0] != '\0') return bs->page_title;
    if (bs->url_bar[0] != '\0') return bs->url_bar;
    return "New tab";
}

/* --- painting --- */

static void toolbar_rects(const browser_window *w,
                          double *back_x, double *fwd_x,
                          double *url_x, double *url_w,
                          double *go_x, double *menu_x);

/* Top of the tab strip: directly under the client-side titlebar (or at the surface
 * top under server-side decorations). */
static double tabbar_top(const browser_window *w) {
    return w->use_csd ? UI_TITLEBAR_H : 0.0;
}

/* Top of the toolbar: under the tab strip, which is always reserved. The whole
 * content area derives from this, so adding the strip reflows everything below it. */
static double toolbar_top(const browser_window *w) {
    return tabbar_top(w) + UI_TABBAR_H;
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

/* Width available to page content: the window width minus the left/right margins
 * and the always-reserved scrollbar gutter. The single source of truth shared by
 * the painter and the click/link hit-tests so the laid-out lines and the hit
 * geometry cannot drift. */
static double content_width(const browser_window *w) {
    double cw = (double)w->width - 2.0 * w->theme.content_margin - UI_SCROLLBAR_W;
    if (cw < 1.0) cw = 1.0;
    return cw;
}

/* Geometry of the vertical scrollbar in surface coordinates, plus the current
 * thumb position. Returns 0 (and leaves outputs untouched) when the content fits
 * and no scrollbar is needed. content_total_h is the height cached by the last
 * paint; the track spans the content area down to the bottom edge. */
static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
                             double *track_h, double *thumb_y, double *thumb_h) {
    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);
    double total = w->content_total_h;
    if (content_h <= 0.0 || total <= content_h) return 0;

    double trh = (double)w->height - content_top;
    if (trh < 1.0) trh = 1.0;
    double thh = trh * (content_h / total);
    if (thh < UI_SCROLLBAR_MIN) thh = UI_SCROLLBAR_MIN;
    if (thh > trh) thh = trh;

    double max_scroll = total - content_h;
    double frac = (max_scroll > 0.0) ? (w->scroll / max_scroll) : 0.0;
    if (frac < 0.0) frac = 0.0;
    if (frac > 1.0) frac = 1.0;

    *track_x = (double)w->width - UI_SCROLLBAR_W;
    *track_y = content_top;
    *track_h = trh;
    *thumb_h = thh;
    *thumb_y = content_top + frac * (trh - thh);
    return 1;
}

/* Maps the current pointer Y (less the grab offset) to a scroll offset while the
 * thumb is being dragged, then repaints. No-op when there is no scrollbar. */
static void scrollbar_drag_to(browser_window *w) {
    double tx, ty, trh, thy, thh;
    if (!scrollbar_metrics(w, &tx, &ty, &trh, &thy, &thh)) return;
    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);
    double max_scroll = w->content_total_h - content_h;
    if (max_scroll < 0.0) max_scroll = 0.0;
    double travel = trh - thh;
    double frac = (travel > 0.0) ? ((w->ptr_y - w->scroll_grab_dy) - ty) / travel : 0.0;
    if (frac < 0.0) frac = 0.0;
    if (frac > 1.0) frac = 1.0;
    w->scroll = frac * max_scroll;
    redraw(w);
}

/* Paints the scrollbar track and thumb. The thumb highlights while hovered or
 * dragged, the same affordance the toolbar buttons and links get. */
static void draw_scrollbar(cairo_t *cr, const browser_window *w) {
    double tx, ty, trh, thy, thh;
    if (!scrollbar_metrics(w, &tx, &ty, &trh, &thy, &thh)) return;
    const ui_theme *th = &w->theme;

    set_rgb(cr, th->scrollbar_track);
    cairo_rectangle(cr, tx, ty, UI_SCROLLBAR_W, trh);
    cairo_fill(cr);

    int hot = w->dragging_scroll
           || (w->ptr_x >= tx && w->ptr_x <= tx + UI_SCROLLBAR_W
               && w->ptr_y >= thy && w->ptr_y <= thy + thh);
    set_rgb(cr, hot ? th->scrollbar_thumb_hot : th->scrollbar_thumb);
    cairo_rectangle(cr, tx + UI_SCROLLBAR_PAD, thy + UI_SCROLLBAR_PAD,
                    UI_SCROLLBAR_W - 2.0 * UI_SCROLLBAR_PAD, thh - 2.0 * UI_SCROLLBAR_PAD);
    cairo_fill(cr);
}

/* Interactive-resize edge for a pointer near the window border (CSD only). Returns
 * an xdg_toplevel resize edge, or 0 (NONE) away from the edges. The top edge is
 * excluded: it belongs to the titlebar (move / window buttons). */
static uint32_t resize_edge_at(const browser_window *w, double x, double y) {
    double m = UI_RESIZE_MARGIN;
    int left   = x < m;
    int right  = x > (double)w->width - m;
    int bottom = y > (double)w->height - m;
    /* The side edges live in the page margins; keep them out of the titlebar and
     * toolbar rows so the chrome buttons stay clickable. */
    if (y < toolbar_top(w) + UI_TOOLBAR_H) { left = 0; right = 0; }
    if (bottom && left)  return XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_LEFT;
    if (bottom && right) return XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT;
    if (bottom) return XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM;
    if (left)   return XDG_TOPLEVEL_RESIZE_EDGE_LEFT;
    if (right)  return XDG_TOPLEVEL_RESIZE_EDGE_RIGHT;
    return XDG_TOPLEVEL_RESIZE_EDGE_NONE;
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

/* Which toolbar button (if any) is at (px, py). Shared by the hover highlight and
 * the cursor shape so they cannot drift from the click hit-test. */
static ui_hot toolbar_button_at(const browser_window *w, double px, double py) {
    if (w->menu_open) return UI_HOT_NONE;
    double ttop = toolbar_top(w);
    if (py < ttop || py >= ttop + UI_TOOLBAR_H) return UI_HOT_NONE;
    double back_x, fwd_x, url_x, url_w, go_x, menu_x;
    toolbar_rects(w, &back_x, &fwd_x, &url_x, &url_w, &go_x, &menu_x);
    if (px >= menu_x) return UI_HOT_MENU;
    if (px >= go_x && px < menu_x) return UI_HOT_GO;
    if (px >= fwd_x && px < fwd_x + UI_BTN_W) return UI_HOT_FWD;
    if (px >= back_x && px < back_x + UI_BTN_W) return UI_HOT_BACK;
    return UI_HOT_NONE;
}

/* A hovered button is "actionable" (gets the hand cursor) when clicking it would
 * do something: Go/menu always, Back/Forward only when there is history. */
static int hot_actionable(const browser_window *w, ui_hot hot) {
    switch (hot) {
        case UI_HOT_GO: case UI_HOT_MENU: return 1;
        case UI_HOT_BACK: return browser_can_back(&w->bs);
        case UI_HOT_FWD:  return browser_can_forward(&w->bs);
        default: return 0;
    }
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
    int         bold, italic, underline;
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
    int             bg_rgb;        /* author background-color packed 0xRRGGBB, or -1 */
    double          x_off;         /* extra horizontal offset (flex/grid column), 0 normally */
    const rd_block *blk;           /* RC_IMAGE: source image block */
} rc_row;

typedef struct rc_layout {
    rc_frag *frags; size_t nfrag, capfrag;
    rc_row  *rows;  size_t nrow,  caprow;
    double   total_h;
} rc_layout;

typedef struct rc_state {
    double cur_top, pending_gap, pen_x, line_asc, line_desc;
    double prev_bottom;  /* bottom margin (px) of the last block, for CSS margin collapsing */
    double indent_px;    /* left indent of the current line (list nesting), applied as row x_off */
    int    line_open, banner;
    int    bg_rgb;       /* current block's author background-color, or -1 */
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

static void content_font(cairo_t *cr, double size, int bold, int italic) {
    cairo_select_font_face(cr, "sans-serif",
                           italic ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL,
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
                        double *size, int *bold, int *italic, int *underline, ui_rgb *color) {
    *bold = 0; *italic = 0; *underline = 0; *size = th->body_font; *color = th->text;
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
    /* Inline emphasis (b/strong/i/em) layers on top of the block's base style: a
     * heading stays bold, a bold link stays a link. */
    if (b->bold) *bold = 1;
    if (b->italic) *italic = 1;
}

/* Vertical margins (px) of a block from the user-agent box model (box_style),
 * resolved against the block's own font size (em -> px). The user-agent notice has
 * no HTML tag, so it keeps the theme's paragraph gap as a separator and does not
 * regress. The single place that turns "what tag is this" into block spacing. */
static void block_margins(const ui_theme *th, const rd_block *b,
                          double *top_px, double *bottom_px) {
    const char *tag = rd_block_tag(b);
    if (tag == NULL) { *top_px = th->paragraph_gap; *bottom_px = th->paragraph_gap; return; }
    bx_box box = bx_default_for_tag(tag);
    double size; int bold, italic, underline; ui_rgb color;
    block_style(th, b, &size, &bold, &italic, &underline, &color);
    *top_px = box.margin.top * size;
    *bottom_px = box.margin.bottom * size;
}

static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th) {
    if (!s->line_open) return;
    double h = (s->line_asc + s->line_desc) * th->line_spacing;
    rc_row *r = rc_add_row(L);
    if (r != NULL) {
        r->kind = RC_TEXT; r->top = s->cur_top; r->height = h; r->ascent = s->line_asc;
        r->first = s->line_first; r->count = L->nfrag - s->line_first;
        r->banner = s->banner; r->bg_rgb = s->bg_rgb; r->x_off = s->indent_px; r->blk = NULL;
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
                      const char *text, double size, int bold, int italic, int underline,
                      ui_rgb color, double content_w, const char *href) {
    content_font(cr, size, bold, italic);
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
            f->bold = bold; f->italic = italic; f->underline = underline; f->color = color;
            f->text = text + ws; f->len = wl; f->href = href;
        }
        s->pen_x += ww;
        if (fe.ascent  > s->line_asc)  s->line_asc  = fe.ascent;
        if (fe.descent > s->line_desc) s->line_desc = fe.descent;
    }
}

/* Flows one text/link/notice block into L at content_w using state s. The caller
 * sets s->bg_rgb (the block's author background, or -1) beforehand; the foreground
 * color and link/heading styling are derived here. */
static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                            rc_state *s, const ui_theme *th, const rd_block *b,
                            double content_w) {
    double size; int bold, italic, underline; ui_rgb color;
    block_style(th, b, &size, &bold, &italic, &underline, &color);
    if (!w->force_theme && b->fg_rgb >= 0) color = rgb_from_packed(b->fg_rgb);
    const char *href = (b->kind == RD_LINK) ? b->href : NULL;
    if (b->kind == RD_NOTICE) {
        s->banner = 1;
        flow_text(cr, L, s, th, b->text, size, bold, italic, underline, color, content_w, href);
        flush_line(L, s, th);
        s->banner = 0;
    } else {
        flow_text(cr, L, s, th, b->text, size, bold, italic, underline, color, content_w, href);
    }
}

/* Lays a contiguous range [start,end) of blocks that share one author flex/grid
 * container into equal columns, then appends the positioned rows to L and advances
 * s->cur_top. Each block is one item (basic: items are not grouped). Column geometry
 * and row packing come from box_tree/flex_layout (already tested); this only flows
 * the text and translates the rows. Visual-only structure, applied by default
 * (decoupled from caps.css, which gates only author colors). A run that falls
 * outside the engine's range degrades to plain vertical flow. */
static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                             rc_state *s, const ui_theme *th, double content_w,
                             const rd_doc *doc, size_t start, size_t end) {
    size_t n = end - start;
    const rd_block *head = rd_at(doc, start);
    int is_grid = (head->cont_display == BX_DISPLAY_GRID);
    size_t ncols = is_grid ? (size_t)head->cont_cols : n;
    if (ncols < 1) ncols = 1;

    if (n == 0 || n > BT_MAX_CHILDREN || ncols > BT_MAX_CHILDREN) {
        for (size_t k = start; k < end; ++k) {
            s->bg_rgb = (!w->force_theme) ? rd_at(doc, k)->bg_rgb : -1;
            flow_text_block(cr, w, L, s, th, rd_at(doc, k), content_w);
        }
        return;
    }

    flush_line(L, s, th);
    double base_top = s->cur_top + ((L->nrow > 0) ? s->pending_gap : 0.0);
    s->pending_gap = 0;

    bt_node kids[BT_MAX_CHILDREN];
    bt_node root;
    memset(&root, 0, sizeof root);
    memset(kids, 0, sizeof kids[0] * n);
    root.display = BX_DISPLAY_GRID;   /* flex row == grid with n columns, one row */
    root.grid_cols = ncols;
    root.gap = (double)head->cont_gap;
    root.justify = (fx_justify)head->cont_justify;
    root.children = kids;
    root.child_count = n;
    for (size_t k = 0; k < n; ++k) kids[k].display = BX_DISPLAY_BLOCK;

    /* First pass: column widths (heights still 0). */
    if (bt_layout(&root, content_w) != BT_OK) {
        for (size_t k = start; k < end; ++k) {
            s->bg_rgb = (!w->force_theme) ? rd_at(doc, k)->bg_rgb : -1;
            flow_text_block(cr, w, L, s, th, rd_at(doc, k), content_w);
        }
        return;
    }

    /* Flow each item into L at its column width; record its row range and height. */
    size_t row_start[BT_MAX_CHILDREN], row_count[BT_MAX_CHILDREN];
    for (size_t k = 0; k < n; ++k) {
        rc_state si;
        memset(&si, 0, sizeof si);
        si.bg_rgb = -1;   /* container item backgrounds are out of scope (basic) */
        double cw = (kids[k].w < 1.0) ? 1.0 : kids[k].w;
        size_t sr = L->nrow;
        flow_text_block(cr, w, L, &si, th, rd_at(doc, start + k), cw);
        flush_line(L, &si, th);
        row_start[k] = sr;
        row_count[k] = L->nrow - sr;
        kids[k].content_h = si.cur_top;
    }

    /* Second pass: final row packing + y now that the heights are known. */
    if (bt_layout(&root, content_w) != BT_OK) return;

    /* Translate each item's rows into its column rectangle. */
    for (size_t k = 0; k < n; ++k) {
        for (size_t r = row_start[k]; r < row_start[k] + row_count[k]; ++r) {
            L->rows[r].top += base_top + kids[k].y;
            L->rows[r].x_off = kids[k].x;
        }
    }
    s->cur_top = base_top + root.h;
}

static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                       rc_layout *L) {
    const rd_doc *doc = w->doc;
    const ui_theme *th = &w->theme;
    memset(L, 0, sizeof *L);
    rc_state s;
    memset(&s, 0, sizeof s);
    s.bg_rgb = -1;  /* 0 is opaque black; no background until a block sets one */

    for (size_t i = 0; i < rd_count(doc); ++i) {
        const rd_block *b = rd_at(doc, i);
        /* Hidden controls are never painted (their value still submits). */
        if (b->kind == RD_INPUT && b->input_type == PV_IN_HIDDEN) continue;

        /* A maximal run of blocks sharing one author flex/grid container (carried
         * by default; layout is structure, not gated by caps.css) is laid out in
         * columns and then skipped. */
        if (b->cont_id >= 0 &&
            (b->cont_display == BX_DISPLAY_FLEX || b->cont_display == BX_DISPLAY_GRID)) {
            size_t j = i + 1;
            while (j < rd_count(doc) && rd_at(doc, j)->cont_id == b->cont_id) ++j;
            double mt, mb;
            block_margins(th, b, &mt, &mb);
            s.pending_gap = (s.prev_bottom > mt) ? s.prev_bottom : mt;
            layout_container(cr, w, L, &s, th, content_w, doc, i, j);
            s.prev_bottom = mb;
            i = j - 1;  /* the loop's ++i moves past the container */
            continue;
        }

        int standalone = (b->kind == RD_IMAGE || b->kind == RD_NOTICE
                       || b->kind == RD_HEADING || b->kind == RD_INPUT);
        if (standalone || b->block_break) {
            flush_line(L, &s, th);
            /* Space before this block = its top margin collapsed with the previous
             * block's bottom margin (CSS adjacent-margin collapsing, basic). */
            double mt, mb;
            block_margins(th, b, &mt, &mb);
            s.pending_gap = (s.prev_bottom > mt) ? s.prev_bottom : mt;
            s.prev_bottom = mb;
        }

        if (b->kind == RD_INPUT) {
            content_font(cr, th->body_font, 0, 0);
            cairo_font_extents_t fe;
            cairo_font_extents(cr, &fe);
            double h = fe.height + 2.0 * UI_INPUT_PAD;
            double top = s.cur_top + (L->nrow > 0 ? s.pending_gap : 0.0);
            s.pending_gap = 0;
            rc_row *r = rc_add_row(L);
            if (r != NULL) {
                r->kind = RC_INPUT; r->top = top; r->height = h; r->ascent = fe.ascent;
                r->first = 0; r->count = 0; r->banner = 0; r->bg_rgb = -1; r->x_off = 0.0; r->blk = b;
            }
            s.cur_top = top + h;
            continue;
        }

        if (b->kind == RD_IMAGE) {
            content_font(cr, th->body_font, 0, 0);
            cairo_font_extents_t fe;
            cairo_font_extents(cr, &fe);
            /* A decoded image sizes the row to its on-screen height; otherwise the
             * row is a single-line placeholder box. Same box width used to paint. */
            double dw, dh;
            double box_w = content_w - 2.0 * th->image_box_pad;
            double h = image_display_size(w, b, box_w, &dw, &dh)
                       ? dh + 2.0 * th->image_box_pad
                       : fe.height + 2.0 * th->image_box_pad;
            double top = s.cur_top + (L->nrow > 0 ? s.pending_gap : 0.0);
            s.pending_gap = 0;
            rc_row *r = rc_add_row(L);
            if (r != NULL) {
                r->kind = RC_IMAGE; r->top = top; r->height = h; r->ascent = fe.ascent;
                r->first = 0; r->count = 0; r->banner = 0; r->bg_rgb = -1; r->x_off = 0.0; r->blk = b;
            }
            s.cur_top = top + h;
            continue;
        }

        /* Author background travels on the row (unless the theme is forced); the
         * foreground tints the fragments inside flow_text_block. */
        s.bg_rgb = (!w->force_theme) ? b->bg_rgb : -1;
        /* List items indent the whole block by their nesting depth; the marker text
         * was prepended by page_view. Non-list blocks have indent 0. The available
         * text width shrinks by the indent so wrapped lines stay inside the column. */
        s.indent_px = (double)b->indent * UI_LIST_INDENT;
        double avail_w = content_w - s.indent_px;
        if (avail_w < 1.0) avail_w = 1.0;
        flow_text_block(cr, w, L, &s, th, b, avail_w);
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
    content_font(cr, th->body_font, 0, 0);
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
        content_font(cr, th->body_font, 0, 0);
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

    content_font(cr, th->body_font, 0, 0);
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

/* Paints one RD_IMAGE row inside the content rectangle: the decoded image blitted
 * and scaled to fit the content width (the bytes were fetched and decoded in the
 * confined worker), or, when no image is available (blocked / policy-rejected /
 * decode failed), a bordered placeholder box labelled with the render_policy
 * decision plus the alt text. The on-screen size comes from image_display_size, the
 * same source of truth the layout used to size this row, so paint and layout agree. */
static void paint_image_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                            double left, double ry, double content_w, double row_h) {
    const ui_theme *th = &w->theme;
    const double pad = th->image_box_pad;
    double box_w = content_w - 2.0 * pad;

    double dw, dh;
    if (image_display_size(w, blk, box_w, &dw, &dh)) {
        const ui_image *im = find_image(w, blk); /* non-NULL with surface, nat_w > 0 */
        double scale = dw / (double)im->nat_w;
        cairo_save(cr);
        cairo_translate(cr, left + pad, ry + pad);
        cairo_rectangle(cr, 0.0, 0.0, dw, dh);
        cairo_clip(cr);
        cairo_scale(cr, scale, scale); /* uniform => aspect preserved */
        cairo_set_source_surface(cr, im->surface, 0.0, 0.0);
        cairo_pattern_set_filter(cairo_get_source(cr), CAIRO_FILTER_GOOD);
        cairo_paint(cr);
        cairo_restore(cr);
        return;
    }

    int blocked = (blk->img_decision != RDP_IMG_ALLOW);
    set_rgb(cr, blocked ? th->image_blocked : th->image_box);
    cairo_set_line_width(cr, 1.0);
    cairo_rectangle(cr, left, ry, content_w, row_h);
    cairo_stroke(cr);

    content_font(cr, th->body_font, 0, 0);
    cairo_save(cr);
    cairo_rectangle(cr, left + pad, ry, content_w - 2.0 * pad, row_h);
    cairo_clip(cr);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    cairo_move_to(cr, left + pad, ry + fe.ascent + pad);
    char label[1024];
    const char *alt = (blk->text != NULL) ? blk->text : "";
    snprintf(label, sizeof label, "%s%s%s",
             rd_image_label(blk->img_decision), alt[0] ? " : " : "", alt);
    cairo_show_text(cr, label);
    cairo_restore(cr);
}

/* Paints the structured document into the content rectangle, honouring scroll. */
/* Paints one laid-out row at vertical position ry. Shared by the on-screen painter
 * and the PDF exporter so both render identically (same fonts, colours, emphasis,
 * links and backgrounds). band_w is the full-bleed width for notice banners (the
 * window width on screen, the page width in the PDF). show_hover draws the link
 * hover highlight (on screen only; suppressed when exporting). */
static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
                              const rc_row *r, double left, double ry,
                              double content_w, double band_w, int show_hover) {
    const ui_theme *th = &w->theme;

    if (r->kind == RC_IMAGE && r->blk != NULL) {
        paint_image_row(cr, w, r->blk, left, ry, content_w, r->height);
        return;
    }
    if (r->kind == RC_INPUT && r->blk != NULL) {
        draw_input_row(cr, w, r->blk, left, content_w, ry, r->ascent, r->height);
        return;
    }

    if (r->banner) {
        set_rgb(cr, th->notice_bg);
        cairo_rectangle(cr, 0.0, ry, band_w, r->height);
        cairo_fill(cr);
    } else if (r->bg_rgb >= 0) {
        /* Author background-color behind the block's text (content box). */
        set_rgb(cr, rgb_from_packed(r->bg_rgb));
        cairo_rectangle(cr, left, ry, content_w, r->height);
        cairo_fill(cr);
    }
    double baseline = ry + r->ascent;
    double rx = left + r->x_off;  /* row origin (column offset for flex/grid) */
    for (size_t k = r->first; k < r->first + r->count && k < L->nfrag; ++k) {
        const rc_frag *f = &L->frags[k];
        /* Highlight the link under the pointer (all fragments of that link share
         * its href pointer into the doc). */
        if (show_hover && f->href != NULL && f->href == w->hover_href) {
            set_rgb(cr, th->link_hover_bg);
            cairo_rectangle(cr, rx + f->x, ry, f->width, r->height);
            cairo_fill(cr);
        }
        content_font(cr, f->font_size, f->bold, f->italic);
        set_rgb(cr, f->color);
        cairo_move_to(cr, rx + f->x, baseline);
        draw_slice(cr, f->text, f->len);
        if (f->underline) {
            double uy = baseline + f->font_size * UI_UNDERLINE_OFFSET;
            cairo_set_line_width(cr, UI_UNDERLINE_THICK);
            cairo_move_to(cr, rx + f->x, uy);
            cairo_line_to(cr, rx + f->x + f->width, uy);
            cairo_stroke(cr);
        }
    }
}

static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                             double content_h) {
    const ui_theme *th = &w->theme;
    double left = th->content_margin;
    double content_w = content_width(w);

    rc_layout L;
    layout_doc(cr, w, content_w, &L);
    w->content_total_h = L.total_h;  /* cached for the scrollbar */

    double max_scroll = L.total_h - content_h;
    if (max_scroll < 0.0) max_scroll = 0.0;
    if (w->scroll < 0.0) w->scroll = 0.0;
    if (w->scroll > max_scroll) w->scroll = max_scroll;
    double origin = content_top + th->content_margin - w->scroll;

    for (size_t i = 0; i < L.nrow; ++i) {
        const rc_row *r = &L.rows[i];
        double ry = origin + r->top;
        if (ry + r->height < content_top || ry > content_top + content_h) continue;
        paint_content_row(cr, w, &L, r, left, ry, content_w, (double)w->width, 1);
    }
    rc_free(&L);
}

/* PDF page geometry: US Letter at 72 dpi (Cairo's PDF user-space unit is 1 point =
 * 1/72 inch), with a uniform margin. */
#define PDF_PAGE_W  612.0
#define PDF_PAGE_H  792.0
#define PDF_MARGIN  48.0

/* Saves the current page as a vector PDF (selectable text, infinite zoom): Cairo
 * re-draws the SAME render_doc display list onto a cairo_pdf_surface_t instead of
 * the screen. Pure helpers (pdf_export) choose a safe output path from the hostile
 * page title and paginate the rows; this orchestrator only does the Cairo I/O. The
 * page is laid out in a clean light theme so the print is dark-on-white. */
static void export_pdf(browser_window *w) {
    if (w->doc == NULL || rd_count(w->doc) == 0) {
        browser_set_status(&w->bs, "Nothing to export to PDF.", now_ms());
        redraw(w);
        return;
    }

    /* Output directory: $XDG_DOWNLOAD_DIR, else $HOME, else the current directory. */
    const char *dir = getenv("XDG_DOWNLOAD_DIR");
    if (dir == NULL || dir[0] == '\0') dir = getenv("HOME");
    if (dir == NULL || dir[0] == '\0') dir = ".";

    const char *title = (w->bs.page_title != NULL && w->bs.page_title[0] != '\0')
                        ? w->bs.page_title : PE_FALLBACK_NAME;
    char path[PE_NAME_MAX + 4096u];
    if (pe_build_path(dir, title, path, sizeof path) != PE_OK) {
        browser_set_status(&w->bs, "Could not build a safe PDF path.", now_ms());
        redraw(w);
        return;
    }

    cairo_surface_t *surf = cairo_pdf_surface_create(path, PDF_PAGE_W, PDF_PAGE_H);
    if (cairo_surface_status(surf) != CAIRO_STATUS_SUCCESS) {
        cairo_surface_destroy(surf);
        browser_set_status(&w->bs, "Could not create the PDF file.", now_ms());
        redraw(w);
        return;
    }
    cairo_t *cr = cairo_create(surf);

    /* Lay out (and colour fragments) in a light theme so the PDF is print-friendly;
     * restore the live theme afterwards. layout_doc reads w->theme for colours. */
    ui_theme saved = w->theme;
    w->theme = ui_theme_for(UI_THEME_LIGHT);

    double content_w = PDF_PAGE_W - 2.0 * PDF_MARGIN;
    double page_content_h = PDF_PAGE_H - 2.0 * PDF_MARGIN;

    rc_layout L;
    layout_doc(cr, w, content_w, &L);

    size_t pages = 0;
    double *tops = NULL, *heights = NULL, *yof = NULL;
    int *pageof = NULL;
    if (L.nrow > 0) {
        tops    = (double *)malloc(L.nrow * sizeof *tops);
        heights = (double *)malloc(L.nrow * sizeof *heights);
        yof     = (double *)malloc(L.nrow * sizeof *yof);
        pageof  = (int *)malloc(L.nrow * sizeof *pageof);
    }
    if (L.nrow > 0 && tops != NULL && heights != NULL && yof != NULL && pageof != NULL) {
        for (size_t i = 0; i < L.nrow; ++i) {
            tops[i] = L.rows[i].top;
            heights[i] = L.rows[i].height;
        }
        pages = pe_paginate(tops, heights, L.nrow, page_content_h, pageof, yof);
        for (size_t p = 0; p < pages; ++p) {
            cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); /* white page */
            cairo_paint(cr);
            for (size_t i = 0; i < L.nrow; ++i) {
                if ((size_t)pageof[i] != p) continue;
                paint_content_row(cr, w, &L, &L.rows[i], PDF_MARGIN,
                                  PDF_MARGIN + yof[i], content_w, PDF_PAGE_W, 0);
            }
            cairo_show_page(cr);
        }
    }

    free(tops); free(heights); free(yof); free(pageof);
    rc_free(&L);
    w->theme = saved;
    cairo_destroy(cr);
    cairo_surface_destroy(surf);

    char msg[PE_NAME_MAX + 4096u + 64u];
    if (pages > 0) {
        snprintf(msg, sizeof msg, "Saved PDF (%zu page%s): %s",
                 pages, pages == 1 ? "" : "s", path);
    } else {
        snprintf(msg, sizeof msg, "Nothing to export to PDF.");
    }
    browser_set_status(&w->bs, msg, now_ms());
    redraw(w);
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
    double content_w = content_width(w);

    cairo_t *cr = cairo_create(w->cairo_surface);
    rc_layout L;
    layout_doc(cr, w, content_w, &L);

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
            double fx = left + r->x_off + f->x;
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
    double content_w = content_width(w);

    cairo_t *cr = cairo_create(w->cairo_surface);
    rc_layout L;
    layout_doc(cr, w, content_w, &L);

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

/* Submits a POST plan ASYNCHRONOUSLY (same model as do_load): the pre-fetch gates run
 * here, then the blocking POST goes to a worker thread and the result is rendered by
 * deliver_fetch_result. Goes through the SAME gates as a GET (host filter, exception,
 * allowlist, Tor/I2P realm route) and the SAME navigability fallbacks: a POST to a
 * .onion is routed through Tor instead of failing SF_ERR_NETWORK, and never reaches
 * the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_window *w, const fm_plan *plan) {
    w->net_gen++;        /* new navigation: supersede any in-flight fetch */
    w->menu_open = 0;

    sf_config cfg;
    fetch_prep pr;
    if (!prepare_fetch(w, plan->url, &cfg, &pr)) {
        clear_doc(w);
        w->scroll = 0.0; w->ua_field_focused = 0; w->focused_input = -1; w->loading = 0;
        set_cache(w, NULL, 0, NULL);
        browser_set_page(&w->bs, NULL, pr.err, 1);
        return;
    }

    if (!fetch_launch(w, plan->url, &cfg, pr.allowlisted, 1,
                      plan->body, plan->body_len, plan->content_type)) {
        clear_doc(w);
        w->scroll = 0.0; w->loading = 0;
        set_cache(w, NULL, 0, NULL);
        browser_set_page(&w->bs, NULL, "Could not start the POST (out of resources).", 1);
        return;
    }
    show_busy(w); /* spinner on; the form page stays visible until the response lands */
}

/* Renders a completed fetch on the main thread. A result whose generation no longer
 * matches w->net_gen is silently dropped: the user navigated again or switched tabs,
 * so the active tab is no longer this job's target (fail safe -- never paint a stale
 * or wrong-tab page). On success the page is rendered in place; a POST redirect is
 * followed as a fresh async GET (re-applying the full policy, Zero Trust). */
static void deliver_fetch_result(browser_window *w, fetch_job *j) {
    if (j->gen != w->net_gen) return; /* superseded/abandoned navigation */
    w->loading = 0;

    if (j->status != SF_OK) {
        show_fetch_error(w, j->url, j->status, j->allowlisted);
        w->scroll = 0.0; w->ua_field_focused = 0; w->focused_input = -1;
        redraw(w);
        return;
    }

    if (j->is_post && sf_is_redirect_code(j->http_code) && j->location != NULL) {
        char next[SF_MAX_URL];
        if (sf_resolve_redirect(j->url, j->location, next, sizeof next) == SF_OK) {
            if (browser_navigate(&w->bs, next) == BROWSER_OK) do_load(w, next);
            redraw(w);
            return;
        }
    }

    clear_doc(w);
    w->scroll = 0.0; w->ua_field_focused = 0; w->focused_input = -1;

    char *html = j->html;
    size_t len = j->html_len;
    j->html = NULL; /* ownership moves into the page cache */
    if (html == NULL) { html = strdup(""); len = 0; }

    /* Image policy resolves srcs against this origin (the requested URL, as before). */
    set_cache(w, html, len, j->url);
    if (j->is_post) browser_set_url_bar(&w->bs, j->url); /* reflect action URL; no history push */
    render_current(w);

    if (j->downgraded == DOWNGRADE_ALLOWLISTED) {
        browser_set_status(&w->bs,
            "Warning: allowlisted host loaded below Freedom's standard "
            "(possibly TLS 1.2 / weak crypto).", now_ms());
    } else if (j->downgraded == DOWNGRADE_CLASSICAL_KE) {
        browser_set_status(&w->bs,
            "Warning: connection is not post-quantum (classical TLS 1.3).", now_ms());
    }
    redraw(w);
}

/* Drains every completed fetch the worker threads have posted (the read end is
 * non-blocking; pointer-sized writes are atomic). Called when the loop sees the
 * fetch pipe readable. */
static void drain_fetch_results(browser_window *w) {
    fetch_job *j;
    while (read(w->fetch_pipe[0], &j, sizeof j) == (ssize_t)sizeof j) {
        deliver_fetch_result(w, j);
        fetch_job_free(j);
    }
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
/* True when options-menu item i is currently enabled (drives its checkmark). */
static int menu_item_checked(const browser_window *w, size_t i) {
    const ui_menu_item *it = &UI_MENU_ITEMS[i];
    if (it->action == UI_MENU_THEME) return w->theme_mode == it->theme_val;
    if (it->action == UI_MENU_FORCE) return w->force_theme;
    if (it->action == UI_MENU_TOR)   return w->net_cfg.tor_enabled;
    if (it->action == UI_MENU_I2P)   return w->net_cfg.i2p_enabled;
    if (it->action == UI_MENU_PDF)   return 0; /* an action, never "checked" */
    return *(const bool *)((const char *)&w->caps + it->cap_offset);
}

/* Toggles options-menu item i and applies its effect. Theme and force-colors only
 * affect presentation (a repaint, which re-runs layout, suffices); a capability
 * change re-renders from cache. */
static void menu_item_toggle(browser_window *w, size_t i) {
    const ui_menu_item *it = &UI_MENU_ITEMS[i];
    if (it->action == UI_MENU_THEME) {
        /* Clicking the active palette returns to light; otherwise select it. */
        w->theme_mode = (w->theme_mode == it->theme_val) ? UI_THEME_LIGHT : it->theme_val;
        w->theme = ui_theme_for(w->theme_mode);
        return;
    }
    if (it->action == UI_MENU_FORCE) {
        w->force_theme = !w->force_theme;
        return;  /* layout re-applies author colors (or not) on the next paint */
    }
    if (it->action == UI_MENU_TOR) {
        /* One switch: enable Tor and route clearnet through it too (so the whole
         * session is anonymized and .onion becomes reachable). Takes effect on the
         * next navigation; warn the user, who must have a Tor proxy running. */
        w->net_cfg.tor_enabled = !w->net_cfg.tor_enabled;
        w->net_cfg.torify_clearnet = w->net_cfg.tor_enabled;
        browser_set_status(&w->bs, w->net_cfg.tor_enabled
            ? "Tor routing ON (needs a Tor proxy on the configured port). Reload to apply."
            : "Tor routing OFF.", now_ms());
        return;
    }
    if (it->action == UI_MENU_I2P) {
        w->net_cfg.i2p_enabled = !w->net_cfg.i2p_enabled;
        browser_set_status(&w->bs, w->net_cfg.i2p_enabled
            ? "I2P routing ON for .i2p (needs an I2P HTTP proxy). Reload to apply."
            : "I2P routing OFF.", now_ms());
        return;
    }
    if (it->action == UI_MENU_PDF) {
        w->menu_open = 0; /* dismiss the menu, then export */
        export_pdf(w);
        return;
    }
    bool *flag = (bool *)((char *)&w->caps + it->cap_offset);
    *flag = !*flag;
    render_current(w);
}

/* A small spinner meaning "busy". Now that the fetch runs off the event-loop thread,
 * the loop ticks ~12 fps while loading and rotates a leading arc so the user sees real
 * progress. phase in [0,1) is the rotation, derived from the wall clock. */
static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
                       double phase) {
    double a0 = phase * UI_TWO_PI;
    set_rgb(cr, color);
    cairo_set_line_width(cr, 2.0);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    /* A 270-degree arc that sweeps around, leaving a moving gap (a classic spinner). */
    cairo_new_sub_path(cr);
    cairo_arc(cr, cx, cy, r, a0, a0 + UI_TWO_PI * 0.75);
    cairo_stroke(cr);
}

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

        if (menu_item_checked(w, i)) {
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
        /* Empty field => the normalized anti-fingerprint identity (a shared Firefox
         * string) is sent. The placeholder names that intent rather than the long UA
         * literal; "Freedom" is deliberately never sent on the wire. */
        set_rgb(cr, th->chrome_text_dim);
        cairo_move_to(cr, tx, ty);
        cairo_show_text(cr, "anti-fingerprint default (shared Firefox identity)");
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

/* Persistent bottom strip showing the target of the link under the pointer, so
 * the user always knows where a click will go. Returns the strip height (0 when
 * nothing is hovered) so the toast can stack above it. */
static double draw_hover_url(cairo_t *cr, browser_window *w) {
    if (w->hover_href == NULL) return 0.0;
    const ui_theme *th = &w->theme;

    cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, th->body_font);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    cairo_text_extents_t te;
    cairo_text_extents(cr, w->hover_href, &te);

    double bh = fe.height + 2.0 * UI_TOAST_PAD;
    double bw = te.width + 2.0 * UI_TOAST_PAD;
    if (bw > (double)w->width) bw = (double)w->width; /* never wider than the window */
    double by = (double)w->height - bh;

    set_rgb(cr, th->toast_bg);
    cairo_rectangle(cr, 0.0, by, bw, bh);
    cairo_fill(cr);

    cairo_save(cr);
    cairo_rectangle(cr, 0.0, by, bw - UI_TOAST_PAD, bh); /* clip a long URL */
    cairo_clip(cr);
    set_rgb(cr, th->toast_text);
    cairo_move_to(cr, UI_TOAST_PAD, by + UI_TOAST_PAD + fe.ascent);
    cairo_show_text(cr, w->hover_href);
    cairo_restore(cr);
    return bh;
}

/* Draws the transient status toast (a banner near the bottom of the window),
 * raised by bottom_offset so it stacks above the hover-URL strip when both show. */
static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset) {
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
    double by = (double)w->height - bh - UI_MARGIN - bottom_offset;

    set_rgb(cr, th->toast_bg);
    cairo_rectangle(cr, bx, by, bw, bh);
    cairo_fill(cr);
    set_rgb(cr, th->toast_text);
    cairo_move_to(cr, bx + UI_TOAST_PAD, by + UI_TOAST_PAD + fe.ascent);
    cairo_show_text(cr, msg);
}

/* Paints the tab strip: one cell per tab (the active one connected to the content
 * background, the rest dimmed), each with its clipped title and a close 'x', then a
 * trailing '+' to open a new tab. The geometry mirrors the pointer hit-test
 * (tab_width/newtab_x) so a click lands on exactly what is drawn. Uses the chrome
 * (monospace) font already selected by paint(). */
static void draw_tabstrip(cairo_t *cr, browser_window *w) {
    const ui_theme *th = &w->theme;
    double top = tabbar_top(w);
    double h = UI_TABBAR_H;

    set_rgb(cr, th->titlebar_bg);
    cairo_rectangle(cr, 0, top, w->width, h);
    cairo_fill(cr);

    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    double baseline = top + (h + fe.ascent - fe.descent) / 2.0;
    double tw = tab_width(w);

    for (int i = 0; i < w->tab_count; ++i) {
        double x = (double)i * tw;
        int active = (i == w->active_tab);
        int hot = (w->ptr_y >= top && w->ptr_y < top + h
                   && w->ptr_x >= x && w->ptr_x < x + tw);

        set_rgb(cr, active ? th->content_bg : (hot ? th->btn_hover_bg : th->toolbar_bg));
        cairo_rectangle(cr, x, top, tw - 1.0, h);
        cairo_fill(cr);

        cairo_save(cr);
        cairo_rectangle(cr, x + 6.0, top, tw - 6.0 - UI_TAB_CLOSE_W, h);
        cairo_clip(cr);
        set_rgb(cr, active ? th->chrome_text : th->chrome_text_dim);
        cairo_move_to(cr, x + 6.0, baseline);
        cairo_show_text(cr, tab_title(w, i));
        cairo_restore(cr);

        if (w->tab_count > 1) {
            double cxr = x + tw - UI_TAB_CLOSE_W;
            int cl_hot = (w->ptr_y >= top && w->ptr_y < top + h
                          && w->ptr_x >= cxr && w->ptr_x < x + tw);
            set_rgb(cr, cl_hot ? th->close_button
                                : (active ? th->chrome_text : th->chrome_text_dim));
            draw_text(cr, "x", cxr + UI_TAB_CLOSE_W / 2.0, baseline, 1);
        }
    }

    double nx = newtab_x(w);
    int nhot = (w->ptr_y >= top && w->ptr_y < top + h
                && w->ptr_x >= nx && w->ptr_x < nx + UI_TAB_NEW_W);
    set_rgb(cr, nhot ? th->btn_hover_bg : th->titlebar_bg);
    cairo_rectangle(cr, nx, top, UI_TAB_NEW_W, h);
    cairo_fill(cr);
    set_rgb(cr, th->chrome_text);
    draw_text(cr, "+", nx + UI_TAB_NEW_W / 2.0, baseline, 1);
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
        cairo_show_text(cr, w->loading ? "Loading..."
                          : (w->bs.page_title != NULL) ? w->bs.page_title : "Freedom");

        double min_x, max_x, close_x;
        window_button_rects(w, &min_x, &max_x, &close_x);
        set_rgb(cr, th->chrome_text);
        draw_text(cr, "_", min_x + UI_WIN_BTN_W / 2.0, bl, 1);
        draw_text(cr, "[]", max_x + UI_WIN_BTN_W / 2.0, bl, 1);
        set_rgb(cr, th->close_button);
        draw_text(cr, "X", close_x + UI_WIN_BTN_W / 2.0, bl, 1);
    }

    /* Tab strip, between the titlebar and the toolbar. */
    draw_tabstrip(cr, w);

    /* Toolbar. */
    set_rgb(cr, th->toolbar_bg);
    cairo_rectangle(cr, 0, ttop, w->width, UI_TOOLBAR_H);
    cairo_fill(cr);

    double back_x, fwd_x, url_x, url_w, go_x, menu_x;
    toolbar_rects(w, &back_x, &fwd_x, &url_x, &url_w, &go_x, &menu_x);
    double bl = ttop + (UI_TOOLBAR_H + fe.ascent - fe.descent) / 2.0;

    /* Hover highlight behind the toolbar button under the pointer (the same
     * affordance links get). */
    if (w->hot != UI_HOT_NONE) {
        double hx = back_x;
        switch (w->hot) {
            case UI_HOT_BACK: hx = back_x; break;
            case UI_HOT_FWD:  hx = fwd_x;  break;
            case UI_HOT_GO:   hx = go_x;   break;
            case UI_HOT_MENU: hx = menu_x; break;
            default: break;
        }
        set_rgb(cr, th->btn_hover_bg);
        cairo_rectangle(cr, hx, ttop, UI_BTN_W, UI_TOOLBAR_H);
        cairo_fill(cr);
    }

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

    /* Animated spinner at the right of the URL bar while a request is in flight. The
     * rotation comes from the wall clock; the loop wakes ~12 fps while loading. */
    if (w->loading) {
        double r = (UI_TOOLBAR_H - 2.0 * UI_MARGIN) * 0.30;
        double ccx = url_x + url_w - r - UI_MARGIN;
        double ccy = ttop + UI_TOOLBAR_H / 2.0;
        double phase = (double)(now_ms() % 1000u) / 1000.0;
        draw_clock(cr, th->link, ccx, ccy, r, phase);
    }

    /* Content area. */
    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);

    set_rgb(cr, th->content_bg);
    cairo_rectangle(cr, 0, content_top, w->width, (double)w->height - content_top);
    cairo_fill(cr);

    /* Clip every page paint to the content viewport. Rows that straddle the top
     * edge (partly scrolled above content_top) would otherwise bleed up over the
     * toolbar/tab strip; the clip is the single guard that keeps content under the
     * chrome no matter the scroll offset. Released before the chrome overlays
     * (scrollbar, menu, toast) so those still paint over the full surface. */
    cairo_save(cr);
    cairo_rectangle(cr, 0, content_top, w->width, (double)w->height - content_top);
    cairo_clip(cr);

    w->content_total_h = 0.0;  /* each branch sets the real height; 0 => no scrollbar */
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

        size_t max_cols = (size_t)(content_width(w) / cell_w);
        if (max_cols == 0) max_cols = 1;
        size_t viewport_lines = (size_t)(content_h / cell_h);
        if (viewport_lines == 0) viewport_lines = 1;

        ui_layout lay;
        if (ui_wrap_text(text, text_len, max_cols, &lay) == UI_OK) {
            w->content_total_h = (double)lay.count * cell_h;  /* cached for the scrollbar */
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

    cairo_restore(cr);  /* end content-viewport clip */

    /* Scrollbar over the content's right gutter, then overlays on top. */
    draw_scrollbar(cr, w);
    draw_menu(cr, w);
    double hover_h = draw_hover_url(cr, w);
    draw_toast(cr, w, hover_h);

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
    (void)t;
    browser_window *w = (browser_window *)data;
    if (width > 0 && height > 0) {
        w->width = width;
        w->height = height;
    }
    /* Track the maximized state so the titlebar button toggles correctly. */
    w->maximized = 0;
    if (states != NULL) {
        const uint32_t *st;
        wl_array_for_each(st, states) {
            if (*st == XDG_TOPLEVEL_STATE_MAXIMIZED) w->maximized = 1;
        }
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
    ui_hot hot = toolbar_button_at(w, w->ptr_x, w->ptr_y);
    if (h == w->hover_href && hot == w->hot) return;

    int hand_was = (w->hover_href != NULL) || hot_actionable(w, w->hot);
    int hand_now = (h != NULL) || hot_actionable(w, hot);
    w->hover_href = h;
    w->hot = hot;
    if (hand_was != hand_now) set_cursor(w, hand_now);
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
    if (w->hover_href != NULL || w->hot != UI_HOT_NONE) {
        w->hover_href = NULL;
        w->hot = UI_HOT_NONE;
        redraw(w);
    }
}
static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y) {
    (void)p; (void)t;
    browser_window *w = (browser_window *)d;
    w->ptr_x = wl_fixed_to_double(x);
    w->ptr_y = wl_fixed_to_double(y);
    if (w->dragging_scroll) { scrollbar_drag_to(w); return; }
    update_hover(w);
}

static void load_current(browser_window *w) {
    const char *url = browser_current_url(&w->bs);
    if (url != NULL) {
        browser_set_url_bar(&w->bs, url);
        do_load(w, url);
    }
}

/* Commits the URL bar like a real omnibox: an existing local file is opened as
 * before; otherwise url_omnibox (pure) decides between navigating to a site and
 * running a DuckDuckGo HTML search, building the absolute https URL either way. So
 * "example.com" becomes https://example.com and "best linux distro" becomes a
 * search, instead of the old "cannot read file" dead end. */
static void go_omnibox(browser_window *w) {
    const char *raw = w->bs.url_bar;
    if (raw == NULL || raw[0] == '\0') return;

    /* A readable local path keeps the file-browsing capability (the start page is a
     * relative path), and must win over the host heuristic ("docs/index.html"). */
    if (!is_https_url(raw) && !is_overlay_http_url(raw) && access(raw, R_OK) == 0) {
        if (browser_navigate(&w->bs, raw) == BROWSER_OK) load_current(w);
        return;
    }

    char target[URL_MAX_LEN];
    url_omni_kind kind;
    if (url_omnibox(raw, &kind, target, sizeof target) == URL_OK &&
        browser_navigate(&w->bs, target) == BROWSER_OK) {
        do_load(w, target);
        return;
    }
    /* Fail closed to the legacy path (e.g. about:blank or an OOM in the bounded build). */
    browser_commit_url_bar(&w->bs);
    load_current(w);
}

static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
                       uint32_t button, uint32_t state) {
    (void)p; (void)t;
    browser_window *w = (browser_window *)d;
    if (button != UI_BTN_LEFT) return;
    if (state == WL_POINTER_BUTTON_STATE_RELEASED) {
        if (w->dragging_scroll) { w->dragging_scroll = 0; redraw(w); }
        return;
    }
    /* state == WL_POINTER_BUTTON_STATE_PRESSED below. */

    double ttop = toolbar_top(w);

    /* Tab strip (between titlebar and toolbar): the "+" opens a tab, the close 'x' at
     * a tab's right edge closes it, and a click on the body switches to it. */
    double tbtop = tabbar_top(w);
    if (w->ptr_y >= tbtop && w->ptr_y < tbtop + UI_TABBAR_H) {
        double nx = newtab_x(w);
        if (w->ptr_x >= nx && w->ptr_x < nx + UI_TAB_NEW_W) { tab_new(w, NULL); return; }
        double tw = tab_width(w);
        int i = (int)(w->ptr_x / tw);
        if (i >= 0 && i < w->tab_count) {
            double cxr = (double)i * tw + tw - UI_TAB_CLOSE_W;
            if (w->tab_count > 1 && w->ptr_x >= cxr && w->ptr_x < (double)i * tw + tw)
                uitab_close(w, i);
            else
                tab_switch(w, i);
        }
        return; /* clicks anywhere on the strip stay on the strip */
    }

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
                    if (row < UI_MENU_COUNT) menu_item_toggle(w, row);
                }
            }
        } else {
            w->menu_open = 0;
            w->ua_field_focused = 0;
        }
        redraw(w);
        return;
    }

    /* Dragging a window border starts an interactive resize (CSD only; the
     * compositor owns the edges under server-side decorations). Checked before the
     * scrollbar so the extreme edge always resizes; the rest of the gutter drags. */
    if (w->use_csd && !w->maximized) {
        uint32_t edge = resize_edge_at(w, w->ptr_x, w->ptr_y);
        if (edge != XDG_TOPLEVEL_RESIZE_EDGE_NONE) {
            if (w->seat != NULL)
                xdg_toplevel_resize(w->xdg_toplevel, w->seat, serial, edge);
            return;
        }
    }

    /* The scrollbar captures the press: grabbing the thumb starts a drag; clicking
     * the track jumps the thumb under the cursor and then drags. */
    {
        double tx, ty, trh, thy, thh;
        if (scrollbar_metrics(w, &tx, &ty, &trh, &thy, &thh)
            && w->ptr_x >= tx && w->ptr_x <= tx + UI_SCROLLBAR_W
            && w->ptr_y >= ty && w->ptr_y <= ty + trh) {
            w->scroll_grab_dy = (w->ptr_y >= thy && w->ptr_y <= thy + thh)
                                ? (w->ptr_y - thy)   /* grabbed the thumb */
                                : (thh / 2.0);       /* clicked the track: center on cursor */
            w->dragging_scroll = 1;
            scrollbar_drag_to(w);
            return;
        }
    }

    /* Client-side decoration controls: close / maximize-toggle / minimize, and a
     * drag on the empty titlebar moves the window. */
    if (w->use_csd && w->ptr_y < UI_TITLEBAR_H) {
        double min_x, max_x, close_x;
        window_button_rects(w, &min_x, &max_x, &close_x);
        if (w->ptr_x >= close_x) {
            w->running = 0;
        } else if (w->ptr_x >= max_x) {
            if (w->maximized) xdg_toplevel_unset_maximized(w->xdg_toplevel);
            else              xdg_toplevel_set_maximized(w->xdg_toplevel);
        } else if (w->ptr_x >= min_x) {
            xdg_toplevel_set_minimized(w->xdg_toplevel);
        } else if (w->seat != NULL) {
            xdg_toplevel_move(w->xdg_toplevel, w->seat, serial);
        }
        return;
    }

    double back_x, fwd_x, url_x, url_w, go_x, menu_x;
    toolbar_rects(w, &back_x, &fwd_x, &url_x, &url_w, &go_x, &menu_x);

    if (w->ptr_y >= ttop && w->ptr_y < ttop + UI_TOOLBAR_H) {
        if (w->ptr_x >= menu_x) {
            w->menu_open = 1;
        } else if (w->ptr_x >= go_x && w->ptr_x < menu_x) {
            go_omnibox(w);
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

/* --- clipboard (wl_data_device) --- */

/* True for a mime type that carries plain UTF-8/Latin text we can paste. */
static int mime_is_text(const char *mime) {
    if (mime == NULL) return 0;
    return strncmp(mime, "text/plain", 10) == 0 ||
           strcmp(mime, "UTF8_STRING") == 0 ||
           strcmp(mime, "TEXT") == 0 ||
           strcmp(mime, "STRING") == 0;
}

/* A mime type advertised by the incoming offer. Remember the best text mime so paste
 * requests exactly what the source provides (preferring an explicit UTF-8 variant). */
static void data_offer_mime(void *data, struct wl_data_offer *offer, const char *mime) {
    browser_window *w = (browser_window *)data;
    if (offer != w->incoming_offer || !mime_is_text(mime)) return;
    w->incoming_offer_has_text = 1;
    int prefer = (strstr(mime, "utf-8") != NULL || strstr(mime, "UTF-8") != NULL);
    if (w->incoming_mime[0] == '\0' || prefer)
        snprintf(w->incoming_mime, sizeof w->incoming_mime, "%s", mime);
}
static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a) {
    (void)d; (void)o; (void)a;
}
static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a) {
    (void)d; (void)o; (void)a;
}
static const struct wl_data_offer_listener data_offer_listener = {
    .offer = data_offer_mime,
    .source_actions = data_offer_source_actions,
    .action = data_offer_action,
};

/* A new offer is being introduced: start scanning its mime types. */
static void data_device_data_offer(void *data, struct wl_data_device *dev,
                                   struct wl_data_offer *offer) {
    (void)dev;
    browser_window *w = (browser_window *)data;
    w->incoming_offer = offer;
    w->incoming_offer_has_text = 0;
    w->incoming_mime[0] = '\0';
    wl_data_offer_add_listener(offer, &data_offer_listener, w);
}

/* The clipboard selection changed. Commit the new offer (or NULL when the clipboard
 * was cleared), destroying any previous one we held. */
static void data_device_selection(void *data, struct wl_data_device *dev,
                                  struct wl_data_offer *offer) {
    (void)dev;
    browser_window *w = (browser_window *)data;
    if (w->selection_offer != NULL && w->selection_offer != offer)
        wl_data_offer_destroy(w->selection_offer);
    if (offer == NULL) {
        w->selection_offer = NULL;
        w->selection_offer_has_text = 0;
        w->sel_mime[0] = '\0';
        return;
    }
    w->selection_offer = offer;
    w->selection_offer_has_text = (offer == w->incoming_offer) ? w->incoming_offer_has_text : 0;
    snprintf(w->sel_mime, sizeof w->sel_mime, "%s",
             (offer == w->incoming_offer && w->incoming_mime[0]) ? w->incoming_mime : "text/plain");
}

/* Drag-and-drop events: not supported (the data device is clipboard-only). */
static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
                              struct wl_surface *s, wl_fixed_t x, wl_fixed_t y,
                              struct wl_data_offer *o) {
    (void)d; (void)dev; (void)serial; (void)s; (void)x; (void)y; (void)o;
}
static void data_device_leave(void *d, struct wl_data_device *dev) { (void)d; (void)dev; }
static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                               wl_fixed_t x, wl_fixed_t y) {
    (void)d; (void)dev; (void)t; (void)x; (void)y;
}
static void data_device_drop(void *d, struct wl_data_device *dev) { (void)d; (void)dev; }
static const struct wl_data_device_listener data_device_listener = {
    .data_offer = data_device_data_offer,
    .enter = data_device_enter,
    .leave = data_device_leave,
    .motion = data_device_motion,
    .drop = data_device_drop,
    .selection = data_device_selection,
};

/* Another client now owns our copied text: drop our source. */
static void data_source_cancelled(void *data, struct wl_data_source *src) {
    browser_window *w = (browser_window *)data;
    if (src == w->copy_source) w->copy_source = NULL;
    wl_data_source_destroy(src);
}
/* A paster asked for our copied text: write it to the pipe and close. */
static void data_source_send(void *data, struct wl_data_source *src,
                             const char *mime, int32_t fd) {
    (void)src; (void)mime;
    browser_window *w = (browser_window *)data;
    const char *t = (w->copy_text != NULL) ? w->copy_text : "";
    size_t len = strlen(t), off = 0;
    while (off < len) {
        ssize_t n = write(fd, t + off, len - off);
        if (n <= 0) break;       /* SIGPIPE is ignored process-wide; a closed reader ends it */
        off += (size_t)n;
    }
    close(fd);
}
static void data_source_target(void *d, struct wl_data_source *s, const char *m) {
    (void)d; (void)s; (void)m;
}
static const struct wl_data_source_listener data_source_listener = {
    .target = data_source_target,
    .send = data_source_send,
    .cancelled = data_source_cancelled,
};

/* Inserts pasted bytes into whichever text target currently has focus (page input,
 * User-Agent box, or the URL bar). Control bytes -- including embedded CR/LF/TAB that
 * a multi-line clipboard would carry -- are dropped so a paste cannot inject a newline
 * into a single-line field; UTF-8 continuation bytes (>= 0x80) pass through. */
static void insert_pasted_text(browser_window *w, const char *text, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        unsigned char c = (unsigned char)text[i];
        if (c < 0x20 || c == 0x7f) continue;
        if (w->ua_field_focused) {
            tf_insert(&w->ua_field, (char)c);
        } else if (w->focused_input >= 0 && (size_t)w->focused_input < w->input_count) {
            tf_insert(&w->inputs[w->focused_input].field, (char)c);
        } else if (w->url_bar_focused) {
            browser_url_bar_insert(&w->bs, (char)c);
        } else {
            return; /* nothing focused: paste goes nowhere */
        }
    }
}

/* Ctrl+V: pull the clipboard's text and insert it at the focused field's cursor.
 * Synchronous (like the v1 image fetch): a pipe is handed to the source, the display
 * is flushed so the source -- possibly ourselves -- writes, then we drain to EOF. The
 * read is capped so a hostile clipboard cannot exhaust memory. */
static void clipboard_paste(browser_window *w) {
    if (w->selection_offer == NULL || !w->selection_offer_has_text) return;
    /* Only paste when a text field is focused, else the bytes have nowhere to go. */
    if (!w->ua_field_focused && w->url_bar_focused == 0 &&
        !(w->focused_input >= 0 && (size_t)w->focused_input < w->input_count))
        return;

    int fds[2];
    if (pipe(fds) != 0) return;
    const char *mime = (w->sel_mime[0] != '\0') ? w->sel_mime : "text/plain";
    wl_data_offer_receive(w->selection_offer, mime, fds[1]);
    /* Roundtrip so the source dispatches the receive request (our own data_source_send
     * runs here for a self-paste), then close our write end to bound the read by EOF. */
    wl_display_roundtrip(w->display);
    close(fds[1]);

    char *buf = NULL;
    size_t cap = 0, total = 0;
    const size_t LIMIT = 1u << 20; /* 1 MiB hard cap */
    for (;;) {
        /* Bound the wait: a misbehaving source must not freeze the UI. Local clipboard
         * transfers complete in well under this; a stall just truncates the paste. */
        struct pollfd rp = { .fd = fds[0], .events = POLLIN, .revents = 0 };
        int pr = poll(&rp, 1, 500);
        if (pr <= 0) break; /* timeout or error: stop reading */
        if (total == cap) {
            size_t ncap = (cap == 0) ? 4096 : cap * 2;
            if (ncap > LIMIT) ncap = LIMIT;
            if (ncap == cap) break; /* hit the cap */
            char *nb = (char *)realloc(buf, ncap);
            if (nb == NULL) break;
            buf = nb; cap = ncap;
        }
        ssize_t n = read(fds[0], buf + total, cap - total);
        if (n <= 0) break;
        total += (size_t)n;
    }
    close(fds[0]);
    if (buf != NULL) insert_pasted_text(w, buf, total);
    free(buf);
}

/* Ctrl+C: copy the focused field's text (or, with nothing focused, the page address)
 * to the clipboard by owning a wl_data_source that serves it on demand. */
static void clipboard_copy(browser_window *w) {
    if (w->data_device == NULL || w->data_device_manager == NULL) return;

    const char *text = NULL;
    if (w->ua_field_focused) {
        text = tf_text(&w->ua_field);
    } else if (w->focused_input >= 0 && (size_t)w->focused_input < w->input_count) {
        text = tf_text(&w->inputs[w->focused_input].field);
    } else if (w->url_bar_focused) {
        text = w->bs.url_bar;
    } else {
        text = browser_current_url(&w->bs); /* copy the current page's address */
    }
    if (text == NULL || text[0] == '\0') return;

    char *dup = strdup(text);
    if (dup == NULL) return;
    free(w->copy_text);
    w->copy_text = dup;
    if (w->copy_source != NULL) wl_data_source_destroy(w->copy_source);
    w->copy_source = wl_data_device_manager_create_data_source(w->data_device_manager);
    if (w->copy_source == NULL) return;
    wl_data_source_add_listener(w->copy_source, &data_source_listener, w);
    wl_data_source_offer(w->copy_source, "text/plain;charset=utf-8");
    wl_data_source_offer(w->copy_source, "text/plain");
    wl_data_device_set_selection(w->data_device, w->copy_source, w->last_serial);
}

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

/* Performs the effect of a single key press. Factored out of keyboard_key so a held
 * key can be re-fired from the repeat timer with the exact same semantics (the caller
 * recomputes sym/utf8/modifiers from the live xkb_state each time). */
static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
                             int n, int ctrl, int shift) {
    /* Ctrl+L focuses and clears the URL bar. */
    if (ctrl && !shift && (sym == XKB_KEY_l || sym == XKB_KEY_L)) {
        w->url_bar_focused = 1;
        browser_url_bar_clear(&w->bs);
        redraw(w);
        return;
    }

    /* Ctrl+V pastes the clipboard into the focused field; Ctrl+C copies the focused
     * field's text (or the page address when nothing is focused). */
    if (ctrl && !shift && (sym == XKB_KEY_v || sym == XKB_KEY_V)) {
        clipboard_paste(w);
        redraw(w);
        return;
    }
    if (ctrl && !shift && (sym == XKB_KEY_c || sym == XKB_KEY_C)) {
        clipboard_copy(w);
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

    /* Ctrl+P saves the current page as a vector PDF (selectable text) to the
     * downloads directory. The output filename is derived safely from the page
     * title (pdf_export, fail-closed). */
    if (ctrl && !shift && (sym == XKB_KEY_p || sym == XKB_KEY_P)) {
        export_pdf(w);
        return;
    }

    /* Tab shortcuts. Ctrl+T opens a tab, Ctrl+W closes the current one (never the
     * last), Ctrl+Tab / Ctrl+Shift+Tab cycle forward / backward. */
    if (ctrl && !shift && (sym == XKB_KEY_t || sym == XKB_KEY_T)) {
        tab_new(w, NULL);
        return;
    }
    if (ctrl && !shift && (sym == XKB_KEY_w || sym == XKB_KEY_W)) {
        uitab_close(w, w->active_tab);
        return;
    }
    if (ctrl && (sym == XKB_KEY_Tab || sym == XKB_KEY_ISO_Left_Tab)) {
        if (w->tab_count > 1) {
            int next = shift ? (w->active_tab + w->tab_count - 1) % w->tab_count
                             : (w->active_tab + 1) % w->tab_count;
            tab_switch(w, next);
        }
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
        /* Page scroll plus vim-style keys: j/k by line, space/b by page, gg to the
         * top, G to the bottom. pending_g remembers a lone 'g' for the gg sequence. */
        double line = scroll_line_px(w);
        double page = w->theme.page_step_lines * line;
        int was_g = w->pending_g;
        w->pending_g = 0;
        if (sym == XKB_KEY_Up || sym == XKB_KEY_k) { w->scroll -= line; }
        else if (sym == XKB_KEY_Down || sym == XKB_KEY_j) { w->scroll += line; }
        else if (sym == XKB_KEY_Page_Up || sym == XKB_KEY_b) { w->scroll -= page; }
        else if (sym == XKB_KEY_Page_Down || sym == XKB_KEY_space) { w->scroll += page; }
        else if (sym == XKB_KEY_Home) { w->scroll = 0.0; }
        else if (sym == XKB_KEY_End || sym == XKB_KEY_G) { w->scroll = w->content_total_h; }
        else if (sym == XKB_KEY_g) { if (was_g) w->scroll = 0.0; else w->pending_g = 1; }
        if (w->scroll < 0.0) w->scroll = 0.0;
        redraw(w);
        return;
    }

    if (sym == XKB_KEY_Escape) {
        w->url_bar_focused = 0;
    } else if (sym == XKB_KEY_Return || sym == XKB_KEY_KP_Enter) {
        go_omnibox(w);
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

/* Keys whose held-down auto-repeat is safe and useful: text editing, cursor motion
 * and scrolling. A Ctrl chord (tab spawn, reload, image toggle...) or Enter must NOT
 * repeat -- holding them would loop a navigation or spawn tabs. A printable character
 * (n > 0) repeats so a held letter types, mirroring every text widget. */
static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl) {
    if (ctrl) return 0;
    switch (sym) {
        case XKB_KEY_BackSpace:
        case XKB_KEY_Delete: case XKB_KEY_KP_Delete:
        case XKB_KEY_Left:   case XKB_KEY_Right:
        case XKB_KEY_Up:     case XKB_KEY_Down:
        case XKB_KEY_Page_Up: case XKB_KEY_Page_Down:
            return 1;
        default:
            return n > 0;
    }
}

/* Arms the repeat timer for key: first fire after repeat_delay ms, then every
 * 1/repeat_rate s. A held key thus repeats until released (key_repeat_stop). */
static void key_repeat_arm(browser_window *w, uint32_t key) {
    if (w->repeat_timer_fd < 0 || w->repeat_rate <= 0) return;
    w->repeat_key = key;
    long interval_ns = 1000000000L / w->repeat_rate;
    struct itimerspec its;
    its.it_value.tv_sec  = w->repeat_delay / 1000;
    its.it_value.tv_nsec = (long)(w->repeat_delay % 1000) * 1000000L;
    its.it_interval.tv_sec  = interval_ns / 1000000000L;
    its.it_interval.tv_nsec = interval_ns % 1000000000L;
    timerfd_settime(w->repeat_timer_fd, 0, &its, NULL);
}

/* Disarms repeat (key released, or a non-repeatable key was pressed). */
static void key_repeat_stop(browser_window *w) {
    w->repeat_key = 0;
    if (w->repeat_timer_fd < 0) return;
    struct itimerspec off;
    memset(&off, 0, sizeof off);
    timerfd_settime(w->repeat_timer_fd, 0, &off, NULL);
}

/* Re-fires the currently held key. Called from the event loop when the timer expires.
 * Modifiers/keysym are recomputed from the live xkb_state, so a chord released
 * mid-repeat degrades correctly. */
static void key_repeat_fire(browser_window *w) {
    if (w->repeat_key == 0 || w->xkb_state == NULL) return;
    uint32_t kc = w->repeat_key + 8;
    xkb_keysym_t sym = xkb_state_key_get_one_sym(w->xkb_state, kc);
    char utf8[16];
    int n = xkb_state_key_get_utf8(w->xkb_state, kc, utf8, sizeof utf8);
    int ctrl = xkb_state_mod_name_is_active(w->xkb_state, XKB_MOD_NAME_CTRL,
                                            XKB_STATE_MODS_EFFECTIVE);
    int shift = xkb_state_mod_name_is_active(w->xkb_state, XKB_MOD_NAME_SHIFT,
                                             XKB_STATE_MODS_EFFECTIVE);
    if (!key_is_repeatable(sym, n, ctrl)) { key_repeat_stop(w); return; }
    handle_key_press(w, sym, utf8, n, ctrl, shift);
}

static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                         uint32_t time, uint32_t key, uint32_t state) {
    (void)kbd; (void)time;
    browser_window *w = (browser_window *)data;
    w->last_serial = serial; /* for wl_data_device_set_selection on Ctrl+C */
    if (w->xkb_state == NULL) return;

    /* Releasing the held key (or any other key while it repeats) stops the repeat. */
    if (state != WL_KEYBOARD_KEY_STATE_PRESSED) {
        if (key == w->repeat_key) key_repeat_stop(w);
        return;
    }

    xkb_keysym_t sym = xkb_state_key_get_one_sym(w->xkb_state, key + 8);
    char utf8[16];
    int n = xkb_state_key_get_utf8(w->xkb_state, key + 8, utf8, sizeof utf8);
    int ctrl = xkb_state_mod_name_is_active(w->xkb_state, XKB_MOD_NAME_CTRL,
                                            XKB_STATE_MODS_EFFECTIVE);
    int shift = xkb_state_mod_name_is_active(w->xkb_state, XKB_MOD_NAME_SHIFT,
                                             XKB_STATE_MODS_EFFECTIVE);

    handle_key_press(w, sym, utf8, n, ctrl, shift);

    /* Start (or restart, for a new key) auto-repeat for the keys that warrant it. */
    if (key_is_repeatable(sym, n, ctrl) &&
        w->xkb_keymap != NULL && xkb_keymap_key_repeats(w->xkb_keymap, key + 8))
        key_repeat_arm(w, key);
    else
        key_repeat_stop(w);
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
    (void)kbd;
    browser_window *w = (browser_window *)d;
    /* rate is repeats/second (0 => repeat disabled); delay is ms before the first. */
    w->repeat_rate = rate;
    w->repeat_delay = delay;
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
    } else if (strcmp(iface, wl_data_device_manager_interface.name) == 0) {
        w->data_device_manager = wl_registry_bind(reg, name, &wl_data_device_manager_interface, 1);
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
    w.tab_count = 1;            /* the foreground tab lives in the window's own fields */
    w.active_tab = 0;
    tf_init(&w.ua_field);       /* empty => SF_DEFAULT_USER_AGENT */

    /* Key auto-repeat: a monotonic timerfd polled alongside the Wayland fd. Defaults
     * apply until the compositor sends keyboard_repeat_info. A failed create (-1) just
     * disables repeat -- one event per press, as before. */
    w.repeat_timer_fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    w.repeat_key = 0;
    w.repeat_rate = 25;         /* repeats/second */
    w.repeat_delay = 600;       /* ms before the first repeat */

    /* A clipboard paster that closes the pipe early would otherwise SIGPIPE us out of
     * data_source_send; ignore it process-wide (curl is also happier this way). A
     * fetch worker writing to a closed result pipe at shutdown benefits too. */
    signal(SIGPIPE, SIG_IGN);

    /* Async fetch: thread-safe global transport init on the main thread (before any
     * worker), and the non-blocking result pipe the loop polls. If the pipe cannot be
     * created, fetch_launch fails closed and loads report an error rather than block. */
    sf_global_init();
    w.fetch_pipe[0] = w.fetch_pipe[1] = -1;
    if (pipe(w.fetch_pipe) == 0) {
        fcntl(w.fetch_pipe[0], F_SETFL, O_NONBLOCK); /* drain without blocking the loop */
        fcntl(w.fetch_pipe[0], F_SETFD, FD_CLOEXEC);
        fcntl(w.fetch_pipe[1], F_SETFD, FD_CLOEXEC);
    }

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

    /* Clipboard wiring (optional: a compositor without wl_data_device_manager simply
     * has no copy/paste). The seat and the manager are both bound by the roundtrip. */
    if (w.data_device_manager != NULL && w.seat != NULL) {
        w.data_device = wl_data_device_manager_get_data_device(w.data_device_manager, w.seat);
        wl_data_device_add_listener(w.data_device, &data_device_listener, &w);
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

    /* Host filter (blocklist + allowlist) ready before the first fetch. Placed after
     * the fallible Wayland setup so its error returns above never leak it. */
    w.hosts = build_host_filter();
    init_net_config(&w);  /* Tor/I2P routing config from the environment (opt-in) */

    /* Initial page. Provide instructions because the strict TLS policy means
       many public sites will be rejected. */
    if (start_url != NULL) {
        do_load(&w, start_url);
    } else {
        do_load(&w, "docs/index.html");
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
        /* While a fetch is in flight, wake ~12 fps to animate the spinner. */
        if (w.loading && (timeout < 0 || timeout > 80)) timeout = 80;

        /* Poll the Wayland fd, the key-repeat timer, and the async-fetch result pipe
         * together. The Wayland fd keeps the prepare_read/read_events contract; the
         * timer fires a held key's repeat; the pipe carries completed fetches. */
        struct pollfd pfds[3];
        int nfds = 0;
        pfds[nfds].fd = wl_display_get_fd(w.display); pfds[nfds].events = POLLIN; pfds[nfds].revents = 0; nfds++;
        int timer_idx = -1, fetch_idx = -1;
        if (w.repeat_timer_fd >= 0) {
            pfds[nfds].fd = w.repeat_timer_fd; pfds[nfds].events = POLLIN; pfds[nfds].revents = 0;
            timer_idx = nfds++;
        }
        if (w.fetch_pipe[0] >= 0) {
            pfds[nfds].fd = w.fetch_pipe[0]; pfds[nfds].events = POLLIN; pfds[nfds].revents = 0;
            fetch_idx = nfds++;
        }
        int pr = poll(pfds, (nfds_t)nfds, timeout);

        if (pr > 0 && (pfds[0].revents & POLLIN)) {
            if (wl_display_read_events(w.display) == -1) break;
            if (wl_display_dispatch_pending(w.display) == -1) break;
        } else {
            wl_display_cancel_read(w.display);
            if (pr < 0) { if (errno != EINTR) break; }       /* a real poll error */
            else if (pr == 0) redraw(&w);                    /* toast/spinner tick: repaint */
            else if (pfds[0].revents & (POLLHUP | POLLERR)) break; /* the display is gone */
        }

        /* A held key fired: re-apply it (read drains the expiration count so the timer
         * re-arms cleanly). Only acts while a repeat key is set. */
        if (pr > 0 && timer_idx >= 0 && (pfds[timer_idx].revents & POLLIN)) {
            uint64_t expirations;
            if (read(w.repeat_timer_fd, &expirations, sizeof expirations) > 0)
                key_repeat_fire(&w);
        }

        /* One or more fetches completed: render them on this (main) thread. */
        if (pr > 0 && fetch_idx >= 0 && (pfds[fetch_idx].revents & POLLIN))
            drain_fetch_results(&w);
    }

    destroy_buffer(&w);
    if (w.copy_source) wl_data_source_destroy(w.copy_source);
    free(w.copy_text);
    if (w.selection_offer) wl_data_offer_destroy(w.selection_offer);
    if (w.data_device) wl_data_device_destroy(w.data_device);
    if (w.data_device_manager) wl_data_device_manager_destroy(w.data_device_manager);
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

    if (w.repeat_timer_fd >= 0) close(w.repeat_timer_fd);
    /* Close the result pipe. Any still-running detached fetch worker that posts after
     * this gets a write error (SIGPIPE ignored) and frees its own job; the process is
     * exiting, so the OS reclaims the rest. */
    if (w.fetch_pipe[0] >= 0) close(w.fetch_pipe[0]);
    if (w.fetch_pipe[1] >= 0) close(w.fetch_pipe[1]);
    if (w.xkb_keymap) xkb_keymap_unref(w.xkb_keymap);
    if (w.xkb_state) xkb_state_unref(w.xkb_state);
    xkb_context_unref(w.xkb_ctx);

    /* Release background tabs (parked in slots); the foreground tab is freed via the
     * live fields just below. */
    for (int i = 0; i < w.tab_count; ++i) {
        if (i != w.active_tab) tab_ctx_release(&w.tab_slots[i]);
    }

    clear_doc(&w);
    hb_free(w.hosts);
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
