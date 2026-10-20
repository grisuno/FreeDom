# Subsystem: gui (page 1 of 2)
Pages: [KB_gui.md](KB_gui.md), [KB_gui_p2.md](KB_gui_p2.md)

## gui/browser_ui.c
- Doc: ui_input_state: Live editable state for one form text control, aliasing a block of the current...
- Layer: presentation
- Language: c
- Symbols:
  - `ui_menu_item` (struct, line 191)
  - `ui_input_state` (struct, line 229)
  - `ui_image` (struct, line 253)
  - `ui_bg_image` (struct, line 266)
  - `tab_ctx` (struct, line 283)
  - `browser_window` (struct, line 299)
  - `repl_edges` (struct, line 1116)
  - `fetch_prep` (struct, line 1725)
  - `fetch_job` (struct, line 1806)
  - `rc_frag` (struct, line 3148)
  - `rc_row` (struct, line 3213)
  - `rc_box` (struct, line 3236)
  - `rc_oof_sub` (struct, line 3295)
  - `rc_layout` (struct, line 3297)
  - `rc_oof_sub` (struct, line 3343)
  - `rc_open_box` (struct, line 3353)
  - `rc_ibox` (struct, line 3406)
  - `rc_state` (struct, line 3442)
  - `rc_ext` (struct, line 4085)
  - `item_sides` (struct, line 5191)
  - `rc_defer_col` (struct, line 8057)
  - `rc_defer` (struct, line 8064)
  - `bui_mask_ctx` (struct, line 12678)
  - `screen_flow_ctx` (struct, line 13725)
  - `png_flow_ctx` (struct, line 14140)
  - `freebug_window` (struct, line 16169)
  - `ui_menu_action` (enum, line 174)
  - `ui_hot` (enum, line 222)
  - `rc_rowkind` (enum, line 3211)
  - `bs` (type_alias, line 283) `typedef struct tab_ctx { browser_state bs;`
  - `freebug_window` (type_alias, line 571) `typedef struct freebug_window freebug_window;`
  - `pl` (type_alias, line 1116) `typedef struct repl_edges { double mt, mr, mb, ml, bt, br, bb, bl, pt, pr, pb, pl;`
  - `allowlisted` (type_alias, line 1725) `typedef struct fetch_prep { int allowlisted;`
  - `font_size` (type_alias, line 3147) `typedef struct rc_frag { double x, width, font_size;`
  - `kind` (type_alias, line 3212) `typedef struct rc_row { rc_rowkind kind;`
  - `h` (type_alias, line 3236) `typedef struct rc_box { double x, top, w, h;`
  - `block_id` (type_alias, line 3353) `typedef struct rc_open_box { int block_id;`
  - `col_founder_box` (type_alias, line 3441) `typedef struct rc_state { /* Inside a float band column whose width was SHRUNK TO FIT: the float * founder's own box...`
  - `family` (type_alias, line 4085) `typedef struct rc_ext { int family;`
  - `mr` (type_alias, line 5191) `typedef struct item_sides { double ml, mr;`
  - `key` (type_alias, line 8057) `typedef struct rc_defer_col { int key;`
  - `col` (type_alias, line 8064) `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];`
  - `now_ms` (function, line 162) `static uint64_t now_ms(void)`
  - `gutter` (function, line 590) `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
  - `apply_zoom` (function, line 610) `static void apply_zoom(browser_window *w)`
  - `buffer_release` (function, line 621) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 627) `static void destroy_buffer(browser_window *w)`
  - `ensure_buffer` (function, line 633) `static int ensure_buffer(browser_window *w)`
  - `read_file` (function, line 663) `static char *read_file(const char *path, size_t *out_len)`
  - `build_file_origin` (function, line 702) `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)`
  - `build_host_filter` (function, line 716) `static hb_set *build_host_filter(void)`
  - `build_js_filter` (function, line 732) `static hb_set *build_js_filter(void)`
  - `build_impersonate_optin` (function, line 735) `static int build_impersonate_optin(void)`
  - `freedom_write_dir` (function, line 744) `static int freedom_write_dir(char *out, size_t cap)`
  - `add_current_host_to_list` (function, line 769) `static void add_current_host_to_list(browser_window *w, int sel)`
  - `load_favorites` (function, line 837) `static void load_favorites(browser_window *w)`
  - `omni_refresh` (function, line 874) `static void omni_refresh(browser_window *w)`
  - `profile_sync` (function, line 905) `static void profile_sync(browser_window *w)`
  - `remember_visit` (function, line 922) `static void remember_visit(browser_window *w, const char *url)`
  - `bookmark_toggle_current` (function, line 930) `static void bookmark_toggle_current(browser_window *w)`
  - `proxy_addr_from_env` (function, line 954) `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...`
  - `init_net_config` (function, line 968) `static void init_net_config(browser_window *w)`
  - `is_https_url` (function, line 978) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 982) `static int is_http_url(const char *s)`
  - `host_from_url` (function, line 993) `static int host_from_url(const char *url, char *out, size_t outsz)`
  - `toggle_fullscreen` (function, line 1025) `static void toggle_fullscreen(browser_window *w)`
  - `input_is_interactive` (function, line 1040) `static int input_is_interactive(int input_type)`
  - `input_is_editable` (function, line 1046) `static int input_is_editable(int input_type)`
  - `free_inputs` (function, line 1052) `static void free_inputs(browser_window *w)`
  - `free_images` (function, line 1060) `static void free_images(browser_window *w)`
  - `find_bg_image` (function, line 1099) `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)`
  - `replaced_edges` (function, line 1123) `static repl_edges replaced_edges(const rd_doc *doc, const rd_block *b, double cb_w)`
  - `repl_edges_x` (function, line 1147) `static double repl_edges_x(const repl_edges *e)`
  - `repl_edges_y` (function, line 1151) `static double repl_edges_y(const repl_edges *e)`
  - `image_display_size` (function, line 1185) `static int image_display_size(const browser_window *w, const rd_block *blk,
                     ...`
  - `placeholder_display_size` (function, line 1251) `static int placeholder_display_size(const rd_block *blk, double box_w,
                          ...`
  - `rebuild_inputs` (function, line 1274) `static void rebuild_inputs(browser_window *w)`
  - `find_input_state` (function, line 1299) `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)`
  - `clear_doc` (function, line 1307) `static void clear_doc(browser_window *w)`
  - `set_cache` (function, line 1317) `static void set_cache(browser_window *w, char *html, size_t len, const char *top)`
  - `surface_from_pixels` (function, line 1328) `static cairo_surface_t *surface_from_pixels(const tab_image *img)`
  - `fetch_follow_navigable` (function, line 1395) `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...`
  - `GET` (function, line 1431) `* a GET (Zero Trust). cfg->policy is restored before returning. */
static sf_status fetch_post_na...`
  - `gui_subresource_fetch` (function, line 1472) `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...`
  - `gui_css_sink` (function, line 1556) `static void gui_css_sink(void *vctx, const char *url,
                         const char *body, ...`
  - `first` (function, line 1624) `* Navigation: clear the registry first (faces are per document). Untrusted:
 * no-op (fetch NULL)...`
  - `prepare_fetch` (function, line 1734) `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...`
  - `fetch_job_free` (function, line 1838) `static void fetch_job_free(fetch_job *j)`
  - `stream_progress_cb` (function, line 1858) `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)`
  - `fetch_thread` (function, line 1882) `static void *fetch_thread(void *arg)`
  - `fetch_launch` (function, line 1930) `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...`
  - `load_images` (function, line 2051) `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
  - `load_bg_images` (function, line 2135) `static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
  - `page_js_host_allowlisted` (function, line 2198) `static int page_js_host_allowlisted(const browser_window *w)`
  - `compute_page_js` (function, line 2204) `static int compute_page_js(const browser_window *w)`
  - `seed_session_cookies` (function, line 2218) `static void seed_session_cookies(tab *t, int trusted, const char *url)`
  - `seed_local_storage` (function, line 2242) `static void seed_local_storage(browser_window *w, tab *t, int trusted)`
  - `collect_local_storage` (function, line 2257) `static void collect_local_storage(browser_window *w, const tab_page *page)`
  - `foldback_session_cookies` (function, line 2267) `static void foldback_session_cookies(const char *url, const char *jar)`
  - `drop_repl_worker` (function, line 2293) `static void drop_repl_worker(browser_window *w)`
  - `schedule_js_tick` (function, line 2307) `static void schedule_js_tick(browser_window *w, int next_ms)`
  - `render_current_ex` (function, line 2317) `static void render_current_ex(browser_window *w, int allow_js_nav)`
  - `render_current` (function, line 2495) `static void render_current(browser_window *w)`
  - `show_busy` (function, line 2502) `static void show_busy(browser_window *w)`
  - `show_fetch_error` (function, line 2511) `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...`
  - `arrives` (function, line 2562) `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...`
  - `strcmp` (function, line 2630) `&& strcmp(auth_host_buf, w->auth_host) != 0)`
  - `tab_save` (function, line 2691) `static void tab_save(browser_window *w)`
  - `tab_restore` (function, line 2708) `static void tab_restore(browser_window *w)`
  - `free_live_page` (function, line 2725) `static void free_live_page(browser_window *w)`
  - `tab_ctx_release` (function, line 2736) `static void tab_ctx_release(tab_ctx *c)`
  - `tab_switch` (function, line 2760) `static void tab_switch(browser_window *w, int idx)`
  - `uitab_close` (function, line 2820) `static void uitab_close(browser_window *w, int idx)`
  - `newtab_x` (function, line 2862) `static double newtab_x(const browser_window *w)`
  - `tab_title` (function, line 2869) `static const char *tab_title(const browser_window *w, int i)`
  - `tabbar_top` (function, line 2885) `static double tabbar_top(const browser_window *w)`
  - `toolbar_top` (function, line 2891) `static double toolbar_top(const browser_window *w)`
  - `content_geometry` (function, line 2898) `static void content_geometry(const browser_window *w, double *top, double *height)`
  - `page_side` (function, line 2924) `static double page_side(const browser_window *w, int side)`
  - `content_margin_x` (function, line 2928) `static double content_margin_x(const browser_window *w)`
  - `content_margins_x` (function, line 2939) `static double content_margins_x(const browser_window *w)`
  - `content_width` (function, line 2944) `static double content_width(const browser_window *w)`
  - `html_center_offset` (function, line 2954) `static double html_center_offset(const browser_window *w)`
  - `scrollbar_metrics` (function, line 2968) `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...`
  - `scrollbar_drag_to` (function, line 2996) `static void scrollbar_drag_to(browser_window *w)`
  - `draw_scrollbar` (function, line 3013) `static void draw_scrollbar(cairo_t *cr, const browser_window *w)`
  - `window_button_rects` (function, line 3050) `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...`
  - `toolbar_rects` (function, line 3060) `static void toolbar_rects(const browser_window *w,
                          double *back_x, doub...`
  - `toolbar_button_at` (function, line 3075) `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)`
  - `hot_actionable` (function, line 3091) `static int hot_actionable(const browser_window *w, ui_hot hot)`
  - `menu_panel_rect` (function, line 3102) `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...`
  - `ua_box_rect` (function, line 3118) `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...`
  - `draw_text` (function, line 3128) `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)`
  - `rc_float_bottom` (function, line 3538) `static double rc_float_bottom(const rc_state *s)`
  - `rc_float_clear` (function, line 3547) `static void rc_float_clear(rc_state *s)`
  - `rc_float_refresh` (function, line 3560) `static void rc_float_refresh(rc_state *s, double line_h)`
  - `rc_float_fit_line` (function, line 3606) `static void rc_float_fit_line(rc_state *s, double line_h)`
  - `line_limit` (function, line 3625) `static double line_limit(const rc_state *s, double content_w)`
  - `rc_free` (function, line 3633) `static void rc_free(rc_layout *L)`
  - `rc_add_box` (function, line 3653) `static rc_box *rc_add_box(rc_layout *L)`
  - `rc_add_frag` (function, line 3665) `static rc_frag *rc_add_frag(rc_layout *L)`
  - `rc_add_row` (function, line 3680) `static rc_row *rc_add_row(rc_layout *L)`
  - `family_face` (function, line 3692) `static const char *family_face(int family)`
  - `content_font_ex` (function, line 3714) `static void content_font_ex(cairo_t *cr, double size, int bold, int italic, int family,
         ...`
  - `sites` (function, line 3727) `* sites (wfh 0, local 0) get the bucket face, which is the toy face's twin. */
    if (wfh != 0u ...`
  - `content_font` (function, line 3736) `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,
            ...`
  - `set_rgb_alpha` (function, line 3743) `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)`
  - `utf8_clen` (function, line 3752) `static size_t utf8_clen(const char *s, size_t n)`
  - `draw_slice` (function, line 3785) `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)`
  - `frag_styled` (function, line 3798) `static int frag_styled(const rc_frag *f)`
  - `styled_advance` (function, line 3805) `static double styled_advance(cairo_t *cr, const rc_frag *f)`
  - `styled_draw` (function, line 3827) `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)`
  - `block_style` (function, line 3850) `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
  - `block_margins` (function, line 3878) `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...`
  - `area` (function, line 3915) `* box spans its CONTENT area (the font's ascent + descent plus its vertical padding
 * and border...`
  - `run` (function, line 3968) `* continuation run (block_id < 0 with no block break) deliberately skips reconcile
 * to stay on ...`
  - `flush_line` (function, line 3982) `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `open_line_height` (function, line 4049) `static double open_line_height(const rc_state *s, const ui_theme *th)`
  - `open_line` (function, line 4064) `static void open_line(rc_layout *L, rc_state *s)`
  - `flow_emit_frag` (function, line 4118) `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...`
  - `flow_smallcaps_word` (function, line 4178) `static double flow_smallcaps_word(cairo_t *cr, rc_layout *L, rc_state *s,
                       ...`
  - `ibx_advance` (function, line 4233) `static void ibx_advance(const rc_layout *L, rc_state *s, double adv)`
  - `flow_text` (function, line 4241) `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...`
  - `input_inline_eligible` (function, line 4520) `static int input_inline_eligible(const rd_block *b)`
  - `input_inline_size` (function, line 4534) `static int input_inline_size(cairo_t *cr, const ui_theme *th, const rd_block *b,
                ...`
  - `replaced_inline_size` (function, line 4556) `static int replaced_inline_size(cairo_t *cr, const browser_window *w, const ui_theme *th,
       ...`
  - `replaced_is_inline_level` (function, line 4588) `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)`
  - `inlines` (function, line 4601) `* next run may also be a replaced element without its own break: consecutive
 * atomic inlines (`...`
  - `place_inline_replaced` (function, line 4638) `static int place_inline_replaced(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
    ...`
  - `css_replaced_box` (function, line 4723) `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...`
  - `emit_replaced_row` (function, line 4732) `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `block_text_style` (function, line 4845) `static void block_text_style(const browser_window *w, const ui_theme *th, const rd_block *b,
    ...`
  - `flow_text_block` (function, line 4856) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
  - `run_is_content` (function, line 5012) `static int run_is_content(const rd_block *bk)`
  - `item_root_box_pass` (function, line 5022) `static int item_root_box_pass(const rd_doc *doc, size_t b0, size_t b1, int cbox,
                ...`
  - `them` (function, line 5075) `* to them (jkanime's badge-only tiles keep their box). */
static int item_root_box_in(const rd_do...`
  - `item_root_box` (function, line 5096) `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)`
  - `itself` (function, line 5104) `* STRETCH itself (box_tree fills the line with it). */
static int css_align_to_bt(int align_kw)`
  - `box_edge_px` (function, line 5115) `static double box_edge_px(int wpx)`
  - `rc_box_copy_decoration` (function, line 5135) `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)`
  - `box_is_strict_descendant` (function, line 5220) `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)`
  - `item_sides_at_level` (function, line 5242) `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,
                  ...`
  - `container_box_of` (function, line 5299) `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)`
  - `table` (function, line 5321) `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...`
  - `row` (function, line 5386) `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...`
  - `measure_item_w_at` (function, line 5434) `static double measure_item_w_at(cairo_t *cr, const browser_window *w,
                           ...`
  - `lines_at` (function, line 5484) `static size_t lines_at(cairo_t *cr, const browser_window *w, const ui_theme *th,
                ...`
  - `balanced_wrap_width` (function, line 5502) `static double balanced_wrap_width(cairo_t *cr, const browser_window *w, const ui_theme *th,
     ...`
  - `item_inner_inset` (function, line 5523) `static double item_inner_inset(const rd_doc *doc, size_t b0, size_t b1, int root)`
  - `measure_item_content_w` (function, line 5550) `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
  - `run_width_cap` (function, line 5583) `static double run_width_cap(const rd_block *b, double avail_w)`
  - `def_width_cap` (function, line 5587) `static double def_width_cap(const pv_box_def *d, double avail_w)`
  - `def_declared_width` (function, line 5593) `static double def_declared_width(const pv_box_def *d, double avail_w)`
  - `item_declared_basis` (function, line 5598) `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
  - `nested_cont_basis` (function, line 5612) `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...`
  - `flex_item_basis` (function, line 5686) `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
  - `flex_item_min_main` (function, line 5726) `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...`
  - `item_at_level` (function, line 5791) `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `child_cont_at_level` (function, line 5806) `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `cont_in_view` (function, line 5825) `static int cont_in_view(const rd_doc *doc, int cid)`
  - `root_cont_of` (function, line 5839) `static int root_cont_of(const rd_doc *doc, int cid)`
  - `box_under` (function, line 5850) `static int box_under(const rd_doc *doc, int child, int anc)`
  - `root_cont_in` (function, line 5867) `static int root_cont_in(const rd_doc *doc, int cid, int float_box)`
  - `block_is_oof` (function, line 5911) `static int block_is_oof(const rd_doc *doc, const rd_block *bk)`
  - `item_vmargins` (function, line 5956) `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,
          ...`
  - `container_inner_h` (function, line 5977) `static double container_inner_h(const rd_doc *doc, const pv_cont_def *cdv, double content_w)`
  - `layout_container` (function, line 6017) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `slot` (function, line 6207) `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
  - `path` (function, line 6406) `*
         * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when
        ...`
  - `box_line_visible` (function, line 6998) `static int box_line_visible(int style)`
  - `col_spend_free_space` (function, line 7012) `static void col_spend_free_space(rc_layout *L, const rc_open_box *ob, double free_px)`
  - `close_top_box` (function, line 7057) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `wins` (function, line 7125) `* content taller than the ratio still wins (min-height:auto). */
        if (bx->aspect_num > 0 &...`
  - `rc_box_context` (function, line 7232) `static void rc_box_context(const rc_state *s, double content_w,
                           double...`
  - `box_margin_top` (function, line 7259) `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `box_margin_bottom` (function, line 7266) `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `children` (function, line 7276) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
  - `column` (function, line 7503) `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
  - `box_path_has` (function, line 7597) `static int box_path_has(const rd_doc *doc, int block_id, int want)`
  - `columns` (function, line 7611) `* each card made 1080px columns (huggingface, github). */
static int deepest_open_on_path(const r...`
  - `float_item_stop` (function, line 7628) `static int float_item_stop(const rd_doc *doc, const rd_block *bk, int founder_key, int base_stop)`
  - `nested_stop` (function, line 7647) `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)`
  - `box_shrink_width` (function, line 7659) `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...`
  - `reconcile_boxes_below` (function, line 7735) `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
  - `reconcile_boxes` (function, line 7851) `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
  - `box_path_of` (function, line 7879) `static int box_path_of(const rd_doc *doc, int block_id, int *out)`
  - `oof_static_xy` (function, line 7899) `static void oof_static_xy(const rc_state *s, const ui_theme *th, double content_w,
              ...`
  - `band_parent_box` (function, line 7915) `static int band_parent_box(const rd_doc *doc, const rd_block *bk)`
  - `band_common_box_ex` (function, line 7922) `static int band_common_box_ex(const rd_doc *doc, size_t start, size_t end, int skip_boxless)`
  - `band_common_box` (function, line 7947) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)`
  - `block_in_table_caption` (function, line 8021) `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)`
  - `defer_key_block` (function, line 8085) `static int defer_key_block(const rd_block *bk)`
  - `defer_append` (function, line 8247) `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...`
  - `float_founder_edges` (function, line 8308) `static double float_founder_edges(const rd_doc *doc, int float_box, double ctx_w)`
  - `defer_flush` (function, line 8329) `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...`
  - `layout_float_band` (function, line 8601) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
  - `yet` (function, line 9076) `* does not carry yet (WPT flex-abspos-staticpos-*). */
static int runs_share_float(const rd_doc *...`
  - `layout_doc` (function, line 9088) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
  - `count` (function, line 9568) `* the box count (a hostile parent cycle terminates). */
static int oof_depth(const rd_doc *doc, s...`
  - `approximation` (function, line 9587) `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */
static void oof_s...`
  - `position_doc` (function, line 9788) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
  - `defer_root_of` (function, line 9966) `static int defer_root_of(const rc_layout *L, int bid)`
  - `defer_wants` (function, line 9974) `static int defer_wants(const rc_layout *L, int bid, int only_root)`
  - `input_box_width` (function, line 9980) `static double input_box_width(double content_w)`
  - `select_box_width` (function, line 9984) `static double select_box_width(double content_w)`
  - `button_box_width` (function, line 9989) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...`
  - `blit_image_box` (function, line 10433) `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,
                 ...`
  - `v_read` (function, line 10624) `static int v_read(int fd, void *buf, size_t n)`
  - `dies` (function, line 10652) `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
  - `audio_spawn` (function, line 10661) `static void audio_spawn(browser_window *w, int rate, int channels)`
  - `audio_mark_dead` (function, line 10715) `static void audio_mark_dead(browser_window *w)`
  - `audio_write` (function, line 10732) `static void audio_write(browser_window *w, const uint8_t *data, size_t len)`
  - `audio_stop` (function, line 10747) `static void audio_stop(browser_window *w)`
  - `video_stop` (function, line 10767) `static void video_stop(browser_window *w)`
  - `video_fetch` (function, line 10945) `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...`
  - `video_play` (function, line 10962) `static int video_play(browser_window *w, const char *m3u8_url)`
  - `video_stop` (function, line 11064) `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
  - `paint_video_row` (function, line 11118) `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
  - `row_line_slack` (function, line 11230) `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)`
  - `row_align_offset` (function, line 11242) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)`
  - `upstream` (function, line 11270) `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
  - `box_path` (function, line 11298) `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `paint_box_shadow_layer` (function, line 11309) `static void paint_box_shadow_layer(cairo_t *cr, double x, double y, double w, double h,
         ...`
  - `text` (function, line 11400) `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
  - `grad_stop` (function, line 11427) `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)`
  - `bui_grad_color_at` (function, line 11442) `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...`
  - `spaced` (function, line 11475) `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
  - `paint_bg_layer` (function, line 11508) `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...`
  - `paint_box_decoration` (function, line 11552) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
  - `widths` (function, line 11695) `* the outer minus the adjacent border widths (CSS Backgrounds 3 5.2). The straight
     * per-sid...`
  - `cairo_set_dash` (function, line 11731) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11734) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11780) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11783) `cairo_set_dash(cr, (double[])`
  - `set_rgb` (function, line 11817) `set_rgb(cr, (ui_rgb)`
  - `cairo_set_dash` (function, line 11841) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11844) `cairo_set_dash(cr, (double[])`
  - `paint_deco_line` (function, line 11902) `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...`
  - `cairo_set_dash` (function, line 11936) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11938) `cairo_set_dash(cr, (double[])`
  - `paint_svg_at` (function, line 11958) `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...`
  - `replaced_current_color` (function, line 11978) `static int replaced_current_color(const browser_window *w, const rd_block *blk)`
  - `paint_inline_replaced` (function, line 11987) `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...`
  - `paint_content_row` (function, line 12032) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
  - `paint_content_row_ex` (function, line 12039) `static void paint_content_row_ex(cairo_t *cr, browser_window *w, const rc_layout *L,
            ...`
  - `ov_box_clips` (function, line 12248) `static int ov_box_clips(const pv_box_def *d)`
  - `ov_collect_chain` (function, line 12255) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)`
  - `ov_box_bounds` (function, line 12276) `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)`
  - `ov_content_rect` (function, line 12300) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...`
  - `fragment` (function, line 12320) `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
  - `box_forms_stacking_context` (function, line 12375) `static int box_forms_stacking_context(const pv_box_def *def)`
  - `bui_skew_tan` (function, line 12419) `static double bui_skew_tan(int deg)`
  - `box_transform_matrix` (function, line 12426) `static int box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
              ...`
  - `bui_blend_operator` (function, line 12554) `static cairo_operator_t bui_blend_operator(int mix_blend)`
  - `bui_gaussian_blur_surface` (function, line 12580) `static void bui_gaussian_blur_surface(cairo_surface_t *surf, double sigma)`
  - `bui_paint_backdrop_blur` (function, line 12616) `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...`
  - `bui_mask_ref_rect` (function, line 12685) `static int bui_mask_ref_rect(const rc_layout *L, int ref, rc_box *out)`
  - `bui_build_mask` (function, line 12701) `static cairo_surface_t *bui_build_mask(const pv_box_def *def, const rc_box *bx_in,
              ...`
  - `bui_pop_group_composite` (function, line 12807) `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms,
    ...`
  - `limits` (function, line 13059) `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
  - `paint_box_decoration_grouped` (function, line 13128) `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
  - `paint_box_and_direct_rows` (function, line 13169) `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...`
  - `bui_pop_group_composite` (function, line 13245) `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
  - `paint_oof_sub` (function, line 13278) `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,
                ...`
  - `paint_positioned_one` (function, line 13316) `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...`
  - `box` (function, line 13431) `* content belongs to that box (painted by its own positioned entry). */
    if (sub == NULL)`
  - `paint_nested_children` (function, line 13537) `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...`
  - `bui_pop_group_composite` (function, line 13560) `bui_pop_group_composite(cr, cdef, now_ms() - w->page_load_mono_ms, &L->boxes[j], left, origin,
  ...`
  - `geom_from_layout` (function, line 13575) `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,
                ...`
  - `publish_geometry` (function, line 13606) `static void publish_geometry(browser_window *w, const rc_layout *L, double left,
                ...`
  - `defer_root_z` (function, line 13659) `static int defer_root_z(const rd_doc *doc, size_t root)`
  - `defer_root_before` (function, line 13665) `static int defer_root_before(const rd_doc *doc, const rc_layout *L, size_t a, size_t b)`
  - `paint_positioned_layer` (function, line 13671) `static void paint_positioned_layer(cairo_t *cr, browser_window *w, const ui_theme *th,
          ...`
  - `paint_screen_inflow` (function, line 13736) `static void paint_screen_inflow(const screen_flow_ctx *c, int only_root)`
  - `bui_pop_group_composite` (function, line 13801) `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
  - `paint_screen_deferred` (function, line 13851) `static void paint_screen_deferred(void *ctx, int root)`
  - `paint_structured` (function, line 13855) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
  - `write_doc_pdf` (function, line 13971) `static long write_doc_pdf(browser_window *w, const char *path)`
  - `export_pdf` (function, line 14080) `static void export_pdf(browser_window *w)`
  - `paint_png_inflow` (function, line 14152) `static void paint_png_inflow(const png_flow_ctx *c, int only_root)`
  - `paint_png_deferred` (function, line 14181) `static void paint_png_deferred(void *ctx, int root)`
  - `write_doc_png` (function, line 14190) `static long write_doc_png(browser_window *w, const char *path)`
  - `export_png` (function, line 14289) `static void export_png(browser_window *w)`
  - `caller` (function, line 14323) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
  - `ui_render_png` (function, line 14346) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)`
  - `render_doc_images` (function, line 14406) `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...`
  - `ui_render_png_images` (function, line 14437) `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_pdf_images` (function, line 14443) `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_dump_layout` (function, line 14458) `ui_status ui_dump_layout(const rd_doc *doc)`
  - `link_at_point` (function, line 14530) `static const char *link_at_point(browser_window *w, double px, double py)`
  - `resolve_box_cursor` (function, line 14621) `static int resolve_box_cursor(const rd_doc *doc, int block_id)`
  - `box_pointer_events_none` (function, line 14635) `static int box_pointer_events_none(const rd_doc *doc, int block_id)`
  - `cursor_at_point` (function, line 14651) `static int cursor_at_point(browser_window *w, double px, double py)`
  - `node_at_point` (function, line 14716) `static dom_node_id node_at_point(browser_window *w, double px, double py)`
  - `Firefox` (function, line 14724) `* on its face does in Firefox (spec/page_view.md, tanda 40). */
static const rd_block *submit_pro...`
  - `frag_at_point` (function, line 14743) `static dom_node_id frag_at_point(browser_window *w, double px, double py,
                       ...`
  - `reference` (function, line 14797) `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
  - `set_page_url` (function, line 14816) `static void set_page_url(browser_window *w, const char *url)`
  - `ws_apply_ops` (function, line 14841) `static void ws_apply_ops(browser_window *w, const tab_page *page)`
  - `apply_history_ops` (function, line 14876) `static void apply_history_ops(browser_window *w, const tab_page *page)`
  - `history_step` (function, line 14888) `static void history_step(browser_window *w, int steps)`
  - `apply_click_result` (function, line 14921) `static int apply_click_result(browser_window *w, tab_page *page)`
  - `memory` (function, line 14971) `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
  - `GET` (function, line 15065) `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
  - `ensure_download_dir` (function, line 15099) `static int ensure_download_dir(char *out, size_t outsz)`
  - `write_file_atomic` (function, line 15114) `static int write_file_atomic(const char *path, const void *bytes, size_t len)`
  - `save_download` (function, line 15136) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...`
  - `save_current_page` (function, line 15169) `static void save_current_page(browser_window *w)`
  - `deliver_fetch_result` (function, line 15179) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
  - `drain_fetch_results` (function, line 15233) `static void drain_fetch_results(browser_window *w)`
  - `toggle_reader` (function, line 15309) `static void toggle_reader(browser_window *w)`
  - `menu_item_checked` (function, line 15320) `static int menu_item_checked(const browser_window *w, size_t i)`
  - `menu_item_toggle` (function, line 15342) `static void menu_item_toggle(browser_window *w, size_t i)`
  - `draw_clock` (function, line 15452) `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...`
  - `draw_hamburger` (function, line 15464) `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_reload` (function, line 15480) `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_menu` (function, line 15502) `static void draw_menu(cairo_t *cr, browser_window *w)`
  - `draw_hover_url` (function, line 15613) `static double draw_hover_url(cairo_t *cr, browser_window *w)`
  - `draw_toast` (function, line 15645) `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)`
  - `draw_tabstrip` (function, line 15675) `static void draw_tabstrip(cairo_t *cr, browser_window *w)`
  - `draw_omnibox` (function, line 15730) `static void draw_omnibox(cairo_t *cr, browser_window *w)`
  - `paint` (function, line 15764) `static void paint(browser_window *w)`
  - `redraw` (function, line 16008) `static void redraw(browser_window *w)`
  - `wm_base_ping` (function, line 16035) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 16041) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 16049) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `wl_array_for_each` (function, line 16065) `wl_array_for_each(st, states)`

Next: [KB_gui_p2.md](KB_gui_p2.md)
