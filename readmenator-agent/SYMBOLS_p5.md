# Symbols (page 5 of 14)
Previous: [SYMBOLS_p4.md](SYMBOLS_p4.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `wf_supported_format` | function | `include/webfont.h:60` | `int wf_supported_format(const char *fmt);` |
| `FREEDOM_WEBFONT_LOAD_H` | macro | `include/webfont_load.h:2` | `#define FREEDOM_WEBFONT_LOAD_H` |
| `WF_LOAD_MAX_FETCHES` | macro | `include/webfont_load.h:54` | `#define WF_LOAD_MAX_FETCHES` |
| `WF_LOAD_MAX_KEYS` | macro | `include/webfont_load.h:53` | `#define WF_LOAD_MAX_KEYS` |
| `WF_LOAD_TRIES_PER_KEY` | macro | `include/webfont_load.h:52` | `#define WF_LOAD_TRIES_PER_KEY` |
| `free` | function | `include/webfont_load.h:31` | `* free()), *out_status the HTTP status. Nonzero on refusal/error (fail-closed: * the face is skipped, never the...` |
| `skipped` | function | `include/webfont_load.h:47` | `* URLs are skipped (no base). Returns faces registered (>= 0) otherwise. */ int wf_load_document(wf_fetch_fn fetch...` |
| `wf_sheet` | struct | `include/webfont_load.h:24` | `` |
| `FREEDOM_WS_HUB_H` | macro | `include/ws_hub.h:2` | `#define FREEDOM_WS_HUB_H` |
| `WH_CLOSE_ABNORMAL` | macro | `include/ws_hub.h:27` | `#define WH_CLOSE_ABNORMAL` |
| `WH_MAX` | macro | `include/ws_hub.h:21` | `#define WH_MAX` |
| `generation` | function | `include/ws_hub.h:50` | `* previous generation (before wh_close_all) are closed and dropped silently. */ void wh_on_notify(wh_hub *h...` |
| `wh_close` | function | `include/ws_hub.h:58` | `void wh_close(wh_hub *h, int id);` |
| `wh_close_all` | function | `include/ws_hub.h:61` | `void wh_close_all(wh_hub *h);` |
| `wh_count` | function | `include/ws_hub.h:73` | `size_t wh_count(const wh_hub *h);` |
| `wh_free` | function | `include/ws_hub.h:38` | `void wh_free(wh_hub *h);` |
| `wh_hub` | type_alias | `include/ws_hub.h:30` | `typedef struct wh_hub wh_hub;` |
| `wh_new` | function | `include/ws_hub.h:34` | `wh_hub *wh_new(void);` |
| `wh_notify_fd` | function | `include/ws_hub.h:41` | `int wh_notify_fd(const wh_hub *h);` |
| `wh_on_readable` | function | `include/ws_hub.h:70` | `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx);` |
| `wh_open_async` | function | `include/ws_hub.h:46` | `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg);` |
| `wh_poll_fds` | function | `include/ws_hub.h:65` | `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap);` |
| `wh_send` | function | `include/ws_hub.h:54` | `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary);` |
| `FREEDOM_ZOOM_H` | macro | `include/zoom.h:2` | `#define FREEDOM_ZOOM_H` |
| `ZM_DEFAULT_PCT` | macro | `include/zoom.h:23` | `#define ZM_DEFAULT_PCT` |
| `ZM_MAX_PCT` | macro | `include/zoom.h:22` | `#define ZM_MAX_PCT` |
| `ZM_MIN_PCT` | macro | `include/zoom.h:21` | `#define ZM_MIN_PCT` |
| `zm_apply` | function | `include/zoom.h:42` | `double zm_apply(double base_px, int pct);` |
| `zm_clamp` | function | `include/zoom.h:26` | `int zm_clamp(int pct);` |
| `zm_reset` | function | `include/zoom.h:35` | `int zm_reset(void);` |
| `zm_scale` | function | `include/zoom.h:38` | `double zm_scale(int pct);` |
| `zm_zoom_in` | function | `include/zoom.h:29` | `int zm_zoom_in(int pct);` |
| `zm_zoom_out` | function | `include/zoom.h:32` | `int zm_zoom_out(int pct);` |
| `fp_accept_language` | function | `src/anti_fp.c:27` | `const char *fp_accept_language(void)` |
| `fp_accept_language_header` | function | `src/anti_fp.c:31` | `const char *fp_accept_language_header(void)` |
| `fp_app_code_name` | function | `src/anti_fp.c:61` | `const char *fp_app_code_name(void)` |
| `fp_app_name` | function | `src/anti_fp.c:69` | `const char *fp_app_name(void)` |
| `fp_app_version` | function | `src/anti_fp.c:57` | `const char *fp_app_version(void)` |
| `fp_bucket_screen` | function | `src/anti_fp.c:99` | `void fp_bucket_screen(int w, int h, int *out_w, int *out_h)` |
| `fp_build_id` | function | `src/anti_fp.c:81` | `const char *fp_build_id(void)` |
| `fp_coarsen_time_ms` | function | `src/anti_fp.c:17` | `uint64_t fp_coarsen_time_ms(uint64_t raw_ms)` |
| `fp_cookie_enabled` | function | `src/anti_fp.c:93` | `int fp_cookie_enabled(void)` |
| `fp_device_memory_gb` | function | `src/anti_fp.c:51` | `int fp_device_memory_gb(void)` |
| `fp_hardware_concurrency` | function | `src/anti_fp.c:47` | `int fp_hardware_concurrency(void)` |
| `fp_max_touch_points` | function | `src/anti_fp.c:85` | `int fp_max_touch_points(void)` |
| `fp_on_line` | function | `src/anti_fp.c:89` | `int fp_on_line(void)` |
| `fp_origin_key` | function | `src/anti_fp.c:139` | `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain)` |
| `fp_oscpu` | function | `src/anti_fp.c:77` | `const char *fp_oscpu(void)` |
| `fp_perturb` | function | `src/anti_fp.c:128` | `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key)` |
| `fp_platform` | function | `src/anti_fp.c:39` | `const char *fp_platform(void)` |
| `fp_product` | function | `src/anti_fp.c:65` | `const char *fp_product(void)` |
| `fp_product_sub` | function | `src/anti_fp.c:73` | `const char *fp_product_sub(void)` |
| `fp_timezone` | function | `src/anti_fp.c:35` | `const char *fp_timezone(void)` |
| `fp_user_agent` | function | `src/anti_fp.c:23` | `const char *fp_user_agent(void)` |
| `fp_vendor` | function | `src/anti_fp.c:43` | `const char *fp_vendor(void)` |
| `splitmix64` | function | `src/anti_fp.c:121` | `static uint64_t splitmix64(uint64_t *state)` |
| `bf_collapse` | function | `src/block_flow.c:30` | `double bf_collapse(double a, double b)` |
| `bf_collapse_n` | function | `src/block_flow.c:15` | `double bf_collapse_n(const double *m, size_t n)` |
| `bf_margins_adjoin` | function | `src/block_flow.c:35` | `int bf_margins_adjoin(double border_px, double padding_px)` |
| `finite_or_zero` | function | `src/block_flow.c:11` | `static double finite_or_zero(double v)` |
| `bb_blur_a8` | function | `src/box_blur.c:41` | `int bb_blur_a8(unsigned char *buf, int w, int h, int stride, double sigma)` |
| `bb_box_sizes` | function | `src/box_blur.c:7` | `int bb_box_sizes(double sigma, int sizes[3])` |
| `box_line` | function | `src/box_blur.c:28` | `static void box_line(unsigned char *p, int n, int step, int bw, unsigned char *tmp)` |
| `variance` | function | `src/box_blur.c:10` | `* width w has variance (w^2 - 1) / 12): the ideal common width, rounded down * to an odd wl and up to wu = wl + 2...` |
| `BLOCK` | macro | `src/box_style.c:67` | `#define BLOCK` |
| `BX_DISPLAY_MAX` | macro | `src/box_style.c:25` | `#define BX_DISPLAY_MAX` |
| `BX_TAG_MAX` | macro | `src/box_style.c:24` | `#define BX_TAG_MAX` |
| `DISP_N` | macro | `src/box_style.c:259` | `#define DISP_N` |
| `EDG` | macro | `src/box_style.c:72` | `#define EDG(t, r, b, l)` |
| `IBLOCK` | macro | `src/box_style.c:69` | `#define IBLOCK` |
| `INLINE` | macro | `src/box_style.c:68` | `#define INLINE` |
| `LITEM` | macro | `src/box_style.c:70` | `#define LITEM` |
| `NONE` | macro | `src/box_style.c:71` | `#define NONE` |
| `TAG_N` | macro | `src/box_style.c:161` | `#define TAG_N` |
| `T_CAP` | macro | `src/box_style.c:80` | `#define T_CAP` |
| `T_CELL` | macro | `src/box_style.c:79` | `#define T_CELL` |
| `T_COL` | macro | `src/box_style.c:81` | `#define T_COL` |
| `T_GRP` | macro | `src/box_style.c:77` | `#define T_GRP` |
| `T_NO` | macro | `src/box_style.c:75` | `#define T_NO` |
| `T_ROW` | macro | `src/box_style.c:78` | `#define T_ROW` |
| `T_TBL` | macro | `src/box_style.c:76` | `#define T_TBL` |
| `ZERO` | macro | `src/box_style.c:73` | `#define ZERO` |
| `bg_size_component` | function | `src/box_style.c:408` | `static double bg_size_component(int px_val, int pct_pm, double area)` |
| `bx_background_layer` | function | `src/box_style.c:415` | `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h,                     ...` |
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
| `BT_LEN_AUTO` | macro | `src/box_tree.c:31` | `#define BT_LEN_AUTO` |
| `BT_WRAP_EPS` | macro | `src/box_tree.c:62` | `#define BT_WRAP_EPS` |
| `assign_doc_order` | function | `src/box_tree.c:505` | `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,                   ...` |
| `block` | function | `src/box_tree.c:566` | `* true block (same flow neighbourhood), strictly better than zeros. NULL      * placed keeps lega...` |
| `bt_box_hidden` | function | `src/box_tree.c:776` | `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)` |
| `bt_containing_block` | function | `src/box_tree.c:555` | `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i,                         ...` |
| `bt_defer_roots` | function | `src/box_tree.c:797` | `size_t bt_defer_roots(const pv_box_def *boxes, size_t nbox,                       const bt_positi...` |
| `bt_layout` | function | `src/box_tree.c:465` | `bt_status bt_layout(bt_node *root, double avail_w)` |
| `bt_nn` | function | `src/box_tree.c:58` | `static double bt_nn(double v)` |
| `bt_oof_anchor` | function | `src/box_tree.c:768` | `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)` |
| `bt_oof_avail` | function | `src/box_tree.c:789` | `double bt_oof_avail(int a, int a_pct, int b, int b_pct, double cb, int *both)` |
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
| `cx_box_layer` | function | `src/compositor.c:34` | `cx_layer cx_box_layer(const cx_style *s)` |
| `cx_forms_stacking_context` | function | `src/compositor.c:16` | `int cx_forms_stacking_context(const cx_style *s)` |
| `cx_item_compare` | function | `src/compositor.c:54` | `int cx_item_compare(const cx_item *a, const cx_item *b)` |
| `cx_sort` | function | `src/compositor.c:70` | `void cx_sort(cx_item *items, size_t n)` |
| `eff_z` | function | `src/compositor.c:50` | `static int eff_z(const cx_item *it)` |
| `AUTO_REJECT` | macro | `src/css.c:273` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css.c:275` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css.c:276` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css.c:274` | `#define AUTO_VALUE` |
| `CSS_ATTR_MARK` | macro | `src/css.c:1683` | `#define CSS_ATTR_MARK` |
| `CSS_ATTR_SEP` | macro | `src/css.c:1684` | `#define CSS_ATTR_SEP` |
| `CSS_DECL_SLOTS_MIN` | macro | `src/css.c:65` | `#define CSS_DECL_SLOTS_MIN` |
| `CSS_INIT_DECLS` | macro | `src/css.c:50` | `#define CSS_INIT_DECLS` |
| `CSS_INIT_RULES` | macro | `src/css.c:66` | `#define CSS_INIT_RULES` |
| `CSS_INIT_SELS` | macro | `src/css.c:49` | `#define CSS_INIT_SELS` |
| `CSS_INLINE_DECLS` | macro | `src/css.c:68` | `#define CSS_INLINE_DECLS` |
| `CSS_MAX_FONT_FACES` | macro | `src/css.c:163` | `#define CSS_MAX_FONT_FACES` |
| `CSS_MAX_RAW` | macro | `src/css.c:85` | `#define CSS_MAX_RAW` |
| `CSS_MEDIA_MAX_DEPTH` | macro | `src/css.c:4647` | `#define CSS_MEDIA_MAX_DEPTH` |
| `CSS_SELS_PER_GROUP` | macro | `src/css.c:67` | `#define CSS_SELS_PER_GROUP` |
| `CSS_VAR_POOL` | macro | `src/css.c:5925` | `#define CSS_VAR_POOL` |
| `CSS_WIDE_RESET` | macro | `src/css.c:220` | `#define CSS_WIDE_RESET` |
| `LIST` | function | `src/css.c:2514` | `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose...` |
| `NULL` | function | `src/css.c:6340` | `* Sheet can be NULL (inline style, no @keyframes). */ void css_resolve_anim_keyframes(css_style *...` |
| `P_META_CUSTOM` | macro | `src/css.c:81` | `#define P_META_CUSTOM` |
| `P_META_VARSRC` | macro | `src/css.c:82` | `#define P_META_VARSRC` |
| `add_rule` | function | `src/css.c:4363` | `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,                      siz...` |
| `anim_easing_iv` | function | `src/css.c:1184` | `static int anim_easing_iv(const char *tok)` |
| `apply_decl` | function | `src/css.c:5401` | `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_rule` | function | `src/css.c:5956` | `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_var_source` | function | `src/css.c:5929` | `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,         ...` |
| `at_is_media` | function | `src/css.c:4514` | `static int at_is_media(const char *s, size_t i, size_t n)` |
| `at_keyword` | function | `src/css.c:4525` | `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)` |
| `axis` | function | `src/css.c:1510` | `* bare center displaces it to the free axis (`center right` = x:right, y:center).  * Any other co...` |
| `bg_alpha_of` | function | `src/css.c:234` | `static int bg_alpha_of(const char *v)` |
| `block_end` | function | `src/css.c:4492` | `static size_t block_end(const char *s, size_t open, size_t n)` |
| `blur` | function | `src/css.c:1473` | `* consumes ONLY blur(Npx);` |
| `box_shadow_layer` | function | `src/css.c:1968` | `static int box_shadow_layer(const char *val, size_t len, int out[6])` |
| `caller` | function | `src/css.c:3358` | `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached...` |
| `cand_cmp` | function | `src/css.c:5864` | `static int cand_cmp(const void *pa, const void *pb)` |
| `cap` | function | `src/css.c:1742` | `* string past the cap (emit_content): a conforming declaration must not * count as a discard just because an icon...` |
| `collect_custom_props_scoped` | function | `src/css.c:4656` | `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,                 ...` |
| `column` | function | `src/css.c:2069` | `* column (`flex: 1 1 0%`);` |
| `computed_font_size` | function | `src/css.c:5848` | `static double computed_font_size(const css_style *o, const css_element *el)` |
| `consumer` | function | `src/css.c:5312` | `* consumer (shorthands, calc(), var() values) gets it with no context          * threaded through...` |
| `content_attr_of` | function | `src/css.c:5392` | `static const char *content_attr_of(const css_element *el, const char *name)` |
| `copy_trim` | function | `src/css.c:2229` | `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `csel_substr` | function | `src/css.c:4547` | `return known && csel_substr(val, "var(", 1);` |
| `css_cand` | struct | `src/css.c:5859` | `` |
| `css_decl` | function | `src/css.c:89` | `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);` |
| `css_font_face_at` | function | `src/css.c:6376` | `int css_font_face_at(const css_sheet *sheet, size_t i,                      char *family, size_t ...` |
| `css_font_face_count` | function | `src/css.c:6372` | `size_t css_font_face_count(const css_sheet *sheet)` |
| `css_free` | function | `src/css.c:5370` | `void css_free(css_sheet *s)` |
| `css_keyframe_stop` | struct | `src/css.c:142` | `` |
| `css_match` | struct | `src/css.c:5853` | `` |
| `css_parse` | function | `src/css.c:5264` | `css_status css_parse(const char *text, size_t len, css_sheet **out)` |
| `css_parse_inline` | function | `src/css.c:6386` | `css_style css_parse_inline(const char *style, size_t len)` |
| `css_parse_logged` | function | `src/css.c:5278` | `css_status css_parse_logged(const char *text, size_t len, const css_media *media,                ...` |
| `css_parse_media` | function | `src/css.c:5268` | `css_status css_parse_media(const char *text, size_t len, const css_media *media,                 ...` |
| `css_parse_scoped` | function | `src/css.c:5273` | `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,                ...` |
| `css_resolve` | function | `src/css.c:6316` | `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,                   ...` |
| `css_resolve_el` | function | `src/css.c:6025` | `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,                          ...` |
| `css_resolve_el_ex` | function | `src/css.c:6034` | `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,                       ...` |
| `css_resolve_pseudo` | function | `src/css.c:6050` | `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)` |
| `css_rule` | struct | `src/css.c:100` | `` |
| `css_sheet` | struct | `src/css.c:102` | `` |
| `declaration` | function | `src/css.c:2004` | `* invalid layer drops the whole declaration (fail closed). `none` is an explicit  * no-shadow. ur...` |
| `download` | function | `src/css.c:4887` | `* the download (spec/webfont.md b3b). An empty src_url                      * simply never resolv...` |
| `drop_copy_text` | function | `src/css.c:4141` | `static void drop_copy_text(char *dst, size_t cap, const char *src)` |
| `drop_record` | function | `src/css.c:4160` | `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)` |
| `emit` | function | `src/css.c:62` | `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand...` |
| `emit_content` | function | `src/css.c:1666` | `static int emit_content(css_decl *dst, int cap, const char *str,                         char (*c...` |
| `emit_radius_corner` | function | `src/css.c:921` | `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)` |
| `emit_spacing` | function | `src/css.c:364` | `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `empty` | function | `src/css.c:1776` | `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and...` |
| `expand_animation` | function | `src/css.c:1212` | `static int expand_animation(const char *val, css_decl *dst, int cap)` |
| `expand_backdrop_filter` | function | `src/css.c:1476` | `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)` |
| `expand_background` | function | `src/css.c:251` | `static int expand_background(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_bg_image` | function | `src/css.c:246` | `static int expand_bg_image(const char *val, css_decl *dst, int cap,                            ch...` |
| `expand_bg_size` | function | `src/css.c:1626` | `static int expand_bg_size(const char *val, css_decl *dst, int cap)` |
| `expand_box2` | function | `src/css.c:288` | `static int expand_box2(const char *val, int slot_start, int slot_end,                        int ...` |
| `expand_box4` | function | `src/css.c:283` | `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,             ...` |
| `expand_column_rule` | function | `src/css.c:1091` | `static int expand_column_rule(const char *val, css_decl *dst, int cap)` |
| `expand_columns` | function | `src/css.c:1035` | `static int expand_columns(const char *val, css_decl *dst, int cap)` |
| `expand_content` | function | `src/css.c:1772` | `static int expand_content(const char *val, css_decl *dst, int cap,                           char...` |
| `expand_flex` | function | `src/css.c:2090` | `static int expand_flex(const char *val, css_decl *dst, int cap)` |
| `expand_flex_flow` | function | `src/css.c:1069` | `static int expand_flex_flow(const char *val, css_decl *dst, int cap)` |
| `expand_gap` | function | `src/css.c:3050` | `static int expand_gap(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area` | function | `src/css.c:1877` | `static int expand_grid_area(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area_lines` | function | `src/css.c:1843` | `static int expand_grid_area_lines(const char *val, css_decl *dst, int cap)` |
| `expand_grid_areas` | function | `src/css.c:1815` | `static int expand_grid_areas(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_grid_line` | function | `src/css.c:1868` | `static int expand_grid_line(const char *val, css_decl *dst, int cap, int p_start, int p_end)` |
| `expand_grid_template` | function | `src/css.c:1916` | `static int expand_grid_template(const char *val, css_decl *dst, int cap,                         ...` |
| `expand_grid_template_cols` | function | `src/css.c:346` | `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `expand_outline` | function | `src/css.c:996` | `static int expand_outline(const char *val, css_decl *dst, int cap)` |
| `expand_shadow` | function | `src/css.c:365` | `static int expand_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_transform_list` | function | `src/css.c:2791` | `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);` |
| `expand_transform_origin` | function | `src/css.c:3018` | `static int expand_transform_origin(const char *val, css_decl *dst, int cap)` |
| `expand_valign` | function | `src/css.c:355` | `static int expand_valign(const char *val, css_decl *dst, int cap)` |
| `filter_paren_body` | function | `src/css.c:1132` | `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)` |
| `fold_font_relative` | function | `src/css.c:5994` | `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,                          ...` |
| `font_list_alias` | function | `src/css.c:3158` | `static void font_list_alias(const css_sheet *sheet, const char *ls, char *out, size_t cap)` |
| `font_list_norm` | function | `src/css.c:3192` | `static int font_list_norm(const char *val, char *out, size_t cap)` |
| `function` | function | `src/css.c:2795` | `* transform function (perspective/rotate3d/...), or unparseable syntax,  * rejects the WHOLE decl...` |
| `here` | function | `src/css.c:3843` | `* servers have no form here (fail closed). */ int o = csel_ci_eq(val, "none") ? CSS_SVG_PAINT_NONE : interp_color(val);` |
| `idx` | type_alias | `src/css.c:5859` | `typedef struct css_cand { int imp, espec, ord, idx;` |
| `interp_accent_color` | function | `src/css.c:714` | `static int interp_accent_color(const char *v)` |
| `interp_align` | function | `src/css.c:310` | `static int interp_align(const char *v)` |
| `interp_align_kw` | function | `src/css.c:2135` | `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` |
| `interp_appearance` | function | `src/css.c:586` | `static int interp_appearance(const char *v)` |
| `interp_aspect_ratio` | function | `src/css.c:361` | `static int interp_aspect_ratio(const char *v, int *num, int *den)` |
| `interp_backface_visibility` | function | `src/css.c:830` | `static int interp_backface_visibility(const char *v)` |
| `interp_bc_tok` | function | `src/css.c:931` | `static int interp_bc_tok(const char *t, int *o)` |
| `interp_bg` | function | `src/css.c:238` | `static int interp_bg(const char *v)` |
| `interp_bg_attachment` | function | `src/css.c:648` | `static int interp_bg_attachment(const char *v)` |
| `interp_bg_clip` | function | `src/css.c:633` | `static int interp_bg_clip(const char *v)` |
| `interp_bg_origin` | function | `src/css.c:641` | `static int interp_bg_origin(const char *v)` |
| `interp_bg_repeat` | function | `src/css.c:616` | `static int interp_bg_repeat(const char *v)` |
| `interp_bg_size` | function | `src/css.c:626` | `static int interp_bg_size(const char *v)` |
| `interp_border_collapse` | function | `src/css.c:494` | `static int interp_border_collapse(const char *v)` |
| `interp_border_style` | function | `src/css.c:853` | `static int interp_border_style(const char *v)` |
| `interp_box_orient` | function | `src/css.c:2166` | `static int interp_box_orient(const char *v)` |
| `interp_boxsizing` | function | `src/css.c:378` | `static int interp_boxsizing(const char *v)` |
| `interp_bs_tok` | function | `src/css.c:930` | `static int interp_bs_tok(const char *t, int *o)` |
| `interp_bw_tok` | function | `src/css.c:929` | `static int interp_bw_tok(const char *t, int *o)` |
| `interp_bwidth1` | function | `src/css.c:879` | `static int interp_bwidth1(const char *v)` |
| `interp_caption_side` | function | `src/css.c:535` | `static int interp_caption_side(const char *v)` |
| `interp_caret_color` | function | `src/css.c:574` | `static int interp_caret_color(const char *v)` |
| `interp_clear` | function | `src/css.c:391` | `static int interp_clear(const char *v)` |
| `interp_color` | function | `src/css.c:194` | `static int interp_color(const char *v)` |
| `interp_color_scheme` | function | `src/css.c:696` | `static int interp_color_scheme(const char *v)` |
| `interp_column_count` | function | `src/css.c:1012` | `static int interp_column_count(const char *v)` |
| `interp_column_width` | function | `src/css.c:1024` | `static int interp_column_width(const char *v)` |
| `interp_contain` | function | `src/css.c:661` | `static int interp_contain(const char *v)` |
| `interp_content_visibility` | function | `src/css.c:682` | `static int interp_content_visibility(const char *v)` |
| `interp_cursor` | function | `src/css.c:440` | `static int interp_cursor(const char *v)` |
| `interp_direction` | function | `src/css.c:362` | `static int interp_direction(const char *v)` |
| `interp_display` | function | `src/css.c:334` | `static int interp_display(const char *v)` |
| `interp_empty_cells` | function | `src/css.c:528` | `static int interp_empty_cells(const char *v)` |
| `interp_filter_deg` | function | `src/css.c:1117` | `static int interp_filter_deg(const char *s)` |
| `interp_filter_pct` | function | `src/css.c:1103` | `static int interp_filter_pct(const char *s)` |
| `interp_flex_basis` | function | `src/css.c:2056` | `static int interp_flex_basis(const char *v, int *out)` |
| `interp_flex_direction` | function | `src/css.c:2148` | `static int interp_flex_direction(const char *v)` |
| `interp_flex_factor` | function | `src/css.c:2046` | `static int interp_flex_factor(const char *v)` |
| `interp_flex_line_pack` | function | `src/css.c:2193` | `static int interp_flex_line_pack(const char *v)` |
| `interp_flex_wrap` | function | `src/css.c:2203` | `static int interp_flex_wrap(const char *v)` |
| `interp_float` | function | `src/css.c:384` | `static int interp_float(const char *v)` |
| `interp_font_kerning` | function | `src/css.c:765` | `static int interp_font_kerning(const char *v)` |
| `interp_font_stretch` | function | `src/css.c:780` | `static int interp_font_stretch(const char *v)` |
| `interp_font_variant` | function | `src/css.c:549` | `static int interp_font_variant(const char *v)` |
| `interp_fontfamily` | function | `src/css.c:352` | `static int interp_fontfamily(const char *v)` |
| `interp_fontsize_ex` | function | `src/css.c:314` | `static int interp_fontsize_ex(const char *v, int *abs_out)` |
| `interp_forced_color_adjust` | function | `src/css.c:725` | `static int interp_forced_color_adjust(const char *v)` |
| `interp_gap` | function | `src/css.c:338` | `static int interp_gap(const char *v)` |
| `interp_grid_flow` | function | `src/css.c:2211` | `static int interp_grid_flow(const char *v)` |
| `interp_hyphens` | function | `src/css.c:557` | `static int interp_hyphens(const char *v)` |
| `interp_image_rendering` | function | `src/css.c:689` | `static int interp_image_rendering(const char *v)` |
| `interp_isolation` | function | `src/css.c:655` | `static int interp_isolation(const char *v)` |
| `interp_justify` | function | `src/css.c:342` | `static int interp_justify(const char *v)` |
| `interp_len` | function | `src/css.c:293` | `static int interp_len(const char *v, int allow_auto, int *out)` |
| `interp_lineheight` | function | `src/css.c:318` | `static int interp_lineheight(const char *v)` |
| `interp_list_style_pos` | function | `src/css.c:759` | `static int interp_list_style_pos(const char *v)` |
| `interp_liststyle` | function | `src/css.c:363` | `static int interp_liststyle(const char *v)` |
| `interp_lp` | function | `src/css.c:297` | `static int interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_...` |
| `interp_mix_blend_mode` | function | `src/css.c:732` | `static int interp_mix_blend_mode(const char *v)` |
| `interp_object_fit` | function | `src/css.c:750` | `static int interp_object_fit(const char *v)` |
| `interp_opacity` | function | `src/css.c:354` | `static int interp_opacity(const char *v)` |
| `interp_overflow` | function | `src/css.c:408` | `static int interp_overflow(const char *v)` |
| `interp_overflow_wrap` | function | `src/css.c:486` | `static int interp_overflow_wrap(const char *v)` |
| `interp_overscroll_behavior` | function | `src/css.c:823` | `static int interp_overscroll_behavior(const char *v)` |
| `interp_pointer_events` | function | `src/css.c:604` | `static int interp_pointer_events(const char *v)` |
| `interp_position` | function | `src/css.c:369` | `static int interp_position(const char *v)` |
| `interp_print_color_adjust` | function | `src/css.c:719` | `static int interp_print_color_adjust(const char *v)` |
| `interp_resize` | function | `src/css.c:793` | `static int interp_resize(const char *v)` |
| `interp_scroll_behavior` | function | `src/css.c:801` | `static int interp_scroll_behavior(const char *v)` |
| `interp_style` | function | `src/css.c:326` | `static int interp_style(const char *v)` |
| `interp_table_layout` | function | `src/css.c:542` | `static int interp_table_layout(const char *v)` |
| `interp_tabsize` | function | `src/css.c:358` | `static int interp_tabsize(const char *v)` |
| `interp_text_overflow` | function | `src/css.c:472` | `static int interp_text_overflow(const char *v)` |
| `interp_text_rendering` | function | `src/css.c:772` | `static int interp_text_rendering(const char *v)` |
| `interp_textdeco` | function | `src/css.c:330` | `static int interp_textdeco(const char *v)` |
| `interp_textdeco_style` | function | `src/css.c:359` | `static int interp_textdeco_style(const char *v)` |
| `interp_textdeco_thickness` | function | `src/css.c:360` | `static int interp_textdeco_thickness(const char *v)` |
| `interp_texttransform` | function | `src/css.c:353` | `static int interp_texttransform(const char *v)` |
| `interp_time_ms` | function | `src/css.c:888` | `static int interp_time_ms(const char *v)` |
| `interp_transition_property` | function | `src/css.c:356` | `static int interp_transition_property(const char *v)` |
| `interp_user_select` | function | `src/css.c:565` | `static int interp_user_select(const char *v)` |
| `interp_visibility` | function | `src/css.c:401` | `static int interp_visibility(const char *v)` |
| `interp_weight` | function | `src/css.c:322` | `static int interp_weight(const char *v)` |
| `interp_whitespace` | function | `src/css.c:357` | `static int interp_whitespace(const char *v)` |
| `interp_word_break` | function | `src/css.c:478` | `static int interp_word_break(const char *v)` |
| `interpret_decls` | function | `src/css.c:4299` | `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,                ...` |
| `interpret_prop` | function | `src/css.c:4114` | `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,             ...` |
| `interpret_prop_dispatch` | function | `src/css.c:3370` | `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,    ...` |
| `is_anim_ident` | function | `src/css.c:1196` | `static int is_anim_ident(const char *tok)` |
| `item` | function | `src/css.c:1145` | `* timing list takes its first item (CSS Animations/Transitions 1: with one  * transition/animatio...` |
| `layer_register` | function | `src/css.c:4613` | `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,                      ...` |
| `len_rebase` | function | `src/css.c:5097` | `static char *len_rebase(const char *s, size_t n, const len_rebase_ctx *c, size_t *outlen)` |
| `len_rebase_ctx` | struct | `src/css.c:5055` | `` |
| `len_unit_px` | function | `src/css.c:5067` | `static double len_unit_px(const char *u, size_t len, const len_rebase_ctx *c)` |
| `lp_can_be_nonneg` | function | `src/css.c:302` | `static int lp_can_be_nonneg(int px_val, int pct_pm)` |
| `matrix` | function | `src/css.c:2429` | `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands...` |
| `next_ws_token` | function | `src/css.c:306` | `static int next_ws_token(const char **p, char *tok, size_t cap)` |
| `number` | function | `src/css.c:503` | `* number (no unit) as px (common in shorthand context like "10 5"). */ static int interp_border_s...` |
| `order` | function | `src/css.c:1438` | `* declaration order (dx, dy, optional blur >= 0);` |
| `origin_component` | function | `src/css.c:2992` | `static int origin_component(const char *tok, int axis, int *out)` |
| `page_view` | function | `src/css.c:5408` | `* the generated text reaches page_view (which materialises it as a synthetic * run);` |
| `parent` | function | `src/css.c:5441` | `* property from the parent (`inherit`), and an unset non-inherited one          * stands at its i...` |
| `parse_angle_deg` | function | `src/css.c:2788` | `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);` |
| `parse_block` | function | `src/css.c:4731` | `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,                  ...` |
| `parse_color` | function | `src/css.c:190` | `static int parse_color(const char *v)` |
| `parse_matrix6` | function | `src/css.c:2459` | `static int parse_matrix6(const char *p, size_t argn, double m6[6])` |
| `parse_num` | function | `src/css.c:179` | `static int parse_num(const char *s, double *out, const char **endp)` |
| `property` | function | `src/css.c:3104` | `* error drops the whole property (fail closed). */ static int expand_clip(const char *val, css_de...` |
| `pseudo_of` | function | `src/css.c:6041` | `static int pseudo_of(int which)` |
| `raw_add` | function | `src/css.c:4186` | `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)` |
| `rem_emit_px` | function | `src/css.c:5037` | `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)` |
| `rem_ident_ch` | function | `src/css.c:5019` | `static int rem_ident_ch(char c)` |
| `rem_num_starts_after` | function | `src/css.c:5027` | `static int rem_num_starts_after(char prev)` |
| `rem_px` | type_alias | `src/css.c:5055` | `typedef struct len_rebase_ctx { double rem_px;` |
| `rem_rebase` | function | `src/css.c:5163` | `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)` |
| `resolve_core` | function | `src/css.c:6061` | `static css_style resolve_core(const css_sheet *sheet, const css_element *el,                     ...` |
| `sel_list_comma` | function | `src/css.c:1961` | `static size_t sel_list_comma(const char *s, size_t i, size_t end);` |
| `selector_matches_root` | function | `src/css.c:2289` | `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m)` |
| `sentinel` | function | `src/css.c:3640` | `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);` |
| `sheet_index` | function | `src/css.c:5171` | `static void sheet_index(css_sheet *sh)` |
| `sheet_pools_reserve` | function | `src/css.c:4357` | `static void sheet_pools_reserve(css_sheet *sh)` |
| `sheet_rewind` | function | `src/css.c:5176` | `static void sheet_rewind(css_sheet *sh)` |
| `sheet_root_font_px` | function | `src/css.c:5221` | `static double sheet_root_font_px(const css_sheet *sh)` |
| `shorthand` | function | `src/css.c:3069` | `* An uninterpretable token drops the whole shorthand (fail closed). */ static int expand_place(co...` |
| `shorthand` | function | `src/css.c:3278` | `* generic bucket keeps the rest of the shorthand (same net effect as the  * font-family longhand ...` |
| `skip_at_rule` | function | `src/css.c:4476` | `static size_t skip_at_rule(const char *s, size_t i, size_t n)` |
| `slots` | function | `src/css.c:3528` | `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return...` |
| `split_top_args` | function | `src/css.c:2491` | `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,                ...` |
| `strip_comments` | function | `src/css.c:5229` | `static char *strip_comments(const char *text, size_t len, size_t *outlen)` |
| `strip_important` | function | `src/css.c:2242` | `static int strip_important(char *val)` |
| `supports_matches` | function | `src/css.c:4559` | `static int supports_matches(const char *s, size_t a, size_t b)` |
| `supports_selector_ok` | function | `src/css.c:4550` | `static int supports_selector_ok(void *ctx, const char *sel)` |
| `text` | function | `src/css.c:263` | `* source text (rem_rebase, see below) rather than by threading a context here.  *  * Viewport uni...` |
| `through` | function | `src/css.c:210` | `* at the two SHARED chokepoints every property funnels through (the generic  * dispatch tail, and...` |
| `tr_decompose` | function | `src/css.c:2436` | `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,                         in...` |
| `tr_mul` | function | `src/css.c:2416` | `static void tr_mul(double out[6], const double l[6], const double r[6])` |
| `translate3d` | function | `src/css.c:2521` | `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine  * renders z as nothing,...` |
| `translateX` | function | `src/css.c:2784` | `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc...` |
| `translateZ` | function | `src/css.c:2793` | `* translateZ(), rotateX(0) and rotateY(0) emit the identity (with the stacking * context Firefox builds);` |
| `var` | function | `src/css.c:2267` | `* cvr_resolve then substitutes var() references when a declaration's value is  * interpreted (par...` |
| `var` | function | `src/css.c:5239` | `* collected and forty var() declarations -- font sizes, widths, radii, the      * whole theme -- ...` |
| `wide_claim` | function | `src/css.c:4074` | `static int wide_claim(const char *prop, css_decl *dst, int cap,                       char (*urlt...` |
| `writing` | function | `src/css.c:3236` | `* Wide keywords claim BOTH slots without writing (inheritance then flows, as  * the tail does for...` |
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
| `AUTO_REJECT` | macro | `src/css_box.c:1158` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css_box.c:1160` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css_box.c:1164` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css_box.c:1159` | `#define AUTO_VALUE` |
| `CSS_CALC_MAX_DEPTH` | macro | `src/css_box.c:678` | `#define CSS_CALC_MAX_DEPTH` |
| `CSS_MATHFN_MAX_ARGS` | macro | `src/css_box.c:682` | `#define CSS_MATHFN_MAX_ARGS` |
| `RELATIVE` | function | `src/css_box.c:63` | `* or RELATIVE (of the inherited size). Absolute: px/pt/rem/viewport units and the * absolute keywords. Relative: em...` |
| `accepts` | function | `src/css_box.c:670` | `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further...` |
| `calc_eval_em` | function | `src/css_box.c:927` | `static int calc_eval_em(const char *v, size_t vlen, double *out_em)` |
| `calc_eval_full` | function | `src/css_box.c:913` | `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,            ...` |
| `calc_expr` | function | `src/css_box.c:894` | `static int calc_expr(calc_parser *p, calc_val *out, int depth)` |
| `calc_match_fn` | function | `src/css_box.c:707` | `static int calc_match_fn(calc_parser *p, const char *name)` |
| `calc_mathfn` | function | `src/css_box.c:749` | `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` |
| `calc_parser` | struct | `src/css_box.c:698` | `` |
| `calc_piecewise` | function | `src/css_box.c:734` | `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)` |
| `calc_skip_ws` | function | `src/css_box.c:700` | `static void calc_skip_ws(calc_parser *p)` |
| `calc_term` | function | `src/css_box.c:870` | `static int calc_term(calc_parser *p, calc_val *out, int depth)` |
| `calc_unwrap` | function | `src/css_box.c:935` | `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` |
| `calc_val` | struct | `src/css_box.c:697` | `` |
| `cb_copy_trim` | function | `src/css_box.c:25` | `static size_t cb_copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `cb_expand_box2` | function | `src/css_box.c:1332` | `int cb_expand_box2(const char *val, int slot_start, int slot_end,                        int allo...` |
| `cb_expand_grid_template_cols` | function | `src/css_box.c:591` | `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `cb_expand_grid_template_rows` | function | `src/css_box.c:614` | `int cb_expand_grid_template_rows(const char *val, css_decl *dst, int cap)` |
| `cb_interp_align` | function | `src/css_box.c:54` | `int cb_interp_align(const char *v)` |
| `cb_interp_display` | function | `src/css_box.c:213` | `int cb_interp_display(const char *v)` |
| `cb_interp_fontsize_ex` | function | `src/css_box.c:72` | `int cb_interp_fontsize_ex(const char *v, int *abs_out)` |
| `cb_interp_gap` | function | `src/css_box.c:288` | `int cb_interp_gap(const char *v)` |
| `cb_interp_justify` | function | `src/css_box.c:295` | `int cb_interp_justify(const char *v)` |
| `cb_interp_len` | function | `src/css_box.c:986` | `int cb_interp_len(const char *v, int allow_auto, int *out)` |
| `cb_interp_lineheight` | function | `src/css_box.c:145` | `int cb_interp_lineheight(const char *v)` |
| `cb_interp_lp` | function | `src/css_box.c:1085` | `int cb_interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_px, ...` |
| `cb_interp_style` | function | `src/css_box.c:183` | `int cb_interp_style(const char *v)` |
| `cb_interp_textdeco` | function | `src/css_box.c:193` | `int cb_interp_textdeco(const char *v)` |
| `cb_interp_weight` | function | `src/css_box.c:174` | `int cb_interp_weight(const char *v)` |
| `cb_length_px` | function | `src/css_box.c:49` | `int cb_length_px(const char *v, double *px)` |
| `cb_parse_num` | function | `src/css_box.c:13` | `static int cb_parse_num(const char *s, double *out, const char **endp)` |
| `cb_starts_with_ci` | function | `src/css_box.c:320` | `static int cb_starts_with_ci(const char *s, const char *pre)` |
| `cb_value_em_milli` | function | `src/css_box.c:1065` | `int cb_value_em_milli(const char *v)` |
| `cb_wide_keyword` | function | `src/css_box.c:18` | `static int cb_wide_keyword(const char *v)` |
| `count_one_repeat` | function | `src/css_box.c:364` | `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,                       ...` |
| `count_tracks` | function | `src/css_box.c:326` | `static int count_tracks(const char *s, size_t n)` |
| `expand_auto_fill` | function | `src/css_box.c:513` | `static int expand_auto_fill(const char *val, css_decl *dst, int cap)` |
| `interp_len` | function | `src/css_box.c:1261` | `* this file that might hand a token to interp_len (transitively: margin/padding/  * inset, flex-b...` |
| `min` | function | `src/css_box.c:768` | `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the...` |
| `pct_slot_of` | function | `src/css_box.c:1015` | `static int pct_slot_of(int slot)` |
| `px` | type_alias | `src/css_box.c:697` | `typedef struct calc_val { double px;` |
| `repeat` | function | `src/css_box.c:309` | `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill\|...) /...` |
| `term` | function | `src/css_box.c:1092` | `* the same expression and failed closed on the percentage term (its property * may not accept one);` |
| `track_min_of` | function | `src/css_box.c:475` | `static int track_min_of(const char *tok)` |
| `track_size_of` | function | `src/css_box.c:334` | `static int track_size_of(const char *tok)` |
| `walk_tracks` | function | `src/css_box.c:407` | `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)` |
| `CCH_ATTR_BUF` | macro | `src/css_chain.c:23` | `#define CCH_ATTR_BUF` |
| `CCH_CLASS_BUF` | macro | `src/css_chain.c:17` | `#define CCH_CLASS_BUF` |
| `CCH_CLASS_SPILL_MAX` | macro | `src/css_chain.c:21` | `#define CCH_CLASS_SPILL_MAX` |
| `CCH_ID_MAX` | macro | `src/css_chain.c:16` | `#define CCH_ID_MAX` |
| `CCH_MAX_ATTRS` | macro | `src/css_chain.c:22` | `#define CCH_MAX_ATTRS` |

Next: [SYMBOLS_p6.md](SYMBOLS_p6.md)
