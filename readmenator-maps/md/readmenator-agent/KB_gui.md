# Subsystem: gui (page 1 of 2)
Pages: [KB_gui.md](KB_gui.md), [KB_gui_p2.md](KB_gui_p2.md)

## gui/browser_ui.c
- Doc: ui_input_state: Live editable state for one form text control, aliasing a block of the current...
- Layer: presentation
- Language: c
- Symbols:
  - `ui_menu_item` (struct, line 185)
  - `ui_input_state` (struct, line 223)
  - `ui_image` (struct, line 247)
  - `ui_bg_image` (struct, line 260)
  - `tab_ctx` (struct, line 277)
  - `browser_window` (struct, line 293)
  - `fetch_prep` (struct, line 1693)
  - `fetch_job` (struct, line 1774)
  - `rc_frag` (struct, line 3116)
  - `rc_row` (struct, line 3181)
  - `rc_box` (struct, line 3200)
  - `rc_oof_sub` (struct, line 3251)
  - `rc_layout` (struct, line 3253)
  - `rc_oof_sub` (struct, line 3291)
  - `rc_open_box` (struct, line 3301)
  - `rc_state` (struct, line 3359)
  - `rc_ext` (struct, line 3957)
  - `item_sides` (struct, line 4897)
  - `rc_defer_col` (struct, line 7145)
  - `rc_defer` (struct, line 7152)
  - `freebug_window` (struct, line 14483)
  - `ui_menu_action` (enum, line 168)
  - `ui_hot` (enum, line 216)
  - `rc_rowkind` (enum, line 3179)
  - `bs` (type_alias, line 277) `typedef struct tab_ctx { browser_state bs;`
  - `freebug_window` (type_alias, line 565) `typedef struct freebug_window freebug_window;`
  - `allowlisted` (type_alias, line 1693) `typedef struct fetch_prep { int allowlisted;`
  - `font_size` (type_alias, line 3115) `typedef struct rc_frag { double x, width, font_size;`
  - `kind` (type_alias, line 3180) `typedef struct rc_row { rc_rowkind kind;`
  - `h` (type_alias, line 3200) `typedef struct rc_box { double x, top, w, h;`
  - `block_id` (type_alias, line 3301) `typedef struct rc_open_box { int block_id;`
  - `line_desc` (type_alias, line 3358) `typedef struct rc_state { double cur_top, pending_gap, pen_x, line_asc, line_desc;`
  - `family` (type_alias, line 3957) `typedef struct rc_ext { int family;`
  - `mr` (type_alias, line 4897) `typedef struct item_sides { double ml, mr;`
  - `key` (type_alias, line 7145) `typedef struct rc_defer_col { int key;`
  - `col` (type_alias, line 7152) `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];`
  - `now_ms` (function, line 156) `static uint64_t now_ms(void)`
  - `gutter` (function, line 584) `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
  - `apply_zoom` (function, line 605) `static void apply_zoom(browser_window *w)`
  - `buffer_release` (function, line 616) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 622) `static void destroy_buffer(browser_window *w)`
  - `ensure_buffer` (function, line 628) `static int ensure_buffer(browser_window *w)`
  - `read_file` (function, line 658) `static char *read_file(const char *path, size_t *out_len)`
  - `build_file_origin` (function, line 697) `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)`
  - `load_host_file` (function, line 707) `static void load_host_file(hb_set *s, const char *dir, const char *name, hb_list list)`
  - `build_host_filter` (function, line 724) `static hb_set *build_host_filter(void)`
  - `build_js_filter` (function, line 771) `static hb_set *build_js_filter(void)`
  - `build_impersonate_optin` (function, line 774) `static int build_impersonate_optin(void)`
  - `freedom_write_dir` (function, line 783) `static int freedom_write_dir(char *out, size_t cap)`
  - `add_current_host_to_list` (function, line 808) `static void add_current_host_to_list(browser_window *w, int sel)`
  - `load_favorites` (function, line 876) `static void load_favorites(browser_window *w)`
  - `omni_refresh` (function, line 922) `static void omni_refresh(browser_window *w)`
  - `profile_sync` (function, line 953) `static void profile_sync(browser_window *w)`
  - `remember_visit` (function, line 970) `static void remember_visit(browser_window *w, const char *url)`
  - `bookmark_toggle_current` (function, line 978) `static void bookmark_toggle_current(browser_window *w)`
  - `proxy_addr_from_env` (function, line 1002) `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...`
  - `init_net_config` (function, line 1016) `static void init_net_config(browser_window *w)`
  - `is_https_url` (function, line 1026) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 1030) `static int is_http_url(const char *s)`
  - `host_from_url` (function, line 1041) `static int host_from_url(const char *url, char *out, size_t outsz)`
  - `toggle_fullscreen` (function, line 1073) `static void toggle_fullscreen(browser_window *w)`
  - `input_is_interactive` (function, line 1088) `static int input_is_interactive(int input_type)`
  - `input_is_editable` (function, line 1094) `static int input_is_editable(int input_type)`
  - `free_inputs` (function, line 1100) `static void free_inputs(browser_window *w)`
  - `free_images` (function, line 1108) `static void free_images(browser_window *w)`
  - `find_bg_image` (function, line 1147) `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)`
  - `layout` (function, line 1159) `* shared by layout (row height) and paint (blit), so they cannot drift apart. */
