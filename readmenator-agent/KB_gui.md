# Subsystem: gui (page 1 of 3)
Pages: [KB_gui.md](KB_gui.md), [KB_gui_p2.md](KB_gui_p2.md), [KB_gui_p3.md](KB_gui_p3.md)

## gui/browser_ui.c
- Doc: ui_input_state: Live editable state for one form text control, aliasing a block of the current...
- Layer: presentation
- Language: c
- Symbols:
  - `ui_menu_item` (struct, line 201)
  - `ui_input_state` (struct, line 243)
  - `ui_image` (struct, line 268)
  - `ui_bg_image` (struct, line 282)
  - `tab_ctx` (struct, line 301)
  - `browser_window` (struct, line 322)
  - `fip_hit` (struct, line 694)
  - `repl_edges` (struct, line 1339)
  - `gui_sub_prep` (struct, line 1730)
  - `gui_net_ctx` (struct, line 1824)
  - `fetch_prep` (struct, line 2084)
  - `fetch_job` (struct, line 2165)
  - `rc_frag` (struct, line 3714)
  - `rc_row` (struct, line 3781)
  - `rc_box` (struct, line 3804)
  - `rc_oof_sub` (struct, line 3865)
  - `rc_table_ctx` (struct, line 3869)
  - `rc_layout` (struct, line 3878)
  - `rc_oof_sub` (struct, line 3936)
  - `rc_open_box` (struct, line 3946)
  - `rc_ibox` (struct, line 3999)
  - `rc_state` (struct, line 4044)
  - `rc_ext` (struct, line 4748)
  - `item_sides` (struct, line 5864)
  - `rc_defer_col` (struct, line 9299)
  - `rc_defer` (struct, line 9306)
  - `bui_mask_ctx` (struct, line 14584)
  - `screen_flow_ctx` (struct, line 15705)
  - `frame_undo` (struct, line 16098)
  - `png_flow_ctx` (struct, line 16458)
  - `freebug_window` (struct, line 18777)
  - `ui_menu_action` (enum, line 183)
  - `rc_rowkind` (enum, line 3779)
  - `ui_hot` (type_alias, line 235) `typedef int ui_hot;`
  - `bs` (type_alias, line 301) `typedef struct tab_ctx { browser_state bs;`
  - `addr` (type_alias, line 693) `typedef struct fip_hit { uintptr_t addr;`
  - `freebug_window` (type_alias, line 703) `typedef struct freebug_window freebug_window;`
  - `pl` (type_alias, line 1339) `typedef struct repl_edges { double mt, mr, mb, ml, bt, br, bb, bl, pt, pr, pb, pl;`
  - `ln` (type_alias, line 1730) `typedef struct gui_sub_prep { ln_result ln;`
  - `allowlisted` (type_alias, line 2084) `typedef struct fetch_prep { int allowlisted;`
  - `font_size` (type_alias, line 3713) `typedef struct rc_frag { double x, width, font_size;`
  - `kind` (type_alias, line 3780) `typedef struct rc_row { rc_rowkind kind;`
  - `h` (type_alias, line 3804) `typedef struct rc_box { double x, top, w, h;`
  - `cid` (type_alias, line 3869) `typedef struct rc_table_ctx { int cid;`
  - `block_id` (type_alias, line 3946) `typedef struct rc_open_box { int block_id;`
  - `col_founder_box` (type_alias, line 4043) `typedef struct rc_state { /* Inside a float band column whose width was SHRUNK TO FIT: the float * founder's own box...`
  - `family` (type_alias, line 4748) `typedef struct rc_ext { int family;`
  - `mr` (type_alias, line 5864) `typedef struct item_sides { double ml, mr;`
  - `key` (type_alias, line 9299) `typedef struct rc_defer_col { int key;`
  - `col` (type_alias, line 9306) `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];`
  - `now_ms` (function, line 170) `static uint64_t now_ms(void)`
  - `gutter` (function, line 724) `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
  - `apply_zoom` (function, line 744) `static void apply_zoom(browser_window *w)`
  - `buffer_release` (function, line 755) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `fb_buffer_release` (function, line 766) `static void fb_buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 769) `static void destroy_buffer(browser_window *w)`
  - `make_slot` (function, line 779) `static int make_slot(browser_window *w, int i, size_t size, int stride)`
  - `ensure_buffer` (function, line 804) `static int ensure_buffer(browser_window *w)`
  - `read_file` (function, line 823) `static char *read_file(const char *path, size_t *out_len)`
  - `build_file_origin` (function, line 862) `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)`
  - `build_host_filter` (function, line 876) `static hb_set *build_host_filter(void)`
  - `build_js_filter` (function, line 892) `static hb_set *build_js_filter(void)`
  - `build_impersonate_optin` (function, line 895) `static int build_impersonate_optin(void)`
  - `freedom_write_dir` (function, line 904) `static int freedom_write_dir(char *out, size_t cap)`
  - `list_append_host` (function, line 933) `static int list_append_host(const char *filename, const char *host)`
  - `reload_host_list` (function, line 967) `static void reload_host_list(browser_window *w, int sel)`
  - `add_current_host_to_list` (function, line 1017) `static int add_current_host_to_list(browser_window *w, int sel)`
  - `load_favorites` (function, line 1052) `static void load_favorites(browser_window *w)`
  - `omni_refresh` (function, line 1089) `static void omni_refresh(browser_window *w)`
  - `profile_sync` (function, line 1120) `static void profile_sync(browser_window *w)`
  - `remember_visit` (function, line 1137) `static void remember_visit(browser_window *w, const char *url)`
  - `bookmark_toggle_current` (function, line 1145) `static void bookmark_toggle_current(browser_window *w)`
  - `proxy_addr_from_env` (function, line 1169) `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...`
  - `init_net_config` (function, line 1183) `static void init_net_config(browser_window *w)`
  - `is_https_url` (function, line 1193) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 1197) `static int is_http_url(const char *s)`
  - `host_from_url` (function, line 1208) `static int host_from_url(const char *url, char *out, size_t outsz)`
  - `toggle_fullscreen` (function, line 1246) `static void toggle_fullscreen(browser_window *w)`
  - `input_is_interactive` (function, line 1261) `static int input_is_interactive(int input_type)`
  - `input_is_editable` (function, line 1267) `static int input_is_editable(int input_type)`
  - `free_inputs` (function, line 1273) `static void free_inputs(browser_window *w)`
  - `free_images` (function, line 1281) `static void free_images(browser_window *w)`
  - `find_bg_image` (function, line 1320) `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)`
  - `replaced_edges` (function, line 1346) `static repl_edges replaced_edges(const rd_doc *doc, const rd_block *b, double cb_w)`
  - `repl_edges_x` (function, line 1370) `static double repl_edges_x(const repl_edges *e)`
  - `repl_edges_y` (function, line 1374) `static double repl_edges_y(const repl_edges *e)`
  - `image_display_size` (function, line 1408) `static int image_display_size(const browser_window *w, const rd_block *blk,
                     ...`
  - `placeholder_display_size` (function, line 1474) `static int placeholder_display_size(const rd_block *blk, double box_w,
                          ...`
  - `rebuild_inputs` (function, line 1497) `static void rebuild_inputs(browser_window *w)`
  - `find_input_state` (function, line 1523) `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)`
  - `set_doc` (function, line 1531) `static void set_doc(browser_window *w, rd_doc *d)`
  - `clear_doc` (function, line 1538) `static void clear_doc(browser_window *w)`
  - `set_cache` (function, line 1548) `static void set_cache(browser_window *w, char *html, size_t len, const char *top)`
  - `img_css_w` (function, line 1564) `static uint32_t img_css_w(const tab_image *img)`
  - `img_css_h` (function, line 1565) `static uint32_t img_css_h(const tab_image *img)`
  - `surface_from_pixels` (function, line 1567) `static cairo_surface_t *surface_from_pixels(const tab_image *img)`
  - `fetch_follow_navigable` (function, line 1631) `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...`
  - `fetch_get_cached` (function, line 1639) `static sf_status fetch_get_cached(const browser_window *w, const char *url, sf_config *cfg,
     ...`
  - `fetch_post_navigable` (function, line 1647) `static sf_status fetch_post_navigable(const char *url, sf_config *cfg,
                          ...`
  - `page_host_allowlisted` (function, line 1671) `static int page_host_allowlisted(const browser_window *w)`
  - `ui_set_operator_insecure` (function, line 1680) `void ui_set_operator_insecure(int on)`
  - `apply_operator_override` (function, line 1681) `static void apply_operator_override(sf_config *cfg)`
  - `aa_note` (function, line 1698) `static void aa_note(browser_window *w, const char *abs, const char *host)`
  - `gui_sub_prepare` (function, line 1737) `static int gui_sub_prepare(browser_window *w, const char *top, int trusted, int top_allowed,
    ...`
  - `gui_sub_perform` (function, line 1778) `static int gui_sub_perform(gui_sub_prep *p, const char *method, const void *body, size_t body_len...`
  - `gui_subresource_fetch` (function, line 1807) `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...`
  - `gui_net_ctx_free` (function, line 1832) `static void gui_net_ctx_free(void *p)`
  - `gui_net_ctx_new` (function, line 1840) `static gui_net_ctx *gui_net_ctx_new(browser_window *w)`
  - `net_ctx_lock` (function, line 1853) `static void net_ctx_lock(browser_window *w)`
  - `net_ctx_unlock` (function, line 1854) `static void net_ctx_unlock(browser_window *w)`
  - `gui_net_ctx_retire` (function, line 1857) `static void gui_net_ctx_retire(gui_net_ctx *c)`
  - `gui_async_fetch` (function, line 1864) `static int gui_async_fetch(void *vctx, const char *method, const char *url,
                     ...`
  - `gui_css_sink` (function, line 1911) `static void gui_css_sink(void *vctx, const char *url,
                         const char *body, ...`
  - `first` (function, line 1979) `* Navigation: clear the registry first (faces are per document). Untrusted:
 * no-op (fetch NULL)...`
  - `prepare_fetch` (function, line 2093) `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...`
  - `fetch_job_free` (function, line 2200) `static void fetch_job_free(fetch_job *j)`
  - `stream_progress_cb` (function, line 2222) `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)`
  - `fetch_job_cancelled` (function, line 2247) `static int fetch_job_cancelled(void *ctx)`
  - `fetch_thread` (function, line 2255) `static void *fetch_thread(void *arg)`
  - `stream_discard` (function, line 2310) `static void stream_discard(browser_window *w)`
  - `nav_supersede` (function, line 2321) `static void nav_supersede(browser_window *w)`
  - `fetch_launch` (function, line 2329) `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...`
  - `is_frame_href` (function, line 2464) `static int is_frame_href(const char *href)`
  - `load_images` (function, line 2470) `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx,
     ...`
  - `page_js_host_allowlisted` (function, line 2644) `static int page_js_host_allowlisted(const browser_window *w)`
  - `compute_page_js` (function, line 2650) `static int compute_page_js(const browser_window *w)`
  - `seed_session_cookies` (function, line 2664) `static void seed_session_cookies(tab *t, int trusted, const char *url)`
  - `seed_local_storage` (function, line 2688) `static void seed_local_storage(browser_window *w, tab *t, int trusted)`
  - `collect_local_storage` (function, line 2703) `static void collect_local_storage(browser_window *w, const tab_page *page)`
  - `foldback_session_cookies` (function, line 2713) `static void foldback_session_cookies(const char *url, const char *jar)`
  - `drop_repl_worker` (function, line 2746) `static void drop_repl_worker(browser_window *w)`
  - `gui_viewport_w` (function, line 2763) `static int gui_viewport_w(const browser_window *w)`
  - `schedule_js_tick` (function, line 2770) `static void schedule_js_tick(browser_window *w, int next_ms)`
  - `render_current_ex` (function, line 2780) `static void render_current_ex(browser_window *w, int allow_js_nav)`
  - `render_current` (function, line 2969) `static void render_current(browser_window *w)`
  - `show_busy` (function, line 2976) `static void show_busy(browser_window *w)`
  - `show_fetch_error` (function, line 2985) `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...`
  - `identity_load` (function, line 3054) `static void identity_load(browser_window *w)`
  - `arrives` (function, line 3064) `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...`
  - `strcmp` (function, line 3171) `&& strcmp(auth_host_buf, w->auth_host) != 0)`
  - `tab_save` (function, line 3235) `static void tab_save(browser_window *w)`
  - `tab_restore` (function, line 3258) `static void tab_restore(browser_window *w)`
  - `free_live_page` (function, line 3281) `static void free_live_page(browser_window *w)`
  - `tab_ctx_release` (function, line 3294) `static void tab_ctx_release(tab_ctx *c)`
  - `tab_show_ready` (function, line 3324) `static void tab_show_ready(browser_window *w)`
  - `tab_switch` (function, line 3332) `static void tab_switch(browser_window *w, int idx)`
  - `uitab_close` (function, line 3398) `static void uitab_close(browser_window *w, int idx)`
  - `chrome_of` (function, line 3437) `static chl_layout chrome_of(const browser_window *w)`
  - `tab_move` (function, line 3448) `static void tab_move(browser_window *w, int from, int to)`
  - `tab_title` (function, line 3475) `static const char *tab_title(const browser_window *w, int i)`
  - `tabbar_top` (function, line 3486) `static double tabbar_top(const browser_window *w)`
  - `toolbar_top` (function, line 3493) `static double toolbar_top(const browser_window *w)`
  - `content_geometry` (function, line 3500) `static void content_geometry(const browser_window *w, double *top, double *height)`
  - `page_side` (function, line 3527) `static double page_side(const browser_window *w, int side)`
  - `content_margin_x` (function, line 3531) `static double content_margin_x(const browser_window *w)`
  - `content_margins_x` (function, line 3542) `static double content_margins_x(const browser_window *w)`
  - `content_width` (function, line 3547) `static double content_width(const browser_window *w)`
  - `html_center_offset` (function, line 3557) `static double html_center_offset(const browser_window *w)`
  - `scrollbar_metrics` (function, line 3571) `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...`
  - `scrollbar_drag_to` (function, line 3599) `static void scrollbar_drag_to(browser_window *w)`
  - `draw_scrollbar` (function, line 3616) `static void draw_scrollbar(cairo_t *cr, const browser_window *w)`
  - `chrome_hot_at` (function, line 3655) `static ui_hot chrome_hot_at(const browser_window *w, double px, double py)`
  - `hot_actionable` (function, line 3666) `static int hot_actionable(const browser_window *w, ui_hot hot)`
  - `menu_panel_rect` (function, line 3678) `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...`
  - `ua_box_rect` (function, line 3693) `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...`
  - `rc_float_bottom` (function, line 4142) `static double rc_float_bottom(const rc_state *s)`
  - `rc_float_clear` (function, line 4151) `static void rc_float_clear(rc_state *s)`
  - `rc_float_refresh` (function, line 4164) `static void rc_float_refresh(rc_state *s, double line_h)`
  - `rc_float_fit_line` (function, line 4210) `static void rc_float_fit_line(rc_state *s, double line_h)`
  - `line_limit` (function, line 4229) `static double line_limit(const rc_state *s, double content_w)`
  - `rc_free` (function, line 4237) `static void rc_free(rc_layout *L)`
  - `rc_add_box` (function, line 4257) `static rc_box *rc_add_box(rc_layout *L)`
  - `rc_add_frag` (function, line 4269) `static rc_frag *rc_add_frag(rc_layout *L)`
  - `rc_add_row` (function, line 4284) `static rc_row *rc_add_row(rc_layout *L)`
  - `family_face` (function, line 4296) `static const char *family_face(int family)`
  - `content_font_ex` (function, line 4318) `static void content_font_ex(cairo_t *cr, double size, int bold, int italic, int family,
         ...`
  - `sites` (function, line 4331) `* sites (wfh 0, local 0) get the bucket face, which is the toy face's twin. */
    if (wfh != 0u ...`
  - `content_font` (function, line 4340) `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,
            ...`
  - `set_rgb_alpha` (function, line 4347) `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)`
  - `utf8_clen` (function, line 4356) `static size_t utf8_clen(const char *s, size_t n)`
  - `draw_slice` (function, line 4389) `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)`
  - `frag_styled` (function, line 4402) `static int frag_styled(const rc_frag *f)`
  - `styled_advance` (function, line 4409) `static double styled_advance(cairo_t *cr, const rc_frag *f)`
  - `styled_draw` (function, line 4431) `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)`
  - `block_style` (function, line 4454) `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
  - `block_margins` (function, line 4482) `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...`
  - `area` (function, line 4519) `* box spans its CONTENT area (the font's ascent + descent plus its vertical padding
 * and border...`
  - `leave_inline_box` (function, line 4579) `static void leave_inline_box(rc_layout *L, rc_state *s, const rd_doc *doc, int block_id)`
  - `atoms_extend_line` (function, line 4601) `static void atoms_extend_line(const rc_layout *L, rc_state *s, double *h,
                       ...`
  - `flush_line` (function, line 4643) `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `open_line_height` (function, line 4712) `static double open_line_height(const rc_state *s, const ui_theme *th)`
  - `open_line` (function, line 4727) `static void open_line(rc_layout *L, rc_state *s)`
  - `flow_emit_frag` (function, line 4781) `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...`
  - `flow_smallcaps_word` (function, line 4843) `static double flow_smallcaps_word(cairo_t *cr, rc_layout *L, rc_state *s,
                       ...`
  - `ibx_advance` (function, line 4898) `static void ibx_advance(const rc_layout *L, rc_state *s, double adv)`
  - `flow_text` (function, line 4907) `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...`
  - `input_inline_eligible` (function, line 5188) `static int input_inline_eligible(const rd_block *b)`
  - `input_inline_size` (function, line 5202) `static int input_inline_size(cairo_t *cr, const ui_theme *th, const rd_block *b,
                ...`
  - `replaced_inline_size` (function, line 5224) `static int replaced_inline_size(cairo_t *cr, const browser_window *w, const ui_theme *th,
       ...`
  - `replaced_is_inline_level` (function, line 5256) `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)`
  - `inlines` (function, line 5269) `* next run may also be a replaced element without its own break: consecutive
 * atomic inlines (`...`
  - `place_inline_replaced` (function, line 5306) `static int place_inline_replaced(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
    ...`
  - `css_replaced_box` (function, line 5391) `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...`
  - `emit_replaced_row` (function, line 5400) `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `block_text_style` (function, line 5513) `static void block_text_style(const browser_window *w, const ui_theme *th, const rd_block *b,
    ...`
  - `flow_text_block` (function, line 5524) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
  - `run_is_content` (function, line 5681) `static int run_is_content(const rd_block *bk)`
  - `item_root_box_pass` (function, line 5691) `static int item_root_box_pass(const rd_doc *doc, size_t b0, size_t b1, int cbox,
                ...`
  - `them` (function, line 5744) `* to them (jkanime's badge-only tiles keep their box). */
static int item_root_box_in(const rd_do...`
  - `item_root_box` (function, line 5765) `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)`
  - `itself` (function, line 5773) `* STRETCH itself (box_tree fills the line with it). */
static int css_align_to_bt(int align_kw)`
  - `box_edge_px` (function, line 5784) `static double box_edge_px(int wpx)`
  - `rc_box_copy_decoration` (function, line 5804) `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)`
  - `box_is_strict_descendant` (function, line 5897) `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)`
  - `block_space_px` (function, line 5915) `static double block_space_px(cairo_t *cr, const browser_window *w, const ui_theme *th,
          ...`
  - `item_sides_at_level` (function, line 5935) `static item_sides item_sides_at_level(cairo_t *cr, const browser_window *w, const ui_theme *th,
 ...`
  - `item_sides_at_level_raw` (function, line 5954) `static item_sides item_sides_at_level_raw(const rd_doc *doc, size_t b0, size_t b1,
              ...`
  - `container_box_of` (function, line 6021) `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)`
  - `table` (function, line 6043) `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...`
  - `row` (function, line 6108) `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...`
  - `empty_atom_outer_w` (function, line 6160) `static double empty_atom_outer_w(const rd_doc *doc, size_t k, const rd_block *bk)`
  - `sized_block_content_w` (function, line 6180) `static double sized_block_content_w(const rd_doc *doc, const rd_block *bk)`
  - `inside` (function, line 6197) `* whatever its own items do inside (jkanime's fixed nav: one `<a display:flex>` per
 * entry, mea...`
  - `measure_item_w_at` (function, line 6213) `static double measure_item_w_at(cairo_t *cr, const browser_window *w,
                           ...`
  - `lines_at` (function, line 6287) `static size_t lines_at(cairo_t *cr, const browser_window *w, const ui_theme *th,
                ...`
  - `balanced_wrap_width` (function, line 6305) `static double balanced_wrap_width(cairo_t *cr, const browser_window *w, const ui_theme *th,
     ...`
  - `item_inner_inset` (function, line 6326) `static double item_inner_inset(const rd_doc *doc, size_t b0, size_t b1, int root)`
  - `measure_item_content_w` (function, line 6353) `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
  - `run_width_cap` (function, line 6386) `static double run_width_cap(const rd_block *b, double avail_w)`
  - `def_width_cap` (function, line 6390) `static double def_width_cap(const pv_box_def *d, double avail_w)`
  - `def_declared_width` (function, line 6396) `static double def_declared_width(const pv_box_def *d, double avail_w)`
  - `cont_gap_px` (function, line 6405) `static double cont_gap_px(cairo_t *cr, const browser_window *w, const ui_theme *th,
             ...`
  - `item_declared_basis` (function, line 6412) `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
  - `nested_cont_basis` (function, line 6431) `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...`
  - `flex_item_basis` (function, line 6512) `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
  - `flex_item_min_main` (function, line 6560) `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...`
  - `item_at_level` (function, line 6625) `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `child_cont_at_level` (function, line 6640) `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `cont_in_view` (function, line 6659) `static int cont_in_view(const rd_doc *doc, int cid)`
  - `root_cont_of` (function, line 6673) `static int root_cont_of(const rd_doc *doc, int cid)`
  - `box_under` (function, line 6684) `static int box_under(const rd_doc *doc, int child, int anc)`
  - `root_cont_in` (function, line 6701) `static int root_cont_in(const rd_doc *doc, int cid, int float_box)`
  - `block_is_oof` (function, line 6745) `static int block_is_oof(const rd_doc *doc, const rd_block *bk)`
  - `item_vmargins` (function, line 6790) `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,
          ...`
  - `container_inner_h` (function, line 6811) `static double container_inner_h(const rd_doc *doc, const pv_cont_def *cdv, double content_w)`
  - `cont_next_item` (function, line 6854) `static int cont_next_item(const rd_doc *doc, int cid, size_t end, size_t *k, size_t *e)`
  - `table_item_slot` (function, line 6871) `static void table_item_slot(const rd_doc *doc, size_t k, int cid, int *row, int *col, int *span)`
  - `table_solve` (function, line 6893) `static double table_solve(cairo_t *cr, const browser_window *w, const ui_theme *th,
             ...`
  - `layout_container` (function, line 7118) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `slot` (function, line 7314) `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
  - `box_line_visible` (function, line 8128) `static int box_line_visible(int style)`
  - `col_spend_free_space` (function, line 8142) `static void col_spend_free_space(rc_layout *L, const rc_open_box *ob, double free_px)`
  - `close_top_box` (function, line 8187) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `wins` (function, line 8255) `* content taller than the ratio still wins (min-height:auto). */
        if (bx->aspect_num > 0 &...`
  - `rc_box_context` (function, line 8362) `static void rc_box_context(const rc_state *s, double content_w,
                           double...`
  - `box_margin_top` (function, line 8389) `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `box_margin_bottom` (function, line 8396) `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `children` (function, line 8406) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
  - `column` (function, line 8658) `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
  - `box_path_has` (function, line 8752) `static int box_path_has(const rd_doc *doc, int block_id, int want)`
  - `columns` (function, line 8766) `* each card made 1080px columns (huggingface, github). */
static int deepest_open_on_path(const r...`
  - `float_item_stop` (function, line 8783) `static int float_item_stop(const rd_doc *doc, const rd_block *bk, int founder_key, int base_stop)`
  - `nested_stop` (function, line 8802) `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)`
  - `table_box_shrink_width` (function, line 8813) `static double table_box_shrink_width(cairo_t *cr, const browser_window *w, const ui_theme *th,
  ...`
  - `box_shrink_width` (function, line 8862) `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...`
  - `reconcile_boxes_below` (function, line 8951) `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
  - `reconcile_boxes` (function, line 9097) `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
  - `box_path_of` (function, line 9125) `static int box_path_of(const rd_doc *doc, int block_id, int *out)`
  - `oof_static_xy` (function, line 9145) `static void oof_static_xy(const rc_state *s, const ui_theme *th, double content_w,
              ...`
  - `band_parent_box` (function, line 9161) `static int band_parent_box(const rd_doc *doc, const rd_block *bk)`
  - `band_common_box_ex` (function, line 9168) `static int band_common_box_ex(const rd_doc *doc, size_t start, size_t end, int skip_boxless)`
  - `band_common_box` (function, line 9193) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)`
  - `block_in_table_caption` (function, line 9263) `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)`
  - `defer_key_block` (function, line 9329) `static int defer_key_block(const rd_block *bk)`
  - `defer_append` (function, line 9529) `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...`
  - `float_founder_edges` (function, line 9594) `static double float_founder_edges(const rd_doc *doc, int float_box, double ctx_w)`
  - `defer_col_shrink_w` (function, line 9609) `static double defer_col_shrink_w(cairo_t *cr, const browser_window *w, const ui_theme *th,
      ...`
  - `defer_flush` (function, line 9664) `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...`
  - `layout_float_band` (function, line 9963) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
  - `yet` (function, line 10442) `* does not carry yet (WPT flex-abspos-staticpos-*). */
static int runs_share_float(const rd_doc *...`
  - `layout_doc` (function, line 10457) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
  - `count` (function, line 10985) `* the box count (a hostile parent cycle terminates). */
static int oof_depth(const rd_doc *doc, s...`
  - `approximation` (function, line 11004) `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */
static void oof_s...`
  - `page` (function, line 11234) `* such a page (Wikipedia's Vector skin) at 1080px, and a page made only of boxes has no
 * in-flo...`
  - `position_doc` (function, line 11253) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
  - `position_boxes` (function, line 11259) `static void position_boxes(cairo_t *cr, const browser_window *w, double content_w,
              ...`
  - `defer_root_of` (function, line 11441) `static int defer_root_of(const rc_layout *L, int bid)`
  - `defer_wants` (function, line 11449) `static int defer_wants(const rc_layout *L, int bid, int only_root)`
  - `input_box_width` (function, line 11455) `static double input_box_width(double content_w)`
  - `select_box_width` (function, line 11459) `static double select_box_width(double content_w)`
  - `button_box_width` (function, line 11464) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...`
  - `blit_image_box` (function, line 11913) `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,
                 ...`
  - `v_read` (function, line 12114) `static int v_read(int fd, void *buf, size_t n)`
  - `dies` (function, line 12142) `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
  - `audio_spawn` (function, line 12151) `static void audio_spawn(browser_window *w, int rate, int channels)`
  - `audio_mark_dead` (function, line 12205) `static void audio_mark_dead(browser_window *w)`
  - `audio_write` (function, line 12222) `static void audio_write(browser_window *w, const uint8_t *data, size_t len)`
  - `audio_stop` (function, line 12237) `static void audio_stop(browser_window *w)`
  - `video_stop` (function, line 12293) `static void video_stop(browser_window *w)`
  - `video_feed_cancelled` (function, line 12447) `static int video_feed_cancelled(void *ctx)`
  - `video_fetch_ex` (function, line 12453) `static sf_status video_fetch_ex(const char *url, browser_window *w, sf_response *resp,
          ...`
  - `video_fetch` (function, line 12468) `static sf_status video_fetch(const char *url, browser_window *w, sf_response *resp)`
  - `video_play` (function, line 12478) `static int video_play(browser_window *w, const char *m3u8_url)`
  - `video_pipeline_up` (function, line 12552) `static int video_pipeline_up(browser_window *w, size_t start_seg)`
  - `video_seek_to` (function, line 12591) `static void video_seek_to(browser_window *w, double t)`
  - `video_position_s` (function, line 12599) `static double video_position_s(const browser_window *w)`
  - `video_toggle_pause` (function, line 12606) `static void video_toggle_pause(browser_window *w)`
  - `video_stop` (function, line 12621) `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
  - `video_draw_rect` (function, line 12698) `static void video_draw_rect(const browser_window *w, double *x, double *y,
                      ...`
  - `blit_video_frame` (function, line 12737) `static int blit_video_frame(cairo_t *cr, browser_window *w,
                            double x,...`
  - `paint_video_row` (function, line 12765) `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
  - `row_line_slack` (function, line 12843) `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)`
  - `row_align_offset` (function, line 12855) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)`
  - `upstream` (function, line 12883) `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
  - `box_path` (function, line 12911) `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `box_shadow_layers` (function, line 12924) `static int box_shadow_layers(const rc_box *bx, int layers[PV_BSHADOW_LAYERS][6])`
  - `cr_mask_cache` (function, line 12948) `static mkc_cache *cr_mask_cache(cairo_t *cr)`
  - `shadow_mask_surface` (function, line 12986) `static cairo_surface_t *shadow_mask_surface(mkc_cache *mc, const mkc_key *k)`
  - `paint_box_shadow_layer` (function, line 13026) `static void paint_box_shadow_layer(cairo_t *cr, double x, double y, double w, double h,
         ...`
  - `text` (function, line 13103) `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
  - `grad_stop` (function, line 13130) `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)`
  - `bui_grad_color_at` (function, line 13145) `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...`
  - `spaced` (function, line 13178) `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
  - `paint_bg_layer` (function, line 13211) `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...`
  - `paint_gradient_fill` (function, line 13257) `static void paint_gradient_fill(cairo_t *cr, const rc_box *bx, double x, double y,
              ...`
  - `paint_gradient_tiled` (function, line 13304) `static void paint_gradient_tiled(cairo_t *cr, const rc_box *bx, double x, double y,
             ...`
  - `paint_box_decoration` (function, line 13331) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
  - `widths` (function, line 13449) `* the outer minus the adjacent border widths (CSS Backgrounds 3 5.2). The straight
     * per-sid...`
  - `cairo_set_dash` (function, line 13485) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 13488) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 13534) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 13537) `cairo_set_dash(cr, (double[])`
  - `set_rgb` (function, line 13571) `set_rgb(cr, (ui_rgb)`
  - `cairo_set_dash` (function, line 13595) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 13598) `cairo_set_dash(cr, (double[])`
  - `paint_deco_line` (function, line 13656) `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...`
  - `cairo_set_dash` (function, line 13690) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 13692) `cairo_set_dash(cr, (double[])`
  - `paint_svg_at` (function, line 13712) `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...`
  - `replaced_current_color` (function, line 13732) `static int replaced_current_color(const browser_window *w, const rd_block *blk)`
  - `paint_inline_replaced` (function, line 13741) `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...`
  - `fip_lower` (function, line 13780) `static size_t fip_lower(const browser_window *w, uintptr_t addr)`
  - `fip_paint_frag` (function, line 13791) `static void fip_paint_frag(cairo_t *cr, const browser_window *w, const rc_frag *f,
              ...`
  - `fip_clear_hits` (function, line 13812) `static void fip_clear_hits(browser_window *w)`
  - `fip_hit_cmp` (function, line 13823) `static int fip_hit_cmp(const void *a, const void *b)`
  - `fip_collect` (function, line 13829) `static void fip_collect(const rc_layout *L, double dy, ft_piece *p, double *ys, size_t cap,
     ...`
  - `fip_sync` (function, line 13851) `static void fip_sync(browser_window *w, const rc_layout *L)`
  - `fip_reveal` (function, line 13901) `static void fip_reveal(browser_window *w, double content_h)`
  - `paint_content_row` (function, line 13920) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
  - `paint_content_row_ex` (function, line 13927) `static void paint_content_row_ex(cairo_t *cr, browser_window *w, const rc_layout *L,
            ...`
  - `ov_box_clips` (function, line 14149) `static int ov_box_clips(const pv_box_def *d)`
  - `ov_collect_chain` (function, line 14156) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)`
  - `ov_box_bounds` (function, line 14177) `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)`
  - `ov_content_rect` (function, line 14203) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...`
  - `fragment` (function, line 14219) `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
  - `box_forms_stacking_context` (function, line 14274) `static int box_forms_stacking_context(const pv_box_def *def)`
  - `bui_skew_tan` (function, line 14318) `static double bui_skew_tan(int deg)`
  - `box_transform_matrix` (function, line 14325) `static int box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
              ...`
  - `bui_blend_operator` (function, line 14453) `static cairo_operator_t bui_blend_operator(int mix_blend)`
  - `bui_gaussian_blur_surface` (function, line 14479) `static void bui_gaussian_blur_surface(cairo_surface_t *surf, double sigma)`
  - `bui_paint_backdrop_blur` (function, line 14522) `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...`
  - `bui_mask_ref_rect` (function, line 14592) `static int bui_mask_ref_rect(const rc_layout *L, int ref, rc_box *out)`
  - `bui_build_mask` (function, line 14608) `static cairo_surface_t *bui_build_mask(const pv_box_def *def, const rc_box *bx_in,
              ...`
  - `bui_pop_group_composite` (function, line 14724) `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms,
    ...`
  - `limits` (function, line 14978) `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
  - `paint_box_decoration_grouped` (function, line 15047) `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
  - `paint_box_and_direct_rows` (function, line 15088) `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...`
  - `bui_pop_group_composite` (function, line 15164) `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
  - `paint_oof_sub` (function, line 15218) `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,
                ...`
  - `paint_positioned_one` (function, line 15256) `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...`
  - `box` (function, line 15377) `* content belongs to that box (painted by its own positioned entry). */

Next: [KB_gui_p2.md](KB_gui_p2.md)
