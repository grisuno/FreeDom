# API (page 3 of 9)
Previous: [API_p2.md](API_p2.md)

## gui/browser_ui.c (continued)
                            ...` -- .enter = data_device_enter, .leave = data_device_leave, .motion = data_device_motion, .drop = data_device_drop...
- `data_source_target` (function) `gui/browser_ui.c:14927` `static void data_source_target(void *d, struct wl_data_source *s, const char *m)`
- `freebug_copy_console` (function) `gui/browser_ui.c:14939` `static void freebug_copy_console(browser_window *w)` -- Formats the entire Freebug console buffer and places it on the Wayland clipboard, so the user can paste the...
- `loop` (function) `gui/browser_ui.c:14988` `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately...`
- `insert_pasted_text` (function) `gui/browser_ui.c:14997` `static void insert_pasted_text(browser_window *w, const char *text, size_t len)` -- Inserts pasted bytes into whichever text target currently has focus (page input, User-Agent box, or the URL bar).
- `clipboard_copy` (function) `gui/browser_ui.c:15061` `static void clipboard_copy(browser_window *w)` -- Ctrl+C: copy the focused field's text (or, with nothing focused, the page address) * to the clipboard by owning a...
- `keyboard_keymap` (function) `gui/browser_ui.c:15109` `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...`
- `keyboard_enter` (function) `gui/browser_ui.c:15130` `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...`
- `keyboard_leave` (function) `gui/browser_ui.c:15137` `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)`
- `key_sym_to_js_key` (function) `gui/browser_ui.c:15145` `static const char *key_sym_to_js_key(xkb_keysym_t sym)` -- Maps an xkb keysym to a JS event.key string.
- `key_sym_to_keycode` (function) `gui/browser_ui.c:15171` `static int key_sym_to_keycode(xkb_keysym_t sym)` -- Maps an xkb keysym to a JS keyCode number.
- `dispatch_js_event` (function) `gui/browser_ui.c:15196` `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...` -- Dispatches a JS DOM event to the worker for the given node_id.
- `handle_key_press` (function) `gui/browser_ui.c:15254` `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...` -- Performs the effect of a single key press.
- `key_is_repeatable` (function) `gui/browser_ui.c:15584` `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)` -- Keys whose held-down auto-repeat is safe and useful: text editing, cursor motion and scrolling.
- `key_repeat_arm` (function) `gui/browser_ui.c:15600` `static void key_repeat_arm(browser_window *w, uint32_t key)` -- Arms the repeat timer for key: first fire after repeat_delay ms, then every * 1/repeat_rate s.
- `key_repeat_stop` (function) `gui/browser_ui.c:15613` `static void key_repeat_stop(browser_window *w)` -- 1/repeat_rate s.
- `key_repeat_fire` (function) `gui/browser_ui.c:15624` `static void key_repeat_fire(browser_window *w)` -- Re-fires the currently held key.
- `keyboard_key` (function) `gui/browser_ui.c:15638` `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...`
- `keyboard_modifiers` (function) `gui/browser_ui.c:15678` `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...`
- `keyboard_repeat_info` (function) `gui/browser_ui.c:15687` `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)`
- `seat_caps` (function) `gui/browser_ui.c:15706` `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
- `seat_name` (function) `gui/browser_ui.c:15717` `static void seat_name(void *d, struct wl_seat *s, const char *name)`
- `registry_global` (function) `gui/browser_ui.c:15724` `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
- `registry_remove` (function) `gui/browser_ui.c:15744` `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
- `ui_run_browser` (function) `gui/browser_ui.c:15754` `ui_status ui_run_browser(const char *start_url)`
- `saving` (function) `gui/browser_ui.c:15769` `* disables saving (never clobber);`
- `redraws` (function) `gui/browser_ui.c:15848` `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A...`
- `applies` (function) `gui/browser_ui.c:15918` `* persisted choice applies (prefs_parse already clamped it to a valid mode). */ const char *js_env =...`
- `flow` (function) `gui/browser_ui.c:16127` `* flow (counting them starved aplay). A video frame read while * overdue overwrites the held slot (standard player...`
- `cost` (function) `gui/browser_ui.c:16149` `* measured cost (floor 33 ms = the existing ~30 fps ceiling):
             * cheap pages paint at...`

