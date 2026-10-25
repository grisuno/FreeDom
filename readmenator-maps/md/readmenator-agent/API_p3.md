# API (page 3 of 11)
Previous: [API_p2.md](API_p2.md)

## gui/browser_ui.c (continued)
- `resolve_box_cursor` (function) `gui/browser_ui.c:15060` `static int resolve_box_cursor(const rd_doc *doc, int block_id)` -- First non-unset author `cursor` on block_id's box or an ancestor (nearest wins, like the rest of the box-decoration...
- `box_pointer_events_none` (function) `gui/browser_ui.c:15074` `static int box_pointer_events_none(const rd_doc *doc, int block_id)` -- True when author `pointer-events: none` removes block_id's content from hit-testing (2026-07-10): the nearest box in...
- `cursor_at_point` (function) `gui/browser_ui.c:15090` `static int cursor_at_point(browser_window *w, double px, double py)` -- Returns the resolved author `cursor` (css_cursor) at (px, py), or CSS_CUR_UNSET when outside content / no box sets one.
- `node_at_point` (function) `gui/browser_ui.c:15155` `static dom_node_id node_at_point(browser_window *w, double px, double py)`
- `Firefox` (function) `gui/browser_ui.c:15163` `* on its face does in Firefox (spec/page_view.md, tanda 40). */
static const rd_block *submit_pro...`
- `frag_at_point` (function) `gui/browser_ui.c:15182` `static dom_node_id frag_at_point(browser_window *w, double px, double py,
                       ...`
