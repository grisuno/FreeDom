# include: page_view

*Community 3 | 31 files | cohesion 0.51*

## Definition

This community groups 31 file(s) rooted at `include` with dominant language c (cohesion 0.51). Central symbols: `BLOCK`, `BLOCKED`, `BT_ALIGN_CENTER`, `BT_ALIGN_END`, `BT_ALIGN_START`, `BT_ALIGN_STRETCH`, `BT_LEN_AUTO`, `BT_MAUTO_LEFT`. Core file: `src/page_view.c` (222 symbols).

## Files

### `include` (10 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/box_style.h` | h | utility | 25 | no |
| `include/box_tree.h` | h | utility | 32 | no |
| `include/dom_debug.h` | h | utility | 4 | no |
| `include/flex_layout.h` | h | presentation | 35 | no |
| `include/js_policy.h` | h | business_logic | 7 | no |
| `include/page_view.h` | h | presentation | 72 | no |
| `include/perf_trace.h` | h | utility | 17 | no |

### `src` (10 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/box_style.c` | c | utility | 41 | no |
| `src/box_tree.c` | c | utility | 22 | no |
| `src/dom_debug.c` | c | utility | 24 | no |
| `src/flex_layout.c` | c | presentation | 24 | no |
| `src/freedom.c` | c | utility | 39 | no |
| `src/js_policy.c` | c | business_logic | 6 | no |

### `tests` (10 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_box_style.c` | c | testing | 42 | no |
| `tests/test_box_tree.c` | c | testing | 57 | no |
| `tests/test_dom_debug.c` | c | testing | 11 | no |
| `tests/test_flex_layout.c` | c | testing | 67 | no |
| `tests/test_js_policy.c` | c | testing | 5 | no |
| `tests/test_page_view.c` | c | testing | 181 | no |

### `fuzz` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_dom_debug.c` | c | utility | 1 | no |

*... and 11 more files in this community.*


## Key Symbols

