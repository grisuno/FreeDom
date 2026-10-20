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
  - `rc_oof_sub` (struct, line 3342)
  - `rc_open_box` (struct, line 3352)
  - `rc_ibox` (struct, line 3398)
  - `rc_state` (struct, line 3434)
  - `rc_ext` (struct, line 4077)
  - `item_sides` (struct, line 5183)
  - `rc_defer_col` (struct, line 7932)
  - `rc_defer` (struct, line 7939)
  - `bui_mask_ctx` (struct, line 12513)
  - `screen_flow_ctx` (struct, line 13530)
  - `png_flow_ctx` (struct, line 13945)
  - `freebug_window` (struct, line 15959)
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
  - `block_id` (type_alias, line 3352) `typedef struct rc_open_box { int block_id;`
  - `col_founder_box` (type_alias, line 3433) `typedef struct rc_state { /* Inside a float band column whose width was SHRUNK TO FIT: the float * founder's own box...`
  - `family` (type_alias, line 4077) `typedef struct rc_ext { int family;`
  - `mr` (type_alias, line 5183) `typedef struct item_sides { double ml, mr;`
  - `key` (type_alias, line 7932) `typedef struct rc_defer_col { int key;`
  - `col` (type_alias, line 7939) `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];`
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
  - `rc_float_bottom` (function, line 3530) `static double rc_float_bottom(const rc_state *s)`
  - `rc_float_clear` (function, line 3539) `static void rc_float_clear(rc_state *s)`
  - `rc_float_refresh` (function, line 3552) `static void rc_float_refresh(rc_state *s, double line_h)`
  - `rc_float_fit_line` (function, line 3598) `static void rc_float_fit_line(rc_state *s, double line_h)`
  - `line_limit` (function, line 3617) `static double line_limit(const rc_state *s, double content_w)`
  - `rc_free` (function, line 3625) `static void rc_free(rc_layout *L)`
  - `rc_add_box` (function, line 3645) `static rc_box *rc_add_box(rc_layout *L)`
  - `rc_add_frag` (function, line 3657) `static rc_frag *rc_add_frag(rc_layout *L)`
  - `rc_add_row` (function, line 3672) `static rc_row *rc_add_row(rc_layout *L)`
  - `family_face` (function, line 3684) `static const char *family_face(int family)`
  - `content_font_ex` (function, line 3706) `static void content_font_ex(cairo_t *cr, double size, int bold, int italic, int family,
         ...`
  - `sites` (function, line 3719) `* sites (wfh 0, local 0) get the bucket face, which is the toy face's twin. */
    if (wfh != 0u ...`
  - `content_font` (function, line 3728) `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,
            ...`
  - `set_rgb_alpha` (function, line 3735) `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)`
  - `utf8_clen` (function, line 3744) `static size_t utf8_clen(const char *s, size_t n)`
  - `draw_slice` (function, line 3777) `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)`
  - `frag_styled` (function, line 3790) `static int frag_styled(const rc_frag *f)`
  - `styled_advance` (function, line 3797) `static double styled_advance(cairo_t *cr, const rc_frag *f)`
  - `styled_draw` (function, line 3819) `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)`
  - `block_style` (function, line 3842) `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
  - `block_margins` (function, line 3870) `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...`
  - `area` (function, line 3907) `* box spans its CONTENT area (the font's ascent + descent plus its vertical padding
 * and border...`
  - `run` (function, line 3960) `* continuation run (block_id < 0 with no block break) deliberately skips reconcile
 * to stay on ...`
  - `flush_line` (function, line 3974) `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `open_line_height` (function, line 4041) `static double open_line_height(const rc_state *s, const ui_theme *th)`
  - `open_line` (function, line 4056) `static void open_line(rc_layout *L, rc_state *s)`
  - `flow_emit_frag` (function, line 4110) `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...`
  - `flow_smallcaps_word` (function, line 4170) `static double flow_smallcaps_word(cairo_t *cr, rc_layout *L, rc_state *s,
                       ...`
  - `ibx_advance` (function, line 4225) `static void ibx_advance(const rc_layout *L, rc_state *s, double adv)`
  - `flow_text` (function, line 4233) `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...`
  - `input_inline_eligible` (function, line 4512) `static int input_inline_eligible(const rd_block *b)`
  - `input_inline_size` (function, line 4526) `static int input_inline_size(cairo_t *cr, const ui_theme *th, const rd_block *b,
                ...`
  - `replaced_inline_size` (function, line 4548) `static int replaced_inline_size(cairo_t *cr, const browser_window *w, const ui_theme *th,
       ...`
  - `replaced_is_inline_level` (function, line 4580) `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)`
  - `inlines` (function, line 4593) `* next run may also be a replaced element without its own break: consecutive
 * atomic inlines (`...`
  - `place_inline_replaced` (function, line 4630) `static int place_inline_replaced(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
    ...`
  - `css_replaced_box` (function, line 4715) `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...`
  - `emit_replaced_row` (function, line 4724) `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `block_text_style` (function, line 4837) `static void block_text_style(const browser_window *w, const ui_theme *th, const rd_block *b,
    ...`
  - `flow_text_block` (function, line 4848) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
  - `run_is_content` (function, line 5004) `static int run_is_content(const rd_block *bk)`
  - `item_root_box_pass` (function, line 5014) `static int item_root_box_pass(const rd_doc *doc, size_t b0, size_t b1, int cbox,
                ...`
  - `them` (function, line 5067) `* to them (jkanime's badge-only tiles keep their box). */
static int item_root_box_in(const rd_do...`
  - `item_root_box` (function, line 5088) `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)`
  - `itself` (function, line 5096) `* STRETCH itself (box_tree fills the line with it). */
static int css_align_to_bt(int align_kw)`
  - `box_edge_px` (function, line 5107) `static double box_edge_px(int wpx)`
  - `rc_box_copy_decoration` (function, line 5127) `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)`
  - `box_is_strict_descendant` (function, line 5212) `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)`
  - `item_sides_at_level` (function, line 5234) `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,
                  ...`
  - `container_box_of` (function, line 5291) `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)`
  - `table` (function, line 5313) `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...`
  - `row` (function, line 5378) `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...`
  - `measure_item_w_at` (function, line 5426) `static double measure_item_w_at(cairo_t *cr, const browser_window *w,
                           ...`
  - `lines_at` (function, line 5476) `static size_t lines_at(cairo_t *cr, const browser_window *w, const ui_theme *th,
                ...`
  - `balanced_wrap_width` (function, line 5494) `static double balanced_wrap_width(cairo_t *cr, const browser_window *w, const ui_theme *th,
     ...`
  - `item_inner_inset` (function, line 5515) `static double item_inner_inset(const rd_doc *doc, size_t b0, size_t b1, int root)`
  - `measure_item_content_w` (function, line 5542) `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
  - `run_width_cap` (function, line 5575) `static double run_width_cap(const rd_block *b, double avail_w)`
  - `def_width_cap` (function, line 5579) `static double def_width_cap(const pv_box_def *d, double avail_w)`
  - `def_declared_width` (function, line 5585) `static double def_declared_width(const pv_box_def *d, double avail_w)`
  - `item_declared_basis` (function, line 5590) `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
  - `nested_cont_basis` (function, line 5604) `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...`
  - `flex_item_basis` (function, line 5678) `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
  - `flex_item_min_main` (function, line 5718) `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...`
  - `item_at_level` (function, line 5773) `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `child_cont_at_level` (function, line 5788) `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `cont_in_view` (function, line 5807) `static int cont_in_view(const rd_doc *doc, int cid)`
  - `root_cont_of` (function, line 5821) `static int root_cont_of(const rd_doc *doc, int cid)`
  - `box_under` (function, line 5832) `static int box_under(const rd_doc *doc, int child, int anc)`
  - `root_cont_in` (function, line 5849) `static int root_cont_in(const rd_doc *doc, int cid, int float_box)`
  - `block_is_oof` (function, line 5893) `static int block_is_oof(const rd_doc *doc, const rd_block *bk)`
  - `item_vmargins` (function, line 5938) `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,
          ...`
  - `container_inner_h` (function, line 5959) `static double container_inner_h(const rd_doc *doc, const pv_cont_def *cdv, double content_w)`
  - `layout_container` (function, line 5999) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `slot` (function, line 6195) `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
  - `path` (function, line 6394) `*
         * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when
        ...`
  - `box_line_visible` (function, line 6986) `static int box_line_visible(int style)`
  - `col_spend_free_space` (function, line 7000) `static void col_spend_free_space(rc_layout *L, const rc_open_box *ob, double free_px)`
  - `close_top_box` (function, line 7045) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `wins` (function, line 7110) `* content taller than the ratio still wins (min-height:auto). */
        if (bx->aspect_num > 0 &...`
  - `rc_box_context` (function, line 7195) `static void rc_box_context(const rc_state *s, double content_w,
                           double...`
  - `box_margin_top` (function, line 7222) `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `box_margin_bottom` (function, line 7229) `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `children` (function, line 7239) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
  - `column` (function, line 7462) `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
  - `box_path_has` (function, line 7556) `static int box_path_has(const rd_doc *doc, int block_id, int want)`
  - `columns` (function, line 7570) `* each card made 1080px columns (huggingface, github). */
static int deepest_open_on_path(const r...`
  - `nested_stop` (function, line 7584) `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)`
  - `box_shrink_width` (function, line 7596) `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...`
  - `reconcile_boxes_below` (function, line 7672) `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
  - `reconcile_boxes` (function, line 7788) `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
  - `box_path_of` (function, line 7816) `static int box_path_of(const rd_doc *doc, int block_id, int *out)`
  - `band_common_box` (function, line 7832) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)`
  - `block_in_table_caption` (function, line 7896) `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)`
  - `defer_key_block` (function, line 7960) `static int defer_key_block(const rd_block *bk)`
  - `defer_append` (function, line 8122) `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...`
  - `float_founder_edges` (function, line 8178) `static double float_founder_edges(const rd_doc *doc, int float_box, double ctx_w)`
  - `defer_flush` (function, line 8199) `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...`
  - `layout_float_band` (function, line 8460) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
  - `yet` (function, line 8936) `* does not carry yet (WPT flex-abspos-staticpos-*). */
static int runs_share_float(const rd_doc *...`
  - `layout_doc` (function, line 8948) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
  - `count` (function, line 9408) `* the box count (a hostile parent cycle terminates). */
static int oof_depth(const rd_doc *doc, s...`
  - `approximation` (function, line 9427) `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */
static void oof_s...`
  - `position_doc` (function, line 9628) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
  - `defer_root_of` (function, line 9801) `static int defer_root_of(const rc_layout *L, int bid)`
  - `defer_wants` (function, line 9809) `static int defer_wants(const rc_layout *L, int bid, int only_root)`
  - `input_box_width` (function, line 9815) `static double input_box_width(double content_w)`
  - `select_box_width` (function, line 9819) `static double select_box_width(double content_w)`
  - `button_box_width` (function, line 9824) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...`
  - `blit_image_box` (function, line 10268) `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,
                 ...`
  - `v_read` (function, line 10459) `static int v_read(int fd, void *buf, size_t n)`
  - `dies` (function, line 10487) `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
  - `audio_spawn` (function, line 10496) `static void audio_spawn(browser_window *w, int rate, int channels)`
  - `audio_mark_dead` (function, line 10550) `static void audio_mark_dead(browser_window *w)`
  - `audio_write` (function, line 10567) `static void audio_write(browser_window *w, const uint8_t *data, size_t len)`
  - `audio_stop` (function, line 10582) `static void audio_stop(browser_window *w)`
  - `video_stop` (function, line 10602) `static void video_stop(browser_window *w)`
  - `video_fetch` (function, line 10780) `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...`
  - `video_play` (function, line 10797) `static int video_play(browser_window *w, const char *m3u8_url)`
  - `video_stop` (function, line 10899) `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
  - `paint_video_row` (function, line 10953) `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
  - `row_line_slack` (function, line 11065) `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)`
  - `row_align_offset` (function, line 11077) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)`
  - `upstream` (function, line 11105) `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
  - `box_path` (function, line 11133) `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `paint_box_shadow_layer` (function, line 11144) `static void paint_box_shadow_layer(cairo_t *cr, double x, double y, double w, double h,
         ...`
  - `text` (function, line 11235) `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
  - `grad_stop` (function, line 11262) `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)`
  - `bui_grad_color_at` (function, line 11277) `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...`
  - `spaced` (function, line 11310) `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
  - `paint_bg_layer` (function, line 11343) `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...`
  - `paint_box_decoration` (function, line 11387) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
  - `widths` (function, line 11530) `* the outer minus the adjacent border widths (CSS Backgrounds 3 5.2). The straight
     * per-sid...`
  - `cairo_set_dash` (function, line 11566) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11569) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11615) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11618) `cairo_set_dash(cr, (double[])`
  - `set_rgb` (function, line 11652) `set_rgb(cr, (ui_rgb)`
  - `cairo_set_dash` (function, line 11676) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11679) `cairo_set_dash(cr, (double[])`
  - `paint_deco_line` (function, line 11737) `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...`
  - `cairo_set_dash` (function, line 11771) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 11773) `cairo_set_dash(cr, (double[])`
  - `paint_svg_at` (function, line 11793) `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...`
  - `replaced_current_color` (function, line 11813) `static int replaced_current_color(const browser_window *w, const rd_block *blk)`
  - `paint_inline_replaced` (function, line 11822) `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...`
  - `paint_content_row` (function, line 11867) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
  - `paint_content_row_ex` (function, line 11874) `static void paint_content_row_ex(cairo_t *cr, browser_window *w, const rc_layout *L,
            ...`
  - `ov_box_clips` (function, line 12083) `static int ov_box_clips(const pv_box_def *d)`
  - `ov_collect_chain` (function, line 12090) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)`
  - `ov_box_bounds` (function, line 12111) `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)`
  - `ov_content_rect` (function, line 12135) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...`
  - `fragment` (function, line 12155) `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
  - `box_forms_stacking_context` (function, line 12210) `static int box_forms_stacking_context(const pv_box_def *def)`
  - `bui_skew_tan` (function, line 12254) `static double bui_skew_tan(int deg)`
  - `box_transform_matrix` (function, line 12261) `static int box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
              ...`
  - `bui_blend_operator` (function, line 12389) `static cairo_operator_t bui_blend_operator(int mix_blend)`
  - `bui_gaussian_blur_surface` (function, line 12415) `static void bui_gaussian_blur_surface(cairo_surface_t *surf, double sigma)`
  - `bui_paint_backdrop_blur` (function, line 12451) `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...`
  - `bui_mask_ref_rect` (function, line 12520) `static int bui_mask_ref_rect(const rc_layout *L, int ref, rc_box *out)`
  - `bui_build_mask` (function, line 12536) `static cairo_surface_t *bui_build_mask(const pv_box_def *def, const rc_box *bx_in,
              ...`
  - `bui_pop_group_composite` (function, line 12642) `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms,
    ...`
  - `limits` (function, line 12894) `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
  - `paint_box_decoration_grouped` (function, line 12963) `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
  - `paint_box_and_direct_rows` (function, line 13004) `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...`
  - `bui_pop_group_composite` (function, line 13080) `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
  - `paint_oof_sub` (function, line 13113) `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,
                ...`
  - `paint_positioned_one` (function, line 13151) `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...`
  - `box` (function, line 13266) `* content belongs to that box (painted by its own positioned entry). */
    if (sub == NULL)`
  - `paint_nested_children` (function, line 13372) `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...`
  - `bui_pop_group_composite` (function, line 13395) `bui_pop_group_composite(cr, cdef, now_ms() - w->page_load_mono_ms, &L->boxes[j], left, origin,
  ...`
  - `geom_from_layout` (function, line 13410) `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,
                ...`
  - `publish_geometry` (function, line 13441) `static void publish_geometry(browser_window *w, const rc_layout *L, double left,
                ...`
  - `paint_positioned_layer` (function, line 13493) `static void paint_positioned_layer(cairo_t *cr, browser_window *w, const ui_theme *th,
          ...`
  - `paint_screen_inflow` (function, line 13541) `static void paint_screen_inflow(const screen_flow_ctx *c, int only_root)`
  - `bui_pop_group_composite` (function, line 13606) `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
  - `paint_screen_deferred` (function, line 13656) `static void paint_screen_deferred(void *ctx, int root)`
  - `paint_structured` (function, line 13660) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
  - `write_doc_pdf` (function, line 13776) `static long write_doc_pdf(browser_window *w, const char *path)`
  - `export_pdf` (function, line 13885) `static void export_pdf(browser_window *w)`
  - `paint_png_inflow` (function, line 13957) `static void paint_png_inflow(const png_flow_ctx *c, int only_root)`
  - `paint_png_deferred` (function, line 13986) `static void paint_png_deferred(void *ctx, int root)`
  - `write_doc_png` (function, line 13995) `static long write_doc_png(browser_window *w, const char *path)`
  - `export_png` (function, line 14094) `static void export_png(browser_window *w)`
  - `caller` (function, line 14128) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
  - `ui_render_png` (function, line 14151) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)`
  - `render_doc_images` (function, line 14211) `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...`
  - `ui_render_png_images` (function, line 14242) `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_pdf_images` (function, line 14248) `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_dump_layout` (function, line 14263) `ui_status ui_dump_layout(const rd_doc *doc)`
  - `link_at_point` (function, line 14335) `static const char *link_at_point(browser_window *w, double px, double py)`
  - `resolve_box_cursor` (function, line 14426) `static int resolve_box_cursor(const rd_doc *doc, int block_id)`
  - `box_pointer_events_none` (function, line 14440) `static int box_pointer_events_none(const rd_doc *doc, int block_id)`
  - `cursor_at_point` (function, line 14456) `static int cursor_at_point(browser_window *w, double px, double py)`
  - `node_at_point` (function, line 14521) `static dom_node_id node_at_point(browser_window *w, double px, double py)`
  - `Firefox` (function, line 14529) `* on its face does in Firefox (spec/page_view.md, tanda 40). */
static const rd_block *submit_pro...`
  - `frag_at_point` (function, line 14548) `static dom_node_id frag_at_point(browser_window *w, double px, double py,
                       ...`
  - `reference` (function, line 14602) `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
  - `set_page_url` (function, line 14621) `static void set_page_url(browser_window *w, const char *url)`
  - `ws_apply_ops` (function, line 14646) `static void ws_apply_ops(browser_window *w, const tab_page *page)`
  - `apply_history_ops` (function, line 14681) `static void apply_history_ops(browser_window *w, const tab_page *page)`
  - `history_step` (function, line 14693) `static void history_step(browser_window *w, int steps)`
  - `apply_click_result` (function, line 14726) `static int apply_click_result(browser_window *w, tab_page *page)`
  - `memory` (function, line 14776) `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
  - `GET` (function, line 14870) `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
  - `ensure_download_dir` (function, line 14904) `static int ensure_download_dir(char *out, size_t outsz)`
  - `write_file_atomic` (function, line 14919) `static int write_file_atomic(const char *path, const void *bytes, size_t len)`
  - `save_download` (function, line 14941) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...`
  - `save_current_page` (function, line 14974) `static void save_current_page(browser_window *w)`
  - `deliver_fetch_result` (function, line 14984) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
  - `drain_fetch_results` (function, line 15038) `static void drain_fetch_results(browser_window *w)`
  - `toggle_reader` (function, line 15114) `static void toggle_reader(browser_window *w)`
  - `menu_item_checked` (function, line 15125) `static int menu_item_checked(const browser_window *w, size_t i)`
  - `menu_item_toggle` (function, line 15147) `static void menu_item_toggle(browser_window *w, size_t i)`
  - `draw_clock` (function, line 15257) `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...`
  - `draw_hamburger` (function, line 15269) `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_reload` (function, line 15285) `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_menu` (function, line 15307) `static void draw_menu(cairo_t *cr, browser_window *w)`
  - `draw_hover_url` (function, line 15418) `static double draw_hover_url(cairo_t *cr, browser_window *w)`
  - `draw_toast` (function, line 15450) `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)`
  - `draw_tabstrip` (function, line 15480) `static void draw_tabstrip(cairo_t *cr, browser_window *w)`
  - `draw_omnibox` (function, line 15535) `static void draw_omnibox(cairo_t *cr, browser_window *w)`
  - `paint` (function, line 15569) `static void paint(browser_window *w)`
  - `redraw` (function, line 15813) `static void redraw(browser_window *w)`
  - `wm_base_ping` (function, line 15825) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 15831) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 15839) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `wl_array_for_each` (function, line 15855) `wl_array_for_each(st, states)`
  - `toplevel_close` (function, line 15861) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 15870) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `set_cursor` (function, line 15882) `static void set_cursor(browser_window *w, int cur_kind)`
  - `element` (function, line 15912) `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...`
  - `fbw_split_y` (function, line 15982) `static double fbw_split_y(const freebug_window *fb)`
  - `freebug_ensure_buffer` (function, line 15991) `static int freebug_ensure_buffer(freebug_window *fb)`

Next: [KB_gui_p2.md](KB_gui_p2.md)
