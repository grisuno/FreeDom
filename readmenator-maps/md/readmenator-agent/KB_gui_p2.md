# Subsystem: gui (page 2 of 2)
Previous: [KB_gui.md](KB_gui.md)

## gui/browser_ui.c (continued)
  - `ensure_download_dir` (function, line 15688) `static int ensure_download_dir(char *out, size_t outsz)`
  - `write_file_atomic` (function, line 15703) `static int write_file_atomic(const char *path, const void *bytes, size_t len)`
  - `save_download` (function, line 15725) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...`
  - `save_current_page` (function, line 15758) `static void save_current_page(browser_window *w)`
  - `deliver_fetch_result` (function, line 15768) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
  - `drain_fetch_results` (function, line 15822) `static void drain_fetch_results(browser_window *w)`
  - `toggle_reader` (function, line 15927) `static void toggle_reader(browser_window *w)`
  - `menu_item_checked` (function, line 15938) `static int menu_item_checked(const browser_window *w, size_t i)`
  - `menu_item_toggle` (function, line 15960) `static void menu_item_toggle(browser_window *w, size_t i)`
  - `draw_clock` (function, line 16075) `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...`
  - `draw_hamburger` (function, line 16087) `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_reload` (function, line 16103) `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)`
  - `draw_menu` (function, line 16125) `static void draw_menu(cairo_t *cr, browser_window *w)`
  - `draw_hover_url` (function, line 16236) `static double draw_hover_url(cairo_t *cr, browser_window *w)`
  - `draw_toast` (function, line 16268) `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)`
  - `draw_tabstrip` (function, line 16298) `static void draw_tabstrip(cairo_t *cr, browser_window *w)`
  - `draw_omnibox` (function, line 16353) `static void draw_omnibox(cairo_t *cr, browser_window *w)`
  - `paint` (function, line 16387) `static void paint(browser_window *w)`
  - `redraw` (function, line 16631) `static void redraw(browser_window *w)`
  - `wm_base_ping` (function, line 16662) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 16668) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 16676) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `wl_array_for_each` (function, line 16692) `wl_array_for_each(st, states)`
  - `toplevel_close` (function, line 16698) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 16707) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `set_cursor` (function, line 16719) `static void set_cursor(browser_window *w, int cur_kind)`
  - `element` (function, line 16749) `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...`
  - `fbw_split_y` (function, line 16828) `static double fbw_split_y(const freebug_window *fb)`
  - `freebug_ensure_buffer` (function, line 16837) `static int freebug_ensure_buffer(freebug_window *fb)`
  - `fbw_level_rgb` (function, line 16864) `static void fbw_level_rgb(int level, double *r, double *g, double *b)`
  - `fbw_console_lines` (function, line 16875) `static size_t fbw_console_lines(const fb_buffer *log, int filter)`
  - `fbw_cell_w` (function, line 16890) `static double fbw_cell_w(cairo_t *cr)`
  - `fbw_text_lines` (function, line 16896) `static size_t fbw_text_lines(const char *t)`
  - `fbw_arg_hint` (function, line 16903) `static const char *fbw_arg_hint(int which)`
  - `fbw_paint_tabs` (function, line 16914) `static void fbw_paint_tabs(cairo_t *cr, const freebug_window *fb)`
  - `fbw_paint_pane` (function, line 16947) `static void fbw_paint_pane(cairo_t *cr, const freebug_window *fb, double y, double split_y)`
  - `freebug_paint` (function, line 16978) `static void freebug_paint(freebug_window *fb)`
  - `freebug_redraw_fb` (function, line 17190) `static void freebug_redraw_fb(freebug_window *fb)`
  - `freebug_redraw` (function, line 17199) `static void freebug_redraw(browser_window *w)`
  - `freebug_hide` (function, line 17203) `static void freebug_hide(browser_window *w)`
  - `fbw_xdg_surface_configure` (function, line 17219) `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `fbw_toplevel_configure` (function, line 17227) `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...`
  - `fbw_toplevel_close` (function, line 17236) `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)`
  - `freebug_show` (function, line 17246) `static void freebug_show(browser_window *w)`
  - `freebug_toggle` (function, line 17276) `static void freebug_toggle(browser_window *w)`
  - `freebug_destroy` (function, line 17281) `static void freebug_destroy(browser_window *w)`
  - `freebug_owns_surface` (function, line 17290) `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)`
  - `freebug_is_open` (function, line 17294) `static int freebug_is_open(const browser_window *w)`
  - `freebug_repl_worker` (function, line 17301) `static tab *freebug_repl_worker(browser_window *w)`
  - `freebug_pane_refresh` (function, line 17343) `static void freebug_pane_refresh(browser_window *w)`
  - `freebug_set_tab` (function, line 17380) `static void freebug_set_tab(browser_window *w, int which)`
  - `freebug_panes_invalidate` (function, line 17398) `static void freebug_panes_invalidate(browser_window *w)`
  - `freebug_eval` (function, line 17405) `static void freebug_eval(browser_window *w)`
  - `freebug_set_editor` (function, line 17448) `static void freebug_set_editor(freebug_window *fb, const char *s)`
  - `freebug_complete` (function, line 17456) `static void freebug_complete(browser_window *w)`
  - `freebug_handle_key` (function, line 17486) `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...`
  - `freebug_pointer_button` (function, line 17539) `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...`
  - `freebug_pointer_motion` (function, line 17568) `static void freebug_pointer_motion(browser_window *w)`
  - `freebug_pointer_axis` (function, line 17590) `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)`
  - `ptr_enter` (function, line 17608) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
  - `ptr_leave` (function, line 17626) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
  - `ptr_motion` (function, line 17643) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
  - `load_current` (function, line 17668) `static void load_current(browser_window *w)`
  - `go_omnibox` (function, line 17681) `static void go_omnibox(browser_window *w)`
  - `ptr_button` (function, line 17726) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
  - `scroll_line_px` (function, line 17973) `static double scroll_line_px(const browser_window *w)`
  - `ptr_axis` (function, line 17977) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
  - `ptr_frame` (function, line 18001) `static void ptr_frame(void *d, struct wl_pointer *p)`
  - `mime_is_text` (function, line 18017) `static int mime_is_text(const char *mime)`
  - `data_offer_source_actions` (function, line 18035) `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_offer_action` (function, line 18038) `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_device_data_offer` (function, line 18048) `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...`
  - `data_device_selection` (function, line 18060) `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...`
  - `data_device_enter` (function, line 18079) `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...`
  - `data_device_leave` (function, line 18084) `static void data_device_leave(void *d, struct wl_data_device *dev)`
  - `data_device_motion` (function, line 18085) `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...`
  - `data_device_drop` (function, line 18089) `static void data_device_drop(void *d, struct wl_data_device *dev)`
  - `data_source_cancelled` (function, line 18100) `static void data_source_cancelled(void *data, struct wl_data_source *src)`
  - `data_source_send` (function, line 18106) `static void data_source_send(void *data, struct wl_data_source *src,
                            ...`
  - `data_source_target` (function, line 18119) `static void data_source_target(void *d, struct wl_data_source *s, const char *m)`
  - `freebug_copy_console` (function, line 18131) `static void freebug_copy_console(browser_window *w)`
  - `insert_pasted_text` (function, line 18199) `static void insert_pasted_text(browser_window *w, const char *text, size_t len)`
  - `clipboard_copy` (function, line 18263) `static void clipboard_copy(browser_window *w)`
  - `keyboard_keymap` (function, line 18311) `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...`
  - `keyboard_enter` (function, line 18332) `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...`
  - `keyboard_leave` (function, line 18339) `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)`
  - `key_sym_to_js_key` (function, line 18347) `static const char *key_sym_to_js_key(xkb_keysym_t sym)`
  - `key_sym_to_keycode` (function, line 18373) `static int key_sym_to_keycode(xkb_keysym_t sym)`
  - `dispatch_js_event` (function, line 18398) `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...`
  - `handle_key_press` (function, line 18456) `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...`
  - `key_is_repeatable` (function, line 18792) `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)`
  - `key_repeat_arm` (function, line 18808) `static void key_repeat_arm(browser_window *w, uint32_t key)`
  - `key_repeat_stop` (function, line 18821) `static void key_repeat_stop(browser_window *w)`
  - `key_repeat_fire` (function, line 18832) `static void key_repeat_fire(browser_window *w)`
  - `keyboard_key` (function, line 18846) `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...`
  - `keyboard_modifiers` (function, line 18886) `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...`
  - `keyboard_repeat_info` (function, line 18895) `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)`
  - `seat_caps` (function, line 18914) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
  - `seat_name` (function, line 18925) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
  - `registry_global` (function, line 18932) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
  - `registry_remove` (function, line 18952) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
  - `gui_is_idle` (function, line 18965) `static int gui_is_idle(const browser_window *w)`
  - `gui_timing_step` (function, line 18976) `static int gui_timing_step(browser_window *w, uint64_t now)`
  - `startup_abort_release` (function, line 18993) `static void startup_abort_release(browser_window *w)`
  - `ui_run_browser` (function, line 19002) `ui_status ui_run_browser(const char *start_url)`
  - `cost` (function, line 19462) `* measured cost (floor 33 ms = the existing ~30 fps ceiling):
             * cheap pages paint at...`
  - `offset` (function, line 179) `* offset (labels and the flag live in one place, no magic indices);`
  - `fields` (function, line 291) `* fields (so the 200+ render/event call sites stay unchanged);`
  - `delay` (function, line 407) `* timer delay (tab_page.next_timer_ms);`
  - `main` (function, line 553) `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never...`
  - `proxy` (function, line 1040) `* and enable each proxy ("1" => the default port);`
  - `video_feeder_thread` (function, line 1096) `static void *video_feeder_thread(void *arg);`
  - `box_pad_px` (function, line 1199) `static double box_pad_px(int px_val, int pct_pm, double cb_w);`
  - `page_trusted` (function, line 1528) `static int page_trusted(const browser_window *w);`
  - `only` (function, line 1619) `* Trusted pages only (untrusted CSS is still applied by the worker, but its * fonts never reach the parent...`
  - `hb_is_allowlisted` (function, line 1756) `&& hb_is_allowlisted(w->hosts, ihost);`
  - `proceed` (function, line 1802) `* may proceed (cfg and pr->allowlisted are then set);`
  - `secure_fetch` (function, line 2056) `* through secure_fetch (Zero Trust);`
  - `string` (function, line 2215) `* or an empty string (unset, blocked, or off by caps.images), so there is no * decision to re-check, unlike...`
  - `do_load` (function, line 2255) `static void do_load(browser_window *w, const char *url);`
  - `tab_new` (function, line 2260) `static void tab_new(browser_window *w, const char *url);`
  - `toggle` (function, line 2270) `* No network: a capability toggle (images/CSS) re-renders from cache. Does nothing * when there is no cached source...`
  - `stylesheets` (function, line 2426) `* External stylesheets (Hito 27) follow the author-styles opt-in -- or the * trusted-host doctrine (Hito 28)...`
  - `body` (function, line 2459) `* every served CSS body (serial and pool paths alike). */ font_stash_reset(w);`
  - `ALIVE` (function, line 2566) `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or...`
  - `resolve` (function, line 2816) `* origin so its relative references and local images resolve (confined to the * document's directory) -- a local...`
  - `smaller` (function, line 3419) `* size when the content is smaller (height) or wider (min-width);`
  - `HarfBuzz` (function, line 3862) `* descriptor via HarfBuzz (text_shape);`
  - `produced` (function, line 4371) `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target...`
  - `line` (function, line 4470) `* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the...`
  - `box_path4` (function, line 4671) `static void box_path4(cairo_t *cr, double x, double y, double w, double h, const double *rc);`
  - `block_leaves_flow` (function, line 4753) `static int block_leaves_flow(const rd_doc *doc, const rd_block *bk);`
  - `container` (function, line 5508) `* were the container (github's tab pill). */ int item = item_at_level(doc, rd_at(doc, k), cid);`
  - `way` (function, line 5608) `* intrinsic box either way (it does not wrap below its own size). */ static int block_leaves_flow(const rd_doc *doc...`
  - `layout` (function, line 5849) `* hypothetical size in the real layout (Flexbox 9.2.3). */ if (ibd != NULL && ibd->box_min_w > 0) base =...`
  - `close_all_boxes` (function, line 5933) `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);`
  - `deepest_open_on_path` (function, line 5961) `static int deepest_open_on_path(const rc_state *outer, const rd_doc *doc, int block_id);`
  - `TABLE` (function, line 6076) `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all...`
  - `band_shared_box` (function, line 6186) `static int band_shared_box(const rd_doc *doc, const rc_state *s, size_t start, size_t end);`
  - `axis` (function, line 6331) `* differs: items stack on the vertical main axis (fx_column_place) and align on * the horizontal cross axis...`
  - `struct` (function, line 6530) `* struct (0 = auto);`
  - `descriptor` (function, line 6538) `* placement rides the nested descriptor (spec/grid_areas.md 6). */ int nbc = child_cont_at_level(doc, bk, cid);`
  - `builds` (function, line 6817) `* wraps beside it: the same band the top level builds (spec/float.md). */ const rd_block *fk = rd_at(doc, k);`
  - `it` (function, line 6879) `* with anything: that margin is the gap before it (a heading's * `margin-bottom` above a `display:grid` list). */...`
  - `flow` (function, line 6903) `* it collapse their vertical margins with each other exactly as in * the main flow (CSS 2.1 8.3.1), and none escapes...`
  - `own` (function, line 6935) `* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and...`
  - `items` (function, line 7016) `* items (Flexbox 4.2);`
  - `multicol_fragment` (function, line 7181) `static double multicol_fragment(rc_layout *L, const rc_open_box *ob, double content_bottom);`
  - `behind` (function, line 7471) `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old...`
  - `treatment` (function, line 7972) `* block treatment (shrink-wrapped and placed by text-align), which is what a * standalone centred call-to-action...`
  - `rule` (function, line 8181) `* wrapper keeps the old rule (opened with the float's own column). */ const pv_box_def *wd = rd_box_at(doc...`
  - `context` (function, line 8196) `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document...`
  - `width` (function, line 8557) `* box width (an inline-block icon `width:12px` inside the float) is * not the float's. */ double t =...`
  - `x` (function, line 8606) `* reported x is already the BORDER x (the §7c.2 rule);`
  - `chain` (function, line 9353) `* chain (the box that left the normal flow at this pen position);`
  - `anchor` (function, line 9468) `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is...`
  - `key` (function, line 9537) `* founders splits by key (stories, rail, footer nav each take * their column);`
  - `have` (function, line 9565) `* as they always have (spec/float.md §6b.3). The line still open beside * the previous float is committed first, at...`
  - `standalone` (function, line 9586) `* must not be treated as standalone (which would flush that line and give * the element a row of its own -- R7). */...`
  - `margin` (function, line 9980) `* own left margin (the margin box starts at the anchor point), a right- * anchored one ends at it. Same for the...`
  - `rd_build` (function, line 10667) `* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr...`
  - `descriptors` (function, line 10924) `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection —...`
  - `again` (function, line 11005) `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one...`
  - `blocking` (function, line 11293) `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);`
  - `rect` (function, line 11646) `* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops...`
  - `layer` (function, line 11955) `* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the...`
  - `convention` (function, line 12111) `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE || style...`
  - `row_owner_block_id` (function, line 12261) `static int row_owner_block_id(const rc_layout *L, const rc_row *r);`
  - `exactly` (function, line 12307) `* the resolved size exactly (like the SVG path above): routing through * paint_image_row would re-resolve a % width...`
  - `bg` (function, line 12405) `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);`
  - `rows` (function, line 12627) `* RC_IMAGE rows (see its declaration);`
  - `made` (function, line 13185) `* its zero channels made (255,255,255,alpha 0) -- an invalid * premultiplied value Cairo composites as ADDITIVE...`
  - `the` (function, line 13289) `* the (already filtered) group with the shadow color, blur it, and * paint it under the group at the declared offset...`
  - `fill` (function, line 13473) `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in...`
  - `overflow` (function, line 13533) `* adding two of them in int was signed overflow (UB, found by UBSan). */ double ox = left + bx->x +...`
  - `compositing` (function, line 13576) `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context...`
  - `once` (function, line 14289) `* box the layout never placed loads at once (fail open);`
  - `origin` (function, line 14922) `* top_url is the page origin (https or file://);`
  - `in` (function, line 15000) `* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);`
  - `sf_ws_url_check` (function, line 15418) `&& sf_ws_url_check(op->data) == SF_OK && rp_host_of(op->data, host, sizeof host) == 0 &&...`
  - `presentation` (function, line 15958) `* affect presentation (a repaint, which re-runs layout, suffices);`
  - `resizes` (function, line 16684) `* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);`
  - `down` (function, line 17602) `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void...`
  - `loop` (function, line 18190) `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately...`
  - `saving` (function, line 19021) `* disables saving (never clobber);`
  - `redraws` (function, line 19114) `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A...`
  - `moves` (function, line 19127) `* client that stops reading its socket while the pointer moves (spec/wl_guard.md). */ if...`
  - `_GNU_SOURCE` (macro, line 12) `#define _GNU_SOURCE`
  - `UI_TOOLBAR_H` (macro, line 96) `#define UI_TOOLBAR_H`
  - `UI_TITLEBAR_H` (macro, line 97) `#define UI_TITLEBAR_H`
  - `UI_TABBAR_H` (macro, line 98) `#define UI_TABBAR_H`
  - `UI_TAB_MIN_W` (macro, line 99) `#define UI_TAB_MIN_W`
  - `UI_TAB_MAX_W` (macro, line 100) `#define UI_TAB_MAX_W`
  - `UI_TAB_NEW_W` (macro, line 101) `#define UI_TAB_NEW_W`
  - `UI_TAB_CLOSE_W` (macro, line 102) `#define UI_TAB_CLOSE_W`
  - `UI_BTN_W` (macro, line 103) `#define UI_BTN_W`
  - `UI_WIN_BTN_W` (macro, line 104) `#define UI_WIN_BTN_W`
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
  - `UI_CHECK_SZ` (macro, line 129) `#define UI_CHECK_SZ`
  - `UI_MENU_LABEL_H` (macro, line 130) `#define UI_MENU_LABEL_H`
  - `UI_MENU_INPUT_H` (macro, line 131) `#define UI_MENU_INPUT_H`
  - `UI_HAMBURGER_W` (macro, line 132) `#define UI_HAMBURGER_W`
  - `UI_HAMBURGER_GAP` (macro, line 133) `#define UI_HAMBURGER_GAP`
  - `UI_CURSOR_SIZE` (macro, line 134) `#define UI_CURSOR_SIZE`
  - `UI_TOAST_PAD` (macro, line 135) `#define UI_TOAST_PAD`
  - `OMNI_MAX_SUGG` (macro, line 136) `#define OMNI_MAX_SUGG`
  - `UI_OMNI_ROW_H` (macro, line 137) `#define UI_OMNI_ROW_H`
  - `UI_TWO_PI` (macro, line 138) `#define UI_TWO_PI`
  - `UI_INPUT_PAD` (macro, line 142) `#define UI_INPUT_PAD`
  - `UI_CONTROL_FONT` (macro, line 145) `#define UI_CONTROL_FONT`
  - `UI_INPUT_MEASURE_W` (macro, line 151) `#define UI_INPUT_MEASURE_W`
  - `UI_INPUT_WIDTH` (macro, line 152) `#define UI_INPUT_WIDTH`
  - `UI_BUTTON_HPAD` (macro, line 153) `#define UI_BUTTON_HPAD`
  - `UI_FORM_FIELDS_MAX` (macro, line 154) `#define UI_FORM_FIELDS_MAX`
  - `UI_UNDERLINE_OFFSET` (macro, line 159) `#define UI_UNDERLINE_OFFSET`
  - `UI_UNDERLINE_THICK` (macro, line 160) `#define UI_UNDERLINE_THICK`
  - `UI_STRIKE_OFFSET` (macro, line 161) `#define UI_STRIKE_OFFSET`
  - `UI_OVERLINE_OFFSET` (macro, line 162) `#define UI_OVERLINE_OFFSET`
  - `UI_SLICE_MAX` (macro, line 166) `#define UI_SLICE_MAX`
  - `UI_MENU_COUNT` (macro, line 227) `#define UI_MENU_COUNT`
  - `UI_IMAGE_MAX_BODY` (macro, line 245) `#define UI_IMAGE_MAX_BODY`
  - `UI_MAX_TABS` (macro, line 287) `#define UI_MAX_TABS`
  - `UI_READER_COLUMN_W` (macro, line 642) `#define UI_READER_COLUMN_W`
  - `FONT_STASH_MAX_SHEETS` (macro, line 1596) `#define FONT_STASH_MAX_SHEETS`
  - `FONT_STASH_MAX_BYTES` (macro, line 1597) `#define FONT_STASH_MAX_BYTES`
  - `JS_NAV_MAX` (macro, line 2265) `#define JS_NAV_MAX`
  - `HIST_STEP_DEPTH_MAX` (macro, line 2267) `#define HIST_STEP_DEPTH_MAX`
  - `JS_TICKS_PER_LOAD` (macro, line 2391) `#define JS_TICKS_PER_LOAD`
  - `UI_RELOAD_X` (macro, line 3215) `#define UI_RELOAD_X`
  - `RC_IBOX_MAX` (macro, line 3586) `#define RC_IBOX_MAX`
  - `RC_BOX_STACK_MAX` (macro, line 3588) `#define RC_BOX_STACK_MAX`
  - `RC_FLOAT_MAX` (macro, line 3592) `#define RC_FLOAT_MAX`
  - `RC_FLOAT_FIT_MIN` (macro, line 3599) `#define RC_FLOAT_FIT_MIN`
  - `FLEX_MEASURE_W` (macro, line 5550) `#define FLEX_MEASURE_W`
  - `FLEX_MIN_MEASURE_W` (macro, line 5555) `#define FLEX_MIN_MEASURE_W`
  - `BALANCE_MAX_LINES` (macro, line 5678) `#define BALANCE_MAX_LINES`
  - `RC_COL_FREE_MAX` (macro, line 7197) `#define RC_COL_FREE_MAX`
  - `RC_MAX_OUT_OF_FLOW` (macro, line 8061) `#define RC_MAX_OUT_OF_FLOW`
  - `RC_DEFER_COLS` (macro, line 8231) `#define RC_DEFER_COLS`
  - `RC_DEFER_RANGES` (macro, line 8232) `#define RC_DEFER_RANGES`
  - `RC_DEFER_BAND_RUNS` (macro, line 8314) `#define RC_DEFER_BAND_RUNS`
  - `BUI_CONIC_SLICES` (macro, line 11719) `#define BUI_CONIC_SLICES`
  - `ROW_PAINT_ALL` (macro, line 12331) `#define ROW_PAINT_ALL`
  - `ROW_PAINT_BAND` (macro, line 12332) `#define ROW_PAINT_BAND`
  - `ROW_PAINT_CONTENT` (macro, line 12333) `#define ROW_PAINT_CONTENT`
  - `OV_MAX_DEPTH` (macro, line 12554) `#define OV_MAX_DEPTH`
  - `H2R` (macro, line 13241) `#define H2R(p,q,t)`
  - `UI_LAZY_PER_PASS` (macro, line 14220) `#define UI_LAZY_PER_PASS`
  - `UI_LAZY_PASSES` (macro, line 14221) `#define UI_LAZY_PASSES`
  - `PDF_PAGE_W` (macro, line 14456) `#define PDF_PAGE_W`
  - `PDF_PAGE_H` (macro, line 14457) `#define PDF_PAGE_H`
  - `PDF_MARGIN` (macro, line 14458) `#define PDF_MARGIN`
  - `PNG_PAGE_W` (macro, line 14623) `#define PNG_PAGE_W`
  - `PNG_MARGIN` (macro, line 14647) `#define PNG_MARGIN`
  - `PNG_MAX_H` (macro, line 14648) `#define PNG_MAX_H`
  - `FBW_W` (macro, line 16785) `#define FBW_W`
  - `FBW_H` (macro, line 16786) `#define FBW_H`
  - `FBW_HEADER` (macro, line 16787) `#define FBW_HEADER`
  - `FBW_TABBAR` (macro, line 16788) `#define FBW_TABBAR`
  - `FBW_TOP` (macro, line 16789) `#define FBW_TOP`
  - `FBW_TAB_PAD` (macro, line 16790) `#define FBW_TAB_PAD`
  - `FBW_PAD` (macro, line 16791) `#define FBW_PAD`
  - `FBW_LINE` (macro, line 16792) `#define FBW_LINE`
  - `FBW_GUTTER` (macro, line 16793) `#define FBW_GUTTER`
  - `FBW_MIN_SPLIT` (macro, line 16794) `#define FBW_MIN_SPLIT`
  - `FBW_MAX_SPLIT` (macro, line 16795) `#define FBW_MAX_SPLIT`
  - `FBW_COPY_BTN_W` (macro, line 16796) `#define FBW_COPY_BTN_W`
  - `FBW_COPY_BTN_H` (macro, line 16797) `#define FBW_COPY_BTN_H`
  - `TIMING_QUIET_MS` (macro, line 18975) `#define TIMING_QUIET_MS`
