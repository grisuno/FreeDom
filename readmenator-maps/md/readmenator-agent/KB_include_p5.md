# Subsystem: include (page 5 of 6)
Previous: [KB_include_p4.md](KB_include_p4.md)

## include/perf_trace.h
- Doc: pt_init: #define PT_MAX_SAMPLES 256 typedef struct pt_stage_stats { uint64_t...
- Layer: utility
- Language: h
- Symbols:
  - `pt_stage_stats` (struct, line 34)
  - `pt_trace` (struct, line 41)
  - `order` (enum, line 71)
  - `samples` (type_alias, line 33) `typedef struct pt_stage_stats { uint64_t samples[PT_MAX_SAMPLES];`
  - `stage` (type_alias, line 40) `typedef struct pt_trace { pt_stage_stats stage[PT_STAGE_COUNT];`
  - `pt_init` (function, line 46) `void pt_init(pt_trace *t);`
  - `pt_elapsed_us` (function, line 50) `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us);`
  - `pt_record` (function, line 54) `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us);`
  - `pt_count` (function, line 57) `size_t pt_count(const pt_trace *t, pt_stage stage);`
  - `pt_last_us` (function, line 60) `uint64_t pt_last_us(const pt_trace *t, pt_stage stage);`
  - `pt_min_us` (function, line 63) `uint64_t pt_min_us(const pt_trace *t, pt_stage stage);`
  - `pt_max_us` (function, line 64) `uint64_t pt_max_us(const pt_trace *t, pt_stage stage);`
  - `pt_median_us` (function, line 65) `uint64_t pt_median_us(const pt_trace *t, pt_stage stage);`
  - `pt_stage_name` (function, line 69) `const char *pt_stage_name(pt_stage stage);`
  - `pt_format` (function, line 76) `size_t pt_format(const pt_trace *t, char *buf, size_t cap);`
  - `FREEDOM_PERF_TRACE_H` (macro, line 2) `#define FREEDOM_PERF_TRACE_H`
  - `PT_MAX_SAMPLES` (macro, line 32) `#define PT_MAX_SAMPLES`
- Imported by: `src/freedom.c`, `src/perf_trace.c`, `tests/test_perf_trace.c`

## include/pq_seal.h
- Doc: pqs_buf_free: DER of the PRIVATE key: secret, the caller seals it before it touches disk. *der...
- Layer: utility
- Language: h
- Symbols:
  - `pqs_status` (enum, line 24)
  - `pqs_keys` (type_alias, line 33) `typedef struct pqs_keys pqs_keys;`
  - `pqs_free` (function, line 41) `void pqs_free(pqs_keys *k);`
  - `pqs_buf_free` (function, line 51) `void pqs_buf_free(uint8_t *buf, size_t len);`
  - `FREEDOM_PQ_SEAL_H` (macro, line 2) `#define FREEDOM_PQ_SEAL_H`
  - `PQS_MAGIC` (macro, line 20) `#define PQS_MAGIC`
  - `PQS_MAGIC_LEN` (macro, line 21) `#define PQS_MAGIC_LEN`
  - `PQS_CT_LEN` (macro, line 22) `#define PQS_CT_LEN`
- Depends on: `include/local_store.h`
- Imported by: `src/http_cache.c`, `src/pq_seal.c`, `tests/test_pq_seal.c`

