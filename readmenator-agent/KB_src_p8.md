# Subsystem: src (page 8 of 10)
Previous: [KB_src_p7.md](KB_src_p7.md)

## src/profile.c
- Doc: keyfile_create: #include <unistd.h> #include <openssl/crypto.h> #include <openssl/rand.h>...
- Layer: utility
- Language: c
- Symbols:
  - `join_path` (function, line 29) `static int join_path(const profile_ctx *ctx, const char *name,
                     char *out, si...`
  - `keyfile_create` (function, line 36) `static profile_status keyfile_create(const char *dir, const char *path,
                         ...`
  - `profile_open` (function, line 59) `profile_status profile_open(profile_ctx *ctx, const char *dir)`
  - `map_ds` (function, line 98) `static profile_status map_ds(ds_status ds)`
  - `profile_load` (function, line 112) `profile_status profile_load(const profile_ctx *ctx, prefs_state *out)`
  - `profile_save` (function, line 133) `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p)`
  - `profile_close` (function, line 149) `void profile_close(profile_ctx *ctx)`
  - `_POSIX_C_SOURCE` (macro, line 11) `#define _POSIX_C_SOURCE`
  - `PROFILE_KEYFILE_LEN` (macro, line 27) `#define PROFILE_KEYFILE_LEN`
- Depends on: `include/disk_store.h`, `include/profile.h`

## src/render_doc.c
- Doc: rd_push: Appends one block, taking owned copies of text (required) and href (optional). *...
- Layer: presentation
- Language: c
- Symbols:
  - `utf8_sanitized_dup` (function, line 28) `static char *utf8_sanitized_dup(const char *s)`
  - `rd_push` (function, line 60) `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,
                 ...`
  - `rd_push_input` (function, line 214) `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)`
  - `resolve_image_decision` (function, line 250) `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,
        ...`
  - `too` (function, line 281) `* that would not fit is cleared too (never truncated-and-fetched). */
static void gate_box_image_...`
  - `rd_build` (function, line 293) `rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_u...`
  - `rd_free` (function, line 744) `void rd_free(rd_doc *d)`
  - `rd_count` (function, line 761) `size_t rd_count(const rd_doc *d)`
  - `rd_at` (function, line 765) `const rd_block *rd_at(const rd_doc *d, size_t i)`
  - `rd_box_count` (function, line 770) `size_t rd_box_count(const rd_doc *d)`
  - `rd_box_at` (function, line 774) `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)`
  - `rd_cont_count` (function, line 779) `size_t rd_cont_count(const rd_doc *d)`
  - `rd_cont_at` (function, line 783) `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)`
  - `rd_kind_name` (function, line 788) `const char *rd_kind_name(rd_kind k)`
  - `rd_block_heading_level` (function, line 802) `int rd_block_heading_level(const rd_block *b)`
  - `rd_block_tag` (function, line 813) `const char *rd_block_tag(const rd_block *b)`
  - `rd_input_label` (function, line 844) `const char *rd_input_label(int input_type)`
  - `rd_input_invisible` (function, line 864) `int rd_input_invisible(int input_type)`
  - `rd_image_label` (function, line 868) `const char *rd_image_label(rdp_img_decision d)`
  - `rd_image_fail_label` (function, line 879) `const char *rd_image_fail_label(img_fail_reason reason)`
  - `place` (function, line 240) `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never...`
  - `unset` (function, line 706) `* background paints as if unset (no border/box-shadow-style * "broken image" placeholder) -- it is decoration, not...`
- Depends on: `include/box_style.h`, `include/css.h`, `include/data_url.h`, `include/render_doc.h`, `include/url.h`, `include/util.h`

