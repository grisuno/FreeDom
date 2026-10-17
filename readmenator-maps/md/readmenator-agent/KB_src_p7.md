# Subsystem: src (page 7 of 8)
Previous: [KB_src_p6.md](KB_src_p6.md)

## src/render_doc.c
- Doc: rd_push: Appends one block, taking owned copies of text (required) and href (optional). *...
- Layer: presentation
- Language: c
- Symbols:
  - `utf8_sanitized_dup` (function, line 28) `static char *utf8_sanitized_dup(const char *s)`
  - `rd_push` (function, line 60) `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,
                 ...`
  - `rd_push_input` (function, line 204) `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)`
  - `resolve_image_decision` (function, line 240) `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,
        ...`
  - `rd_build` (function, line 262) `rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_u...`
  - `unset` (function, line 650) `* background paints as if unset (no border/box-shadow-style
                 * "broken image" pla...`
  - `rd_free` (function, line 715) `void rd_free(rd_doc *d)`
  - `rd_count` (function, line 732) `size_t rd_count(const rd_doc *d)`
  - `rd_at` (function, line 736) `const rd_block *rd_at(const rd_doc *d, size_t i)`
  - `rd_box_count` (function, line 741) `size_t rd_box_count(const rd_doc *d)`
  - `rd_box_at` (function, line 745) `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)`
  - `rd_cont_count` (function, line 750) `size_t rd_cont_count(const rd_doc *d)`
  - `rd_cont_at` (function, line 754) `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)`
  - `rd_kind_name` (function, line 759) `const char *rd_kind_name(rd_kind k)`
  - `rd_block_tag` (function, line 773) `const char *rd_block_tag(const rd_block *b)`
  - `rd_input_label` (function, line 804) `const char *rd_input_label(int input_type)`
  - `rd_input_invisible` (function, line 824) `int rd_input_invisible(int input_type)`
  - `rd_image_label` (function, line 828) `const char *rd_image_label(rdp_img_decision d)`
  - `rd_image_fail_label` (function, line 839) `const char *rd_image_fail_label(img_fail_reason reason)`
  - `place` (function, line 230) `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never...`
- Depends on: `include/box_style.h`, `include/css.h`, `include/data_url.h`, `include/render_doc.h`, `include/url.h`, `include/util.h`

## src/render_policy.c
- Layer: presentation
- Language: c
- Symbols:
  - `rdp_caps_safe` (function, line 17) `rdp_caps rdp_caps_safe(void)`
  - `rdp_is_tracking_pixel` (function, line 22) `int rdp_is_tracking_pixel(int w, int h)`
  - `rdp_image_decision` (function, line 28) `rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char...`
  - `rdp_img_reason` (function, line 63) `const char *rdp_img_reason(rdp_img_decision d)`
  - `rdp_images_warning` (function, line 74) `const char *rdp_images_warning(void)`
- Depends on: `include/data_url.h`, `include/render_policy.h`, `include/request_policy.h`

## src/renderer.c
- Layer: presentation
- Language: c
- Symbols:
  - `child_render` (function, line 25) `static void child_render(int wfd, const char *html, size_t len)`
  - `read_field` (function, line 53) `static int read_field(int fd, char **out, size_t *out_len)`
  - `rd_render_html` (function, line 70) `rd_status rd_render_html(const char *html, size_t len, rd_result *out)`
  - `rd_result_free` (function, line 120) `void rd_result_free(rd_result *out)`
  - `write_full` (function, line 40) `&& write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 || write_full(wfd, title, tl) == 0) && write_full(wfd, &xl...`
  - `_POSIX_C_SOURCE` (macro, line 7) `#define _POSIX_C_SOURCE`
- Depends on: `include/html_parse.h`, `include/os_sandbox.h`, `include/renderer.h`, `include/util.h`

## src/request_policy.c
- Doc: public_suffix_labels: Number of labels of the public suffix (eTLD) of a lowercased host...
- Layer: business_logic
- Language: c
- Symbols:
  - `lower` (function, line 22) `static char lower(char c)`
  - `ci_starts_with` (function, line 26) `static int ci_starts_with(const char *s, const char *prefix)`
  - `psl_cmp` (function, line 36) `static int psl_cmp(const void *key, const void *elem)`
  - `psl_in` (function, line 40) `static int psl_in(const char *const *arr, size_t n, const char *key)`
  - `public_suffix_labels` (function, line 48) `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)`
  - `rp_host_of` (function, line 76) `int rp_host_of(const char *url, char *out, size_t out_size)`
  - `rp_site_of` (function, line 102) `int rp_site_of(const char *host, char *out, size_t out_size)`
  - `rp_same_site` (function, line 134) `int rp_same_site(const char *top_level_url, const char *request_url)`
  - `rp_evaluate` (function, line 143) `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)`
  - `RP_MAX_HOST` (macro, line 17) `#define RP_MAX_HOST`
  - `RP_MAX_LABELS` (macro, line 18) `#define RP_MAX_LABELS`
