# Symbols (page 7 of 19)
Previous: [SYMBOLS_p6.md](SYMBOLS_p6.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `bx_block_ua_box` | function | `src/box_style.c:225` | `bx_box bx_block_ua_box(int heading_level, int in_list, bx_ua_tag ua)` |
| `bx_border_box_h` | function | `src/box_style.c:335` | `double bx_border_box_h(double declared_h, int border_box,                        double pad_t, do...` |
| `bx_border_span` | function | `src/box_style.c:396` | `double bx_border_span(double width_cap, int border_box,                       double pad_l, doubl...` |
| `bx_content_cap` | function | `src/box_style.c:378` | `double bx_content_cap(double width_cap, int border_box,                       double pad_l, doubl...` |
| `bx_content_clipped` | function | `src/box_style.c:361` | `int bx_content_clipped(int overflow_x, int overflow_y)` |
| `bx_default_for_tag` | function | `src/box_style.c:163` | `bx_box bx_default_for_tag(const char *tag)` |
| `bx_default_for_ua` | function | `src/box_style.c:219` | `bx_box bx_default_for_ua(bx_ua_tag id)` |
| `bx_definite_content_h` | function | `src/box_style.c:352` | `double bx_definite_content_h(double h, double min_h, double max_h,                              i...` |
| `bx_display_name` | function | `src/box_style.c:454` | `const char *bx_display_name(bx_display d)` |
| `bx_flex_max_clamp` | function | `src/box_style.c:467` | `double bx_flex_max_clamp(double outer_basis, double mw_cap, int border_box,                      ...` |
| `bx_flex_min_clamp` | function | `src/box_style.c:389` | `double bx_flex_min_clamp(double outer_basis, double min_w, int border_box,                       ...` |
| `bx_line_height_px` | function | `src/box_style.c:484` | `double bx_line_height_px(int line_scale, double font_px)` |
| `bx_lp_px` | function | `src/box_style.c:367` | `double bx_lp_px(int px_val, int pct_pm, double basis)` |
| `bx_parse_display` | function | `src/box_style.c:261` | `bx_status bx_parse_display(const char *token, bx_display *out)` |
| `bx_pct_block_size` | function | `src/box_style.c:346` | `double bx_pct_block_size(int px_val, int pct_pm, double cb_h)` |
| `bx_place` | function | `src/box_style.c:271` | `bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,                 ...` |
| `bx_place_ex` | function | `src/box_style.c:474` | `bx_hplace bx_place_ex(double inset_l, double inset_r, double width_cap, int center,              ...` |
| `bx_replaced_box` | function | `src/box_style.c:321` | `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den,                     doub...` |
| `bx_table_role_of` | function | `src/box_style.c:171` | `bx_table_role bx_table_role_of(const char *tag, css_display display)` |
| `bx_ua_of_tag` | function | `src/box_style.c:210` | `bx_ua_tag bx_ua_of_tag(const char *tag)` |
| `bx_width_cap` | function | `src/box_style.c:288` | `double bx_width_cap(int w_px, int w_pct, double avail_w)` |
| `bx_width_cap2` | function | `src/box_style.c:313` | `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w)` |
| `copy_lower_trim` | function | `src/box_style.c:37` | `static int copy_lower_trim(const char *in, char *out, size_t out_size)` |
| `disp_row` | struct | `src/box_style.c:241` | `` |
| `is_ws` | function | `src/box_style.c:31` | `static int is_ws(char c)` |
| `name_cmp` | function | `src/box_style.c:50` | `static int name_cmp(const void *key, const void *elem)` |
| `tag_row` | struct | `src/box_style.c:61` | `` |
| `take` | function | `src/box_style.c:295` | `* caller has to take (Sizing 3 section 5.1), so to a resolver that only sums a * px and a percentage half they read...` |
| `BT_LEN_AUTO` | macro | `src/box_tree.c:34` | `#define BT_LEN_AUTO` |
| `BT_SC_DEPTH` | macro | `src/box_tree.c:609` | `#define BT_SC_DEPTH` |
| `BT_WRAP_EPS` | macro | `src/box_tree.c:65` | `#define BT_WRAP_EPS` |
| `assign_doc_order` | function | `src/box_tree.c:508` | `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,                   ...` |
| `block` | function | `src/box_tree.c:569` | `* true block (same flow neighbourhood), strictly better than zeros. NULL      * placed keeps lega...` |
| `bt_box_hidden` | function | `src/box_tree.c:887` | `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)` |
| `bt_containing_block` | function | `src/box_tree.c:558` | `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i,                         ...` |
| `bt_defer_roots` | function | `src/box_tree.c:919` | `size_t bt_defer_roots(const pv_box_def *boxes, size_t nbox,                       const bt_positi...` |
| `bt_in_subtree` | function | `src/box_tree.c:900` | `int bt_in_subtree(const pv_box_def *boxes, size_t nbox, size_t root, size_t bid)` |
| `bt_layout` | function | `src/box_tree.c:468` | `bt_status bt_layout(bt_node *root, double avail_w)` |
| `bt_nn` | function | `src/box_tree.c:61` | `static double bt_nn(double v)` |
| `bt_oof_anchor` | function | `src/box_tree.c:879` | `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)` |
| `bt_oof_avail` | function | `src/box_tree.c:911` | `double bt_oof_avail(int a, int a_pct, int b, int b_pct, double cb, int *both)` |
| `bt_oof_root` | function | `src/box_tree.c:883` | `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)` |
| `bt_resolve_positioning` | function | `src/box_tree.c:588` | `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,                           ...` |
| `bt_resolve_positioning_ex` | function | `src/box_tree.c:706` | `bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,                        ...` |
| `find_positioned_ancestor` | function | `src/box_tree.c:525` | `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,                        ...` |
| `height` | function | `src/box_tree.c:81` | `* exactly that height (Flexbox 9.4 step 15).  *  * wrap_reverse (node->wrap_reverse): when node->...` |
| `inset_unset` | function | `src/box_tree.c:554` | `static int inset_unset(int v, int pct_pm)` |
| `layout_block` | function | `src/box_tree.c:40` | `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,                    ...` |
| `layout_flex` | function | `src/box_tree.c:101` | `static bt_status layout_flex(bt_node *node, bt_node *const *kids, size_t nk,                     ...` |
| `layout_grid` | function | `src/box_tree.c:283` | `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,                     ...` |
| `layout_node` | function | `src/box_tree.c:423` | `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)` |
| `len` | type_alias | `src/box_tree.c:610` | `typedef struct sc_chain { uint16_t len;` |
| `nest_in_contexts` | function | `src/box_tree.c:638` | `static void nest_in_contexts(const pv_box_def *boxes, size_t nbox, const bt_positioned *tmp,     ...` |
| `oof_walk` | function | `src/box_tree.c:862` | `static int oof_walk(const pv_box_def *boxes, size_t nbox, int bid, int nearest)` |
| `resolve_inset` | function | `src/box_tree.c:545` | `static double resolve_inset(int v, int pct_pm, double basis)` |
| `sc_chain` | struct | `src/box_tree.c:611` | `` |
| `sc_chain_compare` | function | `src/box_tree.c:629` | `static int sc_chain_compare(const sc_chain *a, const sc_chain *b, const cx_item *by_ref)` |
| `sc_forms` | function | `src/box_tree.c:616` | `static int sc_forms(const pv_box_def *b)` |
| `sized` | function | `src/box_tree.c:353` | `* the tracks are sized (CSS Grid 1 11.5, items spanning several tracks come * last);` |
| `_POSIX_C_SOURCE` | macro | `src/browser.c:7` | `#define _POSIX_C_SOURCE` |
| `begin_pending` | function | `src/browser.c:72` | `static void begin_pending(browser_state *bs, int kind)` |
| `browser_abort_pending` | function | `src/browser.c:620` | `int browser_abort_pending(browser_state *bs)` |
| `browser_add_exception` | function | `src/browser.c:570` | `browser_status browser_add_exception(browser_state *bs, const char *host)` |
| `browser_back` | function | `src/browser.c:364` | `browser_status browser_back(browser_state *bs)` |
| `browser_can_back` | function | `src/browser.c:390` | `int browser_can_back(const browser_state *bs)` |
| `browser_can_forward` | function | `src/browser.c:394` | `int browser_can_forward(const browser_state *bs)` |
| `browser_closed_pop` | function | `src/browser.c:603` | `int browser_closed_pop(browser_closed *c, char *out, size_t cap)` |
| `browser_closed_push` | function | `src/browser.c:588` | `browser_status browser_closed_push(browser_closed *c, const char *url)` |
| `browser_commit_pending` | function | `src/browser.c:615` | `void browser_commit_pending(browser_state *bs)` |
| `browser_commit_url_bar` | function | `src/browser.c:232` | `browser_status browser_commit_url_bar(browser_state *bs)` |
| `browser_current_url` | function | `src/browser.c:398` | `const char *browser_current_url(const browser_state *bs)` |
| `browser_doc_index` | function | `src/browser.c:356` | `int browser_doc_index(const browser_state *bs)` |
| `browser_entry_doc` | function | `src/browser.c:351` | `int browser_entry_doc(const browser_state *bs, size_t pos)` |
| `browser_entry_scroll` | function | `src/browser.c:346` | `double browser_entry_scroll(const browser_state *bs)` |
| `browser_forward` | function | `src/browser.c:377` | `browser_status browser_forward(browser_state *bs)` |
| `browser_free` | function | `src/browser.c:208` | `void browser_free(browser_state *bs)` |
| `browser_has_pending` | function | `src/browser.c:650` | `int browser_has_pending(const browser_state *bs)` |
| `browser_init` | function | `src/browser.c:197` | `browser_status browser_init(browser_state *bs)` |
| `browser_is_exception` | function | `src/browser.c:562` | `int browser_is_exception(const browser_state *bs, const char *host)` |
| `browser_navigate` | function | `src/browser.c:288` | `browser_status browser_navigate(browser_state *bs, const char *url)` |
| `browser_push_state` | function | `src/browser.c:320` | `browser_status browser_push_state(browser_state *bs, const char *url)` |
| `browser_replace_state` | function | `src/browser.c:328` | `browser_status browser_replace_state(browser_state *bs, const char *url)` |
| `browser_set_entry_scroll` | function | `src/browser.c:341` | `void browser_set_entry_scroll(browser_state *bs, double scroll)` |
| `browser_set_page` | function | `src/browser.c:507` | `browser_status browser_set_page(browser_state *bs, const char *title,                            ...` |
| `browser_set_status` | function | `src/browser.c:529` | `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)` |
| `browser_set_url_bar` | function | `src/browser.c:220` | `browser_status browser_set_url_bar(browser_state *bs, const char *url)` |
| `browser_status_text` | function | `src/browser.c:543` | `const char *browser_status_text(const browser_state *bs, uint64_t now_ms)` |
| `browser_url_bar_backspace` | function | `src/browser.c:439` | `browser_status browser_url_bar_backspace(browser_state *bs)` |
| `browser_url_bar_clear` | function | `src/browser.c:498` | `browser_status browser_url_bar_clear(browser_state *bs)` |
| `browser_url_bar_delete` | function | `src/browser.c:453` | `browser_status browser_url_bar_delete(browser_state *bs)` |
| `browser_url_bar_delete_selection` | function | `src/browser.c:414` | `int browser_url_bar_delete_selection(browser_state *bs)` |
| `browser_url_bar_extend_cursor` | function | `src/browser.c:474` | `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)` |
| `browser_url_bar_insert` | function | `src/browser.c:424` | `browser_status browser_url_bar_insert(browser_state *bs, char c)` |
| `browser_url_bar_move_cursor` | function | `src/browser.c:464` | `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)` |
| `browser_url_bar_select_all` | function | `src/browser.c:491` | `browser_status browser_url_bar_select_all(browser_state *bs)` |
| `browser_url_bar_selection` | function | `src/browser.c:403` | `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)` |
| `browser_url_bar_set_cursor` | function | `src/browser.c:483` | `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)` |
| `clear_status` | function | `src/browser.c:26` | `static void clear_status(browser_state *bs)` |
| `cp1252_to_ucs` | function | `src/browser.c:129` | `static unsigned int cp1252_to_ucs(unsigned char c)` |
| `free_exceptions` | function | `src/browser.c:83` | `static void free_exceptions(browser_state *bs)` |
| `free_history` | function | `src/browser.c:31` | `static void free_history(browser_state *bs)` |
| `free_page` | function | `src/browser.c:16` | `static void free_page(browser_state *bs)` |
| `free_pending` | function | `src/browser.c:59` | `static void free_pending(browser_state *bs)` |
| `free_stash` | function | `src/browser.c:47` | `static void free_stash(browser_state *bs)` |
| `host_equal` | function | `src/browser.c:551` | `static int host_equal(const char *a, const char *b)` |
| `is_https_url` | function | `src/browser.c:92` | `static int is_https_url(const char *s)` |
| `is_local_path` | function | `src/browser.c:96` | `static int is_local_path(const char *s)` |
| `url_is_allowed` | function | `src/browser.c:101` | `static int url_is_allowed(const char *url)` |
| `utf8_encode` | function | `src/browser.c:143` | `static size_t utf8_encode(unsigned int cp, char *out)` |
| `xstrdup` | function | `src/browser.c:115` | `static char *xstrdup(const char *s)` |
| `_POSIX_C_SOURCE` | macro | `src/cached_fetch.c:7` | `#define _POSIX_C_SOURCE` |
| `cacheable_request` | function | `src/cached_fetch.c:26` | `static int cacheable_request(const sf_config *cfg, const char *url)` |
| `cf_attach_redirect_memory` | function | `src/cached_fetch.c:148` | `void cf_attach_redirect_memory(hc_store *store)` |
| `cf_get` | function | `src/cached_fetch.c:133` | `sf_status cf_get(const char *partition, const char *url, sf_config *cfg, sf_response *out,       ...` |
| `cf_get_with` | function | `src/cached_fetch.c:85` | `sf_status cf_get_with(hc_store *store, cf_fetch_fn fetch, const char *partition, const char *url,...` |
| `cf_set_store` | function | `src/cached_fetch.c:22` | `void cf_set_store(hc_store *store)` |
| `cf_store` | function | `src/cached_fetch.c:23` | `hc_store *cf_store(void)` |
| `copy_val` | function | `src/cached_fetch.c:33` | `static void copy_val(char *dst, size_t cap, const char *src)` |
| `meta_from_response` | function | `src/cached_fetch.c:40` | `static void meta_from_response(hc_meta *m, const sf_response *r, const char *url, time_t now)` |
| `redirect_load` | function | `src/cached_fetch.c:140` | `static int redirect_load(void *ctx, const char *from, time_t now, char *out, size_t cap)` |
| `redirect_save` | function | `src/cached_fetch.c:144` | `static void redirect_save(void *ctx, const char *from, const char *to, time_t now)` |
| `remember` | function | `src/cached_fetch.c:77` | `static void remember(hc_store *store, const char *partition, const char *url,                    ...` |
| `response_from_cache` | function | `src/cached_fetch.c:53` | `static int response_from_cache(sf_response *out, const hc_meta *m, uint8_t *body, size_t len)` |
| `trace` | function | `src/cached_fetch.c:18` | `static void trace(const char *what, const char *url)` |
| `CHL_ID_INSET` | macro | `src/chrome_layout.c:13` | `#define CHL_ID_INSET` |
| `CHL_TAB_CLOSE_INSET` | macro | `src/chrome_layout.c:9` | `#define CHL_TAB_CLOSE_INSET` |
| `CHL_URL_GAP` | macro | `src/chrome_layout.c:11` | `#define CHL_URL_GAP` |
| `CHL_WIDTH_MAX` | macro | `src/chrome_layout.c:15` | `#define CHL_WIDTH_MAX` |
| `chl_compute` | function | `src/chrome_layout.c:30` | `chl_status chl_compute(double width, int csd, int tab_count, int active, chl_layout *out)` |
| `chl_findbar_compute` | function | `src/chrome_layout.c:273` | `chl_status chl_findbar_compute(double width, double height, chl_findbar *out)` |
| `chl_findbar_hit` | function | `src/chrome_layout.c:309` | `chl_find_part chl_findbar_hit(const chl_findbar *f, double x, double y)` |
| `chl_hit` | function | `src/chrome_layout.c:135` | `chl_part chl_hit(const chl_layout *l, double x, double y, int *tab)` |
| `chl_identity_label` | function | `src/chrome_layout.c:256` | `const char *chl_identity_label(chl_identity id)` |
| `chl_identity_of` | function | `src/chrome_layout.c:232` | `chl_identity chl_identity_of(const char *url, int transport_known, int downgrade,                ...` |
| `chl_move_index` | function | `src/chrome_layout.c:179` | `int chl_move_index(int i, int from, int to)` |
| `chl_rect_has` | function | `src/chrome_layout.c:26` | `int chl_rect_has(chl_rect r, double x, double y)` |
| `chl_tab_close_rect` | function | `src/chrome_layout.c:125` | `int chl_tab_close_rect(const chl_layout *l, int i, chl_rect *r)` |
| `chl_tab_drop_index` | function | `src/chrome_layout.c:169` | `int chl_tab_drop_index(const chl_layout *l, double x)` |
| `chl_tab_fallback_title` | function | `src/chrome_layout.c:321` | `void chl_tab_fallback_title(const char *url, char *out, size_t cap)` |
| `chl_tab_for_digit` | function | `src/chrome_layout.c:186` | `int chl_tab_for_digit(int digit, int tab_count)` |
| `chl_tab_rect` | function | `src/chrome_layout.c:115` | `int chl_tab_rect(const chl_layout *l, int i, chl_rect *r)` |
| `has_prefix_ci` | function | `src/chrome_layout.c:197` | `static int has_prefix_ci(const char *s, const char *prefix)` |
| `host_ends_with` | function | `src/chrome_layout.c:204` | `static int host_ends_with(const char *h, size_t n, const char *suffix)` |
| `lower` | function | `src/chrome_layout.c:194` | `static int lower(int c)` |
| `rect` | function | `src/chrome_layout.c:17` | `static chl_rect rect(double x, double y, double w, double h)` |
| `url_host` | function | `src/chrome_layout.c:214` | `static size_t url_host(const char *rest, const char **out)` |
| `cx_box_layer` | function | `src/compositor.c:36` | `cx_layer cx_box_layer(const cx_style *s)` |
| `cx_forms_stacking_context` | function | `src/compositor.c:18` | `int cx_forms_stacking_context(const cx_style *s)` |
| `cx_ink_reach` | function | `src/compositor.c:87` | `double cx_ink_reach(const int (*layers)[6], int n, int outline_w, int outline_offset)` |
| `cx_item_compare` | function | `src/compositor.c:56` | `int cx_item_compare(const cx_item *a, const cx_item *b)` |
| `cx_sort` | function | `src/compositor.c:72` | `void cx_sort(cx_item *items, size_t n)` |
| `cx_span_visible` | function | `src/compositor.c:104` | `int cx_span_visible(double top, double h, double reach, double view_top, double view_h)` |
| `eff_z` | function | `src/compositor.c:52` | `static int eff_z(const cx_item *it)` |
| `AUTO_REJECT` | macro | `src/css.c:285` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css.c:287` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css.c:288` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css.c:286` | `#define AUTO_VALUE` |
| `CSS_ANIM_ITERS_FINITE_MAX` | macro | `src/css.c:333` | `#define CSS_ANIM_ITERS_FINITE_MAX` |
| `CSS_ATTR_MARK` | macro | `src/css.c:2001` | `#define CSS_ATTR_MARK` |
| `CSS_ATTR_SEP` | macro | `src/css.c:2002` | `#define CSS_ATTR_SEP` |
| `CSS_CQ_TEXT_MAX` | macro | `src/css.c:5315` | `#define CSS_CQ_TEXT_MAX` |
| `CSS_DECL_SLOTS_MIN` | macro | `src/css.c:67` | `#define CSS_DECL_SLOTS_MIN` |
| `CSS_INIT_DECLS` | macro | `src/css.c:52` | `#define CSS_INIT_DECLS` |
| `CSS_INIT_RULES` | macro | `src/css.c:68` | `#define CSS_INIT_RULES` |
| `CSS_INIT_SELS` | macro | `src/css.c:51` | `#define CSS_INIT_SELS` |
| `CSS_INLINE_DECLS` | macro | `src/css.c:70` | `#define CSS_INLINE_DECLS` |
| `CSS_MAX_CQ` | macro | `src/css.c:5314` | `#define CSS_MAX_CQ` |
| `CSS_MAX_FONT_FACES` | macro | `src/css.c:172` | `#define CSS_MAX_FONT_FACES` |
| `CSS_MAX_RAW` | macro | `src/css.c:87` | `#define CSS_MAX_RAW` |
| `CSS_MEDIA_MAX_DEPTH` | macro | `src/css.c:5389` | `#define CSS_MEDIA_MAX_DEPTH` |
| `CSS_SELS_PER_GROUP` | macro | `src/css.c:69` | `#define CSS_SELS_PER_GROUP` |
| `CSS_VAR_POOL` | macro | `src/css.c:6762` | `#define CSS_VAR_POOL` |
| `CSS_WIDE_RESET` | macro | `src/css.c:229` | `#define CSS_WIDE_RESET` |
| `LIST` | function | `src/css.c:2933` | `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose...` |
| `NULL` | function | `src/css.c:7184` | `* Sheet can be NULL (inline style, no @keyframes). */ void css_resolve_anim_keyframes(css_style *...` |
| `P_META_CUSTOM` | macro | `src/css.c:83` | `#define P_META_CUSTOM` |
| `P_META_VARSRC` | macro | `src/css.c:84` | `#define P_META_VARSRC` |
| `add_rule` | function | `src/css.c:5064` | `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,                      siz...` |
| `anim_easing_iv` | function | `src/css.c:1496` | `static int anim_easing_iv(const char *tok)` |
| `apply_decl` | function | `src/css.c:6176` | `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_rule` | function | `src/css.c:6793` | `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_var_source` | function | `src/css.c:6766` | `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,         ...` |
| `at_is_media` | function | `src/css.c:5216` | `static int at_is_media(const char *s, size_t i, size_t n)` |
| `at_keyword` | function | `src/css.c:5227` | `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)` |
| `axis` | function | `src/css.c:1828` | `* bare center displaces it to the free axis (`center right` = x:right, y:center).  * Any other co...` |
| `bg_alpha_of` | function | `src/css.c:243` | `static int bg_alpha_of(const char *v)` |
| `bg_to_mask_slot` | function | `src/css.c:755` | `static int bg_to_mask_slot(int prop)` |
| `block_end` | function | `src/css.c:5194` | `static size_t block_end(const char *s, size_t open, size_t n)` |
| `blur` | function | `src/css.c:1791` | `* consumes ONLY blur(Npx);` |
| `box_shadow_layer` | function | `src/css.c:2313` | `static int box_shadow_layer(const char *val, size_t len, int out[6])` |
| `caller` | function | `src/css.c:3871` | `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached...` |
| `cand_cmp` | function | `src/css.c:6701` | `static int cand_cmp(const void *pa, const void *pb)` |
| `cap` | function | `src/css.c:2060` | `* string past the cap (emit_content): a conforming declaration must not * count as a discard just because an icon...` |
| `collect_custom_props_scoped` | function | `src/css.c:5398` | `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,                 ...` |
| `column` | function | `src/css.c:2414` | `* column (`flex: 1 1 0%`);` |
| `computed_font_size` | function | `src/css.c:6684` | `static double computed_font_size(const css_style *o, const css_element *el)` |
| `consumer` | function | `src/css.c:6084` | `* consumer (shorthands, calc(), var() values) gets it with no context          * threaded through...` |
| `content_attr_of` | function | `src/css.c:6167` | `static const char *content_attr_of(const css_element *el, const char *name)` |
| `copy_trim` | function | `src/css.c:2585` | `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `cq_holds` | function | `src/css.c:5341` | `static int cq_holds(const css_sheet *sheet, int id, const cmq_container *scope)` |
| `cq_register` | function | `src/css.c:5319` | `static int cq_register(css_sheet *sh, const char *text, size_t len, int max_w)` |
| `csel_substr` | function | `src/css.c:5249` | `return known && csel_substr(val, "var(", 1);` |
| `css_cand` | struct | `src/css.c:6696` | `` |
| `css_computed_font_size_for_tag` | function | `src/css.c:6676` | `double css_computed_font_size_for_tag(const css_style *o, double inherited_px, const char *tag)` |
| `css_cq` | struct | `src/css.c:141` | `` |
| `css_decl` | function | `src/css.c:91` | `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);` |
| `css_font_face_at` | function | `src/css.c:7220` | `int css_font_face_at(const css_sheet *sheet, size_t i,                      char *family, size_t ...` |
| `css_font_face_count` | function | `src/css.c:7216` | `size_t css_font_face_count(const css_sheet *sheet)` |
| `css_free` | function | `src/css.c:6142` | `void css_free(css_sheet *s)` |
| `css_keyframe_stop` | struct | `src/css.c:151` | `` |
| `css_match` | struct | `src/css.c:6690` | `` |
| `css_parse` | function | `src/css.c:6036` | `css_status css_parse(const char *text, size_t len, css_sheet **out)` |
| `css_parse_inline` | function | `src/css.c:7230` | `css_style css_parse_inline(const char *style, size_t len)` |
| `css_parse_logged` | function | `src/css.c:6050` | `css_status css_parse_logged(const char *text, size_t len, const css_media *media,                ...` |
| `css_parse_media` | function | `src/css.c:6040` | `css_status css_parse_media(const char *text, size_t len, const css_media *media,                 ...` |
| `css_parse_scoped` | function | `src/css.c:6045` | `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,                ...` |
| `css_resolve` | function | `src/css.c:7160` | `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,                   ...` |
| `css_resolve_el` | function | `src/css.c:6862` | `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,                          ...` |
| `css_resolve_el_ex` | function | `src/css.c:6871` | `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,                       ...` |
| `css_resolve_pseudo` | function | `src/css.c:6887` | `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)` |
| `css_rule` | struct | `src/css.c:102` | `` |
| `css_sheet` | struct | `src/css.c:104` | `` |
| `css_sheet_uses_containers` | function | `src/css.c:7234` | `int css_sheet_uses_containers(const css_sheet *sheet)` |
| `css_sheet_uses_counters` | function | `src/css.c:7238` | `int css_sheet_uses_counters(const css_sheet *sheet)` |
| `css_ua_heading_em` | function | `src/css.c:6671` | `double css_ua_heading_em(int level)` |
| `declaration` | function | `src/css.c:2349` | `* invalid layer drops the whole declaration (fail closed). `none` is an explicit  * no-shadow. ur...` |
| `download` | function | `src/css.c:5657` | `* the download (spec/webfont.md b3b). An empty src_url                      * simply never resolv...` |
| `drop_copy_text` | function | `src/css.c:4836` | `static void drop_copy_text(char *dst, size_t cap, const char *src)` |
| `drop_record` | function | `src/css.c:4855` | `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)` |
| `easing_steps` | function | `src/css.c:1474` | `static int easing_steps(const char *tok)` |
| `emit` | function | `src/css.c:64` | `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand...` |
| `emit_content` | function | `src/css.c:1984` | `static int emit_content(css_decl *dst, int cap, const char *str,                         char (*c...` |
| `emit_mask_image` | function | `src/css.c:797` | `static int emit_mask_image(const char *prop, const char *val, css_decl *dst, int cap,            ...` |
| `emit_radius_corner` | function | `src/css.c:1158` | `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)` |
| `emit_spacing` | function | `src/css.c:386` | `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `empty` | function | `src/css.c:2113` | `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and...` |
| `expand_animation` | function | `src/css.c:1529` | `static int expand_animation(const char *val, css_decl *dst, int cap)` |
| `expand_backdrop_filter` | function | `src/css.c:1794` | `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)` |
| `expand_background` | function | `src/css.c:263` | `static int expand_background(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_background_layer` | function | `src/css.c:679` | `static int expand_background_layer(const char *val, css_decl *dst, int cap)` |
| `expand_bg_image` | function | `src/css.c:255` | `static int expand_bg_image(const char *val, css_decl *dst, int cap,                            ch...` |
| `expand_bg_position` | function | `src/css.c:260` | `static int expand_bg_position(const char *val, css_decl *dst, int cap);` |
| `expand_bg_size` | function | `src/css.c:1944` | `static int expand_bg_size(const char *val, css_decl *dst, int cap)` |
| `expand_box2` | function | `src/css.c:300` | `static int expand_box2(const char *val, int slot_start, int slot_end,                        int ...` |
| `expand_box4` | function | `src/css.c:295` | `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,             ...` |
| `expand_clip_path` | function | `src/css.c:3624` | `static int expand_clip_path(const char *val, css_decl *dst, int cap)` |
| `expand_column_rule` | function | `src/css.c:1349` | `static int expand_column_rule(const char *val, css_decl *dst, int cap)` |
| `expand_columns` | function | `src/css.c:1293` | `static int expand_columns(const char *val, css_decl *dst, int cap)` |
| `expand_content` | function | `src/css.c:2109` | `static int expand_content(const char *val, css_decl *dst, int cap,                           char...` |
| `expand_counter_decls` | function | `src/css.c:2091` | `static int expand_counter_decls(const char *prop, const char *val, css_decl *dst, int cap,       ...` |
| `expand_flex` | function | `src/css.c:2435` | `static int expand_flex(const char *val, css_decl *dst, int cap)` |
| `expand_flex_flow` | function | `src/css.c:1327` | `static int expand_flex_flow(const char *val, css_decl *dst, int cap)` |
| `expand_gap` | function | `src/css.c:3521` | `static int expand_gap(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area` | function | `src/css.c:2222` | `static int expand_grid_area(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area_lines` | function | `src/css.c:2188` | `static int expand_grid_area_lines(const char *val, css_decl *dst, int cap)` |
| `expand_grid_areas` | function | `src/css.c:2160` | `static int expand_grid_areas(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_grid_line` | function | `src/css.c:2213` | `static int expand_grid_line(const char *val, css_decl *dst, int cap, int p_start, int p_end)` |
| `expand_grid_template` | function | `src/css.c:2261` | `static int expand_grid_template(const char *val, css_decl *dst, int cap,                         ...` |
| `expand_grid_template_cols` | function | `src/css.c:368` | `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `expand_mask_geometry` | function | `src/css.c:778` | `static int expand_mask_geometry(const char *prop, const char *val, css_decl *dst, int cap)` |
| `expand_outline` | function | `src/css.c:1244` | `static int expand_outline(const char *val, css_decl *dst, int cap)` |
| `expand_shadow` | function | `src/css.c:387` | `static int expand_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_transform_list` | function | `src/css.c:3258` | `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);` |
| `expand_transform_origin` | function | `src/css.c:3489` | `static int expand_transform_origin(const char *val, css_decl *dst, int cap)` |
| `expand_valign` | function | `src/css.c:377` | `static int expand_valign(const char *val, css_decl *dst, int cap)` |
| `filter_paren_body` | function | `src/css.c:1390` | `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)` |
| `first_comma_item` | function | `src/css.c:753` | `static void first_comma_item(const char *val, char *buf, size_t cap);` |
| `fold_font_relative` | function | `src/css.c:6831` | `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,                          ...` |
| `font_list_alias` | function | `src/css.c:3671` | `static void font_list_alias(const css_sheet *sheet, const char *ls, char *out, size_t cap)` |
| `font_list_norm` | function | `src/css.c:3705` | `static int font_list_norm(const char *val, char *out, size_t cap)` |
| `function` | function | `src/css.c:3262` | `* transform function (perspective/rotate3d/...), or unparseable syntax,  * rejects the WHOLE decl...` |
| `has_double_dash` | function | `src/css.c:2645` | `static int has_double_dash(const char *p, size_t n)` |
| `here` | function | `src/css.c:4507` | `* servers have no form here (fail closed). */ int o = csel_ci_eq(val, "none") ? CSS_SVG_PAINT_NONE : interp_color(val);` |
| `idx` | type_alias | `src/css.c:6696` | `typedef struct css_cand { int imp, espec, ord, idx;` |
| `interp_accent_color` | function | `src/css.c:904` | `static int interp_accent_color(const char *v)` |
| `interp_align` | function | `src/css.c:322` | `static int interp_align(const char *v)` |
| `interp_align_kw` | function | `src/css.c:2480` | `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` |
| `interp_appearance` | function | `src/css.c:608` | `static int interp_appearance(const char *v)` |
| `interp_aspect_ratio` | function | `src/css.c:383` | `static int interp_aspect_ratio(const char *v, int *num, int *den)` |
| `interp_backface_visibility` | function | `src/css.c:1067` | `static int interp_backface_visibility(const char *v)` |
| `interp_bc_tok` | function | `src/css.c:1171` | `static int interp_bc_tok(const char *t, int *o)` |
| `interp_bg` | function | `src/css.c:247` | `static int interp_bg(const char *v)` |
| `interp_bg_attachment` | function | `src/css.c:838` | `static int interp_bg_attachment(const char *v)` |
| `interp_bg_clip` | function | `src/css.c:823` | `static int interp_bg_clip(const char *v)` |
| `interp_bg_origin` | function | `src/css.c:831` | `static int interp_bg_origin(const char *v)` |
| `interp_bg_repeat` | function | `src/css.c:638` | `static int interp_bg_repeat(const char *v)` |
| `interp_bg_repeat2` | function | `src/css.c:649` | `static int interp_bg_repeat2(const char *v)` |
| `interp_bg_size` | function | `src/css.c:816` | `static int interp_bg_size(const char *v)` |
| `interp_border_collapse` | function | `src/css.c:516` | `static int interp_border_collapse(const char *v)` |
| `interp_border_color` | function | `src/css.c:1170` | `static int interp_border_color(const char *v)` |
| `interp_border_style` | function | `src/css.c:1090` | `static int interp_border_style(const char *v)` |
| `interp_box_orient` | function | `src/css.c:2522` | `static int interp_box_orient(const char *v)` |
| `interp_boxsizing` | function | `src/css.c:400` | `static int interp_boxsizing(const char *v)` |
| `interp_bs_tok` | function | `src/css.c:1167` | `static int interp_bs_tok(const char *t, int *o)` |
| `interp_bw_tok` | function | `src/css.c:1166` | `static int interp_bw_tok(const char *t, int *o)` |
| `interp_bwidth1` | function | `src/css.c:1116` | `static int interp_bwidth1(const char *v)` |
| `interp_caption_side` | function | `src/css.c:557` | `static int interp_caption_side(const char *v)` |
| `interp_caret_color` | function | `src/css.c:596` | `static int interp_caret_color(const char *v)` |
| `interp_clear` | function | `src/css.c:413` | `static int interp_clear(const char *v)` |
| `interp_color` | function | `src/css.c:203` | `static int interp_color(const char *v)` |
| `interp_color_scheme` | function | `src/css.c:886` | `static int interp_color_scheme(const char *v)` |
| `interp_column_count` | function | `src/css.c:1270` | `static int interp_column_count(const char *v)` |
| `interp_column_width` | function | `src/css.c:1282` | `static int interp_column_width(const char *v)` |
| `interp_contain` | function | `src/css.c:851` | `static int interp_contain(const char *v)` |
| `interp_content_visibility` | function | `src/css.c:872` | `static int interp_content_visibility(const char *v)` |
| `interp_cursor` | function | `src/css.c:462` | `static int interp_cursor(const char *v)` |
| `interp_direction` | function | `src/css.c:384` | `static int interp_direction(const char *v)` |
| `interp_display` | function | `src/css.c:356` | `static int interp_display(const char *v)` |
| `interp_empty_cells` | function | `src/css.c:550` | `static int interp_empty_cells(const char *v)` |
| `interp_filter_deg` | function | `src/css.c:1375` | `static int interp_filter_deg(const char *s)` |
| `interp_filter_pct` | function | `src/css.c:1361` | `static int interp_filter_pct(const char *s)` |
| `interp_flex_basis` | function | `src/css.c:2401` | `static int interp_flex_basis(const char *v, int *out)` |
| `interp_flex_direction` | function | `src/css.c:2504` | `static int interp_flex_direction(const char *v)` |
| `interp_flex_factor` | function | `src/css.c:2391` | `static int interp_flex_factor(const char *v)` |
| `interp_flex_line_pack` | function | `src/css.c:2549` | `static int interp_flex_line_pack(const char *v)` |
| `interp_flex_wrap` | function | `src/css.c:2559` | `static int interp_flex_wrap(const char *v)` |
| `interp_float` | function | `src/css.c:406` | `static int interp_float(const char *v)` |
| `interp_font_kerning` | function | `src/css.c:1002` | `static int interp_font_kerning(const char *v)` |
| `interp_font_stretch` | function | `src/css.c:1017` | `static int interp_font_stretch(const char *v)` |
| `interp_font_variant` | function | `src/css.c:571` | `static int interp_font_variant(const char *v)` |
| `interp_fontfamily` | function | `src/css.c:374` | `static int interp_fontfamily(const char *v)` |
| `interp_fontsize_ex` | function | `src/css.c:326` | `static int interp_fontsize_ex(const char *v, int *abs_out)` |
| `interp_forced_color_adjust` | function | `src/css.c:915` | `static int interp_forced_color_adjust(const char *v)` |
| `interp_gap` | function | `src/css.c:360` | `static int interp_gap(const char *v)` |
| `interp_grid_flow` | function | `src/css.c:2567` | `static int interp_grid_flow(const char *v)` |
| `interp_hyphens` | function | `src/css.c:579` | `static int interp_hyphens(const char *v)` |
| `interp_image_rendering` | function | `src/css.c:879` | `static int interp_image_rendering(const char *v)` |
| `interp_isolation` | function | `src/css.c:845` | `static int interp_isolation(const char *v)` |
| `interp_justify` | function | `src/css.c:364` | `static int interp_justify(const char *v)` |
| `interp_len` | function | `src/css.c:305` | `static int interp_len(const char *v, int allow_auto, int *out)` |
| `interp_lineheight` | function | `src/css.c:340` | `static int interp_lineheight(const char *v)` |
| `interp_list_style_pos` | function | `src/css.c:996` | `static int interp_list_style_pos(const char *v)` |
| `interp_liststyle` | function | `src/css.c:385` | `static int interp_liststyle(const char *v)` |
| `interp_lp` | function | `src/css.c:309` | `static int interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_...` |
| `interp_mix_blend_mode` | function | `src/css.c:922` | `static int interp_mix_blend_mode(const char *v)` |
| `interp_object_fit` | function | `src/css.c:987` | `static int interp_object_fit(const char *v)` |
| `interp_object_pos` | function | `src/css.c:945` | `static int interp_object_pos(const char *v)` |
| `interp_opacity` | function | `src/css.c:376` | `static int interp_opacity(const char *v)` |
| `interp_outline_style` | function | `src/css.c:1239` | `static int interp_outline_style(const char *v)` |
| `interp_overflow` | function | `src/css.c:430` | `static int interp_overflow(const char *v)` |
| `interp_overflow_wrap` | function | `src/css.c:508` | `static int interp_overflow_wrap(const char *v)` |
| `interp_overscroll_behavior` | function | `src/css.c:1060` | `static int interp_overscroll_behavior(const char *v)` |
| `interp_pointer_events` | function | `src/css.c:626` | `static int interp_pointer_events(const char *v)` |
| `interp_position` | function | `src/css.c:391` | `static int interp_position(const char *v)` |
| `interp_print_color_adjust` | function | `src/css.c:909` | `static int interp_print_color_adjust(const char *v)` |
| `interp_resize` | function | `src/css.c:1030` | `static int interp_resize(const char *v)` |
| `interp_scroll_behavior` | function | `src/css.c:1038` | `static int interp_scroll_behavior(const char *v)` |
| `interp_style` | function | `src/css.c:348` | `static int interp_style(const char *v)` |
| `interp_table_layout` | function | `src/css.c:564` | `static int interp_table_layout(const char *v)` |
| `interp_tabsize` | function | `src/css.c:380` | `static int interp_tabsize(const char *v)` |
| `interp_text_overflow` | function | `src/css.c:494` | `static int interp_text_overflow(const char *v)` |
| `interp_text_rendering` | function | `src/css.c:1009` | `static int interp_text_rendering(const char *v)` |
| `interp_textdeco` | function | `src/css.c:352` | `static int interp_textdeco(const char *v)` |
| `interp_textdeco_style` | function | `src/css.c:381` | `static int interp_textdeco_style(const char *v)` |
| `interp_textdeco_thickness` | function | `src/css.c:382` | `static int interp_textdeco_thickness(const char *v)` |
| `interp_texttransform` | function | `src/css.c:375` | `static int interp_texttransform(const char *v)` |
| `interp_time_ms` | function | `src/css.c:1125` | `static int interp_time_ms(const char *v)` |
| `interp_transition_property` | function | `src/css.c:378` | `static int interp_transition_property(const char *v)` |
| `interp_user_select` | function | `src/css.c:587` | `static int interp_user_select(const char *v)` |
| `interp_visibility` | function | `src/css.c:423` | `static int interp_visibility(const char *v)` |
| `interp_weight` | function | `src/css.c:344` | `static int interp_weight(const char *v)` |
| `interp_whitespace` | function | `src/css.c:379` | `static int interp_whitespace(const char *v)` |
| `interp_word_break` | function | `src/css.c:500` | `static int interp_word_break(const char *v)` |
| `interpret_decls` | function | `src/css.c:5000` | `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,                ...` |
| `interpret_prop` | function | `src/css.c:4807` | `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,             ...` |
| `interpret_prop_dispatch` | function | `src/css.c:3964` | `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,    ...` |
| `is_anim_ident` | function | `src/css.c:1513` | `static int is_anim_ident(const char *tok)` |
| `is_inert_prop` | function | `src/css.c:3941` | `static int is_inert_prop(const char *prop)` |
| `item` | function | `src/css.c:1403` | `* timing list takes its first item (CSS Animations/Transitions 1: with one  * transition/animatio...` |
| `layer` | function | `src/css.c:670` | `* first layer (the one painted) -- so `background: url(x) no-repeat` stops tiling  * and a later ...` |
| `layer_register` | function | `src/css.c:5355` | `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,                      ...` |
| `len_rebase` | function | `src/css.c:5867` | `static char *len_rebase(const char *s, size_t n, const len_rebase_ctx *c, size_t *outlen)` |
| `len_rebase_ctx` | struct | `src/css.c:5825` | `` |
| `len_unit_px` | function | `src/css.c:5837` | `static double len_unit_px(const char *u, size_t len, const len_rebase_ctx *c)` |
| `lp_can_be_nonneg` | function | `src/css.c:314` | `static int lp_can_be_nonneg(int px_val, int pct_pm)` |
| `matrix` | function | `src/css.c:2844` | `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands...` |
| `multiplying` | function | `src/css.c:3888` | `* instead of the two multiplying (no page measured needs both on one element).  * A third (z) com...` |
| `next_ws_token` | function | `src/css.c:318` | `static int next_ws_token(const char **p, char *tok, size_t cap)` |
| `number` | function | `src/css.c:525` | `* number (no unit) as px (common in shorthand context like "10 5"). */ static int interp_border_s...` |
| `order` | function | `src/css.c:1755` | `* declaration order (dx, dy, optional blur >= 0);` |
| `origin_component` | function | `src/css.c:3463` | `static int origin_component(const char *tok, int axis, int *out)` |
| `page_view` | function | `src/css.c:6183` | `* the generated text reaches page_view (which materialises it as a synthetic * run);` |
| `parent` | function | `src/css.c:6216` | `* property from the parent (`inherit`), and an unset non-inherited one          * stands at its i...` |
| `parse_angle_deg` | function | `src/css.c:3255` | `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);` |
| `parse_block` | function | `src/css.c:5480` | `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,                  ...` |
| `parse_color` | function | `src/css.c:199` | `static int parse_color(const char *v)` |
| `parse_matrix6` | function | `src/css.c:2897` | `static int parse_matrix6(const char *p, size_t argn, double m6[6])` |
| `parse_num` | function | `src/css.c:188` | `static int parse_num(const char *s, double *out, const char **endp)` |
| `parse_numlist` | function | `src/css.c:2874` | `static int parse_numlist(const char *p, size_t argn, double *m6, int count)` |
| `property` | function | `src/css.c:3580` | `* error drops the whole property (fail closed). */ static int expand_clip(const char *val, css_de...` |
| `pseudo_of` | function | `src/css.c:6878` | `static int pseudo_of(int which)` |
| `raw_add` | function | `src/css.c:4881` | `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)` |
| `rem_emit_px` | function | `src/css.c:5807` | `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)` |
| `rem_ident_ch` | function | `src/css.c:5789` | `static int rem_ident_ch(char c)` |
| `rem_num_starts_after` | function | `src/css.c:5797` | `static int rem_num_starts_after(char prev)` |
| `rem_px` | type_alias | `src/css.c:5825` | `typedef struct len_rebase_ctx { double rem_px;` |
| `rem_rebase` | function | `src/css.c:5933` | `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)` |
| `remap_to_mask` | function | `src/css.c:769` | `static int remap_to_mask(css_decl *dst, int n)` |
| `resolve_core` | function | `src/css.c:6898` | `static css_style resolve_core(const css_sheet *sheet, const css_element *el,                     ...` |
| `sel_list_comma` | function | `src/css.c:2306` | `static size_t sel_list_comma(const char *s, size_t i, size_t end);` |
| `selector_matches_root` | function | `src/css.c:2702` | `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m,          ...` |
| `sentinel` | function | `src/css.c:4294` | `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);` |
| `sheet_index` | function | `src/css.c:5941` | `static void sheet_index(css_sheet *sh)` |
| `sheet_pools_reserve` | function | `src/css.c:5058` | `static void sheet_pools_reserve(css_sheet *sh)` |
| `sheet_rewind` | function | `src/css.c:5946` | `static void sheet_rewind(css_sheet *sh)` |
| `sheet_root_font_px` | function | `src/css.c:5993` | `static double sheet_root_font_px(const css_sheet *sh)` |
| `shorthand` | function | `src/css.c:3545` | `* An uninterpretable token drops the whole shorthand (fail closed). */ static int expand_place(co...` |
| `shorthand` | function | `src/css.c:3791` | `* generic bucket keeps the rest of the shorthand (same net effect as the  * font-family longhand ...` |
| `skip_at_rule` | function | `src/css.c:5178` | `static size_t skip_at_rule(const char *s, size_t i, size_t n)` |
| `slots` | function | `src/css.c:4154` | `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return...` |
| `split_top_args` | function | `src/css.c:2910` | `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,                ...` |
| `strip_comments` | function | `src/css.c:6001` | `static char *strip_comments(const char *text, size_t len, size_t *outlen)` |
| `strip_important` | function | `src/css.c:2598` | `static int strip_important(char *val)` |
| `subject_may_be_root` | function | `src/css.c:2654` | `static int subject_may_be_root(const char *s, size_t a, size_t b, const char *root_scope)` |
| `supports_matches` | function | `src/css.c:5261` | `static int supports_matches(const char *s, size_t a, size_t b)` |
| `supports_selector_ok` | function | `src/css.c:5252` | `static int supports_selector_ok(void *ctx, const char *sel)` |
| `text` | function | `src/css.c:275` | `* source text (rem_rebase, see below) rather than by threading a context here.  *  * Viewport uni...` |
| `through` | function | `src/css.c:219` | `* at the two SHARED chokepoints every property funnels through (the generic  * dispatch tail, and...` |
| `tr_decompose` | function | `src/css.c:2851` | `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,                         in...` |
| `tr_mul` | function | `src/css.c:2831` | `static void tr_mul(double out[6], const double l[6], const double r[6])` |
| `translate3d` | function | `src/css.c:2940` | `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine  * renders z as nothing,...` |
| `translateX` | function | `src/css.c:3251` | `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc...` |
| `translateZ` | function | `src/css.c:3260` | `* translateZ(), rotateX(0) and rotateY(0) emit the identity (with the stacking * context Firefox builds);` |
| `var` | function | `src/css.c:2623` | `* cvr_resolve then substitutes var() references when a declaration's value is  * interpreted (par...` |
| `var` | function | `src/css.c:6011` | `* collected and forty var() declarations -- font sizes, widths, radii, the      * whole theme -- ...` |
| `wide_claim` | function | `src/css.c:4767` | `static int wide_claim(const char *prop, css_decl *dst, int cap,                       char (*urlt...` |
| `writing` | function | `src/css.c:3749` | `* Wide keywords claim BOTH slots without writing (inheritance then flows, as  * the tail does for...` |
| `CAR_TEXT_MAX` | macro | `src/css_atrule.c:13` | `#define CAR_TEXT_MAX` |
| `car_effective_spec` | function | `src/css_atrule.c:171` | `int car_effective_spec(int spec, int layer, int important)` |
| `car_layer_rank` | function | `src/css_atrule.c:148` | `int car_layer_rank(car_layers *L, const char *name, size_t len)` |
| `car_supports` | function | `src/css_atrule.c:141` | `int car_supports(const char *s, size_t a, size_t b, const car_ops *ops)` |
| `close_paren` | function | `src/css_atrule.c:33` | `static size_t close_paren(const char *s, size_t open, size_t b)` |
| `copy_trimmed` | function | `src/css_atrule.c:54` | `static int copy_trimmed(const char *s, size_t a, size_t b, char *dst, size_t cap, int lower)` |
| `eval_condition` | function | `src/css_atrule.c:114` | `static int eval_condition(const char *s, size_t a, size_t b, const car_ops *ops,                 ...` |
| `eval_declaration` | function | `src/css_atrule.c:68` | `static int eval_declaration(const char *s, size_t a, size_t b, const car_ops *ops, int *ok)` |
| `eval_in_parens` | function | `src/css_atrule.c:85` | `static int eval_in_parens(const char *s, size_t *i, size_t b, const car_ops *ops,                ...` |
| `keyword_at` | function | `src/css_atrule.c:23` | `static int keyword_at(const char *s, size_t i, size_t b, const char *kw)` |
| `skip_ws` | function | `src/css_atrule.c:17` | `static size_t skip_ws(const char *s, size_t i, size_t b)` |
| `AUTO_REJECT` | macro | `src/css_box.c:1248` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css_box.c:1250` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css_box.c:1254` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css_box.c:1249` | `#define AUTO_VALUE` |
| `CSS_CALC_MAX_DEPTH` | macro | `src/css_box.c:714` | `#define CSS_CALC_MAX_DEPTH` |
| `CSS_MATHFN_MAX_ARGS` | macro | `src/css_box.c:718` | `#define CSS_MATHFN_MAX_ARGS` |
| `RELATIVE` | function | `src/css_box.c:63` | `* or RELATIVE (of the inherited size). Absolute: px/pt/rem/viewport units and the * absolute keywords. Relative: em...` |
| `accepts` | function | `src/css_box.c:706` | `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further...` |
| `calc_eval_em` | function | `src/css_box.c:974` | `static int calc_eval_em(const char *v, size_t vlen, double *out_em)` |
| `calc_eval_full` | function | `src/css_box.c:960` | `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,            ...` |
| `calc_expr` | function | `src/css_box.c:938` | `static int calc_expr(calc_parser *p, calc_val *out, int depth)` |
| `calc_match_fn` | function | `src/css_box.c:746` | `static int calc_match_fn(calc_parser *p, const char *name)` |
| `calc_mathfn` | function | `src/css_box.c:788` | `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` |
| `calc_parser` | struct | `src/css_box.c:737` | `` |
| `calc_piecewise` | function | `src/css_box.c:773` | `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)` |
| `calc_skip_ws` | function | `src/css_box.c:739` | `static void calc_skip_ws(calc_parser *p)` |
| `calc_term` | function | `src/css_box.c:911` | `static int calc_term(calc_parser *p, calc_val *out, int depth)` |
| `calc_unwrap` | function | `src/css_box.c:982` | `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` |
| `calc_val` | struct | `src/css_box.c:736` | `` |
| `cb_clip_inset` | function | `src/css_box.c:1141` | `int cb_clip_inset(const char *val, int px[4], int pm[4])` |
| `cb_copy_trim` | function | `src/css_box.c:25` | `static size_t cb_copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `cb_expand_box2` | function | `src/css_box.c:1422` | `int cb_expand_box2(const char *val, int slot_start, int slot_end,                        int allo...` |
| `cb_expand_grid_template_cols` | function | `src/css_box.c:623` | `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `cb_expand_grid_template_rows` | function | `src/css_box.c:646` | `int cb_expand_grid_template_rows(const char *val, css_decl *dst, int cap)` |
| `cb_interp_align` | function | `src/css_box.c:54` | `int cb_interp_align(const char *v)` |
| `cb_interp_display` | function | `src/css_box.c:233` | `int cb_interp_display(const char *v)` |
| `cb_interp_fontsize_ex` | function | `src/css_box.c:72` | `int cb_interp_fontsize_ex(const char *v, int *abs_out)` |
| `cb_interp_gap` | function | `src/css_box.c:313` | `int cb_interp_gap(const char *v)` |
| `cb_interp_justify` | function | `src/css_box.c:320` | `int cb_interp_justify(const char *v)` |
| `cb_interp_len` | function | `src/css_box.c:1042` | `int cb_interp_len(const char *v, int allow_auto, int *out)` |
| `cb_interp_lineheight` | function | `src/css_box.c:145` | `int cb_interp_lineheight(const char *v)` |
| `cb_interp_lp` | function | `src/css_box.c:1175` | `int cb_interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_px, ...` |
| `cb_interp_style` | function | `src/css_box.c:203` | `int cb_interp_style(const char *v)` |
| `cb_interp_textdeco` | function | `src/css_box.c:213` | `int cb_interp_textdeco(const char *v)` |
| `cb_interp_weight` | function | `src/css_box.c:194` | `int cb_interp_weight(const char *v)` |
| `cb_length_px` | function | `src/css_box.c:49` | `int cb_length_px(const char *v, double *px)` |
| `cb_math_length_px` | function | `src/css_box.c:1033` | `int cb_math_length_px(const char *v, double *px)` |
| `cb_parse_num` | function | `src/css_box.c:13` | `static int cb_parse_num(const char *s, double *out, const char **endp)` |
| `cb_starts_with_ci` | function | `src/css_box.c:352` | `static int cb_starts_with_ci(const char *s, const char *pre)` |
| `cb_value_em_milli` | function | `src/css_box.c:1121` | `int cb_value_em_milli(const char *v)` |
| `cb_wide_keyword` | function | `src/css_box.c:18` | `static int cb_wide_keyword(const char *v)` |
| `count_one_repeat` | function | `src/css_box.c:396` | `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,                       ...` |
| `count_tracks` | function | `src/css_box.c:358` | `static int count_tracks(const char *s, size_t n)` |
| `expand_auto_fill` | function | `src/css_box.c:545` | `static int expand_auto_fill(const char *val, css_decl *dst, int cap)` |
| `interp_len` | function | `src/css_box.c:1351` | `* this file that might hand a token to interp_len (transitively: margin/padding/  * inset, flex-b...` |
| `min` | function | `src/css_box.c:807` | `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the...` |
| `pct_slot_of` | function | `src/css_box.c:1071` | `static int pct_slot_of(int slot)` |
| `px` | type_alias | `src/css_box.c:736` | `typedef struct calc_val { double px;` |
| `repeat` | function | `src/css_box.c:341` | `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill\|...) /...` |
| `term` | function | `src/css_box.c:1182` | `* the same expression and failed closed on the percentage term (its property * may not accept one);` |
| `track_min_of` | function | `src/css_box.c:507` | `static int track_min_of(const char *tok)` |
| `track_size_of` | function | `src/css_box.c:366` | `static int track_size_of(const char *tok)` |
| `walk_tracks` | function | `src/css_box.c:439` | `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)` |
| `CCH_ATTR_BUF` | macro | `src/css_chain.c:23` | `#define CCH_ATTR_BUF` |
| `CCH_CLASS_BUF` | macro | `src/css_chain.c:17` | `#define CCH_CLASS_BUF` |

Next: [SYMBOLS_p8.md](SYMBOLS_p8.md)
