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
  - `rc_defer_col` (struct, line 6241)
  - `rc_defer` (struct, line 6248)
  - `freebug_window` (struct, line 12832)
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
  - `key` (type_alias, line 6241) `typedef struct rc_defer_col { int key;`
  - `col` (type_alias, line 6248) `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];`
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
  - `open_line_height` (function, line 3586) `static double open_line_height(const rc_state *s, const ui_theme *th)`
  - `open_line` (function, line 3598) `static void open_line(rc_layout *L, rc_state *s)`
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
  - `emit_replaced_row` (function, line 4072) `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `flow_text_block` (function, line 4175) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
  - `item_root_box_in` (function, line 4287) `static int item_root_box_in(const rd_doc *doc, size_t b0, size_t b1, int cbox)`
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
  - `measure_item_content_w` (function, line 4651) `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
  - `item_declared_basis` (function, line 4683) `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
  - `nested_cont_basis` (function, line 4697) `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...`
  - `flex_item_basis` (function, line 4729) `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
  - `flex_item_min_main` (function, line 4760) `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...`
  - `item_at_level` (function, line 4793) `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `child_cont_at_level` (function, line 4808) `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `root_cont_of` (function, line 4823) `static int root_cont_of(const rd_doc *doc, int cid)`
  - `block_is_oof` (function, line 4860) `static int block_is_oof(const rd_doc *doc, const rd_block *bk)`
  - `layout_container` (function, line 4876) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `ITEMS` (function, line 4987) `* between ITEMS (not between the lines inside one item). column-reverse
     * reverses the visua...`
  - `slot` (function, line 5079) `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
  - `path` (function, line 5197) `*
         * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when
        ...`
  - `box_line_visible` (function, line 5529) `static int box_line_visible(int style)`
  - `close_top_box` (function, line 5536) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `rc_box_context` (function, line 5673) `static void rc_box_context(const rc_state *s, double content_w,
                           double...`
  - `box_margin_top` (function, line 5699) `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `box_margin_bottom` (function, line 5706) `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `children` (function, line 5717) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
  - `column` (function, line 5924) `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
  - `box_path_has` (function, line 6019) `static int box_path_has(const rd_doc *doc, int block_id, int want)`
  - `box_shrink_width` (function, line 6034) `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...`
  - `reconcile_boxes_below` (function, line 6042) `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
  - `treatment` (function, line 6088) `* block treatment (shrink-wrapped and placed by text-align), which is what a
         * standalon...`
  - `reconcile_boxes` (function, line 6115) `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
  - `box_path_of` (function, line 6130) `static int box_path_of(const rd_doc *doc, int block_id, int *out)`
  - `band_common_box` (function, line 6146) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)`
  - `block_in_table_caption` (function, line 6210) `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)`
  - `defer_key_block` (function, line 6269) `static int defer_key_block(const rd_block *bk)`
  - `defer_append` (function, line 6391) `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...`
  - `defer_flush` (function, line 6426) `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...`
  - `layout_float_band` (function, line 6646) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
  - `thumbnail` (function, line 6728) `* is what made a wikipedia thumbnail (a 250px image and its caption, no
     * declared width) sp...`
  - `layout_doc` (function, line 6983) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
  - `position_doc` (function, line 7353) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
  - `input_box_width` (function, line 7511) `static double input_box_width(double content_w)`
  - `select_box_width` (function, line 7514) `static double select_box_width(double content_w)`
  - `button_box_width` (function, line 7520) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...`
  - `v_read` (function, line 8100) `static int v_read(int fd, void *buf, size_t n)`
  - `dies` (function, line 8128) `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
  - `audio_spawn` (function, line 8136) `static void audio_spawn(browser_window *w, int rate, int channels)`
  - `audio_mark_dead` (function, line 8191) `static void audio_mark_dead(browser_window *w)`
  - `audio_write` (function, line 8208) `static void audio_write(browser_window *w, const uint8_t *data, size_t len)`
  - `audio_stop` (function, line 8222) `static void audio_stop(browser_window *w)`
  - `video_stop` (function, line 8242) `static void video_stop(browser_window *w)`
  - `video_fetch` (function, line 8421) `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...`
  - `video_play` (function, line 8438) `static int video_play(browser_window *w, const char *m3u8_url)`
  - `video_stop` (function, line 8540) `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
  - `paint_video_row` (function, line 8593) `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
  - `row_line_slack` (function, line 8706) `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)`
  - `row_align_offset` (function, line 8718) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)`
  - `upstream` (function, line 8746) `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
  - `box_path` (function, line 8774) `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `text` (function, line 8791) `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
  - `bui_grad_color_at` (function, line 8816) `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...`
  - `spaced` (function, line 8847) `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
  - `paint_bg_layer` (function, line 8879) `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...`
  - `paint_box_decoration` (function, line 8922) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
  - `cairo_set_dash` (function, line 9085) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 9088) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 9127) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 9130) `cairo_set_dash(cr, (double[])`
  - `set_rgb` (function, line 9164) `set_rgb(cr, (ui_rgb)`
  - `cairo_set_dash` (function, line 9187) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 9190) `cairo_set_dash(cr, (double[])`
  - `paint_deco_line` (function, line 9248) `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...`
  - `cairo_set_dash` (function, line 9282) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 9284) `cairo_set_dash(cr, (double[])`
  - `paint_svg_at` (function, line 9304) `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...`
  - `replaced_current_color` (function, line 9324) `static int replaced_current_color(const browser_window *w, const rd_block *blk)`
  - `paint_inline_replaced` (function, line 9333) `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...`
  - `paint_content_row` (function, line 9352) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
  - `ov_box_clips` (function, line 9541) `static int ov_box_clips(const pv_box_def *d)`
  - `ov_collect_chain` (function, line 9548) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)`
  - `ov_box_bounds` (function, line 9569) `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)`
  - `ov_content_rect` (function, line 9593) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...`
  - `fragment` (function, line 9613) `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
  - `box_forms_stacking_context` (function, line 9668) `static int box_forms_stacking_context(const pv_box_def *def)`
  - `bui_skew_tan` (function, line 9711) `static double bui_skew_tan(int deg)`
  - `box_transform_matrix` (function, line 9717) `static void box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
             ...`
  - `bui_blend_operator` (function, line 9836) `static cairo_operator_t bui_blend_operator(int mix_blend)`
  - `bui_paint_backdrop_blur` (function, line 9974) `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...`
  - `bui_pop_group_composite` (function, line 10032) `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms)`
  - `limits` (function, line 10262) `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
  - `paint_box_decoration_grouped` (function, line 10330) `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
  - `paint_box_and_direct_rows` (function, line 10371) `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...`
  - `paint_positioned_one` (function, line 10466) `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...`
  - `paint_nested_children` (function, line 10655) `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...`
  - `paint_structured` (function, line 10687) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
  - `write_doc_pdf` (function, line 10905) `static long write_doc_pdf(browser_window *w, const char *path)`
  - `export_pdf` (function, line 11010) `static void export_pdf(browser_window *w)`
  - `write_doc_png` (function, line 11074) `static long write_doc_png(browser_window *w, const char *path)`
  - `export_png` (function, line 11195) `static void export_png(browser_window *w)`
  - `caller` (function, line 11230) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
  - `ui_render_png` (function, line 11253) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)`
  - `render_doc_images` (function, line 11279) `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...`
  - `ui_render_png_images` (function, line 11309) `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_pdf_images` (function, line 11315) `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_dump_layout` (function, line 11331) `ui_status ui_dump_layout(const rd_doc *doc)`
  - `link_at_point` (function, line 11392) `static const char *link_at_point(browser_window *w, double px, double py)`
  - `resolve_box_cursor` (function, line 11486) `static int resolve_box_cursor(const rd_doc *doc, int block_id)`
  - `box_pointer_events_none` (function, line 11500) `static int box_pointer_events_none(const rd_doc *doc, int block_id)`
  - `cursor_at_point` (function, line 11516) `static int cursor_at_point(browser_window *w, double px, double py)`
  - `node_at_point` (function, line 11568) `static dom_node_id node_at_point(browser_window *w, double px, double py)`
  - `reference` (function, line 11616) `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
  - `apply_click_result` (function, line 11637) `static void apply_click_result(browser_window *w, tab_page *page)`
  - `memory` (function, line 11660) `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
  - `GET` (function, line 11743) `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
  - `ensure_download_dir` (function, line 11777) `static int ensure_download_dir(char *out, size_t outsz)`
  - `write_file_atomic` (function, line 11792) `static int write_file_atomic(const char *path, const void *bytes, size_t len)`
  - `save_download` (function, line 11814) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...`
  - `save_current_page` (function, line 11847) `static void save_current_page(browser_window *w)`
  - `deliver_fetch_result` (function, line 11856) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
  - `drain_fetch_results` (function, line 11911) `static void drain_fetch_results(browser_window *w)`
  - `toggle_reader` (function, line 11987) `static void toggle_reader(browser_window *w)`
  - `menu_item_checked` (function, line 11998) `static int menu_item_checked(const browser_window *w, size_t i)`
  - `menu_item_toggle` (function, line 12020) `static void menu_item_toggle(browser_window *w, size_t i)`
  - `draw_clock` (function, line 12130) `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...`
  - `draw_hamburger` (function, line 12141) `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_reload` (function, line 12158) `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_menu` (function, line 12180) `static void draw_menu(cairo_t *cr, browser_window *w)`
  - `draw_hover_url` (function, line 12291) `static double draw_hover_url(cairo_t *cr, browser_window *w)`
  - `draw_toast` (function, line 12323) `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)`
  - `draw_tabstrip` (function, line 12353) `static void draw_tabstrip(cairo_t *cr, browser_window *w)`
  - `draw_omnibox` (function, line 12408) `static void draw_omnibox(cairo_t *cr, browser_window *w)`
  - `paint` (function, line 12441) `static void paint(browser_window *w)`
  - `redraw` (function, line 12685) `static void redraw(browser_window *w)`
  - `wm_base_ping` (function, line 12697) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 12703) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 12711) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `wl_array_for_each` (function, line 12728) `wl_array_for_each(st, states)`
  - `toplevel_close` (function, line 12734) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 12742) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `set_cursor` (function, line 12755) `static void set_cursor(browser_window *w, int cur_kind)`
  - `element` (function, line 12785) `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...`
  - `fbw_split_y` (function, line 12855) `static double fbw_split_y(const freebug_window *fb)`
  - `freebug_ensure_buffer` (function, line 12863) `static int freebug_ensure_buffer(freebug_window *fb)`
  - `fbw_level_rgb` (function, line 12891) `static void fbw_level_rgb(int level, double *r, double *g, double *b)`
  - `fbw_console_lines` (function, line 12902) `static size_t fbw_console_lines(const fb_buffer *log)`
  - `freebug_paint` (function, line 12914) `static void freebug_paint(freebug_window *fb)`
  - `freebug_redraw_fb` (function, line 13113) `static void freebug_redraw_fb(freebug_window *fb)`
  - `freebug_redraw` (function, line 13122) `static void freebug_redraw(browser_window *w)`
  - `freebug_hide` (function, line 13126) `static void freebug_hide(browser_window *w)`
  - `fbw_xdg_surface_configure` (function, line 13142) `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `fbw_toplevel_configure` (function, line 13150) `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...`
  - `fbw_toplevel_close` (function, line 13160) `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)`
  - `freebug_show` (function, line 13169) `static void freebug_show(browser_window *w)`
  - `freebug_toggle` (function, line 13199) `static void freebug_toggle(browser_window *w)`
  - `freebug_destroy` (function, line 13204) `static void freebug_destroy(browser_window *w)`
  - `freebug_owns_surface` (function, line 13211) `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)`
  - `freebug_is_open` (function, line 13215) `static int freebug_is_open(const browser_window *w)`
  - `freebug_repl_worker` (function, line 13223) `static tab *freebug_repl_worker(browser_window *w)`
  - `freebug_eval` (function, line 13259) `static void freebug_eval(browser_window *w)`
  - `freebug_handle_key` (function, line 13299) `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...`
  - `freebug_pointer_button` (function, line 13334) `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...`
  - `freebug_pointer_motion` (function, line 13353) `static void freebug_pointer_motion(browser_window *w)`
  - `freebug_pointer_axis` (function, line 13375) `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)`
  - `ptr_enter` (function, line 13393) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
  - `ptr_leave` (function, line 13412) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
  - `ptr_motion` (function, line 13429) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
  - `load_current` (function, line 13453) `static void load_current(browser_window *w)`
  - `go_omnibox` (function, line 13467) `static void go_omnibox(browser_window *w)`
  - `ptr_button` (function, line 13511) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
  - `scroll_line_px` (function, line 13741) `static double scroll_line_px(const browser_window *w)`
  - `ptr_axis` (function, line 13744) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
  - `ptr_frame` (function, line 13768) `static void ptr_frame(void *d, struct wl_pointer *p)`
  - `mime_is_text` (function, line 13785) `static int mime_is_text(const char *mime)`
  - `data_offer_source_actions` (function, line 13803) `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_offer_action` (function, line 13806) `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_device_data_offer` (function, line 13816) `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...`
  - `data_device_selection` (function, line 13828) `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...`
  - `data_device_enter` (function, line 13847) `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...`
  - `data_device_leave` (function, line 13852) `static void data_device_leave(void *d, struct wl_data_device *dev)`
  - `data_device_motion` (function, line 13853) `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...`
  - `data_device_drop` (function, line 13857) `static void data_device_drop(void *d, struct wl_data_device *dev)`
  - `data_source_cancelled` (function, line 13868) `static void data_source_cancelled(void *data, struct wl_data_source *src)`
  - `data_source_send` (function, line 13874) `static void data_source_send(void *data, struct wl_data_source *src,
                            ...`
  - `data_source_target` (function, line 13887) `static void data_source_target(void *d, struct wl_data_source *s, const char *m)`
  - `freebug_copy_console` (function, line 13899) `static void freebug_copy_console(browser_window *w)`
  - `insert_pasted_text` (function, line 13957) `static void insert_pasted_text(browser_window *w, const char *text, size_t len)`
  - `clipboard_copy` (function, line 14021) `static void clipboard_copy(browser_window *w)`
  - `keyboard_keymap` (function, line 14068) `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...`
  - `keyboard_enter` (function, line 14089) `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...`
  - `keyboard_leave` (function, line 14097) `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)`
  - `key_sym_to_js_key` (function, line 14105) `static const char *key_sym_to_js_key(xkb_keysym_t sym)`
  - `key_sym_to_keycode` (function, line 14131) `static int key_sym_to_keycode(xkb_keysym_t sym)`
  - `dispatch_js_event` (function, line 14156) `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...`
  - `handle_key_press` (function, line 14213) `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...`
  - `key_is_repeatable` (function, line 14543) `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)`
  - `key_repeat_arm` (function, line 14559) `static void key_repeat_arm(browser_window *w, uint32_t key)`
  - `key_repeat_stop` (function, line 14572) `static void key_repeat_stop(browser_window *w)`
  - `key_repeat_fire` (function, line 14583) `static void key_repeat_fire(browser_window *w)`
  - `keyboard_key` (function, line 14596) `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...`
  - `keyboard_modifiers` (function, line 14636) `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...`
  - `keyboard_repeat_info` (function, line 14646) `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)`
  - `seat_caps` (function, line 14664) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
  - `seat_name` (function, line 14676) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
  - `registry_global` (function, line 14682) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
  - `registry_remove` (function, line 14703) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
  - `ui_run_browser` (function, line 14712) `ui_status ui_run_browser(const char *start_url)`
  - `cost` (function, line 15089) `* measured cost (floor 33 ms = the existing ~30 fps ceiling):
             * cheap pages paint at...`
  - `clock_gettime` (function, line 147) `clock_gettime(CLOCK_MONOTONIC, &ts);`
  - `offset` (function, line 155) `* offset (labels and the flag live in one place, no magic indices);`
  - `fields` (function, line 262) `* fields (so the 200+ render/event call sites stay unchanged);`
  - `delay` (function, line 356) `* timer delay (tab_page.next_timer_ms);`
  - `main` (function, line 486) `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never blocks on HTTP. The thread is spawned by * video_play() and joined by video_stop();`
  - `apply_theme` (function, line 573) `apply_theme(w);`
  - `snprintf` (function, line 575) `snprintf(msg, sizeof msg, "Zoom %d%%", w->zoom_pct);`
  - `browser_set_status` (function, line 576) `browser_set_status(&w->bs, msg, now_ms());`
  - `wl_shm_pool_destroy` (function, line 611) `wl_shm_pool_destroy(pool);`
  - `close` (function, line 612) `close(fd);`
  - `wl_buffer_add_listener` (function, line 614) `wl_buffer_add_listener(w->buffer, &buffer_listener, w);`
  - `rewind` (function, line 631) `rewind(f);`
  - `fclose` (function, line 635) `fclose(f);`
  - `hb_load` (function, line 681) `hb_load(s, txt, list);`
  - `free` (function, line 682) `free(txt);`
  - `mkdir` (function, line 757) `mkdir(cfg, 0700);`
  - `memcpy` (function, line 803) `memcpy(txt, cur, cur_len);`
  - `hb_free` (function, line 824) `hb_free(w->js_hosts);`
  - `proxy` (function, line 976) `* and enable each proxy ("1" => the default port);`
  - `memset` (function, line 980) `memset(&w->net_cfg, 0, sizeof w->net_cfg);`
  - `video_feeder_thread` (function, line 1029) `static void *video_feeder_thread(void *arg);`
  - `xdg_toplevel_unset_fullscreen` (function, line 1037) `xdg_toplevel_unset_fullscreen(w->xdg_toplevel);`
  - `xdg_toplevel_set_fullscreen` (function, line 1039) `xdg_toplevel_set_fullscreen(w->xdg_toplevel, NULL);`
  - `tf_init` (function, line 1187) `tf_init(&st->field);`
  - `free_bg_images` (function, line 1205) `free_bg_images(w);`
  - `cairo_surface_destroy` (function, line 1228) `cairo_surface_destroy(s);`
  - `cairo_surface_flush` (function, line 1231) `cairo_surface_flush(s);`
  - `cairo_surface_mark_dirty` (function, line 1240) `cairo_surface_mark_dirty(s);`
  - `sf_response_free` (function, line 1303) `sf_response_free(out);`
  - `hb_is_allowlisted` (function, line 1360) `return hb_is_allowlisted(w->hosts, host);`
  - `apply_auth` (function, line 1391) `apply_auth(w, abs, &cfg);`
  - `proceed` (function, line 1492) `* may proceed (cfg and pr->allowlisted are then set);`
  - `pthread_mutex_lock` (function, line 1623) `pthread_mutex_lock(&w->stream_lock);`
  - `pthread_mutex_unlock` (function, line 1631) `pthread_mutex_unlock(&w->stream_lock);`
  - `pthread_detach` (function, line 1734) `pthread_detach(th);`
  - `secure_fetch` (function, line 1740) `* through secure_fetch (Zero Trust);`
  - `tab_image_free` (function, line 1775) `tab_image_free(&img);`
  - `fetch_decode_image` (function, line 1866) `fetch_decode_image(w, t, img_fetch, fetch_ctx, target_url, &imgpool, pooled, &slot->surface, &slot->nat_w, &slot->nat_h);`
  - `string` (function, line 1888) `* or an empty string (unset, blocked, or off by caps.images), so there is no * decision to re-check, unlike load_images which still reads b->img_decision (a * box def carries no decision field, only t`
  - `do_load` (function, line 1929) `static void do_load(browser_window *w, const char *url);`
  - `toggle` (function, line 1937) `* No network: a capability toggle (images/CSS) re-renders from cache. Does nothing * when there is no cached source (start/error pages stay in plain-text mode). * * allow_js_nav: on a FRESH load (not `
  - `jsp_enabled` (function, line 1955) `return jsp_enabled(w->js_mode, page_js_host_allowlisted(w));`
  - `jsp_trusted` (function, line 1963) `return jsp_trusted(compute_page_js(w), page_host_allowlisted(w));`
  - `tab_set_cookies` (function, line 1972) `tab_set_cookies(t, ckhdr);`
  - `sf_cookie_put` (function, line 1991) `sf_cookie_put(url, pair);`
  - `fb_buffer_reset` (function, line 2002) `fb_buffer_reset(&w->console);`
  - `browser_set_page` (function, line 2038) `browser_set_page(&w->bs, NULL, "Failed to spawn sandboxed tab.", 1);`
  - `stylesheets` (function, line 2044) `* External stylesheets (Hito 27) follow the author-styles opt-in -- or the * trusted-host doctrine (Hito 28) -- (GET-only at the parent gate);`
  - `tab_set_net_allowed` (function, line 2058) `tab_set_net_allowed(t, wc.net);`
  - `tab_set_css_allowed` (function, line 2059) `tab_set_css_allowed(t, wc.css);`
  - `tab_set_fetcher` (function, line 2084) `tab_set_fetcher(t, pf_pooled_fetch, &gated);`
  - `tab_set_viewport_w` (function, line 2094) `tab_set_viewport_w(t, (int)w->width);`
  - `pf_list_free` (function, line 2103) `pf_list_free(&scanned);`
  - `tab_close` (function, line 2107) `tab_close(t);`
  - `tab_page_free` (function, line 2125) `tab_page_free(&page);`
  - `fc_set_active` (function, line 2163) `fc_set_active(&w->fc, has_anim);`
  - `ALIVE` (function, line 2179) `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or a tab switch) closes it. */ fb_buffer_free(&w->console);`
  - `fb_buffer_init` (function, line 2183) `fb_buffer_init(&page.console);`
  - `browser_set_url_bar` (function, line 2295) `browser_set_url_bar(&w->bs, "about:bookmarks");`
  - `resolve` (function, line 2365) `* origin so its relative references and local images resolve (confined to the * document's directory) -- a local page "acts like https" for resolution. */ clear_doc(w);`
  - `browser_free` (function, line 2430) `browser_free(&w->bs);`
  - `browser_url_bar_clear` (function, line 2506) `browser_url_bar_clear(&w->bs);`
  - `cairo_rectangle` (function, line 2691) `cairo_rectangle(cr, tx, ty, UI_SCROLLBAR_W, trh);`
  - `cairo_fill` (function, line 2692) `cairo_fill(cr);`
  - `browser_can_back` (function, line 2766) `case UI_HOT_BACK: return browser_can_back(&w->bs);`
  - `browser_can_forward` (function, line 2767) `case UI_HOT_FWD: return browser_can_forward(&w->bs);`
  - `cairo_text_extents` (function, line 2803) `cairo_text_extents(cr, s, &te);`
  - `cairo_move_to` (function, line 2805) `cairo_move_to(cr, dx, y);`
  - `cairo_show_text` (function, line 2806) `cairo_show_text(cr, s);`
  - `smaller` (function, line 2921) `* size when the content is smaller (height) or wider (min-width);`
  - `HarfBuzz` (function, line 3289) `* descriptor via HarfBuzz (text_shape);`
  - `cairo_select_font_face` (function, line 3297) `cairo_select_font_face(cr, family_face(family), italic ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL, bold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);`
  - `cairo_set_font_size` (function, line 3300) `cairo_set_font_size(cr, size);`
  - `cairo_set_source_rgb` (function, line 3312) `else cairo_set_source_rgb(cr, c.r, c.g, c.b);`
  - `close_inline_box` (function, line 3548) `close_inline_box(L, s, s->cur_top, h);`
  - `produced` (function, line 3697) `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target without re-walking the document. node_id tags the * originating element for JS click dis`
  - `cairo_font_extents` (function, line 3773) `cairo_font_extents(cr, &fe);`
  - `line` (function, line 3781) `* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the same buffer the loop scans, so a tab-expanded * <pre> agrees with itself. */ int star`
  - `svg_intrinsic_size` (function, line 3970) `svg_intrinsic_size(b, &sw, &sh);`
  - `bx_replaced_box` (function, line 4069) `return bx_replaced_box(d->box_w, d->box_w_pct, d->aspect_num, d->aspect_den, avail_w, dw, dh);`
  - `box` (function, line 4118) `* declared intrinsic size reserves that box (broken-image parity);`
  - `item_sides_from_box` (function, line 4471) `return item_sides_from_box(doc, cbox, cb_w);`
  - `measure_item_w_at` (function, line 4655) `return measure_item_w_at(cr, w, th, doc, b0, b1, FLEX_MEASURE_W);`
  - `bx_width_cap` (function, line 4688) `return bx_width_cap(d->box_w, d->box_w_pct, content_w);`
  - `fx_auto_min_size` (function, line 4772) `return fx_auto_min_size(mc, basis, author_min, scroll);`
  - `close_all_boxes` (function, line 4782) `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);`
  - `TABLE` (function, line 4848) `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all containers has no run of its own to read them from -- that * is the whole reason the table ex`
  - `struct` (function, line 5184) `* struct (0 = auto);`
  - `own` (function, line 5425) `* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and its ancestors) * INSIDE the item -- which is what painted a nested nav's own backdro`
  - `multicol_fragment` (function, line 5527) `static double multicol_fragment(rc_layout *L, const rc_open_box *ob, double content_bottom);`
  - `behind` (function, line 5726) `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old code used th->paragraph_gap as a floor here, * which gave a <div> the vertical rhythm`
  - `bx_lp_px` (function, line 5807) `bx_lp_px(def->box_r, def->box_r_pct, avail_w), wcap, def->box_center, avail_w);`
  - `open_box` (function, line 6112) `open_box(L, s, th, path[k], d, ctx_left, ctx_w, shrink, align);`
  - `context` (function, line 6199) `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document order);`
  - `defer_founder_style` (function, line 6378) `defer_founder_style(doc, start, end, runs[r].key, &side, &ml, &mlpct, &mr, &mrpct);`
  - `fprintf` (function, line 6385) `fprintf(stderr, "[defer] band [%zu,%zu) keys=", start, end);`
  - `x` (function, line 6479) `* reported x is already the BORDER x (the §7c.2 rule);`
  - `leave_inline_box` (function, line 6868) `leave_inline_box(L, &si, bk->block_id);`
  - `chain` (function, line 7033) `* chain (the box that left the normal flow at this pen position);`
  - `first` (function, line 7095) `* flush first (no-op when nothing is deferred). */ defer_flush(cr, w, L, &s, th, content_w, doc, &df);`
  - `anchor` (function, line 7117) `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is a no-op * for it. Without this a flex header never anchored and pulled * columns te`
  - `key` (function, line 7176) `* founders splits by key (stories, rail, footer nav each take * their column);`
  - `have` (function, line 7190) `* as they always have (spec/float.md §6b.3). */ rc_float_clear(&s);`
  - `standalone` (function, line 7208) `* must not be treated as standalone (which would flush that line and give * the element a row of its own -- R7). */ int inline_replaced = replaced_is_inline_level(&s, b);`
  - `it` (function, line 7256) `* column: flush first so the column lands above it (source order), * then move the anchor — the image bottom is the container top * for whatever follows. */ defer_flush(cr, w, L, &s, th, content_w, do`
  - `rd_input_label` (function, line 7524) `: rd_input_label(b->input_type);`
  - `cairo_save` (function, line 7550) `cairo_save(cr);`
  - `cairo_clip` (function, line 7552) `cairo_clip(cr);`
  - `cairo_restore` (function, line 7556) `cairo_restore(cr);`
  - `cairo_set_line_width` (function, line 7566) `cairo_set_line_width(cr, lw);`
  - `cairo_arc` (function, line 7569) `cairo_arc(cr, bx + 7.0, by + 7.0, r, 0, 2 * M_PI);`
  - `cairo_stroke` (function, line 7570) `cairo_stroke(cr);`
  - `cairo_line_to` (function, line 7582) `cairo_line_to(cr, bx + 6.5, by + 10.5);`
  - `cairo_close_path` (function, line 7652) `cairo_close_path(cr);`
  - `rd_build` (function, line 7915) `* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr, rgb_from_packed(b->caret_color));`
  - `cairo_translate` (function, line 7952) `cairo_translate(cr, left + pad + ax, ry + pad);`
  - `cairo_scale` (function, line 7958) `cairo_scale(cr, dw / (double)im->nat_w, dh / (double)im->nat_h);`
  - `cairo_set_source_surface` (function, line 7993) `cairo_set_source_surface(cr, im->surface, 0.0, 0.0);`
  - `cairo_pattern_set_filter` (function, line 7996) `cairo_pattern_set_filter(cairo_get_source(cr), nearest ? CAIRO_FILTER_NEAREST : CAIRO_FILTER_GOOD);`
  - `cairo_paint` (function, line 7998) `cairo_paint(cr);`
  - `poll` (function, line 8109) `poll(&pfd, 1, 10);`
  - `descriptors` (function, line 8151) `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection — the most common * cause of the "page flashes white and render loops" bug. */ close(p[`
  - `dup2` (function, line 8155) `dup2(p[0], 0);`
  - `execlp` (function, line 8171) `else execlp("aplay", "aplay", "-r", rate_str, "-c", ch_str, "-f", "S16_LE", "-t", "raw", "-q", (char *)NULL);`
  - `_exit` (function, line 8174) `_exit(127);`
  - `kill` (function, line 8197) `kill(w->audio_pid, SIGKILL);`
  - `waitpid` (function, line 8198) `waitpid(w->audio_pid, NULL, 0);`
  - `again` (function, line 8232) `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one fail with "Device * or resource busy"). Death is immediate, so the wait is too. */ kill`
  - `pthread_join` (function, line 8257) `pthread_join(w->video_thread, NULL);`
  - `hls_playlist_free` (function, line 8274) `hls_playlist_free(w->video_pl);`
  - `blocking` (function, line 8519) `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);`
  - `signal` (function, line 8548) `signal(SIGPIPE, SIG_IGN);`
  - `v_write` (function, line 8573) `v_write(w->decoder_cmd_fd, &cmd, 1);`
  - `cairo_fill_preserve` (function, line 8670) `cairo_fill_preserve(cr);`
  - `cairo_new_sub_path` (function, line 8764) `cairo_new_sub_path(cr);`
  - `box_path4` (function, line 8776) `box_path4(cr, x, y, w, h, rc);`
  - `rect` (function, line 8787) `* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops land on the corners. Stops at explicit * 0-1000 positions (pos1000, -1 or NULL = evenly`
  - `cairo_pattern_add_color_stop_rgba` (function, line 8807) `cairo_pattern_add_color_stop_rgba(pat, pos, sc.r, sc.g, sc.b, alpha);`
  - `rgb_from_packed` (function, line 8838) `return rgb_from_packed(cols[nst - 1] >= 0 ? cols[nst - 1] : 0);`
  - `cairo_pattern_set_extend` (function, line 8914) `cairo_pattern_set_extend(ipat, bx->bg_repeat == CSS_BGR_NO_REPEAT ? CAIRO_EXTEND_NONE : CAIRO_EXTEND_REPEAT);`
  - `cairo_set_source` (function, line 8917) `cairo_set_source(cr, ipat);`
  - `cairo_pattern_destroy` (function, line 8919) `cairo_pattern_destroy(ipat);`
  - `cairo_set_source_rgba` (function, line 8962) `cairo_set_source_rgba(cr, sc.r, sc.g, sc.b, 0.30 / (double)steps);`
  - `cairo_set_fill_rule` (function, line 8978) `cairo_set_fill_rule(cr, CAIRO_FILL_RULE_EVEN_ODD);`
  - `bui_paint_conic` (function, line 8998) `bui_paint_conic(cr, x, y, w, h, rad, bx->grad_angle, bx->grad_c, bx->grad_pos, bx->grad_n);`
  - `cairo_pattern_add_color_stop_rgb` (function, line 9010) `cairo_pattern_add_color_stop_rgb(pat, pos, sc.r, sc.g, sc.b);`
  - `layer` (function, line 9039) `* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the border. Same sizing/repeat/position * as the first layer, using the SAME rc_box fields`
  - `cairo_set_line_cap` (function, line 9087) `cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);`
  - `convention` (function, line 9150) `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE || style == CSS_BST_RIDGE || style == CSS_BST_INSET || style == CSS_BST_OUTSET);`
  - `cairo_curve_to` (function, line 9263) `cairo_curve_to(cr, cx + half * 0.5, ly, cx + half * 0.5, cy, cx + half, cy);`
  - `row_owner_block_id` (function, line 9299) `static int row_owner_block_id(const rc_layout *L, const rc_row *r);`
  - `paint_image_row` (function, line 9347) `paint_image_row(cr, w, blk, x - th->image_box_pad, y - th->image_box_pad, f->repl_w + 2.0 * th->image_box_pad, f->repl_h + 2.0 * th->image_box_pad);`
  - `draw_input_row` (function, line 9393) `draw_input_row(cr, w, r->blk, left + r->x_off, cw, ry, r->ascent, r->height);`
  - `bg` (function, line 9406) `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);`
  - `bx_content_clipped` (function, line 9543) `return bx_content_clipped(d->overflow_x, d->overflow_y);`
  - `rows` (function, line 9612) `* RC_IMAGE rows (see its declaration);`
  - `cx_forms_stacking_context` (function, line 9695) `return cx_forms_stacking_context(&st);`
  - `cairo_matrix_init_identity` (function, line 9721) `cairo_matrix_init_identity(m);`
  - `ip_anim_init` (function, line 9747) `ip_anim_init(&a, IP_VAL_SCALAR, &ease, prog_kf, 2, (double)def->anim_duration_ms, delay, iters, dir, fill);`
  - `ip_anim_tick` (function, line 9749) `ip_anim_tick(&a, (double)elapsed_ms);`
  - `cairo_matrix_translate` (function, line 9818) `cairo_matrix_translate(m, tx, ty);`
  - `cairo_matrix_rotate` (function, line 9820) `cairo_matrix_rotate(m, rot);`
  - `cairo_matrix_scale` (function, line 9821) `cairo_matrix_scale(m, sx, sy);`
  - `cairo_matrix_multiply` (function, line 9826) `cairo_matrix_multiply(m, &k, m);`
  - `cairo_user_to_device` (function, line 9989) `cairo_user_to_device(cr, &dx, &dy);`
  - `cairo_destroy` (function, line 10013) `cairo_destroy(scr);`
  - `bui_box_blur_surface` (function, line 10014) `bui_box_blur_surface(snap, radius);`
  - `cairo_identity_matrix` (function, line 10021) `cairo_identity_matrix(cr);`
  - `cairo_clip_extents` (function, line 10052) `cairo_clip_extents(cr, &x1, &y1, &x2, &y2);`
  - `the` (function, line 10184) `* the (already filtered) group with the shadow color, blur it, and * paint it under the group at the declared offset -- the shadow * follows the real content shape (PNG transparency, glyphs), not * th`
  - `cairo_mask_surface` (function, line 10193) `cairo_mask_surface(scr, flt_surf, 0, 0);`
  - `cairo_pop_group_to_source` (function, line 10208) `cairo_pop_group_to_source(cr);`
  - `cairo_set_operator` (function, line 10251) `cairo_set_operator(cr, bui_blend_operator(def ? def->mix_blend : CSS_MB_UNSET));`
  - `cairo_paint_with_alpha` (function, line 10252) `cairo_paint_with_alpha(cr, alpha);`
  - `cairo_push_group` (function, line 10348) `cairo_push_group(cr);`
  - `cairo_transform` (function, line 10350) `cairo_transform(cr, &m);`
  - `fill` (function, line 10360) `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in the caller's separate row pass -- * left ungrouped, it shows as a solid, un-faded re`
  - `ov_reconcile` (function, line 10426) `ov_reconcile(cr, ov_stack, &ov_depth, w->doc, bx->block_id, L, origin, left);`
  - `compositing` (function, line 10452) `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context: opacity<1, mix-blend != normal, isolation:isolate, * transform != none, or the posit`
  - `cairo_show_page` (function, line 10999) `cairo_show_page(cr);`
  - `cairo_image_surface_create` (function, line 11122) `cairo_image_surface_create(CAIRO_FORMAT_ARGB32, (int)PNG_PAGE_W, (int)img_h);`
  - `origin` (function, line 11275) `* top_url is the page origin (https or file://);`
  - `printf` (function, line 11348) `printf("=== Freedom layout ===\n");`
  - `in` (function, line 11353) `* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);`
  - `fb_buffer_free` (function, line 11648) `fb_buffer_free(&w->console);`
  - `unlink` (function, line 11807) `unlink(tmp);`
  - `do_submit_post` (function, line 11978) `do_submit_post(w, &plan);`
  - `presentation` (function, line 12018) `* affect presentation (a repaint, which re-runs layout, suffices);`
  - `ui_layout_free` (function, line 12669) `ui_layout_free(&lay);`
  - `wl_surface_attach` (function, line 12690) `wl_surface_attach(w->surface, w->buffer, 0, 0);`
  - `wl_surface_damage_buffer` (function, line 12691) `wl_surface_damage_buffer(w->surface, 0, 0, w->width, w->height);`
  - `wl_surface_commit` (function, line 12692) `wl_surface_commit(w->surface);`
  - `wl_display_flush` (function, line 12693) `wl_display_flush(w->display);`
  - `xdg_wm_base_pong` (function, line 12700) `xdg_wm_base_pong(b, serial);`
  - `xdg_surface_ack_configure` (function, line 12706) `xdg_surface_ack_configure(s, serial);`
  - `resizes` (function, line 12720) `* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);`
  - `wl_pointer_set_cursor` (function, line 12775) `wl_pointer_set_cursor(w->pointer, w->pointer_serial, w->cursor_surface, (int32_t)img->hotspot_x, (int32_t)img->hotspot_y);`
  - `wl_surface_damage` (function, line 12778) `wl_surface_damage(w->cursor_surface, 0, 0, (int32_t)img->width, (int32_t)img->height);`
  - `xdg_surface_add_listener` (function, line 13186) `xdg_surface_add_listener(fb->xdg_surface, &fbw_xdg_surface_listener, fb);`
  - `xdg_toplevel_add_listener` (function, line 13188) `xdg_toplevel_add_listener(fb->xdg_toplevel, &fbw_toplevel_listener, fb);`
  - `xdg_toplevel_set_title` (function, line 13189) `xdg_toplevel_set_title(fb->xdg_toplevel, "Freebug - Freedom DevTools");`
  - `xdg_toplevel_set_app_id` (function, line 13190) `xdg_toplevel_set_app_id(fb->xdg_toplevel, "org.freedom.freebug");`
  - `zxdg_toplevel_decoration_v1_set_mode` (function, line 13193) `zxdg_toplevel_decoration_v1_set_mode(fb->deco, ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);`
  - `fb_buffer_push` (function, line 13273) `fb_buffer_push(&w->console, FB_ERROR, "Freebug: no live page to evaluate (reload the page first).", 56);`
  - `fb_buffer_push_loc` (function, line 13284) `fb_buffer_push_loc(&w->console, e->level, e->text, e->len, e->file, e->line, e->col);`
  - `tab_eval_result_free` (function, line 13292) `tab_eval_result_free(&r);`
  - `tf_clear` (function, line 13295) `tf_clear(&fb->editor);`
  - `tf_insert` (function, line 13314) `tf_insert(&fb->editor, '\n');`
  - `down` (function, line 13388) `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void dispatch_mouse_event(browser_window *w, dom_node_id node_id, const char *event_type, int `
  - `update_hover` (function, line 13404) `update_hover(w);`
  - `dispatch_mouse_event` (function, line 13409) `dispatch_mouse_event(w, nid, "mouseenter", (int)w->ptr_x, (int)w->ptr_y, 0);`
  - `browser_commit_url_bar` (function, line 13504) `browser_commit_url_bar(&w->bs);`
  - `xdg_toplevel_set_maximized` (function, line 13633) `else xdg_toplevel_set_maximized(w->xdg_toplevel);`
  - `xdg_toplevel_set_minimized` (function, line 13635) `xdg_toplevel_set_minimized(w->xdg_toplevel);`
  - `xdg_toplevel_move` (function, line 13637) `xdg_toplevel_move(w->xdg_toplevel, w->seat, serial);`
  - `submit_form` (function, line 13716) `submit_form(w, ctl);`
  - `dispatch_click` (function, line 13734) `dispatch_click(w, w->ptr_x, w->ptr_y);`
  - `wl_data_offer_add_listener` (function, line 13823) `wl_data_offer_add_listener(offer, &data_offer_listener, w);`
  - `wl_data_source_destroy` (function, line 13871) `wl_data_source_destroy(src);`
  - `wl_data_source_add_listener` (function, line 13943) `wl_data_source_add_listener(w->copy_source, &data_source_listener, w);`
  - `wl_data_source_offer` (function, line 13945) `wl_data_source_offer(w->copy_source, "text/plain");`
  - `wl_data_device_set_selection` (function, line 13946) `wl_data_device_set_selection(w->data_device, w->copy_source, w->last_serial);`
  - `loop` (function, line 13948) `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately might miss it). */ wl_display_roundtrip(w->display);`
  - `browser_url_bar_insert` (function, line 13966) `browser_url_bar_insert(&w->bs, (char)c);`
  - `wl_data_offer_receive` (function, line 13987) `wl_data_offer_receive(w->selection_offer, mime, fds[1]);`
  - `wl_display_roundtrip` (function, line 13990) `wl_display_roundtrip(w->display);`
  - `browser_url_bar_delete_selection` (function, line 14064) `browser_url_bar_delete_selection(&w->bs);`
  - `munmap` (function, line 14085) `munmap(map_str, size);`
  - `tf_set` (function, line 14182) `tf_set(&w->inputs[i].field, value);`
  - `clipboard_paste` (function, line 14248) `clipboard_paste(w);`
  - `clipboard_cut` (function, line 14258) `clipboard_cut(w);`
  - `browser_url_bar_select_all` (function, line 14264) `browser_url_bar_select_all(&w->bs);`
  - `browser_add_exception` (function, line 14274) `browser_add_exception(&w->bs, host);`
  - `tf_backspace` (function, line 14397) `tf_backspace(&w->ua_field);`
  - `tf_delete` (function, line 14399) `tf_delete(&w->ua_field);`
  - `tf_move` (function, line 14401) `tf_move(&w->ua_field, -1);`
  - `tf_home` (function, line 14405) `tf_home(&w->ua_field);`
  - `tf_end` (function, line 14407) `tf_end(&w->ua_field);`
  - `browser_url_bar_backspace` (function, line 14515) `browser_url_bar_backspace(&w->bs);`
  - `browser_url_bar_delete` (function, line 14518) `browser_url_bar_delete(&w->bs);`
  - `browser_url_bar_move_cursor` (function, line 14522) `else browser_url_bar_move_cursor(&w->bs, -1);`
  - `browser_url_bar_set_cursor` (function, line 14527) `browser_url_bar_set_cursor(&w->bs, 0, shift);`
  - `timerfd_settime` (function, line 14568) `timerfd_settime(w->repeat_timer_fd, 0, &its, NULL);`
  - `xkb_state_update_mask` (function, line 14643) `xkb_state_update_mask(w->xkb_state, mods_depressed, mods_latched, mods_locked, 0, 0, group);`
  - `wl_pointer_add_listener` (function, line 14669) `wl_pointer_add_listener(w->pointer, &pointer_listener, w);`
  - `wl_keyboard_add_listener` (function, line 14673) `wl_keyboard_add_listener(w->keyboard, &keyboard_listener, w);`
  - `xdg_wm_base_add_listener` (function, line 14693) `xdg_wm_base_add_listener(w->wm_base, &wm_base_listener, w);`
  - `wl_seat_add_listener` (function, line 14696) `wl_seat_add_listener(w->seat, &seat_listener, w);`
  - `saving` (function, line 14728) `* disables saving (never clobber);`
  - `prefs_init` (function, line 14729) `prefs_init(&w.prefs);`
  - `fc_init` (function, line 14751) `fc_init(&w.fc);`
  - `sf_global_init` (function, line 14769) `sf_global_init();`
  - `fcntl` (function, line 14772) `fcntl(w.fetch_pipe[0], F_SETFL, O_NONBLOCK);`
  - `pthread_mutex_init` (function, line 14778) `pthread_mutex_init(&w.stream_lock, NULL);`
  - `browser_navigate` (function, line 14796) `else browser_navigate(&w.bs, start_url);`
  - `redraws` (function, line 14807) `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A 4 KiB buffer overflows when * accumulated messages exceed that, since manual flushes`
  - `wl_registry_add_listener` (function, line 14817) `wl_registry_add_listener(w.registry, &registry_listener, &w);`
  - `wl_display_disconnect` (function, line 14821) `wl_display_disconnect(w.display);`
  - `xkb_context_unref` (function, line 14823) `xkb_context_unref(w.xkb_ctx);`
  - `wl_data_device_add_listener` (function, line 14831) `wl_data_device_add_listener(w.data_device, &data_device_listener, &w);`
  - `zxdg_toplevel_decoration_v1_add_listener` (function, line 14845) `zxdg_toplevel_decoration_v1_add_listener(w.deco, &deco_listener, &w);`
  - `applies` (function, line 14877) `* persisted choice applies (prefs_parse already clamped it to a valid mode). */ const char *js_env = getenv("FREEDOM_JS");`
  - `wl_display_dispatch_pending` (function, line 14920) `wl_display_dispatch_pending(w.display);`
  - `wl_display_cancel_read` (function, line 14989) `wl_display_cancel_read(w.display);`
  - `flow` (function, line 15067) `* flow (counting them starved aplay). A video frame read while * overdue overwrites the held slot (standard player frame drop);`
  - `pthread_mutex_destroy` (function, line 15144) `pthread_mutex_destroy(&w.stream_lock);`
  - `prefs_free` (function, line 15165) `prefs_free(&w.prefs);`
  - `profile_close` (function, line 15166) `profile_close(&w.profile);`
  - `tsh_shutdown` (function, line 15173) `tsh_shutdown();`
  - `cairo_debug_reset_static_data` (function, line 15174) `cairo_debug_reset_static_data();`
  - `FcFini` (function, line 15175) `FcFini();`
  - `_GNU_SOURCE` (macro, line 11) `#define _GNU_SOURCE`
  - `UI_TOOLBAR_H` (macro, line 80) `#define UI_TOOLBAR_H`
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
  - `RC_MAX_OUT_OF_FLOW` (macro, line 6126) `#define RC_MAX_OUT_OF_FLOW`
  - `RC_DEFER_COLS` (macro, line 6234) `#define RC_DEFER_COLS`
  - `RC_DEFER_RANGES` (macro, line 6235) `#define RC_DEFER_RANGES`
  - `RC_DEFER_BAND_RUNS` (macro, line 6312) `#define RC_DEFER_BAND_RUNS`
  - `BUI_CONIC_SLICES` (macro, line 8840) `#define BUI_CONIC_SLICES`
  - `OV_MAX_DEPTH` (macro, line 9537) `#define OV_MAX_DEPTH`
  - `H2R` (macro, line 10140) `#define H2R(p,q,t)`
  - `PDF_PAGE_W` (macro, line 10889) `#define PDF_PAGE_W`
  - `PDF_PAGE_H` (macro, line 10890) `#define PDF_PAGE_H`
  - `PDF_MARGIN` (macro, line 10891) `#define PDF_MARGIN`
  - `PNG_PAGE_W` (macro, line 11053) `#define PNG_PAGE_W`
  - `PNG_MARGIN` (macro, line 11066) `#define PNG_MARGIN`
  - `PNG_MAX_H` (macro, line 11067) `#define PNG_MAX_H`
  - `FBW_W` (macro, line 12820) `#define FBW_W`
  - `FBW_H` (macro, line 12822) `#define FBW_H`
  - `FBW_HEADER` (macro, line 12823) `#define FBW_HEADER`
  - `FBW_PAD` (macro, line 12824) `#define FBW_PAD`
  - `FBW_LINE` (macro, line 12825) `#define FBW_LINE`
  - `FBW_GUTTER` (macro, line 12826) `#define FBW_GUTTER`
  - `FBW_MIN_SPLIT` (macro, line 12827) `#define FBW_MIN_SPLIT`
  - `FBW_MAX_SPLIT` (macro, line 12828) `#define FBW_MAX_SPLIT`
  - `FBW_COPY_BTN_W` (macro, line 12829) `#define FBW_COPY_BTN_W`
  - `FBW_COPY_BTN_H` (macro, line 12830) `#define FBW_COPY_BTN_H`
- Depends on: `gui/browser_ui_internal.h`, `include/block_flow.h`, `include/box_style.h`, `include/box_tree.h`, `include/browser.h`, `include/compositor.h`, `include/css.h`, `include/css_color.h`, `include/data_url.h`, `include/download.h`, `include/form.h`, `include/frame_clock.h`, `include/freebug.h`, `include/hls.h`, `include/hostblock.h`, `include/hostedit.h`, `include/image_decode.h`, `include/interp.h`, `include/js_policy.h`, `include/link_nav.h`, `include/media_decoder.h`, `include/net_realm.h`, `include/pdf_export.h`, `include/prefetch.h`, `include/prefs.h`, `include/profile.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/svg_paint.h`, `include/svg_render.h`, `include/tab.h`, `include/text_shape.h`, `include/textfield.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/webcaps.h`, `include/zoom.h`

## gui/browser_ui_internal.h
- Layer: presentation
- Doc: ifndef FREEDOM_BROWSER_UI_INTERNAL_H define FREEDOM_BROWSER_UI_INTERNAL_H  ifdef __cplusplus error "Freedom is pure C (C
- Language: h
- Symbols:
  - `ui_rgb` (struct, line 39)
  - `ui_theme` (struct, line 41)
  - `ui_theme_mode` (enum, line 91)
  - `b` (type_alias, line 38) `typedef struct ui_rgb { double r, g, b;`
  - `body_font` (type_alias, line 40) `typedef struct ui_theme { double body_font;`
  - `ui_theme_default` (function, line 98) `ui_theme ui_theme_default(void);`
  - `ui_theme_dark` (function, line 100) `ui_theme ui_theme_dark(void);`
  - `ui_theme_sepia` (function, line 101) `ui_theme ui_theme_sepia(void);`
  - `ui_theme_for` (function, line 102) `ui_theme ui_theme_for(int mode);`
  - `rgb_from_packed` (function, line 103) `ui_rgb rgb_from_packed(int packed);`
  - `set_rgb` (function, line 104) `void set_rgb(cairo_t *cr, ui_rgb c);`
  - `FREEDOM_BROWSER_UI_INTERNAL_H` (macro, line 2) `#define FREEDOM_BROWSER_UI_INTERNAL_H`
  - `UI_FONT_SIZE` (macro, line 28) `#define UI_FONT_SIZE`
  - `UI_TEXT_MARGIN` (macro, line 29) `#define UI_TEXT_MARGIN`
  - `UI_HEADING_LEVELS` (macro, line 30) `#define UI_HEADING_LEVELS`
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
  - `set_rgb` (function, line 184) `void set_rgb(cairo_t *cr, ui_rgb c)`
  - `cairo_set_source_rgb` (function, line 186) `cairo_set_source_rgb(cr, c.r, c.g, c.b);`
- Depends on: `gui/browser_ui_internal.h`, `include/css_color.h`

## gui/freedom_view.c
- Layer: presentation
- Language: c
- Symbols:
  - `main` (function, line 36) `int main(int argc, char **argv)`
  - `rewind` (function, line 26) `rewind(f);`
  - `fclose` (function, line 31) `fclose(f);`
  - `fprintf` (function, line 39) `fprintf(stderr, "usage: %s <file.html>\n", argv[0]);`
  - `free` (function, line 52) `free(html);`
  - `hp_document_free` (function, line 61) `hp_document_free(doc);`
  - `hp_free` (function, line 67) `hp_free(title);`
  - `_POSIX_C_SOURCE` (macro, line 9) `#define _POSIX_C_SOURCE`
- Depends on: `include/html_parse.h`, `include/ui.h`

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
  - `cairo_rectangle` (function, line 41) `cairo_rectangle(cr, x, y, w, h);`
  - `cairo_new_sub_path` (function, line 48) `cairo_new_sub_path(cr);`
  - `cairo_save` (function, line 49) `cairo_save(cr);`
  - `cairo_translate` (function, line 50) `cairo_translate(cr, x + rx, y + ry);`
  - `cairo_scale` (function, line 51) `cairo_scale(cr, rx, ry);`
  - `cairo_arc` (function, line 52) `cairo_arc(cr, 0.0, 0.0, 1.0, PI, 1.5 * PI);`
  - `cairo_restore` (function, line 53) `cairo_restore(cr);`
  - `cairo_close_path` (function, line 69) `cairo_close_path(cr);`
  - `cairo_move_to` (function, line 90) `case SV_LINE: cairo_move_to(cr, sh->a, sh->b);`
  - `cairo_line_to` (function, line 92) `cairo_line_to(cr, sh->c, sh->d);`
  - `cairo_curve_to` (function, line 112) `case SV_CUBIC: cairo_curve_to(cr, sg->x[0], sg->y[0], sg->x[1], sg->y[1], sg->x[2], sg->y[2]);`
  - `cairo_set_source_rgba` (function, line 129) `cairo_set_source_rgba(cr, r, g, b, svp_alpha(sh->opacity, sh->fill_opacity));`
  - `cairo_select_font_face` (function, line 130) `cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);`
  - `cairo_set_font_size` (function, line 131) `cairo_set_font_size(cr, (sh->c > 0.0) ? sh->c : 16.0);`
  - `cairo_show_text` (function, line 133) `cairo_show_text(cr, sh->text);`
  - `cairo_new_path` (function, line 134) `cairo_new_path(cr);`
  - `sv_fit` (function, line 143) `sv_fit(img, w, h, &scale, &off_x, &off_y);`
  - `cairo_clip` (function, line 149) `cairo_clip(cr);`
  - `cairo_matrix_init` (function, line 158) `cairo_matrix_init(&m, sh->m[0], sh->m[1], sh->m[2], sh->m[3], sh->m[4], sh->m[5]);`
  - `cairo_transform` (function, line 159) `cairo_transform(cr, &m);`
  - `cairo_set_fill_rule` (function, line 173) `cairo_set_fill_rule(cr, sh->fill_even_odd ? CAIRO_FILL_RULE_EVEN_ODD : CAIRO_FILL_RULE_WINDING);`
  - `cairo_fill_preserve` (function, line 175) `cairo_fill_preserve(cr);`
  - `cairo_set_line_width` (function, line 179) `cairo_set_line_width(cr, sh->stroke_w);`
  - `cairo_set_line_cap` (function, line 180) `cairo_set_line_cap(cr, (sh->linecap == 1) ? CAIRO_LINE_CAP_ROUND : (sh->linecap == 2) ? CAIRO_LINE_CAP_SQUARE : CAIRO_LINE_CAP_BUTT);`
  - `cairo_set_line_join` (function, line 183) `cairo_set_line_join(cr, (sh->linejoin == 1) ? CAIRO_LINE_JOIN_ROUND : (sh->linejoin == 2) ? CAIRO_LINE_JOIN_BEVEL : CAIRO_LINE_JOIN_MITER);`
  - `cairo_stroke` (function, line 186) `cairo_stroke(cr);`
- Depends on: `include/css_color.h`, `include/svg_paint.h`

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
  - `wl_shm_pool_destroy` (function, line 143) `wl_shm_pool_destroy(pool);`
  - `close` (function, line 144) `close(fd);`
  - `wl_buffer_add_listener` (function, line 146) `wl_buffer_add_listener(w->buffer, &buffer_listener, w);`
  - `cairo_set_source_rgb` (function, line 159) `cairo_set_source_rgb(cr, 1, 1, 1);`
  - `cairo_paint` (function, line 161) `cairo_paint(cr);`
  - `cairo_select_font_face` (function, line 162) `cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);`
  - `cairo_set_font_size` (function, line 165) `cairo_set_font_size(cr, UI_FONT_SIZE);`
  - `cairo_font_extents` (function, line 168) `cairo_font_extents(cr, &fe);`
  - `cairo_text_extents` (function, line 170) `cairo_text_extents(cr, "M", &te);`
  - `cairo_rectangle` (function, line 181) `cairo_rectangle(cr, 0, 0, w->width, UI_TITLEBAR_H);`
  - `cairo_fill` (function, line 182) `cairo_fill(cr);`
  - `cairo_move_to` (function, line 185) `cairo_move_to(cr, UI_MARGIN, bl);`
  - `cairo_show_text` (function, line 186) `cairo_show_text(cr, (w->title != NULL) ? w->title : "Freedom");`
  - `cairo_destroy` (function, line 208) `cairo_destroy(cr);`
  - `fprintf` (function, line 213) `fprintf(stderr, "[ui] paint csd=%d cols=%zu viewport=%zu total_lines=%zu scroll=%zu\n", w->use_csd, max_cols, viewport_lines, lay.count, w->scroll);`
  - `memcpy` (function, line 228) `memcpy(linebuf, w->text + lay.lines[idx].offset, n);`
  - `free` (function, line 235) `free(linebuf);`
  - `ui_layout_free` (function, line 237) `ui_layout_free(&lay);`
  - `cairo_surface_flush` (function, line 239) `cairo_surface_flush(w->cairo_surface);`
  - `wl_surface_attach` (function, line 251) `wl_surface_attach(w->surface, w->buffer, 0, 0);`
  - `wl_surface_damage_buffer` (function, line 252) `wl_surface_damage_buffer(w->surface, 0, 0, w->width, w->height);`
  - `wl_surface_commit` (function, line 253) `wl_surface_commit(w->surface);`
  - `xdg_wm_base_pong` (function, line 260) `xdg_wm_base_pong(b, serial);`
  - `xdg_surface_ack_configure` (function, line 266) `xdg_surface_ack_configure(s, serial);`
  - `xdg_toplevel_set_maximized` (function, line 334) `else xdg_toplevel_set_maximized(w->xdg_toplevel);`
  - `xdg_toplevel_set_minimized` (function, line 337) `xdg_toplevel_set_minimized(w->xdg_toplevel);`
  - `xdg_toplevel_move` (function, line 339) `xdg_toplevel_move(w->xdg_toplevel, w->seat, serial);`
  - `wl_pointer_add_listener` (function, line 371) `wl_pointer_add_listener(w->pointer, &pointer_listener, w);`
  - `xdg_wm_base_add_listener` (function, line 391) `xdg_wm_base_add_listener(w->wm_base, &wm_base_listener, w);`
  - `wl_seat_add_listener` (function, line 394) `wl_seat_add_listener(w->seat, &seat_listener, w);`
  - `memset` (function, line 412) `memset(&w, 0, sizeof w);`
  - `wl_registry_add_listener` (function, line 424) `wl_registry_add_listener(w.registry, &registry_listener, &w);`
  - `wl_display_roundtrip` (function, line 425) `wl_display_roundtrip(w.display);`
  - `wl_display_disconnect` (function, line 432) `wl_display_disconnect(w.display);`
  - `xdg_surface_add_listener` (function, line 438) `xdg_surface_add_listener(w.xdg_surface, &xdg_surface_listener, &w);`
  - `xdg_toplevel_add_listener` (function, line 440) `xdg_toplevel_add_listener(w.xdg_toplevel, &toplevel_listener, &w);`
  - `xdg_toplevel_set_title` (function, line 441) `xdg_toplevel_set_title(w.xdg_toplevel, w.title);`
  - `xdg_toplevel_set_app_id` (function, line 442) `xdg_toplevel_set_app_id(w.xdg_toplevel, "org.freedom.browser");`
  - `zxdg_toplevel_decoration_v1_add_listener` (function, line 449) `zxdg_toplevel_decoration_v1_add_listener(w.deco, &deco_listener, &w);`
  - `zxdg_toplevel_decoration_v1_set_mode` (function, line 450) `zxdg_toplevel_decoration_v1_set_mode(w.deco, ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);`
  - `_GNU_SOURCE` (macro, line 9) `#define _GNU_SOURCE`
  - `UI_FONT_SIZE` (macro, line 25) `#define UI_FONT_SIZE`
  - `UI_MARGIN` (macro, line 27) `#define UI_MARGIN`
  - `UI_TITLEBAR_H` (macro, line 28) `#define UI_TITLEBAR_H`
  - `UI_BTN_W` (macro, line 29) `#define UI_BTN_W`
  - `UI_BTN_LEFT` (macro, line 30) `#define UI_BTN_LEFT`
- Depends on: `include/ui.h`
