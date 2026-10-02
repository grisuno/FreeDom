# src

*Community 10 | 20 files | cohesion 0.42*

## Definition

This community groups 20 file(s) rooted at `src` with dominant language c (cohesion 0.42). Central symbols: `CSS_PAGE`, `EXT_PAGE`, `FM_BODY_MAX`, `FM_CONTENT_TYPE_URLENCODED`, `FM_MAX_FIELDS`, `FM_URL_MAX`, `FP_ACCEPT_HEADER_NAV`, `FP_ACCEPT_LANGUAGE`. Core file: `tests/test_tab.c` (114 symbols). Documented purpose: Private to js_dom.c / js_location.c: the dom.histTarget native lives with the.

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_url.c` | c | utility | 2 | no |
| `fuzz/fuzz_web_storage.c` | c | data_access | 0 | no |
| `include/anti_fp.h` | h | utility | 35 | no |
| `include/form.h` | h | data_access | 12 | no |
| `include/url.h` | h | utility | 14 | no |
| `include/web_storage.h` | h | data_access | 13 | no |
| `src/anti_fp.c` | c | utility | 23 | no |
| `src/form.c` | c | data_access | 8 | no |
| `src/js_location.c` | c | utility | 6 | no |
| `src/js_location_internal.h` | h | utility | 2 | yes |
| `src/js_trusted.c` | c | utility | 14 | no |
| `src/link_nav.c` | c | utility | 10 | no |
| `src/secure_fetch.c` | c | utility | 61 | no |
| `src/url.c` | c | utility | 29 | no |
| `src/web_storage.c` | c | data_access | 17 | no |
| `tests/test_anti_fp.c` | c | testing | 15 | no |
| `tests/test_form.c` | c | testing | 20 | no |
| `tests/test_tab.c` | c | testing | 114 | no |
| `tests/test_url.c` | c | testing | 49 | no |
| `tests/test_web_storage.c` | c | testing | 9 | no |

## Key Symbols

- `check_split` (function, `fuzz/fuzz_url.c:31`) `static void check_split(const char *url)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_url.c:59`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_ANTI_FP_H` (macro, `include/anti_fp.h:2`) `#define FREEDOM_ANTI_FP_H`
- `FP_TIMER_RESOLUTION_MS` (macro, `include/anti_fp.h:22`) `#define FP_TIMER_RESOLUTION_MS`
- `FP_USER_AGENT` (macro, `include/anti_fp.h:31`) `#define FP_USER_AGENT`
- `FP_ACCEPT_LANGUAGE` (macro, `include/anti_fp.h:33`) `#define FP_ACCEPT_LANGUAGE`
- `FP_ACCEPT_LANGUAGE_HEADER` (macro, `include/anti_fp.h:34`) `#define FP_ACCEPT_LANGUAGE_HEADER`
- `FP_ACCEPT_HEADER_NAV` (macro, `include/anti_fp.h:40`) `#define FP_ACCEPT_HEADER_NAV`
- `FP_SEC_FETCH_DEST_NAV` (macro, `include/anti_fp.h:45`) `#define FP_SEC_FETCH_DEST_NAV`
- `FP_SEC_FETCH_MODE_NAV` (macro, `include/anti_fp.h:46`) `#define FP_SEC_FETCH_MODE_NAV`
- `FP_SEC_FETCH_SITE_NONE` (macro, `include/anti_fp.h:47`) `#define FP_SEC_FETCH_SITE_NONE`
- `FP_SEC_FETCH_USER_ON` (macro, `include/anti_fp.h:48`) `#define FP_SEC_FETCH_USER_ON`
- `fp_timer_resolution_ms` (function, `include/anti_fp.h:52`) `uint64_t fp_timer_resolution_ms(void);`
- `fp_coarsen_time_ms` (function, `include/anti_fp.h:53`) `uint64_t fp_coarsen_time_ms(uint64_t raw_ms);`
- `fp_user_agent` (function, `include/anti_fp.h:57`) `const char *fp_user_agent(void);`
- `fp_accept_language` (function, `include/anti_fp.h:58`) `const char *fp_accept_language(void);`
- `fp_accept_language_header` (function, `include/anti_fp.h:59`) `const char *fp_accept_language_header(void);` - #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_F
- `fp_timezone` (function, `include/anti_fp.h:60`) `const char *fp_timezone(void);` - #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH
- `fp_platform` (function, `include/anti_fp.h:61`) `const char *fp_platform(void);` - #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse gran
- `fp_vendor` (function, `include/anti_fp.h:62`) `const char *fp_vendor(void);` - #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against high-resolution timing
- `fp_hardware_concurrency` (function, `include/anti_fp.h:63`) `int fp_hardware_concurrency(void);` - /* --- clocks: coarse granularity against high-resolution timing --- uint64_t fp_timer_resolution_ms
- `fp_device_memory_gb` (function, `include/anti_fp.h:64`) `int fp_device_memory_gb(void);`
- `properties` (function, `include/anti_fp.h:67`) `* Legacy navigator properties (Hito 30b): normalized Firefox values shared by *`
- `fp_app_code_name` (function, `include/anti_fp.h:71`) `const char *fp_app_code_name(void);` - Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network l
- `fp_product` (function, `include/anti_fp.h:72`) `const char *fp_product(void);` - Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network l
- `fp_app_name` (function, `include/anti_fp.h:73`) `const char *fp_app_name(void);` - Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network l
- `fp_product_sub` (function, `include/anti_fp.h:74`) `const char *fp_product_sub(void);` - Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network l
- `fp_oscpu` (function, `include/anti_fp.h:75`) `const char *fp_oscpu(void);` - Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network l
- `fp_build_id` (function, `include/anti_fp.h:76`) `const char *fp_build_id(void);` - Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network l
- `fp_max_touch_points` (function, `include/anti_fp.h:77`) `int fp_max_touch_points(void);` - Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network l

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 19
- Cross-boundary resolved imports (EXTRACTED): 26

## Connections

- [EXTRACTED] depends_on community 2 <-> 10 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_js_dom.c imports include/web_storage.h.
- [EXTRACTED] depends_on community 10 <-> 3 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_url.c imports include/link_nav.h.
- [EXTRACTED] depends_on community 0 <-> 10 (strength 0.9): Extracted import edge crosses communities: src/render_doc.c imports include/url.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/form.h` (data_access)
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [dataflow DEAD_STORE] `src/link_nav.c:58` `ci_prefix` `hash`: `hash` assigned at line 58 but never read afterwards.

## Open Questions

- Why do 19 file(s) lack file-level docs (e.g. `fuzz/fuzz_url.c`)? What purpose do they serve?
- What would break if the most connected file in src changed?
- Should src be split, given cohesion 0.42?

## Sources

- `fuzz/fuzz_url.c`
- `fuzz/fuzz_web_storage.c`
- `include/anti_fp.h`
- `include/form.h`
- `include/url.h`
- `include/web_storage.h`
- `src/anti_fp.c`
- `src/form.c`
- `src/js_location.c`
- `src/js_location_internal.h`
- `src/js_trusted.c`
- `src/link_nav.c`
- `src/secure_fetch.c`
- `src/url.c`
- `src/web_storage.c`
- `tests/test_anti_fp.c`
- `tests/test_form.c`
- `tests/test_tab.c`
- `tests/test_url.c`
- `tests/test_web_storage.c`
