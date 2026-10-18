# include: browser_ui

*Community 2 | 46 files | cohesion 0.52*

## Definition

This community groups 46 file(s) rooted at `tests` with dominant language c (cohesion 0.52). Central symbols: `ABSENT`, `ALIVE`, `BALANCE_MAX_LINES`, `BB_MAX_PIXELS`, `BROWSER_STATUS_DURATION_MS`, `BROWSER_STATUS_MAX`, `BROWSER_URL_MAX`, `BUI_CONIC_SLICES`. Core file: `gui/browser_ui.c` (574 symbols). Documented purpose: block_flow (bf_) -- vertical margin collapsing for block-level boxes..

## Files

### `tests` (15 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_block_flow.c` | c | testing | 8 | no |
| `tests/test_box_blur.c` | c | testing | 7 | no |
| `tests/test_browser.c` | c | testing | 17 | no |
| `tests/test_form.c` | c | testing | 20 | no |
| `tests/test_frame_clock.c` | c | testing | 4 | no |
| `tests/test_freedom.c` | c | testing | 88 | no |

### `include` (14 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/block_flow.h` | h | utility | 4 | yes |
| `include/box_blur.h` | h | utility | 4 | yes |
| `include/browser.h` | h | utility | 19 | no |
| `include/form.h` | h | utility | 12 | no |
| `include/frame_clock.h` | h | utility | 7 | no |
| `include/hls.h` | h | utility | 8 | no |

### `src` (14 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/block_flow.c` | c | utility | 4 | yes |
| `src/box_blur.c` | c | utility | 4 | no |
| `src/browser.c` | c | utility | 41 | no |
| `src/form.c` | c | utility | 8 | no |
| `src/frame_clock.c` | c | utility | 4 | no |

### `fuzz` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_image_decode.c` | c | utility | 2 | no |
| `fuzz/fuzz_tls_impersonate.c` | c | utility | 0 | no |

### `gui` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui.c` | c | presentation | 574 | no |

*... and 26 more files in this community.*


## Key Symbols

- `poke_and_free` (function, `fuzz/fuzz_image_decode.c:21`) `static void poke_and_free(img_pixels *px)` - Touch every claimed pixel corner so the sanitizer flags an out-of-bounds extent, * then release. Saf
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_image_decode.c:32`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `_GNU_SOURCE` (macro, `gui/browser_ui.c:12`) `#define _GNU_SOURCE`
- `UI_TOOLBAR_H` (macro, `gui/browser_ui.c:85`) `#define UI_TOOLBAR_H`
- `UI_TITLEBAR_H` (macro, `gui/browser_ui.c:86`) `#define UI_TITLEBAR_H`
- `UI_TABBAR_H` (macro, `gui/browser_ui.c:87`) `#define UI_TABBAR_H`
- `UI_TAB_MIN_W` (macro, `gui/browser_ui.c:88`) `#define UI_TAB_MIN_W`
- `UI_TAB_MAX_W` (macro, `gui/browser_ui.c:89`) `#define UI_TAB_MAX_W`
- `UI_TAB_NEW_W` (macro, `gui/browser_ui.c:90`) `#define UI_TAB_NEW_W`
- `UI_TAB_CLOSE_W` (macro, `gui/browser_ui.c:91`) `#define UI_TAB_CLOSE_W`
- `UI_BTN_W` (macro, `gui/browser_ui.c:92`) `#define UI_BTN_W`
- `UI_WIN_BTN_W` (macro, `gui/browser_ui.c:93`) `#define UI_WIN_BTN_W`
- `UI_MARGIN` (macro, `gui/browser_ui.c:94`) `#define UI_MARGIN`
- `UI_BTN_LEFT` (macro, `gui/browser_ui.c:95`) `#define UI_BTN_LEFT`
- `UI_LIST_INDENT` (macro, `gui/browser_ui.c:99`) `#define UI_LIST_INDENT`
- `UI_SCROLLBAR_W` (macro, `gui/browser_ui.c:104`) `#define UI_SCROLLBAR_W`
- `UI_SCROLLBAR_MIN` (macro, `gui/browser_ui.c:105`) `#define UI_SCROLLBAR_MIN`
- `UI_SCROLLBAR_PAD` (macro, `gui/browser_ui.c:106`) `#define UI_SCROLLBAR_PAD`
- `UI_RESIZE_MARGIN` (macro, `gui/browser_ui.c:110`) `#define UI_RESIZE_MARGIN`
- `UI_MENU_W` (macro, `gui/browser_ui.c:115`) `#define UI_MENU_W`
- `UI_MENU_ITEM_H` (macro, `gui/browser_ui.c:116`) `#define UI_MENU_ITEM_H`
- `UI_MENU_PAD` (macro, `gui/browser_ui.c:117`) `#define UI_MENU_PAD`
- `UI_CHECK_SZ` (macro, `gui/browser_ui.c:118`) `#define UI_CHECK_SZ`
- `UI_MENU_LABEL_H` (macro, `gui/browser_ui.c:119`) `#define UI_MENU_LABEL_H`
- `UI_MENU_INPUT_H` (macro, `gui/browser_ui.c:120`) `#define UI_MENU_INPUT_H`
- `UI_HAMBURGER_W` (macro, `gui/browser_ui.c:121`) `#define UI_HAMBURGER_W`
- `UI_HAMBURGER_GAP` (macro, `gui/browser_ui.c:122`) `#define UI_HAMBURGER_GAP`
- `UI_CURSOR_SIZE` (macro, `gui/browser_ui.c:123`) `#define UI_CURSOR_SIZE`
- `UI_TOAST_PAD` (macro, `gui/browser_ui.c:124`) `#define UI_TOAST_PAD`
- `OMNI_MAX_SUGG` (macro, `gui/browser_ui.c:125`) `#define OMNI_MAX_SUGG`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 45
- Cross-boundary resolved imports (EXTRACTED): 42

