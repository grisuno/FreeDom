# Subsystem: gui (page 2 of 3)
Previous: [KB_gui.md](KB_gui.md)

## gui/browser_ui.c (continued)
    if (sub == NULL)`
  - `paint_owned_negz` (function, line 15482) `static void paint_owned_negz(cairo_t *cr, browser_window *w, rc_layout *L, double left,
         ...`
  - `paint_nested_children` (function, line 15498) `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...`
  - `bui_pop_group_composite` (function, line 15521) `bui_pop_group_composite(cr, cdef, now_ms() - w->page_load_mono_ms, &L->boxes[j], left, origin,
  ...`
  - `geom_from_layout` (function, line 15542) `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,
                ...`
  - `publish_geometry` (function, line 15573) `static void publish_geometry(browser_window *w, const rc_layout *L, double left,
                ...`
  - `defer_root_z` (function, line 15635) `static int defer_root_z(const rd_doc *doc, size_t root)`
  - `defer_root_before` (function, line 15641) `static int defer_root_before(const rd_doc *doc, const rc_layout *L, size_t a, size_t b)`
  - `paint_positioned_layer` (function, line 15647) `static void paint_positioned_layer(cairo_t *cr, browser_window *w, const ui_theme *th,
          ...`
  - `paint_screen_inflow` (function, line 15716) `static void paint_screen_inflow(const screen_flow_ctx *c, int only_root)`
  - `bui_pop_group_composite` (function, line 15783) `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
  - `lazy_slot` (function, line 15837) `static ui_image *lazy_slot(browser_window *w, const char *href, size_t *idx)`
  - `lazy_load_one` (function, line 15848) `static void lazy_load_one(browser_window *w, ui_image *slot, const rd_block *b)`
  - `load_lazy_bg_images` (function, line 15904) `static void load_lazy_bg_images(browser_window *w, const rc_layout *L, double origin,
           ...`
  - `paint_screen_deferred` (function, line 15939) `static void paint_screen_deferred(void *ctx, int root)`
  - `gui_prof_now_ms` (function, line 15944) `static double gui_prof_now_ms(void)`
  - `gui_prof_log` (function, line 15949) `static void gui_prof_log(const char *what, double ms)`
  - `layout_key_build` (function, line 15960) `static void layout_key_build(const browser_window *w, double content_w, double content_h,
       ...`
  - `layout_diff` (function, line 16004) `static const char *layout_diff(const rc_layout *a, const rc_layout *b)`
  - `layout_for_frame` (function, line 16044) `static rc_layout *layout_for_frame(cairo_t *cr, browser_window *w, double content_w,
            ...`
  - `layout_cache_free` (function, line 16085) `static void layout_cache_free(browser_window *w)`
  - `frame_undo_restore` (function, line 16104) `static void frame_undo_restore(rc_layout *L, frame_undo *u)`
  - `paint_structured` (function, line 16115) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
  - `write_doc_pdf` (function, line 16277) `static long write_doc_pdf(browser_window *w, const char *path)`
  - `export_pdf` (function, line 16387) `static void export_pdf(browser_window *w)`
  - `ui_render_viewport_w` (function, line 16442) `int ui_render_viewport_w(void)`
  - `paint_png_inflow` (function, line 16471) `static void paint_png_inflow(const png_flow_ctx *c, int only_root)`
  - `paint_png_deferred` (function, line 16508) `static void paint_png_deferred(void *ctx, int root)`
  - `write_doc_png` (function, line 16608) `static long write_doc_png(browser_window *w, const char *path)`
  - `render_frame_surface` (function, line 16620) `static cairo_surface_t *render_frame_surface(const pv_view *view, tab *ft, const char *url,
     ...`
  - `live_frame_view` (function, line 16663) `static const pv_view *live_frame_view(const browser_window *w, const char *href, tab **ft,
      ...`
  - `fill_frame_slot` (function, line 16677) `static void fill_frame_slot(browser_window *w, const rd_block *b, ui_image *slot,
               ...`
  - `refresh_frame_images` (function, line 16726) `static void refresh_frame_images(browser_window *w)`
  - `export_png` (function, line 16744) `static void export_png(browser_window *w)`
  - `caller` (function, line 16778) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
  - `ui_render_png` (function, line 16801) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)`
  - `render_doc_images` (function, line 16861) `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...`
  - `ui_render_png_images` (function, line 16894) `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_png_frames` (function, line 16900) `ui_status ui_render_png_frames(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_pdf_images` (function, line 16906) `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_dump_layout` (function, line 16921) `ui_status ui_dump_layout(const rd_doc *doc)`
  - `link_at_point` (function, line 16993) `static const char *link_at_point(browser_window *w, double px, double py)`
  - `video_at_point` (function, line 17058) `static const char *video_at_point(browser_window *w, double px, double py,
                      ...`
  - `resolve_box_cursor` (function, line 17109) `static int resolve_box_cursor(const rd_doc *doc, int block_id)`
  - `box_pointer_events_none` (function, line 17123) `static int box_pointer_events_none(const rd_doc *doc, int block_id)`
  - `cursor_at_point` (function, line 17139) `static int cursor_at_point(browser_window *w, double px, double py)`
  - `node_at_point` (function, line 17204) `static dom_node_id node_at_point(browser_window *w, double px, double py)`
  - `Firefox` (function, line 17212) `* on its face does in Firefox (spec/page_view.md, tanda 40). */
static const rd_block *submit_pro...`
  - `frag_at_point` (function, line 17231) `static dom_node_id frag_at_point(browser_window *w, double px, double py,
                       ...`
  - `reference` (function, line 17285) `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
  - `set_page_url` (function, line 17304) `static void set_page_url(browser_window *w, const char *url)`
  - `gui_frame_top_msg` (function, line 17332) `static void gui_frame_top_msg(void *ctx, const char *data, size_t len)`
  - `frames_drain` (function, line 17345) `static void frames_drain(browser_window *w)`
  - `frames_apply` (function, line 17363) `static void frames_apply(browser_window *w, const tab_page *page)`
  - `ws_apply_ops` (function, line 17378) `static void ws_apply_ops(browser_window *w, const tab_page *page)`
  - `apply_history_ops` (function, line 17415) `static void apply_history_ops(browser_window *w, const tab_page *page)`
  - `history_step` (function, line 17427) `static void history_step(browser_window *w, int steps)`
  - `page_render_caps` (function, line 17455) `static rdp_caps page_render_caps(const browser_window *w)`
  - `wc_render_caps` (function, line 17456) `return wc_render_caps(wc_derive((wc_input)`
  - `apply_click_result` (function, line 17474) `static int apply_click_result(browser_window *w, tab_page *page)`
  - `on_tab_async` (function, line 17526) `static void on_tab_async(browser_window *w)`
  - `gui_quiesce` (function, line 17546) `static void gui_quiesce(browser_window *w)`
  - `memory` (function, line 17554) `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
  - `GET` (function, line 17674) `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
  - `ensure_download_dir` (function, line 17709) `static int ensure_download_dir(char *out, size_t outsz)`
  - `write_file_atomic` (function, line 17724) `static int write_file_atomic(const char *path, const void *bytes, size_t len)`
  - `save_download` (function, line 17746) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...`
  - `save_current_page` (function, line 17779) `static void save_current_page(browser_window *w)`
  - `deliver_fetch_result` (function, line 17789) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
  - `drain_fetch_results` (function, line 17858) `static void drain_fetch_results(browser_window *w)`
  - `toggle_reader` (function, line 18008) `static void toggle_reader(browser_window *w)`
  - `menu_item_checked` (function, line 18019) `static int menu_item_checked(const browser_window *w, size_t i)`
  - `menu_item_toggle` (function, line 18041) `static void menu_item_toggle(browser_window *w, size_t i)`
  - `draw_menu` (function, line 18155) `static void draw_menu(cairo_t *cr, browser_window *w)`
  - `draw_hover_url` (function, line 18277) `static double draw_hover_url(cairo_t *cr, browser_window *w)`
  - `draw_toast` (function, line 18309) `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)`
  - `page_identity` (function, line 18335) `static chl_identity page_identity(const browser_window *w)`
  - `site_panel_now` (function, line 18341) `static int site_panel_now(const browser_window *w, sp_panel *p, sp_geom *g)`
  - `draw_site_panel` (function, line 18361) `static void draw_site_panel(cairo_t *cr, browser_window *w)`
  - `site_panel_act` (function, line 18369) `static void site_panel_act(browser_window *w, sp_action a)`
  - `chrome_view_fill` (function, line 18376) `static void chrome_view_fill(browser_window *w, const chl_layout *l, const char **titles,
       ...`
  - `paint_chrome` (function, line 18406) `static void paint_chrome(cairo_t *cr, browser_window *w)`
  - `draw_omnibox` (function, line 18418) `static void draw_omnibox(cairo_t *cr, browser_window *w)`
  - `draw_findbar` (function, line 18453) `static void draw_findbar(cairo_t *cr, browser_window *w)`
  - `paint` (function, line 18468) `static void paint(browser_window *w)`
  - `redraw` (function, line 18573) `static void redraw(browser_window *w)`
  - `wm_base_ping` (function, line 18618) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 18624) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 18632) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `wl_array_for_each` (function, line 18648) `wl_array_for_each(st, states)`
  - `toplevel_close` (function, line 18654) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 18663) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `set_cursor` (function, line 18675) `static void set_cursor(browser_window *w, int cur_kind)`
  - `element` (function, line 18705) `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...`
  - `update_hover` (function, line 18716) `static void update_hover(browser_window *w)`
  - `fbw_split_y` (function, line 18806) `static double fbw_split_y(const freebug_window *fb)`
  - `freebug_ensure_buffer` (function, line 18815) `static int freebug_ensure_buffer(freebug_window *fb)`
  - `fbw_level_rgb` (function, line 18842) `static void fbw_level_rgb(int level, double *r, double *g, double *b)`
  - `fbw_console_lines` (function, line 18853) `static size_t fbw_console_lines(const fb_buffer *log, int filter)`
  - `fbw_cell_w` (function, line 18868) `static double fbw_cell_w(cairo_t *cr)`
  - `fbw_text_lines` (function, line 18874) `static size_t fbw_text_lines(const char *t)`
  - `fbw_arg_hint` (function, line 18881) `static const char *fbw_arg_hint(int which)`
  - `fbw_paint_tabs` (function, line 18892) `static void fbw_paint_tabs(cairo_t *cr, const freebug_window *fb)`
  - `fbw_paint_pane` (function, line 18925) `static void fbw_paint_pane(cairo_t *cr, const freebug_window *fb, double y, double split_y)`
  - `freebug_paint` (function, line 18956) `static void freebug_paint(freebug_window *fb)`
  - `freebug_redraw_fb` (function, line 19168) `static void freebug_redraw_fb(freebug_window *fb)`
  - `freebug_redraw` (function, line 19177) `static void freebug_redraw(browser_window *w)`
  - `freebug_hide` (function, line 19181) `static void freebug_hide(browser_window *w)`
  - `fbw_xdg_surface_configure` (function, line 19197) `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `fbw_toplevel_configure` (function, line 19205) `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...`
  - `fbw_toplevel_close` (function, line 19214) `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)`
  - `freebug_show` (function, line 19224) `static void freebug_show(browser_window *w)`
  - `freebug_toggle` (function, line 19254) `static void freebug_toggle(browser_window *w)`
  - `freebug_destroy` (function, line 19259) `static void freebug_destroy(browser_window *w)`
  - `freebug_owns_surface` (function, line 19268) `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)`
  - `freebug_is_open` (function, line 19272) `static int freebug_is_open(const browser_window *w)`
  - `freebug_repl_worker` (function, line 19279) `static tab *freebug_repl_worker(browser_window *w)`
  - `freebug_pane_refresh` (function, line 19321) `static void freebug_pane_refresh(browser_window *w)`
  - `freebug_set_tab` (function, line 19358) `static void freebug_set_tab(browser_window *w, int which)`
  - `freebug_panes_invalidate` (function, line 19376) `static void freebug_panes_invalidate(browser_window *w)`
  - `freebug_eval` (function, line 19383) `static void freebug_eval(browser_window *w)`
  - `freebug_set_editor` (function, line 19426) `static void freebug_set_editor(freebug_window *fb, const char *s)`
  - `freebug_complete` (function, line 19434) `static void freebug_complete(browser_window *w)`
  - `freebug_handle_key` (function, line 19464) `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...`
  - `freebug_pointer_button` (function, line 19517) `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...`
  - `freebug_pointer_motion` (function, line 19546) `static void freebug_pointer_motion(browser_window *w)`
  - `freebug_pointer_axis` (function, line 19568) `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)`
  - `ptr_enter` (function, line 19586) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
  - `ptr_leave` (function, line 19604) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
  - `ptr_motion` (function, line 19621) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
  - `stop_loading` (function, line 19650) `static int stop_loading(browser_window *w)`
  - `load_current` (function, line 19663) `static void load_current(browser_window *w)`
  - `go_omnibox` (function, line 19676) `static void go_omnibox(browser_window *w)`
  - `ptr_button` (function, line 19721) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
  - `scroll_line_px` (function, line 19982) `static double scroll_line_px(const browser_window *w)`
  - `ptr_axis` (function, line 19986) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
  - `ptr_frame` (function, line 20010) `static void ptr_frame(void *d, struct wl_pointer *p)`
  - `mime_is_text` (function, line 20026) `static int mime_is_text(const char *mime)`
  - `data_offer_source_actions` (function, line 20044) `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_offer_action` (function, line 20047) `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_device_data_offer` (function, line 20057) `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...`
  - `data_device_selection` (function, line 20069) `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...`
  - `data_device_enter` (function, line 20088) `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...`
  - `data_device_leave` (function, line 20093) `static void data_device_leave(void *d, struct wl_data_device *dev)`
  - `data_device_motion` (function, line 20094) `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...`
  - `data_device_drop` (function, line 20098) `static void data_device_drop(void *d, struct wl_data_device *dev)`
  - `data_source_cancelled` (function, line 20109) `static void data_source_cancelled(void *data, struct wl_data_source *src)`
  - `data_source_send` (function, line 20115) `static void data_source_send(void *data, struct wl_data_source *src,
                            ...`
  - `data_source_target` (function, line 20128) `static void data_source_target(void *d, struct wl_data_source *s, const char *m)`
  - `freebug_copy_console` (function, line 20140) `static void freebug_copy_console(browser_window *w)`
  - `insert_pasted_text` (function, line 20208) `static void insert_pasted_text(browser_window *w, const char *text, size_t len)`
  - `clipboard_copy` (function, line 20274) `static void clipboard_copy(browser_window *w)`
  - `keyboard_keymap` (function, line 20324) `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...`
  - `keyboard_enter` (function, line 20345) `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...`
  - `keyboard_leave` (function, line 20352) `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)`
  - `key_sym_to_js_key` (function, line 20360) `static const char *key_sym_to_js_key(xkb_keysym_t sym)`
  - `key_sym_to_keycode` (function, line 20386) `static int key_sym_to_keycode(xkb_keysym_t sym)`
  - `dispatch_js_event` (function, line 20411) `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...`
  - `fip_focus` (function, line 20468) `static void fip_focus(browser_window *w)`
  - `fip_open_bar` (function, line 20477) `static void fip_open_bar(browser_window *w)`
  - `fip_close_bar` (function, line 20488) `static void fip_close_bar(browser_window *w)`
  - `fip_step` (function, line 20499) `static void fip_step(browser_window *w, int dir)`
  - `fip_edited` (function, line 20508) `static void fip_edited(browser_window *w)`
  - `fip_type` (function, line 20514) `static void fip_type(browser_window *w, const char *s, size_t n)`
  - `fip_key` (function, line 20525) `static int fip_key(browser_window *w, xkb_keysym_t sym, const char *utf8, int n, int ctrl,
      ...`
  - `fip_click` (function, line 20558) `static int fip_click(browser_window *w, double x, double y)`
  - `fip_hot_at` (function, line 20573) `static chl_find_part fip_hot_at(const browser_window *w, double x, double y)`
  - `handle_key_press` (function, line 20583) `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...`
  - `key_is_repeatable` (function, line 20980) `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)`
  - `key_repeat_arm` (function, line 20996) `static void key_repeat_arm(browser_window *w, uint32_t key)`
  - `key_repeat_stop` (function, line 21009) `static void key_repeat_stop(browser_window *w)`
  - `key_repeat_fire` (function, line 21020) `static void key_repeat_fire(browser_window *w)`
  - `keyboard_key` (function, line 21034) `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...`
  - `keyboard_modifiers` (function, line 21074) `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...`
  - `keyboard_repeat_info` (function, line 21083) `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)`
  - `seat_caps` (function, line 21102) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
  - `seat_name` (function, line 21113) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
  - `registry_global` (function, line 21120) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
  - `registry_remove` (function, line 21140) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
  - `gui_is_idle` (function, line 21153) `static int gui_is_idle(const browser_window *w)`
  - `gui_timing_step` (function, line 21164) `static int gui_timing_step(browser_window *w, uint64_t now)`
  - `startup_abort_release` (function, line 21222) `static void startup_abort_release(browser_window *w)`
  - `ui_run_browser` (function, line 21233) `ui_status ui_run_browser(const char *start_url)`
  - `cost` (function, line 21716) `* measured cost (floor 33 ms = the existing ~30 fps ceiling):
             * cheap pages paint at...`
  - `offset` (function, line 181) `* offset (labels and the flag live in one place, no magic indices);`
  - `fields` (function, line 297) `* fields (so the 200+ render/event call sites stay unchanged);`
  - `delay` (function, line 429) `* timer delay (tab_page.next_timer_ms);`
  - `main` (function, line 594) `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never...`
  - `proxy` (function, line 1180) `* and enable each proxy ("1" => the default port);`
  - `video_feeder_thread` (function, line 1239) `static void *video_feeder_thread(void *arg);`
  - `video_pipeline_down` (function, line 1241) `static void video_pipeline_down(browser_window *w);`
  - `box_pad_px` (function, line 1344) `static double box_pad_px(int px_val, int pct_pm, double cb_w);`
  - `page_trusted` (function, line 1725) `static int page_trusted(const browser_window *w);`
  - `only` (function, line 1906) `* Trusted pages only (untrusted CSS is still applied by the worker, but its * fonts never reach the parent...`
  - `hb_is_allowlisted` (function, line 2043) `&& hb_is_allowlisted(w->hosts, ihost);`
  - `proceed` (function, line 2090) `* may proceed (cfg and pr->allowlisted are then set);`
  - `secure_fetch` (function, line 2385) `* through secure_fetch (Zero Trust);`
  - `string` (function, line 2553) `* or an empty string (unset, blocked, or off by caps.images), so there is no * decision to re-check, unlike...`
  - `do_load` (function, line 2614) `static void do_load(browser_window *w, const char *url);`
  - `tab_new` (function, line 2619) `static void tab_new(browser_window *w, const char *url);`
  - `toggle` (function, line 2633) `* No network: a capability toggle (images/CSS) re-renders from cache. Does nothing * when there is no cached source...`
  - `window` (function, line 2798) `* first paint and a hung one never holds the window (spec/subreq_async.md). */ gui_net_ctx *nctx = gui_net_ctx_new(w);`
  - `stylesheets` (function, line 2807) `* External stylesheets (Hito 27) follow the author-styles opt-in -- or the * trusted-host doctrine (Hito 28)...`
  - `body` (function, line 2840) `* every served CSS body (serial and pool paths alike). */ font_stash_reset(w);`
  - `ALIVE` (function, line 2948) `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or...`
  - `resolve` (function, line 3208) `* origin so its relative references and local images resolve (confined to the * document's directory) -- a local...`
  - `smaller` (function, line 3830) `* size when the content is smaller (height) or wider (min-width);`
  - `HarfBuzz` (function, line 4307) `* descriptor via HarfBuzz (text_shape);`
  - `run` (function, line 4573) `* continuation run (block_id < 0 with no block break) deliberately skips reconcile * to stay on the line, and that...`
  - `produced` (function, line 4877) `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target...`
  - `line` (function, line 4977) `* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the...`
  - `box_path4` (function, line 5180) `static void box_path4(cairo_t *cr, double x, double y, double w, double h, const double *rc);`
  - `block_leaves_flow` (function, line 5262) `static int block_leaves_flow(const rd_doc *doc, const rd_block *bk);`
  - `container` (function, line 6053) `* were the container (github's tab pill). */ int item = item_at_level(doc, rd_at(doc, k), cid);`
  - `way` (function, line 6153) `* intrinsic box either way (it does not wrap below its own size). */ static int block_leaves_flow(const rd_doc *doc...`
  - `empty_atom_continues_line` (function, line 6156) `static int empty_atom_continues_line(const rd_doc *doc, size_t run_i, int box_id);`
  - `width` (function, line 6253) `* the line: the layout spends its width (reconcile_boxes_below), so the * measure must too, or the label wraps...`
  - `layout` (function, line 6498) `* hypothetical size in the real layout (Flexbox 9.2.3). */ if (ibd != NULL && ibd->box_min_w > 0) base =...`
  - `close_all_boxes` (function, line 6590) `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);`
  - `deepest_open_on_path` (function, line 6618) `static int deepest_open_on_path(const rc_state *outer, const rd_doc *doc, int block_id);`
  - `TABLE` (function, line 6733) `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all...`
  - `band_shared_box` (function, line 6843) `static int band_shared_box(const rd_doc *doc, const rc_state *s, size_t start, size_t end);`
  - `axis` (function, line 7261) `* differs: items stack on the vertical main axis (fx_column_place) and align on * the horizontal cross axis...`
  - `struct` (function, line 7465) `* struct (0 = auto);`
  - `descriptor` (function, line 7474) `* placement rides the nested descriptor (spec/grid_areas.md 6). */ int nbc = child_cont_at_level(doc, bk, cid);`
  - `builds` (function, line 7718) `* wraps beside it: the same band the top level builds (spec/float.md). */ const rd_block *fk = rd_at(doc, k);`
  - `flow` (function, line 7814) `* it collapse their vertical margins with each other exactly as in * the main flow (CSS 2.1 8.3.1), and none escapes...`
  - `own` (function, line 7862) `* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and...`
  - `items` (function, line 7943) `* items (Flexbox 4.2);`
  - `multicol_fragment` (function, line 8125) `static double multicol_fragment(rc_layout *L, const rc_open_box *ob, double content_bottom);`
  - `behind` (function, line 8415) `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old...`
  - `treatment` (function, line 9009) `* block treatment (shrink-wrapped and placed by text-align), which is what a * standalone centred call-to-action...`
  - `it` (function, line 9073) `* sized atom with text reaches it when the flow leaves it (leave_inline_box). */ s->pen_x += ib->pad_l + (ib_empty ?...`
  - `context` (function, line 9252) `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document...`
  - `path` (function, line 9284) `* overflow degrades to the old inline path (fail-open: content overlaps or * stacks instead of vanishing). With no...`
  - `beside` (function, line 9483) `* margin: nothing to pull up beside (CSS 2.1 9.5.1 rule 5 -- a float's top is never * above an earlier block). They...`
  - `x` (function, line 9746) `* reported x is already the BORDER x (the §7c.2 rule);`
  - `chain` (function, line 10511) `* chain (the box that left the normal flow at this pen position);`
  - `anchor` (function, line 10626) `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is...`
  - `key` (function, line 10695) `* founders splits by key (stories, rail, footer nav each take * their column);`
  - `inline` (function, line 10697) `* lays out whole inline (fail-open: today's path). */ if (getenv("FREEDOM_DEFER_DEBUG") != NULL) fprintf(stderr...`
  - `have` (function, line 10732) `* as they always have (spec/float.md §6b.3). The line still open beside * the previous float is committed first, at...`
  - `standalone` (function, line 10753) `* must not be treated as standalone (which would flush that line and give * the element a row of its own -- R7). */...`
  - `margin` (function, line 11176) `* own left margin (the margin box starts at the anchor point), a right- * anchored one ends at it. Same for the...`
  - `one` (function, line 11351) `* the padding of the boxes between the text and this one (a padded * `<a display:flex>` entry is as wide as its...`
  - `rd_build` (function, line 11898) `* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr...`
  - `descriptors` (function, line 12165) `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection —...`
  - `again` (function, line 12246) `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one...`
  - `blocking` (function, line 12575) `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);`
  - `rect` (function, line 13099) `* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops...`
  - `layer` (function, line 13401) `* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the...`
  - `convention` (function, line 13557) `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE || style...`
  - `row_owner_block_id` (function, line 13707) `static int row_owner_block_id(const rc_layout *L, const rc_row *r);`
  - `exactly` (function, line 13753) `* the resolved size exactly (like the SVG path above): routing through * paint_image_row would re-resolve a % width...`
  - `bg` (function, line 13985) `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);`
  - `rows` (function, line 14218) `* RC_IMAGE rows (see its declaration);`
  - `made` (function, line 14789) `* its zero channels made (255,255,255,alpha 0) -- an invalid * premultiplied value Cairo composites as ADDITIVE...`
  - `the` (function, line 14893) `* the (already filtered) group with the shadow color, blur it, and * paint it under the group at the declared offset...`
  - `fill` (function, line 15077) `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in...`
  - `overflow` (function, line 15137) `* adding two of them in int was signed overflow (UB, found by UBSan). */ double ox = left + bx->x +...`
  - `compositing` (function, line 15180) `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context...`
  - `once` (function, line 15903) `* box the layout never placed loads at once (fail open);`
  - `origin` (function, line 16857) `* top_url is the page origin (https or file://);`
  - `in` (function, line 16943) `* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);`
  - `sf_ws_url_check` (function, line 17388) `&& sf_ws_url_check(op->data) == SF_OK && rp_host_of(op->data, host, sizeof host) == 0 &&...`
  - `vcl_layout` (function, line 17567) `&& vcl_layout(w->video_rect.x, w->video_rect.y, w->video_rect.w, w->video_rect.h, &g);`
  - `presentation` (function, line 18039) `* affect presentation (a repaint, which re-runs layout, suffices);`
  - `resizes` (function, line 18640) `* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);`
  - `down` (function, line 19580) `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void...`
  - `loop` (function, line 20199) `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately...`
  - `saving` (function, line 21256) `* disables saving (never clobber);`
  - `redraws` (function, line 21352) `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A...`
  - `moves` (function, line 21365) `* client that stops reading its socket while the pointer moves (spec/wl_guard.md). */ if...`
  - `_GNU_SOURCE` (macro, line 12) `#define _GNU_SOURCE`
  - `UI_TOOLBAR_H` (macro, line 104) `#define UI_TOOLBAR_H`
  - `UI_MARGIN` (macro, line 105) `#define UI_MARGIN`
  - `UI_BTN_LEFT` (macro, line 106) `#define UI_BTN_LEFT`
  - `UI_LIST_INDENT` (macro, line 110) `#define UI_LIST_INDENT`
  - `UI_SCROLLBAR_W` (macro, line 115) `#define UI_SCROLLBAR_W`
  - `UI_SCROLLBAR_MIN` (macro, line 116) `#define UI_SCROLLBAR_MIN`
  - `UI_SCROLLBAR_PAD` (macro, line 117) `#define UI_SCROLLBAR_PAD`
  - `UI_RESIZE_MARGIN` (macro, line 121) `#define UI_RESIZE_MARGIN`
  - `UI_MENU_W` (macro, line 126) `#define UI_MENU_W`
  - `UI_MENU_ITEM_H` (macro, line 127) `#define UI_MENU_ITEM_H`
  - `UI_MENU_PAD` (macro, line 128) `#define UI_MENU_PAD`
  - `UI_MENU_RADIUS` (macro, line 129) `#define UI_MENU_RADIUS`
  - `UI_CHECK_SZ` (macro, line 130) `#define UI_CHECK_SZ`
  - `UI_MENU_LABEL_H` (macro, line 131) `#define UI_MENU_LABEL_H`
  - `UI_MENU_INPUT_H` (macro, line 132) `#define UI_MENU_INPUT_H`
  - `UI_HAMBURGER_W` (macro, line 133) `#define UI_HAMBURGER_W`
  - `UI_HAMBURGER_GAP` (macro, line 134) `#define UI_HAMBURGER_GAP`
  - `UI_CURSOR_SIZE` (macro, line 135) `#define UI_CURSOR_SIZE`
  - `UI_TOAST_PAD` (macro, line 136) `#define UI_TOAST_PAD`
  - `OMNI_MAX_SUGG` (macro, line 137) `#define OMNI_MAX_SUGG`
  - `UI_OMNI_ROW_H` (macro, line 138) `#define UI_OMNI_ROW_H`
  - `UI_TWO_PI` (macro, line 139) `#define UI_TWO_PI`
  - `UI_INPUT_PAD` (macro, line 143) `#define UI_INPUT_PAD`
  - `UI_CONTROL_FONT` (macro, line 146) `#define UI_CONTROL_FONT`
  - `UI_INPUT_MEASURE_W` (macro, line 152) `#define UI_INPUT_MEASURE_W`
  - `UI_INPUT_WIDTH` (macro, line 153) `#define UI_INPUT_WIDTH`
  - `UI_BUTTON_HPAD` (macro, line 154) `#define UI_BUTTON_HPAD`
  - `UI_FORM_FIELDS_MAX` (macro, line 155) `#define UI_FORM_FIELDS_MAX`
  - `UI_UNDERLINE_OFFSET` (macro, line 160) `#define UI_UNDERLINE_OFFSET`
  - `UI_UNDERLINE_THICK` (macro, line 161) `#define UI_UNDERLINE_THICK`
  - `UI_STRIKE_OFFSET` (macro, line 162) `#define UI_STRIKE_OFFSET`
  - `UI_OVERLINE_OFFSET` (macro, line 163) `#define UI_OVERLINE_OFFSET`
  - `UI_SLICE_MAX` (macro, line 167) `#define UI_SLICE_MAX`
  - `AA_QUEUE_MAX` (macro, line 178) `#define AA_QUEUE_MAX`
  - `UI_MENU_COUNT` (macro, line 229) `#define UI_MENU_COUNT`
  - `UI_HOT_NONE` (macro, line 236) `#define UI_HOT_NONE`
  - `UI_HOT_PART` (macro, line 237) `#define UI_HOT_PART(h)`
  - `UI_HOT_TAB` (macro, line 238) `#define UI_HOT_TAB(h)`
  - `UI_IMAGE_MAX_BODY` (macro, line 251) `#define UI_IMAGE_MAX_BODY`
  - `UI_MAX_TABS` (macro, line 293) `#define UI_MAX_TABS`
  - `UI_READER_COLUMN_W` (macro, line 728) `#define UI_READER_COLUMN_W`
  - `FONT_STASH_MAX_SHEETS` (macro, line 1883) `#define FONT_STASH_MAX_SHEETS`
  - `FONT_STASH_MAX_BYTES` (macro, line 1884) `#define FONT_STASH_MAX_BYTES`
  - `JS_NAV_MAX` (macro, line 2628) `#define JS_NAV_MAX`
  - `HIST_STEP_DEPTH_MAX` (macro, line 2630) `#define HIST_STEP_DEPTH_MAX`
  - `JS_TICKS_PER_LOAD` (macro, line 2756) `#define JS_TICKS_PER_LOAD`
  - `RC_TABLE_SOLVED_N` (macro, line 3876) `#define RC_TABLE_SOLVED_N`
  - `RC_IBOX_MAX` (macro, line 4029) `#define RC_IBOX_MAX`
  - `RC_BOX_STACK_MAX` (macro, line 4031) `#define RC_BOX_STACK_MAX`
  - `RC_FLOAT_MAX` (macro, line 4035) `#define RC_FLOAT_MAX`
  - `RC_FLOAT_FIT_MIN` (macro, line 4042) `#define RC_FLOAT_FIT_MIN`
  - `FLEX_MEASURE_W` (macro, line 6095) `#define FLEX_MEASURE_W`
  - `FLEX_MIN_MEASURE_W` (macro, line 6100) `#define FLEX_MIN_MEASURE_W`
  - `BALANCE_MAX_LINES` (macro, line 6304) `#define BALANCE_MAX_LINES`
  - `RC_COL_FREE_MAX` (macro, line 8141) `#define RC_COL_FREE_MAX`
  - `RC_MAX_OUT_OF_FLOW` (macro, line 9121) `#define RC_MAX_OUT_OF_FLOW`
  - `RC_DEFER_COLS` (macro, line 9287) `#define RC_DEFER_COLS`
  - `RC_DEFER_RANGES` (macro, line 9288) `#define RC_DEFER_RANGES`
  - `RC_DEFER_BAND_RUNS` (macro, line 9372) `#define RC_DEFER_BAND_RUNS`
  - `BUI_CONIC_SLICES` (macro, line 13172) `#define BUI_CONIC_SLICES`
  - `ROW_PAINT_ALL` (macro, line 13911) `#define ROW_PAINT_ALL`
  - `ROW_PAINT_BAND` (macro, line 13912) `#define ROW_PAINT_BAND`
  - `ROW_PAINT_CONTENT` (macro, line 13913) `#define ROW_PAINT_CONTENT`
  - `OV_MAX_DEPTH` (macro, line 14145) `#define OV_MAX_DEPTH`
  - `H2R` (macro, line 14845) `#define H2R(p,q,t)`
  - `UI_LAZY_PER_PASS` (macro, line 15834) `#define UI_LAZY_PER_PASS`
  - `UI_LAZY_PASSES` (macro, line 15835) `#define UI_LAZY_PASSES`
  - `PDF_PAGE_W` (macro, line 16261) `#define PDF_PAGE_W`
  - `PDF_PAGE_H` (macro, line 16262) `#define PDF_PAGE_H`
  - `PDF_MARGIN` (macro, line 16263) `#define PDF_MARGIN`
  - `PNG_PAGE_W` (macro, line 16429) `#define PNG_PAGE_W`
  - `PNG_MARGIN` (macro, line 16453) `#define PNG_MARGIN`
  - `PNG_MAX_H` (macro, line 16454) `#define PNG_MAX_H`
  - `FRAME_BOX_MAX` (macro, line 16659) `#define FRAME_BOX_MAX`
  - `FBW_W` (macro, line 18763) `#define FBW_W`
  - `FBW_H` (macro, line 18764) `#define FBW_H`
  - `FBW_HEADER` (macro, line 18765) `#define FBW_HEADER`
  - `FBW_TABBAR` (macro, line 18766) `#define FBW_TABBAR`
  - `FBW_TOP` (macro, line 18767) `#define FBW_TOP`
  - `FBW_TAB_PAD` (macro, line 18768) `#define FBW_TAB_PAD`
  - `FBW_PAD` (macro, line 18769) `#define FBW_PAD`
  - `FBW_LINE` (macro, line 18770) `#define FBW_LINE`
  - `FBW_GUTTER` (macro, line 18771) `#define FBW_GUTTER`
  - `FBW_MIN_SPLIT` (macro, line 18772) `#define FBW_MIN_SPLIT`
  - `FBW_MAX_SPLIT` (macro, line 18773) `#define FBW_MAX_SPLIT`
  - `FBW_COPY_BTN_W` (macro, line 18774) `#define FBW_COPY_BTN_W`
  - `FBW_COPY_BTN_H` (macro, line 18775) `#define FBW_COPY_BTN_H`
  - `TIMING_QUIET_MS` (macro, line 21163) `#define TIMING_QUIET_MS`
  - `GUI_EVAL_DEFAULT_AFTER_MS` (macro, line 21188) `#define GUI_EVAL_DEFAULT_AFTER_MS`
- Depends on: `gui/browser_ui_internal.h`, `include/block_flow.h`, `include/box_blur.h`, `include/box_style.h`, `include/box_tree.h`, `include/browser.h`, `include/cached_fetch.h`, `include/compositor.h`, `include/css.h`, `include/css_color.h`, `include/css_gradient.h`, `include/css_mask.h`, `include/css_values.h`, `include/data_url.h`, `include/download.h`, `include/exact_key.h`, `include/fb_cmdline.h`, `include/fb_panes.h`, `include/find_text.h`, `include/form.h`, `include/frame_clock.h`, `include/frame_host.h`, `include/freebug.h`, `include/hls.h`, `include/host_conf.h`, `include/hostblock.h`, `include/hostedit.h`, `include/identity.h`, `include/image_decode.h`, `include/interp.h`, `include/js_policy.h`, `include/lazy_load.h`, `include/link_nav.h`, `include/mask_cache.h`, `include/media_decoder.h`, `include/nav_token.h`, `include/net_realm.h`, `include/pdf_export.h`, `include/prefetch.h`, `include/prefs.h`, `include/profile.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/shm_slots.h`, `include/svg_paint.h`, `include/svg_render.h`, `include/tab.h`, `include/table_layout.h`, `include/text_case.h`, `include/text_shape.h`, `include/textfield.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/video_controls.h`, `include/video_pick.h`, `include/web_storage.h`, `include/webcaps.h`, `include/webfont.h`, `include/webfont_load.h`, `include/wl_guard.h`, `include/ws_hub.h`, `include/zoom.h`

## gui/browser_ui_internal.h
- Doc: bui_chrome_view: ui_theme ui_theme_for(int mode);          /* maps a ui_theme_mode to a palette...
- Layer: presentation
- Language: h
- Symbols:
  - `ui_rgb` (struct, line 41)
  - `ui_theme` (struct, line 43)
  - `bui_chrome_view` (struct, line 132)
  - `bui_find_view` (struct, line 150)
  - `ui_theme_mode` (enum, line 107)
  - `b` (type_alias, line 40) `typedef struct ui_rgb { double r, g, b;`
  - `body_font` (type_alias, line 42) `typedef struct ui_theme { double body_font;`
  - `set_rgb` (function, line 120) `void set_rgb(cairo_t *cr, ui_rgb c);`
  - `bui_paint_findbar` (function, line 163) `void bui_paint_findbar(cairo_t *cr, const bui_find_view *v);`
  - `bui_chrome_font` (function, line 165) `void bui_chrome_font(cairo_t *cr, double size);`
  - `bui_paint_chrome` (function, line 167) `void bui_paint_chrome(cairo_t *cr, const bui_chrome_view *v);`
  - `bui_url_text_x` (function, line 170) `double bui_url_text_x(const bui_chrome_view *v, cairo_t *cr, double *shift);`
  - `bui_url_index_at` (function, line 172) `size_t bui_url_index_at(cairo_t *cr, const bui_chrome_view *v, double x);`
  - `bui_round_rect` (function, line 174) `void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double r);`
  - `bui_paint_video_bar` (function, line 179) `void bui_paint_video_bar(cairo_t *cr, const vcl_geom *g, int paused, double pos, double total);`
  - `bui_paint_site_panel` (function, line 183) `void bui_paint_site_panel(cairo_t *cr, const ui_theme *th, const sp_panel *p, const sp_geom *g, int hot_action);`
  - `area` (function, line 189) `* tiled over the mask area (ax, ay, aw, ah) by the layer geometry `geo` (css.h CSS_MG_*, * resolved by...`
  - `FREEDOM_BROWSER_UI_INTERNAL_H` (macro, line 2) `#define FREEDOM_BROWSER_UI_INTERNAL_H`
  - `UI_FONT_SIZE` (macro, line 30) `#define UI_FONT_SIZE`
  - `UI_TEXT_MARGIN` (macro, line 31) `#define UI_TEXT_MARGIN`
  - `UI_HEADING_LEVELS` (macro, line 32) `#define UI_HEADING_LEVELS`
  - `BUI_CHROME_FONT` (macro, line 127) `#define BUI_CHROME_FONT`
  - `BUI_CHROME_FONT_SIZE` (macro, line 128) `#define BUI_CHROME_FONT_SIZE`
  - `BUI_URL_FONT_SIZE` (macro, line 129) `#define BUI_URL_FONT_SIZE`
- Depends on: `include/chrome_layout.h`, `include/freedom_config.h`, `include/video_controls.h`
- Imported by: `gui/browser_ui.c`, `gui/bui_chrome.c`, `gui/bui_mask_img.c`, `gui/bui_theme.c`


Next: [KB_gui_p3.md](KB_gui_p3.md)
