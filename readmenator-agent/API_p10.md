# API (page 10 of 11)
Previous: [API_p9.md](API_p9.md)

## src/perf_trace.c
Depends on: `include/perf_trace.h`
- `pt_init` (function) `src/perf_trace.c:16` `void pt_init(pt_trace *t)`
- `pt_elapsed_us` (function) `src/perf_trace.c:21` `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us)`
- `pt_record` (function) `src/perf_trace.c:26` `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us)`
- `pt_count` (function) `src/perf_trace.c:35` `size_t pt_count(const pt_trace *t, pt_stage stage)`
- `pt_last_us` (function) `src/perf_trace.c:40` `uint64_t pt_last_us(const pt_trace *t, pt_stage stage)`
- `pt_min_us` (function) `src/perf_trace.c:49` `uint64_t pt_min_us(const pt_trace *t, pt_stage stage)`
- `pt_max_us` (function) `src/perf_trace.c:60` `uint64_t pt_max_us(const pt_trace *t, pt_stage stage)`
- `cmp_u64` (function) `src/perf_trace.c:71` `static int cmp_u64(const void *a, const void *b)`
- `pt_median_us` (function) `src/perf_trace.c:79` `uint64_t pt_median_us(const pt_trace *t, pt_stage stage)`
- `pt_stage_name` (function) `src/perf_trace.c:89` `const char *pt_stage_name(pt_stage stage)`
- `pt_format` (function) `src/perf_trace.c:109` `size_t pt_format(const pt_trace *t, char *buf, size_t cap)`