- Depends on: `include/psl_data.h`, `include/request_policy.h`

## src/secure_fetch.c
- Doc: tls_capture: Snapshot of the negotiated TLS state. curl exposes the live SSL* only while a...
- Layer: utility
- Language: c
- Symbols:
  - `body_sink` (struct, line 434)
  - `tls_capture` (struct, line 447)
  - `fetch_ctx` (struct, line 457)
  - `sf_ws` (struct, line 1098)
  - `sink` (type_alias, line 456) `typedef struct fetch_ctx { body_sink sink;`
  - `ci_starts_with` (function, line 44) `static int ci_starts_with(const char *haystack, const char *prefix)`
  - `ci_index` (function, line 56) `static long ci_index(const char *haystack, const char *needle)`
  - `sf_share_lock` (function, line 68) `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...`
  - `sf_share_unlock` (function, line 74) `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)`
  - `sf_global_init` (function, line 81) `void sf_global_init(void)`
  - `sf_cookie_line_matches` (function, line 96) `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...`
  - `sf_url_host_path` (function, line 151) `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...`
  - `sf_cookie_header_for` (function, line 166) `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)`
  - `sf_cookie_put` (function, line 195) `void sf_cookie_put(const char *url, const char *namevalue)`
  - `sf_config_default` (function, line 216) `sf_config sf_config_default(void)`
  - `sf_user_agent_or_default` (function, line 241) `const char *sf_user_agent_or_default(const char *ua)`
  - `sf_impersonate_kex_groups` (function, line 245) `const char *sf_impersonate_kex_groups(void)`
  - `sf_impersonate_tls13_ciphers` (function, line 246) `const char *sf_impersonate_tls13_ciphers(void)`
  - `sf_validate_url` (function, line 250) `sf_status sf_validate_url(const char *url)`
  - `sf_url_is_http` (function, line 258) `static int sf_url_is_http(const char *url)`
  - `sf_check_tls_version` (function, line 270) `sf_status sf_check_tls_version(const char *negotiated_version)`
  - `sf_check_group_is_pq` (function, line 275) `sf_status sf_check_group_is_pq(const char *negotiated_group)`
  - `sf_check_chain_policy` (function, line 284) `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)`
  - `sf_enforce_policy` (function, line 294) `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...`
  - `copy_checked` (function, line 325) `static int copy_checked(char *dst, size_t dstsz, const char *src)`
  - `sf_is_redirect_code` (function, line 334) `int sf_is_redirect_code(long http_code)`
  - `sf_parse_location_header` (function, line 341) `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)`
  - `sf_resolve_redirect` (function, line 359) `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...`
  - `sf_ci_prefix` (function, line 371) `static int sf_ci_prefix(const char *s, const char *p)`
  - `sf_response_free` (function, line 411) `void sf_response_free(sf_response *resp)`
  - `copy_bounded` (function, line 470) `static void copy_bounded(char *dst, size_t dstsz, const char *src)`
  - `get_negotiated_group_name` (function, line 481) `static const char *get_negotiated_group_name(SSL *ssl)`
  - `tls_capture_try` (function, line 514) `static void tls_capture_try(tls_capture *cap)`
  - `tls_capture_from_ssl` (function, line 524) `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)`
  - `header_cb` (function, line 550) `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)`
  - `write_cb` (function, line 586) `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)`
  - `name_is_pq_sig` (function, line 618) `static int name_is_pq_sig(int pknid)`
  - `inspect_chain` (function, line 628) `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)`
  - `map_curl_error` (function, line 681) `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)`
  - `add_header` (function, line 722) `static int add_header(struct curl_slist **h, const char *line)`
  - `sf_setup_handle` (function, line 736) `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,
           ...`
  - `redirect` (function, line 811) `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...`
  - `sf_perform` (function, line 879) `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...`
  - `sf_get` (function, line 1014) `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)`
  - `sf_post` (function, line 1018) `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...`
  - `sf_get_follow` (function, line 1032) `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...`
  - `ws_ssl_info_cb` (function, line 1084) `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)`
  - `ws_ssl_ctx_cb` (function, line 1091) `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)`
  - `sf_ws_url_check` (function, line 1105) `sf_status sf_ws_url_check(const char *url)`
  - `ws_free` (function, line 1117) `static void ws_free(sf_ws *ws)`
  - `sf_ws_open` (function, line 1126) `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)`
  - `sf_ws_send` (function, line 1181) `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)`
  - `sf_ws_recv` (function, line 1204) `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)`
  - `sf_ws_fd` (function, line 1226) `int sf_ws_fd(const sf_ws *ws)`
  - `sf_ws_close` (function, line 1233) `void sf_ws_close(sf_ws *ws)`
  - `module` (function, line 364) `* pure url module (DRY);`
  - `progress` (function, line 443) `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);`
  - `database` (function, line 485) `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid...`
  - `group` (function, line 499) `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);`
  - `this` (function, line 531) `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and...`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
