# Symbols (page 5 of 14)
Previous: [SYMBOLS_p4.md](SYMBOLS_p4.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `T_GRP` | macro | `src/box_style.c:77` | `#define T_GRP` |
| `T_NO` | macro | `src/box_style.c:75` | `#define T_NO` |
| `T_ROW` | macro | `src/box_style.c:78` | `#define T_ROW` |
| `T_TBL` | macro | `src/box_style.c:76` | `#define T_TBL` |
| `ZERO` | macro | `src/box_style.c:73` | `#define ZERO` |
| `bg_size_component` | function | `src/box_style.c:393` | `static double bg_size_component(int px_val, int pct_pm, double area)` |
| `bx_background_layer` | function | `src/box_style.c:400` | `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h,                     ...` |
| `bx_block_ua_box` | function | `src/box_style.c:225` | `bx_box bx_block_ua_box(int heading_level, int in_list, bx_ua_tag ua)` |
| `bx_border_box_h` | function | `src/box_style.c:335` | `double bx_border_box_h(double declared_h, int border_box,                        double pad_t, do...` |
| `bx_border_span` | function | `src/box_style.c:381` | `double bx_border_span(double width_cap, int border_box,                       double pad_l, doubl...` |
| `bx_content_cap` | function | `src/box_style.c:363` | `double bx_content_cap(double width_cap, int border_box,                       double pad_l, doubl...` |
| `bx_content_clipped` | function | `src/box_style.c:346` | `int bx_content_clipped(int overflow_x, int overflow_y)` |
| `bx_default_for_tag` | function | `src/box_style.c:163` | `bx_box bx_default_for_tag(const char *tag)` |
| `bx_default_for_ua` | function | `src/box_style.c:219` | `bx_box bx_default_for_ua(bx_ua_tag id)` |
| `bx_display_name` | function | `src/box_style.c:439` | `const char *bx_display_name(bx_display d)` |
| `bx_flex_max_clamp` | function | `src/box_style.c:452` | `double bx_flex_max_clamp(double outer_basis, double mw_cap, int border_box,                      ...` |
| `bx_flex_min_clamp` | function | `src/box_style.c:374` | `double bx_flex_min_clamp(double outer_basis, double min_w, int border_box,                       ...` |
| `bx_lp_px` | function | `src/box_style.c:352` | `double bx_lp_px(int px_val, int pct_pm, double basis)` |
| `bx_parse_display` | function | `src/box_style.c:261` | `bx_status bx_parse_display(const char *token, bx_display *out)` |
| `bx_place` | function | `src/box_style.c:271` | `bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,                 ...` |
| `bx_place_ex` | function | `src/box_style.c:459` | `bx_hplace bx_place_ex(double inset_l, double inset_r, double width_cap, int center,              ...` |
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
| `BT_LEN_AUTO` | macro | `src/box_tree.c:31` | `#define BT_LEN_AUTO` |
| `BT_WRAP_EPS` | macro | `src/box_tree.c:62` | `#define BT_WRAP_EPS` |
| `assign_doc_order` | function | `src/box_tree.c:412` | `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,                   ...` |
| `block` | function | `src/box_tree.c:473` | `* true block (same flow neighbourhood), strictly better than zeros. NULL      * placed keeps lega...` |
| `bt_box_hidden` | function | `src/box_tree.c:683` | `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)` |
| `bt_containing_block` | function | `src/box_tree.c:462` | `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i,                         ...` |
| `bt_layout` | function | `src/box_tree.c:372` | `bt_status bt_layout(bt_node *root, double avail_w)` |
| `bt_nn` | function | `src/box_tree.c:58` | `static double bt_nn(double v)` |
| `bt_oof_anchor` | function | `src/box_tree.c:675` | `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)` |
| `bt_oof_avail` | function | `src/box_tree.c:696` | `double bt_oof_avail(int a, int a_pct, int b, int b_pct, double cb, int *both)` |
| `bt_oof_root` | function | `src/box_tree.c:679` | `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)` |
| `bt_resolve_positioning` | function | `src/box_tree.c:492` | `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,                           ...` |
| `bt_resolve_positioning_ex` | function | `src/box_tree.c:503` | `bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,                        ...` |
| `find_positioned_ancestor` | function | `src/box_tree.c:429` | `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,                        ...` |
| `inset_unset` | function | `src/box_tree.c:458` | `static int inset_unset(int v, int pct_pm)` |
| `layout_block` | function | `src/box_tree.c:37` | `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,                    ...` |
| `layout_flex` | function | `src/box_tree.c:97` | `static bt_status layout_flex(bt_node *node, bt_node *const *kids, size_t nk,                     ...` |
| `layout_grid` | function | `src/box_tree.c:220` | `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,                     ...` |
| `layout_node` | function | `src/box_tree.c:327` | `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)` |
| `oof_walk` | function | `src/box_tree.c:658` | `static int oof_walk(const pv_box_def *boxes, size_t nbox, int bid, int nearest)` |
| `resolve_inset` | function | `src/box_tree.c:449` | `static double resolve_inset(int v, int pct_pm, double basis)` |
| `wrap_reverse` | function | `src/box_tree.c:79` | `*  * wrap_reverse (node->wrap_reverse): when node->wrap is active and node->wrap_reverse  * is no...` |
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
| `cx_box_layer` | function | `src/compositor.c:34` | `cx_layer cx_box_layer(const cx_style *s)` |
| `cx_forms_stacking_context` | function | `src/compositor.c:16` | `int cx_forms_stacking_context(const cx_style *s)` |
| `cx_item_compare` | function | `src/compositor.c:54` | `int cx_item_compare(const cx_item *a, const cx_item *b)` |
| `cx_sort` | function | `src/compositor.c:70` | `void cx_sort(cx_item *items, size_t n)` |
| `eff_z` | function | `src/compositor.c:50` | `static int eff_z(const cx_item *it)` |
| `AUTO_REJECT` | macro | `src/css.c:270` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css.c:272` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css.c:273` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css.c:271` | `#define AUTO_VALUE` |
| `CSS_ATTR_MARK` | macro | `src/css.c:1684` | `#define CSS_ATTR_MARK` |
| `CSS_ATTR_SEP` | macro | `src/css.c:1685` | `#define CSS_ATTR_SEP` |
| `CSS_DECL_SLOTS_MIN` | macro | `src/css.c:65` | `#define CSS_DECL_SLOTS_MIN` |
| `CSS_INIT_DECLS` | macro | `src/css.c:50` | `#define CSS_INIT_DECLS` |
| `CSS_INIT_RULES` | macro | `src/css.c:66` | `#define CSS_INIT_RULES` |
| `CSS_INIT_SELS` | macro | `src/css.c:49` | `#define CSS_INIT_SELS` |
| `CSS_INLINE_DECLS` | macro | `src/css.c:68` | `#define CSS_INLINE_DECLS` |
| `CSS_MAX_FONT_FACES` | macro | `src/css.c:163` | `#define CSS_MAX_FONT_FACES` |
| `CSS_MAX_RAW` | macro | `src/css.c:85` | `#define CSS_MAX_RAW` |
| `CSS_MEDIA_MAX_DEPTH` | macro | `src/css.c:4535` | `#define CSS_MEDIA_MAX_DEPTH` |
| `CSS_SELS_PER_GROUP` | macro | `src/css.c:67` | `#define CSS_SELS_PER_GROUP` |
| `CSS_VAR_POOL` | macro | `src/css.c:5773` | `#define CSS_VAR_POOL` |
| `CSS_WIDE_RESET` | macro | `src/css.c:217` | `#define CSS_WIDE_RESET` |
| `LIST` | function | `src/css.c:2464` | `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose...` |
| `NULL` | function | `src/css.c:6187` | `* Sheet can be NULL (inline style, no @keyframes). */ void css_resolve_anim_keyframes(css_style *...` |
| `P_META_CUSTOM` | macro | `src/css.c:81` | `#define P_META_CUSTOM` |
| `P_META_VARSRC` | macro | `src/css.c:82` | `#define P_META_VARSRC` |
| `add_rule` | function | `src/css.c:4252` | `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,                      siz...` |
| `anim_easing_iv` | function | `src/css.c:1185` | `static int anim_easing_iv(const char *tok)` |
| `apply_decl` | function | `src/css.c:5256` | `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_rule` | function | `src/css.c:5804` | `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_var_source` | function | `src/css.c:5777` | `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,         ...` |
| `at_is_media` | function | `src/css.c:4402` | `static int at_is_media(const char *s, size_t i, size_t n)` |
| `at_keyword` | function | `src/css.c:4413` | `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)` |
| `axis` | function | `src/css.c:1511` | `* bare center displaces it to the free axis (`center right` = x:right, y:center).  * Any other co...` |
| `bg_alpha_of` | function | `src/css.c:231` | `static int bg_alpha_of(const char *v)` |
| `block_end` | function | `src/css.c:4380` | `static size_t block_end(const char *s, size_t open, size_t n)` |
| `blur` | function | `src/css.c:1474` | `* consumes ONLY blur(Npx);` |
| `caller` | function | `src/css.c:3269` | `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached...` |
| `cand_cmp` | function | `src/css.c:5712` | `static int cand_cmp(const void *pa, const void *pb)` |
| `cap` | function | `src/css.c:1743` | `* string past the cap (emit_content): a conforming declaration must not * count as a discard just because an icon...` |
| `collect_custom_props_scoped` | function | `src/css.c:4544` | `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,                 ...` |
| `column` | function | `src/css.c:2019` | `* column (`flex: 1 1 0%`);` |
| `computed_font_size` | function | `src/css.c:5696` | `static double computed_font_size(const css_style *o, const css_element *el)` |
| `consumer` | function | `src/css.c:5169` | `* consumer (shorthands, calc(), var() values) gets it with no context          * threaded through...` |
| `content_attr_of` | function | `src/css.c:5247` | `static const char *content_attr_of(const css_element *el, const char *name)` |
| `copy_trim` | function | `src/css.c:2179` | `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `csel_substr` | function | `src/css.c:4435` | `return known && csel_substr(val, "var(", 1);` |
| `css_cand` | struct | `src/css.c:5707` | `` |
| `css_decl` | function | `src/css.c:89` | `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);` |
| `css_font_face_at` | function | `src/css.c:6223` | `int css_font_face_at(const css_sheet *sheet, size_t i,                      char *family, size_t ...` |
| `css_font_face_count` | function | `src/css.c:6219` | `size_t css_font_face_count(const css_sheet *sheet)` |
| `css_free` | function | `src/css.c:5227` | `void css_free(css_sheet *s)` |
| `css_keyframe_stop` | struct | `src/css.c:142` | `` |
| `css_match` | struct | `src/css.c:5701` | `` |
| `css_parse` | function | `src/css.c:5121` | `css_status css_parse(const char *text, size_t len, css_sheet **out)` |
| `css_parse_inline` | function | `src/css.c:6233` | `css_style css_parse_inline(const char *style, size_t len)` |
| `css_parse_logged` | function | `src/css.c:5135` | `css_status css_parse_logged(const char *text, size_t len, const css_media *media,                ...` |
| `css_parse_media` | function | `src/css.c:5125` | `css_status css_parse_media(const char *text, size_t len, const css_media *media,                 ...` |
| `css_parse_scoped` | function | `src/css.c:5130` | `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,                ...` |
| `css_resolve` | function | `src/css.c:6163` | `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,                   ...` |
| `css_resolve_el` | function | `src/css.c:5873` | `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,                          ...` |
| `css_resolve_el_ex` | function | `src/css.c:5882` | `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,                       ...` |
| `css_resolve_pseudo` | function | `src/css.c:5898` | `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)` |
| `css_rule` | struct | `src/css.c:100` | `` |
| `css_sheet` | struct | `src/css.c:102` | `` |
| `declaration` | function | `src/css.c:1212` | `* declaration (precedent: expand_filter);` |
| `download` | function | `src/css.c:4746` | `* the download (spec/webfont.md b3b). An empty src_url                      * simply never resolv...` |
| `drop_copy_text` | function | `src/css.c:4050` | `static void drop_copy_text(char *dst, size_t cap, const char *src)` |
| `drop_record` | function | `src/css.c:4069` | `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)` |
| `emit` | function | `src/css.c:62` | `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand...` |
| `emit_content` | function | `src/css.c:1667` | `static int emit_content(css_decl *dst, int cap, const char *str,                         char (*c...` |
| `emit_radius_corner` | function | `src/css.c:922` | `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)` |
| `emit_spacing` | function | `src/css.c:365` | `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `empty` | function | `src/css.c:1777` | `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and...` |
| `expand_animation` | function | `src/css.c:1213` | `static int expand_animation(const char *val, css_decl *dst, int cap)` |
| `expand_backdrop_filter` | function | `src/css.c:1477` | `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)` |
| `expand_background` | function | `src/css.c:248` | `static int expand_background(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_bg_image` | function | `src/css.c:243` | `static int expand_bg_image(const char *val, css_decl *dst, int cap,                            ch...` |
| `expand_bg_size` | function | `src/css.c:1627` | `static int expand_bg_size(const char *val, css_decl *dst, int cap)` |
| `expand_box2` | function | `src/css.c:285` | `static int expand_box2(const char *val, int slot_start, int slot_end,                        int ...` |
| `expand_box4` | function | `src/css.c:280` | `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,             ...` |
| `expand_box_shadow` | function | `src/css.c:1968` | `static int expand_box_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_column_rule` | function | `src/css.c:1092` | `static int expand_column_rule(const char *val, css_decl *dst, int cap)` |
| `expand_columns` | function | `src/css.c:1036` | `static int expand_columns(const char *val, css_decl *dst, int cap)` |
| `expand_content` | function | `src/css.c:1773` | `static int expand_content(const char *val, css_decl *dst, int cap,                           char...` |
| `expand_flex` | function | `src/css.c:2040` | `static int expand_flex(const char *val, css_decl *dst, int cap)` |
| `expand_flex_flow` | function | `src/css.c:1070` | `static int expand_flex_flow(const char *val, css_decl *dst, int cap)` |
| `expand_gap` | function | `src/css.c:3000` | `static int expand_gap(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area` | function | `src/css.c:1878` | `static int expand_grid_area(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area_lines` | function | `src/css.c:1844` | `static int expand_grid_area_lines(const char *val, css_decl *dst, int cap)` |
| `expand_grid_areas` | function | `src/css.c:1816` | `static int expand_grid_areas(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_grid_line` | function | `src/css.c:1869` | `static int expand_grid_line(const char *val, css_decl *dst, int cap, int p_start, int p_end)` |
| `expand_grid_template` | function | `src/css.c:1917` | `static int expand_grid_template(const char *val, css_decl *dst, int cap,                         ...` |
| `expand_grid_template_cols` | function | `src/css.c:347` | `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `expand_outline` | function | `src/css.c:997` | `static int expand_outline(const char *val, css_decl *dst, int cap)` |
| `expand_shadow` | function | `src/css.c:366` | `static int expand_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_transform_list` | function | `src/css.c:2741` | `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);` |
| `expand_transform_origin` | function | `src/css.c:2968` | `static int expand_transform_origin(const char *val, css_decl *dst, int cap)` |
| `expand_valign` | function | `src/css.c:356` | `static int expand_valign(const char *val, css_decl *dst, int cap)` |
| `filter_paren_body` | function | `src/css.c:1133` | `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)` |
| `fold_font_relative` | function | `src/css.c:5842` | `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,                          ...` |
| `font_list_norm` | function | `src/css.c:3103` | `static int font_list_norm(const char *val, char *out, size_t cap)` |
| `function` | function | `src/css.c:2745` | `* transform function (perspective/rotate3d/...), or unparseable syntax,  * rejects the WHOLE decl...` |
| `here` | function | `src/css.c:3752` | `* servers have no form here (fail closed). */ int o = csel_ci_eq(val, "none") ? CSS_SVG_PAINT_NONE : interp_color(val);` |
| `idx` | type_alias | `src/css.c:5707` | `typedef struct css_cand { int imp, espec, ord, idx;` |
| `ignored` | function | `src/css.c:3019` | `* engine slot and is ignored (documented simplification, like list-style's  * ignored tokens). An...` |
| `interp_accent_color` | function | `src/css.c:715` | `static int interp_accent_color(const char *v)` |
| `interp_align` | function | `src/css.c:307` | `static int interp_align(const char *v)` |
| `interp_align_kw` | function | `src/css.c:2085` | `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` |
| `interp_appearance` | function | `src/css.c:587` | `static int interp_appearance(const char *v)` |
| `interp_aspect_ratio` | function | `src/css.c:362` | `static int interp_aspect_ratio(const char *v, int *num, int *den)` |
| `interp_backface_visibility` | function | `src/css.c:831` | `static int interp_backface_visibility(const char *v)` |
| `interp_bc_tok` | function | `src/css.c:932` | `static int interp_bc_tok(const char *t, int *o)` |
| `interp_bg` | function | `src/css.c:235` | `static int interp_bg(const char *v)` |
| `interp_bg_attachment` | function | `src/css.c:649` | `static int interp_bg_attachment(const char *v)` |
| `interp_bg_clip` | function | `src/css.c:634` | `static int interp_bg_clip(const char *v)` |
| `interp_bg_origin` | function | `src/css.c:642` | `static int interp_bg_origin(const char *v)` |
| `interp_bg_repeat` | function | `src/css.c:617` | `static int interp_bg_repeat(const char *v)` |
| `interp_bg_size` | function | `src/css.c:627` | `static int interp_bg_size(const char *v)` |
| `interp_border_collapse` | function | `src/css.c:495` | `static int interp_border_collapse(const char *v)` |
| `interp_border_style` | function | `src/css.c:854` | `static int interp_border_style(const char *v)` |
| `interp_box_orient` | function | `src/css.c:2116` | `static int interp_box_orient(const char *v)` |
| `interp_boxsizing` | function | `src/css.c:379` | `static int interp_boxsizing(const char *v)` |
| `interp_bs_tok` | function | `src/css.c:931` | `static int interp_bs_tok(const char *t, int *o)` |
| `interp_bw_tok` | function | `src/css.c:930` | `static int interp_bw_tok(const char *t, int *o)` |
| `interp_bwidth1` | function | `src/css.c:880` | `static int interp_bwidth1(const char *v)` |
| `interp_caption_side` | function | `src/css.c:536` | `static int interp_caption_side(const char *v)` |
| `interp_caret_color` | function | `src/css.c:575` | `static int interp_caret_color(const char *v)` |
| `interp_clear` | function | `src/css.c:392` | `static int interp_clear(const char *v)` |
| `interp_color` | function | `src/css.c:191` | `static int interp_color(const char *v)` |
| `interp_color_scheme` | function | `src/css.c:697` | `static int interp_color_scheme(const char *v)` |
| `interp_column_count` | function | `src/css.c:1013` | `static int interp_column_count(const char *v)` |
| `interp_column_width` | function | `src/css.c:1025` | `static int interp_column_width(const char *v)` |
| `interp_contain` | function | `src/css.c:662` | `static int interp_contain(const char *v)` |
| `interp_content_visibility` | function | `src/css.c:683` | `static int interp_content_visibility(const char *v)` |
| `interp_cursor` | function | `src/css.c:441` | `static int interp_cursor(const char *v)` |
| `interp_direction` | function | `src/css.c:363` | `static int interp_direction(const char *v)` |
| `interp_display` | function | `src/css.c:331` | `static int interp_display(const char *v)` |
| `interp_empty_cells` | function | `src/css.c:529` | `static int interp_empty_cells(const char *v)` |
| `interp_filter_deg` | function | `src/css.c:1118` | `static int interp_filter_deg(const char *s)` |
| `interp_filter_pct` | function | `src/css.c:1104` | `static int interp_filter_pct(const char *s)` |
| `interp_flex_basis` | function | `src/css.c:2006` | `static int interp_flex_basis(const char *v, int *out)` |
| `interp_flex_direction` | function | `src/css.c:2098` | `static int interp_flex_direction(const char *v)` |
| `interp_flex_factor` | function | `src/css.c:1996` | `static int interp_flex_factor(const char *v)` |
| `interp_flex_line_pack` | function | `src/css.c:2143` | `static int interp_flex_line_pack(const char *v)` |
| `interp_flex_wrap` | function | `src/css.c:2153` | `static int interp_flex_wrap(const char *v)` |
| `interp_float` | function | `src/css.c:385` | `static int interp_float(const char *v)` |
| `interp_font_kerning` | function | `src/css.c:766` | `static int interp_font_kerning(const char *v)` |
| `interp_font_stretch` | function | `src/css.c:781` | `static int interp_font_stretch(const char *v)` |
| `interp_font_variant` | function | `src/css.c:550` | `static int interp_font_variant(const char *v)` |
| `interp_fontfamily` | function | `src/css.c:353` | `static int interp_fontfamily(const char *v)` |
| `interp_fontsize_ex` | function | `src/css.c:311` | `static int interp_fontsize_ex(const char *v, int *abs_out)` |
| `interp_forced_color_adjust` | function | `src/css.c:726` | `static int interp_forced_color_adjust(const char *v)` |
| `interp_gap` | function | `src/css.c:335` | `static int interp_gap(const char *v)` |
| `interp_grid_flow` | function | `src/css.c:2161` | `static int interp_grid_flow(const char *v)` |
| `interp_gridcols` | function | `src/css.c:343` | `static int interp_gridcols(const char *v)` |
| `interp_hyphens` | function | `src/css.c:558` | `static int interp_hyphens(const char *v)` |
| `interp_image_rendering` | function | `src/css.c:690` | `static int interp_image_rendering(const char *v)` |
| `interp_isolation` | function | `src/css.c:656` | `static int interp_isolation(const char *v)` |
| `interp_justify` | function | `src/css.c:339` | `static int interp_justify(const char *v)` |
| `interp_len` | function | `src/css.c:290` | `static int interp_len(const char *v, int allow_auto, int *out)` |
| `interp_lineheight` | function | `src/css.c:315` | `static int interp_lineheight(const char *v)` |
| `interp_list_style_pos` | function | `src/css.c:760` | `static int interp_list_style_pos(const char *v)` |
| `interp_liststyle` | function | `src/css.c:364` | `static int interp_liststyle(const char *v)` |
| `interp_lp` | function | `src/css.c:294` | `static int interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_...` |
| `interp_mix_blend_mode` | function | `src/css.c:733` | `static int interp_mix_blend_mode(const char *v)` |
| `interp_object_fit` | function | `src/css.c:751` | `static int interp_object_fit(const char *v)` |
| `interp_opacity` | function | `src/css.c:355` | `static int interp_opacity(const char *v)` |
| `interp_overflow` | function | `src/css.c:409` | `static int interp_overflow(const char *v)` |
| `interp_overflow_wrap` | function | `src/css.c:487` | `static int interp_overflow_wrap(const char *v)` |
| `interp_overscroll_behavior` | function | `src/css.c:824` | `static int interp_overscroll_behavior(const char *v)` |
| `interp_pointer_events` | function | `src/css.c:605` | `static int interp_pointer_events(const char *v)` |
| `interp_position` | function | `src/css.c:370` | `static int interp_position(const char *v)` |
| `interp_print_color_adjust` | function | `src/css.c:720` | `static int interp_print_color_adjust(const char *v)` |
| `interp_resize` | function | `src/css.c:794` | `static int interp_resize(const char *v)` |
| `interp_scroll_behavior` | function | `src/css.c:802` | `static int interp_scroll_behavior(const char *v)` |
| `interp_style` | function | `src/css.c:323` | `static int interp_style(const char *v)` |
| `interp_table_layout` | function | `src/css.c:543` | `static int interp_table_layout(const char *v)` |
| `interp_tabsize` | function | `src/css.c:359` | `static int interp_tabsize(const char *v)` |
| `interp_text_overflow` | function | `src/css.c:473` | `static int interp_text_overflow(const char *v)` |
| `interp_text_rendering` | function | `src/css.c:773` | `static int interp_text_rendering(const char *v)` |
| `interp_textdeco` | function | `src/css.c:327` | `static int interp_textdeco(const char *v)` |
| `interp_textdeco_style` | function | `src/css.c:360` | `static int interp_textdeco_style(const char *v)` |
| `interp_textdeco_thickness` | function | `src/css.c:361` | `static int interp_textdeco_thickness(const char *v)` |
| `interp_texttransform` | function | `src/css.c:354` | `static int interp_texttransform(const char *v)` |
| `interp_time_ms` | function | `src/css.c:889` | `static int interp_time_ms(const char *v)` |
| `interp_transition_property` | function | `src/css.c:357` | `static int interp_transition_property(const char *v)` |
| `interp_user_select` | function | `src/css.c:566` | `static int interp_user_select(const char *v)` |
| `interp_visibility` | function | `src/css.c:402` | `static int interp_visibility(const char *v)` |
| `interp_weight` | function | `src/css.c:319` | `static int interp_weight(const char *v)` |
| `interp_whitespace` | function | `src/css.c:358` | `static int interp_whitespace(const char *v)` |
| `interp_word_break` | function | `src/css.c:479` | `static int interp_word_break(const char *v)` |
| `interpret_decls` | function | `src/css.c:4208` | `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,                ...` |
| `interpret_prop` | function | `src/css.c:4023` | `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,             ...` |
| `interpret_prop_dispatch` | function | `src/css.c:3281` | `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,    ...` |
| `is_anim_ident` | function | `src/css.c:1197` | `static int is_anim_ident(const char *tok)` |
| `item` | function | `src/css.c:1146` | `* timing list takes its first item (CSS Animations/Transitions 1: with one  * transition/animatio...` |
| `layer_register` | function | `src/css.c:4501` | `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,                      ...` |
| `len_rebase` | function | `src/css.c:4954` | `static char *len_rebase(const char *s, size_t n, const len_rebase_ctx *c, size_t *outlen)` |
| `len_rebase_ctx` | struct | `src/css.c:4912` | `` |
| `len_unit_px` | function | `src/css.c:4924` | `static double len_unit_px(const char *u, size_t len, const len_rebase_ctx *c)` |
| `lp_can_be_nonneg` | function | `src/css.c:299` | `static int lp_can_be_nonneg(int px_val, int pct_pm)` |
| `matrix` | function | `src/css.c:2379` | `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands...` |
| `next_ws_token` | function | `src/css.c:303` | `static int next_ws_token(const char **p, char *tok, size_t cap)` |
| `number` | function | `src/css.c:504` | `* number (no unit) as px (common in shorthand context like "10 5"). */ static int interp_border_s...` |
| `order` | function | `src/css.c:1439` | `* declaration order (dx, dy, optional blur >= 0);` |
| `origin_component` | function | `src/css.c:2942` | `static int origin_component(const char *tok, int axis, int *out)` |
| `page_view` | function | `src/css.c:5263` | `* the generated text reaches page_view (which materialises it as a synthetic * run);` |
| `parent` | function | `src/css.c:5296` | `* property from the parent (`inherit`), and an unset non-inherited one          * stands at its i...` |
| `parse_angle_deg` | function | `src/css.c:2738` | `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);` |
| `parse_block` | function | `src/css.c:4619` | `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,                  ...` |
| `parse_color` | function | `src/css.c:187` | `static int parse_color(const char *v)` |
| `parse_matrix6` | function | `src/css.c:2409` | `static int parse_matrix6(const char *p, size_t argn, double m6[6])` |
| `parse_num` | function | `src/css.c:176` | `static int parse_num(const char *s, double *out, const char **endp)` |
| `property` | function | `src/css.c:3054` | `* error drops the whole property (fail closed). */ static int expand_clip(const char *val, css_de...` |
| `pseudo_of` | function | `src/css.c:5889` | `static int pseudo_of(int which)` |
| `raw_add` | function | `src/css.c:4095` | `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)` |
| `rem_emit_px` | function | `src/css.c:4894` | `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)` |
| `rem_ident_ch` | function | `src/css.c:4876` | `static int rem_ident_ch(char c)` |
| `rem_num_starts_after` | function | `src/css.c:4884` | `static int rem_num_starts_after(char prev)` |
| `rem_px` | type_alias | `src/css.c:4912` | `typedef struct len_rebase_ctx { double rem_px;` |
| `rem_rebase` | function | `src/css.c:5020` | `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)` |
| `resolve_core` | function | `src/css.c:5909` | `static css_style resolve_core(const css_sheet *sheet, const css_element *el,                     ...` |
| `selector_matches_root` | function | `src/css.c:2239` | `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m)` |
| `sentinel` | function | `src/css.c:3551` | `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);` |
| `sheet_index` | function | `src/css.c:5028` | `static void sheet_index(css_sheet *sh)` |
| `sheet_rewind` | function | `src/css.c:5033` | `static void sheet_rewind(css_sheet *sh)` |
| `sheet_root_font_px` | function | `src/css.c:5078` | `static double sheet_root_font_px(const css_sheet *sh)` |
| `shorthand` | function | `src/css.c:3189` | `* generic bucket keeps the rest of the shorthand (same net effect as the  * font-family longhand ...` |
| `skip_at_rule` | function | `src/css.c:4364` | `static size_t skip_at_rule(const char *s, size_t i, size_t n)` |
| `slots` | function | `src/css.c:3439` | `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return...` |
| `split_top_args` | function | `src/css.c:2441` | `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,                ...` |
| `strip_comments` | function | `src/css.c:5086` | `static char *strip_comments(const char *text, size_t len, size_t *outlen)` |
| `strip_important` | function | `src/css.c:2192` | `static int strip_important(char *val)` |
| `supports_matches` | function | `src/css.c:4447` | `static int supports_matches(const char *s, size_t a, size_t b)` |
| `supports_selector_ok` | function | `src/css.c:4438` | `static int supports_selector_ok(void *ctx, const char *sel)` |
| `text` | function | `src/css.c:260` | `* source text (rem_rebase, see below) rather than by threading a context here.  *  * Viewport uni...` |
| `through` | function | `src/css.c:207` | `* at the two SHARED chokepoints every property funnels through (the generic  * dispatch tail, and...` |
| `tr_decompose` | function | `src/css.c:2386` | `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,                         in...` |
| `tr_mul` | function | `src/css.c:2366` | `static void tr_mul(double out[6], const double l[6], const double r[6])` |
| `translate3d` | function | `src/css.c:2471` | `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine  * renders z as nothing,...` |
| `translateX` | function | `src/css.c:2734` | `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc...` |
| `translateZ` | function | `src/css.c:2743` | `* translateZ(), rotateX(0) and rotateY(0) emit the identity (with the stacking * context Firefox builds);` |
| `var` | function | `src/css.c:2217` | `* cvr_resolve then substitutes var() references when a declaration's value is  * interpreted (par...` |
| `var` | function | `src/css.c:5096` | `* collected and forty var() declarations -- font sizes, widths, radii, the      * whole theme -- ...` |
| `wide_claim` | function | `src/css.c:3983` | `static int wide_claim(const char *prop, css_decl *dst, int cap,                       char (*urlt...` |
| `writing` | function | `src/css.c:3147` | `* Wide keywords claim BOTH slots without writing (inheritance then flows, as  * the tail does for...` |
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
| `AUTO_REJECT` | macro | `src/css_box.c:1098` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css_box.c:1100` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css_box.c:1104` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css_box.c:1099` | `#define AUTO_VALUE` |
| `CSS_CALC_MAX_DEPTH` | macro | `src/css_box.c:618` | `#define CSS_CALC_MAX_DEPTH` |
| `CSS_MATHFN_MAX_ARGS` | macro | `src/css_box.c:622` | `#define CSS_MATHFN_MAX_ARGS` |
| `RELATIVE` | function | `src/css_box.c:63` | `* or RELATIVE (of the inherited size). Absolute: px/pt/rem/viewport units and the * absolute keywords. Relative: em...` |
| `accepts` | function | `src/css_box.c:610` | `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further...` |
| `calc_eval_em` | function | `src/css_box.c:867` | `static int calc_eval_em(const char *v, size_t vlen, double *out_em)` |
| `calc_eval_full` | function | `src/css_box.c:853` | `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,            ...` |
| `calc_expr` | function | `src/css_box.c:834` | `static int calc_expr(calc_parser *p, calc_val *out, int depth)` |
| `calc_match_fn` | function | `src/css_box.c:647` | `static int calc_match_fn(calc_parser *p, const char *name)` |
| `calc_mathfn` | function | `src/css_box.c:689` | `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` |
| `calc_parser` | struct | `src/css_box.c:638` | `` |
| `calc_piecewise` | function | `src/css_box.c:674` | `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)` |
| `calc_skip_ws` | function | `src/css_box.c:640` | `static void calc_skip_ws(calc_parser *p)` |
| `calc_term` | function | `src/css_box.c:810` | `static int calc_term(calc_parser *p, calc_val *out, int depth)` |
| `calc_unwrap` | function | `src/css_box.c:875` | `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` |
| `calc_val` | struct | `src/css_box.c:637` | `` |
| `cb_copy_trim` | function | `src/css_box.c:25` | `static size_t cb_copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `cb_expand_box2` | function | `src/css_box.c:1272` | `int cb_expand_box2(const char *val, int slot_start, int slot_end,                        int allo...` |
| `cb_expand_grid_template_cols` | function | `src/css_box.c:583` | `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `cb_interp_align` | function | `src/css_box.c:54` | `int cb_interp_align(const char *v)` |
| `cb_interp_display` | function | `src/css_box.c:205` | `int cb_interp_display(const char *v)` |
| `cb_interp_fontsize_ex` | function | `src/css_box.c:72` | `int cb_interp_fontsize_ex(const char *v, int *abs_out)` |
| `cb_interp_gap` | function | `src/css_box.c:280` | `int cb_interp_gap(const char *v)` |
| `cb_interp_justify` | function | `src/css_box.c:287` | `int cb_interp_justify(const char *v)` |
| `cb_interp_len` | function | `src/css_box.c:926` | `int cb_interp_len(const char *v, int allow_auto, int *out)` |
| `cb_interp_lineheight` | function | `src/css_box.c:145` | `int cb_interp_lineheight(const char *v)` |
| `cb_interp_lp` | function | `src/css_box.c:1025` | `int cb_interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_px, ...` |
| `cb_interp_style` | function | `src/css_box.c:175` | `int cb_interp_style(const char *v)` |
| `cb_interp_textdeco` | function | `src/css_box.c:185` | `int cb_interp_textdeco(const char *v)` |
| `cb_interp_weight` | function | `src/css_box.c:166` | `int cb_interp_weight(const char *v)` |
| `cb_length_px` | function | `src/css_box.c:49` | `int cb_length_px(const char *v, double *px)` |
| `cb_parse_num` | function | `src/css_box.c:13` | `static int cb_parse_num(const char *s, double *out, const char **endp)` |
| `cb_starts_with_ci` | function | `src/css_box.c:312` | `static int cb_starts_with_ci(const char *s, const char *pre)` |
| `cb_value_em_milli` | function | `src/css_box.c:1005` | `int cb_value_em_milli(const char *v)` |
| `cb_wide_keyword` | function | `src/css_box.c:18` | `static int cb_wide_keyword(const char *v)` |
| `count_one_repeat` | function | `src/css_box.c:356` | `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,                       ...` |
| `count_tracks` | function | `src/css_box.c:318` | `static int count_tracks(const char *s, size_t n)` |
| `expand_auto_fill` | function | `src/css_box.c:505` | `static int expand_auto_fill(const char *val, css_decl *dst, int cap)` |
| `interp_len` | function | `src/css_box.c:1201` | `* this file that might hand a token to interp_len (transitively: margin/padding/  * inset, flex-b...` |
| `min` | function | `src/css_box.c:708` | `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the...` |
| `pct_slot_of` | function | `src/css_box.c:955` | `static int pct_slot_of(int slot)` |
| `px` | type_alias | `src/css_box.c:637` | `typedef struct calc_val { double px;` |
| `repeat` | function | `src/css_box.c:301` | `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill\|...) /...` |
| `term` | function | `src/css_box.c:1032` | `* the same expression and failed closed on the percentage term (its property * may not accept one);` |
| `track_min_of` | function | `src/css_box.c:467` | `static int track_min_of(const char *tok)` |
| `track_size_of` | function | `src/css_box.c:326` | `static int track_size_of(const char *tok)` |
| `walk_tracks` | function | `src/css_box.c:399` | `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)` |
| `CCH_ATTR_BUF` | macro | `src/css_chain.c:23` | `#define CCH_ATTR_BUF` |
| `CCH_CLASS_BUF` | macro | `src/css_chain.c:17` | `#define CCH_CLASS_BUF` |
| `CCH_CLASS_SPILL_MAX` | macro | `src/css_chain.c:21` | `#define CCH_CLASS_SPILL_MAX` |
| `CCH_ID_MAX` | macro | `src/css_chain.c:16` | `#define CCH_ID_MAX` |
| `CCH_MAX_ATTRS` | macro | `src/css_chain.c:22` | `#define CCH_MAX_ATTRS` |
| `CCH_MAX_CLASSES` | macro | `src/css_chain.c:18` | `#define CCH_MAX_CLASSES` |
| `CCH_TAG_MAX` | macro | `src/css_chain.c:15` | `#define CCH_TAG_MAX` |
| `cch_element_matches` | function | `src/css_chain.c:351` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)` |
| `cch_element_style` | function | `src/css_chain.c:347` | `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)` |
| `cch_element_style_vars` | function | `src/css_chain.c:297` | `css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,                  ...` |
| `cch_node` | struct | `src/css_chain.c:27` | `` |
| `cch_pseudo_style` | function | `src/css_chain.c:328` | `css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,             ...` |
| `cls_space` | function | `src/css_chain.c:42` | `static int cls_space(char c)` |
| `count_children` | function | `src/css_chain.c:227` | `static int count_children(lxb_dom_node_t *n)` |
| `fill_css_node` | function | `src/css_chain.c:99` | `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)` |
| `inputs` | function | `src/css_chain.c:241` | `* identical inputs (single source of truth). */ static const css_element *build_chain(lxb_dom_ele...` |
| `release_nodes` | function | `src/css_chain.c:90` | `static void release_nodes(cch_node *nodes, int n)` |
| `sibling_position` | function | `src/css_chain.c:181` | `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `sibling_type_position` | function | `src/css_chain.c:199` | `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `tag` | type_alias | `src/css_chain.c:27` | `typedef struct cch_node { char tag[CCH_TAG_MAX];` |
| `CC_CHANNEL_MAX` | macro | `src/css_color.c:22` | `#define CC_CHANNEL_MAX` |
| `CC_HSL_SCALE` | macro | `src/css_color.c:31` | `#define CC_HSL_SCALE` |
| `CC_NUMBER_MAX_DIGITS` | macro | `src/css_color.c:28` | `#define CC_NUMBER_MAX_DIGITS` |
| `CC_PERCENT_MAX` | macro | `src/css_color.c:23` | `#define CC_PERCENT_MAX` |
| `CC_PI` | macro | `src/css_color.c:463` | `#define CC_PI` |
| `CC_TOKEN_MAX` | macro | `src/css_color.c:19` | `#define CC_TOKEN_MAX` |
| `ascii_lower` | function | `src/css_color.c:118` | `static int ascii_lower(int c)` |
| `cc_named` | struct | `src/css_color.c:33` | `` |
| `cc_pack` | function | `src/css_color.c:623` | `int cc_pack(cc_rgb c)` |
| `cc_parse` | function | `src/css_color.c:583` | `cc_status cc_parse(const char *token, cc_rgb *out)` |
| `cc_round` | function | `src/css_color.c:215` | `static long cc_round(double v)` |
| `cc_unpack` | function | `src/css_color.c:627` | `cc_rgb cc_unpack(int packed)` |
| `hex_val` | function | `src/css_color.c:122` | `static int hex_val(int c)` |
| `lab_comp` | function | `src/css_color.c:467` | `static int lab_comp(const char *b, const char *e, double pct_ref, int is_hue, double *out)` |
| `lab_to_rgb` | function | `src/css_color.c:513` | `static void lab_to_rgb(double L, double a, double b, cc_rgb *out)` |
| `named_cmp` | function | `src/css_color.c:567` | `static int named_cmp(const void *key, const void *element)` |
| `normalize` | function | `src/css_color.c:131` | `static int normalize(const char *token, char *out)` |
| `oklab_to_rgb` | function | `src/css_color.c:502` | `static void oklab_to_rgb(double L, double a, double b, cc_rgb *out)` |
| `parse_component` | function | `src/css_color.c:220` | `static int parse_component(const char *b, const char *e, int is_alpha, int *out)` |
| `parse_func` | function | `src/css_color.c:397` | `static int parse_func(const char *s, cc_rgb *out)` |
| `parse_hex` | function | `src/css_color.c:145` | `static int parse_hex(const char *s, cc_rgb *out)` |
| `parse_hsl_comp` | function | `src/css_color.c:253` | `static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out)` |
| `parse_lab_family` | function | `src/css_color.c:529` | `static int parse_lab_family(const char *s, cc_rgb *out)` |
| `parse_named` | function | `src/css_color.c:573` | `static int parse_named(const char *s, cc_rgb *out)` |
| `span` | function | `src/css_color.c:325` | `* span (when a slash is present) into ab/ae, and returns the component count,  * or -1. Bounded: ...` |
| `srgb_encode` | function | `src/css_color.c:495` | `static unsigned char srgb_encode(double lin)` |
| `strncmp` | function | `src/css_color.c:598` | `strncmp(buf, "oklab(", 6) == 0 \|\| strncmp(buf, "oklch(", 6) == 0)` |
| `CSS_GRAD_STOPS_MAX` | function | `src/css_gradient.c:183` | `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when  * the gradient fai...` |
| `bg_layer_tokens_ok` | function | `src/css_gradient.c:458` | `static int bg_layer_tokens_ok(const char *s)` |
| `cg_expand_background` | function | `src/css_gradient.c:498` | `int cg_expand_background(const char *val, css_decl *dst, int cap,                              ch...` |
| `cg_parse_num` | function | `src/css_gradient.c:12` | `static int cg_parse_num(const char *s, double *out, const char **endp)` |
| `cg_wide_keyword` | function | `src/css_gradient.c:17` | `static int cg_wide_keyword(const char *v)` |
| `conic_prelude` | function | `src/css_gradient.c:110` | `static int conic_prelude(const char *seg, int *angle)` |
| `declaration` | function | `src/css_gradient.c:451` | `* declaration (fail closed);` |
| `downstream` | function | `src/css_gradient.c:392` | `* happens downstream (render_doc.c), gated by caps.images like an <img>. */ int cg_expand_bg_imag...` |
| `emit_gradient` | function | `src/css_gradient.c:290` | `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,                          ...` |
| `find_gradient_call` | function | `src/css_gradient.c:76` | `static int find_gradient_call(const char *v, const char *fn, size_t *start,                      ...` |
| `find_radial_gradient` | function | `src/css_gradient.c:347` | `static int find_radial_gradient(const char *v, size_t *start, size_t *end,                       ...` |
| `grad_stop_pos` | function | `src/css_gradient.c:152` | `static int grad_stop_pos(const char *pp, int conic, const char **endp)` |
| `gradient` | function | `src/css_gradient.c:27` | `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,  * the whole decl...` |
| `pool` | function | `src/css_gradient.c:388` | `* pool (gradient explicitly reset);` |
| `cix_build` | function | `src/css_index.c:52` | `void cix_build(const css_sel *sels, size_t n, cix_index *idx)` |
| `cix_candidates` | function | `src/css_index.c:120` | `size_t cix_candidates(const cix_index *idx, const css_element *el,                       uint32_t...` |
| `cix_free` | function | `src/css_index.c:45` | `void cix_free(cix_index *idx)` |
| `entry_cmp` | function | `src/css_index.c:34` | `static int entry_cmp(const void *a, const void *b)` |
| `key_of` | function | `src/css_index.c:11` | `static uint64_t key_of(int kind, const char *s, size_t n, int lower)` |
| `key_of_token` | function | `src/css_index.c:26` | `static uint64_t key_of_token(int kind, const char *tok)` |
| `lower_bound` | function | `src/css_index.c:90` | `static size_t lower_bound(const cix_index *idx, uint64_t k)` |
| `push` | function | `src/css_index.c:100` | `static int push(uint32_t **buf, size_t *cap, size_t *n, uint32_t v)` |
| `push_bucket` | function | `src/css_index.c:113` | `static int push_bucket(const cix_index *idx, uint64_t k,                        uint32_t **buf, s...` |
| `u32_cmp` | function | `src/css_index.c:40` | `static int u32_cmp(const void *a, const void *b)` |
| `CL_PX_PER_IN` | macro | `src/css_length.c:21` | `#define CL_PX_PER_IN` |
| `cl_ctx_initial` | function | `src/css_length.c:100` | `cl_ctx cl_ctx_initial(void)` |
| `cl_em_refit` | function | `src/css_length.c:219` | `double cl_em_refit(double px, double em, double from_font_size, double font_size)` |
| `cl_font_size` | function | `src/css_length.c:56` | `static double cl_font_size(const cl_ctx *ctx)` |
| `cl_is_length_unit` | function | `src/css_length.c:167` | `int cl_is_length_unit(const char *unit, size_t unit_len)` |
| `cl_lp_used` | function | `src/css_length.c:395` | `double cl_lp_used(cl_lp lp, double basis)` |
| `cl_metric_or` | function | `src/css_length.c:67` | `static double cl_metric_or(double measured, double ratio, const cl_ctx *ctx)` |
| `cl_number` | function | `src/css_length.c:292` | `int cl_number(const char *s, double *out, const char **endp)` |
| `cl_parse_number` | function | `src/css_length.c:233` | `static int cl_parse_number(const char **pp, const char *end, double *out)` |
| `cl_resolve` | function | `src/css_length.c:377` | `cl_status cl_resolve(const char *value, const cl_ctx *ctx, double *out_px)` |
| `cl_resolve_core` | function | `src/css_length.c:309` | `static cl_status cl_resolve_core(const char *value, const cl_ctx *ctx, cl_lp *out)` |
| `cl_resolve_lp` | function | `src/css_length.c:391` | `cl_status cl_resolve_lp(const char *value, const cl_ctx *ctx, cl_lp *out)` |
| `cl_root_font_size` | function | `src/css_length.c:60` | `static double cl_root_font_size(const cl_ctx *ctx)` |
| `cl_unit_eq` | function | `src/css_length.c:30` | `static int cl_unit_eq(const char *unit, size_t len, const char *lit)` |
| `cl_unit_is_font_relative` | function | `src/css_length.c:174` | `int cl_unit_is_font_relative(const char *unit, size_t unit_len)` |
| `cl_unit_scale` | function | `src/css_length.c:117` | `cl_status cl_unit_scale(const char *unit, size_t unit_len,                         const cl_ctx *...` |
| `cl_viewport_scale` | function | `src/css_length.c:80` | `static int cl_viewport_scale(const char *u, size_t len, const cl_ctx *ctx, double *per)` |
| `know` | function | `src/css_length.c:7` | `* this module cannot know (real font metrics, the viewport) arrives through  * cl_ctx rather than...` |
| `CMQ_CM_PER_IN` | macro | `src/css_mq.c:23` | `#define CMQ_CM_PER_IN` |

Next: [SYMBOLS_p6.md](SYMBOLS_p6.md)
