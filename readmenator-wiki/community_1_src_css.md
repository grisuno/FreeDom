# src: css

*Community 1 | 64 files | cohesion 0.70*

## Definition

This community groups 64 file(s) rooted at `src` with dominant language c (cohesion 0.70). Central symbols: `AUTO_REJECT`, `AUTO_RESET`, `AUTO_RESET_NONE`, `AUTO_VALUE`, `BUI_CHROME_FONT`, `BUI_CHROME_FONT_SIZE`, `BUI_DISABLED`, `BUI_FOCUS_RING`. Core file: `tests/test_css.c` (371 symbols). Documented purpose: bui_mask_img -- paints a mask-image: url() layer into a mask surface..

## Files

### `src` (21 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/chrome_layout.c` | c | presentation | 21 | yes |
| `src/compositor.c` | c | utility | 7 | no |
| `src/css.c` | c | utility | 273 | no |
| `src/css_atrule.c` | c | utility | 11 | no |
| `src/css_box.c` | c | utility | 53 | no |
| `src/css_chain.c` | c | utility | 26 | no |

### `include` (20 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/chrome_layout.h` | h | presentation | 41 | no |
| `include/compositor.h` | h | utility | 11 | no |
| `include/css.h` | h | utility | 148 | no |
| `include/css_atrule.h` | h | utility | 10 | no |
| `include/css_box.h` | h | utility | 28 | no |

### `tests` (19 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_chrome_layout.c` | c | testing | 18 | yes |
| `tests/test_compositor.c` | c | testing | 23 | no |
| `tests/test_css.c` | c | testing | 371 | no |
| `tests/test_css_atrule.c` | c | testing | 10 | yes |
| `tests/test_css_box.c` | c | testing | 13 | no |

### `gui` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui_internal.h` | h | presentation | 24 | no |
| `gui/bui_chrome.c` | c | utility | 61 | no |
| `gui/bui_mask_img.c` | c | utility | 1 | yes |
| `gui/bui_theme.c` | c | utility | 6 | no |

*... and 44 more files in this community.*


## Key Symbols

