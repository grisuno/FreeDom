# include: request_policy

*Community 7 | 9 files | cohesion 0.53*

## Definition

This community groups 9 file(s) rooted at `include` with dominant language c (cohesion 0.53). Central symbols: `DU_MAX_ENCODED_LEN`, `FREEDOM_DATA_URL_H`, `FREEDOM_PSL_DATA_H`, `FREEDOM_REQUEST_POLICY_H`, `RP_MAX_HOST`, `RP_MAX_LABELS`, `allocation`, `ascii_ws`. Core file: `tests/test_data_url.c` (26 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_data_url.c` | c | data_access | 1 | no |
| `include/data_url.h` | h | data_access | 6 | no |
| `include/psl_data.h` | h | data_access | 7 | no |
| `include/request_policy.h` | h | business_logic | 5 | no |
| `src/data_url.c` | c | data_access | 10 | no |
| `src/render_policy.c` | c | presentation | 5 | no |
| `src/request_policy.c` | c | business_logic | 11 | no |
| `tests/test_data_url.c` | c | testing | 26 | no |
| `tests/test_request_policy.c` | c | testing | 12 | no |

## Key Symbols

- `worker` (function, `fuzz/fuzz_data_url.c:6`) `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, nev`
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
- `rdp_caps_safe` (function, `src/render_policy.c:17`) `rdp_caps rdp_caps_safe(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 8
- Cross-boundary resolved imports (EXTRACTED): 7

## Connections

- [EXTRACTED] depends_on community 1 <-> 7 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 3 <-> 7 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/request_policy.h.
- [EXTRACTED] depends_on community 0 <-> 7 (strength 0.9): Extracted import edge crosses communities: src/tab.c imports include/data_url.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_policy.c` (presentation) -> `include/data_url.h` (data_access)

## Open Questions

- Why do 9 file(s) lack file-level docs (e.g. `fuzz/fuzz_data_url.c`)? What purpose do they serve?
- What would break if the most connected file in include: request_policy changed?
- Should include: request_policy be split, given cohesion 0.53?

## Sources

- `fuzz/fuzz_data_url.c`
- `include/data_url.h`
- `include/psl_data.h`
- `include/request_policy.h`
- `src/data_url.c`
- `src/render_policy.c`
- `src/request_policy.c`
- `tests/test_data_url.c`
- `tests/test_request_policy.c`