## include/prefetch.h
- Doc: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher *...
- Layer: utility
- Language: h
- Symbols:
  - `pf_ref` (struct, line 42)
  - `pf_list` (struct, line 53)
  - `pf_job` (struct, line 80)
  - `pf_pool` (struct, line 90)
  - `pf_gated_fetch` (struct, line 159)
  - `pf_kind` (enum, line 35)
  - `pf_job_state` (enum, line 73)
  - `kind` (type_alias, line 42) `typedef struct pf_ref { pf_kind kind;`
  - `refs` (type_alias, line 52) `typedef struct pf_list { pf_ref refs[PF_MAX_REFS];`
  - `jobs` (type_alias, line 89) `typedef struct pf_pool { pf_job jobs[PF_MAX_JOBS];`
  - `inner` (type_alias, line 159) `typedef struct pf_gated_fetch { pf_fetch_fn inner;`
  - `pf_scan` (function, line 62) `int pf_scan(const char *html, size_t len, pf_list *out);`
  - `pf_list_free` (function, line 63) `void pf_list_free(pf_list *l);`
  - `specifiers` (function, line 110) `* specifiers (each < PF_SPEC_MAX) into out[k] and returns how many. Pure. */ size_t pf_scan_imports(const char *js...`
  - `pf_find_importmap` (function, line 115) `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n);`
  - `started` (function, line 121) `* to fetch or no thread started (the caller fetches serially). */ int pf_pool_start_page(pf_pool *p, const char...`
  - `pf_pool_add` (function, line 127) `int pf_pool_add(pf_pool *p, const char *url);`
  - `fetch` (function, line 132) `* claiming jobs and running fetch(ctx, "GET", url, ...). Returns 0 on success or * -1 when no thread could start...`
  - `pf_pool_take` (function, line 145) `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status, char **body, size_t *len, char **ctype);`
  - `pf_pool_finish` (function, line 151) `void pf_pool_finish(pf_pool *p);`
  - `pool` (function, line 155) `* whose URL is pooled is served from the pool (a failed prefetch propagates the * failure -- never refetched);`
  - `pf_pooled_fetch` (function, line 165) `int pf_pooled_fetch(void *vctx, const char *method, const char *url, const char *body, size_t body_len, int...`
  - `FREEDOM_PREFETCH_H` (macro, line 2) `#define FREEDOM_PREFETCH_H`
  - `PF_MAX_REFS` (macro, line 47) `#define PF_MAX_REFS`
  - `PF_MAX_THREADS` (macro, line 48) `#define PF_MAX_THREADS`
  - `PF_MAX_JOBS` (macro, line 49) `#define PF_MAX_JOBS`
  - `PF_MAX_IMPORTS` (macro, line 50) `#define PF_MAX_IMPORTS`
  - `PF_SPEC_MAX` (macro, line 51) `#define PF_SPEC_MAX`
- Imported by: `fuzz/fuzz_prefetch.c`, `gui/browser_ui.c`, `src/freedom.c`, `src/prefetch.c`, `tests/test_prefetch.c`

## include/prefs.h
- Doc: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, *...
- Layer: utility
- Language: h
- Symbols:
  - `prefs_entry` (struct, line 45)
  - `prefs_state` (struct, line 50)
  - `prefs_status` (enum, line 36)
  - `theme_mode` (type_alias, line 49) `typedef struct prefs_state { int theme_mode;`
  - `prefs_init` (function, line 66) `void prefs_init(prefs_state *p);`
  - `prefs_free` (function, line 69) `void prefs_free(prefs_state *p);`
  - `free` (function, line 72) `* free(). */ prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len);`
  - `prefs_bookmark_index` (function, line 82) `int prefs_bookmark_index(const prefs_state *p, const char *url);`
  - `prefs_suggest` (function, line 101) `int prefs_suggest(const prefs_state *p, const char *query, char *out, size_t row_len, int max_rows);`
  - `anyway` (function, line 106) `* page is rendered by the normal confined pipeline anyway (defence in depth). * *out is owned (free());`
  - `FREEDOM_PREFS_H` (macro, line 2) `#define FREEDOM_PREFS_H`
  - `PREFS_VERSION` (macro, line 26) `#define PREFS_VERSION`
  - `PREFS_MAX_URL` (macro, line 27) `#define PREFS_MAX_URL`
  - `PREFS_MAX_TITLE` (macro, line 28) `#define PREFS_MAX_TITLE`
  - `PREFS_MAX_BOOKMARKS` (macro, line 29) `#define PREFS_MAX_BOOKMARKS`
  - `PREFS_MAX_HISTORY` (macro, line 30) `#define PREFS_MAX_HISTORY`
  - `PREFS_MAX_TEXT` (macro, line 31) `#define PREFS_MAX_TEXT`
  - `PREFS_PAGE_HISTORY` (macro, line 34) `#define PREFS_PAGE_HISTORY`
- Imported by: `fuzz/fuzz_prefs.c`, `gui/browser_ui.c`, `include/profile.h`, `include/ui.h`, `src/prefs.c`, `tests/test_prefs.c`, `tests/test_profile.c`

## include/pres_hints.h
- Doc: pres_hints (ph_) -- HTML presentational attributes as zero-specificity style.
- Layer: utility
- Language: h
- Symbols:
  - `ph_parse_dimension` (function, line 24) `int ph_parse_dimension(const char *s, size_t len, int *px, int *per_mille);`
  - `ph_apply` (function, line 31) `void ph_apply(const char *tag, ph_attr_fn get, void *ctx, unsigned flags, css_style *cs);`
  - `ph_parse_nonneg` (function, line 34) `int ph_parse_nonneg(const char *s, size_t len, int *out);`
  - `ph_table_cellpadding` (function, line 37) `int ph_table_cellpadding(ph_attr_fn get, void *ctx);`
  - `ph_cell_padding` (function, line 41) `void ph_cell_padding(int cellpad, css_style *cs);`
  - `FREEDOM_PRES_HINTS_H` (macro, line 8) `#define FREEDOM_PRES_HINTS_H`
  - `PH_ATTR_MAX` (macro, line 17) `#define PH_ATTR_MAX`
  - `PH_DIM_MAX_PX` (macro, line 18) `#define PH_DIM_MAX_PX`
  - `PH_CENTERED` (macro, line 26) `#define PH_CENTERED`
  - `PH_QUIRKS` (macro, line 27) `#define PH_QUIRKS`
