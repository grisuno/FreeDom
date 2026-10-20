# Symbols (page 2 of 14)
Previous: [SYMBOLS.md](SYMBOLS.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `rc_box` | struct | `gui/browser_ui.c:3236` | `` |
| `rc_box_context` | function | `gui/browser_ui.c:7232` | `static void rc_box_context(const rc_state *s, double content_w,                            double...` |
| `rc_box_copy_decoration` | function | `gui/browser_ui.c:5135` | `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)` |
| `rc_defer` | struct | `gui/browser_ui.c:8064` | `` |
| `rc_defer_col` | struct | `gui/browser_ui.c:8057` | `` |
| `rc_ext` | struct | `gui/browser_ui.c:4085` | `` |
| `rc_float_bottom` | function | `gui/browser_ui.c:3538` | `static double rc_float_bottom(const rc_state *s)` |
| `rc_float_clear` | function | `gui/browser_ui.c:3547` | `static void rc_float_clear(rc_state *s)` |
| `rc_float_fit_line` | function | `gui/browser_ui.c:3606` | `static void rc_float_fit_line(rc_state *s, double line_h)` |
| `rc_float_refresh` | function | `gui/browser_ui.c:3560` | `static void rc_float_refresh(rc_state *s, double line_h)` |
| `rc_frag` | struct | `gui/browser_ui.c:3148` | `` |
| `rc_free` | function | `gui/browser_ui.c:3633` | `static void rc_free(rc_layout *L)` |
| `rc_ibox` | struct | `gui/browser_ui.c:3406` | `` |
| `rc_layout` | struct | `gui/browser_ui.c:3297` | `` |
| `rc_oof_sub` | struct | `gui/browser_ui.c:3295` | `` |
| `rc_oof_sub` | struct | `gui/browser_ui.c:3343` | `` |
| `rc_open_box` | struct | `gui/browser_ui.c:3353` | `` |
| `rc_row` | struct | `gui/browser_ui.c:3213` | `` |
| `rc_rowkind` | enum | `gui/browser_ui.c:3211` | `` |
| `rc_state` | struct | `gui/browser_ui.c:3442` | `` |
| `rd_build` | function | `gui/browser_ui.c:10418` | `* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr...` |
| `read_file` | function | `gui/browser_ui.c:663` | `static char *read_file(const char *path, size_t *out_len)` |
| `rebuild_inputs` | function | `gui/browser_ui.c:1274` | `static void rebuild_inputs(browser_window *w)` |
| `reconcile_boxes` | function | `gui/browser_ui.c:7851` | `static void reconcile_boxes(cairo_t *cr, const browser_window *w,                             rc_...` |
| `reconcile_boxes_below` | function | `gui/browser_ui.c:7735` | `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,                          ...` |
| `rect` | function | `gui/browser_ui.c:11396` | `* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops...` |
| `redraw` | function | `gui/browser_ui.c:16008` | `static void redraw(browser_window *w)` |
| `redraws` | function | `gui/browser_ui.c:18168` | `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A...` |
| `reference` | function | `gui/browser_ui.c:14797` | `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:  * hostile content...` |
| `registry_global` | function | `gui/browser_ui.c:18040` | `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,                  ...` |
| `registry_remove` | function | `gui/browser_ui.c:18060` | `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)` |
| `remember_visit` | function | `gui/browser_ui.c:922` | `static void remember_visit(browser_window *w, const char *url)` |
| `render_current` | function | `gui/browser_ui.c:2495` | `static void render_current(browser_window *w)` |
| `render_current_ex` | function | `gui/browser_ui.c:2317` | `static void render_current_ex(browser_window *w, int allow_js_nav)` |
| `render_doc_images` | function | `gui/browser_ui.c:14406` | `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,               ...` |
| `repl_edges` | struct | `gui/browser_ui.c:1116` | `` |
| `repl_edges_x` | function | `gui/browser_ui.c:1147` | `static double repl_edges_x(const repl_edges *e)` |
| `repl_edges_y` | function | `gui/browser_ui.c:1151` | `static double repl_edges_y(const repl_edges *e)` |
| `replaced_current_color` | function | `gui/browser_ui.c:11978` | `static int replaced_current_color(const browser_window *w, const rd_block *blk)` |
| `replaced_edges` | function | `gui/browser_ui.c:1123` | `static repl_edges replaced_edges(const rd_doc *doc, const rd_block *b, double cb_w)` |
| `replaced_inline_size` | function | `gui/browser_ui.c:4556` | `static int replaced_inline_size(cairo_t *cr, const browser_window *w, const ui_theme *th,        ...` |
| `replaced_is_inline_level` | function | `gui/browser_ui.c:4588` | `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)` |
| `resizes` | function | `gui/browser_ui.c:16057` | `* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);` |
| `resolve` | function | `gui/browser_ui.c:2664` | `* origin so its relative references and local images resolve (confined to the * document's directory) -- a local...` |
| `resolve_box_cursor` | function | `gui/browser_ui.c:14621` | `static int resolve_box_cursor(const rd_doc *doc, int block_id)` |
| `root_cont_in` | function | `gui/browser_ui.c:5867` | `static int root_cont_in(const rd_doc *doc, int cid, int float_box)` |
| `root_cont_of` | function | `gui/browser_ui.c:5839` | `static int root_cont_of(const rd_doc *doc, int cid)` |
| `row` | function | `gui/browser_ui.c:5386` | `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */ static d...` |
| `row_align_offset` | function | `gui/browser_ui.c:11242` | `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)` |
| `row_line_slack` | function | `gui/browser_ui.c:11230` | `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)` |
| `row_owner_block_id` | function | `gui/browser_ui.c:11953` | `static int row_owner_block_id(const rc_layout *L, const rc_row *r);` |
| `rows` | function | `gui/browser_ui.c:12319` | `* RC_IMAGE rows (see its declaration);` |
| `rule` | function | `gui/browser_ui.c:7995` | `* wrapper keeps the old rule (opened with the float's own column). */ const pv_box_def *wd = rd_box_at(doc...` |
| `run` | function | `gui/browser_ui.c:3968` | `* continuation run (block_id < 0 with no block break) deliberately skips reconcile  * to stay on ...` |
| `run_is_content` | function | `gui/browser_ui.c:5012` | `static int run_is_content(const rd_block *bk)` |
| `run_width_cap` | function | `gui/browser_ui.c:5583` | `static double run_width_cap(const rd_block *b, double avail_w)` |
| `save_current_page` | function | `gui/browser_ui.c:15169` | `static void save_current_page(browser_window *w)` |
| `save_download` | function | `gui/browser_ui.c:15136` | `static void save_download(browser_window *w, const char *url, const char *bytes,                 ...` |
| `saving` | function | `gui/browser_ui.c:18089` | `* disables saving (never clobber);` |
| `schedule_js_tick` | function | `gui/browser_ui.c:2307` | `static void schedule_js_tick(browser_window *w, int next_ms)` |
| `screen_flow_ctx` | struct | `gui/browser_ui.c:13725` | `` |
| `scroll_line_px` | function | `gui/browser_ui.c:17097` | `static double scroll_line_px(const browser_window *w)` |
| `scrollbar_drag_to` | function | `gui/browser_ui.c:2996` | `static void scrollbar_drag_to(browser_window *w)` |
| `scrollbar_metrics` | function | `gui/browser_ui.c:2968` | `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,          ...` |
| `seat_caps` | function | `gui/browser_ui.c:18022` | `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)` |
| `seat_name` | function | `gui/browser_ui.c:18033` | `static void seat_name(void *d, struct wl_seat *s, const char *name)` |
| `secure_fetch` | function | `gui/browser_ui.c:1982` | `* through secure_fetch (Zero Trust);` |
| `seed_local_storage` | function | `gui/browser_ui.c:2242` | `static void seed_local_storage(browser_window *w, tab *t, int trusted)` |
| `seed_session_cookies` | function | `gui/browser_ui.c:2218` | `static void seed_session_cookies(tab *t, int trusted, const char *url)` |
| `select_box_width` | function | `gui/browser_ui.c:9984` | `static double select_box_width(double content_w)` |
| `set_cache` | function | `gui/browser_ui.c:1317` | `static void set_cache(browser_window *w, char *html, size_t len, const char *top)` |
| `set_cursor` | function | `gui/browser_ui.c:16092` | `static void set_cursor(browser_window *w, int cur_kind)` |
| `set_page_url` | function | `gui/browser_ui.c:14816` | `static void set_page_url(browser_window *w, const char *url)` |
| `set_rgb` | function | `gui/browser_ui.c:11817` | `set_rgb(cr, (ui_rgb)` |
| `set_rgb_alpha` | function | `gui/browser_ui.c:3743` | `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)` |
| `sf_ws_url_check` | function | `gui/browser_ui.c:14849` | `&& sf_ws_url_check(op->data) == SF_OK && rp_host_of(op->data, host, sizeof host) == 0 && hb_check(w->hosts, host) !=...` |
| `show_busy` | function | `gui/browser_ui.c:2502` | `static void show_busy(browser_window *w)` |
| `show_fetch_error` | function | `gui/browser_ui.c:2511` | `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,                   ...` |
| `sites` | function | `gui/browser_ui.c:3727` | `* sites (wfh 0, local 0) get the bucket face, which is the toy face's twin. */     if (wfh != 0u ...` |
| `slot` | function | `gui/browser_ui.c:6207` | `* layout slot (item 0 → rightmost, last item → leftmost). */     if (use_flex && cdv.direction ==...` |
| `smaller` | function | `gui/browser_ui.c:3260` | `* size when the content is smaller (height) or wider (min-width);` |
| `spaced` | function | `gui/browser_ui.c:11475` | `* or evenly spaced (bui_grad_color_at). */ static void bui_paint_conic(cairo_t *cr, double x, dou...` |
| `standalone` | function | `gui/browser_ui.c:9353` | `* must not be treated as standalone (which would flush that line and give * the element a row of its own -- R7). */...` |
| `strcmp` | function | `gui/browser_ui.c:2630` | `&& strcmp(auth_host_buf, w->auth_host) != 0)` |
| `stream_progress_cb` | function | `gui/browser_ui.c:1858` | `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)` |
| `string` | function | `gui/browser_ui.c:2130` | `* or an empty string (unset, blocked, or off by caps.images), so there is no * decision to re-check, unlike...` |
| `struct` | function | `gui/browser_ui.c:6353` | `* struct (0 = auto);` |
| `styled_advance` | function | `gui/browser_ui.c:3805` | `static double styled_advance(cairo_t *cr, const rc_frag *f)` |
| `styled_draw` | function | `gui/browser_ui.c:3827` | `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)` |
| `stylesheets` | function | `gui/browser_ui.c:2337` | `* External stylesheets (Hito 27) follow the author-styles opt-in -- or the * trusted-host doctrine (Hito 28)...` |
| `surface_from_pixels` | function | `gui/browser_ui.c:1328` | `static cairo_surface_t *surface_from_pixels(const tab_image *img)` |
| `tab_ctx` | struct | `gui/browser_ui.c:283` | `` |
| `tab_ctx_release` | function | `gui/browser_ui.c:2736` | `static void tab_ctx_release(tab_ctx *c)` |
| `tab_new` | function | `gui/browser_ui.c:2177` | `static void tab_new(browser_window *w, const char *url);` |
| `tab_restore` | function | `gui/browser_ui.c:2708` | `static void tab_restore(browser_window *w)` |
| `tab_save` | function | `gui/browser_ui.c:2691` | `static void tab_save(browser_window *w)` |
| `tab_switch` | function | `gui/browser_ui.c:2760` | `static void tab_switch(browser_window *w, int idx)` |
| `tab_title` | function | `gui/browser_ui.c:2869` | `static const char *tab_title(const browser_window *w, int i)` |
| `tabbar_top` | function | `gui/browser_ui.c:2885` | `static double tabbar_top(const browser_window *w)` |
| `table` | function | `gui/browser_ui.c:5321` | `* synthesised table (no descriptors to disagree) keeps the stamp. */         if (cd != NULL && !c...` |
| `text` | function | `gui/browser_ui.c:11400` | `* fill and gradient text (2026-07-19). */ static cairo_pattern_t *bui_linear_grad(double x, doubl...` |
| `the` | function | `gui/browser_ui.c:12974` | `* the (already filtered) group with the shadow color, blur it, and * paint it under the group at the declared offset...` |
| `them` | function | `gui/browser_ui.c:5075` | `* to them (jkanime's badge-only tiles keep their box). */ static int item_root_box_in(const rd_do...` |
| `toggle` | function | `gui/browser_ui.c:2187` | `* No network: a capability toggle (images/CSS) re-renders from cache. Does nothing * when there is no cached source...` |
| `toggle_fullscreen` | function | `gui/browser_ui.c:1025` | `static void toggle_fullscreen(browser_window *w)` |
| `toggle_reader` | function | `gui/browser_ui.c:15309` | `static void toggle_reader(browser_window *w)` |
| `toolbar_button_at` | function | `gui/browser_ui.c:3075` | `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)` |
| `toolbar_rects` | function | `gui/browser_ui.c:3060` | `static void toolbar_rects(const browser_window *w,                           double *back_x, doub...` |
| `toolbar_top` | function | `gui/browser_ui.c:2891` | `static double toolbar_top(const browser_window *w)` |
| `toplevel_close` | function | `gui/browser_ui.c:16071` | `static void toplevel_close(void *data, struct xdg_toplevel *t)` |
| `toplevel_configure` | function | `gui/browser_ui.c:16049` | `static void toplevel_configure(void *data, struct xdg_toplevel *t,                               ...` |
| `treatment` | function | `gui/browser_ui.c:7786` | `* block treatment (shrink-wrapped and placed by text-align), which is what a * standalone centred call-to-action...` |
| `ua_box_rect` | function | `gui/browser_ui.c:3118` | `static void ua_box_rect(const browser_window *w, double *x, double *y,                         do...` |
| `ui_bg_image` | struct | `gui/browser_ui.c:266` | `` |
| `ui_dump_layout` | function | `gui/browser_ui.c:14458` | `ui_status ui_dump_layout(const rd_doc *doc)` |
| `ui_hot` | enum | `gui/browser_ui.c:222` | `` |
| `ui_image` | struct | `gui/browser_ui.c:253` | `` |
| `ui_input_state` | struct | `gui/browser_ui.c:229` | `` |
| `ui_menu_action` | enum | `gui/browser_ui.c:174` | `` |
| `ui_menu_item` | struct | `gui/browser_ui.c:191` | `` |
| `ui_render_pdf_images` | function | `gui/browser_ui.c:14443` | `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,                   ...` |
| `ui_render_png` | function | `gui/browser_ui.c:14346` | `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)` |
| `ui_render_png_images` | function | `gui/browser_ui.c:14437` | `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,                   ...` |
| `ui_run_browser` | function | `gui/browser_ui.c:18070` | `ui_status ui_run_browser(const char *start_url)` |
| `uitab_close` | function | `gui/browser_ui.c:2820` | `static void uitab_close(browser_window *w, int idx)` |
| `upstream` | function | `gui/browser_ui.c:11270` | `* upstream (see spec/css.md). */ static void box_path4(cairo_t *cr, double x, double y, double w,...` |
| `utf8_clen` | function | `gui/browser_ui.c:3752` | `static size_t utf8_clen(const char *s, size_t n)` |
| `v_read` | function | `gui/browser_ui.c:10624` | `static int v_read(int fd, void *buf, size_t n)` |
| `video_feeder_thread` | function | `gui/browser_ui.c:1020` | `static void *video_feeder_thread(void *arg);` |
| `video_fetch` | function | `gui/browser_ui.c:10945` | `static sf_status video_fetch(const char *url, browser_window *w,                               sf...` |
| `video_play` | function | `gui/browser_ui.c:10962` | `static int video_play(browser_window *w, const char *m3u8_url)` |
| `video_stop` | function | `gui/browser_ui.c:10767` | `static void video_stop(browser_window *w)` |
| `video_stop` | function | `gui/browser_ui.c:11064` | `* each segment loop so a video_stop() in the main thread (which sets it to 0  * then calls pthrea...` |
| `way` | function | `gui/browser_ui.c:5431` | `* intrinsic box either way (it does not wrap below its own size). */ static int block_leaves_flow(const rd_doc *doc...` |
| `width` | function | `gui/browser_ui.c:8359` | `* box width (an inline-block icon `width:12px` inside the float) is * not the float's. */ double t =...` |
| `widths` | function | `gui/browser_ui.c:11695` | `* the outer minus the adjacent border widths (CSS Backgrounds 3 5.2). The straight      * per-sid...` |
| `window_button_rects` | function | `gui/browser_ui.c:3050` | `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...` |
| `wins` | function | `gui/browser_ui.c:7125` | `* content taller than the ratio still wins (min-height:auto). */         if (bx->aspect_num > 0 &...` |
| `wl_array_for_each` | function | `gui/browser_ui.c:16065` | `wl_array_for_each(st, states)` |
| `wm_base_ping` | function | `gui/browser_ui.c:16035` | `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)` |
| `write_doc_pdf` | function | `gui/browser_ui.c:13971` | `static long write_doc_pdf(browser_window *w, const char *path)` |
| `write_doc_png` | function | `gui/browser_ui.c:14190` | `static long write_doc_png(browser_window *w, const char *path)` |
| `write_file_atomic` | function | `gui/browser_ui.c:15114` | `static int write_file_atomic(const char *path, const void *bytes, size_t len)` |
| `ws_apply_ops` | function | `gui/browser_ui.c:14841` | `static void ws_apply_ops(browser_window *w, const tab_page *page)` |
| `x` | function | `gui/browser_ui.c:8408` | `* reported x is already the BORDER x (the §7c.2 rule);` |
| `xdg_surface_configure` | function | `gui/browser_ui.c:16041` | `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)` |
| `yet` | function | `gui/browser_ui.c:9076` | `* does not carry yet (WPT flex-abspos-staticpos-*). */ static int runs_share_float(const rd_doc *...` |
| `FREEDOM_BROWSER_UI_INTERNAL_H` | macro | `gui/browser_ui_internal.h:2` | `#define FREEDOM_BROWSER_UI_INTERNAL_H` |
| `UI_FONT_SIZE` | macro | `gui/browser_ui_internal.h:30` | `#define UI_FONT_SIZE` |
| `UI_HEADING_LEVELS` | macro | `gui/browser_ui_internal.h:32` | `#define UI_HEADING_LEVELS` |
| `UI_TEXT_MARGIN` | macro | `gui/browser_ui_internal.h:31` | `#define UI_TEXT_MARGIN` |
| `b` | type_alias | `gui/browser_ui_internal.h:40` | `typedef struct ui_rgb { double r, g, b;` |
| `body_font` | type_alias | `gui/browser_ui_internal.h:42` | `typedef struct ui_theme { double body_font;` |
| `set_rgb` | function | `gui/browser_ui_internal.h:105` | `void set_rgb(cairo_t *cr, ui_rgb c);` |
| `ui_rgb` | struct | `gui/browser_ui_internal.h:41` | `` |
| `ui_theme` | struct | `gui/browser_ui_internal.h:43` | `` |
| `ui_theme_mode` | enum | `gui/browser_ui_internal.h:92` | `` |
| `rgb_from_packed` | function | `gui/bui_theme.c:174` | `ui_rgb rgb_from_packed(int packed)` |
| `set_rgb` | function | `gui/bui_theme.c:179` | `void set_rgb(cairo_t *cr, ui_rgb c)` |
| `ui_theme_dark` | function | `gui/bui_theme.c:78` | `ui_theme ui_theme_dark(void)` |
| `ui_theme_default` | function | `gui/bui_theme.c:15` | `ui_theme ui_theme_default(void)` |
| `ui_theme_for` | function | `gui/bui_theme.c:165` | `ui_theme ui_theme_for(int mode)` |
| `ui_theme_sepia` | function | `gui/bui_theme.c:123` | `ui_theme ui_theme_sepia(void)` |
| `_POSIX_C_SOURCE` | macro | `gui/freedom_view.c:10` | `#define _POSIX_C_SOURCE` |
| `main` | function | `gui/freedom_view.c:37` | `int main(int argc, char **argv)` |
| `svp_alpha` | function | `gui/svg_paint.c:31` | `static double svp_alpha(int opacity, int paint_opacity)` |
| `svp_draw` | function | `gui/svg_paint.c:139` | `void svp_draw(cairo_t *cr, const sv_image *img,               double x, double y, double w, doubl...` |
| `svp_draw_text` | function | `gui/svg_paint.c:126` | `static void svp_draw_text(cairo_t *cr, const sv_shape *sh, int current_rgb)` |
| `svp_rect_path` | function | `gui/svg_paint.c:38` | `static void svp_rect_path(cairo_t *cr, const sv_shape *sh)` |
| `svp_shape_path` | function | `gui/svg_paint.c:73` | `static void svp_shape_path(cairo_t *cr, const sv_image *img, const sv_shape *sh)` |
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
| `BB_MAX_PIXELS` | function | `include/box_blur.h:20` | `* arguments or a mask larger than BB_MAX_PIXELS (buffer untouched). */ int bb_blur_a8(unsigned char *buf, int w, int...` |
| `FREEDOM_BOX_BLUR_H` | macro | `include/box_blur.h:2` | `#define FREEDOM_BOX_BLUR_H` |
| `bb_box_sizes` | function | `include/box_blur.h:16` | `int bb_box_sizes(double sigma, int sizes[3]);` |
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
| `bt_containing_block` | function | `include/box_tree.h:262` | `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i, const double *box_x, const double *box_y...` |
| `bt_defer_roots` | function | `include/box_tree.h:285` | `size_t bt_defer_roots(const pv_box_def *boxes, size_t nbox, const bt_positioned *pos, size_t npos, const char...` |
| `bt_node` | struct | `include/box_tree.h:67` | `` |
| `bt_oof_anchor` | function | `include/box_tree.h:247` | `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid);` |
| `bt_oof_root` | function | `include/box_tree.h:248` | `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid);` |
| `bt_positioned` | struct | `include/box_tree.h:146` | `` |
| `bt_status` | enum | `include/box_tree.h:153` | `` |
| `closed` | function | `include/box_tree.h:34` | `* fails closed (BT_ERR_RANGE) instead of overflowing the stack. */ #define BT_MAX_DEPTH 64u #define BT_MAX_CHILDREN...` |
| `display` | type_alias | `include/box_tree.h:66` | `typedef struct bt_node { bx_display display;` |
| `flow` | function | `include/box_tree.h:201` | `* position is where the box would have started in flow (CSS 2.2 §10.3.7/§10.6.4);` |
| `insets` | function | `include/box_tree.h:252` | `* minus the two insets (px half + per-mille half of cb), an auto/unset inset * counting 0, never below 0. *both (may...` |
| `line` | function | `include/box_tree.h:115` | `* its line (already resolved from align-self / the * container's align-items by the caller). */ /* this node as a...` |
| `node` | function | `include/box_tree.h:162` | `* node (x/y parent-relative, w/h border-box). display:none nodes get a zero rect and * take no space. The caller...` |
| `one` | function | `include/box_tree.h:99` | `* of forcing them all onto one (flex-wrap);` |
| `placed` | function | `include/box_tree.h:215` | `* box counts as placed (legacy behaviour). * bt_resolve_positioning delegates with NULL arrays (legacy behaviour)....` |
| `BROWSER_STATUS_DURATION_MS` | macro | `include/browser.h:25` | `#define BROWSER_STATUS_DURATION_MS` |
| `BROWSER_STATUS_MAX` | macro | `include/browser.h:24` | `#define BROWSER_STATUS_MAX` |
| `BROWSER_URL_MAX` | macro | `include/browser.h:21` | `#define BROWSER_URL_MAX` |
| `FREEDOM_BROWSER_H` | macro | `include/browser.h:2` | `#define FREEDOM_BROWSER_H` |
| `browser_can_back` | function | `include/browser.h:94` | `int browser_can_back(const browser_state *bs);` |
| `browser_can_forward` | function | `include/browser.h:95` | `int browser_can_forward(const browser_state *bs);` |
| `browser_current_url` | function | `include/browser.h:96` | `const char *browser_current_url(const browser_state *bs);` |
| `browser_doc_index` | function | `include/browser.h:91` | `int browser_doc_index(const browser_state *bs);` |
| `browser_entry_doc` | function | `include/browser.h:87` | `int browser_entry_doc(const browser_state *bs, size_t pos);` |
| `browser_free` | function | `include/browser.h:66` | `void browser_free(browser_state *bs);` |
| `browser_is_exception` | function | `include/browser.h:99` | `int browser_is_exception(const browser_state *bs, const char *host);` |
| `browser_set_page` | function | `include/browser.h:71` | `* browser_set_page() with the result. */ browser_status browser_navigate(browser_state *bs, const char *url);` |
| `browser_state` | struct | `include/browser.h:27` | `` |
| `browser_status` | enum | `include/browser.h:52` | `` |
| `browser_status_text` | function | `include/browser.h:150` | `const char *browser_status_text(const browser_state *bs, uint64_t now_ms);` |
| `browser_url_bar_delete_selection` | function | `include/browser.h:135` | `int browser_url_bar_delete_selection(browser_state *bs);` |
| `browser_url_bar_selection` | function | `include/browser.h:131` | `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len);` |
| `copied` | function | `include/browser.h:143` | `* copied (truncated to fit) and shown until now_ms reaches the expiry * (now_ms + BROWSER_STATUS_DURATION_MS). A...` |
| `state` | function | `include/browser.h:62` | `* state (frees old history and page buffers). */ browser_status browser_init(browser_state *bs);` |
| `FREEDOM_COMPOSITOR_H` | macro | `include/compositor.h:2` | `#define FREEDOM_COMPOSITOR_H` |
| `cx_forms_stacking_context` | function | `include/compositor.h:60` | `int cx_forms_stacking_context(const cx_style *s);` |
| `cx_item` | struct | `include/compositor.h:69` | `` |
| `cx_item_compare` | function | `include/compositor.h:80` | `int cx_item_compare(const cx_item *a, const cx_item *b);` |
| `cx_layer` | enum | `include/compositor.h:27` | `` |
| `cx_sort` | function | `include/compositor.h:84` | `void cx_sort(cx_item *items, size_t n);` |
| `cx_style` | struct | `include/compositor.h:46` | `` |
| `layer` | type_alias | `include/compositor.h:69` | `typedef struct cx_item { cx_layer layer;` |
| `position` | type_alias | `include/compositor.h:46` | `typedef struct cx_style { int position;` |
| `CSS_BORDER_SPACING_MAX` | macro | `include/css.h:443` | `#define CSS_BORDER_SPACING_MAX` |
| `CSS_BORDER_W_MAX` | macro | `include/css.h:442` | `#define CSS_BORDER_W_MAX` |
| `CSS_BSHADOW_LAYERS` | macro | `include/css.h:451` | `#define CSS_BSHADOW_LAYERS` |
| `CSS_COLUMN_COUNT_MAX` | macro | `include/css.h:510` | `#define CSS_COLUMN_COUNT_MAX` |
| `CSS_CONTAIN_LAYOUT` | macro | `include/css.h:352` | `#define CSS_CONTAIN_LAYOUT` |
| `CSS_CONTAIN_PAINT` | macro | `include/css.h:354` | `#define CSS_CONTAIN_PAINT` |
| `CSS_CONTAIN_SIZE` | macro | `include/css.h:351` | `#define CSS_CONTAIN_SIZE` |
| `CSS_CONTAIN_STYLE` | macro | `include/css.h:353` | `#define CSS_CONTAIN_STYLE` |
| `CSS_DECO_LINE_THROUGH` | macro | `include/css.h:106` | `#define CSS_DECO_LINE_THROUGH` |
| `CSS_DECO_OVERLINE` | macro | `include/css.h:107` | `#define CSS_DECO_OVERLINE` |
| `CSS_DECO_UNDERLINE` | macro | `include/css.h:105` | `#define CSS_DECO_UNDERLINE` |
| `CSS_DROP_PROP_MAX` | macro | `include/css.h:1043` | `#define CSS_DROP_PROP_MAX` |
| `CSS_DROP_VAL_MAX` | macro | `include/css.h:1044` | `#define CSS_DROP_VAL_MAX` |
| `CSS_EM_MILLI_MAX` | macro | `include/css.h:500` | `#define CSS_EM_MILLI_MAX` |
| `CSS_FLEX_FACTOR_MAX` | macro | `include/css.h:444` | `#define CSS_FLEX_FACTOR_MAX` |
| `CSS_FONT_LIST_MAX` | macro | `include/css.h:99` | `#define CSS_FONT_LIST_MAX` |
| `CSS_FONT_SIZE_MAX` | macro | `include/css.h:506` | `#define CSS_FONT_SIZE_MAX` |
| `CSS_GAP_MAX` | macro | `include/css.h:80` | `#define CSS_GAP_MAX` |
| `CSS_GRAD_STOPS_MAX` | macro | `include/css.h:89` | `#define CSS_GRAD_STOPS_MAX` |
| `CSS_GRID_AREAS_MAX` | macro | `include/css.h:88` | `#define CSS_GRID_AREAS_MAX` |
| `CSS_GRID_COLS_MAX` | macro | `include/css.h:81` | `#define CSS_GRID_COLS_MAX` |
| `CSS_GRID_SPAN_MAX` | macro | `include/css.h:445` | `#define CSS_GRID_SPAN_MAX` |
| `CSS_GRID_TRACKS_MAX` | macro | `include/css.h:82` | `#define CSS_GRID_TRACKS_MAX` |
| `CSS_LEN_AUTO` | macro | `include/css.h:458` | `#define CSS_LEN_AUTO` |
| `CSS_LEN_END` | macro | `include/css.h:459` | `#define CSS_LEN_END` |
| `CSS_LEN_FIT_CONTENT` | macro | `include/css.h:468` | `#define CSS_LEN_FIT_CONTENT` |
| `CSS_LEN_IS_INTRINSIC` | macro | `include/css.h:471` | `#define CSS_LEN_IS_INTRINSIC(v)` |
| `CSS_LEN_MAX` | macro | `include/css.h:456` | `#define CSS_LEN_MAX` |
| `CSS_LEN_MAX_CONTENT` | macro | `include/css.h:467` | `#define CSS_LEN_MAX_CONTENT` |
| `CSS_LEN_MIN_CONTENT` | macro | `include/css.h:466` | `#define CSS_LEN_MIN_CONTENT` |
| `CSS_LEN_UNSET` | macro | `include/css.h:457` | `#define CSS_LEN_UNSET` |
| `CSS_LINE_ABS_BASE` | macro | `include/css.h:96` | `#define CSS_LINE_ABS_BASE` |
| `CSS_LINE_ABS_MAX_PX` | macro | `include/css.h:97` | `#define CSS_LINE_ABS_MAX_PX` |
| `CSS_LINE_MAX` | macro | `include/css.h:91` | `#define CSS_LINE_MAX` |
| `CSS_LINE_MIN` | macro | `include/css.h:90` | `#define CSS_LINE_MIN` |
| `CSS_MAX_ATTR_SEL` | macro | `include/css.h:569` | `#define CSS_MAX_ATTR_SEL` |
| `CSS_MAX_COMPOUNDS` | macro | `include/css.h:565` | `#define CSS_MAX_COMPOUNDS` |
| `CSS_MAX_KF_STOPS` | macro | `include/css.h:896` | `#define CSS_MAX_KF_STOPS` |
| `CSS_MAX_PSEUDO_SEL` | macro | `include/css.h:573` | `#define CSS_MAX_PSEUDO_SEL` |
| `CSS_MEDIA_DEFAULT_HEIGHT` | macro | `include/css.h:1004` | `#define CSS_MEDIA_DEFAULT_HEIGHT` |
| `CSS_MEDIA_DEFAULT_WIDTH` | macro | `include/css.h:999` | `#define CSS_MEDIA_DEFAULT_WIDTH` |
| `CSS_NTH_MAX` | macro | `include/css.h:577` | `#define CSS_NTH_MAX` |
| `CSS_PCT_MAX` | macro | `include/css.h:494` | `#define CSS_PCT_MAX` |
| `CSS_PSEUDO_AFTER` | macro | `include/css.h:1174` | `#define CSS_PSEUDO_AFTER` |
| `CSS_PSEUDO_BEFORE` | macro | `include/css.h:1173` | `#define CSS_PSEUDO_BEFORE` |
| `CSS_PSEUDO_PLACEHOLDER` | macro | `include/css.h:1175` | `#define CSS_PSEUDO_PLACEHOLDER` |
| `CSS_SHADOW_MAX` | macro | `include/css.h:450` | `#define CSS_SHADOW_MAX` |
| `CSS_SPACING_MAX` | macro | `include/css.h:449` | `#define CSS_SPACING_MAX` |
| `CSS_SVG_PAINT_NONE` | macro | `include/css.h:98` | `#define CSS_SVG_PAINT_NONE` |
| `CSS_URL_MAX` | macro | `include/css.h:100` | `#define CSS_URL_MAX` |
| `FREEDOM_CSS_H` | macro | `include/css.h:2` | `#define FREEDOM_CSS_H` |
| `POINTER` | function | `include/css.h:220` | `* POINTER (shows the hand cursor already used for links) from every other value * (shows the default arrow);` |
| `color` | type_alias | `include/css.h:584` | `typedef struct css_style { int color;` |
| `css_align` | enum | `include/css.h:34` | `` |
| `css_align_kw` | enum | `include/css.h:179` | `` |
| `css_appearance` | enum | `include/css.h:314` | `` |
| `css_attr` | struct | `include/css.h:1092` | `` |
| `css_backface` | enum | `include/css.h:435` | `` |
| `css_bg_attachment` | enum | `include/css.h:343` | `` |
| `css_bg_clip` | enum | `include/css.h:334` | `` |
| `css_bg_origin` | enum | `include/css.h:339` | `` |
| `css_bg_repeat` | enum | `include/css.h:325` | `` |
| `css_bg_size` | enum | `include/css.h:330` | `` |
| `css_border_collapse` | enum | `include/css.h:272` | `` |
| `css_border_style` | enum | `include/css.h:160` | `` |
| `css_box_sizing` | enum | `include/css.h:153` | `` |
| `css_caption_side` | enum | `include/css.h:284` | `` |
| `css_clear` | enum | `include/css.h:198` | `` |
| `css_color_scheme` | enum | `include/css.h:364` | `` |
| `css_column_fill` | enum | `include/css.h:426` | `` |
| `css_column_span` | enum | `include/css.h:431` | `` |
| `css_content_visibility` | enum | `include/css.h:356` | `` |
| `css_cursor` | enum | `include/css.h:225` | `` |
| `css_direction` | enum | `include/css.h:266` | `` |
| `css_display` | enum | `include/css.h:42` | `` |
| `css_drop` | struct | `include/css.h:1051` | `` |
| `css_drop_cause` | enum | `include/css.h:1038` | `` |
| `css_drop_log` | struct | `include/css.h:1063` | `` |
| `css_element` | struct | `include/css.h:1102` | `` |
| `css_empty_cells` | enum | `include/css.h:278` | `` |
| `css_flex_direction` | enum | `include/css.h:167` | `` |
| `css_flex_wrap` | enum | `include/css.h:173` | `` |
| `css_float` | enum | `include/css.h:192` | `` |
| `css_font_face_at` | function | `include/css.h:1215` | `int css_font_face_at(const css_sheet *sheet, size_t i, char *family, size_t fam_cap, char *src_url, size_t url_cap);` |
| `css_font_face_count` | function | `include/css.h:1214` | `size_t css_font_face_count(const css_sheet *sheet);` |
| `css_font_family` | enum | `include/css.h:111` | `` |
| `css_font_kerning` | enum | `include/css.h:394` | `` |
| `css_font_stretch` | enum | `include/css.h:403` | `` |
| `css_font_variant` | enum | `include/css.h:296` | `` |
| `css_forced_color_adjust` | enum | `include/css.h:372` | `` |
| `css_free` | function | `include/css.h:1078` | `void css_free(css_sheet *s);` |
| `css_grid_flow` | enum | `include/css.h:186` | `` |
| `css_hyphens` | enum | `include/css.h:302` | `` |
| `css_image_rendering` | enum | `include/css.h:360` | `` |
| `css_isolation` | enum | `include/css.h:347` | `` |
| `css_justify` | enum | `include/css.h:69` | `` |
| `css_list_pos` | enum | `include/css.h:390` | `` |
| `css_list_style` | enum | `include/css.h:134` | `` |
| `css_media` | struct | `include/css.h:987` | `` |
| `css_mix_blend` | enum | `include/css.h:377` | `` |
| `css_object_fit` | enum | `include/css.h:385` | `` |
| `css_overflow` | enum | `include/css.h:215` | `` |
| `css_overscroll` | enum | `include/css.h:421` | `` |
| `css_pct_slot` | enum | `include/css.h:512` | `` |
| `css_pointer_events` | enum | `include/css.h:320` | `` |
| `css_position` | enum | `include/css.h:146` | `` |
| `css_print_color_adjust` | enum | `include/css.h:368` | `` |
| `css_resize` | enum | `include/css.h:409` | `` |
| `css_resolve_anim_keyframes` | function | `include/css.h:1223` | `void css_resolve_anim_keyframes(css_style *s, const css_sheet *sheet);` |
| `css_scroll_behavior` | enum | `include/css.h:413` | `` |
| `css_sel` | struct | `include/css.h:985` | `` |
| `css_sheet` | type_alias | `include/css.h:979` | `typedef struct css_sheet css_sheet;` |
| `css_status` | enum | `include/css.h:28` | `` |
| `css_style` | struct | `include/css.h:584` | `` |
| `css_table_layout` | enum | `include/css.h:290` | `` |
| `css_text_decoration_style` | enum | `include/css.h:259` | `` |
| `css_text_overflow` | enum | `include/css.h:238` | `` |
| `css_text_rendering` | enum | `include/css.h:398` | `` |
| `css_text_transform` | enum | `include/css.h:117` | `` |
| `css_touch_action` | enum | `include/css.h:417` | `` |
| `css_ua_heading_em` | function | `include/css.h:1199` | `double css_ua_heading_em(int level);` |
| `css_user_select` | enum | `include/css.h:308` | `` |
| `css_valign` | enum | `include/css.h:122` | `` |
| `css_visibility` | enum | `include/css.h:206` | `` |
| `css_white_space` | enum | `include/css.h:128` | `` |
| `css_word_break` | enum | `include/css.h:252` | `` |
| `cvr_table` | struct | `include/css.h:1163` | `` |
| `declared` | function | `include/css.h:861` | `* function was not declared (identity: 0 offset / 100% scale / 0deg). * Percentage translate arguments are not...` |
| `element` | function | `include/css.h:866` | `* so two different rules matching the same element (e.g. one setting * translate, a more specific one setting...` |
| `family` | function | `include/css.h:690` | `* LOCAL family (spec/text_shape.md section 7);` |
| `inherited_px` | function | `include/css.h:1187` | `* whose PARENT computes to inherited_px (<= 0 = unknown -> the CSS initial). * * Exported because the caller that...` |
| `name` | function | `include/css.h:1204` | `* name (NULL = not a heading). */ double css_computed_font_size_for_tag(const css_style *o, double inherited_px...` |
| `order` | function | `include/css.h:1081` | `* cascade order (specificity, then document order), then the element's own * inline_style (which wins)....` |
| `palette` | function | `include/css.h:1028` | `* so an inactive theme * palette (a dark palette in a light render) can never clobber the active one. *...` |
| `prefers_dark` | type_alias | `include/css.h:986` | `typedef struct css_media { int prefers_dark;` |
| `prop` | type_alias | `include/css.h:1051` | `typedef struct css_drop { char prop[CSS_DROP_PROP_MAX];` |
| `scaleY` | function | `include/css.h:857` | `* scaleY() as a PERCENT of identity (100 = scale(1), matching font_scale's * convention);` |
| `slots` | function | `include/css.h:873` | `* parse time into ALL seven slots (singular matrices fail closed);` |
| `translate` | function | `include/css.h:856` | `* translate()/translateX()/translateY();` |
| `verbatim` | function | `include/css.h:84` | `* the quoted row strings verbatim (flex_layout parses them);` |
| `CAR_INLINE_SPEC` | macro | `include/css_atrule.h:18` | `#define CAR_INLINE_SPEC` |
| `CAR_LAYER_NAME_MAX` | macro | `include/css_atrule.h:17` | `#define CAR_LAYER_NAME_MAX` |
| `CAR_MAX_DEPTH` | macro | `include/css_atrule.h:15` | `#define CAR_MAX_DEPTH` |
| `CAR_MAX_LAYERS` | macro | `include/css_atrule.h:16` | `#define CAR_MAX_LAYERS` |
| `FREEDOM_CSS_ATRULE_H` | macro | `include/css_atrule.h:2` | `#define FREEDOM_CSS_ATRULE_H` |
| `car_effective_spec` | function | `include/css_atrule.h:44` | `int car_effective_spec(int spec, int layer, int important);` |
| `car_layer_rank` | function | `include/css_atrule.h:40` | `int car_layer_rank(car_layers *L, const char *name, size_t len);` |
| `car_layers` | struct | `include/css_atrule.h:31` | `` |
| `car_ops` | struct | `include/css_atrule.h:22` | `` |
| `car_supports` | function | `include/css_atrule.h:29` | `int car_supports(const char *s, size_t a, size_t b, const car_ops *ops);` |
| `CB_AUTO_REJECT` | macro | `include/css_box.h:10` | `#define CB_AUTO_REJECT` |
| `CB_AUTO_RESET` | macro | `include/css_box.h:12` | `#define CB_AUTO_RESET` |
| `CB_AUTO_RESET_NONE` | macro | `include/css_box.h:13` | `#define CB_AUTO_RESET_NONE` |
| `CB_AUTO_VALUE` | macro | `include/css_box.h:11` | `#define CB_AUTO_VALUE` |
| `FREEDOM_CSS_BOX_H` | macro | `include/css_box.h:2` | `#define FREEDOM_CSS_BOX_H` |
| `cb_emit_len` | function | `include/css_box.h:17` | `int cb_emit_len(css_decl *dst, int cap, int slot, const char *val, int allow_auto, int allow_neg);` |
| `cb_expand_box2` | function | `include/css_box.h:21` | `int cb_expand_box2(const char *val, int slot_start, int slot_end, int allow_auto, int allow_neg, css_decl *dst, int...` |
| `cb_expand_box4` | function | `include/css_box.h:19` | `int cb_expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg, css_decl *dst, int cap);` |
| `cb_expand_grid_template_cols` | function | `include/css_box.h:38` | `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap);` |

Next: [SYMBOLS_p3.md](SYMBOLS_p3.md)
