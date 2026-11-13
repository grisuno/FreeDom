# src: css

*Community 0 | 57 files | cohesion 0.69*

## Definition

This community groups 57 file(s) rooted at `src` with dominant language c (cohesion 0.69). Central symbols: `AUTO_REJECT`, `AUTO_RESET`, `AUTO_RESET_NONE`, `AUTO_VALUE`, `CAR_INLINE_SPEC`, `CAR_LAYER_NAME_MAX`, `CAR_MAX_DEPTH`, `CAR_MAX_LAYERS`. Core file: `tests/test_css.c` (369 symbols). Documented purpose: bui_mask_img -- paints a mask-image: url() layer into a mask surface..

## Files

### `src` (19 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/compositor.c` | c | utility | 5 | no |
| `src/css.c` | c | utility | 268 | no |
| `src/css_atrule.c` | c | utility | 11 | no |
| `src/css_box.c` | c | utility | 52 | no |
| `src/css_chain.c` | c | utility | 26 | no |
| `src/css_color.c` | c | utility | 36 | no |

### `include` (18 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/compositor.h` | h | utility | 9 | no |
| `include/css.h` | h | utility | 147 | no |
| `include/css_atrule.h` | h | utility | 10 | no |
| `include/css_box.h` | h | utility | 27 | no |
| `include/css_color.h` | h | utility | 7 | no |
| `include/css_computed.h` | h | utility | 6 | no |

### `tests` (17 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_compositor.c` | c | testing | 21 | no |
| `tests/test_css.c` | c | testing | 369 | no |
| `tests/test_css_atrule.c` | c | testing | 10 | yes |
| `tests/test_css_box.c` | c | testing | 13 | no |
| `tests/test_css_color.c` | c | testing | 37 | no |

### `gui` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui_internal.h` | h | presentation | 11 | no |
| `gui/bui_mask_img.c` | c | utility | 1 | yes |
| `gui/bui_theme.c` | c | utility | 6 | no |

*... and 37 more files in this community.*


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
- `FREEDOM_COMPOSITOR_H` (macro, `include/compositor.h:2`) `#define FREEDOM_COMPOSITOR_H`
- `cx_layer` (enum, `include/compositor.h:27`) - allocation: given a box's already-resolved style scalars it decides (a) whether the box establishes
- `cx_style` (struct, `include/compositor.h:46`) - A box's resolved style, in the SAME value-spaces as css.h: position uses css_position (CSS_POS_STATI
- `position` (type_alias, `include/compositor.h:46`) `typedef struct cx_style { int position;` - A box's resolved style, in the SAME value-spaces as css.h: position uses css_position (CSS_POS_STATI
- `cx_forms_stacking_context` (function, `include/compositor.h:60`) `int cx_forms_stacking_context(const cx_style *s);` - Does this box establish a stacking context? (The root context is the caller's.) * NULL-safe: returns
- `cx_item` (struct, `include/compositor.h:69`) - One box to order for painting: its layer, z-index (z_auto treated as 0 within the ZERO_Z layer), doc
- `layer` (type_alias, `include/compositor.h:69`) `typedef struct cx_item { cx_layer layer;` - One box to order for painting: its layer, z-index (z_auto treated as 0 within the ZERO_Z layer), doc
- `cx_item_compare` (function, `include/compositor.h:80`) `int cx_item_compare(const cx_item *a, const cx_item *b);` - Total paint order: layer ascending, then z-index ascending (auto == 0), then document order ascendin
- `cx_sort` (function, `include/compositor.h:84`) `void cx_sort(cx_item *items, size_t n);` - Stable in-place sort of `items` into paint order (uses cx_item_compare). Stable: * equal keys keep t
- `FREEDOM_CSS_H` (macro, `include/css.h:2`) `#define FREEDOM_CSS_H`
- `css_status` (enum, `include/css.h:29`)
- `css_align` (enum, `include/css.h:35`)

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 105
- Cross-boundary resolved imports (EXTRACTED): 47

## Connections

- [EXTRACTED] depends_on community 2 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/compositor.h.
- [EXTRACTED] depends_on community 0 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui_internal.h imports include/freedom_config.h.
- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: src/css.c imports include/webfont.h.
- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: src/dom.c imports include/css_select.h.

## Risks

- [layer strict] `tests/test_css.c` (testing) -> `include/flex_layout.h` (presentation)
- [dataflow DEAD_STORE] `src/css.c:6109` `page_view` `had_winner`: `had_winner` assigned at line 6109 but never read afterwards.
- [dataflow DEAD_STORE] `src/css_color.c:156` `parse_hex` `r`: `r` assigned at line 156 but never read afterwards.
- [dataflow DEAD_STORE] `src/css_color.c:157` `parse_hex` `g`: `g` assigned at line 157 but never read afterwards.

## Open Questions

- Why do 41 file(s) lack file-level docs (e.g. `gui/browser_ui_internal.h`)? What purpose do they serve?
- What would break if the most connected file in src: css changed?
- Should src: css be split, given cohesion 0.69?

## Sources

- `gui/browser_ui_internal.h`
- `gui/bui_mask_img.c`
- `gui/bui_theme.c`
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
- `include/css_values.h`
- `include/css_vars.h`
- *... and 37 more*
