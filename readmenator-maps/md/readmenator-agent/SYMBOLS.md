# Symbols (page 1 of 14)
Pages: [SYMBOLS.md](SYMBOLS.md), [SYMBOLS_p2.md](SYMBOLS_p2.md), [SYMBOLS_p3.md](SYMBOLS_p3.md), [SYMBOLS_p4.md](SYMBOLS_p4.md), [SYMBOLS_p5.md](SYMBOLS_p5.md), [SYMBOLS_p6.md](SYMBOLS_p6.md), [SYMBOLS_p7.md](SYMBOLS_p7.md), [SYMBOLS_p8.md](SYMBOLS_p8.md), [SYMBOLS_p9.md](SYMBOLS_p9.md), [SYMBOLS_p10.md](SYMBOLS_p10.md), [SYMBOLS_p11.md](SYMBOLS_p11.md), [SYMBOLS_p12.md](SYMBOLS_p12.md), [SYMBOLS_p13.md](SYMBOLS_p13.md), [SYMBOLS_p14.md](SYMBOLS_p14.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `list_unique_crashes` | function | `app.py:39` | `def list_unique_crashes()` |
| `read_fuzz_stats` | function | `app.py:30` | `def read_fuzz_stats()` |
| `run_freedom_headless` | function | `app.py:47` | `def run_freedom_headless(payload_path)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_css.c:90` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `fuzz_root_match` | function | `fuzz/fuzz_css.c:76` | `static int fuzz_root_match(void *ctx, const css_sel *sel)` |
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
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_prefetch.c:14` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_prefs.c:21` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_svg_render.c:24` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_text_case.c:13` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `ASCII` | function | `fuzz/fuzz_text_shape.c:56` | `* printable ASCII (one run, the requested face) the two must agree. */ double m = tsh_measure(&f, px, text, len);` |
| `FZ_CAP` | macro | `fuzz/fuzz_text_shape.c:23` | `#define FZ_CAP` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_text_shape.c:25` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `glyph` | function | `fuzz/fuzz_text_shape.c:54` | `* one lacks a glyph (spec/text_shape.md 8);` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_url.c:59` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `check_split` | function | `fuzz/fuzz_url.c:31` | `static void check_split(const char *url)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_webfont.c:11` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `ALIVE` | function | `gui/browser_ui.c:2525` | `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or...` |
| `BALANCE_MAX_LINES` | macro | `gui/browser_ui.c:5517` | `#define BALANCE_MAX_LINES` |
| `BUI_CONIC_SLICES` | macro | `gui/browser_ui.c:10956` | `#define BUI_CONIC_SLICES` |
| `FBW_COPY_BTN_H` | macro | `gui/browser_ui.c:15467` | `#define FBW_COPY_BTN_H` |
| `FBW_COPY_BTN_W` | macro | `gui/browser_ui.c:15466` | `#define FBW_COPY_BTN_W` |
| `FBW_GUTTER` | macro | `gui/browser_ui.c:15463` | `#define FBW_GUTTER` |
| `FBW_H` | macro | `gui/browser_ui.c:15459` | `#define FBW_H` |
| `FBW_HEADER` | macro | `gui/browser_ui.c:15460` | `#define FBW_HEADER` |
| `FBW_LINE` | macro | `gui/browser_ui.c:15462` | `#define FBW_LINE` |
| `FBW_MAX_SPLIT` | macro | `gui/browser_ui.c:15465` | `#define FBW_MAX_SPLIT` |
| `FBW_MIN_SPLIT` | macro | `gui/browser_ui.c:15464` | `#define FBW_MIN_SPLIT` |
| `FBW_PAD` | macro | `gui/browser_ui.c:15461` | `#define FBW_PAD` |
| `FBW_W` | macro | `gui/browser_ui.c:15458` | `#define FBW_W` |
| `FLEX_MEASURE_W` | macro | `gui/browser_ui.c:5389` | `#define FLEX_MEASURE_W` |
| `FLEX_MIN_MEASURE_W` | macro | `gui/browser_ui.c:5394` | `#define FLEX_MIN_MEASURE_W` |
| `FONT_STASH_MAX_BYTES` | macro | `gui/browser_ui.c:1578` | `#define FONT_STASH_MAX_BYTES` |
| `FONT_STASH_MAX_SHEETS` | macro | `gui/browser_ui.c:1577` | `#define FONT_STASH_MAX_SHEETS` |
| `Firefox` | function | `gui/browser_ui.c:14039` | `* on its face does in Firefox (spec/page_view.md, tanda 40). */ static const rd_block *submit_pro...` |
| `GET` | function | `gui/browser_ui.c:1480` | `* a GET (Zero Trust). cfg->policy is restored before returning. */ static sf_status fetch_post_na...` |
| `GET` | function | `gui/browser_ui.c:14380` | `* the network under weaker rules than a GET (Zero Trust). */ static void do_submit_post(browser_w...` |
| `H2R` | macro | `gui/browser_ui.c:12308` | `#define H2R(p,q,t)` |
| `HIST_STEP_DEPTH_MAX` | macro | `gui/browser_ui.c:2233` | `#define HIST_STEP_DEPTH_MAX` |
| `HarfBuzz` | function | `gui/browser_ui.c:3736` | `* descriptor via HarfBuzz (text_shape);` |
| `JS_NAV_MAX` | macro | `gui/browser_ui.c:2231` | `#define JS_NAV_MAX` |
| `JS_TICKS_PER_LOAD` | macro | `gui/browser_ui.c:2351` | `#define JS_TICKS_PER_LOAD` |
| `OMNI_MAX_SUGG` | macro | `gui/browser_ui.c:125` | `#define OMNI_MAX_SUGG` |
| `OV_MAX_DEPTH` | macro | `gui/browser_ui.c:11683` | `#define OV_MAX_DEPTH` |
| `PDF_MARGIN` | macro | `gui/browser_ui.c:13274` | `#define PDF_MARGIN` |
| `PDF_PAGE_H` | macro | `gui/browser_ui.c:13273` | `#define PDF_PAGE_H` |
| `PDF_PAGE_W` | macro | `gui/browser_ui.c:13272` | `#define PDF_PAGE_W` |
| `PNG_MARGIN` | macro | `gui/browser_ui.c:13451` | `#define PNG_MARGIN` |
| `PNG_MAX_H` | macro | `gui/browser_ui.c:13452` | `#define PNG_MAX_H` |
| `PNG_PAGE_W` | macro | `gui/browser_ui.c:13438` | `#define PNG_PAGE_W` |
| `RC_BOX_STACK_MAX` | macro | `gui/browser_ui.c:3462` | `#define RC_BOX_STACK_MAX` |
| `RC_COL_FREE_MAX` | macro | `gui/browser_ui.c:6886` | `#define RC_COL_FREE_MAX` |
| `RC_DEFER_BAND_RUNS` | macro | `gui/browser_ui.c:7847` | `#define RC_DEFER_BAND_RUNS` |
| `RC_DEFER_COLS` | macro | `gui/browser_ui.c:7764` | `#define RC_DEFER_COLS` |
| `RC_DEFER_RANGES` | macro | `gui/browser_ui.c:7765` | `#define RC_DEFER_RANGES` |
| `RC_FLOAT_FIT_MIN` | macro | `gui/browser_ui.c:3473` | `#define RC_FLOAT_FIT_MIN` |
| `RC_FLOAT_MAX` | macro | `gui/browser_ui.c:3466` | `#define RC_FLOAT_MAX` |
| `RC_IBOX_MAX` | macro | `gui/browser_ui.c:3460` | `#define RC_IBOX_MAX` |
| `RC_MAX_OUT_OF_FLOW` | macro | `gui/browser_ui.c:7656` | `#define RC_MAX_OUT_OF_FLOW` |
| `ROW_PAINT_ALL` | macro | `gui/browser_ui.c:11462` | `#define ROW_PAINT_ALL` |
| `ROW_PAINT_BAND` | macro | `gui/browser_ui.c:11463` | `#define ROW_PAINT_BAND` |
| `ROW_PAINT_CONTENT` | macro | `gui/browser_ui.c:11464` | `#define ROW_PAINT_CONTENT` |
| `TABLE` | function | `gui/browser_ui.c:5852` | `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all...` |
| `UI_BTN_LEFT` | macro | `gui/browser_ui.c:95` | `#define UI_BTN_LEFT` |
| `UI_BTN_W` | macro | `gui/browser_ui.c:92` | `#define UI_BTN_W` |
| `UI_BUTTON_HPAD` | macro | `gui/browser_ui.c:142` | `#define UI_BUTTON_HPAD` |
| `UI_CHECK_SZ` | macro | `gui/browser_ui.c:118` | `#define UI_CHECK_SZ` |
| `UI_CONTROL_FONT` | macro | `gui/browser_ui.c:134` | `#define UI_CONTROL_FONT` |
| `UI_CURSOR_SIZE` | macro | `gui/browser_ui.c:123` | `#define UI_CURSOR_SIZE` |
| `UI_FORM_FIELDS_MAX` | macro | `gui/browser_ui.c:143` | `#define UI_FORM_FIELDS_MAX` |
| `UI_HAMBURGER_GAP` | macro | `gui/browser_ui.c:122` | `#define UI_HAMBURGER_GAP` |
| `UI_HAMBURGER_W` | macro | `gui/browser_ui.c:121` | `#define UI_HAMBURGER_W` |
| `UI_IMAGE_MAX_BODY` | macro | `gui/browser_ui.c:232` | `#define UI_IMAGE_MAX_BODY` |
| `UI_INPUT_MEASURE_W` | macro | `gui/browser_ui.c:140` | `#define UI_INPUT_MEASURE_W` |
| `UI_INPUT_PAD` | macro | `gui/browser_ui.c:131` | `#define UI_INPUT_PAD` |
| `UI_INPUT_WIDTH` | macro | `gui/browser_ui.c:141` | `#define UI_INPUT_WIDTH` |
| `UI_LIST_INDENT` | macro | `gui/browser_ui.c:99` | `#define UI_LIST_INDENT` |
| `UI_MARGIN` | macro | `gui/browser_ui.c:94` | `#define UI_MARGIN` |
| `UI_MAX_TABS` | macro | `gui/browser_ui.c:271` | `#define UI_MAX_TABS` |
| `UI_MENU_COUNT` | macro | `gui/browser_ui.c:214` | `#define UI_MENU_COUNT` |
| `UI_MENU_INPUT_H` | macro | `gui/browser_ui.c:120` | `#define UI_MENU_INPUT_H` |
| `UI_MENU_ITEM_H` | macro | `gui/browser_ui.c:116` | `#define UI_MENU_ITEM_H` |
| `UI_MENU_LABEL_H` | macro | `gui/browser_ui.c:119` | `#define UI_MENU_LABEL_H` |
| `UI_MENU_PAD` | macro | `gui/browser_ui.c:117` | `#define UI_MENU_PAD` |
| `UI_MENU_W` | macro | `gui/browser_ui.c:115` | `#define UI_MENU_W` |
| `UI_OMNI_ROW_H` | macro | `gui/browser_ui.c:126` | `#define UI_OMNI_ROW_H` |
| `UI_OVERLINE_OFFSET` | macro | `gui/browser_ui.c:151` | `#define UI_OVERLINE_OFFSET` |
| `UI_READER_COLUMN_W` | macro | `gui/browser_ui.c:590` | `#define UI_READER_COLUMN_W` |
| `UI_RELOAD_X` | macro | `gui/browser_ui.c:3107` | `#define UI_RELOAD_X` |
| `UI_RESIZE_MARGIN` | macro | `gui/browser_ui.c:110` | `#define UI_RESIZE_MARGIN` |
| `UI_SCROLLBAR_MIN` | macro | `gui/browser_ui.c:105` | `#define UI_SCROLLBAR_MIN` |
| `UI_SCROLLBAR_PAD` | macro | `gui/browser_ui.c:106` | `#define UI_SCROLLBAR_PAD` |
| `UI_SCROLLBAR_W` | macro | `gui/browser_ui.c:104` | `#define UI_SCROLLBAR_W` |
| `UI_SLICE_MAX` | macro | `gui/browser_ui.c:155` | `#define UI_SLICE_MAX` |
| `UI_STRIKE_OFFSET` | macro | `gui/browser_ui.c:150` | `#define UI_STRIKE_OFFSET` |
| `UI_TABBAR_H` | macro | `gui/browser_ui.c:87` | `#define UI_TABBAR_H` |
| `UI_TAB_CLOSE_W` | macro | `gui/browser_ui.c:91` | `#define UI_TAB_CLOSE_W` |
| `UI_TAB_MAX_W` | macro | `gui/browser_ui.c:89` | `#define UI_TAB_MAX_W` |
| `UI_TAB_MIN_W` | macro | `gui/browser_ui.c:88` | `#define UI_TAB_MIN_W` |
| `UI_TAB_NEW_W` | macro | `gui/browser_ui.c:90` | `#define UI_TAB_NEW_W` |
| `UI_TITLEBAR_H` | macro | `gui/browser_ui.c:86` | `#define UI_TITLEBAR_H` |
| `UI_TOAST_PAD` | macro | `gui/browser_ui.c:124` | `#define UI_TOAST_PAD` |
| `UI_TOOLBAR_H` | macro | `gui/browser_ui.c:85` | `#define UI_TOOLBAR_H` |
| `UI_TWO_PI` | macro | `gui/browser_ui.c:127` | `#define UI_TWO_PI` |
| `UI_UNDERLINE_OFFSET` | macro | `gui/browser_ui.c:148` | `#define UI_UNDERLINE_OFFSET` |
| `UI_UNDERLINE_THICK` | macro | `gui/browser_ui.c:149` | `#define UI_UNDERLINE_THICK` |
| `UI_WIN_BTN_W` | macro | `gui/browser_ui.c:93` | `#define UI_WIN_BTN_W` |
| `_GNU_SOURCE` | macro | `gui/browser_ui.c:12` | `#define _GNU_SOURCE` |
| `add_current_host_to_list` | function | `gui/browser_ui.c:809` | `static void add_current_host_to_list(browser_window *w, int sel)` |
| `again` | function | `gui/browser_ui.c:10243` | `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one...` |
| `allowlisted` | type_alias | `gui/browser_ui.c:1774` | `typedef struct fetch_prep { int allowlisted;` |
| `anchor` | function | `gui/browser_ui.c:8784` | `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is...` |
| `applies` | function | `gui/browser_ui.c:17534` | `* persisted choice applies (prefs_parse already clamped it to a valid mode). */ const char *js_env =...` |
| `apply_click_result` | function | `gui/browser_ui.c:14236` | `static int apply_click_result(browser_window *w, tab_page *page)` |
| `apply_history_ops` | function | `gui/browser_ui.c:14191` | `static void apply_history_ops(browser_window *w, const tab_page *page)` |
| `apply_zoom` | function | `gui/browser_ui.c:606` | `static void apply_zoom(browser_window *w)` |
| `approximation` | function | `gui/browser_ui.c:9079` | `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */ static void oof_s...` |
| `area` | function | `gui/browser_ui.c:3947` | `* box spans its CONTENT area (the font's ascent + descent plus its vertical padding  * and border...` |
| `arrives` | function | `gui/browser_ui.c:2611` | `* on screen until the result arrives (deliver_fetch_result renders it). about:blank  * and local ...` |
| `audio_mark_dead` | function | `gui/browser_ui.c:10202` | `static void audio_mark_dead(browser_window *w)` |
| `audio_spawn` | function | `gui/browser_ui.c:10148` | `static void audio_spawn(browser_window *w, int rate, int channels)` |
| `audio_stop` | function | `gui/browser_ui.c:10234` | `static void audio_stop(browser_window *w)` |
| `audio_write` | function | `gui/browser_ui.c:10219` | `static void audio_write(browser_window *w, const uint8_t *data, size_t len)` |
| `axis` | function | `gui/browser_ui.c:6110` | `* differs: items stack on the vertical main axis (fx_column_place) and align on * the horizontal cross axis...` |
| `balanced_wrap_width` | function | `gui/browser_ui.c:5518` | `static double balanced_wrap_width(cairo_t *cr, const browser_window *w, const ui_theme *th,      ...` |
| `band_common_box` | function | `gui/browser_ui.c:7676` | `static int band_common_box(const rd_doc *doc, size_t start, size_t end)` |
| `band_shared_box` | function | `gui/browser_ui.c:5962` | `static int band_shared_box(const rd_doc *doc, const rc_state *s, size_t start, size_t end);` |
| `behind` | function | `gui/browser_ui.c:7123` | `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old...` |
| `bg` | function | `gui/browser_ui.c:11534` | `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);` |
| `blit_image_box` | function | `gui/browser_ui.c:9920` | `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,                  ...` |
| `block_id` | type_alias | `gui/browser_ui.c:3398` | `typedef struct rc_open_box { int block_id;` |
| `block_in_table_caption` | function | `gui/browser_ui.c:7740` | `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)` |
| `block_is_oof` | function | `gui/browser_ui.c:5864` | `static int block_is_oof(const rd_doc *doc, const rd_block *bk)` |
| `block_leaves_flow` | function | `gui/browser_ui.c:4621` | `static int block_leaves_flow(const rd_doc *doc, const rd_block *bk);` |
| `block_margins` | function | `gui/browser_ui.c:3910` | `static void block_margins(const ui_theme *th, const rd_block *b,                           double...` |
| `block_style` | function | `gui/browser_ui.c:3883` | `static void block_style(const ui_theme *th, const rd_block *b,                         double *si...` |
| `block_text_style` | function | `gui/browser_ui.c:4872` | `static void block_text_style(const browser_window *w, const ui_theme *th, const rd_block *b,     ...` |
| `blocking` | function | `gui/browser_ui.c:10530` | `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);` |
| `body` | function | `gui/browser_ui.c:2418` | `* every served CSS body (serial and pool paths alike). */ font_stash_reset(w);` |
| `bookmark_toggle_current` | function | `gui/browser_ui.c:979` | `static void bookmark_toggle_current(browser_window *w)` |
| `box` | function | `gui/browser_ui.c:12802` | `* content belongs to that box (painted by its own positioned entry). */     if (sub == NULL)` |
| `box_edge_px` | function | `gui/browser_ui.c:5135` | `static double box_edge_px(int wpx)` |
| `box_forms_stacking_context` | function | `gui/browser_ui.c:11814` | `static int box_forms_stacking_context(const pv_box_def *def)` |
| `box_is_strict_descendant` | function | `gui/browser_ui.c:5237` | `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)` |
| `box_line_visible` | function | `gui/browser_ui.c:6873` | `static int box_line_visible(int style)` |
| `box_margin_bottom` | function | `gui/browser_ui.c:7104` | `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)` |
| `box_margin_top` | function | `gui/browser_ui.c:7097` | `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)` |
| `box_pad_px` | function | `gui/browser_ui.c:1170` | `static double box_pad_px(int px_val, int pct_pm, double cb_w);` |
| `box_path` | function | `gui/browser_ui.c:10785` | `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)` |
| `box_path4` | function | `gui/browser_ui.c:4539` | `static void box_path4(cairo_t *cr, double x, double y, double w, double h, const double *rc);` |
| `box_path_has` | function | `gui/browser_ui.c:7431` | `static int box_path_has(const rd_doc *doc, int block_id, int want)` |
| `box_path_of` | function | `gui/browser_ui.c:7660` | `static int box_path_of(const rd_doc *doc, int block_id, int *out)` |
| `box_pointer_events_none` | function | `gui/browser_ui.c:13950` | `static int box_pointer_events_none(const rd_doc *doc, int block_id)` |
| `box_shrink_width` | function | `gui/browser_ui.c:7471` | `static double box_shrink_width(cairo_t *cr, const browser_window *w,                             ...` |
| `box_transform_matrix` | function | `gui/browser_ui.c:11864` | `static int box_transform_matrix(const pv_box_def *def, double box_x, double box_y,               ...` |
| `box_under` | function | `gui/browser_ui.c:5803` | `static int box_under(const rd_doc *doc, int child, int anc)` |
| `browser_window` | struct | `gui/browser_ui.c:295` | `` |
| `bs` | type_alias | `gui/browser_ui.c:279` | `typedef struct tab_ctx { browser_state bs;` |
| `buffer_release` | function | `gui/browser_ui.c:617` | `static void buffer_release(void *data, struct wl_buffer *wl_buffer)` |
| `bui_blend_operator` | function | `gui/browser_ui.c:11992` | `static cairo_operator_t bui_blend_operator(int mix_blend)` |
| `bui_grad_color_at` | function | `gui/browser_ui.c:10929` | `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,                    ...` |
| `bui_paint_backdrop_blur` | function | `gui/browser_ui.c:12130` | `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,                          ...` |
| `bui_pop_group_composite` | function | `gui/browser_ui.c:12188` | `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms)` |
| `bui_skew_tan` | function | `gui/browser_ui.c:11857` | `static double bui_skew_tan(int deg)` |
| `build_file_origin` | function | `gui/browser_ui.c:698` | `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)` |
| `build_host_filter` | function | `gui/browser_ui.c:725` | `static hb_set *build_host_filter(void)` |
| `build_impersonate_optin` | function | `gui/browser_ui.c:775` | `static int build_impersonate_optin(void)` |
| `build_js_filter` | function | `gui/browser_ui.c:772` | `static hb_set *build_js_filter(void)` |
| `builds` | function | `gui/browser_ui.c:6596` | `* wraps beside it: the same band the top level builds (spec/float.md). */ const rd_block *fk = rd_at(doc, k);` |
| `button_box_width` | function | `gui/browser_ui.c:9476` | `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,               ...` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11176` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11179` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11219` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11222` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11280` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11283` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11375` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11377` | `cairo_set_dash(cr, (double[])` |
| `caller` | function | `gui/browser_ui.c:13638` | `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the  * out_path ve...` |
| `chain` | function | `gui/browser_ui.c:8678` | `* chain (the box that left the normal flow at this pen position);` |
| `child_cont_at_level` | function | `gui/browser_ui.c:5759` | `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)` |
| `children` | function | `gui/browser_ui.c:7114` | `* own content rect onto the stack so its children (text or nested boxes) place inside  * it. At t...` |
| `clear_doc` | function | `gui/browser_ui.c:1356` | `static void clear_doc(browser_window *w)` |
| `clipboard_copy` | function | `gui/browser_ui.c:16677` | `static void clipboard_copy(browser_window *w)` |
| `close_all_boxes` | function | `gui/browser_ui.c:5731` | `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);` |
| `close_top_box` | function | `gui/browser_ui.c:6932` | `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)` |
| `col` | type_alias | `gui/browser_ui.c:7783` | `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];` |
| `col_founder_box` | type_alias | `gui/browser_ui.c:3474` | `typedef struct rc_state { /* Inside a float band column whose width was SHRUNK TO FIT: the float * founder's own box...` |
| `col_spend_free_space` | function | `gui/browser_ui.c:6887` | `static void col_spend_free_space(rc_layout *L, const rc_open_box *ob, double free_px)` |
| `collect_local_storage` | function | `gui/browser_ui.c:2306` | `static void collect_local_storage(browser_window *w, const tab_page *page)` |
| `column` | function | `gui/browser_ui.c:7337` | `*  * Returns the height of the tallest column (0 when there is nothing to fragment). */ static do...` |
| `columns` | function | `gui/browser_ui.c:7445` | `* each card made 1080px columns (huggingface, github). */ static int deepest_open_on_path(const r...` |
| `compositing` | function | `gui/browser_ui.c:12635` | `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context...` |
| `compute_page_js` | function | `gui/browser_ui.c:2253` | `static int compute_page_js(const browser_window *w)` |
| `cont_in_view` | function | `gui/browser_ui.c:5778` | `static int cont_in_view(const rd_doc *doc, int cid)` |
| `container` | function | `gui/browser_ui.c:5347` | `* were the container (github's tab pill). */ int item = item_at_level(doc, rd_at(doc, k), cid);` |
| `container_box_of` | function | `gui/browser_ui.c:5315` | `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)` |
| `container_inner_h` | function | `gui/browser_ui.c:5930` | `static double container_inner_h(const rd_doc *doc, const pv_cont_def *cdv, double content_w)` |
| `content_font` | function | `gui/browser_ui.c:3769` | `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,             ...` |
| `content_font_ex` | function | `gui/browser_ui.c:3747` | `static void content_font_ex(cairo_t *cr, double size, int bold, int italic, int family,          ...` |
| `content_geometry` | function | `gui/browser_ui.c:2947` | `static void content_geometry(const browser_window *w, double *top, double *height)` |
| `content_margin_x` | function | `gui/browser_ui.c:2977` | `static double content_margin_x(const browser_window *w)` |
| `content_margins_x` | function | `gui/browser_ui.c:2988` | `static double content_margins_x(const browser_window *w)` |
| `content_width` | function | `gui/browser_ui.c:2993` | `static double content_width(const browser_window *w)` |
| `context` | function | `gui/browser_ui.c:7729` | `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document...` |
| `convention` | function | `gui/browser_ui.c:11242` | `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE \|\| style...` |
| `cost` | function | `gui/browser_ui.c:17765` | `* measured cost (floor 33 ms = the existing ~30 fps ceiling):              * cheap pages paint at...` |
| `count` | function | `gui/browser_ui.c:9060` | `* the box count (a hostile parent cycle terminates). */ static int oof_depth(const rd_doc *doc, s...` |
| `css_replaced_box` | function | `gui/browser_ui.c:4750` | `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,                ...` |
| `cursor_at_point` | function | `gui/browser_ui.c:13966` | `static int cursor_at_point(browser_window *w, double px, double py)` |
| `data_device_data_offer` | function | `gui/browser_ui.c:16472` | `static void data_device_data_offer(void *data, struct wl_data_device *dev,                       ...` |
| `data_device_drop` | function | `gui/browser_ui.c:16513` | `static void data_device_drop(void *d, struct wl_data_device *dev)` |
| `data_device_enter` | function | `gui/browser_ui.c:16503` | `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,              ...` |
| `data_device_leave` | function | `gui/browser_ui.c:16508` | `static void data_device_leave(void *d, struct wl_data_device *dev)` |
| `data_device_motion` | function | `gui/browser_ui.c:16509` | `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,                  ...` |
| `data_device_selection` | function | `gui/browser_ui.c:16484` | `static void data_device_selection(void *data, struct wl_data_device *dev,                        ...` |
| `data_offer_action` | function | `gui/browser_ui.c:16462` | `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)` |
| `data_offer_source_actions` | function | `gui/browser_ui.c:16459` | `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)` |
| `data_source_cancelled` | function | `gui/browser_ui.c:16524` | `static void data_source_cancelled(void *data, struct wl_data_source *src)` |
| `data_source_send` | function | `gui/browser_ui.c:16530` | `static void data_source_send(void *data, struct wl_data_source *src,                             ...` |
| `data_source_target` | function | `gui/browser_ui.c:16543` | `static void data_source_target(void *d, struct wl_data_source *s, const char *m)` |
| `deco_configure` | function | `gui/browser_ui.c:15380` | `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)` |
| `deepest_open_on_path` | function | `gui/browser_ui.c:5737` | `static int deepest_open_on_path(const rc_state *outer, const rd_doc *doc, int block_id);` |
| `def_declared_width` | function | `gui/browser_ui.c:5575` | `static double def_declared_width(const pv_box_def *d, double avail_w)` |
| `def_width_cap` | function | `gui/browser_ui.c:5569` | `static double def_width_cap(const pv_box_def *d, double avail_w)` |
| `defer_append` | function | `gui/browser_ui.c:7927` | `static int defer_append(rc_defer *d, int key, int side,                         int ml, int mlpct...` |
| `defer_flush` | function | `gui/browser_ui.c:7961` | `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,                      ...` |
| `defer_key_block` | function | `gui/browser_ui.c:7804` | `static int defer_key_block(const rd_block *bk)` |
| `defer_root_of` | function | `gui/browser_ui.c:9453` | `static int defer_root_of(const rc_layout *L, int bid)` |
| `defer_wants` | function | `gui/browser_ui.c:9461` | `static int defer_wants(const rc_layout *L, int bid, int only_root)` |
| `delay` | function | `gui/browser_ui.c:369` | `* timer delay (tab_page.next_timer_ms);` |
| `deliver_fetch_result` | function | `gui/browser_ui.c:14494` | `static void deliver_fetch_result(browser_window *w, fetch_job *j)` |
| `descriptor` | function | `gui/browser_ui.c:6317` | `* placement rides the nested descriptor (spec/grid_areas.md 6). */ int nbc = child_cont_at_level(doc, bk, cid);` |
| `descriptors` | function | `gui/browser_ui.c:10162` | `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection —...` |
| `destroy_buffer` | function | `gui/browser_ui.c:623` | `static void destroy_buffer(browser_window *w)` |
| `dies` | function | `gui/browser_ui.c:10139` | `* child dies (exec failed, device busy, daemon absent) is detected on the  * next PCM write (EPIP...` |
| `dispatch_js_event` | function | `gui/browser_ui.c:16812` | `static void dispatch_js_event(browser_window *w, dom_node_id node_id,                            ...` |
| `do_load` | function | `gui/browser_ui.c:2221` | `static void do_load(browser_window *w, const char *url);` |
| `down` | function | `gui/browser_ui.c:16026` | `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void...` |
| `drain_fetch_results` | function | `gui/browser_ui.c:14548` | `static void drain_fetch_results(browser_window *w)` |
| `draw_clock` | function | `gui/browser_ui.c:14767` | `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,                ...` |
| `draw_hamburger` | function | `gui/browser_ui.c:14779` | `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)` |
| `draw_hover_url` | function | `gui/browser_ui.c:14928` | `static double draw_hover_url(cairo_t *cr, browser_window *w)` |
| `draw_menu` | function | `gui/browser_ui.c:14817` | `static void draw_menu(cairo_t *cr, browser_window *w)` |
| `draw_omnibox` | function | `gui/browser_ui.c:15045` | `static void draw_omnibox(cairo_t *cr, browser_window *w)` |
| `draw_reload` | function | `gui/browser_ui.c:14795` | `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)` |
| `draw_scrollbar` | function | `gui/browser_ui.c:3062` | `static void draw_scrollbar(cairo_t *cr, const browser_window *w)` |
| `draw_slice` | function | `gui/browser_ui.c:3818` | `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)` |
| `draw_tabstrip` | function | `gui/browser_ui.c:14990` | `static void draw_tabstrip(cairo_t *cr, browser_window *w)` |
| `draw_text` | function | `gui/browser_ui.c:3177` | `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)` |
| `draw_toast` | function | `gui/browser_ui.c:14960` | `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)` |
| `drop_repl_worker` | function | `gui/browser_ui.c:2342` | `static void drop_repl_worker(browser_window *w)` |
| `element` | function | `gui/browser_ui.c:15422` | `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand  * even without...` |
| `emit_replaced_row` | function | `gui/browser_ui.c:4759` | `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,                 ...` |
| `ensure_buffer` | function | `gui/browser_ui.c:629` | `static int ensure_buffer(browser_window *w)` |
| `ensure_download_dir` | function | `gui/browser_ui.c:14414` | `static int ensure_download_dir(char *out, size_t outsz)` |
| `exactly` | function | `gui/browser_ui.c:11438` | `* the resolved size exactly (like the SVG path above): routing through * paint_image_row would re-resolve a % width...` |
| `export_pdf` | function | `gui/browser_ui.c:13396` | `static void export_pdf(browser_window *w)` |
| `export_png` | function | `gui/browser_ui.c:13604` | `static void export_png(browser_window *w)` |
| `family` | type_alias | `gui/browser_ui.c:4112` | `typedef struct rc_ext { int family;` |
| `family_face` | function | `gui/browser_ui.c:3725` | `static const char *family_face(int family)` |
| `fbw_console_lines` | function | `gui/browser_ui.c:15539` | `static size_t fbw_console_lines(const fb_buffer *log)` |
| `fbw_level_rgb` | function | `gui/browser_ui.c:15528` | `static void fbw_level_rgb(int level, double *r, double *g, double *b)` |
| `fbw_split_y` | function | `gui/browser_ui.c:15492` | `static double fbw_split_y(const freebug_window *fb)` |
| `fbw_toplevel_close` | function | `gui/browser_ui.c:15797` | `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)` |
| `fbw_toplevel_configure` | function | `gui/browser_ui.c:15788` | `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,                           ...` |
| `fbw_xdg_surface_configure` | function | `gui/browser_ui.c:15780` | `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)` |
| `fetch_follow_navigable` | function | `gui/browser_ui.c:1444` | `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,                         ...` |
| `fetch_job` | struct | `gui/browser_ui.c:1855` | `` |
| `fetch_job_free` | function | `gui/browser_ui.c:1887` | `static void fetch_job_free(fetch_job *j)` |
| `fetch_launch` | function | `gui/browser_ui.c:1979` | `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,                ...` |
| `fetch_prep` | struct | `gui/browser_ui.c:1774` | `` |
| `fetch_thread` | function | `gui/browser_ui.c:1931` | `static void *fetch_thread(void *arg)` |
| `fields` | function | `gui/browser_ui.c:275` | `* fields (so the 200+ render/event call sites stay unchanged);` |
| `fill` | function | `gui/browser_ui.c:12533` | `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in...` |
| `find_bg_image` | function | `gui/browser_ui.c:1148` | `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)` |
| `find_input_state` | function | `gui/browser_ui.c:1348` | `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)` |
| `first` | function | `gui/browser_ui.c:1673` | `* Navigation: clear the registry first (faces are per document). Untrusted:  * no-op (fetch NULL)...` |
| `flex_item_basis` | function | `gui/browser_ui.c:5667` | `static double flex_item_basis(cairo_t *cr, const browser_window *w,                              ...` |
| `flex_item_min_main` | function | `gui/browser_ui.c:5706` | `static double flex_item_min_main(cairo_t *cr, const browser_window *w,                           ...` |
| `flow` | function | `gui/browser_ui.c:6673` | `* it collapse their vertical margins with each other exactly as in * the main flow (CSS 2.1 8.3.1), and none escapes...` |
| `flow_emit_frag` | function | `gui/browser_ui.c:4145` | `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,                  ...` |
| `flow_smallcaps_word` | function | `gui/browser_ui.c:4205` | `static double flow_smallcaps_word(cairo_t *cr, rc_layout *L, rc_state *s,                        ...` |
| `flow_text` | function | `gui/browser_ui.c:4268` | `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,                ...` |
| `flow_text_block` | function | `gui/browser_ui.c:4883` | `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,                  ...` |
| `flush_line` | function | `gui/browser_ui.c:4009` | `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)` |
| `foldback_session_cookies` | function | `gui/browser_ui.c:2316` | `static void foldback_session_cookies(const char *url, const char *jar)` |
| `font_size` | type_alias | `gui/browser_ui.c:3196` | `typedef struct rc_frag { double x, width, font_size;` |
| `frag_at_point` | function | `gui/browser_ui.c:14058` | `static dom_node_id frag_at_point(browser_window *w, double px, double py,                        ...` |
| `frag_styled` | function | `gui/browser_ui.c:3831` | `static int frag_styled(const rc_frag *f)` |
| `fragment` | function | `gui/browser_ui.c:11759` | `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using  * blk->block_id alo...` |
| `free_images` | function | `gui/browser_ui.c:1109` | `static void free_images(browser_window *w)` |
| `free_inputs` | function | `gui/browser_ui.c:1101` | `static void free_inputs(browser_window *w)` |
| `free_live_page` | function | `gui/browser_ui.c:2774` | `static void free_live_page(browser_window *w)` |
| `freebug_copy_console` | function | `gui/browser_ui.c:16555` | `static void freebug_copy_console(browser_window *w)` |
| `freebug_destroy` | function | `gui/browser_ui.c:15842` | `static void freebug_destroy(browser_window *w)` |
| `freebug_ensure_buffer` | function | `gui/browser_ui.c:15501` | `static int freebug_ensure_buffer(freebug_window *fb)` |
| `freebug_eval` | function | `gui/browser_ui.c:15898` | `static void freebug_eval(browser_window *w)` |
| `freebug_handle_key` | function | `gui/browser_ui.c:15938` | `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,                              ...` |
| `freebug_hide` | function | `gui/browser_ui.c:15764` | `static void freebug_hide(browser_window *w)` |
| `freebug_is_open` | function | `gui/browser_ui.c:15853` | `static int freebug_is_open(const browser_window *w)` |
| `freebug_owns_surface` | function | `gui/browser_ui.c:15849` | `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)` |
| `freebug_paint` | function | `gui/browser_ui.c:15552` | `static void freebug_paint(freebug_window *fb)` |
| `freebug_pointer_axis` | function | `gui/browser_ui.c:16014` | `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)` |
| `freebug_pointer_button` | function | `gui/browser_ui.c:15973` | `static void freebug_pointer_button(browser_window *w, uint32_t serial,                           ...` |
| `freebug_pointer_motion` | function | `gui/browser_ui.c:15992` | `static void freebug_pointer_motion(browser_window *w)` |
| `freebug_redraw` | function | `gui/browser_ui.c:15760` | `static void freebug_redraw(browser_window *w)` |
| `freebug_redraw_fb` | function | `gui/browser_ui.c:15751` | `static void freebug_redraw_fb(freebug_window *fb)` |
| `freebug_repl_worker` | function | `gui/browser_ui.c:15860` | `static tab *freebug_repl_worker(browser_window *w)` |
| `freebug_show` | function | `gui/browser_ui.c:15807` | `static void freebug_show(browser_window *w)` |
| `freebug_toggle` | function | `gui/browser_ui.c:15837` | `static void freebug_toggle(browser_window *w)` |
| `freebug_window` | type_alias | `gui/browser_ui.c:567` | `typedef struct freebug_window freebug_window;` |
| `freebug_window` | struct | `gui/browser_ui.c:15469` | `` |
| `freedom_write_dir` | function | `gui/browser_ui.c:784` | `static int freedom_write_dir(char *out, size_t cap)` |
| `geom_from_layout` | function | `gui/browser_ui.c:12944` | `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,                 ...` |
| `go_omnibox` | function | `gui/browser_ui.c:16105` | `static void go_omnibox(browser_window *w)` |
| `grad_stop` | function | `gui/browser_ui.c:10914` | `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)` |
| `gui_css_sink` | function | `gui/browser_ui.c:1605` | `static void gui_css_sink(void *vctx, const char *url,                          const char *body, ...` |
| `gui_subresource_fetch` | function | `gui/browser_ui.c:1521` | `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,                ...` |
| `gutter` | function | `gui/browser_ui.c:586` | `* gutter (content_margin) is intentionally left unzoomed, like a browser's text  * zoom. The PDF ...` |
| `h` | type_alias | `gui/browser_ui.c:3285` | `typedef struct rc_box { double x, top, w, h;` |
| `handle_key_press` | function | `gui/browser_ui.c:16870` | `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,              ...` |
| `have` | function | `gui/browser_ui.c:8858` | `* as they always have (spec/float.md §6b.3). The line still open beside * the previous float is committed first, at...` |
| `hb_is_allowlisted` | function | `gui/browser_ui.c:1737` | `&& hb_is_allowlisted(w->hosts, ihost);` |
| `history_step` | function | `gui/browser_ui.c:14203` | `static void history_step(browser_window *w, int steps)` |
| `host_from_url` | function | `gui/browser_ui.c:1042` | `static int host_from_url(const char *url, char *out, size_t outsz)` |
| `hot_actionable` | function | `gui/browser_ui.c:3140` | `static int hot_actionable(const browser_window *w, ui_hot hot)` |
| `html_center_offset` | function | `gui/browser_ui.c:3003` | `static double html_center_offset(const browser_window *w)` |
| `ibx_advance` | function | `gui/browser_ui.c:4260` | `static void ibx_advance(const rc_layout *L, rc_state *s, double adv)` |
| `image_display_size` | function | `gui/browser_ui.c:1234` | `static int image_display_size(const browser_window *w, const rd_block *blk,                      ...` |
| `in` | function | `gui/browser_ui.c:13795` | `* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);` |
| `init_net_config` | function | `gui/browser_ui.c:1017` | `static void init_net_config(browser_window *w)` |
| `inlines` | function | `gui/browser_ui.c:4628` | `* next run may also be a replaced element without its own break: consecutive  * atomic inlines (`...` |
| `input_box_width` | function | `gui/browser_ui.c:9467` | `static double input_box_width(double content_w)` |
| `input_inline_eligible` | function | `gui/browser_ui.c:4547` | `static int input_inline_eligible(const rd_block *b)` |
| `input_inline_size` | function | `gui/browser_ui.c:4561` | `static int input_inline_size(cairo_t *cr, const ui_theme *th, const rd_block *b,                 ...` |
| `input_is_editable` | function | `gui/browser_ui.c:1095` | `static int input_is_editable(int input_type)` |
| `input_is_interactive` | function | `gui/browser_ui.c:1089` | `static int input_is_interactive(int input_type)` |
| `insert_pasted_text` | function | `gui/browser_ui.c:16613` | `static void insert_pasted_text(browser_window *w, const char *text, size_t len)` |
| `is_http_url` | function | `gui/browser_ui.c:1031` | `static int is_http_url(const char *s)` |
| `is_https_url` | function | `gui/browser_ui.c:1027` | `static int is_https_url(const char *s)` |
| `it` | function | `gui/browser_ui.c:8959` | `* column: flush first so the column lands above it (source order), * then move the anchor — the image bottom is the...` |
| `item_at_level` | function | `gui/browser_ui.c:5744` | `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)` |
| `item_declared_basis` | function | `gui/browser_ui.c:5580` | `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,                       ...` |
| `item_root_box` | function | `gui/browser_ui.c:5116` | `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)` |
| `item_root_box_pass` | function | `gui/browser_ui.c:5049` | `static int item_root_box_pass(const rd_doc *doc, size_t b0, size_t b1, int cbox,                 ...` |
| `item_sides` | struct | `gui/browser_ui.c:5208` | `` |
| `item_sides_at_level` | function | `gui/browser_ui.c:5259` | `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,                   ...` |
| `item_vmargins` | function | `gui/browser_ui.c:5909` | `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,           ...` |
| `items` | function | `gui/browser_ui.c:6776` | `* items (Flexbox 4.2);` |
| `itself` | function | `gui/browser_ui.c:5124` | `* STRETCH itself (box_tree fills the line with it). */ static int css_align_to_bt(int align_kw)` |
| `key` | type_alias | `gui/browser_ui.c:7776` | `typedef struct rc_defer_col { int key;` |
| `key` | function | `gui/browser_ui.c:8844` | `* founders splits by key (stories, rail, footer nav each take * their column);` |
| `key_is_repeatable` | function | `gui/browser_ui.c:17200` | `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)` |
| `key_repeat_arm` | function | `gui/browser_ui.c:17216` | `static void key_repeat_arm(browser_window *w, uint32_t key)` |
| `key_repeat_fire` | function | `gui/browser_ui.c:17240` | `static void key_repeat_fire(browser_window *w)` |
| `key_repeat_stop` | function | `gui/browser_ui.c:17229` | `static void key_repeat_stop(browser_window *w)` |
| `key_sym_to_js_key` | function | `gui/browser_ui.c:16761` | `static const char *key_sym_to_js_key(xkb_keysym_t sym)` |
| `key_sym_to_keycode` | function | `gui/browser_ui.c:16787` | `static int key_sym_to_keycode(xkb_keysym_t sym)` |
| `keyboard_enter` | function | `gui/browser_ui.c:16746` | `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,                         ...` |
| `keyboard_key` | function | `gui/browser_ui.c:17254` | `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,                   ...` |
| `keyboard_keymap` | function | `gui/browser_ui.c:16725` | `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,                             uint...` |
| `keyboard_leave` | function | `gui/browser_ui.c:16753` | `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)` |
| `keyboard_modifiers` | function | `gui/browser_ui.c:17294` | `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,                  ...` |
| `keyboard_repeat_info` | function | `gui/browser_ui.c:17303` | `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)` |
| `kind` | type_alias | `gui/browser_ui.c:3261` | `typedef struct rc_row { rc_rowkind kind;` |
| `layer` | function | `gui/browser_ui.c:11126` | `* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the...` |
| `layout` | function | `gui/browser_ui.c:5653` | `* hypothetical size in the real layout (Flexbox 9.2.3). */ if (ibd != NULL && ibd->box_min_w > 0) base =...` |
| `layout_container` | function | `gui/browser_ui.c:5970` | `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,                 ...` |
| `layout_doc` | function | `gui/browser_ui.c:8624` | `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,                   ...` |
| `layout_float_band` | function | `gui/browser_ui.c:8182` | `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,                ...` |
| `limits` | function | `gui/browser_ui.c:12434` | `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box  * grouped this w...` |
| `line` | function | `gui/browser_ui.c:4338` | `* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the...` |
| `line_limit` | function | `gui/browser_ui.c:3658` | `static double line_limit(const rc_state *s, double content_w)` |
| `lines_at` | function | `gui/browser_ui.c:5500` | `static size_t lines_at(cairo_t *cr, const browser_window *w, const ui_theme *th,                 ...` |
| `link_at_point` | function | `gui/browser_ui.c:13845` | `static const char *link_at_point(browser_window *w, double px, double py)` |
| `load_bg_images` | function | `gui/browser_ui.c:2184` | `static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)` |
| `load_current` | function | `gui/browser_ui.c:16092` | `static void load_current(browser_window *w)` |
| `load_favorites` | function | `gui/browser_ui.c:877` | `static void load_favorites(browser_window *w)` |
| `load_host_file` | function | `gui/browser_ui.c:708` | `static void load_host_file(hb_set *s, const char *dir, const char *name, hb_list list)` |
| `load_images` | function | `gui/browser_ui.c:2100` | `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)` |
| `loop` | function | `gui/browser_ui.c:16604` | `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately...` |
| `made` | function | `gui/browser_ui.c:12252` | `* its zero channels made (255,255,255,alpha 0) -- an invalid * premultiplied value Cairo composites as ADDITIVE...` |
| `main` | function | `gui/browser_ui.c:512` | `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never...` |
| `margin` | function | `gui/browser_ui.c:9227` | `* own left margin (the margin box starts at the anchor point), a right- * anchored one ends at it. Same for the...` |
| `measure_item_content_w` | function | `gui/browser_ui.c:5532` | `static double measure_item_content_w(cairo_t *cr, const browser_window *w,                       ...` |
| `measure_item_w_at` | function | `gui/browser_ui.c:5450` | `static double measure_item_w_at(cairo_t *cr, const browser_window *w,                            ...` |
| `memory` | function | `gui/browser_ui.c:14286` | `* memory (the href pointer, not its contents, was all the old code preserved). */ static void dis...` |
| `menu_item_checked` | function | `gui/browser_ui.c:14635` | `static int menu_item_checked(const browser_window *w, size_t i)` |
| `menu_item_toggle` | function | `gui/browser_ui.c:14657` | `static void menu_item_toggle(browser_window *w, size_t i)` |
| `menu_panel_rect` | function | `gui/browser_ui.c:3151` | `static void menu_panel_rect(const browser_window *w, double *x, double *y,                       ...` |
| `mime_is_text` | function | `gui/browser_ui.c:16441` | `static int mime_is_text(const char *mime)` |
| `mr` | type_alias | `gui/browser_ui.c:5208` | `typedef struct item_sides { double ml, mr;` |
| `multicol_fragment` | function | `gui/browser_ui.c:6870` | `static double multicol_fragment(rc_layout *L, const rc_open_box *ob, double content_bottom);` |
| `nested_cont_basis` | function | `gui/browser_ui.c:5594` | `static double nested_cont_basis(cairo_t *cr, const browser_window *w,                            ...` |
| `nested_stop` | function | `gui/browser_ui.c:7459` | `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)` |
| `newtab_x` | function | `gui/browser_ui.c:2911` | `static double newtab_x(const browser_window *w)` |
| `node_at_point` | function | `gui/browser_ui.c:14031` | `static dom_node_id node_at_point(browser_window *w, double px, double py)` |
| `now_ms` | function | `gui/browser_ui.c:158` | `static uint64_t now_ms(void)` |
| `offset` | function | `gui/browser_ui.c:168` | `* offset (labels and the flag live in one place, no magic indices);` |
| `omni_refresh` | function | `gui/browser_ui.c:923` | `static void omni_refresh(browser_window *w)` |
| `only` | function | `gui/browser_ui.c:1600` | `* Trusted pages only (untrusted CSS is still applied by the worker, but its * fonts never reach the parent...` |
| `open_line` | function | `gui/browser_ui.c:4091` | `static void open_line(rc_layout *L, rc_state *s)` |
| `open_line_height` | function | `gui/browser_ui.c:4076` | `static double open_line_height(const rc_state *s, const ui_theme *th)` |
| `origin` | function | `gui/browser_ui.c:13717` | `* top_url is the page origin (https or file://);` |
| `ov_box_bounds` | function | `gui/browser_ui.c:11715` | `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)` |
| `ov_box_clips` | function | `gui/browser_ui.c:11687` | `static int ov_box_clips(const pv_box_def *d)` |
| `ov_collect_chain` | function | `gui/browser_ui.c:11694` | `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)` |
| `ov_content_rect` | function | `gui/browser_ui.c:11739` | `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,                             do...` |
| `overflow` | function | `gui/browser_ui.c:12593` | `* adding two of them in int was signed overflow (UB, found by UBSan). */ double ox = left + bx->x +...` |
| `own` | function | `gui/browser_ui.c:6695` | `* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and...` |
| `page_js_host_allowlisted` | function | `gui/browser_ui.c:2247` | `static int page_js_host_allowlisted(const browser_window *w)` |
| `page_side` | function | `gui/browser_ui.c:2973` | `static double page_side(const browser_window *w, int side)` |
| `page_trusted` | function | `gui/browser_ui.c:1519` | `static int page_trusted(const browser_window *w);` |
| `paint` | function | `gui/browser_ui.c:15079` | `static void paint(browser_window *w)` |
| `paint_bg_layer` | function | `gui/browser_ui.c:10995` | `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,                ...` |
| `paint_box_and_direct_rows` | function | `gui/browser_ui.c:12544` | `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,        ...` |
| `paint_box_decoration` | function | `gui/browser_ui.c:11039` | `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,            ...` |
| `paint_box_decoration_grouped` | function | `gui/browser_ui.c:12503` | `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,                         ...` |
| `paint_box_shadow_layer` | function | `gui/browser_ui.c:10796` | `static void paint_box_shadow_layer(cairo_t *cr, double x, double y, double w, double h,          ...` |
| `paint_content_row` | function | `gui/browser_ui.c:11471` | `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,                ...` |
| `paint_content_row_ex` | function | `gui/browser_ui.c:11478` | `static void paint_content_row_ex(cairo_t *cr, browser_window *w, const rc_layout *L,             ...` |
| `paint_deco_line` | function | `gui/browser_ui.c:11341` | `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,                        ...` |
| `paint_inline_replaced` | function | `gui/browser_ui.c:11426` | `static void paint_inline_replaced(cairo_t *cr, browser_window *w,                                ...` |
| `paint_nested_children` | function | `gui/browser_ui.c:12907` | `static void paint_nested_children(cairo_t *cr, browser_window *w,                                ...` |
| `paint_oof_sub` | function | `gui/browser_ui.c:12652` | `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,                 ...` |
| `paint_png_deferred` | function | `gui/browser_ui.c:13497` | `static void paint_png_deferred(void *ctx, int root)` |
| `paint_png_inflow` | function | `gui/browser_ui.c:13468` | `static void paint_png_inflow(const png_flow_ctx *c, int only_root)` |
| `paint_positioned_one` | function | `gui/browser_ui.c:12690` | `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,             ...` |
| `paint_screen_deferred` | function | `gui/browser_ui.c:13169` | `static void paint_screen_deferred(void *ctx, int root)` |
| `paint_screen_inflow` | function | `gui/browser_ui.c:13055` | `static void paint_screen_inflow(const screen_flow_ctx *c, int only_root)` |
| `paint_structured` | function | `gui/browser_ui.c:13173` | `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,                 ...` |
| `paint_svg_at` | function | `gui/browser_ui.c:11397` | `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,                          doub...` |
| `paint_video_row` | function | `gui/browser_ui.c:10605` | `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,                 ...` |
| `path` | function | `gui/browser_ui.c:6362` | `*          * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when         ...` |
| `pl` | type_alias | `gui/browser_ui.c:1165` | `typedef struct repl_edges { double mt, mr, mb, ml, bt, br, bb, bl, pt, pr, pb, pl;` |
| `place_inline_replaced` | function | `gui/browser_ui.c:4665` | `static int place_inline_replaced(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,     ...` |
| `placeholder_display_size` | function | `gui/browser_ui.c:1300` | `static int placeholder_display_size(const rd_block *blk, double box_w,                           ...` |
| `png_flow_ctx` | struct | `gui/browser_ui.c:13456` | `` |
| `position_doc` | function | `gui/browser_ui.c:9280` | `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,                 ...` |
| `prepare_fetch` | function | `gui/browser_ui.c:1783` | `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,                     ...` |
| `presentation` | function | `gui/browser_ui.c:14655` | `* affect presentation (a repaint, which re-runs layout, suffices);` |
| `proceed` | function | `gui/browser_ui.c:1780` | `* may proceed (cfg and pr->allowlisted are then set);` |
| `produced` | function | `gui/browser_ui.c:4239` | `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target...` |
| `profile_sync` | function | `gui/browser_ui.c:954` | `static void profile_sync(browser_window *w)` |
| `proxy` | function | `gui/browser_ui.c:1014` | `* and enable each proxy ("1" => the default port);` |
| `proxy_addr_from_env` | function | `gui/browser_ui.c:1003` | `static int proxy_addr_from_env(const char *envname, const char *deflt,                           ...` |
| `ptr_axis` | function | `gui/browser_ui.c:16401` | `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,                      uint32...` |
| `ptr_button` | function | `gui/browser_ui.c:16150` | `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,               ...` |
| `ptr_enter` | function | `gui/browser_ui.c:16032` | `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,                       struct wl_...` |
| `ptr_frame` | function | `gui/browser_ui.c:16425` | `static void ptr_frame(void *d, struct wl_pointer *p)` |
| `ptr_leave` | function | `gui/browser_ui.c:16050` | `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)` |
| `ptr_motion` | function | `gui/browser_ui.c:16067` | `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)` |
| `publish_geometry` | function | `gui/browser_ui.c:12975` | `static void publish_geometry(browser_window *w, const rc_layout *L, double left,                 ...` |
| `rc_add_box` | function | `gui/browser_ui.c:3686` | `static rc_box *rc_add_box(rc_layout *L)` |
| `rc_add_frag` | function | `gui/browser_ui.c:3698` | `static rc_frag *rc_add_frag(rc_layout *L)` |
| `rc_add_row` | function | `gui/browser_ui.c:3713` | `static rc_row *rc_add_row(rc_layout *L)` |
| `rc_box` | struct | `gui/browser_ui.c:3285` | `` |
| `rc_box_context` | function | `gui/browser_ui.c:7070` | `static void rc_box_context(const rc_state *s, double content_w,                            double...` |
| `rc_box_copy_decoration` | function | `gui/browser_ui.c:5155` | `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)` |
| `rc_defer` | struct | `gui/browser_ui.c:7783` | `` |
| `rc_defer_col` | struct | `gui/browser_ui.c:7776` | `` |
| `rc_ext` | struct | `gui/browser_ui.c:4112` | `` |
| `rc_float_bottom` | function | `gui/browser_ui.c:3571` | `static double rc_float_bottom(const rc_state *s)` |
| `rc_float_clear` | function | `gui/browser_ui.c:3580` | `static void rc_float_clear(rc_state *s)` |
| `rc_float_fit_line` | function | `gui/browser_ui.c:3639` | `static void rc_float_fit_line(rc_state *s, double line_h)` |
| `rc_float_refresh` | function | `gui/browser_ui.c:3593` | `static void rc_float_refresh(rc_state *s, double line_h)` |
| `rc_frag` | struct | `gui/browser_ui.c:3197` | `` |
| `rc_free` | function | `gui/browser_ui.c:3666` | `static void rc_free(rc_layout *L)` |
| `rc_ibox` | struct | `gui/browser_ui.c:3444` | `` |
| `rc_layout` | struct | `gui/browser_ui.c:3343` | `` |
| `rc_oof_sub` | struct | `gui/browser_ui.c:3341` | `` |

Next: [SYMBOLS_p2.md](SYMBOLS_p2.md)
