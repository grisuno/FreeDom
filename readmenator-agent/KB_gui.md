# Subsystem: gui (page 1 of 2)
Pages: [KB_gui.md](KB_gui.md), [KB_gui_p2.md](KB_gui_p2.md)

## gui/browser_ui.c
- Doc: ui_input_state: Live editable state for one form text control, aliasing a block of the current...
- Layer: presentation
- Language: c
- Symbols:
  - `ui_menu_item` (struct, line 179)
  - `ui_input_state` (struct, line 217)
  - `ui_image` (struct, line 241)
  - `ui_bg_image` (struct, line 254)
  - `tab_ctx` (struct, line 271)
  - `browser_window` (struct, line 287)
  - `fetch_prep` (struct, line 1664)
  - `fetch_job` (struct, line 1745)
  - `rc_frag` (struct, line 3080)
  - `rc_row` (struct, line 3143)
  - `rc_box` (struct, line 3162)
  - `rc_oof_sub` (struct, line 3213)
  - `rc_layout` (struct, line 3215)
  - `rc_oof_sub` (struct, line 3253)
  - `rc_open_box` (struct, line 3263)
  - `rc_state` (struct, line 3321)
  - `rc_ext` (struct, line 3912)
  - `item_sides` (struct, line 4759)
  - `rc_defer_col` (struct, line 6826)
  - `rc_defer` (struct, line 6833)
  - `freebug_window` (struct, line 14084)
  - `ui_menu_action` (enum, line 162)
  - `ui_hot` (enum, line 210)
  - `rc_rowkind` (enum, line 3141)
  - `bs` (type_alias, line 271) `typedef struct tab_ctx { browser_state bs;`
  - `freebug_window` (type_alias, line 559) `typedef struct freebug_window freebug_window;`
  - `allowlisted` (type_alias, line 1664) `typedef struct fetch_prep { int allowlisted;`
  - `font_size` (type_alias, line 3079) `typedef struct rc_frag { double x, width, font_size;`
  - `kind` (type_alias, line 3142) `typedef struct rc_row { rc_rowkind kind;`
  - `h` (type_alias, line 3162) `typedef struct rc_box { double x, top, w, h;`
  - `block_id` (type_alias, line 3263) `typedef struct rc_open_box { int block_id;`
  - `line_desc` (type_alias, line 3320) `typedef struct rc_state { double cur_top, pending_gap, pen_x, line_asc, line_desc;`
  - `family` (type_alias, line 3912) `typedef struct rc_ext { int family;`
  - `mr` (type_alias, line 4759) `typedef struct item_sides { double ml, mr;`
  - `key` (type_alias, line 6826) `typedef struct rc_defer_col { int key;`
  - `col` (type_alias, line 6833) `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];`
  - `now_ms` (function, line 150) `static uint64_t now_ms(void)`
  - `gutter` (function, line 578) `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
  - `apply_zoom` (function, line 599) `static void apply_zoom(browser_window *w)`
  - `buffer_release` (function, line 610) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 616) `static void destroy_buffer(browser_window *w)`
  - `ensure_buffer` (function, line 622) `static int ensure_buffer(browser_window *w)`
  - `read_file` (function, line 652) `static char *read_file(const char *path, size_t *out_len)`
  - `build_file_origin` (function, line 691) `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)`
  - `load_host_file` (function, line 701) `static void load_host_file(hb_set *s, const char *dir, const char *name, hb_list list)`
  - `build_host_filter` (function, line 718) `static hb_set *build_host_filter(void)`
  - `build_js_filter` (function, line 765) `static hb_set *build_js_filter(void)`
  - `build_impersonate_optin` (function, line 768) `static int build_impersonate_optin(void)`
  - `freedom_write_dir` (function, line 777) `static int freedom_write_dir(char *out, size_t cap)`
  - `add_current_host_to_list` (function, line 802) `static void add_current_host_to_list(browser_window *w, int sel)`
  - `load_favorites` (function, line 870) `static void load_favorites(browser_window *w)`
  - `omni_refresh` (function, line 916) `static void omni_refresh(browser_window *w)`
  - `profile_sync` (function, line 947) `static void profile_sync(browser_window *w)`
  - `remember_visit` (function, line 964) `static void remember_visit(browser_window *w, const char *url)`
  - `bookmark_toggle_current` (function, line 972) `static void bookmark_toggle_current(browser_window *w)`
  - `proxy_addr_from_env` (function, line 996) `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...`
  - `init_net_config` (function, line 1010) `static void init_net_config(browser_window *w)`
  - `is_https_url` (function, line 1020) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 1024) `static int is_http_url(const char *s)`
  - `host_from_url` (function, line 1035) `static int host_from_url(const char *url, char *out, size_t outsz)`
  - `toggle_fullscreen` (function, line 1067) `static void toggle_fullscreen(browser_window *w)`
  - `input_is_interactive` (function, line 1082) `static int input_is_interactive(int input_type)`
  - `input_is_editable` (function, line 1088) `static int input_is_editable(int input_type)`
  - `free_inputs` (function, line 1094) `static void free_inputs(browser_window *w)`
  - `free_images` (function, line 1102) `static void free_images(browser_window *w)`
  - `find_bg_image` (function, line 1141) `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)`
  - `layout` (function, line 1153) `* shared by layout (row height) and paint (blit), so they cannot drift apart. */
