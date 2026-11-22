#ifndef FREEDOM_BROWSER_UI_INTERNAL_H
#define FREEDOM_BROWSER_UI_INTERNAL_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * browser_ui_internal — shared vocabulary for the Wayland/Cairo GUI translation
 * units (gui/browser_ui.c and the gui/bui_*.c modules split off from it).
 *
 * This header is internal to gui/: it is NOT a public contract (those live in
 * include/). It exists so the monolithic browser_ui.c can be carved into smaller,
 * cohesive files without each one re-declaring the types and constants it shares.
 * As more pieces are extracted, the types and declarations they have in common
 * move here. Symbols promoted from file-local (static) to cross-TU linkage keep
 * their existing ui_/ui_theme_ namespacing.
 */

#include <cairo/cairo.h>

#include "freedom_config.h"

/* --- chrome metrics shared by the theme and the painters --- */

/* The web's base font size AND the root css.c resolves px/rem against. One number
 * governs both or the two drift: at 14 every page rendered ~12% small and an
 * absolute `font-size:40px` landed at 250% x 14 = 35px.
 * spec/box_style.md "Metricas UA del tema". */
#define UI_FONT_SIZE      FC_UI_FONT_SIZE
#define UI_TEXT_MARGIN    20.0   /* left/right/top breathing room around page content */
#define UI_HEADING_LEVELS 6      /* heading levels h1..h6; scale index 0 is body text */

/* --- presentation theme ---
 *
 * Every font size, spacing and colour the renderer uses, gathered in one place so
 * no value is hardcoded at a call site. An RGB colour is three components in
 * [0,1]. The structured-content painter and the window chrome both read from a
 * single theme instance (see ui_theme_default). */

typedef struct ui_rgb { double r, g, b; } ui_rgb;

typedef struct ui_theme {
    double body_font;                          /* body text size (px) */
    double heading_scale[UI_HEADING_LEVELS + 1]; /* [level] multiplier; [0] = body */
    double line_spacing;                       /* multiplier of font height per line */
    double paragraph_gap;                      /* extra px above a new paragraph block */
    double content_margin;                     /* left/right/top padding of the content area */
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
    /* Browser chrome (gui/bui_chrome.c). */
    ui_rgb tab_active_bg;   /* the selected tab; continues into the toolbar */
    ui_rgb url_text;        /* URL pill text (the host when unfocused) */
    ui_rgb url_text_dim;    /* scheme/path around the emphasised host */
    ui_rgb url_caret;
    ui_rgb url_select_bg;
    ui_rgb accent;          /* focus ring of the URL pill, active-tab marker */
    ui_rgb win_close_hot;   /* window close button under the pointer */
    ui_rgb id_good;         /* identity badge: post-quantum */
    ui_rgb id_warn;         /* identity badge: classical / weak / unknown */
    ui_rgb id_bad;          /* identity badge: unverified / plaintext */
    ui_rgb id_overlay;      /* identity badge: Tor / I2P */
    /* Find in page: fixed in every theme, since they paint over the author's colours. */
    ui_rgb find_hl;         /* every match */
    ui_rgb find_hl_cur;     /* the current match */
} ui_theme;

/* Selectable palettes for the options menu. */
typedef enum ui_theme_mode {
    UI_THEME_LIGHT = 0,
    UI_THEME_DARK,
    UI_THEME_SEPIA
} ui_theme_mode;

/* --- bui_theme.c: palette construction (pure; no window state) --- */

ui_theme ui_theme_default(void);
ui_theme ui_theme_dark(void);
ui_theme ui_theme_sepia(void);
ui_theme ui_theme_for(int mode);          /* maps a ui_theme_mode to a palette */
ui_rgb   rgb_from_packed(int packed);     /* 0xRRGGBB author colour -> theme RGB */
void     set_rgb(cairo_t *cr, ui_rgb c);  /* cairo_set_source_rgb from a ui_rgb */

/* --- bui_chrome.c: the browser chrome painter (geometry from chrome_layout) --- */

#include "chrome_layout.h"
#include <stddef.h>

#define BUI_CHROME_FONT      "sans-serif"
#define BUI_CHROME_FONT_SIZE 13.0
#define BUI_URL_FONT_SIZE    14.0

/* Everything the chrome painter shows, gathered by the orchestrator. Borrowed. */
typedef struct bui_chrome_view {
    const chl_layout  *l;
    const ui_theme    *th;
    chl_part           hot_part;     /* part under the pointer */
    int                hot_tab;      /* tab under the pointer, or -1 */
    const char *const *titles;       /* tab_count titles (never NULL entries) */
    const int         *tab_loading;  /* tab_count flags, or NULL */
    double             phase;        /* spinner phase in [0,1) */
    int                can_back, can_fwd, maximized;
    int                loading;      /* the active tab is loading: reload shows Stop */
    const char        *url;          /* URL bar text */
    size_t             url_len, cursor, sel_start, sel_len;
    int                url_focused;
    chl_identity       identity;
} bui_chrome_view;

/* Selects the chrome face at `size` on cr. */
/* The find bar (spec/find_text.md). */
typedef struct bui_find_view {
    const chl_findbar *f;
    const ui_theme    *th;
    const char        *text;        /* query */
    size_t             len, cursor;
    int                focused;
    int                selected;    /* the whole query is selected (just reopened) */
    size_t             total;       /* matches kept */
    long               current;     /* index of the current match, -1 = none */
    int                truncated;   /* more matches than kept */
    chl_find_part      hot;         /* part under the pointer */
} bui_find_view;

void bui_paint_findbar(cairo_t *cr, const bui_find_view *v);

void bui_chrome_font(cairo_t *cr, double size);
/* Paints both chrome rows. */
void bui_paint_chrome(cairo_t *cr, const bui_chrome_view *v);
/* X where URL text starts and the horizontal shift keeping the caret visible:
 * the single geometry the painter and the click-to-caret mapping share. */
double bui_url_text_x(const bui_chrome_view *v, cairo_t *cr, double *shift);
/* Byte index of the URL caret for a click at surface x (UTF-8 boundary). */
size_t bui_url_index_at(cairo_t *cr, const bui_chrome_view *v, double x);
/* Rounded rectangle path. */
void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double r);

/* --- bui_mask_img.c: a mask-image url() layer into a mask surface --- */

/* Paints the decoded image `img` (nat_w x nat_h) as an alpha source into `c`, placed and
 * tiled over the mask area (ax, ay, aw, ah) by the layer geometry `geo` (css.h CSS_MG_*,
 * resolved by bx_background_layer). 1 = painted, 0 = nothing usable. */
int bui_paint_mask_image(cairo_t *c, cairo_surface_t *img, int nat_w, int nat_h,
                         const int geo[10], double ax, double ay, double aw, double ah);

#endif /* FREEDOM_BROWSER_UI_INTERNAL_H */
