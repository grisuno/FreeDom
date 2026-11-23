# include: pres_hints

*Community 12 | 7 files | cohesion 0.60*

## Definition

This community groups 7 file(s) rooted at `include` with dominant language c (cohesion 0.60). Central symbols: `EPS`, `FREEDOM_PRES_HINTS_H`, `FREEDOM_TABLE_LAYOUT_H`, `LLVMFuzzerTestOneInput`, `PH_ATTR_MAX`, `PH_CENTERED`, `PH_DIM_MAX_PX`, `PH_PER_MILLE_MAX`. Core file: `tests/test_pres_hints.c` (14 symbols). Documented purpose: libFuzzer harness for table_layout and pres_hints (spec/table_layout.md, spec/pres_hints.md)..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_table_layout.c` | c | presentation | 3 | yes |
| `include/pres_hints.h` | h | utility | 10 | yes |
| `include/table_layout.h` | h | presentation | 8 | yes |
| `src/pres_hints.c` | c | utility | 12 | yes |
| `src/table_layout.c` | c | presentation | 5 | yes |
| `tests/test_pres_hints.c` | c | testing | 14 | yes |
| `tests/test_table_layout.c` | c | testing | 14 | yes |

## Key Symbols

- `attr_src` (struct, `fuzz/fuzz_table_layout.c:15`)
- `attr_get` (function, `fuzz/fuzz_table_layout.c:17`) `static const char *attr_get(void *ctx, const char *name, size_t *len)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_table_layout.c:24`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_PRES_HINTS_H` (macro, `include/pres_hints.h:8`) `#define FREEDOM_PRES_HINTS_H`
- `PH_ATTR_MAX` (macro, `include/pres_hints.h:17`) `#define PH_ATTR_MAX`
- `PH_DIM_MAX_PX` (macro, `include/pres_hints.h:18`) `#define PH_DIM_MAX_PX`
- `ph_parse_dimension` (function, `include/pres_hints.h:24`) `int ph_parse_dimension(const char *s, size_t len, int *px, int *per_mille);` - #ifdef __cplusplus #error "Freedom is pure C11 by policy; C++ is not supported." #endif #include <st
- `PH_CENTERED` (macro, `include/pres_hints.h:26`) `#define PH_CENTERED`
- `PH_QUIRKS` (macro, `include/pres_hints.h:27`) `#define PH_QUIRKS`
- `ph_apply` (function, `include/pres_hints.h:31`) `void ph_apply(const char *tag, ph_attr_fn get, void *ctx, unsigned flags, css_st` - Applies the hints of element `tag` (lower-case, NUL-terminated) to *cs; flags is a set of * PH_*. No
- `ph_parse_nonneg` (function, `include/pres_hints.h:34`) `int ph_parse_nonneg(const char *s, size_t len, int *out);` - Applies the hints of element `tag` (lower-case, NUL-terminated) to *cs; flags is a set of * PH_*. No
- `ph_table_cellpadding` (function, `include/pres_hints.h:37`) `int ph_table_cellpadding(ph_attr_fn get, void *ctx);` - Applies the hints of element `tag` (lower-case, NUL-terminated) to *cs; flags is a set of * PH_*. No
- `ph_cell_padding` (function, `include/pres_hints.h:41`) `void ph_cell_padding(int cellpad, css_style *cs);` - A table cell's padding: every side the cascade left unset takes cellpad px, or the UA * sheet's 1px
- `FREEDOM_TABLE_LAYOUT_H` (macro, `include/table_layout.h:11`) `#define FREEDOM_TABLE_LAYOUT_H`
- `TL_MAX_COLS` (macro, `include/table_layout.h:20`) `#define TL_MAX_COLS`
- `TL_WIDTH_MAX` (macro, `include/table_layout.h:23`) `#define TL_WIDTH_MAX`
- `TL_PER_MILLE` (macro, `include/table_layout.h:26`) `#define TL_PER_MILLE`
- `col` (type_alias, `include/table_layout.h:27`) `typedef struct tl_cell { int col;` - #ifdef __cplusplus #error "Freedom is pure C11 by policy; C++ is not supported." #endif #include <st
- `tl_cell` (struct, `include/table_layout.h:28`)
- `px` (function, `include/table_layout.h:41`) `* px (< 0 = auto: the table is as wide as its content, capped at avail). gap is`
- `tl_intrinsic` (function, `include/table_layout.h:53`) `void tl_intrinsic(const tl_cell *cells, size_t n, size_t ncols, double gap, doub` - The table's min-content and max-content widths (columns plus gaps): what it contributes when it is i
- `PH_PER_MILLE_MAX` (macro, `src/pres_hints.c:8`) `#define PH_PER_MILLE_MAX`
- `ph_is_space` (function, `src/pres_hints.c:10`) `static int ph_is_space(char c)`
- `ph_parse_dimension` (function, `src/pres_hints.c:14`) `int ph_parse_dimension(const char *s, size_t len, int *px, int *per_mille)`
- `ph_ci_eq` (function, `src/pres_hints.c:42`) `static int ph_ci_eq(const char *s, size_t len, const char *word)`
- `ph_align` (function, `src/pres_hints.c:53`) `static css_align ph_align(ph_attr_fn get, void *ctx)`
- `ph_width` (function, `src/pres_hints.c:64`) `static void ph_width(ph_attr_fn get, void *ctx, css_style *cs)`
- `ph_is_heading` (function, `src/pres_hints.c:76`) `static int ph_is_heading(const char *tag)`
- `ph_bgcolor` (function, `src/pres_hints.c:81`) `static void ph_bgcolor(ph_attr_fn get, void *ctx, css_style *cs)` - const char *v = get(ctx, "width", &len); int px = 0, pm = 0; switch (ph_parse_dimension(v, len, &px,
- `ph_apply` (function, `src/pres_hints.c:93`) `void ph_apply(const char *tag, ph_attr_fn get, void *ctx, unsigned flags, css_st`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 6
- Cross-boundary resolved imports (EXTRACTED): 4

## Connections

- [EXTRACTED] depends_on community 1 <-> 12 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/table_layout.h.

## Risks

- [layer strict] `tests/test_table_layout.c` (testing) -> `include/table_layout.h` (presentation)

## Open Questions

- What would break if the most connected file in include: pres_hints changed?
- Should include: pres_hints be split, given cohesion 0.60?

## Sources

- `fuzz/fuzz_table_layout.c`
- `include/pres_hints.h`
- `include/table_layout.h`
- `src/pres_hints.c`
- `src/table_layout.c`
- `tests/test_pres_hints.c`
- `tests/test_table_layout.c`
