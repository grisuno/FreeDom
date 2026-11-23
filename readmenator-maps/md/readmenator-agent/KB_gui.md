# Subsystem: gui (page 1 of 3)
Pages: [KB_gui.md](KB_gui.md), [KB_gui_p2.md](KB_gui_p2.md), [KB_gui_p3.md](KB_gui_p3.md)

## gui/browser_ui.c
- Doc: ui_input_state: Live editable state for one form text control, aliasing a block of the current...
- Layer: presentation
- Language: c
- Symbols:
  - `ui_menu_item` (struct, line 207)
  - `ui_input_state` (struct, line 249)
  - `ui_image` (struct, line 274)
  - `ui_bg_image` (struct, line 288)
  - `tab_ctx` (struct, line 307)
  - `browser_window` (struct, line 329)
  - `fip_hit` (struct, line 735)
  - `repl_edges` (struct, line 1388)
  - `gui_sub_prep` (struct, line 1796)
  - `gui_net_ctx` (struct, line 1890)
  - `fetch_prep` (struct, line 2150)
  - `fetch_job` (struct, line 2231)
  - `rc_frag` (struct, line 3826)
  - `rc_row` (struct, line 3893)
  - `rc_box` (struct, line 3916)
  - `rc_oof_sub` (struct, line 3977)
  - `rc_table_ctx` (struct, line 3981)
  - `rc_layout` (struct, line 3990)
  - `rc_oof_sub` (struct, line 4048)
  - `rc_open_box` (struct, line 4058)
  - `rc_ibox` (struct, line 4111)
  - `rc_state` (struct, line 4156)
  - `rc_ext` (struct, line 4865)
  - `item_sides` (struct, line 5981)
  - `rc_defer_col` (struct, line 9447)
  - `rc_defer` (struct, line 9454)
  - `bui_mask_ctx` (struct, line 14728)
  - `screen_flow_ctx` (struct, line 15850)
  - `frame_undo` (struct, line 16347)
  - `png_flow_ctx` (struct, line 16710)
  - `freebug_window` (struct, line 19389)
  - `ui_menu_action` (enum, line 189)
  - `rc_rowkind` (enum, line 3891)
  - `ui_hot` (type_alias, line 241) `typedef int ui_hot;`
  - `bs` (type_alias, line 307) `typedef struct tab_ctx { browser_state bs;`
  - `addr` (type_alias, line 734) `typedef struct fip_hit { uintptr_t addr;`
  - `freebug_window` (type_alias, line 744) `typedef struct freebug_window freebug_window;`
  - `pl` (type_alias, line 1388) `typedef struct repl_edges { double mt, mr, mb, ml, bt, br, bb, bl, pt, pr, pb, pl;`
  - `ln` (type_alias, line 1796) `typedef struct gui_sub_prep { ln_result ln;`
  - `allowlisted` (type_alias, line 2150) `typedef struct fetch_prep { int allowlisted;`
  - `font_size` (type_alias, line 3825) `typedef struct rc_frag { double x, width, font_size;`
  - `kind` (type_alias, line 3892) `typedef struct rc_row { rc_rowkind kind;`
  - `h` (type_alias, line 3916) `typedef struct rc_box { double x, top, w, h;`
  - `cid` (type_alias, line 3981) `typedef struct rc_table_ctx { int cid;`
  - `block_id` (type_alias, line 4058) `typedef struct rc_open_box { int block_id;`
  - `col_founder_box` (type_alias, line 4155) `typedef struct rc_state { /* Inside a float band column whose width was SHRUNK TO FIT: the float * founder's own box...`
  - `family` (type_alias, line 4865) `typedef struct rc_ext { int family;`
  - `mr` (type_alias, line 5981) `typedef struct item_sides { double ml, mr;`
  - `key` (type_alias, line 9447) `typedef struct rc_defer_col { int key;`
  - `col` (type_alias, line 9454) `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];`
  - `now_ms` (function, line 176) `static uint64_t now_ms(void)`
  - `gutter` (function, line 765) `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
  - `apply_zoom` (function, line 785) `static void apply_zoom(browser_window *w)`
  - `buffer_release` (function, line 796) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `fb_buffer_release` (function, line 807) `static void fb_buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 810) `static void destroy_buffer(browser_window *w)`
  - `make_slot` (function, line 820) `static int make_slot(browser_window *w, int i, size_t size, int stride)`
  - `ensure_buffer` (function, line 845) `static int ensure_buffer(browser_window *w)`
  - `read_file` (function, line 864) `static char *read_file(const char *path, size_t *out_len)`
  - `build_file_origin` (function, line 903) `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)`
  - `build_host_filter` (function, line 917) `static hb_set *build_host_filter(void)`
  - `build_js_filter` (function, line 933) `static hb_set *build_js_filter(void)`
  - `build_impersonate_optin` (function, line 936) `static int build_impersonate_optin(void)`
  - `freedom_write_dir` (function, line 945) `static int freedom_write_dir(char *out, size_t cap)`
  - `list_append_host` (function, line 974) `static int list_append_host(const char *filename, const char *host)`
  - `reload_host_list` (function, line 1008) `static void reload_host_list(browser_window *w, int sel)`
  - `add_current_host_to_list` (function, line 1058) `static int add_current_host_to_list(browser_window *w, int sel)`
  - `load_favorites` (function, line 1093) `static void load_favorites(browser_window *w)`
  - `omni_refresh` (function, line 1130) `static void omni_refresh(browser_window *w)`
  - `profile_sync` (function, line 1161) `static void profile_sync(browser_window *w)`
  - `remember_visit` (function, line 1178) `static void remember_visit(browser_window *w, const char *url)`
  - `bookmark_star_state` (function, line 1187) `static int bookmark_star_state(const browser_window *w)`
  - `bookmark_toggle_current` (function, line 1194) `static void bookmark_toggle_current(browser_window *w)`
  - `proxy_addr_from_env` (function, line 1218) `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...`
  - `init_net_config` (function, line 1232) `static void init_net_config(browser_window *w)`
  - `is_https_url` (function, line 1242) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 1246) `static int is_http_url(const char *s)`
  - `host_from_url` (function, line 1257) `static int host_from_url(const char *url, char *out, size_t outsz)`
  - `toggle_fullscreen` (function, line 1295) `static void toggle_fullscreen(browser_window *w)`
  - `input_is_interactive` (function, line 1310) `static int input_is_interactive(int input_type)`
  - `input_is_editable` (function, line 1316) `static int input_is_editable(int input_type)`
  - `free_inputs` (function, line 1322) `static void free_inputs(browser_window *w)`
  - `free_images` (function, line 1330) `static void free_images(browser_window *w)`
  - `find_bg_image` (function, line 1369) `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)`
  - `replaced_edges` (function, line 1395) `static repl_edges replaced_edges(const rd_doc *doc, const rd_block *b, double cb_w)`
  - `repl_edges_x` (function, line 1419) `static double repl_edges_x(const repl_edges *e)`
  - `repl_edges_y` (function, line 1423) `static double repl_edges_y(const repl_edges *e)`
  - `set_packed_rgba` (function, line 1429) `static void set_packed_rgba(cairo_t *cr, int col)`
  - `image_display_size` (function, line 1465) `static int image_display_size(const browser_window *w, const rd_block *blk,
                     ...`
  - `placeholder_display_size` (function, line 1531) `static int placeholder_display_size(const rd_block *blk, double box_w,
                          ...`
  - `rebuild_inputs` (function, line 1554) `static void rebuild_inputs(browser_window *w)`
  - `find_input_state` (function, line 1580) `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)`
  - `set_doc` (function, line 1588) `static void set_doc(browser_window *w, rd_doc *d)`
  - `clear_doc` (function, line 1595) `static void clear_doc(browser_window *w)`
  - `load_requests_reset` (function, line 1605) `static void load_requests_reset(browser_window *w)`
  - `set_cache` (function, line 1613) `static void set_cache(browser_window *w, char *html, size_t len, const char *top)`
  - `img_css_w` (function, line 1630) `static uint32_t img_css_w(const tab_image *img)`
  - `img_css_h` (function, line 1631) `static uint32_t img_css_h(const tab_image *img)`
  - `surface_from_pixels` (function, line 1633) `static cairo_surface_t *surface_from_pixels(const tab_image *img)`
  - `fetch_follow_navigable` (function, line 1697) `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...`
  - `fetch_get_cached` (function, line 1705) `static sf_status fetch_get_cached(const browser_window *w, const char *url, sf_config *cfg,
     ...`
  - `fetch_post_navigable` (function, line 1713) `static sf_status fetch_post_navigable(const char *url, sf_config *cfg,
                          ...`
  - `page_host_allowlisted` (function, line 1737) `static int page_host_allowlisted(const browser_window *w)`
  - `ui_set_operator_insecure` (function, line 1746) `void ui_set_operator_insecure(int on)`
  - `apply_operator_override` (function, line 1747) `static void apply_operator_override(sf_config *cfg)`
  - `aa_note` (function, line 1764) `static void aa_note(browser_window *w, const char *abs, const char *host)`
  - `gui_sub_prepare` (function, line 1803) `static int gui_sub_prepare(browser_window *w, const char *top, int trusted, int top_allowed,
    ...`
  - `gui_sub_perform` (function, line 1844) `static int gui_sub_perform(gui_sub_prep *p, const char *method, const void *body, size_t body_len...`
  - `gui_subresource_fetch` (function, line 1873) `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...`
  - `gui_net_ctx_free` (function, line 1898) `static void gui_net_ctx_free(void *p)`
  - `gui_net_ctx_new` (function, line 1906) `static gui_net_ctx *gui_net_ctx_new(browser_window *w)`
  - `net_ctx_lock` (function, line 1919) `static void net_ctx_lock(browser_window *w)`
  - `net_ctx_unlock` (function, line 1920) `static void net_ctx_unlock(browser_window *w)`
  - `gui_net_ctx_retire` (function, line 1923) `static void gui_net_ctx_retire(gui_net_ctx *c)`
  - `gui_async_fetch` (function, line 1930) `static int gui_async_fetch(void *vctx, const char *method, const char *url,
                     ...`
  - `gui_css_sink` (function, line 1977) `static void gui_css_sink(void *vctx, const char *url,
                         const char *body, ...`
  - `first` (function, line 2045) `* Navigation: clear the registry first (faces are per document). Untrusted:
 * no-op (fetch NULL)...`
  - `prepare_fetch` (function, line 2159) `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...`
  - `fetch_job_free` (function, line 2266) `static void fetch_job_free(fetch_job *j)`
  - `stream_progress_cb` (function, line 2288) `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)`
  - `fetch_job_cancelled` (function, line 2313) `static int fetch_job_cancelled(void *ctx)`
  - `fetch_thread` (function, line 2321) `static void *fetch_thread(void *arg)`
  - `stream_discard` (function, line 2376) `static void stream_discard(browser_window *w)`
  - `nav_supersede` (function, line 2387) `static void nav_supersede(browser_window *w)`
  - `fetch_launch` (function, line 2395) `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...`
  - `is_frame_href` (function, line 2530) `static int is_frame_href(const char *href)`
  - `load_images` (function, line 2536) `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx,
     ...`
  - `page_js_host_allowlisted` (function, line 2717) `static int page_js_host_allowlisted(const browser_window *w)`
  - `compute_page_js` (function, line 2723) `static int compute_page_js(const browser_window *w)`
  - `seed_session_cookies` (function, line 2737) `static void seed_session_cookies(tab *t, int trusted, const char *url)`
  - `seed_local_storage` (function, line 2761) `static void seed_local_storage(browser_window *w, tab *t, int trusted)`
  - `collect_local_storage` (function, line 2776) `static void collect_local_storage(browser_window *w, const tab_page *page)`
  - `foldback_session_cookies` (function, line 2786) `static void foldback_session_cookies(const char *url, const char *jar)`
  - `drop_repl_worker` (function, line 2819) `static void drop_repl_worker(browser_window *w)`
  - `gui_viewport_w` (function, line 2836) `static int gui_viewport_w(const browser_window *w)`
  - `schedule_js_tick` (function, line 2843) `static void schedule_js_tick(browser_window *w, int next_ms)`
  - `render_current_ex` (function, line 2853) `static void render_current_ex(browser_window *w, int allow_js_nav)`
  - `render_current` (function, line 3054) `static void render_current(browser_window *w)`
  - `show_busy` (function, line 3061) `static void show_busy(browser_window *w)`
  - `show_fetch_error` (function, line 3070) `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...`
  - `identity_load` (function, line 3139) `static void identity_load(browser_window *w)`
  - `arrives` (function, line 3149) `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...`
  - `strcmp` (function, line 3256) `&& strcmp(auth_host_buf, w->auth_host) != 0)`
  - `tab_save` (function, line 3330) `static void tab_save(browser_window *w)`
  - `tab_restore` (function, line 3353) `static void tab_restore(browser_window *w)`
  - `free_live_page` (function, line 3376) `static void free_live_page(browser_window *w)`
  - `tab_ctx_release` (function, line 3390) `static void tab_ctx_release(tab_ctx *c)`
  - `tab_show_ready` (function, line 3420) `static void tab_show_ready(browser_window *w)`
  - `tab_switch` (function, line 3429) `static void tab_switch(browser_window *w, int idx)`
  - `uitab_close` (function, line 3495) `static void uitab_close(browser_window *w, int idx)`
  - `chrome_of` (function, line 3534) `static chl_layout chrome_of(const browser_window *w)`
  - `tab_move` (function, line 3545) `static void tab_move(browser_window *w, int from, int to)`
  - `tab_title` (function, line 3572) `static const char *tab_title(const browser_window *w, int i, char *buf, size_t cap)`
  - `tabbar_top` (function, line 3592) `static double tabbar_top(const browser_window *w)`
  - `toolbar_top` (function, line 3599) `static double toolbar_top(const browser_window *w)`
  - `content_geometry` (function, line 3608) `static void content_geometry(const browser_window *w, double *top, double *height)`
  - `page_side` (function, line 3638) `static double page_side(const browser_window *w, int side)`
  - `content_margin_x` (function, line 3642) `static double content_margin_x(const browser_window *w)`
  - `content_margins_x` (function, line 3653) `static double content_margins_x(const browser_window *w)`
  - `content_width` (function, line 3658) `static double content_width(const browser_window *w)`
  - `html_center_offset` (function, line 3668) `static double html_center_offset(const browser_window *w)`
  - `scrollbar_metrics` (function, line 3682) `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...`
  - `scrollbar_drag_to` (function, line 3710) `static void scrollbar_drag_to(browser_window *w)`
  - `draw_scrollbar` (function, line 3727) `static void draw_scrollbar(cairo_t *cr, const browser_window *w)`
  - `chrome_hot_at` (function, line 3766) `static ui_hot chrome_hot_at(const browser_window *w, double px, double py)`
  - `hot_actionable` (function, line 3778) `static int hot_actionable(const browser_window *w, ui_hot hot)`
  - `menu_panel_rect` (function, line 3790) `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...`
  - `ua_box_rect` (function, line 3805) `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...`
  - `rc_float_bottom` (function, line 4254) `static double rc_float_bottom(const rc_state *s)`
  - `rc_float_clear` (function, line 4263) `static void rc_float_clear(rc_state *s)`
  - `rc_float_refresh` (function, line 4276) `static void rc_float_refresh(rc_state *s, double line_h)`
  - `rc_float_fit_line` (function, line 4322) `static void rc_float_fit_line(rc_state *s, double line_h)`
  - `line_limit` (function, line 4341) `static double line_limit(const rc_state *s, double content_w)`
  - `rc_free` (function, line 4349) `static void rc_free(rc_layout *L)`
  - `rc_add_box` (function, line 4369) `static rc_box *rc_add_box(rc_layout *L)`
  - `rc_add_frag` (function, line 4381) `static rc_frag *rc_add_frag(rc_layout *L)`
  - `rc_add_row` (function, line 4396) `static rc_row *rc_add_row(rc_layout *L)`
  - `family_face` (function, line 4408) `static const char *family_face(int family)`
  - `content_font_ex` (function, line 4430) `static void content_font_ex(cairo_t *cr, double size, int bold, int italic, int family,
         ...`
  - `sites` (function, line 4443) `* sites (wfh 0, local 0) get the bucket face, which is the toy face's twin. */
    if (wfh != 0u ...`
  - `content_font` (function, line 4452) `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,
            ...`
  - `set_rgb_alpha` (function, line 4459) `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)`
  - `utf8_clen` (function, line 4468) `static size_t utf8_clen(const char *s, size_t n)`
  - `draw_slice` (function, line 4501) `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)`
  - `frag_styled` (function, line 4514) `static int frag_styled(const rc_frag *f)`
  - `styled_advance` (function, line 4521) `static double styled_advance(cairo_t *cr, const rc_frag *f)`
  - `styled_draw` (function, line 4543) `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)`
  - `block_style` (function, line 4566) `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
  - `block_margins` (function, line 4594) `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...`
  - `area` (function, line 4631) `* box spans its CONTENT area (the font's ascent + descent plus its vertical padding
 * and border...`
  - `leave_inline_box` (function, line 4694) `static void leave_inline_box(rc_layout *L, rc_state *s, const rd_doc *doc, int block_id)`
  - `atoms_extend_line` (function, line 4716) `static void atoms_extend_line(const rc_layout *L, rc_state *s, double *h,
                       ...`
  - `flush_line` (function, line 4758) `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `open_line_height` (function, line 4829) `static double open_line_height(const rc_state *s, const ui_theme *th)`
  - `open_line` (function, line 4844) `static void open_line(rc_layout *L, rc_state *s)`
  - `flow_emit_frag` (function, line 4898) `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...`
  - `flow_smallcaps_word` (function, line 4960) `static double flow_smallcaps_word(cairo_t *cr, rc_layout *L, rc_state *s,
                       ...`
  - `ibx_advance` (function, line 5015) `static void ibx_advance(const rc_layout *L, rc_state *s, double adv)`
  - `flow_text` (function, line 5024) `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...`
  - `input_inline_eligible` (function, line 5305) `static int input_inline_eligible(const rd_block *b)`
  - `input_inline_size` (function, line 5319) `static int input_inline_size(cairo_t *cr, const ui_theme *th, const rd_block *b,
                ...`
  - `replaced_inline_size` (function, line 5341) `static int replaced_inline_size(cairo_t *cr, const browser_window *w, const ui_theme *th,
       ...`
  - `replaced_is_inline_level` (function, line 5373) `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)`
  - `inlines` (function, line 5386) `* next run may also be a replaced element without its own break: consecutive
 * atomic inlines (`...`
  - `place_inline_replaced` (function, line 5423) `static int place_inline_replaced(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
    ...`
  - `css_replaced_box` (function, line 5508) `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...`
  - `emit_replaced_row` (function, line 5517) `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `block_text_style` (function, line 5630) `static void block_text_style(const browser_window *w, const ui_theme *th, const rd_block *b,
    ...`
  - `flow_text_block` (function, line 5641) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
  - `run_is_content` (function, line 5798) `static int run_is_content(const rd_block *bk)`
  - `item_root_box_pass` (function, line 5808) `static int item_root_box_pass(const rd_doc *doc, size_t b0, size_t b1, int cbox,
                ...`
  - `them` (function, line 5861) `* to them (jkanime's badge-only tiles keep their box). */
static int item_root_box_in(const rd_do...`
  - `item_root_box` (function, line 5882) `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)`
  - `itself` (function, line 5890) `* STRETCH itself (box_tree fills the line with it). */
static int css_align_to_bt(int align_kw)`
  - `box_edge_px` (function, line 5901) `static double box_edge_px(int wpx)`
  - `rc_box_copy_decoration` (function, line 5921) `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)`
  - `box_is_strict_descendant` (function, line 6014) `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)`
  - `block_space_px` (function, line 6032) `static double block_space_px(cairo_t *cr, const browser_window *w, const ui_theme *th,
          ...`
  - `item_sides_at_level` (function, line 6052) `static item_sides item_sides_at_level(cairo_t *cr, const browser_window *w, const ui_theme *th,
 ...`
  - `item_sides_at_level_raw` (function, line 6071) `static item_sides item_sides_at_level_raw(const rd_doc *doc, size_t b0, size_t b1,
              ...`
  - `container_box_of` (function, line 6138) `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)`
  - `table` (function, line 6160) `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...`
  - `row` (function, line 6225) `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...`
  - `empty_atom_outer_w` (function, line 6277) `static double empty_atom_outer_w(const rd_doc *doc, size_t k, const rd_block *bk)`
  - `sized_block_content_w` (function, line 6297) `static double sized_block_content_w(const rd_doc *doc, const rd_block *bk)`
  - `inside` (function, line 6314) `* whatever its own items do inside (jkanime's fixed nav: one `<a display:flex>` per
 * entry, mea...`
  - `measure_item_w_at` (function, line 6330) `static double measure_item_w_at(cairo_t *cr, const browser_window *w,
                           ...`
  - `lines_at` (function, line 6404) `static size_t lines_at(cairo_t *cr, const browser_window *w, const ui_theme *th,
                ...`
  - `balanced_wrap_width` (function, line 6422) `static double balanced_wrap_width(cairo_t *cr, const browser_window *w, const ui_theme *th,
     ...`
  - `item_inner_inset` (function, line 6443) `static double item_inner_inset(const rd_doc *doc, size_t b0, size_t b1, int root)`
  - `measure_item_content_w` (function, line 6470) `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
  - `run_width_cap` (function, line 6503) `static double run_width_cap(const rd_block *b, double avail_w)`
  - `def_width_cap` (function, line 6507) `static double def_width_cap(const pv_box_def *d, double avail_w)`
  - `def_declared_width` (function, line 6513) `static double def_declared_width(const pv_box_def *d, double avail_w)`
  - `cont_gap_px` (function, line 6522) `static double cont_gap_px(cairo_t *cr, const browser_window *w, const ui_theme *th,
             ...`
  - `item_declared_basis` (function, line 6529) `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
  - `nested_cont_basis` (function, line 6548) `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...`
  - `flex_item_basis` (function, line 6629) `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
  - `flex_item_min_main` (function, line 6677) `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...`
  - `text_atom_continues_line` (function, line 6735) `static int text_atom_continues_line(const rd_doc *doc, size_t run_i, int box_id)`
  - `item_at_level` (function, line 6769) `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `child_cont_at_level` (function, line 6784) `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)`
  - `cont_in_view` (function, line 6803) `static int cont_in_view(const rd_doc *doc, int cid)`
  - `root_cont_of` (function, line 6817) `static int root_cont_of(const rd_doc *doc, int cid)`
  - `box_under` (function, line 6828) `static int box_under(const rd_doc *doc, int child, int anc)`
  - `root_cont_in` (function, line 6845) `static int root_cont_in(const rd_doc *doc, int cid, int float_box)`
  - `block_is_oof` (function, line 6889) `static int block_is_oof(const rd_doc *doc, const rd_block *bk)`
  - `item_vmargins` (function, line 6934) `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,
          ...`
  - `container_inner_h` (function, line 6955) `static double container_inner_h(const rd_doc *doc, const pv_cont_def *cdv, double content_w)`
  - `cont_next_item` (function, line 6998) `static int cont_next_item(const rd_doc *doc, int cid, size_t end, size_t *k, size_t *e)`
  - `table_item_slot` (function, line 7015) `static void table_item_slot(const rd_doc *doc, size_t k, int cid, int *row, int *col, int *span)`
  - `table_solve` (function, line 7037) `static double table_solve(cairo_t *cr, const browser_window *w, const ui_theme *th,
             ...`
  - `layout_container` (function, line 7262) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
  - `slot` (function, line 7458) `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
  - `box_line_visible` (function, line 8272) `static int box_line_visible(int style)`
  - `col_spend_free_space` (function, line 8286) `static void col_spend_free_space(rc_layout *L, const rc_open_box *ob, double free_px)`
  - `close_top_box` (function, line 8331) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
  - `wins` (function, line 8399) `* content taller than the ratio still wins (min-height:auto). */
        if (bx->aspect_num > 0 &...`
  - `rc_box_context` (function, line 8506) `static void rc_box_context(const rc_state *s, double content_w,
                           double...`
  - `box_margin_top` (function, line 8533) `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `box_margin_bottom` (function, line 8540) `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
  - `children` (function, line 8550) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
  - `column` (function, line 8802) `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
  - `box_path_has` (function, line 8896) `static int box_path_has(const rd_doc *doc, int block_id, int want)`
  - `columns` (function, line 8910) `* each card made 1080px columns (huggingface, github). */
static int deepest_open_on_path(const r...`
  - `float_item_stop` (function, line 8927) `static int float_item_stop(const rd_doc *doc, const rd_block *bk, int founder_key, int base_stop)`
  - `nested_stop` (function, line 8946) `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)`
  - `table_box_shrink_width` (function, line 8957) `static double table_box_shrink_width(cairo_t *cr, const browser_window *w, const ui_theme *th,
  ...`
  - `box_shrink_width` (function, line 9006) `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...`
  - `reconcile_boxes_below` (function, line 9095) `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
  - `reconcile_boxes` (function, line 9245) `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
  - `box_path_of` (function, line 9273) `static int box_path_of(const rd_doc *doc, int block_id, int *out)`
  - `oof_static_xy` (function, line 9293) `static void oof_static_xy(const rc_state *s, const ui_theme *th, double content_w,
              ...`
  - `band_parent_box` (function, line 9309) `static int band_parent_box(const rd_doc *doc, const rd_block *bk)`
  - `band_common_box_ex` (function, line 9316) `static int band_common_box_ex(const rd_doc *doc, size_t start, size_t end, int skip_boxless)`
  - `band_common_box` (function, line 9341) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)`
  - `block_in_table_caption` (function, line 9411) `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)`
  - `defer_key_block` (function, line 9477) `static int defer_key_block(const rd_block *bk)`
  - `defer_append` (function, line 9677) `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...`
  - `float_founder_edges` (function, line 9742) `static double float_founder_edges(const rd_doc *doc, int float_box, double ctx_w)`
  - `defer_col_shrink_w` (function, line 9757) `static double defer_col_shrink_w(cairo_t *cr, const browser_window *w, const ui_theme *th,
      ...`
  - `defer_flush` (function, line 9812) `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...`
  - `layout_float_band` (function, line 10111) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
  - `yet` (function, line 10590) `* does not carry yet (WPT flex-abspos-staticpos-*). */
static int runs_share_float(const rd_doc *...`
  - `layout_doc` (function, line 10605) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
  - `count` (function, line 11140) `* the box count (a hostile parent cycle terminates). */
static int oof_depth(const rd_doc *doc, s...`
  - `approximation` (function, line 11159) `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */
static void oof_s...`
  - `page` (function, line 11389) `* such a page (Wikipedia's Vector skin) at 1080px, and a page made only of boxes has no
 * in-flo...`
  - `position_doc` (function, line 11408) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
  - `position_boxes` (function, line 11414) `static void position_boxes(cairo_t *cr, const browser_window *w, double content_w,
              ...`
  - `defer_root_of` (function, line 11596) `static int defer_root_of(const rc_layout *L, int bid)`
  - `defer_wants` (function, line 11604) `static int defer_wants(const rc_layout *L, int bid, int only_root)`
  - `input_box_width` (function, line 11610) `static double input_box_width(double content_w)`
  - `select_box_width` (function, line 11614) `static double select_box_width(double content_w)`
  - `button_box_width` (function, line 11619) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...`
  - `blit_image_box` (function, line 12068) `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,
                 ...`
  - `v_read` (function, line 12269) `static int v_read(int fd, void *buf, size_t n)`
  - `dies` (function, line 12297) `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
  - `audio_spawn` (function, line 12306) `static void audio_spawn(browser_window *w, int rate, int channels)`
  - `audio_mark_dead` (function, line 12360) `static void audio_mark_dead(browser_window *w)`
  - `audio_write` (function, line 12377) `static void audio_write(browser_window *w, const uint8_t *data, size_t len)`
  - `audio_stop` (function, line 12392) `static void audio_stop(browser_window *w)`
  - `video_stop` (function, line 12448) `static void video_stop(browser_window *w)`
  - `video_feed_cancelled` (function, line 12602) `static int video_feed_cancelled(void *ctx)`
  - `video_fetch_ex` (function, line 12608) `static sf_status video_fetch_ex(const char *url, browser_window *w, sf_response *resp,
          ...`
  - `video_fetch` (function, line 12623) `static sf_status video_fetch(const char *url, browser_window *w, sf_response *resp)`
  - `video_play` (function, line 12633) `static int video_play(browser_window *w, const char *m3u8_url)`
  - `video_pipeline_up` (function, line 12707) `static int video_pipeline_up(browser_window *w, size_t start_seg)`
  - `video_seek_to` (function, line 12746) `static void video_seek_to(browser_window *w, double t)`
  - `video_position_s` (function, line 12754) `static double video_position_s(const browser_window *w)`
  - `video_toggle_pause` (function, line 12761) `static void video_toggle_pause(browser_window *w)`
  - `video_stop` (function, line 12776) `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
  - `video_draw_rect` (function, line 12853) `static void video_draw_rect(const browser_window *w, double *x, double *y,
                      ...`
  - `blit_video_frame` (function, line 12892) `static int blit_video_frame(cairo_t *cr, browser_window *w,
                            double x,...`
  - `paint_video_row` (function, line 12920) `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
  - `row_line_slack` (function, line 12998) `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)`
  - `row_align_offset` (function, line 13010) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)`
  - `upstream` (function, line 13038) `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
  - `box_path` (function, line 13066) `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `box_shadow_layers` (function, line 13079) `static int box_shadow_layers(const rc_box *bx, int layers[PV_BSHADOW_LAYERS][6])`
  - `cr_mask_cache` (function, line 13103) `static mkc_cache *cr_mask_cache(cairo_t *cr)`
  - `shadow_mask_surface` (function, line 13141) `static cairo_surface_t *shadow_mask_surface(mkc_cache *mc, const mkc_key *k)`
  - `paint_box_shadow_layer` (function, line 13181) `static void paint_box_shadow_layer(cairo_t *cr, double x, double y, double w, double h,
         ...`
  - `text` (function, line 13258) `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
  - `grad_stop` (function, line 13285) `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)`
  - `bui_grad_color_at` (function, line 13300) `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...`
  - `spaced` (function, line 13333) `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
  - `paint_bg_layer` (function, line 13366) `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...`
  - `paint_gradient_fill` (function, line 13412) `static void paint_gradient_fill(cairo_t *cr, const rc_box *bx, double x, double y,
              ...`
  - `paint_gradient_tiled` (function, line 13459) `static void paint_gradient_tiled(cairo_t *cr, const rc_box *bx, double x, double y,
             ...`
  - `paint_box_decoration` (function, line 13486) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
  - `widths` (function, line 13604) `* the outer minus the adjacent border widths (CSS Backgrounds 3 5.2). The straight
     * per-sid...`
  - `cairo_set_dash` (function, line 13640) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 13643) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 13689) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 13692) `cairo_set_dash(cr, (double[])`
  - `set_rgb` (function, line 13726) `set_rgb(cr, (ui_rgb)`
  - `cairo_set_dash` (function, line 13750) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 13753) `cairo_set_dash(cr, (double[])`
  - `paint_deco_line` (function, line 13811) `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...`
  - `cairo_set_dash` (function, line 13845) `cairo_set_dash(cr, (double[])`
  - `cairo_set_dash` (function, line 13847) `cairo_set_dash(cr, (double[])`
  - `paint_svg_at` (function, line 13866) `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...`
  - `replaced_current_color` (function, line 13886) `static int replaced_current_color(const browser_window *w, const rd_block *blk)`
  - `paint_inline_replaced` (function, line 13895) `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...`
  - `fip_lower` (function, line 13934) `static size_t fip_lower(const browser_window *w, uintptr_t addr)`
  - `fip_paint_frag` (function, line 13945) `static void fip_paint_frag(cairo_t *cr, const browser_window *w, const rc_frag *f,
              ...`
  - `fip_clear_hits` (function, line 13966) `static void fip_clear_hits(browser_window *w)`
  - `fip_hit_cmp` (function, line 13977) `static int fip_hit_cmp(const void *a, const void *b)`
  - `fip_collect` (function, line 13983) `static void fip_collect(const rc_layout *L, double dy, ft_piece *p, double *ys, size_t cap,
     ...`
  - `fip_sync` (function, line 14005) `static void fip_sync(browser_window *w, const rc_layout *L)`
  - `fip_reveal` (function, line 14055) `static void fip_reveal(browser_window *w, double content_h)`
  - `paint_content_row` (function, line 14073) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
  - `paint_content_row_ex` (function, line 14079) `static void paint_content_row_ex(cairo_t *cr, browser_window *w, const rc_layout *L,
            ...`
  - `ov_box_clips` (function, line 14293) `static int ov_box_clips(const pv_box_def *d)`
  - `ov_collect_chain` (function, line 14300) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)`
  - `ov_box_bounds` (function, line 14321) `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)`
  - `ov_content_rect` (function, line 14347) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...`
  - `fragment` (function, line 14363) `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
  - `box_forms_stacking_context` (function, line 14418) `static int box_forms_stacking_context(const pv_box_def *def)`
  - `bui_skew_tan` (function, line 14462) `static double bui_skew_tan(int deg)`
  - `box_transform_matrix` (function, line 14469) `static int box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
              ...`
  - `bui_blend_operator` (function, line 14597) `static cairo_operator_t bui_blend_operator(int mix_blend)`
  - `bui_gaussian_blur_surface` (function, line 14623) `static void bui_gaussian_blur_surface(cairo_surface_t *surf, double sigma)`
  - `bui_paint_backdrop_blur` (function, line 14666) `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...`
  - `bui_mask_ref_rect` (function, line 14736) `static int bui_mask_ref_rect(const rc_layout *L, int ref, rc_box *out)`
  - `bui_build_mask` (function, line 14752) `static cairo_surface_t *bui_build_mask(const pv_box_def *def, const rc_box *bx_in,
              ...`
  - `bui_pop_group_composite` (function, line 14868) `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms,
    ...`
  - `limits` (function, line 15123) `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
  - `paint_box_decoration_grouped` (function, line 15192) `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
  - `paint_box_and_direct_rows` (function, line 15233) `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...`
  - `bui_pop_group_composite` (function, line 15309) `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
  - `paint_oof_sub` (function, line 15363) `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,

Next: [KB_gui_p2.md](KB_gui_p2.md)
