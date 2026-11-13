# include: browser_ui

*Community 2 | 47 files | cohesion 0.52*

## Definition

This community groups 47 file(s) rooted at `include` with dominant language c (cohesion 0.52). Central symbols: `AA_QUEUE_MAX`, `ABSENT`, `ALIVE`, `BALANCE_MAX_LINES`, `BB_MAX_PIXELS`, `BUI_CONIC_SLICES`, `DL_ERR_OVERFLOW`, `DL_FALLBACK_NAME`. Core file: `gui/browser_ui.c` (663 symbols). Documented purpose: block_flow (bf_) -- vertical margin collapsing for block-level boxes..

## Files

### `include` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/block_flow.h` | h | utility | 4 | yes |
| `include/box_blur.h` | h | utility | 5 | yes |
| `include/download.h` | h | utility | 9 | no |
| `include/form.h` | h | utility | 12 | no |
| `include/frame_clock.h` | h | utility | 7 | no |
| `include/hostedit.h` | h | utility | 7 | no |

### `tests` (15 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_block_flow.c` | c | testing | 8 | no |
| `tests/test_box_blur.c` | c | testing | 11 | no |
| `tests/test_download.c` | c | testing | 21 | no |
| `tests/test_form.c` | c | testing | 20 | no |
| `tests/test_frame_clock.c` | c | testing | 4 | no |
| `tests/test_hostedit.c` | c | testing | 12 | no |

### `src` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/block_flow.c` | c | utility | 4 | yes |
| `src/box_blur.c` | c | utility | 5 | no |
| `src/download.c` | c | utility | 12 | no |
| `src/form.c` | c | utility | 8 | no |
| `src/frame_clock.c` | c | utility | 4 | no |

### `gui` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui.c` | c | presentation | 663 | no |
| `gui/freedom_view.c` | c | presentation | 2 | no |
| `gui/ui_render.c` | c | presentation | 29 | no |

*... and 27 more files in this community.*


## Key Symbols

- `_GNU_SOURCE` (macro, `gui/browser_ui.c:12`) `#define _GNU_SOURCE`
- `UI_TOOLBAR_H` (macro, `gui/browser_ui.c:96`) `#define UI_TOOLBAR_H`
- `UI_TITLEBAR_H` (macro, `gui/browser_ui.c:97`) `#define UI_TITLEBAR_H`
- `UI_TABBAR_H` (macro, `gui/browser_ui.c:98`) `#define UI_TABBAR_H`
- `UI_TAB_MIN_W` (macro, `gui/browser_ui.c:99`) `#define UI_TAB_MIN_W`
- `UI_TAB_MAX_W` (macro, `gui/browser_ui.c:100`) `#define UI_TAB_MAX_W`
- `UI_TAB_NEW_W` (macro, `gui/browser_ui.c:101`) `#define UI_TAB_NEW_W`
- `UI_TAB_CLOSE_W` (macro, `gui/browser_ui.c:102`) `#define UI_TAB_CLOSE_W`
- `UI_BTN_W` (macro, `gui/browser_ui.c:103`) `#define UI_BTN_W`
- `UI_WIN_BTN_W` (macro, `gui/browser_ui.c:104`) `#define UI_WIN_BTN_W`
- `UI_MARGIN` (macro, `gui/browser_ui.c:105`) `#define UI_MARGIN`
- `UI_BTN_LEFT` (macro, `gui/browser_ui.c:106`) `#define UI_BTN_LEFT`
- `UI_LIST_INDENT` (macro, `gui/browser_ui.c:110`) `#define UI_LIST_INDENT`
- `UI_SCROLLBAR_W` (macro, `gui/browser_ui.c:115`) `#define UI_SCROLLBAR_W`
- `UI_SCROLLBAR_MIN` (macro, `gui/browser_ui.c:116`) `#define UI_SCROLLBAR_MIN`
- `UI_SCROLLBAR_PAD` (macro, `gui/browser_ui.c:117`) `#define UI_SCROLLBAR_PAD`
- `UI_RESIZE_MARGIN` (macro, `gui/browser_ui.c:121`) `#define UI_RESIZE_MARGIN`
- `UI_MENU_W` (macro, `gui/browser_ui.c:126`) `#define UI_MENU_W`
- `UI_MENU_ITEM_H` (macro, `gui/browser_ui.c:127`) `#define UI_MENU_ITEM_H`
- `UI_MENU_PAD` (macro, `gui/browser_ui.c:128`) `#define UI_MENU_PAD`
- `UI_CHECK_SZ` (macro, `gui/browser_ui.c:129`) `#define UI_CHECK_SZ`
- `UI_MENU_LABEL_H` (macro, `gui/browser_ui.c:130`) `#define UI_MENU_LABEL_H`
- `UI_MENU_INPUT_H` (macro, `gui/browser_ui.c:131`) `#define UI_MENU_INPUT_H`
- `UI_HAMBURGER_W` (macro, `gui/browser_ui.c:132`) `#define UI_HAMBURGER_W`
- `UI_HAMBURGER_GAP` (macro, `gui/browser_ui.c:133`) `#define UI_HAMBURGER_GAP`
- `UI_CURSOR_SIZE` (macro, `gui/browser_ui.c:134`) `#define UI_CURSOR_SIZE`
- `UI_TOAST_PAD` (macro, `gui/browser_ui.c:135`) `#define UI_TOAST_PAD`
- `OMNI_MAX_SUGG` (macro, `gui/browser_ui.c:136`) `#define OMNI_MAX_SUGG`
- `UI_OMNI_ROW_H` (macro, `gui/browser_ui.c:137`) `#define UI_OMNI_ROW_H`
- `UI_TWO_PI` (macro, `gui/browser_ui.c:138`) `#define UI_TWO_PI`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 53
- Cross-boundary resolved imports (EXTRACTED): 49

