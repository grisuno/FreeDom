# gui

*Community 5 | 15 files | cohesion 0.50*

## Definition

This community groups 15 file(s) rooted at `gui` with dominant language c (cohesion 0.50). Central symbols: `FC_FLEX_MEASURE_W`, `FC_FLEX_MIN_MEASURE_W`, `FC_FONT_CHAIN_MAX`, `FC_FONT_FALLBACK_PX`, `FC_HEADLESS_VIEW_H`, `FC_MAX_AUTHOR_CSS_BYTES`, `FC_MAX_BOXES`, `FC_PNG_MARGIN`. Core file: `src/svg_render.c` (33 symbols). Documented purpose: svg_paint — Cairo back end for the shapes svg_render extracted..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_page_view.c` | c | presentation | 0 | no |
| `fuzz/fuzz_svg_render.c` | c | presentation | 1 | no |
| `gui/browser_ui_internal.h` | h | presentation | 10 | no |
| `gui/bui_theme.c` | c | utility | 6 | no |
| `gui/freedom_view.c` | c | presentation | 2 | no |
| `gui/svg_paint.c` | c | utility | 5 | yes |
| `gui/ui_render.c` | c | presentation | 29 | no |
| `include/freedom_config.h` | h | infrastructure | 13 | no |
| `include/svg_paint.h` | h | utility | 2 | no |
| `include/svg_render.h` | h | presentation | 19 | no |
| `include/ui.h` | h | presentation | 17 | no |
| `src/svg_render.c` | c | presentation | 33 | yes |
| `src/ui_layout.c` | c | presentation | 4 | no |
| `tests/test_svg_render.c` | c | testing | 16 | yes |
| `tests/test_ui.c` | c | testing | 12 | no |

## Key Symbols

- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_svg_render.c:24`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
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
- `_POSIX_C_SOURCE` (macro, `gui/freedom_view.c:10`) `#define _POSIX_C_SOURCE`
- `main` (function, `gui/freedom_view.c:37`) `int main(int argc, char **argv)`
- `svp_alpha` (function, `gui/svg_paint.c:31`) `static double svp_alpha(int opacity, int paint_opacity)` - Resolves a shape's packed paint into an RGB triple. Returns 0 when the shape * asked for no paint at
- `svp_rect_path` (function, `gui/svg_paint.c:38`) `static void svp_rect_path(cairo_t *cr, const sv_shape *sh)` - r = (double)((c >> 16) & 0xFF) / 255.0; g = (double)((c >> 8) & 0xFF) / 255.0; b = (double)(c & 0xFF
- `svp_shape_path` (function, `gui/svg_paint.c:73`) `static void svp_shape_path(cairo_t *cr, const sv_image *img, const sv_shape *sh)`
- `svp_draw_text` (function, `gui/svg_paint.c:126`) `static void svp_draw_text(cairo_t *cr, const sv_shape *sh, int current_rgb)`
- `svp_draw` (function, `gui/svg_paint.c:139`) `void svp_draw(cairo_t *cr, const sv_image *img,               double x, double y`
- `_GNU_SOURCE` (macro, `gui/ui_render.c:10`) `#define _GNU_SOURCE`
- `UI_FONT_SIZE` (macro, `gui/ui_render.c:28`) `#define UI_FONT_SIZE`
- `UI_MARGIN` (macro, `gui/ui_render.c:29`) `#define UI_MARGIN`
- `UI_TITLEBAR_H` (macro, `gui/ui_render.c:30`) `#define UI_TITLEBAR_H`
- `UI_BTN_W` (macro, `gui/ui_render.c:31`) `#define UI_BTN_W`
- `UI_BTN_LEFT` (macro, `gui/ui_render.c:32`) `#define UI_BTN_LEFT`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 14
- Cross-boundary resolved imports (EXTRACTED): 14

## Connections

- [EXTRACTED] depends_on community 5 <-> 0 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_page_view.c imports include/html_parse.h.
- [EXTRACTED] depends_on community 5 <-> 3 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_page_view.c imports include/page_view.h.
- [EXTRACTED] depends_on community 1 <-> 5 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/svg_paint.h.
- [EXTRACTED] depends_on community 5 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/bui_theme.c imports include/css_color.h.

## Risks

- [layer strict] `tests/test_svg_render.c` (testing) -> `include/svg_render.h` (presentation)
- [layer strict] `tests/test_ui.c` (testing) -> `include/ui.h` (presentation)

## Open Questions

- Why do 12 file(s) lack file-level docs (e.g. `fuzz/fuzz_page_view.c`)? What purpose do they serve?
- What would break if the most connected file in gui changed?
- Should gui be split, given cohesion 0.50?

## Sources

- `fuzz/fuzz_page_view.c`
- `fuzz/fuzz_svg_render.c`
- `gui/browser_ui_internal.h`
- `gui/bui_theme.c`
- `gui/freedom_view.c`
- `gui/svg_paint.c`
- `gui/ui_render.c`
- `include/freedom_config.h`
- `include/svg_paint.h`
- `include/svg_render.h`
- `include/ui.h`
- `src/svg_render.c`
- `src/ui_layout.c`
- `tests/test_svg_render.c`
- `tests/test_ui.c`
