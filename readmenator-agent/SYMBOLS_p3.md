# Symbols (page 3 of 19)
Previous: [SYMBOLS_p2.md](SYMBOLS_p2.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `ANC_MAX_FRAGMENT` | macro | `include/anchor.h:23` | `#define ANC_MAX_FRAGMENT` |
| `ANC_MAX_HANDLES` | macro | `include/anchor.h:24` | `#define ANC_MAX_HANDLES` |
| `FREEDOM_ANCHOR_H` | macro | `include/anchor.h:2` | `#define FREEDOM_ANCHOR_H` |
| `anc_collect` | function | `include/anchor.h:50` | `size_t anc_collect(const dom_index *idx, dom_node_id target, dom_node_id *out, size_t cap, size_t *nsub);` |
| `anc_kind` | enum | `include/anchor.h:26` | `` |
| `anc_scroll_for` | function | `include/anchor.h:62` | `double anc_scroll_for(double top, double max_scroll);` |
| `anc_target_top` | function | `include/anchor.h:57` | `int anc_target_top(const jg_table *g, const dom_node_id *h, size_t n, size_t nsub, double *top);` |
| `fit` | function | `include/anchor.h:35` | `* result does not fit (out is then "" when cap > 0). */ size_t anc_percent_decode(const char *in, char *out, size_t...` |
| `FP_ACCEPT_HEADER_NAV` | macro | `include/anti_fp.h:40` | `#define FP_ACCEPT_HEADER_NAV` |
| `FP_ACCEPT_LANGUAGE` | macro | `include/anti_fp.h:33` | `#define FP_ACCEPT_LANGUAGE` |
| `FP_ACCEPT_LANGUAGE_HEADER` | macro | `include/anti_fp.h:34` | `#define FP_ACCEPT_LANGUAGE_HEADER` |
| `FP_SEC_FETCH_DEST_NAV` | macro | `include/anti_fp.h:45` | `#define FP_SEC_FETCH_DEST_NAV` |
| `FP_SEC_FETCH_MODE_NAV` | macro | `include/anti_fp.h:46` | `#define FP_SEC_FETCH_MODE_NAV` |
| `FP_SEC_FETCH_SITE_NONE` | macro | `include/anti_fp.h:47` | `#define FP_SEC_FETCH_SITE_NONE` |
| `FP_SEC_FETCH_USER_ON` | macro | `include/anti_fp.h:48` | `#define FP_SEC_FETCH_USER_ON` |
| `FP_TIMER_RESOLUTION_MS` | macro | `include/anti_fp.h:22` | `#define FP_TIMER_RESOLUTION_MS` |
| `FP_USER_AGENT` | macro | `include/anti_fp.h:31` | `#define FP_USER_AGENT` |
| `FREEDOM_ANTI_FP_H` | macro | `include/anti_fp.h:2` | `#define FREEDOM_ANTI_FP_H` |
| `domain` | function | `include/anti_fp.h:91` | `* registrable domain (eTLD+1). Same (session_key, domain) => same key (poisoning * is stable within a site);` |
| `fp_accept_language` | function | `include/anti_fp.h:58` | `const char *fp_accept_language(void);` |
| `fp_accept_language_header` | function | `include/anti_fp.h:59` | `const char *fp_accept_language_header(void);` |
| `fp_app_code_name` | function | `include/anti_fp.h:71` | `const char *fp_app_code_name(void);` |
| `fp_app_name` | function | `include/anti_fp.h:73` | `const char *fp_app_name(void);` |
| `fp_bucket_screen` | function | `include/anti_fp.h:83` | `void fp_bucket_screen(int w, int h, int *out_w, int *out_h);` |
| `fp_build_id` | function | `include/anti_fp.h:76` | `const char *fp_build_id(void);` |
| `fp_coarsen_time_ms` | function | `include/anti_fp.h:53` | `uint64_t fp_coarsen_time_ms(uint64_t raw_ms);` |
| `fp_cookie_enabled` | function | `include/anti_fp.h:79` | `int fp_cookie_enabled(void);` |
| `fp_device_memory_gb` | function | `include/anti_fp.h:64` | `int fp_device_memory_gb(void);` |
| `fp_hardware_concurrency` | function | `include/anti_fp.h:63` | `int fp_hardware_concurrency(void);` |
| `fp_max_touch_points` | function | `include/anti_fp.h:77` | `int fp_max_touch_points(void);` |
| `fp_on_line` | function | `include/anti_fp.h:78` | `int fp_on_line(void);` |
| `fp_origin_key` | function | `include/anti_fp.h:98` | `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain);` |
| `fp_oscpu` | function | `include/anti_fp.h:75` | `const char *fp_oscpu(void);` |
| `fp_perturb` | function | `include/anti_fp.h:88` | `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key);` |
| `fp_platform` | function | `include/anti_fp.h:61` | `const char *fp_platform(void);` |
| `fp_product` | function | `include/anti_fp.h:72` | `const char *fp_product(void);` |
| `fp_product_sub` | function | `include/anti_fp.h:74` | `const char *fp_product_sub(void);` |
| `fp_timer_resolution_ms` | function | `include/anti_fp.h:52` | `uint64_t fp_timer_resolution_ms(void);` |
| `fp_timezone` | function | `include/anti_fp.h:60` | `const char *fp_timezone(void);` |
| `fp_user_agent` | function | `include/anti_fp.h:57` | `const char *fp_user_agent(void);` |
| `fp_vendor` | function | `include/anti_fp.h:62` | `const char *fp_vendor(void);` |
| `probability` | function | `include/anti_fp.h:93` | `* keys with overwhelming probability (canvas/audio noise is not linkable across * sites, defeating cross-origin...` |
| `properties` | function | `include/anti_fp.h:67` | `* Legacy navigator properties (Hito 30b): normalized Firefox values shared by * js_env and the network layer so JS...` |
| `ABSENT` | function | `include/block_flow.h:26` | `* as ABSENT (0) rather than propagated: a poisoned length must not spread into * the geometry of the rest of the...` |
| `FREEDOM_BLOCK_FLOW_H` | macro | `include/block_flow.h:11` | `#define FREEDOM_BLOCK_FLOW_H` |
| `bf_collapse_n` | function | `include/block_flow.h:33` | `* bf_collapse_n((double[])` |
| `bf_margins_adjoin` | function | `include/block_flow.h:43` | `int bf_margins_adjoin(double border_px, double padding_px);` |
| `BB_MAX_PIXELS` | macro | `include/box_blur.h:12` | `#define BB_MAX_PIXELS` |
| `FREEDOM_BOX_BLUR_H` | macro | `include/box_blur.h:2` | `#define FREEDOM_BOX_BLUR_H` |
| `alpha` | function | `include/box_blur.h:27` | `* no pixel has alpha (nothing to blur), 1 otherwise. Everything outside rect stays 0 after the blur, * so blurring...` |
| `bb_box_sizes` | function | `include/box_blur.h:16` | `int bb_box_sizes(double sigma, int sizes[3]);` |
| `wider` | function | `include/box_blur.h:21` | `* BB_BOX_MAX px or wider (buffer untouched). One scratch copy of w x h bytes. */ int bb_blur_a8(unsigned char *buf...` |
| `BX_TAG_NAME_MAX` | macro | `include/box_style.h:33` | `#define BX_TAG_NAME_MAX` |
| `BX_TROLE_NONE` | function | `include/box_style.h:144` | `* BX_TROLE_NONE (an unrecognised element joins no table -- fail closed). */ bx_table_role bx_table_role_of(const...` |
| `FREEDOM_BOX_STYLE_H` | macro | `include/box_style.h:2` | `#define FREEDOM_BOX_STYLE_H` |
| `block` | function | `include/box_style.h:226` | `* indefinite containing block (cb_h < 0) the value behaves as auto: -1. * Without a percentage it is px_val...` |
| `box` | function | `include/box_style.h:115` | `* in_list nonzero when the block sits inside a list item: it then takes * the <li> box (zero margin), keeping items...` |
| `bx_background_layer` | function | `include/box_style.h:331` | `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h, double *out_x, double *out_y);` |
| `bx_bg_layer` | struct | `include/box_style.h:321` | `` |
| `bx_border_box_h` | function | `include/box_style.h:220` | `double bx_border_box_h(double declared_h, int border_box, double pad_t, double pad_b, double bord_t, double bord_b);` |
| `bx_border_span` | function | `include/box_style.h:286` | `double bx_border_span(double width_cap, int border_box, double pad_l, double pad_r, double bord_l, double bord_r);` |
| `bx_box` | struct | `include/box_style.h:50` | `` |
| `bx_content_cap` | function | `include/box_style.h:275` | `double bx_content_cap(double width_cap, int border_box, double pad_l, double pad_r, double bord_l, double bord_r);` |
| `bx_definite_content_h` | function | `include/box_style.h:241` | `double bx_definite_content_h(double h, double min_h, double max_h, int border_box, double v_edges);` |
| `bx_display` | enum | `include/box_style.h:35` | `` |
| `bx_display_name` | function | `include/box_style.h:156` | `const char *bx_display_name(bx_display d);` |
| `bx_edges` | struct | `include/box_style.h:46` | `` |
| `bx_flex_max_clamp` | function | `include/box_style.h:292` | `double bx_flex_max_clamp(double outer_basis, double mw_cap, int border_box, double pad_bord_h, double margin_h);` |
| `bx_flex_min_clamp` | function | `include/box_style.h:298` | `double bx_flex_min_clamp(double outer_basis, double min_w, int border_box, double pad_bord_h, double margin_h);` |
| `bx_hplace` | struct | `include/box_style.h:63` | `` |
| `bx_line_height_px` | function | `include/box_style.h:239` | `double bx_line_height_px(int line_scale, double font_px);` |
| `bx_lp_px` | function | `include/box_style.h:267` | `double bx_lp_px(int px_val, int pct_pm, double basis);` |
| `bx_replaced_box` | function | `include/box_style.h:206` | `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den, double avail_w, double *out_w, double *out_h);` |
| `bx_status` | enum | `include/box_style.h:56` | `` |
| `bx_table_role` | enum | `include/box_style.h:127` | `` |
| `bx_ua_tag` | enum | `include/box_style.h:84` | `` |
| `bx_width_cap` | function | `include/box_style.h:182` | `double bx_width_cap(int w_px, int w_pct, double avail_w);` |
| `bx_width_cap2` | function | `include/box_style.h:187` | `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w);` |
| `display` | type_alias | `include/box_style.h:49` | `typedef struct bx_box { bx_display display;` |
| `left` | type_alias | `include/box_style.h:46` | `typedef struct bx_edges { double top, right, bottom, left;` |
| `nat_h` | type_alias | `include/box_style.h:321` | `typedef struct bx_bg_layer { double nat_w, nat_h;` |
| `page` | function | `include/box_style.h:245` | `* instead of letting it extend the page (CSS 2.1 section 10.7 + 11.1.1). That * is the case unless BOTH overflow...` |
| `x_off` | type_alias | `include/box_style.h:63` | `typedef struct bx_hplace { double x_off;` |
| `BT_ALIGN_CENTER` | macro | `include/box_tree.h:59` | `#define BT_ALIGN_CENTER` |
| `BT_ALIGN_END` | macro | `include/box_tree.h:60` | `#define BT_ALIGN_END` |
| `BT_ALIGN_START` | macro | `include/box_tree.h:58` | `#define BT_ALIGN_START` |
| `BT_ALIGN_STRETCH` | macro | `include/box_tree.h:61` | `#define BT_ALIGN_STRETCH` |
| `BT_MAUTO_LEFT` | macro | `include/box_tree.h:64` | `#define BT_MAUTO_LEFT` |
| `BT_MAUTO_RIGHT` | macro | `include/box_tree.h:65` | `#define BT_MAUTO_RIGHT` |
| `BT_MAX_CHILDREN` | macro | `include/box_tree.h:36` | `#define BT_MAX_CHILDREN` |
| `BT_MAX_DEPTH` | macro | `include/box_tree.h:35` | `#define BT_MAX_DEPTH` |
| `BT_MAX_POSITIONED` | macro | `include/box_tree.h:42` | `#define BT_MAX_POSITIONED` |
| `BT_POS_ABSOLUTE` | macro | `include/box_tree.h:49` | `#define BT_POS_ABSOLUTE` |
| `BT_POS_FIXED` | macro | `include/box_tree.h:50` | `#define BT_POS_FIXED` |
| `BT_POS_RELATIVE` | macro | `include/box_tree.h:48` | `#define BT_POS_RELATIVE` |
| `BT_POS_STATIC` | macro | `include/box_tree.h:47` | `#define BT_POS_STATIC` |
| `BT_POS_STICKY` | macro | `include/box_tree.h:51` | `#define BT_POS_STICKY` |
| `FREEDOM_BOX_TREE_H` | macro | `include/box_tree.h:2` | `#define FREEDOM_BOX_TREE_H` |
| `bottom` | function | `include/box_tree.h:208` | `* bottom with auto top still anchors bottom (R8). * `placed` (may be NULL) marks which boxes have an in-flow rect in...` |
| `box_index` | type_alias | `include/box_tree.h:146` | `typedef struct bt_positioned { size_t box_index;` |
| `bt_box_hidden` | function | `include/box_tree.h:233` | `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid);` |
| `bt_containing_block` | function | `include/box_tree.h:268` | `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i, const double *box_x, const double *box_y...` |
| `bt_defer_roots` | function | `include/box_tree.h:291` | `size_t bt_defer_roots(const pv_box_def *boxes, size_t nbox, const bt_positioned *pos, size_t npos, const char...` |
| `bt_in_subtree` | function | `include/box_tree.h:239` | `int bt_in_subtree(const pv_box_def *boxes, size_t nbox, size_t root, size_t bid);` |
| `bt_node` | struct | `include/box_tree.h:67` | `` |
| `bt_oof_anchor` | function | `include/box_tree.h:253` | `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid);` |
| `bt_oof_root` | function | `include/box_tree.h:254` | `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid);` |
| `bt_positioned` | struct | `include/box_tree.h:146` | `` |
| `bt_status` | enum | `include/box_tree.h:153` | `` |
| `closed` | function | `include/box_tree.h:34` | `* fails closed (BT_ERR_RANGE) instead of overflowing the stack. */ #define BT_MAX_DEPTH 64u #define BT_MAX_CHILDREN...` |
| `display` | type_alias | `include/box_tree.h:66` | `typedef struct bt_node { bx_display display;` |
| `flow` | function | `include/box_tree.h:201` | `* position is where the box would have started in flow (CSS 2.2 §10.3.7/§10.6.4);` |
| `insets` | function | `include/box_tree.h:258` | `* minus the two insets (px half + per-mille half of cb), an auto/unset inset * counting 0, never below 0. *both (may...` |
| `line` | function | `include/box_tree.h:115` | `* its line (already resolved from align-self / the * container's align-items by the caller). */ /* this node as a...` |
| `node` | function | `include/box_tree.h:162` | `* node (x/y parent-relative, w/h border-box). display:none nodes get a zero rect and * take no space. The caller...` |
| `one` | function | `include/box_tree.h:99` | `* of forcing them all onto one (flex-wrap);` |
| `placed` | function | `include/box_tree.h:215` | `* box counts as placed (legacy behaviour). * bt_resolve_positioning delegates with NULL arrays (legacy behaviour)....` |
| `BROWSER_CLOSED_MAX` | macro | `include/browser.h:185` | `#define BROWSER_CLOSED_MAX` |
| `BROWSER_STATUS_DURATION_MS` | macro | `include/browser.h:25` | `#define BROWSER_STATUS_DURATION_MS` |
| `BROWSER_STATUS_MAX` | macro | `include/browser.h:24` | `#define BROWSER_STATUS_MAX` |
| `BROWSER_URL_MAX` | macro | `include/browser.h:21` | `#define BROWSER_URL_MAX` |
| `FREEDOM_BROWSER_H` | macro | `include/browser.h:2` | `#define FREEDOM_BROWSER_H` |
| `browser_abort_pending` | function | `include/browser.h:108` | `int browser_abort_pending(browser_state *bs);` |
| `browser_can_back` | function | `include/browser.h:126` | `int browser_can_back(const browser_state *bs);` |
| `browser_can_forward` | function | `include/browser.h:127` | `int browser_can_forward(const browser_state *bs);` |
| `browser_closed` | struct | `include/browser.h:186` | `` |
| `browser_closed_pop` | function | `include/browser.h:197` | `int browser_closed_pop(browser_closed *c, char *out, size_t cap);` |
| `browser_commit_pending` | function | `include/browser.h:107` | `void browser_commit_pending(browser_state *bs);` |
| `browser_current_url` | function | `include/browser.h:128` | `const char *browser_current_url(const browser_state *bs);` |
| `browser_doc_index` | function | `include/browser.h:116` | `int browser_doc_index(const browser_state *bs);` |
| `browser_entry_doc` | function | `include/browser.h:112` | `int browser_entry_doc(const browser_state *bs, size_t pos);` |
| `browser_entry_scroll` | function | `include/browser.h:123` | `double browser_entry_scroll(const browser_state *bs);` |
| `browser_free` | function | `include/browser.h:80` | `void browser_free(browser_state *bs);` |
| `browser_has_pending` | function | `include/browser.h:109` | `int browser_has_pending(const browser_state *bs);` |
| `browser_is_exception` | function | `include/browser.h:131` | `int browser_is_exception(const browser_state *bs, const char *host);` |
| `browser_set_entry_scroll` | function | `include/browser.h:122` | `void browser_set_entry_scroll(browser_state *bs, double scroll);` |
| `browser_set_page` | function | `include/browser.h:85` | `* browser_set_page() with the result. */ browser_status browser_navigate(browser_state *bs, const char *url);` |
| `browser_state` | struct | `include/browser.h:27` | `` |
| `browser_status` | enum | `include/browser.h:65` | `` |
| `browser_status_text` | function | `include/browser.h:182` | `const char *browser_status_text(const browser_state *bs, uint64_t now_ms);` |
| `browser_url_bar_delete_selection` | function | `include/browser.h:167` | `int browser_url_bar_delete_selection(browser_state *bs);` |
| `browser_url_bar_selection` | function | `include/browser.h:163` | `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len);` |
| `copied` | function | `include/browser.h:175` | `* copied (truncated to fit) and shown until now_ms reaches the expiry * (now_ms + BROWSER_STATUS_DURATION_MS). A...` |
| `one` | function | `include/browser.h:104` | `* A navigate while pending first aborts the pending one (the new one replaces it);` |
| `state` | function | `include/browser.h:76` | `* state (frees old history and page buffers). */ browser_status browser_init(browser_state *bs);` |
| `FREEDOM_CACHED_FETCH_H` | macro | `include/cached_fetch.h:2` | `#define FREEDOM_CACHED_FETCH_H` |
| `cf_attach_redirect_memory` | function | `include/cached_fetch.h:38` | `void cf_attach_redirect_memory(hc_store *store);` |
| `cf_set_store` | function | `include/cached_fetch.h:30` | `void cf_set_store(hc_store *store);` |
| `cf_store` | function | `include/cached_fetch.h:31` | `hc_store *cf_store(void);` |
| `CHL_BTN` | macro | `include/chrome_layout.h:29` | `#define CHL_BTN` |
| `CHL_BTN_GAP` | macro | `include/chrome_layout.h:30` | `#define CHL_BTN_GAP` |
| `CHL_DRAG_MIN` | macro | `include/chrome_layout.h:28` | `#define CHL_DRAG_MIN` |
| `CHL_DRAG_THRESHOLD` | macro | `include/chrome_layout.h:36` | `#define CHL_DRAG_THRESHOLD` |
| `CHL_FIND_BTN` | macro | `include/chrome_layout.h:118` | `#define CHL_FIND_BTN` |
| `CHL_FIND_COUNT_W` | macro | `include/chrome_layout.h:119` | `#define CHL_FIND_COUNT_W` |
| `CHL_FIND_FIELD_H` | macro | `include/chrome_layout.h:117` | `#define CHL_FIND_FIELD_H` |
| `CHL_FIND_FIELD_W` | macro | `include/chrome_layout.h:116` | `#define CHL_FIND_FIELD_W` |
| `CHL_FIND_H` | macro | `include/chrome_layout.h:115` | `#define CHL_FIND_H` |
| `CHL_ID_W` | macro | `include/chrome_layout.h:32` | `#define CHL_ID_W` |
| `CHL_MORE_W` | macro | `include/chrome_layout.h:35` | `#define CHL_MORE_W` |
| `CHL_NEWTAB_W` | macro | `include/chrome_layout.h:26` | `#define CHL_NEWTAB_W` |
| `CHL_PAD` | macro | `include/chrome_layout.h:19` | `#define CHL_PAD` |
| `CHL_STAR_MIN_URL` | macro | `include/chrome_layout.h:34` | `#define CHL_STAR_MIN_URL` |
| `CHL_STAR_W` | macro | `include/chrome_layout.h:33` | `#define CHL_STAR_W` |
| `CHL_TABBAR_H` | macro | `include/chrome_layout.h:17` | `#define CHL_TABBAR_H` |
| `CHL_TAB_CLOSE` | macro | `include/chrome_layout.h:24` | `#define CHL_TAB_CLOSE` |
| `CHL_TAB_CLOSE_MIN_W` | macro | `include/chrome_layout.h:25` | `#define CHL_TAB_CLOSE_MIN_W` |
| `CHL_TAB_GAP` | macro | `include/chrome_layout.h:23` | `#define CHL_TAB_GAP` |
| `CHL_TAB_MAX_W` | macro | `include/chrome_layout.h:22` | `#define CHL_TAB_MAX_W` |
| `CHL_TAB_MIN_W` | macro | `include/chrome_layout.h:21` | `#define CHL_TAB_MIN_W` |
| `CHL_TAB_TOP_GAP` | macro | `include/chrome_layout.h:20` | `#define CHL_TAB_TOP_GAP` |
| `CHL_TOOLBAR_H` | macro | `include/chrome_layout.h:18` | `#define CHL_TOOLBAR_H` |
| `CHL_URL_H` | macro | `include/chrome_layout.h:31` | `#define CHL_URL_H` |
| `CHL_WIN_BTN_W` | macro | `include/chrome_layout.h:27` | `#define CHL_WIN_BTN_W` |
| `FREEDOM_CHROME_LAYOUT_H` | macro | `include/chrome_layout.h:2` | `#define FREEDOM_CHROME_LAYOUT_H` |
| `chl_find_part` | enum | `include/chrome_layout.h:121` | `` |
| `chl_findbar` | struct | `include/chrome_layout.h:130` | `` |
| `chl_identity` | enum | `include/chrome_layout.h:143` | `` |
| `chl_identity_label` | function | `include/chrome_layout.h:162` | `const char *chl_identity_label(chl_identity id);` |
| `chl_layout` | struct | `include/chrome_layout.h:63` | `` |
| `chl_move_index` | function | `include/chrome_layout.h:103` | `int chl_move_index(int i, int from, int to);` |
| `chl_part` | enum | `include/chrome_layout.h:42` | `` |
| `chl_rect` | struct | `include/chrome_layout.h:40` | `` |
| `chl_rect_has` | function | `include/chrome_layout.h:91` | `int chl_rect_has(chl_rect r, double x, double y);` |
| `chl_status` | enum | `include/chrome_layout.h:38` | `` |
| `chl_tab_close_rect` | function | `include/chrome_layout.h:88` | `int chl_tab_close_rect(const chl_layout *l, int i, chl_rect *r);` |
| `chl_tab_drop_index` | function | `include/chrome_layout.h:99` | `int chl_tab_drop_index(const chl_layout *l, double x);` |
| `chl_tab_fallback_title` | function | `include/chrome_layout.h:111` | `void chl_tab_fallback_title(const char *url, char *out, size_t cap);` |
| `chl_tab_for_digit` | function | `include/chrome_layout.h:106` | `int chl_tab_for_digit(int digit, int tab_count);` |
| `chl_tab_rect` | function | `include/chrome_layout.h:87` | `int chl_tab_rect(const chl_layout *l, int i, chl_rect *r);` |
| `close` | type_alias | `include/chrome_layout.h:129` | `typedef struct chl_findbar { chl_rect bar, field, prev, next, count, close;` |
| `h` | type_alias | `include/chrome_layout.h:39` | `typedef struct chl_rect { double x, y, w, h;` |
| `width` | type_alias | `include/chrome_layout.h:62` | `typedef struct chl_layout { double width;` |
| `FREEDOM_COMPOSITOR_H` | macro | `include/compositor.h:2` | `#define FREEDOM_COMPOSITOR_H` |
| `cx_forms_stacking_context` | function | `include/compositor.h:60` | `int cx_forms_stacking_context(const cx_style *s);` |
| `cx_ink_reach` | function | `include/compositor.h:91` | `double cx_ink_reach(const int (*layers)[6], int n, int outline_w, int outline_offset);` |
| `cx_item` | struct | `include/compositor.h:69` | `` |
| `cx_item_compare` | function | `include/compositor.h:80` | `int cx_item_compare(const cx_item *a, const cx_item *b);` |
| `cx_layer` | enum | `include/compositor.h:27` | `` |
| `cx_sort` | function | `include/compositor.h:84` | `void cx_sort(cx_item *items, size_t n);` |
| `cx_span_visible` | function | `include/compositor.h:95` | `int cx_span_visible(double top, double h, double reach, double view_top, double view_h);` |
| `cx_style` | struct | `include/compositor.h:46` | `` |
| `layer` | type_alias | `include/compositor.h:69` | `typedef struct cx_item { cx_layer layer;` |
| `position` | type_alias | `include/compositor.h:46` | `typedef struct cx_style { int position;` |
| `CSS_BORDER_SPACING_MAX` | macro | `include/css.h:465` | `#define CSS_BORDER_SPACING_MAX` |
| `CSS_BORDER_W_MAX` | macro | `include/css.h:464` | `#define CSS_BORDER_W_MAX` |
| `CSS_BSHADOW_LAYERS` | macro | `include/css.h:473` | `#define CSS_BSHADOW_LAYERS` |
| `CSS_COLUMN_COUNT_MAX` | macro | `include/css.h:532` | `#define CSS_COLUMN_COUNT_MAX` |
| `CSS_CONTAIN_LAYOUT` | macro | `include/css.h:367` | `#define CSS_CONTAIN_LAYOUT` |
| `CSS_CONTAIN_PAINT` | macro | `include/css.h:369` | `#define CSS_CONTAIN_PAINT` |
| `CSS_CONTAIN_SIZE` | macro | `include/css.h:366` | `#define CSS_CONTAIN_SIZE` |
| `CSS_CONTAIN_STYLE` | macro | `include/css.h:368` | `#define CSS_CONTAIN_STYLE` |
| `CSS_DECO_LINE_THROUGH` | macro | `include/css.h:121` | `#define CSS_DECO_LINE_THROUGH` |
| `CSS_DECO_OVERLINE` | macro | `include/css.h:122` | `#define CSS_DECO_OVERLINE` |
| `CSS_DECO_UNDERLINE` | macro | `include/css.h:120` | `#define CSS_DECO_UNDERLINE` |
| `CSS_DISP_INLINE_OUTER` | macro | `include/css.h:74` | `#define CSS_DISP_INLINE_OUTER` |
| `CSS_DISP_INNER_MASK` | macro | `include/css.h:75` | `#define CSS_DISP_INNER_MASK` |
| `CSS_DROP_PROP_MAX` | macro | `include/css.h:1091` | `#define CSS_DROP_PROP_MAX` |
| `CSS_DROP_VAL_MAX` | macro | `include/css.h:1092` | `#define CSS_DROP_VAL_MAX` |
| `CSS_EM_MILLI_MAX` | macro | `include/css.h:522` | `#define CSS_EM_MILLI_MAX` |
| `CSS_FLEX_FACTOR_MAX` | macro | `include/css.h:466` | `#define CSS_FLEX_FACTOR_MAX` |
| `CSS_FONT_LIST_MAX` | macro | `include/css.h:107` | `#define CSS_FONT_LIST_MAX` |
| `CSS_FONT_SIZE_MAX` | macro | `include/css.h:528` | `#define CSS_FONT_SIZE_MAX` |
| `CSS_GAP_MAX` | macro | `include/css.h:88` | `#define CSS_GAP_MAX` |
| `CSS_GRAD_STOPS_MAX` | macro | `include/css.h:97` | `#define CSS_GRAD_STOPS_MAX` |
| `CSS_GRID_AREAS_MAX` | macro | `include/css.h:96` | `#define CSS_GRID_AREAS_MAX` |
| `CSS_GRID_COLS_MAX` | macro | `include/css.h:89` | `#define CSS_GRID_COLS_MAX` |
| `CSS_GRID_SPAN_MAX` | macro | `include/css.h:467` | `#define CSS_GRID_SPAN_MAX` |
| `CSS_GRID_TRACKS_MAX` | macro | `include/css.h:90` | `#define CSS_GRID_TRACKS_MAX` |
| `CSS_LEN_AUTO` | macro | `include/css.h:480` | `#define CSS_LEN_AUTO` |
| `CSS_LEN_END` | macro | `include/css.h:481` | `#define CSS_LEN_END` |
| `CSS_LEN_FIT_CONTENT` | macro | `include/css.h:490` | `#define CSS_LEN_FIT_CONTENT` |
| `CSS_LEN_IS_INTRINSIC` | macro | `include/css.h:493` | `#define CSS_LEN_IS_INTRINSIC(v)` |
| `CSS_LEN_MAX` | macro | `include/css.h:478` | `#define CSS_LEN_MAX` |
| `CSS_LEN_MAX_CONTENT` | macro | `include/css.h:489` | `#define CSS_LEN_MAX_CONTENT` |
| `CSS_LEN_MIN_CONTENT` | macro | `include/css.h:488` | `#define CSS_LEN_MIN_CONTENT` |
| `CSS_LEN_UNSET` | macro | `include/css.h:479` | `#define CSS_LEN_UNSET` |
| `CSS_LINE_ABS_BASE` | macro | `include/css.h:104` | `#define CSS_LINE_ABS_BASE` |
| `CSS_LINE_ABS_MAX_PX` | macro | `include/css.h:105` | `#define CSS_LINE_ABS_MAX_PX` |
| `CSS_LINE_MAX` | macro | `include/css.h:99` | `#define CSS_LINE_MAX` |
| `CSS_LINE_MIN` | macro | `include/css.h:98` | `#define CSS_LINE_MIN` |
| `CSS_MAX_ATTR_SEL` | macro | `include/css.h:591` | `#define CSS_MAX_ATTR_SEL` |
| `CSS_MAX_COMPOUNDS` | macro | `include/css.h:587` | `#define CSS_MAX_COMPOUNDS` |
| `CSS_MAX_KF_STOPS` | macro | `include/css.h:933` | `#define CSS_MAX_KF_STOPS` |
| `CSS_MAX_PSEUDO_SEL` | macro | `include/css.h:595` | `#define CSS_MAX_PSEUDO_SEL` |
| `CSS_MEDIA_DEFAULT_HEIGHT` | macro | `include/css.h:1044` | `#define CSS_MEDIA_DEFAULT_HEIGHT` |
| `CSS_MEDIA_DEFAULT_WIDTH` | macro | `include/css.h:1039` | `#define CSS_MEDIA_DEFAULT_WIDTH` |
| `CSS_NTH_MAX` | macro | `include/css.h:599` | `#define CSS_NTH_MAX` |
| `CSS_OBJPOS_PACK` | macro | `include/css.h:408` | `#define CSS_OBJPOS_PACK(x_pm, y_pm)` |
| `CSS_OBJPOS_X` | macro | `include/css.h:409` | `#define CSS_OBJPOS_X(p)` |
| `CSS_OBJPOS_Y` | macro | `include/css.h:410` | `#define CSS_OBJPOS_Y(p)` |
| `CSS_PCT_MAX` | macro | `include/css.h:516` | `#define CSS_PCT_MAX` |
| `CSS_PSEUDO_AFTER` | macro | `include/css.h:1233` | `#define CSS_PSEUDO_AFTER` |
| `CSS_PSEUDO_BEFORE` | macro | `include/css.h:1232` | `#define CSS_PSEUDO_BEFORE` |
| `CSS_PSEUDO_PLACEHOLDER` | macro | `include/css.h:1234` | `#define CSS_PSEUDO_PLACEHOLDER` |
| `CSS_SHADOW_MAX` | macro | `include/css.h:472` | `#define CSS_SHADOW_MAX` |
| `CSS_SPACING_MAX` | macro | `include/css.h:471` | `#define CSS_SPACING_MAX` |
| `CSS_SVG_PAINT_NONE` | macro | `include/css.h:106` | `#define CSS_SVG_PAINT_NONE` |
| `CSS_URL_MAX` | macro | `include/css.h:108` | `#define CSS_URL_MAX` |
| `FREEDOM_CSS_H` | macro | `include/css.h:2` | `#define FREEDOM_CSS_H` |
| `POINTER` | function | `include/css.h:235` | `* POINTER (shows the hand cursor already used for links) from every other value * (shows the default arrow);` |
| `color` | type_alias | `include/css.h:606` | `typedef struct css_style { int color;` |
| `container` | function | `include/css.h:674` | `* container (Display 3 section 2);` |
| `css_align` | enum | `include/css.h:36` | `` |
| `css_align_kw` | enum | `include/css.h:194` | `` |
| `css_appearance` | enum | `include/css.h:329` | `` |
| `css_attr` | struct | `include/css.h:1140` | `` |
| `css_backface` | enum | `include/css.h:457` | `` |
| `css_bg_attachment` | enum | `include/css.h:358` | `` |
| `css_bg_clip` | enum | `include/css.h:349` | `` |
| `css_bg_origin` | enum | `include/css.h:354` | `` |
| `css_bg_repeat` | enum | `include/css.h:340` | `` |
| `css_bg_size` | enum | `include/css.h:345` | `` |
| `css_border_collapse` | enum | `include/css.h:287` | `` |
| `css_border_style` | enum | `include/css.h:175` | `` |
| `css_box_sizing` | enum | `include/css.h:168` | `` |
| `css_caption_side` | enum | `include/css.h:299` | `` |
| `css_clear` | enum | `include/css.h:213` | `` |
| `css_color_scheme` | enum | `include/css.h:379` | `` |
| `css_column_fill` | enum | `include/css.h:448` | `` |
| `css_column_span` | enum | `include/css.h:453` | `` |
| `css_content_visibility` | enum | `include/css.h:371` | `` |
| `css_cursor` | enum | `include/css.h:240` | `` |
| `css_direction` | enum | `include/css.h:281` | `` |
| `css_display` | enum | `include/css.h:44` | `` |
| `css_drop` | struct | `include/css.h:1099` | `` |
| `css_drop_cause` | enum | `include/css.h:1086` | `` |
| `css_drop_log` | struct | `include/css.h:1111` | `` |
| `css_element` | struct | `include/css.h:1150` | `` |
| `css_empty_cells` | enum | `include/css.h:293` | `` |
| `css_flex_direction` | enum | `include/css.h:182` | `` |
| `css_flex_wrap` | enum | `include/css.h:188` | `` |
| `css_float` | enum | `include/css.h:207` | `` |
| `css_font_face_at` | function | `include/css.h:1274` | `int css_font_face_at(const css_sheet *sheet, size_t i, char *family, size_t fam_cap, char *src_url, size_t url_cap);` |
| `css_font_face_count` | function | `include/css.h:1273` | `size_t css_font_face_count(const css_sheet *sheet);` |
| `css_font_family` | enum | `include/css.h:126` | `` |
| `css_font_kerning` | enum | `include/css.h:416` | `` |
| `css_font_stretch` | enum | `include/css.h:425` | `` |
| `css_font_variant` | enum | `include/css.h:311` | `` |
| `css_forced_color_adjust` | enum | `include/css.h:387` | `` |
| `css_free` | function | `include/css.h:1126` | `void css_free(css_sheet *s);` |
| `css_grid_flow` | enum | `include/css.h:201` | `` |
| `css_hyphens` | enum | `include/css.h:317` | `` |
| `css_image_rendering` | enum | `include/css.h:375` | `` |
| `css_isolation` | enum | `include/css.h:362` | `` |
| `css_justify` | enum | `include/css.h:77` | `` |
| `css_list_pos` | enum | `include/css.h:412` | `` |
| `css_list_style` | enum | `include/css.h:149` | `` |
| `css_media` | struct | `include/css.h:1027` | `` |
| `css_mix_blend` | enum | `include/css.h:392` | `` |
| `css_object_fit` | enum | `include/css.h:400` | `` |
| `css_overflow` | enum | `include/css.h:230` | `` |
| `css_overscroll` | enum | `include/css.h:443` | `` |
| `css_pct_slot` | enum | `include/css.h:534` | `` |
| `css_pointer_events` | enum | `include/css.h:335` | `` |
| `css_position` | enum | `include/css.h:161` | `` |
| `css_print_color_adjust` | enum | `include/css.h:383` | `` |
| `css_resize` | enum | `include/css.h:431` | `` |
| `css_resolve_anim_keyframes` | function | `include/css.h:1282` | `void css_resolve_anim_keyframes(css_style *s, const css_sheet *sheet);` |
| `css_scroll_behavior` | enum | `include/css.h:435` | `` |
| `css_sel` | struct | `include/css.h:1025` | `` |
| `css_sheet` | type_alias | `include/css.h:1019` | `typedef struct css_sheet css_sheet;` |
| `css_sheet_uses_containers` | function | `include/css.h:1059` | `int css_sheet_uses_containers(const css_sheet *sheet);` |
| `css_sheet_uses_counters` | function | `include/css.h:1055` | `int css_sheet_uses_counters(const css_sheet *sheet);` |
| `css_status` | enum | `include/css.h:30` | `` |
| `css_style` | struct | `include/css.h:606` | `` |
| `css_table_layout` | enum | `include/css.h:305` | `` |
| `css_text_decoration_style` | enum | `include/css.h:274` | `` |
| `css_text_overflow` | enum | `include/css.h:253` | `` |
| `css_text_rendering` | enum | `include/css.h:420` | `` |
| `css_text_transform` | enum | `include/css.h:132` | `` |
| `css_touch_action` | enum | `include/css.h:439` | `` |
| `css_ua_heading_em` | function | `include/css.h:1258` | `double css_ua_heading_em(int level);` |
| `css_user_select` | enum | `include/css.h:323` | `` |
| `css_valign` | enum | `include/css.h:137` | `` |
| `css_visibility` | enum | `include/css.h:221` | `` |
| `css_white_space` | enum | `include/css.h:143` | `` |
| `css_word_break` | enum | `include/css.h:267` | `` |
| `cvr_table` | struct | `include/css.h:1222` | `` |
| `declared` | function | `include/css.h:898` | `* function was not declared (identity: 0 offset / 100% scale / 0deg). * Percentage translate arguments are not...` |
| `element` | function | `include/css.h:903` | `* so two different rules matching the same element (e.g. one setting * translate, a more specific one setting...` |
| `family` | function | `include/css.h:719` | `* LOCAL family (spec/text_shape.md section 7);` |
| `inherited_px` | function | `include/css.h:1246` | `* whose PARENT computes to inherited_px (<= 0 = unknown -> the CSS initial). * * Exported because the caller that...` |
| `name` | function | `include/css.h:1263` | `* name (NULL = not a heading). */ double css_computed_font_size_for_tag(const css_style *o, double inherited_px...` |
| `order` | function | `include/css.h:1129` | `* cascade order (specificity, then document order), then the element's own * inline_style (which wins)....` |
| `palette` | function | `include/css.h:1076` | `* so an inactive theme * palette (a dark palette in a light render) can never clobber the active one. *...` |
| `prefers_dark` | type_alias | `include/css.h:1026` | `typedef struct css_media { int prefers_dark;` |
| `prop` | type_alias | `include/css.h:1099` | `typedef struct css_drop { char prop[CSS_DROP_PROP_MAX];` |
| `scaleY` | function | `include/css.h:894` | `* scaleY() as a PERCENT of identity (100 = scale(1), matching font_scale's * convention);` |
| `slots` | function | `include/css.h:910` | `* parse time into ALL seven slots (singular matrices fail closed);` |
| `translate` | function | `include/css.h:893` | `* translate()/translateX()/translateY();` |
| `verbatim` | function | `include/css.h:92` | `* the quoted row strings verbatim (flex_layout parses them);` |
| `CAR_INLINE_SPEC` | macro | `include/css_atrule.h:18` | `#define CAR_INLINE_SPEC` |
| `CAR_LAYER_NAME_MAX` | macro | `include/css_atrule.h:17` | `#define CAR_LAYER_NAME_MAX` |
| `CAR_MAX_DEPTH` | macro | `include/css_atrule.h:15` | `#define CAR_MAX_DEPTH` |
| `CAR_MAX_LAYERS` | macro | `include/css_atrule.h:16` | `#define CAR_MAX_LAYERS` |
| `FREEDOM_CSS_ATRULE_H` | macro | `include/css_atrule.h:2` | `#define FREEDOM_CSS_ATRULE_H` |
| `car_effective_spec` | function | `include/css_atrule.h:44` | `int car_effective_spec(int spec, int layer, int important);` |
| `car_layer_rank` | function | `include/css_atrule.h:40` | `int car_layer_rank(car_layers *L, const char *name, size_t len);` |
| `car_layers` | struct | `include/css_atrule.h:31` | `` |
| `car_ops` | struct | `include/css_atrule.h:22` | `` |
| `car_supports` | function | `include/css_atrule.h:29` | `int car_supports(const char *s, size_t a, size_t b, const car_ops *ops);` |
| `CB_AUTO_REJECT` | macro | `include/css_box.h:10` | `#define CB_AUTO_REJECT` |
| `CB_AUTO_RESET` | macro | `include/css_box.h:12` | `#define CB_AUTO_RESET` |
| `CB_AUTO_RESET_NONE` | macro | `include/css_box.h:13` | `#define CB_AUTO_RESET_NONE` |
| `CB_AUTO_VALUE` | macro | `include/css_box.h:11` | `#define CB_AUTO_VALUE` |
| `FREEDOM_CSS_BOX_H` | macro | `include/css_box.h:2` | `#define FREEDOM_CSS_BOX_H` |
| `block` | function | `include/css_box.h:19` | `* For contexts with no element and no containing block (media query values). */ int cb_math_length_px(const char *v...` |
| `cb_emit_len` | function | `include/css_box.h:22` | `int cb_emit_len(css_decl *dst, int cap, int slot, const char *val, int allow_auto, int allow_neg);` |
| `cb_expand_box2` | function | `include/css_box.h:26` | `int cb_expand_box2(const char *val, int slot_start, int slot_end, int allow_auto, int allow_neg, css_decl *dst, int...` |
| `cb_expand_box4` | function | `include/css_box.h:24` | `int cb_expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg, css_decl *dst, int cap);` |
| `cb_expand_grid_template_cols` | function | `include/css_box.h:48` | `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap);` |
| `cb_interp_align` | function | `include/css_box.h:38` | `int cb_interp_align(const char *v);` |
| `cb_interp_display` | function | `include/css_box.h:44` | `int cb_interp_display(const char *v);` |
| `cb_interp_fontsize_ex` | function | `include/css_box.h:39` | `int cb_interp_fontsize_ex(const char *v, int *abs_out);` |
| `cb_interp_gap` | function | `include/css_box.h:45` | `int cb_interp_gap(const char *v);` |
| `cb_interp_gridcols` | function | `include/css_box.h:47` | `int cb_interp_gridcols(const char *v);` |
| `cb_interp_justify` | function | `include/css_box.h:46` | `int cb_interp_justify(const char *v);` |
| `cb_interp_len` | function | `include/css_box.h:21` | `int cb_interp_len(const char *v, int allow_auto, int *out);` |
| `cb_interp_lineheight` | function | `include/css_box.h:40` | `int cb_interp_lineheight(const char *v);` |
| `cb_interp_lp` | function | `include/css_box.h:28` | `int cb_interp_lp(const char *v, int allow_auto, int allow_pct, int *out_px, int *out_pm);` |
| `cb_interp_style` | function | `include/css_box.h:42` | `int cb_interp_style(const char *v);` |
| `cb_interp_textdeco` | function | `include/css_box.h:43` | `int cb_interp_textdeco(const char *v);` |
| `cb_interp_weight` | function | `include/css_box.h:41` | `int cb_interp_weight(const char *v);` |
| `cb_length_px` | function | `include/css_box.h:15` | `int cb_length_px(const char *v, double *px);` |
| `cb_lp_can_be_nonneg` | function | `include/css_box.h:36` | `int cb_lp_can_be_nonneg(int px_val, int pct_pm);` |
| `cb_next_ws_token` | function | `include/css_box.h:37` | `int cb_next_ws_token(const char **p, char *tok, size_t cap);` |
| `cb_value_em_milli` | function | `include/css_box.h:30` | `int cb_value_em_milli(const char *v);` |
| `rectangle` | function | `include/css_box.h:32` | `* rectangle (top, right, bottom, left): px[i] + pm[i]/1000 of the border box (height for * top/bottom, width for...` |
| `strings` | function | `include/css_box.h:50` | `* Quoted area strings (the grid-template shorthand's row half) are skipped. */ int...` |
| `CCH_CHAIN_MAX` | macro | `include/css_chain.h:26` | `#define CCH_CHAIN_MAX` |
| `CCH_NTH_MAX` | macro | `include/css_chain.h:28` | `#define CCH_NTH_MAX` |
| `CCH_SIB_MAX` | macro | `include/css_chain.h:27` | `#define CCH_SIB_MAX` |
| `FREEDOM_CSS_CHAIN_H` | macro | `include/css_chain.h:2` | `#define FREEDOM_CSS_CHAIN_H` |
| `box` | function | `include/css_chain.h:92` | `* generated box (css_resolve_pseudo) against the same element context. * font_size is el's own COMPUTED font-size...` |
| `cch_element_matches` | function | `include/css_chain.h:82` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel);` |
| `cch_path` | type_alias | `include/css_chain.h:69` | `typedef struct cch_path cch_path;` |
| `cch_path_free` | function | `include/css_chain.h:71` | `void cch_path_free(cch_path *pa);` |
| `cch_path_new` | function | `include/css_chain.h:70` | `cch_path *cch_path_new(void);` |
| `cvr_chain` | struct | `include/css_chain.h:51` | `` |
| `cvr_table` | struct | `include/css_chain.h:52` | `` |
| `lacks` | function | `include/css_chain.h:86` | `* the element lacks (csel's subj_req) is rejected before the ancestor chain is built: on a * query that scans a...` |
| `CC_COLOR_CURRENT` | macro | `include/css_color.h:59` | `#define CC_COLOR_CURRENT` |
| `CC_COLOR_TRANSPARENT` | macro | `include/css_color.h:60` | `#define CC_COLOR_TRANSPARENT` |
| `FREEDOM_CSS_COLOR_H` | macro | `include/css_color.h:2` | `#define FREEDOM_CSS_COLOR_H` |
| `b` | type_alias | `include/css_color.h:26` | `typedef struct cc_rgb { unsigned char r, g, b;` |
| `cc_pack` | function | `include/css_color.h:49` | `int cc_pack(cc_rgb c);` |
| `cc_rgb` | struct | `include/css_color.h:27` | `` |
| `cc_status` | enum | `include/css_color.h:31` | `` |
| `CCM_VALUE_MAX` | macro | `include/css_computed.h:17` | `#define CCM_VALUE_MAX` |
| `FREEDOM_CSS_COMPUTED_H` | macro | `include/css_computed.h:2` | `#define FREEDOM_CSS_COMPUTED_H` |
| `ccm_get` | function | `include/css_computed.h:29` | `size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap);` |
| `ccm_input` | struct | `include/css_computed.h:19` | `` |
| `ccm_property_count` | function | `include/css_computed.h:32` | `size_t ccm_property_count(void);` |
| `ccm_property_name` | function | `include/css_computed.h:33` | `const char *ccm_property_name(size_t i);` |
| `CNT_MAX_DECL` | macro | `include/css_counter.h:17` | `#define CNT_MAX_DECL` |
| `CNT_MAX_INSTANCES` | macro | `include/css_counter.h:18` | `#define CNT_MAX_INSTANCES` |
| `CNT_NAME_MAX` | macro | `include/css_counter.h:19` | `#define CNT_NAME_MAX` |
| `FREEDOM_CSS_COUNTER_H` | macro | `include/css_counter.h:9` | `#define FREEDOM_CSS_COUNTER_H` |
| `cnt_decl` | struct | `include/css_counter.h:21` | `` |
| `cnt_format` | function | `include/css_counter.h:49` | `size_t cnt_format(int style, long value, char *out, size_t cap);` |
| `cnt_hash` | function | `include/css_counter.h:34` | `unsigned cnt_hash(const char *name, size_t len);` |
| `cnt_increment` | function | `include/css_counter.h:57` | `void cnt_increment(cnt_state *s, int depth, const cnt_decl *d, int n);` |
| `cnt_is_marker` | function | `include/css_counter.h:45` | `int cnt_is_marker(const char *s);` |
| `cnt_leave` | function | `include/css_counter.h:60` | `void cnt_leave(cnt_state *s, int depth);` |
| `cnt_parse_content` | function | `include/css_counter.h:44` | `int cnt_parse_content(const char *val, char *out, size_t cap);` |
| `cnt_reset` | function | `include/css_counter.h:56` | `void cnt_reset(cnt_state *s, int depth, const cnt_decl *d, int n);` |
| `cnt_resolve` | function | `include/css_counter.h:67` | `size_t cnt_resolve(const cnt_state *s, const char *marker, cnt_attr_fn attr, void *ctx, char *out, size_t cap);` |
| `cnt_state` | type_alias | `include/css_counter.h:50` | `typedef struct cnt_state cnt_state;` |
| `cnt_state_free` | function | `include/css_counter.h:53` | `void cnt_state_free(cnt_state *s);` |
| `cnt_state_new` | function | `include/css_counter.h:52` | `cnt_state *cnt_state_new(void);` |
| `cnt_style` | enum | `include/css_counter.h:26` | `` |
| `name` | type_alias | `include/css_counter.h:20` | `typedef struct cnt_decl { unsigned name;` |
| `written` | function | `include/css_counter.h:37` | `* written (0 for `none`) or -1 when invalid. `dflt` is the value of an entry with no * integer: 0 for reset, 1 for...` |
| `CSS_INLINE_BG_URLS` | macro | `include/css_decl.h:28` | `#define CSS_INLINE_BG_URLS` |
| `CSS_MAX_BG_URLS` | macro | `include/css_decl.h:22` | `#define CSS_MAX_BG_URLS` |
| `CSS_MAX_CONTENT_URLS` | macro | `include/css_decl.h:23` | `#define CSS_MAX_CONTENT_URLS` |
| `CSS_MAX_KEYFRAMES` | macro | `include/css_decl.h:25` | `#define CSS_MAX_KEYFRAMES` |
| `CSS_MAX_KEYFRAME_DECLS` | macro | `include/css_decl.h:27` | `#define CSS_MAX_KEYFRAME_DECLS` |
| `CSS_MAX_KEYFRAME_STOPS` | macro | `include/css_decl.h:26` | `#define CSS_MAX_KEYFRAME_STOPS` |
| `CSS_POOL_HEADROOM` | macro | `include/css_decl.h:21` | `#define CSS_POOL_HEADROOM` |
| `CSS_POOL_INIT` | macro | `include/css_decl.h:20` | `#define CSS_POOL_INIT` |
| `CSS_WIDE_PROBE_DECLS` | macro | `include/css_decl.h:35` | `#define CSS_WIDE_PROBE_DECLS` |
| `FREEDOM_CSS_DECL_H` | macro | `include/css_decl.h:2` | `#define FREEDOM_CSS_DECL_H` |
| `contiguous` | function | `include/css_decl.h:65` | `* contiguous (dx,dy,color) so expand_shadow writes them as a group. */ P_FONTFAMILY, P_TEXTTRANSFORM...` |
| `css_decl` | struct | `include/css_decl.h:241` | `` |
| `order` | function | `include/css_decl.h:50` | `* The four margin slots are contiguous in CSS shorthand order (top,right,bottom, * left);` |
| `part` | function | `include/css_decl.h:216` | `* each P_CLIP_* edge adds to its px part (the other half of a <length-percentage>). */ P_CLIP_TOP_PM...` |
| `prop` | type_alias | `include/css_decl.h:240` | `typedef struct css_decl { int prop;` |
| `CG_LEN_UNSET` | macro | `include/css_gradient.h:22` | `#define CG_LEN_UNSET` |
| `FREEDOM_CSS_GRADIENT_H` | macro | `include/css_gradient.h:2` | `#define FREEDOM_CSS_GRADIENT_H` |
| `cg_expand_background` | function | `include/css_gradient.h:17` | `int cg_expand_background(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...` |
| `cg_expand_bg_image` | function | `include/css_gradient.h:15` | `int cg_expand_bg_image(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...` |
| `cg_first_url` | function | `include/css_gradient.h:13` | `int cg_first_url(const char *val, char *out, size_t outcap);` |
| `cg_parse_linear` | function | `include/css_gradient.h:55` | `int cg_parse_linear(const char *fn, int *angle, int *colors, int *positions);` |
| `cg_radial` | struct | `include/css_gradient.h:28` | `` |
| `cg_radial_len_px` | function | `include/css_gradient.h:41` | `double cg_radial_len_px(int enc, double dim);` |
| `cg_radial_shape` | enum | `include/css_gradient.h:23` | `` |
| `cg_radial_size` | enum | `include/css_gradient.h:24` | `` |
| `out` | function | `include/css_gradient.h:36` | `* Returns 1 and fills *out (defaults first) when seg is a valid prelude, 0 when seg is not * one (it is a colour...` |
| `shape` | type_alias | `include/css_gradient.h:28` | `typedef struct cg_radial { int shape;` |
| `width` | function | `include/css_gradient.h:21` | `* width (x, rx) or height (y, ry);` |
| `zero` | function | `include/css_gradient.h:45` | `* floored at a hair above zero (the spec paints the last colour for a degenerate size) and * never non-finite. Pure....` |
| `CI_COND_MAX` | macro | `include/css_import.h:20` | `#define CI_COND_MAX` |
| `CI_MAX_DEPTH` | macro | `include/css_import.h:21` | `#define CI_MAX_DEPTH` |
| `CI_MAX_PER_PAGE` | macro | `include/css_import.h:22` | `#define CI_MAX_PER_PAGE` |
| `CI_MAX_PER_SHEET` | macro | `include/css_import.h:23` | `#define CI_MAX_PER_SHEET` |
| `CI_URL_MAX` | macro | `include/css_import.h:19` | `#define CI_URL_MAX` |
| `FREEDOM_CSS_IMPORT_H` | macro | `include/css_import.h:2` | `#define FREEDOM_CSS_IMPORT_H` |
| `ci_balanced` | function | `include/css_import.h:45` | `int ci_balanced(const char *css, size_t len);` |
| `ci_import` | struct | `include/css_import.h:25` | `` |
| `ci_scan` | function | `include/css_import.h:36` | `size_t ci_scan(const char *css, size_t len, ci_import *out, size_t cap);` |
| `ci_wrap` | function | `include/css_import.h:41` | `int ci_wrap(const ci_import *im, char *open, size_t ocap, char *close, size_t ccap);` |
| `url` | type_alias | `include/css_import.h:24` | `typedef struct ci_import { char url[CI_URL_MAX];` |
| `url` | function | `include/css_import.h:55` | `* rewritten to url("ABS"), ABS = resolve(base, ref) (spec/css_import.md, "Rebase"). * Fragment-only, schemed, empty...` |
| `FREEDOM_CSS_INDEX_H` | macro | `include/css_index.h:11` | `#define FREEDOM_CSS_INDEX_H` |
| `cix_build` | function | `include/css_index.h:34` | `void cix_build(const css_sel *sels, size_t n, cix_index *idx);` |
| `cix_build_ptrs` | function | `include/css_index.h:37` | `void cix_build_ptrs(css_sel *const *sels, size_t n, cix_index *idx);` |
| `cix_entry` | struct | `include/css_index.h:18` | `` |
| `cix_free` | function | `include/css_index.h:40` | `void cix_free(cix_index *idx);` |
| `cix_index` | struct | `include/css_index.h:23` | `` |
| `index` | function | `include/css_index.h:44` | `* index (the caller then scans linearly). */ size_t cix_candidates(const cix_index *idx, const css_element *el...` |
| `key` | type_alias | `include/css_index.h:17` | `typedef struct cix_entry { uint64_t key;` |
| `CL_FALLBACK_CAP_RATIO` | macro | `include/css_length.h:65` | `#define CL_FALLBACK_CAP_RATIO` |
| `CL_FALLBACK_CH_RATIO` | macro | `include/css_length.h:64` | `#define CL_FALLBACK_CH_RATIO` |
| `CL_FALLBACK_EX_RATIO` | macro | `include/css_length.h:57` | `#define CL_FALLBACK_EX_RATIO` |
| `CL_FALLBACK_IC_RATIO` | macro | `include/css_length.h:66` | `#define CL_FALLBACK_IC_RATIO` |
| `CL_INITIAL_FONT_SIZE` | macro | `include/css_length.h:39` | `#define CL_INITIAL_FONT_SIZE` |
| `CL_MAX_TOKEN` | macro | `include/css_length.h:33` | `#define CL_MAX_TOKEN` |
| `CL_NORMAL_LINE_RATIO` | macro | `include/css_length.h:45` | `#define CL_NORMAL_LINE_RATIO` |
| `FREEDOM_CSS_LENGTH_H` | macro | `include/css_length.h:2` | `#define FREEDOM_CSS_LENGTH_H` |
| `cl_ctx` | struct | `include/css_length.h:91` | `` |
| `cl_is_length_unit` | function | `include/css_length.h:253` | `int cl_is_length_unit(const char *unit, size_t unit_len);` |

Next: [SYMBOLS_p4.md](SYMBOLS_p4.md)