- `FREEDOM_BROWSER_UI_INTERNAL_H` (macro, `gui/browser_ui_internal.h:2`) `#define FREEDOM_BROWSER_UI_INTERNAL_H`
- `UI_FONT_SIZE` (macro, `gui/browser_ui_internal.h:30`) `#define UI_FONT_SIZE`
- `UI_TEXT_MARGIN` (macro, `gui/browser_ui_internal.h:31`) `#define UI_TEXT_MARGIN`
- `UI_HEADING_LEVELS` (macro, `gui/browser_ui_internal.h:32`) `#define UI_HEADING_LEVELS`
- `b` (type_alias, `gui/browser_ui_internal.h:40`) `typedef struct ui_rgb { double r, g, b;` - -- presentation theme ---  Every font size, spacing and colour the renderer uses, gathered in one pl
- `ui_rgb` (struct, `gui/browser_ui_internal.h:41`)
- `body_font` (type_alias, `gui/browser_ui_internal.h:42`) `typedef struct ui_theme { double body_font;`
- `ui_theme` (struct, `gui/browser_ui_internal.h:43`)
- `ui_theme_mode` (enum, `gui/browser_ui_internal.h:107`) - ui_rgb url_caret; ui_rgb url_select_bg; ui_rgb accent;          /* focus ring of the URL pill, activ
- `set_rgb` (function, `gui/browser_ui_internal.h:120`) `void set_rgb(cairo_t *cr, ui_rgb c);` - /* Selectable palettes for the options menu. typedef enum ui_theme_mode { UI_THEME_LIGHT = 0, UI_THE
- `BUI_CHROME_FONT` (macro, `gui/browser_ui_internal.h:127`) `#define BUI_CHROME_FONT`
- `BUI_CHROME_FONT_SIZE` (macro, `gui/browser_ui_internal.h:128`) `#define BUI_CHROME_FONT_SIZE`
- `BUI_URL_FONT_SIZE` (macro, `gui/browser_ui_internal.h:129`) `#define BUI_URL_FONT_SIZE`
- `bui_chrome_view` (struct, `gui/browser_ui_internal.h:132`) - ui_theme ui_theme_for(int mode);          /* maps a ui_theme_mode to a palette ui_rgb   rgb_from_pac
- `bui_find_view` (struct, `gui/browser_ui_internal.h:150`) - int                hot_tab;      /* tab under the pointer, or -1 const char *const *titles;       /*
- `bui_paint_findbar` (function, `gui/browser_ui_internal.h:163`) `void bui_paint_findbar(cairo_t *cr, const bui_find_view *v);`
- `bui_chrome_font` (function, `gui/browser_ui_internal.h:165`) `void bui_chrome_font(cairo_t *cr, double size);`
- `bui_paint_chrome` (function, `gui/browser_ui_internal.h:167`) `void bui_paint_chrome(cairo_t *cr, const bui_chrome_view *v);` - const char        *text;        /* query size_t             len, cursor; int                focused;
- `bui_url_text_x` (function, `gui/browser_ui_internal.h:170`) `double bui_url_text_x(const bui_chrome_view *v, cairo_t *cr, double *shift);` - X where URL text starts and the horizontal shift keeping the caret visible: * the single geometry th
- `bui_url_index_at` (function, `gui/browser_ui_internal.h:172`) `size_t bui_url_index_at(cairo_t *cr, const bui_chrome_view *v, double x);` - X where URL text starts and the horizontal shift keeping the caret visible: * the single geometry th
- `bui_round_rect` (function, `gui/browser_ui_internal.h:174`) `void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double` - X where URL text starts and the horizontal shift keeping the caret visible: * the single geometry th
- `bui_paint_video_bar` (function, `gui/browser_ui_internal.h:179`) `void bui_paint_video_bar(cairo_t *cr, const vcl_geom *g, int paused, double pos,` - The browser's player bar over a playing video (spec/video_controls.md), drawn in the * geometry g th
- `bui_paint_site_panel` (function, `gui/browser_ui_internal.h:183`) `void bui_paint_site_panel(cairo_t *cr, const ui_theme *th, const sp_panel *p, co` - The browser's player bar over a playing video (spec/video_controls.md), drawn in the * geometry g th
- `area` (function, `gui/browser_ui_internal.h:189`) `* tiled over the mask area (ax, ay, aw, ah) by the layer geometry `geo` (css.h C`
- `BUI_TWO_PI` (macro, `gui/bui_chrome.c:18`) `#define BUI_TWO_PI`
- `BUI_ICON_LINE` (macro, `gui/bui_chrome.c:19`) `#define BUI_ICON_LINE`
- `BUI_TAB_RADIUS` (macro, `gui/bui_chrome.c:20`) `#define BUI_TAB_RADIUS`
- `BUI_PILL_RADIUS` (macro, `gui/bui_chrome.c:21`) `#define BUI_PILL_RADIUS`
- `BUI_TAB_PAD` (macro, `gui/bui_chrome.c:22`) `#define BUI_TAB_PAD`
- `BUI_TAB_FADE` (macro, `gui/bui_chrome.c:23`) `#define BUI_TAB_FADE`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 115
- Cross-boundary resolved imports (EXTRACTED): 49

## Connections

- [EXTRACTED] depends_on community 0 <-> 1 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/compositor.h.
- [EXTRACTED] depends_on community 1 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui_internal.h imports include/freedom_config.h.
- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui_internal.h imports include/video_controls.h.

## Risks

- [layer strict] `tests/test_chrome_layout.c` (testing) -> `include/chrome_layout.h` (presentation)
- [layer strict] `tests/test_css.c` (testing) -> `include/flex_layout.h` (presentation)
- [dataflow DEAD_STORE] `src/css.c:6204` `page_view` `had_winner`: `had_winner` assigned at line 6204 but never read afterwards.

## Open Questions

- Why do 43 file(s) lack file-level docs (e.g. `gui/browser_ui_internal.h`)? What purpose do they serve?
- What would break if the most connected file in src: css changed?
- Should src: css be split, given cohesion 0.70?

## Sources

- `gui/browser_ui_internal.h`
- `gui/bui_chrome.c`
- `gui/bui_mask_img.c`
- `gui/bui_theme.c`
- `include/chrome_layout.h`
- `include/compositor.h`
- `include/css.h`
- `include/css_atrule.h`
- `include/css_box.h`
- `include/css_color.h`
- `include/css_computed.h`
- `include/css_counter.h`
- `include/css_decl.h`
- `include/css_gradient.h`
- `include/css_index.h`
- `include/css_length.h`
- `include/css_mask.h`
- `include/css_mq.h`
- `include/css_select.h`
- `include/css_text.h`
- *... and 44 more*