## gui/browser_ui_internal.h
Depends on: `include/freedom_config.h`
Imported by: `gui/browser_ui.c`, `gui/bui_theme.c`
- `set_rgb` (function) `gui/browser_ui_internal.h:106` `void set_rgb(cairo_t *cr, ui_rgb c);` -- /* Selectable palettes for the options menu. typedef enum ui_theme_mode { UI_THEME_LIGHT = 0, UI_THEME_DARK...

## gui/bui_theme.c
Depends on: `gui/browser_ui_internal.h`, `include/css_color.h`
- `ui_theme_default` (function) `gui/bui_theme.c:14` `ui_theme ui_theme_default(void)` -- bui_theme — presentation palettes for the Wayland/Cairo GUI.
- `ui_theme_dark` (function) `gui/bui_theme.c:84` `ui_theme ui_theme_dark(void)` -- Dark reading palette.
- `ui_theme_sepia` (function) `gui/bui_theme.c:129` `ui_theme ui_theme_sepia(void)` -- Sepia reading palette: warm paper background and dark-brown ink, easier on the eyes for long-form text.
- `ui_theme_for` (function) `gui/bui_theme.c:171` `ui_theme ui_theme_for(int mode)` -- t.menu_bg        = (ui_rgb){ 0.95, 0.90, 0.80 }; t.menu_border    = (ui_rgb){ 0.55, 0.46, 0.32 }; t.menu_text      =...
- `rgb_from_packed` (function) `gui/bui_theme.c:180` `ui_rgb rgb_from_packed(int packed)` -- t.scrollbar_thumb_hot = (ui_rgb){ 0.44, 0.35, 0.22 }; return t; } /* The single place that maps the theme mode to a...
- `set_rgb` (function) `gui/bui_theme.c:185` `void set_rgb(cairo_t *cr, ui_rgb c)`

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
Imported by: `include/secure_fetch.h`, `src/anti_fp.c`, `src/js_env.c`, `src/secure_fetch.c`, `src/tab.c`, `tests/test_anti_fp.c`
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

## include/box_style.h
Depends on: `include/css.h`
Imported by: `gui/browser_ui.c`, `include/box_tree.h`, `src/box_style.c`, `src/box_tree.c`, `src/dom_debug.c`, `src/page_view.c`, `src/render_doc.c`, `tests/test_box_style.c`, `tests/test_dom_debug.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`
- `box` (function) `include/box_style.h:115` `* in_list nonzero when the block sits inside a list item: it then takes * the <li> box (zero margin), keeping items...`
- `BX_TROLE_NONE` (function) `include/box_style.h:144` `* BX_TROLE_NONE (an unrecognised element joins no table -- fail closed). */ bx_table_role bx_table_role_of(const...`
- `bx_display_name` (function) `include/box_style.h:156` `const char *bx_display_name(bx_display d);` -- Stable, short English name of a display type for structured/agent output.
- `bx_width_cap` (function) `include/box_style.h:172` `double bx_width_cap(int w_px, int w_pct, double avail_w);` -- Effective width cap combining the px cap (w_px, 0 = none) with a symbolic per-mille cap (w_pct, 0 = none; Hito 32)...
- `bx_width_cap2` (function) `include/box_style.h:177` `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w);` -- The used width cap of an element: the tighter of its `width` (w_px, w_pct) and its `max-width` (mw_px, mw_pct), each...
- `bx_replaced_box` (function) `include/box_style.h:196` `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den, double avail_w, double *out_w, double *out_h);` -- CSS Sizing 4 section 4: when one axis is definite and an aspect-ratio is present, the ratio supplies the other.
- `bx_border_box_h` (function) `include/box_style.h:210` `double bx_border_box_h(double declared_h, int border_box, double pad_t, double pad_b, double bord_t, double bord_b);` -- Border-box height for a DECLARED height under box-sizing (CSS 2.1 10.6.3, CSS Box Sizing 3 section 4).
- `page` (function) `include/box_style.h:214` `* instead of letting it extend the page (CSS 2.1 section 10.7 + 11.1.1). That * is the case unless BOTH overflow...`
- `bx_lp_px` (function) `include/box_style.h:236` `double bx_lp_px(int px_val, int pct_pm, double basis);` -- half plus pct_pm per-mille of `basis`.
- `bx_content_cap` (function) `include/box_style.h:244` `double bx_content_cap(double width_cap, int border_box, double pad_l, double pad_r, double bord_l, double bord_r);` -- Content-width cap adjusted for box-sizing (2026-07-11).
- `bx_background_layer` (function) `include/box_style.h:277` `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h, double *out_x, double *out_y);`

## include/box_tree.h
Depends on: `include/box_style.h`, `include/flex_layout.h`, `include/page_view.h`
Imported by: `gui/browser_ui.c`, `src/box_tree.c`, `src/page_view.c`, `src/tab.c`, `tests/test_box_tree.c`
- `closed` (function) `include/box_tree.h:34` `* fails closed (BT_ERR_RANGE) instead of overflowing the stack. */ #define BT_MAX_DEPTH 64u #define BT_MAX_CHILDREN...`
- `one` (function) `include/box_tree.h:81` `* of forcing them all onto one (flex-wrap);`
- `line` (function) `include/box_tree.h:97` `* its line (already resolved from align-self / the * container's align-items by the caller). */ /* this node as a...`
- `node` (function) `include/box_tree.h:144` `* node (x/y parent-relative, w/h border-box). display:none nodes get a zero rect and * take no space. The caller...`
- `flow` (function) `include/box_tree.h:183` `* position is where the box would have started in flow (CSS 2.2 §10.3.7/§10.6.4);`
- `bottom` (function) `include/box_tree.h:190` `* bottom with auto top still anchors bottom (R8). * `placed` (may be NULL) marks which boxes have an in-flow rect in...`
- `placed` (function) `include/box_tree.h:197` `* box counts as placed (legacy behaviour). * bt_resolve_positioning delegates with NULL arrays (legacy behaviour)....`
- `bt_box_hidden` (function) `include/box_tree.h:215` `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid);` -- Stage 2b visibility gate: 1 when the box at `bid` or any ancestor on the parent_id chain has visibility...
- `bt_oof_anchor` (function) `include/box_tree.h:229` `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid);` -- Stage 2d out-of-flow subtree classification (spec/box_engine.md).
- `bt_oof_root` (function) `include/box_tree.h:230` `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid);`
- `insets` (function) `include/box_tree.h:234` `* minus the two insets (px half + per-mille half of cb), an auto/unset inset * counting 0, never below 0. *both (may...`
- `bt_containing_block` (function) `include/box_tree.h:244` `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i, const double *box_x, const double *box_y...` -- The containing block of box i as the positioning solver resolves it: the viewport for FIXED (and for ABSOLUTE with...

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

## include/compositor.h
Imported by: `gui/browser_ui.c`, `src/box_tree.c`, `src/compositor.c`, `tests/test_compositor.c`
- `cx_forms_stacking_context` (function) `include/compositor.h:60` `int cx_forms_stacking_context(const cx_style *s);` -- Does this box establish a stacking context?
- `cx_item_compare` (function) `include/compositor.h:80` `int cx_item_compare(const cx_item *a, const cx_item *b);` -- Total paint order: layer ascending, then z-index ascending (auto == 0), then document order ascending.
- `cx_sort` (function) `include/compositor.h:84` `void cx_sort(cx_item *items, size_t n);` -- Stable in-place sort of `items` into paint order (uses cx_item_compare).

## include/css.h
Depends on: `include/css_color.h`
Imported by: `fuzz/fuzz_css.c`, `gui/browser_ui.c`, `include/box_style.h`, `include/css_chain.h`, `include/css_decl.h`, `include/css_select.h`, `include/page_view.h`, `src/box_tree.c`, `src/compositor.c`, `src/css.c`, `src/css_box.c`, `src/css_length.c`, `src/css_text.c`, `src/css_values.c`, `src/dom_debug.c`, `src/page_view.c`, `src/render_doc.c`, `src/tab.c`, `src/text_shape.c`, `tests/test_box_tree.c`, `tests/test_compositor.c`, `tests/test_css.c`, `tests/test_css_drops.c`, `tests/test_css_gradient.c`, `tests/test_css_length.c`, `tests/test_css_text.c`, `tests/test_css_values.c`, `tests/test_dom_debug.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`, `tests/test_tab.c`, `tests/test_text_shape.c`
- `verbatim` (function) `include/css.h:79` `* the quoted row strings verbatim (flex_layout parses them);`
- `POINTER` (function) `include/css.h:207` `* POINTER (shows the hand cursor already used for links) from every other value * (shows the default arrow);`
- `translate` (function) `include/css.h:796` `* translate()/translateX()/translateY();`
- `scaleY` (function) `include/css.h:797` `* scaleY() as a PERCENT of identity (100 = scale(1), matching font_scale's * convention);`
- `declared` (function) `include/css.h:801` `* function was not declared (identity: 0 offset / 100% scale / 0deg). * Percentage translate arguments are not...`
- `element` (function) `include/css.h:806` `* so two different rules matching the same element (e.g. one setting * translate, a more specific one setting...`
- `slots` (function) `include/css.h:813` `* parse time into ALL seven slots (singular matrices fail closed);`
- `palette` (function) `include/css.h:968` `* so an inactive theme * palette (a dark palette in a light render) can never clobber the active one. *...`
- `css_free` (function) `include/css.h:1018` `void css_free(css_sheet *s);` -- As css_parse_scoped, plus the drop sink. log == NULL is exactly css_parse_scoped: same path, same sheet, same cost.
- `order` (function) `include/css.h:1021` `* cascade order (specificity, then document order), then the element's own * inline_style (which wins)....`
- `inherited_px` (function) `include/css.h:1126` `* whose PARENT computes to inherited_px (<= 0 = unknown -> the CSS initial). * * Exported because the caller that...`
- `css_font_face_count` (function) `include/css.h:1142` `size_t css_font_face_count(const css_sheet *sheet);` -- Web font access: returns the number of @font-face declarations parsed into the sheet, and copies the i-th...
- `css_font_face_at` (function) `include/css.h:1143` `int css_font_face_at(const css_sheet *sheet, size_t i, char *family, size_t fam_cap, char *src_url, size_t url_cap);`
- `css_resolve_anim_keyframes` (function) `include/css.h:1151` `void css_resolve_anim_keyframes(css_style *s, const css_sheet *sheet);` -- Resolve @keyframes: scans sheet->keyframes[] for a name matching s->anim_name (first-char match).

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
- `cb_lp_can_be_nonneg` (function) `include/css_box.h:26` `int cb_lp_can_be_nonneg(int px_val, int pct_pm);`
- `cb_next_ws_token` (function) `include/css_box.h:27` `int cb_next_ws_token(const char **p, char *tok, size_t cap);`
- `cb_interp_align` (function) `include/css_box.h:28` `int cb_interp_align(const char *v);`
- `cb_interp_fontsize_ex` (function) `include/css_box.h:29` `int cb_interp_fontsize_ex(const char *v, int *abs_out);`
- `cb_interp_lineheight` (function) `include/css_box.h:30` `int cb_interp_lineheight(const char *v);`
- `cb_interp_weight` (function) `include/css_box.h:31` `int cb_interp_weight(const char *v);`
- `cb_interp_style` (function) `include/css_box.h:32` `int cb_interp_style(const char *v);`
- `cb_interp_textdeco` (function) `include/css_box.h:33` `int cb_interp_textdeco(const char *v);`
- `cb_interp_display` (function) `include/css_box.h:34` `int cb_interp_display(const char *v);`
- `cb_interp_gap` (function) `include/css_box.h:35` `int cb_interp_gap(const char *v);`
- `cb_interp_justify` (function) `include/css_box.h:36` `int cb_interp_justify(const char *v);`
- `cb_interp_gridcols` (function) `include/css_box.h:37` `int cb_interp_gridcols(const char *v);`
- `cb_expand_grid_template_cols` (function) `include/css_box.h:38` `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap);`

## include/css_chain.h
Depends on: `include/css.h`, `include/css_select.h`
Imported by: `src/css_chain.c`, `src/dom.c`, `src/page_view.c`
- `cch_element_matches` (function) `include/css_chain.h:69` `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel);` -- Nonzero iff the parsed selector *sel matches element `el`, built against the same bounded ancestor/sibling/attribute...
- `box` (function) `include/css_chain.h:72` `* generated box (css_resolve_pseudo) against the same element context. * font_size is el's own COMPUTED font-size...`

## include/css_color.h
Imported by: `gui/browser_ui.c`, `gui/bui_theme.c`, `gui/svg_paint.c`, `include/css.h`, `src/css.c`, `src/css_box.c`, `src/css_color.c`, `src/css_gradient.c`, `src/css_text.c`, `src/css_values.c`, `src/page_view.c`, `src/svg_render.c`, `tests/test_css_color.c`
- `cc_pack` (function) `include/css_color.h:49` `int cc_pack(cc_rgb c);` -- Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color"...

## include/css_decl.h
Depends on: `include/css.h`, `include/css_select.h`
Imported by: `include/css_box.h`, `include/css_gradient.h`, `include/css_text.h`, `src/css.c`, `src/css_box.c`, `src/css_gradient.c`, `src/css_text.c`, `src/css_values.c`, `tests/test_css_box.c`, `tests/test_css_text.c`
- `order` (function) `include/css_decl.h:44` `* The four margin slots are contiguous in CSS shorthand order (top,right,bottom, * left);`
- `contiguous` (function) `include/css_decl.h:59` `* contiguous (dx,dy,color) so expand_shadow writes them as a group. */ P_FONTFAMILY, P_TEXTTRANSFORM...`

## include/css_gradient.h
Depends on: `include/css_decl.h`
Imported by: `src/css.c`, `src/css_gradient.c`, `tests/test_css_gradient.c`
- `cg_expand_bg_image` (function) `include/css_gradient.h:11` `int cg_expand_bg_image(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...`
- `cg_expand_background` (function) `include/css_gradient.h:13` `int cg_expand_background(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...`

## include/css_length.h
Imported by: `src/css.c`, `src/css_box.c`, `src/css_gradient.c`, `src/css_length.c`, `src/css_mq.c`, `src/css_text.c`, `src/css_values.c`, `src/page_view.c`, `tests/test_css_length.c`
- `prelude` (function) `include/css_length.h:99` `* correct context for a media query prelude (whose `em` is defined to use the * initial font size, never the...`
- `cl_unit_is_font_relative` (function) `include/css_length.h:157` `* cl_unit_is_font_relative() draws. */ /* * Re-fits a resolved length to a different font-size: * * used = px + em *...`
- `cl_unit_font_ratio` (function) `include/css_length.h:182` `double cl_unit_font_ratio(const char *unit, size_t unit_len);` -- How many px one of `unit` is worth per 1px of font-size -- the per-unit derivative behind cl_lp.em.
- `here` (function) `include/css_length.h:186` `* Every input cl_resolve accepts resolves identically here (with has_pct 0);`
- `length` (function) `include/css_length.h:206` `* * A basis that is not a usable length (negative, zero, non-finite) contributes * nothing, but the absolute...`
- `cl_number` (function) `include/css_length.h:230` `int cl_number(const char *s, double *out, const char **endp);` -- Returns 1 on success, writing *out and pointing *endp at the first unconsumed character; 0 if there is no number there.
- `cl_is_length_unit` (function) `include/css_length.h:246` `int cl_is_length_unit(const char *unit, size_t unit_len);` -- Non-zero when `unit` names a <length> unit at all (any of the three families * plus px).

## include/css_mq.h
Imported by: `src/css.c`, `src/css_mq.c`, `tests/test_css_mq.c`
- `cmq_matches` (function) `include/css_mq.h:28` `int cmq_matches(const char *s, size_t len, const cmq_env *env);` -- 1 iff the media query list s[0,len) matches env; malformed/unknown parts fail * closed.

## include/css_select.h
Depends on: `include/css.h`
Imported by: `fuzz/fuzz_css.c`, `include/css_chain.h`, `include/css_decl.h`, `src/css.c`, `src/css_atrule.c`, `src/css_box.c`, `src/css_chain.c`, `src/css_gradient.c`, `src/css_select.c`, `src/css_text.c`, `src/css_values.c`, `src/css_vars.c`, `src/dom.c`, `tests/test_css.c`
- `csel_parse` (function) `include/css_select.h:150` `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel);` -- Parses the complex selector s[a,b) into *sel (spec computed; order/rule left to * the caller).
- `csel_matches` (function) `include/css_select.h:159` `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id, int allow_pseudo_el, int...` -- True if *sel matches element *el against its ancestor chain. target_id (optional) is the URL fragment for :target...
- `identifier` (function) `include/css_select.h:163` `* A selector identifier (tag, .class, #id) is read with CSS escapes decoded * (`.md\:flex` is the class "md:flex")...`
- `csel_emit_utf8` (function) `include/css_select.h:175` `size_t csel_emit_utf8(unsigned int cp, char *out);`
- `csel_unescape` (function) `include/css_select.h:177` `void csel_unescape(char *dst, size_t cap, const char *src, size_t n);` -- A selector identifier (tag, .class, #id) is read with CSS escapes decoded (`.md\:flex` is the class "md:flex") and...
- `csel_escape_len` (function) `include/css_select.h:179` `size_t csel_escape_len(const char *s, size_t i, size_t b);` -- does not fit is FOLDED: its first CSEL_FOLD_PREFIX bytes, CSEL_FOLD_MARK (a byte no identifier contains) and 16 hex...
- `csel_ident_fold` (function) `include/css_select.h:181` `void csel_ident_fold(const char *src, size_t len, char *dst);` -- csel_ident_eq folds the element's token the same way, so a CSS Modules name such as...
- `csel_ident_eq` (function) `include/css_select.h:183` `int csel_ident_eq(const char *stored, const char *tok, size_t tlen);` -- instead of being truncated and never matching. #define CSEL_FOLD_PREFIX   40u #define CSEL_FOLD_MARK     '\x1f'...
- `csel_read_ident` (function) `include/css_select.h:186` `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower);` -- Reads an identifier at s[*ip] (escapes decoded, non-ASCII kept, lowercased when * lower != 0) into dst (CSS_TOK_MAX).
- `csel_decl_end` (function) `include/css_select.h:191` `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace);` -- Index of the ';' ending the declaration that starts at s[i] (or of a '}' when stop_brace), or b: separators inside...
- `csel_lower_ch` (function) `include/css_select.h:195` `static inline char csel_lower_ch(char c)`
- `csel_ci_eq` (function) `include/css_select.h:199` `static inline int csel_ci_eq(const char *a, const char *b)`
- `csel_span_eq` (function) `include/css_select.h:208` `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)` -- static inline char csel_lower_ch(char c) { return (c >= 'A' && c <= 'Z') ?
- `csel_substr` (function) `include/css_select.h:219` `static inline int csel_substr(const char *hay, const char *needle, int ci)` -- Substring test (used both to drop any value carrying url() — always ci — and by * the attribute `*=` operator).
- `csel_ident_ch` (function) `include/css_select.h:227` `static inline int csel_ident_ch(char c)`

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
Imported by: `src/css.c`, `src/css_box.c`, `src/css_gradient.c`, `src/css_text.c`, `src/css_values.c`, `tests/test_css_values.c`
- `cv_parse_color` (function) `include/css_values.h:12` `int cv_parse_color(const char *v);`
- `cv_interp_color` (function) `include/css_values.h:13` `int cv_interp_color(const char *v);`
- `cv_color_ok` (function) `include/css_values.h:14` `int cv_color_ok(int c);`
- `cv_bg_alpha_of` (function) `include/css_values.h:15` `int cv_bg_alpha_of(const char *v);`
- `cv_interp_bg` (function) `include/css_values.h:16` `int cv_interp_bg(const char *v);`

## include/css_vars.h
Imported by: `src/css.c`, `src/css_vars.c`, `src/page_view.c`, `tests/test_css.c`, `tests/test_css_vars.c`
- `name` (function) `include/css_vars.h:62` `* name (last declaration wins). Returns 1 when stored, 0 when dropped: a name that * is not "--" + at least one...`
- `cvr_get` (function) `include/css_vars.h:69` `const char *cvr_get(const cvr_table *t, const char *name, size_t nlen);` -- The stored value for name[0,nlen), or NULL.
- `cvr_count` (function) `include/css_vars.h:71` `size_t cvr_count(const cvr_table *t);`
- `cvr_reset` (function) `include/css_vars.h:75` `void cvr_reset(cvr_table *t);` -- Frees every stored string and empties the table, keeping its arrays for reuse. * NULL-safe.
- `cvr_free` (function) `include/css_vars.h:78` `void cvr_free(cvr_table *t);` -- Frees every stored string and empties the table, keeping its arrays for reuse. * NULL-safe. void cvr_reset(cvr_table...
- `cvr_collect_decls` (function) `include/css_vars.h:83` `void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b);` -- Scans the declaration span s[a,b) for `--ident : value` pairs and stores each (a trailing !important is stripped).
- `declaration` (function) `include/css_vars.h:91` `* then drops the whole declaration (CSS Variables 1: invalid at computed time). */ int cvr_resolve(const char *val...`
- `cvr_lookup` (function) `include/css_vars.h:96` `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen);` -- The value name[0,nlen) has in scope sc (same lookup order as cvr_resolve), or * NULL.

## include/data_url.h
Imported by: `fuzz/fuzz_data_url.c`, `gui/browser_ui.c`, `src/data_url.c`, `src/render_doc.c`, `src/render_policy.c`, `src/tab.c`, `tests/test_data_url.c`
- `allocation` (function) `include/data_url.h:21` `* * du_base64_payload does no allocation (it only slices the caller's url string);`
- `du_is_data_url` (function) `include/data_url.h:46` `int du_is_data_url(const char *url);` -- 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation...
- `closed` (function) `include/data_url.h:59` `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/out/out_len == NULL (with b64_len !=...`

## include/disk_store.h
Depends on: `include/local_store.h`
Imported by: `src/disk_store.c`, `src/profile.c`, `tests/test_disk_store.c`
- `ds_free` (function) `include/disk_store.h:47` `void ds_free(uint8_t *buf, size_t len);` -- Reads and decrypts path.

## include/dom.h
Depends on: `include/html_parse.h`
Imported by: `fuzz/fuzz_dom.c`, `fuzz/fuzz_js_dom.c`, `include/js_dom.h`, `include/js_geom.h`, `include/page_view.h`, `src/dom.c`, `src/html_parse.c`, `src/js_dom.c`, `src/js_dom_internal.h`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/page_view.c`, `src/tab.c`, `tests/test_dom.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_page_view.c`
- `dom_free` (function) `include/dom.h:48` `void dom_free(dom_index *idx);` -- Builds the index over an already-parsed document. doc must outlive *out. doc == NULL / out == NULL =>...
- `dom_node_count` (function) `include/dom.h:51` `size_t dom_node_count(const dom_index *idx);` -- Builds the index over an already-parsed document. doc must outlive *out. doc == NULL / out == NULL =>...
- `count` (function) `include/dom.h:59` `* match count (which may exceed cap, so the caller can size a buffer). */ size_t dom_get_by_tag(const dom_index...`
- `dom_get_by_class` (function) `include/dom.h:62` `size_t dom_get_by_class(const dom_index *idx, const char *cls, dom_node_id *out, size_t cap);`
- `dom_matches` (function) `include/dom.h:91` `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector);` -- Writes up to cap matching ids (document order) into out; returns the total * match count (may exceed cap, so the...
- `dom_document_position` (function) `include/dom.h:101` `size_t dom_document_position(const dom_index *idx, dom_node_id node);` -- Nearest element at or above node matching the selector list, or DOM_NODE_NONE * (Element.closest). dom_node_id...
- `dom_precedes` (function) `include/dom.h:104` `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);` -- Nearest element at or above node matching the selector list, or DOM_NODE_NONE * (Element.closest). dom_node_id...
- `dom_tag_name` (function) `include/dom.h:118` `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);` -- int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b); /* Node at the given document-order position...
- `dom_get_attribute` (function) `include/dom.h:121` `const char *dom_get_attribute(const dom_index *idx, dom_node_id node, const char *name, size_t *len);` -- dom_node_id dom_node_at(const dom_index *idx, size_t position); /* --- navigation (element-only; DOM_NODE_NONE at...
- `dom_attribute_names` (function) `include/dom.h:128` `size_t dom_attribute_names(const dom_index *idx, dom_node_id node, const char **names, size_t *lens, size_t cap);` -- Qualified names of node's attributes, in document order, written to names[] (borrowed, valid while idx/doc are...
- `dom_text_content` (function) `include/dom.h:133` `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len);` -- Concatenated text content of node's subtree (borrowed, valid while idx/doc are * alive), or NULL. *len (optional)...
- `dom_document_title` (function) `include/dom.h:136` `const char *dom_document_title(const dom_index *idx, size_t *len);` -- Concatenated text content of node's subtree (borrowed, valid while idx/doc are * alive), or NULL. *len (optional)...
- `cycle` (function) `include/dom.h:164` `* Rejects a cycle (child being an ancestor of parent). Invalid handle / self / cycle * => DOM_ERR_NULL_ARG. */...`
- `parent` (function) `include/dom.h:191` `* child of parent (for the *_REF places) or an invalid handle => DOM_ERR_NULL_ARG. */ dom_status...`
- `dom_node_kind` (function) `include/dom.h:207` `int dom_node_kind(const dom_index *idx, dom_node_id node);` -- -- text and comment nodes (spec/dom.md 9) --- Character-data nodes get LAZY handles in the same arena: registered...
- `index` (function) `include/dom.h:223` `* stays valid in the index (not freed). Invalid handle / not-a-child => DOM_ERR_NULL_ARG. */ dom_status...`
- `length` (function) `include/dom.h:248` `* length (no children => an owned empty string). Uses a chain of fixed-size * blocks internally so there is no hard...`

## include/dom_debug.h
Depends on: `include/render_doc.h`
Imported by: `fuzz/fuzz_dom_debug.c`, `src/dom_debug.c`, `src/freedom.c`, `tests/test_dom_debug.c`
- `dd_format` (function) `include/dom_debug.h:36` `size_t dd_format(const rd_doc *doc, char *out, size_t cap);` -- Formats doc into out[0..cap) as a NUL-terminated, line-oriented dump (see the spec for the stable format).
- `dd_format_css` (function) `include/dom_debug.h:41` `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap);` -- CSS inspector: dumps every block with its FULL resolved css_style fields as a compact property list.

## include/download.h
Imported by: `fuzz/fuzz_download.c`, `gui/browser_ui.c`, `src/download.c`, `tests/test_download.c`
- `dl_should_download` (function) `include/download.h:43` `int dl_should_download(const char *content_type, const char *content_disposition);` -- 1 if the response should be saved (attachment, or a non-renderable media type), 0 if it should be rendered.
- `literal` (function) `include/download.h:47` `* a static string literal (never freed). */ const char *dl_ext_for_type(const char *content_type);`
- `DL_ERR_OVERFLOW` (function) `include/download.h:56` `* DL_ERR_OVERFLOW (out left empty). url/content_disposition NULL => absent. */ dl_status dl_pick_name(const char...`
- `basename` (function) `include/download.h:61` `* sanitized basename (a name still containing '/' is rejected => DL_ERR_OVERFLOW, * so the path can never escape...`

## include/flex_layout.h
Imported by: `include/box_tree.h`, `src/css.c`, `src/dom_debug.c`, `src/flex_layout.c`, `src/page_view.c`, `tests/test_dom_debug.c`, `tests/test_flex_layout.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`
- `size` (function) `include/flex_layout.h:60` `* content size (px);`
- `out` (function) `include/flex_layout.h:62` `* fx_result to out (caller-owned). n == 0 is a no-op (out may be NULL). */ fx_status fx_flex_line(const fx_item...`
- `fx_grid_cell` (function) `include/flex_layout.h:74` `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col);` -- Row and column of the index-th item placed row-major into ncols columns. * ncols == 0 yields row = col = 0...
- `fx_grid_area_hash` (function) `include/flex_layout.h:125` `unsigned fx_grid_area_hash(const char *name);` -- FNV-1a of a trimmed, case-sensitive CSS identifier; never returns 0 for a non-empty name (0 is reserved for "unnamed").
- `offset` (function) `include/flex_layout.h:143` `* offset (from the content start, clamped to >= 0) to out_x[n]. The band does NOT wrap * (v1): an item that would...`
- `required` (function) `include/flex_layout.h:156` `* out_row is required (NULL with n > 0 yields FX_ERR_NULL_ARG);`
- `widths` (function) `include/flex_layout.h:166` `* the OUTER widths (width + ml + mr, clamped >= 0, so a negative margin narrows * the slot and a positive one widens...`
- `FX_ERR_NULL_ARG` (function) `include/flex_layout.h:200` `* Returns FX_ERR_NULL_ARG (a required pointer NULL with n > 0), FX_ERR_RANGE * (negative h/avail, or n > FX_MAX_ITEMS);`
- `space` (function) `include/flex_layout.h:206` `* line order: positive free space (avail - sizes - gaps) is split equally among every * auto margin...`
- `fx_auto_min_size` (function) `include/flex_layout.h:235` `double fx_auto_min_size(double min_content, double basis, double author_min, int scroll_container);` -- min_content  the item's min-content size (its longest unbreakable word, or a replaced element's intrinsic size), in...
- `fx_justify_name` (function) `include/flex_layout.h:291` `const char *fx_justify_name(fx_justify j);` -- Stable, short English name of a justify mode for structured/agent output.
- `height` (function) `include/flex_layout.h:297` `* used height (h_out);`
- `win` (function) `include/flex_layout.h:314` `* margins win (both = centre, left only = end);`
- `fx_cross_offset` (function) `include/flex_layout.h:316` `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r);` -- Cross-axis (horizontal) offset of a column item of width w in avail px. auto margins win (both = centre, left only =...

## include/frame_clock.h
Imported by: `gui/browser_ui.c`, `src/frame_clock.c`, `tests/test_frame_clock.c`
- `fc_init` (function) `include/frame_clock.h:20` `void fc_init(fc_clock *c);`
- `fc_set_active` (function) `include/frame_clock.h:21` `void fc_set_active(fc_clock *c, int active);`
- `fc_needs_tick` (function) `include/frame_clock.h:22` `int fc_needs_tick(const fc_clock *c);`
- `fc_interval_ms` (function) `include/frame_clock.h:23` `int fc_interval_ms(const fc_clock *c);`

## include/freebug.h
Imported by: `fuzz/fuzz_freebug.c`, `gui/browser_ui.c`, `include/js_dom.h`, `include/tab.h`, `src/freebug.c`, `src/freedom.c`, `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/tab.c`, `tests/test_freebug.c`
- `fb_buffer_init` (function) `include/freebug.h:65` `void fb_buffer_init(fb_buffer *b);` -- A stored source name is truncated to this many bytes (NUL excluded).
- `truncated` (function) `include/freebug.h:69` `* A message longer than FB_MAX_ENTRY_BYTES is stored truncated (not dropped). A * dropped push raises b->overflow...`
- `copied` (function) `include/freebug.h:75` `* copied (truncated to FB_MAX_FILE_BYTES);`
- `fb_buffer_push_loc` (function) `include/freebug.h:78` `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len, const char *file, int line, int col);` -- As fb_buffer_push, but also records a source location. file (may be NULL) is copied (truncated to...
- `fb_buffer_reset` (function) `include/freebug.h:83` `void fb_buffer_reset(fb_buffer *b);` -- Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the * entry array allocation for reuse.
- `fb_buffer_free` (function) `include/freebug.h:86` `void fb_buffer_free(fb_buffer *b);` -- Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the * entry array allocation for reuse.
- `fb_buffer_count` (function) `include/freebug.h:89` `size_t fb_buffer_count(const fb_buffer *b);` -- Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the * entry array allocation for reuse.
- `fb_buffer_at` (function) `include/freebug.h:92` `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i);` -- Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the * entry array allocation for reuse.
- `fb_level_name` (function) `include/freebug.h:96` `const char *fb_level_name(int level);` -- A stable lowercase level name ("log"/"info"/"warn"/"error"/"debug"); an * out-of-range level clamps to "log".

## include/hls.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/hls.c`, `tests/test_hls.c`
- `hls_select_variant` (function) `include/hls.h:65` `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h);` -- Selects the best variant from a multi-variant playlist.
- `resolved` (function) `include/hls.h:68` `* Writes the absolute URL into resolved (bounded by resolved_sz). Returns the * written length, or 0 on failure. */...`
- `hls_playlist_free` (function) `include/hls.h:74` `void hls_playlist_free(hls_playlist *pl);` -- Resolves a (possibly relative) segment URL against the playlist base URL.

