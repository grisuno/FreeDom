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

/* --- chrome metrics shared by the theme and the painters --- */

#define UI_FONT_SIZE      14.0
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

#endif /* FREEDOM_BROWSER_UI_INTERNAL_H */
