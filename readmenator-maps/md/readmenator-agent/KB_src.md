# Subsystem: src (page 1 of 10)
Pages: [KB_src.md](KB_src.md), [KB_src_p2.md](KB_src_p2.md), [KB_src_p3.md](KB_src_p3.md), [KB_src_p4.md](KB_src_p4.md), [KB_src_p5.md](KB_src_p5.md), [KB_src_p6.md](KB_src_p6.md), [KB_src_p7.md](KB_src_p7.md), [KB_src_p8.md](KB_src_p8.md), [KB_src_p9.md](KB_src_p9.md), [KB_src_p10.md](KB_src_p10.md)

## src/anti_fp.c
- Layer: utility
- Language: c
- Symbols:
  - `fp_coarsen_time_ms` (function, line 17) `uint64_t fp_coarsen_time_ms(uint64_t raw_ms)`
  - `fp_user_agent` (function, line 23) `const char *fp_user_agent(void)`
  - `fp_accept_language` (function, line 27) `const char *fp_accept_language(void)`
  - `fp_accept_language_header` (function, line 31) `const char *fp_accept_language_header(void)`
  - `fp_timezone` (function, line 35) `const char *fp_timezone(void)`
  - `fp_platform` (function, line 39) `const char *fp_platform(void)`
  - `fp_vendor` (function, line 43) `const char *fp_vendor(void)`
  - `fp_hardware_concurrency` (function, line 47) `int fp_hardware_concurrency(void)`
  - `fp_device_memory_gb` (function, line 51) `int fp_device_memory_gb(void)`
  - `fp_app_version` (function, line 57) `const char *fp_app_version(void)`
  - `fp_app_code_name` (function, line 61) `const char *fp_app_code_name(void)`
  - `fp_product` (function, line 65) `const char *fp_product(void)`
  - `fp_app_name` (function, line 69) `const char *fp_app_name(void)`
  - `fp_product_sub` (function, line 73) `const char *fp_product_sub(void)`
  - `fp_oscpu` (function, line 77) `const char *fp_oscpu(void)`
  - `fp_build_id` (function, line 81) `const char *fp_build_id(void)`
  - `fp_max_touch_points` (function, line 85) `int fp_max_touch_points(void)`
  - `fp_on_line` (function, line 89) `int fp_on_line(void)`
  - `fp_cookie_enabled` (function, line 93) `int fp_cookie_enabled(void)`
  - `fp_bucket_screen` (function, line 99) `void fp_bucket_screen(int w, int h, int *out_w, int *out_h)`
  - `splitmix64` (function, line 121) `static uint64_t splitmix64(uint64_t *state)`
  - `fp_perturb` (function, line 128) `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key)`
  - `fp_origin_key` (function, line 139) `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain)`
- Depends on: `include/anti_fp.h`

## src/block_flow.c
- Doc: block_flow (bf_) -- vertical margin collapsing.
- Layer: utility
- Language: c
- Symbols:
  - `finite_or_zero` (function, line 11) `static double finite_or_zero(double v)`
  - `bf_collapse_n` (function, line 15) `double bf_collapse_n(const double *m, size_t n)`
  - `bf_collapse` (function, line 30) `double bf_collapse(double a, double b)`
  - `bf_margins_adjoin` (function, line 35) `int bf_margins_adjoin(double border_px, double padding_px)`
- Depends on: `include/block_flow.h`

## src/box_blur.c
- Doc: box_line: One box pass of odd width bw over n samples spaced `step` apart, through tmp * (n bytes).
- Layer: utility
- Language: c
- Symbols:
  - `bb_box_sizes` (function, line 7) `int bb_box_sizes(double sigma, int sizes[3])`
  - `box_line` (function, line 28) `static void box_line(unsigned char *p, int n, int step, int bw, unsigned char *tmp)`
  - `bb_blur_a8` (function, line 41) `int bb_blur_a8(unsigned char *buf, int w, int h, int stride, double sigma)`
  - `bb_ink_rect` (function, line 57) `int bb_ink_rect(const unsigned char *argb, int w, int h, int stride, double sigma, int rect[4])`
  - `variance` (function, line 10) `* width w has variance (w^2 - 1) / 12): the ideal common width, rounded down * to an odd wl and up to wu = wl + 2...`
- Depends on: `include/box_blur.h`

