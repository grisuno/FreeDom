# include: browser_ui

*Community 1 | 65 files | cohesion 0.52*

## Definition

This community groups 65 file(s) rooted at `include` with dominant language c (cohesion 0.52). Central symbols: `AA_QUEUE_MAX`, `ABSENT`, `ALIVE`, `BALANCE_MAX_LINES`, `BB_BOX_MAX`, `BB_MAX_PIXELS`, `BROWSER_CLOSED_MAX`, `BROWSER_STATUS_DURATION_MS`. Core file: `gui/browser_ui.c` (761 symbols). Documented purpose: libFuzzer harness for box_blur (spec/box_blur.md): a hostile mask, size, stride and sigma.

## Files

### `include` (19 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/block_flow.h` | h | utility | 4 | yes |
| `include/box_blur.h` | h | utility | 5 | yes |
| `include/browser.h` | h | utility | 28 | no |
| `include/doc_title.h` | h | utility | 3 | yes |
| `include/exact_key.h` | h | utility | 9 | yes |

### `tests` (18 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_block_flow.c` | c | testing | 8 | no |
| `tests/test_box_blur.c` | c | testing | 15 | no |
| `tests/test_browser.c` | c | testing | 28 | no |
| `tests/test_doc_title.c` | c | testing | 7 | yes |
| `tests/test_exact_key.c` | c | testing | 6 | no |

### `src` (17 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/block_flow.c` | c | utility | 4 | yes |
| `src/box_blur.c` | c | utility | 9 | no |
| `src/browser.c` | c | utility | 51 | no |
| `src/doc_title.c` | c | utility | 12 | yes |
| `src/exact_key.c` | c | utility | 6 | no |

### `fuzz` (10 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_box_blur.c` | c | utility | 2 | yes |
| `fuzz/fuzz_browser.c` | c | utility | 9 | no |
| `fuzz/fuzz_doc_title.c` | c | utility | 1 | yes |
| `fuzz/fuzz_exact_key.c` | c | utility | 1 | yes |

### `gui` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui.c` | c | presentation | 761 | no |

*... and 45 more files in this community.*


## Key Symbols

- `ref_line` (function, `fuzz/fuzz_box_blur.c:12`) `static void ref_line(unsigned char *p, int n, int step, int bw, unsigned char *t`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_box_blur.c:25`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `_POSIX_C_SOURCE` (macro, `fuzz/fuzz_browser.c:8`) `#define _POSIX_C_SOURCE`
- `SNAP_MAX` (macro, `fuzz/fuzz_browser.c:17`) `#define SNAP_MAX`
- `pos` (type_alias, `fuzz/fuzz_browser.c:18`) `typedef struct snap { size_t n, pos;` - define SNAP_MAX 512
- `snap` (struct, `fuzz/fuzz_browser.c:19`)
- `snap_free` (function, `fuzz/fuzz_browser.c:25`) `static void snap_free(snap *s)`
- `snap_take` (function, `fuzz/fuzz_browser.c:30`) `static void snap_take(snap *s, const browser_state *bs)`
- `snap_check` (function, `fuzz/fuzz_browser.c:41`) `static void snap_check(const snap *s, const browser_state *bs)`
- `invariants` (function, `fuzz/fuzz_browser.c:48`) `static void invariants(const browser_state *bs)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_browser.c:53`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_doc_title.c:26`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_exact_key.c:22`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `MAXP` (macro, `fuzz/fuzz_find_text.c:9`) `#define MAXP`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_find_text.c:11`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_group_index.c:9`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `KEYS` (macro, `fuzz/fuzz_mask_cache.c:13`) `#define KEYS`
- `key_for` (function, `fuzz/fuzz_mask_cache.c:15`) `static mkc_key key_for(unsigned id, int w, int h)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_mask_cache.c:21`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `POOL` (macro, `fuzz/fuzz_nav_token.c:11`) `#define POOL`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_nav_token.c:13`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `take` (function, `fuzz/fuzz_smooth_scroll.c:11`) `static double take(const uint8_t **d, size_t *n)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_smooth_scroll.c:18`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `_GNU_SOURCE` (macro, `gui/browser_ui.c:12`) `#define _GNU_SOURCE`
- `UI_TOOLBAR_H` (macro, `gui/browser_ui.c:108`) `#define UI_TOOLBAR_H`
- `UI_MARGIN` (macro, `gui/browser_ui.c:109`) `#define UI_MARGIN`
- `UI_BTN_LEFT` (macro, `gui/browser_ui.c:110`) `#define UI_BTN_LEFT`
- `UI_BTN_MIDDLE` (macro, `gui/browser_ui.c:111`) `#define UI_BTN_MIDDLE`
- `UI_LIST_INDENT` (macro, `gui/browser_ui.c:115`) `#define UI_LIST_INDENT`
- `UI_SCROLLBAR_W` (macro, `gui/browser_ui.c:120`) `#define UI_SCROLLBAR_W`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 66
- Cross-boundary resolved imports (EXTRACTED): 62

