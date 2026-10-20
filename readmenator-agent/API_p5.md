# API (page 5 of 11)
Previous: [API_p4.md](API_p4.md)

## include/ui.h
Imported by: `gui/browser_ui.c`, `gui/freedom_view.c`, `gui/ui_render.c`, `src/freedom.c`, `src/ui_layout.c`, `tests/test_ui.c`
- `space` (function) `include/ui.h:43` `* Breaks at the last fitting space (the break space is consumed), hard-breaks * words longer than max_cols, and...`
- `ui_layout_free` (function) `include/ui.h:51` `void ui_layout_free(ui_layout *lay);` -- Word-wraps text into lines of at most max_cols columns (monospace model).
- `ui_clamp_scroll` (function) `include/ui.h:54` `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines);` -- Word-wraps text into lines of at most max_cols columns (monospace model).
- `available` (function) `include/ui.h:85` `* cheapest artifact to inspect a render where no display is available (CI, an AI * agent): export, then read the PNG...`
- `out` (function) `include/ui.h:97` `* ui_render_png does and fills *out (jg_init'ed by the caller) with one rect per * element in document coordinates...`
- `placeholders` (function) `include/ui.h:107` `* above always draw image placeholders (no worker to decode hostile bytes);`
- `disk` (function) `include/ui.h:112` `* images are read from disk (confined to the document directory by render_doc). * top_url is the page origin (https...`
- `images` (function) `include/ui.h:114` `* fetcher loads no images (placeholders, as before). Any image that fails falls back * to its placeholder...`
- `ui_render_viewport_w` (function) `include/ui.h:141` `int ui_render_viewport_w(void);` -- The fixed canvas width (px) every headless render (ui_render_png/pdf, ui_dump_layout) lays out at.

## include/url.h
Imported by: `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_url.c`, `gui/browser_ui.c`, `include/form.h`, `include/js_dom.h`, `include/js_location.h`, `src/freedom.c`, `src/js_location.c`, `src/link_nav.c`, `src/prefetch.c`, `src/render_doc.c`, `src/secure_fetch.c`, `src/tab.c`, `src/url.c`, `src/webfont_load.c`, `tests/test_js_dom.c`, `tests/test_tab.c`, `tests/test_url.c`
- `url_is_https` (function) `include/url.h:42` `int url_is_https(const char *s);` -- Nonzero iff s begins (case-insensitively) with "https://" and the host is * neither empty nor a leading '/'.
- `url_has_scheme` (function) `include/url.h:46` `int url_has_scheme(const char *s);` -- Nonzero iff s begins with "<scheme>:" per RFC 3986 * (ALPHA *( ALPHA / DIGIT / "+" / "-" / "." ) ":").
- `url_authority_len` (function) `include/url.h:51` `size_t url_authority_len(const char *url);` -- Length of "https://host[:port]" within a validated absolute https URL: the index of the first '/', '?' or '#' after...
- `URL_ERR_NOT_HTTPS` (function) `include/url.h:109` `* URL_ERR_NOT_HTTPS (out untouched);`
- `path` (function) `include/url.h:115` `* absolute path ("file:///..."). NULL => 0. */ int url_is_file(const char *s);`
- `url_file_path` (function) `include/url.h:121` `const char *url_file_path(const char *s);` -- Returns the absolute filesystem path inside a "file:///path" URL (i.e. the "/path" part), or NULL when s is not a...
- `url` (function) `include/url.h:126` `* Every field ALIASES the input url (not owned, valid while url is alive);`
- `password` (function) `include/url.h:152` `* username and password (owned, must be freed) into *username_out and * *password_out, and returns URL_OK. When...`

## include/util.h
Imported by: `src/browser.c`, `src/disk_store.c`, `src/dom.c`, `src/hostblock.c`, `src/html_parse.c`, `src/media_decoder.c`, `src/page_view.c`, `src/render_doc.c`, `src/renderer.c`, `src/tab.c`
- `write_full` (function) `include/util.h:15` `static inline int write_full(int fd, const void *buf, size_t n)`
- `read_full` (function) `include/util.h:26` `static inline int read_full(int fd, void *buf, size_t n)`
- `mem_contains_ci` (function) `include/util.h:43` `static inline int mem_contains_ci(const void *hay, size_t hlen, const char *needle)` -- Returns 1 when the trusted lowercase-ASCII needle (letters/digits) occurs in the hostile, length-delimited haystack...
- `utf8_seq_len` (function) `include/util.h:57` `static inline size_t utf8_seq_len(unsigned char c)`
- `fnv1a` (function) `include/util.h:67` `static inline uint64_t fnv1a(const char *s, size_t n)`

