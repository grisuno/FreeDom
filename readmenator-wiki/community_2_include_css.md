# include: css

*Community 2 | 44 files | cohesion 0.77*

## Definition

This community groups 44 file(s) rooted at `include` with dominant language c (cohesion 0.77). Central symbols: `AUTO_REJECT`, `AUTO_RESET`, `AUTO_RESET_NONE`, `AUTO_VALUE`, `CAR_INLINE_SPEC`, `CAR_LAYER_NAME_MAX`, `CAR_MAX_DEPTH`, `CAR_MAX_LAYERS`. Core file: `tests/test_css.c` (306 symbols). Documented purpose: Bound for the ::before/::after content string pool (and the grid-template.

## Files

### `include` (15 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/compositor.h` | h | utility | 9 | no |
| `include/css.h` | h | utility | 131 | no |
| `include/css_atrule.h` | h | utility | 10 | no |
| `include/css_box.h` | h | utility | 25 | no |
| `include/css_chain.h` | h | utility | 8 | no |
| `include/css_color.h` | h | utility | 7 | no |

### `src` (14 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/compositor.c` | c | utility | 5 | no |
| `src/css.c` | c | utility | 220 | no |
| `src/css_atrule.c` | c | utility | 11 | no |
| `src/css_box.c` | c | utility | 47 | no |
| `src/css_chain.c` | c | utility | 17 | no |
| `src/css_color.c` | c | utility | 27 | no |

### `tests` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_compositor.c` | c | testing | 21 | no |
| `tests/test_css.c` | c | testing | 306 | no |
| `tests/test_css_atrule.c` | c | testing | 10 | yes |
| `tests/test_css_box.c` | c | testing | 9 | no |
| `tests/test_css_color.c` | c | testing | 36 | no |
| `tests/test_css_drops.c` | c | testing | 25 | yes |

### `fuzz` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_css.c` | c | utility | 2 | no |
| `fuzz/fuzz_text_shape.c` | c | utility | 2 | no |

*... and 24 more files in this community.*


## Key Symbols

- `fuzz_root_match` (function, `fuzz/fuzz_css.c:66`) `static int fuzz_root_match(void *ctx, const css_sel *sel)` - Root matcher for the attribute-scoped custom-property path: a fixed <html class="theme-dark" data-co
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_css.c:80`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FZ_CAP` (macro, `fuzz/fuzz_text_shape.c:23`) `#define FZ_CAP`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_text_shape.c:25`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
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
- `css_justify` (enum, `include/css.h:64`)
- `CSS_GAP_MAX` (macro, `include/css.h:75`) `#define CSS_GAP_MAX`
- `CSS_GRID_COLS_MAX` (macro, `include/css.h:76`) `#define CSS_GRID_COLS_MAX`
- `CSS_GRID_TRACKS_MAX` (macro, `include/css.h:77`) `#define CSS_GRID_TRACKS_MAX`
- `verbatim` (function, `include/css.h:79`) `* the quoted row strings verbatim (flex_layout parses them);`
- `CSS_GRID_AREAS_MAX` (macro, `include/css.h:83`) `#define CSS_GRID_AREAS_MAX`
- `CSS_GRAD_STOPS_MAX` (macro, `include/css.h:84`) `#define CSS_GRAD_STOPS_MAX`
- `CSS_LINE_MIN` (macro, `include/css.h:85`) `#define CSS_LINE_MIN`
- `CSS_LINE_MAX` (macro, `include/css.h:86`) `#define CSS_LINE_MAX`
- `CSS_URL_MAX` (macro, `include/css.h:87`) `#define CSS_URL_MAX`
- `CSS_DECO_UNDERLINE` (macro, `include/css.h:92`) `#define CSS_DECO_UNDERLINE`
- `CSS_DECO_LINE_THROUGH` (macro, `include/css.h:93`) `#define CSS_DECO_LINE_THROUGH`
- `CSS_DECO_OVERLINE` (macro, `include/css.h:94`) `#define CSS_DECO_OVERLINE`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 90
- Cross-boundary resolved imports (EXTRACTED): 27

## Connections

- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/compositor.h.
- [EXTRACTED] depends_on community 5 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/bui_theme.c imports include/css_color.h.
- [EXTRACTED] depends_on community 3 <-> 2 (strength 0.9): Extracted import edge crosses communities: include/box_style.h imports include/css.h.
- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: src/dom.c imports include/css_chain.h.

## Risks

- [dataflow DEAD_STORE] `src/css_color.c:155` `parse_hex` `r`: `r` assigned at line 155 but never read afterwards.
- [dataflow DEAD_STORE] `src/css_color.c:156` `parse_hex` `g`: `g` assigned at line 156 but never read afterwards.

## Open Questions

- Why do 38 file(s) lack file-level docs (e.g. `fuzz/fuzz_css.c`)? What purpose do they serve?
- What would break if the most connected file in include: css changed?
- Should include: css be split, given cohesion 0.77?

## Sources

- `fuzz/fuzz_css.c`
- `fuzz/fuzz_text_shape.c`
- `include/compositor.h`
- `include/css.h`
- `include/css_atrule.h`
- `include/css_box.h`
- `include/css_chain.h`
- `include/css_color.h`
- `include/css_decl.h`
- `include/css_gradient.h`
- `include/css_length.h`
- `include/css_mq.h`
- `include/css_select.h`
- `include/css_text.h`
- `include/css_values.h`
- `include/css_vars.h`
- `include/text_shape.h`
- `src/compositor.c`
- `src/css.c`
- `src/css_atrule.c`
- *... and 24 more*
