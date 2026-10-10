# Symbols (page 9 of 13)
Previous: [SYMBOLS_p8.md](SYMBOLS_p8.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `assert_edges` | function | `tests/test_box_style.c:27` | `static void assert_edges(bx_edges e, double t, double r, double b, double l)` |
| `dbl_eq` | function | `tests/test_box_style.c:22` | `static int dbl_eq(double a, double b)` |
| `main` | function | `tests/test_box_style.c:608` | `int main(void)` |
| `percentage` | function | `tests/test_box_style.c:542` | `* percentage (a plain `width:50%` leaves the px half UNSET, a plain `width:300px`  * leaves the p...` |
| `test_block_ua_box_heading_level_wins` | function | `tests/test_box_style.c:205` | `static void test_block_ua_box_heading_level_wins(void **state)` |
| `test_block_ua_box_is_content_independent` | function | `tests/test_box_style.c:194` | `static void test_block_ua_box_is_content_independent(void **state)` |
| `test_block_ua_box_is_total` | function | `tests/test_box_style.c:227` | `static void test_block_ua_box_is_total(void **state)` |
| `test_block_ua_box_list_item_wins_over_ancestor` | function | `tests/test_box_style.c:218` | `static void test_block_ua_box_list_item_wins_over_ancestor(void **state)` |
| `test_blockquote` | function | `tests/test_box_style.c:76` | `static void test_blockquote(void **state)` |
| `test_body_has_no_margin` | function | `tests/test_box_style.c:34` | `static void test_body_has_no_margin(void **state)` |
| `test_border_box_height` | function | `tests/test_box_style.c:474` | `static void test_border_box_height(void **state)` |
| `test_case_insensitive` | function | `tests/test_box_style.c:110` | `static void test_case_insensitive(void **state)` |
| `test_content_clipped` | function | `tests/test_box_style.c:492` | `static void test_content_clipped(void **state)` |
| `test_display_name` | function | `tests/test_box_style.c:374` | `static void test_display_name(void **state)` |
| `test_display_none_for_non_rendered` | function | `tests/test_box_style.c:101` | `static void test_display_none_for_non_rendered(void **state)` |
| `test_div_is_block` | function | `tests/test_box_style.c:133` | `static void test_div_is_block(void **state)` |
| `test_heading_ladder` | function | `tests/test_box_style.c:49` | `static void test_heading_ladder(void **state)` |
| `test_hr` | function | `tests/test_box_style.c:83` | `static void test_hr(void **state)` |
| `test_inline_and_inline_block` | function | `tests/test_box_style.c:90` | `static void test_inline_and_inline_block(void **state)` |
| `test_lists` | function | `tests/test_box_style.c:65` | `static void test_lists(void **state)` |
| `test_paragraph` | function | `tests/test_box_style.c:42` | `static void test_paragraph(void **state)` |
| `test_parse_display_case_and_trim` | function | `tests/test_box_style.c:347` | `static void test_parse_display_case_and_trim(void **state)` |
| `test_parse_display_errors` | function | `tests/test_box_style.c:356` | `static void test_parse_display_errors(void **state)` |
| `test_parse_display_inline_aliases` | function | `tests/test_box_style.c:338` | `static void test_parse_display_inline_aliases(void **state)` |
| `test_parse_display_keywords` | function | `tests/test_box_style.c:319` | `static void test_parse_display_keywords(void **state)` |
| `test_place_centering` | function | `tests/test_box_style.c:407` | `static void test_place_centering(void **state)` |
| `test_place_failclosed_bounds` | function | `tests/test_box_style.c:431` | `static void test_place_failclosed_bounds(void **state)` |
| `test_place_insets` | function | `tests/test_box_style.c:419` | `static void test_place_insets(void **state)` |
| `test_place_max_width_caps` | function | `tests/test_box_style.c:396` | `static void test_place_max_width_caps(void **state)` |
| `test_place_no_box_is_identity` | function | `tests/test_box_style.c:389` | `static void test_place_no_box_is_identity(void **state)` |
| `test_table_role_from_tag` | function | `tests/test_box_style.c:242` | `static void test_table_role_from_tag(void **state)` |
| `test_table_role_is_total` | function | `tests/test_box_style.c:272` | `static void test_table_role_is_total(void **state)` |
| `test_ua_case_insensitive_and_trimmed` | function | `tests/test_box_style.c:282` | `static void test_ua_case_insensitive_and_trimmed(void **state)` |
| `test_ua_code_space_is_total` | function | `tests/test_box_style.c:308` | `static void test_ua_code_space_is_total(void **state)` |
| `test_ua_fails_closed` | function | `tests/test_box_style.c:290` | `static void test_ua_fails_closed(void **state)` |
| `test_ua_list_item_is_distinct_but_unspaced` | function | `tests/test_box_style.c:181` | `static void test_ua_list_item_is_distinct_but_unspaced(void **state)` |
| `test_ua_spaced_tags_round_trip` | function | `tests/test_box_style.c:161` | `static void test_ua_spaced_tags_round_trip(void **state)` |
| `test_ua_structural_wrappers_have_no_margin` | function | `tests/test_box_style.c:144` | `static void test_ua_structural_wrappers_have_no_margin(void **state)` |
| `test_unknown_and_null_are_neutral_inline` | function | `tests/test_box_style.c:118` | `static void test_unknown_and_null_are_neutral_inline(void **state)` |
| `test_width_cap2_is_min_of_two_values` | function | `tests/test_box_style.c:523` | `static void test_width_cap2_is_min_of_two_values(void **state)` |
| `test_width_cap_pct` | function | `tests/test_box_style.c:508` | `static void test_width_cap_pct(void **state)` |
| `width` | function | `tests/test_box_style.c:552` | `* a negative width (CSS Values 4 section 10.1: out-of-range calc() results are * clamped at used-value time). */...` |
| `UNSET4` | macro | `tests/test_box_tree.c:630` | `#define UNSET4` |
| `assert_rect` | function | `tests/test_box_tree.c:28` | `static void assert_rect(const bt_node *n, double x, double y, double w, double h)` |
| `card` | function | `tests/test_box_tree.c:769` | `* containing block climbs the unplaced card(1) → placed ancestor(0, x=100). */ assert_true(dbl_eq(out[2].x, 100));` |
| `main` | function | `tests/test_box_tree.c:931` | `int main(void)` |
| `test_abspos_resolves_against_placed_ancestor` | function | `tests/test_box_tree.c:744` | `static void test_abspos_resolves_against_placed_ancestor(void **state)` |
| `test_abspos_unplaced_without_anchor_falls_to_viewport` | function | `tests/test_box_tree.c:774` | `static void test_abspos_unplaced_without_anchor_falls_to_viewport(void **state)` |
| `test_block_stacking_with_collapse` | function | `tests/test_box_tree.c:62` | `static void test_block_stacking_with_collapse(void **state)` |
| `test_box_hidden_ancestor` | function | `tests/test_box_tree.c:806` | `static void test_box_hidden_ancestor(void **state)` |
| `test_box_hidden_fail_closed` | function | `tests/test_box_tree.c:819` | `static void test_box_hidden_fail_closed(void **state)` |
| `test_box_hidden_self` | function | `tests/test_box_tree.c:794` | `static void test_box_hidden_self(void **state)` |
| `test_children_cap` | function | `tests/test_box_tree.c:388` | `static void test_children_cap(void **state)` |
| `test_depth_cap` | function | `tests/test_box_tree.c:398` | `static void test_depth_cap(void **state)` |
| `test_display_none_skipped` | function | `tests/test_box_tree.c:353` | `static void test_display_none_skipped(void **state)` |
| `test_flex_auto_margin_pushes_item` | function | `tests/test_box_tree.c:95` | `static void test_flex_auto_margin_pushes_item(void **state)` |
| `test_flex_cross_axis_align` | function | `tests/test_box_tree.c:213` | `static void test_flex_cross_axis_align(void **state)` |
| `test_flex_gap_and_justify_center` | function | `tests/test_box_tree.c:113` | `static void test_flex_gap_and_justify_center(void **state)` |
| `test_flex_negative_gap` | function | `tests/test_box_tree.c:378` | `static void test_flex_negative_gap(void **state)` |
| `test_flex_nowrap_default_single_line_unchanged` | function | `tests/test_box_tree.c:151` | `static void test_flex_nowrap_default_single_line_unchanged(void **state)` |
| `test_flex_row_grow` | function | `tests/test_box_tree.c:75` | `static void test_flex_row_grow(void **state)` |
| `test_flex_wrap_reverse_two_lines` | function | `tests/test_box_tree.c:171` | `static void test_flex_wrap_reverse_two_lines(void **state)` |
| `test_flex_wrap_row_gap_distinct_from_gap` | function | `tests/test_box_tree.c:193` | `static void test_flex_wrap_row_gap_distinct_from_gap(void **state)` |
| `test_flex_wrap_two_lines` | function | `tests/test_box_tree.c:129` | `static void test_flex_wrap_two_lines(void **state)` |
| `test_grid` | function | `tests/test_box_tree.c:270` | `static void test_grid(void **state)` |
| `test_grid_bad_columns` | function | `tests/test_box_tree.c:368` | `static void test_grid_bad_columns(void **state)` |
| `test_grid_column_span` | function | `tests/test_box_tree.c:309` | `static void test_grid_column_span(void **state)` |
| `test_grid_row_gap_distinct_from_gap` | function | `tests/test_box_tree.c:231` | `static void test_grid_row_gap_distinct_from_gap(void **state)` |
| `test_grid_weighted_tracks` | function | `tests/test_box_tree.c:291` | `static void test_grid_weighted_tracks(void **state)` |
| `test_grid_without_row_gap_falls_back_to_gap` | function | `tests/test_box_tree.c:254` | `static void test_grid_without_row_gap_falls_back_to_gap(void **state)` |
| `test_leaf` | function | `tests/test_box_tree.c:40` | `static void test_leaf(void **state)` |
| `test_leaf_with_padding` | function | `tests/test_box_tree.c:47` | `static void test_leaf_with_padding(void **state)` |
| `test_nested_flex_in_block` | function | `tests/test_box_tree.c:329` | `static void test_nested_flex_in_block(void **state)` |
| `test_null_root` | function | `tests/test_box_tree.c:35` | `static void test_null_root(void **state)` |
| `test_oof_anchor_none_on_static_chain` | function | `tests/test_box_tree.c:832` | `static void test_oof_anchor_none_on_static_chain(void **state)` |
| `test_oof_anchor_self` | function | `tests/test_box_tree.c:842` | `static void test_oof_anchor_self(void **state)` |
| `test_oof_anchor_via_ancestor` | function | `tests/test_box_tree.c:849` | `static void test_oof_anchor_via_ancestor(void **state)` |
| `test_oof_avail_stretch_and_shrink` | function | `tests/test_box_tree.c:913` | `static void test_oof_avail_stretch_and_shrink(void **state)` |
| `test_oof_fail_open` | function | `tests/test_box_tree.c:891` | `static void test_oof_fail_open(void **state)` |
| `test_oof_nested_absolute_anchor_vs_root` | function | `tests/test_box_tree.c:862` | `static void test_oof_nested_absolute_anchor_vs_root(void **state)` |
| `test_oof_relative_does_not_anchor` | function | `tests/test_box_tree.c:877` | `static void test_oof_relative_does_not_anchor(void **state)` |
| `test_positioning_absolute_against_ancestor` | function | `tests/test_box_tree.c:462` | `static void test_positioning_absolute_against_ancestor(void **state)` |
| `test_positioning_absolute_against_viewport` | function | `tests/test_box_tree.c:485` | `static void test_positioning_absolute_against_viewport(void **state)` |
| `test_positioning_doc_order_tiebreak` | function | `tests/test_box_tree.c:559` | `static void test_positioning_doc_order_tiebreak(void **state)` |
| `test_positioning_fixed_against_viewport` | function | `tests/test_box_tree.c:502` | `static void test_positioning_fixed_against_viewport(void **state)` |
| `test_positioning_nbox_cap` | function | `tests/test_box_tree.c:611` | `static void test_positioning_nbox_cap(void **state)` |
| `test_positioning_no_insets` | function | `tests/test_box_tree.c:577` | `static void test_positioning_no_insets(void **state)` |
| `test_positioning_null_args` | function | `tests/test_box_tree.c:415` | `static void test_positioning_null_args(void **state)` |
| `test_positioning_null_geometry` | function | `tests/test_box_tree.c:594` | `static void test_positioning_null_geometry(void **state)` |
| `test_positioning_relative_offset` | function | `tests/test_box_tree.c:441` | `static void test_positioning_relative_offset(void **state)` |
| `test_positioning_stacking_order` | function | `tests/test_box_tree.c:539` | `static void test_positioning_stacking_order(void **state)` |
| `test_positioning_static_unchanged` | function | `tests/test_box_tree.c:429` | `static void test_positioning_static_unchanged(void **state)` |
| `test_positioning_sticky_treated_as_relative` | function | `tests/test_box_tree.c:521` | `static void test_positioning_sticky_treated_as_relative(void **state)` |
| `test_static_position_absolute_auto_insets` | function | `tests/test_box_tree.c:633` | `static void test_static_position_absolute_auto_insets(void **state)` |
| `test_static_position_explicit_insets_win` | function | `tests/test_box_tree.c:665` | `static void test_static_position_explicit_insets_win(void **state)` |
| `test_static_position_fixed_auto_insets` | function | `tests/test_box_tree.c:649` | `static void test_static_position_fixed_auto_insets(void **state)` |
| `test_static_position_mixed_axis` | function | `tests/test_box_tree.c:686` | `static void test_static_position_mixed_axis(void **state)` |
| `test_static_position_null_arrays_legacy` | function | `tests/test_box_tree.c:726` | `static void test_static_position_null_arrays_legacy(void **state)` |
| `test_static_position_right_inset_keeps_anchor` | function | `tests/test_box_tree.c:706` | `static void test_static_position_right_inset_keeps_anchor(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_browser.c:8` | `#define _POSIX_C_SOURCE` |
| `main` | function | `tests/test_browser.c:378` | `int main(void)` |
| `test_accepts_https_and_file` | function | `tests/test_browser.c:108` | `static void test_accepts_https_and_file(void **state)` |
| `test_back_forward_bounds` | function | `tests/test_browser.c:79` | `static void test_back_forward_bounds(void **state)` |
| `test_exceptions` | function | `tests/test_browser.c:252` | `static void test_exceptions(void **state)` |
| `test_init` | function | `tests/test_browser.c:20` | `static void test_init(void **state)` |
| `test_navigate_from_middle_discards_future` | function | `tests/test_browser.c:61` | `static void test_navigate_from_middle_discards_future(void **state)` |
| `test_navigate_history` | function | `tests/test_browser.c:31` | `static void test_navigate_history(void **state)` |
| `test_push_state_rejects_and_guards` | function | `tests/test_browser.c:361` | `static void test_push_state_rejects_and_guards(void **state)` |
| `test_push_state_same_document` | function | `tests/test_browser.c:328` | `static void test_push_state_same_document(void **state)` |
| `test_rejects_invalid_url` | function | `tests/test_browser.c:95` | `static void test_rejects_invalid_url(void **state)` |
| `test_set_page` | function | `tests/test_browser.c:196` | `static void test_set_page(void **state)` |
| `test_set_page_sanitizes_invalid_utf8` | function | `tests/test_browser.c:218` | `static void test_set_page_sanitizes_invalid_utf8(void **state)` |
| `test_status_toast` | function | `tests/test_browser.c:277` | `static void test_status_toast(void **state)` |
| `test_status_truncates` | function | `tests/test_browser.c:309` | `static void test_status_truncates(void **state)` |
| `test_url_bar_editing` | function | `tests/test_browser.c:122` | `static void test_url_bar_editing(void **state)` |
| `test_url_bar_selection` | function | `tests/test_browser.c:152` | `static void test_url_bar_selection(void **state)` |
| `main` | function | `tests/test_compositor.c:231` | `int main(void)` |
| `mk` | function | `tests/test_compositor.c:133` | `static cx_item mk(cx_layer layer, int z, int z_auto, size_t doc, size_t ref)` |
| `test_compare_layer_then_z_then_doc` | function | `tests/test_compositor.c:139` | `static void test_compare_layer_then_z_then_doc(void **state)` |
| `test_layer_float` | function | `tests/test_compositor.c:116` | `static void test_layer_float(void **state)` |
| `test_layer_inline_and_block` | function | `tests/test_compositor.c:123` | `static void test_layer_inline_and_block(void **state)` |
| `test_layer_negative_z` | function | `tests/test_compositor.c:86` | `static void test_layer_negative_z(void **state)` |
| `test_layer_positive_z` | function | `tests/test_compositor.c:93` | `static void test_layer_positive_z(void **state)` |
| `test_layer_zero_z_context` | function | `tests/test_compositor.c:100` | `static void test_layer_zero_z_context(void **state)` |
| `test_layer_zero_z_positioned_auto` | function | `tests/test_compositor.c:109` | `static void test_layer_zero_z_positioned_auto(void **state)` |
| `test_sc_fixed_sticky_always` | function | `tests/test_compositor.c:70` | `static void test_sc_fixed_sticky_always(void **state)` |
| `test_sc_isolation` | function | `tests/test_compositor.c:43` | `static void test_sc_isolation(void **state)` |
| `test_sc_mix_blend` | function | `tests/test_compositor.c:35` | `static void test_sc_mix_blend(void **state)` |
| `test_sc_opacity` | function | `tests/test_compositor.c:26` | `static void test_sc_opacity(void **state)` |
| `test_sc_positioned_z` | function | `tests/test_compositor.c:58` | `static void test_sc_positioned_z(void **state)` |
| `test_sc_static_none` | function | `tests/test_compositor.c:77` | `static void test_sc_static_none(void **state)` |
| `test_sc_transform` | function | `tests/test_compositor.c:51` | `static void test_sc_transform(void **state)` |
| `test_sort_full_paint_order` | function | `tests/test_compositor.c:160` | `static void test_sort_full_paint_order(void **state)` |
| `test_sort_matches_zindex_only_ordering` | function | `tests/test_compositor.c:218` | `static void test_sort_matches_zindex_only_ordering(void **state)` |
| `test_sort_noop_guards` | function | `tests/test_compositor.c:207` | `static void test_sort_noop_guards(void **state)` |
| `test_sort_stability` | function | `tests/test_compositor.c:193` | `static void test_sort_stability(void **state)` |
| `test_sort_z_within_layer` | function | `tests/test_compositor.c:177` | `static void test_sort_z_within_layer(void **state)` |
| `assert_int_equal` | function | `tests/test_css.c:1036` | `assert_int_equal(css_parse(         "@supports (display:grid)` |
| `assert_int_equal` | function | `tests/test_css.c:1050` | `assert_int_equal(css_parse(         "@supports (display:flex)` |
| `assert_int_equal` | function | `tests/test_css.c:1114` | `assert_int_equal(css_parse("@container (width>=10px)` |
| `assert_int_equal` | function | `tests/test_css.c:1697` | `assert_int_equal(css_parse("tr:nth-child(even)` |
| `assert_int_equal` | function | `tests/test_css.c:1720` | `assert_int_equal(css_parse("li:nth-last-child(2)` |
| `assert_int_equal` | function | `tests/test_css.c:1816` | `assert_int_equal(css_parse(".s:not(:focus)` |
| `assert_int_equal` | function | `tests/test_css.c:1844` | `assert_int_equal(css_parse("p:not(.x > y)` |
| `assert_int_equal` | function | `tests/test_css.c:2204` | `assert_int_equal(css_parse("li:nth-child()` |
| `assert_int_equal` | function | `tests/test_css.c:2239` | `assert_int_equal(css_parse("li:nth-of-type(2n)` |
| `assert_int_equal` | function | `tests/test_css.c:2271` | `assert_int_equal(css_parse("div:has(.x)` |
| `assert_int_equal` | function | `tests/test_css.c:2292` | `assert_int_equal(css_parse("html:lang(en)` |
| `assert_int_equal` | function | `tests/test_css.c:2648` | `assert_int_equal(css_parse(         "@media (min-width: 600px)` |
| `assert_int_equal` | function | `tests/test_css.c:2663` | `assert_int_equal(css_parse(         "@media screen and (min-width: 600px)` |
| `assert_int_equal` | function | `tests/test_css.c:2679` | `assert_int_equal(css_parse(         "@media (frobnicate: 1)` |
| `assert_int_equal` | function | `tests/test_css.c:5091` | `assert_int_equal(css_parse("@media (min-width: 200em)` |
| `assert_int_equal` | function | `tests/test_css.c:5097` | `assert_int_equal(css_parse("@media (min-width: 40em)` |
| `box` | function | `tests/test_css.c:230` | `* box (CSS 2.1 section 10.8.1). With one line box per line and no separate * parent content edge, they land on the...` |
| `cls_el` | function | `tests/test_css.c:1212` | `static css_element cls_el(const char *tag, const char *const *cl, size_t n,                      ...` |
| `color_for_class` | function | `tests/test_css.c:1135` | `static int color_for_class(const char *css, const char *cls)` |
| `downstream` | function | `tests/test_css.c:653` | `* and deciding whether to fetch happens downstream (render_doc.c) */ assert_string_equal(css_parse_inline(...` |
| `dropped` | function | `tests/test_css.c:508` | `* dropped (which kept a lower rule's, or the UA button face's, colour). */ static void test_backg...` |
| `el_attr_node` | function | `tests/test_css.c:1480` | `static css_element el_attr_node(const char *tag, const char *id,                                 ...` |
| `el_node` | function | `tests/test_css.c:1445` | `static css_element el_node(const char *tag, const char *id,                            const char...` |
| `el_sib_node` | function | `tests/test_css.c:1460` | `static css_element el_sib_node(const char *tag, int nth, int nsib,                               ...` |
| `el_type_node` | function | `tests/test_css.c:1469` | `static css_element el_type_node(const char *tag, int nth, int nsib,                              ...` |
| `geometry` | function | `tests/test_css.c:2931` | `* hostile sheet never sees real window geometry (anti-fingerprinting) yet 100vh  * heroes and cal...` |
| `grammar` | function | `tests/test_css.c:5132` | `* grammar (spec/css.md), so they parse instead of dropping. */ static void test_vendor_prefixes(v...` |
| `invalid` | function | `tests/test_css.c:755` | `* invalid (fail closed), not silently coerced into some default. */ css_style s = css_parse_inline("color...` |
| `main` | function | `tests/test_css.c:5168` | `int main(void)` |
| `root_is_dark_html` | function | `tests/test_css.c:959` | `static int root_is_dark_html(void *ctx, const css_sel *sel)` |
| `silent` | function | `tests/test_css.c:2545` | `* silent (anti-DoS truncation, not a parse failure). 500 filler rules is well past  * the OLD cap...` |
| `terminator` | function | `tests/test_css.c:1946` | `* terminator (consumed, not painted);` |
| `test_adjacent_sibling_combinator` | function | `tests/test_css.c:1571` | `static void test_adjacent_sibling_combinator(void **state)` |
| `test_anim_keyframes_resolved_from_sheet` | function | `tests/test_css.c:4841` | `static void test_anim_keyframes_resolved_from_sheet(void **state)` |
| `test_anim_transform_keyframes_from_sheet` | function | `tests/test_css.c:4874` | `static void test_anim_transform_keyframes_from_sheet(void **state)` |
| `test_animation_none_resets` | function | `tests/test_css.c:3366` | `static void test_animation_none_resets(void **state)` |
| `test_animation_shorthand_basic` | function | `tests/test_css.c:3341` | `static void test_animation_shorthand_basic(void **state)` |
| `test_animation_shorthand_ignores_bezier` | function | `tests/test_css.c:3359` | `static void test_animation_shorthand_ignores_bezier(void **state)` |
| `test_animation_shorthand_order_free` | function | `tests/test_css.c:3350` | `static void test_animation_shorthand_order_free(void **state)` |
| `test_at_rules_skipped` | function | `tests/test_css.c:2593` | `static void test_at_rules_skipped(void **state)` |
| `test_attr_case_insensitive_flag` | function | `tests/test_css.c:2380` | `static void test_attr_case_insensitive_flag(void **state)` |
| `test_attr_equals` | function | `tests/test_css.c:2330` | `static void test_attr_equals(void **state)` |
| `test_attr_in_combinator` | function | `tests/test_css.c:2437` | `static void test_attr_in_combinator(void **state)` |
| `test_attr_malformed_fail_closed` | function | `tests/test_css.c:2453` | `static void test_attr_malformed_fail_closed(void **state)` |
| `test_attr_name_case_insensitive` | function | `tests/test_css.c:2395` | `static void test_attr_name_case_insensitive(void **state)` |
| `test_attr_operators` | function | `tests/test_css.c:2348` | `static void test_attr_operators(void **state)` |
| `test_attr_presence` | function | `tests/test_css.c:2317` | `static void test_attr_presence(void **state)` |
| `test_attr_quoted_value_with_space` | function | `tests/test_css.c:2406` | `static void test_attr_quoted_value_with_space(void **state)` |
| `test_attr_specificity_and_compound` | function | `tests/test_css.c:2420` | `static void test_attr_specificity_and_compound(void **state)` |
| `test_backdrop_filter_blur` | function | `tests/test_css.c:4801` | `static void test_backdrop_filter_blur(void **state)` |
| `test_background_clip_text` | function | `tests/test_css.c:4676` | `static void test_background_clip_text(void **state)` |
| `test_background_rgba_alpha` | function | `tests/test_css.c:4647` | `static void test_background_rgba_alpha(void **state)` |
| `test_background_shorthand_resets_gradient` | function | `tests/test_css.c:611` | `static void test_background_shorthand_resets_gradient(void **state)` |
| `test_bare_ms_box_sizing_drops` | function | `tests/test_css.c:3560` | `static void test_bare_ms_box_sizing_drops(void **state)` |
| `test_bg_image_url_absolute` | function | `tests/test_css.c:650` | `static void test_bg_image_url_absolute(void **state)` |
| `test_bg_image_url_basic` | function | `tests/test_css.c:632` | `static void test_bg_image_url_basic(void **state)` |
| `test_bg_image_url_gradient_mutually_exclusive` | function | `tests/test_css.c:686` | `static void test_bg_image_url_gradient_mutually_exclusive(void **state)` |
| `test_bg_image_url_none_and_junk_reset` | function | `tests/test_css.c:659` | `static void test_bg_image_url_none_and_junk_reset(void **state)` |
| `test_bg_image_url_overlong_fails_closed` | function | `tests/test_css.c:673` | `static void test_bg_image_url_overlong_fails_closed(void **state)` |
| `test_bg_image_url_quoted` | function | `tests/test_css.c:639` | `static void test_bg_image_url_quoted(void **state)` |
| `test_bg_position_center_by_identity` | function | `tests/test_css.c:3427` | `static void test_bg_position_center_by_identity(void **state)` |
| `test_bg_position_collision_drops` | function | `tests/test_css.c:3448` | `static void test_bg_position_collision_drops(void **state)` |
| `test_bg_position_edge_offset` | function | `tests/test_css.c:3415` | `static void test_bg_position_edge_offset(void **state)` |
| `test_bg_position_four_value` | function | `tests/test_css.c:3438` | `static void test_bg_position_four_value(void **state)` |
| `test_bg_shorthand_captures_url_and_resets_color` | function | `tests/test_css.c:694` | `static void test_bg_shorthand_captures_url_and_resets_color(void **state)` |
| `test_bg_size_and_repeat` | function | `tests/test_css.c:713` | `static void test_bg_size_and_repeat(void **state)` |
| `test_border_longhands` | function | `tests/test_css.c:3642` | `static void test_border_longhands(void **state)` |
| `test_border_shorthand` | function | `tests/test_css.c:3612` | `static void test_border_shorthand(void **state)` |
| `test_box_auto_and_centering` | function | `tests/test_css.c:2764` | `static void test_box_auto_and_centering(void **state)` |
| `test_box_clamp_anti_dos` | function | `tests/test_css.c:3021` | `static void test_box_clamp_anti_dos(void **state)` |
| `test_box_extension_sheet_cascade` | function | `tests/test_css.c:3071` | `static void test_box_extension_sheet_cascade(void **state)` |
| `test_box_orient_maps_to_flex_direction` | function | `tests/test_css.c:3768` | `static void test_box_orient_maps_to_flex_direction(void **state)` |
| `test_box_shadow_and_outline` | function | `tests/test_css.c:3668` | `static void test_box_shadow_and_outline(void **state)` |
| `test_box_sheet_cascade_inline_wins` | function | `tests/test_css.c:3198` | `static void test_box_sheet_cascade_inline_wins(void **state)` |
| `test_box_shorthand_expansion` | function | `tests/test_css.c:2736` | `static void test_box_shorthand_expansion(void **state)` |
| `test_box_sizing` | function | `tests/test_css.c:3604` | `static void test_box_sizing(void **state)` |
| `test_box_units_and_failclosed` | function | `tests/test_css.c:2781` | `static void test_box_units_and_failclosed(void **state)` |
| `test_calc_basic_arithmetic` | function | `tests/test_css.c:2877` | `static void test_calc_basic_arithmetic(void **state)` |
| `test_calc_clamped_anti_dos` | function | `tests/test_css.c:2923` | `static void test_calc_clamped_anti_dos(void **state)` |
| `test_calc_dimension_errors_fail_closed` | function | `tests/test_css.c:2901` | `static void test_calc_dimension_errors_fail_closed(void **state)` |
| `test_calc_inside_shorthands` | function | `tests/test_css.c:2976` | `static void test_calc_inside_shorthands(void **state)` |
| `test_calc_precedence_and_parens` | function | `tests/test_css.c:2886` | `static void test_calc_precedence_and_parens(void **state)` |
| `test_calc_shape_mismatch_drops` | function | `tests/test_css.c:3552` | `static void test_calc_shape_mismatch_drops(void **state)` |
| `test_calc_units_and_signs` | function | `tests/test_css.c:2893` | `static void test_calc_units_and_signs(void **state)` |
| `test_calc_with_custom_property` | function | `tests/test_css.c:3014` | `static void test_calc_with_custom_property(void **state)` |
| `test_cascade_document_order` | function | `tests/test_css.c:2575` | `static void test_cascade_document_order(void **state)` |
| `test_cascade_inline_wins` | function | `tests/test_css.c:2584` | `static void test_cascade_inline_wins(void **state)` |
| `test_cascade_specificity` | function | `tests/test_css.c:2529` | `static void test_cascade_specificity(void **state)` |
| `test_child_combinator` | function | `tests/test_css.c:1524` | `static void test_child_combinator(void **state)` |
| `test_clip_auto` | function | `tests/test_css.c:5115` | `static void test_clip_auto(void **state)` |
| `test_clip_rect` | function | `tests/test_css.c:5105` | `static void test_clip_rect(void **state)` |
| `test_combinator_class_chain` | function | `tests/test_css.c:1552` | `static void test_combinator_class_chain(void **state)` |
| `test_combinator_specificity_sum` | function | `tests/test_css.c:1537` | `static void test_combinator_specificity_sum(void **state)` |
| `test_component_var_cascade_order` | function | `tests/test_css.c:1333` | `static void test_component_var_cascade_order(void **state)` |
| `test_component_var_inherited_by_child` | function | `tests/test_css.c:1313` | `static void test_component_var_inherited_by_child(void **state)` |
| `test_component_var_inline_overrides` | function | `tests/test_css.c:1350` | `static void test_component_var_inline_overrides(void **state)` |
| `test_component_var_same_element` | function | `tests/test_css.c:1300` | `static void test_component_var_same_element(void **state)` |
| `test_conic_gradient_basic` | function | `tests/test_css.c:4696` | `static void test_conic_gradient_basic(void **state)` |
| `test_conic_gradient_deg_positions` | function | `tests/test_css.c:4737` | `static void test_conic_gradient_deg_positions(void **state)` |
| `test_conic_gradient_fails_closed` | function | `tests/test_css.c:4747` | `static void test_conic_gradient_fails_closed(void **state)` |
| `test_conic_gradient_from_angle` | function | `tests/test_css.c:4708` | `static void test_conic_gradient_from_angle(void **state)` |
| `test_conic_gradient_pie_hard_stop` | function | `tests/test_css.c:4722` | `static void test_conic_gradient_pie_hard_stop(void **state)` |
| `test_container_block_still_skipped` | function | `tests/test_css.c:1111` | `static void test_container_block_still_skipped(void **state)` |
| `test_container_cascade_inline_wins` | function | `tests/test_css.c:377` | `static void test_container_cascade_inline_wins(void **state)` |
| `test_container_fail_closed_and_bounds` | function | `tests/test_css.c:392` | `static void test_container_fail_closed_and_bounds(void **state)` |
| `test_container_unset` | function | `tests/test_css.c:485` | `static void test_container_unset(void **state)` |
| `test_cursor` | function | `tests/test_css.c:3308` | `static void test_cursor(void **state)` |
| `test_custom_prop_attr_scoped_skipped_without_matcher` | function | `tests/test_css.c:983` | `static void test_custom_prop_attr_scoped_skipped_without_matcher(void **state)` |
| `test_custom_prop_attr_scoped_via_root_matcher` | function | `tests/test_css.c:971` | `static void test_custom_prop_attr_scoped_via_root_matcher(void **state)` |
| `test_custom_prop_chain_eight_deep` | function | `tests/test_css.c:936` | `static void test_custom_prop_chain_eight_deep(void **state)` |
| `test_custom_prop_class_scoped_applies_with_root_scope` | function | `tests/test_css.c:841` | `static void test_custom_prop_class_scoped_applies_with_root_scope(void **state)` |
| `test_custom_prop_class_scoped_skipped_without_scope` | function | `tests/test_css.c:829` | `static void test_custom_prop_class_scoped_skipped_without_scope(void **state)` |
| `test_custom_prop_dark_media_collected_in_dark` | function | `tests/test_css.c:816` | `static void test_custom_prop_dark_media_collected_in_dark(void **state)` |
| `test_custom_prop_dark_media_not_collected_in_light` | function | `tests/test_css.c:801` | `static void test_custom_prop_dark_media_not_collected_in_light(void **state)` |
| `test_custom_prop_descendant_scoped_skipped` | function | `tests/test_css.c:854` | `static void test_custom_prop_descendant_scoped_skipped(void **state)` |
| `test_custom_prop_fanout_bounded` | function | `tests/test_css.c:944` | `static void test_custom_prop_fanout_bounded(void **state)` |
| `test_custom_prop_long_name_survives` | function | `tests/test_css.c:905` | `static void test_custom_prop_long_name_survives(void **state)` |
| `test_custom_prop_long_value_survives` | function | `tests/test_css.c:890` | `static void test_custom_prop_long_value_survives(void **state)` |
| `test_custom_prop_root_matcher_rejects_descendant` | function | `tests/test_css.c:994` | `static void test_custom_prop_root_matcher_rejects_descendant(void **state)` |
| `test_custom_prop_table_holds_hundreds` | function | `tests/test_css.c:866` | `static void test_custom_prop_table_holds_hundreds(void **state)` |
| `test_custom_prop_table_holds_thousands` | function | `tests/test_css.c:917` | `static void test_custom_prop_table_holds_thousands(void **state)` |
| `test_custom_prop_var_basic` | function | `tests/test_css.c:735` | `static void test_custom_prop_var_basic(void **state)` |
| `test_custom_prop_var_chain` | function | `tests/test_css.c:761` | `static void test_custom_prop_var_chain(void **state)` |
| `test_custom_prop_var_fallback_used_when_missing` | function | `tests/test_css.c:746` | `static void test_custom_prop_var_fallback_used_when_missing(void **state)` |
| `test_custom_prop_var_in_shorthand` | function | `tests/test_css.c:778` | `static void test_custom_prop_var_in_shorthand(void **state)` |
| `test_custom_prop_var_later_declaration_wins` | function | `tests/test_css.c:788` | `static void test_custom_prop_var_later_declaration_wins(void **state)` |
| `test_custom_prop_var_never_phones_home` | function | `tests/test_css.c:1387` | `static void test_custom_prop_var_never_phones_home(void **state)` |
| `test_custom_prop_var_no_fallback_drops_decl` | function | `tests/test_css.c:752` | `static void test_custom_prop_var_no_fallback_drops_decl(void **state)` |
| `test_custom_prop_var_self_reference_fails_closed` | function | `tests/test_css.c:769` | `static void test_custom_prop_var_self_reference_fails_closed(void **state)` |
| `test_custom_prop_var_unbalanced_paren_drops` | function | `tests/test_css.c:1374` | `static void test_custom_prop_var_unbalanced_paren_drops(void **state)` |
| `test_decl_split_ignores_semicolon_in_url_and_string` | function | `tests/test_css.c:1190` | `static void test_decl_split_ignores_semicolon_in_url_and_string(void **state)` |
| `test_descendant_combinator` | function | `tests/test_css.c:1508` | `static void test_descendant_combinator(void **state)` |
| `test_drops_retry_rewinds_buckets` | function | `tests/test_css.c:2037` | `static void test_drops_retry_rewinds_buckets(void **state)` |
| `test_filter_blur_and_grayscale` | function | `tests/test_css.c:4813` | `static void test_filter_blur_and_grayscale(void **state)` |
| `test_filter_drop_shadow` | function | `tests/test_css.c:4774` | `static void test_filter_drop_shadow(void **state)` |
| `test_filter_drop_shadow_defaults_and_failclosed` | function | `tests/test_css.c:4787` | `static void test_filter_drop_shadow_defaults_and_failclosed(void **state)` |
| `test_flex_align` | function | `tests/test_css.c:3737` | `static void test_flex_align(void **state)` |
| `test_flex_item` | function | `tests/test_css.c:3693` | `static void test_flex_item(void **state)` |
| `test_float_and_clear` | function | `tests/test_css.c:3244` | `static void test_float_and_clear(void **state)` |
| `test_font_family` | function | `tests/test_css.c:139` | `static void test_font_family(void **state)` |
| `test_font_shorthand` | function | `tests/test_css.c:4617` | `static void test_font_shorthand(void **state)` |
| `test_font_without_family_drops` | function | `tests/test_css.c:3566` | `static void test_font_without_family_drops(void **state)` |
| `test_fontface_case_insensitive` | function | `tests/test_css.c:3494` | `static void test_fontface_case_insensitive(void **state)` |
| `test_fontface_icon_only_family` | function | `tests/test_css.c:3505` | `static void test_fontface_icon_only_family(void **state)` |
| `test_fontface_inline_has_no_sheet` | function | `tests/test_css.c:3517` | `static void test_fontface_inline_has_no_sheet(void **state)` |
| `test_fontface_later_rule_clears` | function | `tests/test_css.c:3525` | `static void test_fontface_later_rule_clears(void **state)` |
| `test_fontface_matches_sheet_face` | function | `tests/test_css.c:3471` | `static void test_fontface_matches_sheet_face(void **state)` |
| `test_fontface_no_match_is_zero` | function | `tests/test_css.c:3483` | `static void test_fontface_no_match_is_zero(void **state)` |
| `test_gap_two_value` | function | `tests/test_css.c:4600` | `static void test_gap_two_value(void **state)` |
| `test_general_sibling_combinator` | function | `tests/test_css.c:1586` | `static void test_general_sibling_combinator(void **state)` |
| `test_gradient_stop_alpha` | function | `tests/test_css.c:1248` | `static void test_gradient_stop_alpha(void **state)` |
| `test_grid_autofill_marker` | function | `tests/test_css.c:3458` | `static void test_grid_autofill_marker(void **state)` |
| `test_grid_extras` | function | `tests/test_css.c:3791` | `static void test_grid_extras(void **state)` |
| `test_grid_minmax_counts_as_one_track` | function | `tests/test_css.c:463` | `static void test_grid_minmax_counts_as_one_track(void **state)` |
| `test_grid_repeat_clamped_anti_dos` | function | `tests/test_css.c:478` | `static void test_grid_repeat_clamped_anti_dos(void **state)` |
| `test_grid_repeat_expands_count` | function | `tests/test_css.c:452` | `static void test_grid_repeat_expands_count(void **state)` |
| `test_grid_repeat_malformed_fails_closed` | function | `tests/test_css.c:471` | `static void test_grid_repeat_malformed_fails_closed(void **state)` |
| `test_has_parses_and_fails_closed` | function | `tests/test_css.c:2265` | `static void test_has_parses_and_fails_closed(void **state)` |
| `test_important_beats_specificity` | function | `tests/test_css.c:2481` | `static void test_important_beats_specificity(void **state)` |
| `test_important_in_shorthand` | function | `tests/test_css.c:2512` | `static void test_important_in_shorthand(void **state)` |
| `test_important_inline_beats_sheet_important` | function | `tests/test_css.c:2500` | `static void test_important_inline_beats_sheet_important(void **state)` |
| `test_important_inline_not_dropped` | function | `tests/test_css.c:2471` | `static void test_important_inline_not_dropped(void **state)` |
| `test_important_tier_then_normal_order` | function | `tests/test_css.c:2490` | `static void test_important_tier_then_normal_order(void **state)` |
| `test_inline_accent_color` | function | `tests/test_css.c:4092` | `static void test_inline_accent_color(void **state)` |
| `test_inline_appearance` | function | `tests/test_css.c:3963` | `static void test_inline_appearance(void **state)` |
| `test_inline_aspect_ratio` | function | `tests/test_css.c:3137` | `static void test_inline_aspect_ratio(void **state)` |
| `test_inline_backface_visibility` | function | `tests/test_css.c:4484` | `static void test_inline_backface_visibility(void **state)` |
| `test_inline_bg_clip_origin_attachment` | function | `tests/test_css.c:4021` | `static void test_inline_bg_clip_origin_attachment(void **state)` |
| `test_inline_bg_repeat` | function | `tests/test_css.c:4000` | `static void test_inline_bg_repeat(void **state)` |
| `test_inline_bg_size` | function | `tests/test_css.c:4012` | `static void test_inline_bg_size(void **state)` |
| `test_inline_border_collapse` | function | `tests/test_css.c:3876` | `static void test_inline_border_collapse(void **state)` |
| `test_inline_border_spacing` | function | `tests/test_css.c:3885` | `static void test_inline_border_spacing(void **state)` |
| `test_inline_box_longhands` | function | `tests/test_css.c:2718` | `static void test_inline_box_longhands(void **state)` |
| `test_inline_caption_side` | function | `tests/test_css.c:3905` | `static void test_inline_caption_side(void **state)` |
| `test_inline_caret_color` | function | `tests/test_css.c:3953` | `static void test_inline_caret_color(void **state)` |
| `test_inline_color_scheme` | function | `tests/test_css.c:4082` | `static void test_inline_color_scheme(void **state)` |
| `test_inline_contain` | function | `tests/test_css.c:4049` | `static void test_inline_contain(void **state)` |
| `test_inline_container_props` | function | `tests/test_css.c:329` | `static void test_inline_container_props(void **state)` |
| `test_inline_content_visibility` | function | `tests/test_css.c:4064` | `static void test_inline_content_visibility(void **state)` |
| `test_inline_direction` | function | `tests/test_css.c:3167` | `static void test_inline_direction(void **state)` |
| `test_inline_display` | function | `tests/test_css.c:291` | `static void test_inline_display(void **state)` |
| `test_inline_display_table_family` | function | `tests/test_css.c:304` | `static void test_inline_display_table_family(void **state)` |
| `test_inline_empty_cells` | function | `tests/test_css.c:3896` | `static void test_inline_empty_cells(void **state)` |
| `test_inline_font_kerning` | function | `tests/test_css.c:4411` | `static void test_inline_font_kerning(void **state)` |
| `test_inline_font_size` | function | `tests/test_css.c:43` | `static void test_inline_font_size(void **state)` |
| `test_inline_font_size_absolute_flag` | function | `tests/test_css.c:58` | `static void test_inline_font_size_absolute_flag(void **state)` |
| `test_inline_font_stretch` | function | `tests/test_css.c:4430` | `static void test_inline_font_stretch(void **state)` |
| `test_inline_font_variant` | function | `tests/test_css.c:3923` | `static void test_inline_font_variant(void **state)` |
| `test_inline_font_weight_style` | function | `tests/test_css.c:100` | `static void test_inline_font_weight_style(void **state)` |
| `test_inline_hyphens` | function | `tests/test_css.c:3932` | `static void test_inline_hyphens(void **state)` |
| `test_inline_image_rendering` | function | `tests/test_css.c:4073` | `static void test_inline_image_rendering(void **state)` |
| `test_inline_isolation` | function | `tests/test_css.c:4041` | `static void test_inline_isolation(void **state)` |
| `test_inline_line_height` | function | `tests/test_css.c:85` | `static void test_inline_line_height(void **state)` |
| `test_inline_list_style_pos` | function | `tests/test_css.c:4403` | `static void test_inline_list_style_pos(void **state)` |
| `test_inline_min_max_height` | function | `tests/test_css.c:3057` | `static void test_inline_min_max_height(void **state)` |
| `test_inline_min_width_height` | function | `tests/test_css.c:3030` | `static void test_inline_min_width_height(void **state)` |
| `test_inline_mix_blend_mode` | function | `tests/test_css.c:4115` | `static void test_inline_mix_blend_mode(void **state)` |
| `test_inline_object_fit` | function | `tests/test_css.c:4392` | `static void test_inline_object_fit(void **state)` |
| `test_inline_outline_longhands` | function | `tests/test_css.c:3845` | `static void test_inline_outline_longhands(void **state)` |
| `test_inline_outline_offset` | function | `tests/test_css.c:3176` | `static void test_inline_outline_offset(void **state)` |

Next: [SYMBOLS_p10.md](SYMBOLS_p10.md)