- Depends on: `gui/browser_ui_internal.h`, `include/block_flow.h`, `include/box_blur.h`, `include/box_style.h`, `include/box_tree.h`, `include/browser.h`, `include/cached_fetch.h`, `include/compositor.h`, `include/css.h`, `include/css_color.h`, `include/css_gradient.h`, `include/css_mask.h`, `include/css_values.h`, `include/data_url.h`, `include/download.h`, `include/fb_cmdline.h`, `include/fb_panes.h`, `include/form.h`, `include/frame_clock.h`, `include/frame_host.h`, `include/freebug.h`, `include/hls.h`, `include/host_conf.h`, `include/hostblock.h`, `include/hostedit.h`, `include/identity.h`, `include/image_decode.h`, `include/interp.h`, `include/js_policy.h`, `include/lazy_load.h`, `include/link_nav.h`, `include/media_decoder.h`, `include/net_realm.h`, `include/pdf_export.h`, `include/prefetch.h`, `include/prefs.h`, `include/profile.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/shm_slots.h`, `include/svg_paint.h`, `include/svg_render.h`, `include/tab.h`, `include/text_case.h`, `include/text_shape.h`, `include/textfield.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/web_storage.h`, `include/webcaps.h`, `include/webfont.h`, `include/webfont_load.h`, `include/wl_guard.h`, `include/ws_hub.h`, `include/zoom.h`

