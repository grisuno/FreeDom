# src: text_shape

*Community 3 | 55 files | cohesion 0.60*

## Definition

This community groups 55 file(s) rooted at `src` with dominant language c (cohesion 0.60). Central symbols: `ASCII`, `BLOCKED`, `CSS_DROPS_REPORT_MAX`, `DU_MAX_ENCODED_LEN`, `EXIT_ERROR`, `EXIT_OK`, `EXIT_USAGE`, `FREEDOM_DATA_URL_H`. Core file: `src/text_shape.c` (75 symbols). Documented purpose: libFuzzer harness for hls (spec/hls.md): hostile playlist text, hostile.

## Files

### `src` (17 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/data_url.c` | c | data_access | 11 | no |
| `src/freedom.c` | c | utility | 50 | no |
| `src/hls.c` | c | utility | 20 | no |
| `src/host_conf.c` | c | utility | 9 | no |
| `src/hostblock.c` | c | utility | 19 | no |

### `include` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/data_url.h` | h | data_access | 7 | no |
| `include/hls.h` | h | utility | 11 | no |
| `include/host_conf.h` | h | utility | 9 | no |
| `include/hostblock.h` | h | utility | 10 | no |
| `include/js_policy.h` | h | business_logic | 7 | no |

### `tests` (15 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_data_url.c` | c | testing | 26 | no |
| `tests/test_hls.c` | c | testing | 25 | no |
| `tests/test_host_conf.c` | c | testing | 8 | no |
| `tests/test_hostblock.c` | c | testing | 24 | no |
| `tests/test_js_policy.c` | c | testing | 5 | no |

### `fuzz` (7 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_data_url.c` | c | data_access | 1 | no |
| `fuzz/fuzz_hls.c` | c | utility | 1 | yes |
| `fuzz/fuzz_request_headers.c` | c | utility | 0 | no |
| `fuzz/fuzz_text_shape.c` | c | utility | 4 | no |
| `fuzz/fuzz_tls_impersonate.c` | c | utility | 0 | no |

*... and 35 more files in this community.*


## Key Symbols

- `worker` (function, `fuzz/fuzz_data_url.c:6`) `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, nev`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_hls.c:13`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FZ_CAP` (macro, `fuzz/fuzz_text_shape.c:23`) `#define FZ_CAP`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_text_shape.c:25`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `glyph` (function, `fuzz/fuzz_text_shape.c:54`) `* one lacks a glyph (spec/text_shape.md 8);`
- `ASCII` (function, `fuzz/fuzz_text_shape.c:56`) `* printable ASCII (one run, the requested face) the two must agree. */ double m`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_webfont.c:11`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FZ_GLYPHS` (macro, `fuzz/fuzz_webfont_register.c:24`) `#define FZ_GLYPHS`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_webfont_register.c:26`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
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

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 67
- Cross-boundary resolved imports (EXTRACTED): 44

## Connections

- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_policy.c` (presentation) -> `include/data_url.h` (data_access)

## Open Questions

- Why do 52 file(s) lack file-level docs (e.g. `fuzz/fuzz_data_url.c`)? What purpose do they serve?
- What would break if the most connected file in src: text_shape changed?
- Should src: text_shape be split, given cohesion 0.60?

## Sources

- `fuzz/fuzz_data_url.c`
- `fuzz/fuzz_hls.c`
- `fuzz/fuzz_request_headers.c`
- `fuzz/fuzz_text_shape.c`
- `fuzz/fuzz_tls_impersonate.c`
- `fuzz/fuzz_webfont.c`
- `fuzz/fuzz_webfont_register.c`
- `include/data_url.h`
- `include/hls.h`
- `include/host_conf.h`
- `include/hostblock.h`
- `include/js_policy.h`
- `include/media_decoder.h`
- `include/net_realm.h`
- `include/perf_trace.h`
- `include/psl_data.h`
- `include/request_policy.h`
- `include/text_shape.h`
- `include/tls_impersonate.h`
- `include/webcaps.h`
- *... and 35 more*
