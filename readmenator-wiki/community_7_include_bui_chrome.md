# include: bui_chrome

*Community 7 | 20 files | cohesion 0.61*

## Definition

This community groups 20 file(s) rooted at `include` with dominant language c (cohesion 0.61). Central symbols: `BUI_CHROME_FONT`, `BUI_CHROME_FONT_SIZE`, `BUI_DISABLED`, `BUI_FOCUS_RING`, `BUI_ICON_LINE`, `BUI_INACTIVE_TEXT`, `BUI_LS_FONT`, `BUI_LS_MAX_FRAC`. Core file: `gui/bui_chrome.c` (71 symbols). Documented purpose: libFuzzer harness for chrome_layout (spec/chrome_layout.md): a hostile URL (a page.

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_chrome_layout.c` | c | presentation | 3 | yes |
| `fuzz/fuzz_link_preview.c` | c | utility | 1 | yes |
| `fuzz/fuzz_url.c` | c | utility | 2 | no |
| `fuzz/fuzz_video_controls.c` | c | utility | 2 | no |
| `gui/browser_ui_internal.h` | h | presentation | 26 | no |
| `gui/bui_chrome.c` | c | utility | 71 | no |
| `gui/bui_mask_img.c` | c | utility | 1 | yes |
| `gui/bui_theme.c` | c | utility | 6 | no |
| `include/chrome_layout.h` | h | presentation | 44 | no |
| `include/link_nav.h` | h | utility | 11 | no |
| `include/link_preview.h` | h | utility | 6 | no |
| `include/video_controls.h` | h | utility | 23 | no |
| `src/chrome_layout.c` | c | presentation | 22 | yes |
| `src/link_nav.c` | c | utility | 10 | no |
| `src/link_preview.c` | c | utility | 7 | yes |
| `src/video_controls.c` | c | utility | 11 | no |
| `tests/test_chrome_layout.c` | c | testing | 20 | yes |
| `tests/test_link_nav.c` | c | testing | 22 | no |
| `tests/test_link_preview.c` | c | testing | 13 | yes |
| `tests/test_video_controls.c` | c | testing | 8 | no |

## Key Symbols

- `take_double` (function, `fuzz/fuzz_chrome_layout.c:15`) `static double take_double(const uint8_t **p, size_t *n)`
- `check_rect` (function, `fuzz/fuzz_chrome_layout.c:25`) `static void check_rect(chl_rect r)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_chrome_layout.c:30`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_link_preview.c:11`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `check_split` (function, `fuzz/fuzz_url.c:31`) `static void check_split(const char *url)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_url.c:59`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `take` (function, `fuzz/fuzz_video_controls.c:8`) `static double take(const uint8_t **p, size_t *n)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_video_controls.c:14`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
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
- `bui_find_view` (struct, `gui/browser_ui_internal.h:151`) - const char *const *titles;       /* tab_count titles (never NULL entries) const int         *tab_loa
- `bui_paint_findbar` (function, `gui/browser_ui_internal.h:164`) `void bui_paint_findbar(cairo_t *cr, const bui_find_view *v);`
- `bui_chrome_font` (function, `gui/browser_ui_internal.h:166`) `void bui_chrome_font(cairo_t *cr, double size);`
- `bui_paint_chrome` (function, `gui/browser_ui_internal.h:168`) `void bui_paint_chrome(cairo_t *cr, const bui_chrome_view *v);` - const char        *text;        /* query size_t             len, cursor; int                focused;
- `bui_url_text_x` (function, `gui/browser_ui_internal.h:171`) `double bui_url_text_x(const bui_chrome_view *v, cairo_t *cr, double *shift);` - X where URL text starts and the horizontal shift keeping the caret visible: * the single geometry th
- `bui_url_index_at` (function, `gui/browser_ui_internal.h:173`) `size_t bui_url_index_at(cairo_t *cr, const bui_chrome_view *v, double x);` - X where URL text starts and the horizontal shift keeping the caret visible: * the single geometry th
- `bui_round_rect` (function, `gui/browser_ui_internal.h:175`) `void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double` - X where URL text starts and the horizontal shift keeping the caret visible: * the single geometry th
- `bui_paint_video_bar` (function, `gui/browser_ui_internal.h:180`) `void bui_paint_video_bar(cairo_t *cr, const vcl_geom *g, int paused, double pos,` - The browser's player bar over a playing video (spec/video_controls.md), drawn in the * geometry g th

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 20
- Cross-boundary resolved imports (EXTRACTED): 13

## Connections

- [EXTRACTED] depends_on community 7 <-> 0 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_url.c imports include/url.h.
- [EXTRACTED] depends_on community 1 <-> 7 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/link_nav.h.
- [EXTRACTED] depends_on community 7 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui_internal.h imports include/freedom_config.h.
- [EXTRACTED] depends_on community 7 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/bui_mask_img.c imports include/css.h.

## Risks

- [layer strict] `tests/test_chrome_layout.c` (testing) -> `include/chrome_layout.h` (presentation)

## Open Questions

- Why do 13 file(s) lack file-level docs (e.g. `fuzz/fuzz_url.c`)? What purpose do they serve?
- What would break if the most connected file in include: bui_chrome changed?
- Should include: bui_chrome be split, given cohesion 0.61?

## Sources

- `fuzz/fuzz_chrome_layout.c`
- `fuzz/fuzz_link_preview.c`
- `fuzz/fuzz_url.c`
- `fuzz/fuzz_video_controls.c`
- `gui/browser_ui_internal.h`
- `gui/bui_chrome.c`
- `gui/bui_mask_img.c`
- `gui/bui_theme.c`
- `include/chrome_layout.h`
- `include/link_nav.h`
- `include/link_preview.h`
- `include/video_controls.h`
- `src/chrome_layout.c`
- `src/link_nav.c`
- `src/link_preview.c`
- `src/video_controls.c`
- `tests/test_chrome_layout.c`
- `tests/test_link_nav.c`
- `tests/test_link_preview.c`
- `tests/test_video_controls.c`