static int image...`
  - `rebuild_inputs` (function, line 1213) `static void rebuild_inputs(browser_window *w)`
  - `find_input_state` (function, line 1238) `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)`
  - `clear_doc` (function, line 1246) `static void clear_doc(browser_window *w)`
  - `set_cache` (function, line 1256) `static void set_cache(browser_window *w, char *html, size_t len, const char *top)`
  - `surface_from_pixels` (function, line 1267) `static cairo_surface_t *surface_from_pixels(const tab_image *img)`
  - `fetch_follow_navigable` (function, line 1334) `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...`
  - `GET` (function, line 1370) `* a GET (Zero Trust). cfg->policy is restored before returning. */
static sf_status fetch_post_na...`
  - `gui_subresource_fetch` (function, line 1411) `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...`
  - `gui_css_sink` (function, line 1495) `static void gui_css_sink(void *vctx, const char *url,
                         const char *body, ...`
  - `first` (function, line 1563) `* Navigation: clear the registry first (faces are per document). Untrusted:
 * no-op (fetch NULL)...`
  - `prepare_fetch` (function, line 1673) `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...`
  - `fetch_job_free` (function, line 1777) `static void fetch_job_free(fetch_job *j)`
  - `stream_progress_cb` (function, line 1797) `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)`
  - `fetch_thread` (function, line 1821) `static void *fetch_thread(void *arg)`
  - `fetch_launch` (function, line 1869) `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...`
  - `load_images` (function, line 1990) `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
  - `load_bg_images` (function, line 2074) `static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
  - `page_js_host_allowlisted` (function, line 2137) `static int page_js_host_allowlisted(const browser_window *w)`
  - `compute_page_js` (function, line 2143) `static int compute_page_js(const browser_window *w)`
  - `seed_session_cookies` (function, line 2157) `static void seed_session_cookies(tab *t, int trusted, const char *url)`
  - `seed_local_storage` (function, line 2181) `static void seed_local_storage(browser_window *w, tab *t, int trusted)`
  - `collect_local_storage` (function, line 2196) `static void collect_local_storage(browser_window *w, const tab_page *page)`
  - `foldback_session_cookies` (function, line 2206) `static void foldback_session_cookies(const char *url, const char *jar)`
  - `drop_repl_worker` (function, line 2232) `static void drop_repl_worker(browser_window *w)`
  - `schedule_js_tick` (function, line 2246) `static void schedule_js_tick(browser_window *w, int next_ms)`
  - `render_current_ex` (function, line 2256) `static void render_current_ex(browser_window *w, int allow_js_nav)`
  - `render_current` (function, line 2446) `static void render_current(browser_window *w)`
  - `show_busy` (function, line 2453) `static void show_busy(browser_window *w)`
  - `show_fetch_error` (function, line 2462) `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...`
  - `arrives` (function, line 2513) `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...`
  - `strcmp` (function, line 2581) `&& strcmp(auth_host_buf, w->auth_host) != 0)`
  - `tab_save` (function, line 2642) `static void tab_save(browser_window *w)`
  - `tab_restore` (function, line 2659) `static void tab_restore(browser_window *w)`
  - `free_live_page` (function, line 2676) `static void free_live_page(browser_window *w)`
  - `tab_ctx_release` (function, line 2687) `static void tab_ctx_release(tab_ctx *c)`
  - `tab_switch` (function, line 2711) `static void tab_switch(browser_window *w, int idx)`
  - `uitab_close` (function, line 2771) `static void uitab_close(browser_window *w, int idx)`
  - `newtab_x` (function, line 2813) `static double newtab_x(const browser_window *w)`
  - `tab_title` (function, line 2820) `static const char *tab_title(const browser_window *w, int i)`
  - `tabbar_top` (function, line 2836) `static double tabbar_top(const browser_window *w)`
  - `toolbar_top` (function, line 2842) `static double toolbar_top(const browser_window *w)`
  - `content_geometry` (function, line 2849) `static void content_geometry(const browser_window *w, double *top, double *height)`
  - `content_width` (function, line 2876) `static double content_width(const browser_window *w)`
  - `html_center_offset` (function, line 2886) `static double html_center_offset(const browser_window *w)`
  - `scrollbar_metrics` (function, line 2900) `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...`
  - `scrollbar_drag_to` (function, line 2928) `static void scrollbar_drag_to(browser_window *w)`
  - `draw_scrollbar` (function, line 2945) `static void draw_scrollbar(cairo_t *cr, const browser_window *w)`
  - `window_button_rects` (function, line 2982) `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...`
  - `toolbar_rects` (function, line 2992) `static void toolbar_rects(const browser_window *w,
                          double *back_x, doub...`
  - `toolbar_button_at` (function, line 3007) `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)`
  - `hot_actionable` (function, line 3023) `static int hot_actionable(const browser_window *w, ui_hot hot)`
  - `menu_panel_rect` (function, line 3034) `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...`
  - `ua_box_rect` (function, line 3050) `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...`
  - `draw_text` (function, line 3060) `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)`
  - `rc_float_bottom` (function, line 3415) `static double rc_float_bottom(const rc_state *s)`
  - `rc_float_clear` (function, line 3424) `static void rc_float_clear(rc_state *s)`
  - `rc_float_refresh` (function, line 3437) `static void rc_float_refresh(rc_state *s, double line_h)`
  - `rc_float_fit_line` (function, line 3483) `static void rc_float_fit_line(rc_state *s, double line_h)`
  - `line_limit` (function, line 3502) `static double line_limit(const rc_state *s, double content_w)`
  - `rc_free` (function, line 3507) `static void rc_free(rc_layout *L)`
  - `rc_add_box` (function, line 3527) `static rc_box *rc_add_box(rc_layout *L)`
  - `rc_add_frag` (function, line 3539) `static rc_frag *rc_add_frag(rc_layout *L)`
  - `rc_add_row` (function, line 3554) `static rc_row *rc_add_row(rc_layout *L)`
  - `family_face` (function, line 3566) `static const char *family_face(int family)`
  - `content_font` (function, line 3588) `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,
            ...`
  - `set_rgb_alpha` (function, line 3603) `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)`
  - `utf8_clen` (function, line 3612) `static size_t utf8_clen(const char *s, size_t n)`
  - `draw_slice` (function, line 3652) `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)`
  - `frag_styled` (function, line 3665) `static int frag_styled(const rc_frag *f)`
  - `styled_advance` (function, line 3672) `static double styled_advance(cairo_t *cr, const rc_frag *f)`
  - `styled_draw` (function, line 3688) `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)`
  - `block_style` (function, line 3705) `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
  - `block_margins` (function, line 3732) `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...`
  - `add` (function, line 3762) `* about to add (top/h passed in). A box that survived a line wrap simply ends at the
 * wrap -- m...`
  - `run` (function, line 3797) `* continuation run (block_id < 0 with no block break) deliberately skips reconcile
 * to stay on ...`
  - `flush_line` (function, line 3822) `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `open_line_height` (function, line 3880) `static double open_line_height(const rc_state *s, const ui_theme *th)`
  - `open_line` (function, line 3893) `static void open_line(rc_layout *L, rc_state *s)`
  - `flow_emit_frag` (function, line 3944) `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...`
  - `flow_text` (function, line 4012) `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...`
  - `replaced_inline_size` (function, line 4264) `static int replaced_inline_size(const browser_window *w, const rd_block *b,
                     ...`
  - `replaced_is_inline_level` (function, line 4294) `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)`
  - `inlines` (function, line 4307) `* next run may also be a replaced element without its own break: consecutive
 * atomic inlines (`...`
  - `place_inline_replaced` (function, line 4342) `static int place_inline_replaced(rc_layout *L, rc_state *s, const ui_theme *th,
                 ...`
  - `css_replaced_box` (function, line 4398) `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...`
  - `emit_replaced_row` (function, line 4407) `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `flow_text_block` (function, line 4510) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
  - `item_root_box_in` (function, line 4623) `static int item_root_box_in(const rd_doc *doc, size_t b0, size_t b1, int cbox)`
  - `item_root_box` (function, line 4670) `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)`
  - `css_align_to_bt` (function, line 4679) `static int css_align_to_bt(int align_kw)`
  - `box_edge_px` (function, line 4689) `static double box_edge_px(int wpx)`
  - `rc_box_copy_decoration` (function, line 4709) `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)`
  - `box_is_strict_descendant` (function, line 4788) `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)`
  - `item_sides_at_level` (function, line 4810) `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,
                  ...`
  - `container_box_of` (function, line 4839) `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)`
  - `table` (function, line 4861) `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...`
  - `row` (function, line 4921) `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...`
  - `measure_item_w_at` (function, line 4965) `static double measure_item_w_at(cairo_t *cr, const browser_window *w,
                           ...`
  - `measure_item_content_w` (function, line 5009) `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
  - `run_width_cap` (function, line 5042) `static double run_width_cap(const rd_block *b, double avail_w)`
  - `def_width_cap` (function, line 5046) `static double def_width_cap(const pv_box_def *d, double avail_w)`
  - `def_declared_width` (function, line 5052) `static double def_declared_width(const pv_box_def *d, double avail_w)`
  - `item_declared_basis` (function, line 5057) `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
  - `nested_cont_basis` (function, line 5071) `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...`
  - `flex_item_basis` (function, line 5113) `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
  - `flex_item_min_main` (function, line 5152) `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...`
  - `item_at_level` (function, line 5187) `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `child_cont_at_level` (function, line 5202) `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `root_cont_of` (function, line 5217) `static int root_cont_of(const rd_doc *doc, int cid)`
  - `block_is_oof` (function, line 5254) `static int block_is_oof(const rd_doc *doc, const rd_block *bk)`
  - `item_vmargins` (function, line 5296) `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,
          ...`
  - `layout_container` (function, line 5311) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `slot` (function, line 5504) `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
  - `path` (function, line 5634) `*
         * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when
        ...`
  - `box_line_visible` (function, line 6062) `static int box_line_visible(int style)`
  - `close_top_box` (function, line 6068) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `rc_box_context` (function, line 6205) `static void rc_box_context(const rc_state *s, double content_w,
                           double...`
  - `box_margin_top` (function, line 6232) `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `box_margin_bottom` (function, line 6239) `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `children` (function, line 6249) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
  - `column` (function, line 6457) `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
  - `box_path_has` (function, line 6551) `static int box_path_has(const rd_doc *doc, int block_id, int want)`
  - `columns` (function, line 6565) `* each card made 1080px columns (huggingface, github). */
static int deepest_open_on_path(const r...`
  - `nested_stop` (function, line 6579) `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)`
  - `box_shrink_width` (function, line 6591) `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...`
  - `reconcile_boxes_below` (function, line 6600) `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
  - `treatment` (function, line 6651) `* block treatment (shrink-wrapped and placed by text-align), which is what a
         * standalon...`
  - `reconcile_boxes` (function, line 6682) `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
  - `box_path_of` (function, line 6710) `static int box_path_of(const rd_doc *doc, int block_id, int *out)`
  - `band_common_box` (function, line 6726) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)`
  - `block_in_table_caption` (function, line 6790) `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)`
  - `defer_key_block` (function, line 6854) `static int defer_key_block(const rd_block *bk)`
  - `defer_append` (function, line 6977) `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...`
  - `defer_flush` (function, line 7011) `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...`
  - `layout_float_band` (function, line 7232) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
  - `thumbnail` (function, line 7315) `* is what made a wikipedia thumbnail (a 250px image and its caption, no
     * declared width) sp...`
  - `yet` (function, line 7597) `* does not carry yet (WPT flex-abspos-staticpos-*). */
