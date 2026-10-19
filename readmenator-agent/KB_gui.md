# Subsystem: gui (page 1 of 2)
Pages: [KB_gui.md](KB_gui.md), [KB_gui_p2.md](KB_gui_p2.md)

## gui/browser_ui.c
- Doc: ui_input_state: Live editable state for one form text control, aliasing a block of the current...
- Layer: presentation
- Language: c
- Symbols:
  - `ui_menu_item` (struct, line 187)
  - `ui_input_state` (struct, line 225)
  - `ui_image` (struct, line 249)
  - `ui_bg_image` (struct, line 262)
  - `tab_ctx` (struct, line 279)
  - `browser_window` (struct, line 295)
  - `repl_edges` (struct, line 1165)
  - `fetch_prep` (struct, line 1774)
  - `fetch_job` (struct, line 1855)
  - `rc_frag` (struct, line 3197)
  - `rc_row` (struct, line 3262)
  - `rc_box` (struct, line 3285)
  - `rc_oof_sub` (struct, line 3341)
  - `rc_layout` (struct, line 3343)
  - `rc_oof_sub` (struct, line 3388)
  - `rc_open_box` (struct, line 3398)
  - `rc_ibox` (struct, line 3444)
  - `rc_state` (struct, line 3475)
  - `rc_ext` (struct, line 4112)
  - `item_sides` (struct, line 5208)
  - `rc_defer_col` (struct, line 7913)
  - `rc_defer` (struct, line 7920)
  - `screen_flow_ctx` (struct, line 13208)
  - `png_flow_ctx` (struct, line 13620)
  - `freebug_window` (struct, line 15633)
  - `ui_menu_action` (enum, line 170)
  - `ui_hot` (enum, line 218)
  - `rc_rowkind` (enum, line 3260)
  - `bs` (type_alias, line 279) `typedef struct tab_ctx { browser_state bs;`
  - `freebug_window` (type_alias, line 567) `typedef struct freebug_window freebug_window;`
  - `pl` (type_alias, line 1165) `typedef struct repl_edges { double mt, mr, mb, ml, bt, br, bb, bl, pt, pr, pb, pl;`
  - `allowlisted` (type_alias, line 1774) `typedef struct fetch_prep { int allowlisted;`
  - `font_size` (type_alias, line 3196) `typedef struct rc_frag { double x, width, font_size;`
  - `kind` (type_alias, line 3261) `typedef struct rc_row { rc_rowkind kind;`
  - `h` (type_alias, line 3285) `typedef struct rc_box { double x, top, w, h;`
  - `block_id` (type_alias, line 3398) `typedef struct rc_open_box { int block_id;`
  - `col_founder_box` (type_alias, line 3474) `typedef struct rc_state { /* Inside a float band column whose width was SHRUNK TO FIT: the float * founder's own box...`
  - `family` (type_alias, line 4112) `typedef struct rc_ext { int family;`
  - `mr` (type_alias, line 5208) `typedef struct item_sides { double ml, mr;`
  - `key` (type_alias, line 7913) `typedef struct rc_defer_col { int key;`
  - `col` (type_alias, line 7920) `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];`
  - `now_ms` (function, line 158) `static uint64_t now_ms(void)`
  - `gutter` (function, line 586) `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
  - `apply_zoom` (function, line 606) `static void apply_zoom(browser_window *w)`
  - `buffer_release` (function, line 617) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 623) `static void destroy_buffer(browser_window *w)`
  - `ensure_buffer` (function, line 629) `static int ensure_buffer(browser_window *w)`
  - `read_file` (function, line 659) `static char *read_file(const char *path, size_t *out_len)`
  - `build_file_origin` (function, line 698) `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)`
  - `load_host_file` (function, line 708) `static void load_host_file(hb_set *s, const char *dir, const char *name, hb_list list)`
  - `build_host_filter` (function, line 725) `static hb_set *build_host_filter(void)`
  - `build_js_filter` (function, line 772) `static hb_set *build_js_filter(void)`
  - `build_impersonate_optin` (function, line 775) `static int build_impersonate_optin(void)`
  - `freedom_write_dir` (function, line 784) `static int freedom_write_dir(char *out, size_t cap)`
  - `add_current_host_to_list` (function, line 809) `static void add_current_host_to_list(browser_window *w, int sel)`
  - `load_favorites` (function, line 877) `static void load_favorites(browser_window *w)`
  - `omni_refresh` (function, line 923) `static void omni_refresh(browser_window *w)`
  - `profile_sync` (function, line 954) `static void profile_sync(browser_window *w)`
  - `remember_visit` (function, line 971) `static void remember_visit(browser_window *w, const char *url)`
  - `bookmark_toggle_current` (function, line 979) `static void bookmark_toggle_current(browser_window *w)`
  - `proxy_addr_from_env` (function, line 1003) `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...`
  - `init_net_config` (function, line 1017) `static void init_net_config(browser_window *w)`
  - `is_https_url` (function, line 1027) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 1031) `static int is_http_url(const char *s)`
  - `host_from_url` (function, line 1042) `static int host_from_url(const char *url, char *out, size_t outsz)`
  - `toggle_fullscreen` (function, line 1074) `static void toggle_fullscreen(browser_window *w)`
  - `input_is_interactive` (function, line 1089) `static int input_is_interactive(int input_type)`
  - `input_is_editable` (function, line 1095) `static int input_is_editable(int input_type)`
  - `free_inputs` (function, line 1101) `static void free_inputs(browser_window *w)`
  - `free_images` (function, line 1109) `static void free_images(browser_window *w)`
  - `find_bg_image` (function, line 1148) `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)`
  - `replaced_edges` (function, line 1172) `static repl_edges replaced_edges(const rd_doc *doc, const rd_block *b, double cb_w)`
  - `repl_edges_x` (function, line 1196) `static double repl_edges_x(const repl_edges *e)`
  - `repl_edges_y` (function, line 1200) `static double repl_edges_y(const repl_edges *e)`
  - `image_display_size` (function, line 1234) `static int image_display_size(const browser_window *w, const rd_block *blk,
                     ...`
  - `placeholder_display_size` (function, line 1300) `static int placeholder_display_size(const rd_block *blk, double box_w,
                          ...`
  - `rebuild_inputs` (function, line 1323) `static void rebuild_inputs(browser_window *w)`
  - `find_input_state` (function, line 1348) `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)`
  - `clear_doc` (function, line 1356) `static void clear_doc(browser_window *w)`
  - `set_cache` (function, line 1366) `static void set_cache(browser_window *w, char *html, size_t len, const char *top)`
  - `surface_from_pixels` (function, line 1377) `static cairo_surface_t *surface_from_pixels(const tab_image *img)`
  - `fetch_follow_navigable` (function, line 1444) `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...`
  - `GET` (function, line 1480) `* a GET (Zero Trust). cfg->policy is restored before returning. */
static sf_status fetch_post_na...`
  - `gui_subresource_fetch` (function, line 1521) `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...`
  - `gui_css_sink` (function, line 1605) `static void gui_css_sink(void *vctx, const char *url,
                         const char *body, ...`
  - `first` (function, line 1673) `* Navigation: clear the registry first (faces are per document). Untrusted:
 * no-op (fetch NULL)...`
  - `prepare_fetch` (function, line 1783) `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...`
  - `fetch_job_free` (function, line 1887) `static void fetch_job_free(fetch_job *j)`
  - `stream_progress_cb` (function, line 1907) `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)`
  - `fetch_thread` (function, line 1931) `static void *fetch_thread(void *arg)`
  - `fetch_launch` (function, line 1979) `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...`
  - `load_images` (function, line 2100) `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
  - `load_bg_images` (function, line 2184) `static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
  - `page_js_host_allowlisted` (function, line 2247) `static int page_js_host_allowlisted(const browser_window *w)`
  - `compute_page_js` (function, line 2253) `static int compute_page_js(const browser_window *w)`
  - `seed_session_cookies` (function, line 2267) `static void seed_session_cookies(tab *t, int trusted, const char *url)`
  - `seed_local_storage` (function, line 2291) `static void seed_local_storage(browser_window *w, tab *t, int trusted)`
  - `collect_local_storage` (function, line 2306) `static void collect_local_storage(browser_window *w, const tab_page *page)`
  - `foldback_session_cookies` (function, line 2316) `static void foldback_session_cookies(const char *url, const char *jar)`
  - `drop_repl_worker` (function, line 2342) `static void drop_repl_worker(browser_window *w)`
  - `schedule_js_tick` (function, line 2356) `static void schedule_js_tick(browser_window *w, int next_ms)`
  - `render_current_ex` (function, line 2366) `static void render_current_ex(browser_window *w, int allow_js_nav)`
  - `render_current` (function, line 2544) `static void render_current(browser_window *w)`
  - `show_busy` (function, line 2551) `static void show_busy(browser_window *w)`
  - `show_fetch_error` (function, line 2560) `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...`
  - `arrives` (function, line 2611) `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...`
  - `strcmp` (function, line 2679) `&& strcmp(auth_host_buf, w->auth_host) != 0)`
  - `tab_save` (function, line 2740) `static void tab_save(browser_window *w)`
  - `tab_restore` (function, line 2757) `static void tab_restore(browser_window *w)`
  - `free_live_page` (function, line 2774) `static void free_live_page(browser_window *w)`
  - `tab_ctx_release` (function, line 2785) `static void tab_ctx_release(tab_ctx *c)`
  - `tab_switch` (function, line 2809) `static void tab_switch(browser_window *w, int idx)`
  - `uitab_close` (function, line 2869) `static void uitab_close(browser_window *w, int idx)`
  - `newtab_x` (function, line 2911) `static double newtab_x(const browser_window *w)`
  - `tab_title` (function, line 2918) `static const char *tab_title(const browser_window *w, int i)`
  - `tabbar_top` (function, line 2934) `static double tabbar_top(const browser_window *w)`
  - `toolbar_top` (function, line 2940) `static double toolbar_top(const browser_window *w)`
  - `content_geometry` (function, line 2947) `static void content_geometry(const browser_window *w, double *top, double *height)`
  - `page_side` (function, line 2973) `static double page_side(const browser_window *w, int side)`
  - `content_margin_x` (function, line 2977) `static double content_margin_x(const browser_window *w)`
  - `content_margins_x` (function, line 2988) `static double content_margins_x(const browser_window *w)`
  - `content_width` (function, line 2993) `static double content_width(const browser_window *w)`
  - `html_center_offset` (function, line 3003) `static double html_center_offset(const browser_window *w)`
  - `scrollbar_metrics` (function, line 3017) `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...`
  - `scrollbar_drag_to` (function, line 3045) `static void scrollbar_drag_to(browser_window *w)`
  - `draw_scrollbar` (function, line 3062) `static void draw_scrollbar(cairo_t *cr, const browser_window *w)`
  - `window_button_rects` (function, line 3099) `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...`
  - `toolbar_rects` (function, line 3109) `static void toolbar_rects(const browser_window *w,
                          double *back_x, doub...`
  - `toolbar_button_at` (function, line 3124) `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)`
  - `hot_actionable` (function, line 3140) `static int hot_actionable(const browser_window *w, ui_hot hot)`
  - `menu_panel_rect` (function, line 3151) `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...`
  - `ua_box_rect` (function, line 3167) `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...`
  - `draw_text` (function, line 3177) `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)`
  - `rc_float_bottom` (function, line 3571) `static double rc_float_bottom(const rc_state *s)`
  - `rc_float_clear` (function, line 3580) `static void rc_float_clear(rc_state *s)`
  - `rc_float_refresh` (function, line 3593) `static void rc_float_refresh(rc_state *s, double line_h)`
  - `rc_float_fit_line` (function, line 3639) `static void rc_float_fit_line(rc_state *s, double line_h)`
  - `line_limit` (function, line 3658) `static double line_limit(const rc_state *s, double content_w)`
  - `rc_free` (function, line 3666) `static void rc_free(rc_layout *L)`
  - `rc_add_box` (function, line 3686) `static rc_box *rc_add_box(rc_layout *L)`
  - `rc_add_frag` (function, line 3698) `static rc_frag *rc_add_frag(rc_layout *L)`
  - `rc_add_row` (function, line 3713) `static rc_row *rc_add_row(rc_layout *L)`
  - `family_face` (function, line 3725) `static const char *family_face(int family)`
  - `content_font_ex` (function, line 3747) `static void content_font_ex(cairo_t *cr, double size, int bold, int italic, int family,
         ...`
  - `sites` (function, line 3760) `* sites (wfh 0, local 0) get the bucket face, which is the toy face's twin. */
    if (wfh != 0u ...`
  - `content_font` (function, line 3769) `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,
            ...`
  - `set_rgb_alpha` (function, line 3776) `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)`
  - `utf8_clen` (function, line 3785) `static size_t utf8_clen(const char *s, size_t n)`
  - `draw_slice` (function, line 3818) `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)`
  - `frag_styled` (function, line 3831) `static int frag_styled(const rc_frag *f)`
  - `styled_advance` (function, line 3838) `static double styled_advance(cairo_t *cr, const rc_frag *f)`
  - `styled_draw` (function, line 3860) `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)`
  - `block_style` (function, line 3883) `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
  - `block_margins` (function, line 3910) `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...`
  - `area` (function, line 3947) `* box spans its CONTENT area (the font's ascent + descent plus its vertical padding
 * and border...`
  - `run` (function, line 3995) `* continuation run (block_id < 0 with no block break) deliberately skips reconcile
 * to stay on ...`
  - `flush_line` (function, line 4009) `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `open_line_height` (function, line 4076) `static double open_line_height(const rc_state *s, const ui_theme *th)`
  - `open_line` (function, line 4091) `static void open_line(rc_layout *L, rc_state *s)`
  - `flow_emit_frag` (function, line 4145) `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...`
  - `flow_smallcaps_word` (function, line 4205) `static double flow_smallcaps_word(cairo_t *cr, rc_layout *L, rc_state *s,
                       ...`
  - `ibx_advance` (function, line 4260) `static void ibx_advance(const rc_layout *L, rc_state *s, double adv)`
  - `flow_text` (function, line 4268) `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...`
  - `input_inline_eligible` (function, line 4547) `static int input_inline_eligible(const rd_block *b)`
  - `input_inline_size` (function, line 4561) `static int input_inline_size(cairo_t *cr, const ui_theme *th, const rd_block *b,
                ...`
  - `replaced_inline_size` (function, line 4583) `static int replaced_inline_size(cairo_t *cr, const browser_window *w, const ui_theme *th,
       ...`
  - `replaced_is_inline_level` (function, line 4615) `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)`
  - `inlines` (function, line 4628) `* next run may also be a replaced element without its own break: consecutive
 * atomic inlines (`...`
  - `place_inline_replaced` (function, line 4665) `static int place_inline_replaced(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
    ...`
  - `css_replaced_box` (function, line 4750) `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...`
  - `emit_replaced_row` (function, line 4759) `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `block_text_style` (function, line 4872) `static void block_text_style(const browser_window *w, const ui_theme *th, const rd_block *b,
    ...`
  - `flow_text_block` (function, line 4883) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
  - `run_is_content` (function, line 5039) `static int run_is_content(const rd_block *bk)`
  - `item_root_box_pass` (function, line 5049) `static int item_root_box_pass(const rd_doc *doc, size_t b0, size_t b1, int cbox,
                ...`
  - `them` (function, line 5102) `* to them (jkanime's badge-only tiles keep their box). */
static int item_root_box_in(const rd_do...`
  - `item_root_box` (function, line 5116) `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)`
  - `itself` (function, line 5124) `* STRETCH itself (box_tree fills the line with it). */
static int css_align_to_bt(int align_kw)`
  - `box_edge_px` (function, line 5135) `static double box_edge_px(int wpx)`
  - `rc_box_copy_decoration` (function, line 5155) `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)`
  - `box_is_strict_descendant` (function, line 5237) `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)`
  - `item_sides_at_level` (function, line 5259) `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,
                  ...`
  - `container_box_of` (function, line 5315) `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)`
  - `table` (function, line 5337) `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...`
  - `row` (function, line 5402) `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...`
  - `measure_item_w_at` (function, line 5450) `static double measure_item_w_at(cairo_t *cr, const browser_window *w,
                           ...`
  - `lines_at` (function, line 5500) `static size_t lines_at(cairo_t *cr, const browser_window *w, const ui_theme *th,
                ...`
  - `balanced_wrap_width` (function, line 5518) `static double balanced_wrap_width(cairo_t *cr, const browser_window *w, const ui_theme *th,
     ...`
  - `item_inner_inset` (function, line 5539) `static double item_inner_inset(const rd_doc *doc, size_t b0, size_t b1, int root)`
  - `measure_item_content_w` (function, line 5566) `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
  - `run_width_cap` (function, line 5599) `static double run_width_cap(const rd_block *b, double avail_w)`
  - `def_width_cap` (function, line 5603) `static double def_width_cap(const pv_box_def *d, double avail_w)`
  - `def_declared_width` (function, line 5609) `static double def_declared_width(const pv_box_def *d, double avail_w)`
  - `item_declared_basis` (function, line 5614) `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
  - `nested_cont_basis` (function, line 5628) `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...`
  - `flex_item_basis` (function, line 5702) `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
  - `flex_item_min_main` (function, line 5742) `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...`
  - `item_at_level` (function, line 5781) `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `child_cont_at_level` (function, line 5796) `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `cont_in_view` (function, line 5815) `static int cont_in_view(const rd_doc *doc, int cid)`
  - `root_cont_of` (function, line 5829) `static int root_cont_of(const rd_doc *doc, int cid)`
  - `box_under` (function, line 5840) `static int box_under(const rd_doc *doc, int child, int anc)`
  - `root_cont_in` (function, line 5857) `static int root_cont_in(const rd_doc *doc, int cid, int float_box)`
  - `block_is_oof` (function, line 5901) `static int block_is_oof(const rd_doc *doc, const rd_block *bk)`
  - `item_vmargins` (function, line 5946) `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,
          ...`
  - `container_inner_h` (function, line 5967) `static double container_inner_h(const rd_doc *doc, const pv_cont_def *cdv, double content_w)`
  - `layout_container` (function, line 6007) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `slot` (function, line 6200) `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
  - `path` (function, line 6399) `*
         * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when
        ...`
  - `box_line_visible` (function, line 6991) `static int box_line_visible(int style)`
  - `col_spend_free_space` (function, line 7005) `static void col_spend_free_space(rc_layout *L, const rc_open_box *ob, double free_px)`
  - `close_top_box` (function, line 7050) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `rc_box_context` (function, line 7188) `static void rc_box_context(const rc_state *s, double content_w,
                           double...`
  - `box_margin_top` (function, line 7215) `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `box_margin_bottom` (function, line 7222) `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `children` (function, line 7232) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
  - `column` (function, line 7455) `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
  - `box_path_has` (function, line 7549) `static int box_path_has(const rd_doc *doc, int block_id, int want)`
  - `columns` (function, line 7563) `* each card made 1080px columns (huggingface, github). */
static int deepest_open_on_path(const r...`
  - `nested_stop` (function, line 7577) `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)`
  - `box_shrink_width` (function, line 7589) `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...`
  - `reconcile_boxes_below` (function, line 7665) `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
  - `reconcile_boxes` (function, line 7769) `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
  - `box_path_of` (function, line 7797) `static int box_path_of(const rd_doc *doc, int block_id, int *out)`
  - `band_common_box` (function, line 7813) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)`
  - `block_in_table_caption` (function, line 7877) `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)`
  - `defer_key_block` (function, line 7941) `static int defer_key_block(const rd_block *bk)`
  - `defer_append` (function, line 8064) `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...`
  - `defer_flush` (function, line 8098) `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...`
  - `layout_float_band` (function, line 8319) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
  - `yet` (function, line 8770) `* does not carry yet (WPT flex-abspos-staticpos-*). */
static int runs_share_float(const rd_doc *...`
  - `layout_doc` (function, line 8782) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
  - `count` (function, line 9224) `* the box count (a hostile parent cycle terminates). */
static int oof_depth(const rd_doc *doc, s...`
  - `approximation` (function, line 9243) `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */
static void oof_s...`
  - `position_doc` (function, line 9444) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
  - `defer_root_of` (function, line 9617) `static int defer_root_of(const rc_layout *L, int bid)`
  - `defer_wants` (function, line 9625) `static int defer_wants(const rc_layout *L, int bid, int only_root)`
  - `input_box_width` (function, line 9631) `static double input_box_width(double content_w)`
  - `select_box_width` (function, line 9635) `static double select_box_width(double content_w)`
  - `button_box_width` (function, line 9640) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...`
  - `blit_image_box` (function, line 10084) `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,
                 ...`
  - `v_read` (function, line 10275) `static int v_read(int fd, void *buf, size_t n)`
  - `dies` (function, line 10303) `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
  - `audio_spawn` (function, line 10312) `static void audio_spawn(browser_window *w, int rate, int channels)`
  - `audio_mark_dead` (function, line 10366) `static void audio_mark_dead(browser_window *w)`
  - `audio_write` (function, line 10383) `static void audio_write(browser_window *w, const uint8_t *data, size_t len)`
  - `audio_stop` (function, line 10398) `static void audio_stop(browser_window *w)`
  - `video_stop` (function, line 10418) `static void video_stop(browser_window *w)`
  - `video_fetch` (function, line 10596) `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...`
  - `video_play` (function, line 10613) `static int video_play(browser_window *w, const char *m3u8_url)`
  - `video_stop` (function, line 10715) `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
  - `paint_video_row` (function, line 10769) `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
  - `row_line_slack` (function, line 10881) `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)`
  - `row_align_offset` (function, line 10893) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)`
  - `upstream` (function, line 10921) `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
  - `box_path` (function, line 10949) `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `paint_box_shadow_layer` (function, line 10960) `static void paint_box_shadow_layer(cairo_t *cr, double x, double y, double w, double h,
         ...`
  - `text` (function, line 11051) `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
  - `grad_stop` (function, line 11078) `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)`
  - `bui_grad_color_at` (function, line 11093) `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...`
  - `spaced` (function, line 11126) `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
  - `paint_bg_layer` (function, line 11159) `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...`
  - `paint_box_decoration` (function, line 11203) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
  - `cairo_set_dash` (function, line 11340) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11343) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11383) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11386) `cairo_set_dash(cr, (double[])`
  - `set_rgb` (function, line 11420) `set_rgb(cr, (ui_rgb)`
  - `cairo_set_dash` (function, line 11444) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11447) `cairo_set_dash(cr, (double[])`
  - `paint_deco_line` (function, line 11505) `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...`
  - `cairo_set_dash` (function, line 11539) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11541) `cairo_set_dash(cr, (double[])`
  - `paint_svg_at` (function, line 11561) `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...`
  - `replaced_current_color` (function, line 11581) `static int replaced_current_color(const browser_window *w, const rd_block *blk)`
  - `paint_inline_replaced` (function, line 11590) `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...`
  - `paint_content_row` (function, line 11635) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
  - `paint_content_row_ex` (function, line 11642) `static void paint_content_row_ex(cairo_t *cr, browser_window *w, const rc_layout *L,
            ...`
  - `ov_box_clips` (function, line 11851) `static int ov_box_clips(const pv_box_def *d)`
  - `ov_collect_chain` (function, line 11858) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)`
  - `ov_box_bounds` (function, line 11879) `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)`
  - `ov_content_rect` (function, line 11903) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...`
  - `fragment` (function, line 11923) `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
  - `box_forms_stacking_context` (function, line 11978) `static int box_forms_stacking_context(const pv_box_def *def)`
  - `bui_skew_tan` (function, line 12021) `static double bui_skew_tan(int deg)`
  - `box_transform_matrix` (function, line 12028) `static int box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
              ...`
  - `bui_blend_operator` (function, line 12156) `static cairo_operator_t bui_blend_operator(int mix_blend)`
  - `bui_paint_backdrop_blur` (function, line 12294) `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...`
  - `bui_pop_group_composite` (function, line 12352) `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms)`
  - `limits` (function, line 12598) `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
  - `paint_box_decoration_grouped` (function, line 12667) `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
  - `paint_box_and_direct_rows` (function, line 12708) `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...`
  - `paint_oof_sub` (function, line 12816) `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,
                ...`
  - `paint_positioned_one` (function, line 12854) `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...`
  - `box` (function, line 12966) `* content belongs to that box (painted by its own positioned entry). */
    if (sub == NULL)`
  - `paint_nested_children` (function, line 13071) `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...`
  - `geom_from_layout` (function, line 13108) `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,
                ...`
  - `publish_geometry` (function, line 13139) `static void publish_geometry(browser_window *w, const rc_layout *L, double left,
                ...`
  - `paint_screen_inflow` (function, line 13219) `static void paint_screen_inflow(const screen_flow_ctx *c, int only_root)`
  - `paint_screen_deferred` (function, line 13333) `static void paint_screen_deferred(void *ctx, int root)`
  - `paint_structured` (function, line 13337) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
  - `write_doc_pdf` (function, line 13452) `static long write_doc_pdf(browser_window *w, const char *path)`
  - `export_pdf` (function, line 13560) `static void export_pdf(browser_window *w)`
  - `paint_png_inflow` (function, line 13632) `static void paint_png_inflow(const png_flow_ctx *c, int only_root)`
  - `paint_png_deferred` (function, line 13661) `static void paint_png_deferred(void *ctx, int root)`
  - `write_doc_png` (function, line 13670) `static long write_doc_png(browser_window *w, const char *path)`
  - `export_png` (function, line 13768) `static void export_png(browser_window *w)`
  - `caller` (function, line 13802) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
  - `ui_render_png` (function, line 13825) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)`
  - `render_doc_images` (function, line 13885) `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...`
  - `ui_render_png_images` (function, line 13916) `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_pdf_images` (function, line 13922) `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_dump_layout` (function, line 13937) `ui_status ui_dump_layout(const rd_doc *doc)`
  - `link_at_point` (function, line 14009) `static const char *link_at_point(browser_window *w, double px, double py)`
  - `resolve_box_cursor` (function, line 14100) `static int resolve_box_cursor(const rd_doc *doc, int block_id)`
  - `box_pointer_events_none` (function, line 14114) `static int box_pointer_events_none(const rd_doc *doc, int block_id)`
  - `cursor_at_point` (function, line 14130) `static int cursor_at_point(browser_window *w, double px, double py)`
  - `node_at_point` (function, line 14195) `static dom_node_id node_at_point(browser_window *w, double px, double py)`
  - `Firefox` (function, line 14203) `* on its face does in Firefox (spec/page_view.md, tanda 40). */
static const rd_block *submit_pro...`
  - `frag_at_point` (function, line 14222) `static dom_node_id frag_at_point(browser_window *w, double px, double py,
                       ...`
  - `reference` (function, line 14276) `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
  - `set_page_url` (function, line 14295) `static void set_page_url(browser_window *w, const char *url)`
  - `ws_apply_ops` (function, line 14320) `static void ws_apply_ops(browser_window *w, const tab_page *page)`
  - `apply_history_ops` (function, line 14355) `static void apply_history_ops(browser_window *w, const tab_page *page)`
  - `history_step` (function, line 14367) `static void history_step(browser_window *w, int steps)`
  - `apply_click_result` (function, line 14400) `static int apply_click_result(browser_window *w, tab_page *page)`
  - `memory` (function, line 14450) `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
  - `GET` (function, line 14544) `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
  - `ensure_download_dir` (function, line 14578) `static int ensure_download_dir(char *out, size_t outsz)`
  - `write_file_atomic` (function, line 14593) `static int write_file_atomic(const char *path, const void *bytes, size_t len)`
  - `save_download` (function, line 14615) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...`
  - `save_current_page` (function, line 14648) `static void save_current_page(browser_window *w)`
  - `deliver_fetch_result` (function, line 14658) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
  - `drain_fetch_results` (function, line 14712) `static void drain_fetch_results(browser_window *w)`
  - `toggle_reader` (function, line 14788) `static void toggle_reader(browser_window *w)`
  - `menu_item_checked` (function, line 14799) `static int menu_item_checked(const browser_window *w, size_t i)`
  - `menu_item_toggle` (function, line 14821) `static void menu_item_toggle(browser_window *w, size_t i)`
  - `draw_clock` (function, line 14931) `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...`
  - `draw_hamburger` (function, line 14943) `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_reload` (function, line 14959) `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_menu` (function, line 14981) `static void draw_menu(cairo_t *cr, browser_window *w)`
  - `draw_hover_url` (function, line 15092) `static double draw_hover_url(cairo_t *cr, browser_window *w)`
  - `draw_toast` (function, line 15124) `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)`
  - `draw_tabstrip` (function, line 15154) `static void draw_tabstrip(cairo_t *cr, browser_window *w)`
  - `draw_omnibox` (function, line 15209) `static void draw_omnibox(cairo_t *cr, browser_window *w)`
  - `paint` (function, line 15243) `static void paint(browser_window *w)`
  - `redraw` (function, line 15487) `static void redraw(browser_window *w)`
  - `wm_base_ping` (function, line 15499) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 15505) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 15513) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `wl_array_for_each` (function, line 15529) `wl_array_for_each(st, states)`
  - `toplevel_close` (function, line 15535) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 15544) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `set_cursor` (function, line 15556) `static void set_cursor(browser_window *w, int cur_kind)`
  - `element` (function, line 15586) `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...`
  - `fbw_split_y` (function, line 15656) `static double fbw_split_y(const freebug_window *fb)`
  - `freebug_ensure_buffer` (function, line 15665) `static int freebug_ensure_buffer(freebug_window *fb)`
  - `fbw_level_rgb` (function, line 15692) `static void fbw_level_rgb(int level, double *r, double *g, double *b)`
  - `fbw_console_lines` (function, line 15703) `static size_t fbw_console_lines(const fb_buffer *log)`
  - `freebug_paint` (function, line 15716) `static void freebug_paint(freebug_window *fb)`
  - `freebug_redraw_fb` (function, line 15915) `static void freebug_redraw_fb(freebug_window *fb)`
  - `freebug_redraw` (function, line 15924) `static void freebug_redraw(browser_window *w)`
  - `freebug_hide` (function, line 15928) `static void freebug_hide(browser_window *w)`
  - `fbw_xdg_surface_configure` (function, line 15944) `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `fbw_toplevel_configure` (function, line 15952) `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...`
  - `fbw_toplevel_close` (function, line 15961) `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)`
  - `freebug_show` (function, line 15971) `static void freebug_show(browser_window *w)`
  - `freebug_toggle` (function, line 16001) `static void freebug_toggle(browser_window *w)`
  - `freebug_destroy` (function, line 16006) `static void freebug_destroy(browser_window *w)`
  - `freebug_owns_surface` (function, line 16013) `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)`
  - `freebug_is_open` (function, line 16017) `static int freebug_is_open(const browser_window *w)`
  - `freebug_repl_worker` (function, line 16024) `static tab *freebug_repl_worker(browser_window *w)`
  - `freebug_eval` (function, line 16062) `static void freebug_eval(browser_window *w)`
  - `freebug_handle_key` (function, line 16102) `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,

Next: [KB_gui_p2.md](KB_gui_p2.md)