- Depends on: `include/anti_fp.h`, `include/secure_fetch.h`, `include/url.h`

## src/svg_render.c
- Doc: svg_render — inline <svg> markup -> a bounded list of geometric shapes.
- Layer: presentation
- Language: c
- Symbols:
  - `sv_attr` (struct, line 91)
  - `sv_ctx` (struct, line 151)
  - `stroke` (type_alias, line 151) `typedef struct sv_ctx { int fill, stroke;`
  - `sv_is_space` (function, line 21) `static int sv_is_space(char c)`
  - `sv_is_digit` (function, line 25) `static int sv_is_digit(char c)`
  - `sv_lower` (function, line 27) `static char sv_lower(char c)`
  - `sv_span_eq` (function, line 32) `static int sv_span_eq(const char *s, size_t n, const char *lit)`
  - `sv_sep` (function, line 82) `static void sv_sep(const char *s, size_t n, size_t *i)`
  - `sv_attr_get` (function, line 99) `static const char *sv_attr_get(const sv_attr *at, size_t nat, const char *name, size_t *len)`
  - `sv_attr_num` (function, line 108) `static double sv_attr_num(const sv_attr *at, size_t nat, const char *name, double dflt)`
  - `sv_mat_identity` (function, line 161) `static void sv_mat_identity(double *m)`
  - `sv_mat_mul` (function, line 166) `static void sv_mat_mul(const double *a, const double *b, double *out)`
  - `sv_parse_transform` (function, line 179) `static void sv_parse_transform(const char *s, size_t n, double *m)`
  - `sv_style_next` (function, line 238) `static int sv_style_next(const char *s, size_t n, size_t *i,
                         const char ...`
  - `sv_apply_prop` (function, line 260) `static void sv_apply_prop(sv_ctx *ctx, const char *nm, size_t nl,
                          const...`
  - `sv_ctx_from_attrs` (function, line 307) `static void sv_ctx_from_attrs(sv_ctx *ctx, const sv_attr *at, size_t nat)`
  - `sv_new_shape` (function, line 324) `static sv_shape *sv_new_shape(sv_image *im, int kind, const sv_ctx *ctx)`
  - `sv_parse_points` (function, line 343) `static void sv_parse_points(sv_image *im, sv_shape *sh, const char *s, size_t n)`
  - `sv_new_seg` (function, line 363) `static sv_seg *sv_new_seg(sv_image *im, sv_shape *sh)`
  - `sv_seg_move` (function, line 371) `static int sv_seg_move(sv_image *im, sv_shape *sh, double x, double y)`
  - `sv_seg_line` (function, line 378) `static int sv_seg_line(sv_image *im, sv_shape *sh, double x, double y)`
  - `sv_seg_cubic` (function, line 385) `static int sv_seg_cubic(sv_image *im, sv_shape *sh,
                        double x1, double y1,...`
  - `sv_arc_to_cubics` (function, line 399) `static int sv_arc_to_cubics(sv_image *im, sv_shape *sh,
                            double x0, do...`
  - `sv_parse_path` (function, line 477) `static void sv_parse_path(sv_image *im, sv_shape *sh, const char *s, size_t n)`
  - `sv_is_dropped_element` (function, line 635) `static int sv_is_dropped_element(const char *name, size_t n)`
  - `sv_scan_attrs` (function, line 647) `static void sv_scan_attrs(const char *s, size_t n, size_t *i,
                          sv_attr *...`
  - `sv_skip_subtree` (function, line 693) `static void sv_skip_subtree(const char *s, size_t n, size_t *i, const char *name, size_t nlen)`
  - `sv_collect_text` (function, line 725) `static void sv_collect_text(const char *s, size_t n, size_t *i, char *dst, size_t cap)`
  - `sv_fit` (function, line 743) `void sv_fit(const sv_image *img, double dw, double dh,
            double *scale, double *off_x, ...`
  - `sv_parse` (function, line 763) `sv_status sv_parse(const char *markup, size_t len, sv_image *out)`
  - `sv_parse_ex` (function, line 767) `sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill)`
  - `point` (function, line 556) `* current point (SVG 8.3.6). */ int had = (prev == 'C' || prev == 'c' || prev == 'S' || prev == 's');`
  - `SV_MAX_ATTRS` (macro, line 96) `#define SV_MAX_ATTRS`
