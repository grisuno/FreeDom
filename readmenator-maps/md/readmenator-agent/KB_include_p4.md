# Subsystem: include (page 4 of 5)
Previous: [KB_include_p3.md](KB_include_p3.md)

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
  - `rd_doc` (struct, line 262)
  - `img_fail_reason` (enum, line 34)
  - `rd_kind` (enum, line 42)
  - `rd_status` (enum, line 294)
  - `kind` (type_alias, line 64) `typedef struct rd_block { rd_kind kind;`
  - `list` (function, line 18) `* inert display list (page_view) and the presentation orchestrator (the GUI and * the --headless writer). It decides...`
  - `RD_IMAGE` (function, line 59) `* RD_IMAGE (image src) and RD_INPUT (the owning form's action);`
  - `form` (function, line 63) `* form (-1 = none);`
  - `default` (function, line 150) `* default (layout is structure, not author styling, and leaks nothing to the * network) so the presentation layer...`
  - `to` (function, line 248) `* belongs to (-1 = none);`
  - `rdp_images_warning` (function, line 303) `* rdp_images_warning() is prepended so the user is always told. Each image * becomes an RD_IMAGE block whose...`
  - `rd_free` (function, line 313) `void rd_free(rd_doc *d);`
  - `rd_count` (function, line 316) `size_t rd_count(const rd_doc *d);`
  - `rd_at` (function, line 317) `const rd_block *rd_at(const rd_doc *d, size_t i);`
  - `rd_box_count` (function, line 321) `size_t rd_box_count(const rd_doc *d);`
  - `rd_box_at` (function, line 322) `const pv_box_def *rd_box_at(const rd_doc *d, size_t i);`
  - `rd_cont_count` (function, line 326) `size_t rd_cont_count(const rd_doc *d);`
  - `rd_cont_at` (function, line 327) `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i);`
  - `rd_kind_name` (function, line 331) `const char *rd_kind_name(rd_kind k);`
  - `rd_block_tag` (function, line 339) `const char *rd_block_tag(const rd_block *b);`
  - `rd_block_heading_level` (function, line 346) `int rd_block_heading_level(const rd_block *b);`
  - `decision` (function, line 349) `* decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never * NULL. */ const char...`
  - `IMG_FAIL_OK` (function, line 355) `* IMG_FAIL_OK (not a failure) or the reason is unknown. */ const char *rd_image_fail_label(img_fail_reason reason);`
  - `rd_input_label` (function, line 360) `const char *rd_input_label(int input_type);`
  - `rd_input_invisible` (function, line 365) `int rd_input_invisible(int input_type);`
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
- Doc: rp_host_of: Lowercased host of an absolute URL into out.
- Layer: business_logic
- Language: h
- Symbols:
  - `rp_decision` (enum, line 21)
  - `rp_host_of` (function, line 30) `int rp_host_of(const char *url, char *out, size_t out_size);`
  - `rp_site_of` (function, line 34) `int rp_site_of(const char *host, char *out, size_t out_size);`
  - `rp_same_site` (function, line 37) `int rp_same_site(const char *top_level_url, const char *request_url);`
  - `FREEDOM_REQUEST_POLICY_H` (macro, line 2) `#define FREEDOM_REQUEST_POLICY_H`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/render_policy.c`, `src/request_policy.c`, `src/tab.c`, `tests/test_request_policy.c`

## include/secure_fetch.h
- Doc: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. *...
- Layer: utility
- Language: h
- Symbols:
  - `sf_chain_info` (struct, line 60)
  - `sf_config` (struct, line 75)
  - `sf_response` (struct, line 117)
  - `sf_status` (enum, line 23)
  - `sf_policy` (enum, line 40)
  - `sf_proxy_type` (enum, line 69)
  - `policy` (type_alias, line 74) `typedef struct sf_config { sf_policy policy;`
  - `status` (type_alias, line 116) `typedef struct sf_response { sf_status status;`
  - `sf_ws` (type_alias, line 293) `typedef struct sf_ws sf_ws;`
  - `validators` (function, line 17) `* The security logic lives in pure validators (no I/O);`
  - `sf_global_init` (function, line 204) `void sf_global_init(void);`
  - `EXCLUDED` (function, line 210) `* cookies are EXCLUDED (network-only, never exposed to JS) and expired cookies skipped. * Only for a TRUSTED host...`
  - `sf_cookie_put` (function, line 217) `void sf_cookie_put(const char *url, const char *namevalue);`
  - `sf_cookie_line_matches` (function, line 222) `int sf_cookie_line_matches(const char *line, const char *host, const char *path, long now, char *out, size_t outsz);`
  - `sf_user_agent_or_default` (function, line 231) `const char *sf_user_agent_or_default(const char *ua);`
  - `sf_impersonate_kex_groups` (function, line 235) `const char *sf_impersonate_kex_groups(void);`
  - `sf_impersonate_tls13_ciphers` (function, line 236) `const char *sf_impersonate_tls13_ciphers(void);`
  - `skipped` (function, line 256) `* skipped (a classical key exchange is accepted);`
  - `sf_is_redirect_code` (function, line 267) `int sf_is_redirect_code(long http_code);`
  - `bits` (function, line 310) `* *flags receives CURLWS_* bits (text/binary/close/cont);`
  - `sf_ws_fd` (function, line 317) `int sf_ws_fd(const sf_ws *ws);`
  - `sf_ws_close` (function, line 320) `void sf_ws_close(sf_ws *ws);`
  - `connection` (function, line 324) `* on each connection (Zero Trust). Each target is re-validated and a downgrade * to http:// is refused. Exceeding...`
  - `sf_get` (function, line 333) `* sf_get (Zero Trust): an insecure POST is not representable. Does not follow * redirects (the caller inspects...`
  - `sf_response_free` (function, line 344) `void sf_response_free(sf_response *resp);`
  - `FREEDOM_SECURE_FETCH_H` (macro, line 2) `#define FREEDOM_SECURE_FETCH_H`
  - `SF_DEFAULT_KEX_GROUPS` (macro, line 143) `#define SF_DEFAULT_KEX_GROUPS`
  - `SF_IMPERSONATE_KEX_GROUPS` (macro, line 152) `#define SF_IMPERSONATE_KEX_GROUPS`
  - `SF_IMPERSONATE_TLS13_CIPHERS` (macro, line 153) `#define SF_IMPERSONATE_TLS13_CIPHERS`
  - `SF_IMPERSONATE_TLS12_CIPHERS` (macro, line 157) `#define SF_IMPERSONATE_TLS12_CIPHERS`
  - `SF_DEFAULT_USER_AGENT` (macro, line 168) `#define SF_DEFAULT_USER_AGENT`
  - `SF_DEFAULT_MAX_BODY` (macro, line 169) `#define SF_DEFAULT_MAX_BODY`
  - `SF_DEFAULT_TIMEOUT_MS` (macro, line 170) `#define SF_DEFAULT_TIMEOUT_MS`
  - `SF_CONNECT_TIMEOUT_MS` (macro, line 193) `#define SF_CONNECT_TIMEOUT_MS`
  - `SF_SUBRESOURCE_TIMEOUT_MS` (macro, line 194) `#define SF_SUBRESOURCE_TIMEOUT_MS`
  - `SF_DEFAULT_MAX_REDIRECTS` (macro, line 195) `#define SF_DEFAULT_MAX_REDIRECTS`
  - `SF_MAX_URL` (macro, line 196) `#define SF_MAX_URL`
  - `SF_WS_MAX_MESSAGE` (macro, line 292) `#define SF_WS_MAX_MESSAGE`
- Depends on: `include/anti_fp.h`
- Imported by: `gui/browser_ui.c`, `include/ws_hub.h`, `src/freedom.c`, `src/secure_fetch.c`, `tests/itest_secure_fetch.c`, `tests/test_secure_fetch.c`

## include/svg_paint.h
- Doc: svp_draw: Paints `img` into the rect [x, y, w, h] of `cr`, scaled uniformly and centred...
- Layer: utility
- Language: h
- Symbols:
  - `svp_draw` (function, line 31) `void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, double h, int current_rgb);`
  - `FREEDOM_SVG_PAINT_H` (macro, line 2) `#define FREEDOM_SVG_PAINT_H`
- Depends on: `include/svg_render.h`
- Imported by: `gui/browser_ui.c`, `gui/svg_paint.c`

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
- Imported by: `fuzz/fuzz_svg_render.c`, `gui/browser_ui.c`, `include/svg_paint.h`, `src/page_view.c`, `src/svg_render.c`, `tests/test_svg_render.c`

## include/tab.h
- Doc: tab_hist_op: One history operation the page's JS performed (spec/js_dom.md 7e): pushState...
- Layer: utility
- Language: h
- Symbols:
  - `tab_hist_op` (struct, line 53)
  - `tab_ws_op` (struct, line 68)
  - `tab_page` (struct, line 75)
  - `tab_eval_result` (struct, line 127)
  - `tab_image` (struct, line 140)
  - `tab_status` (enum, line 31)
  - `tab_ws_kind` (enum, line 60)
  - `tab_ws_event_kind` (enum, line 64)
  - `tab` (type_alias, line 45) `typedef struct tab tab;`
  - `replace` (type_alias, line 53) `typedef struct tab_hist_op { int replace;`
  - `kind` (type_alias, line 67) `typedef struct tab_ws_op { int kind;`
  - `width` (type_alias, line 140) `typedef struct tab_image { uint32_t width;`
  - `tab_worker_dispatch` (function, line 152) `* Call tab_worker_dispatch(argc, argv) as the FIRST thing in main(): if argv is the * internal "--tab-worker <rfd>...`
  - `tab_open` (function, line 156) `* and reaches tab_open (the app and the test harness) must call this first. */ void tab_worker_dispatch(int argc...`
  - `tab_parse_worker_args` (function, line 163) `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd);`
  - `out_status` (function, line 175) `* On success return 0 and set *out_status (HTTP status), *out_body / *out_body_len * (malloc'd response bytes, tab...`
  - `tab_set_fetcher` (function, line 186) `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx);`
  - `bytes` (function, line 190) `* so the parent can retain the bytes (spec/webfont.md b3b feeds them to the * @font-face loader as extern sheets)....`
  - `tab_set_css_sink` (function, line 199) `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx);`
  - `tab_set_net_allowed` (function, line 204) `void tab_set_net_allowed(tab *t, int allowed);`
  - `jar` (function, line 207) `* the trusted parent read from its ephemeral network jar (sf_cookie_header_for). Only * meaningful for a trusted...`
  - `tab_set_cookies` (function, line 211) `void tab_set_cookies(tab *t, const char *cookies);`
  - `origin` (function, line 214) `* page origin (web_storage snapshot, copied). Used only when the load is trusted * (net granted);`
  - `tab_set_storage` (function, line 216) `void tab_set_storage(tab *t, const char *blob, size_t len);`
  - `exclusively` (function, line 222) `* exclusively (tab_subreq_permitted). Default 0: zero fetches, Privacy by Default. */ void tab_set_css_allowed(tab...`
  - `tab_set_viewport_w` (function, line 230) `void tab_set_viewport_w(tab *t, int px);`
  - `tab_last_subreq_stats` (function, line 236) `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us);`
  - `tab_subreq_permitted` (function, line 241) `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method);`
  - `view` (function, line 249) `* <noscript> handling in the built view (off => fallback shown, on => suppressed) * and is where allowlisted...`
  - `string` (function, line 269) `* event_type is a JS event type string (e.g. "keydown", "input", "change"). * key is the keyboard key value (may be...`
  - `granted` (function, line 318) `* granted (allow.conf AND js.conf);`
  - `returned` (function, line 319) `* returned (the page keeps its zeros). The worker re-checks the same condition. * g must be finished (jg_finish). */...`
  - `popstate` (function, line 325) `* popstate (+ hashchange) and re-derives the view like a click. */ tab_status tab_popstate(tab *t, int index...`
  - `decode` (function, line 344) `* could not decode (caller shows the placeholder), which is not a transport error. * TAB_ERR_* is reserved for...`
  - `tab_alive` (function, line 357) `int tab_alive(const tab *t);`
  - `tab_child_pid` (function, line 360) `pid_t tab_child_pid(const tab *t);`
  - `tab_close` (function, line 363) `void tab_close(tab *t);`
  - `tab_page_free` (function, line 366) `void tab_page_free(tab_page *p);`
  - `tab_eval_result_free` (function, line 367) `void tab_eval_result_free(tab_eval_result *r);`
  - `tab_image_free` (function, line 368) `void tab_image_free(tab_image *img);`
  - `FREEDOM_TAB_H` (macro, line 2) `#define FREEDOM_TAB_H`
  - `TAB_MAX_INPUT` (macro, line 148) `#define TAB_MAX_INPUT`
- Depends on: `include/freebug.h`, `include/js_geom.h`, `include/page_view.h`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/tab.c`, `tests/test_tab.c`

## include/text_case.h
- Doc: Case mapping for text-transform and synthesized small caps (spec/text_case.md).
- Layer: utility
- Language: h
- Symbols:
  - `tc_run` (struct, line 33)
  - `cp` (function, line 19) `* cp (identity otherwise), so a transformed text keeps its length. */ uint32_t tc_upper(uint32_t cp);`
  - `tc_lower` (function, line 21) `uint32_t tc_lower(uint32_t cp);`
  - `tc_is_lower` (function, line 24) `int tc_is_lower(uint32_t cp);`
  - `tc_transform` (function, line 29) `size_t tc_transform(const char *s, size_t n, int transform, int word_start, char *out, size_t cap);`
  - `tc_smallcaps_runs` (function, line 41) `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap);`
  - `FREEDOM_TEXT_CASE_H` (macro, line 2) `#define FREEDOM_TEXT_CASE_H`
  - `TC_SMALLCAPS_SCALE` (macro, line 15) `#define TC_SMALLCAPS_SCALE`
- Imported by: `fuzz/fuzz_text_case.c`, `gui/browser_ui.c`, `src/text_case.c`, `tests/test_text_case.c`

## include/text_shape.h
- Doc: tsh_font: Font selector: a css_font_family bucket (CSS_FF_*) plus weight/slant flags.
- Layer: utility
- Language: h
- Symbols:
  - `tsh_font` (struct, line 33)
  - `tsh_run` (struct, line 132)
  - `tsh_status` (enum, line 80)
  - `family` (type_alias, line 33) `typedef struct tsh_font { int family;`
  - `end` (type_alias, line 132) `typedef struct tsh_run { size_t start, end;`
  - `content` (function, line 11) `* TEXT is hostile remote content (sanitised UTF-8) and is fuzzed (make fuzz-tsh);`
  - `tsh_family_is_generic` (function, line 52) `int tsh_family_is_generic(const char *name);`
  - `wins` (function, line 58) `* the first name the resolver accepts wins (returns 1, family in out). Pure: the * resolver is injected (fontconfig...`
  - `tsh_pick_family` (function, line 68) `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong, size_t n, int...`
  - `tsh_local_handle` (function, line 75) `int tsh_local_handle(const char *list);`
  - `tsh_ready` (function, line 89) `int tsh_ready(void);`
  - `origin` (function, line 92) `* glyphs are written with positions relative to origin (0,0) on the baseline, * and *out_adv holds the total pen...`
  - `tsh_measure` (function, line 101) `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len);`
  - `tsh_webfont_register` (function, line 114) `int tsh_webfont_register(const char *name, const unsigned char *bytes, size_t nbytes, int bold, int italic);`
  - `tsh_webfont_clear` (function, line 120) `void tsh_webfont_clear(void);`
  - `tsh_face` (function, line 127) `cairo_font_face_t *tsh_face(const tsh_font *f);`
  - `own` (function, line 136) `* face of their own (controls, combining marks, variation selectors, ZWJ/ZWNJ) * stay in the run before them....`
  - `tsh_shutdown` (function, line 143) `void tsh_shutdown(void);`
  - `FREEDOM_TEXT_SHAPE_H` (macro, line 19) `#define FREEDOM_TEXT_SHAPE_H`
  - `TSH_LOCAL_LISTS` (macro, line 46) `#define TSH_LOCAL_LISTS`
  - `TSH_LOCAL_FAMILIES` (macro, line 47) `#define TSH_LOCAL_FAMILIES`
  - `TSH_FAMILY_MAX` (macro, line 48) `#define TSH_FAMILY_MAX`
  - `TSH_MAX_GLYPHS` (macro, line 77) `#define TSH_MAX_GLYPHS`
  - `TSH_MAX_TEXT` (macro, line 78) `#define TSH_MAX_TEXT`
- Imported by: `fuzz/fuzz_text_shape.c`, `gui/browser_ui.c`, `src/freedom.c`, `src/text_shape.c`, `src/webfont_load.c`, `tests/test_text_shape.c`, `tests/test_webfont_load.c`

## include/textfield.h
- Doc: tf_init: typedef struct tf_field { char   buf[TF_CAP]; /* content, always NUL-terminated at...
- Layer: utility
- Language: h
- Symbols:
  - `tf_field` (struct, line 25)
  - `tf_status` (enum, line 31)
  - `buf` (type_alias, line 24) `typedef struct tf_field { char buf[TF_CAP];`
  - `tf_init` (function, line 38) `void tf_init(tf_field *f);`
  - `tf_clear` (function, line 45) `void tf_clear(tf_field *f);`
  - `tf_backspace` (function, line 53) `void tf_backspace(tf_field *f);`
  - `tf_delete` (function, line 56) `void tf_delete(tf_field *f);`
  - `tf_move` (function, line 59) `void tf_move(tf_field *f, long delta);`
  - `tf_home` (function, line 62) `void tf_home(tf_field *f);`
  - `tf_end` (function, line 63) `void tf_end(tf_field *f);`
  - `tf_text` (function, line 66) `const char *tf_text(const tf_field *f);`
  - `tf_len` (function, line 67) `size_t tf_len(const tf_field *f);`
  - `tf_cursor` (function, line 68) `size_t tf_cursor(const tf_field *f);`
  - `FREEDOM_TEXTFIELD_H` (macro, line 2) `#define FREEDOM_TEXTFIELD_H`
  - `TF_CAP` (macro, line 23) `#define TF_CAP`
- Imported by: `gui/browser_ui.c`, `src/textfield.c`, `tests/test_textfield.c`

## include/tls_impersonate.h
- Doc: ti_req: Request: parent -> helper.
- Layer: utility
- Language: h
- Symbols:
  - `ti_req` (struct, line 72)
  - `ti_resp` (struct, line 82)
  - `ti_profile` (enum, line 41)
  - `status` (type_alias, line 82) `typedef struct ti_resp { long status;`
  - `path` (function, line 26) `* Zero Knowledge path (PQ-hybrid, VERIFYPEER). * * 2. ti_encode_x / ti_decode_x — the length-prefixed, fail-closed...`
  - `chain` (function, line 32) `* * The response carries the peer certificate chain (DER) and the negotiated group so * the TRUSTED PARENT...`
  - `ti_should_impersonate` (function, line 56) `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled, int user_opt_in);`
  - `success` (function, line 97) `* ti_decode_* returns 0 on success (out fully populated), <0 on any malformed, * truncated or over-cap input (out...`
  - `ti_decode_req` (function, line 101) `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out);`
  - `ti_req_free` (function, line 102) `void ti_req_free(ti_req *r);`
  - `ti_encode_resp` (function, line 104) `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap);`
  - `ti_decode_resp` (function, line 105) `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out);`
  - `ti_resp_free` (function, line 106) `void ti_resp_free(ti_resp *r);`
  - `FREEDOM_TLS_IMPERSONATE_H` (macro, line 2) `#define FREEDOM_TLS_IMPERSONATE_H`
  - `TI_MAGIC` (macro, line 60) `#define TI_MAGIC`
  - `TI_MAX_URL` (macro, line 61) `#define TI_MAX_URL`
  - `TI_MAX_METHOD` (macro, line 62) `#define TI_MAX_METHOD`
  - `TI_MAX_HEADERS` (macro, line 63) `#define TI_MAX_HEADERS`
  - `TI_MAX_BODY` (macro, line 64) `#define TI_MAX_BODY`
  - `TI_MAX_RESP_HDR` (macro, line 65) `#define TI_MAX_RESP_HDR`
  - `TI_MAX_RESP_BODY` (macro, line 66) `#define TI_MAX_RESP_BODY`
  - `TI_MAX_CHAIN` (macro, line 67) `#define TI_MAX_CHAIN`
  - `TI_MAX_GROUP` (macro, line 68) `#define TI_MAX_GROUP`
- Imported by: `fuzz/fuzz_tls_impersonate.c`, `gui/browser_ui.c`, `src/freedom.c`, `src/tls_impersonate.c`, `tests/test_tls_impersonate.c`

## include/ui.h
- Doc: ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no...
- Layer: presentation
- Language: h
- Symbols:
  - `ui_line` (struct, line 29)
  - `ui_layout` (struct, line 34)
  - `rd_doc` (struct, line 68)
  - `jg_table` (struct, line 94)
  - `tab` (struct, line 104)
  - `ui_status` (enum, line 19)
  - `offset` (type_alias, line 29) `typedef struct ui_line { size_t offset;`
  - `space` (function, line 43) `* Breaks at the last fitting space (the break space is consumed), hard-breaks * words longer than max_cols, and...`
  - `ui_layout_free` (function, line 51) `void ui_layout_free(ui_layout *lay);`
  - `ui_clamp_scroll` (function, line 54) `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines);`
  - `available` (function, line 85) `* cheapest artifact to inspect a render where no display is available (CI, an AI * agent): export, then read the PNG...`
  - `out` (function, line 97) `* ui_render_png does and fills *out (jg_init'ed by the caller) with one rect per * element in document coordinates...`
  - `placeholders` (function, line 107) `* above always draw image placeholders (no worker to decode hostile bytes);`
  - `disk` (function, line 112) `* images are read from disk (confined to the document directory by render_doc). * top_url is the page origin (https...`
  - `images` (function, line 114) `* fetcher loads no images (placeholders, as before). Any image that fails falls back * to its placeholder...`
  - `ui_render_viewport_w` (function, line 141) `int ui_render_viewport_w(void);`
  - `FREEDOM_UI_H` (macro, line 2) `#define FREEDOM_UI_H`
- Imported by: `gui/browser_ui.c`, `gui/freedom_view.c`, `gui/ui_render.c`, `src/freedom.c`, `src/ui_layout.c`, `tests/test_ui.c`

## include/url.h
- Doc: url_parts: Components of a validated absolute https URL, sliced for a JS location object.
- Layer: utility
- Language: h
- Symbols:
  - `url_parts` (struct, line 129)
  - `url_status` (enum, line 32)
  - `url_omni_kind` (enum, line 78)
  - `url_is_https` (function, line 42) `int url_is_https(const char *s);`
  - `url_has_scheme` (function, line 46) `int url_has_scheme(const char *s);`
  - `url_authority_len` (function, line 51) `size_t url_authority_len(const char *url);`
  - `URL_ERR_NOT_HTTPS` (function, line 109) `* URL_ERR_NOT_HTTPS (out untouched);`
  - `path` (function, line 115) `* absolute path ("file:///..."). NULL => 0. */ int url_is_file(const char *s);`
  - `url_file_path` (function, line 121) `const char *url_file_path(const char *s);`
  - `url` (function, line 126) `* Every field ALIASES the input url (not owned, valid while url is alive);`
  - `password` (function, line 152) `* username and password (owned, must be freed) into *username_out and * *password_out, and returns URL_OK. When...`
  - `FREEDOM_URL_H` (macro, line 2) `#define FREEDOM_URL_H`
  - `URL_MAX_LEN` (macro, line 30) `#define URL_MAX_LEN`
  - `URL_SEARCH_ENDPOINT` (macro, line 76) `#define URL_SEARCH_ENDPOINT`
- Imported by: `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_url.c`, `gui/browser_ui.c`, `include/form.h`, `include/js_dom.h`, `include/js_location.h`, `src/freedom.c`, `src/js_location.c`, `src/link_nav.c`, `src/prefetch.c`, `src/render_doc.c`, `src/secure_fetch.c`, `src/tab.c`, `src/url.c`, `src/webfont_load.c`, `tests/test_js_dom.c`, `tests/test_tab.c`, `tests/test_url.c`

## include/util.h
- Doc: — shared pure helpers (no I/O except where noted).
- Layer: utility
- Language: h
- Symbols:
  - `write_full` (function, line 15) `static inline int write_full(int fd, const void *buf, size_t n)`
  - `read_full` (function, line 26) `static inline int read_full(int fd, void *buf, size_t n)`
  - `mem_contains_ci` (function, line 43) `static inline int mem_contains_ci(const void *hay, size_t hlen, const char *needle)`
  - `utf8_seq_len` (function, line 57) `static inline size_t utf8_seq_len(unsigned char c)`
  - `fnv1a` (function, line 67) `static inline uint64_t fnv1a(const char *s, size_t n)`
  - `UTIL_H` (macro, line 5) `#define UTIL_H`
- Imported by: `src/browser.c`, `src/disk_store.c`, `src/dom.c`, `src/hostblock.c`, `src/html_parse.c`, `src/media_decoder.c`, `src/page_view.c`, `src/render_doc.c`, `src/renderer.c`, `src/tab.c`

## include/web_storage.h
- Doc: wst_new: web_storage — in-MEMORY localStorage for trusted hosts (owner decision: nothing...
- Layer: data_access
- Language: h
- Symbols:
  - `wst_db` (type_alias, line 21) `typedef struct wst_db wst_db;`
  - `wst_new` (function, line 25) `wst_db *wst_new(void);`
  - `wst_free` (function, line 28) `void wst_free(wst_db *db);`
  - `wst_encode` (function, line 33) `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len);`
  - `wst_decode_check` (function, line 37) `int wst_decode_check(const char *blob, size_t len);`
  - `wst_replace` (function, line 42) `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len);`
  - `full` (function, line 45) `* validating it in full (wst_decode_check). Returns 0, or -1 when invalid (fn is then * never called). The one...`
  - `wst_origin_bytes` (function, line 59) `size_t wst_origin_bytes(const wst_db *db, const char *origin);`
  - `FREEDOM_WEB_STORAGE_H` (macro, line 2) `#define FREEDOM_WEB_STORAGE_H`
  - `WST_MAX_ORIGINS` (macro, line 17) `#define WST_MAX_ORIGINS`
  - `WST_MAX_KEYS` (macro, line 18) `#define WST_MAX_KEYS`
  - `WST_QUOTA` (macro, line 19) `#define WST_QUOTA`
  - `WST_ORIGIN_MAX` (macro, line 20) `#define WST_ORIGIN_MAX`
- Imported by: `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_web_storage.c`, `gui/browser_ui.c`, `src/js_dom.c`, `src/js_trusted.c`, `src/tab.c`, `src/web_storage.c`, `tests/test_js_dom.c`, `tests/test_tab.c`, `tests/test_web_storage.c`

## include/webcaps.h
- Doc: wc_caps: Full capability table for one page.
- Layer: utility
- Language: h
- Symbols:
  - `wc_caps` (struct, line 38)
  - `wc_input` (struct, line 57)
  - `js` (type_alias, line 38) `typedef struct wc_caps { /* leak-free (global): granted by user toggle or allow.conf presentation-trust. */ bool js;`
  - `js_mode` (type_alias, line 57) `typedef struct wc_input { jsp_mode js_mode;`
  - `FREEDOM_WEBCAPS_H` (macro, line 2) `#define FREEDOM_WEBCAPS_H`
- Depends on: `include/js_policy.h`, `include/render_policy.h`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/webcaps.c`, `tests/test_webcaps.c`

## include/webfont.h
- Doc: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- Layer: utility
- Language: h
- Symbols:
  - `wf_ref` (struct, line 31)
  - `wf_list` (struct, line 46)
  - `family` (type_alias, line 30) `typedef struct wf_ref { char family[WF_FAMILY_MAX];`
  - `wf_name_hash` (function, line 69) `static inline unsigned wf_name_hash(const char *s, size_t n)`
  - `here` (function, line 38) `* set with the decoded bytes owned here (freed by wf_list_free);`
  - `wf_scan` (function, line 52) `int wf_scan(const char *css, size_t len, wf_list *out);`
  - `wf_list_free` (function, line 53) `void wf_list_free(wf_list *l);`
  - `boundaries` (function, line 57) `* boundaries (scan_inline accumulation, loader collection). */ void wf_ref_move(wf_ref *dst, wf_ref *src);`
  - `wf_supported_format` (function, line 60) `int wf_supported_format(const char *fmt);`
  - `FREEDOM_WEBFONT_H` (macro, line 2) `#define FREEDOM_WEBFONT_H`
  - `WF_FAMILY_MAX` (macro, line 20) `#define WF_FAMILY_MAX`
  - `WF_URL_MAX` (macro, line 21) `#define WF_URL_MAX`
  - `WF_FORMAT_MAX` (macro, line 22) `#define WF_FORMAT_MAX`
  - `WF_MAX_REFS` (macro, line 23) `#define WF_MAX_REFS`
  - `WF_MAX_FACE_BYTES` (macro, line 24) `#define WF_MAX_FACE_BYTES`
  - `WF_MAX_TOTAL_BYTES` (macro, line 25) `#define WF_MAX_TOTAL_BYTES`
  - `WF_DATA_URL_MAX` (macro, line 29) `#define WF_DATA_URL_MAX`
- Imported by: `fuzz/fuzz_webfont.c`, `gui/browser_ui.c`, `src/css.c`, `src/freedom.c`, `src/text_shape.c`, `src/webfont.c`, `src/webfont_load.c`, `tests/test_css.c`, `tests/test_page_view.c`, `tests/test_text_shape.c`, `tests/test_webfont.c`, `tests/test_webfont_load.c`

## include/webfont_load.h
- Doc: wf_sheet: One collected stylesheet: text plus the URL it was fetched from (the * resolution base...
- Layer: utility
- Language: h
- Symbols:
  - `wf_sheet` (struct, line 24)
  - `free` (function, line 31) `* free()), *out_status the HTTP status. Nonzero on refusal/error (fail-closed: * the face is skipped, never the...`
  - `skipped` (function, line 47) `* URLs are skipped (no base). Returns faces registered (>= 0) otherwise. */ int wf_load_document(wf_fetch_fn fetch...`
  - `FREEDOM_WEBFONT_LOAD_H` (macro, line 2) `#define FREEDOM_WEBFONT_LOAD_H`
  - `WF_LOAD_TRIES_PER_KEY` (macro, line 52) `#define WF_LOAD_TRIES_PER_KEY`
  - `WF_LOAD_MAX_KEYS` (macro, line 53) `#define WF_LOAD_MAX_KEYS`
  - `WF_LOAD_MAX_FETCHES` (macro, line 54) `#define WF_LOAD_MAX_FETCHES`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/webfont_load.c`, `tests/test_webfont_load.c`

## include/wl_display.h
- Doc: wd_pick: Choose the lowest-numbered "wayland-N" (N = digits only) from names[0..n).
- Layer: utility
- Language: h
- Symbols:
  - `pure` (function, line 3) `* wd_pick is pure (no I/O);`
  - `wd_pick` (function, line 16) `int wd_pick(const char *const *names, size_t n, char *out, size_t cap);`
  - `wd_resolve_env` (function, line 20) `int wd_resolve_env(void);`
  - `FREEDOM_WL_DISPLAY_H` (macro, line 6) `#define FREEDOM_WL_DISPLAY_H`
  - `WD_OK` (macro, line 10) `#define WD_OK`
  - `WD_NONE` (macro, line 11) `#define WD_NONE`
- Imported by: `src/freedom.c`, `src/wl_display.c`, `tests/test_wl_display.c`


Next: [KB_include_p5.md](KB_include_p5.md)
