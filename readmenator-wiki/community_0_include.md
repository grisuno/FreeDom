# include

*Community 0 | 28 files | cohesion 0.71*

## Definition

This community groups 28 file(s) rooted at `include` with dominant language c (cohesion 0.71). Central symbols: `AUTO_REJECT`, `AUTO_RESET`, `AUTO_RESET_NONE`, `AUTO_VALUE`, `CB_AUTO_REJECT`, `CB_AUTO_RESET`, `CB_AUTO_RESET_NONE`, `CB_AUTO_VALUE`. Core file: `tests/test_css.c` (266 symbols). Documented purpose: Bound for the ::before/::after content string pool (and the grid-template.

## Files

### `include` (10 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/css.h` | h | utility | 127 | no |
| `include/css_box.h` | h | utility | 25 | no |
| `include/css_chain.h` | h | utility | 5 | no |
| `include/css_color.h` | h | utility | 7 | no |
| `include/css_decl.h` | h | utility | 12 | yes |
| `include/css_gradient.h` | h | infrastructure | 3 | no |
| `include/css_length.h` | h | utility | 20 | no |

### `src` (9 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/css.c` | c | utility | 219 | no |
| `src/css_box.c` | c | utility | 47 | no |
| `src/css_chain.c` | c | utility | 15 | no |
| `src/css_color.c` | c | utility | 20 | no |
| `src/css_gradient.c` | c | infrastructure | 13 | no |
| `src/css_length.c` | c | utility | 18 | no |

### `tests` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_css.c` | c | testing | 266 | no |
| `tests/test_css_box.c` | c | testing | 9 | no |
| `tests/test_css_color.c` | c | testing | 29 | no |
| `tests/test_css_drops.c` | c | testing | 25 | yes |
| `tests/test_css_gradient.c` | c | testing | 7 | no |
| `tests/test_css_length.c` | c | testing | 25 | no |

### `fuzz` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_css.c` | c | utility | 1 | no |

*... and 8 more files in this community.*


## Key Symbols

- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_css.c:62`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_CSS_H` (macro, `include/css.h:2`) `#define FREEDOM_CSS_H`
- `css_status` (enum, `include/css.h:28`)
- `css_align` (enum, `include/css.h:34`)
- `css_display` (enum, `include/css.h:42`)
- `css_justify` (enum, `include/css.h:64`)
- `CSS_GAP_MAX` (macro, `include/css.h:75`) `#define CSS_GAP_MAX`
- `CSS_GRID_COLS_MAX` (macro, `include/css.h:76`) `#define CSS_GRID_COLS_MAX`
- `CSS_GRID_TRACKS_MAX` (macro, `include/css.h:77`) `#define CSS_GRID_TRACKS_MAX`
- `verbatim` (function, `include/css.h:79`) `* the quoted row strings verbatim (flex_layout parses them);`
- `CSS_GRID_AREAS_MAX` (macro, `include/css.h:83`) `#define CSS_GRID_AREAS_MAX`
- `CSS_GRAD_STOPS_MAX` (macro, `include/css.h:84`) `#define CSS_GRAD_STOPS_MAX`
- `CSS_LINE_MIN` (macro, `include/css.h:85`) `#define CSS_LINE_MIN`
- `CSS_LINE_MAX` (macro, `include/css.h:86`) `#define CSS_LINE_MAX`
- `CSS_URL_MAX` (macro, `include/css.h:87`) `#define CSS_URL_MAX`
- `CSS_DECO_UNDERLINE` (macro, `include/css.h:92`) `#define CSS_DECO_UNDERLINE`
- `CSS_DECO_LINE_THROUGH` (macro, `include/css.h:93`) `#define CSS_DECO_LINE_THROUGH`
- `CSS_DECO_OVERLINE` (macro, `include/css.h:94`) `#define CSS_DECO_OVERLINE`
- `css_font_family` (enum, `include/css.h:98`) - Generic font family bucket (font-family). A specific family name is mapped to its * generic group; a
- `css_text_transform` (enum, `include/css.h:104`) - Generic font family bucket (font-family). A specific family name is mapped to its * generic group; a
- `css_valign` (enum, `include/css.h:109`) - Generic font family bucket (font-family). A specific family name is mapped to its * generic group; a
- `css_white_space` (enum, `include/css.h:115`) - } css_font_family; /* text-transform. 0 is unset; CSS_TT_NONE is an explicit `none`. typedef enum cs
- `css_list_style` (enum, `include/css.h:121`) - /* vertical-align (subset: only the inline shifts). 0 unset. typedef enum css_valign { CSS_VA_UNSET
- `css_position` (enum, `include/css.h:133`) - position. 0 unset; STATIC is the explicit in-flow default. RELATIVE offsets the box from its in-flow
- `css_box_sizing` (enum, `include/css.h:140`) - box-sizing. 0 unset; CONTENT is content-box (width excludes padding/border), * BORDER is border-box
- `css_border_style` (enum, `include/css.h:147`) - border-style / outline-style (subset). 0 unset; NONE/HIDDEN paint nothing. The decorative variants a
- `css_flex_direction` (enum, `include/css.h:154`) - border-style / outline-style (subset). 0 unset; NONE/HIDDEN paint nothing. The decorative variants a
- `css_flex_wrap` (enum, `include/css.h:160`) - collapse the fancier ones (groove/ridge/inset/outset) to solid. typedef enum css_border_style { CSS_
- `css_align_kw` (enum, `include/css.h:166`) - align-items / align-self / align-content / justify-items (cross-axis alignment). * 0 unset. AUTO onl
- `css_grid_flow` (enum, `include/css.h:173`) - align-items / align-self / align-content / justify-items (cross-axis alignment). * 0 unset. AUTO onl

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 67
- Cross-boundary resolved imports (EXTRACTED): 27

## Connections

- [EXTRACTED] depends_on community 2 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/css.h.
- [EXTRACTED] depends_on community 8 <-> 0 (strength 0.9): Extracted import edge crosses communities: src/text_shape.c imports include/css.h.
- [INFERRED] shares_context community 0 <-> 1 (strength 0.5): Inferred shared context (language c) with no import path between community 0 (include) and community 1 (include).
- [INFERRED] shares_context community 0 <-> 3 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 0 (include) and community 3 (include).
- [INFERRED] shares_context community 0 <-> 4 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 0 (include) and community 4 (tests).
- [INFERRED] shares_context community 0 <-> 5 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 0 (include) and community 5 (include).
- [INFERRED] shares_context community 0 <-> 6 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 0 (include) and community 6 (include).

## Risks

- [dataflow DEAD_STORE] `src/css.c:3601` `drop_record` `important`: `important` assigned at line 3601 but never read afterwards.
- [dataflow DEAD_STORE] `src/css_color.c:150` `parse_hex` `r`: `r` assigned at line 150 but never read afterwards.
- [dataflow DEAD_STORE] `src/css_color.c:151` `parse_hex` `g`: `g` assigned at line 151 but never read afterwards.

## Open Questions

- Why do 24 file(s) lack file-level docs (e.g. `fuzz/fuzz_css.c`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.71?

## Sources

- `fuzz/fuzz_css.c`
- `include/css.h`
- `include/css_box.h`
- `include/css_chain.h`
- `include/css_color.h`
- `include/css_decl.h`
- `include/css_gradient.h`
- `include/css_length.h`
- `include/css_select.h`
- `include/css_text.h`
- `include/css_values.h`
- `src/css.c`
- `src/css_box.c`
- `src/css_chain.c`
- `src/css_color.c`
- `src/css_gradient.c`
- `src/css_length.c`
- `src/css_select.c`
- `src/css_text.c`
- `src/css_values.c`
- *... and 8 more*
