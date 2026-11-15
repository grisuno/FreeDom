# Subsystem: gui (page 1 of 2)
Pages: [KB_gui.md](KB_gui.md), [KB_gui_p2.md](KB_gui_p2.md)

## gui/browser_ui.c
- Doc: ui_input_state: Live editable state for one form text control, aliasing a block of the current...
- Layer: presentation
- Language: c
- Symbols:
  - `ui_menu_item` (struct, line 200)
  - `ui_input_state` (struct, line 239)
  - `ui_image` (struct, line 264)
  - `ui_bg_image` (struct, line 278)
  - `tab_ctx` (struct, line 297)
  - `browser_window` (struct, line 313)
  - `repl_edges` (struct, line 1256)
  - `fetch_prep` (struct, line 1902)
  - `fetch_job` (struct, line 1983)
  - `rc_frag` (struct, line 3452)
  - `rc_row` (struct, line 3519)
  - `rc_box` (struct, line 3542)
  - `rc_oof_sub` (struct, line 3603)
  - `rc_layout` (struct, line 3605)
  - `rc_oof_sub` (struct, line 3651)
  - `rc_open_box` (struct, line 3661)
  - `rc_ibox` (struct, line 3714)
  - `rc_state` (struct, line 3755)
  - `rc_ext` (struct, line 4453)
  - `item_sides` (struct, line 5568)
  - `rc_defer_col` (struct, line 8656)
  - `rc_defer` (struct, line 8663)
  - `bui_mask_ctx` (struct, line 13588)
  - `screen_flow_ctx` (struct, line 14697)
  - `png_flow_ctx` (struct, line 15258)
  - `freebug_window` (struct, line 17593)
  - `ui_menu_action` (enum, line 182)
  - `ui_hot` (enum, line 232)
  - `rc_rowkind` (enum, line 3517)
  - `bs` (type_alias, line 297) `typedef struct tab_ctx { browser_state bs;`
  - `freebug_window` (type_alias, line 631) `typedef struct freebug_window freebug_window;`
  - `pl` (type_alias, line 1256) `typedef struct repl_edges { double mt, mr, mb, ml, bt, br, bb, bl, pt, pr, pb, pl;`
  - `allowlisted` (type_alias, line 1902) `typedef struct fetch_prep { int allowlisted;`
  - `font_size` (type_alias, line 3451) `typedef struct rc_frag { double x, width, font_size;`
  - `kind` (type_alias, line 3518) `typedef struct rc_row { rc_rowkind kind;`
  - `h` (type_alias, line 3542) `typedef struct rc_box { double x, top, w, h;`
  - `block_id` (type_alias, line 3661) `typedef struct rc_open_box { int block_id;`
  - `col_founder_box` (type_alias, line 3754) `typedef struct rc_state { /* Inside a float band column whose width was SHRUNK TO FIT: the float * founder's own box...`
  - `family` (type_alias, line 4453) `typedef struct rc_ext { int family;`
  - `mr` (type_alias, line 5568) `typedef struct item_sides { double ml, mr;`
  - `key` (type_alias, line 8656) `typedef struct rc_defer_col { int key;`
  - `col` (type_alias, line 8663) `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];`
  - `now_ms` (function, line 169) `static uint64_t now_ms(void)`
  - `gutter` (function, line 652) `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
  - `apply_zoom` (function, line 672) `static void apply_zoom(browser_window *w)`
  - `buffer_release` (function, line 683) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `fb_buffer_release` (function, line 694) `static void fb_buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 697) `static void destroy_buffer(browser_window *w)`
  - `make_slot` (function, line 707) `static int make_slot(browser_window *w, int i, size_t size, int stride)`
  - `ensure_buffer` (function, line 732) `static int ensure_buffer(browser_window *w)`
  - `read_file` (function, line 751) `static char *read_file(const char *path, size_t *out_len)`
  - `build_file_origin` (function, line 790) `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)`
  - `build_host_filter` (function, line 804) `static hb_set *build_host_filter(void)`
  - `build_js_filter` (function, line 820) `static hb_set *build_js_filter(void)`
  - `build_impersonate_optin` (function, line 823) `static int build_impersonate_optin(void)`
  - `freedom_write_dir` (function, line 832) `static int freedom_write_dir(char *out, size_t cap)`
  - `list_append_host` (function, line 861) `static int list_append_host(const char *filename, const char *host)`
  - `reload_host_list` (function, line 892) `static void reload_host_list(browser_window *w, int sel)`
  - `add_current_host_to_list` (function, line 940) `static void add_current_host_to_list(browser_window *w, int sel)`
  - `load_favorites` (function, line 974) `static void load_favorites(browser_window *w)`
  - `omni_refresh` (function, line 1011) `static void omni_refresh(browser_window *w)`
  - `profile_sync` (function, line 1042) `static void profile_sync(browser_window *w)`
  - `remember_visit` (function, line 1059) `static void remember_visit(browser_window *w, const char *url)`
  - `bookmark_toggle_current` (function, line 1067) `static void bookmark_toggle_current(browser_window *w)`
  - `proxy_addr_from_env` (function, line 1091) `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...`
  - `init_net_config` (function, line 1105) `static void init_net_config(browser_window *w)`
  - `is_https_url` (function, line 1115) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 1119) `static int is_http_url(const char *s)`
  - `host_from_url` (function, line 1130) `static int host_from_url(const char *url, char *out, size_t outsz)`
  - `toggle_fullscreen` (function, line 1163) `static void toggle_fullscreen(browser_window *w)`
  - `input_is_interactive` (function, line 1178) `static int input_is_interactive(int input_type)`
  - `input_is_editable` (function, line 1184) `static int input_is_editable(int input_type)`
  - `free_inputs` (function, line 1190) `static void free_inputs(browser_window *w)`
  - `free_images` (function, line 1198) `static void free_images(browser_window *w)`
  - `find_bg_image` (function, line 1237) `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)`
  - `replaced_edges` (function, line 1263) `static repl_edges replaced_edges(const rd_doc *doc, const rd_block *b, double cb_w)`
  - `repl_edges_x` (function, line 1287) `static double repl_edges_x(const repl_edges *e)`
  - `repl_edges_y` (function, line 1291) `static double repl_edges_y(const repl_edges *e)`
  - `image_display_size` (function, line 1325) `static int image_display_size(const browser_window *w, const rd_block *blk,
                     ...`
  - `placeholder_display_size` (function, line 1391) `static int placeholder_display_size(const rd_block *blk, double box_w,
                          ...`
  - `rebuild_inputs` (function, line 1414) `static void rebuild_inputs(browser_window *w)`
  - `find_input_state` (function, line 1440) `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)`
  - `clear_doc` (function, line 1448) `static void clear_doc(browser_window *w)`
  - `set_cache` (function, line 1458) `static void set_cache(browser_window *w, char *html, size_t len, const char *top)`
  - `img_css_w` (function, line 1471) `static uint32_t img_css_w(const tab_image *img)`
  - `img_css_h` (function, line 1472) `static uint32_t img_css_h(const tab_image *img)`
  - `surface_from_pixels` (function, line 1474) `static cairo_surface_t *surface_from_pixels(const tab_image *img)`
  - `fetch_follow_navigable` (function, line 1538) `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...`
  - `fetch_get_cached` (function, line 1546) `static sf_status fetch_get_cached(const browser_window *w, const char *url, sf_config *cfg,
     ...`
  - `fetch_post_navigable` (function, line 1554) `static sf_status fetch_post_navigable(const char *url, sf_config *cfg,
                          ...`
  - `page_host_allowlisted` (function, line 1578) `static int page_host_allowlisted(const browser_window *w)`
  - `ui_set_operator_insecure` (function, line 1587) `void ui_set_operator_insecure(int on)`
  - `apply_operator_override` (function, line 1588) `static void apply_operator_override(sf_config *cfg)`
  - `aa_note` (function, line 1605) `static void aa_note(browser_window *w, const char *abs, const char *host)`
  - `gui_subresource_fetch` (function, line 1634) `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...`
  - `gui_css_sink` (function, line 1729) `static void gui_css_sink(void *vctx, const char *url,
                         const char *body, ...`
  - `first` (function, line 1797) `* Navigation: clear the registry first (faces are per document). Untrusted:
 * no-op (fetch NULL)...`
  - `prepare_fetch` (function, line 1911) `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...`
  - `fetch_job_free` (function, line 2017) `static void fetch_job_free(fetch_job *j)`
  - `stream_progress_cb` (function, line 2038) `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)`
  - `fetch_thread` (function, line 2062) `static void *fetch_thread(void *arg)`
  - `fetch_launch` (function, line 2112) `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...`
  - `is_frame_href` (function, line 2246) `static int is_frame_href(const char *href)`
  - `load_images` (function, line 2252) `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx,
     ...`
  - `page_js_host_allowlisted` (function, line 2422) `static int page_js_host_allowlisted(const browser_window *w)`
  - `compute_page_js` (function, line 2428) `static int compute_page_js(const browser_window *w)`
  - `seed_session_cookies` (function, line 2442) `static void seed_session_cookies(tab *t, int trusted, const char *url)`
  - `seed_local_storage` (function, line 2466) `static void seed_local_storage(browser_window *w, tab *t, int trusted)`
  - `collect_local_storage` (function, line 2481) `static void collect_local_storage(browser_window *w, const tab_page *page)`
  - `foldback_session_cookies` (function, line 2491) `static void foldback_session_cookies(const char *url, const char *jar)`
  - `drop_repl_worker` (function, line 2522) `static void drop_repl_worker(browser_window *w)`
  - `schedule_js_tick` (function, line 2537) `static void schedule_js_tick(browser_window *w, int next_ms)`
  - `render_current_ex` (function, line 2547) `static void render_current_ex(browser_window *w, int allow_js_nav)`
  - `render_current` (function, line 2731) `static void render_current(browser_window *w)`
  - `show_busy` (function, line 2738) `static void show_busy(browser_window *w)`
  - `show_fetch_error` (function, line 2747) `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...`
  - `identity_load` (function, line 2815) `static void identity_load(browser_window *w)`
  - `arrives` (function, line 2825) `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...`
  - `strcmp` (function, line 2928) `&& strcmp(auth_host_buf, w->auth_host) != 0)`
  - `tab_save` (function, line 2990) `static void tab_save(browser_window *w)`
  - `tab_restore` (function, line 3008) `static void tab_restore(browser_window *w)`
  - `free_live_page` (function, line 3026) `static void free_live_page(browser_window *w)`
  - `tab_ctx_release` (function, line 3038) `static void tab_ctx_release(tab_ctx *c)`
  - `tab_switch` (function, line 3062) `static void tab_switch(browser_window *w, int idx)`
  - `uitab_close` (function, line 3124) `static void uitab_close(browser_window *w, int idx)`
  - `newtab_x` (function, line 3166) `static double newtab_x(const browser_window *w)`
  - `tab_title` (function, line 3173) `static const char *tab_title(const browser_window *w, int i)`
  - `tabbar_top` (function, line 3189) `static double tabbar_top(const browser_window *w)`
  - `toolbar_top` (function, line 3195) `static double toolbar_top(const browser_window *w)`
  - `content_geometry` (function, line 3202) `static void content_geometry(const browser_window *w, double *top, double *height)`
  - `page_side` (function, line 3228) `static double page_side(const browser_window *w, int side)`
  - `content_margin_x` (function, line 3232) `static double content_margin_x(const browser_window *w)`
  - `content_margins_x` (function, line 3243) `static double content_margins_x(const browser_window *w)`
  - `content_width` (function, line 3248) `static double content_width(const browser_window *w)`
  - `html_center_offset` (function, line 3258) `static double html_center_offset(const browser_window *w)`
  - `scrollbar_metrics` (function, line 3272) `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...`
  - `scrollbar_drag_to` (function, line 3300) `static void scrollbar_drag_to(browser_window *w)`
  - `draw_scrollbar` (function, line 3317) `static void draw_scrollbar(cairo_t *cr, const browser_window *w)`
  - `window_button_rects` (function, line 3354) `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...`
  - `toolbar_rects` (function, line 3364) `static void toolbar_rects(const browser_window *w,
                          double *back_x, doub...`
  - `toolbar_button_at` (function, line 3379) `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)`
  - `hot_actionable` (function, line 3395) `static int hot_actionable(const browser_window *w, ui_hot hot)`
  - `menu_panel_rect` (function, line 3406) `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...`
  - `ua_box_rect` (function, line 3422) `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...`
  - `draw_text` (function, line 3432) `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)`
  - `rc_float_bottom` (function, line 3853) `static double rc_float_bottom(const rc_state *s)`
  - `rc_float_clear` (function, line 3862) `static void rc_float_clear(rc_state *s)`
  - `rc_float_refresh` (function, line 3875) `static void rc_float_refresh(rc_state *s, double line_h)`
  - `rc_float_fit_line` (function, line 3921) `static void rc_float_fit_line(rc_state *s, double line_h)`
  - `line_limit` (function, line 3940) `static double line_limit(const rc_state *s, double content_w)`
  - `rc_free` (function, line 3948) `static void rc_free(rc_layout *L)`
  - `rc_add_box` (function, line 3968) `static rc_box *rc_add_box(rc_layout *L)`
  - `rc_add_frag` (function, line 3980) `static rc_frag *rc_add_frag(rc_layout *L)`
  - `rc_add_row` (function, line 3995) `static rc_row *rc_add_row(rc_layout *L)`
  - `family_face` (function, line 4007) `static const char *family_face(int family)`
  - `content_font_ex` (function, line 4029) `static void content_font_ex(cairo_t *cr, double size, int bold, int italic, int family,
         ...`
  - `sites` (function, line 4042) `* sites (wfh 0, local 0) get the bucket face, which is the toy face's twin. */
    if (wfh != 0u ...`
  - `content_font` (function, line 4051) `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,
            ...`
  - `set_rgb_alpha` (function, line 4058) `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)`
  - `utf8_clen` (function, line 4067) `static size_t utf8_clen(const char *s, size_t n)`
  - `draw_slice` (function, line 4100) `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)`
  - `frag_styled` (function, line 4113) `static int frag_styled(const rc_frag *f)`
  - `styled_advance` (function, line 4120) `static double styled_advance(cairo_t *cr, const rc_frag *f)`
  - `styled_draw` (function, line 4142) `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)`
  - `block_style` (function, line 4165) `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
  - `block_margins` (function, line 4193) `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...`
  - `area` (function, line 4230) `* box spans its CONTENT area (the font's ascent + descent plus its vertical padding
 * and border...`
  - `run` (function, line 4284) `* continuation run (block_id < 0 with no block break) deliberately skips reconcile
 * to stay on ...`
  - `atoms_extend_line` (function, line 4306) `static void atoms_extend_line(const rc_layout *L, rc_state *s, double *h,
                       ...`
  - `flush_line` (function, line 4348) `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `open_line_height` (function, line 4417) `static double open_line_height(const rc_state *s, const ui_theme *th)`
  - `open_line` (function, line 4432) `static void open_line(rc_layout *L, rc_state *s)`
  - `flow_emit_frag` (function, line 4486) `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...`
  - `flow_smallcaps_word` (function, line 4548) `static double flow_smallcaps_word(cairo_t *cr, rc_layout *L, rc_state *s,
                       ...`
  - `ibx_advance` (function, line 4603) `static void ibx_advance(const rc_layout *L, rc_state *s, double adv)`
  - `flow_text` (function, line 4611) `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...`
  - `input_inline_eligible` (function, line 4892) `static int input_inline_eligible(const rd_block *b)`
  - `input_inline_size` (function, line 4906) `static int input_inline_size(cairo_t *cr, const ui_theme *th, const rd_block *b,
                ...`
  - `replaced_inline_size` (function, line 4928) `static int replaced_inline_size(cairo_t *cr, const browser_window *w, const ui_theme *th,
       ...`
  - `replaced_is_inline_level` (function, line 4960) `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)`
  - `inlines` (function, line 4973) `* next run may also be a replaced element without its own break: consecutive
 * atomic inlines (`...`
  - `place_inline_replaced` (function, line 5010) `static int place_inline_replaced(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
    ...`
  - `css_replaced_box` (function, line 5095) `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...`
  - `emit_replaced_row` (function, line 5104) `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `block_text_style` (function, line 5217) `static void block_text_style(const browser_window *w, const ui_theme *th, const rd_block *b,
    ...`
  - `flow_text_block` (function, line 5228) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
  - `run_is_content` (function, line 5385) `static int run_is_content(const rd_block *bk)`
  - `item_root_box_pass` (function, line 5395) `static int item_root_box_pass(const rd_doc *doc, size_t b0, size_t b1, int cbox,
                ...`
  - `them` (function, line 5448) `* to them (jkanime's badge-only tiles keep their box). */
static int item_root_box_in(const rd_do...`
  - `item_root_box` (function, line 5469) `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)`
  - `itself` (function, line 5477) `* STRETCH itself (box_tree fills the line with it). */
static int css_align_to_bt(int align_kw)`
  - `box_edge_px` (function, line 5488) `static double box_edge_px(int wpx)`
  - `rc_box_copy_decoration` (function, line 5508) `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)`
  - `box_is_strict_descendant` (function, line 5601) `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)`
  - `block_space_px` (function, line 5619) `static double block_space_px(cairo_t *cr, const browser_window *w, const ui_theme *th,
          ...`
  - `item_sides_at_level` (function, line 5639) `static item_sides item_sides_at_level(cairo_t *cr, const browser_window *w, const ui_theme *th,
 ...`
  - `item_sides_at_level_raw` (function, line 5658) `static item_sides item_sides_at_level_raw(const rd_doc *doc, size_t b0, size_t b1,
              ...`
  - `container_box_of` (function, line 5725) `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)`
  - `table` (function, line 5747) `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...`
  - `row` (function, line 5812) `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...`
  - `empty_atom_outer_w` (function, line 5864) `static double empty_atom_outer_w(const rd_doc *doc, size_t k, const rd_block *bk)`
  - `measure_item_w_at` (function, line 5880) `static double measure_item_w_at(cairo_t *cr, const browser_window *w,
                           ...`
  - `lines_at` (function, line 5944) `static size_t lines_at(cairo_t *cr, const browser_window *w, const ui_theme *th,
                ...`
  - `balanced_wrap_width` (function, line 5962) `static double balanced_wrap_width(cairo_t *cr, const browser_window *w, const ui_theme *th,
     ...`
  - `item_inner_inset` (function, line 5983) `static double item_inner_inset(const rd_doc *doc, size_t b0, size_t b1, int root)`
  - `measure_item_content_w` (function, line 6010) `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
  - `run_width_cap` (function, line 6043) `static double run_width_cap(const rd_block *b, double avail_w)`
  - `def_width_cap` (function, line 6047) `static double def_width_cap(const pv_box_def *d, double avail_w)`
  - `def_declared_width` (function, line 6053) `static double def_declared_width(const pv_box_def *d, double avail_w)`
  - `cont_gap_px` (function, line 6062) `static double cont_gap_px(cairo_t *cr, const browser_window *w, const ui_theme *th,
             ...`
  - `item_declared_basis` (function, line 6069) `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
  - `nested_cont_basis` (function, line 6083) `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...`
  - `flex_item_basis` (function, line 6156) `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
  - `flex_item_min_main` (function, line 6204) `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...`
  - `item_at_level` (function, line 6269) `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `child_cont_at_level` (function, line 6284) `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `cont_in_view` (function, line 6303) `static int cont_in_view(const rd_doc *doc, int cid)`
  - `root_cont_of` (function, line 6317) `static int root_cont_of(const rd_doc *doc, int cid)`
  - `box_under` (function, line 6328) `static int box_under(const rd_doc *doc, int child, int anc)`
  - `root_cont_in` (function, line 6345) `static int root_cont_in(const rd_doc *doc, int cid, int float_box)`
  - `block_is_oof` (function, line 6389) `static int block_is_oof(const rd_doc *doc, const rd_block *bk)`
  - `item_vmargins` (function, line 6434) `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,
          ...`
  - `container_inner_h` (function, line 6455) `static double container_inner_h(const rd_doc *doc, const pv_cont_def *cdv, double content_w)`
  - `layout_container` (function, line 6495) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `slot` (function, line 6686) `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
  - `path` (function, line 6890) `*
         * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when
        ...`
  - `box_line_visible` (function, line 7548) `static int box_line_visible(int style)`
  - `col_spend_free_space` (function, line 7562) `static void col_spend_free_space(rc_layout *L, const rc_open_box *ob, double free_px)`
  - `close_top_box` (function, line 7607) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `wins` (function, line 7675) `* content taller than the ratio still wins (min-height:auto). */
        if (bx->aspect_num > 0 &...`
  - `rc_box_context` (function, line 7782) `static void rc_box_context(const rc_state *s, double content_w,
                           double...`
  - `box_margin_top` (function, line 7809) `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `box_margin_bottom` (function, line 7816) `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `children` (function, line 7826) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
  - `column` (function, line 8078) `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
  - `box_path_has` (function, line 8172) `static int box_path_has(const rd_doc *doc, int block_id, int want)`
  - `columns` (function, line 8186) `* each card made 1080px columns (huggingface, github). */
static int deepest_open_on_path(const r...`
  - `float_item_stop` (function, line 8203) `static int float_item_stop(const rd_doc *doc, const rd_block *bk, int founder_key, int base_stop)`
  - `nested_stop` (function, line 8222) `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)`
  - `box_shrink_width` (function, line 8234) `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...`
  - `reconcile_boxes_below` (function, line 8323) `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
  - `reconcile_boxes` (function, line 8454) `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
  - `box_path_of` (function, line 8482) `static int box_path_of(const rd_doc *doc, int block_id, int *out)`
  - `oof_static_xy` (function, line 8502) `static void oof_static_xy(const rc_state *s, const ui_theme *th, double content_w,
              ...`
  - `band_parent_box` (function, line 8518) `static int band_parent_box(const rd_doc *doc, const rd_block *bk)`
  - `band_common_box_ex` (function, line 8525) `static int band_common_box_ex(const rd_doc *doc, size_t start, size_t end, int skip_boxless)`
  - `band_common_box` (function, line 8550) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)`
  - `block_in_table_caption` (function, line 8620) `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)`
  - `defer_key_block` (function, line 8686) `static int defer_key_block(const rd_block *bk)`
  - `defer_append` (function, line 8886) `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...`
  - `float_founder_edges` (function, line 8951) `static double float_founder_edges(const rd_doc *doc, int float_box, double ctx_w)`
  - `defer_col_shrink_w` (function, line 8966) `static double defer_col_shrink_w(cairo_t *cr, const browser_window *w, const ui_theme *th,
      ...`
  - `defer_flush` (function, line 9021) `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...`
  - `layout_float_band` (function, line 9320) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
  - `yet` (function, line 9799) `* does not carry yet (WPT flex-abspos-staticpos-*). */
static int runs_share_float(const rd_doc *...`
  - `layout_doc` (function, line 9814) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
  - `count` (function, line 10342) `* the box count (a hostile parent cycle terminates). */
static int oof_depth(const rd_doc *doc, s...`
  - `approximation` (function, line 10361) `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */
static void oof_s...`
  - `page` (function, line 10591) `* such a page (Wikipedia's Vector skin) at 1080px, and a page made only of boxes has no
 * in-flo...`
  - `position_doc` (function, line 10610) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
  - `position_boxes` (function, line 10616) `static void position_boxes(cairo_t *cr, const browser_window *w, double content_w,
              ...`
  - `defer_root_of` (function, line 10794) `static int defer_root_of(const rc_layout *L, int bid)`
  - `defer_wants` (function, line 10802) `static int defer_wants(const rc_layout *L, int bid, int only_root)`
  - `input_box_width` (function, line 10808) `static double input_box_width(double content_w)`
  - `select_box_width` (function, line 10812) `static double select_box_width(double content_w)`
  - `button_box_width` (function, line 10817) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...`
  - `blit_image_box` (function, line 11266) `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,
                 ...`
  - `v_read` (function, line 11464) `static int v_read(int fd, void *buf, size_t n)`
  - `dies` (function, line 11492) `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
  - `audio_spawn` (function, line 11501) `static void audio_spawn(browser_window *w, int rate, int channels)`
  - `audio_mark_dead` (function, line 11555) `static void audio_mark_dead(browser_window *w)`
  - `audio_write` (function, line 11572) `static void audio_write(browser_window *w, const uint8_t *data, size_t len)`
  - `audio_stop` (function, line 11587) `static void audio_stop(browser_window *w)`
  - `video_stop` (function, line 11607) `static void video_stop(browser_window *w)`
  - `video_fetch` (function, line 11786) `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...`
  - `video_play` (function, line 11803) `static int video_play(browser_window *w, const char *m3u8_url)`
  - `video_stop` (function, line 11905) `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
  - `paint_video_row` (function, line 11959) `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
  - `row_line_slack` (function, line 12071) `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)`
  - `row_align_offset` (function, line 12083) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)`
  - `upstream` (function, line 12111) `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
  - `box_path` (function, line 12139) `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `paint_box_shadow_layer` (function, line 12150) `static void paint_box_shadow_layer(cairo_t *cr, double x, double y, double w, double h,
         ...`
  - `text` (function, line 12241) `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
  - `grad_stop` (function, line 12268) `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)`
  - `bui_grad_color_at` (function, line 12283) `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...`
  - `spaced` (function, line 12316) `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
  - `paint_bg_layer` (function, line 12349) `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...`
  - `paint_gradient_fill` (function, line 12395) `static void paint_gradient_fill(cairo_t *cr, const rc_box *bx, double x, double y,
              ...`
  - `paint_gradient_tiled` (function, line 12442) `static void paint_gradient_tiled(cairo_t *cr, const rc_box *bx, double x, double y,
             ...`
  - `paint_box_decoration` (function, line 12469) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
  - `widths` (function, line 12594) `* the outer minus the adjacent border widths (CSS Backgrounds 3 5.2). The straight
     * per-sid...`
  - `cairo_set_dash` (function, line 12630) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 12633) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 12679) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 12682) `cairo_set_dash(cr, (double[])`
  - `set_rgb` (function, line 12716) `set_rgb(cr, (ui_rgb)`
  - `cairo_set_dash` (function, line 12740) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 12743) `cairo_set_dash(cr, (double[])`
  - `paint_deco_line` (function, line 12801) `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...`
  - `cairo_set_dash` (function, line 12835) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 12837) `cairo_set_dash(cr, (double[])`
  - `paint_svg_at` (function, line 12857) `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...`
  - `replaced_current_color` (function, line 12877) `static int replaced_current_color(const browser_window *w, const rd_block *blk)`
  - `paint_inline_replaced` (function, line 12886) `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...`
  - `paint_content_row` (function, line 12931) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
  - `paint_content_row_ex` (function, line 12938) `static void paint_content_row_ex(cairo_t *cr, browser_window *w, const rc_layout *L,
            ...`
  - `ov_box_clips` (function, line 13153) `static int ov_box_clips(const pv_box_def *d)`
  - `ov_collect_chain` (function, line 13160) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)`
  - `ov_box_bounds` (function, line 13181) `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)`
  - `ov_content_rect` (function, line 13207) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...`
  - `fragment` (function, line 13223) `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
  - `box_forms_stacking_context` (function, line 13278) `static int box_forms_stacking_context(const pv_box_def *def)`
  - `bui_skew_tan` (function, line 13322) `static double bui_skew_tan(int deg)`
  - `box_transform_matrix` (function, line 13329) `static int box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
              ...`
  - `bui_blend_operator` (function, line 13457) `static cairo_operator_t bui_blend_operator(int mix_blend)`
  - `bui_gaussian_blur_surface` (function, line 13483) `static void bui_gaussian_blur_surface(cairo_surface_t *surf, double sigma)`
  - `bui_paint_backdrop_blur` (function, line 13526) `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...`
  - `bui_mask_ref_rect` (function, line 13596) `static int bui_mask_ref_rect(const rc_layout *L, int ref, rc_box *out)`
  - `bui_build_mask` (function, line 13612) `static cairo_surface_t *bui_build_mask(const pv_box_def *def, const rc_box *bx_in,
              ...`
  - `bui_pop_group_composite` (function, line 13728) `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms,
    ...`
  - `limits` (function, line 13980) `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
  - `paint_box_decoration_grouped` (function, line 14049) `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
  - `paint_box_and_direct_rows` (function, line 14090) `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...`
  - `bui_pop_group_composite` (function, line 14166) `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
  - `paint_oof_sub` (function, line 14220) `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,
                ...`
  - `paint_positioned_one` (function, line 14258) `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...`
  - `box` (function, line 14379) `* content belongs to that box (painted by its own positioned entry). */
    if (sub == NULL)`
  - `paint_owned_negz` (function, line 14484) `static void paint_owned_negz(cairo_t *cr, browser_window *w, rc_layout *L, double left,
         ...`
  - `paint_nested_children` (function, line 14500) `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...`
  - `bui_pop_group_composite` (function, line 14523) `bui_pop_group_composite(cr, cdef, now_ms() - w->page_load_mono_ms, &L->boxes[j], left, origin,
  ...`
  - `geom_from_layout` (function, line 14538) `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,
                ...`
  - `publish_geometry` (function, line 14569) `static void publish_geometry(browser_window *w, const rc_layout *L, double left,
                ...`
  - `defer_root_z` (function, line 14631) `static int defer_root_z(const rd_doc *doc, size_t root)`
  - `defer_root_before` (function, line 14637) `static int defer_root_before(const rd_doc *doc, const rc_layout *L, size_t a, size_t b)`
  - `paint_positioned_layer` (function, line 14643) `static void paint_positioned_layer(cairo_t *cr, browser_window *w, const ui_theme *th,
          ...`
  - `paint_screen_inflow` (function, line 14708) `static void paint_screen_inflow(const screen_flow_ctx *c, int only_root)`
  - `bui_pop_group_composite` (function, line 14775) `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
  - `lazy_slot` (function, line 14829) `static ui_image *lazy_slot(browser_window *w, const char *href, size_t *idx)`
  - `lazy_load_one` (function, line 14840) `static void lazy_load_one(browser_window *w, ui_image *slot, const rd_block *b)`
  - `load_lazy_bg_images` (function, line 14896) `static void load_lazy_bg_images(browser_window *w, const rc_layout *L, double origin,
           ...`
  - `paint_screen_deferred` (function, line 14931) `static void paint_screen_deferred(void *ctx, int root)`
  - `gui_prof_now_ms` (function, line 14936) `static double gui_prof_now_ms(void)`
  - `gui_prof_log` (function, line 14941) `static void gui_prof_log(const char *what, double ms)`
  - `paint_structured` (function, line 14947) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
  - `write_doc_pdf` (function, line 15078) `static long write_doc_pdf(browser_window *w, const char *path)`
  - `export_pdf` (function, line 15187) `static void export_pdf(browser_window *w)`
  - `ui_render_viewport_w` (function, line 15242) `int ui_render_viewport_w(void)`
  - `paint_png_inflow` (function, line 15271) `static void paint_png_inflow(const png_flow_ctx *c, int only_root)`
  - `paint_png_deferred` (function, line 15307) `static void paint_png_deferred(void *ctx, int root)`
  - `write_doc_png` (function, line 15407) `static long write_doc_png(browser_window *w, const char *path)`
  - `render_frame_surface` (function, line 15419) `static cairo_surface_t *render_frame_surface(const pv_view *view, tab *ft, const char *url,
     ...`
  - `fill_frame_slot` (function, line 15460) `static void fill_frame_slot(browser_window *w, const rd_block *b, ui_image *slot,
               ...`
  - `refresh_frame_images` (function, line 15518) `static void refresh_frame_images(browser_window *w)`
  - `export_png` (function, line 15536) `static void export_png(browser_window *w)`
  - `caller` (function, line 15570) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
  - `ui_render_png` (function, line 15593) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)`
  - `render_doc_images` (function, line 15653) `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...`
  - `ui_render_png_images` (function, line 15686) `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_png_frames` (function, line 15692) `ui_status ui_render_png_frames(const rd_doc *doc, tab *t, const char *top_url,
                  ...`

Next: [KB_gui_p2.md](KB_gui_p2.md)
