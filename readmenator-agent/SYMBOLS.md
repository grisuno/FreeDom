# Symbols (page 1 of 13)
Pages: [SYMBOLS.md](SYMBOLS.md), [SYMBOLS_p2.md](SYMBOLS_p2.md), [SYMBOLS_p3.md](SYMBOLS_p3.md), [SYMBOLS_p4.md](SYMBOLS_p4.md), [SYMBOLS_p5.md](SYMBOLS_p5.md), [SYMBOLS_p6.md](SYMBOLS_p6.md), [SYMBOLS_p7.md](SYMBOLS_p7.md), [SYMBOLS_p8.md](SYMBOLS_p8.md), [SYMBOLS_p9.md](SYMBOLS_p9.md), [SYMBOLS_p10.md](SYMBOLS_p10.md), [SYMBOLS_p11.md](SYMBOLS_p11.md), [SYMBOLS_p12.md](SYMBOLS_p12.md), [SYMBOLS_p13.md](SYMBOLS_p13.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `list_unique_crashes` | function | `app.py:39` | `def list_unique_crashes()` |
| `read_fuzz_stats` | function | `app.py:30` | `def read_fuzz_stats()` |
| `run_freedom_headless` | function | `app.py:47` | `def run_freedom_headless(payload_path)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_css.c:80` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `fuzz_root_match` | function | `fuzz/fuzz_css.c:66` | `static int fuzz_root_match(void *ctx, const css_sel *sel)` |
| `worker` | function | `fuzz/fuzz_data_url.c:6` | `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, never  * interpreted...` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_dom.c:48` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `ensure_built` | function | `fuzz/fuzz_dom.c:41` | `static void ensure_built(void)` |
| `pass` | function | `fuzz/fuzz_dom_debug.c:8` | `* the measure pass (cap 0) must agree with the would-write return value.  *  * Build & run: make ...` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_download.c:31` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_freebug.c:37` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_image_decode.c:32` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `poke_and_free` | function | `fuzz/fuzz_image_decode.c:21` | `static void poke_and_free(img_pixels *px)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_import_map.c:24` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `fres` | function | `fuzz/fuzz_import_map.c:17` | `static int fres(void *ctx, const char *base, const char *ref, char *out, size_t outsz)` |
| `FUZZ_JSDOM_MAX_NODES` | macro | `fuzz/fuzz_js_dom.c:38` | `#define FUZZ_JSDOM_MAX_NODES` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_js_dom.c:40` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `fz_dom_parent` | function | `fuzz/fuzz_js_dom.c:33` | `static dom_node_id fz_dom_parent(void *ctx, dom_node_id n)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_js_geom.c:27` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `fz_parent` | struct | `fuzz/fuzz_js_geom.c:17` | `` |
| `fz_parent_of` | function | `fuzz/fuzz_js_geom.c:20` | `static dom_node_id fz_parent_of(void *ctx, dom_node_id n)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_js_sandbox.c:48` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `fz_fetch` | function | `fuzz/fuzz_js_sandbox.c:33` | `static char *fz_fetch(void *host, const char *url, size_t *len)` |
| `fz_mod` | struct | `fuzz/fuzz_js_sandbox.c:21` | `` |
| `fz_resolve` | function | `fuzz/fuzz_js_sandbox.c:23` | `static int fz_resolve(void *host, const char *base, const char *spec, char *out, size_t outsz)` |
| `js_sandbox` | function | `fuzz/fuzz_js_sandbox.c:2` | `* libFuzzer harness for js_sandbox (Hito 3). * * Goal: arbitrary bytes treated as untrusted script through the full...` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_pdf_export.c:30` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_prefetch.c:10` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_prefs.c:21` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_svg_render.c:24` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `FZ_CAP` | macro | `fuzz/fuzz_text_shape.c:23` | `#define FZ_CAP` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_text_shape.c:25` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_url.c:59` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `check_split` | function | `fuzz/fuzz_url.c:31` | `static void check_split(const char *url)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_webfont.c:11` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `ALIVE` | function | `gui/browser_ui.c:2427` | `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or...` |
| `BUI_CONIC_SLICES` | macro | `gui/browser_ui.c:9740` | `#define BUI_CONIC_SLICES` |
| `FBW_COPY_BTN_H` | macro | `gui/browser_ui.c:14082` | `#define FBW_COPY_BTN_H` |
| `FBW_COPY_BTN_W` | macro | `gui/browser_ui.c:14081` | `#define FBW_COPY_BTN_W` |
| `FBW_GUTTER` | macro | `gui/browser_ui.c:14078` | `#define FBW_GUTTER` |
| `FBW_H` | macro | `gui/browser_ui.c:14074` | `#define FBW_H` |
| `FBW_HEADER` | macro | `gui/browser_ui.c:14075` | `#define FBW_HEADER` |
| `FBW_LINE` | macro | `gui/browser_ui.c:14077` | `#define FBW_LINE` |
| `FBW_MAX_SPLIT` | macro | `gui/browser_ui.c:14080` | `#define FBW_MAX_SPLIT` |
| `FBW_MIN_SPLIT` | macro | `gui/browser_ui.c:14079` | `#define FBW_MIN_SPLIT` |
| `FBW_PAD` | macro | `gui/browser_ui.c:14076` | `#define FBW_PAD` |
| `FBW_W` | macro | `gui/browser_ui.c:14073` | `#define FBW_W` |
| `FLEX_MEASURE_W` | macro | `gui/browser_ui.c:4908` | `#define FLEX_MEASURE_W` |
| `FLEX_MIN_MEASURE_W` | macro | `gui/browser_ui.c:4913` | `#define FLEX_MIN_MEASURE_W` |
| `FONT_STASH_MAX_BYTES` | macro | `gui/browser_ui.c:1468` | `#define FONT_STASH_MAX_BYTES` |
| `FONT_STASH_MAX_SHEETS` | macro | `gui/browser_ui.c:1467` | `#define FONT_STASH_MAX_SHEETS` |
| `Firefox` | function | `gui/browser_ui.c:12665` | `* on its face does in Firefox (spec/page_view.md, tanda 40). */ static const rd_block *submit_pro...` |
| `GET` | function | `gui/browser_ui.c:1370` | `* a GET (Zero Trust). cfg->policy is restored before returning. */ static sf_status fetch_post_na...` |
| `GET` | function | `gui/browser_ui.c:12995` | `* the network under weaker rules than a GET (Zero Trust). */ static void do_submit_post(browser_w...` |
| `H2R` | macro | `gui/browser_ui.c:11044` | `#define H2R(p,q,t)` |
| `HIST_STEP_DEPTH_MAX` | macro | `gui/browser_ui.c:2123` | `#define HIST_STEP_DEPTH_MAX` |
| `HarfBuzz` | function | `gui/browser_ui.c:3577` | `* descriptor via HarfBuzz (text_shape);` |
| `JS_NAV_MAX` | macro | `gui/browser_ui.c:2121` | `#define JS_NAV_MAX` |
| `JS_TICKS_PER_LOAD` | macro | `gui/browser_ui.c:2241` | `#define JS_TICKS_PER_LOAD` |
| `OMNI_MAX_SUGG` | macro | `gui/browser_ui.c:123` | `#define OMNI_MAX_SUGG` |
| `OV_MAX_DEPTH` | macro | `gui/browser_ui.c:10441` | `#define OV_MAX_DEPTH` |
| `PDF_MARGIN` | macro | `gui/browser_ui.c:11920` | `#define PDF_MARGIN` |
| `PDF_PAGE_H` | macro | `gui/browser_ui.c:11919` | `#define PDF_PAGE_H` |
| `PDF_PAGE_W` | macro | `gui/browser_ui.c:11918` | `#define PDF_PAGE_W` |
| `PNG_MARGIN` | macro | `gui/browser_ui.c:12095` | `#define PNG_MARGIN` |
| `PNG_MAX_H` | macro | `gui/browser_ui.c:12096` | `#define PNG_MAX_H` |
| `PNG_PAGE_W` | macro | `gui/browser_ui.c:12082` | `#define PNG_PAGE_W` |
| `RC_BOX_STACK_MAX` | macro | `gui/browser_ui.c:3308` | `#define RC_BOX_STACK_MAX` |
| `RC_DEFER_BAND_RUNS` | macro | `gui/browser_ui.c:6897` | `#define RC_DEFER_BAND_RUNS` |
| `RC_DEFER_COLS` | macro | `gui/browser_ui.c:6814` | `#define RC_DEFER_COLS` |
| `RC_DEFER_RANGES` | macro | `gui/browser_ui.c:6815` | `#define RC_DEFER_RANGES` |
| `RC_FLOAT_FIT_MIN` | macro | `gui/browser_ui.c:3319` | `#define RC_FLOAT_FIT_MIN` |
| `RC_FLOAT_MAX` | macro | `gui/browser_ui.c:3312` | `#define RC_FLOAT_MAX` |
| `RC_MAX_OUT_OF_FLOW` | macro | `gui/browser_ui.c:6706` | `#define RC_MAX_OUT_OF_FLOW` |
| `TABLE` | function | `gui/browser_ui.c:5242` | `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all...` |
| `UI_BTN_LEFT` | macro | `gui/browser_ui.c:93` | `#define UI_BTN_LEFT` |
| `UI_BTN_W` | macro | `gui/browser_ui.c:90` | `#define UI_BTN_W` |
| `UI_BUTTON_HPAD` | macro | `gui/browser_ui.c:134` | `#define UI_BUTTON_HPAD` |
| `UI_CHECK_SZ` | macro | `gui/browser_ui.c:116` | `#define UI_CHECK_SZ` |
| `UI_CURSOR_SIZE` | macro | `gui/browser_ui.c:121` | `#define UI_CURSOR_SIZE` |
| `UI_FORM_FIELDS_MAX` | macro | `gui/browser_ui.c:135` | `#define UI_FORM_FIELDS_MAX` |
| `UI_HAMBURGER_GAP` | macro | `gui/browser_ui.c:120` | `#define UI_HAMBURGER_GAP` |
| `UI_HAMBURGER_W` | macro | `gui/browser_ui.c:119` | `#define UI_HAMBURGER_W` |
| `UI_IMAGE_MAX_BODY` | macro | `gui/browser_ui.c:224` | `#define UI_IMAGE_MAX_BODY` |
| `UI_INPUT_MEASURE_W` | macro | `gui/browser_ui.c:132` | `#define UI_INPUT_MEASURE_W` |
| `UI_INPUT_PAD` | macro | `gui/browser_ui.c:129` | `#define UI_INPUT_PAD` |
| `UI_INPUT_WIDTH` | macro | `gui/browser_ui.c:133` | `#define UI_INPUT_WIDTH` |
| `UI_LIST_INDENT` | macro | `gui/browser_ui.c:97` | `#define UI_LIST_INDENT` |
| `UI_MARGIN` | macro | `gui/browser_ui.c:92` | `#define UI_MARGIN` |
| `UI_MAX_TABS` | macro | `gui/browser_ui.c:263` | `#define UI_MAX_TABS` |
| `UI_MENU_COUNT` | macro | `gui/browser_ui.c:206` | `#define UI_MENU_COUNT` |
| `UI_MENU_INPUT_H` | macro | `gui/browser_ui.c:118` | `#define UI_MENU_INPUT_H` |
| `UI_MENU_ITEM_H` | macro | `gui/browser_ui.c:114` | `#define UI_MENU_ITEM_H` |
| `UI_MENU_LABEL_H` | macro | `gui/browser_ui.c:117` | `#define UI_MENU_LABEL_H` |
| `UI_MENU_PAD` | macro | `gui/browser_ui.c:115` | `#define UI_MENU_PAD` |
| `UI_MENU_W` | macro | `gui/browser_ui.c:113` | `#define UI_MENU_W` |
| `UI_OMNI_ROW_H` | macro | `gui/browser_ui.c:124` | `#define UI_OMNI_ROW_H` |
| `UI_OVERLINE_OFFSET` | macro | `gui/browser_ui.c:143` | `#define UI_OVERLINE_OFFSET` |
| `UI_READER_COLUMN_W` | macro | `gui/browser_ui.c:582` | `#define UI_READER_COLUMN_W` |
| `UI_RELOAD_X` | macro | `gui/browser_ui.c:2990` | `#define UI_RELOAD_X` |
| `UI_RESIZE_MARGIN` | macro | `gui/browser_ui.c:108` | `#define UI_RESIZE_MARGIN` |
| `UI_SCROLLBAR_MIN` | macro | `gui/browser_ui.c:103` | `#define UI_SCROLLBAR_MIN` |
| `UI_SCROLLBAR_PAD` | macro | `gui/browser_ui.c:104` | `#define UI_SCROLLBAR_PAD` |
| `UI_SCROLLBAR_W` | macro | `gui/browser_ui.c:102` | `#define UI_SCROLLBAR_W` |
| `UI_SLICE_MAX` | macro | `gui/browser_ui.c:147` | `#define UI_SLICE_MAX` |
| `UI_STRIKE_OFFSET` | macro | `gui/browser_ui.c:142` | `#define UI_STRIKE_OFFSET` |
| `UI_TABBAR_H` | macro | `gui/browser_ui.c:85` | `#define UI_TABBAR_H` |
| `UI_TAB_CLOSE_W` | macro | `gui/browser_ui.c:89` | `#define UI_TAB_CLOSE_W` |
| `UI_TAB_MAX_W` | macro | `gui/browser_ui.c:87` | `#define UI_TAB_MAX_W` |
| `UI_TAB_MIN_W` | macro | `gui/browser_ui.c:86` | `#define UI_TAB_MIN_W` |
| `UI_TAB_NEW_W` | macro | `gui/browser_ui.c:88` | `#define UI_TAB_NEW_W` |
| `UI_TITLEBAR_H` | macro | `gui/browser_ui.c:84` | `#define UI_TITLEBAR_H` |
| `UI_TOAST_PAD` | macro | `gui/browser_ui.c:122` | `#define UI_TOAST_PAD` |
| `UI_TOOLBAR_H` | macro | `gui/browser_ui.c:83` | `#define UI_TOOLBAR_H` |
| `UI_TWO_PI` | macro | `gui/browser_ui.c:125` | `#define UI_TWO_PI` |
| `UI_UNDERLINE_OFFSET` | macro | `gui/browser_ui.c:140` | `#define UI_UNDERLINE_OFFSET` |
| `UI_UNDERLINE_THICK` | macro | `gui/browser_ui.c:141` | `#define UI_UNDERLINE_THICK` |
| `UI_WIN_BTN_W` | macro | `gui/browser_ui.c:91` | `#define UI_WIN_BTN_W` |
| `_GNU_SOURCE` | macro | `gui/browser_ui.c:12` | `#define _GNU_SOURCE` |
| `add` | function | `gui/browser_ui.c:3762` | `* about to add (top/h passed in). A box that survived a line wrap simply ends at the  * wrap -- m...` |
| `add_current_host_to_list` | function | `gui/browser_ui.c:802` | `static void add_current_host_to_list(browser_window *w, int sel)` |
| `again` | function | `gui/browser_ui.c:9110` | `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one...` |
| `allowlisted` | type_alias | `gui/browser_ui.c:1664` | `typedef struct fetch_prep { int allowlisted;` |
| `anchor` | function | `gui/browser_ui.c:7750` | `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is...` |
| `applies` | function | `gui/browser_ui.c:16149` | `* persisted choice applies (prefs_parse already clamped it to a valid mode). */ const char *js_env =...` |
| `apply_click_result` | function | `gui/browser_ui.c:12862` | `static int apply_click_result(browser_window *w, tab_page *page)` |
| `apply_history_ops` | function | `gui/browser_ui.c:12817` | `static void apply_history_ops(browser_window *w, const tab_page *page)` |
| `apply_zoom` | function | `gui/browser_ui.c:599` | `static void apply_zoom(browser_window *w)` |
| `approximation` | function | `gui/browser_ui.c:8020` | `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */ static void oof_s...` |
| `arrives` | function | `gui/browser_ui.c:2513` | `* on screen until the result arrives (deliver_fetch_result renders it). about:blank  * and local ...` |
| `audio_mark_dead` | function | `gui/browser_ui.c:9069` | `static void audio_mark_dead(browser_window *w)` |
| `audio_spawn` | function | `gui/browser_ui.c:9015` | `static void audio_spawn(browser_window *w, int rate, int channels)` |
| `audio_stop` | function | `gui/browser_ui.c:9101` | `static void audio_stop(browser_window *w)` |
| `audio_write` | function | `gui/browser_ui.c:9086` | `static void audio_write(browser_window *w, const uint8_t *data, size_t len)` |
| `axis` | function | `gui/browser_ui.c:5451` | `* differs: items stack on the vertical main axis (fx_column_place) and align on * the horizontal cross axis...` |
| `band_common_box` | function | `gui/browser_ui.c:6726` | `static int band_common_box(const rd_doc *doc, size_t start, size_t end)` |
| `behind` | function | `gui/browser_ui.c:6258` | `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old...` |
| `bg` | function | `gui/browser_ui.c:10310` | `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);` |
| `blit_image_box` | function | `gui/browser_ui.c:8795` | `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,                  ...` |
| `block_id` | type_alias | `gui/browser_ui.c:3263` | `typedef struct rc_open_box { int block_id;` |
| `block_in_table_caption` | function | `gui/browser_ui.c:6790` | `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)` |
| `block_is_oof` | function | `gui/browser_ui.c:5254` | `static int block_is_oof(const rd_doc *doc, const rd_block *bk)` |
| `block_leaves_flow` | function | `gui/browser_ui.c:4300` | `static int block_leaves_flow(const rd_doc *doc, const rd_block *bk);` |
| `block_margins` | function | `gui/browser_ui.c:3732` | `static void block_margins(const ui_theme *th, const rd_block *b,                           double...` |
| `block_style` | function | `gui/browser_ui.c:3705` | `static void block_style(const ui_theme *th, const rd_block *b,                         double *si...` |
| `blocking` | function | `gui/browser_ui.c:9397` | `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);` |
| `body` | function | `gui/browser_ui.c:2319` | `* every served CSS body (serial and pool paths alike). */ font_stash_reset(w);` |
| `bookmark_toggle_current` | function | `gui/browser_ui.c:972` | `static void bookmark_toggle_current(browser_window *w)` |
| `box` | function | `gui/browser_ui.c:11520` | `* content belongs to that box (painted by its own positioned entry). */     if (sub == NULL)` |
| `box_edge_px` | function | `gui/browser_ui.c:4689` | `static double box_edge_px(int wpx)` |
| `box_forms_stacking_context` | function | `gui/browser_ui.c:10572` | `static int box_forms_stacking_context(const pv_box_def *def)` |
| `box_is_strict_descendant` | function | `gui/browser_ui.c:4788` | `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)` |
| `box_line_visible` | function | `gui/browser_ui.c:6062` | `static int box_line_visible(int style)` |
| `box_margin_bottom` | function | `gui/browser_ui.c:6239` | `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)` |
| `box_margin_top` | function | `gui/browser_ui.c:6232` | `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)` |
| `box_path` | function | `gui/browser_ui.c:9652` | `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)` |
| `box_path_has` | function | `gui/browser_ui.c:6551` | `static int box_path_has(const rd_doc *doc, int block_id, int want)` |
| `box_path_of` | function | `gui/browser_ui.c:6710` | `static int box_path_of(const rd_doc *doc, int block_id, int *out)` |
| `box_pointer_events_none` | function | `gui/browser_ui.c:12575` | `static int box_pointer_events_none(const rd_doc *doc, int block_id)` |
| `box_shrink_width` | function | `gui/browser_ui.c:6591` | `static double box_shrink_width(cairo_t *cr, const browser_window *w,                             ...` |
| `box_transform_matrix` | function | `gui/browser_ui.c:10622` | `static void box_transform_matrix(const pv_box_def *def, double box_x, double box_y,              ...` |
| `browser_window` | struct | `gui/browser_ui.c:287` | `` |
| `bs` | type_alias | `gui/browser_ui.c:271` | `typedef struct tab_ctx { browser_state bs;` |
| `buffer_release` | function | `gui/browser_ui.c:610` | `static void buffer_release(void *data, struct wl_buffer *wl_buffer)` |
| `bui_blend_operator` | function | `gui/browser_ui.c:10740` | `static cairo_operator_t bui_blend_operator(int mix_blend)` |
| `bui_grad_color_at` | function | `gui/browser_ui.c:9713` | `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,                    ...` |
| `bui_paint_backdrop_blur` | function | `gui/browser_ui.c:10878` | `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,                          ...` |
| `bui_pop_group_composite` | function | `gui/browser_ui.c:10936` | `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms)` |
| `bui_skew_tan` | function | `gui/browser_ui.c:10615` | `static double bui_skew_tan(int deg)` |
| `build_file_origin` | function | `gui/browser_ui.c:691` | `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)` |
| `build_host_filter` | function | `gui/browser_ui.c:718` | `static hb_set *build_host_filter(void)` |
| `build_impersonate_optin` | function | `gui/browser_ui.c:768` | `static int build_impersonate_optin(void)` |
| `build_js_filter` | function | `gui/browser_ui.c:765` | `static hb_set *build_js_filter(void)` |
| `button_box_width` | function | `gui/browser_ui.c:8385` | `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,               ...` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9990` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9993` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:10033` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:10036` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:10094` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:10097` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:10189` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:10191` | `cairo_set_dash(cr, (double[])` |
| `caller` | function | `gui/browser_ui.c:12261` | `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the  * out_path ve...` |
| `chain` | function | `gui/browser_ui.c:7658` | `* chain (the box that left the normal flow at this pen position);` |
| `child_cont_at_level` | function | `gui/browser_ui.c:5202` | `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)` |
| `children` | function | `gui/browser_ui.c:6249` | `* own content rect onto the stack so its children (text or nested boxes) place inside  * it. At t...` |
| `clear_doc` | function | `gui/browser_ui.c:1246` | `static void clear_doc(browser_window *w)` |
| `clipboard_copy` | function | `gui/browser_ui.c:15292` | `static void clipboard_copy(browser_window *w)` |
| `close_all_boxes` | function | `gui/browser_ui.c:5174` | `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);` |
| `close_top_box` | function | `gui/browser_ui.c:6068` | `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)` |
| `col` | type_alias | `gui/browser_ui.c:6833` | `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];` |
| `collect_local_storage` | function | `gui/browser_ui.c:2196` | `static void collect_local_storage(browser_window *w, const tab_page *page)` |
| `column` | function | `gui/browser_ui.c:6457` | `*  * Returns the height of the tallest column (0 when there is nothing to fragment). */ static do...` |
| `columns` | function | `gui/browser_ui.c:6565` | `* each card made 1080px columns (huggingface, github). */ static int deepest_open_on_path(const r...` |
| `compositing` | function | `gui/browser_ui.c:11357` | `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context...` |
| `compute_page_js` | function | `gui/browser_ui.c:2143` | `static int compute_page_js(const browser_window *w)` |
| `container_box_of` | function | `gui/browser_ui.c:4839` | `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)` |
| `content_font` | function | `gui/browser_ui.c:3588` | `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,             ...` |
| `content_geometry` | function | `gui/browser_ui.c:2849` | `static void content_geometry(const browser_window *w, double *top, double *height)` |
| `content_width` | function | `gui/browser_ui.c:2876` | `static double content_width(const browser_window *w)` |
| `context` | function | `gui/browser_ui.c:6779` | `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document...` |
| `convention` | function | `gui/browser_ui.c:10056` | `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE \|\| style...` |
| `cost` | function | `gui/browser_ui.c:16380` | `* measured cost (floor 33 ms = the existing ~30 fps ceiling):              * cheap pages paint at...` |
| `count` | function | `gui/browser_ui.c:8001` | `* the box count (a hostile parent cycle terminates). */ static int oof_depth(const rd_doc *doc, s...` |
| `css_align_to_bt` | function | `gui/browser_ui.c:4679` | `static int css_align_to_bt(int align_kw)` |
| `css_replaced_box` | function | `gui/browser_ui.c:4398` | `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,                ...` |
| `cursor_at_point` | function | `gui/browser_ui.c:12591` | `static int cursor_at_point(browser_window *w, double px, double py)` |
| `data_device_data_offer` | function | `gui/browser_ui.c:15087` | `static void data_device_data_offer(void *data, struct wl_data_device *dev,                       ...` |
| `data_device_drop` | function | `gui/browser_ui.c:15128` | `static void data_device_drop(void *d, struct wl_data_device *dev)` |
| `data_device_enter` | function | `gui/browser_ui.c:15118` | `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,              ...` |
| `data_device_leave` | function | `gui/browser_ui.c:15123` | `static void data_device_leave(void *d, struct wl_data_device *dev)` |
| `data_device_motion` | function | `gui/browser_ui.c:15124` | `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,                  ...` |
| `data_device_selection` | function | `gui/browser_ui.c:15099` | `static void data_device_selection(void *data, struct wl_data_device *dev,                        ...` |
| `data_offer_action` | function | `gui/browser_ui.c:15077` | `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)` |
| `data_offer_source_actions` | function | `gui/browser_ui.c:15074` | `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)` |
| `data_source_cancelled` | function | `gui/browser_ui.c:15139` | `static void data_source_cancelled(void *data, struct wl_data_source *src)` |
| `data_source_send` | function | `gui/browser_ui.c:15145` | `static void data_source_send(void *data, struct wl_data_source *src,                             ...` |
| `data_source_target` | function | `gui/browser_ui.c:15158` | `static void data_source_target(void *d, struct wl_data_source *s, const char *m)` |
| `deco_configure` | function | `gui/browser_ui.c:13995` | `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)` |
| `deepest_open_on_path` | function | `gui/browser_ui.c:5180` | `static int deepest_open_on_path(const rc_state *outer, const rd_doc *doc, int block_id);` |
| `def_declared_width` | function | `gui/browser_ui.c:5052` | `static double def_declared_width(const pv_box_def *d, double avail_w)` |
| `def_width_cap` | function | `gui/browser_ui.c:5046` | `static double def_width_cap(const pv_box_def *d, double avail_w)` |
| `defer_append` | function | `gui/browser_ui.c:6977` | `static int defer_append(rc_defer *d, int key, int side,                         int ml, int mlpct...` |
| `defer_flush` | function | `gui/browser_ui.c:7011` | `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,                      ...` |
| `defer_key_block` | function | `gui/browser_ui.c:6854` | `static int defer_key_block(const rd_block *bk)` |
| `delay` | function | `gui/browser_ui.c:361` | `* timer delay (tab_page.next_timer_ms);` |
| `deliver_fetch_result` | function | `gui/browser_ui.c:13109` | `static void deliver_fetch_result(browser_window *w, fetch_job *j)` |
| `descriptors` | function | `gui/browser_ui.c:9029` | `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection —...` |
| `destroy_buffer` | function | `gui/browser_ui.c:616` | `static void destroy_buffer(browser_window *w)` |
| `dies` | function | `gui/browser_ui.c:9006` | `* child dies (exec failed, device busy, daemon absent) is detected on the  * next PCM write (EPIP...` |
| `dispatch_js_event` | function | `gui/browser_ui.c:15427` | `static void dispatch_js_event(browser_window *w, dom_node_id node_id,                            ...` |
| `do_load` | function | `gui/browser_ui.c:2111` | `static void do_load(browser_window *w, const char *url);` |
| `down` | function | `gui/browser_ui.c:14641` | `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void...` |
| `drain_fetch_results` | function | `gui/browser_ui.c:13163` | `static void drain_fetch_results(browser_window *w)` |
| `draw_clock` | function | `gui/browser_ui.c:13382` | `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,                ...` |
| `draw_hamburger` | function | `gui/browser_ui.c:13394` | `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)` |
| `draw_hover_url` | function | `gui/browser_ui.c:13543` | `static double draw_hover_url(cairo_t *cr, browser_window *w)` |
| `draw_menu` | function | `gui/browser_ui.c:13432` | `static void draw_menu(cairo_t *cr, browser_window *w)` |
| `draw_omnibox` | function | `gui/browser_ui.c:13660` | `static void draw_omnibox(cairo_t *cr, browser_window *w)` |
| `draw_reload` | function | `gui/browser_ui.c:13410` | `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)` |
| `draw_scrollbar` | function | `gui/browser_ui.c:2945` | `static void draw_scrollbar(cairo_t *cr, const browser_window *w)` |
| `draw_slice` | function | `gui/browser_ui.c:3652` | `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)` |
| `draw_tabstrip` | function | `gui/browser_ui.c:13605` | `static void draw_tabstrip(cairo_t *cr, browser_window *w)` |
| `draw_text` | function | `gui/browser_ui.c:3060` | `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)` |
| `draw_toast` | function | `gui/browser_ui.c:13575` | `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)` |
| `drop_repl_worker` | function | `gui/browser_ui.c:2232` | `static void drop_repl_worker(browser_window *w)` |
| `element` | function | `gui/browser_ui.c:14037` | `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand  * even without...` |
| `emit_replaced_row` | function | `gui/browser_ui.c:4407` | `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,                 ...` |
| `ensure_buffer` | function | `gui/browser_ui.c:622` | `static int ensure_buffer(browser_window *w)` |
| `ensure_download_dir` | function | `gui/browser_ui.c:13029` | `static int ensure_download_dir(char *out, size_t outsz)` |
| `export_pdf` | function | `gui/browser_ui.c:12040` | `static void export_pdf(browser_window *w)` |
| `export_png` | function | `gui/browser_ui.c:12227` | `static void export_png(browser_window *w)` |
| `family` | type_alias | `gui/browser_ui.c:3912` | `typedef struct rc_ext { int family;` |
| `family_face` | function | `gui/browser_ui.c:3566` | `static const char *family_face(int family)` |
| `fbw_console_lines` | function | `gui/browser_ui.c:14154` | `static size_t fbw_console_lines(const fb_buffer *log)` |
| `fbw_level_rgb` | function | `gui/browser_ui.c:14143` | `static void fbw_level_rgb(int level, double *r, double *g, double *b)` |
| `fbw_split_y` | function | `gui/browser_ui.c:14107` | `static double fbw_split_y(const freebug_window *fb)` |
| `fbw_toplevel_close` | function | `gui/browser_ui.c:14412` | `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)` |
| `fbw_toplevel_configure` | function | `gui/browser_ui.c:14403` | `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,                           ...` |
| `fbw_xdg_surface_configure` | function | `gui/browser_ui.c:14395` | `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)` |
| `fetch_follow_navigable` | function | `gui/browser_ui.c:1334` | `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,                         ...` |
| `fetch_job` | struct | `gui/browser_ui.c:1745` | `` |
| `fetch_job_free` | function | `gui/browser_ui.c:1777` | `static void fetch_job_free(fetch_job *j)` |
| `fetch_launch` | function | `gui/browser_ui.c:1869` | `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,                ...` |
| `fetch_prep` | struct | `gui/browser_ui.c:1664` | `` |
| `fetch_thread` | function | `gui/browser_ui.c:1821` | `static void *fetch_thread(void *arg)` |
| `fields` | function | `gui/browser_ui.c:267` | `* fields (so the 200+ render/event call sites stay unchanged);` |
| `fill` | function | `gui/browser_ui.c:11264` | `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in...` |
| `find_bg_image` | function | `gui/browser_ui.c:1141` | `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)` |
| `find_input_state` | function | `gui/browser_ui.c:1238` | `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)` |
| `first` | function | `gui/browser_ui.c:1563` | `* Navigation: clear the registry first (faces are per document). Untrusted:  * no-op (fetch NULL)...` |
| `flex_item_basis` | function | `gui/browser_ui.c:5113` | `static double flex_item_basis(cairo_t *cr, const browser_window *w,                              ...` |
| `flex_item_min_main` | function | `gui/browser_ui.c:5152` | `static double flex_item_min_main(cairo_t *cr, const browser_window *w,                           ...` |
| `flow` | function | `gui/browser_ui.c:16358` | `* flow (counting them starved aplay). A video frame read while * overdue overwrites the held slot (standard player...` |
| `flow_emit_frag` | function | `gui/browser_ui.c:3944` | `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,                  ...` |
| `flow_text` | function | `gui/browser_ui.c:4012` | `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,                ...` |
| `flow_text_block` | function | `gui/browser_ui.c:4510` | `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,                  ...` |
| `flush_line` | function | `gui/browser_ui.c:3822` | `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)` |
| `foldback_session_cookies` | function | `gui/browser_ui.c:2206` | `static void foldback_session_cookies(const char *url, const char *jar)` |
| `font_size` | type_alias | `gui/browser_ui.c:3079` | `typedef struct rc_frag { double x, width, font_size;` |
| `frag_at_point` | function | `gui/browser_ui.c:12684` | `static dom_node_id frag_at_point(browser_window *w, double px, double py,                        ...` |
| `frag_styled` | function | `gui/browser_ui.c:3665` | `static int frag_styled(const rc_frag *f)` |
| `fragment` | function | `gui/browser_ui.c:10517` | `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using  * blk->block_id alo...` |
| `free_images` | function | `gui/browser_ui.c:1102` | `static void free_images(browser_window *w)` |
| `free_inputs` | function | `gui/browser_ui.c:1094` | `static void free_inputs(browser_window *w)` |
| `free_live_page` | function | `gui/browser_ui.c:2676` | `static void free_live_page(browser_window *w)` |
| `freebug_copy_console` | function | `gui/browser_ui.c:15170` | `static void freebug_copy_console(browser_window *w)` |
| `freebug_destroy` | function | `gui/browser_ui.c:14457` | `static void freebug_destroy(browser_window *w)` |
| `freebug_ensure_buffer` | function | `gui/browser_ui.c:14116` | `static int freebug_ensure_buffer(freebug_window *fb)` |
| `freebug_eval` | function | `gui/browser_ui.c:14513` | `static void freebug_eval(browser_window *w)` |
| `freebug_handle_key` | function | `gui/browser_ui.c:14553` | `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,                              ...` |
| `freebug_hide` | function | `gui/browser_ui.c:14379` | `static void freebug_hide(browser_window *w)` |
| `freebug_is_open` | function | `gui/browser_ui.c:14468` | `static int freebug_is_open(const browser_window *w)` |
| `freebug_owns_surface` | function | `gui/browser_ui.c:14464` | `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)` |
| `freebug_paint` | function | `gui/browser_ui.c:14167` | `static void freebug_paint(freebug_window *fb)` |
| `freebug_pointer_axis` | function | `gui/browser_ui.c:14629` | `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)` |
| `freebug_pointer_button` | function | `gui/browser_ui.c:14588` | `static void freebug_pointer_button(browser_window *w, uint32_t serial,                           ...` |
| `freebug_pointer_motion` | function | `gui/browser_ui.c:14607` | `static void freebug_pointer_motion(browser_window *w)` |
| `freebug_redraw` | function | `gui/browser_ui.c:14375` | `static void freebug_redraw(browser_window *w)` |
| `freebug_redraw_fb` | function | `gui/browser_ui.c:14366` | `static void freebug_redraw_fb(freebug_window *fb)` |
| `freebug_repl_worker` | function | `gui/browser_ui.c:14475` | `static tab *freebug_repl_worker(browser_window *w)` |
| `freebug_show` | function | `gui/browser_ui.c:14422` | `static void freebug_show(browser_window *w)` |
| `freebug_toggle` | function | `gui/browser_ui.c:14452` | `static void freebug_toggle(browser_window *w)` |
| `freebug_window` | type_alias | `gui/browser_ui.c:559` | `typedef struct freebug_window freebug_window;` |
| `freebug_window` | struct | `gui/browser_ui.c:14084` | `` |
| `freedom_write_dir` | function | `gui/browser_ui.c:777` | `static int freedom_write_dir(char *out, size_t cap)` |
| `geom_from_layout` | function | `gui/browser_ui.c:11663` | `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,                 ...` |
| `go_omnibox` | function | `gui/browser_ui.c:14720` | `static void go_omnibox(browser_window *w)` |
| `grad_stop` | function | `gui/browser_ui.c:9698` | `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)` |
| `gui_css_sink` | function | `gui/browser_ui.c:1495` | `static void gui_css_sink(void *vctx, const char *url,                          const char *body, ...` |
| `gui_subresource_fetch` | function | `gui/browser_ui.c:1411` | `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,                ...` |
| `gutter` | function | `gui/browser_ui.c:578` | `* gutter (content_margin) is intentionally left unzoomed, like a browser's text  * zoom. The PDF ...` |
| `h` | type_alias | `gui/browser_ui.c:3162` | `typedef struct rc_box { double x, top, w, h;` |
| `handle_key_press` | function | `gui/browser_ui.c:15485` | `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,              ...` |
| `have` | function | `gui/browser_ui.c:7824` | `* as they always have (spec/float.md §6b.3). The line still open beside * the previous float is committed first, at...` |
| `hb_is_allowlisted` | function | `gui/browser_ui.c:1627` | `&& hb_is_allowlisted(w->hosts, ihost);` |
| `history_step` | function | `gui/browser_ui.c:12829` | `static void history_step(browser_window *w, int steps)` |
| `host_from_url` | function | `gui/browser_ui.c:1035` | `static int host_from_url(const char *url, char *out, size_t outsz)` |
| `hot_actionable` | function | `gui/browser_ui.c:3023` | `static int hot_actionable(const browser_window *w, ui_hot hot)` |
| `html_center_offset` | function | `gui/browser_ui.c:2886` | `static double html_center_offset(const browser_window *w)` |
| `in` | function | `gui/browser_ui.c:12418` | `* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);` |
| `init_net_config` | function | `gui/browser_ui.c:1010` | `static void init_net_config(browser_window *w)` |
| `inlines` | function | `gui/browser_ui.c:4307` | `* next run may also be a replaced element without its own break: consecutive  * atomic inlines (`...` |
| `input_box_width` | function | `gui/browser_ui.c:8376` | `static double input_box_width(double content_w)` |
| `input_is_editable` | function | `gui/browser_ui.c:1088` | `static int input_is_editable(int input_type)` |
| `input_is_interactive` | function | `gui/browser_ui.c:1082` | `static int input_is_interactive(int input_type)` |
| `insert_pasted_text` | function | `gui/browser_ui.c:15228` | `static void insert_pasted_text(browser_window *w, const char *text, size_t len)` |
| `is_http_url` | function | `gui/browser_ui.c:1024` | `static int is_http_url(const char *s)` |
| `is_https_url` | function | `gui/browser_ui.c:1020` | `static int is_https_url(const char *s)` |
| `it` | function | `gui/browser_ui.c:7905` | `* column: flush first so the column lands above it (source order), * then move the anchor — the image bottom is the...` |
| `item_at_level` | function | `gui/browser_ui.c:5187` | `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)` |
| `item_declared_basis` | function | `gui/browser_ui.c:5057` | `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,                       ...` |
| `item_root_box` | function | `gui/browser_ui.c:4670` | `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)` |
| `item_root_box_in` | function | `gui/browser_ui.c:4623` | `static int item_root_box_in(const rd_doc *doc, size_t b0, size_t b1, int cbox)` |
| `item_sides` | struct | `gui/browser_ui.c:4759` | `` |
| `item_sides_at_level` | function | `gui/browser_ui.c:4810` | `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,                   ...` |
| `item_vmargins` | function | `gui/browser_ui.c:5296` | `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,           ...` |
| `items` | function | `gui/browser_ui.c:5952` | `* items (Flexbox 4.2);` |
| `key` | type_alias | `gui/browser_ui.c:6826` | `typedef struct rc_defer_col { int key;` |
| `key` | function | `gui/browser_ui.c:7810` | `* founders splits by key (stories, rail, footer nav each take * their column);` |
| `key_is_repeatable` | function | `gui/browser_ui.c:15815` | `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)` |
| `key_repeat_arm` | function | `gui/browser_ui.c:15831` | `static void key_repeat_arm(browser_window *w, uint32_t key)` |
| `key_repeat_fire` | function | `gui/browser_ui.c:15855` | `static void key_repeat_fire(browser_window *w)` |
| `key_repeat_stop` | function | `gui/browser_ui.c:15844` | `static void key_repeat_stop(browser_window *w)` |
| `key_sym_to_js_key` | function | `gui/browser_ui.c:15376` | `static const char *key_sym_to_js_key(xkb_keysym_t sym)` |
| `key_sym_to_keycode` | function | `gui/browser_ui.c:15402` | `static int key_sym_to_keycode(xkb_keysym_t sym)` |
| `keyboard_enter` | function | `gui/browser_ui.c:15361` | `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,                         ...` |
| `keyboard_key` | function | `gui/browser_ui.c:15869` | `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,                   ...` |
| `keyboard_keymap` | function | `gui/browser_ui.c:15340` | `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,                             uint...` |
| `keyboard_leave` | function | `gui/browser_ui.c:15368` | `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)` |
| `keyboard_modifiers` | function | `gui/browser_ui.c:15909` | `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,                  ...` |
| `keyboard_repeat_info` | function | `gui/browser_ui.c:15918` | `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)` |
| `kind` | type_alias | `gui/browser_ui.c:3142` | `typedef struct rc_row { rc_rowkind kind;` |
| `layer` | function | `gui/browser_ui.c:9940` | `* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the...` |
| `layout` | function | `gui/browser_ui.c:1153` | `* shared by layout (row height) and paint (blit), so they cannot drift apart. */ static int image...` |
| `layout_container` | function | `gui/browser_ui.c:5311` | `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,                 ...` |
| `layout_doc` | function | `gui/browser_ui.c:7609` | `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,                   ...` |
| `layout_float_band` | function | `gui/browser_ui.c:7232` | `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,                ...` |
| `limits` | function | `gui/browser_ui.c:11166` | `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box  * grouped this w...` |
| `line` | function | `gui/browser_ui.c:4079` | `* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the...` |
| `line_desc` | type_alias | `gui/browser_ui.c:3320` | `typedef struct rc_state { double cur_top, pending_gap, pen_x, line_asc, line_desc;` |
| `line_limit` | function | `gui/browser_ui.c:3502` | `static double line_limit(const rc_state *s, double content_w)` |
| `link_at_point` | function | `gui/browser_ui.c:12468` | `static const char *link_at_point(browser_window *w, double px, double py)` |
| `load_bg_images` | function | `gui/browser_ui.c:2074` | `static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)` |
| `load_current` | function | `gui/browser_ui.c:14707` | `static void load_current(browser_window *w)` |
| `load_favorites` | function | `gui/browser_ui.c:870` | `static void load_favorites(browser_window *w)` |
| `load_host_file` | function | `gui/browser_ui.c:701` | `static void load_host_file(hb_set *s, const char *dir, const char *name, hb_list list)` |
| `load_images` | function | `gui/browser_ui.c:1990` | `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)` |
| `loop` | function | `gui/browser_ui.c:15219` | `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately...` |
| `main` | function | `gui/browser_ui.c:504` | `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never...` |
| `margin` | function | `gui/browser_ui.c:8156` | `* own left margin (the margin box starts at the anchor point), a right- * anchored one ends at it. Same for the...` |
| `measure_item_content_w` | function | `gui/browser_ui.c:5009` | `static double measure_item_content_w(cairo_t *cr, const browser_window *w,                       ...` |
| `measure_item_w_at` | function | `gui/browser_ui.c:4965` | `static double measure_item_w_at(cairo_t *cr, const browser_window *w,                            ...` |
| `memory` | function | `gui/browser_ui.c:12912` | `* memory (the href pointer, not its contents, was all the old code preserved). */ static void dis...` |
| `menu_item_checked` | function | `gui/browser_ui.c:13250` | `static int menu_item_checked(const browser_window *w, size_t i)` |
| `menu_item_toggle` | function | `gui/browser_ui.c:13272` | `static void menu_item_toggle(browser_window *w, size_t i)` |
| `menu_panel_rect` | function | `gui/browser_ui.c:3034` | `static void menu_panel_rect(const browser_window *w, double *x, double *y,                       ...` |
| `mime_is_text` | function | `gui/browser_ui.c:15056` | `static int mime_is_text(const char *mime)` |
| `mr` | type_alias | `gui/browser_ui.c:4759` | `typedef struct item_sides { double ml, mr;` |
| `multicol_fragment` | function | `gui/browser_ui.c:6059` | `static double multicol_fragment(rc_layout *L, const rc_open_box *ob, double content_bottom);` |
| `nested_cont_basis` | function | `gui/browser_ui.c:5071` | `static double nested_cont_basis(cairo_t *cr, const browser_window *w,                            ...` |
| `nested_stop` | function | `gui/browser_ui.c:6579` | `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)` |
| `newtab_x` | function | `gui/browser_ui.c:2813` | `static double newtab_x(const browser_window *w)` |
| `node_at_point` | function | `gui/browser_ui.c:12657` | `static dom_node_id node_at_point(browser_window *w, double px, double py)` |
| `now_ms` | function | `gui/browser_ui.c:150` | `static uint64_t now_ms(void)` |
| `offset` | function | `gui/browser_ui.c:160` | `* offset (labels and the flag live in one place, no magic indices);` |
| `omni_refresh` | function | `gui/browser_ui.c:916` | `static void omni_refresh(browser_window *w)` |
| `only` | function | `gui/browser_ui.c:1490` | `* Trusted pages only (untrusted CSS is still applied by the worker, but its * fonts never reach the parent...` |
| `open_line` | function | `gui/browser_ui.c:3893` | `static void open_line(rc_layout *L, rc_state *s)` |
| `open_line_height` | function | `gui/browser_ui.c:3880` | `static double open_line_height(const rc_state *s, const ui_theme *th)` |
| `origin` | function | `gui/browser_ui.c:12340` | `* top_url is the page origin (https or file://);` |
| `ov_box_bounds` | function | `gui/browser_ui.c:10473` | `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)` |
| `ov_box_clips` | function | `gui/browser_ui.c:10445` | `static int ov_box_clips(const pv_box_def *d)` |
| `ov_collect_chain` | function | `gui/browser_ui.c:10452` | `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)` |
| `ov_content_rect` | function | `gui/browser_ui.c:10497` | `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,                             do...` |
| `own` | function | `gui/browser_ui.c:5890` | `* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and...` |
| `page_js_host_allowlisted` | function | `gui/browser_ui.c:2137` | `static int page_js_host_allowlisted(const browser_window *w)` |
| `page_trusted` | function | `gui/browser_ui.c:1409` | `static int page_trusted(const browser_window *w);` |
| `paint` | function | `gui/browser_ui.c:13694` | `static void paint(browser_window *w)` |
| `paint_bg_layer` | function | `gui/browser_ui.c:9779` | `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,                ...` |
| `paint_box_and_direct_rows` | function | `gui/browser_ui.c:11275` | `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,        ...` |
| `paint_box_decoration` | function | `gui/browser_ui.c:9823` | `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,            ...` |
| `paint_box_decoration_grouped` | function | `gui/browser_ui.c:11235` | `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,                         ...` |
| `paint_content_row` | function | `gui/browser_ui.c:10257` | `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,                ...` |
| `paint_deco_line` | function | `gui/browser_ui.c:10155` | `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,                        ...` |
| `paint_inline_replaced` | function | `gui/browser_ui.c:10240` | `static void paint_inline_replaced(cairo_t *cr, browser_window *w,                                ...` |
| `paint_nested_children` | function | `gui/browser_ui.c:11626` | `static void paint_nested_children(cairo_t *cr, browser_window *w,                                ...` |
| `paint_oof_sub` | function | `gui/browser_ui.c:11374` | `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,                 ...` |
| `paint_positioned_one` | function | `gui/browser_ui.c:11412` | `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,             ...` |
| `paint_structured` | function | `gui/browser_ui.c:11716` | `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,                 ...` |
| `paint_svg_at` | function | `gui/browser_ui.c:10211` | `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,                          doub...` |
| `paint_video_row` | function | `gui/browser_ui.c:9472` | `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,                 ...` |
| `path` | function | `gui/browser_ui.c:5634` | `*          * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when         ...` |
| `place_inline_replaced` | function | `gui/browser_ui.c:4342` | `static int place_inline_replaced(rc_layout *L, rc_state *s, const ui_theme *th,                  ...` |
| `position_doc` | function | `gui/browser_ui.c:8209` | `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,                 ...` |
| `prepare_fetch` | function | `gui/browser_ui.c:1673` | `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,                     ...` |
| `presentation` | function | `gui/browser_ui.c:13270` | `* affect presentation (a repaint, which re-runs layout, suffices);` |
| `proceed` | function | `gui/browser_ui.c:1670` | `* may proceed (cfg and pr->allowlisted are then set);` |
| `produced` | function | `gui/browser_ui.c:3995` | `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target...` |
| `profile_sync` | function | `gui/browser_ui.c:947` | `static void profile_sync(browser_window *w)` |
| `proxy` | function | `gui/browser_ui.c:1007` | `* and enable each proxy ("1" => the default port);` |
| `proxy_addr_from_env` | function | `gui/browser_ui.c:996` | `static int proxy_addr_from_env(const char *envname, const char *deflt,                           ...` |
| `ptr_axis` | function | `gui/browser_ui.c:15016` | `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,                      uint32...` |
| `ptr_button` | function | `gui/browser_ui.c:14765` | `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,               ...` |
| `ptr_enter` | function | `gui/browser_ui.c:14647` | `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,                       struct wl_...` |
| `ptr_frame` | function | `gui/browser_ui.c:15040` | `static void ptr_frame(void *d, struct wl_pointer *p)` |
| `ptr_leave` | function | `gui/browser_ui.c:14665` | `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)` |
| `ptr_motion` | function | `gui/browser_ui.c:14682` | `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)` |
| `publish_geometry` | function | `gui/browser_ui.c:11694` | `static void publish_geometry(browser_window *w, const rc_layout *L, double left,                 ...` |
| `rc_add_box` | function | `gui/browser_ui.c:3527` | `static rc_box *rc_add_box(rc_layout *L)` |
| `rc_add_frag` | function | `gui/browser_ui.c:3539` | `static rc_frag *rc_add_frag(rc_layout *L)` |
| `rc_add_row` | function | `gui/browser_ui.c:3554` | `static rc_row *rc_add_row(rc_layout *L)` |
| `rc_box` | struct | `gui/browser_ui.c:3162` | `` |
| `rc_box_context` | function | `gui/browser_ui.c:6205` | `static void rc_box_context(const rc_state *s, double content_w,                            double...` |
| `rc_box_copy_decoration` | function | `gui/browser_ui.c:4709` | `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)` |
| `rc_defer` | struct | `gui/browser_ui.c:6833` | `` |
| `rc_defer_col` | struct | `gui/browser_ui.c:6826` | `` |
| `rc_ext` | struct | `gui/browser_ui.c:3912` | `` |
| `rc_float_bottom` | function | `gui/browser_ui.c:3415` | `static double rc_float_bottom(const rc_state *s)` |
| `rc_float_clear` | function | `gui/browser_ui.c:3424` | `static void rc_float_clear(rc_state *s)` |
| `rc_float_fit_line` | function | `gui/browser_ui.c:3483` | `static void rc_float_fit_line(rc_state *s, double line_h)` |
| `rc_float_refresh` | function | `gui/browser_ui.c:3437` | `static void rc_float_refresh(rc_state *s, double line_h)` |
| `rc_frag` | struct | `gui/browser_ui.c:3080` | `` |
| `rc_free` | function | `gui/browser_ui.c:3507` | `static void rc_free(rc_layout *L)` |
| `rc_layout` | struct | `gui/browser_ui.c:3215` | `` |
| `rc_oof_sub` | struct | `gui/browser_ui.c:3213` | `` |
| `rc_oof_sub` | struct | `gui/browser_ui.c:3253` | `` |
| `rc_open_box` | struct | `gui/browser_ui.c:3263` | `` |
| `rc_row` | struct | `gui/browser_ui.c:3143` | `` |
| `rc_rowkind` | enum | `gui/browser_ui.c:3141` | `` |
| `rc_state` | struct | `gui/browser_ui.c:3321` | `` |
| `rd_build` | function | `gui/browser_ui.c:8780` | `* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr...` |
| `read_file` | function | `gui/browser_ui.c:652` | `static char *read_file(const char *path, size_t *out_len)` |
| `rebuild_inputs` | function | `gui/browser_ui.c:1213` | `static void rebuild_inputs(browser_window *w)` |
| `reconcile_boxes` | function | `gui/browser_ui.c:6682` | `static void reconcile_boxes(cairo_t *cr, const browser_window *w,                             rc_...` |
| `reconcile_boxes_below` | function | `gui/browser_ui.c:6600` | `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,                          ...` |
| `rect` | function | `gui/browser_ui.c:9667` | `* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops...` |
| `redraw` | function | `gui/browser_ui.c:13938` | `static void redraw(browser_window *w)` |
| `redraws` | function | `gui/browser_ui.c:16079` | `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A...` |
| `reference` | function | `gui/browser_ui.c:12738` | `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:  * hostile content...` |
| `registry_global` | function | `gui/browser_ui.c:15955` | `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,                  ...` |
| `registry_remove` | function | `gui/browser_ui.c:15975` | `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)` |
| `remember_visit` | function | `gui/browser_ui.c:964` | `static void remember_visit(browser_window *w, const char *url)` |
| `render_current` | function | `gui/browser_ui.c:2446` | `static void render_current(browser_window *w)` |
| `render_current_ex` | function | `gui/browser_ui.c:2256` | `static void render_current_ex(browser_window *w, int allow_js_nav)` |
| `render_doc_images` | function | `gui/browser_ui.c:12344` | `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,               ...` |
| `replaced_current_color` | function | `gui/browser_ui.c:10231` | `static int replaced_current_color(const browser_window *w, const rd_block *blk)` |
| `replaced_inline_size` | function | `gui/browser_ui.c:4264` | `static int replaced_inline_size(const browser_window *w, const rd_block *b,                      ...` |
| `replaced_is_inline_level` | function | `gui/browser_ui.c:4294` | `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)` |
| `resizes` | function | `gui/browser_ui.c:13972` | `* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);` |
| `resolve` | function | `gui/browser_ui.c:2615` | `* origin so its relative references and local images resolve (confined to the * document's directory) -- a local...` |
| `resolve_box_cursor` | function | `gui/browser_ui.c:12561` | `static int resolve_box_cursor(const rd_doc *doc, int block_id)` |
| `root_cont_of` | function | `gui/browser_ui.c:5217` | `static int root_cont_of(const rd_doc *doc, int cid)` |
| `row` | function | `gui/browser_ui.c:4921` | `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */ static d...` |
| `row_align_offset` | function | `gui/browser_ui.c:9596` | `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)` |
| `row_line_slack` | function | `gui/browser_ui.c:9584` | `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)` |
| `row_owner_block_id` | function | `gui/browser_ui.c:10206` | `static int row_owner_block_id(const rc_layout *L, const rc_row *r);` |
| `rows` | function | `gui/browser_ui.c:10516` | `* RC_IMAGE rows (see its declaration);` |
| `run` | function | `gui/browser_ui.c:3797` | `* continuation run (block_id < 0 with no block break) deliberately skips reconcile  * to stay on ...` |
| `run_width_cap` | function | `gui/browser_ui.c:5042` | `static double run_width_cap(const rd_block *b, double avail_w)` |
| `save_current_page` | function | `gui/browser_ui.c:13099` | `static void save_current_page(browser_window *w)` |
| `save_download` | function | `gui/browser_ui.c:13066` | `static void save_download(browser_window *w, const char *url, const char *bytes,                 ...` |
| `saving` | function | `gui/browser_ui.c:16000` | `* disables saving (never clobber);` |
| `schedule_js_tick` | function | `gui/browser_ui.c:2246` | `static void schedule_js_tick(browser_window *w, int next_ms)` |
| `scroll_line_px` | function | `gui/browser_ui.c:15012` | `static double scroll_line_px(const browser_window *w)` |
| `scrollbar_drag_to` | function | `gui/browser_ui.c:2928` | `static void scrollbar_drag_to(browser_window *w)` |
| `scrollbar_metrics` | function | `gui/browser_ui.c:2900` | `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,          ...` |
| `seat_caps` | function | `gui/browser_ui.c:15937` | `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)` |
| `seat_name` | function | `gui/browser_ui.c:15948` | `static void seat_name(void *d, struct wl_seat *s, const char *name)` |
| `secure_fetch` | function | `gui/browser_ui.c:1921` | `* through secure_fetch (Zero Trust);` |
| `seed_local_storage` | function | `gui/browser_ui.c:2181` | `static void seed_local_storage(browser_window *w, tab *t, int trusted)` |
| `seed_session_cookies` | function | `gui/browser_ui.c:2157` | `static void seed_session_cookies(tab *t, int trusted, const char *url)` |
| `select_box_width` | function | `gui/browser_ui.c:8380` | `static double select_box_width(double content_w)` |

Next: [SYMBOLS_p2.md](SYMBOLS_p2.md)