## include/web_storage.h
Imported by: `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_web_storage.c`, `gui/browser_ui.c`, `src/js_dom.c`, `src/js_trusted.c`, `src/tab.c`, `src/web_storage.c`, `tests/test_js_dom.c`, `tests/test_tab.c`, `tests/test_web_storage.c`
- `wst_new` (function) `include/web_storage.h:25` `wst_db *wst_new(void);` -- web_storage — in-MEMORY localStorage for trusted hosts (owner decision: nothing persists to disk).
- `wst_free` (function) `include/web_storage.h:28` `void wst_free(wst_db *db);` -- before it may touch the database.
- `wst_encode` (function) `include/web_storage.h:33` `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len);` -- Snapshot of origin's pairs ([n:u32]([klen:u32][key][vlen:u32][val])*, little-endian) into an owned *out of *len bytes.
- `wst_decode_check` (function) `include/web_storage.h:37` `int wst_decode_check(const char *blob, size_t len);` -- Pure validation of a snapshot: 0 when it is complete and well-formed (counts and * lengths fit, total <= WST_QUOTA...
- `wst_replace` (function) `include/web_storage.h:42` `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len);` -- Replaces origin's contents with the snapshot after wst_decode_check.
- `full` (function) `include/web_storage.h:45` `* validating it in full (wst_decode_check). Returns 0, or -1 when invalid (fn is then * never called). The one...`
- `wst_origin_bytes` (function) `include/web_storage.h:59` `size_t wst_origin_bytes(const wst_db *db, const char *origin);` -- Builds a snapshot from n pairs into an owned *out.

## include/webfont.h
Imported by: `fuzz/fuzz_webfont.c`, `gui/browser_ui.c`, `src/css.c`, `src/freedom.c`, `src/text_shape.c`, `src/webfont.c`, `src/webfont_load.c`, `tests/test_css.c`, `tests/test_page_view.c`, `tests/test_text_shape.c`, `tests/test_webfont.c`, `tests/test_webfont_load.c`
- `here` (function) `include/webfont.h:38` `* set with the decoded bytes owned here (freed by wf_list_free);`
- `wf_scan` (function) `include/webfont.h:52` `int wf_scan(const char *css, size_t len, wf_list *out);`
- `wf_list_free` (function) `include/webfont.h:53` `void wf_list_free(wf_list *l);`
- `boundaries` (function) `include/webfont.h:57` `* boundaries (scan_inline accumulation, loader collection). */ void wf_ref_move(wf_ref *dst, wf_ref *src);`
- `wf_supported_format` (function) `include/webfont.h:60` `int wf_supported_format(const char *fmt);`
- `wf_name_hash` (function) `include/webfont.h:69` `static inline unsigned wf_name_hash(const char *s, size_t n)` -- FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.

## include/webfont_load.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/webfont_load.c`, `tests/test_webfont_load.c`
- `free` (function) `include/webfont_load.h:31` `* free()), *out_status the HTTP status. Nonzero on refusal/error (fail-closed: * the face is skipped, never the...`
- `skipped` (function) `include/webfont_load.h:47` `* URLs are skipped (no base). Returns faces registered (>= 0) otherwise. */ int wf_load_document(wf_fetch_fn fetch...`

## include/wl_display.h
Imported by: `src/freedom.c`, `src/wl_display.c`, `tests/test_wl_display.c`
- `pure` (function) `include/wl_display.h:3` `* wd_pick is pure (no I/O);`
- `wd_pick` (function) `include/wl_display.h:16` `int wd_pick(const char *const *names, size_t n, char *out, size_t cap);` -- Choose the lowest-numbered "wayland-N" (N = digits only) from names[0..n).
- `wd_resolve_env` (function) `include/wl_display.h:20` `int wd_resolve_env(void);` -- If WAYLAND_DISPLAY is unset/empty, set it from the sockets found in XDG_RUNTIME_DIR. * Returns WD_OK if the variable...

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


Next: [API_p6.md](API_p6.md)
