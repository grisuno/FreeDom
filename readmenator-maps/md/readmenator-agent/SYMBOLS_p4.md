# Symbols (page 4 of 13)
Previous: [SYMBOLS_p3.md](SYMBOLS_p3.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `run` | function | `include/page_view.h:954` | `* run (cont_id, the bx_display, the parsed gap/justify/cols, plus flex-wrap/ * row-gap/align-items). No-op on an...` |
| `scale` | function | `include/page_view.h:557` | `* scale(1)) and rotate in whole degrees (transform_rotate);` |
| `word_spacing` | type_alias | `include/page_view.h:896` | `typedef struct pv_text_ext { int font_family, text_transform, letter_spacing, word_spacing;` |
| `FREEDOM_PDF_EXPORT_H` | macro | `include/pdf_export.h:2` | `#define FREEDOM_PDF_EXPORT_H` |
| `PE_EXT` | macro | `include/pdf_export.h:29` | `#define PE_EXT` |
| `PE_EXT_PNG` | macro | `include/pdf_export.h:30` | `#define PE_EXT_PNG` |
| `PE_FALLBACK_NAME` | macro | `include/pdf_export.h:31` | `#define PE_FALLBACK_NAME` |
| `PE_NAME_MAX` | macro | `include/pdf_export.h:28` | `#define PE_NAME_MAX` |
| `fallback` | function | `include/pdf_export.h:46` | `* fallback (PE_ERR_OVERFLOW, out left empty). title == NULL is treated as empty. * Does NOT append the extension...` |
| `literal` | function | `include/pdf_export.h:52` | `* trusted literal (e.g. PE_EXT / PE_EXT_PNG);` |
| `pe_paginate` | function | `include/pdf_export.h:70` | `size_t pe_paginate(const double *tops, const double *heights, size_t n, double page_h, int *out_page, double...` |
| `pe_status` | enum | `include/pdf_export.h:33` | `` |
| `trusted` | function | `include/pdf_export.h:51` | `* dir is trusted (chosen by the app from XDG/$HOME);` |
| `FREEDOM_PERF_TRACE_H` | macro | `include/perf_trace.h:2` | `#define FREEDOM_PERF_TRACE_H` |
| `PT_MAX_SAMPLES` | macro | `include/perf_trace.h:32` | `#define PT_MAX_SAMPLES` |
| `order` | enum | `include/perf_trace.h:71` | `` |
| `pt_count` | function | `include/perf_trace.h:57` | `size_t pt_count(const pt_trace *t, pt_stage stage);` |
| `pt_elapsed_us` | function | `include/perf_trace.h:50` | `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us);` |
| `pt_format` | function | `include/perf_trace.h:76` | `size_t pt_format(const pt_trace *t, char *buf, size_t cap);` |
| `pt_init` | function | `include/perf_trace.h:46` | `void pt_init(pt_trace *t);` |
| `pt_last_us` | function | `include/perf_trace.h:60` | `uint64_t pt_last_us(const pt_trace *t, pt_stage stage);` |
| `pt_max_us` | function | `include/perf_trace.h:64` | `uint64_t pt_max_us(const pt_trace *t, pt_stage stage);` |
| `pt_median_us` | function | `include/perf_trace.h:65` | `uint64_t pt_median_us(const pt_trace *t, pt_stage stage);` |
| `pt_min_us` | function | `include/perf_trace.h:63` | `uint64_t pt_min_us(const pt_trace *t, pt_stage stage);` |
| `pt_record` | function | `include/perf_trace.h:54` | `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us);` |
| `pt_stage_name` | function | `include/perf_trace.h:69` | `const char *pt_stage_name(pt_stage stage);` |
| `pt_stage_stats` | struct | `include/perf_trace.h:34` | `` |
| `pt_trace` | struct | `include/perf_trace.h:41` | `` |
| `samples` | type_alias | `include/perf_trace.h:33` | `typedef struct pt_stage_stats { uint64_t samples[PT_MAX_SAMPLES];` |
| `stage` | type_alias | `include/perf_trace.h:40` | `typedef struct pt_trace { pt_stage_stats stage[PT_STAGE_COUNT];` |
| `FREEDOM_PREFETCH_H` | macro | `include/prefetch.h:2` | `#define FREEDOM_PREFETCH_H` |
| `PF_MAX_REFS` | macro | `include/prefetch.h:47` | `#define PF_MAX_REFS` |
| `PF_MAX_THREADS` | macro | `include/prefetch.h:48` | `#define PF_MAX_THREADS` |
| `fetch` | function | `include/prefetch.h:102` | `* claiming jobs and running fetch(ctx, "GET", url, ...). Returns 0 on success or * -1 when no thread could start...` |
| `inner` | type_alias | `include/prefetch.h:129` | `typedef struct pf_gated_fetch { pf_fetch_fn inner;` |
| `jobs` | type_alias | `include/prefetch.h:86` | `typedef struct pf_pool { pf_job jobs[PF_MAX_REFS];` |
| `kind` | type_alias | `include/prefetch.h:42` | `typedef struct pf_ref { pf_kind kind;` |
| `pf_gated_fetch` | struct | `include/prefetch.h:129` | `` |
| `pf_job` | struct | `include/prefetch.h:77` | `` |
| `pf_job_state` | enum | `include/prefetch.h:70` | `` |
| `pf_kind` | enum | `include/prefetch.h:35` | `` |
| `pf_list` | struct | `include/prefetch.h:50` | `` |
| `pf_list_free` | function | `include/prefetch.h:60` | `void pf_list_free(pf_list *l);` |
| `pf_pool` | struct | `include/prefetch.h:87` | `` |
| `pf_pool_finish` | function | `include/prefetch.h:121` | `void pf_pool_finish(pf_pool *p);` |
| `pf_pool_take` | function | `include/prefetch.h:115` | `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status, char **body, size_t *len, char **ctype);` |
| `pf_pooled_fetch` | function | `include/prefetch.h:135` | `int pf_pooled_fetch(void *vctx, const char *method, const char *url, const char *body, size_t body_len, int...` |
| `pf_ref` | struct | `include/prefetch.h:42` | `` |
| `pf_scan` | function | `include/prefetch.h:59` | `int pf_scan(const char *html, size_t len, pf_list *out);` |
| `pool` | function | `include/prefetch.h:125` | `* whose URL is pooled is served from the pool (a failed prefetch propagates the * failure -- never refetched);` |
| `refs` | type_alias | `include/prefetch.h:49` | `typedef struct pf_list { pf_ref refs[PF_MAX_REFS];` |
| `FREEDOM_PREFS_H` | macro | `include/prefs.h:2` | `#define FREEDOM_PREFS_H` |
| `PREFS_MAX_BOOKMARKS` | macro | `include/prefs.h:29` | `#define PREFS_MAX_BOOKMARKS` |
| `PREFS_MAX_HISTORY` | macro | `include/prefs.h:30` | `#define PREFS_MAX_HISTORY` |
| `PREFS_MAX_TEXT` | macro | `include/prefs.h:31` | `#define PREFS_MAX_TEXT` |
| `PREFS_MAX_TITLE` | macro | `include/prefs.h:28` | `#define PREFS_MAX_TITLE` |
| `PREFS_MAX_URL` | macro | `include/prefs.h:27` | `#define PREFS_MAX_URL` |
| `PREFS_PAGE_HISTORY` | macro | `include/prefs.h:34` | `#define PREFS_PAGE_HISTORY` |
| `PREFS_VERSION` | macro | `include/prefs.h:26` | `#define PREFS_VERSION` |
| `anyway` | function | `include/prefs.h:105` | `* page is rendered by the normal confined pipeline anyway (defence in depth). * *out is owned (free());` |
| `free` | function | `include/prefs.h:71` | `* free(). */ prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len);` |
| `prefs_bookmark_index` | function | `include/prefs.h:81` | `int prefs_bookmark_index(const prefs_state *p, const char *url);` |
| `prefs_entry` | struct | `include/prefs.h:45` | `` |
| `prefs_free` | function | `include/prefs.h:68` | `void prefs_free(prefs_state *p);` |
| `prefs_init` | function | `include/prefs.h:65` | `void prefs_init(prefs_state *p);` |
| `prefs_state` | struct | `include/prefs.h:50` | `` |
| `prefs_status` | enum | `include/prefs.h:36` | `` |
| `prefs_suggest` | function | `include/prefs.h:100` | `int prefs_suggest(const prefs_state *p, const char *query, char *out, size_t row_len, int max_rows);` |
| `theme_mode` | type_alias | `include/prefs.h:49` | `typedef struct prefs_state { int theme_mode;` |
| `FREEDOM_PROFILE_H` | macro | `include/profile.h:2` | `#define FREEDOM_PROFILE_H` |
| `PROFILE_KEY_FILE` | macro | `include/profile.h:32` | `#define PROFILE_KEY_FILE` |
| `PROFILE_PREFS_FILE` | macro | `include/profile.h:33` | `#define PROFILE_PREFS_FILE` |
| `absent` | function | `include/profile.h:53` | `* the keyfile when absent (0600, atomic write);` |
| `closed` | function | `include/profile.h:54` | `* wrong size fails closed (PROFILE_ERR_KEY, never overwritten). Derives the * AEAD key (Argon2id, per-device salt)...` |
| `dir` | type_alias | `include/profile.h:45` | `typedef struct profile_ctx { char dir[1024];` |
| `profile_close` | function | `include/profile.h:67` | `void profile_close(profile_ctx *ctx);` |
| `profile_ctx` | struct | `include/profile.h:46` | `` |
| `profile_status` | enum | `include/profile.h:35` | `` |
| `FREEDOM_PSL_DATA_H` | macro | `include/psl_data.h:2` | `#define FREEDOM_PSL_DATA_H` |
| `psl_exceptions` | variable | `include/psl_data.h:25` | `extern const char *const psl_exceptions[];` |
| `psl_exceptions_n` | variable | `include/psl_data.h:26` | `extern const size_t psl_exceptions_n;` |
| `psl_rules` | variable | `include/psl_data.h:21` | `extern const char *const psl_rules[];` |
| `psl_rules_n` | variable | `include/psl_data.h:22` | `extern const size_t psl_rules_n;` |
| `psl_wildcards` | variable | `include/psl_data.h:23` | `extern const char *const psl_wildcards[];` |
| `psl_wildcards_n` | variable | `include/psl_data.h:24` | `extern const size_t psl_wildcards_n;` |
| `FREEDOM_RENDER_DOC_H` | macro | `include/render_doc.h:2` | `#define FREEDOM_RENDER_DOC_H` |
| `IMG_FAIL_OK` | function | `include/render_doc.h:327` | `* IMG_FAIL_OK (not a failure) or the reason is unknown. */ const char *rd_image_fail_label(img_fail_reason reason);` |
| `RD_IMAGE` | function | `include/render_doc.h:59` | `* RD_IMAGE (image src) and RD_INPUT (the owning form's action);` |
| `decision` | function | `include/render_doc.h:321` | `* decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never * NULL. */ const char...` |
| `default` | function | `include/render_doc.h:145` | `* default (layout is structure, not author styling, and leaks nothing to the * network) so the presentation layer...` |
| `form` | function | `include/render_doc.h:63` | `* form (-1 = none);` |
| `img_fail_reason` | enum | `include/render_doc.h:34` | `` |
| `kind` | type_alias | `include/render_doc.h:64` | `typedef struct rd_block { rd_kind kind;` |
| `list` | function | `include/render_doc.h:18` | `* inert display list (page_view) and the presentation orchestrator (the GUI and * the --headless writer). It decides...` |
| `rd_at` | function | `include/render_doc.h:296` | `const rd_block *rd_at(const rd_doc *d, size_t i);` |
| `rd_block` | struct | `include/render_doc.h:64` | `` |
| `rd_block_tag` | function | `include/render_doc.h:318` | `const char *rd_block_tag(const rd_block *b);` |
| `rd_box_at` | function | `include/render_doc.h:301` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i);` |
| `rd_box_count` | function | `include/render_doc.h:300` | `size_t rd_box_count(const rd_doc *d);` |
| `rd_cont_at` | function | `include/render_doc.h:306` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i);` |
| `rd_cont_count` | function | `include/render_doc.h:305` | `size_t rd_cont_count(const rd_doc *d);` |
| `rd_count` | function | `include/render_doc.h:295` | `size_t rd_count(const rd_doc *d);` |
| `rd_doc` | struct | `include/render_doc.h:247` | `` |
| `rd_free` | function | `include/render_doc.h:292` | `void rd_free(rd_doc *d);` |
| `rd_input_invisible` | function | `include/render_doc.h:337` | `int rd_input_invisible(int input_type);` |
| `rd_input_label` | function | `include/render_doc.h:332` | `const char *rd_input_label(int input_type);` |
| `rd_kind` | enum | `include/render_doc.h:42` | `` |
| `rd_kind_name` | function | `include/render_doc.h:310` | `const char *rd_kind_name(rd_kind k);` |
| `rd_status` | enum | `include/render_doc.h:273` | `` |
| `rdp_images_warning` | function | `include/render_doc.h:282` | `* rdp_images_warning() is prepended so the user is always told. Each image * becomes an RD_IMAGE block whose...` |
| `to` | function | `include/render_doc.h:233` | `* belongs to (-1 = none);` |
| `FREEDOM_RENDER_POLICY_H` | macro | `include/render_policy.h:2` | `#define FREEDOM_RENDER_POLICY_H` |
| `RDP_TRACKER_MAX_DIM` | macro | `include/render_policy.h:27` | `#define RDP_TRACKER_MAX_DIM` |
| `images` | type_alias | `include/render_policy.h:32` | `typedef struct rdp_caps { bool images;` |
| `rdp_caps` | struct | `include/render_policy.h:32` | `` |
| `rdp_images_warning` | function | `include/render_policy.h:69` | `const char *rdp_images_warning(void);` |
| `rdp_img_decision` | enum | `include/render_policy.h:39` | `` |
| `rdp_img_reason` | function | `include/render_policy.h:66` | `const char *rdp_img_reason(rdp_img_decision d);` |
| `rdp_is_tracking_pixel` | function | `include/render_policy.h:53` | `int rdp_is_tracking_pixel(int w, int h);` |
| `size` | function | `include/render_policy.h:56` | `* announced size (e.g. <img width height>);` |
| `FREEDOM_RENDERER_H` | macro | `include/renderer.h:2` | `#define FREEDOM_RENDERER_H` |
| `RD_MAX_FIELD` | macro | `include/renderer.h:38` | `#define RD_MAX_FIELD` |
| `RD_MAX_INPUT` | macro | `include/renderer.h:37` | `#define RD_MAX_INPUT` |
| `rd_result` | struct | `include/renderer.h:29` | `` |
| `rd_result_free` | function | `include/renderer.h:46` | `void rd_result_free(rd_result *out);` |
| `rd_status` | enum | `include/renderer.h:20` | `` |
| `status` | type_alias | `include/renderer.h:28` | `typedef struct rd_result { rd_status status;` |
| `FREEDOM_REQUEST_POLICY_H` | macro | `include/request_policy.h:2` | `#define FREEDOM_REQUEST_POLICY_H` |
| `rp_decision` | enum | `include/request_policy.h:21` | `` |
| `rp_host_of` | function | `include/request_policy.h:30` | `int rp_host_of(const char *url, char *out, size_t out_size);` |
| `rp_same_site` | function | `include/request_policy.h:37` | `int rp_same_site(const char *top_level_url, const char *request_url);` |
| `rp_site_of` | function | `include/request_policy.h:34` | `int rp_site_of(const char *host, char *out, size_t out_size);` |
| `EXCLUDED` | function | `include/secure_fetch.h:210` | `* cookies are EXCLUDED (network-only, never exposed to JS) and expired cookies skipped. * Only for a TRUSTED host...` |
| `FREEDOM_SECURE_FETCH_H` | macro | `include/secure_fetch.h:2` | `#define FREEDOM_SECURE_FETCH_H` |
| `SF_CONNECT_TIMEOUT_MS` | macro | `include/secure_fetch.h:193` | `#define SF_CONNECT_TIMEOUT_MS` |
| `SF_DEFAULT_KEX_GROUPS` | macro | `include/secure_fetch.h:143` | `#define SF_DEFAULT_KEX_GROUPS` |
| `SF_DEFAULT_MAX_BODY` | macro | `include/secure_fetch.h:169` | `#define SF_DEFAULT_MAX_BODY` |
| `SF_DEFAULT_MAX_REDIRECTS` | macro | `include/secure_fetch.h:195` | `#define SF_DEFAULT_MAX_REDIRECTS` |
| `SF_DEFAULT_TIMEOUT_MS` | macro | `include/secure_fetch.h:170` | `#define SF_DEFAULT_TIMEOUT_MS` |
| `SF_DEFAULT_USER_AGENT` | macro | `include/secure_fetch.h:168` | `#define SF_DEFAULT_USER_AGENT` |
| `SF_IMPERSONATE_KEX_GROUPS` | macro | `include/secure_fetch.h:152` | `#define SF_IMPERSONATE_KEX_GROUPS` |
| `SF_IMPERSONATE_TLS12_CIPHERS` | macro | `include/secure_fetch.h:157` | `#define SF_IMPERSONATE_TLS12_CIPHERS` |
| `SF_IMPERSONATE_TLS13_CIPHERS` | macro | `include/secure_fetch.h:153` | `#define SF_IMPERSONATE_TLS13_CIPHERS` |
| `SF_MAX_URL` | macro | `include/secure_fetch.h:196` | `#define SF_MAX_URL` |
| `SF_SUBRESOURCE_TIMEOUT_MS` | macro | `include/secure_fetch.h:194` | `#define SF_SUBRESOURCE_TIMEOUT_MS` |
| `SF_WS_MAX_MESSAGE` | macro | `include/secure_fetch.h:292` | `#define SF_WS_MAX_MESSAGE` |
| `bits` | function | `include/secure_fetch.h:310` | `* *flags receives CURLWS_* bits (text/binary/close/cont);` |
| `connection` | function | `include/secure_fetch.h:324` | `* on each connection (Zero Trust). Each target is re-validated and a downgrade * to http:// is refused. Exceeding...` |
| `policy` | type_alias | `include/secure_fetch.h:74` | `typedef struct sf_config { sf_policy policy;` |
| `sf_chain_info` | struct | `include/secure_fetch.h:60` | `` |
| `sf_config` | struct | `include/secure_fetch.h:75` | `` |
| `sf_cookie_line_matches` | function | `include/secure_fetch.h:222` | `int sf_cookie_line_matches(const char *line, const char *host, const char *path, long now, char *out, size_t outsz);` |
| `sf_cookie_put` | function | `include/secure_fetch.h:217` | `void sf_cookie_put(const char *url, const char *namevalue);` |
| `sf_get` | function | `include/secure_fetch.h:333` | `* sf_get (Zero Trust): an insecure POST is not representable. Does not follow * redirects (the caller inspects...` |
| `sf_global_init` | function | `include/secure_fetch.h:204` | `void sf_global_init(void);` |
| `sf_impersonate_kex_groups` | function | `include/secure_fetch.h:235` | `const char *sf_impersonate_kex_groups(void);` |
| `sf_impersonate_tls13_ciphers` | function | `include/secure_fetch.h:236` | `const char *sf_impersonate_tls13_ciphers(void);` |
| `sf_is_redirect_code` | function | `include/secure_fetch.h:267` | `int sf_is_redirect_code(long http_code);` |
| `sf_policy` | enum | `include/secure_fetch.h:40` | `` |
| `sf_proxy_type` | enum | `include/secure_fetch.h:69` | `` |
| `sf_response` | struct | `include/secure_fetch.h:117` | `` |
| `sf_response_free` | function | `include/secure_fetch.h:344` | `void sf_response_free(sf_response *resp);` |
| `sf_status` | enum | `include/secure_fetch.h:23` | `` |
| `sf_user_agent_or_default` | function | `include/secure_fetch.h:231` | `const char *sf_user_agent_or_default(const char *ua);` |
| `sf_ws` | type_alias | `include/secure_fetch.h:293` | `typedef struct sf_ws sf_ws;` |
| `sf_ws_close` | function | `include/secure_fetch.h:320` | `void sf_ws_close(sf_ws *ws);` |
| `sf_ws_fd` | function | `include/secure_fetch.h:317` | `int sf_ws_fd(const sf_ws *ws);` |
| `skipped` | function | `include/secure_fetch.h:256` | `* skipped (a classical key exchange is accepted);` |
| `status` | type_alias | `include/secure_fetch.h:116` | `typedef struct sf_response { sf_status status;` |
| `validators` | function | `include/secure_fetch.h:17` | `* The security logic lives in pure validators (no I/O);` |
| `FREEDOM_SVG_PAINT_H` | macro | `include/svg_paint.h:2` | `#define FREEDOM_SVG_PAINT_H` |
| `svp_draw` | function | `include/svg_paint.h:31` | `void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, double h, int current_rgb);` |
| `FREEDOM_SVG_RENDER_H` | macro | `include/svg_render.h:2` | `#define FREEDOM_SVG_RENDER_H` |
| `SV_DEFAULT_H` | macro | `include/svg_render.h:42` | `#define SV_DEFAULT_H` |
| `SV_DEFAULT_W` | macro | `include/svg_render.h:41` | `#define SV_DEFAULT_W` |
| `SV_MAX_DEPTH` | macro | `include/svg_render.h:35` | `#define SV_MAX_DEPTH` |
| `SV_MAX_INPUT` | macro | `include/svg_render.h:37` | `#define SV_MAX_INPUT` |
| `SV_MAX_POINTS` | macro | `include/svg_render.h:33` | `#define SV_MAX_POINTS` |
| `SV_MAX_SEGS` | macro | `include/svg_render.h:34` | `#define SV_MAX_SEGS` |
| `SV_MAX_SHAPES` | macro | `include/svg_render.h:32` | `#define SV_MAX_SHAPES` |
| `SV_TEXT_MAX` | macro | `include/svg_render.h:36` | `#define SV_TEXT_MAX` |
| `height` | type_alias | `include/svg_render.h:104` | `typedef struct sv_image { double width, height;` |
| `kind` | type_alias | `include/svg_render.h:75` | `typedef struct sv_shape { int kind;` |
| `sv_fit` | function | `include/svg_render.h:131` | `void sv_fit(const sv_image *img, double dw, double dh, double *scale, double *off_x, double *off_y);` |
| `sv_image` | struct | `include/svg_render.h:104` | `` |
| `sv_seg` | struct | `include/svg_render.h:65` | `` |
| `sv_shape` | struct | `include/svg_render.h:75` | `` |
| `sv_shape_kind` | enum | `include/svg_render.h:44` | `` |
| `sv_status` | enum | `include/svg_render.h:25` | `` |
| `sv_verb` | enum | `include/svg_render.h:58` | `` |
| `verb` | type_alias | `include/svg_render.h:64` | `typedef struct sv_seg { int verb;` |
| `FREEDOM_TAB_H` | macro | `include/tab.h:2` | `#define FREEDOM_TAB_H` |
| `TAB_MAX_INPUT` | macro | `include/tab.h:148` | `#define TAB_MAX_INPUT` |
| `decode` | function | `include/tab.h:325` | `* could not decode (caller shows the placeholder), which is not a transport error. * TAB_ERR_* is reserved for...` |
| `exclusively` | function | `include/tab.h:209` | `* exclusively (tab_subreq_permitted). Default 0: zero fetches, Privacy by Default. */ void tab_set_css_allowed(tab...` |
| `granted` | function | `include/tab.h:299` | `* granted (allow.conf AND js.conf);` |
| `jar` | function | `include/tab.h:194` | `* the trusted parent read from its ephemeral network jar (sf_cookie_header_for). Only * meaningful for a trusted...` |
| `kind` | type_alias | `include/tab.h:67` | `typedef struct tab_ws_op { int kind;` |
| `origin` | function | `include/tab.h:201` | `* page origin (web_storage snapshot, copied). Used only when the load is trusted * (net granted);` |
| `out_status` | function | `include/tab.h:175` | `* On success return 0 and set *out_status (HTTP status), *out_body / *out_body_len * (malloc'd response bytes, tab...` |
| `popstate` | function | `include/tab.h:306` | `* popstate (+ hashchange) and re-derives the view like a click. */ tab_status tab_popstate(tab *t, int index...` |
| `replace` | type_alias | `include/tab.h:53` | `typedef struct tab_hist_op { int replace;` |
| `returned` | function | `include/tab.h:300` | `* returned (the page keeps its zeros). The worker re-checks the same condition. * g must be finished (jg_finish). */...` |
| `string` | function | `include/tab.h:250` | `* event_type is a JS event type string (e.g. "keydown", "input", "change"). * key is the keyboard key value (may be...` |
| `tab` | type_alias | `include/tab.h:45` | `typedef struct tab tab;` |
| `tab_alive` | function | `include/tab.h:338` | `int tab_alive(const tab *t);` |
| `tab_child_pid` | function | `include/tab.h:341` | `pid_t tab_child_pid(const tab *t);` |
| `tab_close` | function | `include/tab.h:344` | `void tab_close(tab *t);` |
| `tab_eval_result` | struct | `include/tab.h:127` | `` |
| `tab_eval_result_free` | function | `include/tab.h:348` | `void tab_eval_result_free(tab_eval_result *r);` |
| `tab_hist_op` | struct | `include/tab.h:53` | `` |
| `tab_image` | struct | `include/tab.h:140` | `` |
| `tab_image_free` | function | `include/tab.h:349` | `void tab_image_free(tab_image *img);` |
| `tab_open` | function | `include/tab.h:156` | `* and reaches tab_open (the app and the test harness) must call this first. */ void tab_worker_dispatch(int argc...` |
| `tab_page` | struct | `include/tab.h:75` | `` |
| `tab_page_free` | function | `include/tab.h:347` | `void tab_page_free(tab_page *p);` |
| `tab_parse_worker_args` | function | `include/tab.h:163` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd);` |
| `tab_set_cookies` | function | `include/tab.h:198` | `void tab_set_cookies(tab *t, const char *cookies);` |
| `tab_set_fetcher` | function | `include/tab.h:186` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx);` |
| `tab_set_net_allowed` | function | `include/tab.h:191` | `void tab_set_net_allowed(tab *t, int allowed);` |
| `tab_set_storage` | function | `include/tab.h:203` | `void tab_set_storage(tab *t, const char *blob, size_t len);` |
| `tab_set_viewport_w` | function | `include/tab.h:217` | `void tab_set_viewport_w(tab *t, int px);` |
| `tab_status` | enum | `include/tab.h:31` | `` |
| `tab_subreq_permitted` | function | `include/tab.h:222` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method);` |
| `tab_worker_dispatch` | function | `include/tab.h:152` | `* Call tab_worker_dispatch(argc, argv) as the FIRST thing in main(): if argv is the * internal "--tab-worker <rfd>...` |
| `tab_ws_event_kind` | enum | `include/tab.h:64` | `` |
| `tab_ws_kind` | enum | `include/tab.h:60` | `` |
| `tab_ws_op` | struct | `include/tab.h:68` | `` |
| `view` | function | `include/tab.h:230` | `* <noscript> handling in the built view (off => fallback shown, on => suppressed) * and is where allowlisted...` |
| `width` | type_alias | `include/tab.h:140` | `typedef struct tab_image { uint32_t width;` |
| `FREEDOM_TEXT_SHAPE_H` | macro | `include/text_shape.h:19` | `#define FREEDOM_TEXT_SHAPE_H` |
| `TSH_MAX_GLYPHS` | macro | `include/text_shape.h:40` | `#define TSH_MAX_GLYPHS` |
| `TSH_MAX_TEXT` | macro | `include/text_shape.h:41` | `#define TSH_MAX_TEXT` |
| `content` | function | `include/text_shape.h:11` | `* TEXT is hostile remote content (sanitised UTF-8) and is fuzzed (make fuzz-tsh);` |
| `family` | type_alias | `include/text_shape.h:33` | `typedef struct tsh_font { int family;` |
| `origin` | function | `include/text_shape.h:55` | `* glyphs are written with positions relative to origin (0,0) on the baseline, * and *out_adv holds the total pen...` |
| `tsh_font` | struct | `include/text_shape.h:33` | `` |
| `tsh_measure` | function | `include/text_shape.h:64` | `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len);` |
| `tsh_ready` | function | `include/text_shape.h:52` | `int tsh_ready(void);` |
| `tsh_shutdown` | function | `include/text_shape.h:86` | `void tsh_shutdown(void);` |
| `tsh_status` | enum | `include/text_shape.h:43` | `` |
| `tsh_webfont_clear` | function | `include/text_shape.h:83` | `void tsh_webfont_clear(void);` |
| `tsh_webfont_register` | function | `include/text_shape.h:77` | `int tsh_webfont_register(const char *name, const unsigned char *bytes, size_t nbytes, int bold, int italic);` |
| `FREEDOM_TEXTFIELD_H` | macro | `include/textfield.h:2` | `#define FREEDOM_TEXTFIELD_H` |
| `TF_CAP` | macro | `include/textfield.h:23` | `#define TF_CAP` |
| `buf` | type_alias | `include/textfield.h:24` | `typedef struct tf_field { char buf[TF_CAP];` |
| `tf_backspace` | function | `include/textfield.h:53` | `void tf_backspace(tf_field *f);` |
| `tf_clear` | function | `include/textfield.h:45` | `void tf_clear(tf_field *f);` |
| `tf_cursor` | function | `include/textfield.h:68` | `size_t tf_cursor(const tf_field *f);` |
| `tf_delete` | function | `include/textfield.h:56` | `void tf_delete(tf_field *f);` |
| `tf_end` | function | `include/textfield.h:63` | `void tf_end(tf_field *f);` |
| `tf_field` | struct | `include/textfield.h:25` | `` |
| `tf_home` | function | `include/textfield.h:62` | `void tf_home(tf_field *f);` |
| `tf_init` | function | `include/textfield.h:38` | `void tf_init(tf_field *f);` |
| `tf_len` | function | `include/textfield.h:67` | `size_t tf_len(const tf_field *f);` |
| `tf_move` | function | `include/textfield.h:59` | `void tf_move(tf_field *f, long delta);` |
| `tf_status` | enum | `include/textfield.h:31` | `` |
| `tf_text` | function | `include/textfield.h:66` | `const char *tf_text(const tf_field *f);` |
| `FREEDOM_TLS_IMPERSONATE_H` | macro | `include/tls_impersonate.h:2` | `#define FREEDOM_TLS_IMPERSONATE_H` |
| `TI_MAGIC` | macro | `include/tls_impersonate.h:60` | `#define TI_MAGIC` |
| `TI_MAX_BODY` | macro | `include/tls_impersonate.h:64` | `#define TI_MAX_BODY` |
| `TI_MAX_CHAIN` | macro | `include/tls_impersonate.h:67` | `#define TI_MAX_CHAIN` |
| `TI_MAX_GROUP` | macro | `include/tls_impersonate.h:68` | `#define TI_MAX_GROUP` |
| `TI_MAX_HEADERS` | macro | `include/tls_impersonate.h:63` | `#define TI_MAX_HEADERS` |
| `TI_MAX_METHOD` | macro | `include/tls_impersonate.h:62` | `#define TI_MAX_METHOD` |
| `TI_MAX_RESP_BODY` | macro | `include/tls_impersonate.h:66` | `#define TI_MAX_RESP_BODY` |
| `TI_MAX_RESP_HDR` | macro | `include/tls_impersonate.h:65` | `#define TI_MAX_RESP_HDR` |
| `TI_MAX_URL` | macro | `include/tls_impersonate.h:61` | `#define TI_MAX_URL` |
| `chain` | function | `include/tls_impersonate.h:32` | `* * The response carries the peer certificate chain (DER) and the negotiated group so * the TRUSTED PARENT...` |
| `path` | function | `include/tls_impersonate.h:26` | `* Zero Knowledge path (PQ-hybrid, VERIFYPEER). * * 2. ti_encode_x / ti_decode_x — the length-prefixed, fail-closed...` |
| `status` | type_alias | `include/tls_impersonate.h:82` | `typedef struct ti_resp { long status;` |
| `success` | function | `include/tls_impersonate.h:97` | `* ti_decode_* returns 0 on success (out fully populated), <0 on any malformed, * truncated or over-cap input (out...` |
| `ti_decode_req` | function | `include/tls_impersonate.h:101` | `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out);` |
| `ti_decode_resp` | function | `include/tls_impersonate.h:105` | `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out);` |
| `ti_encode_resp` | function | `include/tls_impersonate.h:104` | `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap);` |
| `ti_profile` | enum | `include/tls_impersonate.h:41` | `` |
| `ti_req` | struct | `include/tls_impersonate.h:72` | `` |
| `ti_req_free` | function | `include/tls_impersonate.h:102` | `void ti_req_free(ti_req *r);` |
| `ti_resp` | struct | `include/tls_impersonate.h:82` | `` |
| `ti_resp_free` | function | `include/tls_impersonate.h:106` | `void ti_resp_free(ti_resp *r);` |
| `ti_should_impersonate` | function | `include/tls_impersonate.h:56` | `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled, int user_opt_in);` |
| `FREEDOM_UI_H` | macro | `include/ui.h:2` | `#define FREEDOM_UI_H` |
| `available` | function | `include/ui.h:85` | `* cheapest artifact to inspect a render where no display is available (CI, an AI * agent): export, then read the PNG...` |
| `disk` | function | `include/ui.h:112` | `* images are read from disk (confined to the document directory by render_doc). * top_url is the page origin (https...` |
| `images` | function | `include/ui.h:114` | `* fetcher loads no images (placeholders, as before). Any image that fails falls back * to its placeholder...` |
| `jg_table` | struct | `include/ui.h:94` | `` |
| `offset` | type_alias | `include/ui.h:29` | `typedef struct ui_line { size_t offset;` |
| `out` | function | `include/ui.h:97` | `* ui_render_png does and fills *out (jg_init'ed by the caller) with one rect per * element in document coordinates...` |
| `placeholders` | function | `include/ui.h:107` | `* above always draw image placeholders (no worker to decode hostile bytes);` |
| `rd_doc` | struct | `include/ui.h:68` | `` |
| `space` | function | `include/ui.h:43` | `* Breaks at the last fitting space (the break space is consumed), hard-breaks * words longer than max_cols, and...` |
| `tab` | struct | `include/ui.h:104` | `` |
| `ui_clamp_scroll` | function | `include/ui.h:54` | `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines);` |
| `ui_layout` | struct | `include/ui.h:34` | `` |
| `ui_layout_free` | function | `include/ui.h:51` | `void ui_layout_free(ui_layout *lay);` |
| `ui_line` | struct | `include/ui.h:29` | `` |
| `ui_render_viewport_w` | function | `include/ui.h:141` | `int ui_render_viewport_w(void);` |
| `ui_status` | enum | `include/ui.h:19` | `` |
| `FREEDOM_URL_H` | macro | `include/url.h:2` | `#define FREEDOM_URL_H` |
| `URL_ERR_NOT_HTTPS` | function | `include/url.h:109` | `* URL_ERR_NOT_HTTPS (out untouched);` |
| `URL_MAX_LEN` | macro | `include/url.h:30` | `#define URL_MAX_LEN` |
| `URL_SEARCH_ENDPOINT` | macro | `include/url.h:76` | `#define URL_SEARCH_ENDPOINT` |
| `password` | function | `include/url.h:152` | `* username and password (owned, must be freed) into *username_out and * *password_out, and returns URL_OK. When...` |
| `path` | function | `include/url.h:115` | `* absolute path ("file:///..."). NULL => 0. */ int url_is_file(const char *s);` |
| `url` | function | `include/url.h:126` | `* Every field ALIASES the input url (not owned, valid while url is alive);` |
| `url_authority_len` | function | `include/url.h:51` | `size_t url_authority_len(const char *url);` |
| `url_file_path` | function | `include/url.h:121` | `const char *url_file_path(const char *s);` |
| `url_has_scheme` | function | `include/url.h:46` | `int url_has_scheme(const char *s);` |
| `url_is_https` | function | `include/url.h:42` | `int url_is_https(const char *s);` |
| `url_omni_kind` | enum | `include/url.h:78` | `` |
| `url_parts` | struct | `include/url.h:129` | `` |
| `url_status` | enum | `include/url.h:32` | `` |
| `UTIL_H` | macro | `include/util.h:5` | `#define UTIL_H` |
| `fnv1a` | function | `include/util.h:67` | `static inline uint64_t fnv1a(const char *s, size_t n)` |
| `mem_contains_ci` | function | `include/util.h:43` | `static inline int mem_contains_ci(const void *hay, size_t hlen, const char *needle)` |
| `read_full` | function | `include/util.h:26` | `static inline int read_full(int fd, void *buf, size_t n)` |
| `utf8_seq_len` | function | `include/util.h:57` | `static inline size_t utf8_seq_len(unsigned char c)` |
| `write_full` | function | `include/util.h:15` | `static inline int write_full(int fd, const void *buf, size_t n)` |
| `FREEDOM_WEB_STORAGE_H` | macro | `include/web_storage.h:2` | `#define FREEDOM_WEB_STORAGE_H` |
| `WST_MAX_KEYS` | macro | `include/web_storage.h:18` | `#define WST_MAX_KEYS` |
| `WST_MAX_ORIGINS` | macro | `include/web_storage.h:17` | `#define WST_MAX_ORIGINS` |
| `WST_ORIGIN_MAX` | macro | `include/web_storage.h:20` | `#define WST_ORIGIN_MAX` |
| `WST_QUOTA` | macro | `include/web_storage.h:19` | `#define WST_QUOTA` |
| `full` | function | `include/web_storage.h:45` | `* validating it in full (wst_decode_check). Returns 0, or -1 when invalid (fn is then * never called). The one...` |
| `wst_db` | type_alias | `include/web_storage.h:21` | `typedef struct wst_db wst_db;` |
| `wst_decode_check` | function | `include/web_storage.h:37` | `int wst_decode_check(const char *blob, size_t len);` |
| `wst_encode` | function | `include/web_storage.h:33` | `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len);` |
| `wst_free` | function | `include/web_storage.h:28` | `void wst_free(wst_db *db);` |
| `wst_new` | function | `include/web_storage.h:25` | `wst_db *wst_new(void);` |
| `wst_origin_bytes` | function | `include/web_storage.h:59` | `size_t wst_origin_bytes(const wst_db *db, const char *origin);` |
| `wst_replace` | function | `include/web_storage.h:42` | `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len);` |
| `FREEDOM_WEBCAPS_H` | macro | `include/webcaps.h:2` | `#define FREEDOM_WEBCAPS_H` |
| `js` | type_alias | `include/webcaps.h:38` | `typedef struct wc_caps { /* leak-free (global): granted by user toggle or allow.conf presentation-trust. */ bool js;` |
| `js_mode` | type_alias | `include/webcaps.h:57` | `typedef struct wc_input { jsp_mode js_mode;` |
| `wc_caps` | struct | `include/webcaps.h:38` | `` |
| `wc_input` | struct | `include/webcaps.h:57` | `` |
| `FREEDOM_WEBFONT_H` | macro | `include/webfont.h:2` | `#define FREEDOM_WEBFONT_H` |
| `WF_DATA_URL_MAX` | macro | `include/webfont.h:29` | `#define WF_DATA_URL_MAX` |
| `WF_FAMILY_MAX` | macro | `include/webfont.h:20` | `#define WF_FAMILY_MAX` |
| `WF_FORMAT_MAX` | macro | `include/webfont.h:22` | `#define WF_FORMAT_MAX` |
| `WF_MAX_FACE_BYTES` | macro | `include/webfont.h:24` | `#define WF_MAX_FACE_BYTES` |
| `WF_MAX_REFS` | macro | `include/webfont.h:23` | `#define WF_MAX_REFS` |
| `WF_MAX_TOTAL_BYTES` | macro | `include/webfont.h:25` | `#define WF_MAX_TOTAL_BYTES` |
| `WF_URL_MAX` | macro | `include/webfont.h:21` | `#define WF_URL_MAX` |
| `boundaries` | function | `include/webfont.h:57` | `* boundaries (scan_inline accumulation, loader collection). */ void wf_ref_move(wf_ref *dst, wf_ref *src);` |
| `family` | type_alias | `include/webfont.h:30` | `typedef struct wf_ref { char family[WF_FAMILY_MAX];` |
| `here` | function | `include/webfont.h:38` | `* set with the decoded bytes owned here (freed by wf_list_free);` |
| `wf_list` | struct | `include/webfont.h:46` | `` |
| `wf_list_free` | function | `include/webfont.h:53` | `void wf_list_free(wf_list *l);` |
| `wf_name_hash` | function | `include/webfont.h:69` | `static inline unsigned wf_name_hash(const char *s, size_t n)` |
| `wf_ref` | struct | `include/webfont.h:31` | `` |
| `wf_scan` | function | `include/webfont.h:52` | `int wf_scan(const char *css, size_t len, wf_list *out);` |
| `wf_supported_format` | function | `include/webfont.h:60` | `int wf_supported_format(const char *fmt);` |
| `FREEDOM_WEBFONT_LOAD_H` | macro | `include/webfont_load.h:2` | `#define FREEDOM_WEBFONT_LOAD_H` |
| `WF_LOAD_MAX_FETCHES` | macro | `include/webfont_load.h:52` | `#define WF_LOAD_MAX_FETCHES` |
| `WF_LOAD_MAX_KEYS` | macro | `include/webfont_load.h:51` | `#define WF_LOAD_MAX_KEYS` |
| `WF_LOAD_TRIES_PER_KEY` | macro | `include/webfont_load.h:50` | `#define WF_LOAD_TRIES_PER_KEY` |
| `free` | function | `include/webfont_load.h:31` | `* free()), *out_status the HTTP status. Nonzero on refusal/error (fail-closed: * the face is skipped, never the...` |
| `wf_load_document` | function | `include/webfont_load.h:46` | `int wf_load_document(wf_fetch_fn fetch, void *fctx, const char *page_url, const wf_sheet *extern_sheets, size_t...` |
| `wf_sheet` | struct | `include/webfont_load.h:24` | `` |
| `FREEDOM_WS_HUB_H` | macro | `include/ws_hub.h:2` | `#define FREEDOM_WS_HUB_H` |
| `WH_CLOSE_ABNORMAL` | macro | `include/ws_hub.h:27` | `#define WH_CLOSE_ABNORMAL` |
| `WH_MAX` | macro | `include/ws_hub.h:21` | `#define WH_MAX` |
| `generation` | function | `include/ws_hub.h:50` | `* previous generation (before wh_close_all) are closed and dropped silently. */ void wh_on_notify(wh_hub *h...` |
| `wh_close` | function | `include/ws_hub.h:58` | `void wh_close(wh_hub *h, int id);` |
| `wh_close_all` | function | `include/ws_hub.h:61` | `void wh_close_all(wh_hub *h);` |
| `wh_count` | function | `include/ws_hub.h:73` | `size_t wh_count(const wh_hub *h);` |
| `wh_free` | function | `include/ws_hub.h:38` | `void wh_free(wh_hub *h);` |
| `wh_hub` | type_alias | `include/ws_hub.h:30` | `typedef struct wh_hub wh_hub;` |
| `wh_new` | function | `include/ws_hub.h:34` | `wh_hub *wh_new(void);` |
| `wh_notify_fd` | function | `include/ws_hub.h:41` | `int wh_notify_fd(const wh_hub *h);` |
| `wh_on_readable` | function | `include/ws_hub.h:70` | `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx);` |
| `wh_open_async` | function | `include/ws_hub.h:46` | `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg);` |
| `wh_poll_fds` | function | `include/ws_hub.h:65` | `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap);` |
| `wh_send` | function | `include/ws_hub.h:54` | `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary);` |
| `FREEDOM_ZOOM_H` | macro | `include/zoom.h:2` | `#define FREEDOM_ZOOM_H` |
| `ZM_DEFAULT_PCT` | macro | `include/zoom.h:23` | `#define ZM_DEFAULT_PCT` |
| `ZM_MAX_PCT` | macro | `include/zoom.h:22` | `#define ZM_MAX_PCT` |
| `ZM_MIN_PCT` | macro | `include/zoom.h:21` | `#define ZM_MIN_PCT` |
| `zm_apply` | function | `include/zoom.h:42` | `double zm_apply(double base_px, int pct);` |
| `zm_clamp` | function | `include/zoom.h:26` | `int zm_clamp(int pct);` |
| `zm_reset` | function | `include/zoom.h:35` | `int zm_reset(void);` |
| `zm_scale` | function | `include/zoom.h:38` | `double zm_scale(int pct);` |
| `zm_zoom_in` | function | `include/zoom.h:29` | `int zm_zoom_in(int pct);` |
| `zm_zoom_out` | function | `include/zoom.h:32` | `int zm_zoom_out(int pct);` |
| `fp_accept_language` | function | `src/anti_fp.c:27` | `const char *fp_accept_language(void)` |
| `fp_accept_language_header` | function | `src/anti_fp.c:31` | `const char *fp_accept_language_header(void)` |
| `fp_app_code_name` | function | `src/anti_fp.c:61` | `const char *fp_app_code_name(void)` |
| `fp_app_name` | function | `src/anti_fp.c:69` | `const char *fp_app_name(void)` |
| `fp_app_version` | function | `src/anti_fp.c:57` | `const char *fp_app_version(void)` |
| `fp_bucket_screen` | function | `src/anti_fp.c:99` | `void fp_bucket_screen(int w, int h, int *out_w, int *out_h)` |
| `fp_build_id` | function | `src/anti_fp.c:81` | `const char *fp_build_id(void)` |
| `fp_coarsen_time_ms` | function | `src/anti_fp.c:17` | `uint64_t fp_coarsen_time_ms(uint64_t raw_ms)` |
| `fp_cookie_enabled` | function | `src/anti_fp.c:93` | `int fp_cookie_enabled(void)` |
| `fp_device_memory_gb` | function | `src/anti_fp.c:51` | `int fp_device_memory_gb(void)` |
| `fp_hardware_concurrency` | function | `src/anti_fp.c:47` | `int fp_hardware_concurrency(void)` |
| `fp_max_touch_points` | function | `src/anti_fp.c:85` | `int fp_max_touch_points(void)` |
| `fp_on_line` | function | `src/anti_fp.c:89` | `int fp_on_line(void)` |
| `fp_origin_key` | function | `src/anti_fp.c:139` | `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain)` |
| `fp_oscpu` | function | `src/anti_fp.c:77` | `const char *fp_oscpu(void)` |
| `fp_perturb` | function | `src/anti_fp.c:128` | `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key)` |
| `fp_platform` | function | `src/anti_fp.c:39` | `const char *fp_platform(void)` |
| `fp_product` | function | `src/anti_fp.c:65` | `const char *fp_product(void)` |
| `fp_product_sub` | function | `src/anti_fp.c:73` | `const char *fp_product_sub(void)` |
| `fp_timezone` | function | `src/anti_fp.c:35` | `const char *fp_timezone(void)` |
| `fp_user_agent` | function | `src/anti_fp.c:23` | `const char *fp_user_agent(void)` |
| `fp_vendor` | function | `src/anti_fp.c:43` | `const char *fp_vendor(void)` |
| `splitmix64` | function | `src/anti_fp.c:121` | `static uint64_t splitmix64(uint64_t *state)` |
| `bf_collapse` | function | `src/block_flow.c:30` | `double bf_collapse(double a, double b)` |
| `bf_collapse_n` | function | `src/block_flow.c:15` | `double bf_collapse_n(const double *m, size_t n)` |
| `bf_margins_adjoin` | function | `src/block_flow.c:35` | `int bf_margins_adjoin(double border_px, double padding_px)` |
| `finite_or_zero` | function | `src/block_flow.c:11` | `static double finite_or_zero(double v)` |
| `BLOCK` | macro | `src/box_style.c:65` | `#define BLOCK` |
| `BX_DISPLAY_MAX` | macro | `src/box_style.c:23` | `#define BX_DISPLAY_MAX` |
| `BX_TAG_MAX` | macro | `src/box_style.c:22` | `#define BX_TAG_MAX` |
| `DISP_N` | macro | `src/box_style.c:257` | `#define DISP_N` |
| `EDG` | macro | `src/box_style.c:70` | `#define EDG(t, r, b, l)` |
| `IBLOCK` | macro | `src/box_style.c:67` | `#define IBLOCK` |
| `INLINE` | macro | `src/box_style.c:66` | `#define INLINE` |
| `LITEM` | macro | `src/box_style.c:68` | `#define LITEM` |
| `NONE` | macro | `src/box_style.c:69` | `#define NONE` |
| `TAG_N` | macro | `src/box_style.c:159` | `#define TAG_N` |
| `T_CAP` | macro | `src/box_style.c:78` | `#define T_CAP` |
| `T_CELL` | macro | `src/box_style.c:77` | `#define T_CELL` |
| `T_COL` | macro | `src/box_style.c:79` | `#define T_COL` |
| `T_GRP` | macro | `src/box_style.c:75` | `#define T_GRP` |
| `T_NO` | macro | `src/box_style.c:73` | `#define T_NO` |
| `T_ROW` | macro | `src/box_style.c:76` | `#define T_ROW` |
| `T_TBL` | macro | `src/box_style.c:74` | `#define T_TBL` |
| `ZERO` | macro | `src/box_style.c:71` | `#define ZERO` |
| `bg_size_component` | function | `src/box_style.c:375` | `static double bg_size_component(int px_val, int pct_pm, double area)` |
| `bx_background_layer` | function | `src/box_style.c:382` | `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h,                     ...` |
| `bx_block_ua_box` | function | `src/box_style.c:223` | `bx_box bx_block_ua_box(int heading_level, int in_list, bx_ua_tag ua)` |
| `bx_border_box_h` | function | `src/box_style.c:333` | `double bx_border_box_h(double declared_h, int border_box,                        double pad_t, do...` |
| `bx_content_cap` | function | `src/box_style.c:361` | `double bx_content_cap(double width_cap, int border_box,                       double pad_l, doubl...` |
| `bx_content_clipped` | function | `src/box_style.c:344` | `int bx_content_clipped(int overflow_x, int overflow_y)` |
| `bx_default_for_tag` | function | `src/box_style.c:161` | `bx_box bx_default_for_tag(const char *tag)` |
| `bx_default_for_ua` | function | `src/box_style.c:217` | `bx_box bx_default_for_ua(bx_ua_tag id)` |
| `bx_display_name` | function | `src/box_style.c:421` | `const char *bx_display_name(bx_display d)` |
| `bx_lp_px` | function | `src/box_style.c:350` | `double bx_lp_px(int px_val, int pct_pm, double basis)` |
| `bx_parse_display` | function | `src/box_style.c:259` | `bx_status bx_parse_display(const char *token, bx_display *out)` |
| `bx_place` | function | `src/box_style.c:269` | `bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,                 ...` |
| `bx_replaced_box` | function | `src/box_style.c:319` | `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den,                     doub...` |
| `bx_table_role_of` | function | `src/box_style.c:169` | `bx_table_role bx_table_role_of(const char *tag, css_display display)` |
| `bx_ua_of_tag` | function | `src/box_style.c:208` | `bx_ua_tag bx_ua_of_tag(const char *tag)` |
| `bx_width_cap` | function | `src/box_style.c:286` | `double bx_width_cap(int w_px, int w_pct, double avail_w)` |
| `bx_width_cap2` | function | `src/box_style.c:311` | `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w)` |
| `copy_lower_trim` | function | `src/box_style.c:35` | `static int copy_lower_trim(const char *in, char *out, size_t out_size)` |
| `disp_row` | struct | `src/box_style.c:239` | `` |
| `is_ws` | function | `src/box_style.c:29` | `static int is_ws(char c)` |
| `name_cmp` | function | `src/box_style.c:48` | `static int name_cmp(const void *key, const void *elem)` |
| `tag_row` | struct | `src/box_style.c:59` | `` |
| `take` | function | `src/box_style.c:293` | `* caller has to take (Sizing 3 section 5.1), so to a resolver that only sums a * px and a percentage half they read...` |
| `BT_LEN_AUTO` | macro | `src/box_tree.c:31` | `#define BT_LEN_AUTO` |
| `BT_WRAP_EPS` | macro | `src/box_tree.c:62` | `#define BT_WRAP_EPS` |
| `assign_doc_order` | function | `src/box_tree.c:412` | `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,                   ...` |
| `block` | function | `src/box_tree.c:473` | `* true block (same flow neighbourhood), strictly better than zeros. NULL      * placed keeps lega...` |
| `bt_box_hidden` | function | `src/box_tree.c:683` | `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)` |
| `bt_containing_block` | function | `src/box_tree.c:462` | `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i,                         ...` |
| `bt_layout` | function | `src/box_tree.c:372` | `bt_status bt_layout(bt_node *root, double avail_w)` |
| `bt_nn` | function | `src/box_tree.c:58` | `static double bt_nn(double v)` |
| `bt_oof_anchor` | function | `src/box_tree.c:675` | `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)` |
| `bt_oof_avail` | function | `src/box_tree.c:696` | `double bt_oof_avail(int a, int a_pct, int b, int b_pct, double cb, int *both)` |
| `bt_oof_root` | function | `src/box_tree.c:679` | `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)` |
| `bt_resolve_positioning` | function | `src/box_tree.c:492` | `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,                           ...` |
| `bt_resolve_positioning_ex` | function | `src/box_tree.c:503` | `bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,                        ...` |
| `find_positioned_ancestor` | function | `src/box_tree.c:429` | `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,                        ...` |
| `inset_unset` | function | `src/box_tree.c:458` | `static int inset_unset(int v, int pct_pm)` |
| `layout_block` | function | `src/box_tree.c:37` | `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,                    ...` |
| `layout_flex` | function | `src/box_tree.c:97` | `static bt_status layout_flex(bt_node *node, bt_node *const *kids, size_t nk,                     ...` |
| `layout_grid` | function | `src/box_tree.c:220` | `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,                     ...` |
| `layout_node` | function | `src/box_tree.c:327` | `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)` |
| `oof_walk` | function | `src/box_tree.c:658` | `static int oof_walk(const pv_box_def *boxes, size_t nbox, int bid, int nearest)` |
| `resolve_inset` | function | `src/box_tree.c:449` | `static double resolve_inset(int v, int pct_pm, double basis)` |
| `wrap_reverse` | function | `src/box_tree.c:79` | `*  * wrap_reverse (node->wrap_reverse): when node->wrap is active and node->wrap_reverse  * is no...` |
| `_POSIX_C_SOURCE` | macro | `src/browser.c:7` | `#define _POSIX_C_SOURCE` |
| `browser_add_exception` | function | `src/browser.c:472` | `browser_status browser_add_exception(browser_state *bs, const char *host)` |
| `browser_back` | function | `src/browser.c:268` | `browser_status browser_back(browser_state *bs)` |
| `browser_can_back` | function | `src/browser.c:292` | `int browser_can_back(const browser_state *bs)` |
| `browser_can_forward` | function | `src/browser.c:296` | `int browser_can_forward(const browser_state *bs)` |
| `browser_commit_url_bar` | function | `src/browser.c:190` | `browser_status browser_commit_url_bar(browser_state *bs)` |
| `browser_current_url` | function | `src/browser.c:300` | `const char *browser_current_url(const browser_state *bs)` |
| `browser_doc_index` | function | `src/browser.c:260` | `int browser_doc_index(const browser_state *bs)` |
| `browser_entry_doc` | function | `src/browser.c:255` | `int browser_entry_doc(const browser_state *bs, size_t pos)` |
| `browser_forward` | function | `src/browser.c:280` | `browser_status browser_forward(browser_state *bs)` |
| `browser_free` | function | `src/browser.c:167` | `void browser_free(browser_state *bs)` |
| `browser_init` | function | `src/browser.c:156` | `browser_status browser_init(browser_state *bs)` |
| `browser_is_exception` | function | `src/browser.c:464` | `int browser_is_exception(const browser_state *bs, const char *host)` |
| `browser_navigate` | function | `src/browser.c:224` | `browser_status browser_navigate(browser_state *bs, const char *url)` |
| `browser_push_state` | function | `src/browser.c:236` | `browser_status browser_push_state(browser_state *bs, const char *url)` |
| `browser_replace_state` | function | `src/browser.c:243` | `browser_status browser_replace_state(browser_state *bs, const char *url)` |
| `browser_set_page` | function | `src/browser.c:409` | `browser_status browser_set_page(browser_state *bs, const char *title,                            ...` |
| `browser_set_status` | function | `src/browser.c:431` | `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)` |

Next: [SYMBOLS_p5.md](SYMBOLS_p5.md)