## Connections

- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/box_style.h.
- [EXTRACTED] depends_on community 2 <-> 1 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/compositor.h.
- [EXTRACTED] depends_on community 2 <-> 6 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/svg_paint.h.
- [EXTRACTED] depends_on community 2 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 2 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/download.h.
- [EXTRACTED] depends_on community 2 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/freebug.h.
- [EXTRACTED] depends_on community 2 <-> 9 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefetch.h.
- [EXTRACTED] depends_on community 2 <-> 5 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefs.h.
- [EXTRACTED] depends_on community 2 <-> 7 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/secure_fetch.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [dataflow UNCHECKED_ALLOC] `gui/browser_ui.c:1569` `gui_subresource_fetch` `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- [dataflow DEAD_STORE] `gui/browser_ui.c:1734` `first` `dg`: `dg` assigned at line 1734 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:4325` `flow_text` `space_w`: `space_w` assigned at line 4325 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:4327` `flow_text` `i`: `i` assigned at line 4327 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5307` `table` `parent`: `parent` assigned at line 5307 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5308` `table` `seen`: `seen` assigned at line 5308 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5310` `table` `j`: `j` assigned at line 5310 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5576` `nested_cont_basis` `total`: `total` assigned at line 5576 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5577` `nested_cont_basis` `n_items`: `n_items` assigned at line 5577 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:9840` `button_box_width` `cx`: `cx` assigned at line 9840 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:10984` `paint_box_decoration` `bt`: `bt` assigned at line 10984 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:10985` `paint_box_decoration` `bb`: `bb` assigned at line 10985 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:11114` `layer` `on`: `on` assigned at line 11114 but never read afterwards.

## Open Questions

- Why do 43 file(s) lack file-level docs (e.g. `fuzz/fuzz_image_decode.c`)? What purpose do they serve?
- What would break if the most connected file in include: browser_ui changed?
- Should include: browser_ui be split, given cohesion 0.52?

## Sources

- `fuzz/fuzz_image_decode.c`
- `fuzz/fuzz_tls_impersonate.c`
- `gui/browser_ui.c`
- `include/block_flow.h`
- `include/box_blur.h`
- `include/browser.h`
- `include/form.h`
- `include/frame_clock.h`
- `include/hls.h`
- `include/hostblock.h`
- `include/hostedit.h`
- `include/image_decode.h`
- `include/interp.h`
- `include/media_decoder.h`
- `include/net_realm.h`
- `include/textfield.h`
- `include/tls_impersonate.h`
- `src/block_flow.c`
- `src/box_blur.c`
- `src/browser.c`
- *... and 26 more*
