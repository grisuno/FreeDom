# include: page_view

*Community 2 | 43 files | cohesion 0.56*

## Definition

This community groups 43 file(s) rooted at `include` with dominant language c (cohesion 0.56). Central symbols: `BLOCK`, `BT_ALIGN_CENTER`, `BT_ALIGN_END`, `BT_ALIGN_START`, `BT_ALIGN_STRETCH`, `BT_LEN_AUTO`, `BT_MAUTO_LEFT`, `BT_MAUTO_RIGHT`. Core file: `tests/test_css.c` (369 symbols). Documented purpose: bui_mask_img -- paints a mask-image: url() layer into a mask surface..

## Files

### `include` (15 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/box_style.h` | h | utility | 31 | no |
| `include/box_tree.h` | h | utility | 34 | no |
| `include/compositor.h` | h | utility | 9 | no |
| `include/css.h` | h | utility | 144 | no |
| `include/css_chain.h` | h | utility | 12 | no |
| `include/css_computed.h` | h | utility | 6 | no |

### `tests` (14 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_box_style.c` | c | testing | 49 | no |
| `tests/test_box_tree.c` | c | testing | 69 | no |
| `tests/test_compositor.c` | c | testing | 21 | no |
| `tests/test_css.c` | c | testing | 369 | no |
| `tests/test_css_computed.c` | c | testing | 9 | no |
| `tests/test_css_counter.c` | c | testing | 12 | yes |

### `src` (11 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/box_style.c` | c | utility | 48 | no |
| `src/box_tree.c` | c | utility | 25 | no |
| `src/compositor.c` | c | utility | 5 | no |
| `src/css_computed.c` | c | utility | 45 | no |
| `src/css_counter.c` | c | utility | 34 | no |

### `gui` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui_internal.h` | h | presentation | 11 | no |
| `gui/bui_mask_img.c` | c | utility | 1 | yes |
| `gui/bui_theme.c` | c | utility | 6 | no |

