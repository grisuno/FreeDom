# Symbols (page 9 of 14)
Previous: [SYMBOLS_p8.md](SYMBOLS_p8.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `sf_check_tls_version` | function | `src/secure_fetch.c:270` | `sf_status sf_check_tls_version(const char *negotiated_version)` |
| `sf_ci_prefix` | function | `src/secure_fetch.c:371` | `static int sf_ci_prefix(const char *s, const char *p)` |
| `sf_config_default` | function | `src/secure_fetch.c:216` | `sf_config sf_config_default(void)` |
| `sf_cookie_header_for` | function | `src/secure_fetch.c:166` | `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)` |
| `sf_cookie_line_matches` | function | `src/secure_fetch.c:96` | `int sf_cookie_line_matches(const char *line, const char *host, const char *path,                 ...` |
| `sf_cookie_put` | function | `src/secure_fetch.c:195` | `void sf_cookie_put(const char *url, const char *namevalue)` |
| `sf_enforce_policy` | function | `src/secure_fetch.c:294` | `sf_status sf_enforce_policy(const char *tls_version, const char *group,                          ...` |
| `sf_get` | function | `src/secure_fetch.c:1014` | `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)` |
| `sf_get_follow` | function | `src/secure_fetch.c:1032` | `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,                 ...` |
| `sf_global_init` | function | `src/secure_fetch.c:81` | `void sf_global_init(void)` |
| `sf_impersonate_kex_groups` | function | `src/secure_fetch.c:245` | `const char *sf_impersonate_kex_groups(void)` |
| `sf_impersonate_tls13_ciphers` | function | `src/secure_fetch.c:246` | `const char *sf_impersonate_tls13_ciphers(void)` |
| `sf_is_redirect_code` | function | `src/secure_fetch.c:334` | `int sf_is_redirect_code(long http_code)` |
| `sf_parse_location_header` | function | `src/secure_fetch.c:341` | `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)` |
| `sf_perform` | function | `src/secure_fetch.c:879` | `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,             ...` |
| `sf_post` | function | `src/secure_fetch.c:1018` | `sf_status sf_post(const char *url, const sf_config *cfg,                   const void *body, size...` |
| `sf_resolve_redirect` | function | `src/secure_fetch.c:359` | `sf_status sf_resolve_redirect(const char *base_url, const char *location,                        ...` |
| `sf_response_free` | function | `src/secure_fetch.c:411` | `void sf_response_free(sf_response *resp)` |
| `sf_setup_handle` | function | `src/secure_fetch.c:736` | `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,            ...` |
| `sf_share_lock` | function | `src/secure_fetch.c:68` | `static void sf_share_lock(CURL *handle, curl_lock_data data,                           curl_lock_...` |
| `sf_share_unlock` | function | `src/secure_fetch.c:74` | `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)` |
| `sf_url_host_path` | function | `src/secure_fetch.c:151` | `static int sf_url_host_path(const char *url, char *host, size_t hostsz,                          ...` |
| `sf_url_is_http` | function | `src/secure_fetch.c:258` | `static int sf_url_is_http(const char *url)` |
| `sf_user_agent_or_default` | function | `src/secure_fetch.c:241` | `const char *sf_user_agent_or_default(const char *ua)` |
| `sf_validate_url` | function | `src/secure_fetch.c:250` | `sf_status sf_validate_url(const char *url)` |
| `sf_ws` | struct | `src/secure_fetch.c:1098` | `` |
| `sf_ws_close` | function | `src/secure_fetch.c:1233` | `void sf_ws_close(sf_ws *ws)` |
| `sf_ws_fd` | function | `src/secure_fetch.c:1226` | `int sf_ws_fd(const sf_ws *ws)` |
| `sf_ws_open` | function | `src/secure_fetch.c:1126` | `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)` |
| `sf_ws_recv` | function | `src/secure_fetch.c:1204` | `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)` |
| `sf_ws_send` | function | `src/secure_fetch.c:1181` | `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)` |
| `sf_ws_url_check` | function | `src/secure_fetch.c:1105` | `sf_status sf_ws_url_check(const char *url)` |
| `sink` | type_alias | `src/secure_fetch.c:456` | `typedef struct fetch_ctx { body_sink sink;` |
| `this` | function | `src/secure_fetch.c:531` | `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and...` |
| `tls_capture` | struct | `src/secure_fetch.c:447` | `` |
| `tls_capture_from_ssl` | function | `src/secure_fetch.c:524` | `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)` |
| `tls_capture_try` | function | `src/secure_fetch.c:514` | `static void tls_capture_try(tls_capture *cap)` |
| `write_cb` | function | `src/secure_fetch.c:586` | `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)` |
| `ws_free` | function | `src/secure_fetch.c:1117` | `static void ws_free(sf_ws *ws)` |
| `ws_ssl_ctx_cb` | function | `src/secure_fetch.c:1091` | `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)` |
| `ws_ssl_info_cb` | function | `src/secure_fetch.c:1084` | `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)` |
| `SV_MAX_ATTRS` | macro | `src/svg_render.c:96` | `#define SV_MAX_ATTRS` |
| `point` | function | `src/svg_render.c:556` | `* current point (SVG 8.3.6). */ int had = (prev == 'C' \|\| prev == 'c' \|\| prev == 'S' \|\| prev == 's');` |
| `stroke` | type_alias | `src/svg_render.c:151` | `typedef struct sv_ctx { int fill, stroke;` |
| `sv_apply_prop` | function | `src/svg_render.c:260` | `static void sv_apply_prop(sv_ctx *ctx, const char *nm, size_t nl,                           const...` |
| `sv_arc_to_cubics` | function | `src/svg_render.c:399` | `static int sv_arc_to_cubics(sv_image *im, sv_shape *sh,                             double x0, do...` |
| `sv_attr` | struct | `src/svg_render.c:91` | `` |
| `sv_attr_get` | function | `src/svg_render.c:99` | `static const char *sv_attr_get(const sv_attr *at, size_t nat, const char *name, size_t *len)` |
| `sv_attr_num` | function | `src/svg_render.c:108` | `static double sv_attr_num(const sv_attr *at, size_t nat, const char *name, double dflt)` |
| `sv_collect_text` | function | `src/svg_render.c:725` | `static void sv_collect_text(const char *s, size_t n, size_t *i, char *dst, size_t cap)` |
| `sv_ctx` | struct | `src/svg_render.c:151` | `` |
| `sv_ctx_from_attrs` | function | `src/svg_render.c:307` | `static void sv_ctx_from_attrs(sv_ctx *ctx, const sv_attr *at, size_t nat)` |
| `sv_fit` | function | `src/svg_render.c:743` | `void sv_fit(const sv_image *img, double dw, double dh,             double *scale, double *off_x, ...` |
| `sv_is_digit` | function | `src/svg_render.c:25` | `static int sv_is_digit(char c)` |
| `sv_is_dropped_element` | function | `src/svg_render.c:635` | `static int sv_is_dropped_element(const char *name, size_t n)` |
| `sv_is_space` | function | `src/svg_render.c:21` | `static int sv_is_space(char c)` |
| `sv_lower` | function | `src/svg_render.c:27` | `static char sv_lower(char c)` |
| `sv_mat_identity` | function | `src/svg_render.c:161` | `static void sv_mat_identity(double *m)` |
| `sv_mat_mul` | function | `src/svg_render.c:166` | `static void sv_mat_mul(const double *a, const double *b, double *out)` |
| `sv_new_seg` | function | `src/svg_render.c:363` | `static sv_seg *sv_new_seg(sv_image *im, sv_shape *sh)` |
| `sv_new_shape` | function | `src/svg_render.c:324` | `static sv_shape *sv_new_shape(sv_image *im, int kind, const sv_ctx *ctx)` |
| `sv_parse` | function | `src/svg_render.c:763` | `sv_status sv_parse(const char *markup, size_t len, sv_image *out)` |
| `sv_parse_ex` | function | `src/svg_render.c:767` | `sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill)` |
| `sv_parse_path` | function | `src/svg_render.c:477` | `static void sv_parse_path(sv_image *im, sv_shape *sh, const char *s, size_t n)` |
| `sv_parse_points` | function | `src/svg_render.c:343` | `static void sv_parse_points(sv_image *im, sv_shape *sh, const char *s, size_t n)` |
| `sv_parse_transform` | function | `src/svg_render.c:179` | `static void sv_parse_transform(const char *s, size_t n, double *m)` |
| `sv_scan_attrs` | function | `src/svg_render.c:647` | `static void sv_scan_attrs(const char *s, size_t n, size_t *i,                           sv_attr *...` |
| `sv_seg_cubic` | function | `src/svg_render.c:385` | `static int sv_seg_cubic(sv_image *im, sv_shape *sh,                         double x1, double y1,...` |
| `sv_seg_line` | function | `src/svg_render.c:378` | `static int sv_seg_line(sv_image *im, sv_shape *sh, double x, double y)` |
| `sv_seg_move` | function | `src/svg_render.c:371` | `static int sv_seg_move(sv_image *im, sv_shape *sh, double x, double y)` |
| `sv_sep` | function | `src/svg_render.c:82` | `static void sv_sep(const char *s, size_t n, size_t *i)` |
| `sv_skip_subtree` | function | `src/svg_render.c:693` | `static void sv_skip_subtree(const char *s, size_t n, size_t *i, const char *name, size_t nlen)` |
| `sv_span_eq` | function | `src/svg_render.c:32` | `static int sv_span_eq(const char *s, size_t n, const char *lit)` |
| `sv_style_next` | function | `src/svg_render.c:238` | `static int sv_style_next(const char *s, size_t n, size_t *i,                          const char ...` |
| `EPIPE` | function | `src/tab.c:1738` | `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();` |
| `FB_MAX_FILE_BYTES` | function | `src/tab.c:746` | `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify  * the stream. ...` |
| `PV_MAX_CONTAINERS_WIRE` | macro | `src/tab.c:75` | `#define PV_MAX_CONTAINERS_WIRE` |
| `TAB_MAX_EXTERN_CSS` | macro | `src/tab.c:819` | `#define TAB_MAX_EXTERN_CSS` |
| `TAB_MAX_GEOM_WORDS` | macro | `src/tab.c:102` | `#define TAB_MAX_GEOM_WORDS` |
| `TAB_MAX_HIST_BYTES` | macro | `src/tab.c:96` | `#define TAB_MAX_HIST_BYTES` |
| `TAB_MAX_HIST_OPS` | macro | `src/tab.c:95` | `#define TAB_MAX_HIST_OPS` |
| `TAB_MAX_JS_JOBS` | macro | `src/tab.c:114` | `#define TAB_MAX_JS_JOBS` |
| `TAB_MAX_OPENS` | macro | `src/tab.c:98` | `#define TAB_MAX_OPENS` |
| `TAB_MAX_OPEN_BYTES` | macro | `src/tab.c:99` | `#define TAB_MAX_OPEN_BYTES` |
| `TAB_MAX_RUNS` | macro | `src/tab.c:71` | `#define TAB_MAX_RUNS` |
| `TAB_MAX_STORAGE` | macro | `src/tab.c:91` | `#define TAB_MAX_STORAGE` |
| `TAB_MAX_SUBREQ` | macro | `src/tab.c:112` | `#define TAB_MAX_SUBREQ` |
| `TAB_MAX_SUBRESOURCE` | macro | `src/tab.c:113` | `#define TAB_MAX_SUBRESOURCE` |
| `TAB_MAX_URL` | macro | `src/tab.c:78` | `#define TAB_MAX_URL` |
| `TAB_MAX_WS_MSG` | macro | `src/tab.c:87` | `#define TAB_MAX_WS_MSG` |
| `TAB_SCREEN_H` | macro | `src/tab.c:59` | `#define TAB_SCREEN_H` |
| `TAB_SCREEN_W` | macro | `src/tab.c:58` | `#define TAB_SCREEN_W` |
| `TAB_WIRE_A_N` | macro | `src/tab.c:64` | `#define TAB_WIRE_A_N` |
| `TAB_WIRE_BOX_F_N` | macro | `src/tab.c:66` | `#define TAB_WIRE_BOX_F_N` |
| `TAB_WIRE_B_N` | macro | `src/tab.c:65` | `#define TAB_WIRE_B_N` |
| `TAB_WIRE_GRID_N` | macro | `src/tab.c:67` | `#define TAB_WIRE_GRID_N` |
| `TAB_WIRE_HEAD_N` | macro | `src/tab.c:63` | `#define TAB_WIRE_HEAD_N` |
| `WHERE` | function | `src/tab.c:1225` | `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...` |
| `_GNU_SOURCE` | macro | `src/tab.c:14` | `#define _GNU_SOURCE` |
| `answered` | function | `src/tab.c:2718` | `* A refused frame is still consumed and answered (status 0), so the protocol never  * desyncs. Re...` |
| `blocks` | function | `src/tab.c:331` | `*  * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the  * grid arr...` |
| `budget_remaining_ms` | function | `src/tab.c:776` | `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` |
| `buffer` | function | `src/tab.c:273` | `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...` |
| `child_handle_click` | function | `src/tab.c:1491` | `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_decode_image` | function | `src/tab.c:1682` | `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` |
| `child_handle_decode_image_b64` | function | `src/tab.c:1704` | `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)` |
| `child_handle_eval` | function | `src/tab.c:1649` | `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` |
| `child_handle_event` | function | `src/tab.c:1505` | `static void child_handle_event(int wfd, child_state *cs)` |
| `child_handle_geom` | function | `src/tab.c:1591` | `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` |
| `child_handle_load` | function | `src/tab.c:991` | `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,            ...` |
| `child_handle_mouse` | function | `src/tab.c:1553` | `static void child_handle_mouse(int wfd, child_state *cs)` |
| `child_handle_mutation` | function | `src/tab.c:1412` | `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,                         ...` |
| `child_handle_submit` | function | `src/tab.c:1615` | `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_tick` | function | `src/tab.c:1495` | `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)` |
| `child_next_timer_ms` | function | `src/tab.c:1397` | `static int32_t child_next_timer_ms(child_state *cs)` |
| `child_reset_page` | function | `src/tab.c:156` | `static void child_reset_page(child_state *cs)` |
| `child_state` | struct | `src/tab.c:125` | `` |
| `column` | function | `src/tab.c:2226` | `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...` |
| `content` | function | `src/tab.c:1258` | `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...` |
| `ctype_is_css` | function | `src/tab.c:799` | `static int ctype_is_css(const char *ctype)` |
| `ctype_is_javascript` | function | `src/tab.c:790` | `static int ctype_is_javascript(const char *ctype)` |
| `depth` | function | `src/tab.c:1759` | `* defense in depth (seccomp already excludes open/socket/exec);` |
| `exec_worker_child` | function | `src/tab.c:2597` | `static void exec_worker_child(int rfd, int wfd)` |
| `fallback` | function | `src/tab.c:1067` | `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it...` |
| `gate_js_nav` | function | `src/tab.c:2952` | `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` |
| `gen_session_key` | function | `src/tab.c:1716` | `static uint64_t gen_session_key(void)` |
| `geom_parent` | function | `src/tab.c:1583` | `static dom_node_id geom_parent(void *ctx, dom_node_id n)` |
| `hist_ops_free` | function | `src/tab.c:2761` | `static void hist_ops_free(tab_hist_op *ops, size_t n)` |
| `host` | function | `src/tab.c:285` | `* granted net access for this host (allow.conf AND js.conf). Otherwise they stay * undefined...` |
| `ignore_sigpipe` | function | `src/tab.c:1994` | `static void ignore_sigpipe(void)` |
| `io_failure` | function | `src/tab.c:2589` | `static tab_status io_failure(tab *t)` |
| `is_activation_event` | function | `src/tab.c:2826` | `static int is_activation_event(const char *type)` |
| `layout` | function | `src/tab.c:2215` | `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....` |
| `load` | function | `src/tab.c:1973` | `* subresource requests this load (set per page: host in allow.conf AND js.conf);` |
| `log_external_skip` | function | `src/tab.c:807` | `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,                 ...` |
| `once` | function | `src/tab.c:1303` | `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);` |
| `open_urls_free` | function | `src/tab.c:2835` | `static void open_urls_free(char **u, size_t n)` |
| `parse_worker_fd` | function | `src/tab.c:1934` | `static int parse_worker_fd(const char *s, int *out)` |
| `policy` | function | `src/tab.c:176` | `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a  * compromi...` |
| `read_console` | function | `src/tab.c:2542` | `static int read_console(int fd, fb_buffer *out)` |
| `read_field` | function | `src/tab.c:2020` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `read_opens` | function | `src/tab.c:2845` | `static tab_status read_opens(tab *t, const char *page_url, int gesture,                          ...` |
| `read_view` | function | `src/tab.c:2036` | `static int read_view(int fd, pv_view **out)` |
| `read_ws` | function | `src/tab.c:2883` | `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` |
| `run` | function | `src/tab.c:825` | `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).  * Call after every ...` |
| `run_js` | function | `src/tab.c:230` | `* regardless of run_js (a no-JS load simply never records a request). */ static int child_load(ch...` |
| `send_request` | function | `src/tab.c:2579` | `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` |
| `swap` | function | `src/tab.c:1312` | `* display:none hiding an element via class swap (CSS, not      * DOM removal). */     if (ok && v...` |
| `tab` | struct | `src/tab.c:1966` | `` |
| `tab_alive` | function | `src/tab.c:3492` | `int tab_alive(const tab *t)` |
| `tab_child_pid` | function | `src/tab.c:3498` | `pid_t tab_child_pid(const tab *t)` |
| `tab_click` | function | `src/tab.c:3165` | `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)` |
| `tab_close` | function | `src/tab.c:3502` | `void tab_close(tab *t)` |
| `tab_decode_image` | function | `src/tab.c:3468` | `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)` |
| `tab_decode_image_data_url` | function | `src/tab.c:3474` | `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)` |
| `tab_decode_image_op` | function | `src/tab.c:3426` | `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,         ...` |
| `tab_eval` | function | `src/tab.c:3386` | `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)` |
| `tab_eval_result_free` | function | `src/tab.c:3547` | `void tab_eval_result_free(tab_eval_result *r)` |
| `tab_image_free` | function | `src/tab.c:3556` | `void tab_image_free(tab_image *img)` |
| `tab_last_subreq_stats` | function | `src/tab.c:2690` | `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)` |
| `tab_load` | function | `src/tab.c:2962` | `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)` |
| `tab_load_ex` | function | `src/tab.c:2966` | `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)` |
| `tab_load_full` | function | `src/tab.c:2970` | `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,             ...` |
| `tab_mod_fetch` | function | `src/tab.c:905` | `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` |
| `tab_mod_resolve` | function | `src/tab.c:883` | `static int tab_mod_resolve(void *host, const char *base, const char *spec,                       ...` |
| `tab_page_free` | function | `src/tab.c:3517` | `void tab_page_free(tab_page *p)` |
| `tab_parse_worker_args` | function | `src/tab.c:1946` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)` |
| `tab_popstate` | function | `src/tab.c:3592` | `tab_status tab_popstate(tab *t, int index, tab_page *out)` |
| `tab_read_view` | function | `src/tab.c:3286` | `tab_status tab_read_view(tab *t, tab_page *out)` |
| `tab_read_view_ex` | function | `src/tab.c:3290` | `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)` |
| `tab_refresh_alive` | function | `src/tab.c:2001` | `static void tab_refresh_alive(tab *t)` |
| `tab_set_cookies` | function | `src/tab.c:2700` | `void tab_set_cookies(tab *t, const char *cookies)` |
| `tab_set_css_allowed` | function | `src/tab.c:2685` | `void tab_set_css_allowed(tab *t, int allowed)` |
| `tab_set_css_sink` | function | `src/tab.c:2674` | `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)` |
| `tab_set_fetcher` | function | `src/tab.c:2668` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)` |
| `tab_set_geometry` | function | `src/tab.c:3566` | `tab_status tab_set_geometry(tab *t, const jg_table *g)` |
| `tab_set_net_allowed` | function | `src/tab.c:2680` | `void tab_set_net_allowed(tab *t, int allowed)` |
| `tab_set_storage` | function | `src/tab.c:3617` | `void tab_set_storage(tab *t, const char *blob, size_t len)` |
| `tab_set_viewport_w` | function | `src/tab.c:2695` | `void tab_set_viewport_w(tab *t, int px)` |
| `tab_submit` | function | `src/tab.c:3181` | `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` |
| `tab_subreq_permitted` | function | `src/tab.c:2706` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)` |
| `tab_tick` | function | `src/tab.c:3172` | `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)` |
| `tab_url_resolve` | function | `src/tab.c:874` | `static int tab_url_resolve(void *ctx, const char *base, const char *ref,                         ...` |
| `tab_worker_dispatch` | function | `src/tab.c:1956` | `void tab_worker_dispatch(int argc, char **argv)` |
| `tab_worker_run` | function | `src/tab.c:1736` | `static void tab_worker_run(int rfd, int wfd)` |
| `tab_ws_event` | function | `src/tab.c:3598` | `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,        ...` |
| `tests` | function | `src/tab.c:2111` | `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...` |
| `tzset` | function | `src/tab.c:1754` | `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);` |
| `window` | function | `src/tab.c:946` | `* net window (cs->net_active). */ static void child_fetch_stylesheets(child_state *cs)` |
| `write_field` | function | `src/tab.c:297` | `static int write_field(int fd, const char *s)` |
| `write_full` | function | `src/tab.c:1332` | `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 \|\| write_full(wfd, text, xl) == 0) && write_view(wfd...` |
| `write_history` | function | `src/tab.c:927` | `static int write_history(int wfd, child_state *cs)` |
| `write_opens` | function | `src/tab.c:1385` | `static int write_opens(int wfd, child_state *cs)` |
| `write_storage` | function | `src/tab.c:1371` | `static int write_storage(int wfd, child_state *cs)` |
| `write_ws` | function | `src/tab.c:1354` | `static int write_ws(int wfd, child_state *cs)` |
| `ws_ops_free` | function | `src/tab.c:2874` | `static void ws_ops_free(tab_ws_op *ops, size_t n)` |
| `pair_parity` | function | `src/text_case.c:8` | `static int pair_parity(uint32_t cp)` |
| `tc_is_lower` | function | `src/text_case.c:54` | `int tc_is_lower(uint32_t cp)` |
| `tc_lower` | function | `src/text_case.c:37` | `uint32_t tc_lower(uint32_t cp)` |
| `tc_smallcaps_runs` | function | `src/text_case.c:117` | `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap)` |
| `tc_transform` | function | `src/text_case.c:95` | `size_t tc_transform(const char *s, size_t n, int transform, int word_start,                     c...` |
| `tc_upper` | function | `src/text_case.c:18` | `uint32_t tc_upper(uint32_t cp)` |
| `utf8_decode` | function | `src/text_case.c:61` | `static size_t utf8_decode(const unsigned char *s, size_t n, uint32_t *cp)` |
| `utf8_len_of` | function | `src/text_case.c:91` | `static size_t utf8_len_of(uint32_t cp)` |
| `utf8_put` | function | `src/text_case.c:79` | `static void utf8_put(uint32_t cp, size_t len, unsigned char *out)` |
| `TSH_CACHE_SLOTS` | macro | `src/text_shape.c:33` | `#define TSH_CACHE_SLOTS` |
| `TSH_FB_BLOCKS` | macro | `src/text_shape.c:649` | `#define TSH_FB_BLOCKS` |
| `TSH_FB_SLOTS` | macro | `src/text_shape.c:648` | `#define TSH_FB_SLOTS` |
| `TSH_MAX_FONT_BYTES` | macro | `src/text_shape.c:29` | `#define TSH_MAX_FONT_BYTES` |
| `TSH_MAX_RUNS` | macro | `src/text_shape.c:783` | `#define TSH_MAX_RUNS` |
| `TSH_SUBS_MAX` | macro | `src/text_shape.c:400` | `#define TSH_SUBS_MAX` |
| `TSH_WEB_SLOTS` | macro | `src/text_shape.c:189` | `#define TSH_WEB_SLOTS` |
| `_POSIX_C_SOURCE` | macro | `src/text_shape.c:12` | `#define _POSIX_C_SOURCE` |
| `ascii_ieq` | function | `src/text_shape.c:331` | `static int ascii_ieq(const char *a, const char *b)` |
| `backend_init` | function | `src/text_shape.c:65` | `static int backend_init(void)` |
| `characters` | function | `src/text_shape.c:100` | `* hold characters ('-', ':') that the pattern syntax treats specially. */ static int load_entry_file(tsh_entry *e...` |
| `cover_cp` | function | `src/text_shape.c:743` | `static int cover_cp(unsigned cp, void *vctx)` |
| `entry_free` | function | `src/text_shape.c:318` | `static void entry_free(tsh_entry *e)` |
| `fb_clear` | function | `src/text_shape.c:662` | `static void fb_clear(void)` |
| `fb_entry` | function | `src/text_shape.c:672` | `static tsh_entry *fb_entry(unsigned cp, int bold)` |
| `fc_installed` | function | `src/text_shape.c:386` | `static int fc_installed(const char *name, void *ctx)` |
| `fc_resolve` | function | `src/text_shape.c:429` | `static int fc_resolve(const char *name, char *out, size_t cap, void *ctx)` |
| `file` | type_alias | `src/text_shape.c:650` | `typedef struct tsh_fb { char file[512];` |
| `generic_name` | function | `src/text_shape.c:55` | `static const char *generic_name(int family)` |
| `get_entry` | function | `src/text_shape.c:173` | `static tsh_entry *get_entry(int family, int bold, int italic)` |
| `get_entry_ex` | function | `src/text_shape.c:531` | `static tsh_entry *get_entry_ex(const tsh_font *f)` |
| `lfam_index` | function | `src/text_shape.c:484` | `static int lfam_index(const char *fam)` |
| `load_entry` | function | `src/text_shape.c:169` | `static int load_entry(tsh_entry *e, int family, int bold, int italic)` |
| `load_entry_file` | function | `src/text_shape.c:133` | `static int load_entry_file(tsh_entry *e, const char *path, int index)` |
| `load_entry_named` | function | `src/text_shape.c:103` | `static int load_entry_named(tsh_entry *e, const char *fam, int bold, int italic)` |
| `loaded` | type_alias | `src/text_shape.c:34` | `typedef struct tsh_entry { int loaded;` |
| `local_clear` | function | `src/text_shape.c:474` | `static void local_clear(void)` |
| `local_entry` | function | `src/text_shape.c:511` | `static tsh_entry *local_entry(int handle, int bold, int italic)` |
| `name` | type_alias | `src/text_shape.c:457` | `typedef struct tsh_lfam { char name[TSH_FAMILY_MAX];` |
| `read_font_file` | function | `src/text_shape.c:82` | `static unsigned char *read_font_file(const char *path, long *out_n)` |
| `rides_previous` | function | `src/text_shape.c:614` | `static int rides_previous(unsigned cp)` |
| `shape_entry` | function | `src/text_shape.c:756` | `static tsh_status shape_entry(tsh_entry *e, double px, const char *text, size_t len,             ...` |
| `shape_runs` | function | `src/text_shape.c:787` | `static tsh_status shape_runs(cairo_t *cr, const tsh_font *f, double px, double x,                ...` |
| `slice` | function | `src/text_shape.c:213` | `* woff2 slice (spec/webfont.md);` |
| `tsh_cover_ctx` | struct | `src/text_shape.c:734` | `` |
| `tsh_draw` | function | `src/text_shape.c:835` | `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,                     double x, doub...` |
| `tsh_entry` | struct | `src/text_shape.c:35` | `` |
| `tsh_face` | function | `src/text_shape.c:842` | `cairo_font_face_t *tsh_face(const tsh_font *f)` |
| `tsh_family_is_generic` | function | `src/text_shape.c:340` | `int tsh_family_is_generic(const char *name)` |
| `tsh_fb` | struct | `src/text_shape.c:651` | `` |
| `tsh_lfam` | struct | `src/text_shape.c:458` | `` |
| `tsh_llist` | struct | `src/text_shape.c:464` | `` |
| `tsh_local_handle` | function | `src/text_shape.c:492` | `int tsh_local_handle(const char *list)` |
| `tsh_measure` | function | `src/text_shape.c:829` | `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)` |
| `tsh_pick_family` | function | `src/text_shape.c:373` | `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong,         ...` |
| `tsh_pick_from_list` | function | `src/text_shape.c:352` | `int tsh_pick_from_list(const char *list, tsh_name_resolver resolve, void *ctx,                   ...` |
| `tsh_ready` | function | `src/text_shape.c:543` | `int tsh_ready(void)` |
| `tsh_segment` | function | `src/text_shape.c:622` | `int tsh_segment(const char *text, size_t len, tsh_cover_fn cover, void *ctx,                 tsh_...` |
| `tsh_shape` | function | `src/text_shape.c:548` | `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,                 ...` |
| `tsh_shutdown` | function | `src/text_shape.c:848` | `void tsh_shutdown(void)` |
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
| `wh_send` | function | `src/ws_hub.c:221` | `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary)` |
| `ZM_LADDER_N` | macro | `src/zoom.c:12` | `#define ZM_LADDER_N` |
| `zm_apply` | function | `src/zoom.c:44` | `double zm_apply(double base_px, int pct)` |
| `zm_clamp` | function | `src/zoom.c:14` | `int zm_clamp(int pct)` |
| `zm_reset` | function | `src/zoom.c:36` | `int zm_reset(void)` |
| `zm_scale` | function | `src/zoom.c:40` | `double zm_scale(int pct)` |
| `zm_zoom_in` | function | `src/zoom.c:20` | `int zm_zoom_in(int pct)` |
| `zm_zoom_out` | function | `src/zoom.c:28` | `int zm_zoom_out(int pct)` |
| `CHECK` | macro | `tests/itest_secure_fetch.c:16` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/itest_secure_fetch.c:26` | `int main(void)` |
| `main` | function | `tests/test_anti_fp.c:197` | `int main(void)` |
| `test_boolean_props` | function | `tests/test_anti_fp.c:74` | `static void test_boolean_props(void **state)` |
| `test_bucket_screen` | function | `tests/test_anti_fp.c:83` | `static void test_bucket_screen(void **state)` |
| `test_coarsen_time` | function | `tests/test_anti_fp.c:18` | `static void test_coarsen_time(void **state)` |
| `test_identity_is_fixed` | function | `tests/test_anti_fp.c:34` | `static void test_identity_is_fixed(void **state)` |
| `test_legacy_identity_fixed` | function | `tests/test_anti_fp.c:61` | `static void test_legacy_identity_fixed(void **state)` |
| `test_origin_key_deterministic` | function | `tests/test_anti_fp.c:146` | `static void test_origin_key_deterministic(void **state)` |
| `test_origin_key_empty_namespace` | function | `tests/test_anti_fp.c:171` | `static void test_origin_key_empty_namespace(void **state)` |
| `test_origin_key_per_session` | function | `tests/test_anti_fp.c:165` | `static void test_origin_key_per_session(void **state)` |
| `test_origin_key_per_site` | function | `tests/test_anti_fp.c:153` | `static void test_origin_key_per_site(void **state)` |
| `test_origin_key_unlinks_readback` | function | `tests/test_anti_fp.c:183` | `static void test_origin_key_unlinks_readback(void **state)` |
| `test_perturb_bounded_lsb` | function | `tests/test_anti_fp.c:111` | `static void test_perturb_bounded_lsb(void **state)` |
| `test_perturb_deterministic` | function | `tests/test_anti_fp.c:101` | `static void test_perturb_deterministic(void **state)` |
| `test_perturb_key_sensitive` | function | `tests/test_anti_fp.c:126` | `static void test_perturb_key_sensitive(void **state)` |
| `test_perturb_safe_edges` | function | `tests/test_anti_fp.c:136` | `static void test_perturb_safe_edges(void **state)` |
| `dbl_eq` | function | `tests/test_block_flow.c:21` | `static int dbl_eq(double a, double b)` |
| `main` | function | `tests/test_block_flow.c:105` | `int main(void)` |
| `test_collapse_n_edges` | function | `tests/test_block_flow.c:84` | `static void test_collapse_n_edges(void **state)` |
| `test_collapse_n_matches_binary` | function | `tests/test_block_flow.c:70` | `static void test_collapse_n_matches_binary(void **state)` |
| `test_margins_adjoin` | function | `tests/test_block_flow.c:95` | `static void test_margins_adjoin(void **state)` |
| `test_non_finite_is_absent` | function | `tests/test_block_flow.c:59` | `static void test_non_finite_is_absent(void **state)` |
| `test_two_negative_take_the_most_negative` | function | `tests/test_block_flow.c:50` | `static void test_two_negative_take_the_most_negative(void **state)` |
| `test_two_positive_collapse_to_max` | function | `tests/test_block_flow.c:29` | `static void test_two_positive_collapse_to_max(void **state)` |
| `main` | function | `tests/test_box_blur.c:78` | `int main(void)` |
| `mass` | function | `tests/test_box_blur.c:11` | `static long mass(const unsigned char *b, int n)` |
| `test_box_sizes` | function | `tests/test_box_blur.c:17` | `static void test_box_sizes(void **state)` |
| `test_impulse_conserves_mass_and_is_symmetric` | function | `tests/test_box_blur.c:34` | `static void test_impulse_conserves_mass_and_is_symmetric(void **state)` |
| `test_invalid_arguments` | function | `tests/test_box_blur.c:69` | `static void test_invalid_arguments(void **state)` |
| `test_uniform_interior_unchanged` | function | `tests/test_box_blur.c:58` | `static void test_uniform_interior_unchanged(void **state)` |
| `test_zero_sigma_is_identity` | function | `tests/test_box_blur.c:50` | `static void test_zero_sigma_is_identity(void **state)` |
| `assert_edges` | function | `tests/test_box_style.c:28` | `static void assert_edges(bx_edges e, double t, double r, double b, double l)` |
| `dbl_eq` | function | `tests/test_box_style.c:23` | `static int dbl_eq(double a, double b)` |
| `main` | function | `tests/test_box_style.c:712` | `int main(void)` |
| `percentage` | function | `tests/test_box_style.c:543` | `* percentage (a plain `width:50%` leaves the px half UNSET, a plain `width:300px`  * leaves the p...` |
| `test_block_ua_box_heading_level_wins` | function | `tests/test_box_style.c:206` | `static void test_block_ua_box_heading_level_wins(void **state)` |
| `test_block_ua_box_is_content_independent` | function | `tests/test_box_style.c:195` | `static void test_block_ua_box_is_content_independent(void **state)` |
| `test_block_ua_box_is_total` | function | `tests/test_box_style.c:228` | `static void test_block_ua_box_is_total(void **state)` |
| `test_block_ua_box_list_item_wins_over_ancestor` | function | `tests/test_box_style.c:219` | `static void test_block_ua_box_list_item_wins_over_ancestor(void **state)` |
| `test_blockquote` | function | `tests/test_box_style.c:77` | `static void test_blockquote(void **state)` |
| `test_body_has_no_margin` | function | `tests/test_box_style.c:35` | `static void test_body_has_no_margin(void **state)` |
| `test_border_box_height` | function | `tests/test_box_style.c:475` | `static void test_border_box_height(void **state)` |
| `test_border_span` | function | `tests/test_box_style.c:646` | `static void test_border_span(void **state)` |
| `test_case_insensitive` | function | `tests/test_box_style.c:111` | `static void test_case_insensitive(void **state)` |
| `test_content_clipped` | function | `tests/test_box_style.c:493` | `static void test_content_clipped(void **state)` |
| `test_definite_content_h` | function | `tests/test_box_style.c:688` | `static void test_definite_content_h(void **state)` |
| `test_display_name` | function | `tests/test_box_style.c:375` | `static void test_display_name(void **state)` |
| `test_display_none_for_non_rendered` | function | `tests/test_box_style.c:102` | `static void test_display_none_for_non_rendered(void **state)` |
| `test_div_is_block` | function | `tests/test_box_style.c:134` | `static void test_div_is_block(void **state)` |
| `test_flex_max_clamp` | function | `tests/test_box_style.c:611` | `static void test_flex_max_clamp(void **state)` |
| `test_flex_min_clamp` | function | `tests/test_box_style.c:659` | `static void test_flex_min_clamp(void **state)` |
| `test_heading_ladder` | function | `tests/test_box_style.c:50` | `static void test_heading_ladder(void **state)` |
| `test_hr` | function | `tests/test_box_style.c:84` | `static void test_hr(void **state)` |
| `test_inline_and_inline_block` | function | `tests/test_box_style.c:91` | `static void test_inline_and_inline_block(void **state)` |
| `test_line_height_px` | function | `tests/test_box_style.c:701` | `static void test_line_height_px(void **state)` |
| `test_lists` | function | `tests/test_box_style.c:66` | `static void test_lists(void **state)` |
| `test_paragraph` | function | `tests/test_box_style.c:43` | `static void test_paragraph(void **state)` |
| `test_parse_display_case_and_trim` | function | `tests/test_box_style.c:348` | `static void test_parse_display_case_and_trim(void **state)` |
| `test_parse_display_errors` | function | `tests/test_box_style.c:357` | `static void test_parse_display_errors(void **state)` |
| `test_parse_display_inline_aliases` | function | `tests/test_box_style.c:339` | `static void test_parse_display_inline_aliases(void **state)` |
| `test_parse_display_keywords` | function | `tests/test_box_style.c:320` | `static void test_parse_display_keywords(void **state)` |
| `test_pct_block_size` | function | `tests/test_box_style.c:672` | `static void test_pct_block_size(void **state)` |
| `test_place_centering` | function | `tests/test_box_style.c:408` | `static void test_place_centering(void **state)` |
| `test_place_declared_width_overflows` | function | `tests/test_box_style.c:627` | `static void test_place_declared_width_overflows(void **state)` |
| `test_place_failclosed_bounds` | function | `tests/test_box_style.c:432` | `static void test_place_failclosed_bounds(void **state)` |
| `test_place_insets` | function | `tests/test_box_style.c:420` | `static void test_place_insets(void **state)` |
| `test_place_max_width_caps` | function | `tests/test_box_style.c:397` | `static void test_place_max_width_caps(void **state)` |
| `test_place_no_box_is_identity` | function | `tests/test_box_style.c:390` | `static void test_place_no_box_is_identity(void **state)` |
| `test_table_role_from_tag` | function | `tests/test_box_style.c:243` | `static void test_table_role_from_tag(void **state)` |
| `test_table_role_is_total` | function | `tests/test_box_style.c:273` | `static void test_table_role_is_total(void **state)` |
| `test_ua_case_insensitive_and_trimmed` | function | `tests/test_box_style.c:283` | `static void test_ua_case_insensitive_and_trimmed(void **state)` |
| `test_ua_code_space_is_total` | function | `tests/test_box_style.c:309` | `static void test_ua_code_space_is_total(void **state)` |
| `test_ua_fails_closed` | function | `tests/test_box_style.c:291` | `static void test_ua_fails_closed(void **state)` |
| `test_ua_list_item_is_distinct_but_unspaced` | function | `tests/test_box_style.c:182` | `static void test_ua_list_item_is_distinct_but_unspaced(void **state)` |
| `test_ua_spaced_tags_round_trip` | function | `tests/test_box_style.c:162` | `static void test_ua_spaced_tags_round_trip(void **state)` |
| `test_ua_structural_wrappers_have_no_margin` | function | `tests/test_box_style.c:145` | `static void test_ua_structural_wrappers_have_no_margin(void **state)` |
| `test_unknown_and_null_are_neutral_inline` | function | `tests/test_box_style.c:119` | `static void test_unknown_and_null_are_neutral_inline(void **state)` |
| `test_width_cap2_is_min_of_two_values` | function | `tests/test_box_style.c:524` | `static void test_width_cap2_is_min_of_two_values(void **state)` |
| `test_width_cap_pct` | function | `tests/test_box_style.c:509` | `static void test_width_cap_pct(void **state)` |
| `width` | function | `tests/test_box_style.c:553` | `* a negative width (CSS Values 4 section 10.1: out-of-range calc() results are * clamped at used-value time). */...` |
| `UNSET4` | macro | `tests/test_box_tree.c:630` | `#define UNSET4` |
| `assert_rect` | function | `tests/test_box_tree.c:28` | `static void assert_rect(const bt_node *n, double x, double y, double w, double h)` |

Next: [SYMBOLS_p10.md](SYMBOLS_p10.md)