static int image...`
  - `placeholder_display_size` (function, line 1219) `static int placeholder_display_size(const rd_block *blk, double box_w,
                          ...`
  - `rebuild_inputs` (function, line 1242) `static void rebuild_inputs(browser_window *w)`
  - `find_input_state` (function, line 1267) `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)`
  - `clear_doc` (function, line 1275) `static void clear_doc(browser_window *w)`
  - `set_cache` (function, line 1285) `static void set_cache(browser_window *w, char *html, size_t len, const char *top)`
  - `surface_from_pixels` (function, line 1296) `static cairo_surface_t *surface_from_pixels(const tab_image *img)`
  - `fetch_follow_navigable` (function, line 1363) `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...`
  - `GET` (function, line 1399) `* a GET (Zero Trust). cfg->policy is restored before returning. */
static sf_status fetch_post_na...`
  - `gui_subresource_fetch` (function, line 1440) `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...`
  - `gui_css_sink` (function, line 1524) `static void gui_css_sink(void *vctx, const char *url,
                         const char *body, ...`
  - `first` (function, line 1592) `* Navigation: clear the registry first (faces are per document). Untrusted:
 * no-op (fetch NULL)...`
  - `prepare_fetch` (function, line 1702) `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...`
  - `fetch_job_free` (function, line 1806) `static void fetch_job_free(fetch_job *j)`
  - `stream_progress_cb` (function, line 1826) `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)`
  - `fetch_thread` (function, line 1850) `static void *fetch_thread(void *arg)`
  - `fetch_launch` (function, line 1898) `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...`
  - `load_images` (function, line 2019) `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
  - `load_bg_images` (function, line 2103) `static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
  - `page_js_host_allowlisted` (function, line 2166) `static int page_js_host_allowlisted(const browser_window *w)`
  - `compute_page_js` (function, line 2172) `static int compute_page_js(const browser_window *w)`
  - `seed_session_cookies` (function, line 2186) `static void seed_session_cookies(tab *t, int trusted, const char *url)`
  - `seed_local_storage` (function, line 2210) `static void seed_local_storage(browser_window *w, tab *t, int trusted)`
  - `collect_local_storage` (function, line 2225) `static void collect_local_storage(browser_window *w, const tab_page *page)`
  - `foldback_session_cookies` (function, line 2235) `static void foldback_session_cookies(const char *url, const char *jar)`
  - `drop_repl_worker` (function, line 2261) `static void drop_repl_worker(browser_window *w)`
  - `schedule_js_tick` (function, line 2275) `static void schedule_js_tick(browser_window *w, int next_ms)`
  - `render_current_ex` (function, line 2285) `static void render_current_ex(browser_window *w, int allow_js_nav)`
  - `render_current` (function, line 2463) `static void render_current(browser_window *w)`
  - `show_busy` (function, line 2470) `static void show_busy(browser_window *w)`
  - `show_fetch_error` (function, line 2479) `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...`
  - `arrives` (function, line 2530) `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...`
  - `strcmp` (function, line 2598) `&& strcmp(auth_host_buf, w->auth_host) != 0)`
  - `tab_save` (function, line 2659) `static void tab_save(browser_window *w)`
  - `tab_restore` (function, line 2676) `static void tab_restore(browser_window *w)`
  - `free_live_page` (function, line 2693) `static void free_live_page(browser_window *w)`
  - `tab_ctx_release` (function, line 2704) `static void tab_ctx_release(tab_ctx *c)`
  - `tab_switch` (function, line 2728) `static void tab_switch(browser_window *w, int idx)`
  - `uitab_close` (function, line 2788) `static void uitab_close(browser_window *w, int idx)`
  - `newtab_x` (function, line 2830) `static double newtab_x(const browser_window *w)`
  - `tab_title` (function, line 2837) `static const char *tab_title(const browser_window *w, int i)`
  - `tabbar_top` (function, line 2853) `static double tabbar_top(const browser_window *w)`
  - `toolbar_top` (function, line 2859) `static double toolbar_top(const browser_window *w)`
  - `content_geometry` (function, line 2866) `static void content_geometry(const browser_window *w, double *top, double *height)`
  - `page_side` (function, line 2892) `static double page_side(const browser_window *w, int side)`
  - `content_margin_x` (function, line 2896) `static double content_margin_x(const browser_window *w)`
  - `content_margins_x` (function, line 2907) `static double content_margins_x(const browser_window *w)`
  - `content_width` (function, line 2912) `static double content_width(const browser_window *w)`
  - `html_center_offset` (function, line 2922) `static double html_center_offset(const browser_window *w)`
  - `scrollbar_metrics` (function, line 2936) `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...`
  - `scrollbar_drag_to` (function, line 2964) `static void scrollbar_drag_to(browser_window *w)`
  - `draw_scrollbar` (function, line 2981) `static void draw_scrollbar(cairo_t *cr, const browser_window *w)`
  - `window_button_rects` (function, line 3018) `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...`
  - `toolbar_rects` (function, line 3028) `static void toolbar_rects(const browser_window *w,
                          double *back_x, doub...`
  - `toolbar_button_at` (function, line 3043) `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)`
  - `hot_actionable` (function, line 3059) `static int hot_actionable(const browser_window *w, ui_hot hot)`
  - `menu_panel_rect` (function, line 3070) `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...`
  - `ua_box_rect` (function, line 3086) `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...`
  - `draw_text` (function, line 3096) `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)`
  - `rc_float_bottom` (function, line 3454) `static double rc_float_bottom(const rc_state *s)`
  - `rc_float_clear` (function, line 3463) `static void rc_float_clear(rc_state *s)`
  - `rc_float_refresh` (function, line 3476) `static void rc_float_refresh(rc_state *s, double line_h)`
  - `rc_float_fit_line` (function, line 3522) `static void rc_float_fit_line(rc_state *s, double line_h)`
  - `line_limit` (function, line 3541) `static double line_limit(const rc_state *s, double content_w)`
  - `rc_free` (function, line 3549) `static void rc_free(rc_layout *L)`
  - `rc_add_box` (function, line 3569) `static rc_box *rc_add_box(rc_layout *L)`
  - `rc_add_frag` (function, line 3581) `static rc_frag *rc_add_frag(rc_layout *L)`
  - `rc_add_row` (function, line 3596) `static rc_row *rc_add_row(rc_layout *L)`
  - `family_face` (function, line 3608) `static const char *family_face(int family)`
  - `content_font_ex` (function, line 3630) `static void content_font_ex(cairo_t *cr, double size, int bold, int italic, int family,
         ...`
  - `sites` (function, line 3643) `* sites (wfh 0, local 0) get the bucket face, which is the toy face's twin. */
    if (wfh != 0u ...`
  - `content_font` (function, line 3652) `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,
            ...`
  - `set_rgb_alpha` (function, line 3659) `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)`
  - `utf8_clen` (function, line 3668) `static size_t utf8_clen(const char *s, size_t n)`
  - `draw_slice` (function, line 3708) `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)`
  - `frag_styled` (function, line 3721) `static int frag_styled(const rc_frag *f)`
  - `styled_advance` (function, line 3728) `static double styled_advance(cairo_t *cr, const rc_frag *f)`
  - `styled_draw` (function, line 3744) `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)`
  - `block_style` (function, line 3761) `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
  - `block_margins` (function, line 3788) `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...`
  - `add` (function, line 3818) `* about to add (top/h passed in). A box that survived a line wrap simply ends at the
 * wrap -- m...`
  - `run` (function, line 3853) `* continuation run (block_id < 0 with no block break) deliberately skips reconcile
 * to stay on ...`
  - `flush_line` (function, line 3865) `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `open_line_height` (function, line 3923) `static double open_line_height(const rc_state *s, const ui_theme *th)`
  - `open_line` (function, line 3936) `static void open_line(rc_layout *L, rc_state *s)`
  - `flow_emit_frag` (function, line 3990) `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...`
  - `flow_text` (function, line 4063) `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...`
  - `input_inline_eligible` (function, line 4325) `static int input_inline_eligible(const rd_block *b)`
  - `input_inline_size` (function, line 4339) `static int input_inline_size(cairo_t *cr, const ui_theme *th, const rd_block *b,
                ...`
  - `replaced_inline_size` (function, line 4361) `static int replaced_inline_size(cairo_t *cr, const browser_window *w, const ui_theme *th,
       ...`
  - `replaced_is_inline_level` (function, line 4393) `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)`
  - `inlines` (function, line 4406) `* next run may also be a replaced element without its own break: consecutive
 * atomic inlines (`...`
  - `place_inline_replaced` (function, line 4442) `static int place_inline_replaced(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
    ...`
  - `css_replaced_box` (function, line 4518) `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...`
  - `emit_replaced_row` (function, line 4527) `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `flow_text_block` (function, line 4630) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
  - `item_root_box_pass` (function, line 4746) `static int item_root_box_pass(const rd_doc *doc, size_t b0, size_t b1, int cbox,
                ...`
  - `them` (function, line 4794) `* to them (jkanime's badge-only tiles keep their box). */
static int item_root_box_in(const rd_do...`
  - `item_root_box` (function, line 4808) `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)`
  - `css_align_to_bt` (function, line 4817) `static int css_align_to_bt(int align_kw)`
  - `box_edge_px` (function, line 4827) `static double box_edge_px(int wpx)`
  - `rc_box_copy_decoration` (function, line 4847) `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)`
  - `box_is_strict_descendant` (function, line 4926) `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)`
  - `item_sides_at_level` (function, line 4948) `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,
                  ...`
  - `container_box_of` (function, line 4979) `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)`
  - `table` (function, line 5001) `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...`
  - `row` (function, line 5066) `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...`
  - `measure_item_w_at` (function, line 5114) `static double measure_item_w_at(cairo_t *cr, const browser_window *w,
                           ...`
  - `lines_at` (function, line 5160) `static size_t lines_at(cairo_t *cr, const browser_window *w, const ui_theme *th,
                ...`
  - `balanced_wrap_width` (function, line 5178) `static double balanced_wrap_width(cairo_t *cr, const browser_window *w, const ui_theme *th,
     ...`
  - `measure_item_content_w` (function, line 5192) `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
  - `run_width_cap` (function, line 5225) `static double run_width_cap(const rd_block *b, double avail_w)`
  - `def_width_cap` (function, line 5229) `static double def_width_cap(const pv_box_def *d, double avail_w)`
  - `def_declared_width` (function, line 5235) `static double def_declared_width(const pv_box_def *d, double avail_w)`
  - `item_declared_basis` (function, line 5240) `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
  - `nested_cont_basis` (function, line 5254) `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...`
  - `flex_item_basis` (function, line 5320) `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
  - `flex_item_min_main` (function, line 5359) `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...`
  - `item_at_level` (function, line 5397) `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `child_cont_at_level` (function, line 5412) `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `cont_in_view` (function, line 5431) `static int cont_in_view(const rd_doc *doc, int cid)`
  - `root_cont_of` (function, line 5445) `static int root_cont_of(const rd_doc *doc, int cid)`
  - `block_is_oof` (function, line 5482) `static int block_is_oof(const rd_doc *doc, const rd_block *bk)`
  - `item_vmargins` (function, line 5524) `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,
          ...`
  - `layout_container` (function, line 5539) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `slot` (function, line 5732) `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
  - `path` (function, line 5894) `*
         * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when
        ...`
  - `box_line_visible` (function, line 6337) `static int box_line_visible(int style)`
  - `close_top_box` (function, line 6343) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `rc_box_context` (function, line 6480) `static void rc_box_context(const rc_state *s, double content_w,
                           double...`
  - `box_margin_top` (function, line 6507) `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `box_margin_bottom` (function, line 6514) `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `children` (function, line 6524) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
  - `column` (function, line 6742) `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
  - `box_path_has` (function, line 6836) `static int box_path_has(const rd_doc *doc, int block_id, int want)`
  - `columns` (function, line 6850) `* each card made 1080px columns (huggingface, github). */
static int deepest_open_on_path(const r...`
  - `nested_stop` (function, line 6864) `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)`
  - `box_shrink_width` (function, line 6876) `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...`
  - `reconcile_boxes_below` (function, line 6916) `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
  - `treatment` (function, line 6967) `* block treatment (shrink-wrapped and placed by text-align), which is what a
         * standalon...`
  - `reconcile_boxes` (function, line 7001) `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
  - `box_path_of` (function, line 7029) `static int box_path_of(const rd_doc *doc, int block_id, int *out)`
  - `band_common_box` (function, line 7045) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)`
  - `block_in_table_caption` (function, line 7109) `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)`
  - `defer_key_block` (function, line 7173) `static int defer_key_block(const rd_block *bk)`
  - `defer_append` (function, line 7296) `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...`
  - `defer_flush` (function, line 7330) `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...`
  - `layout_float_band` (function, line 7551) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
  - `thumbnail` (function, line 7634) `* is what made a wikipedia thumbnail (a 250px image and its caption, no
     * declared width) sp...`
  - `yet` (function, line 7916) `* does not carry yet (WPT flex-abspos-staticpos-*). */
static int runs_share_float(const rd_doc *...`
  - `layout_doc` (function, line 7928) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
  - `count` (function, line 8339) `* the box count (a hostile parent cycle terminates). */
static int oof_depth(const rd_doc *doc, s...`
  - `approximation` (function, line 8358) `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */
static void oof_s...`
  - `position_doc` (function, line 8551) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
  - `input_box_width` (function, line 8718) `static double input_box_width(double content_w)`
  - `select_box_width` (function, line 8722) `static double select_box_width(double content_w)`
  - `button_box_width` (function, line 8727) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...`
  - `blit_image_box` (function, line 9171) `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,
                 ...`
  - `v_read` (function, line 9354) `static int v_read(int fd, void *buf, size_t n)`
  - `dies` (function, line 9382) `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
  - `audio_spawn` (function, line 9391) `static void audio_spawn(browser_window *w, int rate, int channels)`
  - `audio_mark_dead` (function, line 9445) `static void audio_mark_dead(browser_window *w)`
  - `audio_write` (function, line 9462) `static void audio_write(browser_window *w, const uint8_t *data, size_t len)`
  - `audio_stop` (function, line 9477) `static void audio_stop(browser_window *w)`
  - `video_stop` (function, line 9497) `static void video_stop(browser_window *w)`
  - `video_fetch` (function, line 9675) `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...`
  - `video_play` (function, line 9692) `static int video_play(browser_window *w, const char *m3u8_url)`
  - `video_stop` (function, line 9794) `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
  - `paint_video_row` (function, line 9848) `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
  - `row_line_slack` (function, line 9960) `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)`
  - `row_align_offset` (function, line 9972) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)`
  - `upstream` (function, line 10000) `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
  - `box_path` (function, line 10028) `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `text` (function, line 10047) `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
  - `grad_stop` (function, line 10074) `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)`
  - `bui_grad_color_at` (function, line 10089) `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...`
  - `spaced` (function, line 10122) `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
  - `paint_bg_layer` (function, line 10155) `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...`
  - `paint_box_decoration` (function, line 10199) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
  - `cairo_set_dash` (function, line 10366) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 10369) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 10409) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 10412) `cairo_set_dash(cr, (double[])`
  - `set_rgb` (function, line 10446) `set_rgb(cr, (ui_rgb)`
  - `cairo_set_dash` (function, line 10470) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 10473) `cairo_set_dash(cr, (double[])`
  - `paint_deco_line` (function, line 10531) `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...`
  - `cairo_set_dash` (function, line 10565) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 10567) `cairo_set_dash(cr, (double[])`
  - `paint_svg_at` (function, line 10587) `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...`
  - `replaced_current_color` (function, line 10607) `static int replaced_current_color(const browser_window *w, const rd_block *blk)`
  - `paint_inline_replaced` (function, line 10616) `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...`
  - `paint_content_row` (function, line 10642) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
  - `ov_box_clips` (function, line 10832) `static int ov_box_clips(const pv_box_def *d)`
  - `ov_collect_chain` (function, line 10839) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)`
  - `ov_box_bounds` (function, line 10860) `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)`
  - `ov_content_rect` (function, line 10884) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...`
  - `fragment` (function, line 10904) `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
  - `box_forms_stacking_context` (function, line 10959) `static int box_forms_stacking_context(const pv_box_def *def)`
  - `bui_skew_tan` (function, line 11002) `static double bui_skew_tan(int deg)`
  - `box_transform_matrix` (function, line 11009) `static void box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
             ...`
  - `bui_blend_operator` (function, line 11127) `static cairo_operator_t bui_blend_operator(int mix_blend)`
  - `bui_paint_backdrop_blur` (function, line 11265) `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...`
  - `bui_pop_group_composite` (function, line 11323) `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms)`
  - `limits` (function, line 11553) `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
  - `paint_box_decoration_grouped` (function, line 11622) `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
  - `paint_box_and_direct_rows` (function, line 11662) `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...`
  - `paint_oof_sub` (function, line 11761) `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,
                ...`
  - `paint_positioned_one` (function, line 11799) `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...`
  - `box` (function, line 11907) `* content belongs to that box (painted by its own positioned entry). */
    if (sub == NULL)`
  - `paint_nested_children` (function, line 12013) `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...`
  - `geom_from_layout` (function, line 12050) `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,
                ...`
  - `publish_geometry` (function, line 12081) `static void publish_geometry(browser_window *w, const rc_layout *L, double left,
                ...`
  - `paint_structured` (function, line 12103) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
  - `write_doc_pdf` (function, line 12321) `static long write_doc_pdf(browser_window *w, const char *path)`
  - `export_pdf` (function, line 12427) `static void export_pdf(browser_window *w)`
  - `write_doc_png` (function, line 12490) `static long write_doc_png(browser_window *w, const char *path)`
  - `export_png` (function, line 12618) `static void export_png(browser_window *w)`
  - `caller` (function, line 12652) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
  - `ui_render_png` (function, line 12675) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)`
  - `render_doc_images` (function, line 12735) `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...`
  - `ui_render_png_images` (function, line 12766) `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_pdf_images` (function, line 12772) `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_dump_layout` (function, line 12787) `ui_status ui_dump_layout(const rd_doc *doc)`
  - `link_at_point` (function, line 12859) `static const char *link_at_point(browser_window *w, double px, double py)`
  - `resolve_box_cursor` (function, line 12950) `static int resolve_box_cursor(const rd_doc *doc, int block_id)`
  - `box_pointer_events_none` (function, line 12964) `static int box_pointer_events_none(const rd_doc *doc, int block_id)`
  - `cursor_at_point` (function, line 12980) `static int cursor_at_point(browser_window *w, double px, double py)`
  - `node_at_point` (function, line 13045) `static dom_node_id node_at_point(browser_window *w, double px, double py)`
  - `Firefox` (function, line 13053) `* on its face does in Firefox (spec/page_view.md, tanda 40). */
static const rd_block *submit_pro...`
  - `frag_at_point` (function, line 13072) `static dom_node_id frag_at_point(browser_window *w, double px, double py,
                       ...`
  - `reference` (function, line 13126) `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
  - `set_page_url` (function, line 13145) `static void set_page_url(browser_window *w, const char *url)`
  - `ws_apply_ops` (function, line 13170) `static void ws_apply_ops(browser_window *w, const tab_page *page)`
  - `apply_history_ops` (function, line 13205) `static void apply_history_ops(browser_window *w, const tab_page *page)`
  - `history_step` (function, line 13217) `static void history_step(browser_window *w, int steps)`
  - `apply_click_result` (function, line 13250) `static int apply_click_result(browser_window *w, tab_page *page)`
  - `memory` (function, line 13300) `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
  - `GET` (function, line 13394) `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
  - `ensure_download_dir` (function, line 13428) `static int ensure_download_dir(char *out, size_t outsz)`
  - `write_file_atomic` (function, line 13443) `static int write_file_atomic(const char *path, const void *bytes, size_t len)`
  - `save_download` (function, line 13465) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...`
  - `save_current_page` (function, line 13498) `static void save_current_page(browser_window *w)`
  - `deliver_fetch_result` (function, line 13508) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
  - `drain_fetch_results` (function, line 13562) `static void drain_fetch_results(browser_window *w)`
  - `toggle_reader` (function, line 13638) `static void toggle_reader(browser_window *w)`
  - `menu_item_checked` (function, line 13649) `static int menu_item_checked(const browser_window *w, size_t i)`
  - `menu_item_toggle` (function, line 13671) `static void menu_item_toggle(browser_window *w, size_t i)`
  - `draw_clock` (function, line 13781) `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...`
  - `draw_hamburger` (function, line 13793) `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_reload` (function, line 13809) `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_menu` (function, line 13831) `static void draw_menu(cairo_t *cr, browser_window *w)`
  - `draw_hover_url` (function, line 13942) `static double draw_hover_url(cairo_t *cr, browser_window *w)`
  - `draw_toast` (function, line 13974) `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)`
  - `draw_tabstrip` (function, line 14004) `static void draw_tabstrip(cairo_t *cr, browser_window *w)`
  - `draw_omnibox` (function, line 14059) `static void draw_omnibox(cairo_t *cr, browser_window *w)`
  - `paint` (function, line 14093) `static void paint(browser_window *w)`
  - `redraw` (function, line 14337) `static void redraw(browser_window *w)`
  - `wm_base_ping` (function, line 14349) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 14355) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 14363) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `wl_array_for_each` (function, line 14379) `wl_array_for_each(st, states)`
  - `toplevel_close` (function, line 14385) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 14394) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `set_cursor` (function, line 14406) `static void set_cursor(browser_window *w, int cur_kind)`
  - `element` (function, line 14436) `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...`
  - `fbw_split_y` (function, line 14506) `static double fbw_split_y(const freebug_window *fb)`
  - `freebug_ensure_buffer` (function, line 14515) `static int freebug_ensure_buffer(freebug_window *fb)`
  - `fbw_level_rgb` (function, line 14542) `static void fbw_level_rgb(int level, double *r, double *g, double *b)`
  - `fbw_console_lines` (function, line 14553) `static size_t fbw_console_lines(const fb_buffer *log)`
  - `freebug_paint` (function, line 14566) `static void freebug_paint(freebug_window *fb)`
  - `freebug_redraw_fb` (function, line 14765) `static void freebug_redraw_fb(freebug_window *fb)`
  - `freebug_redraw` (function, line 14774) `static void freebug_redraw(browser_window *w)`
  - `freebug_hide` (function, line 14778) `static void freebug_hide(browser_window *w)`
  - `fbw_xdg_surface_configure` (function, line 14794) `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `fbw_toplevel_configure` (function, line 14802) `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...`
  - `fbw_toplevel_close` (function, line 14811) `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)`
  - `freebug_show` (function, line 14821) `static void freebug_show(browser_window *w)`
  - `freebug_toggle` (function, line 14851) `static void freebug_toggle(browser_window *w)`
  - `freebug_destroy` (function, line 14856) `static void freebug_destroy(browser_window *w)`
  - `freebug_owns_surface` (function, line 14863) `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)`
  - `freebug_is_open` (function, line 14867) `static int freebug_is_open(const browser_window *w)`
  - `freebug_repl_worker` (function, line 14874) `static tab *freebug_repl_worker(browser_window *w)`
  - `freebug_eval` (function, line 14912) `static void freebug_eval(browser_window *w)`
  - `freebug_handle_key` (function, line 14952) `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...`
  - `freebug_pointer_button` (function, line 14987) `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...`
  - `freebug_pointer_motion` (function, line 15006) `static void freebug_pointer_motion(browser_window *w)`
  - `freebug_pointer_axis` (function, line 15028) `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)`
  - `ptr_enter` (function, line 15046) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
  - `ptr_leave` (function, line 15064) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
  - `ptr_motion` (function, line 15081) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
  - `load_current` (function, line 15106) `static void load_current(browser_window *w)`
  - `go_omnibox` (function, line 15119) `static void go_omnibox(browser_window *w)`
  - `ptr_button` (function, line 15164) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
  - `scroll_line_px` (function, line 15411) `static double scroll_line_px(const browser_window *w)`
  - `ptr_axis` (function, line 15415) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
  - `ptr_frame` (function, line 15439) `static void ptr_frame(void *d, struct wl_pointer *p)`
  - `mime_is_text` (function, line 15455) `static int mime_is_text(const char *mime)`
  - `data_offer_source_actions` (function, line 15473) `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_offer_action` (function, line 15476) `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_device_data_offer` (function, line 15486) `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...`
  - `data_device_selection` (function, line 15498) `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...`
  - `data_device_enter` (function, line 15517) `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...`

Next: [KB_gui_p2.md](KB_gui_p2.md)