- Depends on: `include/css.h`
- Imported by: `fuzz/fuzz_table_layout.c`, `src/page_view.c`, `src/pres_hints.c`, `tests/test_pres_hints.c`

## include/profile.h
- Doc: profile_close: Loads and decrypts prefs.bin over an out ALREADY initialised (prefs_init).
- Layer: utility
- Language: h
- Symbols:
  - `profile_ctx` (struct, line 46)
  - `profile_status` (enum, line 35)
  - `dir` (type_alias, line 45) `typedef struct profile_ctx { char dir[1024];`
  - `absent` (function, line 53) `* the keyfile when absent (0600, atomic write);`
  - `closed` (function, line 54) `* wrong size fails closed (PROFILE_ERR_KEY, never overwritten). Derives the * AEAD key (Argon2id, per-device salt)...`
  - `profile_close` (function, line 67) `void profile_close(profile_ctx *ctx);`
  - `FREEDOM_PROFILE_H` (macro, line 2) `#define FREEDOM_PROFILE_H`
  - `PROFILE_KEY_FILE` (macro, line 32) `#define PROFILE_KEY_FILE`
  - `PROFILE_PREFS_FILE` (macro, line 33) `#define PROFILE_PREFS_FILE`
- Depends on: `include/local_store.h`, `include/prefs.h`
- Imported by: `gui/browser_ui.c`, `src/profile.c`, `tests/test_profile.c`

## include/psl_data.h
- Layer: data_access
- Language: h
- Symbols:
  - `psl_rules` (variable, line 21) `extern const char *const psl_rules[];`
  - `psl_rules_n` (variable, line 22) `extern const size_t psl_rules_n;`
  - `psl_wildcards` (variable, line 23) `extern const char *const psl_wildcards[];`
  - `psl_wildcards_n` (variable, line 24) `extern const size_t psl_wildcards_n;`
  - `psl_exceptions` (variable, line 25) `extern const char *const psl_exceptions[];`
  - `psl_exceptions_n` (variable, line 26) `extern const size_t psl_exceptions_n;`
  - `FREEDOM_PSL_DATA_H` (macro, line 2) `#define FREEDOM_PSL_DATA_H`
- Imported by: `src/request_policy.c`

## include/render_doc.h
- Doc: rd_block: One paint-ready block in document order. text is owned, NUL-terminated and valid...
- Layer: presentation
- Language: h
- Symbols:
  - `rd_block` (struct, line 64)
  - `rd_doc` (struct, line 267)
  - `img_fail_reason` (enum, line 34)
  - `rd_kind` (enum, line 42)
  - `rd_status` (enum, line 302)
  - `kind` (type_alias, line 64) `typedef struct rd_block { rd_kind kind;`
  - `list` (function, line 18) `* inert display list (page_view) and the presentation orchestrator (the GUI and * the --headless writer). It decides...`
  - `RD_IMAGE` (function, line 59) `* RD_IMAGE (image src) and RD_INPUT (the owning form's action);`
  - `form` (function, line 63) `* form (-1 = none);`
  - `default` (function, line 153) `* default (layout is structure, not author styling, and leaks nothing to the * network) so the presentation layer...`
  - `to` (function, line 253) `* belongs to (-1 = none);`
  - `rdp_images_warning` (function, line 311) `* rdp_images_warning() is prepended so the user is always told. Each image * becomes an RD_IMAGE block whose...`
  - `rd_free` (function, line 321) `void rd_free(rd_doc *d);`
  - `rd_count` (function, line 324) `size_t rd_count(const rd_doc *d);`
  - `rd_at` (function, line 325) `const rd_block *rd_at(const rd_doc *d, size_t i);`
  - `rd_box_count` (function, line 329) `size_t rd_box_count(const rd_doc *d);`
  - `rd_box_at` (function, line 330) `const pv_box_def *rd_box_at(const rd_doc *d, size_t i);`
  - `rd_cont_count` (function, line 334) `size_t rd_cont_count(const rd_doc *d);`
  - `rd_cont_at` (function, line 335) `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i);`
  - `rd_kind_name` (function, line 339) `const char *rd_kind_name(rd_kind k);`
  - `rd_block_tag` (function, line 347) `const char *rd_block_tag(const rd_block *b);`
  - `rd_block_heading_level` (function, line 354) `int rd_block_heading_level(const rd_block *b);`
  - `decision` (function, line 357) `* decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never * NULL. */ const char...`
  - `IMG_FAIL_OK` (function, line 363) `* IMG_FAIL_OK (not a failure) or the reason is unknown. */ const char *rd_image_fail_label(img_fail_reason reason);`
  - `rd_input_label` (function, line 368) `const char *rd_input_label(int input_type);`
  - `rd_input_invisible` (function, line 373) `int rd_input_invisible(int input_type);`
  - `FREEDOM_RENDER_DOC_H` (macro, line 2) `#define FREEDOM_RENDER_DOC_H`
