# include

*Community 2 | 4 files | cohesion 0.60*

## Definition

This community groups 4 file(s) rooted at `include` with dominant language c (cohesion 0.60). Central symbols: `FREEDOM_PDF_EXPORT_H`, `LLVMFuzzerTestOneInput`, `PE_EXT`, `PE_EXT_PNG`, `PE_FALLBACK_NAME`, `PE_NAME_MAX`, `fallback`, `literal`. Core file: `tests/test_pdf_export.c` (30 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_pdf_export.c` | c | utility | 1 | no |
| `include/pdf_export.h` | h | utility | 10 | no |
| `src/pdf_export.c` | c | utility | 4 | no |
| `tests/test_pdf_export.c` | c | testing | 30 | no |

## Key Symbols

- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_pdf_export.c:30`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_PDF_EXPORT_H` (macro, `include/pdf_export.h:2`) `#define FREEDOM_PDF_EXPORT_H`
- `PE_NAME_MAX` (macro, `include/pdf_export.h:28`) `#define PE_NAME_MAX`
- `PE_EXT` (macro, `include/pdf_export.h:29`) `#define PE_EXT`
- `PE_EXT_PNG` (macro, `include/pdf_export.h:30`) `#define PE_EXT_PNG`
- `PE_FALLBACK_NAME` (macro, `include/pdf_export.h:31`) `#define PE_FALLBACK_NAME`
- `pe_status` (enum, `include/pdf_export.h:33`)
- `fallback` (function, `include/pdf_export.h:46`) `* fallback (PE_ERR_OVERFLOW, out left empty). title == NULL is treated as empty.`
- `trusted` (function, `include/pdf_export.h:51`) `* dir is trusted (chosen by the app from XDG/$HOME);`
- `literal` (function, `include/pdf_export.h:52`) `* trusted literal (e.g. PE_EXT / PE_EXT_PNG);`
- `pe_paginate` (function, `include/pdf_export.h:70`) `size_t pe_paginate(const double *tops, const double *heights, size_t n, double p` - Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usab
- `pe_safe_basename` (function, `src/pdf_export.c:25`) `pe_status pe_safe_basename(const char *title, char *out, size_t outsz)`
- `pe_build_path_ext` (function, `src/pdf_export.c:66`) `pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,`
- `pe_build_path` (function, `src/pdf_export.c:91`) `pe_status pe_build_path(const char *dir, const char *title, char *out, size_t ou`
- `pe_paginate` (function, `src/pdf_export.c:95`) `size_t pe_paginate(const double *tops, const double *heights, size_t n,`
- `pagination` (function, `tests/test_pdf_export.c:8`) `* deterministic pagination (single/multi page, no row splitting, oversized row,`
- `test_basename_maps_spaces_and_reserved` (function, `tests/test_pdf_export.c:31`) `static void test_basename_maps_spaces_and_reserved(void **state)`
- `test_basename_rejects_path_separators` (function, `tests/test_pdf_export.c:39`) `static void test_basename_rejects_path_separators(void **state)`
- `test_basename_neutralizes_traversal` (function, `tests/test_pdf_export.c:49`) `static void test_basename_neutralizes_traversal(void **state)`
- `test_basename_dotdot_only_falls_back` (function, `tests/test_pdf_export.c:57`) `static void test_basename_dotdot_only_falls_back(void **state)`
- `test_basename_trims_edges` (function, `tests/test_pdf_export.c:64`) `static void test_basename_trims_edges(void **state)`
- `test_basename_collapses_underscores` (function, `tests/test_pdf_export.c:72`) `static void test_basename_collapses_underscores(void **state)`
- `test_basename_control_bytes_mapped` (function, `tests/test_pdf_export.c:79`) `static void test_basename_control_bytes_mapped(void **state)`
- `test_basename_non_ascii_mapped` (function, `tests/test_pdf_export.c:87`) `static void test_basename_non_ascii_mapped(void **state)`
- `test_basename_empty_and_null_fall_back` (function, `tests/test_pdf_export.c:96`) `static void test_basename_empty_and_null_fall_back(void **state)`
- `test_basename_all_separators_fall_back` (function, `tests/test_pdf_export.c:105`) `static void test_basename_all_separators_fall_back(void **state)`
- `test_basename_length_bound` (function, `tests/test_pdf_export.c:112`) `static void test_basename_length_bound(void **state)`
- `test_basename_null_out_and_zero_size` (function, `tests/test_pdf_export.c:123`) `static void test_basename_null_out_and_zero_size(void **state)`
- `test_basename_overflow_fails_closed` (function, `tests/test_pdf_export.c:130`) `static void test_basename_overflow_fails_closed(void **state)`
- `test_build_path_basic` (function, `tests/test_pdf_export.c:139`) `static void test_build_path_basic(void **state)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 3
- Cross-boundary resolved imports (EXTRACTED): 2

## Connections

- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/pdf_export.h.
- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: src/download.c imports include/pdf_export.h.
- [INFERRED] shares_context community 2 <-> 3 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 2 (include) and community 3 (include).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 4 file(s) lack file-level docs (e.g. `fuzz/fuzz_pdf_export.c`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.60?

## Sources

- `fuzz/fuzz_pdf_export.c`
- `include/pdf_export.h`
- `src/pdf_export.c`
- `tests/test_pdf_export.c`
