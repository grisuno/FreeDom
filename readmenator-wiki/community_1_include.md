# include

*Community 1 | 4 files | cohesion 0.43*

## Definition

This community groups 4 file(s) rooted at `include` with dominant language c (cohesion 0.43). Central symbols: `DU_MAX_ENCODED_LEN`, `FREEDOM_DATA_URL_H`, `allocation`, `ascii_ws`, `b64_val`, `ci_starts_with`, `closed`, `du_base64_decode`. Core file: `tests/test_data_url.c` (26 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_data_url.c` | c | data_access | 1 | no |
| `include/data_url.h` | h | data_access | 6 | no |
| `src/data_url.c` | c | data_access | 10 | no |
| `tests/test_data_url.c` | c | testing | 26 | no |

## Key Symbols

- `worker` (function, `fuzz/fuzz_data_url.c:6`) `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, nev`
- `FREEDOM_DATA_URL_H` (macro, `include/data_url.h:2`) `#define FREEDOM_DATA_URL_H`
- `allocation` (function, `include/data_url.h:21`) `* * du_base64_payload does no allocation (it only slices the caller's url string`
- `du_status` (enum, `include/data_url.h:27`)
- `DU_MAX_ENCODED_LEN` (macro, `include/data_url.h:43`) `#define DU_MAX_ENCODED_LEN`
- `du_is_data_url` (function, `include/data_url.h:46`) `int du_is_data_url(const char *url);` - 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding
- `closed` (function, `include/data_url.h:59`) `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/ou`
- `lower` (function, `src/data_url.c:16`) `static int lower(char c)`
- `ci_starts_with` (function, `src/data_url.c:20`) `static int ci_starts_with(const char *s, const char *prefix)`
- `du_is_data_url` (function, `src/data_url.c:28`) `int du_is_data_url(const char *url)`
- `du_base64_payload` (function, `src/data_url.c:32`) `du_status du_base64_payload(const char *url, const char **payload, size_t *paylo`
- `b64_val` (function, `src/data_url.c:61`) `static int b64_val(unsigned char c)` - 0-63 for a base64 alphabet character, -1 otherwise. Kept as a small function * (not a 256-entry tabl
- `du_base64_decode` (function, `src/data_url.c:70`) `du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_`
- `hexval` (function, `src/data_url.c:108`) `static int hexval(char c)`
- `ascii_ws` (function, `src/data_url.c:115`) `static int ascii_ws(char c)`
- `ends_ci` (function, `src/data_url.c:120`) `static int ends_ci(const char *s, size_t n, const char *suf)` - } static int hexval(char c) { if (c >= '0' && c <= '9') return c - '0'; if (c >= 'a' && c <= 'f') re
- `du_decode` (function, `src/data_url.c:131`) `du_status du_decode(const char *url, char *mime, size_t mime_cap, uint8_t **out,`
- `test_is_data_url_true` (function, `tests/test_data_url.c:23`) `static void test_is_data_url_true(void **state)`
- `test_is_data_url_false` (function, `tests/test_data_url.c:31`) `static void test_is_data_url_false(void **state)`
- `test_payload_basic` (function, `tests/test_data_url.c:43`) `static void test_payload_basic(void **state)`
- `test_payload_no_mediatype` (function, `tests/test_data_url.c:54`) `static void test_payload_no_mediatype(void **state)`
- `test_payload_empty` (function, `tests/test_data_url.c:63`) `static void test_payload_empty(void **state)`
- `test_payload_not_data_url` (function, `tests/test_data_url.c:73`) `static void test_payload_not_data_url(void **state)`
- `test_payload_percent_encoded_not_supported` (function, `tests/test_data_url.c:81`) `static void test_payload_percent_encoded_not_supported(void **state)`
- `test_payload_no_comma` (function, `tests/test_data_url.c:89`) `static void test_payload_no_comma(void **state)`
- `test_payload_base64_flag_case_insensitive` (function, `tests/test_data_url.c:97`) `static void test_payload_base64_flag_case_insensitive(void **state)`
- `test_payload_too_large` (function, `tests/test_data_url.c:106`) `static void test_payload_too_large(void **state)`
- `test_payload_nulls` (function, `tests/test_data_url.c:122`) `static void test_payload_nulls(void **state)`
- `test_decode_one_byte_double_pad` (function, `tests/test_data_url.c:135`) `static void test_decode_one_byte_double_pad(void **state)`
- `test_decode_two_bytes_single_pad` (function, `tests/test_data_url.c:146`) `static void test_decode_two_bytes_single_pad(void **state)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 3
- Cross-boundary resolved imports (EXTRACTED): 4

## Connections

- [EXTRACTED] depends_on community 3 <-> 1 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 0 <-> 1 (strength 0.9): Extracted import edge crosses communities: src/render_doc.c imports include/data_url.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_policy.c` (presentation) -> `include/data_url.h` (data_access)

## Open Questions

- Why do 4 file(s) lack file-level docs (e.g. `fuzz/fuzz_data_url.c`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.43?

## Sources

- `fuzz/fuzz_data_url.c`
- `include/data_url.h`
- `src/data_url.c`
- `tests/test_data_url.c`
