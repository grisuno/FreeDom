# Symbols (page 2 of 18)
Previous: [SYMBOLS.md](SYMBOLS.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `paint` | function | `gui/browser_ui.c:17962` | `static void paint(browser_window *w)` |
| `paint_bg_layer` | function | `gui/browser_ui.c:12830` | `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,                ...` |
| `paint_box_and_direct_rows` | function | `gui/browser_ui.c:14707` | `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,        ...` |
| `paint_box_decoration` | function | `gui/browser_ui.c:12950` | `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,            ...` |
| `paint_box_decoration_grouped` | function | `gui/browser_ui.c:14666` | `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,                         ...` |
| `paint_box_shadow_layer` | function | `gui/browser_ui.c:12645` | `static void paint_box_shadow_layer(cairo_t *cr, double x, double y, double w, double h,          ...` |
| `paint_chrome` | function | `gui/browser_ui.c:17900` | `static void paint_chrome(cairo_t *cr, browser_window *w)` |
| `paint_content_row` | function | `gui/browser_ui.c:13539` | `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,                ...` |
| `paint_content_row_ex` | function | `gui/browser_ui.c:13546` | `static void paint_content_row_ex(cairo_t *cr, browser_window *w, const rc_layout *L,             ...` |
| `paint_deco_line` | function | `gui/browser_ui.c:13275` | `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,                        ...` |
| `paint_gradient_fill` | function | `gui/browser_ui.c:12876` | `static void paint_gradient_fill(cairo_t *cr, const rc_box *bx, double x, double y,               ...` |
| `paint_gradient_tiled` | function | `gui/browser_ui.c:12923` | `static void paint_gradient_tiled(cairo_t *cr, const rc_box *bx, double x, double y,              ...` |
| `paint_inline_replaced` | function | `gui/browser_ui.c:13360` | `static void paint_inline_replaced(cairo_t *cr, browser_window *w,                                ...` |
| `paint_nested_children` | function | `gui/browser_ui.c:15117` | `static void paint_nested_children(cairo_t *cr, browser_window *w,                                ...` |
| `paint_oof_sub` | function | `gui/browser_ui.c:14837` | `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,                 ...` |
| `paint_owned_negz` | function | `gui/browser_ui.c:15101` | `static void paint_owned_negz(cairo_t *cr, browser_window *w, rc_layout *L, double left,          ...` |
| `paint_png_deferred` | function | `gui/browser_ui.c:16122` | `static void paint_png_deferred(void *ctx, int root)` |
| `paint_png_inflow` | function | `gui/browser_ui.c:16085` | `static void paint_png_inflow(const png_flow_ctx *c, int only_root)` |
| `paint_positioned_layer` | function | `gui/browser_ui.c:15266` | `static void paint_positioned_layer(cairo_t *cr, browser_window *w, const ui_theme *th,           ...` |
| `paint_positioned_one` | function | `gui/browser_ui.c:14875` | `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,             ...` |
| `paint_screen_deferred` | function | `gui/browser_ui.c:15554` | `static void paint_screen_deferred(void *ctx, int root)` |
| `paint_screen_inflow` | function | `gui/browser_ui.c:15331` | `static void paint_screen_inflow(const screen_flow_ctx *c, int only_root)` |
| `paint_structured` | function | `gui/browser_ui.c:15730` | `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,                 ...` |
| `paint_svg_at` | function | `gui/browser_ui.c:13331` | `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,                          doub...` |
| `paint_video_row` | function | `gui/browser_ui.c:12350` | `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,                 ...` |
| `path` | function | `gui/browser_ui.c:9032` | `* overflow degrades to the old inline path (fail-open: content overlaps or * stacks instead of vanishing). With no...` |
| `pl` | type_alias | `gui/browser_ui.c:1297` | `typedef struct repl_edges { double mt, mr, mb, ml, bt, br, bb, bl, pt, pr, pb, pl;` |
| `place_inline_replaced` | function | `gui/browser_ui.c:5076` | `static int place_inline_replaced(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,     ...` |
| `placeholder_display_size` | function | `gui/browser_ui.c:1432` | `static int placeholder_display_size(const rd_block *blk, double box_w,                           ...` |
| `png_flow_ctx` | struct | `gui/browser_ui.c:16072` | `` |
| `position_boxes` | function | `gui/browser_ui.c:11007` | `static void position_boxes(cairo_t *cr, const browser_window *w, double content_w,               ...` |
| `position_doc` | function | `gui/browser_ui.c:11001` | `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,                 ...` |
| `prepare_fetch` | function | `gui/browser_ui.c:1961` | `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,                     ...` |
| `presentation` | function | `gui/browser_ui.c:17569` | `* affect presentation (a repaint, which re-runs layout, suffices);` |
| `proceed` | function | `gui/browser_ui.c:1958` | `* may proceed (cfg and pr->allowlisted are then set);` |
| `produced` | function | `gui/browser_ui.c:4647` | `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target...` |
| `profile_sync` | function | `gui/browser_ui.c:1083` | `static void profile_sync(browser_window *w)` |
| `proxy` | function | `gui/browser_ui.c:1143` | `* and enable each proxy ("1" => the default port);` |
| `proxy_addr_from_env` | function | `gui/browser_ui.c:1132` | `static int proxy_addr_from_env(const char *envname, const char *deflt,                           ...` |
| `ptr_axis` | function | `gui/browser_ui.c:19427` | `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,                      uint32...` |
| `ptr_button` | function | `gui/browser_ui.c:19189` | `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,               ...` |
| `ptr_enter` | function | `gui/browser_ui.c:19056` | `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,                       struct wl_...` |
| `ptr_frame` | function | `gui/browser_ui.c:19451` | `static void ptr_frame(void *d, struct wl_pointer *p)` |
| `ptr_leave` | function | `gui/browser_ui.c:19074` | `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)` |
| `ptr_motion` | function | `gui/browser_ui.c:19091` | `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)` |
| `publish_geometry` | function | `gui/browser_ui.c:15192` | `static void publish_geometry(browser_window *w, const rc_layout *L, double left,                 ...` |
| `rc_add_box` | function | `gui/browser_ui.c:4027` | `static rc_box *rc_add_box(rc_layout *L)` |
| `rc_add_frag` | function | `gui/browser_ui.c:4039` | `static rc_frag *rc_add_frag(rc_layout *L)` |
| `rc_add_row` | function | `gui/browser_ui.c:4054` | `static rc_row *rc_add_row(rc_layout *L)` |
| `rc_box` | struct | `gui/browser_ui.c:3574` | `` |
| `rc_box_context` | function | `gui/browser_ui.c:8110` | `static void rc_box_context(const rc_state *s, double content_w,                            double...` |
| `rc_box_copy_decoration` | function | `gui/browser_ui.c:5574` | `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)` |
| `rc_defer` | struct | `gui/browser_ui.c:9054` | `` |
| `rc_defer_col` | struct | `gui/browser_ui.c:9047` | `` |
| `rc_ext` | struct | `gui/browser_ui.c:4518` | `` |
| `rc_float_bottom` | function | `gui/browser_ui.c:3912` | `static double rc_float_bottom(const rc_state *s)` |
| `rc_float_clear` | function | `gui/browser_ui.c:3921` | `static void rc_float_clear(rc_state *s)` |
| `rc_float_fit_line` | function | `gui/browser_ui.c:3980` | `static void rc_float_fit_line(rc_state *s, double line_h)` |
| `rc_float_refresh` | function | `gui/browser_ui.c:3934` | `static void rc_float_refresh(rc_state *s, double line_h)` |
| `rc_frag` | struct | `gui/browser_ui.c:3484` | `` |
| `rc_free` | function | `gui/browser_ui.c:4007` | `static void rc_free(rc_layout *L)` |
| `rc_ibox` | struct | `gui/browser_ui.c:3769` | `` |
| `rc_layout` | struct | `gui/browser_ui.c:3648` | `` |
| `rc_oof_sub` | struct | `gui/browser_ui.c:3635` | `` |
| `rc_oof_sub` | struct | `gui/browser_ui.c:3706` | `` |
| `rc_open_box` | struct | `gui/browser_ui.c:3716` | `` |
| `rc_row` | struct | `gui/browser_ui.c:3551` | `` |
| `rc_rowkind` | enum | `gui/browser_ui.c:3549` | `` |
| `rc_state` | struct | `gui/browser_ui.c:3814` | `` |
| `rc_table_ctx` | struct | `gui/browser_ui.c:3639` | `` |
| `rd_build` | function | `gui/browser_ui.c:11642` | `* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr...` |
| `read_file` | function | `gui/browser_ui.c:792` | `static char *read_file(const char *path, size_t *out_len)` |
| `rebuild_inputs` | function | `gui/browser_ui.c:1455` | `static void rebuild_inputs(browser_window *w)` |
| `reconcile_boxes` | function | `gui/browser_ui.c:8845` | `static void reconcile_boxes(cairo_t *cr, const browser_window *w,                             rc_...` |
| `reconcile_boxes_below` | function | `gui/browser_ui.c:8699` | `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,                          ...` |
| `rect` | function | `gui/browser_ui.c:12718` | `* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops...` |
| `redraw` | function | `gui/browser_ui.c:18066` | `static void redraw(browser_window *w)` |
| `redraws` | function | `gui/browser_ui.c:20764` | `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A...` |
| `reference` | function | `gui/browser_ui.c:16867` | `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:  * hostile content...` |
| `refresh_frame_images` | function | `gui/browser_ui.c:16333` | `static void refresh_frame_images(browser_window *w)` |
| `registry_global` | function | `gui/browser_ui.c:20537` | `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,                  ...` |
| `registry_remove` | function | `gui/browser_ui.c:20557` | `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)` |
| `reload_host_list` | function | `gui/browser_ui.c:933` | `static void reload_host_list(browser_window *w, int sel)` |
| `remember_visit` | function | `gui/browser_ui.c:1100` | `static void remember_visit(browser_window *w, const char *url)` |
| `render_current` | function | `gui/browser_ui.c:2796` | `static void render_current(browser_window *w)` |
| `render_current_ex` | function | `gui/browser_ui.c:2612` | `static void render_current_ex(browser_window *w, int allow_js_nav)` |
| `render_doc_images` | function | `gui/browser_ui.c:16468` | `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,               ...` |
| `render_frame_surface` | function | `gui/browser_ui.c:16234` | `static cairo_surface_t *render_frame_surface(const pv_view *view, tab *ft, const char *url,      ...` |
| `repl_edges` | struct | `gui/browser_ui.c:1297` | `` |
| `repl_edges_x` | function | `gui/browser_ui.c:1328` | `static double repl_edges_x(const repl_edges *e)` |
| `repl_edges_y` | function | `gui/browser_ui.c:1332` | `static double repl_edges_y(const repl_edges *e)` |
| `replaced_current_color` | function | `gui/browser_ui.c:13351` | `static int replaced_current_color(const browser_window *w, const rd_block *blk)` |
| `replaced_edges` | function | `gui/browser_ui.c:1304` | `static repl_edges replaced_edges(const rd_doc *doc, const rd_block *b, double cb_w)` |
| `replaced_inline_size` | function | `gui/browser_ui.c:4994` | `static int replaced_inline_size(cairo_t *cr, const browser_window *w, const ui_theme *th,        ...` |
| `replaced_is_inline_level` | function | `gui/browser_ui.c:5026` | `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)` |
| `resizes` | function | `gui/browser_ui.c:18119` | `* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);` |
| `resolve` | function | `gui/browser_ui.c:3033` | `* origin so its relative references and local images resolve (confined to the * document's directory) -- a local...` |
| `resolve_box_cursor` | function | `gui/browser_ui.c:16691` | `static int resolve_box_cursor(const rd_doc *doc, int block_id)` |
| `root_cont_in` | function | `gui/browser_ui.c:6449` | `static int root_cont_in(const rd_doc *doc, int cid, int float_box)` |
| `root_cont_of` | function | `gui/browser_ui.c:6421` | `static int root_cont_of(const rd_doc *doc, int cid)` |
| `row` | function | `gui/browser_ui.c:5878` | `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */ static d...` |
| `row_align_offset` | function | `gui/browser_ui.c:12474` | `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)` |
| `row_line_slack` | function | `gui/browser_ui.c:12462` | `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)` |
| `row_owner_block_id` | function | `gui/browser_ui.c:13326` | `static int row_owner_block_id(const rc_layout *L, const rc_row *r);` |
| `rows` | function | `gui/browser_ui.c:13837` | `* RC_IMAGE rows (see its declaration);` |
| `run` | function | `gui/browser_ui.c:4343` | `* continuation run (block_id < 0 with no block break) deliberately skips reconcile * to stay on the line, and that...` |
| `run_is_content` | function | `gui/browser_ui.c:5451` | `static int run_is_content(const rd_block *bk)` |
| `run_width_cap` | function | `gui/browser_ui.c:6134` | `static double run_width_cap(const rd_block *b, double avail_w)` |
| `save_current_page` | function | `gui/browser_ui.c:17333` | `static void save_current_page(browser_window *w)` |
| `save_download` | function | `gui/browser_ui.c:17300` | `static void save_download(browser_window *w, const char *url, const char *bytes,                 ...` |
| `saving` | function | `gui/browser_ui.c:20670` | `* disables saving (never clobber);` |
| `schedule_js_tick` | function | `gui/browser_ui.c:2602` | `static void schedule_js_tick(browser_window *w, int next_ms)` |
| `screen_flow_ctx` | struct | `gui/browser_ui.c:15320` | `` |
| `scroll_line_px` | function | `gui/browser_ui.c:19423` | `static double scroll_line_px(const browser_window *w)` |
| `scrollbar_drag_to` | function | `gui/browser_ui.c:3369` | `static void scrollbar_drag_to(browser_window *w)` |
| `scrollbar_metrics` | function | `gui/browser_ui.c:3341` | `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,          ...` |
| `seat_caps` | function | `gui/browser_ui.c:20519` | `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)` |
| `seat_name` | function | `gui/browser_ui.c:20530` | `static void seat_name(void *d, struct wl_seat *s, const char *name)` |
| `secure_fetch` | function | `gui/browser_ui.c:2228` | `* through secure_fetch (Zero Trust);` |
| `seed_local_storage` | function | `gui/browser_ui.c:2531` | `static void seed_local_storage(browser_window *w, tab *t, int trusted)` |
| `seed_session_cookies` | function | `gui/browser_ui.c:2507` | `static void seed_session_cookies(tab *t, int trusted, const char *url)` |
| `select_box_width` | function | `gui/browser_ui.c:11203` | `static double select_box_width(double content_w)` |
| `set_cache` | function | `gui/browser_ui.c:1506` | `static void set_cache(browser_window *w, char *html, size_t len, const char *top)` |
| `set_cursor` | function | `gui/browser_ui.c:18154` | `static void set_cursor(browser_window *w, int cur_kind)` |
| `set_doc` | function | `gui/browser_ui.c:1489` | `static void set_doc(browser_window *w, rd_doc *d)` |
| `set_page_url` | function | `gui/browser_ui.c:16886` | `static void set_page_url(browser_window *w, const char *url)` |
| `set_rgb` | function | `gui/browser_ui.c:13190` | `set_rgb(cr, (ui_rgb)` |
| `set_rgb_alpha` | function | `gui/browser_ui.c:4117` | `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)` |
| `sf_ws_url_check` | function | `gui/browser_ui.c:16969` | `&& sf_ws_url_check(op->data) == SF_OK && rp_host_of(op->data, host, sizeof host) == 0 &&...` |
| `shadow_mask_surface` | function | `gui/browser_ui.c:12605` | `static cairo_surface_t *shadow_mask_surface(mkc_cache *mc, const mkc_key *k)` |
| `show_busy` | function | `gui/browser_ui.c:2803` | `static void show_busy(browser_window *w)` |
| `show_fetch_error` | function | `gui/browser_ui.c:2812` | `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,                   ...` |
| `sites` | function | `gui/browser_ui.c:4101` | `* sites (wfh 0, local 0) get the bucket face, which is the toy face's twin. */     if (wfh != 0u ...` |
| `sized_block_content_w` | function | `gui/browser_ui.c:5950` | `static double sized_block_content_w(const rd_doc *doc, const rd_block *bk)` |
| `slot` | function | `gui/browser_ui.c:7062` | `* layout slot (item 0 → rightmost, last item → leftmost). */     if (use_flex && cdv.direction ==...` |
| `smaller` | function | `gui/browser_ui.c:3600` | `* size when the content is smaller (height) or wider (min-width);` |
| `spaced` | function | `gui/browser_ui.c:12797` | `* or evenly spaced (bui_grad_color_at). */ static void bui_paint_conic(cairo_t *cr, double x, dou...` |
| `standalone` | function | `gui/browser_ui.c:10501` | `* must not be treated as standalone (which would flush that line and give * the element a row of its own -- R7). */...` |
| `startup_abort_release` | function | `gui/browser_ui.c:20636` | `static void startup_abort_release(browser_window *w)` |
| `stop_loading` | function | `gui/browser_ui.c:19119` | `static int stop_loading(browser_window *w)` |
| `strcmp` | function | `gui/browser_ui.c:2996` | `&& strcmp(auth_host_buf, w->auth_host) != 0)` |
| `stream_progress_cb` | function | `gui/browser_ui.c:2088` | `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)` |
| `string` | function | `gui/browser_ui.c:2396` | `* or an empty string (unset, blocked, or off by caps.images), so there is no * decision to re-check, unlike...` |
| `struct` | function | `gui/browser_ui.c:7213` | `* struct (0 = auto);` |
| `styled_advance` | function | `gui/browser_ui.c:4179` | `static double styled_advance(cairo_t *cr, const rc_frag *f)` |
| `styled_draw` | function | `gui/browser_ui.c:4201` | `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)` |
| `stylesheets` | function | `gui/browser_ui.c:2635` | `* External stylesheets (Hito 27) follow the author-styles opt-in -- or the * trusted-host doctrine (Hito 28)...` |
| `surface_from_pixels` | function | `gui/browser_ui.c:1524` | `static cairo_surface_t *surface_from_pixels(const tab_image *img)` |
| `tab_ctx` | struct | `gui/browser_ui.c:299` | `` |
| `tab_ctx_release` | function | `gui/browser_ui.c:3110` | `static void tab_ctx_release(tab_ctx *c)` |
| `tab_new` | function | `gui/browser_ui.c:2462` | `static void tab_new(browser_window *w, const char *url);` |
| `tab_restore` | function | `gui/browser_ui.c:3079` | `static void tab_restore(browser_window *w)` |
| `tab_save` | function | `gui/browser_ui.c:3060` | `static void tab_save(browser_window *w)` |
| `tab_switch` | function | `gui/browser_ui.c:3134` | `static void tab_switch(browser_window *w, int idx)` |
| `tab_title` | function | `gui/browser_ui.c:3245` | `static const char *tab_title(const browser_window *w, int i)` |
| `tabbar_top` | function | `gui/browser_ui.c:3256` | `static double tabbar_top(const browser_window *w)` |
| `table` | function | `gui/browser_ui.c:5813` | `* synthesised table (no descriptors to disagree) keeps the stamp. */         if (cd != NULL && !c...` |
| `table_box_shrink_width` | function | `gui/browser_ui.c:8561` | `static double table_box_shrink_width(cairo_t *cr, const browser_window *w, const ui_theme *th,   ...` |
| `table_item_slot` | function | `gui/browser_ui.c:6619` | `static void table_item_slot(const rd_doc *doc, size_t k, int cid, int *row, int *col, int *span)` |
| `table_solve` | function | `gui/browser_ui.c:6641` | `static double table_solve(cairo_t *cr, const browser_window *w, const ui_theme *th,              ...` |
| `text` | function | `gui/browser_ui.c:12722` | `* fill and gradient text (2026-07-19). */ static cairo_pattern_t *bui_linear_grad(double x, doubl...` |
| `the` | function | `gui/browser_ui.c:14512` | `* the (already filtered) group with the shadow color, blur it, and * paint it under the group at the declared offset...` |
| `them` | function | `gui/browser_ui.c:5514` | `* to them (jkanime's badge-only tiles keep their box). */ static int item_root_box_in(const rd_do...` |
| `toggle` | function | `gui/browser_ui.c:2476` | `* No network: a capability toggle (images/CSS) re-renders from cache. Does nothing * when there is no cached source...` |
| `toggle_fullscreen` | function | `gui/browser_ui.c:1204` | `static void toggle_fullscreen(browser_window *w)` |
| `toggle_reader` | function | `gui/browser_ui.c:17538` | `static void toggle_reader(browser_window *w)` |
| `toolbar_top` | function | `gui/browser_ui.c:3263` | `static double toolbar_top(const browser_window *w)` |
| `toplevel_close` | function | `gui/browser_ui.c:18133` | `static void toplevel_close(void *data, struct xdg_toplevel *t)` |
| `toplevel_configure` | function | `gui/browser_ui.c:18111` | `static void toplevel_configure(void *data, struct xdg_toplevel *t,                               ...` |
| `treatment` | function | `gui/browser_ui.c:8757` | `* block treatment (shrink-wrapped and placed by text-align), which is what a * standalone centred call-to-action...` |
| `ua_box_rect` | function | `gui/browser_ui.c:3463` | `static void ua_box_rect(const browser_window *w, double *x, double *y,                         do...` |
| `ui_bg_image` | struct | `gui/browser_ui.c:280` | `` |
| `ui_dump_layout` | function | `gui/browser_ui.c:16528` | `ui_status ui_dump_layout(const rd_doc *doc)` |
| `ui_hot` | type_alias | `gui/browser_ui.c:233` | `typedef int ui_hot;` |
| `ui_image` | struct | `gui/browser_ui.c:266` | `` |
| `ui_input_state` | struct | `gui/browser_ui.c:241` | `` |
| `ui_menu_action` | enum | `gui/browser_ui.c:181` | `` |
| `ui_menu_item` | struct | `gui/browser_ui.c:199` | `` |
| `ui_render_pdf_images` | function | `gui/browser_ui.c:16513` | `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,                   ...` |
| `ui_render_png` | function | `gui/browser_ui.c:16408` | `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)` |
| `ui_render_png_frames` | function | `gui/browser_ui.c:16507` | `ui_status ui_render_png_frames(const rd_doc *doc, tab *t, const char *top_url,                   ...` |
| `ui_render_png_images` | function | `gui/browser_ui.c:16501` | `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,                   ...` |
| `ui_render_viewport_w` | function | `gui/browser_ui.c:16056` | `int ui_render_viewport_w(void)` |
| `ui_run_browser` | function | `gui/browser_ui.c:20647` | `ui_status ui_run_browser(const char *start_url)` |
| `ui_set_operator_insecure` | function | `gui/browser_ui.c:1637` | `void ui_set_operator_insecure(int on)` |
| `uitab_close` | function | `gui/browser_ui.c:3200` | `static void uitab_close(browser_window *w, int idx)` |
| `update_hover` | function | `gui/browser_ui.c:18195` | `static void update_hover(browser_window *w)` |
| `upstream` | function | `gui/browser_ui.c:12502` | `* upstream (see spec/css.md). */ static void box_path4(cairo_t *cr, double x, double y, double w,...` |
| `utf8_clen` | function | `gui/browser_ui.c:4126` | `static size_t utf8_clen(const char *s, size_t n)` |
| `v_read` | function | `gui/browser_ui.c:11855` | `static int v_read(int fd, void *buf, size_t n)` |
| `video_feeder_thread` | function | `gui/browser_ui.c:1199` | `static void *video_feeder_thread(void *arg);` |
| `video_fetch` | function | `gui/browser_ui.c:12177` | `static sf_status video_fetch(const char *url, browser_window *w,                               sf...` |
| `video_play` | function | `gui/browser_ui.c:12194` | `static int video_play(browser_window *w, const char *m3u8_url)` |
| `video_stop` | function | `gui/browser_ui.c:11998` | `static void video_stop(browser_window *w)` |
| `video_stop` | function | `gui/browser_ui.c:12296` | `* each segment loop so a video_stop() in the main thread (which sets it to 0  * then calls pthrea...` |
| `way` | function | `gui/browser_ui.c:5923` | `* intrinsic box either way (it does not wrap below its own size). */ static int block_leaves_flow(const rd_doc *doc...` |
| `wc_render_caps` | function | `gui/browser_ui.c:17037` | `return wc_render_caps(wc_derive((wc_input)` |
| `width` | function | `gui/browser_ui.c:6001` | `* the line: the layout spends its width (reconcile_boxes_below), so the * measure must too, or the label wraps...` |
| `widths` | function | `gui/browser_ui.c:13068` | `* the outer minus the adjacent border widths (CSS Backgrounds 3 5.2). The straight      * per-sid...` |
| `wins` | function | `gui/browser_ui.c:8003` | `* content taller than the ratio still wins (min-height:auto). */         if (bx->aspect_num > 0 &...` |
| `wl_array_for_each` | function | `gui/browser_ui.c:18127` | `wl_array_for_each(st, states)` |
| `wm_base_ping` | function | `gui/browser_ui.c:18097` | `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)` |
| `write_doc_pdf` | function | `gui/browser_ui.c:15892` | `static long write_doc_pdf(browser_window *w, const char *path)` |
| `write_doc_png` | function | `gui/browser_ui.c:16222` | `static long write_doc_png(browser_window *w, const char *path)` |
| `write_file_atomic` | function | `gui/browser_ui.c:17278` | `static int write_file_atomic(const char *path, const void *bytes, size_t len)` |
| `ws_apply_ops` | function | `gui/browser_ui.c:16959` | `static void ws_apply_ops(browser_window *w, const tab_page *page)` |
| `x` | function | `gui/browser_ui.c:9494` | `* reported x is already the BORDER x (the §7c.2 rule);` |
| `xdg_surface_configure` | function | `gui/browser_ui.c:18103` | `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)` |
| `yet` | function | `gui/browser_ui.c:10190` | `* does not carry yet (WPT flex-abspos-staticpos-*). */ static int runs_share_float(const rd_doc *...` |
| `BUI_CHROME_FONT` | macro | `gui/browser_ui_internal.h:127` | `#define BUI_CHROME_FONT` |
| `BUI_CHROME_FONT_SIZE` | macro | `gui/browser_ui_internal.h:128` | `#define BUI_CHROME_FONT_SIZE` |
| `BUI_URL_FONT_SIZE` | macro | `gui/browser_ui_internal.h:129` | `#define BUI_URL_FONT_SIZE` |
| `FREEDOM_BROWSER_UI_INTERNAL_H` | macro | `gui/browser_ui_internal.h:2` | `#define FREEDOM_BROWSER_UI_INTERNAL_H` |
| `UI_FONT_SIZE` | macro | `gui/browser_ui_internal.h:30` | `#define UI_FONT_SIZE` |
| `UI_HEADING_LEVELS` | macro | `gui/browser_ui_internal.h:32` | `#define UI_HEADING_LEVELS` |
| `UI_TEXT_MARGIN` | macro | `gui/browser_ui_internal.h:31` | `#define UI_TEXT_MARGIN` |
| `area` | function | `gui/browser_ui_internal.h:179` | `* tiled over the mask area (ax, ay, aw, ah) by the layer geometry `geo` (css.h CSS_MG_*, * resolved by...` |
| `b` | type_alias | `gui/browser_ui_internal.h:40` | `typedef struct ui_rgb { double r, g, b;` |
| `body_font` | type_alias | `gui/browser_ui_internal.h:42` | `typedef struct ui_theme { double body_font;` |
| `bui_chrome_font` | function | `gui/browser_ui_internal.h:165` | `void bui_chrome_font(cairo_t *cr, double size);` |
| `bui_chrome_view` | struct | `gui/browser_ui_internal.h:132` | `` |
| `bui_find_view` | struct | `gui/browser_ui_internal.h:150` | `` |
| `bui_paint_chrome` | function | `gui/browser_ui_internal.h:167` | `void bui_paint_chrome(cairo_t *cr, const bui_chrome_view *v);` |
| `bui_paint_findbar` | function | `gui/browser_ui_internal.h:163` | `void bui_paint_findbar(cairo_t *cr, const bui_find_view *v);` |
| `bui_round_rect` | function | `gui/browser_ui_internal.h:174` | `void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double r);` |
| `bui_url_index_at` | function | `gui/browser_ui_internal.h:172` | `size_t bui_url_index_at(cairo_t *cr, const bui_chrome_view *v, double x);` |
| `bui_url_text_x` | function | `gui/browser_ui_internal.h:170` | `double bui_url_text_x(const bui_chrome_view *v, cairo_t *cr, double *shift);` |
| `set_rgb` | function | `gui/browser_ui_internal.h:120` | `void set_rgb(cairo_t *cr, ui_rgb c);` |
| `ui_rgb` | struct | `gui/browser_ui_internal.h:41` | `` |
| `ui_theme` | struct | `gui/browser_ui_internal.h:43` | `` |
| `ui_theme_mode` | enum | `gui/browser_ui_internal.h:107` | `` |
| `BUI_DISABLED` | macro | `gui/bui_chrome.c:30` | `#define BUI_DISABLED` |
| `BUI_FOCUS_RING` | macro | `gui/bui_chrome.c:28` | `#define BUI_FOCUS_RING` |
| `BUI_ICON_LINE` | macro | `gui/bui_chrome.c:19` | `#define BUI_ICON_LINE` |
| `BUI_INACTIVE_TEXT` | macro | `gui/bui_chrome.c:29` | `#define BUI_INACTIVE_TEXT` |
| `BUI_PILL_RADIUS` | macro | `gui/bui_chrome.c:21` | `#define BUI_PILL_RADIUS` |
| `BUI_SPINNER_R` | macro | `gui/bui_chrome.c:24` | `#define BUI_SPINNER_R` |
| `BUI_STOP_HALF` | macro | `gui/bui_chrome.c:25` | `#define BUI_STOP_HALF` |
| `BUI_TAB_FADE` | macro | `gui/bui_chrome.c:23` | `#define BUI_TAB_FADE` |
| `BUI_TAB_PAD` | macro | `gui/bui_chrome.c:22` | `#define BUI_TAB_PAD` |
| `BUI_TAB_RADIUS` | macro | `gui/bui_chrome.c:20` | `#define BUI_TAB_RADIUS` |
| `BUI_TWO_PI` | macro | `gui/bui_chrome.c:18` | `#define BUI_TWO_PI` |
| `BUI_URL_END_PAD` | macro | `gui/bui_chrome.c:27` | `#define BUI_URL_END_PAD` |
| `BUI_URL_MEASURE` | macro | `gui/bui_chrome.c:31` | `#define BUI_URL_MEASURE` |
| `BUI_URL_TEXT_PAD` | macro | `gui/bui_chrome.c:26` | `#define BUI_URL_TEXT_PAD` |
| `bui_chrome_font` | function | `gui/bui_chrome.c:61` | `void bui_chrome_font(cairo_t *cr, double size)` |
| `bui_paint_chrome` | function | `gui/bui_chrome.c:569` | `void bui_paint_chrome(cairo_t *cr, const bui_chrome_view *v)` |
| `bui_paint_findbar` | function | `gui/bui_chrome.c:655` | `void bui_paint_findbar(cairo_t *cr, const bui_find_view *v)` |
| `bui_round_rect` | function | `gui/bui_chrome.c:35` | `void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double r)` |
| `bui_url_index_at` | function | `gui/bui_chrome.c:310` | `size_t bui_url_index_at(cairo_t *cr, const bui_chrome_view *v, double x)` |
| `bui_url_text_x` | function | `gui/bui_chrome.c:296` | `double bui_url_text_x(const bui_chrome_view *v, cairo_t *cr, double *shift)` |
| `find_button` | function | `gui/bui_chrome.c:635` | `static void find_button(cairo_t *cr, const bui_find_view *v, chl_rect r, chl_find_part part,     ...` |
| `glyph_info` | function | `gui/bui_chrome.c:210` | `static void glyph_info(cairo_t *cr, double cx, double cy)` |
| `glyph_lock` | function | `gui/bui_chrome.c:161` | `static void glyph_lock(cairo_t *cr, double cx, double cy)` |
| `glyph_overlay` | function | `gui/bui_chrome.c:192` | `static void glyph_overlay(cairo_t *cr, double cx, double cy)` |
| `glyph_page` | function | `gui/bui_chrome.c:200` | `static void glyph_page(cairo_t *cr, double cx, double cy)` |
| `glyph_shield` | function | `gui/bui_chrome.c:137` | `static void glyph_shield(cairo_t *cr, double cx, double cy, int check, int fill)` |
| `glyph_warning` | function | `gui/bui_chrome.c:173` | `static void glyph_warning(cairo_t *cr, double cx, double cy)` |
| `icon_arrow` | function | `gui/bui_chrome.c:76` | `static void icon_arrow(cairo_t *cr, double cx, double cy, int dir)` |
| `icon_chevron` | function | `gui/bui_chrome.c:647` | `static void icon_chevron(cairo_t *cr, double cx, double cy, int dir)` |
| `icon_cross` | function | `gui/bui_chrome.c:107` | `static void icon_cross(cairo_t *cr, double cx, double cy, double h)` |
| `icon_menu` | function | `gui/bui_chrome.c:99` | `static void icon_menu(cairo_t *cr, double cx, double cy)` |
| `icon_plus` | function | `gui/bui_chrome.c:115` | `static void icon_plus(cairo_t *cr, double cx, double cy, double h)` |
| `icon_reload` | function | `gui/bui_chrome.c:87` | `static void icon_reload(cairo_t *cr, double cx, double cy)` |
| `icon_stroke` | function | `gui/bui_chrome.c:69` | `static void icon_stroke(cairo_t *cr)` |
| `paint_find_field` | function | `gui/bui_chrome.c:586` | `static void paint_find_field(cairo_t *cr, const bui_find_view *v)` |
| `paint_identity` | function | `gui/bui_chrome.c:220` | `static void paint_identity(cairo_t *cr, const bui_chrome_view *v)` |
| `paint_tabstrip` | function | `gui/bui_chrome.c:480` | `static void paint_tabstrip(cairo_t *cr, const bui_chrome_view *v)` |
| `paint_toolbar` | function | `gui/bui_chrome.c:430` | `static void paint_toolbar(cairo_t *cr, const bui_chrome_view *v)` |
| `paint_url` | function | `gui/bui_chrome.c:347` | `static void paint_url(cairo_t *cr, const bui_chrome_view *v)` |
| `rcx` | function | `gui/bui_chrome.c:66` | `static double rcx(chl_rect r)` |
| `rcy` | function | `gui/bui_chrome.c:67` | `static double rcy(chl_rect r)` |
| `round_button` | function | `gui/bui_chrome.c:419` | `static void round_button(cairo_t *cr, const bui_chrome_view *v, chl_rect r, chl_part part,       ...` |
| `set_rgba` | function | `gui/bui_chrome.c:57` | `static void set_rgba(cairo_t *cr, ui_rgb c, double a)` |
| `show_n` | function | `gui/bui_chrome.c:288` | `static void show_n(cairo_t *cr, const char *s, size_t n)` |
| `spinner` | function | `gui/bui_chrome.c:123` | `static void spinner(cairo_t *cr, ui_rgb c, double cx, double cy, double phase)` |
| `tab_path` | function | `gui/bui_chrome.c:48` | `static void tab_path(cairo_t *cr, chl_rect t, double r)` |
| `tab_title` | function | `gui/bui_chrome.c:449` | `static void tab_title(cairo_t *cr, const char *s, ui_rgb c, double alpha,                       d...` |
| `text_w` | function | `gui/bui_chrome.c:278` | `static double text_w(cairo_t *cr, const char *s, size_t n)` |
| `utf8_next` | function | `gui/bui_chrome.c:271` | `static size_t utf8_next(const char *s, size_t n, size_t i)` |
| `bui_paint_mask_image` | function | `gui/bui_mask_img.c:17` | `int bui_paint_mask_image(cairo_t *c, cairo_surface_t *img, int nat_w, int nat_h,                 ...` |
| `rgb_from_packed` | function | `gui/bui_theme.c:198` | `ui_rgb rgb_from_packed(int packed)` |
| `set_rgb` | function | `gui/bui_theme.c:203` | `void set_rgb(cairo_t *cr, ui_rgb c)` |
| `ui_theme_dark` | function | `gui/bui_theme.c:91` | `ui_theme ui_theme_dark(void)` |
| `ui_theme_default` | function | `gui/bui_theme.c:15` | `ui_theme ui_theme_default(void)` |
| `ui_theme_for` | function | `gui/bui_theme.c:189` | `ui_theme ui_theme_for(int mode)` |
| `ui_theme_sepia` | function | `gui/bui_theme.c:137` | `ui_theme ui_theme_sepia(void)` |
| `_POSIX_C_SOURCE` | macro | `gui/freedom_view.c:10` | `#define _POSIX_C_SOURCE` |
| `main` | function | `gui/freedom_view.c:37` | `int main(int argc, char **argv)` |
| `UI_BTN_LEFT` | macro | `gui/ui_render.c:32` | `#define UI_BTN_LEFT` |
| `UI_BTN_W` | macro | `gui/ui_render.c:31` | `#define UI_BTN_W` |
| `UI_FONT_SIZE` | macro | `gui/ui_render.c:28` | `#define UI_FONT_SIZE` |
| `UI_MARGIN` | macro | `gui/ui_render.c:29` | `#define UI_MARGIN` |
| `UI_TITLEBAR_H` | macro | `gui/ui_render.c:30` | `#define UI_TITLEBAR_H` |
| `_GNU_SOURCE` | macro | `gui/ui_render.c:10` | `#define _GNU_SOURCE` |
| `buffer_release` | function | `gui/ui_render.c:115` | `static void buffer_release(void *data, struct wl_buffer *wl_buffer)` |
| `button_rects` | function | `gui/ui_render.c:107` | `static void button_rects(const ui_window *w, double *min_x, double *max_x, double *close_x)` |
| `deco_configure` | function | `gui/ui_render.c:294` | `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)` |
| `destroy_buffer` | function | `gui/ui_render.c:122` | `static void destroy_buffer(ui_window *w)` |
| `ensure_buffer` | function | `gui/ui_render.c:128` | `static int ensure_buffer(ui_window *w)` |
| `paint` | function | `gui/ui_render.c:159` | `static void paint(ui_window *w)` |
| `ptr_axis` | function | `gui/ui_render.c:344` | `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,                      uint32...` |
| `ptr_button` | function | `gui/ui_render.c:322` | `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,               ...` |
| `ptr_enter` | function | `gui/ui_render.c:305` | `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,                       struct wl_...` |
| `ptr_leave` | function | `gui/ui_render.c:312` | `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)` |
| `ptr_motion` | function | `gui/ui_render.c:315` | `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)` |
| `redraw` | function | `gui/ui_render.c:245` | `static void redraw(ui_window *w)` |
| `registry_global` | function | `gui/ui_render.c:383` | `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,                  ...` |
| `registry_remove` | function | `gui/ui_render.c:401` | `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)` |
| `sanitize_utf8_inplace` | function | `gui/ui_render.c:39` | `static void sanitize_utf8_inplace(char *s)` |
| `seat_caps` | function | `gui/ui_render.c:367` | `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)` |
| `seat_name` | function | `gui/ui_render.c:376` | `static void seat_name(void *d, struct wl_seat *s, const char *name)` |
| `toplevel_close` | function | `gui/ui_render.c:283` | `static void toplevel_close(void *data, struct xdg_toplevel *t)` |
| `toplevel_configure` | function | `gui/ui_render.c:274` | `static void toplevel_configure(void *data, struct xdg_toplevel *t,                               ...` |
| `ui_run_text_view` | function | `gui/ui_render.c:410` | `ui_status ui_run_text_view(const char *title, const char *text, size_t text_len)` |
| `ui_window` | struct | `gui/ui_render.c:67` | `` |
| `wm_base_ping` | function | `gui/ui_render.c:260` | `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)` |
| `xdg_surface_configure` | function | `gui/ui_render.c:266` | `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)` |
| `FP_ACCEPT_HEADER_NAV` | macro | `include/anti_fp.h:40` | `#define FP_ACCEPT_HEADER_NAV` |
| `FP_ACCEPT_LANGUAGE` | macro | `include/anti_fp.h:33` | `#define FP_ACCEPT_LANGUAGE` |
| `FP_ACCEPT_LANGUAGE_HEADER` | macro | `include/anti_fp.h:34` | `#define FP_ACCEPT_LANGUAGE_HEADER` |
| `FP_SEC_FETCH_DEST_NAV` | macro | `include/anti_fp.h:45` | `#define FP_SEC_FETCH_DEST_NAV` |
| `FP_SEC_FETCH_MODE_NAV` | macro | `include/anti_fp.h:46` | `#define FP_SEC_FETCH_MODE_NAV` |
| `FP_SEC_FETCH_SITE_NONE` | macro | `include/anti_fp.h:47` | `#define FP_SEC_FETCH_SITE_NONE` |
| `FP_SEC_FETCH_USER_ON` | macro | `include/anti_fp.h:48` | `#define FP_SEC_FETCH_USER_ON` |
| `FP_TIMER_RESOLUTION_MS` | macro | `include/anti_fp.h:22` | `#define FP_TIMER_RESOLUTION_MS` |
| `FP_USER_AGENT` | macro | `include/anti_fp.h:31` | `#define FP_USER_AGENT` |
| `FREEDOM_ANTI_FP_H` | macro | `include/anti_fp.h:2` | `#define FREEDOM_ANTI_FP_H` |
| `domain` | function | `include/anti_fp.h:91` | `* registrable domain (eTLD+1). Same (session_key, domain) => same key (poisoning * is stable within a site);` |
| `fp_accept_language` | function | `include/anti_fp.h:58` | `const char *fp_accept_language(void);` |
| `fp_accept_language_header` | function | `include/anti_fp.h:59` | `const char *fp_accept_language_header(void);` |
| `fp_app_code_name` | function | `include/anti_fp.h:71` | `const char *fp_app_code_name(void);` |
| `fp_app_name` | function | `include/anti_fp.h:73` | `const char *fp_app_name(void);` |
| `fp_bucket_screen` | function | `include/anti_fp.h:83` | `void fp_bucket_screen(int w, int h, int *out_w, int *out_h);` |
| `fp_build_id` | function | `include/anti_fp.h:76` | `const char *fp_build_id(void);` |
| `fp_coarsen_time_ms` | function | `include/anti_fp.h:53` | `uint64_t fp_coarsen_time_ms(uint64_t raw_ms);` |
| `fp_cookie_enabled` | function | `include/anti_fp.h:79` | `int fp_cookie_enabled(void);` |
| `fp_device_memory_gb` | function | `include/anti_fp.h:64` | `int fp_device_memory_gb(void);` |
| `fp_hardware_concurrency` | function | `include/anti_fp.h:63` | `int fp_hardware_concurrency(void);` |
| `fp_max_touch_points` | function | `include/anti_fp.h:77` | `int fp_max_touch_points(void);` |
| `fp_on_line` | function | `include/anti_fp.h:78` | `int fp_on_line(void);` |
| `fp_origin_key` | function | `include/anti_fp.h:98` | `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain);` |
| `fp_oscpu` | function | `include/anti_fp.h:75` | `const char *fp_oscpu(void);` |
| `fp_perturb` | function | `include/anti_fp.h:88` | `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key);` |
| `fp_platform` | function | `include/anti_fp.h:61` | `const char *fp_platform(void);` |
| `fp_product` | function | `include/anti_fp.h:72` | `const char *fp_product(void);` |
| `fp_product_sub` | function | `include/anti_fp.h:74` | `const char *fp_product_sub(void);` |
| `fp_timer_resolution_ms` | function | `include/anti_fp.h:52` | `uint64_t fp_timer_resolution_ms(void);` |
| `fp_timezone` | function | `include/anti_fp.h:60` | `const char *fp_timezone(void);` |
| `fp_user_agent` | function | `include/anti_fp.h:57` | `const char *fp_user_agent(void);` |
| `fp_vendor` | function | `include/anti_fp.h:62` | `const char *fp_vendor(void);` |
| `probability` | function | `include/anti_fp.h:93` | `* keys with overwhelming probability (canvas/audio noise is not linkable across * sites, defeating cross-origin...` |
| `properties` | function | `include/anti_fp.h:67` | `* Legacy navigator properties (Hito 30b): normalized Firefox values shared by * js_env and the network layer so JS...` |
| `ABSENT` | function | `include/block_flow.h:26` | `* as ABSENT (0) rather than propagated: a poisoned length must not spread into * the geometry of the rest of the...` |
| `FREEDOM_BLOCK_FLOW_H` | macro | `include/block_flow.h:11` | `#define FREEDOM_BLOCK_FLOW_H` |
| `bf_collapse_n` | function | `include/block_flow.h:33` | `* bf_collapse_n((double[])` |
| `bf_margins_adjoin` | function | `include/block_flow.h:43` | `int bf_margins_adjoin(double border_px, double padding_px);` |
| `BB_MAX_PIXELS` | macro | `include/box_blur.h:12` | `#define BB_MAX_PIXELS` |
| `FREEDOM_BOX_BLUR_H` | macro | `include/box_blur.h:2` | `#define FREEDOM_BOX_BLUR_H` |
| `alpha` | function | `include/box_blur.h:27` | `* no pixel has alpha (nothing to blur), 1 otherwise. Everything outside rect stays 0 after the blur, * so blurring...` |
| `bb_box_sizes` | function | `include/box_blur.h:16` | `int bb_box_sizes(double sigma, int sizes[3]);` |
| `wider` | function | `include/box_blur.h:21` | `* BB_BOX_MAX px or wider (buffer untouched). One scratch copy of w x h bytes. */ int bb_blur_a8(unsigned char *buf...` |
| `BX_TAG_NAME_MAX` | macro | `include/box_style.h:33` | `#define BX_TAG_NAME_MAX` |
| `BX_TROLE_NONE` | function | `include/box_style.h:144` | `* BX_TROLE_NONE (an unrecognised element joins no table -- fail closed). */ bx_table_role bx_table_role_of(const...` |
| `FREEDOM_BOX_STYLE_H` | macro | `include/box_style.h:2` | `#define FREEDOM_BOX_STYLE_H` |
| `block` | function | `include/box_style.h:226` | `* indefinite containing block (cb_h < 0) the value behaves as auto: -1. * Without a percentage it is px_val...` |
| `box` | function | `include/box_style.h:115` | `* in_list nonzero when the block sits inside a list item: it then takes * the <li> box (zero margin), keeping items...` |
| `bx_background_layer` | function | `include/box_style.h:331` | `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h, double *out_x, double *out_y);` |
| `bx_bg_layer` | struct | `include/box_style.h:321` | `` |
| `bx_border_box_h` | function | `include/box_style.h:220` | `double bx_border_box_h(double declared_h, int border_box, double pad_t, double pad_b, double bord_t, double bord_b);` |
| `bx_border_span` | function | `include/box_style.h:286` | `double bx_border_span(double width_cap, int border_box, double pad_l, double pad_r, double bord_l, double bord_r);` |
| `bx_box` | struct | `include/box_style.h:50` | `` |
| `bx_content_cap` | function | `include/box_style.h:275` | `double bx_content_cap(double width_cap, int border_box, double pad_l, double pad_r, double bord_l, double bord_r);` |
| `bx_definite_content_h` | function | `include/box_style.h:241` | `double bx_definite_content_h(double h, double min_h, double max_h, int border_box, double v_edges);` |
| `bx_display` | enum | `include/box_style.h:35` | `` |
| `bx_display_name` | function | `include/box_style.h:156` | `const char *bx_display_name(bx_display d);` |
| `bx_edges` | struct | `include/box_style.h:46` | `` |
| `bx_flex_max_clamp` | function | `include/box_style.h:292` | `double bx_flex_max_clamp(double outer_basis, double mw_cap, int border_box, double pad_bord_h, double margin_h);` |
| `bx_flex_min_clamp` | function | `include/box_style.h:298` | `double bx_flex_min_clamp(double outer_basis, double min_w, int border_box, double pad_bord_h, double margin_h);` |
| `bx_hplace` | struct | `include/box_style.h:63` | `` |
| `bx_line_height_px` | function | `include/box_style.h:239` | `double bx_line_height_px(int line_scale, double font_px);` |
| `bx_lp_px` | function | `include/box_style.h:267` | `double bx_lp_px(int px_val, int pct_pm, double basis);` |
| `bx_replaced_box` | function | `include/box_style.h:206` | `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den, double avail_w, double *out_w, double *out_h);` |
| `bx_status` | enum | `include/box_style.h:56` | `` |
| `bx_table_role` | enum | `include/box_style.h:127` | `` |
| `bx_ua_tag` | enum | `include/box_style.h:84` | `` |
| `bx_width_cap` | function | `include/box_style.h:182` | `double bx_width_cap(int w_px, int w_pct, double avail_w);` |
| `bx_width_cap2` | function | `include/box_style.h:187` | `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w);` |
| `display` | type_alias | `include/box_style.h:49` | `typedef struct bx_box { bx_display display;` |
| `left` | type_alias | `include/box_style.h:46` | `typedef struct bx_edges { double top, right, bottom, left;` |
| `nat_h` | type_alias | `include/box_style.h:321` | `typedef struct bx_bg_layer { double nat_w, nat_h;` |
| `page` | function | `include/box_style.h:245` | `* instead of letting it extend the page (CSS 2.1 section 10.7 + 11.1.1). That * is the case unless BOTH overflow...` |
| `x_off` | type_alias | `include/box_style.h:63` | `typedef struct bx_hplace { double x_off;` |
| `BT_ALIGN_CENTER` | macro | `include/box_tree.h:59` | `#define BT_ALIGN_CENTER` |
| `BT_ALIGN_END` | macro | `include/box_tree.h:60` | `#define BT_ALIGN_END` |
| `BT_ALIGN_START` | macro | `include/box_tree.h:58` | `#define BT_ALIGN_START` |
| `BT_ALIGN_STRETCH` | macro | `include/box_tree.h:61` | `#define BT_ALIGN_STRETCH` |
| `BT_MAUTO_LEFT` | macro | `include/box_tree.h:64` | `#define BT_MAUTO_LEFT` |
| `BT_MAUTO_RIGHT` | macro | `include/box_tree.h:65` | `#define BT_MAUTO_RIGHT` |
| `BT_MAX_CHILDREN` | macro | `include/box_tree.h:36` | `#define BT_MAX_CHILDREN` |
| `BT_MAX_DEPTH` | macro | `include/box_tree.h:35` | `#define BT_MAX_DEPTH` |
| `BT_MAX_POSITIONED` | macro | `include/box_tree.h:42` | `#define BT_MAX_POSITIONED` |
| `BT_POS_ABSOLUTE` | macro | `include/box_tree.h:49` | `#define BT_POS_ABSOLUTE` |
| `BT_POS_FIXED` | macro | `include/box_tree.h:50` | `#define BT_POS_FIXED` |
| `BT_POS_RELATIVE` | macro | `include/box_tree.h:48` | `#define BT_POS_RELATIVE` |
| `BT_POS_STATIC` | macro | `include/box_tree.h:47` | `#define BT_POS_STATIC` |
| `BT_POS_STICKY` | macro | `include/box_tree.h:51` | `#define BT_POS_STICKY` |
| `FREEDOM_BOX_TREE_H` | macro | `include/box_tree.h:2` | `#define FREEDOM_BOX_TREE_H` |
| `bottom` | function | `include/box_tree.h:208` | `* bottom with auto top still anchors bottom (R8). * `placed` (may be NULL) marks which boxes have an in-flow rect in...` |
| `box_index` | type_alias | `include/box_tree.h:146` | `typedef struct bt_positioned { size_t box_index;` |
| `bt_box_hidden` | function | `include/box_tree.h:233` | `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid);` |
| `bt_containing_block` | function | `include/box_tree.h:268` | `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i, const double *box_x, const double *box_y...` |
| `bt_defer_roots` | function | `include/box_tree.h:291` | `size_t bt_defer_roots(const pv_box_def *boxes, size_t nbox, const bt_positioned *pos, size_t npos, const char...` |
| `bt_in_subtree` | function | `include/box_tree.h:239` | `int bt_in_subtree(const pv_box_def *boxes, size_t nbox, size_t root, size_t bid);` |
| `bt_node` | struct | `include/box_tree.h:67` | `` |
| `bt_oof_anchor` | function | `include/box_tree.h:253` | `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid);` |
| `bt_oof_root` | function | `include/box_tree.h:254` | `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid);` |
| `bt_positioned` | struct | `include/box_tree.h:146` | `` |
| `bt_status` | enum | `include/box_tree.h:153` | `` |
| `closed` | function | `include/box_tree.h:34` | `* fails closed (BT_ERR_RANGE) instead of overflowing the stack. */ #define BT_MAX_DEPTH 64u #define BT_MAX_CHILDREN...` |
| `display` | type_alias | `include/box_tree.h:66` | `typedef struct bt_node { bx_display display;` |
| `flow` | function | `include/box_tree.h:201` | `* position is where the box would have started in flow (CSS 2.2 §10.3.7/§10.6.4);` |
| `insets` | function | `include/box_tree.h:258` | `* minus the two insets (px half + per-mille half of cb), an auto/unset inset * counting 0, never below 0. *both (may...` |
| `line` | function | `include/box_tree.h:115` | `* its line (already resolved from align-self / the * container's align-items by the caller). */ /* this node as a...` |
| `node` | function | `include/box_tree.h:162` | `* node (x/y parent-relative, w/h border-box). display:none nodes get a zero rect and * take no space. The caller...` |
| `one` | function | `include/box_tree.h:99` | `* of forcing them all onto one (flex-wrap);` |
| `placed` | function | `include/box_tree.h:215` | `* box counts as placed (legacy behaviour). * bt_resolve_positioning delegates with NULL arrays (legacy behaviour)....` |
| `BROWSER_CLOSED_MAX` | macro | `include/browser.h:176` | `#define BROWSER_CLOSED_MAX` |
| `BROWSER_STATUS_DURATION_MS` | macro | `include/browser.h:25` | `#define BROWSER_STATUS_DURATION_MS` |
| `BROWSER_STATUS_MAX` | macro | `include/browser.h:24` | `#define BROWSER_STATUS_MAX` |
| `BROWSER_URL_MAX` | macro | `include/browser.h:21` | `#define BROWSER_URL_MAX` |
| `FREEDOM_BROWSER_H` | macro | `include/browser.h:2` | `#define FREEDOM_BROWSER_H` |
| `browser_abort_pending` | function | `include/browser.h:106` | `int browser_abort_pending(browser_state *bs);` |
| `browser_can_back` | function | `include/browser.h:117` | `int browser_can_back(const browser_state *bs);` |
| `browser_can_forward` | function | `include/browser.h:118` | `int browser_can_forward(const browser_state *bs);` |
| `browser_closed` | struct | `include/browser.h:177` | `` |
| `browser_closed_pop` | function | `include/browser.h:188` | `int browser_closed_pop(browser_closed *c, char *out, size_t cap);` |
| `browser_commit_pending` | function | `include/browser.h:105` | `void browser_commit_pending(browser_state *bs);` |
| `browser_current_url` | function | `include/browser.h:119` | `const char *browser_current_url(const browser_state *bs);` |
| `browser_doc_index` | function | `include/browser.h:114` | `int browser_doc_index(const browser_state *bs);` |
| `browser_entry_doc` | function | `include/browser.h:110` | `int browser_entry_doc(const browser_state *bs, size_t pos);` |
| `browser_free` | function | `include/browser.h:78` | `void browser_free(browser_state *bs);` |
| `browser_has_pending` | function | `include/browser.h:107` | `int browser_has_pending(const browser_state *bs);` |
| `browser_is_exception` | function | `include/browser.h:122` | `int browser_is_exception(const browser_state *bs, const char *host);` |
| `browser_set_page` | function | `include/browser.h:83` | `* browser_set_page() with the result. */ browser_status browser_navigate(browser_state *bs, const char *url);` |
| `browser_state` | struct | `include/browser.h:27` | `` |
| `browser_status` | enum | `include/browser.h:63` | `` |
| `browser_status_text` | function | `include/browser.h:173` | `const char *browser_status_text(const browser_state *bs, uint64_t now_ms);` |
| `browser_url_bar_delete_selection` | function | `include/browser.h:158` | `int browser_url_bar_delete_selection(browser_state *bs);` |
| `browser_url_bar_selection` | function | `include/browser.h:154` | `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len);` |
| `copied` | function | `include/browser.h:166` | `* copied (truncated to fit) and shown until now_ms reaches the expiry * (now_ms + BROWSER_STATUS_DURATION_MS). A...` |
| `one` | function | `include/browser.h:102` | `* A navigate while pending first aborts the pending one (the new one replaces it);` |
| `state` | function | `include/browser.h:74` | `* state (frees old history and page buffers). */ browser_status browser_init(browser_state *bs);` |
| `FREEDOM_CACHED_FETCH_H` | macro | `include/cached_fetch.h:2` | `#define FREEDOM_CACHED_FETCH_H` |
| `cf_attach_redirect_memory` | function | `include/cached_fetch.h:38` | `void cf_attach_redirect_memory(hc_store *store);` |
| `cf_set_store` | function | `include/cached_fetch.h:30` | `void cf_set_store(hc_store *store);` |
| `cf_store` | function | `include/cached_fetch.h:31` | `hc_store *cf_store(void);` |
| `CHL_BTN` | macro | `include/chrome_layout.h:27` | `#define CHL_BTN` |
| `CHL_BTN_GAP` | macro | `include/chrome_layout.h:28` | `#define CHL_BTN_GAP` |
| `CHL_DRAG_MIN` | macro | `include/chrome_layout.h:26` | `#define CHL_DRAG_MIN` |
| `CHL_FIND_BTN` | macro | `include/chrome_layout.h:89` | `#define CHL_FIND_BTN` |
| `CHL_FIND_COUNT_W` | macro | `include/chrome_layout.h:90` | `#define CHL_FIND_COUNT_W` |
| `CHL_FIND_FIELD_H` | macro | `include/chrome_layout.h:88` | `#define CHL_FIND_FIELD_H` |
| `CHL_FIND_FIELD_W` | macro | `include/chrome_layout.h:87` | `#define CHL_FIND_FIELD_W` |
| `CHL_FIND_H` | macro | `include/chrome_layout.h:86` | `#define CHL_FIND_H` |
| `CHL_ID_W` | macro | `include/chrome_layout.h:30` | `#define CHL_ID_W` |
| `CHL_NEWTAB_W` | macro | `include/chrome_layout.h:24` | `#define CHL_NEWTAB_W` |
| `CHL_PAD` | macro | `include/chrome_layout.h:17` | `#define CHL_PAD` |
| `CHL_TABBAR_H` | macro | `include/chrome_layout.h:15` | `#define CHL_TABBAR_H` |
| `CHL_TAB_CLOSE` | macro | `include/chrome_layout.h:22` | `#define CHL_TAB_CLOSE` |
| `CHL_TAB_CLOSE_MIN_W` | macro | `include/chrome_layout.h:23` | `#define CHL_TAB_CLOSE_MIN_W` |
| `CHL_TAB_GAP` | macro | `include/chrome_layout.h:21` | `#define CHL_TAB_GAP` |
| `CHL_TAB_MAX_W` | macro | `include/chrome_layout.h:20` | `#define CHL_TAB_MAX_W` |
| `CHL_TAB_MIN_W` | macro | `include/chrome_layout.h:19` | `#define CHL_TAB_MIN_W` |
| `CHL_TAB_TOP_GAP` | macro | `include/chrome_layout.h:18` | `#define CHL_TAB_TOP_GAP` |
| `CHL_TOOLBAR_H` | macro | `include/chrome_layout.h:16` | `#define CHL_TOOLBAR_H` |
| `CHL_URL_H` | macro | `include/chrome_layout.h:29` | `#define CHL_URL_H` |
| `CHL_WIN_BTN_W` | macro | `include/chrome_layout.h:25` | `#define CHL_WIN_BTN_W` |
| `FREEDOM_CHROME_LAYOUT_H` | macro | `include/chrome_layout.h:2` | `#define FREEDOM_CHROME_LAYOUT_H` |
| `chl_find_part` | enum | `include/chrome_layout.h:92` | `` |
| `chl_findbar` | struct | `include/chrome_layout.h:101` | `` |
| `chl_identity` | enum | `include/chrome_layout.h:114` | `` |
| `chl_identity_label` | function | `include/chrome_layout.h:133` | `const char *chl_identity_label(chl_identity id);` |
| `chl_layout` | struct | `include/chrome_layout.h:54` | `` |
| `chl_part` | enum | `include/chrome_layout.h:36` | `` |
| `chl_rect` | struct | `include/chrome_layout.h:34` | `` |
| `chl_rect_has` | function | `include/chrome_layout.h:78` | `int chl_rect_has(chl_rect r, double x, double y);` |
| `chl_status` | enum | `include/chrome_layout.h:32` | `` |
| `chl_tab_close_rect` | function | `include/chrome_layout.h:75` | `int chl_tab_close_rect(const chl_layout *l, int i, chl_rect *r);` |
| `chl_tab_rect` | function | `include/chrome_layout.h:74` | `int chl_tab_rect(const chl_layout *l, int i, chl_rect *r);` |
| `close` | type_alias | `include/chrome_layout.h:100` | `typedef struct chl_findbar { chl_rect bar, field, prev, next, count, close;` |
| `h` | type_alias | `include/chrome_layout.h:33` | `typedef struct chl_rect { double x, y, w, h;` |
| `width` | type_alias | `include/chrome_layout.h:53` | `typedef struct chl_layout { double width;` |

Next: [SYMBOLS_p3.md](SYMBOLS_p3.md)