## src/pq_seal.c
Depends on: `include/pq_seal.h`
- `pqs_buf_free` (function) `src/pq_seal.c:23` `void pqs_buf_free(uint8_t *buf, size_t len)`
- `pqs_free` (function) `src/pq_seal.c:29` `void pqs_free(pqs_keys *k)`
- `keys_wrap` (function) `src/pq_seal.c:35` `static pqs_keys *keys_wrap(EVP_PKEY *pkey)`
- `pqs_generate` (function) `src/pq_seal.c:42` `pqs_status pqs_generate(pqs_keys **out)`
- `pqs_export` (function) `src/pq_seal.c:55` `pqs_status pqs_export(const pqs_keys *k, uint8_t **der, size_t *len)`
- `pqs_import` (function) `src/pq_seal.c:68` `pqs_status pqs_import(const uint8_t *der, size_t len, pqs_keys **out)`
- `derive_key` (function) `src/pq_seal.c:81` `static int derive_key(const uint8_t ss[PQS_SS_LEN], const uint8_t wrap[LS_KEY_LEN],
             ...` -- pqs_status pqs_import(const uint8_t *der, size_t len, pqs_keys **out) { if (der == NULL || out == NULL) return...
- `pqs_seal` (function) `src/pq_seal.c:106` `pqs_status pqs_seal(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],
                    const ...`
- `pqs_open` (function) `src/pq_seal.c:147` `pqs_status pqs_open(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],
                    const ...`

## src/prefetch.c
Depends on: `include/import_map.h`, `include/prefetch.h`, `include/url.h`
- `is_ws` (function) `src/prefetch.c:26` `static int is_ws(char c)`
- `is_name_char` (function) `src/prefetch.c:30` `static int is_name_char(char c)`
- `lower` (function) `src/prefetch.c:35` `static int lower(int c)`
- `ci_starts` (function) `src/prefetch.c:40` `static int ci_starts(const char *p, const char *end, const char *kw)` -- static int is_ws(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'; } static int...
- `ci_find` (function) `src/prefetch.c:49` `static const char *ci_find(const char *p, const char *end, const char *kw)` -- static int lower(int c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; } /* Case-insensitive: [p,end) starts...
- `ci_eq_span` (function) `src/prefetch.c:58` `static int ci_eq_span(const char *s, size_t n, const char *kw)`
- `emit` (function) `src/prefetch.c:120` `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)`
- `pf_scan` (function) `src/prefetch.c:133` `int pf_scan(const char *html, size_t len, pf_list *out)`
- `pf_list_free` (function) `src/prefetch.c:196` `void pf_list_free(pf_list *l)`
- `js_ident_ch` (function) `src/prefetch.c:207` `static int js_ident_ch(char c)`
- `js_skip_ws` (function) `src/prefetch.c:212` `static size_t js_skip_ws(const char *s, size_t i, size_t n)`
- `js_skip_string` (function) `src/prefetch.c:219` `static size_t js_skip_string(const char *s, size_t i, size_t n)` -- /* --- ES module graph (spec/prefetch.md section 8) --- static int js_ident_ch(char c) { return (c >= 'a' && c <=...
- `js_take_spec` (function) `src/prefetch.c:226` `static void js_take_spec(const char *s, size_t i, size_t n,
                         char (*out)[...` -- static size_t js_skip_ws(const char *s, size_t i, size_t n) { while (i < n && (s[i] == ' ' || s[i] == '\t' || s[i]...
- `pf_scan_imports` (function) `src/prefetch.c:241` `size_t pf_scan_imports(const char *js, size_t len, char (*out)[PF_SPEC_MAX], size_t cap)`
- `pf_pool_add` (function) `src/prefetch.c:288` `int pf_pool_add(pf_pool *p, const char *url)`
- `pf_is_js` (function) `src/prefetch.c:311` `static int pf_is_js(const char *url, const char *ctype)`
- `pf_url_cb` (function) `src/prefetch.c:319` `static int pf_url_cb(void *ctx, const char *base, const char *ref, char *out, size_t outsz)`
- `pf_url_shaped` (function) `src/prefetch.c:324` `static int pf_url_shaped(const char *sp)`
- `pf_follow_imports` (function) `src/prefetch.c:333` `static void pf_follow_imports(pf_pool *p, const char *base, const char *body, size_t len)` -- Queues the static imports of a fetched module body, resolved the way the module loader resolves them: through the...
- `pf_worker` (function) `src/prefetch.c:349` `static void *pf_worker(void *arg)`
- `pf_pool_start` (function) `src/prefetch.c:387` `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                  pf_fetch_f...`
- `pool_start` (function) `src/prefetch.c:394` `static int pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                      pf...` -- map (owned on success) is set BEFORE the threads start: they read it after a * fetch, unlocked, and it never changes...
- `pf_pool_take` (function) `src/prefetch.c:444` `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,
                 char **body,...`
- `pf_find_importmap` (function) `src/prefetch.c:483` `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n)`
- `pf_pool_start_page` (function) `src/prefetch.c:504` `int pf_pool_start_page(pf_pool *p, const char *html, size_t len, const char *page_url,
          ...`
- `pf_pool_finish` (function) `src/prefetch.c:540` `void pf_pool_finish(pf_pool *p)`
- `pf_pooled_fetch` (function) `src/prefetch.c:561` `int pf_pooled_fetch(void *vctx, const char *method, const char *url,
                    const ch...`

## src/prefs.c
Depends on: `include/prefs.h`, `include/zoom.h`
- `url_valid` (function) `src/prefs.c:26` `static int url_valid(const char *url)` -- A representable URL: 1..PREFS_MAX_URL-1 bytes, no control bytes, no DEL. * Space is allowed (local paths may carry...
- `title_clean` (function) `src/prefs.c:39` `static char *title_clean(const char *src)` -- Copies src into a fresh buffer, mapping control bytes/DEL to ' ' and truncating to PREFS_MAX_TITLE bytes on a UTF-8...
- `prefs_init` (function) `src/prefs.c:66` `void prefs_init(prefs_state *p)`
- `prefs_free` (function) `src/prefs.c:74` `void prefs_free(prefs_state *p)`
- `bookmark_push` (function) `src/prefs.c:91` `static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title)` -- Appends a cleaned bookmark.
- `history_push_back` (function) `src/prefs.c:109` `static prefs_status history_push_back(prefs_state *p, const char *url)` -- Appends a history entry at the BACK preserving document order (parser path; * the API path inserts at the front).
- `prefs_bookmark_index` (function) `src/prefs.c:125` `int prefs_bookmark_index(const prefs_state *p, const char *url)`
- `prefs_bookmark_toggle` (function) `src/prefs.c:132` `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,
                             ...`
- `prefs_history_add` (function) `src/prefs.c:152` `prefs_status prefs_history_add(prefs_state *p, const char *url)`
- `prefs_format` (function) `src/prefs.c:183` `prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len)`
- `apply_kv` (function) `src/prefs.c:231` `static void apply_kv(prefs_state *out, const char *key, long val)` -- } for (size_t i = 0; i < p->history_len; ++i) { size_t space = cap - n; if (space == 0) break; int r = snprintf(buf...
- `prefs_parse` (function) `src/prefs.c:247` `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)`
- `ci_eq` (function) `src/prefs.c:313` `static int ci_eq(char a, char b)`
- `ci_starts` (function) `src/prefs.c:319` `static int ci_starts(const char *s, const char *q)`
- `ci_contains` (function) `src/prefs.c:327` `static int ci_contains(const char *s, const char *q)`
- `url_prefix_match` (function) `src/prefs.c:336` `static int url_prefix_match(const char *url, const char *q)` -- Prefix match as the user types it: the raw URL, past the scheme, and past a * leading "www." ("wiki" hits...
- `sugg_push` (function) `src/prefs.c:348` `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,
                      cons...` -- Prefix match as the user types it: the raw URL, past the scheme, and past a * leading "www." ("wiki" hits...
- `prefs_suggest` (function) `src/prefs.c:357` `int prefs_suggest(const prefs_state *p, const char *query,
                  char *out, size_t ro...`
- `sb_put` (function) `src/prefs.c:382` `static void sb_put(sbuf *b, const char *s, size_t n)`
- `sb_str` (function) `src/prefs.c:397` `static void sb_str(sbuf *b, const char *s)`
- `sb_esc` (function) `src/prefs.c:400` `static void sb_esc(sbuf *b, const char *s)` -- while (nc < b->len + n + 1) nc *= 2; char *nd = (char *)realloc(b->data, nc); if (nd == NULL) { b->oom = 1; return...
- `sb_link_item` (function) `src/prefs.c:413` `static void sb_link_item(sbuf *b, const char *url, const char *label)`
- `prefs_bookmarks_page` (function) `src/prefs.c:421` `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)`

## src/profile.c
Depends on: `include/disk_store.h`, `include/profile.h`
- `join_path` (function) `src/profile.c:29` `static int join_path(const profile_ctx *ctx, const char *name,
                     char *out, si...`
- `keyfile_create` (function) `src/profile.c:36` `static profile_status keyfile_create(const char *dir, const char *path,
                         ...` -- #include <unistd.h> #include <openssl/crypto.h> #include <openssl/rand.h> #define PROFILE_KEYFILE_LEN (LS_SALT_LEN +...
- `profile_open` (function) `src/profile.c:59` `profile_status profile_open(profile_ctx *ctx, const char *dir)`
- `map_ds` (function) `src/profile.c:98` `static profile_status map_ds(ds_status ds)`
- `profile_load` (function) `src/profile.c:112` `profile_status profile_load(const profile_ctx *ctx, prefs_state *out)`
- `profile_save` (function) `src/profile.c:133` `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p)`
- `profile_close` (function) `src/profile.c:149` `void profile_close(profile_ctx *ctx)`

## src/render_doc.c
Depends on: `include/box_style.h`, `include/css.h`, `include/data_url.h`, `include/render_doc.h`, `include/url.h`, `include/util.h`
- `utf8_sanitized_dup` (function) `src/render_doc.c:28` `static char *utf8_sanitized_dup(const char *s)`
- `rd_push` (function) `src/render_doc.c:60` `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,
                 ...` -- Appends one block, taking owned copies of text (required) and href (optional). * Returns 0 on success, -1 on...
- `rd_push_input` (function) `src/render_doc.c:211` `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` -- Appends an RD_INPUT block, copying text (placeholder/label), the form action * (href), and the control name/value.
- `place` (function) `src/render_doc.c:237` `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never...`
- `resolve_image_decision` (function) `src/render_doc.c:247` `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,
        ...` -- Resolves raw_src (possibly relative, or a data: URI) against top_level_url and judges it under the exact same policy...
- `rd_build` (function) `src/render_doc.c:269` `rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_u...`
- `unset` (function) `src/render_doc.c:677` `* background paints as if unset (no border/box-shadow-style
                 * "broken image" pla...`
- `rd_free` (function) `src/render_doc.c:742` `void rd_free(rd_doc *d)`
- `rd_count` (function) `src/render_doc.c:759` `size_t rd_count(const rd_doc *d)`
- `rd_at` (function) `src/render_doc.c:763` `const rd_block *rd_at(const rd_doc *d, size_t i)`
- `rd_box_count` (function) `src/render_doc.c:768` `size_t rd_box_count(const rd_doc *d)`
- `rd_box_at` (function) `src/render_doc.c:772` `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)`
- `rd_cont_count` (function) `src/render_doc.c:777` `size_t rd_cont_count(const rd_doc *d)`
- `rd_cont_at` (function) `src/render_doc.c:781` `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)`
- `rd_kind_name` (function) `src/render_doc.c:786` `const char *rd_kind_name(rd_kind k)`
- `rd_block_heading_level` (function) `src/render_doc.c:800` `int rd_block_heading_level(const rd_block *b)`
- `rd_block_tag` (function) `src/render_doc.c:811` `const char *rd_block_tag(const rd_block *b)`
- `rd_input_label` (function) `src/render_doc.c:842` `const char *rd_input_label(int input_type)`
- `rd_input_invisible` (function) `src/render_doc.c:862` `int rd_input_invisible(int input_type)`
- `rd_image_label` (function) `src/render_doc.c:866` `const char *rd_image_label(rdp_img_decision d)`
- `rd_image_fail_label` (function) `src/render_doc.c:877` `const char *rd_image_fail_label(img_fail_reason reason)`

## src/render_policy.c
Depends on: `include/data_url.h`, `include/render_policy.h`, `include/request_policy.h`
- `rdp_caps_safe` (function) `src/render_policy.c:17` `rdp_caps rdp_caps_safe(void)`
- `rdp_is_tracking_pixel` (function) `src/render_policy.c:22` `int rdp_is_tracking_pixel(int w, int h)`
- `rdp_image_decision` (function) `src/render_policy.c:28` `rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char...`
- `rdp_img_reason` (function) `src/render_policy.c:63` `const char *rdp_img_reason(rdp_img_decision d)`
- `rdp_images_warning` (function) `src/render_policy.c:74` `const char *rdp_images_warning(void)`

## src/renderer.c
Depends on: `include/html_parse.h`, `include/os_sandbox.h`, `include/renderer.h`, `include/util.h`
- `child_render` (function) `src/renderer.c:25` `static void child_render(int wfd, const char *html, size_t len)`
- `write_full` (function) `src/renderer.c:40` `&& write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 || write_full(wfd, title, tl) == 0) && write_full(wfd, &xl...`
- `read_field` (function) `src/renderer.c:53` `static int read_field(int fd, char **out, size_t *out_len)`
- `rd_render_html` (function) `src/renderer.c:70` `rd_status rd_render_html(const char *html, size_t len, rd_result *out)`
- `rd_result_free` (function) `src/renderer.c:120` `void rd_result_free(rd_result *out)`

## src/request_policy.c
Depends on: `include/psl_data.h`, `include/request_policy.h`
- `lower` (function) `src/request_policy.c:22` `static char lower(char c)`
- `ci_starts_with` (function) `src/request_policy.c:26` `static int ci_starts_with(const char *s, const char *prefix)`
- `psl_cmp` (function) `src/request_policy.c:36` `static int psl_cmp(const void *key, const void *elem)`
- `psl_in` (function) `src/request_policy.c:40` `static int psl_in(const char *const *arr, size_t n, const char *key)`
- `public_suffix_labels` (function) `src/request_policy.c:48` `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)` -- Number of labels of the public suffix (eTLD) of a lowercased host, applying the full PSL algorithm: exception rules...
- `rp_host_of` (function) `src/request_policy.c:76` `int rp_host_of(const char *url, char *out, size_t out_size)`
- `rp_site_of` (function) `src/request_policy.c:102` `int rp_site_of(const char *host, char *out, size_t out_size)`
- `rp_same_site` (function) `src/request_policy.c:134` `int rp_same_site(const char *top_level_url, const char *request_url)`
- `rp_evaluate` (function) `src/request_policy.c:143` `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)`
- `hdr_lower` (function) `src/request_policy.c:162` `static int hdr_lower(int c)`
- `hdr_name_ieq` (function) `src/request_policy.c:164` `static int hdr_name_ieq(const char *a, size_t alen, const char *lit)`
- `hdr_name_has_prefix` (function) `src/request_policy.c:171` `static int hdr_name_has_prefix(const char *a, size_t alen, const char *lit)`
- `hdr_token_char` (function) `src/request_policy.c:178` `static int hdr_token_char(unsigned char c)`
- `hdr_forbidden` (function) `src/request_policy.c:184` `static int hdr_forbidden(const char *n, size_t len)` -- static int hdr_name_has_prefix(const char *a, size_t alen, const char *lit) { size_t n = strlen(lit); if (alen < n)...
- `rp_sanitize_request_headers` (function) `src/request_policy.c:197` `int rp_sanitize_request_headers(const char *raw, char *out, size_t cap)`

## src/secure_fetch.c
Depends on: `include/anti_fp.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/url.h`
- `ci_starts_with` (function) `src/secure_fetch.c:46` `static int ci_starts_with(const char *haystack, const char *prefix)` -- /* --- small helpers (no libc locale dependence) --- static int ci_equal(const char *a, const char *b) { while (*a...
- `ci_index` (function) `src/secure_fetch.c:58` `static long ci_index(const char *haystack, const char *needle)` -- /* Case-insensitive: does haystack start with prefix? static int ci_starts_with(const char *haystack, const char...
- `sf_share_lock` (function) `src/secure_fetch.c:74` `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...`
- `sf_share_unlock` (function) `src/secure_fetch.c:80` `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)`
- `sf_global_init` (function) `src/secure_fetch.c:87` `void sf_global_init(void)`
- `sf_cookie_line_matches` (function) `src/secure_fetch.c:112` `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...`
- `sf_url_host_path` (function) `src/secure_fetch.c:167` `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...` -- Extracts host + path from a validated https url into caller buffers (path defaults * to "/").
- `sf_cookie_header_for` (function) `src/secure_fetch.c:182` `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)`
- `sf_cookie_put` (function) `src/secure_fetch.c:211` `void sf_cookie_put(const char *url, const char *namevalue)`
- `sf_config_default` (function) `src/secure_fetch.c:232` `sf_config sf_config_default(void)`
- `header_value_clean` (function) `src/secure_fetch.c:258` `static int header_value_clean(const char *s)` -- c.password = NULL; c.insecure = 0; c.impersonate = 0; /* default hardened PQ-hybrid ClientHello; opt-in per trusted...
- `sf_user_agent_or_default` (function) `src/secure_fetch.c:264` `const char *sf_user_agent_or_default(const char *ua)`
- `sf_accept_language_or_default` (function) `src/secure_fetch.c:268` `const char *sf_accept_language_or_default(const char *lang)`
- `sf_impersonate_kex_groups` (function) `src/secure_fetch.c:272` `const char *sf_impersonate_kex_groups(void)`
- `sf_impersonate_tls13_ciphers` (function) `src/secure_fetch.c:273` `const char *sf_impersonate_tls13_ciphers(void)`
- `sf_validate_url` (function) `src/secure_fetch.c:277` `sf_status sf_validate_url(const char *url)`
- `sf_url_is_http` (function) `src/secure_fetch.c:285` `static int sf_url_is_http(const char *url)` -- Nonzero iff url is "http://host..." (case-insensitive) with a non-empty host.
- `sf_check_tls_version` (function) `src/secure_fetch.c:297` `sf_status sf_check_tls_version(const char *negotiated_version)`
- `sf_check_group_is_pq` (function) `src/secure_fetch.c:302` `sf_status sf_check_group_is_pq(const char *negotiated_group)`
- `sf_check_chain_policy` (function) `src/secure_fetch.c:311` `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)`
- `sf_enforce_policy` (function) `src/secure_fetch.c:321` `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...`
- `copy_checked` (function) `src/secure_fetch.c:352` `static int copy_checked(char *dst, size_t dstsz, const char *src)`
- `sf_is_redirect_code` (function) `src/secure_fetch.c:361` `int sf_is_redirect_code(long http_code)`
- `sf_header_value` (function) `src/secure_fetch.c:368` `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz)`
- `sf_parse_location_header` (function) `src/secure_fetch.c:390` `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)`
- `sf_resolve_redirect` (function) `src/secure_fetch.c:408` `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...`
- `module` (function) `src/secure_fetch.c:413` `* pure url module (DRY);`
- `sf_ci_prefix` (function) `src/secure_fetch.c:420` `static int sf_ci_prefix(const char *s, const char *p)` -- Reference resolution + the https-only / no-downgrade policy live in the pure url module (DRY); a redirect is just a...
- `sf_response_free` (function) `src/secure_fetch.c:460` `void sf_response_free(sf_response *resp)`
- `progress` (function) `src/secure_fetch.c:499` `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);`
- `copy_bounded` (function) `src/secure_fetch.c:530` `static void copy_bounded(char *dst, size_t dstsz, const char *src)`
- `get_negotiated_group_name` (function) `src/secure_fetch.c:541` `static const char *get_negotiated_group_name(SSL *ssl)` -- static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len); static void...
- `database` (function) `src/secure_fetch.c:545` `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid...`
- `group` (function) `src/secure_fetch.c:559` `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);`
- `tls_capture_try` (function) `src/secure_fetch.c:574` `static void tls_capture_try(tls_capture *cap)` -- nid = SSL_get_shared_group(ssl, 0); #endif if (nid == 0) { return NULL; /* There is no negotiated group (e.g., TLS...
- `tls_capture_from_ssl` (function) `src/secure_fetch.c:584` `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)` -- static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl); /* Idempotent: takes the TLS snapshot the first time...
- `this` (function) `src/secure_fetch.c:591` `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and...`
- `header_cb` (function) `src/secure_fetch.c:610` `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` -- Fires for every HTTP response (status line + headers) even when there is no * body, so it is the reliable point to...
- `write_cb` (function) `src/secure_fetch.c:667` `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)`
- `name_is_pq_sig` (function) `src/secure_fetch.c:699` `static int name_is_pq_sig(int pknid)` -- if (grown == NULL) { sink->overflow = 2; /* OOM marker return 0; } sink->data = grown; sink->cap = newcap; }...
- `inspect_chain` (function) `src/secure_fetch.c:709` `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` -- Walks the verified chain into *info. sigbuf receives the leaf signature alg name. * Returns 0 on success, nonzero if...
- `map_curl_error` (function) `src/secure_fetch.c:762` `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)`
- `add_header` (function) `src/secure_fetch.c:803` `static int add_header(struct curl_slist **h, const char *line)` -- Appends one header line without losing the list on OOM (the plain "h = curl_slist_append(h, ...)" idiom dropped the...
- `sf_setup_handle` (function) `src/secure_fetch.c:817` `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,
           ...` -- The ONE place a curl handle is configured for a request (spec/secure_fetch.md): URL, realm proxy, TLS floor + KE...
- `redirect` (function) `src/secure_fetch.c:892` `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...`
- `sf_perform` (function) `src/secure_fetch.c:984` `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...` -- The shared request engine for sf_get and sf_post.
- `sf_get` (function) `src/secure_fetch.c:1144` `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)`
- `sf_post` (function) `src/secure_fetch.c:1148` `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...`
- `sf_rcache_clear` (function) `src/secure_fetch.c:1178` `void sf_rcache_clear(void)`
- `sf_rcache_set_backing` (function) `src/secure_fetch.c:1189` `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx)`
- `rcache_put_ram` (function) `src/secure_fetch.c:1197` `static int rcache_put_ram(const char *from, const char *to, time_t now)`
- `sf_rcache_put` (function) `src/secure_fetch.c:1216` `int sf_rcache_put(const char *from, const char *to, time_t now)`
- `sf_rcache_get` (function) `src/secure_fetch.c:1226` `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap)`
- `sf_get_follow` (function) `src/secure_fetch.c:1255` `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...`
- `ws_ssl_info_cb` (function) `src/secure_fetch.c:1318` `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)` -- An upgraded (CONNECT_ONLY) connection never runs the header callback that snapshots TLS for a fetch, and curl no...
- `ws_ssl_ctx_cb` (function) `src/secure_fetch.c:1325` `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)`
- `sf_ws_url_check` (function) `src/secure_fetch.c:1339` `sf_status sf_ws_url_check(const char *url)`
- `ws_free` (function) `src/secure_fetch.c:1351` `static void ws_free(sf_ws *ws)`
- `sf_ws_open` (function) `src/secure_fetch.c:1360` `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)`
- `sf_ws_send` (function) `src/secure_fetch.c:1415` `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)`
- `sf_ws_recv` (function) `src/secure_fetch.c:1438` `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)`
- `sf_ws_fd` (function) `src/secure_fetch.c:1460` `int sf_ws_fd(const sf_ws *ws)`
- `sf_ws_close` (function) `src/secure_fetch.c:1467` `void sf_ws_close(sf_ws *ws)`
- `sf_fallback_policy` (function) `src/secure_fetch.c:1478` `int sf_fallback_policy(sf_status failed, sf_policy tried, int allowlisted, sf_policy *next)`
- `sf_downgrade_of` (function) `src/secure_fetch.c:1492` `static int sf_downgrade_of(sf_policy p)`
- `sf_attempt_get` (function) `src/secure_fetch.c:1501` `static sf_status sf_attempt_get(const char *url, const sf_config *cfg, sf_response *out,
        ...`
- `sf_attempt_post` (function) `src/secure_fetch.c:1507` `static sf_status sf_attempt_post(const char *url, const sf_config *cfg, sf_response *out,
       ...`
- `sf_navigable` (function) `src/secure_fetch.c:1512` `static sf_status sf_navigable(sf_attempt_fn attempt, const char *url, sf_config *cfg,
           ...`
- `sf_get_follow_navigable` (function) `src/secure_fetch.c:1532` `sf_status sf_get_follow_navigable(const char *url, sf_config *cfg, sf_response *out,
            ...`
- `sf_post_navigable` (function) `src/secure_fetch.c:1537` `sf_status sf_post_navigable(const char *url, sf_config *cfg, const void *body,
                  ...`

## src/svg_render.c
Depends on: `include/css_color.h`, `include/svg_render.h`
- `sv_is_space` (function) `src/svg_render.c:21` `static int sv_is_space(char c)`
- `sv_is_digit` (function) `src/svg_render.c:25` `static int sv_is_digit(char c)`
- `sv_lower` (function) `src/svg_render.c:27` `static char sv_lower(char c)`
- `sv_span_eq` (function) `src/svg_render.c:32` `static int sv_span_eq(const char *s, size_t n, const char *lit)` -- /* --- small scanning helpers (no locale, no allocation) --- static int sv_is_space(char c) { return c == ' ' || c...
- `sv_sep` (function) `src/svg_render.c:82` `static void sv_sep(const char *s, size_t n, size_t *i)` -- if (ev > 300) ev = 300; double m = pow(10.0, eneg ? -(double)ev : (double)ev); v *= m; p = q; } } if (neg) v = -v...
- `sv_attr_get` (function) `src/svg_render.c:99` `static const char *sv_attr_get(const sv_attr *at, size_t nat, const char *name, size_t *len)` -- while (*i < n && sv_is_space(s[*i])) ++*i; } /* --- attribute lookup
- `sv_attr_num` (function) `src/svg_render.c:108` `static double sv_attr_num(const sv_attr *at, size_t nat, const char *name, double dflt)` -- Numeric attribute, or `dflt` when absent/malformed.
- `sv_mat_identity` (function) `src/svg_render.c:161` `static void sv_mat_identity(double *m)`
- `sv_mat_mul` (function) `src/svg_render.c:166` `static void sv_mat_mul(const double *a, const double *b, double *out)` -- int    fill, stroke; double stroke_w; int    opacity, fill_opacity, stroke_opacity; int    fill_even_odd; int...
- `sv_parse_transform` (function) `src/svg_render.c:179` `static void sv_parse_transform(const char *s, size_t n, double *m)` -- Parses a `transform` list and composes it onto ctx->m.
- `sv_style_next` (function) `src/svg_render.c:238` `static int sv_style_next(const char *s, size_t n, size_t *i,
                         const char ...` -- Reads one `name:value` declaration out of a style="" attribute.
- `sv_apply_prop` (function) `src/svg_render.c:260` `static void sv_apply_prop(sv_ctx *ctx, const char *nm, size_t nl,
                          const...` -- if (*i >= n || s[*i] != ':') { while (*i < n && s[*i] != ';') ++*i; return 1; } ++*i; size_t vs = *i; while (*i < n...
- `sv_ctx_from_attrs` (function) `src/svg_render.c:307` `static void sv_ctx_from_attrs(sv_ctx *ctx, const sv_attr *at, size_t nat)` -- Folds every presentation attribute of the current tag (and its style="") into a copy of the inherited context.
- `sv_new_shape` (function) `src/svg_render.c:324` `static sv_shape *sv_new_shape(sv_image *im, int kind, const sv_ctx *ctx)`
- `sv_parse_points` (function) `src/svg_render.c:343` `static void sv_parse_points(sv_image *im, sv_shape *sh, const char *s, size_t n)` -- sh->fill = ctx->fill; sh->stroke = ctx->stroke; sh->stroke_w = ctx->stroke_w; sh->opacity = ctx->opacity...
- `sv_new_seg` (function) `src/svg_render.c:363` `static sv_seg *sv_new_seg(sv_image *im, sv_shape *sh)`
- `sv_seg_move` (function) `src/svg_render.c:371` `static int sv_seg_move(sv_image *im, sv_shape *sh, double x, double y)`
- `sv_seg_line` (function) `src/svg_render.c:378` `static int sv_seg_line(sv_image *im, sv_shape *sh, double x, double y)`
- `sv_seg_cubic` (function) `src/svg_render.c:385` `static int sv_seg_cubic(sv_image *im, sv_shape *sh,
                        double x1, double y1,...`
- `sv_arc_to_cubics` (function) `src/svg_render.c:399` `static int sv_arc_to_cubics(sv_image *im, sv_shape *sh,
                            double x0, do...` -- Endpoint-parameterised elliptical arc -> up to 4 cubic segments (F.6.5 of the SVG spec).
- `sv_flag` (function) `src/svg_render.c:477` `static int sv_flag(const char *s, size_t n, size_t *i, double *out)` -- An arc flag (SVG 1.1 path grammar): exactly one '0' or '1' character, with no separator required after it -- `a5 5 0...
- `sv_parse_path` (function) `src/svg_render.c:488` `static void sv_parse_path(sv_image *im, sv_shape *sh, const char *s, size_t n)` -- Parses path data.
- `point` (function) `src/svg_render.c:567` `* current point (SVG 8.3.6). */ int had = (prev == 'C' || prev == 'c' || prev == 'S' || prev == 's');`
- `sv_is_dropped_element` (function) `src/svg_render.c:646` `static int sv_is_dropped_element(const char *name, size_t n)` -- True for elements whose whole subtree is dropped. <image>/<use>/<foreignObject> can name external resources...
- `sv_scan_attrs` (function) `src/svg_render.c:658` `static void sv_scan_attrs(const char *s, size_t n, size_t *i,
                          sv_attr *...` -- Scans the attributes of a tag whose body starts at s[*i] (just past the name). * Stops at '>' and reports whether...
- `sv_skip_subtree` (function) `src/svg_render.c:704` `static void sv_skip_subtree(const char *s, size_t n, size_t *i, const char *name, size_t nlen)` -- Skips to just past the matching close tag of `name`, honouring nesting.
- `sv_collect_text` (function) `src/svg_render.c:736` `static void sv_collect_text(const char *s, size_t n, size_t *i, char *dst, size_t cap)` -- Collects the literal text of the element that just opened, up to its close tag, * into a bounded buffer.
- `sv_fit` (function) `src/svg_render.c:754` `void sv_fit(const sv_image *img, double dw, double dh,
            double *scale, double *off_x, ...`
- `sv_parse` (function) `src/svg_render.c:774` `sv_status sv_parse(const char *markup, size_t len, sv_image *out)`
- `sv_parse_ex` (function) `src/svg_render.c:778` `sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill)`

## src/tab.c
Depends on: `include/anti_fp.h`, `include/box_tree.h`, `include/css.h`, `include/css_computed.h`, `include/css_gradient.h`, `include/data_url.h`, `include/dom.h`, `include/flex_layout.h`, `include/freebug.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/identity.h`, `include/image_decode.h`, `include/import_map.h`, `include/js_dom.h`, `include/js_env.h`, `include/js_sandbox.h`, `include/js_trusted.h`, `include/link_nav.h`, `include/os_sandbox.h`, `include/page_view.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/tab.h`, `include/url.h`, `include/util.h`, `include/web_storage.h`
- `clip_pm_ok` (function) `src/tab.c:77` `static int clip_pm_ok(int32_t v)` -- A clip-edge percentage off the wire: per-mille, bounded like CSS_PCT_MAX (a hostile * worker cannot hand the painter...
- `rad_len_ok` (function) `src/tab.c:83` `static int rad_len_ok(int32_t v, int dflt)` -- A radial-gradient length off the wire (cg_radial encoding): per-mille 0..1e6, or * -(px)-1 with px <= 100000, or...
- `child_reset_page` (function) `src/tab.c:184` `static void child_reset_page(child_state *cs)`
- `sig_mix` (function) `src/tab.c:204` `static uint64_t sig_mix(uint64_t h, const char *s, size_t n)`
- `computed_signature` (function) `src/tab.c:212` `static uint64_t computed_signature(const dom_index *idx)` -- What the retained cascade depends on: every <style> text plus the attributes of <html>/<body> (class/data-* theme...
- `policy` (function) `src/tab.c:292` `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a
 * compromi...`
- `prof_now_ms` (function) `src/tab.c:358` `static double prof_now_ms(void)` -- if (read_full(cs->rfd, &xlen, sizeof xlen) != 0 || xlen > SF_RESPONSE_HEADERS_MAX) { free(rbody); free(ctype)...
- `prof_on` (function) `src/tab.c:363` `static int prof_on(void)`
- `prof_lap` (function) `src/tab.c:368` `static void prof_lap(const char *what, double *t0)`
- `run_js` (function) `src/tab.c:379` `* regardless of run_js (a no-JS load simply never records a request). */
static int child_load(ch...`
- `buffer` (function) `src/tab.c:427` `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...`
- `write_field` (function) `src/tab.c:458` `static int write_field(int fd, const char *s)` -- Writes one length-prefixed string field (the write mirror of read_field): a size_t * length then the bytes, with...
- `blocks` (function) `src/tab.c:492` `*
 * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the
 * grid arr...`
- `FB_MAX_FILE_BYTES` (function) `src/tab.c:923` `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...`
- `budget_remaining_ms` (function) `src/tab.c:953` `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` -- Milliseconds of `budget_ms` still left since `start` (CLOCK_MONOTONIC), 0 if spent. * Used to share one page-wide JS...
- `ctype_is_javascript` (function) `src/tab.c:967` `static int ctype_is_javascript(const char *ctype)` -- Content-Type gate for an external script's response (anti type-confusion, fail closed for real content types)...
- `ctype_is_css` (function) `src/tab.c:976` `static int ctype_is_css(const char *ctype)` -- Content-Type gate for an external stylesheet (Hito 27), same shape as the script gate: a missing/empty type is...
- `log_external_skip` (function) `src/tab.c:984` `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...` -- Freebug note about an external subresource (script/stylesheet) that was not used (skipped or refused).
- `run` (function) `src/tab.c:1002` `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...`
- `tab_url_resolve` (function) `src/tab.c:1051` `static int tab_url_resolve(void *ctx, const char *base, const char *ref,
                        ...` -- Plain URL resolution of ref against base (https, or a local file confined to its * document's directory): the...
- `tab_mod_resolve` (function) `src/tab.c:1060` `static int tab_mod_resolve(void *host, const char *base, const char *spec,
                      ...`
- `tab_mod_fetch` (function) `src/tab.c:1090` `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` -- Loads a module's source through the trusted parent (TAG_SUBREQ: the full network policy applies), only inside a...
- `write_history` (function) `src/tab.c:1112` `static int write_history(int wfd, child_state *cs)` -- Writes the history block of a response: [len][ops "K url\n"...][go:int32] * (spec/js_dom.md 7e).
- `window` (function) `src/tab.c:1131` `* net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs)`
- `child_handle_load` (function) `src/tab.c:1176` `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...`
- `fallback` (function) `src/tab.c:1257` `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it...`
- `WHERE` (function) `src/tab.c:1447` `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...`
- `content` (function) `src/tab.c:1507` `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...`
- `once` (function) `src/tab.c:1555` `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);`
- `swap` (function) `src/tab.c:1564` `* display:none hiding an element via class swap (CSS, not
     * DOM removal). */
    if (ok && v...`
- `write_full` (function) `src/tab.c:1585` `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0) && write_view(wfd...`
- `write_ws` (function) `src/tab.c:1609` `static int write_ws(int wfd, child_state *cs)` -- Writes the WebSocket block of a response: [n:int32] then per op * [kind:int32][id:int32][len][bytes] (spec/js_dom.md...
- `write_storage` (function) `src/tab.c:1626` `static int write_storage(int wfd, child_state *cs)` -- int32_t cnt = (int32_t)n; int rc = (write_full(wfd, &cnt, sizeof cnt) == 0) ?
- `write_opens` (function) `src/tab.c:1640` `static int write_opens(int wfd, child_state *cs)` -- static int write_storage(int wfd, child_state *cs) { char *blob = NULL; size_t len = 0; int32_t dirty = (cs->js !=...
- `child_next_timer_ms` (function) `src/tab.c:1652` `static int32_t child_next_timer_ms(child_state *cs)` -- Smallest pending JS timer delay (__nextTimerMs), or -1 when JS is absent, the * eval fails, or nothing is pending.
- `child_handle_mutation` (function) `src/tab.c:1667` `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...` -- Fire click handlers for node_id (OP_CLICK) or advance the virtual timer clock (OP_TICK), then re-derive the view so...
- `child_handle_click` (function) `src/tab.c:1746` `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)`
- `child_handle_tick` (function) `src/tab.c:1750` `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)`
- `child_handle_event` (function) `src/tab.c:1760` `static void child_handle_event(int wfd, child_state *cs)`
- `child_handle_mouse` (function) `src/tab.c:1808` `static void child_handle_mouse(int wfd, child_state *cs)` -- Handles a mouse DOM event (OP_MOUSE).
- `geom_parent` (function) `src/tab.c:1838` `static dom_node_id geom_parent(void *ctx, dom_node_id n)`
- `child_handle_geom` (function) `src/tab.c:1846` `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` -- OP_GEOM (spec/js_geom.md): installs the parent's laid-out geometry into the page's JS, aggregated into ancestors...
- `child_handle_submit` (function) `src/tab.c:1872` `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` -- Fires a submit event on the form enclosing node_id.
- `child_handle_eval` (function) `src/tab.c:1906` `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` -- Response: [ok:int32][is_exception:int32][value_len][value]. ok==0 means a worker-level failure (no page loaded); a...
- `child_handle_decode_image` (function) `src/tab.c:1947` `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` -- Response: [ok:int32] then, when ok, [w:u32][h:u32][stride:u32][len:size_t][data].
- `child_handle_decode_image_b64` (function) `src/tab.c:1969` `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)` -- data: URI images: the parent only sliced the base64 payload (pure pointer arithmetic, no interpretation); the base64...
- `gen_session_key` (function) `src/tab.c:1981` `static uint64_t gen_session_key(void)`
- `tab_worker_run` (function) `src/tab.c:2001` `static void tab_worker_run(int rfd, int wfd)` -- The confined request loop.
- `EPIPE` (function) `src/tab.c:2003` `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();`
- `tzset` (function) `src/tab.c:2019` `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);`
- `depth` (function) `src/tab.c:2033` `* defense in depth (seccomp already excludes open/socket/exec);`
- `parse_worker_fd` (function) `src/tab.c:2225` `static int parse_worker_fd(const char *s, int *out)` -- free(buf); free(url); free(cookies); free(storage); } child_reset_page(&cs); fb_buffer_free(&cs.log); _exit(0); } /*...
- `tab_parse_worker_args` (function) `src/tab.c:2237` `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)`
- `tab_worker_dispatch` (function) `src/tab.c:2247` `void tab_worker_dispatch(int argc, char **argv)`
- `load` (function) `src/tab.c:2264` `* subresource requests this load (set per page: host in allow.conf AND js.conf);`
- `ignore_sigpipe` (function) `src/tab.c:2301` `static void ignore_sigpipe(void)` -- A write to a dead child must not kill the parent with SIGPIPE.
- `tab_refresh_alive` (function) `src/tab.c:2308` `static void tab_refresh_alive(tab *t)`
- `read_field` (function) `src/tab.c:2327` `static int read_field(int fd, char **out, size_t *out_len)` -- Read one length-prefixed owned field from the child, capped against * amplification. *out is NUL-terminated.
- `read_view` (function) `src/tab.c:2343` `static int read_view(int fd, pv_view **out)` -- Reads a display list serialised by write_view into a fresh pv_view.
- `tests` (function) `src/tab.c:2418` `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...`
- `layout` (function) `src/tab.c:2524` `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....`
- `column` (function) `src/tab.c:2535` `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...`
- `read_console` (function) `src/tab.c:2870` `static int read_console(int fd, fb_buffer *out)` -- Reads the console section written by write_console into out (a zero-initialised fb_buffer).
- `send_request` (function) `src/tab.c:2907` `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` -- if (elen != 0) { txt = (char *)malloc(elen); if (txt == NULL) { free(file); return -1; } if (read_full(fd, txt...
- `io_failure` (function) `src/tab.c:2917` `static tab_status io_failure(tab *t)`
- `exec_worker_child` (function) `src/tab.c:2925` `static void exec_worker_child(int rfd, int wfd)` -- Child half of the fork: re-exec a fresh worker image so it inherits NONE of the parent's address space (no other...
- `tab_set_fetcher` (function) `src/tab.c:2997` `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)`
- `tab_set_css_sink` (function) `src/tab.c:3003` `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)`
- `tab_set_op_net_budget_ms` (function) `src/tab.c:3009` `void tab_set_op_net_budget_ms(tab *t, int ms)`
- `tab_set_net_allowed` (function) `src/tab.c:3013` `void tab_set_net_allowed(tab *t, int allowed)`
- `tab_set_css_allowed` (function) `src/tab.c:3018` `void tab_set_css_allowed(tab *t, int allowed)`
- `tab_last_subreq_stats` (function) `src/tab.c:3023` `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)`
- `tab_set_identity` (function) `src/tab.c:3028` `void tab_set_identity(tab *t, const char *serialized)`
- `tab_set_viewport_w` (function) `src/tab.c:3036` `void tab_set_viewport_w(tab *t, int px)`
- `tab_set_cookies` (function) `src/tab.c:3041` `void tab_set_cookies(tab *t, const char *cookies)`
- `tab_subreq_permitted` (function) `src/tab.c:3047` `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)`
- `tab_report_response_headers` (function) `src/tab.c:3061` `void tab_report_response_headers(const char *lines)`
- `tab_inflight_request_headers` (function) `src/tab.c:3073` `const char *tab_inflight_request_headers(void)`
- `answered` (function) `src/tab.c:3082` `* A refused frame is still consumed and answered (status 0), so the protocol never
 * desyncs. Re...`
- `hist_ops_free` (function) `src/tab.c:3155` `static void hist_ops_free(tab_hist_op *ops, size_t n)`
- `is_activation_event` (function) `src/tab.c:3220` `static int is_activation_event(const char *type)` -- HTML 6.4.2 activation-triggering input events: only these let a page open a * window.
- `open_urls_free` (function) `src/tab.c:3229` `static void open_urls_free(char **u, size_t n)`
- `read_opens` (function) `src/tab.c:3239` `static tab_status read_opens(tab *t, const char *page_url, int gesture,
                         ...` -- Reads the window.open block (see write_opens).
- `ws_ops_free` (function) `src/tab.c:3268` `static void ws_ops_free(tab_ws_op *ops, size_t n)`
- `read_ws` (function) `src/tab.c:3277` `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` -- Reads the WebSocket block (see write_ws), bounded by JT_WS_MAX_OPS ops and JT_WS_MAX_BYTES of payload.
- `gate_js_nav` (function) `src/tab.c:3346` `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` -- Gates a raw JS navigation request against the page URL in the trusted parent (Zero Trust: a compromised worker...
- `tab_load` (function) `src/tab.c:3356` `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)`
- `tab_load_ex` (function) `src/tab.c:3360` `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)`
- `tab_load_full` (function) `src/tab.c:3364` `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...`
- `tab_click` (function) `src/tab.c:3563` `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)`
- `tab_tick` (function) `src/tab.c:3571` `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)`
- `tab_submit` (function) `src/tab.c:3581` `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` -- Dispatches a submit event on the form enclosing node_id.
- `tab_read_view` (function) `src/tab.c:3689` `tab_status tab_read_view(tab *t, tab_page *out)` -- Reads the TAG_RESULT + TAG_VIEW response into *out (titles + view + console). * Used by tab_mutation_request...
- `frames` (function) `src/tab.c:3695` `* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of...`
- `tab_await_result` (function) `src/tab.c:3698` `static tab_status tab_await_result(tab *t)`
- `tab_await_result_inner` (function) `src/tab.c:3706` `static tab_status tab_await_result_inner(tab *t)`
- `tab_read_view_ex` (function) `src/tab.c:3716` `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)`
- `tab_eval` (function) `src/tab.c:3811` `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)`
- `tab_decode_image_op` (function) `src/tab.c:3852` `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...` -- Shared by tab_decode_image and tab_decode_image_data_url: sends `bytes` under opcode `op` and parses the...
- `tab_decode_image` (function) `src/tab.c:3894` `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)`
- `tab_decode_image_data_url` (function) `src/tab.c:3901` `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)`
- `tab_alive` (function) `src/tab.c:3920` `int tab_alive(const tab *t)`
- `tab_child_pid` (function) `src/tab.c:3926` `pid_t tab_child_pid(const tab *t)`
- `tab_close` (function) `src/tab.c:3930` `void tab_close(tab *t)`
- `tab_page_free` (function) `src/tab.c:3947` `void tab_page_free(tab_page *p)`
- `tab_eval_result_free` (function) `src/tab.c:3977` `void tab_eval_result_free(tab_eval_result *r)`
- `tab_image_free` (function) `src/tab.c:3986` `void tab_image_free(tab_image *img)`
- `tab_geometry_send` (function) `src/tab.c:3998` `static tab_status tab_geometry_send(tab *t, const int32_t *buf, size_t words)` -- Writes one encoded geometry table and waits for its acknowledgement (serving any network the * observer callbacks it...
- `geometry_encode` (function) `src/tab.c:4016` `static int32_t *geometry_encode(const jg_table *g, size_t *words_out)`
- `tab_set_geometry` (function) `src/tab.c:4026` `tab_status tab_set_geometry(tab *t, const jg_table *g)`
- `job_discard` (function) `src/tab.c:4040` `static void job_discard(tab *t)`
- `tab_async_sync` (function) `src/tab.c:4052` `static void tab_async_sync(tab *t)` -- Waits for a running job and DISCARDS its result: any other worker call is about to change * the page, so the...
- `job_main` (function) `src/tab.c:4062` `static void *job_main(void *arg)`
- `tab_async_fd` (function) `src/tab.c:4078` `int tab_async_fd(tab *t)`
- `tab_async_busy` (function) `src/tab.c:4087` `int tab_async_busy(const tab *t)`
- `job_start` (function) `src/tab.c:4091` `static tab_status job_start(tab *t)`
- `tab_tick_async` (function) `src/tab.c:4104` `tab_status tab_tick_async(tab *t, int elapsed_ms)`
- `tab_geometry_async` (function) `src/tab.c:4114` `tab_status tab_geometry_async(tab *t, const jg_table *g)`
- `tab_async_finish` (function) `src/tab.c:4129` `tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)`
- `tab_popstate` (function) `src/tab.c:4151` `tab_status tab_popstate(tab *t, int index, tab_page *out)`
- `tab_ws_event` (function) `src/tab.c:4158` `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,
       ...`
- `tab_set_storage` (function) `src/tab.c:4178` `void tab_set_storage(tab *t, const char *blob, size_t len)`

## src/text_case.c
Depends on: `include/css.h`, `include/text_case.h`
- `pair_parity` (function) `src/text_case.c:8` `static int pair_parity(uint32_t cp)` -- Latin Extended-A and the Cyrillic historic block pair letters on adjacent code points, uppercase first.
- `tc_upper` (function) `src/text_case.c:18` `uint32_t tc_upper(uint32_t cp)`
- `tc_lower` (function) `src/text_case.c:37` `uint32_t tc_lower(uint32_t cp)`
- `tc_is_lower` (function) `src/text_case.c:54` `int tc_is_lower(uint32_t cp)`
- `utf8_decode` (function) `src/text_case.c:61` `static size_t utf8_decode(const unsigned char *s, size_t n, uint32_t *cp)` -- Decodes one UTF-8 code point of s[0,n) into *cp.
- `utf8_put` (function) `src/text_case.c:79` `static void utf8_put(uint32_t cp, size_t len, unsigned char *out)` -- if ((c >> 5) == 0x6) { if (n < 2 || (s[1] & 0xC0) != 0x80) return 0; cp = ((c & 0x1Fu) << 6) | (s[1] & 0x3Fu)...
- `utf8_len_of` (function) `src/text_case.c:91` `static size_t utf8_len_of(uint32_t cp)`
- `tc_transform` (function) `src/text_case.c:95` `size_t tc_transform(const char *s, size_t n, int transform, int word_start,
                    c...`
- `tc_smallcaps_runs` (function) `src/text_case.c:117` `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap)`


Next: [API_p11.md](API_p11.md)
