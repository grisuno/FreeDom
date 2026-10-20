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
| `ALIVE` | function | `gui/browser_ui.c:2476` | `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or...` |
| `BALANCE_MAX_LINES` | macro | `gui/browser_ui.c:5501` | `#define BALANCE_MAX_LINES` |
| `BUI_CONIC_SLICES` | macro | `gui/browser_ui.c:11469` | `#define BUI_CONIC_SLICES` |
| `FBW_COPY_BTN_H` | macro | `gui/browser_ui.c:16167` | `#define FBW_COPY_BTN_H` |
| `FBW_COPY_BTN_W` | macro | `gui/browser_ui.c:16166` | `#define FBW_COPY_BTN_W` |
| `FBW_GUTTER` | macro | `gui/browser_ui.c:16163` | `#define FBW_GUTTER` |
| `FBW_H` | macro | `gui/browser_ui.c:16159` | `#define FBW_H` |
| `FBW_HEADER` | macro | `gui/browser_ui.c:16160` | `#define FBW_HEADER` |
| `FBW_LINE` | macro | `gui/browser_ui.c:16162` | `#define FBW_LINE` |
| `FBW_MAX_SPLIT` | macro | `gui/browser_ui.c:16165` | `#define FBW_MAX_SPLIT` |
| `FBW_MIN_SPLIT` | macro | `gui/browser_ui.c:16164` | `#define FBW_MIN_SPLIT` |
| `FBW_PAD` | macro | `gui/browser_ui.c:16161` | `#define FBW_PAD` |
| `FBW_W` | macro | `gui/browser_ui.c:16158` | `#define FBW_W` |
| `FLEX_MEASURE_W` | macro | `gui/browser_ui.c:5373` | `#define FLEX_MEASURE_W` |
| `FLEX_MIN_MEASURE_W` | macro | `gui/browser_ui.c:5378` | `#define FLEX_MIN_MEASURE_W` |
| `FONT_STASH_MAX_BYTES` | macro | `gui/browser_ui.c:1529` | `#define FONT_STASH_MAX_BYTES` |
| `FONT_STASH_MAX_SHEETS` | macro | `gui/browser_ui.c:1528` | `#define FONT_STASH_MAX_SHEETS` |
| `Firefox` | function | `gui/browser_ui.c:14724` | `* on its face does in Firefox (spec/page_view.md, tanda 40). */ static const rd_block *submit_pro...` |
| `GET` | function | `gui/browser_ui.c:1431` | `* a GET (Zero Trust). cfg->policy is restored before returning. */ static sf_status fetch_post_na...` |
| `GET` | function | `gui/browser_ui.c:15065` | `* the network under weaker rules than a GET (Zero Trust). */ static void do_submit_post(browser_w...` |
| `H2R` | macro | `gui/browser_ui.c:12926` | `#define H2R(p,q,t)` |
| `HIST_STEP_DEPTH_MAX` | macro | `gui/browser_ui.c:2184` | `#define HIST_STEP_DEPTH_MAX` |
| `HarfBuzz` | function | `gui/browser_ui.c:3703` | `* descriptor via HarfBuzz (text_shape);` |
| `JS_NAV_MAX` | macro | `gui/browser_ui.c:2182` | `#define JS_NAV_MAX` |
| `JS_TICKS_PER_LOAD` | macro | `gui/browser_ui.c:2302` | `#define JS_TICKS_PER_LOAD` |
| `OMNI_MAX_SUGG` | macro | `gui/browser_ui.c:129` | `#define OMNI_MAX_SUGG` |
| `OV_MAX_DEPTH` | macro | `gui/browser_ui.c:12244` | `#define OV_MAX_DEPTH` |
| `PDF_MARGIN` | macro | `gui/browser_ui.c:13957` | `#define PDF_MARGIN` |
| `PDF_PAGE_H` | macro | `gui/browser_ui.c:13956` | `#define PDF_PAGE_H` |
| `PDF_PAGE_W` | macro | `gui/browser_ui.c:13955` | `#define PDF_PAGE_W` |
| `PNG_MARGIN` | macro | `gui/browser_ui.c:14135` | `#define PNG_MARGIN` |
| `PNG_MAX_H` | macro | `gui/browser_ui.c:14136` | `#define PNG_MAX_H` |
| `PNG_PAGE_W` | macro | `gui/browser_ui.c:14122` | `#define PNG_PAGE_W` |
| `RC_BOX_STACK_MAX` | macro | `gui/browser_ui.c:3429` | `#define RC_BOX_STACK_MAX` |
| `RC_COL_FREE_MAX` | macro | `gui/browser_ui.c:7011` | `#define RC_COL_FREE_MAX` |
| `RC_DEFER_BAND_RUNS` | macro | `gui/browser_ui.c:8128` | `#define RC_DEFER_BAND_RUNS` |
| `RC_DEFER_COLS` | macro | `gui/browser_ui.c:8045` | `#define RC_DEFER_COLS` |
| `RC_DEFER_RANGES` | macro | `gui/browser_ui.c:8046` | `#define RC_DEFER_RANGES` |
| `RC_FLOAT_FIT_MIN` | macro | `gui/browser_ui.c:3440` | `#define RC_FLOAT_FIT_MIN` |
| `RC_FLOAT_MAX` | macro | `gui/browser_ui.c:3433` | `#define RC_FLOAT_MAX` |
| `RC_IBOX_MAX` | macro | `gui/browser_ui.c:3427` | `#define RC_IBOX_MAX` |
| `RC_MAX_OUT_OF_FLOW` | macro | `gui/browser_ui.c:7875` | `#define RC_MAX_OUT_OF_FLOW` |
| `ROW_PAINT_ALL` | macro | `gui/browser_ui.c:12023` | `#define ROW_PAINT_ALL` |
| `ROW_PAINT_BAND` | macro | `gui/browser_ui.c:12024` | `#define ROW_PAINT_BAND` |
| `ROW_PAINT_CONTENT` | macro | `gui/browser_ui.c:12025` | `#define ROW_PAINT_CONTENT` |
| `TABLE` | function | `gui/browser_ui.c:5899` | `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all...` |
| `UI_BTN_LEFT` | macro | `gui/browser_ui.c:99` | `#define UI_BTN_LEFT` |
| `UI_BTN_W` | macro | `gui/browser_ui.c:96` | `#define UI_BTN_W` |
| `UI_BUTTON_HPAD` | macro | `gui/browser_ui.c:146` | `#define UI_BUTTON_HPAD` |
| `UI_CHECK_SZ` | macro | `gui/browser_ui.c:122` | `#define UI_CHECK_SZ` |
| `UI_CONTROL_FONT` | macro | `gui/browser_ui.c:138` | `#define UI_CONTROL_FONT` |
| `UI_CURSOR_SIZE` | macro | `gui/browser_ui.c:127` | `#define UI_CURSOR_SIZE` |
| `UI_FORM_FIELDS_MAX` | macro | `gui/browser_ui.c:147` | `#define UI_FORM_FIELDS_MAX` |
| `UI_HAMBURGER_GAP` | macro | `gui/browser_ui.c:126` | `#define UI_HAMBURGER_GAP` |
| `UI_HAMBURGER_W` | macro | `gui/browser_ui.c:125` | `#define UI_HAMBURGER_W` |
| `UI_IMAGE_MAX_BODY` | macro | `gui/browser_ui.c:236` | `#define UI_IMAGE_MAX_BODY` |
| `UI_INPUT_MEASURE_W` | macro | `gui/browser_ui.c:144` | `#define UI_INPUT_MEASURE_W` |
| `UI_INPUT_PAD` | macro | `gui/browser_ui.c:135` | `#define UI_INPUT_PAD` |
| `UI_INPUT_WIDTH` | macro | `gui/browser_ui.c:145` | `#define UI_INPUT_WIDTH` |
| `UI_LIST_INDENT` | macro | `gui/browser_ui.c:103` | `#define UI_LIST_INDENT` |
| `UI_MARGIN` | macro | `gui/browser_ui.c:98` | `#define UI_MARGIN` |
| `UI_MAX_TABS` | macro | `gui/browser_ui.c:275` | `#define UI_MAX_TABS` |
| `UI_MENU_COUNT` | macro | `gui/browser_ui.c:218` | `#define UI_MENU_COUNT` |
| `UI_MENU_INPUT_H` | macro | `gui/browser_ui.c:124` | `#define UI_MENU_INPUT_H` |
| `UI_MENU_ITEM_H` | macro | `gui/browser_ui.c:120` | `#define UI_MENU_ITEM_H` |
| `UI_MENU_LABEL_H` | macro | `gui/browser_ui.c:123` | `#define UI_MENU_LABEL_H` |
| `UI_MENU_PAD` | macro | `gui/browser_ui.c:121` | `#define UI_MENU_PAD` |
| `UI_MENU_W` | macro | `gui/browser_ui.c:119` | `#define UI_MENU_W` |
| `UI_OMNI_ROW_H` | macro | `gui/browser_ui.c:130` | `#define UI_OMNI_ROW_H` |
| `UI_OVERLINE_OFFSET` | macro | `gui/browser_ui.c:155` | `#define UI_OVERLINE_OFFSET` |
| `UI_READER_COLUMN_W` | macro | `gui/browser_ui.c:594` | `#define UI_READER_COLUMN_W` |
| `UI_RELOAD_X` | macro | `gui/browser_ui.c:3058` | `#define UI_RELOAD_X` |
| `UI_RESIZE_MARGIN` | macro | `gui/browser_ui.c:114` | `#define UI_RESIZE_MARGIN` |
| `UI_SCROLLBAR_MIN` | macro | `gui/browser_ui.c:109` | `#define UI_SCROLLBAR_MIN` |
| `UI_SCROLLBAR_PAD` | macro | `gui/browser_ui.c:110` | `#define UI_SCROLLBAR_PAD` |
| `UI_SCROLLBAR_W` | macro | `gui/browser_ui.c:108` | `#define UI_SCROLLBAR_W` |
| `UI_SLICE_MAX` | macro | `gui/browser_ui.c:159` | `#define UI_SLICE_MAX` |
| `UI_STRIKE_OFFSET` | macro | `gui/browser_ui.c:154` | `#define UI_STRIKE_OFFSET` |
| `UI_TABBAR_H` | macro | `gui/browser_ui.c:91` | `#define UI_TABBAR_H` |
| `UI_TAB_CLOSE_W` | macro | `gui/browser_ui.c:95` | `#define UI_TAB_CLOSE_W` |
| `UI_TAB_MAX_W` | macro | `gui/browser_ui.c:93` | `#define UI_TAB_MAX_W` |
| `UI_TAB_MIN_W` | macro | `gui/browser_ui.c:92` | `#define UI_TAB_MIN_W` |
| `UI_TAB_NEW_W` | macro | `gui/browser_ui.c:94` | `#define UI_TAB_NEW_W` |
| `UI_TITLEBAR_H` | macro | `gui/browser_ui.c:90` | `#define UI_TITLEBAR_H` |
| `UI_TOAST_PAD` | macro | `gui/browser_ui.c:128` | `#define UI_TOAST_PAD` |
| `UI_TOOLBAR_H` | macro | `gui/browser_ui.c:89` | `#define UI_TOOLBAR_H` |
| `UI_TWO_PI` | macro | `gui/browser_ui.c:131` | `#define UI_TWO_PI` |
| `UI_UNDERLINE_OFFSET` | macro | `gui/browser_ui.c:152` | `#define UI_UNDERLINE_OFFSET` |
| `UI_UNDERLINE_THICK` | macro | `gui/browser_ui.c:153` | `#define UI_UNDERLINE_THICK` |
| `UI_WIN_BTN_W` | macro | `gui/browser_ui.c:97` | `#define UI_WIN_BTN_W` |
| `_GNU_SOURCE` | macro | `gui/browser_ui.c:12` | `#define _GNU_SOURCE` |
| `add_current_host_to_list` | function | `gui/browser_ui.c:769` | `static void add_current_host_to_list(browser_window *w, int sel)` |
| `again` | function | `gui/browser_ui.c:10756` | `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one...` |
| `allowlisted` | type_alias | `gui/browser_ui.c:1725` | `typedef struct fetch_prep { int allowlisted;` |
| `anchor` | function | `gui/browser_ui.c:9249` | `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is...` |
| `applies` | function | `gui/browser_ui.c:18238` | `* persisted choice applies (prefs_parse already clamped it to a valid mode). */ const char *js_env =...` |
| `apply_click_result` | function | `gui/browser_ui.c:14921` | `static int apply_click_result(browser_window *w, tab_page *page)` |
| `apply_history_ops` | function | `gui/browser_ui.c:14876` | `static void apply_history_ops(browser_window *w, const tab_page *page)` |
| `apply_zoom` | function | `gui/browser_ui.c:610` | `static void apply_zoom(browser_window *w)` |
| `approximation` | function | `gui/browser_ui.c:9587` | `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */ static void oof_s...` |
| `area` | function | `gui/browser_ui.c:3915` | `* box spans its CONTENT area (the font's ascent + descent plus its vertical padding  * and border...` |
| `arrives` | function | `gui/browser_ui.c:2562` | `* on screen until the result arrives (deliver_fetch_result renders it). about:blank  * and local ...` |
| `audio_mark_dead` | function | `gui/browser_ui.c:10715` | `static void audio_mark_dead(browser_window *w)` |
| `audio_spawn` | function | `gui/browser_ui.c:10661` | `static void audio_spawn(browser_window *w, int rate, int channels)` |
| `audio_stop` | function | `gui/browser_ui.c:10747` | `static void audio_stop(browser_window *w)` |
| `audio_write` | function | `gui/browser_ui.c:10732` | `static void audio_write(browser_window *w, const uint8_t *data, size_t len)` |
| `axis` | function | `gui/browser_ui.c:6154` | `* differs: items stack on the vertical main axis (fx_column_place) and align on * the horizontal cross axis...` |
| `balanced_wrap_width` | function | `gui/browser_ui.c:5502` | `static double balanced_wrap_width(cairo_t *cr, const browser_window *w, const ui_theme *th,      ...` |
| `band_common_box` | function | `gui/browser_ui.c:7947` | `static int band_common_box(const rd_doc *doc, size_t start, size_t end)` |
| `band_common_box_ex` | function | `gui/browser_ui.c:7922` | `static int band_common_box_ex(const rd_doc *doc, size_t start, size_t end, int skip_boxless)` |
| `band_parent_box` | function | `gui/browser_ui.c:7915` | `static int band_parent_box(const rd_doc *doc, const rd_block *bk)` |
| `band_shared_box` | function | `gui/browser_ui.c:6009` | `static int band_shared_box(const rd_doc *doc, const rc_state *s, size_t start, size_t end);` |
| `behind` | function | `gui/browser_ui.c:7285` | `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old...` |
| `bg` | function | `gui/browser_ui.c:12095` | `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);` |
| `blit_image_box` | function | `gui/browser_ui.c:10433` | `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,                  ...` |
| `block_id` | type_alias | `gui/browser_ui.c:3353` | `typedef struct rc_open_box { int block_id;` |
| `block_in_table_caption` | function | `gui/browser_ui.c:8021` | `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)` |
| `block_is_oof` | function | `gui/browser_ui.c:5911` | `static int block_is_oof(const rd_doc *doc, const rd_block *bk)` |
| `block_leaves_flow` | function | `gui/browser_ui.c:4594` | `static int block_leaves_flow(const rd_doc *doc, const rd_block *bk);` |
| `block_margins` | function | `gui/browser_ui.c:3878` | `static void block_margins(const ui_theme *th, const rd_block *b,                           double...` |
| `block_style` | function | `gui/browser_ui.c:3850` | `static void block_style(const ui_theme *th, const rd_block *b,                         double *si...` |
| `block_text_style` | function | `gui/browser_ui.c:4845` | `static void block_text_style(const browser_window *w, const ui_theme *th, const rd_block *b,     ...` |
| `blocking` | function | `gui/browser_ui.c:11043` | `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);` |
| `body` | function | `gui/browser_ui.c:2369` | `* every served CSS body (serial and pool paths alike). */ font_stash_reset(w);` |
| `bookmark_toggle_current` | function | `gui/browser_ui.c:930` | `static void bookmark_toggle_current(browser_window *w)` |
| `box` | function | `gui/browser_ui.c:13431` | `* content belongs to that box (painted by its own positioned entry). */     if (sub == NULL)` |
| `box_edge_px` | function | `gui/browser_ui.c:5115` | `static double box_edge_px(int wpx)` |
| `box_forms_stacking_context` | function | `gui/browser_ui.c:12375` | `static int box_forms_stacking_context(const pv_box_def *def)` |
| `box_is_strict_descendant` | function | `gui/browser_ui.c:5220` | `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)` |
| `box_line_visible` | function | `gui/browser_ui.c:6998` | `static int box_line_visible(int style)` |
| `box_margin_bottom` | function | `gui/browser_ui.c:7266` | `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)` |
| `box_margin_top` | function | `gui/browser_ui.c:7259` | `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)` |
| `box_pad_px` | function | `gui/browser_ui.c:1121` | `static double box_pad_px(int px_val, int pct_pm, double cb_w);` |
| `box_path` | function | `gui/browser_ui.c:11298` | `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)` |
| `box_path4` | function | `gui/browser_ui.c:4512` | `static void box_path4(cairo_t *cr, double x, double y, double w, double h, const double *rc);` |
| `box_path_has` | function | `gui/browser_ui.c:7597` | `static int box_path_has(const rd_doc *doc, int block_id, int want)` |
| `box_path_of` | function | `gui/browser_ui.c:7879` | `static int box_path_of(const rd_doc *doc, int block_id, int *out)` |
| `box_pointer_events_none` | function | `gui/browser_ui.c:14635` | `static int box_pointer_events_none(const rd_doc *doc, int block_id)` |
| `box_shrink_width` | function | `gui/browser_ui.c:7659` | `static double box_shrink_width(cairo_t *cr, const browser_window *w,                             ...` |
| `box_transform_matrix` | function | `gui/browser_ui.c:12426` | `static int box_transform_matrix(const pv_box_def *def, double box_x, double box_y,               ...` |
| `box_under` | function | `gui/browser_ui.c:5850` | `static int box_under(const rd_doc *doc, int child, int anc)` |
| `browser_window` | struct | `gui/browser_ui.c:299` | `` |
| `bs` | type_alias | `gui/browser_ui.c:283` | `typedef struct tab_ctx { browser_state bs;` |
| `buffer_release` | function | `gui/browser_ui.c:621` | `static void buffer_release(void *data, struct wl_buffer *wl_buffer)` |
| `bui_blend_operator` | function | `gui/browser_ui.c:12554` | `static cairo_operator_t bui_blend_operator(int mix_blend)` |
| `bui_build_mask` | function | `gui/browser_ui.c:12701` | `static cairo_surface_t *bui_build_mask(const pv_box_def *def, const rc_box *bx_in,               ...` |
| `bui_gaussian_blur_surface` | function | `gui/browser_ui.c:12580` | `static void bui_gaussian_blur_surface(cairo_surface_t *surf, double sigma)` |
| `bui_grad_color_at` | function | `gui/browser_ui.c:11442` | `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,                    ...` |
| `bui_mask_ctx` | struct | `gui/browser_ui.c:12678` | `` |
| `bui_mask_ref_rect` | function | `gui/browser_ui.c:12685` | `static int bui_mask_ref_rect(const rc_layout *L, int ref, rc_box *out)` |
| `bui_paint_backdrop_blur` | function | `gui/browser_ui.c:12616` | `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,                          ...` |
| `bui_pop_group_composite` | function | `gui/browser_ui.c:12807` | `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms,     ...` |
| `bui_pop_group_composite` | function | `gui/browser_ui.c:13245` | `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,              ...` |
| `bui_pop_group_composite` | function | `gui/browser_ui.c:13560` | `bui_pop_group_composite(cr, cdef, now_ms() - w->page_load_mono_ms, &L->boxes[j], left, origin,   ...` |
| `bui_pop_group_composite` | function | `gui/browser_ui.c:13801` | `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,              ...` |
| `bui_skew_tan` | function | `gui/browser_ui.c:12419` | `static double bui_skew_tan(int deg)` |
| `build_file_origin` | function | `gui/browser_ui.c:702` | `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)` |
| `build_host_filter` | function | `gui/browser_ui.c:716` | `static hb_set *build_host_filter(void)` |
| `build_impersonate_optin` | function | `gui/browser_ui.c:735` | `static int build_impersonate_optin(void)` |
| `build_js_filter` | function | `gui/browser_ui.c:732` | `static hb_set *build_js_filter(void)` |
| `builds` | function | `gui/browser_ui.c:6640` | `* wraps beside it: the same band the top level builds (spec/float.md). */ const rd_block *fk = rd_at(doc, k);` |
| `button_box_width` | function | `gui/browser_ui.c:9989` | `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,               ...` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11731` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11734` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11780` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11783` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11841` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11844` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11936` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:11938` | `cairo_set_dash(cr, (double[])` |
| `caller` | function | `gui/browser_ui.c:14323` | `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the  * out_path ve...` |
| `chain` | function | `gui/browser_ui.c:9142` | `* chain (the box that left the normal flow at this pen position);` |
| `child_cont_at_level` | function | `gui/browser_ui.c:5806` | `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)` |
| `children` | function | `gui/browser_ui.c:7276` | `* own content rect onto the stack so its children (text or nested boxes) place inside  * it. At t...` |
| `clear_doc` | function | `gui/browser_ui.c:1307` | `static void clear_doc(browser_window *w)` |
| `clipboard_copy` | function | `gui/browser_ui.c:17377` | `static void clipboard_copy(browser_window *w)` |
| `close_all_boxes` | function | `gui/browser_ui.c:5756` | `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);` |
| `close_top_box` | function | `gui/browser_ui.c:7057` | `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)` |
| `col` | type_alias | `gui/browser_ui.c:8064` | `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];` |
| `col_founder_box` | type_alias | `gui/browser_ui.c:3441` | `typedef struct rc_state { /* Inside a float band column whose width was SHRUNK TO FIT: the float * founder's own box...` |
| `col_spend_free_space` | function | `gui/browser_ui.c:7012` | `static void col_spend_free_space(rc_layout *L, const rc_open_box *ob, double free_px)` |
| `collect_local_storage` | function | `gui/browser_ui.c:2257` | `static void collect_local_storage(browser_window *w, const tab_page *page)` |
| `column` | function | `gui/browser_ui.c:7503` | `*  * Returns the height of the tallest column (0 when there is nothing to fragment). */ static do...` |
| `columns` | function | `gui/browser_ui.c:7611` | `* each card made 1080px columns (huggingface, github). */ static int deepest_open_on_path(const r...` |
| `compositing` | function | `gui/browser_ui.c:13261` | `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context...` |
| `compute_page_js` | function | `gui/browser_ui.c:2204` | `static int compute_page_js(const browser_window *w)` |
| `cont_in_view` | function | `gui/browser_ui.c:5825` | `static int cont_in_view(const rd_doc *doc, int cid)` |
| `container` | function | `gui/browser_ui.c:5331` | `* were the container (github's tab pill). */ int item = item_at_level(doc, rd_at(doc, k), cid);` |
| `container_box_of` | function | `gui/browser_ui.c:5299` | `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)` |
| `container_inner_h` | function | `gui/browser_ui.c:5977` | `static double container_inner_h(const rd_doc *doc, const pv_cont_def *cdv, double content_w)` |
| `content_font` | function | `gui/browser_ui.c:3736` | `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,             ...` |
| `content_font_ex` | function | `gui/browser_ui.c:3714` | `static void content_font_ex(cairo_t *cr, double size, int bold, int italic, int family,          ...` |
| `content_geometry` | function | `gui/browser_ui.c:2898` | `static void content_geometry(const browser_window *w, double *top, double *height)` |
| `content_margin_x` | function | `gui/browser_ui.c:2928` | `static double content_margin_x(const browser_window *w)` |
| `content_margins_x` | function | `gui/browser_ui.c:2939` | `static double content_margins_x(const browser_window *w)` |
| `content_width` | function | `gui/browser_ui.c:2944` | `static double content_width(const browser_window *w)` |
| `context` | function | `gui/browser_ui.c:8010` | `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document...` |
| `convention` | function | `gui/browser_ui.c:11803` | `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE \|\| style...` |
| `cost` | function | `gui/browser_ui.c:18469` | `* measured cost (floor 33 ms = the existing ~30 fps ceiling):              * cheap pages paint at...` |
| `count` | function | `gui/browser_ui.c:9568` | `* the box count (a hostile parent cycle terminates). */ static int oof_depth(const rd_doc *doc, s...` |
| `css_replaced_box` | function | `gui/browser_ui.c:4723` | `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,                ...` |
| `cursor_at_point` | function | `gui/browser_ui.c:14651` | `static int cursor_at_point(browser_window *w, double px, double py)` |
| `data_device_data_offer` | function | `gui/browser_ui.c:17172` | `static void data_device_data_offer(void *data, struct wl_data_device *dev,                       ...` |
| `data_device_drop` | function | `gui/browser_ui.c:17213` | `static void data_device_drop(void *d, struct wl_data_device *dev)` |
| `data_device_enter` | function | `gui/browser_ui.c:17203` | `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,              ...` |
| `data_device_leave` | function | `gui/browser_ui.c:17208` | `static void data_device_leave(void *d, struct wl_data_device *dev)` |
| `data_device_motion` | function | `gui/browser_ui.c:17209` | `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,                  ...` |
| `data_device_selection` | function | `gui/browser_ui.c:17184` | `static void data_device_selection(void *data, struct wl_data_device *dev,                        ...` |
| `data_offer_action` | function | `gui/browser_ui.c:17162` | `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)` |
| `data_offer_source_actions` | function | `gui/browser_ui.c:17159` | `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)` |
| `data_source_cancelled` | function | `gui/browser_ui.c:17224` | `static void data_source_cancelled(void *data, struct wl_data_source *src)` |
| `data_source_send` | function | `gui/browser_ui.c:17230` | `static void data_source_send(void *data, struct wl_data_source *src,                             ...` |
| `data_source_target` | function | `gui/browser_ui.c:17243` | `static void data_source_target(void *d, struct wl_data_source *s, const char *m)` |
| `deco_configure` | function | `gui/browser_ui.c:16080` | `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)` |
| `deepest_open_on_path` | function | `gui/browser_ui.c:5784` | `static int deepest_open_on_path(const rc_state *outer, const rd_doc *doc, int block_id);` |
| `def_declared_width` | function | `gui/browser_ui.c:5593` | `static double def_declared_width(const pv_box_def *d, double avail_w)` |
| `def_width_cap` | function | `gui/browser_ui.c:5587` | `static double def_width_cap(const pv_box_def *d, double avail_w)` |
| `defer_append` | function | `gui/browser_ui.c:8247` | `static int defer_append(rc_defer *d, int key, int side,                         int ml, int mlpct...` |
| `defer_flush` | function | `gui/browser_ui.c:8329` | `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,                      ...` |
| `defer_key_block` | function | `gui/browser_ui.c:8085` | `static int defer_key_block(const rd_block *bk)` |
| `defer_root_before` | function | `gui/browser_ui.c:13665` | `static int defer_root_before(const rd_doc *doc, const rc_layout *L, size_t a, size_t b)` |
| `defer_root_of` | function | `gui/browser_ui.c:9966` | `static int defer_root_of(const rc_layout *L, int bid)` |
| `defer_root_z` | function | `gui/browser_ui.c:13659` | `static int defer_root_z(const rd_doc *doc, size_t root)` |
| `defer_wants` | function | `gui/browser_ui.c:9974` | `static int defer_wants(const rc_layout *L, int bid, int only_root)` |
| `delay` | function | `gui/browser_ui.c:373` | `* timer delay (tab_page.next_timer_ms);` |
| `deliver_fetch_result` | function | `gui/browser_ui.c:15179` | `static void deliver_fetch_result(browser_window *w, fetch_job *j)` |
| `descriptor` | function | `gui/browser_ui.c:6361` | `* placement rides the nested descriptor (spec/grid_areas.md 6). */ int nbc = child_cont_at_level(doc, bk, cid);` |
| `descriptors` | function | `gui/browser_ui.c:10675` | `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection —...` |
| `destroy_buffer` | function | `gui/browser_ui.c:627` | `static void destroy_buffer(browser_window *w)` |
| `dies` | function | `gui/browser_ui.c:10652` | `* child dies (exec failed, device busy, daemon absent) is detected on the  * next PCM write (EPIP...` |
| `dispatch_js_event` | function | `gui/browser_ui.c:17512` | `static void dispatch_js_event(browser_window *w, dom_node_id node_id,                            ...` |
| `do_load` | function | `gui/browser_ui.c:2172` | `static void do_load(browser_window *w, const char *url);` |
| `down` | function | `gui/browser_ui.c:16726` | `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void...` |
| `drain_fetch_results` | function | `gui/browser_ui.c:15233` | `static void drain_fetch_results(browser_window *w)` |
| `draw_clock` | function | `gui/browser_ui.c:15452` | `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,                ...` |
| `draw_hamburger` | function | `gui/browser_ui.c:15464` | `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)` |
| `draw_hover_url` | function | `gui/browser_ui.c:15613` | `static double draw_hover_url(cairo_t *cr, browser_window *w)` |
| `draw_menu` | function | `gui/browser_ui.c:15502` | `static void draw_menu(cairo_t *cr, browser_window *w)` |
| `draw_omnibox` | function | `gui/browser_ui.c:15730` | `static void draw_omnibox(cairo_t *cr, browser_window *w)` |
| `draw_reload` | function | `gui/browser_ui.c:15480` | `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)` |
| `draw_scrollbar` | function | `gui/browser_ui.c:3013` | `static void draw_scrollbar(cairo_t *cr, const browser_window *w)` |
| `draw_slice` | function | `gui/browser_ui.c:3785` | `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)` |
| `draw_tabstrip` | function | `gui/browser_ui.c:15675` | `static void draw_tabstrip(cairo_t *cr, browser_window *w)` |
| `draw_text` | function | `gui/browser_ui.c:3128` | `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)` |
| `draw_toast` | function | `gui/browser_ui.c:15645` | `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)` |
| `drop_repl_worker` | function | `gui/browser_ui.c:2293` | `static void drop_repl_worker(browser_window *w)` |
| `element` | function | `gui/browser_ui.c:16122` | `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand  * even without...` |
| `emit_replaced_row` | function | `gui/browser_ui.c:4732` | `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,                 ...` |
| `ensure_buffer` | function | `gui/browser_ui.c:633` | `static int ensure_buffer(browser_window *w)` |
| `ensure_download_dir` | function | `gui/browser_ui.c:15099` | `static int ensure_download_dir(char *out, size_t outsz)` |
| `exactly` | function | `gui/browser_ui.c:11999` | `* the resolved size exactly (like the SVG path above): routing through * paint_image_row would re-resolve a % width...` |
| `export_pdf` | function | `gui/browser_ui.c:14080` | `static void export_pdf(browser_window *w)` |
| `export_png` | function | `gui/browser_ui.c:14289` | `static void export_png(browser_window *w)` |
| `family` | type_alias | `gui/browser_ui.c:4085` | `typedef struct rc_ext { int family;` |
| `family_face` | function | `gui/browser_ui.c:3692` | `static const char *family_face(int family)` |
| `fbw_console_lines` | function | `gui/browser_ui.c:16239` | `static size_t fbw_console_lines(const fb_buffer *log)` |
| `fbw_level_rgb` | function | `gui/browser_ui.c:16228` | `static void fbw_level_rgb(int level, double *r, double *g, double *b)` |
| `fbw_split_y` | function | `gui/browser_ui.c:16192` | `static double fbw_split_y(const freebug_window *fb)` |
| `fbw_toplevel_close` | function | `gui/browser_ui.c:16497` | `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)` |
| `fbw_toplevel_configure` | function | `gui/browser_ui.c:16488` | `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,                           ...` |
| `fbw_xdg_surface_configure` | function | `gui/browser_ui.c:16480` | `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)` |
| `fetch_follow_navigable` | function | `gui/browser_ui.c:1395` | `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,                         ...` |
| `fetch_job` | struct | `gui/browser_ui.c:1806` | `` |
| `fetch_job_free` | function | `gui/browser_ui.c:1838` | `static void fetch_job_free(fetch_job *j)` |
| `fetch_launch` | function | `gui/browser_ui.c:1930` | `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,                ...` |
| `fetch_prep` | struct | `gui/browser_ui.c:1725` | `` |
| `fetch_thread` | function | `gui/browser_ui.c:1882` | `static void *fetch_thread(void *arg)` |
| `fields` | function | `gui/browser_ui.c:279` | `* fields (so the 200+ render/event call sites stay unchanged);` |
| `fill` | function | `gui/browser_ui.c:13158` | `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in...` |
| `find_bg_image` | function | `gui/browser_ui.c:1099` | `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)` |
| `find_input_state` | function | `gui/browser_ui.c:1299` | `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)` |
| `first` | function | `gui/browser_ui.c:1624` | `* Navigation: clear the registry first (faces are per document). Untrusted:  * no-op (fetch NULL)...` |
| `flex_item_basis` | function | `gui/browser_ui.c:5686` | `static double flex_item_basis(cairo_t *cr, const browser_window *w,                              ...` |
| `flex_item_min_main` | function | `gui/browser_ui.c:5726` | `static double flex_item_min_main(cairo_t *cr, const browser_window *w,                           ...` |
| `float_founder_edges` | function | `gui/browser_ui.c:8308` | `static double float_founder_edges(const rd_doc *doc, int float_box, double ctx_w)` |
| `float_item_stop` | function | `gui/browser_ui.c:7628` | `static int float_item_stop(const rd_doc *doc, const rd_block *bk, int founder_key, int base_stop)` |
| `flow` | function | `gui/browser_ui.c:6717` | `* it collapse their vertical margins with each other exactly as in * the main flow (CSS 2.1 8.3.1), and none escapes...` |
| `flow_emit_frag` | function | `gui/browser_ui.c:4118` | `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,                  ...` |
| `flow_smallcaps_word` | function | `gui/browser_ui.c:4178` | `static double flow_smallcaps_word(cairo_t *cr, rc_layout *L, rc_state *s,                        ...` |
| `flow_text` | function | `gui/browser_ui.c:4241` | `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,                ...` |
| `flow_text_block` | function | `gui/browser_ui.c:4856` | `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,                  ...` |
| `flush_line` | function | `gui/browser_ui.c:3982` | `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)` |
| `foldback_session_cookies` | function | `gui/browser_ui.c:2267` | `static void foldback_session_cookies(const char *url, const char *jar)` |
| `font_size` | type_alias | `gui/browser_ui.c:3147` | `typedef struct rc_frag { double x, width, font_size;` |
| `frag_at_point` | function | `gui/browser_ui.c:14743` | `static dom_node_id frag_at_point(browser_window *w, double px, double py,                        ...` |
| `frag_styled` | function | `gui/browser_ui.c:3798` | `static int frag_styled(const rc_frag *f)` |
| `fragment` | function | `gui/browser_ui.c:12320` | `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using  * blk->block_id alo...` |
| `free_images` | function | `gui/browser_ui.c:1060` | `static void free_images(browser_window *w)` |
| `free_inputs` | function | `gui/browser_ui.c:1052` | `static void free_inputs(browser_window *w)` |
| `free_live_page` | function | `gui/browser_ui.c:2725` | `static void free_live_page(browser_window *w)` |
| `freebug_copy_console` | function | `gui/browser_ui.c:17255` | `static void freebug_copy_console(browser_window *w)` |
| `freebug_destroy` | function | `gui/browser_ui.c:16542` | `static void freebug_destroy(browser_window *w)` |
| `freebug_ensure_buffer` | function | `gui/browser_ui.c:16201` | `static int freebug_ensure_buffer(freebug_window *fb)` |
| `freebug_eval` | function | `gui/browser_ui.c:16598` | `static void freebug_eval(browser_window *w)` |
| `freebug_handle_key` | function | `gui/browser_ui.c:16638` | `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,                              ...` |
| `freebug_hide` | function | `gui/browser_ui.c:16464` | `static void freebug_hide(browser_window *w)` |
| `freebug_is_open` | function | `gui/browser_ui.c:16553` | `static int freebug_is_open(const browser_window *w)` |
| `freebug_owns_surface` | function | `gui/browser_ui.c:16549` | `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)` |
| `freebug_paint` | function | `gui/browser_ui.c:16252` | `static void freebug_paint(freebug_window *fb)` |
| `freebug_pointer_axis` | function | `gui/browser_ui.c:16714` | `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)` |
| `freebug_pointer_button` | function | `gui/browser_ui.c:16673` | `static void freebug_pointer_button(browser_window *w, uint32_t serial,                           ...` |
| `freebug_pointer_motion` | function | `gui/browser_ui.c:16692` | `static void freebug_pointer_motion(browser_window *w)` |
| `freebug_redraw` | function | `gui/browser_ui.c:16460` | `static void freebug_redraw(browser_window *w)` |
| `freebug_redraw_fb` | function | `gui/browser_ui.c:16451` | `static void freebug_redraw_fb(freebug_window *fb)` |
| `freebug_repl_worker` | function | `gui/browser_ui.c:16560` | `static tab *freebug_repl_worker(browser_window *w)` |
| `freebug_show` | function | `gui/browser_ui.c:16507` | `static void freebug_show(browser_window *w)` |
| `freebug_toggle` | function | `gui/browser_ui.c:16537` | `static void freebug_toggle(browser_window *w)` |
| `freebug_window` | type_alias | `gui/browser_ui.c:571` | `typedef struct freebug_window freebug_window;` |
| `freebug_window` | struct | `gui/browser_ui.c:16169` | `` |
| `freedom_write_dir` | function | `gui/browser_ui.c:744` | `static int freedom_write_dir(char *out, size_t cap)` |
| `geom_from_layout` | function | `gui/browser_ui.c:13575` | `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,                 ...` |
| `go_omnibox` | function | `gui/browser_ui.c:16805` | `static void go_omnibox(browser_window *w)` |
| `grad_stop` | function | `gui/browser_ui.c:11427` | `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)` |
| `gui_css_sink` | function | `gui/browser_ui.c:1556` | `static void gui_css_sink(void *vctx, const char *url,                          const char *body, ...` |
| `gui_subresource_fetch` | function | `gui/browser_ui.c:1472` | `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,                ...` |
| `gutter` | function | `gui/browser_ui.c:590` | `* gutter (content_margin) is intentionally left unzoomed, like a browser's text  * zoom. The PDF ...` |
| `h` | type_alias | `gui/browser_ui.c:3236` | `typedef struct rc_box { double x, top, w, h;` |
| `handle_key_press` | function | `gui/browser_ui.c:17570` | `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,              ...` |
| `have` | function | `gui/browser_ui.c:9332` | `* as they always have (spec/float.md §6b.3). The line still open beside * the previous float is committed first, at...` |
| `hb_is_allowlisted` | function | `gui/browser_ui.c:1688` | `&& hb_is_allowlisted(w->hosts, ihost);` |
| `history_step` | function | `gui/browser_ui.c:14888` | `static void history_step(browser_window *w, int steps)` |
| `host_from_url` | function | `gui/browser_ui.c:993` | `static int host_from_url(const char *url, char *out, size_t outsz)` |
| `hot_actionable` | function | `gui/browser_ui.c:3091` | `static int hot_actionable(const browser_window *w, ui_hot hot)` |
| `html_center_offset` | function | `gui/browser_ui.c:2954` | `static double html_center_offset(const browser_window *w)` |
| `ibx_advance` | function | `gui/browser_ui.c:4233` | `static void ibx_advance(const rc_layout *L, rc_state *s, double adv)` |
| `image_display_size` | function | `gui/browser_ui.c:1185` | `static int image_display_size(const browser_window *w, const rd_block *blk,                      ...` |
| `in` | function | `gui/browser_ui.c:14480` | `* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);` |
| `init_net_config` | function | `gui/browser_ui.c:968` | `static void init_net_config(browser_window *w)` |
| `inlines` | function | `gui/browser_ui.c:4601` | `* next run may also be a replaced element without its own break: consecutive  * atomic inlines (`...` |
| `input_box_width` | function | `gui/browser_ui.c:9980` | `static double input_box_width(double content_w)` |
| `input_inline_eligible` | function | `gui/browser_ui.c:4520` | `static int input_inline_eligible(const rd_block *b)` |
| `input_inline_size` | function | `gui/browser_ui.c:4534` | `static int input_inline_size(cairo_t *cr, const ui_theme *th, const rd_block *b,                 ...` |
| `input_is_editable` | function | `gui/browser_ui.c:1046` | `static int input_is_editable(int input_type)` |
| `input_is_interactive` | function | `gui/browser_ui.c:1040` | `static int input_is_interactive(int input_type)` |
| `insert_pasted_text` | function | `gui/browser_ui.c:17313` | `static void insert_pasted_text(browser_window *w, const char *text, size_t len)` |
| `is_http_url` | function | `gui/browser_ui.c:982` | `static int is_http_url(const char *s)` |
| `is_https_url` | function | `gui/browser_ui.c:978` | `static int is_https_url(const char *s)` |
| `it` | function | `gui/browser_ui.c:8983` | `* already sized it (see col_founder_set), so it is not a cap again. */ int fills_column = (si.col_founder_set &&...` |
| `item_at_level` | function | `gui/browser_ui.c:5791` | `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)` |
| `item_declared_basis` | function | `gui/browser_ui.c:5598` | `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,                       ...` |
| `item_inner_inset` | function | `gui/browser_ui.c:5523` | `static double item_inner_inset(const rd_doc *doc, size_t b0, size_t b1, int root)` |
| `item_root_box` | function | `gui/browser_ui.c:5096` | `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)` |
| `item_root_box_pass` | function | `gui/browser_ui.c:5022` | `static int item_root_box_pass(const rd_doc *doc, size_t b0, size_t b1, int cbox,                 ...` |
| `item_sides` | struct | `gui/browser_ui.c:5191` | `` |
| `item_sides_at_level` | function | `gui/browser_ui.c:5242` | `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,                   ...` |
| `item_vmargins` | function | `gui/browser_ui.c:5956` | `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,           ...` |
| `items` | function | `gui/browser_ui.c:6830` | `* items (Flexbox 4.2);` |
| `itself` | function | `gui/browser_ui.c:5104` | `* STRETCH itself (box_tree fills the line with it). */ static int css_align_to_bt(int align_kw)` |
| `key` | type_alias | `gui/browser_ui.c:8057` | `typedef struct rc_defer_col { int key;` |
| `key` | function | `gui/browser_ui.c:9318` | `* founders splits by key (stories, rail, footer nav each take * their column);` |
| `key_is_repeatable` | function | `gui/browser_ui.c:17900` | `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)` |
| `key_repeat_arm` | function | `gui/browser_ui.c:17916` | `static void key_repeat_arm(browser_window *w, uint32_t key)` |
| `key_repeat_fire` | function | `gui/browser_ui.c:17940` | `static void key_repeat_fire(browser_window *w)` |
| `key_repeat_stop` | function | `gui/browser_ui.c:17929` | `static void key_repeat_stop(browser_window *w)` |
| `key_sym_to_js_key` | function | `gui/browser_ui.c:17461` | `static const char *key_sym_to_js_key(xkb_keysym_t sym)` |
| `key_sym_to_keycode` | function | `gui/browser_ui.c:17487` | `static int key_sym_to_keycode(xkb_keysym_t sym)` |
| `keyboard_enter` | function | `gui/browser_ui.c:17446` | `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,                         ...` |
| `keyboard_key` | function | `gui/browser_ui.c:17954` | `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,                   ...` |
| `keyboard_keymap` | function | `gui/browser_ui.c:17425` | `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,                             uint...` |
| `keyboard_leave` | function | `gui/browser_ui.c:17453` | `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)` |
| `keyboard_modifiers` | function | `gui/browser_ui.c:17994` | `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,                  ...` |
| `keyboard_repeat_info` | function | `gui/browser_ui.c:18003` | `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)` |
| `kind` | type_alias | `gui/browser_ui.c:3212` | `typedef struct rc_row { rc_rowkind kind;` |
| `layer` | function | `gui/browser_ui.c:11648` | `* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the...` |
| `layout` | function | `gui/browser_ui.c:5672` | `* hypothetical size in the real layout (Flexbox 9.2.3). */ if (ibd != NULL && ibd->box_min_w > 0) base =...` |
| `layout_container` | function | `gui/browser_ui.c:6017` | `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,                 ...` |
| `layout_doc` | function | `gui/browser_ui.c:9088` | `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,                   ...` |
| `layout_float_band` | function | `gui/browser_ui.c:8601` | `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,                ...` |
| `limits` | function | `gui/browser_ui.c:13059` | `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box  * grouped this w...` |
| `line` | function | `gui/browser_ui.c:4311` | `* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the...` |
| `line_limit` | function | `gui/browser_ui.c:3625` | `static double line_limit(const rc_state *s, double content_w)` |
| `lines_at` | function | `gui/browser_ui.c:5484` | `static size_t lines_at(cairo_t *cr, const browser_window *w, const ui_theme *th,                 ...` |
| `link_at_point` | function | `gui/browser_ui.c:14530` | `static const char *link_at_point(browser_window *w, double px, double py)` |
| `load_bg_images` | function | `gui/browser_ui.c:2135` | `static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)` |
| `load_current` | function | `gui/browser_ui.c:16792` | `static void load_current(browser_window *w)` |
| `load_favorites` | function | `gui/browser_ui.c:837` | `static void load_favorites(browser_window *w)` |
| `load_images` | function | `gui/browser_ui.c:2051` | `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)` |
| `loop` | function | `gui/browser_ui.c:17304` | `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately...` |
| `made` | function | `gui/browser_ui.c:12870` | `* its zero channels made (255,255,255,alpha 0) -- an invalid * premultiplied value Cairo composites as ADDITIVE...` |
| `main` | function | `gui/browser_ui.c:516` | `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never...` |
| `margin` | function | `gui/browser_ui.c:9735` | `* own left margin (the margin box starts at the anchor point), a right- * anchored one ends at it. Same for the...` |
| `measure_item_content_w` | function | `gui/browser_ui.c:5550` | `static double measure_item_content_w(cairo_t *cr, const browser_window *w,                       ...` |
| `measure_item_w_at` | function | `gui/browser_ui.c:5434` | `static double measure_item_w_at(cairo_t *cr, const browser_window *w,                            ...` |
| `memory` | function | `gui/browser_ui.c:14971` | `* memory (the href pointer, not its contents, was all the old code preserved). */ static void dis...` |
| `menu_item_checked` | function | `gui/browser_ui.c:15320` | `static int menu_item_checked(const browser_window *w, size_t i)` |
| `menu_item_toggle` | function | `gui/browser_ui.c:15342` | `static void menu_item_toggle(browser_window *w, size_t i)` |
| `menu_panel_rect` | function | `gui/browser_ui.c:3102` | `static void menu_panel_rect(const browser_window *w, double *x, double *y,                       ...` |
| `mime_is_text` | function | `gui/browser_ui.c:17141` | `static int mime_is_text(const char *mime)` |
| `mr` | type_alias | `gui/browser_ui.c:5191` | `typedef struct item_sides { double ml, mr;` |
| `multicol_fragment` | function | `gui/browser_ui.c:6995` | `static double multicol_fragment(rc_layout *L, const rc_open_box *ob, double content_bottom);` |
| `nested_cont_basis` | function | `gui/browser_ui.c:5612` | `static double nested_cont_basis(cairo_t *cr, const browser_window *w,                            ...` |
| `nested_stop` | function | `gui/browser_ui.c:7647` | `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)` |
| `newtab_x` | function | `gui/browser_ui.c:2862` | `static double newtab_x(const browser_window *w)` |
| `node_at_point` | function | `gui/browser_ui.c:14716` | `static dom_node_id node_at_point(browser_window *w, double px, double py)` |
| `now_ms` | function | `gui/browser_ui.c:162` | `static uint64_t now_ms(void)` |
| `offset` | function | `gui/browser_ui.c:172` | `* offset (labels and the flag live in one place, no magic indices);` |
| `omni_refresh` | function | `gui/browser_ui.c:874` | `static void omni_refresh(browser_window *w)` |
| `only` | function | `gui/browser_ui.c:1551` | `* Trusted pages only (untrusted CSS is still applied by the worker, but its * fonts never reach the parent...` |
| `oof_static_xy` | function | `gui/browser_ui.c:7899` | `static void oof_static_xy(const rc_state *s, const ui_theme *th, double content_w,               ...` |
| `open_line` | function | `gui/browser_ui.c:4064` | `static void open_line(rc_layout *L, rc_state *s)` |
| `open_line_height` | function | `gui/browser_ui.c:4049` | `static double open_line_height(const rc_state *s, const ui_theme *th)` |
| `origin` | function | `gui/browser_ui.c:14402` | `* top_url is the page origin (https or file://);` |
| `ov_box_bounds` | function | `gui/browser_ui.c:12276` | `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)` |
| `ov_box_clips` | function | `gui/browser_ui.c:12248` | `static int ov_box_clips(const pv_box_def *d)` |
| `ov_collect_chain` | function | `gui/browser_ui.c:12255` | `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)` |
| `ov_content_rect` | function | `gui/browser_ui.c:12300` | `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,                             do...` |
| `overflow` | function | `gui/browser_ui.c:13218` | `* adding two of them in int was signed overflow (UB, found by UBSan). */ double ox = left + bx->x +...` |
| `own` | function | `gui/browser_ui.c:6749` | `* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and...` |
| `page_js_host_allowlisted` | function | `gui/browser_ui.c:2198` | `static int page_js_host_allowlisted(const browser_window *w)` |
| `page_side` | function | `gui/browser_ui.c:2924` | `static double page_side(const browser_window *w, int side)` |
| `page_trusted` | function | `gui/browser_ui.c:1470` | `static int page_trusted(const browser_window *w);` |
| `paint` | function | `gui/browser_ui.c:15764` | `static void paint(browser_window *w)` |
| `paint_bg_layer` | function | `gui/browser_ui.c:11508` | `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,                ...` |
| `paint_box_and_direct_rows` | function | `gui/browser_ui.c:13169` | `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,        ...` |
| `paint_box_decoration` | function | `gui/browser_ui.c:11552` | `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,            ...` |
| `paint_box_decoration_grouped` | function | `gui/browser_ui.c:13128` | `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,                         ...` |
| `paint_box_shadow_layer` | function | `gui/browser_ui.c:11309` | `static void paint_box_shadow_layer(cairo_t *cr, double x, double y, double w, double h,          ...` |
| `paint_content_row` | function | `gui/browser_ui.c:12032` | `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,                ...` |
| `paint_content_row_ex` | function | `gui/browser_ui.c:12039` | `static void paint_content_row_ex(cairo_t *cr, browser_window *w, const rc_layout *L,             ...` |
| `paint_deco_line` | function | `gui/browser_ui.c:11902` | `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,                        ...` |
| `paint_inline_replaced` | function | `gui/browser_ui.c:11987` | `static void paint_inline_replaced(cairo_t *cr, browser_window *w,                                ...` |
| `paint_nested_children` | function | `gui/browser_ui.c:13537` | `static void paint_nested_children(cairo_t *cr, browser_window *w,                                ...` |
| `paint_oof_sub` | function | `gui/browser_ui.c:13278` | `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,                 ...` |
| `paint_png_deferred` | function | `gui/browser_ui.c:14181` | `static void paint_png_deferred(void *ctx, int root)` |
| `paint_png_inflow` | function | `gui/browser_ui.c:14152` | `static void paint_png_inflow(const png_flow_ctx *c, int only_root)` |
| `paint_positioned_layer` | function | `gui/browser_ui.c:13671` | `static void paint_positioned_layer(cairo_t *cr, browser_window *w, const ui_theme *th,           ...` |
| `paint_positioned_one` | function | `gui/browser_ui.c:13316` | `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,             ...` |
| `paint_screen_deferred` | function | `gui/browser_ui.c:13851` | `static void paint_screen_deferred(void *ctx, int root)` |
| `paint_screen_inflow` | function | `gui/browser_ui.c:13736` | `static void paint_screen_inflow(const screen_flow_ctx *c, int only_root)` |
| `paint_structured` | function | `gui/browser_ui.c:13855` | `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,                 ...` |
| `paint_svg_at` | function | `gui/browser_ui.c:11958` | `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,                          doub...` |
| `paint_video_row` | function | `gui/browser_ui.c:11118` | `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,                 ...` |
| `path` | function | `gui/browser_ui.c:6406` | `*          * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when         ...` |
| `pl` | type_alias | `gui/browser_ui.c:1116` | `typedef struct repl_edges { double mt, mr, mb, ml, bt, br, bb, bl, pt, pr, pb, pl;` |
| `place_inline_replaced` | function | `gui/browser_ui.c:4638` | `static int place_inline_replaced(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,     ...` |
| `placeholder_display_size` | function | `gui/browser_ui.c:1251` | `static int placeholder_display_size(const rd_block *blk, double box_w,                           ...` |
| `png_flow_ctx` | struct | `gui/browser_ui.c:14140` | `` |
| `position_doc` | function | `gui/browser_ui.c:9788` | `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,                 ...` |
| `prepare_fetch` | function | `gui/browser_ui.c:1734` | `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,                     ...` |
| `presentation` | function | `gui/browser_ui.c:15340` | `* affect presentation (a repaint, which re-runs layout, suffices);` |
| `proceed` | function | `gui/browser_ui.c:1731` | `* may proceed (cfg and pr->allowlisted are then set);` |
| `produced` | function | `gui/browser_ui.c:4212` | `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target...` |
| `profile_sync` | function | `gui/browser_ui.c:905` | `static void profile_sync(browser_window *w)` |
| `proxy` | function | `gui/browser_ui.c:965` | `* and enable each proxy ("1" => the default port);` |
| `proxy_addr_from_env` | function | `gui/browser_ui.c:954` | `static int proxy_addr_from_env(const char *envname, const char *deflt,                           ...` |
| `ptr_axis` | function | `gui/browser_ui.c:17101` | `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,                      uint32...` |
| `ptr_button` | function | `gui/browser_ui.c:16850` | `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,               ...` |
| `ptr_enter` | function | `gui/browser_ui.c:16732` | `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,                       struct wl_...` |
| `ptr_frame` | function | `gui/browser_ui.c:17125` | `static void ptr_frame(void *d, struct wl_pointer *p)` |
| `ptr_leave` | function | `gui/browser_ui.c:16750` | `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)` |
| `ptr_motion` | function | `gui/browser_ui.c:16767` | `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)` |
| `publish_geometry` | function | `gui/browser_ui.c:13606` | `static void publish_geometry(browser_window *w, const rc_layout *L, double left,                 ...` |
| `rc_add_box` | function | `gui/browser_ui.c:3653` | `static rc_box *rc_add_box(rc_layout *L)` |
| `rc_add_frag` | function | `gui/browser_ui.c:3665` | `static rc_frag *rc_add_frag(rc_layout *L)` |
| `rc_add_row` | function | `gui/browser_ui.c:3680` | `static rc_row *rc_add_row(rc_layout *L)` |

Next: [SYMBOLS_p2.md](SYMBOLS_p2.md)
