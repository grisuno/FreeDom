# include: secure_fetch

*Community 6 | 10 files | cohesion 0.62*

## Definition

This community groups 10 file(s) rooted at `tests` with dominant language c (cohesion 0.62). Central symbols: `CHECK`, `EXCLUDED`, `FP_ACCEPT_HEADER_NAV`, `FP_ACCEPT_LANGUAGE`, `FP_ACCEPT_LANGUAGE_HEADER`, `FP_SEC_FETCH_DEST_NAV`, `FP_SEC_FETCH_MODE_NAV`, `FP_SEC_FETCH_SITE_NONE`. Core file: `src/secure_fetch.c` (61 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/anti_fp.h` | h | utility | 35 | no |
| `include/secure_fetch.h` | h | utility | 38 | no |
| `include/ws_hub.h` | h | utility | 15 | no |
| `src/anti_fp.c` | c | utility | 23 | no |
| `src/secure_fetch.c` | c | utility | 61 | no |
| `src/ws_hub.c` | c | utility | 27 | no |
| `tests/itest_secure_fetch.c` | c | testing | 2 | no |
| `tests/test_anti_fp.c` | c | testing | 15 | no |
| `tests/test_secure_fetch.c` | c | testing | 50 | no |
| `tests/test_ws_hub.c` | c | testing | 13 | no |

## Key Symbols

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
- `fp_on_line` (function, `include/anti_fp.h:78`) `int fp_on_line(void);` - Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network l
- `fp_cookie_enabled` (function, `include/anti_fp.h:79`) `int fp_cookie_enabled(void);` - Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network l

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 10
- Cross-boundary resolved imports (EXTRACTED): 6

## Connections

- [EXTRACTED] depends_on community 1 <-> 6 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/secure_fetch.h.
- [EXTRACTED] depends_on community 3 <-> 6 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/secure_fetch.h.
- [EXTRACTED] depends_on community 0 <-> 6 (strength 0.9): Extracted import edge crosses communities: src/js_env.c imports include/anti_fp.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 10 file(s) lack file-level docs (e.g. `include/anti_fp.h`)? What purpose do they serve?
- What would break if the most connected file in include: secure_fetch changed?
- Should include: secure_fetch be split, given cohesion 0.62?

## Sources

- `include/anti_fp.h`
- `include/secure_fetch.h`
- `include/ws_hub.h`
- `src/anti_fp.c`
- `src/secure_fetch.c`
- `src/ws_hub.c`
- `tests/itest_secure_fetch.c`
- `tests/test_anti_fp.c`
- `tests/test_secure_fetch.c`
- `tests/test_ws_hub.c`
