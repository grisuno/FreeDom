# Symbols (page 6 of 17)
Previous: [SYMBOLS_p5.md](SYMBOLS_p5.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `disp_row` | struct | `src/box_style.c:241` | `` |
| `is_ws` | function | `src/box_style.c:31` | `static int is_ws(char c)` |
| `name_cmp` | function | `src/box_style.c:50` | `static int name_cmp(const void *key, const void *elem)` |
| `tag_row` | struct | `src/box_style.c:61` | `` |
| `take` | function | `src/box_style.c:295` | `* caller has to take (Sizing 3 section 5.1), so to a resolver that only sums a * px and a percentage half they read...` |
| `BT_LEN_AUTO` | macro | `src/box_tree.c:31` | `#define BT_LEN_AUTO` |
| `BT_WRAP_EPS` | macro | `src/box_tree.c:62` | `#define BT_WRAP_EPS` |
| `assign_doc_order` | function | `src/box_tree.c:505` | `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,                   ...` |
| `block` | function | `src/box_tree.c:566` | `* true block (same flow neighbourhood), strictly better than zeros. NULL      * placed keeps lega...` |
| `bt_box_hidden` | function | `src/box_tree.c:776` | `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)` |
| `bt_containing_block` | function | `src/box_tree.c:555` | `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i,                         ...` |
| `bt_defer_roots` | function | `src/box_tree.c:808` | `size_t bt_defer_roots(const pv_box_def *boxes, size_t nbox,                       const bt_positi...` |
| `bt_in_subtree` | function | `src/box_tree.c:789` | `int bt_in_subtree(const pv_box_def *boxes, size_t nbox, size_t root, size_t bid)` |
| `bt_layout` | function | `src/box_tree.c:465` | `bt_status bt_layout(bt_node *root, double avail_w)` |
| `bt_nn` | function | `src/box_tree.c:58` | `static double bt_nn(double v)` |
| `bt_oof_anchor` | function | `src/box_tree.c:768` | `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)` |
| `bt_oof_avail` | function | `src/box_tree.c:800` | `double bt_oof_avail(int a, int a_pct, int b, int b_pct, double cb, int *both)` |
| `bt_oof_root` | function | `src/box_tree.c:772` | `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)` |
| `bt_resolve_positioning` | function | `src/box_tree.c:585` | `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,                           ...` |
| `bt_resolve_positioning_ex` | function | `src/box_tree.c:596` | `bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,                        ...` |
| `find_positioned_ancestor` | function | `src/box_tree.c:522` | `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,                        ...` |
| `height` | function | `src/box_tree.c:78` | `* exactly that height (Flexbox 9.4 step 15).  *  * wrap_reverse (node->wrap_reverse): when node->...` |
| `inset_unset` | function | `src/box_tree.c:551` | `static int inset_unset(int v, int pct_pm)` |
| `layout_block` | function | `src/box_tree.c:37` | `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,                    ...` |
| `layout_flex` | function | `src/box_tree.c:98` | `static bt_status layout_flex(bt_node *node, bt_node *const *kids, size_t nk,                     ...` |
| `layout_grid` | function | `src/box_tree.c:280` | `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,                     ...` |
| `layout_node` | function | `src/box_tree.c:420` | `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)` |
| `oof_walk` | function | `src/box_tree.c:751` | `static int oof_walk(const pv_box_def *boxes, size_t nbox, int bid, int nearest)` |
| `resolve_inset` | function | `src/box_tree.c:542` | `static double resolve_inset(int v, int pct_pm, double basis)` |
| `sized` | function | `src/box_tree.c:350` | `* the tracks are sized (CSS Grid 1 11.5, items spanning several tracks come * last);` |
| `_POSIX_C_SOURCE` | macro | `src/browser.c:7` | `#define _POSIX_C_SOURCE` |
| `browser_add_exception` | function | `src/browser.c:472` | `browser_status browser_add_exception(browser_state *bs, const char *host)` |
| `browser_back` | function | `src/browser.c:268` | `browser_status browser_back(browser_state *bs)` |
| `browser_can_back` | function | `src/browser.c:292` | `int browser_can_back(const browser_state *bs)` |
| `browser_can_forward` | function | `src/browser.c:296` | `int browser_can_forward(const browser_state *bs)` |
| `browser_commit_url_bar` | function | `src/browser.c:190` | `browser_status browser_commit_url_bar(browser_state *bs)` |
| `browser_current_url` | function | `src/browser.c:300` | `const char *browser_current_url(const browser_state *bs)` |
| `browser_doc_index` | function | `src/browser.c:260` | `int browser_doc_index(const browser_state *bs)` |
| `browser_entry_doc` | function | `src/browser.c:255` | `int browser_entry_doc(const browser_state *bs, size_t pos)` |
| `browser_forward` | function | `src/browser.c:280` | `browser_status browser_forward(browser_state *bs)` |
| `browser_free` | function | `src/browser.c:167` | `void browser_free(browser_state *bs)` |
| `browser_init` | function | `src/browser.c:156` | `browser_status browser_init(browser_state *bs)` |
| `browser_is_exception` | function | `src/browser.c:464` | `int browser_is_exception(const browser_state *bs, const char *host)` |
| `browser_navigate` | function | `src/browser.c:224` | `browser_status browser_navigate(browser_state *bs, const char *url)` |
| `browser_push_state` | function | `src/browser.c:236` | `browser_status browser_push_state(browser_state *bs, const char *url)` |
| `browser_replace_state` | function | `src/browser.c:243` | `browser_status browser_replace_state(browser_state *bs, const char *url)` |
| `browser_set_page` | function | `src/browser.c:409` | `browser_status browser_set_page(browser_state *bs, const char *title,                            ...` |
| `browser_set_status` | function | `src/browser.c:431` | `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)` |
| `browser_set_url_bar` | function | `src/browser.c:178` | `browser_status browser_set_url_bar(browser_state *bs, const char *url)` |
| `browser_status_text` | function | `src/browser.c:445` | `const char *browser_status_text(const browser_state *bs, uint64_t now_ms)` |
| `browser_url_bar_backspace` | function | `src/browser.c:341` | `browser_status browser_url_bar_backspace(browser_state *bs)` |
| `browser_url_bar_clear` | function | `src/browser.c:400` | `browser_status browser_url_bar_clear(browser_state *bs)` |
| `browser_url_bar_delete` | function | `src/browser.c:355` | `browser_status browser_url_bar_delete(browser_state *bs)` |
| `browser_url_bar_delete_selection` | function | `src/browser.c:316` | `int browser_url_bar_delete_selection(browser_state *bs)` |
| `browser_url_bar_extend_cursor` | function | `src/browser.c:376` | `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)` |
| `browser_url_bar_insert` | function | `src/browser.c:326` | `browser_status browser_url_bar_insert(browser_state *bs, char c)` |
| `browser_url_bar_move_cursor` | function | `src/browser.c:366` | `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)` |
| `browser_url_bar_select_all` | function | `src/browser.c:393` | `browser_status browser_url_bar_select_all(browser_state *bs)` |
| `browser_url_bar_selection` | function | `src/browser.c:305` | `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)` |
| `browser_url_bar_set_cursor` | function | `src/browser.c:385` | `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)` |
| `clear_status` | function | `src/browser.c:25` | `static void clear_status(browser_state *bs)` |
| `cp1252_to_ucs` | function | `src/browser.c:88` | `static unsigned int cp1252_to_ucs(unsigned char c)` |
| `free_exceptions` | function | `src/browser.c:42` | `static void free_exceptions(browser_state *bs)` |
| `free_history` | function | `src/browser.c:30` | `static void free_history(browser_state *bs)` |
| `free_page` | function | `src/browser.c:15` | `static void free_page(browser_state *bs)` |
| `host_equal` | function | `src/browser.c:453` | `static int host_equal(const char *a, const char *b)` |
| `is_https_url` | function | `src/browser.c:51` | `static int is_https_url(const char *s)` |
| `is_local_path` | function | `src/browser.c:55` | `static int is_local_path(const char *s)` |
| `url_is_allowed` | function | `src/browser.c:60` | `static int url_is_allowed(const char *url)` |
| `utf8_encode` | function | `src/browser.c:102` | `static size_t utf8_encode(unsigned int cp, char *out)` |
| `xstrdup` | function | `src/browser.c:74` | `static char *xstrdup(const char *s)` |
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
| `cx_box_layer` | function | `src/compositor.c:34` | `cx_layer cx_box_layer(const cx_style *s)` |
| `cx_forms_stacking_context` | function | `src/compositor.c:16` | `int cx_forms_stacking_context(const cx_style *s)` |
| `cx_item_compare` | function | `src/compositor.c:54` | `int cx_item_compare(const cx_item *a, const cx_item *b)` |
| `cx_sort` | function | `src/compositor.c:70` | `void cx_sort(cx_item *items, size_t n)` |
| `eff_z` | function | `src/compositor.c:50` | `static int eff_z(const cx_item *it)` |
| `AUTO_REJECT` | macro | `src/css.c:278` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css.c:280` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css.c:281` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css.c:279` | `#define AUTO_VALUE` |
| `CSS_ANIM_ITERS_FINITE_MAX` | macro | `src/css.c:326` | `#define CSS_ANIM_ITERS_FINITE_MAX` |
| `CSS_ATTR_MARK` | macro | `src/css.c:1990` | `#define CSS_ATTR_MARK` |
| `CSS_ATTR_SEP` | macro | `src/css.c:1991` | `#define CSS_ATTR_SEP` |
| `CSS_DECL_SLOTS_MIN` | macro | `src/css.c:67` | `#define CSS_DECL_SLOTS_MIN` |
| `CSS_INIT_DECLS` | macro | `src/css.c:52` | `#define CSS_INIT_DECLS` |
| `CSS_INIT_RULES` | macro | `src/css.c:68` | `#define CSS_INIT_RULES` |
| `CSS_INIT_SELS` | macro | `src/css.c:51` | `#define CSS_INIT_SELS` |
| `CSS_INLINE_DECLS` | macro | `src/css.c:70` | `#define CSS_INLINE_DECLS` |
| `CSS_MAX_FONT_FACES` | macro | `src/css.c:165` | `#define CSS_MAX_FONT_FACES` |
| `CSS_MAX_RAW` | macro | `src/css.c:87` | `#define CSS_MAX_RAW` |
| `CSS_MEDIA_MAX_DEPTH` | macro | `src/css.c:5304` | `#define CSS_MEDIA_MAX_DEPTH` |
| `CSS_SELS_PER_GROUP` | macro | `src/css.c:69` | `#define CSS_SELS_PER_GROUP` |
| `CSS_VAR_POOL` | macro | `src/css.c:6660` | `#define CSS_VAR_POOL` |
| `CSS_WIDE_RESET` | macro | `src/css.c:222` | `#define CSS_WIDE_RESET` |
| `LIST` | function | `src/css.c:2922` | `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose...` |
| `NULL` | function | `src/css.c:7081` | `* Sheet can be NULL (inline style, no @keyframes). */ void css_resolve_anim_keyframes(css_style *...` |
| `P_META_CUSTOM` | macro | `src/css.c:83` | `#define P_META_CUSTOM` |
| `P_META_VARSRC` | macro | `src/css.c:84` | `#define P_META_VARSRC` |
| `add_rule` | function | `src/css.c:5020` | `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,                      siz...` |
| `anim_easing_iv` | function | `src/css.c:1486` | `static int anim_easing_iv(const char *tok)` |
| `apply_decl` | function | `src/css.c:6077` | `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_rule` | function | `src/css.c:6691` | `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_var_source` | function | `src/css.c:6664` | `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,         ...` |
| `at_is_media` | function | `src/css.c:5171` | `static int at_is_media(const char *s, size_t i, size_t n)` |
| `at_keyword` | function | `src/css.c:5182` | `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)` |
| `axis` | function | `src/css.c:1817` | `* bare center displaces it to the free axis (`center right` = x:right, y:center).  * Any other co...` |
| `bg_alpha_of` | function | `src/css.c:236` | `static int bg_alpha_of(const char *v)` |
| `bg_to_mask_slot` | function | `src/css.c:748` | `static int bg_to_mask_slot(int prop)` |
| `block_end` | function | `src/css.c:5149` | `static size_t block_end(const char *s, size_t open, size_t n)` |
| `blur` | function | `src/css.c:1780` | `* consumes ONLY blur(Npx);` |
| `box_shadow_layer` | function | `src/css.c:2302` | `static int box_shadow_layer(const char *val, size_t len, int out[6])` |
| `caller` | function | `src/css.c:3860` | `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached...` |
| `cand_cmp` | function | `src/css.c:6599` | `static int cand_cmp(const void *pa, const void *pb)` |
| `cap` | function | `src/css.c:2049` | `* string past the cap (emit_content): a conforming declaration must not * count as a discard just because an icon...` |
| `collect_custom_props_scoped` | function | `src/css.c:5313` | `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,                 ...` |
| `column` | function | `src/css.c:2403` | `* column (`flex: 1 1 0%`);` |
| `computed_font_size` | function | `src/css.c:6582` | `static double computed_font_size(const css_style *o, const css_element *el)` |
| `consumer` | function | `src/css.c:5987` | `* consumer (shorthands, calc(), var() values) gets it with no context          * threaded through...` |
| `content_attr_of` | function | `src/css.c:6068` | `static const char *content_attr_of(const css_element *el, const char *name)` |
| `copy_trim` | function | `src/css.c:2574` | `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `csel_substr` | function | `src/css.c:5204` | `return known && csel_substr(val, "var(", 1);` |
| `css_cand` | struct | `src/css.c:6594` | `` |
| `css_computed_font_size_for_tag` | function | `src/css.c:6574` | `double css_computed_font_size_for_tag(const css_style *o, double inherited_px, const char *tag)` |
| `css_decl` | function | `src/css.c:91` | `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);` |
| `css_font_face_at` | function | `src/css.c:7117` | `int css_font_face_at(const css_sheet *sheet, size_t i,                      char *family, size_t ...` |
| `css_font_face_count` | function | `src/css.c:7113` | `size_t css_font_face_count(const css_sheet *sheet)` |
| `css_free` | function | `src/css.c:6045` | `void css_free(css_sheet *s)` |
| `css_keyframe_stop` | struct | `src/css.c:144` | `` |
| `css_match` | struct | `src/css.c:6588` | `` |
| `css_parse` | function | `src/css.c:5939` | `css_status css_parse(const char *text, size_t len, css_sheet **out)` |
| `css_parse_inline` | function | `src/css.c:7127` | `css_style css_parse_inline(const char *style, size_t len)` |
| `css_parse_logged` | function | `src/css.c:5953` | `css_status css_parse_logged(const char *text, size_t len, const css_media *media,                ...` |
| `css_parse_media` | function | `src/css.c:5943` | `css_status css_parse_media(const char *text, size_t len, const css_media *media,                 ...` |
| `css_parse_scoped` | function | `src/css.c:5948` | `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,                ...` |
| `css_resolve` | function | `src/css.c:7057` | `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,                   ...` |
| `css_resolve_el` | function | `src/css.c:6760` | `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,                          ...` |
| `css_resolve_el_ex` | function | `src/css.c:6769` | `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,                       ...` |
| `css_resolve_pseudo` | function | `src/css.c:6785` | `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)` |
| `css_rule` | struct | `src/css.c:102` | `` |
| `css_sheet` | struct | `src/css.c:104` | `` |
| `css_sheet_uses_counters` | function | `src/css.c:7131` | `int css_sheet_uses_counters(const css_sheet *sheet)` |
| `css_ua_heading_em` | function | `src/css.c:6569` | `double css_ua_heading_em(int level)` |
| `declaration` | function | `src/css.c:2338` | `* invalid layer drops the whole declaration (fail closed). `none` is an explicit  * no-shadow. ur...` |
| `download` | function | `src/css.c:5562` | `* the download (spec/webfont.md b3b). An empty src_url                      * simply never resolv...` |
| `drop_copy_text` | function | `src/css.c:4792` | `static void drop_copy_text(char *dst, size_t cap, const char *src)` |
| `drop_record` | function | `src/css.c:4811` | `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)` |
| `easing_steps` | function | `src/css.c:1464` | `static int easing_steps(const char *tok)` |
| `emit` | function | `src/css.c:64` | `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand...` |
| `emit_content` | function | `src/css.c:1973` | `static int emit_content(css_decl *dst, int cap, const char *str,                         char (*c...` |
| `emit_mask_image` | function | `src/css.c:790` | `static int emit_mask_image(const char *prop, const char *val, css_decl *dst, int cap,            ...` |
| `emit_radius_corner` | function | `src/css.c:1151` | `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)` |
| `emit_spacing` | function | `src/css.c:379` | `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `empty` | function | `src/css.c:2102` | `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and...` |
| `evaluated` | function | `src/css.c:3938` | `* queries that read it are evaluated (or not) on their own (cmq_container_surely);` |
| `expand_animation` | function | `src/css.c:1519` | `static int expand_animation(const char *val, css_decl *dst, int cap)` |
| `expand_backdrop_filter` | function | `src/css.c:1783` | `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)` |
| `expand_background` | function | `src/css.c:256` | `static int expand_background(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_background_layer` | function | `src/css.c:672` | `static int expand_background_layer(const char *val, css_decl *dst, int cap)` |
| `expand_bg_image` | function | `src/css.c:248` | `static int expand_bg_image(const char *val, css_decl *dst, int cap,                            ch...` |
| `expand_bg_position` | function | `src/css.c:253` | `static int expand_bg_position(const char *val, css_decl *dst, int cap);` |
| `expand_bg_size` | function | `src/css.c:1933` | `static int expand_bg_size(const char *val, css_decl *dst, int cap)` |
| `expand_box2` | function | `src/css.c:293` | `static int expand_box2(const char *val, int slot_start, int slot_end,                        int ...` |
| `expand_box4` | function | `src/css.c:288` | `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,             ...` |
| `expand_clip_path` | function | `src/css.c:3613` | `static int expand_clip_path(const char *val, css_decl *dst, int cap)` |
| `expand_column_rule` | function | `src/css.c:1339` | `static int expand_column_rule(const char *val, css_decl *dst, int cap)` |
| `expand_columns` | function | `src/css.c:1283` | `static int expand_columns(const char *val, css_decl *dst, int cap)` |
| `expand_content` | function | `src/css.c:2098` | `static int expand_content(const char *val, css_decl *dst, int cap,                           char...` |
| `expand_counter_decls` | function | `src/css.c:2080` | `static int expand_counter_decls(const char *prop, const char *val, css_decl *dst, int cap,       ...` |
| `expand_flex` | function | `src/css.c:2424` | `static int expand_flex(const char *val, css_decl *dst, int cap)` |
| `expand_flex_flow` | function | `src/css.c:1317` | `static int expand_flex_flow(const char *val, css_decl *dst, int cap)` |
| `expand_gap` | function | `src/css.c:3510` | `static int expand_gap(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area` | function | `src/css.c:2211` | `static int expand_grid_area(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area_lines` | function | `src/css.c:2177` | `static int expand_grid_area_lines(const char *val, css_decl *dst, int cap)` |
| `expand_grid_areas` | function | `src/css.c:2149` | `static int expand_grid_areas(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_grid_line` | function | `src/css.c:2202` | `static int expand_grid_line(const char *val, css_decl *dst, int cap, int p_start, int p_end)` |
| `expand_grid_template` | function | `src/css.c:2250` | `static int expand_grid_template(const char *val, css_decl *dst, int cap,                         ...` |
| `expand_grid_template_cols` | function | `src/css.c:361` | `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `expand_mask_geometry` | function | `src/css.c:771` | `static int expand_mask_geometry(const char *prop, const char *val, css_decl *dst, int cap)` |
| `expand_outline` | function | `src/css.c:1234` | `static int expand_outline(const char *val, css_decl *dst, int cap)` |
| `expand_shadow` | function | `src/css.c:380` | `static int expand_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_transform_list` | function | `src/css.c:3247` | `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);` |
| `expand_transform_origin` | function | `src/css.c:3478` | `static int expand_transform_origin(const char *val, css_decl *dst, int cap)` |
| `expand_valign` | function | `src/css.c:370` | `static int expand_valign(const char *val, css_decl *dst, int cap)` |
| `filter_paren_body` | function | `src/css.c:1380` | `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)` |
| `first_comma_item` | function | `src/css.c:746` | `static void first_comma_item(const char *val, char *buf, size_t cap);` |
| `fold_font_relative` | function | `src/css.c:6729` | `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,                          ...` |
| `font_list_alias` | function | `src/css.c:3660` | `static void font_list_alias(const css_sheet *sheet, const char *ls, char *out, size_t cap)` |
| `font_list_norm` | function | `src/css.c:3694` | `static int font_list_norm(const char *val, char *out, size_t cap)` |
| `function` | function | `src/css.c:3251` | `* transform function (perspective/rotate3d/...), or unparseable syntax,  * rejects the WHOLE decl...` |
| `has_double_dash` | function | `src/css.c:2634` | `static int has_double_dash(const char *p, size_t n)` |
| `here` | function | `src/css.c:4463` | `* servers have no form here (fail closed). */ int o = csel_ci_eq(val, "none") ? CSS_SVG_PAINT_NONE : interp_color(val);` |
| `idx` | type_alias | `src/css.c:6594` | `typedef struct css_cand { int imp, espec, ord, idx;` |
| `interp_accent_color` | function | `src/css.c:897` | `static int interp_accent_color(const char *v)` |
| `interp_align` | function | `src/css.c:315` | `static int interp_align(const char *v)` |
| `interp_align_kw` | function | `src/css.c:2469` | `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` |
| `interp_appearance` | function | `src/css.c:601` | `static int interp_appearance(const char *v)` |
| `interp_aspect_ratio` | function | `src/css.c:376` | `static int interp_aspect_ratio(const char *v, int *num, int *den)` |
| `interp_backface_visibility` | function | `src/css.c:1060` | `static int interp_backface_visibility(const char *v)` |
| `interp_bc_tok` | function | `src/css.c:1161` | `static int interp_bc_tok(const char *t, int *o)` |
| `interp_bg` | function | `src/css.c:240` | `static int interp_bg(const char *v)` |
| `interp_bg_attachment` | function | `src/css.c:831` | `static int interp_bg_attachment(const char *v)` |
| `interp_bg_clip` | function | `src/css.c:816` | `static int interp_bg_clip(const char *v)` |
| `interp_bg_origin` | function | `src/css.c:824` | `static int interp_bg_origin(const char *v)` |
| `interp_bg_repeat` | function | `src/css.c:631` | `static int interp_bg_repeat(const char *v)` |
| `interp_bg_repeat2` | function | `src/css.c:642` | `static int interp_bg_repeat2(const char *v)` |
| `interp_bg_size` | function | `src/css.c:809` | `static int interp_bg_size(const char *v)` |
| `interp_border_collapse` | function | `src/css.c:509` | `static int interp_border_collapse(const char *v)` |
| `interp_border_style` | function | `src/css.c:1083` | `static int interp_border_style(const char *v)` |
| `interp_box_orient` | function | `src/css.c:2511` | `static int interp_box_orient(const char *v)` |
| `interp_boxsizing` | function | `src/css.c:393` | `static int interp_boxsizing(const char *v)` |
| `interp_bs_tok` | function | `src/css.c:1160` | `static int interp_bs_tok(const char *t, int *o)` |
| `interp_bw_tok` | function | `src/css.c:1159` | `static int interp_bw_tok(const char *t, int *o)` |
| `interp_bwidth1` | function | `src/css.c:1109` | `static int interp_bwidth1(const char *v)` |
| `interp_caption_side` | function | `src/css.c:550` | `static int interp_caption_side(const char *v)` |
| `interp_caret_color` | function | `src/css.c:589` | `static int interp_caret_color(const char *v)` |
| `interp_clear` | function | `src/css.c:406` | `static int interp_clear(const char *v)` |
| `interp_color` | function | `src/css.c:196` | `static int interp_color(const char *v)` |
| `interp_color_scheme` | function | `src/css.c:879` | `static int interp_color_scheme(const char *v)` |
| `interp_column_count` | function | `src/css.c:1260` | `static int interp_column_count(const char *v)` |
| `interp_column_width` | function | `src/css.c:1272` | `static int interp_column_width(const char *v)` |
| `interp_contain` | function | `src/css.c:844` | `static int interp_contain(const char *v)` |
| `interp_content_visibility` | function | `src/css.c:865` | `static int interp_content_visibility(const char *v)` |
| `interp_cursor` | function | `src/css.c:455` | `static int interp_cursor(const char *v)` |
| `interp_direction` | function | `src/css.c:377` | `static int interp_direction(const char *v)` |
| `interp_display` | function | `src/css.c:349` | `static int interp_display(const char *v)` |
| `interp_empty_cells` | function | `src/css.c:543` | `static int interp_empty_cells(const char *v)` |
| `interp_filter_deg` | function | `src/css.c:1365` | `static int interp_filter_deg(const char *s)` |
| `interp_filter_pct` | function | `src/css.c:1351` | `static int interp_filter_pct(const char *s)` |
| `interp_flex_basis` | function | `src/css.c:2390` | `static int interp_flex_basis(const char *v, int *out)` |
| `interp_flex_direction` | function | `src/css.c:2493` | `static int interp_flex_direction(const char *v)` |
| `interp_flex_factor` | function | `src/css.c:2380` | `static int interp_flex_factor(const char *v)` |
| `interp_flex_line_pack` | function | `src/css.c:2538` | `static int interp_flex_line_pack(const char *v)` |
| `interp_flex_wrap` | function | `src/css.c:2548` | `static int interp_flex_wrap(const char *v)` |
| `interp_float` | function | `src/css.c:399` | `static int interp_float(const char *v)` |
| `interp_font_kerning` | function | `src/css.c:995` | `static int interp_font_kerning(const char *v)` |
| `interp_font_stretch` | function | `src/css.c:1010` | `static int interp_font_stretch(const char *v)` |
| `interp_font_variant` | function | `src/css.c:564` | `static int interp_font_variant(const char *v)` |
| `interp_fontfamily` | function | `src/css.c:367` | `static int interp_fontfamily(const char *v)` |
| `interp_fontsize_ex` | function | `src/css.c:319` | `static int interp_fontsize_ex(const char *v, int *abs_out)` |
| `interp_forced_color_adjust` | function | `src/css.c:908` | `static int interp_forced_color_adjust(const char *v)` |
| `interp_gap` | function | `src/css.c:353` | `static int interp_gap(const char *v)` |
| `interp_grid_flow` | function | `src/css.c:2556` | `static int interp_grid_flow(const char *v)` |
| `interp_hyphens` | function | `src/css.c:572` | `static int interp_hyphens(const char *v)` |
| `interp_image_rendering` | function | `src/css.c:872` | `static int interp_image_rendering(const char *v)` |
| `interp_isolation` | function | `src/css.c:838` | `static int interp_isolation(const char *v)` |
| `interp_justify` | function | `src/css.c:357` | `static int interp_justify(const char *v)` |
| `interp_len` | function | `src/css.c:298` | `static int interp_len(const char *v, int allow_auto, int *out)` |
| `interp_lineheight` | function | `src/css.c:333` | `static int interp_lineheight(const char *v)` |
| `interp_list_style_pos` | function | `src/css.c:989` | `static int interp_list_style_pos(const char *v)` |
| `interp_liststyle` | function | `src/css.c:378` | `static int interp_liststyle(const char *v)` |
| `interp_lp` | function | `src/css.c:302` | `static int interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_...` |
| `interp_mix_blend_mode` | function | `src/css.c:915` | `static int interp_mix_blend_mode(const char *v)` |
| `interp_object_fit` | function | `src/css.c:980` | `static int interp_object_fit(const char *v)` |
| `interp_object_pos` | function | `src/css.c:938` | `static int interp_object_pos(const char *v)` |
| `interp_opacity` | function | `src/css.c:369` | `static int interp_opacity(const char *v)` |
| `interp_outline_style` | function | `src/css.c:1229` | `static int interp_outline_style(const char *v)` |
| `interp_overflow` | function | `src/css.c:423` | `static int interp_overflow(const char *v)` |
| `interp_overflow_wrap` | function | `src/css.c:501` | `static int interp_overflow_wrap(const char *v)` |
| `interp_overscroll_behavior` | function | `src/css.c:1053` | `static int interp_overscroll_behavior(const char *v)` |
| `interp_pointer_events` | function | `src/css.c:619` | `static int interp_pointer_events(const char *v)` |
| `interp_position` | function | `src/css.c:384` | `static int interp_position(const char *v)` |
| `interp_print_color_adjust` | function | `src/css.c:902` | `static int interp_print_color_adjust(const char *v)` |
| `interp_resize` | function | `src/css.c:1023` | `static int interp_resize(const char *v)` |
| `interp_scroll_behavior` | function | `src/css.c:1031` | `static int interp_scroll_behavior(const char *v)` |
| `interp_style` | function | `src/css.c:341` | `static int interp_style(const char *v)` |
| `interp_table_layout` | function | `src/css.c:557` | `static int interp_table_layout(const char *v)` |
| `interp_tabsize` | function | `src/css.c:373` | `static int interp_tabsize(const char *v)` |
| `interp_text_overflow` | function | `src/css.c:487` | `static int interp_text_overflow(const char *v)` |
| `interp_text_rendering` | function | `src/css.c:1002` | `static int interp_text_rendering(const char *v)` |
| `interp_textdeco` | function | `src/css.c:345` | `static int interp_textdeco(const char *v)` |
| `interp_textdeco_style` | function | `src/css.c:374` | `static int interp_textdeco_style(const char *v)` |
| `interp_textdeco_thickness` | function | `src/css.c:375` | `static int interp_textdeco_thickness(const char *v)` |
| `interp_texttransform` | function | `src/css.c:368` | `static int interp_texttransform(const char *v)` |
| `interp_time_ms` | function | `src/css.c:1118` | `static int interp_time_ms(const char *v)` |
| `interp_transition_property` | function | `src/css.c:371` | `static int interp_transition_property(const char *v)` |
| `interp_user_select` | function | `src/css.c:580` | `static int interp_user_select(const char *v)` |
| `interp_visibility` | function | `src/css.c:416` | `static int interp_visibility(const char *v)` |
| `interp_weight` | function | `src/css.c:337` | `static int interp_weight(const char *v)` |
| `interp_whitespace` | function | `src/css.c:372` | `static int interp_whitespace(const char *v)` |
| `interp_word_break` | function | `src/css.c:493` | `static int interp_word_break(const char *v)` |
| `interpret_decls` | function | `src/css.c:4956` | `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,                ...` |
| `interpret_prop` | function | `src/css.c:4763` | `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,             ...` |
| `interpret_prop_dispatch` | function | `src/css.c:3953` | `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,    ...` |
| `is_anim_ident` | function | `src/css.c:1503` | `static int is_anim_ident(const char *tok)` |
| `is_inert_prop` | function | `src/css.c:3930` | `static int is_inert_prop(const char *prop)` |
| `item` | function | `src/css.c:1393` | `* timing list takes its first item (CSS Animations/Transitions 1: with one  * transition/animatio...` |
| `layer` | function | `src/css.c:663` | `* first layer (the one painted) -- so `background: url(x) no-repeat` stops tiling  * and a later ...` |
| `layer_register` | function | `src/css.c:5270` | `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,                      ...` |
| `len_rebase` | function | `src/css.c:5772` | `static char *len_rebase(const char *s, size_t n, const len_rebase_ctx *c, size_t *outlen)` |
| `len_rebase_ctx` | struct | `src/css.c:5730` | `` |
| `len_unit_px` | function | `src/css.c:5742` | `static double len_unit_px(const char *u, size_t len, const len_rebase_ctx *c)` |
| `lp_can_be_nonneg` | function | `src/css.c:307` | `static int lp_can_be_nonneg(int px_val, int pct_pm)` |
| `matrix` | function | `src/css.c:2833` | `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands...` |
| `multiplying` | function | `src/css.c:3877` | `* instead of the two multiplying (no page measured needs both on one element).  * A third (z) com...` |
| `next_ws_token` | function | `src/css.c:311` | `static int next_ws_token(const char **p, char *tok, size_t cap)` |
| `number` | function | `src/css.c:518` | `* number (no unit) as px (common in shorthand context like "10 5"). */ static int interp_border_s...` |
| `order` | function | `src/css.c:1745` | `* declaration order (dx, dy, optional blur >= 0);` |
| `origin_component` | function | `src/css.c:3452` | `static int origin_component(const char *tok, int axis, int *out)` |
| `page_view` | function | `src/css.c:6084` | `* the generated text reaches page_view (which materialises it as a synthetic * run);` |
| `parent` | function | `src/css.c:6117` | `* property from the parent (`inherit`), and an unset non-inherited one          * stands at its i...` |
| `parse_angle_deg` | function | `src/css.c:3244` | `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);` |
| `parse_block` | function | `src/css.c:5395` | `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,                  ...` |
| `parse_color` | function | `src/css.c:192` | `static int parse_color(const char *v)` |
| `parse_matrix6` | function | `src/css.c:2886` | `static int parse_matrix6(const char *p, size_t argn, double m6[6])` |
| `parse_num` | function | `src/css.c:181` | `static int parse_num(const char *s, double *out, const char **endp)` |
| `parse_numlist` | function | `src/css.c:2863` | `static int parse_numlist(const char *p, size_t argn, double *m6, int count)` |
| `property` | function | `src/css.c:3569` | `* error drops the whole property (fail closed). */ static int expand_clip(const char *val, css_de...` |
| `pseudo_of` | function | `src/css.c:6776` | `static int pseudo_of(int which)` |
| `raw_add` | function | `src/css.c:4837` | `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)` |
| `rem_emit_px` | function | `src/css.c:5712` | `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)` |
| `rem_ident_ch` | function | `src/css.c:5694` | `static int rem_ident_ch(char c)` |
| `rem_num_starts_after` | function | `src/css.c:5702` | `static int rem_num_starts_after(char prev)` |
| `rem_px` | type_alias | `src/css.c:5730` | `typedef struct len_rebase_ctx { double rem_px;` |
| `rem_rebase` | function | `src/css.c:5838` | `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)` |
| `remap_to_mask` | function | `src/css.c:762` | `static int remap_to_mask(css_decl *dst, int n)` |
| `resolve_core` | function | `src/css.c:6796` | `static css_style resolve_core(const css_sheet *sheet, const css_element *el,                     ...` |
| `sel_list_comma` | function | `src/css.c:2295` | `static size_t sel_list_comma(const char *s, size_t i, size_t end);` |
| `selector_matches_root` | function | `src/css.c:2691` | `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m,          ...` |
| `sentinel` | function | `src/css.c:4250` | `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);` |
| `sheet_index` | function | `src/css.c:5846` | `static void sheet_index(css_sheet *sh)` |
| `sheet_pools_reserve` | function | `src/css.c:5014` | `static void sheet_pools_reserve(css_sheet *sh)` |
| `sheet_rewind` | function | `src/css.c:5851` | `static void sheet_rewind(css_sheet *sh)` |
| `sheet_root_font_px` | function | `src/css.c:5896` | `static double sheet_root_font_px(const css_sheet *sh)` |
| `shorthand` | function | `src/css.c:3534` | `* An uninterpretable token drops the whole shorthand (fail closed). */ static int expand_place(co...` |
| `shorthand` | function | `src/css.c:3780` | `* generic bucket keeps the rest of the shorthand (same net effect as the  * font-family longhand ...` |
| `skip_at_rule` | function | `src/css.c:5133` | `static size_t skip_at_rule(const char *s, size_t i, size_t n)` |
| `slots` | function | `src/css.c:4122` | `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return...` |
| `split_top_args` | function | `src/css.c:2899` | `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,                ...` |
| `strip_comments` | function | `src/css.c:5904` | `static char *strip_comments(const char *text, size_t len, size_t *outlen)` |
| `strip_important` | function | `src/css.c:2587` | `static int strip_important(char *val)` |
| `subject_may_be_root` | function | `src/css.c:2643` | `static int subject_may_be_root(const char *s, size_t a, size_t b, const char *root_scope)` |
| `supports_matches` | function | `src/css.c:5216` | `static int supports_matches(const char *s, size_t a, size_t b)` |
| `supports_selector_ok` | function | `src/css.c:5207` | `static int supports_selector_ok(void *ctx, const char *sel)` |
| `text` | function | `src/css.c:268` | `* source text (rem_rebase, see below) rather than by threading a context here.  *  * Viewport uni...` |
| `through` | function | `src/css.c:212` | `* at the two SHARED chokepoints every property funnels through (the generic  * dispatch tail, and...` |
| `tr_decompose` | function | `src/css.c:2840` | `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,                         in...` |
| `tr_mul` | function | `src/css.c:2820` | `static void tr_mul(double out[6], const double l[6], const double r[6])` |
| `translate3d` | function | `src/css.c:2929` | `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine  * renders z as nothing,...` |
| `translateX` | function | `src/css.c:3240` | `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc...` |
| `translateZ` | function | `src/css.c:3249` | `* translateZ(), rotateX(0) and rotateY(0) emit the identity (with the stacking * context Firefox builds);` |
| `var` | function | `src/css.c:2612` | `* cvr_resolve then substitutes var() references when a declaration's value is  * interpreted (par...` |
| `var` | function | `src/css.c:5914` | `* collected and forty var() declarations -- font sizes, widths, radii, the      * whole theme -- ...` |
| `wide_claim` | function | `src/css.c:4723` | `static int wide_claim(const char *prop, css_decl *dst, int cap,                       char (*urlt...` |
| `writing` | function | `src/css.c:3738` | `* Wide keywords claim BOTH slots without writing (inheritance then flows, as  * the tail does for...` |
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
| `CCH_CLASS_SPILL_MAX` | macro | `src/css_chain.c:21` | `#define CCH_CLASS_SPILL_MAX` |
| `CCH_ID_MAX` | macro | `src/css_chain.c:16` | `#define CCH_ID_MAX` |
| `CCH_MAX_ATTRS` | macro | `src/css_chain.c:22` | `#define CCH_MAX_ATTRS` |
| `CCH_MAX_CLASSES` | macro | `src/css_chain.c:18` | `#define CCH_MAX_CLASSES` |
| `CCH_TAG_MAX` | macro | `src/css_chain.c:15` | `#define CCH_TAG_MAX` |
| `cch_element_matches` | function | `src/css_chain.c:462` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)` |
| `cch_element_matches_any` | function | `src/css_chain.c:476` | `int cch_element_matches_any(lxb_dom_element_t *el, const css_sel *sels, size_t n)` |
| `cch_element_style` | function | `src/css_chain.c:458` | `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)` |
| `cch_element_style_path` | function | `src/css_chain.c:372` | `css_style cch_element_style_path(cch_path *pa, lxb_dom_element_t *el, const css_sheet *sheet,    ...` |
| `cch_element_style_vars` | function | `src/css_chain.c:310` | `css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,                  ...` |
| `cch_node` | struct | `src/css_chain.c:27` | `` |
| `cch_path` | struct | `src/css_chain.c:347` | `` |
| `cch_path_free` | function | `src/css_chain.c:365` | `void cch_path_free(cch_path *pa)` |
| `cch_path_new` | function | `src/css_chain.c:353` | `cch_path *cch_path_new(void)` |
| `cch_pseudo_style` | function | `src/css_chain.c:439` | `css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,             ...` |
| `cls_space` | function | `src/css_chain.c:42` | `static int cls_space(char c)` |
| `count_children` | function | `src/css_chain.c:227` | `static int count_children(lxb_dom_node_t *n)` |
| `fill_css_node` | function | `src/css_chain.c:99` | `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)` |
| `inputs` | function | `src/css_chain.c:241` | `* identical inputs (single source of truth). */ static const css_element *build_chain(lxb_dom_ele...` |
| `path_truncate` | function | `src/css_chain.c:357` | `static void path_truncate(cch_path *pa, int keep)` |
| `release_nodes` | function | `src/css_chain.c:90` | `static void release_nodes(cch_node *nodes, int n)` |
| `sibling_position` | function | `src/css_chain.c:181` | `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `sibling_type_position` | function | `src/css_chain.c:199` | `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `tag` | type_alias | `src/css_chain.c:27` | `typedef struct cch_node { char tag[CCH_TAG_MAX];` |
| `CC_CALC_DEPTH` | macro | `src/css_color.c:221` | `#define CC_CALC_DEPTH` |
| `CC_CHANNEL_MAX` | macro | `src/css_color.c:23` | `#define CC_CHANNEL_MAX` |
| `CC_HSL_SCALE` | macro | `src/css_color.c:32` | `#define CC_HSL_SCALE` |
| `CC_NUMBER_MAX_DIGITS` | macro | `src/css_color.c:29` | `#define CC_NUMBER_MAX_DIGITS` |
| `CC_PERCENT_MAX` | macro | `src/css_color.c:24` | `#define CC_PERCENT_MAX` |
| `CC_PI` | macro | `src/css_color.c:577` | `#define CC_PI` |
| `CC_TOKEN_MAX` | macro | `src/css_color.c:20` | `#define CC_TOKEN_MAX` |
| `ascii_lower` | function | `src/css_color.c:119` | `static int ascii_lower(int c)` |
| `cc_cexpr` | function | `src/css_color.c:269` | `static int cc_cexpr(cc_cp *c, cc_cv *out, int depth)` |
| `cc_cfactor` | function | `src/css_color.c:229` | `static int cc_cfactor(cc_cp *c, cc_cv *out, int depth)` |
| `cc_cp` | struct | `src/css_color.c:224` | `` |
| `cc_cterm` | function | `src/css_color.c:250` | `static int cc_cterm(cc_cp *c, cc_cv *out, int depth)` |
| `cc_cv` | struct | `src/css_color.c:223` | `` |
| `cc_cws` | function | `src/css_color.c:226` | `static void cc_cws(cc_cp *c)` |
| `cc_fold_calc` | function | `src/css_color.c:285` | `static int cc_fold_calc(const char **b, const char **e, char *buf, size_t cap)` |
| `cc_named` | struct | `src/css_color.c:34` | `` |
| `cc_pack` | function | `src/css_color.c:768` | `int cc_pack(cc_rgb c)` |
| `cc_parse` | function | `src/css_color.c:728` | `cc_status cc_parse(const char *token, cc_rgb *out)` |
| `cc_round` | function | `src/css_color.c:305` | `static long cc_round(double v)` |
| `cc_unpack` | function | `src/css_color.c:772` | `cc_rgb cc_unpack(int packed)` |
| `hex_val` | function | `src/css_color.c:123` | `static int hex_val(int c)` |
| `lab_comp` | function | `src/css_color.c:581` | `static int lab_comp(const char *b, const char *e, double pct_ref, int is_hue, double *out)` |
| `lab_to_rgb` | function | `src/css_color.c:627` | `static void lab_to_rgb(double L, double a, double b, cc_rgb *out)` |
| `named_cmp` | function | `src/css_color.c:681` | `static int named_cmp(const void *key, const void *element)` |
| `normalize` | function | `src/css_color.c:132` | `static int normalize(const char *token, char *out)` |
| `oklab_to_rgb` | function | `src/css_color.c:616` | `static void oklab_to_rgb(double L, double a, double b, cc_rgb *out)` |
| `parse_component` | function | `src/css_color.c:310` | `static int parse_component(const char *b, const char *e, int is_alpha, int *out)` |
| `parse_func` | function | `src/css_color.c:508` | `static int parse_func(const char *s, cc_rgb *out)` |
| `parse_hex` | function | `src/css_color.c:146` | `static int parse_hex(const char *s, cc_rgb *out)` |
| `parse_hsl_comp` | function | `src/css_color.c:343` | `static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out)` |
| `parse_lab_family` | function | `src/css_color.c:643` | `static int parse_lab_family(const char *s, cc_rgb *out)` |
| `parse_named` | function | `src/css_color.c:715` | `static int parse_named(const char *s, cc_rgb *out)` |
| `span` | function | `src/css_color.c:431` | `* span (when a slash is present) into ab/ae, and returns the component count,  * or -1. Bounded: ...` |
| `srgb_encode` | function | `src/css_color.c:609` | `static unsigned char srgb_encode(double lin)` |
| `strncmp` | function | `src/css_color.c:743` | `strncmp(buf, "oklab(", 6) == 0 \|\| strncmp(buf, "oklch(", 6) == 0)` |
| `v` | type_alias | `src/css_color.c:222` | `typedef struct cc_cv { double v;` |
| `CCM_NPROPS` | macro | `src/css_computed.c:310` | `#define CCM_NPROPS` |
| `LEN_FIELD` | macro | `src/css_computed.c:225` | `#define LEN_FIELD(NAME, FIELD, UNSET)` |
| `NAME` | function | `src/css_computed.c:226` | `static size_t NAME(const ccm_input *in, char *out, size_t cap)` |
| `ccm_get` | function | `src/css_computed.c:312` | `size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap)` |
| `ccm_prop` | struct | `src/css_computed.c:278` | `` |
| `ccm_property_count` | function | `src/css_computed.c:325` | `size_t ccm_property_count(void)` |
| `ccm_property_name` | function | `src/css_computed.c:327` | `const char *ccm_property_name(size_t i)` |
| `f_align_items` | function | `src/css_computed.c:153` | `static size_t f_align_items(const ccm_input *in, char *out, size_t cap)` |
| `f_background_color` | function | `src/css_computed.c:200` | `static size_t f_background_color(const ccm_input *in, char *out, size_t cap)` |

Next: [SYMBOLS_p7.md](SYMBOLS_p7.md)
