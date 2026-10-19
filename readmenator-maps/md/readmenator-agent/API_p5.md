# API (page 5 of 10)
Previous: [API_p4.md](API_p4.md)

## include/webfont_load.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/webfont_load.c`, `tests/test_webfont_load.c`
- `free` (function) `include/webfont_load.h:31` `* free()), *out_status the HTTP status. Nonzero on refusal/error (fail-closed: * the face is skipped, never the...`
- `skipped` (function) `include/webfont_load.h:47` `* URLs are skipped (no base). Returns faces registered (>= 0) otherwise. */ int wf_load_document(wf_fetch_fn fetch...`

## include/ws_hub.h
Depends on: `include/secure_fetch.h`
Imported by: `gui/browser_ui.c`, `src/ws_hub.c`, `tests/test_ws_hub.c`
- `wh_new` (function) `include/ws_hub.h:34` `wh_hub *wh_new(void);` -- #define WH_MAX 8   /* == JD_WS_MAX: sockets per page /* Event kinds delivered to the page; values match...
- `wh_free` (function) `include/ws_hub.h:38` `void wh_free(wh_hub *h);` -- Closes every connection and frees the hub.
- `wh_notify_fd` (function) `include/ws_hub.h:41` `int wh_notify_fd(const wh_hub *h);` -- Closes every connection and frees the hub.
- `wh_open_async` (function) `include/ws_hub.h:46` `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg);` -- Starts opening url for page socket id on a thread (cfg and all its strings are copied).
- `generation` (function) `include/ws_hub.h:50` `* previous generation (before wh_close_all) are closed and dropped silently. */ void wh_on_notify(wh_hub *h...`
- `wh_send` (function) `include/ws_hub.h:54` `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary);` -- Drains finished opens: success => the connection joins the hub and WH_EV_OPEN is emitted; failure => WH_EV_ERROR...
- `wh_close` (function) `include/ws_hub.h:58` `void wh_close(wh_hub *h, int id);` -- The page closed socket id: sends a close frame and frees it (also cancels a * pending open for that id: its result...
- `wh_close_all` (function) `include/ws_hub.h:61` `void wh_close_all(wh_hub *h);` -- The page closed socket id: sends a close frame and frees it (also cancels a * pending open for that id: its result...
- `wh_poll_fds` (function) `include/ws_hub.h:65` `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap);` -- Fills up to cap pollfds (POLLIN) and the matching page ids for the open * connections.
- `wh_on_readable` (function) `include/ws_hub.h:70` `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx);` -- Reads everything pending on socket id without blocking, emitting each complete message; a close frame emits...
- `wh_count` (function) `include/ws_hub.h:73` `size_t wh_count(const wh_hub *h);` -- Reads everything pending on socket id without blocking, emitting each complete message; a close frame emits...

## include/zoom.h
Imported by: `gui/browser_ui.c`, `src/prefs.c`, `src/zoom.c`, `tests/test_prefs.c`, `tests/test_zoom.c`
- `zm_clamp` (function) `include/zoom.h:26` `int zm_clamp(int pct);` -- stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser.
- `zm_zoom_in` (function) `include/zoom.h:29` `int zm_zoom_in(int pct);` -- never escape the bounds.
- `zm_zoom_out` (function) `include/zoom.h:32` `int zm_zoom_out(int pct);` -- only calls these.
- `zm_reset` (function) `include/zoom.h:35` `int zm_reset(void);` -- #define ZM_MIN_PCT     50 #define ZM_MAX_PCT     300 #define ZM_DEFAULT_PCT 100 /* Clamp pct to [ZM_MIN_PCT...
- `zm_scale` (function) `include/zoom.h:38` `double zm_scale(int pct);` -- /* Clamp pct to [ZM_MIN_PCT, ZM_MAX_PCT]. int zm_clamp(int pct); /* Smallest ladder stop strictly greater than...
- `zm_apply` (function) `include/zoom.h:42` `double zm_apply(double base_px, int pct);` -- base_px * zm_scale(pct), floored to 1.0 when base_px > 0 so a font can never * scale away to nothing. base_px <= 0...

## src/anti_fp.c
Depends on: `include/anti_fp.h`
- `fp_coarsen_time_ms` (function) `src/anti_fp.c:17` `uint64_t fp_coarsen_time_ms(uint64_t raw_ms)`
- `fp_user_agent` (function) `src/anti_fp.c:23` `const char *fp_user_agent(void)`
- `fp_accept_language` (function) `src/anti_fp.c:27` `const char *fp_accept_language(void)`
- `fp_accept_language_header` (function) `src/anti_fp.c:31` `const char *fp_accept_language_header(void)`
- `fp_timezone` (function) `src/anti_fp.c:35` `const char *fp_timezone(void)`
- `fp_platform` (function) `src/anti_fp.c:39` `const char *fp_platform(void)`
- `fp_vendor` (function) `src/anti_fp.c:43` `const char *fp_vendor(void)`
- `fp_hardware_concurrency` (function) `src/anti_fp.c:47` `int fp_hardware_concurrency(void)`
- `fp_device_memory_gb` (function) `src/anti_fp.c:51` `int fp_device_memory_gb(void)`
- `fp_app_version` (function) `src/anti_fp.c:57` `const char *fp_app_version(void)`
- `fp_app_code_name` (function) `src/anti_fp.c:61` `const char *fp_app_code_name(void)`
- `fp_product` (function) `src/anti_fp.c:65` `const char *fp_product(void)`
- `fp_app_name` (function) `src/anti_fp.c:69` `const char *fp_app_name(void)`
- `fp_product_sub` (function) `src/anti_fp.c:73` `const char *fp_product_sub(void)`
- `fp_oscpu` (function) `src/anti_fp.c:77` `const char *fp_oscpu(void)`
- `fp_build_id` (function) `src/anti_fp.c:81` `const char *fp_build_id(void)`
- `fp_max_touch_points` (function) `src/anti_fp.c:85` `int fp_max_touch_points(void)`
- `fp_on_line` (function) `src/anti_fp.c:89` `int fp_on_line(void)`
- `fp_cookie_enabled` (function) `src/anti_fp.c:93` `int fp_cookie_enabled(void)`
- `fp_bucket_screen` (function) `src/anti_fp.c:99` `void fp_bucket_screen(int w, int h, int *out_w, int *out_h)`
- `splitmix64` (function) `src/anti_fp.c:121` `static uint64_t splitmix64(uint64_t *state)`
- `fp_perturb` (function) `src/anti_fp.c:128` `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key)`
- `fp_origin_key` (function) `src/anti_fp.c:139` `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain)`

## src/block_flow.c
Depends on: `include/block_flow.h`
- `finite_or_zero` (function) `src/block_flow.c:11` `static double finite_or_zero(double v)` -- A margin the caller could not compute (NaN from a hostile calc(), an infinity from an overflowing unit conversion)...
- `bf_collapse_n` (function) `src/block_flow.c:15` `double bf_collapse_n(const double *m, size_t n)`
- `bf_collapse` (function) `src/block_flow.c:30` `double bf_collapse(double a, double b)`
- `bf_margins_adjoin` (function) `src/block_flow.c:35` `int bf_margins_adjoin(double border_px, double padding_px)`

## src/box_blur.c
Depends on: `include/box_blur.h`
- `bb_box_sizes` (function) `src/box_blur.c:7` `int bb_box_sizes(double sigma, int sizes[3])`
- `variance` (function) `src/box_blur.c:10` `* width w has variance (w^2 - 1) / 12): the ideal common width, rounded down * to an odd wl and up to wu = wl + 2...`
- `box_line` (function) `src/box_blur.c:28` `static void box_line(unsigned char *p, int n, int step, int bw, unsigned char *tmp)` -- One box pass of odd width bw over n samples spaced `step` apart, through tmp * (n bytes).
- `bb_blur_a8` (function) `src/box_blur.c:41` `int bb_blur_a8(unsigned char *buf, int w, int h, int stride, double sigma)`

## src/box_style.c
Depends on: `include/box_style.h`
- `is_ws` (function) `src/box_style.c:31` `static int is_ws(char c)`
- `copy_lower_trim` (function) `src/box_style.c:37` `static int copy_lower_trim(const char *in, char *out, size_t out_size)` -- Copies in into out, trimming ASCII whitespace and lowercasing.
- `name_cmp` (function) `src/box_style.c:50` `static int name_cmp(const void *key, const void *elem)` -- Both row structs start with `const char *name`, so a pointer to a row is also a * pointer to its name field: one...
- `bx_default_for_tag` (function) `src/box_style.c:163` `bx_box bx_default_for_tag(const char *tag)`
- `bx_table_role_of` (function) `src/box_style.c:171` `bx_table_role bx_table_role_of(const char *tag, css_display display)`
- `bx_ua_of_tag` (function) `src/box_style.c:210` `bx_ua_tag bx_ua_of_tag(const char *tag)`
- `bx_default_for_ua` (function) `src/box_style.c:219` `bx_box bx_default_for_ua(bx_ua_tag id)`
- `bx_block_ua_box` (function) `src/box_style.c:225` `bx_box bx_block_ua_box(int heading_level, int in_list, bx_ua_tag ua)`
- `bx_parse_display` (function) `src/box_style.c:261` `bx_status bx_parse_display(const char *token, bx_display *out)`
- `bx_place` (function) `src/box_style.c:271` `bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,
                ...`
- `bx_width_cap` (function) `src/box_style.c:288` `double bx_width_cap(int w_px, int w_pct, double avail_w)`
- `take` (function) `src/box_style.c:295` `* caller has to take (Sizing 3 section 5.1), so to a resolver that only sums a * px and a percentage half they read...`
- `bx_width_cap2` (function) `src/box_style.c:313` `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w)`
- `bx_replaced_box` (function) `src/box_style.c:321` `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den,
                    doub...`
- `bx_border_box_h` (function) `src/box_style.c:335` `double bx_border_box_h(double declared_h, int border_box,
                       double pad_t, do...`
- `bx_pct_block_size` (function) `src/box_style.c:346` `double bx_pct_block_size(int px_val, int pct_pm, double cb_h)`
- `bx_definite_content_h` (function) `src/box_style.c:352` `double bx_definite_content_h(double h, double min_h, double max_h,
                             i...`
- `bx_content_clipped` (function) `src/box_style.c:361` `int bx_content_clipped(int overflow_x, int overflow_y)`
- `bx_lp_px` (function) `src/box_style.c:367` `double bx_lp_px(int px_val, int pct_pm, double basis)`
- `bx_content_cap` (function) `src/box_style.c:378` `double bx_content_cap(double width_cap, int border_box,
                      double pad_l, doubl...`
- `bx_flex_min_clamp` (function) `src/box_style.c:389` `double bx_flex_min_clamp(double outer_basis, double min_w, int border_box,
                      ...`
- `bx_border_span` (function) `src/box_style.c:396` `double bx_border_span(double width_cap, int border_box,
                      double pad_l, doubl...`
- `bg_size_component` (function) `src/box_style.c:408` `static double bg_size_component(int px_val, int pct_pm, double area)` -- One background-size component in px, or -1 when it is `auto` (Backgrounds 3 section 3.9).
- `bx_background_layer` (function) `src/box_style.c:415` `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h,
                    ...`
- `bx_display_name` (function) `src/box_style.c:454` `const char *bx_display_name(bx_display d)`
- `bx_flex_max_clamp` (function) `src/box_style.c:467` `double bx_flex_max_clamp(double outer_basis, double mw_cap, int border_box,
                     ...`
- `bx_place_ex` (function) `src/box_style.c:474` `bx_hplace bx_place_ex(double inset_l, double inset_r, double width_cap, int center,
             ...`
- `bx_line_height_px` (function) `src/box_style.c:484` `double bx_line_height_px(int line_scale, double font_px)`

## src/box_tree.c
Depends on: `include/box_style.h`, `include/box_tree.h`, `include/compositor.h`, `include/css.h`
- `layout_block` (function) `src/box_tree.c:37` `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,
                   ...` -- Block container: stack non-none children vertically, collapsing each child's top * margin with the previous child's...
- `bt_nn` (function) `src/box_tree.c:58` `static double bt_nn(double v)` -- if (cavail < 0.0) cavail = 0.0; bt_status r = layout_node(c, cavail, depth + 1); if (r != BT_OK) return r; double...
- `height` (function) `src/box_tree.c:78` `* exactly that height (Flexbox 9.4 step 15).
 *
 * wrap_reverse (node->wrap_reverse): when node->...`
- `layout_flex` (function) `src/box_tree.c:98` `static bt_status layout_flex(bt_node *node, bt_node *const *kids, size_t nk,
                    ...`
- `layout_grid` (function) `src/box_tree.c:280` `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,
                    ...`
- `sized` (function) `src/box_tree.c:350` `* the tracks are sized (CSS Grid 1 11.5, items spanning several tracks come * last);`
- `layout_node` (function) `src/box_tree.c:420` `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)`
- `bt_layout` (function) `src/box_tree.c:465` `bt_status bt_layout(bt_node *root, double avail_w)`
- `assign_doc_order` (function) `src/box_tree.c:505` `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,
                  ...` -- Recursive doc_order assignment.
- `find_positioned_ancestor` (function) `src/box_tree.c:522` `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,
                       ...` -- Walk the parent_id chain from `start` to find the nearest ancestor with position != STATIC.
- `resolve_inset` (function) `src/box_tree.c:542` `static double resolve_inset(int v, int pct_pm, double basis)` -- Resolves an inset <length-percentage>: PV_LEN_UNSET or BT_LEN_AUTO with no percentage half → 0 (anchor at the...
- `inset_unset` (function) `src/box_tree.c:551` `static int inset_unset(int v, int pct_pm)` -- Stage 2b: an inset axis the author left undeclared (UNSET) or `auto`.
- `bt_containing_block` (function) `src/box_tree.c:555` `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i,
                        ...`
- `block` (function) `src/box_tree.c:566` `* true block (same flow neighbourhood), strictly better than zeros. NULL
     * placed keeps lega...`
- `bt_resolve_positioning` (function) `src/box_tree.c:585` `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,
                          ...`
- `bt_resolve_positioning_ex` (function) `src/box_tree.c:596` `bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,
                       ...`
- `oof_walk` (function) `src/box_tree.c:751` `static int oof_walk(const pv_box_def *boxes, size_t nbox, int bid, int nearest)` -- Shared walk for the Stage 2d classifiers: nearest==1 stops at the first * ABSOLUTE/FIXED box, nearest==0 remembers...
- `bt_oof_anchor` (function) `src/box_tree.c:768` `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)`
- `bt_oof_root` (function) `src/box_tree.c:772` `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)`
- `bt_box_hidden` (function) `src/box_tree.c:776` `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)`
- `bt_oof_avail` (function) `src/box_tree.c:789` `double bt_oof_avail(int a, int a_pct, int b, int b_pct, double cb, int *both)`
- `bt_defer_roots` (function) `src/box_tree.c:797` `size_t bt_defer_roots(const pv_box_def *boxes, size_t nbox,
                      const bt_positi...`

## src/browser.c
Depends on: `include/browser.h`, `include/util.h`
- `free_page` (function) `src/browser.c:15` `static void free_page(browser_state *bs)`
- `clear_status` (function) `src/browser.c:25` `static void clear_status(browser_state *bs)` -- #include <stdlib.h> #include <string.h> static void free_page(browser_state *bs) { if (bs == NULL) return...
- `free_history` (function) `src/browser.c:30` `static void free_history(browser_state *bs)`
- `free_exceptions` (function) `src/browser.c:42` `static void free_exceptions(browser_state *bs)`
- `is_https_url` (function) `src/browser.c:51` `static int is_https_url(const char *s)`
- `is_local_path` (function) `src/browser.c:55` `static int is_local_path(const char *s)`
- `url_is_allowed` (function) `src/browser.c:60` `static int url_is_allowed(const char *url)`
- `xstrdup` (function) `src/browser.c:74` `static char *xstrdup(const char *s)`
- `cp1252_to_ucs` (function) `src/browser.c:88` `static unsigned int cp1252_to_ucs(unsigned char c)` -- Unicode scalar for a Windows-1252 byte (only meaningful for c >= 0x80).
- `utf8_encode` (function) `src/browser.c:102` `static size_t utf8_encode(unsigned int cp, char *out)` -- Encodes a BMP scalar (<= 0xFFFF) as UTF-8 into out (up to 3 bytes); returns the * byte count written.
- `browser_init` (function) `src/browser.c:156` `browser_status browser_init(browser_state *bs)`
- `browser_free` (function) `src/browser.c:167` `void browser_free(browser_state *bs)`
- `browser_set_url_bar` (function) `src/browser.c:178` `browser_status browser_set_url_bar(browser_state *bs, const char *url)`
- `browser_commit_url_bar` (function) `src/browser.c:190` `browser_status browser_commit_url_bar(browser_state *bs)`
- `browser_navigate` (function) `src/browser.c:224` `browser_status browser_navigate(browser_state *bs, const char *url)`
- `browser_push_state` (function) `src/browser.c:236` `browser_status browser_push_state(browser_state *bs, const char *url)`
- `browser_replace_state` (function) `src/browser.c:243` `browser_status browser_replace_state(browser_state *bs, const char *url)`
- `browser_entry_doc` (function) `src/browser.c:255` `int browser_entry_doc(const browser_state *bs, size_t pos)`
- `browser_doc_index` (function) `src/browser.c:260` `int browser_doc_index(const browser_state *bs)`
- `browser_back` (function) `src/browser.c:268` `browser_status browser_back(browser_state *bs)`
- `browser_forward` (function) `src/browser.c:280` `browser_status browser_forward(browser_state *bs)`
- `browser_can_back` (function) `src/browser.c:292` `int browser_can_back(const browser_state *bs)`
- `browser_can_forward` (function) `src/browser.c:296` `int browser_can_forward(const browser_state *bs)`
- `browser_current_url` (function) `src/browser.c:300` `const char *browser_current_url(const browser_state *bs)`
- `browser_url_bar_selection` (function) `src/browser.c:305` `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)`
- `browser_url_bar_delete_selection` (function) `src/browser.c:316` `int browser_url_bar_delete_selection(browser_state *bs)`
- `browser_url_bar_insert` (function) `src/browser.c:326` `browser_status browser_url_bar_insert(browser_state *bs, char c)`
- `browser_url_bar_backspace` (function) `src/browser.c:341` `browser_status browser_url_bar_backspace(browser_state *bs)`
- `browser_url_bar_delete` (function) `src/browser.c:355` `browser_status browser_url_bar_delete(browser_state *bs)`
- `browser_url_bar_move_cursor` (function) `src/browser.c:366` `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)`
- `browser_url_bar_extend_cursor` (function) `src/browser.c:376` `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)`
- `browser_url_bar_set_cursor` (function) `src/browser.c:385` `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)`
- `browser_url_bar_select_all` (function) `src/browser.c:393` `browser_status browser_url_bar_select_all(browser_state *bs)`
- `browser_url_bar_clear` (function) `src/browser.c:400` `browser_status browser_url_bar_clear(browser_state *bs)`
- `browser_set_page` (function) `src/browser.c:409` `browser_status browser_set_page(browser_state *bs, const char *title,
                           ...`
- `browser_set_status` (function) `src/browser.c:431` `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)`
- `browser_status_text` (function) `src/browser.c:445` `const char *browser_status_text(const browser_state *bs, uint64_t now_ms)`
- `host_equal` (function) `src/browser.c:453` `static int host_equal(const char *a, const char *b)`
- `browser_is_exception` (function) `src/browser.c:464` `int browser_is_exception(const browser_state *bs, const char *host)`
- `browser_add_exception` (function) `src/browser.c:472` `browser_status browser_add_exception(browser_state *bs, const char *host)`

## src/compositor.c
Depends on: `include/compositor.h`, `include/css.h`
- `cx_forms_stacking_context` (function) `src/compositor.c:16` `int cx_forms_stacking_context(const cx_style *s)`
- `cx_box_layer` (function) `src/compositor.c:34` `cx_layer cx_box_layer(const cx_style *s)`
- `eff_z` (function) `src/compositor.c:50` `static int eff_z(const cx_item *it)` -- Not a stacking context: a positioned box with z:auto still paints in the * positioned/zero layer (CSS 2.1 App E...
- `cx_item_compare` (function) `src/compositor.c:54` `int cx_item_compare(const cx_item *a, const cx_item *b)`
- `cx_sort` (function) `src/compositor.c:70` `void cx_sort(cx_item *items, size_t n)` -- Stable insertion sort: n is bounded by the caller (BT_MAX_POSITIONED), so O(n^2) is fine, and stability keeps...

## src/css.c
Depends on: `include/css.h`, `include/css_atrule.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_gradient.h`, `include/css_index.h`, `include/css_length.h`, `include/css_mq.h`, `include/css_select.h`, `include/css_text.h`, `include/css_values.h`, `include/css_vars.h`, `include/flex_layout.h`, `include/webfont.h`
- `emit` (function) `src/css.c:62` `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand...`
- `css_decl` (function) `src/css.c:89` `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);`
- `parse_num` (function) `src/css.c:179` `static int parse_num(const char *s, double *out, const char **endp)` -- Parses a leading non-negative number (digits + optional fraction).
- `parse_color` (function) `src/css.c:190` `static int parse_color(const char *v)` -- Delegates to the canonical CSS <number> grammar so a number means the same thing here as in a length, a colour...
- `interp_color` (function) `src/css.c:194` `static int interp_color(const char *v)`
- `through` (function) `src/css.c:210` `* at the two SHARED chokepoints every property funnels through (the generic
 * dispatch tail, and...`
- `bg_alpha_of` (function) `src/css.c:234` `static int bg_alpha_of(const char *v)` -- Alpha (4th) component of the first rgba()/hsla() call inside v, as a percent 0..100; CSS_LEN_UNSET when there is none.
- `interp_bg` (function) `src/css.c:238` `static int interp_bg(const char *v)`
- `expand_bg_image` (function) `src/css.c:246` `static int expand_bg_image(const char *val, css_decl *dst, int cap,
                           ch...`
- `expand_background` (function) `src/css.c:251` `static int expand_background(const char *val, css_decl *dst, int cap,
                           ...`
- `text` (function) `src/css.c:263` `* source text (rem_rebase, see below) rather than by threading a context here.
 *
 * Viewport uni...`
- `expand_box4` (function) `src/css.c:283` `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,
            ...`
- `expand_box2` (function) `src/css.c:288` `static int expand_box2(const char *val, int slot_start, int slot_end,
                       int ...`
- `interp_len` (function) `src/css.c:293` `static int interp_len(const char *v, int allow_auto, int *out)`
- `interp_lp` (function) `src/css.c:297` `static int interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_...`
- `lp_can_be_nonneg` (function) `src/css.c:302` `static int lp_can_be_nonneg(int px_val, int pct_pm)`
- `next_ws_token` (function) `src/css.c:306` `static int next_ws_token(const char **p, char *tok, size_t cap)`
- `interp_align` (function) `src/css.c:310` `static int interp_align(const char *v)`
- `interp_fontsize_ex` (function) `src/css.c:314` `static int interp_fontsize_ex(const char *v, int *abs_out)`
- `interp_lineheight` (function) `src/css.c:318` `static int interp_lineheight(const char *v)`
- `interp_weight` (function) `src/css.c:322` `static int interp_weight(const char *v)`
- `interp_style` (function) `src/css.c:326` `static int interp_style(const char *v)`
- `interp_textdeco` (function) `src/css.c:330` `static int interp_textdeco(const char *v)`
- `interp_display` (function) `src/css.c:334` `static int interp_display(const char *v)`
- `interp_gap` (function) `src/css.c:338` `static int interp_gap(const char *v)`
- `interp_justify` (function) `src/css.c:342` `static int interp_justify(const char *v)`
- `expand_grid_template_cols` (function) `src/css.c:346` `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)`
- `interp_fontfamily` (function) `src/css.c:352` `static int interp_fontfamily(const char *v)` -- Text-presentation family lives in css_text.c (single owner).
- `interp_texttransform` (function) `src/css.c:353` `static int interp_texttransform(const char *v)`
- `interp_opacity` (function) `src/css.c:354` `static int interp_opacity(const char *v)`
- `expand_valign` (function) `src/css.c:355` `static int expand_valign(const char *val, css_decl *dst, int cap)`
- `interp_transition_property` (function) `src/css.c:356` `static int interp_transition_property(const char *v)`
- `interp_whitespace` (function) `src/css.c:357` `static int interp_whitespace(const char *v)`
- `interp_tabsize` (function) `src/css.c:358` `static int interp_tabsize(const char *v)`
- `interp_textdeco_style` (function) `src/css.c:359` `static int interp_textdeco_style(const char *v)`
- `interp_textdeco_thickness` (function) `src/css.c:360` `static int interp_textdeco_thickness(const char *v)`
- `interp_aspect_ratio` (function) `src/css.c:361` `static int interp_aspect_ratio(const char *v, int *num, int *den)`
- `interp_direction` (function) `src/css.c:362` `static int interp_direction(const char *v)`
- `interp_liststyle` (function) `src/css.c:363` `static int interp_liststyle(const char *v)`
- `emit_spacing` (function) `src/css.c:364` `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
- `expand_shadow` (function) `src/css.c:365` `static int expand_shadow(const char *val, css_decl *dst, int cap)`
- `interp_position` (function) `src/css.c:369` `static int interp_position(const char *v)`
- `interp_boxsizing` (function) `src/css.c:378` `static int interp_boxsizing(const char *v)`
- `interp_float` (function) `src/css.c:384` `static int interp_float(const char *v)`
- `interp_clear` (function) `src/css.c:391` `static int interp_clear(const char *v)`
- `interp_visibility` (function) `src/css.c:401` `static int interp_visibility(const char *v)`
- `interp_overflow` (function) `src/css.c:408` `static int interp_overflow(const char *v)`
- `interp_cursor` (function) `src/css.c:440` `static int interp_cursor(const char *v)`
- `interp_text_overflow` (function) `src/css.c:472` `static int interp_text_overflow(const char *v)`
- `interp_word_break` (function) `src/css.c:478` `static int interp_word_break(const char *v)`
- `interp_overflow_wrap` (function) `src/css.c:486` `static int interp_overflow_wrap(const char *v)`
- `interp_border_collapse` (function) `src/css.c:494` `static int interp_border_collapse(const char *v)` -- if (csel_ci_eq(v, "break-all"))  return CSS_WB_BREAK;       /* greedy mid-line break if (csel_ci_eq(v...
- `number` (function) `src/css.c:503` `* number (no unit) as px (common in shorthand context like "10 5"). */
static int interp_border_s...`
- `interp_empty_cells` (function) `src/css.c:528` `static int interp_empty_cells(const char *v)` -- if (interp_len(tok, 0, &px) && px >= 0) { if (px > CSS_BORDER_SPACING_MAX) px = CSS_BORDER_SPACING_MAX; return px; }...
- `interp_caption_side` (function) `src/css.c:535` `static int interp_caption_side(const char *v)` -- px = css_round_clamp(num, 0, CSS_BORDER_SPACING_MAX); return px; } return -1; } /* empty-cells: show/hide. -1...
- `interp_table_layout` (function) `src/css.c:542` `static int interp_table_layout(const char *v)` -- static int interp_empty_cells(const char *v) { if (csel_ci_eq(v, "show")) return CSS_EC_SHOW; if (csel_ci_eq(v...
- `interp_font_variant` (function) `src/css.c:549` `static int interp_font_variant(const char *v)` -- static int interp_caption_side(const char *v) { if (csel_ci_eq(v, "top"))    return CSS_CS_TOP; if (csel_ci_eq(v...
- `interp_hyphens` (function) `src/css.c:557` `static int interp_hyphens(const char *v)` -- if (csel_ci_eq(v, "auto"))  return CSS_TL_AUTO; if (csel_ci_eq(v, "fixed")) return CSS_TL_FIXED; return -1; } /*...
- `interp_user_select` (function) `src/css.c:565` `static int interp_user_select(const char *v)` -- if (csel_ci_eq(v, "small-caps")) return CSS_FV_SMALL_CAPS; /* all-small-caps, petite-caps, etc: out of scope, fail...
- `interp_caret_color` (function) `src/css.c:574` `static int interp_caret_color(const char *v)` -- if (csel_ci_eq(v, "auto"))   return CSS_HY_AUTO; return -1; } /* user-select: none/text/all/auto. -1 unknown. static...
- `interp_appearance` (function) `src/css.c:586` `static int interp_appearance(const char *v)` -- appearance (CSS Basic UI 4 section 6.1).
- `interp_pointer_events` (function) `src/css.c:604` `static int interp_pointer_events(const char *v)` -- pointer-events.
- `interp_bg_repeat` (function) `src/css.c:616` `static int interp_bg_repeat(const char *v)` -- of them means "this element is a target" -- the same answer as `auto`.
- `interp_bg_size` (function) `src/css.c:626` `static int interp_bg_size(const char *v)` -- return -1; } /* background-repeat: repeat/no-repeat/repeat-x/repeat-y/space/round. -1 unknown. static int...
- `interp_bg_clip` (function) `src/css.c:633` `static int interp_bg_clip(const char *v)` -- if (csel_ci_eq(v, "repeat-x"))  return CSS_BGR_REPEAT_X; if (csel_ci_eq(v, "repeat-y"))  return CSS_BGR_REPEAT_Y; if...
- `interp_bg_origin` (function) `src/css.c:641` `static int interp_bg_origin(const char *v)` -- if (csel_ci_eq(v, "auto"))    return CSS_BGS_AUTO; if (csel_ci_eq(v, "cover"))   return CSS_BGS_COVER; if...
- `interp_bg_attachment` (function) `src/css.c:648` `static int interp_bg_attachment(const char *v)` -- if (csel_ci_eq(v, "border-box"))   return CSS_BGC_BORDER_BOX; if (csel_ci_eq(v, "padding-box"))  return...
- `interp_isolation` (function) `src/css.c:655` `static int interp_isolation(const char *v)` -- static int interp_bg_origin(const char *v) { if (csel_ci_eq(v, "padding-box"))  return CSS_BGO_PADDING_BOX; if...
- `interp_contain` (function) `src/css.c:661` `static int interp_contain(const char *v)` -- /* background-attachment: scroll/fixed/local. -1 unknown. static int interp_bg_attachment(const char *v) { if...
- `interp_content_visibility` (function) `src/css.c:682` `static int interp_content_visibility(const char *v)` -- while (*p == ' ' || *p == '\t') ++p; if (*p == '\0') break; char tok[CSS_TOK_MAX]; size_t k = 0; while (*p != '\0'...
- `interp_image_rendering` (function) `src/css.c:689` `static int interp_image_rendering(const char *v)` -- else if (csel_ci_eq(tok, "layout")) mask |= CSS_CONTAIN_LAYOUT; else if (csel_ci_eq(tok, "style"))  mask |=...
- `interp_color_scheme` (function) `src/css.c:696` `static int interp_color_scheme(const char *v)` -- static int interp_content_visibility(const char *v) { if (csel_ci_eq(v, "visible")) return CSS_CV_VISIBLE; if...
- `interp_accent_color` (function) `src/css.c:714` `static int interp_accent_color(const char *v)` -- const char *p = v; while (*p != '\0') { while (*p == ' ' || *p == '\t') ++p; if (*p == '\0') break; char...
- `interp_print_color_adjust` (function) `src/css.c:719` `static int interp_print_color_adjust(const char *v)` -- size_t k = 0; while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++; tok[k] = '\0'; if...
- `interp_forced_color_adjust` (function) `src/css.c:725` `static int interp_forced_color_adjust(const char *v)` -- return -1; } /* accent-color: auto -> CSS_LEN_AUTO; color -> 0xRRGGBB; -1 unknown. static int...
- `interp_mix_blend_mode` (function) `src/css.c:732` `static int interp_mix_blend_mode(const char *v)` -- /* print-color-adjust: economy/exact. -1 unknown. static int interp_print_color_adjust(const char *v) { if...
- `interp_object_fit` (function) `src/css.c:750` `static int interp_object_fit(const char *v)` -- if (csel_ci_eq(v, "overlay"))      return CSS_MB_OVERLAY; if (csel_ci_eq(v, "darken"))       return CSS_MB_DARKEN...
- `interp_list_style_pos` (function) `src/css.c:759` `static int interp_list_style_pos(const char *v)` -- if (csel_ci_eq(v, "color"))        return CSS_MB_COLOR; if (csel_ci_eq(v, "luminosity"))   return CSS_MB_LUMINOSITY...
- `interp_font_kerning` (function) `src/css.c:765` `static int interp_font_kerning(const char *v)` -- if (csel_ci_eq(v, "fill"))        return CSS_OFI_FILL; if (csel_ci_eq(v, "contain"))     return CSS_OFI_CONTAIN; if...
- `interp_text_rendering` (function) `src/css.c:772` `static int interp_text_rendering(const char *v)` -- /* list-style-position: inside/outside. -1 unknown. static int interp_list_style_pos(const char *v) { if...
- `interp_font_stretch` (function) `src/css.c:780` `static int interp_font_stretch(const char *v)` -- if (csel_ci_eq(v, "auto"))   return CSS_FK_AUTO; if (csel_ci_eq(v, "normal")) return CSS_FK_NORMAL; if...
- `interp_resize` (function) `src/css.c:793` `static int interp_resize(const char *v)` -- /* font-stretch: normal/condensed/expanded/etc. -1 unknown. static int interp_font_stretch(const char *v) { if...
- `interp_scroll_behavior` (function) `src/css.c:801` `static int interp_scroll_behavior(const char *v)` -- if (csel_ci_eq(v, "semi-expanded"))      return CSS_FS_SEMI_EXPANDED; if (csel_ci_eq(v, "extra-expanded"))...
- `interp_overscroll_behavior` (function) `src/css.c:823` `static int interp_overscroll_behavior(const char *v)` -- all, so every one of them behaves exactly like the default -- the same answer as `auto`.
- `interp_backface_visibility` (function) `src/css.c:830` `static int interp_backface_visibility(const char *v)` -- if (csel_ci_eq(v, "pan-x") || csel_ci_eq(v, "pan-y") || csel_ci_eq(v, "pan-left") || csel_ci_eq(v, "pan-right") ||...
- `interp_border_style` (function) `src/css.c:853` `static int interp_border_style(const char *v)`
- `interp_bwidth1` (function) `src/css.c:879` `static int interp_bwidth1(const char *v)`
- `interp_time_ms` (function) `src/css.c:888` `static int interp_time_ms(const char *v)` -- Parses a CSS time: "2s" → 2000, "500ms" → 500, "0s" → 0. * Returns -1 on invalid/missing unit.
- `emit_radius_corner` (function) `src/css.c:921` `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)` -- One corner longhand (border-top-left-radius and friends).
- `interp_bw_tok` (function) `src/css.c:929` `static int interp_bw_tok(const char *t, int *o)` -- One corner longhand (border-top-left-radius and friends).
- `interp_bs_tok` (function) `src/css.c:930` `static int interp_bs_tok(const char *t, int *o)`
- `interp_bc_tok` (function) `src/css.c:931` `static int interp_bc_tok(const char *t, int *o)`
- `expand_outline` (function) `src/css.c:996` `static int expand_outline(const char *val, css_decl *dst, int cap)`
- `interp_column_count` (function) `src/css.c:1012` `static int interp_column_count(const char *v)` -- `column-count`: a positive <integer>, or `auto`.
- `interp_column_width` (function) `src/css.c:1024` `static int interp_column_width(const char *v)` -- layout, for the same reason CSS_LEN_MAX lives on the emitter: it is an * anti-DoS policy of the box model, not a...
- `expand_columns` (function) `src/css.c:1035` `static int expand_columns(const char *val, css_decl *dst, int cap)` -- `columns` shorthand: <'column-width'> || <'column-count'> in either order, one or two tokens.
- `expand_flex_flow` (function) `src/css.c:1069` `static int expand_flex_flow(const char *val, css_decl *dst, int cap)` -- `flex-flow` shorthand: the direction and the wrap keyword in either order, one or two tokens.
- `expand_column_rule` (function) `src/css.c:1091` `static int expand_column_rule(const char *val, css_decl *dst, int cap)` -- `column-rule` shorthand: same <line-width> || <line-style> || <color> grammar * as `border`/`outline`, so it reuses...
- `interp_filter_pct` (function) `src/css.c:1103` `static int interp_filter_pct(const char *s)` -- Parse a percentage (or 0..1 float) from inside a filter function's parens. * Returns 0..100 (clamped), -1 on error.
- `interp_filter_deg` (function) `src/css.c:1117` `static int interp_filter_deg(const char *s)` -- Parse a degrees value (e.g. "45deg") from inside a filter function's parens.
- `filter_paren_body` (function) `src/css.c:1132` `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)` -- Helper: extract content inside filter(...) parens.
- `item` (function) `src/css.c:1145` `* timing list takes its first item (CSS Animations/Transitions 1: with one
 * transition/animatio...`
- `anim_easing_iv` (function) `src/css.c:1184` `static int anim_easing_iv(const char *tok)` -- Named easing shared by the animation/transition timing parsers (CSS Easing 1: the five keywords...
- `is_anim_ident` (function) `src/css.c:1196` `static int is_anim_ident(const char *tok)` -- True when tok is a CSS <custom-ident> (the shape an animation-name takes): starts with a letter, underscore, hyphen...
- `expand_animation` (function) `src/css.c:1212` `static int expand_animation(const char *val, css_decl *dst, int cap)` -- animation shorthand (CSS Animations 1 6.2): every longhand in any order in the first top-level comma item.
- `order` (function) `src/css.c:1438` `* declaration order (dx, dy, optional blur >= 0);`
- `blur` (function) `src/css.c:1473` `* consumes ONLY blur(Npx);`
- `expand_backdrop_filter` (function) `src/css.c:1476` `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)` -- backdrop-filter / -webkit-backdrop-filter (2026-07-19, glassmorphism v1): same lax space-separated function-list...
- `axis` (function) `src/css.c:1510` `* bare center displaces it to the free axis (`center right` = x:right, y:center).
 * Any other co...`
- `expand_bg_size` (function) `src/css.c:1626` `static int expand_bg_size(const char *val, css_decl *dst, int cap)` -- background-size (CSS Backgrounds 3 section 3.9): either a keyword (cover/contain) or one-to-two...
- `emit_content` (function) `src/css.c:1666` `static int emit_content(css_decl *dst, int cap, const char *str,
                        char (*c...` -- h = (n == 2) ? comp_px[1] : CSS_LEN_AUTO; hp = (n == 2) ? comp_pm[1] : 0; /* The bare keyword keeps its own code; an...
- `cap` (function) `src/css.c:1742` `* string past the cap (emit_content): a conforming declaration must not * count as a discard just because an icon...`
- `expand_content` (function) `src/css.c:1772` `static int expand_content(const char *val, css_decl *dst, int cap,
                          char...` -- R8: content property.
- `empty` (function) `src/css.c:1776` `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and...`
- `expand_grid_areas` (function) `src/css.c:1815` `static int expand_grid_areas(const char *val, css_decl *dst, int cap,
                           ...` -- grid-template-areas (CSS Grid 1 7.3): the value is a list of quoted strings, one per grid row.
- `expand_grid_area_lines` (function) `src/css.c:1843` `static int expand_grid_area_lines(const char *val, css_decl *dst, int cap)` -- grid-area on an ITEM.
- `expand_grid_line` (function) `src/css.c:1868` `static int expand_grid_line(const char *val, css_decl *dst, int cap, int p_start, int p_end)` -- if (!fx_grid_line_side(part, &side[k])) return 0; if (slash == NULL) break; p = slash + 1; if (k == 3) return 0...
- `expand_grid_area` (function) `src/css.c:1877` `static int expand_grid_area(const char *val, css_decl *dst, int cap)`
- `expand_grid_template` (function) `src/css.c:1916` `static int expand_grid_template(const char *val, css_decl *dst, int cap,
                        ...` -- grid-template: <rows> / <columns>            e.g.
- `sel_list_comma` (function) `src/css.c:1961` `static size_t sel_list_comma(const char *s, size_t i, size_t end);`
- `box_shadow_layer` (function) `src/css.c:1968` `static int box_shadow_layer(const char *val, size_t len, int out[6])` -- One box-shadow layer: up to four lengths in order dx, dy, blur, spread, an optional color, and an optional `inset`...
- `declaration` (function) `src/css.c:2004` `* invalid layer drops the whole declaration (fail closed). `none` is an explicit
 * no-shadow. ur...`
- `interp_flex_factor` (function) `src/css.c:2046` `static int interp_flex_factor(const char *v)` -- flex-grow / flex-shrink: a non-negative number stored x100 (0.5 -> 50), clamped to * [0, CSS_FLEX_FACTOR_MAX].
- `interp_flex_basis` (function) `src/css.c:2056` `static int interp_flex_basis(const char *v, int *out)` -- flex-basis: `auto`/`content` -> CSS_LEN_AUTO; a non-negative length -> px; a percentage as per-mille encoded...
- `column` (function) `src/css.c:2069` `* column (`flex: 1 1 0%`);`
- `expand_flex` (function) `src/css.c:2090` `static int expand_flex(const char *val, css_decl *dst, int cap)` -- flex shorthand -> the three contiguous P_FLEX_GROW/SHRINK/BASIS slots.
- `interp_align_kw` (function) `src/css.c:2135` `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` -- align-items / align-self / align-content / justify-items keyword. allow_auto is for * align-self; allow_dist...
- `interp_flex_direction` (function) `src/css.c:2148` `static int interp_flex_direction(const char *v)`
- `interp_box_orient` (function) `src/css.c:2166` `static int interp_box_orient(const char *v)` -- 2009 flexbox `box-orient` axis names onto `css_flex_direction`.
- `interp_flex_line_pack` (function) `src/css.c:2193` `static int interp_flex_line_pack(const char *v)` -- `flex-line-pack` (2012 align-content): the `flex-pack` vocabulary plus `stretch`, mapped onto the css_align_kw slots...
- `interp_flex_wrap` (function) `src/css.c:2203` `static int interp_flex_wrap(const char *v)`
- `interp_grid_flow` (function) `src/css.c:2211` `static int interp_grid_flow(const char *v)` -- if (csel_ci_eq(v, "justify")) return CSS_AK_SPACE_BETWEEN; if (csel_ci_eq(v, "distribute")) return...
- `copy_trim` (function) `src/css.c:2229` `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` -- Copies s[a,b) into dst (bounded, NUL-terminated), trimming ASCII whitespace from * both ends.
- `strip_important` (function) `src/css.c:2242` `static int strip_important(char *val)` -- Strips a trailing "!important" (case-insensitive, with optional whitespace before '!' and between '!' and the...
- `var` (function) `src/css.c:2267` `* cvr_resolve then substitutes var() references when a declaration's value is
 * interpreted (par...`
- `selector_matches_root` (function) `src/css.c:2289` `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m)` -- True when the caller's root matcher (css_media.scope_match) says the selector s[a,b) matches the document's <html>...
- `tr_mul` (function) `src/css.c:2416` `static void tr_mul(double out[6], const double l[6], const double r[6])` -- Right-multiply 2D affine matrices: out = l * r (r applies first).
- `matrix` (function) `src/css.c:2429` `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands...`
- `tr_decompose` (function) `src/css.c:2436` `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,
                        in...` -- QR-decompose an affine matrix into whole px/percent/degree slots.
- `parse_matrix6` (function) `src/css.c:2459` `static int parse_matrix6(const char *p, size_t argn, double m6[6])` -- Parse matrix(a,b,c,d,e,f): six comma-separated unitless numbers.
- `split_top_args` (function) `src/css.c:2491` `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,
               ...` -- Split a top-level comma list honouring paren depth.
- `LIST` (function) `src/css.c:2514` `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose...`
- `translate3d` (function) `src/css.c:2521` `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine
 * renders z as nothing,...`
- `translateX` (function) `src/css.c:2784` `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc...`
- `parse_angle_deg` (function) `src/css.c:2788` `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);`
- `expand_transform_list` (function) `src/css.c:2791` `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);`
- `translateZ` (function) `src/css.c:2793` `* translateZ(), rotateX(0) and rotateY(0) emit the identity (with the stacking * context Firefox builds);`
- `function` (function) `src/css.c:2795` `* transform function (perspective/rotate3d/...), or unparseable syntax,
 * rejects the WHOLE decl...`
- `origin_component` (function) `src/css.c:2992` `static int origin_component(const char *tok, int axis, int *out)` -- One transform-origin component: keyword (axis-checked), a percent, or a bare zero. axis: 0 = x (left/right valid), 1...
- `expand_transform_origin` (function) `src/css.c:3018` `static int expand_transform_origin(const char *val, css_decl *dst, int cap)` -- transform-origin (M1.2c): 1-2 values; keywords and percents only (px lengths fail closed -- the parser has no box...
- `expand_gap` (function) `src/css.c:3050` `static int expand_gap(const char *val, css_decl *dst, int cap)` -- gap / grid-gap (2026-07-10): one value keeps the pre-existing semantics (both axes; row-gap stays unset and falls...
- `shorthand` (function) `src/css.c:3069` `* An uninterpretable token drops the whole shorthand (fail closed). */
static int expand_place(co...`
- `property` (function) `src/css.c:3104` `* error drops the whole property (fail closed). */
static int expand_clip(const char *val, css_de...`
- `font_list_alias` (function) `src/css.c:3158` `static void font_list_alias(const css_sheet *sheet, const char *ls, char *out, size_t cap)` -- Copies the normalized family list `ls` into out, replacing every name that matches a local()-only @font-face of the...
- `font_list_norm` (function) `src/css.c:3192` `static int font_list_norm(const char *val, char *out, size_t cap)`
- `writing` (function) `src/css.c:3236` `* Wide keywords claim BOTH slots without writing (inheritance then flows, as
 * the tail does for...`
- `shorthand` (function) `src/css.c:3278` `* generic bucket keeps the rest of the shorthand (same net effect as the
 * font-family longhand ...`
- `caller` (function) `src/css.c:3358` `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached...`
- `interpret_prop_dispatch` (function) `src/css.c:3370` `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,
   ...`
- `slots` (function) `src/css.c:3528` `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return...`
- `sentinel` (function) `src/css.c:3640` `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);`
- `here` (function) `src/css.c:3843` `* servers have no form here (fail closed). */ int o = csel_ci_eq(val, "none") ? CSS_SVG_PAINT_NONE : interp_color(val);`
- `wide_claim` (function) `src/css.c:4074` `static int wide_claim(const char *prop, css_decl *dst, int cap,
                      char (*urlt...` -- SHORTHAND it applies to every longhand the shorthand expands to.
- `interpret_prop` (function) `src/css.c:4114` `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,
            ...` -- The two value-level rules that hold for EVERY property, applied once around the dispatch so no per-property branch...
- `drop_copy_text` (function) `src/css.c:4141` `static void drop_copy_text(char *dst, size_t cap, const char *src)` -- Copies hostile CSS text into a fixed report buffer: bounded, NUL-terminated, truncated with a visible "..." marker...
- `drop_record` (function) `src/css.c:4160` `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)` -- Records one dropped declaration, coalescing by (property, cause).
- `raw_add` (function) `src/css.c:4186` `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)` -- Interprets one declaration span s[0,n) into dst (up to cap).
- `interpret_decls` (function) `src/css.c:4299` `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,
               ...` -- Splits a ';'-separated declaration block into dst (up to cap).
- `sheet_pools_reserve` (function) `src/css.c:4357` `static void sheet_pools_reserve(css_sheet *sh)`
- `add_rule` (function) `src/css.c:4363` `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,
                     siz...` -- while (nc - n < CSS_POOL_HEADROOM && nc < hard_cap) nc *= 2; if (nc > hard_cap) nc = hard_cap; char...
- `skip_at_rule` (function) `src/css.c:4476` `static size_t skip_at_rule(const char *s, size_t i, size_t n)` -- Skips an @-rule starting at s[i] ('@'): to the terminating ';' or past a * brace-balanced block.
- `block_end` (function) `src/css.c:4492` `static size_t block_end(const char *s, size_t open, size_t n)` -- Index just past the '}' that closes the block whose '{' is at s[open]. n if * unbalanced.
- `at_is_media` (function) `src/css.c:4514` `static int at_is_media(const char *s, size_t i, size_t n)` -- A media query list s[a,b), evaluated by the Media Queries 4 module against the render width (the only real datum...
- `at_keyword` (function) `src/css.c:4525` `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)` -- True when s[i] ('@') begins the at-keyword kw (lowercase, without '@') followed * by a delimiter.
- `csel_substr` (function) `src/css.c:4547` `return known && csel_substr(val, "var(", 1);`
- `supports_selector_ok` (function) `src/css.c:4550` `static int supports_selector_ok(void *ctx, const char *sel)`
- `supports_matches` (function) `src/css.c:4559` `static int supports_matches(const char *s, size_t a, size_t b)`
- `layer_register` (function) `src/css.c:4613` `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,
                     ...` -- Registers the layer name s[a,b) (trimmed; empty = anonymous) nested under the sheet's current layer, and returns its...
- `collect_custom_props_scoped` (function) `src/css.c:4656` `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,
                ...` -- Structure-aware custom-property collection (see the block comment above cvr_collect_decls): walks s[start,end) with...
- `parse_block` (function) `src/css.c:4731` `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                 ...` -- Parses rules in s[start,end).
- `download` (function) `src/css.c:4887` `* the download (spec/webfont.md b3b). An empty src_url
                     * simply never resolv...`
- `rem_ident_ch` (function) `src/css.c:5019` `static int rem_ident_ch(char c)` -- True for a character that continues a CSS identifier, so a `rem` glued to one is * part of a name and not a unit.
- `rem_num_starts_after` (function) `src/css.c:5027` `static int rem_num_starts_after(char prev)` -- True when a number may START at a character preceded by prev -- i.e. prev cannot be part of a longer name or number.
- `rem_emit_px` (function) `src/css.c:5037` `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)` -- Appends the px equivalent of num rem.
- `len_unit_px` (function) `src/css.c:5067` `static double len_unit_px(const char *u, size_t len, const len_rebase_ctx *c)` -- px per unit for a unit identifier u[0,len) under c, or 0 when c leaves it alone.
- `len_rebase` (function) `src/css.c:5097` `static char *len_rebase(const char *s, size_t n, const len_rebase_ctx *c, size_t *outlen)` -- width family) in s[0,n) into `<number x scale>px`.
- `rem_rebase` (function) `src/css.c:5163` `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)`
- `sheet_index` (function) `src/css.c:5171` `static void sheet_index(css_sheet *sh)` -- Rewinds a sheet to empty while keeping every allocation, so the text can be * re-parsed in place.
- `sheet_rewind` (function) `src/css.c:5176` `static void sheet_rewind(css_sheet *sh)`
- `sheet_root_font_px` (function) `src/css.c:5221` `static double sheet_root_font_px(const css_sheet *sh)` -- The root element's font-size in px, as the cascade resolves it (16px when the sheet leaves the root alone).
- `strip_comments` (function) `src/css.c:5229` `static char *strip_comments(const char *text, size_t len, size_t *outlen)` -- Removes C-style block comments into a fresh NUL-terminated buffer (each comment * becomes one space).
- `var` (function) `src/css.c:5239` `* collected and forty var() declarations -- font sizes, widths, radii, the
     * whole theme -- ...`
- `css_parse` (function) `src/css.c:5264` `css_status css_parse(const char *text, size_t len, css_sheet **out)`
- `css_parse_media` (function) `src/css.c:5268` `css_status css_parse_media(const char *text, size_t len, const css_media *media,
                ...`
- `css_parse_scoped` (function) `src/css.c:5273` `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,
               ...`
- `css_parse_logged` (function) `src/css.c:5278` `css_status css_parse_logged(const char *text, size_t len, const css_media *media,
               ...`
- `consumer` (function) `src/css.c:5312` `* consumer (shorthands, calc(), var() values) gets it with no context
         * threaded through...`
- `css_free` (function) `src/css.c:5370` `void css_free(css_sheet *s)`
- `content_attr_of` (function) `src/css.c:5392` `static const char *content_attr_of(const css_element *el, const char *name)` -- Looks up an attribute value on the element being styled (names are stored * lowercased by css_chain; the query is...
- `apply_decl` (function) `src/css.c:5401` `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...`
- `page_view` (function) `src/css.c:5408` `* the generated text reaches page_view (which materialises it as a synthetic * run);`
- `parent` (function) `src/css.c:5441` `* property from the parent (`inherit`), and an unset non-inherited one
         * stands at its i...`
- `computed_font_size` (function) `src/css.c:5848` `static double computed_font_size(const css_style *o, const css_element *el)`
- `cand_cmp` (function) `src/css.c:5864` `static int cand_cmp(const void *pa, const void *pb)`
- `apply_var_source` (function) `src/css.c:5929` `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
        ...` -- Re-resolves one var() source ("prop\0value") against the element's scope and * applies what it interprets to...
- `apply_rule` (function) `src/css.c:5956` `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...` -- Applies one matched rule. es == NULL: the page-global meaning of every var() (markers skipped, their spans applied).
- `fold_font_relative` (function) `src/css.c:5994` `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,
                         ...` -- computed font-size.
- `css_resolve_el` (function) `src/css.c:6025` `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         ...`
- `css_resolve_el_ex` (function) `src/css.c:6034` `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,
                      ...`
- `pseudo_of` (function) `src/css.c:6041` `static int pseudo_of(int which)` -- return css_resolve_el_ex(sheet, el, inline_style, inline_len, NULL); } static css_style resolve_core(const css_sheet...
- `css_resolve_pseudo` (function) `src/css.c:6050` `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)`
- `resolve_core` (function) `src/css.c:6061` `static css_style resolve_core(const css_sheet *sheet, const css_element *el,
                    ...` -- The cascade. want_pseudo 0 resolves the ELEMENT (a ::before/::after rule only hands it `content`)...
- `css_resolve` (function) `src/css.c:6316` `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                  ...`
- `NULL` (function) `src/css.c:6340` `* Sheet can be NULL (inline style, no @keyframes). */
void css_resolve_anim_keyframes(css_style *...`
- `css_font_face_count` (function) `src/css.c:6372` `size_t css_font_face_count(const css_sheet *sheet)`
- `css_font_face_at` (function) `src/css.c:6376` `int css_font_face_at(const css_sheet *sheet, size_t i,
                     char *family, size_t ...`
- `css_parse_inline` (function) `src/css.c:6386` `css_style css_parse_inline(const char *style, size_t len)`

## src/css_atrule.c
Depends on: `include/css_atrule.h`, `include/css_select.h`
- `skip_ws` (function) `src/css_atrule.c:17` `static size_t skip_ws(const char *s, size_t i, size_t b)`
- `keyword_at` (function) `src/css_atrule.c:23` `static int keyword_at(const char *s, size_t i, size_t b, const char *kw)` -- Scratch size for one declaration or selector handed to the caller.
- `close_paren` (function) `src/css_atrule.c:33` `static size_t close_paren(const char *s, size_t open, size_t b)` -- Index of the ')' matching the '(' at s[open], or b when unbalanced.
- `copy_trimmed` (function) `src/css_atrule.c:54` `static int copy_trimmed(const char *s, size_t a, size_t b, char *dst, size_t cap, int lower)` -- Copies s[a,b) trimmed into dst (cap bytes, NUL-terminated); 0 if it does not fit * or is empty. lower != 0...
- `eval_declaration` (function) `src/css_atrule.c:68` `static int eval_declaration(const char *s, size_t a, size_t b, const car_ops *ops, int *ok)` -- True when s[a,b) (inside a pair of parens) is a declaration `prop: value` * rather than a nested condition.
- `eval_in_parens` (function) `src/css_atrule.c:85` `static int eval_in_parens(const char *s, size_t *i, size_t b, const car_ops *ops,
               ...` -- while (i < b && (csel_ident_ch(s[i]) || s[i] == '-')) ++i; if (i == n0) { *ok = 0; return 0; } size_t n1 = i; i =...
- `eval_condition` (function) `src/css_atrule.c:114` `static int eval_condition(const char *s, size_t a, size_t b, const car_ops *ops,
                ...`
- `car_supports` (function) `src/css_atrule.c:141` `int car_supports(const char *s, size_t a, size_t b, const car_ops *ops)`
- `car_layer_rank` (function) `src/css_atrule.c:148` `int car_layer_rank(car_layers *L, const char *name, size_t len)`
- `car_effective_spec` (function) `src/css_atrule.c:171` `int car_effective_spec(int spec, int layer, int important)`


Next: [API_p6.md](API_p6.md)
