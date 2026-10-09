# Symbols (page 8 of 13)
Previous: [SYMBOLS_p7.md](SYMBOLS_p7.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `pv_cache_find` | function | `src/page_view.c:2103` | `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cache_put` | function | `src/page_view.c:2123` | `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,                      ...` |
| `pv_cache_reindex` | function | `src/page_view.c:2061` | `static void pv_cache_reindex(pv_style_cache *c)` |
| `pv_cached_font_px` | function | `src/page_view.c:2118` | `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cont_at` | function | `src/page_view.c:767` | `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)` |
| `pv_cont_count` | function | `src/page_view.c:763` | `size_t pv_cont_count(const pv_view *v)` |
| `pv_cont_info` | struct | `src/page_view.c:1100` | `` |
| `pv_container_reg` | struct | `src/page_view.c:1510` | `` |
| `pv_content_hidden` | function | `src/page_view.c:1213` | `int pv_content_hidden(int box_hidden, int run_visibility)` |
| `pv_count` | function | `src/page_view.c:802` | `size_t pv_count(const pv_view *v)` |
| `pv_css_drops` | function | `src/page_view.c:5961` | `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,                        const cha...` |
| `pv_flow_reg` | struct | `src/page_view.c:2647` | `` |
| `pv_flow_reg` | struct | `src/page_view.c:3978` | `` |
| `pv_free` | function | `src/page_view.c:785` | `void pv_free(pv_view *v)` |
| `pv_item_track` | struct | `src/page_view.c:1174` | `` |
| `pv_mauto_of` | function | `src/page_view.c:1317` | `static int pv_mauto_of(const css_style *cs)` |
| `pv_new` | function | `src/page_view.c:331` | `pv_view *pv_new(void)` |
| `pv_node_map` | struct | `src/page_view.c:272` | `` |
| `pv_node_map_build` | function | `src/page_view.c:322` | `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root)` |
| `pv_node_map_free` | function | `src/page_view.c:286` | `static void pv_node_map_free(pv_node_map *m)` |
| `pv_node_map_init` | function | `src/page_view.c:278` | `static int pv_node_map_init(pv_node_map *m)` |
| `pv_parent_element` | function | `src/page_view.c:2183` | `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)` |
| `pv_ptr_hash` | function | `src/page_view.c:2053` | `static size_t pv_ptr_hash(const void *p)` |
| `pv_ptrmap` | struct | `src/page_view.c:1962` | `` |
| `pv_ptrmap_free` | function | `src/page_view.c:2008` | `static void pv_ptrmap_free(pv_ptrmap *m)` |
| `pv_ptrmap_get` | function | `src/page_view.c:1978` | `static int pv_ptrmap_get(const pv_ptrmap *m, const void *k, int *out)` |
| `pv_ptrmap_put` | function | `src/page_view.c:1986` | `static void pv_ptrmap_put(pv_ptrmap *m, const void *k, int v)` |
| `pv_ptrmap_slot` | function | `src/page_view.c:1968` | `static size_t pv_ptrmap_slot(const pv_ptrmap *m, const void *k)` |
| `pv_root_els` | struct | `src/page_view.c:3550` | `` |
| `pv_set_bgcolor` | function | `src/page_view.c:521` | `void pv_set_bgcolor(pv_view *v, int bg_rgb)` |
| `pv_set_block_id` | function | `src/page_view.c:722` | `void pv_set_block_id(pv_view *v, int block_id)` |
| `pv_set_box` | function | `src/page_view.c:681` | `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,                 int box_center, int ...` |
| `pv_set_box_maxw` | function | `src/page_view.c:704` | `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct)` |
| `pv_set_box_pct` | function | `src/page_view.c:693` | `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,                     ...` |
| `pv_set_color` | function | `src/page_view.c:516` | `void pv_set_color(pv_view *v, int fg_rgb)` |
| `pv_set_cont_box` | function | `src/page_view.c:632` | `void pv_set_cont_box(pv_view *v, int cont_box_id)` |
| `pv_set_cont_item` | function | `src/page_view.c:654` | `void pv_set_cont_item(pv_view *v, int cont_item)` |
| `pv_set_container` | function | `src/page_view.c:592` | `void pv_set_container(pv_view *v, int cont_id, int cont_display,                       int cont_g...` |
| `pv_set_emphasis` | function | `src/page_view.c:504` | `void pv_set_emphasis(pv_view *v, int bold, int italic)` |
| `pv_set_flex` | function | `src/page_view.c:636` | `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,                  int...` |
| `pv_set_flex_mauto` | function | `src/page_view.c:648` | `void pv_set_flex_mauto(pv_view *v, int mauto)` |
| `pv_set_float` | function | `src/page_view.c:659` | `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear,                 int ...` |
| `pv_set_grad_text` | function | `src/page_view.c:537` | `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)` |
| `pv_set_grid` | function | `src/page_view.c:618` | `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)` |
| `pv_set_grid_area` | function | `src/page_view.c:611` | `void pv_set_grid_area(pv_view *v, int row_start, int col_start)` |
| `pv_set_grid_rows` | function | `src/page_view.c:628` | `void pv_set_grid_rows(pv_view *v, int grid_rows)` |
| `pv_set_indent` | function | `src/page_view.c:511` | `void pv_set_indent(pv_view *v, int indent)` |
| `pv_set_input_checked` | function | `src/page_view.c:737` | `void pv_set_input_checked(pv_view *v, int checked)` |
| `pv_set_input_select_opts` | function | `src/page_view.c:742` | `void pv_set_input_select_opts(pv_view *v, const char *select_opts)` |
| `pv_set_node_id` | function | `src/page_view.c:717` | `void pv_set_node_id(pv_view *v, dom_node_id node_id)` |
| `pv_set_oof` | function | `src/page_view.c:732` | `void pv_set_oof(pv_view *v, int oof)` |
| `pv_set_own_box` | function | `src/page_view.c:727` | `void pv_set_own_box(pv_view *v, int box_id)` |
| `pv_set_row_span` | function | `src/page_view.c:607` | `void pv_set_row_span(pv_view *v, int row_span)` |
| `pv_set_text_ext` | function | `src/page_view.c:545` | `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)` |
| `pv_set_text_style` | function | `src/page_view.c:526` | `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,                 ...` |
| `pv_set_ua_tag` | function | `src/page_view.c:711` | `void pv_set_ua_tag(pv_view *v, int ua_tag)` |
| `pv_style_cache` | struct | `src/page_view.c:2033` | `` |
| `pv_style_cache_free` | function | `src/page_view.c:2089` | `static void pv_style_cache_free(pv_style_cache *c)` |
| `pv_style_cache_init` | function | `src/page_view.c:2071` | `static int pv_style_cache_init(pv_style_cache *c)` |
| `pv_text_ext_merge` | function | `src/page_view.c:1245` | `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)` |
| `pv_text_ext_reset` | function | `src/page_view.c:1219` | `void pv_text_ext_reset(pv_text_ext *e)` |
| `pv_var_node` | struct | `src/page_view.c:2028` | `` |
| `pv_var_push` | function | `src/page_view.c:2162` | `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,                       ...` |
| `px` | function | `src/page_view.c:5008` | `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */                 if (iw <...` |
| `resolve_context` | function | `src/page_view.c:2651` | `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,                 ...` |
| `resolves` | function | `src/page_view.c:887` | `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close  * button/tooltip w...` |
| `roman_marker` | function | `src/page_view.c:3926` | `static void roman_marker(int n, int upper, char *out, size_t cap)` |
| `run_init_common` | function | `src/page_view.c:159` | `static void run_init_common(pv_run *r)` |
| `serialize_subtree` | function | `src/page_view.c:3308` | `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)` |
| `size` | function | `src/page_view.c:2282` | `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */ static void app...` |
| `srcset_slot_width` | function | `src/page_view.c:3463` | `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,                               ...` |
| `string` | function | `src/page_view.c:3579` | `* Returns a heap string (caller frees) or NULL when neither carries a class —  * NULL simply mean...` |
| `subtree_has_own_text` | function | `src/page_view.c:2608` | `static int subtree_has_own_text(const lxb_dom_node_t *n, const lxb_dom_node_t *base,             ...` |
| `subtree_is_oof` | function | `src/page_view.c:2262` | `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,                      ...` |
| `sz_count` | function | `src/page_view.c:3286` | `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)` |
| `sz_fill` | struct | `src/page_view.c:3294` | `` |
| `sz_write` | function | `src/page_view.c:3300` | `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)` |
| `table` | function | `src/page_view.c:4166` | `* FLOW table (multi-link: walked so its links survive) do NOT suppress their  * content -- their ...` |
| `table_columns` | function | `src/page_view.c:4184` | `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)` |
| `trying` | function | `src/page_view.c:1620` | `* a real page passes without trying (slashdot's front page saturates it), and past  * it box_reg_...` |
| `ua_tag_of` | function | `src/page_view.c:962` | `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)` |
| `under_unrendered` | function | `src/page_view.c:3691` | `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)` |
| `utf8_encode` | function | `src/page_view.c:98` | `static size_t utf8_encode(unsigned int cp, char *out)` |
| `utf8_sanitized_dup` | function | `src/page_view.c:111` | `static char *utf8_sanitized_dup(const char *s)` |
| `walk` | function | `src/page_view.c:3150` | `* far on this walk (they are all inside this element). */                          /* The innermo...` |
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
| `PF_MAX_URL` | macro | `src/prefetch.c:21` | `#define PF_MAX_URL` |
| `_POSIX_C_SOURCE` | macro | `src/prefetch.c:12` | `#define _POSIX_C_SOURCE` |
| `attr_span` | struct | `src/prefetch.c:62` | `` |
| `ci_eq_span` | function | `src/prefetch.c:55` | `static int ci_eq_span(const char *s, size_t n, const char *kw)` |
| `ci_find` | function | `src/prefetch.c:46` | `static const char *ci_find(const char *p, const char *end, const char *kw)` |
| `ci_starts` | function | `src/prefetch.c:37` | `static int ci_starts(const char *p, const char *end, const char *kw)` |
| `emit` | function | `src/prefetch.c:117` | `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)` |
| `is_name_char` | function | `src/prefetch.c:27` | `static int is_name_char(char c)` |
| `is_ws` | function | `src/prefetch.c:23` | `static int is_ws(char c)` |
| `lower` | function | `src/prefetch.c:32` | `static int lower(int c)` |
| `pf_list_free` | function | `src/prefetch.c:193` | `void pf_list_free(pf_list *l)` |
| `pf_pool_finish` | function | `src/prefetch.c:310` | `void pf_pool_finish(pf_pool *p)` |
| `pf_pool_start` | function | `src/prefetch.c:227` | `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,                   pf_fetch_f...` |
| `pf_pool_take` | function | `src/prefetch.c:271` | `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,                  char **body,...` |
| `pf_pooled_fetch` | function | `src/prefetch.c:324` | `int pf_pooled_fetch(void *vctx, const char *method, const char *url,                     const ch...` |
| `pf_scan` | function | `src/prefetch.c:130` | `int pf_scan(const char *html, size_t len, pf_list *out)` |
| `pf_worker` | function | `src/prefetch.c:201` | `static void *pf_worker(void *arg)` |
| `PREFS_MAGIC` | macro | `src/prefs.c:20` | `#define PREFS_MAGIC` |
| `_POSIX_C_SOURCE` | macro | `src/prefs.c:11` | `#define _POSIX_C_SOURCE` |
| `apply_kv` | function | `src/prefs.c:225` | `static void apply_kv(prefs_state *out, const char *key, long val)` |
| `bookmark_push` | function | `src/prefs.c:91` | `static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title)` |
| `ci_contains` | function | `src/prefs.c:314` | `static int ci_contains(const char *s, const char *q)` |
| `ci_eq` | function | `src/prefs.c:300` | `static int ci_eq(char a, char b)` |
| `ci_starts` | function | `src/prefs.c:306` | `static int ci_starts(const char *s, const char *q)` |
| `history_push_back` | function | `src/prefs.c:109` | `static prefs_status history_push_back(prefs_state *p, const char *url)` |
| `prefs_bookmark_index` | function | `src/prefs.c:125` | `int prefs_bookmark_index(const prefs_state *p, const char *url)` |
| `prefs_bookmark_toggle` | function | `src/prefs.c:132` | `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,                              ...` |
| `prefs_bookmarks_page` | function | `src/prefs.c:408` | `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)` |
| `prefs_format` | function | `src/prefs.c:183` | `prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len)` |
| `prefs_free` | function | `src/prefs.c:74` | `void prefs_free(prefs_state *p)` |
| `prefs_history_add` | function | `src/prefs.c:152` | `prefs_status prefs_history_add(prefs_state *p, const char *url)` |
| `prefs_init` | function | `src/prefs.c:66` | `void prefs_init(prefs_state *p)` |
| `prefs_parse` | function | `src/prefs.c:241` | `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)` |
| `prefs_suggest` | function | `src/prefs.c:344` | `int prefs_suggest(const prefs_state *p, const char *query,                   char *out, size_t ro...` |
| `sb_esc` | function | `src/prefs.c:387` | `static void sb_esc(sbuf *b, const char *s)` |
| `sb_link_item` | function | `src/prefs.c:400` | `static void sb_link_item(sbuf *b, const char *url, const char *label)` |
| `sb_put` | function | `src/prefs.c:369` | `static void sb_put(sbuf *b, const char *s, size_t n)` |
| `sb_str` | function | `src/prefs.c:384` | `static void sb_str(sbuf *b, const char *s)` |
| `sbuf` | struct | `src/prefs.c:367` | `` |
| `sugg_push` | function | `src/prefs.c:335` | `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,                       cons...` |
| `title_clean` | function | `src/prefs.c:39` | `static char *title_clean(const char *src)` |
| `url_prefix_match` | function | `src/prefs.c:323` | `static int url_prefix_match(const char *url, const char *q)` |
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
| `place` | function | `src/render_doc.c:220` | `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never...` |
| `rd_at` | function | `src/render_doc.c:704` | `const rd_block *rd_at(const rd_doc *d, size_t i)` |
| `rd_block_tag` | function | `src/render_doc.c:741` | `const char *rd_block_tag(const rd_block *b)` |
| `rd_box_at` | function | `src/render_doc.c:713` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)` |
| `rd_box_count` | function | `src/render_doc.c:709` | `size_t rd_box_count(const rd_doc *d)` |
| `rd_build` | function | `src/render_doc.c:252` | `rd_status rd_build(const pv_view *view, rdp_caps caps,                    const char *top_level_u...` |
| `rd_cont_at` | function | `src/render_doc.c:722` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)` |
| `rd_cont_count` | function | `src/render_doc.c:718` | `size_t rd_cont_count(const rd_doc *d)` |
| `rd_count` | function | `src/render_doc.c:700` | `size_t rd_count(const rd_doc *d)` |
| `rd_free` | function | `src/render_doc.c:684` | `void rd_free(rd_doc *d)` |
| `rd_image_fail_label` | function | `src/render_doc.c:807` | `const char *rd_image_fail_label(img_fail_reason reason)` |
| `rd_image_label` | function | `src/render_doc.c:796` | `const char *rd_image_label(rdp_img_decision d)` |
| `rd_input_invisible` | function | `src/render_doc.c:792` | `int rd_input_invisible(int input_type)` |
| `rd_input_label` | function | `src/render_doc.c:772` | `const char *rd_input_label(int input_type)` |
| `rd_kind_name` | function | `src/render_doc.c:727` | `const char *rd_kind_name(rd_kind k)` |
| `rd_push` | function | `src/render_doc.c:60` | `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,                  ...` |
| `rd_push_input` | function | `src/render_doc.c:195` | `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` |
| `resolve_image_decision` | function | `src/render_doc.c:230` | `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,         ...` |
| `unset` | function | `src/render_doc.c:619` | `* background paints as if unset (no border/box-shadow-style                  * "broken image" pla...` |
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
| `lower` | function | `src/request_policy.c:22` | `static char lower(char c)` |
| `psl_cmp` | function | `src/request_policy.c:36` | `static int psl_cmp(const void *key, const void *elem)` |
| `psl_in` | function | `src/request_policy.c:40` | `static int psl_in(const char *const *arr, size_t n, const char *key)` |
| `public_suffix_labels` | function | `src/request_policy.c:48` | `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)` |
| `rp_evaluate` | function | `src/request_policy.c:143` | `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)` |
| `rp_host_of` | function | `src/request_policy.c:76` | `int rp_host_of(const char *url, char *out, size_t out_size)` |
| `rp_same_site` | function | `src/request_policy.c:134` | `int rp_same_site(const char *top_level_url, const char *request_url)` |
| `rp_site_of` | function | `src/request_policy.c:102` | `int rp_site_of(const char *host, char *out, size_t out_size)` |
| `_POSIX_C_SOURCE` | macro | `src/secure_fetch.c:12` | `#define _POSIX_C_SOURCE` |
| `add_header` | function | `src/secure_fetch.c:722` | `static int add_header(struct curl_slist **h, const char *line)` |
| `body_sink` | struct | `src/secure_fetch.c:434` | `` |
| `ci_index` | function | `src/secure_fetch.c:56` | `static long ci_index(const char *haystack, const char *needle)` |
| `ci_starts_with` | function | `src/secure_fetch.c:44` | `static int ci_starts_with(const char *haystack, const char *prefix)` |
| `copy_bounded` | function | `src/secure_fetch.c:470` | `static void copy_bounded(char *dst, size_t dstsz, const char *src)` |
| `copy_checked` | function | `src/secure_fetch.c:325` | `static int copy_checked(char *dst, size_t dstsz, const char *src)` |
| `database` | function | `src/secure_fetch.c:485` | `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid...` |
| `fetch_ctx` | struct | `src/secure_fetch.c:457` | `` |
| `get_negotiated_group_name` | function | `src/secure_fetch.c:481` | `static const char *get_negotiated_group_name(SSL *ssl)` |
| `group` | function | `src/secure_fetch.c:499` | `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);` |
| `header_cb` | function | `src/secure_fetch.c:550` | `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` |
| `inspect_chain` | function | `src/secure_fetch.c:628` | `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` |
| `map_curl_error` | function | `src/secure_fetch.c:681` | `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)` |
| `module` | function | `src/secure_fetch.c:364` | `* pure url module (DRY);` |
| `name_is_pq_sig` | function | `src/secure_fetch.c:618` | `static int name_is_pq_sig(int pknid)` |
| `progress` | function | `src/secure_fetch.c:443` | `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);` |
| `redirect` | function | `src/secure_fetch.c:811` | `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a      * different orig...` |
| `sf_check_chain_policy` | function | `src/secure_fetch.c:284` | `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)` |
| `sf_check_group_is_pq` | function | `src/secure_fetch.c:275` | `sf_status sf_check_group_is_pq(const char *negotiated_group)` |
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
| `EPIPE` | function | `src/tab.c:1690` | `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();` |
| `FB_MAX_FILE_BYTES` | function | `src/tab.c:698` | `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify  * the stream. ...` |
| `PV_MAX_CONTAINERS_WIRE` | macro | `src/tab.c:74` | `#define PV_MAX_CONTAINERS_WIRE` |
| `TAB_MAX_EXTERN_CSS` | macro | `src/tab.c:771` | `#define TAB_MAX_EXTERN_CSS` |
| `TAB_MAX_GEOM_WORDS` | macro | `src/tab.c:101` | `#define TAB_MAX_GEOM_WORDS` |
| `TAB_MAX_HIST_BYTES` | macro | `src/tab.c:95` | `#define TAB_MAX_HIST_BYTES` |
| `TAB_MAX_HIST_OPS` | macro | `src/tab.c:94` | `#define TAB_MAX_HIST_OPS` |
| `TAB_MAX_JS_JOBS` | macro | `src/tab.c:113` | `#define TAB_MAX_JS_JOBS` |
| `TAB_MAX_OPENS` | macro | `src/tab.c:97` | `#define TAB_MAX_OPENS` |
| `TAB_MAX_OPEN_BYTES` | macro | `src/tab.c:98` | `#define TAB_MAX_OPEN_BYTES` |
| `TAB_MAX_RUNS` | macro | `src/tab.c:70` | `#define TAB_MAX_RUNS` |
| `TAB_MAX_STORAGE` | macro | `src/tab.c:90` | `#define TAB_MAX_STORAGE` |
| `TAB_MAX_SUBREQ` | macro | `src/tab.c:111` | `#define TAB_MAX_SUBREQ` |
| `TAB_MAX_SUBRESOURCE` | macro | `src/tab.c:112` | `#define TAB_MAX_SUBRESOURCE` |
| `TAB_MAX_URL` | macro | `src/tab.c:77` | `#define TAB_MAX_URL` |
| `TAB_MAX_WS_MSG` | macro | `src/tab.c:86` | `#define TAB_MAX_WS_MSG` |
| `TAB_SCREEN_H` | macro | `src/tab.c:58` | `#define TAB_SCREEN_H` |
| `TAB_SCREEN_W` | macro | `src/tab.c:57` | `#define TAB_SCREEN_W` |
| `TAB_WIRE_A_N` | macro | `src/tab.c:63` | `#define TAB_WIRE_A_N` |
| `TAB_WIRE_BOX_F_N` | macro | `src/tab.c:65` | `#define TAB_WIRE_BOX_F_N` |
| `TAB_WIRE_B_N` | macro | `src/tab.c:64` | `#define TAB_WIRE_B_N` |
| `TAB_WIRE_GRID_N` | macro | `src/tab.c:66` | `#define TAB_WIRE_GRID_N` |
| `TAB_WIRE_HEAD_N` | macro | `src/tab.c:62` | `#define TAB_WIRE_HEAD_N` |
| `WHERE` | function | `src/tab.c:1177` | `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...` |
| `_GNU_SOURCE` | macro | `src/tab.c:14` | `#define _GNU_SOURCE` |
| `answered` | function | `src/tab.c:2591` | `* A refused frame is still consumed and answered (status 0), so the protocol never  * desyncs. Re...` |
| `blocks` | function | `src/tab.c:330` | `*  * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the  * grid arr...` |
| `budget_remaining_ms` | function | `src/tab.c:728` | `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` |
| `buffer` | function | `src/tab.c:272` | `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...` |
| `child_handle_click` | function | `src/tab.c:1443` | `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_decode_image` | function | `src/tab.c:1634` | `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` |
| `child_handle_decode_image_b64` | function | `src/tab.c:1656` | `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)` |
| `child_handle_eval` | function | `src/tab.c:1601` | `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` |
| `child_handle_event` | function | `src/tab.c:1457` | `static void child_handle_event(int wfd, child_state *cs)` |
| `child_handle_geom` | function | `src/tab.c:1543` | `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` |
| `child_handle_load` | function | `src/tab.c:943` | `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,            ...` |
| `child_handle_mouse` | function | `src/tab.c:1505` | `static void child_handle_mouse(int wfd, child_state *cs)` |
| `child_handle_mutation` | function | `src/tab.c:1364` | `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,                         ...` |
| `child_handle_submit` | function | `src/tab.c:1567` | `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_tick` | function | `src/tab.c:1447` | `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)` |
| `child_next_timer_ms` | function | `src/tab.c:1349` | `static int32_t child_next_timer_ms(child_state *cs)` |
| `child_reset_page` | function | `src/tab.c:155` | `static void child_reset_page(child_state *cs)` |
| `child_state` | struct | `src/tab.c:124` | `` |
| `column` | function | `src/tab.c:2144` | `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...` |
| `content` | function | `src/tab.c:1210` | `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...` |
| `ctype_is_css` | function | `src/tab.c:751` | `static int ctype_is_css(const char *ctype)` |
| `ctype_is_javascript` | function | `src/tab.c:742` | `static int ctype_is_javascript(const char *ctype)` |
| `depth` | function | `src/tab.c:1711` | `* defense in depth (seccomp already excludes open/socket/exec);` |
| `exec_worker_child` | function | `src/tab.c:2481` | `static void exec_worker_child(int rfd, int wfd)` |
| `fallback` | function | `src/tab.c:1019` | `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it...` |
| `gate_js_nav` | function | `src/tab.c:2818` | `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` |
| `gen_session_key` | function | `src/tab.c:1668` | `static uint64_t gen_session_key(void)` |
| `geom_parent` | function | `src/tab.c:1535` | `static dom_node_id geom_parent(void *ctx, dom_node_id n)` |
| `hist_ops_free` | function | `src/tab.c:2627` | `static void hist_ops_free(tab_hist_op *ops, size_t n)` |
| `host` | function | `src/tab.c:284` | `* granted net access for this host (allow.conf AND js.conf). Otherwise they stay * undefined...` |
| `ignore_sigpipe` | function | `src/tab.c:1942` | `static void ignore_sigpipe(void)` |
| `io_failure` | function | `src/tab.c:2473` | `static tab_status io_failure(tab *t)` |
| `is_activation_event` | function | `src/tab.c:2692` | `static int is_activation_event(const char *type)` |
| `layout` | function | `src/tab.c:2133` | `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....` |
| `load` | function | `src/tab.c:1925` | `* subresource requests this load (set per page: host in allow.conf AND js.conf);` |
| `log_external_skip` | function | `src/tab.c:759` | `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,                 ...` |
| `once` | function | `src/tab.c:1255` | `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);` |
| `open_urls_free` | function | `src/tab.c:2701` | `static void open_urls_free(char **u, size_t n)` |
| `parse_worker_fd` | function | `src/tab.c:1886` | `static int parse_worker_fd(const char *s, int *out)` |
| `policy` | function | `src/tab.c:175` | `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a  * compromi...` |
| `read_console` | function | `src/tab.c:2426` | `static int read_console(int fd, fb_buffer *out)` |
| `read_field` | function | `src/tab.c:1968` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `read_opens` | function | `src/tab.c:2711` | `static tab_status read_opens(tab *t, const char *page_url, int gesture,                          ...` |
| `read_view` | function | `src/tab.c:1984` | `static int read_view(int fd, pv_view **out)` |
| `read_ws` | function | `src/tab.c:2749` | `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` |
| `run` | function | `src/tab.c:777` | `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).  * Call after every ...` |
| `run_js` | function | `src/tab.c:229` | `* regardless of run_js (a no-JS load simply never records a request). */ static int child_load(ch...` |
| `send_request` | function | `src/tab.c:2463` | `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` |
| `swap` | function | `src/tab.c:1264` | `* display:none hiding an element via class swap (CSS, not      * DOM removal). */     if (ok && v...` |
| `tab` | struct | `src/tab.c:1918` | `` |
| `tab_alive` | function | `src/tab.c:3349` | `int tab_alive(const tab *t)` |
| `tab_child_pid` | function | `src/tab.c:3355` | `pid_t tab_child_pid(const tab *t)` |
| `tab_click` | function | `src/tab.c:3022` | `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)` |
| `tab_close` | function | `src/tab.c:3359` | `void tab_close(tab *t)` |
| `tab_decode_image` | function | `src/tab.c:3325` | `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)` |
| `tab_decode_image_data_url` | function | `src/tab.c:3331` | `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)` |
| `tab_decode_image_op` | function | `src/tab.c:3283` | `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,         ...` |
| `tab_eval` | function | `src/tab.c:3243` | `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)` |
| `tab_eval_result_free` | function | `src/tab.c:3404` | `void tab_eval_result_free(tab_eval_result *r)` |
| `tab_image_free` | function | `src/tab.c:3413` | `void tab_image_free(tab_image *img)` |
| `tab_load` | function | `src/tab.c:2828` | `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)` |
| `tab_load_ex` | function | `src/tab.c:2832` | `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)` |
| `tab_load_full` | function | `src/tab.c:2836` | `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,             ...` |
| `tab_mod_fetch` | function | `src/tab.c:857` | `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` |
| `tab_mod_resolve` | function | `src/tab.c:835` | `static int tab_mod_resolve(void *host, const char *base, const char *spec,                       ...` |
| `tab_page_free` | function | `src/tab.c:3374` | `void tab_page_free(tab_page *p)` |
| `tab_parse_worker_args` | function | `src/tab.c:1898` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)` |
| `tab_popstate` | function | `src/tab.c:3449` | `tab_status tab_popstate(tab *t, int index, tab_page *out)` |
| `tab_read_view` | function | `src/tab.c:3143` | `tab_status tab_read_view(tab *t, tab_page *out)` |
| `tab_read_view_ex` | function | `src/tab.c:3147` | `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)` |
| `tab_refresh_alive` | function | `src/tab.c:1949` | `static void tab_refresh_alive(tab *t)` |
| `tab_set_cookies` | function | `src/tab.c:2573` | `void tab_set_cookies(tab *t, const char *cookies)` |
| `tab_set_css_allowed` | function | `src/tab.c:2563` | `void tab_set_css_allowed(tab *t, int allowed)` |
| `tab_set_fetcher` | function | `src/tab.c:2552` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)` |
| `tab_set_geometry` | function | `src/tab.c:3423` | `tab_status tab_set_geometry(tab *t, const jg_table *g)` |
| `tab_set_net_allowed` | function | `src/tab.c:2558` | `void tab_set_net_allowed(tab *t, int allowed)` |
| `tab_set_storage` | function | `src/tab.c:3474` | `void tab_set_storage(tab *t, const char *blob, size_t len)` |
| `tab_set_viewport_w` | function | `src/tab.c:2568` | `void tab_set_viewport_w(tab *t, int px)` |
| `tab_submit` | function | `src/tab.c:3038` | `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` |
| `tab_subreq_permitted` | function | `src/tab.c:2579` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)` |
| `tab_tick` | function | `src/tab.c:3029` | `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)` |
| `tab_url_resolve` | function | `src/tab.c:826` | `static int tab_url_resolve(void *ctx, const char *base, const char *ref,                         ...` |
| `tab_worker_dispatch` | function | `src/tab.c:1908` | `void tab_worker_dispatch(int argc, char **argv)` |
| `tab_worker_run` | function | `src/tab.c:1688` | `static void tab_worker_run(int rfd, int wfd)` |
| `tab_ws_event` | function | `src/tab.c:3455` | `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,        ...` |
| `tzset` | function | `src/tab.c:1706` | `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);` |
| `window` | function | `src/tab.c:898` | `* net window (cs->net_active). */ static void child_fetch_stylesheets(child_state *cs)` |
| `write_field` | function | `src/tab.c:296` | `static int write_field(int fd, const char *s)` |
| `write_full` | function | `src/tab.c:1284` | `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 \|\| write_full(wfd, text, xl) == 0) && write_view(wfd...` |
| `write_history` | function | `src/tab.c:879` | `static int write_history(int wfd, child_state *cs)` |
| `write_opens` | function | `src/tab.c:1337` | `static int write_opens(int wfd, child_state *cs)` |
| `write_storage` | function | `src/tab.c:1323` | `static int write_storage(int wfd, child_state *cs)` |
| `write_ws` | function | `src/tab.c:1306` | `static int write_ws(int wfd, child_state *cs)` |
| `ws_ops_free` | function | `src/tab.c:2740` | `static void ws_ops_free(tab_ws_op *ops, size_t n)` |
| `TSH_CACHE_SLOTS` | macro | `src/text_shape.c:32` | `#define TSH_CACHE_SLOTS` |
| `TSH_MAX_FONT_BYTES` | macro | `src/text_shape.c:28` | `#define TSH_MAX_FONT_BYTES` |
| `_POSIX_C_SOURCE` | macro | `src/text_shape.c:12` | `#define _POSIX_C_SOURCE` |
| `backend_init` | function | `src/text_shape.c:64` | `static int backend_init(void)` |
| `generic_name` | function | `src/text_shape.c:54` | `static const char *generic_name(int family)` |
| `get_entry` | function | `src/text_shape.c:152` | `static tsh_entry *get_entry(int family, int bold, int italic)` |
| `load_entry` | function | `src/text_shape.c:97` | `static int load_entry(tsh_entry *e, int family, int bold, int italic)` |
| `loaded` | type_alias | `src/text_shape.c:33` | `typedef struct tsh_entry { int loaded;` |
| `read_font_file` | function | `src/text_shape.c:81` | `static unsigned char *read_font_file(const char *path, long *out_n)` |
| `tsh_draw` | function | `src/text_shape.c:221` | `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,                     double x, doub...` |
| `tsh_entry` | struct | `src/text_shape.c:34` | `` |
| `tsh_measure` | function | `src/text_shape.c:214` | `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)` |
| `tsh_ready` | function | `src/text_shape.c:164` | `int tsh_ready(void)` |
| `tsh_shape` | function | `src/text_shape.c:169` | `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,                 ...` |
| `tsh_shutdown` | function | `src/text_shape.c:243` | `void tsh_shutdown(void)` |
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

Next: [SYMBOLS_p9.md](SYMBOLS_p9.md)