## include/hostblock.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/hostblock.c`, `tests/test_hostblock.c`
- `hb_new` (function) `include/hostblock.h:49` `hb_set *hb_new(void);` -- } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on...
- `hb_free` (function) `include/hostblock.h:52` `void hb_free(hb_set *s);` -- HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) }...
- `walked` (function) `include/hostblock.h:65` `* walked (the host, then without its first label, ...): any suffix on the allowlist * => HB_ALLOW (allow wins...`
- `hb_is_allowlisted` (function) `include/hostblock.h:75` `int hb_is_allowlisted(const hb_set *s, const char *host);` -- 1 iff a domain suffix of host is explicitly on the allowlist (covers subdomains), else 0.
- `hb_count` (function) `include/hostblock.h:79` `size_t hb_count(const hb_set *s, hb_list list);` -- Number of unique domains on the given list (for tests/diagnostics).

## include/hostedit.h
Imported by: `gui/browser_ui.c`, `src/hostedit.c`, `tests/test_hostedit.c`
- `he_text_has_host` (function) `include/hostedit.h:46` `int he_text_has_host(const char *text, const char *host);` -- Returns 1 if text (the body of a hosts-format file) already lists host as a domain token on a non-comment line...
- `he_suggest` (function) `include/hostedit.h:55` `int he_suggest(const char *text, const char *query, char results[][HE_MAX_HOST + 1], int max);` -- Omnibar autocomplete: treats allow.conf (a hosts-format text) as a favorites list.

