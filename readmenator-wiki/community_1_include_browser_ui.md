# include: browser_ui

*Community 1 | 52 files | cohesion 0.55*

## Definition

This community groups 52 file(s) rooted at `include` with dominant language c (cohesion 0.55). Central symbols: `ABSENT`, `ALIVE`, `BALANCE_MAX_LINES`, `BB_MAX_PIXELS`, `BROWSER_STATUS_DURATION_MS`, `BROWSER_STATUS_MAX`, `BROWSER_URL_MAX`, `BUI_CONIC_SLICES`. Core file: `gui/browser_ui.c` (593 symbols). Documented purpose: block_flow (bf_) -- vertical margin collapsing for block-level boxes..

## Files

### `include` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/block_flow.h` | h | utility | 4 | yes |
| `include/box_blur.h` | h | utility | 4 | yes |
| `include/browser.h` | h | utility | 19 | no |
| `include/download.h` | h | utility | 9 | no |
| `include/form.h` | h | utility | 12 | no |
| `include/frame_clock.h` | h | utility | 7 | no |

### `src` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/block_flow.c` | c | utility | 4 | yes |
| `src/box_blur.c` | c | utility | 4 | no |
| `src/browser.c` | c | utility | 41 | no |
| `src/download.c` | c | utility | 12 | no |
| `src/form.c` | c | utility | 8 | no |

### `tests` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_block_flow.c` | c | testing | 8 | no |
| `tests/test_box_blur.c` | c | testing | 7 | no |
| `tests/test_browser.c` | c | testing | 17 | no |
| `tests/test_download.c` | c | testing | 21 | no |
| `tests/test_form.c` | c | testing | 20 | no |

### `fuzz` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_download.c` | c | utility | 1 | no |
| `fuzz/fuzz_pdf_export.c` | c | utility | 1 | no |
| `fuzz/fuzz_tls_impersonate.c` | c | utility | 0 | no |

### `gui` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui.c` | c | presentation | 593 | no |

*... and 32 more files in this community.*


## Key Symbols

- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_download.c:31`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_pdf_export.c:30`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `_GNU_SOURCE` (macro, `gui/browser_ui.c:12`) `#define _GNU_SOURCE`
- `UI_TOOLBAR_H` (macro, `gui/browser_ui.c:89`) `#define UI_TOOLBAR_H`
- `UI_TITLEBAR_H` (macro, `gui/browser_ui.c:90`) `#define UI_TITLEBAR_H`
- `UI_TABBAR_H` (macro, `gui/browser_ui.c:91`) `#define UI_TABBAR_H`
- `UI_TAB_MIN_W` (macro, `gui/browser_ui.c:92`) `#define UI_TAB_MIN_W`
- `UI_TAB_MAX_W` (macro, `gui/browser_ui.c:93`) `#define UI_TAB_MAX_W`
- `UI_TAB_NEW_W` (macro, `gui/browser_ui.c:94`) `#define UI_TAB_NEW_W`
- `UI_TAB_CLOSE_W` (macro, `gui/browser_ui.c:95`) `#define UI_TAB_CLOSE_W`
- `UI_BTN_W` (macro, `gui/browser_ui.c:96`) `#define UI_BTN_W`
- `UI_WIN_BTN_W` (macro, `gui/browser_ui.c:97`) `#define UI_WIN_BTN_W`
- `UI_MARGIN` (macro, `gui/browser_ui.c:98`) `#define UI_MARGIN`
- `UI_BTN_LEFT` (macro, `gui/browser_ui.c:99`) `#define UI_BTN_LEFT`
- `UI_LIST_INDENT` (macro, `gui/browser_ui.c:103`) `#define UI_LIST_INDENT`
- `UI_SCROLLBAR_W` (macro, `gui/browser_ui.c:108`) `#define UI_SCROLLBAR_W`
- `UI_SCROLLBAR_MIN` (macro, `gui/browser_ui.c:109`) `#define UI_SCROLLBAR_MIN`
- `UI_SCROLLBAR_PAD` (macro, `gui/browser_ui.c:110`) `#define UI_SCROLLBAR_PAD`
- `UI_RESIZE_MARGIN` (macro, `gui/browser_ui.c:114`) `#define UI_RESIZE_MARGIN`
- `UI_MENU_W` (macro, `gui/browser_ui.c:119`) `#define UI_MENU_W`
- `UI_MENU_ITEM_H` (macro, `gui/browser_ui.c:120`) `#define UI_MENU_ITEM_H`
- `UI_MENU_PAD` (macro, `gui/browser_ui.c:121`) `#define UI_MENU_PAD`
- `UI_CHECK_SZ` (macro, `gui/browser_ui.c:122`) `#define UI_CHECK_SZ`
- `UI_MENU_LABEL_H` (macro, `gui/browser_ui.c:123`) `#define UI_MENU_LABEL_H`
- `UI_MENU_INPUT_H` (macro, `gui/browser_ui.c:124`) `#define UI_MENU_INPUT_H`
- `UI_HAMBURGER_W` (macro, `gui/browser_ui.c:125`) `#define UI_HAMBURGER_W`
- `UI_HAMBURGER_GAP` (macro, `gui/browser_ui.c:126`) `#define UI_HAMBURGER_GAP`
- `UI_CURSOR_SIZE` (macro, `gui/browser_ui.c:127`) `#define UI_CURSOR_SIZE`
- `UI_TOAST_PAD` (macro, `gui/browser_ui.c:128`) `#define UI_TOAST_PAD`
- `OMNI_MAX_SUGG` (macro, `gui/browser_ui.c:129`) `#define OMNI_MAX_SUGG`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 53
- Cross-boundary resolved imports (EXTRACTED): 44