*... and 23 more files in this community.*


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
- `bui_paint_mask_image` (function, `gui/bui_mask_img.c:17`) `int bui_paint_mask_image(cairo_t *c, cairo_surface_t *img, int nat_w, int nat_h,`
- `ui_theme_default` (function, `gui/bui_theme.c:15`) `ui_theme ui_theme_default(void)` - bui_theme — presentation palettes for the Wayland/Cairo GUI.  Carved out of browser_ui.c: the light/
- `ui_theme_dark` (function, `gui/bui_theme.c:78`) `ui_theme ui_theme_dark(void)` - Dark reading palette. Shares all the metrics (font sizes, spacing) with the * default theme; only th
- `ui_theme_sepia` (function, `gui/bui_theme.c:123`) `ui_theme ui_theme_sepia(void)` - Sepia reading palette: warm paper background and dark-brown ink, easier on the eyes for long-form te
- `ui_theme_for` (function, `gui/bui_theme.c:165`) `ui_theme ui_theme_for(int mode)` - t.menu_bg        = (ui_rgb){ 0.95, 0.90, 0.80 }; t.menu_border    = (ui_rgb){ 0.55, 0.46, 0.32 }; t.
- `rgb_from_packed` (function, `gui/bui_theme.c:174`) `ui_rgb rgb_from_packed(int packed)` - t.scrollbar_thumb_hot = (ui_rgb){ 0.44, 0.35, 0.22 }; return t; } /* The single place that maps the
- `set_rgb` (function, `gui/bui_theme.c:179`) `void set_rgb(cairo_t *cr, ui_rgb c)`
- `FREEDOM_BOX_STYLE_H` (macro, `include/box_style.h:2`) `#define FREEDOM_BOX_STYLE_H`
- `BX_TAG_NAME_MAX` (macro, `include/box_style.h:33`) `#define BX_TAG_NAME_MAX`
- `bx_display` (enum, `include/box_style.h:35`)
- `bx_edges` (struct, `include/box_style.h:46`) - anything longer fails closed instead of truncating into a wrong match. #define BX_TAG_NAME_MAX 32u t
- `left` (type_alias, `include/box_style.h:46`) `typedef struct bx_edges { double top, right, bottom, left;` - anything longer fails closed instead of truncating into a wrong match. #define BX_TAG_NAME_MAX 32u t
- `display` (type_alias, `include/box_style.h:49`) `typedef struct bx_box { bx_display display;`
- `bx_box` (struct, `include/box_style.h:50`)
- `bx_status` (enum, `include/box_style.h:56`)
- `bx_hplace` (struct, `include/box_style.h:63`) - typedef struct bx_box { bx_display display; bx_edges   margin; bx_edges   padding; } bx_box; typedef
- `x_off` (type_alias, `include/box_style.h:63`) `typedef struct bx_hplace { double x_off;` - typedef struct bx_box { bx_display display; bx_edges   margin; bx_edges   padding; } bx_box; typedef
- `bx_ua_tag` (enum, `include/box_style.h:84`) - Compact, stable identity of a block's SOURCE element, just wide enough to recover its user-agent box
- `box` (function, `include/box_style.h:115`) `* in_list nonzero when the block sits inside a list item: it then takes * the <l`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 84
- Cross-boundary resolved imports (EXTRACTED): 66

## Connections

- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/box_style.h.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/bui_theme.c imports include/css_color.h.
- [EXTRACTED] depends_on community 9 <-> 2 (strength 0.9): Extracted import edge crosses communities: include/frame_host.h imports include/page_view.h.
- [EXTRACTED] depends_on community 2 <-> 0 (strength 0.9): Extracted import edge crosses communities: include/page_view.h imports include/dom.h.
- [EXTRACTED] depends_on community 4 <-> 2 (strength 0.9): Extracted import edge crosses communities: include/webcaps.h imports include/render_policy.h.

## Risks

- [layer strict] `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `tests/test_box_tree.c` (testing) -> `include/page_view.h` (presentation)
- [layer strict] `tests/test_css.c` (testing) -> `include/flex_layout.h` (presentation)
- [layer strict] `tests/test_dom_debug.c` (testing) -> `include/flex_layout.h` (presentation)
- [layer strict] `tests/test_dom_debug.c` (testing) -> `include/page_view.h` (presentation)
- [layer strict] `tests/test_dom_debug.c` (testing) -> `include/render_doc.h` (presentation)
- [layer strict] `tests/test_dom_debug.c` (testing) -> `include/render_policy.h` (presentation)
- [layer strict] `tests/test_flex_layout.c` (testing) -> `include/flex_layout.h` (presentation)
- [layer strict] `tests/test_page_view.c` (testing) -> `include/flex_layout.h` (presentation)
- [layer strict] `tests/test_page_view.c` (testing) -> `include/page_view.h` (presentation)
- [layer strict] `tests/test_render_doc.c` (testing) -> `include/flex_layout.h` (presentation)
- [layer strict] `tests/test_render_doc.c` (testing) -> `include/page_view.h` (presentation)
- [layer strict] `tests/test_render_doc.c` (testing) -> `include/render_doc.h` (presentation)
- [layer strict] `tests/test_render_doc.c` (testing) -> `include/render_policy.h` (presentation)
- [layer strict] `tests/test_render_policy.c` (testing) -> `include/render_policy.h` (presentation)

## Open Questions

- Why do 36 file(s) lack file-level docs (e.g. `gui/browser_ui_internal.h`)? What purpose do they serve?
- What would break if the most connected file in include: page_view changed?
- Should include: page_view be split, given cohesion 0.56?

## Sources

- `gui/browser_ui_internal.h`
- `gui/bui_mask_img.c`
- `gui/bui_theme.c`
- `include/box_style.h`
- `include/box_tree.h`
- `include/compositor.h`
- `include/css.h`
- `include/css_chain.h`
- `include/css_computed.h`
- `include/css_counter.h`
- `include/dom_debug.h`
- `include/flex_layout.h`
- `include/freedom_config.h`
- `include/page_view.h`
- `include/render_doc.h`
- `include/render_policy.h`
- `include/sheet_cache.h`
- `include/text_case.h`
- `src/box_style.c`
- `src/box_tree.c`
- *... and 23 more*