## Connections

- [EXTRACTED] depends_on community 2 <-> 6 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/browser.h.
- [EXTRACTED] depends_on community 2 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/box_style.h.
- [EXTRACTED] depends_on community 2 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/compositor.h.
- [EXTRACTED] depends_on community 2 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/svg_paint.h.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 2 <-> 1 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/freebug.h.
- [EXTRACTED] depends_on community 2 <-> 5 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/identity.h.
- [EXTRACTED] depends_on community 2 <-> 10 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefetch.h.
- [EXTRACTED] depends_on community 2 <-> 9 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/tab.h.
- [EXTRACTED] depends_on community 2 <-> 7 (strength 0.9): Extracted import edge crosses communities: include/profile.h imports include/local_store.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [layer strict] `tests/test_ui.c` (testing) -> `include/ui.h` (presentation)
- [dataflow UNCHECKED_ALLOC] `gui/browser_ui.c:1691` `gui_subresource_fetch` `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- [dataflow DEAD_STORE] `gui/browser_ui.c:1857` `first` `dg`: `dg` assigned at line 1857 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:4674` `flow_text` `space_w`: `space_w` assigned at line 4674 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:4676` `flow_text` `i`: `i` assigned at line 4676 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5713` `table` `parent`: `parent` assigned at line 5713 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5714` `table` `seen`: `seen` assigned at line 5714 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5716` `table` `j`: `j` assigned at line 5716 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5851` `measure_item_w_at` `repl_max`: `repl_max` assigned at line 5851 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5852` `measure_item_w_at` `atom_line_max`: `atom_line_max` assigned at line 5852 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5870` `measure_item_w_at` `rw`: `rw` assigned at line 5870 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:6050` `nested_cont_basis` `total`: `total` assigned at line 6050 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:6051` `nested_cont_basis` `n_items`: `n_items` assigned at line 6051 but never read afterwards.

## Open Questions

- Why do 44 file(s) lack file-level docs (e.g. `gui/browser_ui.c`)? What purpose do they serve?
- What would break if the most connected file in include: browser_ui changed?
- Should include: browser_ui be split, given cohesion 0.52?

## Sources

- `gui/browser_ui.c`
- `gui/freedom_view.c`
- `gui/ui_render.c`
- `include/block_flow.h`
- `include/box_blur.h`
- `include/download.h`
- `include/form.h`
- `include/frame_clock.h`
- `include/hostedit.h`
- `include/interp.h`
- `include/lazy_load.h`
- `include/pdf_export.h`
- `include/prefs.h`
- `include/profile.h`
- `include/shm_slots.h`
- `include/textfield.h`
- `include/ui.h`
- `include/wl_guard.h`
- `include/zoom.h`
- `src/block_flow.c`
- *... and 27 more*
