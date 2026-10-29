# include: css

*Community 4 | 35 files | cohesion 0.68*

## Definition

This community groups 35 file(s) rooted at `include` with dominant language c (cohesion 0.68). Central symbols: `AUTO_REJECT`, `AUTO_RESET`, `AUTO_RESET_NONE`, `AUTO_VALUE`, `CAR_INLINE_SPEC`, `CAR_LAYER_NAME_MAX`, `CAR_MAX_DEPTH`, `CAR_MAX_LAYERS`. Core file: `tests/test_css.c` (354 symbols). Documented purpose: The sheet's two string pools -- background url()s, and the ::before/::after.

## Files

### `include` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/css_atrule.h` | h | utility | 10 | no |
| `include/css_box.h` | h | utility | 27 | no |
| `include/css_color.h` | h | utility | 7 | no |
| `include/css_decl.h` | h | utility | 14 | yes |
| `include/css_gradient.h` | h | utility | 13 | no |
| `include/css_index.h` | h | utility | 8 | no |
| `include/css_length.h` | h | utility | 20 | no |

### `src` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/css.c` | c | utility | 249 | no |
| `src/css_atrule.c` | c | utility | 11 | no |
| `src/css_box.c` | c | utility | 52 | no |
| `src/css_chain.c` | c | utility | 26 | no |
| `src/css_color.c` | c | utility | 27 | no |
| `src/css_gradient.c` | c | utility | 31 | no |
| `src/css_index.c` | c | utility | 13 | yes |

### `tests` (9 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_css.c` | c | testing | 354 | no |
| `tests/test_css_atrule.c` | c | testing | 10 | yes |
| `tests/test_css_box.c` | c | testing | 13 | no |
| `tests/test_css_color.c` | c | testing | 36 | no |
| `tests/test_css_index.c` | c | testing | 14 | yes |
| `tests/test_css_mask.c` | c | testing | 12 | yes |

*... and 15 more files in this community.*


## Key Symbols