## src/render_policy.c
- Layer: presentation
- Language: c
- Symbols:
  - `rdp_caps_safe` (function, line 17) `rdp_caps rdp_caps_safe(void)`
  - `rdp_is_tracking_pixel` (function, line 22) `int rdp_is_tracking_pixel(int w, int h)`
  - `rdp_image_decision` (function, line 28) `rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char...`
  - `rdp_img_reason` (function, line 60) `const char *rdp_img_reason(rdp_img_decision d)`
  - `rdp_images_warning` (function, line 71) `const char *rdp_images_warning(void)`
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
  - `hdr_lower` (function, line 162) `static int hdr_lower(int c)`
  - `hdr_name_ieq` (function, line 164) `static int hdr_name_ieq(const char *a, size_t alen, const char *lit)`
  - `hdr_name_has_prefix` (function, line 171) `static int hdr_name_has_prefix(const char *a, size_t alen, const char *lit)`
  - `hdr_token_char` (function, line 178) `static int hdr_token_char(unsigned char c)`
  - `hdr_forbidden` (function, line 184) `static int hdr_forbidden(const char *n, size_t len)`
  - `rp_sanitize_request_headers` (function, line 197) `int rp_sanitize_request_headers(const char *raw, char *out, size_t cap)`
  - `RP_MAX_HOST` (macro, line 17) `#define RP_MAX_HOST`
  - `RP_MAX_LABELS` (macro, line 18) `#define RP_MAX_LABELS`
- Depends on: `include/psl_data.h`, `include/request_policy.h`

