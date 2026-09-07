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
  - `rc_ext` (struct, line 3600)
  - `item_sides` (struct, line 4395)
  - `freebug_window` (struct, line 12265)
  - `now_ms` (function, line 145) `static uint64_t now_ms(void)`
  - `gutter` (function, line 551) `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
  - `apply_zoom` (function, line 572) `static void apply_zoom(browser_window *w)`
  - `buffer_release` (function, line 582) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 588) `static void destroy_buffer(browser_window *w)`
  - `ensure_buffer` (function, line 594) `static int ensure_buffer(browser_window *w)`
  - `read_file` (function, line 624) `static char *read_file(const char *path, size_t *out_len)`
  - `build_file_origin` (function, line 664) `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)`
  - `load_host_file` (function, line 674) `static void load_host_file(hb_set *s, const char *dir, const char *name, hb_list list)`
  - `build_host_filter` (function, line 691) `static hb_set *build_host_filter(void)`
  - `build_js_filter` (function, line 737) `static hb_set *build_js_filter(void)`
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
  - `is_https_url` (function, line 988) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 992) `static int is_http_url(const char *s)`
  - `host_from_url` (function, line 1004) `static int host_from_url(const char *url, char *out, size_t outsz)`
  - `toggle_fullscreen` (function, line 1034) `static void toggle_fullscreen(browser_window *w)`
  - `input_is_interactive` (function, line 1049) `static int input_is_interactive(int input_type)`
  - `input_is_editable` (function, line 1054) `static int input_is_editable(int input_type)`
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
  - `fetch_job_free` (function, line 1595) `static void fetch_job_free(fetch_job *j)`
  - `stream_progress_cb` (function, line 1616) `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)`
  - `fetch_thread` (function, line 1640) `static void *fetch_thread(void *arg)`
  - `fetch_launch` (function, line 1688) `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...`
  - `load_images` (function, line 1808) `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
  - `load_bg_images` (function, line 1893) `static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
  - `page_js_host_allowlisted` (function, line 1948) `static int page_js_host_allowlisted(const browser_window *w)`
  - `compute_page_js` (function, line 1954) `static int compute_page_js(const browser_window *w)`
  - `seed_session_cookies` (function, line 1968) `static void seed_session_cookies(tab *t, int trusted, const char *url)`
  - `foldback_session_cookies` (function, line 1981) `static void foldback_session_cookies(const char *url, const char *jar)`
  - `drop_repl_worker` (function, line 2000) `static void drop_repl_worker(browser_window *w)`
  - `schedule_js_tick` (function, line 2014) `static void schedule_js_tick(browser_window *w, int next_ms)`
  - `render_current_ex` (function, line 2023) `static void render_current_ex(browser_window *w, int allow_js_nav)`
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
  - `content_width` (function, line 2615) `static double content_width(const browser_window *w)`
  - `html_center_offset` (function, line 2625) `static double html_center_offset(const browser_window *w)`
  - `scrollbar_metrics` (function, line 2640) `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...`
  - `scrollbar_drag_to` (function, line 2668) `static void scrollbar_drag_to(browser_window *w)`
  - `draw_scrollbar` (function, line 2685) `static void draw_scrollbar(cairo_t *cr, const browser_window *w)`
  - `window_button_rects` (function, line 2721) `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...`
  - `toolbar_rects` (function, line 2731) `static void toolbar_rects(const browser_window *w,
                          double *back_x, doub...`
  - `toolbar_button_at` (function, line 2747) `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)`
  - `hot_actionable` (function, line 2763) `static int hot_actionable(const browser_window *w, ui_hot hot)`
  - `menu_panel_rect` (function, line 2774) `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...`
  - `ua_box_rect` (function, line 2790) `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...`
  - `draw_text` (function, line 2799) `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)`
  - `rc_float_bottom` (function, line 3138) `static double rc_float_bottom(const rc_state *s)`
  - `rc_float_clear` (function, line 3147) `static void rc_float_clear(rc_state *s)`
  - `rc_float_refresh` (function, line 3160) `static void rc_float_refresh(rc_state *s, double line_h)`
  - `rc_float_fit_line` (function, line 3206) `static void rc_float_fit_line(rc_state *s, double line_h)`
  - `line_limit` (function, line 3225) `static double line_limit(const rc_state *s, double content_w)`
  - `rc_free` (function, line 3229) `static void rc_free(rc_layout *L)`
  - `rc_add_box` (function, line 3238) `static rc_box *rc_add_box(rc_layout *L)`
  - `rc_add_frag` (function, line 3250) `static rc_frag *rc_add_frag(rc_layout *L)`
  - `rc_add_row` (function, line 3265) `static rc_row *rc_add_row(rc_layout *L)`
  - `family_face` (function, line 3278) `static const char *family_face(int family)`
  - `content_font` (function, line 3295) `static void content_font(cairo_t *cr, double size, int bold, int italic, int family)`
  - `set_rgb_alpha` (function, line 3309) `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)`
  - `utf8_clen` (function, line 3318) `static size_t utf8_clen(const char *s, size_t n)`
  - `draw_slice` (function, line 3358) `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)`
  - `frag_styled` (function, line 3371) `static int frag_styled(const rc_frag *f)`
  - `styled_advance` (function, line 3378) `static double styled_advance(cairo_t *cr, const rc_frag *f)`
  - `styled_draw` (function, line 3394) `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)`
  - `block_style` (function, line 3410) `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
  - `block_margins` (function, line 3438) `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...`
  - `add` (function, line 3468) `* about to add (top/h passed in). A box that survived a line wrap simply ends at the
 * wrap -- m...`
  - `run` (function, line 3503) `* continuation run (block_id < 0 with no block break) deliberately skips reconcile
 * to stay on ...`
  - `flush_line` (function, line 3527) `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `open_line` (function, line 3580) `static void open_line(rc_layout *L, rc_state *s)`
  - `flow_emit_frag` (function, line 3629) `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...`
  - `flow_text` (function, line 3696) `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...`
  - `replaced_inline_size` (function, line 3948) `static int replaced_inline_size(const browser_window *w, const rd_block *b,
                     ...`
  - `replaced_is_inline_level` (function, line 3978) `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)`
  - `place_inline_replaced` (function, line 3991) `static int place_inline_replaced(rc_layout *L, rc_state *s, const ui_theme *th,
                 ...`
  - `css_replaced_box` (function, line 4046) `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...`
  - `emit_replaced_row` (function, line 4054) `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `flow_text_block` (function, line 4157) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
  - `item_root_box_in` (function, line 4269) `static int item_root_box_in(const rd_doc *doc, size_t b0, size_t b1, int cbox)`
  - `item_root_box` (function, line 4306) `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)`
  - `css_align_to_bt` (function, line 4315) `static int css_align_to_bt(int align_kw)`
  - `box_edge_px` (function, line 4325) `static double box_edge_px(int wpx)`
  - `rc_box_copy_decoration` (function, line 4345) `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)`
  - `box_is_strict_descendant` (function, line 4424) `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)`
  - `item_sides_at_level` (function, line 4446) `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,
                  ...`
  - `container_box_of` (function, line 4475) `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)`
  - `table` (function, line 4497) `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...`
  - `row` (function, line 4557) `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...`
  - `way` (function, line 4598) `* intrinsic box either way (it does not wrap below its own size). */
static double measure_item_w...`
  - `measure_item_content_w` (function, line 4633) `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
  - `item_declared_basis` (function, line 4665) `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
  - `nested_cont_basis` (function, line 4679) `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...`
  - `flex_item_basis` (function, line 4711) `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
  - `flex_item_min_main` (function, line 4742) `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...`
  - `item_at_level` (function, line 4775) `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `child_cont_at_level` (function, line 4790) `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `root_cont_of` (function, line 4805) `static int root_cont_of(const rd_doc *doc, int cid)`
  - `block_is_oof` (function, line 4842) `static int block_is_oof(const rd_doc *doc, const rd_block *bk)`
  - `layout_container` (function, line 4858) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `ITEMS` (function, line 4968) `* between ITEMS (not between the lines inside one item). column-reverse
     * reverses the visua...`
  - `slot` (function, line 5060) `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
  - `path` (function, line 5178) `*
         * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when
        ...`
  - `box_line_visible` (function, line 5510) `static int box_line_visible(int style)`
  - `close_top_box` (function, line 5517) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `rc_box_context` (function, line 5654) `static void rc_box_context(const rc_state *s, double content_w,
                           double...`
  - `box_margin_top` (function, line 5680) `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `box_margin_bottom` (function, line 5687) `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `children` (function, line 5698) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
  - `column` (function, line 5905) `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
  - `box_path_has` (function, line 6000) `static int box_path_has(const rd_doc *doc, int block_id, int want)`
  - `box_shrink_width` (function, line 6015) `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...`
  - `reconcile_boxes_below` (function, line 6023) `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
  - `treatment` (function, line 6069) `* block treatment (shrink-wrapped and placed by text-align), which is what a
         * standalon...`
  - `reconcile_boxes` (function, line 6096) `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
  - `box_path_of` (function, line 6111) `static int box_path_of(const rd_doc *doc, int block_id, int *out)`
  - `band_common_box` (function, line 6127) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)`
  - `block_in_table_caption` (function, line 6191) `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)`
  - `layout_float_band` (function, line 6202) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
  - `thumbnail` (function, line 6285) `* is what made a wikipedia thumbnail (a 250px image and its caption, no
     * declared width) sp...`
  - `layout_doc` (function, line 6501) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
  - `position_doc` (function, line 6786) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
  - `input_box_width` (function, line 6944) `static double input_box_width(double content_w)`
  - `select_box_width` (function, line 6947) `static double select_box_width(double content_w)`
  - `button_box_width` (function, line 6953) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...`
  - `v_read` (function, line 7533) `static int v_read(int fd, void *buf, size_t n)`
  - `dies` (function, line 7561) `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
  - `audio_spawn` (function, line 7569) `static void audio_spawn(browser_window *w, int rate, int channels)`
  - `audio_mark_dead` (function, line 7624) `static void audio_mark_dead(browser_window *w)`
  - `audio_write` (function, line 7641) `static void audio_write(browser_window *w, const uint8_t *data, size_t len)`
  - `audio_stop` (function, line 7655) `static void audio_stop(browser_window *w)`
  - `video_stop` (function, line 7675) `static void video_stop(browser_window *w)`
  - `video_fetch` (function, line 7854) `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...`
  - `video_play` (function, line 7871) `static int video_play(browser_window *w, const char *m3u8_url)`
  - `video_stop` (function, line 7973) `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
  - `paint_video_row` (function, line 8026) `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
  - `row_line_slack` (function, line 8139) `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)`
  - `row_align_offset` (function, line 8151) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)`
  - `upstream` (function, line 8179) `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
  - `box_path` (function, line 8207) `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `text` (function, line 8224) `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
  - `bui_grad_color_at` (function, line 8249) `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...`
  - `spaced` (function, line 8280) `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
  - `paint_bg_layer` (function, line 8312) `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...`
  - `paint_box_decoration` (function, line 8355) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
  - `cairo_set_dash` (function, line 8518) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 8521) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 8560) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 8563) `cairo_set_dash(cr, (double[])`
  - `set_rgb` (function, line 8597) `set_rgb(cr, (ui_rgb)`
  - `cairo_set_dash` (function, line 8620) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 8623) `cairo_set_dash(cr, (double[])`
  - `paint_deco_line` (function, line 8681) `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...`
  - `cairo_set_dash` (function, line 8715) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 8717) `cairo_set_dash(cr, (double[])`
  - `paint_svg_at` (function, line 8737) `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...`
  - `replaced_current_color` (function, line 8757) `static int replaced_current_color(const browser_window *w, const rd_block *blk)`
  - `paint_inline_replaced` (function, line 8766) `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...`
  - `paint_content_row` (function, line 8785) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
  - `ov_box_clips` (function, line 8974) `static int ov_box_clips(const pv_box_def *d)`
  - `ov_collect_chain` (function, line 8981) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)`
  - `ov_box_bounds` (function, line 9002) `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)`
  - `ov_content_rect` (function, line 9026) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...`
  - `fragment` (function, line 9046) `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
  - `box_forms_stacking_context` (function, line 9101) `static int box_forms_stacking_context(const pv_box_def *def)`
  - `bui_skew_tan` (function, line 9144) `static double bui_skew_tan(int deg)`
  - `box_transform_matrix` (function, line 9150) `static void box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
             ...`
  - `bui_blend_operator` (function, line 9269) `static cairo_operator_t bui_blend_operator(int mix_blend)`
  - `bui_paint_backdrop_blur` (function, line 9407) `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...`
  - `bui_pop_group_composite` (function, line 9465) `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms)`
  - `limits` (function, line 9695) `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
  - `paint_box_decoration_grouped` (function, line 9763) `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
  - `paint_box_and_direct_rows` (function, line 9804) `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...`
  - `paint_positioned_one` (function, line 9899) `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...`
  - `paint_nested_children` (function, line 10088) `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...`
  - `paint_structured` (function, line 10120) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
  - `write_doc_pdf` (function, line 10338) `static long write_doc_pdf(browser_window *w, const char *path)`
  - `export_pdf` (function, line 10443) `static void export_pdf(browser_window *w)`
  - `write_doc_png` (function, line 10507) `static long write_doc_png(browser_window *w, const char *path)`
  - `export_png` (function, line 10628) `static void export_png(browser_window *w)`
  - `caller` (function, line 10663) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
  - `ui_render_png` (function, line 10686) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)`
  - `render_doc_images` (function, line 10712) `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...`
  - `ui_render_png_images` (function, line 10742) `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_pdf_images` (function, line 10748) `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_dump_layout` (function, line 10764) `ui_status ui_dump_layout(const rd_doc *doc)`
  - `link_at_point` (function, line 10825) `static const char *link_at_point(browser_window *w, double px, double py)`
  - `resolve_box_cursor` (function, line 10919) `static int resolve_box_cursor(const rd_doc *doc, int block_id)`
  - `box_pointer_events_none` (function, line 10933) `static int box_pointer_events_none(const rd_doc *doc, int block_id)`
  - `cursor_at_point` (function, line 10949) `static int cursor_at_point(browser_window *w, double px, double py)`
  - `node_at_point` (function, line 11001) `static dom_node_id node_at_point(browser_window *w, double px, double py)`
  - `reference` (function, line 11049) `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
  - `apply_click_result` (function, line 11070) `static void apply_click_result(browser_window *w, tab_page *page)`
  - `memory` (function, line 11093) `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
  - `GET` (function, line 11176) `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
  - `ensure_download_dir` (function, line 11210) `static int ensure_download_dir(char *out, size_t outsz)`
  - `write_file_atomic` (function, line 11225) `static int write_file_atomic(const char *path, const void *bytes, size_t len)`
  - `save_download` (function, line 11247) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...`
  - `save_current_page` (function, line 11280) `static void save_current_page(browser_window *w)`
  - `deliver_fetch_result` (function, line 11289) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
  - `drain_fetch_results` (function, line 11344) `static void drain_fetch_results(browser_window *w)`
  - `toggle_reader` (function, line 11420) `static void toggle_reader(browser_window *w)`
  - `menu_item_checked` (function, line 11431) `static int menu_item_checked(const browser_window *w, size_t i)`
  - `menu_item_toggle` (function, line 11453) `static void menu_item_toggle(browser_window *w, size_t i)`
  - `draw_clock` (function, line 11563) `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...`
  - `draw_hamburger` (function, line 11574) `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_reload` (function, line 11591) `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_menu` (function, line 11613) `static void draw_menu(cairo_t *cr, browser_window *w)`
  - `draw_hover_url` (function, line 11724) `static double draw_hover_url(cairo_t *cr, browser_window *w)`
  - `draw_toast` (function, line 11756) `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)`
  - `draw_tabstrip` (function, line 11786) `static void draw_tabstrip(cairo_t *cr, browser_window *w)`
  - `draw_omnibox` (function, line 11841) `static void draw_omnibox(cairo_t *cr, browser_window *w)`
  - `paint` (function, line 11874) `static void paint(browser_window *w)`
  - `redraw` (function, line 12118) `static void redraw(browser_window *w)`
  - `wm_base_ping` (function, line 12130) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 12136) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 12144) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `wl_array_for_each` (function, line 12161) `wl_array_for_each(st, states)`
  - `toplevel_close` (function, line 12167) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 12175) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `set_cursor` (function, line 12188) `static void set_cursor(browser_window *w, int cur_kind)`
  - `element` (function, line 12218) `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...`
  - `fbw_split_y` (function, line 12288) `static double fbw_split_y(const freebug_window *fb)`
  - `freebug_ensure_buffer` (function, line 12296) `static int freebug_ensure_buffer(freebug_window *fb)`
  - `fbw_level_rgb` (function, line 12324) `static void fbw_level_rgb(int level, double *r, double *g, double *b)`
  - `fbw_console_lines` (function, line 12335) `static size_t fbw_console_lines(const fb_buffer *log)`
  - `freebug_paint` (function, line 12347) `static void freebug_paint(freebug_window *fb)`
  - `freebug_redraw_fb` (function, line 12546) `static void freebug_redraw_fb(freebug_window *fb)`
  - `freebug_redraw` (function, line 12555) `static void freebug_redraw(browser_window *w)`
  - `freebug_hide` (function, line 12559) `static void freebug_hide(browser_window *w)`
  - `fbw_xdg_surface_configure` (function, line 12575) `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `fbw_toplevel_configure` (function, line 12583) `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...`
  - `fbw_toplevel_close` (function, line 12593) `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)`
  - `freebug_show` (function, line 12602) `static void freebug_show(browser_window *w)`
  - `freebug_toggle` (function, line 12632) `static void freebug_toggle(browser_window *w)`
  - `freebug_destroy` (function, line 12637) `static void freebug_destroy(browser_window *w)`
  - `freebug_owns_surface` (function, line 12644) `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)`
  - `freebug_is_open` (function, line 12648) `static int freebug_is_open(const browser_window *w)`
  - `freebug_repl_worker` (function, line 12656) `static tab *freebug_repl_worker(browser_window *w)`
  - `freebug_eval` (function, line 12692) `static void freebug_eval(browser_window *w)`
  - `freebug_handle_key` (function, line 12732) `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...`
  - `freebug_pointer_button` (function, line 12767) `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...`
  - `freebug_pointer_motion` (function, line 12786) `static void freebug_pointer_motion(browser_window *w)`
  - `freebug_pointer_axis` (function, line 12808) `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)`
  - `ptr_enter` (function, line 12826) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
  - `ptr_leave` (function, line 12845) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
  - `ptr_motion` (function, line 12862) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
  - `load_current` (function, line 12886) `static void load_current(browser_window *w)`
  - `go_omnibox` (function, line 12900) `static void go_omnibox(browser_window *w)`
  - `ptr_button` (function, line 12944) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
  - `scroll_line_px` (function, line 13174) `static double scroll_line_px(const browser_window *w)`
  - `ptr_axis` (function, line 13177) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
  - `ptr_frame` (function, line 13201) `static void ptr_frame(void *d, struct wl_pointer *p)`
  - `mime_is_text` (function, line 13218) `static int mime_is_text(const char *mime)`
  - `data_offer_source_actions` (function, line 13236) `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_offer_action` (function, line 13239) `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_device_data_offer` (function, line 13249) `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...`
  - `data_device_selection` (function, line 13261) `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...`
  - `data_device_enter` (function, line 13280) `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...`
  - `data_device_leave` (function, line 13285) `static void data_device_leave(void *d, struct wl_data_device *dev)`
  - `data_device_motion` (function, line 13286) `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...`
  - `data_device_drop` (function, line 13290) `static void data_device_drop(void *d, struct wl_data_device *dev)`
  - `data_source_cancelled` (function, line 13301) `static void data_source_cancelled(void *data, struct wl_data_source *src)`
  - `data_source_send` (function, line 13307) `static void data_source_send(void *data, struct wl_data_source *src,
                            ...`
  - `data_source_target` (function, line 13320) `static void data_source_target(void *d, struct wl_data_source *s, const char *m)`
  - `freebug_copy_console` (function, line 13332) `static void freebug_copy_console(browser_window *w)`
  - `insert_pasted_text` (function, line 13390) `static void insert_pasted_text(browser_window *w, const char *text, size_t len)`
  - `clipboard_copy` (function, line 13454) `static void clipboard_copy(browser_window *w)`
  - `keyboard_keymap` (function, line 13501) `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...`
  - `keyboard_enter` (function, line 13522) `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...`
  - `keyboard_leave` (function, line 13530) `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)`
  - `key_sym_to_js_key` (function, line 13538) `static const char *key_sym_to_js_key(xkb_keysym_t sym)`
  - `key_sym_to_keycode` (function, line 13564) `static int key_sym_to_keycode(xkb_keysym_t sym)`
  - `dispatch_js_event` (function, line 13589) `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...`
  - `handle_key_press` (function, line 13646) `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...`
  - `key_is_repeatable` (function, line 13976) `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)`
  - `key_repeat_arm` (function, line 13992) `static void key_repeat_arm(browser_window *w, uint32_t key)`
  - `key_repeat_stop` (function, line 14005) `static void key_repeat_stop(browser_window *w)`
  - `key_repeat_fire` (function, line 14016) `static void key_repeat_fire(browser_window *w)`
  - `keyboard_key` (function, line 14029) `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...`
  - `keyboard_modifiers` (function, line 14069) `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...`
  - `keyboard_repeat_info` (function, line 14079) `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)`
  - `seat_caps` (function, line 14097) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
  - `seat_name` (function, line 14109) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
  - `registry_global` (function, line 14115) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
  - `registry_remove` (function, line 14136) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
  - `ui_run_browser` (function, line 14145) `ui_status ui_run_browser(const char *start_url)`
  - `cost` (function, line 14522) `* measured cost (floor 33 ms = the existing ~30 fps ceiling):
             * cheap pages paint at...`
  - `_GNU_SOURCE` (macro, line 11)
  - `UI_TOOLBAR_H` (macro, line 80)
  - `UI_TITLEBAR_H` (macro, line 82)
  - `UI_TABBAR_H` (macro, line 83)
  - `UI_TAB_MIN_W` (macro, line 84)
  - `UI_TAB_MAX_W` (macro, line 85)
  - `UI_TAB_NEW_W` (macro, line 86)
  - `UI_TAB_CLOSE_W` (macro, line 87)
  - `UI_BTN_W` (macro, line 88)
  - `UI_WIN_BTN_W` (macro, line 89)
  - `UI_MARGIN` (macro, line 90)
  - `UI_BTN_LEFT` (macro, line 91)
  - `UI_LIST_INDENT` (macro, line 92)
  - `UI_SCROLLBAR_W` (macro, line 97)
  - `UI_SCROLLBAR_MIN` (macro, line 98)
  - `UI_SCROLLBAR_PAD` (macro, line 99)
  - `UI_RESIZE_MARGIN` (macro, line 103)
  - `UI_MENU_W` (macro, line 108)
  - `UI_MENU_ITEM_H` (macro, line 109)
  - `UI_MENU_PAD` (macro, line 110)
  - `UI_CHECK_SZ` (macro, line 111)
  - `UI_MENU_LABEL_H` (macro, line 112)
  - `UI_MENU_INPUT_H` (macro, line 113)
  - `UI_HAMBURGER_W` (macro, line 114)
  - `UI_HAMBURGER_GAP` (macro, line 115)
  - `UI_CURSOR_SIZE` (macro, line 116)
  - `UI_TOAST_PAD` (macro, line 117)
  - `OMNI_MAX_SUGG` (macro, line 118)
  - `UI_OMNI_ROW_H` (macro, line 119)
  - `UI_TWO_PI` (macro, line 120)
  - `UI_INPUT_PAD` (macro, line 124)
  - `UI_INPUT_MEASURE_W` (macro, line 127)
  - `UI_INPUT_WIDTH` (macro, line 128)
  - `UI_BUTTON_HPAD` (macro, line 129)
  - `UI_FORM_FIELDS_MAX` (macro, line 130)
  - `UI_UNDERLINE_OFFSET` (macro, line 135)
  - `UI_UNDERLINE_THICK` (macro, line 136)
  - `UI_STRIKE_OFFSET` (macro, line 137)
  - `UI_OVERLINE_OFFSET` (macro, line 138)
  - `UI_SLICE_MAX` (macro, line 142)
  - `UI_MENU_COUNT` (macro, line 201)
  - `UI_IMAGE_MAX_BODY` (macro, line 219)
  - `UI_MAX_TABS` (macro, line 258)
  - `UI_READER_COLUMN_W` (macro, line 555)
  - `JS_NAV_MAX` (macro, line 1934)
  - `JS_TICKS_PER_LOAD` (macro, line 2009)
  - `UI_RELOAD_X` (macro, line 2730)
  - `RC_BOX_STACK_MAX` (macro, line 3031)
  - `RC_FLOAT_MAX` (macro, line 3035)
  - `RC_FLOAT_FIT_MIN` (macro, line 3042)
  - `FLEX_MEASURE_W` (macro, line 4544)
  - `FLEX_MIN_MEASURE_W` (macro, line 4549)
  - `RC_MAX_OUT_OF_FLOW` (macro, line 6107)
  - `BUI_CONIC_SLICES` (macro, line 8273)
  - `OV_MAX_DEPTH` (macro, line 8970)
  - `H2R` (macro, line 9573)
  - `PDF_PAGE_W` (macro, line 10322)
  - `PDF_PAGE_H` (macro, line 10323)
  - `PDF_MARGIN` (macro, line 10324)
  - `PNG_PAGE_W` (macro, line 10486)
  - `PNG_MARGIN` (macro, line 10499)
  - `PNG_MAX_H` (macro, line 10500)
  - `FBW_W` (macro, line 12253)
  - `FBW_H` (macro, line 12255)
  - `FBW_HEADER` (macro, line 12256)
  - `FBW_PAD` (macro, line 12257)
  - `FBW_LINE` (macro, line 12258)
  - `FBW_GUTTER` (macro, line 12259)
  - `FBW_MIN_SPLIT` (macro, line 12260)
  - `FBW_MAX_SPLIT` (macro, line 12261)
  - `FBW_COPY_BTN_W` (macro, line 12262)
  - `FBW_COPY_BTN_H` (macro, line 12263)

## gui/browser_ui_internal.h
- Layer: presentation
- Doc: ifndef FREEDOM_BROWSER_UI_INTERNAL_H define FREEDOM_BROWSER_UI_INTERNAL_H  ifdef __cplusplus error "Freedom is pure C (C
- Language: h
- Symbols:
  - `ui_rgb` (struct, line 39)
  - `ui_theme` (struct, line 41)
  - `FREEDOM_BROWSER_UI_INTERNAL_H` (macro, line 2)
  - `UI_FONT_SIZE` (macro, line 28)
  - `UI_TEXT_MARGIN` (macro, line 29)
  - `UI_HEADING_LEVELS` (macro, line 30)

## gui/bui_theme.c
- Layer: presentation
- Language: c
- Symbols:
  - `ui_theme_default` (function, line 14) `ui_theme ui_theme_default(void)`
  - `ui_theme_dark` (function, line 84) `ui_theme ui_theme_dark(void)`
  - `ui_theme_sepia` (function, line 129) `ui_theme ui_theme_sepia(void)`
  - `ui_theme_for` (function, line 171) `ui_theme ui_theme_for(int mode)`
  - `rgb_from_packed` (function, line 180) `ui_rgb rgb_from_packed(int packed)`
  - `set_rgb` (function, line 184) `void set_rgb(cairo_t *cr, ui_rgb c)`

## gui/freedom_view.c
- Layer: presentation
- Language: c
- Symbols:
  - `main` (function, line 36) `int main(int argc, char **argv)`
  - `_POSIX_C_SOURCE` (macro, line 9)

## gui/svg_paint.c
- Layer: presentation
- Doc: svg_paint — Cairo back end for the shapes svg_render extracted.
- Language: c
- Symbols:
  - `svp_alpha` (function, line 30) `static double svp_alpha(int opacity, int paint_opacity)`
  - `svp_rect_path` (function, line 37) `static void svp_rect_path(cairo_t *cr, const sv_shape *sh)`
  - `svp_shape_path` (function, line 71) `static void svp_shape_path(cairo_t *cr, const sv_image *img, const sv_shape *sh)`
  - `svp_draw_text` (function, line 124) `static void svp_draw_text(cairo_t *cr, const sv_shape *sh, int current_rgb)`
  - `svp_draw` (function, line 137) `void svp_draw(cairo_t *cr, const sv_image *img,
              double x, double y, double w, doubl...`

## gui/ui_render.c
- Layer: presentation
- Language: c
- Symbols:
  - `ui_window` (struct, line 65)
  - `sanitize_utf8_inplace` (function, line 37) `static void sanitize_utf8_inplace(char *s)`
  - `button_rects` (function, line 105) `static void button_rects(const ui_window *w, double *min_x, double *max_x, double *close_x)`
  - `buffer_release` (function, line 112) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 119) `static void destroy_buffer(ui_window *w)`
  - `ensure_buffer` (function, line 125) `static int ensure_buffer(ui_window *w)`
  - `paint` (function, line 156) `static void paint(ui_window *w)`
  - `redraw` (function, line 242) `static void redraw(ui_window *w)`
  - `wm_base_ping` (function, line 257) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 263) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 271) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `toplevel_close` (function, line 281) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 292) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `ptr_enter` (function, line 302) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
  - `ptr_leave` (function, line 310) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
  - `ptr_motion` (function, line 313) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
  - `ptr_button` (function, line 320) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
  - `ptr_axis` (function, line 342) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
  - `seat_caps` (function, line 364) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
  - `seat_name` (function, line 374) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
  - `registry_global` (function, line 380) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
  - `registry_remove` (function, line 399) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
  - `ui_run_text_view` (function, line 407) `ui_status ui_run_text_view(const char *title, const char *text, size_t text_len)`
  - `_GNU_SOURCE` (macro, line 9)
  - `UI_FONT_SIZE` (macro, line 25)
  - `UI_MARGIN` (macro, line 27)
  - `UI_TITLEBAR_H` (macro, line 28)
  - `UI_BTN_W` (macro, line 29)
  - `UI_BTN_LEFT` (macro, line 30)
