# Subsystem: gui (page 1 of 2)
Pages: [KB_gui.md](KB_gui.md), [KB_gui_p2.md](KB_gui_p2.md)

## gui/browser_ui.c
- Doc: ui_input_state: Live editable state for one form text control, aliasing a block of the current...
- Layer: presentation
- Language: c
- Symbols:
  - `ui_menu_item` (struct, line 194)
  - `ui_input_state` (struct, line 233)
  - `ui_image` (struct, line 257)
  - `ui_bg_image` (struct, line 271)
  - `tab_ctx` (struct, line 288)
  - `browser_window` (struct, line 304)
  - `repl_edges` (struct, line 1127)
  - `fetch_prep` (struct, line 1700)
  - `fetch_job` (struct, line 1780)
  - `rc_frag` (struct, line 3198)
  - `rc_row` (struct, line 3263)
  - `rc_box` (struct, line 3286)
  - `rc_oof_sub` (struct, line 3347)
  - `rc_layout` (struct, line 3349)
  - `rc_oof_sub` (struct, line 3395)
  - `rc_open_box` (struct, line 3405)
  - `rc_ibox` (struct, line 3458)
  - `rc_state` (struct, line 3494)
  - `rc_ext` (struct, line 4137)
  - `item_sides` (struct, line 5247)
  - `rc_defer_col` (struct, line 8136)
  - `rc_defer` (struct, line 8143)
  - `bui_mask_ctx` (struct, line 12876)
  - `screen_flow_ctx` (struct, line 13974)
  - `png_flow_ctx` (struct, line 14481)
  - `freebug_window` (struct, line 16573)
  - `ui_menu_action` (enum, line 176)
  - `ui_hot` (enum, line 226)
  - `rc_rowkind` (enum, line 3261)
  - `bs` (type_alias, line 288) `typedef struct tab_ctx { browser_state bs;`
  - `freebug_window` (type_alias, line 580) `typedef struct freebug_window freebug_window;`
  - `pl` (type_alias, line 1127) `typedef struct repl_edges { double mt, mr, mb, ml, bt, br, bb, bl, pt, pr, pb, pl;`
  - `allowlisted` (type_alias, line 1700) `typedef struct fetch_prep { int allowlisted;`
  - `font_size` (type_alias, line 3197) `typedef struct rc_frag { double x, width, font_size;`
  - `kind` (type_alias, line 3262) `typedef struct rc_row { rc_rowkind kind;`
  - `h` (type_alias, line 3286) `typedef struct rc_box { double x, top, w, h;`
  - `block_id` (type_alias, line 3405) `typedef struct rc_open_box { int block_id;`
  - `col_founder_box` (type_alias, line 3493) `typedef struct rc_state { /* Inside a float band column whose width was SHRUNK TO FIT: the float * founder's own box...`
  - `family` (type_alias, line 4137) `typedef struct rc_ext { int family;`
  - `mr` (type_alias, line 5247) `typedef struct item_sides { double ml, mr;`
  - `key` (type_alias, line 8136) `typedef struct rc_defer_col { int key;`
  - `col` (type_alias, line 8143) `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];`
  - `now_ms` (function, line 164) `static uint64_t now_ms(void)`
  - `gutter` (function, line 600) `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
  - `apply_zoom` (function, line 620) `static void apply_zoom(browser_window *w)`
  - `buffer_release` (function, line 631) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 637) `static void destroy_buffer(browser_window *w)`
  - `ensure_buffer` (function, line 643) `static int ensure_buffer(browser_window *w)`
  - `read_file` (function, line 673) `static char *read_file(const char *path, size_t *out_len)`
  - `build_file_origin` (function, line 712) `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)`
  - `build_host_filter` (function, line 726) `static hb_set *build_host_filter(void)`
  - `build_js_filter` (function, line 742) `static hb_set *build_js_filter(void)`
  - `build_impersonate_optin` (function, line 745) `static int build_impersonate_optin(void)`
  - `freedom_write_dir` (function, line 754) `static int freedom_write_dir(char *out, size_t cap)`
  - `add_current_host_to_list` (function, line 779) `static void add_current_host_to_list(browser_window *w, int sel)`
  - `load_favorites` (function, line 848) `static void load_favorites(browser_window *w)`
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
  - `toggle_fullscreen` (function, line 1036) `static void toggle_fullscreen(browser_window *w)`
  - `input_is_interactive` (function, line 1051) `static int input_is_interactive(int input_type)`
  - `input_is_editable` (function, line 1057) `static int input_is_editable(int input_type)`
  - `free_inputs` (function, line 1063) `static void free_inputs(browser_window *w)`
  - `free_images` (function, line 1071) `static void free_images(browser_window *w)`
  - `find_bg_image` (function, line 1110) `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)`
  - `replaced_edges` (function, line 1134) `static repl_edges replaced_edges(const rd_doc *doc, const rd_block *b, double cb_w)`
  - `repl_edges_x` (function, line 1158) `static double repl_edges_x(const repl_edges *e)`
  - `repl_edges_y` (function, line 1162) `static double repl_edges_y(const repl_edges *e)`
  - `image_display_size` (function, line 1196) `static int image_display_size(const browser_window *w, const rd_block *blk,
                     ...`
  - `placeholder_display_size` (function, line 1262) `static int placeholder_display_size(const rd_block *blk, double box_w,
                          ...`
  - `rebuild_inputs` (function, line 1285) `static void rebuild_inputs(browser_window *w)`
  - `find_input_state` (function, line 1310) `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)`
  - `clear_doc` (function, line 1318) `static void clear_doc(browser_window *w)`
  - `set_cache` (function, line 1328) `static void set_cache(browser_window *w, char *html, size_t len, const char *top)`
  - `surface_from_pixels` (function, line 1340) `static cairo_surface_t *surface_from_pixels(const tab_image *img)`
  - `fetch_follow_navigable` (function, line 1400) `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...`
  - `fetch_get_cached` (function, line 1408) `static sf_status fetch_get_cached(const browser_window *w, const char *url, sf_config *cfg,
     ...`
  - `fetch_post_navigable` (function, line 1416) `static sf_status fetch_post_navigable(const char *url, sf_config *cfg,
                          ...`
  - `gui_subresource_fetch` (function, line 1440) `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...`
  - `gui_css_sink` (function, line 1529) `static void gui_css_sink(void *vctx, const char *url,
                         const char *body, ...`
  - `first` (function, line 1597) `* Navigation: clear the registry first (faces are per document). Untrusted:
 * no-op (fetch NULL)...`
  - `prepare_fetch` (function, line 1709) `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...`
  - `fetch_job_free` (function, line 1812) `static void fetch_job_free(fetch_job *j)`
  - `stream_progress_cb` (function, line 1832) `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)`
  - `fetch_thread` (function, line 1856) `static void *fetch_thread(void *arg)`
  - `fetch_launch` (function, line 1904) `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...`
  - `load_images` (function, line 2033) `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx,
     ...`
  - `load_bg_images` (function, line 2120) `static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
  - `page_js_host_allowlisted` (function, line 2183) `static int page_js_host_allowlisted(const browser_window *w)`
  - `compute_page_js` (function, line 2189) `static int compute_page_js(const browser_window *w)`
  - `seed_session_cookies` (function, line 2203) `static void seed_session_cookies(tab *t, int trusted, const char *url)`
  - `seed_local_storage` (function, line 2227) `static void seed_local_storage(browser_window *w, tab *t, int trusted)`
  - `collect_local_storage` (function, line 2242) `static void collect_local_storage(browser_window *w, const tab_page *page)`
  - `foldback_session_cookies` (function, line 2252) `static void foldback_session_cookies(const char *url, const char *jar)`
  - `drop_repl_worker` (function, line 2278) `static void drop_repl_worker(browser_window *w)`
  - `schedule_js_tick` (function, line 2292) `static void schedule_js_tick(browser_window *w, int next_ms)`
  - `render_current_ex` (function, line 2302) `static void render_current_ex(browser_window *w, int allow_js_nav)`
  - `render_current` (function, line 2481) `static void render_current(browser_window *w)`
  - `show_busy` (function, line 2488) `static void show_busy(browser_window *w)`
  - `show_fetch_error` (function, line 2497) `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...`
  - `identity_load` (function, line 2563) `static void identity_load(browser_window *w)`
  - `arrives` (function, line 2573) `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...`
  - `strcmp` (function, line 2675) `&& strcmp(auth_host_buf, w->auth_host) != 0)`
  - `tab_save` (function, line 2736) `static void tab_save(browser_window *w)`
  - `tab_restore` (function, line 2754) `static void tab_restore(browser_window *w)`
  - `free_live_page` (function, line 2772) `static void free_live_page(browser_window *w)`
  - `tab_ctx_release` (function, line 2784) `static void tab_ctx_release(tab_ctx *c)`
  - `tab_switch` (function, line 2808) `static void tab_switch(browser_window *w, int idx)`
  - `uitab_close` (function, line 2870) `static void uitab_close(browser_window *w, int idx)`
  - `newtab_x` (function, line 2912) `static double newtab_x(const browser_window *w)`
  - `tab_title` (function, line 2919) `static const char *tab_title(const browser_window *w, int i)`
  - `tabbar_top` (function, line 2935) `static double tabbar_top(const browser_window *w)`
  - `toolbar_top` (function, line 2941) `static double toolbar_top(const browser_window *w)`
  - `content_geometry` (function, line 2948) `static void content_geometry(const browser_window *w, double *top, double *height)`
  - `page_side` (function, line 2974) `static double page_side(const browser_window *w, int side)`
  - `content_margin_x` (function, line 2978) `static double content_margin_x(const browser_window *w)`
  - `content_margins_x` (function, line 2989) `static double content_margins_x(const browser_window *w)`
  - `content_width` (function, line 2994) `static double content_width(const browser_window *w)`
  - `html_center_offset` (function, line 3004) `static double html_center_offset(const browser_window *w)`
  - `scrollbar_metrics` (function, line 3018) `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...`
  - `scrollbar_drag_to` (function, line 3046) `static void scrollbar_drag_to(browser_window *w)`
  - `draw_scrollbar` (function, line 3063) `static void draw_scrollbar(cairo_t *cr, const browser_window *w)`
  - `window_button_rects` (function, line 3100) `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...`
  - `toolbar_rects` (function, line 3110) `static void toolbar_rects(const browser_window *w,
                          double *back_x, doub...`
  - `toolbar_button_at` (function, line 3125) `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)`
  - `hot_actionable` (function, line 3141) `static int hot_actionable(const browser_window *w, ui_hot hot)`
  - `menu_panel_rect` (function, line 3152) `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...`
  - `ua_box_rect` (function, line 3168) `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...`
  - `draw_text` (function, line 3178) `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)`
  - `rc_float_bottom` (function, line 3590) `static double rc_float_bottom(const rc_state *s)`
  - `rc_float_clear` (function, line 3599) `static void rc_float_clear(rc_state *s)`
  - `rc_float_refresh` (function, line 3612) `static void rc_float_refresh(rc_state *s, double line_h)`
  - `rc_float_fit_line` (function, line 3658) `static void rc_float_fit_line(rc_state *s, double line_h)`
  - `line_limit` (function, line 3677) `static double line_limit(const rc_state *s, double content_w)`
  - `rc_free` (function, line 3685) `static void rc_free(rc_layout *L)`
  - `rc_add_box` (function, line 3705) `static rc_box *rc_add_box(rc_layout *L)`
  - `rc_add_frag` (function, line 3717) `static rc_frag *rc_add_frag(rc_layout *L)`
  - `rc_add_row` (function, line 3732) `static rc_row *rc_add_row(rc_layout *L)`
  - `family_face` (function, line 3744) `static const char *family_face(int family)`
  - `content_font_ex` (function, line 3766) `static void content_font_ex(cairo_t *cr, double size, int bold, int italic, int family,
         ...`
  - `sites` (function, line 3779) `* sites (wfh 0, local 0) get the bucket face, which is the toy face's twin. */
    if (wfh != 0u ...`
  - `content_font` (function, line 3788) `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,
            ...`
  - `set_rgb_alpha` (function, line 3795) `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)`
  - `utf8_clen` (function, line 3804) `static size_t utf8_clen(const char *s, size_t n)`
  - `draw_slice` (function, line 3837) `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)`
  - `frag_styled` (function, line 3850) `static int frag_styled(const rc_frag *f)`
  - `styled_advance` (function, line 3857) `static double styled_advance(cairo_t *cr, const rc_frag *f)`
  - `styled_draw` (function, line 3879) `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)`
  - `block_style` (function, line 3902) `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
  - `block_margins` (function, line 3930) `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...`
  - `area` (function, line 3967) `* box spans its CONTENT area (the font's ascent + descent plus its vertical padding
 * and border...`
  - `run` (function, line 4020) `* continuation run (block_id < 0 with no block break) deliberately skips reconcile
 * to stay on ...`
  - `flush_line` (function, line 4034) `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `open_line_height` (function, line 4101) `static double open_line_height(const rc_state *s, const ui_theme *th)`
  - `open_line` (function, line 4116) `static void open_line(rc_layout *L, rc_state *s)`
  - `flow_emit_frag` (function, line 4170) `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...`
  - `flow_smallcaps_word` (function, line 4230) `static double flow_smallcaps_word(cairo_t *cr, rc_layout *L, rc_state *s,
                       ...`
  - `ibx_advance` (function, line 4285) `static void ibx_advance(const rc_layout *L, rc_state *s, double adv)`
  - `flow_text` (function, line 4293) `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...`
  - `input_inline_eligible` (function, line 4572) `static int input_inline_eligible(const rd_block *b)`
  - `input_inline_size` (function, line 4586) `static int input_inline_size(cairo_t *cr, const ui_theme *th, const rd_block *b,
                ...`
  - `replaced_inline_size` (function, line 4608) `static int replaced_inline_size(cairo_t *cr, const browser_window *w, const ui_theme *th,
       ...`
  - `replaced_is_inline_level` (function, line 4640) `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)`
  - `inlines` (function, line 4653) `* next run may also be a replaced element without its own break: consecutive
 * atomic inlines (`...`
  - `place_inline_replaced` (function, line 4690) `static int place_inline_replaced(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
    ...`
  - `css_replaced_box` (function, line 4775) `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...`
  - `emit_replaced_row` (function, line 4784) `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `block_text_style` (function, line 4897) `static void block_text_style(const browser_window *w, const ui_theme *th, const rd_block *b,
    ...`
  - `flow_text_block` (function, line 4908) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
  - `run_is_content` (function, line 5064) `static int run_is_content(const rd_block *bk)`
  - `item_root_box_pass` (function, line 5074) `static int item_root_box_pass(const rd_doc *doc, size_t b0, size_t b1, int cbox,
                ...`
  - `them` (function, line 5127) `* to them (jkanime's badge-only tiles keep their box). */
static int item_root_box_in(const rd_do...`
  - `item_root_box` (function, line 5148) `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)`
  - `itself` (function, line 5156) `* STRETCH itself (box_tree fills the line with it). */
static int css_align_to_bt(int align_kw)`
  - `box_edge_px` (function, line 5167) `static double box_edge_px(int wpx)`
  - `rc_box_copy_decoration` (function, line 5187) `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)`
  - `box_is_strict_descendant` (function, line 5280) `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)`
  - `item_sides_at_level` (function, line 5302) `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,
                  ...`
  - `container_box_of` (function, line 5369) `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)`
  - `table` (function, line 5391) `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...`
  - `row` (function, line 5456) `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...`
  - `measure_item_w_at` (function, line 5504) `static double measure_item_w_at(cairo_t *cr, const browser_window *w,
                           ...`
  - `lines_at` (function, line 5554) `static size_t lines_at(cairo_t *cr, const browser_window *w, const ui_theme *th,
                ...`
  - `balanced_wrap_width` (function, line 5572) `static double balanced_wrap_width(cairo_t *cr, const browser_window *w, const ui_theme *th,
     ...`
  - `item_inner_inset` (function, line 5593) `static double item_inner_inset(const rd_doc *doc, size_t b0, size_t b1, int root)`
  - `measure_item_content_w` (function, line 5620) `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
  - `run_width_cap` (function, line 5653) `static double run_width_cap(const rd_block *b, double avail_w)`
  - `def_width_cap` (function, line 5657) `static double def_width_cap(const pv_box_def *d, double avail_w)`
  - `def_declared_width` (function, line 5663) `static double def_declared_width(const pv_box_def *d, double avail_w)`
  - `item_declared_basis` (function, line 5668) `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
  - `nested_cont_basis` (function, line 5682) `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...`
  - `flex_item_basis` (function, line 5756) `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
  - `flex_item_min_main` (function, line 5796) `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...`
  - `item_at_level` (function, line 5861) `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `child_cont_at_level` (function, line 5876) `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `cont_in_view` (function, line 5895) `static int cont_in_view(const rd_doc *doc, int cid)`
  - `root_cont_of` (function, line 5909) `static int root_cont_of(const rd_doc *doc, int cid)`
  - `box_under` (function, line 5920) `static int box_under(const rd_doc *doc, int child, int anc)`
  - `root_cont_in` (function, line 5937) `static int root_cont_in(const rd_doc *doc, int cid, int float_box)`
  - `block_is_oof` (function, line 5981) `static int block_is_oof(const rd_doc *doc, const rd_block *bk)`
  - `item_vmargins` (function, line 6026) `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,
          ...`
  - `container_inner_h` (function, line 6047) `static double container_inner_h(const rd_doc *doc, const pv_cont_def *cdv, double content_w)`
  - `layout_container` (function, line 6087) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `slot` (function, line 6277) `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
  - `path` (function, line 6476) `*
         * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when
        ...`
  - `box_line_visible` (function, line 7077) `static int box_line_visible(int style)`
  - `col_spend_free_space` (function, line 7091) `static void col_spend_free_space(rc_layout *L, const rc_open_box *ob, double free_px)`
  - `close_top_box` (function, line 7136) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `wins` (function, line 7204) `* content taller than the ratio still wins (min-height:auto). */
        if (bx->aspect_num > 0 &...`
  - `rc_box_context` (function, line 7311) `static void rc_box_context(const rc_state *s, double content_w,
                           double...`
  - `box_margin_top` (function, line 7338) `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `box_margin_bottom` (function, line 7345) `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `children` (function, line 7355) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
  - `column` (function, line 7582) `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
  - `box_path_has` (function, line 7676) `static int box_path_has(const rd_doc *doc, int block_id, int want)`
  - `columns` (function, line 7690) `* each card made 1080px columns (huggingface, github). */
static int deepest_open_on_path(const r...`
  - `float_item_stop` (function, line 7707) `static int float_item_stop(const rd_doc *doc, const rd_block *bk, int founder_key, int base_stop)`
  - `nested_stop` (function, line 7726) `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)`
  - `box_shrink_width` (function, line 7738) `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...`
  - `reconcile_boxes_below` (function, line 7814) `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
  - `reconcile_boxes` (function, line 7930) `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
  - `box_path_of` (function, line 7958) `static int box_path_of(const rd_doc *doc, int block_id, int *out)`
  - `oof_static_xy` (function, line 7978) `static void oof_static_xy(const rc_state *s, const ui_theme *th, double content_w,
              ...`
  - `band_parent_box` (function, line 7994) `static int band_parent_box(const rd_doc *doc, const rd_block *bk)`
  - `band_common_box_ex` (function, line 8001) `static int band_common_box_ex(const rd_doc *doc, size_t start, size_t end, int skip_boxless)`
  - `band_common_box` (function, line 8026) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)`
  - `block_in_table_caption` (function, line 8100) `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)`
  - `defer_key_block` (function, line 8164) `static int defer_key_block(const rd_block *bk)`
  - `defer_append` (function, line 8338) `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...`
  - `float_founder_edges` (function, line 8399) `static double float_founder_edges(const rd_doc *doc, int float_box, double ctx_w)`
  - `defer_flush` (function, line 8420) `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...`
  - `layout_float_band` (function, line 8705) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
  - `yet` (function, line 9180) `* does not carry yet (WPT flex-abspos-staticpos-*). */
static int runs_share_float(const rd_doc *...`
  - `layout_doc` (function, line 9192) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
  - `count` (function, line 9694) `* the box count (a hostile parent cycle terminates). */
static int oof_depth(const rd_doc *doc, s...`
  - `approximation` (function, line 9713) `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */
static void oof_s...`
  - `position_doc` (function, line 9927) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
  - `defer_root_of` (function, line 10105) `static int defer_root_of(const rc_layout *L, int bid)`
  - `defer_wants` (function, line 10113) `static int defer_wants(const rc_layout *L, int bid, int only_root)`
  - `input_box_width` (function, line 10119) `static double input_box_width(double content_w)`
  - `select_box_width` (function, line 10123) `static double select_box_width(double content_w)`
  - `button_box_width` (function, line 10128) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...`
  - `blit_image_box` (function, line 10573) `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,
                 ...`
  - `v_read` (function, line 10764) `static int v_read(int fd, void *buf, size_t n)`
  - `dies` (function, line 10792) `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
  - `audio_spawn` (function, line 10801) `static void audio_spawn(browser_window *w, int rate, int channels)`
  - `audio_mark_dead` (function, line 10855) `static void audio_mark_dead(browser_window *w)`
  - `audio_write` (function, line 10872) `static void audio_write(browser_window *w, const uint8_t *data, size_t len)`
  - `audio_stop` (function, line 10887) `static void audio_stop(browser_window *w)`
  - `video_stop` (function, line 10907) `static void video_stop(browser_window *w)`
  - `video_fetch` (function, line 11085) `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...`
  - `video_play` (function, line 11102) `static int video_play(browser_window *w, const char *m3u8_url)`
  - `video_stop` (function, line 11204) `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
  - `paint_video_row` (function, line 11258) `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
  - `row_line_slack` (function, line 11370) `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)`
  - `row_align_offset` (function, line 11382) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)`
  - `upstream` (function, line 11410) `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
  - `box_path` (function, line 11438) `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `paint_box_shadow_layer` (function, line 11449) `static void paint_box_shadow_layer(cairo_t *cr, double x, double y, double w, double h,
         ...`
  - `text` (function, line 11540) `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
  - `grad_stop` (function, line 11567) `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)`
  - `bui_grad_color_at` (function, line 11582) `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...`
  - `spaced` (function, line 11615) `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
  - `paint_bg_layer` (function, line 11648) `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...`
  - `paint_gradient_fill` (function, line 11694) `static void paint_gradient_fill(cairo_t *cr, const rc_box *bx, double x, double y,
              ...`
  - `paint_gradient_tiled` (function, line 11741) `static void paint_gradient_tiled(cairo_t *cr, const rc_box *bx, double x, double y,
             ...`
  - `paint_box_decoration` (function, line 11768) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
  - `widths` (function, line 11893) `* the outer minus the adjacent border widths (CSS Backgrounds 3 5.2). The straight
     * per-sid...`
  - `cairo_set_dash` (function, line 11929) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11932) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11978) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11981) `cairo_set_dash(cr, (double[])`
  - `set_rgb` (function, line 12015) `set_rgb(cr, (ui_rgb)`
  - `cairo_set_dash` (function, line 12039) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 12042) `cairo_set_dash(cr, (double[])`
  - `paint_deco_line` (function, line 12100) `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...`
  - `cairo_set_dash` (function, line 12134) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 12136) `cairo_set_dash(cr, (double[])`
  - `paint_svg_at` (function, line 12156) `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...`
  - `replaced_current_color` (function, line 12176) `static int replaced_current_color(const browser_window *w, const rd_block *blk)`
  - `paint_inline_replaced` (function, line 12185) `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...`
  - `paint_content_row` (function, line 12230) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
  - `paint_content_row_ex` (function, line 12237) `static void paint_content_row_ex(cairo_t *cr, browser_window *w, const rc_layout *L,
            ...`
  - `ov_box_clips` (function, line 12448) `static int ov_box_clips(const pv_box_def *d)`
  - `ov_collect_chain` (function, line 12455) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)`
  - `ov_box_bounds` (function, line 12476) `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)`
  - `ov_content_rect` (function, line 12502) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...`
  - `fragment` (function, line 12518) `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
  - `box_forms_stacking_context` (function, line 12573) `static int box_forms_stacking_context(const pv_box_def *def)`
  - `bui_skew_tan` (function, line 12617) `static double bui_skew_tan(int deg)`
  - `box_transform_matrix` (function, line 12624) `static int box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
              ...`
  - `bui_blend_operator` (function, line 12752) `static cairo_operator_t bui_blend_operator(int mix_blend)`
  - `bui_gaussian_blur_surface` (function, line 12778) `static void bui_gaussian_blur_surface(cairo_surface_t *surf, double sigma)`
  - `bui_paint_backdrop_blur` (function, line 12814) `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...`
  - `bui_mask_ref_rect` (function, line 12883) `static int bui_mask_ref_rect(const rc_layout *L, int ref, rc_box *out)`
  - `bui_build_mask` (function, line 12899) `static cairo_surface_t *bui_build_mask(const pv_box_def *def, const rc_box *bx_in,
              ...`
  - `bui_pop_group_composite` (function, line 13005) `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms,
    ...`
  - `limits` (function, line 13257) `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
  - `paint_box_decoration_grouped` (function, line 13326) `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
  - `paint_box_and_direct_rows` (function, line 13367) `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...`
  - `bui_pop_group_composite` (function, line 13443) `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
  - `paint_oof_sub` (function, line 13497) `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,
                ...`
  - `paint_positioned_one` (function, line 13535) `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...`
  - `box` (function, line 13656) `* content belongs to that box (painted by its own positioned entry). */
    if (sub == NULL)`
  - `paint_owned_negz` (function, line 13761) `static void paint_owned_negz(cairo_t *cr, browser_window *w, rc_layout *L, double left,
         ...`
  - `paint_nested_children` (function, line 13777) `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...`
  - `bui_pop_group_composite` (function, line 13800) `bui_pop_group_composite(cr, cdef, now_ms() - w->page_load_mono_ms, &L->boxes[j], left, origin,
  ...`
  - `geom_from_layout` (function, line 13815) `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,
                ...`
  - `publish_geometry` (function, line 13846) `static void publish_geometry(browser_window *w, const rc_layout *L, double left,
                ...`
  - `defer_root_z` (function, line 13908) `static int defer_root_z(const rd_doc *doc, size_t root)`
  - `defer_root_before` (function, line 13914) `static int defer_root_before(const rd_doc *doc, const rc_layout *L, size_t a, size_t b)`
  - `paint_positioned_layer` (function, line 13920) `static void paint_positioned_layer(cairo_t *cr, browser_window *w, const ui_theme *th,
          ...`
  - `paint_screen_inflow` (function, line 13985) `static void paint_screen_inflow(const screen_flow_ctx *c, int only_root)`
  - `bui_pop_group_composite` (function, line 14052) `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
  - `lazy_slot` (function, line 14106) `static ui_image *lazy_slot(browser_window *w, const char *href, size_t *idx)`
  - `lazy_load_one` (function, line 14117) `static void lazy_load_one(browser_window *w, ui_image *slot, const rd_block *b)`
  - `paint_screen_deferred` (function, line 14171) `static void paint_screen_deferred(void *ctx, int root)`
  - `paint_structured` (function, line 14175) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
  - `write_doc_pdf` (function, line 14301) `static long write_doc_pdf(browser_window *w, const char *path)`
  - `export_pdf` (function, line 14410) `static void export_pdf(browser_window *w)`
  - `ui_render_viewport_w` (function, line 14465) `int ui_render_viewport_w(void)`
  - `paint_png_inflow` (function, line 14493) `static void paint_png_inflow(const png_flow_ctx *c, int only_root)`
  - `paint_png_deferred` (function, line 14529) `static void paint_png_deferred(void *ctx, int root)`
  - `write_doc_png` (function, line 14538) `static long write_doc_png(browser_window *w, const char *path)`
  - `export_png` (function, line 14638) `static void export_png(browser_window *w)`
  - `caller` (function, line 14672) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
  - `ui_render_png` (function, line 14695) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)`
  - `render_doc_images` (function, line 14755) `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...`
  - `ui_render_png_images` (function, line 14786) `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_pdf_images` (function, line 14792) `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_dump_layout` (function, line 14807) `ui_status ui_dump_layout(const rd_doc *doc)`
  - `link_at_point` (function, line 14879) `static const char *link_at_point(browser_window *w, double px, double py)`
  - `resolve_box_cursor` (function, line 14970) `static int resolve_box_cursor(const rd_doc *doc, int block_id)`
  - `box_pointer_events_none` (function, line 14984) `static int box_pointer_events_none(const rd_doc *doc, int block_id)`
  - `cursor_at_point` (function, line 15000) `static int cursor_at_point(browser_window *w, double px, double py)`
  - `node_at_point` (function, line 15065) `static dom_node_id node_at_point(browser_window *w, double px, double py)`
  - `Firefox` (function, line 15073) `* on its face does in Firefox (spec/page_view.md, tanda 40). */
static const rd_block *submit_pro...`
  - `frag_at_point` (function, line 15092) `static dom_node_id frag_at_point(browser_window *w, double px, double py,
                       ...`
  - `reference` (function, line 15146) `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
  - `set_page_url` (function, line 15165) `static void set_page_url(browser_window *w, const char *url)`
  - `ws_apply_ops` (function, line 15191) `static void ws_apply_ops(browser_window *w, const tab_page *page)`
  - `apply_history_ops` (function, line 15226) `static void apply_history_ops(browser_window *w, const tab_page *page)`
  - `history_step` (function, line 15238) `static void history_step(browser_window *w, int steps)`
  - `apply_click_result` (function, line 15271) `static int apply_click_result(browser_window *w, tab_page *page)`
  - `on_tab_async` (function, line 15320) `static void on_tab_async(browser_window *w)`
  - `gui_quiesce` (function, line 15333) `static void gui_quiesce(browser_window *w)`
  - `memory` (function, line 15341) `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
  - `GET` (function, line 15435) `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
  - `ensure_download_dir` (function, line 15469) `static int ensure_download_dir(char *out, size_t outsz)`
  - `write_file_atomic` (function, line 15484) `static int write_file_atomic(const char *path, const void *bytes, size_t len)`
  - `save_download` (function, line 15506) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...`
  - `save_current_page` (function, line 15539) `static void save_current_page(browser_window *w)`
  - `deliver_fetch_result` (function, line 15549) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
  - `drain_fetch_results` (function, line 15603) `static void drain_fetch_results(browser_window *w)`
  - `toggle_reader` (function, line 15708) `static void toggle_reader(browser_window *w)`
  - `menu_item_checked` (function, line 15719) `static int menu_item_checked(const browser_window *w, size_t i)`
  - `menu_item_toggle` (function, line 15741) `static void menu_item_toggle(browser_window *w, size_t i)`
  - `draw_clock` (function, line 15856) `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,

Next: [KB_gui_p2.md](KB_gui_p2.md)