- Depends on: `include/page_view.h`, `include/render_policy.h`
- Imported by: `fuzz/fuzz_dom_debug.c`, `gui/browser_ui.c`, `include/dom_debug.h`, `src/freedom.c`, `src/render_doc.c`, `tests/test_dom_debug.c`, `tests/test_render_doc.c`

## include/render_policy.h
- Doc: rdp_caps: Render capabilities for a page.
- Layer: presentation
- Language: h
- Symbols:
  - `rdp_caps` (struct, line 32)
  - `rdp_img_decision` (enum, line 39)
  - `images` (type_alias, line 32) `typedef struct rdp_caps { bool images;`
  - `rdp_is_tracking_pixel` (function, line 53) `int rdp_is_tracking_pixel(int w, int h);`
  - `size` (function, line 56) `* announced size (e.g. <img width height>);`
  - `rdp_img_reason` (function, line 66) `const char *rdp_img_reason(rdp_img_decision d);`
  - `rdp_images_warning` (function, line 69) `const char *rdp_images_warning(void);`
  - `FREEDOM_RENDER_POLICY_H` (macro, line 2) `#define FREEDOM_RENDER_POLICY_H`
  - `RDP_TRACKER_MAX_DIM` (macro, line 27) `#define RDP_TRACKER_MAX_DIM`
- Imported by: `fuzz/fuzz_dom_debug.c`, `gui/browser_ui.c`, `include/render_doc.h`, `include/webcaps.h`, `src/freedom.c`, `src/render_policy.c`, `tests/test_dom_debug.c`, `tests/test_render_doc.c`, `tests/test_render_policy.c`

## include/renderer.h
- Doc: rd_result_free: Renders untrusted HTML out-of-process and returns an inert title + text. html ==...
- Layer: presentation
- Language: h
- Symbols:
  - `rd_result` (struct, line 29)
  - `rd_status` (enum, line 20)
  - `status` (type_alias, line 28) `typedef struct rd_result { rd_status status;`
  - `rd_result_free` (function, line 46) `void rd_result_free(rd_result *out);`
  - `FREEDOM_RENDERER_H` (macro, line 2) `#define FREEDOM_RENDERER_H`
  - `RD_MAX_INPUT` (macro, line 37) `#define RD_MAX_INPUT`
  - `RD_MAX_FIELD` (macro, line 38) `#define RD_MAX_FIELD`
- Imported by: `src/renderer.c`, `tests/test_renderer.c`

## include/request_policy.h
- Doc: rp_headers_have: 1 when the sanitized block `lines` carries a header called `name`...
- Layer: business_logic
- Language: h
- Symbols:
  - `rp_decision` (enum, line 21)
  - `rp_headers_have` (function, line 61) `static inline int rp_headers_have(const char *lines, const char *name)`
  - `rp_host_of` (function, line 30) `int rp_host_of(const char *url, char *out, size_t out_size);`
  - `rp_site_of` (function, line 34) `int rp_site_of(const char *host, char *out, size_t out_size);`
  - `rp_same_site` (function, line 37) `int rp_same_site(const char *top_level_url, const char *request_url);`
  - `rp_sanitize_request_headers` (function, line 57) `int rp_sanitize_request_headers(const char *raw, char *out, size_t cap);`
  - `FREEDOM_REQUEST_POLICY_H` (macro, line 2) `#define FREEDOM_REQUEST_POLICY_H`
  - `RP_HDR_MAX_COUNT` (macro, line 43) `#define RP_HDR_MAX_COUNT`
  - `RP_HDR_MAX_BYTES` (macro, line 44) `#define RP_HDR_MAX_BYTES`
  - `RP_HDR_NAME_MAX` (macro, line 45) `#define RP_HDR_NAME_MAX`
  - `RP_HDR_VALUE_MAX` (macro, line 46) `#define RP_HDR_VALUE_MAX`
