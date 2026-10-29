# include: page_view

*Community 3 | 36 files | cohesion 0.53*

## Definition

This community groups 36 file(s) rooted at `tests` with dominant language c (cohesion 0.53). Central symbols: `BLOCK`, `BT_ALIGN_CENTER`, `BT_ALIGN_END`, `BT_ALIGN_START`, `BT_ALIGN_STRETCH`, `BT_LEN_AUTO`, `BT_MAUTO_LEFT`, `BT_MAUTO_RIGHT`. Core file: `src/page_view.c` (261 symbols). Documented purpose: Case mapping for text-transform and synthesized small caps (spec/text_case.md). Pure: no I/O, no state, no allocation..

## Files

### `tests` (14 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_box_style.c` | c | testing | 49 | no |
| `tests/test_box_tree.c` | c | testing | 69 | no |
| `tests/test_compositor.c` | c | testing | 21 | no |
| `tests/test_css_computed.c` | c | testing | 9 | no |
| `tests/test_css_drops.c` | c | testing | 25 | yes |
| `tests/test_css_gradient.c` | c | testing | 13 | no |
| `tests/test_css_length.c` | c | testing | 25 | no |

### `include` (12 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/box_style.h` | h | utility | 31 | no |
| `include/box_tree.h` | h | utility | 34 | no |
| `include/compositor.h` | h | utility | 9 | no |
| `include/css.h` | h | utility | 140 | no |
| `include/css_chain.h` | h | utility | 12 | no |
| `include/css_computed.h` | h | utility | 6 | no |
| `include/dom_debug.h` | h | utility | 4 | no |

### `src` (10 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/box_style.c` | c | utility | 48 | no |
| `src/box_tree.c` | c | utility | 25 | no |
| `src/compositor.c` | c | utility | 5 | no |
| `src/css_computed.c` | c | utility | 45 | no |
| `src/css_length.c` | c | utility | 18 | no |
| `src/dom_debug.c` | c | utility | 24 | no |

*... and 16 more files in this community.*


## Key Symbols

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
- `bx_width_cap` (function, `include/box_style.h:182`) `double bx_width_cap(int w_px, int w_pct, double avail_w);` - Effective width cap combining the px cap (w_px, 0 = none) with a symbolic per-mille cap (w_pct, 0 =
- `bx_width_cap2` (function, `include/box_style.h:187`) `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w)` - The used width cap of an element: the tighter of its `width` (w_px, w_pct) and its `max-width` (mw_p
- `bx_replaced_box` (function, `include/box_style.h:206`) `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den, double` - CSS Sizing 4 section 4: when one axis is definite and an aspect-ratio is present, the ratio supplies
- `bx_border_box_h` (function, `include/box_style.h:220`) `double bx_border_box_h(double declared_h, int border_box, double pad_t, double p` - Border-box height for a DECLARED height under box-sizing (CSS 2.1 10.6.3, CSS Box Sizing 3 section 4
- `block` (function, `include/box_style.h:226`) `* indefinite containing block (cb_h < 0) the value behaves as auto: -1. * Withou`
- `bx_line_height_px` (function, `include/box_style.h:239`) `double bx_line_height_px(int line_scale, double font_px);` - The used line-height in px of text at font_px for a css line_scale value (spec/box_style.md 4c): 0 =
- `bx_definite_content_h` (function, `include/box_style.h:241`) `double bx_definite_content_h(double h, double min_h, double max_h, int border_bo`
- `page` (function, `include/box_style.h:245`) `* instead of letting it extend the page (CSS 2.1 section 10.7 + 11.1.1). That *`
- `bx_lp_px` (function, `include/box_style.h:267`) `double bx_lp_px(int px_val, int pct_pm, double basis);` - half plus pct_pm per-mille of `basis`. This is the ONLY place the engine turns a percentage into pix
- `bx_content_cap` (function, `include/box_style.h:275`) `double bx_content_cap(double width_cap, int border_box, double pad_l, double pad` - Content-width cap adjusted for box-sizing (2026-07-11). With border_box set, the declared width incl
- `bx_border_span` (function, `include/box_style.h:286`) `double bx_border_span(double width_cap, int border_box, double pad_l, double pad` - The border-inclusive span the painter lays a box out with (its content plus left/right border; paddi
- `bx_flex_max_clamp` (function, `include/box_style.h:292`) `double bx_flex_max_clamp(double outer_basis, double mw_cap, int border_box, doub` - Flexbox 1 9.2.3: an item's OUTER flex base size clamped by its max-width (the hypothetical main size
- `bx_flex_min_clamp` (function, `include/box_style.h:298`) `double bx_flex_min_clamp(double outer_basis, double min_w, int border_box, doubl` - The min-width half of the same clamp (Flexbox 9.2.3): an outer base below the item's min-width (conv
- `bx_bg_layer` (struct, `include/box_style.h:321`) - the explicit form, each component is a px value (CSS_LEN_AUTO = auto, CSS_LEN_UNSET = not declared,
- `nat_h` (type_alias, `include/box_style.h:321`) `typedef struct bx_bg_layer { double nat_w, nat_h;` - the explicit form, each component is a px value (CSS_LEN_AUTO = auto, CSS_LEN_UNSET = not declared,

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 69
- Cross-boundary resolved imports (EXTRACTED): 60

## Connections

- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/box_style.h.
- [EXTRACTED] depends_on community 3 <-> 4 (strength 0.9): Extracted import edge crosses communities: include/css.h imports include/css_color.h.
- [EXTRACTED] depends_on community 8 <-> 3 (strength 0.9): Extracted import edge crosses communities: include/frame_host.h imports include/page_view.h.
- [EXTRACTED] depends_on community 3 <-> 1 (strength 0.9): Extracted import edge crosses communities: include/page_view.h imports include/dom.h.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: include/webcaps.h imports include/render_policy.h.

## Risks

- [layer strict] `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `tests/test_box_tree.c` (testing) -> `include/page_view.h` (presentation)
- [layer strict] `tests/test_css.c` (testing) -> `include/flex_layout.h` (presentation)
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

## Open Questions

- Why do 33 file(s) lack file-level docs (e.g. `include/box_style.h`)? What purpose do they serve?
- What would break if the most connected file in include: page_view changed?
- Should include: page_view be split, given cohesion 0.53?

## Sources

- `include/box_style.h`
- `include/box_tree.h`
- `include/compositor.h`
- `include/css.h`
- `include/css_chain.h`
- `include/css_computed.h`
- `include/dom_debug.h`
- `include/flex_layout.h`
- `include/page_view.h`
- `include/render_doc.h`
- `include/render_policy.h`
- `include/text_case.h`
- `src/box_style.c`
- `src/box_tree.c`
- `src/compositor.c`
- `src/css_computed.c`
- `src/css_length.c`
- `src/dom_debug.c`
- `src/flex_layout.c`
- `src/page_view.c`
- *... and 16 more*