## Connections

- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/box_style.h.
- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/compositor.h.
- [EXTRACTED] depends_on community 1 <-> 6 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/svg_paint.h.
- [EXTRACTED] depends_on community 1 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/freebug.h.
- [EXTRACTED] depends_on community 1 <-> 9 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/image_decode.h.
- [EXTRACTED] depends_on community 1 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefetch.h.
- [EXTRACTED] depends_on community 1 <-> 5 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefs.h.
- [EXTRACTED] depends_on community 1 <-> 7 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/secure_fetch.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [dataflow UNCHECKED_ALLOC] `gui/browser_ui.c:1520` `gui_subresource_fetch` `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- [dataflow DEAD_STORE] `gui/browser_ui.c:1685` `first` `dg`: `dg` assigned at line 1685 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:4287` `flow_text` `space_w`: `space_w` assigned at line 4287 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:4289` `flow_text` `i`: `i` assigned at line 4289 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5298` `table` `parent`: `parent` assigned at line 5298 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5299` `table` `seen`: `seen` assigned at line 5299 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5301` `table` `j`: `j` assigned at line 5301 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5601` `nested_cont_basis` `total`: `total` assigned at line 5601 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5602` `nested_cont_basis` `n_items`: `n_items` assigned at line 5602 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:8166` `defer_flush` `fw`: `fw` assigned at line 8166 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:8167` `defer_flush` `ngroups`: `ngroups` assigned at line 8167 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:8431` `layout_float_band` `base_top`: `base_top` assigned at line 8431 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:8654` `layout_float_band` `sr`: `sr` assigned at line 8654 but never read afterwards.

## Open Questions

- Why do 49 file(s) lack file-level docs (e.g. `fuzz/fuzz_download.c`)? What purpose do they serve?
- What would break if the most connected file in include: browser_ui changed?
- Should include: browser_ui be split, given cohesion 0.55?

## Sources

- `fuzz/fuzz_download.c`
- `fuzz/fuzz_pdf_export.c`
- `fuzz/fuzz_tls_impersonate.c`
- `gui/browser_ui.c`
- `include/block_flow.h`
- `include/box_blur.h`
- `include/browser.h`
- `include/download.h`
- `include/form.h`
- `include/frame_clock.h`
- `include/hls.h`
- `include/host_conf.h`
- `include/hostblock.h`
- `include/hostedit.h`
- `include/interp.h`
- `include/media_decoder.h`
- `include/net_realm.h`
- `include/pdf_export.h`
- `include/textfield.h`
- `include/tls_impersonate.h`
- *... and 32 more*
