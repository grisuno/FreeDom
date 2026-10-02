# src

*Community 0 | 63 files | cohesion 0.74*

## Definition

This community groups 63 file(s) rooted at `src` with dominant language c (cohesion 0.74). Central symbols: `AUTO_REJECT`, `AUTO_RESET`, `AUTO_RESET_NONE`, `AUTO_VALUE`, `BROWSER_STATUS_DURATION_MS`, `BROWSER_STATUS_MAX`, `BROWSER_URL_MAX`, `BT_LEN_AUTO`. Core file: `tests/test_css.c` (306 symbols). Documented purpose: svg_paint — Cairo back end for the shapes svg_render extracted..

## Files

### `src` (23 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/box_tree.c` | c | utility | 22 | no |
| `src/browser.c` | c | utility | 41 | no |
| `src/compositor.c` | c | utility | 5 | no |
| `src/css.c` | c | utility | 220 | no |
| `src/css_atrule.c` | c | business_logic | 11 | no |
| `src/css_box.c` | c | utility | 47 | no |

### `include` (20 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/browser.h` | h | utility | 19 | no |
| `include/compositor.h` | h | utility | 9 | no |
| `include/css.h` | h | utility | 131 | no |
| `include/css_atrule.h` | h | business_logic | 10 | no |
| `include/css_box.h` | h | utility | 25 | no |

### `tests` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_browser.c` | c | testing | 17 | no |
| `tests/test_compositor.c` | c | testing | 21 | no |
| `tests/test_css.c` | c | testing | 306 | no |
| `tests/test_css_atrule.c` | c | testing | 10 | yes |
| `tests/test_css_box.c` | c | testing | 9 | no |

### `fuzz` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_css.c` | c | utility | 2 | no |
| `fuzz/fuzz_svg_render.c` | c | presentation | 1 | no |
| `fuzz/fuzz_text_shape.c` | c | utility | 2 | no |

### `gui` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/svg_paint.c` | c | presentation | 5 | yes |

*... and 43 more files in this community.*


## Key Symbols

