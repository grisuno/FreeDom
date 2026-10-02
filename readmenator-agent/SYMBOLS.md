# Symbols

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `list_unique_crashes` | function | `app.py:39` | `def list_unique_crashes()` |
| `read_fuzz_stats` | function | `app.py:30` | `def read_fuzz_stats()` |
| `run_freedom_headless` | function | `app.py:47` | `def run_freedom_headless(payload_path)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_css.c:80` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `fuzz_root_match` | function | `fuzz/fuzz_css.c:66` | `static int fuzz_root_match(void *ctx, const css_sel *sel)` |
| `worker` | function | `fuzz/fuzz_data_url.c:6` | `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, never
 * interpreted...` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_dom.c:48` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `ensure_built` | function | `fuzz/fuzz_dom.c:41` | `static void ensure_built(void)` |
| `pass` | function | `fuzz/fuzz_dom_debug.c:8` | `* the measure pass (cap 0) must agree with the would-write return value.
 *
 * Build & run: make ...` |
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
| `js_sandbox` | function | `fuzz/fuzz_js_sandbox.c:2` | `* libFuzzer harness for js_sandbox (Hito 3). * * Goal: arbitrary bytes treated as untrusted script through the full * ev` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_pdf_export.c:30` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_prefetch.c:10` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_prefs.c:21` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_svg_render.c:24` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `FZ_CAP` | macro | `fuzz/fuzz_text_shape.c:23` | `#define FZ_CAP` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_text_shape.c:25` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_url.c:59` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `check_split` | function | `fuzz/fuzz_url.c:31` | `static void check_split(const char *url)` |
| `ALIVE` | function | `gui/browser_ui.c:2263` | `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or a ta` |
| `BUI_CONIC_SLICES` | macro | `gui/browser_ui.c:9506` | `#define BUI_CONIC_SLICES` |
| `FBW_COPY_BTN_H` | macro | `gui/browser_ui.c:13851` | `#define FBW_COPY_BTN_H` |
| `FBW_COPY_BTN_W` | macro | `gui/browser_ui.c:13850` | `#define FBW_COPY_BTN_W` |
| `FBW_GUTTER` | macro | `gui/browser_ui.c:13847` | `#define FBW_GUTTER` |
| `FBW_H` | macro | `gui/browser_ui.c:13843` | `#define FBW_H` |
| `FBW_HEADER` | macro | `gui/browser_ui.c:13844` | `#define FBW_HEADER` |
| `FBW_LINE` | macro | `gui/browser_ui.c:13846` | `#define FBW_LINE` |
| `FBW_MAX_SPLIT` | macro | `gui/browser_ui.c:13849` | `#define FBW_MAX_SPLIT` |
| `FBW_MIN_SPLIT` | macro | `gui/browser_ui.c:13848` | `#define FBW_MIN_SPLIT` |
| `FBW_PAD` | macro | `gui/browser_ui.c:13845` | `#define FBW_PAD` |
| `FBW_W` | macro | `gui/browser_ui.c:13842` | `#define FBW_W` |
| `FLEX_MEASURE_W` | macro | `gui/browser_ui.c:4718` | `#define FLEX_MEASURE_W` |
| `FLEX_MIN_MEASURE_W` | macro | `gui/browser_ui.c:4723` | `#define FLEX_MIN_MEASURE_W` |
| `Firefox` | function | `gui/browser_ui.c:12434` | `* on its face does in Firefox (spec/page_view.md, tanda 40). */
static const rd_block *submit_pro...` |
| `GET` | function | `gui/browser_ui.c:1346` | `* a GET (Zero Trust). cfg->policy is restored before returning. */
static sf_status fetch_post_na...` |
| `GET` | function | `gui/browser_ui.c:12764` | `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...` |
| `H2R` | macro | `gui/browser_ui.c:10813` | `#define H2R(p,q,t)` |
| `HIST_STEP_DEPTH_MAX` | macro | `gui/browser_ui.c:1969` | `#define HIST_STEP_DEPTH_MAX` |
| `HarfBuzz` | function | `gui/browser_ui.c:3408` | `* descriptor via HarfBuzz (text_shape);` |
| `JS_NAV_MAX` | macro | `gui/browser_ui.c:1967` | `#define JS_NAV_MAX` |
| `JS_TICKS_PER_LOAD` | macro | `gui/browser_ui.c:2087` | `#define JS_TICKS_PER_LOAD` |
| `OMNI_MAX_SUGG` | macro | `gui/browser_ui.c:121` | `#define OMNI_MAX_SUGG` |
| `OV_MAX_DEPTH` | macro | `gui/browser_ui.c:10210` | `#define OV_MAX_DEPTH` |
| `PDF_MARGIN` | macro | `gui/browser_ui.c:11689` | `#define PDF_MARGIN` |
| `PDF_PAGE_H` | macro | `gui/browser_ui.c:11688` | `#define PDF_PAGE_H` |
| `PDF_PAGE_W` | macro | `gui/browser_ui.c:11687` | `#define PDF_PAGE_W` |
| `PNG_MARGIN` | macro | `gui/browser_ui.c:11864` | `#define PNG_MARGIN` |
| `PNG_MAX_H` | macro | `gui/browser_ui.c:11865` | `#define PNG_MAX_H` |
| `PNG_PAGE_W` | macro | `gui/browser_ui.c:11851` | `#define PNG_PAGE_W` |
| `RC_BOX_STACK_MAX` | macro | `gui/browser_ui.c:3139` | `#define RC_BOX_STACK_MAX` |
| `RC_DEFER_BAND_RUNS` | macro | `gui/browser_ui.c:6685` | `#define RC_DEFER_BAND_RUNS` |
| `RC_DEFER_COLS` | macro | `gui/browser_ui.c:6602` | `#define RC_DEFER_COLS` |
| `RC_DEFER_RANGES` | macro | `gui/browser_ui.c:6603` | `#define RC_DEFER_RANGES` |
| `RC_FLOAT_FIT_MIN` | macro | `gui/browser_ui.c:3150` | `#define RC_FLOAT_FIT_MIN` |
| `RC_FLOAT_MAX` | macro | `gui/browser_ui.c:3143` | `#define RC_FLOAT_MAX` |
| `RC_MAX_OUT_OF_FLOW` | macro | `gui/browser_ui.c:6494` | `#define RC_MAX_OUT_OF_FLOW` |
| `TABLE` | function | `gui/browser_ui.c:5052` | `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all containers ha` |
| `UI_BTN_LEFT` | macro | `gui/browser_ui.c:91` | `#define UI_BTN_LEFT` |
| `UI_BTN_W` | macro | `gui/browser_ui.c:88` | `#define UI_BTN_W` |
| `UI_BUTTON_HPAD` | macro | `gui/browser_ui.c:132` | `#define UI_BUTTON_HPAD` |
| `UI_CHECK_SZ` | macro | `gui/browser_ui.c:114` | `#define UI_CHECK_SZ` |
| `UI_CURSOR_SIZE` | macro | `gui/browser_ui.c:119` | `#define UI_CURSOR_SIZE` |
| `UI_FORM_FIELDS_MAX` | macro | `gui/browser_ui.c:133` | `#define UI_FORM_FIELDS_MAX` |
| `UI_HAMBURGER_GAP` | macro | `gui/browser_ui.c:118` | `#define UI_HAMBURGER_GAP` |
| `UI_HAMBURGER_W` | macro | `gui/browser_ui.c:117` | `#define UI_HAMBURGER_W` |
| `UI_IMAGE_MAX_BODY` | macro | `gui/browser_ui.c:222` | `#define UI_IMAGE_MAX_BODY` |
| `UI_INPUT_MEASURE_W` | macro | `gui/browser_ui.c:130` | `#define UI_INPUT_MEASURE_W` |
| `UI_INPUT_PAD` | macro | `gui/browser_ui.c:127` | `#define UI_INPUT_PAD` |
| `UI_INPUT_WIDTH` | macro | `gui/browser_ui.c:131` | `#define UI_INPUT_WIDTH` |
| `UI_LIST_INDENT` | macro | `gui/browser_ui.c:95` | `#define UI_LIST_INDENT` |
| `UI_MARGIN` | macro | `gui/browser_ui.c:90` | `#define UI_MARGIN` |
| `UI_MAX_TABS` | macro | `gui/browser_ui.c:261` | `#define UI_MAX_TABS` |
| `UI_MENU_COUNT` | macro | `gui/browser_ui.c:204` | `#define UI_MENU_COUNT` |
| `UI_MENU_INPUT_H` | macro | `gui/browser_ui.c:116` | `#define UI_MENU_INPUT_H` |
| `UI_MENU_ITEM_H` | macro | `gui/browser_ui.c:112` | `#define UI_MENU_ITEM_H` |
| `UI_MENU_LABEL_H` | macro | `gui/browser_ui.c:115` | `#define UI_MENU_LABEL_H` |
| `UI_MENU_PAD` | macro | `gui/browser_ui.c:113` | `#define UI_MENU_PAD` |
| `UI_MENU_W` | macro | `gui/browser_ui.c:111` | `#define UI_MENU_W` |
| `UI_OMNI_ROW_H` | macro | `gui/browser_ui.c:122` | `#define UI_OMNI_ROW_H` |
| `UI_OVERLINE_OFFSET` | macro | `gui/browser_ui.c:141` | `#define UI_OVERLINE_OFFSET` |
| `UI_READER_COLUMN_W` | macro | `gui/browser_ui.c:569` | `#define UI_READER_COLUMN_W` |
| `UI_RELOAD_X` | macro | `gui/browser_ui.c:2824` | `#define UI_RELOAD_X` |
| `UI_RESIZE_MARGIN` | macro | `gui/browser_ui.c:106` | `#define UI_RESIZE_MARGIN` |
| `UI_SCROLLBAR_MIN` | macro | `gui/browser_ui.c:101` | `#define UI_SCROLLBAR_MIN` |
| `UI_SCROLLBAR_PAD` | macro | `gui/browser_ui.c:102` | `#define UI_SCROLLBAR_PAD` |
| `UI_SCROLLBAR_W` | macro | `gui/browser_ui.c:100` | `#define UI_SCROLLBAR_W` |
| `UI_SLICE_MAX` | macro | `gui/browser_ui.c:145` | `#define UI_SLICE_MAX` |
| `UI_STRIKE_OFFSET` | macro | `gui/browser_ui.c:140` | `#define UI_STRIKE_OFFSET` |
| `UI_TABBAR_H` | macro | `gui/browser_ui.c:83` | `#define UI_TABBAR_H` |
| `UI_TAB_CLOSE_W` | macro | `gui/browser_ui.c:87` | `#define UI_TAB_CLOSE_W` |
| `UI_TAB_MAX_W` | macro | `gui/browser_ui.c:85` | `#define UI_TAB_MAX_W` |
| `UI_TAB_MIN_W` | macro | `gui/browser_ui.c:84` | `#define UI_TAB_MIN_W` |
| `UI_TAB_NEW_W` | macro | `gui/browser_ui.c:86` | `#define UI_TAB_NEW_W` |
| `UI_TITLEBAR_H` | macro | `gui/browser_ui.c:82` | `#define UI_TITLEBAR_H` |
| `UI_TOAST_PAD` | macro | `gui/browser_ui.c:120` | `#define UI_TOAST_PAD` |
| `UI_TOOLBAR_H` | macro | `gui/browser_ui.c:81` | `#define UI_TOOLBAR_H` |
| `UI_TWO_PI` | macro | `gui/browser_ui.c:123` | `#define UI_TWO_PI` |
| `UI_UNDERLINE_OFFSET` | macro | `gui/browser_ui.c:138` | `#define UI_UNDERLINE_OFFSET` |
| `UI_UNDERLINE_THICK` | macro | `gui/browser_ui.c:139` | `#define UI_UNDERLINE_THICK` |
| `UI_WIN_BTN_W` | macro | `gui/browser_ui.c:89` | `#define UI_WIN_BTN_W` |
| `_GNU_SOURCE` | macro | `gui/browser_ui.c:12` | `#define _GNU_SOURCE` |
| `add` | function | `gui/browser_ui.c:3587` | `* about to add (top/h passed in). A box that survived a line wrap simply ends at the
 * wrap -- m...` |
| `add_current_host_to_list` | function | `gui/browser_ui.c:789` | `static void add_current_host_to_list(browser_window *w, int sel)` |
| `again` | function | `gui/browser_ui.c:8876` | `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one fail wi` |
| `allowlisted` | type_alias | `gui/browser_ui.c:1510` | `typedef struct fetch_prep { int allowlisted;` |
| `anchor` | function | `gui/browser_ui.c:7538` | `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is a n` |
| `applies` | function | `gui/browser_ui.c:15918` | `* persisted choice applies (prefs_parse already clamped it to a valid mode). */ const char *js_env = getenv("FREEDOM_JS"` |
| `apply_click_result` | function | `gui/browser_ui.c:12631` | `static int apply_click_result(browser_window *w, tab_page *page)` |
| `apply_history_ops` | function | `gui/browser_ui.c:12586` | `static void apply_history_ops(browser_window *w, const tab_page *page)` |
| `apply_zoom` | function | `gui/browser_ui.c:586` | `static void apply_zoom(browser_window *w)` |
| `approximation` | function | `gui/browser_ui.c:7800` | `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */
static void oof_s...` |
| `arrives` | function | `gui/browser_ui.c:2349` | `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...` |
| `audio_mark_dead` | function | `gui/browser_ui.c:8835` | `static void audio_mark_dead(browser_window *w)` |
| `audio_spawn` | function | `gui/browser_ui.c:8781` | `static void audio_spawn(browser_window *w, int rate, int channels)` |
| `audio_stop` | function | `gui/browser_ui.c:8867` | `static void audio_stop(browser_window *w)` |
| `audio_write` | function | `gui/browser_ui.c:8852` | `static void audio_write(browser_window *w, const uint8_t *data, size_t len)` |
| `axis` | function | `gui/browser_ui.c:5239` | `* differs: items stack on the vertical main axis (fx_column_place) and align on * the horizontal cross axis (fx_cross_of` |
| `band_common_box` | function | `gui/browser_ui.c:6514` | `static int band_common_box(const rd_doc *doc, size_t start, size_t end)` |
| `behind` | function | `gui/browser_ui.c:6046` | `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old code ` |
| `bg` | function | `gui/browser_ui.c:10079` | `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);` |
| `block_id` | type_alias | `gui/browser_ui.c:3094` | `typedef struct rc_open_box { int block_id;` |
| `block_in_table_caption` | function | `gui/browser_ui.c:6578` | `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)` |
| `block_is_oof` | function | `gui/browser_ui.c:5064` | `static int block_is_oof(const rd_doc *doc, const rd_block *bk)` |
| `block_leaves_flow` | function | `gui/browser_ui.c:4121` | `static int block_leaves_flow(const rd_doc *doc, const rd_block *bk);` |
| `block_margins` | function | `gui/browser_ui.c:3557` | `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...` |
| `block_style` | function | `gui/browser_ui.c:3530` | `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...` |
| `blocking` | function | `gui/browser_ui.c:9163` | `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);` |
| `bookmark_toggle_current` | function | `gui/browser_ui.c:959` | `static void bookmark_toggle_current(browser_window *w)` |
| `box` | function | `gui/browser_ui.c:11289` | `* content belongs to that box (painted by its own positioned entry). */
    if (sub == NULL)` |
| `box_edge_px` | function | `gui/browser_ui.c:4499` | `static double box_edge_px(int wpx)` |
| `box_forms_stacking_context` | function | `gui/browser_ui.c:10341` | `static int box_forms_stacking_context(const pv_box_def *def)` |
| `box_is_strict_descendant` | function | `gui/browser_ui.c:4598` | `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)` |
| `box_line_visible` | function | `gui/browser_ui.c:5850` | `static int box_line_visible(int style)` |
| `box_margin_bottom` | function | `gui/browser_ui.c:6027` | `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)` |
| `box_margin_top` | function | `gui/browser_ui.c:6020` | `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)` |
| `box_path` | function | `gui/browser_ui.c:9418` | `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)` |
| `box_path_has` | function | `gui/browser_ui.c:6339` | `static int box_path_has(const rd_doc *doc, int block_id, int want)` |
| `box_path_of` | function | `gui/browser_ui.c:6498` | `static int box_path_of(const rd_doc *doc, int block_id, int *out)` |
| `box_pointer_events_none` | function | `gui/browser_ui.c:12344` | `static int box_pointer_events_none(const rd_doc *doc, int block_id)` |
| `box_shrink_width` | function | `gui/browser_ui.c:6379` | `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...` |
| `box_transform_matrix` | function | `gui/browser_ui.c:10391` | `static void box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
             ...` |
| `browser_window` | struct | `gui/browser_ui.c:285` | `` |
| `bs` | type_alias | `gui/browser_ui.c:269` | `typedef struct tab_ctx { browser_state bs;` |
| `buffer_release` | function | `gui/browser_ui.c:597` | `static void buffer_release(void *data, struct wl_buffer *wl_buffer)` |
| `bui_blend_operator` | function | `gui/browser_ui.c:10509` | `static cairo_operator_t bui_blend_operator(int mix_blend)` |
| `bui_grad_color_at` | function | `gui/browser_ui.c:9479` | `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...` |
| `bui_paint_backdrop_blur` | function | `gui/browser_ui.c:10647` | `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...` |
| `bui_pop_group_composite` | function | `gui/browser_ui.c:10705` | `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms)` |
| `bui_skew_tan` | function | `gui/browser_ui.c:10384` | `static double bui_skew_tan(int deg)` |
| `build_file_origin` | function | `gui/browser_ui.c:678` | `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)` |
| `build_host_filter` | function | `gui/browser_ui.c:705` | `static hb_set *build_host_filter(void)` |
| `build_impersonate_optin` | function | `gui/browser_ui.c:755` | `static int build_impersonate_optin(void)` |
| `build_js_filter` | function | `gui/browser_ui.c:752` | `static hb_set *build_js_filter(void)` |
| `button_box_width` | function | `gui/browser_ui.c:8165` | `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9756` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9759` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9799` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9802` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9860` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9863` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9955` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9957` | `cairo_set_dash(cr, (double[])` |
| `caller` | function | `gui/browser_ui.c:12030` | `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...` |
| `chain` | function | `gui/browser_ui.c:7446` | `* chain (the box that left the normal flow at this pen position);` |
| `child_cont_at_level` | function | `gui/browser_ui.c:5012` | `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)` |
| `children` | function | `gui/browser_ui.c:6037` | `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...` |
| `clear_doc` | function | `gui/browser_ui.c:1222` | `static void clear_doc(browser_window *w)` |
| `clipboard_copy` | function | `gui/browser_ui.c:15061` | `static void clipboard_copy(browser_window *w)` |
| `close_all_boxes` | function | `gui/browser_ui.c:4984` | `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);` |
| `close_top_box` | function | `gui/browser_ui.c:5856` | `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)` |
| `col` | type_alias | `gui/browser_ui.c:6621` | `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];` |
| `collect_local_storage` | function | `gui/browser_ui.c:2042` | `static void collect_local_storage(browser_window *w, const tab_page *page)` |
| `column` | function | `gui/browser_ui.c:6245` | `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...` |
| `columns` | function | `gui/browser_ui.c:6353` | `* each card made 1080px columns (huggingface, github). */
static int deepest_open_on_path(const r...` |
| `compositing` | function | `gui/browser_ui.c:11126` | `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context: opac` |
| `compute_page_js` | function | `gui/browser_ui.c:1989` | `static int compute_page_js(const browser_window *w)` |
| `container_box_of` | function | `gui/browser_ui.c:4649` | `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)` |
| `content_font` | function | `gui/browser_ui.c:3415` | `static void content_font(cairo_t *cr, double size, int bold, int italic, int family)` |
| `content_geometry` | function | `gui/browser_ui.c:2683` | `static void content_geometry(const browser_window *w, double *top, double *height)` |
| `content_width` | function | `gui/browser_ui.c:2710` | `static double content_width(const browser_window *w)` |
| `context` | function | `gui/browser_ui.c:6567` | `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document ord` |
| `convention` | function | `gui/browser_ui.c:9822` | `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE \|\| style == ` |
| `cost` | function | `gui/browser_ui.c:16149` | `* measured cost (floor 33 ms = the existing ~30 fps ceiling):
             * cheap pages paint at...` |
| `count` | function | `gui/browser_ui.c:7781` | `* the box count (a hostile parent cycle terminates). */
static int oof_depth(const rd_doc *doc, s...` |
| `css_align_to_bt` | function | `gui/browser_ui.c:4489` | `static int css_align_to_bt(int align_kw)` |
| `css_replaced_box` | function | `gui/browser_ui.c:4209` | `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...` |
| `cursor_at_point` | function | `gui/browser_ui.c:12360` | `static int cursor_at_point(browser_window *w, double px, double py)` |
| `data_device_data_offer` | function | `gui/browser_ui.c:14856` | `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...` |
| `data_device_drop` | function | `gui/browser_ui.c:14897` | `static void data_device_drop(void *d, struct wl_data_device *dev)` |
| `data_device_enter` | function | `gui/browser_ui.c:14887` | `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...` |
| `data_device_leave` | function | `gui/browser_ui.c:14892` | `static void data_device_leave(void *d, struct wl_data_device *dev)` |
| `data_device_motion` | function | `gui/browser_ui.c:14893` | `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...` |
| `data_device_selection` | function | `gui/browser_ui.c:14868` | `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...` |
| `data_offer_action` | function | `gui/browser_ui.c:14846` | `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)` |
| `data_offer_source_actions` | function | `gui/browser_ui.c:14843` | `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)` |
| `data_source_cancelled` | function | `gui/browser_ui.c:14908` | `static void data_source_cancelled(void *data, struct wl_data_source *src)` |
| `data_source_send` | function | `gui/browser_ui.c:14914` | `static void data_source_send(void *data, struct wl_data_source *src,
                            ...` |
| `data_source_target` | function | `gui/browser_ui.c:14927` | `static void data_source_target(void *d, struct wl_data_source *s, const char *m)` |
| `deco_configure` | function | `gui/browser_ui.c:13764` | `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)` |
| `deepest_open_on_path` | function | `gui/browser_ui.c:4990` | `static int deepest_open_on_path(const rc_state *outer, const rd_doc *doc, int block_id);` |
| `def_declared_width` | function | `gui/browser_ui.c:4862` | `static double def_declared_width(const pv_box_def *d, double avail_w)` |
| `def_width_cap` | function | `gui/browser_ui.c:4856` | `static double def_width_cap(const pv_box_def *d, double avail_w)` |
| `defer_append` | function | `gui/browser_ui.c:6765` | `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...` |
| `defer_flush` | function | `gui/browser_ui.c:6799` | `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...` |
| `defer_key_block` | function | `gui/browser_ui.c:6642` | `static int defer_key_block(const rd_block *bk)` |
| `delay` | function | `gui/browser_ui.c:359` | `* timer delay (tab_page.next_timer_ms);` |
| `deliver_fetch_result` | function | `gui/browser_ui.c:12878` | `static void deliver_fetch_result(browser_window *w, fetch_job *j)` |
| `descriptors` | function | `gui/browser_ui.c:8795` | `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection — the m` |
| `destroy_buffer` | function | `gui/browser_ui.c:603` | `static void destroy_buffer(browser_window *w)` |
| `dies` | function | `gui/browser_ui.c:8772` | `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...` |
| `dispatch_js_event` | function | `gui/browser_ui.c:15196` | `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...` |
| `do_load` | function | `gui/browser_ui.c:1957` | `static void do_load(browser_window *w, const char *url);` |
| `down` | function | `gui/browser_ui.c:14410` | `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void dispatch_` |
| `drain_fetch_results` | function | `gui/browser_ui.c:12932` | `static void drain_fetch_results(browser_window *w)` |
| `draw_clock` | function | `gui/browser_ui.c:13151` | `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...` |
| `draw_hamburger` | function | `gui/browser_ui.c:13163` | `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)` |
| `draw_hover_url` | function | `gui/browser_ui.c:13312` | `static double draw_hover_url(cairo_t *cr, browser_window *w)` |
| `draw_menu` | function | `gui/browser_ui.c:13201` | `static void draw_menu(cairo_t *cr, browser_window *w)` |
| `draw_omnibox` | function | `gui/browser_ui.c:13429` | `static void draw_omnibox(cairo_t *cr, browser_window *w)` |
| `draw_reload` | function | `gui/browser_ui.c:13179` | `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)` |
| `draw_scrollbar` | function | `gui/browser_ui.c:2779` | `static void draw_scrollbar(cairo_t *cr, const browser_window *w)` |
| `draw_slice` | function | `gui/browser_ui.c:3477` | `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)` |
| `draw_tabstrip` | function | `gui/browser_ui.c:13374` | `static void draw_tabstrip(cairo_t *cr, browser_window *w)` |
| `draw_text` | function | `gui/browser_ui.c:2894` | `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)` |
| `draw_toast` | function | `gui/browser_ui.c:13344` | `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)` |
| `drop_repl_worker` | function | `gui/browser_ui.c:2078` | `static void drop_repl_worker(browser_window *w)` |
| `element` | function | `gui/browser_ui.c:13806` | `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...` |
| `emit_replaced_row` | function | `gui/browser_ui.c:4218` | `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...` |
| `ensure_buffer` | function | `gui/browser_ui.c:609` | `static int ensure_buffer(browser_window *w)` |
| `ensure_download_dir` | function | `gui/browser_ui.c:12798` | `static int ensure_download_dir(char *out, size_t outsz)` |
| `export_pdf` | function | `gui/browser_ui.c:11809` | `static void export_pdf(browser_window *w)` |
| `export_png` | function | `gui/browser_ui.c:11996` | `static void export_png(browser_window *w)` |
| `family` | type_alias | `gui/browser_ui.c:3737` | `typedef struct rc_ext { int family;` |
| `family_face` | function | `gui/browser_ui.c:3397` | `static const char *family_face(int family)` |
| `fbw_console_lines` | function | `gui/browser_ui.c:13923` | `static size_t fbw_console_lines(const fb_buffer *log)` |
| `fbw_level_rgb` | function | `gui/browser_ui.c:13912` | `static void fbw_level_rgb(int level, double *r, double *g, double *b)` |
| `fbw_split_y` | function | `gui/browser_ui.c:13876` | `static double fbw_split_y(const freebug_window *fb)` |
| `fbw_toplevel_close` | function | `gui/browser_ui.c:14181` | `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)` |
| `fbw_toplevel_configure` | function | `gui/browser_ui.c:14172` | `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...` |
| `fbw_xdg_surface_configure` | function | `gui/browser_ui.c:14164` | `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)` |
| `fetch_follow_navigable` | function | `gui/browser_ui.c:1310` | `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...` |
| `fetch_job` | struct | `gui/browser_ui.c:1591` | `` |
| `fetch_job_free` | function | `gui/browser_ui.c:1623` | `static void fetch_job_free(fetch_job *j)` |
| `fetch_launch` | function | `gui/browser_ui.c:1715` | `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...` |
| `fetch_prep` | struct | `gui/browser_ui.c:1510` | `` |
| `fetch_thread` | function | `gui/browser_ui.c:1667` | `static void *fetch_thread(void *arg)` |
| `fields` | function | `gui/browser_ui.c:265` | `* fields (so the 200+ render/event call sites stay unchanged);` |
| `fill` | function | `gui/browser_ui.c:11033` | `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in the ` |
| `find_bg_image` | function | `gui/browser_ui.c:1128` | `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)` |
| `find_input_state` | function | `gui/browser_ui.c:1214` | `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)` |
| `first` | function | `gui/browser_ui.c:7513` | `* flush first (no-op when nothing is deferred). */ /* The open line beside the float is committed where it is BEFORE the` |
| `flex_item_basis` | function | `gui/browser_ui.c:4923` | `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...` |
| `flex_item_min_main` | function | `gui/browser_ui.c:4962` | `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...` |
| `flow` | function | `gui/browser_ui.c:16127` | `* flow (counting them starved aplay). A video frame read while * overdue overwrites the held slot (standard player frame` |
| `flow_emit_frag` | function | `gui/browser_ui.c:3766` | `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...` |
| `flow_text` | function | `gui/browser_ui.c:3833` | `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...` |
| `flow_text_block` | function | `gui/browser_ui.c:4321` | `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...` |
| `flush_line` | function | `gui/browser_ui.c:3647` | `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)` |
| `foldback_session_cookies` | function | `gui/browser_ui.c:2052` | `static void foldback_session_cookies(const char *url, const char *jar)` |
| `font_size` | type_alias | `gui/browser_ui.c:2913` | `typedef struct rc_frag { double x, width, font_size;` |
| `frag_at_point` | function | `gui/browser_ui.c:12453` | `static dom_node_id frag_at_point(browser_window *w, double px, double py,
                       ...` |
| `frag_styled` | function | `gui/browser_ui.c:3490` | `static int frag_styled(const rc_frag *f)` |
| `fragment` | function | `gui/browser_ui.c:10286` | `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...` |
| `free_images` | function | `gui/browser_ui.c:1089` | `static void free_images(browser_window *w)` |
| `free_inputs` | function | `gui/browser_ui.c:1081` | `static void free_inputs(browser_window *w)` |
| `free_live_page` | function | `gui/browser_ui.c:2512` | `static void free_live_page(browser_window *w)` |
| `freebug_copy_console` | function | `gui/browser_ui.c:14939` | `static void freebug_copy_console(browser_window *w)` |
| `freebug_destroy` | function | `gui/browser_ui.c:14226` | `static void freebug_destroy(browser_window *w)` |
| `freebug_ensure_buffer` | function | `gui/browser_ui.c:13885` | `static int freebug_ensure_buffer(freebug_window *fb)` |
| `freebug_eval` | function | `gui/browser_ui.c:14282` | `static void freebug_eval(browser_window *w)` |
| `freebug_handle_key` | function | `gui/browser_ui.c:14322` | `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...` |
| `freebug_hide` | function | `gui/browser_ui.c:14148` | `static void freebug_hide(browser_window *w)` |
| `freebug_is_open` | function | `gui/browser_ui.c:14237` | `static int freebug_is_open(const browser_window *w)` |
| `freebug_owns_surface` | function | `gui/browser_ui.c:14233` | `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)` |
| `freebug_paint` | function | `gui/browser_ui.c:13936` | `static void freebug_paint(freebug_window *fb)` |
| `freebug_pointer_axis` | function | `gui/browser_ui.c:14398` | `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)` |
| `freebug_pointer_button` | function | `gui/browser_ui.c:14357` | `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...` |
| `freebug_pointer_motion` | function | `gui/browser_ui.c:14376` | `static void freebug_pointer_motion(browser_window *w)` |
| `freebug_redraw` | function | `gui/browser_ui.c:14144` | `static void freebug_redraw(browser_window *w)` |
| `freebug_redraw_fb` | function | `gui/browser_ui.c:14135` | `static void freebug_redraw_fb(freebug_window *fb)` |
| `freebug_repl_worker` | function | `gui/browser_ui.c:14244` | `static tab *freebug_repl_worker(browser_window *w)` |
| `freebug_show` | function | `gui/browser_ui.c:14191` | `static void freebug_show(browser_window *w)` |
| `freebug_toggle` | function | `gui/browser_ui.c:14221` | `static void freebug_toggle(browser_window *w)` |
| `freebug_window` | type_alias | `gui/browser_ui.c:546` | `typedef struct freebug_window freebug_window;` |
| `freebug_window` | struct | `gui/browser_ui.c:13853` | `` |
| `freedom_write_dir` | function | `gui/browser_ui.c:764` | `static int freedom_write_dir(char *out, size_t cap)` |
| `geom_from_layout` | function | `gui/browser_ui.c:11432` | `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,
                ...` |
| `go_omnibox` | function | `gui/browser_ui.c:14489` | `static void go_omnibox(browser_window *w)` |
| `grad_stop` | function | `gui/browser_ui.c:9464` | `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)` |
| `gui_subresource_fetch` | function | `gui/browser_ui.c:1387` | `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...` |
| `gutter` | function | `gui/browser_ui.c:565` | `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...` |
| `h` | type_alias | `gui/browser_ui.c:2993` | `typedef struct rc_box { double x, top, w, h;` |
| `handle_key_press` | function | `gui/browser_ui.c:15254` | `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...` |
| `have` | function | `gui/browser_ui.c:7612` | `* as they always have (spec/float.md §6b.3). The line still open beside * the previous float is committed first, at its ` |
| `hb_is_allowlisted` | function | `gui/browser_ui.c:1473` | `&& hb_is_allowlisted(w->hosts, ihost);` |
| `history_step` | function | `gui/browser_ui.c:12598` | `static void history_step(browser_window *w, int steps)` |
| `host_from_url` | function | `gui/browser_ui.c:1022` | `static int host_from_url(const char *url, char *out, size_t outsz)` |
| `hot_actionable` | function | `gui/browser_ui.c:2857` | `static int hot_actionable(const browser_window *w, ui_hot hot)` |
| `html_center_offset` | function | `gui/browser_ui.c:2720` | `static double html_center_offset(const browser_window *w)` |
| `in` | function | `gui/browser_ui.c:12187` | `* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);` |
| `init_net_config` | function | `gui/browser_ui.c:997` | `static void init_net_config(browser_window *w)` |
| `input_box_width` | function | `gui/browser_ui.c:8156` | `static double input_box_width(double content_w)` |
| `input_is_editable` | function | `gui/browser_ui.c:1075` | `static int input_is_editable(int input_type)` |
| `input_is_interactive` | function | `gui/browser_ui.c:1069` | `static int input_is_interactive(int input_type)` |
| `insert_pasted_text` | function | `gui/browser_ui.c:14997` | `static void insert_pasted_text(browser_window *w, const char *text, size_t len)` |
| `is_http_url` | function | `gui/browser_ui.c:1011` | `static int is_http_url(const char *s)` |
| `is_https_url` | function | `gui/browser_ui.c:1007` | `static int is_https_url(const char *s)` |
| `it` | function | `gui/browser_ui.c:7685` | `* column: flush first so the column lands above it (source order), * then move the anchor — the image bottom is the cont` |
| `item_at_level` | function | `gui/browser_ui.c:4997` | `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)` |
| `item_declared_basis` | function | `gui/browser_ui.c:4867` | `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...` |
| `item_root_box` | function | `gui/browser_ui.c:4480` | `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)` |
| `item_root_box_in` | function | `gui/browser_ui.c:4433` | `static int item_root_box_in(const rd_doc *doc, size_t b0, size_t b1, int cbox)` |
| `item_sides` | struct | `gui/browser_ui.c:4569` | `` |
| `item_sides_at_level` | function | `gui/browser_ui.c:4620` | `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,
                  ...` |
| `item_vmargins` | function | `gui/browser_ui.c:5106` | `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,
          ...` |
| `items` | function | `gui/browser_ui.c:5740` | `* items (Flexbox 4.2);` |
| `key` | type_alias | `gui/browser_ui.c:6614` | `typedef struct rc_defer_col { int key;` |
| `key` | function | `gui/browser_ui.c:7598` | `* founders splits by key (stories, rail, footer nav each take * their column);` |
| `key_is_repeatable` | function | `gui/browser_ui.c:15584` | `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)` |
| `key_repeat_arm` | function | `gui/browser_ui.c:15600` | `static void key_repeat_arm(browser_window *w, uint32_t key)` |
| `key_repeat_fire` | function | `gui/browser_ui.c:15624` | `static void key_repeat_fire(browser_window *w)` |
| `key_repeat_stop` | function | `gui/browser_ui.c:15613` | `static void key_repeat_stop(browser_window *w)` |
| `key_sym_to_js_key` | function | `gui/browser_ui.c:15145` | `static const char *key_sym_to_js_key(xkb_keysym_t sym)` |
| `key_sym_to_keycode` | function | `gui/browser_ui.c:15171` | `static int key_sym_to_keycode(xkb_keysym_t sym)` |
| `keyboard_enter` | function | `gui/browser_ui.c:15130` | `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...` |
| `keyboard_key` | function | `gui/browser_ui.c:15638` | `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...` |
| `keyboard_keymap` | function | `gui/browser_ui.c:15109` | `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...` |
| `keyboard_leave` | function | `gui/browser_ui.c:15137` | `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)` |
| `keyboard_modifiers` | function | `gui/browser_ui.c:15678` | `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...` |
| `keyboard_repeat_info` | function | `gui/browser_ui.c:15687` | `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)` |
| `kind` | type_alias | `gui/browser_ui.c:2973` | `typedef struct rc_row { rc_rowkind kind;` |
| `layer` | function | `gui/browser_ui.c:9706` | `* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the border` |
| `layout` | function | `gui/browser_ui.c:1140` | `* shared by layout (row height) and paint (blit), so they cannot drift apart. */
static int image...` |
| `layout_container` | function | `gui/browser_ui.c:5121` | `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...` |
| `layout_doc` | function | `gui/browser_ui.c:7397` | `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...` |
| `layout_float_band` | function | `gui/browser_ui.c:7020` | `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...` |
| `limits` | function | `gui/browser_ui.c:10935` | `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...` |
| `line` | function | `gui/browser_ui.c:3900` | `* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the same ` |
| `line_desc` | type_alias | `gui/browser_ui.c:3151` | `typedef struct rc_state { double cur_top, pending_gap, pen_x, line_asc, line_desc;` |
| `line_limit` | function | `gui/browser_ui.c:3333` | `static double line_limit(const rc_state *s, double content_w)` |
| `link_at_point` | function | `gui/browser_ui.c:12237` | `static const char *link_at_point(browser_window *w, double px, double py)` |
| `load_bg_images` | function | `gui/browser_ui.c:1920` | `static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)` |
| `load_current` | function | `gui/browser_ui.c:14476` | `static void load_current(browser_window *w)` |
| `load_favorites` | function | `gui/browser_ui.c:857` | `static void load_favorites(browser_window *w)` |
| `load_host_file` | function | `gui/browser_ui.c:688` | `static void load_host_file(hb_set *s, const char *dir, const char *name, hb_list list)` |
| `load_images` | function | `gui/browser_ui.c:1836` | `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)` |
| `loop` | function | `gui/browser_ui.c:14988` | `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately mig` |
| `main` | function | `gui/browser_ui.c:491` | `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never blocks` |
| `margin` | function | `gui/browser_ui.c:7936` | `* own left margin (the margin box starts at the anchor point), a right- * anchored one ends at it. Same for the vertical` |
| `measure_item_content_w` | function | `gui/browser_ui.c:4819` | `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...` |
| `measure_item_w_at` | function | `gui/browser_ui.c:4775` | `static double measure_item_w_at(cairo_t *cr, const browser_window *w,
                           ...` |
| `memory` | function | `gui/browser_ui.c:12681` | `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...` |
| `menu_item_checked` | function | `gui/browser_ui.c:13019` | `static int menu_item_checked(const browser_window *w, size_t i)` |
| `menu_item_toggle` | function | `gui/browser_ui.c:13041` | `static void menu_item_toggle(browser_window *w, size_t i)` |
| `menu_panel_rect` | function | `gui/browser_ui.c:2868` | `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...` |
| `mime_is_text` | function | `gui/browser_ui.c:14825` | `static int mime_is_text(const char *mime)` |
| `mr` | type_alias | `gui/browser_ui.c:4569` | `typedef struct item_sides { double ml, mr;` |
| `multicol_fragment` | function | `gui/browser_ui.c:5847` | `static double multicol_fragment(rc_layout *L, const rc_open_box *ob, double content_bottom);` |
| `nested_cont_basis` | function | `gui/browser_ui.c:4881` | `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...` |
| `nested_stop` | function | `gui/browser_ui.c:6367` | `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)` |
| `newtab_x` | function | `gui/browser_ui.c:2647` | `static double newtab_x(const browser_window *w)` |
| `node_at_point` | function | `gui/browser_ui.c:12426` | `static dom_node_id node_at_point(browser_window *w, double px, double py)` |
| `now_ms` | function | `gui/browser_ui.c:148` | `static uint64_t now_ms(void)` |
| `offset` | function | `gui/browser_ui.c:158` | `* offset (labels and the flag live in one place, no magic indices);` |
| `omni_refresh` | function | `gui/browser_ui.c:903` | `static void omni_refresh(browser_window *w)` |
| `open_line` | function | `gui/browser_ui.c:3718` | `static void open_line(rc_layout *L, rc_state *s)` |
| `open_line_height` | function | `gui/browser_ui.c:3705` | `static double open_line_height(const rc_state *s, const ui_theme *th)` |
| `origin` | function | `gui/browser_ui.c:12109` | `* top_url is the page origin (https or file://);` |
| `ov_box_bounds` | function | `gui/browser_ui.c:10242` | `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)` |
| `ov_box_clips` | function | `gui/browser_ui.c:10214` | `static int ov_box_clips(const pv_box_def *d)` |
| `ov_collect_chain` | function | `gui/browser_ui.c:10221` | `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)` |
| `ov_content_rect` | function | `gui/browser_ui.c:10266` | `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...` |
| `own` | function | `gui/browser_ui.c:5678` | `* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and its ` |
| `page_js_host_allowlisted` | function | `gui/browser_ui.c:1983` | `static int page_js_host_allowlisted(const browser_window *w)` |
| `page_trusted` | function | `gui/browser_ui.c:1385` | `static int page_trusted(const browser_window *w);` |
| `paint` | function | `gui/browser_ui.c:13463` | `static void paint(browser_window *w)` |
| `paint_bg_layer` | function | `gui/browser_ui.c:9545` | `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...` |
| `paint_box_and_direct_rows` | function | `gui/browser_ui.c:11044` | `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...` |
| `paint_box_decoration` | function | `gui/browser_ui.c:9589` | `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...` |
| `paint_box_decoration_grouped` | function | `gui/browser_ui.c:11004` | `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...` |
| `paint_content_row` | function | `gui/browser_ui.c:10026` | `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...` |
| `paint_deco_line` | function | `gui/browser_ui.c:9921` | `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...` |
| `paint_inline_replaced` | function | `gui/browser_ui.c:10006` | `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...` |
| `paint_nested_children` | function | `gui/browser_ui.c:11395` | `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...` |
| `paint_oof_sub` | function | `gui/browser_ui.c:11143` | `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,
                ...` |
| `paint_positioned_one` | function | `gui/browser_ui.c:11181` | `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...` |
| `paint_structured` | function | `gui/browser_ui.c:11485` | `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...` |
| `paint_svg_at` | function | `gui/browser_ui.c:9977` | `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...` |
| `paint_video_row` | function | `gui/browser_ui.c:9238` | `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...` |
| `path` | function | `gui/browser_ui.c:5422` | `*
         * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when
        ...` |
| `place_inline_replaced` | function | `gui/browser_ui.c:4153` | `static int place_inline_replaced(rc_layout *L, rc_state *s, const ui_theme *th,
                 ...` |
| `position_doc` | function | `gui/browser_ui.c:7989` | `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...` |
| `prepare_fetch` | function | `gui/browser_ui.c:1519` | `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...` |
| `presentation` | function | `gui/browser_ui.c:13039` | `* affect presentation (a repaint, which re-runs layout, suffices);` |
| `proceed` | function | `gui/browser_ui.c:1516` | `* may proceed (cfg and pr->allowlisted are then set);` |
| `produced` | function | `gui/browser_ui.c:3816` | `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target without ` |
| `profile_sync` | function | `gui/browser_ui.c:934` | `static void profile_sync(browser_window *w)` |
| `proxy` | function | `gui/browser_ui.c:994` | `* and enable each proxy ("1" => the default port);` |
| `proxy_addr_from_env` | function | `gui/browser_ui.c:983` | `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...` |
| `ptr_axis` | function | `gui/browser_ui.c:14785` | `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...` |
| `ptr_button` | function | `gui/browser_ui.c:14534` | `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...` |
| `ptr_enter` | function | `gui/browser_ui.c:14416` | `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...` |
| `ptr_frame` | function | `gui/browser_ui.c:14809` | `static void ptr_frame(void *d, struct wl_pointer *p)` |
| `ptr_leave` | function | `gui/browser_ui.c:14434` | `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)` |
| `ptr_motion` | function | `gui/browser_ui.c:14451` | `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)` |
| `publish_geometry` | function | `gui/browser_ui.c:11463` | `static void publish_geometry(browser_window *w, const rc_layout *L, double left,
                ...` |
| `rc_add_box` | function | `gui/browser_ui.c:3358` | `static rc_box *rc_add_box(rc_layout *L)` |
| `rc_add_frag` | function | `gui/browser_ui.c:3370` | `static rc_frag *rc_add_frag(rc_layout *L)` |
| `rc_add_row` | function | `gui/browser_ui.c:3385` | `static rc_row *rc_add_row(rc_layout *L)` |
| `rc_box` | struct | `gui/browser_ui.c:2993` | `` |
| `rc_box_context` | function | `gui/browser_ui.c:5993` | `static void rc_box_context(const rc_state *s, double content_w,
                           double...` |
| `rc_box_copy_decoration` | function | `gui/browser_ui.c:4519` | `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)` |
| `rc_defer` | struct | `gui/browser_ui.c:6621` | `` |
| `rc_defer_col` | struct | `gui/browser_ui.c:6614` | `` |
| `rc_ext` | struct | `gui/browser_ui.c:3737` | `` |
| `rc_float_bottom` | function | `gui/browser_ui.c:3246` | `static double rc_float_bottom(const rc_state *s)` |
| `rc_float_clear` | function | `gui/browser_ui.c:3255` | `static void rc_float_clear(rc_state *s)` |
| `rc_float_fit_line` | function | `gui/browser_ui.c:3314` | `static void rc_float_fit_line(rc_state *s, double line_h)` |
| `rc_float_refresh` | function | `gui/browser_ui.c:3268` | `static void rc_float_refresh(rc_state *s, double line_h)` |
| `rc_frag` | struct | `gui/browser_ui.c:2914` | `` |
| `rc_free` | function | `gui/browser_ui.c:3338` | `static void rc_free(rc_layout *L)` |
| `rc_layout` | struct | `gui/browser_ui.c:3046` | `` |
| `rc_oof_sub` | struct | `gui/browser_ui.c:3044` | `` |
| `rc_oof_sub` | struct | `gui/browser_ui.c:3084` | `` |
| `rc_open_box` | struct | `gui/browser_ui.c:3094` | `` |
| `rc_row` | struct | `gui/browser_ui.c:2974` | `` |
| `rc_rowkind` | enum | `gui/browser_ui.c:2972` | `` |
| `rc_state` | struct | `gui/browser_ui.c:3152` | `` |
| `rd_build` | function | `gui/browser_ui.c:8560` | `* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr, rgb_from_packed(b-` |
| `read_file` | function | `gui/browser_ui.c:639` | `static char *read_file(const char *path, size_t *out_len)` |
| `rebuild_inputs` | function | `gui/browser_ui.c:1189` | `static void rebuild_inputs(browser_window *w)` |
| `reconcile_boxes` | function | `gui/browser_ui.c:6470` | `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...` |
| `reconcile_boxes_below` | function | `gui/browser_ui.c:6388` | `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...` |
| `rect` | function | `gui/browser_ui.c:9433` | `* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops land on` |
| `redraw` | function | `gui/browser_ui.c:13707` | `static void redraw(browser_window *w)` |
| `redraws` | function | `gui/browser_ui.c:15848` | `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A 4 Ki` |
| `reference` | function | `gui/browser_ui.c:12507` | `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...` |
| `registry_global` | function | `gui/browser_ui.c:15724` | `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...` |
| `registry_remove` | function | `gui/browser_ui.c:15744` | `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)` |
| `remember_visit` | function | `gui/browser_ui.c:951` | `static void remember_visit(browser_window *w, const char *url)` |
| `render_current` | function | `gui/browser_ui.c:2282` | `static void render_current(browser_window *w)` |
| `render_current_ex` | function | `gui/browser_ui.c:2102` | `static void render_current_ex(browser_window *w, int allow_js_nav)` |
| `render_doc_images` | function | `gui/browser_ui.c:12113` | `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...` |
| `replaced_current_color` | function | `gui/browser_ui.c:9997` | `static int replaced_current_color(const browser_window *w, const rd_block *blk)` |
| `replaced_inline_size` | function | `gui/browser_ui.c:4085` | `static int replaced_inline_size(const browser_window *w, const rd_block *b,
                     ...` |
| `replaced_is_inline_level` | function | `gui/browser_ui.c:4115` | `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)` |
| `replaced_opens_inline_line` | function | `gui/browser_ui.c:4128` | `static size_t replaced_opens_inline_line(const rd_doc *doc, size_t i)` |
| `resizes` | function | `gui/browser_ui.c:13741` | `* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);` |
| `resolve` | function | `gui/browser_ui.c:2451` | `* origin so its relative references and local images resolve (confined to the * document's directory) -- a local page "a` |
| `resolve_box_cursor` | function | `gui/browser_ui.c:12330` | `static int resolve_box_cursor(const rd_doc *doc, int block_id)` |
| `root_cont_of` | function | `gui/browser_ui.c:5027` | `static int root_cont_of(const rd_doc *doc, int cid)` |
| `row` | function | `gui/browser_ui.c:4731` | `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...` |
| `row_align_offset` | function | `gui/browser_ui.c:9362` | `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)` |
| `row_line_slack` | function | `gui/browser_ui.c:9350` | `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)` |
| `row_owner_block_id` | function | `gui/browser_ui.c:9972` | `static int row_owner_block_id(const rc_layout *L, const rc_row *r);` |
| `rows` | function | `gui/browser_ui.c:10285` | `* RC_IMAGE rows (see its declaration);` |
| `run` | function | `gui/browser_ui.c:3622` | `* continuation run (block_id < 0 with no block break) deliberately skips reconcile
 * to stay on ...` |
| `run_width_cap` | function | `gui/browser_ui.c:4852` | `static double run_width_cap(const rd_block *b, double avail_w)` |
| `save_current_page` | function | `gui/browser_ui.c:12868` | `static void save_current_page(browser_window *w)` |
| `save_download` | function | `gui/browser_ui.c:12835` | `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...` |
| `saving` | function | `gui/browser_ui.c:15769` | `* disables saving (never clobber);` |
| `schedule_js_tick` | function | `gui/browser_ui.c:2092` | `static void schedule_js_tick(browser_window *w, int next_ms)` |
| `scroll_line_px` | function | `gui/browser_ui.c:14781` | `static double scroll_line_px(const browser_window *w)` |
| `scrollbar_drag_to` | function | `gui/browser_ui.c:2762` | `static void scrollbar_drag_to(browser_window *w)` |
| `scrollbar_metrics` | function | `gui/browser_ui.c:2734` | `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...` |
| `seat_caps` | function | `gui/browser_ui.c:15706` | `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)` |
| `seat_name` | function | `gui/browser_ui.c:15717` | `static void seat_name(void *d, struct wl_seat *s, const char *name)` |
| `secure_fetch` | function | `gui/browser_ui.c:1767` | `* through secure_fetch (Zero Trust);` |
| `seed_local_storage` | function | `gui/browser_ui.c:2027` | `static void seed_local_storage(browser_window *w, tab *t, int trusted)` |
| `seed_session_cookies` | function | `gui/browser_ui.c:2003` | `static void seed_session_cookies(tab *t, int trusted, const char *url)` |
| `select_box_width` | function | `gui/browser_ui.c:8160` | `static double select_box_width(double content_w)` |
| `set_cache` | function | `gui/browser_ui.c:1232` | `static void set_cache(browser_window *w, char *html, size_t len, const char *top)` |
| `set_cursor` | function | `gui/browser_ui.c:13776` | `static void set_cursor(browser_window *w, int cur_kind)` |
| `set_page_url` | function | `gui/browser_ui.c:12526` | `static void set_page_url(browser_window *w, const char *url)` |
| `set_rgb` | function | `gui/browser_ui.c:9836` | `set_rgb(cr, (ui_rgb)` |
| `set_rgb_alpha` | function | `gui/browser_ui.c:3428` | `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)` |
| `sf_ws_url_check` | function | `gui/browser_ui.c:12559` | `&& sf_ws_url_check(op->data) == SF_OK && rp_host_of(op->data, host, sizeof host) == 0 && hb_check(w->hosts, host) != HB_` |
| `show_busy` | function | `gui/browser_ui.c:2289` | `static void show_busy(browser_window *w)` |
| `show_fetch_error` | function | `gui/browser_ui.c:2298` | `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...` |
| `slot` | function | `gui/browser_ui.c:5292` | `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...` |
| `smaller` | function | `gui/browser_ui.c:3015` | `* size when the content is smaller (height) or wider (min-width);` |
| `spaced` | function | `gui/browser_ui.c:9512` | `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...` |
| `standalone` | function | `gui/browser_ui.c:7633` | `* must not be treated as standalone (which would flush that line and give * the element a row of its own -- R7). */ size` |
| `strcmp` | function | `gui/browser_ui.c:2417` | `&& strcmp(auth_host_buf, w->auth_host) != 0)` |
| `stream_progress_cb` | function | `gui/browser_ui.c:1643` | `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)` |
| `string` | function | `gui/browser_ui.c:1915` | `* or an empty string (unset, blocked, or off by caps.images), so there is no * decision to re-check, unlike load_images ` |
| `struct` | function | `gui/browser_ui.c:5408` | `* struct (0 = auto);` |
| `styled_advance` | function | `gui/browser_ui.c:3497` | `static double styled_advance(cairo_t *cr, const rc_frag *f)` |
| `styled_draw` | function | `gui/browser_ui.c:3513` | `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)` |
| `stylesheets` | function | `gui/browser_ui.c:2122` | `* External stylesheets (Hito 27) follow the author-styles opt-in -- or the * trusted-host doctrine (Hito 28) -- (GET-onl` |
| `surface_from_pixels` | function | `gui/browser_ui.c:1243` | `static cairo_surface_t *surface_from_pixels(const tab_image *img)` |
| `tab_ctx` | struct | `gui/browser_ui.c:269` | `` |
| `tab_ctx_release` | function | `gui/browser_ui.c:2521` | `static void tab_ctx_release(tab_ctx *c)` |
| `tab_new` | function | `gui/browser_ui.c:1962` | `static void tab_new(browser_window *w, const char *url);` |
| `tab_restore` | function | `gui/browser_ui.c:2495` | `static void tab_restore(browser_window *w)` |
| `tab_save` | function | `gui/browser_ui.c:2478` | `static void tab_save(browser_window *w)` |
| `tab_switch` | function | `gui/browser_ui.c:2545` | `static void tab_switch(browser_window *w, int idx)` |
| `tab_title` | function | `gui/browser_ui.c:2654` | `static const char *tab_title(const browser_window *w, int i)` |
| `tabbar_top` | function | `gui/browser_ui.c:2670` | `static double tabbar_top(const browser_window *w)` |
| `table` | function | `gui/browser_ui.c:4671` | `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...` |
| `text` | function | `gui/browser_ui.c:9437` | `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...` |
| `the` | function | `gui/browser_ui.c:10857` | `* the (already filtered) group with the shadow color, blur it, and * paint it under the group at the declared offset -- ` |
| `thumbnail` | function | `gui/browser_ui.c:7103` | `* is what made a wikipedia thumbnail (a 250px image and its caption, no
     * declared width) sp...` |
| `toggle` | function | `gui/browser_ui.c:1972` | `* No network: a capability toggle (images/CSS) re-renders from cache. Does nothing * when there is no cached source (sta` |
| `toggle_fullscreen` | function | `gui/browser_ui.c:1054` | `static void toggle_fullscreen(browser_window *w)` |
| `toggle_reader` | function | `gui/browser_ui.c:13008` | `static void toggle_reader(browser_window *w)` |
| `toolbar_button_at` | function | `gui/browser_ui.c:2841` | `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)` |
| `toolbar_rects` | function | `gui/browser_ui.c:2826` | `static void toolbar_rects(const browser_window *w,
                          double *back_x, doub...` |
| `toolbar_top` | function | `gui/browser_ui.c:2676` | `static double toolbar_top(const browser_window *w)` |
| `toplevel_close` | function | `gui/browser_ui.c:13755` | `static void toplevel_close(void *data, struct xdg_toplevel *t)` |
| `toplevel_configure` | function | `gui/browser_ui.c:13733` | `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...` |
| `treatment` | function | `gui/browser_ui.c:6439` | `* block treatment (shrink-wrapped and placed by text-align), which is what a
         * standalon...` |
| `ua_box_rect` | function | `gui/browser_ui.c:2884` | `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...` |
| `ui_bg_image` | struct | `gui/browser_ui.c:252` | `` |
| `ui_dump_layout` | function | `gui/browser_ui.c:12165` | `ui_status ui_dump_layout(const rd_doc *doc)` |
| `ui_hot` | enum | `gui/browser_ui.c:208` | `` |
| `ui_image` | struct | `gui/browser_ui.c:239` | `` |
| `ui_input_state` | struct | `gui/browser_ui.c:215` | `` |
| `ui_menu_action` | enum | `gui/browser_ui.c:160` | `` |
| `ui_menu_item` | struct | `gui/browser_ui.c:177` | `` |
| `ui_render_pdf_images` | function | `gui/browser_ui.c:12150` | `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...` |
| `ui_render_png` | function | `gui/browser_ui.c:12053` | `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)` |
| `ui_render_png_images` | function | `gui/browser_ui.c:12144` | `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...` |
| `ui_run_browser` | function | `gui/browser_ui.c:15754` | `ui_status ui_run_browser(const char *start_url)` |
| `uitab_close` | function | `gui/browser_ui.c:2605` | `static void uitab_close(browser_window *w, int idx)` |
| `upstream` | function | `gui/browser_ui.c:9390` | `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...` |
| `utf8_clen` | function | `gui/browser_ui.c:3437` | `static size_t utf8_clen(const char *s, size_t n)` |
| `v_read` | function | `gui/browser_ui.c:8744` | `static int v_read(int fd, void *buf, size_t n)` |
| `video_feeder_thread` | function | `gui/browser_ui.c:1049` | `static void *video_feeder_thread(void *arg);` |
| `video_fetch` | function | `gui/browser_ui.c:9065` | `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...` |
| `video_play` | function | `gui/browser_ui.c:9082` | `static int video_play(browser_window *w, const char *m3u8_url)` |
| `video_stop` | function | `gui/browser_ui.c:8887` | `static void video_stop(browser_window *w)` |
| `video_stop` | function | `gui/browser_ui.c:9184` | `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...` |
| `way` | function | `gui/browser_ui.c:4772` | `* intrinsic box either way (it does not wrap below its own size). */ static int block_leaves_flow(const rd_doc *doc, con` |
| `window_button_rects` | function | `gui/browser_ui.c:2816` | `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...` |
| `wl_array_for_each` | function | `gui/browser_ui.c:13749` | `wl_array_for_each(st, states)` |
| `wm_base_ping` | function | `gui/browser_ui.c:13719` | `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)` |
| `write_doc_pdf` | function | `gui/browser_ui.c:11703` | `static long write_doc_pdf(browser_window *w, const char *path)` |
| `write_doc_png` | function | `gui/browser_ui.c:11872` | `static long write_doc_png(browser_window *w, const char *path)` |
| `write_file_atomic` | function | `gui/browser_ui.c:12813` | `static int write_file_atomic(const char *path, const void *bytes, size_t len)` |
| `ws_apply_ops` | function | `gui/browser_ui.c:12551` | `static void ws_apply_ops(browser_window *w, const tab_page *page)` |
| `x` | function | `gui/browser_ui.c:6852` | `* reported x is already the BORDER x (the §7c.2 rule);` |
| `xdg_surface_configure` | function | `gui/browser_ui.c:13725` | `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)` |
| `yet` | function | `gui/browser_ui.c:7385` | `* does not carry yet (WPT flex-abspos-staticpos-*). */
static int runs_share_float(const rd_doc *...` |
| `FREEDOM_BROWSER_UI_INTERNAL_H` | macro | `gui/browser_ui_internal.h:2` | `#define FREEDOM_BROWSER_UI_INTERNAL_H` |
| `UI_FONT_SIZE` | macro | `gui/browser_ui_internal.h:30` | `#define UI_FONT_SIZE` |
| `UI_HEADING_LEVELS` | macro | `gui/browser_ui_internal.h:32` | `#define UI_HEADING_LEVELS` |
| `UI_TEXT_MARGIN` | macro | `gui/browser_ui_internal.h:31` | `#define UI_TEXT_MARGIN` |
| `b` | type_alias | `gui/browser_ui_internal.h:40` | `typedef struct ui_rgb { double r, g, b;` |
| `body_font` | type_alias | `gui/browser_ui_internal.h:42` | `typedef struct ui_theme { double body_font;` |
| `set_rgb` | function | `gui/browser_ui_internal.h:106` | `void set_rgb(cairo_t *cr, ui_rgb c);` |
| `ui_rgb` | struct | `gui/browser_ui_internal.h:41` | `` |
| `ui_theme` | struct | `gui/browser_ui_internal.h:43` | `` |
| `ui_theme_mode` | enum | `gui/browser_ui_internal.h:93` | `` |
| `rgb_from_packed` | function | `gui/bui_theme.c:180` | `ui_rgb rgb_from_packed(int packed)` |
| `set_rgb` | function | `gui/bui_theme.c:185` | `void set_rgb(cairo_t *cr, ui_rgb c)` |
| `ui_theme_dark` | function | `gui/bui_theme.c:84` | `ui_theme ui_theme_dark(void)` |
| `ui_theme_default` | function | `gui/bui_theme.c:14` | `ui_theme ui_theme_default(void)` |
| `ui_theme_for` | function | `gui/bui_theme.c:171` | `ui_theme ui_theme_for(int mode)` |
| `ui_theme_sepia` | function | `gui/bui_theme.c:129` | `ui_theme ui_theme_sepia(void)` |
| `_POSIX_C_SOURCE` | macro | `gui/freedom_view.c:10` | `#define _POSIX_C_SOURCE` |
| `main` | function | `gui/freedom_view.c:37` | `int main(int argc, char **argv)` |
| `svp_alpha` | function | `gui/svg_paint.c:31` | `static double svp_alpha(int opacity, int paint_opacity)` |
| `svp_draw` | function | `gui/svg_paint.c:139` | `void svp_draw(cairo_t *cr, const sv_image *img,
              double x, double y, double w, doubl...` |
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
| `ptr_axis` | function | `gui/ui_render.c:344` | `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...` |
| `ptr_button` | function | `gui/ui_render.c:322` | `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...` |
| `ptr_enter` | function | `gui/ui_render.c:305` | `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...` |
| `ptr_leave` | function | `gui/ui_render.c:312` | `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)` |
| `ptr_motion` | function | `gui/ui_render.c:315` | `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)` |
| `redraw` | function | `gui/ui_render.c:245` | `static void redraw(ui_window *w)` |
| `registry_global` | function | `gui/ui_render.c:383` | `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...` |
| `registry_remove` | function | `gui/ui_render.c:401` | `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)` |
| `sanitize_utf8_inplace` | function | `gui/ui_render.c:39` | `static void sanitize_utf8_inplace(char *s)` |
| `seat_caps` | function | `gui/ui_render.c:367` | `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)` |
| `seat_name` | function | `gui/ui_render.c:376` | `static void seat_name(void *d, struct wl_seat *s, const char *name)` |
| `toplevel_close` | function | `gui/ui_render.c:283` | `static void toplevel_close(void *data, struct xdg_toplevel *t)` |
| `toplevel_configure` | function | `gui/ui_render.c:274` | `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...` |
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
| `probability` | function | `include/anti_fp.h:93` | `* keys with overwhelming probability (canvas/audio noise is not linkable across * sites, defeating cross-origin fingerpr` |
| `properties` | function | `include/anti_fp.h:67` | `* Legacy navigator properties (Hito 30b): normalized Firefox values shared by * js_env and the network layer so JS and H` |
| `ABSENT` | function | `include/block_flow.h:26` | `* as ABSENT (0) rather than propagated: a poisoned length must not spread into * the geometry of the rest of the page. *` |
| `FREEDOM_BLOCK_FLOW_H` | macro | `include/block_flow.h:11` | `#define FREEDOM_BLOCK_FLOW_H` |
| `bf_collapse_n` | function | `include/block_flow.h:33` | `* bf_collapse_n((double[])` |
| `bf_margins_adjoin` | function | `include/block_flow.h:43` | `int bf_margins_adjoin(double border_px, double padding_px);` |
| `BX_TAG_NAME_MAX` | macro | `include/box_style.h:33` | `#define BX_TAG_NAME_MAX` |
| `BX_TROLE_NONE` | function | `include/box_style.h:144` | `* BX_TROLE_NONE (an unrecognised element joins no table -- fail closed). */ bx_table_role bx_table_role_of(const char *t` |
| `FREEDOM_BOX_STYLE_H` | macro | `include/box_style.h:2` | `#define FREEDOM_BOX_STYLE_H` |
| `box` | function | `include/box_style.h:115` | `* in_list nonzero when the block sits inside a list item: it then takes * the <li> box (zero margin), keeping items tigh` |
| `bx_background_layer` | function | `include/box_style.h:277` | `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h, double *out_x, double *out_y);` |
| `bx_bg_layer` | struct | `include/box_style.h:267` | `` |
| `bx_border_box_h` | function | `include/box_style.h:210` | `double bx_border_box_h(double declared_h, int border_box, double pad_t, double pad_b, double bord_t, double bord_b);` |
| `bx_box` | struct | `include/box_style.h:50` | `` |
| `bx_content_cap` | function | `include/box_style.h:244` | `double bx_content_cap(double width_cap, int border_box, double pad_l, double pad_r, double bord_l, double bord_r);` |
| `bx_display` | enum | `include/box_style.h:35` | `` |
| `bx_display_name` | function | `include/box_style.h:156` | `const char *bx_display_name(bx_display d);` |
| `bx_edges` | struct | `include/box_style.h:46` | `` |
| `bx_hplace` | struct | `include/box_style.h:63` | `` |
| `bx_lp_px` | function | `include/box_style.h:236` | `double bx_lp_px(int px_val, int pct_pm, double basis);` |
| `bx_replaced_box` | function | `include/box_style.h:196` | `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den, double avail_w, double *out_w, double *out_h);` |
| `bx_status` | enum | `include/box_style.h:56` | `` |
| `bx_table_role` | enum | `include/box_style.h:127` | `` |
| `bx_ua_tag` | enum | `include/box_style.h:84` | `` |
| `bx_width_cap` | function | `include/box_style.h:172` | `double bx_width_cap(int w_px, int w_pct, double avail_w);` |
| `bx_width_cap2` | function | `include/box_style.h:177` | `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w);` |
| `display` | type_alias | `include/box_style.h:49` | `typedef struct bx_box { bx_display display;` |
| `left` | type_alias | `include/box_style.h:46` | `typedef struct bx_edges { double top, right, bottom, left;` |
| `nat_h` | type_alias | `include/box_style.h:267` | `typedef struct bx_bg_layer { double nat_w, nat_h;` |
| `page` | function | `include/box_style.h:214` | `* instead of letting it extend the page (CSS 2.1 section 10.7 + 11.1.1). That * is the case unless BOTH overflow axes ar` |
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
| `bottom` | function | `include/box_tree.h:190` | `* bottom with auto top still anchors bottom (R8). * `placed` (may be NULL) marks which boxes have an in-flow rect in box` |
| `box_index` | type_alias | `include/box_tree.h:128` | `typedef struct bt_positioned { size_t box_index;` |
| `bt_box_hidden` | function | `include/box_tree.h:215` | `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid);` |
| `bt_containing_block` | function | `include/box_tree.h:244` | `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i, const double *box_x, const double *box_y, const` |
| `bt_node` | struct | `include/box_tree.h:67` | `` |
| `bt_oof_anchor` | function | `include/box_tree.h:229` | `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid);` |
| `bt_oof_root` | function | `include/box_tree.h:230` | `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid);` |
| `bt_positioned` | struct | `include/box_tree.h:128` | `` |
| `bt_status` | enum | `include/box_tree.h:135` | `` |
| `closed` | function | `include/box_tree.h:34` | `* fails closed (BT_ERR_RANGE) instead of overflowing the stack. */ #define BT_MAX_DEPTH 64u #define BT_MAX_CHILDREN 128u` |
| `display` | type_alias | `include/box_tree.h:66` | `typedef struct bt_node { bx_display display;` |
| `flow` | function | `include/box_tree.h:183` | `* position is where the box would have started in flow (CSS 2.2 §10.3.7/§10.6.4);` |
| `insets` | function | `include/box_tree.h:234` | `* minus the two insets (px half + per-mille half of cb), an auto/unset inset * counting 0, never below 0. *both (may be ` |
| `line` | function | `include/box_tree.h:97` | `* its line (already resolved from align-self / the * container's align-items by the caller). */ /* this node as a grid i` |
| `node` | function | `include/box_tree.h:144` | `* node (x/y parent-relative, w/h border-box). display:none nodes get a zero rect and * take no space. The caller compose` |
| `one` | function | `include/box_tree.h:81` | `* of forcing them all onto one (flex-wrap);` |
| `placed` | function | `include/box_tree.h:197` | `* box counts as placed (legacy behaviour). * bt_resolve_positioning delegates with NULL arrays (legacy behaviour). */ bt` |
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
| `copied` | function | `include/browser.h:143` | `* copied (truncated to fit) and shown until now_ms reaches the expiry * (now_ms + BROWSER_STATUS_DURATION_MS). A NULL or` |
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
| `CSS_BORDER_SPACING_MAX` | macro | `include/css.h:423` | `#define CSS_BORDER_SPACING_MAX` |
| `CSS_BORDER_W_MAX` | macro | `include/css.h:422` | `#define CSS_BORDER_W_MAX` |
| `CSS_COLUMN_COUNT_MAX` | macro | `include/css.h:489` | `#define CSS_COLUMN_COUNT_MAX` |
| `CSS_CONTAIN_LAYOUT` | macro | `include/css.h:333` | `#define CSS_CONTAIN_LAYOUT` |
| `CSS_CONTAIN_PAINT` | macro | `include/css.h:335` | `#define CSS_CONTAIN_PAINT` |
| `CSS_CONTAIN_SIZE` | macro | `include/css.h:332` | `#define CSS_CONTAIN_SIZE` |
| `CSS_CONTAIN_STYLE` | macro | `include/css.h:334` | `#define CSS_CONTAIN_STYLE` |
| `CSS_DECO_LINE_THROUGH` | macro | `include/css.h:93` | `#define CSS_DECO_LINE_THROUGH` |
| `CSS_DECO_OVERLINE` | macro | `include/css.h:94` | `#define CSS_DECO_OVERLINE` |
| `CSS_DECO_UNDERLINE` | macro | `include/css.h:92` | `#define CSS_DECO_UNDERLINE` |
| `CSS_DROP_PROP_MAX` | macro | `include/css.h:983` | `#define CSS_DROP_PROP_MAX` |
| `CSS_DROP_VAL_MAX` | macro | `include/css.h:984` | `#define CSS_DROP_VAL_MAX` |
| `CSS_EM_MILLI_MAX` | macro | `include/css.h:479` | `#define CSS_EM_MILLI_MAX` |
| `CSS_FLEX_FACTOR_MAX` | macro | `include/css.h:424` | `#define CSS_FLEX_FACTOR_MAX` |
| `CSS_FONT_SIZE_MAX` | macro | `include/css.h:485` | `#define CSS_FONT_SIZE_MAX` |
| `CSS_GAP_MAX` | macro | `include/css.h:75` | `#define CSS_GAP_MAX` |
| `CSS_GRAD_STOPS_MAX` | macro | `include/css.h:84` | `#define CSS_GRAD_STOPS_MAX` |
| `CSS_GRID_AREAS_MAX` | macro | `include/css.h:83` | `#define CSS_GRID_AREAS_MAX` |
| `CSS_GRID_COLS_MAX` | macro | `include/css.h:76` | `#define CSS_GRID_COLS_MAX` |
| `CSS_GRID_SPAN_MAX` | macro | `include/css.h:425` | `#define CSS_GRID_SPAN_MAX` |
| `CSS_GRID_TRACKS_MAX` | macro | `include/css.h:77` | `#define CSS_GRID_TRACKS_MAX` |
| `CSS_LEN_AUTO` | macro | `include/css.h:437` | `#define CSS_LEN_AUTO` |
| `CSS_LEN_END` | macro | `include/css.h:438` | `#define CSS_LEN_END` |
| `CSS_LEN_FIT_CONTENT` | macro | `include/css.h:447` | `#define CSS_LEN_FIT_CONTENT` |
| `CSS_LEN_IS_INTRINSIC` | macro | `include/css.h:450` | `#define CSS_LEN_IS_INTRINSIC(v)` |
| `CSS_LEN_MAX` | macro | `include/css.h:435` | `#define CSS_LEN_MAX` |
| `CSS_LEN_MAX_CONTENT` | macro | `include/css.h:446` | `#define CSS_LEN_MAX_CONTENT` |
| `CSS_LEN_MIN_CONTENT` | macro | `include/css.h:445` | `#define CSS_LEN_MIN_CONTENT` |
| `CSS_LEN_UNSET` | macro | `include/css.h:436` | `#define CSS_LEN_UNSET` |
| `CSS_LINE_MAX` | macro | `include/css.h:86` | `#define CSS_LINE_MAX` |
| `CSS_LINE_MIN` | macro | `include/css.h:85` | `#define CSS_LINE_MIN` |
| `CSS_MAX_ATTR_SEL` | macro | `include/css.h:548` | `#define CSS_MAX_ATTR_SEL` |
| `CSS_MAX_COMPOUNDS` | macro | `include/css.h:544` | `#define CSS_MAX_COMPOUNDS` |
| `CSS_MAX_KF_STOPS` | macro | `include/css.h:836` | `#define CSS_MAX_KF_STOPS` |
| `CSS_MAX_PSEUDO_SEL` | macro | `include/css.h:552` | `#define CSS_MAX_PSEUDO_SEL` |
| `CSS_MEDIA_DEFAULT_HEIGHT` | macro | `include/css.h:944` | `#define CSS_MEDIA_DEFAULT_HEIGHT` |
| `CSS_MEDIA_DEFAULT_WIDTH` | macro | `include/css.h:939` | `#define CSS_MEDIA_DEFAULT_WIDTH` |
| `CSS_NTH_MAX` | macro | `include/css.h:556` | `#define CSS_NTH_MAX` |
| `CSS_PCT_MAX` | macro | `include/css.h:473` | `#define CSS_PCT_MAX` |
| `CSS_PSEUDO_AFTER` | macro | `include/css.h:1114` | `#define CSS_PSEUDO_AFTER` |
| `CSS_PSEUDO_BEFORE` | macro | `include/css.h:1113` | `#define CSS_PSEUDO_BEFORE` |
| `CSS_SHADOW_MAX` | macro | `include/css.h:430` | `#define CSS_SHADOW_MAX` |
| `CSS_SPACING_MAX` | macro | `include/css.h:429` | `#define CSS_SPACING_MAX` |
| `CSS_URL_MAX` | macro | `include/css.h:87` | `#define CSS_URL_MAX` |
| `FREEDOM_CSS_H` | macro | `include/css.h:2` | `#define FREEDOM_CSS_H` |
| `POINTER` | function | `include/css.h:207` | `* POINTER (shows the hand cursor already used for links) from every other value * (shows the default arrow);` |
| `color` | type_alias | `include/css.h:563` | `typedef struct css_style { int color;` |
| `css_align` | enum | `include/css.h:34` | `` |
| `css_align_kw` | enum | `include/css.h:166` | `` |
| `css_appearance` | enum | `include/css.h:295` | `` |
| `css_attr` | struct | `include/css.h:1032` | `` |
| `css_backface` | enum | `include/css.h:415` | `` |
| `css_bg_attachment` | enum | `include/css.h:324` | `` |
| `css_bg_clip` | enum | `include/css.h:315` | `` |
| `css_bg_origin` | enum | `include/css.h:320` | `` |
| `css_bg_repeat` | enum | `include/css.h:306` | `` |
| `css_bg_size` | enum | `include/css.h:311` | `` |
| `css_border_collapse` | enum | `include/css.h:253` | `` |
| `css_border_style` | enum | `include/css.h:147` | `` |
| `css_box_sizing` | enum | `include/css.h:140` | `` |
| `css_caption_side` | enum | `include/css.h:265` | `` |
| `css_clear` | enum | `include/css.h:185` | `` |
| `css_color_scheme` | enum | `include/css.h:345` | `` |
| `css_column_fill` | enum | `include/css.h:406` | `` |
| `css_column_span` | enum | `include/css.h:411` | `` |
| `css_content_visibility` | enum | `include/css.h:337` | `` |
| `css_cursor` | enum | `include/css.h:210` | `` |
| `css_direction` | enum | `include/css.h:247` | `` |
| `css_display` | enum | `include/css.h:42` | `` |
| `css_drop` | struct | `include/css.h:991` | `` |
| `css_drop_cause` | enum | `include/css.h:978` | `` |
| `css_drop_log` | struct | `include/css.h:1003` | `` |
| `css_element` | struct | `include/css.h:1042` | `` |
| `css_empty_cells` | enum | `include/css.h:259` | `` |
| `css_flex_direction` | enum | `include/css.h:154` | `` |
| `css_flex_wrap` | enum | `include/css.h:160` | `` |
| `css_float` | enum | `include/css.h:179` | `` |
| `css_font_face_at` | function | `include/css.h:1143` | `int css_font_face_at(const css_sheet *sheet, size_t i, char *family, size_t fam_cap, char *src_url, size_t url_cap);` |
| `css_font_face_count` | function | `include/css.h:1142` | `size_t css_font_face_count(const css_sheet *sheet);` |
| `css_font_family` | enum | `include/css.h:98` | `` |
| `css_font_kerning` | enum | `include/css.h:374` | `` |
| `css_font_stretch` | enum | `include/css.h:383` | `` |
| `css_font_variant` | enum | `include/css.h:277` | `` |
| `css_forced_color_adjust` | enum | `include/css.h:353` | `` |
| `css_free` | function | `include/css.h:1018` | `void css_free(css_sheet *s);` |
| `css_grid_flow` | enum | `include/css.h:173` | `` |
| `css_hyphens` | enum | `include/css.h:283` | `` |
| `css_image_rendering` | enum | `include/css.h:341` | `` |
| `css_isolation` | enum | `include/css.h:328` | `` |
| `css_justify` | enum | `include/css.h:64` | `` |
| `css_list_pos` | enum | `include/css.h:370` | `` |
| `css_list_style` | enum | `include/css.h:121` | `` |
| `css_media` | struct | `include/css.h:927` | `` |
| `css_mix_blend` | enum | `include/css.h:358` | `` |
| `css_object_fit` | enum | `include/css.h:365` | `` |
| `css_overflow` | enum | `include/css.h:202` | `` |
| `css_overscroll` | enum | `include/css.h:401` | `` |
| `css_pct_slot` | enum | `include/css.h:491` | `` |
| `css_pointer_events` | enum | `include/css.h:301` | `` |
| `css_position` | enum | `include/css.h:133` | `` |
| `css_print_color_adjust` | enum | `include/css.h:349` | `` |
| `css_resize` | enum | `include/css.h:389` | `` |
| `css_resolve_anim_keyframes` | function | `include/css.h:1151` | `void css_resolve_anim_keyframes(css_style *s, const css_sheet *sheet);` |
| `css_scroll_behavior` | enum | `include/css.h:393` | `` |
| `css_sel` | struct | `include/css.h:925` | `` |
| `css_sheet` | type_alias | `include/css.h:919` | `typedef struct css_sheet css_sheet;` |
| `css_status` | enum | `include/css.h:28` | `` |
| `css_style` | struct | `include/css.h:563` | `` |
| `css_table_layout` | enum | `include/css.h:271` | `` |
| `css_text_decoration_style` | enum | `include/css.h:240` | `` |
| `css_text_overflow` | enum | `include/css.h:219` | `` |
| `css_text_rendering` | enum | `include/css.h:378` | `` |
| `css_text_transform` | enum | `include/css.h:104` | `` |
| `css_touch_action` | enum | `include/css.h:397` | `` |
| `css_user_select` | enum | `include/css.h:289` | `` |
| `css_valign` | enum | `include/css.h:109` | `` |
| `css_visibility` | enum | `include/css.h:193` | `` |
| `css_white_space` | enum | `include/css.h:115` | `` |
| `css_word_break` | enum | `include/css.h:233` | `` |
| `cvr_table` | struct | `include/css.h:1103` | `` |
| `declared` | function | `include/css.h:801` | `* function was not declared (identity: 0 offset / 100% scale / 0deg). * Percentage translate arguments are not supported` |
| `element` | function | `include/css.h:806` | `* so two different rules matching the same element (e.g. one setting * translate, a more specific one setting rotate) ca` |
| `inherited_px` | function | `include/css.h:1126` | `* whose PARENT computes to inherited_px (<= 0 = unknown -> the CSS initial). * * Exported because the caller that walks ` |
| `order` | function | `include/css.h:1021` | `* cascade order (specificity, then document order), then the element's own * inline_style (which wins). sheet/tag/classe` |
| `palette` | function | `include/css.h:968` | `* so an inactive theme * palette (a dark palette in a light render) can never clobber the active one. * css_parse/css_pa` |
| `prefers_dark` | type_alias | `include/css.h:926` | `typedef struct css_media { int prefers_dark;` |
| `prop` | type_alias | `include/css.h:991` | `typedef struct css_drop { char prop[CSS_DROP_PROP_MAX];` |
| `scaleY` | function | `include/css.h:797` | `* scaleY() as a PERCENT of identity (100 = scale(1), matching font_scale's * convention);` |
| `slots` | function | `include/css.h:813` | `* parse time into ALL seven slots (singular matrices fail closed);` |
| `translate` | function | `include/css.h:796` | `* translate()/translateX()/translateY();` |
| `verbatim` | function | `include/css.h:79` | `* the quoted row strings verbatim (flex_layout parses them);` |
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
| `cb_expand_box2` | function | `include/css_box.h:21` | `int cb_expand_box2(const char *val, int slot_start, int slot_end, int allow_auto, int allow_neg, css_decl *dst, int cap)` |
| `cb_expand_box4` | function | `include/css_box.h:19` | `int cb_expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg, css_decl *dst, int cap);` |
| `cb_expand_grid_template_cols` | function | `include/css_box.h:38` | `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap);` |
| `cb_interp_align` | function | `include/css_box.h:28` | `int cb_interp_align(const char *v);` |
| `cb_interp_display` | function | `include/css_box.h:34` | `int cb_interp_display(const char *v);` |
| `cb_interp_fontsize_ex` | function | `include/css_box.h:29` | `int cb_interp_fontsize_ex(const char *v, int *abs_out);` |
| `cb_interp_gap` | function | `include/css_box.h:35` | `int cb_interp_gap(const char *v);` |
| `cb_interp_gridcols` | function | `include/css_box.h:37` | `int cb_interp_gridcols(const char *v);` |
| `cb_interp_justify` | function | `include/css_box.h:36` | `int cb_interp_justify(const char *v);` |
| `cb_interp_len` | function | `include/css_box.h:16` | `int cb_interp_len(const char *v, int allow_auto, int *out);` |
| `cb_interp_lineheight` | function | `include/css_box.h:30` | `int cb_interp_lineheight(const char *v);` |
| `cb_interp_lp` | function | `include/css_box.h:23` | `int cb_interp_lp(const char *v, int allow_auto, int allow_pct, int *out_px, int *out_pm);` |
| `cb_interp_style` | function | `include/css_box.h:32` | `int cb_interp_style(const char *v);` |
| `cb_interp_textdeco` | function | `include/css_box.h:33` | `int cb_interp_textdeco(const char *v);` |
| `cb_interp_weight` | function | `include/css_box.h:31` | `int cb_interp_weight(const char *v);` |
| `cb_length_px` | function | `include/css_box.h:15` | `int cb_length_px(const char *v, double *px);` |
| `cb_lp_can_be_nonneg` | function | `include/css_box.h:26` | `int cb_lp_can_be_nonneg(int px_val, int pct_pm);` |
| `cb_next_ws_token` | function | `include/css_box.h:27` | `int cb_next_ws_token(const char **p, char *tok, size_t cap);` |
| `cb_value_em_milli` | function | `include/css_box.h:25` | `int cb_value_em_milli(const char *v);` |
| `CCH_CHAIN_MAX` | macro | `include/css_chain.h:26` | `#define CCH_CHAIN_MAX` |
| `CCH_NTH_MAX` | macro | `include/css_chain.h:28` | `#define CCH_NTH_MAX` |
| `CCH_SIB_MAX` | macro | `include/css_chain.h:27` | `#define CCH_SIB_MAX` |
| `FREEDOM_CSS_CHAIN_H` | macro | `include/css_chain.h:2` | `#define FREEDOM_CSS_CHAIN_H` |
| `box` | function | `include/css_chain.h:72` | `* generated box (css_resolve_pseudo) against the same element context. * font_size is el's own COMPUTED font-size (the p` |
| `cch_element_matches` | function | `include/css_chain.h:69` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel);` |
| `cvr_chain` | struct | `include/css_chain.h:51` | `` |
| `cvr_table` | struct | `include/css_chain.h:52` | `` |
| `CC_COLOR_CURRENT` | macro | `include/css_color.h:59` | `#define CC_COLOR_CURRENT` |
| `CC_COLOR_TRANSPARENT` | macro | `include/css_color.h:60` | `#define CC_COLOR_TRANSPARENT` |
| `FREEDOM_CSS_COLOR_H` | macro | `include/css_color.h:2` | `#define FREEDOM_CSS_COLOR_H` |
| `b` | type_alias | `include/css_color.h:26` | `typedef struct cc_rgb { unsigned char r, g, b;` |
| `cc_pack` | function | `include/css_color.h:49` | `int cc_pack(cc_rgb c);` |
| `cc_rgb` | struct | `include/css_color.h:27` | `` |
| `cc_status` | enum | `include/css_color.h:31` | `` |
| `CSS_INLINE_BG_URLS` | macro | `include/css_decl.h:23` | `#define CSS_INLINE_BG_URLS` |
| `CSS_MAX_BG_URLS` | macro | `include/css_decl.h:11` | `#define CSS_MAX_BG_URLS` |
| `CSS_MAX_CONTENT_URLS` | macro | `include/css_decl.h:18` | `#define CSS_MAX_CONTENT_URLS` |
| `CSS_MAX_KEYFRAMES` | macro | `include/css_decl.h:20` | `#define CSS_MAX_KEYFRAMES` |
| `CSS_MAX_KEYFRAME_DECLS` | macro | `include/css_decl.h:22` | `#define CSS_MAX_KEYFRAME_DECLS` |
| `CSS_MAX_KEYFRAME_STOPS` | macro | `include/css_decl.h:21` | `#define CSS_MAX_KEYFRAME_STOPS` |
| `CSS_WIDE_PROBE_DECLS` | macro | `include/css_decl.h:29` | `#define CSS_WIDE_PROBE_DECLS` |
| `FREEDOM_CSS_DECL_H` | macro | `include/css_decl.h:2` | `#define FREEDOM_CSS_DECL_H` |
| `contiguous` | function | `include/css_decl.h:59` | `* contiguous (dx,dy,color) so expand_shadow writes them as a group. */ P_FONTFAMILY, P_TEXTTRANSFORM, P_LETTERSPACING, P` |
| `css_decl` | struct | `include/css_decl.h:181` | `` |
| `order` | function | `include/css_decl.h:44` | `* The four margin slots are contiguous in CSS shorthand order (top,right,bottom, * left);` |
| `prop` | type_alias | `include/css_decl.h:180` | `typedef struct css_decl { int prop;` |
| `FREEDOM_CSS_GRADIENT_H` | macro | `include/css_gradient.h:2` | `#define FREEDOM_CSS_GRADIENT_H` |
| `cg_expand_background` | function | `include/css_gradient.h:13` | `int cg_expand_background(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlc` |
| `cg_expand_bg_image` | function | `include/css_gradient.h:11` | `int cg_expand_bg_image(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap` |
| `CL_FALLBACK_CAP_RATIO` | macro | `include/css_length.h:58` | `#define CL_FALLBACK_CAP_RATIO` |
| `CL_FALLBACK_CH_RATIO` | macro | `include/css_length.h:57` | `#define CL_FALLBACK_CH_RATIO` |
| `CL_FALLBACK_EX_RATIO` | macro | `include/css_length.h:56` | `#define CL_FALLBACK_EX_RATIO` |
| `CL_FALLBACK_IC_RATIO` | macro | `include/css_length.h:59` | `#define CL_FALLBACK_IC_RATIO` |
| `CL_INITIAL_FONT_SIZE` | macro | `include/css_length.h:39` | `#define CL_INITIAL_FONT_SIZE` |
| `CL_MAX_TOKEN` | macro | `include/css_length.h:33` | `#define CL_MAX_TOKEN` |
| `CL_NORMAL_LINE_RATIO` | macro | `include/css_length.h:45` | `#define CL_NORMAL_LINE_RATIO` |
| `FREEDOM_CSS_LENGTH_H` | macro | `include/css_length.h:2` | `#define FREEDOM_CSS_LENGTH_H` |
| `cl_ctx` | struct | `include/css_length.h:84` | `` |
| `cl_is_length_unit` | function | `include/css_length.h:246` | `int cl_is_length_unit(const char *unit, size_t unit_len);` |
| `cl_lp` | struct | `include/css_length.h:132` | `` |
| `cl_number` | function | `include/css_length.h:230` | `int cl_number(const char *s, double *out, const char **endp);` |
| `cl_status` | enum | `include/css_length.h:61` | `` |
| `cl_unit_font_ratio` | function | `include/css_length.h:182` | `double cl_unit_font_ratio(const char *unit, size_t unit_len);` |
| `cl_unit_is_font_relative` | function | `include/css_length.h:157` | `* cl_unit_is_font_relative() draws. */ /* * Re-fits a resolved length to a different font-size: * * used = px + em * (fo` |
| `font_size` | type_alias | `include/css_length.h:84` | `typedef struct cl_ctx { double font_size;` |
| `here` | function | `include/css_length.h:186` | `* Every input cl_resolve accepts resolves identically here (with has_pct 0);` |
| `length` | function | `include/css_length.h:206` | `* * A basis that is not a usable length (negative, zero, non-finite) contributes * nothing, but the absolute component s` |
| `prelude` | function | `include/css_length.h:99` | `* correct context for a media query prelude (whose `em` is defined to use the * initial font size, never the author's ro` |
| `px` | type_alias | `include/css_length.h:132` | `typedef struct cl_lp { double px;` |
| `CMQ_MAX_DEPTH` | macro | `include/css_mq.h:16` | `#define CMQ_MAX_DEPTH` |
| `CMQ_TOK_MAX` | macro | `include/css_mq.h:17` | `#define CMQ_TOK_MAX` |
| `FREEDOM_CSS_MQ_H` | macro | `include/css_mq.h:2` | `#define FREEDOM_CSS_MQ_H` |
| `cmq_env` | struct | `include/css_mq.h:19` | `` |
| `cmq_matches` | function | `include/css_mq.h:28` | `int cmq_matches(const char *s, size_t len, const cmq_env *env);` |
| `width_px` | type_alias | `include/css_mq.h:18` | `typedef struct cmq_env { int width_px;` |
| `CSEL_FOLD_MARK` | macro | `include/css_select.h:171` | `#define CSEL_FOLD_MARK` |
| `CSEL_FOLD_PREFIX` | macro | `include/css_select.h:170` | `#define CSEL_FOLD_PREFIX` |
| `CSEL_IDENT_SCRATCH` | macro | `include/css_select.h:172` | `#define CSEL_IDENT_SCRATCH` |
| `CSS_MAX_CLASSES_PER_SEL` | macro | `include/css_select.h:28` | `#define CSS_MAX_CLASSES_PER_SEL` |
| `CSS_MAX_SUB_SELS` | macro | `include/css_select.h:80` | `#define CSS_MAX_SUB_SELS` |
| `CSS_SUB_MAX_ATTRS` | macro | `include/css_select.h:81` | `#define CSS_SUB_MAX_ATTRS` |
| `CSS_SUB_MAX_PSEUDOS` | macro | `include/css_select.h:82` | `#define CSS_SUB_MAX_PSEUDOS` |
| `CSS_TOK_MAX` | macro | `include/css_select.h:27` | `#define CSS_TOK_MAX` |
| `FREEDOM_CSS_SELECT_H` | macro | `include/css_select.h:2` | `#define FREEDOM_CSS_SELECT_H` |
| `csel_ci_eq` | function | `include/css_select.h:199` | `static inline int csel_ci_eq(const char *a, const char *b)` |
| `csel_decl_end` | function | `include/css_select.h:191` | `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace);` |
| `csel_emit_utf8` | function | `include/css_select.h:175` | `size_t csel_emit_utf8(unsigned int cp, char *out);` |
| `csel_escape_len` | function | `include/css_select.h:179` | `size_t csel_escape_len(const char *s, size_t i, size_t b);` |
| `csel_ident_ch` | function | `include/css_select.h:227` | `static inline int csel_ident_ch(char c)` |
| `csel_ident_eq` | function | `include/css_select.h:183` | `int csel_ident_eq(const char *stored, const char *tok, size_t tlen);` |
| `csel_ident_fold` | function | `include/css_select.h:181` | `void csel_ident_fold(const char *src, size_t len, char *dst);` |
| `csel_lower_ch` | function | `include/css_select.h:195` | `static inline char csel_lower_ch(char c)` |
| `csel_matches` | function | `include/css_select.h:159` | `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id, int allow_pseudo_el, int *pseudo_kind` |
| `csel_parse` | function | `include/css_select.h:150` | `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel);` |
| `csel_read_ident` | function | `include/css_select.h:186` | `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower);` |
| `csel_span_eq` | function | `include/css_select.h:208` | `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)` |
| `csel_substr` | function | `include/css_select.h:219` | `static inline int csel_substr(const char *hay, const char *needle, int ci)` |
| `csel_unescape` | function | `include/css_select.h:177` | `void csel_unescape(char *dst, size_t cap, const char *src, size_t n);` |
| `css_attr_match` | struct | `include/css_select.h:85` | `` |
| `css_compound` | struct | `include/css_select.h:119` | `` |
| `css_pseudo_match` | struct | `include/css_select.h:109` | `` |
| `css_sel` | struct | `include/css_select.h:136` | `` |
| `css_sub_sel` | struct | `include/css_select.h:92` | `` |
| `identifier` | function | `include/css_select.h:163` | `* A selector identifier (tag, .class, #id) is read with CSS escapes decoded * (`.md\:flex` is the class "md:flex") and s` |
| `kind` | type_alias | `include/css_select.h:109` | `typedef struct css_pseudo_match { int kind;` |
| `name` | type_alias | `include/css_select.h:85` | `typedef struct css_attr_match { char name[CSS_TOK_MAX];` |
| `parts` | type_alias | `include/css_select.h:136` | `typedef struct css_sel { css_compound parts[CSS_MAX_COMPOUNDS];` |
| `tag` | type_alias | `include/css_select.h:91` | `typedef struct css_sub_sel { char tag[CSS_TOK_MAX];` |
| `tag` | type_alias | `include/css_select.h:119` | `typedef struct css_compound { char tag[CSS_TOK_MAX];` |
| `FREEDOM_CSS_TEXT_H` | macro | `include/css_text.h:2` | `#define FREEDOM_CSS_TEXT_H` |
| `ct_emit_spacing` | function | `include/css_text.h:24` | `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val);` |
| `ct_expand_shadow` | function | `include/css_text.h:25` | `int ct_expand_shadow(const char *val, css_decl *dst, int cap);` |
| `ct_expand_valign` | function | `include/css_text.h:14` | `int ct_expand_valign(const char *val, css_decl *dst, int cap);` |
| `ct_interp_aspect_ratio` | function | `include/css_text.h:20` | `int ct_interp_aspect_ratio(const char *v, int *num, int *den);` |
| `ct_interp_direction` | function | `include/css_text.h:21` | `int ct_interp_direction(const char *v);` |
| `ct_interp_fontfamily` | function | `include/css_text.h:10` | `int ct_interp_fontfamily(const char *v);` |
| `ct_interp_liststyle` | function | `include/css_text.h:22` | `int ct_interp_liststyle(const char *v);` |
| `ct_interp_opacity` | function | `include/css_text.h:12` | `int ct_interp_opacity(const char *v);` |
| `ct_interp_spacing` | function | `include/css_text.h:23` | `int ct_interp_spacing(const char *v, int *out);` |
| `ct_interp_tabsize` | function | `include/css_text.h:17` | `int ct_interp_tabsize(const char *v);` |
| `ct_interp_textdeco_style` | function | `include/css_text.h:18` | `int ct_interp_textdeco_style(const char *v);` |
| `ct_interp_textdeco_thickness` | function | `include/css_text.h:19` | `int ct_interp_textdeco_thickness(const char *v);` |
| `ct_interp_texttransform` | function | `include/css_text.h:11` | `int ct_interp_texttransform(const char *v);` |
| `ct_interp_transition_property` | function | `include/css_text.h:15` | `int ct_interp_transition_property(const char *v);` |
| `ct_interp_valign` | function | `include/css_text.h:13` | `int ct_interp_valign(const char *v);` |
| `ct_interp_whitespace` | function | `include/css_text.h:16` | `int ct_interp_whitespace(const char *v);` |
| `FREEDOM_CSS_VALUES_H` | macro | `include/css_values.h:2` | `#define FREEDOM_CSS_VALUES_H` |
| `cv_bg_alpha_of` | function | `include/css_values.h:15` | `int cv_bg_alpha_of(const char *v);` |
| `cv_color_ok` | function | `include/css_values.h:14` | `int cv_color_ok(int c);` |
| `cv_interp_bg` | function | `include/css_values.h:16` | `int cv_interp_bg(const char *v);` |
| `cv_interp_color` | function | `include/css_values.h:13` | `int cv_interp_color(const char *v);` |
| `cv_parse_color` | function | `include/css_values.h:12` | `int cv_parse_color(const char *v);` |
| `CVR_CHAIN_MAX` | macro | `include/css_vars.h:45` | `#define CVR_CHAIN_MAX` |
| `CVR_MAX_DEPTH` | macro | `include/css_vars.h:22` | `#define CVR_MAX_DEPTH` |
| `CVR_MAX_ENTRIES` | macro | `include/css_vars.h:21` | `#define CVR_MAX_ENTRIES` |
| `CVR_MAX_LOOKUPS` | macro | `include/css_vars.h:26` | `#define CVR_MAX_LOOKUPS` |
| `CVR_NAME_MAX` | macro | `include/css_vars.h:19` | `#define CVR_NAME_MAX` |
| `CVR_VALUE_MAX` | macro | `include/css_vars.h:20` | `#define CVR_VALUE_MAX` |
| `FREEDOM_CSS_VARS_H` | macro | `include/css_vars.h:2` | `#define FREEDOM_CSS_VARS_H` |
| `cvr_chain` | struct | `include/css_vars.h:46` | `` |
| `cvr_collect_decls` | function | `include/css_vars.h:83` | `void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b);` |
| `cvr_count` | function | `include/css_vars.h:71` | `size_t cvr_count(const cvr_table *t);` |
| `cvr_ent` | struct | `include/css_vars.h:28` | `` |
| `cvr_free` | function | `include/css_vars.h:78` | `void cvr_free(cvr_table *t);` |
| `cvr_get` | function | `include/css_vars.h:69` | `const char *cvr_get(const cvr_table *t, const char *name, size_t nlen);` |
| `cvr_lookup` | function | `include/css_vars.h:96` | `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen);` |
| `cvr_reset` | function | `include/css_vars.h:75` | `void cvr_reset(cvr_table *t);` |
| `cvr_scope` | struct | `include/css_vars.h:54` | `` |
| `cvr_table` | struct | `include/css_vars.h:35` | `` |
| `declaration` | function | `include/css_vars.h:91` | `* then drops the whole declaration (CSS Variables 1: invalid at computed time). */ int cvr_resolve(const char *val, char` |
| `name` | function | `include/css_vars.h:62` | `* name (last declaration wins). Returns 1 when stored, 0 when dropped: a name that * is not "--" + at least one byte, a ` |
| `DU_MAX_ENCODED_LEN` | macro | `include/data_url.h:43` | `#define DU_MAX_ENCODED_LEN` |
| `FREEDOM_DATA_URL_H` | macro | `include/data_url.h:2` | `#define FREEDOM_DATA_URL_H` |
| `allocation` | function | `include/data_url.h:21` | `* * du_base64_payload does no allocation (it only slices the caller's url string);` |
| `closed` | function | `include/data_url.h:59` | `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/out/out_len == NULL (with b64_len != 0) =>` |
| `du_is_data_url` | function | `include/data_url.h:46` | `int du_is_data_url(const char *url);` |
| `du_status` | enum | `include/data_url.h:27` | `` |
| `FREEDOM_DISK_STORE_H` | macro | `include/disk_store.h:2` | `#define FREEDOM_DISK_STORE_H` |
| `ds_free` | function | `include/disk_store.h:47` | `void ds_free(uint8_t *buf, size_t len);` |
| `ds_status` | enum | `include/disk_store.h:25` | `` |
| `DOM_KIND_COMMENT` | macro | `include/dom.h:201` | `#define DOM_KIND_COMMENT` |
| `DOM_KIND_ELEMENT` | macro | `include/dom.h:199` | `#define DOM_KIND_ELEMENT` |
| `DOM_KIND_NONE` | macro | `include/dom.h:198` | `#define DOM_KIND_NONE` |
| `DOM_KIND_TEXT` | macro | `include/dom.h:200` | `#define DOM_KIND_TEXT` |
| `DOM_MAX_HANDLES` | macro | `include/dom.h:204` | `#define DOM_MAX_HANDLES` |
| `DOM_NODE_NONE` | macro | `include/dom.h:37` | `#define DOM_NODE_NONE` |
| `FREEDOM_DOM_H` | macro | `include/dom.h:2` | `#define FREEDOM_DOM_H` |
| `count` | function | `include/dom.h:59` | `* match count (which may exceed cap, so the caller can size a buffer). */ size_t dom_get_by_tag(const dom_index *idx, co` |
| `cycle` | function | `include/dom.h:164` | `* Rejects a cycle (child being an ancestor of parent). Invalid handle / self / cycle * => DOM_ERR_NULL_ARG. */ dom_statu` |
| `dom_attribute_names` | function | `include/dom.h:128` | `size_t dom_attribute_names(const dom_index *idx, dom_node_id node, const char **names, size_t *lens, size_t cap);` |
| `dom_document_position` | function | `include/dom.h:101` | `size_t dom_document_position(const dom_index *idx, dom_node_id node);` |
| `dom_document_title` | function | `include/dom.h:136` | `const char *dom_document_title(const dom_index *idx, size_t *len);` |
| `dom_free` | function | `include/dom.h:48` | `void dom_free(dom_index *idx);` |
| `dom_get_attribute` | function | `include/dom.h:121` | `const char *dom_get_attribute(const dom_index *idx, dom_node_id node, const char *name, size_t *len);` |
| `dom_get_by_class` | function | `include/dom.h:62` | `size_t dom_get_by_class(const dom_index *idx, const char *cls, dom_node_id *out, size_t cap);` |
| `dom_index` | type_alias | `include/dom.h:40` | `typedef struct dom_index dom_index;` |
| `dom_matches` | function | `include/dom.h:91` | `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector);` |
| `dom_node_count` | function | `include/dom.h:51` | `size_t dom_node_count(const dom_index *idx);` |
| `dom_node_id` | type_alias | `include/dom.h:34` | `typedef uint32_t dom_node_id;` |
| `dom_node_kind` | function | `include/dom.h:207` | `int dom_node_kind(const dom_index *idx, dom_node_id node);` |
| `dom_place` | enum | `include/dom.h:182` | `` |
| `dom_precedes` | function | `include/dom.h:104` | `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);` |
| `dom_status` | enum | `include/dom.h:26` | `` |
| `dom_tag_name` | function | `include/dom.h:118` | `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);` |
| `dom_text_content` | function | `include/dom.h:133` | `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len);` |
| `index` | function | `include/dom.h:223` | `* stays valid in the index (not freed). Invalid handle / not-a-child => DOM_ERR_NULL_ARG. */ dom_status dom_remove_child` |
| `length` | function | `include/dom.h:248` | `* length (no children => an owned empty string). Uses a chain of fixed-size * blocks internally so there is no hard cap ` |
| `parent` | function | `include/dom.h:191` | `* child of parent (for the *_REF places) or an invalid handle => DOM_ERR_NULL_ARG. */ dom_status dom_move_children(dom_i` |
| `DD_FIELD_MAX` | macro | `include/dom_debug.h:28` | `#define DD_FIELD_MAX` |
| `FREEDOM_DOM_DEBUG_H` | macro | `include/dom_debug.h:2` | `#define FREEDOM_DOM_DEBUG_H` |
| `dd_format` | function | `include/dom_debug.h:36` | `size_t dd_format(const rd_doc *doc, char *out, size_t cap);` |
| `dd_format_css` | function | `include/dom_debug.h:41` | `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap);` |
| `DL_ERR_OVERFLOW` | function | `include/download.h:56` | `* DL_ERR_OVERFLOW (out left empty). url/content_disposition NULL => absent. */ dl_status dl_pick_name(const char *url, c` |
| `DL_FALLBACK_NAME` | macro | `include/download.h:30` | `#define DL_FALLBACK_NAME` |
| `DL_MAX_BYTES` | macro | `include/download.h:31` | `#define DL_MAX_BYTES` |
| `DL_NAME_MAX` | macro | `include/download.h:29` | `#define DL_NAME_MAX` |
| `FREEDOM_DOWNLOAD_H` | macro | `include/download.h:2` | `#define FREEDOM_DOWNLOAD_H` |
| `basename` | function | `include/download.h:61` | `* sanitized basename (a name still containing '/' is rejected => DL_ERR_OVERFLOW, * so the path can never escape dir). T` |
| `dl_should_download` | function | `include/download.h:43` | `int dl_should_download(const char *content_type, const char *content_disposition);` |
| `dl_status` | enum | `include/download.h:33` | `` |
| `literal` | function | `include/download.h:47` | `* a static string literal (never freed). */ const char *dl_ext_for_type(const char *content_type);` |
| `FREEDOM_FLEX_LAYOUT_H` | macro | `include/flex_layout.h:2` | `#define FREEDOM_FLEX_LAYOUT_H` |
| `FX_AREA_MAX_CELLS` | macro | `include/flex_layout.h:110` | `#define FX_AREA_MAX_CELLS` |
| `FX_AREA_MAX_COLS` | macro | `include/flex_layout.h:109` | `#define FX_AREA_MAX_COLS` |
| `FX_AREA_MAX_ROWS` | macro | `include/flex_layout.h:108` | `#define FX_AREA_MAX_ROWS` |
| `FX_AREA_NAME_MAX` | macro | `include/flex_layout.h:111` | `#define FX_AREA_NAME_MAX` |
| `FX_ERR_NULL_ARG` | function | `include/flex_layout.h:200` | `* Returns FX_ERR_NULL_ARG (a required pointer NULL with n > 0), FX_ERR_RANGE * (negative h/avail, or n > FX_MAX_ITEMS);` |
| `FX_FLOAT_MIN_LINE` | macro | `include/flex_layout.h:180` | `#define FX_FLOAT_MIN_LINE` |
| `FX_MAUTO_BOTTOM` | macro | `include/flex_layout.h:308` | `#define FX_MAUTO_BOTTOM` |
| `FX_MAUTO_TOP` | macro | `include/flex_layout.h:307` | `#define FX_MAUTO_TOP` |
| `FX_MAX_COLUMNS` | macro | `include/flex_layout.h:240` | `#define FX_MAX_COLUMNS` |
| `FX_MAX_ITEMS` | macro | `include/flex_layout.h:28` | `#define FX_MAX_ITEMS` |
| `basis` | type_alias | `include/flex_layout.h:40` | `typedef struct fx_item { double basis;` |
| `bottom` | type_alias | `include/flex_layout.h:186` | `typedef struct fx_float_rect { double top, bottom;` |
| `cols` | type_alias | `include/flex_layout.h:116` | `typedef struct fx_area_map { int rows, cols;` |
| `fx_area_map` | struct | `include/flex_layout.h:116` | `` |
| `fx_auto_min_size` | function | `include/flex_layout.h:235` | `double fx_auto_min_size(double min_content, double basis, double author_min, int scroll_container);` |
| `fx_cross_offset` | function | `include/flex_layout.h:316` | `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r);` |
| `fx_float_rect` | struct | `include/flex_layout.h:186` | `` |
| `fx_grid_area_hash` | function | `include/flex_layout.h:125` | `unsigned fx_grid_area_hash(const char *name);` |
| `fx_grid_cell` | function | `include/flex_layout.h:74` | `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col);` |
| `fx_item` | struct | `include/flex_layout.h:40` | `` |
| `fx_justify` | enum | `include/flex_layout.h:30` | `` |
| `fx_justify_name` | function | `include/flex_layout.h:291` | `const char *fx_justify_name(fx_justify j);` |
| `fx_result` | struct | `include/flex_layout.h:48` | `` |
| `fx_status` | enum | `include/flex_layout.h:53` | `` |
| `height` | function | `include/flex_layout.h:297` | `* used height (h_out);` |
| `offset` | function | `include/flex_layout.h:143` | `* offset (from the content start, clamped to >= 0) to out_x[n]. The band does NOT wrap * (v1): an item that would overfl` |
| `out` | function | `include/flex_layout.h:62` | `* fx_result to out (caller-owned). n == 0 is a no-op (out may be NULL). */ fx_status fx_flex_line(const fx_item *items, ` |
| `pos` | type_alias | `include/flex_layout.h:48` | `typedef struct fx_result { double pos;` |
| `required` | function | `include/flex_layout.h:156` | `* out_row is required (NULL with n > 0 yields FX_ERR_NULL_ARG);` |
| `size` | function | `include/flex_layout.h:60` | `* content size (px);` |
| `space` | function | `include/flex_layout.h:206` | `* line order: positive free space (avail - sizes - gaps) is split equally among every * auto margin (auto_l[i]/auto_r[i]` |
| `widths` | function | `include/flex_layout.h:166` | `* the OUTER widths (width + ml + mr, clamped >= 0, so a negative margin narrows * the slot and a positive one widens it)` |
| `win` | function | `include/flex_layout.h:314` | `* margins win (both = centre, left only = end);` |
| `FM_BODY_MAX` | macro | `include/form.h:30` | `#define FM_BODY_MAX` |
| `FM_CONTENT_TYPE_URLENCODED` | variable | `include/form.h:68` | `extern const char FM_CONTENT_TYPE_URLENCODED[];` |
| `FM_MAX_FIELDS` | macro | `include/form.h:31` | `#define FM_MAX_FIELDS` |
| `FM_URL_MAX` | macro | `include/form.h:29` | `#define FM_URL_MAX` |
| `FREEDOM_FORM_H` | macro | `include/form.h:2` | `#define FREEDOM_FORM_H` |
| `fm_block_reason` | enum | `include/form.h:45` | `` |
| `fm_field` | struct | `include/form.h:37` | `` |
| `fm_kind` | enum | `include/form.h:39` | `` |
| `fm_method` | enum | `include/form.h:33` | `` |
| `fm_plan` | struct | `include/form.h:52` | `` |
| `fm_status` | enum | `include/form.h:61` | `` |
| `kind` | type_alias | `include/form.h:51` | `typedef struct fm_plan { fm_kind kind;` |
| `FREEDOM_FRAME_CLOCK_H` | macro | `include/frame_clock.h:2` | `#define FREEDOM_FRAME_CLOCK_H` |
| `active` | type_alias | `include/frame_clock.h:14` | `typedef struct fc_clock { int active;` |
| `fc_clock` | struct | `include/frame_clock.h:15` | `` |
| `fc_init` | function | `include/frame_clock.h:20` | `void fc_init(fc_clock *c);` |
| `fc_interval_ms` | function | `include/frame_clock.h:23` | `int fc_interval_ms(const fc_clock *c);` |
| `fc_needs_tick` | function | `include/frame_clock.h:22` | `int fc_needs_tick(const fc_clock *c);` |
| `fc_set_active` | function | `include/frame_clock.h:21` | `void fc_set_active(fc_clock *c, int active);` |
| `FB_MAX_ENTRIES` | macro | `include/freebug.h:56` | `#define FB_MAX_ENTRIES` |
| `FB_MAX_ENTRY_BYTES` | macro | `include/freebug.h:57` | `#define FB_MAX_ENTRY_BYTES` |
| `FB_MAX_FILE_BYTES` | macro | `include/freebug.h:62` | `#define FB_MAX_FILE_BYTES` |
| `FB_MAX_TOTAL_BYTES` | macro | `include/freebug.h:58` | `#define FB_MAX_TOTAL_BYTES` |
| `FREEDOM_FREEBUG_H` | macro | `include/freebug.h:2` | `#define FREEDOM_FREEBUG_H` |
| `copied` | function | `include/freebug.h:75` | `* copied (truncated to FB_MAX_FILE_BYTES);` |
| `fb_buffer` | struct | `include/freebug.h:46` | `` |
| `fb_buffer_at` | function | `include/freebug.h:92` | `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i);` |
| `fb_buffer_count` | function | `include/freebug.h:89` | `size_t fb_buffer_count(const fb_buffer *b);` |
| `fb_buffer_free` | function | `include/freebug.h:86` | `void fb_buffer_free(fb_buffer *b);` |
| `fb_buffer_init` | function | `include/freebug.h:65` | `void fb_buffer_init(fb_buffer *b);` |
| `fb_buffer_push_loc` | function | `include/freebug.h:78` | `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len, const char *file, int line, int col);` |
| `fb_buffer_reset` | function | `include/freebug.h:83` | `void fb_buffer_reset(fb_buffer *b);` |
| `fb_entry` | struct | `include/freebug.h:36` | `` |
| `fb_level` | enum | `include/freebug.h:24` | `` |
| `fb_level_name` | function | `include/freebug.h:96` | `const char *fb_level_name(int level);` |
| `level` | type_alias | `include/freebug.h:36` | `typedef struct fb_entry { int level;` |
| `truncated` | function | `include/freebug.h:69` | `* A message longer than FB_MAX_ENTRY_BYTES is stored truncated (not dropped). A * dropped push raises b->overflow and le` |
| `FC_FLEX_MEASURE_W` | macro | `include/freedom_config.h:44` | `#define FC_FLEX_MEASURE_W` |
| `FC_FLEX_MIN_MEASURE_W` | macro | `include/freedom_config.h:50` | `#define FC_FLEX_MIN_MEASURE_W` |
| `FC_FONT_CHAIN_MAX` | macro | `include/freedom_config.h:55` | `#define FC_FONT_CHAIN_MAX` |
| `FC_FONT_FALLBACK_PX` | macro | `include/freedom_config.h:65` | `#define FC_FONT_FALLBACK_PX` |
| `FC_HEADLESS_VIEW_H` | macro | `include/freedom_config.h:24` | `#define FC_HEADLESS_VIEW_H` |
| `FC_MAX_AUTHOR_CSS_BYTES` | macro | `include/freedom_config.h:77` | `#define FC_MAX_AUTHOR_CSS_BYTES` |
| `FC_MAX_BOXES` | macro | `include/freedom_config.h:60` | `#define FC_MAX_BOXES` |
| `FC_PNG_MARGIN` | macro | `include/freedom_config.h:33` | `#define FC_PNG_MARGIN` |
| `FC_PNG_MAX_H` | macro | `include/freedom_config.h:38` | `#define FC_PNG_MAX_H` |
| `FC_PNG_PAGE_W` | macro | `include/freedom_config.h:20` | `#define FC_PNG_PAGE_W` |
| `FC_TRUSTED_JS_BUDGET_MS` | macro | `include/freedom_config.h:29` | `#define FC_TRUSTED_JS_BUDGET_MS` |
| `FC_UI_FONT_SIZE` | macro | `include/freedom_config.h:69` | `#define FC_UI_FONT_SIZE` |
| `FREEDOM_CONFIG_H` | macro | `include/freedom_config.h:14` | `#define FREEDOM_CONFIG_H` |
| `FREEDOM_HLS_H` | macro | `include/hls.h:2` | `#define FREEDOM_HLS_H` |
| `hls_playlist` | struct | `include/hls.h:45` | `` |
| `hls_playlist_free` | function | `include/hls.h:74` | `void hls_playlist_free(hls_playlist *pl);` |
| `hls_segment` | struct | `include/hls.h:29` | `` |
| `hls_select_variant` | function | `include/hls.h:65` | `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h);` |
| `hls_status` | enum | `include/hls.h:21` | `` |
| `hls_variant` | struct | `include/hls.h:36` | `` |
| `resolved` | function | `include/hls.h:68` | `* Writes the absolute URL into resolved (bounded by resolved_sz). Returns the * written length, or 0 on failure. */ size` |
| `FREEDOM_HOSTBLOCK_H` | macro | `include/hostblock.h:2` | `#define FREEDOM_HOSTBLOCK_H` |
| `hb_count` | function | `include/hostblock.h:79` | `size_t hb_count(const hb_set *s, hb_list list);` |
| `hb_decision` | enum | `include/hostblock.h:37` | `` |
| `hb_free` | function | `include/hostblock.h:52` | `void hb_free(hb_set *s);` |
| `hb_is_allowlisted` | function | `include/hostblock.h:75` | `int hb_is_allowlisted(const hb_set *s, const char *host);` |
| `hb_list` | enum | `include/hostblock.h:32` | `` |
| `hb_new` | function | `include/hostblock.h:49` | `hb_set *hb_new(void);` |
| `hb_set` | type_alias | `include/hostblock.h:29` | `typedef struct hb_set hb_set;` |
| `hb_status` | enum | `include/hostblock.h:42` | `` |
| `walked` | function | `include/hostblock.h:65` | `* walked (the host, then without its first label, ...): any suffix on the allowlist * => HB_ALLOW (allow wins, covers su` |
| `FREEDOM_HOSTEDIT_H` | macro | `include/hostedit.h:2` | `#define FREEDOM_HOSTEDIT_H` |
| `HE_MAX_HOST` | macro | `include/hostedit.h:32` | `#define HE_MAX_HOST` |
| `he_status` | enum | `include/hostedit.h:24` | `` |
| `he_suggest` | function | `include/hostedit.h:55` | `int he_suggest(const char *text, const char *query, char results[][HE_MAX_HOST + 1], int max);` |
| `he_text_has_host` | function | `include/hostedit.h:46` | `int he_text_has_host(const char *text, const char *host);` |
| `FREEDOM_HTML_PARSE_H` | macro | `include/html_parse.h:2` | `#define FREEDOM_HTML_PARSE_H` |
| `HP_DEFAULT_MAX_BYTES` | macro | `include/html_parse.h:41` | `#define HP_DEFAULT_MAX_BYTES` |
| `HP_MAX_SCRIPTS` | macro | `include/html_parse.h:48` | `#define HP_MAX_SCRIPTS` |
| `HP_MAX_STYLESHEETS` | macro | `include/html_parse.h:115` | `#define HP_MAX_STYLESHEETS` |
| `cfg` | function | `include/html_parse.h:57` | `* policy in cfg (cfg == NULL => secure defaults). No script is ever executed. * html == NULL or out == NULL => HP_ERR_NU` |
| `dropped` | function | `include/html_parse.h:47` | `* dropped (not executed). */ #define HP_MAX_SCRIPTS ((size_t)4096) /* Returns a configuration with the secure defaults a` |
| `hp_config` | struct | `include/html_parse.h:32` | `` |
| `hp_document` | type_alias | `include/html_parse.h:39` | `typedef struct hp_document hp_document;` |
| `hp_document_free` | function | `include/html_parse.h:136` | `void hp_document_free(hp_document *doc);` |
| `hp_document_root` | function | `include/html_parse.h:142` | `const void *hp_document_root(const hp_document *doc);` |
| `hp_element_count` | function | `include/html_parse.h:63` | `size_t hp_element_count(const hp_document *doc);` |
| `hp_event_handler_count` | function | `include/html_parse.h:65` | `size_t hp_event_handler_count(const hp_document *doc);` |
| `hp_extract_stylesheet_hrefs` | function | `include/html_parse.h:127` | `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count);` |
| `hp_extract_text` | function | `include/html_parse.h:69` | `char *hp_extract_text(const hp_document *doc, size_t *out_len);` |
| `hp_free` | function | `include/html_parse.h:133` | `void hp_free(char *buf);` |
| `hp_free_scripts` | function | `include/html_parse.h:111` | `void hp_free_scripts(hp_script *scripts, size_t count);` |
| `hp_free_stylesheet_hrefs` | function | `include/html_parse.h:130` | `void hp_free_stylesheet_hrefs(char **hrefs, size_t count);` |
| `hp_get_title` | function | `include/html_parse.h:70` | `char *hp_get_title(const hp_document *doc, size_t *out_len);` |
| `hp_script` | struct | `include/html_parse.h:76` | `` |
| `hp_script_count` | function | `include/html_parse.h:64` | `size_t hp_script_count(const hp_document *doc);` |
| `hp_status` | enum | `include/html_parse.h:22` | `` |
| `max_bytes` | type_alias | `include/html_parse.h:31` | `typedef struct hp_config { size_t max_bytes;` |
| `modules` | function | `include/html_parse.h:94` | `* ES modules (import/export cannot run as a classic script), and template blocks * (text/x-jquery-tmpl, text/html, text/` |
| `src` | function | `include/html_parse.h:90` | `* carry their raw src (a <script src> with an inline body lists ONLY the src -- * browser rule: when src is present the ` |
| `FREEDOM_IMAGE_DECODE_H` | macro | `include/image_decode.h:2` | `#define FREEDOM_IMAGE_DECODE_H` |
| `IMG_MAX_DIM` | macro | `include/image_decode.h:65` | `#define IMG_MAX_DIM` |
| `IMG_MAX_PIXELS` | macro | `include/image_decode.h:66` | `#define IMG_MAX_PIXELS` |
| `decode` | function | `include/image_decode.h:92` | `* the declared dimensions BEFORE the full decode (anti-bomb), decodes to RGB and * expands to BGRA. Rejects non-JPEG (IM` |
| `guards` | function | `include/image_decode.h:25` | `* guards (in-memory source only, longjmp error manager so a bad stream never * calls exit(), dimension caps before decod` |
| `img_dimensions_ok` | function | `include/image_decode.h:78` | `int img_dimensions_ok(uint32_t w, uint32_t h);` |
| `img_format` | enum | `include/image_decode.h:33` | `` |
| `img_format_name` | function | `include/image_decode.h:124` | `const char *img_format_name(img_format f);` |
| `img_pixels` | struct | `include/image_decode.h:56` | `` |
| `img_pixels_free` | function | `include/image_decode.h:121` | `void img_pixels_free(img_pixels *p);` |
| `img_status` | enum | `include/image_decode.h:41` | `` |
| `inputs` | function | `include/image_decode.h:81` | `* Degenerate inputs (<= 0) yield (0,0). Pure. */ void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h, doub` |
| `width` | type_alias | `include/image_decode.h:56` | `typedef struct img_pixels { uint32_t width;` |
| `FREEDOM_IMPORT_MAP_H` | macro | `include/import_map.h:2` | `#define FREEDOM_IMPORT_MAP_H` |
| `IM_MAX_ENTRIES` | macro | `include/import_map.h:18` | `#define IM_MAX_ENTRIES` |
| `IM_MAX_SCOPES` | macro | `include/import_map.h:19` | `#define IM_MAX_SCOPES` |
| `IM_MAX_TEXT` | macro | `include/import_map.h:17` | `#define IM_MAX_TEXT` |
| `algorithm` | function | `include/import_map.h:13` | `* resolution algorithm (scopes, exact and prefix matches). URL resolution is the * caller's (the same resolver the modul` |
| `im_count` | function | `include/import_map.h:37` | `size_t im_count(const im_map *m);` |
| `im_free` | function | `include/import_map.h:40` | `void im_free(im_map *m);` |
| `im_map` | type_alias | `include/import_map.h:23` | `typedef struct im_map im_map;` |
| `im_resolve` | function | `include/import_map.h:33` | `int im_resolve(const im_map *m, const char *base, const char *specifier, im_url_fn resolve, void *ctx, char *out, size_t` |
| `map` | function | `include/import_map.h:28` | `* map (fail closed = no mapping). NULL only on OOM. */ im_map *im_parse(const char *json, size_t len, const char *doc_ur` |
| `FREEDOM_INTERP_H` | macro | `include/interp.h:2` | `#define FREEDOM_INTERP_H` |
| `IP_ITERATION_INFINITE` | macro | `include/interp.h:85` | `#define IP_ITERATION_INFINITE` |
| `IP_MAX_KEYFRAMES` | macro | `include/interp.h:68` | `#define IP_MAX_KEYFRAMES` |
| `ip_anim` | struct | `include/interp.h:101` | `` |
| `ip_anim_current` | function | `include/interp.h:131` | `double ip_anim_current(const ip_anim *a);` |
| `ip_anim_done` | function | `include/interp.h:134` | `int ip_anim_done(const ip_anim *a);` |
| `ip_anim_init` | function | `include/interp.h:121` | `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease, const ip_keyframe *kf, int n_kf, double duration_m` |
| `ip_anim_tick` | function | `include/interp.h:128` | `int ip_anim_tick(ip_anim *a, double dt_ms);` |
| `ip_direction` | enum | `include/interp.h:87` | `` |
| `ip_ease` | function | `include/interp.h:48` | `double ip_ease(double t, const ip_ease_fn *fn);` |
| `ip_ease_fn` | struct | `include/interp.h:38` | `` |
| `ip_easing` | enum | `include/interp.h:25` | `` |
| `ip_fill_mode` | enum | `include/interp.h:94` | `` |
| `ip_interp` | function | `include/interp.h:62` | `double ip_interp(ip_val_kind kind, double a, double b, double t);` |
| `ip_keyframe` | struct | `include/interp.h:70` | `` |
| `ip_kf_interp` | function | `include/interp.h:78` | `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf, int n_kf, double pct);` |
| `ip_lerp` | function | `include/interp.h:60` | `double ip_lerp(double a, double b, double t);` |
| `ip_lerp_color` | function | `include/interp.h:61` | `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t);` |
| `ip_val_kind` | enum | `include/interp.h:54` | `` |
| `kind` | type_alias | `include/interp.h:37` | `typedef struct ip_ease_fn { ip_easing kind;` |
| `pct` | type_alias | `include/interp.h:69` | `typedef struct ip_keyframe { double pct;` |
| `val_kind` | type_alias | `include/interp.h:100` | `typedef struct ip_anim { ip_val_kind val_kind;` |
| `FREEDOM_JS_DOM_H` | macro | `include/js_dom.h:2` | `#define FREEDOM_JS_DOM_H` |
| `JD_IFRAME_TRACK_MAX` | macro | `include/js_dom.h:40` | `#define JD_IFRAME_TRACK_MAX` |
| `URLs` | function | `include/js_dom.h:170` | `* video URLs (.m3u8 then .mp4 patterns), and creates <video> elements in the document for * any found. Does NOT re-proce` |
| `host` | function | `include/js_dom.h:123` | `* for a trusted host (allow.conf AND js.conf);` |
| `jd_click_state` | type_alias | `include/js_dom.h:35` | `typedef struct jd_click_state jd_click_state;` |
| `jd_click_state_free` | function | `include/js_dom.h:78` | `* jd_click_state_free(). Bound to one context via jd_install_events(). */ jd_click_state *jd_click_state_new(void);` |
| `jd_get_cookies` | function | `include/js_dom.h:134` | `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz);` |
| `jd_iframe_track` | struct | `include/js_dom.h:41` | `` |
| `jd_opaque` | struct | `include/js_dom.h:46` | `` |
| `jd_process_iframes` | function | `include/js_dom.h:163` | `* BEFORE jd_process_iframes() (so iframes are in the DOM for it to process). * ctx == NULL => JD_ERR_NULL_ARG. */ jd_sta` |
| `jd_status` | enum | `include/js_dom.h:25` | `` |
| `jd_video_from_scripts` | function | `include/js_dom.h:184` | `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts, const size_t *script_lens, size_t nscripts` |
| `opaque` | function | `include/js_dom.h:64` | `* the engine runtime opaque (unreachable from script);` |
| `out_status` | function | `include/js_dom.h:142` | `* On success returns 0 and sets *out_status (HTTP status, 0 if unknown), *out_body / * *out_body_len (response bytes, ma` |
| `preventDefault` | function | `include/js_dom.h:94` | `* preventDefault() was called, 1 if the default (form submission) should proceed. * ctx == NULL or no form found => 1 (f` |
| `processed` | type_alias | `include/js_dom.h:41` | `typedef struct jd_iframe_track { dom_node_id processed[JD_IFRAME_TRACK_MAX];` |
| `run` | function | `include/js_dom.h:87` | `* run (no handler registered, or handlers ran without calling preventDefault()), * and 0 if a handler called preventDefa` |
| `FREEDOM_JS_ENV_H` | macro | `include/js_env.h:2` | `#define FREEDOM_JS_ENV_H` |
| `je_status` | enum | `include/js_env.h:27` | `` |
| `poisoned` | function | `include/js_env.h:43` | `* readback is poisoned (deterministic within an origin, unlinkable across * sessions and across origins) to defeat readb` |
| `FREEDOM_JS_GEOM_H` | macro | `include/js_geom.h:2` | `#define FREEDOM_JS_GEOM_H` |
| `JG_COORD_MAX` | macro | `include/js_geom.h:26` | `#define JG_COORD_MAX` |
| `JG_HEADER_N` | macro | `include/js_geom.h:27` | `#define JG_HEADER_N` |
| `JG_MAX_DEPTH` | macro | `include/js_geom.h:25` | `#define JG_MAX_DEPTH` |
| `JG_MAX_RECTS` | macro | `include/js_geom.h:24` | `#define JG_MAX_RECTS` |
| `JG_RECT_N` | macro | `include/js_geom.h:28` | `#define JG_RECT_N` |
| `jg_add` | function | `include/js_geom.h:52` | `int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h);` |
| `jg_aggregate` | function | `include/js_geom.h:65` | `int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx);` |
| `jg_decode` | function | `include/js_geom.h:77` | `int jg_decode(const int32_t *in, size_t n, jg_table *out);` |
| `jg_encode` | function | `include/js_geom.h:71` | `int jg_encode(const jg_table *t, int32_t *out, size_t cap);` |
| `jg_find` | function | `include/js_geom.h:59` | `const jg_rect *jg_find(const jg_table *t, dom_node_id node);` |
| `jg_finish` | function | `include/js_geom.h:56` | `int jg_finish(jg_table *t);` |
| `jg_free` | function | `include/js_geom.h:47` | `void jg_free(jg_table *t);` |
| `jg_hash` | function | `include/js_geom.h:80` | `uint64_t jg_hash(const jg_table *t);` |
| `jg_init` | function | `include/js_geom.h:44` | `void jg_init(jg_table *t);` |
| `jg_rect` | struct | `include/js_geom.h:30` | `` |
| `jg_table` | struct | `include/js_geom.h:35` | `` |
| `jg_wire_len` | function | `include/js_geom.h:68` | `size_t jg_wire_len(const jg_table *t);` |
| `node` | type_alias | `include/js_geom.h:29` | `typedef struct jg_rect { dom_node_id node;` |
| `FREEDOM_JS_LOCATION_H` | macro | `include/js_location.h:2` | `#define FREEDOM_JS_LOCATION_H` |
| `JD_HIST_MAX` | macro | `include/js_location.h:31` | `#define JD_HIST_MAX` |
| `acting` | function | `include/js_location.h:49` | `* The caller MUST gate the raw target with ln_resolve before acting (Zero Trust). */ int jd_take_nav_request(js_context ` |
| `jd_pop_state` | function | `include/js_location.h:44` | `int jd_pop_state(js_context *ctx, int index);` |
| `jd_take_history` | function | `include/js_location.h:38` | `char *jd_take_history(js_context *ctx, int *go);` |
| `reads` | function | `include/js_location.h:25` | `* reads (NULL => only href is known, the rest fall back to stub defaults). Call after * jd_install, on the page's contex` |
| `FREEDOM_JS_POLICY_H` | macro | `include/js_policy.h:2` | `#define FREEDOM_JS_POLICY_H` |
| `allowlist` | function | `include/js_policy.h:34` | `* allowlist (e.g. hb_is_allowlisted over js.conf). Fails closed: an unknown mode * yields false. */ bool jsp_enabled(jsp` |
| `jsp_mode` | enum | `include/js_policy.h:27` | `` |
| `jsp_mode_str` | function | `include/js_policy.h:64` | `const char *jsp_mode_str(jsp_mode mode);` |
| `jsp_present_trusted` | function | `include/js_policy.h:54` | `bool jsp_present_trusted(int host_allowlisted);` |
| `jsp_trusted` | function | `include/js_policy.h:45` | `bool jsp_trusted(bool js_enabled, int host_allowlisted);` |
| `membership` | function | `include/js_policy.h:16` | `* membership (the allowlist itself is matched by the hostblock module, which * already covers subdomains). No I/O, no gl` |
| `FREEDOM_JS_SANDBOX_H` | macro | `include/js_sandbox.h:2` | `#define FREEDOM_JS_SANDBOX_H` |
| `JS_DEFAULT_MAX_SOURCE` | macro | `include/js_sandbox.h:66` | `#define JS_DEFAULT_MAX_SOURCE` |
| `JS_DEFAULT_MEM_LIMIT` | macro | `include/js_sandbox.h:67` | `#define JS_DEFAULT_MEM_LIMIT` |
| `JS_DEFAULT_STACK_LIMIT` | macro | `include/js_sandbox.h:68` | `#define JS_DEFAULT_STACK_LIMIT` |
| `JS_DEFAULT_TIME_BUDGET` | macro | `include/js_sandbox.h:69` | `#define JS_DEFAULT_TIME_BUDGET` |
| `JS_LOC_FILE_MAX` | macro | `include/js_sandbox.h:64` | `#define JS_LOC_FILE_MAX` |
| `JS_MODULE_BYTES_MAX` | macro | `include/js_sandbox.h:106` | `#define JS_MODULE_BYTES_MAX` |
| `JS_MODULE_MAX` | macro | `include/js_sandbox.h:105` | `#define JS_MODULE_MAX` |
| `JS_REALM_MAX` | macro | `include/js_sandbox.h:179` | `#define JS_REALM_MAX` |
| `handle` | function | `include/js_sandbox.h:162` | `* as an opaque handle (so this header stays free of backend types), or NULL. * Valid only while ctx is alive. Binding mo` |
| `js_context` | type_alias | `include/js_sandbox.h:47` | `typedef struct js_context js_context;` |
| `js_context_free` | function | `include/js_sandbox.h:86` | `void js_context_free(js_context *ctx);` |
| `js_limits` | struct | `include/js_sandbox.h:39` | `` |
| `js_loc_from_stack` | function | `include/js_sandbox.h:140` | `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap, int *line, int *col);` |
| `js_pump_jobs` | function | `include/js_sandbox.h:159` | `int js_pump_jobs(js_context *ctx, int max_jobs);` |
| `js_result` | struct | `include/js_sandbox.h:49` | `` |
| `js_result_free` | function | `include/js_sandbox.h:151` | `void js_result_free(js_result *res);` |
| `js_set_current_script` | function | `include/js_sandbox.h:171` | `void js_set_current_script(js_context *ctx, const char *src, const char *type);` |
| `js_set_module_host` | function | `include/js_sandbox.h:119` | `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve, js_module_fetch_fn fetch, void *host);` |
| `js_set_time_budget` | function | `include/js_sandbox.h:148` | `void js_set_time_budget(js_context *ctx, uint64_t budget_ms);` |
| `js_status` | enum | `include/js_sandbox.h:24` | `` |
| `loaded` | function | `include/js_sandbox.h:114` | `* NULL when it cannot be loaded (policy refusal, network error, not JavaScript). */ typedef char *(*js_module_fetch_fn)(` |
| `max_source_bytes` | type_alias | `include/js_sandbox.h:39` | `typedef struct js_limits { size_t max_source_bytes;` |
| `status` | type_alias | `include/js_sandbox.h:48` | `typedef struct js_result { js_status status;` |
| `FREEDOM_JS_TRUSTED_H` | macro | `include/js_trusted.h:2` | `#define FREEDOM_JS_TRUSTED_H` |
| `JT_WS_MAX` | macro | `include/js_trusted.h:35` | `#define JT_WS_MAX` |
| `JT_WS_MAX_BYTES` | macro | `include/js_trusted.h:37` | `#define JT_WS_MAX_BYTES` |
| `JT_WS_MAX_OPS` | macro | `include/js_trusted.h:36` | `#define JT_WS_MAX_OPS` |
| `jt_take_opens` | function | `include/js_trusted.h:31` | `char *jt_take_opens(js_context *ctx);` |
| `jt_take_storage` | function | `include/js_trusted.h:82` | `int jt_take_storage(js_context *ctx, char **out, size_t *len);` |
| `jt_take_ws` | function | `include/js_trusted.h:64` | `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap);` |
| `jt_ws_event` | function | `include/js_trusted.h:70` | `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len);` |
| `jt_ws_event_kind` | enum | `include/js_trusted.h:53` | `` |
| `jt_ws_kind` | enum | `include/js_trusted.h:39` | `` |
| `jt_ws_op` | struct | `include/js_trusted.h:46` | `` |
| `jt_ws_ops_free` | function | `include/js_trusted.h:65` | `void jt_ws_ops_free(jt_ws_op *ops, size_t n);` |
| `kind` | type_alias | `include/js_trusted.h:45` | `typedef struct jt_ws_op { int kind;` |
| `null` | function | `include/js_trusted.h:24` | `* noopener semantics: it returns null (no cross-window reference, so no same-origin * channel) and only records up to 4 ` |
| `parent` | function | `include/js_trusted.h:58` | `* socket: the object records operations for the parent (jt_take_ws). */ jd_status jt_enable_ws(js_context *ctx);` |
| `realm` | function | `include/js_trusted.h:85` | `* runs in its own realm (js_install_realms) of this context's runtime, inside the * same confined process and budget. ct` |
| `FREEDOM_LINK_NAV_H` | macro | `include/link_nav.h:2` | `#define FREEDOM_LINK_NAV_H` |
| `LN_MAX_FRAGMENT` | macro | `include/link_nav.h:38` | `#define LN_MAX_FRAGMENT` |
| `LN_MAX_TARGET` | macro | `include/link_nav.h:33` | `#define LN_MAX_TARGET` |
| `action` | type_alias | `include/link_nav.h:61` | `typedef struct ln_result { ln_action action;` |
| `dropped` | function | `include/link_nav.h:36` | `* A longer fragment is dropped (stored as "");` |
| `ln_action` | enum | `include/link_nav.h:40` | `` |
| `ln_block_reason` | enum | `include/link_nav.h:54` | `` |
| `ln_block_reason_text` | function | `include/link_nav.h:85` | `const char *ln_block_reason_text(ln_block_reason reason);` |
| `ln_result` | struct | `include/link_nav.h:62` | `` |
| `ln_status` | enum | `include/link_nav.h:70` | `` |
| `ln_target_kind` | enum | `include/link_nav.h:46` | `` |
| `FREEDOM_LOCAL_STORE_H` | macro | `include/local_store.h:2` | `#define FREEDOM_LOCAL_STORE_H` |
| `LS_HEADER_LEN` | macro | `include/local_store.h:30` | `#define LS_HEADER_LEN` |
| `LS_KEY_LEN` | macro | `include/local_store.h:26` | `#define LS_KEY_LEN` |
| `LS_MAX_PLAINTEXT` | macro | `include/local_store.h:32` | `#define LS_MAX_PLAINTEXT` |
| `LS_NONCE_LEN` | macro | `include/local_store.h:28` | `#define LS_NONCE_LEN` |
| `LS_OVERHEAD` | macro | `include/local_store.h:31` | `#define LS_OVERHEAD` |
| `LS_SALT_LEN` | macro | `include/local_store.h:27` | `#define LS_SALT_LEN` |
| `LS_TAG_LEN` | macro | `include/local_store.h:29` | `#define LS_TAG_LEN` |
| `ls_aead` | enum | `include/local_store.h:34` | `` |
| `ls_free` | function | `include/local_store.h:80` | `void ls_free(uint8_t *buf, size_t len);` |
| `ls_status` | enum | `include/local_store.h:39` | `` |
| `FREEDOM_MEDIA_DECODER_H` | macro | `include/media_decoder.h:2` | `#define FREEDOM_MEDIA_DECODER_H` |
| `MD_MAX_CATCHUP_READS` | macro | `include/media_decoder.h:65` | `#define MD_MAX_CATCHUP_READS` |
| `MD_MAX_SEGMENT_BYTES` | macro | `include/media_decoder.h:46` | `#define MD_MAX_SEGMENT_BYTES` |
| `MD_PACE_MAX_LAG_MS` | macro | `include/media_decoder.h:58` | `#define MD_PACE_MAX_LAG_MS` |
| `MD_PACE_MAX_STEP_MS` | macro | `include/media_decoder.h:62` | `#define MD_PACE_MAX_STEP_MS` |
| `epoch_ms` | type_alias | `include/media_decoder.h:66` | `typedef struct md_pacer { uint64_t epoch_ms;` |
| `md_cmd` | enum | `include/media_decoder.h:29` | `` |
| `md_pace_due_ms` | function | `include/media_decoder.h:79` | `static inline uint64_t md_pace_due_ms(md_pacer *p, uint64_t now_ms,
                             ...` |
| `md_pacer` | struct | `include/media_decoder.h:67` | `` |
| `md_resp` | enum | `include/media_decoder.h:38` | `` |
| `media_decoder_run` | function | `include/media_decoder.h:99` | `void media_decoder_run(int out_fd, int cmd_fd);` |
| `media_decoder_spawn` | function | `include/media_decoder.h:104` | `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd);` |
| `FREEDOM_NET_REALM_H` | macro | `include/net_realm.h:2` | `#define FREEDOM_NET_REALM_H` |
| `NR_ROUTE_BLOCKED` | function | `include/net_realm.h:57` | `* NR_ROUTE_BLOCKED (fail closed: never route what cannot be classified). A realm * whose proxy is not enabled => NR_ROUT` |
| `address` | function | `include/net_realm.h:62` | `* and encrypts by its address (the I2P destination / onion key), so http over it is * not a downgrade. Currently: NR_I2P` |
| `nr_config` | struct | `include/net_realm.h:42` | `` |
| `nr_realm` | enum | `include/net_realm.h:29` | `` |
| `nr_realm_allows_http` | function | `include/net_realm.h:66` | `int nr_realm_allows_http(nr_realm r);` |
| `nr_realm_name` | function | `include/net_realm.h:69` | `const char *nr_realm_name(nr_realm r);` |
| `nr_route` | enum | `include/net_realm.h:35` | `` |
| `nr_route_name` | function | `include/net_realm.h:70` | `const char *nr_route_name(nr_route r);` |
| `tor_enabled` | type_alias | `include/net_realm.h:41` | `typedef struct nr_config { int tor_enabled;` |
| `FREEDOM_OS_SANDBOX_H` | macro | `include/os_sandbox.h:2` | `#define FREEDOM_OS_SANDBOX_H` |
| `denied` | function | `include/os_sandbox.h:59` | `* request PROT_EXEC are denied (see os_prot_allowed). * Returns OS_ERR_UNSUPPORTED on platforms without seccomp-bpf x86_` |
| `flags` | function | `include/os_sandbox.h:39` | `* permission also depends on the protection flags (see os_prot_allowed / W^X). */ int os_policy_allows(long syscall_nr);` |
| `namespace` | function | `include/os_sandbox.h:75` | `* namespace (the unprivileged enabler), network (the worker never needs the * network -- the parent fetches and passes b` |
| `os_fs_access` | enum | `include/os_sandbox.h:102` | `` |
| `os_fs_rule` | struct | `include/os_sandbox.h:108` | `` |
| `os_landlock_abi` | function | `include/os_sandbox.h:114` | `int os_landlock_abi(void);` |
| `os_namespace_flags` | function | `include/os_sandbox.h:81` | `int os_namespace_flags(void);` |
| `os_policy_size` | function | `include/os_sandbox.h:43` | `size_t os_policy_size(void);` |
| `os_prot_allowed` | function | `include/os_sandbox.h:52` | `int os_prot_allowed(long syscall_nr, unsigned long prot);` |
| `os_status` | enum | `include/os_sandbox.h:21` | `` |
| `os_violation` | enum | `include/os_sandbox.h:30` | `` |
| `CSS_LEN_UNSET` | function | `include/page_view.h:479` | `* CSS_LEN_UNSET (unset) / CSS_LEN_AUTO. z_index is signed, or CSS_LEN_UNSET. v1 * paints only position:relative (an in-f` |
| `FREEDOM_PAGE_VIEW_H` | macro | `include/page_view.h:2` | `#define FREEDOM_PAGE_VIEW_H` |
| `PV_BG_URL_MAX` | macro | `include/page_view.h:66` | `#define PV_BG_URL_MAX` |
| `PV_CONT_DEPTH` | macro | `include/page_view.h:60` | `#define PV_CONT_DEPTH` |
| `PV_GRID_TRACKS` | macro | `include/page_view.h:55` | `#define PV_GRID_TRACKS` |
| `PV_LEN_AUTO` | macro | `include/page_view.h:51` | `#define PV_LEN_AUTO` |
| `PV_LEN_END` | macro | `include/page_view.h:52` | `#define PV_LEN_END` |
| `PV_LEN_UNSET` | macro | `include/page_view.h:50` | `#define PV_LEN_UNSET` |
| `PV_MAUTO_BOTTOM` | macro | `include/page_view.h:46` | `#define PV_MAUTO_BOTTOM` |
| `PV_MAUTO_LEFT` | macro | `include/page_view.h:43` | `#define PV_MAUTO_LEFT` |
| `PV_MAUTO_RIGHT` | macro | `include/page_view.h:44` | `#define PV_MAUTO_RIGHT` |
| `PV_MAUTO_TOP` | macro | `include/page_view.h:45` | `#define PV_MAUTO_TOP` |
| `ancestors` | function | `include/page_view.h:929` | `* itself by walking its ancestors (css_visibility, 0 = unset). * * An explicit value on the run WINS over the box stack ` |
| `bx_display` | function | `include/page_view.h:218` | `* bx_display (flex/grid);` |
| `cause` | function | `include/page_view.h:790` | `* cause (spec/css_drops.md). Builds no view and changes nothing -- it exists so * "what is this page's CSS losing?" is a` |
| `container` | function | `include/page_view.h:217` | `* cont_id groups runs of one container (-1 = none);` |
| `default` | function | `include/page_view.h:858` | `* structure is carried by default (not gated by caps.css). */ void pv_set_indent(pv_view *v, int indent);` |
| `form` | function | `include/page_view.h:821` | `* form (-1 if none);` |
| `itself` | function | `include/page_view.h:333` | `* by itself (bx_width_cap2);` |
| `kind` | type_alias | `include/page_view.h:118` | `typedef struct pv_run { pv_kind kind;` |
| `nonzero` | function | `include/page_view.h:757` | `* when nonzero (JS allowed for this page) the <noscript> subtree is suppressed. */ pv_status pv_build_ex(const hp_docume` |
| `order` | function | `include/page_view.h:282` | `* groups the runs of ONE floated element in document order (-1 = not in a float);` |
| `parent_id` | type_alias | `include/page_view.h:406` | `typedef struct pv_box_def { int parent_id;` |
| `parent_id` | type_alias | `include/page_view.h:695` | `typedef struct pv_cont_def { int parent_id;` |
| `policy` | function | `include/page_view.h:772` | `* TRUSTED parent under full network policy (spec/tab.md §8) -- page_view stays * pure and never fetches. The external te` |
| `pv_at` | function | `include/page_view.h:1070` | `const pv_run *pv_at(const pv_view *v, size_t i);` |
| `pv_box_at` | function | `include/page_view.h:1075` | `const pv_box_def *pv_box_at(const pv_view *v, size_t i);` |
| `pv_box_count` | function | `include/page_view.h:1074` | `size_t pv_box_count(const pv_view *v);` |
| `pv_box_def` | struct | `include/page_view.h:406` | `` |
| `pv_cont_at` | function | `include/page_view.h:1055` | `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i);` |
| `pv_cont_count` | function | `include/page_view.h:1054` | `size_t pv_cont_count(const pv_view *v);` |
| `pv_cont_def` | struct | `include/page_view.h:695` | `` |
| `pv_count` | function | `include/page_view.h:1069` | `size_t pv_count(const pv_view *v);` |
| `pv_form_method` | enum | `include/page_view.h:104` | `` |
| `pv_free` | function | `include/page_view.h:1066` | `void pv_free(pv_view *v);` |
| `pv_input_type` | enum | `include/page_view.h:84` | `` |
| `pv_kind` | enum | `include/page_view.h:68` | `` |
| `pv_new` | function | `include/page_view.h:802` | `pv_view *pv_new(void);` |
| `pv_run` | struct | `include/page_view.h:118` | `` |
| `pv_set_bgcolor` | function | `include/page_view.h:868` | `void pv_set_bgcolor(pv_view *v, int bg_rgb);` |
| `pv_set_block_id` | function | `include/page_view.h:1031` | `void pv_set_block_id(pv_view *v, int block_id);` |
| `pv_set_box` | function | `include/page_view.h:1010` | `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w, int box_center, int box_mt, int box_mb);` |
| `pv_set_box_maxw` | function | `include/page_view.h:1021` | `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct);` |
| `pv_set_box_pct` | function | `include/page_view.h:1016` | `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct, int box_mt_pct, int box_mb_pct);` |
| `pv_set_color` | function | `include/page_view.h:861` | `void pv_set_color(pv_view *v, int fg_rgb);` |
| `pv_set_cont_box` | function | `include/page_view.h:975` | `void pv_set_cont_box(pv_view *v, int cont_box_id);` |
| `pv_set_cont_item` | function | `include/page_view.h:991` | `void pv_set_cont_item(pv_view *v, int cont_item);` |
| `pv_set_emphasis` | function | `include/page_view.h:853` | `void pv_set_emphasis(pv_view *v, int bold, int italic);` |
| `pv_set_flex` | function | `include/page_view.h:984` | `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis, int flex_order, int flex_direction, int fle` |
| `pv_set_flex_mauto` | function | `include/page_view.h:987` | `void pv_set_flex_mauto(pv_view *v, int mauto);` |
| `pv_set_float` | function | `include/page_view.h:1000` | `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear, int float_ml, int float_ml_pct, int float_m` |
| `pv_set_grad_text` | function | `include/page_view.h:945` | `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4);` |
| `pv_set_grid` | function | `include/page_view.h:976` | `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span);` |
| `pv_set_grid_area` | function | `include/page_view.h:965` | `void pv_set_grid_area(pv_view *v, int row_start, int col_start);` |
| `pv_set_grid_rows` | function | `include/page_view.h:966` | `void pv_set_grid_rows(pv_view *v, int grid_rows);` |
| `pv_set_input_checked` | function | `include/page_view.h:1059` | `void pv_set_input_checked(pv_view *v, int checked);` |
| `pv_set_input_select_opts` | function | `include/page_view.h:1063` | `void pv_set_input_select_opts(pv_view *v, const char *select_opts);` |
| `pv_set_node_id` | function | `include/page_view.h:1026` | `void pv_set_node_id(pv_view *v, dom_node_id node_id);` |
| `pv_set_oof` | function | `include/page_view.h:1039` | `void pv_set_oof(pv_view *v, int oof);` |
| `pv_set_own_box` | function | `include/page_view.h:1035` | `void pv_set_own_box(pv_view *v, int box_id);` |
| `pv_set_row_span` | function | `include/page_view.h:961` | `void pv_set_row_span(pv_view *v, int row_span);` |
| `pv_set_text_ext` | function | `include/page_view.h:939` | `void pv_set_text_ext(pv_view *v, const pv_text_ext *e);` |
| `pv_set_text_style` | function | `include/page_view.h:877` | `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs, int line_scale, int text_decoration);` |
| `pv_set_ua_tag` | function | `include/page_view.h:971` | `void pv_set_ua_tag(pv_view *v, int ua_tag);` |
| `pv_status` | enum | `include/page_view.h:34` | `` |
| `pv_text_ext` | struct | `include/page_view.h:893` | `` |
| `pv_text_ext_reset` | function | `include/page_view.h:924` | `void pv_text_ext_reset(pv_text_ext *e);` |
| `pv_view` | struct | `include/page_view.h:732` | `` |
| `resolved` | function | `include/page_view.h:764` | `* author CSS is still resolved (the presentation layer decides whether to apply it). * pv_build_ex is pv_build_full with` |
| `run` | function | `include/page_view.h:948` | `* run (cont_id, the bx_display, the parsed gap/justify/cols, plus flex-wrap/ * row-gap/align-items). No-op on an empty o` |
| `scale` | function | `include/page_view.h:554` | `* scale(1)) and rotate in whole degrees (transform_rotate);` |
| `word_spacing` | type_alias | `include/page_view.h:893` | `typedef struct pv_text_ext { int font_family, text_transform, letter_spacing, word_spacing;` |
| `FREEDOM_PDF_EXPORT_H` | macro | `include/pdf_export.h:2` | `#define FREEDOM_PDF_EXPORT_H` |
| `PE_EXT` | macro | `include/pdf_export.h:29` | `#define PE_EXT` |
| `PE_EXT_PNG` | macro | `include/pdf_export.h:30` | `#define PE_EXT_PNG` |
| `PE_FALLBACK_NAME` | macro | `include/pdf_export.h:31` | `#define PE_FALLBACK_NAME` |
| `PE_NAME_MAX` | macro | `include/pdf_export.h:28` | `#define PE_NAME_MAX` |
| `fallback` | function | `include/pdf_export.h:46` | `* fallback (PE_ERR_OVERFLOW, out left empty). title == NULL is treated as empty. * Does NOT append the extension (that i` |
| `literal` | function | `include/pdf_export.h:52` | `* trusted literal (e.g. PE_EXT / PE_EXT_PNG);` |
| `pe_paginate` | function | `include/pdf_export.h:70` | `size_t pe_paginate(const double *tops, const double *heights, size_t n, double page_h, int *out_page, double *out_page_y` |
| `pe_status` | enum | `include/pdf_export.h:33` | `` |
| `trusted` | function | `include/pdf_export.h:51` | `* dir is trusted (chosen by the app from XDG/$HOME);` |
| `FREEDOM_PERF_TRACE_H` | macro | `include/perf_trace.h:2` | `#define FREEDOM_PERF_TRACE_H` |
| `PT_MAX_SAMPLES` | macro | `include/perf_trace.h:32` | `#define PT_MAX_SAMPLES` |
| `order` | enum | `include/perf_trace.h:71` | `` |
| `pt_count` | function | `include/perf_trace.h:57` | `size_t pt_count(const pt_trace *t, pt_stage stage);` |
| `pt_elapsed_us` | function | `include/perf_trace.h:50` | `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us);` |
| `pt_format` | function | `include/perf_trace.h:76` | `size_t pt_format(const pt_trace *t, char *buf, size_t cap);` |
| `pt_init` | function | `include/perf_trace.h:46` | `void pt_init(pt_trace *t);` |
| `pt_last_us` | function | `include/perf_trace.h:60` | `uint64_t pt_last_us(const pt_trace *t, pt_stage stage);` |
| `pt_max_us` | function | `include/perf_trace.h:64` | `uint64_t pt_max_us(const pt_trace *t, pt_stage stage);` |
| `pt_median_us` | function | `include/perf_trace.h:65` | `uint64_t pt_median_us(const pt_trace *t, pt_stage stage);` |
| `pt_min_us` | function | `include/perf_trace.h:63` | `uint64_t pt_min_us(const pt_trace *t, pt_stage stage);` |
| `pt_record` | function | `include/perf_trace.h:54` | `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us);` |
| `pt_stage_name` | function | `include/perf_trace.h:69` | `const char *pt_stage_name(pt_stage stage);` |
| `pt_stage_stats` | struct | `include/perf_trace.h:34` | `` |
| `pt_trace` | struct | `include/perf_trace.h:41` | `` |
| `samples` | type_alias | `include/perf_trace.h:33` | `typedef struct pt_stage_stats { uint64_t samples[PT_MAX_SAMPLES];` |
| `stage` | type_alias | `include/perf_trace.h:40` | `typedef struct pt_trace { pt_stage_stats stage[PT_STAGE_COUNT];` |
| `FREEDOM_PREFETCH_H` | macro | `include/prefetch.h:2` | `#define FREEDOM_PREFETCH_H` |
| `PF_MAX_REFS` | macro | `include/prefetch.h:47` | `#define PF_MAX_REFS` |
| `PF_MAX_THREADS` | macro | `include/prefetch.h:48` | `#define PF_MAX_THREADS` |
| `fetch` | function | `include/prefetch.h:102` | `* claiming jobs and running fetch(ctx, "GET", url, ...). Returns 0 on success or * -1 when no thread could start (the ca` |
| `inner` | type_alias | `include/prefetch.h:129` | `typedef struct pf_gated_fetch { pf_fetch_fn inner;` |
| `jobs` | type_alias | `include/prefetch.h:86` | `typedef struct pf_pool { pf_job jobs[PF_MAX_REFS];` |
| `kind` | type_alias | `include/prefetch.h:42` | `typedef struct pf_ref { pf_kind kind;` |
| `pf_gated_fetch` | struct | `include/prefetch.h:129` | `` |
| `pf_job` | struct | `include/prefetch.h:77` | `` |
| `pf_job_state` | enum | `include/prefetch.h:70` | `` |
| `pf_kind` | enum | `include/prefetch.h:35` | `` |
| `pf_list` | struct | `include/prefetch.h:50` | `` |
| `pf_list_free` | function | `include/prefetch.h:60` | `void pf_list_free(pf_list *l);` |
| `pf_pool` | struct | `include/prefetch.h:87` | `` |
| `pf_pool_finish` | function | `include/prefetch.h:121` | `void pf_pool_finish(pf_pool *p);` |
| `pf_pool_take` | function | `include/prefetch.h:115` | `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status, char **body, size_t *len, char **ctype);` |
| `pf_pooled_fetch` | function | `include/prefetch.h:135` | `int pf_pooled_fetch(void *vctx, const char *method, const char *url, const char *body, size_t body_len, int *out_status,` |
| `pf_ref` | struct | `include/prefetch.h:42` | `` |
| `pf_scan` | function | `include/prefetch.h:59` | `int pf_scan(const char *html, size_t len, pf_list *out);` |
| `pool` | function | `include/prefetch.h:125` | `* whose URL is pooled is served from the pool (a failed prefetch propagates the * failure -- never refetched);` |
| `refs` | type_alias | `include/prefetch.h:49` | `typedef struct pf_list { pf_ref refs[PF_MAX_REFS];` |
| `FREEDOM_PREFS_H` | macro | `include/prefs.h:2` | `#define FREEDOM_PREFS_H` |
| `PREFS_MAX_BOOKMARKS` | macro | `include/prefs.h:29` | `#define PREFS_MAX_BOOKMARKS` |
| `PREFS_MAX_HISTORY` | macro | `include/prefs.h:30` | `#define PREFS_MAX_HISTORY` |
| `PREFS_MAX_TEXT` | macro | `include/prefs.h:31` | `#define PREFS_MAX_TEXT` |
| `PREFS_MAX_TITLE` | macro | `include/prefs.h:28` | `#define PREFS_MAX_TITLE` |
| `PREFS_MAX_URL` | macro | `include/prefs.h:27` | `#define PREFS_MAX_URL` |
| `PREFS_PAGE_HISTORY` | macro | `include/prefs.h:34` | `#define PREFS_PAGE_HISTORY` |
| `PREFS_VERSION` | macro | `include/prefs.h:26` | `#define PREFS_VERSION` |
| `anyway` | function | `include/prefs.h:105` | `* page is rendered by the normal confined pipeline anyway (defence in depth). * *out is owned (free());` |
| `free` | function | `include/prefs.h:71` | `* free(). */ prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len);` |
| `prefs_bookmark_index` | function | `include/prefs.h:81` | `int prefs_bookmark_index(const prefs_state *p, const char *url);` |
| `prefs_entry` | struct | `include/prefs.h:45` | `` |
| `prefs_free` | function | `include/prefs.h:68` | `void prefs_free(prefs_state *p);` |
| `prefs_init` | function | `include/prefs.h:65` | `void prefs_init(prefs_state *p);` |
| `prefs_state` | struct | `include/prefs.h:50` | `` |
| `prefs_status` | enum | `include/prefs.h:36` | `` |
| `prefs_suggest` | function | `include/prefs.h:100` | `int prefs_suggest(const prefs_state *p, const char *query, char *out, size_t row_len, int max_rows);` |
| `theme_mode` | type_alias | `include/prefs.h:49` | `typedef struct prefs_state { int theme_mode;` |
| `FREEDOM_PROFILE_H` | macro | `include/profile.h:2` | `#define FREEDOM_PROFILE_H` |
| `PROFILE_KEY_FILE` | macro | `include/profile.h:32` | `#define PROFILE_KEY_FILE` |
| `PROFILE_PREFS_FILE` | macro | `include/profile.h:33` | `#define PROFILE_PREFS_FILE` |
| `absent` | function | `include/profile.h:53` | `* the keyfile when absent (0600, atomic write);` |
| `closed` | function | `include/profile.h:54` | `* wrong size fails closed (PROFILE_ERR_KEY, never overwritten). Derives the * AEAD key (Argon2id, per-device salt) and m` |
| `dir` | type_alias | `include/profile.h:45` | `typedef struct profile_ctx { char dir[1024];` |
| `profile_close` | function | `include/profile.h:67` | `void profile_close(profile_ctx *ctx);` |
| `profile_ctx` | struct | `include/profile.h:46` | `` |
| `profile_status` | enum | `include/profile.h:35` | `` |
| `FREEDOM_PSL_DATA_H` | macro | `include/psl_data.h:2` | `#define FREEDOM_PSL_DATA_H` |
| `psl_exceptions` | variable | `include/psl_data.h:25` | `extern const char *const psl_exceptions[];` |
| `psl_exceptions_n` | variable | `include/psl_data.h:26` | `extern const size_t psl_exceptions_n;` |
| `psl_rules` | variable | `include/psl_data.h:21` | `extern const char *const psl_rules[];` |
| `psl_rules_n` | variable | `include/psl_data.h:22` | `extern const size_t psl_rules_n;` |
| `psl_wildcards` | variable | `include/psl_data.h:23` | `extern const char *const psl_wildcards[];` |
| `psl_wildcards_n` | variable | `include/psl_data.h:24` | `extern const size_t psl_wildcards_n;` |
| `FREEDOM_RENDER_DOC_H` | macro | `include/render_doc.h:2` | `#define FREEDOM_RENDER_DOC_H` |
| `IMG_FAIL_OK` | function | `include/render_doc.h:324` | `* IMG_FAIL_OK (not a failure) or the reason is unknown. */ const char *rd_image_fail_label(img_fail_reason reason);` |
| `RD_IMAGE` | function | `include/render_doc.h:59` | `* RD_IMAGE (image src) and RD_INPUT (the owning form's action);` |
| `decision` | function | `include/render_doc.h:318` | `* decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never * NULL. */ const char *rd_image_label(rdp_i` |
| `default` | function | `include/render_doc.h:142` | `* default (layout is structure, not author styling, and leaks nothing to the * network) so the presentation layer can la` |
| `form` | function | `include/render_doc.h:63` | `* form (-1 = none);` |
| `img_fail_reason` | enum | `include/render_doc.h:34` | `` |
| `kind` | type_alias | `include/render_doc.h:64` | `typedef struct rd_block { rd_kind kind;` |
| `list` | function | `include/render_doc.h:18` | `* inert display list (page_view) and the presentation orchestrator (the GUI and * the --headless writer). It decides WHA` |
| `rd_at` | function | `include/render_doc.h:293` | `const rd_block *rd_at(const rd_doc *d, size_t i);` |
| `rd_block` | struct | `include/render_doc.h:64` | `` |
| `rd_block_tag` | function | `include/render_doc.h:315` | `const char *rd_block_tag(const rd_block *b);` |
| `rd_box_at` | function | `include/render_doc.h:298` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i);` |
| `rd_box_count` | function | `include/render_doc.h:297` | `size_t rd_box_count(const rd_doc *d);` |
| `rd_cont_at` | function | `include/render_doc.h:303` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i);` |
| `rd_cont_count` | function | `include/render_doc.h:302` | `size_t rd_cont_count(const rd_doc *d);` |
| `rd_count` | function | `include/render_doc.h:292` | `size_t rd_count(const rd_doc *d);` |
| `rd_doc` | struct | `include/render_doc.h:244` | `` |
| `rd_free` | function | `include/render_doc.h:289` | `void rd_free(rd_doc *d);` |
| `rd_input_invisible` | function | `include/render_doc.h:334` | `int rd_input_invisible(int input_type);` |
| `rd_input_label` | function | `include/render_doc.h:329` | `const char *rd_input_label(int input_type);` |
| `rd_kind` | enum | `include/render_doc.h:42` | `` |
| `rd_kind_name` | function | `include/render_doc.h:307` | `const char *rd_kind_name(rd_kind k);` |
| `rd_status` | enum | `include/render_doc.h:270` | `` |
| `rdp_images_warning` | function | `include/render_doc.h:279` | `* rdp_images_warning() is prepended so the user is always told. Each image * becomes an RD_IMAGE block whose img_decisio` |
| `to` | function | `include/render_doc.h:230` | `* belongs to (-1 = none);` |
| `FREEDOM_RENDER_POLICY_H` | macro | `include/render_policy.h:2` | `#define FREEDOM_RENDER_POLICY_H` |
| `RDP_TRACKER_MAX_DIM` | macro | `include/render_policy.h:27` | `#define RDP_TRACKER_MAX_DIM` |
| `images` | type_alias | `include/render_policy.h:32` | `typedef struct rdp_caps { bool images;` |
| `rdp_caps` | struct | `include/render_policy.h:32` | `` |
| `rdp_images_warning` | function | `include/render_policy.h:69` | `const char *rdp_images_warning(void);` |
| `rdp_img_decision` | enum | `include/render_policy.h:39` | `` |
| `rdp_img_reason` | function | `include/render_policy.h:66` | `const char *rdp_img_reason(rdp_img_decision d);` |
| `rdp_is_tracking_pixel` | function | `include/render_policy.h:53` | `int rdp_is_tracking_pixel(int w, int h);` |
| `size` | function | `include/render_policy.h:56` | `* announced size (e.g. <img width height>);` |
| `FREEDOM_RENDERER_H` | macro | `include/renderer.h:2` | `#define FREEDOM_RENDERER_H` |
| `RD_MAX_FIELD` | macro | `include/renderer.h:38` | `#define RD_MAX_FIELD` |
| `RD_MAX_INPUT` | macro | `include/renderer.h:37` | `#define RD_MAX_INPUT` |
| `rd_result` | struct | `include/renderer.h:29` | `` |
| `rd_result_free` | function | `include/renderer.h:46` | `void rd_result_free(rd_result *out);` |
| `rd_status` | enum | `include/renderer.h:20` | `` |
| `status` | type_alias | `include/renderer.h:28` | `typedef struct rd_result { rd_status status;` |
| `FREEDOM_REQUEST_POLICY_H` | macro | `include/request_policy.h:2` | `#define FREEDOM_REQUEST_POLICY_H` |
| `rp_decision` | enum | `include/request_policy.h:21` | `` |
| `rp_host_of` | function | `include/request_policy.h:30` | `int rp_host_of(const char *url, char *out, size_t out_size);` |
| `rp_same_site` | function | `include/request_policy.h:37` | `int rp_same_site(const char *top_level_url, const char *request_url);` |
| `rp_site_of` | function | `include/request_policy.h:34` | `int rp_site_of(const char *host, char *out, size_t out_size);` |
| `EXCLUDED` | function | `include/secure_fetch.h:210` | `* cookies are EXCLUDED (network-only, never exposed to JS) and expired cookies skipped. * Only for a TRUSTED host (the c` |
| `FREEDOM_SECURE_FETCH_H` | macro | `include/secure_fetch.h:2` | `#define FREEDOM_SECURE_FETCH_H` |
| `SF_CONNECT_TIMEOUT_MS` | macro | `include/secure_fetch.h:193` | `#define SF_CONNECT_TIMEOUT_MS` |
| `SF_DEFAULT_KEX_GROUPS` | macro | `include/secure_fetch.h:143` | `#define SF_DEFAULT_KEX_GROUPS` |
| `SF_DEFAULT_MAX_BODY` | macro | `include/secure_fetch.h:169` | `#define SF_DEFAULT_MAX_BODY` |
| `SF_DEFAULT_MAX_REDIRECTS` | macro | `include/secure_fetch.h:195` | `#define SF_DEFAULT_MAX_REDIRECTS` |
| `SF_DEFAULT_TIMEOUT_MS` | macro | `include/secure_fetch.h:170` | `#define SF_DEFAULT_TIMEOUT_MS` |
| `SF_DEFAULT_USER_AGENT` | macro | `include/secure_fetch.h:168` | `#define SF_DEFAULT_USER_AGENT` |
| `SF_IMPERSONATE_KEX_GROUPS` | macro | `include/secure_fetch.h:152` | `#define SF_IMPERSONATE_KEX_GROUPS` |
| `SF_IMPERSONATE_TLS12_CIPHERS` | macro | `include/secure_fetch.h:157` | `#define SF_IMPERSONATE_TLS12_CIPHERS` |
| `SF_IMPERSONATE_TLS13_CIPHERS` | macro | `include/secure_fetch.h:153` | `#define SF_IMPERSONATE_TLS13_CIPHERS` |
| `SF_MAX_URL` | macro | `include/secure_fetch.h:196` | `#define SF_MAX_URL` |
| `SF_SUBRESOURCE_TIMEOUT_MS` | macro | `include/secure_fetch.h:194` | `#define SF_SUBRESOURCE_TIMEOUT_MS` |
| `SF_WS_MAX_MESSAGE` | macro | `include/secure_fetch.h:292` | `#define SF_WS_MAX_MESSAGE` |
| `bits` | function | `include/secure_fetch.h:310` | `* *flags receives CURLWS_* bits (text/binary/close/cont);` |
| `connection` | function | `include/secure_fetch.h:324` | `* on each connection (Zero Trust). Each target is re-validated and a downgrade * to http:// is refused. Exceeding max_re` |
| `policy` | type_alias | `include/secure_fetch.h:74` | `typedef struct sf_config { sf_policy policy;` |
| `sf_chain_info` | struct | `include/secure_fetch.h:60` | `` |
| `sf_config` | struct | `include/secure_fetch.h:75` | `` |
| `sf_cookie_line_matches` | function | `include/secure_fetch.h:222` | `int sf_cookie_line_matches(const char *line, const char *host, const char *path, long now, char *out, size_t outsz);` |
| `sf_cookie_put` | function | `include/secure_fetch.h:217` | `void sf_cookie_put(const char *url, const char *namevalue);` |
| `sf_get` | function | `include/secure_fetch.h:333` | `* sf_get (Zero Trust): an insecure POST is not representable. Does not follow * redirects (the caller inspects out->http` |
| `sf_global_init` | function | `include/secure_fetch.h:204` | `void sf_global_init(void);` |
| `sf_impersonate_kex_groups` | function | `include/secure_fetch.h:235` | `const char *sf_impersonate_kex_groups(void);` |
| `sf_impersonate_tls13_ciphers` | function | `include/secure_fetch.h:236` | `const char *sf_impersonate_tls13_ciphers(void);` |
| `sf_is_redirect_code` | function | `include/secure_fetch.h:267` | `int sf_is_redirect_code(long http_code);` |
| `sf_policy` | enum | `include/secure_fetch.h:40` | `` |
| `sf_proxy_type` | enum | `include/secure_fetch.h:69` | `` |
| `sf_response` | struct | `include/secure_fetch.h:117` | `` |
| `sf_response_free` | function | `include/secure_fetch.h:344` | `void sf_response_free(sf_response *resp);` |
| `sf_status` | enum | `include/secure_fetch.h:23` | `` |
| `sf_user_agent_or_default` | function | `include/secure_fetch.h:231` | `const char *sf_user_agent_or_default(const char *ua);` |
| `sf_ws` | type_alias | `include/secure_fetch.h:293` | `typedef struct sf_ws sf_ws;` |
| `sf_ws_close` | function | `include/secure_fetch.h:320` | `void sf_ws_close(sf_ws *ws);` |
| `sf_ws_fd` | function | `include/secure_fetch.h:317` | `int sf_ws_fd(const sf_ws *ws);` |
| `skipped` | function | `include/secure_fetch.h:256` | `* skipped (a classical key exchange is accepted);` |
| `status` | type_alias | `include/secure_fetch.h:116` | `typedef struct sf_response { sf_status status;` |
| `validators` | function | `include/secure_fetch.h:17` | `* The security logic lives in pure validators (no I/O);` |
| `FREEDOM_SVG_PAINT_H` | macro | `include/svg_paint.h:2` | `#define FREEDOM_SVG_PAINT_H` |
| `svp_draw` | function | `include/svg_paint.h:31` | `void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, double h, int current_rgb);` |
| `FREEDOM_SVG_RENDER_H` | macro | `include/svg_render.h:2` | `#define FREEDOM_SVG_RENDER_H` |
| `SV_DEFAULT_H` | macro | `include/svg_render.h:42` | `#define SV_DEFAULT_H` |
| `SV_DEFAULT_W` | macro | `include/svg_render.h:41` | `#define SV_DEFAULT_W` |
| `SV_MAX_DEPTH` | macro | `include/svg_render.h:35` | `#define SV_MAX_DEPTH` |
| `SV_MAX_INPUT` | macro | `include/svg_render.h:37` | `#define SV_MAX_INPUT` |
| `SV_MAX_POINTS` | macro | `include/svg_render.h:33` | `#define SV_MAX_POINTS` |
| `SV_MAX_SEGS` | macro | `include/svg_render.h:34` | `#define SV_MAX_SEGS` |
| `SV_MAX_SHAPES` | macro | `include/svg_render.h:32` | `#define SV_MAX_SHAPES` |
| `SV_TEXT_MAX` | macro | `include/svg_render.h:36` | `#define SV_TEXT_MAX` |
| `height` | type_alias | `include/svg_render.h:104` | `typedef struct sv_image { double width, height;` |
| `kind` | type_alias | `include/svg_render.h:75` | `typedef struct sv_shape { int kind;` |
| `sv_fit` | function | `include/svg_render.h:131` | `void sv_fit(const sv_image *img, double dw, double dh, double *scale, double *off_x, double *off_y);` |
| `sv_image` | struct | `include/svg_render.h:104` | `` |
| `sv_seg` | struct | `include/svg_render.h:65` | `` |
| `sv_shape` | struct | `include/svg_render.h:75` | `` |
| `sv_shape_kind` | enum | `include/svg_render.h:44` | `` |
| `sv_status` | enum | `include/svg_render.h:25` | `` |
| `sv_verb` | enum | `include/svg_render.h:58` | `` |
| `verb` | type_alias | `include/svg_render.h:64` | `typedef struct sv_seg { int verb;` |
| `FREEDOM_TAB_H` | macro | `include/tab.h:2` | `#define FREEDOM_TAB_H` |
| `TAB_MAX_INPUT` | macro | `include/tab.h:148` | `#define TAB_MAX_INPUT` |
| `decode` | function | `include/tab.h:325` | `* could not decode (caller shows the placeholder), which is not a transport error. * TAB_ERR_* is reserved for transport` |
| `exclusively` | function | `include/tab.h:209` | `* exclusively (tab_subreq_permitted). Default 0: zero fetches, Privacy by Default. */ void tab_set_css_allowed(tab *t, i` |
| `granted` | function | `include/tab.h:299` | `* granted (allow.conf AND js.conf);` |
| `jar` | function | `include/tab.h:194` | `* the trusted parent read from its ephemeral network jar (sf_cookie_header_for). Only * meaningful for a trusted host (a` |
| `kind` | type_alias | `include/tab.h:67` | `typedef struct tab_ws_op { int kind;` |
| `origin` | function | `include/tab.h:201` | `* page origin (web_storage snapshot, copied). Used only when the load is trusted * (net granted);` |
| `out_status` | function | `include/tab.h:175` | `* On success return 0 and set *out_status (HTTP status), *out_body / *out_body_len * (malloc'd response bytes, tab frees` |
| `popstate` | function | `include/tab.h:306` | `* popstate (+ hashchange) and re-derives the view like a click. */ tab_status tab_popstate(tab *t, int index, tab_page *` |
| `replace` | type_alias | `include/tab.h:53` | `typedef struct tab_hist_op { int replace;` |
| `returned` | function | `include/tab.h:300` | `* returned (the page keeps its zeros). The worker re-checks the same condition. * g must be finished (jg_finish). */ tab` |
| `string` | function | `include/tab.h:250` | `* event_type is a JS event type string (e.g. "keydown", "input", "change"). * key is the keyboard key value (may be NULL` |
| `tab` | type_alias | `include/tab.h:45` | `typedef struct tab tab;` |
| `tab_alive` | function | `include/tab.h:338` | `int tab_alive(const tab *t);` |
| `tab_child_pid` | function | `include/tab.h:341` | `pid_t tab_child_pid(const tab *t);` |
| `tab_close` | function | `include/tab.h:344` | `void tab_close(tab *t);` |
| `tab_eval_result` | struct | `include/tab.h:127` | `` |
| `tab_eval_result_free` | function | `include/tab.h:348` | `void tab_eval_result_free(tab_eval_result *r);` |
| `tab_hist_op` | struct | `include/tab.h:53` | `` |
| `tab_image` | struct | `include/tab.h:140` | `` |
| `tab_image_free` | function | `include/tab.h:349` | `void tab_image_free(tab_image *img);` |
| `tab_open` | function | `include/tab.h:156` | `* and reaches tab_open (the app and the test harness) must call this first. */ void tab_worker_dispatch(int argc, char *` |
| `tab_page` | struct | `include/tab.h:75` | `` |
| `tab_page_free` | function | `include/tab.h:347` | `void tab_page_free(tab_page *p);` |
| `tab_parse_worker_args` | function | `include/tab.h:163` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd);` |
| `tab_set_cookies` | function | `include/tab.h:198` | `void tab_set_cookies(tab *t, const char *cookies);` |
| `tab_set_fetcher` | function | `include/tab.h:186` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx);` |
| `tab_set_net_allowed` | function | `include/tab.h:191` | `void tab_set_net_allowed(tab *t, int allowed);` |
| `tab_set_storage` | function | `include/tab.h:203` | `void tab_set_storage(tab *t, const char *blob, size_t len);` |
| `tab_set_viewport_w` | function | `include/tab.h:217` | `void tab_set_viewport_w(tab *t, int px);` |
| `tab_status` | enum | `include/tab.h:31` | `` |
| `tab_subreq_permitted` | function | `include/tab.h:222` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method);` |
| `tab_worker_dispatch` | function | `include/tab.h:152` | `* Call tab_worker_dispatch(argc, argv) as the FIRST thing in main(): if argv is the * internal "--tab-worker <rfd> <wfd>` |
| `tab_ws_event_kind` | enum | `include/tab.h:64` | `` |
| `tab_ws_kind` | enum | `include/tab.h:60` | `` |
| `tab_ws_op` | struct | `include/tab.h:68` | `` |
| `view` | function | `include/tab.h:230` | `* <noscript> handling in the built view (off => fallback shown, on => suppressed) * and is where allowlisted page-script` |
| `width` | type_alias | `include/tab.h:140` | `typedef struct tab_image { uint32_t width;` |
| `FREEDOM_TEXT_SHAPE_H` | macro | `include/text_shape.h:19` | `#define FREEDOM_TEXT_SHAPE_H` |
| `TSH_MAX_GLYPHS` | macro | `include/text_shape.h:36` | `#define TSH_MAX_GLYPHS` |
| `TSH_MAX_TEXT` | macro | `include/text_shape.h:37` | `#define TSH_MAX_TEXT` |
| `content` | function | `include/text_shape.h:11` | `* TEXT is hostile remote content (sanitised UTF-8) and is fuzzed (make fuzz-tsh);` |
| `family` | type_alias | `include/text_shape.h:30` | `typedef struct tsh_font { int family;` |
| `origin` | function | `include/text_shape.h:51` | `* glyphs are written with positions relative to origin (0,0) on the baseline, * and *out_adv holds the total pen advance` |
| `tsh_font` | struct | `include/text_shape.h:30` | `` |
| `tsh_measure` | function | `include/text_shape.h:60` | `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len);` |
| `tsh_ready` | function | `include/text_shape.h:48` | `int tsh_ready(void);` |
| `tsh_shutdown` | function | `include/text_shape.h:69` | `void tsh_shutdown(void);` |
| `tsh_status` | enum | `include/text_shape.h:39` | `` |
| `FREEDOM_TEXTFIELD_H` | macro | `include/textfield.h:2` | `#define FREEDOM_TEXTFIELD_H` |
| `TF_CAP` | macro | `include/textfield.h:23` | `#define TF_CAP` |
| `buf` | type_alias | `include/textfield.h:24` | `typedef struct tf_field { char buf[TF_CAP];` |
| `tf_backspace` | function | `include/textfield.h:53` | `void tf_backspace(tf_field *f);` |
| `tf_clear` | function | `include/textfield.h:45` | `void tf_clear(tf_field *f);` |
| `tf_cursor` | function | `include/textfield.h:68` | `size_t tf_cursor(const tf_field *f);` |
| `tf_delete` | function | `include/textfield.h:56` | `void tf_delete(tf_field *f);` |
| `tf_end` | function | `include/textfield.h:63` | `void tf_end(tf_field *f);` |
| `tf_field` | struct | `include/textfield.h:25` | `` |
| `tf_home` | function | `include/textfield.h:62` | `void tf_home(tf_field *f);` |
| `tf_init` | function | `include/textfield.h:38` | `void tf_init(tf_field *f);` |
| `tf_len` | function | `include/textfield.h:67` | `size_t tf_len(const tf_field *f);` |
| `tf_move` | function | `include/textfield.h:59` | `void tf_move(tf_field *f, long delta);` |
| `tf_status` | enum | `include/textfield.h:31` | `` |
| `tf_text` | function | `include/textfield.h:66` | `const char *tf_text(const tf_field *f);` |
| `FREEDOM_TLS_IMPERSONATE_H` | macro | `include/tls_impersonate.h:2` | `#define FREEDOM_TLS_IMPERSONATE_H` |
| `TI_MAGIC` | macro | `include/tls_impersonate.h:60` | `#define TI_MAGIC` |
| `TI_MAX_BODY` | macro | `include/tls_impersonate.h:64` | `#define TI_MAX_BODY` |
| `TI_MAX_CHAIN` | macro | `include/tls_impersonate.h:67` | `#define TI_MAX_CHAIN` |
| `TI_MAX_GROUP` | macro | `include/tls_impersonate.h:68` | `#define TI_MAX_GROUP` |
| `TI_MAX_HEADERS` | macro | `include/tls_impersonate.h:63` | `#define TI_MAX_HEADERS` |
| `TI_MAX_METHOD` | macro | `include/tls_impersonate.h:62` | `#define TI_MAX_METHOD` |
| `TI_MAX_RESP_BODY` | macro | `include/tls_impersonate.h:66` | `#define TI_MAX_RESP_BODY` |
| `TI_MAX_RESP_HDR` | macro | `include/tls_impersonate.h:65` | `#define TI_MAX_RESP_HDR` |
| `TI_MAX_URL` | macro | `include/tls_impersonate.h:61` | `#define TI_MAX_URL` |
| `chain` | function | `include/tls_impersonate.h:32` | `* * The response carries the peer certificate chain (DER) and the negotiated group so * the TRUSTED PARENT re-applies th` |
| `path` | function | `include/tls_impersonate.h:26` | `* Zero Knowledge path (PQ-hybrid, VERIFYPEER). * * 2. ti_encode_x / ti_decode_x — the length-prefixed, fail-closed seria` |
| `status` | type_alias | `include/tls_impersonate.h:82` | `typedef struct ti_resp { long status;` |
| `success` | function | `include/tls_impersonate.h:97` | `* ti_decode_* returns 0 on success (out fully populated), <0 on any malformed, * truncated or over-cap input (out left z` |
| `ti_decode_req` | function | `include/tls_impersonate.h:101` | `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out);` |
| `ti_decode_resp` | function | `include/tls_impersonate.h:105` | `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out);` |
| `ti_encode_resp` | function | `include/tls_impersonate.h:104` | `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap);` |
| `ti_profile` | enum | `include/tls_impersonate.h:41` | `` |
| `ti_req` | struct | `include/tls_impersonate.h:72` | `` |
| `ti_req_free` | function | `include/tls_impersonate.h:102` | `void ti_req_free(ti_req *r);` |
| `ti_resp` | struct | `include/tls_impersonate.h:82` | `` |
| `ti_resp_free` | function | `include/tls_impersonate.h:106` | `void ti_resp_free(ti_resp *r);` |
| `ti_should_impersonate` | function | `include/tls_impersonate.h:56` | `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled, int user_opt_in);` |
| `FREEDOM_UI_H` | macro | `include/ui.h:2` | `#define FREEDOM_UI_H` |
| `available` | function | `include/ui.h:85` | `* cheapest artifact to inspect a render where no display is available (CI, an AI * agent): export, then read the PNG dir` |
| `disk` | function | `include/ui.h:112` | `* images are read from disk (confined to the document directory by render_doc). * top_url is the page origin (https or f` |
| `images` | function | `include/ui.h:114` | `* fetcher loads no images (placeholders, as before). Any image that fails falls back * to its placeholder, byte-identica` |
| `jg_table` | struct | `include/ui.h:94` | `` |
| `offset` | type_alias | `include/ui.h:29` | `typedef struct ui_line { size_t offset;` |
| `out` | function | `include/ui.h:97` | `* ui_render_png does and fills *out (jg_init'ed by the caller) with one rect per * element in document coordinates, plus` |
| `placeholders` | function | `include/ui.h:107` | `* above always draw image placeholders (no worker to decode hostile bytes);` |
| `rd_doc` | struct | `include/ui.h:68` | `` |
| `space` | function | `include/ui.h:43` | `* Breaks at the last fitting space (the break space is consumed), hard-breaks * words longer than max_cols, and treats '` |
| `tab` | struct | `include/ui.h:104` | `` |
| `ui_clamp_scroll` | function | `include/ui.h:54` | `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines);` |
| `ui_layout` | struct | `include/ui.h:34` | `` |
| `ui_layout_free` | function | `include/ui.h:51` | `void ui_layout_free(ui_layout *lay);` |
| `ui_line` | struct | `include/ui.h:29` | `` |
| `ui_render_viewport_w` | function | `include/ui.h:141` | `int ui_render_viewport_w(void);` |
| `ui_status` | enum | `include/ui.h:19` | `` |
| `FREEDOM_URL_H` | macro | `include/url.h:2` | `#define FREEDOM_URL_H` |
| `URL_ERR_NOT_HTTPS` | function | `include/url.h:109` | `* URL_ERR_NOT_HTTPS (out untouched);` |
| `URL_MAX_LEN` | macro | `include/url.h:30` | `#define URL_MAX_LEN` |
| `URL_SEARCH_ENDPOINT` | macro | `include/url.h:76` | `#define URL_SEARCH_ENDPOINT` |
| `password` | function | `include/url.h:152` | `* username and password (owned, must be freed) into *username_out and * *password_out, and returns URL_OK. When there is` |
| `path` | function | `include/url.h:115` | `* absolute path ("file:///..."). NULL => 0. */ int url_is_file(const char *s);` |
| `url` | function | `include/url.h:126` | `* Every field ALIASES the input url (not owned, valid while url is alive);` |
| `url_authority_len` | function | `include/url.h:51` | `size_t url_authority_len(const char *url);` |
| `url_file_path` | function | `include/url.h:121` | `const char *url_file_path(const char *s);` |
| `url_has_scheme` | function | `include/url.h:46` | `int url_has_scheme(const char *s);` |
| `url_is_https` | function | `include/url.h:42` | `int url_is_https(const char *s);` |
| `url_omni_kind` | enum | `include/url.h:78` | `` |
| `url_parts` | struct | `include/url.h:129` | `` |
| `url_status` | enum | `include/url.h:32` | `` |
| `UTIL_H` | macro | `include/util.h:5` | `#define UTIL_H` |
| `fnv1a` | function | `include/util.h:67` | `static inline uint64_t fnv1a(const char *s, size_t n)` |
| `mem_contains_ci` | function | `include/util.h:43` | `static inline int mem_contains_ci(const void *hay, size_t hlen, const char *needle)` |
| `read_full` | function | `include/util.h:26` | `static inline int read_full(int fd, void *buf, size_t n)` |
| `utf8_seq_len` | function | `include/util.h:57` | `static inline size_t utf8_seq_len(unsigned char c)` |
| `write_full` | function | `include/util.h:15` | `static inline int write_full(int fd, const void *buf, size_t n)` |
| `FREEDOM_WEB_STORAGE_H` | macro | `include/web_storage.h:2` | `#define FREEDOM_WEB_STORAGE_H` |
| `WST_MAX_KEYS` | macro | `include/web_storage.h:18` | `#define WST_MAX_KEYS` |
| `WST_MAX_ORIGINS` | macro | `include/web_storage.h:17` | `#define WST_MAX_ORIGINS` |
| `WST_ORIGIN_MAX` | macro | `include/web_storage.h:20` | `#define WST_ORIGIN_MAX` |
| `WST_QUOTA` | macro | `include/web_storage.h:19` | `#define WST_QUOTA` |
| `full` | function | `include/web_storage.h:45` | `* validating it in full (wst_decode_check). Returns 0, or -1 when invalid (fn is then * never called). The one parser of` |
| `wst_db` | type_alias | `include/web_storage.h:21` | `typedef struct wst_db wst_db;` |
| `wst_decode_check` | function | `include/web_storage.h:37` | `int wst_decode_check(const char *blob, size_t len);` |
| `wst_encode` | function | `include/web_storage.h:33` | `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len);` |
| `wst_free` | function | `include/web_storage.h:28` | `void wst_free(wst_db *db);` |
| `wst_new` | function | `include/web_storage.h:25` | `wst_db *wst_new(void);` |
| `wst_origin_bytes` | function | `include/web_storage.h:59` | `size_t wst_origin_bytes(const wst_db *db, const char *origin);` |
| `wst_replace` | function | `include/web_storage.h:42` | `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len);` |
| `FREEDOM_WEBCAPS_H` | macro | `include/webcaps.h:2` | `#define FREEDOM_WEBCAPS_H` |
| `js` | type_alias | `include/webcaps.h:38` | `typedef struct wc_caps { /* leak-free (global): granted by user toggle or allow.conf presentation-trust. */ bool js;` |
| `js_mode` | type_alias | `include/webcaps.h:57` | `typedef struct wc_input { jsp_mode js_mode;` |
| `wc_caps` | struct | `include/webcaps.h:38` | `` |
| `wc_input` | struct | `include/webcaps.h:57` | `` |
| `FREEDOM_WS_HUB_H` | macro | `include/ws_hub.h:2` | `#define FREEDOM_WS_HUB_H` |
| `WH_CLOSE_ABNORMAL` | macro | `include/ws_hub.h:27` | `#define WH_CLOSE_ABNORMAL` |
| `WH_MAX` | macro | `include/ws_hub.h:21` | `#define WH_MAX` |
| `generation` | function | `include/ws_hub.h:50` | `* previous generation (before wh_close_all) are closed and dropped silently. */ void wh_on_notify(wh_hub *h, wh_emit_fn ` |
| `wh_close` | function | `include/ws_hub.h:58` | `void wh_close(wh_hub *h, int id);` |
| `wh_close_all` | function | `include/ws_hub.h:61` | `void wh_close_all(wh_hub *h);` |
| `wh_count` | function | `include/ws_hub.h:73` | `size_t wh_count(const wh_hub *h);` |
| `wh_free` | function | `include/ws_hub.h:38` | `void wh_free(wh_hub *h);` |
| `wh_hub` | type_alias | `include/ws_hub.h:30` | `typedef struct wh_hub wh_hub;` |
| `wh_new` | function | `include/ws_hub.h:34` | `wh_hub *wh_new(void);` |
| `wh_notify_fd` | function | `include/ws_hub.h:41` | `int wh_notify_fd(const wh_hub *h);` |
| `wh_on_readable` | function | `include/ws_hub.h:70` | `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx);` |
| `wh_open_async` | function | `include/ws_hub.h:46` | `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg);` |
| `wh_poll_fds` | function | `include/ws_hub.h:65` | `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap);` |
| `wh_send` | function | `include/ws_hub.h:54` | `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary);` |
| `FREEDOM_ZOOM_H` | macro | `include/zoom.h:2` | `#define FREEDOM_ZOOM_H` |
| `ZM_DEFAULT_PCT` | macro | `include/zoom.h:23` | `#define ZM_DEFAULT_PCT` |
| `ZM_MAX_PCT` | macro | `include/zoom.h:22` | `#define ZM_MAX_PCT` |
| `ZM_MIN_PCT` | macro | `include/zoom.h:21` | `#define ZM_MIN_PCT` |
| `zm_apply` | function | `include/zoom.h:42` | `double zm_apply(double base_px, int pct);` |
| `zm_clamp` | function | `include/zoom.h:26` | `int zm_clamp(int pct);` |
| `zm_reset` | function | `include/zoom.h:35` | `int zm_reset(void);` |
| `zm_scale` | function | `include/zoom.h:38` | `double zm_scale(int pct);` |
| `zm_zoom_in` | function | `include/zoom.h:29` | `int zm_zoom_in(int pct);` |
| `zm_zoom_out` | function | `include/zoom.h:32` | `int zm_zoom_out(int pct);` |
| `fp_accept_language` | function | `src/anti_fp.c:27` | `const char *fp_accept_language(void)` |
| `fp_accept_language_header` | function | `src/anti_fp.c:31` | `const char *fp_accept_language_header(void)` |
| `fp_app_code_name` | function | `src/anti_fp.c:61` | `const char *fp_app_code_name(void)` |
| `fp_app_name` | function | `src/anti_fp.c:69` | `const char *fp_app_name(void)` |
| `fp_app_version` | function | `src/anti_fp.c:57` | `const char *fp_app_version(void)` |
| `fp_bucket_screen` | function | `src/anti_fp.c:99` | `void fp_bucket_screen(int w, int h, int *out_w, int *out_h)` |
| `fp_build_id` | function | `src/anti_fp.c:81` | `const char *fp_build_id(void)` |
| `fp_coarsen_time_ms` | function | `src/anti_fp.c:17` | `uint64_t fp_coarsen_time_ms(uint64_t raw_ms)` |
| `fp_cookie_enabled` | function | `src/anti_fp.c:93` | `int fp_cookie_enabled(void)` |
| `fp_device_memory_gb` | function | `src/anti_fp.c:51` | `int fp_device_memory_gb(void)` |
| `fp_hardware_concurrency` | function | `src/anti_fp.c:47` | `int fp_hardware_concurrency(void)` |
| `fp_max_touch_points` | function | `src/anti_fp.c:85` | `int fp_max_touch_points(void)` |
| `fp_on_line` | function | `src/anti_fp.c:89` | `int fp_on_line(void)` |
| `fp_origin_key` | function | `src/anti_fp.c:139` | `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain)` |
| `fp_oscpu` | function | `src/anti_fp.c:77` | `const char *fp_oscpu(void)` |
| `fp_perturb` | function | `src/anti_fp.c:128` | `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key)` |
| `fp_platform` | function | `src/anti_fp.c:39` | `const char *fp_platform(void)` |
| `fp_product` | function | `src/anti_fp.c:65` | `const char *fp_product(void)` |
| `fp_product_sub` | function | `src/anti_fp.c:73` | `const char *fp_product_sub(void)` |
| `fp_timezone` | function | `src/anti_fp.c:35` | `const char *fp_timezone(void)` |
| `fp_user_agent` | function | `src/anti_fp.c:23` | `const char *fp_user_agent(void)` |
| `fp_vendor` | function | `src/anti_fp.c:43` | `const char *fp_vendor(void)` |
| `splitmix64` | function | `src/anti_fp.c:121` | `static uint64_t splitmix64(uint64_t *state)` |
| `bf_collapse` | function | `src/block_flow.c:30` | `double bf_collapse(double a, double b)` |
| `bf_collapse_n` | function | `src/block_flow.c:15` | `double bf_collapse_n(const double *m, size_t n)` |
| `bf_margins_adjoin` | function | `src/block_flow.c:35` | `int bf_margins_adjoin(double border_px, double padding_px)` |
| `finite_or_zero` | function | `src/block_flow.c:11` | `static double finite_or_zero(double v)` |
| `BLOCK` | macro | `src/box_style.c:65` | `#define BLOCK` |
| `BX_DISPLAY_MAX` | macro | `src/box_style.c:23` | `#define BX_DISPLAY_MAX` |
| `BX_TAG_MAX` | macro | `src/box_style.c:22` | `#define BX_TAG_MAX` |
| `DISP_N` | macro | `src/box_style.c:257` | `#define DISP_N` |
| `EDG` | macro | `src/box_style.c:70` | `#define EDG(t, r, b, l)` |
| `IBLOCK` | macro | `src/box_style.c:67` | `#define IBLOCK` |
| `INLINE` | macro | `src/box_style.c:66` | `#define INLINE` |
| `LITEM` | macro | `src/box_style.c:68` | `#define LITEM` |
| `NONE` | macro | `src/box_style.c:69` | `#define NONE` |
| `TAG_N` | macro | `src/box_style.c:159` | `#define TAG_N` |
| `T_CAP` | macro | `src/box_style.c:78` | `#define T_CAP` |
| `T_CELL` | macro | `src/box_style.c:77` | `#define T_CELL` |
| `T_COL` | macro | `src/box_style.c:79` | `#define T_COL` |
| `T_GRP` | macro | `src/box_style.c:75` | `#define T_GRP` |
| `T_NO` | macro | `src/box_style.c:73` | `#define T_NO` |
| `T_ROW` | macro | `src/box_style.c:76` | `#define T_ROW` |
| `T_TBL` | macro | `src/box_style.c:74` | `#define T_TBL` |
| `ZERO` | macro | `src/box_style.c:71` | `#define ZERO` |
| `bg_size_component` | function | `src/box_style.c:375` | `static double bg_size_component(int px_val, int pct_pm, double area)` |
| `bx_background_layer` | function | `src/box_style.c:382` | `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h,
                    ...` |
| `bx_block_ua_box` | function | `src/box_style.c:223` | `bx_box bx_block_ua_box(int heading_level, int in_list, bx_ua_tag ua)` |
| `bx_border_box_h` | function | `src/box_style.c:333` | `double bx_border_box_h(double declared_h, int border_box,
                       double pad_t, do...` |
| `bx_content_cap` | function | `src/box_style.c:361` | `double bx_content_cap(double width_cap, int border_box,
                      double pad_l, doubl...` |
| `bx_content_clipped` | function | `src/box_style.c:344` | `int bx_content_clipped(int overflow_x, int overflow_y)` |
| `bx_default_for_tag` | function | `src/box_style.c:161` | `bx_box bx_default_for_tag(const char *tag)` |
| `bx_default_for_ua` | function | `src/box_style.c:217` | `bx_box bx_default_for_ua(bx_ua_tag id)` |
| `bx_display_name` | function | `src/box_style.c:421` | `const char *bx_display_name(bx_display d)` |
| `bx_lp_px` | function | `src/box_style.c:350` | `double bx_lp_px(int px_val, int pct_pm, double basis)` |
| `bx_parse_display` | function | `src/box_style.c:259` | `bx_status bx_parse_display(const char *token, bx_display *out)` |
| `bx_place` | function | `src/box_style.c:269` | `bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,
                ...` |
| `bx_replaced_box` | function | `src/box_style.c:319` | `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den,
                    doub...` |
| `bx_table_role_of` | function | `src/box_style.c:169` | `bx_table_role bx_table_role_of(const char *tag, css_display display)` |
| `bx_ua_of_tag` | function | `src/box_style.c:208` | `bx_ua_tag bx_ua_of_tag(const char *tag)` |
| `bx_width_cap` | function | `src/box_style.c:286` | `double bx_width_cap(int w_px, int w_pct, double avail_w)` |
| `bx_width_cap2` | function | `src/box_style.c:311` | `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w)` |
| `copy_lower_trim` | function | `src/box_style.c:35` | `static int copy_lower_trim(const char *in, char *out, size_t out_size)` |
| `disp_row` | struct | `src/box_style.c:239` | `` |
| `is_ws` | function | `src/box_style.c:29` | `static int is_ws(char c)` |
| `name_cmp` | function | `src/box_style.c:48` | `static int name_cmp(const void *key, const void *elem)` |
| `tag_row` | struct | `src/box_style.c:59` | `` |
| `take` | function | `src/box_style.c:293` | `* caller has to take (Sizing 3 section 5.1), so to a resolver that only sums a * px and a percentage half they read exac` |
| `BT_LEN_AUTO` | macro | `src/box_tree.c:31` | `#define BT_LEN_AUTO` |
| `BT_WRAP_EPS` | macro | `src/box_tree.c:62` | `#define BT_WRAP_EPS` |
| `assign_doc_order` | function | `src/box_tree.c:412` | `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,
                  ...` |
| `block` | function | `src/box_tree.c:473` | `* true block (same flow neighbourhood), strictly better than zeros. NULL
     * placed keeps lega...` |
| `bt_box_hidden` | function | `src/box_tree.c:683` | `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)` |
| `bt_containing_block` | function | `src/box_tree.c:462` | `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i,
                        ...` |
| `bt_layout` | function | `src/box_tree.c:372` | `bt_status bt_layout(bt_node *root, double avail_w)` |
| `bt_nn` | function | `src/box_tree.c:58` | `static double bt_nn(double v)` |
| `bt_oof_anchor` | function | `src/box_tree.c:675` | `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)` |
| `bt_oof_avail` | function | `src/box_tree.c:696` | `double bt_oof_avail(int a, int a_pct, int b, int b_pct, double cb, int *both)` |
| `bt_oof_root` | function | `src/box_tree.c:679` | `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)` |
| `bt_resolve_positioning` | function | `src/box_tree.c:492` | `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,
                          ...` |
| `bt_resolve_positioning_ex` | function | `src/box_tree.c:503` | `bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,
                       ...` |
| `find_positioned_ancestor` | function | `src/box_tree.c:429` | `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,
                       ...` |
| `inset_unset` | function | `src/box_tree.c:458` | `static int inset_unset(int v, int pct_pm)` |
| `layout_block` | function | `src/box_tree.c:37` | `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,
                   ...` |
| `layout_flex` | function | `src/box_tree.c:97` | `static bt_status layout_flex(bt_node *node, bt_node *const *kids, size_t nk,
                    ...` |
| `layout_grid` | function | `src/box_tree.c:220` | `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,
                    ...` |
| `layout_node` | function | `src/box_tree.c:327` | `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)` |
| `oof_walk` | function | `src/box_tree.c:658` | `static int oof_walk(const pv_box_def *boxes, size_t nbox, int bid, int nearest)` |
| `resolve_inset` | function | `src/box_tree.c:449` | `static double resolve_inset(int v, int pct_pm, double basis)` |
| `wrap_reverse` | function | `src/box_tree.c:79` | `*
 * wrap_reverse (node->wrap_reverse): when node->wrap is active and node->wrap_reverse
 * is no...` |
| `_POSIX_C_SOURCE` | macro | `src/browser.c:7` | `#define _POSIX_C_SOURCE` |
| `browser_add_exception` | function | `src/browser.c:472` | `browser_status browser_add_exception(browser_state *bs, const char *host)` |
| `browser_back` | function | `src/browser.c:268` | `browser_status browser_back(browser_state *bs)` |
| `browser_can_back` | function | `src/browser.c:292` | `int browser_can_back(const browser_state *bs)` |
| `browser_can_forward` | function | `src/browser.c:296` | `int browser_can_forward(const browser_state *bs)` |
| `browser_commit_url_bar` | function | `src/browser.c:190` | `browser_status browser_commit_url_bar(browser_state *bs)` |
| `browser_current_url` | function | `src/browser.c:300` | `const char *browser_current_url(const browser_state *bs)` |
| `browser_doc_index` | function | `src/browser.c:260` | `int browser_doc_index(const browser_state *bs)` |
| `browser_entry_doc` | function | `src/browser.c:255` | `int browser_entry_doc(const browser_state *bs, size_t pos)` |
| `browser_forward` | function | `src/browser.c:280` | `browser_status browser_forward(browser_state *bs)` |
| `browser_free` | function | `src/browser.c:167` | `void browser_free(browser_state *bs)` |
| `browser_init` | function | `src/browser.c:156` | `browser_status browser_init(browser_state *bs)` |
| `browser_is_exception` | function | `src/browser.c:464` | `int browser_is_exception(const browser_state *bs, const char *host)` |
| `browser_navigate` | function | `src/browser.c:224` | `browser_status browser_navigate(browser_state *bs, const char *url)` |
| `browser_push_state` | function | `src/browser.c:236` | `browser_status browser_push_state(browser_state *bs, const char *url)` |
| `browser_replace_state` | function | `src/browser.c:243` | `browser_status browser_replace_state(browser_state *bs, const char *url)` |
| `browser_set_page` | function | `src/browser.c:409` | `browser_status browser_set_page(browser_state *bs, const char *title,
                           ...` |
| `browser_set_status` | function | `src/browser.c:431` | `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)` |
| `browser_set_url_bar` | function | `src/browser.c:178` | `browser_status browser_set_url_bar(browser_state *bs, const char *url)` |
| `browser_status_text` | function | `src/browser.c:445` | `const char *browser_status_text(const browser_state *bs, uint64_t now_ms)` |
| `browser_url_bar_backspace` | function | `src/browser.c:341` | `browser_status browser_url_bar_backspace(browser_state *bs)` |
| `browser_url_bar_clear` | function | `src/browser.c:400` | `browser_status browser_url_bar_clear(browser_state *bs)` |
| `browser_url_bar_delete` | function | `src/browser.c:355` | `browser_status browser_url_bar_delete(browser_state *bs)` |
| `browser_url_bar_delete_selection` | function | `src/browser.c:316` | `int browser_url_bar_delete_selection(browser_state *bs)` |
| `browser_url_bar_extend_cursor` | function | `src/browser.c:376` | `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)` |
| `browser_url_bar_insert` | function | `src/browser.c:326` | `browser_status browser_url_bar_insert(browser_state *bs, char c)` |
| `browser_url_bar_move_cursor` | function | `src/browser.c:366` | `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)` |
| `browser_url_bar_select_all` | function | `src/browser.c:393` | `browser_status browser_url_bar_select_all(browser_state *bs)` |
| `browser_url_bar_selection` | function | `src/browser.c:305` | `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)` |
| `browser_url_bar_set_cursor` | function | `src/browser.c:385` | `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)` |
| `clear_status` | function | `src/browser.c:25` | `static void clear_status(browser_state *bs)` |
| `cp1252_to_ucs` | function | `src/browser.c:88` | `static unsigned int cp1252_to_ucs(unsigned char c)` |
| `free_exceptions` | function | `src/browser.c:42` | `static void free_exceptions(browser_state *bs)` |
| `free_history` | function | `src/browser.c:30` | `static void free_history(browser_state *bs)` |
| `free_page` | function | `src/browser.c:15` | `static void free_page(browser_state *bs)` |
| `host_equal` | function | `src/browser.c:453` | `static int host_equal(const char *a, const char *b)` |
| `is_https_url` | function | `src/browser.c:51` | `static int is_https_url(const char *s)` |
| `is_local_path` | function | `src/browser.c:55` | `static int is_local_path(const char *s)` |
| `url_is_allowed` | function | `src/browser.c:60` | `static int url_is_allowed(const char *url)` |
| `utf8_encode` | function | `src/browser.c:102` | `static size_t utf8_encode(unsigned int cp, char *out)` |
| `xstrdup` | function | `src/browser.c:74` | `static char *xstrdup(const char *s)` |
| `cx_box_layer` | function | `src/compositor.c:34` | `cx_layer cx_box_layer(const cx_style *s)` |
| `cx_forms_stacking_context` | function | `src/compositor.c:16` | `int cx_forms_stacking_context(const cx_style *s)` |
| `cx_item_compare` | function | `src/compositor.c:54` | `int cx_item_compare(const cx_item *a, const cx_item *b)` |
| `cx_sort` | function | `src/compositor.c:70` | `void cx_sort(cx_item *items, size_t n)` |
| `eff_z` | function | `src/compositor.c:50` | `static int eff_z(const cx_item *it)` |
| `AUTO_REJECT` | macro | `src/css.c:253` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css.c:255` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css.c:256` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css.c:254` | `#define AUTO_VALUE` |
| `CSS_DECL_SLOTS_MIN` | macro | `src/css.c:62` | `#define CSS_DECL_SLOTS_MIN` |
| `CSS_INIT_DECLS` | macro | `src/css.c:47` | `#define CSS_INIT_DECLS` |
| `CSS_INIT_RULES` | macro | `src/css.c:63` | `#define CSS_INIT_RULES` |
| `CSS_INIT_SELS` | macro | `src/css.c:46` | `#define CSS_INIT_SELS` |
| `CSS_INLINE_DECLS` | macro | `src/css.c:65` | `#define CSS_INLINE_DECLS` |
| `CSS_MAX_FONT_FACES` | macro | `src/css.c:150` | `#define CSS_MAX_FONT_FACES` |
| `CSS_MAX_RAW` | macro | `src/css.c:82` | `#define CSS_MAX_RAW` |
| `CSS_MEDIA_MAX_DEPTH` | macro | `src/css.c:3820` | `#define CSS_MEDIA_MAX_DEPTH` |
| `CSS_SELS_PER_GROUP` | macro | `src/css.c:64` | `#define CSS_SELS_PER_GROUP` |
| `CSS_VAR_POOL` | macro | `src/css.c:4908` | `#define CSS_VAR_POOL` |
| `LIST` | function | `src/css.c:2046` | `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose into ` |
| `NULL` | function | `src/css.c:5262` | `* Sheet can be NULL (inline style, no @keyframes). */
void css_resolve_anim_keyframes(css_style *...` |
| `P_META_CUSTOM` | macro | `src/css.c:78` | `#define P_META_CUSTOM` |
| `P_META_VARSRC` | macro | `src/css.c:79` | `#define P_META_VARSRC` |
| `add_rule` | function | `src/css.c:3562` | `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,
                     siz...` |
| `apply_decl` | function | `src/css.c:4458` | `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...` |
| `apply_rule` | function | `src/css.c:4938` | `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...` |
| `apply_var_source` | function | `src/css.c:4912` | `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
        ...` |
| `at_is_media` | function | `src/css.c:3687` | `static int at_is_media(const char *s, size_t i, size_t n)` |
| `at_keyword` | function | `src/css.c:3698` | `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)` |
| `bg_alpha_of` | function | `src/css.c:214` | `static int bg_alpha_of(const char *v)` |
| `block_end` | function | `src/css.c:3665` | `static size_t block_end(const char *s, size_t open, size_t n)` |
| `blur` | function | `src/css.c:1251` | `* consumes ONLY blur(Npx);` |
| `caller` | function | `src/css.c:2710` | `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached a br` |
| `cand_cmp` | function | `src/css.c:4847` | `static int cand_cmp(const void *pa, const void *pb)` |
| `collect_custom_props_scoped` | function | `src/css.c:3829` | `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,
                ...` |
| `column` | function | `src/css.c:1608` | `* column (`flex: 1 1 0%`);` |
| `computed_font_size` | function | `src/css.c:4831` | `static double computed_font_size(const css_style *o, const css_element *el)` |
| `copy_trim` | function | `src/css.c:1764` | `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `csel_substr` | function | `src/css.c:3720` | `return known && csel_substr(val, "var(", 1);` |
| `css_cand` | struct | `src/css.c:4842` | `` |
| `css_decl` | function | `src/css.c:86` | `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);` |
| `css_font_face_at` | function | `src/css.c:5298` | `int css_font_face_at(const css_sheet *sheet, size_t i,
                     char *family, size_t ...` |
| `css_font_face_count` | function | `src/css.c:5294` | `size_t css_font_face_count(const css_sheet *sheet)` |
| `css_free` | function | `src/css.c:4441` | `void css_free(css_sheet *s)` |
| `css_keyframe_stop` | struct | `src/css.c:132` | `` |
| `css_match` | struct | `src/css.c:4836` | `` |
| `css_parse` | function | `src/css.c:4357` | `css_status css_parse(const char *text, size_t len, css_sheet **out)` |
| `css_parse_inline` | function | `src/css.c:5308` | `css_style css_parse_inline(const char *style, size_t len)` |
| `css_parse_logged` | function | `src/css.c:4371` | `css_status css_parse_logged(const char *text, size_t len, const css_media *media,
               ...` |
| `css_parse_media` | function | `src/css.c:4361` | `css_status css_parse_media(const char *text, size_t len, const css_media *media,
                ...` |
| `css_parse_scoped` | function | `src/css.c:4366` | `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,
               ...` |
| `css_resolve` | function | `src/css.c:5238` | `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                  ...` |
| `css_resolve_el` | function | `src/css.c:5005` | `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         ...` |
| `css_resolve_el_ex` | function | `src/css.c:5014` | `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,
                      ...` |
| `css_resolve_pseudo` | function | `src/css.c:5020` | `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)` |
| `css_rule` | struct | `src/css.c:97` | `` |
| `css_sheet` | struct | `src/css.c:99` | `` |
| `drop_copy_text` | function | `src/css.c:3360` | `static void drop_copy_text(char *dst, size_t cap, const char *src)` |
| `drop_record` | function | `src/css.c:3379` | `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)` |
| `emit` | function | `src/css.c:59` | `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand at 1` |
| `emit_content` | function | `src/css.c:1387` | `static int emit_content(css_decl *dst, int cap, const char *str,
                        char (*c...` |
| `emit_radius_corner` | function | `src/css.c:880` | `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)` |
| `emit_spacing` | function | `src/css.c:348` | `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `empty` | function | `src/css.c:1407` | `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and the` |
| `expand_backdrop_filter` | function | `src/css.c:1254` | `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)` |
| `expand_background` | function | `src/css.c:231` | `static int expand_background(const char *val, css_decl *dst, int cap,
                           ...` |
| `expand_bg_image` | function | `src/css.c:226` | `static int expand_bg_image(const char *val, css_decl *dst, int cap,
                           ch...` |
| `expand_bg_position` | function | `src/css.c:1287` | `static int expand_bg_position(const char *val, css_decl *dst, int cap)` |
| `expand_bg_size` | function | `src/css.c:1347` | `static int expand_bg_size(const char *val, css_decl *dst, int cap)` |
| `expand_box2` | function | `src/css.c:268` | `static int expand_box2(const char *val, int slot_start, int slot_end,
                       int ...` |
| `expand_box4` | function | `src/css.c:263` | `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,
            ...` |
| `expand_box_shadow` | function | `src/css.c:1557` | `static int expand_box_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_column_rule` | function | `src/css.c:1050` | `static int expand_column_rule(const char *val, css_decl *dst, int cap)` |
| `expand_columns` | function | `src/css.c:994` | `static int expand_columns(const char *val, css_decl *dst, int cap)` |
| `expand_content` | function | `src/css.c:1403` | `static int expand_content(const char *val, css_decl *dst, int cap,
                          char...` |
| `expand_flex` | function | `src/css.c:1629` | `static int expand_flex(const char *val, css_decl *dst, int cap)` |
| `expand_flex_flow` | function | `src/css.c:1028` | `static int expand_flex_flow(const char *val, css_decl *dst, int cap)` |
| `expand_gap` | function | `src/css.c:2554` | `static int expand_gap(const char *val, css_decl *dst, int cap)` |
| `expand_grid_areas` | function | `src/css.c:1439` | `static int expand_grid_areas(const char *val, css_decl *dst, int cap,
                           ...` |
| `expand_grid_template` | function | `src/css.c:1506` | `static int expand_grid_template(const char *val, css_decl *dst, int cap,
                        ...` |
| `expand_grid_template_cols` | function | `src/css.c:330` | `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `expand_outline` | function | `src/css.c:955` | `static int expand_outline(const char *val, css_decl *dst, int cap)` |
| `expand_shadow` | function | `src/css.c:349` | `static int expand_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_transform_list` | function | `src/css.c:2302` | `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);` |
| `expand_transform_origin` | function | `src/css.c:2522` | `static int expand_transform_origin(const char *val, css_decl *dst, int cap)` |
| `expand_valign` | function | `src/css.c:339` | `static int expand_valign(const char *val, css_decl *dst, int cap)` |
| `filter_paren_body` | function | `src/css.c:1091` | `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)` |
| `fold_font_relative` | function | `src/css.c:4976` | `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,
                         ...` |
| `function` | function | `src/css.c:1218` | `* function (the rest of the list still applies). Emits the whole * 4-decl group in lock-step or nothing. */ const char *` |
| `grammar` | function | `src/css.c:2740` | `* grammar (`justify`/`distribute`) is not `justify-content`'s. Guessing
     * there would be inv...` |
| `idx` | type_alias | `src/css.c:4842` | `typedef struct css_cand { int imp, espec, ord, idx;` |
| `ignored` | function | `src/css.c:2573` | `* engine slot and is ignored (documented simplification, like list-style's
 * ignored tokens). An...` |
| `interp_accent_color` | function | `src/css.c:682` | `static int interp_accent_color(const char *v)` |
| `interp_align` | function | `src/css.c:290` | `static int interp_align(const char *v)` |
| `interp_align_kw` | function | `src/css.c:1674` | `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` |
| `interp_appearance` | function | `src/css.c:554` | `static int interp_appearance(const char *v)` |
| `interp_aspect_ratio` | function | `src/css.c:345` | `static int interp_aspect_ratio(const char *v, int *num, int *den)` |
| `interp_backface_visibility` | function | `src/css.c:789` | `static int interp_backface_visibility(const char *v)` |
| `interp_bc_tok` | function | `src/css.c:890` | `static int interp_bc_tok(const char *t, int *o)` |
| `interp_bg` | function | `src/css.c:218` | `static int interp_bg(const char *v)` |
| `interp_bg_attachment` | function | `src/css.c:616` | `static int interp_bg_attachment(const char *v)` |
| `interp_bg_clip` | function | `src/css.c:601` | `static int interp_bg_clip(const char *v)` |
| `interp_bg_origin` | function | `src/css.c:609` | `static int interp_bg_origin(const char *v)` |
| `interp_bg_repeat` | function | `src/css.c:584` | `static int interp_bg_repeat(const char *v)` |
| `interp_bg_size` | function | `src/css.c:594` | `static int interp_bg_size(const char *v)` |
| `interp_border_collapse` | function | `src/css.c:462` | `static int interp_border_collapse(const char *v)` |
| `interp_border_style` | function | `src/css.c:812` | `static int interp_border_style(const char *v)` |
| `interp_box_orient` | function | `src/css.c:1705` | `static int interp_box_orient(const char *v)` |
| `interp_boxsizing` | function | `src/css.c:362` | `static int interp_boxsizing(const char *v)` |
| `interp_bs_tok` | function | `src/css.c:889` | `static int interp_bs_tok(const char *t, int *o)` |
| `interp_bw_tok` | function | `src/css.c:888` | `static int interp_bw_tok(const char *t, int *o)` |
| `interp_bwidth1` | function | `src/css.c:838` | `static int interp_bwidth1(const char *v)` |
| `interp_caption_side` | function | `src/css.c:503` | `static int interp_caption_side(const char *v)` |
| `interp_caret_color` | function | `src/css.c:542` | `static int interp_caret_color(const char *v)` |
| `interp_clear` | function | `src/css.c:375` | `static int interp_clear(const char *v)` |
| `interp_color` | function | `src/css.c:178` | `static int interp_color(const char *v)` |
| `interp_color_scheme` | function | `src/css.c:664` | `static int interp_color_scheme(const char *v)` |
| `interp_column_count` | function | `src/css.c:971` | `static int interp_column_count(const char *v)` |
| `interp_column_width` | function | `src/css.c:983` | `static int interp_column_width(const char *v)` |
| `interp_contain` | function | `src/css.c:629` | `static int interp_contain(const char *v)` |
| `interp_content_visibility` | function | `src/css.c:650` | `static int interp_content_visibility(const char *v)` |
| `interp_cursor` | function | `src/css.c:424` | `static int interp_cursor(const char *v)` |
| `interp_direction` | function | `src/css.c:346` | `static int interp_direction(const char *v)` |
| `interp_display` | function | `src/css.c:314` | `static int interp_display(const char *v)` |
| `interp_empty_cells` | function | `src/css.c:496` | `static int interp_empty_cells(const char *v)` |
| `interp_filter_deg` | function | `src/css.c:1076` | `static int interp_filter_deg(const char *s)` |
| `interp_filter_pct` | function | `src/css.c:1062` | `static int interp_filter_pct(const char *s)` |
| `interp_flex_basis` | function | `src/css.c:1595` | `static int interp_flex_basis(const char *v, int *out)` |
| `interp_flex_direction` | function | `src/css.c:1687` | `static int interp_flex_direction(const char *v)` |
| `interp_flex_factor` | function | `src/css.c:1585` | `static int interp_flex_factor(const char *v)` |
| `interp_flex_wrap` | function | `src/css.c:1711` | `static int interp_flex_wrap(const char *v)` |
| `interp_float` | function | `src/css.c:368` | `static int interp_float(const char *v)` |
| `interp_font_kerning` | function | `src/css.c:733` | `static int interp_font_kerning(const char *v)` |
| `interp_font_stretch` | function | `src/css.c:748` | `static int interp_font_stretch(const char *v)` |
| `interp_font_variant` | function | `src/css.c:517` | `static int interp_font_variant(const char *v)` |
| `interp_fontfamily` | function | `src/css.c:336` | `static int interp_fontfamily(const char *v)` |
| `interp_fontsize_ex` | function | `src/css.c:294` | `static int interp_fontsize_ex(const char *v, int *abs_out)` |
| `interp_forced_color_adjust` | function | `src/css.c:693` | `static int interp_forced_color_adjust(const char *v)` |
| `interp_gap` | function | `src/css.c:318` | `static int interp_gap(const char *v)` |
| `interp_grid_flow` | function | `src/css.c:1719` | `static int interp_grid_flow(const char *v)` |
| `interp_grid_span` | function | `src/css.c:1745` | `static int interp_grid_span(const char *v)` |
| `interp_gridcols` | function | `src/css.c:326` | `static int interp_gridcols(const char *v)` |
| `interp_hyphens` | function | `src/css.c:525` | `static int interp_hyphens(const char *v)` |
| `interp_image_rendering` | function | `src/css.c:657` | `static int interp_image_rendering(const char *v)` |
| `interp_isolation` | function | `src/css.c:623` | `static int interp_isolation(const char *v)` |
| `interp_justify` | function | `src/css.c:322` | `static int interp_justify(const char *v)` |
| `interp_len` | function | `src/css.c:273` | `static int interp_len(const char *v, int allow_auto, int *out)` |
| `interp_lineheight` | function | `src/css.c:298` | `static int interp_lineheight(const char *v)` |
| `interp_list_style_pos` | function | `src/css.c:727` | `static int interp_list_style_pos(const char *v)` |
| `interp_liststyle` | function | `src/css.c:347` | `static int interp_liststyle(const char *v)` |
| `interp_lp` | function | `src/css.c:277` | `static int interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_...` |
| `interp_mix_blend_mode` | function | `src/css.c:700` | `static int interp_mix_blend_mode(const char *v)` |
| `interp_object_fit` | function | `src/css.c:718` | `static int interp_object_fit(const char *v)` |
| `interp_opacity` | function | `src/css.c:338` | `static int interp_opacity(const char *v)` |
| `interp_overflow` | function | `src/css.c:392` | `static int interp_overflow(const char *v)` |
| `interp_overflow_wrap` | function | `src/css.c:454` | `static int interp_overflow_wrap(const char *v)` |
| `interp_overscroll_behavior` | function | `src/css.c:782` | `static int interp_overscroll_behavior(const char *v)` |
| `interp_pointer_events` | function | `src/css.c:572` | `static int interp_pointer_events(const char *v)` |
| `interp_position` | function | `src/css.c:353` | `static int interp_position(const char *v)` |
| `interp_print_color_adjust` | function | `src/css.c:687` | `static int interp_print_color_adjust(const char *v)` |
| `interp_resize` | function | `src/css.c:761` | `static int interp_resize(const char *v)` |
| `interp_scroll_behavior` | function | `src/css.c:769` | `static int interp_scroll_behavior(const char *v)` |
| `interp_style` | function | `src/css.c:306` | `static int interp_style(const char *v)` |
| `interp_table_layout` | function | `src/css.c:510` | `static int interp_table_layout(const char *v)` |
| `interp_tabsize` | function | `src/css.c:342` | `static int interp_tabsize(const char *v)` |
| `interp_text_overflow` | function | `src/css.c:440` | `static int interp_text_overflow(const char *v)` |
| `interp_text_rendering` | function | `src/css.c:740` | `static int interp_text_rendering(const char *v)` |
| `interp_textdeco` | function | `src/css.c:310` | `static int interp_textdeco(const char *v)` |
| `interp_textdeco_style` | function | `src/css.c:343` | `static int interp_textdeco_style(const char *v)` |
| `interp_textdeco_thickness` | function | `src/css.c:344` | `static int interp_textdeco_thickness(const char *v)` |
| `interp_texttransform` | function | `src/css.c:337` | `static int interp_texttransform(const char *v)` |
| `interp_time_ms` | function | `src/css.c:847` | `static int interp_time_ms(const char *v)` |
| `interp_touch_action` | function | `src/css.c:775` | `static int interp_touch_action(const char *v)` |
| `interp_transition_property` | function | `src/css.c:340` | `static int interp_transition_property(const char *v)` |
| `interp_user_select` | function | `src/css.c:533` | `static int interp_user_select(const char *v)` |
| `interp_visibility` | function | `src/css.c:385` | `static int interp_visibility(const char *v)` |
| `interp_weight` | function | `src/css.c:302` | `static int interp_weight(const char *v)` |
| `interp_whitespace` | function | `src/css.c:341` | `static int interp_whitespace(const char *v)` |
| `interp_word_break` | function | `src/css.c:446` | `static int interp_word_break(const char *v)` |
| `interpret_decls` | function | `src/css.c:3518` | `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,
               ...` |
| `interpret_prop` | function | `src/css.c:3333` | `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,
            ...` |
| `interpret_prop_dispatch` | function | `src/css.c:2722` | `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,
   ...` |
| `layer_register` | function | `src/css.c:3786` | `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,
                     ...` |
| `lp_can_be_nonneg` | function | `src/css.c:282` | `static int lp_can_be_nonneg(int px_val, int pct_pm)` |
| `matrix` | function | `src/css.c:1961` | `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands on ` |
| `next_ws_token` | function | `src/css.c:286` | `static int next_ws_token(const char **p, char *tok, size_t cap)` |
| `number` | function | `src/css.c:471` | `* number (no unit) as px (common in shorthand context like "10 5"). */
static int interp_border_s...` |
| `order` | function | `src/css.c:1216` | `* Lengths in declaration order (dx, dy, optional blur >= 0);` |
| `origin_component` | function | `src/css.c:2496` | `static int origin_component(const char *tok, int axis, int *out)` |
| `page_view` | function | `src/css.c:4464` | `* the generated text reaches page_view (which materialises it as a synthetic * run);` |
| `parent` | function | `src/css.c:4496` | `* property from the parent (`inherit`), and an unset non-inherited one
         * stands at its i...` |
| `parse_angle_deg` | function | `src/css.c:2299` | `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);` |
| `parse_block` | function | `src/css.c:3904` | `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                 ...` |
| `parse_color` | function | `src/css.c:174` | `static int parse_color(const char *v)` |
| `parse_matrix6` | function | `src/css.c:1991` | `static int parse_matrix6(const char *p, size_t argn, double m6[6])` |
| `parse_num` | function | `src/css.c:163` | `static int parse_num(const char *s, double *out, const char **endp)` |
| `property` | function | `src/css.c:2608` | `* error drops the whole property (fail closed). */
static int expand_clip(const char *val, css_de...` |
| `raw_add` | function | `src/css.c:3405` | `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)` |
| `rem_emit_px` | function | `src/css.c:4174` | `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)` |
| `rem_ident_ch` | function | `src/css.c:4156` | `static int rem_ident_ch(char c)` |
| `rem_num_starts_after` | function | `src/css.c:4164` | `static int rem_num_starts_after(char prev)` |
| `rem_rebase` | function | `src/css.c:4204` | `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)` |
| `resolve_core` | function | `src/css.c:5030` | `static css_style resolve_core(const css_sheet *sheet, const css_element *el,
                    ...` |
| `selector_matches_root` | function | `src/css.c:1824` | `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m)` |
| `sentinel` | function | `src/css.c:2944` | `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);` |
| `sheet_rewind` | function | `src/css.c:4271` | `static void sheet_rewind(css_sheet *sh)` |
| `sheet_root_font_px` | function | `src/css.c:4314` | `static double sheet_root_font_px(const css_sheet *sh)` |
| `shorthand` | function | `src/css.c:2651` | `* generic bucket keeps the rest of the shorthand (same net effect as the
 * font-family longhand ...` |
| `skip_at_rule` | function | `src/css.c:3649` | `static size_t skip_at_rule(const char *s, size_t i, size_t n)` |
| `slots` | function | `src/css.c:2832` | `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return emit_len(dst, ` |
| `split_top_args` | function | `src/css.c:2023` | `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,
               ...` |
| `strip_comments` | function | `src/css.c:4322` | `static char *strip_comments(const char *text, size_t len, size_t *outlen)` |
| `strip_important` | function | `src/css.c:1777` | `static int strip_important(char *val)` |
| `supports_matches` | function | `src/css.c:3732` | `static int supports_matches(const char *s, size_t a, size_t b)` |
| `supports_selector_ok` | function | `src/css.c:3723` | `static int supports_selector_ok(void *ctx, const char *sel)` |
| `text` | function | `src/css.c:243` | `* source text (rem_rebase, see below) rather than by threading a context here.
 *
 * Viewport uni...` |
| `through` | function | `src/css.c:194` | `* at the two SHARED chokepoints every property funnels through (the generic
 * dispatch tail, and...` |
| `tr_decompose` | function | `src/css.c:1968` | `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,
                        in...` |
| `tr_mul` | function | `src/css.c:1948` | `static void tr_mul(double out[6], const double l[6], const double r[6])` |
| `translate3d` | function | `src/css.c:2053` | `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine
 * renders z as nothing,...` |
| `translate3d` | function | `src/css.c:2303` | `* translate3d()/translateZ() flatten to their 2D projection. Any other
 * transform function (per...` |
| `translateX` | function | `src/css.c:2295` | `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc numbers ` |
| `var` | function | `src/css.c:1802` | `* cvr_resolve then substitutes var() references when a declaration's value is
 * interpreted (par...` |
| `var` | function | `src/css.c:4332` | `* collected and forty var() declarations -- font sizes, widths, radii, the
     * whole theme -- ...` |
| `wide_claim` | function | `src/css.c:3293` | `static int wide_claim(const char *prop, css_decl *dst, int cap,
                      char (*urlt...` |
| `CAR_TEXT_MAX` | macro | `src/css_atrule.c:13` | `#define CAR_TEXT_MAX` |
| `car_effective_spec` | function | `src/css_atrule.c:171` | `int car_effective_spec(int spec, int layer, int important)` |
| `car_layer_rank` | function | `src/css_atrule.c:148` | `int car_layer_rank(car_layers *L, const char *name, size_t len)` |
| `car_supports` | function | `src/css_atrule.c:141` | `int car_supports(const char *s, size_t a, size_t b, const car_ops *ops)` |
| `close_paren` | function | `src/css_atrule.c:33` | `static size_t close_paren(const char *s, size_t open, size_t b)` |
| `copy_trimmed` | function | `src/css_atrule.c:54` | `static int copy_trimmed(const char *s, size_t a, size_t b, char *dst, size_t cap, int lower)` |
| `eval_condition` | function | `src/css_atrule.c:114` | `static int eval_condition(const char *s, size_t a, size_t b, const car_ops *ops,
                ...` |
| `eval_declaration` | function | `src/css_atrule.c:68` | `static int eval_declaration(const char *s, size_t a, size_t b, const car_ops *ops, int *ok)` |
| `eval_in_parens` | function | `src/css_atrule.c:85` | `static int eval_in_parens(const char *s, size_t *i, size_t b, const car_ops *ops,
               ...` |
| `keyword_at` | function | `src/css_atrule.c:23` | `static int keyword_at(const char *s, size_t i, size_t b, const char *kw)` |
| `skip_ws` | function | `src/css_atrule.c:17` | `static size_t skip_ws(const char *s, size_t i, size_t b)` |
| `AUTO_REJECT` | macro | `src/css_box.c:932` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css_box.c:934` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css_box.c:938` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css_box.c:933` | `#define AUTO_VALUE` |
| `CSS_CALC_MAX_DEPTH` | macro | `src/css_box.c:460` | `#define CSS_CALC_MAX_DEPTH` |
| `CSS_MATHFN_MAX_ARGS` | macro | `src/css_box.c:464` | `#define CSS_MATHFN_MAX_ARGS` |
| `accepts` | function | `src/css_box.c:452` | `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further than` |
| `calc_eval` | function | `src/css_box.c:711` | `static int calc_eval(const char *v, size_t vlen, double *out_px)` |
| `calc_eval_em` | function | `src/css_box.c:718` | `static int calc_eval_em(const char *v, size_t vlen, double *out_em)` |
| `calc_eval_full` | function | `src/css_box.c:695` | `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,
           ...` |
| `calc_expr` | function | `src/css_box.c:676` | `static int calc_expr(calc_parser *p, calc_val *out, int depth)` |
| `calc_match_fn` | function | `src/css_box.c:489` | `static int calc_match_fn(calc_parser *p, const char *name)` |
| `calc_mathfn` | function | `src/css_box.c:531` | `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` |
| `calc_parser` | struct | `src/css_box.c:480` | `` |
| `calc_piecewise` | function | `src/css_box.c:516` | `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)` |
| `calc_skip_ws` | function | `src/css_box.c:482` | `static void calc_skip_ws(calc_parser *p)` |
| `calc_term` | function | `src/css_box.c:652` | `static int calc_term(calc_parser *p, calc_val *out, int depth)` |
| `calc_unwrap` | function | `src/css_box.c:726` | `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` |
| `calc_val` | struct | `src/css_box.c:479` | `` |
| `cb_copy_trim` | function | `src/css_box.c:25` | `static size_t cb_copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `cb_expand_box2` | function | `src/css_box.c:1106` | `int cb_expand_box2(const char *val, int slot_start, int slot_end,
                       int allo...` |
| `cb_expand_grid_template_cols` | function | `src/css_box.c:430` | `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `cb_interp_align` | function | `src/css_box.c:54` | `int cb_interp_align(const char *v)` |
| `cb_interp_display` | function | `src/css_box.c:176` | `int cb_interp_display(const char *v)` |
| `cb_interp_gap` | function | `src/css_box.c:251` | `int cb_interp_gap(const char *v)` |
| `cb_interp_justify` | function | `src/css_box.c:258` | `int cb_interp_justify(const char *v)` |
| `cb_interp_len` | function | `src/css_box.c:744` | `int cb_interp_len(const char *v, int allow_auto, int *out)` |
| `cb_interp_lineheight` | function | `src/css_box.c:116` | `int cb_interp_lineheight(const char *v)` |
| `cb_interp_lp` | function | `src/css_box.c:859` | `int cb_interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_px, ...` |
| `cb_interp_style` | function | `src/css_box.c:146` | `int cb_interp_style(const char *v)` |
| `cb_interp_textdeco` | function | `src/css_box.c:156` | `int cb_interp_textdeco(const char *v)` |
| `cb_interp_weight` | function | `src/css_box.c:137` | `int cb_interp_weight(const char *v)` |
| `cb_length_px` | function | `src/css_box.c:49` | `int cb_length_px(const char *v, double *px)` |
| `cb_parse_num` | function | `src/css_box.c:13` | `static int cb_parse_num(const char *s, double *out, const char **endp)` |
| `cb_starts_with_ci` | function | `src/css_box.c:283` | `static int cb_starts_with_ci(const char *s, const char *pre)` |
| `cb_value_em_milli` | function | `src/css_box.c:839` | `int cb_value_em_milli(const char *v)` |
| `cb_wide_keyword` | function | `src/css_box.c:18` | `static int cb_wide_keyword(const char *v)` |
| `count_one_repeat` | function | `src/css_box.c:327` | `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,
                      ...` |
| `count_tracks` | function | `src/css_box.c:289` | `static int count_tracks(const char *s, size_t n)` |
| `interp_len` | function | `src/css_box.c:1035` | `* this file that might hand a token to interp_len (transitively: margin/padding/
 * inset, flex-b...` |
| `min` | function | `src/css_box.c:550` | `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the element to` |
| `pct_slot_of` | function | `src/css_box.c:789` | `static int pct_slot_of(int slot)` |
| `px` | type_alias | `src/css_box.c:479` | `typedef struct calc_val { double px;` |
| `repeat` | function | `src/css_box.c:272` | `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill\|...) / repeat(auto-fit\` |
| `term` | function | `src/css_box.c:866` | `* the same expression and failed closed on the percentage term (its property * may not accept one);` |
| `track_size_of` | function | `src/css_box.c:297` | `static int track_size_of(const char *tok)` |
| `walk_tracks` | function | `src/css_box.c:370` | `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)` |
| `CCH_ATTR_BUF` | macro | `src/css_chain.c:19` | `#define CCH_ATTR_BUF` |
| `CCH_CLASS_BUF` | macro | `src/css_chain.c:16` | `#define CCH_CLASS_BUF` |
| `CCH_ID_MAX` | macro | `src/css_chain.c:15` | `#define CCH_ID_MAX` |
| `CCH_MAX_ATTRS` | macro | `src/css_chain.c:18` | `#define CCH_MAX_ATTRS` |
| `CCH_MAX_CLASSES` | macro | `src/css_chain.c:17` | `#define CCH_MAX_CLASSES` |
| `CCH_TAG_MAX` | macro | `src/css_chain.c:14` | `#define CCH_TAG_MAX` |
| `cch_element_matches` | function | `src/css_chain.c:292` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)` |
| `cch_element_style` | function | `src/css_chain.c:288` | `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)` |
| `cch_element_style_vars` | function | `src/css_chain.c:246` | `css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,
                 ...` |
| `cch_node` | struct | `src/css_chain.c:23` | `` |
| `cch_pseudo_style` | function | `src/css_chain.c:273` | `css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,
            ...` |
| `count_children` | function | `src/css_chain.c:179` | `static int count_children(lxb_dom_node_t *n)` |
| `fill_css_node` | function | `src/css_chain.c:35` | `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)` |
| `inputs` | function | `src/css_chain.c:193` | `* identical inputs (single source of truth). */
static const css_element *build_chain(lxb_dom_ele...` |
| `sibling_position` | function | `src/css_chain.c:133` | `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `sibling_type_position` | function | `src/css_chain.c:151` | `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `tag` | type_alias | `src/css_chain.c:23` | `typedef struct cch_node { char tag[CCH_TAG_MAX];` |
| `CC_CHANNEL_MAX` | macro | `src/css_color.c:22` | `#define CC_CHANNEL_MAX` |
| `CC_HSL_SCALE` | macro | `src/css_color.c:31` | `#define CC_HSL_SCALE` |
| `CC_NUMBER_MAX_DIGITS` | macro | `src/css_color.c:28` | `#define CC_NUMBER_MAX_DIGITS` |
| `CC_PERCENT_MAX` | macro | `src/css_color.c:23` | `#define CC_PERCENT_MAX` |
| `CC_PI` | macro | `src/css_color.c:463` | `#define CC_PI` |
| `CC_TOKEN_MAX` | macro | `src/css_color.c:19` | `#define CC_TOKEN_MAX` |
| `ascii_lower` | function | `src/css_color.c:118` | `static int ascii_lower(int c)` |
| `cc_named` | struct | `src/css_color.c:33` | `` |
| `cc_pack` | function | `src/css_color.c:623` | `int cc_pack(cc_rgb c)` |
| `cc_parse` | function | `src/css_color.c:583` | `cc_status cc_parse(const char *token, cc_rgb *out)` |
| `cc_round` | function | `src/css_color.c:215` | `static long cc_round(double v)` |
| `cc_unpack` | function | `src/css_color.c:627` | `cc_rgb cc_unpack(int packed)` |
| `hex_val` | function | `src/css_color.c:122` | `static int hex_val(int c)` |
| `lab_comp` | function | `src/css_color.c:467` | `static int lab_comp(const char *b, const char *e, double pct_ref, int is_hue, double *out)` |
| `lab_to_rgb` | function | `src/css_color.c:513` | `static void lab_to_rgb(double L, double a, double b, cc_rgb *out)` |
| `named_cmp` | function | `src/css_color.c:567` | `static int named_cmp(const void *key, const void *element)` |
| `normalize` | function | `src/css_color.c:131` | `static int normalize(const char *token, char *out)` |
| `oklab_to_rgb` | function | `src/css_color.c:502` | `static void oklab_to_rgb(double L, double a, double b, cc_rgb *out)` |
| `parse_component` | function | `src/css_color.c:220` | `static int parse_component(const char *b, const char *e, int is_alpha, int *out)` |
| `parse_func` | function | `src/css_color.c:397` | `static int parse_func(const char *s, cc_rgb *out)` |
| `parse_hex` | function | `src/css_color.c:145` | `static int parse_hex(const char *s, cc_rgb *out)` |
| `parse_hsl_comp` | function | `src/css_color.c:253` | `static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out)` |
| `parse_lab_family` | function | `src/css_color.c:529` | `static int parse_lab_family(const char *s, cc_rgb *out)` |
| `parse_named` | function | `src/css_color.c:573` | `static int parse_named(const char *s, cc_rgb *out)` |
| `span` | function | `src/css_color.c:325` | `* span (when a slash is present) into ab/ae, and returns the component count,
 * or -1. Bounded: ...` |
| `srgb_encode` | function | `src/css_color.c:495` | `static unsigned char srgb_encode(double lin)` |
| `strncmp` | function | `src/css_color.c:598` | `strncmp(buf, "oklab(", 6) == 0 \|\| strncmp(buf, "oklch(", 6) == 0)` |
| `CSS_GRAD_STOPS_MAX` | function | `src/css_gradient.c:183` | `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when
 * the gradient fai...` |
| `bg_layer_tokens_ok` | function | `src/css_gradient.c:458` | `static int bg_layer_tokens_ok(const char *s)` |
| `cg_expand_background` | function | `src/css_gradient.c:498` | `int cg_expand_background(const char *val, css_decl *dst, int cap,
                             ch...` |
| `cg_parse_num` | function | `src/css_gradient.c:12` | `static int cg_parse_num(const char *s, double *out, const char **endp)` |
| `cg_wide_keyword` | function | `src/css_gradient.c:17` | `static int cg_wide_keyword(const char *v)` |
| `conic_prelude` | function | `src/css_gradient.c:110` | `static int conic_prelude(const char *seg, int *angle)` |
| `declaration` | function | `src/css_gradient.c:451` | `* declaration (fail closed);` |
| `downstream` | function | `src/css_gradient.c:392` | `* happens downstream (render_doc.c), gated by caps.images like an <img>. */
int cg_expand_bg_imag...` |
| `emit_gradient` | function | `src/css_gradient.c:290` | `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,
                         ...` |
| `find_gradient_call` | function | `src/css_gradient.c:76` | `static int find_gradient_call(const char *v, const char *fn, size_t *start,
                     ...` |
| `find_radial_gradient` | function | `src/css_gradient.c:347` | `static int find_radial_gradient(const char *v, size_t *start, size_t *end,
                      ...` |
| `grad_stop_pos` | function | `src/css_gradient.c:152` | `static int grad_stop_pos(const char *pp, int conic, const char **endp)` |
| `gradient` | function | `src/css_gradient.c:27` | `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,
 * the whole decl...` |
| `pool` | function | `src/css_gradient.c:388` | `* pool (gradient explicitly reset);` |
| `CL_PX_PER_IN` | macro | `src/css_length.c:21` | `#define CL_PX_PER_IN` |
| `cl_ctx_initial` | function | `src/css_length.c:100` | `cl_ctx cl_ctx_initial(void)` |
| `cl_em_refit` | function | `src/css_length.c:219` | `double cl_em_refit(double px, double em, double from_font_size, double font_size)` |
| `cl_font_size` | function | `src/css_length.c:56` | `static double cl_font_size(const cl_ctx *ctx)` |
| `cl_is_length_unit` | function | `src/css_length.c:167` | `int cl_is_length_unit(const char *unit, size_t unit_len)` |
| `cl_lp_used` | function | `src/css_length.c:395` | `double cl_lp_used(cl_lp lp, double basis)` |
| `cl_metric_or` | function | `src/css_length.c:67` | `static double cl_metric_or(double measured, double ratio, const cl_ctx *ctx)` |
| `cl_number` | function | `src/css_length.c:292` | `int cl_number(const char *s, double *out, const char **endp)` |
| `cl_parse_number` | function | `src/css_length.c:233` | `static int cl_parse_number(const char **pp, const char *end, double *out)` |
| `cl_resolve` | function | `src/css_length.c:377` | `cl_status cl_resolve(const char *value, const cl_ctx *ctx, double *out_px)` |
| `cl_resolve_core` | function | `src/css_length.c:309` | `static cl_status cl_resolve_core(const char *value, const cl_ctx *ctx, cl_lp *out)` |
| `cl_resolve_lp` | function | `src/css_length.c:391` | `cl_status cl_resolve_lp(const char *value, const cl_ctx *ctx, cl_lp *out)` |
| `cl_root_font_size` | function | `src/css_length.c:60` | `static double cl_root_font_size(const cl_ctx *ctx)` |
| `cl_unit_eq` | function | `src/css_length.c:30` | `static int cl_unit_eq(const char *unit, size_t len, const char *lit)` |
| `cl_unit_is_font_relative` | function | `src/css_length.c:174` | `int cl_unit_is_font_relative(const char *unit, size_t unit_len)` |
| `cl_unit_scale` | function | `src/css_length.c:117` | `cl_status cl_unit_scale(const char *unit, size_t unit_len,
                        const cl_ctx *...` |
| `cl_viewport_scale` | function | `src/css_length.c:80` | `static int cl_viewport_scale(const char *u, size_t len, const cl_ctx *ctx, double *per)` |
| `know` | function | `src/css_length.c:7` | `* this module cannot know (real font metrics, the viewport) arrives through
 * cl_ctx rather than...` |
| `CMQ_CM_PER_IN` | macro | `src/css_mq.c:23` | `#define CMQ_CM_PER_IN` |
| `CMQ_COLOR_BITS` | macro | `src/css_mq.c:21` | `#define CMQ_COLOR_BITS` |
| `CMQ_DEVICE_H` | macro | `src/css_mq.c:19` | `#define CMQ_DEVICE_H` |
| `CMQ_DEVICE_W` | macro | `src/css_mq.c:18` | `#define CMQ_DEVICE_W` |
| `CMQ_DPI_PER_DPPX` | macro | `src/css_mq.c:22` | `#define CMQ_DPI_PER_DPPX` |
| `CMQ_DPPX` | macro | `src/css_mq.c:20` | `#define CMQ_DPPX` |
| `MQ_EPS` | macro | `src/css_mq.c:203` | `#define MQ_EPS` |
| `and3` | function | `src/css_mq.c:66` | `static int and3(int a, int b)` |
| `bool_ctx` | function | `src/css_mq.c:229` | `static int bool_ctx(const fval *v)` |
| `cmp_op` | function | `src/css_mq.c:206` | `static int cmp_op(double lhs, int op, double rhs)` |
| `cmq_matches` | function | `src/css_mq.c:458` | `int cmq_matches(const char *s, size_t len, const cmq_env *env)` |
| `copy_trim_lower` | function | `src/css_mq.c:83` | `static int copy_trim_lower(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `eval_cond` | function | `src/css_mq.c:380` | `static int eval_cond(mq_cur *c, int depth)` |
| `eval_feature` | function | `src/css_mq.c:328` | `static int eval_feature(const char *s, size_t a, size_t b, const cmq_env *env)` |
| `eval_in_parens` | function | `src/css_mq.c:353` | `static int eval_in_parens(mq_cur *c, int depth)` |
| `eval_plain` | function | `src/css_mq.c:237` | `static int eval_plain(const char *name, const char *value, const cmq_env *env)` |
| `eval_query` | function | `src/css_mq.c:404` | `static int eval_query(const char *s, size_t a, size_t b, const cmq_env *env)` |
| `eval_range` | function | `src/css_mq.c:280` | `static int eval_range(const char *t, const cmq_env *env)` |
| `feature_of` | function | `src/css_mq.c:106` | `static fval feature_of(const char *name, const cmq_env *env)` |
| `flip_op` | function | `src/css_mq.c:218` | `static int flip_op(int op)` |
| `fval` | struct | `src/css_mq.c:96` | `` |
| `is_ident_ch` | function | `src/css_mq.c:39` | `static int is_ident_ch(char c)` |
| `is_space` | function | `src/css_mq.c:35` | `static int is_space(char c)` |
| `kind` | type_alias | `src/css_mq.c:95` | `typedef struct fval { fv_kind kind;` |
| `lower_ch` | function | `src/css_mq.c:31` | `static char lower_ch(char c)` |
| `mq_cur` | struct | `src/css_mq.c:25` | `` |
| `not3` | function | `src/css_mq.c:78` | `static int not3(int a)` |
| `or3` | function | `src/css_mq.c:72` | `static int or3(int a, int b)` |
| `parse_value` | function | `src/css_mq.c:167` | `static int parse_value(const char *t, int unit, double *out)` |
| `peek_word` | function | `src/css_mq.c:61` | `static int peek_word(const mq_cur *c, char *w, size_t cap)` |
| `read_num` | function | `src/css_mq.c:162` | `static int read_num(const char *t, double *out, const char **end)` |
| `read_op` | function | `src/css_mq.c:266` | `static int read_op(const char **p)` |
| `read_word` | function | `src/css_mq.c:49` | `static int read_word(mq_cur *c, char *w, size_t cap)` |
| `skip_ws` | function | `src/css_mq.c:44` | `static void skip_ws(mq_cur *c)` |
| `HAS_MAX_DEPTH` | macro | `src/css_select.c:839` | `#define HAS_MAX_DEPTH` |
| `attr_matches` | function | `src/css_select.c:688` | `static int attr_matches(const css_attr_match *am, const css_element *el)` |
| `between` | function | `src/css_select.c:376` | `* between ( and ) is split on commas (not inside [] or ());` |
| `built` | function | `src/css_select.c:1014` | `* chains the caller built (an element without parent/prev links never matches
 * through that com...` |
| `compound_matches` | function | `src/css_select.c:979` | `static int compound_matches(const css_compound *c, const css_element *el,
                       ...` |
| `csel_decl_end` | function | `src/css_select.c:104` | `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace)` |
| `csel_emit_utf8` | function | `src/css_select.c:30` | `size_t csel_emit_utf8(unsigned int cp, char *out)` |
| `csel_escape_len` | function | `src/css_select.c:91` | `size_t csel_escape_len(const char *s, size_t i, size_t b)` |
| `csel_hex_val` | function | `src/css_select.c:23` | `int csel_hex_val(char c)` |
| `csel_ident_eq` | function | `src/css_select.c:142` | `int csel_ident_eq(const char *stored, const char *tok, size_t tlen)` |
| `csel_ident_fold` | function | `src/css_select.c:127` | `void csel_ident_fold(const char *src, size_t len, char *dst)` |
| `csel_matches` | function | `src/css_select.c:1055` | `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,
              ...` |
| `csel_read_ident` | function | `src/css_select.c:150` | `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower)` |
| `csel_unescape` | function | `src/css_select.c:52` | `void csel_unescape(char *dst, size_t cap, const char *src, size_t n)` |
| `el_attr_value` | function | `src/css_select.c:655` | `static const char *el_attr_value(const css_element *el, const char *name)` |
| `ends_with` | function | `src/css_select.c:665` | `static int ends_with(const char *v, const char *suf, int ci)` |
| `has_word` | function | `src/css_select.c:673` | `static int has_word(const char *v, const char *w, int ci)` |
| `ident_hash` | function | `src/css_select.c:121` | `static unsigned long long ident_hash(const char *s, size_t n)` |
| `is_form_control` | function | `src/css_select.c:717` | `static int is_form_control(const char *tag)` |
| `nth_matches` | function | `src/css_select.c:708` | `static int nth_matches(int A, int B, int idx)` |
| `parse_attr_sel` | function | `src/css_select.c:184` | `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)` |
| `parse_compound` | function | `src/css_select.c:517` | `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,
                  ...` |
| `parse_nth_arg` | function | `src/css_select.c:241` | `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)` |
| `parse_sub_compound` | function | `src/css_select.c:452` | `static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub)` |
| `pseudo_matches` | function | `src/css_select.c:726` | `static int pseudo_matches(const css_pseudo_match *pm, const css_element *el, const css_sel *sel, const char *target_id, ` |
| `selector` | function | `src/css_select.c:559` | `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is
 * dropped. Whitespa...` |
| `simple_pseudo_kind` | function | `src/css_select.c:431` | `static int simple_pseudo_kind(const char *nm)` |
| `sub_sel_matches` | function | `src/css_select.c:730` | `static int sub_sel_matches(const css_sub_sel *sub, const css_element *el)` |
| `take_sub_arg` | function | `src/css_select.c:293` | `static int take_sub_arg(const char *s, size_t a, size_t b, css_sel *sel, int strict);` |
| `ct_emit_spacing` | function | `src/css_text.c:300` | `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `ct_expand_shadow` | function | `src/css_text.c:313` | `int ct_expand_shadow(const char *val, css_decl *dst, int cap)` |
| `ct_expand_valign` | function | `src/css_text.c:122` | `int ct_expand_valign(const char *val, css_decl *dst, int cap)` |
| `ct_family_of` | function | `src/css_text.c:18` | `static int ct_family_of(const char *name)` |
| `ct_interp_aspect_ratio` | function | `src/css_text.c:194` | `int ct_interp_aspect_ratio(const char *v, int *num, int *den)` |
| `ct_interp_direction` | function | `src/css_text.c:227` | `int ct_interp_direction(const char *v)` |
| `ct_interp_fontfamily` | function | `src/css_text.c:47` | `int ct_interp_fontfamily(const char *v)` |
| `ct_interp_liststyle` | function | `src/css_text.c:265` | `int ct_interp_liststyle(const char *v)` |
| `ct_interp_tabsize` | function | `src/css_text.c:160` | `int ct_interp_tabsize(const char *v)` |
| `ct_interp_textdeco_style` | function | `src/css_text.c:171` | `int ct_interp_textdeco_style(const char *v)` |
| `ct_interp_textdeco_thickness` | function | `src/css_text.c:182` | `int ct_interp_textdeco_thickness(const char *v)` |
| `ct_interp_texttransform` | function | `src/css_text.c:69` | `int ct_interp_texttransform(const char *v)` |
| `ct_interp_transition_property` | function | `src/css_text.c:139` | `int ct_interp_transition_property(const char *v)` |
| `ct_interp_valign` | function | `src/css_text.c:91` | `int ct_interp_valign(const char *v)` |
| `ct_interp_whitespace` | function | `src/css_text.c:147` | `int ct_interp_whitespace(const char *v)` |
| `ct_liststyle_kw` | function | `src/css_text.c:233` | `static int ct_liststyle_kw(const char *t)` |
| `ct_liststyle_unknown_name` | function | `src/css_text.c:254` | `static int ct_liststyle_unknown_name(const char *t)` |
| `cv_bg_alpha_of` | function | `src/css_values.c:46` | `int cv_bg_alpha_of(const char *v)` |
| `cv_color_ok` | function | `src/css_values.c:41` | `int cv_color_ok(int c)` |
| `cv_interp_bg` | function | `src/css_values.c:160` | `int cv_interp_bg(const char *v)` |
| `cv_interp_color` | function | `src/css_values.c:36` | `int cv_interp_color(const char *v)` |
| `cv_parse_color` | function | `src/css_values.c:16` | `int cv_parse_color(const char *v)` |
| `cv_parse_num` | function | `src/css_values.c:11` | `static int cv_parse_num(const char *s, double *out, const char **endp)` |
| `cvr_collect_decls` | function | `src/css_vars.c:139` | `void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b)` |
| `cvr_count` | function | `src/css_vars.c:100` | `size_t cvr_count(const cvr_table *t)` |
| `cvr_free` | function | `src/css_vars.c:112` | `void cvr_free(cvr_table *t)` |
| `cvr_get` | function | `src/css_vars.c:94` | `const char *cvr_get(const cvr_table *t, const char *name, size_t nlen)` |
| `cvr_lookup` | function | `src/css_vars.c:239` | `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen)` |
| `cvr_reset` | function | `src/css_vars.c:102` | `void cvr_reset(cvr_table *t)` |
| `cvr_resolve` | function | `src/css_vars.c:230` | `int cvr_resolve(const char *val, char *out, size_t outcap, const cvr_scope *sc)` |
| `cvr_set` | function | `src/css_vars.c:67` | `int cvr_set(cvr_table *t, const char *name, size_t nlen, const char *value, size_t vlen)` |
| `dup_n` | function | `src/css_vars.c:21` | `static char *dup_n(const char *s, size_t n)` |
| `find_slot` | function | `src/css_vars.c:32` | `static size_t find_slot(const cvr_table *t, const char *name, size_t nlen)` |
| `grow` | function | `src/css_vars.c:45` | `static int grow(cvr_table *t)` |
| `is_ws` | function | `src/css_vars.c:120` | `static int is_ws(char c)` |
| `name_hash` | function | `src/css_vars.c:12` | `static size_t name_hash(const char *s, size_t n)` |
| `resolve_rec` | function | `src/css_vars.c:178` | `static int resolve_rec(const char *val, size_t vlen, char *out, size_t outcap,
                  ...` |
| `scope_get` | function | `src/css_vars.c:164` | `static const char *scope_get(const cvr_scope *sc, const char *name, size_t nlen)` |
| `without_important` | function | `src/css_vars.c:124` | `static size_t without_important(const char *val, size_t n)` |
| `ascii_ws` | function | `src/data_url.c:115` | `static int ascii_ws(char c)` |
| `b64_val` | function | `src/data_url.c:61` | `static int b64_val(unsigned char c)` |
| `ci_starts_with` | function | `src/data_url.c:20` | `static int ci_starts_with(const char *s, const char *prefix)` |
| `du_base64_decode` | function | `src/data_url.c:70` | `du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len)` |
| `du_base64_payload` | function | `src/data_url.c:32` | `du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len)` |
| `du_decode` | function | `src/data_url.c:131` | `du_status du_decode(const char *url, char *mime, size_t mime_cap, uint8_t **out, size_t *out_len)` |
| `du_is_data_url` | function | `src/data_url.c:28` | `int du_is_data_url(const char *url)` |
| `ends_ci` | function | `src/data_url.c:120` | `static int ends_ci(const char *s, size_t n, const char *suf)` |
| `hexval` | function | `src/data_url.c:108` | `static int hexval(char c)` |
| `lower` | function | `src/data_url.c:16` | `static int lower(char c)` |
| `_POSIX_C_SOURCE` | macro | `src/disk_store.c:11` | `#define _POSIX_C_SOURCE` |
| `ds_free` | function | `src/disk_store.c:136` | `void ds_free(uint8_t *buf, size_t len)` |
| `ds_read` | function | `src/disk_store.c:103` | `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],
                  uint8_t **ou...` |
| `ds_write` | function | `src/disk_store.c:66` | `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,
               ...` |
| `fsync_dir` | function | `src/disk_store.c:32` | `static void fsync_dir(const char *path)` |
| `map_ls` | function | `src/disk_store.c:50` | `static ds_status map_ls(ls_status s)` |
| `DOM_QS_MAX_SELECTORS` | macro | `src/dom.c:380` | `#define DOM_QS_MAX_SELECTORS` |
| `IH_BLOCK_SIZE` | macro | `src/dom.c:818` | `#define IH_BLOCK_SIZE` |
| `_POSIX_C_SOURCE` | macro | `src/dom.c:11` | `#define _POSIX_C_SOURCE` |
| `char_kind` | function | `src/dom.c:981` | `static int char_kind(const lxb_dom_node_t *n)` |
| `copy_ids` | function | `src/dom.c:354` | `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)` |
| `count` | function | `src/dom.c:437` | `* count (may exceed cap), and returns DOM_NODE_NONE. */
static dom_node_id qs_walk(const dom_inde...` |
| `dom_append_child` | function | `src/dom.c:710` | `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)` |
| `dom_attribute_names` | function | `src/dom.c:586` | `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,
                           con...` |
| `dom_build` | function | `src/dom.c:291` | `dom_status dom_build(const hp_document *doc, dom_index **out)` |
| `dom_child_node` | function | `src/dom.c:1004` | `dom_node_id dom_child_node(dom_index *idx, dom_node_id node, int last)` |
| `dom_clone_node` | function | `src/dom.c:934` | `dom_status dom_clone_node(dom_index *idx, dom_node_id node, int deep, dom_node_id *out_id)` |
| `dom_closest` | function | `src/dom.c:496` | `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,
                        const cha...` |
| `dom_create_char_node` | function | `src/dom.c:1018` | `dom_status dom_create_char_node(dom_index *idx, int kind, const char *text, size_t len,
         ...` |
| `dom_create_element` | function | `src/dom.c:690` | `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)` |
| `dom_document_position` | function | `src/dom.c:512` | `size_t dom_document_position(const dom_index *idx, dom_node_id node)` |
| `dom_document_title` | function | `src/dom.c:614` | `const char *dom_document_title(const dom_index *idx, size_t *len)` |
| `dom_first_child` | function | `src/dom.c:537` | `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)` |
| `dom_free` | function | `src/dom.c:332` | `void dom_free(dom_index *idx)` |
| `dom_get_attribute` | function | `src/dom.c:564` | `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,
                           ...` |
| `dom_get_by_class` | function | `src/dom.c:370` | `size_t dom_get_by_class(const dom_index *idx, const char *cls,
                        dom_node_i...` |
| `dom_get_by_tag` | function | `src/dom.c:361` | `size_t dom_get_by_tag(const dom_index *idx, const char *tag,
                      dom_node_id *o...` |
| `dom_get_element_by_id` | function | `src/dom.c:348` | `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)` |
| `dom_get_inner_html` | function | `src/dom.c:887` | `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,
                           ...` |
| `dom_index` | struct | `src/dom.c:220` | `` |
| `dom_insert_before` | function | `src/dom.c:917` | `dom_status dom_insert_before(dom_index *idx, dom_node_id parent, dom_node_id child,
             ...` |
| `dom_matches` | function | `src/dom.c:487` | `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)` |
| `dom_move_children` | function | `src/dom.c:948` | `dom_status dom_move_children(dom_index *idx, dom_node_id src, dom_node_id parent,
               ...` |
| `dom_next_sibling` | function | `src/dom.c:545` | `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)` |
| `dom_node_at` | function | `src/dom.c:522` | `dom_node_id dom_node_at(const dom_index *idx, size_t position)` |
| `dom_node_count` | function | `src/dom.c:344` | `size_t dom_node_count(const dom_index *idx)` |
| `dom_node_kind` | function | `src/dom.c:1000` | `int dom_node_kind(const dom_index *idx, dom_node_id node)` |
| `dom_parent` | function | `src/dom.c:527` | `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)` |
| `dom_precedes` | function | `src/dom.c:517` | `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)` |
| `dom_query_selector` | function | `src/dom.c:467` | `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,
                          ...` |
| `dom_query_selector_all` | function | `src/dom.c:476` | `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,
                           ...` |
| `dom_remove_attribute` | function | `src/dom.c:761` | `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)` |
| `dom_remove_child` | function | `src/dom.c:724` | `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)` |
| `dom_set_attribute` | function | `src/dom.c:732` | `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,
                             const...` |
| `dom_set_document_title` | function | `src/dom.c:661` | `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)` |
| `dom_set_inner_html` | function | `src/dom.c:780` | `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,
                              con...` |
| `dom_set_text_content` | function | `src/dom.c:627` | `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,
                               ...` |
| `dom_sibling_node` | function | `src/dom.c:1011` | `dom_node_id dom_sibling_node(dom_index *idx, dom_node_id node, int prev)` |
| `dom_tag_name` | function | `src/dom.c:553` | `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)` |
| `dom_text_content` | function | `src/dom.c:604` | `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)` |
| `handle_of` | function | `src/dom.c:992` | `static dom_node_id handle_of(dom_index *idx, lxb_dom_node_t *n)` |
| `id_of` | function | `src/dom.c:383` | `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)` |
| `idx_push` | function | `src/dom.c:672` | `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)` |
| `ih_acc` | struct | `src/dom.c:825` | `` |
| `ih_append` | function | `src/dom.c:833` | `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)` |
| `ih_block` | struct | `src/dom.c:820` | `` |
| `ih_free` | function | `src/dom.c:860` | `static void ih_free(ih_acc *a)` |
| `index_element` | function | `src/dom.c:254` | `static int index_element(dom_index *idx, lxb_dom_element_t *el, dom_node_id id)` |
| `index_subtree` | function | `src/dom.c:770` | `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)` |
| `node_matches_any` | function | `src/dom.c:426` | `static int node_matches_any(const lxb_dom_node_t *cn,
                            const css_sel *...` |
| `node_next` | function | `src/dom.c:232` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `parse_selector_list` | function | `src/dom.c:393` | `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)` |
| `pm_entry` | struct | `src/dom.c:154` | `` |
| `pm_free` | function | `src/dom.c:211` | `static void pm_free(ptrmap *m)` |
| `pm_get` | function | `src/dom.c:200` | `static int pm_get(const ptrmap *m, const void *key, dom_node_id *out)` |
| `pm_grow` | function | `src/dom.c:166` | `static int pm_grow(ptrmap *m)` |
| `pm_put` | function | `src/dom.c:183` | `static int pm_put(ptrmap *m, const void *key, dom_node_id id)` |
| `ptr_hash` | function | `src/dom.c:45` | `static size_t ptr_hash(const void *p)` |
| `ptrmap` | struct | `src/dom.c:160` | `` |
| `sm_entry` | struct | `src/dom.c:55` | `` |
| `sm_entry_append` | function | `src/dom.c:70` | `static int sm_entry_append(sm_entry *e, dom_node_id id)` |
| `sm_find` | function | `src/dom.c:127` | `static const sm_entry *sm_find(const strmap *m, const char *key, size_t klen)` |
| `sm_free` | function | `src/dom.c:139` | `static void sm_free(strmap *m)` |
| `sm_grow` | function | `src/dom.c:82` | `static int sm_grow(strmap *m)` |
| `sm_put` | function | `src/dom.c:99` | `static int sm_put(strmap *m, const char *key, size_t klen, dom_node_id id)` |
| `strmap` | struct | `src/dom.c:64` | `` |
| `to_lower_buf` | function | `src/dom.c:33` | `static int to_lower_buf(const char *s, size_t n, char *out, size_t outcap)` |
| `valid` | function | `src/dom.c:242` | `static int valid(const dom_index *idx, dom_node_id n)` |
| `dd_align_name` | function | `src/dom_debug.c:108` | `static const char *dd_align_name(int a)` |
| `dd_block_line` | function | `src/dom_debug.c:304` | `static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b)` |
| `dd_border_style_name` | function | `src/dom_debug.c:211` | `static const char *dd_border_style_name(int s)` |
| `dd_box_line` | function | `src/dom_debug.c:244` | `static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b)` |
| `dd_color` | function | `src/dom_debug.c:83` | `static void dd_color(dd_cursor *c, int rgb)` |
| `dd_cursor` | struct | `src/dom_debug.c:24` | `` |
| `dd_cursor_name` | function | `src/dom_debug.c:165` | `static const char *dd_cursor_name(int c)` |
| `dd_display_name` | function | `src/dom_debug.c:88` | `static const char *dd_display_name(int d)` |
| `dd_emit` | function | `src/dom_debug.c:36` | `static void dd_emit(dd_cursor *c, const char *s, size_t len)` |
| `dd_format` | function | `src/dom_debug.c:380` | `size_t dd_format(const rd_doc *doc, char *out, size_t cap)` |
| `dd_format_css` | function | `src/dom_debug.c:412` | `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)` |
| `dd_image_rendering_name` | function | `src/dom_debug.c:202` | `static const char *dd_image_rendering_name(int r)` |
| `dd_inset` | function | `src/dom_debug.c:187` | `static int dd_inset(int v)` |
| `dd_justify_name` | function | `src/dom_debug.c:96` | `static const char *dd_justify_name(int j)` |
| `dd_mix_blend_name` | function | `src/dom_debug.c:137` | `static const char *dd_mix_blend_name(int m)` |
| `dd_object_fit_name` | function | `src/dom_debug.c:191` | `static const char *dd_object_fit_name(int o)` |
| `dd_overflow_name` | function | `src/dom_debug.c:156` | `static const char *dd_overflow_name(int o)` |
| `dd_position_name` | function | `src/dom_debug.c:118` | `static const char *dd_position_name(int p)` |
| `dd_printf` | function | `src/dom_debug.c:48` | `static void dd_printf(dd_cursor *c, const char *fmt, ...)` |
| `dd_putc` | function | `src/dom_debug.c:31` | `static void dd_putc(dd_cursor *c, char ch)` |
| `dd_puts` | function | `src/dom_debug.c:40` | `static void dd_puts(dd_cursor *c, const char *s)` |
| `dd_text_overflow_name` | function | `src/dom_debug.c:182` | `static const char *dd_text_overflow_name(int t)` |
| `dd_visibility_name` | function | `src/dom_debug.c:129` | `static const char *dd_visibility_name(int v)` |
| `dd_w` | function | `src/dom_debug.c:80` | `static int dd_w(int v)` |
| `ci_find` | function | `src/download.c:19` | `static const char *ci_find(const char *hay, const char *needle)` |
| `copy_span` | function | `src/download.c:85` | `static void copy_span(const char *src, const char *end, char *buf, size_t bufsz)` |
| `dl_build_path` | function | `src/download.c:195` | `dl_status dl_build_path(const char *dir, const char *name, char *out, size_t outsz)` |
| `dl_check_size` | function | `src/download.c:213` | `dl_status dl_check_size(size_t len)` |
| `dl_ext_for_type` | function | `src/download.c:58` | `const char *dl_ext_for_type(const char *content_type)` |
| `dl_pick_name` | function | `src/download.c:153` | `dl_status dl_pick_name(const char *url, const char *content_disposition,
                       c...` |
| `dl_should_download` | function | `src/download.c:47` | `int dl_should_download(const char *content_type, const char *content_disposition)` |
| `extract_disposition_name` | function | `src/download.c:96` | `static int extract_disposition_name(const char *cd, char *buf, size_t bufsz)` |
| `extract_url_name` | function | `src/download.c:134` | `static int extract_url_name(const char *url, char *buf, size_t bufsz)` |
| `has_extension` | function | `src/download.c:148` | `static int has_extension(const char *name)` |
| `lc` | function | `src/download.c:13` | `static int lc(int c)` |
| `media_type` | function | `src/download.c:33` | `static void media_type(const char *content_type, char *buf, size_t bufsz)` |
| `FX_EPS` | macro | `src/flex_layout.c:15` | `#define FX_EPS` |
| `area_token_is_null_cell` | function | `src/flex_layout.c:294` | `static int area_token_is_null_cell(const char *tok, size_t len)` |
| `float_pack_impl` | function | `src/flex_layout.c:417` | `static fx_status float_pack_impl(const double *width, const int *side, size_t n,
                ...` |
| `fx_auto_margins` | function | `src/flex_layout.c:556` | `fx_status fx_auto_margins(fx_result *res, size_t n, const unsigned char *auto_l,
                ...` |
| `fx_auto_min_size` | function | `src/flex_layout.c:579` | `double fx_auto_min_size(double min_content, double basis, double author_min,
                    ...` |
| `fx_column_place` | function | `src/flex_layout.c:673` | `fx_status fx_column_place(const double *h, const double *grow, size_t n, double gap,
            ...` |
| `fx_column_place_m` | function | `src/flex_layout.c:680` | `fx_status fx_column_place_m(const double *h, const double *grow, const int *mauto,
              ...` |
| `fx_cross_offset` | function | `src/flex_layout.c:741` | `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r)` |
| `fx_flex_line` | function | `src/flex_layout.c:22` | `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                ...` |
| `fx_float_insets` | function | `src/flex_layout.c:457` | `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,
                 ...` |
| `fx_float_pack` | function | `src/flex_layout.c:497` | `fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        d...` |
| `fx_float_pack_wrap` | function | `src/flex_layout.c:502` | `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,
                    ...` |
| `fx_grid_area_hash` | function | `src/flex_layout.c:270` | `unsigned fx_grid_area_hash(const char *name)` |
| `fx_grid_area_rect` | function | `src/flex_layout.c:375` | `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,
                            int ...` |
| `fx_grid_areas_parse` | function | `src/flex_layout.c:300` | `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)` |
| `fx_grid_cell` | function | `src/flex_layout.c:544` | `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)` |
| `fx_grid_columns` | function | `src/flex_layout.c:127` | `fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          doubl...` |
| `fx_grid_columns_weighted` | function | `src/flex_layout.c:132` | `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                      ...` |
| `fx_grid_place_span` | function | `src/flex_layout.c:166` | `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                      ...` |
| `fx_justify_name` | function | `src/flex_layout.c:661` | `const char *fx_justify_name(fx_justify j)` |
| `fx_multicol_balance` | function | `src/flex_layout.c:630` | `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,
                        ...` |
| `fx_multicol_used` | function | `src/flex_layout.c:593` | `fx_status fx_multicol_used(double avail_w, int column_count, double column_width,
               ...` |
| `nn` | function | `src/flex_layout.c:18` | `static double nn(double v)` |
| `clean_action` | function | `src/form.c:75` | `static int clean_action(const char *action, char *out, size_t outsz)` |
| `copy_fit` | function | `src/form.c:66` | `static int copy_fit(char *dst, size_t dstsz, const char *src)` |
| `enc_component` | function | `src/form.c:25` | `static int enc_component(const char *s, char *out, size_t outsz, size_t *pos)` |
| `fm_build` | function | `src/form.c:120` | `fm_status fm_build(const char *base, const char *action, fm_method method,
                   con...` |
| `fm_encode` | function | `src/form.c:43` | `fm_status fm_encode(const fm_field *fields, size_t n,
                    char *out, size_t outsz...` |
| `put_char` | function | `src/form.c:17` | `static int put_char(char *out, size_t outsz, size_t *pos, char c)` |
| `resolve_target` | function | `src/form.c:101` | `static fm_block_reason resolve_target(const char *base, const char *act,
                        ...` |
| `strip_query` | function | `src/form.c:93` | `static void strip_query(char *url)` |
| `FC_DEFAULT_INTERVAL_MS` | macro | `src/frame_clock.c:8` | `#define FC_DEFAULT_INTERVAL_MS` |
| `fc_interval_ms` | function | `src/frame_clock.c:26` | `int fc_interval_ms(const fc_clock *c)` |
| `fc_needs_tick` | function | `src/frame_clock.c:21` | `int fc_needs_tick(const fc_clock *c)` |
| `fc_set_active` | function | `src/frame_clock.c:16` | `void fc_set_active(fc_clock *c, int active)` |
| `fb_buffer_at` | function | `src/freebug.c:105` | `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)` |
| `fb_buffer_count` | function | `src/freebug.c:101` | `size_t fb_buffer_count(const fb_buffer *b)` |
| `fb_buffer_free` | function | `src/freebug.c:91` | `void fb_buffer_free(fb_buffer *b)` |
| `fb_buffer_init` | function | `src/freebug.c:15` | `void fb_buffer_init(fb_buffer *b)` |
| `fb_buffer_push` | function | `src/freebug.c:19` | `int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)` |
| `fb_buffer_push_loc` | function | `src/freebug.c:23` | `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len,
                   ...` |
| `fb_buffer_reset` | function | `src/freebug.c:78` | `void fb_buffer_reset(fb_buffer *b)` |
| `fb_level_name` | function | `src/freebug.c:110` | `const char *fb_level_name(int level)` |
| `whole` | function | `src/freebug.c:5` | `* FB_MAX_TOTAL_BYTES is dropped whole (overflow flag raised, prior entries kept);` |
| `BLOCKED` | function | `src/freedom.c:802` | `* is BLOCKED (fail closed), never leaked over the clearnet. */ nr_route route = nr_route_for(url, global_net);` |
| `CSS_DROPS_REPORT_MAX` | macro | `src/freedom.c:161` | `#define CSS_DROPS_REPORT_MAX` |
| `EXIT_ERROR` | macro | `src/freedom.c:44` | `#define EXIT_ERROR` |
| `EXIT_OK` | macro | `src/freedom.c:43` | `#define EXIT_OK` |
| `EXIT_USAGE` | macro | `src/freedom.c:45` | `#define EXIT_USAGE` |
| `HL_JS_NAV_MAX` | macro | `src/freedom.c:772` | `#define HL_JS_NAV_MAX` |
| `_DEFAULT_SOURCE` | macro | `src/freedom.c:10` | `#define _DEFAULT_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `src/freedom.c:9` | `#define _POSIX_C_SOURCE` |
| `elsewhere` | function | `src/freedom.c:837` | `* page whose script immediately forwards elsewhere (e.g. a search engine's
 * JS-capability inter...` |
| `fetch_and_render_one` | function | `src/freedom.c:776` | `static int fetch_and_render_one(const char *url, char **out_nav)` |
| `foldback_cookies` | function | `src/freedom.c:477` | `static void foldback_cookies(const char *url, const char *jar)` |
| `gets` | function | `src/freedom.c:411` | `* gate a click gets (https-only, no downgrade, no foreign scheme), so relative * subresources work. Realm-routed (fail-c` |
| `headless_fetch` | function | `src/freedom.c:415` | `static int headless_fetch(void *ctx, const char *method, const char *url,
                       ...` |
| `headless_load_hosts` | function | `src/freedom.c:223` | `static void headless_load_hosts(void)` |
| `is_blank_text` | function | `src/freedom.c:253` | `static int is_blank_text(const char *s)` |
| `is_http_url` | function | `src/freedom.c:77` | `static int is_http_url(const char *s)` |
| `is_https_url` | function | `src/freedom.c:73` | `static int is_https_url(const char *s)` |
| `is_overlay_http` | function | `src/freedom.c:82` | `static int is_overlay_http(const char *s)` |
| `main` | function | `src/freedom.c:1066` | `int main(int argc, char **argv)` |
| `now_us` | function | `src/freedom.c:136` | `static uint64_t now_us(void)` |
| `only` | function | `src/freedom.c:645` | `* styling for the local render only (no network). --images enables image loading * AND rendering, including remote fetch` |
| `parent` | function | `src/freedom.c:863` | `* gated by the parent (ln_resolve: a local target stays under the document's
 * directory, a remo...` |
| `pool` | function | `src/freedom.c:592` | `* the pool (unconsumed results freed, in-flight fetches joined). */ tab_set_fetcher(t, headless_fetch, (void *)(uintptr_` |
| `print_console` | function | `src/freedom.c:359` | `static void print_console(const fb_buffer *log)` |
| `print_css_drops` | function | `src/freedom.c:501` | `static void print_css_drops(const char *html, size_t len)` |
| `print_doc` | function | `src/freedom.c:266` | `static void print_doc(const rd_doc *doc)` |
| `print_dom` | function | `src/freedom.c:376` | `static void print_dom(const rd_doc *doc)` |
| `print_dom_css` | function | `src/freedom.c:391` | `static void print_dom_css(const rd_doc *doc)` |
| `print_usage` | function | `src/freedom.c:47` | `static void print_usage(FILE *fp, const char *prog)` |
| `read_file` | function | `src/freedom.c:205` | `static char *read_file(const char *path, size_t *out_len)` |
| `render_page` | function | `src/freedom.c:532` | `static int render_page(const char *html, size_t len, const char *top_url,
                       ...` |
| `run_dump_video` | function | `src/freedom.c:1047` | `static int run_dump_video(const char *url)` |
| `run_headless` | function | `src/freedom.c:900` | `static int run_headless(const char *target)` |
| `sf_reason` | function | `src/freedom.c:757` | `static const char *sf_reason(sf_status ss)` |
| `timings_dump` | function | `src/freedom.c:150` | `static void timings_dump(void)` |
| `timings_enabled` | function | `src/freedom.c:146` | `static int timings_enabled(void)` |
| `timings_ensure_init` | function | `src/freedom.c:142` | `static void timings_ensure_init(void)` |
| `user_impersonate_enabled` | function | `src/freedom.c:198` | `static int user_impersonate_enabled(void)` |
| `video_fetch_with_fallback` | function | `src/freedom.c:936` | `static sf_status video_fetch_with_fallback(const char *url, sf_config *cfg,
                     ...` |
| `_GNU_SOURCE` | macro | `src/hls.c:21` | `#define _GNU_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `src/hls.c:22` | `#define _POSIX_C_SOURCE` |
| `hls_parse` | function | `src/hls.c:80` | `hls_status hls_parse(const char *text, size_t len, hls_playlist **out)` |
| `hls_playlist_free` | function | `src/hls.c:253` | `void hls_playlist_free(hls_playlist *pl)` |
| `hls_resolve_url` | function | `src/hls.c:223` | `size_t hls_resolve_url(const char *base_url, const char *segment_url,
                       char...` |
| `hls_select_variant` | function | `src/hls.c:202` | `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h)` |
| `last_char` | function | `src/hls.c:38` | `static const char *last_char(const char *s, size_t n, int c)` |
| `name` | function | `src/hls.c:46` | `* attr is the attribute name (e.g. "BANDWIDTH=");` |
| `parse_attr_long` | function | `src/hls.c:48` | `static int parse_attr_long(const char *attrs, const char *end,
                           const c...` |
| `parse_attr_resolution` | function | `src/hls.c:62` | `static void parse_attr_resolution(const char *attrs, const char *end,
                           ...` |
| `HB_INIT_CAP` | macro | `src/hostblock.c:20` | `#define HB_INIT_CAP` |
| `HB_MAX_HOST` | macro | `src/hostblock.c:19` | `#define HB_MAX_HOST` |
| `hb_check` | function | `src/hostblock.c:193` | `hb_decision hb_check(const hb_set *s, const char *host)` |
| `hb_count` | function | `src/hostblock.c:238` | `size_t hb_count(const hb_set *s, hb_list list)` |
| `hb_free` | function | `src/hostblock.c:149` | `void hb_free(hb_set *s)` |
| `hb_is_allowlisted` | function | `src/hostblock.c:218` | `int hb_is_allowlisted(const hb_set *s, const char *host)` |
| `hb_load` | function | `src/hostblock.c:156` | `hb_status hb_load(hb_set *s, const char *text, hb_list list)` |
| `hb_new` | function | `src/hostblock.c:144` | `hb_set *hb_new(void)` |
| `hb_set` | struct | `src/hostblock.c:30` | `` |
| `hb_table` | struct | `src/hostblock.c:24` | `` |
| `is_domain_char` | function | `src/hostblock.c:122` | `static int is_domain_char(char c)` |
| `is_ip_token` | function | `src/hostblock.c:113` | `static int is_ip_token(const char *s, size_t n)` |
| `lower` | function | `src/hostblock.c:107` | `static char lower(char c)` |
| `table_contains` | function | `src/hostblock.c:92` | `static int table_contains(const hb_table *t, const char *key)` |
| `table_free` | function | `src/hostblock.c:98` | `static void table_free(hb_table *t)` |
| `table_grow` | function | `src/hostblock.c:49` | `static int table_grow(hb_table *t, size_t newcap)` |
| `table_insert` | function | `src/hostblock.c:71` | `static int table_insert(hb_table *t, const char *key, size_t klen)` |
| `table_probe` | function | `src/hostblock.c:38` | `static size_t table_probe(const hb_table *t, const char *key, size_t klen)` |
| `contains_ci` | function | `src/hostedit.c:115` | `static int contains_ci(const char *hs, size_t hl, const char *needle)` |
| `has_host_cb` | function | `src/hostedit.c:105` | `static int has_host_cb(const char *ts, size_t tl, void *ctx)` |
| `he_lower` | function | `src/hostedit.c:12` | `static char he_lower(char c)` |
| `he_make_line` | function | `src/hostedit.c:41` | `he_status he_make_line(const char *host, char *out, size_t cap)` |
| `he_scan` | function | `src/hostedit.c:80` | `static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), void *ctx)` |
| `he_suggest` | function | `src/hostedit.c:164` | `int he_suggest(const char *text, const char *query,
               char results[][HE_MAX_HOST + 1...` |
| `he_text_has_host` | function | `src/hostedit.c:109` | `int he_text_has_host(const char *text, const char *host)` |
| `is_ip_token` | function | `src/hostedit.c:67` | `static int is_ip_token(const char *ts, const char *te)` |
| `is_label_char` | function | `src/hostedit.c:16` | `static int is_label_char(char c)` |
| `starts_with_ci` | function | `src/hostedit.c:128` | `static int starts_with_ci(const char *hs, size_t hl, const char *pfx)` |
| `suggest_cb` | function | `src/hostedit.c:144` | `static int suggest_cb(const char *ts, size_t tl, void *vctx)` |
| `suggest_ctx` | struct | `src/hostedit.c:136` | `` |
| `valid_host` | function | `src/hostedit.c:22` | `static int valid_host(const char *host, size_t n)` |
| `_POSIX_C_SOURCE` | macro | `src/html_parse.c:9` | `#define _POSIX_C_SOURCE` |
| `attr_has_token_ci` | function | `src/html_parse.c:251` | `static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle)` |
| `attr_is_event_handler` | function | `src/html_parse.c:47` | `static int attr_is_event_handler(const lxb_dom_attr_t *attr)` |
| `dup_bytes` | function | `src/html_parse.c:27` | `static char *dup_bytes(const lxb_char_t *src, size_t len)` |
| `hp_config_default` | function | `src/html_parse.c:357` | `hp_config hp_config_default(void)` |
| `hp_document` | struct | `src/html_parse.c:21` | `` |
| `hp_document_free` | function | `src/html_parse.c:483` | `void hp_document_free(hp_document *doc)` |
| `hp_document_root` | function | `src/html_parse.c:489` | `const void *hp_document_root(const hp_document *doc)` |
| `hp_element_count` | function | `src/html_parse.c:409` | `size_t hp_element_count(const hp_document *doc)` |
| `hp_event_handler_count` | function | `src/html_parse.c:429` | `size_t hp_event_handler_count(const hp_document *doc)` |
| `hp_extract_script_list` | function | `src/html_parse.c:164` | `hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count)` |
| `hp_extract_stylesheet_hrefs` | function | `src/html_parse.c:294` | `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count)` |
| `hp_extract_text` | function | `src/html_parse.c:445` | `char *hp_extract_text(const hp_document *doc, size_t *out_len)` |
| `hp_free` | function | `src/html_parse.c:479` | `void hp_free(char *buf)` |
| `hp_free_scripts` | function | `src/html_parse.c:238` | `void hp_free_scripts(hp_script *scripts, size_t count)` |
| `hp_free_stylesheet_hrefs` | function | `src/html_parse.c:328` | `void hp_free_stylesheet_hrefs(char **hrefs, size_t count)` |
| `hp_get_title` | function | `src/html_parse.c:464` | `char *hp_get_title(const hp_document *doc, size_t *out_len)` |
| `hp_parse` | function | `src/html_parse.c:375` | `hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out)` |
| `hp_script_count` | function | `src/html_parse.c:419` | `size_t hp_script_count(const hp_document *doc)` |
| `hp_validate_input` | function | `src/html_parse.c:365` | `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg)` |
| `link_is_active_stylesheet` | function | `src/html_parse.c:272` | `static int link_is_active_stylesheet(lxb_dom_element_t *el,
                                     ...` |
| `lxb_dom_element_has_attribute` | function | `src/html_parse.c:230` | `&& lxb_dom_element_has_attribute(sel, (const lxb_char_t *)"nomodule", 8);` |
| `node_is_script` | function | `src/html_parse.c:54` | `static int node_is_script(const lxb_dom_node_t *node)` |
| `node_next` | function | `src/html_parse.c:37` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `script_classify` | function | `src/html_parse.c:121` | `static int script_classify(const lxb_dom_node_t *n,
                           const lxb_char_t *...` |
| `strip_event_handlers` | function | `src/html_parse.c:334` | `static void strip_event_handlers(lxb_html_document_t *document)` |
| `strip_scripts` | function | `src/html_parse.c:60` | `static void strip_scripts(lxb_html_document_t *document)` |
| `type_is` | function | `src/html_parse.c:100` | `static int type_is(const lxb_char_t *t, size_t len, const char *word)` |
| `type_is_module` | function | `src/html_parse.c:117` | `static int type_is_module(const lxb_char_t *t, size_t len)` |
| `GIF_LZW_MAX_CODES` | macro | `src/image_decode.c:253` | `#define GIF_LZW_MAX_CODES` |
| `PNG_IHDR_MIN` | macro | `src/image_decode.c:34` | `#define PNG_IHDR_MIN` |
| `exit` | function | `src/image_decode.c:6` | `* malformed stream fails closed instead of calling exit(). GIF uses an own pure-C * bounded LZW decoder (no giflib). Web` |
| `gb_next_code` | function | `src/image_decode.c:298` | `static int gb_next_code(gif_bits *b, unsigned width, unsigned *out)` |
| `gif_bits` | struct | `src/image_decode.c:290` | `` |
| `gif_deinterlace_row` | function | `src/image_decode.c:319` | `static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh)` |
| `gif_put_pixel` | function | `src/image_decode.c:334` | `static void gif_put_pixel(uint32_t *canvas, uint32_t cw, uint32_t ch,
                          u...` |
| `gif_reader` | struct | `src/image_decode.c:255` | `` |
| `gr_skip` | function | `src/image_decode.c:273` | `static int gr_skip(gif_reader *r, size_t n)` |
| `gr_skip_subblocks` | function | `src/image_decode.c:280` | `static int gr_skip_subblocks(gif_reader *r)` |
| `gr_u16le` | function | `src/image_decode.c:266` | `static int gr_u16le(gif_reader *r, uint16_t *out)` |
| `gr_u8` | function | `src/image_decode.c:260` | `static int gr_u8(gif_reader *r, uint8_t *out)` |
| `img_decode` | function | `src/image_decode.c:553` | `img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_gif` | function | `src/image_decode.c:354` | `img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_jpeg` | function | `src/image_decode.c:166` | `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_png` | function | `src/image_decode.c:102` | `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_webp` | function | `src/image_decode.c:520` | `img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_dimensions_ok` | function | `src/image_decode.c:68` | `int img_dimensions_ok(uint32_t w, uint32_t h)` |
| `img_fit` | function | `src/image_decode.c:76` | `void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,
             double *out_w, do...` |
| `img_format_name` | function | `src/image_decode.c:575` | `const char *img_format_name(img_format f)` |
| `img_pixels_free` | function | `src/image_decode.c:566` | `void img_pixels_free(img_pixels *p)` |
| `img_png_dimensions` | function | `src/image_decode.c:57` | `img_status img_png_dimensions(const uint8_t *bytes, size_t len,
                              uin...` |
| `jpeg_err_ctx` | struct | `src/image_decode.c:153` | `` |
| `jpeg_error_longjmp` | function | `src/image_decode.c:158` | `static void jpeg_error_longjmp(j_common_ptr cinfo)` |
| `jpeg_silence` | function | `src/image_decode.c:164` | `static void jpeg_silence(j_common_ptr cinfo)` |
| `premultiply` | function | `src/image_decode.c:90` | `static void premultiply(uint8_t *data, size_t pixels)` |
| `read_be32` | function | `src/image_decode.c:52` | `static uint32_t read_be32(const uint8_t *p)` |
| `IM_MAX_DEPTH` | macro | `src/import_map.c:16` | `#define IM_MAX_DEPTH` |
| `IM_URL_MAX` | macro | `src/import_map.c:17` | `#define IM_URL_MAX` |
| `add` | function | `src/import_map.c:185` | `static int add(im_map *m, int scope, const char *key, const char *addr, const char *doc_url,
    ...` |
| `clear` | function | `src/import_map.c:175` | `static void clear(im_map *m)` |
| `dup_s` | function | `src/import_map.c:168` | `static char *dup_s(const char *s)` |
| `eat` | function | `src/import_map.c:44` | `static int eat(jr *r, char c)` |
| `hex4` | function | `src/import_map.c:50` | `static int hex4(const char *s, uint32_t *out)` |
| `im_count` | function | `src/import_map.c:339` | `size_t im_count(const im_map *m)` |
| `im_entry` | struct | `src/import_map.c:19` | `` |
| `im_free` | function | `src/import_map.c:343` | `void im_free(im_map *m)` |
| `im_map` | struct | `src/import_map.c:25` | `` |
| `im_parse` | function | `src/import_map.c:225` | `im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn resolve, void *ctx)` |
| `im_resolve` | function | `src/import_map.c:301` | `int im_resolve(const im_map *m, const char *base, const char *specifier,
               im_url_fn...` |
| `jr` | struct | `src/import_map.c:34` | `` |
| `match` | function | `src/import_map.c:272` | `static int match(const im_map *m, int scope, const char *key, char *out, size_t outsz)` |
| `put_utf8` | function | `src/import_map.c:64` | `static size_t put_utf8(char *o, uint32_t cp)` |
| `scope` | type_alias | `src/import_map.c:18` | `typedef struct im_entry { int scope;` |
| `skip` | function | `src/import_map.c:128` | `static void skip(jr *r, int depth)` |
| `specifier_map` | function | `src/import_map.c:209` | `static void specifier_map(jr *r, im_map *m, int scope, const char *doc_url,
                     ...` |
| `str` | function | `src/import_map.c:78` | `static char *str(jr *r)` |
| `url_like` | function | `src/import_map.c:156` | `static int url_like(const char *s)` |
| `ws` | function | `src/import_map.c:39` | `static void ws(jr *r)` |
| `anim_effective_dir` | function | `src/interp.c:232` | `static int anim_effective_dir(const ip_anim *a)` |
| `anim_effective_dir_for` | function | `src/interp.c:222` | `static int anim_effective_dir_for(const ip_anim *a, int iter)` |
| `ip_anim_current` | function | `src/interp.c:282` | `double ip_anim_current(const ip_anim *a)` |
| `ip_anim_done` | function | `src/interp.c:320` | `int ip_anim_done(const ip_anim *a)` |
| `ip_anim_init` | function | `src/interp.c:196` | `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease,
                  const ip_...` |
| `ip_anim_tick` | function | `src/interp.c:236` | `int ip_anim_tick(ip_anim *a, double dt_ms)` |
| `ip_ease` | function | `src/interp.c:55` | `double ip_ease(double t, const ip_ease_fn *fn)` |
| `ip_ease` | function | `src/interp.c:64` | `case IP_EASE_EASE:
        return ip_ease(t, &(ip_ease_fn)` |
| `ip_ease` | function | `src/interp.c:70` | `case IP_EASE_EASE_IN:
        return ip_ease(t, &(ip_ease_fn)` |
| `ip_ease` | function | `src/interp.c:76` | `case IP_EASE_EASE_OUT:
        return ip_ease(t, &(ip_ease_fn)` |
| `ip_ease` | function | `src/interp.c:82` | `case IP_EASE_EASE_IN_OUT:
        return ip_ease(t, &(ip_ease_fn)` |
| `ip_interp` | function | `src/interp.c:162` | `double ip_interp(ip_val_kind kind, double a, double b, double t)` |
| `ip_kf_interp` | function | `src/interp.c:175` | `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf,
                    int n_kf, do...` |
| `ip_lerp` | function | `src/interp.c:134` | `double ip_lerp(double a, double b, double t)` |
| `ip_lerp_color` | function | `src/interp.c:139` | `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t)` |
| `sample_bezier_dx` | function | `src/interp.c:23` | `static double sample_bezier_dx(double t, double cx1, double cx2)` |
| `sample_bezier_x` | function | `src/interp.c:18` | `static double sample_bezier_x(double t, double cx1, double cx2)` |
| `sample_bezier_y` | function | `src/interp.c:29` | `static double sample_bezier_y(double t, double cy1, double cy2)` |
| `solve_bezier_t` | function | `src/interp.c:35` | `static double solve_bezier_t(double x, double cx1, double cx2)` |
| `_GNU_SOURCE` | macro | `src/js_dom.c:10` | `#define _GNU_SOURCE` |
| `attrNames` | function | `src/js_dom.c:610` | `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so
     * a missing '...` |
| `empty` | function | `src/js_dom.c:1193` | `* inert: DOM interface constructors are empty (instanceof yields false, harmless);` |
| `enough` | function | `src/js_dom.c:909` | `* enough (cloneNode/lastChild/removeChild/insertBefore) that library feature * detection does not throw: jQuery clones a` |
| `fails` | function | `src/js_dom.c:1798` | `* cap is reached or an allocation fails (caller stops), else 0. */
static int cb_append(char **bu...` |
| `fire` | function | `src/js_dom.c:1194` | `* observers never fire (no observation -> no info leak);` |
| `jd_get_cookies` | function | `src/js_dom.c:1969` | `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)` |
| `jd_handle` | function | `src/js_dom.c:40` | `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out)` |
| `jd_handle_or_null` | function | `src/js_dom.c:47` | `JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h)` |
| `jd_idx` | function | `src/js_dom.c:31` | `dom_index *jd_idx(JSContext *ctx)` |
| `jd_install` | function | `src/js_dom.c:1721` | `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)` |
| `jd_install_console` | function | `src/js_dom.c:1912` | `jd_status jd_install_console(js_context *ctx, fb_buffer *log)` |
| `jd_method` | struct | `src/js_dom.c:428` | `` |
| `jd_opaque_get` | function | `src/js_dom.c:27` | `jd_opaque *jd_opaque_get(JSContext *ctx)` |
| `jd_query_list` | function | `src/js_dom.c:70` | `static JSValue jd_query_list(JSContext *ctx, JSValueConst arg, int by_class)` |
| `jd_set_cookies` | function | `src/js_dom.c:1949` | `jd_status jd_set_cookies(js_context *ctx, const char *cookies)` |
| `jd_set_geometry` | function | `src/js_dom.c:1992` | `jd_status jd_set_geometry(js_context *ctx, const jg_table *geom)` |
| `js_env` | function | `src/js_dom.c:1199` | `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the
 * document shim (uses...` |
| `m_append_child` | function | `src/js_dom.c:264` | `static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,
                            ...` |
| `m_attr_names` | function | `src/js_dom.c:503` | `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,
                            in...` |
| `m_child_node` | function | `src/js_dom.c:159` | `static JSValue m_child_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_clone_node` | function | `src/js_dom.c:289` | `static JSValue m_clone_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_closest` | function | `src/js_dom.c:491` | `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,
                         int argc...` |
| `m_create_char` | function | `src/js_dom.c:174` | `static JSValue m_create_char(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_create_element` | function | `src/js_dom.c:252` | `static JSValue m_create_element(JSContext *ctx, JSValueConst this_val,
                          ...` |
| `m_first_child` | function | `src/js_dom.c:143` | `static JSValue m_first_child(JSContext *ctx, JSValueConst this_val,
                             ...` |
| `m_get_attribute` | function | `src/js_dom.c:122` | `static JSValue m_get_attribute(JSContext *ctx, JSValueConst this_val,
                           ...` |
| `m_get_by_class` | function | `src/js_dom.c:106` | `static JSValue m_get_by_class(JSContext *ctx, JSValueConst this_val,
                            ...` |
| `m_get_by_tag` | function | `src/js_dom.c:100` | `static JSValue m_get_by_tag(JSContext *ctx, JSValueConst this_val,
                            in...` |
| `m_get_element_by_id` | function | `src/js_dom.c:59` | `static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val,
                       ...` |
| `m_get_inner_html` | function | `src/js_dom.c:364` | `static JSValue m_get_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...` |
| `m_get_title` | function | `src/js_dom.c:231` | `static JSValue m_get_title(JSContext *ctx, JSValueConst this_val,
                           int ...` |
| `m_insert_before` | function | `src/js_dom.c:299` | `static JSValue m_insert_before(JSContext *ctx, JSValueConst this_val,
                           ...` |
| `m_matches` | function | `src/js_dom.c:479` | `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,
                         int argc...` |
| `m_move_children` | function | `src/js_dom.c:275` | `static JSValue m_move_children(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_next_sibling` | function | `src/js_dom.c:188` | `static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,
                            ...` |
| `m_node_count` | function | `src/js_dom.c:53` | `static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,
                            in...` |
| `m_node_kind` | function | `src/js_dom.c:152` | `static JSValue m_node_kind(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_parent` | function | `src/js_dom.c:135` | `static JSValue m_parent(JSContext *ctx, JSValueConst this_val,
                        int argc, ...` |
| `m_precedes` | function | `src/js_dom.c:196` | `static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,
                          int ar...` |
| `m_query_selector` | function | `src/js_dom.c:437` | `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,
                          ...` |
| `m_query_selector_all` | function | `src/js_dom.c:450` | `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,
                      ...` |
| `m_rect` | function | `src/js_dom.c:396` | `static JSValue m_rect(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_remove_attribute` | function | `src/js_dom.c:336` | `static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,
                        ...` |
| `m_remove_child` | function | `src/js_dom.c:311` | `static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,
                            ...` |
| `m_set_attribute` | function | `src/js_dom.c:320` | `static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,
                           ...` |
| `m_set_inner_html` | function | `src/js_dom.c:348` | `static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...` |
| `m_set_text` | function | `src/js_dom.c:217` | `static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,
                          int ar...` |
| `m_set_title` | function | `src/js_dom.c:239` | `static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,
                           int ...` |
| `m_sibling_node` | function | `src/js_dom.c:166` | `static JSValue m_sibling_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_tag_name` | function | `src/js_dom.c:112` | `static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,
                          int ar...` |
| `m_text_content` | function | `src/js_dom.c:207` | `static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,
                            ...` |
| `ms` | function | `src/js_dom.c:1045` | `* due is the remaining virtual ms (the trusted parent advances the clock via * OP_TICK -> __tickTimers(elapsed);` |
| `scripts` | function | `src/js_dom.c:746` | `* player scripts (canPlayType feature-detection, play/pause, muted/loop * reflection, buffered ranges) run without throw` |
| `table` | function | `src/js_dom.c:571` | `* a table (dom.viewport() non-null);` |
| `jdx_install` | function | `src/js_dom_ext.c:334` | `int jdx_install(JSContext *ctx)` |
| `run` | function | `src/js_dom_ext.c:326` | `static int run(JSContext *ctx, const char *src, size_t len, const char *name)` |
| `FREEDOM_JS_DOM_EXT_H` | macro | `src/js_dom_ext.h:2` | `#define FREEDOM_JS_DOM_EXT_H` |
| `jdx_install` | function | `src/js_dom_ext.h:10` | `int jdx_install(JSContext *ctx);` |
| `FREEDOM_JS_DOM_INTERNAL_H` | macro | `src/js_dom_internal.h:2` | `#define FREEDOM_JS_DOM_INTERNAL_H` |
| `jd_handle` | function | `src/js_dom_internal.h:14` | `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out);` |
| `jd_idx` | function | `src/js_dom_internal.h:12` | `dom_index *jd_idx(JSContext *ctx);` |
| `jd_opaque_get` | function | `src/js_dom_internal.h:11` | `jd_opaque *jd_opaque_get(JSContext *ctx);` |
| `_GNU_SOURCE` | macro | `src/js_embed.c:6` | `#define _GNU_SOURCE` |
| `jd_inject_video_shim` | function | `src/js_embed.c:242` | `jd_status jd_inject_video_shim(js_context *ctx)` |
| `jd_process_iframes` | function | `src/js_embed.c:294` | `void jd_process_iframes(js_context *ctx, dom_index *idx,
                        jd_fetch_fn fn, ...` |
| `jd_video_from_scripts` | function | `src/js_embed.c:203` | `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,
                   ...` |
| `scan_video_url` | function | `src/js_embed.c:256` | `static int scan_video_url(const char *body, size_t blen,
                           char *out, si...` |
| `try_create_iframe_from_script` | function | `src/js_embed.c:86` | `static int try_create_iframe_from_script(dom_index *idx,
                                        ...` |
| `FP_MIME_COUNT` | macro | `src/js_env.c:260` | `#define FP_MIME_COUNT` |
| `PERF_ORIGIN_EPOCH` | macro | `src/js_env.c:344` | `#define PERF_ORIGIN_EPOCH` |
| `_POSIX_C_SOURCE` | macro | `src/js_env.c:17` | `#define _POSIX_C_SOURCE` |
| `build_crypto` | function | `src/js_env.c:346` | `static int build_crypto(JSContext *ctx, JSValueConst global)` |
| `build_languages` | function | `src/js_env.c:174` | `static JSValue build_languages(JSContext *ctx)` |
| `build_navigator` | function | `src/js_env.c:198` | `static int build_navigator(JSContext *ctx, JSValueConst global)` |
| `build_perf_navigation` | function | `src/js_env.c:388` | `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)` |
| `build_perf_timing` | function | `src/js_env.c:374` | `static int build_perf_timing(JSContext *ctx, JSValueConst perf)` |
| `build_performance` | function | `src/js_env.c:400` | `static int build_performance(JSContext *ctx, JSValueConst global)` |
| `build_readback_obj` | function | `src/js_env.c:484` | `static int build_readback_obj(JSContext *ctx, JSValueConst global,
                              ...` |
| `build_screen` | function | `src/js_env.c:302` | `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)` |
| `def_fn` | function | `src/js_env.c:167` | `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,
                  JSCFuncti...` |
| `def_int` | function | `src/js_env.c:163` | `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)` |
| `def_str` | function | `src/js_env.c:159` | `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)` |
| `def_val` | function | `src/js_env.c:153` | `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)` |
| `je_install` | function | `src/js_env.c:497` | `je_status je_install(js_context *ctx, int screen_w, int screen_h)` |
| `je_install_canvas` | function | `src/js_env.c:516` | `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)` |
| `m_date_now` | function | `src/js_env.c:49` | `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,
                          int ar...` |
| `m_empty_array` | function | `src/js_env.c:77` | `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,
                             ...` |
| `m_get_random_values` | function | `src/js_env.c:85` | `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,
                       ...` |
| `m_perf_now` | function | `src/js_env.c:57` | `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,
                          int ar...` |
| `m_random_uuid` | function | `src/js_env.c:125` | `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,
                             ...` |
| `m_subtle_null` | function | `src/js_env.c:142` | `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,
                             ...` |
| `make_readback` | function | `src/js_env.c:476` | `static JSValue make_readback(JSContext *ctx, uint64_t key)` |
| `methods` | function | `src/js_env.c:201` | `* capability methods (sendBeacon, spec/js_dom.md 7h) without touching any * fingerprintable field. An untrusted page's p` |
| `monotonic_ms` | function | `src/js_env.c:41` | `static double monotonic_ms(void)` |
| `override_date_now` | function | `src/js_env.c:432` | `static int override_date_now(JSContext *ctx, JSValueConst global)` |
| `primitives` | function | `src/js_env.c:6` | `* the pure anti_fp primitives (one audited source of normalized constants);` |
| `wall_clock_ms` | function | `src/js_env.c:35` | `static uint64_t wall_clock_ms(void)` |
| `_GNU_SOURCE` | macro | `src/js_events.c:6` | `#define _GNU_SOURCE` |
| `jd_click_state` | struct | `src/js_events.c:25` | `` |
| `jd_click_state_free` | function | `src/js_events.c:34` | `void jd_click_state_free(jd_click_state *s)` |
| `jd_click_state_new` | function | `src/js_events.c:29` | `jd_click_state *jd_click_state_new(void)` |
| `jd_escape_js_str` | function | `src/js_events.c:91` | `static size_t jd_escape_js_str(const char *src, char *dst, size_t dstsz)` |
| `jd_eval_default_action` | function | `src/js_events.c:52` | `static int jd_eval_default_action(JSContext *jsctx, const char *src, size_t n,
                  ...` |
| `jd_fire_click` | function | `src/js_events.c:66` | `int jd_fire_click(js_context *ctx, dom_node_id node_id)` |
| `jd_fire_mouse_event` | function | `src/js_events.c:163` | `int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,
                        const char ...` |
| `jd_fire_submit` | function | `src/js_events.c:78` | `int jd_fire_submit(js_context *ctx, dom_node_id form_node_id)` |
| `jd_install_events` | function | `src/js_events.c:38` | `jd_status jd_install_events(js_context *ctx, jd_click_state *state)` |
| `_GNU_SOURCE` | macro | `src/js_fetch.c:6` | `#define _GNU_SOURCE` |
| `jd_install_xhr` | function | `src/js_fetch.c:197` | `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)` |
| `jd_pack_ptr` | function | `src/js_fetch.c:28` | `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)` |
| `jd_unpack_ptr` | function | `src/js_fetch.c:33` | `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)` |
| `m_host_fetch` | function | `src/js_fetch.c:46` | `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,
                            in...` |
| `send` | function | `src/js_fetch.c:92` | `* callbacks fire right after send();` |
| `task` | function | `src/js_fetch.c:179` | `* current task (the page never waits on it);` |
| `JG_INDEX_SLOTS` | macro | `src/js_geom.c:14` | `#define JG_INDEX_SLOTS` |
| `JG_SLOT_EMPTY` | macro | `src/js_geom.c:15` | `#define JG_SLOT_EMPTY` |
| `clamp_coord` | function | `src/js_geom.c:27` | `static int32_t clamp_coord(double v, double lo)` |
| `cmp_node` | function | `src/js_geom.c:78` | `static int cmp_node(const void *pa, const void *pb)` |
| `fnv` | function | `src/js_geom.c:212` | `static uint64_t fnv(uint64_t h, int32_t v)` |
| `grow` | function | `src/js_geom.c:33` | `static int grow(jg_table *t)` |
| `in_range` | function | `src/js_geom.c:182` | `static int in_range(int32_t v, int32_t lo)` |
| `index_of` | function | `src/js_geom.c:109` | `static size_t index_of(jg_table *t, uint32_t *slots, dom_node_id node, const jg_rect *seed,
     ...` |
| `jg_add` | function | `src/js_geom.c:52` | `int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h)` |
| `jg_aggregate` | function | `src/js_geom.c:124` | `int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx)` |
| `jg_decode` | function | `src/js_geom.c:186` | `int jg_decode(const int32_t *in, size_t n, jg_table *out)` |
| `jg_encode` | function | `src/js_geom.c:167` | `int jg_encode(const jg_table *t, int32_t *out, size_t cap)` |
| `jg_find` | function | `src/js_geom.c:96` | `const jg_rect *jg_find(const jg_table *t, dom_node_id node)` |
| `jg_finish` | function | `src/js_geom.c:83` | `int jg_finish(jg_table *t)` |
| `jg_free` | function | `src/js_geom.c:21` | `void jg_free(jg_table *t)` |
| `jg_hash` | function | `src/js_geom.c:221` | `uint64_t jg_hash(const jg_table *t)` |
| `jg_init` | function | `src/js_geom.c:17` | `void jg_init(jg_table *t)` |
| `jg_wire_len` | function | `src/js_geom.c:163` | `size_t jg_wire_len(const jg_table *t)` |
| `push` | function | `src/js_geom.c:45` | `static int push(jg_table *t, dom_node_id node, int32_t x, int32_t y, int32_t w, int32_t h)` |
| `slot_of` | function | `src/js_geom.c:102` | `static uint32_t slot_of(dom_node_id n)` |
| `unite` | function | `src/js_geom.c:63` | `static int unite(jg_rect *a, const jg_rect *b)` |
| `jd_lp_set` | function | `src/js_location.c:24` | `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,
                      const ...` |
| `jd_pop_state` | function | `src/js_location.c:250` | `int jd_pop_state(js_context *ctx, int index)` |
| `jd_set_location` | function | `src/js_location.c:139` | `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)` |
| `jd_take_history` | function | `src/js_location.c:219` | `char *jd_take_history(js_context *ctx, int *go)` |
| `jd_take_nav_request` | function | `src/js_location.c:173` | `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)` |
| `jl_m_hist_target` | function | `src/js_location.c:35` | `JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `FREEDOM_JS_LOCATION_INTERNAL_H` | macro | `src/js_location_internal.h:2` | `#define FREEDOM_JS_LOCATION_INTERNAL_H` |
| `header` | function | `src/js_location_internal.h:6` | `* stay out of every public header (include/ never sees quickjs.h). */ #include "quickjs.h" JSValue jl_m_hist_target(JSCo` |
| `eq_ci` | function | `src/js_policy.c:12` | `static int eq_ci(const char *a, const char *b)` |
| `jsp_enabled` | function | `src/js_policy.c:22` | `bool jsp_enabled(jsp_mode mode, int host_allowlisted)` |
| `jsp_mode_from_str` | function | `src/js_policy.c:39` | `jsp_mode jsp_mode_from_str(const char *s)` |
| `jsp_mode_str` | function | `src/js_policy.c:51` | `const char *jsp_mode_str(jsp_mode mode)` |
| `jsp_present_trusted` | function | `src/js_policy.c:35` | `bool jsp_present_trusted(int host_allowlisted)` |
| `jsp_trusted` | function | `src/js_policy.c:31` | `bool jsp_trusted(bool js_enabled, int host_allowlisted)` |
| `JS_MODULE_URL_MAX` | macro | `src/js_sandbox.c:527` | `#define JS_MODULE_URL_MAX` |
| `_POSIX_C_SOURCE` | macro | `src/js_sandbox.c:12` | `#define _POSIX_C_SOURCE` |
| `arm_deadline` | function | `src/js_sandbox.c:327` | `static void arm_deadline(js_context *ctx, uint64_t budget_ms)` |
| `host_dup` | function | `src/js_sandbox.c:99` | `static char *host_dup(const char *src, size_t len)` |
| `is_ascii_digit` | function | `src/js_sandbox.c:127` | `static int is_ascii_digit(char c)` |
| `jm_calloc` | function | `src/js_sandbox.c:63` | `static void *jm_calloc(void *opaque, size_t count, size_t size)` |
| `jm_free` | function | `src/js_sandbox.c:73` | `static void jm_free(void *opaque, void *ptr)` |
| `jm_malloc` | function | `src/js_sandbox.c:55` | `static void *jm_malloc(void *opaque, size_t size)` |
| `jm_realloc` | function | `src/js_sandbox.c:79` | `static void *jm_realloc(void *opaque, void *ptr, size_t size)` |
| `jm_usable_size` | function | `src/js_sandbox.c:89` | `static size_t jm_usable_size(const void *ptr)` |
| `js_context` | struct | `src/js_sandbox.c:33` | `` |
| `js_context_free` | function | `src/js_sandbox.c:316` | `void js_context_free(js_context *ctx)` |
| `js_context_new` | function | `src/js_sandbox.c:277` | `js_status js_context_new(const js_limits *lim, js_context **out)` |
| `js_context_raw` | function | `src/js_sandbox.c:522` | `void *js_context_raw(js_context *ctx)` |
| `js_eval` | function | `src/js_sandbox.c:347` | `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)` |
| `js_eval_module` | function | `src/js_sandbox.c:613` | `js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,
        ...` |
| `js_eval_named` | function | `src/js_sandbox.c:351` | `js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        con...` |
| `js_eval_once` | function | `src/js_sandbox.c:452` | `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)` |
| `js_install_realms` | function | `src/js_sandbox.c:775` | `js_status js_install_realms(js_context *ctx)` |
| `js_interrupt_cb` | function | `src/js_sandbox.c:114` | `static int js_interrupt_cb(JSRuntime *rt, void *opaque)` |
| `js_limits_default` | function | `src/js_sandbox.c:248` | `js_limits js_limits_default(void)` |
| `js_loc_from_stack` | function | `src/js_sandbox.c:129` | `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      i...` |
| `js_mem_state` | struct | `src/js_sandbox.c:27` | `` |
| `js_pump_jobs` | function | `src/js_sandbox.c:434` | `int js_pump_jobs(js_context *ctx, int max_jobs)` |
| `js_result_free` | function | `src/js_sandbox.c:465` | `void js_result_free(js_result *res)` |
| `js_set_current_script` | function | `src/js_sandbox.c:489` | `void js_set_current_script(js_context *ctx, const char *src, const char *type)` |
| `js_set_module_host` | function | `src/js_sandbox.c:588` | `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,
                        js...` |
| `js_set_time_budget` | function | `src/js_sandbox.c:342` | `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)` |
| `js_validate_source` | function | `src/js_sandbox.c:266` | `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)` |
| `limit` | type_alias | `src/js_sandbox.c:27` | `typedef struct js_mem_state { size_t limit;` |
| `limits_resolve` | function | `src/js_sandbox.c:257` | `static js_limits limits_resolve(const js_limits *lim)` |
| `m_realm_clone` | function | `src/js_sandbox.c:753` | `static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,
                   ...` |
| `m_realm_eval` | function | `src/js_sandbox.c:717` | `static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,
                    ...` |
| `m_realm_new` | function | `src/js_sandbox.c:703` | `static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,
                     ...` |
| `mod_fail` | function | `src/js_sandbox.c:598` | `static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,
      ...` |
| `mod_loader` | function | `src/js_sandbox.c:552` | `static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque)` |
| `mod_set_meta` | function | `src/js_sandbox.c:543` | `static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url)` |
| `realm_of` | function | `src/js_sandbox.c:680` | `static JSContext *realm_of(js_context *c, JSValueConst g)` |
| `throw_named` | function | `src/js_sandbox.c:693` | `static JSValue throw_named(JSContext *ctx, const char *name, const char *msg)` |
| `timespec_reached` | function | `src/js_sandbox.c:108` | `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)` |
| `undefined` | function | `src/js_sandbox.c:221` | `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx, exc, ` |
| `explicitly` | function | `src/js_trusted.c:344` | `* explicitly (no window, no document). Delivery is always a timer task. */
static const char JT_W...` |
| `hex_nibble` | function | `src/js_trusted.c:137` | `static int hex_nibble(char c)` |
| `jt_enable_open` | function | `src/js_trusted.c:26` | `jd_status jt_enable_open(js_context *ctx)` |
| `jt_enable_storage` | function | `src/js_trusted.c:275` | `jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len)` |
| `jt_enable_worker` | function | `src/js_trusted.c:425` | `jd_status jt_enable_worker(js_context *ctx)` |
| `jt_enable_ws` | function | `src/js_trusted.c:120` | `jd_status jt_enable_ws(js_context *ctx)` |
| `jt_seed_ctx` | struct | `src/js_trusted.c:263` | `` |
| `jt_seed_pair` | function | `src/js_trusted.c:265` | `static void jt_seed_pair(void *vctx, const char *k, size_t kl, const char *v, size_t vl)` |
| `jt_take_opens` | function | `src/js_trusted.c:42` | `char *jt_take_opens(js_context *ctx)` |
| `jt_take_storage` | function | `src/js_trusted.c:296` | `int jt_take_storage(js_context *ctx, char **out, size_t *len)` |
| `jt_take_ws` | function | `src/js_trusted.c:168` | `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap)` |
| `jt_ws_event` | function | `src/js_trusted.c:210` | `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len)` |
| `jt_ws_ops_free` | function | `src/js_trusted.c:132` | `void jt_ws_ops_free(jt_ws_op *ops, size_t n)` |
| `ws_payload` | function | `src/js_trusted.c:144` | `static char *ws_payload(int kind, const char *s, size_t n, size_t *out_len)` |
| `append_seg` | function | `src/link_nav.c:86` | `static int append_seg(char *body, size_t bodysz, size_t *blen,
                      const char *...` |
| `ci_prefix` | function | `src/link_nav.c:38` | `static int ci_prefix(const char *s, const char *prefix)` |
| `classify_block` | function | `src/link_nav.c:62` | `static ln_block_reason classify_block(const char *ref)` |
| `clean_href` | function | `src/link_nav.c:19` | `static int clean_href(const char *href, char *out, size_t outsz)` |
| `file_dir_len` | function | `src/link_nav.c:69` | `static size_t file_dir_len(const char *base)` |
| `last_seg_is_dotdot` | function | `src/link_nav.c:79` | `static int last_seg_is_dotdot(const char *body, size_t blen)` |
| `ln_block_reason_text` | function | `src/link_nav.c:241` | `const char *ln_block_reason_text(ln_block_reason reason)` |
| `ln_resolve` | function | `src/link_nav.c:172` | `ln_status ln_resolve(const char *base, const char *href, ln_result *out)` |
| `pop_seg` | function | `src/link_nav.c:98` | `static void pop_seg(char *body, size_t *blen)` |
| `resolve_file` | function | `src/link_nav.c:149` | `static int resolve_file(const char *base, const char *ref, char *out, size_t outsz)` |
| `LS_ARGON2_M_KIB` | macro | `src/local_store.c:713` | `#define LS_ARGON2_M_KIB` |
| `LS_ARGON2_P` | macro | `src/local_store.c:714` | `#define LS_ARGON2_P` |
| `LS_ARGON2_T` | macro | `src/local_store.c:712` | `#define LS_ARGON2_T` |
| `LS_KDF_ARGON2ID` | macro | `src/local_store.c:709` | `#define LS_KDF_ARGON2ID` |
| `LS_KDF_NONE` | macro | `src/local_store.c:708` | `#define LS_KDF_NONE` |
| `LS_VERSION` | macro | `src/local_store.c:707` | `#define LS_VERSION` |
| `OFF_AEAD` | macro | `src/local_store.c:719` | `#define OFF_AEAD` |
| `OFF_KDF` | macro | `src/local_store.c:720` | `#define OFF_KDF` |
| `OFF_MAGIC` | macro | `src/local_store.c:717` | `#define OFF_MAGIC` |
| `OFF_NONCE` | macro | `src/local_store.c:722` | `#define OFF_NONCE` |
| `OFF_SALT` | macro | `src/local_store.c:721` | `#define OFF_SALT` |
| `OFF_VERSION` | macro | `src/local_store.c:718` | `#define OFF_VERSION` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:3` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:14` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:25` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:36` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:47` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:58` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:69` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:80` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:91` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:102` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:113` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:124` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:135` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:146` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:157` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:168` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:179` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:190` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:201` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:212` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:223` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:234` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:245` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:256` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:267` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:278` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:289` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:300` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:311` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:322` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:333` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:344` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:355` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:366` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:377` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:388` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:399` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:410` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:421` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:432` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:443` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:454` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:465` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:476` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:487` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:498` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:509` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:520` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:531` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:542` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:553` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:564` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:575` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:586` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:597` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:608` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:619` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:630` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:641` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:652` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:663` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:698` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:6` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:17` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:28` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:39` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:50` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:61` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:72` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:83` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:94` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:105` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:116` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:127` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:138` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:149` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:160` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:171` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:182` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:193` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:204` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:215` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:226` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:237` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:248` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:259` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:270` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:281` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:292` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:303` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:314` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:325` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:336` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:347` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:358` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:369` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:380` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:391` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:402` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:413` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:424` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:435` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:446` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:457` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:468` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:479` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:490` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:501` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:512` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:523` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:534` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:545` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:556` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:567` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:578` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:589` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:600` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:611` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:622` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:633` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:644` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:655` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:666` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:701` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:9` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:20` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:31` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:42` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:53` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:64` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:75` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:86` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:97` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:108` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:119` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:130` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:141` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:152` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:163` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:174` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:185` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:196` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:207` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:218` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:229` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:240` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:251` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:262` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:273` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:284` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:295` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:306` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:317` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:328` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:339` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:350` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:361` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:372` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:383` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:394` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:405` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:416` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:427` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:438` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:449` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:460` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:471` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:482` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:493` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:504` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:515` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:526` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:537` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:548` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:559` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:570` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:581` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:592` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:603` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:614` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:625` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:636` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:647` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:658` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:669` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:704` | `#define OSSL_KDF_PARAM_THREADS` |
| `_GNU_SOURCE` | macro | `src/local_store.c:11` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:22` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:33` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:44` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:55` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:66` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:77` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:88` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:99` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:110` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:121` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:132` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:143` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:154` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:165` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:176` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:187` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:198` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:209` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:220` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:231` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:242` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:253` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:264` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:275` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:286` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:297` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:308` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:319` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:330` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:341` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:352` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:363` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:374` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:385` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:396` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:407` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:418` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:429` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:440` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:451` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:462` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:473` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:484` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:495` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:506` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:517` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:528` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:539` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:550` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:561` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:572` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:583` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:594` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:605` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:616` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:627` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:638` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:649` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:660` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:671` | `#define _GNU_SOURCE` |
| `aead_decrypt` | function | `src/local_store.c:802` | `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...` |
| `aead_encrypt` | function | `src/local_store.c:776` | `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...` |
| `argon2id_derive` | function | `src/local_store.c:738` | `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,
                          ...` |
| `cipher_for` | function | `src/local_store.c:728` | `static const EVP_CIPHER *cipher_for(ls_aead aead)` |
| `decrypt_blob` | function | `src/local_store.c:867` | `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,
         ...` |
| `ls_derive_key` | function | `src/local_store.c:767` | `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,
                        const...` |
| `ls_free` | function | `src/local_store.c:963` | `void ls_free(uint8_t *buf, size_t len)` |
| `ls_open` | function | `src/local_store.c:911` | `ls_status ls_open(const uint8_t key[LS_KEY_LEN],
                  const uint8_t *blob, size_t bl...` |
| `ls_open_passphrase` | function | `src/local_store.c:943` | `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,
                        ...` |
| `ls_seal` | function | `src/local_store.c:898` | `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,
                  const uint8_t *p...` |
| `ls_seal_passphrase` | function | `src/local_store.c:922` | `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,
          ...` |
| `seal_core` | function | `src/local_store.c:830` | `static ls_status seal_core(const uint8_t *key, ls_aead aead, uint8_t kdf_id,
                    ...` |
| `_POSIX_C_SOURCE` | macro | `src/media_decoder.c:23` | `#define _POSIX_C_SOURCE` |
| `av_rescale_q` | function | `src/media_decoder.c:217` | `return av_rescale_q(f->pts, tb, (AVRational)` |
| `decode_segment` | function | `src/media_decoder.c:276` | `static int decode_segment(decoder_ctx *dc, const uint8_t *data, size_t len)` |
| `decoder_close` | function | `src/media_decoder.c:78` | `static void decoder_close(decoder_ctx *dc)` |
| `decoder_ctx` | struct | `src/media_decoder.c:54` | `` |
| `decoder_init` | function | `src/media_decoder.c:96` | `static int decoder_init(decoder_ctx *dc, const uint8_t *data, size_t len)` |
| `dropped` | function | `src/media_decoder.c:369` | `* the codec in permanent EOF state: every segment after the first decoded * one was silently dropped ("plays a couple of` |
| `fd` | function | `src/media_decoder.c:469` | `* prevent the Wayland display fd (inherited from the parent) from * surviving the exec. An inherited Wayland fd would be` |
| `frame_pts_us` | function | `src/media_decoder.c:215` | `static int64_t frame_pts_us(const AVFrame *f, AVRational tb, int64_t fallback)` |
| `media_decoder_run` | function | `src/media_decoder.c:379` | `void media_decoder_run(int out_fd, int cmd_fd)` |
| `media_decoder_spawn` | function | `src/media_decoder.c:449` | `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd)` |
| `open` | function | `src/media_decoder.c:18` | `*
 * Sandbox: the decoder needs open() for shared libraries (.so loading) and
 * brk/mmap for FFm...` |
| `out_fd` | type_alias | `src/media_decoder.c:53` | `typedef struct decoder_ctx { int out_fd;` |
| `send_audio_frame` | function | `src/media_decoder.c:242` | `static void send_audio_frame(decoder_ctx *dc, int64_t pts_us)` |
| `send_video_frame` | function | `src/media_decoder.c:222` | `static void send_video_frame(decoder_ctx *dc, int64_t pts_us)` |
| `NR_MAX_HOST` | macro | `src/net_realm.c:15` | `#define NR_MAX_HOST` |
| `ends_with_realm` | function | `src/net_realm.c:23` | `static int ends_with_realm(const char *host, size_t n, const char *suffix)` |
| `host_of` | function | `src/net_realm.c:52` | `static int host_of(const char *url, char *out, size_t out_size)` |
| `lower` | function | `src/net_realm.c:17` | `static char lower(char c)` |
| `nr_classify_host` | function | `src/net_realm.c:34` | `nr_realm nr_classify_host(const char *host)` |
| `nr_classify_url` | function | `src/net_realm.c:68` | `nr_realm nr_classify_url(const char *url)` |
| `nr_realm_allows_http` | function | `src/net_realm.c:88` | `int nr_realm_allows_http(nr_realm r)` |
| `nr_realm_name` | function | `src/net_realm.c:94` | `const char *nr_realm_name(nr_realm r)` |
| `nr_route_for` | function | `src/net_realm.c:74` | `nr_route nr_route_for(const char *url, nr_config cfg)` |
| `nr_route_name` | function | `src/net_realm.c:103` | `const char *nr_route_name(nr_route r)` |
| `LL_FS_BASE` | macro | `src/os_sandbox.c:254` | `#define LL_FS_BASE` |
| `OS_ALLOWED_N` | macro | `src/os_sandbox.c:50` | `#define OS_ALLOWED_N` |
| `OS_SECCOMP_ARCH` | macro | `src/os_sandbox.c:140` | `#  define OS_SECCOMP_ARCH` |
| `OS_SECCOMP_ARCH` | macro | `src/os_sandbox.c:142` | `#  define OS_SECCOMP_ARCH` |
| `_GNU_SOURCE` | macro | `src/os_sandbox.c:13` | `#define _GNU_SOURCE` |
| `excluded` | function | `src/os_sandbox.c:89` | `* intentionally excluded (they need /proc remounting and a post-unshare fork). */
int os_namespac...` |
| `fields` | function | `src/os_sandbox.c:303` | `* long as the unknown trailing fields (net/scoped) are zero, which they are. */ int rfd = (int)ll_create_ruleset(&attr, ` |
| `headroom` | function | `src/os_sandbox.c:203` | `* wide headroom (room for ~125 allowed syscalls). */ prog[at_mmap].jt = (unsigned char)(prot_check - (at_mmap + 1));` |
| `ll_add_rule` | function | `src/os_sandbox.c:244` | `static long ll_add_rule(int fd, enum landlock_rule_type type,
                        const void ...` |
| `ll_create_ruleset` | function | `src/os_sandbox.c:239` | `static long ll_create_ruleset(const struct landlock_ruleset_attr *attr,
                         ...` |
| `ll_handled` | function | `src/os_sandbox.c:265` | `static uint64_t ll_handled(int abi)` |
| `ll_read_access` | function | `src/os_sandbox.c:279` | `static uint64_t ll_read_access(uint64_t handled)` |
| `ll_restrict_self` | function | `src/os_sandbox.c:249` | `static long ll_restrict_self(int fd, uint32_t flags)` |
| `number` | function | `src/os_sandbox.c:157` | `* number (x32/i386 on x86_64, AArch32 on aarch64). */ prog[n++] = (struct sock_filter)BPF_STMT(BPF_LD \| BPF_W \| BPF_AB` |
| `os_harden` | function | `src/os_sandbox.c:113` | `os_status os_harden(os_violation action)` |
| `os_harden` | function | `src/os_sandbox.c:145` | `os_status os_harden(os_violation action)` |
| `os_isolate_namespaces` | function | `src/os_sandbox.c:94` | `os_status os_isolate_namespaces(void)` |
| `os_isolate_namespaces` | function | `src/os_sandbox.c:116` | `os_status os_isolate_namespaces(void)` |
| `os_landlock_abi` | function | `src/os_sandbox.c:285` | `int os_landlock_abi(void)` |
| `os_landlock_abi` | function | `src/os_sandbox.c:331` | `int os_landlock_abi(void)` |
| `os_landlock_restrict` | function | `src/os_sandbox.c:291` | `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)` |
| `os_landlock_restrict` | function | `src/os_sandbox.c:332` | `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)` |
| `os_namespace_flags` | function | `src/os_sandbox.c:115` | `int os_namespace_flags(void)` |
| `os_no_dump` | function | `src/os_sandbox.c:75` | `os_status os_no_dump(void)` |
| `os_no_dump` | function | `src/os_sandbox.c:111` | `os_status os_no_dump(void)` |
| `os_policy_allows` | function | `src/os_sandbox.c:52` | `int os_policy_allows(long syscall_nr)` |
| `os_policy_allows` | function | `src/os_sandbox.c:106` | `int os_policy_allows(long syscall_nr)` |
| `os_policy_size` | function | `src/os_sandbox.c:59` | `size_t os_policy_size(void)` |
| `os_policy_size` | function | `src/os_sandbox.c:107` | `size_t os_policy_size(void)` |
| `os_prot_allowed` | function | `src/os_sandbox.c:65` | `int os_prot_allowed(long syscall_nr, unsigned long prot)` |
| `os_prot_allowed` | function | `src/os_sandbox.c:108` | `int os_prot_allowed(long syscall_nr, unsigned long prot)` |
| `PV_COLOR_TOKEN_MAX` | macro | `src/page_view.c:1040` | `#define PV_COLOR_TOKEN_MAX` |
| `PV_FONT_CHAIN_MAX` | macro | `src/page_view.c:58` | `#define PV_FONT_CHAIN_MAX` |
| `PV_FONT_PCT_MAX` | macro | `src/page_view.c:60` | `#define PV_FONT_PCT_MAX` |
| `PV_FONT_PCT_MIN` | macro | `src/page_view.c:59` | `#define PV_FONT_PCT_MIN` |
| `PV_FONT_REL_MAX` | macro | `src/page_view.c:52` | `#define PV_FONT_REL_MAX` |
| `PV_FONT_REL_MIN` | macro | `src/page_view.c:51` | `#define PV_FONT_REL_MIN` |
| `PV_MAX_BOXES` | macro | `src/page_view.c:1087` | `#define PV_MAX_BOXES` |
| `PV_MAX_CONTAINERS` | macro | `src/page_view.c:1078` | `#define PV_MAX_CONTAINERS` |
| `PV_MAX_DIM` | macro | `src/page_view.c:46` | `#define PV_MAX_DIM` |
| `PV_MAX_GRID_COLS` | macro | `src/page_view.c:1079` | `#define PV_MAX_GRID_COLS` |
| `PV_MAX_INLINE_ROW_ITEMS` | macro | `src/page_view.c:2388` | `#define PV_MAX_INLINE_ROW_ITEMS` |
| `PV_MAX_STYLE_BYTES` | macro | `src/page_view.c:4211` | `#define PV_MAX_STYLE_BYTES` |
| `PV_NODE_MAP_INIT_CAP` | macro | `src/page_view.c:270` | `#define PV_NODE_MAP_INIT_CAP` |
| `PV_TEXTLESS_DEPTH_MAX` | macro | `src/page_view.c:2591` | `#define PV_TEXTLESS_DEPTH_MAX` |
| `URL` | function | `src/page_view.c:5304` | `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `_POSIX_C_SOURCE` | macro | `src/page_view.c:10` | `#define _POSIX_C_SOURCE` |
| `address` | function | `src/page_view.c:1090` | `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <= BT_MAX_POS` |
| `annotate_flow_run` | function | `src/page_view.c:1581` | `static void annotate_flow_run(pv_view *v, pv_container_reg *reg, pv_item_track *items,
          ...` |
| `annotate_replaced_run` | function | `src/page_view.c:4340` | `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,
                            ...` |
| `appended` | function | `src/page_view.c:5881` | `* AFTER the run is appended (so THIS run's brk stays) but BEFORE the next. */
        if (cont.fl...` |
| `ascii_ieq` | function | `src/page_view.c:3634` | `static int ascii_ieq(const char *s, const char *lit)` |
| `attr_dup` | function | `src/page_view.c:3646` | `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)` |
| `attributes` | function | `src/page_view.c:3568` | `* carries those attributes (spec/css.md, "Root matcher"). */
static int root_els_match(void *ctx,...` |
| `bgcolor_attr` | function | `src/page_view.c:1068` | `static int bgcolor_attr(lxb_dom_element_t *el)` |
| `block_id` | function | `src/page_view.c:5173` | `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it falls ` |
| `box_reg_free` | function | `src/page_view.c:1649` | `static void box_reg_free(pv_box_reg *r)` |
| `box_reg_id` | function | `src/page_view.c:1881` | `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,
           ...` |
| `boxdef_from_style` | function | `src/page_view.c:1658` | `static void boxdef_from_style(pv_box_def *d, const css_style *cs)` |
| `builder` | function | `src/page_view.c:2302` | `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box
 * (the ...` |
| `cached_pseudo_style` | function | `src/page_view.c:2244` | `static css_style cached_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet,
             ...` |
| `causes_block_break` | function | `src/page_view.c:928` | `static int causes_block_break(lxb_tag_id_t t, css_display display)` |
| `cell_anchors` | function | `src/page_view.c:4106` | `static const lxb_dom_node_t *cell_anchors(const lxb_dom_node_t *cell, int *count)` |
| `cell_has_nested_table` | function | `src/page_view.c:4086` | `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)` |
| `chain` | type_alias | `src/page_view.c:2028` | `typedef struct pv_var_node { cvr_chain chain;` |
| `child` | function | `src/page_view.c:1098` | `* child (NULL = anonymous item: text directly inside the container);` |
| `children_all_inline_block` | function | `src/page_view.c:2416` | `static int children_all_inline_block(const lxb_dom_node_t *p, const css_sheet *sheet,
           ...` |
| `classify_input` | function | `src/page_view.c:3728` | `static pv_input_type classify_input(const char *type)` |
| `col_has_free_space` | function | `src/page_view.c:2435` | `static int col_has_free_space(const css_style *cs)` |
| `collapse_ws` | function | `src/page_view.c:3327` | `static char *collapse_ws(const char *s, size_t n)` |
| `collect_page_css` | function | `src/page_view.c:4406` | `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,
                     ...` |
| `collect_text` | function | `src/page_view.c:3704` | `static char *collect_text(const lxb_dom_node_t *el)` |
| `cols` | type_alias | `src/page_view.c:1100` | `typedef struct pv_cont_info { int id, display, gap, justify, cols;` |
| `cont_def_reset` | function | `src/page_view.c:1520` | `static void cont_def_reset(pv_cont_def *d)` |
| `container` | function | `src/page_view.c:3066` | `* membership in this container (and none in any container further out,
                 * since i...` |
| `container_id` | function | `src/page_view.c:1535` | `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)` |
| `content` | function | `src/page_view.c:1022` | `* a <noscript> ancestor also suppresses content (the script would run, so the * fallback is hidden);` |
| `control` | function | `src/page_view.c:4857` | `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);` |
| `cp1252_to_ucs` | function | `src/page_view.c:84` | `static unsigned int cp1252_to_ucs(unsigned char c)` |
| `css_has_boxdeco` | function | `src/page_view.c:1377` | `static int css_has_boxdeco(const css_style *cs)` |
| `css_has_hbox` | function | `src/page_view.c:1303` | `static int css_has_hbox(const css_style *cs)` |
| `css_has_position` | function | `src/page_view.c:1372` | `static int css_has_position(const css_style *cs)` |
| `css_hbox_resolve` | function | `src/page_view.c:1324` | `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)` |
| `css_to_fx_justify` | function | `src/page_view.c:2331` | `static int css_to_fx_justify(css_justify j)` |
| `dimensions` | function | `src/page_view.c:3509` | `* viewport dimensions (data: inline detection, <picture> <source> scanning). */
static void srcse...` |
| `dup_n` | function | `src/page_view.c:145` | `static char *dup_n(const char *s, size_t n)` |
| `element_is_content_leaf` | function | `src/page_view.c:2628` | `static int element_is_content_leaf(const lxb_dom_node_t *n, const css_sheet *sheet,
             ...` |
| `engine` | function | `src/page_view.c:5826` | `* layout engine (contiguous item gather) drops every cell onto its own row and
         * a 2-col...` |
| `find_body` | function | `src/page_view.c:3541` | `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)` |
| `find_root_els` | function | `src/page_view.c:3554` | `static pv_root_els find_root_els(lxb_dom_node_t *root)` |
| `flex_column_flows_as_block` | function | `src/page_view.c:2446` | `static int flex_column_flows_as_block(const lxb_dom_node_t *el, const css_style *cs,
            ...` |
| `float` | function | `src/page_view.c:3243` | `* genuinely nested float (oid != id) takes the deferred-column path. */
    if (cont->float_oid =...` |
| `flow` | function | `src/page_view.c:5726` | `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through it. ` |
| `flow_table` | function | `src/page_view.c:4145` | `static int flow_table(pv_flow_reg *fr, const lxb_dom_node_t *table)` |
| `fold_column_gap` | function | `src/page_view.c:2478` | `static void fold_column_gap(const lxb_dom_node_t *el, css_style *cs,
                            ...` |
| `font_color_attr` | function | `src/page_view.c:1062` | `static int font_color_attr(lxb_dom_element_t *el)` |
| `form_for` | function | `src/page_view.c:3675` | `static int form_for(const form_table *ft, const lxb_dom_node_t *n,
                    const lxb_...` |
| `form_rec` | struct | `src/page_view.c:3616` | `` |
| `form_table` | struct | `src/page_view.c:3622` | `` |
| `forms_add` | function | `src/page_view.c:3655` | `static int forms_add(form_table *ft, const lxb_dom_node_t *node)` |
| `forms_free` | function | `src/page_view.c:3627` | `static void forms_free(form_table *ft)` |
| `generates_box` | function | `src/page_view.c:909` | `static int generates_box(lxb_tag_id_t t, css_display display)` |
| `generates_box_style` | function | `src/page_view.c:921` | `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)` |
| `glyphs` | function | `src/page_view.c:1787` | `* glyphs (the runs carry it as their fill source);` |
| `heading_level` | function | `src/page_view.c:984` | `static int heading_level(lxb_tag_id_t t)` |
| `height` | function | `src/page_view.c:5075` | `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `here` | function | `src/page_view.c:1749` | `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3 sectio` |
| `id` | function | `src/page_view.c:1118` | `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);` |
| `ignored` | function | `src/page_view.c:577` | `* source is ignored (fail-visible: never invisible text from half a
     * pattern). A real text-...` |
| `in_boilerplate_subtree` | function | `src/page_view.c:4275` | `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` |
| `in_closed_details_subtree` | function | `src/page_view.c:4290` | `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` |
| `in_flow_table_cell` | function | `src/page_view.c:4157` | `static int in_flow_table_cell(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,
           ...` |
| `in_hidden_subtree` | function | `src/page_view.c:4258` | `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
               ...` |
| `in_mixed_line` | function | `src/page_view.c:2400` | `static int in_mixed_line(const lxb_dom_node_t *p, const css_sheet *sheet,
                       ...` |
| `in_skipped_subtree` | function | `src/page_view.c:1025` | `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
              ...` |
| `is_block_like` | function | `src/page_view.c:858` | `static int is_block_like(lxb_tag_id_t t, css_display display)` |
| `is_block_like_style` | function | `src/page_view.c:897` | `static int is_block_like_style(lxb_tag_id_t t, const css_style *cs)` |
| `is_block_tag` | function | `src/page_view.c:833` | `static int is_block_tag(lxb_tag_id_t t)` |
| `is_bold_tag` | function | `src/page_view.c:2350` | `static int is_bold_tag(lxb_tag_id_t t)` |
| `is_inline_level_style` | function | `src/page_view.c:2392` | `static int is_inline_level_style(lxb_tag_id_t t, const css_style *cs)` |
| `is_italic_tag` | function | `src/page_view.c:2355` | `static int is_italic_tag(lxb_tag_id_t t)` |
| `is_layout_container` | function | `src/page_view.c:2502` | `static int is_layout_container(const lxb_dom_node_t *el, const css_style *cs,
                   ...` |
| `is_skipped_tag` | function | `src/page_view.c:996` | `static int is_skipped_tag(lxb_tag_id_t t)` |
| `it` | function | `src/page_view.c:1209` | `* it (they inherit in CSS). list_style drives the <li> marker (structural);` |
| `item_ordinal` | function | `src/page_view.c:1181` | `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)` |
| `item_sizes_itself` | function | `src/page_view.c:2516` | `static int item_sizes_itself(const lxb_dom_node_t *el, const css_style *cs,
                     ...` |
| `li_is_list_item` | function | `src/page_view.c:2538` | `static int li_is_list_item(const lxb_dom_node_t *li, const css_sheet *sheet,
                    ...` |
| `li_ordinal` | function | `src/page_view.c:3900` | `static int li_ordinal(const lxb_dom_node_t *li)` |
| `line` | function | `src/page_view.c:5835` | `* to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);` |
| `links` | function | `src/page_view.c:4124` | `* its links (the Hacker News case: every story link lives inside a <td>), so the
 * caller flows ...` |
| `list_marker` | function | `src/page_view.c:3951` | `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,
                  ...` |
| `margins` | function | `src/page_view.c:2948` | `* margins (boxdef_from_style) and the painter applies them when
                         * it ope...` |
| `mb` | type_alias | `src/page_view.c:1193` | `typedef struct pv_box_info { int l, r, w, center, mt, mb;` |
| `nearest_cell` | function | `src/page_view.c:4071` | `static const lxb_dom_node_t *nearest_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
  ...` |
| `nearest_table` | function | `src/page_view.c:4010` | `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
 ...` |
| `next_skip` | function | `src/page_view.c:4095` | `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)` |
| `node_next` | function | `src/page_view.c:823` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `node_table_role` | function | `src/page_view.c:3992` | `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `node_tag` | function | `src/page_view.c:1017` | `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)` |
| `opens` | function | `src/page_view.c:2920` | `* painter applies it when the box opens (band/shared context) — seeding
             * it onto ru...` |
| `outermost` | function | `src/page_view.c:2871` | `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);` |
| `paints` | function | `src/page_view.c:937` | `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas
 * vacías"). Comment a...` |
| `paints` | function | `src/page_view.c:2565` | `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas vacías").
 *
 * A chil...` |
| `parent_is_table_internal` | function | `src/page_view.c:4044` | `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `parse_dim` | function | `src/page_view.c:3351` | `static int parse_dim(const lxb_char_t *s, size_t len)` |
| `positions` | function | `src/page_view.c:134` | `* positions (cp == 0) keep the legacy '?' fallback. */ unsigned int cp = cp1252_to_ucs(c);` |
| `present` | function | `src/page_view.c:3368` | `* when no width descriptors are present (density-only or bare URLs). */
static void srcset_best_u...` |
| `pseudo_box_reg` | function | `src/page_view.c:1910` | `static int pseudo_box_reg(pv_box_reg *r, const lxb_dom_node_t *el, int which,
                   ...` |
| `pseudo_generates_box` | function | `src/page_view.c:1931` | `static int pseudo_generates_box(const css_style *ps)` |
| `pseudo_is_block` | function | `src/page_view.c:1948` | `static int pseudo_is_block(const css_style *ps)` |
| `pseudo_is_oof` | function | `src/page_view.c:1944` | `static int pseudo_is_oof(const css_style *ps)` |
| `pseudo_key` | function | `src/page_view.c:1954` | `static const void *pseudo_key(const lxb_dom_node_t *el, int which)` |
| `pv_add_box_def` | function | `src/page_view.c:772` | `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)` |
| `pv_add_cont_def` | function | `src/page_view.c:750` | `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)` |
| `pv_append` | function | `src/page_view.c:335` | `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    c...` |
| `pv_append_image` | function | `src/page_view.c:369` | `pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          con...` |
| `pv_append_input` | function | `src/page_view.c:399` | `pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_...` |
| `pv_append_svg` | function | `src/page_view.c:475` | `pv_status pv_append_svg(pv_view *v, int heading, int block_break,
                        const c...` |
| `pv_append_video` | function | `src/page_view.c:439` | `pv_status pv_append_video(pv_view *v, int heading, int block_break,
                          con...` |
| `pv_at` | function | `src/page_view.c:806` | `const pv_run *pv_at(const pv_view *v, size_t i)` |
| `pv_box_at` | function | `src/page_view.c:815` | `const pv_box_def *pv_box_at(const pv_view *v, size_t i)` |
| `pv_box_count` | function | `src/page_view.c:811` | `size_t pv_box_count(const pv_view *v)` |
| `pv_box_info` | struct | `src/page_view.c:1193` | `` |
| `pv_box_reg` | struct | `src/page_view.c:1610` | `` |
| `pv_build` | function | `src/page_view.c:4310` | `pv_status pv_build(const hp_document *doc, pv_view **out)` |
| `pv_build_ex` | function | `src/page_view.c:4314` | `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)` |
| `pv_build_full` | function | `src/page_view.c:4318` | `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                     ...` |
| `pv_build_styled` | function | `src/page_view.c:4435` | `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                   ...` |
| `pv_cache_find` | function | `src/page_view.c:2103` | `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cache_put` | function | `src/page_view.c:2123` | `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,
                     ...` |
| `pv_cache_reindex` | function | `src/page_view.c:2061` | `static void pv_cache_reindex(pv_style_cache *c)` |
| `pv_cached_font_px` | function | `src/page_view.c:2118` | `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cont_at` | function | `src/page_view.c:767` | `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)` |
| `pv_cont_count` | function | `src/page_view.c:763` | `size_t pv_cont_count(const pv_view *v)` |
| `pv_cont_info` | struct | `src/page_view.c:1100` | `` |
| `pv_container_reg` | struct | `src/page_view.c:1510` | `` |
| `pv_content_hidden` | function | `src/page_view.c:1213` | `int pv_content_hidden(int box_hidden, int run_visibility)` |
| `pv_count` | function | `src/page_view.c:802` | `size_t pv_count(const pv_view *v)` |
| `pv_css_drops` | function | `src/page_view.c:5961` | `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,
                       const cha...` |
| `pv_flow_reg` | struct | `src/page_view.c:2647` | `` |
| `pv_flow_reg` | struct | `src/page_view.c:3978` | `` |
| `pv_free` | function | `src/page_view.c:785` | `void pv_free(pv_view *v)` |
| `pv_item_track` | struct | `src/page_view.c:1174` | `` |
| `pv_mauto_of` | function | `src/page_view.c:1317` | `static int pv_mauto_of(const css_style *cs)` |
| `pv_new` | function | `src/page_view.c:331` | `pv_view *pv_new(void)` |
| `pv_node_map` | struct | `src/page_view.c:272` | `` |
| `pv_node_map_build` | function | `src/page_view.c:322` | `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root)` |
| `pv_node_map_free` | function | `src/page_view.c:286` | `static void pv_node_map_free(pv_node_map *m)` |
| `pv_node_map_init` | function | `src/page_view.c:278` | `static int pv_node_map_init(pv_node_map *m)` |
| `pv_parent_element` | function | `src/page_view.c:2183` | `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)` |
| `pv_ptr_hash` | function | `src/page_view.c:2053` | `static size_t pv_ptr_hash(const void *p)` |
| `pv_ptrmap` | struct | `src/page_view.c:1962` | `` |
| `pv_ptrmap_free` | function | `src/page_view.c:2008` | `static void pv_ptrmap_free(pv_ptrmap *m)` |
| `pv_ptrmap_get` | function | `src/page_view.c:1978` | `static int pv_ptrmap_get(const pv_ptrmap *m, const void *k, int *out)` |
| `pv_ptrmap_put` | function | `src/page_view.c:1986` | `static void pv_ptrmap_put(pv_ptrmap *m, const void *k, int v)` |
| `pv_ptrmap_slot` | function | `src/page_view.c:1968` | `static size_t pv_ptrmap_slot(const pv_ptrmap *m, const void *k)` |
| `pv_root_els` | struct | `src/page_view.c:3550` | `` |
| `pv_set_bgcolor` | function | `src/page_view.c:521` | `void pv_set_bgcolor(pv_view *v, int bg_rgb)` |
| `pv_set_block_id` | function | `src/page_view.c:722` | `void pv_set_block_id(pv_view *v, int block_id)` |
| `pv_set_box` | function | `src/page_view.c:681` | `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                int box_center, int ...` |
| `pv_set_box_maxw` | function | `src/page_view.c:704` | `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct)` |
| `pv_set_box_pct` | function | `src/page_view.c:693` | `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,
                    ...` |
| `pv_set_color` | function | `src/page_view.c:516` | `void pv_set_color(pv_view *v, int fg_rgb)` |
| `pv_set_cont_box` | function | `src/page_view.c:632` | `void pv_set_cont_box(pv_view *v, int cont_box_id)` |
| `pv_set_cont_item` | function | `src/page_view.c:654` | `void pv_set_cont_item(pv_view *v, int cont_item)` |
| `pv_set_container` | function | `src/page_view.c:592` | `void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_g...` |
| `pv_set_emphasis` | function | `src/page_view.c:504` | `void pv_set_emphasis(pv_view *v, int bold, int italic)` |
| `pv_set_flex` | function | `src/page_view.c:636` | `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                 int...` |
| `pv_set_flex_mauto` | function | `src/page_view.c:648` | `void pv_set_flex_mauto(pv_view *v, int mauto)` |
| `pv_set_float` | function | `src/page_view.c:659` | `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear,
                int ...` |
| `pv_set_grad_text` | function | `src/page_view.c:537` | `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)` |
| `pv_set_grid` | function | `src/page_view.c:618` | `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)` |
| `pv_set_grid_area` | function | `src/page_view.c:611` | `void pv_set_grid_area(pv_view *v, int row_start, int col_start)` |
| `pv_set_grid_rows` | function | `src/page_view.c:628` | `void pv_set_grid_rows(pv_view *v, int grid_rows)` |
| `pv_set_indent` | function | `src/page_view.c:511` | `void pv_set_indent(pv_view *v, int indent)` |
| `pv_set_input_checked` | function | `src/page_view.c:737` | `void pv_set_input_checked(pv_view *v, int checked)` |
| `pv_set_input_select_opts` | function | `src/page_view.c:742` | `void pv_set_input_select_opts(pv_view *v, const char *select_opts)` |
| `pv_set_node_id` | function | `src/page_view.c:717` | `void pv_set_node_id(pv_view *v, dom_node_id node_id)` |
| `pv_set_oof` | function | `src/page_view.c:732` | `void pv_set_oof(pv_view *v, int oof)` |
| `pv_set_own_box` | function | `src/page_view.c:727` | `void pv_set_own_box(pv_view *v, int box_id)` |
| `pv_set_row_span` | function | `src/page_view.c:607` | `void pv_set_row_span(pv_view *v, int row_span)` |
| `pv_set_text_ext` | function | `src/page_view.c:545` | `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)` |
| `pv_set_text_style` | function | `src/page_view.c:526` | `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,
                ...` |
| `pv_set_ua_tag` | function | `src/page_view.c:711` | `void pv_set_ua_tag(pv_view *v, int ua_tag)` |
| `pv_style_cache` | struct | `src/page_view.c:2033` | `` |
| `pv_style_cache_free` | function | `src/page_view.c:2089` | `static void pv_style_cache_free(pv_style_cache *c)` |
| `pv_style_cache_init` | function | `src/page_view.c:2071` | `static int pv_style_cache_init(pv_style_cache *c)` |
| `pv_text_ext_merge` | function | `src/page_view.c:1245` | `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)` |
| `pv_text_ext_reset` | function | `src/page_view.c:1219` | `void pv_text_ext_reset(pv_text_ext *e)` |
| `pv_var_node` | struct | `src/page_view.c:2028` | `` |
| `pv_var_push` | function | `src/page_view.c:2162` | `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,
                      ...` |
| `px` | function | `src/page_view.c:5008` | `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */
                if (iw <...` |
| `resolve_context` | function | `src/page_view.c:2651` | `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                ...` |
| `resolves` | function | `src/page_view.c:887` | `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close
 * button/tooltip w...` |
| `roman_marker` | function | `src/page_view.c:3926` | `static void roman_marker(int n, int upper, char *out, size_t cap)` |
| `run_init_common` | function | `src/page_view.c:159` | `static void run_init_common(pv_run *r)` |
| `serialize_subtree` | function | `src/page_view.c:3308` | `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)` |
| `size` | function | `src/page_view.c:2282` | `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */
static void app...` |
| `srcset_slot_width` | function | `src/page_view.c:3463` | `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,
                              ...` |
| `string` | function | `src/page_view.c:3579` | `* Returns a heap string (caller frees) or NULL when neither carries a class —
 * NULL simply mean...` |
| `subtree_has_own_text` | function | `src/page_view.c:2608` | `static int subtree_has_own_text(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
            ...` |
| `subtree_is_oof` | function | `src/page_view.c:2262` | `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,
                     ...` |
| `sz_count` | function | `src/page_view.c:3286` | `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)` |
| `sz_fill` | struct | `src/page_view.c:3294` | `` |
| `sz_write` | function | `src/page_view.c:3300` | `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)` |
| `table` | function | `src/page_view.c:4166` | `* FLOW table (multi-link: walked so its links survive) do NOT suppress their
 * content -- their ...` |
| `table_columns` | function | `src/page_view.c:4184` | `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)` |
| `trying` | function | `src/page_view.c:1620` | `* a real page passes without trying (slashdot's front page saturates it), and past
 * it box_reg_...` |
| `ua_tag_of` | function | `src/page_view.c:962` | `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)` |
| `under_unrendered` | function | `src/page_view.c:3691` | `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)` |
| `utf8_encode` | function | `src/page_view.c:98` | `static size_t utf8_encode(unsigned int cp, char *out)` |
| `utf8_sanitized_dup` | function | `src/page_view.c:111` | `static char *utf8_sanitized_dup(const char *s)` |
| `walk` | function | `src/page_view.c:3150` | `* far on this walk (they are all inside this element). */

                        /* The innermo...` |
| `pe_build_path` | function | `src/pdf_export.c:91` | `pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz)` |
| `pe_build_path_ext` | function | `src/pdf_export.c:66` | `pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,
                ...` |
| `pe_paginate` | function | `src/pdf_export.c:95` | `size_t pe_paginate(const double *tops, const double *heights, size_t n,
                   double...` |
| `pe_safe_basename` | function | `src/pdf_export.c:25` | `pe_status pe_safe_basename(const char *title, char *out, size_t outsz)` |
| `PT_LINE_CAP` | macro | `src/perf_trace.c:107` | `#define PT_LINE_CAP` |
| `cmp_u64` | function | `src/perf_trace.c:71` | `static int cmp_u64(const void *a, const void *b)` |
| `pt_count` | function | `src/perf_trace.c:35` | `size_t pt_count(const pt_trace *t, pt_stage stage)` |
| `pt_elapsed_us` | function | `src/perf_trace.c:21` | `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us)` |
| `pt_format` | function | `src/perf_trace.c:109` | `size_t pt_format(const pt_trace *t, char *buf, size_t cap)` |
| `pt_init` | function | `src/perf_trace.c:16` | `void pt_init(pt_trace *t)` |
| `pt_last_us` | function | `src/perf_trace.c:40` | `uint64_t pt_last_us(const pt_trace *t, pt_stage stage)` |
| `pt_max_us` | function | `src/perf_trace.c:60` | `uint64_t pt_max_us(const pt_trace *t, pt_stage stage)` |
| `pt_median_us` | function | `src/perf_trace.c:79` | `uint64_t pt_median_us(const pt_trace *t, pt_stage stage)` |
| `pt_min_us` | function | `src/perf_trace.c:49` | `uint64_t pt_min_us(const pt_trace *t, pt_stage stage)` |
| `pt_record` | function | `src/perf_trace.c:26` | `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us)` |
| `pt_stage_name` | function | `src/perf_trace.c:89` | `const char *pt_stage_name(pt_stage stage)` |
| `PF_MAX_URL` | macro | `src/prefetch.c:21` | `#define PF_MAX_URL` |
| `_POSIX_C_SOURCE` | macro | `src/prefetch.c:12` | `#define _POSIX_C_SOURCE` |
| `attr_span` | struct | `src/prefetch.c:62` | `` |
| `ci_eq_span` | function | `src/prefetch.c:55` | `static int ci_eq_span(const char *s, size_t n, const char *kw)` |
| `ci_find` | function | `src/prefetch.c:46` | `static const char *ci_find(const char *p, const char *end, const char *kw)` |
| `ci_starts` | function | `src/prefetch.c:37` | `static int ci_starts(const char *p, const char *end, const char *kw)` |
| `emit` | function | `src/prefetch.c:117` | `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)` |
| `is_name_char` | function | `src/prefetch.c:27` | `static int is_name_char(char c)` |
| `is_ws` | function | `src/prefetch.c:23` | `static int is_ws(char c)` |
| `lower` | function | `src/prefetch.c:32` | `static int lower(int c)` |
| `pf_list_free` | function | `src/prefetch.c:193` | `void pf_list_free(pf_list *l)` |
| `pf_pool_finish` | function | `src/prefetch.c:310` | `void pf_pool_finish(pf_pool *p)` |
| `pf_pool_start` | function | `src/prefetch.c:227` | `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                  pf_fetch_f...` |
| `pf_pool_take` | function | `src/prefetch.c:271` | `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,
                 char **body,...` |
| `pf_pooled_fetch` | function | `src/prefetch.c:324` | `int pf_pooled_fetch(void *vctx, const char *method, const char *url,
                    const ch...` |
| `pf_scan` | function | `src/prefetch.c:130` | `int pf_scan(const char *html, size_t len, pf_list *out)` |
| `pf_worker` | function | `src/prefetch.c:201` | `static void *pf_worker(void *arg)` |
| `PREFS_MAGIC` | macro | `src/prefs.c:20` | `#define PREFS_MAGIC` |
| `_POSIX_C_SOURCE` | macro | `src/prefs.c:11` | `#define _POSIX_C_SOURCE` |
| `apply_kv` | function | `src/prefs.c:225` | `static void apply_kv(prefs_state *out, const char *key, long val)` |
| `bookmark_push` | function | `src/prefs.c:91` | `static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title)` |
| `ci_contains` | function | `src/prefs.c:314` | `static int ci_contains(const char *s, const char *q)` |
| `ci_eq` | function | `src/prefs.c:300` | `static int ci_eq(char a, char b)` |
| `ci_starts` | function | `src/prefs.c:306` | `static int ci_starts(const char *s, const char *q)` |
| `history_push_back` | function | `src/prefs.c:109` | `static prefs_status history_push_back(prefs_state *p, const char *url)` |
| `prefs_bookmark_index` | function | `src/prefs.c:125` | `int prefs_bookmark_index(const prefs_state *p, const char *url)` |
| `prefs_bookmark_toggle` | function | `src/prefs.c:132` | `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,
                             ...` |
| `prefs_bookmarks_page` | function | `src/prefs.c:408` | `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)` |
| `prefs_format` | function | `src/prefs.c:183` | `prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len)` |
| `prefs_free` | function | `src/prefs.c:74` | `void prefs_free(prefs_state *p)` |
| `prefs_history_add` | function | `src/prefs.c:152` | `prefs_status prefs_history_add(prefs_state *p, const char *url)` |
| `prefs_init` | function | `src/prefs.c:66` | `void prefs_init(prefs_state *p)` |
| `prefs_parse` | function | `src/prefs.c:241` | `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)` |
| `prefs_suggest` | function | `src/prefs.c:344` | `int prefs_suggest(const prefs_state *p, const char *query,
                  char *out, size_t ro...` |
| `sb_esc` | function | `src/prefs.c:387` | `static void sb_esc(sbuf *b, const char *s)` |
| `sb_link_item` | function | `src/prefs.c:400` | `static void sb_link_item(sbuf *b, const char *url, const char *label)` |
| `sb_put` | function | `src/prefs.c:369` | `static void sb_put(sbuf *b, const char *s, size_t n)` |
| `sb_str` | function | `src/prefs.c:384` | `static void sb_str(sbuf *b, const char *s)` |
| `sbuf` | struct | `src/prefs.c:367` | `` |
| `sugg_push` | function | `src/prefs.c:335` | `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,
                      cons...` |
| `title_clean` | function | `src/prefs.c:39` | `static char *title_clean(const char *src)` |
| `url_prefix_match` | function | `src/prefs.c:323` | `static int url_prefix_match(const char *url, const char *q)` |
| `url_valid` | function | `src/prefs.c:26` | `static int url_valid(const char *url)` |
| `PROFILE_KEYFILE_LEN` | macro | `src/profile.c:27` | `#define PROFILE_KEYFILE_LEN` |
| `_POSIX_C_SOURCE` | macro | `src/profile.c:11` | `#define _POSIX_C_SOURCE` |
| `join_path` | function | `src/profile.c:29` | `static int join_path(const profile_ctx *ctx, const char *name,
                     char *out, si...` |
| `keyfile_create` | function | `src/profile.c:36` | `static profile_status keyfile_create(const char *dir, const char *path,
                         ...` |
| `map_ds` | function | `src/profile.c:98` | `static profile_status map_ds(ds_status ds)` |
| `profile_close` | function | `src/profile.c:149` | `void profile_close(profile_ctx *ctx)` |
| `profile_load` | function | `src/profile.c:112` | `profile_status profile_load(const profile_ctx *ctx, prefs_state *out)` |
| `profile_open` | function | `src/profile.c:59` | `profile_status profile_open(profile_ctx *ctx, const char *dir)` |
| `profile_save` | function | `src/profile.c:133` | `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p)` |
| `place` | function | `src/render_doc.c:220` | `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never resolved,` |
| `rd_at` | function | `src/render_doc.c:704` | `const rd_block *rd_at(const rd_doc *d, size_t i)` |
| `rd_block_tag` | function | `src/render_doc.c:741` | `const char *rd_block_tag(const rd_block *b)` |
| `rd_box_at` | function | `src/render_doc.c:713` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)` |
| `rd_box_count` | function | `src/render_doc.c:709` | `size_t rd_box_count(const rd_doc *d)` |
| `rd_build` | function | `src/render_doc.c:252` | `rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_u...` |
| `rd_cont_at` | function | `src/render_doc.c:722` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)` |
| `rd_cont_count` | function | `src/render_doc.c:718` | `size_t rd_cont_count(const rd_doc *d)` |
| `rd_count` | function | `src/render_doc.c:700` | `size_t rd_count(const rd_doc *d)` |
| `rd_free` | function | `src/render_doc.c:684` | `void rd_free(rd_doc *d)` |
| `rd_image_fail_label` | function | `src/render_doc.c:807` | `const char *rd_image_fail_label(img_fail_reason reason)` |
| `rd_image_label` | function | `src/render_doc.c:796` | `const char *rd_image_label(rdp_img_decision d)` |
| `rd_input_invisible` | function | `src/render_doc.c:792` | `int rd_input_invisible(int input_type)` |
| `rd_input_label` | function | `src/render_doc.c:772` | `const char *rd_input_label(int input_type)` |
| `rd_kind_name` | function | `src/render_doc.c:727` | `const char *rd_kind_name(rd_kind k)` |
| `rd_push` | function | `src/render_doc.c:60` | `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,
                 ...` |
| `rd_push_input` | function | `src/render_doc.c:195` | `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` |
| `resolve_image_decision` | function | `src/render_doc.c:230` | `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,
        ...` |
| `unset` | function | `src/render_doc.c:619` | `* background paints as if unset (no border/box-shadow-style
                 * "broken image" pla...` |
| `utf8_sanitized_dup` | function | `src/render_doc.c:28` | `static char *utf8_sanitized_dup(const char *s)` |
| `rdp_caps_safe` | function | `src/render_policy.c:17` | `rdp_caps rdp_caps_safe(void)` |
| `rdp_image_decision` | function | `src/render_policy.c:28` | `rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char...` |
| `rdp_images_warning` | function | `src/render_policy.c:74` | `const char *rdp_images_warning(void)` |
| `rdp_img_reason` | function | `src/render_policy.c:63` | `const char *rdp_img_reason(rdp_img_decision d)` |
| `rdp_is_tracking_pixel` | function | `src/render_policy.c:22` | `int rdp_is_tracking_pixel(int w, int h)` |
| `_POSIX_C_SOURCE` | macro | `src/renderer.c:7` | `#define _POSIX_C_SOURCE` |
| `child_render` | function | `src/renderer.c:25` | `static void child_render(int wfd, const char *html, size_t len)` |
| `rd_render_html` | function | `src/renderer.c:70` | `rd_status rd_render_html(const char *html, size_t len, rd_result *out)` |
| `rd_result_free` | function | `src/renderer.c:120` | `void rd_result_free(rd_result *out)` |
| `read_field` | function | `src/renderer.c:53` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `write_full` | function | `src/renderer.c:40` | `&& write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 \|\| write_full(wfd, title, tl) == 0) && write_full(wfd, &xl, sizeof` |
| `RP_MAX_HOST` | macro | `src/request_policy.c:17` | `#define RP_MAX_HOST` |
| `RP_MAX_LABELS` | macro | `src/request_policy.c:18` | `#define RP_MAX_LABELS` |
| `ci_starts_with` | function | `src/request_policy.c:26` | `static int ci_starts_with(const char *s, const char *prefix)` |
| `lower` | function | `src/request_policy.c:22` | `static char lower(char c)` |
| `psl_cmp` | function | `src/request_policy.c:36` | `static int psl_cmp(const void *key, const void *elem)` |
| `psl_in` | function | `src/request_policy.c:40` | `static int psl_in(const char *const *arr, size_t n, const char *key)` |
| `public_suffix_labels` | function | `src/request_policy.c:48` | `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)` |
| `rp_evaluate` | function | `src/request_policy.c:143` | `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)` |
| `rp_host_of` | function | `src/request_policy.c:76` | `int rp_host_of(const char *url, char *out, size_t out_size)` |
| `rp_same_site` | function | `src/request_policy.c:134` | `int rp_same_site(const char *top_level_url, const char *request_url)` |
| `rp_site_of` | function | `src/request_policy.c:102` | `int rp_site_of(const char *host, char *out, size_t out_size)` |
| `_POSIX_C_SOURCE` | macro | `src/secure_fetch.c:12` | `#define _POSIX_C_SOURCE` |
| `add_header` | function | `src/secure_fetch.c:722` | `static int add_header(struct curl_slist **h, const char *line)` |
| `body_sink` | struct | `src/secure_fetch.c:434` | `` |
| `ci_index` | function | `src/secure_fetch.c:56` | `static long ci_index(const char *haystack, const char *needle)` |
| `ci_starts_with` | function | `src/secure_fetch.c:44` | `static int ci_starts_with(const char *haystack, const char *prefix)` |
| `copy_bounded` | function | `src/secure_fetch.c:470` | `static void copy_bounded(char *dst, size_t dstsz, const char *src)` |
| `copy_checked` | function | `src/secure_fetch.c:325` | `static int copy_checked(char *dst, size_t dstsz, const char *src)` |
| `database` | function | `src/secure_fetch.c:485` | `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid handsha` |
| `fetch_ctx` | struct | `src/secure_fetch.c:457` | `` |
| `get_negotiated_group_name` | function | `src/secure_fetch.c:481` | `static const char *get_negotiated_group_name(SSL *ssl)` |
| `group` | function | `src/secure_fetch.c:499` | `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);` |
| `header_cb` | function | `src/secure_fetch.c:550` | `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` |
| `inspect_chain` | function | `src/secure_fetch.c:628` | `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` |
| `map_curl_error` | function | `src/secure_fetch.c:681` | `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)` |
| `module` | function | `src/secure_fetch.c:364` | `* pure url module (DRY);` |
| `name_is_pq_sig` | function | `src/secure_fetch.c:618` | `static int name_is_pq_sig(int pknid)` |
| `progress` | function | `src/secure_fetch.c:443` | `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);` |
| `redirect` | function | `src/secure_fetch.c:811` | `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...` |
| `sf_check_chain_policy` | function | `src/secure_fetch.c:284` | `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)` |
| `sf_check_group_is_pq` | function | `src/secure_fetch.c:275` | `sf_status sf_check_group_is_pq(const char *negotiated_group)` |
| `sf_check_tls_version` | function | `src/secure_fetch.c:270` | `sf_status sf_check_tls_version(const char *negotiated_version)` |
| `sf_ci_prefix` | function | `src/secure_fetch.c:371` | `static int sf_ci_prefix(const char *s, const char *p)` |
| `sf_config_default` | function | `src/secure_fetch.c:216` | `sf_config sf_config_default(void)` |
| `sf_cookie_header_for` | function | `src/secure_fetch.c:166` | `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)` |
| `sf_cookie_line_matches` | function | `src/secure_fetch.c:96` | `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...` |
| `sf_cookie_put` | function | `src/secure_fetch.c:195` | `void sf_cookie_put(const char *url, const char *namevalue)` |
| `sf_enforce_policy` | function | `src/secure_fetch.c:294` | `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...` |
| `sf_get` | function | `src/secure_fetch.c:1014` | `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)` |
| `sf_get_follow` | function | `src/secure_fetch.c:1032` | `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...` |
| `sf_global_init` | function | `src/secure_fetch.c:81` | `void sf_global_init(void)` |
| `sf_impersonate_kex_groups` | function | `src/secure_fetch.c:245` | `const char *sf_impersonate_kex_groups(void)` |
| `sf_impersonate_tls13_ciphers` | function | `src/secure_fetch.c:246` | `const char *sf_impersonate_tls13_ciphers(void)` |
| `sf_is_redirect_code` | function | `src/secure_fetch.c:334` | `int sf_is_redirect_code(long http_code)` |
| `sf_parse_location_header` | function | `src/secure_fetch.c:341` | `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)` |
| `sf_perform` | function | `src/secure_fetch.c:879` | `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...` |
| `sf_post` | function | `src/secure_fetch.c:1018` | `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...` |
| `sf_resolve_redirect` | function | `src/secure_fetch.c:359` | `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...` |
| `sf_response_free` | function | `src/secure_fetch.c:411` | `void sf_response_free(sf_response *resp)` |
| `sf_setup_handle` | function | `src/secure_fetch.c:736` | `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,
           ...` |
| `sf_share_lock` | function | `src/secure_fetch.c:68` | `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...` |
| `sf_share_unlock` | function | `src/secure_fetch.c:74` | `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)` |
| `sf_url_host_path` | function | `src/secure_fetch.c:151` | `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...` |
| `sf_url_is_http` | function | `src/secure_fetch.c:258` | `static int sf_url_is_http(const char *url)` |
| `sf_user_agent_or_default` | function | `src/secure_fetch.c:241` | `const char *sf_user_agent_or_default(const char *ua)` |
| `sf_validate_url` | function | `src/secure_fetch.c:250` | `sf_status sf_validate_url(const char *url)` |
| `sf_ws` | struct | `src/secure_fetch.c:1098` | `` |
| `sf_ws_close` | function | `src/secure_fetch.c:1233` | `void sf_ws_close(sf_ws *ws)` |
| `sf_ws_fd` | function | `src/secure_fetch.c:1226` | `int sf_ws_fd(const sf_ws *ws)` |
| `sf_ws_open` | function | `src/secure_fetch.c:1126` | `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)` |
| `sf_ws_recv` | function | `src/secure_fetch.c:1204` | `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)` |
| `sf_ws_send` | function | `src/secure_fetch.c:1181` | `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)` |
| `sf_ws_url_check` | function | `src/secure_fetch.c:1105` | `sf_status sf_ws_url_check(const char *url)` |
| `sink` | type_alias | `src/secure_fetch.c:456` | `typedef struct fetch_ctx { body_sink sink;` |
| `this` | function | `src/secure_fetch.c:531` | `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and causes` |
| `tls_capture` | struct | `src/secure_fetch.c:447` | `` |
| `tls_capture_from_ssl` | function | `src/secure_fetch.c:524` | `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)` |
| `tls_capture_try` | function | `src/secure_fetch.c:514` | `static void tls_capture_try(tls_capture *cap)` |
| `write_cb` | function | `src/secure_fetch.c:586` | `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)` |
| `ws_free` | function | `src/secure_fetch.c:1117` | `static void ws_free(sf_ws *ws)` |
| `ws_ssl_ctx_cb` | function | `src/secure_fetch.c:1091` | `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)` |
| `ws_ssl_info_cb` | function | `src/secure_fetch.c:1084` | `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)` |
| `SV_MAX_ATTRS` | macro | `src/svg_render.c:96` | `#define SV_MAX_ATTRS` |
| `point` | function | `src/svg_render.c:556` | `* current point (SVG 8.3.6). */ int had = (prev == 'C' \|\| prev == 'c' \|\| prev == 'S' \|\| prev == 's');` |
| `stroke` | type_alias | `src/svg_render.c:151` | `typedef struct sv_ctx { int fill, stroke;` |
| `sv_apply_prop` | function | `src/svg_render.c:260` | `static void sv_apply_prop(sv_ctx *ctx, const char *nm, size_t nl,
                          const...` |
| `sv_arc_to_cubics` | function | `src/svg_render.c:399` | `static int sv_arc_to_cubics(sv_image *im, sv_shape *sh,
                            double x0, do...` |
| `sv_attr` | struct | `src/svg_render.c:91` | `` |
| `sv_attr_get` | function | `src/svg_render.c:99` | `static const char *sv_attr_get(const sv_attr *at, size_t nat, const char *name, size_t *len)` |
| `sv_attr_num` | function | `src/svg_render.c:108` | `static double sv_attr_num(const sv_attr *at, size_t nat, const char *name, double dflt)` |
| `sv_collect_text` | function | `src/svg_render.c:725` | `static void sv_collect_text(const char *s, size_t n, size_t *i, char *dst, size_t cap)` |
| `sv_ctx` | struct | `src/svg_render.c:151` | `` |
| `sv_ctx_from_attrs` | function | `src/svg_render.c:307` | `static void sv_ctx_from_attrs(sv_ctx *ctx, const sv_attr *at, size_t nat)` |
| `sv_fit` | function | `src/svg_render.c:743` | `void sv_fit(const sv_image *img, double dw, double dh,
            double *scale, double *off_x, ...` |
| `sv_is_digit` | function | `src/svg_render.c:25` | `static int sv_is_digit(char c)` |
| `sv_is_dropped_element` | function | `src/svg_render.c:635` | `static int sv_is_dropped_element(const char *name, size_t n)` |
| `sv_is_space` | function | `src/svg_render.c:21` | `static int sv_is_space(char c)` |
| `sv_lower` | function | `src/svg_render.c:27` | `static char sv_lower(char c)` |
| `sv_mat_identity` | function | `src/svg_render.c:161` | `static void sv_mat_identity(double *m)` |
| `sv_mat_mul` | function | `src/svg_render.c:166` | `static void sv_mat_mul(const double *a, const double *b, double *out)` |
| `sv_new_seg` | function | `src/svg_render.c:363` | `static sv_seg *sv_new_seg(sv_image *im, sv_shape *sh)` |
| `sv_new_shape` | function | `src/svg_render.c:324` | `static sv_shape *sv_new_shape(sv_image *im, int kind, const sv_ctx *ctx)` |
| `sv_parse` | function | `src/svg_render.c:763` | `sv_status sv_parse(const char *markup, size_t len, sv_image *out)` |
| `sv_parse_ex` | function | `src/svg_render.c:767` | `sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill)` |
| `sv_parse_path` | function | `src/svg_render.c:477` | `static void sv_parse_path(sv_image *im, sv_shape *sh, const char *s, size_t n)` |
| `sv_parse_points` | function | `src/svg_render.c:343` | `static void sv_parse_points(sv_image *im, sv_shape *sh, const char *s, size_t n)` |
| `sv_parse_transform` | function | `src/svg_render.c:179` | `static void sv_parse_transform(const char *s, size_t n, double *m)` |
| `sv_scan_attrs` | function | `src/svg_render.c:647` | `static void sv_scan_attrs(const char *s, size_t n, size_t *i,
                          sv_attr *...` |
| `sv_seg_cubic` | function | `src/svg_render.c:385` | `static int sv_seg_cubic(sv_image *im, sv_shape *sh,
                        double x1, double y1,...` |
| `sv_seg_line` | function | `src/svg_render.c:378` | `static int sv_seg_line(sv_image *im, sv_shape *sh, double x, double y)` |
| `sv_seg_move` | function | `src/svg_render.c:371` | `static int sv_seg_move(sv_image *im, sv_shape *sh, double x, double y)` |
| `sv_sep` | function | `src/svg_render.c:82` | `static void sv_sep(const char *s, size_t n, size_t *i)` |
| `sv_skip_subtree` | function | `src/svg_render.c:693` | `static void sv_skip_subtree(const char *s, size_t n, size_t *i, const char *name, size_t nlen)` |
| `sv_span_eq` | function | `src/svg_render.c:32` | `static int sv_span_eq(const char *s, size_t n, const char *lit)` |
| `sv_style_next` | function | `src/svg_render.c:238` | `static int sv_style_next(const char *s, size_t n, size_t *i,
                         const char ...` |
| `EPIPE` | function | `src/tab.c:1690` | `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();` |
| `FB_MAX_FILE_BYTES` | function | `src/tab.c:698` | `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...` |
| `PV_MAX_CONTAINERS_WIRE` | macro | `src/tab.c:74` | `#define PV_MAX_CONTAINERS_WIRE` |
| `TAB_MAX_EXTERN_CSS` | macro | `src/tab.c:771` | `#define TAB_MAX_EXTERN_CSS` |
| `TAB_MAX_GEOM_WORDS` | macro | `src/tab.c:101` | `#define TAB_MAX_GEOM_WORDS` |
| `TAB_MAX_HIST_BYTES` | macro | `src/tab.c:95` | `#define TAB_MAX_HIST_BYTES` |
| `TAB_MAX_HIST_OPS` | macro | `src/tab.c:94` | `#define TAB_MAX_HIST_OPS` |
| `TAB_MAX_JS_JOBS` | macro | `src/tab.c:113` | `#define TAB_MAX_JS_JOBS` |
| `TAB_MAX_OPENS` | macro | `src/tab.c:97` | `#define TAB_MAX_OPENS` |
| `TAB_MAX_OPEN_BYTES` | macro | `src/tab.c:98` | `#define TAB_MAX_OPEN_BYTES` |
| `TAB_MAX_RUNS` | macro | `src/tab.c:70` | `#define TAB_MAX_RUNS` |
| `TAB_MAX_STORAGE` | macro | `src/tab.c:90` | `#define TAB_MAX_STORAGE` |
| `TAB_MAX_SUBREQ` | macro | `src/tab.c:111` | `#define TAB_MAX_SUBREQ` |
| `TAB_MAX_SUBRESOURCE` | macro | `src/tab.c:112` | `#define TAB_MAX_SUBRESOURCE` |
| `TAB_MAX_URL` | macro | `src/tab.c:77` | `#define TAB_MAX_URL` |
| `TAB_MAX_WS_MSG` | macro | `src/tab.c:86` | `#define TAB_MAX_WS_MSG` |
| `TAB_SCREEN_H` | macro | `src/tab.c:58` | `#define TAB_SCREEN_H` |
| `TAB_SCREEN_W` | macro | `src/tab.c:57` | `#define TAB_SCREEN_W` |
| `TAB_WIRE_A_N` | macro | `src/tab.c:63` | `#define TAB_WIRE_A_N` |
| `TAB_WIRE_BOX_F_N` | macro | `src/tab.c:65` | `#define TAB_WIRE_BOX_F_N` |
| `TAB_WIRE_B_N` | macro | `src/tab.c:64` | `#define TAB_WIRE_B_N` |
| `TAB_WIRE_GRID_N` | macro | `src/tab.c:66` | `#define TAB_WIRE_GRID_N` |
| `TAB_WIRE_HEAD_N` | macro | `src/tab.c:62` | `#define TAB_WIRE_HEAD_N` |
| `WHERE` | function | `src/tab.c:1177` | `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value != ` |
| `_GNU_SOURCE` | macro | `src/tab.c:14` | `#define _GNU_SOURCE` |
| `answered` | function | `src/tab.c:2591` | `* A refused frame is still consumed and answered (status 0), so the protocol never
 * desyncs. Re...` |
| `blocks` | function | `src/tab.c:330` | `*
 * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the
 * grid arr...` |
| `budget_remaining_ms` | function | `src/tab.c:728` | `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` |
| `buffer` | function | `src/tab.c:272` | `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of run_j` |
| `child_handle_click` | function | `src/tab.c:1443` | `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_decode_image` | function | `src/tab.c:1634` | `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` |
| `child_handle_decode_image_b64` | function | `src/tab.c:1656` | `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)` |
| `child_handle_eval` | function | `src/tab.c:1601` | `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` |
| `child_handle_event` | function | `src/tab.c:1457` | `static void child_handle_event(int wfd, child_state *cs)` |
| `child_handle_geom` | function | `src/tab.c:1543` | `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` |
| `child_handle_load` | function | `src/tab.c:943` | `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...` |
| `child_handle_mouse` | function | `src/tab.c:1505` | `static void child_handle_mouse(int wfd, child_state *cs)` |
| `child_handle_mutation` | function | `src/tab.c:1364` | `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...` |
| `child_handle_submit` | function | `src/tab.c:1567` | `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_tick` | function | `src/tab.c:1447` | `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)` |
| `child_next_timer_ms` | function | `src/tab.c:1349` | `static int32_t child_next_timer_ms(child_state *cs)` |
| `child_reset_page` | function | `src/tab.c:155` | `static void child_reset_page(child_state *cs)` |
| `child_state` | struct | `src/tab.c:124` | `` |
| `column` | function | `src/tab.c:2144` | `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation as te` |
| `content` | function | `src/tab.c:1210` | `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video> elements i` |
| `ctype_is_css` | function | `src/tab.c:751` | `static int ctype_is_css(const char *ctype)` |
| `ctype_is_javascript` | function | `src/tab.c:742` | `static int ctype_is_javascript(const char *ctype)` |
| `depth` | function | `src/tab.c:1711` | `* defense in depth (seccomp already excludes open/socket/exec);` |
| `exec_worker_child` | function | `src/tab.c:2481` | `static void exec_worker_child(int rfd, int wfd)` |
| `fallback` | function | `src/tab.c:1019` | `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it even ` |
| `gate_js_nav` | function | `src/tab.c:2818` | `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` |
| `gen_session_key` | function | `src/tab.c:1668` | `static uint64_t gen_session_key(void)` |
| `geom_parent` | function | `src/tab.c:1535` | `static dom_node_id geom_parent(void *ctx, dom_node_id n)` |
| `hist_ops_free` | function | `src/tab.c:2627` | `static void hist_ops_free(tab_hist_op *ops, size_t n)` |
| `host` | function | `src/tab.c:284` | `* granted net access for this host (allow.conf AND js.conf). Otherwise they stay * undefined (Same-Origin-by-constructio` |
| `ignore_sigpipe` | function | `src/tab.c:1942` | `static void ignore_sigpipe(void)` |
| `io_failure` | function | `src/tab.c:2473` | `static tab_status io_failure(tab *t)` |
| `is_activation_event` | function | `src/tab.c:2692` | `static int is_activation_event(const char *type)` |
| `layout` | function | `src/tab.c:2133` | `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property. */ pv` |
| `load` | function | `src/tab.c:1925` | `* subresource requests this load (set per page: host in allow.conf AND js.conf);` |
| `log_external_skip` | function | `src/tab.c:759` | `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...` |
| `once` | function | `src/tab.c:1255` | `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);` |
| `open_urls_free` | function | `src/tab.c:2701` | `static void open_urls_free(char **u, size_t n)` |
| `parse_worker_fd` | function | `src/tab.c:1886` | `static int parse_worker_fd(const char *s, int *out)` |
| `policy` | function | `src/tab.c:175` | `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a
 * compromi...` |
| `read_console` | function | `src/tab.c:2426` | `static int read_console(int fd, fb_buffer *out)` |
| `read_field` | function | `src/tab.c:1968` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `read_opens` | function | `src/tab.c:2711` | `static tab_status read_opens(tab *t, const char *page_url, int gesture,
                         ...` |
| `read_view` | function | `src/tab.c:1984` | `static int read_view(int fd, pv_view **out)` |
| `read_ws` | function | `src/tab.c:2749` | `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` |
| `run` | function | `src/tab.c:777` | `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...` |
| `run_js` | function | `src/tab.c:229` | `* regardless of run_js (a no-JS load simply never records a request). */
static int child_load(ch...` |
| `send_request` | function | `src/tab.c:2463` | `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` |
| `swap` | function | `src/tab.c:1264` | `* display:none hiding an element via class swap (CSS, not
     * DOM removal). */
    if (ok && v...` |
| `tab` | struct | `src/tab.c:1918` | `` |
| `tab_alive` | function | `src/tab.c:3349` | `int tab_alive(const tab *t)` |
| `tab_child_pid` | function | `src/tab.c:3355` | `pid_t tab_child_pid(const tab *t)` |
| `tab_click` | function | `src/tab.c:3022` | `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)` |
| `tab_close` | function | `src/tab.c:3359` | `void tab_close(tab *t)` |
| `tab_decode_image` | function | `src/tab.c:3325` | `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)` |
| `tab_decode_image_data_url` | function | `src/tab.c:3331` | `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)` |
| `tab_decode_image_op` | function | `src/tab.c:3283` | `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...` |
| `tab_eval` | function | `src/tab.c:3243` | `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)` |
| `tab_eval_result_free` | function | `src/tab.c:3404` | `void tab_eval_result_free(tab_eval_result *r)` |
| `tab_image_free` | function | `src/tab.c:3413` | `void tab_image_free(tab_image *img)` |
| `tab_load` | function | `src/tab.c:2828` | `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)` |
| `tab_load_ex` | function | `src/tab.c:2832` | `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)` |
| `tab_load_full` | function | `src/tab.c:2836` | `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...` |
| `tab_mod_fetch` | function | `src/tab.c:857` | `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` |
| `tab_mod_resolve` | function | `src/tab.c:835` | `static int tab_mod_resolve(void *host, const char *base, const char *spec,
                      ...` |
| `tab_page_free` | function | `src/tab.c:3374` | `void tab_page_free(tab_page *p)` |
| `tab_parse_worker_args` | function | `src/tab.c:1898` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)` |
| `tab_popstate` | function | `src/tab.c:3449` | `tab_status tab_popstate(tab *t, int index, tab_page *out)` |
| `tab_read_view` | function | `src/tab.c:3143` | `tab_status tab_read_view(tab *t, tab_page *out)` |
| `tab_read_view_ex` | function | `src/tab.c:3147` | `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)` |
| `tab_refresh_alive` | function | `src/tab.c:1949` | `static void tab_refresh_alive(tab *t)` |
| `tab_set_cookies` | function | `src/tab.c:2573` | `void tab_set_cookies(tab *t, const char *cookies)` |
| `tab_set_css_allowed` | function | `src/tab.c:2563` | `void tab_set_css_allowed(tab *t, int allowed)` |
| `tab_set_fetcher` | function | `src/tab.c:2552` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)` |
| `tab_set_geometry` | function | `src/tab.c:3423` | `tab_status tab_set_geometry(tab *t, const jg_table *g)` |
| `tab_set_net_allowed` | function | `src/tab.c:2558` | `void tab_set_net_allowed(tab *t, int allowed)` |
| `tab_set_storage` | function | `src/tab.c:3474` | `void tab_set_storage(tab *t, const char *blob, size_t len)` |
| `tab_set_viewport_w` | function | `src/tab.c:2568` | `void tab_set_viewport_w(tab *t, int px)` |
| `tab_submit` | function | `src/tab.c:3038` | `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` |
| `tab_subreq_permitted` | function | `src/tab.c:2579` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)` |
| `tab_tick` | function | `src/tab.c:3029` | `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)` |
| `tab_url_resolve` | function | `src/tab.c:826` | `static int tab_url_resolve(void *ctx, const char *base, const char *ref,
                        ...` |
| `tab_worker_dispatch` | function | `src/tab.c:1908` | `void tab_worker_dispatch(int argc, char **argv)` |
| `tab_worker_run` | function | `src/tab.c:1688` | `static void tab_worker_run(int rfd, int wfd)` |
| `tab_ws_event` | function | `src/tab.c:3455` | `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,
       ...` |
| `tzset` | function | `src/tab.c:1706` | `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);` |
| `window` | function | `src/tab.c:898` | `* net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs)` |
| `write_field` | function | `src/tab.c:296` | `static int write_field(int fd, const char *s)` |
| `write_full` | function | `src/tab.c:1284` | `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 \|\| write_full(wfd, text, xl) == 0) && write_view(wfd, write_which)` |
| `write_history` | function | `src/tab.c:879` | `static int write_history(int wfd, child_state *cs)` |
| `write_opens` | function | `src/tab.c:1337` | `static int write_opens(int wfd, child_state *cs)` |
| `write_storage` | function | `src/tab.c:1323` | `static int write_storage(int wfd, child_state *cs)` |
| `write_ws` | function | `src/tab.c:1306` | `static int write_ws(int wfd, child_state *cs)` |
| `ws_ops_free` | function | `src/tab.c:2740` | `static void ws_ops_free(tab_ws_op *ops, size_t n)` |
| `TSH_CACHE_SLOTS` | macro | `src/text_shape.c:32` | `#define TSH_CACHE_SLOTS` |
| `TSH_MAX_FONT_BYTES` | macro | `src/text_shape.c:28` | `#define TSH_MAX_FONT_BYTES` |
| `_POSIX_C_SOURCE` | macro | `src/text_shape.c:12` | `#define _POSIX_C_SOURCE` |
| `backend_init` | function | `src/text_shape.c:64` | `static int backend_init(void)` |
| `generic_name` | function | `src/text_shape.c:54` | `static const char *generic_name(int family)` |
| `get_entry` | function | `src/text_shape.c:152` | `static tsh_entry *get_entry(int family, int bold, int italic)` |
| `load_entry` | function | `src/text_shape.c:97` | `static int load_entry(tsh_entry *e, int family, int bold, int italic)` |
| `loaded` | type_alias | `src/text_shape.c:33` | `typedef struct tsh_entry { int loaded;` |
| `read_font_file` | function | `src/text_shape.c:81` | `static unsigned char *read_font_file(const char *path, long *out_n)` |
| `tsh_draw` | function | `src/text_shape.c:221` | `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, doub...` |
| `tsh_entry` | struct | `src/text_shape.c:34` | `` |
| `tsh_measure` | function | `src/text_shape.c:214` | `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)` |
| `tsh_ready` | function | `src/text_shape.c:164` | `int tsh_ready(void)` |
| `tsh_shape` | function | `src/text_shape.c:169` | `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                ...` |
| `tsh_shutdown` | function | `src/text_shape.c:243` | `void tsh_shutdown(void)` |
| `tf_backspace` | function | `src/textfield.c:47` | `void tf_backspace(tf_field *f)` |
| `tf_clear` | function | `src/textfield.c:20` | `void tf_clear(tf_field *f)` |
| `tf_cursor` | function | `src/textfield.c:91` | `size_t tf_cursor(const tf_field *f)` |
| `tf_delete` | function | `src/textfield.c:55` | `void tf_delete(tf_field *f)` |
| `tf_end` | function | `src/textfield.c:78` | `void tf_end(tf_field *f)` |
| `tf_home` | function | `src/textfield.c:73` | `void tf_home(tf_field *f)` |
| `tf_insert` | function | `src/textfield.c:35` | `tf_status tf_insert(tf_field *f, char c)` |
| `tf_len` | function | `src/textfield.c:87` | `size_t tf_len(const tf_field *f)` |
| `tf_move` | function | `src/textfield.c:62` | `void tf_move(tf_field *f, long delta)` |
| `tf_set` | function | `src/textfield.c:24` | `tf_status tf_set(tf_field *f, const char *s)` |
| `tf_text` | function | `src/textfield.c:83` | `const char *tf_text(const tf_field *f)` |
| `whole` | function | `src/textfield.c:6` | `* the buffer is rejected whole (fail closed), never applied partially.
 */

#include "textfield.h...` |
| `bounded_len` | function | `src/tls_impersonate.c:25` | `static size_t bounded_len(const char *s, size_t max)` |
| `get_bytes` | function | `src/tls_impersonate.c:89` | `static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len)` |
| `get_str` | function | `src/tls_impersonate.c:103` | `static char *get_str(ti_rd *r, size_t cap)` |
| `get_u32` | function | `src/tls_impersonate.c:70` | `static uint32_t get_u32(ti_rd *r)` |
| `get_u64` | function | `src/tls_impersonate.c:80` | `static uint64_t get_u64(ti_rd *r)` |
| `get_u8` | function | `src/tls_impersonate.c:65` | `static uint8_t get_u8(ti_rd *r)` |
| `put_blob` | function | `src/tls_impersonate.c:53` | `static void put_blob(ti_wr *w, const uint8_t *b, size_t n)` |
| `put_u32` | function | `src/tls_impersonate.c:40` | `static void put_u32(ti_wr *w, uint32_t v)` |
| `put_u64` | function | `src/tls_impersonate.c:48` | `static void put_u64(ti_wr *w, uint64_t v)` |
| `put_u8` | function | `src/tls_impersonate.c:35` | `static void put_u8(ti_wr *w, uint8_t v)` |
| `ti_decode_req` | function | `src/tls_impersonate.c:140` | `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out)` |
| `ti_decode_resp` | function | `src/tls_impersonate.c:196` | `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out)` |
| `ti_encode_req` | function | `src/tls_impersonate.c:122` | `size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap)` |
| `ti_encode_resp` | function | `src/tls_impersonate.c:177` | `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap)` |
| `ti_rd` | struct | `src/tls_impersonate.c:63` | `` |
| `ti_req_free` | function | `src/tls_impersonate.c:166` | `void ti_req_free(ti_req *r)` |
| `ti_resp_free` | function | `src/tls_impersonate.c:230` | `void ti_resp_free(ti_resp *r)` |
| `ti_should_impersonate` | function | `src/tls_impersonate.c:18` | `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,
                          i...` |
| `ti_wr` | struct | `src/tls_impersonate.c:33` | `` |
| `valid_profile` | function | `src/tls_impersonate.c:116` | `static int valid_profile(int p)` |
| `layout_push` | function | `src/ui_layout.c:13` | `static int layout_push(ui_layout *lay, size_t offset, size_t len)` |
| `ui_clamp_scroll` | function | `src/ui_layout.c:99` | `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines)` |
| `ui_layout_free` | function | `src/ui_layout.c:91` | `void ui_layout_free(ui_layout *lay)` |
| `ui_wrap_text` | function | `src/ui_layout.c:27` | `ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out)` |
| `_POSIX_C_SOURCE` | macro | `src/url.c:9` | `#define _POSIX_C_SOURCE` |
| `append_query_encoded` | function | `src/url.c:229` | `static int append_query_encoded(char *out, size_t outsz, const char *src)` |
| `assumed` | function | `src/url.c:254` | `* assumed (the caller already routed whitespace to search). */
static int looks_like_host(const c...` |
| `build_search` | function | `src/url.c:303` | `static url_status build_search(const char *query, char *out, size_t outsz)` |
| `cat_checked` | function | `src/url.c:40` | `static int cat_checked(char *out, size_t outsz, const char *src)` |
| `ci_prefix` | function | `src/url.c:20` | `static int ci_prefix(const char *haystack, const char *prefix)` |
| `copy_bounded` | function | `src/url.c:645` | `static url_status copy_bounded(char *out, size_t outsz, const char *a, size_t alen,
             ...` |
| `copy_checked` | function | `src/url.c:32` | `static int copy_checked(char *out, size_t outsz, const char *src)` |
| `dir_len` | function | `src/url.c:159` | `static size_t dir_len(const char *base)` |
| `host_equals` | function | `src/url.c:378` | `static int host_equals(const url_parts *p, const char *want)` |
| `is_space` | function | `src/url.c:218` | `static int is_space(int c)` |
| `is_unreserved` | function | `src/url.c:222` | `static int is_unreserved(int c)` |
| `ncat_checked` | function | `src/url.c:49` | `static int ncat_checked(char *out, size_t outsz, const char *src, size_t n)` |
| `out_pop_segment` | function | `src/url.c:102` | `static void out_pop_segment(char *out, size_t *olen)` |
| `query_find_q` | function | `src/url.c:393` | `static const char *query_find_q(const char *search, size_t len, size_t *vlen)` |
| `url_authority_len` | function | `src/url.c:91` | `size_t url_authority_len(const char *url)` |
| `url_extract_userinfo` | function | `src/url.c:431` | `url_status url_extract_userinfo(const char *url, char *out, size_t outsz,
                       ...` |
| `url_file_path` | function | `src/url.c:531` | `const char *url_file_path(const char *s)` |
| `url_has_scheme` | function | `src/url.c:59` | `int url_has_scheme(const char *s)` |
| `url_history_target` | function | `src/url.c:654` | `url_status url_history_target(const char *base, const char *ref, char *out, size_t outsz)` |
| `url_is_file` | function | `src/url.c:525` | `int url_is_file(const char *s)` |
| `url_is_https` | function | `src/url.c:73` | `int url_is_https(const char *s)` |
| `url_omnibox` | function | `src/url.c:309` | `url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz)` |
| `url_remove_dot_segments` | function | `src/url.c:109` | `url_status url_remove_dot_segments(const char *path, char *out, size_t outsz)` |
| `url_resolve_file` | function | `src/url.c:535` | `url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz)` |
| `url_resolve_https` | function | `src/url.c:170` | `url_status url_resolve_https(const char *base, const char *ref,
                             char...` |
| `url_search_rewrite` | function | `src/url.c:411` | `url_status url_search_rewrite(const char *url, char *out, size_t outsz)` |
| `url_split` | function | `src/url.c:584` | `url_status url_split(const char *url, url_parts *out)` |
| `url_validate_https` | function | `src/url.c:80` | `url_status url_validate_https(const char *url)` |
| `check` | function | `src/web_storage.c:65` | `static int check(const char *blob, size_t len, size_t *bytes_out)` |
| `find` | function | `src/web_storage.c:118` | `static wst_origin *find(const wst_db *db, const char *origin)` |
| `get_u32` | function | `src/web_storage.c:25` | `static uint32_t get_u32(const unsigned char *p)` |
| `key_cmp` | function | `src/web_storage.c:56` | `static int key_cmp(const void *a, const void *b)` |
| `key_ref` | struct | `src/web_storage.c:54` | `` |
| `put_u32` | function | `src/web_storage.c:201` | `static void put_u32(char *b, uint32_t v)` |
| `utf8_ok` | function | `src/web_storage.c:32` | `static int utf8_ok(const unsigned char *s, size_t n)` |
| `wst_db` | struct | `src/web_storage.c:20` | `` |
| `wst_decode_check` | function | `src/web_storage.c:101` | `int wst_decode_check(const char *blob, size_t len)` |
| `wst_encode` | function | `src/web_storage.c:125` | `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len)` |
| `wst_foreach` | function | `src/web_storage.c:181` | `int wst_foreach(const char *blob, size_t len,
                void (*fn)(void *ctx, const char *k...` |
| `wst_free` | function | `src/web_storage.c:109` | `void wst_free(wst_db *db)` |
| `wst_new` | function | `src/web_storage.c:105` | `wst_db *wst_new(void)` |
| `wst_origin` | struct | `src/web_storage.c:12` | `` |
| `wst_origin_bytes` | function | `src/web_storage.c:175` | `size_t wst_origin_bytes(const wst_db *db, const char *origin)` |
| `wst_pack` | function | `src/web_storage.c:206` | `int wst_pack(const char *const *keys, const size_t *klens,
             const char *const *vals, ...` |
| `wst_replace` | function | `src/web_storage.c:140` | `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len)` |
| `wc_derive` | function | `src/webcaps.c:15` | `wc_caps wc_derive(wc_input in)` |
| `wc_from_flags` | function | `src/webcaps.c:35` | `wc_caps wc_from_flags(bool js, bool css, bool images)` |
| `wc_render_caps` | function | `src/webcaps.c:46` | `rdp_caps wc_render_caps(wc_caps c)` |
| `wc_safe` | function | `src/webcaps.c:10` | `wc_caps wc_safe(void)` |
| `WH_READS_PER_PUMP` | macro | `src/ws_hub.c:21` | `#define WH_READS_PER_PUMP` |
| `WH_RECV_CHUNK` | macro | `src/ws_hub.c:22` | `#define WH_RECV_CHUNK` |
| `_POSIX_C_SOURCE` | macro | `src/ws_hub.c:6` | `#define _POSIX_C_SOURCE` |
| `conn_clear` | function | `src/ws_hub.c:98` | `static void conn_clear(wh_conn *c)` |
| `dup_str` | function | `src/ws_hub.c:54` | `static char *dup_str(const char *s)` |
| `fail_conn` | function | `src/ws_hub.c:258` | `static void fail_conn(wh_conn *c, int id, wh_emit_fn emit, void *ctx)` |
| `find_id` | function | `src/ws_hub.c:104` | `static wh_conn *find_id(wh_hub *h, int id)` |
| `find_token` | function | `src/ws_hub.c:110` | `static wh_conn *find_token(wh_hub *h, uint64_t token)` |
| `job_free` | function | `src/ws_hub.c:63` | `static void job_free(wh_job *j)` |
| `job_str` | function | `src/ws_hub.c:71` | `static int job_str(wh_job *j, size_t slot, const char **field)` |
| `open_thread` | function | `src/ws_hub.c:79` | `static void *open_thread(void *arg)` |
| `used` | type_alias | `src/ws_hub.c:23` | `typedef struct wh_conn { int used;` |
| `wfd` | type_alias | `src/ws_hub.c:43` | `typedef struct wh_job { int wfd;` |
| `wh_close` | function | `src/ws_hub.c:228` | `void wh_close(wh_hub *h, int id)` |
| `wh_close_all` | function | `src/ws_hub.c:234` | `void wh_close_all(wh_hub *h)` |
| `wh_conn` | struct | `src/ws_hub.c:24` | `` |
| `wh_count` | function | `src/ws_hub.c:314` | `size_t wh_count(const wh_hub *h)` |
| `wh_free` | function | `src/ws_hub.c:129` | `void wh_free(wh_hub *h)` |
| `wh_hub` | struct | `src/ws_hub.c:35` | `` |
| `wh_job` | struct | `src/ws_hub.c:43` | `` |
| `wh_new` | function | `src/ws_hub.c:116` | `wh_hub *wh_new(void)` |
| `wh_notify_fd` | function | `src/ws_hub.c:144` | `int wh_notify_fd(const wh_hub *h)` |
| `wh_on_notify` | function | `src/ws_hub.c:192` | `void wh_on_notify(wh_hub *h, wh_emit_fn emit, void *ctx)` |
| `wh_on_readable` | function | `src/ws_hub.c:266` | `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx)` |
| `wh_open_async` | function | `src/ws_hub.c:148` | `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg)` |
| `wh_poll_fds` | function | `src/ws_hub.c:240` | `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap)` |
| `wh_send` | function | `src/ws_hub.c:221` | `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary)` |
| `ZM_LADDER_N` | macro | `src/zoom.c:12` | `#define ZM_LADDER_N` |
| `zm_apply` | function | `src/zoom.c:44` | `double zm_apply(double base_px, int pct)` |
| `zm_clamp` | function | `src/zoom.c:14` | `int zm_clamp(int pct)` |
| `zm_reset` | function | `src/zoom.c:36` | `int zm_reset(void)` |
| `zm_scale` | function | `src/zoom.c:40` | `double zm_scale(int pct)` |
| `zm_zoom_in` | function | `src/zoom.c:20` | `int zm_zoom_in(int pct)` |
| `zm_zoom_out` | function | `src/zoom.c:28` | `int zm_zoom_out(int pct)` |
| `CHECK` | macro | `tests/itest_secure_fetch.c:16` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/itest_secure_fetch.c:26` | `int main(void)` |
| `main` | function | `tests/test_anti_fp.c:197` | `int main(void)` |
| `test_boolean_props` | function | `tests/test_anti_fp.c:74` | `static void test_boolean_props(void **state)` |
| `test_bucket_screen` | function | `tests/test_anti_fp.c:83` | `static void test_bucket_screen(void **state)` |
| `test_coarsen_time` | function | `tests/test_anti_fp.c:18` | `static void test_coarsen_time(void **state)` |
| `test_identity_is_fixed` | function | `tests/test_anti_fp.c:34` | `static void test_identity_is_fixed(void **state)` |
| `test_legacy_identity_fixed` | function | `tests/test_anti_fp.c:61` | `static void test_legacy_identity_fixed(void **state)` |
| `test_origin_key_deterministic` | function | `tests/test_anti_fp.c:146` | `static void test_origin_key_deterministic(void **state)` |
| `test_origin_key_empty_namespace` | function | `tests/test_anti_fp.c:171` | `static void test_origin_key_empty_namespace(void **state)` |
| `test_origin_key_per_session` | function | `tests/test_anti_fp.c:165` | `static void test_origin_key_per_session(void **state)` |
| `test_origin_key_per_site` | function | `tests/test_anti_fp.c:153` | `static void test_origin_key_per_site(void **state)` |
| `test_origin_key_unlinks_readback` | function | `tests/test_anti_fp.c:183` | `static void test_origin_key_unlinks_readback(void **state)` |
| `test_perturb_bounded_lsb` | function | `tests/test_anti_fp.c:111` | `static void test_perturb_bounded_lsb(void **state)` |
| `test_perturb_deterministic` | function | `tests/test_anti_fp.c:101` | `static void test_perturb_deterministic(void **state)` |
| `test_perturb_key_sensitive` | function | `tests/test_anti_fp.c:126` | `static void test_perturb_key_sensitive(void **state)` |
| `test_perturb_safe_edges` | function | `tests/test_anti_fp.c:136` | `static void test_perturb_safe_edges(void **state)` |
| `dbl_eq` | function | `tests/test_block_flow.c:21` | `static int dbl_eq(double a, double b)` |
| `main` | function | `tests/test_block_flow.c:105` | `int main(void)` |
| `test_collapse_n_edges` | function | `tests/test_block_flow.c:84` | `static void test_collapse_n_edges(void **state)` |
| `test_collapse_n_matches_binary` | function | `tests/test_block_flow.c:70` | `static void test_collapse_n_matches_binary(void **state)` |
| `test_margins_adjoin` | function | `tests/test_block_flow.c:95` | `static void test_margins_adjoin(void **state)` |
| `test_non_finite_is_absent` | function | `tests/test_block_flow.c:59` | `static void test_non_finite_is_absent(void **state)` |
| `test_two_negative_take_the_most_negative` | function | `tests/test_block_flow.c:50` | `static void test_two_negative_take_the_most_negative(void **state)` |
| `test_two_positive_collapse_to_max` | function | `tests/test_block_flow.c:29` | `static void test_two_positive_collapse_to_max(void **state)` |
| `assert_edges` | function | `tests/test_box_style.c:27` | `static void assert_edges(bx_edges e, double t, double r, double b, double l)` |
| `dbl_eq` | function | `tests/test_box_style.c:22` | `static int dbl_eq(double a, double b)` |
| `main` | function | `tests/test_box_style.c:608` | `int main(void)` |
| `percentage` | function | `tests/test_box_style.c:542` | `* percentage (a plain `width:50%` leaves the px half UNSET, a plain `width:300px`
 * leaves the p...` |
| `test_block_ua_box_heading_level_wins` | function | `tests/test_box_style.c:205` | `static void test_block_ua_box_heading_level_wins(void **state)` |
| `test_block_ua_box_is_content_independent` | function | `tests/test_box_style.c:194` | `static void test_block_ua_box_is_content_independent(void **state)` |
| `test_block_ua_box_is_total` | function | `tests/test_box_style.c:227` | `static void test_block_ua_box_is_total(void **state)` |
| `test_block_ua_box_list_item_wins_over_ancestor` | function | `tests/test_box_style.c:218` | `static void test_block_ua_box_list_item_wins_over_ancestor(void **state)` |
| `test_blockquote` | function | `tests/test_box_style.c:76` | `static void test_blockquote(void **state)` |
| `test_body_has_no_margin` | function | `tests/test_box_style.c:34` | `static void test_body_has_no_margin(void **state)` |
| `test_border_box_height` | function | `tests/test_box_style.c:474` | `static void test_border_box_height(void **state)` |
| `test_case_insensitive` | function | `tests/test_box_style.c:110` | `static void test_case_insensitive(void **state)` |
| `test_content_clipped` | function | `tests/test_box_style.c:492` | `static void test_content_clipped(void **state)` |
| `test_display_name` | function | `tests/test_box_style.c:374` | `static void test_display_name(void **state)` |
| `test_display_none_for_non_rendered` | function | `tests/test_box_style.c:101` | `static void test_display_none_for_non_rendered(void **state)` |
| `test_div_is_block` | function | `tests/test_box_style.c:133` | `static void test_div_is_block(void **state)` |
| `test_heading_ladder` | function | `tests/test_box_style.c:49` | `static void test_heading_ladder(void **state)` |
| `test_hr` | function | `tests/test_box_style.c:83` | `static void test_hr(void **state)` |
| `test_inline_and_inline_block` | function | `tests/test_box_style.c:90` | `static void test_inline_and_inline_block(void **state)` |
| `test_lists` | function | `tests/test_box_style.c:65` | `static void test_lists(void **state)` |
| `test_paragraph` | function | `tests/test_box_style.c:42` | `static void test_paragraph(void **state)` |
| `test_parse_display_case_and_trim` | function | `tests/test_box_style.c:347` | `static void test_parse_display_case_and_trim(void **state)` |
| `test_parse_display_errors` | function | `tests/test_box_style.c:356` | `static void test_parse_display_errors(void **state)` |
| `test_parse_display_inline_aliases` | function | `tests/test_box_style.c:338` | `static void test_parse_display_inline_aliases(void **state)` |
| `test_parse_display_keywords` | function | `tests/test_box_style.c:319` | `static void test_parse_display_keywords(void **state)` |
| `test_place_centering` | function | `tests/test_box_style.c:407` | `static void test_place_centering(void **state)` |
| `test_place_failclosed_bounds` | function | `tests/test_box_style.c:431` | `static void test_place_failclosed_bounds(void **state)` |
| `test_place_insets` | function | `tests/test_box_style.c:419` | `static void test_place_insets(void **state)` |
| `test_place_max_width_caps` | function | `tests/test_box_style.c:396` | `static void test_place_max_width_caps(void **state)` |
| `test_place_no_box_is_identity` | function | `tests/test_box_style.c:389` | `static void test_place_no_box_is_identity(void **state)` |
| `test_table_role_from_tag` | function | `tests/test_box_style.c:242` | `static void test_table_role_from_tag(void **state)` |
| `test_table_role_is_total` | function | `tests/test_box_style.c:272` | `static void test_table_role_is_total(void **state)` |
| `test_ua_case_insensitive_and_trimmed` | function | `tests/test_box_style.c:282` | `static void test_ua_case_insensitive_and_trimmed(void **state)` |
| `test_ua_code_space_is_total` | function | `tests/test_box_style.c:308` | `static void test_ua_code_space_is_total(void **state)` |
| `test_ua_fails_closed` | function | `tests/test_box_style.c:290` | `static void test_ua_fails_closed(void **state)` |
| `test_ua_list_item_is_distinct_but_unspaced` | function | `tests/test_box_style.c:181` | `static void test_ua_list_item_is_distinct_but_unspaced(void **state)` |
| `test_ua_spaced_tags_round_trip` | function | `tests/test_box_style.c:161` | `static void test_ua_spaced_tags_round_trip(void **state)` |
| `test_ua_structural_wrappers_have_no_margin` | function | `tests/test_box_style.c:144` | `static void test_ua_structural_wrappers_have_no_margin(void **state)` |
| `test_unknown_and_null_are_neutral_inline` | function | `tests/test_box_style.c:118` | `static void test_unknown_and_null_are_neutral_inline(void **state)` |
| `test_width_cap2_is_min_of_two_values` | function | `tests/test_box_style.c:523` | `static void test_width_cap2_is_min_of_two_values(void **state)` |
| `test_width_cap_pct` | function | `tests/test_box_style.c:508` | `static void test_width_cap_pct(void **state)` |
| `width` | function | `tests/test_box_style.c:552` | `* a negative width (CSS Values 4 section 10.1: out-of-range calc() results are * clamped at used-value time). */ assert_` |
| `UNSET4` | macro | `tests/test_box_tree.c:630` | `#define UNSET4` |
| `assert_rect` | function | `tests/test_box_tree.c:28` | `static void assert_rect(const bt_node *n, double x, double y, double w, double h)` |
| `card` | function | `tests/test_box_tree.c:769` | `* containing block climbs the unplaced card(1) → placed ancestor(0, x=100). */ assert_true(dbl_eq(out[2].x, 100));` |
| `main` | function | `tests/test_box_tree.c:931` | `int main(void)` |
| `test_abspos_resolves_against_placed_ancestor` | function | `tests/test_box_tree.c:744` | `static void test_abspos_resolves_against_placed_ancestor(void **state)` |
| `test_abspos_unplaced_without_anchor_falls_to_viewport` | function | `tests/test_box_tree.c:774` | `static void test_abspos_unplaced_without_anchor_falls_to_viewport(void **state)` |
| `test_block_stacking_with_collapse` | function | `tests/test_box_tree.c:62` | `static void test_block_stacking_with_collapse(void **state)` |
| `test_box_hidden_ancestor` | function | `tests/test_box_tree.c:806` | `static void test_box_hidden_ancestor(void **state)` |
| `test_box_hidden_fail_closed` | function | `tests/test_box_tree.c:819` | `static void test_box_hidden_fail_closed(void **state)` |
| `test_box_hidden_self` | function | `tests/test_box_tree.c:794` | `static void test_box_hidden_self(void **state)` |
| `test_children_cap` | function | `tests/test_box_tree.c:388` | `static void test_children_cap(void **state)` |
| `test_depth_cap` | function | `tests/test_box_tree.c:398` | `static void test_depth_cap(void **state)` |
| `test_display_none_skipped` | function | `tests/test_box_tree.c:353` | `static void test_display_none_skipped(void **state)` |
| `test_flex_auto_margin_pushes_item` | function | `tests/test_box_tree.c:95` | `static void test_flex_auto_margin_pushes_item(void **state)` |
| `test_flex_cross_axis_align` | function | `tests/test_box_tree.c:213` | `static void test_flex_cross_axis_align(void **state)` |
| `test_flex_gap_and_justify_center` | function | `tests/test_box_tree.c:113` | `static void test_flex_gap_and_justify_center(void **state)` |
| `test_flex_negative_gap` | function | `tests/test_box_tree.c:378` | `static void test_flex_negative_gap(void **state)` |
| `test_flex_nowrap_default_single_line_unchanged` | function | `tests/test_box_tree.c:151` | `static void test_flex_nowrap_default_single_line_unchanged(void **state)` |
| `test_flex_row_grow` | function | `tests/test_box_tree.c:75` | `static void test_flex_row_grow(void **state)` |
| `test_flex_wrap_reverse_two_lines` | function | `tests/test_box_tree.c:171` | `static void test_flex_wrap_reverse_two_lines(void **state)` |
| `test_flex_wrap_row_gap_distinct_from_gap` | function | `tests/test_box_tree.c:193` | `static void test_flex_wrap_row_gap_distinct_from_gap(void **state)` |
| `test_flex_wrap_two_lines` | function | `tests/test_box_tree.c:129` | `static void test_flex_wrap_two_lines(void **state)` |
| `test_grid` | function | `tests/test_box_tree.c:270` | `static void test_grid(void **state)` |
| `test_grid_bad_columns` | function | `tests/test_box_tree.c:368` | `static void test_grid_bad_columns(void **state)` |
| `test_grid_column_span` | function | `tests/test_box_tree.c:309` | `static void test_grid_column_span(void **state)` |
| `test_grid_row_gap_distinct_from_gap` | function | `tests/test_box_tree.c:231` | `static void test_grid_row_gap_distinct_from_gap(void **state)` |
| `test_grid_weighted_tracks` | function | `tests/test_box_tree.c:291` | `static void test_grid_weighted_tracks(void **state)` |
| `test_grid_without_row_gap_falls_back_to_gap` | function | `tests/test_box_tree.c:254` | `static void test_grid_without_row_gap_falls_back_to_gap(void **state)` |
| `test_leaf` | function | `tests/test_box_tree.c:40` | `static void test_leaf(void **state)` |
| `test_leaf_with_padding` | function | `tests/test_box_tree.c:47` | `static void test_leaf_with_padding(void **state)` |
| `test_nested_flex_in_block` | function | `tests/test_box_tree.c:329` | `static void test_nested_flex_in_block(void **state)` |
| `test_null_root` | function | `tests/test_box_tree.c:35` | `static void test_null_root(void **state)` |
| `test_oof_anchor_none_on_static_chain` | function | `tests/test_box_tree.c:832` | `static void test_oof_anchor_none_on_static_chain(void **state)` |
| `test_oof_anchor_self` | function | `tests/test_box_tree.c:842` | `static void test_oof_anchor_self(void **state)` |
| `test_oof_anchor_via_ancestor` | function | `tests/test_box_tree.c:849` | `static void test_oof_anchor_via_ancestor(void **state)` |
| `test_oof_avail_stretch_and_shrink` | function | `tests/test_box_tree.c:913` | `static void test_oof_avail_stretch_and_shrink(void **state)` |
| `test_oof_fail_open` | function | `tests/test_box_tree.c:891` | `static void test_oof_fail_open(void **state)` |
| `test_oof_nested_absolute_anchor_vs_root` | function | `tests/test_box_tree.c:862` | `static void test_oof_nested_absolute_anchor_vs_root(void **state)` |
| `test_oof_relative_does_not_anchor` | function | `tests/test_box_tree.c:877` | `static void test_oof_relative_does_not_anchor(void **state)` |
| `test_positioning_absolute_against_ancestor` | function | `tests/test_box_tree.c:462` | `static void test_positioning_absolute_against_ancestor(void **state)` |
| `test_positioning_absolute_against_viewport` | function | `tests/test_box_tree.c:485` | `static void test_positioning_absolute_against_viewport(void **state)` |
| `test_positioning_doc_order_tiebreak` | function | `tests/test_box_tree.c:559` | `static void test_positioning_doc_order_tiebreak(void **state)` |
| `test_positioning_fixed_against_viewport` | function | `tests/test_box_tree.c:502` | `static void test_positioning_fixed_against_viewport(void **state)` |
| `test_positioning_nbox_cap` | function | `tests/test_box_tree.c:611` | `static void test_positioning_nbox_cap(void **state)` |
| `test_positioning_no_insets` | function | `tests/test_box_tree.c:577` | `static void test_positioning_no_insets(void **state)` |
| `test_positioning_null_args` | function | `tests/test_box_tree.c:415` | `static void test_positioning_null_args(void **state)` |
| `test_positioning_null_geometry` | function | `tests/test_box_tree.c:594` | `static void test_positioning_null_geometry(void **state)` |
| `test_positioning_relative_offset` | function | `tests/test_box_tree.c:441` | `static void test_positioning_relative_offset(void **state)` |
| `test_positioning_stacking_order` | function | `tests/test_box_tree.c:539` | `static void test_positioning_stacking_order(void **state)` |
| `test_positioning_static_unchanged` | function | `tests/test_box_tree.c:429` | `static void test_positioning_static_unchanged(void **state)` |
| `test_positioning_sticky_treated_as_relative` | function | `tests/test_box_tree.c:521` | `static void test_positioning_sticky_treated_as_relative(void **state)` |
| `test_static_position_absolute_auto_insets` | function | `tests/test_box_tree.c:633` | `static void test_static_position_absolute_auto_insets(void **state)` |
| `test_static_position_explicit_insets_win` | function | `tests/test_box_tree.c:665` | `static void test_static_position_explicit_insets_win(void **state)` |
| `test_static_position_fixed_auto_insets` | function | `tests/test_box_tree.c:649` | `static void test_static_position_fixed_auto_insets(void **state)` |
| `test_static_position_mixed_axis` | function | `tests/test_box_tree.c:686` | `static void test_static_position_mixed_axis(void **state)` |
| `test_static_position_null_arrays_legacy` | function | `tests/test_box_tree.c:726` | `static void test_static_position_null_arrays_legacy(void **state)` |
| `test_static_position_right_inset_keeps_anchor` | function | `tests/test_box_tree.c:706` | `static void test_static_position_right_inset_keeps_anchor(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_browser.c:8` | `#define _POSIX_C_SOURCE` |
| `main` | function | `tests/test_browser.c:378` | `int main(void)` |
| `test_accepts_https_and_file` | function | `tests/test_browser.c:108` | `static void test_accepts_https_and_file(void **state)` |
| `test_back_forward_bounds` | function | `tests/test_browser.c:79` | `static void test_back_forward_bounds(void **state)` |
| `test_exceptions` | function | `tests/test_browser.c:252` | `static void test_exceptions(void **state)` |
| `test_init` | function | `tests/test_browser.c:20` | `static void test_init(void **state)` |
| `test_navigate_from_middle_discards_future` | function | `tests/test_browser.c:61` | `static void test_navigate_from_middle_discards_future(void **state)` |
| `test_navigate_history` | function | `tests/test_browser.c:31` | `static void test_navigate_history(void **state)` |
| `test_push_state_rejects_and_guards` | function | `tests/test_browser.c:361` | `static void test_push_state_rejects_and_guards(void **state)` |
| `test_push_state_same_document` | function | `tests/test_browser.c:328` | `static void test_push_state_same_document(void **state)` |
| `test_rejects_invalid_url` | function | `tests/test_browser.c:95` | `static void test_rejects_invalid_url(void **state)` |
| `test_set_page` | function | `tests/test_browser.c:196` | `static void test_set_page(void **state)` |
| `test_set_page_sanitizes_invalid_utf8` | function | `tests/test_browser.c:218` | `static void test_set_page_sanitizes_invalid_utf8(void **state)` |
| `test_status_toast` | function | `tests/test_browser.c:277` | `static void test_status_toast(void **state)` |
| `test_status_truncates` | function | `tests/test_browser.c:309` | `static void test_status_truncates(void **state)` |
| `test_url_bar_editing` | function | `tests/test_browser.c:122` | `static void test_url_bar_editing(void **state)` |
| `test_url_bar_selection` | function | `tests/test_browser.c:152` | `static void test_url_bar_selection(void **state)` |
| `main` | function | `tests/test_compositor.c:231` | `int main(void)` |
| `mk` | function | `tests/test_compositor.c:133` | `static cx_item mk(cx_layer layer, int z, int z_auto, size_t doc, size_t ref)` |
| `test_compare_layer_then_z_then_doc` | function | `tests/test_compositor.c:139` | `static void test_compare_layer_then_z_then_doc(void **state)` |
| `test_layer_float` | function | `tests/test_compositor.c:116` | `static void test_layer_float(void **state)` |
| `test_layer_inline_and_block` | function | `tests/test_compositor.c:123` | `static void test_layer_inline_and_block(void **state)` |
| `test_layer_negative_z` | function | `tests/test_compositor.c:86` | `static void test_layer_negative_z(void **state)` |
| `test_layer_positive_z` | function | `tests/test_compositor.c:93` | `static void test_layer_positive_z(void **state)` |
| `test_layer_zero_z_context` | function | `tests/test_compositor.c:100` | `static void test_layer_zero_z_context(void **state)` |
| `test_layer_zero_z_positioned_auto` | function | `tests/test_compositor.c:109` | `static void test_layer_zero_z_positioned_auto(void **state)` |
| `test_sc_fixed_sticky_always` | function | `tests/test_compositor.c:70` | `static void test_sc_fixed_sticky_always(void **state)` |
| `test_sc_isolation` | function | `tests/test_compositor.c:43` | `static void test_sc_isolation(void **state)` |
| `test_sc_mix_blend` | function | `tests/test_compositor.c:35` | `static void test_sc_mix_blend(void **state)` |
| `test_sc_opacity` | function | `tests/test_compositor.c:26` | `static void test_sc_opacity(void **state)` |
| `test_sc_positioned_z` | function | `tests/test_compositor.c:58` | `static void test_sc_positioned_z(void **state)` |
| `test_sc_static_none` | function | `tests/test_compositor.c:77` | `static void test_sc_static_none(void **state)` |
| `test_sc_transform` | function | `tests/test_compositor.c:51` | `static void test_sc_transform(void **state)` |
| `test_sort_full_paint_order` | function | `tests/test_compositor.c:160` | `static void test_sort_full_paint_order(void **state)` |
| `test_sort_matches_zindex_only_ordering` | function | `tests/test_compositor.c:218` | `static void test_sort_matches_zindex_only_ordering(void **state)` |
| `test_sort_noop_guards` | function | `tests/test_compositor.c:207` | `static void test_sort_noop_guards(void **state)` |
| `test_sort_stability` | function | `tests/test_compositor.c:193` | `static void test_sort_stability(void **state)` |
| `test_sort_z_within_layer` | function | `tests/test_compositor.c:177` | `static void test_sort_z_within_layer(void **state)` |
| `assert_int_equal` | function | `tests/test_css.c:1046` | `assert_int_equal(css_parse(
        "@supports (display:grid)` |
| `assert_int_equal` | function | `tests/test_css.c:1060` | `assert_int_equal(css_parse(
        "@supports (display:flex)` |
| `assert_int_equal` | function | `tests/test_css.c:1124` | `assert_int_equal(css_parse("@container (width>=10px)` |
| `assert_int_equal` | function | `tests/test_css.c:1707` | `assert_int_equal(css_parse("tr:nth-child(even)` |
| `assert_int_equal` | function | `tests/test_css.c:1730` | `assert_int_equal(css_parse("li:nth-last-child(2)` |
| `assert_int_equal` | function | `tests/test_css.c:1826` | `assert_int_equal(css_parse(".s:not(:focus)` |
| `assert_int_equal` | function | `tests/test_css.c:1854` | `assert_int_equal(css_parse("p:not(.x > y)` |
| `assert_int_equal` | function | `tests/test_css.c:2133` | `assert_int_equal(css_parse("li:nth-child()` |
| `assert_int_equal` | function | `tests/test_css.c:2168` | `assert_int_equal(css_parse("li:nth-of-type(2n)` |
| `assert_int_equal` | function | `tests/test_css.c:2200` | `assert_int_equal(css_parse("div:has(.x)` |
| `assert_int_equal` | function | `tests/test_css.c:2221` | `assert_int_equal(css_parse("html:lang(en)` |
| `assert_int_equal` | function | `tests/test_css.c:2577` | `assert_int_equal(css_parse(
        "@media (min-width: 600px)` |
| `assert_int_equal` | function | `tests/test_css.c:2592` | `assert_int_equal(css_parse(
        "@media screen and (min-width: 600px)` |
| `assert_int_equal` | function | `tests/test_css.c:2608` | `assert_int_equal(css_parse(
        "@media (frobnicate: 1)` |
| `assert_int_equal` | function | `tests/test_css.c:4769` | `assert_int_equal(css_parse("@media (min-width: 200em)` |
| `assert_int_equal` | function | `tests/test_css.c:4775` | `assert_int_equal(css_parse("@media (min-width: 40em)` |
| `box` | function | `tests/test_css.c:229` | `* box (CSS 2.1 section 10.8.1). With one line box per line and no separate * parent content edge, they land on the same ` |
| `closed` | function | `tests/test_css.c:473` | `* fail closed (unset), never a wrong guess. */ assert_int_equal( css_parse_inline("grid-template-columns: repeat(auto-fi` |
| `cls_el` | function | `tests/test_css.c:1222` | `static css_element cls_el(const char *tag, const char *const *cl, size_t n,
                     ...` |
| `color_for_class` | function | `tests/test_css.c:1145` | `static int color_for_class(const char *css, const char *cls)` |
| `downstream` | function | `tests/test_css.c:663` | `* and deciding whether to fetch happens downstream (render_doc.c) */ assert_string_equal(css_parse_inline( "background-i` |
| `dropped` | function | `tests/test_css.c:518` | `* dropped (which kept a lower rule's, or the UA button face's, colour). */
static void test_backg...` |
| `el_attr_node` | function | `tests/test_css.c:1490` | `static css_element el_attr_node(const char *tag, const char *id,
                                ...` |
| `el_node` | function | `tests/test_css.c:1455` | `static css_element el_node(const char *tag, const char *id,
                           const char...` |
| `el_sib_node` | function | `tests/test_css.c:1470` | `static css_element el_sib_node(const char *tag, int nth, int nsib,
                              ...` |
| `el_type_node` | function | `tests/test_css.c:1479` | `static css_element el_type_node(const char *tag, int nth, int nsib,
                             ...` |
| `geometry` | function | `tests/test_css.c:2860` | `* hostile sheet never sees real window geometry (anti-fingerprinting) yet 100vh
 * heroes and cal...` |
| `invalid` | function | `tests/test_css.c:765` | `* invalid (fail closed), not silently coerced into some default. */ css_style s = css_parse_inline("color: var(--missing` |
| `main` | function | `tests/test_css.c:4846` | `int main(void)` |
| `root_is_dark_html` | function | `tests/test_css.c:969` | `static int root_is_dark_html(void *ctx, const css_sel *sel)` |
| `silent` | function | `tests/test_css.c:2474` | `* silent (anti-DoS truncation, not a parse failure). 500 filler rules is well past
 * the OLD cap...` |
| `terminator` | function | `tests/test_css.c:1956` | `* terminator (consumed, not painted);` |
| `test_adjacent_sibling_combinator` | function | `tests/test_css.c:1581` | `static void test_adjacent_sibling_combinator(void **state)` |
| `test_anim_keyframes_resolved_from_sheet` | function | `tests/test_css.c:4519` | `static void test_anim_keyframes_resolved_from_sheet(void **state)` |
| `test_anim_transform_keyframes_from_sheet` | function | `tests/test_css.c:4552` | `static void test_anim_transform_keyframes_from_sheet(void **state)` |
| `test_at_rules_skipped` | function | `tests/test_css.c:2522` | `static void test_at_rules_skipped(void **state)` |
| `test_attr_case_insensitive_flag` | function | `tests/test_css.c:2309` | `static void test_attr_case_insensitive_flag(void **state)` |
| `test_attr_equals` | function | `tests/test_css.c:2259` | `static void test_attr_equals(void **state)` |
| `test_attr_in_combinator` | function | `tests/test_css.c:2366` | `static void test_attr_in_combinator(void **state)` |
| `test_attr_malformed_fail_closed` | function | `tests/test_css.c:2382` | `static void test_attr_malformed_fail_closed(void **state)` |
| `test_attr_name_case_insensitive` | function | `tests/test_css.c:2324` | `static void test_attr_name_case_insensitive(void **state)` |
| `test_attr_operators` | function | `tests/test_css.c:2277` | `static void test_attr_operators(void **state)` |
| `test_attr_presence` | function | `tests/test_css.c:2246` | `static void test_attr_presence(void **state)` |
| `test_attr_quoted_value_with_space` | function | `tests/test_css.c:2335` | `static void test_attr_quoted_value_with_space(void **state)` |
| `test_attr_specificity_and_compound` | function | `tests/test_css.c:2349` | `static void test_attr_specificity_and_compound(void **state)` |
| `test_backdrop_filter_blur` | function | `tests/test_css.c:4479` | `static void test_backdrop_filter_blur(void **state)` |
| `test_background_clip_text` | function | `tests/test_css.c:4354` | `static void test_background_clip_text(void **state)` |
| `test_background_rgba_alpha` | function | `tests/test_css.c:4325` | `static void test_background_rgba_alpha(void **state)` |
| `test_background_shorthand_resets_gradient` | function | `tests/test_css.c:621` | `static void test_background_shorthand_resets_gradient(void **state)` |
| `test_bg_image_url_absolute` | function | `tests/test_css.c:660` | `static void test_bg_image_url_absolute(void **state)` |
| `test_bg_image_url_basic` | function | `tests/test_css.c:642` | `static void test_bg_image_url_basic(void **state)` |
| `test_bg_image_url_gradient_mutually_exclusive` | function | `tests/test_css.c:696` | `static void test_bg_image_url_gradient_mutually_exclusive(void **state)` |
| `test_bg_image_url_none_and_junk_reset` | function | `tests/test_css.c:669` | `static void test_bg_image_url_none_and_junk_reset(void **state)` |
| `test_bg_image_url_overlong_fails_closed` | function | `tests/test_css.c:683` | `static void test_bg_image_url_overlong_fails_closed(void **state)` |
| `test_bg_image_url_quoted` | function | `tests/test_css.c:649` | `static void test_bg_image_url_quoted(void **state)` |
| `test_bg_shorthand_captures_url_and_resets_color` | function | `tests/test_css.c:704` | `static void test_bg_shorthand_captures_url_and_resets_color(void **state)` |
| `test_bg_size_and_repeat` | function | `tests/test_css.c:723` | `static void test_bg_size_and_repeat(void **state)` |
| `test_border_longhands` | function | `tests/test_css.c:3323` | `static void test_border_longhands(void **state)` |
| `test_border_shorthand` | function | `tests/test_css.c:3293` | `static void test_border_shorthand(void **state)` |
| `test_box_auto_and_centering` | function | `tests/test_css.c:2693` | `static void test_box_auto_and_centering(void **state)` |
| `test_box_clamp_anti_dos` | function | `tests/test_css.c:2950` | `static void test_box_clamp_anti_dos(void **state)` |
| `test_box_extension_sheet_cascade` | function | `tests/test_css.c:3000` | `static void test_box_extension_sheet_cascade(void **state)` |
| `test_box_orient_maps_to_flex_direction` | function | `tests/test_css.c:3449` | `static void test_box_orient_maps_to_flex_direction(void **state)` |
| `test_box_shadow_and_outline` | function | `tests/test_css.c:3349` | `static void test_box_shadow_and_outline(void **state)` |
| `test_box_sheet_cascade_inline_wins` | function | `tests/test_css.c:3127` | `static void test_box_sheet_cascade_inline_wins(void **state)` |
| `test_box_shorthand_expansion` | function | `tests/test_css.c:2665` | `static void test_box_shorthand_expansion(void **state)` |
| `test_box_sizing` | function | `tests/test_css.c:3285` | `static void test_box_sizing(void **state)` |
| `test_box_units_and_failclosed` | function | `tests/test_css.c:2710` | `static void test_box_units_and_failclosed(void **state)` |
| `test_calc_basic_arithmetic` | function | `tests/test_css.c:2806` | `static void test_calc_basic_arithmetic(void **state)` |
| `test_calc_clamped_anti_dos` | function | `tests/test_css.c:2852` | `static void test_calc_clamped_anti_dos(void **state)` |
| `test_calc_dimension_errors_fail_closed` | function | `tests/test_css.c:2830` | `static void test_calc_dimension_errors_fail_closed(void **state)` |
| `test_calc_inside_shorthands` | function | `tests/test_css.c:2905` | `static void test_calc_inside_shorthands(void **state)` |
| `test_calc_precedence_and_parens` | function | `tests/test_css.c:2815` | `static void test_calc_precedence_and_parens(void **state)` |
| `test_calc_units_and_signs` | function | `tests/test_css.c:2822` | `static void test_calc_units_and_signs(void **state)` |
| `test_calc_with_custom_property` | function | `tests/test_css.c:2943` | `static void test_calc_with_custom_property(void **state)` |
| `test_cascade_document_order` | function | `tests/test_css.c:2504` | `static void test_cascade_document_order(void **state)` |
| `test_cascade_inline_wins` | function | `tests/test_css.c:2513` | `static void test_cascade_inline_wins(void **state)` |
| `test_cascade_specificity` | function | `tests/test_css.c:2458` | `static void test_cascade_specificity(void **state)` |
| `test_child_combinator` | function | `tests/test_css.c:1534` | `static void test_child_combinator(void **state)` |
| `test_clip_auto` | function | `tests/test_css.c:4793` | `static void test_clip_auto(void **state)` |
| `test_clip_rect` | function | `tests/test_css.c:4783` | `static void test_clip_rect(void **state)` |
| `test_combinator_class_chain` | function | `tests/test_css.c:1562` | `static void test_combinator_class_chain(void **state)` |
| `test_combinator_specificity_sum` | function | `tests/test_css.c:1547` | `static void test_combinator_specificity_sum(void **state)` |
| `test_component_var_cascade_order` | function | `tests/test_css.c:1343` | `static void test_component_var_cascade_order(void **state)` |
| `test_component_var_inherited_by_child` | function | `tests/test_css.c:1323` | `static void test_component_var_inherited_by_child(void **state)` |
| `test_component_var_inline_overrides` | function | `tests/test_css.c:1360` | `static void test_component_var_inline_overrides(void **state)` |
| `test_component_var_same_element` | function | `tests/test_css.c:1310` | `static void test_component_var_same_element(void **state)` |
| `test_conic_gradient_basic` | function | `tests/test_css.c:4374` | `static void test_conic_gradient_basic(void **state)` |
| `test_conic_gradient_deg_positions` | function | `tests/test_css.c:4415` | `static void test_conic_gradient_deg_positions(void **state)` |
| `test_conic_gradient_fails_closed` | function | `tests/test_css.c:4425` | `static void test_conic_gradient_fails_closed(void **state)` |
| `test_conic_gradient_from_angle` | function | `tests/test_css.c:4386` | `static void test_conic_gradient_from_angle(void **state)` |
| `test_conic_gradient_pie_hard_stop` | function | `tests/test_css.c:4400` | `static void test_conic_gradient_pie_hard_stop(void **state)` |
| `test_container_block_still_skipped` | function | `tests/test_css.c:1121` | `static void test_container_block_still_skipped(void **state)` |
| `test_container_cascade_inline_wins` | function | `tests/test_css.c:376` | `static void test_container_cascade_inline_wins(void **state)` |
| `test_container_fail_closed_and_bounds` | function | `tests/test_css.c:391` | `static void test_container_fail_closed_and_bounds(void **state)` |
| `test_container_unset` | function | `tests/test_css.c:495` | `static void test_container_unset(void **state)` |
| `test_cursor` | function | `tests/test_css.c:3237` | `static void test_cursor(void **state)` |
| `test_custom_prop_attr_scoped_skipped_without_matcher` | function | `tests/test_css.c:993` | `static void test_custom_prop_attr_scoped_skipped_without_matcher(void **state)` |
| `test_custom_prop_attr_scoped_via_root_matcher` | function | `tests/test_css.c:981` | `static void test_custom_prop_attr_scoped_via_root_matcher(void **state)` |
| `test_custom_prop_chain_eight_deep` | function | `tests/test_css.c:946` | `static void test_custom_prop_chain_eight_deep(void **state)` |
| `test_custom_prop_class_scoped_applies_with_root_scope` | function | `tests/test_css.c:851` | `static void test_custom_prop_class_scoped_applies_with_root_scope(void **state)` |
| `test_custom_prop_class_scoped_skipped_without_scope` | function | `tests/test_css.c:839` | `static void test_custom_prop_class_scoped_skipped_without_scope(void **state)` |
| `test_custom_prop_dark_media_collected_in_dark` | function | `tests/test_css.c:826` | `static void test_custom_prop_dark_media_collected_in_dark(void **state)` |
| `test_custom_prop_dark_media_not_collected_in_light` | function | `tests/test_css.c:811` | `static void test_custom_prop_dark_media_not_collected_in_light(void **state)` |
| `test_custom_prop_descendant_scoped_skipped` | function | `tests/test_css.c:864` | `static void test_custom_prop_descendant_scoped_skipped(void **state)` |
| `test_custom_prop_fanout_bounded` | function | `tests/test_css.c:954` | `static void test_custom_prop_fanout_bounded(void **state)` |
| `test_custom_prop_long_name_survives` | function | `tests/test_css.c:915` | `static void test_custom_prop_long_name_survives(void **state)` |
| `test_custom_prop_long_value_survives` | function | `tests/test_css.c:900` | `static void test_custom_prop_long_value_survives(void **state)` |
| `test_custom_prop_root_matcher_rejects_descendant` | function | `tests/test_css.c:1004` | `static void test_custom_prop_root_matcher_rejects_descendant(void **state)` |
| `test_custom_prop_table_holds_hundreds` | function | `tests/test_css.c:876` | `static void test_custom_prop_table_holds_hundreds(void **state)` |
| `test_custom_prop_table_holds_thousands` | function | `tests/test_css.c:927` | `static void test_custom_prop_table_holds_thousands(void **state)` |
| `test_custom_prop_var_basic` | function | `tests/test_css.c:745` | `static void test_custom_prop_var_basic(void **state)` |
| `test_custom_prop_var_chain` | function | `tests/test_css.c:771` | `static void test_custom_prop_var_chain(void **state)` |
| `test_custom_prop_var_fallback_used_when_missing` | function | `tests/test_css.c:756` | `static void test_custom_prop_var_fallback_used_when_missing(void **state)` |
| `test_custom_prop_var_in_shorthand` | function | `tests/test_css.c:788` | `static void test_custom_prop_var_in_shorthand(void **state)` |
| `test_custom_prop_var_later_declaration_wins` | function | `tests/test_css.c:798` | `static void test_custom_prop_var_later_declaration_wins(void **state)` |
| `test_custom_prop_var_never_phones_home` | function | `tests/test_css.c:1397` | `static void test_custom_prop_var_never_phones_home(void **state)` |
| `test_custom_prop_var_no_fallback_drops_decl` | function | `tests/test_css.c:762` | `static void test_custom_prop_var_no_fallback_drops_decl(void **state)` |
| `test_custom_prop_var_self_reference_fails_closed` | function | `tests/test_css.c:779` | `static void test_custom_prop_var_self_reference_fails_closed(void **state)` |
| `test_custom_prop_var_unbalanced_paren_drops` | function | `tests/test_css.c:1384` | `static void test_custom_prop_var_unbalanced_paren_drops(void **state)` |
| `test_decl_split_ignores_semicolon_in_url_and_string` | function | `tests/test_css.c:1200` | `static void test_decl_split_ignores_semicolon_in_url_and_string(void **state)` |
| `test_descendant_combinator` | function | `tests/test_css.c:1518` | `static void test_descendant_combinator(void **state)` |
| `test_filter_blur_and_grayscale` | function | `tests/test_css.c:4491` | `static void test_filter_blur_and_grayscale(void **state)` |
| `test_filter_drop_shadow` | function | `tests/test_css.c:4452` | `static void test_filter_drop_shadow(void **state)` |
| `test_filter_drop_shadow_defaults_and_failclosed` | function | `tests/test_css.c:4465` | `static void test_filter_drop_shadow_defaults_and_failclosed(void **state)` |
| `test_flex_align` | function | `tests/test_css.c:3418` | `static void test_flex_align(void **state)` |
| `test_flex_item` | function | `tests/test_css.c:3374` | `static void test_flex_item(void **state)` |
| `test_float_and_clear` | function | `tests/test_css.c:3173` | `static void test_float_and_clear(void **state)` |
| `test_font_family` | function | `tests/test_css.c:138` | `static void test_font_family(void **state)` |
| `test_font_shorthand` | function | `tests/test_css.c:4295` | `static void test_font_shorthand(void **state)` |
| `test_gap_two_value` | function | `tests/test_css.c:4278` | `static void test_gap_two_value(void **state)` |
| `test_general_sibling_combinator` | function | `tests/test_css.c:1596` | `static void test_general_sibling_combinator(void **state)` |
| `test_gradient_stop_alpha` | function | `tests/test_css.c:1258` | `static void test_gradient_stop_alpha(void **state)` |
| `test_grid_extras` | function | `tests/test_css.c:3472` | `static void test_grid_extras(void **state)` |
| `test_grid_minmax_counts_as_one_track` | function | `tests/test_css.c:462` | `static void test_grid_minmax_counts_as_one_track(void **state)` |
| `test_grid_repeat_autofill_fails_closed` | function | `tests/test_css.c:470` | `static void test_grid_repeat_autofill_fails_closed(void **state)` |
| `test_grid_repeat_clamped_anti_dos` | function | `tests/test_css.c:488` | `static void test_grid_repeat_clamped_anti_dos(void **state)` |
| `test_grid_repeat_expands_count` | function | `tests/test_css.c:451` | `static void test_grid_repeat_expands_count(void **state)` |
| `test_grid_repeat_malformed_fails_closed` | function | `tests/test_css.c:481` | `static void test_grid_repeat_malformed_fails_closed(void **state)` |
| `test_has_parses_and_fails_closed` | function | `tests/test_css.c:2194` | `static void test_has_parses_and_fails_closed(void **state)` |
| `test_important_beats_specificity` | function | `tests/test_css.c:2410` | `static void test_important_beats_specificity(void **state)` |
| `test_important_in_shorthand` | function | `tests/test_css.c:2441` | `static void test_important_in_shorthand(void **state)` |
| `test_important_inline_beats_sheet_important` | function | `tests/test_css.c:2429` | `static void test_important_inline_beats_sheet_important(void **state)` |
| `test_important_inline_not_dropped` | function | `tests/test_css.c:2400` | `static void test_important_inline_not_dropped(void **state)` |
| `test_important_tier_then_normal_order` | function | `tests/test_css.c:2419` | `static void test_important_tier_then_normal_order(void **state)` |
| `test_inline_accent_color` | function | `tests/test_css.c:3773` | `static void test_inline_accent_color(void **state)` |
| `test_inline_appearance` | function | `tests/test_css.c:3644` | `static void test_inline_appearance(void **state)` |
| `test_inline_aspect_ratio` | function | `tests/test_css.c:3066` | `static void test_inline_aspect_ratio(void **state)` |
| `test_inline_backface_visibility` | function | `tests/test_css.c:4162` | `static void test_inline_backface_visibility(void **state)` |
| `test_inline_bg_clip_origin_attachment` | function | `tests/test_css.c:3702` | `static void test_inline_bg_clip_origin_attachment(void **state)` |
| `test_inline_bg_repeat` | function | `tests/test_css.c:3681` | `static void test_inline_bg_repeat(void **state)` |
| `test_inline_bg_size` | function | `tests/test_css.c:3693` | `static void test_inline_bg_size(void **state)` |
| `test_inline_border_collapse` | function | `tests/test_css.c:3557` | `static void test_inline_border_collapse(void **state)` |
| `test_inline_border_spacing` | function | `tests/test_css.c:3566` | `static void test_inline_border_spacing(void **state)` |
| `test_inline_box_longhands` | function | `tests/test_css.c:2647` | `static void test_inline_box_longhands(void **state)` |
| `test_inline_caption_side` | function | `tests/test_css.c:3586` | `static void test_inline_caption_side(void **state)` |
| `test_inline_caret_color` | function | `tests/test_css.c:3634` | `static void test_inline_caret_color(void **state)` |
| `test_inline_color_scheme` | function | `tests/test_css.c:3763` | `static void test_inline_color_scheme(void **state)` |
| `test_inline_contain` | function | `tests/test_css.c:3730` | `static void test_inline_contain(void **state)` |
| `test_inline_container_props` | function | `tests/test_css.c:328` | `static void test_inline_container_props(void **state)` |
| `test_inline_content_visibility` | function | `tests/test_css.c:3745` | `static void test_inline_content_visibility(void **state)` |
| `test_inline_direction` | function | `tests/test_css.c:3096` | `static void test_inline_direction(void **state)` |
| `test_inline_display` | function | `tests/test_css.c:290` | `static void test_inline_display(void **state)` |
| `test_inline_display_table_family` | function | `tests/test_css.c:303` | `static void test_inline_display_table_family(void **state)` |
| `test_inline_empty_cells` | function | `tests/test_css.c:3577` | `static void test_inline_empty_cells(void **state)` |
| `test_inline_font_kerning` | function | `tests/test_css.c:4092` | `static void test_inline_font_kerning(void **state)` |
| `test_inline_font_size` | function | `tests/test_css.c:42` | `static void test_inline_font_size(void **state)` |
| `test_inline_font_size_absolute_flag` | function | `tests/test_css.c:57` | `static void test_inline_font_size_absolute_flag(void **state)` |
| `test_inline_font_stretch` | function | `tests/test_css.c:4111` | `static void test_inline_font_stretch(void **state)` |
| `test_inline_font_variant` | function | `tests/test_css.c:3604` | `static void test_inline_font_variant(void **state)` |
| `test_inline_font_weight_style` | function | `tests/test_css.c:99` | `static void test_inline_font_weight_style(void **state)` |
| `test_inline_hyphens` | function | `tests/test_css.c:3613` | `static void test_inline_hyphens(void **state)` |
| `test_inline_image_rendering` | function | `tests/test_css.c:3754` | `static void test_inline_image_rendering(void **state)` |
| `test_inline_isolation` | function | `tests/test_css.c:3722` | `static void test_inline_isolation(void **state)` |
| `test_inline_line_height` | function | `tests/test_css.c:84` | `static void test_inline_line_height(void **state)` |
| `test_inline_list_style_pos` | function | `tests/test_css.c:4084` | `static void test_inline_list_style_pos(void **state)` |
| `test_inline_min_max_height` | function | `tests/test_css.c:2986` | `static void test_inline_min_max_height(void **state)` |
| `test_inline_min_width_height` | function | `tests/test_css.c:2959` | `static void test_inline_min_width_height(void **state)` |
| `test_inline_mix_blend_mode` | function | `tests/test_css.c:3796` | `static void test_inline_mix_blend_mode(void **state)` |
| `test_inline_object_fit` | function | `tests/test_css.c:4073` | `static void test_inline_object_fit(void **state)` |
| `test_inline_outline_longhands` | function | `tests/test_css.c:3526` | `static void test_inline_outline_longhands(void **state)` |
| `test_inline_outline_offset` | function | `tests/test_css.c:3105` | `static void test_inline_outline_offset(void **state)` |
| `test_inline_overscroll_behavior` | function | `tests/test_css.c:4153` | `static void test_inline_overscroll_behavior(void **state)` |
| `test_inline_pointer_events` | function | `tests/test_css.c:3655` | `static void test_inline_pointer_events(void **state)` |
| `test_inline_print_forced_adjust` | function | `tests/test_css.c:3782` | `static void test_inline_print_forced_adjust(void **state)` |
| `test_inline_resize` | function | `tests/test_css.c:4126` | `static void test_inline_resize(void **state)` |
| `test_inline_scroll_behavior` | function | `tests/test_css.c:4136` | `static void test_inline_scroll_behavior(void **state)` |
| `test_inline_tab_size` | function | `tests/test_css.c:3117` | `static void test_inline_tab_size(void **state)` |
| `test_inline_table_layout` | function | `tests/test_css.c:3595` | `static void test_inline_table_layout(void **state)` |
| `test_inline_text_align` | function | `tests/test_css.c:34` | `static void test_inline_text_align(void **state)` |
| `test_inline_text_decoration` | function | `tests/test_css.c:111` | `static void test_inline_text_decoration(void **state)` |
| `test_inline_text_decoration_color_style` | function | `tests/test_css.c:3020` | `static void test_inline_text_decoration_color_style(void **state)` |
| `test_inline_text_decoration_thickness` | function | `tests/test_css.c:3049` | `static void test_inline_text_decoration_thickness(void **state)` |
| `test_inline_text_rendering` | function | `tests/test_css.c:4101` | `static void test_inline_text_rendering(void **state)` |
| `test_inline_touch_action` | function | `tests/test_css.c:4144` | `static void test_inline_touch_action(void **state)` |
| `test_inline_transform_independent_cascade_combines` | function | `tests/test_css.c:4059` | `static void test_inline_transform_independent_cascade_combines(void **state)` |
| `test_inline_transform_rotate` | function | `tests/test_css.c:3908` | `static void test_inline_transform_rotate(void **state)` |
| `test_inline_transform_scale` | function | `tests/test_css.c:3868` | `static void test_inline_transform_scale(void **state)` |
| `test_inline_transform_skew` | function | `tests/test_css.c:3938` | `static void test_inline_transform_skew(void **state)` |
| `test_inline_transform_translate` | function | `tests/test_css.c:3817` | `static void test_inline_transform_translate(void **state)` |
| `test_inline_user_select` | function | `tests/test_css.c:3623` | `static void test_inline_user_select(void **state)` |
| `test_keyframes_content_does_not_crash` | function | `tests/test_css.c:1130` | `static void test_keyframes_content_does_not_crash(void **state)` |
| `test_keyframes_overflow_skips_block_not_sheet` | function | `tests/test_css.c:4623` | `static void test_keyframes_overflow_skips_block_not_sheet(void **state)` |
| `test_layer_block_applies` | function | `tests/test_css.c:1067` | `static void test_layer_block_applies(void **state)` |
| `test_layer_important_reverses` | function | `tests/test_css.c:1102` | `static void test_layer_important_reverses(void **state)` |
| `test_layer_inline_still_wins` | function | `tests/test_css.c:1112` | `static void test_layer_inline_still_wins(void **state)` |
| `test_layer_order_statement` | function | `tests/test_css.c:1089` | `static void test_layer_order_statement(void **state)` |
| `test_layout_sheet_cascade_and_unset` | function | `tests/test_css.c:3490` | `static void test_layout_sheet_cascade_and_unset(void **state)` |
| `test_letter_word_spacing` | function | `tests/test_css.c:173` | `static void test_letter_word_spacing(void **state)` |
| `test_linear_gradient_basic` | function | `tests/test_css.c:543` | `static void test_linear_gradient_basic(void **state)` |
| `test_linear_gradient_directions` | function | `tests/test_css.c:554` | `static void test_linear_gradient_directions(void **state)` |
| `test_linear_gradient_fail_closed` | function | `tests/test_css.c:591` | `static void test_linear_gradient_fail_closed(void **state)` |
| `test_linear_gradient_positions_emitted` | function | `tests/test_css.c:4435` | `static void test_linear_gradient_positions_emitted(void **state)` |
| `test_linear_gradient_stops` | function | `tests/test_css.c:573` | `static void test_linear_gradient_stops(void **state)` |
| `test_list_style_type` | function | `tests/test_css.c:261` | `static void test_list_style_type(void **state)` |
| `test_logical_inset_and_sizes` | function | `tests/test_css.c:4233` | `static void test_logical_inset_and_sizes(void **state)` |
| `test_logical_margin_padding` | function | `tests/test_css.c:4207` | `static void test_logical_margin_padding(void **state)` |
| `test_malformed_inline_no_crash` | function | `tests/test_css.c:737` | `static void test_malformed_inline_no_crash(void **state)` |
| `test_math_clamp` | function | `tests/test_css.c:4183` | `static void test_math_clamp(void **state)` |
| `test_math_min_max_top_level` | function | `tests/test_css.c:4171` | `static void test_math_min_max_top_level(void **state)` |
| `test_math_nested_in_calc` | function | `tests/test_css.c:4193` | `static void test_math_nested_in_calc(void **state)` |
| `test_media_and_or` | function | `tests/test_css.c:2589` | `static void test_media_and_or(void **state)` |
| `test_media_prefers_color_scheme` | function | `tests/test_css.c:2558` | `static void test_media_prefers_color_scheme(void **state)` |
| `test_media_query_length_honours_its_unit` | function | `tests/test_css.c:4762` | `static void test_media_query_length_honours_its_unit(void **state)` |
| `test_media_range_syntax_applies` | function | `tests/test_css.c:1020` | `static void test_media_range_syntax_applies(void **state)` |
| `test_media_screen_and_print` | function | `tests/test_css.c:2539` | `static void test_media_screen_and_print(void **state)` |
| `test_media_width_queries` | function | `tests/test_css.c:2574` | `static void test_media_width_queries(void **state)` |
| `test_not_unreadable_argument_fails_closed` | function | `tests/test_css.c:1851` | `static void test_not_unreadable_argument_fails_closed(void **state)` |
| `test_not_with_pseudo_class` | function | `tests/test_css.c:1823` | `static void test_not_with_pseudo_class(void **state)` |
| `test_opacity` | function | `tests/test_css.c:210` | `static void test_opacity(void **state)` |
| `test_overflow` | function | `tests/test_css.c:3214` | `static void test_overflow(void **state)` |
| `test_parse_null_args` | function | `tests/test_css.c:2623` | `static void test_parse_null_args(void **state)` |
| `test_place_shorthands` | function | `tests/test_css.c:4255` | `static void test_place_shorthands(void **state)` |
| `test_position_and_insets` | function | `tests/test_css.c:3142` | `static void test_position_and_insets(void **state)` |
| `test_property_initial_value` | function | `tests/test_css.c:1370` | `static void test_property_initial_value(void **state)` |
| `test_pseudo_content_before_after_separate` | function | `tests/test_css.c:1868` | `static void test_pseudo_content_before_after_separate(void **state)` |
| `test_pseudo_content_decodes_escaped_char` | function | `tests/test_css.c:1905` | `static void test_pseudo_content_decodes_escaped_char(void **state)` |
| `test_pseudo_content_decodes_hex_escape` | function | `tests/test_css.c:1882` | `static void test_pseudo_content_decodes_hex_escape(void **state)` |
| `test_pseudo_content_empty_without_pseudo` | function | `tests/test_css.c:2006` | `static void test_pseudo_content_empty_without_pseudo(void **state)` |
| `test_pseudo_content_escape_eats_terminator_space` | function | `tests/test_css.c:1894` | `static void test_pseudo_content_escape_eats_terminator_space(void **state)` |
| `test_pseudo_content_escapes_fail_closed` | function | `tests/test_css.c:1952` | `static void test_pseudo_content_escapes_fail_closed(void **state)` |
| `test_pseudo_content_none_parses_empty` | function | `tests/test_css.c:1983` | `static void test_pseudo_content_none_parses_empty(void **state)` |
| `test_pseudo_does_not_claim_cascade_slot` | function | `tests/test_css.c:2080` | `static void test_pseudo_does_not_claim_cascade_slot(void **state)` |
| `test_pseudo_element_style` | function | `tests/test_css.c:1273` | `static void test_pseudo_element_style(void **state)` |
| `test_pseudo_empty` | function | `tests/test_css.c:2181` | `static void test_pseudo_empty(void **state)` |
| `test_pseudo_geometry_does_not_leak_to_element` | function | `tests/test_css.c:2024` | `static void test_pseudo_geometry_does_not_leak_to_element(void **state)` |
| `test_pseudo_lang` | function | `tests/test_css.c:2218` | `static void test_pseudo_lang(void **state)` |
| `test_pseudo_link` | function | `tests/test_css.c:1628` | `static void test_pseudo_link(void **state)` |
| `test_pseudo_never_match_keeps_group` | function | `tests/test_css.c:1646` | `static void test_pseudo_never_match_keeps_group(void **state)` |
| `test_pseudo_nth_child` | function | `tests/test_css.c:1704` | `static void test_pseudo_nth_child(void **state)` |
| `test_pseudo_nth_last_child` | function | `tests/test_css.c:1727` | `static void test_pseudo_nth_last_child(void **state)` |
| `test_pseudo_nth_malformed_drops` | function | `tests/test_css.c:2128` | `static void test_pseudo_nth_malformed_drops(void **state)` |
| `test_pseudo_nth_of_type` | function | `tests/test_css.c:2165` | `static void test_pseudo_nth_of_type(void **state)` |
| `test_pseudo_of_type` | function | `tests/test_css.c:2146` | `static void test_pseudo_of_type(void **state)` |
| `test_pseudo_root_and_form_state` | function | `tests/test_css.c:1738` | `static void test_pseudo_root_and_form_state(void **state)` |
| `test_pseudo_single_colon_before_class_tmp` | function | `tests/test_css.c:1995` | `static void test_pseudo_single_colon_before_class_tmp(void **state)` |
| `test_pseudo_single_colon_before_matches` | function | `tests/test_css.c:1917` | `static void test_pseudo_single_colon_before_matches(void **state)` |
| `test_pseudo_specificity` | function | `tests/test_css.c:2093` | `static void test_pseudo_specificity(void **state)` |
| `test_pseudo_structural` | function | `tests/test_css.c:1684` | `static void test_pseudo_structural(void **state)` |
| `test_pseudo_target` | function | `tests/test_css.c:2207` | `static void test_pseudo_target(void **state)` |
| `test_pseudo_unknown_drops_selector` | function | `tests/test_css.c:1762` | `static void test_pseudo_unknown_drops_selector(void **state)` |
| `test_pseudo_with_sibling_combinator` | function | `tests/test_css.c:2111` | `static void test_pseudo_with_sibling_combinator(void **state)` |
| `test_rem_rebase_62_5_percent_idiom` | function | `tests/test_css.c:4747` | `static void test_rem_rebase_62_5_percent_idiom(void **state)` |
| `test_rem_rebase_absent_root_declaration_is_byte_identical` | function | `tests/test_css.c:4676` | `static void test_rem_rebase_absent_root_declaration_is_byte_identical(void **state)` |
| `test_rem_rebase_applies_to_box_lengths` | function | `tests/test_css.c:4662` | `static void test_rem_rebase_applies_to_box_lengths(void **state)` |
| `test_rem_rebase_honours_root_pseudo_class` | function | `tests/test_css.c:4688` | `static void test_rem_rebase_honours_root_pseudo_class(void **state)` |
| `test_rem_rebase_ignores_identifier_lookalikes` | function | `tests/test_css.c:4732` | `static void test_rem_rebase_ignores_identifier_lookalikes(void **state)` |
| `test_rem_rebase_leaves_quoted_text_alone` | function | `tests/test_css.c:4721` | `static void test_rem_rebase_leaves_quoted_text_alone(void **state)` |
| `test_rem_rebase_skips_at_rule_prelude` | function | `tests/test_css.c:4698` | `static void test_rem_rebase_skips_at_rule_prelude(void **state)` |
| `test_rem_rebased_on_root_font_size` | function | `tests/test_css.c:4650` | `static void test_rem_rebased_on_root_font_size(void **state)` |
| `test_resolve_el_inline_only` | function | `tests/test_css.c:2239` | `static void test_resolve_el_inline_only(void **state)` |
| `test_resolve_null_safe` | function | `tests/test_css.c:2633` | `static void test_resolve_null_safe(void **state)` |
| `test_selector_escape_inside_not` | function | `tests/test_css.c:1178` | `static void test_selector_escape_inside_not(void **state)` |
| `test_selector_escaped_colon_and_slash` | function | `tests/test_css.c:1154` | `static void test_selector_escaped_colon_and_slash(void **state)` |
| `test_selector_escaped_comma_and_parens` | function | `tests/test_css.c:1169` | `static void test_selector_escaped_comma_and_parens(void **state)` |
| `test_selector_hex_escape` | function | `tests/test_css.c:1162` | `static void test_selector_hex_escape(void **state)` |
| `test_selector_long_class_exact` | function | `tests/test_css.c:1185` | `static void test_selector_long_class_exact(void **state)` |
| `test_sheet_class_and_id` | function | `tests/test_css.c:1422` | `static void test_sheet_class_and_id(void **state)` |
| `test_sheet_compound_selector` | function | `tests/test_css.c:1442` | `static void test_sheet_compound_selector(void **state)` |
| `test_sheet_container_props` | function | `tests/test_css.c:356` | `static void test_sheet_container_props(void **state)` |
| `test_sheet_type_selector` | function | `tests/test_css.c:1411` | `static void test_sheet_type_selector(void **state)` |
| `test_sheet_universal_and_group` | function | `tests/test_css.c:1432` | `static void test_sheet_universal_and_group(void **state)` |
| `test_sibling_mixed_with_child` | function | `tests/test_css.c:1611` | `static void test_sibling_mixed_with_child(void **state)` |
| `test_supports_collects_custom_props` | function | `tests/test_css.c:1057` | `static void test_supports_collects_custom_props(void **state)` |
| `test_supports_true_block_applies` | function | `tests/test_css.c:1043` | `static void test_supports_true_block_applies(void **state)` |
| `test_table_sheet_cascade` | function | `tests/test_css.c:3666` | `static void test_table_sheet_cascade(void **state)` |
| `test_text_decoration_cascade` | function | `tests/test_css.c:1499` | `static void test_text_decoration_cascade(void **state)` |
| `test_text_decoration_wide_keyword_is_none` | function | `tests/test_css.c:1245` | `static void test_text_decoration_wide_keyword_is_none(void **state)` |
| `test_text_ext_cascade_and_important` | function | `tests/test_css.c:275` | `static void test_text_ext_cascade_and_important(void **state)` |
| `test_text_fill_color` | function | `tests/test_css.c:4363` | `static void test_text_fill_color(void **state)` |
| `test_text_indent` | function | `tests/test_css.c:241` | `static void test_text_indent(void **state)` |
| `test_text_overflow_and_word_break` | function | `tests/test_css.c:3253` | `static void test_text_overflow_and_word_break(void **state)` |
| `test_text_shadow` | function | `tests/test_css.c:188` | `static void test_text_shadow(void **state)` |
| `test_text_transform` | function | `tests/test_css.c:159` | `static void test_text_transform(void **state)` |
| `test_transform_origin` | function | `tests/test_css.c:4017` | `static void test_transform_origin(void **state)` |
| `test_unknown_props_ignored` | function | `tests/test_css.c:534` | `static void test_unknown_props_ignored(void **state)` |
| `test_unlayered_beats_layer_despite_specificity` | function | `tests/test_css.c:1079` | `static void test_unlayered_beats_layer_despite_specificity(void **state)` |
| `test_url_value_dropped` | function | `tests/test_css.c:505` | `static void test_url_value_dropped(void **state)` |
| `test_vendor_prefixes` | function | `tests/test_css.c:4810` | `static void test_vendor_prefixes(void **state)` |
| `test_vertical_align` | function | `tests/test_css.c:220` | `static void test_vertical_align(void **state)` |
| `test_viewport_units_font_size` | function | `tests/test_css.c:2884` | `static void test_viewport_units_font_size(void **state)` |
| `test_viewport_units_in_calc_and_mathfn` | function | `tests/test_css.c:2876` | `static void test_viewport_units_in_calc_and_mathfn(void **state)` |
| `test_viewport_units_junk_fail_closed` | function | `tests/test_css.c:2892` | `static void test_viewport_units_junk_fail_closed(void **state)` |
| `test_visibility` | function | `tests/test_css.c:3197` | `static void test_visibility(void **state)` |
| `test_white_space` | function | `tests/test_css.c:250` | `static void test_white_space(void **state)` |
| `test_white_space_break_spaces` | function | `tests/test_css.c:4317` | `static void test_white_space_break_spaces(void **state)` |
| `main` | function | `tests/test_css_atrule.c:102` | `int main(void)` |
| `sup` | function | `tests/test_css_atrule.c:30` | `static int sup(const char *c)` |
| `test_boolean_combinators` | function | `tests/test_css_atrule.c:41` | `static void test_boolean_combinators(void **state)` |
| `test_declaration_tests` | function | `tests/test_css_atrule.c:32` | `static void test_declaration_tests(void **state)` |
| `test_effective_spec_orders` | function | `tests/test_css_atrule.c:87` | `static void test_effective_spec_orders(void **state)` |
| `test_layer_ranks_first_appearance` | function | `tests/test_css_atrule.c:73` | `static void test_layer_ranks_first_appearance(void **state)` |
| `test_malformed_is_false` | function | `tests/test_css_atrule.c:58` | `static void test_malformed_is_false(void **state)` |
| `test_selector_function` | function | `tests/test_css_atrule.c:51` | `static void test_selector_function(void **state)` |
| `toy_decl` | function | `tests/test_css_atrule.c:16` | `static int toy_decl(void *ctx, const char *prop, const char *value)` |
| `toy_sel` | function | `tests/test_css_atrule.c:23` | `static int toy_sel(void *ctx, const char *sel)` |
| `main` | function | `tests/test_css_box.c:84` | `int main(void)` |
| `test_align_display_gap` | function | `tests/test_css_box.c:52` | `static void test_align_display_gap(void **state)` |
| `test_box4_partial_fails_closed` | function | `tests/test_css_box.c:44` | `static void test_box4_partial_fails_closed(void **state)` |
| `test_emit_len_claims_both_halves` | function | `tests/test_css_box.c:34` | `static void test_emit_len_claims_both_halves(void **state)` |
| `test_fit_content_trim` | function | `tests/test_css_box.c:70` | `static void test_fit_content_trim(void **state)` |
| `test_grid_repeat_autofill_dropped` | function | `tests/test_css_box.c:63` | `static void test_grid_repeat_autofill_dropped(void **state)` |
| `test_interp_len_auto_reject` | function | `tests/test_css_box.c:17` | `static void test_interp_len_auto_reject(void **state)` |
| `test_interp_len_bare_number_rejected` | function | `tests/test_css_box.c:26` | `static void test_interp_len_bare_number_rejected(void **state)` |
| `test_interp_len_px` | function | `tests/test_css_box.c:9` | `static void test_interp_len_px(void **state)` |
| `main` | function | `tests/test_css_color.c:358` | `int main(void)` |
| `oklch` | function | `tests/test_css_color.c:176` | `* Tailwind v4 writes its whole palette in oklch();` |
| `palette` | function | `tests/test_css_color.c:178` | `* Tailwind v4 palette (sRGB fallbacks it publishes). One unit of rounding slack
 * per channel. *...` |
| `preprocessor` | function | `tests/test_css_color.c:241` | `* is how a page written by a preprocessor (`hsl(0,0%,15.8333333333%)`, the shape a
 * SASS/LESS c...` |
| `result` | function | `tests/test_css_color.c:342` | `* result (`border:1px solid rgba(0,0,0,0)`). A non-zero alpha stays a colour. */
static void test...` |
| `rgba` | function | `tests/test_css_color.c:340` | `* rgba(0,0,0,0)). Minifiers and frameworks write it as #0000, rgba(0,0,0,0) or * hsla(...,0);` |
| `test_fractional_still_fails_closed` | function | `tests/test_css_color.c:280` | `static void test_fractional_still_fails_closed(void **state)` |
| `test_hex_bad` | function | `tests/test_css_color.c:59` | `static void test_hex_bad(void **state)` |
| `test_hex_long` | function | `tests/test_css_color.c:44` | `static void test_hex_long(void **state)` |
| `test_hex_long_alpha` | function | `tests/test_css_color.c:53` | `static void test_hex_long_alpha(void **state)` |
| `test_hex_short` | function | `tests/test_css_color.c:28` | `static void test_hex_short(void **state)` |
| `test_hex_short_alpha` | function | `tests/test_css_color.c:37` | `static void test_hex_short_alpha(void **state)` |
| `test_hsl` | function | `tests/test_css_color.c:134` | `static void test_hsl(void **state)` |
| `test_hsl_120` | function | `tests/test_css_color.c:140` | `static void test_hsl_120(void **state)` |
| `test_hsl_240` | function | `tests/test_css_color.c:147` | `static void test_hsl_240(void **state)` |
| `test_hsl_fractional_hue` | function | `tests/test_css_color.c:256` | `static void test_hsl_fractional_hue(void **state)` |
| `test_hsl_out_of_range` | function | `tests/test_css_color.c:160` | `static void test_hsl_out_of_range(void **state)` |
| `test_hsl_space_separated` | function | `tests/test_css_color.c:310` | `static void test_hsl_space_separated(void **state)` |
| `test_hsla` | function | `tests/test_css_color.c:154` | `static void test_hsla(void **state)` |
| `test_lab_family_malformed` | function | `tests/test_css_color.c:211` | `static void test_lab_family_malformed(void **state)` |
| `test_lab_lch` | function | `tests/test_css_color.c:203` | `static void test_lab_lch(void **state)` |
| `test_leading_dot_number` | function | `tests/test_css_color.c:272` | `static void test_leading_dot_number(void **state)` |
| `test_named` | function | `tests/test_css_color.c:100` | `static void test_named(void **state)` |
| `test_named_bad` | function | `tests/test_css_color.c:118` | `static void test_named_bad(void **state)` |
| `test_null_args` | function | `tests/test_css_color.c:22` | `static void test_null_args(void **state)` |
| `test_oklch_oklab` | function | `tests/test_css_color.c:188` | `static void test_oklch_oklab(void **state)` |
| `test_pack_unpack` | function | `tests/test_css_color.c:223` | `static void test_pack_unpack(void **state)` |
| `test_rgb_fractional` | function | `tests/test_css_color.c:263` | `static void test_rgb_fractional(void **state)` |
| `test_rgb_integer` | function | `tests/test_css_color.c:68` | `static void test_rgb_integer(void **state)` |
| `test_rgb_out_of_range` | function | `tests/test_css_color.c:90` | `static void test_rgb_out_of_range(void **state)` |
| `test_rgb_percent` | function | `tests/test_css_color.c:84` | `static void test_rgb_percent(void **state)` |
| `test_rgb_space_separated` | function | `tests/test_css_color.c:292` | `static void test_rgb_space_separated(void **state)` |
| `test_rgba_integer` | function | `tests/test_css_color.c:77` | `static void test_rgba_integer(void **state)` |
| `test_space_separated_still_fails_closed` | function | `tests/test_css_color.c:323` | `static void test_space_separated_still_fails_closed(void **state)` |
| `test_transparent_currentcolor` | function | `tests/test_css_color.c:126` | `static void test_transparent_currentcolor(void **state)` |
| `test_unsupported_syntax` | function | `tests/test_css_color.c:168` | `static void test_unsupported_syntax(void **state)` |
| `find_drop` | function | `tests/test_css_drops.c:31` | `static const css_drop *find_drop(const css_drop_log *log, const char *prop)` |
| `main` | function | `tests/test_css_drops.c:392` | `int main(void)` |
| `parse_nodrop` | function | `tests/test_css_drops.c:199` | `static css_sheet *parse_nodrop(const char *text)` |
| `test_accepted_declaration_is_not_logged` | function | `tests/test_css_drops.c:69` | `static void test_accepted_declaration_is_not_logged(void **state)` |
| `test_background_position_percentages` | function | `tests/test_css_drops.c:294` | `static void test_background_position_percentages(void **state)` |
| `test_background_size_two_lengths` | function | `tests/test_css_drops.c:283` | `static void test_background_size_two_lengths(void **state)` |
| `test_bad_value_is_distinguished` | function | `tests/test_css_drops.c:56` | `static void test_bad_value_is_distinguished(void **state)` |
| `test_css_wide_keyword_on_shorthand` | function | `tests/test_css_drops.c:324` | `static void test_css_wide_keyword_on_shorthand(void **state)` |
| `test_custom_property_is_not_a_drop` | function | `tests/test_css_drops.c:109` | `static void test_custom_property_is_not_a_drop(void **state)` |
| `test_font_shorthand_with_line_height` | function | `tests/test_css_drops.c:382` | `static void test_font_shorthand_with_line_height(void **state)` |
| `test_full_log_still_counts_total` | function | `tests/test_css_drops.c:121` | `static void test_full_log_still_counts_total(void **state)` |
| `test_intrinsic_sizing_keywords` | function | `tests/test_css_drops.c:360` | `static void test_intrinsic_sizing_keywords(void **state)` |
| `test_log_does_not_change_resolution` | function | `tests/test_css_drops.c:173` | `static void test_log_does_not_change_resolution(void **state)` |
| `test_long_value_truncates_and_control_bytes_are_stripped` | function | `tests/test_css_drops.c:145` | `static void test_long_value_truncates_and_control_bytes_are_stripped(void **state)` |
| `test_null_items_disables_listing` | function | `tests/test_css_drops.c:132` | `static void test_null_items_disables_listing(void **state)` |
| `test_overflow_two_values` | function | `tests/test_css_drops.c:334` | `static void test_overflow_two_values(void **state)` |
| `test_repeats_coalesce_by_property_and_cause` | function | `tests/test_css_drops.c:82` | `static void test_repeats_coalesce_by_property_and_cause(void **state)` |
| `test_transform_3d_flattens` | function | `tests/test_css_drops.c:260` | `static void test_transform_3d_flattens(void **state)` |
| `test_transform_angle_units` | function | `tests/test_css_drops.c:249` | `static void test_transform_angle_units(void **state)` |
| `test_transform_function_names_are_case_insensitive` | function | `tests/test_css_drops.c:238` | `static void test_transform_function_names_are_case_insensitive(void **state)` |
| `test_transform_origin_number_component` | function | `tests/test_css_drops.c:272` | `static void test_transform_origin_number_component(void **state)` |
| `test_unknown_property_is_logged` | function | `tests/test_css_drops.c:39` | `static void test_unknown_property_is_logged(void **state)` |
| `test_vendor_prefixed_value_keyword` | function | `tests/test_css_drops.c:372` | `static void test_vendor_prefixed_value_keyword(void **state)` |
| `test_vertical_align_length` | function | `tests/test_css_drops.c:313` | `static void test_vertical_align_length(void **state)` |
| `var` | function | `tests/test_css_drops.c:213` | `* was never collected and 40 var() declarations died as bad values. */
static void test_leading_b...` |
| `main` | function | `tests/test_css_gradient.c:84` | `int main(void)` |
| `test_degree_prelude_edges` | function | `tests/test_css_gradient.c:64` | `static void test_degree_prelude_edges(void **state)` |
| `test_junk_drops` | function | `tests/test_css_gradient.c:22` | `static void test_junk_drops(void **state)` |
| `test_linear_basic` | function | `tests/test_css_gradient.c:9` | `static void test_linear_basic(void **state)` |
| `test_shorthand_broken_drops` | function | `tests/test_css_gradient.c:54` | `static void test_shorthand_broken_drops(void **state)` |
| `test_shorthand_resets` | function | `tests/test_css_gradient.c:43` | `static void test_shorthand_resets(void **state)` |
| `test_url_single` | function | `tests/test_css_gradient.c:32` | `static void test_url_single(void **state)` |
| `EPS` | macro | `tests/test_css_length.c:19` | `#define EPS` |
| `expect_err` | function | `tests/test_css_length.c:27` | `static void expect_err(const char *value, const cl_ctx *ctx, cl_status want)` |
| `main` | function | `tests/test_css_length.c:450` | `int main(void)` |
| `px_of` | function | `tests/test_css_length.c:21` | `static double px_of(const char *value, const cl_ctx *ctx)` |
| `test_absolute_units` | function | `tests/test_css_length.c:45` | `static void test_absolute_units(void **state)` |
| `test_case_insensitive` | function | `tests/test_css_length.c:129` | `static void test_case_insensitive(void **state)` |
| `test_cl_number` | function | `tests/test_css_length.c:273` | `static void test_cl_number(void **state)` |
| `test_em_derivative` | function | `tests/test_css_length.c:379` | `static void test_em_derivative(void **state)` |
| `test_em_refit` | function | `tests/test_css_length.c:425` | `static void test_em_refit(void **state)` |
| `test_font_metric_fallbacks` | function | `tests/test_css_length.c:75` | `static void test_font_metric_fallbacks(void **state)` |
| `test_font_relative_classifier` | function | `tests/test_css_length.c:226` | `static void test_font_relative_classifier(void **state)` |
| `test_font_relative_em_rem` | function | `tests/test_css_length.c:61` | `static void test_font_relative_em_rem(void **state)` |
| `test_initial_ctx` | function | `tests/test_css_length.c:258` | `static void test_initial_ctx(void **state)` |
| `test_is_length_unit` | function | `tests/test_css_length.c:244` | `static void test_is_length_unit(void **state)` |
| `test_line_height_units` | function | `tests/test_css_length.c:92` | `static void test_line_height_units(void **state)` |
| `test_lp_parse` | function | `tests/test_css_length.c:304` | `static void test_lp_parse(void **state)` |
| `test_lp_used` | function | `tests/test_css_length.c:356` | `static void test_lp_used(void **state)` |
| `test_not_a_length` | function | `tests/test_css_length.c:152` | `static void test_not_a_length(void **state)` |
| `test_null_args` | function | `tests/test_css_length.c:180` | `static void test_null_args(void **state)` |
| `test_number_grammar` | function | `tests/test_css_length.c:140` | `static void test_number_grammar(void **state)` |
| `test_range` | function | `tests/test_css_length.c:192` | `static void test_range(void **state)` |
| `test_syntax` | function | `tests/test_css_length.c:164` | `static void test_syntax(void **state)` |
| `test_unit_scale` | function | `tests/test_css_length.c:207` | `static void test_unit_scale(void **state)` |
| `test_unitless` | function | `tests/test_css_length.c:34` | `static void test_unitless(void **state)` |
| `test_viewport_units` | function | `tests/test_css_length.c:104` | `static void test_viewport_units(void **state)` |
| `m` | function | `tests/test_css_mq.c:13` | `static int m(const char *q)` |
| `main` | function | `tests/test_css_mq.c:91` | `int main(void)` |
| `test_desktop_identity` | function | `tests/test_css_mq.c:56` | `static void test_desktop_identity(void **state)` |
| `test_fail_closed` | function | `tests/test_css_mq.c:78` | `static void test_fail_closed(void **state)` |
| `test_not_or` | function | `tests/test_css_mq.c:44` | `static void test_not_or(void **state)` |
| `test_plain_and_types` | function | `tests/test_css_mq.c:30` | `static void test_plain_and_types(void **state)` |
| `test_range_syntax` | function | `tests/test_css_mq.c:15` | `static void test_range_syntax(void **state)` |
| `main` | function | `tests/test_css_text.c:56` | `int main(void)` |
| `test_aspect_ratio` | function | `tests/test_css_text.c:44` | `static void test_aspect_ratio(void **state)` |
| `test_fontfamily_bucket` | function | `tests/test_css_text.c:10` | `static void test_fontfamily_bucket(void **state)` |
| `test_opacity_shapes` | function | `tests/test_css_text.c:18` | `static void test_opacity_shapes(void **state)` |
| `test_shadow_needs_both_offsets` | function | `tests/test_css_text.c:34` | `static void test_shadow_needs_both_offsets(void **state)` |
| `test_whitespace_direction` | function | `tests/test_css_text.c:26` | `static void test_whitespace_direction(void **state)` |
| `digit` | function | `tests/test_css_values.c:43` | `* digit(s) -- the minifier writes `transparent` as #0000. */ assert_int_equal(cv_bg_alpha_of("#0000"), 0);` |
| `main` | function | `tests/test_css_values.c:71` | `int main(void)` |
| `test_alpha` | function | `tests/test_css_values.c:33` | `static void test_alpha(void **state)` |
| `test_bg_skips_url` | function | `tests/test_css_values.c:65` | `static void test_bg_skips_url(void **state)` |
| `test_junk_fails_closed` | function | `tests/test_css_values.c:24` | `static void test_junk_fails_closed(void **state)` |
| `test_parse_named` | function | `tests/test_css_values.c:9` | `static void test_parse_named(void **state)` |
| `test_sentinels_ok` | function | `tests/test_css_values.c:16` | `static void test_sentinels_ok(void **state)` |
| `get` | function | `tests/test_css_vars.c:19` | `static const char *get(const cvr_table *t, const char *n)` |
| `main` | function | `tests/test_css_vars.c:185` | `int main(void)` |
| `set` | function | `tests/test_css_vars.c:15` | `static int set(cvr_table *t, const char *n, const char *v)` |
| `test_bounds_drop_whole` | function | `tests/test_css_vars.c:46` | `static void test_bounds_drop_whole(void **state)` |
| `test_collect_keeps_semicolon_inside_url` | function | `tests/test_css_vars.c:98` | `static void test_collect_keeps_semicolon_inside_url(void **state)` |
| `test_collect_strips_important_and_trims` | function | `tests/test_css_vars.c:86` | `static void test_collect_strips_important_and_trims(void **state)` |
| `test_cycle_takes_fallback` | function | `tests/test_css_vars.c:149` | `static void test_cycle_takes_fallback(void **state)` |
| `test_fallback_fanout_is_budgeted` | function | `tests/test_css_vars.c:162` | `static void test_fallback_fanout_is_budgeted(void **state)` |
| `test_grows_to_thousands` | function | `tests/test_css_vars.c:66` | `static void test_grows_to_thousands(void **state)` |
| `test_names_are_case_sensitive` | function | `tests/test_css_vars.c:36` | `static void test_names_are_case_sensitive(void **state)` |
| `test_resolve_depth_and_cycle` | function | `tests/test_css_vars.c:129` | `static void test_resolve_depth_and_cycle(void **state)` |
| `test_resolve_overflow_fails` | function | `tests/test_css_vars.c:174` | `static void test_resolve_overflow_fails(void **state)` |
| `test_resolve_scope_order_and_fallback` | function | `tests/test_css_vars.c:110` | `static void test_resolve_scope_order_and_fallback(void **state)` |
| `test_set_get_overwrite` | function | `tests/test_css_vars.c:23` | `static void test_set_get_overwrite(void **state)` |
| `main` | function | `tests/test_data_url.c:317` | `int main(void)` |
| `test_decode_bad_length_not_multiple_of_4` | function | `tests/test_data_url.c:193` | `static void test_decode_bad_length_not_multiple_of_4(void **state)` |
| `test_decode_base64_forgiving_and_mime` | function | `tests/test_data_url.c:284` | `static void test_decode_base64_forgiving_and_mime(void **state)` |
| `test_decode_empty` | function | `tests/test_data_url.c:183` | `static void test_decode_empty(void **state)` |
| `test_decode_invalid_character` | function | `tests/test_data_url.c:210` | `static void test_decode_invalid_character(void **state)` |
| `test_decode_multi_group` | function | `tests/test_data_url.c:171` | `static void test_decode_multi_group(void **state)` |
| `test_decode_no_padding_needed` | function | `tests/test_data_url.c:159` | `static void test_decode_no_padding_needed(void **state)` |
| `test_decode_nulls` | function | `tests/test_data_url.c:236` | `static void test_decode_nulls(void **state)` |
| `test_decode_one_byte_double_pad` | function | `tests/test_data_url.c:135` | `static void test_decode_one_byte_double_pad(void **state)` |
| `test_decode_padding_in_wrong_position` | function | `tests/test_data_url.c:201` | `static void test_decode_padding_in_wrong_position(void **state)` |
| `test_decode_percent_encoded_script` | function | `tests/test_data_url.c:270` | `static void test_decode_percent_encoded_script(void **state)` |
| `test_decode_rejects` | function | `tests/test_data_url.c:302` | `static void test_decode_rejects(void **state)` |
| `test_decode_too_large` | function | `tests/test_data_url.c:221` | `static void test_decode_too_large(void **state)` |
| `test_decode_two_bytes_single_pad` | function | `tests/test_data_url.c:146` | `static void test_decode_two_bytes_single_pad(void **state)` |
| `test_end_to_end_png_data_uri` | function | `tests/test_data_url.c:247` | `static void test_end_to_end_png_data_uri(void **state)` |
| `test_is_data_url_false` | function | `tests/test_data_url.c:31` | `static void test_is_data_url_false(void **state)` |
| `test_is_data_url_true` | function | `tests/test_data_url.c:23` | `static void test_is_data_url_true(void **state)` |
| `test_payload_base64_flag_case_insensitive` | function | `tests/test_data_url.c:97` | `static void test_payload_base64_flag_case_insensitive(void **state)` |
| `test_payload_basic` | function | `tests/test_data_url.c:43` | `static void test_payload_basic(void **state)` |
| `test_payload_empty` | function | `tests/test_data_url.c:63` | `static void test_payload_empty(void **state)` |
| `test_payload_no_comma` | function | `tests/test_data_url.c:89` | `static void test_payload_no_comma(void **state)` |
| `test_payload_no_mediatype` | function | `tests/test_data_url.c:54` | `static void test_payload_no_mediatype(void **state)` |
| `test_payload_not_data_url` | function | `tests/test_data_url.c:73` | `static void test_payload_not_data_url(void **state)` |
| `test_payload_nulls` | function | `tests/test_data_url.c:122` | `static void test_payload_nulls(void **state)` |
| `test_payload_percent_encoded_not_supported` | function | `tests/test_data_url.c:81` | `static void test_payload_percent_encoded_not_supported(void **state)` |
| `test_payload_too_large` | function | `tests/test_data_url.c:106` | `static void test_payload_too_large(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_disk_store.c:8` | `#define _POSIX_C_SOURCE` |
| `count_dir_entries` | function | `tests/test_disk_store.c:65` | `static size_t count_dir_entries(const char *dir)` |
| `dir` | type_alias | `tests/test_disk_store.c:32` | `typedef struct fixture { char dir[64];` |
| `fixture` | struct | `tests/test_disk_store.c:33` | `` |
| `main` | function | `tests/test_disk_store.c:181` | `int main(void)` |
| `setup` | function | `tests/test_disk_store.c:35` | `static int setup(void **state)` |
| `teardown` | function | `tests/test_disk_store.c:45` | `static int teardown(void **state)` |
| `test_empty` | function | `tests/test_disk_store.c:99` | `static void test_empty(void **state)` |
| `test_missing_and_null` | function | `tests/test_disk_store.c:168` | `static void test_missing_and_null(void **state)` |
| `test_no_temp_left` | function | `tests/test_disk_store.c:117` | `static void test_no_temp_left(void **state)` |
| `test_overwrite` | function | `tests/test_disk_store.c:124` | `static void test_overwrite(void **state)` |
| `test_permissions` | function | `tests/test_disk_store.c:108` | `static void test_permissions(void **state)` |
| `test_roundtrip` | function | `tests/test_disk_store.c:78` | `static void test_roundtrip(void **state)` |
| `test_roundtrip_chacha` | function | `tests/test_disk_store.c:89` | `static void test_roundtrip_chacha(void **state)` |
| `test_tamper_on_disk` | function | `tests/test_disk_store.c:150` | `static void test_tamper_on_disk(void **state)` |
| `test_wrong_key` | function | `tests/test_disk_store.c:138` | `static void test_wrong_key(void **state)` |
| `DOC` | macro | `tests/test_dom.c:55` | `#define DOC(state)` |
| `IDX` | macro | `tests/test_dom.c:56` | `#define IDX(state)` |
| `main` | function | `tests/test_dom.c:636` | `int main(void)` |
| `rule` | function | `tests/test_dom.c:405` | `* silently drops the whole rule (fail closed), so the title read black-on-teal
 * instead of the ...` |
| `setup_doc` | function | `tests/test_dom.c:32` | `static int setup_doc(void **state)` |
| `teardown_doc` | function | `tests/test_dom.c:45` | `static int teardown_doc(void **state)` |
| `test_append_rejects_cycle` | function | `tests/test_dom.c:259` | `static void test_append_rejects_cycle(void **state)` |
| `test_attributes` | function | `tests/test_dom.c:171` | `static void test_attributes(void **state)` |
| `test_build_null_args` | function | `tests/test_dom.c:60` | `static void test_build_null_args(void **state)` |
| `test_by_class` | function | `tests/test_dom.c:109` | `static void test_by_class(void **state)` |
| `test_by_tag` | function | `tests/test_dom.c:118` | `static void test_by_tag(void **state)` |
| `test_by_tag_results_in_document_order` | function | `tests/test_dom.c:127` | `static void test_by_tag_results_in_document_order(void **state)` |
| `test_char_nodes` | function | `tests/test_dom.c:589` | `static void test_char_nodes(void **state)` |
| `test_clone_node` | function | `tests/test_dom.c:525` | `static void test_clone_node(void **state)` |
| `test_construction_invalid_args` | function | `tests/test_dom.c:327` | `static void test_construction_invalid_args(void **state)` |
| `test_create_and_append` | function | `tests/test_dom.c:241` | `static void test_create_and_append(void **state)` |
| `test_document_order` | function | `tests/test_dom.c:137` | `static void test_document_order(void **state)` |
| `test_free_null_and_double` | function | `tests/test_dom.c:70` | `static void test_free_null_and_double(void **state)` |
| `test_get_by_id` | function | `tests/test_dom.c:88` | `static void test_get_by_id(void **state)` |
| `test_get_by_id_absent` | function | `tests/test_dom.c:102` | `static void test_get_by_id_absent(void **state)` |
| `test_get_inner_html` | function | `tests/test_dom.c:335` | `static void test_get_inner_html(void **state)` |
| `test_insert_before` | function | `tests/test_dom.c:493` | `static void test_insert_before(void **state)` |
| `test_matches_and_closest` | function | `tests/test_dom.c:460` | `static void test_matches_and_closest(void **state)` |
| `test_move_children` | function | `tests/test_dom.c:548` | `static void test_move_children(void **state)` |
| `test_navigation` | function | `tests/test_dom.c:151` | `static void test_navigation(void **state)` |
| `test_node_count` | function | `tests/test_dom.c:81` | `static void test_node_count(void **state)` |
| `test_query_selector_all_counts` | function | `tests/test_dom.c:377` | `static void test_query_selector_all_counts(void **state)` |
| `test_query_selector_combinators` | function | `tests/test_dom.c:388` | `static void test_query_selector_combinators(void **state)` |
| `test_query_selector_fail_closed` | function | `tests/test_dom.c:473` | `static void test_query_selector_fail_closed(void **state)` |
| `test_query_selector_nth_and_structural` | function | `tests/test_dom.c:435` | `static void test_query_selector_nth_and_structural(void **state)` |
| `test_query_selector_scope_is_descendants_only` | function | `tests/test_dom.c:448` | `static void test_query_selector_scope_is_descendants_only(void **state)` |
| `test_query_selector_type_class_id` | function | `tests/test_dom.c:363` | `static void test_query_selector_type_class_id(void **state)` |
| `test_remove_attribute` | function | `tests/test_dom.c:294` | `static void test_remove_attribute(void **state)` |
| `test_remove_child` | function | `tests/test_dom.c:269` | `static void test_remove_child(void **state)` |
| `test_set_and_get_document_title` | function | `tests/test_dom.c:229` | `static void test_set_and_get_document_title(void **state)` |
| `test_set_attribute_reindexes_id` | function | `tests/test_dom.c:281` | `static void test_set_attribute_reindexes_id(void **state)` |
| `test_set_inner_html` | function | `tests/test_dom.c:311` | `static void test_set_inner_html(void **state)` |
| `test_set_text_content_changes_tree` | function | `tests/test_dom.c:196` | `static void test_set_text_content_changes_tree(void **state)` |
| `test_set_text_content_empty_clears` | function | `tests/test_dom.c:214` | `static void test_set_text_content_empty_clears(void **state)` |
| `test_set_text_content_invalid_node` | function | `tests/test_dom.c:224` | `static void test_set_text_content_invalid_node(void **state)` |
| `test_text_content_read` | function | `tests/test_dom.c:185` | `static void test_text_content_read(void **state)` |
| `build` | function | `tests/test_dom_debug.c:36` | `static rd_doc *build(pv_view *v, rdp_caps caps)` |
| `caps_css_on` | function | `tests/test_dom_debug.c:29` | `static rdp_caps caps_css_on(void)` |
| `main` | function | `tests/test_dom_debug.c:269` | `int main(void)` |
| `test_box_tree_width_cap` | function | `tests/test_dom_debug.c:116` | `static void test_box_tree_width_cap(void **state)` |
| `test_control_bytes_kept_on_one_line` | function | `tests/test_dom_debug.c:245` | `static void test_control_bytes_kept_on_one_line(void **state)` |
| `test_grid_container_annotation` | function | `tests/test_dom_debug.c:92` | `static void test_grid_container_annotation(void **state)` |
| `test_heading_paragraph_link` | function | `tests/test_dom_debug.c:59` | `static void test_heading_paragraph_link(void **state)` |
| `test_no_box_tree_without_css` | function | `tests/test_dom_debug.c:197` | `static void test_no_box_tree_without_css(void **state)` |
| `test_null_doc_is_empty_header` | function | `tests/test_dom_debug.c:45` | `static void test_null_doc_is_empty_header(void **state)` |
| `test_truncation_no_overflow` | function | `tests/test_dom_debug.c:217` | `static void test_truncation_no_overflow(void **state)` |
| `test_visibility_overflow_cursor_and_text_wrap` | function | `tests/test_dom_debug.c:154` | `static void test_visibility_overflow_cursor_and_text_wrap(void **state)` |
| `builder` | function | `tests/test_download.c:8` | `* builder (join, separator rejection, overflow, NULL), and the size cap.
 */

#include <setjmp.h>...` |
| `main` | function | `tests/test_download.c:204` | `int main(void)` |
| `test_build_path_basic` | function | `tests/test_download.c:158` | `static void test_build_path_basic(void **state)` |
| `test_build_path_null_args` | function | `tests/test_download.c:186` | `static void test_build_path_null_args(void **state)` |
| `test_build_path_overflow` | function | `tests/test_download.c:179` | `static void test_build_path_overflow(void **state)` |
| `test_build_path_rejects_separator_in_name` | function | `tests/test_download.c:172` | `static void test_build_path_rejects_separator_in_name(void **state)` |
| `test_build_path_trailing_slash` | function | `tests/test_download.c:165` | `static void test_build_path_trailing_slash(void **state)` |
| `test_check_size` | function | `tests/test_download.c:197` | `static void test_check_size(void **state)` |
| `test_ext_known_types` | function | `tests/test_download.c:52` | `static void test_ext_known_types(void **state)` |
| `test_ext_unknown_type` | function | `tests/test_download.c:63` | `static void test_ext_unknown_type(void **state)` |
| `test_pick_appends_extension_when_missing` | function | `tests/test_download.c:99` | `static void test_pick_appends_extension_when_missing(void **state)` |
| `test_pick_fallback_when_empty` | function | `tests/test_download.c:129` | `static void test_pick_fallback_when_empty(void **state)` |
| `test_pick_from_disposition_ext_form` | function | `tests/test_download.c:81` | `static void test_pick_from_disposition_ext_form(void **state)` |
| `test_pick_from_disposition_quoted` | function | `tests/test_download.c:72` | `static void test_pick_from_disposition_quoted(void **state)` |
| `test_pick_from_url_segment` | function | `tests/test_download.c:91` | `static void test_pick_from_url_segment(void **state)` |
| `test_pick_keeps_existing_extension` | function | `tests/test_download.c:108` | `static void test_pick_keeps_existing_extension(void **state)` |
| `test_pick_null_out` | function | `tests/test_download.c:141` | `static void test_pick_null_out(void **state)` |
| `test_pick_overflow_fails_closed` | function | `tests/test_download.c:148` | `static void test_pick_overflow_fails_closed(void **state)` |
| `test_pick_traversal_contained` | function | `tests/test_download.c:117` | `static void test_pick_traversal_contained(void **state)` |
| `test_should_binary_types` | function | `tests/test_download.c:41` | `static void test_should_binary_types(void **state)` |
| `test_should_renderable_types` | function | `tests/test_download.c:30` | `static void test_should_renderable_types(void **state)` |
| `article` | function | `tests/test_flex_layout.c:351` | `* article (slashdot-cols probe: score 13.41). */

static void test_float_pack_m_holy_grail_pull_u...` |
| `assert_item` | function | `tests/test_flex_layout.c:26` | `static void assert_item(fx_result r, double pos, double size)` |
| `main` | function | `tests/test_flex_layout.c:1031` | `int main(void)` |
| `test_area_hash_basics` | function | `tests/test_flex_layout.c:775` | `static void test_area_hash_basics(void **state)` |
| `test_areas_non_rectangular_is_rejected` | function | `tests/test_flex_layout.c:853` | `static void test_areas_non_rectangular_is_rejected(void **state)` |
| `test_areas_null_cell` | function | `tests/test_flex_layout.c:821` | `static void test_areas_null_cell(void **state)` |
| `test_areas_parse_and_resolve` | function | `tests/test_flex_layout.c:787` | `static void test_areas_parse_and_resolve(void **state)` |
| `test_areas_parse_bounds` | function | `tests/test_flex_layout.c:885` | `static void test_areas_parse_bounds(void **state)` |
| `test_areas_parse_fails_closed` | function | `tests/test_flex_layout.c:867` | `static void test_areas_parse_fails_closed(void **state)` |
| `test_areas_rect_spans_rows_and_cols` | function | `tests/test_flex_layout.c:836` | `static void test_areas_rect_spans_rows_and_cols(void **state)` |
| `test_auto_margins_push_right_and_center` | function | `tests/test_flex_layout.c:938` | `static void test_auto_margins_push_right_and_center(void **state)` |
| `test_auto_min_size_is_min_content` | function | `tests/test_flex_layout.c:642` | `static void test_auto_min_size_is_min_content(void **state)` |
| `test_column_place_auto_margins` | function | `tests/test_flex_layout.c:1014` | `static void test_column_place_auto_margins(void **state)` |
| `test_column_place_stack_and_justify` | function | `tests/test_flex_layout.c:971` | `static void test_column_place_stack_and_justify(void **state)` |
| `test_cross_offset` | function | `tests/test_flex_layout.c:1000` | `static void test_cross_offset(void **state)` |
| `test_flex_errors` | function | `tests/test_flex_layout.c:146` | `static void test_flex_errors(void **state)` |
| `test_flex_zero_items_is_noop` | function | `tests/test_flex_layout.c:141` | `static void test_flex_zero_items_is_noop(void **state)` |
| `test_float_insets_both_sides_take_the_tightest` | function | `tests/test_flex_layout.c:484` | `static void test_float_insets_both_sides_take_the_tightest(void **state)` |
| `test_float_insets_edges` | function | `tests/test_flex_layout.c:521` | `static void test_float_insets_edges(void **state)` |
| `test_float_insets_left_overlapping_line` | function | `tests/test_flex_layout.c:447` | `static void test_float_insets_left_overlapping_line(void **state)` |
| `test_float_insets_line_past_bottom_is_full_width` | function | `tests/test_flex_layout.c:457` | `static void test_float_insets_line_past_bottom_is_full_width(void **state)` |
| `test_float_insets_never_starve_the_line` | function | `tests/test_flex_layout.c:499` | `static void test_float_insets_never_starve_the_line(void **state)` |
| `test_float_insets_right` | function | `tests/test_flex_layout.c:474` | `static void test_float_insets_right(void **state)` |
| `test_float_pack_edges` | function | `tests/test_flex_layout.c:541` | `static void test_float_pack_edges(void **state)` |
| `test_float_pack_left` | function | `tests/test_flex_layout.c:311` | `static void test_float_pack_left(void **state)` |
| `test_float_pack_left_and_right` | function | `tests/test_flex_layout.c:322` | `static void test_float_pack_left_and_right(void **state)` |
| `test_float_pack_m_errors` | function | `tests/test_flex_layout.c:422` | `static void test_float_pack_m_errors(void **state)` |
| `test_float_pack_m_positive_margin_widens` | function | `tests/test_flex_layout.c:390` | `static void test_float_pack_m_positive_margin_widens(void **state)` |
| `test_float_pack_m_right_float_negative_margin` | function | `tests/test_flex_layout.c:406` | `static void test_float_pack_m_right_float_negative_margin(void **state)` |
| `test_float_pack_m_zero_margins_match_wrap` | function | `tests/test_flex_layout.c:370` | `static void test_float_pack_m_zero_margins_match_wrap(void **state)` |
| `test_float_pack_two_right` | function | `tests/test_flex_layout.c:334` | `static void test_float_pack_two_right(void **state)` |
| `test_float_pack_wrap_errors` | function | `tests/test_flex_layout.c:617` | `static void test_float_pack_wrap_errors(void **state)` |
| `test_float_pack_wrap_fits_matches_v1` | function | `tests/test_flex_layout.c:571` | `static void test_float_pack_wrap_fits_matches_v1(void **state)` |
| `test_float_pack_wrap_full_width_stack` | function | `tests/test_flex_layout.c:557` | `static void test_float_pack_wrap_full_width_stack(void **state)` |
| `test_float_pack_wrap_partial` | function | `tests/test_flex_layout.c:594` | `static void test_float_pack_wrap_partial(void **state)` |
| `test_gap_start` | function | `tests/test_flex_layout.c:68` | `static void test_gap_start(void **state)` |
| `test_grid_cell` | function | `tests/test_flex_layout.c:187` | `static void test_grid_cell(void **state)` |
| `test_grid_columns` | function | `tests/test_flex_layout.c:158` | `static void test_grid_columns(void **state)` |
| `test_grid_columns_edges` | function | `tests/test_flex_layout.c:177` | `static void test_grid_columns_edges(void **state)` |
| `test_grid_columns_too_narrow_clamps_to_zero` | function | `tests/test_flex_layout.c:170` | `static void test_grid_columns_too_narrow_clamps_to_zero(void **state)` |
| `test_grid_place_explicit_out_of_range_clamps` | function | `tests/test_flex_layout.c:927` | `static void test_grid_place_explicit_out_of_range_clamps(void **state)` |
| `test_grid_place_null_fixed_is_unchanged` | function | `tests/test_flex_layout.c:915` | `static void test_grid_place_null_fixed_is_unchanged(void **state)` |
| `test_grid_place_rowspan` | function | `tests/test_flex_layout.c:294` | `static void test_grid_place_rowspan(void **state)` |
| `test_grid_place_span_basic` | function | `tests/test_flex_layout.c:255` | `static void test_grid_place_span_basic(void **state)` |
| `test_grid_place_span_clamps_and_defaults` | function | `tests/test_flex_layout.c:278` | `static void test_grid_place_span_clamps_and_defaults(void **state)` |
| `test_grid_place_span_wraps_when_it_does_not_fit` | function | `tests/test_flex_layout.c:266` | `static void test_grid_place_span_wraps_when_it_does_not_fit(void **state)` |
| `test_grid_weighted_all_auto_matches_equal` | function | `tests/test_flex_layout.c:222` | `static void test_grid_weighted_all_auto_matches_equal(void **state)` |
| `test_grid_weighted_errors` | function | `tests/test_flex_layout.c:245` | `static void test_grid_weighted_errors(void **state)` |
| `test_grid_weighted_fixed_overflow_zeroes_fr` | function | `tests/test_flex_layout.c:235` | `static void test_grid_weighted_fixed_overflow_zeroes_fr(void **state)` |
| `test_grid_weighted_fixed_px_reserved_first` | function | `tests/test_flex_layout.c:210` | `static void test_grid_weighted_fixed_px_reserved_first(void **state)` |
| `test_grid_weighted_fr` | function | `tests/test_flex_layout.c:198` | `static void test_grid_weighted_fr(void **state)` |
| `test_grow_equal` | function | `tests/test_flex_layout.c:31` | `static void test_grow_equal(void **state)` |
| `test_grow_weighted` | function | `tests/test_flex_layout.c:40` | `static void test_grow_weighted(void **state)` |
| `test_justify_center` | function | `tests/test_flex_layout.c:77` | `static void test_justify_center(void **state)` |
| `test_justify_end` | function | `tests/test_flex_layout.c:86` | `static void test_justify_end(void **state)` |
| `test_justify_name` | function | `tests/test_flex_layout.c:626` | `static void test_justify_name(void **state)` |
| `test_justify_space_around` | function | `tests/test_flex_layout.c:104` | `static void test_justify_space_around(void **state)` |
| `test_justify_space_between` | function | `tests/test_flex_layout.c:95` | `static void test_justify_space_between(void **state)` |
| `test_justify_space_evenly` | function | `tests/test_flex_layout.c:113` | `static void test_justify_space_evenly(void **state)` |
| `test_multicol_used_counts` | function | `tests/test_flex_layout.c:669` | `static void test_multicol_used_counts(void **state)` |
| `test_multicol_used_edges` | function | `tests/test_flex_layout.c:706` | `static void test_multicol_used_edges(void **state)` |
| `test_negative_fields_clamped` | function | `tests/test_flex_layout.c:131` | `static void test_negative_fields_clamped(void **state)` |
| `test_shrink_equal` | function | `tests/test_flex_layout.c:49` | `static void test_shrink_equal(void **state)` |
| `test_shrink_with_min_clamp` | function | `tests/test_flex_layout.c:58` | `static void test_shrink_with_min_clamp(void **state)` |
| `test_space_between_single_item_is_start` | function | `tests/test_flex_layout.c:123` | `static void test_space_between_single_item_is_start(void **state)` |
| `to` | function | `tests/test_flex_layout.c:269` | `* jumps to (1,0);` |
| `main` | function | `tests/test_form.c:207` | `int main(void)` |
| `test_block_foreign_scheme` | function | `tests/test_form.c:155` | `static void test_block_foreign_scheme(void **state)` |
| `test_block_http_downgrade` | function | `tests/test_form.c:145` | `static void test_block_http_downgrade(void **state)` |
| `test_block_null_field_name` | function | `tests/test_form.c:183` | `static void test_block_null_field_name(void **state)` |
| `test_block_relative_action_on_local_base` | function | `tests/test_form.c:164` | `static void test_block_relative_action_on_local_base(void **state)` |
| `test_block_too_many_fields` | function | `tests/test_form.c:173` | `static void test_block_too_many_fields(void **state)` |
| `test_build_null_args` | function | `tests/test_form.c:192` | `static void test_build_null_args(void **state)` |
| `test_encode_basic` | function | `tests/test_form.c:24` | `static void test_encode_basic(void **state)` |
| `test_encode_empty_and_nameless` | function | `tests/test_form.c:51` | `static void test_encode_empty_and_nameless(void **state)` |
| `test_encode_null_args` | function | `tests/test_form.c:67` | `static void test_encode_null_args(void **state)` |
| `test_encode_overflow_fails_closed` | function | `tests/test_form.c:59` | `static void test_encode_overflow_fails_closed(void **state)` |
| `test_encode_space_and_reserved` | function | `tests/test_form.c:34` | `static void test_encode_space_and_reserved(void **state)` |
| `test_encode_unreserved_kept` | function | `tests/test_form.c:43` | `static void test_encode_unreserved_kept(void **state)` |
| `test_get_absolute_https_action_ignores_base` | function | `tests/test_form.c:89` | `static void test_get_absolute_https_action_ignores_base(void **state)` |
| `test_get_action_cleaned_of_whitespace` | function | `tests/test_form.c:119` | `static void test_get_action_cleaned_of_whitespace(void **state)` |
| `test_get_empty_action_submits_to_base` | function | `tests/test_form.c:100` | `static void test_get_empty_action_submits_to_base(void **state)` |
| `test_get_no_fields_still_navigates` | function | `tests/test_form.c:199` | `static void test_get_no_fields_still_navigates(void **state)` |
| `test_get_relative_action_on_https_base` | function | `tests/test_form.c:78` | `static void test_get_relative_action_on_https_base(void **state)` |
| `test_get_replaces_existing_query` | function | `tests/test_form.c:109` | `static void test_get_replaces_existing_query(void **state)` |
| `test_post_builds_body` | function | `tests/test_form.c:130` | `static void test_post_builds_body(void **state)` |
| `main` | function | `tests/test_frame_clock.c:53` | `int main(void)` |
| `test_null_safe` | function | `tests/test_frame_clock.c:45` | `static void test_null_safe(void **state)` |
| `test_set_active_and_needs_tick` | function | `tests/test_frame_clock.c:23` | `static void test_set_active_and_needs_tick(void **state)` |
| `test_set_active_twice` | function | `tests/test_frame_clock.c:36` | `static void test_set_active_twice(void **state)` |
| `main` | function | `tests/test_freebug.c:228` | `int main(void)` |
| `test_count_cap_fails_closed` | function | `tests/test_freebug.c:59` | `static void test_count_cap_fails_closed(void **state)` |
| `test_empty_and_null_text` | function | `tests/test_freebug.c:46` | `static void test_empty_and_null_text(void **state)` |
| `test_entry_truncated_not_dropped` | function | `tests/test_freebug.c:75` | `static void test_entry_truncated_not_dropped(void **state)` |
| `test_free_idempotent` | function | `tests/test_freebug.c:161` | `static void test_free_idempotent(void **state)` |
| `test_level_clamped` | function | `tests/test_freebug.c:118` | `static void test_level_clamped(void **state)` |
| `test_level_name` | function | `tests/test_freebug.c:129` | `static void test_level_name(void **state)` |
| `test_push_and_read` | function | `tests/test_freebug.c:21` | `static void test_push_and_read(void **state)` |
| `test_push_loc_file_truncated` | function | `tests/test_freebug.c:214` | `static void test_push_loc_file_truncated(void **state)` |
| `test_push_loc_null_file_and_negative_nums` | function | `tests/test_freebug.c:197` | `static void test_push_loc_null_file_and_negative_nums(void **state)` |
| `test_push_loc_records_location` | function | `tests/test_freebug.c:175` | `static void test_push_loc_records_location(void **state)` |
| `test_reset_reuses_and_no_leak` | function | `tests/test_freebug.c:140` | `static void test_reset_reuses_and_no_leak(void **state)` |
| `test_total_bytes_cap_fails_closed` | function | `tests/test_freebug.c:93` | `static void test_total_bytes_cap_fails_closed(void **state)` |
| `ERR_FILE` | macro | `tests/test_freedom.c:28` | `#define ERR_FILE` |
| `FREEDOM_BIN` | macro | `tests/test_freedom.c:26` | `#define FREEDOM_BIN` |
| `OUT_FILE` | macro | `tests/test_freedom.c:27` | `#define OUT_FILE` |
| `_POSIX_C_SOURCE` | macro | `tests/test_freedom.c:11` | `#define _POSIX_C_SOURCE` |
| `ballooned` | function | `tests/test_freedom.c:1526` | `* ballooned (body + wrapper re-opened per child) and the LAST wrapper piece
 * became the contain...` |
| `band` | function | `tests/test_freedom.c:2034` | `* band (which already recurses into nested containers) owns it. */
static void test_dump_layout_c...` |
| `blend` | function | `tests/test_freedom.c:491` | `* not some other blend (double-composited or wrong alpha). */
static void test_download_png_group...` |
| `blend` | function | `tests/test_freedom.c:1185` | `* visibly different from either input color or an OVER blend (which would show
 * opaque blue). E...` |
| `bottom` | function | `tests/test_freedom.c:1818` | `* at the page bottom (the grey-stripe bug had npositioned pushing it away). */ /* (Each sized float now has a box of its` |
| `cleanup_files` | function | `tests/test_freedom.c:84` | `static void cleanup_files(void)` |
| `ink_width` | function | `tests/test_freedom.c:630` | `static double ink_width(const char *html)` |
| `is_pdf_file` | function | `tests/test_freedom.c:64` | `static int is_pdf_file(const char *path)` |
| `is_png_file` | function | `tests/test_freedom.c:74` | `static int is_png_file(const char *path)` |
| `main` | function | `tests/test_freedom.c:2523` | `int main(void)` |
| `markup` | function | `tests/test_freedom.c:1315` | `* against an unrotated control render of the identical markup (a 50-char-wide box
 * at x:[24,975...` |
| `markup` | function | `tests/test_freedom.c:1374` | `* unscaled control render of the identical markup (box y:[24,49] at x=500,
 * center y~36.5): y=2...` |
| `read_file_all` | function | `tests/test_freedom.c:90` | `static uint8_t *read_file_all(const char *path, size_t *out_len)` |
| `rows` | function | `tests/test_freedom.c:992` | `* rows (the bug) made it several times taller. */ assert_true(px.height < 60);` |
| `run_freedom` | function | `tests/test_freedom.c:30` | `static int run_freedom(const char *arg, char *out, size_t out_size, int *exit_status)` |
| `run_freedom_raw` | function | `tests/test_freedom.c:52` | `static int run_freedom_raw(const char *args, int *exit_status)` |
| `test_absolute_font_size_lands_exact` | function | `tests/test_freedom.c:677` | `static void test_absolute_font_size_lands_exact(void **state)` |
| `test_absolute_span_honours_right_bottom` | function | `tests/test_freedom.c:789` | `static void test_absolute_span_honours_right_bottom(void **state)` |
| `test_author_can_unbold_a_heading` | function | `tests/test_freedom.c:770` | `static void test_author_can_unbold_a_heading(void **state)` |
| `test_author_font_size_on_heading_replaces_ua_scale` | function | `tests/test_freedom.c:695` | `static void test_author_font_size_on_heading_replaces_ua_scale(void **state)` |
| `test_download_pdf_local` | function | `tests/test_freedom.c:246` | `static void test_download_pdf_local(void **state)` |
| `test_download_pdf_requires_path` | function | `tests/test_freedom.c:272` | `static void test_download_pdf_requires_path(void **state)` |
| `test_download_png_absolute_shrinks_and_anchors_right` | function | `tests/test_freedom.c:556` | `static void test_download_png_absolute_shrinks_and_anchors_right(void **state)` |
| `test_download_png_flex_container_paints_one_band` | function | `tests/test_freedom.c:2418` | `static void test_download_png_flex_container_paints_one_band(void **state)` |
| `test_download_png_gradient_box_text_keeps_gradient` | function | `tests/test_freedom.c:2393` | `static void test_download_png_gradient_box_text_keeps_gradient(void **state)` |
| `test_download_png_images_local` | function | `tests/test_freedom.c:313` | `static void test_download_png_images_local(void **state)` |
| `test_download_png_inline_block_flows_in_line` | function | `tests/test_freedom.c:938` | `static void test_download_png_inline_block_flows_in_line(void **state)` |
| `test_download_png_inline_block_shrinks_and_centers` | function | `tests/test_freedom.c:2438` | `static void test_download_png_inline_block_shrinks_and_centers(void **state)` |
| `test_download_png_inline_svg_path_and_drops_image` | function | `tests/test_freedom.c:2482` | `static void test_download_png_inline_svg_path_and_drops_image(void **state)` |
| `test_download_png_line_height_zero_does_not_shrink_line` | function | `tests/test_freedom.c:1054` | `static void test_download_png_line_height_zero_does_not_shrink_line(void **state)` |
| `test_download_png_local` | function | `tests/test_freedom.c:281` | `static void test_download_png_local(void **state)` |
| `test_download_png_negative_zindex_paints_behind_inflow` | function | `tests/test_freedom.c:390` | `static void test_download_png_negative_zindex_paints_behind_inflow(void **state)` |
| `test_download_png_nested_flex_lays_out_on_one_row` | function | `tests/test_freedom.c:859` | `static void test_download_png_nested_flex_lays_out_on_one_row(void **state)` |
| `test_download_png_positioned_overflow_clips_own_content` | function | `tests/test_freedom.c:443` | `static void test_download_png_positioned_overflow_clips_own_content(void **state)` |
| `test_download_png_requires_path` | function | `tests/test_freedom.c:374` | `static void test_download_png_requires_path(void **state)` |
| `test_dump_console_shows_output_and_error` | function | `tests/test_freedom.c:1433` | `static void test_dump_console_shows_output_and_error(void **state)` |
| `test_dump_dom_prints_render_tree` | function | `tests/test_freedom.c:1493` | `static void test_dump_dom_prints_render_tree(void **state)` |
| `test_dump_layout_band_flushes_line_before_clear` | function | `tests/test_freedom.c:2103` | `static void test_dump_layout_band_flushes_line_before_clear(void **state)` |
| `test_dump_layout_flex_auto_margin_push_right` | function | `tests/test_freedom.c:2143` | `static void test_dump_layout_flex_auto_margin_push_right(void **state)` |
| `test_dump_layout_flex_item_sibling_boxes` | function | `tests/test_freedom.c:1636` | `static void test_dump_layout_flex_item_sibling_boxes(void **state)` |
| `test_dump_layout_inline_box_second_run_stays` | function | `tests/test_freedom.c:2005` | `static void test_dump_layout_inline_box_second_run_stays(void **state)` |
| `test_dump_layout_line_opening_image_is_inline` | function | `tests/test_freedom.c:2077` | `static void test_dump_layout_line_opening_image_is_inline(void **state)` |
| `test_dump_layout_nested_column_takes_max` | function | `tests/test_freedom.c:2186` | `static void test_dump_layout_nested_column_takes_max(void **state)` |
| `test_dump_layout_oof_subtree_real_layout` | function | `tests/test_freedom.c:1595` | `static void test_dump_layout_oof_subtree_real_layout(void **state)` |
| `test_dump_layout_pulled_rail_single_margin` | function | `tests/test_freedom.c:1838` | `static void test_dump_layout_pulled_rail_single_margin(void **state)` |
| `test_dump_layout_root_box_survives_replaced_run` | function | `tests/test_freedom.c:1745` | `static void test_dump_layout_root_box_survives_replaced_run(void **state)` |
| `test_dump_layout_row_nested_in_column` | function | `tests/test_freedom.c:1954` | `static void test_dump_layout_row_nested_in_column(void **state)` |
| `test_dump_layout_sticky_footer` | function | `tests/test_freedom.c:1710` | `static void test_dump_layout_sticky_footer(void **state)` |
| `test_dump_timings_prints_stages` | function | `tests/test_freedom.c:2498` | `static void test_dump_timings_prints_stages(void **state)` |
| `test_heading_colour_matches_body_text` | function | `tests/test_freedom.c:715` | `static void test_heading_colour_matches_body_text(void **state)` |
| `test_headless_js_measures_real_geometry` | function | `tests/test_freedom.c:161` | `static void test_headless_js_measures_real_geometry(void **state)` |
| `test_headless_timer_navigation_followed` | function | `tests/test_freedom.c:187` | `static void test_headless_timer_navigation_followed(void **state)` |
| `test_help` | function | `tests/test_freedom.c:107` | `static void test_help(void **state)` |
| `test_inline_run_boundary_collapses_runs_of_space` | function | `tests/test_freedom.c:1032` | `static void test_inline_run_boundary_collapses_runs_of_space(void **state)` |
| `test_inline_run_boundary_does_not_invent_space` | function | `tests/test_freedom.c:1011` | `static void test_inline_run_boundary_does_not_invent_space(void **state)` |
| `test_local_form_renders_inputs` | function | `tests/test_freedom.c:210` | `static void test_local_form_renders_inputs(void **state)` |
| `test_local_html` | function | `tests/test_freedom.c:135` | `static void test_local_html(void **state)` |
| `test_missing_file` | function | `tests/test_freedom.c:236` | `static void test_missing_file(void **state)` |
| `test_no_args` | function | `tests/test_freedom.c:125` | `static void test_no_args(void **state)` |
| `test_no_dump_console_without_flag` | function | `tests/test_freedom.c:1468` | `static void test_no_dump_console_without_flag(void **state)` |
| `test_rejects_http_url` | function | `tests/test_freedom.c:2235` | `static void test_rejects_http_url(void **state)` |
| `test_version` | function | `tests/test_freedom.c:116` | `static void test_version(void **state)` |
| `white` | function | `tests/test_freedom.c:2297` | `* and not white (the old behaviour where only text rows got background fills). */
static void tes...` |
| `main` | function | `tests/test_hls.c:219` | `int main(void)` |
| `test_empty_m3u8_is_ok` | function | `tests/test_hls.c:22` | `static void test_empty_m3u8_is_ok(void **state)` |
| `test_handles_windows_line_endings` | function | `tests/test_hls.c:209` | `static void test_handles_windows_line_endings(void **state)` |
| `test_multi_variant_collects_all` | function | `tests/test_hls.c:114` | `static void test_multi_variant_collects_all(void **state)` |
| `test_multiple_segments` | function | `tests/test_hls.c:46` | `static void test_multiple_segments(void **state)` |
| `test_not_m3u8_returns_parse_error` | function | `tests/test_hls.c:15` | `static void test_not_m3u8_returns_parse_error(void **state)` |
| `test_resolve_url_absolute_passthrough` | function | `tests/test_hls.c:180` | `static void test_resolve_url_absolute_passthrough(void **state)` |
| `test_resolve_url_deep_relative` | function | `tests/test_hls.c:200` | `static void test_resolve_url_deep_relative(void **state)` |
| `test_resolve_url_relative` | function | `tests/test_hls.c:190` | `static void test_resolve_url_relative(void **state)` |
| `test_select_variant_empty_returns_error` | function | `tests/test_hls.c:170` | `static void test_select_variant_empty_returns_error(void **state)` |
| `test_select_variant_highest_bandwidth_no_limit` | function | `tests/test_hls.c:135` | `static void test_select_variant_highest_bandwidth_no_limit(void **state)` |
| `test_select_variant_respects_max_dimensions` | function | `tests/test_hls.c:152` | `static void test_select_variant_respects_max_dimensions(void **state)` |
| `test_single_segment` | function | `tests/test_hls.c:31` | `static void test_single_segment(void **state)` |
| `test_target_duration_is_parsed` | function | `tests/test_hls.c:68` | `static void test_target_duration_is_parsed(void **state)` |
| `test_variant_playlist_collects_variants` | function | `tests/test_hls.c:97` | `static void test_variant_playlist_collects_variants(void **state)` |
| `test_variant_playlist_detected` | function | `tests/test_hls.c:83` | `static void test_variant_playlist_detected(void **state)` |
| `main` | function | `tests/test_hostblock.c:266` | `int main(void)` |
| `test_allow_wins_and_covers_subdomains` | function | `tests/test_hostblock.c:210` | `static void test_allow_wins_and_covers_subdomains(void **state)` |
| `test_bare_domain_per_line` | function | `tests/test_hostblock.c:73` | `static void test_bare_domain_per_line(void **state)` |
| `test_block_covers_subdomains` | function | `tests/test_hostblock.c:197` | `static void test_block_covers_subdomains(void **state)` |
| `test_check_fail_open_edges` | function | `tests/test_hostblock.c:252` | `static void test_check_fail_open_edges(void **state)` |
| `test_comments_and_blanks` | function | `tests/test_hostblock.c:83` | `static void test_comments_and_blanks(void **state)` |
| `test_count_null_set` | function | `tests/test_hostblock.c:37` | `static void test_count_null_set(void **state)` |
| `test_dedup_and_accumulate` | function | `tests/test_hostblock.c:174` | `static void test_dedup_and_accumulate(void **state)` |
| `test_free_null_idempotent` | function | `tests/test_hostblock.c:32` | `static void test_free_null_idempotent(void **state)` |
| `test_hosts_line_drops_ip` | function | `tests/test_hostblock.c:55` | `static void test_hosts_line_drops_ip(void **state)` |
| `test_invalid_tokens_skipped` | function | `tests/test_hostblock.c:139` | `static void test_invalid_tokens_skipped(void **state)` |
| `test_is_allowlisted` | function | `tests/test_hostblock.c:231` | `static void test_is_allowlisted(void **state)` |
| `test_lists_independent` | function | `tests/test_hostblock.c:185` | `static void test_lists_independent(void **state)` |
| `test_load_null_args` | function | `tests/test_hostblock.c:45` | `static void test_load_null_args(void **state)` |
| `test_lowercased` | function | `tests/test_hostblock.c:118` | `static void test_lowercased(void **state)` |
| `test_multiple_tokens_per_line` | function | `tests/test_hostblock.c:99` | `static void test_multiple_tokens_per_line(void **state)` |
| `test_no_lists_allows` | function | `tests/test_hostblock.c:224` | `static void test_no_lists_allows(void **state)` |
| `test_no_trailing_newline` | function | `tests/test_hostblock.c:107` | `static void test_no_trailing_newline(void **state)` |
| `test_oversize_token_skipped` | function | `tests/test_hostblock.c:155` | `static void test_oversize_token_skipped(void **state)` |
| `test_trailing_dot_trimmed` | function | `tests/test_hostblock.c:128` | `static void test_trailing_dot_trimmed(void **state)` |
| `test_underscore_and_hyphen_valid` | function | `tests/test_hostblock.c:166` | `static void test_underscore_and_hyphen_valid(void **state)` |
| `test_various_ip_tokens_ignored` | function | `tests/test_hostblock.c:64` | `static void test_various_ip_tokens_ignored(void **state)` |
| `main` | function | `tests/test_hostedit.c:114` | `int main(void)` |
| `test_make_line_lowercases` | function | `tests/test_hostedit.c:11` | `static void test_make_line_lowercases(void **state)` |
| `test_make_line_null_and_range` | function | `tests/test_hostedit.c:47` | `static void test_make_line_null_and_range(void **state)` |
| `test_make_line_plain_host` | function | `tests/test_hostedit.c:18` | `static void test_make_line_plain_host(void **state)` |
| `test_make_line_rejects_bad_labels` | function | `tests/test_hostedit.c:36` | `static void test_make_line_rejects_bad_labels(void **state)` |
| `test_make_line_rejects_path_scheme_garbage` | function | `tests/test_hostedit.c:25` | `static void test_make_line_rejects_path_scheme_garbage(void **state)` |
| `test_make_line_single_label_ok` | function | `tests/test_hostedit.c:56` | `static void test_make_line_single_label_ok(void **state)` |
| `test_suggest_case_insensitive_and_dedup` | function | `tests/test_hostedit.c:92` | `static void test_suggest_case_insensitive_and_dedup(void **state)` |
| `test_suggest_empty_query_and_cap` | function | `tests/test_hostedit.c:101` | `static void test_suggest_empty_query_and_cap(void **state)` |
| `test_suggest_prefix_first` | function | `tests/test_hostedit.c:76` | `static void test_suggest_prefix_first(void **state)` |
| `test_text_has_host` | function | `tests/test_hostedit.c:63` | `static void test_text_has_host(void **state)` |
| `LIT` | macro | `tests/test_html_parse.c:21` | `#define LIT(s)` |
| `main` | function | `tests/test_html_parse.c:507` | `int main(void)` |
| `test_config_default_is_secure` | function | `tests/test_html_parse.c:37` | `static void test_config_default_is_secure(void **state)` |
| `test_event_handlers_kept_when_disabled` | function | `tests/test_html_parse.c:150` | `static void test_event_handlers_kept_when_disabled(void **state)` |
| `test_event_handlers_stripped_by_default` | function | `tests/test_html_parse.c:141` | `static void test_event_handlers_stripped_by_default(void **state)` |
| `test_extract_script_list_empty` | function | `tests/test_html_parse.c:263` | `static void test_extract_script_list_empty(void **state)` |
| `test_extract_script_list_external_semantics` | function | `tests/test_html_parse.c:200` | `static void test_extract_script_list_external_semantics(void **state)` |
| `test_extract_script_list_module_flags` | function | `tests/test_html_parse.c:454` | `static void test_extract_script_list_module_flags(void **state)` |
| `test_extract_script_list_skips_non_js_type` | function | `tests/test_html_parse.c:234` | `static void test_extract_script_list_skips_non_js_type(void **state)` |
| `test_extract_stylesheets_basic` | function | `tests/test_html_parse.c:310` | `static void test_extract_stylesheets_basic(void **state)` |
| `test_extract_stylesheets_caps` | function | `tests/test_html_parse.c:404` | `static void test_extract_stylesheets_caps(void **state)` |
| `test_extract_stylesheets_none_and_null` | function | `tests/test_html_parse.c:387` | `static void test_extract_stylesheets_none_and_null(void **state)` |
| `test_extract_stylesheets_rel_tokens` | function | `tests/test_html_parse.c:337` | `static void test_extract_stylesheets_rel_tokens(void **state)` |
| `test_free_null_and_double` | function | `tests/test_html_parse.c:443` | `static void test_free_null_and_double(void **state)` |
| `test_parse_malformed_does_not_crash` | function | `tests/test_html_parse.c:431` | `static void test_parse_malformed_does_not_crash(void **state)` |
| `test_parse_rejects_null_args` | function | `tests/test_html_parse.c:72` | `static void test_parse_rejects_null_args(void **state)` |
| `test_parse_rejects_oversize` | function | `tests/test_html_parse.c:80` | `static void test_parse_rejects_oversize(void **state)` |
| `test_parse_simple_document` | function | `tests/test_html_parse.c:91` | `static void test_parse_simple_document(void **state)` |
| `test_scripts_kept_when_disabled` | function | `tests/test_html_parse.c:131` | `static void test_scripts_kept_when_disabled(void **state)` |
| `test_scripts_stripped_by_default` | function | `tests/test_html_parse.c:116` | `static void test_scripts_stripped_by_default(void **state)` |
| `test_validate_accepts_within_cap` | function | `tests/test_html_parse.c:64` | `static void test_validate_accepts_within_cap(void **state)` |
| `test_validate_rejects_empty` | function | `tests/test_html_parse.c:51` | `static void test_validate_rejects_empty(void **state)` |
| `test_validate_rejects_null` | function | `tests/test_html_parse.c:45` | `static void test_validate_rejects_null(void **state)` |
| `test_validate_rejects_oversize` | function | `tests/test_html_parse.c:57` | `static void test_validate_rejects_oversize(void **state)` |
| `main` | function | `tests/test_image_decode.c:492` | `int main(void)` |
| `px` | function | `tests/test_image_decode.c:65` | `static uint32_t px(const img_pixels *p, uint32_t x, uint32_t y)` |
| `test_decode_dimensions_and_stride` | function | `tests/test_image_decode.c:166` | `static void test_decode_dimensions_and_stride(void **state)` |
| `test_decode_dispatch_rejects_unknown` | function | `tests/test_image_decode.c:279` | `static void test_decode_dispatch_rejects_unknown(void **state)` |
| `test_decode_dispatch_routes_gif` | function | `tests/test_image_decode.c:430` | `static void test_decode_dispatch_routes_gif(void **state)` |
| `test_decode_dispatch_routes_jpeg_and_png` | function | `tests/test_image_decode.c:267` | `static void test_decode_dispatch_routes_jpeg_and_png(void **state)` |
| `test_decode_dispatch_routes_webp` | function | `tests/test_image_decode.c:483` | `static void test_decode_dispatch_routes_webp(void **state)` |
| `test_decode_gif_animated_first_frame` | function | `tests/test_image_decode.c:405` | `static void test_decode_gif_animated_first_frame(void **state)` |
| `test_decode_gif_fail_closed` | function | `tests/test_image_decode.c:414` | `static void test_decode_gif_fail_closed(void **state)` |
| `test_decode_gif_interlaced` | function | `tests/test_image_decode.c:390` | `static void test_decode_gif_interlaced(void **state)` |
| `test_decode_gif_pixels` | function | `tests/test_image_decode.c:363` | `static void test_decode_gif_pixels(void **state)` |
| `test_decode_gif_transparency` | function | `tests/test_image_decode.c:378` | `static void test_decode_gif_transparency(void **state)` |
| `test_decode_jpeg_dimensions_and_alpha` | function | `tests/test_image_decode.c:244` | `static void test_decode_jpeg_dimensions_and_alpha(void **state)` |
| `test_decode_jpeg_null_args` | function | `tests/test_image_decode.c:302` | `static void test_decode_jpeg_null_args(void **state)` |
| `test_decode_jpeg_rejects_non_jpeg` | function | `tests/test_image_decode.c:295` | `static void test_decode_jpeg_rejects_non_jpeg(void **state)` |
| `test_decode_jpeg_rejects_truncated` | function | `tests/test_image_decode.c:287` | `static void test_decode_jpeg_rejects_truncated(void **state)` |
| `test_decode_null_args` | function | `tests/test_image_decode.c:210` | `static void test_decode_null_args(void **state)` |
| `test_decode_pixels_premultiplied` | function | `tests/test_image_decode.c:178` | `static void test_decode_pixels_premultiplied(void **state)` |
| `test_decode_rejects_non_png` | function | `tests/test_image_decode.c:190` | `static void test_decode_rejects_non_png(void **state)` |
| `test_decode_rejects_truncated` | function | `tests/test_image_decode.c:200` | `static void test_decode_rejects_truncated(void **state)` |
| `test_decode_webp_dimensions_and_pixels` | function | `tests/test_image_decode.c:454` | `static void test_decode_webp_dimensions_and_pixels(void **state)` |
| `test_decode_webp_fail_closed` | function | `tests/test_image_decode.c:471` | `static void test_decode_webp_fail_closed(void **state)` |
| `test_dimensions_from_ihdr` | function | `tests/test_image_decode.c:89` | `static void test_dimensions_from_ihdr(void **state)` |
| `test_dimensions_non_png` | function | `tests/test_image_decode.c:104` | `static void test_dimensions_non_png(void **state)` |
| `test_dimensions_null` | function | `tests/test_image_decode.c:111` | `static void test_dimensions_null(void **state)` |
| `test_dimensions_ok_bounds` | function | `tests/test_image_decode.c:120` | `static void test_dimensions_ok_bounds(void **state)` |
| `test_dimensions_truncated` | function | `tests/test_image_decode.c:97` | `static void test_dimensions_truncated(void **state)` |
| `test_fit_degenerate` | function | `tests/test_image_decode.c:154` | `static void test_fit_degenerate(void **state)` |
| `test_fit_landscape_into_square` | function | `tests/test_image_decode.c:136` | `static void test_fit_landscape_into_square(void **state)` |
| `test_fit_portrait_into_box` | function | `tests/test_image_decode.c:145` | `static void test_fit_portrait_into_box(void **state)` |
| `test_format_name` | function | `tests/test_image_decode.c:227` | `static void test_format_name(void **state)` |
| `test_pixels_free_idempotent` | function | `tests/test_image_decode.c:218` | `static void test_pixels_free_idempotent(void **state)` |
| `test_sniff_gif` | function | `tests/test_image_decode.c:356` | `static void test_sniff_gif(void **state)` |
| `test_sniff_jpeg` | function | `tests/test_image_decode.c:236` | `static void test_sniff_jpeg(void **state)` |
| `test_sniff_png` | function | `tests/test_image_decode.c:75` | `static void test_sniff_png(void **state)` |
| `test_sniff_unsupported` | function | `tests/test_image_decode.c:80` | `static void test_sniff_unsupported(void **state)` |
| `test_sniff_webp` | function | `tests/test_image_decode.c:448` | `static void test_sniff_webp(void **state)` |
| `DOC` | macro | `tests/test_import_map.c:36` | `#define DOC` |
| `expect_res` | function | `tests/test_import_map.c:38` | `static void expect_res(const im_map *m, const char *base, const char *spec, const char *want)` |
| `main` | function | `tests/test_import_map.c:123` | `int main(void)` |
| `test_exact_and_prefix_imports` | function | `tests/test_import_map.c:48` | `static void test_exact_and_prefix_imports(void **state)` |
| `test_invalid_input_yields_empty_map` | function | `tests/test_import_map.c:102` | `static void test_invalid_input_yields_empty_map(void **state)` |
| `test_json_escapes_and_ignored_members` | function | `tests/test_import_map.c:90` | `static void test_json_escapes_and_ignored_members(void **state)` |
| `test_scopes_win_by_longest_prefix` | function | `tests/test_import_map.c:74` | `static void test_scopes_win_by_longest_prefix(void **state)` |
| `tres` | function | `tests/test_import_map.c:17` | `static int tres(void *ctx, const char *base, const char *ref, char *out, size_t outsz)` |
| `assert_float_equal` | function | `tests/test_interp.c:64` | `assert_float_equal(ip_ease(0.0, &(ip_ease_fn)` |
| `assert_float_equal` | function | `tests/test_interp.c:66` | `assert_float_equal(ip_ease(0.0, &(ip_ease_fn)` |
| `linear_ease` | function | `tests/test_interp.c:258` | `static ip_ease_fn linear_ease(void)` |
| `main` | function | `tests/test_interp.c:474` | `int main(void)` |
| `test_anim_active_linear` | function | `tests/test_interp.c:292` | `static void test_anim_active_linear(void **state)` |
| `test_anim_alternate` | function | `tests/test_interp.c:393` | `static void test_anim_alternate(void **state)` |
| `test_anim_alternate_reverse` | function | `tests/test_interp.c:410` | `static void test_anim_alternate_reverse(void **state)` |
| `test_anim_delay_backwards_fill` | function | `tests/test_interp.c:278` | `static void test_anim_delay_backwards_fill(void **state)` |
| `test_anim_delay_no_fill` | function | `tests/test_interp.c:263` | `static void test_anim_delay_no_fill(void **state)` |
| `test_anim_forwards_fill` | function | `tests/test_interp.c:325` | `static void test_anim_forwards_fill(void **state)` |
| `test_anim_infinite` | function | `tests/test_interp.c:367` | `static void test_anim_infinite(void **state)` |
| `test_anim_negative_dt` | function | `tests/test_interp.c:448` | `static void test_anim_negative_dt(void **state)` |
| `test_anim_no_keyframes` | function | `tests/test_interp.c:436` | `static void test_anim_no_keyframes(void **state)` |
| `test_anim_null_init` | function | `tests/test_interp.c:463` | `static void test_anim_null_init(void **state)` |
| `test_anim_reverse_direction` | function | `tests/test_interp.c:380` | `static void test_anim_reverse_direction(void **state)` |
| `test_anim_single_iteration_done` | function | `tests/test_interp.c:310` | `static void test_anim_single_iteration_done(void **state)` |
| `test_anim_two_iterations` | function | `tests/test_interp.c:338` | `static void test_anim_two_iterations(void **state)` |
| `test_anim_zero_duration` | function | `tests/test_interp.c:423` | `static void test_anim_zero_duration(void **state)` |
| `test_ease_clamp` | function | `tests/test_interp.c:78` | `static void test_ease_clamp(void **state)` |
| `test_ease_ease_in_concave` | function | `tests/test_interp.c:92` | `static void test_ease_ease_in_concave(void **state)` |
| `test_ease_ease_out_convex` | function | `tests/test_interp.c:99` | `static void test_ease_ease_out_convex(void **state)` |
| `test_ease_endpoints` | function | `tests/test_interp.c:31` | `static void test_ease_endpoints(void **state)` |
| `test_ease_monotonic` | function | `tests/test_interp.c:106` | `static void test_ease_monotonic(void **state)` |
| `test_ease_null_fn` | function | `tests/test_interp.c:85` | `static void test_ease_null_fn(void **state)` |
| `test_ease_step_start_end_aliases` | function | `tests/test_interp.c:147` | `static void test_ease_step_start_end_aliases(void **state)` |
| `test_ease_steps_end` | function | `tests/test_interp.c:127` | `static void test_ease_steps_end(void **state)` |
| `test_ease_steps_start` | function | `tests/test_interp.c:138` | `static void test_ease_steps_start(void **state)` |
| `test_interp_dispatches` | function | `tests/test_interp.c:192` | `static void test_interp_dispatches(void **state)` |
| `test_kf_after_last` | function | `tests/test_interp.c:231` | `static void test_kf_after_last(void **state)` |
| `test_kf_before_first` | function | `tests/test_interp.c:225` | `static void test_kf_before_first(void **state)` |
| `test_kf_color_interp` | function | `tests/test_interp.c:247` | `static void test_kf_color_interp(void **state)` |
| `test_kf_exact_match` | function | `tests/test_interp.c:219` | `static void test_kf_exact_match(void **state)` |
| `test_kf_null_or_empty` | function | `tests/test_interp.c:237` | `static void test_kf_null_or_empty(void **state)` |
| `test_kf_three_keyframes` | function | `tests/test_interp.c:212` | `static void test_kf_three_keyframes(void **state)` |
| `test_kf_two_keyframes` | function | `tests/test_interp.c:205` | `static void test_kf_two_keyframes(void **state)` |
| `test_lerp_color_rgb` | function | `tests/test_interp.c:171` | `static void test_lerp_color_rgb(void **state)` |
| `test_lerp_scalar` | function | `tests/test_interp.c:163` | `static void test_lerp_scalar(void **state)` |
| `EXPECT` | macro | `tests/test_js_dom.c:77` | `#define EXPECT(f, src, expected)` |
| `EXPECT` | function | `tests/test_js_dom.c:270` | `EXPECT(f, "typeof (new MutationObserver(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:576` | `EXPECT(f,
        "setTimeout(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:1950` | `EXPECT(f, "['DocumentType','CDATASection','ProcessingInstruction','Window','NamedNodeMap',"
     ...` |
| `EXPECT` | function | `tests/test_js_dom.c:2088` | `EXPECT(f, "function mk(h)` |
| `assert_int_equal` | function | `tests/test_js_dom.c:565` | `assert_int_equal(run(f,
        "window.onload=function()` |
| `bundle` | function | `tests/test_js_dom.c:335` | `* library bundle (DuckDuckGo's l.js "cannot read property createElement of
 * undefined"). This l...` |
| `console_fixture` | function | `tests/test_js_dom.c:759` | `static void console_fixture(hp_document **doc, dom_index **idx, js_context **ctx,
               ...` |
| `console_teardown` | function | `tests/test_js_dom.c:772` | `static void console_teardown(hp_document *doc, dom_index *idx, js_context *ctx,
                 ...` |
| `fake_fetch` | function | `tests/test_js_dom.c:2042` | `static int fake_fetch(void *ctx, const char *method, const char *url, const char *body,
         ...` |
| `fake_net` | struct | `tests/test_js_dom.c:2041` | `` |
| `fixture` | struct | `tests/test_js_dom.c:42` | `` |
| `geom_parent` | function | `tests/test_js_dom.c:1549` | `static dom_node_id geom_parent(void *ctx, dom_node_id n)` |
| `handle_after` | function | `tests/test_js_dom.c:1353` | `static dom_node_id handle_after(fixture *f, const char *src)` |
| `identity` | function | `tests/test_js_dom.c:302` | `* identity (the same one innerWidth and the CSS viewport units use);` |
| `jQuery` | function | `tests/test_js_dom.c:246` | `* page that ships jQuery (Slashdot). The fragment must be complete enough that the
 * detection c...` |
| `js_handle` | function | `tests/test_js_dom.c:1553` | `static dom_node_id js_handle(fixture *f, const char *expr)` |
| `main` | function | `tests/test_js_dom.c:2374` | `int main(void)` |
| `methods` | function | `tests/test_js_dom.c:351` | `* backed by the sealed dom methods (this element's own attributes only). */
static void test_elem...` |
| `persisted` | function | `tests/test_js_dom.c:623` | `* never persisted (process-lifetime only). */
static void test_cookie_jar_enabled_for_trusted_hos...` |
| `pump_ticks` | function | `tests/test_js_dom.c:2144` | `static void pump_ticks(fixture *f, int n)` |
| `run` | function | `tests/test_js_dom.c:73` | `static js_status run(fixture *f, const char *src, js_result *r)` |
| `set_https_location` | function | `tests/test_js_dom.c:659` | `static void set_https_location(fixture *f, const char *url)` |
| `set_loc` | function | `tests/test_js_dom.c:1616` | `static void set_loc(fixture *f, const char *href)` |
| `setup` | function | `tests/test_js_dom.c:49` | `static int setup(void **state)` |
| `teardown` | function | `tests/test_js_dom.c:60` | `static int teardown(void **state)` |
| `test_ambient_apis_do_not_throw` | function | `tests/test_js_dom.c:648` | `static void test_ambient_apis_do_not_throw(void **state)` |
| `test_append_cycle_is_rejected` | function | `tests/test_js_dom.c:553` | `static void test_append_cycle_is_rejected(void **state)` |
| `test_attributes` | function | `tests/test_js_dom.c:130` | `static void test_attributes(void **state)` |
| `test_blur_onblur_fires` | function | `tests/test_js_dom.c:984` | `static void test_blur_onblur_fires(void **state)` |
| `test_by_class_and_tag` | function | `tests/test_js_dom.c:112` | `static void test_by_class_and_tag(void **state)` |
| `test_classlist_backs_class_attr` | function | `tests/test_js_dom.c:222` | `static void test_classlist_backs_class_attr(void **state)` |
| `test_click_add_event_listener_fires` | function | `tests/test_js_dom.c:1201` | `static void test_click_add_event_listener_fires(void **state)` |
| `test_click_install_null_args` | function | `tests/test_js_dom.c:1195` | `static void test_click_install_null_args(void **state)` |
| `test_click_no_handler_allows_default` | function | `tests/test_js_dom.c:1272` | `static void test_click_no_handler_allows_default(void **state)` |
| `test_click_onclick_fires` | function | `tests/test_js_dom.c:1225` | `static void test_click_onclick_fires(void **state)` |
| `test_click_prevent_default` | function | `tests/test_js_dom.c:1249` | `static void test_click_prevent_default(void **state)` |
| `test_console_captures_levels` | function | `tests/test_js_dom.c:798` | `static void test_console_captures_levels(void **state)` |
| `test_console_formats_errors_and_elements` | function | `tests/test_js_dom.c:782` | `static void test_console_formats_errors_and_elements(void **state)` |
| `test_console_null_buffer_is_noop` | function | `tests/test_js_dom.c:847` | `static void test_console_null_buffer_is_noop(void **state)` |
| `test_console_null_ctx` | function | `tests/test_js_dom.c:868` | `static void test_console_null_ctx(void **state)` |
| `test_console_object_and_throwing_tostring` | function | `tests/test_js_dom.c:825` | `static void test_console_object_and_throwing_tostring(void **state)` |
| `test_cookie_and_referrer_leak_nothing` | function | `tests/test_js_dom.c:609` | `static void test_cookie_and_referrer_leak_nothing(void **state)` |
| `test_create_append_renders_in_tree` | function | `tests/test_js_dom.c:487` | `static void test_create_append_renders_in_tree(void **state)` |
| `test_current_script_values_and_methods` | function | `tests/test_js_dom.c:1853` | `static void test_current_script_values_and_methods(void **state)` |
| `test_document_fragment_reparents` | function | `tests/test_js_dom.c:232` | `static void test_document_fragment_reparents(void **state)` |
| `test_document_is_not_io` | function | `tests/test_js_dom.c:478` | `static void test_document_is_not_io(void **state)` |
| `test_document_order` | function | `tests/test_js_dom.c:137` | `static void test_document_order(void **state)` |
| `test_document_shim_present` | function | `tests/test_js_dom.c:175` | `static void test_document_shim_present(void **state)` |
| `test_document_title_set_reflects_in_tree` | function | `tests/test_js_dom.c:438` | `static void test_document_title_set_reflects_in_tree(void **state)` |
| `test_dom_childnode_mixins` | function | `tests/test_js_dom.c:1819` | `static void test_dom_childnode_mixins(void **state)` |
| `test_dom_interface_prototypes` | function | `tests/test_js_dom.c:1831` | `static void test_dom_interface_prototypes(void **state)` |
| `test_dom_ordered_insertion` | function | `tests/test_js_dom.c:1809` | `static void test_dom_ordered_insertion(void **state)` |
| `test_dom_template_content` | function | `tests/test_js_dom.c:1840` | `static void test_dom_template_content(void **state)` |
| `test_element_has_attribute` | function | `tests/test_js_dom.c:529` | `static void test_element_has_attribute(void **state)` |
| `test_element_matches_closest_query_from_js` | function | `tests/test_js_dom.c:196` | `static void test_element_matches_closest_query_from_js(void **state)` |
| `test_element_remove_attribute` | function | `tests/test_js_dom.c:535` | `static void test_element_remove_attribute(void **state)` |
| `test_element_src_href_are_strings` | function | `tests/test_js_dom.c:545` | `static void test_element_src_href_are_strings(void **state)` |
| `test_element_traversal` | function | `tests/test_js_dom.c:213` | `static void test_element_traversal(void **state)` |
| `test_event_add_event_listener_fires` | function | `tests/test_js_dom.c:877` | `static void test_event_add_event_listener_fires(void **state)` |
| `test_event_capture_target_bubble_order` | function | `tests/test_js_dom.c:1376` | `static void test_event_capture_target_bubble_order(void **state)` |
| `test_event_click_bubbles_to_ancestor` | function | `tests/test_js_dom.c:1364` | `static void test_event_click_bubbles_to_ancestor(void **state)` |
| `test_event_delegated_prevent_default` | function | `tests/test_js_dom.c:1454` | `static void test_event_delegated_prevent_default(void **state)` |
| `test_event_focus_does_not_bubble` | function | `tests/test_js_dom.c:1486` | `static void test_event_focus_does_not_bubble(void **state)` |
| `test_event_handle_event_object` | function | `tests/test_js_dom.c:1537` | `static void test_event_handle_event_object(void **state)` |
| `test_event_handler_property_slot` | function | `tests/test_js_dom.c:1498` | `static void test_event_handler_property_slot(void **state)` |
| `test_event_input_handler_fires_with_value` | function | `tests/test_js_dom.c:913` | `static void test_event_input_handler_fires_with_value(void **state)` |
| `test_event_keydown_bubbles_with_data` | function | `tests/test_js_dom.c:1475` | `static void test_event_keydown_bubbles_with_data(void **state)` |
| `test_event_listener_exception_continues` | function | `tests/test_js_dom.c:1525` | `static void test_event_listener_exception_continues(void **state)` |
| `test_event_multiple_click_listeners` | function | `tests/test_js_dom.c:1415` | `static void test_event_multiple_click_listeners(void **state)` |
| `test_event_no_handler_allows_default` | function | `tests/test_js_dom.c:948` | `static void test_event_no_handler_allows_default(void **state)` |
| `test_event_null_args` | function | `tests/test_js_dom.c:955` | `static void test_event_null_args(void **state)` |
| `test_event_once` | function | `tests/test_js_dom.c:1442` | `static void test_event_once(void **state)` |
| `test_event_onkeydown_fires` | function | `tests/test_js_dom.c:895` | `static void test_event_onkeydown_fires(void **state)` |
| `test_event_prevent_default_suppresses` | function | `tests/test_js_dom.c:931` | `static void test_event_prevent_default_suppresses(void **state)` |
| `test_event_remove_listener` | function | `tests/test_js_dom.c:1428` | `static void test_event_remove_listener(void **state)` |
| `test_event_script_dispatch_custom_event` | function | `tests/test_js_dom.c:1512` | `static void test_event_script_dispatch_custom_event(void **state)` |
| `test_event_stop_immediate_propagation` | function | `tests/test_js_dom.c:1403` | `static void test_event_stop_immediate_propagation(void **state)` |
| `test_event_stop_propagation` | function | `tests/test_js_dom.c:1390` | `static void test_event_stop_propagation(void **state)` |
| `test_event_submit_bubbles_to_document` | function | `tests/test_js_dom.c:1464` | `static void test_event_submit_bubbles_to_document(void **state)` |
| `test_ext_blob_family` | function | `tests/test_js_dom.c:1965` | `static void test_ext_blob_family(void **state)` |
| `test_ext_compare_document_position` | function | `tests/test_js_dom.c:1877` | `static void test_ext_compare_document_position(void **state)` |
| `test_ext_document_helpers` | function | `tests/test_js_dom.c:1907` | `static void test_ext_document_helpers(void **state)` |
| `test_ext_insert_adjacent` | function | `tests/test_js_dom.c:1984` | `static void test_ext_insert_adjacent(void **state)` |
| `test_ext_is_equal_node` | function | `tests/test_js_dom.c:2086` | `static void test_ext_is_equal_node(void **state)` |
| `test_ext_prototype_delegation` | function | `tests/test_js_dom.c:1999` | `static void test_ext_prototype_delegation(void **state)` |
| `test_ext_shadow_root` | function | `tests/test_js_dom.c:1886` | `static void test_ext_shadow_root(void **state)` |
| `test_ext_tree_navigation` | function | `tests/test_js_dom.c:1866` | `static void test_ext_tree_navigation(void **state)` |
| `test_ext_tree_walker_terminates` | function | `tests/test_js_dom.c:1897` | `static void test_ext_tree_walker_terminates(void **state)` |
| `test_focus_add_event_listener_fires` | function | `tests/test_js_dom.c:967` | `static void test_focus_add_event_listener_fires(void **state)` |
| `test_focus_blur_scroll_no_handler_allows_default` | function | `tests/test_js_dom.c:1061` | `static void test_focus_blur_scroll_no_handler_allows_default(void **state)` |
| `test_focus_blur_scroll_null_args` | function | `tests/test_js_dom.c:1069` | `static void test_focus_blur_scroll_null_args(void **state)` |
| `test_focus_blur_scroll_prevent_default` | function | `tests/test_js_dom.c:1033` | `static void test_focus_blur_scroll_prevent_default(void **state)` |
| `test_geom_absent_is_zero` | function | `tests/test_js_dom.c:1564` | `static void test_geom_absent_is_zero(void **state)` |
| `test_geom_installed_is_real` | function | `tests/test_js_dom.c:1571` | `static void test_geom_installed_is_real(void **state)` |
| `test_geom_null_ctx` | function | `tests/test_js_dom.c:1609` | `static void test_geom_null_ctx(void **state)` |
| `test_get_element_by_id` | function | `tests/test_js_dom.c:99` | `static void test_get_element_by_id(void **state)` |
| `test_history_cross_origin_is_security_error` | function | `tests/test_js_dom.c:1642` | `static void test_history_cross_origin_is_security_error(void **state)` |
| `test_history_go_records_delta` | function | `tests/test_js_dom.c:1668` | `static void test_history_go_records_delta(void **state)` |
| `test_history_is_bounded` | function | `tests/test_js_dom.c:1678` | `static void test_history_is_bounded(void **state)` |
| `test_history_popstate_restores_entry` | function | `tests/test_js_dom.c:1653` | `static void test_history_popstate_restores_entry(void **state)` |
| `test_history_push_replace_update_location` | function | `tests/test_js_dom.c:1622` | `static void test_history_push_replace_update_location(void **state)` |
| `test_inner_html_builds_and_queryable` | function | `tests/test_js_dom.c:582` | `static void test_inner_html_builds_and_queryable(void **state)` |
| `test_inner_html_getter_serializes` | function | `tests/test_js_dom.c:592` | `static void test_inner_html_getter_serializes(void **state)` |
| `test_install_null_args` | function | `tests/test_js_dom.c:88` | `static void test_install_null_args(void **state)` |
| `test_interfaces_window_and_canvas` | function | `tests/test_js_dom.c:1948` | `static void test_interfaces_window_and_canvas(void **state)` |
| `test_intersection_observer_fires_synthetically` | function | `tests/test_js_dom.c:288` | `static void test_intersection_observer_fires_synthetically(void **state)` |
| `test_intl_stub_does_not_throw` | function | `tests/test_js_dom.c:370` | `static void test_intl_stub_does_not_throw(void **state)` |
| `test_intl_surface` | function | `tests/test_js_dom.c:2015` | `static void test_intl_surface(void **state)` |
| `test_invalid_handles` | function | `tests/test_js_dom.c:146` | `static void test_invalid_handles(void **state)` |
| `test_lifecycle_listeners_get_event` | function | `tests/test_js_dom.c:2029` | `static void test_lifecycle_listeners_get_event(void **state)` |
| `test_local_page_captures_nav` | function | `tests/test_js_dom.c:737` | `static void test_local_page_captures_nav(void **state)` |
| `test_location_assign_and_window_last_wins` | function | `tests/test_js_dom.c:716` | `static void test_location_assign_and_window_last_wins(void **state)` |
| `test_location_href_set_captures_raw` | function | `tests/test_js_dom.c:690` | `static void test_location_href_set_captures_raw(void **state)` |
| `test_location_pathname_defaults_slash` | function | `tests/test_js_dom.c:682` | `static void test_location_pathname_defaults_slash(void **state)` |
| `test_location_reads_real_components` | function | `tests/test_js_dom.c:665` | `static void test_location_reads_real_components(void **state)` |
| `test_location_replace_sets_replace_flag` | function | `tests/test_js_dom.c:704` | `static void test_location_replace_sets_replace_flag(void **state)` |
| `test_methods_are_frozen` | function | `tests/test_js_dom.c:156` | `static void test_methods_are_frozen(void **state)` |
| `test_modern_globals_do_not_throw` | function | `tests/test_js_dom.c:265` | `static void test_modern_globals_do_not_throw(void **state)` |
| `test_mouse_add_event_listener_fires` | function | `tests/test_js_dom.c:1079` | `static void test_mouse_add_event_listener_fires(void **state)` |
| `test_mouse_mousemove_sees_coords` | function | `tests/test_js_dom.c:1112` | `static void test_mouse_mousemove_sees_coords(void **state)` |
| `test_mouse_multi_event_fires` | function | `tests/test_js_dom.c:1129` | `static void test_mouse_multi_event_fires(void **state)` |
| `test_mouse_no_handler_allows_default` | function | `tests/test_js_dom.c:1179` | `static void test_mouse_no_handler_allows_default(void **state)` |
| `test_mouse_null_args` | function | `tests/test_js_dom.c:1186` | `static void test_mouse_null_args(void **state)` |
| `test_mouse_onmouseout_fires` | function | `tests/test_js_dom.c:1096` | `static void test_mouse_onmouseout_fires(void **state)` |
| `test_mouse_prevent_default_suppresses` | function | `tests/test_js_dom.c:1163` | `static void test_mouse_prevent_default_suppresses(void **state)` |
| `test_navigation` | function | `tests/test_js_dom.c:120` | `static void test_navigation(void **state)` |
| `test_no_io_with_dom` | function | `tests/test_js_dom.c:167` | `static void test_no_io_with_dom(void **state)` |
| `test_no_nav_request_when_idle` | function | `tests/test_js_dom.c:728` | `static void test_no_nav_request_when_idle(void **state)` |
| `test_node_count` | function | `tests/test_js_dom.c:107` | `static void test_node_count(void **state)` |
| `test_node_identity_is_cached` | function | `tests/test_js_dom.c:206` | `static void test_node_identity_is_cached(void **state)` |
| `test_onload_runs_and_mutates` | function | `tests/test_js_dom.c:561` | `static void test_onload_runs_and_mutates(void **state)` |
| `test_query_selector_from_js` | function | `tests/test_js_dom.c:182` | `static void test_query_selector_from_js(void **state)` |
| `test_scroll_add_event_listener_fires` | function | `tests/test_js_dom.c:1000` | `static void test_scroll_add_event_listener_fires(void **state)` |
| `test_scroll_onscroll_fires` | function | `tests/test_js_dom.c:1017` | `static void test_scroll_onscroll_fires(void **state)` |
| `test_set_attribute_makes_queryable` | function | `tests/test_js_dom.c:503` | `static void test_set_attribute_makes_queryable(void **state)` |
| `test_set_location_null_ctx` | function | `tests/test_js_dom.c:749` | `static void test_set_location_null_ctx(void **state)` |
| `test_set_text_content_detach_is_memory_safe` | function | `tests/test_js_dom.c:463` | `static void test_set_text_content_detach_is_memory_safe(void **state)` |
| `test_set_text_content_reflects_in_tree` | function | `tests/test_js_dom.c:452` | `static void test_set_text_content_reflects_in_tree(void **state)` |
| `test_settimeout_chains_across_rounds` | function | `tests/test_js_dom.c:431` | `static void test_settimeout_chains_across_rounds(void **state)` |
| `test_settimeout_flushed_by_pump` | function | `tests/test_js_dom.c:574` | `static void test_settimeout_flushed_by_pump(void **state)` |
| `test_shims_survive_globalthis_rebinding` | function | `tests/test_js_dom.c:1921` | `static void test_shims_survive_globalthis_rebinding(void **state)` |
| `test_storage_is_ephemeral` | function | `tests/test_js_dom.c:602` | `static void test_storage_is_ephemeral(void **state)` |
| `test_storage_quota_exceeded` | function | `tests/test_js_dom.c:1799` | `static void test_storage_quota_exceeded(void **state)` |
| `test_storage_seeded_and_dirty_snapshot` | function | `tests/test_js_dom.c:1768` | `static void test_storage_seeded_and_dirty_snapshot(void **state)` |
| `test_storage_untrusted_stays_ephemeral` | function | `tests/test_js_dom.c:1759` | `static void test_storage_untrusted_stays_ephemeral(void **state)` |
| `test_submit_add_event_listener_fires` | function | `tests/test_js_dom.c:1286` | `static void test_submit_add_event_listener_fires(void **state)` |
| `test_submit_no_handler_allows_default` | function | `tests/test_js_dom.c:1343` | `static void test_submit_no_handler_allows_default(void **state)` |
| `test_submit_onsubmit_fires` | function | `tests/test_js_dom.c:1305` | `static void test_submit_onsubmit_fires(void **state)` |
| `test_submit_prevent_default` | function | `tests/test_js_dom.c:1324` | `static void test_submit_prevent_default(void **state)` |
| `test_trusted_fetch_request_response` | function | `tests/test_js_dom.c:2065` | `static void test_trusted_fetch_request_response(void **state)` |
| `test_trusted_send_beacon` | function | `tests/test_js_dom.c:2127` | `static void test_trusted_send_beacon(void **state)` |
| `test_trusted_worker` | function | `tests/test_js_dom.c:2151` | `static void test_trusted_worker(void **state)` |
| `test_url_constructor_parses_components` | function | `tests/test_js_dom.c:383` | `static void test_url_constructor_parses_components(void **state)` |
| `test_url_search_params` | function | `tests/test_js_dom.c:406` | `static void test_url_search_params(void **state)` |
| `test_video_from_scripts_no_video` | function | `tests/test_js_dom.c:2352` | `static void test_video_from_scripts_no_video(void **state)` |
| `test_video_from_scripts_null_args` | function | `tests/test_js_dom.c:2363` | `static void test_video_from_scripts_null_args(void **state)` |
| `test_video_from_scripts_relative_resolved` | function | `tests/test_js_dom.c:2317` | `static void test_video_from_scripts_relative_resolved(void **state)` |
| `test_video_from_scripts_video_data_is_variable` | function | `tests/test_js_dom.c:2302` | `static void test_video_from_scripts_video_data_is_variable(void **state)` |
| `test_video_from_scripts_video_data_string` | function | `tests/test_js_dom.c:2335` | `static void test_video_from_scripts_video_data_string(void **state)` |
| `test_video_shim_empty_html` | function | `tests/test_js_dom.c:2258` | `static void test_video_shim_empty_html(void **state)` |
| `test_video_shim_no_video` | function | `tests/test_js_dom.c:2184` | `static void test_video_shim_no_video(void **state)` |
| `test_video_shim_null_ctx` | function | `tests/test_js_dom.c:2270` | `static void test_video_shim_null_ctx(void **state)` |
| `test_video_shim_relative_url_resolved` | function | `tests/test_js_dom.c:2240` | `static void test_video_shim_relative_url_resolved(void **state)` |
| `test_video_shim_uses_index_1` | function | `tests/test_js_dom.c:2192` | `static void test_video_shim_uses_index_1(void **state)` |
| `test_video_shim_video_data_wins` | function | `tests/test_js_dom.c:2216` | `static void test_video_shim_video_data_wins(void **state)` |
| `test_ws_absent_until_enabled` | function | `tests/test_js_dom.c:1694` | `static void test_ws_absent_until_enabled(void **state)` |
| `test_ws_lifecycle_records_ops_and_fires_events` | function | `tests/test_js_dom.c:1699` | `static void test_ws_lifecycle_records_ops_and_fires_events(void **state)` |
| `test_ws_rejects_plaintext_and_caps` | function | `tests/test_js_dom.c:1743` | `static void test_ws_rejects_plaintext_and_caps(void **state)` |
| `EXPECT` | macro | `tests/test_js_env.c:51` | `#define EXPECT(f, src, expected)` |
| `fixture` | struct | `tests/test_js_env.c:25` | `` |
| `main` | function | `tests/test_js_env.c:355` | `int main(void)` |
| `readback_checksum` | function | `tests/test_js_env.c:279` | `static void readback_checksum(uint64_t key, char *out, size_t out_size)` |
| `run` | function | `tests/test_js_env.c:47` | `static js_status run(fixture *f, const char *src, js_result *r)` |
| `setup` | function | `tests/test_js_env.c:29` | `static int setup(void **state)` |
| `teardown` | function | `tests/test_js_env.c:38` | `static int teardown(void **state)` |
| `test_bool_nav_props` | function | `tests/test_js_env.c:103` | `static void test_bool_nav_props(void **state)` |
| `test_canvas_readback` | function | `tests/test_js_env.c:239` | `static void test_canvas_readback(void **state)` |
| `test_canvas_unforgeable` | function | `tests/test_js_env.c:303` | `static void test_canvas_unforgeable(void **state)` |
| `test_canvas_unlinkable` | function | `tests/test_js_env.c:295` | `static void test_canvas_unlinkable(void **state)` |
| `test_clocks_coarse` | function | `tests/test_js_env.c:178` | `static void test_clocks_coarse(void **state)` |
| `test_coexists_with_dom` | function | `tests/test_js_env.c:326` | `static void test_coexists_with_dom(void **state)` |
| `test_crypto_present` | function | `tests/test_js_env.c:129` | `static void test_crypto_present(void **state)` |
| `test_crypto_random_uuid` | function | `tests/test_js_env.c:137` | `static void test_crypto_random_uuid(void **state)` |
| `test_crypto_random_values` | function | `tests/test_js_env.c:146` | `static void test_crypto_random_values(void **state)` |
| `test_install_null_args` | function | `tests/test_js_env.c:62` | `static void test_install_null_args(void **state)` |
| `test_legacy_nav_props` | function | `tests/test_js_env.c:92` | `static void test_legacy_nav_props(void **state)` |
| `test_navigator_identity` | function | `tests/test_js_env.c:74` | `static void test_navigator_identity(void **state)` |
| `test_navigator_mime_types` | function | `tests/test_js_env.c:120` | `static void test_navigator_mime_types(void **state)` |
| `test_navigator_plugins` | function | `tests/test_js_env.c:112` | `static void test_navigator_plugins(void **state)` |
| `test_performance_timing_identity_safe` | function | `tests/test_js_env.c:190` | `static void test_performance_timing_identity_safe(void **state)` |
| `test_screen_bucketed` | function | `tests/test_js_env.c:166` | `static void test_screen_bucketed(void **state)` |
| `test_screen_edges` | function | `tests/test_js_env.c:220` | `static void test_screen_edges(void **state)` |
| `test_screen_orientation` | function | `tests/test_js_env.c:156` | `static void test_screen_orientation(void **state)` |
| `test_unforgeable` | function | `tests/test_js_env.c:206` | `static void test_unforgeable(void **state)` |
| `chain_parent` | function | `tests/test_js_geom.c:97` | `static dom_node_id chain_parent(void *ctx, dom_node_id n)` |
| `cyclic_parent` | function | `tests/test_js_geom.c:132` | `static dom_node_id cyclic_parent(void *ctx, dom_node_id n)` |
| `main` | function | `tests/test_js_geom.c:213` | `int main(void)` |
| `test_add_and_find` | function | `tests/test_js_geom.c:29` | `static void test_add_and_find(void **state)` |
| `test_add_rejects_and_clamps` | function | `tests/test_js_geom.c:65` | `static void test_add_rejects_and_clamps(void **state)` |
| `test_aggregate_cycle_terminates` | function | `tests/test_js_geom.c:137` | `static void test_aggregate_cycle_terminates(void **state)` |
| `test_aggregate_unions_into_ancestors` | function | `tests/test_js_geom.c:108` | `static void test_aggregate_unions_into_ancestors(void **state)` |
| `test_capacity_bound` | function | `tests/test_js_geom.c:85` | `static void test_capacity_bound(void **state)` |
| `test_decode_fails_closed` | function | `tests/test_js_geom.c:179` | `static void test_decode_fails_closed(void **state)` |
| `test_same_node_unions` | function | `tests/test_js_geom.c:48` | `static void test_same_node_unions(void **state)` |
| `test_wire_roundtrip` | function | `tests/test_js_geom.c:149` | `static void test_wire_roundtrip(void **state)` |
| `main` | function | `tests/test_js_policy.c:89` | `int main(void)` |
| `test_enabled_fail_closed_on_bad_mode` | function | `tests/test_js_policy.c:31` | `static void test_enabled_fail_closed_on_bad_mode(void **state)` |
| `test_mode_from_str` | function | `tests/test_js_policy.c:36` | `static void test_mode_from_str(void **state)` |
| `test_mode_str_roundtrip` | function | `tests/test_js_policy.c:53` | `static void test_mode_str_roundtrip(void **state)` |
| `test_trusted_requires_both_signals` | function | `tests/test_js_policy.c:68` | `static void test_trusted_requires_both_signals(void **state)` |
| `assert_int_equal` | function | `tests/test_js_sandbox.c:156` | `assert_int_equal(js_eval_once("while(true)` |
| `assert_int_equal` | function | `tests/test_js_sandbox.c:171` | `assert_int_equal(js_eval(ctx, "while(true)` |
| `fetches` | type_alias | `tests/test_js_sandbox.c:343` | `typedef struct mod_host { int fetches;` |
| `main` | function | `tests/test_js_sandbox.c:547` | `int main(void)` |
| `mh_fetch` | function | `tests/test_js_sandbox.c:361` | `static char *mh_fetch(void *host, const char *url, size_t *len)` |
| `mh_resolve` | function | `tests/test_js_sandbox.c:346` | `static int mh_resolve(void *host, const char *base, const char *spec, char *out, size_t outsz)` |
| `mod_host` | struct | `tests/test_js_sandbox.c:344` | `` |
| `realm_expect` | function | `tests/test_js_sandbox.c:494` | `static void realm_expect(js_context *ctx, const char *src, const char *want)` |
| `self_fetch` | function | `tests/test_js_sandbox.c:455` | `static char *self_fetch(void *host, const char *url, size_t *len)` |
| `test_context_free_null_and_double` | function | `tests/test_js_sandbox.c:205` | `static void test_context_free_null_and_double(void **state)` |
| `test_context_new_and_free` | function | `tests/test_js_sandbox.c:60` | `static void test_context_new_and_free(void **state)` |
| `test_context_new_null_out` | function | `tests/test_js_sandbox.c:68` | `static void test_context_new_null_out(void **state)` |
| `test_eval_arithmetic` | function | `tests/test_js_sandbox.c:75` | `static void test_eval_arithmetic(void **state)` |
| `test_eval_named_captures_location` | function | `tests/test_js_sandbox.c:290` | `static void test_eval_named_captures_location(void **state)` |
| `test_eval_named_null_filename_defaults` | function | `tests/test_js_sandbox.c:311` | `static void test_eval_named_null_filename_defaults(void **state)` |
| `test_eval_null_args` | function | `tests/test_js_sandbox.c:213` | `static void test_eval_null_args(void **state)` |
| `test_eval_runtime_exception` | function | `tests/test_js_sandbox.c:110` | `static void test_eval_runtime_exception(void **state)` |
| `test_eval_string_concat` | function | `tests/test_js_sandbox.c:89` | `static void test_eval_string_concat(void **state)` |
| `test_eval_syntax_error` | function | `tests/test_js_sandbox.c:101` | `static void test_eval_syntax_error(void **state)` |
| `test_eval_thrown_primitive_has_no_location` | function | `tests/test_js_sandbox.c:326` | `static void test_eval_thrown_primitive_has_no_location(void **state)` |
| `test_filesystem_access_is_reference_error` | function | `tests/test_js_sandbox.c:137` | `static void test_filesystem_access_is_reference_error(void **state)` |
| `test_infinite_loop_times_out` | function | `tests/test_js_sandbox.c:150` | `static void test_infinite_loop_times_out(void **state)` |
| `test_loc_file_may_contain_colons` | function | `tests/test_js_sandbox.c:247` | `static void test_loc_file_may_contain_colons(void **state)` |
| `test_loc_line_only_sets_col_zero` | function | `tests/test_js_sandbox.c:258` | `static void test_loc_line_only_sets_col_zero(void **state)` |
| `test_loc_parses_bare_frame` | function | `tests/test_js_sandbox.c:238` | `static void test_loc_parses_bare_frame(void **state)` |
| `test_loc_parses_named_frame` | function | `tests/test_js_sandbox.c:227` | `static void test_loc_parses_named_frame(void **state)` |
| `test_loc_rejects_garbage_and_null` | function | `tests/test_js_sandbox.c:275` | `static void test_loc_rejects_garbage_and_null(void **state)` |
| `test_loc_truncates_to_cap` | function | `tests/test_js_sandbox.c:267` | `static void test_loc_truncates_to_cap(void **state)` |
| `test_memory_limit_is_enforced` | function | `tests/test_js_sandbox.c:180` | `static void test_memory_limit_is_enforced(void **state)` |
| `test_module_errors_are_reported` | function | `tests/test_js_sandbox.c:404` | `static void test_module_errors_are_reported(void **state)` |
| `test_module_imports_resolve_and_run` | function | `tests/test_js_sandbox.c:383` | `static void test_module_imports_resolve_and_run(void **state)` |
| `test_module_self_await_teardown` | function | `tests/test_js_sandbox.c:465` | `static void test_module_self_await_teardown(void **state)` |
| `test_module_without_host_cannot_import` | function | `tests/test_js_sandbox.c:433` | `static void test_module_without_host_cannot_import(void **state)` |
| `test_no_io_globals` | function | `tests/test_js_sandbox.c:124` | `static void test_no_io_globals(void **state)` |
| `test_realm_shares_time_budget` | function | `tests/test_js_sandbox.c:533` | `static void test_realm_shares_time_budget(void **state)` |
| `test_realms_isolate_and_clone` | function | `tests/test_js_sandbox.c:502` | `static void test_realms_isolate_and_clone(void **state)` |
| `test_result_free_on_zeroed` | function | `tests/test_js_sandbox.c:196` | `static void test_result_free_on_zeroed(void **state)` |
| `test_set_time_budget_applies` | function | `tests/test_js_sandbox.c:163` | `static void test_set_time_budget_applies(void **state)` |
| `test_validate_accepts_within_cap` | function | `tests/test_js_sandbox.c:53` | `static void test_validate_accepts_within_cap(void **state)` |
| `test_validate_rejects_empty` | function | `tests/test_js_sandbox.c:41` | `static void test_validate_rejects_empty(void **state)` |
| `test_validate_rejects_null` | function | `tests/test_js_sandbox.c:36` | `static void test_validate_rejects_null(void **state)` |
| `test_validate_rejects_oversize` | function | `tests/test_js_sandbox.c:46` | `static void test_validate_rejects_oversize(void **state)` |
| `main` | function | `tests/test_link_nav.c:273` | `int main(void)` |
| `test_block_reason_text` | function | `tests/test_link_nav.c:234` | `static void test_block_reason_text(void **state)` |
| `test_block_reasons` | function | `tests/test_link_nav.c:207` | `static void test_block_reasons(void **state)` |
| `test_file_absolute_path` | function | `tests/test_link_nav.c:141` | `static void test_file_absolute_path(void **state)` |
| `test_file_base_blocks_schemes_and_scheme_relative` | function | `tests/test_link_nav.c:165` | `static void test_file_base_blocks_schemes_and_scheme_relative(void **state)` |
| `test_file_base_to_https` | function | `tests/test_link_nav.c:157` | `static void test_file_base_to_https(void **state)` |
| `test_file_drops_fragment` | function | `tests/test_link_nav.c:149` | `static void test_file_drops_fragment(void **state)` |
| `test_file_parent` | function | `tests/test_link_nav.c:133` | `static void test_file_parent(void **state)` |
| `test_file_relative` | function | `tests/test_link_nav.c:125` | `static void test_file_relative(void **state)` |
| `test_fragment_capture` | function | `tests/test_link_nav.c:244` | `static void test_fragment_capture(void **state)` |
| `test_fragment_is_same_document` | function | `tests/test_link_nav.c:37` | `static void test_fragment_is_same_document(void **state)` |
| `test_href_cleaning` | function | `tests/test_link_nav.c:114` | `static void test_href_cleaning(void **state)` |
| `test_https_absolute` | function | `tests/test_link_nav.c:49` | `static void test_https_absolute(void **state)` |
| `test_https_absolute_path_and_parent` | function | `tests/test_link_nav.c:65` | `static void test_https_absolute_path_and_parent(void **state)` |
| `test_https_blocks_downgrade_and_schemes` | function | `tests/test_link_nav.c:76` | `static void test_https_blocks_downgrade_and_schemes(void **state)` |
| `test_https_relative` | function | `tests/test_link_nav.c:57` | `static void test_https_relative(void **state)` |
| `test_https_scheme_relative` | function | `tests/test_link_nav.c:91` | `static void test_https_scheme_relative(void **state)` |
| `test_no_base` | function | `tests/test_link_nav.c:179` | `static void test_no_base(void **state)` |
| `test_null_href_blocked` | function | `tests/test_link_nav.c:29` | `static void test_null_href_blocked(void **state)` |
| `test_null_out` | function | `tests/test_link_nav.c:24` | `static void test_null_out(void **state)` |
| `test_overflow_blocked` | function | `tests/test_link_nav.c:195` | `static void test_overflow_blocked(void **state)` |
| `test_resolve_long_bundle_target` | function | `tests/test_link_nav.c:101` | `static void test_resolve_long_bundle_target(void **state)` |
| `local_store` | function | `tests/test_local_store.c:2` | `* TDD suite for local_store (Hito 5 - Zero Knowledge: encrypted local state). * * RED state until src/local_store.c exis` |
| `main` | function | `tests/test_local_store.c:193` | `int main(void)` |
| `roundtrip_raw` | function | `tests/test_local_store.c:30` | `static void roundtrip_raw(ls_aead aead)` |
| `tamper_at` | function | `tests/test_local_store.c:85` | `static void tamper_at(size_t off)` |
| `test_derive_key` | function | `tests/test_local_store.c:149` | `static void test_derive_key(void **s)` |
| `test_empty_plaintext` | function | `tests/test_local_store.c:53` | `static void test_empty_plaintext(void **s)` |
| `test_format_errors` | function | `tests/test_local_store.c:166` | `static void test_format_errors(void **s)` |
| `test_nondeterministic` | function | `tests/test_local_store.c:107` | `static void test_nondeterministic(void **s)` |
| `test_null_and_limits` | function | `tests/test_local_store.c:181` | `static void test_null_and_limits(void **s)` |
| `test_passphrase_roundtrip` | function | `tests/test_local_store.c:121` | `static void test_passphrase_roundtrip(void **s)` |
| `test_roundtrip_aes` | function | `tests/test_local_store.c:48` | `static void test_roundtrip_aes(void **s)` |
| `test_roundtrip_chacha` | function | `tests/test_local_store.c:49` | `static void test_roundtrip_chacha(void **s)` |
| `test_tamper_aead_id` | function | `tests/test_local_store.c:103` | `static void test_tamper_aead_id(void **s)` |
| `test_tamper_ciphertext` | function | `tests/test_local_store.c:99` | `static void test_tamper_ciphertext(void **s)` |
| `test_tamper_nonce` | function | `tests/test_local_store.c:101` | `static void test_tamper_nonce(void **s)` |
| `test_tamper_salt` | function | `tests/test_local_store.c:102` | `static void test_tamper_salt(void **s)` |
| `test_tamper_tag` | function | `tests/test_local_store.c:100` | `static void test_tamper_tag(void **s)` |
| `test_wrong_key` | function | `tests/test_local_store.c:67` | `static void test_wrong_key(void **s)` |
| `main` | function | `tests/test_media_decoder.c:89` | `int main(void)` |
| `test_pacer_backwards_pts_reanchors` | function | `tests/test_media_decoder.c:40` | `static void test_pacer_backwards_pts_reanchors(void **state)` |
| `test_pacer_hostile_pts_bounded` | function | `tests/test_media_decoder.c:69` | `static void test_pacer_hostile_pts_bounded(void **state)` |
| `test_pacer_lag_reanchors` | function | `tests/test_media_decoder.c:52` | `static void test_pacer_lag_reanchors(void **state)` |
| `test_pacer_null_safe` | function | `tests/test_media_decoder.c:84` | `static void test_pacer_null_safe(void **state)` |
| `test_pacer_paces_by_pts_delta` | function | `tests/test_media_decoder.c:28` | `static void test_pacer_paces_by_pts_delta(void **state)` |
| `main` | function | `tests/test_net_realm.c:140` | `int main(void)` |
| `test_classify_host_clearnet` | function | `tests/test_net_realm.c:37` | `static void test_classify_host_clearnet(void **state)` |
| `test_classify_host_edges` | function | `tests/test_net_realm.c:54` | `static void test_classify_host_edges(void **state)` |
| `test_classify_host_i2p` | function | `tests/test_net_realm.c:30` | `static void test_classify_host_i2p(void **state)` |
| `test_classify_host_lookalikes` | function | `tests/test_net_realm.c:44` | `static void test_classify_host_lookalikes(void **state)` |
| `test_classify_host_onion` | function | `tests/test_net_realm.c:22` | `static void test_classify_host_onion(void **state)` |
| `test_classify_url` | function | `tests/test_net_realm.c:67` | `static void test_classify_url(void **state)` |
| `test_names` | function | `tests/test_net_realm.c:126` | `static void test_names(void **state)` |
| `test_realm_allows_http` | function | `tests/test_net_realm.c:118` | `static void test_realm_allows_http(void **state)` |
| `test_route_clearnet` | function | `tests/test_net_realm.c:96` | `static void test_route_clearnet(void **state)` |
| `test_route_i2p` | function | `tests/test_net_realm.c:88` | `static void test_route_i2p(void **state)` |
| `test_route_null_blocked` | function | `tests/test_net_realm.c:110` | `static void test_route_null_blocked(void **state)` |
| `test_route_onion` | function | `tests/test_net_realm.c:79` | `static void test_route_onion(void **state)` |
| `_GNU_SOURCE` | macro | `tests/test_os_sandbox.c:14` | `#define _GNU_SOURCE` |
| `main` | function | `tests/test_os_sandbox.c:335` | `int main(void)` |
| `net_ns_inode` | function | `tests/test_os_sandbox.c:304` | `static unsigned long net_ns_inode(void)` |
| `suite` | function | `tests/test_os_sandbox.c:313` | `* suite (it is best-effort defense in depth), and on a host that allows them the
 * isolation mus...` |
| `test_harden_allows_permitted_syscall` | function | `tests/test_os_sandbox.c:96` | `static void test_harden_allows_permitted_syscall(void **state)` |
| `test_harden_blocks_exec_mmap` | function | `tests/test_os_sandbox.c:162` | `static void test_harden_blocks_exec_mmap(void **state)` |
| `test_harden_blocks_exec_mprotect` | function | `tests/test_os_sandbox.c:182` | `static void test_harden_blocks_exec_mprotect(void **state)` |
| `test_harden_errno_denies_with_eperm` | function | `tests/test_os_sandbox.c:112` | `static void test_harden_errno_denies_with_eperm(void **state)` |
| `test_harden_kills_denied_syscall` | function | `tests/test_os_sandbox.c:79` | `static void test_harden_kills_denied_syscall(void **state)` |
| `test_harden_kills_io_uring_setup` | function | `tests/test_os_sandbox.c:130` | `static void test_harden_kills_io_uring_setup(void **state)` |
| `test_landlock_abi_present` | function | `tests/test_os_sandbox.c:233` | `static void test_landlock_abi_present(void **state)` |
| `test_landlock_allow_read` | function | `tests/test_os_sandbox.c:257` | `static void test_landlock_allow_read(void **state)` |
| `test_landlock_deny_all` | function | `tests/test_os_sandbox.c:239` | `static void test_landlock_deny_all(void **state)` |
| `test_no_dump_undumpable` | function | `tests/test_os_sandbox.c:214` | `static void test_no_dump_undumpable(void **state)` |
| `test_policy_allows_safe` | function | `tests/test_os_sandbox.c:43` | `static void test_policy_allows_safe(void **state)` |
| `test_policy_denies_dangerous` | function | `tests/test_os_sandbox.c:51` | `static void test_policy_denies_dangerous(void **state)` |
| `test_policy_denies_io_uring` | function | `tests/test_os_sandbox.c:64` | `static void test_policy_denies_io_uring(void **state)` |
| `test_policy_size` | function | `tests/test_os_sandbox.c:71` | `static void test_policy_size(void **state)` |
| `test_prot_allowed_wx` | function | `tests/test_os_sandbox.c:151` | `static void test_prot_allowed_wx(void **state)` |
| `applies` | function | `tests/test_page_view.c:3572` | `* <style>: an extern rule applies (presentation and display:none alike);` |
| `box_of_run_with_bg` | function | `tests/test_page_view.c:2940` | `static const pv_box_def *box_of_run_with_bg(const pv_view *v, int bg)` |
| `break` | function | `tests/test_page_view.c:701` | `* block break (from entering <p>);` |
| `count_inputs` | function | `tests/test_page_view.c:2858` | `static size_t count_inputs(const pv_view *v, int type)` |
| `dropped` | function | `tests/test_page_view.c:425` | `* either flank is dropped (the inter-cell rule above stays). */
static void test_build_table_inli...` |
| `find_image` | function | `tests/test_page_view.c:53` | `static const pv_run *find_image(const pv_view *v, const char *src)` |
| `find_input` | function | `tests/test_page_view.c:2760` | `static const pv_run *find_input(const pv_view *v, const char *name)` |
| `find_link` | function | `tests/test_page_view.c:71` | `static const pv_run *find_link(const pv_view *v, const char *href)` |
| `find_sub` | function | `tests/test_page_view.c:44` | `static const pv_run *find_sub(const pv_view *v, const char *sub)` |
| `find_svg` | function | `tests/test_page_view.c:79` | `static const pv_run *find_svg(const pv_view *v)` |
| `find_text` | function | `tests/test_page_view.c:35` | `static const pv_run *find_text(const pv_view *v, const char *text)` |
| `find_video` | function | `tests/test_page_view.c:62` | `static const pv_run *find_video(const pv_view *v, const char *src)` |
| `float_id` | function | `tests/test_page_view.c:1531` | `* A run inside a float nested in another float reports the inner element as * float_id (unchanged) plus the outer elemen` |
| `form` | function | `tests/test_page_view.c:2826` | `* invisible PV_IN_SUBMIT_BOX proxy carries the form (spec/page_view.md). */ assert_non_null(find_text(v, "Log in"));` |
| `height` | function | `tests/test_page_view.c:3546` | `* real height (jkanime's donghuas/ovas panes are display:none, yet all their
 * thumbnails flowed...` |
| `it` | function | `tests/test_page_view.c:632` | `* the rest of the row share it (so an overflowing table degrades to one row per * line, not one blob). */ assert_int_equ` |
| `main` | function | `tests/test_page_view.c:4312` | `int main(void)` |
| `ordinal` | function | `tests/test_page_view.c:1757` | `* cont_item ordinal (they are one flex/grid item and must flow together in one * cell);` |
| `parse` | function | `tests/test_page_view.c:27` | `static hp_document *parse(const char *html)` |
| `reverted` | function | `tests/test_page_view.c:3532` | `* behavior of treating inline display:none as visible when JS is off * was reverted (commit 897f414 regression) because ` |
| `scales` | function | `tests/test_page_view.c:3448` | `* value the UA rule scales (tanda 19). */
static void test_build_heading_own_relative_size_replac...` |
| `size` | function | `tests/test_page_view.c:770` | `* size (~100px) instead of the CSS 40px, blowing up flex rows (slashdot socials). */
static void ...` |
| `test_after_box_on_empty_element` | function | `tests/test_page_view.c:3045` | `static void test_after_box_on_empty_element(void **state)` |
| `test_append_copies_fields` | function | `tests/test_page_view.c:98` | `static void test_append_copies_fields(void **state)` |
| `test_append_image_copies_fields` | function | `tests/test_page_view.c:125` | `static void test_append_image_copies_fields(void **state)` |
| `test_append_image_null_args` | function | `tests/test_page_view.c:141` | `static void test_append_image_null_args(void **state)` |
| `test_append_null_args` | function | `tests/test_page_view.c:205` | `static void test_append_null_args(void **state)` |
| `test_append_transcodes_cp1252_quotes` | function | `tests/test_page_view.c:177` | `static void test_append_transcodes_cp1252_quotes(void **state)` |
| `test_append_transcodes_latin1` | function | `tests/test_page_view.c:156` | `static void test_append_transcodes_latin1(void **state)` |
| `test_append_transcodes_word` | function | `tests/test_page_view.c:166` | `static void test_append_transcodes_word(void **state)` |
| `test_append_undefined_cp1252_is_qmark` | function | `tests/test_page_view.c:187` | `static void test_append_undefined_cp1252_is_qmark(void **state)` |
| `test_append_valid_utf8_passthrough` | function | `tests/test_page_view.c:197` | `static void test_append_valid_utf8_passthrough(void **state)` |
| `test_append_video_copies_fields` | function | `tests/test_page_view.c:4125` | `static void test_append_video_copies_fields(void **state)` |
| `test_append_video_no_poster` | function | `tests/test_page_view.c:4144` | `static void test_append_video_no_poster(void **state)` |
| `test_append_video_null_args` | function | `tests/test_page_view.c:4160` | `static void test_append_video_null_args(void **state)` |
| `test_author_list_padding_replaces_ua_indent` | function | `tests/test_page_view.c:3605` | `static void test_author_list_padding_replaces_ua_indent(void **state)` |
| `test_before_box_before_text` | function | `tests/test_page_view.c:3000` | `static void test_before_box_before_text(void **state)` |
| `test_before_box_on_empty_element` | function | `tests/test_page_view.c:2984` | `static void test_before_box_on_empty_element(void **state)` |
| `test_before_rides_float_and_container` | function | `tests/test_page_view.c:3630` | `static void test_before_rides_float_and_container(void **state)` |
| `test_block_inside_inline_block_in_line` | function | `tests/test_page_view.c:3728` | `static void test_block_inside_inline_block_in_line(void **state)` |
| `test_box_defaults_and_setter` | function | `tests/test_page_view.c:2182` | `static void test_box_defaults_and_setter(void **state)` |
| `test_build_abs_child_is_not_a_flex_item` | function | `tests/test_page_view.c:1934` | `static void test_build_abs_child_is_not_a_flex_item(void **state)` |
| `test_build_absolute_inside_float_escapes` | function | `tests/test_page_view.c:1651` | `static void test_build_absolute_inside_float_escapes(void **state)` |
| `test_build_audio_as_video_kind` | function | `tests/test_page_view.c:4254` | `static void test_build_audio_as_video_kind(void **state)` |
| `test_build_author_color` | function | `tests/test_page_view.c:1147` | `static void test_build_author_color(void **state)` |
| `test_build_bgcolor_attr_fallback` | function | `tests/test_page_view.c:585` | `static void test_build_bgcolor_attr_fallback(void **state)` |
| `test_build_block_break_between_paragraphs` | function | `tests/test_page_view.c:669` | `static void test_build_block_break_between_paragraphs(void **state)` |
| `test_build_box_leaf_inline` | function | `tests/test_page_view.c:2147` | `static void test_build_box_leaf_inline(void **state)` |
| `test_build_box_tree_empty_no_box` | function | `tests/test_page_view.c:2748` | `static void test_build_box_tree_empty_no_box(void **state)` |
| `test_build_box_tree_textless_wrapper` | function | `tests/test_page_view.c:2723` | `static void test_build_box_tree_textless_wrapper(void **state)` |
| `test_build_boxdeco_border_padding` | function | `tests/test_page_view.c:2314` | `static void test_build_boxdeco_border_padding(void **state)` |
| `test_build_boxdeco_defaults_no_box` | function | `tests/test_page_view.c:2629` | `static void test_build_boxdeco_defaults_no_box(void **state)` |
| `test_build_boxdeco_dims_alone_trigger_box` | function | `tests/test_page_view.c:2524` | `static void test_build_boxdeco_dims_alone_trigger_box(void **state)` |
| `test_build_boxdeco_fit_content_height_is_auto` | function | `tests/test_page_view.c:2274` | `static void test_build_boxdeco_fit_content_height_is_auto(void **state)` |
| `test_build_boxdeco_h_margin_alone_creates_box` | function | `tests/test_page_view.c:2213` | `static void test_build_boxdeco_h_margin_alone_creates_box(void **state)` |
| `test_build_boxdeco_h_margin_zero_auto_no_box` | function | `tests/test_page_view.c:2233` | `static void test_build_boxdeco_h_margin_zero_auto_no_box(void **state)` |
| `test_build_boxdeco_min_content_height_is_auto` | function | `tests/test_page_view.c:2296` | `static void test_build_boxdeco_min_content_height_is_auto(void **state)` |
| `test_build_boxdeco_shadow_outline` | function | `tests/test_page_view.c:2422` | `static void test_build_boxdeco_shadow_outline(void **state)` |
| `test_build_boxdeco_shared_id_within_block` | function | `tests/test_page_view.c:2661` | `static void test_build_boxdeco_shared_id_within_block(void **state)` |
| `test_build_boxdeco_sibling_blocks_distinct_ids` | function | `tests/test_page_view.c:2643` | `static void test_build_boxdeco_sibling_blocks_distinct_ids(void **state)` |
| `test_build_boxdeco_visibility_overflow_cursor` | function | `tests/test_page_view.c:2445` | `static void test_build_boxdeco_visibility_overflow_cursor(void **state)` |
| `test_build_boxdef_carries_node_id` | function | `tests/test_page_view.c:2257` | `static void test_build_boxdef_carries_node_id(void **state)` |
| `test_build_caret_color_inherited` | function | `tests/test_page_view.c:4101` | `static void test_build_caret_color_inherited(void **state)` |
| `test_build_combinator_selectors` | function | `tests/test_page_view.c:1273` | `static void test_build_combinator_selectors(void **state)` |
| `test_build_component_custom_props` | function | `tests/test_page_view.c:3481` | `static void test_build_component_custom_props(void **state)` |
| `test_build_cont_item_identity` | function | `tests/test_page_view.c:1759` | `static void test_build_cont_item_identity(void **state)` |
| `test_build_content_visibility_hidden_folds` | function | `tests/test_page_view.c:4056` | `static void test_build_content_visibility_hidden_folds(void **state)` |
| `test_build_control_without_form` | function | `tests/test_page_view.c:3118` | `static void test_build_control_without_form(void **state)` |
| `test_build_css_bold_and_inline_wins` | function | `tests/test_page_view.c:3425` | `static void test_build_css_bold_and_inline_wins(void **state)` |
| `test_build_cursor_alone_triggers_box` | function | `tests/test_page_view.c:2469` | `static void test_build_cursor_alone_triggers_box(void **state)` |
| `test_build_display_none_hidden` | function | `tests/test_page_view.c:3520` | `static void test_build_display_none_hidden(void **state)` |
| `test_build_empty_box_gets_run_and_box` | function | `tests/test_page_view.c:2345` | `static void test_build_empty_box_gets_run_and_box(void **state)` |
| `test_build_empty_document` | function | `tests/test_page_view.c:1111` | `static void test_build_empty_document(void **state)` |
| `test_build_empty_flex_grow_spacer` | function | `tests/test_page_view.c:929` | `static void test_build_empty_flex_grow_spacer(void **state)` |
| `test_build_flex_container` | function | `tests/test_page_view.c:1311` | `static void test_build_flex_container(void **state)` |
| `test_build_flex_container_from_sheet` | function | `tests/test_page_view.c:2035` | `static void test_build_flex_container_from_sheet(void **state)` |
| `test_build_flex_item_values` | function | `tests/test_page_view.c:1424` | `static void test_build_flex_item_values(void **state)` |
| `test_build_flex_whitespace_not_item` | function | `tests/test_page_view.c:1681` | `static void test_build_flex_whitespace_not_item(void **state)` |
| `test_build_flex_wrap_align_row_gap` | function | `tests/test_page_view.c:1383` | `static void test_build_flex_wrap_align_row_gap(void **state)` |
| `test_build_float_outermost_founder` | function | `tests/test_page_view.c:1534` | `static void test_build_float_outermost_founder(void **state)` |
| `test_build_float_threading` | function | `tests/test_page_view.c:1488` | `static void test_build_float_threading(void **state)` |
| `test_build_float_widthless_stays_unset` | function | `tests/test_page_view.c:873` | `static void test_build_float_widthless_stays_unset(void **state)` |
| `test_build_flow_table_row_is_one_block` | function | `tests/test_page_view.c:2387` | `static void test_build_flow_table_row_is_one_block(void **state)` |
| `test_build_form_post_and_hidden` | function | `tests/test_page_view.c:2803` | `static void test_build_form_post_and_hidden(void **state)` |
| `test_build_grid_columns_from_sheet` | function | `tests/test_page_view.c:2057` | `static void test_build_grid_columns_from_sheet(void **state)` |
| `test_build_grid_container` | function | `tests/test_page_view.c:1871` | `static void test_build_grid_container(void **state)` |
| `test_build_hbox_container_width_never_seeds_items` | function | `tests/test_page_view.c:1622` | `static void test_build_hbox_container_width_never_seeds_items(void **state)` |
| `test_build_hbox_margin_above_container_merges` | function | `tests/test_page_view.c:1602` | `static void test_build_hbox_margin_above_container_merges(void **state)` |
| `test_build_heading_level` | function | `tests/test_page_view.c:244` | `static void test_build_heading_level(void **state)` |
| `test_build_iframe_display_none_hidden` | function | `tests/test_page_view.c:4299` | `static void test_build_iframe_display_none_hidden(void **state)` |
| `test_build_iframe_emits_navigable_link` | function | `tests/test_page_view.c:4268` | `static void test_build_iframe_emits_navigable_link(void **state)` |
| `test_build_iframe_without_src_ignored` | function | `tests/test_page_view.c:4286` | `static void test_build_iframe_without_src_ignored(void **state)` |
| `test_build_image_auto_size_keeps_attr` | function | `tests/test_page_view.c:909` | `static void test_build_image_auto_size_keeps_attr(void **state)` |
| `test_build_image_css_size_overrides_attr` | function | `tests/test_page_view.c:892` | `static void test_build_image_css_size_overrides_attr(void **state)` |
| `test_build_image_in_skipped_subtree_ignored` | function | `tests/test_page_view.c:947` | `static void test_build_image_in_skipped_subtree_ignored(void **state)` |
| `test_build_image_no_src_and_no_srcset_ignored` | function | `tests/test_page_view.c:1096` | `static void test_build_image_no_src_and_no_srcset_ignored(void **state)` |
| `test_build_image_plain_src_wins_over_srcset` | function | `tests/test_page_view.c:1053` | `static void test_build_image_plain_src_wins_over_srcset(void **state)` |
| `test_build_image_px_and_tracking_dims` | function | `tests/test_page_view.c:745` | `static void test_build_image_px_and_tracking_dims(void **state)` |
| `test_build_image_rendering_inherited` | function | `tests/test_page_view.c:4082` | `static void test_build_image_rendering_inherited(void **state)` |
| `test_build_image_srcset_data_url_not_truncated_at_comma` | function | `tests/test_page_view.c:1081` | `static void test_build_image_srcset_data_url_not_truncated_at_comma(void **state)` |
| `test_build_image_srcset_fallback_when_no_src` | function | `tests/test_page_view.c:1037` | `static void test_build_image_srcset_fallback_when_no_src(void **state)` |
| `test_build_image_srcset_single_no_descriptor` | function | `tests/test_page_view.c:1068` | `static void test_build_image_srcset_single_no_descriptor(void **state)` |
| `test_build_image_unknown_dims` | function | `tests/test_page_view.c:730` | `static void test_build_image_unknown_dims(void **state)` |
| `test_build_image_with_dims` | function | `tests/test_page_view.c:713` | `static void test_build_image_with_dims(void **state)` |
| `test_build_image_without_src_dims_emit_broken` | function | `tests/test_page_view.c:1020` | `static void test_build_image_without_src_dims_emit_broken(void **state)` |
| `test_build_image_without_src_ignored` | function | `tests/test_page_view.c:989` | `static void test_build_image_without_src_ignored(void **state)` |
| `test_build_inline_emphasis` | function | `tests/test_page_view.c:261` | `static void test_build_inline_emphasis(void **state)` |
| `test_build_inline_link_no_break_within_paragraph` | function | `tests/test_page_view.c:695` | `static void test_build_inline_link_no_break_within_paragraph(void **state)` |
| `test_build_inline_whitespace_kept` | function | `tests/test_page_view.c:1737` | `static void test_build_inline_whitespace_kept(void **state)` |
| `test_build_link_with_href` | function | `tests/test_page_view.c:650` | `static void test_build_link_with_href(void **state)` |
| `test_build_nested_table_not_flattened` | function | `tests/test_page_view.c:601` | `static void test_build_nested_table_not_flattened(void **state)` |
| `test_build_node_id_matches_dom_index` | function | `tests/test_page_view.c:3967` | `static void test_build_node_id_matches_dom_index(void **state)` |
| `test_build_noscript_hidden_when_js_on` | function | `tests/test_page_view.c:976` | `static void test_build_noscript_hidden_when_js_on(void **state)` |
| `test_build_noscript_shown_when_js_off` | function | `tests/test_page_view.c:963` | `static void test_build_noscript_shown_when_js_off(void **state)` |
| `test_build_null_args` | function | `tests/test_page_view.c:222` | `static void test_build_null_args(void **state)` |
| `test_build_oof_flag_badges_idiom` | function | `tests/test_page_view.c:2015` | `static void test_build_oof_flag_badges_idiom(void **state)` |
| `test_build_oof_flag_via_cascade` | function | `tests/test_page_view.c:1991` | `static void test_build_oof_flag_via_cascade(void **state)` |
| `test_build_oof_image_carries_block_id` | function | `tests/test_page_view.c:1566` | `static void test_build_oof_image_carries_block_id(void **state)` |
| `test_build_ordered_and_nested_list` | function | `tests/test_page_view.c:320` | `static void test_build_ordered_and_nested_list(void **state)` |
| `test_build_plain_text` | function | `tests/test_page_view.c:231` | `static void test_build_plain_text(void **state)` |
| `test_build_pointer_events_on_box` | function | `tests/test_page_view.c:4037` | `static void test_build_pointer_events_on_box(void **state)` |
| `test_build_pseudo_classes_and_siblings` | function | `tests/test_page_view.c:3190` | `static void test_build_pseudo_classes_and_siblings(void **state)` |
| `test_build_reader_skips_boilerplate` | function | `tests/test_page_view.c:3923` | `static void test_build_reader_skips_boilerplate(void **state)` |
| `test_build_root_element_style_inherits` | function | `tests/test_page_view.c:1896` | `static void test_build_root_element_style_inherits(void **state)` |
| `test_build_root_font_size_is_overridable` | function | `tests/test_page_view.c:1914` | `static void test_build_root_font_size_is_overridable(void **state)` |
| `test_build_search_form_get` | function | `tests/test_page_view.c:2770` | `static void test_build_search_form_get(void **state)` |
| `test_build_select_defaults_to_first_option` | function | `tests/test_page_view.c:3101` | `static void test_build_select_defaults_to_first_option(void **state)` |
| `test_build_select_shows_selected_option` | function | `tests/test_page_view.c:3062` | `static void test_build_select_shows_selected_option(void **state)` |
| `test_build_skips_script_and_style` | function | `tests/test_page_view.c:681` | `static void test_build_skips_script_and_style(void **state)` |
| `test_build_style_cache_distinct_siblings` | function | `tests/test_page_view.c:3313` | `static void test_build_style_cache_distinct_siblings(void **state)` |
| `test_build_styled_external_css` | function | `tests/test_page_view.c:3576` | `static void test_build_styled_external_css(void **state)` |
| `test_build_svg_fills_border_box_ancestor` | function | `tests/test_page_view.c:812` | `static void test_build_svg_fills_border_box_ancestor(void **state)` |
| `test_build_svg_no_ancestor_width_unset` | function | `tests/test_page_view.c:832` | `static void test_build_svg_no_ancestor_width_unset(void **state)` |
| `test_build_table_cell_author_styles` | function | `tests/test_page_view.c:3253` | `static void test_build_table_cell_author_styles(void **state)` |
| `test_build_table_colspan_rowspan` | function | `tests/test_page_view.c:1825` | `static void test_build_table_colspan_rowspan(void **state)` |
| `test_build_table_flattens_cell` | function | `tests/test_page_view.c:451` | `static void test_build_table_flattens_cell(void **state)` |
| `test_build_table_grid` | function | `tests/test_page_view.c:343` | `static void test_build_table_grid(void **state)` |
| `test_build_table_intercell_whitespace_dropped` | function | `tests/test_page_view.c:383` | `static void test_build_table_intercell_whitespace_dropped(void **state)` |
| `test_build_text_align_and_font_size` | function | `tests/test_page_view.c:3355` | `static void test_build_text_align_and_font_size(void **state)` |
| `test_build_text_decoration` | function | `tests/test_page_view.c:3402` | `static void test_build_text_decoration(void **state)` |
| `test_build_text_overflow_and_word_break` | function | `tests/test_page_view.c:2569` | `static void test_build_text_overflow_and_word_break(void **state)` |
| `test_build_textarea_value` | function | `tests/test_page_view.c:2839` | `static void test_build_textarea_value(void **state)` |
| `test_build_two_forms_distinct_groups` | function | `tests/test_page_view.c:3131` | `static void test_build_two_forms_distinct_groups(void **state)` |
| `test_build_unordered_list` | function | `tests/test_page_view.c:302` | `static void test_build_unordered_list(void **state)` |
| `test_build_video_fallback_suppressed` | function | `tests/test_page_view.c:4228` | `static void test_build_video_fallback_suppressed(void **state)` |
| `test_build_video_source_type_preference` | function | `tests/test_page_view.c:4210` | `static void test_build_video_source_type_preference(void **state)` |
| `test_build_video_uses_source_child` | function | `tests/test_page_view.c:4190` | `static void test_build_video_uses_source_child(void **state)` |
| `test_build_video_with_source` | function | `tests/test_page_view.c:4170` | `static void test_build_video_with_source(void **state)` |
| `test_build_video_without_src_ignored` | function | `tests/test_page_view.c:4243` | `static void test_build_video_without_src_ignored(void **state)` |
| `test_build_zero_padding_is_not_a_box` | function | `tests/test_page_view.c:2370` | `static void test_build_zero_padding_is_not_a_box(void **state)` |
| `test_button_content_flows` | function | `tests/test_page_view.c:2880` | `static void test_button_content_flows(void **state)` |
| `test_button_icon_invents_no_label` | function | `tests/test_page_view.c:2865` | `static void test_button_icon_invents_no_label(void **state)` |
| `test_button_submit_proxy` | function | `tests/test_page_view.c:2894` | `static void test_button_submit_proxy(void **state)` |
| `test_button_ua_face_loses_to_author` | function | `tests/test_page_view.c:2919` | `static void test_button_ua_face_loses_to_author(void **state)` |
| `test_container_defaults` | function | `tests/test_page_view.c:2096` | `static void test_container_defaults(void **state)` |
| `test_free_null_and_double` | function | `tests/test_page_view.c:213` | `static void test_free_null_and_double(void **state)` |
| `test_gradient_text_runs` | function | `tests/test_page_view.c:1195` | `static void test_gradient_text_runs(void **state)` |
| `test_inline_level_tag_list_stays_in_line` | function | `tests/test_page_view.c:3661` | `static void test_inline_level_tag_list_stays_in_line(void **state)` |
| `test_inline_pseudo_registers_no_box` | function | `tests/test_page_view.c:3033` | `static void test_inline_pseudo_registers_no_box(void **state)` |
| `test_link_color_inherit` | function | `tests/test_page_view.c:2957` | `static void test_link_color_inherit(void **state)` |
| `test_marker_only_for_list_item_display` | function | `tests/test_page_view.c:3689` | `static void test_marker_only_for_list_item_display(void **state)` |
| `test_new_is_empty` | function | `tests/test_page_view.c:89` | `static void test_new_is_empty(void **state)` |
| `test_pct_padding_generates_box` | function | `tests/test_page_view.c:2971` | `static void test_pct_padding_generates_box(void **state)` |
| `test_pseudo_after_on_element_with_children` | function | `tests/test_page_view.c:3804` | `static void test_pseudo_after_on_element_with_children(void **state)` |
| `test_pseudo_after_on_whitespace_only_no_run` | function | `tests/test_page_view.c:3882` | `static void test_pseudo_after_on_whitespace_only_no_run(void **state)` |
| `test_pseudo_before_escape_end_to_end` | function | `tests/test_page_view.c:3869` | `static void test_pseudo_before_escape_end_to_end(void **state)` |
| `test_pseudo_before_fires_with_nested_text` | function | `tests/test_page_view.c:3896` | `static void test_pseudo_before_fires_with_nested_text(void **state)` |
| `test_pseudo_before_on_element_with_children` | function | `tests/test_page_view.c:3789` | `static void test_pseudo_before_on_element_with_children(void **state)` |
| `test_pseudo_before_on_empty` | function | `tests/test_page_view.c:3776` | `static void test_pseudo_before_on_empty(void **state)` |
| `test_pseudo_before_on_textless_subtree` | function | `tests/test_page_view.c:3853` | `static void test_pseudo_before_on_textless_subtree(void **state)` |
| `test_pseudo_both_before_and_after` | function | `tests/test_page_view.c:3819` | `static void test_pseudo_both_before_and_after(void **state)` |
| `test_pseudo_display_none_generates_nothing` | function | `tests/test_page_view.c:3016` | `static void test_pseudo_display_none_generates_nothing(void **state)` |
| `test_pseudo_no_content_no_run` | function | `tests/test_page_view.c:3909` | `static void test_pseudo_no_content_no_run(void **state)` |
| `test_set_color_model` | function | `tests/test_page_view.c:1125` | `static void test_set_color_model(void **state)` |
| `test_set_node_id_model` | function | `tests/test_page_view.c:3951` | `static void test_set_node_id_model(void **state)` |
| `test_set_text_style_model` | function | `tests/test_page_view.c:4006` | `static void test_set_text_style_model(void **state)` |
| `test_text_fill_color_runs` | function | `tests/test_page_view.c:1227` | `static void test_text_fill_color_runs(void **state)` |
| `unset` | function | `tests/test_page_view.c:792` | `* unset (-1) so the render step derives it from the viewBox aspect. */
static void test_build_svg...` |
| `wrapping` | function | `tests/test_page_view.c:1351` | `* sideways instead of wrapping (spec/page_view.md, 2026-08-11 correction). */
static void test_bu...` |
| `main` | function | `tests/test_pdf_export.c:290` | `int main(void)` |
| `pagination` | function | `tests/test_pdf_export.c:8` | `* deterministic pagination (single/multi page, no row splitting, oversized row,
 * gap preservati...` |
| `test_basename_all_separators_fall_back` | function | `tests/test_pdf_export.c:105` | `static void test_basename_all_separators_fall_back(void **state)` |
| `test_basename_collapses_underscores` | function | `tests/test_pdf_export.c:72` | `static void test_basename_collapses_underscores(void **state)` |
| `test_basename_control_bytes_mapped` | function | `tests/test_pdf_export.c:79` | `static void test_basename_control_bytes_mapped(void **state)` |
| `test_basename_dotdot_only_falls_back` | function | `tests/test_pdf_export.c:57` | `static void test_basename_dotdot_only_falls_back(void **state)` |
| `test_basename_empty_and_null_fall_back` | function | `tests/test_pdf_export.c:96` | `static void test_basename_empty_and_null_fall_back(void **state)` |
| `test_basename_length_bound` | function | `tests/test_pdf_export.c:112` | `static void test_basename_length_bound(void **state)` |
| `test_basename_maps_spaces_and_reserved` | function | `tests/test_pdf_export.c:31` | `static void test_basename_maps_spaces_and_reserved(void **state)` |
| `test_basename_neutralizes_traversal` | function | `tests/test_pdf_export.c:49` | `static void test_basename_neutralizes_traversal(void **state)` |
| `test_basename_non_ascii_mapped` | function | `tests/test_pdf_export.c:87` | `static void test_basename_non_ascii_mapped(void **state)` |
| `test_basename_null_out_and_zero_size` | function | `tests/test_pdf_export.c:123` | `static void test_basename_null_out_and_zero_size(void **state)` |
| `test_basename_overflow_fails_closed` | function | `tests/test_pdf_export.c:130` | `static void test_basename_overflow_fails_closed(void **state)` |
| `test_basename_rejects_path_separators` | function | `tests/test_pdf_export.c:39` | `static void test_basename_rejects_path_separators(void **state)` |
| `test_basename_trims_edges` | function | `tests/test_pdf_export.c:64` | `static void test_basename_trims_edges(void **state)` |
| `test_build_path_basic` | function | `tests/test_pdf_export.c:139` | `static void test_build_path_basic(void **state)` |
| `test_build_path_empty_title_fallback` | function | `tests/test_pdf_export.c:162` | `static void test_build_path_empty_title_fallback(void **state)` |
| `test_build_path_ext_hostile_title_contained` | function | `tests/test_pdf_export.c:202` | `static void test_build_path_ext_hostile_title_contained(void **state)` |
| `test_build_path_ext_null_ext` | function | `tests/test_pdf_export.c:194` | `static void test_build_path_ext_null_ext(void **state)` |
| `test_build_path_ext_overflow_fails_closed` | function | `tests/test_pdf_export.c:213` | `static void test_build_path_ext_overflow_fails_closed(void **state)` |
| `test_build_path_ext_png` | function | `tests/test_pdf_export.c:186` | `static void test_build_path_ext_png(void **state)` |
| `test_build_path_hostile_title_contained` | function | `tests/test_pdf_export.c:153` | `static void test_build_path_hostile_title_contained(void **state)` |
| `test_build_path_null_args` | function | `tests/test_pdf_export.c:176` | `static void test_build_path_null_args(void **state)` |
| `test_build_path_overflow_fails_closed` | function | `tests/test_pdf_export.c:169` | `static void test_build_path_overflow_fails_closed(void **state)` |
| `test_build_path_trailing_slash` | function | `tests/test_pdf_export.c:146` | `static void test_build_path_trailing_slash(void **state)` |
| `test_paginate_breaks_without_splitting` | function | `tests/test_pdf_export.c:238` | `static void test_paginate_breaks_without_splitting(void **state)` |
| `test_paginate_invalid_args` | function | `tests/test_pdf_export.c:276` | `static void test_paginate_invalid_args(void **state)` |
| `test_paginate_oversized_row_not_split` | function | `tests/test_pdf_export.c:252` | `static void test_paginate_oversized_row_not_split(void **state)` |
| `test_paginate_preserves_gaps` | function | `tests/test_pdf_export.c:264` | `static void test_paginate_preserves_gaps(void **state)` |
| `test_paginate_single_page` | function | `tests/test_pdf_export.c:223` | `static void test_paginate_single_page(void **state)` |
| `main` | function | `tests/test_perf_trace.c:174` | `int main(void)` |
| `test_elapsed_us_normal` | function | `tests/test_perf_trace.c:89` | `static void test_elapsed_us_normal(void **state)` |
| `test_elapsed_us_underflow_guard` | function | `tests/test_perf_trace.c:95` | `static void test_elapsed_us_underflow_guard(void **state)` |
| `test_format_deterministic_and_only_nonempty_stages` | function | `tests/test_perf_trace.c:115` | `static void test_format_deterministic_and_only_nonempty_stages(void **state)` |
| `test_format_null_or_zero_cap` | function | `tests/test_perf_trace.c:152` | `static void test_format_null_or_zero_cap(void **state)` |
| `test_format_truncates_never_overflows` | function | `tests/test_perf_trace.c:138` | `static void test_format_truncates_never_overflows(void **state)` |
| `test_min_max_median` | function | `tests/test_perf_trace.c:42` | `static void test_min_max_median(void **state)` |
| `test_null_safe` | function | `tests/test_perf_trace.c:163` | `static void test_null_safe(void **state)` |
| `test_ring_wraparound_fifo` | function | `tests/test_perf_trace.c:55` | `static void test_ring_wraparound_fifo(void **state)` |
| `test_single_record` | function | `tests/test_perf_trace.c:28` | `static void test_single_record(void **state)` |
| `test_stage_name` | function | `tests/test_perf_trace.c:101` | `static void test_stage_name(void **state)` |
| `test_stage_out_of_range_is_noop` | function | `tests/test_perf_trace.c:72` | `static void test_stage_out_of_range_is_noop(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_prefetch.c:5` | `#define _POSIX_C_SOURCE` |
| `barrier` | type_alias | `tests/test_prefetch.c:126` | `typedef struct fake_ctx { pthread_barrier_t barrier;` |
| `fake_ctx` | struct | `tests/test_prefetch.c:126` | `` |
| `fake_fetch` | function | `tests/test_prefetch.c:135` | `static int fake_fetch(void *vctx, const char *method, const char *url,
                      cons...` |
| `main` | function | `tests/test_prefetch.c:289` | `int main(void)` |
| `test_pool_finish_unconsumed_and_empty` | function | `tests/test_prefetch.c:228` | `static void test_pool_finish_unconsumed_and_empty(void **state)` |
| `test_pool_miss_consume_and_failure` | function | `tests/test_prefetch.c:185` | `static void test_pool_miss_consume_and_failure(void **state)` |
| `test_pool_parallel_fetch_and_take` | function | `tests/test_prefetch.c:153` | `static void test_pool_parallel_fetch_and_take(void **state)` |
| `test_pooled_fetch_adapter` | function | `tests/test_prefetch.c:249` | `static void test_pooled_fetch_adapter(void **state)` |
| `test_scan_basic_stylesheet_and_script` | function | `tests/test_prefetch.c:32` | `static void test_scan_basic_stylesheet_and_script(void **state)` |
| `test_scan_null_args` | function | `tests/test_prefetch.c:22` | `static void test_scan_null_args(void **state)` |
| `test_scan_ref_cap` | function | `tests/test_prefetch.c:104` | `static void test_scan_ref_cap(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_prefs.c:9` | `#define _POSIX_C_SOURCE` |
| `main` | function | `tests/test_prefs.c:394` | `int main(void)` |
| `test_bookmark_toggle_and_cap` | function | `tests/test_prefs.c:237` | `static void test_bookmark_toggle_and_cap(void **state)` |
| `test_bookmarks_page_escapes` | function | `tests/test_prefs.c:345` | `static void test_bookmarks_page_escapes(void **state)` |
| `test_format_null_args` | function | `tests/test_prefs.c:382` | `static void test_format_null_args(void **state)` |
| `test_history_dedup_and_evict` | function | `tests/test_prefs.c:265` | `static void test_history_dedup_and_evict(void **state)` |
| `test_hostile_title_cleaned` | function | `tests/test_prefs.c:207` | `static void test_hostile_title_cleaned(void **state)` |
| `test_init_defaults` | function | `tests/test_prefs.c:25` | `static void test_init_defaults(void **state)` |
| `test_invalid_urls_rejected` | function | `tests/test_prefs.c:179` | `static void test_invalid_urls_rejected(void **state)` |
| `test_parse_bad_magic` | function | `tests/test_prefs.c:110` | `static void test_parse_bad_magic(void **state)` |
| `test_parse_clamps_out_of_range` | function | `tests/test_prefs.c:157` | `static void test_parse_clamps_out_of_range(void **state)` |
| `test_parse_too_large` | function | `tests/test_prefs.c:126` | `static void test_parse_too_large(void **state)` |
| `test_parse_unknown_and_malformed_skipped` | function | `tests/test_prefs.c:135` | `static void test_parse_unknown_and_malformed_skipped(void **state)` |
| `test_roundtrip` | function | `tests/test_prefs.c:50` | `static void test_roundtrip(void **state)` |
| `test_suggest_priorities` | function | `tests/test_prefs.c:290` | `static void test_suggest_priorities(void **state)` |
| `_GNU_SOURCE` | macro | `tests/test_profile.c:9` | `#define _GNU_SOURCE` |
| `dir` | type_alias | `tests/test_profile.c:27` | `typedef struct fixture { char dir[64];` |
| `file_size` | function | `tests/test_profile.c:64` | `static size_t file_size(const char *path)` |
| `fixture` | struct | `tests/test_profile.c:28` | `` |
| `main` | function | `tests/test_profile.c:278` | `int main(void)` |
| `path_of` | function | `tests/test_profile.c:60` | `static void path_of(const fixture *f, const char *name, char *out, size_t cap)` |
| `setup` | function | `tests/test_profile.c:30` | `static int setup(void **state)` |
| `teardown` | function | `tests/test_profile.c:39` | `static int teardown(void **state)` |
| `test_first_launch_defaults` | function | `tests/test_profile.c:115` | `static void test_first_launch_defaults(void **state)` |
| `test_foreign_key_auth_fails` | function | `tests/test_profile.c:236` | `static void test_foreign_key_auth_fails(void **state)` |
| `test_nothing_readable_on_disk` | function | `tests/test_profile.c:174` | `static void test_nothing_readable_on_disk(void **state)` |
| `test_null_and_not_ready` | function | `tests/test_profile.c:261` | `static void test_null_and_not_ready(void **state)` |
| `test_open_bad_dir` | function | `tests/test_profile.c:103` | `static void test_open_bad_dir(void **state)` |
| `test_open_creates_keyfile` | function | `tests/test_profile.c:72` | `static void test_open_creates_keyfile(void **state)` |
| `test_open_rejects_corrupt_keyfile` | function | `tests/test_profile.c:89` | `static void test_open_rejects_corrupt_keyfile(void **state)` |
| `test_save_load_roundtrip_two_ctx` | function | `tests/test_profile.c:128` | `static void test_save_load_roundtrip_two_ctx(void **state)` |
| `test_tampered_blob_auth_fails` | function | `tests/test_profile.c:204` | `static void test_tampered_blob_auth_fails(void **state)` |
| `caps_images_on` | function | `tests/test_render_doc.c:28` | `static rdp_caps caps_images_on(void)` |
| `first_kind` | function | `tests/test_render_doc.c:35` | `static const rd_block *first_kind(const rd_doc *d, rd_kind k)` |
| `main` | function | `tests/test_render_doc.c:826` | `int main(void)` |
| `test_author_color_gated_by_css` | function | `tests/test_render_doc.c:372` | `static void test_author_color_gated_by_css(void **state)` |
| `test_block_tag_total` | function | `tests/test_render_doc.c:777` | `static void test_block_tag_total(void **state)` |
| `test_build_null_out` | function | `tests/test_render_doc.c:44` | `static void test_build_null_out(void **state)` |
| `test_build_null_view_is_empty` | function | `tests/test_render_doc.c:51` | `static void test_build_null_view_is_empty(void **state)` |
| `test_caret_color_gated_on_input` | function | `tests/test_render_doc.c:506` | `static void test_caret_color_gated_on_input(void **state)` |
| `test_cont_item_carried_by_default` | function | `tests/test_render_doc.c:628` | `static void test_cont_item_carried_by_default(void **state)` |
| `test_container_carried_by_default` | function | `tests/test_render_doc.c:596` | `static void test_container_carried_by_default(void **state)` |
| `test_emphasis_propagates` | function | `tests/test_render_doc.c:94` | `static void test_emphasis_propagates(void **state)` |
| `test_flex_item_carried_by_default` | function | `tests/test_render_doc.c:697` | `static void test_flex_item_carried_by_default(void **state)` |
| `test_flex_wrap_align_row_gap_carried_by_default` | function | `tests/test_render_doc.c:745` | `static void test_flex_wrap_align_row_gap_carried_by_default(void **state)` |
| `test_float_carried_by_default` | function | `tests/test_render_doc.c:661` | `static void test_float_carried_by_default(void **state)` |
| `test_free_null_and_double` | function | `tests/test_render_doc.c:362` | `static void test_free_null_and_double(void **state)` |
| `test_heading_paragraph_link` | function | `tests/test_render_doc.c:64` | `static void test_heading_paragraph_link(void **state)` |
| `test_href_sanitised` | function | `tests/test_render_doc.c:322` | `static void test_href_sanitised(void **state)` |
| `test_image_data_url_allowed_no_top` | function | `tests/test_render_doc.c:278` | `static void test_image_data_url_allowed_no_top(void **state)` |
| `test_image_data_url_allowed_remote_top` | function | `tests/test_render_doc.c:260` | `static void test_image_data_url_allowed_remote_top(void **state)` |
| `test_image_data_url_disabled_by_default` | function | `tests/test_render_doc.c:291` | `static void test_image_data_url_disabled_by_default(void **state)` |
| `test_image_data_url_percent_encoded_blocked_invalid` | function | `tests/test_render_doc.c:306` | `static void test_image_data_url_percent_encoded_blocked_invalid(void **state)` |
| `test_image_label_total` | function | `tests/test_render_doc.c:349` | `static void test_image_label_total(void **state)` |
| `test_image_off_emits_notice_and_blocked` | function | `tests/test_render_doc.c:125` | `static void test_image_off_emits_notice_and_blocked(void **state)` |
| `test_image_on_allows_normal` | function | `tests/test_render_doc.c:164` | `static void test_image_on_allows_normal(void **state)` |
| `test_image_on_blocks_non_https` | function | `tests/test_render_doc.c:225` | `static void test_image_on_blocks_non_https(void **state)` |
| `test_image_on_blocks_tracker` | function | `tests/test_render_doc.c:212` | `static void test_image_on_blocks_tracker(void **state)` |
| `test_image_on_resolves_doc_relative_src` | function | `tests/test_render_doc.c:198` | `static void test_image_on_resolves_doc_relative_src(void **state)` |
| `test_image_on_resolves_relative_src` | function | `tests/test_render_doc.c:182` | `static void test_image_on_resolves_relative_src(void **state)` |
| `test_image_rendering_gated_on_image` | function | `tests/test_render_doc.c:477` | `static void test_image_rendering_gated_on_image(void **state)` |
| `test_input_label_total` | function | `tests/test_render_doc.c:571` | `static void test_input_label_total(void **state)` |
| `test_input_passthrough` | function | `tests/test_render_doc.c:536` | `static void test_input_passthrough(void **state)` |
| `test_kind_name_total` | function | `tests/test_render_doc.c:339` | `static void test_kind_name_total(void **state)` |
| `test_no_images_no_notice` | function | `tests/test_render_doc.c:150` | `static void test_no_images_no_notice(void **state)` |
| `test_node_id_carried_by_default` | function | `tests/test_render_doc.c:813` | `static void test_node_id_carried_by_default(void **state)` |
| `test_text_ext_2026_07_10_batch_gated_by_css` | function | `tests/test_render_doc.c:437` | `static void test_text_ext_2026_07_10_batch_gated_by_css(void **state)` |
| `test_text_overflow_word_break_gated_by_css` | function | `tests/test_render_doc.c:402` | `static void test_text_overflow_word_break_gated_by_css(void **state)` |
| `caps_images_on` | function | `tests/test_render_policy.c:90` | `static rdp_caps caps_images_on(void)` |
| `consulted` | function | `tests/test_render_policy.c:76` | `* is not even consulted (a bogus URL still yields BLOCK_DISABLED). */ assert_int_equal( rdp_image_decision(off, "https:/` |
| `main` | function | `tests/test_render_policy.c:241` | `int main(void)` |
| `test_caps_safe_is_all_off` | function | `tests/test_render_policy.c:18` | `static void test_caps_safe_is_all_off(void **state)` |
| `test_caps_zero_value_is_safe` | function | `tests/test_render_policy.c:26` | `static void test_caps_zero_value_is_safe(void **state)` |
| `test_image_allow_cross_site_when_enabled` | function | `tests/test_render_policy.c:108` | `static void test_image_allow_cross_site_when_enabled(void **state)` |
| `test_image_allow_data_url` | function | `tests/test_render_policy.c:164` | `static void test_image_allow_data_url(void **state)` |
| `test_image_allow_same_site` | function | `tests/test_render_policy.c:96` | `static void test_image_allow_same_site(void **state)` |
| `test_image_block_invalid` | function | `tests/test_render_policy.c:142` | `static void test_image_block_invalid(void **state)` |
| `test_image_block_scheme` | function | `tests/test_render_policy.c:134` | `static void test_image_block_scheme(void **state)` |
| `test_image_block_tracker` | function | `tests/test_render_policy.c:119` | `static void test_image_block_tracker(void **state)` |
| `test_image_data_url_disabled_by_default` | function | `tests/test_render_policy.c:183` | `static void test_image_data_url_disabled_by_default(void **state)` |
| `test_image_data_url_malformed_is_invalid` | function | `tests/test_render_policy.c:191` | `static void test_image_data_url_malformed_is_invalid(void **state)` |
| `test_image_disabled_by_default` | function | `tests/test_render_policy.c:72` | `static void test_image_disabled_by_default(void **state)` |
| `test_image_disabled_precedence` | function | `tests/test_render_policy.c:207` | `static void test_image_disabled_precedence(void **state)` |
| `test_images_warning_present` | function | `tests/test_render_policy.c:232` | `static void test_images_warning_present(void **state)` |
| `test_img_reason_total_and_stable` | function | `tests/test_render_policy.c:217` | `static void test_img_reason_total_and_stable(void **state)` |
| `test_tracking_pixel_normal` | function | `tests/test_render_policy.c:52` | `static void test_tracking_pixel_normal(void **state)` |
| `test_tracking_pixel_tiny` | function | `tests/test_render_policy.c:37` | `static void test_tracking_pixel_tiny(void **state)` |
| `test_tracking_pixel_unknown` | function | `tests/test_render_policy.c:62` | `static void test_tracking_pixel_unknown(void **state)` |
| `test_tracking_pixel_zero_area` | function | `tests/test_render_policy.c:45` | `static void test_tracking_pixel_zero_area(void **state)` |
| `main` | function | `tests/test_renderer.c:93` | `int main(void)` |
| `test_render_basic` | function | `tests/test_renderer.c:27` | `static void test_render_basic(void **state)` |
| `test_render_binary_does_not_crash_parent` | function | `tests/test_renderer.c:63` | `static void test_render_binary_does_not_crash_parent(void **state)` |
| `test_render_multiple_independent` | function | `tests/test_renderer.c:74` | `static void test_render_multiple_independent(void **state)` |
| `test_render_null_args` | function | `tests/test_renderer.c:48` | `static void test_render_null_args(void **state)` |
| `test_render_strips_script` | function | `tests/test_renderer.c:39` | `static void test_render_strips_script(void **state)` |
| `test_render_too_large` | function | `tests/test_renderer.c:55` | `static void test_render_too_large(void **state)` |
| `test_result_free_null_and_double` | function | `tests/test_renderer.c:84` | `static void test_result_free_null_and_double(void **state)` |
| `main` | function | `tests/test_request_policy.c:139` | `int main(void)` |
| `test_evaluate_allow_same_site` | function | `tests/test_request_policy.c:105` | `static void test_evaluate_allow_same_site(void **state)` |
| `test_evaluate_block_invalid` | function | `tests/test_request_policy.c:128` | `static void test_evaluate_block_invalid(void **state)` |
| `test_evaluate_block_scheme` | function | `tests/test_request_policy.c:120` | `static void test_evaluate_block_scheme(void **state)` |
| `test_evaluate_block_third_party` | function | `tests/test_request_policy.c:112` | `static void test_evaluate_block_third_party(void **state)` |
| `test_host_of_basic` | function | `tests/test_request_policy.c:18` | `static void test_host_of_basic(void **state)` |
| `test_host_of_invalid` | function | `tests/test_request_policy.c:29` | `static void test_host_of_invalid(void **state)` |
| `test_host_of_overflow` | function | `tests/test_request_policy.c:37` | `static void test_host_of_overflow(void **state)` |
| `test_same_site` | function | `tests/test_request_policy.c:91` | `static void test_same_site(void **state)` |
| `test_site_of` | function | `tests/test_request_policy.c:45` | `static void test_site_of(void **state)` |
| `test_site_of_multi_suffix` | function | `tests/test_request_policy.c:58` | `static void test_site_of_multi_suffix(void **state)` |
| `test_site_of_psl` | function | `tests/test_request_policy.c:70` | `static void test_site_of_psl(void **state)` |
| `main` | function | `tests/test_secure_fetch.c:562` | `int main(void)` |
| `test_chain_hybrid_allows_classical` | function | `tests/test_secure_fetch.c:149` | `static void test_chain_hybrid_allows_classical(void **state)` |
| `test_chain_permissive_allows_weak_certs` | function | `tests/test_secure_fetch.c:166` | `static void test_chain_permissive_allows_weak_certs(void **state)` |
| `test_chain_rejects_null` | function | `tests/test_secure_fetch.c:187` | `static void test_chain_rejects_null(void **state)` |
| `test_chain_rejects_sha1_in_any_policy` | function | `tests/test_secure_fetch.c:157` | `static void test_chain_rejects_sha1_in_any_policy(void **state)` |
| `test_chain_rejects_weak_rsa` | function | `tests/test_secure_fetch.c:179` | `static void test_chain_rejects_weak_rsa(void **state)` |
| `test_chain_strict_accepts_pq` | function | `tests/test_secure_fetch.c:141` | `static void test_chain_strict_accepts_pq(void **state)` |
| `test_chain_strict_rejects_classical` | function | `tests/test_secure_fetch.c:132` | `static void test_chain_strict_rejects_classical(void **state)` |
| `test_config_blend_fields_default_null` | function | `tests/test_secure_fetch.c:34` | `static void test_config_blend_fields_default_null(void **state)` |
| `test_cookie_jar_put_and_header` | function | `tests/test_secure_fetch.c:516` | `static void test_cookie_jar_put_and_header(void **state)` |
| `test_cookie_line_matches_pure` | function | `tests/test_secure_fetch.c:480` | `static void test_cookie_line_matches_pure(void **state)` |
| `test_enforce_all_good_hybrid` | function | `tests/test_secure_fetch.c:201` | `static void test_enforce_all_good_hybrid(void **state)` |
| `test_enforce_allow_classical_ke` | function | `tests/test_secure_fetch.c:244` | `static void test_enforce_allow_classical_ke(void **state)` |
| `test_enforce_allowlisted_insecure` | function | `tests/test_secure_fetch.c:263` | `static void test_enforce_allowlisted_insecure(void **state)` |
| `test_enforce_checks_group_after_version` | function | `tests/test_secure_fetch.c:216` | `static void test_enforce_checks_group_after_version(void **state)` |
| `test_enforce_checks_version_first` | function | `tests/test_secure_fetch.c:207` | `static void test_enforce_checks_version_first(void **state)` |
| `test_enforce_fails_closed_on_null_chain` | function | `tests/test_secure_fetch.c:224` | `static void test_enforce_fails_closed_on_null_chain(void **state)` |
| `test_enforce_strict_requires_pq_chain` | function | `tests/test_secure_fetch.c:231` | `static void test_enforce_strict_requires_pq_chain(void **state)` |
| `test_get_follow_null_args` | function | `tests/test_secure_fetch.c:436` | `static void test_get_follow_null_args(void **state)` |
| `test_get_null_args` | function | `tests/test_secure_fetch.c:445` | `static void test_get_null_args(void **state)` |
| `test_group_accepts_hybrid` | function | `tests/test_secure_fetch.c:123` | `static void test_group_accepts_hybrid(void **state)` |
| `test_group_rejects_classical` | function | `tests/test_secure_fetch.c:109` | `static void test_group_rejects_classical(void **state)` |
| `test_group_rejects_pure_pq` | function | `tests/test_secure_fetch.c:116` | `static void test_group_rejects_pure_pq(void **state)` |
| `test_location_is_case_insensitive_and_trims` | function | `tests/test_secure_fetch.c:313` | `static void test_location_is_case_insensitive_and_trims(void **state)` |
| `test_location_parses_value` | function | `tests/test_secure_fetch.c:305` | `static void test_location_parses_value(void **state)` |
| `test_location_rejects_non_location_and_empty` | function | `tests/test_secure_fetch.c:323` | `static void test_location_rejects_non_location_and_empty(void **state)` |
| `test_location_rejects_overflow` | function | `tests/test_secure_fetch.c:335` | `static void test_location_rejects_overflow(void **state)` |
| `test_post_null_args` | function | `tests/test_secure_fetch.c:454` | `static void test_post_null_args(void **state)` |
| `test_redirect_code_recognizes_3xx` | function | `tests/test_secure_fetch.c:285` | `static void test_redirect_code_recognizes_3xx(void **state)` |
| `test_redirect_code_rejects_others` | function | `tests/test_secure_fetch.c:294` | `static void test_redirect_code_rejects_others(void **state)` |
| `test_resolve_absolute_https` | function | `tests/test_secure_fetch.c:344` | `static void test_resolve_absolute_https(void **state)` |
| `test_resolve_absolute_path` | function | `tests/test_secure_fetch.c:378` | `static void test_resolve_absolute_path(void **state)` |
| `test_resolve_null_args` | function | `tests/test_secure_fetch.c:402` | `static void test_resolve_null_args(void **state)` |
| `test_resolve_refuses_dangerous_schemes` | function | `tests/test_secure_fetch.c:359` | `static void test_resolve_refuses_dangerous_schemes(void **state)` |
| `test_resolve_refuses_http_downgrade` | function | `tests/test_secure_fetch.c:352` | `static void test_resolve_refuses_http_downgrade(void **state)` |
| `test_resolve_relative_path` | function | `tests/test_secure_fetch.c:390` | `static void test_resolve_relative_path(void **state)` |
| `test_resolve_scheme_relative` | function | `tests/test_secure_fetch.c:370` | `static void test_resolve_scheme_relative(void **state)` |
| `test_response_free_on_zeroed` | function | `tests/test_secure_fetch.c:413` | `static void test_response_free_on_zeroed(void **state)` |
| `test_response_free_releases_location` | function | `tests/test_secure_fetch.c:422` | `static void test_response_free_releases_location(void **state)` |
| `test_tls_accepts_13` | function | `tests/test_secure_fetch.c:102` | `static void test_tls_accepts_13(void **state)` |
| `test_tls_rejects_12` | function | `tests/test_secure_fetch.c:88` | `static void test_tls_rejects_12(void **state)` |
| `test_tls_rejects_older_and_garbage` | function | `tests/test_secure_fetch.c:93` | `static void test_tls_rejects_older_and_garbage(void **state)` |
| `test_url_accepts_https` | function | `tests/test_secure_fetch.c:80` | `static void test_url_accepts_https(void **state)` |
| `test_url_rejects_dangerous_schemes` | function | `tests/test_secure_fetch.c:70` | `static void test_url_rejects_dangerous_schemes(void **state)` |
| `test_url_rejects_null` | function | `tests/test_secure_fetch.c:60` | `static void test_url_rejects_null(void **state)` |
| `test_url_rejects_plain_http` | function | `tests/test_secure_fetch.c:65` | `static void test_url_rejects_plain_http(void **state)` |
| `test_user_agent_default_when_unset` | function | `tests/test_secure_fetch.c:46` | `static void test_user_agent_default_when_unset(void **state)` |
| `test_user_agent_uses_override` | function | `tests/test_secure_fetch.c:52` | `static void test_user_agent_uses_override(void **state)` |
| `test_ws_open_rejects_before_any_io` | function | `tests/test_secure_fetch.c:546` | `static void test_ws_open_rejects_before_any_io(void **state)` |
| `test_ws_url_check` | function | `tests/test_secure_fetch.c:534` | `static void test_ws_url_check(void **state)` |
| `main` | function | `tests/test_svg_render.c:328` | `int main(void)` |
| `parse` | function | `tests/test_svg_render.c:26` | `static sv_status parse(sv_image *im, const char *s)` |
| `test_basic_shapes` | function | `tests/test_svg_render.c:71` | `static void test_basic_shapes(void **state)` |
| `test_bounds_are_enforced` | function | `tests/test_svg_render.c:232` | `static void test_bounds_are_enforced(void **state)` |
| `test_dimensions_and_viewbox` | function | `tests/test_svg_render.c:50` | `static void test_dimensions_and_viewbox(void **state)` |
| `test_empty_and_garbage_do_not_parse` | function | `tests/test_svg_render.c:38` | `static void test_empty_and_garbage_do_not_parse(void **state)` |
| `test_fit_uniform_and_centered` | function | `tests/test_svg_render.c:304` | `static void test_fit_uniform_and_centered(void **state)` |
| `test_group_inheritance_and_transform` | function | `tests/test_svg_render.c:118` | `static void test_group_inheritance_and_transform(void **state)` |
| `test_malformed_values_degrade` | function | `tests/test_svg_render.c:269` | `static void test_malformed_values_degrade(void **state)` |
| `test_null_args` | function | `tests/test_svg_render.c:30` | `static void test_null_args(void **state)` |
| `test_paint_attributes` | function | `tests/test_svg_render.c:96` | `static void test_paint_attributes(void **state)` |
| `test_path_arc_reaches_endpoint` | function | `tests/test_svg_render.c:192` | `static void test_path_arc_reaches_endpoint(void **state)` |
| `test_path_commands` | function | `tests/test_svg_render.c:159` | `static void test_path_commands(void **state)` |
| `test_polygon_points` | function | `tests/test_svg_render.c:140` | `static void test_polygon_points(void **state)` |
| `test_text_element` | function | `tests/test_svg_render.c:288` | `static void test_text_element(void **state)` |
| `test_url_bearing_elements_are_dropped` | function | `tests/test_svg_render.c:208` | `static void test_url_bearing_elements_are_dropped(void **state)` |
| `CSS_PAGE` | macro | `tests/test_tab.c:1739` | `#define CSS_PAGE(HREF)` |
| `EXT_PAGE` | macro | `tests/test_tab.c:1612` | `#define EXT_PAGE(SRC)` |
| `XHR_PAGE` | macro | `tests/test_tab.c:1517` | `#define XHR_PAGE(URL)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_tab.c:14` | `#define _POSIX_C_SOURCE` |
| `console_find` | function | `tests/test_tab.c:1165` | `static const fb_entry *console_find(const fb_buffer *log, int level, const char *needle)` |
| `document` | function | `tests/test_tab.c:1831` | `* listener is on document (the React/jQuery-delegation shape);` |
| `expect_eval` | function | `tests/test_tab.c:66` | `static void expect_eval(tab *t, const char *js, const char *expected)` |
| `fixture` | struct | `tests/test_tab.c:43` | `` |
| `geom_load_and_measure` | function | `tests/test_tab.c:1891` | `static int geom_load_and_measure(int net, char *out, size_t outsz)` |
| `load` | function | `tests/test_tab.c:1881` | `* table only for a trusted load (net granted: allow.conf AND js.conf);` |
| `load_js_page` | function | `tests/test_tab.c:1934` | `static void load_js_page(tab **out_t, const char *html, tab_page *p)` |
| `ls_load` | function | `tests/test_tab.c:2169` | `static void ls_load(int net, tab **t, tab_page *p)` |
| `main` | function | `tests/test_tab.c:2873` | `int main(int argc, char **argv)` |
| `module_page` | function | `tests/test_tab.c:2247` | `static const pv_run *module_page(int net, tab **t, tab_page *p, const char *needle)` |
| `open_page` | function | `tests/test_tab.c:2062` | `static void open_page(int net, tab **t, tab_page *p)` |
| `read` | function | `tests/test_tab.c:2412` | `* vector no page may read (Zero Knowledge). Google's real JS hit exactly this. */
static void tes...` |
| `setup_loaded` | function | `tests/test_tab.c:45` | `static int setup_loaded(void **state)` |
| `stub_css_fetch` | function | `tests/test_tab.c:1722` | `static int stub_css_fetch(void *ctx, const char *method, const char *url,
                       ...` |
| `stub_fetch` | function | `tests/test_tab.c:1505` | `static int stub_fetch(void *ctx, const char *method, const char *url,
                      const...` |
| `stub_module_fetch` | function | `tests/test_tab.c:2217` | `static int stub_module_fetch(void *ctx, const char *method, const char *url,
                    ...` |
| `stub_script_fetch` | function | `tests/test_tab.c:1588` | `static int stub_script_fetch(void *ctx, const char *method, const char *url,
                    ...` |
| `teardown` | function | `tests/test_tab.c:56` | `static int teardown(void **state)` |
| `test_binary_does_not_crash_parent` | function | `tests/test_tab.c:2490` | `static void test_binary_does_not_crash_parent(void **state)` |
| `test_boxdef_node_id_crosses_codec` | function | `tests/test_tab.c:1862` | `static void test_boxdef_node_id_crosses_codec(void **state)` |
| `test_child_death_survived` | function | `tests/test_tab.c:2505` | `static void test_child_death_survived(void **state)` |
| `test_click_bubbles_to_delegated_document_listener` | function | `tests/test_tab.c:1834` | `static void test_click_bubbles_to_delegated_document_listener(void **state)` |
| `test_click_handler_navigation_reaches_parent` | function | `tests/test_tab.c:1940` | `static void test_click_handler_navigation_reaches_parent(void **state)` |
| `test_click_runs_handler_and_returns_view` | function | `tests/test_tab.c:519` | `static void test_click_runs_handler_and_returns_view(void **state)` |
| `test_data_url_classic_script_runs_without_network` | function | `tests/test_tab.c:2296` | `static void test_data_url_classic_script_runs_without_network(void **state)` |
| `test_decode_image_data_url_in_sandbox` | function | `tests/test_tab.c:2621` | `static void test_decode_image_data_url_in_sandbox(void **state)` |
| `test_decode_image_data_url_null_args` | function | `tests/test_tab.c:2663` | `static void test_decode_image_data_url_null_args(void **state)` |
| `test_decode_image_in_sandbox` | function | `tests/test_tab.c:2565` | `static void test_decode_image_in_sandbox(void **state)` |
| `test_decode_image_null_args` | function | `tests/test_tab.c:2602` | `static void test_decode_image_null_args(void **state)` |
| `test_decode_image_rejects_junk` | function | `tests/test_tab.c:2587` | `static void test_decode_image_rejects_junk(void **state)` |
| `test_eval_captures_console_output` | function | `tests/test_tab.c:1322` | `static void test_eval_captures_console_output(void **state)` |
| `test_eval_exception` | function | `tests/test_tab.c:2433` | `static void test_eval_exception(void **state)` |
| `test_eval_no_network_or_cross_origin_api` | function | `tests/test_tab.c:1486` | `static void test_eval_no_network_or_cross_origin_api(void **state)` |
| `test_eval_persistent_state` | function | `tests/test_tab.c:2445` | `static void test_eval_persistent_state(void **state)` |
| `test_eval_sees_dom` | function | `tests/test_tab.c:1459` | `static void test_eval_sees_dom(void **state)` |
| `test_eval_sees_env` | function | `tests/test_tab.c:1469` | `static void test_eval_sees_env(void **state)` |
| `test_eval_without_load` | function | `tests/test_tab.c:2478` | `static void test_eval_without_load(void **state)` |
| `test_event_ipc_via_tab_eval` | function | `tests/test_tab.c:558` | `static void test_event_ipc_via_tab_eval(void **state)` |
| `test_event_navigation_is_policy_gated` | function | `tests/test_tab.c:1983` | `static void test_event_navigation_is_policy_gated(void **state)` |
| `test_external_css_applied_when_allowed` | function | `tests/test_tab.c:1755` | `static void test_external_css_applied_when_allowed(void **state)` |
| `test_external_css_bad_ctype_not_parsed` | function | `tests/test_tab.c:1794` | `static void test_external_css_bad_ctype_not_parsed(void **state)` |
| `test_external_css_blocked_host_refused` | function | `tests/test_tab.c:1812` | `static void test_external_css_blocked_host_refused(void **state)` |
| `test_external_css_skipped_without_grant` | function | `tests/test_tab.c:1775` | `static void test_external_css_skipped_without_grant(void **state)` |
| `test_external_css_survives_click_rederive` | function | `tests/test_tab.c:2363` | `static void test_external_css_survives_click_rederive(void **state)` |
| `test_external_script_bad_ctype_not_executed` | function | `tests/test_tab.c:1682` | `static void test_external_script_bad_ctype_not_executed(void **state)` |
| `test_external_script_blocked_host_refused` | function | `tests/test_tab.c:1699` | `static void test_external_script_blocked_host_refused(void **state)` |
| `test_external_script_document_order` | function | `tests/test_tab.c:1635` | `static void test_external_script_document_order(void **state)` |
| `test_external_script_executes_when_net_allowed` | function | `tests/test_tab.c:1618` | `static void test_external_script_executes_when_net_allowed(void **state)` |
| `test_external_script_skipped_without_net` | function | `tests/test_tab.c:1658` | `static void test_external_script_skipped_without_net(void **state)` |
| `test_focus_ipc_round_trip` | function | `tests/test_tab.c:658` | `static void test_focus_ipc_round_trip(void **state)` |
| `test_free_null_and_double` | function | `tests/test_tab.c:2531` | `static void test_free_null_and_double(void **state)` |
| `test_geometry_never_reaches_untrusted_page` | function | `tests/test_tab.c:1924` | `static void test_geometry_never_reaches_untrusted_page(void **state)` |
| `test_geometry_reaches_trusted_page` | function | `tests/test_tab.c:1916` | `static void test_geometry_reaches_trusted_page(void **state)` |
| `test_history_ops_reach_parent_and_popstate_returns` | function | `tests/test_tab.c:2011` | `static void test_history_ops_reach_parent_and_popstate_returns(void **state)` |
| `test_import_map_resolves_bare_specifier` | function | `tests/test_tab.c:2275` | `static void test_import_map_resolves_bare_specifier(void **state)` |
| `test_js_navigation_relative_resolved` | function | `tests/test_tab.c:1388` | `static void test_js_navigation_relative_resolved(void **state)` |
| `test_js_navigation_unsafe_is_blocked` | function | `tests/test_tab.c:1407` | `static void test_js_navigation_unsafe_is_blocked(void **state)` |
| `test_load_basic` | function | `tests/test_tab.c:94` | `static void test_load_basic(void **state)` |
| `test_load_captures_console_and_error` | function | `tests/test_tab.c:1175` | `static void test_load_captures_console_and_error(void **state)` |
| `test_load_carries_author_color` | function | `tests/test_tab.c:169` | `static void test_load_carries_author_color(void **state)` |
| `test_load_carries_box_decoration` | function | `tests/test_tab.c:772` | `static void test_load_carries_box_decoration(void **state)` |
| `test_load_carries_box_tree` | function | `tests/test_tab.c:808` | `static void test_load_carries_box_tree(void **state)` |
| `test_load_carries_flex_item` | function | `tests/test_tab.c:196` | `static void test_load_carries_flex_item(void **state)` |
| `test_load_carries_flex_wrap_align_row_gap` | function | `tests/test_tab.c:283` | `static void test_load_carries_flex_wrap_align_row_gap(void **state)` |
| `test_load_carries_float` | function | `tests/test_tab.c:323` | `static void test_load_carries_float(void **state)` |
| `test_load_carries_input_box_and_clip` | function | `tests/test_tab.c:895` | `static void test_load_carries_input_box_and_clip(void **state)` |
| `test_load_carries_node_id` | function | `tests/test_tab.c:450` | `static void test_load_carries_node_id(void **state)` |
| `test_load_carries_oof_flag` | function | `tests/test_tab.c:484` | `static void test_load_carries_oof_flag(void **state)` |
| `test_load_carries_visibility_overflow_cursor_and_text_wrap` | function | `tests/test_tab.c:366` | `static void test_load_carries_visibility_overflow_cursor_and_text_wrap(void **state)` |
| `test_load_document_fonts_stub` | function | `tests/test_tab.c:1286` | `static void test_load_document_fonts_stub(void **state)` |
| `test_load_element_wrapper_idioms` | function | `tests/test_tab.c:1256` | `static void test_load_element_wrapper_idioms(void **state)` |
| `test_load_error_carries_location` | function | `tests/test_tab.c:1230` | `static void test_load_error_carries_location(void **state)` |
| `test_load_ex_builds_dom_and_fires_onload` | function | `tests/test_tab.c:1086` | `static void test_load_ex_builds_dom_and_fires_onload(void **state)` |
| `test_load_ex_inner_html_renders` | function | `tests/test_tab.c:1114` | `static void test_load_ex_inner_html_renders(void **state)` |
| `test_load_ex_noscript_hidden_with_js` | function | `tests/test_tab.c:987` | `static void test_load_ex_noscript_hidden_with_js(void **state)` |
| `test_load_full_location_is_real` | function | `tests/test_tab.c:1351` | `static void test_load_full_location_is_real(void **state)` |
| `test_load_isolates_script_errors` | function | `tests/test_tab.c:1202` | `static void test_load_isolates_script_errors(void **state)` |
| `test_load_no_session_cookies_when_untrusted` | function | `tests/test_tab.c:1064` | `static void test_load_no_session_cookies_when_untrusted(void **state)` |
| `test_load_null_and_too_large` | function | `tests/test_tab.c:1443` | `static void test_load_null_and_too_large(void **state)` |
| `test_load_returns_image_run` | function | `tests/test_tab.c:138` | `static void test_load_returns_image_run(void **state)` |
| `test_load_returns_view_with_link` | function | `tests/test_tab.c:111` | `static void test_load_returns_view_with_link(void **state)` |
| `test_load_strips_script` | function | `tests/test_tab.c:941` | `static void test_load_strips_script(void **state)` |
| `test_load_view_codec_full_roundtrip` | function | `tests/test_tab.c:2723` | `static void test_load_view_codec_full_roundtrip(void **state)` |
| `test_load_without_js_has_empty_console` | function | `tests/test_tab.c:1306` | `static void test_load_without_js_has_empty_console(void **state)` |
| `test_local_storage_never_seeded_for_untrusted` | function | `tests/test_tab.c:2205` | `static void test_local_storage_never_seeded_for_untrusted(void **state)` |
| `test_local_storage_seeded_and_collected_for_trusted` | function | `tests/test_tab.c:2183` | `static void test_local_storage_seeded_and_collected_for_trusted(void **state)` |
| `test_long_data_module_runs_whole` | function | `tests/test_tab.c:2316` | `static void test_long_data_module_runs_whole(void **state)` |
| `test_module_scripts_run_for_trusted_host` | function | `tests/test_tab.c:2256` | `static void test_module_scripts_run_for_trusted_host(void **state)` |
| `test_module_src_is_a_url_and_data_modules_run` | function | `tests/test_tab.c:2341` | `static void test_module_src_is_a_url_and_data_modules_run(void **state)` |
| `test_mouse_ipc_round_trip` | function | `tests/test_tab.c:613` | `static void test_mouse_ipc_round_trip(void **state)` |
| `test_no_js_no_navigation` | function | `tests/test_tab.c:1429` | `static void test_no_js_no_navigation(void **state)` |
| `test_nomodule_fallback_for_untrusted_host` | function | `tests/test_tab.c:2265` | `static void test_nomodule_fallback_for_untrusted_host(void **state)` |
| `test_open_close` | function | `tests/test_tab.c:77` | `static void test_open_close(void **state)` |
| `test_open_null` | function | `tests/test_tab.c:87` | `static void test_open_null(void **state)` |
| `test_reload_replaces_page` | function | `tests/test_tab.c:2454` | `static void test_reload_replaces_page(void **state)` |
| `test_subreq_permitted_pure` | function | `tests/test_tab.c:2391` | `static void test_subreq_permitted_pure(void **state)` |
| `test_tick_fires_delayed_timer` | function | `tests/test_tab.c:705` | `static void test_tick_fires_delayed_timer(void **state)` |
| `test_tick_interval_rearms` | function | `tests/test_tab.c:742` | `static void test_tick_interval_rearms(void **state)` |
| `test_timer_navigation_reaches_parent` | function | `tests/test_tab.c:1961` | `static void test_timer_navigation_reaches_parent(void **state)` |
| `test_websocket_absent_for_untrusted_host` | function | `tests/test_tab.c:2144` | `static void test_websocket_absent_for_untrusted_host(void **state)` |
| `test_websocket_ops_and_events_cross_the_worker` | function | `tests/test_tab.c:2117` | `static void test_websocket_ops_and_events_cross_the_worker(void **state)` |
| `test_window_open_absent_for_untrusted_host` | function | `tests/test_tab.c:2090` | `static void test_window_open_absent_for_untrusted_host(void **state)` |
| `test_window_open_on_gesture_for_trusted_host` | function | `tests/test_tab.c:2069` | `static void test_window_open_on_gesture_for_trusted_host(void **state)` |
| `test_worker_args_malformed` | function | `tests/test_tab.c:2692` | `static void test_worker_args_malformed(void **state)` |
| `test_worker_args_not_worker` | function | `tests/test_tab.c:2685` | `static void test_worker_args_not_worker(void **state)` |
| `test_worker_args_null_safe` | function | `tests/test_tab.c:2707` | `static void test_worker_args_null_safe(void **state)` |
| `test_worker_args_valid` | function | `tests/test_tab.c:2676` | `static void test_worker_args_valid(void **state)` |
| `test_xhr_undefined_when_net_not_allowed` | function | `tests/test_tab.c:1548` | `static void test_xhr_undefined_when_net_not_allowed(void **state)` |
| `test_xhr_works_when_net_allowed` | function | `tests/test_tab.c:1524` | `static void test_xhr_works_when_net_allowed(void **state)` |
| `view_find_text` | function | `tests/test_tab.c:1744` | `static const pv_run *view_find_text(const pv_view *v, const char *needle)` |
| `main` | function | `tests/test_text_shape.c:149` | `int main(void)` |
| `teardown` | function | `tests/test_text_shape.c:143` | `static int teardown(void **state)` |
| `test_determinism` | function | `tests/test_text_shape.c:92` | `static void test_determinism(void **state)` |
| `test_draw_paints` | function | `tests/test_text_shape.c:130` | `static void test_draw_paints(void **state)` |
| `test_empty_slice_is_ok` | function | `tests/test_text_shape.c:57` | `static void test_empty_slice_is_ok(void **state)` |
| `test_measure_matches_shape` | function | `tests/test_text_shape.c:108` | `static void test_measure_matches_shape(void **state)` |
| `test_null_and_bad_inputs` | function | `tests/test_text_shape.c:27` | `static void test_null_and_bad_inputs(void **state)` |
| `test_overflow_cap` | function | `tests/test_text_shape.c:120` | `static void test_overflow_cap(void **state)` |
| `test_shape_ascii` | function | `tests/test_text_shape.c:70` | `static void test_shape_ascii(void **state)` |
| `main` | function | `tests/test_textfield.c:140` | `int main(void)` |
| `test_backspace_delete` | function | `tests/test_textfield.c:76` | `static void test_backspace_delete(void **state)` |
| `test_full_fails_closed` | function | `tests/test_textfield.c:113` | `static void test_full_fails_closed(void **state)` |
| `test_init_and_accessors` | function | `tests/test_textfield.c:20` | `static void test_init_and_accessors(void **state)` |
| `test_insert_sequence` | function | `tests/test_textfield.c:59` | `static void test_insert_sequence(void **state)` |
| `test_move_saturates` | function | `tests/test_textfield.c:100` | `static void test_move_saturates(void **state)` |
| `test_null_safe` | function | `tests/test_textfield.c:29` | `static void test_null_safe(void **state)` |
| `test_set` | function | `tests/test_textfield.c:46` | `static void test_set(void **state)` |
| `main` | function | `tests/test_tls_impersonate.c:218` | `int main(void)` |
| `test_decode_rejects_bad_magic` | function | `tests/test_tls_impersonate.c:163` | `static void test_decode_rejects_bad_magic(void **state)` |
| `test_decode_rejects_overlong_field` | function | `tests/test_tls_impersonate.c:177` | `static void test_decode_rejects_overlong_field(void **state)` |
| `test_decode_rejects_truncated` | function | `tests/test_tls_impersonate.c:144` | `static void test_decode_rejects_truncated(void **state)` |
| `test_encode_decode_req_empty_body` | function | `tests/test_tls_impersonate.c:65` | `static void test_encode_decode_req_empty_body(void **state)` |
| `test_encode_decode_req_roundtrip` | function | `tests/test_tls_impersonate.c:39` | `static void test_encode_decode_req_roundtrip(void **state)` |
| `test_encode_decode_resp_roundtrip` | function | `tests/test_tls_impersonate.c:89` | `static void test_encode_decode_resp_roundtrip(void **state)` |
| `test_encode_fails_when_no_room` | function | `tests/test_tls_impersonate.c:192` | `static void test_encode_fails_when_no_room(void **state)` |
| `test_encode_rejects_oversize_url` | function | `tests/test_tls_impersonate.c:203` | `static void test_encode_rejects_oversize_url(void **state)` |
| `test_gate_requires_all_three_signals` | function | `tests/test_tls_impersonate.c:22` | `static void test_gate_requires_all_three_signals(void **state)` |
| `test_resp_no_chain_ok` | function | `tests/test_tls_impersonate.c:121` | `static void test_resp_no_chain_ok(void **state)` |
| `assert_line` | function | `tests/test_ui.c:20` | `static void assert_line(const char *text, const ui_layout *lay, size_t n,
                       ...` |
| `main` | function | `tests/test_ui.c:130` | `int main(void)` |
| `test_clamp_scroll` | function | `tests/test_ui.c:113` | `static void test_clamp_scroll(void **state)` |
| `test_layout_free_null_and_double` | function | `tests/test_ui.c:121` | `static void test_layout_free_null_and_double(void **state)` |
| `test_wrap_breaks_at_space` | function | `tests/test_ui.c:53` | `static void test_wrap_breaks_at_space(void **state)` |
| `test_wrap_does_not_split_utf8` | function | `tests/test_ui.c:76` | `static void test_wrap_does_not_split_utf8(void **state)` |
| `test_wrap_empty` | function | `tests/test_ui.c:35` | `static void test_wrap_empty(void **state)` |
| `test_wrap_hard_breaks_long_word` | function | `tests/test_ui.c:64` | `static void test_wrap_hard_breaks_long_word(void **state)` |
| `test_wrap_null_args` | function | `tests/test_ui.c:28` | `static void test_wrap_null_args(void **state)` |
| `test_wrap_respects_newline` | function | `tests/test_ui.c:90` | `static void test_wrap_respects_newline(void **state)` |
| `test_wrap_short_single_line` | function | `tests/test_ui.c:43` | `static void test_wrap_short_single_line(void **state)` |
| `test_wrap_zero_cols_is_sanitised` | function | `tests/test_ui.c:101` | `static void test_wrap_zero_cols_is_sanitised(void **state)` |
| `assert_span` | function | `tests/test_url.c:449` | `static void assert_span(const char *p, size_t len, const char *expect)` |
| `main` | function | `tests/test_url.c:701` | `int main(void)` |
| `test_authority_len` | function | `tests/test_url.c:86` | `static void test_authority_len(void **state)` |
| `test_extract_userinfo_at_authority_start` | function | `tests/test_url.c:589` | `static void test_extract_userinfo_at_authority_start(void **state)` |
| `test_extract_userinfo_basic` | function | `tests/test_url.c:516` | `static void test_extract_userinfo_basic(void **state)` |
| `test_extract_userinfo_empty_password` | function | `tests/test_url.c:615` | `static void test_extract_userinfo_empty_password(void **state)` |
| `test_extract_userinfo_https_subresource_no_auth` | function | `tests/test_url.c:566` | `static void test_extract_userinfo_https_subresource_no_auth(void **state)` |
| `test_extract_userinfo_no_at_sign` | function | `tests/test_url.c:602` | `static void test_extract_userinfo_no_at_sign(void **state)` |
| `test_extract_userinfo_no_userinfo` | function | `tests/test_url.c:542` | `static void test_extract_userinfo_no_userinfo(void **state)` |
| `test_extract_userinfo_non_https_passthrough` | function | `tests/test_url.c:554` | `static void test_extract_userinfo_non_https_passthrough(void **state)` |
| `test_extract_userinfo_nulls` | function | `tests/test_url.c:579` | `static void test_extract_userinfo_nulls(void **state)` |
| `test_extract_userinfo_user_only` | function | `tests/test_url.c:529` | `static void test_extract_userinfo_user_only(void **state)` |
| `test_has_scheme` | function | `tests/test_url.c:69` | `static void test_has_scheme(void **state)` |
| `test_history_target_bad_args` | function | `tests/test_url.c:690` | `static void test_history_target_bad_args(void **state)` |
| `test_history_target_cross_origin_rejected` | function | `tests/test_url.c:662` | `static void test_history_target_cross_origin_rejected(void **state)` |
| `test_history_target_file_query_fragment_only` | function | `tests/test_url.c:677` | `static void test_history_target_file_query_fragment_only(void **state)` |
| `test_history_target_same_origin` | function | `tests/test_url.c:641` | `static void test_history_target_same_origin(void **state)` |
| `test_is_file_and_path` | function | `tests/test_url.c:379` | `static void test_is_file_and_path(void **state)` |
| `test_is_https` | function | `tests/test_url.c:23` | `static void test_is_https(void **state)` |
| `test_omnibox_bare_host_gets_https` | function | `tests/test_url.c:251` | `static void test_omnibox_bare_host_gets_https(void **state)` |
| `test_omnibox_foreign_scheme_is_searched_not_executed` | function | `tests/test_url.c:298` | `static void test_omnibox_foreign_scheme_is_searched_not_executed(void **state)` |
| `test_omnibox_http_upgraded_to_https` | function | `tests/test_url.c:268` | `static void test_omnibox_http_upgraded_to_https(void **state)` |
| `test_omnibox_navigate_https` | function | `tests/test_url.c:238` | `static void test_omnibox_navigate_https(void **state)` |
| `test_omnibox_nulls_and_empty` | function | `tests/test_url.c:311` | `static void test_omnibox_nulls_and_empty(void **state)` |
| `test_omnibox_search_for_queries` | function | `tests/test_url.c:278` | `static void test_omnibox_search_for_queries(void **state)` |
| `test_remove_dot_segments` | function | `tests/test_url.c:98` | `static void test_remove_dot_segments(void **state)` |
| `test_remove_dot_segments_nulls` | function | `tests/test_url.c:127` | `static void test_remove_dot_segments_nulls(void **state)` |
| `test_resolve_absolute` | function | `tests/test_url.c:138` | `static void test_resolve_absolute(void **state)` |
| `test_resolve_absolute_path` | function | `tests/test_url.c:169` | `static void test_resolve_absolute_path(void **state)` |
| `test_resolve_dot_segments` | function | `tests/test_url.c:193` | `static void test_resolve_dot_segments(void **state)` |
| `test_resolve_fail_closed_on_bad_base` | function | `tests/test_url.c:210` | `static void test_resolve_fail_closed_on_bad_base(void **state)` |
| `test_resolve_file_confinement_fail_closed` | function | `tests/test_url.c:411` | `static void test_resolve_file_confinement_fail_closed(void **state)` |
| `test_resolve_file_nulls` | function | `tests/test_url.c:437` | `static void test_resolve_file_nulls(void **state)` |
| `test_resolve_file_relative` | function | `tests/test_url.c:391` | `static void test_resolve_file_relative(void **state)` |
| `test_resolve_null_and_overflow` | function | `tests/test_url.c:222` | `static void test_resolve_null_and_overflow(void **state)` |
| `test_resolve_rejects_downgrade_and_schemes` | function | `tests/test_url.c:146` | `static void test_resolve_rejects_downgrade_and_schemes(void **state)` |
| `test_resolve_relative_path` | function | `tests/test_url.c:181` | `static void test_resolve_relative_path(void **state)` |
| `test_resolve_scheme_relative` | function | `tests/test_url.c:161` | `static void test_resolve_scheme_relative(void **state)` |
| `test_search_rewrite_ddg_spa` | function | `tests/test_url.c:327` | `static void test_search_rewrite_ddg_spa(void **state)` |
| `test_search_rewrite_leaves_others_alone` | function | `tests/test_url.c:344` | `static void test_search_rewrite_leaves_others_alone(void **state)` |
| `test_search_rewrite_nulls` | function | `tests/test_url.c:364` | `static void test_search_rewrite_nulls(void **state)` |
| `test_split_fail_closed_non_https` | function | `tests/test_url.c:628` | `static void test_split_fail_closed_non_https(void **state)` |
| `test_split_fragment_without_query` | function | `tests/test_url.c:495` | `static void test_split_fragment_without_query(void **state)` |
| `test_split_full_url` | function | `tests/test_url.c:454` | `static void test_split_full_url(void **state)` |
| `test_split_ipv6_literal_with_port` | function | `tests/test_url.c:504` | `static void test_split_ipv6_literal_with_port(void **state)` |
| `test_split_no_port_no_path` | function | `tests/test_url.c:473` | `static void test_split_no_port_no_path(void **state)` |
| `test_split_query_without_fragment` | function | `tests/test_url.c:486` | `static void test_split_query_without_fragment(void **state)` |
| `test_validate_https` | function | `tests/test_url.c:36` | `static void test_validate_https(void **state)` |
| `test_validate_long_bundle_url` | function | `tests/test_url.c:49` | `static void test_validate_long_bundle_url(void **state)` |
| `build` | function | `tests/test_web_storage.c:24` | `static size_t build(char *b, const char *const *kv, uint32_t n)` |
| `count_pair` | function | `tests/test_web_storage.c:147` | `static void count_pair(void *ctx, const char *k, size_t kl, const char *v, size_t vl)` |
| `main` | function | `tests/test_web_storage.c:182` | `int main(void)` |
| `test_hostile_snapshots_rejected_and_db_unchanged` | function | `tests/test_web_storage.c:73` | `static void test_hostile_snapshots_rejected_and_db_unchanged(void **state)` |
| `test_origin_table_is_bounded_lru` | function | `tests/test_web_storage.c:129` | `static void test_origin_table_is_bounded_lru(void **state)` |
| `test_pack_foreach_roundtrip` | function | `tests/test_web_storage.c:154` | `static void test_pack_foreach_roundtrip(void **state)` |
| `test_quota_enforced` | function | `tests/test_web_storage.c:112` | `static void test_quota_enforced(void **state)` |
| `test_replace_then_encode_roundtrip` | function | `tests/test_web_storage.c:49` | `static void test_replace_then_encode_roundtrip(void **state)` |
| `test_unknown_origin_encodes_empty` | function | `tests/test_web_storage.c:34` | `static void test_unknown_origin_encodes_empty(void **state)` |
| `assert_memory_equal` | function | `tests/test_webcaps.c:176` | `assert_memory_equal(&(rdp_caps)` |
| `main` | function | `tests/test_webcaps.c:181` | `int main(void)` |
| `mk` | function | `tests/test_webcaps.c:20` | `static wc_input mk(jsp_mode mode, int in_js, int in_allow)` |
| `test_bad_mode_fails_closed` | function | `tests/test_webcaps.c:127` | `static void test_bad_mode_fails_closed(void **state)` |
| `test_from_flags_headless` | function | `tests/test_webcaps.c:153` | `static void test_from_flags_headless(void **state)` |
| `test_jspon_alone_is_not_trust` | function | `tests/test_webcaps.c:85` | `static void test_jspon_alone_is_not_trust(void **state)` |
| `test_present_trust_css_images_only` | function | `tests/test_webcaps.c:56` | `static void test_present_trust_css_images_only(void **state)` |
| `test_render_caps_projection` | function | `tests/test_webcaps.c:138` | `static void test_render_caps_projection(void **state)` |
| `test_safe_is_all_off` | function | `tests/test_webcaps.c:29` | `static void test_safe_is_all_off(void **state)` |
| `test_trusted_host_gets_all_caps` | function | `tests/test_webcaps.c:38` | `static void test_trusted_host_gets_all_caps(void **state)` |
| `test_user_toggles_grant_leakfree` | function | `tests/test_webcaps.c:100` | `static void test_user_toggles_grant_leakfree(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_ws_hub.c:7` | `#define _POSIX_C_SOURCE` |
| `emit` | function | `tests/test_ws_hub.c:21` | `static void emit(void *ctx, int id, int kind, int code, const char *data, size_t len)` |
| `main` | function | `tests/test_ws_hub.c:142` | `int main(void)` |
| `n` | type_alias | `tests/test_ws_hub.c:18` | `typedef struct rec { int n;` |
| `rec` | struct | `tests/test_ws_hub.c:19` | `` |
| `test_close_all_drops_late_results` | function | `tests/test_ws_hub.c:85` | `static void test_close_all_drops_late_results(void **state)` |
| `test_close_cancels_pending_open` | function | `tests/test_ws_hub.c:102` | `static void test_close_cancels_pending_open(void **state)` |
| `test_duplicate_and_capacity` | function | `tests/test_ws_hub.c:64` | `static void test_duplicate_and_capacity(void **state)` |
| `test_failed_open_reports_error_then_close` | function | `tests/test_ws_hub.c:47` | `static void test_failed_open_reports_error_then_close(void **state)` |
| `test_free_with_pending_open` | function | `tests/test_ws_hub.c:132` | `static void test_free_with_pending_open(void **state)` |
| `test_new_free` | function | `tests/test_ws_hub.c:34` | `static void test_new_free(void **state)` |
| `test_send_unknown_and_readable_unknown` | function | `tests/test_ws_hub.c:115` | `static void test_send_unknown_and_readable_unknown(void **state)` |
| `wait_notify` | function | `tests/test_ws_hub.c:28` | `static void wait_notify(wh_hub *h, rec *r)` |
| `main` | function | `tests/test_zoom.c:112` | `int main(void)` |
| `test_apply_scales_and_floors` | function | `tests/test_zoom.c:100` | `static void test_apply_scales_and_floors(void **state)` |
| `test_clamp_bounds` | function | `tests/test_zoom.c:17` | `static void test_clamp_bounds(void **state)` |
| `test_ends_are_idempotent` | function | `tests/test_zoom.c:59` | `static void test_ends_are_idempotent(void **state)` |
| `test_repeated_in_reaches_max` | function | `tests/test_zoom.c:67` | `static void test_repeated_in_reaches_max(void **state)` |
| `test_repeated_out_reaches_min` | function | `tests/test_zoom.c:79` | `static void test_repeated_out_reaches_min(void **state)` |
| `test_reset_is_default` | function | `tests/test_zoom.c:27` | `static void test_reset_is_default(void **state)` |
| `test_scale_factor` | function | `tests/test_zoom.c:91` | `static void test_scale_factor(void **state)` |
| `test_step_snaps_off_ladder` | function | `tests/test_zoom.c:49` | `static void test_step_snaps_off_ladder(void **state)` |
| `test_zoom_in_steps_ladder` | function | `tests/test_zoom.c:33` | `static void test_zoom_in_steps_ladder(void **state)` |
| `test_zoom_out_steps_ladder` | function | `tests/test_zoom.c:41` | `static void test_zoom_out_steps_ladder(void **state)` |
| `_append_probe` | function | `tools/ffgeom.py:237` | `def _append_probe(src, script)` |
| `_word_reader` | function | `tools/ffgeom.py:156` | `def _word_reader(path)` |
| `bit` | function | `tools/ffgeom.py:189` | `def bit(grid_row, cell, origin)` |
| `decode` | function | `tools/ffgeom.py:222` | `def decode(path)` |
| `height` | function | `tools/ffgeom.py:275` | `def height(path)` |
| `height_probe` | function | `tools/ffgeom.py:262` | `def height_probe(page, out_html)` |
| `load_rows` | function | `tools/ffgeom.py:99` | `def load_rows(path)` |
| `lum` | function | `tools/ffgeom.py:152` | `def lum(p)` |
| `lum_at` | function | `tools/ffgeom.py:164` | `def lum_at(x, y)` |
| `main` | function | `tools/ffgeom.py:284` | `def main(argv)` |
| `probe` | function | `tools/ffgeom.py:248` | `def probe(page, selector, out_html)` |
| `word` | function | `tools/ffgeom.py:192` | `def word(grid_row, origin)` |
| `_POSIX_C_SOURCE` | macro | `tools/gen_psl.c:15` | `#define _POSIX_C_SOURCE` |
| `ascii_lower` | function | `tools/gen_psl.c:55` | `static void ascii_lower(char *s)` |
| `cmp_str` | function | `tools/gen_psl.c:38` | `static int cmp_str(const void *a, const void *b)` |
| `emit` | function | `tools/gen_psl.c:61` | `static void emit(const char *name, vec *v)` |
| `main` | function | `tools/gen_psl.c:67` | `int main(int argc, char **argv)` |
| `sort_unique` | function | `tools/gen_psl.c:43` | `static void sort_unique(vec *v)` |
| `vec` | struct | `tools/gen_psl.c:21` | `` |
| `vec_push` | function | `tools/gen_psl.c:27` | `static void vec_push(vec *v, const char *s)` |
| `find_modules` | function | `tools/mutate.py:107` | `def find_modules(root)` |
| `line_sites` | function | `tools/mutate.py:41` | `def line_sites(text)` |
| `main` | function | `tools/mutate.py:137` | `def main(argv)` |
| `mutate_line` | function | `tools/mutate.py:75` | `def mutate_line(line, op)` |
| `run_bin` | function | `tools/mutate.py:125` | `def run_bin(path)` |
| `run_make` | function | `tools/mutate.py:116` | `def run_make(root, target)` |
| `PD_COLS` | macro | `tools/pngdiff.c:57` | `#define PD_COLS` |
| `PD_INK_DELTA` | macro | `tools/pngdiff.c:63` | `#define PD_INK_DELTA` |
| `PD_ROWS` | macro | `tools/pngdiff.c:58` | `#define PD_ROWS` |
| `height` | type_alias | `tools/pngdiff.c:64` | `typedef struct pd_profile { uint32_t width, height;` |
| `main` | function | `tools/pngdiff.c:233` | `int main(int argc, char **argv)` |
| `pd_background` | function | `tools/pngdiff.c:147` | `static int pd_background(const char *path, double *out_bg)` |
| `pd_lum` | function | `tools/pngdiff.c:141` | `static double pd_lum(const png_byte *p)` |
| `pd_mae` | function | `tools/pngdiff.c:227` | `static double pd_mae(const double *a, const double *b, size_t n)` |
| `pd_profile` | struct | `tools/pngdiff.c:65` | `` |
| `pd_profile_of` | function | `tools/pngdiff.c:175` | `static int pd_profile_of(const char *path, pd_profile *out)` |
| `pd_reader` | struct | `tools/pngdiff.c:71` | `` |
| `pd_reader_close` | function | `tools/pngdiff.c:79` | `static void pd_reader_close(pd_reader *r)` |
| `pd_reader_open` | function | `tools/pngdiff.c:88` | `static int pd_reader_open(pd_reader *r, const char *path)` |
| `png_set_background` | function | `tools/pngdiff.c:116` | `png_set_background(r->png, &(png_color_16)` |
| `load_rows` | function | `tools/pngprof.py:41` | `def load_rows(path)` |
| `lum` | function | `tools/pngprof.py:95` | `def lum(p)` |
| `main` | function | `tools/pngprof.py:109` | `def main(argv)` |
| `render_glyph` | function | `tools/pngprof.py:99` | `def render_glyph(v)` |
| `expand_imports` | function | `tools/snapshot.py:31` | `def expand_imports(css, base, depth)` |
| `fetch` | function | `tools/snapshot.py:17` | `def fetch(url)` |
| `inline_css` | function | `tools/snapshot.py:48` | `def inline_css(html, base)` |
| `main` | function | `tools/snapshot.py:69` | `def main()` |
| `repl` | function | `tools/snapshot.py:34` | `def repl(m)` |
| `repl` | function | `tools/snapshot.py:49` | `def repl(m)` |
