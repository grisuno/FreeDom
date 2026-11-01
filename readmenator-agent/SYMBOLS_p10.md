# Symbols (page 10 of 16)
Previous: [SYMBOLS_p9.md](SYMBOLS_p9.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `ci_index` | function | `src/secure_fetch.c:58` | `static long ci_index(const char *haystack, const char *needle)` |
| `ci_starts_with` | function | `src/secure_fetch.c:46` | `static int ci_starts_with(const char *haystack, const char *prefix)` |
| `copy_bounded` | function | `src/secure_fetch.c:530` | `static void copy_bounded(char *dst, size_t dstsz, const char *src)` |
| `copy_checked` | function | `src/secure_fetch.c:352` | `static int copy_checked(char *dst, size_t dstsz, const char *src)` |
| `database` | function | `src/secure_fetch.c:545` | `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid...` |
| `fetch_ctx` | struct | `src/secure_fetch.c:513` | `` |
| `get_negotiated_group_name` | function | `src/secure_fetch.c:541` | `static const char *get_negotiated_group_name(SSL *ssl)` |
| `group` | function | `src/secure_fetch.c:559` | `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);` |
| `header_cb` | function | `src/secure_fetch.c:610` | `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` |
| `header_value_clean` | function | `src/secure_fetch.c:258` | `static int header_value_clean(const char *s)` |
| `inspect_chain` | function | `src/secure_fetch.c:709` | `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` |
| `map_curl_error` | function | `src/secure_fetch.c:762` | `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)` |
| `module` | function | `src/secure_fetch.c:413` | `* pure url module (DRY);` |
| `name_is_pq_sig` | function | `src/secure_fetch.c:699` | `static int name_is_pq_sig(int pknid)` |
| `progress` | function | `src/secure_fetch.c:499` | `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);` |
| `rcache_put_ram` | function | `src/secure_fetch.c:1197` | `static int rcache_put_ram(const char *from, const char *to, time_t now)` |
| `redirect` | function | `src/secure_fetch.c:892` | `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a      * different orig...` |
| `sf_accept_language_or_default` | function | `src/secure_fetch.c:268` | `const char *sf_accept_language_or_default(const char *lang)` |
| `sf_attempt_get` | function | `src/secure_fetch.c:1501` | `static sf_status sf_attempt_get(const char *url, const sf_config *cfg, sf_response *out,         ...` |
| `sf_attempt_post` | function | `src/secure_fetch.c:1507` | `static sf_status sf_attempt_post(const char *url, const sf_config *cfg, sf_response *out,        ...` |
| `sf_check_chain_policy` | function | `src/secure_fetch.c:311` | `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)` |
| `sf_check_group_is_pq` | function | `src/secure_fetch.c:302` | `sf_status sf_check_group_is_pq(const char *negotiated_group)` |
| `sf_check_tls_version` | function | `src/secure_fetch.c:297` | `sf_status sf_check_tls_version(const char *negotiated_version)` |
| `sf_ci_prefix` | function | `src/secure_fetch.c:420` | `static int sf_ci_prefix(const char *s, const char *p)` |
| `sf_config_default` | function | `src/secure_fetch.c:232` | `sf_config sf_config_default(void)` |
| `sf_cookie_header_for` | function | `src/secure_fetch.c:182` | `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)` |
| `sf_cookie_line_matches` | function | `src/secure_fetch.c:112` | `int sf_cookie_line_matches(const char *line, const char *host, const char *path,                 ...` |
| `sf_cookie_put` | function | `src/secure_fetch.c:211` | `void sf_cookie_put(const char *url, const char *namevalue)` |
| `sf_downgrade_of` | function | `src/secure_fetch.c:1492` | `static int sf_downgrade_of(sf_policy p)` |
| `sf_enforce_policy` | function | `src/secure_fetch.c:321` | `sf_status sf_enforce_policy(const char *tls_version, const char *group,                          ...` |
| `sf_fallback_policy` | function | `src/secure_fetch.c:1478` | `int sf_fallback_policy(sf_status failed, sf_policy tried, int allowlisted, sf_policy *next)` |
| `sf_get` | function | `src/secure_fetch.c:1144` | `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)` |
| `sf_get_follow` | function | `src/secure_fetch.c:1255` | `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,                 ...` |
| `sf_get_follow_navigable` | function | `src/secure_fetch.c:1532` | `sf_status sf_get_follow_navigable(const char *url, sf_config *cfg, sf_response *out,             ...` |
| `sf_global_init` | function | `src/secure_fetch.c:87` | `void sf_global_init(void)` |
| `sf_header_value` | function | `src/secure_fetch.c:368` | `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz)` |
| `sf_impersonate_kex_groups` | function | `src/secure_fetch.c:272` | `const char *sf_impersonate_kex_groups(void)` |
| `sf_impersonate_tls13_ciphers` | function | `src/secure_fetch.c:273` | `const char *sf_impersonate_tls13_ciphers(void)` |
| `sf_is_redirect_code` | function | `src/secure_fetch.c:361` | `int sf_is_redirect_code(long http_code)` |
| `sf_navigable` | function | `src/secure_fetch.c:1512` | `static sf_status sf_navigable(sf_attempt_fn attempt, const char *url, sf_config *cfg,            ...` |
| `sf_parse_location_header` | function | `src/secure_fetch.c:390` | `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)` |
| `sf_perform` | function | `src/secure_fetch.c:984` | `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,             ...` |
| `sf_post` | function | `src/secure_fetch.c:1148` | `sf_status sf_post(const char *url, const sf_config *cfg,                   const void *body, size...` |
| `sf_post_navigable` | function | `src/secure_fetch.c:1537` | `sf_status sf_post_navigable(const char *url, sf_config *cfg, const void *body,                   ...` |
| `sf_rcache_clear` | function | `src/secure_fetch.c:1178` | `void sf_rcache_clear(void)` |
| `sf_rcache_entry` | struct | `src/secure_fetch.c:1167` | `` |
| `sf_rcache_get` | function | `src/secure_fetch.c:1226` | `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap)` |
| `sf_rcache_put` | function | `src/secure_fetch.c:1216` | `int sf_rcache_put(const char *from, const char *to, time_t now)` |
| `sf_rcache_set_backing` | function | `src/secure_fetch.c:1189` | `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx)` |
| `sf_resolve_redirect` | function | `src/secure_fetch.c:408` | `sf_status sf_resolve_redirect(const char *base_url, const char *location,                        ...` |
| `sf_response_free` | function | `src/secure_fetch.c:460` | `void sf_response_free(sf_response *resp)` |
| `sf_setup_handle` | function | `src/secure_fetch.c:817` | `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,            ...` |
| `sf_share_lock` | function | `src/secure_fetch.c:74` | `static void sf_share_lock(CURL *handle, curl_lock_data data,                           curl_lock_...` |
| `sf_share_unlock` | function | `src/secure_fetch.c:80` | `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)` |
| `sf_url_host_path` | function | `src/secure_fetch.c:167` | `static int sf_url_host_path(const char *url, char *host, size_t hostsz,                          ...` |
| `sf_url_is_http` | function | `src/secure_fetch.c:285` | `static int sf_url_is_http(const char *url)` |
| `sf_user_agent_or_default` | function | `src/secure_fetch.c:264` | `const char *sf_user_agent_or_default(const char *ua)` |
| `sf_validate_url` | function | `src/secure_fetch.c:277` | `sf_status sf_validate_url(const char *url)` |
| `sf_ws` | struct | `src/secure_fetch.c:1332` | `` |
| `sf_ws_close` | function | `src/secure_fetch.c:1467` | `void sf_ws_close(sf_ws *ws)` |
| `sf_ws_fd` | function | `src/secure_fetch.c:1460` | `int sf_ws_fd(const sf_ws *ws)` |
| `sf_ws_open` | function | `src/secure_fetch.c:1360` | `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)` |
| `sf_ws_recv` | function | `src/secure_fetch.c:1438` | `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)` |
| `sf_ws_send` | function | `src/secure_fetch.c:1415` | `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)` |
| `sf_ws_url_check` | function | `src/secure_fetch.c:1339` | `sf_status sf_ws_url_check(const char *url)` |
| `sink` | type_alias | `src/secure_fetch.c:512` | `typedef struct fetch_ctx { body_sink sink;` |
| `this` | function | `src/secure_fetch.c:591` | `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and...` |
| `tls_capture` | struct | `src/secure_fetch.c:503` | `` |
| `tls_capture_from_ssl` | function | `src/secure_fetch.c:584` | `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)` |
| `tls_capture_try` | function | `src/secure_fetch.c:574` | `static void tls_capture_try(tls_capture *cap)` |
| `write_cb` | function | `src/secure_fetch.c:667` | `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)` |
| `ws_free` | function | `src/secure_fetch.c:1351` | `static void ws_free(sf_ws *ws)` |
| `ws_ssl_ctx_cb` | function | `src/secure_fetch.c:1325` | `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)` |
| `ws_ssl_info_cb` | function | `src/secure_fetch.c:1318` | `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)` |
| `ROL32` | macro | `src/sha2.c:9` | `#define ROL32(x, n)` |
| `ROR32` | macro | `src/sha2.c:8` | `#define ROR32(x, n)` |
| `ROR64` | macro | `src/sha2.c:10` | `#define ROR64(x, n)` |
| `be32` | function | `src/sha2.c:40` | `static uint32_t be32(const uint8_t *p)` |
| `be64` | function | `src/sha2.c:43` | `static uint64_t be64(const uint8_t *p)` |
| `ieq` | function | `src/sha2.c:22` | `static int ieq(const char *a, const char *b)` |
| `pad_tail` | function | `src/sha2.c:49` | `static size_t pad_tail(uint8_t *blk, size_t bs, size_t lenbytes, const uint8_t *tail, size_t tl, ...` |
| `put32` | function | `src/sha2.c:44` | `static void put32(uint8_t *p, uint32_t v)` |
| `put64` | function | `src/sha2.c:45` | `static void put64(uint8_t *p, uint64_t v)` |
| `sha1_block` | function | `src/sha2.c:61` | `static void sha1_block(uint32_t h[5], const uint8_t *p)` |
| `sha256_block` | function | `src/sha2.c:88` | `static void sha256_block(uint32_t h[8], const uint8_t *p)` |
| `sha512_block` | function | `src/sha2.c:131` | `static void sha512_block(uint64_t h[8], const uint8_t *p)` |
| `sha_alg_from_name` | function | `src/sha2.c:31` | `int sha_alg_from_name(const char *name, sha_alg *out)` |
| `sha_digest` | function | `src/sha2.c:152` | `int sha_digest(sha_alg alg, const void *data, size_t len, uint8_t *out)` |
| `sha_digest_len` | function | `src/sha2.c:12` | `size_t sha_digest_len(sha_alg alg)` |
| `_GNU_SOURCE` | macro | `src/subreq_batch.c:2` | `#define _GNU_SOURCE` |
| `dup_n` | function | `src/subreq_batch.c:30` | `static char *dup_n(const char *s, size_t n)` |
| `job_free` | function | `src/subreq_batch.c:44` | `static void job_free(sqb_job *j)` |
| `job_main` | function | `src/subreq_batch.c:51` | `static void *job_main(void *arg)` |
| `res_clear` | function | `src/subreq_batch.c:39` | `static void res_clear(sqb_res *r)` |
| `sqb` | struct | `src/subreq_batch.c:21` | `` |
| `sqb_count` | function | `src/subreq_batch.c:112` | `size_t sqb_count(const sqb *b)` |
| `sqb_free` | function | `src/subreq_batch.c:133` | `void sqb_free(sqb *b)` |
| `sqb_job` | struct | `src/subreq_batch.c:11` | `` |
| `sqb_new` | function | `src/subreq_batch.c:75` | `sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx)` |
| `sqb_reset` | function | `src/subreq_batch.c:126` | `void sqb_reset(sqb *b)` |
| `sqb_result` | function | `src/subreq_batch.c:122` | `const sqb_res *sqb_result(const sqb *b, size_t i)` |
| `sqb_submit` | function | `src/subreq_batch.c:86` | `int sqb_submit(sqb *b, int refused, const sqb_req *req)` |
| `sqb_wait_all` | function | `src/subreq_batch.c:114` | `void sqb_wait_all(sqb *b)` |
| `svp_alpha` | function | `src/svg_paint.c:31` | `static double svp_alpha(int opacity, int paint_opacity)` |
| `svp_draw` | function | `src/svg_paint.c:139` | `void svp_draw(cairo_t *cr, const sv_image *img,               double x, double y, double w, doubl...` |
| `svp_draw_ex` | function | `src/svg_paint.c:144` | `void svp_draw_ex(cairo_t *cr, const sv_image *img,                  double x, double y, double w,...` |
| `svp_draw_text` | function | `src/svg_paint.c:126` | `static void svp_draw_text(cairo_t *cr, const sv_shape *sh, int current_rgb)` |
| `svp_rect_path` | function | `src/svg_paint.c:38` | `static void svp_rect_path(cairo_t *cr, const sv_shape *sh)` |
| `svp_shape_path` | function | `src/svg_paint.c:73` | `static void svp_shape_path(cairo_t *cr, const sv_image *img, const sv_shape *sh)` |
| `sr_rasterize` | function | `src/svg_raster.c:50` | `img_status sr_rasterize(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `sr_skip_past` | function | `src/svg_raster.c:18` | `static size_t sr_skip_past(const uint8_t *b, size_t i, size_t n, const char *end)` |
| `sr_sniff` | function | `src/svg_raster.c:25` | `int sr_sniff(const uint8_t *bytes, size_t len)` |
| `sr_ws` | function | `src/svg_raster.c:14` | `static int sr_ws(uint8_t c)` |
| `SV_MAX_ATTRS` | macro | `src/svg_render.c:96` | `#define SV_MAX_ATTRS` |
| `point` | function | `src/svg_render.c:567` | `* current point (SVG 8.3.6). */ int had = (prev == 'C' \|\| prev == 'c' \|\| prev == 'S' \|\| prev == 's');` |
| `stroke` | type_alias | `src/svg_render.c:151` | `typedef struct sv_ctx { int fill, stroke;` |
| `sv_apply_prop` | function | `src/svg_render.c:260` | `static void sv_apply_prop(sv_ctx *ctx, const char *nm, size_t nl,                           const...` |
| `sv_arc_to_cubics` | function | `src/svg_render.c:399` | `static int sv_arc_to_cubics(sv_image *im, sv_shape *sh,                             double x0, do...` |
| `sv_attr` | struct | `src/svg_render.c:91` | `` |
| `sv_attr_get` | function | `src/svg_render.c:99` | `static const char *sv_attr_get(const sv_attr *at, size_t nat, const char *name, size_t *len)` |
| `sv_attr_num` | function | `src/svg_render.c:108` | `static double sv_attr_num(const sv_attr *at, size_t nat, const char *name, double dflt)` |
| `sv_collect_text` | function | `src/svg_render.c:736` | `static void sv_collect_text(const char *s, size_t n, size_t *i, char *dst, size_t cap)` |
| `sv_ctx` | struct | `src/svg_render.c:151` | `` |
| `sv_ctx_from_attrs` | function | `src/svg_render.c:307` | `static void sv_ctx_from_attrs(sv_ctx *ctx, const sv_attr *at, size_t nat)` |
| `sv_fit` | function | `src/svg_render.c:754` | `void sv_fit(const sv_image *img, double dw, double dh,             double *scale, double *off_x, ...` |
| `sv_flag` | function | `src/svg_render.c:477` | `static int sv_flag(const char *s, size_t n, size_t *i, double *out)` |
| `sv_is_digit` | function | `src/svg_render.c:25` | `static int sv_is_digit(char c)` |
| `sv_is_dropped_element` | function | `src/svg_render.c:646` | `static int sv_is_dropped_element(const char *name, size_t n)` |
| `sv_is_space` | function | `src/svg_render.c:21` | `static int sv_is_space(char c)` |
| `sv_lower` | function | `src/svg_render.c:27` | `static char sv_lower(char c)` |
| `sv_mat_identity` | function | `src/svg_render.c:161` | `static void sv_mat_identity(double *m)` |
| `sv_mat_mul` | function | `src/svg_render.c:166` | `static void sv_mat_mul(const double *a, const double *b, double *out)` |
| `sv_new_seg` | function | `src/svg_render.c:363` | `static sv_seg *sv_new_seg(sv_image *im, sv_shape *sh)` |
| `sv_new_shape` | function | `src/svg_render.c:324` | `static sv_shape *sv_new_shape(sv_image *im, int kind, const sv_ctx *ctx)` |
| `sv_parse` | function | `src/svg_render.c:774` | `sv_status sv_parse(const char *markup, size_t len, sv_image *out)` |
| `sv_parse_ex` | function | `src/svg_render.c:778` | `sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill)` |
| `sv_parse_path` | function | `src/svg_render.c:488` | `static void sv_parse_path(sv_image *im, sv_shape *sh, const char *s, size_t n)` |
| `sv_parse_points` | function | `src/svg_render.c:343` | `static void sv_parse_points(sv_image *im, sv_shape *sh, const char *s, size_t n)` |
| `sv_parse_transform` | function | `src/svg_render.c:179` | `static void sv_parse_transform(const char *s, size_t n, double *m)` |
| `sv_scan_attrs` | function | `src/svg_render.c:658` | `static void sv_scan_attrs(const char *s, size_t n, size_t *i,                           sv_attr *...` |
| `sv_seg_cubic` | function | `src/svg_render.c:385` | `static int sv_seg_cubic(sv_image *im, sv_shape *sh,                         double x1, double y1,...` |
| `sv_seg_line` | function | `src/svg_render.c:378` | `static int sv_seg_line(sv_image *im, sv_shape *sh, double x, double y)` |
| `sv_seg_move` | function | `src/svg_render.c:371` | `static int sv_seg_move(sv_image *im, sv_shape *sh, double x, double y)` |
| `sv_sep` | function | `src/svg_render.c:82` | `static void sv_sep(const char *s, size_t n, size_t *i)` |
| `sv_skip_subtree` | function | `src/svg_render.c:704` | `static void sv_skip_subtree(const char *s, size_t n, size_t *i, const char *name, size_t nlen)` |
| `sv_span_eq` | function | `src/svg_render.c:32` | `static int sv_span_eq(const char *s, size_t n, const char *lit)` |
| `sv_style_next` | function | `src/svg_render.c:238` | `static int sv_style_next(const char *s, size_t n, size_t *i,                          const char ...` |
| `EPIPE` | function | `src/tab.c:2279` | `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();` |
| `FB_MAX_FILE_BYTES` | function | `src/tab.c:1139` | `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify  * the stream. ...` |
| `PV_MAX_CONTAINERS_WIRE` | macro | `src/tab.c:165` | `#define PV_MAX_CONTAINERS_WIRE` |
| `TAB_ASYNC_THREADS` | macro | `src/tab.c:206` | `#define TAB_ASYNC_THREADS` |
| `TAB_IOBUF_BYTES` | macro | `src/tab.c:57` | `#define TAB_IOBUF_BYTES` |
| `TAB_MAX_ASYNC_PENDING` | macro | `src/tab.c:204` | `#define TAB_MAX_ASYNC_PENDING` |
| `TAB_MAX_BATCH_BYTES` | macro | `src/tab.c:207` | `#define TAB_MAX_BATCH_BYTES` |
| `TAB_MAX_EXTERN_CSS` | macro | `src/tab.c:1212` | `#define TAB_MAX_EXTERN_CSS` |
| `TAB_MAX_GEOM_WORDS` | macro | `src/tab.c:192` | `#define TAB_MAX_GEOM_WORDS` |
| `TAB_MAX_HIST_BYTES` | macro | `src/tab.c:186` | `#define TAB_MAX_HIST_BYTES` |
| `TAB_MAX_HIST_OPS` | macro | `src/tab.c:185` | `#define TAB_MAX_HIST_OPS` |
| `TAB_MAX_JS_JOBS` | macro | `src/tab.c:213` | `#define TAB_MAX_JS_JOBS` |
| `TAB_MAX_NET_ROUNDS` | macro | `src/tab.c:205` | `#define TAB_MAX_NET_ROUNDS` |
| `TAB_MAX_OPENS` | macro | `src/tab.c:188` | `#define TAB_MAX_OPENS` |
| `TAB_MAX_OPEN_BYTES` | macro | `src/tab.c:189` | `#define TAB_MAX_OPEN_BYTES` |
| `TAB_MAX_RUNS` | macro | `src/tab.c:161` | `#define TAB_MAX_RUNS` |
| `TAB_MAX_STORAGE` | macro | `src/tab.c:181` | `#define TAB_MAX_STORAGE` |
| `TAB_MAX_SUBREQ` | macro | `src/tab.c:211` | `#define TAB_MAX_SUBREQ` |
| `TAB_MAX_SUBRESOURCE` | macro | `src/tab.c:212` | `#define TAB_MAX_SUBRESOURCE` |
| `TAB_MAX_URL` | macro | `src/tab.c:168` | `#define TAB_MAX_URL` |
| `TAB_MAX_WS_MSG` | macro | `src/tab.c:177` | `#define TAB_MAX_WS_MSG` |
| `TAB_SCREEN_H` | macro | `src/tab.c:134` | `#define TAB_SCREEN_H` |
| `TAB_SCREEN_W` | macro | `src/tab.c:133` | `#define TAB_SCREEN_W` |
| `TAB_WIRE_A_N` | macro | `src/tab.c:139` | `#define TAB_WIRE_A_N` |
| `TAB_WIRE_BOX_F_N` | macro | `src/tab.c:141` | `#define TAB_WIRE_BOX_F_N` |
| `TAB_WIRE_B_N` | macro | `src/tab.c:140` | `#define TAB_WIRE_B_N` |
| `TAB_WIRE_GRID_N` | macro | `src/tab.c:142` | `#define TAB_WIRE_GRID_N` |
| `TAB_WIRE_HEAD_N` | macro | `src/tab.c:138` | `#define TAB_WIRE_HEAD_N` |
| `WHERE` | function | `src/tab.c:1700` | `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...` |
| `_GNU_SOURCE` | macro | `src/tab.c:14` | `#define _GNU_SOURCE` |
| `adopt_worker` | function | `src/tab.c:3311` | `static tab_status adopt_worker(const tab_spawned *sp, tab **out)` |
| `blocks` | function | `src/tab.c:687` | `* * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the * grid array, block B[26])...` |
| `budget_remaining_ms` | function | `src/tab.c:1169` | `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` |
| `buffer` | function | `src/tab.c:622` | `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...` |
| `child_fetch` | function | `src/tab.c:456` | `static int child_fetch(void *vctx, const char *method, const char *url,                        co...` |
| `child_fetch_async` | function | `src/tab.c:472` | `static int child_fetch_async(void *vctx, const char *method, const char *url,                    ...` |
| `child_handle_click` | function | `src/tab.c:2009` | `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_decode_image` | function | `src/tab.c:2210` | `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` |
| `child_handle_decode_image_data` | function | `src/tab.c:2237` | `static void child_handle_decode_image_data(int wfd, const char *url, size_t len)` |
| `child_handle_eval` | function | `src/tab.c:2169` | `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` |
| `child_handle_event` | function | `src/tab.c:2023` | `static void child_handle_event(int wfd, child_state *cs)` |
| `child_handle_geom` | function | `src/tab.c:2109` | `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` |
| `child_handle_load` | function | `src/tab.c:1430` | `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,            ...` |
| `child_handle_mouse` | function | `src/tab.c:2071` | `static void child_handle_mouse(int wfd, child_state *cs)` |
| `child_handle_mutation` | function | `src/tab.c:1928` | `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,                         ...` |
| `child_handle_submit` | function | `src/tab.c:2135` | `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_tick` | function | `src/tab.c:2013` | `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)` |
| `child_load` | function | `src/tab.c:554` | `static int child_load(child_state *cs, const char *html, size_t len, int run_js,                 ...` |
| `child_next_timer_ms` | function | `src/tab.c:1913` | `static int32_t child_next_timer_ms(child_state *cs)` |
| `child_prescript_view` | function | `src/tab.c:1400` | `static pv_view *child_prescript_view(child_state *cs, const char *html, size_t len,              ...` |
| `child_read_reply` | function | `src/tab.c:428` | `static int child_read_reply(child_state *cs, net_reply *out)` |
| `child_reset_page` | function | `src/tab.c:271` | `static void child_reset_page(child_state *cs)` |
| `child_state` | struct | `src/tab.c:224` | `` |
| `child_write_subreq` | function | `src/tab.c:403` | `static int child_write_subreq(child_state *cs, uint8_t tag, const char *method, const char *url, ...` |
| `clip_pm_ok` | function | `src/tab.c:146` | `static int clip_pm_ok(int32_t v)` |
| `column` | function | `src/tab.c:2837` | `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...` |
| `computed_signature` | function | `src/tab.c:299` | `static uint64_t computed_signature(const dom_index *idx)` |
| `content` | function | `src/tab.c:1765` | `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...` |
| `ctype_is_css` | function | `src/tab.c:1192` | `static int ctype_is_css(const char *ctype)` |
| `ctype_is_javascript` | function | `src/tab.c:1183` | `static int ctype_is_javascript(const char *ctype)` |
| `depth` | function | `src/tab.c:2309` | `* defense in depth (seccomp already excludes open/socket/exec);` |
| `exec_worker_child` | function | `src/tab.c:3240` | `static void exec_worker_child(int rfd, int wfd)` |
| `fd` | type_alias | `src/tab.c:58` | `typedef struct tab_iobuf { int fd;` |
| `frames` | function | `src/tab.c:4189` | `* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of...` |
| `gate_js_nav` | function | `src/tab.c:3838` | `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` |
| `gen_session_key` | function | `src/tab.c:2257` | `static uint64_t gen_session_key(void)` |
| `geom_parent` | function | `src/tab.c:2101` | `static dom_node_id geom_parent(void *ctx, dom_node_id n)` |
| `geometry_encode` | function | `src/tab.c:4510` | `static int32_t *geometry_encode(const jg_table *g, size_t *words_out)` |
| `hist_ops_free` | function | `src/tab.c:3647` | `static void hist_ops_free(tab_hist_op *ops, size_t n)` |
| `ignore_sigpipe` | function | `src/tab.c:2587` | `static void ignore_sigpipe(void)` |
| `io_failure` | function | `src/tab.c:3232` | `static tab_status io_failure(tab *t)` |
| `is_activation_event` | function | `src/tab.c:3712` | `static int is_activation_event(const char *type)` |
| `job_discard` | function | `src/tab.c:4534` | `static void job_discard(tab *t)` |
| `job_main` | function | `src/tab.c:4556` | `static void *job_main(void *arg)` |
| `job_start` | function | `src/tab.c:4585` | `static tab_status job_start(tab *t)` |
| `layout` | function | `src/tab.c:2826` | `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....` |
| `libraries` | function | `src/tab.c:1535` | `* load heavier libraries (jQuery, Bootstrap, etc.) that need more time. * Untrusted hosts get the default budget...` |
| `load` | function | `src/tab.c:2547` | `* subresource requests this load (set per page: host in allow.conf AND js.conf);` |
| `log_external_skip` | function | `src/tab.c:1200` | `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,                 ...` |
| `net_reply` | struct | `src/tab.c:392` | `` |
| `net_reply_free` | function | `src/tab.c:400` | `static void net_reply_free(net_reply *r)` |
| `once` | function | `src/tab.c:1816` | `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);` |
| `open_urls_free` | function | `src/tab.c:3721` | `static void open_urls_free(char **u, size_t n)` |
| `parse_worker_fd` | function | `src/tab.c:2508` | `static int parse_worker_fd(const char *s, int *out)` |
| `prof_lap` | function | `src/tab.c:519` | `static void prof_lap(const char *what, double *t0)` |
| `prof_now_ms` | function | `src/tab.c:509` | `static double prof_now_ms(void)` |
| `prof_on` | function | `src/tab.c:514` | `static int prof_on(void)` |
| `rad_len_ok` | function | `src/tab.c:152` | `static int rad_len_ok(int32_t v, int dflt)` |
| `read_console` | function | `src/tab.c:3185` | `static int read_console(int fd, fb_buffer *out)` |
| `read_field` | function | `src/tab.c:2613` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `read_full` | macro | `src/tab.c:112` | `#define read_full(fd, buf, n)` |
| `read_opens` | function | `src/tab.c:3731` | `static tab_status read_opens(tab *t, const char *page_url, int gesture,                          ...` |
| `read_view` | function | `src/tab.c:2630` | `static int read_view(int fd, pv_view **out)` |
| `read_view_raw` | function | `src/tab.c:2638` | `static int read_view_raw(int fd, pv_view **out)` |
| `read_ws` | function | `src/tab.c:3769` | `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` |
| `reap_spawned` | function | `src/tab.c:3302` | `static void reap_spawned(const tab_spawned *sp, int kill_it)` |
| `replies` | function | `src/tab.c:485` | `* writing replies (no pipe deadlock). */ static void child_net_drain(child_state *cs)` |
| `run` | function | `src/tab.c:1218` | `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).  * Call after every ...` |
| `run_js` | function | `src/tab.c:530` | `* regardless of run_js (a no-JS load simply never records a request). */ /* Installs the page-ind...` |
| `send_request` | function | `src/tab.c:3222` | `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` |
| `sig_mix` | function | `src/tab.c:291` | `static uint64_t sig_mix(uint64_t h, const char *s, size_t n)` |
| `spawn_worker` | function | `src/tab.c:3272` | `static tab_status spawn_worker(tab_spawned *sp)` |
| `status` | type_alias | `src/tab.c:392` | `typedef struct net_reply { int32_t status;` |
| `swap` | function | `src/tab.c:1825` | `* display:none hiding an element via class swap (CSS, not      * DOM removal). */     if (ok && v...` |
| `tab` | struct | `src/tab.c:2540` | `` |
| `tab_alive` | function | `src/tab.c:4413` | `int tab_alive(const tab *t)` |
| `tab_async_busy` | function | `src/tab.c:4581` | `int tab_async_busy(const tab *t)` |
| `tab_async_fd` | function | `src/tab.c:4572` | `int tab_async_fd(tab *t)` |
| `tab_async_finish` | function | `src/tab.c:4623` | `tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)` |
| `tab_async_sync` | function | `src/tab.c:4546` | `static void tab_async_sync(tab *t)` |
| `tab_await_result` | function | `src/tab.c:4192` | `static tab_status tab_await_result(tab *t)` |
| `tab_await_result_inner` | function | `src/tab.c:4200` | `static tab_status tab_await_result_inner(tab *t)` |
| `tab_batch_discard` | function | `src/tab.c:3642` | `static void tab_batch_discard(tab *t)` |
| `tab_batch_run` | function | `src/tab.c:3575` | `static int tab_batch_run(void *vt, const sqb_req *rq, sqb_res *out)` |
| `tab_child_pid` | function | `src/tab.c:4419` | `pid_t tab_child_pid(const tab *t)` |
| `tab_click` | function | `src/tab.c:4057` | `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)` |
| `tab_close` | function | `src/tab.c:4423` | `void tab_close(tab *t)` |
| `tab_decode_image` | function | `src/tab.c:4392` | `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)` |
| `tab_decode_image_data_url` | function | `src/tab.c:4399` | `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)` |
| `tab_decode_image_op` | function | `src/tab.c:4345` | `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,         ...` |
| `tab_eval` | function | `src/tab.c:4304` | `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)` |
| `tab_eval_result_free` | function | `src/tab.c:4471` | `void tab_eval_result_free(tab_eval_result *r)` |
| `tab_geometry_async` | function | `src/tab.c:4608` | `tab_status tab_geometry_async(tab *t, const jg_table *g)` |
| `tab_geometry_send` | function | `src/tab.c:4492` | `static tab_status tab_geometry_send(tab *t, const int32_t *buf, size_t words)` |
| `tab_image_free` | function | `src/tab.c:4480` | `void tab_image_free(tab_image *img)` |
| `tab_inflight_request_headers` | function | `src/tab.c:3466` | `const char *tab_inflight_request_headers(void)` |
| `tab_iobuf` | struct | `src/tab.c:58` | `` |
| `tab_last_subreq_stats` | function | `src/tab.c:3411` | `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)` |
| `tab_load` | function | `src/tab.c:3848` | `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)` |
| `tab_load_ex` | function | `src/tab.c:3852` | `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)` |
| `tab_load_full` | function | `src/tab.c:3856` | `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,             ...` |
| `tab_mod_fetch` | function | `src/tab.c:1306` | `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` |
| `tab_mod_resolve` | function | `src/tab.c:1276` | `static int tab_mod_resolve(void *host, const char *base, const char *spec,                       ...` |
| `tab_note_css_served` | function | `src/tab.c:3532` | `static void tab_note_css_served(tab *t, int ok, int status, const char *url, const char *rbody,  ...` |
| `tab_op_budget_us` | function | `src/tab.c:3528` | `static int64_t tab_op_budget_us(const tab *t)` |
| `tab_open` | function | `src/tab.c:3362` | `tab_status tab_open(tab **out)` |
| `tab_page_free` | function | `src/tab.c:4441` | `void tab_page_free(tab_page *p)` |
| `tab_parse_worker_args` | function | `src/tab.c:2520` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)` |
| `tab_popstate` | function | `src/tab.c:4645` | `tab_status tab_popstate(tab *t, int index, tab_page *out)` |
| `tab_prewarm` | function | `src/tab.c:3333` | `void tab_prewarm(void)` |
| `tab_prewarmed` | function | `src/tab.c:3339` | `int tab_prewarmed(void)` |
| `tab_prewarmed_pid` | function | `src/tab.c:3346` | `int tab_prewarmed_pid(void)` |
| `tab_read_full` | function | `src/tab.c:86` | `static int tab_read_full(int fd, void *buf, size_t n)` |
| `tab_read_subreq_fields` | function | `src/tab.c:3517` | `static int tab_read_subreq_fields(tab *t, char **method, char **url, char **body, size_t *blen,  ...` |
| `tab_read_view` | function | `src/tab.c:4183` | `tab_status tab_read_view(tab *t, tab_page *out)` |
| `tab_read_view_ex` | function | `src/tab.c:4209` | `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)` |
| `tab_refresh_alive` | function | `src/tab.c:2594` | `static void tab_refresh_alive(tab *t)` |
| `tab_report_response_headers` | function | `src/tab.c:3454` | `void tab_report_response_headers(const char *lines)` |
| `tab_serve_netwait` | function | `src/tab.c:3612` | `static int tab_serve_netwait(tab *t)` |
| `tab_serve_subreq` | function | `src/tab.c:3548` | `static int tab_serve_subreq(tab *t, int net_granted, int css_granted)` |
| `tab_serve_tag` | function | `src/tab.c:3634` | `static int tab_serve_tag(tab *t, uint8_t tag, int net_granted, int css_granted)` |
| `tab_set_cookies` | function | `src/tab.c:3434` | `void tab_set_cookies(tab *t, const char *cookies)` |
| `tab_set_css_allowed` | function | `src/tab.c:3406` | `void tab_set_css_allowed(tab *t, int allowed)` |
| `tab_set_css_sink` | function | `src/tab.c:3391` | `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)` |
| `tab_set_fetcher` | function | `src/tab.c:3385` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)` |
| `tab_set_frame_id` | function | `src/tab.c:3424` | `void tab_set_frame_id(tab *t, int id)` |
| `tab_set_geometry` | function | `src/tab.c:4520` | `tab_status tab_set_geometry(tab *t, const jg_table *g)` |
| `tab_set_identity` | function | `src/tab.c:3416` | `void tab_set_identity(tab *t, const char *serialized)` |
| `tab_set_net_allowed` | function | `src/tab.c:3401` | `void tab_set_net_allowed(tab *t, int allowed)` |
| `tab_set_op_net_budget_ms` | function | `src/tab.c:3397` | `void tab_set_op_net_budget_ms(tab *t, int ms)` |
| `tab_set_storage` | function | `src/tab.c:4672` | `void tab_set_storage(tab *t, const char *blob, size_t len)` |
| `tab_set_viewport_w` | function | `src/tab.c:3429` | `void tab_set_viewport_w(tab *t, int px)` |
| `tab_shutdown_spare` | function | `src/tab.c:3353` | `void tab_shutdown_spare(void)` |
| `tab_spawned` | struct | `src/tab.c:3260` | `` |
| `tab_submit` | function | `src/tab.c:4075` | `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` |
| `tab_submit_async` | function | `src/tab.c:3590` | `static int tab_submit_async(tab *t, int net_granted, int css_granted)` |
| `tab_subreq_permitted` | function | `src/tab.c:3440` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)` |
| `tab_tick` | function | `src/tab.c:4065` | `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)` |
| `tab_tick_async` | function | `src/tab.c:4598` | `tab_status tab_tick_async(tab *t, int elapsed_ms)` |
| `tab_url_resolve` | function | `src/tab.c:1267` | `static int tab_url_resolve(void *ctx, const char *base, const char *ref,                         ...` |
| `tab_wflush` | function | `src/tab.c:67` | `static int tab_wflush(void)` |
| `tab_worker_dispatch` | function | `src/tab.c:2530` | `void tab_worker_dispatch(int argc, char **argv)` |
| `tab_worker_run` | function | `src/tab.c:2277` | `static void tab_worker_run(int rfd, int wfd)` |
| `tab_write_full` | function | `src/tab.c:74` | `static int tab_write_full(int fd, const void *buf, size_t n)` |
| `tab_write_reply` | function | `src/tab.c:3472` | `static int tab_write_reply(tab *t, int ok, int status, const char *rbody, size_t rlen,           ...` |
| `tab_ws_event` | function | `src/tab.c:4652` | `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,        ...` |
| `tests` | function | `src/tab.c:2713` | `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...` |
| `tzset` | function | `src/tab.c:2295` | `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);` |
| `window` | function | `src/tab.c:1347` | `* net window (cs->net_active). */ static void child_fetch_stylesheets(child_state *cs)` |
| `write_field` | function | `src/tab.c:653` | `static int write_field(int fd, const char *s)` |
| `write_full` | macro | `src/tab.c:111` | `#define write_full(fd, buf, n)` |
| `write_full` | function | `src/tab.c:1846` | `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 \|\| write_full(wfd, text, xl) == 0) && write_view(wfd...` |
| `write_history` | function | `src/tab.c:1328` | `static int write_history(int wfd, child_state *cs)` |
| `write_opens` | function | `src/tab.c:1901` | `static int write_opens(int wfd, child_state *cs)` |
| `write_storage` | function | `src/tab.c:1887` | `static int write_storage(int wfd, child_state *cs)` |
| `write_view` | function | `src/tab.c:695` | `static int write_view(int wfd, const pv_view *v)` |
| `write_view_raw` | function | `src/tab.c:706` | `static int write_view_raw(int wfd, const pv_view *v)` |
| `write_ws` | function | `src/tab.c:1870` | `static int write_ws(int wfd, child_state *cs)` |
| `ws_ops_free` | function | `src/tab.c:3760` | `static void ws_ops_free(tab_ws_op *ops, size_t n)` |
| `pair_parity` | function | `src/text_case.c:8` | `static int pair_parity(uint32_t cp)` |
| `tc_is_lower` | function | `src/text_case.c:54` | `int tc_is_lower(uint32_t cp)` |
| `tc_lower` | function | `src/text_case.c:37` | `uint32_t tc_lower(uint32_t cp)` |
| `tc_smallcaps_runs` | function | `src/text_case.c:117` | `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap)` |
| `tc_transform` | function | `src/text_case.c:95` | `size_t tc_transform(const char *s, size_t n, int transform, int word_start,                     c...` |
| `tc_upper` | function | `src/text_case.c:18` | `uint32_t tc_upper(uint32_t cp)` |
| `utf8_decode` | function | `src/text_case.c:61` | `static size_t utf8_decode(const unsigned char *s, size_t n, uint32_t *cp)` |
| `utf8_len_of` | function | `src/text_case.c:91` | `static size_t utf8_len_of(uint32_t cp)` |
| `utf8_put` | function | `src/text_case.c:79` | `static void utf8_put(uint32_t cp, size_t len, unsigned char *out)` |
| `TSH_BLANK_GLYPH` | macro | `src/text_shape.c:620` | `#define TSH_BLANK_GLYPH` |
| `TSH_CACHE_SLOTS` | macro | `src/text_shape.c:34` | `#define TSH_CACHE_SLOTS` |
| `TSH_FB_BLOCKS` | macro | `src/text_shape.c:663` | `#define TSH_FB_BLOCKS` |
| `TSH_FB_CP_SLOTS` | macro | `src/text_shape.c:680` | `#define TSH_FB_CP_SLOTS` |
| `TSH_FB_SLOTS` | macro | `src/text_shape.c:662` | `#define TSH_FB_SLOTS` |
| `TSH_MAX_FONT_BYTES` | macro | `src/text_shape.c:30` | `#define TSH_MAX_FONT_BYTES` |
| `TSH_MAX_RUNS` | macro | `src/text_shape.c:864` | `#define TSH_MAX_RUNS` |
| `TSH_MEASURE_SLOTS` | macro | `src/text_shape.c:917` | `#define TSH_MEASURE_SLOTS` |
| `TSH_MEASURE_TEXT_MAX` | macro | `src/text_shape.c:918` | `#define TSH_MEASURE_TEXT_MAX` |
| `TSH_SUBS_MAX` | macro | `src/text_shape.c:406` | `#define TSH_SUBS_MAX` |
| `TSH_WEB_SLOTS` | macro | `src/text_shape.c:190` | `#define TSH_WEB_SLOTS` |
| `_POSIX_C_SOURCE` | macro | `src/text_shape.c:12` | `#define _POSIX_C_SOURCE` |
| `ascii_ieq` | function | `src/text_shape.c:337` | `static int ascii_ieq(const char *a, const char *b)` |
| `backend_init` | function | `src/text_shape.c:66` | `static int backend_init(void)` |
| `characters` | function | `src/text_shape.c:101` | `* hold characters ('-', ':') that the pattern syntax treats specially. */ static int load_entry_file(tsh_entry *e...` |
| `cover_cp` | function | `src/text_shape.c:818` | `static int cover_cp(unsigned cp, void *vctx)` |
| `entry_free` | function | `src/text_shape.c:324` | `static void entry_free(tsh_entry *e)` |
| `fb_clear` | function | `src/text_shape.c:689` | `static void fb_clear(void)` |
| `fb_entry` | function | `src/text_shape.c:731` | `static tsh_entry *fb_entry(unsigned cp, int bold)` |
| `fb_entry_uncached` | function | `src/text_shape.c:748` | `static tsh_entry *fb_entry_uncached(unsigned cp, int bold)` |
| `fb_match_covering` | function | `src/text_shape.c:709` | `static FcPattern *fb_match_covering(FcPattern *pat, FcCharSet *cs)` |
| `fc_installed` | function | `src/text_shape.c:392` | `static int fc_installed(const char *name, void *ctx)` |
| `fc_resolve` | function | `src/text_shape.c:435` | `static int fc_resolve(const char *name, char *out, size_t cap, void *ctx)` |
| `file` | type_alias | `src/text_shape.c:664` | `typedef struct tsh_fb { char file[512];` |
| `generic_name` | function | `src/text_shape.c:56` | `static const char *generic_name(int family)` |
| `get_entry` | function | `src/text_shape.c:174` | `static tsh_entry *get_entry(int family, int bold, int italic)` |
| `get_entry_ex` | function | `src/text_shape.c:538` | `static tsh_entry *get_entry_ex(const tsh_font *f)` |
| `is_private_use` | function | `src/text_shape.c:623` | `static int is_private_use(unsigned cp)` |
| `lfam_index` | function | `src/text_shape.c:491` | `static int lfam_index(const char *fam)` |
| `load_entry` | function | `src/text_shape.c:170` | `static int load_entry(tsh_entry *e, int family, int bold, int italic)` |
| `load_entry_file` | function | `src/text_shape.c:134` | `static int load_entry_file(tsh_entry *e, const char *path, int index)` |
| `load_entry_named` | function | `src/text_shape.c:104` | `static int load_entry_named(tsh_entry *e, const char *fam, int bold, int italic)` |
| `loaded` | type_alias | `src/text_shape.c:35` | `typedef struct tsh_entry { int loaded;` |
| `local_clear` | function | `src/text_shape.c:480` | `static void local_clear(void)` |
| `local_entry` | function | `src/text_shape.c:518` | `static tsh_entry *local_entry(int handle, int bold, int italic)` |
| `name` | type_alias | `src/text_shape.c:463` | `typedef struct tsh_lfam { char name[TSH_FAMILY_MAX];` |
| `read_font_file` | function | `src/text_shape.c:83` | `static unsigned char *read_font_file(const char *path, long *out_n)` |
| `rides_previous` | function | `src/text_shape.c:628` | `static int rides_previous(unsigned cp)` |
| `shape_entry` | function | `src/text_shape.c:832` | `static tsh_status shape_entry(tsh_entry *e, double px, const char *text, size_t len,             ...` |
| `shape_runs` | function | `src/text_shape.c:868` | `static tsh_status shape_runs(cairo_t *cr, const tsh_font *f, double px, double x,                ...` |
| `slice` | function | `src/text_shape.c:214` | `* woff2 slice (spec/webfont.md);` |
| `tsh_cover_ctx` | struct | `src/text_shape.c:809` | `` |
| `tsh_draw` | function | `src/text_shape.c:964` | `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,                     double x, doub...` |
| `tsh_entry` | struct | `src/text_shape.c:36` | `` |
| `tsh_face` | function | `src/text_shape.c:971` | `cairo_font_face_t *tsh_face(const tsh_font *f)` |
| `tsh_family_is_generic` | function | `src/text_shape.c:346` | `int tsh_family_is_generic(const char *name)` |
| `tsh_fb` | struct | `src/text_shape.c:665` | `` |
| `tsh_fb_cp` | struct | `src/text_shape.c:681` | `` |
| `tsh_lfam` | struct | `src/text_shape.c:464` | `` |
| `tsh_llist` | struct | `src/text_shape.c:470` | `` |
| `tsh_local_handle` | function | `src/text_shape.c:499` | `int tsh_local_handle(const char *list)` |
| `tsh_measure` | function | `src/text_shape.c:929` | `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)` |
| `tsh_measure_slot` | struct | `src/text_shape.c:919` | `` |
| `tsh_pick_family` | function | `src/text_shape.c:379` | `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong,         ...` |
| `tsh_pick_from_list` | function | `src/text_shape.c:358` | `int tsh_pick_from_list(const char *list, tsh_name_resolver resolve, void *ctx,                   ...` |
| `tsh_ready` | function | `src/text_shape.c:550` | `int tsh_ready(void)` |
| `tsh_segment` | function | `src/text_shape.c:636` | `int tsh_segment(const char *text, size_t len, tsh_cover_fn cover, void *ctx,                 tsh_...` |
| `tsh_shape` | function | `src/text_shape.c:555` | `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,                 ...` |
| `tsh_shutdown` | function | `src/text_shape.c:977` | `void tsh_shutdown(void)` |
| `tsh_web` | struct | `src/text_shape.c:192` | `` |
| `tsh_webfont_clear` | function | `src/text_shape.c:306` | `void tsh_webfont_clear(void)` |
| `tsh_webfont_register` | function | `src/text_shape.c:271` | `int tsh_webfont_register(const char *name,                          const unsigned char *bytes, s...` |
| `used` | type_alias | `src/text_shape.c:191` | `typedef struct tsh_web { int used;` |
| `utf8_next` | function | `src/text_shape.c:604` | `static unsigned utf8_next(const char *s, size_t n, size_t *len)` |
| `web_entry_free` | function | `src/text_shape.c:202` | `static void web_entry_free(tsh_web *w)` |
| `web_find` | function | `src/text_shape.c:312` | `static tsh_entry *web_find(unsigned h, int bold, int italic)` |
| `web_magic_ok` | function | `src/text_shape.c:215` | `static int web_magic_ok(const unsigned char *b, size_t n)` |
| `web_make_entry` | function | `src/text_shape.c:228` | `static int web_make_entry(tsh_entry *e, const unsigned char *bytes, size_t nbytes)` |
| `tf_backspace` | function | `src/textfield.c:47` | `void tf_backspace(tf_field *f)` |
| `tf_clear` | function | `src/textfield.c:20` | `void tf_clear(tf_field *f)` |
| `tf_cursor` | function | `src/textfield.c:91` | `size_t tf_cursor(const tf_field *f)` |
| `tf_delete` | function | `src/textfield.c:55` | `void tf_delete(tf_field *f)` |
| `tf_end` | function | `src/textfield.c:78` | `void tf_end(tf_field *f)` |
| `tf_home` | function | `src/textfield.c:73` | `void tf_home(tf_field *f)` |
| `tf_insert` | function | `src/textfield.c:35` | `tf_status tf_insert(tf_field *f, char c)` |
| `tf_len` | function | `src/textfield.c:87` | `size_t tf_len(const tf_field *f)` |
| `tf_move` | function | `src/textfield.c:62` | `void tf_move(tf_field *f, long delta)` |
| `tf_set` | function | `src/textfield.c:24` | `tf_status tf_set(tf_field *f, const char *s)` |
| `tf_text` | function | `src/textfield.c:83` | `const char *tf_text(const tf_field *f)` |
| `whole` | function | `src/textfield.c:6` | `* the buffer is rejected whole (fail closed), never applied partially.  */  #include "textfield.h...` |
| `bounded_len` | function | `src/tls_impersonate.c:25` | `static size_t bounded_len(const char *s, size_t max)` |
| `get_bytes` | function | `src/tls_impersonate.c:89` | `static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len)` |
| `get_str` | function | `src/tls_impersonate.c:103` | `static char *get_str(ti_rd *r, size_t cap)` |
| `get_u32` | function | `src/tls_impersonate.c:70` | `static uint32_t get_u32(ti_rd *r)` |
| `get_u64` | function | `src/tls_impersonate.c:80` | `static uint64_t get_u64(ti_rd *r)` |
| `get_u8` | function | `src/tls_impersonate.c:65` | `static uint8_t get_u8(ti_rd *r)` |
| `put_blob` | function | `src/tls_impersonate.c:53` | `static void put_blob(ti_wr *w, const uint8_t *b, size_t n)` |
| `put_u32` | function | `src/tls_impersonate.c:40` | `static void put_u32(ti_wr *w, uint32_t v)` |
| `put_u64` | function | `src/tls_impersonate.c:48` | `static void put_u64(ti_wr *w, uint64_t v)` |
| `put_u8` | function | `src/tls_impersonate.c:35` | `static void put_u8(ti_wr *w, uint8_t v)` |
| `ti_decode_req` | function | `src/tls_impersonate.c:140` | `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out)` |
| `ti_decode_resp` | function | `src/tls_impersonate.c:196` | `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out)` |
| `ti_encode_req` | function | `src/tls_impersonate.c:122` | `size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap)` |
| `ti_encode_resp` | function | `src/tls_impersonate.c:177` | `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap)` |
| `ti_rd` | struct | `src/tls_impersonate.c:63` | `` |
| `ti_req_free` | function | `src/tls_impersonate.c:166` | `void ti_req_free(ti_req *r)` |
| `ti_resp_free` | function | `src/tls_impersonate.c:230` | `void ti_resp_free(ti_resp *r)` |
| `ti_should_impersonate` | function | `src/tls_impersonate.c:18` | `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,                           i...` |
| `ti_wr` | struct | `src/tls_impersonate.c:33` | `` |
| `valid_profile` | function | `src/tls_impersonate.c:116` | `static int valid_profile(int p)` |
| `layout_push` | function | `src/ui_layout.c:13` | `static int layout_push(ui_layout *lay, size_t offset, size_t len)` |
| `ui_clamp_scroll` | function | `src/ui_layout.c:99` | `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines)` |
| `ui_layout_free` | function | `src/ui_layout.c:91` | `void ui_layout_free(ui_layout *lay)` |
| `ui_wrap_text` | function | `src/ui_layout.c:27` | `ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out)` |
| `_POSIX_C_SOURCE` | macro | `src/url.c:9` | `#define _POSIX_C_SOURCE` |
| `append_query_encoded` | function | `src/url.c:229` | `static int append_query_encoded(char *out, size_t outsz, const char *src)` |
| `assumed` | function | `src/url.c:254` | `* assumed (the caller already routed whitespace to search). */ static int looks_like_host(const c...` |
| `build_search` | function | `src/url.c:303` | `static url_status build_search(const char *query, char *out, size_t outsz)` |
| `cat_checked` | function | `src/url.c:40` | `static int cat_checked(char *out, size_t outsz, const char *src)` |
| `ci_prefix` | function | `src/url.c:20` | `static int ci_prefix(const char *haystack, const char *prefix)` |
| `copy_bounded` | function | `src/url.c:645` | `static url_status copy_bounded(char *out, size_t outsz, const char *a, size_t alen,              ...` |
| `copy_checked` | function | `src/url.c:32` | `static int copy_checked(char *out, size_t outsz, const char *src)` |
| `dir_len` | function | `src/url.c:159` | `static size_t dir_len(const char *base)` |
| `host_equals` | function | `src/url.c:378` | `static int host_equals(const url_parts *p, const char *want)` |
| `is_space` | function | `src/url.c:218` | `static int is_space(int c)` |
| `is_unreserved` | function | `src/url.c:222` | `static int is_unreserved(int c)` |
| `ncat_checked` | function | `src/url.c:49` | `static int ncat_checked(char *out, size_t outsz, const char *src, size_t n)` |
| `out_pop_segment` | function | `src/url.c:102` | `static void out_pop_segment(char *out, size_t *olen)` |
| `query_find_q` | function | `src/url.c:393` | `static const char *query_find_q(const char *search, size_t len, size_t *vlen)` |
| `url_authority_len` | function | `src/url.c:91` | `size_t url_authority_len(const char *url)` |
| `url_extract_userinfo` | function | `src/url.c:431` | `url_status url_extract_userinfo(const char *url, char *out, size_t outsz,                        ...` |
| `url_file_path` | function | `src/url.c:531` | `const char *url_file_path(const char *s)` |
| `url_has_scheme` | function | `src/url.c:59` | `int url_has_scheme(const char *s)` |
| `url_history_target` | function | `src/url.c:654` | `url_status url_history_target(const char *base, const char *ref, char *out, size_t outsz)` |
| `url_is_file` | function | `src/url.c:525` | `int url_is_file(const char *s)` |
| `url_is_https` | function | `src/url.c:73` | `int url_is_https(const char *s)` |
| `url_omnibox` | function | `src/url.c:309` | `url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz)` |
| `url_remove_dot_segments` | function | `src/url.c:109` | `url_status url_remove_dot_segments(const char *path, char *out, size_t outsz)` |
| `url_resolve_file` | function | `src/url.c:535` | `url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz)` |
| `url_resolve_https` | function | `src/url.c:170` | `url_status url_resolve_https(const char *base, const char *ref,                              char...` |
| `url_search_rewrite` | function | `src/url.c:411` | `url_status url_search_rewrite(const char *url, char *out, size_t outsz)` |
| `url_split` | function | `src/url.c:584` | `url_status url_split(const char *url, url_parts *out)` |
| `url_validate_https` | function | `src/url.c:80` | `url_status url_validate_https(const char *url)` |
| `check` | function | `src/web_storage.c:65` | `static int check(const char *blob, size_t len, size_t *bytes_out)` |
| `find` | function | `src/web_storage.c:118` | `static wst_origin *find(const wst_db *db, const char *origin)` |
| `get_u32` | function | `src/web_storage.c:25` | `static uint32_t get_u32(const unsigned char *p)` |
| `key_cmp` | function | `src/web_storage.c:56` | `static int key_cmp(const void *a, const void *b)` |
| `key_ref` | struct | `src/web_storage.c:54` | `` |
| `put_u32` | function | `src/web_storage.c:201` | `static void put_u32(char *b, uint32_t v)` |
| `utf8_ok` | function | `src/web_storage.c:32` | `static int utf8_ok(const unsigned char *s, size_t n)` |
| `wst_db` | struct | `src/web_storage.c:20` | `` |
| `wst_decode_check` | function | `src/web_storage.c:101` | `int wst_decode_check(const char *blob, size_t len)` |
| `wst_encode` | function | `src/web_storage.c:125` | `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len)` |
| `wst_foreach` | function | `src/web_storage.c:181` | `int wst_foreach(const char *blob, size_t len,                 void (*fn)(void *ctx, const char *k...` |
| `wst_free` | function | `src/web_storage.c:109` | `void wst_free(wst_db *db)` |
| `wst_new` | function | `src/web_storage.c:105` | `wst_db *wst_new(void)` |
| `wst_origin` | struct | `src/web_storage.c:12` | `` |
| `wst_origin_bytes` | function | `src/web_storage.c:175` | `size_t wst_origin_bytes(const wst_db *db, const char *origin)` |

Next: [SYMBOLS_p11.md](SYMBOLS_p11.md)
