# Symbols (page 5 of 15)
Previous: [SYMBOLS_p4.md](SYMBOLS_p4.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `url_omni_kind` | enum | `include/url.h:78` | `` |
| `url_parts` | struct | `include/url.h:129` | `` |
| `url_status` | enum | `include/url.h:32` | `` |
| `UTIL_H` | macro | `include/util.h:5` | `#define UTIL_H` |
| `fnv1a` | function | `include/util.h:67` | `static inline uint64_t fnv1a(const char *s, size_t n)` |
| `mem_contains_ci` | function | `include/util.h:43` | `static inline int mem_contains_ci(const void *hay, size_t hlen, const char *needle)` |
| `read_full` | function | `include/util.h:26` | `static inline int read_full(int fd, void *buf, size_t n)` |
| `utf8_seq_len` | function | `include/util.h:57` | `static inline size_t utf8_seq_len(unsigned char c)` |
| `write_full` | function | `include/util.h:15` | `static inline int write_full(int fd, const void *buf, size_t n)` |
| `FREEDOM_WEB_STORAGE_H` | macro | `include/web_storage.h:2` | `#define FREEDOM_WEB_STORAGE_H` |
| `WST_MAX_KEYS` | macro | `include/web_storage.h:18` | `#define WST_MAX_KEYS` |
| `WST_MAX_ORIGINS` | macro | `include/web_storage.h:17` | `#define WST_MAX_ORIGINS` |
| `WST_ORIGIN_MAX` | macro | `include/web_storage.h:20` | `#define WST_ORIGIN_MAX` |
| `WST_QUOTA` | macro | `include/web_storage.h:19` | `#define WST_QUOTA` |
| `full` | function | `include/web_storage.h:45` | `* validating it in full (wst_decode_check). Returns 0, or -1 when invalid (fn is then * never called). The one...` |
| `wst_db` | type_alias | `include/web_storage.h:21` | `typedef struct wst_db wst_db;` |
| `wst_decode_check` | function | `include/web_storage.h:37` | `int wst_decode_check(const char *blob, size_t len);` |
| `wst_encode` | function | `include/web_storage.h:33` | `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len);` |
| `wst_free` | function | `include/web_storage.h:28` | `void wst_free(wst_db *db);` |
| `wst_new` | function | `include/web_storage.h:25` | `wst_db *wst_new(void);` |
| `wst_origin_bytes` | function | `include/web_storage.h:59` | `size_t wst_origin_bytes(const wst_db *db, const char *origin);` |
| `wst_replace` | function | `include/web_storage.h:42` | `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len);` |
| `FREEDOM_WEBCAPS_H` | macro | `include/webcaps.h:2` | `#define FREEDOM_WEBCAPS_H` |
| `js` | type_alias | `include/webcaps.h:38` | `typedef struct wc_caps { /* leak-free (global): granted by user toggle or allow.conf presentation-trust. */ bool js;` |
| `js_mode` | type_alias | `include/webcaps.h:57` | `typedef struct wc_input { jsp_mode js_mode;` |
| `wc_caps` | struct | `include/webcaps.h:38` | `` |
| `wc_input` | struct | `include/webcaps.h:57` | `` |
| `FREEDOM_WEBFONT_H` | macro | `include/webfont.h:2` | `#define FREEDOM_WEBFONT_H` |
| `WF_DATA_URL_MAX` | macro | `include/webfont.h:29` | `#define WF_DATA_URL_MAX` |
| `WF_FAMILY_MAX` | macro | `include/webfont.h:20` | `#define WF_FAMILY_MAX` |
| `WF_FORMAT_MAX` | macro | `include/webfont.h:22` | `#define WF_FORMAT_MAX` |
| `WF_MAX_FACE_BYTES` | macro | `include/webfont.h:24` | `#define WF_MAX_FACE_BYTES` |
| `WF_MAX_REFS` | macro | `include/webfont.h:23` | `#define WF_MAX_REFS` |
| `WF_MAX_TOTAL_BYTES` | macro | `include/webfont.h:25` | `#define WF_MAX_TOTAL_BYTES` |
| `WF_URL_MAX` | macro | `include/webfont.h:21` | `#define WF_URL_MAX` |
| `boundaries` | function | `include/webfont.h:57` | `* boundaries (scan_inline accumulation, loader collection). */ void wf_ref_move(wf_ref *dst, wf_ref *src);` |
| `family` | type_alias | `include/webfont.h:30` | `typedef struct wf_ref { char family[WF_FAMILY_MAX];` |
| `here` | function | `include/webfont.h:38` | `* set with the decoded bytes owned here (freed by wf_list_free);` |
| `wf_list` | struct | `include/webfont.h:46` | `` |
| `wf_list_free` | function | `include/webfont.h:53` | `void wf_list_free(wf_list *l);` |
| `wf_name_hash` | function | `include/webfont.h:69` | `static inline unsigned wf_name_hash(const char *s, size_t n)` |
| `wf_ref` | struct | `include/webfont.h:31` | `` |
| `wf_scan` | function | `include/webfont.h:52` | `int wf_scan(const char *css, size_t len, wf_list *out);` |
| `wf_supported_format` | function | `include/webfont.h:60` | `int wf_supported_format(const char *fmt);` |
| `FREEDOM_WEBFONT_LOAD_H` | macro | `include/webfont_load.h:2` | `#define FREEDOM_WEBFONT_LOAD_H` |
| `WF_LOAD_MAX_FETCHES` | macro | `include/webfont_load.h:54` | `#define WF_LOAD_MAX_FETCHES` |
| `WF_LOAD_MAX_KEYS` | macro | `include/webfont_load.h:53` | `#define WF_LOAD_MAX_KEYS` |
| `WF_LOAD_TRIES_PER_KEY` | macro | `include/webfont_load.h:52` | `#define WF_LOAD_TRIES_PER_KEY` |
| `free` | function | `include/webfont_load.h:31` | `* free()), *out_status the HTTP status. Nonzero on refusal/error (fail-closed: * the face is skipped, never the...` |
| `skipped` | function | `include/webfont_load.h:47` | `* URLs are skipped (no base). Returns faces registered (>= 0) otherwise. */ int wf_load_document(wf_fetch_fn fetch...` |
| `wf_sheet` | struct | `include/webfont_load.h:24` | `` |
| `FREEDOM_WL_DISPLAY_H` | macro | `include/wl_display.h:6` | `#define FREEDOM_WL_DISPLAY_H` |
| `WD_NONE` | macro | `include/wl_display.h:11` | `#define WD_NONE` |
| `WD_OK` | macro | `include/wl_display.h:10` | `#define WD_OK` |
| `pure` | function | `include/wl_display.h:3` | `* wd_pick is pure (no I/O);` |
| `wd_pick` | function | `include/wl_display.h:16` | `int wd_pick(const char *const *names, size_t n, char *out, size_t cap);` |
| `wd_resolve_env` | function | `include/wl_display.h:20` | `int wd_resolve_env(void);` |
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
| `cx_box_layer` | function | `src/compositor.c:34` | `cx_layer cx_box_layer(const cx_style *s)` |
| `cx_forms_stacking_context` | function | `src/compositor.c:16` | `int cx_forms_stacking_context(const cx_style *s)` |
| `cx_item_compare` | function | `src/compositor.c:54` | `int cx_item_compare(const cx_item *a, const cx_item *b)` |
| `cx_sort` | function | `src/compositor.c:70` | `void cx_sort(cx_item *items, size_t n)` |
| `eff_z` | function | `src/compositor.c:50` | `static int eff_z(const cx_item *it)` |
| `AUTO_REJECT` | macro | `src/css.c:274` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css.c:276` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css.c:277` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css.c:275` | `#define AUTO_VALUE` |
| `CSS_ATTR_MARK` | macro | `src/css.c:1685` | `#define CSS_ATTR_MARK` |
| `CSS_ATTR_SEP` | macro | `src/css.c:1686` | `#define CSS_ATTR_SEP` |
| `CSS_DECL_SLOTS_MIN` | macro | `src/css.c:66` | `#define CSS_DECL_SLOTS_MIN` |
| `CSS_INIT_DECLS` | macro | `src/css.c:51` | `#define CSS_INIT_DECLS` |
| `CSS_INIT_RULES` | macro | `src/css.c:67` | `#define CSS_INIT_RULES` |
| `CSS_INIT_SELS` | macro | `src/css.c:50` | `#define CSS_INIT_SELS` |
| `CSS_INLINE_DECLS` | macro | `src/css.c:69` | `#define CSS_INLINE_DECLS` |
| `CSS_MAX_FONT_FACES` | macro | `src/css.c:164` | `#define CSS_MAX_FONT_FACES` |
| `CSS_MAX_RAW` | macro | `src/css.c:86` | `#define CSS_MAX_RAW` |
| `CSS_MEDIA_MAX_DEPTH` | macro | `src/css.c:4695` | `#define CSS_MEDIA_MAX_DEPTH` |
| `CSS_SELS_PER_GROUP` | macro | `src/css.c:68` | `#define CSS_SELS_PER_GROUP` |
| `CSS_VAR_POOL` | macro | `src/css.c:6003` | `#define CSS_VAR_POOL` |
| `CSS_WIDE_RESET` | macro | `src/css.c:221` | `#define CSS_WIDE_RESET` |
| `LIST` | function | `src/css.c:2516` | `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose...` |
| `NULL` | function | `src/css.c:6420` | `* Sheet can be NULL (inline style, no @keyframes). */ void css_resolve_anim_keyframes(css_style *...` |
| `P_META_CUSTOM` | macro | `src/css.c:82` | `#define P_META_CUSTOM` |
| `P_META_VARSRC` | macro | `src/css.c:83` | `#define P_META_VARSRC` |
| `add_rule` | function | `src/css.c:4411` | `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,                      siz...` |
| `anim_easing_iv` | function | `src/css.c:1186` | `static int anim_easing_iv(const char *tok)` |
| `apply_decl` | function | `src/css.c:5449` | `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_rule` | function | `src/css.c:6034` | `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_var_source` | function | `src/css.c:6007` | `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,         ...` |
| `at_is_media` | function | `src/css.c:4562` | `static int at_is_media(const char *s, size_t i, size_t n)` |
| `at_keyword` | function | `src/css.c:4573` | `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)` |
| `axis` | function | `src/css.c:1512` | `* bare center displaces it to the free axis (`center right` = x:right, y:center).  * Any other co...` |
| `bg_alpha_of` | function | `src/css.c:235` | `static int bg_alpha_of(const char *v)` |
| `block_end` | function | `src/css.c:4540` | `static size_t block_end(const char *s, size_t open, size_t n)` |
| `blur` | function | `src/css.c:1475` | `* consumes ONLY blur(Npx);` |
| `box_shadow_layer` | function | `src/css.c:1970` | `static int box_shadow_layer(const char *val, size_t len, int out[6])` |
| `caller` | function | `src/css.c:3402` | `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached...` |
| `cand_cmp` | function | `src/css.c:5942` | `static int cand_cmp(const void *pa, const void *pb)` |
| `cap` | function | `src/css.c:1744` | `* string past the cap (emit_content): a conforming declaration must not * count as a discard just because an icon...` |
| `collect_custom_props_scoped` | function | `src/css.c:4704` | `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,                 ...` |
| `column` | function | `src/css.c:2071` | `* column (`flex: 1 1 0%`);` |
| `computed_font_size` | function | `src/css.c:5925` | `static double computed_font_size(const css_style *o, const css_element *el)` |
| `consumer` | function | `src/css.c:5360` | `* consumer (shorthands, calc(), var() values) gets it with no context          * threaded through...` |
| `content_attr_of` | function | `src/css.c:5440` | `static const char *content_attr_of(const css_element *el, const char *name)` |
| `copy_trim` | function | `src/css.c:2231` | `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `csel_substr` | function | `src/css.c:4595` | `return known && csel_substr(val, "var(", 1);` |
| `css_cand` | struct | `src/css.c:5937` | `` |
| `css_computed_font_size_for_tag` | function | `src/css.c:5917` | `double css_computed_font_size_for_tag(const css_style *o, double inherited_px, const char *tag)` |
| `css_decl` | function | `src/css.c:90` | `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);` |
| `css_font_face_at` | function | `src/css.c:6456` | `int css_font_face_at(const css_sheet *sheet, size_t i,                      char *family, size_t ...` |
| `css_font_face_count` | function | `src/css.c:6452` | `size_t css_font_face_count(const css_sheet *sheet)` |
| `css_free` | function | `src/css.c:5418` | `void css_free(css_sheet *s)` |
| `css_keyframe_stop` | struct | `src/css.c:143` | `` |
| `css_match` | struct | `src/css.c:5931` | `` |
| `css_parse` | function | `src/css.c:5312` | `css_status css_parse(const char *text, size_t len, css_sheet **out)` |
| `css_parse_inline` | function | `src/css.c:6466` | `css_style css_parse_inline(const char *style, size_t len)` |
| `css_parse_logged` | function | `src/css.c:5326` | `css_status css_parse_logged(const char *text, size_t len, const css_media *media,                ...` |
| `css_parse_media` | function | `src/css.c:5316` | `css_status css_parse_media(const char *text, size_t len, const css_media *media,                 ...` |
| `css_parse_scoped` | function | `src/css.c:5321` | `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,                ...` |
| `css_resolve` | function | `src/css.c:6396` | `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,                   ...` |
| `css_resolve_el` | function | `src/css.c:6103` | `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,                          ...` |
| `css_resolve_el_ex` | function | `src/css.c:6112` | `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,                       ...` |
| `css_resolve_pseudo` | function | `src/css.c:6128` | `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)` |
| `css_rule` | struct | `src/css.c:101` | `` |
| `css_sheet` | struct | `src/css.c:103` | `` |
| `css_ua_heading_em` | function | `src/css.c:5912` | `double css_ua_heading_em(int level)` |
| `declaration` | function | `src/css.c:2006` | `* invalid layer drops the whole declaration (fail closed). `none` is an explicit  * no-shadow. ur...` |
| `download` | function | `src/css.c:4935` | `* the download (spec/webfont.md b3b). An empty src_url                      * simply never resolv...` |
| `drop_copy_text` | function | `src/css.c:4189` | `static void drop_copy_text(char *dst, size_t cap, const char *src)` |
| `drop_record` | function | `src/css.c:4208` | `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)` |
| `emit` | function | `src/css.c:63` | `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand...` |
| `emit_content` | function | `src/css.c:1668` | `static int emit_content(css_decl *dst, int cap, const char *str,                         char (*c...` |
| `emit_radius_corner` | function | `src/css.c:923` | `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)` |
| `emit_spacing` | function | `src/css.c:365` | `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `empty` | function | `src/css.c:1778` | `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and...` |
| `expand_animation` | function | `src/css.c:1214` | `static int expand_animation(const char *val, css_decl *dst, int cap)` |
| `expand_backdrop_filter` | function | `src/css.c:1478` | `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)` |
| `expand_background` | function | `src/css.c:252` | `static int expand_background(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_bg_image` | function | `src/css.c:247` | `static int expand_bg_image(const char *val, css_decl *dst, int cap,                            ch...` |
| `expand_bg_size` | function | `src/css.c:1628` | `static int expand_bg_size(const char *val, css_decl *dst, int cap)` |
| `expand_box2` | function | `src/css.c:289` | `static int expand_box2(const char *val, int slot_start, int slot_end,                        int ...` |
| `expand_box4` | function | `src/css.c:284` | `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,             ...` |
| `expand_clip_path` | function | `src/css.c:3155` | `static int expand_clip_path(const char *val, css_decl *dst, int cap)` |
| `expand_column_rule` | function | `src/css.c:1093` | `static int expand_column_rule(const char *val, css_decl *dst, int cap)` |
| `expand_columns` | function | `src/css.c:1037` | `static int expand_columns(const char *val, css_decl *dst, int cap)` |
| `expand_content` | function | `src/css.c:1774` | `static int expand_content(const char *val, css_decl *dst, int cap,                           char...` |
| `expand_flex` | function | `src/css.c:2092` | `static int expand_flex(const char *val, css_decl *dst, int cap)` |
| `expand_flex_flow` | function | `src/css.c:1071` | `static int expand_flex_flow(const char *val, css_decl *dst, int cap)` |
| `expand_gap` | function | `src/css.c:3052` | `static int expand_gap(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area` | function | `src/css.c:1879` | `static int expand_grid_area(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area_lines` | function | `src/css.c:1845` | `static int expand_grid_area_lines(const char *val, css_decl *dst, int cap)` |
| `expand_grid_areas` | function | `src/css.c:1817` | `static int expand_grid_areas(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_grid_line` | function | `src/css.c:1870` | `static int expand_grid_line(const char *val, css_decl *dst, int cap, int p_start, int p_end)` |
| `expand_grid_template` | function | `src/css.c:1918` | `static int expand_grid_template(const char *val, css_decl *dst, int cap,                         ...` |
| `expand_grid_template_cols` | function | `src/css.c:347` | `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `expand_outline` | function | `src/css.c:998` | `static int expand_outline(const char *val, css_decl *dst, int cap)` |
| `expand_shadow` | function | `src/css.c:366` | `static int expand_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_transform_list` | function | `src/css.c:2793` | `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);` |
| `expand_transform_origin` | function | `src/css.c:3020` | `static int expand_transform_origin(const char *val, css_decl *dst, int cap)` |
| `expand_valign` | function | `src/css.c:356` | `static int expand_valign(const char *val, css_decl *dst, int cap)` |
| `filter_paren_body` | function | `src/css.c:1134` | `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)` |
| `fold_font_relative` | function | `src/css.c:6072` | `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,                          ...` |
| `font_list_alias` | function | `src/css.c:3202` | `static void font_list_alias(const css_sheet *sheet, const char *ls, char *out, size_t cap)` |
| `font_list_norm` | function | `src/css.c:3236` | `static int font_list_norm(const char *val, char *out, size_t cap)` |
| `function` | function | `src/css.c:2797` | `* transform function (perspective/rotate3d/...), or unparseable syntax,  * rejects the WHOLE decl...` |
| `here` | function | `src/css.c:3891` | `* servers have no form here (fail closed). */ int o = csel_ci_eq(val, "none") ? CSS_SVG_PAINT_NONE : interp_color(val);` |
| `idx` | type_alias | `src/css.c:5937` | `typedef struct css_cand { int imp, espec, ord, idx;` |
| `interp_accent_color` | function | `src/css.c:715` | `static int interp_accent_color(const char *v)` |
| `interp_align` | function | `src/css.c:311` | `static int interp_align(const char *v)` |
| `interp_align_kw` | function | `src/css.c:2137` | `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` |
| `interp_appearance` | function | `src/css.c:587` | `static int interp_appearance(const char *v)` |
| `interp_aspect_ratio` | function | `src/css.c:362` | `static int interp_aspect_ratio(const char *v, int *num, int *den)` |
| `interp_backface_visibility` | function | `src/css.c:832` | `static int interp_backface_visibility(const char *v)` |
| `interp_bc_tok` | function | `src/css.c:933` | `static int interp_bc_tok(const char *t, int *o)` |
| `interp_bg` | function | `src/css.c:239` | `static int interp_bg(const char *v)` |
| `interp_bg_attachment` | function | `src/css.c:649` | `static int interp_bg_attachment(const char *v)` |
| `interp_bg_clip` | function | `src/css.c:634` | `static int interp_bg_clip(const char *v)` |
| `interp_bg_origin` | function | `src/css.c:642` | `static int interp_bg_origin(const char *v)` |
| `interp_bg_repeat` | function | `src/css.c:617` | `static int interp_bg_repeat(const char *v)` |
| `interp_bg_size` | function | `src/css.c:627` | `static int interp_bg_size(const char *v)` |
| `interp_border_collapse` | function | `src/css.c:495` | `static int interp_border_collapse(const char *v)` |
| `interp_border_style` | function | `src/css.c:855` | `static int interp_border_style(const char *v)` |
| `interp_box_orient` | function | `src/css.c:2168` | `static int interp_box_orient(const char *v)` |
| `interp_boxsizing` | function | `src/css.c:379` | `static int interp_boxsizing(const char *v)` |
| `interp_bs_tok` | function | `src/css.c:932` | `static int interp_bs_tok(const char *t, int *o)` |
| `interp_bw_tok` | function | `src/css.c:931` | `static int interp_bw_tok(const char *t, int *o)` |
| `interp_bwidth1` | function | `src/css.c:881` | `static int interp_bwidth1(const char *v)` |
| `interp_caption_side` | function | `src/css.c:536` | `static int interp_caption_side(const char *v)` |
| `interp_caret_color` | function | `src/css.c:575` | `static int interp_caret_color(const char *v)` |
| `interp_clear` | function | `src/css.c:392` | `static int interp_clear(const char *v)` |
| `interp_color` | function | `src/css.c:195` | `static int interp_color(const char *v)` |
| `interp_color_scheme` | function | `src/css.c:697` | `static int interp_color_scheme(const char *v)` |
| `interp_column_count` | function | `src/css.c:1014` | `static int interp_column_count(const char *v)` |
| `interp_column_width` | function | `src/css.c:1026` | `static int interp_column_width(const char *v)` |
| `interp_contain` | function | `src/css.c:662` | `static int interp_contain(const char *v)` |
| `interp_content_visibility` | function | `src/css.c:683` | `static int interp_content_visibility(const char *v)` |
| `interp_cursor` | function | `src/css.c:441` | `static int interp_cursor(const char *v)` |
| `interp_direction` | function | `src/css.c:363` | `static int interp_direction(const char *v)` |
| `interp_display` | function | `src/css.c:335` | `static int interp_display(const char *v)` |
| `interp_empty_cells` | function | `src/css.c:529` | `static int interp_empty_cells(const char *v)` |
| `interp_filter_deg` | function | `src/css.c:1119` | `static int interp_filter_deg(const char *s)` |
| `interp_filter_pct` | function | `src/css.c:1105` | `static int interp_filter_pct(const char *s)` |
| `interp_flex_basis` | function | `src/css.c:2058` | `static int interp_flex_basis(const char *v, int *out)` |
| `interp_flex_direction` | function | `src/css.c:2150` | `static int interp_flex_direction(const char *v)` |
| `interp_flex_factor` | function | `src/css.c:2048` | `static int interp_flex_factor(const char *v)` |
| `interp_flex_line_pack` | function | `src/css.c:2195` | `static int interp_flex_line_pack(const char *v)` |
| `interp_flex_wrap` | function | `src/css.c:2205` | `static int interp_flex_wrap(const char *v)` |
| `interp_float` | function | `src/css.c:385` | `static int interp_float(const char *v)` |
| `interp_font_kerning` | function | `src/css.c:767` | `static int interp_font_kerning(const char *v)` |
| `interp_font_stretch` | function | `src/css.c:782` | `static int interp_font_stretch(const char *v)` |
| `interp_font_variant` | function | `src/css.c:550` | `static int interp_font_variant(const char *v)` |
| `interp_fontfamily` | function | `src/css.c:353` | `static int interp_fontfamily(const char *v)` |
| `interp_fontsize_ex` | function | `src/css.c:315` | `static int interp_fontsize_ex(const char *v, int *abs_out)` |
| `interp_forced_color_adjust` | function | `src/css.c:726` | `static int interp_forced_color_adjust(const char *v)` |
| `interp_gap` | function | `src/css.c:339` | `static int interp_gap(const char *v)` |
| `interp_grid_flow` | function | `src/css.c:2213` | `static int interp_grid_flow(const char *v)` |
| `interp_hyphens` | function | `src/css.c:558` | `static int interp_hyphens(const char *v)` |
| `interp_image_rendering` | function | `src/css.c:690` | `static int interp_image_rendering(const char *v)` |
| `interp_isolation` | function | `src/css.c:656` | `static int interp_isolation(const char *v)` |
| `interp_justify` | function | `src/css.c:343` | `static int interp_justify(const char *v)` |
| `interp_len` | function | `src/css.c:294` | `static int interp_len(const char *v, int allow_auto, int *out)` |
| `interp_lineheight` | function | `src/css.c:319` | `static int interp_lineheight(const char *v)` |
| `interp_list_style_pos` | function | `src/css.c:761` | `static int interp_list_style_pos(const char *v)` |
| `interp_liststyle` | function | `src/css.c:364` | `static int interp_liststyle(const char *v)` |
| `interp_lp` | function | `src/css.c:298` | `static int interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_...` |
| `interp_mix_blend_mode` | function | `src/css.c:733` | `static int interp_mix_blend_mode(const char *v)` |
| `interp_object_fit` | function | `src/css.c:752` | `static int interp_object_fit(const char *v)` |
| `interp_opacity` | function | `src/css.c:355` | `static int interp_opacity(const char *v)` |
| `interp_overflow` | function | `src/css.c:409` | `static int interp_overflow(const char *v)` |
| `interp_overflow_wrap` | function | `src/css.c:487` | `static int interp_overflow_wrap(const char *v)` |
| `interp_overscroll_behavior` | function | `src/css.c:825` | `static int interp_overscroll_behavior(const char *v)` |
| `interp_pointer_events` | function | `src/css.c:605` | `static int interp_pointer_events(const char *v)` |
| `interp_position` | function | `src/css.c:370` | `static int interp_position(const char *v)` |
| `interp_print_color_adjust` | function | `src/css.c:720` | `static int interp_print_color_adjust(const char *v)` |
| `interp_resize` | function | `src/css.c:795` | `static int interp_resize(const char *v)` |
| `interp_scroll_behavior` | function | `src/css.c:803` | `static int interp_scroll_behavior(const char *v)` |
| `interp_style` | function | `src/css.c:327` | `static int interp_style(const char *v)` |
| `interp_table_layout` | function | `src/css.c:543` | `static int interp_table_layout(const char *v)` |
| `interp_tabsize` | function | `src/css.c:359` | `static int interp_tabsize(const char *v)` |
| `interp_text_overflow` | function | `src/css.c:473` | `static int interp_text_overflow(const char *v)` |
| `interp_text_rendering` | function | `src/css.c:774` | `static int interp_text_rendering(const char *v)` |
| `interp_textdeco` | function | `src/css.c:331` | `static int interp_textdeco(const char *v)` |
| `interp_textdeco_style` | function | `src/css.c:360` | `static int interp_textdeco_style(const char *v)` |
| `interp_textdeco_thickness` | function | `src/css.c:361` | `static int interp_textdeco_thickness(const char *v)` |
| `interp_texttransform` | function | `src/css.c:354` | `static int interp_texttransform(const char *v)` |
| `interp_time_ms` | function | `src/css.c:890` | `static int interp_time_ms(const char *v)` |
| `interp_transition_property` | function | `src/css.c:357` | `static int interp_transition_property(const char *v)` |
| `interp_user_select` | function | `src/css.c:566` | `static int interp_user_select(const char *v)` |
| `interp_visibility` | function | `src/css.c:402` | `static int interp_visibility(const char *v)` |
| `interp_weight` | function | `src/css.c:323` | `static int interp_weight(const char *v)` |
| `interp_whitespace` | function | `src/css.c:358` | `static int interp_whitespace(const char *v)` |
| `interp_word_break` | function | `src/css.c:479` | `static int interp_word_break(const char *v)` |
| `interpret_decls` | function | `src/css.c:4347` | `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,                ...` |
| `interpret_prop` | function | `src/css.c:4162` | `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,             ...` |
| `interpret_prop_dispatch` | function | `src/css.c:3414` | `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,    ...` |
| `is_anim_ident` | function | `src/css.c:1198` | `static int is_anim_ident(const char *tok)` |
| `item` | function | `src/css.c:1147` | `* timing list takes its first item (CSS Animations/Transitions 1: with one  * transition/animatio...` |
| `layer_register` | function | `src/css.c:4661` | `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,                      ...` |
| `len_rebase` | function | `src/css.c:5145` | `static char *len_rebase(const char *s, size_t n, const len_rebase_ctx *c, size_t *outlen)` |
| `len_rebase_ctx` | struct | `src/css.c:5103` | `` |
| `len_unit_px` | function | `src/css.c:5115` | `static double len_unit_px(const char *u, size_t len, const len_rebase_ctx *c)` |
| `lp_can_be_nonneg` | function | `src/css.c:303` | `static int lp_can_be_nonneg(int px_val, int pct_pm)` |
| `matrix` | function | `src/css.c:2431` | `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands...` |
| `next_ws_token` | function | `src/css.c:307` | `static int next_ws_token(const char **p, char *tok, size_t cap)` |
| `number` | function | `src/css.c:504` | `* number (no unit) as px (common in shorthand context like "10 5"). */ static int interp_border_s...` |
| `order` | function | `src/css.c:1440` | `* declaration order (dx, dy, optional blur >= 0);` |
| `origin_component` | function | `src/css.c:2994` | `static int origin_component(const char *tok, int axis, int *out)` |
| `page_view` | function | `src/css.c:5456` | `* the generated text reaches page_view (which materialises it as a synthetic * run);` |
| `parent` | function | `src/css.c:5489` | `* property from the parent (`inherit`), and an unset non-inherited one          * stands at its i...` |
| `parse_angle_deg` | function | `src/css.c:2790` | `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);` |
| `parse_block` | function | `src/css.c:4779` | `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,                  ...` |
| `parse_color` | function | `src/css.c:191` | `static int parse_color(const char *v)` |
| `parse_matrix6` | function | `src/css.c:2461` | `static int parse_matrix6(const char *p, size_t argn, double m6[6])` |
| `parse_num` | function | `src/css.c:180` | `static int parse_num(const char *s, double *out, const char **endp)` |
| `property` | function | `src/css.c:3111` | `* error drops the whole property (fail closed). */ static int expand_clip(const char *val, css_de...` |
| `pseudo_of` | function | `src/css.c:6119` | `static int pseudo_of(int which)` |
| `raw_add` | function | `src/css.c:4234` | `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)` |
| `rem_emit_px` | function | `src/css.c:5085` | `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)` |
| `rem_ident_ch` | function | `src/css.c:5067` | `static int rem_ident_ch(char c)` |
| `rem_num_starts_after` | function | `src/css.c:5075` | `static int rem_num_starts_after(char prev)` |
| `rem_px` | type_alias | `src/css.c:5103` | `typedef struct len_rebase_ctx { double rem_px;` |
| `rem_rebase` | function | `src/css.c:5211` | `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)` |
| `resolve_core` | function | `src/css.c:6139` | `static css_style resolve_core(const css_sheet *sheet, const css_element *el,                     ...` |
| `sel_list_comma` | function | `src/css.c:1963` | `static size_t sel_list_comma(const char *s, size_t i, size_t end);` |
| `selector_matches_root` | function | `src/css.c:2291` | `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m)` |
| `sentinel` | function | `src/css.c:3688` | `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);` |
| `sheet_index` | function | `src/css.c:5219` | `static void sheet_index(css_sheet *sh)` |
| `sheet_pools_reserve` | function | `src/css.c:4405` | `static void sheet_pools_reserve(css_sheet *sh)` |
| `sheet_rewind` | function | `src/css.c:5224` | `static void sheet_rewind(css_sheet *sh)` |
| `sheet_root_font_px` | function | `src/css.c:5269` | `static double sheet_root_font_px(const css_sheet *sh)` |
| `shorthand` | function | `src/css.c:3076` | `* An uninterpretable token drops the whole shorthand (fail closed). */ static int expand_place(co...` |
| `shorthand` | function | `src/css.c:3322` | `* generic bucket keeps the rest of the shorthand (same net effect as the  * font-family longhand ...` |
| `skip_at_rule` | function | `src/css.c:4524` | `static size_t skip_at_rule(const char *s, size_t i, size_t n)` |
| `slots` | function | `src/css.c:3573` | `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return...` |
| `split_top_args` | function | `src/css.c:2493` | `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,                ...` |
| `strip_comments` | function | `src/css.c:5277` | `static char *strip_comments(const char *text, size_t len, size_t *outlen)` |
| `strip_important` | function | `src/css.c:2244` | `static int strip_important(char *val)` |
| `supports_matches` | function | `src/css.c:4607` | `static int supports_matches(const char *s, size_t a, size_t b)` |
| `supports_selector_ok` | function | `src/css.c:4598` | `static int supports_selector_ok(void *ctx, const char *sel)` |
| `text` | function | `src/css.c:264` | `* source text (rem_rebase, see below) rather than by threading a context here.  *  * Viewport uni...` |
| `through` | function | `src/css.c:211` | `* at the two SHARED chokepoints every property funnels through (the generic  * dispatch tail, and...` |
| `tr_decompose` | function | `src/css.c:2438` | `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,                         in...` |
| `tr_mul` | function | `src/css.c:2418` | `static void tr_mul(double out[6], const double l[6], const double r[6])` |
| `translate3d` | function | `src/css.c:2523` | `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine  * renders z as nothing,...` |
| `translateX` | function | `src/css.c:2786` | `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc...` |
| `translateZ` | function | `src/css.c:2795` | `* translateZ(), rotateX(0) and rotateY(0) emit the identity (with the stacking * context Firefox builds);` |
| `var` | function | `src/css.c:2269` | `* cvr_resolve then substitutes var() references when a declaration's value is  * interpreted (par...` |
| `var` | function | `src/css.c:5287` | `* collected and forty var() declarations -- font sizes, widths, radii, the      * whole theme -- ...` |
| `wide_claim` | function | `src/css.c:4122` | `static int wide_claim(const char *prop, css_decl *dst, int cap,                       char (*urlt...` |
| `writing` | function | `src/css.c:3280` | `* Wide keywords claim BOTH slots without writing (inheritance then flows, as  * the tail does for...` |
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
| `AUTO_REJECT` | macro | `src/css_box.c:1196` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css_box.c:1198` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css_box.c:1202` | `#define AUTO_RESET_NONE` |

Next: [SYMBOLS_p6.md](SYMBOLS_p6.md)
