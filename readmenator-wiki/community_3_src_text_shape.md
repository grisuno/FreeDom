# src: text_shape

*Community 3 | 40 files | cohesion 0.52*

## Definition

This community groups 40 file(s) rooted at `src` with dominant language c (cohesion 0.52). Central symbols: `BLOCKED`, `CSS_DROPS_REPORT_MAX`, `DU_MAX_ENCODED_LEN`, `EXIT_ERROR`, `EXIT_OK`, `EXIT_USAGE`, `FBP_EXPR_MAX`, `FBP_SELECTOR_MAX`. Core file: `src/text_shape.c` (68 symbols). Documented purpose: test_wl_display — CMocka suite for the pure Wayland socket picker..

## Files

### `src` (14 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/data_url.c` | c | data_access | 11 | no |
| `src/fb_panes.c` | c | utility | 10 | no |
| `src/freedom.c` | c | utility | 50 | no |
| `src/hls.c` | c | utility | 10 | no |
| `src/js_policy.c` | c | business_logic | 6 | no |
| `src/link_nav.c` | c | utility | 10 | no |
| `src/net_realm.c` | c | utility | 10 | no |

### `include` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/data_url.h` | h | data_access | 7 | no |
| `include/fb_panes.h` | h | utility | 12 | no |
| `include/hls.h` | h | utility | 8 | no |
| `include/js_policy.h` | h | business_logic | 7 | no |
| `include/link_nav.h` | h | utility | 11 | no |
| `include/net_realm.h` | h | utility | 10 | no |
| `include/perf_trace.h` | h | utility | 17 | no |

### `tests` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_data_url.c` | c | testing | 26 | no |
| `tests/test_fb_panes.c` | c | testing | 11 | no |
| `tests/test_hls.c` | c | testing | 16 | no |
| `tests/test_js_policy.c` | c | testing | 5 | no |
| `tests/test_link_nav.c` | c | testing | 22 | no |
| `tests/test_net_realm.c` | c | testing | 13 | no |

*... and 20 more files in this community.*


## Key Symbols

- `FREEDOM_DATA_URL_H` (macro, `include/data_url.h:2`) `#define FREEDOM_DATA_URL_H`
- `allocation` (function, `include/data_url.h:21`) `* * du_base64_payload does no allocation (it only slices the caller's url string`
- `du_status` (enum, `include/data_url.h:27`)
- `DU_MAX_ENCODED_LEN` (macro, `include/data_url.h:43`) `#define DU_MAX_ENCODED_LEN`
- `du_is_data_url` (function, `include/data_url.h:46`) `int du_is_data_url(const char *url);` - 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding
- `worker` (function, `include/data_url.h:59`) `* the confined worker (du_decode). */ du_status du_shape_ok(const char *url);`
- `closed` (function, `include/data_url.h:65`) `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/ou`
- `FREEDOM_FB_PANES_H` (macro, `include/fb_panes.h:2`) `#define FREEDOM_FB_PANES_H`
- `fbp_tab` (enum, `include/fb_panes.h:17`)
- `FBP_SELECTOR_MAX` (macro, `include/fb_panes.h:30`) `#define FBP_SELECTOR_MAX`
- `FBP_EXPR_MAX` (macro, `include/fb_panes.h:31`) `#define FBP_EXPR_MAX`
- `fbp_tab_label` (function, `include/fb_panes.h:34`) `const char *fbp_tab_label(int tab);` - FBP_CSS, FBP_SCRIPT, FBP_NET, FBP_PROFILE,   /* where the JS time went (sampling profiler, time-weig
- `fbp_tab_from_name` (function, `include/fb_panes.h:37`) `int fbp_tab_from_name(const char *name);` - FBP_PROFILE,   /* where the JS time went (sampling profiler, time-weighted) FBP_THROWS,    /* every
- `fbp_tab_wrap` (function, `include/fb_panes.h:40`) `int fbp_tab_wrap(int tab, int dir);` - FBP_STORAGE,   /* cookies, localStorage and sessionStorage of the page FBP_COUNT } fbp_tab; #define
- `fbp_tab_span` (function, `include/fb_panes.h:43`) `void fbp_tab_span(int tab, double cell_w, double pad_cells, double *x, double *w` - #define FBP_SELECTOR_MAX 256   /* bytes of the user's argument (selector / index / filter) #define F
- `fbp_tab_at` (function, `include/fb_panes.h:46`) `int fbp_tab_at(double x, double cell_w, double pad_cells);` - /* Label of a tab; an out-of-range id is the console. Never NULL. const char *fbp_tab_label(int tab)
- `fbp_is_pane` (function, `include/fb_panes.h:49`) `int fbp_is_pane(int tab);` - /* Tab named `name` (case-insensitive), or -1 when unknown / NULL. int fbp_tab_from_name(const char
- `fbp_js_quote` (function, `include/fb_panes.h:53`) `size_t fbp_js_quote(const char *s, size_t n, char *out, size_t cap);` - JS string literal for s[0,n) (double-quoted). Returns its length, or 0 on failure * (n too long, emb
- `fbp_expr` (function, `include/fb_panes.h:57`) `size_t fbp_expr(int tab, const char *sel, size_t n, char *out, size_t cap);` - The expression that fills `tab`'s panel for argument sel[0,n); NUL-terminated in out. * Returns its
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

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 47
- Cross-boundary resolved imports (EXTRACTED): 43

## Connections

- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/data_url.h.
- [EXTRACTED] depends_on community 3 <-> 4 (strength 0.9): Extracted import edge crosses communities: include/webcaps.h imports include/render_policy.h.
- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: src/css.c imports include/webfont.h.

## Risks

- [layer strict] `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access)
- [layer strict] `src/render_policy.c` (presentation) -> `include/data_url.h` (data_access)
- [dataflow UNCHECKED_ALLOC] `src/freedom.c:561` `headless_fetch` `oct`: Result of allocator stored in `oct` is never checked against NULL.

## Open Questions

- Why do 39 file(s) lack file-level docs (e.g. `include/data_url.h`)? What purpose do they serve?
- What would break if the most connected file in src: text_shape changed?
- Should src: text_shape be split, given cohesion 0.52?

## Sources

- `include/data_url.h`
- `include/fb_panes.h`
- `include/hls.h`
- `include/js_policy.h`
- `include/link_nav.h`
- `include/net_realm.h`
- `include/perf_trace.h`
- `include/text_shape.h`
- `include/tls_impersonate.h`
- `include/webcaps.h`
- `include/webfont.h`
- `include/webfont_load.h`
- `include/wl_display.h`
- `src/data_url.c`
- `src/fb_panes.c`
- `src/freedom.c`
- `src/hls.c`
- `src/js_policy.c`
- `src/link_nav.c`
- `src/net_realm.c`
- *... and 20 more*