## src/box_style.c
- Doc: tag_row: One row of the user-agent sheet.
- Layer: utility
- Language: c
- Symbols:
  - `tag_row` (struct, line 61)
  - `disp_row` (struct, line 241)
  - `is_ws` (function, line 31) `static int is_ws(char c)`
  - `copy_lower_trim` (function, line 37) `static int copy_lower_trim(const char *in, char *out, size_t out_size)`
  - `name_cmp` (function, line 50) `static int name_cmp(const void *key, const void *elem)`
  - `bx_default_for_tag` (function, line 163) `bx_box bx_default_for_tag(const char *tag)`
  - `bx_table_role_of` (function, line 171) `bx_table_role bx_table_role_of(const char *tag, css_display display)`
  - `bx_ua_of_tag` (function, line 210) `bx_ua_tag bx_ua_of_tag(const char *tag)`
  - `bx_default_for_ua` (function, line 219) `bx_box bx_default_for_ua(bx_ua_tag id)`
  - `bx_block_ua_box` (function, line 225) `bx_box bx_block_ua_box(int heading_level, int in_list, bx_ua_tag ua)`
  - `bx_parse_display` (function, line 261) `bx_status bx_parse_display(const char *token, bx_display *out)`
  - `bx_place` (function, line 271) `bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,
                ...`
  - `bx_width_cap` (function, line 288) `double bx_width_cap(int w_px, int w_pct, double avail_w)`
  - `bx_width_cap2` (function, line 313) `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w)`
  - `bx_replaced_box` (function, line 321) `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den,
                    doub...`
  - `bx_border_box_h` (function, line 335) `double bx_border_box_h(double declared_h, int border_box,
                       double pad_t, do...`
  - `bx_pct_block_size` (function, line 346) `double bx_pct_block_size(int px_val, int pct_pm, double cb_h)`
  - `bx_definite_content_h` (function, line 352) `double bx_definite_content_h(double h, double min_h, double max_h,
                             i...`
  - `bx_content_clipped` (function, line 361) `int bx_content_clipped(int overflow_x, int overflow_y)`
  - `bx_lp_px` (function, line 367) `double bx_lp_px(int px_val, int pct_pm, double basis)`
  - `bx_content_cap` (function, line 378) `double bx_content_cap(double width_cap, int border_box,
                      double pad_l, doubl...`
  - `bx_flex_min_clamp` (function, line 389) `double bx_flex_min_clamp(double outer_basis, double min_w, int border_box,
                      ...`
  - `bx_border_span` (function, line 396) `double bx_border_span(double width_cap, int border_box,
                      double pad_l, doubl...`
  - `bg_size_component` (function, line 408) `static double bg_size_component(int px_val, int pct_pm, double area)`
  - `bx_background_layer` (function, line 415) `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h,
                    ...`
  - `bx_display_name` (function, line 454) `const char *bx_display_name(bx_display d)`
  - `bx_flex_max_clamp` (function, line 467) `double bx_flex_max_clamp(double outer_basis, double mw_cap, int border_box,
                     ...`
  - `bx_place_ex` (function, line 474) `bx_hplace bx_place_ex(double inset_l, double inset_r, double width_cap, int center,
             ...`
  - `bx_line_height_px` (function, line 484) `double bx_line_height_px(int line_scale, double font_px)`
  - `take` (function, line 295) `* caller has to take (Sizing 3 section 5.1), so to a resolver that only sums a * px and a percentage half they read...`
  - `BX_TAG_MAX` (macro, line 24) `#define BX_TAG_MAX`
  - `BX_DISPLAY_MAX` (macro, line 25) `#define BX_DISPLAY_MAX`
  - `BLOCK` (macro, line 67) `#define BLOCK`
  - `INLINE` (macro, line 68) `#define INLINE`
  - `IBLOCK` (macro, line 69) `#define IBLOCK`
  - `LITEM` (macro, line 70) `#define LITEM`
  - `NONE` (macro, line 71) `#define NONE`
  - `EDG` (macro, line 72) `#define EDG(t, r, b, l)`
  - `ZERO` (macro, line 73) `#define ZERO`
  - `T_NO` (macro, line 75) `#define T_NO`
  - `T_TBL` (macro, line 76) `#define T_TBL`
  - `T_GRP` (macro, line 77) `#define T_GRP`
  - `T_ROW` (macro, line 78) `#define T_ROW`
  - `T_CELL` (macro, line 79) `#define T_CELL`
  - `T_CAP` (macro, line 80) `#define T_CAP`
  - `T_COL` (macro, line 81) `#define T_COL`
  - `TAG_N` (macro, line 161) `#define TAG_N`
  - `DISP_N` (macro, line 259) `#define DISP_N`
- Depends on: `include/box_style.h`

