# src: text_shape

*Community 2 | 39 files | cohesion 0.53*

## Definition

This community groups 39 file(s) rooted at `src` with dominant language c (cohesion 0.53). Central symbols: `BLOCKED`, `CSS_DROPS_REPORT_MAX`, `DU_MAX_ENCODED_LEN`, `EXIT_ERROR`, `EXIT_OK`, `EXIT_USAGE`, `FREEDOM_DATA_URL_H`, `FREEDOM_HLS_H`. Core file: `src/text_shape.c` (68 symbols). Documented purpose: test_wl_display — CMocka suite for the pure Wayland socket picker..

## Files

### `src` (14 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/data_url.c` | c | data_access | 10 | no |
| `src/freedom.c` | c | utility | 50 | no |
| `src/hls.c` | c | utility | 10 | no |
| `src/js_policy.c` | c | business_logic | 6 | no |
| `src/net_realm.c` | c | utility | 10 | no |
| `src/perf_trace.c` | c | utility | 12 | no |
| `src/render_policy.c` | c | presentation | 5 | no |

### `include` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/data_url.h` | h | data_access | 6 | no |
| `include/hls.h` | h | utility | 8 | no |
| `include/js_policy.h` | h | business_logic | 7 | no |
| `include/net_realm.h` | h | utility | 10 | no |
| `include/perf_trace.h` | h | utility | 17 | no |
| `include/psl_data.h` | h | data_access | 7 | no |
| `include/request_policy.h` | h | business_logic | 11 | no |

### `tests` (12 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_data_url.c` | c | testing | 26 | no |
| `tests/test_hls.c` | c | testing | 16 | no |
| `tests/test_js_policy.c` | c | testing | 5 | no |
| `tests/test_net_realm.c` | c | testing | 13 | no |
| `tests/test_perf_trace.c` | c | testing | 12 | no |
| `tests/test_request_policy.c` | c | testing | 17 | no |

*... and 19 more files in this community.*


## Key Symbols

- `FREEDOM_DATA_URL_H` (macro, `include/data_url.h:2`) `#define FREEDOM_DATA_URL_H`
- `allocation` (function, `include/data_url.h:21`) `* * du_base64_payload does no allocation (it only slices the caller's url string`
- `du_status` (enum, `include/data_url.h:27`)
- `DU_MAX_ENCODED_LEN` (macro, `include/data_url.h:43`) `#define DU_MAX_ENCODED_LEN`
- `du_is_data_url` (function, `include/data_url.h:46`) `int du_is_data_url(const char *url);` - 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding
- `closed` (function, `include/data_url.h:59`) `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/ou`
- `FREEDOM_HLS_H` (macro, `include/hls.h:2`) `#define FREEDOM_HLS_H`
- `hls_status` (enum, `include/hls.h:21`)
- `hls_segment` (struct, `include/hls.h:29`) - or variant info. URLs are returned as they appear in the playlist (may be relative to the playlist's
- `hls_variant` (struct, `include/hls.h:36`) - HLS_OK = 0, HLS_ERR_NULL_ARG, HLS_ERR_PARSE,      /* not a valid m3u8 playlist HLS_ERR_OOM } hls_sta
- `hls_playlist` (struct, `include/hls.h:45`) - size_t url_len; double duration;     /* segment duration in seconds (from #EXTINF) } hls_segment; /*
- `hls_select_variant` (function, `include/hls.h:65`) `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h);` - Selects the best variant from a multi-variant playlist. Returns the index of the chosen variant, or
- `resolved` (function, `include/hls.h:68`) `* Writes the absolute URL into resolved (bounded by resolved_sz). Returns the *`
- `hls_playlist_free` (function, `include/hls.h:74`) `void hls_playlist_free(hls_playlist *pl);` - Resolves a (possibly relative) segment URL against the playlist base URL. Writes the absolute URL in
- `FREEDOM_JS_POLICY_H` (macro, `include/js_policy.h:2`) `#define FREEDOM_JS_POLICY_H`
- `membership` (function, `include/js_policy.h:16`) `* membership (the allowlist itself is matched by the hostblock module, which * a`
- `jsp_mode` (enum, `include/js_policy.h:27`)
- `allowlist` (function, `include/js_policy.h:34`) `* allowlist (e.g. hb_is_allowlisted over js.conf). Fails closed: an unknown mode`
- `jsp_trusted` (function, `include/js_policy.h:45`) `bool jsp_trusted(bool js_enabled, int host_allowlisted);` - Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js
- `jsp_present_trusted` (function, `include/js_policy.h:54`) `bool jsp_present_trusted(int host_allowlisted);` - Presentation-trust (2026-07-11): a host EXPLICITLY on allow.conf (host_allowlisted, e.g. hb_is_allow
- `jsp_mode_str` (function, `include/js_policy.h:64`) `const char *jsp_mode_str(jsp_mode mode);` - Stable lowercase name of a mode ("off"/"allowlist"/"on"); an unknown value * yields "off" (fail clos
- `FREEDOM_NET_REALM_H` (macro, `include/net_realm.h:2`) `#define FREEDOM_NET_REALM_H`
- `nr_realm` (enum, `include/net_realm.h:29`)
- `nr_route` (enum, `include/net_realm.h:35`)
- `tor_enabled` (type_alias, `include/net_realm.h:41`) `typedef struct nr_config { int tor_enabled;`
- `nr_config` (struct, `include/net_realm.h:42`)
- `NR_ROUTE_BLOCKED` (function, `include/net_realm.h:57`) `* NR_ROUTE_BLOCKED (fail closed: never route what cannot be classified). A realm`
- `address` (function, `include/net_realm.h:62`) `* and encrypts by its address (the I2P destination / onion key), so http over it`
- `nr_realm_allows_http` (function, `include/net_realm.h:66`) `int nr_realm_allows_http(nr_realm r);` - 1 iff plain http:// is acceptable for this realm. An overlay realm authenticates and encrypts by its
- `nr_realm_name` (function, `include/net_realm.h:69`) `const char *nr_realm_name(nr_realm r);` - 1 iff plain http:// is acceptable for this realm. An overlay realm authenticates and encrypts by its

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 47
- Cross-boundary resolved imports (EXTRACTED): 41

## Connections

- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: include/webcaps.h imports include/render_policy.h.
- [EXTRACTED] depends_on community 4 <-> 2 (strength 0.9): Extracted import edge crosses communities: src/css.c imports include/webfont.h.
- [EXTRACTED] depends_on community 2 <-> 1 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/html_parse.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_policy.c` (presentation) -> `include/data_url.h` (data_access)
- [dataflow UNCHECKED_ALLOC] `src/freedom.c:561` `headless_fetch` `oct`: Result of allocator stored in `oct` is never checked against NULL.

## Open Questions

- Why do 38 file(s) lack file-level docs (e.g. `include/data_url.h`)? What purpose do they serve?
- What would break if the most connected file in src: text_shape changed?
- Should src: text_shape be split, given cohesion 0.53?

## Sources

- `include/data_url.h`
- `include/hls.h`
- `include/js_policy.h`
- `include/net_realm.h`
- `include/perf_trace.h`
- `include/psl_data.h`
- `include/request_policy.h`
- `include/text_shape.h`
- `include/tls_impersonate.h`
- `include/webcaps.h`
- `include/webfont.h`
- `include/webfont_load.h`
- `include/wl_display.h`
- `src/data_url.c`
- `src/freedom.c`
- `src/hls.c`
- `src/js_policy.c`
- `src/net_realm.c`
- `src/perf_trace.c`
- `src/render_policy.c`
- *... and 19 more*
