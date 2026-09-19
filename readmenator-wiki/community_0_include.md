# include

*Community 0 | 172 files | cohesion 0.96*

## Definition

This community groups 172 file(s) rooted at `include` with dominant language c (cohesion 0.96). Central symbols: `ALIVE`, `AUTO_REJECT`, `AUTO_RESET`, `AUTO_RESET_NONE`, `AUTO_VALUE`, `BLOCK`, `BLOCKED`, `BROWSER_STATUS_DURATION_MS`. Core file: `gui/browser_ui.c` (493 symbols). Documented purpose: svg_paint — Cairo back end for the shapes svg_render extracted..

## Files

### `include` (54 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/anti_fp.h` | h | utility | 35 | no |
| `include/box_style.h` | h | utility | 24 | no |
| `include/box_tree.h` | h | utility | 28 | no |
| `include/browser.h` | h | utility | 17 | no |

### `src` (50 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/anti_fp.c` | c | utility | 23 | no |
| `src/box_style.c` | c | utility | 40 | no |
| `src/box_tree.c` | c | utility | 19 | no |
| `src/browser.c` | c | utility | 37 | no |

### `tests` (50 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/itest_secure_fetch.c` | c | testing | 2 | no |
| `tests/test_anti_fp.c` | c | testing | 15 | no |
| `tests/test_box_style.c` | c | testing | 41 | no |
| `tests/test_box_tree.c` | c | testing | 55 | no |

### `fuzz` (12 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_css.c` | c | utility | 1 | no |
| `fuzz/fuzz_data_url.c` | c | data_access | 1 | no |
| `fuzz/fuzz_dom.c` | c | utility | 2 | no |
| `fuzz/fuzz_dom_debug.c` | c | utility | 1 | no |

### `gui` (6 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui.c` | c | presentation | 493 | no |
| `gui/browser_ui_internal.h` | h | presentation | 10 | no |
| `gui/bui_theme.c` | c | presentation | 6 | no |
| `gui/freedom_view.c` | c | presentation | 2 | no |

*... and 152 more files in this community.*


## Key Symbols

- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_css.c:62`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `worker` (function, `fuzz/fuzz_data_url.c:5`) `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, nev`
- `ensure_built` (function, `fuzz/fuzz_dom.c:41`) `static void ensure_built(void)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_dom.c:48`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `pass` (function, `fuzz/fuzz_dom_debug.c:8`) `* the measure pass (cap 0) must agree with the would-write return value.  *  * B`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_freebug.c:37`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `poke_and_free` (function, `fuzz/fuzz_image_decode.c:21`) `static void poke_and_free(img_pixels *px)` - Touch every claimed pixel corner so the sanitizer flags an out-of-bounds extent, * then release. Saf
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_image_decode.c:32`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_prefs.c:21`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_svg_render.c:24`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `check_split` (function, `fuzz/fuzz_url.c:30`) `static void check_split(const char *url)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_url.c:58`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
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
- `UI_LIST_INDENT` (macro, `gui/browser_ui.c:92`) `#define UI_LIST_INDENT`
- `UI_SCROLLBAR_W` (macro, `gui/browser_ui.c:97`) `#define UI_SCROLLBAR_W`
- `UI_SCROLLBAR_MIN` (macro, `gui/browser_ui.c:98`) `#define UI_SCROLLBAR_MIN`
- `UI_SCROLLBAR_PAD` (macro, `gui/browser_ui.c:99`) `#define UI_SCROLLBAR_PAD`
- `UI_RESIZE_MARGIN` (macro, `gui/browser_ui.c:103`) `#define UI_RESIZE_MARGIN`
- `UI_MENU_W` (macro, `gui/browser_ui.c:108`) `#define UI_MENU_W`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 354
- Cross-boundary resolved imports (EXTRACTED): 15

## Connections

- [EXTRACTED] depends_on community 0 <-> 6 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/block_flow.h.
- [EXTRACTED] depends_on community 0 <-> 1 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/download.h.
- [EXTRACTED] depends_on community 0 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/interp.h.
- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/pdf_export.h.
- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefetch.h.
- [EXTRACTED] depends_on community 0 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/text_shape.h.
- [EXTRACTED] depends_on community 0 <-> 9 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/textfield.h.
- [EXTRACTED] depends_on community 0 <-> 5 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/tls_impersonate.h.
- [EXTRACTED] depends_on community 0 <-> 7 (strength 0.9): Extracted import edge crosses communities: include/profile.h imports include/local_store.h.
- [INFERRED] shares_context community 0 <-> 10 (strength 0.5): Inferred shared context (layer utility) with no import path between community 0 (include) and community 10 (orphans).

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/form.h` (data_access)
- [layer strict] `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access)
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

- Why do 164 file(s) lack file-level docs (e.g. `fuzz/fuzz_css.c`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.96?

## Sources

- `fuzz/fuzz_css.c`
- `fuzz/fuzz_data_url.c`
- `fuzz/fuzz_dom.c`
- `fuzz/fuzz_dom_debug.c`
- `fuzz/fuzz_freebug.c`
- `fuzz/fuzz_html_parse.c`
- `fuzz/fuzz_image_decode.c`
- `fuzz/fuzz_js_sandbox.c`
- `fuzz/fuzz_page_view.c`
- `fuzz/fuzz_prefs.c`
- `fuzz/fuzz_svg_render.c`
- `fuzz/fuzz_url.c`
- `gui/browser_ui.c`
- `gui/browser_ui_internal.h`
- `gui/bui_theme.c`
- `gui/freedom_view.c`
- `gui/svg_paint.c`
- `gui/ui_render.c`
- `include/anti_fp.h`
- `include/box_style.h`
- *... and 152 more*