- Imported by: `fuzz/fuzz_hls.c`, `fuzz/fuzz_request_headers.c`, `gui/browser_ui.c`, `src/freedom.c`, `src/hls.c`, `src/render_policy.c`, `src/request_policy.c`, `src/secure_fetch.c`, `src/tab.c`, `tests/test_request_policy.c`

## include/scroll_req.h
- Doc: srq_encode: Writes r as SRQ_WIRE_N int32: kind, behavior, block, y, margin_top, margin_bottom...
- Layer: utility
- Language: h
- Symbols:
  - `srq_req` (struct, line 37)
  - `srq_view` (struct, line 47)
  - `srq_kind` (enum, line 24)
  - `srq_behavior` (enum, line 31)
  - `srq_block` (enum, line 33)
  - `kind` (type_alias, line 36) `typedef struct srq_req { int kind;`
  - `scroll` (type_alias, line 46) `typedef struct srq_view { double scroll;`
  - `srq_encode` (function, line 58) `void srq_encode(const srq_req *r, int32_t out[SRQ_WIRE_N]);`
  - `srq_decode` (function, line 64) `int srq_decode(const int32_t in[SRQ_WIRE_N], size_t max_handles, srq_req *out);`
  - `srq_target` (function, line 71) `int srq_target(const srq_req *r, const srq_view *v, double el_top, double el_bottom, double *out);`
  - `srq_smooth` (function, line 76) `int srq_smooth(const srq_req *r, int root_smooth);`
  - `FREEDOM_SCROLL_REQ_H` (macro, line 2) `#define FREEDOM_SCROLL_REQ_H`
  - `SRQ_MAX_COORD` (macro, line 21) `#define SRQ_MAX_COORD`
  - `SRQ_WIRE_N` (macro, line 22) `#define SRQ_WIRE_N`
- Imported by: `fuzz/fuzz_scroll_req.c`, `gui/browser_ui.c`, `include/tab.h`, `src/scroll_req.c`, `src/tab.c`, `tests/test_scroll_req.c`

