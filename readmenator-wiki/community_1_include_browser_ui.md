# include: browser_ui

*Community 1 | 47 files | cohesion 0.54*

## Definition

This community groups 47 file(s) rooted at `tests` with dominant language c (cohesion 0.54). Central symbols: `ABSENT`, `ALIVE`, `BROWSER_STATUS_DURATION_MS`, `BROWSER_STATUS_MAX`, `BROWSER_URL_MAX`, `BUI_CONIC_SLICES`, `ERR_FILE`, `FBW_COPY_BTN_H`. Core file: `gui/browser_ui.c` (526 symbols). Documented purpose: libFuzzer harness for the prefetch lookahead scanner (Hito 29). The scanned.

## Files

### `tests` (15 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_block_flow.c` | c | testing | 8 | no |
| `tests/test_browser.c` | c | testing | 17 | no |
| `tests/test_form.c` | c | testing | 20 | no |
| `tests/test_frame_clock.c` | c | testing | 4 | no |
| `tests/test_freedom.c` | c | testing | 70 | no |
| `tests/test_hls.c` | c | testing | 16 | no |

### `include` (14 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/block_flow.h` | h | utility | 4 | yes |
| `include/browser.h` | h | utility | 19 | no |
| `include/form.h` | h | utility | 12 | no |
| `include/frame_clock.h` | h | utility | 7 | no |
| `include/hls.h` | h | utility | 8 | no |

### `src` (14 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/block_flow.c` | c | utility | 4 | yes |
| `src/browser.c` | c | utility | 41 | no |
| `src/form.c` | c | utility | 8 | no |
| `src/frame_clock.c` | c | utility | 4 | no |
| `src/hls.c` | c | utility | 10 | no |

### `fuzz` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_image_decode.c` | c | utility | 2 | no |
| `fuzz/fuzz_prefetch.c` | c | utility | 1 | yes |
| `fuzz/fuzz_tls_impersonate.c` | c | utility | 0 | no |

### `gui` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui.c` | c | presentation | 526 | no |

*... and 27 more files in this community.*


## Key Symbols

- `poke_and_free` (function, `fuzz/fuzz_image_decode.c:21`) `static void poke_and_free(img_pixels *px)` - Touch every claimed pixel corner so the sanitizer flags an out-of-bounds extent, * then release. Saf
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_image_decode.c:32`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_prefetch.c:10`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `_GNU_SOURCE` (macro, `gui/browser_ui.c:12`) `#define _GNU_SOURCE`
- `UI_TOOLBAR_H` (macro, `gui/browser_ui.c:81`) `#define UI_TOOLBAR_H`
- `UI_TITLEBAR_H` (macro, `gui/browser_ui.c:82`) `#define UI_TITLEBAR_H`
- `UI_TABBAR_H` (macro, `gui/browser_ui.c:83`) `#define UI_TABBAR_H`
- `UI_TAB_MIN_W` (macro, `gui/browser_ui.c:84`) `#define UI_TAB_MIN_W`
- `UI_TAB_MAX_W` (macro, `gui/browser_ui.c:85`) `#define UI_TAB_MAX_W`
- `UI_TAB_NEW_W` (macro, `gui/browser_ui.c:86`) `#define UI_TAB_NEW_W`
- `UI_TAB_CLOSE_W` (macro, `gui/browser_ui.c:87`) `#define UI_TAB_CLOSE_W`
- `UI_BTN_W` (macro, `gui/browser_ui.c:88`) `#define UI_BTN_W`
- `UI_WIN_BTN_W` (macro, `gui/browser_ui.c:89`) `#define UI_WIN_BTN_W`
- `UI_MARGIN` (macro, `gui/browser_ui.c:90`) `#define UI_MARGIN`
- `UI_BTN_LEFT` (macro, `gui/browser_ui.c:91`) `#define UI_BTN_LEFT`
- `UI_LIST_INDENT` (macro, `gui/browser_ui.c:95`) `#define UI_LIST_INDENT`
- `UI_SCROLLBAR_W` (macro, `gui/browser_ui.c:100`) `#define UI_SCROLLBAR_W`
- `UI_SCROLLBAR_MIN` (macro, `gui/browser_ui.c:101`) `#define UI_SCROLLBAR_MIN`
- `UI_SCROLLBAR_PAD` (macro, `gui/browser_ui.c:102`) `#define UI_SCROLLBAR_PAD`
- `UI_RESIZE_MARGIN` (macro, `gui/browser_ui.c:106`) `#define UI_RESIZE_MARGIN`
- `UI_MENU_W` (macro, `gui/browser_ui.c:111`) `#define UI_MENU_W`
- `UI_MENU_ITEM_H` (macro, `gui/browser_ui.c:112`) `#define UI_MENU_ITEM_H`
- `UI_MENU_PAD` (macro, `gui/browser_ui.c:113`) `#define UI_MENU_PAD`
- `UI_CHECK_SZ` (macro, `gui/browser_ui.c:114`) `#define UI_CHECK_SZ`
- `UI_MENU_LABEL_H` (macro, `gui/browser_ui.c:115`) `#define UI_MENU_LABEL_H`
- `UI_MENU_INPUT_H` (macro, `gui/browser_ui.c:116`) `#define UI_MENU_INPUT_H`
- `UI_HAMBURGER_W` (macro, `gui/browser_ui.c:117`) `#define UI_HAMBURGER_W`
- `UI_HAMBURGER_GAP` (macro, `gui/browser_ui.c:118`) `#define UI_HAMBURGER_GAP`
- `UI_CURSOR_SIZE` (macro, `gui/browser_ui.c:119`) `#define UI_CURSOR_SIZE`
- `UI_TOAST_PAD` (macro, `gui/browser_ui.c:120`) `#define UI_TOAST_PAD`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 46
- Cross-boundary resolved imports (EXTRACTED): 39

