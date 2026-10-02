# gui

*Community 7 | 5 files | cohesion 0.33*

## Definition

This community groups 5 file(s) rooted at `gui` with dominant language c (cohesion 0.33). Central symbols: `FC_FLEX_MEASURE_W`, `FC_FLEX_MIN_MEASURE_W`, `FC_FONT_CHAIN_MAX`, `FC_FONT_FALLBACK_PX`, `FC_HEADLESS_VIEW_H`, `FC_MAX_AUTHOR_CSS_BYTES`, `FC_MAX_BOXES`, `FC_PNG_MARGIN`. Core file: `gui/ui_render.c` (29 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_page_view.c` | c | presentation | 0 | no |
| `gui/browser_ui_internal.h` | h | presentation | 10 | no |
| `gui/bui_theme.c` | c | presentation | 6 | no |
| `gui/ui_render.c` | c | presentation | 29 | no |
| `include/freedom_config.h` | h | infrastructure | 13 | no |

## Key Symbols

- `FREEDOM_BROWSER_UI_INTERNAL_H` (macro, `gui/browser_ui_internal.h:2`) `#define FREEDOM_BROWSER_UI_INTERNAL_H`
- `UI_FONT_SIZE` (macro, `gui/browser_ui_internal.h:30`) `#define UI_FONT_SIZE`
- `UI_TEXT_MARGIN` (macro, `gui/browser_ui_internal.h:31`) `#define UI_TEXT_MARGIN`
- `UI_HEADING_LEVELS` (macro, `gui/browser_ui_internal.h:32`) `#define UI_HEADING_LEVELS`
- `b` (type_alias, `gui/browser_ui_internal.h:40`) `typedef struct ui_rgb { double r, g, b;` - -- presentation theme ---  Every font size, spacing and colour the renderer uses, gathered in one pl
- `ui_rgb` (struct, `gui/browser_ui_internal.h:41`)
- `body_font` (type_alias, `gui/browser_ui_internal.h:42`) `typedef struct ui_theme { double body_font;`
- `ui_theme` (struct, `gui/browser_ui_internal.h:43`)
- `ui_theme_mode` (enum, `gui/browser_ui_internal.h:93`) - ui_rgb button_text; ui_rgb menu_bg; ui_rgb menu_border; ui_rgb menu_text; ui_rgb check_border; ui_rg
- `set_rgb` (function, `gui/browser_ui_internal.h:106`) `void set_rgb(cairo_t *cr, ui_rgb c);` - /* Selectable palettes for the options menu. typedef enum ui_theme_mode { UI_THEME_LIGHT = 0, UI_THE
- `ui_theme_default` (function, `gui/bui_theme.c:14`) `ui_theme ui_theme_default(void)` - bui_theme — presentation palettes for the Wayland/Cairo GUI.  Carved out of browser_ui.c: the light/
- `ui_theme_dark` (function, `gui/bui_theme.c:84`) `ui_theme ui_theme_dark(void)` - Dark reading palette. Shares all the metrics (font sizes, spacing) with the * default theme; only th
- `ui_theme_sepia` (function, `gui/bui_theme.c:129`) `ui_theme ui_theme_sepia(void)` - Sepia reading palette: warm paper background and dark-brown ink, easier on the eyes for long-form te
- `ui_theme_for` (function, `gui/bui_theme.c:171`) `ui_theme ui_theme_for(int mode)` - t.menu_bg        = (ui_rgb){ 0.95, 0.90, 0.80 }; t.menu_border    = (ui_rgb){ 0.55, 0.46, 0.32 }; t.
- `rgb_from_packed` (function, `gui/bui_theme.c:180`) `ui_rgb rgb_from_packed(int packed)` - t.scrollbar_thumb_hot = (ui_rgb){ 0.44, 0.35, 0.22 }; return t; } /* The single place that maps the
- `set_rgb` (function, `gui/bui_theme.c:185`) `void set_rgb(cairo_t *cr, ui_rgb c)`
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
- `redraw` (function, `gui/ui_render.c:245`) `static void redraw(ui_window *w)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 4
- Cross-boundary resolved imports (EXTRACTED): 8

## Connections

- [EXTRACTED] depends_on community 7 <-> 2 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_page_view.c imports include/html_parse.h.
- [EXTRACTED] depends_on community 7 <-> 3 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_page_view.c imports include/page_view.h.
- [EXTRACTED] depends_on community 7 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/bui_theme.c imports include/css_color.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 5 file(s) lack file-level docs (e.g. `fuzz/fuzz_page_view.c`)? What purpose do they serve?
- What would break if the most connected file in gui changed?
- Should gui be split, given cohesion 0.33?

## Sources

- `fuzz/fuzz_page_view.c`
- `gui/browser_ui_internal.h`
- `gui/bui_theme.c`
- `gui/ui_render.c`
- `include/freedom_config.h`