## gui/browser_ui_internal.h
- Doc: ui_theme_mode: ui_rgb button_text; ui_rgb menu_bg; ui_rgb menu_border; ui_rgb menu_text; ui_rgb...
- Layer: presentation
- Language: h
- Symbols:
  - `ui_rgb` (struct, line 41)
  - `ui_theme` (struct, line 43)
  - `ui_theme_mode` (enum, line 92)
  - `b` (type_alias, line 40) `typedef struct ui_rgb { double r, g, b;`
  - `body_font` (type_alias, line 42) `typedef struct ui_theme { double body_font;`
  - `set_rgb` (function, line 105) `void set_rgb(cairo_t *cr, ui_rgb c);`
  - `FREEDOM_BROWSER_UI_INTERNAL_H` (macro, line 2) `#define FREEDOM_BROWSER_UI_INTERNAL_H`
  - `UI_FONT_SIZE` (macro, line 30) `#define UI_FONT_SIZE`
  - `UI_TEXT_MARGIN` (macro, line 31) `#define UI_TEXT_MARGIN`
  - `UI_HEADING_LEVELS` (macro, line 32) `#define UI_HEADING_LEVELS`
- Depends on: `include/freedom_config.h`
- Imported by: `gui/browser_ui.c`, `gui/bui_theme.c`