## src/secure_fetch.c
- Doc: tls_capture: Snapshot of the negotiated TLS state. curl exposes the live SSL* only while a...
- Layer: utility
- Language: c
- Symbols:
  - `body_sink` (struct, line 497)
  - `tls_capture` (struct, line 510)
  - `fetch_ctx` (struct, line 522)
  - `sf_ws` (struct, line 1432)
  - `sf_rcache_entry` (struct, line 1258)
  - `sink` (type_alias, line 521) `typedef struct fetch_ctx { body_sink sink;`
  - `ci_starts_with` (function, line 49) `static int ci_starts_with(const char *haystack, const char *prefix)`
  - `ci_index` (function, line 61) `static long ci_index(const char *haystack, const char *needle)`
  - `sf_share_lock` (function, line 77) `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...`
  - `sf_share_unlock` (function, line 83) `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)`
  - `sf_global_init` (function, line 90) `void sf_global_init(void)`
  - `sf_cookie_line_matches` (function, line 118) `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...`
  - `sf_url_host_path` (function, line 173) `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...`
  - `sf_cookie_header_for` (function, line 188) `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)`
  - `sf_cookie_put` (function, line 217) `void sf_cookie_put(const char *url, const char *namevalue)`
  - `sf_config_default` (function, line 238) `sf_config sf_config_default(void)`
  - `header_value_clean` (function, line 265) `static int header_value_clean(const char *s)`
  - `sf_user_agent_or_default` (function, line 271) `const char *sf_user_agent_or_default(const char *ua)`
  - `sf_accept_language_or_default` (function, line 275) `const char *sf_accept_language_or_default(const char *lang)`
  - `sf_impersonate_kex_groups` (function, line 279) `const char *sf_impersonate_kex_groups(void)`
  - `sf_impersonate_tls13_ciphers` (function, line 280) `const char *sf_impersonate_tls13_ciphers(void)`
  - `sf_validate_url` (function, line 284) `sf_status sf_validate_url(const char *url)`
  - `sf_url_is_http` (function, line 292) `static int sf_url_is_http(const char *url)`
  - `sf_check_tls_version` (function, line 304) `sf_status sf_check_tls_version(const char *negotiated_version)`
  - `sf_check_group_is_pq` (function, line 309) `sf_status sf_check_group_is_pq(const char *negotiated_group)`
  - `sf_check_chain_policy` (function, line 318) `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)`
  - `sf_enforce_policy` (function, line 328) `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...`
  - `copy_checked` (function, line 359) `static int copy_checked(char *dst, size_t dstsz, const char *src)`
  - `sf_is_redirect_code` (function, line 368) `int sf_is_redirect_code(long http_code)`
  - `sf_header_value` (function, line 375) `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz)`
  - `sf_parse_location_header` (function, line 397) `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)`
  - `sf_resolve_redirect` (function, line 415) `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...`
  - `sf_ci_prefix` (function, line 427) `static int sf_ci_prefix(const char *s, const char *p)`
  - `sf_response_free` (function, line 467) `void sf_response_free(sf_response *resp)`
  - `copy_bounded` (function, line 544) `static void copy_bounded(char *dst, size_t dstsz, const char *src)`
  - `get_negotiated_group_name` (function, line 555) `static const char *get_negotiated_group_name(SSL *ssl)`
  - `tls_capture_try` (function, line 588) `static void tls_capture_try(tls_capture *cap)`
  - `tls_capture_from_ssl` (function, line 598) `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)`
  - `header_cb` (function, line 624) `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)`
  - `write_cb` (function, line 681) `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)`
  - `name_is_pq_sig` (function, line 713) `static int name_is_pq_sig(int pknid)`
  - `inspect_chain` (function, line 723) `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)`
  - `refused` (function, line 781) `* a private peer is then refused (fail closed). */
static void sf_guard_init(fetch_ctx *ctx, cons...`
  - `sf_guard_opensocket` (function, line 808) `static curl_socket_t sf_guard_opensocket(void *clientp, curlsocktype purpose,
                   ...`
  - `sf_guard_prereq` (function, line 835) `static int sf_guard_prereq(void *clientp, char *conn_primary_ip, char *conn_local_ip,
           ...`
  - `map_curl_error` (function, line 846) `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)`
  - `add_header` (function, line 887) `static int add_header(struct curl_slist **h, const char *line)`
  - `sf_setup_handle` (function, line 901) `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,
           ...`
  - `redirect` (function, line 983) `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...`
  - `sf_perform` (function, line 1075) `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...`
  - `sf_get` (function, line 1235) `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)`
  - `sf_post` (function, line 1239) `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...`
  - `sf_rcache_clear` (function, line 1269) `void sf_rcache_clear(void)`
  - `sf_rcache_set_backing` (function, line 1280) `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx)`
  - `rcache_put_ram` (function, line 1288) `static int rcache_put_ram(const char *from, const char *to, time_t now)`
  - `sf_rcache_put` (function, line 1307) `int sf_rcache_put(const char *from, const char *to, time_t now)`
  - `sf_rcache_get` (function, line 1317) `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap)`
  - `sf_get_follow` (function, line 1346) `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...`
  - `ws_ssl_info_cb` (function, line 1418) `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)`
  - `ws_ssl_ctx_cb` (function, line 1425) `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)`
  - `sf_ws_url_check` (function, line 1439) `sf_status sf_ws_url_check(const char *url)`
  - `ws_free` (function, line 1451) `static void ws_free(sf_ws *ws)`
  - `sf_ws_open` (function, line 1460) `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)`
  - `sf_ws_send` (function, line 1515) `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)`
  - `sf_ws_recv` (function, line 1538) `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)`
  - `sf_ws_fd` (function, line 1560) `int sf_ws_fd(const sf_ws *ws)`
  - `sf_ws_close` (function, line 1567) `void sf_ws_close(sf_ws *ws)`
  - `sf_fallback_policy` (function, line 1578) `int sf_fallback_policy(sf_status failed, sf_policy tried, int allowlisted, sf_policy *next)`
  - `sf_downgrade_of` (function, line 1595) `static int sf_downgrade_of(sf_policy p)`
  - `sf_attempt_get` (function, line 1604) `static sf_status sf_attempt_get(const char *url, const sf_config *cfg, sf_response *out,
        ...`
  - `sf_attempt_post` (function, line 1610) `static sf_status sf_attempt_post(const char *url, const sf_config *cfg, sf_response *out,
       ...`
  - `sf_navigable` (function, line 1615) `static sf_status sf_navigable(sf_attempt_fn attempt, const char *url, sf_config *cfg,
           ...`
  - `sf_get_follow_navigable` (function, line 1635) `sf_status sf_get_follow_navigable(const char *url, sf_config *cfg, sf_response *out,
            ...`
  - `sf_post_navigable` (function, line 1640) `sf_status sf_post_navigable(const char *url, sf_config *cfg, const void *body,
                  ...`
  - `module` (function, line 420) `* pure url module (DRY);`
  - `progress` (function, line 506) `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);`
  - `database` (function, line 559) `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid...`
  - `group` (function, line 573) `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);`
  - `this` (function, line 605) `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and...`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
  - `SF_GUARD_HOST_MAX` (macro, line 520) `#define SF_GUARD_HOST_MAX`
  - `SF_RCACHE_SLOTS` (macro, line 1255) `#define SF_RCACHE_SLOTS`
  - `SF_RCACHE_TTL_S` (macro, line 1256) `#define SF_RCACHE_TTL_S`
