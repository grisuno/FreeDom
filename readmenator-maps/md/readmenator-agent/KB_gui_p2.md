# Subsystem: gui (page 2 of 2)
Previous: [KB_gui.md](KB_gui.md)

## gui/browser_ui.c (continued)
                             ...`
  - `freebug_pointer_button` (function, line 16137) `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...`
  - `freebug_pointer_motion` (function, line 16156) `static void freebug_pointer_motion(browser_window *w)`
  - `freebug_pointer_axis` (function, line 16178) `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)`
  - `ptr_enter` (function, line 16196) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
  - `ptr_leave` (function, line 16214) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
  - `ptr_motion` (function, line 16231) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
  - `load_current` (function, line 16256) `static void load_current(browser_window *w)`
  - `go_omnibox` (function, line 16269) `static void go_omnibox(browser_window *w)`
  - `ptr_button` (function, line 16314) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
  - `scroll_line_px` (function, line 16561) `static double scroll_line_px(const browser_window *w)`
  - `ptr_axis` (function, line 16565) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
  - `ptr_frame` (function, line 16589) `static void ptr_frame(void *d, struct wl_pointer *p)`
  - `mime_is_text` (function, line 16605) `static int mime_is_text(const char *mime)`
  - `data_offer_source_actions` (function, line 16623) `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_offer_action` (function, line 16626) `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)`
  - `data_device_data_offer` (function, line 16636) `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...`
  - `data_device_selection` (function, line 16648) `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...`
  - `data_device_enter` (function, line 16667) `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...`
  - `data_device_leave` (function, line 16672) `static void data_device_leave(void *d, struct wl_data_device *dev)`
  - `data_device_motion` (function, line 16673) `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...`
  - `data_device_drop` (function, line 16677) `static void data_device_drop(void *d, struct wl_data_device *dev)`
  - `data_source_cancelled` (function, line 16688) `static void data_source_cancelled(void *data, struct wl_data_source *src)`
  - `data_source_send` (function, line 16694) `static void data_source_send(void *data, struct wl_data_source *src,
                            ...`
  - `data_source_target` (function, line 16707) `static void data_source_target(void *d, struct wl_data_source *s, const char *m)`
  - `freebug_copy_console` (function, line 16719) `static void freebug_copy_console(browser_window *w)`
  - `insert_pasted_text` (function, line 16777) `static void insert_pasted_text(browser_window *w, const char *text, size_t len)`
  - `clipboard_copy` (function, line 16841) `static void clipboard_copy(browser_window *w)`
  - `keyboard_keymap` (function, line 16889) `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...`
  - `keyboard_enter` (function, line 16910) `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...`
  - `keyboard_leave` (function, line 16917) `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)`
  - `key_sym_to_js_key` (function, line 16925) `static const char *key_sym_to_js_key(xkb_keysym_t sym)`
  - `key_sym_to_keycode` (function, line 16951) `static int key_sym_to_keycode(xkb_keysym_t sym)`
  - `dispatch_js_event` (function, line 16976) `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...`
  - `handle_key_press` (function, line 17034) `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...`
  - `key_is_repeatable` (function, line 17364) `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)`
  - `key_repeat_arm` (function, line 17380) `static void key_repeat_arm(browser_window *w, uint32_t key)`
  - `key_repeat_stop` (function, line 17393) `static void key_repeat_stop(browser_window *w)`
  - `key_repeat_fire` (function, line 17404) `static void key_repeat_fire(browser_window *w)`
  - `keyboard_key` (function, line 17418) `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...`
  - `keyboard_modifiers` (function, line 17458) `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...`
  - `keyboard_repeat_info` (function, line 17467) `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)`
  - `seat_caps` (function, line 17486) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
  - `seat_name` (function, line 17497) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
  - `registry_global` (function, line 17504) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
  - `registry_remove` (function, line 17524) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
  - `ui_run_browser` (function, line 17534) `ui_status ui_run_browser(const char *start_url)`
  - `cost` (function, line 17929) `* measured cost (floor 33 ms = the existing ~30 fps ceiling):
             * cheap pages paint at...`
  - `offset` (function, line 168) `* offset (labels and the flag live in one place, no magic indices);`
  - `fields` (function, line 275) `* fields (so the 200+ render/event call sites stay unchanged);`
  - `delay` (function, line 369) `* timer delay (tab_page.next_timer_ms);`
  - `main` (function, line 512) `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never...`
  - `proxy` (function, line 1014) `* and enable each proxy ("1" => the default port);`
  - `video_feeder_thread` (function, line 1069) `static void *video_feeder_thread(void *arg);`
  - `box_pad_px` (function, line 1170) `static double box_pad_px(int px_val, int pct_pm, double cb_w);`
  - `page_trusted` (function, line 1519) `static int page_trusted(const browser_window *w);`
  - `only` (function, line 1600) `* Trusted pages only (untrusted CSS is still applied by the worker, but its * fonts never reach the parent...`
  - `hb_is_allowlisted` (function, line 1737) `&& hb_is_allowlisted(w->hosts, ihost);`
  - `proceed` (function, line 1780) `* may proceed (cfg and pr->allowlisted are then set);`
  - `secure_fetch` (function, line 2031) `* through secure_fetch (Zero Trust);`
  - `string` (function, line 2179) `* or an empty string (unset, blocked, or off by caps.images), so there is no * decision to re-check, unlike...`
  - `do_load` (function, line 2221) `static void do_load(browser_window *w, const char *url);`
  - `tab_new` (function, line 2226) `static void tab_new(browser_window *w, const char *url);`
  - `toggle` (function, line 2236) `* No network: a capability toggle (images/CSS) re-renders from cache. Does nothing * when there is no cached source...`
  - `stylesheets` (function, line 2386) `* External stylesheets (Hito 27) follow the author-styles opt-in -- or the * trusted-host doctrine (Hito 28)...`
  - `body` (function, line 2418) `* every served CSS body (serial and pool paths alike). */ font_stash_reset(w);`
  - `ALIVE` (function, line 2525) `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or...`
  - `resolve` (function, line 2713) `* origin so its relative references and local images resolve (confined to the * document's directory) -- a local...`
  - `smaller` (function, line 3309) `* size when the content is smaller (height) or wider (min-width);`
  - `HarfBuzz` (function, line 3736) `* descriptor via HarfBuzz (text_shape);`
  - `produced` (function, line 4239) `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target...`
  - `line` (function, line 4338) `* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the...`
  - `box_path4` (function, line 4539) `static void box_path4(cairo_t *cr, double x, double y, double w, double h, const double *rc);`
  - `block_leaves_flow` (function, line 4621) `static int block_leaves_flow(const rd_doc *doc, const rd_block *bk);`
  - `container` (function, line 5347) `* were the container (github's tab pill). */ int item = item_at_level(doc, rd_at(doc, k), cid);`
  - `way` (function, line 5447) `* intrinsic box either way (it does not wrap below its own size). */ static int block_leaves_flow(const rd_doc *doc...`
  - `layout` (function, line 5688) `* hypothetical size in the real layout (Flexbox 9.2.3). */ if (ibd != NULL && ibd->box_min_w > 0) base =...`
  - `close_all_boxes` (function, line 5768) `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);`
  - `deepest_open_on_path` (function, line 5774) `static int deepest_open_on_path(const rc_state *outer, const rd_doc *doc, int block_id);`
  - `TABLE` (function, line 5889) `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all...`
  - `band_shared_box` (function, line 5999) `static int band_shared_box(const rd_doc *doc, const rc_state *s, size_t start, size_t end);`
  - `axis` (function, line 6147) `* differs: items stack on the vertical main axis (fx_column_place) and align on * the horizontal cross axis...`
  - `struct` (function, line 6346) `* struct (0 = auto);`
  - `descriptor` (function, line 6354) `* placement rides the nested descriptor (spec/grid_areas.md 6). */ int nbc = child_cont_at_level(doc, bk, cid);`
  - `builds` (function, line 6633) `* wraps beside it: the same band the top level builds (spec/float.md). */ const rd_block *fk = rd_at(doc, k);`
  - `flow` (function, line 6710) `* it collapse their vertical margins with each other exactly as in * the main flow (CSS 2.1 8.3.1), and none escapes...`
  - `own` (function, line 6742) `* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and...`
  - `items` (function, line 6823) `* items (Flexbox 4.2);`
  - `multicol_fragment` (function, line 6988) `static double multicol_fragment(rc_layout *L, const rc_open_box *ob, double content_bottom);`
  - `behind` (function, line 7241) `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old...`
  - `treatment` (function, line 7716) `* block treatment (shrink-wrapped and placed by text-align), which is what a * standalone centred call-to-action...`
  - `context` (function, line 7866) `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document...`
  - `x` (function, line 8151) `* reported x is already the BORDER x (the §7c.2 rule);`
  - `it` (function, line 8677) `* already sized it (see col_founder_set), so it is not a cap again. */ int fills_column = (si.col_founder_set &&...`
  - `chain` (function, line 8836) `* chain (the box that left the normal flow at this pen position);`
  - `anchor` (function, line 8948) `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is...`
  - `key` (function, line 9008) `* founders splits by key (stories, rail, footer nav each take * their column);`
  - `have` (function, line 9022) `* as they always have (spec/float.md §6b.3). The line still open beside * the previous float is committed first, at...`
  - `standalone` (function, line 9043) `* must not be treated as standalone (which would flush that line and give * the element a row of its own -- R7). */...`
  - `margin` (function, line 9391) `* own left margin (the margin box starts at the anchor point), a right- * anchored one ends at it. Same for the...`
  - `rd_build` (function, line 10069) `* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr...`
  - `descriptors` (function, line 10326) `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection —...`
  - `again` (function, line 10407) `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one...`
  - `blocking` (function, line 10694) `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);`
  - `rect` (function, line 11047) `* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops...`
  - `layer` (function, line 11290) `* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the...`
  - `convention` (function, line 11406) `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE || style...`
  - `row_owner_block_id` (function, line 11556) `static int row_owner_block_id(const rc_layout *L, const rc_row *r);`
  - `exactly` (function, line 11602) `* the resolved size exactly (like the SVG path above): routing through * paint_image_row would re-resolve a % width...`
  - `bg` (function, line 11698) `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);`
  - `rows` (function, line 11922) `* RC_IMAGE rows (see its declaration);`
  - `made` (function, line 12416) `* its zero channels made (255,255,255,alpha 0) -- an invalid * premultiplied value Cairo composites as ADDITIVE...`
  - `the` (function, line 12520) `* the (already filtered) group with the shadow color, blur it, and * paint it under the group at the declared offset...`
  - `fill` (function, line 12697) `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in...`
  - `overflow` (function, line 12757) `* adding two of them in int was signed overflow (UB, found by UBSan). */ double ox = left + bx->x +...`
  - `compositing` (function, line 12799) `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context...`
  - `origin` (function, line 13881) `* top_url is the page origin (https or file://);`
  - `in` (function, line 13959) `* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);`
  - `sf_ws_url_check` (function, line 14328) `&& sf_ws_url_check(op->data) == SF_OK && rp_host_of(op->data, host, sizeof host) == 0 && hb_check(w->hosts, host) !=...`
  - `presentation` (function, line 14819) `* affect presentation (a repaint, which re-runs layout, suffices);`
  - `resizes` (function, line 15521) `* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);`
  - `down` (function, line 16190) `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void...`
  - `loop` (function, line 16768) `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately...`
  - `saving` (function, line 17549) `* disables saving (never clobber);`
  - `redraws` (function, line 17628) `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A...`
  - `applies` (function, line 17698) `* persisted choice applies (prefs_parse already clamped it to a valid mode). */ const char *js_env =...`
  - `_GNU_SOURCE` (macro, line 12) `#define _GNU_SOURCE`
  - `UI_TOOLBAR_H` (macro, line 85) `#define UI_TOOLBAR_H`
  - `UI_TITLEBAR_H` (macro, line 86) `#define UI_TITLEBAR_H`
  - `UI_TABBAR_H` (macro, line 87) `#define UI_TABBAR_H`
  - `UI_TAB_MIN_W` (macro, line 88) `#define UI_TAB_MIN_W`
  - `UI_TAB_MAX_W` (macro, line 89) `#define UI_TAB_MAX_W`
  - `UI_TAB_NEW_W` (macro, line 90) `#define UI_TAB_NEW_W`
  - `UI_TAB_CLOSE_W` (macro, line 91) `#define UI_TAB_CLOSE_W`
  - `UI_BTN_W` (macro, line 92) `#define UI_BTN_W`
  - `UI_WIN_BTN_W` (macro, line 93) `#define UI_WIN_BTN_W`
  - `UI_MARGIN` (macro, line 94) `#define UI_MARGIN`
  - `UI_BTN_LEFT` (macro, line 95) `#define UI_BTN_LEFT`
  - `UI_LIST_INDENT` (macro, line 99) `#define UI_LIST_INDENT`
  - `UI_SCROLLBAR_W` (macro, line 104) `#define UI_SCROLLBAR_W`
  - `UI_SCROLLBAR_MIN` (macro, line 105) `#define UI_SCROLLBAR_MIN`
  - `UI_SCROLLBAR_PAD` (macro, line 106) `#define UI_SCROLLBAR_PAD`
  - `UI_RESIZE_MARGIN` (macro, line 110) `#define UI_RESIZE_MARGIN`
  - `UI_MENU_W` (macro, line 115) `#define UI_MENU_W`
  - `UI_MENU_ITEM_H` (macro, line 116) `#define UI_MENU_ITEM_H`
  - `UI_MENU_PAD` (macro, line 117) `#define UI_MENU_PAD`
  - `UI_CHECK_SZ` (macro, line 118) `#define UI_CHECK_SZ`
  - `UI_MENU_LABEL_H` (macro, line 119) `#define UI_MENU_LABEL_H`
  - `UI_MENU_INPUT_H` (macro, line 120) `#define UI_MENU_INPUT_H`
  - `UI_HAMBURGER_W` (macro, line 121) `#define UI_HAMBURGER_W`
  - `UI_HAMBURGER_GAP` (macro, line 122) `#define UI_HAMBURGER_GAP`
  - `UI_CURSOR_SIZE` (macro, line 123) `#define UI_CURSOR_SIZE`
  - `UI_TOAST_PAD` (macro, line 124) `#define UI_TOAST_PAD`
  - `OMNI_MAX_SUGG` (macro, line 125) `#define OMNI_MAX_SUGG`
  - `UI_OMNI_ROW_H` (macro, line 126) `#define UI_OMNI_ROW_H`
  - `UI_TWO_PI` (macro, line 127) `#define UI_TWO_PI`
  - `UI_INPUT_PAD` (macro, line 131) `#define UI_INPUT_PAD`
  - `UI_CONTROL_FONT` (macro, line 134) `#define UI_CONTROL_FONT`
  - `UI_INPUT_MEASURE_W` (macro, line 140) `#define UI_INPUT_MEASURE_W`
  - `UI_INPUT_WIDTH` (macro, line 141) `#define UI_INPUT_WIDTH`
  - `UI_BUTTON_HPAD` (macro, line 142) `#define UI_BUTTON_HPAD`
  - `UI_FORM_FIELDS_MAX` (macro, line 143) `#define UI_FORM_FIELDS_MAX`
  - `UI_UNDERLINE_OFFSET` (macro, line 148) `#define UI_UNDERLINE_OFFSET`
  - `UI_UNDERLINE_THICK` (macro, line 149) `#define UI_UNDERLINE_THICK`
  - `UI_STRIKE_OFFSET` (macro, line 150) `#define UI_STRIKE_OFFSET`
  - `UI_OVERLINE_OFFSET` (macro, line 151) `#define UI_OVERLINE_OFFSET`
  - `UI_SLICE_MAX` (macro, line 155) `#define UI_SLICE_MAX`
  - `UI_MENU_COUNT` (macro, line 214) `#define UI_MENU_COUNT`
  - `UI_IMAGE_MAX_BODY` (macro, line 232) `#define UI_IMAGE_MAX_BODY`
  - `UI_MAX_TABS` (macro, line 271) `#define UI_MAX_TABS`
  - `UI_READER_COLUMN_W` (macro, line 590) `#define UI_READER_COLUMN_W`
  - `FONT_STASH_MAX_SHEETS` (macro, line 1577) `#define FONT_STASH_MAX_SHEETS`
  - `FONT_STASH_MAX_BYTES` (macro, line 1578) `#define FONT_STASH_MAX_BYTES`
  - `JS_NAV_MAX` (macro, line 2231) `#define JS_NAV_MAX`
  - `HIST_STEP_DEPTH_MAX` (macro, line 2233) `#define HIST_STEP_DEPTH_MAX`
  - `JS_TICKS_PER_LOAD` (macro, line 2351) `#define JS_TICKS_PER_LOAD`
  - `UI_RELOAD_X` (macro, line 3107) `#define UI_RELOAD_X`
  - `RC_IBOX_MAX` (macro, line 3460) `#define RC_IBOX_MAX`
  - `RC_BOX_STACK_MAX` (macro, line 3462) `#define RC_BOX_STACK_MAX`
  - `RC_FLOAT_MAX` (macro, line 3466) `#define RC_FLOAT_MAX`
  - `RC_FLOAT_FIT_MIN` (macro, line 3473) `#define RC_FLOAT_FIT_MIN`
  - `FLEX_MEASURE_W` (macro, line 5389) `#define FLEX_MEASURE_W`
  - `FLEX_MIN_MEASURE_W` (macro, line 5394) `#define FLEX_MIN_MEASURE_W`
  - `BALANCE_MAX_LINES` (macro, line 5517) `#define BALANCE_MAX_LINES`
  - `RC_COL_FREE_MAX` (macro, line 7004) `#define RC_COL_FREE_MAX`
  - `RC_MAX_OUT_OF_FLOW` (macro, line 7793) `#define RC_MAX_OUT_OF_FLOW`
  - `RC_DEFER_COLS` (macro, line 7901) `#define RC_DEFER_COLS`
  - `RC_DEFER_RANGES` (macro, line 7902) `#define RC_DEFER_RANGES`
  - `RC_DEFER_BAND_RUNS` (macro, line 7984) `#define RC_DEFER_BAND_RUNS`
  - `BUI_CONIC_SLICES` (macro, line 11120) `#define BUI_CONIC_SLICES`
  - `ROW_PAINT_ALL` (macro, line 11626) `#define ROW_PAINT_ALL`
  - `ROW_PAINT_BAND` (macro, line 11627) `#define ROW_PAINT_BAND`
  - `ROW_PAINT_CONTENT` (macro, line 11628) `#define ROW_PAINT_CONTENT`
  - `OV_MAX_DEPTH` (macro, line 11847) `#define OV_MAX_DEPTH`
  - `H2R` (macro, line 12472) `#define H2R(p,q,t)`
  - `PDF_PAGE_W` (macro, line 13436) `#define PDF_PAGE_W`
  - `PDF_PAGE_H` (macro, line 13437) `#define PDF_PAGE_H`
  - `PDF_MARGIN` (macro, line 13438) `#define PDF_MARGIN`
  - `PNG_PAGE_W` (macro, line 13602) `#define PNG_PAGE_W`
  - `PNG_MARGIN` (macro, line 13615) `#define PNG_MARGIN`
  - `PNG_MAX_H` (macro, line 13616) `#define PNG_MAX_H`
  - `FBW_W` (macro, line 15622) `#define FBW_W`
  - `FBW_H` (macro, line 15623) `#define FBW_H`
  - `FBW_HEADER` (macro, line 15624) `#define FBW_HEADER`
  - `FBW_PAD` (macro, line 15625) `#define FBW_PAD`
  - `FBW_LINE` (macro, line 15626) `#define FBW_LINE`
  - `FBW_GUTTER` (macro, line 15627) `#define FBW_GUTTER`
  - `FBW_MIN_SPLIT` (macro, line 15628) `#define FBW_MIN_SPLIT`
  - `FBW_MAX_SPLIT` (macro, line 15629) `#define FBW_MAX_SPLIT`
  - `FBW_COPY_BTN_W` (macro, line 15630) `#define FBW_COPY_BTN_W`
  - `FBW_COPY_BTN_H` (macro, line 15631) `#define FBW_COPY_BTN_H`
- Depends on: `gui/browser_ui_internal.h`, `include/block_flow.h`, `include/box_blur.h`, `include/box_style.h`, `include/box_tree.h`, `include/browser.h`, `include/compositor.h`, `include/css.h`, `include/css_color.h`, `include/data_url.h`, `include/download.h`, `include/form.h`, `include/frame_clock.h`, `include/freebug.h`, `include/hls.h`, `include/hostblock.h`, `include/hostedit.h`, `include/image_decode.h`, `include/interp.h`, `include/js_policy.h`, `include/link_nav.h`, `include/media_decoder.h`, `include/net_realm.h`, `include/pdf_export.h`, `include/prefetch.h`, `include/prefs.h`, `include/profile.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/svg_paint.h`, `include/svg_render.h`, `include/tab.h`, `include/text_case.h`, `include/text_shape.h`, `include/textfield.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/web_storage.h`, `include/webcaps.h`, `include/webfont.h`, `include/webfont_load.h`, `include/ws_hub.h`, `include/zoom.h`

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
  - `ui_theme_default` (function, line 14) `ui_theme ui_theme_default(void)`
  - `ui_theme_dark` (function, line 83) `ui_theme ui_theme_dark(void)`
  - `ui_theme_sepia` (function, line 128) `ui_theme ui_theme_sepia(void)`
  - `ui_theme_for` (function, line 170) `ui_theme ui_theme_for(int mode)`
  - `rgb_from_packed` (function, line 179) `ui_rgb rgb_from_packed(int packed)`
  - `set_rgb` (function, line 184) `void set_rgb(cairo_t *cr, ui_rgb c)`
- Depends on: `gui/browser_ui_internal.h`, `include/css_color.h`

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

