# include: browser_ui

*Community 1 | 51 files | cohesion 0.57*

## Definition

This community groups 51 file(s) rooted at `tests` with dominant language c (cohesion 0.57). Central symbols: `ABSENT`, `ALIVE`, `BALANCE_MAX_LINES`, `BROWSER_STATUS_DURATION_MS`, `BROWSER_STATUS_MAX`, `BROWSER_URL_MAX`, `BUI_CONIC_SLICES`, `DL_ERR_OVERFLOW`. Core file: `gui/browser_ui.c` (548 symbols). Documented purpose: block_flow (bf_) -- vertical margin collapsing for block-level boxes..

## Files

### `tests` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_block_flow.c` | c | testing | 8 | no |
| `tests/test_browser.c` | c | testing | 17 | no |
| `tests/test_download.c` | c | testing | 21 | no |
| `tests/test_form.c` | c | testing | 20 | no |
| `tests/test_frame_clock.c` | c | testing | 4 | no |

### `include` (15 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/block_flow.h` | h | utility | 4 | yes |
| `include/browser.h` | h | utility | 19 | no |
| `include/download.h` | h | utility | 9 | no |
| `include/form.h` | h | utility | 12 | no |
| `include/frame_clock.h` | h | utility | 7 | no |

### `src` (15 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/block_flow.c` | c | utility | 4 | yes |
| `src/browser.c` | c | utility | 41 | no |
| `src/download.c` | c | utility | 12 | no |
| `src/form.c` | c | utility | 8 | no |
| `src/frame_clock.c` | c | utility | 4 | no |

### `fuzz` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_download.c` | c | utility | 1 | no |
| `fuzz/fuzz_image_decode.c` | c | utility | 2 | no |
| `fuzz/fuzz_pdf_export.c` | c | utility | 1 | no |
| `fuzz/fuzz_tls_impersonate.c` | c | utility | 0 | no |

### `gui` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui.c` | c | presentation | 548 | no |

*... and 31 more files in this community.*


## Key Symbols

- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_download.c:31`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `poke_and_free` (function, `fuzz/fuzz_image_decode.c:21`) `static void poke_and_free(img_pixels *px)` - Touch every claimed pixel corner so the sanitizer flags an out-of-bounds extent, * then release. Saf
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_image_decode.c:32`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_pdf_export.c:30`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `_GNU_SOURCE` (macro, `gui/browser_ui.c:12`) `#define _GNU_SOURCE`
- `UI_TOOLBAR_H` (macro, `gui/browser_ui.c:83`) `#define UI_TOOLBAR_H`
- `UI_TITLEBAR_H` (macro, `gui/browser_ui.c:84`) `#define UI_TITLEBAR_H`
- `UI_TABBAR_H` (macro, `gui/browser_ui.c:85`) `#define UI_TABBAR_H`
- `UI_TAB_MIN_W` (macro, `gui/browser_ui.c:86`) `#define UI_TAB_MIN_W`
- `UI_TAB_MAX_W` (macro, `gui/browser_ui.c:87`) `#define UI_TAB_MAX_W`
- `UI_TAB_NEW_W` (macro, `gui/browser_ui.c:88`) `#define UI_TAB_NEW_W`
- `UI_TAB_CLOSE_W` (macro, `gui/browser_ui.c:89`) `#define UI_TAB_CLOSE_W`
- `UI_BTN_W` (macro, `gui/browser_ui.c:90`) `#define UI_BTN_W`
- `UI_WIN_BTN_W` (macro, `gui/browser_ui.c:91`) `#define UI_WIN_BTN_W`
- `UI_MARGIN` (macro, `gui/browser_ui.c:92`) `#define UI_MARGIN`
- `UI_BTN_LEFT` (macro, `gui/browser_ui.c:93`) `#define UI_BTN_LEFT`
- `UI_LIST_INDENT` (macro, `gui/browser_ui.c:97`) `#define UI_LIST_INDENT`
- `UI_SCROLLBAR_W` (macro, `gui/browser_ui.c:102`) `#define UI_SCROLLBAR_W`
- `UI_SCROLLBAR_MIN` (macro, `gui/browser_ui.c:103`) `#define UI_SCROLLBAR_MIN`
- `UI_SCROLLBAR_PAD` (macro, `gui/browser_ui.c:104`) `#define UI_SCROLLBAR_PAD`
- `UI_RESIZE_MARGIN` (macro, `gui/browser_ui.c:108`) `#define UI_RESIZE_MARGIN`
- `UI_MENU_W` (macro, `gui/browser_ui.c:113`) `#define UI_MENU_W`
- `UI_MENU_ITEM_H` (macro, `gui/browser_ui.c:114`) `#define UI_MENU_ITEM_H`
- `UI_MENU_PAD` (macro, `gui/browser_ui.c:115`) `#define UI_MENU_PAD`
- `UI_CHECK_SZ` (macro, `gui/browser_ui.c:116`) `#define UI_CHECK_SZ`
- `UI_MENU_LABEL_H` (macro, `gui/browser_ui.c:117`) `#define UI_MENU_LABEL_H`
- `UI_MENU_INPUT_H` (macro, `gui/browser_ui.c:118`) `#define UI_MENU_INPUT_H`
- `UI_HAMBURGER_W` (macro, `gui/browser_ui.c:119`) `#define UI_HAMBURGER_W`
- `UI_HAMBURGER_GAP` (macro, `gui/browser_ui.c:120`) `#define UI_HAMBURGER_GAP`
- `UI_CURSOR_SIZE` (macro, `gui/browser_ui.c:121`) `#define UI_CURSOR_SIZE`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 51
- Cross-boundary resolved imports (EXTRACTED): 39