- Depends on: `include/anti_fp.h`, `include/net_guard.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/url.h`

## src/sha2.c
- Doc: pad_tail: Pads the tail of a message into at most two blocks of `bs` bytes with a...
- Layer: utility
- Language: c
- Symbols:
  - `sha_digest_len` (function, line 12) `size_t sha_digest_len(sha_alg alg)`
  - `ieq` (function, line 22) `static int ieq(const char *a, const char *b)`
  - `sha_alg_from_name` (function, line 31) `int sha_alg_from_name(const char *name, sha_alg *out)`
  - `be32` (function, line 40) `static uint32_t be32(const uint8_t *p)`
  - `be64` (function, line 43) `static uint64_t be64(const uint8_t *p)`
  - `put32` (function, line 44) `static void put32(uint8_t *p, uint32_t v)`
  - `put64` (function, line 45) `static void put64(uint8_t *p, uint64_t v)`
  - `pad_tail` (function, line 49) `static size_t pad_tail(uint8_t *blk, size_t bs, size_t lenbytes, const uint8_t *tail, size_t tl,
...`
  - `sha1_block` (function, line 61) `static void sha1_block(uint32_t h[5], const uint8_t *p)`
  - `sha256_block` (function, line 88) `static void sha256_block(uint32_t h[8], const uint8_t *p)`
  - `sha512_block` (function, line 131) `static void sha512_block(uint64_t h[8], const uint8_t *p)`
  - `sha_digest` (function, line 152) `int sha_digest(sha_alg alg, const void *data, size_t len, uint8_t *out)`
  - `ROR32` (macro, line 8) `#define ROR32(x, n)`
  - `ROL32` (macro, line 9) `#define ROL32(x, n)`
  - `ROR64` (macro, line 10) `#define ROR64(x, n)`
- Depends on: `include/sha2.h`

## src/sheet_cache.c
- Doc: sheet_cache -- see include/sheet_cache.h and spec/sheet_cache.md.
- Layer: infrastructure
- Language: c
- Symbols:
  - `shc_query` (struct, line 12)
  - `shc_sheet` (struct, line 17)
  - `shc_cache` (struct, line 30)
  - `shc_probe` (struct, line 39)
  - `shc_probe_match` (function, line 47) `static int shc_probe_match(void *ctx, const struct css_sel *sel)`
  - `shc_queries_free` (function, line 67) `static void shc_queries_free(shc_query *q, size_t n)`
  - `shc_dup` (function, line 72) `static char *shc_dup(const char *src, size_t len)`
  - `shc_sheet_destroy` (function, line 81) `static void shc_sheet_destroy(shc_sheet *s)`
  - `shc_new` (function, line 89) `shc_cache *shc_new(size_t max_text_bytes)`
  - `shc_release` (function, line 96) `void shc_release(shc_sheet *s)`
  - `shc_free` (function, line 101) `void shc_free(shc_cache *c)`
  - `shc_css` (function, line 107) `const css_sheet *shc_css(const shc_sheet *s)`
  - `shc_stats_get` (function, line 111) `void shc_stats_get(const shc_cache *c, shc_stats *out)`
  - `shc_key_matches` (function, line 117) `static int shc_key_matches(const shc_sheet *s, const shc_key *k)`
  - `shc_key_store` (function, line 136) `static int shc_key_store(shc_sheet *s, const shc_key *k)`
  - `shc_acquire` (function, line 155) `shc_sheet *shc_acquire(shc_cache *cache, const shc_key *key)`
- Depends on: `include/css_select.h`, `include/freedom_config.h`, `include/sheet_cache.h`

