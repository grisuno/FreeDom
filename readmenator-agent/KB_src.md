# Subsystem: src (page 1 of 10)
Pages: [KB_src.md](KB_src.md), [KB_src_p2.md](KB_src_p2.md), [KB_src_p3.md](KB_src_p3.md), [KB_src_p4.md](KB_src_p4.md), [KB_src_p5.md](KB_src_p5.md), [KB_src_p6.md](KB_src_p6.md), [KB_src_p7.md](KB_src_p7.md), [KB_src_p8.md](KB_src_p8.md), [KB_src_p9.md](KB_src_p9.md), [KB_src_p10.md](KB_src_p10.md)

## src/anchor.c
- Doc: — the indicated part of a document and where it sits (spec/anchor.md).
- Layer: utility
- Language: c
- Symbols:
  - `hex_val` (function, line 8) `static int hex_val(int c)`
  - `anc_percent_decode` (function, line 15) `size_t anc_percent_decode(const char *in, char *out, size_t cap)`
  - `first_named_a` (function, line 35) `static dom_node_id first_named_a(const dom_index *idx, const char *name)`
  - `potential_indicated` (function, line 54) `static dom_node_id potential_indicated(const dom_index *idx, const char *s)`
  - `is_top` (function, line 59) `static int is_top(const char *s)`
  - `anc_resolve` (function, line 63) `anc_kind anc_resolve(const dom_index *idx, const char *fragment, dom_node_id *out)`
  - `next_preorder` (function, line 81) `static dom_node_id next_preorder(const dom_index *idx, dom_node_id cur, dom_node_id root,
       ...`
  - `anc_collect` (function, line 93) `size_t anc_collect(const dom_index *idx, dom_node_id target, dom_node_id *out, size_t cap,
      ...`
  - `anc_target_top` (function, line 110) `int anc_target_top(const jg_table *g, const dom_node_id *h, size_t n, size_t nsub,
              ...`
  - `anc_scroll_for` (function, line 131) `double anc_scroll_for(double top, double max_scroll)`
