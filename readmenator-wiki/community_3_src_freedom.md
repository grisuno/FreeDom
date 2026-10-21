# src: freedom

*Community 3 | 36 files | cohesion 0.55*

## Definition

This community groups 36 file(s) rooted at `src` with dominant language c (cohesion 0.55). Central symbols: `BLOCKED`, `CSS_DROPS_REPORT_MAX`, `EXIT_ERROR`, `EXIT_OK`, `EXIT_USAGE`, `FREEDOM_HLS_H`, `FREEDOM_HOSTBLOCK_H`, `FREEDOM_HOST_CONF_H`. Core file: `src/freedom.c` (47 symbols). Documented purpose: test_wl_display — CMocka suite for the pure Wayland socket picker..

## Files

### `src` (12 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/freedom.c` | c | utility | 47 | no |
| `src/hls.c` | c | utility | 10 | no |
| `src/host_conf.c` | c | utility | 9 | no |
| `src/hostblock.c` | c | utility | 18 | no |
| `src/js_policy.c` | c | business_logic | 6 | no |
| `src/link_nav.c` | c | utility | 10 | no |

### `include` (11 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/hls.h` | h | utility | 8 | no |
| `include/host_conf.h` | h | utility | 9 | no |
| `include/hostblock.h` | h | utility | 10 | no |
| `include/js_policy.h` | h | business_logic | 7 | no |
| `include/link_nav.h` | h | utility | 11 | no |
| `include/media_decoder.h` | h | utility | 12 | no |

### `tests` (11 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_hls.c` | c | testing | 16 | no |
| `tests/test_host_conf.c` | c | testing | 8 | no |
| `tests/test_hostblock.c` | c | testing | 22 | no |
| `tests/test_js_policy.c` | c | testing | 5 | no |
| `tests/test_link_nav.c` | c | testing | 22 | no |
| `tests/test_media_decoder.c` | c | testing | 6 | no |

### `fuzz` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_tls_impersonate.c` | c | utility | 0 | no |
| `fuzz/fuzz_url.c` | c | utility | 2 | no |

*... and 16 more files in this community.*


## Key Symbols

- `check_split` (function, `fuzz/fuzz_url.c:31`) `static void check_split(const char *url)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_url.c:59`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
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
- `walked` (function, `include/hostblock.h:65`) `* walked (the host, then without its first label, ...): any suffix on the allowl`
- `hb_is_allowlisted` (function, `include/hostblock.h:75`) `int hb_is_allowlisted(const hb_set *s, const char *host);` - 1 iff a domain suffix of host is explicitly on the allowlist (covers subdomains), else 0. Distinct f
- `hb_count` (function, `include/hostblock.h:79`) `size_t hb_count(const hb_set *s, hb_list list);` - Number of unique domains on the given list (for tests/diagnostics). 0 if s is * NULL.
- `FREEDOM_JS_POLICY_H` (macro, `include/js_policy.h:2`) `#define FREEDOM_JS_POLICY_H`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 37
- Cross-boundary resolved imports (EXTRACTED): 30

## Connections

- [EXTRACTED] depends_on community 3 <-> 0 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_url.c imports include/url.h.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/hostblock.h.
- [EXTRACTED] depends_on community 3 <-> 4 (strength 0.9): Extracted import edge crosses communities: include/webcaps.h imports include/render_policy.h.

## Risks

- [dataflow UNCHECKED_ALLOC] `src/freedom.c:509` `headless_fetch` `oct`: Result of allocator stored in `oct` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `src/hostblock.c:145` `hb_new` `s`: Result of allocator stored in `s` is never checked against NULL.

## Open Questions

- Why do 35 file(s) lack file-level docs (e.g. `fuzz/fuzz_tls_impersonate.c`)? What purpose do they serve?
- What would break if the most connected file in src: freedom changed?
- Should src: freedom be split, given cohesion 0.55?

## Sources

- `fuzz/fuzz_tls_impersonate.c`
- `fuzz/fuzz_url.c`
- `include/hls.h`
- `include/host_conf.h`
- `include/hostblock.h`
- `include/js_policy.h`
- `include/link_nav.h`
- `include/media_decoder.h`
- `include/net_realm.h`
- `include/perf_trace.h`
- `include/tls_impersonate.h`
- `include/webcaps.h`
- `include/wl_display.h`
- `src/freedom.c`
- `src/hls.c`
- `src/host_conf.c`
- `src/hostblock.c`
- `src/js_policy.c`
- `src/link_nav.c`
- `src/media_decoder.c`
- *... and 16 more*
