# Subsystem: gui

## gui/browser_ui.c
- Layer: presentation
- Language: c
- Symbols:
  - `ui_menu_item` (struct, line 174)
  - `ui_input_state` (struct, line 212)
  - `ui_image` (struct, line 236)
  - `ui_bg_image` (struct, line 249)
  - `tab_ctx` (struct, line 266)
  - `browser_window` (struct, line 282)
  - `fetch_prep` (struct, line 1486)
  - `fetch_job` (struct, line 1564)
  - `rc_frag` (struct, line 2820)
  - `rc_row` (struct, line 2880)
  - `rc_box` (struct, line 2899)
  - `rc_layout` (struct, line 2950)
  - `rc_open_box` (struct, line 2986)
  - `rc_state` (struct, line 3044)
  - `rc_ext` (struct, line 3618)
  - `item_sides` (struct, line 4413)
  - `rc_defer_col` (struct, line 6258)
  - `rc_defer` (struct, line 6265)
  - `freebug_window` (struct, line 12883)
  - `ui_menu_action` (enum, line 157)
  - `ui_hot` (enum, line 205)
  - `rc_rowkind` (enum, line 2878)
  - `bs` (type_alias, line 266) `typedef struct tab_ctx { browser_state bs;`
  - `freebug_window` (type_alias, line 532) `typedef struct freebug_window freebug_window;`
  - `allowlisted` (type_alias, line 1486) `typedef struct fetch_prep { int allowlisted;`
  - `font_size` (type_alias, line 2819) `typedef struct rc_frag { double x, width, font_size;`
  - `kind` (type_alias, line 2879) `typedef struct rc_row { rc_rowkind kind;`
  - `h` (type_alias, line 2899) `typedef struct rc_box { double x, top, w, h;`
  - `block_id` (type_alias, line 2986) `typedef struct rc_open_box { int block_id;`
  - `line_desc` (type_alias, line 3043) `typedef struct rc_state { double cur_top, pending_gap, pen_x, line_asc, line_desc;`
  - `family` (type_alias, line 3618) `typedef struct rc_ext { int family;`
  - `mr` (type_alias, line 4413) `typedef struct item_sides { double ml, mr;`
  - `key` (type_alias, line 6258) `typedef struct rc_defer_col { int key;`
  - `col` (type_alias, line 6265) `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];`
  - `now_ms` (function, line 145) `static uint64_t now_ms(void)`
  - `gutter` (function, line 551) `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
  - `apply_zoom` (function, line 572) `static void apply_zoom(browser_window *w)`
  - `buffer_release` (function, line 583) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 589) `static void destroy_buffer(browser_window *w)`
  - `ensure_buffer` (function, line 595) `static int ensure_buffer(browser_window *w)`
  - `read_file` (function, line 625) `static char *read_file(const char *path, size_t *out_len)`
  - `build_file_origin` (function, line 664) `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)`
  - `load_host_file` (function, line 674) `static void load_host_file(hb_set *s, const char *dir, const char *name, hb_list list)`
  - `build_host_filter` (function, line 691) `static hb_set *build_host_filter(void)`
  - `build_js_filter` (function, line 738) `static hb_set *build_js_filter(void)`
  - `build_impersonate_filter` (function, line 741) `static hb_set *build_impersonate_filter(void)`
  - `freedom_write_dir` (function, line 746) `static int freedom_write_dir(char *out, size_t cap)`
  - `add_current_host_to_list` (function, line 771) `static void add_current_host_to_list(browser_window *w, int sel)`
  - `load_favorites` (function, line 839) `static void load_favorites(browser_window *w)`
  - `omni_refresh` (function, line 885) `static void omni_refresh(browser_window *w)`
  - `profile_sync` (function, line 916) `static void profile_sync(browser_window *w)`
  - `remember_visit` (function, line 933) `static void remember_visit(browser_window *w, const char *url)`
  - `bookmark_toggle_current` (function, line 941) `static void bookmark_toggle_current(browser_window *w)`
  - `proxy_addr_from_env` (function, line 965) `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...`
  - `init_net_config` (function, line 979) `static void init_net_config(browser_window *w)`
  - `is_https_url` (function, line 989) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 993) `static int is_http_url(const char *s)`
  - `host_from_url` (function, line 1004) `static int host_from_url(const char *url, char *out, size_t outsz)`
  - `toggle_fullscreen` (function, line 1034) `static void toggle_fullscreen(browser_window *w)`
  - `input_is_interactive` (function, line 1049) `static int input_is_interactive(int input_type)`
  - `input_is_editable` (function, line 1055) `static int input_is_editable(int input_type)`
  - `free_inputs` (function, line 1061) `static void free_inputs(browser_window *w)`
  - `free_images` (function, line 1069) `static void free_images(browser_window *w)`
  - `find_bg_image` (function, line 1108) `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)`
  - `layout` (function, line 1120) `* shared by layout (row height) and paint (blit), so they cannot drift apart. */
static int image...`
  - `rebuild_inputs` (function, line 1169) `static void rebuild_inputs(browser_window *w)`
  - `find_input_state` (function, line 1194) `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)`
  - `clear_doc` (function, line 1202) `static void clear_doc(browser_window *w)`
  - `set_cache` (function, line 1212) `static void set_cache(browser_window *w, char *html, size_t len, const char *top)`
  - `surface_from_pixels` (function, line 1223) `static cairo_surface_t *surface_from_pixels(const tab_image *img)`
  - `fetch_follow_navigable` (function, line 1290) `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...`
  - `GET` (function, line 1326) `* a GET (Zero Trust). cfg->policy is restored before returning. */
