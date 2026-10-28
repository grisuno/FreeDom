# Symbols (page 10 of 16)
Previous: [SYMBOLS_p9.md](SYMBOLS_p9.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `pv_set_justify_self` | function | `src/page_view.c:843` | `void pv_set_justify_self(pv_view *v, int justify_self)` |
| `pv_set_node_id` | function | `src/page_view.c:823` | `void pv_set_node_id(pv_view *v, dom_node_id node_id)` |
| `pv_set_oof` | function | `src/page_view.c:838` | `void pv_set_oof(pv_view *v, int oof)` |
| `pv_set_own_box` | function | `src/page_view.c:833` | `void pv_set_own_box(pv_view *v, int box_id)` |
| `pv_set_row_span` | function | `src/page_view.c:702` | `void pv_set_row_span(pv_view *v, int row_span)` |
| `pv_set_text_ext` | function | `src/page_view.c:631` | `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)` |
| `pv_set_text_style` | function | `src/page_view.c:612` | `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,                 ...` |
| `pv_set_ua_tag` | function | `src/page_view.c:817` | `void pv_set_ua_tag(pv_view *v, int ua_tag)` |
| `pv_style_cache` | struct | `src/page_view.c:2311` | `` |
| `pv_style_cache_free` | function | `src/page_view.c:2380` | `static void pv_style_cache_free(pv_style_cache *c)` |
| `pv_style_cache_init` | function | `src/page_view.c:2360` | `static int pv_style_cache_init(pv_style_cache *c)` |
| `pv_svg_append_root_attrs` | function | `src/page_view.c:868` | `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs,                ...` |
| `pv_text_ext_merge` | function | `src/page_view.c:1423` | `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)` |
| `pv_text_ext_reset` | function | `src/page_view.c:1397` | `void pv_text_ext_reset(pv_text_ext *e)` |
| `pv_var_node` | struct | `src/page_view.c:2295` | `` |
| `pv_var_push` | function | `src/page_view.c:2467` | `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,                       ...` |
| `px` | function | `src/page_view.c:5948` | `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */                 if (iw <...` |
| `resolve_context` | function | `src/page_view.c:3362` | `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,                 ...` |
| `resolves` | function | `src/page_view.c:1051` | `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close  * button/tooltip w...` |
| `roman_marker` | function | `src/page_view.c:4810` | `static void roman_marker(int n, int upper, char *out, size_t cap)` |
| `run_init_common` | function | `src/page_view.c:165` | `static void run_init_common(pv_run *r)` |
| `serialize_subtree` | function | `src/page_view.c:4177` | `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)` |
| `size` | function | `src/page_view.c:2802` | `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */ static void app...` |
| `srcset_slot_width` | function | `src/page_view.c:4347` | `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,                               ...` |
| `string` | function | `src/page_view.c:4463` | `* Returns a heap string (caller frees) or NULL when neither carries a class —  * NULL simply mean...` |
| `subtree_has_own_text` | function | `src/page_view.c:3274` | `static int subtree_has_own_text(const lxb_dom_node_t *n, const lxb_dom_node_t *base,             ...` |
| `subtree_is_oof` | function | `src/page_view.c:2782` | `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,                      ...` |
| `sz_count` | function | `src/page_view.c:4155` | `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)` |
| `sz_fill` | struct | `src/page_view.c:4163` | `` |
| `sz_write` | function | `src/page_view.c:4169` | `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)` |
| `table` | function | `src/page_view.c:5055` | `* FLOW table (multi-link: walked so its links survive) do NOT suppress their  * content -- their ...` |
| `table_columns` | function | `src/page_view.c:5073` | `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)` |
| `trying` | function | `src/page_view.c:1917` | `* a real page passes without trying (slashdot's front page saturates it), and past  * it box_reg_...` |
| `ua_tag_of` | function | `src/page_view.c:1130` | `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)` |
| `under_unrendered` | function | `src/page_view.c:4575` | `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)` |
| `utf8_encode` | function | `src/page_view.c:104` | `static size_t utf8_encode(unsigned int cp, char *out)` |
| `utf8_sanitized_dup` | function | `src/page_view.c:117` | `static char *utf8_sanitized_dup(const char *s)` |
| `walk` | function | `src/page_view.c:3984` | `* far on this walk (they are all inside this element). */                          /* The innermo...` |
| `pe_build_path` | function | `src/pdf_export.c:91` | `pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz)` |
| `pe_build_path_ext` | function | `src/pdf_export.c:66` | `pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,                 ...` |
| `pe_paginate` | function | `src/pdf_export.c:95` | `size_t pe_paginate(const double *tops, const double *heights, size_t n,                    double...` |
| `pe_safe_basename` | function | `src/pdf_export.c:25` | `pe_status pe_safe_basename(const char *title, char *out, size_t outsz)` |
| `PT_LINE_CAP` | macro | `src/perf_trace.c:107` | `#define PT_LINE_CAP` |
| `cmp_u64` | function | `src/perf_trace.c:71` | `static int cmp_u64(const void *a, const void *b)` |
| `pt_count` | function | `src/perf_trace.c:35` | `size_t pt_count(const pt_trace *t, pt_stage stage)` |
| `pt_elapsed_us` | function | `src/perf_trace.c:21` | `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us)` |
| `pt_format` | function | `src/perf_trace.c:109` | `size_t pt_format(const pt_trace *t, char *buf, size_t cap)` |
| `pt_init` | function | `src/perf_trace.c:16` | `void pt_init(pt_trace *t)` |
| `pt_last_us` | function | `src/perf_trace.c:40` | `uint64_t pt_last_us(const pt_trace *t, pt_stage stage)` |
| `pt_max_us` | function | `src/perf_trace.c:60` | `uint64_t pt_max_us(const pt_trace *t, pt_stage stage)` |
| `pt_median_us` | function | `src/perf_trace.c:79` | `uint64_t pt_median_us(const pt_trace *t, pt_stage stage)` |
| `pt_min_us` | function | `src/perf_trace.c:49` | `uint64_t pt_min_us(const pt_trace *t, pt_stage stage)` |
| `pt_record` | function | `src/perf_trace.c:26` | `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us)` |
| `pt_stage_name` | function | `src/perf_trace.c:89` | `const char *pt_stage_name(pt_stage stage)` |
| `PQS_SS_LEN` | macro | `src/pq_seal.c:17` | `#define PQS_SS_LEN` |
| `derive_key` | function | `src/pq_seal.c:81` | `static int derive_key(const uint8_t ss[PQS_SS_LEN], const uint8_t wrap[LS_KEY_LEN],              ...` |
| `keys_wrap` | function | `src/pq_seal.c:35` | `static pqs_keys *keys_wrap(EVP_PKEY *pkey)` |
| `pqs_buf_free` | function | `src/pq_seal.c:23` | `void pqs_buf_free(uint8_t *buf, size_t len)` |
| `pqs_export` | function | `src/pq_seal.c:55` | `pqs_status pqs_export(const pqs_keys *k, uint8_t **der, size_t *len)` |
| `pqs_free` | function | `src/pq_seal.c:29` | `void pqs_free(pqs_keys *k)` |
| `pqs_generate` | function | `src/pq_seal.c:42` | `pqs_status pqs_generate(pqs_keys **out)` |
| `pqs_import` | function | `src/pq_seal.c:68` | `pqs_status pqs_import(const uint8_t *der, size_t len, pqs_keys **out)` |
| `pqs_keys` | struct | `src/pq_seal.c:19` | `` |
| `pqs_open` | function | `src/pq_seal.c:147` | `pqs_status pqs_open(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],                     const ...` |
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
| `rd_at` | function | `src/render_doc.c:771` | `const rd_block *rd_at(const rd_doc *d, size_t i)` |
| `rd_block_heading_level` | function | `src/render_doc.c:808` | `int rd_block_heading_level(const rd_block *b)` |
| `rd_block_tag` | function | `src/render_doc.c:819` | `const char *rd_block_tag(const rd_block *b)` |
| `rd_box_at` | function | `src/render_doc.c:780` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)` |
| `rd_box_count` | function | `src/render_doc.c:776` | `size_t rd_box_count(const rd_doc *d)` |
| `rd_build` | function | `src/render_doc.c:274` | `rd_status rd_build(const pv_view *view, rdp_caps caps,                    const char *top_level_u...` |
| `rd_cont_at` | function | `src/render_doc.c:789` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)` |
| `rd_cont_count` | function | `src/render_doc.c:785` | `size_t rd_cont_count(const rd_doc *d)` |
| `rd_count` | function | `src/render_doc.c:767` | `size_t rd_count(const rd_doc *d)` |
| `rd_free` | function | `src/render_doc.c:750` | `void rd_free(rd_doc *d)` |
| `rd_image_fail_label` | function | `src/render_doc.c:885` | `const char *rd_image_fail_label(img_fail_reason reason)` |
| `rd_image_label` | function | `src/render_doc.c:874` | `const char *rd_image_label(rdp_img_decision d)` |
| `rd_input_invisible` | function | `src/render_doc.c:870` | `int rd_input_invisible(int input_type)` |
| `rd_input_label` | function | `src/render_doc.c:850` | `const char *rd_input_label(int input_type)` |
| `rd_kind_name` | function | `src/render_doc.c:794` | `const char *rd_kind_name(rd_kind k)` |
| `rd_push` | function | `src/render_doc.c:60` | `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,                  ...` |
| `rd_push_input` | function | `src/render_doc.c:212` | `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` |
| `resolve_image_decision` | function | `src/render_doc.c:248` | `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,         ...` |
| `unset` | function | `src/render_doc.c:685` | `* background paints as if unset (no border/box-shadow-style                  * "broken image" pla...` |
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
| `EPIPE` | function | `src/tab.c:2087` | `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();` |
| `FB_MAX_FILE_BYTES` | function | `src/tab.c:1002` | `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify  * the stream. ...` |
| `PV_MAX_CONTAINERS_WIRE` | macro | `src/tab.c:97` | `#define PV_MAX_CONTAINERS_WIRE` |
| `TAB_ASYNC_THREADS` | macro | `src/tab.c:138` | `#define TAB_ASYNC_THREADS` |
| `TAB_MAX_ASYNC_PENDING` | macro | `src/tab.c:136` | `#define TAB_MAX_ASYNC_PENDING` |
| `TAB_MAX_BATCH_BYTES` | macro | `src/tab.c:139` | `#define TAB_MAX_BATCH_BYTES` |
| `TAB_MAX_EXTERN_CSS` | macro | `src/tab.c:1075` | `#define TAB_MAX_EXTERN_CSS` |
| `TAB_MAX_GEOM_WORDS` | macro | `src/tab.c:124` | `#define TAB_MAX_GEOM_WORDS` |
| `TAB_MAX_HIST_BYTES` | macro | `src/tab.c:118` | `#define TAB_MAX_HIST_BYTES` |
| `TAB_MAX_HIST_OPS` | macro | `src/tab.c:117` | `#define TAB_MAX_HIST_OPS` |
| `TAB_MAX_JS_JOBS` | macro | `src/tab.c:145` | `#define TAB_MAX_JS_JOBS` |
| `TAB_MAX_NET_ROUNDS` | macro | `src/tab.c:137` | `#define TAB_MAX_NET_ROUNDS` |
| `TAB_MAX_OPENS` | macro | `src/tab.c:120` | `#define TAB_MAX_OPENS` |
| `TAB_MAX_OPEN_BYTES` | macro | `src/tab.c:121` | `#define TAB_MAX_OPEN_BYTES` |
| `TAB_MAX_RUNS` | macro | `src/tab.c:93` | `#define TAB_MAX_RUNS` |
| `TAB_MAX_STORAGE` | macro | `src/tab.c:113` | `#define TAB_MAX_STORAGE` |
| `TAB_MAX_SUBREQ` | macro | `src/tab.c:143` | `#define TAB_MAX_SUBREQ` |
| `TAB_MAX_SUBRESOURCE` | macro | `src/tab.c:144` | `#define TAB_MAX_SUBRESOURCE` |
| `TAB_MAX_URL` | macro | `src/tab.c:100` | `#define TAB_MAX_URL` |
| `TAB_MAX_WS_MSG` | macro | `src/tab.c:109` | `#define TAB_MAX_WS_MSG` |
| `TAB_SCREEN_H` | macro | `src/tab.c:66` | `#define TAB_SCREEN_H` |
| `TAB_SCREEN_W` | macro | `src/tab.c:65` | `#define TAB_SCREEN_W` |
| `TAB_WIRE_A_N` | macro | `src/tab.c:71` | `#define TAB_WIRE_A_N` |
| `TAB_WIRE_BOX_F_N` | macro | `src/tab.c:73` | `#define TAB_WIRE_BOX_F_N` |
| `TAB_WIRE_B_N` | macro | `src/tab.c:72` | `#define TAB_WIRE_B_N` |
| `TAB_WIRE_GRID_N` | macro | `src/tab.c:74` | `#define TAB_WIRE_GRID_N` |
| `TAB_WIRE_HEAD_N` | macro | `src/tab.c:70` | `#define TAB_WIRE_HEAD_N` |
| `WHERE` | function | `src/tab.c:1526` | `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...` |
| `_GNU_SOURCE` | macro | `src/tab.c:14` | `#define _GNU_SOURCE` |
| `adopt_worker` | function | `src/tab.c:3087` | `static tab_status adopt_worker(const tab_spawned *sp, tab **out)` |
| `blocks` | function | `src/tab.c:570` | `*  * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the  * grid arr...` |
| `budget_remaining_ms` | function | `src/tab.c:1032` | `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` |
| `buffer` | function | `src/tab.c:505` | `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...` |
| `child_fetch` | function | `src/tab.c:381` | `static int child_fetch(void *vctx, const char *method, const char *url,                        co...` |
| `child_fetch_async` | function | `src/tab.c:397` | `static int child_fetch_async(void *vctx, const char *method, const char *url,                    ...` |
| `child_handle_click` | function | `src/tab.c:1830` | `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_decode_image` | function | `src/tab.c:2031` | `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` |
| `child_handle_decode_image_b64` | function | `src/tab.c:2053` | `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)` |
| `child_handle_eval` | function | `src/tab.c:1990` | `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` |
| `child_handle_event` | function | `src/tab.c:1844` | `static void child_handle_event(int wfd, child_state *cs)` |
| `child_handle_geom` | function | `src/tab.c:1930` | `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` |
| `child_handle_load` | function | `src/tab.c:1255` | `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,            ...` |
| `child_handle_mouse` | function | `src/tab.c:1892` | `static void child_handle_mouse(int wfd, child_state *cs)` |
| `child_handle_mutation` | function | `src/tab.c:1749` | `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,                         ...` |
| `child_handle_submit` | function | `src/tab.c:1956` | `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_tick` | function | `src/tab.c:1834` | `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)` |
| `child_next_timer_ms` | function | `src/tab.c:1734` | `static int32_t child_next_timer_ms(child_state *cs)` |
| `child_read_reply` | function | `src/tab.c:353` | `static int child_read_reply(child_state *cs, net_reply *out)` |
| `child_reset_page` | function | `src/tab.c:196` | `static void child_reset_page(child_state *cs)` |
| `child_state` | struct | `src/tab.c:156` | `` |
| `child_write_subreq` | function | `src/tab.c:328` | `static int child_write_subreq(child_state *cs, uint8_t tag, const char *method, const char *url, ...` |
| `clip_pm_ok` | function | `src/tab.c:78` | `static int clip_pm_ok(int32_t v)` |
| `column` | function | `src/tab.c:2626` | `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...` |
| `computed_signature` | function | `src/tab.c:224` | `static uint64_t computed_signature(const dom_index *idx)` |
| `content` | function | `src/tab.c:1588` | `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...` |
| `ctype_is_css` | function | `src/tab.c:1055` | `static int ctype_is_css(const char *ctype)` |
| `ctype_is_javascript` | function | `src/tab.c:1046` | `static int ctype_is_javascript(const char *ctype)` |
| `depth` | function | `src/tab.c:2117` | `* defense in depth (seccomp already excludes open/socket/exec);` |
| `exec_worker_child` | function | `src/tab.c:3016` | `static void exec_worker_child(int rfd, int wfd)` |
| `fallback` | function | `src/tab.c:1336` | `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it...` |
| `frames` | function | `src/tab.c:3965` | `* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of...` |
| `gate_js_nav` | function | `src/tab.c:3614` | `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` |
| `gen_session_key` | function | `src/tab.c:2065` | `static uint64_t gen_session_key(void)` |
| `geom_parent` | function | `src/tab.c:1922` | `static dom_node_id geom_parent(void *ctx, dom_node_id n)` |
| `geometry_encode` | function | `src/tab.c:4286` | `static int32_t *geometry_encode(const jg_table *g, size_t *words_out)` |
| `hist_ops_free` | function | `src/tab.c:3423` | `static void hist_ops_free(tab_hist_op *ops, size_t n)` |
| `ignore_sigpipe` | function | `src/tab.c:2391` | `static void ignore_sigpipe(void)` |
| `io_failure` | function | `src/tab.c:3008` | `static tab_status io_failure(tab *t)` |
| `is_activation_event` | function | `src/tab.c:3488` | `static int is_activation_event(const char *type)` |
| `job_discard` | function | `src/tab.c:4310` | `static void job_discard(tab *t)` |
| `job_main` | function | `src/tab.c:4332` | `static void *job_main(void *arg)` |
| `job_start` | function | `src/tab.c:4361` | `static tab_status job_start(tab *t)` |
| `layout` | function | `src/tab.c:2615` | `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....` |
| `load` | function | `src/tab.c:2351` | `* subresource requests this load (set per page: host in allow.conf AND js.conf);` |
| `log_external_skip` | function | `src/tab.c:1063` | `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,                 ...` |
| `net_reply` | struct | `src/tab.c:317` | `` |
| `net_reply_free` | function | `src/tab.c:325` | `static void net_reply_free(net_reply *r)` |
| `once` | function | `src/tab.c:1637` | `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);` |
| `open_urls_free` | function | `src/tab.c:3497` | `static void open_urls_free(char **u, size_t n)` |
| `parse_worker_fd` | function | `src/tab.c:2312` | `static int parse_worker_fd(const char *s, int *out)` |
| `prof_lap` | function | `src/tab.c:444` | `static void prof_lap(const char *what, double *t0)` |
| `prof_now_ms` | function | `src/tab.c:434` | `static double prof_now_ms(void)` |
| `prof_on` | function | `src/tab.c:439` | `static int prof_on(void)` |
| `rad_len_ok` | function | `src/tab.c:84` | `static int rad_len_ok(int32_t v, int dflt)` |
| `read_console` | function | `src/tab.c:2961` | `static int read_console(int fd, fb_buffer *out)` |
| `read_field` | function | `src/tab.c:2417` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `read_opens` | function | `src/tab.c:3507` | `static tab_status read_opens(tab *t, const char *page_url, int gesture,                          ...` |
| `read_view` | function | `src/tab.c:2433` | `static int read_view(int fd, pv_view **out)` |
| `read_ws` | function | `src/tab.c:3545` | `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` |
| `reap_spawned` | function | `src/tab.c:3078` | `static void reap_spawned(const tab_spawned *sp, int kill_it)` |
| `replies` | function | `src/tab.c:410` | `* writing replies (no pipe deadlock). */ static void child_net_drain(child_state *cs)` |
| `run` | function | `src/tab.c:1081` | `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).  * Call after every ...` |
| `run_js` | function | `src/tab.c:455` | `* regardless of run_js (a no-JS load simply never records a request). */ static int child_load(ch...` |
| `send_request` | function | `src/tab.c:2998` | `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` |
| `sig_mix` | function | `src/tab.c:216` | `static uint64_t sig_mix(uint64_t h, const char *s, size_t n)` |
| `spawn_worker` | function | `src/tab.c:3048` | `static tab_status spawn_worker(tab_spawned *sp)` |
| `status` | type_alias | `src/tab.c:317` | `typedef struct net_reply { int32_t status;` |
| `swap` | function | `src/tab.c:1646` | `* display:none hiding an element via class swap (CSS, not      * DOM removal). */     if (ok && v...` |
| `tab` | struct | `src/tab.c:2344` | `` |
| `tab_alive` | function | `src/tab.c:4189` | `int tab_alive(const tab *t)` |
| `tab_async_busy` | function | `src/tab.c:4357` | `int tab_async_busy(const tab *t)` |
| `tab_async_fd` | function | `src/tab.c:4348` | `int tab_async_fd(tab *t)` |
| `tab_async_finish` | function | `src/tab.c:4399` | `tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)` |
| `tab_async_sync` | function | `src/tab.c:4322` | `static void tab_async_sync(tab *t)` |
| `tab_await_result` | function | `src/tab.c:3968` | `static tab_status tab_await_result(tab *t)` |
| `tab_await_result_inner` | function | `src/tab.c:3976` | `static tab_status tab_await_result_inner(tab *t)` |
| `tab_batch_discard` | function | `src/tab.c:3418` | `static void tab_batch_discard(tab *t)` |
| `tab_batch_run` | function | `src/tab.c:3351` | `static int tab_batch_run(void *vt, const sqb_req *rq, sqb_res *out)` |
| `tab_child_pid` | function | `src/tab.c:4195` | `pid_t tab_child_pid(const tab *t)` |
| `tab_click` | function | `src/tab.c:3833` | `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)` |
| `tab_close` | function | `src/tab.c:4199` | `void tab_close(tab *t)` |
| `tab_decode_image` | function | `src/tab.c:4163` | `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)` |
| `tab_decode_image_data_url` | function | `src/tab.c:4170` | `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)` |
| `tab_decode_image_op` | function | `src/tab.c:4121` | `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,         ...` |
| `tab_eval` | function | `src/tab.c:4080` | `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)` |
| `tab_eval_result_free` | function | `src/tab.c:4247` | `void tab_eval_result_free(tab_eval_result *r)` |
| `tab_geometry_async` | function | `src/tab.c:4384` | `tab_status tab_geometry_async(tab *t, const jg_table *g)` |
| `tab_geometry_send` | function | `src/tab.c:4268` | `static tab_status tab_geometry_send(tab *t, const int32_t *buf, size_t words)` |
| `tab_image_free` | function | `src/tab.c:4256` | `void tab_image_free(tab_image *img)` |
| `tab_inflight_request_headers` | function | `src/tab.c:3242` | `const char *tab_inflight_request_headers(void)` |
| `tab_last_subreq_stats` | function | `src/tab.c:3187` | `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)` |
| `tab_load` | function | `src/tab.c:3624` | `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)` |
| `tab_load_ex` | function | `src/tab.c:3628` | `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)` |
| `tab_load_full` | function | `src/tab.c:3632` | `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,             ...` |
| `tab_mod_fetch` | function | `src/tab.c:1169` | `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` |
| `tab_mod_resolve` | function | `src/tab.c:1139` | `static int tab_mod_resolve(void *host, const char *base, const char *spec,                       ...` |
| `tab_note_css_served` | function | `src/tab.c:3308` | `static void tab_note_css_served(tab *t, int ok, int status, const char *url, const char *rbody,  ...` |
| `tab_op_budget_us` | function | `src/tab.c:3304` | `static int64_t tab_op_budget_us(const tab *t)` |
| `tab_open` | function | `src/tab.c:3138` | `tab_status tab_open(tab **out)` |
| `tab_page_free` | function | `src/tab.c:4217` | `void tab_page_free(tab_page *p)` |
| `tab_parse_worker_args` | function | `src/tab.c:2324` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)` |
| `tab_popstate` | function | `src/tab.c:4421` | `tab_status tab_popstate(tab *t, int index, tab_page *out)` |
| `tab_prewarm` | function | `src/tab.c:3109` | `void tab_prewarm(void)` |
| `tab_prewarmed` | function | `src/tab.c:3115` | `int tab_prewarmed(void)` |
| `tab_prewarmed_pid` | function | `src/tab.c:3122` | `int tab_prewarmed_pid(void)` |
| `tab_read_subreq_fields` | function | `src/tab.c:3293` | `static int tab_read_subreq_fields(tab *t, char **method, char **url, char **body, size_t *blen,  ...` |
| `tab_read_view` | function | `src/tab.c:3959` | `tab_status tab_read_view(tab *t, tab_page *out)` |
| `tab_read_view_ex` | function | `src/tab.c:3985` | `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)` |
| `tab_refresh_alive` | function | `src/tab.c:2398` | `static void tab_refresh_alive(tab *t)` |
| `tab_report_response_headers` | function | `src/tab.c:3230` | `void tab_report_response_headers(const char *lines)` |
| `tab_serve_netwait` | function | `src/tab.c:3388` | `static int tab_serve_netwait(tab *t)` |
| `tab_serve_subreq` | function | `src/tab.c:3324` | `static int tab_serve_subreq(tab *t, int net_granted, int css_granted)` |
| `tab_serve_tag` | function | `src/tab.c:3410` | `static int tab_serve_tag(tab *t, uint8_t tag, int net_granted, int css_granted)` |
| `tab_set_cookies` | function | `src/tab.c:3210` | `void tab_set_cookies(tab *t, const char *cookies)` |
| `tab_set_css_allowed` | function | `src/tab.c:3182` | `void tab_set_css_allowed(tab *t, int allowed)` |
| `tab_set_css_sink` | function | `src/tab.c:3167` | `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)` |
| `tab_set_fetcher` | function | `src/tab.c:3161` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)` |
| `tab_set_frame_id` | function | `src/tab.c:3200` | `void tab_set_frame_id(tab *t, int id)` |
| `tab_set_geometry` | function | `src/tab.c:4296` | `tab_status tab_set_geometry(tab *t, const jg_table *g)` |
| `tab_set_identity` | function | `src/tab.c:3192` | `void tab_set_identity(tab *t, const char *serialized)` |
| `tab_set_net_allowed` | function | `src/tab.c:3177` | `void tab_set_net_allowed(tab *t, int allowed)` |
| `tab_set_op_net_budget_ms` | function | `src/tab.c:3173` | `void tab_set_op_net_budget_ms(tab *t, int ms)` |
| `tab_set_storage` | function | `src/tab.c:4448` | `void tab_set_storage(tab *t, const char *blob, size_t len)` |
| `tab_set_viewport_w` | function | `src/tab.c:3205` | `void tab_set_viewport_w(tab *t, int px)` |
| `tab_shutdown_spare` | function | `src/tab.c:3129` | `void tab_shutdown_spare(void)` |
| `tab_spawned` | struct | `src/tab.c:3036` | `` |
| `tab_submit` | function | `src/tab.c:3851` | `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` |
| `tab_submit_async` | function | `src/tab.c:3366` | `static int tab_submit_async(tab *t, int net_granted, int css_granted)` |
| `tab_subreq_permitted` | function | `src/tab.c:3216` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)` |
| `tab_tick` | function | `src/tab.c:3841` | `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)` |
| `tab_tick_async` | function | `src/tab.c:4374` | `tab_status tab_tick_async(tab *t, int elapsed_ms)` |
| `tab_url_resolve` | function | `src/tab.c:1130` | `static int tab_url_resolve(void *ctx, const char *base, const char *ref,                         ...` |
| `tab_worker_dispatch` | function | `src/tab.c:2334` | `void tab_worker_dispatch(int argc, char **argv)` |
| `tab_worker_run` | function | `src/tab.c:2085` | `static void tab_worker_run(int rfd, int wfd)` |
| `tab_write_reply` | function | `src/tab.c:3248` | `static int tab_write_reply(tab *t, int ok, int status, const char *rbody, size_t rlen,           ...` |
| `tab_ws_event` | function | `src/tab.c:4428` | `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,        ...` |
| `tests` | function | `src/tab.c:2508` | `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...` |
| `tzset` | function | `src/tab.c:2103` | `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);` |
| `window` | function | `src/tab.c:1210` | `* net window (cs->net_active). */ static void child_fetch_stylesheets(child_state *cs)` |
| `write_field` | function | `src/tab.c:536` | `static int write_field(int fd, const char *s)` |
| `write_full` | function | `src/tab.c:1667` | `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 \|\| write_full(wfd, text, xl) == 0) && write_view(wfd...` |
| `write_history` | function | `src/tab.c:1191` | `static int write_history(int wfd, child_state *cs)` |

Next: [SYMBOLS_p11.md](SYMBOLS_p11.md)
