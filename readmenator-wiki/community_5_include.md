# include

*Community 5 | 4 files | cohesion 0.60*

## Definition

This community groups 4 file(s) rooted at `include` with dominant language c (cohesion 0.60). Central symbols: `FREEDOM_TLS_IMPERSONATE_H`, `TI_MAGIC`, `TI_MAX_BODY`, `TI_MAX_CHAIN`, `TI_MAX_GROUP`, `TI_MAX_HEADERS`, `TI_MAX_METHOD`, `TI_MAX_RESP_BODY`. Core file: `include/tls_impersonate.h` (22 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_tls_impersonate.c` | c | utility | 0 | no |
| `include/tls_impersonate.h` | h | utility | 22 | no |
| `src/tls_impersonate.c` | c | utility | 20 | no |
| `tests/test_tls_impersonate.c` | c | testing | 11 | no |

## Key Symbols

- `FREEDOM_TLS_IMPERSONATE_H` (macro, `include/tls_impersonate.h:2`) `#define FREEDOM_TLS_IMPERSONATE_H`
- `chain` (function, `include/tls_impersonate.h:29`) `* * The response carries the peer certificate chain (DER) and the negotiated gro`
- `ti_profile` (enum, `include/tls_impersonate.h:38`) - Browser profile imitated on the wire. Owner decision (2026-07-12): TI_PROFILE_CHROME_CLASSIC — maxim
- `ti_should_impersonate` (function, `include/tls_impersonate.h:52`) `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled, int host_i` - The triple opt-in gate (pure). Returns 1 IFF all three signals are set: host_in_allowlist  — an expl
- `TI_MAGIC` (macro, `include/tls_impersonate.h:56`) `#define TI_MAGIC`
- `TI_MAX_URL` (macro, `include/tls_impersonate.h:57`) `#define TI_MAX_URL`
- `TI_MAX_METHOD` (macro, `include/tls_impersonate.h:58`) `#define TI_MAX_METHOD`
- `TI_MAX_HEADERS` (macro, `include/tls_impersonate.h:59`) `#define TI_MAX_HEADERS`
- `TI_MAX_BODY` (macro, `include/tls_impersonate.h:60`) `#define TI_MAX_BODY`
- `TI_MAX_RESP_HDR` (macro, `include/tls_impersonate.h:61`) `#define TI_MAX_RESP_HDR`
- `TI_MAX_RESP_BODY` (macro, `include/tls_impersonate.h:62`) `#define TI_MAX_RESP_BODY`
- `TI_MAX_CHAIN` (macro, `include/tls_impersonate.h:63`) `#define TI_MAX_CHAIN`
- `TI_MAX_GROUP` (macro, `include/tls_impersonate.h:64`) `#define TI_MAX_GROUP`
- `ti_req` (struct, `include/tls_impersonate.h:68`) - Request: parent -> helper. Pointers are borrowed by ti_encode_req (not copied); * ti_decode_req allo
- `ti_resp` (struct, `include/tls_impersonate.h:78`) - Request: parent -> helper. Pointers are borrowed by ti_encode_req (not copied); * ti_decode_req allo
- `status` (type_alias, `include/tls_impersonate.h:78`) `typedef struct ti_resp { long status;` - Request: parent -> helper. Pointers are borrowed by ti_encode_req (not copied); * ti_decode_req allo
- `success` (function, `include/tls_impersonate.h:93`) `* ti_decode_* returns 0 on success (out fully populated), <0 on any malformed, *`
- `ti_decode_req` (function, `include/tls_impersonate.h:97`) `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out);`
- `ti_req_free` (function, `include/tls_impersonate.h:98`) `void ti_req_free(ti_req *r);`
- `ti_encode_resp` (function, `include/tls_impersonate.h:100`) `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap);`
- `ti_decode_resp` (function, `include/tls_impersonate.h:101`) `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out);`
- `ti_resp_free` (function, `include/tls_impersonate.h:102`) `void ti_resp_free(ti_resp *r);`
- `ti_should_impersonate` (function, `src/tls_impersonate.c:18`) `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,`
- `bounded_len` (function, `src/tls_impersonate.c:25`) `static size_t bounded_len(const char *s, size_t max)`
- `ti_wr` (struct, `src/tls_impersonate.c:33`)
- `put_u8` (function, `src/tls_impersonate.c:35`) `static void put_u8(ti_wr *w, uint8_t v)`
- `put_u32` (function, `src/tls_impersonate.c:40`) `static void put_u32(ti_wr *w, uint32_t v)`
- `put_u64` (function, `src/tls_impersonate.c:48`) `static void put_u64(ti_wr *w, uint64_t v)`
- `put_blob` (function, `src/tls_impersonate.c:53`) `static void put_blob(ti_wr *w, const uint8_t *b, size_t n)`
- `ti_rd` (struct, `src/tls_impersonate.c:63`)

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 3
- Cross-boundary resolved imports (EXTRACTED): 2

## Connections

- [EXTRACTED] depends_on community 0 <-> 5 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/tls_impersonate.h.
- [INFERRED] shares_context community 1 <-> 5 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (include) and community 5 (include).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 4 file(s) lack file-level docs (e.g. `fuzz/fuzz_tls_impersonate.c`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.60?

## Sources

- `fuzz/fuzz_tls_impersonate.c`
- `include/tls_impersonate.h`
- `src/tls_impersonate.c`
- `tests/test_tls_impersonate.c`
