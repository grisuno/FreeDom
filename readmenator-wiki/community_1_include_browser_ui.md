# include: browser_ui

*Community 1 | 45 files | cohesion 0.52*

## Definition

This community groups 45 file(s) rooted at `tests` with dominant language c (cohesion 0.52). Central symbols: `ABSENT`, `ALIVE`, `BALANCE_MAX_LINES`, `BB_MAX_PIXELS`, `BUI_CONIC_SLICES`, `DL_ERR_OVERFLOW`, `DL_FALLBACK_NAME`, `DL_MAX_BYTES`. Core file: `gui/browser_ui.c` (633 symbols). Documented purpose: block_flow (bf_) -- vertical margin collapsing for block-level boxes..

## Files

### `tests` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_block_flow.c` | c | testing | 8 | no |
| `tests/test_box_blur.c` | c | testing | 11 | no |
| `tests/test_download.c` | c | testing | 21 | no |
| `tests/test_form.c` | c | testing | 20 | no |
| `tests/test_frame_clock.c` | c | testing | 4 | no |
| `tests/test_freedom.c` | c | testing | 111 | no |
| `tests/test_hostedit.c` | c | testing | 11 | no |

### `include` (15 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/block_flow.h` | h | utility | 4 | yes |
| `include/box_blur.h` | h | utility | 5 | yes |
| `include/download.h` | h | utility | 9 | no |
| `include/form.h` | h | utility | 12 | no |
| `include/frame_clock.h` | h | utility | 7 | no |
| `include/hostedit.h` | h | utility | 5 | no |

### `src` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/block_flow.c` | c | utility | 4 | yes |
| `src/box_blur.c` | c | utility | 5 | no |
| `src/download.c` | c | utility | 12 | no |
| `src/form.c` | c | utility | 8 | no |
| `src/frame_clock.c` | c | utility | 4 | no |
| `src/hostedit.c` | c | utility | 13 | no |

### `gui` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/browser_ui.c` | c | presentation | 633 | no |

*... and 25 more files in this community.*


## Key Symbols

- `_GNU_SOURCE` (macro, `gui/browser_ui.c:12`) `#define _GNU_SOURCE`
- `UI_TOOLBAR_H` (macro, `gui/browser_ui.c:94`) `#define UI_TOOLBAR_H`
- `UI_TITLEBAR_H` (macro, `gui/browser_ui.c:95`) `#define UI_TITLEBAR_H`
- `UI_TABBAR_H` (macro, `gui/browser_ui.c:96`) `#define UI_TABBAR_H`
- `UI_TAB_MIN_W` (macro, `gui/browser_ui.c:97`) `#define UI_TAB_MIN_W`
- `UI_TAB_MAX_W` (macro, `gui/browser_ui.c:98`) `#define UI_TAB_MAX_W`
- `UI_TAB_NEW_W` (macro, `gui/browser_ui.c:99`) `#define UI_TAB_NEW_W`
- `UI_TAB_CLOSE_W` (macro, `gui/browser_ui.c:100`) `#define UI_TAB_CLOSE_W`
- `UI_BTN_W` (macro, `gui/browser_ui.c:101`) `#define UI_BTN_W`
- `UI_WIN_BTN_W` (macro, `gui/browser_ui.c:102`) `#define UI_WIN_BTN_W`
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
- `UI_CHECK_SZ` (macro, `gui/browser_ui.c:127`) `#define UI_CHECK_SZ`
- `UI_MENU_LABEL_H` (macro, `gui/browser_ui.c:128`) `#define UI_MENU_LABEL_H`
- `UI_MENU_INPUT_H` (macro, `gui/browser_ui.c:129`) `#define UI_MENU_INPUT_H`
- `UI_HAMBURGER_W` (macro, `gui/browser_ui.c:130`) `#define UI_HAMBURGER_W`
- `UI_HAMBURGER_GAP` (macro, `gui/browser_ui.c:131`) `#define UI_HAMBURGER_GAP`
- `UI_CURSOR_SIZE` (macro, `gui/browser_ui.c:132`) `#define UI_CURSOR_SIZE`
- `UI_TOAST_PAD` (macro, `gui/browser_ui.c:133`) `#define UI_TOAST_PAD`
- `OMNI_MAX_SUGG` (macro, `gui/browser_ui.c:134`) `#define OMNI_MAX_SUGG`
- `UI_OMNI_ROW_H` (macro, `gui/browser_ui.c:135`) `#define UI_OMNI_ROW_H`
- `UI_TWO_PI` (macro, `gui/browser_ui.c:136`) `#define UI_TWO_PI`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 49
- Cross-boundary resolved imports (EXTRACTED): 45

## Connections

- [EXTRACTED] depends_on community 1 <-> 5 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/browser.h.
- [EXTRACTED] depends_on community 1 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/box_style.h.
- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/compositor.h.
- [EXTRACTED] depends_on community 1 <-> 7 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/svg_paint.h.
- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/freebug.h.
- [EXTRACTED] depends_on community 1 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/identity.h.
- [EXTRACTED] depends_on community 1 <-> 9 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefetch.h.
- [EXTRACTED] depends_on community 1 <-> 6 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/cached_fetch.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [dataflow UNCHECKED_ALLOC] `gui/browser_ui.c:1557` `gui_subresource_fetch` `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- [dataflow DEAD_STORE] `gui/browser_ui.c:1721` `first` `dg`: `dg` assigned at line 1721 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:4424` `flow_text` `space_w`: `space_w` assigned at line 4424 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:4426` `flow_text` `i`: `i` assigned at line 4426 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5460` `table` `parent`: `parent` assigned at line 5460 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5461` `table` `seen`: `seen` assigned at line 5461 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5463` `table` `j`: `j` assigned at line 5463 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5763` `nested_cont_basis` `total`: `total` assigned at line 5763 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:5764` `nested_cont_basis` `n_items`: `n_items` assigned at line 5764 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:6836` `builds` `sl`: `sl` assigned at line 6836 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:8508` `defer_flush` `fw`: `fw` assigned at line 8508 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:8509` `defer_flush` `ngroups`: `ngroups` assigned at line 8509 but never read afterwards.
- [dataflow DEAD_STORE] `gui/browser_ui.c:10621` `button_box_width` `cx`: `cx` assigned at line 10621 but never read afterwards.

## Open Questions

- Why do 42 file(s) lack file-level docs (e.g. `gui/browser_ui.c`)? What purpose do they serve?
- What would break if the most connected file in include: browser_ui changed?
- Should include: browser_ui be split, given cohesion 0.52?

## Sources

- `gui/browser_ui.c`
- `include/block_flow.h`
- `include/box_blur.h`
- `include/download.h`
- `include/form.h`
- `include/frame_clock.h`
- `include/hostedit.h`
- `include/image_decode.h`
- `include/interp.h`
- `include/pdf_export.h`
- `include/prefs.h`
- `include/profile.h`
- `include/shm_slots.h`
- `include/textfield.h`
- `include/wl_guard.h`
- `include/zoom.h`
- `src/block_flow.c`
- `src/box_blur.c`
- `src/download.c`
- `src/form.c`
- *... and 25 more*