## Connections

- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/anchor.h.
- [EXTRACTED] depends_on community 1 <-> 12 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/table_layout.h.
- [EXTRACTED] depends_on community 1 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/box_style.h.
- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/compositor.h.
- [EXTRACTED] depends_on community 1 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/svg_paint.h.
- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 1 <-> 10 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/download.h.
- [EXTRACTED] depends_on community 1 <-> 9 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/freebug.h.
- [EXTRACTED] depends_on community 1 <-> 6 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/identity.h.
- [EXTRACTED] depends_on community 1 <-> 7 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/link_nav.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [dataflow UNCHECKED_ALLOC] `gui/browser_ui.c:1842` `gui_sub_perform` `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- [dataflow DEAD_STORE] `gui/browser_ui.c:2081` `first` `dg`: `dg` assigned at line 2081 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5045` `flow_text` `space_w`: `space_w` assigned at line 5045 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5047` `flow_text` `i`: `i` assigned at line 5047 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:6119` `table` `parent`: `parent` assigned at line 6119 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:6120` `table` `seen`: `seen` assigned at line 6120 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:6122` `table` `j`: `j` assigned at line 6122 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:6295` `measure_item_w_at` `atom_line_max`: `atom_line_max` assigned at line 6295 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:6316` `measure_item_w_at` `rw`: `rw` assigned at line 6316 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:6527` `nested_cont_basis` `total`: `total` assigned at line 6527 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:6528` `nested_cont_basis` `n_items`: `n_items` assigned at line 6528 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:7802` `descriptor` `sb`: `sb` assigned at line 7802 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:7803` `descriptor` `sr`: `sr` assigned at line 7803 but never read afterwards.

## Open Questions

- Why do 39 file(s) lack file-level docs (e.g. `fuzz/fuzz_browser.c`)? What purpose do they serve?
- What would break if the most connected file in include: browser_ui changed?
- Should include: browser_ui be split, given cohesion 0.52?

## Sources

- `fuzz/fuzz_box_blur.c`
- `fuzz/fuzz_browser.c`
- `fuzz/fuzz_doc_title.c`
- `fuzz/fuzz_exact_key.c`
- `fuzz/fuzz_find_text.c`
- `fuzz/fuzz_frame_broker.c`
- `fuzz/fuzz_group_index.c`
- `fuzz/fuzz_mask_cache.c`
- `fuzz/fuzz_nav_token.c`
- `fuzz/fuzz_smooth_scroll.c`
- `gui/browser_ui.c`
- `include/block_flow.h`
- `include/box_blur.h`
- `include/browser.h`
- `include/doc_title.h`
- `include/exact_key.h`
- `include/find_text.h`
- `include/form.h`
- `include/frame_broker.h`
- `include/frame_clock.h`
- *... and 45 more*
