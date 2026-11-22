# include: browser_ui

*Community 1 | 62 files | cohesion 0.58*

## Definition

This community groups 62 file(s) rooted at `include` with dominant language c (cohesion 0.58). Central symbols: `AA_QUEUE_MAX`, `ABSENT`, `ALIVE`, `BALANCE_MAX_LINES`, `BB_BOX_MAX`, `BB_MAX_PIXELS`, `BROWSER_CLOSED_MAX`, `BROWSER_STATUS_DURATION_MS`. Core file: `gui/browser_ui.c` (699 symbols). Documented purpose: block_flow (bf_) -- vertical margin collapsing for block-level boxes..

## Files

### `include` (21 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/block_flow.h` | h | utility | 4 | yes |
| `include/box_blur.h` | h | utility | 5 | yes |
| `include/browser.h` | h | utility | 26 | no |
| `include/download.h` | h | utility | 9 | no |
| `include/exact_key.h` | h | utility | 9 | yes |
| `include/find_text.h` | h | utility | 18 | no |

### `tests` (20 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_block_flow.c` | c | testing | 8 | no |
| `tests/test_box_blur.c` | c | testing | 15 | no |
| `tests/test_browser.c` | c | testing | 27 | no |
| `tests/test_download.c` | c | testing | 21 | no |
| `tests/test_exact_key.c` | c | testing | 6 | no |
| `tests/test_find_text.c` | c | testing | 12 | yes |

### `src` (18 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/block_flow.c` | c | utility | 4 | yes |
| `src/box_blur.c` | c | utility | 9 | no |
| `src/browser.c` | c | utility | 49 | no |
| `src/download.c` | c | utility | 12 | no |
| `src/exact_key.c` | c | utility | 6 | no |

### `gui` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui.c` | c | presentation | 699 | no |
| `gui/freedom_view.c` | c | presentation | 2 | no |
| `gui/ui_render.c` | c | presentation | 29 | no |

*... and 42 more files in this community.*


## Key Symbols

- `_GNU_SOURCE` (macro, `gui/browser_ui.c:12`) `#define _GNU_SOURCE`
- `UI_TOOLBAR_H` (macro, `gui/browser_ui.c:102`) `#define UI_TOOLBAR_H`
- `UI_MARGIN` (macro, `gui/browser_ui.c:103`) `#define UI_MARGIN`
- `UI_BTN_LEFT` (macro, `gui/browser_ui.c:104`) `#define UI_BTN_LEFT`
- `UI_LIST_INDENT` (macro, `gui/browser_ui.c:108`) `#define UI_LIST_INDENT`
- `UI_SCROLLBAR_W` (macro, `gui/browser_ui.c:113`) `#define UI_SCROLLBAR_W`
- `UI_SCROLLBAR_MIN` (macro, `gui/browser_ui.c:114`) `#define UI_SCROLLBAR_MIN`
- `UI_SCROLLBAR_PAD` (macro, `gui/browser_ui.c:115`) `#define UI_SCROLLBAR_PAD`
- `UI_RESIZE_MARGIN` (macro, `gui/browser_ui.c:119`) `#define UI_RESIZE_MARGIN`
- `UI_MENU_W` (macro, `gui/browser_ui.c:124`) `#define UI_MENU_W`
- `UI_MENU_ITEM_H` (macro, `gui/browser_ui.c:125`) `#define UI_MENU_ITEM_H`
- `UI_MENU_PAD` (macro, `gui/browser_ui.c:126`) `#define UI_MENU_PAD`
- `UI_MENU_RADIUS` (macro, `gui/browser_ui.c:127`) `#define UI_MENU_RADIUS`
- `UI_CHECK_SZ` (macro, `gui/browser_ui.c:128`) `#define UI_CHECK_SZ`
- `UI_MENU_LABEL_H` (macro, `gui/browser_ui.c:129`) `#define UI_MENU_LABEL_H`
- `UI_MENU_INPUT_H` (macro, `gui/browser_ui.c:130`) `#define UI_MENU_INPUT_H`
- `UI_HAMBURGER_W` (macro, `gui/browser_ui.c:131`) `#define UI_HAMBURGER_W`
- `UI_HAMBURGER_GAP` (macro, `gui/browser_ui.c:132`) `#define UI_HAMBURGER_GAP`
- `UI_CURSOR_SIZE` (macro, `gui/browser_ui.c:133`) `#define UI_CURSOR_SIZE`
- `UI_TOAST_PAD` (macro, `gui/browser_ui.c:134`) `#define UI_TOAST_PAD`
- `OMNI_MAX_SUGG` (macro, `gui/browser_ui.c:135`) `#define OMNI_MAX_SUGG`
- `UI_OMNI_ROW_H` (macro, `gui/browser_ui.c:136`) `#define UI_OMNI_ROW_H`
- `UI_TWO_PI` (macro, `gui/browser_ui.c:137`) `#define UI_TWO_PI`
- `UI_INPUT_PAD` (macro, `gui/browser_ui.c:141`) `#define UI_INPUT_PAD`
- `UI_CONTROL_FONT` (macro, `gui/browser_ui.c:144`) `#define UI_CONTROL_FONT`
- `UI_INPUT_MEASURE_W` (macro, `gui/browser_ui.c:150`) `#define UI_INPUT_MEASURE_W`
- `UI_INPUT_WIDTH` (macro, `gui/browser_ui.c:151`) `#define UI_INPUT_WIDTH`
- `UI_BUTTON_HPAD` (macro, `gui/browser_ui.c:152`) `#define UI_BUTTON_HPAD`
- `UI_FORM_FIELDS_MAX` (macro, `gui/browser_ui.c:153`) `#define UI_FORM_FIELDS_MAX`
- `UI_UNDERLINE_OFFSET` (macro, `gui/browser_ui.c:158`) `#define UI_UNDERLINE_OFFSET`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 68
- Cross-boundary resolved imports (EXTRACTED): 49

