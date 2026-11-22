# Subsystem: gui (page 2 of 3)
Previous: [KB_gui.md](KB_gui.md)

## gui/browser_ui.c (continued)
  - `layout_cache_free` (function, line 15700) `static void layout_cache_free(browser_window *w)`
  - `frame_undo_restore` (function, line 15719) `static void frame_undo_restore(rc_layout *L, frame_undo *u)`
  - `paint_structured` (function, line 15730) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
  - `write_doc_pdf` (function, line 15892) `static long write_doc_pdf(browser_window *w, const char *path)`
  - `export_pdf` (function, line 16001) `static void export_pdf(browser_window *w)`
  - `ui_render_viewport_w` (function, line 16056) `int ui_render_viewport_w(void)`
  - `paint_png_inflow` (function, line 16085) `static void paint_png_inflow(const png_flow_ctx *c, int only_root)`
  - `paint_png_deferred` (function, line 16122) `static void paint_png_deferred(void *ctx, int root)`
  - `write_doc_png` (function, line 16222) `static long write_doc_png(browser_window *w, const char *path)`
  - `render_frame_surface` (function, line 16234) `static cairo_surface_t *render_frame_surface(const pv_view *view, tab *ft, const char *url,
     ...`
  - `fill_frame_slot` (function, line 16275) `static void fill_frame_slot(browser_window *w, const rd_block *b, ui_image *slot,
               ...`
  - `refresh_frame_images` (function, line 16333) `static void refresh_frame_images(browser_window *w)`
  - `export_png` (function, line 16351) `static void export_png(browser_window *w)`
  - `caller` (function, line 16385) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
  - `ui_render_png` (function, line 16408) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)`
  - `render_doc_images` (function, line 16468) `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...`
  - `ui_render_png_images` (function, line 16501) `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_png_frames` (function, line 16507) `ui_status ui_render_png_frames(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_render_pdf_images` (function, line 16513) `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
  - `ui_dump_layout` (function, line 16528) `ui_status ui_dump_layout(const rd_doc *doc)`
  - `link_at_point` (function, line 16600) `static const char *link_at_point(browser_window *w, double px, double py)`
  - `resolve_box_cursor` (function, line 16691) `static int resolve_box_cursor(const rd_doc *doc, int block_id)`
  - `box_pointer_events_none` (function, line 16705) `static int box_pointer_events_none(const rd_doc *doc, int block_id)`
  - `cursor_at_point` (function, line 16721) `static int cursor_at_point(browser_window *w, double px, double py)`
  - `node_at_point` (function, line 16786) `static dom_node_id node_at_point(browser_window *w, double px, double py)`
  - `Firefox` (function, line 16794) `* on its face does in Firefox (spec/page_view.md, tanda 40). */
static const rd_block *submit_pro...`
  - `frag_at_point` (function, line 16813) `static dom_node_id frag_at_point(browser_window *w, double px, double py,
                       ...`
  - `reference` (function, line 16867) `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
  - `set_page_url` (function, line 16886) `static void set_page_url(browser_window *w, const char *url)`
  - `gui_frame_top_msg` (function, line 16914) `static void gui_frame_top_msg(void *ctx, const char *data, size_t len)`
  - `frames_drain` (function, line 16927) `static void frames_drain(browser_window *w)`
  - `frames_apply` (function, line 16945) `static void frames_apply(browser_window *w, const tab_page *page)`
  - `ws_apply_ops` (function, line 16959) `static void ws_apply_ops(browser_window *w, const tab_page *page)`
  - `apply_history_ops` (function, line 16996) `static void apply_history_ops(browser_window *w, const tab_page *page)`
  - `history_step` (function, line 17008) `static void history_step(browser_window *w, int steps)`
  - `page_render_caps` (function, line 17036) `static rdp_caps page_render_caps(const browser_window *w)`
  - `wc_render_caps` (function, line 17037) `return wc_render_caps(wc_derive((wc_input)`
  - `apply_click_result` (function, line 17055) `static int apply_click_result(browser_window *w, tab_page *page)`
  - `on_tab_async` (function, line 17107) `static void on_tab_async(browser_window *w)`
  - `gui_quiesce` (function, line 17127) `static void gui_quiesce(browser_window *w)`
  - `memory` (function, line 17135) `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
  - `GET` (function, line 17229) `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
  - `ensure_download_dir` (function, line 17263) `static int ensure_download_dir(char *out, size_t outsz)`
  - `write_file_atomic` (function, line 17278) `static int write_file_atomic(const char *path, const void *bytes, size_t len)`
  - `save_download` (function, line 17300) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...`
  - `save_current_page` (function, line 17333) `static void save_current_page(browser_window *w)`
  - `deliver_fetch_result` (function, line 17343) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
  - `drain_fetch_results` (function, line 17409) `static void drain_fetch_results(browser_window *w)`
  - `toggle_reader` (function, line 17538) `static void toggle_reader(browser_window *w)`
  - `menu_item_checked` (function, line 17549) `static int menu_item_checked(const browser_window *w, size_t i)`
  - `menu_item_toggle` (function, line 17571) `static void menu_item_toggle(browser_window *w, size_t i)`
  - `draw_menu` (function, line 17685) `static void draw_menu(cairo_t *cr, browser_window *w)`
  - `draw_hover_url` (function, line 17807) `static double draw_hover_url(cairo_t *cr, browser_window *w)`
  - `draw_toast` (function, line 17839) `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)`
  - `page_identity` (function, line 17865) `static chl_identity page_identity(const browser_window *w)`
  - `chrome_view_fill` (function, line 17870) `static void chrome_view_fill(browser_window *w, const chl_layout *l, const char **titles,
       ...`
  - `paint_chrome` (function, line 17900) `static void paint_chrome(cairo_t *cr, browser_window *w)`
  - `draw_omnibox` (function, line 17912) `static void draw_omnibox(cairo_t *cr, browser_window *w)`
  - `draw_findbar` (function, line 17947) `static void draw_findbar(cairo_t *cr, browser_window *w)`
  - `paint` (function, line 17962) `static void paint(browser_window *w)`
  - `redraw` (function, line 18066) `static void redraw(browser_window *w)`
  - `wm_base_ping` (function, line 18097) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 18103) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 18111) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `wl_array_for_each` (function, line 18127) `wl_array_for_each(st, states)`
  - `toplevel_close` (function, line 18133) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 18142) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `set_cursor` (function, line 18154) `static void set_cursor(browser_window *w, int cur_kind)`
  - `element` (function, line 18184) `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...`
  - `update_hover` (function, line 18195) `static void update_hover(browser_window *w)`
  - `fbw_split_y` (function, line 18276) `static double fbw_split_y(const freebug_window *fb)`
  - `freebug_ensure_buffer` (function, line 18285) `static int freebug_ensure_buffer(freebug_window *fb)`
  - `fbw_level_rgb` (function, line 18312) `static void fbw_level_rgb(int level, double *r, double *g, double *b)`
  - `fbw_console_lines` (function, line 18323) `static size_t fbw_console_lines(const fb_buffer *log, int filter)`
  - `fbw_cell_w` (function, line 18338) `static double fbw_cell_w(cairo_t *cr)`
  - `fbw_text_lines` (function, line 18344) `static size_t fbw_text_lines(const char *t)`
  - `fbw_arg_hint` (function, line 18351) `static const char *fbw_arg_hint(int which)`
  - `fbw_paint_tabs` (function, line 18362) `static void fbw_paint_tabs(cairo_t *cr, const freebug_window *fb)`
  - `fbw_paint_pane` (function, line 18395) `static void fbw_paint_pane(cairo_t *cr, const freebug_window *fb, double y, double split_y)`
  - `freebug_paint` (function, line 18426) `static void freebug_paint(freebug_window *fb)`
  - `freebug_redraw_fb` (function, line 18638) `static void freebug_redraw_fb(freebug_window *fb)`
  - `freebug_redraw` (function, line 18647) `static void freebug_redraw(browser_window *w)`
  - `freebug_hide` (function, line 18651) `static void freebug_hide(browser_window *w)`
  - `fbw_xdg_surface_configure` (function, line 18667) `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `fbw_toplevel_configure` (function, line 18675) `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...`
  - `fbw_toplevel_close` (function, line 18684) `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)`
  - `freebug_show` (function, line 18694) `static void freebug_show(browser_window *w)`
  - `freebug_toggle` (function, line 18724) `static void freebug_toggle(browser_window *w)`
  - `freebug_destroy` (function, line 18729) `static void freebug_destroy(browser_window *w)`
  - `freebug_owns_surface` (function, line 18738) `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)`
  - `freebug_is_open` (function, line 18742) `static int freebug_is_open(const browser_window *w)`
  - `freebug_repl_worker` (function, line 18749) `static tab *freebug_repl_worker(browser_window *w)`
  - `freebug_pane_refresh` (function, line 18791) `static void freebug_pane_refresh(browser_window *w)`
  - `freebug_set_tab` (function, line 18828) `static void freebug_set_tab(browser_window *w, int which)`
  - `freebug_panes_invalidate` (function, line 18846) `static void freebug_panes_invalidate(browser_window *w)`
  - `freebug_eval` (function, line 18853) `static void freebug_eval(browser_window *w)`
  - `freebug_set_editor` (function, line 18896) `static void freebug_set_editor(freebug_window *fb, const char *s)`
  - `freebug_complete` (function, line 18904) `static void freebug_complete(browser_window *w)`
  - `freebug_handle_key` (function, line 18934) `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...`
  - `freebug_pointer_button` (function, line 18987) `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...`
  - `freebug_pointer_motion` (function, line 19016) `static void freebug_pointer_motion(browser_window *w)`
  - `freebug_pointer_axis` (function, line 19038) `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)`
  - `ptr_enter` (function, line 19056) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
  - `ptr_leave` (function, line 19074) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
  - `ptr_motion` (function, line 19091) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
  - `stop_loading` (function, line 19119) `static int stop_loading(browser_window *w)`
  - `load_current` (function, line 19131) `static void load_current(browser_window *w)`
  - `go_omnibox` (function, line 19144) `static void go_omnibox(browser_window *w)`
  - `ptr_button` (function, line 19189) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
  - `scroll_line_px` (function, line 19423) `static double scroll_line_px(const browser_window *w)`
  - `ptr_axis` (function, line 19427) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
  - `ptr_frame` (function, line 19451) `static void ptr_frame(void *d, struct wl_pointer *p)`
  - `mime_is_text` (function, line 19467) `static int mime_is_text(const char *mime)`
  - `data_offer_source_actions` (function, line 19485) `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_offer_action` (function, line 19488) `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_device_data_offer` (function, line 19498) `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...`
  - `data_device_selection` (function, line 19510) `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...`
  - `data_device_enter` (function, line 19529) `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...`
  - `data_device_leave` (function, line 19534) `static void data_device_leave(void *d, struct wl_data_device *dev)`
  - `data_device_motion` (function, line 19535) `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...`
  - `data_device_drop` (function, line 19539) `static void data_device_drop(void *d, struct wl_data_device *dev)`
  - `data_source_cancelled` (function, line 19550) `static void data_source_cancelled(void *data, struct wl_data_source *src)`
  - `data_source_send` (function, line 19556) `static void data_source_send(void *data, struct wl_data_source *src,
                            ...`
  - `data_source_target` (function, line 19569) `static void data_source_target(void *d, struct wl_data_source *s, const char *m)`
  - `freebug_copy_console` (function, line 19581) `static void freebug_copy_console(browser_window *w)`
  - `insert_pasted_text` (function, line 19649) `static void insert_pasted_text(browser_window *w, const char *text, size_t len)`
  - `clipboard_copy` (function, line 19715) `static void clipboard_copy(browser_window *w)`
  - `keyboard_keymap` (function, line 19765) `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...`
  - `keyboard_enter` (function, line 19786) `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...`
  - `keyboard_leave` (function, line 19793) `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)`
  - `key_sym_to_js_key` (function, line 19801) `static const char *key_sym_to_js_key(xkb_keysym_t sym)`
  - `key_sym_to_keycode` (function, line 19827) `static int key_sym_to_keycode(xkb_keysym_t sym)`
  - `dispatch_js_event` (function, line 19852) `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...`
  - `fip_focus` (function, line 19909) `static void fip_focus(browser_window *w)`
  - `fip_open_bar` (function, line 19918) `static void fip_open_bar(browser_window *w)`
  - `fip_close_bar` (function, line 19929) `static void fip_close_bar(browser_window *w)`
  - `fip_step` (function, line 19940) `static void fip_step(browser_window *w, int dir)`
  - `fip_edited` (function, line 19949) `static void fip_edited(browser_window *w)`
  - `fip_type` (function, line 19955) `static void fip_type(browser_window *w, const char *s, size_t n)`
  - `fip_key` (function, line 19966) `static int fip_key(browser_window *w, xkb_keysym_t sym, const char *utf8, int n, int ctrl,
      ...`
  - `fip_click` (function, line 19999) `static int fip_click(browser_window *w, double x, double y)`
  - `fip_hot_at` (function, line 20014) `static chl_find_part fip_hot_at(const browser_window *w, double x, double y)`
  - `handle_key_press` (function, line 20024) `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...`
  - `key_is_repeatable` (function, line 20397) `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)`
  - `key_repeat_arm` (function, line 20413) `static void key_repeat_arm(browser_window *w, uint32_t key)`
  - `key_repeat_stop` (function, line 20426) `static void key_repeat_stop(browser_window *w)`
  - `key_repeat_fire` (function, line 20437) `static void key_repeat_fire(browser_window *w)`
  - `keyboard_key` (function, line 20451) `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...`
  - `keyboard_modifiers` (function, line 20491) `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...`
  - `keyboard_repeat_info` (function, line 20500) `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)`
  - `seat_caps` (function, line 20519) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
  - `seat_name` (function, line 20530) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
  - `registry_global` (function, line 20537) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
  - `registry_remove` (function, line 20557) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
  - `gui_is_idle` (function, line 20570) `static int gui_is_idle(const browser_window *w)`
  - `gui_timing_step` (function, line 20581) `static int gui_timing_step(browser_window *w, uint64_t now)`
  - `startup_abort_release` (function, line 20636) `static void startup_abort_release(browser_window *w)`
  - `ui_run_browser` (function, line 20647) `ui_status ui_run_browser(const char *start_url)`
  - `cost` (function, line 21127) `* measured cost (floor 33 ms = the existing ~30 fps ceiling):
             * cheap pages paint at...`
  - `offset` (function, line 179) `* offset (labels and the flag live in one place, no magic indices);`
  - `fields` (function, line 295) `* fields (so the 200+ render/event call sites stay unchanged);`
  - `delay` (function, line 422) `* timer delay (tab_page.next_timer_ms);`
  - `main` (function, line 582) `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never...`
  - `proxy` (function, line 1143) `* and enable each proxy ("1" => the default port);`
  - `video_feeder_thread` (function, line 1199) `static void *video_feeder_thread(void *arg);`
  - `box_pad_px` (function, line 1302) `static double box_pad_px(int px_val, int pct_pm, double cb_w);`
  - `page_trusted` (function, line 1682) `static int page_trusted(const browser_window *w);`
  - `only` (function, line 1774) `* Trusted pages only (untrusted CSS is still applied by the worker, but its * fonts never reach the parent...`
  - `hb_is_allowlisted` (function, line 1911) `&& hb_is_allowlisted(w->hosts, ihost);`
  - `proceed` (function, line 1958) `* may proceed (cfg and pr->allowlisted are then set);`
  - `secure_fetch` (function, line 2228) `* through secure_fetch (Zero Trust);`
  - `string` (function, line 2396) `* or an empty string (unset, blocked, or off by caps.images), so there is no * decision to re-check, unlike...`
  - `do_load` (function, line 2457) `static void do_load(browser_window *w, const char *url);`
  - `tab_new` (function, line 2462) `static void tab_new(browser_window *w, const char *url);`
  - `toggle` (function, line 2476) `* No network: a capability toggle (images/CSS) re-renders from cache. Does nothing * when there is no cached source...`
  - `stylesheets` (function, line 2635) `* External stylesheets (Hito 27) follow the author-styles opt-in -- or the * trusted-host doctrine (Hito 28)...`
  - `body` (function, line 2668) `* every served CSS body (serial and pool paths alike). */ font_stash_reset(w);`
  - `ALIVE` (function, line 2776) `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or...`
  - `resolve` (function, line 3033) `* origin so its relative references and local images resolve (confined to the * document's directory) -- a local...`
  - `smaller` (function, line 3600) `* size when the content is smaller (height) or wider (min-width);`
  - `HarfBuzz` (function, line 4077) `* descriptor via HarfBuzz (text_shape);`
  - `run` (function, line 4343) `* continuation run (block_id < 0 with no block break) deliberately skips reconcile * to stay on the line, and that...`
  - `produced` (function, line 4647) `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target...`
  - `line` (function, line 4747) `* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the...`
  - `box_path4` (function, line 4950) `static void box_path4(cairo_t *cr, double x, double y, double w, double h, const double *rc);`
  - `block_leaves_flow` (function, line 5032) `static int block_leaves_flow(const rd_doc *doc, const rd_block *bk);`
  - `container` (function, line 5823) `* were the container (github's tab pill). */ int item = item_at_level(doc, rd_at(doc, k), cid);`
  - `way` (function, line 5923) `* intrinsic box either way (it does not wrap below its own size). */ static int block_leaves_flow(const rd_doc *doc...`
  - `empty_atom_continues_line` (function, line 5926) `static int empty_atom_continues_line(const rd_doc *doc, size_t run_i, int box_id);`
  - `width` (function, line 6001) `* the line: the layout spends its width (reconcile_boxes_below), so the * measure must too, or the label wraps...`
  - `layout` (function, line 6246) `* hypothetical size in the real layout (Flexbox 9.2.3). */ if (ibd != NULL && ibd->box_min_w > 0) base =...`
  - `close_all_boxes` (function, line 6338) `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);`
  - `deepest_open_on_path` (function, line 6366) `static int deepest_open_on_path(const rc_state *outer, const rd_doc *doc, int block_id);`
  - `TABLE` (function, line 6481) `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all...`
  - `band_shared_box` (function, line 6591) `static int band_shared_box(const rd_doc *doc, const rc_state *s, size_t start, size_t end);`
  - `axis` (function, line 7009) `* differs: items stack on the vertical main axis (fx_column_place) and align on * the horizontal cross axis...`
  - `struct` (function, line 7213) `* struct (0 = auto);`
  - `descriptor` (function, line 7222) `* placement rides the nested descriptor (spec/grid_areas.md 6). */ int nbc = child_cont_at_level(doc, bk, cid);`
  - `builds` (function, line 7466) `* wraps beside it: the same band the top level builds (spec/float.md). */ const rd_block *fk = rd_at(doc, k);`
  - `flow` (function, line 7562) `* it collapse their vertical margins with each other exactly as in * the main flow (CSS 2.1 8.3.1), and none escapes...`
  - `own` (function, line 7610) `* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and...`
  - `items` (function, line 7691) `* items (Flexbox 4.2);`
  - `multicol_fragment` (function, line 7873) `static double multicol_fragment(rc_layout *L, const rc_open_box *ob, double content_bottom);`
  - `behind` (function, line 8163) `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old...`
  - `treatment` (function, line 8757) `* block treatment (shrink-wrapped and placed by text-align), which is what a * standalone centred call-to-action...`
  - `it` (function, line 8821) `* sized atom with text reaches it when the flow leaves it (leave_inline_box). */ s->pen_x += ib->pad_l + (ib_empty ?...`
  - `context` (function, line 9000) `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document...`
  - `path` (function, line 9032) `* overflow degrades to the old inline path (fail-open: content overlaps or * stacks instead of vanishing). With no...`
  - `beside` (function, line 9231) `* margin: nothing to pull up beside (CSS 2.1 9.5.1 rule 5 -- a float's top is never * above an earlier block). They...`
  - `x` (function, line 9494) `* reported x is already the BORDER x (the §7c.2 rule);`
  - `chain` (function, line 10259) `* chain (the box that left the normal flow at this pen position);`
  - `anchor` (function, line 10374) `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is...`
  - `key` (function, line 10443) `* founders splits by key (stories, rail, footer nav each take * their column);`
  - `inline` (function, line 10445) `* lays out whole inline (fail-open: today's path). */ if (getenv("FREEDOM_DEFER_DEBUG") != NULL) fprintf(stderr...`
  - `have` (function, line 10480) `* as they always have (spec/float.md §6b.3). The line still open beside * the previous float is committed first, at...`
  - `standalone` (function, line 10501) `* must not be treated as standalone (which would flush that line and give * the element a row of its own -- R7). */...`
  - `margin` (function, line 10924) `* own left margin (the margin box starts at the anchor point), a right- * anchored one ends at it. Same for the...`
  - `rd_build` (function, line 11642) `* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr...`
  - `descriptors` (function, line 11906) `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection —...`
  - `again` (function, line 11987) `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one...`
  - `blocking` (function, line 12275) `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);`
  - `rect` (function, line 12718) `* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops...`
  - `layer` (function, line 13020) `* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the...`
  - `convention` (function, line 13176) `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE || style...`
  - `row_owner_block_id` (function, line 13326) `static int row_owner_block_id(const rc_layout *L, const rc_row *r);`
  - `exactly` (function, line 13372) `* the resolved size exactly (like the SVG path above): routing through * paint_image_row would re-resolve a % width...`
  - `bg` (function, line 13604) `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);`
  - `rows` (function, line 13837) `* RC_IMAGE rows (see its declaration);`
  - `made` (function, line 14408) `* its zero channels made (255,255,255,alpha 0) -- an invalid * premultiplied value Cairo composites as ADDITIVE...`
  - `the` (function, line 14512) `* the (already filtered) group with the shadow color, blur it, and * paint it under the group at the declared offset...`
  - `fill` (function, line 14696) `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in...`
  - `overflow` (function, line 14756) `* adding two of them in int was signed overflow (UB, found by UBSan). */ double ox = left + bx->x +...`
  - `compositing` (function, line 14799) `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context...`
  - `once` (function, line 15518) `* box the layout never placed loads at once (fail open);`
  - `origin` (function, line 16464) `* top_url is the page origin (https or file://);`
  - `in` (function, line 16550) `* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);`
  - `sf_ws_url_check` (function, line 16969) `&& sf_ws_url_check(op->data) == SF_OK && rp_host_of(op->data, host, sizeof host) == 0 &&...`
  - `presentation` (function, line 17569) `* affect presentation (a repaint, which re-runs layout, suffices);`
  - `resizes` (function, line 18119) `* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);`
  - `down` (function, line 19050) `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void...`
  - `loop` (function, line 19640) `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately...`
  - `saving` (function, line 20670) `* disables saving (never clobber);`
  - `redraws` (function, line 20764) `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A...`
  - `moves` (function, line 20777) `* client that stops reading its socket while the pointer moves (spec/wl_guard.md). */ if...`
  - `_GNU_SOURCE` (macro, line 12) `#define _GNU_SOURCE`
  - `UI_TOOLBAR_H` (macro, line 102) `#define UI_TOOLBAR_H`
  - `UI_MARGIN` (macro, line 103) `#define UI_MARGIN`
  - `UI_BTN_LEFT` (macro, line 104) `#define UI_BTN_LEFT`
  - `UI_LIST_INDENT` (macro, line 108) `#define UI_LIST_INDENT`
  - `UI_SCROLLBAR_W` (macro, line 113) `#define UI_SCROLLBAR_W`
  - `UI_SCROLLBAR_MIN` (macro, line 114) `#define UI_SCROLLBAR_MIN`
  - `UI_SCROLLBAR_PAD` (macro, line 115) `#define UI_SCROLLBAR_PAD`
  - `UI_RESIZE_MARGIN` (macro, line 119) `#define UI_RESIZE_MARGIN`
  - `UI_MENU_W` (macro, line 124) `#define UI_MENU_W`
  - `UI_MENU_ITEM_H` (macro, line 125) `#define UI_MENU_ITEM_H`
  - `UI_MENU_PAD` (macro, line 126) `#define UI_MENU_PAD`
  - `UI_MENU_RADIUS` (macro, line 127) `#define UI_MENU_RADIUS`
  - `UI_CHECK_SZ` (macro, line 128) `#define UI_CHECK_SZ`
  - `UI_MENU_LABEL_H` (macro, line 129) `#define UI_MENU_LABEL_H`
  - `UI_MENU_INPUT_H` (macro, line 130) `#define UI_MENU_INPUT_H`
  - `UI_HAMBURGER_W` (macro, line 131) `#define UI_HAMBURGER_W`
  - `UI_HAMBURGER_GAP` (macro, line 132) `#define UI_HAMBURGER_GAP`
  - `UI_CURSOR_SIZE` (macro, line 133) `#define UI_CURSOR_SIZE`
  - `UI_TOAST_PAD` (macro, line 134) `#define UI_TOAST_PAD`
  - `OMNI_MAX_SUGG` (macro, line 135) `#define OMNI_MAX_SUGG`
  - `UI_OMNI_ROW_H` (macro, line 136) `#define UI_OMNI_ROW_H`
  - `UI_TWO_PI` (macro, line 137) `#define UI_TWO_PI`
  - `UI_INPUT_PAD` (macro, line 141) `#define UI_INPUT_PAD`
  - `UI_CONTROL_FONT` (macro, line 144) `#define UI_CONTROL_FONT`
  - `UI_INPUT_MEASURE_W` (macro, line 150) `#define UI_INPUT_MEASURE_W`
  - `UI_INPUT_WIDTH` (macro, line 151) `#define UI_INPUT_WIDTH`
  - `UI_BUTTON_HPAD` (macro, line 152) `#define UI_BUTTON_HPAD`
  - `UI_FORM_FIELDS_MAX` (macro, line 153) `#define UI_FORM_FIELDS_MAX`
  - `UI_UNDERLINE_OFFSET` (macro, line 158) `#define UI_UNDERLINE_OFFSET`
  - `UI_UNDERLINE_THICK` (macro, line 159) `#define UI_UNDERLINE_THICK`
  - `UI_STRIKE_OFFSET` (macro, line 160) `#define UI_STRIKE_OFFSET`
  - `UI_OVERLINE_OFFSET` (macro, line 161) `#define UI_OVERLINE_OFFSET`
  - `UI_SLICE_MAX` (macro, line 165) `#define UI_SLICE_MAX`
  - `AA_QUEUE_MAX` (macro, line 176) `#define AA_QUEUE_MAX`
  - `UI_MENU_COUNT` (macro, line 227) `#define UI_MENU_COUNT`
  - `UI_HOT_NONE` (macro, line 234) `#define UI_HOT_NONE`
  - `UI_HOT_PART` (macro, line 235) `#define UI_HOT_PART(h)`
  - `UI_HOT_TAB` (macro, line 236) `#define UI_HOT_TAB(h)`
  - `UI_IMAGE_MAX_BODY` (macro, line 249) `#define UI_IMAGE_MAX_BODY`
  - `UI_MAX_TABS` (macro, line 291) `#define UI_MAX_TABS`
  - `UI_READER_COLUMN_W` (macro, line 697) `#define UI_READER_COLUMN_W`
  - `FONT_STASH_MAX_SHEETS` (macro, line 1751) `#define FONT_STASH_MAX_SHEETS`
  - `FONT_STASH_MAX_BYTES` (macro, line 1752) `#define FONT_STASH_MAX_BYTES`
  - `JS_NAV_MAX` (macro, line 2471) `#define JS_NAV_MAX`
  - `HIST_STEP_DEPTH_MAX` (macro, line 2473) `#define HIST_STEP_DEPTH_MAX`
  - `JS_TICKS_PER_LOAD` (macro, line 2597) `#define JS_TICKS_PER_LOAD`
  - `RC_TABLE_SOLVED_N` (macro, line 3646) `#define RC_TABLE_SOLVED_N`
  - `RC_IBOX_MAX` (macro, line 3799) `#define RC_IBOX_MAX`
  - `RC_BOX_STACK_MAX` (macro, line 3801) `#define RC_BOX_STACK_MAX`
  - `RC_FLOAT_MAX` (macro, line 3805) `#define RC_FLOAT_MAX`
  - `RC_FLOAT_FIT_MIN` (macro, line 3812) `#define RC_FLOAT_FIT_MIN`
  - `FLEX_MEASURE_W` (macro, line 5865) `#define FLEX_MEASURE_W`
  - `FLEX_MIN_MEASURE_W` (macro, line 5870) `#define FLEX_MIN_MEASURE_W`
  - `BALANCE_MAX_LINES` (macro, line 6052) `#define BALANCE_MAX_LINES`
  - `RC_COL_FREE_MAX` (macro, line 7889) `#define RC_COL_FREE_MAX`
  - `RC_MAX_OUT_OF_FLOW` (macro, line 8869) `#define RC_MAX_OUT_OF_FLOW`
  - `RC_DEFER_COLS` (macro, line 9035) `#define RC_DEFER_COLS`
  - `RC_DEFER_RANGES` (macro, line 9036) `#define RC_DEFER_RANGES`
  - `RC_DEFER_BAND_RUNS` (macro, line 9120) `#define RC_DEFER_BAND_RUNS`
  - `BUI_CONIC_SLICES` (macro, line 12791) `#define BUI_CONIC_SLICES`
  - `ROW_PAINT_ALL` (macro, line 13530) `#define ROW_PAINT_ALL`
  - `ROW_PAINT_BAND` (macro, line 13531) `#define ROW_PAINT_BAND`
  - `ROW_PAINT_CONTENT` (macro, line 13532) `#define ROW_PAINT_CONTENT`
  - `OV_MAX_DEPTH` (macro, line 13764) `#define OV_MAX_DEPTH`
  - `H2R` (macro, line 14464) `#define H2R(p,q,t)`
  - `UI_LAZY_PER_PASS` (macro, line 15449) `#define UI_LAZY_PER_PASS`
  - `UI_LAZY_PASSES` (macro, line 15450) `#define UI_LAZY_PASSES`
  - `PDF_PAGE_W` (macro, line 15876) `#define PDF_PAGE_W`
  - `PDF_PAGE_H` (macro, line 15877) `#define PDF_PAGE_H`
  - `PDF_MARGIN` (macro, line 15878) `#define PDF_MARGIN`
  - `PNG_PAGE_W` (macro, line 16043) `#define PNG_PAGE_W`
  - `PNG_MARGIN` (macro, line 16067) `#define PNG_MARGIN`
  - `PNG_MAX_H` (macro, line 16068) `#define PNG_MAX_H`
  - `FRAME_BOX_MAX` (macro, line 16273) `#define FRAME_BOX_MAX`
  - `FBW_W` (macro, line 18233) `#define FBW_W`
  - `FBW_H` (macro, line 18234) `#define FBW_H`
  - `FBW_HEADER` (macro, line 18235) `#define FBW_HEADER`
  - `FBW_TABBAR` (macro, line 18236) `#define FBW_TABBAR`
  - `FBW_TOP` (macro, line 18237) `#define FBW_TOP`
  - `FBW_TAB_PAD` (macro, line 18238) `#define FBW_TAB_PAD`
  - `FBW_PAD` (macro, line 18239) `#define FBW_PAD`
  - `FBW_LINE` (macro, line 18240) `#define FBW_LINE`
  - `FBW_GUTTER` (macro, line 18241) `#define FBW_GUTTER`
  - `FBW_MIN_SPLIT` (macro, line 18242) `#define FBW_MIN_SPLIT`
  - `FBW_MAX_SPLIT` (macro, line 18243) `#define FBW_MAX_SPLIT`
  - `FBW_COPY_BTN_W` (macro, line 18244) `#define FBW_COPY_BTN_W`
  - `FBW_COPY_BTN_H` (macro, line 18245) `#define FBW_COPY_BTN_H`
  - `TIMING_QUIET_MS` (macro, line 20580) `#define TIMING_QUIET_MS`
  - `GUI_EVAL_DEFAULT_AFTER_MS` (macro, line 20602) `#define GUI_EVAL_DEFAULT_AFTER_MS`
- Depends on: `gui/browser_ui_internal.h`, `include/block_flow.h`, `include/box_blur.h`, `include/box_style.h`, `include/box_tree.h`, `include/browser.h`, `include/cached_fetch.h`, `include/compositor.h`, `include/css.h`, `include/css_color.h`, `include/css_gradient.h`, `include/css_mask.h`, `include/css_values.h`, `include/data_url.h`, `include/download.h`, `include/exact_key.h`, `include/fb_cmdline.h`, `include/fb_panes.h`, `include/find_text.h`, `include/form.h`, `include/frame_clock.h`, `include/frame_host.h`, `include/freebug.h`, `include/hls.h`, `include/host_conf.h`, `include/hostblock.h`, `include/hostedit.h`, `include/identity.h`, `include/image_decode.h`, `include/interp.h`, `include/js_policy.h`, `include/lazy_load.h`, `include/link_nav.h`, `include/mask_cache.h`, `include/media_decoder.h`, `include/net_realm.h`, `include/pdf_export.h`, `include/prefetch.h`, `include/prefs.h`, `include/profile.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/shm_slots.h`, `include/svg_paint.h`, `include/svg_render.h`, `include/tab.h`, `include/table_layout.h`, `include/text_case.h`, `include/text_shape.h`, `include/textfield.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/web_storage.h`, `include/webcaps.h`, `include/webfont.h`, `include/webfont_load.h`, `include/wl_guard.h`, `include/ws_hub.h`, `include/zoom.h`

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
  - `area` (function, line 179) `* tiled over the mask area (ax, ay, aw, ah) by the layer geometry `geo` (css.h CSS_MG_*, * resolved by...`
  - `FREEDOM_BROWSER_UI_INTERNAL_H` (macro, line 2) `#define FREEDOM_BROWSER_UI_INTERNAL_H`
  - `UI_FONT_SIZE` (macro, line 30) `#define UI_FONT_SIZE`
  - `UI_TEXT_MARGIN` (macro, line 31) `#define UI_TEXT_MARGIN`
  - `UI_HEADING_LEVELS` (macro, line 32) `#define UI_HEADING_LEVELS`
  - `BUI_CHROME_FONT` (macro, line 127) `#define BUI_CHROME_FONT`
  - `BUI_CHROME_FONT_SIZE` (macro, line 128) `#define BUI_CHROME_FONT_SIZE`
  - `BUI_URL_FONT_SIZE` (macro, line 129) `#define BUI_URL_FONT_SIZE`
- Depends on: `include/chrome_layout.h`, `include/freedom_config.h`
- Imported by: `gui/browser_ui.c`, `gui/bui_chrome.c`, `gui/bui_mask_img.c`, `gui/bui_theme.c`

## gui/bui_chrome.c
- Doc: tab_path: void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double r) {...
- Layer: utility
- Language: c
- Symbols:
  - `bui_round_rect` (function, line 35) `void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double r)`
  - `tab_path` (function, line 48) `static void tab_path(cairo_t *cr, chl_rect t, double r)`
  - `set_rgba` (function, line 57) `static void set_rgba(cairo_t *cr, ui_rgb c, double a)`
  - `bui_chrome_font` (function, line 61) `void bui_chrome_font(cairo_t *cr, double size)`
  - `rcx` (function, line 66) `static double rcx(chl_rect r)`
  - `rcy` (function, line 67) `static double rcy(chl_rect r)`
  - `icon_stroke` (function, line 69) `static void icon_stroke(cairo_t *cr)`
  - `icon_arrow` (function, line 76) `static void icon_arrow(cairo_t *cr, double cx, double cy, int dir)`
  - `icon_reload` (function, line 87) `static void icon_reload(cairo_t *cr, double cx, double cy)`
  - `icon_menu` (function, line 99) `static void icon_menu(cairo_t *cr, double cx, double cy)`
  - `icon_cross` (function, line 107) `static void icon_cross(cairo_t *cr, double cx, double cy, double h)`
  - `icon_plus` (function, line 115) `static void icon_plus(cairo_t *cr, double cx, double cy, double h)`
  - `spinner` (function, line 123) `static void spinner(cairo_t *cr, ui_rgb c, double cx, double cy, double phase)`
  - `glyph_shield` (function, line 137) `static void glyph_shield(cairo_t *cr, double cx, double cy, int check, int fill)`
  - `glyph_lock` (function, line 161) `static void glyph_lock(cairo_t *cr, double cx, double cy)`
  - `glyph_warning` (function, line 173) `static void glyph_warning(cairo_t *cr, double cx, double cy)`
  - `glyph_overlay` (function, line 192) `static void glyph_overlay(cairo_t *cr, double cx, double cy)`
  - `glyph_page` (function, line 200) `static void glyph_page(cairo_t *cr, double cx, double cy)`
  - `glyph_info` (function, line 210) `static void glyph_info(cairo_t *cr, double cx, double cy)`
  - `paint_identity` (function, line 220) `static void paint_identity(cairo_t *cr, const bui_chrome_view *v)`
  - `utf8_next` (function, line 271) `static size_t utf8_next(const char *s, size_t n, size_t i)`
  - `text_w` (function, line 278) `static double text_w(cairo_t *cr, const char *s, size_t n)`
  - `show_n` (function, line 288) `static void show_n(cairo_t *cr, const char *s, size_t n)`
  - `bui_url_text_x` (function, line 296) `double bui_url_text_x(const bui_chrome_view *v, cairo_t *cr, double *shift)`
  - `bui_url_index_at` (function, line 310) `size_t bui_url_index_at(cairo_t *cr, const bui_chrome_view *v, double x)`
  - `paint_url` (function, line 347) `static void paint_url(cairo_t *cr, const bui_chrome_view *v)`
  - `round_button` (function, line 419) `static void round_button(cairo_t *cr, const bui_chrome_view *v, chl_rect r, chl_part part,
      ...`
  - `paint_toolbar` (function, line 430) `static void paint_toolbar(cairo_t *cr, const bui_chrome_view *v)`
  - `tab_title` (function, line 449) `static void tab_title(cairo_t *cr, const char *s, ui_rgb c, double alpha,
                      d...`
  - `paint_tabstrip` (function, line 480) `static void paint_tabstrip(cairo_t *cr, const bui_chrome_view *v)`
  - `bui_paint_chrome` (function, line 569) `void bui_paint_chrome(cairo_t *cr, const bui_chrome_view *v)`
  - `paint_find_field` (function, line 586) `static void paint_find_field(cairo_t *cr, const bui_find_view *v)`
  - `find_button` (function, line 635) `static void find_button(cairo_t *cr, const bui_find_view *v, chl_rect r, chl_find_part part,
    ...`
  - `icon_chevron` (function, line 647) `static void icon_chevron(cairo_t *cr, double cx, double cy, int dir)`
  - `bui_paint_findbar` (function, line 655) `void bui_paint_findbar(cairo_t *cr, const bui_find_view *v)`
  - `BUI_TWO_PI` (macro, line 18) `#define BUI_TWO_PI`
  - `BUI_ICON_LINE` (macro, line 19) `#define BUI_ICON_LINE`
  - `BUI_TAB_RADIUS` (macro, line 20) `#define BUI_TAB_RADIUS`
  - `BUI_PILL_RADIUS` (macro, line 21) `#define BUI_PILL_RADIUS`
  - `BUI_TAB_PAD` (macro, line 22) `#define BUI_TAB_PAD`
  - `BUI_TAB_FADE` (macro, line 23) `#define BUI_TAB_FADE`
  - `BUI_SPINNER_R` (macro, line 24) `#define BUI_SPINNER_R`
  - `BUI_STOP_HALF` (macro, line 25) `#define BUI_STOP_HALF`
  - `BUI_URL_TEXT_PAD` (macro, line 26) `#define BUI_URL_TEXT_PAD`
  - `BUI_URL_END_PAD` (macro, line 27) `#define BUI_URL_END_PAD`
  - `BUI_FOCUS_RING` (macro, line 28) `#define BUI_FOCUS_RING`
  - `BUI_INACTIVE_TEXT` (macro, line 29) `#define BUI_INACTIVE_TEXT`
  - `BUI_DISABLED` (macro, line 30) `#define BUI_DISABLED`
  - `BUI_URL_MEASURE` (macro, line 31) `#define BUI_URL_MEASURE`
- Depends on: `gui/browser_ui_internal.h`

## gui/bui_mask_img.c
- Doc: bui_mask_img -- paints a mask-image: url() layer into a mask surface.
- Layer: utility
- Language: c
- Symbols:
  - `bui_paint_mask_image` (function, line 17) `int bui_paint_mask_image(cairo_t *c, cairo_surface_t *img, int nat_w, int nat_h,
                ...`
- Depends on: `gui/browser_ui_internal.h`, `include/box_style.h`, `include/css.h`

## gui/bui_theme.c
- Doc: ui_theme_default: bui_theme — presentation palettes for the Wayland/Cairo GUI.
- Layer: utility
- Language: c
- Symbols:
  - `ui_theme_default` (function, line 15) `ui_theme ui_theme_default(void)`
  - `ui_theme_dark` (function, line 91) `ui_theme ui_theme_dark(void)`
  - `ui_theme_sepia` (function, line 137) `ui_theme ui_theme_sepia(void)`
  - `ui_theme_for` (function, line 189) `ui_theme ui_theme_for(int mode)`
  - `rgb_from_packed` (function, line 198) `ui_rgb rgb_from_packed(int packed)`
  - `set_rgb` (function, line 203) `void set_rgb(cairo_t *cr, ui_rgb c)`
- Depends on: `gui/browser_ui_internal.h`, `include/css.h`, `include/css_color.h`

## gui/freedom_view.c
- Layer: presentation
- Language: c
- Symbols:
  - `main` (function, line 37) `int main(int argc, char **argv)`
  - `_POSIX_C_SOURCE` (macro, line 10) `#define _POSIX_C_SOURCE`
- Depends on: `include/html_parse.h`, `include/ui.h`


Next: [KB_gui_p3.md](KB_gui_p3.md)
