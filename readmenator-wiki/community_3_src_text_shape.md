# src: text_shape

*Community 3 | 54 files | cohesion 0.58*

## Definition

This community groups 54 file(s) rooted at `src` with dominant language c (cohesion 0.58). Central symbols: `BLOCKED`, `CSS_DROPS_REPORT_MAX`, `DU_MAX_ENCODED_LEN`, `EXIT_ERROR`, `EXIT_OK`, `EXIT_USAGE`, `FREEDOM_DATA_URL_H`, `FREEDOM_HLS_H`. Core file: `src/text_shape.c` (75 symbols). Documented purpose: test_wl_display — CMocka suite for the pure Wayland socket picker..

## Files

### `src` (19 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/data_url.c` | c | data_access | 11 | no |
| `src/freedom.c` | c | utility | 50 | no |
| `src/hls.c` | c | utility | 20 | no |
| `src/host_conf.c` | c | utility | 9 | no |
| `src/hostblock.c` | c | utility | 19 | no |
| `src/js_policy.c` | c | business_logic | 6 | no |
| `src/link_nav.c` | c | utility | 10 | no |

### `include` (18 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/data_url.h` | h | data_access | 7 | no |
| `include/hls.h` | h | utility | 11 | no |
| `include/host_conf.h` | h | utility | 9 | no |
| `include/hostblock.h` | h | utility | 10 | no |
| `include/js_policy.h` | h | business_logic | 7 | no |
| `include/link_nav.h` | h | utility | 11 | no |
| `include/media_decoder.h` | h | utility | 12 | no |

### `tests` (17 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_data_url.c` | c | testing | 26 | no |
| `tests/test_hls.c` | c | testing | 25 | no |
| `tests/test_host_conf.c` | c | testing | 8 | no |
| `tests/test_hostblock.c` | c | testing | 24 | no |
| `tests/test_js_policy.c` | c | testing | 5 | no |
| `tests/test_link_nav.c` | c | testing | 22 | no |

*... and 34 more files in this community.*


## Key Symbols