## Connections

- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/box_style.h.
- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/compositor.h.
- [EXTRACTED] depends_on community 1 <-> 6 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/svg_paint.h.
- [EXTRACTED] depends_on community 1 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 1 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/download.h.
- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/freebug.h.
- [EXTRACTED] depends_on community 1 <-> 5 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefs.h.
- [EXTRACTED] depends_on community 1 <-> 7 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/secure_fetch.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [dataflow UNCHECKED_ALLOC] `gui/browser_ui.c:1446` `gui_subresource_fetch` `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- [dataflow DEAD_STORE] `gui/browser_ui.c:3905` `flow_text` `space_w`: `space_w` assigned at line 3905 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:3907` `flow_text` `i`: `i` assigned at line 3907 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:7109` `layout_float_band` `base_top`: `base_top` assigned at line 7109 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:8607` `button_box_width` `cx`: `cx` assigned at line 8607 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:9660` `paint_box_decoration` `bt`: `bt` assigned at line 9660 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:9661` `paint_box_decoration` `bb`: `bb` assigned at line 9661 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:9820` `layer` `on`: `on` assigned at line 9820 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:9863` `cairo_set_dash` `on`: `on` assigned at line 9863 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:9898` `convention` `nr`: `nr` assigned at line 9898 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:9899` `convention` `ng`: `ng` assigned at line 9899 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:9900` `convention` `nb`: `nb` assigned at line 9900 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:9924` `set_rgb` `on`: `on` assigned at line 9924 but never read afterwards.

## Open Questions

- Why do 43 file(s) lack file-level docs (e.g. `fuzz/fuzz_image_decode.c`)? What purpose do they serve?
- What would break if the most connected file in include: browser_ui changed?
- Should include: browser_ui be split, given cohesion 0.54?

## Sources

- `fuzz/fuzz_image_decode.c`
- `fuzz/fuzz_prefetch.c`
- `fuzz/fuzz_tls_impersonate.c`
- `gui/browser_ui.c`
- `include/block_flow.h`
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
- `include/prefetch.h`
- `include/textfield.h`
- `include/tls_impersonate.h`
- `src/block_flow.c`
- `src/browser.c`
- *... and 27 more*
