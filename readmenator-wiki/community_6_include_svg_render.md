# include: svg_render

*Community 6 | 16 files | cohesion 0.52*

## Definition

This community groups 16 file(s) rooted at `include` with dominant language c (cohesion 0.52). Central symbols: `ERR_FILE`, `FC_FLEX_MEASURE_W`, `FC_FLEX_MIN_MEASURE_W`, `FC_FONT_CHAIN_MAX`, `FC_FONT_FALLBACK_PX`, `FC_HEADLESS_VIEW_H`, `FC_LAZY_IMAGE_MARGIN_PX`, `FC_MAX_AUTHOR_CSS_BYTES`. Core file: `tests/test_freedom.c` (111 symbols). Documented purpose: svg_paint — Cairo back end for the shapes svg_render extracted..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui_internal.h` | h | presentation | 11 | no |
| `gui/bui_theme.c` | c | utility | 6 | no |
| `gui/ui_render.c` | c | presentation | 29 | no |
| `include/freedom_config.h` | h | infrastructure | 15 | no |
| `include/image_decode.h` | h | utility | 14 | no |
| `include/svg_paint.h` | h | utility | 3 | no |
| `include/svg_raster.h` | h | utility | 5 | no |
| `include/svg_render.h` | h | presentation | 19 | no |
| `src/image_decode.c` | c | utility | 27 | no |
| `src/svg_paint.c` | c | utility | 6 | yes |
| `src/svg_raster.c` | c | utility | 4 | yes |
| `src/svg_render.c` | c | presentation | 34 | yes |
| `tests/test_freedom.c` | c | testing | 111 | no |
| `tests/test_image_decode.c` | c | testing | 37 | no |
| `tests/test_svg_raster.c` | c | testing | 10 | yes |
| `tests/test_svg_render.c` | c | testing | 17 | yes |

## Key Symbols

- `FREEDOM_BROWSER_UI_INTERNAL_H` (macro, `gui/browser_ui_internal.h:2`) `#define FREEDOM_BROWSER_UI_INTERNAL_H`
- `UI_FONT_SIZE` (macro, `gui/browser_ui_internal.h:30`) `#define UI_FONT_SIZE`
- `UI_TEXT_MARGIN` (macro, `gui/browser_ui_internal.h:31`) `#define UI_TEXT_MARGIN`
- `UI_HEADING_LEVELS` (macro, `gui/browser_ui_internal.h:32`) `#define UI_HEADING_LEVELS`
- `b` (type_alias, `gui/browser_ui_internal.h:40`) `typedef struct ui_rgb { double r, g, b;` - -- presentation theme ---  Every font size, spacing and colour the renderer uses, gathered in one pl
- `ui_rgb` (struct, `gui/browser_ui_internal.h:41`)
- `body_font` (type_alias, `gui/browser_ui_internal.h:42`) `typedef struct ui_theme { double body_font;`
- `ui_theme` (struct, `gui/browser_ui_internal.h:43`)
- `ui_theme_mode` (enum, `gui/browser_ui_internal.h:92`) - ui_rgb button_text; ui_rgb menu_bg; ui_rgb menu_border; ui_rgb menu_text; ui_rgb check_border; ui_rg
- `set_rgb` (function, `gui/browser_ui_internal.h:105`) `void set_rgb(cairo_t *cr, ui_rgb c);` - /* Selectable palettes for the options menu. typedef enum ui_theme_mode { UI_THEME_LIGHT = 0, UI_THE
- `area` (function, `gui/browser_ui_internal.h:110`) `* tiled over the mask area (ax, ay, aw, ah) by the layer geometry `geo` (css.h C`
- `ui_theme_default` (function, `gui/bui_theme.c:15`) `ui_theme ui_theme_default(void)` - bui_theme — presentation palettes for the Wayland/Cairo GUI.  Carved out of browser_ui.c: the light/
- `ui_theme_dark` (function, `gui/bui_theme.c:78`) `ui_theme ui_theme_dark(void)` - Dark reading palette. Shares all the metrics (font sizes, spacing) with the * default theme; only th
- `ui_theme_sepia` (function, `gui/bui_theme.c:123`) `ui_theme ui_theme_sepia(void)` - Sepia reading palette: warm paper background and dark-brown ink, easier on the eyes for long-form te
- `ui_theme_for` (function, `gui/bui_theme.c:165`) `ui_theme ui_theme_for(int mode)` - t.menu_bg        = (ui_rgb){ 0.95, 0.90, 0.80 }; t.menu_border    = (ui_rgb){ 0.55, 0.46, 0.32 }; t.
- `rgb_from_packed` (function, `gui/bui_theme.c:174`) `ui_rgb rgb_from_packed(int packed)` - t.scrollbar_thumb_hot = (ui_rgb){ 0.44, 0.35, 0.22 }; return t; } /* The single place that maps the
- `set_rgb` (function, `gui/bui_theme.c:179`) `void set_rgb(cairo_t *cr, ui_rgb c)`
- `_GNU_SOURCE` (macro, `gui/ui_render.c:10`) `#define _GNU_SOURCE`
- `UI_FONT_SIZE` (macro, `gui/ui_render.c:28`) `#define UI_FONT_SIZE`
- `UI_MARGIN` (macro, `gui/ui_render.c:29`) `#define UI_MARGIN`
- `UI_TITLEBAR_H` (macro, `gui/ui_render.c:30`) `#define UI_TITLEBAR_H`
- `UI_BTN_W` (macro, `gui/ui_render.c:31`) `#define UI_BTN_W`
- `UI_BTN_LEFT` (macro, `gui/ui_render.c:32`) `#define UI_BTN_LEFT`
- `sanitize_utf8_inplace` (function, `gui/ui_render.c:39`) `static void sanitize_utf8_inplace(char *s)` - Rewrites s in place to well-formed UTF-8, replacing any byte that is not part of a valid sequence wi
- `ui_window` (struct, `gui/ui_render.c:67`)
- `button_rects` (function, `gui/ui_render.c:107`) `static void button_rects(const ui_window *w, double *min_x, double *max_x, doubl` - int    use_csd;    /* draw our own titlebar/controls (compositor has no SSD) int    maximized; doubl
- `buffer_release` (function, `gui/ui_render.c:115`) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
- `destroy_buffer` (function, `gui/ui_render.c:122`) `static void destroy_buffer(ui_window *w)`
- `ensure_buffer` (function, `gui/ui_render.c:128`) `static int ensure_buffer(ui_window *w)`
- `paint` (function, `gui/ui_render.c:159`) `static void paint(ui_window *w)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 16
- Cross-boundary resolved imports (EXTRACTED): 15

## Connections

- [EXTRACTED] depends_on community 1 <-> 6 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/svg_paint.h.
- [EXTRACTED] depends_on community 4 <-> 6 (strength 0.9): Extracted import edge crosses communities: gui/bui_mask_img.c imports gui/browser_ui_internal.h.
- [EXTRACTED] depends_on community 6 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/bui_theme.c imports include/css_color.h.

## Risks

- [layer strict] `tests/test_svg_render.c` (testing) -> `include/svg_render.h` (presentation)
- [dataflow DEAD_STORE] `src/image_decode.c:224` `img_decode_jpeg` `dst`: `dst` assigned at line 224 but never read afterwards.

## Open Questions

- Why do 11 file(s) lack file-level docs (e.g. `gui/browser_ui_internal.h`)? What purpose do they serve?
- What would break if the most connected file in include: svg_render changed?
- Should include: svg_render be split, given cohesion 0.52?

## Sources

- `gui/browser_ui_internal.h`
- `gui/bui_theme.c`
- `gui/ui_render.c`
- `include/freedom_config.h`
- `include/image_decode.h`
- `include/svg_paint.h`
- `include/svg_raster.h`
- `include/svg_render.h`
- `src/image_decode.c`
- `src/svg_paint.c`
- `src/svg_raster.c`
- `src/svg_render.c`
- `tests/test_freedom.c`
- `tests/test_image_decode.c`
- `tests/test_svg_raster.c`
- `tests/test_svg_render.c`
