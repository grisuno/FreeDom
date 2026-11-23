# Symbols (page 6 of 19)
Previous: [SYMBOLS_p5.md](SYMBOLS_p5.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `RD_MAX_INPUT` | macro | `include/renderer.h:37` | `#define RD_MAX_INPUT` |
| `rd_result` | struct | `include/renderer.h:29` | `` |
| `rd_result_free` | function | `include/renderer.h:46` | `void rd_result_free(rd_result *out);` |
| `rd_status` | enum | `include/renderer.h:20` | `` |
| `status` | type_alias | `include/renderer.h:28` | `typedef struct rd_result { rd_status status;` |
| `FREEDOM_REQUEST_POLICY_H` | macro | `include/request_policy.h:2` | `#define FREEDOM_REQUEST_POLICY_H` |
| `RP_HDR_MAX_BYTES` | macro | `include/request_policy.h:44` | `#define RP_HDR_MAX_BYTES` |
| `RP_HDR_MAX_COUNT` | macro | `include/request_policy.h:43` | `#define RP_HDR_MAX_COUNT` |
| `RP_HDR_NAME_MAX` | macro | `include/request_policy.h:45` | `#define RP_HDR_NAME_MAX` |
| `RP_HDR_VALUE_MAX` | macro | `include/request_policy.h:46` | `#define RP_HDR_VALUE_MAX` |
| `rp_decision` | enum | `include/request_policy.h:21` | `` |
| `rp_headers_have` | function | `include/request_policy.h:61` | `static inline int rp_headers_have(const char *lines, const char *name)` |
| `rp_host_of` | function | `include/request_policy.h:30` | `int rp_host_of(const char *url, char *out, size_t out_size);` |
| `rp_same_site` | function | `include/request_policy.h:37` | `int rp_same_site(const char *top_level_url, const char *request_url);` |
| `rp_sanitize_request_headers` | function | `include/request_policy.h:57` | `int rp_sanitize_request_headers(const char *raw, char *out, size_t cap);` |
| `rp_site_of` | function | `include/request_policy.h:34` | `int rp_site_of(const char *host, char *out, size_t out_size);` |
| `EXCLUDED` | function | `include/secure_fetch.h:248` | `* cookies are EXCLUDED (network-only, never exposed to JS) and expired cookies skipped. * Only for a TRUSTED host...` |
| `FREEDOM_SECURE_FETCH_H` | macro | `include/secure_fetch.h:2` | `#define FREEDOM_SECURE_FETCH_H` |
| `SF_CONNECT_TIMEOUT_MS` | macro | `include/secure_fetch.h:231` | `#define SF_CONNECT_TIMEOUT_MS` |
| `SF_DEFAULT_KEX_GROUPS` | macro | `include/secure_fetch.h:181` | `#define SF_DEFAULT_KEX_GROUPS` |
| `SF_DEFAULT_MAX_BODY` | macro | `include/secure_fetch.h:207` | `#define SF_DEFAULT_MAX_BODY` |
| `SF_DEFAULT_MAX_REDIRECTS` | macro | `include/secure_fetch.h:233` | `#define SF_DEFAULT_MAX_REDIRECTS` |
| `SF_DEFAULT_TIMEOUT_MS` | macro | `include/secure_fetch.h:208` | `#define SF_DEFAULT_TIMEOUT_MS` |
| `SF_DEFAULT_USER_AGENT` | macro | `include/secure_fetch.h:206` | `#define SF_DEFAULT_USER_AGENT` |
| `SF_IMPERSONATE_KEX_GROUPS` | macro | `include/secure_fetch.h:190` | `#define SF_IMPERSONATE_KEX_GROUPS` |
| `SF_IMPERSONATE_TLS12_CIPHERS` | macro | `include/secure_fetch.h:195` | `#define SF_IMPERSONATE_TLS12_CIPHERS` |
| `SF_IMPERSONATE_TLS13_CIPHERS` | macro | `include/secure_fetch.h:191` | `#define SF_IMPERSONATE_TLS13_CIPHERS` |
| `SF_MAX_URL` | macro | `include/secure_fetch.h:234` | `#define SF_MAX_URL` |
| `SF_META_MAX` | macro | `include/secure_fetch.h:83` | `#define SF_META_MAX` |
| `SF_RESPONSE_HEADERS_MAX` | macro | `include/secure_fetch.h:84` | `#define SF_RESPONSE_HEADERS_MAX` |
| `SF_SUBRESOURCE_TIMEOUT_MS` | macro | `include/secure_fetch.h:232` | `#define SF_SUBRESOURCE_TIMEOUT_MS` |
| `SF_WS_MAX_MESSAGE` | macro | `include/secure_fetch.h:339` | `#define SF_WS_MAX_MESSAGE` |
| `bits` | function | `include/secure_fetch.h:357` | `* *flags receives CURLWS_* bits (text/binary/close/cont);` |
| `connection` | function | `include/secure_fetch.h:371` | `* on each connection (Zero Trust). Each target is re-validated and a downgrade * to http:// is refused. Exceeding...` |
| `exhausted` | function | `include/secure_fetch.h:402` | `* is exhausted (*next untouched). `allowlisted` enables the sovereignty rung. */ int sf_fallback_policy(sf_status...` |
| `policy` | type_alias | `include/secure_fetch.h:85` | `typedef struct sf_config { sf_policy policy;` |
| `rp_sanitize_request_headers` | function | `include/secure_fetch.h:115` | `* rp_sanitize_request_headers ("Name: value\n" lines);` |
| `sf_accept_language_or_default` | function | `include/secure_fetch.h:273` | `const char *sf_accept_language_or_default(const char *lang);` |
| `sf_chain_info` | struct | `include/secure_fetch.h:67` | `` |
| `sf_config` | struct | `include/secure_fetch.h:86` | `` |
| `sf_cookie_line_matches` | function | `include/secure_fetch.h:260` | `int sf_cookie_line_matches(const char *line, const char *host, const char *path, long now, char *out, size_t outsz);` |
| `sf_cookie_put` | function | `include/secure_fetch.h:255` | `void sf_cookie_put(const char *url, const char *namevalue);` |
| `sf_get` | function | `include/secure_fetch.h:380` | `* sf_get (Zero Trust): an insecure POST is not representable. Does not follow * redirects (the caller inspects...` |
| `sf_global_init` | function | `include/secure_fetch.h:242` | `void sf_global_init(void);` |
| `sf_header_value` | function | `include/secure_fetch.h:320` | `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz);` |
| `sf_impersonate_kex_groups` | function | `include/secure_fetch.h:277` | `const char *sf_impersonate_kex_groups(void);` |
| `sf_impersonate_tls13_ciphers` | function | `include/secure_fetch.h:278` | `const char *sf_impersonate_tls13_ciphers(void);` |
| `sf_is_redirect_code` | function | `include/secure_fetch.h:309` | `int sf_is_redirect_code(long http_code);` |
| `sf_policy` | enum | `include/secure_fetch.h:47` | `` |
| `sf_proxy_type` | enum | `include/secure_fetch.h:76` | `` |
| `sf_rcache_clear` | function | `include/secure_fetch.h:417` | `void sf_rcache_clear(void);` |
| `sf_rcache_get` | function | `include/secure_fetch.h:416` | `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap);` |
| `sf_rcache_put` | function | `include/secure_fetch.h:415` | `int sf_rcache_put(const char *from, const char *to, time_t now);` |
| `sf_rcache_set_backing` | function | `include/secure_fetch.h:426` | `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx);` |
| `sf_response` | struct | `include/secure_fetch.h:145` | `` |
| `sf_response_free` | function | `include/secure_fetch.h:391` | `void sf_response_free(sf_response *resp);` |
| `sf_status` | enum | `include/secure_fetch.h:24` | `` |
| `sf_user_agent_or_default` | function | `include/secure_fetch.h:269` | `const char *sf_user_agent_or_default(const char *ua);` |
| `sf_ws` | type_alias | `include/secure_fetch.h:340` | `typedef struct sf_ws sf_ws;` |
| `sf_ws_close` | function | `include/secure_fetch.h:367` | `void sf_ws_close(sf_ws *ws);` |
| `sf_ws_fd` | function | `include/secure_fetch.h:364` | `int sf_ws_fd(const sf_ws *ws);` |
| `skipped` | function | `include/secure_fetch.h:298` | `* skipped (a classical key exchange is accepted);` |
| `status` | type_alias | `include/secure_fetch.h:144` | `typedef struct sf_response { sf_status status;` |
| `validators` | function | `include/secure_fetch.h:18` | `* The security logic lives in pure validators (no I/O);` |
| `FREEDOM_SHA2_H` | macro | `include/sha2.h:2` | `#define FREEDOM_SHA2_H` |
| `SHA_MAX_DIGEST` | macro | `include/sha2.h:18` | `#define SHA_MAX_DIGEST` |
| `sha_alg` | enum | `include/sha2.h:16` | `` |
| `sha_alg_from_name` | function | `include/sha2.h:24` | `int sha_alg_from_name(const char *name, sha_alg *out);` |
| `sha_digest` | function | `include/sha2.h:28` | `int sha_digest(sha_alg alg, const void *data, size_t len, uint8_t *out);` |
| `sha_digest_len` | function | `include/sha2.h:21` | `size_t sha_digest_len(sha_alg alg);` |
| `FREEDOM_SHEET_CACHE_H` | macro | `include/sheet_cache.h:14` | `#define FREEDOM_SHEET_CACHE_H` |
| `hits` | type_alias | `include/sheet_cache.h:42` | `typedef struct shc_stats { unsigned long hits;` |
| `shc_acquire` | function | `include/sheet_cache.h:60` | `shc_sheet *shc_acquire(shc_cache *cache, const shc_key *key);` |
| `shc_cache` | type_alias | `include/sheet_cache.h:26` | `typedef struct shc_cache shc_cache;` |
| `shc_css` | function | `include/sheet_cache.h:64` | `const css_sheet *shc_css(const shc_sheet *s);` |
| `shc_free` | function | `include/sheet_cache.h:55` | `void shc_free(shc_cache *c);` |
| `shc_key` | struct | `include/sheet_cache.h:36` | `` |
| `shc_new` | function | `include/sheet_cache.h:52` | `shc_cache *shc_new(size_t max_text_bytes);` |
| `shc_release` | function | `include/sheet_cache.h:67` | `void shc_release(shc_sheet *s);` |
| `shc_sheet` | type_alias | `include/sheet_cache.h:28` | `typedef struct shc_sheet shc_sheet;` |
| `shc_stats` | struct | `include/sheet_cache.h:43` | `` |
| `shc_stats_get` | function | `include/sheet_cache.h:70` | `void shc_stats_get(const shc_cache *c, shc_stats *out);` |
| `FREEDOM_SHM_SLOTS_H` | macro | `include/shm_slots.h:2` | `#define FREEDOM_SHM_SLOTS_H` |
| `SS_COUNT` | macro | `include/shm_slots.h:17` | `#define SS_COUNT` |
| `busy` | type_alias | `include/shm_slots.h:18` | `typedef struct ss_state { int busy[SS_COUNT];` |
| `ss_committed` | function | `include/shm_slots.h:41` | `static inline void ss_committed(ss_state *s, int i)` |
| `ss_init` | function | `include/shm_slots.h:24` | `static inline void ss_init(ss_state *s)` |
| `ss_released` | function | `include/shm_slots.h:49` | `static inline int ss_released(ss_state *s, int i)` |
| `ss_state` | struct | `include/shm_slots.h:19` | `` |
| `FREEDOM_SMOOTH_SCROLL_H` | macro | `include/smooth_scroll.h:2` | `#define FREEDOM_SMOOTH_SCROLL_H` |
| `from` | type_alias | `include/smooth_scroll.h:17` | `typedef struct sms_state { double from;` |
| `sms_active` | function | `include/smooth_scroll.h:32` | `int sms_active(const sms_state *s);` |
| `sms_goal` | function | `include/smooth_scroll.h:31` | `double sms_goal(const sms_state *s);` |
| `sms_init` | function | `include/smooth_scroll.h:27` | `void sms_init(sms_state *s, double pos);` |
| `sms_jump` | function | `include/smooth_scroll.h:28` | `void sms_jump(sms_state *s, double pos);` |
| `sms_retarget` | function | `include/smooth_scroll.h:29` | `void sms_retarget(sms_state *s, double target, double now_ms, double dur_ms);` |
| `sms_sample` | function | `include/smooth_scroll.h:30` | `double sms_sample(sms_state *s, double now_ms);` |
| `sms_state` | struct | `include/smooth_scroll.h:18` | `` |
| `SQB_MAX_JOBS` | macro | `include/subreq_batch.h:14` | `#define SQB_MAX_JOBS` |
| `SUBREQ_BATCH_H` | macro | `include/subreq_batch.h:10` | `#define SUBREQ_BATCH_H` |
| `ok` | type_alias | `include/subreq_batch.h:23` | `typedef struct sqb_res { int ok;` |
| `sqb` | type_alias | `include/subreq_batch.h:34` | `typedef struct sqb sqb;` |
| `sqb_abandon` | function | `include/subreq_batch.h:43` | `void sqb_abandon(sqb *b);` |
| `sqb_count` | function | `include/subreq_batch.h:48` | `size_t sqb_count(const sqb *b);` |
| `sqb_free` | function | `include/subreq_batch.h:64` | `void sqb_free(sqb *b);` |
| `sqb_new` | function | `include/subreq_batch.h:37` | `sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx);` |
| `sqb_new_owned` | function | `include/subreq_batch.h:40` | `sqb *sqb_new_owned(int max_threads, sqb_run_fn run, void *ctx, void (*free_ctx)(void *));` |
| `sqb_remove` | function | `include/subreq_batch.h:59` | `void sqb_remove(sqb *b, const size_t *idx, size_t k);` |
| `sqb_req` | struct | `include/subreq_batch.h:16` | `` |
| `sqb_res` | struct | `include/subreq_batch.h:23` | `` |
| `sqb_reset` | function | `include/subreq_batch.h:61` | `void sqb_reset(sqb *b);` |
| `sqb_result` | function | `include/subreq_batch.h:52` | `const sqb_res *sqb_result(const sqb *b, size_t i);` |
| `sqb_submit` | function | `include/subreq_batch.h:47` | `int sqb_submit(sqb *b, int refused, const sqb_req *req);` |
| `sqb_wait_all` | function | `include/subreq_batch.h:50` | `void sqb_wait_all(sqb *b);` |
| `sqb_wait_ready` | function | `include/subreq_batch.h:56` | `size_t sqb_wait_ready(sqb *b, long wait_ms, size_t *idx, size_t cap);` |
| `FREEDOM_SVG_PAINT_H` | macro | `include/svg_paint.h:2` | `#define FREEDOM_SVG_PAINT_H` |
| `svp_draw` | function | `include/svg_paint.h:31` | `void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, double h, int current_rgb);` |
| `way` | function | `include/svg_paint.h:35` | `* worker rasterizes SVG images this way (spec/svg_raster.md section 3): drawing text * would open fontconfig, i.e....` |
| `FREEDOM_SVG_RASTER_H` | macro | `include/svg_raster.h:2` | `#define FREEDOM_SVG_RASTER_H` |
| `SR_MAX_DIM` | macro | `include/svg_raster.h:24` | `#define SR_MAX_DIM` |
| `SR_MIN_RASTER` | macro | `include/svg_raster.h:25` | `#define SR_MIN_RASTER` |
| `SR_SNIFF_MAX` | macro | `include/svg_raster.h:23` | `#define SR_SNIFF_MAX` |
| `sr_sniff` | function | `include/svg_raster.h:29` | `int sr_sniff(const uint8_t *bytes, size_t len);` |
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
| `TAB_MAX_INPUT` | macro | `include/tab.h:160` | `#define TAB_MAX_INPUT` |
| `bytes` | function | `include/tab.h:226` | `* so the parent can retain the bytes (spec/webfont.md b3b feeds them to the * @font-face loader as extern sheets)....` |
| `decode` | function | `include/tab.h:448` | `* could not decode (caller shows the placeholder), which is not a transport error. * TAB_ERR_* is reserved for...` |
| `exclusively` | function | `include/tab.h:298` | `* exclusively (tab_subreq_permitted). Default 0: zero fetches, Privacy by Default. */ void tab_set_css_allowed(tab...` |
| `free_ctx` | function | `include/tab.h:242` | `* free_ctx(ctx) (may be NULL) runs once the tab is closed AND its last abandoned request ended, * so the fetcher may...` |
| `granted` | function | `include/tab.h:404` | `* granted (allow.conf AND js.conf);` |
| `jar` | function | `include/tab.h:283` | `* the trusted parent read from its ephemeral network jar (sf_cookie_header_for). Only * meaningful for a trusted...` |
| `kind` | type_alias | `include/tab.h:71` | `typedef struct tab_ws_op { int kind;` |
| `kind` | type_alias | `include/tab.h:423` | `typedef struct tab_anchor { int kind;` |
| `load` | function | `include/tab.h:310` | `* trusted load (net granted). */ void tab_set_frame_id(tab *t, int id);` |
| `none` | function | `include/tab.h:254` | `* worker sent carries none (tab_page.unchanged) -- on a live page that is almost every tick. * The caller must then...` |
| `origin` | function | `include/tab.h:290` | `* page origin (web_storage snapshot, copied). Used only when the load is trusted * (net granted);` |
| `out_status` | function | `include/tab.h:201` | `* On success return 0 and set *out_status (HTTP status), *out_body / *out_body_len * (malloc'd response bytes, tab...` |
| `popstate` | function | `include/tab.h:411` | `* popstate (+ hashchange) and re-derives the view like a click. */ tab_status tab_popstate(tab *t, int index...` |
| `preorder` | function | `include/tab.h:416` | `* preorder (out->nsub handles) followed by the elements after it, at most * ANC_MAX_HANDLES -- live DOM handles, the...` |
| `replace` | type_alias | `include/tab.h:54` | `typedef struct tab_hist_op { int replace;` |
| `returned` | function | `include/tab.h:405` | `* returned (the page keeps its zeros). The worker re-checks the same condition. * g must be finished (jg_finish). */...` |
| `string` | function | `include/tab.h:355` | `* event_type is a JS event type string (e.g. "keydown", "input", "change"). * key is the keyboard key value (may be...` |
| `tab` | type_alias | `include/tab.h:46` | `typedef struct tab tab;` |
| `tab_alive` | function | `include/tab.h:461` | `int tab_alive(const tab *t);` |
| `tab_anchor` | struct | `include/tab.h:423` | `` |
| `tab_anchor_free` | function | `include/tab.h:430` | `void tab_anchor_free(tab_anchor *a);` |
| `tab_async_busy` | function | `include/tab.h:276` | `int tab_async_busy(const tab *t);` |
| `tab_async_fd` | function | `include/tab.h:270` | `* the completion is signalled on tab_async_fd (readable). The pipe to the worker is a single * channel, so EVERY...` |
| `tab_child_pid` | function | `include/tab.h:464` | `pid_t tab_child_pid(const tab *t);` |
| `tab_close` | function | `include/tab.h:467` | `void tab_close(tab *t);` |
| `tab_eval_result` | struct | `include/tab.h:138` | `` |
| `tab_eval_result_free` | function | `include/tab.h:471` | `void tab_eval_result_free(tab_eval_result *r);` |
| `tab_hist_op` | struct | `include/tab.h:54` | `` |
| `tab_image` | struct | `include/tab.h:151` | `` |
| `tab_image_free` | function | `include/tab.h:472` | `void tab_image_free(tab_image *img);` |
| `tab_inflight_request_headers` | function | `include/tab.h:217` | `const char *tab_inflight_request_headers(void);` |
| `tab_last_subreq_stats` | function | `include/tab.h:322` | `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us);` |
| `tab_open` | function | `include/tab.h:168` | `* and reaches tab_open (the app and the test harness) must call this first. */ void tab_worker_dispatch(int argc...` |
| `tab_page` | struct | `include/tab.h:79` | `` |
| `tab_page_free` | function | `include/tab.h:470` | `void tab_page_free(tab_page *p);` |
| `tab_page_keep_view` | function | `include/tab.h:261` | `void tab_page_keep_view(tab_page *prev, tab_page *next);` |
| `tab_parse_worker_args` | function | `include/tab.h:175` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd);` |
| `tab_prewarm` | function | `include/tab.h:184` | `void tab_prewarm(void);` |
| `tab_prewarmed` | function | `include/tab.h:187` | `int tab_prewarmed(void);` |
| `tab_prewarmed_pid` | function | `include/tab.h:190` | `int tab_prewarmed_pid(void);` |
| `tab_report_response_headers` | function | `include/tab.h:222` | `void tab_report_response_headers(const char *lines);` |
| `tab_set_cookies` | function | `include/tab.h:287` | `void tab_set_cookies(tab *t, const char *cookies);` |
| `tab_set_css_sink` | function | `include/tab.h:235` | `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx);` |
| `tab_set_fetcher` | function | `include/tab.h:212` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx);` |
| `tab_set_identity` | function | `include/tab.h:316` | `void tab_set_identity(tab *t, const char *serialized);` |
| `tab_set_net_allowed` | function | `include/tab.h:250` | `void tab_set_net_allowed(tab *t, int allowed);` |
| `tab_set_op_net_budget_ms` | function | `include/tab.h:265` | `void tab_set_op_net_budget_ms(tab *t, int ms);` |
| `tab_set_storage` | function | `include/tab.h:292` | `void tab_set_storage(tab *t, const char *blob, size_t len);` |
| `tab_set_viewport_w` | function | `include/tab.h:306` | `void tab_set_viewport_w(tab *t, int px);` |
| `tab_shutdown_spare` | function | `include/tab.h:193` | `void tab_shutdown_spare(void);` |
| `tab_status` | enum | `include/tab.h:31` | `` |
| `tab_subreq_permitted` | function | `include/tab.h:327` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method);` |
| `tab_worker_dispatch` | function | `include/tab.h:164` | `* Call tab_worker_dispatch(argc, argv) as the FIRST thing in main(): if argv is the * internal "--tab-worker <rfd>...` |
| `tab_ws_event_kind` | enum | `include/tab.h:67` | `` |
| `tab_ws_kind` | enum | `include/tab.h:61` | `` |
| `tab_ws_op` | struct | `include/tab.h:72` | `` |
| `view` | function | `include/tab.h:335` | `* <noscript> handling in the built view (off => fallback shown, on => suppressed) * and is where allowlisted...` |
| `width` | type_alias | `include/tab.h:151` | `typedef struct tab_image { uint32_t width;` |
| `FREEDOM_TABLE_LAYOUT_H` | macro | `include/table_layout.h:11` | `#define FREEDOM_TABLE_LAYOUT_H` |
| `TL_MAX_COLS` | macro | `include/table_layout.h:20` | `#define TL_MAX_COLS` |
| `TL_PER_MILLE` | macro | `include/table_layout.h:26` | `#define TL_PER_MILLE` |
| `TL_WIDTH_MAX` | macro | `include/table_layout.h:23` | `#define TL_WIDTH_MAX` |
| `col` | type_alias | `include/table_layout.h:27` | `typedef struct tl_cell { int col;` |
| `px` | function | `include/table_layout.h:41` | `* px (< 0 = auto: the table is as wide as its content, capped at avail). gap is the space * between adjacent...` |
| `tl_cell` | struct | `include/table_layout.h:28` | `` |
| `tl_intrinsic` | function | `include/table_layout.h:53` | `void tl_intrinsic(const tl_cell *cells, size_t n, size_t ncols, double gap, double *min_total, double *max_total);` |
| `FREEDOM_TEXT_CASE_H` | macro | `include/text_case.h:2` | `#define FREEDOM_TEXT_CASE_H` |
| `TC_SMALLCAPS_SCALE` | macro | `include/text_case.h:15` | `#define TC_SMALLCAPS_SCALE` |
| `cp` | function | `include/text_case.h:19` | `* cp (identity otherwise), so a transformed text keeps its length. */ uint32_t tc_upper(uint32_t cp);` |
| `tc_is_lower` | function | `include/text_case.h:24` | `int tc_is_lower(uint32_t cp);` |
| `tc_lower` | function | `include/text_case.h:21` | `uint32_t tc_lower(uint32_t cp);` |
| `tc_run` | struct | `include/text_case.h:33` | `` |
| `tc_smallcaps_runs` | function | `include/text_case.h:41` | `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap);` |
| `tc_transform` | function | `include/text_case.h:29` | `size_t tc_transform(const char *s, size_t n, int transform, int word_start, char *out, size_t cap);` |
| `FREEDOM_TEXT_SHAPE_H` | macro | `include/text_shape.h:19` | `#define FREEDOM_TEXT_SHAPE_H` |
| `TSH_FAMILY_MAX` | macro | `include/text_shape.h:48` | `#define TSH_FAMILY_MAX` |
| `TSH_LOCAL_FAMILIES` | macro | `include/text_shape.h:47` | `#define TSH_LOCAL_FAMILIES` |
| `TSH_LOCAL_LISTS` | macro | `include/text_shape.h:46` | `#define TSH_LOCAL_LISTS` |
| `TSH_MAX_GLYPHS` | macro | `include/text_shape.h:77` | `#define TSH_MAX_GLYPHS` |
| `TSH_MAX_TEXT` | macro | `include/text_shape.h:78` | `#define TSH_MAX_TEXT` |
| `content` | function | `include/text_shape.h:11` | `* TEXT is hostile remote content (sanitised UTF-8) and is fuzzed (make fuzz-tsh);` |
| `end` | type_alias | `include/text_shape.h:138` | `typedef struct tsh_run { size_t start, end;` |
| `family` | type_alias | `include/text_shape.h:33` | `typedef struct tsh_font { int family;` |
| `origin` | function | `include/text_shape.h:92` | `* glyphs are written with positions relative to origin (0,0) on the baseline, * and *out_adv holds the total pen...` |
| `own` | function | `include/text_shape.h:142` | `* face of their own (controls, combining marks, variation selectors, ZWJ/ZWNJ) * stay in the run before them....` |
| `tsh_face` | function | `include/text_shape.h:133` | `cairo_font_face_t *tsh_face(const tsh_font *f);` |
| `tsh_face_generation` | function | `include/text_shape.h:122` | `unsigned tsh_face_generation(void);` |
| `tsh_family_is_generic` | function | `include/text_shape.h:52` | `int tsh_family_is_generic(const char *name);` |
| `tsh_font` | struct | `include/text_shape.h:33` | `` |
| `tsh_local_handle` | function | `include/text_shape.h:75` | `int tsh_local_handle(const char *list);` |
| `tsh_measure` | function | `include/text_shape.h:101` | `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len);` |
| `tsh_pick_family` | function | `include/text_shape.h:68` | `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong, size_t n, int...` |
| `tsh_ready` | function | `include/text_shape.h:89` | `int tsh_ready(void);` |
| `tsh_run` | struct | `include/text_shape.h:138` | `` |
| `tsh_shutdown` | function | `include/text_shape.h:149` | `void tsh_shutdown(void);` |
| `tsh_status` | enum | `include/text_shape.h:80` | `` |
| `tsh_webfont_clear` | function | `include/text_shape.h:126` | `void tsh_webfont_clear(void);` |
| `tsh_webfont_register` | function | `include/text_shape.h:114` | `int tsh_webfont_register(const char *name, const unsigned char *bytes, size_t nbytes, int bold, int italic);` |
| `wins` | function | `include/text_shape.h:58` | `* the first name the resolver accepts wins (returns 1, family in out). Pure: the * resolver is injected (fontconfig...` |
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
| `available` | function | `include/ui.h:91` | `* cheapest artifact to inspect a render where no display is available (CI, an AI * agent): export, then read the PNG...` |
| `disk` | function | `include/ui.h:118` | `* images are read from disk (confined to the document directory by render_doc). * top_url is the page origin (https...` |
| `fh_host` | struct | `include/ui.h:130` | `` |
| `images` | function | `include/ui.h:120` | `* fetcher loads no images (placeholders, as before). Any image that fails falls back * to its placeholder...` |
| `jg_table` | struct | `include/ui.h:100` | `` |
| `offset` | type_alias | `include/ui.h:30` | `typedef struct ui_line { size_t offset;` |
| `out` | function | `include/ui.h:103` | `* ui_render_png does and fills *out (jg_init'ed by the caller) with one rect per * element in document coordinates...` |
| `placeholders` | function | `include/ui.h:113` | `* above always draw image placeholders (no worker to decode hostile bytes);` |
| `rd_doc` | struct | `include/ui.h:74` | `` |
| `shortcut` | function | `include/ui.h:71` | `* from a keyboard shortcut (Ctrl+Shift+E only relaxes a weak-but-valid certificate). */ void...` |
| `space` | function | `include/ui.h:44` | `* Breaks at the last fitting space (the break space is consumed), hard-breaks * words longer than max_cols, and...` |
| `tab` | struct | `include/ui.h:110` | `` |
| `ui_clamp_scroll` | function | `include/ui.h:55` | `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines);` |
| `ui_layout` | struct | `include/ui.h:35` | `` |
| `ui_layout_free` | function | `include/ui.h:52` | `void ui_layout_free(ui_layout *lay);` |
| `ui_line` | struct | `include/ui.h:30` | `` |
| `ui_persisted_prefs` | function | `include/ui.h:161` | `int ui_persisted_prefs(prefs_state *out);` |
| `ui_render_viewport_w` | function | `include/ui.h:156` | `int ui_render_viewport_w(void);` |
| `ui_status` | enum | `include/ui.h:20` | `` |
| `FREEDOM_URL_H` | macro | `include/url.h:2` | `#define FREEDOM_URL_H` |
| `URL_ERR_NOT_HTTPS` | function | `include/url.h:109` | `* URL_ERR_NOT_HTTPS (out untouched);` |
| `URL_MAX_LEN` | macro | `include/url.h:30` | `#define URL_MAX_LEN` |
| `URL_SEARCH_ENDPOINT` | macro | `include/url.h:76` | `#define URL_SEARCH_ENDPOINT` |
| `password` | function | `include/url.h:159` | `* username and password (owned, must be freed) into *username_out and * *password_out, and returns URL_OK. When...` |
| `path` | function | `include/url.h:115` | `* absolute path ("file:///..."). NULL => 0. */ int url_is_file(const char *s);` |
| `url` | function | `include/url.h:126` | `* Every field ALIASES the input url (not owned, valid while url is alive);` |
| `url_authority_len` | function | `include/url.h:51` | `size_t url_authority_len(const char *url);` |
| `url_file_path` | function | `include/url.h:121` | `const char *url_file_path(const char *s);` |
| `url_has_scheme` | function | `include/url.h:46` | `int url_has_scheme(const char *s);` |
| `url_is_https` | function | `include/url.h:42` | `int url_is_https(const char *s);` |
| `url_omni_kind` | enum | `include/url.h:78` | `` |
| `url_parts` | struct | `include/url.h:129` | `` |
| `url_split` | function | `include/url.h:153` | `* it for a network or storage decision: those take url_split (https-only). */ url_status url_split_location(const...` |
| `url_status` | enum | `include/url.h:32` | `` |
| `UTIL_H` | macro | `include/util.h:5` | `#define UTIL_H` |
| `fnv1a` | function | `include/util.h:67` | `static inline uint64_t fnv1a(const char *s, size_t n)` |
| `mem_contains_ci` | function | `include/util.h:43` | `static inline int mem_contains_ci(const void *hay, size_t hlen, const char *needle)` |
| `read_full` | function | `include/util.h:26` | `static inline int read_full(int fd, void *buf, size_t n)` |
| `utf8_seq_len` | function | `include/util.h:57` | `static inline size_t utf8_seq_len(unsigned char c)` |
| `write_full` | function | `include/util.h:15` | `static inline int write_full(int fd, const void *buf, size_t n)` |
| `FREEDOM_VIDEO_CONTROLS_H` | macro | `include/video_controls.h:2` | `#define FREEDOM_VIDEO_CONTROLS_H` |
| `VCL_BAR_H` | macro | `include/video_controls.h:18` | `#define VCL_BAR_H` |
| `VCL_MAX_SEGMENT_S` | macro | `include/video_controls.h:24` | `#define VCL_MAX_SEGMENT_S` |
| `VCL_MIN_H` | macro | `include/video_controls.h:20` | `#define VCL_MIN_H` |
| `VCL_MIN_W` | macro | `include/video_controls.h:19` | `#define VCL_MIN_W` |
| `VCL_PAD` | macro | `include/video_controls.h:21` | `#define VCL_PAD` |
| `VCL_SEEK_STEP_S` | macro | `include/video_controls.h:25` | `#define VCL_SEEK_STEP_S` |
| `VCL_TEXT_W` | macro | `include/video_controls.h:22` | `#define VCL_TEXT_W` |
| `VCL_TRACK_H` | macro | `include/video_controls.h:23` | `#define VCL_TRACK_H` |
| `bar` | type_alias | `include/video_controls.h:28` | `typedef struct vcl_geom { vcl_rect bar;` |
| `frac` | function | `include/video_controls.h:50` | `* *frac (may be NULL) receives the track position for VCL_HIT_SEEK, else 0. */ vcl_hit_kind vcl_hit(const vcl_geom...` |
| `h` | type_alias | `include/video_controls.h:26` | `typedef struct vcl_rect { double x, y, w, h;` |
| `start` | function | `include/video_controls.h:61` | `* in *start (may be NULL). NULL/empty playlist => 0 and *start = 0. */ size_t vcl_segment_at(const hls_playlist *pl...` |
| `vcl_clamp_frac` | function | `include/video_controls.h:71` | `double vcl_clamp_frac(double f);` |
| `vcl_format_time` | function | `include/video_controls.h:75` | `size_t vcl_format_time(double seconds, char *buf, size_t cap);` |
| `vcl_geom` | struct | `include/video_controls.h:29` | `` |
| `vcl_hit_kind` | enum | `include/video_controls.h:38` | `` |
| `vcl_layout` | function | `include/video_controls.h:47` | `int vcl_layout(double x, double y, double w, double h, vcl_geom *g);` |
| `vcl_position` | function | `include/video_controls.h:68` | `double vcl_position(double base_s, int64_t pts0_us, int64_t pts_us, double total);` |
| `vcl_rect` | struct | `include/video_controls.h:27` | `` |
| `vcl_seg_duration` | function | `include/video_controls.h:55` | `double vcl_seg_duration(double d);` |
| `vcl_segment_start` | function | `include/video_controls.h:65` | `double vcl_segment_start(const hls_playlist *pl, size_t idx);` |
| `vcl_total` | function | `include/video_controls.h:58` | `double vcl_total(const hls_playlist *pl);` |
| `FREEDOM_VIDEO_PICK_H` | macro | `include/video_pick.h:2` | `#define FREEDOM_VIDEO_PICK_H` |
| `vpk_first_video` | function | `include/video_pick.h:18` | `const char *vpk_first_video(const pv_view *v);` |
| `vpk_for_frame` | function | `include/video_pick.h:23` | `const char *vpk_for_frame(const pv_view *frame_view, const char *top_video);` |
| `vpk_playable` | function | `include/video_pick.h:15` | `int vpk_playable(const char *src);` |
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
| `WF_LOAD_MAX_FETCHES` | macro | `include/webfont_load.h:54` | `#define WF_LOAD_MAX_FETCHES` |
| `WF_LOAD_MAX_KEYS` | macro | `include/webfont_load.h:53` | `#define WF_LOAD_MAX_KEYS` |
| `WF_LOAD_TRIES_PER_KEY` | macro | `include/webfont_load.h:52` | `#define WF_LOAD_TRIES_PER_KEY` |
| `free` | function | `include/webfont_load.h:31` | `* free()), *out_status the HTTP status. Nonzero on refusal/error (fail-closed: * the face is skipped, never the...` |
| `skipped` | function | `include/webfont_load.h:47` | `* URLs are skipped (no base). Returns faces registered (>= 0) otherwise. */ int wf_load_document(wf_fetch_fn fetch...` |
| `wf_sheet` | struct | `include/webfont_load.h:24` | `` |
| `FREEDOM_WL_DISPLAY_H` | macro | `include/wl_display.h:6` | `#define FREEDOM_WL_DISPLAY_H` |
| `WD_NONE` | macro | `include/wl_display.h:11` | `#define WD_NONE` |
| `WD_OK` | macro | `include/wl_display.h:10` | `#define WD_OK` |
| `pure` | function | `include/wl_display.h:3` | `* wd_pick is pure (no I/O);` |
| `wd_pick` | function | `include/wl_display.h:16` | `int wd_pick(const char *const *names, size_t n, char *out, size_t cap);` |
| `wd_resolve_env` | function | `include/wl_display.h:20` | `int wd_resolve_env(void);` |
| `FREEDOM_WL_GUARD_H` | macro | `include/wl_guard.h:2` | `#define FREEDOM_WL_GUARD_H` |
| `wl_display` | struct | `include/wl_guard.h:8` | `` |
| `wl_guard` | type_alias | `include/wl_guard.h:21` | `typedef struct wl_guard wl_guard;` |
| `wlg_start` | function | `include/wl_guard.h:25` | `wl_guard *wlg_start(struct wl_display *display);` |
| `wlg_stop` | function | `include/wl_guard.h:28` | `void wlg_stop(wl_guard *g);` |
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
| `anc_collect` | function | `src/anchor.c:93` | `size_t anc_collect(const dom_index *idx, dom_node_id target, dom_node_id *out, size_t cap,       ...` |
| `anc_percent_decode` | function | `src/anchor.c:15` | `size_t anc_percent_decode(const char *in, char *out, size_t cap)` |
| `anc_resolve` | function | `src/anchor.c:63` | `anc_kind anc_resolve(const dom_index *idx, const char *fragment, dom_node_id *out)` |
| `anc_scroll_for` | function | `src/anchor.c:131` | `double anc_scroll_for(double top, double max_scroll)` |
| `anc_target_top` | function | `src/anchor.c:110` | `int anc_target_top(const jg_table *g, const dom_node_id *h, size_t n, size_t nsub,               ...` |
| `first_named_a` | function | `src/anchor.c:35` | `static dom_node_id first_named_a(const dom_index *idx, const char *name)` |
| `hex_val` | function | `src/anchor.c:8` | `static int hex_val(int c)` |
| `is_top` | function | `src/anchor.c:59` | `static int is_top(const char *s)` |
| `next_preorder` | function | `src/anchor.c:81` | `static dom_node_id next_preorder(const dom_index *idx, dom_node_id cur, dom_node_id root,        ...` |
| `potential_indicated` | function | `src/anchor.c:54` | `static dom_node_id potential_indicated(const dom_index *idx, const char *s)` |
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
| `BB_BOX_MAX` | macro | `src/box_blur.c:31` | `#define BB_BOX_MAX` |
| `bb_blur_a8` | function | `src/box_blur.c:82` | `int bb_blur_a8(unsigned char *buf, int w, int h, int stride, double sigma)` |
| `bb_box_sizes` | function | `src/box_blur.c:8` | `int bb_box_sizes(double sigma, int sizes[3])` |
| `bb_ink_rect` | function | `src/box_blur.c:102` | `int bb_ink_rect(const unsigned char *argb, int w, int h, int stride, double sigma, int rect[4])` |
| `box_avg` | function | `src/box_blur.c:33` | `static unsigned char box_avg(long sum, int bw, uint64_t m)` |
| `box_cols` | function | `src/box_blur.c:56` | `static void box_cols(unsigned char *buf, int w, int h, int stride, int bw,                      u...` |
| `box_line` | function | `src/box_blur.c:39` | `static void box_line(unsigned char *p, int n, int step, int bw, unsigned char *tmp)` |
| `box_recip` | function | `src/box_blur.c:32` | `static uint64_t box_recip(int bw)` |
| `variance` | function | `src/box_blur.c:11` | `* width w has variance (w^2 - 1) / 12): the ideal common width, rounded down * to an odd wl and up to wu = wl + 2...` |
| `BLOCK` | macro | `src/box_style.c:67` | `#define BLOCK` |
| `BX_DISPLAY_MAX` | macro | `src/box_style.c:25` | `#define BX_DISPLAY_MAX` |
| `BX_TAG_MAX` | macro | `src/box_style.c:24` | `#define BX_TAG_MAX` |
| `DISP_N` | macro | `src/box_style.c:259` | `#define DISP_N` |
| `EDG` | macro | `src/box_style.c:72` | `#define EDG(t, r, b, l)` |
| `IBLOCK` | macro | `src/box_style.c:69` | `#define IBLOCK` |
| `INLINE` | macro | `src/box_style.c:68` | `#define INLINE` |
| `LITEM` | macro | `src/box_style.c:70` | `#define LITEM` |
| `NONE` | macro | `src/box_style.c:71` | `#define NONE` |
| `TAG_N` | macro | `src/box_style.c:161` | `#define TAG_N` |
| `T_CAP` | macro | `src/box_style.c:80` | `#define T_CAP` |
| `T_CELL` | macro | `src/box_style.c:79` | `#define T_CELL` |
| `T_COL` | macro | `src/box_style.c:81` | `#define T_COL` |
| `T_GRP` | macro | `src/box_style.c:77` | `#define T_GRP` |
| `T_NO` | macro | `src/box_style.c:75` | `#define T_NO` |
| `T_ROW` | macro | `src/box_style.c:78` | `#define T_ROW` |
| `T_TBL` | macro | `src/box_style.c:76` | `#define T_TBL` |
| `ZERO` | macro | `src/box_style.c:73` | `#define ZERO` |
| `bg_size_component` | function | `src/box_style.c:408` | `static double bg_size_component(int px_val, int pct_pm, double area)` |
| `bx_background_layer` | function | `src/box_style.c:415` | `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h,                     ...` |

Next: [SYMBOLS_p7.md](SYMBOLS_p7.md)