- Depends on: `include/anchor.h`

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
- Doc: box_recip: floor((sum + bw/2) / bw) without a division: m = floor(2^32 / bw) + 1 makes (n * m)...
- Layer: utility
- Language: c
- Symbols:
  - `bb_box_sizes` (function, line 8) `int bb_box_sizes(double sigma, int sizes[3])`
  - `box_recip` (function, line 32) `static uint64_t box_recip(int bw)`
  - `box_avg` (function, line 33) `static unsigned char box_avg(long sum, int bw, uint64_t m)`
  - `box_line` (function, line 39) `static void box_line(unsigned char *p, int n, int step, int bw, unsigned char *tmp)`
  - `box_cols` (function, line 56) `static void box_cols(unsigned char *buf, int w, int h, int stride, int bw,
                     u...`
  - `bb_blur_a8` (function, line 82) `int bb_blur_a8(unsigned char *buf, int w, int h, int stride, double sigma)`
  - `bb_ink_rect` (function, line 102) `int bb_ink_rect(const unsigned char *argb, int w, int h, int stride, double sigma, int rect[4])`
  - `variance` (function, line 11) `* width w has variance (w^2 - 1) / 12): the ideal common width, rounded down * to an odd wl and up to wu = wl + 2...`
  - `BB_BOX_MAX` (macro, line 31) `#define BB_BOX_MAX`
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
  - `sc_chain` (struct, line 611)
  - `len` (type_alias, line 610) `typedef struct sc_chain { uint16_t len;`
  - `layout_block` (function, line 40) `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,
                   ...`
  - `bt_nn` (function, line 61) `static double bt_nn(double v)`
  - `height` (function, line 81) `* exactly that height (Flexbox 9.4 step 15).
 *
 * wrap_reverse (node->wrap_reverse): when node->...`
  - `layout_flex` (function, line 101) `static bt_status layout_flex(bt_node *node, bt_node *const *kids, size_t nk,
                    ...`
  - `layout_grid` (function, line 283) `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,
                    ...`
  - `layout_node` (function, line 423) `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)`
  - `bt_layout` (function, line 468) `bt_status bt_layout(bt_node *root, double avail_w)`
  - `assign_doc_order` (function, line 508) `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,
                  ...`
  - `find_positioned_ancestor` (function, line 525) `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,
                       ...`
  - `resolve_inset` (function, line 545) `static double resolve_inset(int v, int pct_pm, double basis)`
  - `inset_unset` (function, line 554) `static int inset_unset(int v, int pct_pm)`
  - `bt_containing_block` (function, line 558) `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i,
                        ...`
  - `block` (function, line 569) `* true block (same flow neighbourhood), strictly better than zeros. NULL
     * placed keeps lega...`
  - `bt_resolve_positioning` (function, line 588) `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,
                          ...`
  - `sc_forms` (function, line 616) `static int sc_forms(const pv_box_def *b)`
  - `sc_chain_compare` (function, line 629) `static int sc_chain_compare(const sc_chain *a, const sc_chain *b, const cx_item *by_ref)`
  - `nest_in_contexts` (function, line 638) `static void nest_in_contexts(const pv_box_def *boxes, size_t nbox, const bt_positioned *tmp,
    ...`
  - `bt_resolve_positioning_ex` (function, line 706) `bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,
                       ...`
  - `oof_walk` (function, line 862) `static int oof_walk(const pv_box_def *boxes, size_t nbox, int bid, int nearest)`
  - `bt_oof_anchor` (function, line 879) `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)`
  - `bt_oof_root` (function, line 883) `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)`
  - `bt_box_hidden` (function, line 887) `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)`
  - `bt_in_subtree` (function, line 900) `int bt_in_subtree(const pv_box_def *boxes, size_t nbox, size_t root, size_t bid)`
  - `bt_oof_avail` (function, line 911) `double bt_oof_avail(int a, int a_pct, int b, int b_pct, double cb, int *both)`
  - `bt_defer_roots` (function, line 919) `size_t bt_defer_roots(const pv_box_def *boxes, size_t nbox,
                      const bt_positi...`
  - `sized` (function, line 353) `* the tracks are sized (CSS Grid 1 11.5, items spanning several tracks come * last);`
  - `BT_LEN_AUTO` (macro, line 34) `#define BT_LEN_AUTO`
  - `BT_WRAP_EPS` (macro, line 65) `#define BT_WRAP_EPS`
  - `BT_SC_DEPTH` (macro, line 609) `#define BT_SC_DEPTH`
- Depends on: `include/box_style.h`, `include/box_tree.h`, `include/compositor.h`, `include/css.h`

