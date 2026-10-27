# Subsystem: src (page 8 of 10)
Previous: [KB_src_p7.md](KB_src_p7.md)

## src/prefetch.c
- Doc: ci_starts: static int is_ws(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' ||...
- Layer: utility
- Language: c
- Symbols:
  - `attr_span` (struct, line 65)
  - `is_ws` (function, line 26) `static int is_ws(char c)`
  - `is_name_char` (function, line 30) `static int is_name_char(char c)`
  - `lower` (function, line 35) `static int lower(int c)`
  - `ci_starts` (function, line 40) `static int ci_starts(const char *p, const char *end, const char *kw)`
  - `ci_find` (function, line 49) `static const char *ci_find(const char *p, const char *end, const char *kw)`
  - `ci_eq_span` (function, line 58) `static int ci_eq_span(const char *s, size_t n, const char *kw)`
  - `emit` (function, line 120) `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)`
  - `pf_scan` (function, line 133) `int pf_scan(const char *html, size_t len, pf_list *out)`
  - `pf_list_free` (function, line 196) `void pf_list_free(pf_list *l)`
  - `js_ident_ch` (function, line 207) `static int js_ident_ch(char c)`
  - `js_skip_ws` (function, line 212) `static size_t js_skip_ws(const char *s, size_t i, size_t n)`
  - `js_skip_string` (function, line 219) `static size_t js_skip_string(const char *s, size_t i, size_t n)`
  - `js_take_spec` (function, line 226) `static void js_take_spec(const char *s, size_t i, size_t n,
                         char (*out)[...`
  - `pf_scan_imports` (function, line 241) `size_t pf_scan_imports(const char *js, size_t len, char (*out)[PF_SPEC_MAX], size_t cap)`
  - `pf_pool_add` (function, line 288) `int pf_pool_add(pf_pool *p, const char *url)`
  - `pf_is_js` (function, line 311) `static int pf_is_js(const char *url, const char *ctype)`
  - `pf_url_cb` (function, line 319) `static int pf_url_cb(void *ctx, const char *base, const char *ref, char *out, size_t outsz)`
  - `pf_url_shaped` (function, line 324) `static int pf_url_shaped(const char *sp)`
  - `pf_follow_imports` (function, line 333) `static void pf_follow_imports(pf_pool *p, const char *base, const char *body, size_t len)`
  - `pf_worker` (function, line 349) `static void *pf_worker(void *arg)`
  - `pf_pool_start` (function, line 387) `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                  pf_fetch_f...`
  - `pool_start` (function, line 394) `static int pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                      pf...`
  - `pf_pool_take` (function, line 444) `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,
                 char **body,...`
  - `pf_find_importmap` (function, line 483) `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n)`
  - `pf_pool_start_page` (function, line 504) `int pf_pool_start_page(pf_pool *p, const char *html, size_t len, const char *page_url,
          ...`
  - `pf_pool_finish` (function, line 540) `void pf_pool_finish(pf_pool *p)`
  - `pf_pooled_fetch` (function, line 561) `int pf_pooled_fetch(void *vctx, const char *method, const char *url,
                    const ch...`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
  - `PF_MAX_URL` (macro, line 24) `#define PF_MAX_URL`
- Depends on: `include/import_map.h`, `include/prefetch.h`, `include/url.h`

## src/prefs.c
- Doc: url_valid: A representable URL: 1..PREFS_MAX_URL-1 bytes, no control bytes, no DEL. * Space is...
- Layer: utility
- Language: c
- Symbols:
  - `sbuf` (struct, line 380)
  - `url_valid` (function, line 26) `static int url_valid(const char *url)`
  - `title_clean` (function, line 39) `static char *title_clean(const char *src)`
  - `prefs_init` (function, line 66) `void prefs_init(prefs_state *p)`
  - `prefs_free` (function, line 74) `void prefs_free(prefs_state *p)`
  - `bookmark_push` (function, line 91) `static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title)`
  - `history_push_back` (function, line 109) `static prefs_status history_push_back(prefs_state *p, const char *url)`
  - `prefs_bookmark_index` (function, line 125) `int prefs_bookmark_index(const prefs_state *p, const char *url)`
  - `prefs_bookmark_toggle` (function, line 132) `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,
                             ...`
  - `prefs_history_add` (function, line 152) `prefs_status prefs_history_add(prefs_state *p, const char *url)`
  - `prefs_format` (function, line 183) `prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len)`
  - `apply_kv` (function, line 231) `static void apply_kv(prefs_state *out, const char *key, long val)`
  - `prefs_parse` (function, line 247) `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)`
  - `ci_eq` (function, line 313) `static int ci_eq(char a, char b)`
  - `ci_starts` (function, line 319) `static int ci_starts(const char *s, const char *q)`
  - `ci_contains` (function, line 327) `static int ci_contains(const char *s, const char *q)`
  - `url_prefix_match` (function, line 336) `static int url_prefix_match(const char *url, const char *q)`
  - `sugg_push` (function, line 348) `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,
                      cons...`
  - `prefs_suggest` (function, line 357) `int prefs_suggest(const prefs_state *p, const char *query,
                  char *out, size_t ro...`
  - `sb_put` (function, line 382) `static void sb_put(sbuf *b, const char *s, size_t n)`
  - `sb_str` (function, line 397) `static void sb_str(sbuf *b, const char *s)`
  - `sb_esc` (function, line 400) `static void sb_esc(sbuf *b, const char *s)`
  - `sb_link_item` (function, line 413) `static void sb_link_item(sbuf *b, const char *url, const char *label)`
  - `prefs_bookmarks_page` (function, line 421) `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)`
  - `_POSIX_C_SOURCE` (macro, line 11) `#define _POSIX_C_SOURCE`
  - `PREFS_MAGIC` (macro, line 20) `#define PREFS_MAGIC`
- Depends on: `include/prefs.h`, `include/zoom.h`

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
  - `rd_push_input` (function, line 212) `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)`
  - `resolve_image_decision` (function, line 248) `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,
        ...`
  - `rd_build` (function, line 270) `rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_u...`
  - `unset` (function, line 681) `* background paints as if unset (no border/box-shadow-style
                 * "broken image" pla...`
  - `rd_free` (function, line 746) `void rd_free(rd_doc *d)`
  - `rd_count` (function, line 763) `size_t rd_count(const rd_doc *d)`
  - `rd_at` (function, line 767) `const rd_block *rd_at(const rd_doc *d, size_t i)`
  - `rd_box_count` (function, line 772) `size_t rd_box_count(const rd_doc *d)`
  - `rd_box_at` (function, line 776) `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)`
  - `rd_cont_count` (function, line 781) `size_t rd_cont_count(const rd_doc *d)`
  - `rd_cont_at` (function, line 785) `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)`
  - `rd_kind_name` (function, line 790) `const char *rd_kind_name(rd_kind k)`
  - `rd_block_heading_level` (function, line 804) `int rd_block_heading_level(const rd_block *b)`
  - `rd_block_tag` (function, line 815) `const char *rd_block_tag(const rd_block *b)`
  - `rd_input_label` (function, line 846) `const char *rd_input_label(int input_type)`
  - `rd_input_invisible` (function, line 866) `int rd_input_invisible(int input_type)`
  - `rd_image_label` (function, line 870) `const char *rd_image_label(rdp_img_decision d)`
  - `rd_image_fail_label` (function, line 881) `const char *rd_image_fail_label(img_fail_reason reason)`
  - `place` (function, line 238) `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never...`
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
  - `body_sink` (struct, line 490)
  - `tls_capture` (struct, line 503)
  - `fetch_ctx` (struct, line 513)
  - `sf_ws` (struct, line 1332)
  - `sf_rcache_entry` (struct, line 1167)
  - `sink` (type_alias, line 512) `typedef struct fetch_ctx { body_sink sink;`
  - `ci_starts_with` (function, line 46) `static int ci_starts_with(const char *haystack, const char *prefix)`
  - `ci_index` (function, line 58) `static long ci_index(const char *haystack, const char *needle)`
  - `sf_share_lock` (function, line 74) `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...`
  - `sf_share_unlock` (function, line 80) `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)`
  - `sf_global_init` (function, line 87) `void sf_global_init(void)`
  - `sf_cookie_line_matches` (function, line 112) `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...`
  - `sf_url_host_path` (function, line 167) `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...`
  - `sf_cookie_header_for` (function, line 182) `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)`
  - `sf_cookie_put` (function, line 211) `void sf_cookie_put(const char *url, const char *namevalue)`
  - `sf_config_default` (function, line 232) `sf_config sf_config_default(void)`
  - `header_value_clean` (function, line 258) `static int header_value_clean(const char *s)`
  - `sf_user_agent_or_default` (function, line 264) `const char *sf_user_agent_or_default(const char *ua)`
  - `sf_accept_language_or_default` (function, line 268) `const char *sf_accept_language_or_default(const char *lang)`
  - `sf_impersonate_kex_groups` (function, line 272) `const char *sf_impersonate_kex_groups(void)`
  - `sf_impersonate_tls13_ciphers` (function, line 273) `const char *sf_impersonate_tls13_ciphers(void)`
  - `sf_validate_url` (function, line 277) `sf_status sf_validate_url(const char *url)`
  - `sf_url_is_http` (function, line 285) `static int sf_url_is_http(const char *url)`
  - `sf_check_tls_version` (function, line 297) `sf_status sf_check_tls_version(const char *negotiated_version)`
  - `sf_check_group_is_pq` (function, line 302) `sf_status sf_check_group_is_pq(const char *negotiated_group)`
  - `sf_check_chain_policy` (function, line 311) `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)`
  - `sf_enforce_policy` (function, line 321) `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...`
  - `copy_checked` (function, line 352) `static int copy_checked(char *dst, size_t dstsz, const char *src)`
  - `sf_is_redirect_code` (function, line 361) `int sf_is_redirect_code(long http_code)`
  - `sf_header_value` (function, line 368) `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz)`
  - `sf_parse_location_header` (function, line 390) `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)`
  - `sf_resolve_redirect` (function, line 408) `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...`
  - `sf_ci_prefix` (function, line 420) `static int sf_ci_prefix(const char *s, const char *p)`
  - `sf_response_free` (function, line 460) `void sf_response_free(sf_response *resp)`
  - `copy_bounded` (function, line 530) `static void copy_bounded(char *dst, size_t dstsz, const char *src)`
  - `get_negotiated_group_name` (function, line 541) `static const char *get_negotiated_group_name(SSL *ssl)`
  - `tls_capture_try` (function, line 574) `static void tls_capture_try(tls_capture *cap)`
  - `tls_capture_from_ssl` (function, line 584) `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)`
  - `header_cb` (function, line 610) `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)`
  - `write_cb` (function, line 667) `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)`
  - `name_is_pq_sig` (function, line 699) `static int name_is_pq_sig(int pknid)`
  - `inspect_chain` (function, line 709) `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)`
  - `map_curl_error` (function, line 762) `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)`
  - `add_header` (function, line 803) `static int add_header(struct curl_slist **h, const char *line)`
  - `sf_setup_handle` (function, line 817) `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,
           ...`
  - `redirect` (function, line 892) `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...`
  - `sf_perform` (function, line 984) `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...`
  - `sf_get` (function, line 1144) `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)`
  - `sf_post` (function, line 1148) `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...`
  - `sf_rcache_clear` (function, line 1178) `void sf_rcache_clear(void)`
  - `sf_rcache_set_backing` (function, line 1189) `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx)`
  - `rcache_put_ram` (function, line 1197) `static int rcache_put_ram(const char *from, const char *to, time_t now)`
  - `sf_rcache_put` (function, line 1216) `int sf_rcache_put(const char *from, const char *to, time_t now)`
  - `sf_rcache_get` (function, line 1226) `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap)`
  - `sf_get_follow` (function, line 1255) `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...`
  - `ws_ssl_info_cb` (function, line 1318) `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)`
  - `ws_ssl_ctx_cb` (function, line 1325) `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)`
  - `sf_ws_url_check` (function, line 1339) `sf_status sf_ws_url_check(const char *url)`
  - `ws_free` (function, line 1351) `static void ws_free(sf_ws *ws)`
  - `sf_ws_open` (function, line 1360) `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)`
  - `sf_ws_send` (function, line 1415) `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)`
  - `sf_ws_recv` (function, line 1438) `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)`
  - `sf_ws_fd` (function, line 1460) `int sf_ws_fd(const sf_ws *ws)`
  - `sf_ws_close` (function, line 1467) `void sf_ws_close(sf_ws *ws)`
  - `sf_fallback_policy` (function, line 1478) `int sf_fallback_policy(sf_status failed, sf_policy tried, int allowlisted, sf_policy *next)`
  - `sf_downgrade_of` (function, line 1492) `static int sf_downgrade_of(sf_policy p)`
  - `sf_attempt_get` (function, line 1501) `static sf_status sf_attempt_get(const char *url, const sf_config *cfg, sf_response *out,
        ...`
  - `sf_attempt_post` (function, line 1507) `static sf_status sf_attempt_post(const char *url, const sf_config *cfg, sf_response *out,
       ...`
  - `sf_navigable` (function, line 1512) `static sf_status sf_navigable(sf_attempt_fn attempt, const char *url, sf_config *cfg,
           ...`
  - `sf_get_follow_navigable` (function, line 1532) `sf_status sf_get_follow_navigable(const char *url, sf_config *cfg, sf_response *out,
            ...`
  - `sf_post_navigable` (function, line 1537) `sf_status sf_post_navigable(const char *url, sf_config *cfg, const void *body,
                  ...`
  - `module` (function, line 413) `* pure url module (DRY);`
  - `progress` (function, line 499) `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);`
  - `database` (function, line 545) `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid...`
  - `group` (function, line 559) `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);`
  - `this` (function, line 591) `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and...`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
  - `SF_RCACHE_SLOTS` (macro, line 1164) `#define SF_RCACHE_SLOTS`
  - `SF_RCACHE_TTL_S` (macro, line 1165) `#define SF_RCACHE_TTL_S`
- Depends on: `include/anti_fp.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/url.h`

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
