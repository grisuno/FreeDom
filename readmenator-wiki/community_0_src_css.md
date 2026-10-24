# src: css

*Community 0 | 53 files | cohesion 0.72*

## Definition

This community groups 53 file(s) rooted at `src` with dominant language c (cohesion 0.72). Central symbols: `AUTO_REJECT`, `AUTO_RESET`, `AUTO_RESET_NONE`, `AUTO_VALUE`, `BT_LEN_AUTO`, `BT_WRAP_EPS`, `CAR_INLINE_SPEC`, `CAR_LAYER_NAME_MAX`. Core file: `tests/test_css.c` (354 symbols). Documented purpose: The sheet's two string pools -- background url()s, and the ::before/::after.

## Files

### `src` (19 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/box_tree.c` | c | utility | 25 | no |
| `src/compositor.c` | c | utility | 5 | no |
| `src/css.c` | c | utility | 247 | no |
| `src/css_atrule.c` | c | utility | 11 | no |
| `src/css_box.c` | c | utility | 52 | no |
| `src/css_chain.c` | c | utility | 20 | no |
| `src/css_color.c` | c | utility | 27 | no |

### `include` (18 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/compositor.h` | h | utility | 9 | no |
| `include/css.h` | h | utility | 140 | no |
| `include/css_atrule.h` | h | utility | 10 | no |
| `include/css_box.h` | h | utility | 27 | no |
| `include/css_chain.h` | h | utility | 8 | no |
| `include/css_color.h` | h | utility | 7 | no |
| `include/css_computed.h` | h | utility | 6 | no |

### `tests` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_compositor.c` | c | testing | 21 | no |
| `tests/test_css.c` | c | testing | 354 | no |
| `tests/test_css_atrule.c` | c | testing | 10 | yes |
| `tests/test_css_box.c` | c | testing | 13 | no |
| `tests/test_css_color.c` | c | testing | 36 | no |
| `tests/test_css_computed.c` | c | testing | 9 | no |

*... and 33 more files in this community.*


## Key Symbols

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
- `css_status` (enum, `include/css.h:28`)
- `css_align` (enum, `include/css.h:34`)
- `css_display` (enum, `include/css.h:42`)
- `css_justify` (enum, `include/css.h:69`)
- `CSS_GAP_MAX` (macro, `include/css.h:80`) `#define CSS_GAP_MAX`
- `CSS_GRID_COLS_MAX` (macro, `include/css.h:81`) `#define CSS_GRID_COLS_MAX`
- `CSS_GRID_TRACKS_MAX` (macro, `include/css.h:82`) `#define CSS_GRID_TRACKS_MAX`
- `verbatim` (function, `include/css.h:84`) `* the quoted row strings verbatim (flex_layout parses them);`
- `CSS_GRID_AREAS_MAX` (macro, `include/css.h:88`) `#define CSS_GRID_AREAS_MAX`
- `CSS_GRAD_STOPS_MAX` (macro, `include/css.h:89`) `#define CSS_GRAD_STOPS_MAX`
- `CSS_LINE_MIN` (macro, `include/css.h:90`) `#define CSS_LINE_MIN`
- `CSS_LINE_MAX` (macro, `include/css.h:91`) `#define CSS_LINE_MAX`
- `CSS_LINE_ABS_BASE` (macro, `include/css.h:96`) `#define CSS_LINE_ABS_BASE`
- `CSS_LINE_ABS_MAX_PX` (macro, `include/css.h:97`) `#define CSS_LINE_ABS_MAX_PX`
- `CSS_SVG_PAINT_NONE` (macro, `include/css.h:98`) `#define CSS_SVG_PAINT_NONE`
- `CSS_FONT_LIST_MAX` (macro, `include/css.h:99`) `#define CSS_FONT_LIST_MAX`
- `CSS_URL_MAX` (macro, `include/css.h:100`) `#define CSS_URL_MAX`
- `CSS_DECO_UNDERLINE` (macro, `include/css.h:105`) `#define CSS_DECO_UNDERLINE`
- `CSS_DECO_LINE_THROUGH` (macro, `include/css.h:106`) `#define CSS_DECO_LINE_THROUGH`
- `CSS_DECO_OVERLINE` (macro, `include/css.h:107`) `#define CSS_DECO_OVERLINE`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 103
- Cross-boundary resolved imports (EXTRACTED): 42

## Connections

- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/compositor.h.
- [EXTRACTED] depends_on community 7 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/bui_theme.c imports include/css.h.
- [EXTRACTED] depends_on community 4 <-> 0 (strength 0.9): Extracted import edge crosses communities: include/box_style.h imports include/css.h.
- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: src/css.c imports include/webfont.h.
- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: src/dom.c imports include/dom.h.
- [EXTRACTED] depends_on community 0 <-> 5 (strength 0.9): Extracted import edge crosses communities: src/dom.c imports include/util.h.

## Risks

- [layer strict] `tests/test_css.c` (testing) -> `include/flex_layout.h` (presentation)
- [dataflow DEAD_STORE] `src/box_tree.c:286` `layout_grid` `rgap`: `rgap` assigned at line 286 but never read afterwards.
- [dataflow UNINIT_USE] `src/box_tree.c:291` `layout_grid` `col_x`: `col_x` may be read before initialization (declared line 288).
- [dataflow UNINIT_USE] `src/box_tree.c:291` `layout_grid` `col_w`: `col_w` may be read before initialization (declared line 289).
- [dataflow DEAD_STORE] `src/box_tree.c:331` `layout_grid` `tracked`: `tracked` assigned at line 331 but never read afterwards.
- [dataflow DEAD_STORE] `src/box_tree.c:334` `layout_grid` `jx`: `jx` assigned at line 334 but never read afterwards.
- [dataflow DEAD_STORE] `src/box_tree.c:562` `bt_containing_block` `ancestor`: `ancestor` assigned at line 562 but never read afterwards.
- [dataflow DEAD_STORE] `src/box_tree.c:716` `bt_resolve_positioning_ex` `z_auto`: `z_auto` assigned at line 716 but never read afterwards.
- [dataflow DEAD_STORE] `src/css.c:5481` `page_view` `had_winner`: `had_winner` assigned at line 5481 but never read afterwards.
- [dataflow DEAD_STORE] `src/css_color.c:155` `parse_hex` `r`: `r` assigned at line 155 but never read afterwards.
- [dataflow DEAD_STORE] `src/css_color.c:156` `parse_hex` `g`: `g` assigned at line 156 but never read afterwards.

## Open Questions

- Why do 41 file(s) lack file-level docs (e.g. `include/compositor.h`)? What purpose do they serve?
- What would break if the most connected file in src: css changed?
- Should src: css be split, given cohesion 0.72?

## Sources

- `include/compositor.h`
- `include/css.h`
- `include/css_atrule.h`
- `include/css_box.h`
- `include/css_chain.h`
- `include/css_color.h`
- `include/css_computed.h`
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
- `include/text_case.h`
- `src/box_tree.c`
- `src/compositor.c`
- *... and 33 more*