## include/secure_fetch.h
- Doc: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. *...
- Layer: utility
- Language: h
- Symbols:
  - `sf_chain_info` (struct, line 67)
  - `sf_config` (struct, line 86)
  - `sf_response` (struct, line 145)
  - `sf_status` (enum, line 24)
  - `sf_policy` (enum, line 47)
  - `sf_proxy_type` (enum, line 76)
  - `policy` (type_alias, line 85) `typedef struct sf_config { sf_policy policy;`
  - `status` (type_alias, line 144) `typedef struct sf_response { sf_status status;`
  - `sf_ws` (type_alias, line 340) `typedef struct sf_ws sf_ws;`
  - `validators` (function, line 18) `* The security logic lives in pure validators (no I/O);`
  - `rp_sanitize_request_headers` (function, line 115) `* rp_sanitize_request_headers ("Name: value\n" lines);`
  - `sf_global_init` (function, line 242) `void sf_global_init(void);`
  - `EXCLUDED` (function, line 248) `* cookies are EXCLUDED (network-only, never exposed to JS) and expired cookies skipped. * Only for a TRUSTED host...`
  - `sf_cookie_put` (function, line 255) `void sf_cookie_put(const char *url, const char *namevalue);`
  - `sf_cookie_line_matches` (function, line 260) `int sf_cookie_line_matches(const char *line, const char *host, const char *path, long now, char *out, size_t outsz);`
  - `sf_user_agent_or_default` (function, line 269) `const char *sf_user_agent_or_default(const char *ua);`
  - `sf_accept_language_or_default` (function, line 273) `const char *sf_accept_language_or_default(const char *lang);`
  - `sf_impersonate_kex_groups` (function, line 277) `const char *sf_impersonate_kex_groups(void);`
  - `sf_impersonate_tls13_ciphers` (function, line 278) `const char *sf_impersonate_tls13_ciphers(void);`
  - `skipped` (function, line 298) `* skipped (a classical key exchange is accepted);`
  - `sf_is_redirect_code` (function, line 309) `int sf_is_redirect_code(long http_code);`
  - `sf_header_value` (function, line 320) `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz);`
  - `bits` (function, line 357) `* *flags receives CURLWS_* bits (text/binary/close/cont);`
  - `sf_ws_fd` (function, line 364) `int sf_ws_fd(const sf_ws *ws);`
  - `sf_ws_close` (function, line 367) `void sf_ws_close(sf_ws *ws);`
  - `connection` (function, line 371) `* on each connection (Zero Trust). Each target is re-validated and a downgrade * to http:// is refused. Exceeding...`
  - `sf_get` (function, line 380) `* sf_get (Zero Trust): an insecure POST is not representable. Does not follow * redirects (the caller inspects...`
  - `sf_response_free` (function, line 391) `void sf_response_free(sf_response *resp);`
  - `exhausted` (function, line 402) `* is exhausted (*next untouched). `allowlisted` enables the sovereignty rung. */ int sf_fallback_policy(sf_status...`
  - `sf_rcache_put` (function, line 415) `int sf_rcache_put(const char *from, const char *to, time_t now);`
  - `sf_rcache_get` (function, line 416) `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap);`
  - `sf_rcache_clear` (function, line 417) `void sf_rcache_clear(void);`
  - `sf_rcache_set_backing` (function, line 426) `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx);`
  - `FREEDOM_SECURE_FETCH_H` (macro, line 2) `#define FREEDOM_SECURE_FETCH_H`
  - `SF_META_MAX` (macro, line 83) `#define SF_META_MAX`
  - `SF_RESPONSE_HEADERS_MAX` (macro, line 84) `#define SF_RESPONSE_HEADERS_MAX`
  - `SF_DEFAULT_KEX_GROUPS` (macro, line 181) `#define SF_DEFAULT_KEX_GROUPS`
  - `SF_IMPERSONATE_KEX_GROUPS` (macro, line 190) `#define SF_IMPERSONATE_KEX_GROUPS`
  - `SF_IMPERSONATE_TLS13_CIPHERS` (macro, line 191) `#define SF_IMPERSONATE_TLS13_CIPHERS`
  - `SF_IMPERSONATE_TLS12_CIPHERS` (macro, line 195) `#define SF_IMPERSONATE_TLS12_CIPHERS`
  - `SF_DEFAULT_USER_AGENT` (macro, line 206) `#define SF_DEFAULT_USER_AGENT`
  - `SF_DEFAULT_MAX_BODY` (macro, line 207) `#define SF_DEFAULT_MAX_BODY`
  - `SF_DEFAULT_TIMEOUT_MS` (macro, line 208) `#define SF_DEFAULT_TIMEOUT_MS`
  - `SF_CONNECT_TIMEOUT_MS` (macro, line 231) `#define SF_CONNECT_TIMEOUT_MS`
  - `SF_SUBRESOURCE_TIMEOUT_MS` (macro, line 232) `#define SF_SUBRESOURCE_TIMEOUT_MS`
  - `SF_DEFAULT_MAX_REDIRECTS` (macro, line 233) `#define SF_DEFAULT_MAX_REDIRECTS`
  - `SF_MAX_URL` (macro, line 234) `#define SF_MAX_URL`
  - `SF_WS_MAX_MESSAGE` (macro, line 339) `#define SF_WS_MAX_MESSAGE`
- Depends on: `include/anti_fp.h`
- Imported by: `gui/browser_ui.c`, `include/cached_fetch.h`, `include/ws_hub.h`, `src/freedom.c`, `src/secure_fetch.c`, `src/tab.c`, `tests/itest_secure_fetch.c`, `tests/test_secure_fetch.c`

## include/sha2.h
- Doc: sha_digest_len: sha2 -- one-shot SHA-1 / SHA-256 / SHA-384 / SHA-512 (FIPS 180-4), pure and...
- Layer: utility
- Language: h
- Symbols:
  - `sha_alg` (enum, line 16)
  - `sha_digest_len` (function, line 21) `size_t sha_digest_len(sha_alg alg);`
  - `sha_alg_from_name` (function, line 24) `int sha_alg_from_name(const char *name, sha_alg *out);`
  - `sha_digest` (function, line 28) `int sha_digest(sha_alg alg, const void *data, size_t len, uint8_t *out);`
  - `FREEDOM_SHA2_H` (macro, line 2) `#define FREEDOM_SHA2_H`
  - `SHA_MAX_DIGEST` (macro, line 18) `#define SHA_MAX_DIGEST`
- Imported by: `src/js_env.c`, `src/sha2.c`, `tests/test_sha2.c`