## Connections

- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/box_style.h.
- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/compositor.h.
- [EXTRACTED] depends_on community 1 <-> 6 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/svg_paint.h.
- [EXTRACTED] depends_on community 1 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/freebug.h.
- [EXTRACTED] depends_on community 1 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefetch.h.
- [EXTRACTED] depends_on community 1 <-> 5 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefs.h.
- [EXTRACTED] depends_on community 1 <-> 7 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/secure_fetch.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [dataflow UNCHECKED_ALLOC] `gui/browser_ui.c:1488` `gui_subresource_fetch` `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- [dataflow DEAD_STORE] `gui/browser_ui.c:1653` `first` `dg`: `dg` assigned at line 1653 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:4124` `flow_text` `space_w`: `space_w` assigned at line 4124 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:4126` `flow_text` `i`: `i` assigned at line 4126 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5003` `table` `parent`: `parent` assigned at line 5003 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5004` `table` `seen`: `seen` assigned at line 5004 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5006` `table` `j`: `j` assigned at line 5006 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:7597` `layout_float_band` `base_top`: `base_top` assigned at line 7597 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:9152` `button_box_width` `cx`: `cx` assigned at line 9152 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:10205` `paint_box_decoration` `bt`: `bt` assigned at line 10205 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:10206` `paint_box_decoration` `bb`: `bb` assigned at line 10206 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:10365` `layer` `on`: `on` assigned at line 10365 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:10408` `cairo_set_dash` `on`: `on` assigned at line 10408 but never read afterwards.

## Open Questions

- Why do 49 file(s) lack file-level docs (e.g. `fuzz/fuzz_download.c`)? What purpose do they serve?
- What would break if the most connected file in include: browser_ui changed?
- Should include: browser_ui be split, given cohesion 0.57?

## Sources

- `fuzz/fuzz_download.c`
- `fuzz/fuzz_image_decode.c`
- `fuzz/fuzz_pdf_export.c`
- `fuzz/fuzz_tls_impersonate.c`
- `gui/browser_ui.c`
- `include/block_flow.h`
- `include/browser.h`
- `include/download.h`
- `include/form.h`
- `include/frame_clock.h`
- `include/hls.h`
- `include/hostblock.h`
- `include/hostedit.h`
- `include/image_decode.h`
- `include/interp.h`
- `include/media_decoder.h`
- `include/net_realm.h`
- `include/pdf_export.h`
- `include/textfield.h`
- `include/tls_impersonate.h`
- *... and 31 more*
