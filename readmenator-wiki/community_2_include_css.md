# include: css

*Community 2 | 58 files | cohesion 0.69*

## Definition

This community groups 58 file(s) rooted at `include` with dominant language c (cohesion 0.69). Central symbols: `AUTO_REJECT`, `AUTO_RESET`, `AUTO_RESET_NONE`, `AUTO_VALUE`, `CAR_INLINE_SPEC`, `CAR_LAYER_NAME_MAX`, `CAR_MAX_DEPTH`, `CAR_MAX_LAYERS`. Core file: `tests/test_css.c` (374 symbols). Documented purpose: libFuzzer harness for css_counter (spec/css_counter.md): hostile `content` and counter.

## Files

### `include` (19 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/compositor.h` | h | utility | 11 | no |
| `include/css.h` | h | utility | 148 | no |
| `include/css_atrule.h` | h | utility | 10 | no |
| `include/css_box.h` | h | utility | 28 | no |
| `include/css_chain.h` | h | utility | 13 | no |
| `include/css_color.h` | h | utility | 7 | no |

### `src` (19 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/compositor.c` | c | utility | 7 | no |
| `src/css.c` | c | utility | 276 | no |
| `src/css_atrule.c` | c | utility | 11 | no |
| `src/css_box.c` | c | utility | 53 | no |
| `src/css_chain.c` | c | utility | 27 | no |
| `src/css_color.c` | c | utility | 36 | no |

### `tests` (17 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_compositor.c` | c | testing | 23 | no |
| `tests/test_css.c` | c | testing | 374 | no |
| `tests/test_css_atrule.c` | c | testing | 10 | yes |
| `tests/test_css_box.c` | c | testing | 13 | no |
| `tests/test_css_color.c` | c | testing | 37 | no |

### `fuzz` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_css.c` | c | utility | 2 | no |
| `fuzz/fuzz_css_counter.c` | c | utility | 1 | yes |
| `fuzz/fuzz_text_case.c` | c | utility | 1 | yes |

*... and 38 more files in this community.*


## Key Symbols

- `fuzz_root_match` (function, `fuzz/fuzz_css.c:77`) `static int fuzz_root_match(void *ctx, const css_sel *sel)` - Root matcher for the attribute-scoped custom-property path: a fixed <html class="theme-dark" data-co
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_css.c:91`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_css_counter.c:11`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_text_case.c:13`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_COMPOSITOR_H` (macro, `include/compositor.h:2`) `#define FREEDOM_COMPOSITOR_H`
- `cx_layer` (enum, `include/compositor.h:27`) - allocation: given a box's already-resolved style scalars it decides (a) whether the box establishes
- `cx_style` (struct, `include/compositor.h:46`) - A box's resolved style, in the SAME value-spaces as css.h: position uses css_position (CSS_POS_STATI
- `position` (type_alias, `include/compositor.h:46`) `typedef struct cx_style { int position;` - A box's resolved style, in the SAME value-spaces as css.h: position uses css_position (CSS_POS_STATI
- `cx_forms_stacking_context` (function, `include/compositor.h:60`) `int cx_forms_stacking_context(const cx_style *s);` - Does this box establish a stacking context? (The root context is the caller's.) * NULL-safe: returns
- `cx_item` (struct, `include/compositor.h:69`) - One box to order for painting: its layer, z-index (z_auto treated as 0 within the ZERO_Z layer), doc
- `layer` (type_alias, `include/compositor.h:69`) `typedef struct cx_item { cx_layer layer;` - One box to order for painting: its layer, z-index (z_auto treated as 0 within the ZERO_Z layer), doc
- `cx_item_compare` (function, `include/compositor.h:80`) `int cx_item_compare(const cx_item *a, const cx_item *b);` - Total paint order: layer ascending, then z-index ascending (auto == 0), then document order ascendin
- `cx_sort` (function, `include/compositor.h:84`) `void cx_sort(cx_item *items, size_t n);` - Stable in-place sort of `items` into paint order (uses cx_item_compare). Stable: * equal keys keep t
- `cx_ink_reach` (function, `include/compositor.h:91`) `double cx_ink_reach(const int (*layers)[6], int n, int outline_w, int outline_of` - How far (px, >= 0) a box's paint may reach beyond its border box (spec/compositor.md, tanda 95): eac
- `cx_span_visible` (function, `include/compositor.h:95`) `int cx_span_visible(double top, double h, double reach, double view_top, double` - 1 when [top - reach, top + h + reach] touches [view_top, view_top + view_h] (edges * included), else
- `FREEDOM_CSS_H` (macro, `include/css.h:2`) `#define FREEDOM_CSS_H`
- `css_status` (enum, `include/css.h:30`)
- `css_align` (enum, `include/css.h:36`)
- `css_display` (enum, `include/css.h:44`)
- `CSS_DISP_INLINE_OUTER` (macro, `include/css.h:74`) `#define CSS_DISP_INLINE_OUTER`
- `CSS_DISP_INNER_MASK` (macro, `include/css.h:75`) `#define CSS_DISP_INNER_MASK`
- `css_justify` (enum, `include/css.h:77`)
- `CSS_GAP_MAX` (macro, `include/css.h:88`) `#define CSS_GAP_MAX`
- `CSS_GRID_COLS_MAX` (macro, `include/css.h:89`) `#define CSS_GRID_COLS_MAX`
- `CSS_GRID_TRACKS_MAX` (macro, `include/css.h:90`) `#define CSS_GRID_TRACKS_MAX`
- `verbatim` (function, `include/css.h:92`) `* the quoted row strings verbatim (flex_layout parses them);`
- `CSS_GRID_AREAS_MAX` (macro, `include/css.h:96`) `#define CSS_GRID_AREAS_MAX`
- `CSS_GRAD_STOPS_MAX` (macro, `include/css.h:97`) `#define CSS_GRAD_STOPS_MAX`
- `CSS_LINE_MIN` (macro, `include/css.h:98`) `#define CSS_LINE_MIN`
- `CSS_LINE_MAX` (macro, `include/css.h:99`) `#define CSS_LINE_MAX`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 111
- Cross-boundary resolved imports (EXTRACTED): 51

## Connections

- [EXTRACTED] depends_on community 2 <-> 4 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_css.c imports include/flex_layout.h.
- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/compositor.h.
- [EXTRACTED] depends_on community 7 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/bui_mask_img.c imports include/css.h.

## Risks

- [layer strict] `tests/test_css.c` (testing) -> `include/flex_layout.h` (presentation)

## Open Questions

- Why do 41 file(s) lack file-level docs (e.g. `fuzz/fuzz_css.c`)? What purpose do they serve?
- What would break if the most connected file in include: css changed?
- Should include: css be split, given cohesion 0.69?

## Sources

- `fuzz/fuzz_css.c`
- `fuzz/fuzz_css_counter.c`
- `fuzz/fuzz_text_case.c`
- `include/compositor.h`
- `include/css.h`
- `include/css_atrule.h`
- `include/css_box.h`
- `include/css_chain.h`
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
- *... and 38 more*