## include/sheet_cache.h
- Doc: shc_key: Every input of the parse.
- Layer: infrastructure
- Language: h
- Symbols:
  - `shc_key` (struct, line 36)
  - `shc_stats` (struct, line 43)
  - `shc_cache` (type_alias, line 26) `typedef struct shc_cache shc_cache;`
  - `shc_sheet` (type_alias, line 28) `typedef struct shc_sheet shc_sheet;`
  - `hits` (type_alias, line 42) `typedef struct shc_stats { unsigned long hits;`
  - `shc_new` (function, line 52) `shc_cache *shc_new(size_t max_text_bytes);`
  - `shc_free` (function, line 55) `void shc_free(shc_cache *c);`
  - `shc_acquire` (function, line 60) `shc_sheet *shc_acquire(shc_cache *cache, const shc_key *key);`
  - `shc_css` (function, line 64) `const css_sheet *shc_css(const shc_sheet *s);`
  - `shc_release` (function, line 67) `void shc_release(shc_sheet *s);`
  - `shc_stats_get` (function, line 70) `void shc_stats_get(const shc_cache *c, shc_stats *out);`
  - `FREEDOM_SHEET_CACHE_H` (macro, line 14) `#define FREEDOM_SHEET_CACHE_H`
- Depends on: `include/css.h`
- Imported by: `fuzz/fuzz_page_view.c`, `src/page_view.c`, `src/sheet_cache.c`, `src/tab.c`, `tests/test_page_view.c`, `tests/test_sheet_cache.c`

## include/shm_slots.h
- Doc: ss_committed: Chooses the slot to paint into: the current one if free, else the other free one.
- Layer: utility
- Language: h
- Symbols:
  - `ss_state` (struct, line 19)
  - `busy` (type_alias, line 18) `typedef struct ss_state { int busy[SS_COUNT];`
  - `ss_init` (function, line 24) `static inline void ss_init(ss_state *s)`
  - `ss_committed` (function, line 41) `static inline void ss_committed(ss_state *s, int i)`
  - `ss_released` (function, line 49) `static inline int ss_released(ss_state *s, int i)`
  - `FREEDOM_SHM_SLOTS_H` (macro, line 2) `#define FREEDOM_SHM_SLOTS_H`
  - `SS_COUNT` (macro, line 17) `#define SS_COUNT`
- Imported by: `gui/browser_ui.c`, `tests/test_shm_slots.c`

## include/smooth_scroll.h
- Doc: from: smooth_scroll (sms_) -- pure arithmetic of the page's animated scroll: a cubic ease-out...
- Layer: utility
- Language: h
- Symbols:
  - `sms_state` (struct, line 18)
  - `from` (type_alias, line 17) `typedef struct sms_state { double from;`
  - `sms_init` (function, line 27) `void sms_init(sms_state *s, double pos);`
  - `sms_jump` (function, line 28) `void sms_jump(sms_state *s, double pos);`
  - `sms_retarget` (function, line 29) `void sms_retarget(sms_state *s, double target, double now_ms, double dur_ms);`
  - `sms_sample` (function, line 30) `double sms_sample(sms_state *s, double now_ms);`
  - `sms_goal` (function, line 31) `double sms_goal(const sms_state *s);`
  - `sms_active` (function, line 32) `int sms_active(const sms_state *s);`
  - `FREEDOM_SMOOTH_SCROLL_H` (macro, line 2) `#define FREEDOM_SMOOTH_SCROLL_H`
- Imported by: `fuzz/fuzz_smooth_scroll.c`, `gui/browser_ui.c`, `src/smooth_scroll.c`, `tests/test_smooth_scroll.c`

## include/subreq_batch.h
- Doc: sqb_res: #ifndef SUBREQ_BATCH_H #define SUBREQ_BATCH_H #include <stddef.h> #define SQB_MAX_JOBS...
- Layer: utility
- Language: h
- Symbols:
  - `sqb_req` (struct, line 16)
  - `sqb_res` (struct, line 23)
  - `ok` (type_alias, line 23) `typedef struct sqb_res { int ok;`
  - `sqb` (type_alias, line 34) `typedef struct sqb sqb;`
  - `sqb_new` (function, line 37) `sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx);`
  - `sqb_new_owned` (function, line 40) `sqb *sqb_new_owned(int max_threads, sqb_run_fn run, void *ctx, void (*free_ctx)(void *));`
  - `sqb_abandon` (function, line 43) `void sqb_abandon(sqb *b);`
  - `sqb_submit` (function, line 47) `int sqb_submit(sqb *b, int refused, const sqb_req *req);`
  - `sqb_count` (function, line 48) `size_t sqb_count(const sqb *b);`
  - `sqb_wait_all` (function, line 50) `void sqb_wait_all(sqb *b);`
  - `sqb_result` (function, line 52) `const sqb_res *sqb_result(const sqb *b, size_t i);`
  - `sqb_wait_ready` (function, line 56) `size_t sqb_wait_ready(sqb *b, long wait_ms, size_t *idx, size_t cap);`
  - `sqb_remove` (function, line 59) `void sqb_remove(sqb *b, const size_t *idx, size_t k);`
  - `sqb_reset` (function, line 61) `void sqb_reset(sqb *b);`
  - `sqb_free` (function, line 64) `void sqb_free(sqb *b);`
  - `SUBREQ_BATCH_H` (macro, line 10) `#define SUBREQ_BATCH_H`
  - `SQB_MAX_JOBS` (macro, line 14) `#define SQB_MAX_JOBS`
