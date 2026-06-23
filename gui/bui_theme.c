/*
 * bui_theme — presentation palettes for the Wayland/Cairo GUI.
 *
 * Carved out of browser_ui.c: the light/dark/sepia themes and the small colour
 * helpers, none of which touch window state. The theme is the single source of
 * truth for every font size, spacing and colour the renderer and chrome use.
 */

#include "browser_ui_internal.h"

#include "css_color.h"

/* The single source of truth for the look of the browser. */
ui_theme ui_theme_default(void) {
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
ui_theme ui_theme_dark(void) {
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
ui_theme ui_theme_sepia(void) {
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

/* The single place that maps the theme mode to a palette. */
ui_theme ui_theme_for(int mode) {
    switch (mode) {
        case UI_THEME_DARK:  return ui_theme_dark();
        case UI_THEME_SEPIA: return ui_theme_sepia();
        default:             return ui_theme_default();
    }
}

/* Converts a packed 0xRRGGBB author color into a theme RGB triple. */
ui_rgb rgb_from_packed(int packed) {
    cc_rgb c = cc_unpack(packed);
    return (ui_rgb){ c.r / 255.0, c.g / 255.0, c.b / 255.0 };
}

void set_rgb(cairo_t *cr, ui_rgb c) {
    cairo_set_source_rgb(cr, c.r, c.g, c.b);
}