## include/html_parse.h
Imported by: `fuzz/fuzz_dom.c`, `fuzz/fuzz_dom_debug.c`, `fuzz/fuzz_html_parse.c`, `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_page_view.c`, `gui/freedom_view.c`, `include/dom.h`, `include/page_view.h`, `src/dom.c`, `src/freedom.c`, `src/html_parse.c`, `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/page_view.c`, `src/renderer.c`, `src/tab.c`, `tests/test_dom.c`, `tests/test_html_parse.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_page_view.c`
- `dropped` (function) `include/html_parse.h:47` `* dropped (not executed). */ #define HP_MAX_SCRIPTS ((size_t)4096) /* Returns a configuration with the secure...`
- `cfg` (function) `include/html_parse.h:57` `* policy in cfg (cfg == NULL => secure defaults). No script is ever executed. * html == NULL or out == NULL =>...`
- `hp_element_count` (function) `include/html_parse.h:63` `size_t hp_element_count(const hp_document *doc);` -- Parses untrusted HTML into an inert document and applies the sanitisation policy in cfg (cfg == NULL => secure...
- `hp_script_count` (function) `include/html_parse.h:64` `size_t hp_script_count(const hp_document *doc);`
- `hp_event_handler_count` (function) `include/html_parse.h:65` `size_t hp_event_handler_count(const hp_document *doc);`
- `hp_extract_text` (function) `include/html_parse.h:69` `char *hp_extract_text(const hp_document *doc, size_t *out_len);` -- Owned, NUL-terminated buffers; release with hp_free. *out_len (optional) * excludes the trailing NUL.
- `hp_get_title` (function) `include/html_parse.h:70` `char *hp_get_title(const hp_document *doc, size_t *out_len);`
- `src` (function) `include/html_parse.h:90` `* carry their raw src (a <script src> with an inline body lists ONLY the src -- * browser rule: when src is present...`
- `modules` (function) `include/html_parse.h:94` `* ES modules (import/export cannot run as a classic script), and template blocks * (text/x-jquery-tmpl, text/html...`
- `hp_free_scripts` (function) `include/html_parse.h:111` `void hp_free_scripts(hp_script *scripts, size_t count);` -- Releases an array returned by hp_extract_script_list (each text/src and the * array).
- `hp_extract_stylesheet_hrefs` (function) `include/html_parse.h:127` `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count);` -- Returns the RAW href of every applicable <link rel=stylesheet>, in document order, as an owned array of...
- `hp_free_stylesheet_hrefs` (function) `include/html_parse.h:130` `void hp_free_stylesheet_hrefs(char **hrefs, size_t count);` -- Returns the RAW href of every applicable <link rel=stylesheet>, in document order, as an owned array of...
- `hp_free` (function) `include/html_parse.h:133` `void hp_free(char *buf);` -- number found.
- `hp_document_free` (function) `include/html_parse.h:136` `void hp_document_free(hp_document *doc);` -- (ASCII case-insensitive) and NOT the token "alternate"; href is present and non-empty; and media is absent/empty or...
- `hp_document_root` (function) `include/html_parse.h:142` `const void *hp_document_root(const hp_document *doc);` -- Internal seam for the dom layer: returns the document's root node as an opaque handle (so html_parse.h stays free of...

## include/image_decode.h
Imported by: `fuzz/fuzz_image_decode.c`, `gui/browser_ui.c`, `src/image_decode.c`, `src/tab.c`, `tests/test_freedom.c`, `tests/test_image_decode.c`
- `guards` (function) `include/image_decode.h:25` `* guards (in-memory source only, longjmp error manager so a bad stream never * calls exit(), dimension caps before...`
- `img_dimensions_ok` (function) `include/image_decode.h:78` `int img_dimensions_ok(uint32_t w, uint32_t h);` -- 1 iff (w,h) is non-zero and fits the anti-DoS caps (per-side and area, no * overflow of width*height*4); 0 otherwise.
- `inputs` (function) `include/image_decode.h:81` `* Degenerate inputs (<= 0) yield (0,0). Pure. */ void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h...`
- `decode` (function) `include/image_decode.h:92` `* the declared dimensions BEFORE the full decode (anti-bomb), decodes to RGB and * expands to BGRA. Rejects non-JPEG...`
- `img_pixels_free` (function) `include/image_decode.h:121` `void img_pixels_free(img_pixels *p);` -- Releases data and zeroes the struct.
- `img_format_name` (function) `include/image_decode.h:124` `const char *img_format_name(img_format f);` -- Releases data and zeroes the struct.

## include/import_map.h
Imported by: `fuzz/fuzz_import_map.c`, `src/import_map.c`, `src/tab.c`, `tests/test_import_map.c`
- `algorithm` (function) `include/import_map.h:13` `* resolution algorithm (scopes, exact and prefix matches). URL resolution is the * caller's (the same resolver the...`
- `map` (function) `include/import_map.h:28` `* map (fail closed = no mapping). NULL only on OOM. */ im_map *im_parse(const char *json, size_t len, const char...`
- `im_resolve` (function) `include/import_map.h:33` `int im_resolve(const im_map *m, const char *base, const char *specifier, im_url_fn resolve, void *ctx, char *out...` -- Resolves specifier as imported from base (the importing module's URL).
- `im_count` (function) `include/import_map.h:37` `size_t im_count(const im_map *m);` -- Resolves specifier as imported from base (the importing module's URL).
- `im_free` (function) `include/import_map.h:40` `void im_free(im_map *m);` -- Resolves specifier as imported from base (the importing module's URL).

## include/interp.h
Imported by: `gui/browser_ui.c`, `src/interp.c`, `tests/test_interp.c`
- `ip_ease` (function) `include/interp.h:48` `double ip_ease(double t, const ip_ease_fn *fn);` -- Compute eased t for normalized t ∈ [0,1].
- `ip_lerp` (function) `include/interp.h:60` `double ip_lerp(double a, double b, double t);`
- `ip_lerp_color` (function) `include/interp.h:61` `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t);`
- `ip_interp` (function) `include/interp.h:62` `double ip_interp(ip_val_kind kind, double a, double b, double t);`
- `ip_kf_interp` (function) `include/interp.h:78` `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf, int n_kf, double pct);` -- Interpolate between the two keyframes bracketing `pct` (0..100).
- `ip_anim_init` (function) `include/interp.h:121` `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease, const ip_keyframe *kf, int n_kf, double...` -- double duration_ms; double delay_ms; int iteration_count; int direction; int fill_mode; /* Runtime state double...
- `ip_anim_tick` (function) `include/interp.h:128` `int ip_anim_tick(ip_anim *a, double dt_ms);` -- Advance time by dt_ms.
- `ip_anim_current` (function) `include/interp.h:131` `double ip_anim_current(const ip_anim *a);` -- Advance time by dt_ms.
- `ip_anim_done` (function) `include/interp.h:134` `int ip_anim_done(const ip_anim *a);` -- Advance time by dt_ms.

## include/js_dom.h
Depends on: `include/dom.h`, `include/freebug.h`, `include/js_geom.h`, `include/js_location.h`, `include/js_sandbox.h`, `include/url.h`
Imported by: `fuzz/fuzz_js_dom.c`, `include/js_location.h`, `include/js_trusted.h`, `src/js_dom.c`, `src/js_dom_internal.h`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/js_location.c`, `src/tab.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`
- `opaque` (function) `include/js_dom.h:64` `* the engine runtime opaque (unreachable from script);`
- `jd_click_state_free` (function) `include/js_dom.h:78` `* jd_click_state_free(). Bound to one context via jd_install_events(). */ jd_click_state *jd_click_state_new(void);`
- `run` (function) `include/js_dom.h:87` `* run (no handler registered, or handlers ran without calling preventDefault()), * and 0 if a handler called...`
- `preventDefault` (function) `include/js_dom.h:94` `* preventDefault() was called, 1 if the default (form submission) should proceed. * ctx == NULL or no form found =>...`
- `host` (function) `include/js_dom.h:123` `* for a trusted host (allow.conf AND js.conf);`
- `jd_get_cookies` (function) `include/js_dom.h:134` `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz);` -- Serialises the page's current cookie jar ("name=value; ...") into buf (bounded, NUL-terminated) and returns its...
- `out_status` (function) `include/js_dom.h:142` `* On success returns 0 and sets *out_status (HTTP status, 0 if unknown), *out_body / * *out_body_len (response...`
- `jd_process_iframes` (function) `include/js_dom.h:163` `* BEFORE jd_process_iframes() (so iframes are in the DOM for it to process). * ctx == NULL => JD_ERR_NULL_ARG. */...`
- `URLs` (function) `include/js_dom.h:170` `* video URLs (.m3u8 then .mp4 patterns), and creates <video> elements in the document for * any found. Does NOT...`
- `jd_video_from_scripts` (function) `include/js_dom.h:184` `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts, const size_t *script_lens, size_t...` -- Creates <iframe> elements in the DOM from video data (`video[N]` / `video_data`) found in inline script text...

## include/js_env.h
Depends on: `include/js_sandbox.h`
Imported by: `src/js_env.c`, `src/tab.c`, `tests/test_js_env.c`
- `poisoned` (function) `include/js_env.h:43` `* readback is poisoned (deterministic within an origin, unlinkable across * sessions and across origins) to defeat...`


Next: [API_p4.md](API_p4.md)