- Imported by: `src/subreq_batch.c`, `src/tab.c`, `tests/test_subreq_batch.c`

## include/svg_paint.h
- Doc: svp_draw: Paints `img` into the rect [x, y, w, h] of `cr`, scaled uniformly and centred...
- Layer: utility
- Language: h
- Symbols:
  - `svp_draw` (function, line 31) `void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, double h, int current_rgb);`
  - `way` (function, line 35) `* worker rasterizes SVG images this way (spec/svg_raster.md section 3): drawing text * would open fontconfig, i.e....`
  - `FREEDOM_SVG_PAINT_H` (macro, line 2) `#define FREEDOM_SVG_PAINT_H`
- Depends on: `include/svg_render.h`
- Imported by: `gui/browser_ui.c`, `src/svg_paint.c`, `src/svg_raster.c`

## include/svg_raster.h
- Doc: sr_sniff: 1 when the first element of the document (after BOM, whitespace, the XML *...
- Layer: utility
- Language: h
- Symbols:
  - `sr_sniff` (function, line 29) `int sr_sniff(const uint8_t *bytes, size_t len);`
  - `FREEDOM_SVG_RASTER_H` (macro, line 2) `#define FREEDOM_SVG_RASTER_H`
  - `SR_SNIFF_MAX` (macro, line 23) `#define SR_SNIFF_MAX`
  - `SR_MAX_DIM` (macro, line 24) `#define SR_MAX_DIM`
  - `SR_MIN_RASTER` (macro, line 25) `#define SR_MIN_RASTER`
- Depends on: `include/image_decode.h`
- Imported by: `fuzz/fuzz_image_decode.c`, `src/svg_raster.c`, `src/tab.c`, `tests/test_svg_raster.c`

## include/svg_render.h
- Doc: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g>...
- Layer: presentation
- Language: h
- Symbols:
  - `sv_seg` (struct, line 65)
  - `sv_shape` (struct, line 75)
  - `sv_image` (struct, line 104)
  - `sv_status` (enum, line 25)
  - `sv_shape_kind` (enum, line 44)
  - `sv_verb` (enum, line 58)
  - `verb` (type_alias, line 64) `typedef struct sv_seg { int verb;`
  - `kind` (type_alias, line 75) `typedef struct sv_shape { int kind;`
  - `height` (type_alias, line 104) `typedef struct sv_image { double width, height;`
  - `sv_fit` (function, line 131) `void sv_fit(const sv_image *img, double dw, double dh, double *scale, double *off_x, double *off_y);`
  - `FREEDOM_SVG_RENDER_H` (macro, line 2) `#define FREEDOM_SVG_RENDER_H`
  - `SV_MAX_SHAPES` (macro, line 32) `#define SV_MAX_SHAPES`
  - `SV_MAX_POINTS` (macro, line 33) `#define SV_MAX_POINTS`
  - `SV_MAX_SEGS` (macro, line 34) `#define SV_MAX_SEGS`
  - `SV_MAX_DEPTH` (macro, line 35) `#define SV_MAX_DEPTH`
  - `SV_TEXT_MAX` (macro, line 36) `#define SV_TEXT_MAX`
  - `SV_MAX_INPUT` (macro, line 37) `#define SV_MAX_INPUT`
  - `SV_DEFAULT_W` (macro, line 41) `#define SV_DEFAULT_W`
  - `SV_DEFAULT_H` (macro, line 42) `#define SV_DEFAULT_H`
- Imported by: `fuzz/fuzz_svg_render.c`, `gui/browser_ui.c`, `include/svg_paint.h`, `src/page_view.c`, `src/svg_raster.c`, `src/svg_render.c`, `tests/test_svg_render.c`


Next: [KB_include_p6.md](KB_include_p6.md)
