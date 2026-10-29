# src: local_store

*Community 6 | 16 files | cohesion 0.79*

## Definition

This community groups 16 file(s) rooted at `src` with dominant language c (cohesion 0.79). Central symbols: `FREEDOM_CACHED_FETCH_H`, `FREEDOM_DISK_STORE_H`, `FREEDOM_HTTP_CACHE_H`, `FREEDOM_LOCAL_STORE_H`, `FREEDOM_PQ_SEAL_H`, `HC_EVICT_EVERY`, `HC_HEURISTIC_CAP`, `HC_KEY_FILE`. Core file: `src/local_store.c` (347 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/cached_fetch.h` | h | infrastructure | 4 | no |
| `include/disk_store.h` | h | data_access | 3 | no |
| `include/http_cache.h` | h | presentation | 19 | no |
| `include/local_store.h` | h | data_access | 11 | no |
| `include/pq_seal.h` | h | utility | 8 | no |
| `src/cached_fetch.c` | c | infrastructure | 14 | no |
| `src/disk_store.c` | c | data_access | 6 | no |
| `src/http_cache.c` | c | presentation | 38 | no |
| `src/local_store.c` | c | data_access | 347 | no |
| `src/pq_seal.c` | c | utility | 11 | no |
| `src/profile.c` | c | utility | 9 | no |
| `tests/test_cached_fetch.c` | c | testing | 14 | no |
| `tests/test_disk_store.c` | c | testing | 16 | no |
| `tests/test_http_cache.c` | c | testing | 17 | no |
| `tests/test_local_store.c` | c | testing | 18 | no |
| `tests/test_pq_seal.c` | c | testing | 7 | no |

## Key Symbols

- `FREEDOM_CACHED_FETCH_H` (macro, `include/cached_fetch.h:2`) `#define FREEDOM_CACHED_FETCH_H`
- `cf_set_store` (function, `include/cached_fetch.h:30`) `void cf_set_store(hc_store *store);` - Cache-aware GET. `partition` is the top-level site (double keying). On a fresh hit the response is r
- `cf_store` (function, `include/cached_fetch.h:31`) `hc_store *cf_store(void);`
- `cf_attach_redirect_memory` (function, `include/cached_fetch.h:38`) `void cf_attach_redirect_memory(hc_store *store);` - conditional GET is sent to the stored FINAL url and a 304 serves the stored body. sf_status cf_get_w
- `FREEDOM_DISK_STORE_H` (macro, `include/disk_store.h:2`) `#define FREEDOM_DISK_STORE_H`
- `ds_status` (enum, `include/disk_store.h:25`)
- `ds_free` (function, `include/disk_store.h:47`) `void ds_free(uint8_t *buf, size_t len);` - Reads and decrypts path. Wrong key / tampering => DS_ERR_AUTH (no plaintext). * *out is owned; relea
- `FREEDOM_HTTP_CACHE_H` (macro, `include/http_cache.h:2`) `#define FREEDOM_HTTP_CACHE_H`
- `HC_VAL_MAX` (macro, `include/http_cache.h:20`) `#define HC_VAL_MAX`
- `HC_URL_MAX` (macro, `include/http_cache.h:21`) `#define HC_URL_MAX`
- `HC_TYPE_MAX` (macro, `include/http_cache.h:22`) `#define HC_TYPE_MAX`
- `HC_MAX_ENTRY` (macro, `include/http_cache.h:23`) `#define HC_MAX_ENTRY`
- `HC_MAX_TOTAL` (macro, `include/http_cache.h:24`) `#define HC_MAX_TOTAL`
- `HC_REDIRECT_TTL` (macro, `include/http_cache.h:25`) `#define HC_REDIRECT_TTL`
- `HC_HEURISTIC_CAP` (macro, `include/http_cache.h:26`) `#define HC_HEURISTIC_CAP`
- `hc_status` (enum, `include/http_cache.h:28`)
- `hc_class` (enum, `include/http_cache.h:38`)
- `final_url` (type_alias, `include/http_cache.h:43`) `typedef struct hc_meta { char final_url[HC_URL_MAX];`
- `hc_meta` (struct, `include/http_cache.h:44`)
- `hc_parse_http_date` (function, `include/http_cache.h:56`) `time_t hc_parse_http_date(const char *s);` - } hc_class; typedef struct hc_meta { char   final_url[HC_URL_MAX]; char   content_type[HC_TYPE_MAX];
- `by` (function, `include/http_cache.h:59`) `* something to reuse it by (validator, max-age or Expires). */ int hc_storable(l`
- `hc_lifetime` (function, `include/http_cache.h:63`) `long hc_lifetime(const hc_meta *m);` - True when a response may be stored: 200, no `no-store`, body within HC_MAX_ENTRY, and * something to
- `hc_store` (type_alias, `include/http_cache.h:66`) `typedef struct hc_store hc_store;`
- `hc_close` (function, `include/http_cache.h:72`) `void hc_close(hc_store *s);`
- `hc_body_free` (function, `include/http_cache.h:78`) `void hc_body_free(uint8_t *body, size_t len);`
- `hc_clear` (function, `include/http_cache.h:84`) `void hc_clear(hc_store *s);` - ML-KEM keys and empties the directory when the sealed key cannot be opened. hc_status hc_open(hc_sto
- `FREEDOM_LOCAL_STORE_H` (macro, `include/local_store.h:2`) `#define FREEDOM_LOCAL_STORE_H`
- `LS_KEY_LEN` (macro, `include/local_store.h:26`) `#define LS_KEY_LEN`
- `LS_SALT_LEN` (macro, `include/local_store.h:27`) `#define LS_SALT_LEN`
- `LS_NONCE_LEN` (macro, `include/local_store.h:28`) `#define LS_NONCE_LEN`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 19
- Cross-boundary resolved imports (EXTRACTED): 5

## Connections

- [EXTRACTED] depends_on community 0 <-> 6 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/cached_fetch.h.
- [EXTRACTED] depends_on community 6 <-> 7 (strength 0.9): Extracted import edge crosses communities: include/cached_fetch.h imports include/secure_fetch.h.
- [EXTRACTED] depends_on community 6 <-> 5 (strength 0.9): Extracted import edge crosses communities: src/disk_store.c imports include/util.h.

## Risks

- [layer strict] `include/http_cache.h` (presentation) -> `include/local_store.h` (data_access)
- [layer strict] `src/http_cache.c` (presentation) -> `include/disk_store.h` (data_access)
- [layer strict] `tests/test_http_cache.c` (testing) -> `include/http_cache.h` (presentation)

## Open Questions

- Why do 16 file(s) lack file-level docs (e.g. `include/cached_fetch.h`)? What purpose do they serve?
- What would break if the most connected file in src: local_store changed?
- Should src: local_store be split, given cohesion 0.79?

## Sources

- `include/cached_fetch.h`
- `include/disk_store.h`
- `include/http_cache.h`
- `include/local_store.h`
- `include/pq_seal.h`
- `src/cached_fetch.c`
- `src/disk_store.c`
- `src/http_cache.c`
- `src/local_store.c`
- `src/pq_seal.c`
- `src/profile.c`
- `tests/test_cached_fetch.c`
- `tests/test_disk_store.c`
- `tests/test_http_cache.c`
- `tests/test_local_store.c`
- `tests/test_pq_seal.c`