## src/browser.c
- Doc: clear_status: #include <stdlib.h> #include <math.h> #include <string.h> static void...
- Layer: utility
- Language: c
- Symbols:
  - `free_page` (function, line 16) `static void free_page(browser_state *bs)`
  - `clear_status` (function, line 26) `static void clear_status(browser_state *bs)`
  - `free_history` (function, line 31) `static void free_history(browser_state *bs)`
  - `free_stash` (function, line 47) `static void free_stash(browser_state *bs)`
  - `free_pending` (function, line 59) `static void free_pending(browser_state *bs)`
  - `begin_pending` (function, line 72) `static void begin_pending(browser_state *bs, int kind)`
  - `free_exceptions` (function, line 83) `static void free_exceptions(browser_state *bs)`
  - `is_https_url` (function, line 92) `static int is_https_url(const char *s)`
  - `is_local_path` (function, line 96) `static int is_local_path(const char *s)`
  - `url_is_allowed` (function, line 101) `static int url_is_allowed(const char *url)`
  - `xstrdup` (function, line 115) `static char *xstrdup(const char *s)`
  - `cp1252_to_ucs` (function, line 129) `static unsigned int cp1252_to_ucs(unsigned char c)`
  - `utf8_encode` (function, line 143) `static size_t utf8_encode(unsigned int cp, char *out)`
  - `browser_init` (function, line 197) `browser_status browser_init(browser_state *bs)`
  - `browser_free` (function, line 208) `void browser_free(browser_state *bs)`
  - `browser_set_url_bar` (function, line 220) `browser_status browser_set_url_bar(browser_state *bs, const char *url)`
  - `browser_commit_url_bar` (function, line 232) `browser_status browser_commit_url_bar(browser_state *bs)`
  - `browser_navigate` (function, line 288) `browser_status browser_navigate(browser_state *bs, const char *url)`
  - `browser_push_state` (function, line 320) `browser_status browser_push_state(browser_state *bs, const char *url)`
  - `browser_replace_state` (function, line 328) `browser_status browser_replace_state(browser_state *bs, const char *url)`
  - `browser_set_entry_scroll` (function, line 341) `void browser_set_entry_scroll(browser_state *bs, double scroll)`
  - `browser_entry_scroll` (function, line 346) `double browser_entry_scroll(const browser_state *bs)`
  - `browser_entry_doc` (function, line 351) `int browser_entry_doc(const browser_state *bs, size_t pos)`
  - `browser_doc_index` (function, line 356) `int browser_doc_index(const browser_state *bs)`
  - `browser_back` (function, line 364) `browser_status browser_back(browser_state *bs)`
  - `browser_forward` (function, line 377) `browser_status browser_forward(browser_state *bs)`
  - `browser_can_back` (function, line 390) `int browser_can_back(const browser_state *bs)`
  - `browser_can_forward` (function, line 394) `int browser_can_forward(const browser_state *bs)`
  - `browser_current_url` (function, line 398) `const char *browser_current_url(const browser_state *bs)`
  - `browser_url_bar_selection` (function, line 403) `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)`
  - `browser_url_bar_delete_selection` (function, line 414) `int browser_url_bar_delete_selection(browser_state *bs)`
  - `browser_url_bar_insert` (function, line 424) `browser_status browser_url_bar_insert(browser_state *bs, char c)`
  - `browser_url_bar_backspace` (function, line 439) `browser_status browser_url_bar_backspace(browser_state *bs)`
  - `browser_url_bar_delete` (function, line 453) `browser_status browser_url_bar_delete(browser_state *bs)`
  - `browser_url_bar_move_cursor` (function, line 464) `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)`
  - `browser_url_bar_extend_cursor` (function, line 474) `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)`
  - `browser_url_bar_set_cursor` (function, line 483) `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)`
  - `browser_url_bar_select_all` (function, line 491) `browser_status browser_url_bar_select_all(browser_state *bs)`
  - `browser_url_bar_clear` (function, line 498) `browser_status browser_url_bar_clear(browser_state *bs)`
  - `browser_set_page` (function, line 507) `browser_status browser_set_page(browser_state *bs, const char *title,
                           ...`
  - `browser_set_status` (function, line 529) `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)`
  - `browser_status_text` (function, line 543) `const char *browser_status_text(const browser_state *bs, uint64_t now_ms)`
  - `host_equal` (function, line 551) `static int host_equal(const char *a, const char *b)`
  - `browser_is_exception` (function, line 562) `int browser_is_exception(const browser_state *bs, const char *host)`
  - `browser_add_exception` (function, line 570) `browser_status browser_add_exception(browser_state *bs, const char *host)`
  - `browser_closed_push` (function, line 588) `browser_status browser_closed_push(browser_closed *c, const char *url)`
  - `browser_closed_pop` (function, line 603) `int browser_closed_pop(browser_closed *c, char *out, size_t cap)`
  - `browser_commit_pending` (function, line 615) `void browser_commit_pending(browser_state *bs)`
  - `browser_abort_pending` (function, line 620) `int browser_abort_pending(browser_state *bs)`
  - `browser_has_pending` (function, line 650) `int browser_has_pending(const browser_state *bs)`
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