## gui/bui_theme.c
- Doc: ui_theme_default: bui_theme — presentation palettes for the Wayland/Cairo GUI.
- Layer: utility
- Language: c
- Symbols:
  - `ui_theme_default` (function, line 15) `ui_theme ui_theme_default(void)`
  - `ui_theme_dark` (function, line 78) `ui_theme ui_theme_dark(void)`
  - `ui_theme_sepia` (function, line 123) `ui_theme ui_theme_sepia(void)`
  - `ui_theme_for` (function, line 165) `ui_theme ui_theme_for(int mode)`
  - `rgb_from_packed` (function, line 174) `ui_rgb rgb_from_packed(int packed)`
  - `set_rgb` (function, line 179) `void set_rgb(cairo_t *cr, ui_rgb c)`
- Depends on: `gui/browser_ui_internal.h`, `include/css.h`, `include/css_color.h`

## gui/freedom_view.c
- Layer: presentation
- Language: c
- Symbols:
  - `main` (function, line 37) `int main(int argc, char **argv)`
  - `_POSIX_C_SOURCE` (macro, line 10) `#define _POSIX_C_SOURCE`
- Depends on: `include/html_parse.h`, `include/ui.h`

## gui/svg_paint.c
- Doc: svg_paint — Cairo back end for the shapes svg_render extracted.
- Layer: utility
- Language: c
- Symbols:
  - `svp_alpha` (function, line 31) `static double svp_alpha(int opacity, int paint_opacity)`
  - `svp_rect_path` (function, line 38) `static void svp_rect_path(cairo_t *cr, const sv_shape *sh)`
  - `svp_shape_path` (function, line 73) `static void svp_shape_path(cairo_t *cr, const sv_image *img, const sv_shape *sh)`
  - `svp_draw_text` (function, line 126) `static void svp_draw_text(cairo_t *cr, const sv_shape *sh, int current_rgb)`
  - `svp_draw` (function, line 139) `void svp_draw(cairo_t *cr, const sv_image *img,
              double x, double y, double w, doubl...`