- `reference` (function) `gui/browser_ui.c:15236` `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
- `set_page_url` (function) `gui/browser_ui.c:15255` `static void set_page_url(browser_window *w, const char *url)` -- Makes url the page's base (link/image resolution) without touching the cached * source: after pushState the...
- `ws_apply_ops` (function) `gui/browser_ui.c:15281` `static void ws_apply_ops(browser_window *w, const tab_page *page)` -- Opens/sends/closes the page's WebSockets (trusted host only; spec/js_dom.md 7f).
- `sf_ws_url_check` (function) `gui/browser_ui.c:15289` `&& sf_ws_url_check(op->data) == SF_OK && rp_host_of(op->data, host, sizeof host) == 0 && hb_check(w->hosts, host) !=...`
- `apply_history_ops` (function) `gui/browser_ui.c:15316` `static void apply_history_ops(browser_window *w, const tab_page *page)` -- Mirrors the page's history.pushState/replaceState into the session history (spec/js_dom.md 7e): same-document...
- `history_step` (function) `gui/browser_ui.c:15328` `static void history_step(browser_window *w, int steps)` -- Moves steps entries through the session history (negative = back).
- `apply_click_result` (function) `gui/browser_ui.c:15361` `static int apply_click_result(browser_window *w, tab_page *page)` -- Applies a click/event/timer result returned by the worker: rebuild the rendered document and refresh inputs/console...
- `on_tab_async` (function) `gui/browser_ui.c:15410` `static void on_tab_async(browser_window *w)` -- Completion of the tab's background job (tab_tick_async / tab_geometry_async).
- `gui_quiesce` (function) `gui/browser_ui.c:15423` `static void gui_quiesce(browser_window *w)`
- `memory` (function) `gui/browser_ui.c:15431` `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
- `GET` (function) `gui/browser_ui.c:15525` `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
- `ensure_download_dir` (function) `gui/browser_ui.c:15559` `static int ensure_download_dir(char *out, size_t outsz)` -- Builds ~/Downloads/freedom into out and creates both levels (best effort; an existing directory is fine).
- `write_file_atomic` (function) `gui/browser_ui.c:15574` `static int write_file_atomic(const char *path, const void *bytes, size_t len)` -- Writes len bytes to path with 0600 perms via a temp file + atomic rename (the disk_store convention): a crash...
- `save_download` (function) `gui/browser_ui.c:15596` `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...` -- Saves a fetched resource to ~/Downloads/freedom instead of rendering it.
- `save_current_page` (function) `gui/browser_ui.c:15629` `static void save_current_page(browser_window *w)` -- Ctrl+S: save the current page's cached source to ~/Downloads/freedom.
- `deliver_fetch_result` (function) `gui/browser_ui.c:15639` `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
- `drain_fetch_results` (function) `gui/browser_ui.c:15693` `static void drain_fetch_results(browser_window *w)` -- Drains every completed fetch the worker threads have posted (the read end is non-blocking; pointer-sized writes are...
- `toggle_reader` (function) `gui/browser_ui.c:15798` `static void toggle_reader(browser_window *w)` -- Toggles distraction-free (reader) mode and re-renders from cache (no network): the worker drops boilerplate, author...
- `menu_item_checked` (function) `gui/browser_ui.c:15809` `static int menu_item_checked(const browser_window *w, size_t i)` -- Toggles distraction-free (reader) mode and re-renders from cache (no network): the worker drops boilerplate, author...
- `presentation` (function) `gui/browser_ui.c:15829` `* affect presentation (a repaint, which re-runs layout, suffices);`
- `menu_item_toggle` (function) `gui/browser_ui.c:15831` `static void menu_item_toggle(browser_window *w, size_t i)` -- Toggles options-menu item i and applies its effect.
- `draw_clock` (function) `gui/browser_ui.c:15946` `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...` -- A small spinner meaning "busy".
- `draw_hamburger` (function) `gui/browser_ui.c:15958` `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)`
- `draw_reload` (function) `gui/browser_ui.c:15974` `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)` -- The reload button glyph: a ~300-degree circular arrow centred in a UI_BTN_W button starting at bx.
- `draw_menu` (function) `gui/browser_ui.c:15996` `static void draw_menu(cairo_t *cr, browser_window *w)` -- double a1 = a0 + UI_TWO_PI * 0.82;      /* leave a gap for the arrowhead cairo_new_sub_path(cr); cairo_arc(cr, cx...
- `draw_hover_url` (function) `gui/browser_ui.c:16107` `static double draw_hover_url(cairo_t *cr, browser_window *w)` -- Persistent bottom strip showing the target of the link under the pointer, so the user always knows where a click...
- `draw_toast` (function) `gui/browser_ui.c:16139` `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)` -- Draws the transient status toast (a banner near the bottom of the window), * raised by bottom_offset so it stacks...
- `draw_tabstrip` (function) `gui/browser_ui.c:16169` `static void draw_tabstrip(cairo_t *cr, browser_window *w)` -- Paints the tab strip: one cell per tab (the active one connected to the content background, the rest dimmed), each...
- `draw_omnibox` (function) `gui/browser_ui.c:16224` `static void draw_omnibox(cairo_t *cr, browser_window *w)` -- Omnibox autocomplete dropdown: a panel of favorite-host suggestions below the URL bar, drawn as an overlay (on top...
- `paint` (function) `gui/browser_ui.c:16258` `static void paint(browser_window *w)`
- `redraw` (function) `gui/browser_ui.c:16502` `static void redraw(browser_window *w)`
- `wm_base_ping` (function) `gui/browser_ui.c:16533` `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
- `xdg_surface_configure` (function) `gui/browser_ui.c:16539` `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
- `toplevel_configure` (function) `gui/browser_ui.c:16547` `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
- `resizes` (function) `gui/browser_ui.c:16555` `* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);`
- `wl_array_for_each` (function) `gui/browser_ui.c:16563` `wl_array_for_each(st, states)`
- `toplevel_close` (function) `gui/browser_ui.c:16569` `static void toplevel_close(void *data, struct xdg_toplevel *t)`
- `deco_configure` (function) `gui/browser_ui.c:16578` `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
- `set_cursor` (function) `gui/browser_ui.c:16590` `static void set_cursor(browser_window *w, int cur_kind)` -- Applies the appropriate Wayland cursor for the given CSS cursor value. * A no-op when no themed cursor is available...
- `element` (function) `gui/browser_ui.c:16620` `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...`
- `fbw_split_y` (function) `gui/browser_ui.c:16697` `static double fbw_split_y(const freebug_window *fb)` -- double split;          /* log-pane fraction of the body height double scroll;         /* log scroll offset (px) int...
- `freebug_ensure_buffer` (function) `gui/browser_ui.c:16706` `static int freebug_ensure_buffer(freebug_window *fb)`
- `fbw_level_rgb` (function) `gui/browser_ui.c:16733` `static void fbw_level_rgb(int level, double *r, double *g, double *b)` -- struct wl_shm_pool *pool = wl_shm_create_pool(fb->owner->shm, fd, (int32_t)size); fb->buffer =...
- `fbw_console_lines` (function) `gui/browser_ui.c:16744` `static size_t fbw_console_lines(const fb_buffer *log)` -- } /* Color for a console level (dark devtools palette). static void fbw_level_rgb(int level, double *r, double *g...
- `fbw_cell_w` (function) `gui/browser_ui.c:16758` `static double fbw_cell_w(cairo_t *cr)` -- static size_t fbw_console_lines(const fb_buffer *log) { size_t lines = 0; for (size_t i = 0; i <...
- `fbw_text_lines` (function) `gui/browser_ui.c:16764` `static size_t fbw_text_lines(const char *t)`
- `fbw_arg_hint` (function) `gui/browser_ui.c:16771` `static const char *fbw_arg_hint(int which)`
- `fbw_paint_tabs` (function) `gui/browser_ui.c:16782` `static void fbw_paint_tabs(cairo_t *cr, const freebug_window *fb)` -- return n; } static const char *fbw_arg_hint(int which) { switch (which) { case FBP_HTML:   return "CSS selector...
- `fbw_paint_pane` (function) `gui/browser_ui.c:16806` `static void fbw_paint_pane(cairo_t *cr, const freebug_window *fb, double y, double split_y)` -- cairo_set_source_rgb(cr, 0.11, 0.12, 0.14); cairo_rectangle(cr, x, FBW_HEADER + 2.0, w, FBW_TABBAR - 2.0)...
- `freebug_paint` (function) `gui/browser_ui.c:16837` `static void freebug_paint(freebug_window *fb)`
- `freebug_redraw_fb` (function) `gui/browser_ui.c:17044` `static void freebug_redraw_fb(freebug_window *fb)`
- `freebug_redraw` (function) `gui/browser_ui.c:17053` `static void freebug_redraw(browser_window *w)`
- `freebug_hide` (function) `gui/browser_ui.c:17057` `static void freebug_hide(browser_window *w)`
- `fbw_xdg_surface_configure` (function) `gui/browser_ui.c:17073` `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
- `fbw_toplevel_configure` (function) `gui/browser_ui.c:17081` `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...`
- `fbw_toplevel_close` (function) `gui/browser_ui.c:17090` `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)`
- `freebug_show` (function) `gui/browser_ui.c:17100` `static void freebug_show(browser_window *w)`
- `freebug_toggle` (function) `gui/browser_ui.c:17130` `static void freebug_toggle(browser_window *w)`
- `freebug_destroy` (function) `gui/browser_ui.c:17135` `static void freebug_destroy(browser_window *w)`
- `freebug_owns_surface` (function) `gui/browser_ui.c:17143` `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)`
- `freebug_is_open` (function) `gui/browser_ui.c:17147` `static int freebug_is_open(const browser_window *w)`
- `freebug_repl_worker` (function) `gui/browser_ui.c:17154` `static tab *freebug_repl_worker(browser_window *w)` -- Returns the live page worker for the REPL, lazily (re)opening one bound to the active page's cache if none is kept...
- `freebug_pane_refresh` (function) `gui/browser_ui.c:17196` `static void freebug_pane_refresh(browser_window *w)` -- Runs the active panel's expression (fb_panes) in the page's REPL worker and stores the text it returns.
- `freebug_set_tab` (function) `gui/browser_ui.c:17233` `static void freebug_set_tab(browser_window *w, int which)` -- Activates `tab`: each tab keeps its own editor text and scroll, so switching back finds the * argument and position...
- `freebug_panes_invalidate` (function) `gui/browser_ui.c:17251` `static void freebug_panes_invalidate(browser_window *w)` -- A new page (or a dropped worker) makes every fetched panel stale: forget them and, when the * window shows one...
- `freebug_eval` (function) `gui/browser_ui.c:17258` `static void freebug_eval(browser_window *w)`
- `freebug_handle_key` (function) `gui/browser_ui.c:17299` `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...`
- `freebug_pointer_button` (function) `gui/browser_ui.c:17342` `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...`
- `freebug_pointer_motion` (function) `gui/browser_ui.c:17371` `static void freebug_pointer_motion(browser_window *w)`
- `freebug_pointer_axis` (function) `gui/browser_ui.c:17393` `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)`
- `down` (function) `gui/browser_ui.c:17405` `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void...`
- `ptr_enter` (function) `gui/browser_ui.c:17411` `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
- `ptr_leave` (function) `gui/browser_ui.c:17429` `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
- `ptr_motion` (function) `gui/browser_ui.c:17446` `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
- `load_current` (function) `gui/browser_ui.c:17471` `static void load_current(browser_window *w)`
- `go_omnibox` (function) `gui/browser_ui.c:17484` `static void go_omnibox(browser_window *w)` -- Commits the URL bar like a real omnibox: an existing local file is opened as before; otherwise url_omnibox (pure)...
- `ptr_button` (function) `gui/browser_ui.c:17529` `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
- `scroll_line_px` (function) `gui/browser_ui.c:17776` `static double scroll_line_px(const browser_window *w)` -- const rd_block *again = NULL; for (size_t i = 0; w->doc != NULL && i < rd_count(w->doc); ++i) { const rd_block *b =...
- `ptr_axis` (function) `gui/browser_ui.c:17780` `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
- `ptr_frame` (function) `gui/browser_ui.c:17804` `static void ptr_frame(void *d, struct wl_pointer *p)`
- `mime_is_text` (function) `gui/browser_ui.c:17820` `static int mime_is_text(const char *mime)` -- } static const struct wl_pointer_listener pointer_listener = { .enter = ptr_enter, .leave = ptr_leave, .motion =...
- `data_offer_source_actions` (function) `gui/browser_ui.c:17838` `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)`
- `data_offer_action` (function) `gui/browser_ui.c:17841` `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)`
- `data_device_data_offer` (function) `gui/browser_ui.c:17851` `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...` -- } static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a) { (void)d; (void)o; (void)a; }...
- `data_device_selection` (function) `gui/browser_ui.c:17863` `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...` -- The clipboard selection changed.
- `data_device_enter` (function) `gui/browser_ui.c:17882` `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...` -- wl_data_offer_destroy(w->selection_offer); if (offer == NULL) { w->selection_offer = NULL...
- `data_device_leave` (function) `gui/browser_ui.c:17887` `static void data_device_leave(void *d, struct wl_data_device *dev)`
- `data_device_motion` (function) `gui/browser_ui.c:17888` `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...`
- `data_device_drop` (function) `gui/browser_ui.c:17892` `static void data_device_drop(void *d, struct wl_data_device *dev)`
- `data_source_cancelled` (function) `gui/browser_ui.c:17903` `static void data_source_cancelled(void *data, struct wl_data_source *src)` -- wl_fixed_t x, wl_fixed_t y) { (void)d; (void)dev; (void)t; (void)x; (void)y; } static void data_device_drop(void *d...
- `data_source_send` (function) `gui/browser_ui.c:17909` `static void data_source_send(void *data, struct wl_data_source *src,
                            ...` -- .enter = data_device_enter, .leave = data_device_leave, .motion = data_device_motion, .drop = data_device_drop...
- `data_source_target` (function) `gui/browser_ui.c:17922` `static void data_source_target(void *d, struct wl_data_source *s, const char *m)`
- `freebug_copy_console` (function) `gui/browser_ui.c:17934` `static void freebug_copy_console(browser_window *w)` -- Formats the entire Freebug console buffer and places it on the Wayland clipboard, so the user can paste the...
- `loop` (function) `gui/browser_ui.c:17993` `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately...`
- `insert_pasted_text` (function) `gui/browser_ui.c:18002` `static void insert_pasted_text(browser_window *w, const char *text, size_t len)` -- Inserts pasted bytes into whichever text target currently has focus (page input, User-Agent box, or the URL bar).
- `clipboard_copy` (function) `gui/browser_ui.c:18066` `static void clipboard_copy(browser_window *w)` -- Ctrl+C: copy the focused field's text (or, with nothing focused, the page address) * to the clipboard by owning a...
- `keyboard_keymap` (function) `gui/browser_ui.c:18114` `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...`
- `keyboard_enter` (function) `gui/browser_ui.c:18135` `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...`
- `keyboard_leave` (function) `gui/browser_ui.c:18142` `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)`
- `key_sym_to_js_key` (function) `gui/browser_ui.c:18150` `static const char *key_sym_to_js_key(xkb_keysym_t sym)` -- Maps an xkb keysym to a JS event.key string.
- `key_sym_to_keycode` (function) `gui/browser_ui.c:18176` `static int key_sym_to_keycode(xkb_keysym_t sym)` -- Maps an xkb keysym to a JS keyCode number.
- `dispatch_js_event` (function) `gui/browser_ui.c:18201` `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...` -- Dispatches a JS DOM event to the worker for the given node_id.
- `handle_key_press` (function) `gui/browser_ui.c:18259` `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...` -- Performs the effect of a single key press.
- `key_is_repeatable` (function) `gui/browser_ui.c:18595` `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)` -- Keys whose held-down auto-repeat is safe and useful: text editing, cursor motion and scrolling.
- `key_repeat_arm` (function) `gui/browser_ui.c:18611` `static void key_repeat_arm(browser_window *w, uint32_t key)` -- Arms the repeat timer for key: first fire after repeat_delay ms, then every * 1/repeat_rate s.
- `key_repeat_stop` (function) `gui/browser_ui.c:18624` `static void key_repeat_stop(browser_window *w)` -- 1/repeat_rate s.
- `key_repeat_fire` (function) `gui/browser_ui.c:18635` `static void key_repeat_fire(browser_window *w)` -- Re-fires the currently held key.
- `keyboard_key` (function) `gui/browser_ui.c:18649` `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...`
- `keyboard_modifiers` (function) `gui/browser_ui.c:18689` `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...`
- `keyboard_repeat_info` (function) `gui/browser_ui.c:18698` `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)`
- `seat_caps` (function) `gui/browser_ui.c:18717` `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
- `seat_name` (function) `gui/browser_ui.c:18728` `static void seat_name(void *d, struct wl_seat *s, const char *name)`
- `registry_global` (function) `gui/browser_ui.c:18735` `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
- `registry_remove` (function) `gui/browser_ui.c:18755` `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
- `gui_is_idle` (function) `gui/browser_ui.c:18768` `static int gui_is_idle(const browser_window *w)` -- The page has nothing left to do: loaded, no background job, no JS tick due, no deferred repaint.
- `gui_timing_step` (function) `gui/browser_ui.c:18779` `static int gui_timing_step(browser_window *w, uint64_t now)` -- Called every loop turn while FREEDOM_GUI_TIMING is set.
- `ui_run_browser` (function) `gui/browser_ui.c:18794` `ui_status ui_run_browser(const char *start_url)`
- `saving` (function) `gui/browser_ui.c:18813` `* disables saving (never clobber);`
- `redraws` (function) `gui/browser_ui.c:18903` `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A...`
- `moves` (function) `gui/browser_ui.c:18916` `* client that stops reading its socket while the pointer moves (spec/wl_guard.md). */ if...`
- `cost` (function) `gui/browser_ui.c:19234` `* measured cost (floor 33 ms = the existing ~30 fps ceiling):
             * cheap pages paint at...`

## gui/browser_ui_internal.h
Depends on: `include/freedom_config.h`
Imported by: `gui/browser_ui.c`, `gui/bui_theme.c`
- `set_rgb` (function) `gui/browser_ui_internal.h:105` `void set_rgb(cairo_t *cr, ui_rgb c);` -- /* Selectable palettes for the options menu. typedef enum ui_theme_mode { UI_THEME_LIGHT = 0, UI_THEME_DARK...

## gui/bui_theme.c
Depends on: `gui/browser_ui_internal.h`, `include/css.h`, `include/css_color.h`
- `ui_theme_default` (function) `gui/bui_theme.c:15` `ui_theme ui_theme_default(void)` -- bui_theme — presentation palettes for the Wayland/Cairo GUI.
- `ui_theme_dark` (function) `gui/bui_theme.c:78` `ui_theme ui_theme_dark(void)` -- Dark reading palette.
- `ui_theme_sepia` (function) `gui/bui_theme.c:123` `ui_theme ui_theme_sepia(void)` -- Sepia reading palette: warm paper background and dark-brown ink, easier on the eyes for long-form text.
- `ui_theme_for` (function) `gui/bui_theme.c:165` `ui_theme ui_theme_for(int mode)` -- t.menu_bg        = (ui_rgb){ 0.95, 0.90, 0.80 }; t.menu_border    = (ui_rgb){ 0.55, 0.46, 0.32 }; t.menu_text      =...
- `rgb_from_packed` (function) `gui/bui_theme.c:174` `ui_rgb rgb_from_packed(int packed)` -- t.scrollbar_thumb_hot = (ui_rgb){ 0.44, 0.35, 0.22 }; return t; } /* The single place that maps the theme mode to a...
- `set_rgb` (function) `gui/bui_theme.c:179` `void set_rgb(cairo_t *cr, ui_rgb c)`

## gui/freedom_view.c
Depends on: `include/html_parse.h`, `include/ui.h`
- `main` (function) `gui/freedom_view.c:37` `int main(int argc, char **argv)`

## gui/svg_paint.c
Depends on: `include/css_color.h`, `include/freedom_config.h`, `include/svg_paint.h`
- `svp_alpha` (function) `gui/svg_paint.c:31` `static double svp_alpha(int opacity, int paint_opacity)` -- Resolves a shape's packed paint into an RGB triple.
- `svp_rect_path` (function) `gui/svg_paint.c:38` `static void svp_rect_path(cairo_t *cr, const sv_shape *sh)` -- r = (double)((c >> 16) & 0xFF) / 255.0; g = (double)((c >> 8) & 0xFF) / 255.0; b = (double)(c & 0xFF) / 255.0...
- `svp_shape_path` (function) `gui/svg_paint.c:73` `static void svp_shape_path(cairo_t *cr, const sv_image *img, const sv_shape *sh)`
- `svp_draw_text` (function) `gui/svg_paint.c:126` `static void svp_draw_text(cairo_t *cr, const sv_shape *sh, int current_rgb)`
- `svp_draw` (function) `gui/svg_paint.c:139` `void svp_draw(cairo_t *cr, const sv_image *img,
              double x, double y, double w, doubl...`

## gui/ui_render.c
Depends on: `include/freedom_config.h`, `include/ui.h`
- `sanitize_utf8_inplace` (function) `gui/ui_render.c:39` `static void sanitize_utf8_inplace(char *s)` -- Rewrites s in place to well-formed UTF-8, replacing any byte that is not part of a valid sequence with '?'....
- `button_rects` (function) `gui/ui_render.c:107` `static void button_rects(const ui_window *w, double *min_x, double *max_x, double *close_x)` -- int    use_csd;    /* draw our own titlebar/controls (compositor has no SSD) int    maximized; double ptr_x, ptr_y...
- `buffer_release` (function) `gui/ui_render.c:115` `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
- `destroy_buffer` (function) `gui/ui_render.c:122` `static void destroy_buffer(ui_window *w)`
- `ensure_buffer` (function) `gui/ui_render.c:128` `static int ensure_buffer(ui_window *w)`
- `paint` (function) `gui/ui_render.c:159` `static void paint(ui_window *w)`
- `redraw` (function) `gui/ui_render.c:245` `static void redraw(ui_window *w)`
- `wm_base_ping` (function) `gui/ui_render.c:260` `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
- `xdg_surface_configure` (function) `gui/ui_render.c:266` `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
- `toplevel_configure` (function) `gui/ui_render.c:274` `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
- `toplevel_close` (function) `gui/ui_render.c:283` `static void toplevel_close(void *data, struct xdg_toplevel *t)`
- `deco_configure` (function) `gui/ui_render.c:294` `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)` -- The compositor tells us the actual decoration mode it granted.
- `ptr_enter` (function) `gui/ui_render.c:305` `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
- `ptr_leave` (function) `gui/ui_render.c:312` `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
- `ptr_motion` (function) `gui/ui_render.c:315` `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
- `ptr_button` (function) `gui/ui_render.c:322` `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...` -- ui_window *w = (ui_window *)d; w->ptr_x = wl_fixed_to_double(x); w->ptr_y = wl_fixed_to_double(y); } static void...
- `ptr_axis` (function) `gui/ui_render.c:344` `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
- `seat_caps` (function) `gui/ui_render.c:367` `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
- `seat_name` (function) `gui/ui_render.c:376` `static void seat_name(void *d, struct wl_seat *s, const char *name)`
- `registry_global` (function) `gui/ui_render.c:383` `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
- `registry_remove` (function) `gui/ui_render.c:401` `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
- `ui_run_text_view` (function) `gui/ui_render.c:410` `ui_status ui_run_text_view(const char *title, const char *text, size_t text_len)`