## src/chrome_layout.c
- Doc: chrome_layout -- browser chrome geometry + identity badge. spec/chrome_layout.md
- Layer: presentation
- Language: c
- Symbols:
  - `rect` (function, line 17) `static chl_rect rect(double x, double y, double w, double h)`
  - `chl_rect_has` (function, line 26) `int chl_rect_has(chl_rect r, double x, double y)`
  - `chl_compute` (function, line 30) `chl_status chl_compute(double width, int csd, int tab_count, int active, chl_layout *out)`
  - `chl_tab_rect` (function, line 115) `int chl_tab_rect(const chl_layout *l, int i, chl_rect *r)`
  - `chl_tab_close_rect` (function, line 125) `int chl_tab_close_rect(const chl_layout *l, int i, chl_rect *r)`
  - `chl_hit` (function, line 135) `chl_part chl_hit(const chl_layout *l, double x, double y, int *tab)`
  - `chl_tab_drop_index` (function, line 169) `int chl_tab_drop_index(const chl_layout *l, double x)`
  - `chl_move_index` (function, line 179) `int chl_move_index(int i, int from, int to)`
  - `chl_tab_for_digit` (function, line 186) `int chl_tab_for_digit(int digit, int tab_count)`
  - `lower` (function, line 194) `static int lower(int c)`
  - `has_prefix_ci` (function, line 197) `static int has_prefix_ci(const char *s, const char *prefix)`
  - `host_ends_with` (function, line 204) `static int host_ends_with(const char *h, size_t n, const char *suffix)`
  - `url_host` (function, line 214) `static size_t url_host(const char *rest, const char **out)`
  - `chl_identity_of` (function, line 232) `chl_identity chl_identity_of(const char *url, int transport_known, int downgrade,
               ...`
  - `chl_identity_label` (function, line 256) `const char *chl_identity_label(chl_identity id)`
  - `chl_findbar_compute` (function, line 273) `chl_status chl_findbar_compute(double width, double height, chl_findbar *out)`
  - `chl_findbar_hit` (function, line 309) `chl_find_part chl_findbar_hit(const chl_findbar *f, double x, double y)`
  - `chl_tab_fallback_title` (function, line 321) `void chl_tab_fallback_title(const char *url, char *out, size_t cap)`
  - `CHL_TAB_CLOSE_INSET` (macro, line 9) `#define CHL_TAB_CLOSE_INSET`
  - `CHL_URL_GAP` (macro, line 11) `#define CHL_URL_GAP`
  - `CHL_ID_INSET` (macro, line 13) `#define CHL_ID_INSET`
  - `CHL_WIDTH_MAX` (macro, line 15) `#define CHL_WIDTH_MAX`
- Depends on: `include/chrome_layout.h`

## src/compositor.c
- Doc: eff_z: Not a stacking context: a positioned box with z:auto still paints in the *...
- Layer: utility
- Language: c
- Symbols:
  - `cx_forms_stacking_context` (function, line 18) `int cx_forms_stacking_context(const cx_style *s)`
  - `cx_box_layer` (function, line 36) `cx_layer cx_box_layer(const cx_style *s)`
  - `eff_z` (function, line 52) `static int eff_z(const cx_item *it)`
  - `cx_item_compare` (function, line 56) `int cx_item_compare(const cx_item *a, const cx_item *b)`
  - `cx_sort` (function, line 72) `void cx_sort(cx_item *items, size_t n)`
  - `cx_ink_reach` (function, line 87) `double cx_ink_reach(const int (*layers)[6], int n, int outline_w, int outline_offset)`
  - `cx_span_visible` (function, line 104) `int cx_span_visible(double top, double h, double reach, double view_top, double view_h)`
- Depends on: `include/compositor.h`, `include/css.h`


Next: [KB_src_p2.md](KB_src_p2.md)