- Depends on: `include/css_color.h`, `include/svg_render.h`

## src/tab.c
- Doc: write_field: Writes one length-prefixed string field (the write mirror of read_field): a size_t...
- Layer: utility
- Language: c
- Symbols:
  - `child_state` (struct, line 125)
  - `tab` (struct, line 1956)
  - `child_reset_page` (function, line 156) `static void child_reset_page(child_state *cs)`
  - `policy` (function, line 176) `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a
 * compromi...`
  - `run_js` (function, line 230) `* regardless of run_js (a no-JS load simply never records a request). */
static int child_load(ch...`
  - `write_field` (function, line 297) `static int write_field(int fd, const char *s)`
  - `blocks` (function, line 331) `*
 * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the
 * grid arr...`
  - `FB_MAX_FILE_BYTES` (function, line 736) `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...`
  - `budget_remaining_ms` (function, line 766) `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)`
  - `ctype_is_javascript` (function, line 780) `static int ctype_is_javascript(const char *ctype)`
  - `ctype_is_css` (function, line 789) `static int ctype_is_css(const char *ctype)`
  - `log_external_skip` (function, line 797) `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...`
  - `run` (function, line 815) `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...`
  - `tab_url_resolve` (function, line 864) `static int tab_url_resolve(void *ctx, const char *base, const char *ref,
                        ...`
  - `tab_mod_resolve` (function, line 873) `static int tab_mod_resolve(void *host, const char *base, const char *spec,
                      ...`
  - `tab_mod_fetch` (function, line 895) `static char *tab_mod_fetch(void *host, const char *url, size_t *len)`
  - `write_history` (function, line 917) `static int write_history(int wfd, child_state *cs)`
  - `window` (function, line 936) `* net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs)`
  - `child_handle_load` (function, line 981) `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...`
  - `swap` (function, line 1302) `* display:none hiding an element via class swap (CSS, not
     * DOM removal). */
    if (ok && v...`
  - `write_ws` (function, line 1344) `static int write_ws(int wfd, child_state *cs)`
  - `write_storage` (function, line 1361) `static int write_storage(int wfd, child_state *cs)`
  - `write_opens` (function, line 1375) `static int write_opens(int wfd, child_state *cs)`
  - `child_next_timer_ms` (function, line 1387) `static int32_t child_next_timer_ms(child_state *cs)`
  - `child_handle_mutation` (function, line 1402) `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...`
  - `child_handle_click` (function, line 1481) `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)`
  - `child_handle_tick` (function, line 1485) `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)`
  - `child_handle_event` (function, line 1495) `static void child_handle_event(int wfd, child_state *cs)`
  - `child_handle_mouse` (function, line 1543) `static void child_handle_mouse(int wfd, child_state *cs)`
  - `geom_parent` (function, line 1573) `static dom_node_id geom_parent(void *ctx, dom_node_id n)`
  - `child_handle_geom` (function, line 1581) `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)`
  - `child_handle_submit` (function, line 1605) `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)`
  - `child_handle_eval` (function, line 1639) `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)`
  - `child_handle_decode_image` (function, line 1672) `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)`
  - `child_handle_decode_image_b64` (function, line 1694) `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)`
  - `gen_session_key` (function, line 1706) `static uint64_t gen_session_key(void)`
  - `tab_worker_run` (function, line 1726) `static void tab_worker_run(int rfd, int wfd)`
  - `parse_worker_fd` (function, line 1924) `static int parse_worker_fd(const char *s, int *out)`
  - `tab_parse_worker_args` (function, line 1936) `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)`
  - `tab_worker_dispatch` (function, line 1946) `void tab_worker_dispatch(int argc, char **argv)`
  - `ignore_sigpipe` (function, line 1984) `static void ignore_sigpipe(void)`
  - `tab_refresh_alive` (function, line 1991) `static void tab_refresh_alive(tab *t)`
  - `read_field` (function, line 2010) `static int read_field(int fd, char **out, size_t *out_len)`
  - `read_view` (function, line 2026) `static int read_view(int fd, pv_view **out)`
  - `read_console` (function, line 2526) `static int read_console(int fd, fb_buffer *out)`
  - `send_request` (function, line 2563) `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)`
  - `io_failure` (function, line 2573) `static tab_status io_failure(tab *t)`
  - `exec_worker_child` (function, line 2581) `static void exec_worker_child(int rfd, int wfd)`
  - `tab_set_fetcher` (function, line 2652) `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)`
  - `tab_set_css_sink` (function, line 2658) `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)`
  - `tab_set_net_allowed` (function, line 2664) `void tab_set_net_allowed(tab *t, int allowed)`
  - `tab_set_css_allowed` (function, line 2669) `void tab_set_css_allowed(tab *t, int allowed)`
  - `tab_last_subreq_stats` (function, line 2674) `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)`
  - `tab_set_viewport_w` (function, line 2679) `void tab_set_viewport_w(tab *t, int px)`
  - `tab_set_cookies` (function, line 2684) `void tab_set_cookies(tab *t, const char *cookies)`
  - `tab_subreq_permitted` (function, line 2690) `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)`
  - `answered` (function, line 2702) `* A refused frame is still consumed and answered (status 0), so the protocol never
 * desyncs. Re...`
  - `hist_ops_free` (function, line 2745) `static void hist_ops_free(tab_hist_op *ops, size_t n)`
  - `is_activation_event` (function, line 2810) `static int is_activation_event(const char *type)`
  - `open_urls_free` (function, line 2819) `static void open_urls_free(char **u, size_t n)`
  - `read_opens` (function, line 2829) `static tab_status read_opens(tab *t, const char *page_url, int gesture,
                         ...`
  - `ws_ops_free` (function, line 2858) `static void ws_ops_free(tab_ws_op *ops, size_t n)`
  - `read_ws` (function, line 2867) `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)`
  - `gate_js_nav` (function, line 2936) `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)`
  - `tab_load` (function, line 2946) `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)`
  - `tab_load_ex` (function, line 2950) `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)`
  - `tab_load_full` (function, line 2954) `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...`
  - `tab_click` (function, line 3149) `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)`
  - `tab_tick` (function, line 3156) `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)`
  - `tab_submit` (function, line 3165) `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)`
  - `tab_read_view` (function, line 3270) `tab_status tab_read_view(tab *t, tab_page *out)`
  - `tab_read_view_ex` (function, line 3274) `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)`
  - `tab_eval` (function, line 3370) `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)`
  - `tab_decode_image_op` (function, line 3410) `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...`
  - `tab_decode_image` (function, line 3452) `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)`
  - `tab_decode_image_data_url` (function, line 3458) `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)`
  - `tab_alive` (function, line 3476) `int tab_alive(const tab *t)`
  - `tab_child_pid` (function, line 3482) `pid_t tab_child_pid(const tab *t)`
  - `tab_close` (function, line 3486) `void tab_close(tab *t)`
  - `tab_page_free` (function, line 3501) `void tab_page_free(tab_page *p)`
  - `tab_eval_result_free` (function, line 3531) `void tab_eval_result_free(tab_eval_result *r)`
  - `tab_image_free` (function, line 3540) `void tab_image_free(tab_image *img)`
  - `tab_set_geometry` (function, line 3550) `tab_status tab_set_geometry(tab *t, const jg_table *g)`
  - `tab_popstate` (function, line 3576) `tab_status tab_popstate(tab *t, int index, tab_page *out)`
  - `tab_ws_event` (function, line 3582) `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,
       ...`
  - `tab_set_storage` (function, line 3601) `void tab_set_storage(tab *t, const char *blob, size_t len)`
  - `buffer` (function, line 273) `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...`
  - `host` (function, line 285) `* granted net access for this host (allow.conf AND js.conf). Otherwise they stay * undefined...`
  - `fallback` (function, line 1057) `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it...`
  - `WHERE` (function, line 1215) `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...`
  - `content` (function, line 1248) `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...`
  - `once` (function, line 1293) `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);`
  - `write_full` (function, line 1322) `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0) && write_view(wfd...`
  - `EPIPE` (function, line 1728) `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();`
  - `tzset` (function, line 1744) `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);`
  - `depth` (function, line 1749) `* defense in depth (seccomp already excludes open/socket/exec);`
  - `load` (function, line 1963) `* subresource requests this load (set per page: host in allow.conf AND js.conf);`
  - `tests` (function, line 2101) `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...`
  - `layout` (function, line 2205) `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....`
  - `column` (function, line 2216) `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...`
  - `_GNU_SOURCE` (macro, line 14) `#define _GNU_SOURCE`
  - `TAB_SCREEN_W` (macro, line 58) `#define TAB_SCREEN_W`
  - `TAB_SCREEN_H` (macro, line 59) `#define TAB_SCREEN_H`
  - `TAB_WIRE_HEAD_N` (macro, line 63) `#define TAB_WIRE_HEAD_N`
  - `TAB_WIRE_A_N` (macro, line 64) `#define TAB_WIRE_A_N`
  - `TAB_WIRE_B_N` (macro, line 65) `#define TAB_WIRE_B_N`
  - `TAB_WIRE_BOX_F_N` (macro, line 66) `#define TAB_WIRE_BOX_F_N`
  - `TAB_WIRE_GRID_N` (macro, line 67) `#define TAB_WIRE_GRID_N`
  - `TAB_MAX_RUNS` (macro, line 71) `#define TAB_MAX_RUNS`
  - `PV_MAX_CONTAINERS_WIRE` (macro, line 75) `#define PV_MAX_CONTAINERS_WIRE`
  - `TAB_MAX_URL` (macro, line 78) `#define TAB_MAX_URL`
  - `TAB_MAX_WS_MSG` (macro, line 87) `#define TAB_MAX_WS_MSG`
  - `TAB_MAX_STORAGE` (macro, line 91) `#define TAB_MAX_STORAGE`
  - `TAB_MAX_HIST_OPS` (macro, line 95) `#define TAB_MAX_HIST_OPS`
  - `TAB_MAX_HIST_BYTES` (macro, line 96) `#define TAB_MAX_HIST_BYTES`
  - `TAB_MAX_OPENS` (macro, line 98) `#define TAB_MAX_OPENS`
  - `TAB_MAX_OPEN_BYTES` (macro, line 99) `#define TAB_MAX_OPEN_BYTES`
  - `TAB_MAX_GEOM_WORDS` (macro, line 102) `#define TAB_MAX_GEOM_WORDS`
  - `TAB_MAX_SUBREQ` (macro, line 112) `#define TAB_MAX_SUBREQ`
  - `TAB_MAX_SUBRESOURCE` (macro, line 113) `#define TAB_MAX_SUBRESOURCE`
  - `TAB_MAX_JS_JOBS` (macro, line 114) `#define TAB_MAX_JS_JOBS`
  - `TAB_MAX_EXTERN_CSS` (macro, line 809) `#define TAB_MAX_EXTERN_CSS`