## src/subreq_batch.c
- Doc: subreq_batch -- see include/subreq_batch.h and spec/subreq_async.md.
- Layer: utility
- Language: c
- Symbols:
  - `sqb_job` (struct, line 11)
  - `sqb` (struct, line 21)
  - `dup_n` (function, line 30) `static char *dup_n(const char *s, size_t n)`
  - `res_clear` (function, line 39) `static void res_clear(sqb_res *r)`
  - `job_free` (function, line 44) `static void job_free(sqb_job *j)`
  - `job_main` (function, line 51) `static void *job_main(void *arg)`
  - `sqb_new` (function, line 75) `sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx)`
  - `sqb_submit` (function, line 86) `int sqb_submit(sqb *b, int refused, const sqb_req *req)`
  - `sqb_count` (function, line 112) `size_t sqb_count(const sqb *b)`
  - `sqb_wait_all` (function, line 114) `void sqb_wait_all(sqb *b)`
  - `sqb_result` (function, line 122) `const sqb_res *sqb_result(const sqb *b, size_t i)`
  - `sqb_reset` (function, line 126) `void sqb_reset(sqb *b)`
  - `sqb_free` (function, line 133) `void sqb_free(sqb *b)`
  - `_GNU_SOURCE` (macro, line 2) `#define _GNU_SOURCE`
- Depends on: `include/subreq_batch.h`

## src/svg_paint.c
- Doc: svg_paint — Cairo back end for the shapes svg_render extracted.
- Layer: utility
- Language: c
- Symbols:
  - `svp_alpha` (function, line 31) `static double svp_alpha(int opacity, int paint_opacity)`
  - `svp_rect_path` (function, line 38) `static void svp_rect_path(cairo_t *cr, const sv_shape *sh)`
  - `svp_shape_path` (function, line 73) `static void svp_shape_path(cairo_t *cr, const sv_image *img, const sv_shape *sh)`
  - `svp_draw_text` (function, line 126) `static void svp_draw_text(cairo_t *cr, const sv_shape *sh, int current_rgb)`
  - `svp_draw` (function, line 139) `void svp_draw(cairo_t *cr, const sv_image *img,
              double x, double y, double w, doubl...`
  - `svp_draw_ex` (function, line 144) `void svp_draw_ex(cairo_t *cr, const sv_image *img,
                 double x, double y, double w,...`
- Depends on: `include/css_color.h`, `include/freedom_config.h`, `include/svg_paint.h`

## src/svg_raster.c
- Doc: svg_raster -- SVG served as an image, rasterized inside the confined worker. spec/svg_raster.md.
- Layer: utility
- Language: c
- Symbols:
  - `sr_ws` (function, line 14) `static int sr_ws(uint8_t c)`
  - `sr_skip_past` (function, line 18) `static size_t sr_skip_past(const uint8_t *b, size_t i, size_t n, const char *end)`
  - `sr_sniff` (function, line 25) `int sr_sniff(const uint8_t *bytes, size_t len)`
  - `sr_rasterize` (function, line 50) `img_status sr_rasterize(const uint8_t *bytes, size_t len, img_pixels *out)`
- Depends on: `include/svg_paint.h`, `include/svg_raster.h`, `include/svg_render.h`

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
  - `sv_flag` (function, line 477) `static int sv_flag(const char *s, size_t n, size_t *i, double *out)`
  - `sv_parse_path` (function, line 488) `static void sv_parse_path(sv_image *im, sv_shape *sh, const char *s, size_t n)`
  - `sv_is_dropped_element` (function, line 646) `static int sv_is_dropped_element(const char *name, size_t n)`
  - `sv_scan_attrs` (function, line 658) `static void sv_scan_attrs(const char *s, size_t n, size_t *i,
                          sv_attr *...`
  - `sv_skip_subtree` (function, line 704) `static void sv_skip_subtree(const char *s, size_t n, size_t *i, const char *name, size_t nlen)`
  - `sv_collect_text` (function, line 736) `static void sv_collect_text(const char *s, size_t n, size_t *i, char *dst, size_t cap)`
  - `sv_fit` (function, line 754) `void sv_fit(const sv_image *img, double dw, double dh,
            double *scale, double *off_x, ...`
  - `sv_parse` (function, line 774) `sv_status sv_parse(const char *markup, size_t len, sv_image *out)`
  - `sv_parse_ex` (function, line 778) `sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill)`
  - `point` (function, line 567) `* current point (SVG 8.3.6). */ int had = (prev == 'C' || prev == 'c' || prev == 'S' || prev == 's');`
  - `SV_MAX_ATTRS` (macro, line 96) `#define SV_MAX_ATTRS`
- Depends on: `include/css_color.h`, `include/svg_render.h`


Next: [KB_src_p9.md](KB_src_p9.md)
