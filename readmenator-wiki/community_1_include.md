# include

*Community 1 | 4 files | cohesion 0.60*

## Definition

This community groups 4 file(s) rooted at `include` with dominant language c (cohesion 0.60). Central symbols: `DL_ERR_OVERFLOW`, `DL_FALLBACK_NAME`, `DL_MAX_BYTES`, `DL_NAME_MAX`, `FREEDOM_DOWNLOAD_H`, `LLVMFuzzerTestOneInput`, `basename`, `builder`. Core file: `tests/test_download.c` (21 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_download.c` | c | utility | 1 | no |
| `include/download.h` | h | utility | 9 | no |
| `src/download.c` | c | utility | 12 | no |
| `tests/test_download.c` | c | testing | 21 | no |

## Key Symbols

- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_download.c:31`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_DOWNLOAD_H` (macro, `include/download.h:2`) `#define FREEDOM_DOWNLOAD_H`
- `DL_NAME_MAX` (macro, `include/download.h:29`) `#define DL_NAME_MAX`
- `DL_FALLBACK_NAME` (macro, `include/download.h:30`) `#define DL_FALLBACK_NAME`
- `DL_MAX_BYTES` (macro, `include/download.h:31`) `#define DL_MAX_BYTES`
- `dl_status` (enum, `include/download.h:33`)
- `dl_should_download` (function, `include/download.h:43`) `int dl_should_download(const char *content_type, const char *content_disposition` - 1 if the response should be saved (attachment, or a non-renderable media type), 0 if it should be re
- `literal` (function, `include/download.h:47`) `* a static string literal (never freed). */ const char *dl_ext_for_type(const ch`
- `DL_ERR_OVERFLOW` (function, `include/download.h:56`) `* DL_ERR_OVERFLOW (out left empty). url/content_disposition NULL => absent. */ d`
- `basename` (function, `include/download.h:61`) `* sanitized basename (a name still containing '/' is rejected => DL_ERR_OVERFLOW`
- `lc` (function, `src/download.c:13`) `static int lc(int c)` - download — pure helpers for "save this resource to disk". See include/download.h and spec/download.m
- `ci_find` (function, `src/download.c:19`) `static const char *ci_find(const char *hay, const char *needle)` - #include "download.h" #include "pdf_export.h"   /* pe_safe_basename: the single audited sanitizer #i
- `media_type` (function, `src/download.c:33`) `static void media_type(const char *content_type, char *buf, size_t bufsz)` - Writes the lowercased media type of content_type (the part before ';', with * surrounding spaces tri
- `dl_should_download` (function, `src/download.c:47`) `int dl_should_download(const char *content_type, const char *content_disposition`
- `dl_ext_for_type` (function, `src/download.c:58`) `const char *dl_ext_for_type(const char *content_type)`
- `copy_span` (function, `src/download.c:85`) `static void copy_span(const char *src, const char *end, char *buf, size_t bufsz)` - { "application/xhtml+xml",  ".html" }, { "text/plain",            ".txt"  }, { "image/png",
- `extract_disposition_name` (function, `src/download.c:96`) `static int extract_disposition_name(const char *cd, char *buf, size_t bufsz)` - Extracts a filename candidate from a Content-Disposition value into buf. Handles filename="...", fil
- `extract_url_name` (function, `src/download.c:134`) `static int extract_url_name(const char *url, char *buf, size_t bufsz)` - Extracts the last path segment of url (without ?query or #fragment) into buf. * Returns 1 if a non-e
- `has_extension` (function, `src/download.c:148`) `static int has_extension(const char *name)` - Does name already carry an extension (a '.' past the first byte with at least * one character after
- `dl_pick_name` (function, `src/download.c:153`) `dl_status dl_pick_name(const char *url, const char *content_disposition,`
- `dl_build_path` (function, `src/download.c:195`) `dl_status dl_build_path(const char *dir, const char *name, char *out, size_t out`
- `dl_check_size` (function, `src/download.c:213`) `dl_status dl_check_size(size_t len)`
- `builder` (function, `tests/test_download.c:8`) `* builder (join, separator rejection, overflow, NULL), and the size cap.  */  #i`
- `test_should_renderable_types` (function, `tests/test_download.c:30`) `static void test_should_renderable_types(void **state)`
- `test_should_binary_types` (function, `tests/test_download.c:41`) `static void test_should_binary_types(void **state)`
- `test_ext_known_types` (function, `tests/test_download.c:52`) `static void test_ext_known_types(void **state)`
- `test_ext_unknown_type` (function, `tests/test_download.c:63`) `static void test_ext_unknown_type(void **state)`
- `test_pick_from_disposition_quoted` (function, `tests/test_download.c:72`) `static void test_pick_from_disposition_quoted(void **state)`
- `test_pick_from_disposition_ext_form` (function, `tests/test_download.c:81`) `static void test_pick_from_disposition_ext_form(void **state)`
- `test_pick_from_url_segment` (function, `tests/test_download.c:91`) `static void test_pick_from_url_segment(void **state)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 3
- Cross-boundary resolved imports (EXTRACTED): 2

## Connections

- [EXTRACTED] depends_on community 0 <-> 1 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/download.h.
- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: src/download.c imports include/pdf_export.h.
- [INFERRED] shares_context community 1 <-> 3 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (include) and community 3 (include).
- [INFERRED] shares_context community 1 <-> 4 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (include) and community 4 (include).
- [INFERRED] shares_context community 1 <-> 5 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (include) and community 5 (include).
- [INFERRED] shares_context community 1 <-> 6 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (include) and community 6 (include).
- [INFERRED] shares_context community 1 <-> 7 (strength 0.5): Inferred shared context (language c) with no import path between community 1 (include) and community 7 (include).
- [INFERRED] shares_context community 1 <-> 8 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (include) and community 8 (include).
- [INFERRED] shares_context community 1 <-> 9 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (include) and community 9 (include).
- [INFERRED] shares_context community 1 <-> 10 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (include) and community 10 (orphans).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 4 file(s) lack file-level docs (e.g. `fuzz/fuzz_download.c`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.60?

## Sources

- `fuzz/fuzz_download.c`
- `include/download.h`
- `src/download.c`
- `tests/test_download.c`