static int runs_share_float(const rd_doc *...`
  - `layout_doc` (function, line 7609) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
  - `count` (function, line 8001) `* the box count (a hostile parent cycle terminates). */
static int oof_depth(const rd_doc *doc, s...`
  - `approximation` (function, line 8020) `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */
static void oof_s...`
  - `position_doc` (function, line 8209) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
  - `input_box_width` (function, line 8376) `static double input_box_width(double content_w)`
  - `select_box_width` (function, line 8380) `static double select_box_width(double content_w)`
  - `button_box_width` (function, line 8385) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...`
  - `blit_image_box` (function, line 8795) `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,
                 ...`
  - `v_read` (function, line 8978) `static int v_read(int fd, void *buf, size_t n)`
  - `dies` (function, line 9006) `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
  - `audio_spawn` (function, line 9015) `static void audio_spawn(browser_window *w, int rate, int channels)`
  - `audio_mark_dead` (function, line 9069) `static void audio_mark_dead(browser_window *w)`
  - `audio_write` (function, line 9086) `static void audio_write(browser_window *w, const uint8_t *data, size_t len)`
  - `audio_stop` (function, line 9101) `static void audio_stop(browser_window *w)`
  - `video_stop` (function, line 9121) `static void video_stop(browser_window *w)`
  - `video_fetch` (function, line 9299) `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...`
  - `video_play` (function, line 9316) `static int video_play(browser_window *w, const char *m3u8_url)`
  - `video_stop` (function, line 9418) `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
  - `paint_video_row` (function, line 9472) `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
  - `row_line_slack` (function, line 9584) `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)`
  - `row_align_offset` (function, line 9596) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)`
  - `upstream` (function, line 9624) `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
  - `box_path` (function, line 9652) `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `text` (function, line 9671) `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
  - `grad_stop` (function, line 9698) `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)`
  - `bui_grad_color_at` (function, line 9713) `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...`
  - `spaced` (function, line 9746) `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
  - `paint_bg_layer` (function, line 9779) `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...`
  - `paint_box_decoration` (function, line 9823) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
  - `cairo_set_dash` (function, line 9990) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 9993) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 10033) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 10036) `cairo_set_dash(cr, (double[])`
  - `set_rgb` (function, line 10070) `set_rgb(cr, (ui_rgb)`
  - `cairo_set_dash` (function, line 10094) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 10097) `cairo_set_dash(cr, (double[])`
  - `paint_deco_line` (function, line 10155) `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...`
  - `cairo_set_dash` (function, line 10189) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 10191) `cairo_set_dash(cr, (double[])`
  - `paint_svg_at` (function, line 10211) `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...`
  - `replaced_current_color` (function, line 10231) `static int replaced_current_color(const browser_window *w, const rd_block *blk)`
  - `paint_inline_replaced` (function, line 10240) `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...`
  - `paint_content_row` (function, line 10257) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
  - `ov_box_clips` (function, line 10445) `static int ov_box_clips(const pv_box_def *d)`
  - `ov_collect_chain` (function, line 10452) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)`
  - `ov_box_bounds` (function, line 10473) `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)`
  - `ov_content_rect` (function, line 10497) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...`
  - `fragment` (function, line 10517) `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
  - `box_forms_stacking_context` (function, line 10572) `static int box_forms_stacking_context(const pv_box_def *def)`
  - `bui_skew_tan` (function, line 10615) `static double bui_skew_tan(int deg)`
  - `box_transform_matrix` (function, line 10622) `static void box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
             ...`
  - `bui_blend_operator` (function, line 10740) `static cairo_operator_t bui_blend_operator(int mix_blend)`
  - `bui_paint_backdrop_blur` (function, line 10878) `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...`
  - `bui_pop_group_composite` (function, line 10936) `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms)`
  - `limits` (function, line 11166) `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
  - `paint_box_decoration_grouped` (function, line 11235) `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
  - `paint_box_and_direct_rows` (function, line 11275) `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...`
  - `paint_oof_sub` (function, line 11374) `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,
                ...`
  - `paint_positioned_one` (function, line 11412) `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...`
  - `box` (function, line 11520) `* content belongs to that box (painted by its own positioned entry). */
    if (sub == NULL)`
  - `paint_nested_children` (function, line 11626) `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...`
  - `geom_from_layout` (function, line 11663) `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,
                ...`
  - `publish_geometry` (function, line 11694) `static void publish_geometry(browser_window *w, const rc_layout *L, double left,
                ...`
  - `paint_structured` (function, line 11716) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
  - `write_doc_pdf` (function, line 11934) `static long write_doc_pdf(browser_window *w, const char *path)`
  - `export_pdf` (function, line 12040) `static void export_pdf(browser_window *w)`
  - `write_doc_png` (function, line 12103) `static long write_doc_png(browser_window *w, const char *path)`
  - `export_png` (function, line 12227) `static void export_png(browser_window *w)`
  - `caller` (function, line 12261) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
  - `ui_render_png` (function, line 12284) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)`
  - `render_doc_images` (function, line 12344) `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...`
  - `ui_render_png_images` (function, line 12375) `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_pdf_images` (function, line 12381) `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_dump_layout` (function, line 12396) `ui_status ui_dump_layout(const rd_doc *doc)`
  - `link_at_point` (function, line 12468) `static const char *link_at_point(browser_window *w, double px, double py)`
  - `resolve_box_cursor` (function, line 12561) `static int resolve_box_cursor(const rd_doc *doc, int block_id)`
  - `box_pointer_events_none` (function, line 12575) `static int box_pointer_events_none(const rd_doc *doc, int block_id)`
  - `cursor_at_point` (function, line 12591) `static int cursor_at_point(browser_window *w, double px, double py)`
  - `node_at_point` (function, line 12657) `static dom_node_id node_at_point(browser_window *w, double px, double py)`
  - `Firefox` (function, line 12665) `* on its face does in Firefox (spec/page_view.md, tanda 40). */
static const rd_block *submit_pro...`
  - `frag_at_point` (function, line 12684) `static dom_node_id frag_at_point(browser_window *w, double px, double py,
                       ...`
  - `reference` (function, line 12738) `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
  - `set_page_url` (function, line 12757) `static void set_page_url(browser_window *w, const char *url)`
  - `ws_apply_ops` (function, line 12782) `static void ws_apply_ops(browser_window *w, const tab_page *page)`
  - `apply_history_ops` (function, line 12817) `static void apply_history_ops(browser_window *w, const tab_page *page)`
  - `history_step` (function, line 12829) `static void history_step(browser_window *w, int steps)`
  - `apply_click_result` (function, line 12862) `static int apply_click_result(browser_window *w, tab_page *page)`
  - `memory` (function, line 12912) `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
  - `GET` (function, line 12995) `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
  - `ensure_download_dir` (function, line 13029) `static int ensure_download_dir(char *out, size_t outsz)`
  - `write_file_atomic` (function, line 13044) `static int write_file_atomic(const char *path, const void *bytes, size_t len)`
  - `save_download` (function, line 13066) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...`
  - `save_current_page` (function, line 13099) `static void save_current_page(browser_window *w)`
  - `deliver_fetch_result` (function, line 13109) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
  - `drain_fetch_results` (function, line 13163) `static void drain_fetch_results(browser_window *w)`
  - `toggle_reader` (function, line 13239) `static void toggle_reader(browser_window *w)`
  - `menu_item_checked` (function, line 13250) `static int menu_item_checked(const browser_window *w, size_t i)`
  - `menu_item_toggle` (function, line 13272) `static void menu_item_toggle(browser_window *w, size_t i)`
  - `draw_clock` (function, line 13382) `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...`
  - `draw_hamburger` (function, line 13394) `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_reload` (function, line 13410) `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_menu` (function, line 13432) `static void draw_menu(cairo_t *cr, browser_window *w)`
  - `draw_hover_url` (function, line 13543) `static double draw_hover_url(cairo_t *cr, browser_window *w)`
  - `draw_toast` (function, line 13575) `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)`
  - `draw_tabstrip` (function, line 13605) `static void draw_tabstrip(cairo_t *cr, browser_window *w)`
  - `draw_omnibox` (function, line 13660) `static void draw_omnibox(cairo_t *cr, browser_window *w)`
  - `paint` (function, line 13694) `static void paint(browser_window *w)`
  - `redraw` (function, line 13938) `static void redraw(browser_window *w)`
  - `wm_base_ping` (function, line 13950) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 13956) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 13964) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `wl_array_for_each` (function, line 13980) `wl_array_for_each(st, states)`
  - `toplevel_close` (function, line 13986) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 13995) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `set_cursor` (function, line 14007) `static void set_cursor(browser_window *w, int cur_kind)`
  - `element` (function, line 14037) `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...`
  - `fbw_split_y` (function, line 14107) `static double fbw_split_y(const freebug_window *fb)`
  - `freebug_ensure_buffer` (function, line 14116) `static int freebug_ensure_buffer(freebug_window *fb)`
  - `fbw_level_rgb` (function, line 14143) `static void fbw_level_rgb(int level, double *r, double *g, double *b)`
  - `fbw_console_lines` (function, line 14154) `static size_t fbw_console_lines(const fb_buffer *log)`
  - `freebug_paint` (function, line 14167) `static void freebug_paint(freebug_window *fb)`
  - `freebug_redraw_fb` (function, line 14366) `static void freebug_redraw_fb(freebug_window *fb)`
  - `freebug_redraw` (function, line 14375) `static void freebug_redraw(browser_window *w)`
  - `freebug_hide` (function, line 14379) `static void freebug_hide(browser_window *w)`
  - `fbw_xdg_surface_configure` (function, line 14395) `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `fbw_toplevel_configure` (function, line 14403) `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...`
  - `fbw_toplevel_close` (function, line 14412) `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)`
  - `freebug_show` (function, line 14422) `static void freebug_show(browser_window *w)`
  - `freebug_toggle` (function, line 14452) `static void freebug_toggle(browser_window *w)`
  - `freebug_destroy` (function, line 14457) `static void freebug_destroy(browser_window *w)`
  - `freebug_owns_surface` (function, line 14464) `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)`
  - `freebug_is_open` (function, line 14468) `static int freebug_is_open(const browser_window *w)`
  - `freebug_repl_worker` (function, line 14475) `static tab *freebug_repl_worker(browser_window *w)`
  - `freebug_eval` (function, line 14513) `static void freebug_eval(browser_window *w)`
  - `freebug_handle_key` (function, line 14553) `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...`
  - `freebug_pointer_button` (function, line 14588) `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...`
  - `freebug_pointer_motion` (function, line 14607) `static void freebug_pointer_motion(browser_window *w)`
  - `freebug_pointer_axis` (function, line 14629) `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)`
  - `ptr_enter` (function, line 14647) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
  - `ptr_leave` (function, line 14665) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
  - `ptr_motion` (function, line 14682) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
  - `load_current` (function, line 14707) `static void load_current(browser_window *w)`
  - `go_omnibox` (function, line 14720) `static void go_omnibox(browser_window *w)`
  - `ptr_button` (function, line 14765) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
  - `scroll_line_px` (function, line 15012) `static double scroll_line_px(const browser_window *w)`
  - `ptr_axis` (function, line 15016) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
  - `ptr_frame` (function, line 15040) `static void ptr_frame(void *d, struct wl_pointer *p)`
  - `mime_is_text` (function, line 15056) `static int mime_is_text(const char *mime)`
  - `data_offer_source_actions` (function, line 15074) `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_offer_action` (function, line 15077) `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_device_data_offer` (function, line 15087) `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...`
  - `data_device_selection` (function, line 15099) `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...`
  - `data_device_enter` (function, line 15118) `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...`
  - `data_device_leave` (function, line 15123) `static void data_device_leave(void *d, struct wl_data_device *dev)`
  - `data_device_motion` (function, line 15124) `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...`
  - `data_device_drop` (function, line 15128) `static void data_device_drop(void *d, struct wl_data_device *dev)`
  - `data_source_cancelled` (function, line 15139) `static void data_source_cancelled(void *data, struct wl_data_source *src)`
  - `data_source_send` (function, line 15145) `static void data_source_send(void *data, struct wl_data_source *src,
                            ...`
  - `data_source_target` (function, line 15158) `static void data_source_target(void *d, struct wl_data_source *s, const char *m)`
  - `freebug_copy_console` (function, line 15170) `static void freebug_copy_console(browser_window *w)`
  - `insert_pasted_text` (function, line 15228) `static void insert_pasted_text(browser_window *w, const char *text, size_t len)`
  - `clipboard_copy` (function, line 15292) `static void clipboard_copy(browser_window *w)`
  - `keyboard_keymap` (function, line 15340) `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...`
  - `keyboard_enter` (function, line 15361) `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...`
  - `keyboard_leave` (function, line 15368) `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)`
  - `key_sym_to_js_key` (function, line 15376) `static const char *key_sym_to_js_key(xkb_keysym_t sym)`
  - `key_sym_to_keycode` (function, line 15402) `static int key_sym_to_keycode(xkb_keysym_t sym)`
  - `dispatch_js_event` (function, line 15427) `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...`

Next: [KB_gui_p2.md](KB_gui_p2.md)