## include/anti_fp.h
Imported by: `include/secure_fetch.h`, `src/anti_fp.c`, `src/identity.c`, `src/js_env.c`, `src/secure_fetch.c`, `src/tab.c`, `tests/test_anti_fp.c`, `tests/test_identity.c`
- `fp_timer_resolution_ms` (function) `include/anti_fp.h:52` `uint64_t fp_timer_resolution_ms(void);`
- `fp_coarsen_time_ms` (function) `include/anti_fp.h:53` `uint64_t fp_coarsen_time_ms(uint64_t raw_ms);`
- `fp_user_agent` (function) `include/anti_fp.h:57` `const char *fp_user_agent(void);`
- `fp_accept_language` (function) `include/anti_fp.h:58` `const char *fp_accept_language(void);`
- `fp_accept_language_header` (function) `include/anti_fp.h:59` `const char *fp_accept_language_header(void);` -- #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE...
- `fp_timezone` (function) `include/anti_fp.h:60` `const char *fp_timezone(void);` -- #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1"...
- `fp_platform` (function) `include/anti_fp.h:61` `const char *fp_platform(void);` -- #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- `fp_vendor` (function) `include/anti_fp.h:62` `const char *fp_vendor(void);` -- #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against high-resolution timing --- uint64_t...
- `fp_hardware_concurrency` (function) `include/anti_fp.h:63` `int fp_hardware_concurrency(void);` -- /* --- clocks: coarse granularity against high-resolution timing --- uint64_t fp_timer_resolution_ms(void); uint64_t...
- `fp_device_memory_gb` (function) `include/anti_fp.h:64` `int fp_device_memory_gb(void);`
- `properties` (function) `include/anti_fp.h:67` `* Legacy navigator properties (Hito 30b): normalized Firefox values shared by * js_env and the network layer so JS...`
- `fp_app_code_name` (function) `include/anti_fp.h:71` `const char *fp_app_code_name(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_product` (function) `include/anti_fp.h:72` `const char *fp_product(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_app_name` (function) `include/anti_fp.h:73` `const char *fp_app_name(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_product_sub` (function) `include/anti_fp.h:74` `const char *fp_product_sub(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_oscpu` (function) `include/anti_fp.h:75` `const char *fp_oscpu(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_build_id` (function) `include/anti_fp.h:76` `const char *fp_build_id(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_max_touch_points` (function) `include/anti_fp.h:77` `int fp_max_touch_points(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_on_line` (function) `include/anti_fp.h:78` `int fp_on_line(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_cookie_enabled` (function) `include/anti_fp.h:79` `int fp_cookie_enabled(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_bucket_screen` (function) `include/anti_fp.h:83` `void fp_bucket_screen(int w, int h, int *out_w, int *out_h);` -- Snaps a screen size to a standard bucket (cuts entropy). out_w/out_h non-NULL. * Picks the largest-area bucket that...
- `fp_perturb` (function) `include/anti_fp.h:88` `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key);` -- Deterministic per-session readback poisoning (canvas/audio): flips only the least-significant bit of a sparse...
- `domain` (function) `include/anti_fp.h:91` `* registrable domain (eTLD+1). Same (session_key, domain) => same key (poisoning * is stable within a site);`
- `probability` (function) `include/anti_fp.h:93` `* keys with overwhelming probability (canvas/audio noise is not linkable across * sites, defeating cross-origin...`
- `fp_origin_key` (function) `include/anti_fp.h:98` `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain);` -- Derives the per-origin readback key from the per-session secret and a site's registrable domain (eTLD+1).

## include/block_flow.h
Imported by: `gui/browser_ui.c`, `src/block_flow.c`, `tests/test_block_flow.c`
- `ABSENT` (function) `include/block_flow.h:26` `* as ABSENT (0) rather than propagated: a poisoned length must not spread into * the geometry of the rest of the...`
- `bf_collapse_n` (function) `include/block_flow.h:33` `* bf_collapse_n((double[])`
- `bf_margins_adjoin` (function) `include/block_flow.h:43` `int bf_margins_adjoin(double border_px, double padding_px);` -- Whether two vertical margins separated by this much border and padding ADJOIN, i.e. whether they collapse at all...

## include/box_blur.h
Imported by: `gui/browser_ui.c`, `src/box_blur.c`, `tests/test_box_blur.c`
- `bb_box_sizes` (function) `include/box_blur.h:16` `int bb_box_sizes(double sigma, int sizes[3]);` -- The three odd box widths approximating a Gaussian of standard deviation sigma. * Returns 0 (sizes untouched) when...
- `BB_MAX_PIXELS` (function) `include/box_blur.h:20` `* arguments or a mask larger than BB_MAX_PIXELS (buffer untouched). */ int bb_blur_a8(unsigned char *buf, int w, int...`
- `alpha` (function) `include/box_blur.h:26` `* no pixel has alpha (nothing to blur), 1 otherwise. Everything outside rect stays 0 after the blur, * so blurring...`

## include/box_style.h
Depends on: `include/css.h`
Imported by: `gui/browser_ui.c`, `include/box_tree.h`, `src/box_style.c`, `src/box_tree.c`, `src/dom_debug.c`, `src/page_view.c`, `src/render_doc.c`, `tests/test_box_style.c`, `tests/test_dom_debug.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`
- `box` (function) `include/box_style.h:115` `* in_list nonzero when the block sits inside a list item: it then takes * the <li> box (zero margin), keeping items...`
- `BX_TROLE_NONE` (function) `include/box_style.h:144` `* BX_TROLE_NONE (an unrecognised element joins no table -- fail closed). */ bx_table_role bx_table_role_of(const...`
- `bx_display_name` (function) `include/box_style.h:156` `const char *bx_display_name(bx_display d);` -- Stable, short English name of a display type for structured/agent output.
- `bx_width_cap` (function) `include/box_style.h:182` `double bx_width_cap(int w_px, int w_pct, double avail_w);` -- Effective width cap combining the px cap (w_px, 0 = none) with a symbolic per-mille cap (w_pct, 0 = none; Hito 32)...
- `bx_width_cap2` (function) `include/box_style.h:187` `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w);` -- The used width cap of an element: the tighter of its `width` (w_px, w_pct) and its `max-width` (mw_px, mw_pct), each...
- `bx_replaced_box` (function) `include/box_style.h:206` `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den, double avail_w, double *out_w, double *out_h);` -- CSS Sizing 4 section 4: when one axis is definite and an aspect-ratio is present, the ratio supplies the other.
- `bx_border_box_h` (function) `include/box_style.h:220` `double bx_border_box_h(double declared_h, int border_box, double pad_t, double pad_b, double bord_t, double bord_b);` -- Border-box height for a DECLARED height under box-sizing (CSS 2.1 10.6.3, CSS Box Sizing 3 section 4).
- `block` (function) `include/box_style.h:226` `* indefinite containing block (cb_h < 0) the value behaves as auto: -1. * Without a percentage it is px_val...`
- `bx_line_height_px` (function) `include/box_style.h:239` `double bx_line_height_px(int line_scale, double font_px);` -- The used line-height in px of text at font_px for a css line_scale value (spec/box_style.md 4c): 0 = normal (returns...
- `bx_definite_content_h` (function) `include/box_style.h:241` `double bx_definite_content_h(double h, double min_h, double max_h, int border_box, double v_edges);`
- `page` (function) `include/box_style.h:245` `* instead of letting it extend the page (CSS 2.1 section 10.7 + 11.1.1). That * is the case unless BOTH overflow...`
- `bx_lp_px` (function) `include/box_style.h:267` `double bx_lp_px(int px_val, int pct_pm, double basis);` -- half plus pct_pm per-mille of `basis`.
- `bx_content_cap` (function) `include/box_style.h:275` `double bx_content_cap(double width_cap, int border_box, double pad_l, double pad_r, double bord_l, double bord_r);` -- Content-width cap adjusted for box-sizing (2026-07-11).
- `bx_border_span` (function) `include/box_style.h:286` `double bx_border_span(double width_cap, int border_box, double pad_l, double pad_r, double bord_l, double bord_r);` -- The border-inclusive span the painter lays a box out with (its content plus left/right border; padding sits outside it).
- `bx_flex_max_clamp` (function) `include/box_style.h:292` `double bx_flex_max_clamp(double outer_basis, double mw_cap, int border_box, double pad_bord_h, double margin_h);` -- Flexbox 1 9.2.3: an item's OUTER flex base size clamped by its max-width (the hypothetical main size). mw_cap <= 0 =...
- `bx_flex_min_clamp` (function) `include/box_style.h:298` `double bx_flex_min_clamp(double outer_basis, double min_w, int border_box, double pad_bord_h, double margin_h);` -- The min-width half of the same clamp (Flexbox 9.2.3): an outer base below the item's min-width (converted to the...
- `bx_background_layer` (function) `include/box_style.h:331` `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h, double *out_x, double *out_y);`

## include/box_tree.h
Depends on: `include/box_style.h`, `include/flex_layout.h`, `include/page_view.h`
Imported by: `gui/browser_ui.c`, `src/box_tree.c`, `src/page_view.c`, `src/tab.c`, `tests/test_box_tree.c`
- `closed` (function) `include/box_tree.h:34` `* fails closed (BT_ERR_RANGE) instead of overflowing the stack. */ #define BT_MAX_DEPTH 64u #define BT_MAX_CHILDREN...`
- `one` (function) `include/box_tree.h:99` `* of forcing them all onto one (flex-wrap);`
- `line` (function) `include/box_tree.h:115` `* its line (already resolved from align-self / the * container's align-items by the caller). */ /* this node as a...`
- `node` (function) `include/box_tree.h:162` `* node (x/y parent-relative, w/h border-box). display:none nodes get a zero rect and * take no space. The caller...`
- `flow` (function) `include/box_tree.h:201` `* position is where the box would have started in flow (CSS 2.2 §10.3.7/§10.6.4);`
- `bottom` (function) `include/box_tree.h:208` `* bottom with auto top still anchors bottom (R8). * `placed` (may be NULL) marks which boxes have an in-flow rect in...`
- `placed` (function) `include/box_tree.h:215` `* box counts as placed (legacy behaviour). * bt_resolve_positioning delegates with NULL arrays (legacy behaviour)....`
- `bt_box_hidden` (function) `include/box_tree.h:233` `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid);` -- Stage 2b visibility gate: 1 when the box at `bid` or any ancestor on the parent_id chain has visibility...
- `bt_in_subtree` (function) `include/box_tree.h:239` `int bt_in_subtree(const pv_box_def *boxes, size_t nbox, size_t root, size_t bid);` -- 1 when box `bid` is `root` or a descendant of it on the parent_id chain, else 0 (ancestors, siblings, out-of-range...
- `bt_oof_anchor` (function) `include/box_tree.h:253` `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid);` -- Stage 2d out-of-flow subtree classification (spec/box_engine.md).
- `bt_oof_root` (function) `include/box_tree.h:254` `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid);`
- `insets` (function) `include/box_tree.h:258` `* minus the two insets (px half + per-mille half of cb), an auto/unset inset * counting 0, never below 0. *both (may...`
- `bt_containing_block` (function) `include/box_tree.h:268` `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i, const double *box_x, const double *box_y...` -- The containing block of box i as the positioning solver resolves it: the viewport for FIXED (and for ABSOLUTE with...
- `bt_defer_roots` (function) `include/box_tree.h:291` `size_t bt_defer_roots(const pv_box_def *boxes, size_t nbox, const bt_positioned *pos, size_t npos, const char...` -- (an absolute backdrop, say) comes EARLIER in the tree than S, S must paint above it -- but the painter draws all...

## include/browser.h
Imported by: `gui/browser_ui.c`, `src/browser.c`, `tests/test_browser.c`
- `state` (function) `include/browser.h:62` `* state (frees old history and page buffers). */ browser_status browser_init(browser_state *bs);`
- `browser_free` (function) `include/browser.h:66` `void browser_free(browser_state *bs);` -- Zero-initialise or reset a state.
- `browser_set_page` (function) `include/browser.h:71` `* browser_set_page() with the result. */ browser_status browser_navigate(browser_state *bs, const char *url);`
- `browser_entry_doc` (function) `include/browser.h:87` `int browser_entry_doc(const browser_state *bs, size_t pos);` -- Same-document entries (history.pushState, spec/browser.md 3b). push adds an entry of the CURRENT document after...
- `browser_doc_index` (function) `include/browser.h:91` `int browser_doc_index(const browser_state *bs);` -- Index of the current entry within its document's contiguous run of entries (0 for * the entry the document was...
- `browser_can_back` (function) `include/browser.h:94` `int browser_can_back(const browser_state *bs);` -- Index of the current entry within its document's contiguous run of entries (0 for * the entry the document was...
- `browser_can_forward` (function) `include/browser.h:95` `int browser_can_forward(const browser_state *bs);`
- `browser_current_url` (function) `include/browser.h:96` `const char *browser_current_url(const browser_state *bs);`
- `browser_is_exception` (function) `include/browser.h:99` `int browser_is_exception(const browser_state *bs, const char *host);` -- Index of the current entry within its document's contiguous run of entries (0 for * the entry the document was...
- `browser_url_bar_selection` (function) `include/browser.h:131` `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len);` -- If a selection exists, writes its start offset and length and returns 1; else 0. * Lets the GUI copy/cut the...
- `browser_url_bar_delete_selection` (function) `include/browser.h:135` `int browser_url_bar_delete_selection(browser_state *bs);` -- Removes the selected range (if any), placing the cursor at its start; returns 1 if * something was removed, else 0.
- `copied` (function) `include/browser.h:143` `* copied (truncated to fit) and shown until now_ms reaches the expiry * (now_ms + BROWSER_STATUS_DURATION_MS). A...`
- `browser_status_text` (function) `include/browser.h:150` `const char *browser_status_text(const browser_state *bs, uint64_t now_ms);` -- Transient status line (a toast, e.g. "blocked: insecure http link"). msg is copied (truncated to fit) and shown...

## include/cached_fetch.h
Depends on: `include/http_cache.h`, `include/secure_fetch.h`
Imported by: `gui/browser_ui.c`, `src/cached_fetch.c`, `tests/test_cached_fetch.c`
- `cf_set_store` (function) `include/cached_fetch.h:30` `void cf_set_store(hc_store *store);` -- Cache-aware GET.
- `cf_store` (function) `include/cached_fetch.h:31` `hc_store *cf_store(void);`
- `cf_attach_redirect_memory` (function) `include/cached_fetch.h:38` `void cf_attach_redirect_memory(hc_store *store);` -- conditional GET is sent to the stored FINAL url and a 304 serves the stored body. sf_status cf_get_with(hc_store...

## include/compositor.h
Imported by: `gui/browser_ui.c`, `src/box_tree.c`, `src/compositor.c`, `tests/test_compositor.c`
- `cx_forms_stacking_context` (function) `include/compositor.h:60` `int cx_forms_stacking_context(const cx_style *s);` -- Does this box establish a stacking context?
- `cx_item_compare` (function) `include/compositor.h:80` `int cx_item_compare(const cx_item *a, const cx_item *b);` -- Total paint order: layer ascending, then z-index ascending (auto == 0), then document order ascending.
- `cx_sort` (function) `include/compositor.h:84` `void cx_sort(cx_item *items, size_t n);` -- Stable in-place sort of `items` into paint order (uses cx_item_compare).

## include/css.h
Depends on: `include/css_color.h`
Imported by: `gui/browser_ui.c`, `gui/bui_theme.c`, `include/box_style.h`, `include/css_chain.h`, `include/css_computed.h`, `include/css_decl.h`, `include/css_select.h`, `include/page_view.h`, `src/box_tree.c`, `src/compositor.c`, `src/css.c`, `src/css_box.c`, `src/css_length.c`, `src/css_text.c`, `src/css_values.c`, `src/dom_debug.c`, `src/page_view.c`, `src/render_doc.c`, `src/tab.c`, `src/text_case.c`, `src/text_shape.c`, `tests/test_box_tree.c`, `tests/test_compositor.c`, `tests/test_css.c`, `tests/test_css_drops.c`, `tests/test_css_gradient.c`, `tests/test_css_length.c`, `tests/test_css_text.c`, `tests/test_css_values.c`, `tests/test_dom_debug.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`, `tests/test_tab.c`, `tests/test_text_case.c`, `tests/test_text_shape.c`, `tests/test_webfont_load.c`
- `verbatim` (function) `include/css.h:84` `* the quoted row strings verbatim (flex_layout parses them);`
- `POINTER` (function) `include/css.h:220` `* POINTER (shows the hand cursor already used for links) from every other value * (shows the default arrow);`
- `family` (function) `include/css.h:690` `* LOCAL family (spec/text_shape.md section 7);`
- `translate` (function) `include/css.h:856` `* translate()/translateX()/translateY();`
- `scaleY` (function) `include/css.h:857` `* scaleY() as a PERCENT of identity (100 = scale(1), matching font_scale's * convention);`
- `declared` (function) `include/css.h:861` `* function was not declared (identity: 0 offset / 100% scale / 0deg). * Percentage translate arguments are not...`
- `element` (function) `include/css.h:866` `* so two different rules matching the same element (e.g. one setting * translate, a more specific one setting...`
- `slots` (function) `include/css.h:873` `* parse time into ALL seven slots (singular matrices fail closed);`
- `palette` (function) `include/css.h:1031` `* so an inactive theme * palette (a dark palette in a light render) can never clobber the active one. *...`
- `css_free` (function) `include/css.h:1081` `void css_free(css_sheet *s);` -- As css_parse_scoped, plus the drop sink. log == NULL is exactly css_parse_scoped: same path, same sheet, same cost.
- `order` (function) `include/css.h:1084` `* cascade order (specificity, then document order), then the element's own * inline_style (which wins)....`
- `inherited_px` (function) `include/css.h:1197` `* whose PARENT computes to inherited_px (<= 0 = unknown -> the CSS initial). * * Exported because the caller that...`
- `css_ua_heading_em` (function) `include/css.h:1209` `double css_ua_heading_em(int level);` -- The user-agent sheet's font-size of <h1>..<h6> as a multiple of the parent's (HTML Rendering 15.3.6: 2em, 1.5em...
- `name` (function) `include/css.h:1214` `* name (NULL = not a heading). */ double css_computed_font_size_for_tag(const css_style *o, double inherited_px...`
- `css_font_face_count` (function) `include/css.h:1224` `size_t css_font_face_count(const css_sheet *sheet);` -- Web font access: returns the number of @font-face declarations parsed into the sheet, and copies the i-th...
- `css_font_face_at` (function) `include/css.h:1225` `int css_font_face_at(const css_sheet *sheet, size_t i, char *family, size_t fam_cap, char *src_url, size_t url_cap);`
- `css_resolve_anim_keyframes` (function) `include/css.h:1233` `void css_resolve_anim_keyframes(css_style *s, const css_sheet *sheet);` -- Resolve @keyframes: scans sheet->keyframes[] for a name matching s->anim_name (first-char match).

## include/css_atrule.h
Imported by: `src/css.c`, `src/css_atrule.c`, `tests/test_css_atrule.c`
- `car_supports` (function) `include/css_atrule.h:29` `int car_supports(const char *s, size_t a, size_t b, const car_ops *ops);` -- The questions @supports asks the caller's own engine. prop is lowercased and * both strings are trimmed and...
- `car_layer_rank` (function) `include/css_atrule.h:40` `int car_layer_rank(car_layers *L, const char *name, size_t len);` -- Rank (1..CAR_MAX_LAYERS) of the layer whose full dotted name is name[0,len), registering it on first sight. len == 0...
- `car_effective_spec` (function) `include/css_atrule.h:44` `int car_effective_spec(int spec, int layer, int important);` -- Folds layer rank and specificity into one comparable value (layer first). layer * 0 = unlayered.

## include/css_box.h
Depends on: `include/css_decl.h`
Imported by: `src/css.c`, `src/css_box.c`, `src/css_text.c`, `tests/test_css_box.c`
- `cb_length_px` (function) `include/css_box.h:15` `int cb_length_px(const char *v, double *px);`
- `cb_interp_len` (function) `include/css_box.h:16` `int cb_interp_len(const char *v, int allow_auto, int *out);`
- `cb_emit_len` (function) `include/css_box.h:17` `int cb_emit_len(css_decl *dst, int cap, int slot, const char *val, int allow_auto, int allow_neg);`
- `cb_expand_box4` (function) `include/css_box.h:19` `int cb_expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg, css_decl *dst, int cap);`
- `cb_expand_box2` (function) `include/css_box.h:21` `int cb_expand_box2(const char *val, int slot_start, int slot_end, int allow_auto, int allow_neg, css_decl *dst, int...`
- `cb_interp_lp` (function) `include/css_box.h:23` `int cb_interp_lp(const char *v, int allow_auto, int allow_pct, int *out_px, int *out_pm);`
- `cb_value_em_milli` (function) `include/css_box.h:25` `int cb_value_em_milli(const char *v);`
- `rectangle` (function) `include/css_box.h:27` `* rectangle (top, right, bottom, left): px[i] + pm[i]/1000 of the border box (height for * top/bottom, width for...`
- `cb_lp_can_be_nonneg` (function) `include/css_box.h:31` `int cb_lp_can_be_nonneg(int px_val, int pct_pm);`
- `cb_next_ws_token` (function) `include/css_box.h:32` `int cb_next_ws_token(const char **p, char *tok, size_t cap);`
- `cb_interp_align` (function) `include/css_box.h:33` `int cb_interp_align(const char *v);`
- `cb_interp_fontsize_ex` (function) `include/css_box.h:34` `int cb_interp_fontsize_ex(const char *v, int *abs_out);`
- `cb_interp_lineheight` (function) `include/css_box.h:35` `int cb_interp_lineheight(const char *v);`
- `cb_interp_weight` (function) `include/css_box.h:36` `int cb_interp_weight(const char *v);`
- `cb_interp_style` (function) `include/css_box.h:37` `int cb_interp_style(const char *v);`
- `cb_interp_textdeco` (function) `include/css_box.h:38` `int cb_interp_textdeco(const char *v);`
- `cb_interp_display` (function) `include/css_box.h:39` `int cb_interp_display(const char *v);`
- `cb_interp_gap` (function) `include/css_box.h:40` `int cb_interp_gap(const char *v);`
- `cb_interp_justify` (function) `include/css_box.h:41` `int cb_interp_justify(const char *v);`
- `cb_interp_gridcols` (function) `include/css_box.h:42` `int cb_interp_gridcols(const char *v);`
- `cb_expand_grid_template_cols` (function) `include/css_box.h:43` `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap);`
- `strings` (function) `include/css_box.h:45` `* Quoted area strings (the grid-template shorthand's row half) are skipped. */ int...`

## include/css_chain.h
Depends on: `include/css.h`, `include/css_select.h`
Imported by: `src/css_chain.c`, `src/dom.c`, `src/page_view.c`
- `cch_element_matches` (function) `include/css_chain.h:69` `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel);` -- Nonzero iff the parsed selector *sel matches element `el`, built against the same bounded ancestor/sibling/attribute...
- `lacks` (function) `include/css_chain.h:73` `* the element lacks (csel's subj_req) is rejected before the ancestor chain is built: on a * query that scans a...`
- `box` (function) `include/css_chain.h:79` `* generated box (css_resolve_pseudo) against the same element context. * font_size is el's own COMPUTED font-size...`

## include/css_color.h
Imported by: `gui/browser_ui.c`, `gui/bui_theme.c`, `gui/svg_paint.c`, `include/css.h`, `src/css.c`, `src/css_box.c`, `src/css_color.c`, `src/css_gradient.c`, `src/css_text.c`, `src/css_values.c`, `src/page_view.c`, `src/svg_render.c`, `tests/test_css_color.c`
- `cc_pack` (function) `include/css_color.h:49` `int cc_pack(cc_rgb c);` -- Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color"...

## include/css_computed.h
Depends on: `include/css.h`
Imported by: `src/css_computed.c`, `src/tab.c`, `tests/test_css_computed.c`
- `ccm_get` (function) `include/css_computed.h:29` `size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap);` -- Writes the computed value of the kebab-case property `prop` into out (cap bytes, NUL terminated).
- `ccm_property_count` (function) `include/css_computed.h:32` `size_t ccm_property_count(void);` -- Writes the computed value of the kebab-case property `prop` into out (cap bytes, NUL terminated).
- `ccm_property_name` (function) `include/css_computed.h:33` `const char *ccm_property_name(size_t i);`

## include/css_decl.h
Depends on: `include/css.h`, `include/css_select.h`
Imported by: `include/css_box.h`, `include/css_gradient.h`, `include/css_mask.h`, `include/css_text.h`, `src/css.c`, `src/css_box.c`, `src/css_gradient.c`, `src/css_text.c`, `src/css_values.c`, `src/page_view.c`, `tests/test_css_box.c`, `tests/test_css_text.c`
- `order` (function) `include/css_decl.h:50` `* The four margin slots are contiguous in CSS shorthand order (top,right,bottom, * left);`
- `contiguous` (function) `include/css_decl.h:65` `* contiguous (dx,dy,color) so expand_shadow writes them as a group. */ P_FONTFAMILY, P_TEXTTRANSFORM...`

## include/css_gradient.h
Depends on: `include/css_decl.h`
Imported by: `gui/browser_ui.c`, `src/css.c`, `src/css_gradient.c`, `src/css_mask.c`, `src/tab.c`, `tests/test_css_gradient.c`
- `cg_expand_bg_image` (function) `include/css_gradient.h:11` `int cg_expand_bg_image(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...`
- `cg_expand_background` (function) `include/css_gradient.h:13` `int cg_expand_background(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...`
- `width` (function) `include/css_gradient.h:17` `* width (x, rx) or height (y, ry);`
- `out` (function) `include/css_gradient.h:32` `* Returns 1 and fills *out (defaults first) when seg is a valid prelude, 0 when seg is not * one (it is a colour...`
- `cg_radial_len_px` (function) `include/css_gradient.h:37` `double cg_radial_len_px(int enc, double dim);` -- The first comma segment of a radial-gradient() argument list, when it is a prelude.
- `zero` (function) `include/css_gradient.h:41` `* floored at a hair above zero (the spec paints the last colour for a degenerate size) and * never non-finite. Pure....`
- `cg_parse_linear` (function) `include/css_gradient.h:51` `int cg_parse_linear(const char *fn, int *angle, int *colors, int *positions);` -- Parses one `linear-gradient(...)` function (the whole text, nothing around it) into its angle (CSS degrees), packed...

## include/css_index.h
Depends on: `include/css_select.h`
Imported by: `src/css.c`, `src/css_index.c`, `tests/test_css_index.c`
- `cix_build` (function) `include/css_index.h:34` `void cix_build(const css_sel *sels, size_t n, cix_index *idx);` -- Builds the index over sels[0,n) into *idx, overwriting it (a built index must be * cix_free'd first).
- `cix_free` (function) `include/css_index.h:37` `void cix_free(cix_index *idx);` -- Builds the index over sels[0,n) into *idx, overwriting it (a built index must be * cix_free'd first).
- `index` (function) `include/css_index.h:41` `* index (the caller then scans linearly). */ size_t cix_candidates(const cix_index *idx, const css_element *el...`

## include/css_length.h
Imported by: `src/css.c`, `src/css_box.c`, `src/css_gradient.c`, `src/css_length.c`, `src/css_mq.c`, `src/css_text.c`, `src/css_values.c`, `src/page_view.c`, `tests/test_css_length.c`
- `prelude` (function) `include/css_length.h:99` `* correct context for a media query prelude (whose `em` is defined to use the * initial font size, never the...`
- `cl_unit_is_font_relative` (function) `include/css_length.h:157` `* cl_unit_is_font_relative() draws. */ /* * Re-fits a resolved length to a different font-size: * * used = px + em *...`
- `cl_unit_font_ratio` (function) `include/css_length.h:182` `double cl_unit_font_ratio(const char *unit, size_t unit_len);` -- How many px one of `unit` is worth per 1px of font-size -- the per-unit derivative behind cl_lp.em.
- `here` (function) `include/css_length.h:186` `* Every input cl_resolve accepts resolves identically here (with has_pct 0);`
- `length` (function) `include/css_length.h:206` `* * A basis that is not a usable length (negative, zero, non-finite) contributes * nothing, but the absolute...`
- `cl_number` (function) `include/css_length.h:230` `int cl_number(const char *s, double *out, const char **endp);` -- Returns 1 on success, writing *out and pointing *endp at the first unconsumed character; 0 if there is no number there.
- `cl_is_length_unit` (function) `include/css_length.h:246` `int cl_is_length_unit(const char *unit, size_t unit_len);` -- Non-zero when `unit` names a <length> unit at all (any of the three families * plus px).

## include/css_mask.h
Depends on: `include/css_decl.h`
Imported by: `gui/browser_ui.c`, `src/css.c`, `src/css_mask.c`, `tests/test_css_mask.c`
- `cm_is_mask_prop` (function) `include/css_mask.h:28` `int cm_is_mask_prop(const char *prop);` -- One decoded layer. angle is CSS degrees; alpha[] is 0..255; pos[] is per-mille, -1 = evenly * spaced. kind 0 = no...
- `malformed` (function) `include/css_mask.h:31` `* the value is unsupported or malformed (the caller drops the declaration). */ int cm_expand(const char *prop, const...`
- `cm_encode_layer` (function) `include/css_mask.h:35` `void cm_encode_layer(const cm_layer *l, int *meta, int *alphas, int *poss);` -- Expands one mask declaration into cascade slots.
- `cm_decode_layer` (function) `include/css_mask.h:36` `void cm_decode_layer(int meta, int alphas, int poss, cm_layer *out);`

## include/css_mq.h
Imported by: `src/css.c`, `src/css_mq.c`, `tests/test_css_mq.c`
- `cmq_matches` (function) `include/css_mq.h:28` `int cmq_matches(const char *s, size_t len, const cmq_env *env);` -- 1 iff the media query list s[0,len) matches env; malformed/unknown parts fail * closed.

## include/css_select.h
Depends on: `include/css.h`
Imported by: `include/css_chain.h`, `include/css_decl.h`, `include/css_index.h`, `src/css.c`, `src/css_atrule.c`, `src/css_box.c`, `src/css_chain.c`, `src/css_gradient.c`, `src/css_select.c`, `src/css_text.c`, `src/css_values.c`, `src/css_vars.c`, `src/dom.c`, `tests/test_css.c`
- `csel_parse` (function) `include/css_select.h:160` `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel);` -- Parses the complex selector s[a,b) into *sel (spec computed; order/rule left to * the caller).
- `csel_matches` (function) `include/css_select.h:169` `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id, int allow_pseudo_el, int...` -- True if *sel matches element *el against its ancestor chain. target_id (optional) is the URL fragment for :target...
- `csel_element_feature_bits` (function) `include/css_select.h:177` `unsigned long long csel_element_feature_bits(const css_element *e);` -- Ancestor filter. csel_element_feature_bits: the bits of one element's tag, id and classes (two bits per feature...
- `csel_anc_reject` (function) `include/css_select.h:178` `static inline int csel_anc_reject(const css_sel *sel, const css_element *el)`
- `conservative` (function) `include/css_select.h:185` `* Pure and conservative (anything unrecognised answers 1). A selector that answers 0 matches * from the element's...`
- `identifier` (function) `include/css_select.h:191` `* A selector identifier (tag, .class, #id) is read with CSS escapes decoded * (`.md\:flex` is the class "md:flex")...`
- `csel_emit_utf8` (function) `include/css_select.h:203` `size_t csel_emit_utf8(unsigned int cp, char *out);`
- `csel_unescape` (function) `include/css_select.h:205` `void csel_unescape(char *dst, size_t cap, const char *src, size_t n);` -- A selector identifier (tag, .class, #id) is read with CSS escapes decoded (`.md\:flex` is the class "md:flex") and...
- `csel_escape_len` (function) `include/css_select.h:207` `size_t csel_escape_len(const char *s, size_t i, size_t b);` -- does not fit is FOLDED: its first CSEL_FOLD_PREFIX bytes, CSEL_FOLD_MARK (a byte no identifier contains) and 16 hex...
- `csel_ident_fold` (function) `include/css_select.h:209` `void csel_ident_fold(const char *src, size_t len, char *dst);` -- csel_ident_eq folds the element's token the same way, so a CSS Modules name such as...
- `csel_ident_eq` (function) `include/css_select.h:211` `int csel_ident_eq(const char *stored, const char *tok, size_t tlen);` -- instead of being truncated and never matching. #define CSEL_FOLD_PREFIX   40u #define CSEL_FOLD_MARK     '\x1f'...
- `csel_read_ident` (function) `include/css_select.h:214` `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower);` -- Reads an identifier at s[*ip] (escapes decoded, non-ASCII kept, lowercased when * lower != 0) into dst (CSS_TOK_MAX).
- `csel_decl_end` (function) `include/css_select.h:219` `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace);` -- Index of the ';' ending the declaration that starts at s[i] (or of a '}' when stop_brace), or b: separators inside...
- `csel_lower_ch` (function) `include/css_select.h:223` `static inline char csel_lower_ch(char c)`
- `csel_ci_eq` (function) `include/css_select.h:227` `static inline int csel_ci_eq(const char *a, const char *b)`
- `csel_span_eq` (function) `include/css_select.h:236` `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)` -- static inline char csel_lower_ch(char c) { return (c >= 'A' && c <= 'Z') ?
- `csel_substr` (function) `include/css_select.h:247` `static inline int csel_substr(const char *hay, const char *needle, int ci)` -- Substring test (used both to drop any value carrying url() — always ci — and by * the attribute `*=` operator).
- `csel_ident_ch` (function) `include/css_select.h:255` `static inline int csel_ident_ch(char c)`

## include/css_text.h
Depends on: `include/css_decl.h`
Imported by: `src/css.c`, `src/css_text.c`, `tests/test_css_text.c`
- `ct_interp_fontfamily` (function) `include/css_text.h:10` `int ct_interp_fontfamily(const char *v);`
- `ct_interp_texttransform` (function) `include/css_text.h:11` `int ct_interp_texttransform(const char *v);`
- `ct_interp_opacity` (function) `include/css_text.h:12` `int ct_interp_opacity(const char *v);`
- `ct_interp_valign` (function) `include/css_text.h:13` `int ct_interp_valign(const char *v);`
- `ct_expand_valign` (function) `include/css_text.h:14` `int ct_expand_valign(const char *val, css_decl *dst, int cap);`
- `ct_interp_transition_property` (function) `include/css_text.h:15` `int ct_interp_transition_property(const char *v);`
- `ct_interp_whitespace` (function) `include/css_text.h:16` `int ct_interp_whitespace(const char *v);`
- `ct_interp_tabsize` (function) `include/css_text.h:17` `int ct_interp_tabsize(const char *v);`
- `ct_interp_textdeco_style` (function) `include/css_text.h:18` `int ct_interp_textdeco_style(const char *v);`
- `ct_interp_textdeco_thickness` (function) `include/css_text.h:19` `int ct_interp_textdeco_thickness(const char *v);`
- `ct_interp_aspect_ratio` (function) `include/css_text.h:20` `int ct_interp_aspect_ratio(const char *v, int *num, int *den);`
- `ct_interp_direction` (function) `include/css_text.h:21` `int ct_interp_direction(const char *v);`
- `ct_interp_liststyle` (function) `include/css_text.h:22` `int ct_interp_liststyle(const char *v);`
- `ct_interp_spacing` (function) `include/css_text.h:23` `int ct_interp_spacing(const char *v, int *out);`
- `ct_emit_spacing` (function) `include/css_text.h:24` `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val);`
- `ct_expand_shadow` (function) `include/css_text.h:25` `int ct_expand_shadow(const char *val, css_decl *dst, int cap);`

## include/css_values.h
Imported by: `gui/browser_ui.c`, `src/css.c`, `src/css_box.c`, `src/css_gradient.c`, `src/css_text.c`, `src/css_values.c`, `tests/test_css_values.c`
- `cv_parse_color` (function) `include/css_values.h:12` `int cv_parse_color(const char *v);`
- `cv_interp_color` (function) `include/css_values.h:13` `int cv_interp_color(const char *v);`
- `cv_color_ok` (function) `include/css_values.h:14` `int cv_color_ok(int c);`
- `cv_bg_alpha_of` (function) `include/css_values.h:15` `int cv_bg_alpha_of(const char *v);`
- `cv_filter_scale` (function) `include/css_values.h:20` `double cv_filter_scale(int pct);` -- The multiplier a filter() brightness/contrast/saturate percentage means (150 -> 1.5).
- `cv_parse_color_t7` (function) `include/css_values.h:24` `int cv_parse_color_t7(const char *v);` -- cv_parse_color with the color's alpha as TRANSPARENCY in bits 24..30 (0 opaque, 127 clear): an opaque color is...
- `black` (function) `include/css_values.h:27` `* transparent black (127 << 24) -- text that paints nothing, not an absent * value. CC_COLOR_CURRENT and -1...`
- `cv_interp_bg` (function) `include/css_values.h:30` `int cv_interp_bg(const char *v);`


Next: [API_p4.md](API_p4.md)
