# Symbols (page 10 of 16)
Previous: [SYMBOLS_p9.md](SYMBOLS_p9.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `hdr_name_has_prefix` | function | `src/request_policy.c:171` | `static int hdr_name_has_prefix(const char *a, size_t alen, const char *lit)` |
| `hdr_name_ieq` | function | `src/request_policy.c:164` | `static int hdr_name_ieq(const char *a, size_t alen, const char *lit)` |
| `hdr_token_char` | function | `src/request_policy.c:178` | `static int hdr_token_char(unsigned char c)` |
| `lower` | function | `src/request_policy.c:22` | `static char lower(char c)` |
| `psl_cmp` | function | `src/request_policy.c:36` | `static int psl_cmp(const void *key, const void *elem)` |
| `psl_in` | function | `src/request_policy.c:40` | `static int psl_in(const char *const *arr, size_t n, const char *key)` |
| `public_suffix_labels` | function | `src/request_policy.c:48` | `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)` |
| `rp_evaluate` | function | `src/request_policy.c:143` | `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)` |
| `rp_host_of` | function | `src/request_policy.c:76` | `int rp_host_of(const char *url, char *out, size_t out_size)` |
| `rp_same_site` | function | `src/request_policy.c:134` | `int rp_same_site(const char *top_level_url, const char *request_url)` |
| `rp_sanitize_request_headers` | function | `src/request_policy.c:197` | `int rp_sanitize_request_headers(const char *raw, char *out, size_t cap)` |
| `rp_site_of` | function | `src/request_policy.c:102` | `int rp_site_of(const char *host, char *out, size_t out_size)` |
| `SF_RCACHE_SLOTS` | macro | `src/secure_fetch.c:1164` | `#define SF_RCACHE_SLOTS` |
| `SF_RCACHE_TTL_S` | macro | `src/secure_fetch.c:1165` | `#define SF_RCACHE_TTL_S` |
| `_POSIX_C_SOURCE` | macro | `src/secure_fetch.c:12` | `#define _POSIX_C_SOURCE` |
| `add_header` | function | `src/secure_fetch.c:803` | `static int add_header(struct curl_slist **h, const char *line)` |
| `body_sink` | struct | `src/secure_fetch.c:490` | `` |
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
| `EPIPE` | function | `src/tab.c:2006` | `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();` |
| `FB_MAX_FILE_BYTES` | function | `src/tab.c:924` | `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify  * the stream. ...` |
| `PV_MAX_CONTAINERS_WIRE` | macro | `src/tab.c:96` | `#define PV_MAX_CONTAINERS_WIRE` |
| `TAB_MAX_EXTERN_CSS` | macro | `src/tab.c:997` | `#define TAB_MAX_EXTERN_CSS` |
| `TAB_MAX_GEOM_WORDS` | macro | `src/tab.c:123` | `#define TAB_MAX_GEOM_WORDS` |
| `TAB_MAX_HIST_BYTES` | macro | `src/tab.c:117` | `#define TAB_MAX_HIST_BYTES` |
| `TAB_MAX_HIST_OPS` | macro | `src/tab.c:116` | `#define TAB_MAX_HIST_OPS` |
| `TAB_MAX_JS_JOBS` | macro | `src/tab.c:135` | `#define TAB_MAX_JS_JOBS` |
| `TAB_MAX_OPENS` | macro | `src/tab.c:119` | `#define TAB_MAX_OPENS` |
| `TAB_MAX_OPEN_BYTES` | macro | `src/tab.c:120` | `#define TAB_MAX_OPEN_BYTES` |
| `TAB_MAX_RUNS` | macro | `src/tab.c:92` | `#define TAB_MAX_RUNS` |
| `TAB_MAX_STORAGE` | macro | `src/tab.c:112` | `#define TAB_MAX_STORAGE` |
| `TAB_MAX_SUBREQ` | macro | `src/tab.c:133` | `#define TAB_MAX_SUBREQ` |
| `TAB_MAX_SUBRESOURCE` | macro | `src/tab.c:134` | `#define TAB_MAX_SUBRESOURCE` |
| `TAB_MAX_URL` | macro | `src/tab.c:99` | `#define TAB_MAX_URL` |
| `TAB_MAX_WS_MSG` | macro | `src/tab.c:108` | `#define TAB_MAX_WS_MSG` |
| `TAB_SCREEN_H` | macro | `src/tab.c:65` | `#define TAB_SCREEN_H` |
| `TAB_SCREEN_W` | macro | `src/tab.c:64` | `#define TAB_SCREEN_W` |
| `TAB_WIRE_A_N` | macro | `src/tab.c:70` | `#define TAB_WIRE_A_N` |
| `TAB_WIRE_BOX_F_N` | macro | `src/tab.c:72` | `#define TAB_WIRE_BOX_F_N` |
| `TAB_WIRE_B_N` | macro | `src/tab.c:71` | `#define TAB_WIRE_B_N` |
| `TAB_WIRE_GRID_N` | macro | `src/tab.c:73` | `#define TAB_WIRE_GRID_N` |
| `TAB_WIRE_HEAD_N` | macro | `src/tab.c:69` | `#define TAB_WIRE_HEAD_N` |
| `WHERE` | function | `src/tab.c:1448` | `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...` |
| `_GNU_SOURCE` | macro | `src/tab.c:14` | `#define _GNU_SOURCE` |
| `answered` | function | `src/tab.c:3086` | `* A refused frame is still consumed and answered (status 0), so the protocol never  * desyncs. Re...` |
| `blocks` | function | `src/tab.c:492` | `*  * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the  * grid arr...` |
| `budget_remaining_ms` | function | `src/tab.c:954` | `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` |
| `buffer` | function | `src/tab.c:427` | `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...` |
| `child_handle_click` | function | `src/tab.c:1749` | `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_decode_image` | function | `src/tab.c:1950` | `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` |
| `child_handle_decode_image_b64` | function | `src/tab.c:1972` | `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)` |
| `child_handle_eval` | function | `src/tab.c:1909` | `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` |
| `child_handle_event` | function | `src/tab.c:1763` | `static void child_handle_event(int wfd, child_state *cs)` |
| `child_handle_geom` | function | `src/tab.c:1849` | `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` |
| `child_handle_load` | function | `src/tab.c:1177` | `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,            ...` |
| `child_handle_mouse` | function | `src/tab.c:1811` | `static void child_handle_mouse(int wfd, child_state *cs)` |
| `child_handle_mutation` | function | `src/tab.c:1669` | `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,                         ...` |
| `child_handle_submit` | function | `src/tab.c:1875` | `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_tick` | function | `src/tab.c:1753` | `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)` |
| `child_next_timer_ms` | function | `src/tab.c:1654` | `static int32_t child_next_timer_ms(child_state *cs)` |
| `child_reset_page` | function | `src/tab.c:184` | `static void child_reset_page(child_state *cs)` |
| `child_state` | struct | `src/tab.c:146` | `` |
| `clip_pm_ok` | function | `src/tab.c:77` | `static int clip_pm_ok(int32_t v)` |
| `column` | function | `src/tab.c:2539` | `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...` |
| `computed_signature` | function | `src/tab.c:212` | `static uint64_t computed_signature(const dom_index *idx)` |
| `content` | function | `src/tab.c:1508` | `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...` |
| `ctype_is_css` | function | `src/tab.c:977` | `static int ctype_is_css(const char *ctype)` |
| `ctype_is_javascript` | function | `src/tab.c:968` | `static int ctype_is_javascript(const char *ctype)` |
| `depth` | function | `src/tab.c:2036` | `* defense in depth (seccomp already excludes open/socket/exec);` |
| `exec_worker_child` | function | `src/tab.c:2929` | `static void exec_worker_child(int rfd, int wfd)` |
| `fallback` | function | `src/tab.c:1258` | `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it...` |
| `frames` | function | `src/tab.c:3699` | `* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of...` |
| `gate_js_nav` | function | `src/tab.c:3350` | `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` |
| `gen_session_key` | function | `src/tab.c:1984` | `static uint64_t gen_session_key(void)` |
| `geom_parent` | function | `src/tab.c:1841` | `static dom_node_id geom_parent(void *ctx, dom_node_id n)` |
| `geometry_encode` | function | `src/tab.c:4020` | `static int32_t *geometry_encode(const jg_table *g, size_t *words_out)` |
| `hist_ops_free` | function | `src/tab.c:3159` | `static void hist_ops_free(tab_hist_op *ops, size_t n)` |
| `ignore_sigpipe` | function | `src/tab.c:2304` | `static void ignore_sigpipe(void)` |
| `io_failure` | function | `src/tab.c:2921` | `static tab_status io_failure(tab *t)` |
| `is_activation_event` | function | `src/tab.c:3224` | `static int is_activation_event(const char *type)` |
| `job_discard` | function | `src/tab.c:4044` | `static void job_discard(tab *t)` |
| `job_main` | function | `src/tab.c:4066` | `static void *job_main(void *arg)` |
| `job_start` | function | `src/tab.c:4095` | `static tab_status job_start(tab *t)` |
| `layout` | function | `src/tab.c:2528` | `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....` |
| `load` | function | `src/tab.c:2267` | `* subresource requests this load (set per page: host in allow.conf AND js.conf);` |
| `log_external_skip` | function | `src/tab.c:985` | `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,                 ...` |
| `once` | function | `src/tab.c:1557` | `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);` |
| `open_urls_free` | function | `src/tab.c:3233` | `static void open_urls_free(char **u, size_t n)` |
| `parse_worker_fd` | function | `src/tab.c:2228` | `static int parse_worker_fd(const char *s, int *out)` |
| `policy` | function | `src/tab.c:292` | `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a  * compromi...` |
| `prof_lap` | function | `src/tab.c:368` | `static void prof_lap(const char *what, double *t0)` |
| `prof_now_ms` | function | `src/tab.c:358` | `static double prof_now_ms(void)` |
| `prof_on` | function | `src/tab.c:363` | `static int prof_on(void)` |
| `rad_len_ok` | function | `src/tab.c:83` | `static int rad_len_ok(int32_t v, int dflt)` |
| `read_console` | function | `src/tab.c:2874` | `static int read_console(int fd, fb_buffer *out)` |
| `read_field` | function | `src/tab.c:2330` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `read_opens` | function | `src/tab.c:3243` | `static tab_status read_opens(tab *t, const char *page_url, int gesture,                          ...` |
| `read_view` | function | `src/tab.c:2346` | `static int read_view(int fd, pv_view **out)` |
| `read_ws` | function | `src/tab.c:3281` | `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` |
| `run` | function | `src/tab.c:1003` | `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).  * Call after every ...` |
| `run_js` | function | `src/tab.c:379` | `* regardless of run_js (a no-JS load simply never records a request). */ static int child_load(ch...` |
| `send_request` | function | `src/tab.c:2911` | `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` |
| `sig_mix` | function | `src/tab.c:204` | `static uint64_t sig_mix(uint64_t h, const char *s, size_t n)` |
| `swap` | function | `src/tab.c:1566` | `* display:none hiding an element via class swap (CSS, not      * DOM removal). */     if (ok && v...` |
| `tab` | struct | `src/tab.c:2260` | `` |
| `tab_alive` | function | `src/tab.c:3924` | `int tab_alive(const tab *t)` |
| `tab_async_busy` | function | `src/tab.c:4091` | `int tab_async_busy(const tab *t)` |
| `tab_async_fd` | function | `src/tab.c:4082` | `int tab_async_fd(tab *t)` |
| `tab_async_finish` | function | `src/tab.c:4133` | `tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)` |
| `tab_async_sync` | function | `src/tab.c:4056` | `static void tab_async_sync(tab *t)` |
| `tab_await_result` | function | `src/tab.c:3702` | `static tab_status tab_await_result(tab *t)` |
| `tab_await_result_inner` | function | `src/tab.c:3710` | `static tab_status tab_await_result_inner(tab *t)` |
| `tab_child_pid` | function | `src/tab.c:3930` | `pid_t tab_child_pid(const tab *t)` |
| `tab_click` | function | `src/tab.c:3567` | `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)` |
| `tab_close` | function | `src/tab.c:3934` | `void tab_close(tab *t)` |
| `tab_decode_image` | function | `src/tab.c:3898` | `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)` |
| `tab_decode_image_data_url` | function | `src/tab.c:3905` | `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)` |
| `tab_decode_image_op` | function | `src/tab.c:3856` | `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,         ...` |
| `tab_eval` | function | `src/tab.c:3815` | `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)` |
| `tab_eval_result_free` | function | `src/tab.c:3981` | `void tab_eval_result_free(tab_eval_result *r)` |
| `tab_geometry_async` | function | `src/tab.c:4118` | `tab_status tab_geometry_async(tab *t, const jg_table *g)` |
| `tab_geometry_send` | function | `src/tab.c:4002` | `static tab_status tab_geometry_send(tab *t, const int32_t *buf, size_t words)` |
| `tab_image_free` | function | `src/tab.c:3990` | `void tab_image_free(tab_image *img)` |
| `tab_inflight_request_headers` | function | `src/tab.c:3077` | `const char *tab_inflight_request_headers(void)` |
| `tab_last_subreq_stats` | function | `src/tab.c:3027` | `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)` |
| `tab_load` | function | `src/tab.c:3360` | `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)` |
| `tab_load_ex` | function | `src/tab.c:3364` | `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)` |
| `tab_load_full` | function | `src/tab.c:3368` | `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,             ...` |
| `tab_mod_fetch` | function | `src/tab.c:1091` | `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` |
| `tab_mod_resolve` | function | `src/tab.c:1061` | `static int tab_mod_resolve(void *host, const char *base, const char *spec,                       ...` |
| `tab_page_free` | function | `src/tab.c:3951` | `void tab_page_free(tab_page *p)` |
| `tab_parse_worker_args` | function | `src/tab.c:2240` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)` |
| `tab_popstate` | function | `src/tab.c:4155` | `tab_status tab_popstate(tab *t, int index, tab_page *out)` |
| `tab_read_view` | function | `src/tab.c:3693` | `tab_status tab_read_view(tab *t, tab_page *out)` |
| `tab_read_view_ex` | function | `src/tab.c:3720` | `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)` |
| `tab_refresh_alive` | function | `src/tab.c:2311` | `static void tab_refresh_alive(tab *t)` |
| `tab_report_response_headers` | function | `src/tab.c:3065` | `void tab_report_response_headers(const char *lines)` |
| `tab_set_cookies` | function | `src/tab.c:3045` | `void tab_set_cookies(tab *t, const char *cookies)` |
| `tab_set_css_allowed` | function | `src/tab.c:3022` | `void tab_set_css_allowed(tab *t, int allowed)` |
| `tab_set_css_sink` | function | `src/tab.c:3007` | `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)` |
| `tab_set_fetcher` | function | `src/tab.c:3001` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)` |
| `tab_set_geometry` | function | `src/tab.c:4030` | `tab_status tab_set_geometry(tab *t, const jg_table *g)` |
| `tab_set_identity` | function | `src/tab.c:3032` | `void tab_set_identity(tab *t, const char *serialized)` |
| `tab_set_net_allowed` | function | `src/tab.c:3017` | `void tab_set_net_allowed(tab *t, int allowed)` |
| `tab_set_op_net_budget_ms` | function | `src/tab.c:3013` | `void tab_set_op_net_budget_ms(tab *t, int ms)` |
| `tab_set_storage` | function | `src/tab.c:4182` | `void tab_set_storage(tab *t, const char *blob, size_t len)` |
| `tab_set_viewport_w` | function | `src/tab.c:3040` | `void tab_set_viewport_w(tab *t, int px)` |
| `tab_submit` | function | `src/tab.c:3585` | `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` |
| `tab_subreq_permitted` | function | `src/tab.c:3051` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)` |
| `tab_tick` | function | `src/tab.c:3575` | `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)` |
| `tab_tick_async` | function | `src/tab.c:4108` | `tab_status tab_tick_async(tab *t, int elapsed_ms)` |
| `tab_url_resolve` | function | `src/tab.c:1052` | `static int tab_url_resolve(void *ctx, const char *base, const char *ref,                         ...` |
| `tab_worker_dispatch` | function | `src/tab.c:2250` | `void tab_worker_dispatch(int argc, char **argv)` |
| `tab_worker_run` | function | `src/tab.c:2004` | `static void tab_worker_run(int rfd, int wfd)` |
| `tab_ws_event` | function | `src/tab.c:4162` | `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,        ...` |
| `tests` | function | `src/tab.c:2421` | `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...` |
| `tzset` | function | `src/tab.c:2022` | `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);` |
| `window` | function | `src/tab.c:1132` | `* net window (cs->net_active). */ static void child_fetch_stylesheets(child_state *cs)` |
| `write_field` | function | `src/tab.c:458` | `static int write_field(int fd, const char *s)` |
| `write_full` | function | `src/tab.c:1587` | `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 \|\| write_full(wfd, text, xl) == 0) && write_view(wfd...` |
| `write_history` | function | `src/tab.c:1113` | `static int write_history(int wfd, child_state *cs)` |
| `write_opens` | function | `src/tab.c:1642` | `static int write_opens(int wfd, child_state *cs)` |
| `write_storage` | function | `src/tab.c:1628` | `static int write_storage(int wfd, child_state *cs)` |
| `write_ws` | function | `src/tab.c:1611` | `static int write_ws(int wfd, child_state *cs)` |
| `ws_ops_free` | function | `src/tab.c:3272` | `static void ws_ops_free(tab_ws_op *ops, size_t n)` |
| `pair_parity` | function | `src/text_case.c:8` | `static int pair_parity(uint32_t cp)` |
| `tc_is_lower` | function | `src/text_case.c:54` | `int tc_is_lower(uint32_t cp)` |
| `tc_lower` | function | `src/text_case.c:37` | `uint32_t tc_lower(uint32_t cp)` |
| `tc_smallcaps_runs` | function | `src/text_case.c:117` | `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap)` |
| `tc_transform` | function | `src/text_case.c:95` | `size_t tc_transform(const char *s, size_t n, int transform, int word_start,                     c...` |
| `tc_upper` | function | `src/text_case.c:18` | `uint32_t tc_upper(uint32_t cp)` |
| `utf8_decode` | function | `src/text_case.c:61` | `static size_t utf8_decode(const unsigned char *s, size_t n, uint32_t *cp)` |
| `utf8_len_of` | function | `src/text_case.c:91` | `static size_t utf8_len_of(uint32_t cp)` |
| `utf8_put` | function | `src/text_case.c:79` | `static void utf8_put(uint32_t cp, size_t len, unsigned char *out)` |
| `TSH_BLANK_GLYPH` | macro | `src/text_shape.c:613` | `#define TSH_BLANK_GLYPH` |
| `TSH_CACHE_SLOTS` | macro | `src/text_shape.c:33` | `#define TSH_CACHE_SLOTS` |
| `TSH_FB_BLOCKS` | macro | `src/text_shape.c:656` | `#define TSH_FB_BLOCKS` |
| `TSH_FB_SLOTS` | macro | `src/text_shape.c:655` | `#define TSH_FB_SLOTS` |
| `TSH_MAX_FONT_BYTES` | macro | `src/text_shape.c:29` | `#define TSH_MAX_FONT_BYTES` |
| `TSH_MAX_RUNS` | macro | `src/text_shape.c:796` | `#define TSH_MAX_RUNS` |
| `TSH_SUBS_MAX` | macro | `src/text_shape.c:400` | `#define TSH_SUBS_MAX` |
| `TSH_WEB_SLOTS` | macro | `src/text_shape.c:189` | `#define TSH_WEB_SLOTS` |
| `_POSIX_C_SOURCE` | macro | `src/text_shape.c:12` | `#define _POSIX_C_SOURCE` |
| `ascii_ieq` | function | `src/text_shape.c:331` | `static int ascii_ieq(const char *a, const char *b)` |
| `backend_init` | function | `src/text_shape.c:65` | `static int backend_init(void)` |
| `characters` | function | `src/text_shape.c:100` | `* hold characters ('-', ':') that the pattern syntax treats specially. */ static int load_entry_file(tsh_entry *e...` |
| `cover_cp` | function | `src/text_shape.c:750` | `static int cover_cp(unsigned cp, void *vctx)` |
| `entry_free` | function | `src/text_shape.c:318` | `static void entry_free(tsh_entry *e)` |
| `fb_clear` | function | `src/text_shape.c:669` | `static void fb_clear(void)` |
| `fb_entry` | function | `src/text_shape.c:679` | `static tsh_entry *fb_entry(unsigned cp, int bold)` |
| `fc_installed` | function | `src/text_shape.c:386` | `static int fc_installed(const char *name, void *ctx)` |
| `fc_resolve` | function | `src/text_shape.c:429` | `static int fc_resolve(const char *name, char *out, size_t cap, void *ctx)` |
| `file` | type_alias | `src/text_shape.c:657` | `typedef struct tsh_fb { char file[512];` |
| `generic_name` | function | `src/text_shape.c:55` | `static const char *generic_name(int family)` |
| `get_entry` | function | `src/text_shape.c:173` | `static tsh_entry *get_entry(int family, int bold, int italic)` |
| `get_entry_ex` | function | `src/text_shape.c:531` | `static tsh_entry *get_entry_ex(const tsh_font *f)` |
| `is_private_use` | function | `src/text_shape.c:616` | `static int is_private_use(unsigned cp)` |
| `lfam_index` | function | `src/text_shape.c:484` | `static int lfam_index(const char *fam)` |
| `load_entry` | function | `src/text_shape.c:169` | `static int load_entry(tsh_entry *e, int family, int bold, int italic)` |
| `load_entry_file` | function | `src/text_shape.c:133` | `static int load_entry_file(tsh_entry *e, const char *path, int index)` |
| `load_entry_named` | function | `src/text_shape.c:103` | `static int load_entry_named(tsh_entry *e, const char *fam, int bold, int italic)` |
| `loaded` | type_alias | `src/text_shape.c:34` | `typedef struct tsh_entry { int loaded;` |
| `local_clear` | function | `src/text_shape.c:474` | `static void local_clear(void)` |
| `local_entry` | function | `src/text_shape.c:511` | `static tsh_entry *local_entry(int handle, int bold, int italic)` |
| `name` | type_alias | `src/text_shape.c:457` | `typedef struct tsh_lfam { char name[TSH_FAMILY_MAX];` |
| `read_font_file` | function | `src/text_shape.c:82` | `static unsigned char *read_font_file(const char *path, long *out_n)` |
| `rides_previous` | function | `src/text_shape.c:621` | `static int rides_previous(unsigned cp)` |
| `shape_entry` | function | `src/text_shape.c:764` | `static tsh_status shape_entry(tsh_entry *e, double px, const char *text, size_t len,             ...` |
| `shape_runs` | function | `src/text_shape.c:800` | `static tsh_status shape_runs(cairo_t *cr, const tsh_font *f, double px, double x,                ...` |
| `slice` | function | `src/text_shape.c:213` | `* woff2 slice (spec/webfont.md);` |
| `tsh_cover_ctx` | struct | `src/text_shape.c:741` | `` |
| `tsh_draw` | function | `src/text_shape.c:852` | `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,                     double x, doub...` |
| `tsh_entry` | struct | `src/text_shape.c:35` | `` |
| `tsh_face` | function | `src/text_shape.c:859` | `cairo_font_face_t *tsh_face(const tsh_font *f)` |
| `tsh_family_is_generic` | function | `src/text_shape.c:340` | `int tsh_family_is_generic(const char *name)` |
| `tsh_fb` | struct | `src/text_shape.c:658` | `` |
| `tsh_lfam` | struct | `src/text_shape.c:458` | `` |
| `tsh_llist` | struct | `src/text_shape.c:464` | `` |
| `tsh_local_handle` | function | `src/text_shape.c:492` | `int tsh_local_handle(const char *list)` |
| `tsh_measure` | function | `src/text_shape.c:846` | `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)` |
| `tsh_pick_family` | function | `src/text_shape.c:373` | `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong,         ...` |
| `tsh_pick_from_list` | function | `src/text_shape.c:352` | `int tsh_pick_from_list(const char *list, tsh_name_resolver resolve, void *ctx,                   ...` |
| `tsh_ready` | function | `src/text_shape.c:543` | `int tsh_ready(void)` |
| `tsh_segment` | function | `src/text_shape.c:629` | `int tsh_segment(const char *text, size_t len, tsh_cover_fn cover, void *ctx,                 tsh_...` |
| `tsh_shape` | function | `src/text_shape.c:548` | `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,                 ...` |
| `tsh_shutdown` | function | `src/text_shape.c:865` | `void tsh_shutdown(void)` |
| `tsh_web` | struct | `src/text_shape.c:191` | `` |
| `tsh_webfont_clear` | function | `src/text_shape.c:301` | `void tsh_webfont_clear(void)` |
| `tsh_webfont_register` | function | `src/text_shape.c:267` | `int tsh_webfont_register(const char *name,                          const unsigned char *bytes, s...` |
| `used` | type_alias | `src/text_shape.c:190` | `typedef struct tsh_web { int used;` |
| `utf8_next` | function | `src/text_shape.c:597` | `static unsigned utf8_next(const char *s, size_t n, size_t *len)` |
| `web_entry_free` | function | `src/text_shape.c:201` | `static void web_entry_free(tsh_web *w)` |
| `web_find` | function | `src/text_shape.c:306` | `static tsh_entry *web_find(unsigned h, int bold, int italic)` |
| `web_magic_ok` | function | `src/text_shape.c:214` | `static int web_magic_ok(const unsigned char *b, size_t n)` |
| `web_make_entry` | function | `src/text_shape.c:227` | `static int web_make_entry(tsh_entry *e, const unsigned char *bytes, size_t nbytes)` |
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
| `wst_pack` | function | `src/web_storage.c:206` | `int wst_pack(const char *const *keys, const size_t *klens,              const char *const *vals, ...` |
| `wst_replace` | function | `src/web_storage.c:140` | `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len)` |
| `wc_derive` | function | `src/webcaps.c:15` | `wc_caps wc_derive(wc_input in)` |
| `wc_from_flags` | function | `src/webcaps.c:35` | `wc_caps wc_from_flags(bool js, bool css, bool images)` |
| `wc_render_caps` | function | `src/webcaps.c:46` | `rdp_caps wc_render_caps(wc_caps c)` |
| `wc_safe` | function | `src/webcaps.c:10` | `wc_caps wc_safe(void)` |
| `candidates` | function | `src/webfont.c:7` | `* understanding just far enough to find candidates (family + first url() per * src entry + weight/style descriptors);` |
| `ci_eq_span` | function | `src/webfont.c:28` | `static int ci_eq_span(const char *s, size_t n, const char *kw)` |
| `emit` | function | `src/webfont.c:126` | `static void emit(wf_list *out, const char *family,                  const char *url, size_t ulen,...` |
| `emit_data` | function | `src/webfont.c:142` | `static void emit_data(wf_list *out, const char *family,                       const char *span, s...` |
| `emit_family_format` | function | `src/webfont.c:98` | `static void emit_family_format(wf_ref *r, const char *family, const char *format)` |
| `emit_slot` | function | `src/webfont.c:83` | `static wf_ref *emit_slot(wf_list *out)` |
| `is_ws` | function | `src/webfont.c:19` | `static int is_ws(char c)` |
| `lower_ch` | function | `src/webfont.c:23` | `static int lower_ch(char c)` |
| `lower_ch` | function | `src/webfont.c:306` | `&& lower_ch(s[k]) == 's' && k + 3 < bend                 && lower_ch(s[k + 1]) == 'r' && lower_ch...` |
| `scan_face_block` | function | `src/webfont.c:179` | `static void scan_face_block(const char *s, size_t bstart, size_t bend,                           ...` |
| `span_is_data` | function | `src/webfont.c:114` | `static int span_is_data(const char *span, size_t slen)` |
| `wf_list_free` | function | `src/webfont.c:49` | `void wf_list_free(wf_list *l)` |
| `wf_ref_move` | function | `src/webfont.c:64` | `void wf_ref_move(wf_ref *dst, wf_ref *src)` |
| `wf_scan` | function | `src/webfont.c:422` | `int wf_scan(const char *css, size_t len, wf_list *out)` |
| `wf_supported_format` | function | `src/webfont.c:74` | `int wf_supported_format(const char *fmt)` |
| `WF_DATA_URL_MAX` | macro | `src/webfont_load.c:91` | `#define WF_DATA_URL_MAX` |
| `ctype_ok` | function | `src/webfont_load.c:24` | `static int ctype_ok(const char *ct)` |
| `fetch` | type_alias | `src/webfont_load.c:56` | `typedef struct wf_cursor { wf_fetch_fn fetch;` |
| `hash` | type_alias | `src/webfont_load.c:46` | `typedef struct wf_key { unsigned hash;` |
| `here` | function | `src/webfont_load.c:22` | `* filtered here (a "" hint may still name one);` |
| `key_find` | function | `src/webfont_load.c:66` | `static int key_find(wf_key *keys, size_t nkeys, unsigned h, int b, int i)` |
| `ref` | function | `src/webfont_load.c:167` | `* their ref (the register call copies what it keeps). */ if (!is_data) free(fbytes);` |
| `scan_inline` | function | `src/webfont_load.c:178` | `static void scan_inline(const char *html, size_t len, const char *page_url,                      ...` |
| `wf_cursor` | struct | `src/webfont_load.c:56` | `` |
| `wf_key` | struct | `src/webfont_load.c:46` | `` |
| `wf_load_document` | function | `src/webfont_load.c:229` | `int wf_load_document(wf_fetch_fn fetch, void *fctx, const char *page_url,                      co...` |
| `WD_MAX_NAMES` | macro | `src/wl_display.c:10` | `#define WD_MAX_NAMES` |
| `WD_NAME_MAX` | macro | `src/wl_display.c:11` | `#define WD_NAME_MAX` |
| `WD_PREFIX` | macro | `src/wl_display.c:8` | `#define WD_PREFIX` |
| `WD_PREFIX_LEN` | macro | `src/wl_display.c:9` | `#define WD_PREFIX_LEN` |
| `_POSIX_C_SOURCE` | macro | `src/wl_display.c:1` | `#define _POSIX_C_SOURCE` |
| `wd_index` | function | `src/wl_display.c:13` | `static int wd_index(const char *name, unsigned long *idx)` |
| `wd_pick` | function | `src/wl_display.c:27` | `int wd_pick(const char *const *names, size_t n, char *out, size_t cap)` |
| `wd_resolve_env` | function | `src/wl_display.c:42` | `int wd_resolve_env(void)` |
| `WLG_POLL_MS` | macro | `src/wl_guard.c:17` | `#define WLG_POLL_MS` |
| `_DEFAULT_SOURCE` | macro | `src/wl_guard.c:5` | `#define _DEFAULT_SOURCE` |
| `guard_main` | function | `src/wl_guard.c:26` | `static void *guard_main(void *arg)` |
| `wl_guard` | struct | `src/wl_guard.c:19` | `` |
| `wlg_start` | function | `src/wl_guard.c:45` | `wl_guard *wlg_start(struct wl_display *display)` |
| `wlg_stop` | function | `src/wl_guard.c:61` | `void wlg_stop(wl_guard *g)` |
| `WH_READS_PER_PUMP` | macro | `src/ws_hub.c:21` | `#define WH_READS_PER_PUMP` |
| `WH_RECV_CHUNK` | macro | `src/ws_hub.c:22` | `#define WH_RECV_CHUNK` |
| `_POSIX_C_SOURCE` | macro | `src/ws_hub.c:6` | `#define _POSIX_C_SOURCE` |
| `conn_clear` | function | `src/ws_hub.c:98` | `static void conn_clear(wh_conn *c)` |
| `dup_str` | function | `src/ws_hub.c:54` | `static char *dup_str(const char *s)` |
| `fail_conn` | function | `src/ws_hub.c:258` | `static void fail_conn(wh_conn *c, int id, wh_emit_fn emit, void *ctx)` |
| `find_id` | function | `src/ws_hub.c:104` | `static wh_conn *find_id(wh_hub *h, int id)` |
| `find_token` | function | `src/ws_hub.c:110` | `static wh_conn *find_token(wh_hub *h, uint64_t token)` |
| `job_free` | function | `src/ws_hub.c:63` | `static void job_free(wh_job *j)` |
| `job_str` | function | `src/ws_hub.c:71` | `static int job_str(wh_job *j, size_t slot, const char **field)` |
| `open_thread` | function | `src/ws_hub.c:79` | `static void *open_thread(void *arg)` |
| `used` | type_alias | `src/ws_hub.c:23` | `typedef struct wh_conn { int used;` |
| `wfd` | type_alias | `src/ws_hub.c:43` | `typedef struct wh_job { int wfd;` |
| `wh_close` | function | `src/ws_hub.c:228` | `void wh_close(wh_hub *h, int id)` |
| `wh_close_all` | function | `src/ws_hub.c:234` | `void wh_close_all(wh_hub *h)` |
| `wh_conn` | struct | `src/ws_hub.c:24` | `` |
| `wh_count` | function | `src/ws_hub.c:314` | `size_t wh_count(const wh_hub *h)` |
| `wh_free` | function | `src/ws_hub.c:129` | `void wh_free(wh_hub *h)` |
| `wh_hub` | struct | `src/ws_hub.c:35` | `` |
| `wh_job` | struct | `src/ws_hub.c:43` | `` |
| `wh_new` | function | `src/ws_hub.c:116` | `wh_hub *wh_new(void)` |
| `wh_notify_fd` | function | `src/ws_hub.c:144` | `int wh_notify_fd(const wh_hub *h)` |
| `wh_on_notify` | function | `src/ws_hub.c:192` | `void wh_on_notify(wh_hub *h, wh_emit_fn emit, void *ctx)` |
| `wh_on_readable` | function | `src/ws_hub.c:266` | `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx)` |
| `wh_open_async` | function | `src/ws_hub.c:148` | `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg)` |
| `wh_poll_fds` | function | `src/ws_hub.c:240` | `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap)` |

Next: [SYMBOLS_p11.md](SYMBOLS_p11.md)