- Depends on: `include/anti_fp.h`, `include/box_tree.h`, `include/css.h`, `include/data_url.h`, `include/dom.h`, `include/flex_layout.h`, `include/freebug.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/image_decode.h`, `include/import_map.h`, `include/js_dom.h`, `include/js_env.h`, `include/js_sandbox.h`, `include/js_trusted.h`, `include/link_nav.h`, `include/os_sandbox.h`, `include/page_view.h`, `include/request_policy.h`, `include/tab.h`, `include/url.h`, `include/util.h`, `include/web_storage.h`

## src/text_shape.c
- Doc: load_entry_file: Loads face `index` of the font file at `path` into e (FreeType + cairo + *...
- Layer: utility
- Language: c
- Symbols:
  - `tsh_entry` (struct, line 35)
  - `tsh_web` (struct, line 191)
  - `tsh_lfam` (struct, line 458)
  - `tsh_llist` (struct, line 464)
  - `tsh_fb` (struct, line 651)
  - `tsh_cover_ctx` (struct, line 734)
  - `loaded` (type_alias, line 34) `typedef struct tsh_entry { int loaded;`
  - `used` (type_alias, line 190) `typedef struct tsh_web { int used;`
  - `name` (type_alias, line 457) `typedef struct tsh_lfam { char name[TSH_FAMILY_MAX];`
  - `file` (type_alias, line 650) `typedef struct tsh_fb { char file[512];`
  - `generic_name` (function, line 55) `static const char *generic_name(int family)`
  - `backend_init` (function, line 65) `static int backend_init(void)`
  - `read_font_file` (function, line 82) `static unsigned char *read_font_file(const char *path, long *out_n)`
  - `load_entry_named` (function, line 103) `static int load_entry_named(tsh_entry *e, const char *fam, int bold, int italic)`
  - `load_entry_file` (function, line 133) `static int load_entry_file(tsh_entry *e, const char *path, int index)`
  - `load_entry` (function, line 169) `static int load_entry(tsh_entry *e, int family, int bold, int italic)`
  - `get_entry` (function, line 173) `static tsh_entry *get_entry(int family, int bold, int italic)`
  - `web_entry_free` (function, line 201) `static void web_entry_free(tsh_web *w)`
  - `web_magic_ok` (function, line 214) `static int web_magic_ok(const unsigned char *b, size_t n)`
  - `web_make_entry` (function, line 227) `static int web_make_entry(tsh_entry *e, const unsigned char *bytes, size_t nbytes)`
  - `tsh_webfont_register` (function, line 267) `int tsh_webfont_register(const char *name,
                         const unsigned char *bytes, s...`
  - `tsh_webfont_clear` (function, line 301) `void tsh_webfont_clear(void)`
  - `web_find` (function, line 306) `static tsh_entry *web_find(unsigned h, int bold, int italic)`
  - `entry_free` (function, line 318) `static void entry_free(tsh_entry *e)`
  - `ascii_ieq` (function, line 331) `static int ascii_ieq(const char *a, const char *b)`
  - `tsh_family_is_generic` (function, line 340) `int tsh_family_is_generic(const char *name)`
  - `tsh_pick_from_list` (function, line 352) `int tsh_pick_from_list(const char *list, tsh_name_resolver resolve, void *ctx,
                  ...`
  - `tsh_pick_family` (function, line 373) `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong,
        ...`
  - `fc_installed` (function, line 386) `static int fc_installed(const char *name, void *ctx)`
  - `fc_resolve` (function, line 429) `static int fc_resolve(const char *name, char *out, size_t cap, void *ctx)`
  - `local_clear` (function, line 474) `static void local_clear(void)`
  - `lfam_index` (function, line 484) `static int lfam_index(const char *fam)`
  - `tsh_local_handle` (function, line 492) `int tsh_local_handle(const char *list)`
  - `local_entry` (function, line 511) `static tsh_entry *local_entry(int handle, int bold, int italic)`
  - `get_entry_ex` (function, line 531) `static tsh_entry *get_entry_ex(const tsh_font *f)`
  - `tsh_ready` (function, line 543) `int tsh_ready(void)`
  - `tsh_shape` (function, line 548) `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                ...`
  - `utf8_next` (function, line 597) `static unsigned utf8_next(const char *s, size_t n, size_t *len)`
  - `rides_previous` (function, line 614) `static int rides_previous(unsigned cp)`
  - `tsh_segment` (function, line 622) `int tsh_segment(const char *text, size_t len, tsh_cover_fn cover, void *ctx,
                tsh_...`
  - `fb_clear` (function, line 662) `static void fb_clear(void)`
  - `fb_entry` (function, line 672) `static tsh_entry *fb_entry(unsigned cp, int bold)`
  - `cover_cp` (function, line 743) `static int cover_cp(unsigned cp, void *vctx)`
  - `shape_entry` (function, line 756) `static tsh_status shape_entry(tsh_entry *e, double px, const char *text, size_t len,
            ...`
  - `shape_runs` (function, line 787) `static tsh_status shape_runs(cairo_t *cr, const tsh_font *f, double px, double x,
               ...`
  - `tsh_measure` (function, line 829) `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)`
  - `tsh_draw` (function, line 835) `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, doub...`
  - `tsh_face` (function, line 842) `cairo_font_face_t *tsh_face(const tsh_font *f)`
  - `tsh_shutdown` (function, line 848) `void tsh_shutdown(void)`
  - `characters` (function, line 100) `* hold characters ('-', ':') that the pattern syntax treats specially. */ static int load_entry_file(tsh_entry *e...`
  - `slice` (function, line 213) `* woff2 slice (spec/webfont.md);`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
  - `TSH_MAX_FONT_BYTES` (macro, line 29) `#define TSH_MAX_FONT_BYTES`
  - `TSH_CACHE_SLOTS` (macro, line 33) `#define TSH_CACHE_SLOTS`
  - `TSH_WEB_SLOTS` (macro, line 189) `#define TSH_WEB_SLOTS`
  - `TSH_SUBS_MAX` (macro, line 400) `#define TSH_SUBS_MAX`
  - `TSH_FB_SLOTS` (macro, line 648) `#define TSH_FB_SLOTS`
  - `TSH_FB_BLOCKS` (macro, line 649) `#define TSH_FB_BLOCKS`
  - `TSH_MAX_RUNS` (macro, line 783) `#define TSH_MAX_RUNS`
- Depends on: `include/css.h`, `include/text_shape.h`, `include/webfont.h`

## src/textfield.c
- Layer: utility
- Language: c
- Symbols:
  - `whole` (function, line 6) `* the buffer is rejected whole (fail closed), never applied partially.
 */

#include "textfield.h...`
  - `tf_clear` (function, line 20) `void tf_clear(tf_field *f)`
  - `tf_set` (function, line 24) `tf_status tf_set(tf_field *f, const char *s)`
  - `tf_insert` (function, line 35) `tf_status tf_insert(tf_field *f, char c)`
  - `tf_backspace` (function, line 47) `void tf_backspace(tf_field *f)`
  - `tf_delete` (function, line 55) `void tf_delete(tf_field *f)`
  - `tf_move` (function, line 62) `void tf_move(tf_field *f, long delta)`
  - `tf_home` (function, line 73) `void tf_home(tf_field *f)`
  - `tf_end` (function, line 78) `void tf_end(tf_field *f)`
  - `tf_text` (function, line 83) `const char *tf_text(const tf_field *f)`
  - `tf_len` (function, line 87) `size_t tf_len(const tf_field *f)`
  - `tf_cursor` (function, line 91) `size_t tf_cursor(const tf_field *f)`
- Depends on: `include/textfield.h`

## src/tls_impersonate.c
- Doc: get_bytes: | ((uint32_t)r->p[r->off + 3] << 24); r->off += 4; return v; } static uint64_t...
- Layer: utility
- Language: c
- Symbols:
  - `ti_wr` (struct, line 33)
  - `ti_rd` (struct, line 63)
  - `ti_should_impersonate` (function, line 18) `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,
                          i...`
  - `bounded_len` (function, line 25) `static size_t bounded_len(const char *s, size_t max)`
  - `put_u8` (function, line 35) `static void put_u8(ti_wr *w, uint8_t v)`
  - `put_u32` (function, line 40) `static void put_u32(ti_wr *w, uint32_t v)`
  - `put_u64` (function, line 48) `static void put_u64(ti_wr *w, uint64_t v)`
  - `put_blob` (function, line 53) `static void put_blob(ti_wr *w, const uint8_t *b, size_t n)`
  - `get_u8` (function, line 65) `static uint8_t get_u8(ti_rd *r)`
  - `get_u32` (function, line 70) `static uint32_t get_u32(ti_rd *r)`
  - `get_u64` (function, line 80) `static uint64_t get_u64(ti_rd *r)`
  - `get_bytes` (function, line 89) `static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len)`
  - `get_str` (function, line 103) `static char *get_str(ti_rd *r, size_t cap)`
  - `valid_profile` (function, line 116) `static int valid_profile(int p)`
  - `ti_encode_req` (function, line 122) `size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap)`
  - `ti_decode_req` (function, line 140) `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out)`
  - `ti_req_free` (function, line 166) `void ti_req_free(ti_req *r)`
  - `ti_encode_resp` (function, line 177) `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap)`
  - `ti_decode_resp` (function, line 196) `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out)`
  - `ti_resp_free` (function, line 230) `void ti_resp_free(ti_resp *r)`
- Depends on: `include/tls_impersonate.h`

## src/ui_layout.c
- Layer: presentation
- Language: c
- Symbols:
  - `layout_push` (function, line 13) `static int layout_push(ui_layout *lay, size_t offset, size_t len)`
  - `ui_wrap_text` (function, line 27) `ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out)`
  - `ui_layout_free` (function, line 91) `void ui_layout_free(ui_layout *lay)`
  - `ui_clamp_scroll` (function, line 99) `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines)`
- Depends on: `include/ui.h`


Next: [KB_src_p8.md](KB_src_p8.md)