## Connections

- [EXTRACTED] depends_on community 1 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/box_style.h.
- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/compositor.h.
- [EXTRACTED] depends_on community 1 <-> 7 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/svg_paint.h.
- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/freebug.h.
- [EXTRACTED] depends_on community 1 <-> 5 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/identity.h.
- [EXTRACTED] depends_on community 1 <-> 9 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefetch.h.
- [EXTRACTED] depends_on community 1 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/tab.h.
- [EXTRACTED] depends_on community 1 <-> 6 (strength 0.9): Extracted import edge crosses communities: include/profile.h imports include/local_store.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [layer strict] `tests/test_table_layout.c` (testing) -> `include/table_layout.h` (presentation)
- [layer strict] `tests/test_ui.c` (testing) -> `include/ui.h` (presentation)
- [dataflow UNCHECKED_ALLOC] `gui/browser_ui.c:1742` `gui_subresource_fetch` `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- [dataflow DEAD_STORE] `gui/browser_ui.c:1908` `first` `dg`: `dg` assigned at line 1908 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:4741` `flow_text` `space_w`: `space_w` assigned at line 4741 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:4743` `flow_text` `i`: `i` assigned at line 4743 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5815` `table` `parent`: `parent` assigned at line 5815 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5816` `table` `seen`: `seen` assigned at line 5816 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5818` `table` `j`: `j` assigned at line 5818 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5972` `measure_item_w_at` `atom_line_max`: `atom_line_max` assigned at line 5972 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5990` `measure_item_w_at` `rw`: `rw` assigned at line 5990 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:6201` `nested_cont_basis` `total`: `total` assigned at line 6201 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:6202` `nested_cont_basis` `n_items`: `n_items` assigned at line 6202 but never read afterwards.

## Open Questions

- Why do 51 file(s) lack file-level docs (e.g. `gui/browser_ui.c`)? What purpose do they serve?
- What would break if the most connected file in include: browser_ui changed?
- Should include: browser_ui be split, given cohesion 0.58?

## Sources

- `gui/browser_ui.c`
- `gui/freedom_view.c`
- `gui/ui_render.c`
- `include/block_flow.h`
- `include/box_blur.h`
- `include/browser.h`
- `include/download.h`
- `include/exact_key.h`
- `include/find_text.h`
- `include/form.h`
- `include/frame_clock.h`
- `include/hostedit.h`
- `include/interp.h`
- `include/lazy_load.h`
- `include/mask_cache.h`
- `include/pdf_export.h`
- `include/prefs.h`
- `include/profile.h`
- `include/shm_slots.h`
- `include/table_layout.h`
- *... and 42 more*