- Depends on: `include/css_color.h`, `include/freedom_config.h`, `include/svg_paint.h`

## gui/ui_render.c
- Doc: sanitize_utf8_inplace: Rewrites s in place to well-formed UTF-8, replacing any byte that is not...
- Layer: presentation
- Language: c
- Symbols:
  - `ui_window` (struct, line 67)
  - `sanitize_utf8_inplace` (function, line 39) `static void sanitize_utf8_inplace(char *s)`
  - `button_rects` (function, line 107) `static void button_rects(const ui_window *w, double *min_x, double *max_x, double *close_x)`
  - `buffer_release` (function, line 115) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
  - `destroy_buffer` (function, line 122) `static void destroy_buffer(ui_window *w)`
  - `ensure_buffer` (function, line 128) `static int ensure_buffer(ui_window *w)`
  - `paint` (function, line 159) `static void paint(ui_window *w)`
  - `redraw` (function, line 245) `static void redraw(ui_window *w)`
  - `wm_base_ping` (function, line 260) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
  - `xdg_surface_configure` (function, line 266) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
  - `toplevel_configure` (function, line 274) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
  - `toplevel_close` (function, line 283) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
  - `deco_configure` (function, line 294) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
  - `ptr_enter` (function, line 305) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
  - `ptr_leave` (function, line 312) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
  - `ptr_motion` (function, line 315) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
  - `ptr_button` (function, line 322) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
  - `ptr_axis` (function, line 344) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
  - `seat_caps` (function, line 367) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
  - `seat_name` (function, line 376) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
  - `registry_global` (function, line 383) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
  - `registry_remove` (function, line 401) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
  - `ui_run_text_view` (function, line 410) `ui_status ui_run_text_view(const char *title, const char *text, size_t text_len)`
  - `_GNU_SOURCE` (macro, line 10) `#define _GNU_SOURCE`
  - `UI_FONT_SIZE` (macro, line 28) `#define UI_FONT_SIZE`
  - `UI_MARGIN` (macro, line 29) `#define UI_MARGIN`
  - `UI_TITLEBAR_H` (macro, line 30) `#define UI_TITLEBAR_H`
  - `UI_BTN_W` (macro, line 31) `#define UI_BTN_W`
  - `UI_BTN_LEFT` (macro, line 32) `#define UI_BTN_LEFT`
- Depends on: `include/freedom_config.h`, `include/ui.h`