## src/box_tree.c
- Doc: layout_block: Block container: stack non-none children vertically, collapsing each child's top *...
- Layer: utility
- Language: c
- Symbols:
  - `layout_block` (function, line 37) `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,
                   ...`
  - `bt_nn` (function, line 58) `static double bt_nn(double v)`
  - `height` (function, line 78) `* exactly that height (Flexbox 9.4 step 15).
 *
 * wrap_reverse (node->wrap_reverse): when node->...`
  - `layout_flex` (function, line 98) `static bt_status layout_flex(bt_node *node, bt_node *const *kids, size_t nk,
                    ...`
  - `layout_grid` (function, line 280) `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,
                    ...`
  - `layout_node` (function, line 420) `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)`
  - `bt_layout` (function, line 465) `bt_status bt_layout(bt_node *root, double avail_w)`
  - `assign_doc_order` (function, line 505) `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,
                  ...`
  - `find_positioned_ancestor` (function, line 522) `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,
                       ...`
  - `resolve_inset` (function, line 542) `static double resolve_inset(int v, int pct_pm, double basis)`
  - `inset_unset` (function, line 551) `static int inset_unset(int v, int pct_pm)`
  - `bt_containing_block` (function, line 555) `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i,
                        ...`
  - `block` (function, line 566) `* true block (same flow neighbourhood), strictly better than zeros. NULL
     * placed keeps lega...`
  - `bt_resolve_positioning` (function, line 585) `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,
                          ...`
  - `bt_resolve_positioning_ex` (function, line 596) `bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,
                       ...`
  - `oof_walk` (function, line 751) `static int oof_walk(const pv_box_def *boxes, size_t nbox, int bid, int nearest)`
  - `bt_oof_anchor` (function, line 768) `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)`
  - `bt_oof_root` (function, line 772) `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)`
  - `bt_box_hidden` (function, line 776) `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)`
  - `bt_in_subtree` (function, line 789) `int bt_in_subtree(const pv_box_def *boxes, size_t nbox, size_t root, size_t bid)`
  - `bt_oof_avail` (function, line 800) `double bt_oof_avail(int a, int a_pct, int b, int b_pct, double cb, int *both)`
  - `bt_defer_roots` (function, line 808) `size_t bt_defer_roots(const pv_box_def *boxes, size_t nbox,
                      const bt_positi...`
  - `sized` (function, line 350) `* the tracks are sized (CSS Grid 1 11.5, items spanning several tracks come * last);`
  - `BT_LEN_AUTO` (macro, line 31) `#define BT_LEN_AUTO`
  - `BT_WRAP_EPS` (macro, line 62) `#define BT_WRAP_EPS`
- Depends on: `include/box_style.h`, `include/box_tree.h`, `include/compositor.h`, `include/css.h`

## src/browser.c
- Doc: clear_status: #include <stdlib.h> #include <string.h> static void free_page(browser_state *bs) {...
- Layer: utility
- Language: c
- Symbols:
  - `free_page` (function, line 15) `static void free_page(browser_state *bs)`
  - `clear_status` (function, line 25) `static void clear_status(browser_state *bs)`
  - `free_history` (function, line 30) `static void free_history(browser_state *bs)`
  - `free_exceptions` (function, line 42) `static void free_exceptions(browser_state *bs)`
  - `is_https_url` (function, line 51) `static int is_https_url(const char *s)`
  - `is_local_path` (function, line 55) `static int is_local_path(const char *s)`
  - `url_is_allowed` (function, line 60) `static int url_is_allowed(const char *url)`
  - `xstrdup` (function, line 74) `static char *xstrdup(const char *s)`
  - `cp1252_to_ucs` (function, line 88) `static unsigned int cp1252_to_ucs(unsigned char c)`
  - `utf8_encode` (function, line 102) `static size_t utf8_encode(unsigned int cp, char *out)`
  - `browser_init` (function, line 156) `browser_status browser_init(browser_state *bs)`
  - `browser_free` (function, line 167) `void browser_free(browser_state *bs)`
  - `browser_set_url_bar` (function, line 178) `browser_status browser_set_url_bar(browser_state *bs, const char *url)`
  - `browser_commit_url_bar` (function, line 190) `browser_status browser_commit_url_bar(browser_state *bs)`
  - `browser_navigate` (function, line 224) `browser_status browser_navigate(browser_state *bs, const char *url)`
  - `browser_push_state` (function, line 236) `browser_status browser_push_state(browser_state *bs, const char *url)`
  - `browser_replace_state` (function, line 243) `browser_status browser_replace_state(browser_state *bs, const char *url)`
  - `browser_entry_doc` (function, line 255) `int browser_entry_doc(const browser_state *bs, size_t pos)`
  - `browser_doc_index` (function, line 260) `int browser_doc_index(const browser_state *bs)`
  - `browser_back` (function, line 268) `browser_status browser_back(browser_state *bs)`
  - `browser_forward` (function, line 280) `browser_status browser_forward(browser_state *bs)`
  - `browser_can_back` (function, line 292) `int browser_can_back(const browser_state *bs)`
  - `browser_can_forward` (function, line 296) `int browser_can_forward(const browser_state *bs)`
  - `browser_current_url` (function, line 300) `const char *browser_current_url(const browser_state *bs)`
  - `browser_url_bar_selection` (function, line 305) `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)`
  - `browser_url_bar_delete_selection` (function, line 316) `int browser_url_bar_delete_selection(browser_state *bs)`
  - `browser_url_bar_insert` (function, line 326) `browser_status browser_url_bar_insert(browser_state *bs, char c)`
  - `browser_url_bar_backspace` (function, line 341) `browser_status browser_url_bar_backspace(browser_state *bs)`
  - `browser_url_bar_delete` (function, line 355) `browser_status browser_url_bar_delete(browser_state *bs)`
  - `browser_url_bar_move_cursor` (function, line 366) `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)`
  - `browser_url_bar_extend_cursor` (function, line 376) `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)`
  - `browser_url_bar_set_cursor` (function, line 385) `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)`
  - `browser_url_bar_select_all` (function, line 393) `browser_status browser_url_bar_select_all(browser_state *bs)`
  - `browser_url_bar_clear` (function, line 400) `browser_status browser_url_bar_clear(browser_state *bs)`
  - `browser_set_page` (function, line 409) `browser_status browser_set_page(browser_state *bs, const char *title,
                           ...`
  - `browser_set_status` (function, line 431) `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)`
  - `browser_status_text` (function, line 445) `const char *browser_status_text(const browser_state *bs, uint64_t now_ms)`
  - `host_equal` (function, line 453) `static int host_equal(const char *a, const char *b)`
  - `browser_is_exception` (function, line 464) `int browser_is_exception(const browser_state *bs, const char *host)`
  - `browser_add_exception` (function, line 472) `browser_status browser_add_exception(browser_state *bs, const char *host)`
  - `_POSIX_C_SOURCE` (macro, line 7) `#define _POSIX_C_SOURCE`
