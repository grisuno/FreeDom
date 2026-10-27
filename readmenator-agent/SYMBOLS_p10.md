# Symbols (page 10 of 16)
Previous: [SYMBOLS_p9.md](SYMBOLS_p9.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `pqs_seal` | function | `src/pq_seal.c:106` | `pqs_status pqs_seal(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],                     const ...` |
| `PF_MAX_URL` | macro | `src/prefetch.c:24` | `#define PF_MAX_URL` |
| `_POSIX_C_SOURCE` | macro | `src/prefetch.c:12` | `#define _POSIX_C_SOURCE` |
| `attr_span` | struct | `src/prefetch.c:65` | `` |
| `ci_eq_span` | function | `src/prefetch.c:58` | `static int ci_eq_span(const char *s, size_t n, const char *kw)` |
| `ci_find` | function | `src/prefetch.c:49` | `static const char *ci_find(const char *p, const char *end, const char *kw)` |
| `ci_starts` | function | `src/prefetch.c:40` | `static int ci_starts(const char *p, const char *end, const char *kw)` |
| `emit` | function | `src/prefetch.c:120` | `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)` |
| `is_name_char` | function | `src/prefetch.c:30` | `static int is_name_char(char c)` |
| `is_ws` | function | `src/prefetch.c:26` | `static int is_ws(char c)` |
| `js_ident_ch` | function | `src/prefetch.c:207` | `static int js_ident_ch(char c)` |
| `js_skip_string` | function | `src/prefetch.c:219` | `static size_t js_skip_string(const char *s, size_t i, size_t n)` |
| `js_skip_ws` | function | `src/prefetch.c:212` | `static size_t js_skip_ws(const char *s, size_t i, size_t n)` |
| `js_take_spec` | function | `src/prefetch.c:226` | `static void js_take_spec(const char *s, size_t i, size_t n,                          char (*out)[...` |
| `lower` | function | `src/prefetch.c:35` | `static int lower(int c)` |
| `pf_find_importmap` | function | `src/prefetch.c:483` | `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n)` |
| `pf_follow_imports` | function | `src/prefetch.c:333` | `static void pf_follow_imports(pf_pool *p, const char *base, const char *body, size_t len)` |
| `pf_is_js` | function | `src/prefetch.c:311` | `static int pf_is_js(const char *url, const char *ctype)` |
| `pf_list_free` | function | `src/prefetch.c:196` | `void pf_list_free(pf_list *l)` |
| `pf_pool_add` | function | `src/prefetch.c:288` | `int pf_pool_add(pf_pool *p, const char *url)` |
| `pf_pool_finish` | function | `src/prefetch.c:540` | `void pf_pool_finish(pf_pool *p)` |
| `pf_pool_start` | function | `src/prefetch.c:387` | `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,                   pf_fetch_f...` |
| `pf_pool_start_page` | function | `src/prefetch.c:504` | `int pf_pool_start_page(pf_pool *p, const char *html, size_t len, const char *page_url,           ...` |
| `pf_pool_take` | function | `src/prefetch.c:444` | `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,                  char **body,...` |
| `pf_pooled_fetch` | function | `src/prefetch.c:561` | `int pf_pooled_fetch(void *vctx, const char *method, const char *url,                     const ch...` |
| `pf_scan` | function | `src/prefetch.c:133` | `int pf_scan(const char *html, size_t len, pf_list *out)` |
| `pf_scan_imports` | function | `src/prefetch.c:241` | `size_t pf_scan_imports(const char *js, size_t len, char (*out)[PF_SPEC_MAX], size_t cap)` |
| `pf_url_cb` | function | `src/prefetch.c:319` | `static int pf_url_cb(void *ctx, const char *base, const char *ref, char *out, size_t outsz)` |
| `pf_url_shaped` | function | `src/prefetch.c:324` | `static int pf_url_shaped(const char *sp)` |
| `pf_worker` | function | `src/prefetch.c:349` | `static void *pf_worker(void *arg)` |
| `pool_start` | function | `src/prefetch.c:394` | `static int pool_start(pf_pool *p, const char *const *urls, size_t nurls,                       pf...` |
| `PREFS_MAGIC` | macro | `src/prefs.c:20` | `#define PREFS_MAGIC` |
| `_POSIX_C_SOURCE` | macro | `src/prefs.c:11` | `#define _POSIX_C_SOURCE` |
| `apply_kv` | function | `src/prefs.c:231` | `static void apply_kv(prefs_state *out, const char *key, long val)` |
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
| `place` | function | `src/render_doc.c:238` | `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never...` |
| `rd_at` | function | `src/render_doc.c:767` | `const rd_block *rd_at(const rd_doc *d, size_t i)` |
| `rd_block_heading_level` | function | `src/render_doc.c:804` | `int rd_block_heading_level(const rd_block *b)` |
| `rd_block_tag` | function | `src/render_doc.c:815` | `const char *rd_block_tag(const rd_block *b)` |
| `rd_box_at` | function | `src/render_doc.c:776` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)` |
| `rd_box_count` | function | `src/render_doc.c:772` | `size_t rd_box_count(const rd_doc *d)` |
| `rd_build` | function | `src/render_doc.c:270` | `rd_status rd_build(const pv_view *view, rdp_caps caps,                    const char *top_level_u...` |
| `rd_cont_at` | function | `src/render_doc.c:785` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)` |
| `rd_cont_count` | function | `src/render_doc.c:781` | `size_t rd_cont_count(const rd_doc *d)` |
| `rd_count` | function | `src/render_doc.c:763` | `size_t rd_count(const rd_doc *d)` |
| `rd_free` | function | `src/render_doc.c:746` | `void rd_free(rd_doc *d)` |
| `rd_image_fail_label` | function | `src/render_doc.c:881` | `const char *rd_image_fail_label(img_fail_reason reason)` |
| `rd_image_label` | function | `src/render_doc.c:870` | `const char *rd_image_label(rdp_img_decision d)` |
| `rd_input_invisible` | function | `src/render_doc.c:866` | `int rd_input_invisible(int input_type)` |
| `rd_input_label` | function | `src/render_doc.c:846` | `const char *rd_input_label(int input_type)` |
| `rd_kind_name` | function | `src/render_doc.c:790` | `const char *rd_kind_name(rd_kind k)` |
| `rd_push` | function | `src/render_doc.c:60` | `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,                  ...` |
| `rd_push_input` | function | `src/render_doc.c:212` | `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` |
| `resolve_image_decision` | function | `src/render_doc.c:248` | `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,         ...` |
| `unset` | function | `src/render_doc.c:681` | `* background paints as if unset (no border/box-shadow-style                  * "broken image" pla...` |
| `utf8_sanitized_dup` | function | `src/render_doc.c:28` | `static char *utf8_sanitized_dup(const char *s)` |
| `rdp_caps_safe` | function | `src/render_policy.c:17` | `rdp_caps rdp_caps_safe(void)` |
| `rdp_image_decision` | function | `src/render_policy.c:28` | `rdp_img_decision rdp_image_decision(rdp_caps caps,                                     const char...` |
| `rdp_images_warning` | function | `src/render_policy.c:74` | `const char *rdp_images_warning(void)` |
| `rdp_img_reason` | function | `src/render_policy.c:63` | `const char *rdp_img_reason(rdp_img_decision d)` |
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
| `EPIPE` | function | `src/tab.c:2017` | `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();` |
| `FB_MAX_FILE_BYTES` | function | `src/tab.c:935` | `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify  * the stream. ...` |
| `PV_MAX_CONTAINERS_WIRE` | macro | `src/tab.c:96` | `#define PV_MAX_CONTAINERS_WIRE` |
| `TAB_MAX_EXTERN_CSS` | macro | `src/tab.c:1008` | `#define TAB_MAX_EXTERN_CSS` |
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
| `WHERE` | function | `src/tab.c:1459` | `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...` |
| `_GNU_SOURCE` | macro | `src/tab.c:14` | `#define _GNU_SOURCE` |
| `answered` | function | `src/tab.c:3106` | `* A refused frame is still consumed and answered (status 0), so the protocol never  * desyncs. Re...` |
| `blocks` | function | `src/tab.c:503` | `*  * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the  * grid arr...` |
| `budget_remaining_ms` | function | `src/tab.c:965` | `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` |
| `buffer` | function | `src/tab.c:438` | `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...` |
| `child_handle_click` | function | `src/tab.c:1760` | `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_decode_image` | function | `src/tab.c:1961` | `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` |
| `child_handle_decode_image_b64` | function | `src/tab.c:1983` | `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)` |
| `child_handle_eval` | function | `src/tab.c:1920` | `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` |
| `child_handle_event` | function | `src/tab.c:1774` | `static void child_handle_event(int wfd, child_state *cs)` |
| `child_handle_geom` | function | `src/tab.c:1860` | `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` |
| `child_handle_load` | function | `src/tab.c:1188` | `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,            ...` |
| `child_handle_mouse` | function | `src/tab.c:1822` | `static void child_handle_mouse(int wfd, child_state *cs)` |
| `child_handle_mutation` | function | `src/tab.c:1680` | `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,                         ...` |
| `child_handle_submit` | function | `src/tab.c:1886` | `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_tick` | function | `src/tab.c:1764` | `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)` |
| `child_next_timer_ms` | function | `src/tab.c:1665` | `static int32_t child_next_timer_ms(child_state *cs)` |
| `child_reset_page` | function | `src/tab.c:185` | `static void child_reset_page(child_state *cs)` |
| `child_state` | struct | `src/tab.c:146` | `` |
| `clip_pm_ok` | function | `src/tab.c:77` | `static int clip_pm_ok(int32_t v)` |
| `column` | function | `src/tab.c:2554` | `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...` |
| `computed_signature` | function | `src/tab.c:213` | `static uint64_t computed_signature(const dom_index *idx)` |
| `content` | function | `src/tab.c:1519` | `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...` |
| `ctype_is_css` | function | `src/tab.c:988` | `static int ctype_is_css(const char *ctype)` |
| `ctype_is_javascript` | function | `src/tab.c:979` | `static int ctype_is_javascript(const char *ctype)` |
| `depth` | function | `src/tab.c:2047` | `* defense in depth (seccomp already excludes open/socket/exec);` |
| `exec_worker_child` | function | `src/tab.c:2944` | `static void exec_worker_child(int rfd, int wfd)` |
| `fallback` | function | `src/tab.c:1269` | `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it...` |
| `frames` | function | `src/tab.c:3721` | `* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of...` |
| `gate_js_nav` | function | `src/tab.c:3370` | `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` |
| `gen_session_key` | function | `src/tab.c:1995` | `static uint64_t gen_session_key(void)` |
| `geom_parent` | function | `src/tab.c:1852` | `static dom_node_id geom_parent(void *ctx, dom_node_id n)` |
| `geometry_encode` | function | `src/tab.c:4042` | `static int32_t *geometry_encode(const jg_table *g, size_t *words_out)` |
| `hist_ops_free` | function | `src/tab.c:3179` | `static void hist_ops_free(tab_hist_op *ops, size_t n)` |
| `ignore_sigpipe` | function | `src/tab.c:2319` | `static void ignore_sigpipe(void)` |
| `io_failure` | function | `src/tab.c:2936` | `static tab_status io_failure(tab *t)` |
| `is_activation_event` | function | `src/tab.c:3244` | `static int is_activation_event(const char *type)` |
| `job_discard` | function | `src/tab.c:4066` | `static void job_discard(tab *t)` |
| `job_main` | function | `src/tab.c:4088` | `static void *job_main(void *arg)` |
| `job_start` | function | `src/tab.c:4117` | `static tab_status job_start(tab *t)` |
| `layout` | function | `src/tab.c:2543` | `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....` |
| `load` | function | `src/tab.c:2281` | `* subresource requests this load (set per page: host in allow.conf AND js.conf);` |
| `log_external_skip` | function | `src/tab.c:996` | `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,                 ...` |
| `once` | function | `src/tab.c:1568` | `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);` |
| `open_urls_free` | function | `src/tab.c:3253` | `static void open_urls_free(char **u, size_t n)` |
| `parse_worker_fd` | function | `src/tab.c:2242` | `static int parse_worker_fd(const char *s, int *out)` |
| `policy` | function | `src/tab.c:302` | `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a  * compromi...` |
| `prof_lap` | function | `src/tab.c:378` | `static void prof_lap(const char *what, double *t0)` |
| `prof_now_ms` | function | `src/tab.c:368` | `static double prof_now_ms(void)` |
| `prof_on` | function | `src/tab.c:373` | `static int prof_on(void)` |
| `rad_len_ok` | function | `src/tab.c:83` | `static int rad_len_ok(int32_t v, int dflt)` |
| `read_console` | function | `src/tab.c:2889` | `static int read_console(int fd, fb_buffer *out)` |
| `read_field` | function | `src/tab.c:2345` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `read_opens` | function | `src/tab.c:3263` | `static tab_status read_opens(tab *t, const char *page_url, int gesture,                          ...` |
| `read_view` | function | `src/tab.c:2361` | `static int read_view(int fd, pv_view **out)` |
| `read_ws` | function | `src/tab.c:3301` | `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` |
| `run` | function | `src/tab.c:1014` | `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).  * Call after every ...` |
| `run_js` | function | `src/tab.c:389` | `* regardless of run_js (a no-JS load simply never records a request). */ static int child_load(ch...` |
| `send_request` | function | `src/tab.c:2926` | `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` |
| `sig_mix` | function | `src/tab.c:205` | `static uint64_t sig_mix(uint64_t h, const char *s, size_t n)` |
| `swap` | function | `src/tab.c:1577` | `* display:none hiding an element via class swap (CSS, not      * DOM removal). */     if (ok && v...` |
| `tab` | struct | `src/tab.c:2274` | `` |
| `tab_alive` | function | `src/tab.c:3946` | `int tab_alive(const tab *t)` |
| `tab_async_busy` | function | `src/tab.c:4113` | `int tab_async_busy(const tab *t)` |
| `tab_async_fd` | function | `src/tab.c:4104` | `int tab_async_fd(tab *t)` |
| `tab_async_finish` | function | `src/tab.c:4155` | `tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)` |
| `tab_async_sync` | function | `src/tab.c:4078` | `static void tab_async_sync(tab *t)` |
| `tab_await_result` | function | `src/tab.c:3724` | `static tab_status tab_await_result(tab *t)` |
| `tab_await_result_inner` | function | `src/tab.c:3732` | `static tab_status tab_await_result_inner(tab *t)` |
| `tab_child_pid` | function | `src/tab.c:3952` | `pid_t tab_child_pid(const tab *t)` |
| `tab_click` | function | `src/tab.c:3589` | `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)` |
| `tab_close` | function | `src/tab.c:3956` | `void tab_close(tab *t)` |
| `tab_decode_image` | function | `src/tab.c:3920` | `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)` |
| `tab_decode_image_data_url` | function | `src/tab.c:3927` | `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)` |
| `tab_decode_image_op` | function | `src/tab.c:3878` | `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,         ...` |
| `tab_eval` | function | `src/tab.c:3837` | `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)` |
| `tab_eval_result_free` | function | `src/tab.c:4003` | `void tab_eval_result_free(tab_eval_result *r)` |
| `tab_geometry_async` | function | `src/tab.c:4140` | `tab_status tab_geometry_async(tab *t, const jg_table *g)` |
| `tab_geometry_send` | function | `src/tab.c:4024` | `static tab_status tab_geometry_send(tab *t, const int32_t *buf, size_t words)` |
| `tab_image_free` | function | `src/tab.c:4012` | `void tab_image_free(tab_image *img)` |
| `tab_inflight_request_headers` | function | `src/tab.c:3097` | `const char *tab_inflight_request_headers(void)` |
| `tab_last_subreq_stats` | function | `src/tab.c:3042` | `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)` |
| `tab_load` | function | `src/tab.c:3380` | `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)` |
| `tab_load_ex` | function | `src/tab.c:3384` | `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)` |
| `tab_load_full` | function | `src/tab.c:3388` | `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,             ...` |
| `tab_mod_fetch` | function | `src/tab.c:1102` | `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` |
| `tab_mod_resolve` | function | `src/tab.c:1072` | `static int tab_mod_resolve(void *host, const char *base, const char *spec,                       ...` |
| `tab_page_free` | function | `src/tab.c:3973` | `void tab_page_free(tab_page *p)` |
| `tab_parse_worker_args` | function | `src/tab.c:2254` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)` |
| `tab_popstate` | function | `src/tab.c:4177` | `tab_status tab_popstate(tab *t, int index, tab_page *out)` |
| `tab_read_view` | function | `src/tab.c:3715` | `tab_status tab_read_view(tab *t, tab_page *out)` |
| `tab_read_view_ex` | function | `src/tab.c:3742` | `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)` |
| `tab_refresh_alive` | function | `src/tab.c:2326` | `static void tab_refresh_alive(tab *t)` |
| `tab_report_response_headers` | function | `src/tab.c:3085` | `void tab_report_response_headers(const char *lines)` |
| `tab_set_cookies` | function | `src/tab.c:3065` | `void tab_set_cookies(tab *t, const char *cookies)` |
| `tab_set_css_allowed` | function | `src/tab.c:3037` | `void tab_set_css_allowed(tab *t, int allowed)` |
| `tab_set_css_sink` | function | `src/tab.c:3022` | `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)` |
| `tab_set_fetcher` | function | `src/tab.c:3016` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)` |
| `tab_set_frame_id` | function | `src/tab.c:3055` | `void tab_set_frame_id(tab *t, int id)` |
| `tab_set_geometry` | function | `src/tab.c:4052` | `tab_status tab_set_geometry(tab *t, const jg_table *g)` |
| `tab_set_identity` | function | `src/tab.c:3047` | `void tab_set_identity(tab *t, const char *serialized)` |
| `tab_set_net_allowed` | function | `src/tab.c:3032` | `void tab_set_net_allowed(tab *t, int allowed)` |
| `tab_set_op_net_budget_ms` | function | `src/tab.c:3028` | `void tab_set_op_net_budget_ms(tab *t, int ms)` |
| `tab_set_storage` | function | `src/tab.c:4204` | `void tab_set_storage(tab *t, const char *blob, size_t len)` |
| `tab_set_viewport_w` | function | `src/tab.c:3060` | `void tab_set_viewport_w(tab *t, int px)` |
| `tab_submit` | function | `src/tab.c:3607` | `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` |
| `tab_subreq_permitted` | function | `src/tab.c:3071` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)` |
| `tab_tick` | function | `src/tab.c:3597` | `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)` |
| `tab_tick_async` | function | `src/tab.c:4130` | `tab_status tab_tick_async(tab *t, int elapsed_ms)` |
| `tab_url_resolve` | function | `src/tab.c:1063` | `static int tab_url_resolve(void *ctx, const char *base, const char *ref,                         ...` |
| `tab_worker_dispatch` | function | `src/tab.c:2264` | `void tab_worker_dispatch(int argc, char **argv)` |
| `tab_worker_run` | function | `src/tab.c:2015` | `static void tab_worker_run(int rfd, int wfd)` |
| `tab_ws_event` | function | `src/tab.c:4184` | `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,        ...` |
| `tests` | function | `src/tab.c:2436` | `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...` |
| `tzset` | function | `src/tab.c:2033` | `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);` |
| `window` | function | `src/tab.c:1143` | `* net window (cs->net_active). */ static void child_fetch_stylesheets(child_state *cs)` |
| `write_field` | function | `src/tab.c:469` | `static int write_field(int fd, const char *s)` |
| `write_full` | function | `src/tab.c:1598` | `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 \|\| write_full(wfd, text, xl) == 0) && write_view(wfd...` |
| `write_history` | function | `src/tab.c:1124` | `static int write_history(int wfd, child_state *cs)` |
| `write_opens` | function | `src/tab.c:1653` | `static int write_opens(int wfd, child_state *cs)` |
| `write_storage` | function | `src/tab.c:1639` | `static int write_storage(int wfd, child_state *cs)` |
| `write_ws` | function | `src/tab.c:1622` | `static int write_ws(int wfd, child_state *cs)` |
| `ws_ops_free` | function | `src/tab.c:3292` | `static void ws_ops_free(tab_ws_op *ops, size_t n)` |
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

Next: [SYMBOLS_p11.md](SYMBOLS_p11.md)
