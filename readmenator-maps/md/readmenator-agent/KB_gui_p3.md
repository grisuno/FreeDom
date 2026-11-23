# Subsystem: gui (page 3 of 3)
Previous: [KB_gui_p2.md](KB_gui_p2.md)

## gui/bui_chrome.c
- Doc: tab_path: void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double r) {...
- Layer: utility
- Language: c
- Symbols:
  - `bui_round_rect` (function, line 35) `void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `tab_path` (function, line 48) `static void tab_path(cairo_t *cr, chl_rect t, double r)`
  - `set_rgba` (function, line 57) `static void set_rgba(cairo_t *cr, ui_rgb c, double a)`
  - `bui_chrome_font` (function, line 61) `void bui_chrome_font(cairo_t *cr, double size)`
  - `rcx` (function, line 66) `static double rcx(chl_rect r)`
  - `rcy` (function, line 67) `static double rcy(chl_rect r)`
  - `icon_stroke` (function, line 69) `static void icon_stroke(cairo_t *cr)`
  - `icon_arrow` (function, line 76) `static void icon_arrow(cairo_t *cr, double cx, double cy, int dir)`
  - `icon_reload` (function, line 87) `static void icon_reload(cairo_t *cr, double cx, double cy)`
  - `icon_menu` (function, line 99) `static void icon_menu(cairo_t *cr, double cx, double cy)`
  - `icon_cross` (function, line 107) `static void icon_cross(cairo_t *cr, double cx, double cy, double h)`
  - `icon_plus` (function, line 115) `static void icon_plus(cairo_t *cr, double cx, double cy, double h)`
  - `spinner` (function, line 123) `static void spinner(cairo_t *cr, ui_rgb c, double cx, double cy, double phase)`
  - `glyph_shield` (function, line 137) `static void glyph_shield(cairo_t *cr, double cx, double cy, int check, int fill)`
  - `glyph_lock` (function, line 161) `static void glyph_lock(cairo_t *cr, double cx, double cy)`
  - `glyph_warning` (function, line 173) `static void glyph_warning(cairo_t *cr, double cx, double cy)`
  - `glyph_overlay` (function, line 192) `static void glyph_overlay(cairo_t *cr, double cx, double cy)`
  - `glyph_page` (function, line 200) `static void glyph_page(cairo_t *cr, double cx, double cy)`
  - `glyph_info` (function, line 210) `static void glyph_info(cairo_t *cr, double cx, double cy)`
  - `paint_identity` (function, line 220) `static void paint_identity(cairo_t *cr, const bui_chrome_view *v)`
  - `star_path` (function, line 269) `static void star_path(cairo_t *cr, double cx, double cy, double ro)`
  - `paint_star` (function, line 280) `static void paint_star(cairo_t *cr, const bui_chrome_view *v)`
  - `url_text_end` (function, line 302) `static double url_text_end(const bui_chrome_view *v)`
  - `utf8_next` (function, line 310) `static size_t utf8_next(const char *s, size_t n, size_t i)`
  - `text_w` (function, line 317) `static double text_w(cairo_t *cr, const char *s, size_t n)`
  - `show_n` (function, line 327) `static void show_n(cairo_t *cr, const char *s, size_t n)`
  - `bui_url_text_x` (function, line 335) `double bui_url_text_x(const bui_chrome_view *v, cairo_t *cr, double *shift)`
  - `bui_url_index_at` (function, line 349) `size_t bui_url_index_at(cairo_t *cr, const bui_chrome_view *v, double x)`
  - `paint_url` (function, line 386) `static void paint_url(cairo_t *cr, const bui_chrome_view *v)`
  - `round_button` (function, line 459) `static void round_button(cairo_t *cr, const bui_chrome_view *v, chl_rect r, chl_part part,
      ...`
  - `paint_toolbar` (function, line 470) `static void paint_toolbar(cairo_t *cr, const bui_chrome_view *v)`
  - `tab_title` (function, line 489) `static void tab_title(cairo_t *cr, const char *s, ui_rgb c, double alpha,
                      d...`
  - `icon_side_chevron` (function, line 521) `static void icon_side_chevron(cairo_t *cr, double cx, double cy, int dir)`
  - `paint_tabstrip` (function, line 554) `static void paint_tabstrip(cairo_t *cr, const bui_chrome_view *v)`
  - `bui_paint_chrome` (function, line 646) `void bui_paint_chrome(cairo_t *cr, const bui_chrome_view *v)`
  - `paint_find_field` (function, line 663) `static void paint_find_field(cairo_t *cr, const bui_find_view *v)`
  - `find_button` (function, line 712) `static void find_button(cairo_t *cr, const bui_find_view *v, chl_rect r, chl_find_part part,
    ...`
  - `icon_chevron` (function, line 724) `static void icon_chevron(cairo_t *cr, double cx, double cy, int dir)`
  - `bui_paint_findbar` (function, line 732) `void bui_paint_findbar(cairo_t *cr, const bui_find_view *v)`
  - `mix_rgb` (function, line 785) `static ui_rgb mix_rgb(ui_rgb a, ui_rgb b, double t)`
  - `tone_rgb` (function, line 793) `static ui_rgb tone_rgb(const ui_theme *th, sp_tone t)`
  - `text_in` (function, line 804) `static void text_in(cairo_t *cr, const char *s, double x, double baseline, double w, double top,
...`
  - `bui_paint_site_panel` (function, line 815) `void bui_paint_site_panel(cairo_t *cr, const ui_theme *th, const sp_panel *p, const sp_geom *g,
 ...`
  - `bui_paint_video_bar` (function, line 903) `void bui_paint_video_bar(cairo_t *cr, const vcl_geom *g, int paused, double pos, double total)`
  - `bui_link_status_flips` (function, line 962) `int bui_link_status_flips(const double zone[3], double ptr_x, double ptr_y)`
  - `bui_paint_link_status` (function, line 966) `double bui_paint_link_status(cairo_t *cr, const ui_theme *th, const lp_preview *p, double left,
 ...`
  - `BUI_TWO_PI` (macro, line 18) `#define BUI_TWO_PI`
  - `BUI_ICON_LINE` (macro, line 19) `#define BUI_ICON_LINE`
  - `BUI_TAB_RADIUS` (macro, line 20) `#define BUI_TAB_RADIUS`
  - `BUI_PILL_RADIUS` (macro, line 21) `#define BUI_PILL_RADIUS`
  - `BUI_TAB_PAD` (macro, line 22) `#define BUI_TAB_PAD`
  - `BUI_TAB_FADE` (macro, line 23) `#define BUI_TAB_FADE`
  - `BUI_SPINNER_R` (macro, line 24) `#define BUI_SPINNER_R`
  - `BUI_STOP_HALF` (macro, line 25) `#define BUI_STOP_HALF`
  - `BUI_URL_TEXT_PAD` (macro, line 26) `#define BUI_URL_TEXT_PAD`
  - `BUI_URL_END_PAD` (macro, line 27) `#define BUI_URL_END_PAD`
  - `BUI_FOCUS_RING` (macro, line 28) `#define BUI_FOCUS_RING`
  - `BUI_INACTIVE_TEXT` (macro, line 29) `#define BUI_INACTIVE_TEXT`
  - `BUI_DISABLED` (macro, line 30) `#define BUI_DISABLED`
  - `BUI_URL_MEASURE` (macro, line 31) `#define BUI_URL_MEASURE`
  - `BUI_SP_RADIUS` (macro, line 781) `#define BUI_SP_RADIUS`
  - `BUI_SP_LABEL_W` (macro, line 782) `#define BUI_SP_LABEL_W`
  - `BUI_VBAR_ALPHA` (macro, line 898) `#define BUI_VBAR_ALPHA`
  - `BUI_VTRACK_ALPHA` (macro, line 899) `#define BUI_VTRACK_ALPHA`
  - `BUI_VKNOB_R` (macro, line 900) `#define BUI_VKNOB_R`
  - `BUI_VTEXT_SIZE` (macro, line 901) `#define BUI_VTEXT_SIZE`
  - `BUI_LS_PAD_X` (macro, line 956) `#define BUI_LS_PAD_X`
  - `BUI_LS_PAD_Y` (macro, line 957) `#define BUI_LS_PAD_Y`
  - `BUI_LS_RADIUS` (macro, line 958) `#define BUI_LS_RADIUS`
  - `BUI_LS_MAX_FRAC` (macro, line 959) `#define BUI_LS_MAX_FRAC`
  - `BUI_LS_FONT` (macro, line 960) `#define BUI_LS_FONT`
- Depends on: `gui/browser_ui_internal.h`

## gui/bui_mask_img.c
- Doc: bui_mask_img -- paints a mask-image: url() layer into a mask surface.
- Layer: utility
- Language: c
- Symbols:
  - `bui_paint_mask_image` (function, line 17) `int bui_paint_mask_image(cairo_t *c, cairo_surface_t *img, int nat_w, int nat_h,
                ...`
- Depends on: `gui/browser_ui_internal.h`, `include/box_style.h`, `include/css.h`

## gui/bui_theme.c
- Doc: ui_theme_default: bui_theme — presentation palettes for the Wayland/Cairo GUI.
- Layer: utility
- Language: c
- Symbols:
  - `ui_theme_default` (function, line 15) `ui_theme ui_theme_default(void)`
  - `ui_theme_dark` (function, line 91) `ui_theme ui_theme_dark(void)`
  - `ui_theme_sepia` (function, line 137) `ui_theme ui_theme_sepia(void)`
  - `ui_theme_for` (function, line 189) `ui_theme ui_theme_for(int mode)`
  - `rgb_from_packed` (function, line 198) `ui_rgb rgb_from_packed(int packed)`
  - `set_rgb` (function, line 203) `void set_rgb(cairo_t *cr, ui_rgb c)`
- Depends on: `gui/browser_ui_internal.h`, `include/css.h`, `include/css_color.h`

## gui/freedom_view.c
- Layer: presentation
- Language: c
- Symbols:
  - `main` (function, line 37) `int main(int argc, char **argv)`
  - `_POSIX_C_SOURCE` (macro, line 10) `#define _POSIX_C_SOURCE`
- Depends on: `include/html_parse.h`, `include/ui.h`

## gui/ui_render.c
- Doc: sanitize_utf8_inplace: Rewrites s in place to well-formed UTF-8, replacing any byte that is not...
- Layer: presentation
- Language: c
- Symbols:
  - `ui_window` (struct, line 67)
  - `sanitize_utf8_inplace` (function, line 39) `static void sanitize_utf8_inplace(char *s)`
  - `button_rects` (function, line 107) `static void button_rects(const ui_window *w, double *min_x, double *max_x, double *close_x)`
  - `buffer_release` (function, line 115) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 122) `static void destroy_buffer(ui_window *w)`
  - `ensure_buffer` (function, line 128) `static int ensure_buffer(ui_window *w)`
  - `paint` (function, line 159) `static void paint(ui_window *w)`
  - `redraw` (function, line 245) `static void redraw(ui_window *w)`
  - `wm_base_ping` (function, line 260) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 266) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 274) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `toplevel_close` (function, line 283) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 294) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `ptr_enter` (function, line 305) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
  - `ptr_leave` (function, line 312) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
  - `ptr_motion` (function, line 315) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
  - `ptr_button` (function, line 322) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
  - `ptr_axis` (function, line 344) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
  - `seat_caps` (function, line 367) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
  - `seat_name` (function, line 376) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
  - `registry_global` (function, line 383) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
  - `registry_remove` (function, line 401) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
  - `ui_run_text_view` (function, line 410) `ui_status ui_run_text_view(const char *title, const char *text, size_t text_len)`
  - `_GNU_SOURCE` (macro, line 10) `#define _GNU_SOURCE`
  - `UI_FONT_SIZE` (macro, line 28) `#define UI_FONT_SIZE`
  - `UI_MARGIN` (macro, line 29) `#define UI_MARGIN`
  - `UI_TITLEBAR_H` (macro, line 30) `#define UI_TITLEBAR_H`
  - `UI_BTN_W` (macro, line 31) `#define UI_BTN_W`
  - `UI_BTN_LEFT` (macro, line 32) `#define UI_BTN_LEFT`
- Depends on: `include/freedom_config.h`, `include/ui.h`