- `FREEDOM_DATA_URL_H` (macro, `include/data_url.h:2`) `#define FREEDOM_DATA_URL_H`
- `allocation` (function, `include/data_url.h:21`) `* * du_base64_payload does no allocation (it only slices the caller's url string`
- `du_status` (enum, `include/data_url.h:27`)
- `DU_MAX_ENCODED_LEN` (macro, `include/data_url.h:43`) `#define DU_MAX_ENCODED_LEN`
- `du_is_data_url` (function, `include/data_url.h:46`) `int du_is_data_url(const char *url);` - 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding
- `worker` (function, `include/data_url.h:59`) `* the confined worker (du_decode). */ du_status du_shape_ok(const char *url);`
- `closed` (function, `include/data_url.h:65`) `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/ou`
- `FREEDOM_HLS_H` (macro, `include/hls.h:2`) `#define FREEDOM_HLS_H`
- `hls_status` (enum, `include/hls.h:21`)
- `hls_segment` (struct, `include/hls.h:29`) - or variant info. URLs are returned as they appear in the playlist (may be relative to the playlist's
- `hls_variant` (struct, `include/hls.h:36`) - HLS_OK = 0, HLS_ERR_NULL_ARG, HLS_ERR_PARSE,      /* not a valid m3u8 playlist HLS_ERR_OOM } hls_sta
- `hls_playlist` (struct, `include/hls.h:45`) - size_t url_len; double duration;     /* segment duration in seconds (from #EXTINF) } hls_segment; /*
- `hls_select_variant` (function, `include/hls.h:65`) `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h);` - Selects the best variant from a multi-variant playlist. Returns the index of the chosen variant, or
- `resolved` (function, `include/hls.h:68`) `* Writes the absolute URL into resolved (bounded by resolved_sz). Returns the *`
- `hls_playlist_free` (function, `include/hls.h:74`) `void hls_playlist_free(hls_playlist *pl);` - Resolves a (possibly relative) segment URL against the playlist base URL. Writes the absolute URL in
- `media` (function, `include/hls.h:77`) `* media (non-2xx status, HTML/text error body, empty). Recognises MPEG-TS (also`
- `HLS_MAX_MIRRORS` (macro, `include/hls.h:83`) `#define HLS_MAX_MIRRORS`
- `domain` (function, `include/hls.h:87`) `* domain (everything after the first label). Writes NUL-terminated into out and`
- `FREEDOM_HOST_CONF_H` (macro, `include/host_conf.h:2`) `#define FREEDOM_HOST_CONF_H`
- `HCF_MAX_DIRS` (macro, `include/host_conf.h:15`) `#define HCF_MAX_DIRS`
- `HCF_PATH_MAX` (macro, `include/host_conf.h:16`) `#define HCF_PATH_MAX`
- `HCF_MAX_FILE_BYTES` (macro, `include/host_conf.h:18`) `#define HCF_MAX_FILE_BYTES`
- `hcf_dirs` (struct, `include/host_conf.h:20`)
- `hcf_search_dirs` (function, `include/host_conf.h:28`) `void hcf_search_dirs(const char *env, const char *home, hcf_dirs *out);` - Pure. Fills out with, in order: env (when non-empty), home + "/.config/freedom" (when home is non-em
- `hcf_search_dirs_from_env` (function, `include/host_conf.h:31`) `void hcf_search_dirs_from_env(hcf_dirs *out);` - Pure. Fills out with, in order: env (when non-empty), home + "/.config/freedom" (when home is non-em
- `hcf_load_filter` (function, `include/host_conf.h:35`) `hb_set *hcf_load_filter(const hcf_dirs *dirs);` - block.conf (BLOCK) + allow.conf (ALLOW) from every directory, cumulative. Missing or * unreadable fi
- `hcf_load_allowlist` (function, `include/host_conf.h:39`) `hb_set *hcf_load_allowlist(const hcf_dirs *dirs, const char *fname);` - One file (js.conf, allow.conf, ...) from every directory as an ALLOW list. NULL only on * OOM or a N
- `FREEDOM_HOSTBLOCK_H` (macro, `include/hostblock.h:2`) `#define FREEDOM_HOSTBLOCK_H`
- `hb_set` (type_alias, `include/hostblock.h:29`) `typedef struct hb_set hb_set;` - caller reads the list files and passes their text in; this module parses them into hash tables and d
- `hb_list` (enum, `include/hostblock.h:32`)

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 64
- Cross-boundary resolved imports (EXTRACTED): 47

## Connections

- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui_internal.h imports include/video_controls.h.
- [EXTRACTED] depends_on community 3 <-> 4 (strength 0.9): Extracted import edge crosses communities: include/webcaps.h imports include/render_policy.h.
- [EXTRACTED] depends_on community 3 <-> 2 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/html_parse.h.
- [EXTRACTED] depends_on community 3 <-> 5 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/identity.h.
- [EXTRACTED] depends_on community 3 <-> 9 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/prefetch.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_policy.c` (presentation) -> `include/data_url.h` (data_access)

## Open Questions

- Why do 53 file(s) lack file-level docs (e.g. `include/data_url.h`)? What purpose do they serve?
- What would break if the most connected file in src: text_shape changed?
- Should src: text_shape be split, given cohesion 0.58?

## Sources

- `include/data_url.h`
- `include/hls.h`
- `include/host_conf.h`
- `include/hostblock.h`
- `include/js_policy.h`
- `include/link_nav.h`
- `include/media_decoder.h`
- `include/net_realm.h`
- `include/perf_trace.h`
- `include/psl_data.h`
- `include/request_policy.h`
- `include/text_shape.h`
- `include/tls_impersonate.h`
- `include/video_controls.h`
- `include/webcaps.h`
- `include/webfont.h`
- `include/webfont_load.h`
- `include/wl_display.h`
- `src/data_url.c`
- `src/freedom.c`
- *... and 34 more*
