# include

*Community 3 | 85 files | cohesion 0.64*

## Definition

This community groups 85 file(s) rooted at `include` with dominant language c (cohesion 0.64). Central symbols: `ABSENT`, `ALIVE`, `BLOCK`, `BLOCKED`, `BT_ALIGN_CENTER`, `BT_ALIGN_END`, `BT_ALIGN_START`, `BT_ALIGN_STRETCH`. Core file: `gui/browser_ui.c` (525 symbols). Documented purpose: block_flow (bf_) -- vertical margin collapsing for block-level boxes..

## Files

### `include` (29 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/block_flow.h` | h | utility | 4 | yes |
| `include/box_style.h` | h | utility | 25 | no |
| `include/box_tree.h` | h | utility | 32 | no |
| `include/dom_debug.h` | h | utility | 4 | no |
| `include/flex_layout.h` | h | presentation | 34 | no |

### `tests` (28 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/itest_secure_fetch.c` | c | testing | 2 | no |
| `tests/test_block_flow.c` | c | testing | 8 | no |
| `tests/test_box_style.c` | c | testing | 42 | no |
| `tests/test_box_tree.c` | c | testing | 57 | no |
| `tests/test_dom_debug.c` | c | testing | 11 | no |

### `src` (22 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/block_flow.c` | c | utility | 4 | yes |
| `src/box_style.c` | c | utility | 41 | no |
| `src/dom_debug.c` | c | utility | 24 | no |
| `src/flex_layout.c` | c | presentation | 23 | no |

### `fuzz` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_dom_debug.c` | c | utility | 1 | no |
| `fuzz/fuzz_freebug.c` | c | utility | 1 | no |
| `fuzz/fuzz_prefs.c` | c | utility | 1 | no |
| `fuzz/fuzz_tls_impersonate.c` | c | utility | 0 | no |

### `gui` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui.c` | c | presentation | 525 | no |
| `gui/freedom_view.c` | c | presentation | 2 | no |

*... and 65 more files in this community.*


## Key Symbols

- `pass` (function, `fuzz/fuzz_dom_debug.c:8`) `* the measure pass (cap 0) must agree with the would-write return value.  *  * B`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_freebug.c:37`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_prefs.c:21`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
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

- Internal resolved imports (EXTRACTED): 136
- Cross-boundary resolved imports (EXTRACTED): 77

## Connections

- [EXTRACTED] depends_on community 3 <-> 2 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_dom_debug.c imports include/html_parse.h.
- [EXTRACTED] depends_on community 7 <-> 3 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_page_view.c imports include/page_view.h.
- [EXTRACTED] depends_on community 10 <-> 3 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_url.c imports include/link_nav.h.
- [EXTRACTED] depends_on community 3 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/browser.h.
- [EXTRACTED] depends_on community 3 <-> 1 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 3 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/download.h.
- [EXTRACTED] depends_on community 3 <-> 12 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/frame_clock.h.
- [EXTRACTED] depends_on community 3 <-> 5 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/image_decode.h.
- [EXTRACTED] depends_on community 3 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/pdf_export.h.
- [EXTRACTED] depends_on community 3 <-> 9 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefetch.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/form.h` (data_access)
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [layer strict] `src/render_policy.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `tests/test_box_tree.c` (testing) -> `include/page_view.h` (presentation)
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

## Open Questions

- Why do 83 file(s) lack file-level docs (e.g. `fuzz/fuzz_dom_debug.c`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.64?

## Sources

- `fuzz/fuzz_dom_debug.c`
- `fuzz/fuzz_freebug.c`
- `fuzz/fuzz_prefs.c`
- `fuzz/fuzz_tls_impersonate.c`
- `gui/browser_ui.c`
- `gui/freedom_view.c`
- `include/block_flow.h`
- `include/box_style.h`
- `include/box_tree.h`
- `include/dom_debug.h`
- `include/flex_layout.h`
- `include/freebug.h`
- `include/hls.h`
- `include/hostblock.h`
- `include/hostedit.h`
- `include/interp.h`
- `include/js_policy.h`
- `include/link_nav.h`
- `include/media_decoder.h`
- `include/net_realm.h`
- *... and 65 more*
