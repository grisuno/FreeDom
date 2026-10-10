# include: text_shape

*Community 4 | 20 files | cohesion 0.55*

## Definition

This community groups 20 file(s) rooted at `include` with dominant language c (cohesion 0.55). Central symbols: `DU_MAX_ENCODED_LEN`, `FREEDOM_DATA_URL_H`, `FREEDOM_PSL_DATA_H`, `FREEDOM_REQUEST_POLICY_H`, `FREEDOM_TEXT_SHAPE_H`, `FREEDOM_WEBFONT_H`, `FREEDOM_WEBFONT_LOAD_H`, `FZ_CAP`. Core file: `src/text_shape.c` (26 symbols). Documented purpose: libFuzzer harness for the webfont lookahead scanner (spec/webfont.md). The.

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_data_url.c` | c | data_access | 1 | no |
| `fuzz/fuzz_text_shape.c` | c | utility | 2 | no |
| `fuzz/fuzz_webfont.c` | c | utility | 1 | yes |
| `include/data_url.h` | h | data_access | 6 | no |
| `include/psl_data.h` | h | data_access | 7 | no |
| `include/request_policy.h` | h | business_logic | 5 | no |
| `include/text_shape.h` | h | utility | 13 | no |
| `include/webfont.h` | h | utility | 17 | no |
| `include/webfont_load.h` | h | utility | 7 | no |
| `src/data_url.c` | c | data_access | 10 | no |
| `src/render_policy.c` | c | presentation | 5 | no |
| `src/request_policy.c` | c | business_logic | 11 | no |
| `src/text_shape.c` | c | utility | 26 | no |
| `src/webfont.c` | c | utility | 15 | no |
| `src/webfont_load.c` | c | utility | 11 | no |
| `tests/test_data_url.c` | c | testing | 26 | no |
| `tests/test_request_policy.c` | c | testing | 12 | no |
| `tests/test_text_shape.c` | c | testing | 12 | no |
| `tests/test_webfont.c` | c | testing | 13 | no |
| `tests/test_webfont_load.c` | c | testing | 16 | no |

## Key Symbols

- `worker` (function, `fuzz/fuzz_data_url.c:6`) `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, nev`
- `FZ_CAP` (macro, `fuzz/fuzz_text_shape.c:23`) `#define FZ_CAP`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_text_shape.c:25`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_webfont.c:11`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_DATA_URL_H` (macro, `include/data_url.h:2`) `#define FREEDOM_DATA_URL_H`
- `allocation` (function, `include/data_url.h:21`) `* * du_base64_payload does no allocation (it only slices the caller's url string`
- `du_status` (enum, `include/data_url.h:27`)
- `DU_MAX_ENCODED_LEN` (macro, `include/data_url.h:43`) `#define DU_MAX_ENCODED_LEN`
- `du_is_data_url` (function, `include/data_url.h:46`) `int du_is_data_url(const char *url);` - 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding
- `closed` (function, `include/data_url.h:59`) `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/ou`
- `FREEDOM_PSL_DATA_H` (macro, `include/psl_data.h:2`) `#define FREEDOM_PSL_DATA_H`
- `psl_rules` (variable, `include/psl_data.h:21`) `extern const char *const psl_rules[];`
- `psl_rules_n` (variable, `include/psl_data.h:22`) `extern const size_t psl_rules_n;`
- `psl_wildcards` (variable, `include/psl_data.h:23`) `extern const char *const psl_wildcards[];`
- `psl_wildcards_n` (variable, `include/psl_data.h:24`) `extern const size_t psl_wildcards_n;`
- `psl_exceptions` (variable, `include/psl_data.h:25`) `extern const char *const psl_exceptions[];`
- `psl_exceptions_n` (variable, `include/psl_data.h:26`) `extern const size_t psl_exceptions_n;`
- `FREEDOM_REQUEST_POLICY_H` (macro, `include/request_policy.h:2`) `#define FREEDOM_REQUEST_POLICY_H`
- `rp_decision` (enum, `include/request_policy.h:21`)
- `rp_host_of` (function, `include/request_policy.h:30`) `int rp_host_of(const char *url, char *out, size_t out_size);` - Lowercased host of an absolute URL into out. Returns 0 on success, -1 if no * host can be parsed or
- `rp_site_of` (function, `include/request_policy.h:34`) `int rp_site_of(const char *host, char *out, size_t out_size);` - Registrable domain ("site") of a host into out (simplified public-suffix * rule). Returns 0 on succe
- `rp_same_site` (function, `include/request_policy.h:37`) `int rp_same_site(const char *top_level_url, const char *request_url);` - Registrable domain ("site") of a host into out (simplified public-suffix * rule). Returns 0 on succe
- `content` (function, `include/text_shape.h:11`) `* TEXT is hostile remote content (sanitised UTF-8) and is fuzzed (make fuzz-tsh)`
- `FREEDOM_TEXT_SHAPE_H` (macro, `include/text_shape.h:19`) `#define FREEDOM_TEXT_SHAPE_H`
- `tsh_font` (struct, `include/text_shape.h:33`) - Font selector: a css_font_family bucket (CSS_FF_*) plus weight/slant flags. The engine matches the g
- `family` (type_alias, `include/text_shape.h:33`) `typedef struct tsh_font { int family;` - Font selector: a css_font_family bucket (CSS_FF_*) plus weight/slant flags. The engine matches the g
- `TSH_MAX_GLYPHS` (macro, `include/text_shape.h:40`) `#define TSH_MAX_GLYPHS`
- `TSH_MAX_TEXT` (macro, `include/text_shape.h:41`) `#define TSH_MAX_TEXT`
- `tsh_status` (enum, `include/text_shape.h:43`)
- `tsh_ready` (function, `include/text_shape.h:52`) `int tsh_ready(void);` - 1 once a fallback (sans) font resolves; lazily initialises on first call. * 0 means no font backend:

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 24
- Cross-boundary resolved imports (EXTRACTED): 20

## Connections

- [EXTRACTED] depends_on community 1 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 2 <-> 4 (strength 0.9): Extracted import edge crosses communities: src/css.c imports include/webfont.h.
- [EXTRACTED] depends_on community 3 <-> 4 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/request_policy.h.
- [EXTRACTED] depends_on community 0 <-> 4 (strength 0.9): Extracted import edge crosses communities: src/tab.c imports include/data_url.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_policy.c` (presentation) -> `include/data_url.h` (data_access)

## Open Questions

- Why do 19 file(s) lack file-level docs (e.g. `fuzz/fuzz_data_url.c`)? What purpose do they serve?
- What would break if the most connected file in include: text_shape changed?
- Should include: text_shape be split, given cohesion 0.55?

## Sources

- `fuzz/fuzz_data_url.c`
- `fuzz/fuzz_text_shape.c`
- `fuzz/fuzz_webfont.c`
- `include/data_url.h`
- `include/psl_data.h`
- `include/request_policy.h`
- `include/text_shape.h`
- `include/webfont.h`
- `include/webfont_load.h`
- `src/data_url.c`
- `src/render_policy.c`
- `src/request_policy.c`
- `src/text_shape.c`
- `src/webfont.c`
- `src/webfont_load.c`
- `tests/test_data_url.c`
- `tests/test_request_policy.c`
- `tests/test_text_shape.c`
- `tests/test_webfont.c`
- `tests/test_webfont_load.c`
