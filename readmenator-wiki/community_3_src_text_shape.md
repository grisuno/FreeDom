# src: text_shape

*Community 3 | 39 files | cohesion 0.55*

## Definition

This community groups 39 file(s) rooted at `src` with dominant language c (cohesion 0.55). Central symbols: `BLOCKED`, `CSS_DROPS_REPORT_MAX`, `DU_MAX_ENCODED_LEN`, `EXIT_ERROR`, `EXIT_OK`, `EXIT_USAGE`, `FREEDOM_DATA_URL_H`, `FREEDOM_HLS_H`. Core file: `src/text_shape.c` (61 symbols). Documented purpose: test_wl_display — CMocka suite for the pure Wayland socket picker..

## Files

### `src` (14 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/data_url.c` | c | data_access | 10 | no |
| `src/freedom.c` | c | utility | 48 | no |
| `src/hls.c` | c | utility | 10 | no |
| `src/host_conf.c` | c | utility | 9 | no |
| `src/hostblock.c` | c | utility | 18 | no |
| `src/net_realm.c` | c | utility | 10 | no |
| `src/perf_trace.c` | c | utility | 12 | no |

### `include` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/data_url.h` | h | data_access | 6 | no |
| `include/hls.h` | h | utility | 8 | no |
| `include/host_conf.h` | h | utility | 9 | no |
| `include/hostblock.h` | h | utility | 10 | no |
| `include/net_realm.h` | h | utility | 10 | no |
| `include/perf_trace.h` | h | utility | 17 | no |
| `include/psl_data.h` | h | data_access | 7 | no |

### `tests` (12 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_data_url.c` | c | testing | 26 | no |
| `tests/test_hls.c` | c | testing | 16 | no |
| `tests/test_host_conf.c` | c | testing | 8 | no |
| `tests/test_hostblock.c` | c | testing | 22 | no |
| `tests/test_net_realm.c` | c | testing | 13 | no |
| `tests/test_perf_trace.c` | c | testing | 12 | no |

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
- `hb_decision` (enum, `include/hostblock.h:37`)
- `hb_status` (enum, `include/hostblock.h:42`)
- `hb_new` (function, `include/hostblock.h:49`) `hb_set *hb_new(void);` - } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /*
- `hb_free` (function, `include/hostblock.h:52`) `void hb_free(hb_set *s);` - HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 47
- Cross-boundary resolved imports (EXTRACTED): 38

## Connections

- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: src/css.c imports include/webfont.h.
- [EXTRACTED] depends_on community 3 <-> 5 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/dom_debug.h.
- [EXTRACTED] depends_on community 3 <-> 2 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/html_parse.h.
- [EXTRACTED] depends_on community 3 <-> 7 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/identity.h.
- [EXTRACTED] depends_on community 3 <-> 8 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/prefetch.h.
- [EXTRACTED] depends_on community 3 <-> 4 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/media_decoder.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_policy.c` (presentation) -> `include/data_url.h` (data_access)
- [dataflow UNCHECKED_ALLOC] `src/freedom.c:528` `headless_fetch` `oct`: Result of allocator stored in `oct` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `src/hostblock.c:145` `hb_new` `s`: Result of allocator stored in `s` is never checked against NULL.

## Open Questions

- Why do 38 file(s) lack file-level docs (e.g. `include/data_url.h`)? What purpose do they serve?
- What would break if the most connected file in src: text_shape changed?
- Should src: text_shape be split, given cohesion 0.55?

## Sources

- `include/data_url.h`
- `include/hls.h`
- `include/host_conf.h`
- `include/hostblock.h`
- `include/net_realm.h`
- `include/perf_trace.h`
- `include/psl_data.h`
- `include/request_policy.h`
- `include/text_shape.h`
- `include/tls_impersonate.h`
- `include/webfont.h`
- `include/webfont_load.h`
- `include/wl_display.h`
- `src/data_url.c`
- `src/freedom.c`
- `src/hls.c`
- `src/host_conf.c`
- `src/hostblock.c`
- `src/net_realm.c`
- `src/perf_trace.c`
- *... and 19 more*