- `FREEDOM_CSS_ATRULE_H` (macro, `include/css_atrule.h:2`) `#define FREEDOM_CSS_ATRULE_H`
- `CAR_MAX_DEPTH` (macro, `include/css_atrule.h:15`) `#define CAR_MAX_DEPTH`
- `CAR_MAX_LAYERS` (macro, `include/css_atrule.h:16`) `#define CAR_MAX_LAYERS`
- `CAR_LAYER_NAME_MAX` (macro, `include/css_atrule.h:17`) `#define CAR_LAYER_NAME_MAX`
- `CAR_INLINE_SPEC` (macro, `include/css_atrule.h:18`) `#define CAR_INLINE_SPEC`
- `car_ops` (struct, `include/css_atrule.h:22`) - The questions @supports asks the caller's own engine. prop is lowercased and * both strings are trim
- `car_supports` (function, `include/css_atrule.h:29`) `int car_supports(const char *s, size_t a, size_t b, const car_ops *ops);` - The questions @supports asks the caller's own engine. prop is lowercased and * both strings are trim
- `car_layers` (struct, `include/css_atrule.h:31`)
- `car_layer_rank` (function, `include/css_atrule.h:40`) `int car_layer_rank(car_layers *L, const char *name, size_t len);` - Rank (1..CAR_MAX_LAYERS) of the layer whose full dotted name is name[0,len), registering it on first
- `car_effective_spec` (function, `include/css_atrule.h:44`) `int car_effective_spec(int spec, int layer, int important);` - Folds layer rank and specificity into one comparable value (layer first). layer * 0 = unlayered. Imp
- `FREEDOM_CSS_BOX_H` (macro, `include/css_box.h:2`) `#define FREEDOM_CSS_BOX_H`
- `CB_AUTO_REJECT` (macro, `include/css_box.h:10`) `#define CB_AUTO_REJECT`
- `CB_AUTO_VALUE` (macro, `include/css_box.h:11`) `#define CB_AUTO_VALUE`
- `CB_AUTO_RESET` (macro, `include/css_box.h:12`) `#define CB_AUTO_RESET`
- `CB_AUTO_RESET_NONE` (macro, `include/css_box.h:13`) `#define CB_AUTO_RESET_NONE`
- `cb_length_px` (function, `include/css_box.h:15`) `int cb_length_px(const char *v, double *px);`
- `cb_interp_len` (function, `include/css_box.h:16`) `int cb_interp_len(const char *v, int allow_auto, int *out);`
- `cb_emit_len` (function, `include/css_box.h:17`) `int cb_emit_len(css_decl *dst, int cap, int slot, const char *val, int allow_aut`
- `cb_expand_box4` (function, `include/css_box.h:19`) `int cb_expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,`
- `cb_expand_box2` (function, `include/css_box.h:21`) `int cb_expand_box2(const char *val, int slot_start, int slot_end, int allow_auto`
- `cb_interp_lp` (function, `include/css_box.h:23`) `int cb_interp_lp(const char *v, int allow_auto, int allow_pct, int *out_px, int`
- `cb_value_em_milli` (function, `include/css_box.h:25`) `int cb_value_em_milli(const char *v);`
- `rectangle` (function, `include/css_box.h:27`) `* rectangle (top, right, bottom, left): px[i] + pm[i]/1000 of the border box (he`
- `cb_lp_can_be_nonneg` (function, `include/css_box.h:31`) `int cb_lp_can_be_nonneg(int px_val, int pct_pm);`
- `cb_next_ws_token` (function, `include/css_box.h:32`) `int cb_next_ws_token(const char **p, char *tok, size_t cap);`
- `cb_interp_align` (function, `include/css_box.h:33`) `int cb_interp_align(const char *v);`
- `cb_interp_fontsize_ex` (function, `include/css_box.h:34`) `int cb_interp_fontsize_ex(const char *v, int *abs_out);`
- `cb_interp_lineheight` (function, `include/css_box.h:35`) `int cb_interp_lineheight(const char *v);`
- `cb_interp_weight` (function, `include/css_box.h:36`) `int cb_interp_weight(const char *v);`
- `cb_interp_style` (function, `include/css_box.h:37`) `int cb_interp_style(const char *v);`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 67
- Cross-boundary resolved imports (EXTRACTED): 32

## Connections

- [EXTRACTED] depends_on community 0 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/css_color.h.
- [EXTRACTED] depends_on community 3 <-> 4 (strength 0.9): Extracted import edge crosses communities: include/css.h imports include/css_color.h.
- [EXTRACTED] depends_on community 4 <-> 2 (strength 0.9): Extracted import edge crosses communities: src/css.c imports include/webfont.h.
- [EXTRACTED] depends_on community 1 <-> 4 (strength 0.9): Extracted import edge crosses communities: src/dom.c imports include/css_select.h.

## Risks

- [layer strict] `tests/test_css.c` (testing) -> `include/flex_layout.h` (presentation)
- [dataflow DEAD_STORE] `src/css.c:5545` `page_view` `had_winner`: `had_winner` assigned at line 5545 but never read afterwards.
- [dataflow DEAD_STORE] `src/css_color.c:155` `parse_hex` `r`: `r` assigned at line 155 but never read afterwards.
- [dataflow DEAD_STORE] `src/css_color.c:156` `parse_hex` `g`: `g` assigned at line 156 but never read afterwards.

## Open Questions

- Why do 26 file(s) lack file-level docs (e.g. `include/css_atrule.h`)? What purpose do they serve?
- What would break if the most connected file in include: css changed?
- Should include: css be split, given cohesion 0.68?

## Sources

- `include/css_atrule.h`
- `include/css_box.h`
- `include/css_color.h`
- `include/css_decl.h`
- `include/css_gradient.h`
- `include/css_index.h`
- `include/css_length.h`
- `include/css_mask.h`
- `include/css_mq.h`
- `include/css_select.h`
- `include/css_text.h`
- `include/css_values.h`
- `include/css_vars.h`
- `src/css.c`
- `src/css_atrule.c`
- `src/css_box.c`
- `src/css_chain.c`
- `src/css_color.c`
- `src/css_gradient.c`
- `src/css_index.c`
- *... and 15 more*
