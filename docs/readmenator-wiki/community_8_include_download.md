# include: download

*Community 8 | 8 files | cohesion 0.78*

## Definition

This community groups 8 file(s) rooted at `include` with dominant language c (cohesion 0.78). Central symbols: `DL_ERR_OVERFLOW`, `DL_FALLBACK_NAME`, `DL_MAX_BYTES`, `DL_NAME_MAX`, `FREEDOM_DOWNLOAD_H`, `FREEDOM_PDF_EXPORT_H`, `LLVMFuzzerTestOneInput`, `PE_EXT`. Core file: `tests/test_pdf_export.c` (30 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_download.c` | c | utility | 1 | no |
| `fuzz/fuzz_pdf_export.c` | c | utility | 1 | no |
| `include/download.h` | h | utility | 9 | no |
| `include/pdf_export.h` | h | utility | 10 | no |
| `src/download.c` | c | utility | 12 | no |
| `src/pdf_export.c` | c | utility | 4 | no |
| `tests/test_download.c` | c | testing | 21 | no |
| `tests/test_pdf_export.c` | c | testing | 30 | no |

## Key Symbols

- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_download.c:31`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_pdf_export.c:30`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_DOWNLOAD_H` (macro, `include/download.h:2`) `#define FREEDOM_DOWNLOAD_H`
- `DL_NAME_MAX` (macro, `include/download.h:29`) `#define DL_NAME_MAX`
- `DL_FALLBACK_NAME` (macro, `include/download.h:30`) `#define DL_FALLBACK_NAME`
- `DL_MAX_BYTES` (macro, `include/download.h:31`) `#define DL_MAX_BYTES`
- `dl_status` (enum, `include/download.h:33`)
- `dl_should_download` (function, `include/download.h:43`) `int dl_should_download(const char *content_type, const char *content_disposition` - 1 if the response should be saved (attachment, or a non-renderable media type), 0 if it should be re
- `literal` (function, `include/download.h:47`) `* a static string literal (never freed). */ const char *dl_ext_for_type(const ch`
- `DL_ERR_OVERFLOW` (function, `include/download.h:56`) `* DL_ERR_OVERFLOW (out left empty). url/content_disposition NULL => absent. */ d`
- `basename` (function, `include/download.h:61`) `* sanitized basename (a name still containing '/' is rejected => DL_ERR_OVERFLOW`
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
- `lc` (function, `src/download.c:13`) `static int lc(int c)` - download — pure helpers for "save this resource to disk". See include/download.h and spec/download.m
- `ci_find` (function, `src/download.c:19`) `static const char *ci_find(const char *hay, const char *needle)` - #include "download.h" #include "pdf_export.h"   /* pe_safe_basename: the single audited sanitizer #i
- `media_type` (function, `src/download.c:33`) `static void media_type(const char *content_type, char *buf, size_t bufsz)` - Writes the lowercased media type of content_type (the part before ';', with * surrounding spaces tri
- `dl_should_download` (function, `src/download.c:47`) `int dl_should_download(const char *content_type, const char *content_disposition`
- `dl_ext_for_type` (function, `src/download.c:58`) `const char *dl_ext_for_type(const char *content_type)`
- `copy_span` (function, `src/download.c:85`) `static void copy_span(const char *src, const char *end, char *buf, size_t bufsz)` - { "application/xhtml+xml",  ".html" }, { "text/plain",            ".txt"  }, { "image/png",
- `extract_disposition_name` (function, `src/download.c:96`) `static int extract_disposition_name(const char *cd, char *buf, size_t bufsz)` - Extracts a filename candidate from a Content-Disposition value into buf. Handles filename="...", fil
- `extract_url_name` (function, `src/download.c:134`) `static int extract_url_name(const char *url, char *buf, size_t bufsz)` - Extracts the last path segment of url (without ?query or #fragment) into buf. * Returns 1 if a non-e
- `has_extension` (function, `src/download.c:148`) `static int has_extension(const char *name)` - Does name already carry an extension (a '.' past the first byte with at least * one character after

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 7
- Cross-boundary resolved imports (EXTRACTED): 2

## Connections

- [EXTRACTED] depends_on community 1 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/download.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 8 file(s) lack file-level docs (e.g. `fuzz/fuzz_download.c`)? What purpose do they serve?
- What would break if the most connected file in include: download changed?
- Should include: download be split, given cohesion 0.78?

## Sources

- `fuzz/fuzz_download.c`
- `fuzz/fuzz_pdf_export.c`
- `include/download.h`
- `include/pdf_export.h`
- `src/download.c`
- `src/pdf_export.c`
- `tests/test_download.c`
- `tests/test_pdf_export.c`