- Depends on: `include/browser.h`, `include/util.h`

## src/cached_fetch.c
- Doc: trace: fetcher, and so the same policy, as an uncached request.  #define _POSIX_C_SOURCE 200809L...
- Layer: infrastructure
- Language: c
- Symbols:
  - `trace` (function, line 18) `static void trace(const char *what, const char *url)`
  - `cf_set_store` (function, line 22) `void cf_set_store(hc_store *store)`
  - `cf_store` (function, line 23) `hc_store *cf_store(void)`
  - `cacheable_request` (function, line 26) `static int cacheable_request(const sf_config *cfg, const char *url)`
  - `copy_val` (function, line 33) `static void copy_val(char *dst, size_t cap, const char *src)`
  - `meta_from_response` (function, line 40) `static void meta_from_response(hc_meta *m, const sf_response *r, const char *url, time_t now)`
  - `response_from_cache` (function, line 53) `static int response_from_cache(sf_response *out, const hc_meta *m, uint8_t *body, size_t len)`
  - `remember` (function, line 77) `static void remember(hc_store *store, const char *partition, const char *url,
                   ...`
  - `cf_get_with` (function, line 85) `sf_status cf_get_with(hc_store *store, cf_fetch_fn fetch, const char *partition, const char *url,...`
  - `cf_get` (function, line 133) `sf_status cf_get(const char *partition, const char *url, sf_config *cfg, sf_response *out,
      ...`
  - `redirect_load` (function, line 140) `static int redirect_load(void *ctx, const char *from, time_t now, char *out, size_t cap)`
  - `redirect_save` (function, line 144) `static void redirect_save(void *ctx, const char *from, const char *to, time_t now)`
  - `cf_attach_redirect_memory` (function, line 148) `void cf_attach_redirect_memory(hc_store *store)`
  - `_POSIX_C_SOURCE` (macro, line 7) `#define _POSIX_C_SOURCE`
- Depends on: `include/cached_fetch.h`

## src/compositor.c
- Doc: eff_z: Not a stacking context: a positioned box with z:auto still paints in the *...
- Layer: utility
- Language: c
- Symbols:
  - `cx_forms_stacking_context` (function, line 16) `int cx_forms_stacking_context(const cx_style *s)`
  - `cx_box_layer` (function, line 34) `cx_layer cx_box_layer(const cx_style *s)`
  - `eff_z` (function, line 50) `static int eff_z(const cx_item *it)`
  - `cx_item_compare` (function, line 54) `int cx_item_compare(const cx_item *a, const cx_item *b)`
  - `cx_sort` (function, line 70) `void cx_sort(cx_item *items, size_t n)`
- Depends on: `include/compositor.h`, `include/css.h`


Next: [KB_src_p2.md](KB_src_p2.md)