static sf_status fetch_post_na...`
  - `gui_subresource_fetch` (function, line 1368) `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...`
  - `prepare_fetch` (function, line 1495) `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...`
  - `fetch_job_free` (function, line 1596) `static void fetch_job_free(fetch_job *j)`
  - `stream_progress_cb` (function, line 1616) `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)`
  - `fetch_thread` (function, line 1640) `static void *fetch_thread(void *arg)`
  - `fetch_launch` (function, line 1688) `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...`
  - `load_images` (function, line 1809) `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
  - `load_bg_images` (function, line 1893) `static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
  - `page_js_host_allowlisted` (function, line 1948) `static int page_js_host_allowlisted(const browser_window *w)`
  - `compute_page_js` (function, line 1954) `static int compute_page_js(const browser_window *w)`
  - `seed_session_cookies` (function, line 1968) `static void seed_session_cookies(tab *t, int trusted, const char *url)`
  - `foldback_session_cookies` (function, line 1981) `static void foldback_session_cookies(const char *url, const char *jar)`
  - `drop_repl_worker` (function, line 2000) `static void drop_repl_worker(browser_window *w)`
  - `schedule_js_tick` (function, line 2014) `static void schedule_js_tick(browser_window *w, int next_ms)`
  - `render_current_ex` (function, line 2024) `static void render_current_ex(browser_window *w, int allow_js_nav)`
  - `render_current` (function, line 2196) `static void render_current(browser_window *w)`
  - `show_busy` (function, line 2203) `static void show_busy(browser_window *w)`
  - `show_fetch_error` (function, line 2212) `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...`
  - `arrives` (function, line 2263) `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...`
  - `strcmp` (function, line 2331) `&& strcmp(auth_host_buf, w->auth_host) != 0)`
  - `tab_save` (function, line 2392) `static void tab_save(browser_window *w)`
  - `tab_restore` (function, line 2409) `static void tab_restore(browser_window *w)`
  - `free_live_page` (function, line 2426) `static void free_live_page(browser_window *w)`
  - `tab_ctx_release` (function, line 2435) `static void tab_ctx_release(tab_ctx *c)`
  - `tab_switch` (function, line 2459) `static void tab_switch(browser_window *w, int idx)`
  - `tab_new` (function, line 2478) `static void tab_new(browser_window *w, const char *url)`
  - `uitab_close` (function, line 2511) `static void uitab_close(browser_window *w, int idx)`
  - `newtab_x` (function, line 2553) `static double newtab_x(const browser_window *w)`
  - `tab_title` (function, line 2560) `static const char *tab_title(const browser_window *w, int i)`
  - `tabbar_top` (function, line 2576) `static double tabbar_top(const browser_window *w)`
  - `toolbar_top` (function, line 2582) `static double toolbar_top(const browser_window *w)`
  - `content_geometry` (function, line 2589) `static void content_geometry(const browser_window *w, double *top, double *height)`
  - `content_width` (function, line 2616) `static double content_width(const browser_window *w)`
  - `html_center_offset` (function, line 2626) `static double html_center_offset(const browser_window *w)`
  - `scrollbar_metrics` (function, line 2640) `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...`
  - `scrollbar_drag_to` (function, line 2668) `static void scrollbar_drag_to(browser_window *w)`
  - `draw_scrollbar` (function, line 2685) `static void draw_scrollbar(cairo_t *cr, const browser_window *w)`
  - `window_button_rects` (function, line 2722) `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...`
  - `toolbar_rects` (function, line 2732) `static void toolbar_rects(const browser_window *w,
                          double *back_x, doub...`
  - `toolbar_button_at` (function, line 2747) `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)`
  - `hot_actionable` (function, line 2763) `static int hot_actionable(const browser_window *w, ui_hot hot)`
  - `menu_panel_rect` (function, line 2774) `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...`
  - `ua_box_rect` (function, line 2790) `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...`
  - `draw_text` (function, line 2800) `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)`
  - `rc_float_bottom` (function, line 3138) `static double rc_float_bottom(const rc_state *s)`
  - `rc_float_clear` (function, line 3147) `static void rc_float_clear(rc_state *s)`
  - `rc_float_refresh` (function, line 3160) `static void rc_float_refresh(rc_state *s, double line_h)`
  - `rc_float_fit_line` (function, line 3206) `static void rc_float_fit_line(rc_state *s, double line_h)`
  - `line_limit` (function, line 3225) `static double line_limit(const rc_state *s, double content_w)`
  - `rc_free` (function, line 3230) `static void rc_free(rc_layout *L)`
  - `rc_add_box` (function, line 3239) `static rc_box *rc_add_box(rc_layout *L)`
  - `rc_add_frag` (function, line 3251) `static rc_frag *rc_add_frag(rc_layout *L)`
  - `rc_add_row` (function, line 3266) `static rc_row *rc_add_row(rc_layout *L)`
  - `family_face` (function, line 3278) `static const char *family_face(int family)`
  - `content_font` (function, line 3296) `static void content_font(cairo_t *cr, double size, int bold, int italic, int family)`
  - `set_rgb_alpha` (function, line 3309) `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)`
  - `utf8_clen` (function, line 3318) `static size_t utf8_clen(const char *s, size_t n)`
  - `draw_slice` (function, line 3358) `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)`
  - `frag_styled` (function, line 3371) `static int frag_styled(const rc_frag *f)`
  - `styled_advance` (function, line 3378) `static double styled_advance(cairo_t *cr, const rc_frag *f)`
  - `styled_draw` (function, line 3394) `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)`
  - `block_style` (function, line 3411) `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
  - `block_margins` (function, line 3438) `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...`
  - `add` (function, line 3468) `* about to add (top/h passed in). A box that survived a line wrap simply ends at the
 * wrap -- m...`
  - `run` (function, line 3503) `* continuation run (block_id < 0 with no block break) deliberately skips reconcile
 * to stay on ...`
  - `flush_line` (function, line 3528) `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `open_line_height` (function, line 3586) `static double open_line_height(const rc_state *s, const ui_theme *th)`
  - `open_line` (function, line 3599) `static void open_line(rc_layout *L, rc_state *s)`
  - `flow_emit_frag` (function, line 3647) `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...`
  - `flow_text` (function, line 3714) `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...`
  - `replaced_inline_size` (function, line 3966) `static int replaced_inline_size(const browser_window *w, const rd_block *b,
                     ...`
  - `replaced_is_inline_level` (function, line 3996) `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)`
  - `place_inline_replaced` (function, line 4009) `static int place_inline_replaced(rc_layout *L, rc_state *s, const ui_theme *th,
                 ...`
  - `css_replaced_box` (function, line 4064) `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...`
  - `emit_replaced_row` (function, line 4073) `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `flow_text_block` (function, line 4176) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
  - `item_root_box_in` (function, line 4288) `static int item_root_box_in(const rd_doc *doc, size_t b0, size_t b1, int cbox)`
  - `item_root_box` (function, line 4324) `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)`
  - `css_align_to_bt` (function, line 4333) `static int css_align_to_bt(int align_kw)`
  - `box_edge_px` (function, line 4343) `static double box_edge_px(int wpx)`
  - `rc_box_copy_decoration` (function, line 4363) `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)`
  - `box_is_strict_descendant` (function, line 4442) `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)`
  - `item_sides_at_level` (function, line 4464) `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,
                  ...`
  - `container_box_of` (function, line 4493) `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)`
  - `table` (function, line 4515) `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...`
  - `row` (function, line 4575) `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...`
  - `way` (function, line 4616) `* intrinsic box either way (it does not wrap below its own size). */
static double measure_item_w...`
  - `measure_item_content_w` (function, line 4652) `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
  - `item_declared_basis` (function, line 4683) `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
  - `nested_cont_basis` (function, line 4697) `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...`
  - `flex_item_basis` (function, line 4739) `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
  - `flex_item_min_main` (function, line 4769) `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...`
  - `item_at_level` (function, line 4802) `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `child_cont_at_level` (function, line 4817) `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `root_cont_of` (function, line 4832) `static int root_cont_of(const rd_doc *doc, int cid)`
  - `block_is_oof` (function, line 4869) `static int block_is_oof(const rd_doc *doc, const rd_block *bk)`
  - `layout_container` (function, line 4886) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `ITEMS` (function, line 4996) `* between ITEMS (not between the lines inside one item). column-reverse
     * reverses the visua...`
  - `slot` (function, line 5088) `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
  - `path` (function, line 5207) `*
         * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when
        ...`
  - `box_line_visible` (function, line 5542) `static int box_line_visible(int style)`
  - `close_top_box` (function, line 5548) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `rc_box_context` (function, line 5685) `static void rc_box_context(const rc_state *s, double content_w,
                           double...`
  - `box_margin_top` (function, line 5712) `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `box_margin_bottom` (function, line 5719) `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `children` (function, line 5729) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
  - `column` (function, line 5937) `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
  - `box_path_has` (function, line 6031) `static int box_path_has(const rd_doc *doc, int block_id, int want)`
  - `box_shrink_width` (function, line 6046) `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...`
  - `reconcile_boxes_below` (function, line 6055) `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
  - `treatment` (function, line 6100) `* block treatment (shrink-wrapped and placed by text-align), which is what a
         * standalon...`
  - `reconcile_boxes` (function, line 6128) `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
  - `box_path_of` (function, line 6142) `static int box_path_of(const rd_doc *doc, int block_id, int *out)`
  - `band_common_box` (function, line 6158) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)`
  - `block_in_table_caption` (function, line 6222) `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)`
  - `defer_key_block` (function, line 6286) `static int defer_key_block(const rd_block *bk)`
  - `defer_append` (function, line 6409) `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...`
  - `defer_flush` (function, line 6443) `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...`
  - `layout_float_band` (function, line 6664) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
  - `thumbnail` (function, line 6747) `* is what made a wikipedia thumbnail (a 250px image and its caption, no
     * declared width) sp...`
  - `layout_doc` (function, line 7023) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
  - `position_doc` (function, line 7394) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
  - `input_box_width` (function, line 7551) `static double input_box_width(double content_w)`
  - `select_box_width` (function, line 7555) `static double select_box_width(double content_w)`
  - `button_box_width` (function, line 7560) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...`
  - `v_read` (function, line 8140) `static int v_read(int fd, void *buf, size_t n)`
  - `dies` (function, line 8168) `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
  - `audio_spawn` (function, line 8177) `static void audio_spawn(browser_window *w, int rate, int channels)`
  - `audio_mark_dead` (function, line 8231) `static void audio_mark_dead(browser_window *w)`
  - `audio_write` (function, line 8248) `static void audio_write(browser_window *w, const uint8_t *data, size_t len)`
  - `audio_stop` (function, line 8263) `static void audio_stop(browser_window *w)`
  - `video_stop` (function, line 8283) `static void video_stop(browser_window *w)`
  - `video_fetch` (function, line 8461) `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...`
  - `video_play` (function, line 8478) `static int video_play(browser_window *w, const char *m3u8_url)`
  - `video_stop` (function, line 8580) `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
  - `paint_video_row` (function, line 8634) `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
  - `row_line_slack` (function, line 8746) `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)`
  - `row_align_offset` (function, line 8758) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)`
  - `upstream` (function, line 8786) `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
  - `box_path` (function, line 8814) `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `text` (function, line 8831) `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
  - `bui_grad_color_at` (function, line 8856) `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...`
  - `spaced` (function, line 8887) `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
  - `paint_bg_layer` (function, line 8919) `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...`
  - `paint_box_decoration` (function, line 8963) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
  - `cairo_set_dash` (function, line 9125) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 9128) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 9167) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 9170) `cairo_set_dash(cr, (double[])`
  - `set_rgb` (function, line 9204) `set_rgb(cr, (ui_rgb)`
  - `cairo_set_dash` (function, line 9227) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 9230) `cairo_set_dash(cr, (double[])`
  - `paint_deco_line` (function, line 9288) `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...`
  - `cairo_set_dash` (function, line 9322) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 9324) `cairo_set_dash(cr, (double[])`
  - `paint_svg_at` (function, line 9344) `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...`
  - `replaced_current_color` (function, line 9364) `static int replaced_current_color(const browser_window *w, const rd_block *blk)`
  - `paint_inline_replaced` (function, line 9373) `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...`
  - `paint_content_row` (function, line 9393) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
  - `ov_box_clips` (function, line 9581) `static int ov_box_clips(const pv_box_def *d)`
  - `ov_collect_chain` (function, line 9588) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)`
  - `ov_box_bounds` (function, line 9609) `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)`
  - `ov_content_rect` (function, line 9633) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...`
  - `fragment` (function, line 9653) `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
  - `box_forms_stacking_context` (function, line 9708) `static int box_forms_stacking_context(const pv_box_def *def)`
  - `bui_skew_tan` (function, line 9751) `static double bui_skew_tan(int deg)`
  - `box_transform_matrix` (function, line 9758) `static void box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
             ...`
  - `bui_blend_operator` (function, line 9876) `static cairo_operator_t bui_blend_operator(int mix_blend)`
  - `bui_paint_backdrop_blur` (function, line 10014) `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...`
  - `bui_pop_group_composite` (function, line 10072) `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms)`
  - `limits` (function, line 10302) `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
  - `paint_box_decoration_grouped` (function, line 10371) `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
  - `paint_box_and_direct_rows` (function, line 10411) `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...`
  - `paint_positioned_one` (function, line 10506) `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...`
  - `paint_nested_children` (function, line 10695) `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...`
  - `paint_structured` (function, line 10728) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
  - `write_doc_pdf` (function, line 10945) `static long write_doc_pdf(browser_window *w, const char *path)`
  - `export_pdf` (function, line 11051) `static void export_pdf(browser_window *w)`
  - `write_doc_png` (function, line 11114) `static long write_doc_png(browser_window *w, const char *path)`
  - `export_png` (function, line 11236) `static void export_png(browser_window *w)`
  - `caller` (function, line 11270) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
  - `ui_render_png` (function, line 11293) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)`
  - `render_doc_images` (function, line 11319) `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...`
  - `ui_render_png_images` (function, line 11350) `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_pdf_images` (function, line 11356) `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_dump_layout` (function, line 11371) `ui_status ui_dump_layout(const rd_doc *doc)`
  - `link_at_point` (function, line 11433) `static const char *link_at_point(browser_window *w, double px, double py)`
  - `resolve_box_cursor` (function, line 11526) `static int resolve_box_cursor(const rd_doc *doc, int block_id)`
  - `box_pointer_events_none` (function, line 11540) `static int box_pointer_events_none(const rd_doc *doc, int block_id)`
  - `cursor_at_point` (function, line 11556) `static int cursor_at_point(browser_window *w, double px, double py)`
  - `node_at_point` (function, line 11619) `static dom_node_id node_at_point(browser_window *w, double px, double py)`
  - `reference` (function, line 11667) `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
  - `apply_click_result` (function, line 11688) `static void apply_click_result(browser_window *w, tab_page *page)`
  - `memory` (function, line 11711) `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
  - `GET` (function, line 11794) `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
  - `ensure_download_dir` (function, line 11828) `static int ensure_download_dir(char *out, size_t outsz)`
  - `write_file_atomic` (function, line 11843) `static int write_file_atomic(const char *path, const void *bytes, size_t len)`
  - `save_download` (function, line 11865) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...`
  - `save_current_page` (function, line 11898) `static void save_current_page(browser_window *w)`
  - `deliver_fetch_result` (function, line 11908) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
  - `drain_fetch_results` (function, line 11962) `static void drain_fetch_results(browser_window *w)`
  - `toggle_reader` (function, line 12038) `static void toggle_reader(browser_window *w)`
  - `menu_item_checked` (function, line 12049) `static int menu_item_checked(const browser_window *w, size_t i)`
  - `menu_item_toggle` (function, line 12071) `static void menu_item_toggle(browser_window *w, size_t i)`
  - `draw_clock` (function, line 12181) `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...`
  - `draw_hamburger` (function, line 12193) `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_reload` (function, line 12209) `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_menu` (function, line 12231) `static void draw_menu(cairo_t *cr, browser_window *w)`
  - `draw_hover_url` (function, line 12342) `static double draw_hover_url(cairo_t *cr, browser_window *w)`
  - `draw_toast` (function, line 12374) `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)`
  - `draw_tabstrip` (function, line 12404) `static void draw_tabstrip(cairo_t *cr, browser_window *w)`
  - `draw_omnibox` (function, line 12459) `static void draw_omnibox(cairo_t *cr, browser_window *w)`
  - `paint` (function, line 12493) `static void paint(browser_window *w)`
  - `redraw` (function, line 12737) `static void redraw(browser_window *w)`
  - `wm_base_ping` (function, line 12749) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 12755) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 12763) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `wl_array_for_each` (function, line 12779) `wl_array_for_each(st, states)`
  - `toplevel_close` (function, line 12785) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 12794) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `set_cursor` (function, line 12806) `static void set_cursor(browser_window *w, int cur_kind)`
  - `element` (function, line 12836) `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...`
  - `fbw_split_y` (function, line 12906) `static double fbw_split_y(const freebug_window *fb)`
  - `freebug_ensure_buffer` (function, line 12915) `static int freebug_ensure_buffer(freebug_window *fb)`
  - `fbw_level_rgb` (function, line 12942) `static void fbw_level_rgb(int level, double *r, double *g, double *b)`
  - `fbw_console_lines` (function, line 12953) `static size_t fbw_console_lines(const fb_buffer *log)`
  - `freebug_paint` (function, line 12966) `static void freebug_paint(freebug_window *fb)`
  - `freebug_redraw_fb` (function, line 13165) `static void freebug_redraw_fb(freebug_window *fb)`
  - `freebug_redraw` (function, line 13174) `static void freebug_redraw(browser_window *w)`
  - `freebug_hide` (function, line 13178) `static void freebug_hide(browser_window *w)`
  - `fbw_xdg_surface_configure` (function, line 13194) `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `fbw_toplevel_configure` (function, line 13202) `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...`
  - `fbw_toplevel_close` (function, line 13211) `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)`
  - `freebug_show` (function, line 13221) `static void freebug_show(browser_window *w)`
  - `freebug_toggle` (function, line 13251) `static void freebug_toggle(browser_window *w)`
  - `freebug_destroy` (function, line 13256) `static void freebug_destroy(browser_window *w)`
  - `freebug_owns_surface` (function, line 13263) `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)`
  - `freebug_is_open` (function, line 13267) `static int freebug_is_open(const browser_window *w)`
  - `freebug_repl_worker` (function, line 13274) `static tab *freebug_repl_worker(browser_window *w)`
  - `freebug_eval` (function, line 13311) `static void freebug_eval(browser_window *w)`
  - `freebug_handle_key` (function, line 13351) `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...`
  - `freebug_pointer_button` (function, line 13386) `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...`
  - `freebug_pointer_motion` (function, line 13405) `static void freebug_pointer_motion(browser_window *w)`
  - `freebug_pointer_axis` (function, line 13427) `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)`
  - `ptr_enter` (function, line 13445) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
  - `ptr_leave` (function, line 13463) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
  - `ptr_motion` (function, line 13480) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
  - `load_current` (function, line 13505) `static void load_current(browser_window *w)`
  - `go_omnibox` (function, line 13518) `static void go_omnibox(browser_window *w)`
  - `ptr_button` (function, line 13563) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
  - `scroll_line_px` (function, line 13792) `static double scroll_line_px(const browser_window *w)`
  - `ptr_axis` (function, line 13796) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
  - `ptr_frame` (function, line 13820) `static void ptr_frame(void *d, struct wl_pointer *p)`
  - `mime_is_text` (function, line 13836) `static int mime_is_text(const char *mime)`
  - `data_offer_source_actions` (function, line 13854) `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_offer_action` (function, line 13857) `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_device_data_offer` (function, line 13867) `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...`
  - `data_device_selection` (function, line 13879) `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...`
  - `data_device_enter` (function, line 13898) `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...`
  - `data_device_leave` (function, line 13903) `static void data_device_leave(void *d, struct wl_data_device *dev)`
  - `data_device_motion` (function, line 13904) `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...`
  - `data_device_drop` (function, line 13908) `static void data_device_drop(void *d, struct wl_data_device *dev)`
  - `data_source_cancelled` (function, line 13919) `static void data_source_cancelled(void *data, struct wl_data_source *src)`
  - `data_source_send` (function, line 13925) `static void data_source_send(void *data, struct wl_data_source *src,
                            ...`
  - `data_source_target` (function, line 13938) `static void data_source_target(void *d, struct wl_data_source *s, const char *m)`
  - `freebug_copy_console` (function, line 13950) `static void freebug_copy_console(browser_window *w)`
  - `insert_pasted_text` (function, line 14008) `static void insert_pasted_text(browser_window *w, const char *text, size_t len)`
  - `clipboard_copy` (function, line 14072) `static void clipboard_copy(browser_window *w)`
  - `keyboard_keymap` (function, line 14120) `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...`
  - `keyboard_enter` (function, line 14141) `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...`
  - `keyboard_leave` (function, line 14148) `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)`
  - `key_sym_to_js_key` (function, line 14156) `static const char *key_sym_to_js_key(xkb_keysym_t sym)`
  - `key_sym_to_keycode` (function, line 14182) `static int key_sym_to_keycode(xkb_keysym_t sym)`
  - `dispatch_js_event` (function, line 14207) `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...`
  - `handle_key_press` (function, line 14264) `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...`
  - `key_is_repeatable` (function, line 14594) `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)`
  - `key_repeat_arm` (function, line 14610) `static void key_repeat_arm(browser_window *w, uint32_t key)`
  - `key_repeat_stop` (function, line 14623) `static void key_repeat_stop(browser_window *w)`
  - `key_repeat_fire` (function, line 14634) `static void key_repeat_fire(browser_window *w)`
  - `keyboard_key` (function, line 14648) `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...`
  - `keyboard_modifiers` (function, line 14688) `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...`
  - `keyboard_repeat_info` (function, line 14697) `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)`
  - `seat_caps` (function, line 14716) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
  - `seat_name` (function, line 14727) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
  - `registry_global` (function, line 14734) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
  - `registry_remove` (function, line 14754) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
  - `ui_run_browser` (function, line 14764) `ui_status ui_run_browser(const char *start_url)`
  - `cost` (function, line 15140) `* measured cost (floor 33 ms = the existing ~30 fps ceiling):
             * cheap pages paint at...`
  - `offset` (function, line 155) `* offset (labels and the flag live in one place, no magic indices);`
  - `fields` (function, line 262) `* fields (so the 200+ render/event call sites stay unchanged);`
  - `delay` (function, line 356) `* timer delay (tab_page.next_timer_ms);`
  - `main` (function, line 488) `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never blocks on HTTP. The thread is spawned by * video_play() and joined by video_stop();`
  - `proxy` (function, line 976) `* and enable each proxy ("1" => the default port);`
  - `video_feeder_thread` (function, line 1029) `static void *video_feeder_thread(void *arg);`
  - `hb_is_allowlisted` (function, line 1449) `&& hb_is_allowlisted(w->hosts, ihost);`
  - `proceed` (function, line 1492) `* may proceed (cfg and pr->allowlisted are then set);`
  - `secure_fetch` (function, line 1740) `* through secure_fetch (Zero Trust);`
  - `string` (function, line 1888) `* or an empty string (unset, blocked, or off by caps.images), so there is no * decision to re-check, unlike load_images which still reads b->img_decision (a * box def carries no decision field, only t`
  - `do_load` (function, line 1930) `static void do_load(browser_window *w, const char *url);`
  - `toggle` (function, line 1937) `* No network: a capability toggle (images/CSS) re-renders from cache. Does nothing * when there is no cached source (start/error pages stay in plain-text mode). * * allow_js_nav: on a FRESH load (not `
  - `stylesheets` (function, line 2044) `* External stylesheets (Hito 27) follow the author-styles opt-in -- or the * trusted-host doctrine (Hito 28) -- (GET-only at the parent gate);`
  - `ALIVE` (function, line 2179) `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or a tab switch) closes it. */ fb_buffer_free(&w->console);`
  - `resolve` (function, line 2365) `* origin so its relative references and local images resolve (confined to the * document's directory) -- a local page "acts like https" for resolution. */ clear_doc(w);`
  - `smaller` (function, line 2921) `* size when the content is smaller (height) or wider (min-width);`
  - `HarfBuzz` (function, line 3289) `* descriptor via HarfBuzz (text_shape);`
  - `produced` (function, line 3697) `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target without re-walking the document. node_id tags the * originating element for JS click dis`
  - `line` (function, line 3781) `* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the same buffer the loop scans, so a tab-expanded * <pre> agrees with itself. */ int star`
  - `box` (function, line 4118) `* declared intrinsic size reserves that box (broken-image parity);`
  - `close_all_boxes` (function, line 4791) `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);`
  - `TABLE` (function, line 4857) `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all containers has no run of its own to read them from -- that * is the whole reason the table ex`
  - `struct` (function, line 5193) `* struct (0 = auto);`
  - `own` (function, line 5437) `* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and its ancestors) * INSIDE the item -- which is what painted a nested nav's own backdro`
  - `multicol_fragment` (function, line 5539) `static double multicol_fragment(rc_layout *L, const rc_open_box *ob, double content_bottom);`
  - `behind` (function, line 5738) `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old code used th->paragraph_gap as a floor here, * which gave a <div> the vertical rhythm`
  - `context` (function, line 6211) `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document order);`
  - `x` (function, line 6496) `* reported x is already the BORDER x (the §7c.2 rule);`
  - `chain` (function, line 7072) `* chain (the box that left the normal flow at this pen position);`
  - `first` (function, line 7134) `* flush first (no-op when nothing is deferred). */ defer_flush(cr, w, L, &s, th, content_w, doc, &df);`
  - `anchor` (function, line 7156) `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is a no-op * for it. Without this a flex header never anchored and pulled * columns te`
  - `key` (function, line 7215) `* founders splits by key (stories, rail, footer nav each take * their column);`
  - `have` (function, line 7229) `* as they always have (spec/float.md §6b.3). */ rc_float_clear(&s);`
  - `standalone` (function, line 7248) `* must not be treated as standalone (which would flush that line and give * the element a row of its own -- R7). */ int inline_replaced = replaced_is_inline_level(&s, b);`
  - `it` (function, line 7296) `* column: flush first so the column lands above it (source order), * then move the anchor — the image bottom is the container top * for whatever follows. */ defer_flush(cr, w, L, &s, th, content_w, do`
  - `rd_build` (function, line 7955) `* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr, rgb_from_packed(b->caret_color));`
  - `descriptors` (function, line 8191) `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection — the most common * cause of the "page flashes white and render loops" bug. */ close(p[`
  - `again` (function, line 8272) `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one fail with "Device * or resource busy"). Death is immediate, so the wait is too. */ kill`
  - `blocking` (function, line 8559) `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);`
  - `rect` (function, line 8827) `* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops land on the corners. Stops at explicit * 0-1000 positions (pos1000, -1 or NULL = evenly`
  - `layer` (function, line 9079) `* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the border. Same sizing/repeat/position * as the first layer, using the SAME rc_box fields`
  - `convention` (function, line 9190) `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE || style == CSS_BST_RIDGE || style == CSS_BST_INSET || style == CSS_BST_OUTSET);`
  - `row_owner_block_id` (function, line 9339) `static int row_owner_block_id(const rc_layout *L, const rc_row *r);`
  - `bg` (function, line 9446) `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);`
  - `rows` (function, line 9652) `* RC_IMAGE rows (see its declaration);`
  - `the` (function, line 10224) `* the (already filtered) group with the shadow color, blur it, and * paint it under the group at the declared offset -- the shadow * follows the real content shape (PNG transparency, glyphs), not * th`
  - `fill` (function, line 10400) `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in the caller's separate row pass -- * left ungrouped, it shows as a solid, un-faded re`
  - `compositing` (function, line 10493) `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context: opacity<1, mix-blend != normal, isolation:isolate, * transform != none, or the posit`
  - `origin` (function, line 11315) `* top_url is the page origin (https or file://);`
  - `in` (function, line 11393) `* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);`
  - `presentation` (function, line 12069) `* affect presentation (a repaint, which re-runs layout, suffices);`
  - `resizes` (function, line 12771) `* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);`
  - `down` (function, line 13439) `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void dispatch_mouse_event(browser_window *w, dom_node_id node_id, const char *event_type, int `
  - `loop` (function, line 13999) `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately might miss it). */ wl_display_roundtrip(w->display);`
  - `saving` (function, line 14779) `* disables saving (never clobber);`
  - `redraws` (function, line 14858) `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A 4 KiB buffer overflows when * accumulated messages exceed that, since manual flushes`
  - `applies` (function, line 14928) `* persisted choice applies (prefs_parse already clamped it to a valid mode). */ const char *js_env = getenv("FREEDOM_JS");`
  - `flow` (function, line 15118) `* flow (counting them starved aplay). A video frame read while * overdue overwrites the held slot (standard player frame drop);`
  - `_GNU_SOURCE` (macro, line 12) `#define _GNU_SOURCE`
  - `UI_TOOLBAR_H` (macro, line 81) `#define UI_TOOLBAR_H`
  - `UI_TITLEBAR_H` (macro, line 82) `#define UI_TITLEBAR_H`
  - `UI_TABBAR_H` (macro, line 83) `#define UI_TABBAR_H`
  - `UI_TAB_MIN_W` (macro, line 84) `#define UI_TAB_MIN_W`
  - `UI_TAB_MAX_W` (macro, line 85) `#define UI_TAB_MAX_W`
  - `UI_TAB_NEW_W` (macro, line 86) `#define UI_TAB_NEW_W`
  - `UI_TAB_CLOSE_W` (macro, line 87) `#define UI_TAB_CLOSE_W`
  - `UI_BTN_W` (macro, line 88) `#define UI_BTN_W`
  - `UI_WIN_BTN_W` (macro, line 89) `#define UI_WIN_BTN_W`
  - `UI_MARGIN` (macro, line 90) `#define UI_MARGIN`
  - `UI_BTN_LEFT` (macro, line 91) `#define UI_BTN_LEFT`
  - `UI_LIST_INDENT` (macro, line 92) `#define UI_LIST_INDENT`
  - `UI_SCROLLBAR_W` (macro, line 97) `#define UI_SCROLLBAR_W`
  - `UI_SCROLLBAR_MIN` (macro, line 98) `#define UI_SCROLLBAR_MIN`
  - `UI_SCROLLBAR_PAD` (macro, line 99) `#define UI_SCROLLBAR_PAD`
  - `UI_RESIZE_MARGIN` (macro, line 103) `#define UI_RESIZE_MARGIN`
  - `UI_MENU_W` (macro, line 108) `#define UI_MENU_W`
  - `UI_MENU_ITEM_H` (macro, line 109) `#define UI_MENU_ITEM_H`
  - `UI_MENU_PAD` (macro, line 110) `#define UI_MENU_PAD`
  - `UI_CHECK_SZ` (macro, line 111) `#define UI_CHECK_SZ`
  - `UI_MENU_LABEL_H` (macro, line 112) `#define UI_MENU_LABEL_H`
  - `UI_MENU_INPUT_H` (macro, line 113) `#define UI_MENU_INPUT_H`
  - `UI_HAMBURGER_W` (macro, line 114) `#define UI_HAMBURGER_W`
  - `UI_HAMBURGER_GAP` (macro, line 115) `#define UI_HAMBURGER_GAP`
  - `UI_CURSOR_SIZE` (macro, line 116) `#define UI_CURSOR_SIZE`
  - `UI_TOAST_PAD` (macro, line 117) `#define UI_TOAST_PAD`
  - `OMNI_MAX_SUGG` (macro, line 118) `#define OMNI_MAX_SUGG`
  - `UI_OMNI_ROW_H` (macro, line 119) `#define UI_OMNI_ROW_H`
  - `UI_TWO_PI` (macro, line 120) `#define UI_TWO_PI`
  - `UI_INPUT_PAD` (macro, line 124) `#define UI_INPUT_PAD`
  - `UI_INPUT_MEASURE_W` (macro, line 127) `#define UI_INPUT_MEASURE_W`
  - `UI_INPUT_WIDTH` (macro, line 128) `#define UI_INPUT_WIDTH`
  - `UI_BUTTON_HPAD` (macro, line 129) `#define UI_BUTTON_HPAD`
  - `UI_FORM_FIELDS_MAX` (macro, line 130) `#define UI_FORM_FIELDS_MAX`
  - `UI_UNDERLINE_OFFSET` (macro, line 135) `#define UI_UNDERLINE_OFFSET`
  - `UI_UNDERLINE_THICK` (macro, line 136) `#define UI_UNDERLINE_THICK`
  - `UI_STRIKE_OFFSET` (macro, line 137) `#define UI_STRIKE_OFFSET`
  - `UI_OVERLINE_OFFSET` (macro, line 138) `#define UI_OVERLINE_OFFSET`
  - `UI_SLICE_MAX` (macro, line 142) `#define UI_SLICE_MAX`
  - `UI_MENU_COUNT` (macro, line 201) `#define UI_MENU_COUNT`
  - `UI_IMAGE_MAX_BODY` (macro, line 219) `#define UI_IMAGE_MAX_BODY`
  - `UI_MAX_TABS` (macro, line 258) `#define UI_MAX_TABS`
  - `UI_READER_COLUMN_W` (macro, line 555) `#define UI_READER_COLUMN_W`
  - `JS_NAV_MAX` (macro, line 1934) `#define JS_NAV_MAX`
  - `JS_TICKS_PER_LOAD` (macro, line 2009) `#define JS_TICKS_PER_LOAD`
  - `UI_RELOAD_X` (macro, line 2730) `#define UI_RELOAD_X`
  - `RC_BOX_STACK_MAX` (macro, line 3031) `#define RC_BOX_STACK_MAX`
  - `RC_FLOAT_MAX` (macro, line 3035) `#define RC_FLOAT_MAX`
  - `RC_FLOAT_FIT_MIN` (macro, line 3042) `#define RC_FLOAT_FIT_MIN`
  - `FLEX_MEASURE_W` (macro, line 4562) `#define FLEX_MEASURE_W`
  - `FLEX_MIN_MEASURE_W` (macro, line 4567) `#define FLEX_MIN_MEASURE_W`
  - `RC_MAX_OUT_OF_FLOW` (macro, line 6138) `#define RC_MAX_OUT_OF_FLOW`
  - `RC_DEFER_COLS` (macro, line 6246) `#define RC_DEFER_COLS`
  - `RC_DEFER_RANGES` (macro, line 6247) `#define RC_DEFER_RANGES`
  - `RC_DEFER_BAND_RUNS` (macro, line 6329) `#define RC_DEFER_BAND_RUNS`
  - `BUI_CONIC_SLICES` (macro, line 8881) `#define BUI_CONIC_SLICES`
  - `OV_MAX_DEPTH` (macro, line 9577) `#define OV_MAX_DEPTH`
  - `H2R` (macro, line 10180) `#define H2R(p,q,t)`
  - `PDF_PAGE_W` (macro, line 10929) `#define PDF_PAGE_W`
  - `PDF_PAGE_H` (macro, line 10930) `#define PDF_PAGE_H`
  - `PDF_MARGIN` (macro, line 10931) `#define PDF_MARGIN`
  - `PNG_PAGE_W` (macro, line 11093) `#define PNG_PAGE_W`
  - `PNG_MARGIN` (macro, line 11106) `#define PNG_MARGIN`
  - `PNG_MAX_H` (macro, line 11107) `#define PNG_MAX_H`
  - `FBW_W` (macro, line 12872) `#define FBW_W`
  - `FBW_H` (macro, line 12873) `#define FBW_H`
  - `FBW_HEADER` (macro, line 12874) `#define FBW_HEADER`
  - `FBW_PAD` (macro, line 12875) `#define FBW_PAD`
  - `FBW_LINE` (macro, line 12876) `#define FBW_LINE`
  - `FBW_GUTTER` (macro, line 12877) `#define FBW_GUTTER`
  - `FBW_MIN_SPLIT` (macro, line 12878) `#define FBW_MIN_SPLIT`
  - `FBW_MAX_SPLIT` (macro, line 12879) `#define FBW_MAX_SPLIT`
  - `FBW_COPY_BTN_W` (macro, line 12880) `#define FBW_COPY_BTN_W`
  - `FBW_COPY_BTN_H` (macro, line 12881) `#define FBW_COPY_BTN_H`
- Depends on: `gui/browser_ui_internal.h`, `include/block_flow.h`, `include/box_style.h`, `include/box_tree.h`, `include/browser.h`, `include/compositor.h`, `include/css.h`, `include/css_color.h`, `include/data_url.h`, `include/download.h`, `include/form.h`, `include/frame_clock.h`, `include/freebug.h`, `include/hls.h`, `include/hostblock.h`, `include/hostedit.h`, `include/image_decode.h`, `include/interp.h`, `include/js_policy.h`, `include/link_nav.h`, `include/media_decoder.h`, `include/net_realm.h`, `include/pdf_export.h`, `include/prefetch.h`, `include/prefs.h`, `include/profile.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/svg_paint.h`, `include/svg_render.h`, `include/tab.h`, `include/text_shape.h`, `include/textfield.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/webcaps.h`, `include/zoom.h`

## gui/browser_ui_internal.h
- Layer: presentation
- Language: h
- Symbols:
  - `ui_rgb` (struct, line 41)
  - `ui_theme` (struct, line 43)
  - `ui_theme_mode` (enum, line 93)
  - `b` (type_alias, line 40) `typedef struct ui_rgb { double r, g, b;`
  - `body_font` (type_alias, line 42) `typedef struct ui_theme { double body_font;`
  - `set_rgb` (function, line 106) `void set_rgb(cairo_t *cr, ui_rgb c);`
  - `FREEDOM_BROWSER_UI_INTERNAL_H` (macro, line 2) `#define FREEDOM_BROWSER_UI_INTERNAL_H`
  - `UI_FONT_SIZE` (macro, line 30) `#define UI_FONT_SIZE`
  - `UI_TEXT_MARGIN` (macro, line 31) `#define UI_TEXT_MARGIN`
  - `UI_HEADING_LEVELS` (macro, line 32) `#define UI_HEADING_LEVELS`
- Depends on: `include/freedom_config.h`
- Imported by: `gui/browser_ui.c`, `gui/bui_theme.c`

## gui/bui_theme.c
- Layer: presentation
- Language: c
- Symbols:
  - `ui_theme_default` (function, line 14) `ui_theme ui_theme_default(void)`
  - `ui_theme_dark` (function, line 84) `ui_theme ui_theme_dark(void)`
  - `ui_theme_sepia` (function, line 129) `ui_theme ui_theme_sepia(void)`
  - `ui_theme_for` (function, line 171) `ui_theme ui_theme_for(int mode)`
  - `rgb_from_packed` (function, line 180) `ui_rgb rgb_from_packed(int packed)`
  - `set_rgb` (function, line 185) `void set_rgb(cairo_t *cr, ui_rgb c)`
- Depends on: `gui/browser_ui_internal.h`, `include/css_color.h`

## gui/freedom_view.c
- Layer: presentation
- Language: c
- Symbols:
  - `main` (function, line 37) `int main(int argc, char **argv)`
  - `_POSIX_C_SOURCE` (macro, line 10) `#define _POSIX_C_SOURCE`
- Depends on: `include/html_parse.h`, `include/ui.h`

## gui/svg_paint.c
- Layer: presentation
- Doc: svg_paint — Cairo back end for the shapes svg_render extracted.
- Language: c
- Symbols:
  - `svp_alpha` (function, line 31) `static double svp_alpha(int opacity, int paint_opacity)`
  - `svp_rect_path` (function, line 38) `static void svp_rect_path(cairo_t *cr, const sv_shape *sh)`
  - `svp_shape_path` (function, line 73) `static void svp_shape_path(cairo_t *cr, const sv_image *img, const sv_shape *sh)`
  - `svp_draw_text` (function, line 126) `static void svp_draw_text(cairo_t *cr, const sv_shape *sh, int current_rgb)`
  - `svp_draw` (function, line 139) `void svp_draw(cairo_t *cr, const sv_image *img,
              double x, double y, double w, doubl...`
- Depends on: `include/css_color.h`, `include/freedom_config.h`, `include/svg_paint.h`

## gui/ui_render.c
- Layer: presentation
- Language: c
- Symbols:
  - `ui_window` (struct, line 67)
  - `sanitize_utf8_inplace` (function, line 39) `static void sanitize_utf8_inplace(char *s)`
  - `button_rects` (function, line 107) `static void button_rects(const ui_window *w, double *min_x, double *max_x, double *close_x)`
  - `buffer_release` (function, line 115) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 122) `static void destroy_buffer(ui_window *w)`
  - `ensure_buffer` (function, line 128) `static int ensure_buffer(ui_window *w)`
  - `paint` (function, line 159) `static void paint(ui_window *w)`
  - `redraw` (function, line 245) `static void redraw(ui_window *w)`
  - `wm_base_ping` (function, line 260) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 266) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 274) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `toplevel_close` (function, line 283) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 294) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `ptr_enter` (function, line 305) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
  - `ptr_leave` (function, line 312) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
  - `ptr_motion` (function, line 315) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
  - `ptr_button` (function, line 322) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
  - `ptr_axis` (function, line 344) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
  - `seat_caps` (function, line 367) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
  - `seat_name` (function, line 376) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
  - `registry_global` (function, line 383) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
  - `registry_remove` (function, line 401) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
  - `ui_run_text_view` (function, line 410) `ui_status ui_run_text_view(const char *title, const char *text, size_t text_len)`
  - `_GNU_SOURCE` (macro, line 10) `#define _GNU_SOURCE`
  - `UI_FONT_SIZE` (macro, line 28) `#define UI_FONT_SIZE`
  - `UI_MARGIN` (macro, line 29) `#define UI_MARGIN`
  - `UI_TITLEBAR_H` (macro, line 30) `#define UI_TITLEBAR_H`
  - `UI_BTN_W` (macro, line 31) `#define UI_BTN_W`
  - `UI_BTN_LEFT` (macro, line 32) `#define UI_BTN_LEFT`
- Depends on: `include/freedom_config.h`, `include/ui.h`
