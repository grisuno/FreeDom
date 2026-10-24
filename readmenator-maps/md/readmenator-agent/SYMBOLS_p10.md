# Symbols (page 10 of 15)
Previous: [SYMBOLS_p9.md](SYMBOLS_p9.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `card` | function | `tests/test_box_tree.c:769` | `* containing block climbs the unplaced card(1) → placed ancestor(0, x=100). */ assert_true(dbl_eq(out[2].x, 100));` |
| `dbox` | function | `tests/test_box_tree.c:1071` | `static pv_box_def dbox(int parent, int position, int z)` |
| `main` | function | `tests/test_box_tree.c:1178` | `int main(void)` |
| `test_abspos_resolves_against_placed_ancestor` | function | `tests/test_box_tree.c:744` | `static void test_abspos_resolves_against_placed_ancestor(void **state)` |
| `test_abspos_unplaced_without_anchor_falls_to_viewport` | function | `tests/test_box_tree.c:774` | `static void test_abspos_unplaced_without_anchor_falls_to_viewport(void **state)` |
| `test_block_stacking_with_collapse` | function | `tests/test_box_tree.c:62` | `static void test_block_stacking_with_collapse(void **state)` |
| `test_box_hidden_ancestor` | function | `tests/test_box_tree.c:806` | `static void test_box_hidden_ancestor(void **state)` |
| `test_box_hidden_fail_closed` | function | `tests/test_box_tree.c:819` | `static void test_box_hidden_fail_closed(void **state)` |
| `test_box_hidden_self` | function | `tests/test_box_tree.c:794` | `static void test_box_hidden_self(void **state)` |
| `test_children_cap` | function | `tests/test_box_tree.c:388` | `static void test_children_cap(void **state)` |
| `test_defer_fails_open` | function | `tests/test_box_tree.c:1164` | `static void test_defer_fails_open(void **state)` |
| `test_defer_outermost_root_and_negative_z` | function | `tests/test_box_tree.c:1124` | `static void test_defer_outermost_root_and_negative_z(void **state)` |
| `test_defer_relative_after_abs` | function | `tests/test_box_tree.c:1080` | `static void test_defer_relative_after_abs(void **state)` |
| `test_defer_relative_before_abs_is_not_deferred` | function | `tests/test_box_tree.c:1097` | `static void test_defer_relative_before_abs_is_not_deferred(void **state)` |
| `test_defer_respects_z_order` | function | `tests/test_box_tree.c:1109` | `static void test_defer_respects_z_order(void **state)` |
| `test_defer_uses_tree_order_not_index` | function | `tests/test_box_tree.c:1148` | `static void test_defer_uses_tree_order_not_index(void **state)` |
| `test_depth_cap` | function | `tests/test_box_tree.c:398` | `static void test_depth_cap(void **state)` |
| `test_display_none_skipped` | function | `tests/test_box_tree.c:353` | `static void test_display_none_skipped(void **state)` |
| `test_flex_auto_margin_pushes_item` | function | `tests/test_box_tree.c:95` | `static void test_flex_auto_margin_pushes_item(void **state)` |
| `test_flex_cross_axis_align` | function | `tests/test_box_tree.c:213` | `static void test_flex_cross_axis_align(void **state)` |
| `test_flex_gap_and_justify_center` | function | `tests/test_box_tree.c:113` | `static void test_flex_gap_and_justify_center(void **state)` |
| `test_flex_negative_gap` | function | `tests/test_box_tree.c:378` | `static void test_flex_negative_gap(void **state)` |
| `test_flex_nowrap_default_single_line_unchanged` | function | `tests/test_box_tree.c:151` | `static void test_flex_nowrap_default_single_line_unchanged(void **state)` |
| `test_flex_row_grow` | function | `tests/test_box_tree.c:75` | `static void test_flex_row_grow(void **state)` |
| `test_flex_single_line_definite_height` | function | `tests/test_box_tree.c:1018` | `static void test_flex_single_line_definite_height(void **state)` |
| `test_flex_wrap_reverse_two_lines` | function | `tests/test_box_tree.c:171` | `static void test_flex_wrap_reverse_two_lines(void **state)` |
| `test_flex_wrap_row_gap_distinct_from_gap` | function | `tests/test_box_tree.c:193` | `static void test_flex_wrap_row_gap_distinct_from_gap(void **state)` |
| `test_flex_wrap_two_lines` | function | `tests/test_box_tree.c:129` | `static void test_flex_wrap_two_lines(void **state)` |
| `test_grid` | function | `tests/test_box_tree.c:270` | `static void test_grid(void **state)` |
| `test_grid_bad_columns` | function | `tests/test_box_tree.c:368` | `static void test_grid_bad_columns(void **state)` |
| `test_grid_column_span` | function | `tests/test_box_tree.c:309` | `static void test_grid_column_span(void **state)` |
| `test_grid_justify_self` | function | `tests/test_box_tree.c:1045` | `static void test_grid_justify_self(void **state)` |
| `test_grid_row_gap_distinct_from_gap` | function | `tests/test_box_tree.c:231` | `static void test_grid_row_gap_distinct_from_gap(void **state)` |
| `test_grid_row_tracks_definite_height` | function | `tests/test_box_tree.c:955` | `static void test_grid_row_tracks_definite_height(void **state)` |
| `test_grid_spanning_item_fits_tracked_rows` | function | `tests/test_box_tree.c:994` | `static void test_grid_spanning_item_fits_tracked_rows(void **state)` |
| `test_grid_weighted_tracks` | function | `tests/test_box_tree.c:291` | `static void test_grid_weighted_tracks(void **state)` |
| `test_grid_without_row_gap_falls_back_to_gap` | function | `tests/test_box_tree.c:254` | `static void test_grid_without_row_gap_falls_back_to_gap(void **state)` |
| `test_leaf` | function | `tests/test_box_tree.c:40` | `static void test_leaf(void **state)` |
| `test_leaf_with_padding` | function | `tests/test_box_tree.c:47` | `static void test_leaf_with_padding(void **state)` |
| `test_nested_flex_in_block` | function | `tests/test_box_tree.c:329` | `static void test_nested_flex_in_block(void **state)` |
| `test_null_root` | function | `tests/test_box_tree.c:35` | `static void test_null_root(void **state)` |
| `test_oof_anchor_none_on_static_chain` | function | `tests/test_box_tree.c:853` | `static void test_oof_anchor_none_on_static_chain(void **state)` |
| `test_oof_anchor_self` | function | `tests/test_box_tree.c:863` | `static void test_oof_anchor_self(void **state)` |
| `test_oof_anchor_via_ancestor` | function | `tests/test_box_tree.c:870` | `static void test_oof_anchor_via_ancestor(void **state)` |
| `test_oof_avail_stretch_and_shrink` | function | `tests/test_box_tree.c:934` | `static void test_oof_avail_stretch_and_shrink(void **state)` |
| `test_oof_fail_open` | function | `tests/test_box_tree.c:912` | `static void test_oof_fail_open(void **state)` |
| `test_oof_nested_absolute_anchor_vs_root` | function | `tests/test_box_tree.c:883` | `static void test_oof_nested_absolute_anchor_vs_root(void **state)` |
| `test_oof_relative_does_not_anchor` | function | `tests/test_box_tree.c:898` | `static void test_oof_relative_does_not_anchor(void **state)` |
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
| `assert_int_equal` | function | `tests/test_css.c:1046` | `assert_int_equal(css_parse(         "@supports (display:grid)` |
| `assert_int_equal` | function | `tests/test_css.c:1060` | `assert_int_equal(css_parse(         "@supports (display:flex)` |
| `assert_int_equal` | function | `tests/test_css.c:1124` | `assert_int_equal(css_parse("@container (width>=10px)` |
| `assert_int_equal` | function | `tests/test_css.c:1707` | `assert_int_equal(css_parse("tr:nth-child(even)` |
| `assert_int_equal` | function | `tests/test_css.c:1730` | `assert_int_equal(css_parse("li:nth-last-child(2)` |
| `assert_int_equal` | function | `tests/test_css.c:1826` | `assert_int_equal(css_parse(".s:not(:focus)` |
| `assert_int_equal` | function | `tests/test_css.c:1854` | `assert_int_equal(css_parse("p:not(.x > y)` |
| `assert_int_equal` | function | `tests/test_css.c:2272` | `assert_int_equal(css_parse("li:nth-child()` |
| `assert_int_equal` | function | `tests/test_css.c:2307` | `assert_int_equal(css_parse("li:nth-of-type(2n)` |
| `assert_int_equal` | function | `tests/test_css.c:2339` | `assert_int_equal(css_parse("div:has(.x)` |
| `assert_int_equal` | function | `tests/test_css.c:2360` | `assert_int_equal(css_parse("html:lang(en)` |
| `assert_int_equal` | function | `tests/test_css.c:2716` | `assert_int_equal(css_parse(         "@media (min-width: 600px)` |
| `assert_int_equal` | function | `tests/test_css.c:2731` | `assert_int_equal(css_parse(         "@media screen and (min-width: 600px)` |
| `assert_int_equal` | function | `tests/test_css.c:2747` | `assert_int_equal(css_parse(         "@media (frobnicate: 1)` |
| `assert_int_equal` | function | `tests/test_css.c:5388` | `assert_int_equal(css_resolve(sh, "div", NULL, (const char *[])` |
| `assert_int_equal` | function | `tests/test_css.c:5512` | `assert_int_equal(css_parse("@media (min-width: 200em)` |
| `assert_int_equal` | function | `tests/test_css.c:5518` | `assert_int_equal(css_parse("@media (min-width: 40em)` |
| `box` | function | `tests/test_css.c:234` | `* box (CSS 2.1 section 10.8.1). With one line box per line and no separate * parent content edge, they land on the...` |
| `cls_el` | function | `tests/test_css.c:1222` | `static css_element cls_el(const char *tag, const char *const *cl, size_t n,                      ...` |
| `color_for_class` | function | `tests/test_css.c:1145` | `static int color_for_class(const char *css, const char *cls)` |
| `downstream` | function | `tests/test_css.c:663` | `* and deciding whether to fetch happens downstream (render_doc.c) */ assert_string_equal(css_parse_inline(...` |
| `dropped` | function | `tests/test_css.c:518` | `* dropped (which kept a lower rule's, or the UA button face's, colour). */ static void test_backg...` |
| `el_attr_node` | function | `tests/test_css.c:1490` | `static css_element el_attr_node(const char *tag, const char *id,                                 ...` |
| `el_node` | function | `tests/test_css.c:1455` | `static css_element el_node(const char *tag, const char *id,                            const char...` |
| `el_sib_node` | function | `tests/test_css.c:1470` | `static css_element el_sib_node(const char *tag, int nth, int nsib,                               ...` |
| `el_type_node` | function | `tests/test_css.c:1479` | `static css_element el_type_node(const char *tag, int nth, int nsib,                              ...` |
| `geometry` | function | `tests/test_css.c:2999` | `* hostile sheet never sees real window geometry (anti-fingerprinting) yet 100vh  * heroes and cal...` |
| `grammar` | function | `tests/test_css.c:5553` | `* grammar (spec/css.md), so they parse instead of dropping. */ static void test_vendor_prefixes(v...` |
| `invalid` | function | `tests/test_css.c:765` | `* invalid (fail closed), not silently coerced into some default. */ css_style s = css_parse_inline("color...` |
| `main` | function | `tests/test_css.c:5670` | `int main(void)` |
| `root_is_dark_html` | function | `tests/test_css.c:969` | `static int root_is_dark_html(void *ctx, const css_sel *sel)` |
| `silent` | function | `tests/test_css.c:2613` | `* silent (anti-DoS truncation, not a parse failure). 500 filler rules is well past  * the OLD cap...` |
| `terminator` | function | `tests/test_css.c:2014` | `* terminator (consumed, not painted);` |
| `test_adjacent_sibling_combinator` | function | `tests/test_css.c:1581` | `static void test_adjacent_sibling_combinator(void **state)` |
| `test_anim_keyframes_resolved_from_sheet` | function | `tests/test_css.c:5217` | `static void test_anim_keyframes_resolved_from_sheet(void **state)` |
| `test_anim_transform_keyframes_from_sheet` | function | `tests/test_css.c:5250` | `static void test_anim_transform_keyframes_from_sheet(void **state)` |
| `test_animation_none_resets` | function | `tests/test_css.c:3434` | `static void test_animation_none_resets(void **state)` |
| `test_animation_shorthand_basic` | function | `tests/test_css.c:3409` | `static void test_animation_shorthand_basic(void **state)` |
| `test_animation_shorthand_ignores_bezier` | function | `tests/test_css.c:3427` | `static void test_animation_shorthand_ignores_bezier(void **state)` |
| `test_animation_shorthand_order_free` | function | `tests/test_css.c:3418` | `static void test_animation_shorthand_order_free(void **state)` |
| `test_at_rules_skipped` | function | `tests/test_css.c:2661` | `static void test_at_rules_skipped(void **state)` |
| `test_attr_case_insensitive_flag` | function | `tests/test_css.c:2448` | `static void test_attr_case_insensitive_flag(void **state)` |
| `test_attr_equals` | function | `tests/test_css.c:2398` | `static void test_attr_equals(void **state)` |
| `test_attr_in_combinator` | function | `tests/test_css.c:2505` | `static void test_attr_in_combinator(void **state)` |
| `test_attr_malformed_fail_closed` | function | `tests/test_css.c:2521` | `static void test_attr_malformed_fail_closed(void **state)` |
| `test_attr_name_case_insensitive` | function | `tests/test_css.c:2463` | `static void test_attr_name_case_insensitive(void **state)` |
| `test_attr_operators` | function | `tests/test_css.c:2416` | `static void test_attr_operators(void **state)` |
| `test_attr_presence` | function | `tests/test_css.c:2385` | `static void test_attr_presence(void **state)` |
| `test_attr_quoted_value_with_space` | function | `tests/test_css.c:2474` | `static void test_attr_quoted_value_with_space(void **state)` |
| `test_attr_specificity_and_compound` | function | `tests/test_css.c:2488` | `static void test_attr_specificity_and_compound(void **state)` |
| `test_backdrop_filter_blur` | function | `tests/test_css.c:5177` | `static void test_backdrop_filter_blur(void **state)` |
| `test_background_clip_text` | function | `tests/test_css.c:5052` | `static void test_background_clip_text(void **state)` |
| `test_background_rgba_alpha` | function | `tests/test_css.c:5023` | `static void test_background_rgba_alpha(void **state)` |
| `test_background_shorthand_resets_gradient` | function | `tests/test_css.c:621` | `static void test_background_shorthand_resets_gradient(void **state)` |
| `test_bare_ms_box_sizing_drops` | function | `tests/test_css.c:3785` | `static void test_bare_ms_box_sizing_drops(void **state)` |
| `test_bg_image_url_absolute` | function | `tests/test_css.c:660` | `static void test_bg_image_url_absolute(void **state)` |
| `test_bg_image_url_basic` | function | `tests/test_css.c:642` | `static void test_bg_image_url_basic(void **state)` |
| `test_bg_image_url_gradient_mutually_exclusive` | function | `tests/test_css.c:696` | `static void test_bg_image_url_gradient_mutually_exclusive(void **state)` |
| `test_bg_image_url_none_and_junk_reset` | function | `tests/test_css.c:669` | `static void test_bg_image_url_none_and_junk_reset(void **state)` |
| `test_bg_image_url_overlong_fails_closed` | function | `tests/test_css.c:683` | `static void test_bg_image_url_overlong_fails_closed(void **state)` |
| `test_bg_image_url_quoted` | function | `tests/test_css.c:649` | `static void test_bg_image_url_quoted(void **state)` |
| `test_bg_position_center_by_identity` | function | `tests/test_css.c:3495` | `static void test_bg_position_center_by_identity(void **state)` |
| `test_bg_position_collision_drops` | function | `tests/test_css.c:3516` | `static void test_bg_position_collision_drops(void **state)` |
| `test_bg_position_edge_offset` | function | `tests/test_css.c:3483` | `static void test_bg_position_edge_offset(void **state)` |
| `test_bg_position_four_value` | function | `tests/test_css.c:3506` | `static void test_bg_position_four_value(void **state)` |
| `test_bg_shorthand_captures_url_and_resets_color` | function | `tests/test_css.c:704` | `static void test_bg_shorthand_captures_url_and_resets_color(void **state)` |
| `test_bg_size_and_repeat` | function | `tests/test_css.c:723` | `static void test_bg_size_and_repeat(void **state)` |
| `test_border_longhands` | function | `tests/test_css.c:3867` | `static void test_border_longhands(void **state)` |
| `test_border_shorthand` | function | `tests/test_css.c:3837` | `static void test_border_shorthand(void **state)` |
| `test_box_auto_and_centering` | function | `tests/test_css.c:2832` | `static void test_box_auto_and_centering(void **state)` |
| `test_box_clamp_anti_dos` | function | `tests/test_css.c:3089` | `static void test_box_clamp_anti_dos(void **state)` |
| `test_box_extension_sheet_cascade` | function | `tests/test_css.c:3139` | `static void test_box_extension_sheet_cascade(void **state)` |
| `test_box_orient_maps_to_flex_direction` | function | `tests/test_css.c:4015` | `static void test_box_orient_maps_to_flex_direction(void **state)` |
| `test_box_shadow_and_outline` | function | `tests/test_css.c:3893` | `static void test_box_shadow_and_outline(void **state)` |
| `test_box_shadow_layers_and_alpha` | function | `tests/test_css.c:5629` | `static void test_box_shadow_layers_and_alpha(void **state)` |
| `test_box_sheet_cascade_inline_wins` | function | `tests/test_css.c:3266` | `static void test_box_sheet_cascade_inline_wins(void **state)` |
| `test_box_shorthand_expansion` | function | `tests/test_css.c:2804` | `static void test_box_shorthand_expansion(void **state)` |
| `test_box_sizing` | function | `tests/test_css.c:3829` | `static void test_box_sizing(void **state)` |
| `test_box_units_and_failclosed` | function | `tests/test_css.c:2849` | `static void test_box_units_and_failclosed(void **state)` |
| `test_calc_basic_arithmetic` | function | `tests/test_css.c:2945` | `static void test_calc_basic_arithmetic(void **state)` |
| `test_calc_clamped_anti_dos` | function | `tests/test_css.c:2991` | `static void test_calc_clamped_anti_dos(void **state)` |
| `test_calc_dimension_errors_fail_closed` | function | `tests/test_css.c:2969` | `static void test_calc_dimension_errors_fail_closed(void **state)` |
| `test_calc_inside_shorthands` | function | `tests/test_css.c:3044` | `static void test_calc_inside_shorthands(void **state)` |
| `test_calc_precedence_and_parens` | function | `tests/test_css.c:2954` | `static void test_calc_precedence_and_parens(void **state)` |
| `test_calc_shape_mismatch_drops` | function | `tests/test_css.c:3777` | `static void test_calc_shape_mismatch_drops(void **state)` |
| `test_calc_units_and_signs` | function | `tests/test_css.c:2961` | `static void test_calc_units_and_signs(void **state)` |
| `test_calc_with_custom_property` | function | `tests/test_css.c:3082` | `static void test_calc_with_custom_property(void **state)` |
| `test_cascade_document_order` | function | `tests/test_css.c:2643` | `static void test_cascade_document_order(void **state)` |
| `test_cascade_inline_wins` | function | `tests/test_css.c:2652` | `static void test_cascade_inline_wins(void **state)` |
| `test_cascade_specificity` | function | `tests/test_css.c:2597` | `static void test_cascade_specificity(void **state)` |
| `test_child_combinator` | function | `tests/test_css.c:1534` | `static void test_child_combinator(void **state)` |
| `test_clip_auto` | function | `tests/test_css.c:5536` | `static void test_clip_auto(void **state)` |
| `test_clip_rect` | function | `tests/test_css.c:5526` | `static void test_clip_rect(void **state)` |
| `test_color_keeps_alpha` | function | `tests/test_css.c:1985` | `static void test_color_keeps_alpha(void **state)` |
| `test_combinator_class_chain` | function | `tests/test_css.c:1562` | `static void test_combinator_class_chain(void **state)` |
| `test_combinator_specificity_sum` | function | `tests/test_css.c:1547` | `static void test_combinator_specificity_sum(void **state)` |
| `test_component_var_cascade_order` | function | `tests/test_css.c:1343` | `static void test_component_var_cascade_order(void **state)` |
| `test_component_var_inherited_by_child` | function | `tests/test_css.c:1323` | `static void test_component_var_inherited_by_child(void **state)` |

Next: [SYMBOLS_p11.md](SYMBOLS_p11.md)
