# Symbols (page 10 of 17)
Previous: [SYMBOLS_p9.md](SYMBOLS_p9.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `bookmark_push` | function | `src/prefs.c:91` | `static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title)` |
| `ci_contains` | function | `src/prefs.c:327` | `static int ci_contains(const char *s, const char *q)` |
| `ci_eq` | function | `src/prefs.c:313` | `static int ci_eq(char a, char b)` |
| `ci_starts` | function | `src/prefs.c:319` | `static int ci_starts(const char *s, const char *q)` |
| `history_push_back` | function | `src/prefs.c:109` | `static prefs_status history_push_back(prefs_state *p, const char *url)` |
| `prefs_bookmark_index` | function | `src/prefs.c:125` | `int prefs_bookmark_index(const prefs_state *p, const char *url)` |
| `prefs_bookmark_toggle` | function | `src/prefs.c:132` | `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,                              ...` |
| `prefs_bookmarks_page` | function | `src/prefs.c:421` | `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)` |
| `prefs_format` | function | `src/prefs.c:183` | `prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len)` |
| `prefs_free` | function | `src/prefs.c:74` | `void prefs_free(prefs_state *p)` |
| `prefs_history_add` | function | `src/prefs.c:152` | `prefs_status prefs_history_add(prefs_state *p, const char *url)` |
| `prefs_init` | function | `src/prefs.c:66` | `void prefs_init(prefs_state *p)` |
| `prefs_parse` | function | `src/prefs.c:247` | `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)` |
| `prefs_suggest` | function | `src/prefs.c:357` | `int prefs_suggest(const prefs_state *p, const char *query,                   char *out, size_t ro...` |
| `sb_esc` | function | `src/prefs.c:400` | `static void sb_esc(sbuf *b, const char *s)` |
| `sb_link_item` | function | `src/prefs.c:413` | `static void sb_link_item(sbuf *b, const char *url, const char *label)` |
| `sb_put` | function | `src/prefs.c:382` | `static void sb_put(sbuf *b, const char *s, size_t n)` |
| `sb_str` | function | `src/prefs.c:397` | `static void sb_str(sbuf *b, const char *s)` |
| `sbuf` | struct | `src/prefs.c:380` | `` |
| `sugg_push` | function | `src/prefs.c:348` | `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,                       cons...` |
| `title_clean` | function | `src/prefs.c:39` | `static char *title_clean(const char *src)` |
| `url_prefix_match` | function | `src/prefs.c:336` | `static int url_prefix_match(const char *url, const char *q)` |
| `url_valid` | function | `src/prefs.c:26` | `static int url_valid(const char *url)` |
| `PROFILE_KEYFILE_LEN` | macro | `src/profile.c:27` | `#define PROFILE_KEYFILE_LEN` |
| `_POSIX_C_SOURCE` | macro | `src/profile.c:11` | `#define _POSIX_C_SOURCE` |
| `join_path` | function | `src/profile.c:29` | `static int join_path(const profile_ctx *ctx, const char *name,                      char *out, si...` |
| `keyfile_create` | function | `src/profile.c:36` | `static profile_status keyfile_create(const char *dir, const char *path,                          ...` |
| `map_ds` | function | `src/profile.c:98` | `static profile_status map_ds(ds_status ds)` |
| `profile_close` | function | `src/profile.c:149` | `void profile_close(profile_ctx *ctx)` |
| `profile_load` | function | `src/profile.c:112` | `profile_status profile_load(const profile_ctx *ctx, prefs_state *out)` |
| `profile_open` | function | `src/profile.c:59` | `profile_status profile_open(profile_ctx *ctx, const char *dir)` |
| `profile_save` | function | `src/profile.c:133` | `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p)` |
| `place` | function | `src/render_doc.c:240` | `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never...` |
| `rd_at` | function | `src/render_doc.c:765` | `const rd_block *rd_at(const rd_doc *d, size_t i)` |
| `rd_block_heading_level` | function | `src/render_doc.c:802` | `int rd_block_heading_level(const rd_block *b)` |
| `rd_block_tag` | function | `src/render_doc.c:813` | `const char *rd_block_tag(const rd_block *b)` |
| `rd_box_at` | function | `src/render_doc.c:774` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)` |
| `rd_box_count` | function | `src/render_doc.c:770` | `size_t rd_box_count(const rd_doc *d)` |
| `rd_build` | function | `src/render_doc.c:293` | `rd_status rd_build(const pv_view *view, rdp_caps caps,                    const char *top_level_u...` |
| `rd_cont_at` | function | `src/render_doc.c:783` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)` |
| `rd_cont_count` | function | `src/render_doc.c:779` | `size_t rd_cont_count(const rd_doc *d)` |
| `rd_count` | function | `src/render_doc.c:761` | `size_t rd_count(const rd_doc *d)` |
| `rd_free` | function | `src/render_doc.c:744` | `void rd_free(rd_doc *d)` |
| `rd_image_fail_label` | function | `src/render_doc.c:879` | `const char *rd_image_fail_label(img_fail_reason reason)` |
| `rd_image_label` | function | `src/render_doc.c:868` | `const char *rd_image_label(rdp_img_decision d)` |
| `rd_input_invisible` | function | `src/render_doc.c:864` | `int rd_input_invisible(int input_type)` |
| `rd_input_label` | function | `src/render_doc.c:844` | `const char *rd_input_label(int input_type)` |
| `rd_kind_name` | function | `src/render_doc.c:788` | `const char *rd_kind_name(rd_kind k)` |
| `rd_push` | function | `src/render_doc.c:60` | `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,                  ...` |
| `rd_push_input` | function | `src/render_doc.c:214` | `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` |
| `resolve_image_decision` | function | `src/render_doc.c:250` | `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,         ...` |
| `too` | function | `src/render_doc.c:281` | `* that would not fit is cleared too (never truncated-and-fetched). */ static void gate_box_image_...` |
| `unset` | function | `src/render_doc.c:706` | `* background paints as if unset (no border/box-shadow-style * "broken image" placeholder) -- it is decoration, not...` |
| `utf8_sanitized_dup` | function | `src/render_doc.c:28` | `static char *utf8_sanitized_dup(const char *s)` |
| `rdp_caps_safe` | function | `src/render_policy.c:17` | `rdp_caps rdp_caps_safe(void)` |
| `rdp_image_decision` | function | `src/render_policy.c:28` | `rdp_img_decision rdp_image_decision(rdp_caps caps,                                     const char...` |
| `rdp_images_warning` | function | `src/render_policy.c:71` | `const char *rdp_images_warning(void)` |
| `rdp_img_reason` | function | `src/render_policy.c:60` | `const char *rdp_img_reason(rdp_img_decision d)` |
| `rdp_is_tracking_pixel` | function | `src/render_policy.c:22` | `int rdp_is_tracking_pixel(int w, int h)` |
| `_POSIX_C_SOURCE` | macro | `src/renderer.c:7` | `#define _POSIX_C_SOURCE` |
| `child_render` | function | `src/renderer.c:25` | `static void child_render(int wfd, const char *html, size_t len)` |
| `rd_render_html` | function | `src/renderer.c:70` | `rd_status rd_render_html(const char *html, size_t len, rd_result *out)` |
| `rd_result_free` | function | `src/renderer.c:120` | `void rd_result_free(rd_result *out)` |
| `read_field` | function | `src/renderer.c:53` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `write_full` | function | `src/renderer.c:40` | `&& write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 \|\| write_full(wfd, title, tl) == 0) && write_full(wfd, &xl...` |
| `RP_MAX_HOST` | macro | `src/request_policy.c:17` | `#define RP_MAX_HOST` |
| `RP_MAX_LABELS` | macro | `src/request_policy.c:18` | `#define RP_MAX_LABELS` |
| `ci_starts_with` | function | `src/request_policy.c:26` | `static int ci_starts_with(const char *s, const char *prefix)` |
| `hdr_forbidden` | function | `src/request_policy.c:184` | `static int hdr_forbidden(const char *n, size_t len)` |
| `hdr_lower` | function | `src/request_policy.c:162` | `static int hdr_lower(int c)` |
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
| `SF_GUARD_HOST_MAX` | macro | `src/secure_fetch.c:520` | `#define SF_GUARD_HOST_MAX` |
| `SF_RCACHE_SLOTS` | macro | `src/secure_fetch.c:1255` | `#define SF_RCACHE_SLOTS` |
| `SF_RCACHE_TTL_S` | macro | `src/secure_fetch.c:1256` | `#define SF_RCACHE_TTL_S` |
| `_POSIX_C_SOURCE` | macro | `src/secure_fetch.c:12` | `#define _POSIX_C_SOURCE` |
| `add_header` | function | `src/secure_fetch.c:887` | `static int add_header(struct curl_slist **h, const char *line)` |
| `body_sink` | struct | `src/secure_fetch.c:497` | `` |
| `ci_index` | function | `src/secure_fetch.c:61` | `static long ci_index(const char *haystack, const char *needle)` |
| `ci_starts_with` | function | `src/secure_fetch.c:49` | `static int ci_starts_with(const char *haystack, const char *prefix)` |
| `copy_bounded` | function | `src/secure_fetch.c:544` | `static void copy_bounded(char *dst, size_t dstsz, const char *src)` |
| `copy_checked` | function | `src/secure_fetch.c:359` | `static int copy_checked(char *dst, size_t dstsz, const char *src)` |
| `database` | function | `src/secure_fetch.c:559` | `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid...` |
| `fetch_ctx` | struct | `src/secure_fetch.c:522` | `` |
| `get_negotiated_group_name` | function | `src/secure_fetch.c:555` | `static const char *get_negotiated_group_name(SSL *ssl)` |
| `group` | function | `src/secure_fetch.c:573` | `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);` |
| `header_cb` | function | `src/secure_fetch.c:624` | `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` |
| `header_value_clean` | function | `src/secure_fetch.c:265` | `static int header_value_clean(const char *s)` |
| `inspect_chain` | function | `src/secure_fetch.c:723` | `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` |
| `map_curl_error` | function | `src/secure_fetch.c:846` | `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)` |
| `module` | function | `src/secure_fetch.c:420` | `* pure url module (DRY);` |
| `name_is_pq_sig` | function | `src/secure_fetch.c:713` | `static int name_is_pq_sig(int pknid)` |
| `progress` | function | `src/secure_fetch.c:506` | `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);` |
| `rcache_put_ram` | function | `src/secure_fetch.c:1288` | `static int rcache_put_ram(const char *from, const char *to, time_t now)` |
| `redirect` | function | `src/secure_fetch.c:983` | `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a      * different orig...` |
| `refused` | function | `src/secure_fetch.c:781` | `* a private peer is then refused (fail closed). */ static void sf_guard_init(fetch_ctx *ctx, cons...` |
| `sf_accept_language_or_default` | function | `src/secure_fetch.c:275` | `const char *sf_accept_language_or_default(const char *lang)` |
| `sf_attempt_get` | function | `src/secure_fetch.c:1604` | `static sf_status sf_attempt_get(const char *url, const sf_config *cfg, sf_response *out,         ...` |
| `sf_attempt_post` | function | `src/secure_fetch.c:1610` | `static sf_status sf_attempt_post(const char *url, const sf_config *cfg, sf_response *out,        ...` |
| `sf_check_chain_policy` | function | `src/secure_fetch.c:318` | `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)` |
| `sf_check_group_is_pq` | function | `src/secure_fetch.c:309` | `sf_status sf_check_group_is_pq(const char *negotiated_group)` |
| `sf_check_tls_version` | function | `src/secure_fetch.c:304` | `sf_status sf_check_tls_version(const char *negotiated_version)` |
| `sf_ci_prefix` | function | `src/secure_fetch.c:427` | `static int sf_ci_prefix(const char *s, const char *p)` |
| `sf_config_default` | function | `src/secure_fetch.c:238` | `sf_config sf_config_default(void)` |
| `sf_cookie_header_for` | function | `src/secure_fetch.c:188` | `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)` |
| `sf_cookie_line_matches` | function | `src/secure_fetch.c:118` | `int sf_cookie_line_matches(const char *line, const char *host, const char *path,                 ...` |
| `sf_cookie_put` | function | `src/secure_fetch.c:217` | `void sf_cookie_put(const char *url, const char *namevalue)` |
| `sf_downgrade_of` | function | `src/secure_fetch.c:1595` | `static int sf_downgrade_of(sf_policy p)` |
| `sf_enforce_policy` | function | `src/secure_fetch.c:328` | `sf_status sf_enforce_policy(const char *tls_version, const char *group,                          ...` |
| `sf_fallback_policy` | function | `src/secure_fetch.c:1578` | `int sf_fallback_policy(sf_status failed, sf_policy tried, int allowlisted, sf_policy *next)` |
| `sf_get` | function | `src/secure_fetch.c:1235` | `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)` |
| `sf_get_follow` | function | `src/secure_fetch.c:1346` | `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,                 ...` |
| `sf_get_follow_navigable` | function | `src/secure_fetch.c:1635` | `sf_status sf_get_follow_navigable(const char *url, sf_config *cfg, sf_response *out,             ...` |
| `sf_global_init` | function | `src/secure_fetch.c:90` | `void sf_global_init(void)` |
| `sf_guard_opensocket` | function | `src/secure_fetch.c:808` | `static curl_socket_t sf_guard_opensocket(void *clientp, curlsocktype purpose,                    ...` |
| `sf_guard_prereq` | function | `src/secure_fetch.c:835` | `static int sf_guard_prereq(void *clientp, char *conn_primary_ip, char *conn_local_ip,            ...` |
| `sf_header_value` | function | `src/secure_fetch.c:375` | `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz)` |
| `sf_impersonate_kex_groups` | function | `src/secure_fetch.c:279` | `const char *sf_impersonate_kex_groups(void)` |
| `sf_impersonate_tls13_ciphers` | function | `src/secure_fetch.c:280` | `const char *sf_impersonate_tls13_ciphers(void)` |
| `sf_is_redirect_code` | function | `src/secure_fetch.c:368` | `int sf_is_redirect_code(long http_code)` |
| `sf_navigable` | function | `src/secure_fetch.c:1615` | `static sf_status sf_navigable(sf_attempt_fn attempt, const char *url, sf_config *cfg,            ...` |
| `sf_parse_location_header` | function | `src/secure_fetch.c:397` | `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)` |
| `sf_perform` | function | `src/secure_fetch.c:1075` | `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,             ...` |
| `sf_post` | function | `src/secure_fetch.c:1239` | `sf_status sf_post(const char *url, const sf_config *cfg,                   const void *body, size...` |
| `sf_post_navigable` | function | `src/secure_fetch.c:1640` | `sf_status sf_post_navigable(const char *url, sf_config *cfg, const void *body,                   ...` |
| `sf_rcache_clear` | function | `src/secure_fetch.c:1269` | `void sf_rcache_clear(void)` |
| `sf_rcache_entry` | struct | `src/secure_fetch.c:1258` | `` |
| `sf_rcache_get` | function | `src/secure_fetch.c:1317` | `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap)` |
| `sf_rcache_put` | function | `src/secure_fetch.c:1307` | `int sf_rcache_put(const char *from, const char *to, time_t now)` |
| `sf_rcache_set_backing` | function | `src/secure_fetch.c:1280` | `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx)` |
| `sf_resolve_redirect` | function | `src/secure_fetch.c:415` | `sf_status sf_resolve_redirect(const char *base_url, const char *location,                        ...` |
| `sf_response_free` | function | `src/secure_fetch.c:467` | `void sf_response_free(sf_response *resp)` |
| `sf_setup_handle` | function | `src/secure_fetch.c:901` | `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,            ...` |
| `sf_share_lock` | function | `src/secure_fetch.c:77` | `static void sf_share_lock(CURL *handle, curl_lock_data data,                           curl_lock_...` |
| `sf_share_unlock` | function | `src/secure_fetch.c:83` | `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)` |
| `sf_url_host_path` | function | `src/secure_fetch.c:173` | `static int sf_url_host_path(const char *url, char *host, size_t hostsz,                          ...` |
| `sf_url_is_http` | function | `src/secure_fetch.c:292` | `static int sf_url_is_http(const char *url)` |
| `sf_user_agent_or_default` | function | `src/secure_fetch.c:271` | `const char *sf_user_agent_or_default(const char *ua)` |
| `sf_validate_url` | function | `src/secure_fetch.c:284` | `sf_status sf_validate_url(const char *url)` |
| `sf_ws` | struct | `src/secure_fetch.c:1432` | `` |
| `sf_ws_close` | function | `src/secure_fetch.c:1567` | `void sf_ws_close(sf_ws *ws)` |
| `sf_ws_fd` | function | `src/secure_fetch.c:1560` | `int sf_ws_fd(const sf_ws *ws)` |
| `sf_ws_open` | function | `src/secure_fetch.c:1460` | `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)` |
| `sf_ws_recv` | function | `src/secure_fetch.c:1538` | `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)` |
| `sf_ws_send` | function | `src/secure_fetch.c:1515` | `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)` |
| `sf_ws_url_check` | function | `src/secure_fetch.c:1439` | `sf_status sf_ws_url_check(const char *url)` |
| `sink` | type_alias | `src/secure_fetch.c:521` | `typedef struct fetch_ctx { body_sink sink;` |
| `this` | function | `src/secure_fetch.c:605` | `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and...` |
| `tls_capture` | struct | `src/secure_fetch.c:510` | `` |
| `tls_capture_from_ssl` | function | `src/secure_fetch.c:598` | `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)` |
| `tls_capture_try` | function | `src/secure_fetch.c:588` | `static void tls_capture_try(tls_capture *cap)` |
| `write_cb` | function | `src/secure_fetch.c:681` | `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)` |
| `ws_free` | function | `src/secure_fetch.c:1451` | `static void ws_free(sf_ws *ws)` |
| `ws_ssl_ctx_cb` | function | `src/secure_fetch.c:1425` | `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)` |
| `ws_ssl_info_cb` | function | `src/secure_fetch.c:1418` | `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)` |
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
| `shc_acquire` | function | `src/sheet_cache.c:155` | `shc_sheet *shc_acquire(shc_cache *cache, const shc_key *key)` |
| `shc_cache` | struct | `src/sheet_cache.c:30` | `` |
| `shc_css` | function | `src/sheet_cache.c:107` | `const css_sheet *shc_css(const shc_sheet *s)` |
| `shc_dup` | function | `src/sheet_cache.c:72` | `static char *shc_dup(const char *src, size_t len)` |
| `shc_free` | function | `src/sheet_cache.c:101` | `void shc_free(shc_cache *c)` |
| `shc_key_matches` | function | `src/sheet_cache.c:117` | `static int shc_key_matches(const shc_sheet *s, const shc_key *k)` |
| `shc_key_store` | function | `src/sheet_cache.c:136` | `static int shc_key_store(shc_sheet *s, const shc_key *k)` |
| `shc_new` | function | `src/sheet_cache.c:89` | `shc_cache *shc_new(size_t max_text_bytes)` |
| `shc_probe` | struct | `src/sheet_cache.c:39` | `` |
| `shc_probe_match` | function | `src/sheet_cache.c:47` | `static int shc_probe_match(void *ctx, const struct css_sel *sel)` |
| `shc_queries_free` | function | `src/sheet_cache.c:67` | `static void shc_queries_free(shc_query *q, size_t n)` |
| `shc_query` | struct | `src/sheet_cache.c:12` | `` |
| `shc_release` | function | `src/sheet_cache.c:96` | `void shc_release(shc_sheet *s)` |
| `shc_sheet` | struct | `src/sheet_cache.c:17` | `` |
| `shc_sheet_destroy` | function | `src/sheet_cache.c:81` | `static void shc_sheet_destroy(shc_sheet *s)` |
| `shc_stats_get` | function | `src/sheet_cache.c:111` | `void shc_stats_get(const shc_cache *c, shc_stats *out)` |
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
| `EPIPE` | function | `src/tab.c:2338` | `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();` |
| `FB_MAX_FILE_BYTES` | function | `src/tab.c:1169` | `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify  * the stream. ...` |
| `PV_MAX_CONTAINERS_WIRE` | macro | `src/tab.c:167` | `#define PV_MAX_CONTAINERS_WIRE` |
| `TAB_ASYNC_THREADS` | macro | `src/tab.c:213` | `#define TAB_ASYNC_THREADS` |
| `TAB_IOBUF_BYTES` | macro | `src/tab.c:59` | `#define TAB_IOBUF_BYTES` |
| `TAB_MAX_ASYNC_PENDING` | macro | `src/tab.c:211` | `#define TAB_MAX_ASYNC_PENDING` |
| `TAB_MAX_BATCH_BYTES` | macro | `src/tab.c:214` | `#define TAB_MAX_BATCH_BYTES` |
| `TAB_MAX_EXTERN_CSS` | macro | `src/tab.c:1242` | `#define TAB_MAX_EXTERN_CSS` |
| `TAB_MAX_GEOM_WORDS` | macro | `src/tab.c:199` | `#define TAB_MAX_GEOM_WORDS` |
| `TAB_MAX_HIST_BYTES` | macro | `src/tab.c:193` | `#define TAB_MAX_HIST_BYTES` |
| `TAB_MAX_HIST_OPS` | macro | `src/tab.c:192` | `#define TAB_MAX_HIST_OPS` |
| `TAB_MAX_JS_JOBS` | macro | `src/tab.c:220` | `#define TAB_MAX_JS_JOBS` |
| `TAB_MAX_NET_ROUNDS` | macro | `src/tab.c:212` | `#define TAB_MAX_NET_ROUNDS` |
| `TAB_MAX_OPENS` | macro | `src/tab.c:195` | `#define TAB_MAX_OPENS` |
| `TAB_MAX_OPEN_BYTES` | macro | `src/tab.c:196` | `#define TAB_MAX_OPEN_BYTES` |
| `TAB_MAX_RUNS` | macro | `src/tab.c:163` | `#define TAB_MAX_RUNS` |
| `TAB_MAX_STORAGE` | macro | `src/tab.c:188` | `#define TAB_MAX_STORAGE` |
| `TAB_MAX_SUBREQ` | macro | `src/tab.c:218` | `#define TAB_MAX_SUBREQ` |
| `TAB_MAX_SUBRESOURCE` | macro | `src/tab.c:219` | `#define TAB_MAX_SUBRESOURCE` |
| `TAB_MAX_URL` | macro | `src/tab.c:170` | `#define TAB_MAX_URL` |
| `TAB_MAX_WS_MSG` | macro | `src/tab.c:184` | `#define TAB_MAX_WS_MSG` |
| `TAB_SCREEN_H` | macro | `src/tab.c:136` | `#define TAB_SCREEN_H` |
| `TAB_SCREEN_W` | macro | `src/tab.c:135` | `#define TAB_SCREEN_W` |
| `TAB_WIRE_A_N` | macro | `src/tab.c:141` | `#define TAB_WIRE_A_N` |
| `TAB_WIRE_BOX_F_N` | macro | `src/tab.c:143` | `#define TAB_WIRE_BOX_F_N` |
| `TAB_WIRE_B_N` | macro | `src/tab.c:142` | `#define TAB_WIRE_B_N` |
| `TAB_WIRE_GRID_N` | macro | `src/tab.c:144` | `#define TAB_WIRE_GRID_N` |
| `TAB_WIRE_HEAD_N` | macro | `src/tab.c:140` | `#define TAB_WIRE_HEAD_N` |
| `WHERE` | function | `src/tab.c:1734` | `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...` |
| `_GNU_SOURCE` | macro | `src/tab.c:14` | `#define _GNU_SOURCE` |
| `adopt_worker` | function | `src/tab.c:3377` | `static tab_status adopt_worker(const tab_spawned *sp, tab **out)` |
| `blocks` | function | `src/tab.c:717` | `* * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the * grid array, block B[26])...` |
| `budget_remaining_ms` | function | `src/tab.c:1199` | `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` |
| `buffer` | function | `src/tab.c:647` | `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...` |
| `child_fetch` | function | `src/tab.c:478` | `static int child_fetch(void *vctx, const char *method, const char *url,                        co...` |
| `child_fetch_async` | function | `src/tab.c:494` | `static int child_fetch_async(void *vctx, const char *method, const char *url,                    ...` |
| `child_handle_click` | function | `src/tab.c:2072` | `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_decode_image` | function | `src/tab.c:2269` | `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` |
| `child_handle_decode_image_data` | function | `src/tab.c:2296` | `static void child_handle_decode_image_data(int wfd, const char *url, size_t len)` |
| `child_handle_eval` | function | `src/tab.c:2228` | `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` |
| `child_handle_event` | function | `src/tab.c:2082` | `static void child_handle_event(int wfd, child_state *cs)` |
| `child_handle_geom` | function | `src/tab.c:2168` | `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` |
| `child_handle_load` | function | `src/tab.c:1460` | `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,            ...` |
| `child_handle_mouse` | function | `src/tab.c:2130` | `static void child_handle_mouse(int wfd, child_state *cs)` |
| `child_handle_mutation` | function | `src/tab.c:1966` | `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,                         ...` |
| `child_handle_mutation_ex` | function | `src/tab.c:1973` | `static void child_handle_mutation_ex(int wfd, child_state *cs, int is_tick,                      ...` |
| `child_handle_submit` | function | `src/tab.c:2194` | `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_load` | function | `src/tab.c:579` | `static int child_load(child_state *cs, const char *html, size_t len, int run_js,                 ...` |
| `child_next_timer_ms` | function | `src/tab.c:1949` | `static int32_t child_next_timer_ms(child_state *cs)` |
| `child_prescript_view` | function | `src/tab.c:1430` | `static pv_view *child_prescript_view(child_state *cs, const char *html, size_t len,              ...` |
| `child_read_reply` | function | `src/tab.c:450` | `static int child_read_reply(child_state *cs, net_reply *out)` |
| `child_reset_page` | function | `src/tab.c:291` | `static void child_reset_page(child_state *cs)` |
| `child_sheets` | function | `src/tab.c:286` | `static shc_cache *child_sheets(child_state *cs)` |
| `child_state` | struct | `src/tab.c:231` | `` |
| `child_write_subreq` | function | `src/tab.c:425` | `static int child_write_subreq(child_state *cs, uint8_t tag, const char *method, const char *url, ...` |
| `clip_pm_ok` | function | `src/tab.c:148` | `static int clip_pm_ok(int32_t v)` |
| `column` | function | `src/tab.c:2903` | `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...` |
| `computed_signature` | function | `src/tab.c:320` | `static uint64_t computed_signature(const dom_index *idx)` |
| `content` | function | `src/tab.c:1799` | `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...` |
| `ctype_is_css` | function | `src/tab.c:1222` | `static int ctype_is_css(const char *ctype)` |
| `ctype_is_javascript` | function | `src/tab.c:1213` | `static int ctype_is_javascript(const char *ctype)` |
| `depth` | function | `src/tab.c:2368` | `* defense in depth (seccomp already excludes open/socket/exec);` |
| `does` | function | `src/tab.c:1552` | `* native browser does (spec/js_native.md). Best effort -- an unsealed page still runs. */ (void)jn_seal(cs->js);` |
| `exec_worker_child` | function | `src/tab.c:3306` | `static void exec_worker_child(int rfd, int wfd)` |
| `fd` | type_alias | `src/tab.c:60` | `typedef struct tab_iobuf { int fd;` |
| `frames` | function | `src/tab.c:4275` | `* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of...` |
| `gate_js_nav` | function | `src/tab.c:3920` | `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` |
| `gen_session_key` | function | `src/tab.c:2316` | `static uint64_t gen_session_key(void)` |
| `geom_parent` | function | `src/tab.c:2160` | `static dom_node_id geom_parent(void *ctx, dom_node_id n)` |
| `geometry_encode` | function | `src/tab.c:4606` | `static int32_t *geometry_encode(const jg_table *g, size_t *words_out)` |
| `hist_ops_free` | function | `src/tab.c:3729` | `static void hist_ops_free(tab_hist_op *ops, size_t n)` |
| `ignore_sigpipe` | function | `src/tab.c:2653` | `static void ignore_sigpipe(void)` |
| `io_failure` | function | `src/tab.c:3298` | `static tab_status io_failure(tab *t)` |
| `is_activation_event` | function | `src/tab.c:3794` | `static int is_activation_event(const char *type)` |
| `job_discard` | function | `src/tab.c:4630` | `static void job_discard(tab *t)` |
| `job_main` | function | `src/tab.c:4653` | `static void *job_main(void *arg)` |
| `job_start` | function | `src/tab.c:4682` | `static tab_status job_start(tab *t)` |
| `layout` | function | `src/tab.c:2892` | `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....` |
| `libraries` | function | `src/tab.c:1569` | `* load heavier libraries (jQuery, Bootstrap, etc.) that need more time. * Untrusted hosts get the default budget...` |
| `load` | function | `src/tab.c:2609` | `* subresource requests this load (set per page: host in allow.conf AND js.conf);` |
| `log_external_skip` | function | `src/tab.c:1230` | `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,                 ...` |
| `net_reply` | struct | `src/tab.c:414` | `` |
| `net_reply_free` | function | `src/tab.c:422` | `static void net_reply_free(net_reply *r)` |
| `once` | function | `src/tab.c:1852` | `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);` |
| `open_urls_free` | function | `src/tab.c:3803` | `static void open_urls_free(char **u, size_t n)` |
| `parse_worker_fd` | function | `src/tab.c:2570` | `static int parse_worker_fd(const char *s, int *out)` |
| `prof_lap` | function | `src/tab.c:541` | `static void prof_lap(const char *what, double *t0)` |
| `prof_now_ms` | function | `src/tab.c:531` | `static double prof_now_ms(void)` |
| `prof_on` | function | `src/tab.c:536` | `static int prof_on(void)` |
| `rad_len_ok` | function | `src/tab.c:154` | `static int rad_len_ok(int32_t v, int dflt)` |
| `read_console` | function | `src/tab.c:3251` | `static int read_console(int fd, fb_buffer *out)` |
| `read_field` | function | `src/tab.c:2679` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `read_full` | macro | `src/tab.c:114` | `#define read_full(fd, buf, n)` |
| `read_opens` | function | `src/tab.c:3813` | `static tab_status read_opens(tab *t, const char *page_url, int gesture,                          ...` |
| `read_view` | function | `src/tab.c:2696` | `static int read_view(int fd, pv_view **out)` |
| `read_view_raw` | function | `src/tab.c:2704` | `static int read_view_raw(int fd, pv_view **out)` |
| `read_ws` | function | `src/tab.c:3851` | `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` |
| `reap_spawned` | function | `src/tab.c:3368` | `static void reap_spawned(const tab_spawned *sp, int kill_it)` |
| `replies` | function | `src/tab.c:507` | `* writing replies (no pipe deadlock). */ static void child_net_drain(child_state *cs)` |
| `run` | function | `src/tab.c:1248` | `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).  * Call after every ...` |
| `run_js` | function | `src/tab.c:552` | `* regardless of run_js (a no-JS load simply never records a request). */ /* Installs the page-ind...` |
| `send_request` | function | `src/tab.c:3288` | `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` |
| `sig_mix` | function | `src/tab.c:312` | `static uint64_t sig_mix(uint64_t h, const char *s, size_t n)` |
| `spawn_worker` | function | `src/tab.c:3338` | `static tab_status spawn_worker(tab_spawned *sp)` |
| `status` | type_alias | `src/tab.c:414` | `typedef struct net_reply { int32_t status;` |
| `swap` | function | `src/tab.c:1861` | `* display:none hiding an element via class swap (CSS, not      * DOM removal). */     if (ok && v...` |
| `tab` | struct | `src/tab.c:2602` | `` |
| `tab_alive` | function | `src/tab.c:4509` | `int tab_alive(const tab *t)` |
| `tab_async_busy` | function | `src/tab.c:4678` | `int tab_async_busy(const tab *t)` |
| `tab_async_fd` | function | `src/tab.c:4669` | `int tab_async_fd(tab *t)` |
| `tab_async_finish` | function | `src/tab.c:4720` | `tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)` |
| `tab_async_sync` | function | `src/tab.c:4643` | `static void tab_async_sync(tab *t)` |
| `tab_await_result` | function | `src/tab.c:4278` | `static tab_status tab_await_result(tab *t)` |
| `tab_await_result_inner` | function | `src/tab.c:4286` | `static tab_status tab_await_result_inner(tab *t)` |
| `tab_batch_discard` | function | `src/tab.c:3724` | `static void tab_batch_discard(tab *t)` |
| `tab_batch_run` | function | `src/tab.c:3657` | `static int tab_batch_run(void *vt, const sqb_req *rq, sqb_res *out)` |
| `tab_child_pid` | function | `src/tab.c:4515` | `pid_t tab_child_pid(const tab *t)` |
| `tab_click` | function | `src/tab.c:4143` | `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)` |
| `tab_close` | function | `src/tab.c:4519` | `void tab_close(tab *t)` |
| `tab_decode_image` | function | `src/tab.c:4488` | `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)` |
| `tab_decode_image_data_url` | function | `src/tab.c:4495` | `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)` |
| `tab_decode_image_op` | function | `src/tab.c:4441` | `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,         ...` |
| `tab_eval` | function | `src/tab.c:4400` | `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)` |
| `tab_eval_result_free` | function | `src/tab.c:4567` | `void tab_eval_result_free(tab_eval_result *r)` |
| `tab_geometry_async` | function | `src/tab.c:4705` | `tab_status tab_geometry_async(tab *t, const jg_table *g)` |
| `tab_geometry_send` | function | `src/tab.c:4588` | `static tab_status tab_geometry_send(tab *t, const int32_t *buf, size_t words)` |
| `tab_image_free` | function | `src/tab.c:4576` | `void tab_image_free(tab_image *img)` |
| `tab_inflight_request_headers` | function | `src/tab.c:3548` | `const char *tab_inflight_request_headers(void)` |
| `tab_iobuf` | struct | `src/tab.c:60` | `` |
| `tab_last_subreq_stats` | function | `src/tab.c:3493` | `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)` |
| `tab_load` | function | `src/tab.c:3930` | `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)` |
| `tab_load_ex` | function | `src/tab.c:3934` | `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)` |
| `tab_load_full` | function | `src/tab.c:3938` | `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,             ...` |
| `tab_mod_fetch` | function | `src/tab.c:1336` | `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` |
| `tab_mod_resolve` | function | `src/tab.c:1306` | `static int tab_mod_resolve(void *host, const char *base, const char *spec,                       ...` |
| `tab_note_css_served` | function | `src/tab.c:3614` | `static void tab_note_css_served(tab *t, int ok, int status, const char *url, const char *rbody,  ...` |
| `tab_op_budget_us` | function | `src/tab.c:3610` | `static int64_t tab_op_budget_us(const tab *t)` |
| `tab_open` | function | `src/tab.c:3428` | `tab_status tab_open(tab **out)` |
| `tab_page_free` | function | `src/tab.c:4537` | `void tab_page_free(tab_page *p)` |
| `tab_page_keep_view` | function | `src/tab.c:3477` | `void tab_page_keep_view(tab_page *prev, tab_page *next)` |
| `tab_parse_worker_args` | function | `src/tab.c:2582` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)` |
| `tab_popstate` | function | `src/tab.c:4742` | `tab_status tab_popstate(tab *t, int index, tab_page *out)` |
| `tab_prewarm` | function | `src/tab.c:3399` | `void tab_prewarm(void)` |
| `tab_prewarmed` | function | `src/tab.c:3405` | `int tab_prewarmed(void)` |
| `tab_prewarmed_pid` | function | `src/tab.c:3412` | `int tab_prewarmed_pid(void)` |
| `tab_read_full` | function | `src/tab.c:88` | `static int tab_read_full(int fd, void *buf, size_t n)` |
| `tab_read_subreq_fields` | function | `src/tab.c:3599` | `static int tab_read_subreq_fields(tab *t, char **method, char **url, char **body, size_t *blen,  ...` |
| `tab_read_view` | function | `src/tab.c:4269` | `tab_status tab_read_view(tab *t, tab_page *out)` |
| `tab_read_view_ex` | function | `src/tab.c:4295` | `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)` |
| `tab_refresh_alive` | function | `src/tab.c:2660` | `static void tab_refresh_alive(tab *t)` |
| `tab_report_response_headers` | function | `src/tab.c:3536` | `void tab_report_response_headers(const char *lines)` |
| `tab_serve_netwait` | function | `src/tab.c:3694` | `static int tab_serve_netwait(tab *t)` |
| `tab_serve_subreq` | function | `src/tab.c:3630` | `static int tab_serve_subreq(tab *t, int net_granted, int css_granted)` |
| `tab_serve_tag` | function | `src/tab.c:3716` | `static int tab_serve_tag(tab *t, uint8_t tag, int net_granted, int css_granted)` |
| `tab_set_cookies` | function | `src/tab.c:3516` | `void tab_set_cookies(tab *t, const char *cookies)` |
| `tab_set_css_allowed` | function | `src/tab.c:3488` | `void tab_set_css_allowed(tab *t, int allowed)` |
| `tab_set_css_sink` | function | `src/tab.c:3457` | `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)` |
| `tab_set_fetcher` | function | `src/tab.c:3451` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)` |
| `tab_set_frame_id` | function | `src/tab.c:3506` | `void tab_set_frame_id(tab *t, int id)` |
| `tab_set_geometry` | function | `src/tab.c:4616` | `tab_status tab_set_geometry(tab *t, const jg_table *g)` |
| `tab_set_identity` | function | `src/tab.c:3498` | `void tab_set_identity(tab *t, const char *serialized)` |
| `tab_set_lazy_ticks` | function | `src/tab.c:3472` | `void tab_set_lazy_ticks(tab *t, int on)` |
| `tab_set_net_allowed` | function | `src/tab.c:3467` | `void tab_set_net_allowed(tab *t, int allowed)` |
| `tab_set_op_net_budget_ms` | function | `src/tab.c:3463` | `void tab_set_op_net_budget_ms(tab *t, int ms)` |
| `tab_set_storage` | function | `src/tab.c:4769` | `void tab_set_storage(tab *t, const char *blob, size_t len)` |
| `tab_set_viewport_w` | function | `src/tab.c:3511` | `void tab_set_viewport_w(tab *t, int px)` |
| `tab_shutdown_spare` | function | `src/tab.c:3419` | `void tab_shutdown_spare(void)` |
| `tab_spawned` | struct | `src/tab.c:3326` | `` |
| `tab_submit` | function | `src/tab.c:4161` | `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` |
| `tab_submit_async` | function | `src/tab.c:3672` | `static int tab_submit_async(tab *t, int net_granted, int css_granted)` |
| `tab_subreq_permitted` | function | `src/tab.c:3522` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)` |
| `tab_tick` | function | `src/tab.c:4151` | `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)` |
| `tab_tick_async` | function | `src/tab.c:4695` | `tab_status tab_tick_async(tab *t, int elapsed_ms)` |
| `tab_url_resolve` | function | `src/tab.c:1297` | `static int tab_url_resolve(void *ctx, const char *base, const char *ref,                         ...` |
| `tab_wflush` | function | `src/tab.c:69` | `static int tab_wflush(void)` |
| `tab_worker_dispatch` | function | `src/tab.c:2592` | `void tab_worker_dispatch(int argc, char **argv)` |
| `tab_worker_run` | function | `src/tab.c:2336` | `static void tab_worker_run(int rfd, int wfd)` |
| `tab_write_full` | function | `src/tab.c:76` | `static int tab_write_full(int fd, const void *buf, size_t n)` |
| `tab_write_reply` | function | `src/tab.c:3554` | `static int tab_write_reply(tab *t, int ok, int status, const char *rbody, size_t rlen,           ...` |
| `tab_ws_event` | function | `src/tab.c:4749` | `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,        ...` |
| `tests` | function | `src/tab.c:2779` | `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...` |
| `tzset` | function | `src/tab.c:2354` | `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);` |
| `unchanged` | function | `src/tab.c:264` | `* is unchanged (spec/sheet_cache.md);` |
| `window` | function | `src/tab.c:1377` | `* net window (cs->net_active). */ static void child_fetch_stylesheets(child_state *cs)` |
| `write_field` | function | `src/tab.c:683` | `static int write_field(int fd, const char *s)` |
| `write_full` | macro | `src/tab.c:113` | `#define write_full(fd, buf, n)` |
| `write_full` | function | `src/tab.c:1882` | `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 \|\| write_full(wfd, text, xl) == 0) && write_view(wfd...` |
| `write_history` | function | `src/tab.c:1358` | `static int write_history(int wfd, child_state *cs)` |
| `write_opens` | function | `src/tab.c:1937` | `static int write_opens(int wfd, child_state *cs)` |
| `write_storage` | function | `src/tab.c:1923` | `static int write_storage(int wfd, child_state *cs)` |
| `write_view` | function | `src/tab.c:725` | `static int write_view(int wfd, const pv_view *v)` |
| `write_view_raw` | function | `src/tab.c:736` | `static int write_view_raw(int wfd, const pv_view *v)` |
| `write_ws` | function | `src/tab.c:1906` | `static int write_ws(int wfd, child_state *cs)` |
| `ws_ops_free` | function | `src/tab.c:3842` | `static void ws_ops_free(tab_ws_op *ops, size_t n)` |
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

Next: [SYMBOLS_p11.md](SYMBOLS_p11.md)