- `pass` (function, `fuzz/fuzz_dom_debug.c:8`) `* the measure pass (cap 0) must agree with the would-write return value.  *  * B`
- `FREEDOM_BOX_STYLE_H` (macro, `include/box_style.h:2`) `#define FREEDOM_BOX_STYLE_H`
- `BX_TAG_NAME_MAX` (macro, `include/box_style.h:33`) `#define BX_TAG_NAME_MAX`
- `bx_display` (enum, `include/box_style.h:35`)
- `bx_edges` (struct, `include/box_style.h:46`) - anything longer fails closed instead of truncating into a wrong match. #define BX_TAG_NAME_MAX 32u t
- `left` (type_alias, `include/box_style.h:46`) `typedef struct bx_edges { double top, right, bottom, left;` - anything longer fails closed instead of truncating into a wrong match. #define BX_TAG_NAME_MAX 32u t
- `display` (type_alias, `include/box_style.h:49`) `typedef struct bx_box { bx_display display;`
- `bx_box` (struct, `include/box_style.h:50`)
- `bx_status` (enum, `include/box_style.h:56`)
- `bx_hplace` (struct, `include/box_style.h:63`) - typedef struct bx_box { bx_display display; bx_edges   margin; bx_edges   padding; } bx_box; typedef
- `x_off` (type_alias, `include/box_style.h:63`) `typedef struct bx_hplace { double x_off;` - typedef struct bx_box { bx_display display; bx_edges   margin; bx_edges   padding; } bx_box; typedef
- `bx_ua_tag` (enum, `include/box_style.h:84`) - Compact, stable identity of a block's SOURCE element, just wide enough to recover its user-agent box
- `box` (function, `include/box_style.h:115`) `* in_list nonzero when the block sits inside a list item: it then takes * the <l`
- `bx_table_role` (enum, `include/box_style.h:127`) - The role an element plays in a table (CSS 2.1 17.2). BX_TROLE_COLUMN generates no * box of its own;
- `BX_TROLE_NONE` (function, `include/box_style.h:144`) `* BX_TROLE_NONE (an unrecognised element joins no table -- fail closed). */ bx_t`
- `bx_display_name` (function, `include/box_style.h:156`) `const char *bx_display_name(bx_display d);` - Stable, short English name of a display type for structured/agent output. Never * NULL; an unknown e
- `bx_width_cap` (function, `include/box_style.h:172`) `double bx_width_cap(int w_px, int w_pct, double avail_w);` - Effective width cap combining the px cap (w_px, 0 = none) with a symbolic per-mille cap (w_pct, 0 =
- `bx_width_cap2` (function, `include/box_style.h:177`) `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w)` - The used width cap of an element: the tighter of its `width` (w_px, w_pct) and its `max-width` (mw_p
- `bx_replaced_box` (function, `include/box_style.h:196`) `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den, double` - CSS Sizing 4 section 4: when one axis is definite and an aspect-ratio is present, the ratio supplies
- `bx_border_box_h` (function, `include/box_style.h:210`) `double bx_border_box_h(double declared_h, int border_box, double pad_t, double p` - Border-box height for a DECLARED height under box-sizing (CSS 2.1 10.6.3, CSS Box Sizing 3 section 4
- `page` (function, `include/box_style.h:214`) `* instead of letting it extend the page (CSS 2.1 section 10.7 + 11.1.1). That *`
- `bx_lp_px` (function, `include/box_style.h:236`) `double bx_lp_px(int px_val, int pct_pm, double basis);` - half plus pct_pm per-mille of `basis`. This is the ONLY place the engine turns a percentage into pix
- `bx_content_cap` (function, `include/box_style.h:244`) `double bx_content_cap(double width_cap, int border_box, double pad_l, double pad` - Content-width cap adjusted for box-sizing (2026-07-11). With border_box set, the declared width incl
- `bx_bg_layer` (struct, `include/box_style.h:267`) - the explicit form, each component is a px value (CSS_LEN_AUTO = auto, CSS_LEN_UNSET = not declared,
- `nat_h` (type_alias, `include/box_style.h:267`) `typedef struct bx_bg_layer { double nat_w, nat_h;` - the explicit form, each component is a px value (CSS_LEN_AUTO = auto, CSS_LEN_UNSET = not declared,
- `bx_background_layer` (function, `include/box_style.h:277`) `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h, dou`
- `FREEDOM_BOX_TREE_H` (macro, `include/box_tree.h:2`) `#define FREEDOM_BOX_TREE_H`
- `closed` (function, `include/box_tree.h:34`) `* fails closed (BT_ERR_RANGE) instead of overflowing the stack. */ #define BT_MA`
- `BT_MAX_DEPTH` (macro, `include/box_tree.h:35`) `#define BT_MAX_DEPTH`
- `BT_MAX_CHILDREN` (macro, `include/box_tree.h:36`) `#define BT_MAX_CHILDREN`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 58
- Cross-boundary resolved imports (EXTRACTED): 55

## Connections

- [EXTRACTED] depends_on community 3 <-> 0 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_dom_debug.c imports include/html_parse.h.
- [EXTRACTED] depends_on community 6 <-> 3 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_page_view.c imports include/page_view.h.
- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/box_style.h.
- [EXTRACTED] depends_on community 3 <-> 2 (strength 0.9): Extracted import edge crosses communities: include/box_style.h imports include/css.h.
- [EXTRACTED] depends_on community 3 <-> 4 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/request_policy.h.
- [EXTRACTED] depends_on community 3 <-> 7 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/secure_fetch.h.

## Risks

- [layer strict] `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access)
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
- [layer strict] `tests/test_render_doc.c` (testing) -> `include/render_policy.h` (presentation)
- [layer strict] `tests/test_render_policy.c` (testing) -> `include/render_policy.h` (presentation)
- [dataflow UNINIT_USE] `src/box_tree.c:231` `layout_grid` `col_x`: `col_x` may be read before initialization (declared line 228).

## Open Questions

- Why do 31 file(s) lack file-level docs (e.g. `fuzz/fuzz_dom_debug.c`)? What purpose do they serve?
- What would break if the most connected file in include: page_view changed?
- Should include: page_view be split, given cohesion 0.51?

## Sources

- `fuzz/fuzz_dom_debug.c`
- `include/box_style.h`
- `include/box_tree.h`
- `include/dom_debug.h`
- `include/flex_layout.h`
- `include/js_policy.h`
- `include/page_view.h`
- `include/perf_trace.h`
- `include/render_doc.h`
- `include/render_policy.h`
- `include/webcaps.h`
- `src/box_style.c`
- `src/box_tree.c`
- `src/dom_debug.c`
- `src/flex_layout.c`
- `src/freedom.c`
- `src/js_policy.c`
- `src/page_view.c`
- `src/perf_trace.c`
- `src/render_doc.c`
- *... and 11 more*