- `fuzz_root_match` (function, `fuzz/fuzz_css.c:66`) `static int fuzz_root_match(void *ctx, const css_sel *sel)` - Root matcher for the attribute-scoped custom-property path: a fixed <html class="theme-dark" data-co
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_css.c:80`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_svg_render.c:24`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FZ_CAP` (macro, `fuzz/fuzz_text_shape.c:23`) `#define FZ_CAP`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_text_shape.c:25`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `svp_alpha` (function, `gui/svg_paint.c:31`) `static double svp_alpha(int opacity, int paint_opacity)` - Resolves a shape's packed paint into an RGB triple. Returns 0 when the shape * asked for no paint at
- `svp_rect_path` (function, `gui/svg_paint.c:38`) `static void svp_rect_path(cairo_t *cr, const sv_shape *sh)` - r = (double)((c >> 16) & 0xFF) / 255.0; g = (double)((c >> 8) & 0xFF) / 255.0; b = (double)(c & 0xFF
- `svp_shape_path` (function, `gui/svg_paint.c:73`) `static void svp_shape_path(cairo_t *cr, const sv_image *img, const sv_shape *sh)`
- `svp_draw_text` (function, `gui/svg_paint.c:126`) `static void svp_draw_text(cairo_t *cr, const sv_shape *sh, int current_rgb)`
- `svp_draw` (function, `gui/svg_paint.c:139`) `void svp_draw(cairo_t *cr, const sv_image *img,               double x, double y`
- `FREEDOM_BROWSER_H` (macro, `include/browser.h:2`) `#define FREEDOM_BROWSER_H`
- `BROWSER_URL_MAX` (macro, `include/browser.h:21`) `#define BROWSER_URL_MAX`
- `BROWSER_STATUS_MAX` (macro, `include/browser.h:24`) `#define BROWSER_STATUS_MAX`
- `BROWSER_STATUS_DURATION_MS` (macro, `include/browser.h:25`) `#define BROWSER_STATUS_DURATION_MS`
- `browser_state` (struct, `include/browser.h:27`)
- `browser_status` (enum, `include/browser.h:52`)
- `state` (function, `include/browser.h:62`) `* state (frees old history and page buffers). */ browser_status browser_init(bro`
- `browser_free` (function, `include/browser.h:66`) `void browser_free(browser_state *bs);` - Zero-initialise or reset a state. Safe to call on an already-initialised * state (frees old history
- `browser_set_page` (function, `include/browser.h:71`) `* browser_set_page() with the result. */ browser_status browser_navigate(browser`
- `browser_entry_doc` (function, `include/browser.h:87`) `int browser_entry_doc(const browser_state *bs, size_t pos);` - Same-document entries (history.pushState, spec/browser.md 3b). push adds an entry of the CURRENT doc
- `browser_doc_index` (function, `include/browser.h:91`) `int browser_doc_index(const browser_state *bs);` - Index of the current entry within its document's contiguous run of entries (0 for * the entry the do
- `browser_can_back` (function, `include/browser.h:94`) `int browser_can_back(const browser_state *bs);` - Index of the current entry within its document's contiguous run of entries (0 for * the entry the do
- `browser_can_forward` (function, `include/browser.h:95`) `int browser_can_forward(const browser_state *bs);`
- `browser_current_url` (function, `include/browser.h:96`) `const char *browser_current_url(const browser_state *bs);`
- `browser_is_exception` (function, `include/browser.h:99`) `int browser_is_exception(const browser_state *bs, const char *host);` - Index of the current entry within its document's contiguous run of entries (0 for * the entry the do
- `browser_url_bar_selection` (function, `include/browser.h:131`) `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *le` - If a selection exists, writes its start offset and length and returns 1; else 0. * Lets the GUI copy
- `browser_url_bar_delete_selection` (function, `include/browser.h:135`) `int browser_url_bar_delete_selection(browser_state *bs);` - Removes the selected range (if any), placing the cursor at its start; returns 1 if * something was r
- `copied` (function, `include/browser.h:143`) `* copied (truncated to fit) and shown until now_ms reaches the expiry * (now_ms`
- `browser_status_text` (function, `include/browser.h:150`) `const char *browser_status_text(const browser_state *bs, uint64_t now_ms);` - Transient status line (a toast, e.g. "blocked: insecure http link"). msg is copied (truncated to fit
- `FREEDOM_COMPOSITOR_H` (macro, `include/compositor.h:2`) `#define FREEDOM_COMPOSITOR_H`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 119
- Cross-boundary resolved imports (EXTRACTED): 42

## Connections

- [EXTRACTED] depends_on community 3 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/browser.h.
- [EXTRACTED] depends_on community 7 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/bui_theme.c imports include/css_color.h.
- [EXTRACTED] depends_on community 11 <-> 0 (strength 0.9): Extracted import edge crosses communities: src/disk_store.c imports include/util.h.
- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: src/dom.c imports include/dom.h.
- [EXTRACTED] depends_on community 0 <-> 1 (strength 0.9): Extracted import edge crosses communities: src/render_doc.c imports include/data_url.h.
- [EXTRACTED] depends_on community 0 <-> 10 (strength 0.9): Extracted import edge crosses communities: src/render_doc.c imports include/url.h.

## Risks

- [layer strict] `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `tests/test_renderer.c` (testing) -> `include/renderer.h` (presentation)
- [layer strict] `tests/test_svg_render.c` (testing) -> `include/svg_render.h` (presentation)
- [dataflow UNINIT_USE] `src/box_tree.c:231` `layout_grid` `col_x`: `col_x` may be read before initialization (declared line 228).
- [dataflow UNINIT_USE] `src/box_tree.c:231` `layout_grid` `col_w`: `col_w` may be read before initialization (declared line 229).
- [dataflow DEAD_STORE] `src/box_tree.c:469` `bt_containing_block` `ancestor`: `ancestor` assigned at line 469 but never read afterwards.
- [dataflow DEAD_STORE] `src/box_tree.c:623` `bt_resolve_positioning_ex` `z_auto`: `z_auto` assigned at line 623 but never read afterwards.
- [dataflow DEAD_STORE] `src/css_color.c:155` `parse_hex` `r`: `r` assigned at line 155 but never read afterwards.
- [dataflow DEAD_STORE] `src/css_color.c:156` `parse_hex` `g`: `g` assigned at line 156 but never read afterwards.
- [dataflow UNCHECKED_ALLOC] `src/hostblock.c:145` `hb_new` `s`: Result of allocator stored in `s` is never checked against NULL.
- [dataflow DEAD_STORE] `src/page_view.c:1328` `css_hbox_resolve` `l`: `l` assigned at line 1328 but never read afterwards.
- [dataflow DEAD_STORE] `src/page_view.c:1329` `css_hbox_resolve` `r`: `r` assigned at line 1329 but never read afterwards.
- [dataflow UNCHECKED_ALLOC] `src/page_view.c:1989` `pv_ptrmap_put` `g`: Result of allocator stored in `g` is never checked against NULL.
- [dataflow DEAD_STORE] `src/page_view.c:2704` `resolve_context` `color_inherits`: `color_inherits` assigned at line 2704 but never read afterwards.
- [dataflow DEAD_STORE] `src/page_view.c:2705` `resolve_context` `got_align`: `got_align` assigned at line 2705 but never read afterwards.

## Open Questions

- Why do 53 file(s) lack file-level docs (e.g. `fuzz/fuzz_css.c`)? What purpose do they serve?
- What would break if the most connected file in src changed?
- Should src be split, given cohesion 0.74?

## Sources

- `fuzz/fuzz_css.c`
- `fuzz/fuzz_svg_render.c`
- `fuzz/fuzz_text_shape.c`
- `gui/svg_paint.c`
- `include/browser.h`
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
- `include/renderer.h`
- *... and 43 more*
