# Symbols

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `list_unique_crashes` | function | `app.py:39` | `def list_unique_crashes()` |
| `read_fuzz_stats` | function | `app.py:30` | `def read_fuzz_stats()` |
| `run_freedom_headless` | function | `app.py:47` | `def run_freedom_headless(payload_path)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_css.c:61` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `check_style` | function | `fuzz/fuzz_css.c:77` | `check_style(css_resolve(sh, "p", NULL, NULL, 0, inl, 0));` |
| `css_free` | function | `fuzz/fuzz_css.c:102` | `css_free(sh);` |
| `free` | function | `fuzz/fuzz_css.c:120` | `free(buf);` |
| `memcpy` | function | `fuzz/fuzz_css.c:65` | `memcpy(buf, data, size);` |
| `abort` | function | `fuzz/fuzz_data_url.c:39` | `abort();` |
| `free` | function | `fuzz/fuzz_data_url.c:37` | `free(out);` |
| `memcpy` | function | `fuzz/fuzz_data_url.c:21` | `memcpy(buf, data, size);` |
| `worker` | function | `fuzz/fuzz_data_url.c:5` | `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, never
 * interpreted...` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_dom.c:47` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `ensure_built` | function | `fuzz/fuzz_dom.c:40` | `static void ensure_built(void)` |
| `memcpy` | function | `fuzz/fuzz_dom.c:54` | `memcpy(sel, data, n);` |
| `hp_document_free` | function | `fuzz/fuzz_dom_debug.c:27` | `hp_document_free(doc);` |
| `memset` | function | `fuzz/fuzz_dom_debug.c:42` | `memset(guard, 0xAA, sizeof guard);` |
| `pass` | function | `fuzz/fuzz_dom_debug.c:8` | `* the measure pass (cap 0) must agree with the would-write return value.
 *
 * Build & run: make ...` |
| `pv_free` | function | `fuzz/fuzz_dom_debug.c:58` | `pv_free(v);` |
| `rd_free` | function | `fuzz/fuzz_dom_debug.c:56` | `rd_free(rd);` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_download.c:30` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `check_name` | function | `fuzz/fuzz_download.c:49` | `check_name(name);` |
| `free` | function | `fuzz/fuzz_download.c:62` | `free(buf);` |
| `memcpy` | function | `fuzz/fuzz_download.c:34` | `memcpy(buf, data, size);` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_freebug.c:36` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `check_invariants` | function | `fuzz/fuzz_freebug.c:71` | `check_invariants(&b);` |
| `fb_buffer_free` | function | `fuzz/fuzz_freebug.c:77` | `fb_buffer_free(&b);` |
| `fb_buffer_init` | function | `fuzz/fuzz_freebug.c:39` | `fb_buffer_init(&b);` |
| `fb_buffer_push` | function | `fuzz/fuzz_freebug.c:64` | `fb_buffer_push(&b, level, txt, len);` |
| `fb_buffer_push_loc` | function | `fuzz/fuzz_freebug.c:62` | `fb_buffer_push_loc(&b, level, txt, len, fbuf, line, -(int)len);` |
| `fb_buffer_reset` | function | `fuzz/fuzz_freebug.c:72` | `fb_buffer_reset(&b);` |
| `hp_document_free` | function | `fuzz/fuzz_html_parse.c:56` | `hp_document_free(doc);` |
| `hp_free` | function | `fuzz/fuzz_html_parse.c:23` | `hp_free(text);` |
| `hp_free_scripts` | function | `fuzz/fuzz_html_parse.c:39` | `hp_free_scripts(scripts, nscripts);` |
| `hp_free_stylesheet_hrefs` | function | `fuzz/fuzz_html_parse.c:50` | `hp_free_stylesheet_hrefs(hrefs, nsheets);` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_image_decode.c:31` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `img_pixels_free` | function | `fuzz/fuzz_image_decode.c:29` | `img_pixels_free(px);` |
| `poke_and_free` | function | `fuzz/fuzz_image_decode.c:21` | `static void poke_and_free(img_pixels *px)` |
| `free` | function | `fuzz/fuzz_js_sandbox.c:30` | `free(nt);` |
| `js_eval_once` | function | `fuzz/fuzz_js_sandbox.c:39` | `js_eval_once((const char *)data, size, &lim, &r);` |
| `js_result_free` | function | `fuzz/fuzz_js_sandbox.c:40` | `js_result_free(&r);` |
| `hp_document_free` | function | `fuzz/fuzz_page_view.c:48` | `hp_document_free(doc);` |
| `pv_free` | function | `fuzz/fuzz_page_view.c:45` | `pv_free(v);` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_pdf_export.c:29` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `check_basename` | function | `fuzz/fuzz_pdf_export.c:39` | `check_basename(base);` |
| `free` | function | `fuzz/fuzz_pdf_export.c:56` | `free(title);` |
| `memcpy` | function | `fuzz/fuzz_pdf_export.c:34` | `memcpy(title, data, size);` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_prefetch.c:9` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `pf_list_free` | function | `fuzz/fuzz_prefetch.c:14` | `pf_list_free(&l);` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_prefs.c:20` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `free` | function | `fuzz/fuzz_prefs.c:34` | `free(glued);` |
| `memcpy` | function | `fuzz/fuzz_prefs.c:32` | `memcpy(glued + off, data, size);` |
| `prefs_bookmark_toggle` | function | `fuzz/fuzz_prefs.c:43` | `prefs_bookmark_toggle(&p, "https://fuzz.test/", s, &added);` |
| `prefs_free` | function | `fuzz/fuzz_prefs.c:61` | `prefs_free(&q);` |
| `prefs_history_add` | function | `fuzz/fuzz_prefs.c:45` | `prefs_history_add(&p, s);` |
| `prefs_init` | function | `fuzz/fuzz_prefs.c:23` | `prefs_init(&p);` |
| `prefs_parse` | function | `fuzz/fuzz_prefs.c:27` | `prefs_parse((const char *)data, size, &p);` |
| `prefs_suggest` | function | `fuzz/fuzz_prefs.c:47` | `prefs_suggest(&p, s, (char *)rows, sizeof rows[0], 4);` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_svg_render.c:23` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `free` | function | `fuzz/fuzz_svg_render.c:34` | `free(im);` |
| `sv_fit` | function | `fuzz/fuzz_svg_render.c:81` | `sv_fit(im, dims[a], dims[b], &sc, &ox, &oy);` |
| `FZ_CAP` | macro | `fuzz/fuzz_text_shape.c:22` | `#define FZ_CAP` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_text_shape.c:24` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `cairo_set_source_rgb` | function | `fuzz/fuzz_text_shape.c:70` | `cairo_set_source_rgb(cr, 0, 0, 0);` |
| `cairo_surface_destroy` | function | `fuzz/fuzz_text_shape.c:67` | `cairo_surface_destroy(s);` |
| `tsh_draw` | function | `fuzz/fuzz_text_shape.c:71` | `tsh_draw(cr, &f, px, 2.0, 16.0, text, len);` |
| `free` | function | `fuzz/fuzz_tls_impersonate.c:27` | `free(buf);` |
| `ti_req_free` | function | `fuzz/fuzz_tls_impersonate.c:29` | `ti_req_free(&rq);` |
| `ti_resp_free` | function | `fuzz/fuzz_tls_impersonate.c:43` | `ti_resp_free(&rp);` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_url.c:57` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `abort` | function | `fuzz/fuzz_url.c:85` | `abort();` |
| `check_split` | function | `fuzz/fuzz_url.c:29` | `static void check_split(const char *url)` |
| `free` | function | `fuzz/fuzz_url.c:89` | `free(buf);` |
| `in_bounds` | function | `fuzz/fuzz_url.c:37` | `in_bounds(u.protocol, u.protocol_len, url, total);` |
| `memcpy` | function | `fuzz/fuzz_url.c:61` | `memcpy(buf, data, size);` |
| `ALIVE` | function | `gui/browser_ui.c:2179` | `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or a ta` |
| `BUI_CONIC_SLICES` | macro | `gui/browser_ui.c:8868` | `#define BUI_CONIC_SLICES` |
| `FBW_COPY_BTN_H` | macro | `gui/browser_ui.c:12858` | `#define FBW_COPY_BTN_H` |
| `FBW_COPY_BTN_W` | macro | `gui/browser_ui.c:12857` | `#define FBW_COPY_BTN_W` |
| `FBW_GUTTER` | macro | `gui/browser_ui.c:12854` | `#define FBW_GUTTER` |
| `FBW_H` | macro | `gui/browser_ui.c:12850` | `#define FBW_H` |
| `FBW_HEADER` | macro | `gui/browser_ui.c:12851` | `#define FBW_HEADER` |
| `FBW_LINE` | macro | `gui/browser_ui.c:12853` | `#define FBW_LINE` |
| `FBW_MAX_SPLIT` | macro | `gui/browser_ui.c:12856` | `#define FBW_MAX_SPLIT` |
| `FBW_MIN_SPLIT` | macro | `gui/browser_ui.c:12855` | `#define FBW_MIN_SPLIT` |
| `FBW_PAD` | macro | `gui/browser_ui.c:12852` | `#define FBW_PAD` |
| `FBW_W` | macro | `gui/browser_ui.c:12848` | `#define FBW_W` |
| `FLEX_MEASURE_W` | macro | `gui/browser_ui.c:4562` | `#define FLEX_MEASURE_W` |
| `FLEX_MIN_MEASURE_W` | macro | `gui/browser_ui.c:4567` | `#define FLEX_MIN_MEASURE_W` |
| `FcFini` | function | `gui/browser_ui.c:15203` | `FcFini();` |
| `GET` | function | `gui/browser_ui.c:1326` | `* a GET (Zero Trust). cfg->policy is restored before returning. */
static sf_status fetch_post_na...` |
| `GET` | function | `gui/browser_ui.c:11771` | `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...` |
| `H2R` | macro | `gui/browser_ui.c:10168` | `#define H2R(p,q,t)` |
| `HarfBuzz` | function | `gui/browser_ui.c:3289` | `* descriptor via HarfBuzz (text_shape);` |
| `ITEMS` | function | `gui/browser_ui.c:4987` | `* between ITEMS (not between the lines inside one item). column-reverse
     * reverses the visua...` |
| `JS_NAV_MAX` | macro | `gui/browser_ui.c:1934` | `#define JS_NAV_MAX` |
| `JS_TICKS_PER_LOAD` | macro | `gui/browser_ui.c:2009` | `#define JS_TICKS_PER_LOAD` |
| `OMNI_MAX_SUGG` | macro | `gui/browser_ui.c:118` | `#define OMNI_MAX_SUGG` |
| `OV_MAX_DEPTH` | macro | `gui/browser_ui.c:9565` | `#define OV_MAX_DEPTH` |
| `PDF_MARGIN` | macro | `gui/browser_ui.c:10919` | `#define PDF_MARGIN` |
| `PDF_PAGE_H` | macro | `gui/browser_ui.c:10918` | `#define PDF_PAGE_H` |
| `PDF_PAGE_W` | macro | `gui/browser_ui.c:10917` | `#define PDF_PAGE_W` |
| `PNG_MARGIN` | macro | `gui/browser_ui.c:11094` | `#define PNG_MARGIN` |
| `PNG_MAX_H` | macro | `gui/browser_ui.c:11095` | `#define PNG_MAX_H` |
| `PNG_PAGE_W` | macro | `gui/browser_ui.c:11081` | `#define PNG_PAGE_W` |
| `RC_BOX_STACK_MAX` | macro | `gui/browser_ui.c:3031` | `#define RC_BOX_STACK_MAX` |
| `RC_DEFER_BAND_RUNS` | macro | `gui/browser_ui.c:6317` | `#define RC_DEFER_BAND_RUNS` |
| `RC_DEFER_COLS` | macro | `gui/browser_ui.c:6234` | `#define RC_DEFER_COLS` |
| `RC_DEFER_RANGES` | macro | `gui/browser_ui.c:6235` | `#define RC_DEFER_RANGES` |
| `RC_FLOAT_FIT_MIN` | macro | `gui/browser_ui.c:3042` | `#define RC_FLOAT_FIT_MIN` |
| `RC_FLOAT_MAX` | macro | `gui/browser_ui.c:3035` | `#define RC_FLOAT_MAX` |
| `RC_MAX_OUT_OF_FLOW` | macro | `gui/browser_ui.c:6126` | `#define RC_MAX_OUT_OF_FLOW` |
| `TABLE` | function | `gui/browser_ui.c:4848` | `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all containers ha` |
| `UI_BTN_LEFT` | macro | `gui/browser_ui.c:91` | `#define UI_BTN_LEFT` |
| `UI_BTN_W` | macro | `gui/browser_ui.c:88` | `#define UI_BTN_W` |
| `UI_BUTTON_HPAD` | macro | `gui/browser_ui.c:129` | `#define UI_BUTTON_HPAD` |
| `UI_CHECK_SZ` | macro | `gui/browser_ui.c:111` | `#define UI_CHECK_SZ` |
| `UI_CURSOR_SIZE` | macro | `gui/browser_ui.c:116` | `#define UI_CURSOR_SIZE` |
| `UI_FORM_FIELDS_MAX` | macro | `gui/browser_ui.c:130` | `#define UI_FORM_FIELDS_MAX` |
| `UI_HAMBURGER_GAP` | macro | `gui/browser_ui.c:115` | `#define UI_HAMBURGER_GAP` |
| `UI_HAMBURGER_W` | macro | `gui/browser_ui.c:114` | `#define UI_HAMBURGER_W` |
| `UI_IMAGE_MAX_BODY` | macro | `gui/browser_ui.c:219` | `#define UI_IMAGE_MAX_BODY` |
| `UI_INPUT_MEASURE_W` | macro | `gui/browser_ui.c:127` | `#define UI_INPUT_MEASURE_W` |
| `UI_INPUT_PAD` | macro | `gui/browser_ui.c:124` | `#define UI_INPUT_PAD` |
| `UI_INPUT_WIDTH` | macro | `gui/browser_ui.c:128` | `#define UI_INPUT_WIDTH` |
| `UI_LIST_INDENT` | macro | `gui/browser_ui.c:92` | `#define UI_LIST_INDENT` |
| `UI_MARGIN` | macro | `gui/browser_ui.c:90` | `#define UI_MARGIN` |
| `UI_MAX_TABS` | macro | `gui/browser_ui.c:258` | `#define UI_MAX_TABS` |
| `UI_MENU_COUNT` | macro | `gui/browser_ui.c:201` | `#define UI_MENU_COUNT` |
| `UI_MENU_INPUT_H` | macro | `gui/browser_ui.c:113` | `#define UI_MENU_INPUT_H` |
| `UI_MENU_ITEM_H` | macro | `gui/browser_ui.c:109` | `#define UI_MENU_ITEM_H` |
| `UI_MENU_LABEL_H` | macro | `gui/browser_ui.c:112` | `#define UI_MENU_LABEL_H` |
| `UI_MENU_PAD` | macro | `gui/browser_ui.c:110` | `#define UI_MENU_PAD` |
| `UI_MENU_W` | macro | `gui/browser_ui.c:108` | `#define UI_MENU_W` |
| `UI_OMNI_ROW_H` | macro | `gui/browser_ui.c:119` | `#define UI_OMNI_ROW_H` |
| `UI_OVERLINE_OFFSET` | macro | `gui/browser_ui.c:138` | `#define UI_OVERLINE_OFFSET` |
| `UI_READER_COLUMN_W` | macro | `gui/browser_ui.c:555` | `#define UI_READER_COLUMN_W` |
| `UI_RELOAD_X` | macro | `gui/browser_ui.c:2730` | `#define UI_RELOAD_X` |
| `UI_RESIZE_MARGIN` | macro | `gui/browser_ui.c:103` | `#define UI_RESIZE_MARGIN` |
| `UI_SCROLLBAR_MIN` | macro | `gui/browser_ui.c:98` | `#define UI_SCROLLBAR_MIN` |
| `UI_SCROLLBAR_PAD` | macro | `gui/browser_ui.c:99` | `#define UI_SCROLLBAR_PAD` |
| `UI_SCROLLBAR_W` | macro | `gui/browser_ui.c:97` | `#define UI_SCROLLBAR_W` |
| `UI_SLICE_MAX` | macro | `gui/browser_ui.c:142` | `#define UI_SLICE_MAX` |
| `UI_STRIKE_OFFSET` | macro | `gui/browser_ui.c:137` | `#define UI_STRIKE_OFFSET` |
| `UI_TABBAR_H` | macro | `gui/browser_ui.c:83` | `#define UI_TABBAR_H` |
| `UI_TAB_CLOSE_W` | macro | `gui/browser_ui.c:87` | `#define UI_TAB_CLOSE_W` |
| `UI_TAB_MAX_W` | macro | `gui/browser_ui.c:85` | `#define UI_TAB_MAX_W` |
| `UI_TAB_MIN_W` | macro | `gui/browser_ui.c:84` | `#define UI_TAB_MIN_W` |
| `UI_TAB_NEW_W` | macro | `gui/browser_ui.c:86` | `#define UI_TAB_NEW_W` |
| `UI_TITLEBAR_H` | macro | `gui/browser_ui.c:82` | `#define UI_TITLEBAR_H` |
| `UI_TOAST_PAD` | macro | `gui/browser_ui.c:117` | `#define UI_TOAST_PAD` |
| `UI_TOOLBAR_H` | macro | `gui/browser_ui.c:80` | `#define UI_TOOLBAR_H` |
| `UI_TWO_PI` | macro | `gui/browser_ui.c:120` | `#define UI_TWO_PI` |
| `UI_UNDERLINE_OFFSET` | macro | `gui/browser_ui.c:135` | `#define UI_UNDERLINE_OFFSET` |
| `UI_UNDERLINE_THICK` | macro | `gui/browser_ui.c:136` | `#define UI_UNDERLINE_THICK` |
| `UI_WIN_BTN_W` | macro | `gui/browser_ui.c:89` | `#define UI_WIN_BTN_W` |
| `_GNU_SOURCE` | macro | `gui/browser_ui.c:11` | `#define _GNU_SOURCE` |
| `_exit` | function | `gui/browser_ui.c:8202` | `_exit(127);` |
| `add` | function | `gui/browser_ui.c:3468` | `* about to add (top/h passed in). A box that survived a line wrap simply ends at the
 * wrap -- m...` |
| `add_current_host_to_list` | function | `gui/browser_ui.c:771` | `static void add_current_host_to_list(browser_window *w, int sel)` |
| `again` | function | `gui/browser_ui.c:8260` | `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one fail wi` |
| `allowlisted` | type_alias | `gui/browser_ui.c:1486` | `typedef struct fetch_prep { int allowlisted;` |
| `anchor` | function | `gui/browser_ui.c:7144` | `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is a n` |
| `applies` | function | `gui/browser_ui.c:14905` | `* persisted choice applies (prefs_parse already clamped it to a valid mode). */ const char *js_env = getenv("FREEDOM_JS"` |
| `apply_auth` | function | `gui/browser_ui.c:1391` | `apply_auth(w, abs, &cfg);` |
| `apply_click_result` | function | `gui/browser_ui.c:11665` | `static void apply_click_result(browser_window *w, tab_page *page)` |
| `apply_theme` | function | `gui/browser_ui.c:573` | `apply_theme(w);` |
| `apply_zoom` | function | `gui/browser_ui.c:572` | `static void apply_zoom(browser_window *w)` |
| `arrives` | function | `gui/browser_ui.c:2263` | `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...` |
| `audio_mark_dead` | function | `gui/browser_ui.c:8219` | `static void audio_mark_dead(browser_window *w)` |
| `audio_spawn` | function | `gui/browser_ui.c:8164` | `static void audio_spawn(browser_window *w, int rate, int channels)` |
| `audio_stop` | function | `gui/browser_ui.c:8250` | `static void audio_stop(browser_window *w)` |
| `audio_write` | function | `gui/browser_ui.c:8236` | `static void audio_write(browser_window *w, const uint8_t *data, size_t len)` |
| `band_common_box` | function | `gui/browser_ui.c:6146` | `static int band_common_box(const rd_doc *doc, size_t start, size_t end)` |
| `behind` | function | `gui/browser_ui.c:5726` | `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old code ` |
| `bg` | function | `gui/browser_ui.c:9434` | `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);` |
| `block_id` | type_alias | `gui/browser_ui.c:2986` | `typedef struct rc_open_box { int block_id;` |
| `block_in_table_caption` | function | `gui/browser_ui.c:6210` | `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)` |
| `block_is_oof` | function | `gui/browser_ui.c:4860` | `static int block_is_oof(const rd_doc *doc, const rd_block *bk)` |
| `block_margins` | function | `gui/browser_ui.c:3438` | `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...` |
| `block_style` | function | `gui/browser_ui.c:3410` | `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...` |
| `blocking` | function | `gui/browser_ui.c:8547` | `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);` |
| `bookmark_toggle_current` | function | `gui/browser_ui.c:941` | `static void bookmark_toggle_current(browser_window *w)` |
| `box` | function | `gui/browser_ui.c:4118` | `* declared intrinsic size reserves that box (broken-image parity);` |
| `box_edge_px` | function | `gui/browser_ui.c:4343` | `static double box_edge_px(int wpx)` |
| `box_forms_stacking_context` | function | `gui/browser_ui.c:9696` | `static int box_forms_stacking_context(const pv_box_def *def)` |
| `box_is_strict_descendant` | function | `gui/browser_ui.c:4442` | `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)` |
| `box_line_visible` | function | `gui/browser_ui.c:5529` | `static int box_line_visible(int style)` |
| `box_margin_bottom` | function | `gui/browser_ui.c:5706` | `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)` |
| `box_margin_top` | function | `gui/browser_ui.c:5699` | `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)` |
| `box_path` | function | `gui/browser_ui.c:8802` | `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)` |
| `box_path4` | function | `gui/browser_ui.c:8804` | `box_path4(cr, x, y, w, h, rc);` |
| `box_path_has` | function | `gui/browser_ui.c:6019` | `static int box_path_has(const rd_doc *doc, int block_id, int want)` |
| `box_path_of` | function | `gui/browser_ui.c:6130` | `static int box_path_of(const rd_doc *doc, int block_id, int *out)` |
| `box_pointer_events_none` | function | `gui/browser_ui.c:11528` | `static int box_pointer_events_none(const rd_doc *doc, int block_id)` |
| `box_shrink_width` | function | `gui/browser_ui.c:6034` | `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...` |
| `box_transform_matrix` | function | `gui/browser_ui.c:9745` | `static void box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
             ...` |
| `browser_add_exception` | function | `gui/browser_ui.c:14302` | `browser_add_exception(&w->bs, host);` |
| `browser_can_back` | function | `gui/browser_ui.c:2766` | `case UI_HOT_BACK: return browser_can_back(&w->bs);` |
| `browser_can_forward` | function | `gui/browser_ui.c:2767` | `case UI_HOT_FWD: return browser_can_forward(&w->bs);` |
| `browser_commit_url_bar` | function | `gui/browser_ui.c:13532` | `browser_commit_url_bar(&w->bs);` |
| `browser_free` | function | `gui/browser_ui.c:2430` | `browser_free(&w->bs);` |
| `browser_navigate` | function | `gui/browser_ui.c:14824` | `else browser_navigate(&w.bs, start_url);` |
| `browser_set_page` | function | `gui/browser_ui.c:2038` | `browser_set_page(&w->bs, NULL, "Failed to spawn sandboxed tab.", 1);` |
| `browser_set_status` | function | `gui/browser_ui.c:576` | `browser_set_status(&w->bs, msg, now_ms());` |
| `browser_set_url_bar` | function | `gui/browser_ui.c:2295` | `browser_set_url_bar(&w->bs, "about:bookmarks");` |
| `browser_url_bar_backspace` | function | `gui/browser_ui.c:14543` | `browser_url_bar_backspace(&w->bs);` |
| `browser_url_bar_clear` | function | `gui/browser_ui.c:2506` | `browser_url_bar_clear(&w->bs);` |
| `browser_url_bar_delete` | function | `gui/browser_ui.c:14546` | `browser_url_bar_delete(&w->bs);` |
| `browser_url_bar_delete_selection` | function | `gui/browser_ui.c:14092` | `browser_url_bar_delete_selection(&w->bs);` |
| `browser_url_bar_insert` | function | `gui/browser_ui.c:13994` | `browser_url_bar_insert(&w->bs, (char)c);` |
| `browser_url_bar_move_cursor` | function | `gui/browser_ui.c:14550` | `else browser_url_bar_move_cursor(&w->bs, -1);` |
| `browser_url_bar_select_all` | function | `gui/browser_ui.c:14292` | `browser_url_bar_select_all(&w->bs);` |
| `browser_url_bar_set_cursor` | function | `gui/browser_ui.c:14555` | `browser_url_bar_set_cursor(&w->bs, 0, shift);` |
| `browser_window` | struct | `gui/browser_ui.c:282` | `` |
| `bs` | type_alias | `gui/browser_ui.c:266` | `typedef struct tab_ctx { browser_state bs;` |
| `buffer_release` | function | `gui/browser_ui.c:582` | `static void buffer_release(void *data, struct wl_buffer *wl_buffer)` |
| `bui_blend_operator` | function | `gui/browser_ui.c:9864` | `static cairo_operator_t bui_blend_operator(int mix_blend)` |
| `bui_box_blur_surface` | function | `gui/browser_ui.c:10042` | `bui_box_blur_surface(snap, radius);` |
| `bui_grad_color_at` | function | `gui/browser_ui.c:8844` | `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...` |
| `bui_paint_backdrop_blur` | function | `gui/browser_ui.c:10002` | `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...` |
| `bui_paint_conic` | function | `gui/browser_ui.c:9026` | `bui_paint_conic(cr, x, y, w, h, rad, bx->grad_angle, bx->grad_c, bx->grad_pos, bx->grad_n);` |
| `bui_pop_group_composite` | function | `gui/browser_ui.c:10060` | `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms)` |
| `bui_skew_tan` | function | `gui/browser_ui.c:9739` | `static double bui_skew_tan(int deg)` |
| `build_file_origin` | function | `gui/browser_ui.c:664` | `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)` |
| `build_host_filter` | function | `gui/browser_ui.c:691` | `static hb_set *build_host_filter(void)` |
| `build_impersonate_filter` | function | `gui/browser_ui.c:741` | `static hb_set *build_impersonate_filter(void)` |
| `build_js_filter` | function | `gui/browser_ui.c:737` | `static hb_set *build_js_filter(void)` |
| `button_box_width` | function | `gui/browser_ui.c:7548` | `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...` |
| `bx_content_clipped` | function | `gui/browser_ui.c:9571` | `return bx_content_clipped(d->overflow_x, d->overflow_y);` |
| `bx_lp_px` | function | `gui/browser_ui.c:5807` | `bx_lp_px(def->box_r, def->box_r_pct, avail_w), wcap, def->box_center, avail_w);` |
| `bx_replaced_box` | function | `gui/browser_ui.c:4069` | `return bx_replaced_box(d->box_w, d->box_w_pct, d->aspect_num, d->aspect_den, avail_w, dw, dh);` |
| `bx_width_cap` | function | `gui/browser_ui.c:4688` | `return bx_width_cap(d->box_w, d->box_w_pct, content_w);` |
| `cairo_arc` | function | `gui/browser_ui.c:7597` | `cairo_arc(cr, bx + 7.0, by + 7.0, r, 0, 2 * M_PI);` |
| `cairo_clip` | function | `gui/browser_ui.c:7580` | `cairo_clip(cr);` |
| `cairo_clip_extents` | function | `gui/browser_ui.c:10080` | `cairo_clip_extents(cr, &x1, &y1, &x2, &y2);` |
| `cairo_close_path` | function | `gui/browser_ui.c:7680` | `cairo_close_path(cr);` |
| `cairo_curve_to` | function | `gui/browser_ui.c:9291` | `cairo_curve_to(cr, cx + half * 0.5, ly, cx + half * 0.5, cy, cx + half, cy);` |
| `cairo_debug_reset_static_data` | function | `gui/browser_ui.c:15202` | `cairo_debug_reset_static_data();` |
| `cairo_destroy` | function | `gui/browser_ui.c:10041` | `cairo_destroy(scr);` |
| `cairo_fill` | function | `gui/browser_ui.c:2692` | `cairo_fill(cr);` |
| `cairo_fill_preserve` | function | `gui/browser_ui.c:8698` | `cairo_fill_preserve(cr);` |
| `cairo_font_extents` | function | `gui/browser_ui.c:3773` | `cairo_font_extents(cr, &fe);` |
| `cairo_identity_matrix` | function | `gui/browser_ui.c:10049` | `cairo_identity_matrix(cr);` |
| `cairo_image_surface_create` | function | `gui/browser_ui.c:11150` | `cairo_image_surface_create(CAIRO_FORMAT_ARGB32, (int)PNG_PAGE_W, (int)img_h);` |
| `cairo_line_to` | function | `gui/browser_ui.c:7610` | `cairo_line_to(cr, bx + 6.5, by + 10.5);` |
| `cairo_mask_surface` | function | `gui/browser_ui.c:10221` | `cairo_mask_surface(scr, flt_surf, 0, 0);` |
| `cairo_matrix_init_identity` | function | `gui/browser_ui.c:9749` | `cairo_matrix_init_identity(m);` |
| `cairo_matrix_multiply` | function | `gui/browser_ui.c:9854` | `cairo_matrix_multiply(m, &k, m);` |
| `cairo_matrix_rotate` | function | `gui/browser_ui.c:9848` | `cairo_matrix_rotate(m, rot);` |
| `cairo_matrix_scale` | function | `gui/browser_ui.c:9849` | `cairo_matrix_scale(m, sx, sy);` |
| `cairo_matrix_translate` | function | `gui/browser_ui.c:9846` | `cairo_matrix_translate(m, tx, ty);` |
| `cairo_move_to` | function | `gui/browser_ui.c:2805` | `cairo_move_to(cr, dx, y);` |
| `cairo_new_sub_path` | function | `gui/browser_ui.c:8792` | `cairo_new_sub_path(cr);` |
| `cairo_paint` | function | `gui/browser_ui.c:8026` | `cairo_paint(cr);` |
| `cairo_paint_with_alpha` | function | `gui/browser_ui.c:10280` | `cairo_paint_with_alpha(cr, alpha);` |
| `cairo_pattern_add_color_stop_rgb` | function | `gui/browser_ui.c:9038` | `cairo_pattern_add_color_stop_rgb(pat, pos, sc.r, sc.g, sc.b);` |
| `cairo_pattern_add_color_stop_rgba` | function | `gui/browser_ui.c:8835` | `cairo_pattern_add_color_stop_rgba(pat, pos, sc.r, sc.g, sc.b, alpha);` |
| `cairo_pattern_destroy` | function | `gui/browser_ui.c:8947` | `cairo_pattern_destroy(ipat);` |
| `cairo_pattern_set_extend` | function | `gui/browser_ui.c:8942` | `cairo_pattern_set_extend(ipat, bx->bg_repeat == CSS_BGR_NO_REPEAT ? CAIRO_EXTEND_NONE : CAIRO_EXTEND_REPEAT);` |
| `cairo_pattern_set_filter` | function | `gui/browser_ui.c:8024` | `cairo_pattern_set_filter(cairo_get_source(cr), nearest ? CAIRO_FILTER_NEAREST : CAIRO_FILTER_GOOD);` |
| `cairo_pop_group_to_source` | function | `gui/browser_ui.c:10236` | `cairo_pop_group_to_source(cr);` |
| `cairo_push_group` | function | `gui/browser_ui.c:10376` | `cairo_push_group(cr);` |
| `cairo_rectangle` | function | `gui/browser_ui.c:2691` | `cairo_rectangle(cr, tx, ty, UI_SCROLLBAR_W, trh);` |
| `cairo_restore` | function | `gui/browser_ui.c:7584` | `cairo_restore(cr);` |
| `cairo_save` | function | `gui/browser_ui.c:7578` | `cairo_save(cr);` |
| `cairo_scale` | function | `gui/browser_ui.c:7986` | `cairo_scale(cr, dw / (double)im->nat_w, dh / (double)im->nat_h);` |
| `cairo_select_font_face` | function | `gui/browser_ui.c:3297` | `cairo_select_font_face(cr, family_face(family), italic ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL, bold ? CAIRO` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9113` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9116` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9155` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9158` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9215` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9218` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9310` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:9312` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_fill_rule` | function | `gui/browser_ui.c:9006` | `cairo_set_fill_rule(cr, CAIRO_FILL_RULE_EVEN_ODD);` |
| `cairo_set_font_size` | function | `gui/browser_ui.c:3300` | `cairo_set_font_size(cr, size);` |
| `cairo_set_line_cap` | function | `gui/browser_ui.c:9115` | `cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);` |
| `cairo_set_line_width` | function | `gui/browser_ui.c:7594` | `cairo_set_line_width(cr, lw);` |
| `cairo_set_operator` | function | `gui/browser_ui.c:10279` | `cairo_set_operator(cr, bui_blend_operator(def ? def->mix_blend : CSS_MB_UNSET));` |
| `cairo_set_source` | function | `gui/browser_ui.c:8945` | `cairo_set_source(cr, ipat);` |
| `cairo_set_source_rgb` | function | `gui/browser_ui.c:3312` | `else cairo_set_source_rgb(cr, c.r, c.g, c.b);` |
| `cairo_set_source_rgba` | function | `gui/browser_ui.c:8990` | `cairo_set_source_rgba(cr, sc.r, sc.g, sc.b, 0.30 / (double)steps);` |
| `cairo_set_source_surface` | function | `gui/browser_ui.c:8021` | `cairo_set_source_surface(cr, im->surface, 0.0, 0.0);` |
| `cairo_show_page` | function | `gui/browser_ui.c:11027` | `cairo_show_page(cr);` |
| `cairo_show_text` | function | `gui/browser_ui.c:2806` | `cairo_show_text(cr, s);` |
| `cairo_stroke` | function | `gui/browser_ui.c:7598` | `cairo_stroke(cr);` |
| `cairo_surface_destroy` | function | `gui/browser_ui.c:1228` | `cairo_surface_destroy(s);` |
| `cairo_surface_flush` | function | `gui/browser_ui.c:1231` | `cairo_surface_flush(s);` |
| `cairo_surface_mark_dirty` | function | `gui/browser_ui.c:1240` | `cairo_surface_mark_dirty(s);` |
| `cairo_text_extents` | function | `gui/browser_ui.c:2803` | `cairo_text_extents(cr, s, &te);` |
| `cairo_transform` | function | `gui/browser_ui.c:10378` | `cairo_transform(cr, &m);` |
| `cairo_translate` | function | `gui/browser_ui.c:7980` | `cairo_translate(cr, left + pad + ax, ry + pad);` |
| `cairo_user_to_device` | function | `gui/browser_ui.c:10017` | `cairo_user_to_device(cr, &dx, &dy);` |
| `caller` | function | `gui/browser_ui.c:11258` | `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...` |
| `chain` | function | `gui/browser_ui.c:7060` | `* chain (the box that left the normal flow at this pen position);` |
| `child_cont_at_level` | function | `gui/browser_ui.c:4808` | `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)` |
| `children` | function | `gui/browser_ui.c:5717` | `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...` |
| `clear_doc` | function | `gui/browser_ui.c:1202` | `static void clear_doc(browser_window *w)` |
| `clipboard_copy` | function | `gui/browser_ui.c:14049` | `static void clipboard_copy(browser_window *w)` |
| `clipboard_cut` | function | `gui/browser_ui.c:14286` | `clipboard_cut(w);` |
| `clipboard_paste` | function | `gui/browser_ui.c:14276` | `clipboard_paste(w);` |
| `clock_gettime` | function | `gui/browser_ui.c:147` | `clock_gettime(CLOCK_MONOTONIC, &ts);` |
| `close` | function | `gui/browser_ui.c:612` | `close(fd);` |
| `close_all_boxes` | function | `gui/browser_ui.c:4782` | `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);` |
| `close_inline_box` | function | `gui/browser_ui.c:3548` | `close_inline_box(L, s, s->cur_top, h);` |
| `close_top_box` | function | `gui/browser_ui.c:5536` | `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)` |
| `col` | type_alias | `gui/browser_ui.c:6253` | `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];` |
| `column` | function | `gui/browser_ui.c:5924` | `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...` |
| `compositing` | function | `gui/browser_ui.c:10480` | `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context: opac` |
| `compute_page_js` | function | `gui/browser_ui.c:1954` | `static int compute_page_js(const browser_window *w)` |
| `container_box_of` | function | `gui/browser_ui.c:4493` | `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)` |
| `content_font` | function | `gui/browser_ui.c:3295` | `static void content_font(cairo_t *cr, double size, int bold, int italic, int family)` |
| `content_geometry` | function | `gui/browser_ui.c:2589` | `static void content_geometry(const browser_window *w, double *top, double *height)` |
| `content_width` | function | `gui/browser_ui.c:2615` | `static double content_width(const browser_window *w)` |
| `context` | function | `gui/browser_ui.c:6199` | `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document ord` |
| `convention` | function | `gui/browser_ui.c:9178` | `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE \|\| style == ` |
| `cost` | function | `gui/browser_ui.c:15117` | `* measured cost (floor 33 ms = the existing ~30 fps ceiling):
             * cheap pages paint at...` |
| `css_align_to_bt` | function | `gui/browser_ui.c:4333` | `static int css_align_to_bt(int align_kw)` |
| `css_replaced_box` | function | `gui/browser_ui.c:4064` | `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...` |
| `cursor_at_point` | function | `gui/browser_ui.c:11544` | `static int cursor_at_point(browser_window *w, double px, double py)` |
| `cx_forms_stacking_context` | function | `gui/browser_ui.c:9723` | `return cx_forms_stacking_context(&st);` |
| `data_device_data_offer` | function | `gui/browser_ui.c:13844` | `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...` |
| `data_device_drop` | function | `gui/browser_ui.c:13885` | `static void data_device_drop(void *d, struct wl_data_device *dev)` |
| `data_device_enter` | function | `gui/browser_ui.c:13875` | `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...` |
| `data_device_leave` | function | `gui/browser_ui.c:13880` | `static void data_device_leave(void *d, struct wl_data_device *dev)` |
| `data_device_motion` | function | `gui/browser_ui.c:13881` | `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...` |
| `data_device_selection` | function | `gui/browser_ui.c:13856` | `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...` |
| `data_offer_action` | function | `gui/browser_ui.c:13834` | `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)` |
| `data_offer_source_actions` | function | `gui/browser_ui.c:13831` | `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)` |
| `data_source_cancelled` | function | `gui/browser_ui.c:13896` | `static void data_source_cancelled(void *data, struct wl_data_source *src)` |
| `data_source_send` | function | `gui/browser_ui.c:13902` | `static void data_source_send(void *data, struct wl_data_source *src,
                            ...` |
| `data_source_target` | function | `gui/browser_ui.c:13915` | `static void data_source_target(void *d, struct wl_data_source *s, const char *m)` |
| `deco_configure` | function | `gui/browser_ui.c:12770` | `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)` |
| `defer_append` | function | `gui/browser_ui.c:6396` | `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...` |
| `defer_flush` | function | `gui/browser_ui.c:6431` | `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...` |
| `defer_founder_style` | function | `gui/browser_ui.c:6383` | `defer_founder_style(doc, start, end, runs[r].key, &side, &ml, &mlpct, &mr, &mrpct);` |
| `defer_key_block` | function | `gui/browser_ui.c:6274` | `static int defer_key_block(const rd_block *bk)` |
| `delay` | function | `gui/browser_ui.c:356` | `* timer delay (tab_page.next_timer_ms);` |
| `deliver_fetch_result` | function | `gui/browser_ui.c:11884` | `static void deliver_fetch_result(browser_window *w, fetch_job *j)` |
| `descriptors` | function | `gui/browser_ui.c:8179` | `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection — the m` |
| `destroy_buffer` | function | `gui/browser_ui.c:588` | `static void destroy_buffer(browser_window *w)` |
| `dies` | function | `gui/browser_ui.c:8156` | `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...` |
| `dispatch_click` | function | `gui/browser_ui.c:13762` | `dispatch_click(w, w->ptr_x, w->ptr_y);` |
| `dispatch_js_event` | function | `gui/browser_ui.c:14184` | `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...` |
| `dispatch_mouse_event` | function | `gui/browser_ui.c:13437` | `dispatch_mouse_event(w, nid, "mouseenter", (int)w->ptr_x, (int)w->ptr_y, 0);` |
| `do_load` | function | `gui/browser_ui.c:1929` | `static void do_load(browser_window *w, const char *url);` |
| `do_submit_post` | function | `gui/browser_ui.c:12006` | `do_submit_post(w, &plan);` |
| `down` | function | `gui/browser_ui.c:13416` | `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void dispatch_` |
| `drain_fetch_results` | function | `gui/browser_ui.c:11939` | `static void drain_fetch_results(browser_window *w)` |
| `draw_clock` | function | `gui/browser_ui.c:12158` | `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...` |
| `draw_hamburger` | function | `gui/browser_ui.c:12169` | `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)` |
| `draw_hover_url` | function | `gui/browser_ui.c:12319` | `static double draw_hover_url(cairo_t *cr, browser_window *w)` |
| `draw_input_row` | function | `gui/browser_ui.c:9421` | `draw_input_row(cr, w, r->blk, left + r->x_off, cw, ry, r->ascent, r->height);` |
| `draw_menu` | function | `gui/browser_ui.c:12208` | `static void draw_menu(cairo_t *cr, browser_window *w)` |
| `draw_omnibox` | function | `gui/browser_ui.c:12436` | `static void draw_omnibox(cairo_t *cr, browser_window *w)` |
| `draw_reload` | function | `gui/browser_ui.c:12186` | `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)` |
| `draw_scrollbar` | function | `gui/browser_ui.c:2685` | `static void draw_scrollbar(cairo_t *cr, const browser_window *w)` |
| `draw_slice` | function | `gui/browser_ui.c:3358` | `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)` |
| `draw_tabstrip` | function | `gui/browser_ui.c:12381` | `static void draw_tabstrip(cairo_t *cr, browser_window *w)` |
| `draw_text` | function | `gui/browser_ui.c:2799` | `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)` |
| `draw_toast` | function | `gui/browser_ui.c:12351` | `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)` |
| `drop_repl_worker` | function | `gui/browser_ui.c:2000` | `static void drop_repl_worker(browser_window *w)` |
| `dup2` | function | `gui/browser_ui.c:8183` | `dup2(p[0], 0);` |
| `element` | function | `gui/browser_ui.c:12813` | `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...` |
| `emit_replaced_row` | function | `gui/browser_ui.c:4072` | `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...` |
| `ensure_buffer` | function | `gui/browser_ui.c:594` | `static int ensure_buffer(browser_window *w)` |
| `ensure_download_dir` | function | `gui/browser_ui.c:11805` | `static int ensure_download_dir(char *out, size_t outsz)` |
| `execlp` | function | `gui/browser_ui.c:8199` | `else execlp("aplay", "aplay", "-r", rate_str, "-c", ch_str, "-f", "S16_LE", "-t", "raw", "-q", (char *)NULL);` |
| `export_pdf` | function | `gui/browser_ui.c:11038` | `static void export_pdf(browser_window *w)` |
| `export_png` | function | `gui/browser_ui.c:11223` | `static void export_png(browser_window *w)` |
| `family` | type_alias | `gui/browser_ui.c:3618` | `typedef struct rc_ext { int family;` |
| `family_face` | function | `gui/browser_ui.c:3278` | `static const char *family_face(int family)` |
| `fb_buffer_free` | function | `gui/browser_ui.c:11676` | `fb_buffer_free(&w->console);` |
| `fb_buffer_init` | function | `gui/browser_ui.c:2183` | `fb_buffer_init(&page.console);` |
| `fb_buffer_push` | function | `gui/browser_ui.c:13301` | `fb_buffer_push(&w->console, FB_ERROR, "Freebug: no live page to evaluate (reload the page first).", 56);` |
| `fb_buffer_push_loc` | function | `gui/browser_ui.c:13312` | `fb_buffer_push_loc(&w->console, e->level, e->text, e->len, e->file, e->line, e->col);` |
| `fb_buffer_reset` | function | `gui/browser_ui.c:2002` | `fb_buffer_reset(&w->console);` |
| `fbw_console_lines` | function | `gui/browser_ui.c:12930` | `static size_t fbw_console_lines(const fb_buffer *log)` |
| `fbw_level_rgb` | function | `gui/browser_ui.c:12919` | `static void fbw_level_rgb(int level, double *r, double *g, double *b)` |
| `fbw_split_y` | function | `gui/browser_ui.c:12883` | `static double fbw_split_y(const freebug_window *fb)` |
| `fbw_toplevel_close` | function | `gui/browser_ui.c:13188` | `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)` |
| `fbw_toplevel_configure` | function | `gui/browser_ui.c:13178` | `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...` |
| `fbw_xdg_surface_configure` | function | `gui/browser_ui.c:13170` | `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)` |
| `fc_init` | function | `gui/browser_ui.c:14779` | `fc_init(&w.fc);` |
| `fc_set_active` | function | `gui/browser_ui.c:2163` | `fc_set_active(&w->fc, has_anim);` |
| `fclose` | function | `gui/browser_ui.c:635` | `fclose(f);` |
| `fcntl` | function | `gui/browser_ui.c:14800` | `fcntl(w.fetch_pipe[0], F_SETFL, O_NONBLOCK);` |
| `fetch_decode_image` | function | `gui/browser_ui.c:1866` | `fetch_decode_image(w, t, img_fetch, fetch_ctx, target_url, &imgpool, pooled, &slot->surface, &slot->nat_w, &slot->nat_h)` |
| `fetch_follow_navigable` | function | `gui/browser_ui.c:1290` | `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...` |
| `fetch_job` | struct | `gui/browser_ui.c:1564` | `` |
| `fetch_job_free` | function | `gui/browser_ui.c:1595` | `static void fetch_job_free(fetch_job *j)` |
| `fetch_launch` | function | `gui/browser_ui.c:1688` | `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...` |
| `fetch_prep` | struct | `gui/browser_ui.c:1486` | `` |
| `fetch_thread` | function | `gui/browser_ui.c:1640` | `static void *fetch_thread(void *arg)` |
| `fields` | function | `gui/browser_ui.c:262` | `* fields (so the 200+ render/event call sites stay unchanged);` |
| `fill` | function | `gui/browser_ui.c:10388` | `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in the ` |
| `find_bg_image` | function | `gui/browser_ui.c:1108` | `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)` |
| `find_input_state` | function | `gui/browser_ui.c:1194` | `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)` |
| `first` | function | `gui/browser_ui.c:7122` | `* flush first (no-op when nothing is deferred). */ defer_flush(cr, w, L, &s, th, content_w, doc, &df);` |
| `flex_item_basis` | function | `gui/browser_ui.c:4729` | `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...` |
| `flex_item_min_main` | function | `gui/browser_ui.c:4760` | `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...` |
| `flow` | function | `gui/browser_ui.c:15095` | `* flow (counting them starved aplay). A video frame read while * overdue overwrites the held slot (standard player frame` |
| `flow_emit_frag` | function | `gui/browser_ui.c:3647` | `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...` |
| `flow_text` | function | `gui/browser_ui.c:3714` | `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...` |
| `flow_text_block` | function | `gui/browser_ui.c:4175` | `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...` |
| `flush_line` | function | `gui/browser_ui.c:3527` | `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)` |
| `foldback_session_cookies` | function | `gui/browser_ui.c:1981` | `static void foldback_session_cookies(const char *url, const char *jar)` |
| `font_size` | type_alias | `gui/browser_ui.c:2819` | `typedef struct rc_frag { double x, width, font_size;` |
| `fprintf` | function | `gui/browser_ui.c:6390` | `fprintf(stderr, "[defer] band [%zu,%zu) keys=", start, end);` |
| `frag_styled` | function | `gui/browser_ui.c:3371` | `static int frag_styled(const rc_frag *f)` |
| `fragment` | function | `gui/browser_ui.c:9641` | `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...` |
| `free` | function | `gui/browser_ui.c:682` | `free(txt);` |
| `free_bg_images` | function | `gui/browser_ui.c:1205` | `free_bg_images(w);` |
| `free_images` | function | `gui/browser_ui.c:1069` | `static void free_images(browser_window *w)` |
| `free_inputs` | function | `gui/browser_ui.c:1061` | `static void free_inputs(browser_window *w)` |
| `free_live_page` | function | `gui/browser_ui.c:2426` | `static void free_live_page(browser_window *w)` |
| `freebug_copy_console` | function | `gui/browser_ui.c:13927` | `static void freebug_copy_console(browser_window *w)` |
| `freebug_destroy` | function | `gui/browser_ui.c:13232` | `static void freebug_destroy(browser_window *w)` |
| `freebug_ensure_buffer` | function | `gui/browser_ui.c:12891` | `static int freebug_ensure_buffer(freebug_window *fb)` |
| `freebug_eval` | function | `gui/browser_ui.c:13287` | `static void freebug_eval(browser_window *w)` |
| `freebug_handle_key` | function | `gui/browser_ui.c:13327` | `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...` |
| `freebug_hide` | function | `gui/browser_ui.c:13154` | `static void freebug_hide(browser_window *w)` |
| `freebug_is_open` | function | `gui/browser_ui.c:13243` | `static int freebug_is_open(const browser_window *w)` |
| `freebug_owns_surface` | function | `gui/browser_ui.c:13239` | `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)` |
| `freebug_paint` | function | `gui/browser_ui.c:12942` | `static void freebug_paint(freebug_window *fb)` |
| `freebug_pointer_axis` | function | `gui/browser_ui.c:13403` | `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)` |
| `freebug_pointer_button` | function | `gui/browser_ui.c:13362` | `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...` |
| `freebug_pointer_motion` | function | `gui/browser_ui.c:13381` | `static void freebug_pointer_motion(browser_window *w)` |
| `freebug_redraw` | function | `gui/browser_ui.c:13150` | `static void freebug_redraw(browser_window *w)` |
| `freebug_redraw_fb` | function | `gui/browser_ui.c:13141` | `static void freebug_redraw_fb(freebug_window *fb)` |
| `freebug_repl_worker` | function | `gui/browser_ui.c:13251` | `static tab *freebug_repl_worker(browser_window *w)` |
| `freebug_show` | function | `gui/browser_ui.c:13197` | `static void freebug_show(browser_window *w)` |
| `freebug_toggle` | function | `gui/browser_ui.c:13227` | `static void freebug_toggle(browser_window *w)` |
| `freebug_window` | type_alias | `gui/browser_ui.c:532` | `typedef struct freebug_window freebug_window;` |
| `freebug_window` | struct | `gui/browser_ui.c:12860` | `` |
| `freedom_write_dir` | function | `gui/browser_ui.c:746` | `static int freedom_write_dir(char *out, size_t cap)` |
| `fx_auto_min_size` | function | `gui/browser_ui.c:4772` | `return fx_auto_min_size(mc, basis, author_min, scroll);` |
| `go_omnibox` | function | `gui/browser_ui.c:13495` | `static void go_omnibox(browser_window *w)` |
| `gui_subresource_fetch` | function | `gui/browser_ui.c:1368` | `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...` |
| `gutter` | function | `gui/browser_ui.c:551` | `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...` |
| `h` | type_alias | `gui/browser_ui.c:2899` | `typedef struct rc_box { double x, top, w, h;` |
| `handle_key_press` | function | `gui/browser_ui.c:14241` | `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...` |
| `have` | function | `gui/browser_ui.c:7217` | `* as they always have (spec/float.md §6b.3). */ rc_float_clear(&s);` |
| `hb_free` | function | `gui/browser_ui.c:824` | `hb_free(w->js_hosts);` |
| `hb_is_allowlisted` | function | `gui/browser_ui.c:1360` | `return hb_is_allowlisted(w->hosts, host);` |
| `hb_load` | function | `gui/browser_ui.c:681` | `hb_load(s, txt, list);` |
| `hls_playlist_free` | function | `gui/browser_ui.c:8302` | `hls_playlist_free(w->video_pl);` |
| `host_from_url` | function | `gui/browser_ui.c:1004` | `static int host_from_url(const char *url, char *out, size_t outsz)` |
| `hot_actionable` | function | `gui/browser_ui.c:2763` | `static int hot_actionable(const browser_window *w, ui_hot hot)` |
| `html_center_offset` | function | `gui/browser_ui.c:2625` | `static double html_center_offset(const browser_window *w)` |
| `in` | function | `gui/browser_ui.c:11381` | `* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);` |
| `init_net_config` | function | `gui/browser_ui.c:979` | `static void init_net_config(browser_window *w)` |
| `input_box_width` | function | `gui/browser_ui.c:7539` | `static double input_box_width(double content_w)` |
| `input_is_editable` | function | `gui/browser_ui.c:1054` | `static int input_is_editable(int input_type)` |
| `input_is_interactive` | function | `gui/browser_ui.c:1049` | `static int input_is_interactive(int input_type)` |
| `insert_pasted_text` | function | `gui/browser_ui.c:13985` | `static void insert_pasted_text(browser_window *w, const char *text, size_t len)` |
| `ip_anim_init` | function | `gui/browser_ui.c:9775` | `ip_anim_init(&a, IP_VAL_SCALAR, &ease, prog_kf, 2, (double)def->anim_duration_ms, delay, iters, dir, fill);` |
| `ip_anim_tick` | function | `gui/browser_ui.c:9777` | `ip_anim_tick(&a, (double)elapsed_ms);` |
| `is_http_url` | function | `gui/browser_ui.c:992` | `static int is_http_url(const char *s)` |
| `is_https_url` | function | `gui/browser_ui.c:988` | `static int is_https_url(const char *s)` |
| `it` | function | `gui/browser_ui.c:7284` | `* column: flush first so the column lands above it (source order), * then move the anchor — the image bottom is the cont` |
| `item_at_level` | function | `gui/browser_ui.c:4793` | `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)` |
| `item_declared_basis` | function | `gui/browser_ui.c:4683` | `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...` |
| `item_root_box` | function | `gui/browser_ui.c:4324` | `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)` |
| `item_root_box_in` | function | `gui/browser_ui.c:4287` | `static int item_root_box_in(const rd_doc *doc, size_t b0, size_t b1, int cbox)` |
| `item_sides` | struct | `gui/browser_ui.c:4413` | `` |
| `item_sides_at_level` | function | `gui/browser_ui.c:4464` | `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,
                  ...` |
| `item_sides_from_box` | function | `gui/browser_ui.c:4471` | `return item_sides_from_box(doc, cbox, cb_w);` |
| `jsp_enabled` | function | `gui/browser_ui.c:1955` | `return jsp_enabled(w->js_mode, page_js_host_allowlisted(w));` |
| `jsp_trusted` | function | `gui/browser_ui.c:1963` | `return jsp_trusted(compute_page_js(w), page_host_allowlisted(w));` |
| `key` | type_alias | `gui/browser_ui.c:6246` | `typedef struct rc_defer_col { int key;` |
| `key` | function | `gui/browser_ui.c:7203` | `* founders splits by key (stories, rail, footer nav each take * their column);` |
| `key_is_repeatable` | function | `gui/browser_ui.c:14571` | `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)` |
| `key_repeat_arm` | function | `gui/browser_ui.c:14587` | `static void key_repeat_arm(browser_window *w, uint32_t key)` |
| `key_repeat_fire` | function | `gui/browser_ui.c:14611` | `static void key_repeat_fire(browser_window *w)` |
| `key_repeat_stop` | function | `gui/browser_ui.c:14600` | `static void key_repeat_stop(browser_window *w)` |
| `key_sym_to_js_key` | function | `gui/browser_ui.c:14133` | `static const char *key_sym_to_js_key(xkb_keysym_t sym)` |
| `key_sym_to_keycode` | function | `gui/browser_ui.c:14159` | `static int key_sym_to_keycode(xkb_keysym_t sym)` |
| `keyboard_enter` | function | `gui/browser_ui.c:14117` | `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...` |
| `keyboard_key` | function | `gui/browser_ui.c:14624` | `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...` |
| `keyboard_keymap` | function | `gui/browser_ui.c:14096` | `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...` |
| `keyboard_leave` | function | `gui/browser_ui.c:14125` | `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)` |
| `keyboard_modifiers` | function | `gui/browser_ui.c:14664` | `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...` |
| `keyboard_repeat_info` | function | `gui/browser_ui.c:14674` | `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)` |
| `kill` | function | `gui/browser_ui.c:8225` | `kill(w->audio_pid, SIGKILL);` |
| `kind` | type_alias | `gui/browser_ui.c:2879` | `typedef struct rc_row { rc_rowkind kind;` |
| `layer` | function | `gui/browser_ui.c:9067` | `* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the border` |
| `layout` | function | `gui/browser_ui.c:1120` | `* shared by layout (row height) and paint (blit), so they cannot drift apart. */
static int image...` |
| `layout_container` | function | `gui/browser_ui.c:4876` | `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...` |
| `layout_doc` | function | `gui/browser_ui.c:7010` | `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...` |
| `layout_float_band` | function | `gui/browser_ui.c:6652` | `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...` |
| `leave_inline_box` | function | `gui/browser_ui.c:6895` | `leave_inline_box(L, &si, bk->block_id);` |
| `limits` | function | `gui/browser_ui.c:10290` | `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...` |
| `line` | function | `gui/browser_ui.c:3781` | `* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the same ` |
| `line_desc` | type_alias | `gui/browser_ui.c:3043` | `typedef struct rc_state { double cur_top, pending_gap, pen_x, line_asc, line_desc;` |
| `line_limit` | function | `gui/browser_ui.c:3225` | `static double line_limit(const rc_state *s, double content_w)` |
| `link_at_point` | function | `gui/browser_ui.c:11420` | `static const char *link_at_point(browser_window *w, double px, double py)` |
| `load_bg_images` | function | `gui/browser_ui.c:1893` | `static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)` |
| `load_current` | function | `gui/browser_ui.c:13481` | `static void load_current(browser_window *w)` |
| `load_favorites` | function | `gui/browser_ui.c:839` | `static void load_favorites(browser_window *w)` |
| `load_host_file` | function | `gui/browser_ui.c:674` | `static void load_host_file(hb_set *s, const char *dir, const char *name, hb_list list)` |
| `load_images` | function | `gui/browser_ui.c:1808` | `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)` |
| `loop` | function | `gui/browser_ui.c:13976` | `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately mig` |
| `main` | function | `gui/browser_ui.c:486` | `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never blocks` |
| `measure_item_content_w` | function | `gui/browser_ui.c:4651` | `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...` |
| `measure_item_w_at` | function | `gui/browser_ui.c:4655` | `return measure_item_w_at(cr, w, th, doc, b0, b1, FLEX_MEASURE_W);` |
| `memcpy` | function | `gui/browser_ui.c:803` | `memcpy(txt, cur, cur_len);` |
| `memory` | function | `gui/browser_ui.c:11688` | `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...` |
| `memset` | function | `gui/browser_ui.c:980` | `memset(&w->net_cfg, 0, sizeof w->net_cfg);` |
| `menu_item_checked` | function | `gui/browser_ui.c:12026` | `static int menu_item_checked(const browser_window *w, size_t i)` |
| `menu_item_toggle` | function | `gui/browser_ui.c:12048` | `static void menu_item_toggle(browser_window *w, size_t i)` |
| `menu_panel_rect` | function | `gui/browser_ui.c:2774` | `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...` |
| `mime_is_text` | function | `gui/browser_ui.c:13813` | `static int mime_is_text(const char *mime)` |
| `mkdir` | function | `gui/browser_ui.c:757` | `mkdir(cfg, 0700);` |
| `mr` | type_alias | `gui/browser_ui.c:4413` | `typedef struct item_sides { double ml, mr;` |
| `multicol_fragment` | function | `gui/browser_ui.c:5527` | `static double multicol_fragment(rc_layout *L, const rc_open_box *ob, double content_bottom);` |
| `munmap` | function | `gui/browser_ui.c:14113` | `munmap(map_str, size);` |
| `nested_cont_basis` | function | `gui/browser_ui.c:4697` | `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...` |
| `newtab_x` | function | `gui/browser_ui.c:2553` | `static double newtab_x(const browser_window *w)` |
| `node_at_point` | function | `gui/browser_ui.c:11596` | `static dom_node_id node_at_point(browser_window *w, double px, double py)` |
| `now_ms` | function | `gui/browser_ui.c:145` | `static uint64_t now_ms(void)` |
| `offset` | function | `gui/browser_ui.c:155` | `* offset (labels and the flag live in one place, no magic indices);` |
| `omni_refresh` | function | `gui/browser_ui.c:885` | `static void omni_refresh(browser_window *w)` |
| `open_box` | function | `gui/browser_ui.c:6112` | `open_box(L, s, th, path[k], d, ctx_left, ctx_w, shrink, align);` |
| `open_line` | function | `gui/browser_ui.c:3598` | `static void open_line(rc_layout *L, rc_state *s)` |
| `open_line_height` | function | `gui/browser_ui.c:3586` | `static double open_line_height(const rc_state *s, const ui_theme *th)` |
| `origin` | function | `gui/browser_ui.c:11303` | `* top_url is the page origin (https or file://);` |
| `ov_box_bounds` | function | `gui/browser_ui.c:9597` | `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)` |
| `ov_box_clips` | function | `gui/browser_ui.c:9569` | `static int ov_box_clips(const pv_box_def *d)` |
| `ov_collect_chain` | function | `gui/browser_ui.c:9576` | `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)` |
| `ov_content_rect` | function | `gui/browser_ui.c:9621` | `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...` |
| `ov_reconcile` | function | `gui/browser_ui.c:10454` | `ov_reconcile(cr, ov_stack, &ov_depth, w->doc, bx->block_id, L, origin, left);` |
| `own` | function | `gui/browser_ui.c:5425` | `* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and its ` |
| `page_js_host_allowlisted` | function | `gui/browser_ui.c:1948` | `static int page_js_host_allowlisted(const browser_window *w)` |
| `paint` | function | `gui/browser_ui.c:12469` | `static void paint(browser_window *w)` |
| `paint_bg_layer` | function | `gui/browser_ui.c:8907` | `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...` |
| `paint_box_and_direct_rows` | function | `gui/browser_ui.c:10399` | `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...` |
| `paint_box_decoration` | function | `gui/browser_ui.c:8950` | `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...` |
| `paint_box_decoration_grouped` | function | `gui/browser_ui.c:10358` | `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...` |
| `paint_content_row` | function | `gui/browser_ui.c:9380` | `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...` |
| `paint_deco_line` | function | `gui/browser_ui.c:9276` | `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...` |
| `paint_image_row` | function | `gui/browser_ui.c:9375` | `paint_image_row(cr, w, blk, x - th->image_box_pad, y - th->image_box_pad, f->repl_w + 2.0 * th->image_box_pad, f->repl_h` |
| `paint_inline_replaced` | function | `gui/browser_ui.c:9361` | `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...` |
| `paint_nested_children` | function | `gui/browser_ui.c:10683` | `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...` |
| `paint_positioned_one` | function | `gui/browser_ui.c:10494` | `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...` |
| `paint_structured` | function | `gui/browser_ui.c:10715` | `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...` |
| `paint_svg_at` | function | `gui/browser_ui.c:9332` | `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...` |
| `paint_video_row` | function | `gui/browser_ui.c:8621` | `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...` |
| `path` | function | `gui/browser_ui.c:5197` | `*
         * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when
        ...` |
| `pf_list_free` | function | `gui/browser_ui.c:2103` | `pf_list_free(&scanned);` |
| `place_inline_replaced` | function | `gui/browser_ui.c:4009` | `static int place_inline_replaced(rc_layout *L, rc_state *s, const ui_theme *th,
                 ...` |
| `poll` | function | `gui/browser_ui.c:8137` | `poll(&pfd, 1, 10);` |
| `position_doc` | function | `gui/browser_ui.c:7381` | `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...` |
| `prefs_free` | function | `gui/browser_ui.c:15193` | `prefs_free(&w.prefs);` |
| `prefs_init` | function | `gui/browser_ui.c:14757` | `prefs_init(&w.prefs);` |
| `prepare_fetch` | function | `gui/browser_ui.c:1495` | `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...` |
| `presentation` | function | `gui/browser_ui.c:12046` | `* affect presentation (a repaint, which re-runs layout, suffices);` |
| `printf` | function | `gui/browser_ui.c:11376` | `printf("=== Freedom layout ===\n");` |
| `proceed` | function | `gui/browser_ui.c:1492` | `* may proceed (cfg and pr->allowlisted are then set);` |
| `produced` | function | `gui/browser_ui.c:3697` | `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target without ` |
| `profile_close` | function | `gui/browser_ui.c:15194` | `profile_close(&w.profile);` |
| `profile_sync` | function | `gui/browser_ui.c:916` | `static void profile_sync(browser_window *w)` |
| `proxy` | function | `gui/browser_ui.c:976` | `* and enable each proxy ("1" => the default port);` |
| `proxy_addr_from_env` | function | `gui/browser_ui.c:965` | `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...` |
| `pthread_detach` | function | `gui/browser_ui.c:1734` | `pthread_detach(th);` |
| `pthread_join` | function | `gui/browser_ui.c:8285` | `pthread_join(w->video_thread, NULL);` |
| `pthread_mutex_destroy` | function | `gui/browser_ui.c:15172` | `pthread_mutex_destroy(&w.stream_lock);` |
| `pthread_mutex_init` | function | `gui/browser_ui.c:14806` | `pthread_mutex_init(&w.stream_lock, NULL);` |
| `pthread_mutex_lock` | function | `gui/browser_ui.c:1623` | `pthread_mutex_lock(&w->stream_lock);` |
| `pthread_mutex_unlock` | function | `gui/browser_ui.c:1631` | `pthread_mutex_unlock(&w->stream_lock);` |
| `ptr_axis` | function | `gui/browser_ui.c:13772` | `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...` |
| `ptr_button` | function | `gui/browser_ui.c:13539` | `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...` |
| `ptr_enter` | function | `gui/browser_ui.c:13421` | `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...` |
| `ptr_frame` | function | `gui/browser_ui.c:13796` | `static void ptr_frame(void *d, struct wl_pointer *p)` |
| `ptr_leave` | function | `gui/browser_ui.c:13440` | `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)` |
| `ptr_motion` | function | `gui/browser_ui.c:13457` | `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)` |
| `rc_add_box` | function | `gui/browser_ui.c:3238` | `static rc_box *rc_add_box(rc_layout *L)` |
| `rc_add_frag` | function | `gui/browser_ui.c:3250` | `static rc_frag *rc_add_frag(rc_layout *L)` |
| `rc_add_row` | function | `gui/browser_ui.c:3265` | `static rc_row *rc_add_row(rc_layout *L)` |
| `rc_box` | struct | `gui/browser_ui.c:2899` | `` |
| `rc_box_context` | function | `gui/browser_ui.c:5673` | `static void rc_box_context(const rc_state *s, double content_w,
                           double...` |
| `rc_box_copy_decoration` | function | `gui/browser_ui.c:4363` | `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)` |
| `rc_defer` | struct | `gui/browser_ui.c:6253` | `` |
| `rc_defer_col` | struct | `gui/browser_ui.c:6246` | `` |
| `rc_ext` | struct | `gui/browser_ui.c:3618` | `` |
| `rc_float_bottom` | function | `gui/browser_ui.c:3138` | `static double rc_float_bottom(const rc_state *s)` |
| `rc_float_clear` | function | `gui/browser_ui.c:3147` | `static void rc_float_clear(rc_state *s)` |
| `rc_float_fit_line` | function | `gui/browser_ui.c:3206` | `static void rc_float_fit_line(rc_state *s, double line_h)` |
| `rc_float_refresh` | function | `gui/browser_ui.c:3160` | `static void rc_float_refresh(rc_state *s, double line_h)` |
| `rc_frag` | struct | `gui/browser_ui.c:2820` | `` |
| `rc_free` | function | `gui/browser_ui.c:3229` | `static void rc_free(rc_layout *L)` |
| `rc_layout` | struct | `gui/browser_ui.c:2950` | `` |
| `rc_open_box` | struct | `gui/browser_ui.c:2986` | `` |
| `rc_row` | struct | `gui/browser_ui.c:2880` | `` |
| `rc_rowkind` | enum | `gui/browser_ui.c:2878` | `` |
| `rc_state` | struct | `gui/browser_ui.c:3044` | `` |
| `rd_build` | function | `gui/browser_ui.c:7943` | `* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr, rgb_from_packed(b-` |
| `rd_input_label` | function | `gui/browser_ui.c:7552` | `: rd_input_label(b->input_type);` |
| `read_file` | function | `gui/browser_ui.c:624` | `static char *read_file(const char *path, size_t *out_len)` |
| `rebuild_inputs` | function | `gui/browser_ui.c:1169` | `static void rebuild_inputs(browser_window *w)` |
| `reconcile_boxes` | function | `gui/browser_ui.c:6115` | `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...` |
| `reconcile_boxes_below` | function | `gui/browser_ui.c:6042` | `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...` |
| `rect` | function | `gui/browser_ui.c:8815` | `* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops land on` |
| `redraw` | function | `gui/browser_ui.c:12713` | `static void redraw(browser_window *w)` |
| `redraws` | function | `gui/browser_ui.c:14835` | `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A 4 Ki` |
| `reference` | function | `gui/browser_ui.c:11644` | `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...` |
| `registry_global` | function | `gui/browser_ui.c:14710` | `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...` |
| `registry_remove` | function | `gui/browser_ui.c:14731` | `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)` |
| `remember_visit` | function | `gui/browser_ui.c:933` | `static void remember_visit(browser_window *w, const char *url)` |
| `render_current` | function | `gui/browser_ui.c:2196` | `static void render_current(browser_window *w)` |
| `render_current_ex` | function | `gui/browser_ui.c:2023` | `static void render_current_ex(browser_window *w, int allow_js_nav)` |
| `render_doc_images` | function | `gui/browser_ui.c:11307` | `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...` |
| `replaced_current_color` | function | `gui/browser_ui.c:9352` | `static int replaced_current_color(const browser_window *w, const rd_block *blk)` |
| `replaced_inline_size` | function | `gui/browser_ui.c:3966` | `static int replaced_inline_size(const browser_window *w, const rd_block *b,
                     ...` |
| `replaced_is_inline_level` | function | `gui/browser_ui.c:3996` | `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)` |
| `resizes` | function | `gui/browser_ui.c:12748` | `* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);` |
| `resolve` | function | `gui/browser_ui.c:2365` | `* origin so its relative references and local images resolve (confined to the * document's directory) -- a local page "a` |
| `resolve_box_cursor` | function | `gui/browser_ui.c:11514` | `static int resolve_box_cursor(const rd_doc *doc, int block_id)` |
| `rewind` | function | `gui/browser_ui.c:631` | `rewind(f);` |
| `rgb_from_packed` | function | `gui/browser_ui.c:8866` | `return rgb_from_packed(cols[nst - 1] >= 0 ? cols[nst - 1] : 0);` |
| `root_cont_of` | function | `gui/browser_ui.c:4823` | `static int root_cont_of(const rd_doc *doc, int cid)` |
| `row` | function | `gui/browser_ui.c:4575` | `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...` |
| `row_align_offset` | function | `gui/browser_ui.c:8746` | `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)` |
| `row_line_slack` | function | `gui/browser_ui.c:8734` | `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)` |
| `row_owner_block_id` | function | `gui/browser_ui.c:9327` | `static int row_owner_block_id(const rc_layout *L, const rc_row *r);` |
| `rows` | function | `gui/browser_ui.c:9640` | `* RC_IMAGE rows (see its declaration);` |
| `run` | function | `gui/browser_ui.c:3503` | `* continuation run (block_id < 0 with no block break) deliberately skips reconcile
 * to stay on ...` |
| `save_current_page` | function | `gui/browser_ui.c:11875` | `static void save_current_page(browser_window *w)` |
| `save_download` | function | `gui/browser_ui.c:11842` | `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...` |
| `saving` | function | `gui/browser_ui.c:14756` | `* disables saving (never clobber);` |
| `schedule_js_tick` | function | `gui/browser_ui.c:2014` | `static void schedule_js_tick(browser_window *w, int next_ms)` |
| `scroll_line_px` | function | `gui/browser_ui.c:13769` | `static double scroll_line_px(const browser_window *w)` |
| `scrollbar_drag_to` | function | `gui/browser_ui.c:2668` | `static void scrollbar_drag_to(browser_window *w)` |
| `scrollbar_metrics` | function | `gui/browser_ui.c:2640` | `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...` |
| `seat_caps` | function | `gui/browser_ui.c:14692` | `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)` |
| `seat_name` | function | `gui/browser_ui.c:14704` | `static void seat_name(void *d, struct wl_seat *s, const char *name)` |
| `secure_fetch` | function | `gui/browser_ui.c:1740` | `* through secure_fetch (Zero Trust);` |
| `seed_session_cookies` | function | `gui/browser_ui.c:1968` | `static void seed_session_cookies(tab *t, int trusted, const char *url)` |
| `select_box_width` | function | `gui/browser_ui.c:7542` | `static double select_box_width(double content_w)` |
| `set_cache` | function | `gui/browser_ui.c:1212` | `static void set_cache(browser_window *w, char *html, size_t len, const char *top)` |
| `set_cursor` | function | `gui/browser_ui.c:12783` | `static void set_cursor(browser_window *w, int cur_kind)` |
| `set_rgb` | function | `gui/browser_ui.c:9192` | `set_rgb(cr, (ui_rgb)` |
| `set_rgb_alpha` | function | `gui/browser_ui.c:3309` | `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)` |
| `sf_cookie_put` | function | `gui/browser_ui.c:1991` | `sf_cookie_put(url, pair);` |
| `sf_global_init` | function | `gui/browser_ui.c:14797` | `sf_global_init();` |
| `sf_response_free` | function | `gui/browser_ui.c:1303` | `sf_response_free(out);` |
| `show_busy` | function | `gui/browser_ui.c:2203` | `static void show_busy(browser_window *w)` |
| `show_fetch_error` | function | `gui/browser_ui.c:2212` | `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...` |
| `signal` | function | `gui/browser_ui.c:8576` | `signal(SIGPIPE, SIG_IGN);` |
| `slot` | function | `gui/browser_ui.c:5079` | `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...` |
| `smaller` | function | `gui/browser_ui.c:2921` | `* size when the content is smaller (height) or wider (min-width);` |
| `snprintf` | function | `gui/browser_ui.c:575` | `snprintf(msg, sizeof msg, "Zoom %d%%", w->zoom_pct);` |
| `spaced` | function | `gui/browser_ui.c:8875` | `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...` |
| `standalone` | function | `gui/browser_ui.c:7236` | `* must not be treated as standalone (which would flush that line and give * the element a row of its own -- R7). */ int ` |
| `strcmp` | function | `gui/browser_ui.c:2331` | `&& strcmp(auth_host_buf, w->auth_host) != 0)` |
| `stream_progress_cb` | function | `gui/browser_ui.c:1616` | `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)` |
| `string` | function | `gui/browser_ui.c:1888` | `* or an empty string (unset, blocked, or off by caps.images), so there is no * decision to re-check, unlike load_images ` |
| `struct` | function | `gui/browser_ui.c:5184` | `* struct (0 = auto);` |
| `styled_advance` | function | `gui/browser_ui.c:3378` | `static double styled_advance(cairo_t *cr, const rc_frag *f)` |
| `styled_draw` | function | `gui/browser_ui.c:3394` | `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)` |
| `stylesheets` | function | `gui/browser_ui.c:2044` | `* External stylesheets (Hito 27) follow the author-styles opt-in -- or the * trusted-host doctrine (Hito 28) -- (GET-onl` |
| `submit_form` | function | `gui/browser_ui.c:13744` | `submit_form(w, ctl);` |
| `surface_from_pixels` | function | `gui/browser_ui.c:1223` | `static cairo_surface_t *surface_from_pixels(const tab_image *img)` |
| `svg_intrinsic_size` | function | `gui/browser_ui.c:3970` | `svg_intrinsic_size(b, &sw, &sh);` |
| `tab_close` | function | `gui/browser_ui.c:2107` | `tab_close(t);` |
| `tab_ctx` | struct | `gui/browser_ui.c:266` | `` |
| `tab_ctx_release` | function | `gui/browser_ui.c:2435` | `static void tab_ctx_release(tab_ctx *c)` |
| `tab_eval_result_free` | function | `gui/browser_ui.c:13320` | `tab_eval_result_free(&r);` |
| `tab_image_free` | function | `gui/browser_ui.c:1775` | `tab_image_free(&img);` |
| `tab_new` | function | `gui/browser_ui.c:2478` | `static void tab_new(browser_window *w, const char *url)` |
| `tab_page_free` | function | `gui/browser_ui.c:2125` | `tab_page_free(&page);` |
| `tab_restore` | function | `gui/browser_ui.c:2409` | `static void tab_restore(browser_window *w)` |
| `tab_save` | function | `gui/browser_ui.c:2392` | `static void tab_save(browser_window *w)` |
| `tab_set_cookies` | function | `gui/browser_ui.c:1972` | `tab_set_cookies(t, ckhdr);` |
| `tab_set_css_allowed` | function | `gui/browser_ui.c:2059` | `tab_set_css_allowed(t, wc.css);` |
| `tab_set_fetcher` | function | `gui/browser_ui.c:2084` | `tab_set_fetcher(t, pf_pooled_fetch, &gated);` |
| `tab_set_net_allowed` | function | `gui/browser_ui.c:2058` | `tab_set_net_allowed(t, wc.net);` |
| `tab_set_viewport_w` | function | `gui/browser_ui.c:2094` | `tab_set_viewport_w(t, (int)w->width);` |
| `tab_switch` | function | `gui/browser_ui.c:2459` | `static void tab_switch(browser_window *w, int idx)` |
| `tab_title` | function | `gui/browser_ui.c:2560` | `static const char *tab_title(const browser_window *w, int i)` |
| `tabbar_top` | function | `gui/browser_ui.c:2576` | `static double tabbar_top(const browser_window *w)` |
| `table` | function | `gui/browser_ui.c:4515` | `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...` |
| `text` | function | `gui/browser_ui.c:8819` | `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...` |
| `tf_backspace` | function | `gui/browser_ui.c:14425` | `tf_backspace(&w->ua_field);` |
| `tf_clear` | function | `gui/browser_ui.c:13323` | `tf_clear(&fb->editor);` |
| `tf_delete` | function | `gui/browser_ui.c:14427` | `tf_delete(&w->ua_field);` |
| `tf_end` | function | `gui/browser_ui.c:14435` | `tf_end(&w->ua_field);` |
| `tf_home` | function | `gui/browser_ui.c:14433` | `tf_home(&w->ua_field);` |
| `tf_init` | function | `gui/browser_ui.c:1187` | `tf_init(&st->field);` |
| `tf_insert` | function | `gui/browser_ui.c:13342` | `tf_insert(&fb->editor, '\n');` |
| `tf_move` | function | `gui/browser_ui.c:14429` | `tf_move(&w->ua_field, -1);` |
| `tf_set` | function | `gui/browser_ui.c:14210` | `tf_set(&w->inputs[i].field, value);` |
| `the` | function | `gui/browser_ui.c:10212` | `* the (already filtered) group with the shadow color, blur it, and * paint it under the group at the declared offset -- ` |
| `thumbnail` | function | `gui/browser_ui.c:6735` | `* is what made a wikipedia thumbnail (a 250px image and its caption, no
     * declared width) sp...` |
| `timerfd_settime` | function | `gui/browser_ui.c:14596` | `timerfd_settime(w->repeat_timer_fd, 0, &its, NULL);` |
| `toggle` | function | `gui/browser_ui.c:1937` | `* No network: a capability toggle (images/CSS) re-renders from cache. Does nothing * when there is no cached source (sta` |
| `toggle_fullscreen` | function | `gui/browser_ui.c:1034` | `static void toggle_fullscreen(browser_window *w)` |
| `toggle_reader` | function | `gui/browser_ui.c:12015` | `static void toggle_reader(browser_window *w)` |
| `toolbar_button_at` | function | `gui/browser_ui.c:2747` | `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)` |
| `toolbar_rects` | function | `gui/browser_ui.c:2731` | `static void toolbar_rects(const browser_window *w,
                          double *back_x, doub...` |
| `toolbar_top` | function | `gui/browser_ui.c:2582` | `static double toolbar_top(const browser_window *w)` |
| `toplevel_close` | function | `gui/browser_ui.c:12762` | `static void toplevel_close(void *data, struct xdg_toplevel *t)` |
| `toplevel_configure` | function | `gui/browser_ui.c:12739` | `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...` |
| `treatment` | function | `gui/browser_ui.c:6088` | `* block treatment (shrink-wrapped and placed by text-align), which is what a
         * standalon...` |
| `tsh_shutdown` | function | `gui/browser_ui.c:15201` | `tsh_shutdown();` |
| `ua_box_rect` | function | `gui/browser_ui.c:2790` | `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...` |
| `ui_bg_image` | struct | `gui/browser_ui.c:249` | `` |
| `ui_dump_layout` | function | `gui/browser_ui.c:11359` | `ui_status ui_dump_layout(const rd_doc *doc)` |
| `ui_hot` | enum | `gui/browser_ui.c:205` | `` |
| `ui_image` | struct | `gui/browser_ui.c:236` | `` |
| `ui_input_state` | struct | `gui/browser_ui.c:212` | `` |
| `ui_layout_free` | function | `gui/browser_ui.c:12697` | `ui_layout_free(&lay);` |
| `ui_menu_action` | enum | `gui/browser_ui.c:157` | `` |
| `ui_menu_item` | struct | `gui/browser_ui.c:174` | `` |
| `ui_render_pdf_images` | function | `gui/browser_ui.c:11343` | `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...` |
| `ui_render_png` | function | `gui/browser_ui.c:11281` | `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)` |
| `ui_render_png_images` | function | `gui/browser_ui.c:11337` | `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...` |
| `ui_run_browser` | function | `gui/browser_ui.c:14740` | `ui_status ui_run_browser(const char *start_url)` |
| `uitab_close` | function | `gui/browser_ui.c:2511` | `static void uitab_close(browser_window *w, int idx)` |
| `unlink` | function | `gui/browser_ui.c:11835` | `unlink(tmp);` |
| `update_hover` | function | `gui/browser_ui.c:13432` | `update_hover(w);` |
| `upstream` | function | `gui/browser_ui.c:8774` | `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...` |
| `utf8_clen` | function | `gui/browser_ui.c:3318` | `static size_t utf8_clen(const char *s, size_t n)` |
| `v_read` | function | `gui/browser_ui.c:8128` | `static int v_read(int fd, void *buf, size_t n)` |
| `v_write` | function | `gui/browser_ui.c:8601` | `v_write(w->decoder_cmd_fd, &cmd, 1);` |
| `video_feeder_thread` | function | `gui/browser_ui.c:1029` | `static void *video_feeder_thread(void *arg);` |
| `video_fetch` | function | `gui/browser_ui.c:8449` | `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...` |
| `video_play` | function | `gui/browser_ui.c:8466` | `static int video_play(browser_window *w, const char *m3u8_url)` |
| `video_stop` | function | `gui/browser_ui.c:8270` | `static void video_stop(browser_window *w)` |
| `video_stop` | function | `gui/browser_ui.c:8568` | `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...` |
| `waitpid` | function | `gui/browser_ui.c:8226` | `waitpid(w->audio_pid, NULL, 0);` |
| `way` | function | `gui/browser_ui.c:4616` | `* intrinsic box either way (it does not wrap below its own size). */
static double measure_item_w...` |
| `window_button_rects` | function | `gui/browser_ui.c:2721` | `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...` |
| `wl_array_for_each` | function | `gui/browser_ui.c:12756` | `wl_array_for_each(st, states)` |
| `wl_buffer_add_listener` | function | `gui/browser_ui.c:614` | `wl_buffer_add_listener(w->buffer, &buffer_listener, w);` |
| `wl_data_device_add_listener` | function | `gui/browser_ui.c:14859` | `wl_data_device_add_listener(w.data_device, &data_device_listener, &w);` |
| `wl_data_device_set_selection` | function | `gui/browser_ui.c:13974` | `wl_data_device_set_selection(w->data_device, w->copy_source, w->last_serial);` |
| `wl_data_offer_add_listener` | function | `gui/browser_ui.c:13851` | `wl_data_offer_add_listener(offer, &data_offer_listener, w);` |
| `wl_data_offer_receive` | function | `gui/browser_ui.c:14015` | `wl_data_offer_receive(w->selection_offer, mime, fds[1]);` |
| `wl_data_source_add_listener` | function | `gui/browser_ui.c:13971` | `wl_data_source_add_listener(w->copy_source, &data_source_listener, w);` |
| `wl_data_source_destroy` | function | `gui/browser_ui.c:13899` | `wl_data_source_destroy(src);` |
| `wl_data_source_offer` | function | `gui/browser_ui.c:13973` | `wl_data_source_offer(w->copy_source, "text/plain");` |
| `wl_display_cancel_read` | function | `gui/browser_ui.c:15017` | `wl_display_cancel_read(w.display);` |
| `wl_display_disconnect` | function | `gui/browser_ui.c:14849` | `wl_display_disconnect(w.display);` |
| `wl_display_dispatch_pending` | function | `gui/browser_ui.c:14948` | `wl_display_dispatch_pending(w.display);` |
| `wl_display_flush` | function | `gui/browser_ui.c:12721` | `wl_display_flush(w->display);` |
| `wl_display_roundtrip` | function | `gui/browser_ui.c:14018` | `wl_display_roundtrip(w->display);` |
| `wl_keyboard_add_listener` | function | `gui/browser_ui.c:14701` | `wl_keyboard_add_listener(w->keyboard, &keyboard_listener, w);` |
| `wl_pointer_add_listener` | function | `gui/browser_ui.c:14697` | `wl_pointer_add_listener(w->pointer, &pointer_listener, w);` |
| `wl_pointer_set_cursor` | function | `gui/browser_ui.c:12803` | `wl_pointer_set_cursor(w->pointer, w->pointer_serial, w->cursor_surface, (int32_t)img->hotspot_x, (int32_t)img->hotspot_y` |
| `wl_registry_add_listener` | function | `gui/browser_ui.c:14845` | `wl_registry_add_listener(w.registry, &registry_listener, &w);` |
| `wl_seat_add_listener` | function | `gui/browser_ui.c:14724` | `wl_seat_add_listener(w->seat, &seat_listener, w);` |
| `wl_shm_pool_destroy` | function | `gui/browser_ui.c:611` | `wl_shm_pool_destroy(pool);` |
| `wl_surface_attach` | function | `gui/browser_ui.c:12718` | `wl_surface_attach(w->surface, w->buffer, 0, 0);` |
| `wl_surface_commit` | function | `gui/browser_ui.c:12720` | `wl_surface_commit(w->surface);` |
| `wl_surface_damage` | function | `gui/browser_ui.c:12806` | `wl_surface_damage(w->cursor_surface, 0, 0, (int32_t)img->width, (int32_t)img->height);` |
| `wl_surface_damage_buffer` | function | `gui/browser_ui.c:12719` | `wl_surface_damage_buffer(w->surface, 0, 0, w->width, w->height);` |
| `wm_base_ping` | function | `gui/browser_ui.c:12725` | `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)` |
| `write_doc_pdf` | function | `gui/browser_ui.c:10933` | `static long write_doc_pdf(browser_window *w, const char *path)` |
| `write_doc_png` | function | `gui/browser_ui.c:11102` | `static long write_doc_png(browser_window *w, const char *path)` |
| `write_file_atomic` | function | `gui/browser_ui.c:11820` | `static int write_file_atomic(const char *path, const void *bytes, size_t len)` |
| `x` | function | `gui/browser_ui.c:6484` | `* reported x is already the BORDER x (the §7c.2 rule);` |
| `xdg_surface_ack_configure` | function | `gui/browser_ui.c:12734` | `xdg_surface_ack_configure(s, serial);` |
| `xdg_surface_add_listener` | function | `gui/browser_ui.c:13214` | `xdg_surface_add_listener(fb->xdg_surface, &fbw_xdg_surface_listener, fb);` |
| `xdg_surface_configure` | function | `gui/browser_ui.c:12731` | `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)` |
| `xdg_toplevel_add_listener` | function | `gui/browser_ui.c:13216` | `xdg_toplevel_add_listener(fb->xdg_toplevel, &fbw_toplevel_listener, fb);` |
| `xdg_toplevel_move` | function | `gui/browser_ui.c:13665` | `xdg_toplevel_move(w->xdg_toplevel, w->seat, serial);` |
| `xdg_toplevel_set_app_id` | function | `gui/browser_ui.c:13218` | `xdg_toplevel_set_app_id(fb->xdg_toplevel, "org.freedom.freebug");` |
| `xdg_toplevel_set_fullscreen` | function | `gui/browser_ui.c:1039` | `xdg_toplevel_set_fullscreen(w->xdg_toplevel, NULL);` |
| `xdg_toplevel_set_maximized` | function | `gui/browser_ui.c:13661` | `else xdg_toplevel_set_maximized(w->xdg_toplevel);` |
| `xdg_toplevel_set_minimized` | function | `gui/browser_ui.c:13663` | `xdg_toplevel_set_minimized(w->xdg_toplevel);` |
| `xdg_toplevel_set_title` | function | `gui/browser_ui.c:13217` | `xdg_toplevel_set_title(fb->xdg_toplevel, "Freebug - Freedom DevTools");` |
| `xdg_toplevel_unset_fullscreen` | function | `gui/browser_ui.c:1037` | `xdg_toplevel_unset_fullscreen(w->xdg_toplevel);` |
| `xdg_wm_base_add_listener` | function | `gui/browser_ui.c:14721` | `xdg_wm_base_add_listener(w->wm_base, &wm_base_listener, w);` |
| `xdg_wm_base_pong` | function | `gui/browser_ui.c:12728` | `xdg_wm_base_pong(b, serial);` |
| `xkb_context_unref` | function | `gui/browser_ui.c:14851` | `xkb_context_unref(w.xkb_ctx);` |
| `xkb_state_update_mask` | function | `gui/browser_ui.c:14671` | `xkb_state_update_mask(w->xkb_state, mods_depressed, mods_latched, mods_locked, 0, 0, group);` |
| `zxdg_toplevel_decoration_v1_add_listener` | function | `gui/browser_ui.c:14873` | `zxdg_toplevel_decoration_v1_add_listener(w.deco, &deco_listener, &w);` |
| `zxdg_toplevel_decoration_v1_set_mode` | function | `gui/browser_ui.c:13221` | `zxdg_toplevel_decoration_v1_set_mode(fb->deco, ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);` |
| `FREEDOM_BROWSER_UI_INTERNAL_H` | macro | `gui/browser_ui_internal.h:2` | `#define FREEDOM_BROWSER_UI_INTERNAL_H` |
| `UI_FONT_SIZE` | macro | `gui/browser_ui_internal.h:28` | `#define UI_FONT_SIZE` |
| `UI_HEADING_LEVELS` | macro | `gui/browser_ui_internal.h:30` | `#define UI_HEADING_LEVELS` |
| `UI_TEXT_MARGIN` | macro | `gui/browser_ui_internal.h:29` | `#define UI_TEXT_MARGIN` |
| `b` | type_alias | `gui/browser_ui_internal.h:38` | `typedef struct ui_rgb { double r, g, b;` |
| `body_font` | type_alias | `gui/browser_ui_internal.h:40` | `typedef struct ui_theme { double body_font;` |
| `rgb_from_packed` | function | `gui/browser_ui_internal.h:103` | `ui_rgb rgb_from_packed(int packed);` |
| `set_rgb` | function | `gui/browser_ui_internal.h:104` | `void set_rgb(cairo_t *cr, ui_rgb c);` |
| `ui_rgb` | struct | `gui/browser_ui_internal.h:39` | `` |
| `ui_theme` | struct | `gui/browser_ui_internal.h:41` | `` |
| `ui_theme_dark` | function | `gui/browser_ui_internal.h:100` | `ui_theme ui_theme_dark(void);` |
| `ui_theme_default` | function | `gui/browser_ui_internal.h:98` | `ui_theme ui_theme_default(void);` |
| `ui_theme_for` | function | `gui/browser_ui_internal.h:102` | `ui_theme ui_theme_for(int mode);` |
| `ui_theme_mode` | enum | `gui/browser_ui_internal.h:91` | `` |
| `ui_theme_sepia` | function | `gui/browser_ui_internal.h:101` | `ui_theme ui_theme_sepia(void);` |
| `cairo_set_source_rgb` | function | `gui/bui_theme.c:186` | `cairo_set_source_rgb(cr, c.r, c.g, c.b);` |
| `rgb_from_packed` | function | `gui/bui_theme.c:180` | `ui_rgb rgb_from_packed(int packed)` |
| `set_rgb` | function | `gui/bui_theme.c:184` | `void set_rgb(cairo_t *cr, ui_rgb c)` |
| `ui_theme_dark` | function | `gui/bui_theme.c:84` | `ui_theme ui_theme_dark(void)` |
| `ui_theme_default` | function | `gui/bui_theme.c:14` | `ui_theme ui_theme_default(void)` |
| `ui_theme_for` | function | `gui/bui_theme.c:171` | `ui_theme ui_theme_for(int mode)` |
| `ui_theme_sepia` | function | `gui/bui_theme.c:129` | `ui_theme ui_theme_sepia(void)` |
| `_POSIX_C_SOURCE` | macro | `gui/freedom_view.c:9` | `#define _POSIX_C_SOURCE` |
| `fclose` | function | `gui/freedom_view.c:31` | `fclose(f);` |
| `fprintf` | function | `gui/freedom_view.c:39` | `fprintf(stderr, "usage: %s <file.html>\n", argv[0]);` |
| `free` | function | `gui/freedom_view.c:52` | `free(html);` |
| `hp_document_free` | function | `gui/freedom_view.c:61` | `hp_document_free(doc);` |
| `hp_free` | function | `gui/freedom_view.c:67` | `hp_free(title);` |
| `main` | function | `gui/freedom_view.c:36` | `int main(int argc, char **argv)` |
| `rewind` | function | `gui/freedom_view.c:26` | `rewind(f);` |
| `cairo_arc` | function | `gui/svg_paint.c:52` | `cairo_arc(cr, 0.0, 0.0, 1.0, PI, 1.5 * PI);` |
| `cairo_clip` | function | `gui/svg_paint.c:149` | `cairo_clip(cr);` |
| `cairo_close_path` | function | `gui/svg_paint.c:69` | `cairo_close_path(cr);` |
| `cairo_curve_to` | function | `gui/svg_paint.c:112` | `case SV_CUBIC: cairo_curve_to(cr, sg->x[0], sg->y[0], sg->x[1], sg->y[1], sg->x[2], sg->y[2]);` |
| `cairo_fill_preserve` | function | `gui/svg_paint.c:175` | `cairo_fill_preserve(cr);` |
| `cairo_line_to` | function | `gui/svg_paint.c:92` | `cairo_line_to(cr, sh->c, sh->d);` |
| `cairo_matrix_init` | function | `gui/svg_paint.c:158` | `cairo_matrix_init(&m, sh->m[0], sh->m[1], sh->m[2], sh->m[3], sh->m[4], sh->m[5]);` |
| `cairo_move_to` | function | `gui/svg_paint.c:90` | `case SV_LINE: cairo_move_to(cr, sh->a, sh->b);` |
| `cairo_new_path` | function | `gui/svg_paint.c:134` | `cairo_new_path(cr);` |
| `cairo_new_sub_path` | function | `gui/svg_paint.c:48` | `cairo_new_sub_path(cr);` |
| `cairo_rectangle` | function | `gui/svg_paint.c:41` | `cairo_rectangle(cr, x, y, w, h);` |
| `cairo_restore` | function | `gui/svg_paint.c:53` | `cairo_restore(cr);` |
| `cairo_save` | function | `gui/svg_paint.c:49` | `cairo_save(cr);` |
| `cairo_scale` | function | `gui/svg_paint.c:51` | `cairo_scale(cr, rx, ry);` |
| `cairo_select_font_face` | function | `gui/svg_paint.c:130` | `cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);` |
| `cairo_set_fill_rule` | function | `gui/svg_paint.c:173` | `cairo_set_fill_rule(cr, sh->fill_even_odd ? CAIRO_FILL_RULE_EVEN_ODD : CAIRO_FILL_RULE_WINDING);` |
| `cairo_set_font_size` | function | `gui/svg_paint.c:131` | `cairo_set_font_size(cr, (sh->c > 0.0) ? sh->c : 16.0);` |
| `cairo_set_line_cap` | function | `gui/svg_paint.c:180` | `cairo_set_line_cap(cr, (sh->linecap == 1) ? CAIRO_LINE_CAP_ROUND : (sh->linecap == 2) ? CAIRO_LINE_CAP_SQUARE : CAIRO_LI` |
| `cairo_set_line_join` | function | `gui/svg_paint.c:183` | `cairo_set_line_join(cr, (sh->linejoin == 1) ? CAIRO_LINE_JOIN_ROUND : (sh->linejoin == 2) ? CAIRO_LINE_JOIN_BEVEL : CAIR` |
| `cairo_set_line_width` | function | `gui/svg_paint.c:179` | `cairo_set_line_width(cr, sh->stroke_w);` |
| `cairo_set_source_rgba` | function | `gui/svg_paint.c:129` | `cairo_set_source_rgba(cr, r, g, b, svp_alpha(sh->opacity, sh->fill_opacity));` |
| `cairo_show_text` | function | `gui/svg_paint.c:133` | `cairo_show_text(cr, sh->text);` |
| `cairo_stroke` | function | `gui/svg_paint.c:186` | `cairo_stroke(cr);` |
| `cairo_transform` | function | `gui/svg_paint.c:159` | `cairo_transform(cr, &m);` |
| `cairo_translate` | function | `gui/svg_paint.c:50` | `cairo_translate(cr, x + rx, y + ry);` |
| `sv_fit` | function | `gui/svg_paint.c:143` | `sv_fit(img, w, h, &scale, &off_x, &off_y);` |
| `svp_alpha` | function | `gui/svg_paint.c:30` | `static double svp_alpha(int opacity, int paint_opacity)` |
| `svp_draw` | function | `gui/svg_paint.c:137` | `void svp_draw(cairo_t *cr, const sv_image *img,
              double x, double y, double w, doubl...` |
| `svp_draw_text` | function | `gui/svg_paint.c:124` | `static void svp_draw_text(cairo_t *cr, const sv_shape *sh, int current_rgb)` |
| `svp_rect_path` | function | `gui/svg_paint.c:37` | `static void svp_rect_path(cairo_t *cr, const sv_shape *sh)` |
| `svp_shape_path` | function | `gui/svg_paint.c:71` | `static void svp_shape_path(cairo_t *cr, const sv_image *img, const sv_shape *sh)` |
| `UI_BTN_LEFT` | macro | `gui/ui_render.c:30` | `#define UI_BTN_LEFT` |
| `UI_BTN_W` | macro | `gui/ui_render.c:29` | `#define UI_BTN_W` |
| `UI_FONT_SIZE` | macro | `gui/ui_render.c:25` | `#define UI_FONT_SIZE` |
| `UI_MARGIN` | macro | `gui/ui_render.c:27` | `#define UI_MARGIN` |
| `UI_TITLEBAR_H` | macro | `gui/ui_render.c:28` | `#define UI_TITLEBAR_H` |
| `_GNU_SOURCE` | macro | `gui/ui_render.c:9` | `#define _GNU_SOURCE` |
| `buffer_release` | function | `gui/ui_render.c:112` | `static void buffer_release(void *data, struct wl_buffer *wl_buffer)` |
| `button_rects` | function | `gui/ui_render.c:105` | `static void button_rects(const ui_window *w, double *min_x, double *max_x, double *close_x)` |
| `cairo_destroy` | function | `gui/ui_render.c:208` | `cairo_destroy(cr);` |
| `cairo_fill` | function | `gui/ui_render.c:182` | `cairo_fill(cr);` |
| `cairo_font_extents` | function | `gui/ui_render.c:168` | `cairo_font_extents(cr, &fe);` |
| `cairo_move_to` | function | `gui/ui_render.c:185` | `cairo_move_to(cr, UI_MARGIN, bl);` |
| `cairo_paint` | function | `gui/ui_render.c:161` | `cairo_paint(cr);` |
| `cairo_rectangle` | function | `gui/ui_render.c:181` | `cairo_rectangle(cr, 0, 0, w->width, UI_TITLEBAR_H);` |
| `cairo_select_font_face` | function | `gui/ui_render.c:162` | `cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);` |
| `cairo_set_font_size` | function | `gui/ui_render.c:165` | `cairo_set_font_size(cr, UI_FONT_SIZE);` |
| `cairo_set_source_rgb` | function | `gui/ui_render.c:159` | `cairo_set_source_rgb(cr, 1, 1, 1);` |
| `cairo_show_text` | function | `gui/ui_render.c:186` | `cairo_show_text(cr, (w->title != NULL) ? w->title : "Freedom");` |
| `cairo_surface_flush` | function | `gui/ui_render.c:239` | `cairo_surface_flush(w->cairo_surface);` |
| `cairo_text_extents` | function | `gui/ui_render.c:170` | `cairo_text_extents(cr, "M", &te);` |
| `close` | function | `gui/ui_render.c:144` | `close(fd);` |
| `deco_configure` | function | `gui/ui_render.c:292` | `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)` |
| `destroy_buffer` | function | `gui/ui_render.c:119` | `static void destroy_buffer(ui_window *w)` |
| `ensure_buffer` | function | `gui/ui_render.c:125` | `static int ensure_buffer(ui_window *w)` |
| `fprintf` | function | `gui/ui_render.c:213` | `fprintf(stderr, "[ui] paint csd=%d cols=%zu viewport=%zu total_lines=%zu scroll=%zu\n", w->use_csd, max_cols, viewport_l` |
| `free` | function | `gui/ui_render.c:235` | `free(linebuf);` |
| `memcpy` | function | `gui/ui_render.c:228` | `memcpy(linebuf, w->text + lay.lines[idx].offset, n);` |
| `memset` | function | `gui/ui_render.c:412` | `memset(&w, 0, sizeof w);` |
| `paint` | function | `gui/ui_render.c:156` | `static void paint(ui_window *w)` |
| `ptr_axis` | function | `gui/ui_render.c:342` | `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...` |
| `ptr_button` | function | `gui/ui_render.c:320` | `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...` |
| `ptr_enter` | function | `gui/ui_render.c:302` | `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...` |
| `ptr_leave` | function | `gui/ui_render.c:310` | `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)` |
| `ptr_motion` | function | `gui/ui_render.c:313` | `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)` |
| `redraw` | function | `gui/ui_render.c:242` | `static void redraw(ui_window *w)` |
| `registry_global` | function | `gui/ui_render.c:380` | `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...` |
| `registry_remove` | function | `gui/ui_render.c:399` | `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)` |
| `sanitize_utf8_inplace` | function | `gui/ui_render.c:37` | `static void sanitize_utf8_inplace(char *s)` |
| `seat_caps` | function | `gui/ui_render.c:364` | `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)` |
| `seat_name` | function | `gui/ui_render.c:374` | `static void seat_name(void *d, struct wl_seat *s, const char *name)` |
| `toplevel_close` | function | `gui/ui_render.c:281` | `static void toplevel_close(void *data, struct xdg_toplevel *t)` |
| `toplevel_configure` | function | `gui/ui_render.c:271` | `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...` |
| `ui_layout_free` | function | `gui/ui_render.c:237` | `ui_layout_free(&lay);` |
| `ui_run_text_view` | function | `gui/ui_render.c:407` | `ui_status ui_run_text_view(const char *title, const char *text, size_t text_len)` |
| `ui_window` | struct | `gui/ui_render.c:65` | `` |
| `wl_buffer_add_listener` | function | `gui/ui_render.c:146` | `wl_buffer_add_listener(w->buffer, &buffer_listener, w);` |
| `wl_display_disconnect` | function | `gui/ui_render.c:432` | `wl_display_disconnect(w.display);` |
| `wl_display_roundtrip` | function | `gui/ui_render.c:425` | `wl_display_roundtrip(w.display);` |
| `wl_pointer_add_listener` | function | `gui/ui_render.c:371` | `wl_pointer_add_listener(w->pointer, &pointer_listener, w);` |
| `wl_registry_add_listener` | function | `gui/ui_render.c:424` | `wl_registry_add_listener(w.registry, &registry_listener, &w);` |
| `wl_seat_add_listener` | function | `gui/ui_render.c:394` | `wl_seat_add_listener(w->seat, &seat_listener, w);` |
| `wl_shm_pool_destroy` | function | `gui/ui_render.c:143` | `wl_shm_pool_destroy(pool);` |
| `wl_surface_attach` | function | `gui/ui_render.c:251` | `wl_surface_attach(w->surface, w->buffer, 0, 0);` |
| `wl_surface_commit` | function | `gui/ui_render.c:253` | `wl_surface_commit(w->surface);` |
| `wl_surface_damage_buffer` | function | `gui/ui_render.c:252` | `wl_surface_damage_buffer(w->surface, 0, 0, w->width, w->height);` |
| `wm_base_ping` | function | `gui/ui_render.c:257` | `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)` |
| `xdg_surface_ack_configure` | function | `gui/ui_render.c:266` | `xdg_surface_ack_configure(s, serial);` |
| `xdg_surface_add_listener` | function | `gui/ui_render.c:438` | `xdg_surface_add_listener(w.xdg_surface, &xdg_surface_listener, &w);` |
| `xdg_surface_configure` | function | `gui/ui_render.c:263` | `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)` |
| `xdg_toplevel_add_listener` | function | `gui/ui_render.c:440` | `xdg_toplevel_add_listener(w.xdg_toplevel, &toplevel_listener, &w);` |
| `xdg_toplevel_move` | function | `gui/ui_render.c:339` | `xdg_toplevel_move(w->xdg_toplevel, w->seat, serial);` |
| `xdg_toplevel_set_app_id` | function | `gui/ui_render.c:442` | `xdg_toplevel_set_app_id(w.xdg_toplevel, "org.freedom.browser");` |
| `xdg_toplevel_set_maximized` | function | `gui/ui_render.c:334` | `else xdg_toplevel_set_maximized(w->xdg_toplevel);` |
| `xdg_toplevel_set_minimized` | function | `gui/ui_render.c:337` | `xdg_toplevel_set_minimized(w->xdg_toplevel);` |
| `xdg_toplevel_set_title` | function | `gui/ui_render.c:441` | `xdg_toplevel_set_title(w.xdg_toplevel, w.title);` |
| `xdg_wm_base_add_listener` | function | `gui/ui_render.c:391` | `xdg_wm_base_add_listener(w->wm_base, &wm_base_listener, w);` |
| `xdg_wm_base_pong` | function | `gui/ui_render.c:260` | `xdg_wm_base_pong(b, serial);` |
| `zxdg_toplevel_decoration_v1_add_listener` | function | `gui/ui_render.c:449` | `zxdg_toplevel_decoration_v1_add_listener(w.deco, &deco_listener, &w);` |
| `zxdg_toplevel_decoration_v1_set_mode` | function | `gui/ui_render.c:450` | `zxdg_toplevel_decoration_v1_set_mode(w.deco, ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);` |
| `FP_ACCEPT_HEADER_NAV` | macro | `include/anti_fp.h:40` | `#define FP_ACCEPT_HEADER_NAV` |
| `FP_ACCEPT_LANGUAGE` | macro | `include/anti_fp.h:33` | `#define FP_ACCEPT_LANGUAGE` |
| `FP_ACCEPT_LANGUAGE_HEADER` | macro | `include/anti_fp.h:34` | `#define FP_ACCEPT_LANGUAGE_HEADER` |
| `FP_SEC_FETCH_DEST_NAV` | macro | `include/anti_fp.h:45` | `#define FP_SEC_FETCH_DEST_NAV` |
| `FP_SEC_FETCH_MODE_NAV` | macro | `include/anti_fp.h:46` | `#define FP_SEC_FETCH_MODE_NAV` |
| `FP_SEC_FETCH_SITE_NONE` | macro | `include/anti_fp.h:47` | `#define FP_SEC_FETCH_SITE_NONE` |
| `FP_SEC_FETCH_USER_ON` | macro | `include/anti_fp.h:48` | `#define FP_SEC_FETCH_USER_ON` |
| `FP_TIMER_RESOLUTION_MS` | macro | `include/anti_fp.h:21` | `#define FP_TIMER_RESOLUTION_MS` |
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
| `fp_timer_resolution_ms` | function | `include/anti_fp.h:51` | `uint64_t fp_timer_resolution_ms(void);` |
| `fp_timezone` | function | `include/anti_fp.h:60` | `const char *fp_timezone(void);` |
| `fp_user_agent` | function | `include/anti_fp.h:56` | `const char *fp_user_agent(void);` |
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
| `box` | function | `include/box_style.h:114` | `* in_list nonzero when the block sits inside a list item: it then takes * the <li> box (zero margin), keeping items tigh` |
| `bx_background_layer` | function | `include/box_style.h:271` | `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h, double *out_x, double *out_y);` |
| `bx_bg_layer` | struct | `include/box_style.h:262` | `` |
| `bx_border_box_h` | function | `include/box_style.h:205` | `double bx_border_box_h(double declared_h, int border_box, double pad_t, double pad_b, double bord_t, double bord_b);` |
| `bx_box` | struct | `include/box_style.h:50` | `` |
| `bx_content_cap` | function | `include/box_style.h:239` | `double bx_content_cap(double width_cap, int border_box, double pad_l, double pad_r, double bord_l, double bord_r);` |
| `bx_default_for_tag` | function | `include/box_style.h:72` | `bx_box bx_default_for_tag(const char *tag);` |
| `bx_default_for_ua` | function | `include/box_style.h:106` | `bx_box bx_default_for_ua(bx_ua_tag id);` |
| `bx_display` | enum | `include/box_style.h:35` | `` |
| `bx_display_name` | function | `include/box_style.h:156` | `const char *bx_display_name(bx_display d);` |
| `bx_edges` | struct | `include/box_style.h:46` | `` |
| `bx_hplace` | struct | `include/box_style.h:63` | `` |
| `bx_lp_px` | function | `include/box_style.h:231` | `double bx_lp_px(int px_val, int pct_pm, double basis);` |
| `bx_parse_display` | function | `include/box_style.h:152` | `bx_status bx_parse_display(const char *token, bx_display *out);` |
| `bx_place` | function | `include/box_style.h:165` | `bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center, double avail_w);` |
| `bx_replaced_box` | function | `include/box_style.h:191` | `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den, double avail_w, double *out_w, double *out_h);` |
| `bx_status` | enum | `include/box_style.h:56` | `` |
| `bx_table_role` | enum | `include/box_style.h:127` | `` |
| `bx_ua_of_tag` | function | `include/box_style.h:101` | `bx_ua_tag bx_ua_of_tag(const char *tag);` |
| `bx_ua_tag` | enum | `include/box_style.h:84` | `` |
| `bx_width_cap` | function | `include/box_style.h:172` | `double bx_width_cap(int w_px, int w_pct, double avail_w);` |
| `display` | type_alias | `include/box_style.h:49` | `typedef struct bx_box { bx_display display;` |
| `left` | type_alias | `include/box_style.h:46` | `typedef struct bx_edges { double top, right, bottom, left;` |
| `nat_h` | type_alias | `include/box_style.h:262` | `typedef struct bx_bg_layer { double nat_w, nat_h;` |
| `page` | function | `include/box_style.h:209` | `* instead of letting it extend the page (CSS 2.1 section 10.7 + 11.1.1). That * is the case unless BOTH overflow axes ar` |
| `x_off` | type_alias | `include/box_style.h:63` | `typedef struct bx_hplace { double x_off;` |
| `BT_ALIGN_CENTER` | macro | `include/box_tree.h:59` | `#define BT_ALIGN_CENTER` |
| `BT_ALIGN_END` | macro | `include/box_tree.h:60` | `#define BT_ALIGN_END` |
| `BT_ALIGN_START` | macro | `include/box_tree.h:58` | `#define BT_ALIGN_START` |
| `BT_ALIGN_STRETCH` | macro | `include/box_tree.h:61` | `#define BT_ALIGN_STRETCH` |
| `BT_MAX_CHILDREN` | macro | `include/box_tree.h:36` | `#define BT_MAX_CHILDREN` |
| `BT_MAX_DEPTH` | macro | `include/box_tree.h:35` | `#define BT_MAX_DEPTH` |
| `BT_MAX_POSITIONED` | macro | `include/box_tree.h:42` | `#define BT_MAX_POSITIONED` |
| `BT_POS_ABSOLUTE` | macro | `include/box_tree.h:49` | `#define BT_POS_ABSOLUTE` |
| `BT_POS_FIXED` | macro | `include/box_tree.h:50` | `#define BT_POS_FIXED` |
| `BT_POS_RELATIVE` | macro | `include/box_tree.h:48` | `#define BT_POS_RELATIVE` |
| `BT_POS_STATIC` | macro | `include/box_tree.h:47` | `#define BT_POS_STATIC` |
| `BT_POS_STICKY` | macro | `include/box_tree.h:51` | `#define BT_POS_STICKY` |
| `FREEDOM_BOX_TREE_H` | macro | `include/box_tree.h:2` | `#define FREEDOM_BOX_TREE_H` |
| `bottom` | function | `include/box_tree.h:184` | `* bottom with auto top still anchors bottom (R8). * `placed` (may be NULL) marks which boxes have an in-flow rect in box` |
| `box_index` | type_alias | `include/box_tree.h:122` | `typedef struct bt_positioned { size_t box_index;` |
| `bt_box_hidden` | function | `include/box_tree.h:209` | `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid);` |
| `bt_node` | struct | `include/box_tree.h:63` | `` |
| `bt_oof_anchor` | function | `include/box_tree.h:223` | `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid);` |
| `bt_oof_root` | function | `include/box_tree.h:224` | `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid);` |
| `bt_positioned` | struct | `include/box_tree.h:122` | `` |
| `bt_resolve_positioning` | function | `include/box_tree.h:168` | `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox, const double *box_x, const double *box_y, const d` |
| `bt_status` | enum | `include/box_tree.h:129` | `` |
| `closed` | function | `include/box_tree.h:34` | `* fails closed (BT_ERR_RANGE) instead of overflowing the stack. */ #define BT_MAX_DEPTH 64u #define BT_MAX_CHILDREN 128u` |
| `display` | type_alias | `include/box_tree.h:62` | `typedef struct bt_node { bx_display display;` |
| `flow` | function | `include/box_tree.h:177` | `* position is where the box would have started in flow (CSS 2.2 §10.3.7/§10.6.4);` |
| `line` | function | `include/box_tree.h:91` | `* its line (already resolved from align-self / the * container's align-items by the caller). */ /* this node as a grid i` |
| `node` | function | `include/box_tree.h:138` | `* node (x/y parent-relative, w/h border-box). display:none nodes get a zero rect and * take no space. The caller compose` |
| `one` | function | `include/box_tree.h:77` | `* of forcing them all onto one (flex-wrap);` |
| `placed` | function | `include/box_tree.h:191` | `* box counts as placed (legacy behaviour). * bt_resolve_positioning delegates with NULL arrays (legacy behaviour). */ bt` |
| `BROWSER_STATUS_DURATION_MS` | macro | `include/browser.h:25` | `#define BROWSER_STATUS_DURATION_MS` |
| `BROWSER_STATUS_MAX` | macro | `include/browser.h:24` | `#define BROWSER_STATUS_MAX` |
| `BROWSER_URL_MAX` | macro | `include/browser.h:20` | `#define BROWSER_URL_MAX` |
| `FREEDOM_BROWSER_H` | macro | `include/browser.h:2` | `#define FREEDOM_BROWSER_H` |
| `browser_add_exception` | function | `include/browser.h:83` | `browser_status browser_add_exception(browser_state *bs, const char *host);` |
| `browser_back` | function | `include/browser.h:73` | `browser_status browser_back(browser_state *bs);` |
| `browser_can_back` | function | `include/browser.h:77` | `int browser_can_back(const browser_state *bs);` |
| `browser_can_forward` | function | `include/browser.h:78` | `int browser_can_forward(const browser_state *bs);` |
| `browser_commit_url_bar` | function | `include/browser.h:87` | `browser_status browser_commit_url_bar(browser_state *bs);` |
| `browser_current_url` | function | `include/browser.h:79` | `const char *browser_current_url(const browser_state *bs);` |
| `browser_forward` | function | `include/browser.h:74` | `browser_status browser_forward(browser_state *bs);` |
| `browser_free` | function | `include/browser.h:64` | `void browser_free(browser_state *bs);` |
| `browser_is_exception` | function | `include/browser.h:82` | `int browser_is_exception(const browser_state *bs, const char *host);` |
| `browser_set_page` | function | `include/browser.h:69` | `* browser_set_page() with the result. */ browser_status browser_navigate(browser_state *bs, const char *url);` |
| `browser_set_url_bar` | function | `include/browser.h:86` | `browser_status browser_set_url_bar(browser_state *bs, const char *url);` |
| `browser_state` | struct | `include/browser.h:27` | `` |
| `browser_status` | enum | `include/browser.h:50` | `` |
| `browser_status_text` | function | `include/browser.h:133` | `const char *browser_status_text(const browser_state *bs, uint64_t now_ms);` |
| `browser_url_bar_backspace` | function | `include/browser.h:91` | `browser_status browser_url_bar_backspace(browser_state *bs);` |
| `browser_url_bar_clear` | function | `include/browser.h:94` | `browser_status browser_url_bar_clear(browser_state *bs);` |
| `browser_url_bar_delete` | function | `include/browser.h:92` | `browser_status browser_url_bar_delete(browser_state *bs);` |
| `browser_url_bar_delete_selection` | function | `include/browser.h:118` | `int browser_url_bar_delete_selection(browser_state *bs);` |
| `browser_url_bar_extend_cursor` | function | `include/browser.h:103` | `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta);` |
| `browser_url_bar_insert` | function | `include/browser.h:90` | `browser_status browser_url_bar_insert(browser_state *bs, char c);` |
| `browser_url_bar_move_cursor` | function | `include/browser.h:93` | `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta);` |
| `browser_url_bar_select_all` | function | `include/browser.h:110` | `browser_status browser_url_bar_select_all(browser_state *bs);` |
| `browser_url_bar_selection` | function | `include/browser.h:114` | `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len);` |
| `browser_url_bar_set_cursor` | function | `include/browser.h:107` | `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend);` |
| `copied` | function | `include/browser.h:126` | `* copied (truncated to fit) and shown until now_ms reaches the expiry * (now_ms + BROWSER_STATUS_DURATION_MS). A NULL or` |
| `state` | function | `include/browser.h:60` | `* state (frees old history and page buffers). */ browser_status browser_init(browser_state *bs);` |
| `FREEDOM_COMPOSITOR_H` | macro | `include/compositor.h:2` | `#define FREEDOM_COMPOSITOR_H` |
| `cx_box_layer` | function | `include/compositor.h:64` | `cx_layer cx_box_layer(const cx_style *s);` |
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
| `CSS_DROP_PROP_MAX` | macro | `include/css.h:968` | `#define CSS_DROP_PROP_MAX` |
| `CSS_DROP_VAL_MAX` | macro | `include/css.h:970` | `#define CSS_DROP_VAL_MAX` |
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
| `CSS_MAX_KF_STOPS` | macro | `include/css.h:830` | `#define CSS_MAX_KF_STOPS` |
| `CSS_MAX_PSEUDO_SEL` | macro | `include/css.h:552` | `#define CSS_MAX_PSEUDO_SEL` |
| `CSS_MEDIA_DEFAULT_HEIGHT` | macro | `include/css.h:930` | `#define CSS_MEDIA_DEFAULT_HEIGHT` |
| `CSS_MEDIA_DEFAULT_WIDTH` | macro | `include/css.h:924` | `#define CSS_MEDIA_DEFAULT_WIDTH` |
| `CSS_NTH_MAX` | macro | `include/css.h:556` | `#define CSS_NTH_MAX` |
| `CSS_PCT_MAX` | macro | `include/css.h:473` | `#define CSS_PCT_MAX` |
| `CSS_SHADOW_MAX` | macro | `include/css.h:430` | `#define CSS_SHADOW_MAX` |
| `CSS_SPACING_MAX` | macro | `include/css.h:429` | `#define CSS_SPACING_MAX` |
| `CSS_URL_MAX` | macro | `include/css.h:87` | `#define CSS_URL_MAX` |
| `FREEDOM_CSS_H` | macro | `include/css.h:2` | `#define FREEDOM_CSS_H` |
| `POINTER` | function | `include/css.h:207` | `* POINTER (shows the hand cursor already used for links) from every other value * (shows the default arrow);` |
| `color` | type_alias | `include/css.h:563` | `typedef struct css_style { int color;` |
| `css_align` | enum | `include/css.h:34` | `` |
| `css_align_kw` | enum | `include/css.h:166` | `` |
| `css_appearance` | enum | `include/css.h:295` | `` |
| `css_attr` | struct | `include/css.h:1018` | `` |
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
| `css_drop` | struct | `include/css.h:977` | `` |
| `css_drop_cause` | enum | `include/css.h:964` | `` |
| `css_drop_log` | struct | `include/css.h:989` | `` |
| `css_element` | struct | `include/css.h:1028` | `` |
| `css_empty_cells` | enum | `include/css.h:259` | `` |
| `css_flex_direction` | enum | `include/css.h:154` | `` |
| `css_flex_wrap` | enum | `include/css.h:160` | `` |
| `css_float` | enum | `include/css.h:179` | `` |
| `css_font_face_at` | function | `include/css.h:1104` | `int css_font_face_at(const css_sheet *sheet, size_t i, char *family, size_t fam_cap, char *src_url, size_t url_cap);` |
| `css_font_face_count` | function | `include/css.h:1103` | `size_t css_font_face_count(const css_sheet *sheet);` |
| `css_font_family` | enum | `include/css.h:98` | `` |
| `css_font_kerning` | enum | `include/css.h:374` | `` |
| `css_font_stretch` | enum | `include/css.h:383` | `` |
| `css_font_variant` | enum | `include/css.h:277` | `` |
| `css_forced_color_adjust` | enum | `include/css.h:353` | `` |
| `css_free` | function | `include/css.h:1004` | `void css_free(css_sheet *s);` |
| `css_grid_flow` | enum | `include/css.h:173` | `` |
| `css_hyphens` | enum | `include/css.h:283` | `` |
| `css_image_rendering` | enum | `include/css.h:341` | `` |
| `css_isolation` | enum | `include/css.h:328` | `` |
| `css_justify` | enum | `include/css.h:64` | `` |
| `css_list_pos` | enum | `include/css.h:370` | `` |
| `css_list_style` | enum | `include/css.h:121` | `` |
| `css_media` | struct | `include/css.h:919` | `` |
| `css_mix_blend` | enum | `include/css.h:358` | `` |
| `css_object_fit` | enum | `include/css.h:365` | `` |
| `css_overflow` | enum | `include/css.h:202` | `` |
| `css_overscroll` | enum | `include/css.h:401` | `` |
| `css_parse` | function | `include/css.h:937` | `css_status css_parse(const char *text, size_t len, css_sheet **out);` |
| `css_parse_inline` | function | `include/css.h:1097` | `css_style css_parse_inline(const char *style, size_t len);` |
| `css_parse_logged` | function | `include/css.h:999` | `css_status css_parse_logged(const char *text, size_t len, const css_media *media, const char *root_scope, css_sheet **ou` |
| `css_parse_media` | function | `include/css.h:943` | `css_status css_parse_media(const char *text, size_t len, const css_media *media, css_sheet **out);` |
| `css_pct_slot` | enum | `include/css.h:491` | `` |
| `css_pointer_events` | enum | `include/css.h:301` | `` |
| `css_position` | enum | `include/css.h:133` | `` |
| `css_print_color_adjust` | enum | `include/css.h:349` | `` |
| `css_resize` | enum | `include/css.h:389` | `` |
| `css_resolve_anim_keyframes` | function | `include/css.h:1112` | `void css_resolve_anim_keyframes(css_style *s, const css_sheet *sheet);` |
| `css_resolve_el` | function | `include/css.h:1082` | `css_style css_resolve_el(const css_sheet *sheet, const css_element *el, const char *inline_style, size_t inline_len);` |
| `css_scroll_behavior` | enum | `include/css.h:393` | `` |
| `css_sheet` | type_alias | `include/css.h:913` | `typedef struct css_sheet css_sheet;` |
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
| `declared` | function | `include/css.h:795` | `* function was not declared (identity: 0 offset / 100% scale / 0deg). * Percentage translate arguments are not supported` |
| `element` | function | `include/css.h:800` | `* so two different rules matching the same element (e.g. one setting * translate, a more specific one setting rotate) ca` |
| `inherited_px` | function | `include/css.h:1087` | `* whose PARENT computes to inherited_px (<= 0 = unknown -> the CSS initial). * * Exported because the caller that walks ` |
| `order` | function | `include/css.h:1007` | `* cascade order (specificity, then document order), then the element's own * inline_style (which wins). sheet/tag/classe` |
| `palette` | function | `include/css.h:953` | `* so an inactive theme * palette (a dark palette in a light render) can never clobber the active one. * css_parse/css_pa` |
| `prefers_dark` | type_alias | `include/css.h:919` | `typedef struct css_media { int prefers_dark;` |
| `prop` | type_alias | `include/css.h:977` | `typedef struct css_drop { char prop[CSS_DROP_PROP_MAX];` |
| `scaleY` | function | `include/css.h:791` | `* scaleY() as a PERCENT of identity (100 = scale(1), matching font_scale's * convention);` |
| `slots` | function | `include/css.h:807` | `* parse time into ALL seven slots (singular matrices fail closed);` |
| `translate` | function | `include/css.h:790` | `* translate()/translateX()/translateY();` |
| `verbatim` | function | `include/css.h:79` | `* the quoted row strings verbatim (flex_layout parses them);` |
| `CCH_CHAIN_MAX` | macro | `include/css_chain.h:26` | `#define CCH_CHAIN_MAX` |
| `CCH_NTH_MAX` | macro | `include/css_chain.h:28` | `#define CCH_NTH_MAX` |
| `CCH_SIB_MAX` | macro | `include/css_chain.h:27` | `#define CCH_SIB_MAX` |
| `FREEDOM_CSS_CHAIN_H` | macro | `include/css_chain.h:2` | `#define FREEDOM_CSS_CHAIN_H` |
| `cch_element_matches` | function | `include/css_chain.h:56` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel);` |
| `cch_element_style` | function | `include/css_chain.h:36` | `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet);` |
| `cch_element_style_fs` | function | `include/css_chain.h:48` | `css_style cch_element_style_fs(lxb_dom_element_t *el, const css_sheet *sheet, double parent_font_size);` |
| `CC_COLOR_CURRENT` | macro | `include/css_color.h:59` | `#define CC_COLOR_CURRENT` |
| `CC_COLOR_TRANSPARENT` | macro | `include/css_color.h:60` | `#define CC_COLOR_TRANSPARENT` |
| `FREEDOM_CSS_COLOR_H` | macro | `include/css_color.h:2` | `#define FREEDOM_CSS_COLOR_H` |
| `b` | type_alias | `include/css_color.h:26` | `typedef struct cc_rgb { unsigned char r, g, b;` |
| `cc_pack` | function | `include/css_color.h:49` | `int cc_pack(cc_rgb c);` |
| `cc_parse` | function | `include/css_color.h:45` | `cc_status cc_parse(const char *token, cc_rgb *out);` |
| `cc_rgb` | struct | `include/css_color.h:27` | `` |
| `cc_status` | enum | `include/css_color.h:31` | `` |
| `cc_unpack` | function | `include/css_color.h:52` | `cc_rgb cc_unpack(int packed);` |
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
| `cl_resolve` | function | `include/css_length.h:117` | `cl_status cl_resolve(const char *value, const cl_ctx *ctx, double *out_px);` |
| `cl_resolve_lp` | function | `include/css_length.h:194` | `cl_status cl_resolve_lp(const char *value, const cl_ctx *ctx, cl_lp *out);` |
| `cl_status` | enum | `include/css_length.h:61` | `` |
| `cl_unit_font_ratio` | function | `include/css_length.h:182` | `double cl_unit_font_ratio(const char *unit, size_t unit_len);` |
| `cl_unit_is_font_relative` | function | `include/css_length.h:157` | `* cl_unit_is_font_relative() draws. */ /* * Re-fits a resolved length to a different font-size: * * used = px + em * (fo` |
| `cl_unit_scale` | function | `include/css_length.h:241` | `cl_status cl_unit_scale(const char *unit, size_t unit_len, const cl_ctx *ctx, double *out_px_per_unit);` |
| `font_size` | type_alias | `include/css_length.h:84` | `typedef struct cl_ctx { double font_size;` |
| `here` | function | `include/css_length.h:186` | `* Every input cl_resolve accepts resolves identically here (with has_pct 0);` |
| `length` | function | `include/css_length.h:205` | `* * A basis that is not a usable length (negative, zero, non-finite) contributes * nothing, but the absolute component s` |
| `prelude` | function | `include/css_length.h:99` | `* correct context for a media query prelude (whose `em` is defined to use the * initial font size, never the author's ro` |
| `px` | type_alias | `include/css_length.h:132` | `typedef struct cl_lp { double px;` |
| `CSS_MAX_CLASSES_PER_SEL` | macro | `include/css_select.h:28` | `#define CSS_MAX_CLASSES_PER_SEL` |
| `CSS_MAX_SUB_SELS` | macro | `include/css_select.h:80` | `#define CSS_MAX_SUB_SELS` |
| `CSS_SUB_MAX_ATTRS` | macro | `include/css_select.h:81` | `#define CSS_SUB_MAX_ATTRS` |
| `CSS_TOK_MAX` | macro | `include/css_select.h:27` | `#define CSS_TOK_MAX` |
| `FREEDOM_CSS_SELECT_H` | macro | `include/css_select.h:2` | `#define FREEDOM_CSS_SELECT_H` |
| `csel_ci_eq` | function | `include/css_select.h:162` | `static inline int csel_ci_eq(const char *a, const char *b)` |
| `csel_ident_ch` | function | `include/css_select.h:190` | `static inline int csel_ident_ch(char c)` |
| `csel_lower_ch` | function | `include/css_select.h:158` | `static inline char csel_lower_ch(char c)` |
| `csel_matches` | function | `include/css_select.h:154` | `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id, int allow_pseudo_el, int *pseudo_kind` |
| `csel_parse` | function | `include/css_select.h:145` | `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel);` |
| `csel_span_eq` | function | `include/css_select.h:172` | `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)` |
| `csel_substr` | function | `include/css_select.h:183` | `static inline int csel_substr(const char *hay, const char *needle, int ci)` |
| `css_attr_match` | struct | `include/css_select.h:84` | `` |
| `css_compound` | struct | `include/css_select.h:115` | `` |
| `css_pseudo_match` | struct | `include/css_select.h:105` | `` |
| `css_sel` | struct | `include/css_select.h:132` | `` |
| `css_sub_sel` | struct | `include/css_select.h:91` | `` |
| `kind` | type_alias | `include/css_select.h:105` | `typedef struct css_pseudo_match { int kind;` |
| `name` | type_alias | `include/css_select.h:84` | `typedef struct css_attr_match { char name[CSS_TOK_MAX];` |
| `parts` | type_alias | `include/css_select.h:132` | `typedef struct css_sel { css_compound parts[CSS_MAX_COMPOUNDS];` |
| `tag` | type_alias | `include/css_select.h:90` | `typedef struct css_sub_sel { char tag[CSS_TOK_MAX];` |
| `tag` | type_alias | `include/css_select.h:115` | `typedef struct css_compound { char tag[CSS_TOK_MAX];` |
| `DU_MAX_ENCODED_LEN` | macro | `include/data_url.h:43` | `#define DU_MAX_ENCODED_LEN` |
| `FREEDOM_DATA_URL_H` | macro | `include/data_url.h:2` | `#define FREEDOM_DATA_URL_H` |
| `allocation` | function | `include/data_url.h:20` | `* * du_base64_payload does no allocation (it only slices the caller's url string);` |
| `closed` | function | `include/data_url.h:59` | `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/out/out_len == NULL (with b64_len != 0) =>` |
| `du_base64_payload` | function | `include/data_url.h:54` | `du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len);` |
| `du_is_data_url` | function | `include/data_url.h:46` | `int du_is_data_url(const char *url);` |
| `du_status` | enum | `include/data_url.h:27` | `` |
| `FREEDOM_DISK_STORE_H` | macro | `include/disk_store.h:2` | `#define FREEDOM_DISK_STORE_H` |
| `ds_free` | function | `include/disk_store.h:47` | `void ds_free(uint8_t *buf, size_t len);` |
| `ds_read` | function | `include/disk_store.h:43` | `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN], uint8_t **out, size_t *out_len);` |
| `ds_status` | enum | `include/disk_store.h:25` | `` |
| `ds_write` | function | `include/disk_store.h:38` | `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead, const uint8_t *plaintext, size_t pt_le` |
| `DOM_NODE_NONE` | macro | `include/dom.h:37` | `#define DOM_NODE_NONE` |
| `FREEDOM_DOM_H` | macro | `include/dom.h:2` | `#define FREEDOM_DOM_H` |
| `count` | function | `include/dom.h:59` | `* match count (which may exceed cap, so the caller can size a buffer). */ size_t dom_get_by_tag(const dom_index *idx, co` |
| `cycle` | function | `include/dom.h:164` | `* Rejects a cycle (child being an ancestor of parent). Invalid handle / self / cycle * => DOM_ERR_NULL_ARG. */ dom_statu` |
| `dom_attribute_names` | function | `include/dom.h:128` | `size_t dom_attribute_names(const dom_index *idx, dom_node_id node, const char **names, size_t *lens, size_t cap);` |
| `dom_build` | function | `include/dom.h:45` | `dom_status dom_build(const hp_document *doc, dom_index **out);` |
| `dom_closest` | function | `include/dom.h:95` | `dom_node_id dom_closest(const dom_index *idx, dom_node_id node, const char *selector);` |
| `dom_create_element` | function | `include/dom.h:161` | `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id);` |
| `dom_document_position` | function | `include/dom.h:101` | `size_t dom_document_position(const dom_index *idx, dom_node_id node);` |
| `dom_document_title` | function | `include/dom.h:136` | `const char *dom_document_title(const dom_index *idx, size_t *len);` |
| `dom_first_child` | function | `include/dom.h:112` | `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node);` |
| `dom_free` | function | `include/dom.h:48` | `void dom_free(dom_index *idx);` |
| `dom_get_attribute` | function | `include/dom.h:121` | `const char *dom_get_attribute(const dom_index *idx, dom_node_id node, const char *name, size_t *len);` |
| `dom_get_by_class` | function | `include/dom.h:62` | `size_t dom_get_by_class(const dom_index *idx, const char *cls, dom_node_id *out, size_t cap);` |
| `dom_get_element_by_id` | function | `include/dom.h:56` | `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id);` |
| `dom_index` | type_alias | `include/dom.h:40` | `typedef struct dom_index dom_index;` |
| `dom_matches` | function | `include/dom.h:91` | `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector);` |
| `dom_next_sibling` | function | `include/dom.h:113` | `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node);` |
| `dom_node_at` | function | `include/dom.h:107` | `dom_node_id dom_node_at(const dom_index *idx, size_t position);` |
| `dom_node_count` | function | `include/dom.h:51` | `size_t dom_node_count(const dom_index *idx);` |
| `dom_node_id` | type_alias | `include/dom.h:34` | `typedef uint32_t dom_node_id;` |
| `dom_parent` | function | `include/dom.h:110` | `dom_node_id dom_parent(const dom_index *idx, dom_node_id node);` |
| `dom_precedes` | function | `include/dom.h:104` | `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);` |
| `dom_query_selector` | function | `include/dom.h:82` | `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root, const char *selector);` |
| `dom_remove_attribute` | function | `include/dom.h:182` | `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name);` |
| `dom_set_attribute` | function | `include/dom.h:175` | `dom_status dom_set_attribute(dom_index *idx, dom_node_id node, const char *name, const char *value);` |
| `dom_set_document_title` | function | `include/dom.h:151` | `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len);` |
| `dom_set_inner_html` | function | `include/dom.h:189` | `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node, const char *html, size_t len);` |
| `dom_set_text_content` | function | `include/dom.h:146` | `dom_status dom_set_text_content(dom_index *idx, dom_node_id node, const char *text, size_t len);` |
| `dom_status` | enum | `include/dom.h:26` | `` |
| `dom_tag_name` | function | `include/dom.h:118` | `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);` |
| `dom_text_content` | function | `include/dom.h:133` | `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len);` |
| `index` | function | `include/dom.h:169` | `* stays valid in the index (not freed). Invalid handle / not-a-child => DOM_ERR_NULL_ARG. */ dom_status dom_remove_child` |
| `length` | function | `include/dom.h:194` | `* length (no children => an owned empty string). Uses a chain of fixed-size * blocks internally so there is no hard cap ` |
| `DD_FIELD_MAX` | macro | `include/dom_debug.h:28` | `#define DD_FIELD_MAX` |
| `FREEDOM_DOM_DEBUG_H` | macro | `include/dom_debug.h:2` | `#define FREEDOM_DOM_DEBUG_H` |
| `dd_format` | function | `include/dom_debug.h:36` | `size_t dd_format(const rd_doc *doc, char *out, size_t cap);` |
| `dd_format_css` | function | `include/dom_debug.h:41` | `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap);` |
| `DL_ERR_OVERFLOW` | function | `include/download.h:56` | `* DL_ERR_OVERFLOW (out left empty). url/content_disposition NULL => absent. */ dl_status dl_pick_name(const char *url, c` |
| `DL_FALLBACK_NAME` | macro | `include/download.h:30` | `#define DL_FALLBACK_NAME` |
| `DL_MAX_BYTES` | macro | `include/download.h:31` | `#define DL_MAX_BYTES` |
| `DL_NAME_MAX` | macro | `include/download.h:28` | `#define DL_NAME_MAX` |
| `FREEDOM_DOWNLOAD_H` | macro | `include/download.h:2` | `#define FREEDOM_DOWNLOAD_H` |
| `basename` | function | `include/download.h:61` | `* sanitized basename (a name still containing '/' is rejected => DL_ERR_OVERFLOW, * so the path can never escape dir). T` |
| `dl_check_size` | function | `include/download.h:67` | `dl_status dl_check_size(size_t len);` |
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
| `FX_MAX_COLUMNS` | macro | `include/flex_layout.h:231` | `#define FX_MAX_COLUMNS` |
| `FX_MAX_ITEMS` | macro | `include/flex_layout.h:28` | `#define FX_MAX_ITEMS` |
| `basis` | type_alias | `include/flex_layout.h:40` | `typedef struct fx_item { double basis;` |
| `bottom` | type_alias | `include/flex_layout.h:186` | `typedef struct fx_float_rect { double top, bottom;` |
| `cols` | type_alias | `include/flex_layout.h:116` | `typedef struct fx_area_map { int rows, cols;` |
| `fx_area_map` | struct | `include/flex_layout.h:116` | `` |
| `fx_auto_min_size` | function | `include/flex_layout.h:226` | `double fx_auto_min_size(double min_content, double basis, double author_min, int scroll_container);` |
| `fx_float_insets` | function | `include/flex_layout.h:202` | `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h, double avail, double *out_l, double *out` |
| `fx_float_pack_wrap` | function | `include/flex_layout.h:158` | `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n, double avail, double gap, double *out_x, si` |
| `fx_float_rect` | struct | `include/flex_layout.h:186` | `` |
| `fx_grid_area_hash` | function | `include/flex_layout.h:125` | `unsigned fx_grid_area_hash(const char *name);` |
| `fx_grid_area_rect` | function | `include/flex_layout.h:136` | `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name, int *row, int *col, int *row_span, int *col_span);` |
| `fx_grid_areas_parse` | function | `include/flex_layout.h:130` | `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out);` |
| `fx_grid_cell` | function | `include/flex_layout.h:74` | `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col);` |
| `fx_grid_columns` | function | `include/flex_layout.h:69` | `fx_status fx_grid_columns(double avail, size_t ncols, double gap, double *col_x, double *col_w);` |
| `fx_grid_columns_weighted` | function | `include/flex_layout.h:82` | `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap, const int *track, size_t ntrack, double *col_` |
| `fx_grid_place_span` | function | `include/flex_layout.h:98` | `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span, const int *row_span, const int *fixed_row, co` |
| `fx_item` | struct | `include/flex_layout.h:40` | `` |
| `fx_justify` | enum | `include/flex_layout.h:30` | `` |
| `fx_justify_name` | function | `include/flex_layout.h:282` | `const char *fx_justify_name(fx_justify j);` |
| `fx_multicol_balance` | function | `include/flex_layout.h:277` | `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol, int *out_col, double *out_colh);` |
| `fx_multicol_used` | function | `include/flex_layout.h:258` | `fx_status fx_multicol_used(double avail_w, int column_count, double column_width, double gap, int *out_n, double *out_w)` |
| `fx_result` | struct | `include/flex_layout.h:48` | `` |
| `fx_status` | enum | `include/flex_layout.h:53` | `` |
| `offset` | function | `include/flex_layout.h:143` | `* offset (from the content start, clamped to >= 0) to out_x[n]. The band does NOT wrap * (v1): an item that would overfl` |
| `out` | function | `include/flex_layout.h:62` | `* fx_result to out (caller-owned). n == 0 is a no-op (out may be NULL). */ fx_status fx_flex_line(const fx_item *items, ` |
| `pos` | type_alias | `include/flex_layout.h:48` | `typedef struct fx_result { double pos;` |
| `required` | function | `include/flex_layout.h:156` | `* out_row is required (NULL with n > 0 yields FX_ERR_NULL_ARG);` |
| `size` | function | `include/flex_layout.h:60` | `* content size (px);` |
| `widths` | function | `include/flex_layout.h:166` | `* the OUTER widths (width + ml + mr, clamped >= 0, so a negative margin narrows * the slot and a positive one widens it)` |
| `FM_BODY_MAX` | macro | `include/form.h:30` | `#define FM_BODY_MAX` |
| `FM_CONTENT_TYPE_URLENCODED` | variable | `include/form.h:68` | `extern const char FM_CONTENT_TYPE_URLENCODED[];` |
| `FM_MAX_FIELDS` | macro | `include/form.h:31` | `#define FM_MAX_FIELDS` |
| `FM_URL_MAX` | macro | `include/form.h:28` | `#define FM_URL_MAX` |
| `FREEDOM_FORM_H` | macro | `include/form.h:2` | `#define FREEDOM_FORM_H` |
| `fm_block_reason` | enum | `include/form.h:45` | `` |
| `fm_build` | function | `include/form.h:81` | `fm_status fm_build(const char *base, const char *action, fm_method method, const fm_field *fields, size_t n, fm_plan *ou` |
| `fm_encode` | function | `include/form.h:74` | `fm_status fm_encode(const fm_field *fields, size_t n, char *out, size_t outsz, size_t *out_len);` |
| `fm_field` | struct | `include/form.h:37` | `` |
| `fm_kind` | enum | `include/form.h:39` | `` |
| `fm_method` | enum | `include/form.h:33` | `` |
| `fm_plan` | struct | `include/form.h:52` | `` |
| `fm_status` | enum | `include/form.h:61` | `` |
| `kind` | type_alias | `include/form.h:51` | `typedef struct fm_plan { fm_kind kind;` |
| `FREEDOM_FRAME_CLOCK_H` | macro | `include/frame_clock.h:2` | `#define FREEDOM_FRAME_CLOCK_H` |
| `active` | type_alias | `include/frame_clock.h:14` | `typedef struct fc_clock { int active;` |
| `fc_clock` | struct | `include/frame_clock.h:15` | `` |
| `fc_init` | function | `include/frame_clock.h:19` | `void fc_init(fc_clock *c);` |
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
| `FC_FLEX_MEASURE_W` | macro | `include/freedom_config.h:35` | `#define FC_FLEX_MEASURE_W` |
| `FC_FLEX_MIN_MEASURE_W` | macro | `include/freedom_config.h:41` | `#define FC_FLEX_MIN_MEASURE_W` |
| `FC_FONT_CHAIN_MAX` | macro | `include/freedom_config.h:46` | `#define FC_FONT_CHAIN_MAX` |
| `FC_MAX_BOXES` | macro | `include/freedom_config.h:51` | `#define FC_MAX_BOXES` |
| `FC_PNG_MARGIN` | macro | `include/freedom_config.h:24` | `#define FC_PNG_MARGIN` |
| `FC_PNG_MAX_H` | macro | `include/freedom_config.h:29` | `#define FC_PNG_MAX_H` |
| `FC_PNG_PAGE_W` | macro | `include/freedom_config.h:20` | `#define FC_PNG_PAGE_W` |
| `FREEDOM_CONFIG_H` | macro | `include/freedom_config.h:14` | `#define FREEDOM_CONFIG_H` |
| `FREEDOM_HLS_H` | macro | `include/hls.h:2` | `#define FREEDOM_HLS_H` |
| `hls_parse` | function | `include/hls.h:59` | `hls_status hls_parse(const char *playlist_text, size_t len, hls_playlist **out);` |
| `hls_playlist` | struct | `include/hls.h:45` | `` |
| `hls_playlist_free` | function | `include/hls.h:74` | `void hls_playlist_free(hls_playlist *pl);` |
| `hls_segment` | struct | `include/hls.h:29` | `` |
| `hls_select_variant` | function | `include/hls.h:65` | `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h);` |
| `hls_status` | enum | `include/hls.h:21` | `` |
| `hls_variant` | struct | `include/hls.h:36` | `` |
| `resolved` | function | `include/hls.h:68` | `* Writes the absolute URL into resolved (bounded by resolved_sz). Returns the * written length, or 0 on failure. */ size` |
| `FREEDOM_HOSTBLOCK_H` | macro | `include/hostblock.h:2` | `#define FREEDOM_HOSTBLOCK_H` |
| `hb_check` | function | `include/hostblock.h:68` | `hb_decision hb_check(const hb_set *s, const char *host);` |
| `hb_count` | function | `include/hostblock.h:79` | `size_t hb_count(const hb_set *s, hb_list list);` |
| `hb_decision` | enum | `include/hostblock.h:37` | `` |
| `hb_free` | function | `include/hostblock.h:52` | `void hb_free(hb_set *s);` |
| `hb_is_allowlisted` | function | `include/hostblock.h:75` | `int hb_is_allowlisted(const hb_set *s, const char *host);` |
| `hb_list` | enum | `include/hostblock.h:32` | `` |
| `hb_load` | function | `include/hostblock.h:60` | `hb_status hb_load(hb_set *s, const char *text, hb_list list);` |
| `hb_new` | function | `include/hostblock.h:49` | `hb_set *hb_new(void);` |
| `hb_set` | type_alias | `include/hostblock.h:29` | `typedef struct hb_set hb_set;` |
| `hb_status` | enum | `include/hostblock.h:42` | `` |
| `walked` | function | `include/hostblock.h:65` | `* walked (the host, then without its first label, ...): any suffix on the allowlist * => HB_ALLOW (allow wins, covers su` |
| `FREEDOM_HOSTEDIT_H` | macro | `include/hostedit.h:2` | `#define FREEDOM_HOSTEDIT_H` |
| `HE_MAX_HOST` | macro | `include/hostedit.h:32` | `#define HE_MAX_HOST` |
| `he_make_line` | function | `include/hostedit.h:40` | `he_status he_make_line(const char *host, char *out, size_t cap);` |
| `he_status` | enum | `include/hostedit.h:24` | `` |
| `he_suggest` | function | `include/hostedit.h:55` | `int he_suggest(const char *text, const char *query, char results[][HE_MAX_HOST + 1], int max);` |
| `he_text_has_host` | function | `include/hostedit.h:46` | `int he_text_has_host(const char *text, const char *host);` |
| `FREEDOM_HTML_PARSE_H` | macro | `include/html_parse.h:2` | `#define FREEDOM_HTML_PARSE_H` |
| `HP_DEFAULT_MAX_BYTES` | macro | `include/html_parse.h:40` | `#define HP_DEFAULT_MAX_BYTES` |
| `HP_MAX_SCRIPTS` | macro | `include/html_parse.h:48` | `#define HP_MAX_SCRIPTS` |
| `HP_MAX_STYLESHEETS` | macro | `include/html_parse.h:112` | `#define HP_MAX_STYLESHEETS` |
| `cfg` | function | `include/html_parse.h:57` | `* policy in cfg (cfg == NULL => secure defaults). No script is ever executed. * html == NULL or out == NULL => HP_ERR_NU` |
| `dropped` | function | `include/html_parse.h:47` | `* dropped (not executed). */ #define HP_MAX_SCRIPTS ((size_t)4096) /* Returns a configuration with the secure defaults a` |
| `hp_config` | struct | `include/html_parse.h:32` | `` |
| `hp_document` | type_alias | `include/html_parse.h:39` | `typedef struct hp_document hp_document;` |
| `hp_document_free` | function | `include/html_parse.h:133` | `void hp_document_free(hp_document *doc);` |
| `hp_document_root` | function | `include/html_parse.h:139` | `const void *hp_document_root(const hp_document *doc);` |
| `hp_element_count` | function | `include/html_parse.h:63` | `size_t hp_element_count(const hp_document *doc);` |
| `hp_event_handler_count` | function | `include/html_parse.h:65` | `size_t hp_event_handler_count(const hp_document *doc);` |
| `hp_extract_stylesheet_hrefs` | function | `include/html_parse.h:124` | `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count);` |
| `hp_extract_text` | function | `include/html_parse.h:69` | `char *hp_extract_text(const hp_document *doc, size_t *out_len);` |
| `hp_free` | function | `include/html_parse.h:130` | `void hp_free(char *buf);` |
| `hp_free_scripts` | function | `include/html_parse.h:108` | `void hp_free_scripts(hp_script *scripts, size_t count);` |
| `hp_free_stylesheet_hrefs` | function | `include/html_parse.h:127` | `void hp_free_stylesheet_hrefs(char **hrefs, size_t count);` |
| `hp_get_title` | function | `include/html_parse.h:70` | `char *hp_get_title(const hp_document *doc, size_t *out_len);` |
| `hp_script` | struct | `include/html_parse.h:76` | `` |
| `hp_script_count` | function | `include/html_parse.h:64` | `size_t hp_script_count(const hp_document *doc);` |
| `hp_status` | enum | `include/html_parse.h:22` | `` |
| `hp_validate_input` | function | `include/html_parse.h:54` | `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg);` |
| `max_bytes` | type_alias | `include/html_parse.h:31` | `typedef struct hp_config { size_t max_bytes;` |
| `modules` | function | `include/html_parse.h:91` | `* ES modules (import/export cannot run as a classic script), and template blocks * (text/x-jquery-tmpl, text/html, text/` |
| `src` | function | `include/html_parse.h:87` | `* carry their raw src (a <script src> with an inline body lists ONLY the src -- * browser rule: when src is present the ` |
| `FREEDOM_IMAGE_DECODE_H` | macro | `include/image_decode.h:2` | `#define FREEDOM_IMAGE_DECODE_H` |
| `IMG_MAX_DIM` | macro | `include/image_decode.h:65` | `#define IMG_MAX_DIM` |
| `IMG_MAX_PIXELS` | macro | `include/image_decode.h:66` | `#define IMG_MAX_PIXELS` |
| `decode` | function | `include/image_decode.h:92` | `* the declared dimensions BEFORE the full decode (anti-bomb), decodes to RGB and * expands to BGRA. Rejects non-JPEG (IM` |
| `guards` | function | `include/image_decode.h:25` | `* guards (in-memory source only, longjmp error manager so a bad stream never * calls exit(), dimension caps before decod` |
| `img_decode` | function | `include/image_decode.h:117` | `img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out);` |
| `img_decode_gif` | function | `include/image_decode.h:104` | `img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out);` |
| `img_decode_png` | function | `include/image_decode.h:89` | `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out);` |
| `img_dimensions_ok` | function | `include/image_decode.h:78` | `int img_dimensions_ok(uint32_t w, uint32_t h);` |
| `img_format` | enum | `include/image_decode.h:33` | `` |
| `img_format_name` | function | `include/image_decode.h:124` | `const char *img_format_name(img_format f);` |
| `img_pixels` | struct | `include/image_decode.h:56` | `` |
| `img_pixels_free` | function | `include/image_decode.h:121` | `void img_pixels_free(img_pixels *p);` |
| `img_png_dimensions` | function | `include/image_decode.h:73` | `img_status img_png_dimensions(const uint8_t *bytes, size_t len, uint32_t *out_w, uint32_t *out_h);` |
| `img_sniff` | function | `include/image_decode.h:69` | `img_format img_sniff(const uint8_t *bytes, size_t len);` |
| `img_status` | enum | `include/image_decode.h:41` | `` |
| `inputs` | function | `include/image_decode.h:81` | `* Degenerate inputs (<= 0) yield (0,0). Pure. */ void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h, doub` |
| `width` | type_alias | `include/image_decode.h:56` | `typedef struct img_pixels { uint32_t width;` |
| `FREEDOM_INTERP_H` | macro | `include/interp.h:2` | `#define FREEDOM_INTERP_H` |
| `IP_ITERATION_INFINITE` | macro | `include/interp.h:84` | `#define IP_ITERATION_INFINITE` |
| `IP_MAX_KEYFRAMES` | macro | `include/interp.h:67` | `#define IP_MAX_KEYFRAMES` |
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
| `ip_lerp` | function | `include/interp.h:59` | `double ip_lerp(double a, double b, double t);` |
| `ip_lerp_color` | function | `include/interp.h:61` | `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t);` |
| `ip_val_kind` | enum | `include/interp.h:54` | `` |
| `kind` | type_alias | `include/interp.h:37` | `typedef struct ip_ease_fn { ip_easing kind;` |
| `pct` | type_alias | `include/interp.h:69` | `typedef struct ip_keyframe { double pct;` |
| `val_kind` | type_alias | `include/interp.h:100` | `typedef struct ip_anim { ip_val_kind val_kind;` |
| `FREEDOM_JS_DOM_H` | macro | `include/js_dom.h:2` | `#define FREEDOM_JS_DOM_H` |
| `JD_IFRAME_TRACK_MAX` | macro | `include/js_dom.h:39` | `#define JD_IFRAME_TRACK_MAX` |
| `URLs` | function | `include/js_dom.h:172` | `* video URLs (.m3u8 then .mp4 patterns), and creates <video> elements in the document for * any found. Does NOT re-proce` |
| `acting` | function | `include/js_dom.h:136` | `* The caller MUST gate the raw target with ln_resolve before acting (Zero Trust). */ int jd_take_nav_request(js_context ` |
| `host` | function | `include/js_dom.h:120` | `* for a trusted host (allow.conf AND js.conf);` |
| `jd_click_state` | type_alias | `include/js_dom.h:34` | `typedef struct jd_click_state jd_click_state;` |
| `jd_click_state_free` | function | `include/js_dom.h:68` | `* jd_click_state_free(). Bound to one context via jd_install_events(). */ jd_click_state *jd_click_state_new(void);` |
| `jd_get_cookies` | function | `include/js_dom.h:131` | `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz);` |
| `jd_iframe_track` | struct | `include/js_dom.h:40` | `` |
| `jd_install` | function | `include/js_dom.h:57` | `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque);` |
| `jd_install_console` | function | `include/js_dom.h:65` | `jd_status jd_install_console(js_context *ctx, fb_buffer *log);` |
| `jd_install_events` | function | `include/js_dom.h:74` | `jd_status jd_install_events(js_context *ctx, jd_click_state *state);` |
| `jd_install_xhr` | function | `include/js_dom.h:160` | `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx);` |
| `jd_opaque` | struct | `include/js_dom.h:45` | `` |
| `jd_process_iframes` | function | `include/js_dom.h:165` | `* BEFORE jd_process_iframes() (so iframes are in the DOM for it to process). * ctx == NULL => JD_ERR_NULL_ARG. */ jd_sta` |
| `jd_set_cookies` | function | `include/js_dom.h:125` | `jd_status jd_set_cookies(js_context *ctx, const char *cookies);` |
| `jd_status` | enum | `include/js_dom.h:24` | `` |
| `jd_video_from_scripts` | function | `include/js_dom.h:186` | `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts, const size_t *script_lens, size_t nscripts` |
| `opaque` | function | `include/js_dom.h:62` | `* the engine runtime opaque (unreachable from script);` |
| `out_status` | function | `include/js_dom.h:144` | `* On success returns 0 and sets *out_status (HTTP status, 0 if unknown), *out_body / * *out_body_len (response bytes, ma` |
| `preventDefault` | function | `include/js_dom.h:84` | `* preventDefault() was called, 1 if the default (form submission) should proceed. * ctx == NULL or no form found => 1 (f` |
| `processed` | type_alias | `include/js_dom.h:40` | `typedef struct jd_iframe_track { dom_node_id processed[JD_IFRAME_TRACK_MAX];` |
| `reads` | function | `include/js_dom.h:115` | `* reads (NULL => only href is known, the rest fall back to stub defaults). Call after * jd_install, on the page's contex` |
| `run` | function | `include/js_dom.h:77` | `* run (no handler registered, or handlers ran without calling preventDefault()), * and 0 if a handler called preventDefa` |
| `FREEDOM_JS_ENV_H` | macro | `include/js_env.h:2` | `#define FREEDOM_JS_ENV_H` |
| `je_install` | function | `include/js_env.h:38` | `je_status je_install(js_context *ctx, int screen_w, int screen_h);` |
| `je_status` | enum | `include/js_env.h:27` | `` |
| `poisoned` | function | `include/js_env.h:43` | `* readback is poisoned (deterministic within an origin, unlinkable across * sessions and across origins) to defeat readb` |
| `FREEDOM_JS_POLICY_H` | macro | `include/js_policy.h:2` | `#define FREEDOM_JS_POLICY_H` |
| `allowlist` | function | `include/js_policy.h:34` | `* allowlist (e.g. hb_is_allowlisted over js.conf). Fails closed: an unknown mode * yields false. */ bool jsp_enabled(jsp` |
| `jsp_mode` | enum | `include/js_policy.h:27` | `` |
| `jsp_mode_from_str` | function | `include/js_policy.h:60` | `jsp_mode jsp_mode_from_str(const char *s);` |
| `jsp_mode_str` | function | `include/js_policy.h:64` | `const char *jsp_mode_str(jsp_mode mode);` |
| `jsp_present_trusted` | function | `include/js_policy.h:54` | `bool jsp_present_trusted(int host_allowlisted);` |
| `jsp_trusted` | function | `include/js_policy.h:45` | `bool jsp_trusted(bool js_enabled, int host_allowlisted);` |
| `membership` | function | `include/js_policy.h:16` | `* membership (the allowlist itself is matched by the hostblock module, which * already covers subdomains). No I/O, no gl` |
| `FREEDOM_JS_SANDBOX_H` | macro | `include/js_sandbox.h:2` | `#define FREEDOM_JS_SANDBOX_H` |
| `JS_DEFAULT_MAX_SOURCE` | macro | `include/js_sandbox.h:65` | `#define JS_DEFAULT_MAX_SOURCE` |
| `JS_DEFAULT_MEM_LIMIT` | macro | `include/js_sandbox.h:67` | `#define JS_DEFAULT_MEM_LIMIT` |
| `JS_DEFAULT_STACK_LIMIT` | macro | `include/js_sandbox.h:68` | `#define JS_DEFAULT_STACK_LIMIT` |
| `JS_DEFAULT_TIME_BUDGET` | macro | `include/js_sandbox.h:69` | `#define JS_DEFAULT_TIME_BUDGET` |
| `JS_LOC_FILE_MAX` | macro | `include/js_sandbox.h:64` | `#define JS_LOC_FILE_MAX` |
| `handle` | function | `include/js_sandbox.h:137` | `* as an opaque handle (so this header stays free of backend types), or NULL. * Valid only while ctx is alive. Binding mo` |
| `js_context` | type_alias | `include/js_sandbox.h:47` | `typedef struct js_context js_context;` |
| `js_context_free` | function | `include/js_sandbox.h:86` | `void js_context_free(js_context *ctx);` |
| `js_context_new` | function | `include/js_sandbox.h:83` | `js_status js_context_new(const js_limits *lim, js_context **out);` |
| `js_eval` | function | `include/js_sandbox.h:94` | `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res);` |
| `js_eval_named` | function | `include/js_sandbox.h:100` | `js_status js_eval_named(js_context *ctx, const char *src, size_t len, const char *filename, js_result *res);` |
| `js_eval_once` | function | `include/js_sandbox.h:105` | `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res);` |
| `js_limits` | struct | `include/js_sandbox.h:39` | `` |
| `js_limits_default` | function | `include/js_sandbox.h:72` | `js_limits js_limits_default(void);` |
| `js_loc_from_stack` | function | `include/js_sandbox.h:115` | `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap, int *line, int *col);` |
| `js_pump_jobs` | function | `include/js_sandbox.h:134` | `int js_pump_jobs(js_context *ctx, int max_jobs);` |
| `js_result` | struct | `include/js_sandbox.h:49` | `` |
| `js_result_free` | function | `include/js_sandbox.h:126` | `void js_result_free(js_result *res);` |
| `js_set_current_script` | function | `include/js_sandbox.h:146` | `void js_set_current_script(js_context *ctx, const char *src, const char *type);` |
| `js_set_time_budget` | function | `include/js_sandbox.h:123` | `void js_set_time_budget(js_context *ctx, uint64_t budget_ms);` |
| `js_status` | enum | `include/js_sandbox.h:24` | `` |
| `js_validate_source` | function | `include/js_sandbox.h:75` | `js_status js_validate_source(const char *src, size_t len, const js_limits *lim);` |
| `max_source_bytes` | type_alias | `include/js_sandbox.h:39` | `typedef struct js_limits { size_t max_source_bytes;` |
| `status` | type_alias | `include/js_sandbox.h:48` | `typedef struct js_result { js_status status;` |
| `FREEDOM_LINK_NAV_H` | macro | `include/link_nav.h:2` | `#define FREEDOM_LINK_NAV_H` |
| `LN_MAX_FRAGMENT` | macro | `include/link_nav.h:38` | `#define LN_MAX_FRAGMENT` |
| `LN_MAX_TARGET` | macro | `include/link_nav.h:33` | `#define LN_MAX_TARGET` |
| `action` | type_alias | `include/link_nav.h:61` | `typedef struct ln_result { ln_action action;` |
| `dropped` | function | `include/link_nav.h:36` | `* A longer fragment is dropped (stored as "");` |
| `ln_action` | enum | `include/link_nav.h:40` | `` |
| `ln_block_reason` | enum | `include/link_nav.h:54` | `` |
| `ln_block_reason_text` | function | `include/link_nav.h:85` | `const char *ln_block_reason_text(ln_block_reason reason);` |
| `ln_resolve` | function | `include/link_nav.h:81` | `ln_status ln_resolve(const char *base, const char *href, ln_result *out);` |
| `ln_result` | struct | `include/link_nav.h:62` | `` |
| `ln_status` | enum | `include/link_nav.h:70` | `` |
| `ln_target_kind` | enum | `include/link_nav.h:46` | `` |
| `FREEDOM_LOCAL_STORE_H` | macro | `include/local_store.h:2` | `#define FREEDOM_LOCAL_STORE_H` |
| `LS_HEADER_LEN` | macro | `include/local_store.h:30` | `#define LS_HEADER_LEN` |
| `LS_KEY_LEN` | macro | `include/local_store.h:25` | `#define LS_KEY_LEN` |
| `LS_MAX_PLAINTEXT` | macro | `include/local_store.h:32` | `#define LS_MAX_PLAINTEXT` |
| `LS_NONCE_LEN` | macro | `include/local_store.h:28` | `#define LS_NONCE_LEN` |
| `LS_OVERHEAD` | macro | `include/local_store.h:31` | `#define LS_OVERHEAD` |
| `LS_SALT_LEN` | macro | `include/local_store.h:27` | `#define LS_SALT_LEN` |
| `LS_TAG_LEN` | macro | `include/local_store.h:29` | `#define LS_TAG_LEN` |
| `ls_aead` | enum | `include/local_store.h:34` | `` |
| `ls_derive_key` | function | `include/local_store.h:52` | `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len, const uint8_t *salt, size_t salt_len, uint8_t out_ke` |
| `ls_free` | function | `include/local_store.h:80` | `void ls_free(uint8_t *buf, size_t len);` |
| `ls_open` | function | `include/local_store.h:64` | `ls_status ls_open(const uint8_t key[LS_KEY_LEN], const uint8_t *blob, size_t blob_len, uint8_t **out, size_t *out_len);` |
| `ls_open_passphrase` | function | `include/local_store.h:75` | `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len, const uint8_t *blob, size_t blob_len, uint8_t *` |
| `ls_seal` | function | `include/local_store.h:58` | `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead, const uint8_t *plaintext, size_t pt_len, uint8_t **out, s` |
| `ls_seal_passphrase` | function | `include/local_store.h:70` | `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead, const uint8_t *plaintext, size_t ` |
| `ls_status` | enum | `include/local_store.h:39` | `` |
| `FREEDOM_MEDIA_DECODER_H` | macro | `include/media_decoder.h:2` | `#define FREEDOM_MEDIA_DECODER_H` |
| `MD_MAX_CATCHUP_READS` | macro | `include/media_decoder.h:65` | `#define MD_MAX_CATCHUP_READS` |
| `MD_MAX_SEGMENT_BYTES` | macro | `include/media_decoder.h:45` | `#define MD_MAX_SEGMENT_BYTES` |
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
| `nr_classify_host` | function | `include/net_realm.h:51` | `nr_realm nr_classify_host(const char *host);` |
| `nr_classify_url` | function | `include/net_realm.h:54` | `nr_realm nr_classify_url(const char *url);` |
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
| `os_isolate_namespaces` | function | `include/os_sandbox.h:97` | `os_status os_isolate_namespaces(void);` |
| `os_landlock_abi` | function | `include/os_sandbox.h:114` | `int os_landlock_abi(void);` |
| `os_landlock_restrict` | function | `include/os_sandbox.h:122` | `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n);` |
| `os_namespace_flags` | function | `include/os_sandbox.h:81` | `int os_namespace_flags(void);` |
| `os_no_dump` | function | `include/os_sandbox.h:70` | `os_status os_no_dump(void);` |
| `os_policy_size` | function | `include/os_sandbox.h:43` | `size_t os_policy_size(void);` |
| `os_prot_allowed` | function | `include/os_sandbox.h:52` | `int os_prot_allowed(long syscall_nr, unsigned long prot);` |
| `os_status` | enum | `include/os_sandbox.h:21` | `` |
| `os_violation` | enum | `include/os_sandbox.h:30` | `` |
| `CSS_LEN_UNSET` | function | `include/page_view.h:460` | `* CSS_LEN_UNSET (unset) / CSS_LEN_AUTO. z_index is signed, or CSS_LEN_UNSET. v1 * paints only position:relative (an in-f` |
| `FREEDOM_PAGE_VIEW_H` | macro | `include/page_view.h:2` | `#define FREEDOM_PAGE_VIEW_H` |
| `PV_BG_URL_MAX` | macro | `include/page_view.h:59` | `#define PV_BG_URL_MAX` |
| `PV_CONT_DEPTH` | macro | `include/page_view.h:53` | `#define PV_CONT_DEPTH` |
| `PV_GRID_TRACKS` | macro | `include/page_view.h:48` | `#define PV_GRID_TRACKS` |
| `PV_LEN_AUTO` | macro | `include/page_view.h:44` | `#define PV_LEN_AUTO` |
| `PV_LEN_END` | macro | `include/page_view.h:45` | `#define PV_LEN_END` |
| `PV_LEN_UNSET` | macro | `include/page_view.h:43` | `#define PV_LEN_UNSET` |
| `ancestors` | function | `include/page_view.h:906` | `* itself by walking its ancestors (css_visibility, 0 = unset). * * An explicit value on the run WINS over the box stack ` |
| `bx_display` | function | `include/page_view.h:208` | `* bx_display (flex/grid);` |
| `cause` | function | `include/page_view.h:767` | `* cause (spec/css_drops.md). Builds no view and changes nothing -- it exists so * "what is this page's CSS losing?" is a` |
| `container` | function | `include/page_view.h:207` | `* cont_id groups runs of one container (-1 = none);` |
| `default` | function | `include/page_view.h:835` | `* structure is carried by default (not gated by caps.css). */ void pv_set_indent(pv_view *v, int indent);` |
| `form` | function | `include/page_view.h:798` | `* form (-1 if none);` |
| `kind` | type_alias | `include/page_view.h:108` | `typedef struct pv_run { pv_kind kind;` |
| `nonzero` | function | `include/page_view.h:734` | `* when nonzero (JS allowed for this page) the <noscript> subtree is suppressed. */ pv_status pv_build_ex(const hp_docume` |
| `order` | function | `include/page_view.h:269` | `* groups the runs of ONE floated element in document order (-1 = not in a float);` |
| `parent_id` | type_alias | `include/page_view.h:388` | `typedef struct pv_box_def { int parent_id;` |
| `parent_id` | type_alias | `include/page_view.h:673` | `typedef struct pv_cont_def { int parent_id;` |
| `policy` | function | `include/page_view.h:749` | `* TRUSTED parent under full network policy (spec/tab.md §8) -- page_view stays * pure and never fetches. The external te` |
| `pv_add_box_def` | function | `include/page_view.h:1017` | `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d);` |
| `pv_add_cont_def` | function | `include/page_view.h:1021` | `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d);` |
| `pv_append` | function | `include/page_view.h:784` | `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break, const char *text, const char *href);` |
| `pv_append_image` | function | `include/page_view.h:792` | `pv_status pv_append_image(pv_view *v, int heading, int block_break, const char *alt, const char *src, int w, int h);` |
| `pv_append_input` | function | `include/page_view.h:801` | `pv_status pv_append_input(pv_view *v, int heading, int block_break, pv_input_type input_type, const char *text, const ch` |
| `pv_append_svg` | function | `include/page_view.h:818` | `pv_status pv_append_svg(pv_view *v, int heading, int block_break, const char *markup, int w, int h);` |
| `pv_append_video` | function | `include/page_view.h:811` | `pv_status pv_append_video(pv_view *v, int heading, int block_break, const char *alt, const char *src, const char *poster` |
| `pv_at` | function | `include/page_view.h:1041` | `const pv_run *pv_at(const pv_view *v, size_t i);` |
| `pv_box_at` | function | `include/page_view.h:1046` | `const pv_box_def *pv_box_at(const pv_view *v, size_t i);` |
| `pv_box_count` | function | `include/page_view.h:1045` | `size_t pv_box_count(const pv_view *v);` |
| `pv_box_def` | struct | `include/page_view.h:388` | `` |
| `pv_build` | function | `include/page_view.h:730` | `pv_status pv_build(const hp_document *doc, pv_view **out);` |
| `pv_cont_at` | function | `include/page_view.h:1026` | `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i);` |
| `pv_cont_count` | function | `include/page_view.h:1025` | `size_t pv_cont_count(const pv_view *v);` |
| `pv_cont_def` | struct | `include/page_view.h:673` | `` |
| `pv_count` | function | `include/page_view.h:1040` | `size_t pv_count(const pv_view *v);` |
| `pv_form_method` | enum | `include/page_view.h:94` | `` |
| `pv_free` | function | `include/page_view.h:1037` | `void pv_free(pv_view *v);` |
| `pv_input_type` | enum | `include/page_view.h:77` | `` |
| `pv_kind` | enum | `include/page_view.h:61` | `` |
| `pv_new` | function | `include/page_view.h:779` | `pv_view *pv_new(void);` |
| `pv_run` | struct | `include/page_view.h:108` | `` |
| `pv_set_bgcolor` | function | `include/page_view.h:845` | `void pv_set_bgcolor(pv_view *v, int bg_rgb);` |
| `pv_set_block_id` | function | `include/page_view.h:1002` | `void pv_set_block_id(pv_view *v, int block_id);` |
| `pv_set_box` | function | `include/page_view.h:985` | `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w, int box_center, int box_mt, int box_mb);` |
| `pv_set_box_pct` | function | `include/page_view.h:991` | `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct, int box_mt_pct, int box_mb_pct);` |
| `pv_set_color` | function | `include/page_view.h:837` | `void pv_set_color(pv_view *v, int fg_rgb);` |
| `pv_set_cont_box` | function | `include/page_view.h:952` | `void pv_set_cont_box(pv_view *v, int cont_box_id);` |
| `pv_set_cont_item` | function | `include/page_view.h:966` | `void pv_set_cont_item(pv_view *v, int cont_item);` |
| `pv_set_emphasis` | function | `include/page_view.h:830` | `void pv_set_emphasis(pv_view *v, int bold, int italic);` |
| `pv_set_flex` | function | `include/page_view.h:961` | `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis, int flex_order, int flex_direction, int fle` |
| `pv_set_float` | function | `include/page_view.h:975` | `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear, int float_ml, int float_ml_pct, int float_m` |
| `pv_set_grad_text` | function | `include/page_view.h:922` | `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4);` |
| `pv_set_grid` | function | `include/page_view.h:953` | `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span);` |
| `pv_set_grid_area` | function | `include/page_view.h:942` | `void pv_set_grid_area(pv_view *v, int row_start, int col_start);` |
| `pv_set_grid_rows` | function | `include/page_view.h:943` | `void pv_set_grid_rows(pv_view *v, int grid_rows);` |
| `pv_set_input_checked` | function | `include/page_view.h:1030` | `void pv_set_input_checked(pv_view *v, int checked);` |
| `pv_set_input_select_opts` | function | `include/page_view.h:1034` | `void pv_set_input_select_opts(pv_view *v, const char *select_opts);` |
| `pv_set_node_id` | function | `include/page_view.h:997` | `void pv_set_node_id(pv_view *v, dom_node_id node_id);` |
| `pv_set_oof` | function | `include/page_view.h:1010` | `void pv_set_oof(pv_view *v, int oof);` |
| `pv_set_own_box` | function | `include/page_view.h:1006` | `void pv_set_own_box(pv_view *v, int box_id);` |
| `pv_set_row_span` | function | `include/page_view.h:938` | `void pv_set_row_span(pv_view *v, int row_span);` |
| `pv_set_text_ext` | function | `include/page_view.h:915` | `void pv_set_text_ext(pv_view *v, const pv_text_ext *e);` |
| `pv_set_text_style` | function | `include/page_view.h:854` | `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs, int line_scale, int text_decoration);` |
| `pv_set_ua_tag` | function | `include/page_view.h:948` | `void pv_set_ua_tag(pv_view *v, int ua_tag);` |
| `pv_status` | enum | `include/page_view.h:34` | `` |
| `pv_text_ext` | struct | `include/page_view.h:870` | `` |
| `pv_text_ext_reset` | function | `include/page_view.h:901` | `void pv_text_ext_reset(pv_text_ext *e);` |
| `pv_view` | struct | `include/page_view.h:709` | `` |
| `resolved` | function | `include/page_view.h:741` | `* author CSS is still resolved (the presentation layer decides whether to apply it). * pv_build_ex is pv_build_full with` |
| `run` | function | `include/page_view.h:925` | `* run (cont_id, the bx_display, the parsed gap/justify/cols, plus flex-wrap/ * row-gap/align-items). No-op on an empty o` |
| `scale` | function | `include/page_view.h:535` | `* scale(1)) and rotate in whole degrees (transform_rotate);` |
| `word_spacing` | type_alias | `include/page_view.h:870` | `typedef struct pv_text_ext { int font_family, text_transform, letter_spacing, word_spacing;` |
| `FREEDOM_PDF_EXPORT_H` | macro | `include/pdf_export.h:2` | `#define FREEDOM_PDF_EXPORT_H` |
| `PE_EXT` | macro | `include/pdf_export.h:29` | `#define PE_EXT` |
| `PE_EXT_PNG` | macro | `include/pdf_export.h:30` | `#define PE_EXT_PNG` |
| `PE_FALLBACK_NAME` | macro | `include/pdf_export.h:31` | `#define PE_FALLBACK_NAME` |
| `PE_NAME_MAX` | macro | `include/pdf_export.h:27` | `#define PE_NAME_MAX` |
| `fallback` | function | `include/pdf_export.h:46` | `* fallback (PE_ERR_OVERFLOW, out left empty). title == NULL is treated as empty. * Does NOT append the extension (that i` |
| `literal` | function | `include/pdf_export.h:52` | `* trusted literal (e.g. PE_EXT / PE_EXT_PNG);` |
| `pe_build_path` | function | `include/pdf_export.h:61` | `pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz);` |
| `pe_build_path_ext` | function | `include/pdf_export.h:57` | `pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext, char *out, size_t outsz);` |
| `pe_paginate` | function | `include/pdf_export.h:70` | `size_t pe_paginate(const double *tops, const double *heights, size_t n, double page_h, int *out_page, double *out_page_y` |
| `pe_status` | enum | `include/pdf_export.h:33` | `` |
| `trusted` | function | `include/pdf_export.h:51` | `* dir is trusted (chosen by the app from XDG/$HOME);` |
| `FREEDOM_PERF_TRACE_H` | macro | `include/perf_trace.h:2` | `#define FREEDOM_PERF_TRACE_H` |
| `PT_MAX_SAMPLES` | macro | `include/perf_trace.h:31` | `#define PT_MAX_SAMPLES` |
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
| `PF_MAX_REFS` | macro | `include/prefetch.h:46` | `#define PF_MAX_REFS` |
| `PF_MAX_THREADS` | macro | `include/prefetch.h:48` | `#define PF_MAX_THREADS` |
| `fetch` | function | `include/prefetch.h:102` | `* claiming jobs and running fetch(ctx, "GET", url, ...). Returns 0 on success or * -1 when no thread could start (the ca` |
| `inner` | type_alias | `include/prefetch.h:129` | `typedef struct pf_gated_fetch { pf_fetch_fn inner;` |
| `int` | function | `include/prefetch.h:65` | `typedef int (*pf_fetch_fn)(void *ctx, const char *method, const char *url, const char *body, size_t body_len, int *out_s` |
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
| `pf_pooled_fetch` | function | `include/prefetch.h:134` | `int pf_pooled_fetch(void *vctx, const char *method, const char *url, const char *body, size_t body_len, int *out_status,` |
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
| `PREFS_VERSION` | macro | `include/prefs.h:25` | `#define PREFS_VERSION` |
| `anyway` | function | `include/prefs.h:105` | `* page is rendered by the normal confined pipeline anyway (defence in depth). * *out is owned (free());` |
| `free` | function | `include/prefs.h:71` | `* free(). */ prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len);` |
| `prefs_bookmark_index` | function | `include/prefs.h:81` | `int prefs_bookmark_index(const prefs_state *p, const char *url);` |
| `prefs_bookmark_toggle` | function | `include/prefs.h:86` | `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url, const char *title, int *added);` |
| `prefs_bookmarks_page` | function | `include/prefs.h:107` | `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len);` |
| `prefs_entry` | struct | `include/prefs.h:45` | `` |
| `prefs_free` | function | `include/prefs.h:68` | `void prefs_free(prefs_state *p);` |
| `prefs_history_add` | function | `include/prefs.h:92` | `prefs_status prefs_history_add(prefs_state *p, const char *url);` |
| `prefs_init` | function | `include/prefs.h:65` | `void prefs_init(prefs_state *p);` |
| `prefs_parse` | function | `include/prefs.h:78` | `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out);` |
| `prefs_state` | struct | `include/prefs.h:50` | `` |
| `prefs_status` | enum | `include/prefs.h:36` | `` |
| `prefs_suggest` | function | `include/prefs.h:100` | `int prefs_suggest(const prefs_state *p, const char *query, char *out, size_t row_len, int max_rows);` |
| `theme_mode` | type_alias | `include/prefs.h:49` | `typedef struct prefs_state { int theme_mode;` |
| `FREEDOM_PROFILE_H` | macro | `include/profile.h:2` | `#define FREEDOM_PROFILE_H` |
| `PROFILE_KEY_FILE` | macro | `include/profile.h:31` | `#define PROFILE_KEY_FILE` |
| `PROFILE_PREFS_FILE` | macro | `include/profile.h:33` | `#define PROFILE_PREFS_FILE` |
| `absent` | function | `include/profile.h:53` | `* the keyfile when absent (0600, atomic write);` |
| `closed` | function | `include/profile.h:54` | `* wrong size fails closed (PROFILE_ERR_KEY, never overwritten). Derives the * AEAD key (Argon2id, per-device salt) and m` |
| `dir` | type_alias | `include/profile.h:45` | `typedef struct profile_ctx { char dir[1024];` |
| `profile_close` | function | `include/profile.h:67` | `void profile_close(profile_ctx *ctx);` |
| `profile_ctx` | struct | `include/profile.h:46` | `` |
| `profile_load` | function | `include/profile.h:61` | `profile_status profile_load(const profile_ctx *ctx, prefs_state *out);` |
| `profile_save` | function | `include/profile.h:64` | `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p);` |
| `profile_status` | enum | `include/profile.h:35` | `` |
| `FREEDOM_PSL_DATA_H` | macro | `include/psl_data.h:2` | `#define FREEDOM_PSL_DATA_H` |
| `psl_exceptions` | variable | `include/psl_data.h:25` | `extern const char *const psl_exceptions[];` |
| `psl_exceptions_n` | variable | `include/psl_data.h:26` | `extern const size_t psl_exceptions_n;` |
| `psl_rules` | variable | `include/psl_data.h:20` | `extern const char *const psl_rules[];` |
| `psl_rules_n` | variable | `include/psl_data.h:22` | `extern const size_t psl_rules_n;` |
| `psl_wildcards` | variable | `include/psl_data.h:23` | `extern const char *const psl_wildcards[];` |
| `psl_wildcards_n` | variable | `include/psl_data.h:24` | `extern const size_t psl_wildcards_n;` |
| `FREEDOM_RENDER_DOC_H` | macro | `include/render_doc.h:2` | `#define FREEDOM_RENDER_DOC_H` |
| `IMG_FAIL_OK` | function | `include/render_doc.h:322` | `* IMG_FAIL_OK (not a failure) or the reason is unknown. */ const char *rd_image_fail_label(img_fail_reason reason);` |
| `RD_IMAGE` | function | `include/render_doc.h:59` | `* RD_IMAGE (image src) and RD_INPUT (the owning form's action);` |
| `decision` | function | `include/render_doc.h:316` | `* decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never * NULL. */ const char *rd_image_label(rdp_i` |
| `default` | function | `include/render_doc.h:142` | `* default (layout is structure, not author styling, and leaks nothing to the * network) so the presentation layer can la` |
| `form` | function | `include/render_doc.h:63` | `* form (-1 = none);` |
| `img_fail_reason` | enum | `include/render_doc.h:34` | `` |
| `kind` | type_alias | `include/render_doc.h:64` | `typedef struct rd_block { rd_kind kind;` |
| `list` | function | `include/render_doc.h:18` | `* inert display list (page_view) and the presentation orchestrator (the GUI and * the --headless writer). It decides WHA` |
| `rd_at` | function | `include/render_doc.h:291` | `const rd_block *rd_at(const rd_doc *d, size_t i);` |
| `rd_block` | struct | `include/render_doc.h:64` | `` |
| `rd_block_tag` | function | `include/render_doc.h:313` | `const char *rd_block_tag(const rd_block *b);` |
| `rd_box_at` | function | `include/render_doc.h:296` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i);` |
| `rd_box_count` | function | `include/render_doc.h:295` | `size_t rd_box_count(const rd_doc *d);` |
| `rd_cont_at` | function | `include/render_doc.h:301` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i);` |
| `rd_cont_count` | function | `include/render_doc.h:300` | `size_t rd_cont_count(const rd_doc *d);` |
| `rd_count` | function | `include/render_doc.h:290` | `size_t rd_count(const rd_doc *d);` |
| `rd_doc` | struct | `include/render_doc.h:242` | `` |
| `rd_free` | function | `include/render_doc.h:287` | `void rd_free(rd_doc *d);` |
| `rd_input_label` | function | `include/render_doc.h:327` | `const char *rd_input_label(int input_type);` |
| `rd_kind` | enum | `include/render_doc.h:42` | `` |
| `rd_kind_name` | function | `include/render_doc.h:305` | `const char *rd_kind_name(rd_kind k);` |
| `rd_status` | enum | `include/render_doc.h:268` | `` |
| `rdp_images_warning` | function | `include/render_doc.h:277` | `* rdp_images_warning() is prepended so the user is always told. Each image * becomes an RD_IMAGE block whose img_decisio` |
| `to` | function | `include/render_doc.h:228` | `* belongs to (-1 = none);` |
| `FREEDOM_RENDER_POLICY_H` | macro | `include/render_policy.h:2` | `#define FREEDOM_RENDER_POLICY_H` |
| `RDP_TRACKER_MAX_DIM` | macro | `include/render_policy.h:27` | `#define RDP_TRACKER_MAX_DIM` |
| `images` | type_alias | `include/render_policy.h:32` | `typedef struct rdp_caps { bool images;` |
| `rdp_caps` | struct | `include/render_policy.h:32` | `` |
| `rdp_caps_safe` | function | `include/render_policy.h:48` | `rdp_caps rdp_caps_safe(void);` |
| `rdp_image_decision` | function | `include/render_policy.h:59` | `rdp_img_decision rdp_image_decision(rdp_caps caps, const char *top_level_url, const char *image_url, int declared_w, int` |
| `rdp_images_warning` | function | `include/render_policy.h:69` | `const char *rdp_images_warning(void);` |
| `rdp_img_decision` | enum | `include/render_policy.h:39` | `` |
| `rdp_img_reason` | function | `include/render_policy.h:66` | `const char *rdp_img_reason(rdp_img_decision d);` |
| `rdp_is_tracking_pixel` | function | `include/render_policy.h:53` | `int rdp_is_tracking_pixel(int w, int h);` |
| `size` | function | `include/render_policy.h:56` | `* announced size (e.g. <img width height>);` |
| `FREEDOM_RENDERER_H` | macro | `include/renderer.h:2` | `#define FREEDOM_RENDERER_H` |
| `RD_MAX_FIELD` | macro | `include/renderer.h:38` | `#define RD_MAX_FIELD` |
| `RD_MAX_INPUT` | macro | `include/renderer.h:36` | `#define RD_MAX_INPUT` |
| `rd_render_html` | function | `include/renderer.h:43` | `rd_status rd_render_html(const char *html, size_t len, rd_result *out);` |
| `rd_result` | struct | `include/renderer.h:29` | `` |
| `rd_result_free` | function | `include/renderer.h:46` | `void rd_result_free(rd_result *out);` |
| `rd_status` | enum | `include/renderer.h:20` | `` |
| `status` | type_alias | `include/renderer.h:28` | `typedef struct rd_result { rd_status status;` |
| `FREEDOM_REQUEST_POLICY_H` | macro | `include/request_policy.h:2` | `#define FREEDOM_REQUEST_POLICY_H` |
| `rp_decision` | enum | `include/request_policy.h:21` | `` |
| `rp_evaluate` | function | `include/request_policy.h:40` | `rp_decision rp_evaluate(const char *top_level_url, const char *request_url);` |
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
| `connection` | function | `include/secure_fetch.h:292` | `* on each connection (Zero Trust). Each target is re-validated and a downgrade * to http:// is refused. Exceeding max_re` |
| `policy` | type_alias | `include/secure_fetch.h:74` | `typedef struct sf_config { sf_policy policy;` |
| `sf_chain_info` | struct | `include/secure_fetch.h:60` | `` |
| `sf_check_chain_policy` | function | `include/secure_fetch.h:252` | `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy);` |
| `sf_check_group_is_pq` | function | `include/secure_fetch.h:248` | `sf_status sf_check_group_is_pq(const char *negotiated_group);` |
| `sf_check_tls_version` | function | `include/secure_fetch.h:244` | `sf_status sf_check_tls_version(const char *negotiated_version);` |
| `sf_config` | struct | `include/secure_fetch.h:75` | `` |
| `sf_config_default` | function | `include/secure_fetch.h:226` | `sf_config sf_config_default(void);` |
| `sf_cookie_line_matches` | function | `include/secure_fetch.h:222` | `int sf_cookie_line_matches(const char *line, const char *host, const char *path, long now, char *out, size_t outsz);` |
| `sf_cookie_put` | function | `include/secure_fetch.h:217` | `void sf_cookie_put(const char *url, const char *namevalue);` |
| `sf_enforce_policy` | function | `include/secure_fetch.h:261` | `sf_status sf_enforce_policy(const char *tls_version, const char *group, const sf_chain_info *chain, sf_policy policy);` |
| `sf_get` | function | `include/secure_fetch.h:288` | `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out);` |
| `sf_global_init` | function | `include/secure_fetch.h:204` | `void sf_global_init(void);` |
| `sf_impersonate_kex_groups` | function | `include/secure_fetch.h:235` | `const char *sf_impersonate_kex_groups(void);` |
| `sf_impersonate_tls13_ciphers` | function | `include/secure_fetch.h:236` | `const char *sf_impersonate_tls13_ciphers(void);` |
| `sf_is_redirect_code` | function | `include/secure_fetch.h:267` | `int sf_is_redirect_code(long http_code);` |
| `sf_parse_location_header` | function | `include/secure_fetch.h:273` | `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz);` |
| `sf_policy` | enum | `include/secure_fetch.h:40` | `` |
| `sf_proxy_type` | enum | `include/secure_fetch.h:69` | `` |
| `sf_resolve_redirect` | function | `include/secure_fetch.h:278` | `sf_status sf_resolve_redirect(const char *base_url, const char *location, char *out, size_t outsz);` |
| `sf_response` | struct | `include/secure_fetch.h:117` | `` |
| `sf_response_free` | function | `include/secure_fetch.h:312` | `void sf_response_free(sf_response *resp);` |
| `sf_status` | enum | `include/secure_fetch.h:23` | `` |
| `sf_user_agent_or_default` | function | `include/secure_fetch.h:231` | `const char *sf_user_agent_or_default(const char *ua);` |
| `sf_validate_url` | function | `include/secure_fetch.h:241` | `sf_status sf_validate_url(const char *url);` |
| `skipped` | function | `include/secure_fetch.h:256` | `* skipped (a classical key exchange is accepted);` |
| `status` | type_alias | `include/secure_fetch.h:116` | `typedef struct sf_response { sf_status status;` |
| `validators` | function | `include/secure_fetch.h:17` | `* The security logic lives in pure validators (no I/O);` |
| `void` | function | `include/secure_fetch.h:110` | `void (*progress_cb)(const uint8_t *body, size_t body_len, void *ctx);` |
| `FREEDOM_SVG_PAINT_H` | macro | `include/svg_paint.h:2` | `#define FREEDOM_SVG_PAINT_H` |
| `svp_draw` | function | `include/svg_paint.h:31` | `void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, double h, int current_rgb);` |
| `FREEDOM_SVG_RENDER_H` | macro | `include/svg_render.h:2` | `#define FREEDOM_SVG_RENDER_H` |
| `SV_DEFAULT_H` | macro | `include/svg_render.h:42` | `#define SV_DEFAULT_H` |
| `SV_DEFAULT_W` | macro | `include/svg_render.h:41` | `#define SV_DEFAULT_W` |
| `SV_MAX_DEPTH` | macro | `include/svg_render.h:35` | `#define SV_MAX_DEPTH` |
| `SV_MAX_INPUT` | macro | `include/svg_render.h:37` | `#define SV_MAX_INPUT` |
| `SV_MAX_POINTS` | macro | `include/svg_render.h:33` | `#define SV_MAX_POINTS` |
| `SV_MAX_SEGS` | macro | `include/svg_render.h:34` | `#define SV_MAX_SEGS` |
| `SV_MAX_SHAPES` | macro | `include/svg_render.h:31` | `#define SV_MAX_SHAPES` |
| `SV_TEXT_MAX` | macro | `include/svg_render.h:36` | `#define SV_TEXT_MAX` |
| `height` | type_alias | `include/svg_render.h:104` | `typedef struct sv_image { double width, height;` |
| `kind` | type_alias | `include/svg_render.h:75` | `typedef struct sv_shape { int kind;` |
| `sv_fit` | function | `include/svg_render.h:131` | `void sv_fit(const sv_image *img, double dw, double dh, double *scale, double *off_x, double *off_y);` |
| `sv_image` | struct | `include/svg_render.h:104` | `` |
| `sv_parse` | function | `include/svg_render.h:120` | `sv_status sv_parse(const char *markup, size_t len, sv_image *out);` |
| `sv_parse_ex` | function | `include/svg_render.h:125` | `sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill);` |
| `sv_seg` | struct | `include/svg_render.h:65` | `` |
| `sv_shape` | struct | `include/svg_render.h:75` | `` |
| `sv_shape_kind` | enum | `include/svg_render.h:44` | `` |
| `sv_status` | enum | `include/svg_render.h:25` | `` |
| `sv_verb` | enum | `include/svg_render.h:58` | `` |
| `verb` | type_alias | `include/svg_render.h:64` | `typedef struct sv_seg { int verb;` |
| `FREEDOM_TAB_H` | macro | `include/tab.h:2` | `#define FREEDOM_TAB_H` |
| `TAB_MAX_INPUT` | macro | `include/tab.h:100` | `#define TAB_MAX_INPUT` |
| `decode` | function | `include/tab.h:254` | `* could not decode (caller shows the placeholder), which is not a transport error. * TAB_ERR_* is reserved for transport` |
| `exclusively` | function | `include/tab.h:157` | `* exclusively (tab_subreq_permitted). Default 0: zero fetches, Privacy by Default. */ void tab_set_css_allowed(tab *t, i` |
| `jar` | function | `include/tab.h:147` | `* the trusted parent read from its ephemeral network jar (sf_cookie_header_for). Only * meaningful for a trusted host (a` |
| `out_status` | function | `include/tab.h:128` | `* On success return 0 and set *out_status (HTTP status), *out_body / *out_body_len * (malloc'd response bytes, tab frees` |
| `string` | function | `include/tab.h:198` | `* event_type is a JS event type string (e.g. "keydown", "input", "change"). * key is the keyboard key value (may be NULL` |
| `tab` | type_alias | `include/tab.h:44` | `typedef struct tab tab;` |
| `tab_alive` | function | `include/tab.h:267` | `int tab_alive(const tab *t);` |
| `tab_child_pid` | function | `include/tab.h:270` | `pid_t tab_child_pid(const tab *t);` |
| `tab_click` | function | `include/tab.h:228` | `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out);` |
| `tab_close` | function | `include/tab.h:273` | `void tab_close(tab *t);` |
| `tab_decode_image_data_url` | function | `include/tab.h:264` | `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out);` |
| `tab_eval` | function | `include/tab.h:248` | `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out);` |
| `tab_eval_result` | struct | `include/tab.h:80` | `` |
| `tab_eval_result_free` | function | `include/tab.h:277` | `void tab_eval_result_free(tab_eval_result *r);` |
| `tab_image` | struct | `include/tab.h:93` | `` |
| `tab_image_free` | function | `include/tab.h:278` | `void tab_image_free(tab_image *img);` |
| `tab_load` | function | `include/tab.h:175` | `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out);` |
| `tab_load_full` | function | `include/tab.h:191` | `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url, int run_js, int reader, int prefers` |
| `tab_open` | function | `include/tab.h:109` | `* and reaches tab_open (the app and the test harness) must call this first. */ void tab_worker_dispatch(int argc, char *` |
| `tab_page` | struct | `include/tab.h:49` | `` |
| `tab_page_free` | function | `include/tab.h:276` | `void tab_page_free(tab_page *p);` |
| `tab_parse_worker_args` | function | `include/tab.h:116` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd);` |
| `tab_read_view` | function | `include/tab.h:222` | `tab_status tab_read_view(tab *t, tab_page *out);` |
| `tab_set_cookies` | function | `include/tab.h:151` | `void tab_set_cookies(tab *t, const char *cookies);` |
| `tab_set_fetcher` | function | `include/tab.h:139` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx);` |
| `tab_set_net_allowed` | function | `include/tab.h:144` | `void tab_set_net_allowed(tab *t, int allowed);` |
| `tab_set_viewport_w` | function | `include/tab.h:165` | `void tab_set_viewport_w(tab *t, int px);` |
| `tab_status` | enum | `include/tab.h:30` | `` |
| `tab_submit` | function | `include/tab.h:235` | `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented);` |
| `tab_subreq_permitted` | function | `include/tab.h:170` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method);` |
| `tab_tick` | function | `include/tab.h:242` | `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out);` |
| `tab_worker_dispatch` | function | `include/tab.h:105` | `* Call tab_worker_dispatch(argc, argv) as the FIRST thing in main(): if argv is the * internal "--tab-worker <rfd> <wfd>` |
| `view` | function | `include/tab.h:178` | `* <noscript> handling in the built view (off => fallback shown, on => suppressed) * and is where allowlisted page-script` |
| `width` | type_alias | `include/tab.h:93` | `typedef struct tab_image { uint32_t width;` |
| `FREEDOM_TEXT_SHAPE_H` | macro | `include/text_shape.h:19` | `#define FREEDOM_TEXT_SHAPE_H` |
| `TSH_MAX_GLYPHS` | macro | `include/text_shape.h:35` | `#define TSH_MAX_GLYPHS` |
| `TSH_MAX_TEXT` | macro | `include/text_shape.h:37` | `#define TSH_MAX_TEXT` |
| `content` | function | `include/text_shape.h:11` | `* TEXT is hostile remote content (sanitised UTF-8) and is fuzzed (make fuzz-tsh);` |
| `family` | type_alias | `include/text_shape.h:30` | `typedef struct tsh_font { int family;` |
| `origin` | function | `include/text_shape.h:51` | `* glyphs are written with positions relative to origin (0,0) on the baseline, * and *out_adv holds the total pen advance` |
| `tsh_draw` | function | `include/text_shape.h:65` | `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px, double x, double baseline, const char *text, size_t len);` |
| `tsh_font` | struct | `include/text_shape.h:30` | `` |
| `tsh_measure` | function | `include/text_shape.h:60` | `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len);` |
| `tsh_ready` | function | `include/text_shape.h:48` | `int tsh_ready(void);` |
| `tsh_shutdown` | function | `include/text_shape.h:69` | `void tsh_shutdown(void);` |
| `tsh_status` | enum | `include/text_shape.h:39` | `` |
| `FREEDOM_TEXTFIELD_H` | macro | `include/textfield.h:2` | `#define FREEDOM_TEXTFIELD_H` |
| `TF_CAP` | macro | `include/textfield.h:22` | `#define TF_CAP` |
| `buf` | type_alias | `include/textfield.h:24` | `typedef struct tf_field { char buf[TF_CAP];` |
| `tf_backspace` | function | `include/textfield.h:53` | `void tf_backspace(tf_field *f);` |
| `tf_clear` | function | `include/textfield.h:45` | `void tf_clear(tf_field *f);` |
| `tf_cursor` | function | `include/textfield.h:68` | `size_t tf_cursor(const tf_field *f);` |
| `tf_delete` | function | `include/textfield.h:56` | `void tf_delete(tf_field *f);` |
| `tf_end` | function | `include/textfield.h:63` | `void tf_end(tf_field *f);` |
| `tf_field` | struct | `include/textfield.h:25` | `` |
| `tf_home` | function | `include/textfield.h:62` | `void tf_home(tf_field *f);` |
| `tf_init` | function | `include/textfield.h:38` | `void tf_init(tf_field *f);` |
| `tf_insert` | function | `include/textfield.h:50` | `tf_status tf_insert(tf_field *f, char c);` |
| `tf_len` | function | `include/textfield.h:67` | `size_t tf_len(const tf_field *f);` |
| `tf_move` | function | `include/textfield.h:59` | `void tf_move(tf_field *f, long delta);` |
| `tf_set` | function | `include/textfield.h:42` | `tf_status tf_set(tf_field *f, const char *s);` |
| `tf_status` | enum | `include/textfield.h:31` | `` |
| `tf_text` | function | `include/textfield.h:66` | `const char *tf_text(const tf_field *f);` |
| `FREEDOM_TLS_IMPERSONATE_H` | macro | `include/tls_impersonate.h:2` | `#define FREEDOM_TLS_IMPERSONATE_H` |
| `TI_MAGIC` | macro | `include/tls_impersonate.h:56` | `#define TI_MAGIC` |
| `TI_MAX_BODY` | macro | `include/tls_impersonate.h:60` | `#define TI_MAX_BODY` |
| `TI_MAX_CHAIN` | macro | `include/tls_impersonate.h:63` | `#define TI_MAX_CHAIN` |
| `TI_MAX_GROUP` | macro | `include/tls_impersonate.h:64` | `#define TI_MAX_GROUP` |
| `TI_MAX_HEADERS` | macro | `include/tls_impersonate.h:59` | `#define TI_MAX_HEADERS` |
| `TI_MAX_METHOD` | macro | `include/tls_impersonate.h:58` | `#define TI_MAX_METHOD` |
| `TI_MAX_RESP_BODY` | macro | `include/tls_impersonate.h:62` | `#define TI_MAX_RESP_BODY` |
| `TI_MAX_RESP_HDR` | macro | `include/tls_impersonate.h:61` | `#define TI_MAX_RESP_HDR` |
| `TI_MAX_URL` | macro | `include/tls_impersonate.h:57` | `#define TI_MAX_URL` |
| `chain` | function | `include/tls_impersonate.h:28` | `* * The response carries the peer certificate chain (DER) and the negotiated group so * the TRUSTED PARENT re-applies th` |
| `status` | type_alias | `include/tls_impersonate.h:78` | `typedef struct ti_resp { long status;` |
| `success` | function | `include/tls_impersonate.h:93` | `* ti_decode_* returns 0 on success (out fully populated), <0 on any malformed, * truncated or over-cap input (out left z` |
| `ti_decode_req` | function | `include/tls_impersonate.h:97` | `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out);` |
| `ti_decode_resp` | function | `include/tls_impersonate.h:101` | `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out);` |
| `ti_encode_resp` | function | `include/tls_impersonate.h:99` | `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap);` |
| `ti_profile` | enum | `include/tls_impersonate.h:38` | `` |
| `ti_req` | struct | `include/tls_impersonate.h:68` | `` |
| `ti_req_free` | function | `include/tls_impersonate.h:98` | `void ti_req_free(ti_req *r);` |
| `ti_resp` | struct | `include/tls_impersonate.h:78` | `` |
| `ti_resp_free` | function | `include/tls_impersonate.h:102` | `void ti_resp_free(ti_resp *r);` |
| `ti_should_impersonate` | function | `include/tls_impersonate.h:52` | `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled, int host_in_impersonate);` |
| `FREEDOM_UI_H` | macro | `include/ui.h:2` | `#define FREEDOM_UI_H` |
| `available` | function | `include/ui.h:85` | `* cheapest artifact to inspect a render where no display is available (CI, an AI * agent): export, then read the PNG dir` |
| `disk` | function | `include/ui.h:102` | `* images are read from disk (confined to the document directory by render_doc). * top_url is the page origin (https or f` |
| `images` | function | `include/ui.h:104` | `* fetcher loads no images (placeholders, as before). Any image that fails falls back * to its placeholder, byte-identica` |
| `offset` | type_alias | `include/ui.h:29` | `typedef struct ui_line { size_t offset;` |
| `placeholders` | function | `include/ui.h:97` | `* above always draw image placeholders (no worker to decode hostile bytes);` |
| `rd_doc` | struct | `include/ui.h:68` | `` |
| `space` | function | `include/ui.h:43` | `* Breaks at the last fitting space (the break space is consumed), hard-breaks * words longer than max_cols, and treats '` |
| `tab` | struct | `include/ui.h:94` | `` |
| `ui_clamp_scroll` | function | `include/ui.h:54` | `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines);` |
| `ui_dump_layout` | function | `include/ui.h:126` | `ui_status ui_dump_layout(const struct rd_doc *doc);` |
| `ui_layout` | struct | `include/ui.h:34` | `` |
| `ui_layout_free` | function | `include/ui.h:51` | `void ui_layout_free(ui_layout *lay);` |
| `ui_line` | struct | `include/ui.h:29` | `` |
| `ui_render_pdf` | function | `include/ui.h:79` | `ui_status ui_render_pdf(const struct rd_doc *doc, const char *out_path, long *out_pages);` |
| `ui_render_pdf_images` | function | `include/ui.h:112` | `ui_status ui_render_pdf_images(const struct rd_doc *doc, struct tab *t, const char *top_url, int (*img_fetch)(void *, co` |
| `ui_render_png` | function | `include/ui.h:92` | `ui_status ui_render_png(const struct rd_doc *doc, const char *out_path, long *out_h);` |
| `ui_render_viewport_w` | function | `include/ui.h:131` | `int ui_render_viewport_w(void);` |
| `ui_run_browser` | function | `include/ui.h:66` | `ui_status ui_run_browser(const char *start_url);` |
| `ui_run_text_view` | function | `include/ui.h:61` | `ui_status ui_run_text_view(const char *title, const char *text, size_t text_len);` |
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
| `url_omnibox` | function | `include/url.h:97` | `url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz);` |
| `url_parts` | struct | `include/url.h:129` | `` |
| `url_remove_dot_segments` | function | `include/url.h:60` | `url_status url_remove_dot_segments(const char *path, char *out, size_t outsz);` |
| `url_resolve_file` | function | `include/url.h:172` | `url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz);` |
| `url_resolve_https` | function | `include/url.h:70` | `url_status url_resolve_https(const char *base, const char *ref, char *out, size_t outsz);` |
| `url_search_rewrite` | function | `include/url.h:110` | `url_status url_search_rewrite(const char *url, char *out, size_t outsz);` |
| `url_split` | function | `include/url.h:147` | `url_status url_split(const char *url, url_parts *out);` |
| `url_status` | enum | `include/url.h:32` | `` |
| `url_validate_https` | function | `include/url.h:55` | `url_status url_validate_https(const char *url);` |
| `UTIL_H` | macro | `include/util.h:5` | `#define UTIL_H` |
| `fnv1a` | function | `include/util.h:66` | `static inline uint64_t fnv1a(const char *s, size_t n)` |
| `mem_contains_ci` | function | `include/util.h:43` | `static inline int mem_contains_ci(const void *hay, size_t hlen, const char *needle)` |
| `read_full` | function | `include/util.h:25` | `static inline int read_full(int fd, void *buf, size_t n)` |
| `utf8_seq_len` | function | `include/util.h:56` | `static inline size_t utf8_seq_len(unsigned char c)` |
| `write_full` | function | `include/util.h:14` | `static inline int write_full(int fd, const void *buf, size_t n)` |
| `FREEDOM_WEBCAPS_H` | macro | `include/webcaps.h:2` | `#define FREEDOM_WEBCAPS_H` |
| `js` | type_alias | `include/webcaps.h:38` | `typedef struct wc_caps { /* leak-free (global): granted by user toggle or allow.conf presentation-trust. */ bool js;` |
| `js_mode` | type_alias | `include/webcaps.h:57` | `typedef struct wc_input { jsp_mode js_mode;` |
| `wc_caps` | struct | `include/webcaps.h:38` | `` |
| `wc_derive` | function | `include/webcaps.h:72` | `wc_caps wc_derive(wc_input in);` |
| `wc_from_flags` | function | `include/webcaps.h:77` | `wc_caps wc_from_flags(bool js, bool css, bool images);` |
| `wc_input` | struct | `include/webcaps.h:57` | `` |
| `wc_render_caps` | function | `include/webcaps.h:82` | `rdp_caps wc_render_caps(wc_caps c);` |
| `wc_safe` | function | `include/webcaps.h:67` | `wc_caps wc_safe(void);` |
| `FREEDOM_ZOOM_H` | macro | `include/zoom.h:2` | `#define FREEDOM_ZOOM_H` |
| `ZM_DEFAULT_PCT` | macro | `include/zoom.h:23` | `#define ZM_DEFAULT_PCT` |
| `ZM_MAX_PCT` | macro | `include/zoom.h:22` | `#define ZM_MAX_PCT` |
| `ZM_MIN_PCT` | macro | `include/zoom.h:20` | `#define ZM_MIN_PCT` |
| `zm_apply` | function | `include/zoom.h:42` | `double zm_apply(double base_px, int pct);` |
| `zm_clamp` | function | `include/zoom.h:26` | `int zm_clamp(int pct);` |
| `zm_reset` | function | `include/zoom.h:35` | `int zm_reset(void);` |
| `zm_scale` | function | `include/zoom.h:38` | `double zm_scale(int pct);` |
| `zm_zoom_in` | function | `include/zoom.h:29` | `int zm_zoom_in(int pct);` |
| `zm_zoom_out` | function | `include/zoom.h:32` | `int zm_zoom_out(int pct);` |
| `fp_accept_language` | function | `src/anti_fp.c:26` | `const char *fp_accept_language(void)` |
| `fp_accept_language_header` | function | `src/anti_fp.c:30` | `const char *fp_accept_language_header(void)` |
| `fp_app_code_name` | function | `src/anti_fp.c:60` | `const char *fp_app_code_name(void)` |
| `fp_app_name` | function | `src/anti_fp.c:68` | `const char *fp_app_name(void)` |
| `fp_app_version` | function | `src/anti_fp.c:56` | `const char *fp_app_version(void)` |
| `fp_bucket_screen` | function | `src/anti_fp.c:98` | `void fp_bucket_screen(int w, int h, int *out_w, int *out_h)` |
| `fp_build_id` | function | `src/anti_fp.c:80` | `const char *fp_build_id(void)` |
| `fp_coarsen_time_ms` | function | `src/anti_fp.c:16` | `uint64_t fp_coarsen_time_ms(uint64_t raw_ms)` |
| `fp_cookie_enabled` | function | `src/anti_fp.c:92` | `int fp_cookie_enabled(void)` |
| `fp_device_memory_gb` | function | `src/anti_fp.c:50` | `int fp_device_memory_gb(void)` |
| `fp_hardware_concurrency` | function | `src/anti_fp.c:46` | `int fp_hardware_concurrency(void)` |
| `fp_max_touch_points` | function | `src/anti_fp.c:84` | `int fp_max_touch_points(void)` |
| `fp_on_line` | function | `src/anti_fp.c:88` | `int fp_on_line(void)` |
| `fp_origin_key` | function | `src/anti_fp.c:138` | `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain)` |
| `fp_oscpu` | function | `src/anti_fp.c:76` | `const char *fp_oscpu(void)` |
| `fp_perturb` | function | `src/anti_fp.c:127` | `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key)` |
| `fp_platform` | function | `src/anti_fp.c:38` | `const char *fp_platform(void)` |
| `fp_product` | function | `src/anti_fp.c:64` | `const char *fp_product(void)` |
| `fp_product_sub` | function | `src/anti_fp.c:72` | `const char *fp_product_sub(void)` |
| `fp_timezone` | function | `src/anti_fp.c:34` | `const char *fp_timezone(void)` |
| `fp_user_agent` | function | `src/anti_fp.c:22` | `const char *fp_user_agent(void)` |
| `fp_vendor` | function | `src/anti_fp.c:42` | `const char *fp_vendor(void)` |
| `splitmix64` | function | `src/anti_fp.c:120` | `static uint64_t splitmix64(uint64_t *state)` |
| `bf_collapse` | function | `src/block_flow.c:29` | `double bf_collapse(double a, double b)` |
| `bf_collapse_n` | function | `src/block_flow.c:14` | `double bf_collapse_n(const double *m, size_t n)` |
| `bf_margins_adjoin` | function | `src/block_flow.c:34` | `int bf_margins_adjoin(double border_px, double padding_px)` |
| `finite_or_zero` | function | `src/block_flow.c:11` | `static double finite_or_zero(double v)` |
| `BLOCK` | macro | `src/box_style.c:64` | `#define BLOCK` |
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
| `bg_size_component` | function | `src/box_style.c:367` | `static double bg_size_component(int px_val, int pct_pm, double area)` |
| `bx_background_layer` | function | `src/box_style.c:373` | `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h,
                    ...` |
| `bx_block_ua_box` | function | `src/box_style.c:222` | `bx_box bx_block_ua_box(int heading_level, int in_list, bx_ua_tag ua)` |
| `bx_border_box_h` | function | `src/box_style.c:324` | `double bx_border_box_h(double declared_h, int border_box,
                       double pad_t, do...` |
| `bx_content_cap` | function | `src/box_style.c:352` | `double bx_content_cap(double width_cap, int border_box,
                      double pad_l, doubl...` |
| `bx_content_clipped` | function | `src/box_style.c:335` | `int bx_content_clipped(int overflow_x, int overflow_y)` |
| `bx_default_for_tag` | function | `src/box_style.c:160` | `bx_box bx_default_for_tag(const char *tag)` |
| `bx_default_for_ua` | function | `src/box_style.c:216` | `bx_box bx_default_for_ua(bx_ua_tag id)` |
| `bx_display_name` | function | `src/box_style.c:412` | `const char *bx_display_name(bx_display d)` |
| `bx_lp_px` | function | `src/box_style.c:341` | `double bx_lp_px(int px_val, int pct_pm, double basis)` |
| `bx_parse_display` | function | `src/box_style.c:258` | `bx_status bx_parse_display(const char *token, bx_display *out)` |
| `bx_place` | function | `src/box_style.c:268` | `bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,
                ...` |
| `bx_replaced_box` | function | `src/box_style.c:309` | `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den,
                    doub...` |
| `bx_table_role_of` | function | `src/box_style.c:168` | `bx_table_role bx_table_role_of(const char *tag, css_display display)` |
| `bx_ua_of_tag` | function | `src/box_style.c:207` | `bx_ua_tag bx_ua_of_tag(const char *tag)` |
| `bx_width_cap` | function | `src/box_style.c:285` | `double bx_width_cap(int w_px, int w_pct, double avail_w)` |
| `copy_lower_trim` | function | `src/box_style.c:35` | `static int copy_lower_trim(const char *in, char *out, size_t out_size)` |
| `disp_row` | struct | `src/box_style.c:239` | `` |
| `is_ws` | function | `src/box_style.c:28` | `static int is_ws(char c)` |
| `name_cmp` | function | `src/box_style.c:48` | `static int name_cmp(const void *key, const void *elem)` |
| `strcmp` | function | `src/box_style.c:49` | `return strcmp((const char *)key, *(const char *const *)elem);` |
| `tag_row` | struct | `src/box_style.c:59` | `` |
| `take` | function | `src/box_style.c:293` | `* caller has to take (Sizing 3 section 5.1), so to a resolver that only sums a * px and a percentage half they read exac` |
| `BT_LEN_AUTO` | macro | `src/box_tree.c:31` | `#define BT_LEN_AUTO` |
| `BT_WRAP_EPS` | macro | `src/box_tree.c:61` | `#define BT_WRAP_EPS` |
| `assign_doc_order` | function | `src/box_tree.c:393` | `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,
                  ...` |
| `block` | function | `src/box_tree.c:512` | `* approximation of the true block (same flow neighbourhood), strictly
             * better than ...` |
| `bt_box_hidden` | function | `src/box_tree.c:658` | `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)` |
| `bt_layout` | function | `src/box_tree.c:352` | `bt_status bt_layout(bt_node *root, double avail_w)` |
| `bt_nn` | function | `src/box_tree.c:58` | `static double bt_nn(double v)` |
| `bt_oof_anchor` | function | `src/box_tree.c:650` | `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)` |
| `bt_oof_root` | function | `src/box_tree.c:654` | `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)` |
| `bt_resolve_positioning` | function | `src/box_tree.c:442` | `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,
                          ...` |
| `bt_resolve_positioning_ex` | function | `src/box_tree.c:453` | `bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,
                       ...` |
| `bx_lp_px` | function | `src/box_tree.c:431` | `return bx_lp_px(v, pct_pm, basis);` |
| `cx_sort` | function | `src/box_tree.c:619` | `cx_sort(order, tmp_count);` |
| `find_positioned_ancestor` | function | `src/box_tree.c:410` | `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,
                       ...` |
| `inset_unset` | function | `src/box_tree.c:439` | `static int inset_unset(int v, int pct_pm)` |
| `layout_block` | function | `src/box_tree.c:37` | `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,
                   ...` |
| `layout_flex` | function | `src/box_tree.c:344` | `case BX_DISPLAY_FLEX: return layout_flex(node, kids, nk, pl, pt, pb, cw, depth);` |
| `layout_grid` | function | `src/box_tree.c:201` | `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,
                    ...` |
| `layout_node` | function | `src/box_tree.c:307` | `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)` |
| `oof_walk` | function | `src/box_tree.c:634` | `static int oof_walk(const pv_box_def *boxes, size_t nbox, int bid, int nearest)` |
| `resolve_inset` | function | `src/box_tree.c:430` | `static double resolve_inset(int v, int pct_pm, double basis)` |
| `wrap_reverse` | function | `src/box_tree.c:78` | `*
 * wrap_reverse (node->wrap_reverse): when node->wrap is active and node->wrap_reverse
 * is no...` |
| `_POSIX_C_SOURCE` | macro | `src/browser.c:6` | `#define _POSIX_C_SOURCE` |
| `browser_add_exception` | function | `src/browser.c:431` | `browser_status browser_add_exception(browser_state *bs, const char *host)` |
| `browser_back` | function | `src/browser.c:227` | `browser_status browser_back(browser_state *bs)` |
| `browser_can_back` | function | `src/browser.c:251` | `int browser_can_back(const browser_state *bs)` |
| `browser_can_forward` | function | `src/browser.c:255` | `int browser_can_forward(const browser_state *bs)` |
| `browser_commit_url_bar` | function | `src/browser.c:187` | `browser_status browser_commit_url_bar(browser_state *bs)` |
| `browser_current_url` | function | `src/browser.c:259` | `const char *browser_current_url(const browser_state *bs)` |
| `browser_forward` | function | `src/browser.c:239` | `browser_status browser_forward(browser_state *bs)` |
| `browser_free` | function | `src/browser.c:164` | `void browser_free(browser_state *bs)` |
| `browser_init` | function | `src/browser.c:153` | `browser_status browser_init(browser_state *bs)` |
| `browser_is_exception` | function | `src/browser.c:423` | `int browser_is_exception(const browser_state *bs, const char *host)` |
| `browser_navigate` | function | `src/browser.c:192` | `browser_status browser_navigate(browser_state *bs, const char *url)` |
| `browser_set_page` | function | `src/browser.c:368` | `browser_status browser_set_page(browser_state *bs, const char *title,
                           ...` |
| `browser_set_status` | function | `src/browser.c:390` | `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)` |
| `browser_set_url_bar` | function | `src/browser.c:175` | `browser_status browser_set_url_bar(browser_state *bs, const char *url)` |
| `browser_status_text` | function | `src/browser.c:404` | `const char *browser_status_text(const browser_state *bs, uint64_t now_ms)` |
| `browser_url_bar_backspace` | function | `src/browser.c:300` | `browser_status browser_url_bar_backspace(browser_state *bs)` |
| `browser_url_bar_clear` | function | `src/browser.c:359` | `browser_status browser_url_bar_clear(browser_state *bs)` |
| `browser_url_bar_delete` | function | `src/browser.c:314` | `browser_status browser_url_bar_delete(browser_state *bs)` |
| `browser_url_bar_delete_selection` | function | `src/browser.c:275` | `int browser_url_bar_delete_selection(browser_state *bs)` |
| `browser_url_bar_extend_cursor` | function | `src/browser.c:335` | `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)` |
| `browser_url_bar_insert` | function | `src/browser.c:285` | `browser_status browser_url_bar_insert(browser_state *bs, char c)` |
| `browser_url_bar_move_cursor` | function | `src/browser.c:325` | `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)` |
| `browser_url_bar_select_all` | function | `src/browser.c:352` | `browser_status browser_url_bar_select_all(browser_state *bs)` |
| `browser_url_bar_selection` | function | `src/browser.c:264` | `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)` |
| `browser_url_bar_set_cursor` | function | `src/browser.c:344` | `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)` |
| `clear_status` | function | `src/browser.c:25` | `static void clear_status(browser_state *bs)` |
| `cp1252_to_ucs` | function | `src/browser.c:86` | `static unsigned int cp1252_to_ucs(unsigned char c)` |
| `free` | function | `src/browser.c:17` | `free(bs->page_title);` |
| `free_exceptions` | function | `src/browser.c:39` | `static void free_exceptions(browser_state *bs)` |
| `free_history` | function | `src/browser.c:29` | `static void free_history(browser_state *bs)` |
| `free_page` | function | `src/browser.c:14` | `static void free_page(browser_state *bs)` |
| `host_equal` | function | `src/browser.c:412` | `static int host_equal(const char *a, const char *b)` |
| `is_https_url` | function | `src/browser.c:48` | `static int is_https_url(const char *s)` |
| `is_local_path` | function | `src/browser.c:52` | `static int is_local_path(const char *s)` |
| `memcpy` | function | `src/browser.c:78` | `memcpy(d, s, n + 1);` |
| `memmove` | function | `src/browser.c:279` | `memmove(bs->url_bar + s, bs->url_bar + s + l, bs->url_bar_len - (s + l) + 1);` |
| `memset` | function | `src/browser.c:157` | `memset(bs, 0, sizeof *bs);` |
| `url_is_allowed` | function | `src/browser.c:57` | `static int url_is_allowed(const char *url)` |
| `utf8_encode` | function | `src/browser.c:100` | `static size_t utf8_encode(unsigned int cp, char *out)` |
| `xstrdup` | function | `src/browser.c:71` | `static char *xstrdup(const char *s)` |
| `cx_box_layer` | function | `src/compositor.c:33` | `cx_layer cx_box_layer(const cx_style *s)` |
| `cx_forms_stacking_context` | function | `src/compositor.c:15` | `int cx_forms_stacking_context(const cx_style *s)` |
| `cx_item_compare` | function | `src/compositor.c:53` | `int cx_item_compare(const cx_item *a, const cx_item *b)` |
| `cx_sort` | function | `src/compositor.c:70` | `void cx_sort(cx_item *items, size_t n)` |
| `eff_z` | function | `src/compositor.c:50` | `static int eff_z(const cx_item *it)` |
| `AUTO_REJECT` | macro | `src/css.c:1849` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css.c:1851` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css.c:1855` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css.c:1850` | `#define AUTO_VALUE` |
| `CSS_CALC_MAX_DEPTH` | macro | `src/css.c:1377` | `#define CSS_CALC_MAX_DEPTH` |
| `CSS_DECL_SLOTS_MIN` | macro | `src/css.c:58` | `#define CSS_DECL_SLOTS_MIN` |
| `CSS_GRAD_STOPS_MAX` | function | `src/css.c:617` | `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when
 * the gradient fai...` |
| `CSS_INIT_DECLS` | macro | `src/css.c:43` | `#define CSS_INIT_DECLS` |
| `CSS_INIT_RULES` | macro | `src/css.c:59` | `#define CSS_INIT_RULES` |
| `CSS_INIT_SELS` | macro | `src/css.c:42` | `#define CSS_INIT_SELS` |
| `CSS_INLINE_BG_URLS` | macro | `src/css.c:88` | `#define CSS_INLINE_BG_URLS` |
| `CSS_INLINE_DECLS` | macro | `src/css.c:61` | `#define CSS_INLINE_DECLS` |
| `CSS_INLINE_SPEC` | macro | `src/css.c:62` | `#define CSS_INLINE_SPEC` |
| `CSS_MATHFN_MAX_ARGS` | macro | `src/css.c:1381` | `#define CSS_MATHFN_MAX_ARGS` |
| `CSS_MAX_BG_URLS` | macro | `src/css.c:83` | `#define CSS_MAX_BG_URLS` |
| `CSS_MAX_CUSTOM_PROPS` | macro | `src/css.c:73` | `#define CSS_MAX_CUSTOM_PROPS` |
| `CSS_MAX_FONT_FACES` | macro | `src/css.c:322` | `#define CSS_MAX_FONT_FACES` |
| `CSS_MAX_KEYFRAMES` | macro | `src/css.c:84` | `#define CSS_MAX_KEYFRAMES` |
| `CSS_MAX_KEYFRAME_DECLS` | macro | `src/css.c:87` | `#define CSS_MAX_KEYFRAME_DECLS` |
| `CSS_MAX_KEYFRAME_STOPS` | macro | `src/css.c:86` | `#define CSS_MAX_KEYFRAME_STOPS` |
| `CSS_MEDIA_MAX_DEPTH` | macro | `src/css.c:5846` | `#define CSS_MEDIA_MAX_DEPTH` |
| `CSS_MEDIA_TOK` | macro | `src/css.c:5715` | `#define CSS_MEDIA_TOK` |
| `CSS_SELS_PER_GROUP` | macro | `src/css.c:60` | `#define CSS_SELS_PER_GROUP` |
| `CSS_VAR_MAX_DEPTH` | macro | `src/css.c:74` | `#define CSS_VAR_MAX_DEPTH` |
| `CSS_WIDE_PROBE_DECLS` | macro | `src/css.c:94` | `#define CSS_WIDE_PROBE_DECLS` |
| `LIST` | function | `src/css.c:4198` | `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose into ` |
| `NULL` | function | `src/css.c:7020` | `* Sheet can be NULL (inline style, no @keyframes). */
void css_resolve_anim_keyframes(css_style *...` |
| `accepts` | function | `src/css.c:1369` | `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further than` |
| `add_rule` | function | `src/css.c:5603` | `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,
                     siz...` |
| `apply_decl` | function | `src/css.c:6413` | `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...` |
| `at_is_media` | function | `src/css.c:5838` | `static int at_is_media(const char *s, size_t i, size_t n)` |
| `bg_alpha_of` | function | `src/css.c:401` | `static int bg_alpha_of(const char *v)` |
| `block_end` | function | `src/css.c:5704` | `static size_t block_end(const char *s, size_t open, size_t n)` |
| `blur` | function | `src/css.c:3273` | `* consumes ONLY blur(Npx);` |
| `calc_eval` | function | `src/css.c:1628` | `static int calc_eval(const char *v, size_t vlen, double *out_px)` |
| `calc_eval_em` | function | `src/css.c:1635` | `static int calc_eval_em(const char *v, size_t vlen, double *out_em)` |
| `calc_eval_full` | function | `src/css.c:1612` | `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,
           ...` |
| `calc_expr` | function | `src/css.c:1592` | `static int calc_expr(calc_parser *p, calc_val *out, int depth)` |
| `calc_match_fn` | function | `src/css.c:1406` | `static int calc_match_fn(calc_parser *p, const char *name)` |
| `calc_mathfn` | function | `src/css.c:1448` | `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` |
| `calc_parser` | struct | `src/css.c:1397` | `` |
| `calc_piecewise` | function | `src/css.c:1433` | `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)` |
| `calc_skip_ws` | function | `src/css.c:1398` | `static void calc_skip_ws(calc_parser *p)` |
| `calc_term` | function | `src/css.c:1569` | `static int calc_term(calc_parser *p, calc_val *out, int depth)` |
| `calc_unwrap` | function | `src/css.c:1643` | `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` |
| `calc_val` | struct | `src/css.c:1396` | `` |
| `caller` | function | `src/css.c:4862` | `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached a br` |
| `cl_ctx_initial` | function | `src/css.c:965` | `return cl_ctx_initial();` |
| `cl_number` | function | `src/css.c:340` | `return cl_number(s, out, endp);` |
| `collect_custom_decls` | function | `src/css.c:5902` | `collect_custom_decls(s, ds, de, tab, cap, ntab);` |
| `collect_custom_props_scoped` | function | `src/css.c:5856` | `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,
                ...` |
| `column` | function | `src/css.c:3622` | `* column (`flex: 1 1 0%`);` |
| `computed_font_size` | function | `src/css.c:6766` | `static double computed_font_size(const css_style *o, const css_element *el)` |
| `conic_prelude` | function | `src/css.c:544` | `static int conic_prelude(const char *seg, int *angle)` |
| `contiguous` | function | `src/css.c:112` | `* contiguous (dx,dy,color) so expand_shadow writes them as a group. */ P_FONTFAMILY, P_TEXTTRANSFORM, P_LETTERSPACING, P` |
| `copy_lower_trim` | function | `src/css.c:5749` | `static size_t copy_lower_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `copy_trim` | function | `src/css.c:3778` | `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `count_one_repeat` | function | `src/css.c:1243` | `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,
                      ...` |
| `count_tracks` | function | `src/css.c:1205` | `static int count_tracks(const char *s, size_t n)` |
| `csel_ci_eq` | function | `src/css.c:390` | `return csel_ci_eq(v, "initial") \|\| csel_ci_eq(v, "inherit") \|\| csel_ci_eq(v, "unset") \|\| csel_ci_eq(v, "revert") \` |
| `csel_lower_ch` | function | `src/css.c:405` | `csel_lower_ch(p[2]) == 'b' && csel_lower_ch(p[3]) == 'a' && p[4] == '(') \|\| (csel_lower_ch(p[0]) == 'h' && csel_lower_` |
| `css_computed_font_size` | function | `src/css.c:6768` | `return css_computed_font_size(o, (el != NULL) ? el->font_size : 0.0);` |
| `css_custom_prop` | struct | `src/css.c:272` | `` |
| `css_decl` | struct | `src/css.c:234` | `` |
| `css_font_face_at` | function | `src/css.c:7055` | `int css_font_face_at(const css_sheet *sheet, size_t i,
                     char *family, size_t ...` |
| `css_font_face_count` | function | `src/css.c:7051` | `size_t css_font_face_count(const css_sheet *sheet)` |
| `css_free` | function | `src/css.c:6399` | `void css_free(css_sheet *s)` |
| `css_keyframe_stop` | struct | `src/css.c:304` | `` |
| `css_parse` | function | `src/css.c:6315` | `css_status css_parse(const char *text, size_t len, css_sheet **out)` |
| `css_parse_inline` | function | `src/css.c:7065` | `css_style css_parse_inline(const char *style, size_t len)` |
| `css_parse_logged` | function | `src/css.c:6329` | `css_status css_parse_logged(const char *text, size_t len, const css_media *media,
               ...` |
| `css_parse_media` | function | `src/css.c:6319` | `css_status css_parse_media(const char *text, size_t len, const css_media *media,
                ...` |
| `css_parse_scoped` | function | `src/css.c:6324` | `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,
               ...` |
| `css_resolve` | function | `src/css.c:6995` | `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                  ...` |
| `css_resolve_anim_keyframes` | function | `src/css.c:6991` | `css_resolve_anim_keyframes(&out, sheet);` |
| `css_resolve_el` | function | `src/css.c:6815` | `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         ...` |
| `css_rule` | struct | `src/css.c:280` | `` |
| `css_sheet` | struct | `src/css.c:282` | `` |
| `declaration` | function | `src/css.c:870` | `* declaration (fail closed);` |
| `declared` | function | `src/css.c:5557` | `* the referenced custom property was never declared (or the fallback * chain bottomed out), so the declaration is invali` |
| `downstream` | function | `src/css.c:811` | `* happens downstream (render_doc.c), gated by caps.images like an <img>. */
static int expand_bg_...` |
| `drop_copy_text` | function | `src/css.c:5488` | `static void drop_copy_text(char *dst, size_t cap, const char *src)` |
| `drop_record` | function | `src/css.c:5507` | `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)` |
| `emit_content` | function | `src/css.c:3408` | `static int emit_content(css_decl *dst, int cap, const char *str,
                        char (*c...` |
| `emit_gradient` | function | `src/css.c:709` | `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,
                         ...` |
| `emit_len` | function | `src/css.c:2906` | `return emit_len(dst, cap, slot, tok, 0, 0);` |
| `emit_radius_corner` | function | `src/css.c:2902` | `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)` |
| `emit_spacing` | function | `src/css.c:2330` | `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `expand_backdrop_filter` | function | `src/css.c:3276` | `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)` |
| `expand_background` | function | `src/css.c:872` | `static int expand_background(const char *val, css_decl *dst, int cap,
                           ...` |
| `expand_bg_position` | function | `src/css.c:3309` | `static int expand_bg_position(const char *val, css_decl *dst, int cap)` |
| `expand_bg_size` | function | `src/css.c:3369` | `static int expand_bg_size(const char *val, css_decl *dst, int cap)` |
| `expand_box2` | function | `src/css.c:2019` | `static int expand_box2(const char *val, int slot_start, int slot_end,
                       int ...` |
| `expand_box4` | function | `src/css.c:2897` | `return expand_box4(horiz, P_BORDER_RADIUS, 0, 0, dst, cap);` |
| `expand_box_shadow` | function | `src/css.c:3571` | `static int expand_box_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_column_rule` | function | `src/css.c:3072` | `static int expand_column_rule(const char *val, css_decl *dst, int cap)` |
| `expand_columns` | function | `src/css.c:3016` | `static int expand_columns(const char *val, css_decl *dst, int cap)` |
| `expand_content` | function | `src/css.c:3421` | `static int expand_content(const char *val, css_decl *dst, int cap,
                          char...` |
| `expand_flex` | function | `src/css.c:3643` | `static int expand_flex(const char *val, css_decl *dst, int cap)` |
| `expand_flex_flow` | function | `src/css.c:3050` | `static int expand_flex_flow(const char *val, css_decl *dst, int cap)` |
| `expand_gap` | function | `src/css.c:4706` | `static int expand_gap(const char *val, css_decl *dst, int cap)` |
| `expand_grid_areas` | function | `src/css.c:3453` | `static int expand_grid_areas(const char *val, css_decl *dst, int cap,
                           ...` |
| `expand_grid_template` | function | `src/css.c:3520` | `static int expand_grid_template(const char *val, css_decl *dst, int cap,
                        ...` |
| `expand_grid_template_cols` | function | `src/css.c:1347` | `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `expand_outline` | function | `src/css.c:2976` | `static int expand_outline(const char *val, css_decl *dst, int cap)` |
| `expand_shadow` | function | `src/css.c:2344` | `static int expand_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_transform_list` | function | `src/css.c:4454` | `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);` |
| `expand_transform_origin` | function | `src/css.c:4674` | `static int expand_transform_origin(const char *val, css_decl *dst, int cap)` |
| `expand_valign` | function | `src/css.c:2153` | `static int expand_valign(const char *val, css_decl *dst, int cap)` |
| `family_of` | function | `src/css.c:2049` | `static int family_of(const char *name)` |
| `filter_paren_body` | function | `src/css.c:3113` | `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)` |
| `find_gradient_call` | function | `src/css.c:510` | `static int find_gradient_call(const char *v, const char *fn, size_t *start,
                     ...` |
| `find_radial_gradient` | function | `src/css.c:766` | `static int find_radial_gradient(const char *v, size_t *start, size_t *end,
                      ...` |
| `fold_font_relative` | function | `src/css.c:6787` | `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,
                         ...` |
| `free` | function | `src/css.c:6391` | `free(rebased);` |
| `function` | function | `src/css.c:3240` | `* function (the rest of the list still applies). Emits the whole * 4-decl group in lock-step or nothing. */ const char *` |
| `grad_stop_pos` | function | `src/css.c:586` | `static int grad_stop_pos(const char *pp, int conic, const char **endp)` |
| `gradient` | function | `src/css.c:461` | `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,
 * the whole decl...` |
| `grammar` | function | `src/css.c:4892` | `* grammar (`justify`/`distribute`) is not `justify-content`'s. Guessing
     * there would be inv...` |
| `here` | function | `src/css.c:69` | `* A value is capped at CSS_TOK_MAX like every other token here (an overlong one * could never fit a re-substituted decla` |
| `ignored` | function | `src/css.c:4725` | `* engine slot and is ignored (documented simplification, like list-style's
 * ignored tokens). An...` |
| `int` | function | `src/css.c:2913` | `typedef int (*tok_interp)(const char *tok, int *out);` |
| `interp_accent_color` | function | `src/css.c:2704` | `static int interp_accent_color(const char *v)` |
| `interp_align` | function | `src/css.c:975` | `static int interp_align(const char *v)` |
| `interp_align_kw` | function | `src/css.c:3688` | `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` |
| `interp_appearance` | function | `src/css.c:2576` | `static int interp_appearance(const char *v)` |
| `interp_aspect_ratio` | function | `src/css.c:2225` | `static int interp_aspect_ratio(const char *v, int *num, int *den)` |
| `interp_backface_visibility` | function | `src/css.c:2811` | `static int interp_backface_visibility(const char *v)` |
| `interp_bc_tok` | function | `src/css.c:2912` | `static int interp_bc_tok(const char *t, int *o)` |
| `interp_bg` | function | `src/css.c:429` | `static int interp_bg(const char *v)` |
| `interp_bg_attachment` | function | `src/css.c:2638` | `static int interp_bg_attachment(const char *v)` |
| `interp_bg_clip` | function | `src/css.c:2623` | `static int interp_bg_clip(const char *v)` |
| `interp_bg_origin` | function | `src/css.c:2631` | `static int interp_bg_origin(const char *v)` |
| `interp_bg_repeat` | function | `src/css.c:2606` | `static int interp_bg_repeat(const char *v)` |
| `interp_bg_size` | function | `src/css.c:2616` | `static int interp_bg_size(const char *v)` |
| `interp_border_collapse` | function | `src/css.c:2484` | `static int interp_border_collapse(const char *v)` |
| `interp_border_style` | function | `src/css.c:2833` | `static int interp_border_style(const char *v)` |
| `interp_box_orient` | function | `src/css.c:3719` | `static int interp_box_orient(const char *v)` |
| `interp_boxsizing` | function | `src/css.c:2383` | `static int interp_boxsizing(const char *v)` |
| `interp_bs_tok` | function | `src/css.c:2911` | `static int interp_bs_tok(const char *t, int *o)` |
| `interp_bw_tok` | function | `src/css.c:2910` | `static int interp_bw_tok(const char *t, int *o)` |
| `interp_bwidth1` | function | `src/css.c:2859` | `static int interp_bwidth1(const char *v)` |
| `interp_caption_side` | function | `src/css.c:2525` | `static int interp_caption_side(const char *v)` |
| `interp_caret_color` | function | `src/css.c:2564` | `static int interp_caret_color(const char *v)` |
| `interp_clear` | function | `src/css.c:2396` | `static int interp_clear(const char *v)` |
| `interp_color` | function | `src/css.c:364` | `static int interp_color(const char *v)` |
| `interp_color_scheme` | function | `src/css.c:2686` | `static int interp_color_scheme(const char *v)` |
| `interp_column_count` | function | `src/css.c:2993` | `static int interp_column_count(const char *v)` |
| `interp_column_width` | function | `src/css.c:3005` | `static int interp_column_width(const char *v)` |
| `interp_contain` | function | `src/css.c:2651` | `static int interp_contain(const char *v)` |
| `interp_content_visibility` | function | `src/css.c:2672` | `static int interp_content_visibility(const char *v)` |
| `interp_cursor` | function | `src/css.c:2445` | `static int interp_cursor(const char *v)` |
| `interp_direction` | function | `src/css.c:2258` | `static int interp_direction(const char *v)` |
| `interp_display` | function | `src/css.c:1097` | `static int interp_display(const char *v)` |
| `interp_empty_cells` | function | `src/css.c:2518` | `static int interp_empty_cells(const char *v)` |
| `interp_filter_deg` | function | `src/css.c:3098` | `static int interp_filter_deg(const char *s)` |
| `interp_filter_pct` | function | `src/css.c:3084` | `static int interp_filter_pct(const char *s)` |
| `interp_flex_basis` | function | `src/css.c:3609` | `static int interp_flex_basis(const char *v, int *out)` |
| `interp_flex_direction` | function | `src/css.c:3700` | `static int interp_flex_direction(const char *v)` |
| `interp_flex_factor` | function | `src/css.c:3599` | `static int interp_flex_factor(const char *v)` |
| `interp_flex_wrap` | function | `src/css.c:3724` | `static int interp_flex_wrap(const char *v)` |
| `interp_float` | function | `src/css.c:2389` | `static int interp_float(const char *v)` |
| `interp_font_kerning` | function | `src/css.c:2755` | `static int interp_font_kerning(const char *v)` |
| `interp_font_stretch` | function | `src/css.c:2770` | `static int interp_font_stretch(const char *v)` |
| `interp_font_variant` | function | `src/css.c:2539` | `static int interp_font_variant(const char *v)` |
| `interp_fontfamily` | function | `src/css.c:2078` | `static int interp_fontfamily(const char *v)` |
| `interp_forced_color_adjust` | function | `src/css.c:2715` | `static int interp_forced_color_adjust(const char *v)` |
| `interp_gap` | function | `src/css.c:1173` | `static int interp_gap(const char *v)` |
| `interp_grid_flow` | function | `src/css.c:3733` | `static int interp_grid_flow(const char *v)` |
| `interp_grid_span` | function | `src/css.c:3759` | `static int interp_grid_span(const char *v)` |
| `interp_hyphens` | function | `src/css.c:2547` | `static int interp_hyphens(const char *v)` |
| `interp_image_rendering` | function | `src/css.c:2679` | `static int interp_image_rendering(const char *v)` |
| `interp_isolation` | function | `src/css.c:2645` | `static int interp_isolation(const char *v)` |
| `interp_justify` | function | `src/css.c:1179` | `static int interp_justify(const char *v)` |
| `interp_len` | function | `src/css.c:1661` | `static int interp_len(const char *v, int allow_auto, int *out)` |
| `interp_len` | function | `src/css.c:1952` | `* this file that might hand a token to interp_len (transitively: margin/padding/
 * inset, flex-b...` |
| `interp_lineheight` | function | `src/css.c:1038` | `static int interp_lineheight(const char *v)` |
| `interp_list_style_pos` | function | `src/css.c:2749` | `static int interp_list_style_pos(const char *v)` |
| `interp_liststyle` | function | `src/css.c:2296` | `static int interp_liststyle(const char *v)` |
| `interp_lp` | function | `src/css.c:1775` | `static int interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_...` |
| `interp_mix_blend_mode` | function | `src/css.c:2722` | `static int interp_mix_blend_mode(const char *v)` |
| `interp_object_fit` | function | `src/css.c:2740` | `static int interp_object_fit(const char *v)` |
| `interp_overflow` | function | `src/css.c:2413` | `static int interp_overflow(const char *v)` |
| `interp_overflow_wrap` | function | `src/css.c:2475` | `static int interp_overflow_wrap(const char *v)` |
| `interp_overscroll_behavior` | function | `src/css.c:2804` | `static int interp_overscroll_behavior(const char *v)` |
| `interp_pointer_events` | function | `src/css.c:2594` | `static int interp_pointer_events(const char *v)` |
| `interp_position` | function | `src/css.c:2374` | `static int interp_position(const char *v)` |
| `interp_print_color_adjust` | function | `src/css.c:2709` | `static int interp_print_color_adjust(const char *v)` |
| `interp_resize` | function | `src/css.c:2783` | `static int interp_resize(const char *v)` |
| `interp_scroll_behavior` | function | `src/css.c:2791` | `static int interp_scroll_behavior(const char *v)` |
| `interp_style` | function | `src/css.c:1067` | `static int interp_style(const char *v)` |
| `interp_table_layout` | function | `src/css.c:2532` | `static int interp_table_layout(const char *v)` |
| `interp_tabsize` | function | `src/css.c:2191` | `static int interp_tabsize(const char *v)` |
| `interp_text_overflow` | function | `src/css.c:2461` | `static int interp_text_overflow(const char *v)` |
| `interp_text_rendering` | function | `src/css.c:2762` | `static int interp_text_rendering(const char *v)` |
| `interp_textdeco` | function | `src/css.c:1078` | `static int interp_textdeco(const char *v)` |
| `interp_textdeco_style` | function | `src/css.c:2202` | `static int interp_textdeco_style(const char *v)` |
| `interp_textdeco_thickness` | function | `src/css.c:2213` | `static int interp_textdeco_thickness(const char *v)` |
| `interp_texttransform` | function | `src/css.c:2099` | `static int interp_texttransform(const char *v)` |
| `interp_time_ms` | function | `src/css.c:2869` | `static int interp_time_ms(const char *v)` |
| `interp_touch_action` | function | `src/css.c:2797` | `static int interp_touch_action(const char *v)` |
| `interp_transition_property` | function | `src/css.c:2170` | `static int interp_transition_property(const char *v)` |
| `interp_user_select` | function | `src/css.c:2555` | `static int interp_user_select(const char *v)` |
| `interp_valign` | function | `src/css.c:2121` | `static int interp_valign(const char *v)` |
| `interp_visibility` | function | `src/css.c:2406` | `static int interp_visibility(const char *v)` |
| `interp_weight` | function | `src/css.c:1058` | `static int interp_weight(const char *v)` |
| `interp_whitespace` | function | `src/css.c:2177` | `static int interp_whitespace(const char *v)` |
| `interp_word_break` | function | `src/css.c:2467` | `static int interp_word_break(const char *v)` |
| `interpret_decls` | function | `src/css.c:5585` | `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,
               ...` |
| `interpret_prop` | function | `src/css.c:5461` | `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,
            ...` |
| `interpret_prop_dispatch` | function | `src/css.c:4873` | `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,
   ...` |
| `length_px` | function | `src/css.c:971` | `static int length_px(const char *v, double *px)` |
| `liststyle_kw` | function | `src/css.c:2263` | `static int liststyle_kw(const char *t)` |
| `liststyle_unknown_name` | function | `src/css.c:2285` | `static int liststyle_unknown_name(const char *t)` |
| `matrix` | function | `src/css.c:4112` | `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands on ` |
| `media_matches` | function | `src/css.c:5824` | `static int media_matches(const char *s, size_t a, size_t b, const css_media *m)` |
| `media_part_matches` | function | `src/css.c:5758` | `static int media_part_matches(const char *p, const css_media *m)` |
| `media_segment_matches` | function | `src/css.c:5787` | `static int media_segment_matches(const char *s, size_t a, size_t b, const css_media *m)` |
| `memcpy` | function | `src/css.c:639` | `memcpy(seg, s + a, len);` |
| `memmove` | function | `src/css.c:5744` | `memmove(s, s + a, n + 1);` |
| `memset` | function | `src/css.c:5437` | `memset(tmp, 0, sizeof tmp);` |
| `min` | function | `src/css.c:1467` | `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the element to` |
| `name` | type_alias | `src/css.c:272` | `typedef struct css_custom_prop { char name[CSS_TOK_MAX];` |
| `number` | function | `src/css.c:2493` | `* number (no unit) as px (common in shorthand context like "10 5"). */
static int interp_border_s...` |
| `order` | function | `src/css.c:3238` | `* Lengths in declaration order (dx, dy, optional blur >= 0);` |
| `origin_component` | function | `src/css.c:4648` | `static int origin_component(const char *tok, int axis, int *out)` |
| `overflowed` | function | `src/css.c:4027` | `* overflowed (caller drops the declaration). */
static int resolve_var(const char *val, char *out...` |
| `page_view` | function | `src/css.c:6419` | `* the generated text reaches page_view (which materialises it as a synthetic * run);` |
| `parent` | function | `src/css.c:6448` | `* property from the parent (`inherit`), and an unset non-inherited one
         * stands at its i...` |
| `parse_angle_deg` | function | `src/css.c:4451` | `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);` |
| `parse_block` | function | `src/css.c:5912` | `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                 ...` |
| `parse_color` | function | `src/css.c:356` | `static int parse_color(const char *v)` |
| `parse_matrix6` | function | `src/css.c:4143` | `static int parse_matrix6(const char *p, size_t argn, double m6[6])` |
| `parse_num` | function | `src/css.c:335` | `static int parse_num(const char *s, double *out, const char **endp)` |
| `pct_slot_of` | function | `src/css.c:1706` | `static int pct_slot_of(int slot)` |
| `pool` | function | `src/css.c:807` | `* pool (gradient explicitly reset);` |
| `prop` | type_alias | `src/css.c:233` | `typedef struct css_decl { int prop;` |
| `property` | function | `src/css.c:4760` | `* error drops the whole property (fail closed). */
static int expand_clip(const char *val, css_de...` |
| `px` | type_alias | `src/css.c:1396` | `typedef struct calc_val { double px;` |
| `rem_emit_px` | function | `src/css.c:6136` | `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)` |
| `rem_ident_ch` | function | `src/css.c:6118` | `static int rem_ident_ch(char c)` |
| `rem_num_starts_after` | function | `src/css.c:6126` | `static int rem_num_starts_after(char prev)` |
| `rem_rebase` | function | `src/css.c:6166` | `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)` |
| `repeat` | function | `src/css.c:1194` | `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill\|...) / repeat(auto-fit\` |
| `resolve_var_rec` | function | `src/css.c:3935` | `static int resolve_var_rec(const char *val, size_t vlen, char *out, size_t outcap, size_t *o, const css_custom_prop *tab` |
| `round_clamp` | function | `src/css.c:347` | `static int round_clamp(double v, int lo, int hi)` |
| `scope_has_class` | function | `src/css.c:3871` | `static int scope_has_class(const char *list, const char *name, size_t len)` |
| `sheet_reparse` | function | `src/css.c:6381` | `sheet_reparse(sh, rebased, rlen, m, root_scope, log);` |
| `sheet_rewind` | function | `src/css.c:6233` | `static void sheet_rewind(css_sheet *sh)` |
| `sheet_root_font_px` | function | `src/css.c:6273` | `static double sheet_root_font_px(const css_sheet *sh)` |
| `shorthand` | function | `src/css.c:4803` | `* generic bucket keeps the rest of the shorthand (same net effect as the
 * font-family longhand ...` |
| `side` | function | `src/css.c:92` | `* and a percentage slot per side (8), grid-template-columns emits one slot per * track plus the count (9), and matrix() ` |
| `skip_at_rule` | function | `src/css.c:5688` | `static size_t skip_at_rule(const char *s, size_t i, size_t n)` |
| `slots` | function | `src/css.c:4984` | `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return emit_len(dst, ` |
| `snprintf` | function | `src/css.c:7061` | `snprintf(family, fam_cap, "%s", sheet->font_faces[i].family);` |
| `split_top_args` | function | `src/css.c:4175` | `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,
               ...` |
| `starts_with_ci` | function | `src/css.c:1204` | `static int starts_with_ci(const char *s, const char *pre);` |
| `strcpy` | function | `src/css.c:3858` | `strcpy(tab[slot].value, valbuf);` |
| `strip_comments` | function | `src/css.c:6281` | `static char *strip_comments(const char *text, size_t len, size_t *outlen)` |
| `strip_important` | function | `src/css.c:3791` | `static int strip_important(char *val)` |
| `stylesheet` | function | `src/css.c:6949` | `* the stylesheet (e.g. a `:root` rule). Inline-declared names win on a * collision (closer to the use site), so they go ` |
| `term` | function | `src/css.c:1783` | `* the same expression and failed closed on the percentage term (its property * may not accept one);` |
| `text` | function | `src/css.c:957` | `* source text (rem_rebase, see below) rather than by threading a context here.
 *
 * Viewport uni...` |
| `through` | function | `src/css.c:381` | `* at the two SHARED chokepoints every property funnels through (the generic
 * dispatch tail, and...` |
| `tr_decompose` | function | `src/css.c:4120` | `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,
                        in...` |
| `tr_mul` | function | `src/css.c:4100` | `static void tr_mul(double out[6], const double l[6], const double r[6])` |
| `track_size_of` | function | `src/css.c:1214` | `static int track_size_of(const char *tok)` |
| `translate3d` | function | `src/css.c:4205` | `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine
 * renders z as nothing,...` |
| `translate3d` | function | `src/css.c:4455` | `* translate3d()/translateZ() flatten to their 2D projection. Any other
 * transform function (per...` |
| `translateX` | function | `src/css.c:4447` | `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc numbers ` |
| `trim_inplace` | function | `src/css.c:5740` | `static void trim_inplace(char *s)` |
| `value` | function | `src/css.c:3967` | `* any other unsupported value (fail closed, never a partially-substituted value). */
static int r...` |
| `value_em_milli` | function | `src/css.c:1756` | `static int value_em_milli(const char *v)` |
| `var` | function | `src/css.c:6291` | `* collected and forty var() declarations -- font sizes, widths, radii, the
     * whole theme -- ...` |
| `var_append` | function | `src/css.c:3940` | `static int var_append(char *out, size_t outcap, size_t *o, const char *s, size_t n)` |
| `walk_tracks` | function | `src/css.c:1286` | `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)` |
| `wide_claim` | function | `src/css.c:5421` | `static int wide_claim(const char *prop, css_decl *dst, int cap,
                      char (*urlt...` |
| `CCH_ATTR_BUF` | macro | `src/css_chain.c:19` | `#define CCH_ATTR_BUF` |
| `CCH_CLASS_BUF` | macro | `src/css_chain.c:16` | `#define CCH_CLASS_BUF` |
| `CCH_ID_MAX` | macro | `src/css_chain.c:15` | `#define CCH_ID_MAX` |
| `CCH_MAX_ATTRS` | macro | `src/css_chain.c:18` | `#define CCH_MAX_ATTRS` |
| `CCH_MAX_CLASSES` | macro | `src/css_chain.c:17` | `#define CCH_MAX_CLASSES` |
| `CCH_TAG_MAX` | macro | `src/css_chain.c:14` | `#define CCH_TAG_MAX` |
| `cch_element_matches` | function | `src/css_chain.c:266` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)` |
| `cch_element_style` | function | `src/css_chain.c:262` | `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)` |
| `cch_element_style_fs` | function | `src/css_chain.c:264` | `return cch_element_style_fs(el, sheet, 0.0);` |
| `cch_node` | struct | `src/css_chain.c:23` | `` |
| `count_children` | function | `src/css_chain.c:179` | `static int count_children(lxb_dom_node_t *n)` |
| `css_resolve_el` | function | `src/css_chain.c:259` | `return css_resolve_el(sheet, subject, (const char *)st, sl);` |
| `fill_css_node` | function | `src/css_chain.c:35` | `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)` |
| `inputs` | function | `src/css_chain.c:193` | `* identical inputs (single source of truth). */
static const css_element *build_chain(lxb_dom_ele...` |
| `lxb_dom_element_get_attribute` | function | `src/css_chain.c:58` | `lxb_dom_element_get_attribute(e, (const lxb_char_t *)"id", 2, &il);` |
| `memcpy` | function | `src/css_chain.c:60` | `memcpy(node->idbuf, idv, il);` |
| `sibling_position` | function | `src/css_chain.c:133` | `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `sibling_type_position` | function | `src/css_chain.c:151` | `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `tag` | type_alias | `src/css_chain.c:23` | `typedef struct cch_node { char tag[CCH_TAG_MAX];` |
| `CC_CHANNEL_MAX` | macro | `src/css_color.c:21` | `#define CC_CHANNEL_MAX` |
| `CC_HSL_SCALE` | macro | `src/css_color.c:30` | `#define CC_HSL_SCALE` |
| `CC_NUMBER_MAX_DIGITS` | macro | `src/css_color.c:27` | `#define CC_NUMBER_MAX_DIGITS` |
| `CC_PERCENT_MAX` | macro | `src/css_color.c:22` | `#define CC_PERCENT_MAX` |
| `CC_TOKEN_MAX` | macro | `src/css_color.c:18` | `#define CC_TOKEN_MAX` |
| `ascii_lower` | function | `src/css_color.c:116` | `static int ascii_lower(int c)` |
| `cc_named` | struct | `src/css_color.c:32` | `` |
| `cc_pack` | function | `src/css_color.c:434` | `int cc_pack(cc_rgb c)` |
| `cc_parse` | function | `src/css_color.c:403` | `cc_status cc_parse(const char *token, cc_rgb *out)` |
| `cc_round` | function | `src/css_color.c:210` | `static long cc_round(double v)` |
| `cc_unpack` | function | `src/css_color.c:438` | `cc_rgb cc_unpack(int packed)` |
| `hex_val` | function | `src/css_color.c:120` | `static int hex_val(int c)` |
| `hsl_to_rgb` | function | `src/css_color.c:361` | `hsl_to_rgb(comps[0], comps[1], comps[2], &out->r, &out->g, &out->b);` |
| `named_cmp` | function | `src/css_color.c:387` | `static int named_cmp(const void *key, const void *element)` |
| `normalize` | function | `src/css_color.c:130` | `static int normalize(const char *token, char *out)` |
| `parse_component` | function | `src/css_color.c:215` | `static int parse_component(const char *b, const char *e, int is_alpha, int *out)` |
| `parse_func` | function | `src/css_color.c:318` | `static int parse_func(const char *s, cc_rgb *out)` |
| `parse_hex` | function | `src/css_color.c:144` | `static int parse_hex(const char *s, cc_rgb *out)` |
| `parse_hsl_comp` | function | `src/css_color.c:248` | `static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out)` |
| `parse_named` | function | `src/css_color.c:393` | `static int parse_named(const char *s, cc_rgb *out)` |
| `strcmp` | function | `src/css_color.c:391` | `return strcmp(k, n->name);` |
| `CL_PX_PER_IN` | macro | `src/css_length.c:21` | `#define CL_PX_PER_IN` |
| `cl_ctx_initial` | function | `src/css_length.c:99` | `cl_ctx cl_ctx_initial(void)` |
| `cl_em_refit` | function | `src/css_length.c:218` | `double cl_em_refit(double px, double em, double from_font_size, double font_size)` |
| `cl_font_size` | function | `src/css_length.c:56` | `static double cl_font_size(const cl_ctx *ctx)` |
| `cl_is_length_unit` | function | `src/css_length.c:166` | `int cl_is_length_unit(const char *unit, size_t unit_len)` |
| `cl_lp_used` | function | `src/css_length.c:394` | `double cl_lp_used(cl_lp lp, double basis)` |
| `cl_metric_or` | function | `src/css_length.c:67` | `static double cl_metric_or(double measured, double ratio, const cl_ctx *ctx)` |
| `cl_number` | function | `src/css_length.c:291` | `int cl_number(const char *s, double *out, const char **endp)` |
| `cl_parse_number` | function | `src/css_length.c:233` | `static int cl_parse_number(const char **pp, const char *end, double *out)` |
| `cl_resolve` | function | `src/css_length.c:376` | `cl_status cl_resolve(const char *value, const cl_ctx *ctx, double *out_px)` |
| `cl_resolve_core` | function | `src/css_length.c:309` | `static cl_status cl_resolve_core(const char *value, const cl_ctx *ctx, cl_lp *out)` |
| `cl_resolve_lp` | function | `src/css_length.c:390` | `cl_status cl_resolve_lp(const char *value, const cl_ctx *ctx, cl_lp *out)` |
| `cl_root_font_size` | function | `src/css_length.c:59` | `static double cl_root_font_size(const cl_ctx *ctx)` |
| `cl_unit_eq` | function | `src/css_length.c:30` | `static int cl_unit_eq(const char *unit, size_t len, const char *lit)` |
| `cl_unit_is_font_relative` | function | `src/css_length.c:173` | `int cl_unit_is_font_relative(const char *unit, size_t unit_len)` |
| `cl_unit_scale` | function | `src/css_length.c:116` | `cl_status cl_unit_scale(const char *unit, size_t unit_len,
                        const cl_ctx *...` |
| `cl_viewport_scale` | function | `src/css_length.c:80` | `static int cl_viewport_scale(const char *u, size_t len, const cl_ctx *ctx, double *per)` |
| `know` | function | `src/css_length.c:7` | `* this module cannot know (real font metrics, the viewport) arrives through
 * cl_ctx rather than...` |
| `HAS_MAX_DEPTH` | macro | `src/css_select.c:646` | `#define HAS_MAX_DEPTH` |
| `attr_matches` | function | `src/css_select.c:507` | `static int attr_matches(const css_attr_match *am, const css_element *el)` |
| `between` | function | `src/css_select.c:206` | `* between ( and ) is split on commas (not inside [] or ());` |
| `built` | function | `src/css_select.c:820` | `* chains the caller built (an element without parent/prev links never matches
 * through that com...` |
| `compound_matches` | function | `src/css_select.c:787` | `static int compound_matches(const css_compound *c, const css_element *el,
                       ...` |
| `csel_ci_eq` | function | `src/css_select.c:538` | `return csel_ci_eq(tag, "input") \|\| csel_ci_eq(tag, "button") \|\| csel_ci_eq(tag, "select") \|\| csel_ci_eq(tag, "text` |
| `csel_matches` | function | `src/css_select.c:860` | `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,
              ...` |
| `csel_span_eq` | function | `src/css_select.c:487` | `return csel_span_eq(v + vl - fl, suf, fl, ci);` |
| `csel_substr` | function | `src/css_select.c:520` | `case ATTR_STAR: return csel_substr(v, am->value, am->ci);` |
| `el_attr_value` | function | `src/css_select.c:474` | `static const char *el_attr_value(const css_element *el, const char *name)` |
| `ends_with` | function | `src/css_select.c:484` | `static int ends_with(const char *v, const char *suf, int ci)` |
| `has_word` | function | `src/css_select.c:492` | `static int has_word(const char *v, const char *w, int ci)` |
| `is_form_control` | function | `src/css_select.c:536` | `static int is_form_control(const char *tag)` |
| `memset` | function | `src/css_select.c:21` | `memset(am, 0, sizeof *am);` |
| `nth_matches` | function | `src/css_select.c:527` | `static int nth_matches(int A, int B, int idx)` |
| `parse_attr_sel` | function | `src/css_select.c:19` | `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)` |
| `parse_compound` | function | `src/css_select.c:321` | `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,
                  ...` |
| `parse_nth_arg` | function | `src/css_select.c:76` | `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)` |
| `parse_sub_compound` | function | `src/css_select.c:270` | `static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub)` |
| `selector` | function | `src/css_select.c:380` | `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is
 * dropped. Whitespa...` |
| `strlen` | function | `src/css_select.c:714` | `strlen(sub->attrs[ai].name), &avl);` |
| `sub_sel_matches` | function | `src/css_select.c:545` | `static int sub_sel_matches(const css_sub_sel *sub, const css_element *el)` |
| `b64_val` | function | `src/data_url.c:61` | `static int b64_val(unsigned char c)` |
| `ci_starts_with` | function | `src/data_url.c:19` | `static int ci_starts_with(const char *s, const char *prefix)` |
| `du_base64_decode` | function | `src/data_url.c:69` | `du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len)` |
| `du_base64_payload` | function | `src/data_url.c:31` | `du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len)` |
| `du_is_data_url` | function | `src/data_url.c:27` | `int du_is_data_url(const char *url)` |
| `lower` | function | `src/data_url.c:15` | `static int lower(char c)` |
| `_POSIX_C_SOURCE` | macro | `src/disk_store.c:10` | `#define _POSIX_C_SOURCE` |
| `close` | function | `src/disk_store.c:117` | `close(fd);` |
| `ds_free` | function | `src/disk_store.c:135` | `void ds_free(uint8_t *buf, size_t len)` |
| `ds_read` | function | `src/disk_store.c:102` | `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],
                  uint8_t **ou...` |
| `ds_write` | function | `src/disk_store.c:65` | `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,
               ...` |
| `free` | function | `src/disk_store.c:47` | `free(dup);` |
| `fsync_dir` | function | `src/disk_store.c:32` | `static void fsync_dir(const char *path)` |
| `ls_free` | function | `src/disk_store.c:99` | `ls_free(blob, blob_len);` |
| `map_ls` | function | `src/disk_store.c:49` | `static ds_status map_ls(ls_status s)` |
| `memcpy` | function | `src/disk_store.c:81` | `memcpy(tmp, path, plen);` |
| `DOM_QS_MAX_SELECTORS` | macro | `src/dom.c:373` | `#define DOM_QS_MAX_SELECTORS` |
| `IH_BLOCK_SIZE` | macro | `src/dom.c:801` | `#define IH_BLOCK_SIZE` |
| `_POSIX_C_SOURCE` | macro | `src/dom.c:10` | `#define _POSIX_C_SOURCE` |
| `copy_ids` | function | `src/dom.c:346` | `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)` |
| `count` | function | `src/dom.c:430` | `* count (may exceed cap), and returns DOM_NODE_NONE. */
static dom_node_id qs_walk(const dom_inde...` |
| `dom_append_child` | function | `src/dom.c:692` | `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)` |
| `dom_attribute_names` | function | `src/dom.c:578` | `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,
                           con...` |
| `dom_build` | function | `src/dom.c:283` | `dom_status dom_build(const hp_document *doc, dom_index **out)` |
| `dom_closest` | function | `src/dom.c:488` | `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,
                        const cha...` |
| `dom_create_element` | function | `src/dom.c:672` | `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)` |
| `dom_document_position` | function | `src/dom.c:504` | `size_t dom_document_position(const dom_index *idx, dom_node_id node)` |
| `dom_document_title` | function | `src/dom.c:606` | `const char *dom_document_title(const dom_index *idx, size_t *len)` |
| `dom_first_child` | function | `src/dom.c:529` | `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)` |
| `dom_free` | function | `src/dom.c:324` | `void dom_free(dom_index *idx)` |
| `dom_get_attribute` | function | `src/dom.c:556` | `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,
                           ...` |
| `dom_get_by_class` | function | `src/dom.c:362` | `size_t dom_get_by_class(const dom_index *idx, const char *cls,
                        dom_node_i...` |
| `dom_get_by_tag` | function | `src/dom.c:353` | `size_t dom_get_by_tag(const dom_index *idx, const char *tag,
                      dom_node_id *o...` |
| `dom_get_element_by_id` | function | `src/dom.c:340` | `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)` |
| `dom_get_inner_html` | function | `src/dom.c:869` | `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,
                           ...` |
| `dom_index` | struct | `src/dom.c:220` | `` |
| `dom_matches` | function | `src/dom.c:479` | `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)` |
| `dom_next_sibling` | function | `src/dom.c:537` | `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)` |
| `dom_node_at` | function | `src/dom.c:514` | `dom_node_id dom_node_at(const dom_index *idx, size_t position)` |
| `dom_node_count` | function | `src/dom.c:336` | `size_t dom_node_count(const dom_index *idx)` |
| `dom_parent` | function | `src/dom.c:519` | `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)` |
| `dom_precedes` | function | `src/dom.c:509` | `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)` |
| `dom_query_selector` | function | `src/dom.c:459` | `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,
                          ...` |
| `dom_query_selector_all` | function | `src/dom.c:468` | `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,
                           ...` |
| `dom_remove_attribute` | function | `src/dom.c:743` | `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)` |
| `dom_remove_child` | function | `src/dom.c:706` | `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)` |
| `dom_set_attribute` | function | `src/dom.c:714` | `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,
                             const...` |
| `dom_set_document_title` | function | `src/dom.c:644` | `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)` |
| `dom_set_inner_html` | function | `src/dom.c:762` | `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,
                              con...` |
| `dom_set_text_content` | function | `src/dom.c:619` | `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,
                               ...` |
| `dom_tag_name` | function | `src/dom.c:545` | `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)` |
| `dom_text_content` | function | `src/dom.c:596` | `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)` |
| `free` | function | `src/dom.c:93` | `free(m->buckets);` |
| `id_of` | function | `src/dom.c:376` | `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)` |
| `idx_push` | function | `src/dom.c:656` | `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)` |
| `ih_acc` | struct | `src/dom.c:808` | `` |
| `ih_append` | function | `src/dom.c:815` | `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)` |
| `ih_block` | struct | `src/dom.c:803` | `` |
| `ih_free` | function | `src/dom.c:842` | `static void ih_free(ih_acc *a)` |
| `index_element` | function | `src/dom.c:247` | `static int index_element(dom_index *idx, lxb_dom_element_t *el, dom_node_id id)` |
| `index_subtree` | function | `src/dom.c:753` | `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)` |
| `lxb_dom_document_create_element` | function | `src/dom.c:682` | `lxb_dom_document_create_element(idx->document, (const lxb_char_t *)lower, tlen, NULL);` |
| `lxb_dom_document_create_text_node` | function | `src/dom.c:637` | `lxb_dom_document_create_text_node(el->owner_document, (const lxb_char_t *)text, len);` |
| `lxb_dom_element_get_attribute` | function | `src/dom.c:251` | `lxb_dom_element_get_attribute(el, (const lxb_char_t *)"id", 2, &len);` |
| `lxb_dom_element_qualified_name` | function | `src/dom.c:551` | `lxb_dom_element_qualified_name(lxb_dom_interface_element(idx->nodes[node]), &tlen);` |
| `lxb_dom_element_remove_attribute` | function | `src/dom.c:747` | `lxb_dom_element_remove_attribute(lxb_dom_interface_element(idx->nodes[node]), (const lxb_char_t *)name, strlen(name));` |
| `lxb_dom_element_set_attribute` | function | `src/dom.c:722` | `lxb_dom_element_set_attribute(lxb_dom_interface_element(idx->nodes[node]), (const lxb_char_t *)name, nl, (const lxb_char` |
| `lxb_dom_node_insert_child` | function | `src/dom.c:640` | `lxb_dom_node_insert_child(el, lxb_dom_interface_node(t));` |
| `lxb_dom_node_remove` | function | `src/dom.c:630` | `lxb_dom_node_remove(c);` |
| `lxb_html_document_parse_fragment` | function | `src/dom.c:770` | `lxb_html_document_parse_fragment((lxb_html_document_t *)idx->document, lxb_dom_interface_element(el), (const lxb_char_t ` |
| `lxb_html_document_title` | function | `src/dom.c:612` | `lxb_html_document_title((lxb_html_document_t *)idx->document, &tl);` |
| `lxb_html_document_title_set` | function | `src/dom.c:648` | `lxb_html_document_title_set((lxb_html_document_t *)idx->document, (const lxb_char_t *)(text != NULL ? text : ""), len);` |
| `memcpy` | function | `src/dom.c:116` | `memcpy(e->key, key, klen);` |
| `node_matches_any` | function | `src/dom.c:419` | `static int node_matches_any(const lxb_dom_node_t *cn,
                            const css_sel *...` |
| `node_next` | function | `src/dom.c:232` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `parse_selector_list` | function | `src/dom.c:386` | `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)` |
| `pm_entry` | struct | `src/dom.c:154` | `` |
| `pm_free` | function | `src/dom.c:210` | `static void pm_free(ptrmap *m)` |
| `pm_get` | function | `src/dom.c:199` | `static int pm_get(const ptrmap *m, const void *key, dom_node_id *out)` |
| `pm_grow` | function | `src/dom.c:165` | `static int pm_grow(ptrmap *m)` |
| `pm_put` | function | `src/dom.c:182` | `static int pm_put(ptrmap *m, const void *key, dom_node_id id)` |
| `ptr_hash` | function | `src/dom.c:43` | `static size_t ptr_hash(const void *p)` |
| `ptrmap` | struct | `src/dom.c:160` | `` |
| `qs_walk` | function | `src/dom.c:466` | `return qs_walk(idx, root, sels, nsel, NULL, 0, NULL, 1);` |
| `sm_entry` | struct | `src/dom.c:55` | `` |
| `sm_entry_append` | function | `src/dom.c:69` | `static int sm_entry_append(sm_entry *e, dom_node_id id)` |
| `sm_find` | function | `src/dom.c:126` | `static const sm_entry *sm_find(const strmap *m, const char *key, size_t klen)` |
| `sm_free` | function | `src/dom.c:138` | `static void sm_free(strmap *m)` |
| `sm_grow` | function | `src/dom.c:81` | `static int sm_grow(strmap *m)` |
| `sm_put` | function | `src/dom.c:98` | `static int sm_put(strmap *m, const char *key, size_t klen, dom_node_id id)` |
| `strmap` | struct | `src/dom.c:64` | `` |
| `to_lower_buf` | function | `src/dom.c:33` | `static int to_lower_buf(const char *s, size_t n, char *out, size_t outcap)` |
| `valid` | function | `src/dom.c:241` | `static int valid(const dom_index *idx, dom_node_id n)` |
| `dd_align_name` | function | `src/dom_debug.c:107` | `static const char *dd_align_name(int a)` |
| `dd_block_line` | function | `src/dom_debug.c:301` | `static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b)` |
| `dd_border_style_name` | function | `src/dom_debug.c:210` | `static const char *dd_border_style_name(int s)` |
| `dd_box_line` | function | `src/dom_debug.c:243` | `static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b)` |
| `dd_color` | function | `src/dom_debug.c:83` | `static void dd_color(dd_cursor *c, int rgb)` |
| `dd_cursor` | struct | `src/dom_debug.c:24` | `` |
| `dd_cursor_name` | function | `src/dom_debug.c:164` | `static const char *dd_cursor_name(int c)` |
| `dd_display_name` | function | `src/dom_debug.c:87` | `static const char *dd_display_name(int d)` |
| `dd_emit` | function | `src/dom_debug.c:35` | `static void dd_emit(dd_cursor *c, const char *s, size_t len)` |
| `dd_field` | function | `src/dom_debug.c:371` | `dd_field(c, b->text);` |
| `dd_format` | function | `src/dom_debug.c:374` | `size_t dd_format(const rd_doc *doc, char *out, size_t cap)` |
| `dd_format_css` | function | `src/dom_debug.c:407` | `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)` |
| `dd_image_rendering_name` | function | `src/dom_debug.c:201` | `static const char *dd_image_rendering_name(int r)` |
| `dd_inset` | function | `src/dom_debug.c:187` | `static int dd_inset(int v)` |
| `dd_justify_name` | function | `src/dom_debug.c:95` | `static const char *dd_justify_name(int j)` |
| `dd_mix_blend_name` | function | `src/dom_debug.c:136` | `static const char *dd_mix_blend_name(int m)` |
| `dd_object_fit_name` | function | `src/dom_debug.c:190` | `static const char *dd_object_fit_name(int o)` |
| `dd_overflow_name` | function | `src/dom_debug.c:155` | `static const char *dd_overflow_name(int o)` |
| `dd_position_name` | function | `src/dom_debug.c:117` | `static const char *dd_position_name(int p)` |
| `dd_printf` | function | `src/dom_debug.c:48` | `static void dd_printf(dd_cursor *c, const char *fmt, ...)` |
| `dd_putc` | function | `src/dom_debug.c:30` | `static void dd_putc(dd_cursor *c, char ch)` |
| `dd_puts` | function | `src/dom_debug.c:39` | `static void dd_puts(dd_cursor *c, const char *s)` |
| `dd_text_overflow_name` | function | `src/dom_debug.c:181` | `static const char *dd_text_overflow_name(int t)` |
| `dd_visibility_name` | function | `src/dom_debug.c:128` | `static const char *dd_visibility_name(int v)` |
| `dd_w` | function | `src/dom_debug.c:80` | `static int dd_w(int v)` |
| `va_end` | function | `src/dom_debug.c:53` | `va_end(ap);` |
| `va_start` | function | `src/dom_debug.c:51` | `va_start(ap, fmt);` |
| `ci_find` | function | `src/download.c:19` | `static const char *ci_find(const char *hay, const char *needle)` |
| `copy_span` | function | `src/download.c:85` | `static void copy_span(const char *src, const char *end, char *buf, size_t bufsz)` |
| `dl_build_path` | function | `src/download.c:194` | `dl_status dl_build_path(const char *dir, const char *name, char *out, size_t outsz)` |
| `dl_check_size` | function | `src/download.c:212` | `dl_status dl_check_size(size_t len)` |
| `dl_ext_for_type` | function | `src/download.c:57` | `const char *dl_ext_for_type(const char *content_type)` |
| `dl_pick_name` | function | `src/download.c:152` | `dl_status dl_pick_name(const char *url, const char *content_disposition,
                       c...` |
| `dl_should_download` | function | `src/download.c:46` | `int dl_should_download(const char *content_type, const char *content_disposition)` |
| `extract_disposition_name` | function | `src/download.c:96` | `static int extract_disposition_name(const char *cd, char *buf, size_t bufsz)` |
| `extract_url_name` | function | `src/download.c:134` | `static int extract_url_name(const char *url, char *buf, size_t bufsz)` |
| `has_extension` | function | `src/download.c:148` | `static int has_extension(const char *name)` |
| `lc` | function | `src/download.c:13` | `static int lc(int c)` |
| `media_type` | function | `src/download.c:33` | `static void media_type(const char *content_type, char *buf, size_t bufsz)` |
| `memcpy` | function | `src/download.c:172` | `memcpy(cand, DL_FALLBACK_NAME, fl + 1);` |
| `FX_EPS` | macro | `src/flex_layout.c:14` | `#define FX_EPS` |
| `area_token_is_null_cell` | function | `src/flex_layout.c:294` | `static int area_token_is_null_cell(const char *tok, size_t len)` |
| `float_pack_impl` | function | `src/flex_layout.c:417` | `static fx_status float_pack_impl(const double *width, const int *side, size_t n,
                ...` |
| `fx_auto_min_size` | function | `src/flex_layout.c:556` | `double fx_auto_min_size(double min_content, double basis, double author_min,
                    ...` |
| `fx_flex_line` | function | `src/flex_layout.c:21` | `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                ...` |
| `fx_float_insets` | function | `src/flex_layout.c:456` | `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,
                 ...` |
| `fx_float_pack` | function | `src/flex_layout.c:496` | `fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        d...` |
| `fx_float_pack_wrap` | function | `src/flex_layout.c:501` | `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,
                    ...` |
| `fx_grid_area_hash` | function | `src/flex_layout.c:269` | `unsigned fx_grid_area_hash(const char *name)` |
| `fx_grid_area_rect` | function | `src/flex_layout.c:374` | `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,
                            int ...` |
| `fx_grid_areas_parse` | function | `src/flex_layout.c:299` | `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)` |
| `fx_grid_cell` | function | `src/flex_layout.c:543` | `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)` |
| `fx_grid_columns` | function | `src/flex_layout.c:126` | `fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          doubl...` |
| `fx_grid_columns_weighted` | function | `src/flex_layout.c:131` | `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                      ...` |
| `fx_grid_place_span` | function | `src/flex_layout.c:165` | `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                      ...` |
| `fx_justify_name` | function | `src/flex_layout.c:637` | `const char *fx_justify_name(fx_justify j)` |
| `fx_multicol_balance` | function | `src/flex_layout.c:606` | `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,
                        ...` |
| `fx_multicol_used` | function | `src/flex_layout.c:569` | `fx_status fx_multicol_used(double avail_w, int column_count, double column_width,
               ...` |
| `nn` | function | `src/flex_layout.c:18` | `static double nn(double v)` |
| `clean_action` | function | `src/form.c:75` | `static int clean_action(const char *action, char *out, size_t outsz)` |
| `copy_fit` | function | `src/form.c:66` | `static int copy_fit(char *dst, size_t dstsz, const char *src)` |
| `enc_component` | function | `src/form.c:25` | `static int enc_component(const char *s, char *out, size_t outsz, size_t *pos)` |
| `fm_build` | function | `src/form.c:119` | `fm_status fm_build(const char *base, const char *action, fm_method method,
                   con...` |
| `fm_encode` | function | `src/form.c:42` | `fm_status fm_encode(const fm_field *fields, size_t n,
                    char *out, size_t outsz...` |
| `memcpy` | function | `src/form.c:69` | `memcpy(dst, src, n + 1);` |
| `memset` | function | `src/form.c:123` | `memset(out, 0, sizeof *out);` |
| `put_char` | function | `src/form.c:17` | `static int put_char(char *out, size_t outsz, size_t *pos, char c)` |
| `resolve_target` | function | `src/form.c:101` | `static fm_block_reason resolve_target(const char *base, const char *act,
                        ...` |
| `strip_query` | function | `src/form.c:93` | `static void strip_query(char *url)` |
| `FC_DEFAULT_INTERVAL_MS` | macro | `src/frame_clock.c:7` | `#define FC_DEFAULT_INTERVAL_MS` |
| `fc_interval_ms` | function | `src/frame_clock.c:25` | `int fc_interval_ms(const fc_clock *c)` |
| `fc_needs_tick` | function | `src/frame_clock.c:20` | `int fc_needs_tick(const fc_clock *c)` |
| `fc_set_active` | function | `src/frame_clock.c:15` | `void fc_set_active(fc_clock *c, int active)` |
| `fb_buffer_at` | function | `src/freebug.c:104` | `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)` |
| `fb_buffer_count` | function | `src/freebug.c:100` | `size_t fb_buffer_count(const fb_buffer *b)` |
| `fb_buffer_free` | function | `src/freebug.c:90` | `void fb_buffer_free(fb_buffer *b)` |
| `fb_buffer_init` | function | `src/freebug.c:14` | `void fb_buffer_init(fb_buffer *b)` |
| `fb_buffer_push` | function | `src/freebug.c:18` | `int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)` |
| `fb_buffer_push_loc` | function | `src/freebug.c:22` | `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len,
                   ...` |
| `fb_buffer_reset` | function | `src/freebug.c:77` | `void fb_buffer_reset(fb_buffer *b)` |
| `fb_level_name` | function | `src/freebug.c:109` | `const char *fb_level_name(int level)` |
| `free` | function | `src/freebug.c:81` | `free(b->entries[i].text);` |
| `memset` | function | `src/freebug.c:98` | `memset(b, 0, sizeof *b);` |
| `whole` | function | `src/freebug.c:5` | `* FB_MAX_TOTAL_BYTES is dropped whole (overflow flag raised, prior entries kept);` |
| `BLOCKED` | function | `src/freedom.c:779` | `* is BLOCKED (fail closed), never leaked over the clearnet. */ nr_route route = nr_route_for(url, global_net);` |
| `CSS_DROPS_REPORT_MAX` | macro | `src/freedom.c:160` | `#define CSS_DROPS_REPORT_MAX` |
| `EXIT_ERROR` | macro | `src/freedom.c:44` | `#define EXIT_ERROR` |
| `EXIT_OK` | macro | `src/freedom.c:42` | `#define EXIT_OK` |
| `EXIT_USAGE` | macro | `src/freedom.c:45` | `#define EXIT_USAGE` |
| `HL_JS_NAV_MAX` | macro | `src/freedom.c:749` | `#define HL_JS_NAV_MAX` |
| `_DEFAULT_SOURCE` | macro | `src/freedom.c:10` | `#define _DEFAULT_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `src/freedom.c:8` | `#define _POSIX_C_SOURCE` |
| `_exit` | function | `src/freedom.c:1036` | `_exit(1);` |
| `dd_format` | function | `src/freedom.c:382` | `dd_format(doc, buf, need + 1);` |
| `dd_format_css` | function | `src/freedom.c:397` | `dd_format_css(doc, buf, need + 1);` |
| `dump_video_stream` | function | `src/freedom.c:950` | `return dump_video_stream(var_url, out_fp);` |
| `elsewhere` | function | `src/freedom.c:814` | `* page whose script immediately forwards elsewhere (e.g. a search engine's
 * JS-capability inter...` |
| `fclose` | function | `src/freedom.c:207` | `fclose(f);` |
| `fetch_and_render` | function | `src/freedom.c:836` | `return fetch_and_render(target);` |
| `fetch_and_render_one` | function | `src/freedom.c:753` | `static int fetch_and_render_one(const char *url, char **out_nav)` |
| `fflush` | function | `src/freedom.c:1021` | `fflush(out);` |
| `foldback_cookies` | function | `src/freedom.c:471` | `static void foldback_cookies(const char *url, const char *jar)` |
| `fprintf` | function | `src/freedom.c:48` | `fprintf(fp, "usage: %s [--help] [--version] [--headless] [--insecure] <url-or-file>\n", prog);` |
| `fputs` | function | `src/freedom.c:383` | `fputs(buf, stdout);` |
| `free` | function | `src/freedom.c:384` | `free(buf);` |
| `gets` | function | `src/freedom.c:409` | `* gate a click gets (https-only, no downgrade, no foreign scheme), so relative * subresources work. Realm-routed (fail-c` |
| `headless_fetch` | function | `src/freedom.c:413` | `static int headless_fetch(void *ctx, const char *method, const char *url,
                       ...` |
| `headless_load_hosts` | function | `src/freedom.c:212` | `static void headless_load_hosts(void)` |
| `hls_playlist_free` | function | `src/freedom.c:942` | `hls_playlist_free(pl);` |
| `hp_document_free` | function | `src/freedom.c:506` | `hp_document_free(hdoc);` |
| `is_blank_text` | function | `src/freedom.c:251` | `static int is_blank_text(const char *s)` |
| `is_http_url` | function | `src/freedom.c:75` | `static int is_http_url(const char *s)` |
| `is_https_url` | function | `src/freedom.c:71` | `static int is_https_url(const char *s)` |
| `is_overlay_http` | function | `src/freedom.c:81` | `static int is_overlay_http(const char *s)` |
| `main` | function | `src/freedom.c:1025` | `int main(int argc, char **argv)` |
| `memcpy` | function | `src/freedom.c:480` | `memcpy(pair, p, plen);` |
| `memset` | function | `src/freedom.c:318` | `memset(bar, '=', (size_t)filled);` |
| `now_us` | function | `src/freedom.c:134` | `static uint64_t now_us(void)` |
| `only` | function | `src/freedom.c:622` | `* styling for the local render only (no network). --images enables image loading * AND rendering, including remote fetch` |
| `pf_list_free` | function | `src/freedom.c:589` | `pf_list_free(&scanned);` |
| `pool` | function | `src/freedom.c:586` | `* the pool (unconsumed results freed, in-flight fetches joined). */ tab_set_fetcher(t, headless_fetch, (void *)(uintptr_` |
| `print_console` | function | `src/freedom.c:357` | `static void print_console(const fb_buffer *log)` |
| `print_css_drops` | function | `src/freedom.c:495` | `static void print_css_drops(const char *html, size_t len)` |
| `print_doc` | function | `src/freedom.c:264` | `static void print_doc(const rd_doc *doc)` |
| `print_dom` | function | `src/freedom.c:374` | `static void print_dom(const rd_doc *doc)` |
| `print_dom_css` | function | `src/freedom.c:389` | `static void print_dom_css(const rd_doc *doc)` |
| `print_usage` | function | `src/freedom.c:46` | `static void print_usage(FILE *fp, const char *prog)` |
| `printf` | function | `src/freedom.c:274` | `printf(" %s\n", b->text);` |
| `pt_record` | function | `src/freedom.c:583` | `pt_record(&g_timings, PT_IPC, pt_elapsed_us(ipc_t0, now_us()));` |
| `putchar` | function | `src/freedom.c:272` | `putchar('\n');` |
| `rd_free` | function | `src/freedom.c:717` | `rd_free(doc);` |
| `read_file` | function | `src/freedom.c:195` | `static char *read_file(const char *path, size_t *out_len)` |
| `render_page` | function | `src/freedom.c:525` | `static int render_page(const char *html, size_t len, const char *top_url,
                       ...` |
| `rewind` | function | `src/freedom.c:201` | `rewind(f);` |
| `run_dump_video` | function | `src/freedom.c:1007` | `static int run_dump_video(const char *url)` |
| `run_headless` | function | `src/freedom.c:832` | `static int run_headless(const char *target)` |
| `setenv` | function | `src/freedom.c:1110` | `setenv("FREEDOM_JS", "on", 1);` |
| `sf_cookie_put` | function | `src/freedom.c:481` | `sf_cookie_put(url, pair);` |
| `sf_get_follow` | function | `src/freedom.c:451` | `: sf_get_follow(url, &cfg, &resp, SF_DEFAULT_MAX_REDIRECTS);` |
| `sf_reason` | function | `src/freedom.c:733` | `static const char *sf_reason(sf_status ss)` |
| `sf_response_free` | function | `src/freedom.c:461` | `sf_response_free(&resp);` |
| `snprintf` | function | `src/freedom.c:225` | `snprintf(home_dir, sizeof home_dir, "%s/.config/freedom", home);` |
| `tab_close` | function | `src/freedom.c:593` | `tab_close(t);` |
| `tab_page_free` | function | `src/freedom.c:605` | `tab_page_free(&page);` |
| `tab_set_css_allowed` | function | `src/freedom.c:543` | `tab_set_css_allowed(t, wc.css);` |
| `tab_set_fetcher` | function | `src/freedom.c:564` | `tab_set_fetcher(t, pf_pooled_fetch, &gated);` |
| `tab_set_net_allowed` | function | `src/freedom.c:542` | `tab_set_net_allowed(t, wc.net);` |
| `tab_set_viewport_w` | function | `src/freedom.c:579` | `tab_set_viewport_w(t, ui_render_viewport_w());` |
| `tab_worker_dispatch` | function | `src/freedom.c:1038` | `tab_worker_dispatch(argc, argv);` |
| `timings_dump` | function | `src/freedom.c:148` | `static void timings_dump(void)` |
| `timings_enabled` | function | `src/freedom.c:144` | `static int timings_enabled(void)` |
| `timings_ensure_init` | function | `src/freedom.c:140` | `static void timings_ensure_init(void)` |
| `ui_render_pdf` | function | `src/freedom.c:649` | `: ui_render_pdf(doc, g_pdf_out, &pages);` |
| `ui_render_png` | function | `src/freedom.c:670` | `: ui_render_png(doc, g_png_out, &img_h);` |
| `video_fetch_with_fallback` | function | `src/freedom.c:896` | `static sf_status video_fetch_with_fallback(const char *url, sf_config *cfg,
                     ...` |
| `_GNU_SOURCE` | macro | `src/hls.c:20` | `#define _GNU_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `src/hls.c:22` | `#define _POSIX_C_SOURCE` |
| `free` | function | `src/hls.c:256` | `free(pl->segments[i].url);` |
| `hls_parse` | function | `src/hls.c:79` | `hls_status hls_parse(const char *text, size_t len, hls_playlist **out)` |
| `hls_playlist_free` | function | `src/hls.c:252` | `void hls_playlist_free(hls_playlist *pl)` |
| `hls_resolve_url` | function | `src/hls.c:222` | `size_t hls_resolve_url(const char *base_url, const char *segment_url,
                       char...` |
| `hls_select_variant` | function | `src/hls.c:201` | `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h)` |
| `last_char` | function | `src/hls.c:38` | `static const char *last_char(const char *s, size_t n, int c)` |
| `memcpy` | function | `src/hls.c:121` | `memcpy(dbuf, val, vallen);` |
| `memset` | function | `src/hls.c:94` | `memset(&current_variant, 0, sizeof current_variant);` |
| `name` | function | `src/hls.c:46` | `* attr is the attribute name (e.g. "BANDWIDTH=");` |
| `parse_attr_long` | function | `src/hls.c:48` | `static int parse_attr_long(const char *attrs, const char *end,
                           const c...` |
| `parse_attr_resolution` | function | `src/hls.c:62` | `static void parse_attr_resolution(const char *attrs, const char *end,
                           ...` |
| `HB_INIT_CAP` | macro | `src/hostblock.c:20` | `#define HB_INIT_CAP` |
| `HB_MAX_HOST` | macro | `src/hostblock.c:18` | `#define HB_MAX_HOST` |
| `free` | function | `src/hostblock.c:65` | `free(old);` |
| `hb_check` | function | `src/hostblock.c:192` | `hb_decision hb_check(const hb_set *s, const char *host)` |
| `hb_count` | function | `src/hostblock.c:237` | `size_t hb_count(const hb_set *s, hb_list list)` |
| `hb_free` | function | `src/hostblock.c:148` | `void hb_free(hb_set *s)` |
| `hb_is_allowlisted` | function | `src/hostblock.c:217` | `int hb_is_allowlisted(const hb_set *s, const char *host)` |
| `hb_load` | function | `src/hostblock.c:155` | `hb_status hb_load(hb_set *s, const char *text, hb_list list)` |
| `hb_new` | function | `src/hostblock.c:143` | `hb_set *hb_new(void)` |
| `hb_set` | struct | `src/hostblock.c:30` | `` |
| `hb_table` | struct | `src/hostblock.c:24` | `` |
| `is_domain_char` | function | `src/hostblock.c:122` | `static int is_domain_char(char c)` |
| `is_ip_token` | function | `src/hostblock.c:113` | `static int is_ip_token(const char *s, size_t n)` |
| `lower` | function | `src/hostblock.c:106` | `static char lower(char c)` |
| `memcpy` | function | `src/hostblock.c:85` | `memcpy(copy, key, klen);` |
| `table_contains` | function | `src/hostblock.c:91` | `static int table_contains(const hb_table *t, const char *key)` |
| `table_free` | function | `src/hostblock.c:97` | `static void table_free(hb_table *t)` |
| `table_grow` | function | `src/hostblock.c:49` | `static int table_grow(hb_table *t, size_t newcap)` |
| `table_insert` | function | `src/hostblock.c:71` | `static int table_insert(hb_table *t, const char *key, size_t klen)` |
| `table_probe` | function | `src/hostblock.c:38` | `static size_t table_probe(const hb_table *t, const char *key, size_t klen)` |
| `contains_ci` | function | `src/hostedit.c:115` | `static int contains_ci(const char *hs, size_t hl, const char *needle)` |
| `has_host_cb` | function | `src/hostedit.c:104` | `static int has_host_cb(const char *ts, size_t tl, void *ctx)` |
| `he_lower` | function | `src/hostedit.c:11` | `static char he_lower(char c)` |
| `he_make_line` | function | `src/hostedit.c:40` | `he_status he_make_line(const char *host, char *out, size_t cap)` |
| `he_scan` | function | `src/hostedit.c:80` | `static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), void *ctx)` |
| `he_suggest` | function | `src/hostedit.c:163` | `int he_suggest(const char *text, const char *query,
               char results[][HE_MAX_HOST + 1...` |
| `he_text_has_host` | function | `src/hostedit.c:108` | `int he_text_has_host(const char *text, const char *host)` |
| `is_ip_token` | function | `src/hostedit.c:67` | `static int is_ip_token(const char *ts, const char *te)` |
| `is_label_char` | function | `src/hostedit.c:15` | `static int is_label_char(char c)` |
| `starts_with_ci` | function | `src/hostedit.c:127` | `static int starts_with_ci(const char *hs, size_t hl, const char *pfx)` |
| `suggest_cb` | function | `src/hostedit.c:143` | `static int suggest_cb(const char *ts, size_t tl, void *vctx)` |
| `suggest_ctx` | struct | `src/hostedit.c:136` | `` |
| `token_eq_host` | function | `src/hostedit.c:106` | `return token_eq_host(ts, ts + tl, (const char *)ctx);` |
| `valid_host` | function | `src/hostedit.c:22` | `static int valid_host(const char *host, size_t n)` |
| `_POSIX_C_SOURCE` | macro | `src/html_parse.c:8` | `#define _POSIX_C_SOURCE` |
| `attr_has_token_ci` | function | `src/html_parse.c:210` | `static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle)` |
| `attr_is_event_handler` | function | `src/html_parse.c:46` | `static int attr_is_event_handler(const lxb_dom_attr_t *attr)` |
| `dup_bytes` | function | `src/html_parse.c:26` | `static char *dup_bytes(const lxb_char_t *src, size_t len)` |
| `free` | function | `src/html_parse.c:81` | `free(list);` |
| `hp_config_default` | function | `src/html_parse.c:315` | `hp_config hp_config_default(void)` |
| `hp_document` | struct | `src/html_parse.c:21` | `` |
| `hp_document_free` | function | `src/html_parse.c:441` | `void hp_document_free(hp_document *doc)` |
| `hp_document_root` | function | `src/html_parse.c:447` | `const void *hp_document_root(const hp_document *doc)` |
| `hp_element_count` | function | `src/html_parse.c:367` | `size_t hp_element_count(const hp_document *doc)` |
| `hp_event_handler_count` | function | `src/html_parse.c:387` | `size_t hp_event_handler_count(const hp_document *doc)` |
| `hp_extract_script_list` | function | `src/html_parse.c:126` | `hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count)` |
| `hp_extract_stylesheet_hrefs` | function | `src/html_parse.c:252` | `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count)` |
| `hp_extract_text` | function | `src/html_parse.c:403` | `char *hp_extract_text(const hp_document *doc, size_t *out_len)` |
| `hp_free` | function | `src/html_parse.c:437` | `void hp_free(char *buf)` |
| `hp_free_scripts` | function | `src/html_parse.c:196` | `void hp_free_scripts(hp_script *scripts, size_t count)` |
| `hp_free_stylesheet_hrefs` | function | `src/html_parse.c:286` | `void hp_free_stylesheet_hrefs(char **hrefs, size_t count)` |
| `hp_get_title` | function | `src/html_parse.c:422` | `char *hp_get_title(const hp_document *doc, size_t *out_len)` |
| `hp_parse` | function | `src/html_parse.c:333` | `hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out)` |
| `hp_script_count` | function | `src/html_parse.c:377` | `size_t hp_script_count(const hp_document *doc)` |
| `hp_validate_input` | function | `src/html_parse.c:323` | `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg)` |
| `link_is_active_stylesheet` | function | `src/html_parse.c:231` | `static int link_is_active_stylesheet(lxb_dom_element_t *el,
                                     ...` |
| `lxb_dom_document_destroy_text` | function | `src/html_parse.c:418` | `lxb_dom_document_destroy_text(lxb_dom_interface_document(doc->doc), text);` |
| `lxb_dom_element_get_attribute` | function | `src/html_parse.c:102` | `lxb_dom_element_get_attribute(el, (const lxb_char_t *)"type", 4, &len);` |
| `lxb_dom_interface_element` | function | `src/html_parse.c:178` | `lxb_dom_interface_element((lxb_dom_node_t *)n), (const lxb_char_t *)"defer", 5, &dl);` |
| `lxb_dom_interface_node` | function | `src/html_parse.c:411` | `: lxb_dom_interface_node(doc->doc);` |
| `lxb_dom_node_destroy_deep` | function | `src/html_parse.c:79` | `lxb_dom_node_destroy_deep(list[i]);` |
| `lxb_dom_node_remove` | function | `src/html_parse.c:78` | `lxb_dom_node_remove(list[i]);` |
| `lxb_html_document_destroy` | function | `src/html_parse.c:349` | `lxb_html_document_destroy(document);` |
| `node_is_script` | function | `src/html_parse.c:53` | `static int node_is_script(const lxb_dom_node_t *node)` |
| `node_next` | function | `src/html_parse.c:37` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `script_classify` | function | `src/html_parse.c:97` | `static int script_classify(const lxb_dom_node_t *n,
                           const lxb_char_t *...` |
| `strip_event_handlers` | function | `src/html_parse.c:292` | `static void strip_event_handlers(lxb_html_document_t *document)` |
| `strip_scripts` | function | `src/html_parse.c:59` | `static void strip_scripts(lxb_html_document_t *document)` |
| `GIF_LZW_MAX_CODES` | macro | `src/image_decode.c:252` | `#define GIF_LZW_MAX_CODES` |
| `PNG_IHDR_MIN` | macro | `src/image_decode.c:34` | `#define PNG_IHDR_MIN` |
| `exit` | function | `src/image_decode.c:6` | `* malformed stream fails closed instead of calling exit(). GIF uses an own pure-C * bounded LZW decoder (no giflib). Web` |
| `free` | function | `src/image_decode.c:137` | `free(buf);` |
| `gb_next_code` | function | `src/image_decode.c:297` | `static int gb_next_code(gif_bits *b, unsigned width, unsigned *out)` |
| `gif_bits` | struct | `src/image_decode.c:290` | `` |
| `gif_deinterlace_row` | function | `src/image_decode.c:319` | `static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh)` |
| `gif_put_pixel` | function | `src/image_decode.c:334` | `static void gif_put_pixel(uint32_t *canvas, uint32_t cw, uint32_t ch,
                          u...` |
| `gif_reader` | struct | `src/image_decode.c:255` | `` |
| `gr_skip` | function | `src/image_decode.c:272` | `static int gr_skip(gif_reader *r, size_t n)` |
| `gr_skip_subblocks` | function | `src/image_decode.c:280` | `static int gr_skip_subblocks(gif_reader *r)` |
| `gr_u16le` | function | `src/image_decode.c:265` | `static int gr_u16le(gif_reader *r, uint16_t *out)` |
| `gr_u8` | function | `src/image_decode.c:259` | `static int gr_u8(gif_reader *r, uint8_t *out)` |
| `img_decode` | function | `src/image_decode.c:552` | `img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_gif` | function | `src/image_decode.c:353` | `img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_jpeg` | function | `src/image_decode.c:165` | `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_png` | function | `src/image_decode.c:101` | `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_webp` | function | `src/image_decode.c:519` | `img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_dimensions_ok` | function | `src/image_decode.c:67` | `int img_dimensions_ok(uint32_t w, uint32_t h)` |
| `img_fit` | function | `src/image_decode.c:75` | `void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,
             double *out_w, do...` |
| `img_format_name` | function | `src/image_decode.c:574` | `const char *img_format_name(img_format f)` |
| `img_pixels_free` | function | `src/image_decode.c:565` | `void img_pixels_free(img_pixels *p)` |
| `img_png_dimensions` | function | `src/image_decode.c:56` | `img_status img_png_dimensions(const uint8_t *bytes, size_t len,
                              uin...` |
| `jpeg_create_decompress` | function | `src/image_decode.c:190` | `jpeg_create_decompress(&cinfo);` |
| `jpeg_destroy_decompress` | function | `src/image_decode.c:185` | `jpeg_destroy_decompress(&cinfo);` |
| `jpeg_err_ctx` | struct | `src/image_decode.c:153` | `` |
| `jpeg_error_longjmp` | function | `src/image_decode.c:157` | `static void jpeg_error_longjmp(j_common_ptr cinfo)` |
| `jpeg_finish_decompress` | function | `src/image_decode.c:235` | `jpeg_finish_decompress(&cinfo);` |
| `jpeg_mem_src` | function | `src/image_decode.c:192` | `jpeg_mem_src(&cinfo, bytes, (unsigned long)len);` |
| `jpeg_silence` | function | `src/image_decode.c:164` | `static void jpeg_silence(j_common_ptr cinfo)` |
| `jpeg_start_decompress` | function | `src/image_decode.c:205` | `jpeg_start_decompress(&cinfo);` |
| `longjmp` | function | `src/image_decode.c:160` | `longjmp(e->jb, 1);` |
| `memset` | function | `src/image_decode.c:104` | `memset(out, 0, sizeof *out);` |
| `png_image_free` | function | `src/image_decode.c:113` | `png_image_free(&image);` |
| `premultiply` | function | `src/image_decode.c:90` | `static void premultiply(uint8_t *data, size_t pixels)` |
| `read_be32` | function | `src/image_decode.c:51` | `static uint32_t read_be32(const uint8_t *p)` |
| `anim_effective_dir` | function | `src/interp.c:231` | `static int anim_effective_dir(const ip_anim *a)` |
| `anim_effective_dir_for` | function | `src/interp.c:221` | `static int anim_effective_dir_for(const ip_anim *a, int iter)` |
| `ip_anim_current` | function | `src/interp.c:281` | `double ip_anim_current(const ip_anim *a)` |
| `ip_anim_done` | function | `src/interp.c:319` | `int ip_anim_done(const ip_anim *a)` |
| `ip_anim_init` | function | `src/interp.c:195` | `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease,
                  const ip_...` |
| `ip_anim_tick` | function | `src/interp.c:235` | `int ip_anim_tick(ip_anim *a, double dt_ms)` |
| `ip_ease` | function | `src/interp.c:54` | `double ip_ease(double t, const ip_ease_fn *fn)` |
| `ip_ease` | function | `src/interp.c:62` | `case IP_EASE_EASE:
        return ip_ease(t, &(ip_ease_fn)` |
| `ip_ease` | function | `src/interp.c:68` | `case IP_EASE_EASE_IN:
        return ip_ease(t, &(ip_ease_fn)` |
| `ip_ease` | function | `src/interp.c:74` | `case IP_EASE_EASE_OUT:
        return ip_ease(t, &(ip_ease_fn)` |
| `ip_ease` | function | `src/interp.c:80` | `case IP_EASE_EASE_IN_OUT:
        return ip_ease(t, &(ip_ease_fn)` |
| `ip_interp` | function | `src/interp.c:161` | `double ip_interp(ip_val_kind kind, double a, double b, double t)` |
| `ip_kf_interp` | function | `src/interp.c:174` | `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf,
                    int n_kf, do...` |
| `ip_lerp` | function | `src/interp.c:133` | `double ip_lerp(double a, double b, double t)` |
| `ip_lerp_color` | function | `src/interp.c:138` | `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t)` |
| `sample_bezier_dx` | function | `src/interp.c:22` | `static double sample_bezier_dx(double t, double cx1, double cx2)` |
| `sample_bezier_x` | function | `src/interp.c:17` | `static double sample_bezier_x(double t, double cx1, double cx2)` |
| `sample_bezier_y` | function | `src/interp.c:28` | `static double sample_bezier_y(double t, double cy1, double cy2)` |
| `solve_bezier_t` | function | `src/interp.c:35` | `static double solve_bezier_t(double x, double cx1, double cx2)` |
| `JS_DefinePropertyValueStr` | function | `src/js_dom.c:1538` | `JS_DefinePropertyValueStr(jsctx, dom, JD_METHODS[i].name, fn, JS_PROP_ENUMERABLE);` |
| `JS_FreeCString` | function | `src/js_dom.c:63` | `JS_FreeCString(ctx, s);` |
| `JS_FreeValue` | function | `src/js_dom.c:83` | `JS_FreeValue(ctx, arr);` |
| `JS_NewBool` | function | `src/js_dom.c:163` | `return JS_NewBool(ctx, dom_precedes(jd_idx(ctx), a, b));` |
| `JS_NewInt64` | function | `src/js_dom.c:54` | `return JS_NewInt64(ctx, (int64_t)dom_node_count(jd_idx(ctx)));` |
| `JS_PreventExtensions` | function | `src/js_dom.c:1543` | `JS_PreventExtensions(jsctx, dom);` |
| `JS_SetContextOpaque` | function | `src/js_dom.c:1528` | `JS_SetContextOpaque(jsctx, (void *)opaque);` |
| `JS_SetPropertyStr` | function | `src/js_dom.c:323` | `JS_SetPropertyStr(ctx, global, "__clickRegistry", JS_DupValue(ctx, reg));` |
| `JS_SetPropertyUint32` | function | `src/js_dom.c:90` | `JS_SetPropertyUint32(ctx, arr, (uint32_t)i, JS_NewInt64(ctx, (int64_t)buf[i]));` |
| `JS_SetRuntimeOpaque` | function | `src/js_dom.c:1655` | `JS_SetRuntimeOpaque(JS_GetRuntime(jsctx), (void *)log);` |
| `JS_ThrowOutOfMemory` | function | `src/js_dom.c:84` | `return JS_ThrowOutOfMemory(ctx);` |
| `JS_ToInt32` | function | `src/js_dom.c:1810` | `JS_ToInt32(ctx, &l, lo);` |
| `_GNU_SOURCE` | macro | `src/js_dom.c:9` | `#define _GNU_SOURCE` |
| `attrNames` | function | `src/js_dom.c:561` | `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so
     * a missing '...` |
| `dom_append_child` | function | `src/js_dom.c:2305` | `dom_append_child(idx, bid, ifr_id);` |
| `dom_get_by_tag` | function | `src/js_dom.c:74` | `: dom_get_by_tag(idx, s, NULL, 0);` |
| `dom_set_attribute` | function | `src/js_dom.c:2304` | `dom_set_attribute(idx, ifr_id, "src", best_url);` |
| `empty` | function | `src/js_dom.c:1006` | `* inert: DOM interface constructors are empty (instanceof yields false, harmless);` |
| `enough` | function | `src/js_dom.c:825` | `* enough (cloneNode/lastChild/removeChild/insertBefore) that library feature * detection does not throw: jQuery clones a` |
| `fails` | function | `src/js_dom.c:1579` | `* cap is reached or an allocation fails (caller stops), else 0. */
static int cb_append(char **bu...` |
| `fb_buffer_push` | function | `src/js_dom.c:1636` | `fb_buffer_push(log, magic, (msg != NULL) ? msg : "", len);` |
| `fire` | function | `src/js_dom.c:1007` | `* observers never fire (no observation -> no info leak);` |
| `free` | function | `src/js_dom.c:92` | `free(buf);` |
| `jd_click_state` | struct | `src/js_dom.c:1940` | `` |
| `jd_click_state_free` | function | `src/js_dom.c:1948` | `void jd_click_state_free(jd_click_state *s)` |
| `jd_click_state_new` | function | `src/js_dom.c:1943` | `jd_click_state *jd_click_state_new(void)` |
| `jd_escape_js_str` | function | `src/js_dom.c:2020` | `static size_t jd_escape_js_str(const char *src, char *dst, size_t dstsz)` |
| `jd_fire_click` | function | `src/js_dom.c:1963` | `int jd_fire_click(js_context *ctx, dom_node_id node_id)` |
| `jd_fire_mouse_event` | function | `src/js_dom.c:2099` | `int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,
                        const char ...` |
| `jd_fire_submit` | function | `src/js_dom.c:1992` | `int jd_fire_submit(js_context *ctx, dom_node_id form_node_id)` |
| `jd_get_cookies` | function | `src/js_dom.c:1738` | `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)` |
| `jd_handle` | function | `src/js_dom.c:38` | `static int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out)` |
| `jd_handle_or_null` | function | `src/js_dom.c:44` | `static JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h)` |
| `jd_idx` | function | `src/js_dom.c:28` | `static dom_index *jd_idx(JSContext *ctx)` |
| `jd_inject_video_shim` | function | `src/js_dom.c:2347` | `jd_status jd_inject_video_shim(js_context *ctx)` |
| `jd_install` | function | `src/js_dom.c:1518` | `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)` |
| `jd_install_console` | function | `src/js_dom.c:1648` | `jd_status jd_install_console(js_context *ctx, fb_buffer *log)` |
| `jd_install_events` | function | `src/js_dom.c:1952` | `jd_status jd_install_events(js_context *ctx, jd_click_state *state)` |
| `jd_install_xhr` | function | `src/js_dom.c:1913` | `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)` |
| `jd_lp_set` | function | `src/js_dom.c:1477` | `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,
                      const ...` |
| `jd_method` | struct | `src/js_dom.c:303` | `` |
| `jd_opaque_get` | function | `src/js_dom.c:24` | `static jd_opaque *jd_opaque_get(JSContext *ctx)` |
| `jd_pack_ptr` | function | `src/js_dom.c:1803` | `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)` |
| `jd_process_iframes` | function | `src/js_dom.c:2399` | `void jd_process_iframes(js_context *ctx, dom_index *idx,
                        jd_fetch_fn fn, ...` |
| `jd_query_list` | function | `src/js_dom.c:68` | `static JSValue jd_query_list(JSContext *ctx, JSValueConst arg, int by_class)` |
| `jd_set_cookies` | function | `src/js_dom.c:1718` | `jd_status jd_set_cookies(js_context *ctx, const char *cookies)` |
| `jd_set_location` | function | `src/js_dom.c:1684` | `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)` |
| `jd_take_nav_request` | function | `src/js_dom.c:1760` | `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)` |
| `jd_unpack_ptr` | function | `src/js_dom.c:1808` | `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)` |
| `jd_video_from_scripts` | function | `src/js_dom.c:2308` | `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,
                   ...` |
| `js_env` | function | `src/js_dom.c:1012` | `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the
 * document shim (uses...` |
| `m_append_child` | function | `src/js_dom.c:224` | `static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,
                            ...` |
| `m_attr_names` | function | `src/js_dom.c:481` | `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,
                            in...` |
| `m_closest` | function | `src/js_dom.c:469` | `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,
                         int argc...` |
| `m_create_element` | function | `src/js_dom.c:212` | `static JSValue m_create_element(JSContext *ctx, JSValueConst this_val,
                          ...` |
| `m_first_child` | function | `src/js_dom.c:140` | `static JSValue m_first_child(JSContext *ctx, JSValueConst this_val,
                             ...` |
| `m_get_attribute` | function | `src/js_dom.c:119` | `static JSValue m_get_attribute(JSContext *ctx, JSValueConst this_val,
                           ...` |
| `m_get_by_class` | function | `src/js_dom.c:103` | `static JSValue m_get_by_class(JSContext *ctx, JSValueConst this_val,
                            ...` |
| `m_get_by_tag` | function | `src/js_dom.c:97` | `static JSValue m_get_by_tag(JSContext *ctx, JSValueConst this_val,
                            in...` |
| `m_get_element_by_id` | function | `src/js_dom.c:56` | `static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val,
                       ...` |
| `m_get_inner_html` | function | `src/js_dom.c:287` | `static JSValue m_get_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...` |
| `m_get_title` | function | `src/js_dom.c:191` | `static JSValue m_get_title(JSContext *ctx, JSValueConst this_val,
                           int ...` |
| `m_host_fetch` | function | `src/js_dom.c:1821` | `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,
                            in...` |
| `m_matches` | function | `src/js_dom.c:457` | `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,
                         int argc...` |
| `m_next_sibling` | function | `src/js_dom.c:148` | `static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,
                            ...` |
| `m_node_count` | function | `src/js_dom.c:50` | `static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,
                            in...` |
| `m_parent` | function | `src/js_dom.c:132` | `static JSValue m_parent(JSContext *ctx, JSValueConst this_val,
                        int argc, ...` |
| `m_precedes` | function | `src/js_dom.c:156` | `static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,
                          int ar...` |
| `m_query_selector` | function | `src/js_dom.c:416` | `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,
                          ...` |
| `m_query_selector_all` | function | `src/js_dom.c:429` | `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,
                      ...` |
| `m_register_click` | function | `src/js_dom.c:308` | `static JSValue m_register_click(JSContext *ctx, JSValueConst this_val,
                          ...` |
| `m_register_event` | function | `src/js_dom.c:355` | `static JSValue m_register_event(JSContext *ctx, JSValueConst this_val,
                          ...` |
| `m_register_submit` | function | `src/js_dom.c:330` | `static JSValue m_register_submit(JSContext *ctx, JSValueConst this_val,
                         ...` |
| `m_remove_attribute` | function | `src/js_dom.c:258` | `static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,
                        ...` |
| `m_remove_child` | function | `src/js_dom.c:233` | `static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,
                            ...` |
| `m_set_attribute` | function | `src/js_dom.c:242` | `static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,
                           ...` |
| `m_set_inner_html` | function | `src/js_dom.c:270` | `static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...` |
| `m_set_text` | function | `src/js_dom.c:177` | `static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,
                          int ar...` |
| `m_set_title` | function | `src/js_dom.c:199` | `static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,
                           int ...` |
| `m_tag_name` | function | `src/js_dom.c:109` | `static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,
                          int ar...` |
| `m_text_content` | function | `src/js_dom.c:167` | `static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,
                            ...` |
| `memcpy` | function | `src/js_dom.c:1752` | `memcpy(buf, s, slen);` |
| `memset` | function | `src/js_dom.c:1526` | `memset(opaque, 0, sizeof *opaque);` |
| `ms` | function | `src/js_dom.c:918` | `* due is the remaining virtual ms (the trusted parent advances the clock via * OP_TICK -> __tickTimers(elapsed);` |
| `resolve_video_url` | function | `src/js_dom.c:2217` | `resolve_video_url(tmp, page_url, best_url, sizeof best_url);` |
| `scan_video_url` | function | `src/js_dom.c:2362` | `static int scan_video_url(const char *body, size_t blen,
                           char *out, si...` |
| `scripts` | function | `src/js_dom.c:694` | `* player scripts (canPlayType feature-detection, play/pause, muted/loop * reflection, buffered ranges) run without throw` |
| `send` | function | `src/js_dom.c:1867` | `* callbacks fire right after send();` |
| `snprintf` | function | `src/js_dom.c:378` | `snprintf(nstr, sizeof nstr, "%u", (unsigned)h);` |
| `try_create_iframe_from_script` | function | `src/js_dom.c:2192` | `static int try_create_iframe_from_script(dom_index *idx,
                                        ...` |
| `FP_MIME_COUNT` | macro | `src/js_env.c:253` | `#define FP_MIME_COUNT` |
| `JS_DefinePropertyValueStr` | function | `src/js_env.c:209` | `JS_DefinePropertyValueStr(ctx, p0, "name", JS_NewString(ctx, "Chrome PDF Plugin"), JS_PROP_ENUMERABLE);` |
| `JS_DefinePropertyValueUint32` | function | `src/js_env.c:218` | `JS_DefinePropertyValueUint32(ctx, plugins, 0, p0, JS_PROP_ENUMERABLE);` |
| `JS_DupValue` | function | `src/js_env.c:122` | `return JS_DupValue(ctx, argv[0]);` |
| `JS_FreeValue` | function | `src/js_env.c:102` | `JS_FreeValue(ctx, ab);` |
| `JS_NewArray` | function | `src/js_env.c:80` | `return JS_NewArray(ctx);` |
| `JS_NewCFunctionData` | function | `src/js_env.c:474` | `return JS_NewCFunctionData(ctx, m_readback, 1, 0, 2, data);` |
| `JS_NewFloat64` | function | `src/js_env.c:52` | `return JS_NewFloat64(ctx, (double)fp_coarsen_time_ms(wall_clock_ms()));` |
| `JS_NewString` | function | `src/js_env.c:139` | `return JS_NewString(ctx, buf);` |
| `JS_PreventExtensions` | function | `src/js_env.c:194` | `JS_PreventExtensions(ctx, arr);` |
| `JS_ToFloat64` | function | `src/js_env.c:62` | `JS_ToFloat64(ctx, &origin, func_data[0]);` |
| `JS_ToInt32` | function | `src/js_env.c:110` | `JS_ToInt32(ctx, &off32, off_val);` |
| `PERF_ORIGIN_EPOCH` | macro | `src/js_env.c:337` | `#define PERF_ORIGIN_EPOCH` |
| `_POSIX_C_SOURCE` | macro | `src/js_env.c:16` | `#define _POSIX_C_SOURCE` |
| `build_crypto` | function | `src/js_env.c:338` | `static int build_crypto(JSContext *ctx, JSValueConst global)` |
| `build_languages` | function | `src/js_env.c:174` | `static JSValue build_languages(JSContext *ctx)` |
| `build_navigator` | function | `src/js_env.c:197` | `static int build_navigator(JSContext *ctx, JSValueConst global)` |
| `build_perf_navigation` | function | `src/js_env.c:380` | `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)` |
| `build_perf_timing` | function | `src/js_env.c:366` | `static int build_perf_timing(JSContext *ctx, JSValueConst perf)` |
| `build_performance` | function | `src/js_env.c:392` | `static int build_performance(JSContext *ctx, JSValueConst global)` |
| `build_readback_obj` | function | `src/js_env.c:476` | `static int build_readback_obj(JSContext *ctx, JSValueConst global,
                              ...` |
| `build_screen` | function | `src/js_env.c:294` | `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)` |
| `def_fn` | function | `src/js_env.c:166` | `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,
                  JSCFuncti...` |
| `def_int` | function | `src/js_env.c:162` | `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)` |
| `def_str` | function | `src/js_env.c:158` | `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)` |
| `def_val` | function | `src/js_env.c:153` | `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)` |
| `fp_bucket_screen` | function | `src/js_env.c:297` | `fp_bucket_screen(w, h, &bw, &bh);` |
| `fp_perturb` | function | `src/js_env.c:462` | `fp_perturb(copy, size, key);` |
| `free` | function | `src/js_env.c:465` | `free(copy);` |
| `je_install` | function | `src/js_env.c:489` | `je_status je_install(js_context *ctx, int screen_w, int screen_h)` |
| `je_install_canvas` | function | `src/js_env.c:508` | `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)` |
| `m_date_now` | function | `src/js_env.c:48` | `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,
                          int ar...` |
| `m_empty_array` | function | `src/js_env.c:76` | `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,
                             ...` |
| `m_get_random_values` | function | `src/js_env.c:84` | `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,
                       ...` |
| `m_perf_now` | function | `src/js_env.c:57` | `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,
                          int ar...` |
| `m_random_uuid` | function | `src/js_env.c:124` | `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,
                             ...` |
| `m_subtle_null` | function | `src/js_env.c:141` | `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,
                             ...` |
| `make_readback` | function | `src/js_env.c:468` | `static JSValue make_readback(JSContext *ctx, uint64_t key)` |
| `monotonic_ms` | function | `src/js_env.c:40` | `static double monotonic_ms(void)` |
| `override_date_now` | function | `src/js_env.c:425` | `static int override_date_now(JSContext *ctx, JSValueConst global)` |
| `primitives` | function | `src/js_env.c:6` | `* the pure anti_fp primitives (one audited source of normalized constants);` |
| `wall_clock_ms` | function | `src/js_env.c:34` | `static uint64_t wall_clock_ms(void)` |
| `eq_ci` | function | `src/js_policy.c:12` | `static int eq_ci(const char *a, const char *b)` |
| `jsp_enabled` | function | `src/js_policy.c:21` | `bool jsp_enabled(jsp_mode mode, int host_allowlisted)` |
| `jsp_mode_from_str` | function | `src/js_policy.c:38` | `jsp_mode jsp_mode_from_str(const char *s)` |
| `jsp_mode_str` | function | `src/js_policy.c:50` | `const char *jsp_mode_str(jsp_mode mode)` |
| `jsp_present_trusted` | function | `src/js_policy.c:34` | `bool jsp_present_trusted(int host_allowlisted)` |
| `jsp_trusted` | function | `src/js_policy.c:30` | `bool jsp_trusted(bool js_enabled, int host_allowlisted)` |
| `JS_FreeCString` | function | `src/js_sandbox.c:206` | `JS_FreeCString(ctx, cmsg);` |
| `JS_FreeRuntime` | function | `src/js_sandbox.c:293` | `JS_FreeRuntime(c->rt);` |
| `JS_FreeValue` | function | `src/js_sandbox.c:213` | `JS_FreeValue(ctx, JS_GetException(ctx));` |
| `JS_SetInterruptHandler` | function | `src/js_sandbox.c:288` | `JS_SetInterruptHandler(c->rt, js_interrupt_cb, c);` |
| `JS_SetMaxStackSize` | function | `src/js_sandbox.c:287` | `JS_SetMaxStackSize(c->rt, l.max_stack_bytes);` |
| `JS_SetPropertyStr` | function | `src/js_sandbox.c:473` | `JS_SetPropertyStr(jc, doc, "currentScript", JS_NULL);` |
| `_POSIX_C_SOURCE` | macro | `src/js_sandbox.c:11` | `#define _POSIX_C_SOURCE` |
| `arm_deadline` | function | `src/js_sandbox.c:313` | `static void arm_deadline(js_context *ctx, uint64_t budget_ms)` |
| `clock_gettime` | function | `src/js_sandbox.c:109` | `clock_gettime(CLOCK_MONOTONIC, &now);` |
| `free` | function | `src/js_sandbox.c:66` | `free(ptr);` |
| `host_dup` | function | `src/js_sandbox.c:88` | `static char *host_dup(const char *src, size_t len)` |
| `is_ascii_digit` | function | `src/js_sandbox.c:116` | `static int is_ascii_digit(char c)` |
| `jm_calloc` | function | `src/js_sandbox.c:52` | `static void *jm_calloc(void *opaque, size_t count, size_t size)` |
| `jm_free` | function | `src/js_sandbox.c:62` | `static void jm_free(void *opaque, void *ptr)` |
| `jm_malloc` | function | `src/js_sandbox.c:44` | `static void *jm_malloc(void *opaque, size_t size)` |
| `jm_realloc` | function | `src/js_sandbox.c:68` | `static void *jm_realloc(void *opaque, void *ptr, size_t size)` |
| `jm_usable_size` | function | `src/js_sandbox.c:78` | `static size_t jm_usable_size(const void *ptr)` |
| `js_context` | struct | `src/js_sandbox.c:33` | `` |
| `js_context_free` | function | `src/js_sandbox.c:304` | `void js_context_free(js_context *ctx)` |
| `js_context_new` | function | `src/js_sandbox.c:265` | `js_status js_context_new(const js_limits *lim, js_context **out)` |
| `js_context_raw` | function | `src/js_sandbox.c:513` | `void *js_context_raw(js_context *ctx)` |
| `js_eval` | function | `src/js_sandbox.c:333` | `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)` |
| `js_eval_named` | function | `src/js_sandbox.c:337` | `js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        con...` |
| `js_eval_once` | function | `src/js_sandbox.c:438` | `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)` |
| `js_interrupt_cb` | function | `src/js_sandbox.c:104` | `static int js_interrupt_cb(JSRuntime *rt, void *opaque)` |
| `js_limits_default` | function | `src/js_sandbox.c:236` | `js_limits js_limits_default(void)` |
| `js_loc_from_stack` | function | `src/js_sandbox.c:118` | `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      i...` |
| `js_mem_state` | struct | `src/js_sandbox.c:27` | `` |
| `js_pump_jobs` | function | `src/js_sandbox.c:420` | `int js_pump_jobs(js_context *ctx, int max_jobs)` |
| `js_result_free` | function | `src/js_sandbox.c:451` | `void js_result_free(js_result *res)` |
| `js_set_current_script` | function | `src/js_sandbox.c:464` | `void js_set_current_script(js_context *ctx, const char *src, const char *type)` |
| `js_set_time_budget` | function | `src/js_sandbox.c:328` | `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)` |
| `js_validate_source` | function | `src/js_sandbox.c:254` | `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)` |
| `limit` | type_alias | `src/js_sandbox.c:27` | `typedef struct js_mem_state { size_t limit;` |
| `limits_resolve` | function | `src/js_sandbox.c:245` | `static js_limits limits_resolve(const js_limits *lim)` |
| `malloc_usable_size` | function | `src/js_sandbox.c:80` | `return malloc_usable_size((void *)ptr);` |
| `memset` | function | `src/js_sandbox.c:342` | `memset(res, 0, sizeof *res);` |
| `timespec_reached` | function | `src/js_sandbox.c:97` | `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)` |
| `undefined` | function | `src/js_sandbox.c:210` | `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx, exc, ` |
| `append_seg` | function | `src/link_nav.c:86` | `static int append_seg(char *body, size_t bodysz, size_t *blen,
                      const char *...` |
| `ci_prefix` | function | `src/link_nav.c:38` | `static int ci_prefix(const char *s, const char *prefix)` |
| `classify_block` | function | `src/link_nav.c:62` | `static ln_block_reason classify_block(const char *ref)` |
| `clean_href` | function | `src/link_nav.c:19` | `static int clean_href(const char *href, char *out, size_t outsz)` |
| `file_dir_len` | function | `src/link_nav.c:69` | `static size_t file_dir_len(const char *base)` |
| `last_seg_is_dotdot` | function | `src/link_nav.c:79` | `static int last_seg_is_dotdot(const char *body, size_t blen)` |
| `ln_block_reason_text` | function | `src/link_nav.c:240` | `const char *ln_block_reason_text(ln_block_reason reason)` |
| `ln_resolve` | function | `src/link_nav.c:171` | `ln_status ln_resolve(const char *base, const char *href, ln_result *out)` |
| `memcpy` | function | `src/link_nav.c:91` | `memcpy(body + *blen, seg, seglen);` |
| `normalize_file_path` | function | `src/link_nav.c:169` | `return normalize_file_path(merged, out, outsz);` |
| `pop_seg` | function | `src/link_nav.c:98` | `static void pop_seg(char *body, size_t *blen)` |
| `resolve_file` | function | `src/link_nav.c:149` | `static int resolve_file(const char *base, const char *ref, char *out, size_t outsz)` |
| `split_fragment` | function | `src/link_nav.c:187` | `split_fragment(clean, out->fragment, sizeof out->fragment);` |
| `EVP_CIPHER_CTX_free` | function | `src/local_store.c:797` | `done: EVP_CIPHER_CTX_free(ctx);` |
| `EVP_KDF_CTX_free` | function | `src/local_store.c:763` | `EVP_KDF_CTX_free(kctx);` |
| `EVP_KDF_free` | function | `src/local_store.c:744` | `EVP_KDF_free(kdf);` |
| `EVP_aes_256_gcm` | function | `src/local_store.c:730` | `case LS_AEAD_AES256_GCM: return EVP_aes_256_gcm();` |
| `EVP_chacha20_poly1305` | function | `src/local_store.c:731` | `case LS_AEAD_CHACHA20_POLY1305: return EVP_chacha20_poly1305();` |
| `LS_ARGON2_M_KIB` | macro | `src/local_store.c:713` | `#define LS_ARGON2_M_KIB` |
| `LS_ARGON2_P` | macro | `src/local_store.c:714` | `#define LS_ARGON2_P` |
| `LS_ARGON2_T` | macro | `src/local_store.c:712` | `#define LS_ARGON2_T` |
| `LS_KDF_ARGON2ID` | macro | `src/local_store.c:709` | `#define LS_KDF_ARGON2ID` |
| `LS_KDF_NONE` | macro | `src/local_store.c:708` | `#define LS_KDF_NONE` |
| `LS_VERSION` | macro | `src/local_store.c:706` | `#define LS_VERSION` |
| `OFF_AEAD` | macro | `src/local_store.c:719` | `#define OFF_AEAD` |
| `OFF_KDF` | macro | `src/local_store.c:720` | `#define OFF_KDF` |
| `OFF_MAGIC` | macro | `src/local_store.c:717` | `#define OFF_MAGIC` |
| `OFF_NONCE` | macro | `src/local_store.c:722` | `#define OFF_NONCE` |
| `OFF_SALT` | macro | `src/local_store.c:721` | `#define OFF_SALT` |
| `OFF_VERSION` | macro | `src/local_store.c:718` | `#define OFF_VERSION` |
| `OPENSSL_cleanse` | function | `src/local_store.c:848` | `OPENSSL_cleanse(blob, blob_len);` |
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
| `aead_decrypt` | function | `src/local_store.c:801` | `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...` |
| `aead_encrypt` | function | `src/local_store.c:775` | `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...` |
| `argon2id_derive` | function | `src/local_store.c:737` | `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,
                          ...` |
| `cipher_for` | function | `src/local_store.c:727` | `static const EVP_CIPHER *cipher_for(ls_aead aead)` |
| `decrypt_blob` | function | `src/local_store.c:866` | `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,
         ...` |
| `free` | function | `src/local_store.c:849` | `free(blob);` |
| `ls_derive_key` | function | `src/local_store.c:766` | `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,
                        const...` |
| `ls_free` | function | `src/local_store.c:962` | `void ls_free(uint8_t *buf, size_t len)` |
| `ls_open` | function | `src/local_store.c:910` | `ls_status ls_open(const uint8_t key[LS_KEY_LEN],
                  const uint8_t *blob, size_t bl...` |
| `ls_open_passphrase` | function | `src/local_store.c:942` | `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,
                        ...` |
| `ls_seal` | function | `src/local_store.c:897` | `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,
                  const uint8_t *p...` |
| `ls_seal_passphrase` | function | `src/local_store.c:921` | `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,
          ...` |
| `memcpy` | function | `src/local_store.c:840` | `memcpy(blob + OFF_MAGIC, LS_MAGIC, sizeof LS_MAGIC);` |
| `memset` | function | `src/local_store.c:907` | `memset(salt, 0, sizeof salt);` |
| `seal_core` | function | `src/local_store.c:829` | `static ls_status seal_core(const uint8_t *key, ls_aead aead, uint8_t kdf_id,
                    ...` |
| `_POSIX_C_SOURCE` | macro | `src/media_decoder.c:22` | `#define _POSIX_C_SOURCE` |
| `_exit` | function | `src/media_decoder.c:446` | `_exit(0);` |
| `av_frame_free` | function | `src/media_decoder.c:80` | `av_frame_free(&dc->rgb);` |
| `av_frame_unref` | function | `src/media_decoder.c:348` | `av_frame_unref(dc->frame);` |
| `av_free` | function | `src/media_decoder.c:114` | `av_free(avio_buf);` |
| `av_packet_free` | function | `src/media_decoder.c:86` | `av_packet_free(&dc->pkt);` |
| `av_packet_unref` | function | `src/media_decoder.c:338` | `av_packet_unref(dc->pkt);` |
| `av_rescale_q` | function | `src/media_decoder.c:217` | `return av_rescale_q(f->pts, tb, (AVRational)` |
| `avcodec_free_context` | function | `src/media_decoder.c:83` | `avcodec_free_context(&dc->video_codec_ctx);` |
| `avcodec_send_packet` | function | `src/media_decoder.c:423` | `avcodec_send_packet(dc.video_codec_ctx, NULL);` |
| `avformat_close_input` | function | `src/media_decoder.c:85` | `avformat_close_input(&dc->fmt_ctx);` |
| `avformat_free_context` | function | `src/media_decoder.c:115` | `avformat_free_context(dc->fmt_ctx);` |
| `avformat_network_init` | function | `src/media_decoder.c:388` | `avformat_network_init();` |
| `close` | function | `src/media_decoder.c:457` | `close(out_pipe[0]);` |
| `decode_segment` | function | `src/media_decoder.c:276` | `static int decode_segment(decoder_ctx *dc, const uint8_t *data, size_t len)` |
| `decoder_close` | function | `src/media_decoder.c:78` | `static void decoder_close(decoder_ctx *dc)` |
| `decoder_ctx` | struct | `src/media_decoder.c:54` | `` |
| `decoder_init` | function | `src/media_decoder.c:96` | `static int decoder_init(decoder_ctx *dc, const uint8_t *data, size_t len)` |
| `dropped` | function | `src/media_decoder.c:368` | `* the codec in permanent EOF state: every segment after the first decoded * one was silently dropped ("plays a couple of` |
| `execl` | function | `src/media_decoder.c:491` | `execl("/proc/self/exe", "freedom", "--media-decoder", out_str, cmd_str, (char *)NULL);` |
| `fd` | function | `src/media_decoder.c:469` | `* prevent the Wayland display fd (inherited from the parent) from * surviving the exec. An inherited Wayland fd would be` |
| `frame_pts_us` | function | `src/media_decoder.c:215` | `static int64_t frame_pts_us(const AVFrame *f, AVRational tb, int64_t fallback)` |
| `free` | function | `src/media_decoder.c:271` | `free(pcm);` |
| `media_decoder_run` | function | `src/media_decoder.c:378` | `void media_decoder_run(int out_fd, int cmd_fd)` |
| `media_decoder_spawn` | function | `src/media_decoder.c:448` | `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd)` |
| `memcpy` | function | `src/media_decoder.c:105` | `memcpy(avio_buf, data, len);` |
| `memset` | function | `src/media_decoder.c:87` | `memset(dc, 0, sizeof *dc);` |
| `open` | function | `src/media_decoder.c:17` | `*
 * Sandbox: the decoder needs open() for shared libraries (.so loading) and
 * brk/mmap for FFm...` |
| `out_fd` | type_alias | `src/media_decoder.c:53` | `typedef struct decoder_ctx { int out_fd;` |
| `send_audio_frame` | function | `src/media_decoder.c:242` | `static void send_audio_frame(decoder_ctx *dc, int64_t pts_us)` |
| `send_error` | function | `src/media_decoder.c:117` | `send_error(dc->out_fd, "OOM avio_alloc");` |
| `send_video_frame` | function | `src/media_decoder.c:222` | `static void send_video_frame(decoder_ctx *dc, int64_t pts_us)` |
| `signal` | function | `src/media_decoder.c:380` | `signal(SIGPIPE, SIG_IGN);` |
| `sws_scale` | function | `src/media_decoder.c:223` | `sws_scale(dc->sws, (const uint8_t *const *)dc->frame->data, dc->frame->linesize, 0, dc->h, dc->rgb->data, dc->rgb->lines` |
| `write_full` | function | `src/media_decoder.c:47` | `write_full(fd, &tag, 1);` |
| `NR_MAX_HOST` | macro | `src/net_realm.c:14` | `#define NR_MAX_HOST` |
| `ends_with_realm` | function | `src/net_realm.c:23` | `static int ends_with_realm(const char *host, size_t n, const char *suffix)` |
| `host_of` | function | `src/net_realm.c:52` | `static int host_of(const char *url, char *out, size_t out_size)` |
| `lower` | function | `src/net_realm.c:16` | `static char lower(char c)` |
| `memcpy` | function | `src/net_realm.c:63` | `memcpy(out, p, n);` |
| `nr_classify_host` | function | `src/net_realm.c:33` | `nr_realm nr_classify_host(const char *host)` |
| `nr_classify_url` | function | `src/net_realm.c:67` | `nr_realm nr_classify_url(const char *url)` |
| `nr_realm_allows_http` | function | `src/net_realm.c:87` | `int nr_realm_allows_http(nr_realm r)` |
| `nr_realm_name` | function | `src/net_realm.c:93` | `const char *nr_realm_name(nr_realm r)` |
| `nr_route_for` | function | `src/net_realm.c:73` | `nr_route nr_route_for(const char *url, nr_config cfg)` |
| `nr_route_name` | function | `src/net_realm.c:102` | `const char *nr_route_name(nr_route r)` |
| `LL_FS_BASE` | macro | `src/os_sandbox.c:254` | `#define LL_FS_BASE` |
| `OS_ALLOWED_N` | macro | `src/os_sandbox.c:49` | `#define OS_ALLOWED_N` |
| `OS_SECCOMP_ARCH` | macro | `src/os_sandbox.c:140` | `#  define OS_SECCOMP_ARCH` |
| `OS_SECCOMP_ARCH` | macro | `src/os_sandbox.c:142` | `#  define OS_SECCOMP_ARCH` |
| `_GNU_SOURCE` | macro | `src/os_sandbox.c:12` | `#define _GNU_SOURCE` |
| `close` | function | `src/os_sandbox.c:318` | `close(pfd);` |
| `excluded` | function | `src/os_sandbox.c:89` | `* intentionally excluded (they need /proc remounting and a post-unshare fork). */
int os_namespac...` |
| `fields` | function | `src/os_sandbox.c:303` | `* long as the unknown trailing fields (net/scoped) are zero, which they are. */ int rfd = (int)ll_create_ruleset(&attr, ` |
| `headroom` | function | `src/os_sandbox.c:203` | `* wide headroom (room for ~125 allowed syscalls). */ prog[at_mmap].jt = (unsigned char)(prot_check - (at_mmap + 1));` |
| `ll_add_rule` | function | `src/os_sandbox.c:243` | `static long ll_add_rule(int fd, enum landlock_rule_type type,
                        const void ...` |
| `ll_create_ruleset` | function | `src/os_sandbox.c:238` | `static long ll_create_ruleset(const struct landlock_ruleset_attr *attr,
                         ...` |
| `ll_handled` | function | `src/os_sandbox.c:265` | `static uint64_t ll_handled(int abi)` |
| `ll_read_access` | function | `src/os_sandbox.c:278` | `static uint64_t ll_read_access(uint64_t handled)` |
| `ll_restrict_self` | function | `src/os_sandbox.c:248` | `static long ll_restrict_self(int fd, uint32_t flags)` |
| `memset` | function | `src/os_sandbox.c:300` | `memset(&attr, 0, sizeof attr);` |
| `number` | function | `src/os_sandbox.c:157` | `* number (x32/i386 on x86_64, AArch32 on aarch64). */ prog[n++] = (struct sock_filter)BPF_STMT(BPF_LD \| BPF_W \| BPF_AB` |
| `offsetof` | function | `src/os_sandbox.c:165` | `offsetof(struct seccomp_data, nr));` |
| `os_harden` | function | `src/os_sandbox.c:112` | `os_status os_harden(os_violation action)` |
| `os_harden` | function | `src/os_sandbox.c:144` | `os_status os_harden(os_violation action)` |
| `os_isolate_namespaces` | function | `src/os_sandbox.c:93` | `os_status os_isolate_namespaces(void)` |
| `os_isolate_namespaces` | function | `src/os_sandbox.c:116` | `os_status os_isolate_namespaces(void)` |
| `os_landlock_abi` | function | `src/os_sandbox.c:284` | `int os_landlock_abi(void)` |
| `os_landlock_abi` | function | `src/os_sandbox.c:330` | `int os_landlock_abi(void)` |
| `os_landlock_restrict` | function | `src/os_sandbox.c:290` | `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)` |
| `os_landlock_restrict` | function | `src/os_sandbox.c:332` | `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)` |
| `os_namespace_flags` | function | `src/os_sandbox.c:114` | `int os_namespace_flags(void)` |
| `os_no_dump` | function | `src/os_sandbox.c:75` | `os_status os_no_dump(void)` |
| `os_no_dump` | function | `src/os_sandbox.c:111` | `os_status os_no_dump(void)` |
| `os_policy_allows` | function | `src/os_sandbox.c:51` | `int os_policy_allows(long syscall_nr)` |
| `os_policy_allows` | function | `src/os_sandbox.c:105` | `int os_policy_allows(long syscall_nr)` |
| `os_policy_size` | function | `src/os_sandbox.c:58` | `size_t os_policy_size(void)` |
| `os_policy_size` | function | `src/os_sandbox.c:107` | `size_t os_policy_size(void)` |
| `os_prot_allowed` | function | `src/os_sandbox.c:65` | `int os_prot_allowed(long syscall_nr, unsigned long prot)` |
| `os_prot_allowed` | function | `src/os_sandbox.c:108` | `int os_prot_allowed(long syscall_nr, unsigned long prot)` |
| `syscall` | function | `src/os_sandbox.c:241` | `return syscall(__NR_landlock_create_ruleset, attr, size, flags);` |
| `PV_COLOR_TOKEN_MAX` | macro | `src/page_view.c:1019` | `#define PV_COLOR_TOKEN_MAX` |
| `PV_FONT_CHAIN_MAX` | macro | `src/page_view.c:56` | `#define PV_FONT_CHAIN_MAX` |
| `PV_FONT_PCT_MAX` | macro | `src/page_view.c:58` | `#define PV_FONT_PCT_MAX` |
| `PV_FONT_PCT_MIN` | macro | `src/page_view.c:57` | `#define PV_FONT_PCT_MIN` |
| `PV_FONT_REL_MAX` | macro | `src/page_view.c:50` | `#define PV_FONT_REL_MAX` |
| `PV_FONT_REL_MIN` | macro | `src/page_view.c:49` | `#define PV_FONT_REL_MIN` |
| `PV_MAX_BOXES` | macro | `src/page_view.c:1066` | `#define PV_MAX_BOXES` |
| `PV_MAX_CONTAINERS` | macro | `src/page_view.c:1056` | `#define PV_MAX_CONTAINERS` |
| `PV_MAX_DIM` | macro | `src/page_view.c:44` | `#define PV_MAX_DIM` |
| `PV_MAX_GRID_COLS` | macro | `src/page_view.c:1058` | `#define PV_MAX_GRID_COLS` |
| `PV_MAX_INLINE_ROW_ITEMS` | macro | `src/page_view.c:2099` | `#define PV_MAX_INLINE_ROW_ITEMS` |
| `PV_MAX_STYLE_BYTES` | macro | `src/page_view.c:3637` | `#define PV_MAX_STYLE_BYTES` |
| `PV_NODE_MAP_INIT_CAP` | macro | `src/page_view.c:267` | `#define PV_NODE_MAP_INIT_CAP` |
| `_POSIX_C_SOURCE` | macro | `src/page_view.c:9` | `#define _POSIX_C_SOURCE` |
| `address` | function | `src/page_view.c:1069` | `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <= BT_MAX_POS` |
| `alpha_marker` | function | `src/page_view.c:3408` | `case CSS_LS_LOWER_ALPHA: alpha_marker(ord, 0, out, cap);` |
| `annotate_replaced_run` | function | `src/page_view.c:3766` | `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,
                            ...` |
| `appended` | function | `src/page_view.c:5038` | `* AFTER the run is appended (so THIS run's brk stays) but BEFORE the next. */
        if (cont.fl...` |
| `apply_css_replaced_size` | function | `src/page_view.c:4364` | `apply_css_replaced_size(el, sheet, &cache, &iw, &ih);` |
| `ascii_ieq` | function | `src/page_view.c:3075` | `static int ascii_ieq(const char *s, const char *lit)` |
| `attr_dup` | function | `src/page_view.c:3087` | `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)` |
| `bgcolor_attr` | function | `src/page_view.c:1047` | `static int bgcolor_attr(lxb_dom_element_t *el)` |
| `block_id` | function | `src/page_view.c:4526` | `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it falls ` |
| `box_reg_free` | function | `src/page_view.c:1573` | `static void box_reg_free(pv_box_reg *r)` |
| `box_reg_id` | function | `src/page_view.c:1804` | `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,
           ...` |
| `boxdef_from_style` | function | `src/page_view.c:1583` | `static void boxdef_from_style(pv_box_def *d, const css_style *cs)` |
| `builder` | function | `src/page_view.c:2013` | `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box
 * (the ...` |
| `bx_table_role_of` | function | `src/page_view.c:3454` | `return bx_table_role_of(tagp, d);` |
| `causes_block_break` | function | `src/page_view.c:908` | `static int causes_block_break(lxb_tag_id_t t, css_display display)` |
| `cell_anchors` | function | `src/page_view.c:3532` | `static const lxb_dom_node_t *cell_anchors(const lxb_dom_node_t *cell, int *count)` |
| `cell_has_nested_table` | function | `src/page_view.c:3512` | `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)` |
| `child` | function | `src/page_view.c:1077` | `* child (NULL = anonymous item: text directly inside the container);` |
| `classify_input` | function | `src/page_view.c:3168` | `static pv_input_type classify_input(const char *type)` |
| `collapse_ws` | function | `src/page_view.c:2796` | `static char *collapse_ws(const char *s, size_t n)` |
| `collect_page_css` | function | `src/page_view.c:3803` | `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,
                     ...` |
| `collect_style_text` | function | `src/page_view.c:3643` | `static char *collect_style_text(lxb_dom_node_t *root, size_t *outlen)` |
| `collect_text` | function | `src/page_view.c:3145` | `static char *collect_text(const lxb_dom_node_t *el)` |
| `color_attr` | function | `src/page_view.c:1042` | `return color_attr(el, "color", 5);` |
| `cols` | type_alias | `src/page_view.c:1079` | `typedef struct pv_cont_info { int id, display, gap, justify, cols;` |
| `cont_def_reset` | function | `src/page_view.c:1478` | `static void cont_def_reset(pv_cont_def *d)` |
| `container` | function | `src/page_view.c:2542` | `* membership in this container (and none in any container further out,
                 * since i...` |
| `container_id` | function | `src/page_view.c:1492` | `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)` |
| `content` | function | `src/page_view.c:1001` | `* a <noscript> ancestor also suppresses content (the script would run, so the * fallback is hidden);` |
| `control` | function | `src/page_view.c:4218` | `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);` |
| `cp1252_to_ucs` | function | `src/page_view.c:82` | `static unsigned int cp1252_to_ucs(unsigned char c)` |
| `css_free` | function | `src/page_view.c:5106` | `css_free(sheet);` |
| `css_has_boxdeco` | function | `src/page_view.c:1338` | `static int css_has_boxdeco(const css_style *cs)` |
| `css_has_hbox` | function | `src/page_view.c:1277` | `static int css_has_hbox(const css_style *cs)` |
| `css_has_position` | function | `src/page_view.c:1334` | `static int css_has_position(const css_style *cs)` |
| `css_hbox_resolve` | function | `src/page_view.c:1290` | `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)` |
| `css_to_fx_justify` | function | `src/page_view.c:2042` | `static int css_to_fx_justify(css_justify j)` |
| `dimensions` | function | `src/page_view.c:2978` | `* viewport dimensions (data: inline detection, <picture> <source> scanning). */
static void srcse...` |
| `dup_n` | function | `src/page_view.c:142` | `static char *dup_n(const char *s, size_t n)` |
| `engine` | function | `src/page_view.c:4984` | `* layout engine (contiguous item gather) drops every cell onto its own row and
         * a 2-col...` |
| `find_body` | function | `src/page_view.c:3009` | `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)` |
| `float` | function | `src/page_view.c:2712` | `* genuinely nested float (oid != id) takes the deferred-column path. */
    if (cont->float_oid =...` |
| `flow` | function | `src/page_view.c:4886` | `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through it. ` |
| `flow_table` | function | `src/page_view.c:3570` | `static int flow_table(pv_flow_reg *fr, const lxb_dom_node_t *table)` |
| `font_color_attr` | function | `src/page_view.c:1040` | `static int font_color_attr(lxb_dom_element_t *el)` |
| `form_for` | function | `src/page_view.c:3116` | `static int form_for(const form_table *ft, const lxb_dom_node_t *n,
                    const lxb_...` |
| `form_rec` | struct | `src/page_view.c:3057` | `` |
| `form_table` | struct | `src/page_view.c:3063` | `` |
| `forms_add` | function | `src/page_view.c:3096` | `static int forms_add(form_table *ft, const lxb_dom_node_t *node)` |
| `forms_free` | function | `src/page_view.c:3067` | `static void forms_free(form_table *ft)` |
| `free` | function | `src/page_view.c:285` | `free(m->nodes);` |
| `generates_box` | function | `src/page_view.c:888` | `static int generates_box(lxb_tag_id_t t, css_display display)` |
| `generates_box_style` | function | `src/page_view.c:901` | `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)` |
| `glyphs` | function | `src/page_view.c:1710` | `* glyphs (the runs carry it as their fill source);` |
| `heading_level` | function | `src/page_view.c:963` | `static int heading_level(lxb_tag_id_t t)` |
| `height` | function | `src/page_view.c:4436` | `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `here` | function | `src/page_view.c:1672` | `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3 sectio` |
| `id` | function | `src/page_view.c:1097` | `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);` |
| `ignored` | function | `src/page_view.c:574` | `* source is ignored (fail-visible: never invisible text from half a
     * pattern). A real text-...` |
| `in_boilerplate_subtree` | function | `src/page_view.c:3701` | `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` |
| `in_closed_details_subtree` | function | `src/page_view.c:3716` | `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` |
| `in_flow_table_cell` | function | `src/page_view.c:3582` | `static int in_flow_table_cell(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,
           ...` |
| `in_hidden_subtree` | function | `src/page_view.c:3684` | `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
               ...` |
| `in_skipped_subtree` | function | `src/page_view.c:1004` | `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
              ...` |
| `is_block_like` | function | `src/page_view.c:842` | `static int is_block_like(lxb_tag_id_t t, css_display display)` |
| `is_block_like_style` | function | `src/page_view.c:877` | `static int is_block_like_style(lxb_tag_id_t t, const css_style *cs)` |
| `is_block_tag` | function | `src/page_view.c:816` | `static int is_block_tag(lxb_tag_id_t t)` |
| `is_bold_tag` | function | `src/page_view.c:2061` | `static int is_bold_tag(lxb_tag_id_t t)` |
| `is_inline_block_row` | function | `src/page_view.c:2100` | `static int is_inline_block_row(const lxb_dom_node_t *p, const css_sheet *sheet,
                 ...` |
| `is_italic_tag` | function | `src/page_view.c:2066` | `static int is_italic_tag(lxb_tag_id_t t)` |
| `is_out_of_flow` | function | `src/page_view.c:878` | `return is_out_of_flow(cs) \|\| is_block_like(t, cs->display);` |
| `is_skipped_tag` | function | `src/page_view.c:975` | `static int is_skipped_tag(lxb_tag_id_t t)` |
| `it` | function | `src/page_view.c:1183` | `* it (they inherit in CSS). list_style drives the <li> marker (structural);` |
| `item_ordinal` | function | `src/page_view.c:1156` | `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)` |
| `li_ordinal` | function | `src/page_view.c:3348` | `static int li_ordinal(const lxb_dom_node_t *li)` |
| `line` | function | `src/page_view.c:4993` | `* to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);` |
| `link_cont_chain` | function | `src/page_view.c:3794` | `link_cont_chain(reg, items, cont);` |
| `links` | function | `src/page_view.c:3550` | `* its links (the Hacker News case: every story link lives inside a <td>), so the
 * caller flows ...` |
| `list_marker` | function | `src/page_view.c:3399` | `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,
                  ...` |
| `lxb_dom_element_get_attribute` | function | `src/page_view.c:1027` | `lxb_dom_element_get_attribute(el, (const lxb_char_t *)name, name_len, &cl);` |
| `lxb_dom_element_tag_id` | function | `src/page_view.c:997` | `return lxb_dom_element_tag_id(lxb_dom_interface_element((lxb_dom_node_t *)n));` |
| `lxb_dom_interface_element` | function | `src/page_view.c:1914` | `return lxb_dom_interface_element(p);` |
| `margins` | function | `src/page_view.c:2426` | `* margins (boxdef_from_style) and the painter applies them when
                         * it ope...` |
| `mb` | type_alias | `src/page_view.c:1168` | `typedef struct pv_box_info { int l, r, w, center, mt, mb;` |
| `memcpy` | function | `src/page_view.c:1030` | `memcpy(buf, col, cl);` |
| `memset` | function | `src/page_view.c:1479` | `memset(d, 0, sizeof *d);` |
| `nearest_cell` | function | `src/page_view.c:3497` | `static const lxb_dom_node_t *nearest_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
  ...` |
| `nearest_table` | function | `src/page_view.c:3458` | `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
 ...` |
| `next_skip` | function | `src/page_view.c:3521` | `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)` |
| `node_next` | function | `src/page_view.c:807` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `node_table_role` | function | `src/page_view.c:3440` | `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `node_tag` | function | `src/page_view.c:995` | `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)` |
| `opens` | function | `src/page_view.c:2399` | `* painter applies it when the box opens (band/shared context) — seeding
             * it onto ru...` |
| `outermost` | function | `src/page_view.c:2350` | `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);` |
| `paints` | function | `src/page_view.c:917` | `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas
 * vacías"). Comment a...` |
| `paints` | function | `src/page_view.c:2120` | `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas vacías").
 *
 * A chil...` |
| `parent_is_table_internal` | function | `src/page_view.c:3486` | `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `parse_dim` | function | `src/page_view.c:2820` | `static int parse_dim(const lxb_char_t *s, size_t len)` |
| `positions` | function | `src/page_view.c:132` | `* positions (cp == 0) keep the legacy '?' fallback. */ unsigned int cp = cp1252_to_ucs(c);` |
| `present` | function | `src/page_view.c:2837` | `* when no width descriptors are present (density-only or bare URLs). */
static void srcset_best_u...` |
| `pv_add_box_def` | function | `src/page_view.c:755` | `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)` |
| `pv_add_cont_def` | function | `src/page_view.c:733` | `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)` |
| `pv_append` | function | `src/page_view.c:331` | `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    c...` |
| `pv_append_image` | function | `src/page_view.c:365` | `pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          con...` |
| `pv_append_input` | function | `src/page_view.c:395` | `pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_...` |
| `pv_append_svg` | function | `src/page_view.c:471` | `pv_status pv_append_svg(pv_view *v, int heading, int block_break,
                        const c...` |
| `pv_append_video` | function | `src/page_view.c:435` | `pv_status pv_append_video(pv_view *v, int heading, int block_break,
                          con...` |
| `pv_at` | function | `src/page_view.c:789` | `const pv_run *pv_at(const pv_view *v, size_t i)` |
| `pv_box_at` | function | `src/page_view.c:798` | `const pv_box_def *pv_box_at(const pv_view *v, size_t i)` |
| `pv_box_count` | function | `src/page_view.c:794` | `size_t pv_box_count(const pv_view *v)` |
| `pv_box_info` | struct | `src/page_view.c:1168` | `` |
| `pv_box_reg` | struct | `src/page_view.c:1535` | `` |
| `pv_build` | function | `src/page_view.c:3735` | `pv_status pv_build(const hp_document *doc, pv_view **out)` |
| `pv_build_ex` | function | `src/page_view.c:3739` | `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)` |
| `pv_build_full` | function | `src/page_view.c:3743` | `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                     ...` |
| `pv_build_styled` | function | `src/page_view.c:3828` | `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                   ...` |
| `pv_cache_find` | function | `src/page_view.c:1872` | `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cache_put` | function | `src/page_view.c:1887` | `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,
                     ...` |
| `pv_cached_font_px` | function | `src/page_view.c:1883` | `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cont_at` | function | `src/page_view.c:750` | `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)` |
| `pv_cont_count` | function | `src/page_view.c:746` | `size_t pv_cont_count(const pv_view *v)` |
| `pv_cont_info` | struct | `src/page_view.c:1079` | `` |
| `pv_container_reg` | struct | `src/page_view.c:1468` | `` |
| `pv_content_hidden` | function | `src/page_view.c:1187` | `int pv_content_hidden(int box_hidden, int run_visibility)` |
| `pv_count` | function | `src/page_view.c:785` | `size_t pv_count(const pv_view *v)` |
| `pv_css_drops` | function | `src/page_view.c:5128` | `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,
                       const cha...` |
| `pv_flow_reg` | struct | `src/page_view.c:2148` | `` |
| `pv_flow_reg` | struct | `src/page_view.c:3426` | `` |
| `pv_free` | function | `src/page_view.c:768` | `void pv_free(pv_view *v)` |
| `pv_item_track` | struct | `src/page_view.c:1149` | `` |
| `pv_new` | function | `src/page_view.c:327` | `pv_view *pv_new(void)` |
| `pv_node_map` | struct | `src/page_view.c:269` | `` |
| `pv_node_map_build` | function | `src/page_view.c:319` | `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root)` |
| `pv_node_map_free` | function | `src/page_view.c:282` | `static void pv_node_map_free(pv_node_map *m)` |
| `pv_node_map_init` | function | `src/page_view.c:274` | `static int pv_node_map_init(pv_node_map *m)` |
| `pv_parent_element` | function | `src/page_view.c:1911` | `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)` |
| `pv_set_bgcolor` | function | `src/page_view.c:517` | `void pv_set_bgcolor(pv_view *v, int bg_rgb)` |
| `pv_set_block_id` | function | `src/page_view.c:705` | `void pv_set_block_id(pv_view *v, int block_id)` |
| `pv_set_box` | function | `src/page_view.c:671` | `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                int box_center, int ...` |
| `pv_set_box_pct` | function | `src/page_view.c:683` | `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,
                    ...` |
| `pv_set_color` | function | `src/page_view.c:512` | `void pv_set_color(pv_view *v, int fg_rgb)` |
| `pv_set_cont_box` | function | `src/page_view.c:628` | `void pv_set_cont_box(pv_view *v, int cont_box_id)` |
| `pv_set_cont_item` | function | `src/page_view.c:644` | `void pv_set_cont_item(pv_view *v, int cont_item)` |
| `pv_set_container` | function | `src/page_view.c:588` | `void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_g...` |
| `pv_set_emphasis` | function | `src/page_view.c:500` | `void pv_set_emphasis(pv_view *v, int bold, int italic)` |
| `pv_set_flex` | function | `src/page_view.c:632` | `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                 int...` |
| `pv_set_float` | function | `src/page_view.c:649` | `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear,
                int ...` |
| `pv_set_grad_text` | function | `src/page_view.c:533` | `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)` |
| `pv_set_grid` | function | `src/page_view.c:614` | `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)` |
| `pv_set_grid_area` | function | `src/page_view.c:607` | `void pv_set_grid_area(pv_view *v, int row_start, int col_start)` |
| `pv_set_grid_rows` | function | `src/page_view.c:624` | `void pv_set_grid_rows(pv_view *v, int grid_rows)` |
| `pv_set_indent` | function | `src/page_view.c:507` | `void pv_set_indent(pv_view *v, int indent)` |
| `pv_set_input_checked` | function | `src/page_view.c:720` | `void pv_set_input_checked(pv_view *v, int checked)` |
| `pv_set_input_select_opts` | function | `src/page_view.c:725` | `void pv_set_input_select_opts(pv_view *v, const char *select_opts)` |
| `pv_set_node_id` | function | `src/page_view.c:700` | `void pv_set_node_id(pv_view *v, dom_node_id node_id)` |
| `pv_set_oof` | function | `src/page_view.c:715` | `void pv_set_oof(pv_view *v, int oof)` |
| `pv_set_own_box` | function | `src/page_view.c:710` | `void pv_set_own_box(pv_view *v, int box_id)` |
| `pv_set_row_span` | function | `src/page_view.c:603` | `void pv_set_row_span(pv_view *v, int row_span)` |
| `pv_set_text_ext` | function | `src/page_view.c:541` | `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)` |
| `pv_set_text_style` | function | `src/page_view.c:522` | `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,
                ...` |
| `pv_set_ua_tag` | function | `src/page_view.c:694` | `void pv_set_ua_tag(pv_view *v, int ua_tag)` |
| `pv_style_cache` | struct | `src/page_view.c:1837` | `` |
| `pv_style_cache_free` | function | `src/page_view.c:1861` | `static void pv_style_cache_free(pv_style_cache *c)` |
| `pv_style_cache_init` | function | `src/page_view.c:1847` | `static int pv_style_cache_init(pv_style_cache *c)` |
| `pv_text_ext_merge` | function | `src/page_view.c:1219` | `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)` |
| `pv_text_ext_reset` | function | `src/page_view.c:1192` | `void pv_text_ext_reset(pv_text_ext *e)` |
| `px` | function | `src/page_view.c:4369` | `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */
                if (iw <...` |
| `resolve_context` | function | `src/page_view.c:2151` | `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                ...` |
| `resolves` | function | `src/page_view.c:867` | `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close
 * button/tooltip w...` |
| `roman_marker` | function | `src/page_view.c:3374` | `static void roman_marker(int n, int upper, char *out, size_t cap)` |
| `run_init_common` | function | `src/page_view.c:157` | `static void run_init_common(pv_run *r)` |
| `serialize_subtree` | function | `src/page_view.c:2776` | `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)` |
| `size` | function | `src/page_view.c:1993` | `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */
static void app...` |
| `snprintf` | function | `src/page_view.c:3404` | `case CSS_LS_DISC: snprintf(out, cap, "\xE2\x80\xA2 ");` |
| `srcset_best_url` | function | `src/page_view.c:4456` | `srcset_best_url(srcset, ssl, sw, &img_src, &img_src_len);` |
| `srcset_first_url` | function | `src/page_view.c:4460` | `srcset_first_url(srcset, ssl, &img_src, &img_src_len);` |
| `srcset_slot_width` | function | `src/page_view.c:2932` | `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,
                              ...` |
| `string` | function | `src/page_view.c:3020` | `* Returns a heap string (caller frees) or NULL when neither carries a class —
 * NULL simply mean...` |
| `strlen` | function | `src/page_view.c:4880` | `strlen(pcs.content_after_str));` |
| `subtree_is_oof` | function | `src/page_view.c:1973` | `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,
                     ...` |
| `sz_count` | function | `src/page_view.c:2755` | `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)` |
| `sz_fill` | struct | `src/page_view.c:2763` | `` |
| `sz_write` | function | `src/page_view.c:2768` | `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)` |
| `table` | function | `src/page_view.c:3592` | `* FLOW table (multi-link: walked so its links survive) do NOT suppress their
 * content -- their ...` |
| `table_columns` | function | `src/page_view.c:3610` | `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)` |
| `trying` | function | `src/page_view.c:1545` | `* a real page passes without trying (slashdot's front page saturates it), and past
 * it box_reg_...` |
| `ua_tag_of` | function | `src/page_view.c:942` | `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)` |
| `under_unrendered` | function | `src/page_view.c:3132` | `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)` |
| `utf8_encode` | function | `src/page_view.c:96` | `static size_t utf8_encode(unsigned int cp, char *out)` |
| `utf8_sanitized_dup` | function | `src/page_view.c:108` | `static char *utf8_sanitized_dup(const char *s)` |
| `walk` | function | `src/page_view.c:2625` | `* far on this walk (they are all inside this element). */

                        /* The innermo...` |
| `memcpy` | function | `src/pdf_export.c:61` | `memcpy(out, name, name_len);` |
| `pe_build_path` | function | `src/pdf_export.c:90` | `pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz)` |
| `pe_build_path_ext` | function | `src/pdf_export.c:65` | `pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,
                ...` |
| `pe_paginate` | function | `src/pdf_export.c:94` | `size_t pe_paginate(const double *tops, const double *heights, size_t n,
                   double...` |
| `pe_safe_basename` | function | `src/pdf_export.c:24` | `pe_status pe_safe_basename(const char *title, char *out, size_t outsz)` |
| `PT_LINE_CAP` | macro | `src/perf_trace.c:107` | `#define PT_LINE_CAP` |
| `cmp_u64` | function | `src/perf_trace.c:70` | `static int cmp_u64(const void *a, const void *b)` |
| `memcpy` | function | `src/perf_trace.c:84` | `memcpy(sorted, s->samples, s->fill * sizeof(uint64_t));` |
| `memset` | function | `src/perf_trace.c:18` | `memset(t, 0, sizeof(*t));` |
| `pt_count` | function | `src/perf_trace.c:34` | `size_t pt_count(const pt_trace *t, pt_stage stage)` |
| `pt_elapsed_us` | function | `src/perf_trace.c:20` | `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us)` |
| `pt_format` | function | `src/perf_trace.c:108` | `size_t pt_format(const pt_trace *t, char *buf, size_t cap)` |
| `pt_init` | function | `src/perf_trace.c:15` | `void pt_init(pt_trace *t)` |
| `pt_last_us` | function | `src/perf_trace.c:39` | `uint64_t pt_last_us(const pt_trace *t, pt_stage stage)` |
| `pt_max_us` | function | `src/perf_trace.c:59` | `uint64_t pt_max_us(const pt_trace *t, pt_stage stage)` |
| `pt_median_us` | function | `src/perf_trace.c:78` | `uint64_t pt_median_us(const pt_trace *t, pt_stage stage)` |
| `pt_min_us` | function | `src/perf_trace.c:48` | `uint64_t pt_min_us(const pt_trace *t, pt_stage stage)` |
| `pt_record` | function | `src/perf_trace.c:25` | `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us)` |
| `pt_stage_name` | function | `src/perf_trace.c:88` | `const char *pt_stage_name(pt_stage stage)` |
| `qsort` | function | `src/perf_trace.c:85` | `qsort(sorted, s->fill, sizeof(uint64_t), cmp_u64);` |
| `PF_MAX_URL` | macro | `src/prefetch.c:21` | `#define PF_MAX_URL` |
| `_POSIX_C_SOURCE` | macro | `src/prefetch.c:11` | `#define _POSIX_C_SOURCE` |
| `attr_span` | struct | `src/prefetch.c:62` | `` |
| `ci_eq_span` | function | `src/prefetch.c:54` | `static int ci_eq_span(const char *s, size_t n, const char *kw)` |
| `ci_find` | function | `src/prefetch.c:46` | `static const char *ci_find(const char *p, const char *end, const char *kw)` |
| `ci_starts` | function | `src/prefetch.c:37` | `static int ci_starts(const char *p, const char *end, const char *kw)` |
| `emit` | function | `src/prefetch.c:116` | `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)` |
| `free` | function | `src/prefetch.c:302` | `free(j->body);` |
| `is_name_char` | function | `src/prefetch.c:26` | `static int is_name_char(char c)` |
| `is_ws` | function | `src/prefetch.c:22` | `static int is_ws(char c)` |
| `lower` | function | `src/prefetch.c:31` | `static int lower(int c)` |
| `memcpy` | function | `src/prefetch.c:123` | `memcpy(u, val, vlen);` |
| `memset` | function | `src/prefetch.c:230` | `memset(p, 0, sizeof *p);` |
| `pf_list_free` | function | `src/prefetch.c:192` | `void pf_list_free(pf_list *l)` |
| `pf_pool_finish` | function | `src/prefetch.c:309` | `void pf_pool_finish(pf_pool *p)` |
| `pf_pool_start` | function | `src/prefetch.c:226` | `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                  pf_fetch_f...` |
| `pf_pool_take` | function | `src/prefetch.c:270` | `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,
                 char **body,...` |
| `pf_pooled_fetch` | function | `src/prefetch.c:323` | `int pf_pooled_fetch(void *vctx, const char *method, const char *url,
                    const ch...` |
| `pf_scan` | function | `src/prefetch.c:129` | `int pf_scan(const char *html, size_t len, pf_list *out)` |
| `pf_worker` | function | `src/prefetch.c:200` | `static void *pf_worker(void *arg)` |
| `pthread_cond_broadcast` | function | `src/prefetch.c:221` | `pthread_cond_broadcast(&p->done_cv);` |
| `pthread_cond_destroy` | function | `src/prefetch.c:263` | `pthread_cond_destroy(&p->done_cv);` |
| `pthread_cond_init` | function | `src/prefetch.c:248` | `pthread_cond_init(&p->done_cv, NULL);` |
| `pthread_join` | function | `src/prefetch.c:313` | `pthread_join(p->threads[i], NULL);` |
| `pthread_mutex_destroy` | function | `src/prefetch.c:262` | `pthread_mutex_destroy(&p->lock);` |
| `pthread_mutex_init` | function | `src/prefetch.c:246` | `pthread_mutex_init(&p->lock, NULL);` |
| `pthread_mutex_lock` | function | `src/prefetch.c:204` | `pthread_mutex_lock(&p->lock);` |
| `pthread_mutex_unlock` | function | `src/prefetch.c:207` | `pthread_mutex_unlock(&p->lock);` |
| `PREFS_MAGIC` | macro | `src/prefs.c:19` | `#define PREFS_MAGIC` |
| `_POSIX_C_SOURCE` | macro | `src/prefs.c:10` | `#define _POSIX_C_SOURCE` |
| `apply_kv` | function | `src/prefs.c:225` | `static void apply_kv(prefs_state *out, const char *key, long val)` |
| `bookmark_push` | function | `src/prefs.c:91` | `static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title)` |
| `ci_contains` | function | `src/prefs.c:313` | `static int ci_contains(const char *s, const char *q)` |
| `ci_eq` | function | `src/prefs.c:299` | `static int ci_eq(char a, char b)` |
| `ci_starts` | function | `src/prefs.c:305` | `static int ci_starts(const char *s, const char *q)` |
| `free` | function | `src/prefs.c:77` | `free(p->bookmarks[i].url);` |
| `history_push_back` | function | `src/prefs.c:109` | `static prefs_status history_push_back(prefs_state *p, const char *url)` |
| `memcpy` | function | `src/prefs.c:255` | `memcpy(head, line, ll);` |
| `memmove` | function | `src/prefs.c:140` | `memmove(&p->bookmarks[idx], &p->bookmarks[idx + 1], (p->bookmarks_len - (size_t)idx - 1) * sizeof p->bookmarks[0]);` |
| `memset` | function | `src/prefs.c:68` | `memset(p, 0, sizeof *p);` |
| `prefs_bookmark_index` | function | `src/prefs.c:124` | `int prefs_bookmark_index(const prefs_state *p, const char *url)` |
| `prefs_bookmark_toggle` | function | `src/prefs.c:131` | `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,
                             ...` |
| `prefs_bookmarks_page` | function | `src/prefs.c:407` | `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)` |
| `prefs_format` | function | `src/prefs.c:182` | `prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len)` |
| `prefs_free` | function | `src/prefs.c:73` | `void prefs_free(prefs_state *p)` |
| `prefs_history_add` | function | `src/prefs.c:151` | `prefs_status prefs_history_add(prefs_state *p, const char *url)` |
| `prefs_init` | function | `src/prefs.c:65` | `void prefs_init(prefs_state *p)` |
| `prefs_parse` | function | `src/prefs.c:240` | `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)` |
| `prefs_suggest` | function | `src/prefs.c:343` | `int prefs_suggest(const prefs_state *p, const char *query,
                  char *out, size_t ro...` |
| `sb_esc` | function | `src/prefs.c:387` | `static void sb_esc(sbuf *b, const char *s)` |
| `sb_link_item` | function | `src/prefs.c:399` | `static void sb_link_item(sbuf *b, const char *url, const char *label)` |
| `sb_put` | function | `src/prefs.c:368` | `static void sb_put(sbuf *b, const char *s, size_t n)` |
| `sb_str` | function | `src/prefs.c:383` | `static void sb_str(sbuf *b, const char *s)` |
| `sbuf` | struct | `src/prefs.c:367` | `` |
| `sugg_push` | function | `src/prefs.c:335` | `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,
                      cons...` |
| `title_clean` | function | `src/prefs.c:39` | `static char *title_clean(const char *src)` |
| `url_prefix_match` | function | `src/prefs.c:323` | `static int url_prefix_match(const char *url, const char *q)` |
| `url_valid` | function | `src/prefs.c:26` | `static int url_valid(const char *url)` |
| `OPENSSL_cleanse` | function | `src/profile.c:92` | `OPENSSL_cleanse(kf, sizeof kf);` |
| `PROFILE_KEYFILE_LEN` | macro | `src/profile.c:26` | `#define PROFILE_KEYFILE_LEN` |
| `_POSIX_C_SOURCE` | macro | `src/profile.c:10` | `#define _POSIX_C_SOURCE` |
| `close` | function | `src/profile.c:47` | `close(fd);` |
| `ds_free` | function | `src/profile.c:127` | `ds_free(pt, pt_len);` |
| `join_path` | function | `src/profile.c:28` | `static int join_path(const profile_ctx *ctx, const char *name,
                     char *out, si...` |
| `keyfile_create` | function | `src/profile.c:36` | `static profile_status keyfile_create(const char *dir, const char *path,
                         ...` |
| `ls_free` | function | `src/profile.c:145` | `ls_free((uint8_t *)text, len);` |
| `map_ds` | function | `src/profile.c:97` | `static profile_status map_ds(ds_status ds)` |
| `memcpy` | function | `src/profile.c:66` | `memcpy(ctx->dir, dir, dlen + 1);` |
| `memset` | function | `src/profile.c:61` | `memset(ctx, 0, sizeof *ctx);` |
| `profile_close` | function | `src/profile.c:148` | `void profile_close(profile_ctx *ctx)` |
| `profile_load` | function | `src/profile.c:111` | `profile_status profile_load(const profile_ctx *ctx, prefs_state *out)` |
| `profile_open` | function | `src/profile.c:58` | `profile_status profile_open(profile_ctx *ctx, const char *dir)` |
| `profile_save` | function | `src/profile.c:132` | `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p)` |
| `unlink` | function | `src/profile.c:48` | `unlink(tmp);` |
| `free` | function | `src/render_doc.c:680` | `free(d->blocks[i].text);` |
| `memcpy` | function | `src/render_doc.c:626` | `memcpy(d->boxes[i].bg_image_url, img_url, ulen + 1);` |
| `place` | function | `src/render_doc.c:216` | `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never resolved,` |
| `rd_at` | function | `src/render_doc.c:696` | `const rd_block *rd_at(const rd_doc *d, size_t i)` |
| `rd_block_tag` | function | `src/render_doc.c:733` | `const char *rd_block_tag(const rd_block *b)` |
| `rd_box_at` | function | `src/render_doc.c:705` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)` |
| `rd_box_count` | function | `src/render_doc.c:701` | `size_t rd_box_count(const rd_doc *d)` |
| `rd_build` | function | `src/render_doc.c:248` | `rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_u...` |
| `rd_cont_at` | function | `src/render_doc.c:714` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)` |
| `rd_cont_count` | function | `src/render_doc.c:710` | `size_t rd_cont_count(const rd_doc *d)` |
| `rd_count` | function | `src/render_doc.c:692` | `size_t rd_count(const rd_doc *d)` |
| `rd_free` | function | `src/render_doc.c:676` | `void rd_free(rd_doc *d)` |
| `rd_image_fail_label` | function | `src/render_doc.c:794` | `const char *rd_image_fail_label(img_fail_reason reason)` |
| `rd_image_label` | function | `src/render_doc.c:783` | `const char *rd_image_label(rdp_img_decision d)` |
| `rd_input_label` | function | `src/render_doc.c:764` | `const char *rd_input_label(int input_type)` |
| `rd_kind_name` | function | `src/render_doc.c:719` | `const char *rd_kind_name(rd_kind k)` |
| `rd_push` | function | `src/render_doc.c:60` | `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,
                 ...` |
| `rd_push_input` | function | `src/render_doc.c:192` | `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` |
| `rdp_image_decision` | function | `src/render_doc.c:246` | `return rdp_image_decision(caps, top_level_url, *out_url, w, h);` |
| `resolve_image_decision` | function | `src/render_doc.c:227` | `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,
        ...` |
| `unset` | function | `src/render_doc.c:612` | `* background paints as if unset (no border/box-shadow-style
                 * "broken image" pla...` |
| `utf8_sanitized_dup` | function | `src/render_doc.c:26` | `static char *utf8_sanitized_dup(const char *s)` |
| `rdp_caps_safe` | function | `src/render_policy.c:16` | `rdp_caps rdp_caps_safe(void)` |
| `rdp_image_decision` | function | `src/render_policy.c:27` | `rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char...` |
| `rdp_images_warning` | function | `src/render_policy.c:73` | `const char *rdp_images_warning(void)` |
| `rdp_img_reason` | function | `src/render_policy.c:62` | `const char *rdp_img_reason(rdp_img_decision d)` |
| `rdp_is_tracking_pixel` | function | `src/render_policy.c:21` | `int rdp_is_tracking_pixel(int w, int h)` |
| `_POSIX_C_SOURCE` | macro | `src/renderer.c:6` | `#define _POSIX_C_SOURCE` |
| `_exit` | function | `src/renderer.c:48` | `_exit(ok ? 0 : 92);` |
| `child_render` | function | `src/renderer.c:24` | `static void child_render(int wfd, const char *html, size_t len)` |
| `close` | function | `src/renderer.c:80` | `close(fds[0]);` |
| `free` | function | `src/renderer.c:106` | `free(title);` |
| `hp_document_free` | function | `src/renderer.c:47` | `hp_document_free(doc);` |
| `hp_free` | function | `src/renderer.c:44` | `hp_free(title);` |
| `memset` | function | `src/renderer.c:72` | `memset(out, 0, sizeof *out);` |
| `os_no_dump` | function | `src/renderer.c:29` | `os_no_dump();` |
| `rd_render_html` | function | `src/renderer.c:69` | `rd_status rd_render_html(const char *html, size_t len, rd_result *out)` |
| `rd_result_free` | function | `src/renderer.c:119` | `void rd_result_free(rd_result *out)` |
| `read_field` | function | `src/renderer.c:52` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `write_full` | function | `src/renderer.c:40` | `&& write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 \|\| write_full(wfd, title, tl) == 0) && write_full(wfd, &xl, sizeof` |
| `RP_MAX_HOST` | macro | `src/request_policy.c:16` | `#define RP_MAX_HOST` |
| `RP_MAX_LABELS` | macro | `src/request_policy.c:18` | `#define RP_MAX_LABELS` |
| `ci_starts_with` | function | `src/request_policy.c:25` | `static int ci_starts_with(const char *s, const char *prefix)` |
| `lower` | function | `src/request_policy.c:21` | `static char lower(char c)` |
| `memcpy` | function | `src/request_policy.c:130` | `memcpy(out, site, n + 1);` |
| `psl_cmp` | function | `src/request_policy.c:35` | `static int psl_cmp(const void *key, const void *elem)` |
| `psl_in` | function | `src/request_policy.c:39` | `static int psl_in(const char *const *arr, size_t n, const char *key)` |
| `public_suffix_labels` | function | `src/request_policy.c:48` | `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)` |
| `rp_evaluate` | function | `src/request_policy.c:142` | `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)` |
| `rp_host_of` | function | `src/request_policy.c:75` | `int rp_host_of(const char *url, char *out, size_t out_size)` |
| `rp_same_site` | function | `src/request_policy.c:133` | `int rp_same_site(const char *top_level_url, const char *request_url)` |
| `rp_site_of` | function | `src/request_policy.c:101` | `int rp_site_of(const char *host, char *out, size_t out_size)` |
| `strcmp` | function | `src/request_policy.c:37` | `return strcmp((const char *)key, *(const char *const *)elem);` |
| `OBJ_nid2sn` | function | `src/secure_fetch.c:507` | `return OBJ_nid2sn(nid);` |
| `OBJ_obj2txt` | function | `src/secure_fetch.c:666` | `OBJ_obj2txt(sigbuf, (int)sigbuf_len, aobj, 0);` |
| `STACK_OF` | function | `src/secure_fetch.c:622` | `STACK_OF(X509) *chain = SSL_get0_verified_chain(ssl);` |
| `X509_ALGOR_get0` | function | `src/secure_fetch.c:664` | `X509_ALGOR_get0(&aobj, NULL, NULL, alg);` |
| `X509_get0_signature` | function | `src/secure_fetch.c:661` | `X509_get0_signature(NULL, &alg, cert);` |
| `_POSIX_C_SOURCE` | macro | `src/secure_fetch.c:11` | `#define _POSIX_C_SOURCE` |
| `body_sink` | struct | `src/secure_fetch.c:433` | `` |
| `ci_index` | function | `src/secure_fetch.c:55` | `static long ci_index(const char *haystack, const char *needle)` |
| `ci_starts_with` | function | `src/secure_fetch.c:43` | `static int ci_starts_with(const char *haystack, const char *prefix)` |
| `copy_bounded` | function | `src/secure_fetch.c:468` | `static void copy_bounded(char *dst, size_t dstsz, const char *src)` |
| `copy_checked` | function | `src/secure_fetch.c:323` | `static int copy_checked(char *dst, size_t dstsz, const char *src)` |
| `curl_easy_cleanup` | function | `src/secure_fetch.c:190` | `curl_easy_cleanup(h);` |
| `curl_easy_getinfo` | function | `src/secure_fetch.c:176` | `curl_easy_getinfo(h, CURLINFO_COOKIELIST, &list);` |
| `curl_easy_setopt` | function | `src/secure_fetch.c:173` | `curl_easy_setopt(h, CURLOPT_SHARE, sf_share);` |
| `curl_global_init` | function | `src/secure_fetch.c:83` | `curl_global_init(CURL_GLOBAL_DEFAULT);` |
| `curl_share_setopt` | function | `src/secure_fetch.c:89` | `curl_share_setopt(sf_share, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);` |
| `curl_slist_free_all` | function | `src/secure_fetch.c:189` | `curl_slist_free_all(list);` |
| `database` | function | `src/secure_fetch.c:484` | `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid handsha` |
| `fetch_ctx` | struct | `src/secure_fetch.c:456` | `` |
| `free` | function | `src/secure_fetch.c:412` | `free(resp->tls_version);` |
| `get_negotiated_group_name` | function | `src/secure_fetch.c:480` | `static const char *get_negotiated_group_name(SSL *ssl)` |
| `group` | function | `src/secure_fetch.c:498` | `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);` |
| `header_cb` | function | `src/secure_fetch.c:543` | `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` |
| `inspect_chain` | function | `src/secure_fetch.c:621` | `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` |
| `map_curl_error` | function | `src/secure_fetch.c:673` | `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)` |
| `memcpy` | function | `src/secure_fetch.c:133` | `memcpy(eb, f[4], el);` |
| `memset` | function | `src/secure_fetch.c:217` | `memset(&c, 0, sizeof c);` |
| `module` | function | `src/secure_fetch.c:363` | `* pure url module (DRY);` |
| `name_is_pq_sig` | function | `src/secure_fetch.c:611` | `static int name_is_pq_sig(int pknid)` |
| `progress` | function | `src/secure_fetch.c:442` | `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);` |
| `pthread_mutex_lock` | function | `src/secure_fetch.c:70` | `pthread_mutex_lock(&sf_cookie_lock);` |
| `pthread_mutex_unlock` | function | `src/secure_fetch.c:75` | `pthread_mutex_unlock(&sf_cookie_lock);` |
| `redirect` | function | `src/secure_fetch.c:832` | `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...` |
| `sf_check_chain_policy` | function | `src/secure_fetch.c:282` | `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)` |
| `sf_check_group_is_pq` | function | `src/secure_fetch.c:273` | `sf_status sf_check_group_is_pq(const char *negotiated_group)` |
| `sf_check_tls_version` | function | `src/secure_fetch.c:268` | `sf_status sf_check_tls_version(const char *negotiated_version)` |
| `sf_ci_prefix` | function | `src/secure_fetch.c:370` | `static int sf_ci_prefix(const char *s, const char *p)` |
| `sf_config_default` | function | `src/secure_fetch.c:214` | `sf_config sf_config_default(void)` |
| `sf_cookie_header_for` | function | `src/secure_fetch.c:164` | `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)` |
| `sf_cookie_line_matches` | function | `src/secure_fetch.c:94` | `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...` |
| `sf_cookie_put` | function | `src/secure_fetch.c:193` | `void sf_cookie_put(const char *url, const char *namevalue)` |
| `sf_enforce_policy` | function | `src/secure_fetch.c:292` | `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...` |
| `sf_get` | function | `src/secure_fetch.c:988` | `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)` |
| `sf_get_follow` | function | `src/secure_fetch.c:1006` | `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...` |
| `sf_global_init` | function | `src/secure_fetch.c:79` | `void sf_global_init(void)` |
| `sf_impersonate_kex_groups` | function | `src/secure_fetch.c:243` | `const char *sf_impersonate_kex_groups(void)` |
| `sf_impersonate_tls13_ciphers` | function | `src/secure_fetch.c:245` | `const char *sf_impersonate_tls13_ciphers(void)` |
| `sf_is_redirect_code` | function | `src/secure_fetch.c:332` | `int sf_is_redirect_code(long http_code)` |
| `sf_parse_location_header` | function | `src/secure_fetch.c:339` | `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)` |
| `sf_perform` | function | `src/secure_fetch.c:716` | `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...` |
| `sf_post` | function | `src/secure_fetch.c:992` | `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...` |
| `sf_resolve_redirect` | function | `src/secure_fetch.c:357` | `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...` |
| `sf_response_free` | function | `src/secure_fetch.c:409` | `void sf_response_free(sf_response *resp)` |
| `sf_share_lock` | function | `src/secure_fetch.c:66` | `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...` |
| `sf_share_unlock` | function | `src/secure_fetch.c:72` | `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)` |
| `sf_url_host_path` | function | `src/secure_fetch.c:150` | `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...` |
| `sf_url_is_http` | function | `src/secure_fetch.c:257` | `static int sf_url_is_http(const char *url)` |
| `sf_user_agent_or_default` | function | `src/secure_fetch.c:239` | `const char *sf_user_agent_or_default(const char *ua)` |
| `sf_validate_url` | function | `src/secure_fetch.c:248` | `sf_status sf_validate_url(const char *url)` |
| `sink` | type_alias | `src/secure_fetch.c:455` | `typedef struct fetch_ctx { body_sink sink;` |
| `this` | function | `src/secure_fetch.c:524` | `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and causes` |
| `tls_capture` | struct | `src/secure_fetch.c:446` | `` |
| `tls_capture_try` | function | `src/secure_fetch.c:511` | `static void tls_capture_try(tls_capture *cap)` |
| `void` | function | `src/secure_fetch.c:464` | `void (*progress_cb)(const uint8_t *body, size_t body_len, void *ctx);` |
| `write_cb` | function | `src/secure_fetch.c:578` | `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)` |
| `SV_MAX_ATTRS` | macro | `src/svg_render.c:95` | `#define SV_MAX_ATTRS` |
| `memcpy` | function | `src/svg_render.c:124` | `memcpy(dst, s, n);` |
| `memset` | function | `src/svg_render.c:327` | `memset(sh, 0, sizeof *sh);` |
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
| `sv_fit` | function | `src/svg_render.c:742` | `void sv_fit(const sv_image *img, double dw, double dh,
            double *scale, double *off_x, ...` |
| `sv_is_digit` | function | `src/svg_render.c:24` | `static int sv_is_digit(char c)` |
| `sv_is_dropped_element` | function | `src/svg_render.c:635` | `static int sv_is_dropped_element(const char *name, size_t n)` |
| `sv_is_space` | function | `src/svg_render.c:20` | `static int sv_is_space(char c)` |
| `sv_lower` | function | `src/svg_render.c:26` | `static char sv_lower(char c)` |
| `sv_mat_identity` | function | `src/svg_render.c:160` | `static void sv_mat_identity(double *m)` |
| `sv_mat_mul` | function | `src/svg_render.c:166` | `static void sv_mat_mul(const double *a, const double *b, double *out)` |
| `sv_new_seg` | function | `src/svg_render.c:362` | `static sv_seg *sv_new_seg(sv_image *im, sv_shape *sh)` |
| `sv_new_shape` | function | `src/svg_render.c:323` | `static sv_shape *sv_new_shape(sv_image *im, int kind, const sv_ctx *ctx)` |
| `sv_parse` | function | `src/svg_render.c:762` | `sv_status sv_parse(const char *markup, size_t len, sv_image *out)` |
| `sv_parse_ex` | function | `src/svg_render.c:766` | `sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill)` |
| `sv_parse_path` | function | `src/svg_render.c:477` | `static void sv_parse_path(sv_image *im, sv_shape *sh, const char *s, size_t n)` |
| `sv_parse_points` | function | `src/svg_render.c:343` | `static void sv_parse_points(sv_image *im, sv_shape *sh, const char *s, size_t n)` |
| `sv_parse_transform` | function | `src/svg_render.c:179` | `static void sv_parse_transform(const char *s, size_t n, double *m)` |
| `sv_scan_attrs` | function | `src/svg_render.c:647` | `static void sv_scan_attrs(const char *s, size_t n, size_t *i,
                          sv_attr *...` |
| `sv_seg_cubic` | function | `src/svg_render.c:384` | `static int sv_seg_cubic(sv_image *im, sv_shape *sh,
                        double x1, double y1,...` |
| `sv_seg_line` | function | `src/svg_render.c:377` | `static int sv_seg_line(sv_image *im, sv_shape *sh, double x, double y)` |
| `sv_seg_move` | function | `src/svg_render.c:370` | `static int sv_seg_move(sv_image *im, sv_shape *sh, double x, double y)` |
| `sv_sep` | function | `src/svg_render.c:82` | `static void sv_sep(const char *s, size_t n, size_t *i)` |
| `sv_skip_subtree` | function | `src/svg_render.c:693` | `static void sv_skip_subtree(const char *s, size_t n, size_t *i, const char *name, size_t nlen)` |
| `sv_span_eq` | function | `src/svg_render.c:32` | `static int sv_span_eq(const char *s, size_t n, const char *lit)` |
| `sv_style_next` | function | `src/svg_render.c:238` | `static int sv_style_next(const char *s, size_t n, size_t *i,
                         const char ...` |
| `EPIPE` | function | `src/tab.c:1377` | `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();` |
| `FB_MAX_FILE_BYTES` | function | `src/tab.c:638` | `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...` |
| `PV_MAX_CONTAINERS_WIRE` | macro | `src/tab.c:61` | `#define PV_MAX_CONTAINERS_WIRE` |
| `TAB_MAX_EXTERN_CSS` | macro | `src/tab.c:711` | `#define TAB_MAX_EXTERN_CSS` |
| `TAB_MAX_JS_JOBS` | macro | `src/tab.c:81` | `#define TAB_MAX_JS_JOBS` |
| `TAB_MAX_RUNS` | macro | `src/tab.c:57` | `#define TAB_MAX_RUNS` |
| `TAB_MAX_SUBREQ` | macro | `src/tab.c:79` | `#define TAB_MAX_SUBREQ` |
| `TAB_MAX_SUBRESOURCE` | macro | `src/tab.c:80` | `#define TAB_MAX_SUBRESOURCE` |
| `TAB_MAX_URL` | macro | `src/tab.c:64` | `#define TAB_MAX_URL` |
| `TAB_SCREEN_H` | macro | `src/tab.c:53` | `#define TAB_SCREEN_H` |
| `TAB_SCREEN_W` | macro | `src/tab.c:52` | `#define TAB_SCREEN_W` |
| `_GNU_SOURCE` | macro | `src/tab.c:13` | `#define _GNU_SOURCE` |
| `_exit` | function | `src/tab.c:1408` | `_exit(hs == TAB_READY ? 0 : 70);` |
| `answered` | function | `src/tab.c:2213` | `* A refused frame is still consumed and answered (status 0), so the protocol never
 * desyncs. Re...` |
| `blocks` | function | `src/tab.c:279` | `*
 * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the
 * grid arr...` |
| `budget_remaining_ms` | function | `src/tab.c:668` | `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` |
| `buffer` | function | `src/tab.c:223` | `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of run_j` |
| `child_fetch_stylesheets` | function | `src/tab.c:822` | `child_fetch_stylesheets(cs);` |
| `child_handle_click` | function | `src/tab.c:1157` | `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_decode_image` | function | `src/tab.c:1321` | `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` |
| `child_handle_decode_image_b64` | function | `src/tab.c:1343` | `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)` |
| `child_handle_eval` | function | `src/tab.c:1288` | `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` |
| `child_handle_event` | function | `src/tab.c:1171` | `static void child_handle_event(int wfd, child_state *cs)` |
| `child_handle_load` | function | `src/tab.c:794` | `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...` |
| `child_handle_mouse` | function | `src/tab.c:1220` | `static void child_handle_mouse(int wfd, child_state *cs)` |
| `child_handle_mutation` | function | `src/tab.c:1091` | `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...` |
| `child_handle_submit` | function | `src/tab.c:1254` | `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_tick` | function | `src/tab.c:1161` | `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)` |
| `child_next_timer_ms` | function | `src/tab.c:1076` | `static int32_t child_next_timer_ms(child_state *cs)` |
| `child_reset_page` | function | `src/tab.c:110` | `static void child_reset_page(child_state *cs)` |
| `child_state` | struct | `src/tab.c:89` | `` |
| `clock_gettime` | function | `src/tab.c:670` | `clock_gettime(CLOCK_MONOTONIC, &now);` |
| `close` | function | `src/tab.c:2129` | `close(req[0]);` |
| `close_range` | function | `src/tab.c:2107` | `close_range(3, ~0U, CLOSE_RANGE_CLOEXEC);` |
| `column` | function | `src/tab.c:1770` | `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation as te` |
| `content` | function | `src/tab.c:984` | `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video> elements i` |
| `ctype_is_css` | function | `src/tab.c:691` | `static int ctype_is_css(const char *ctype)` |
| `ctype_is_javascript` | function | `src/tab.c:682` | `static int ctype_is_javascript(const char *ctype)` |
| `depth` | function | `src/tab.c:1398` | `* defense in depth (seccomp already excludes open/socket/exec);` |
| `dom_free` | function | `src/tab.c:197` | `dom_free(idx);` |
| `exec_worker_child` | function | `src/tab.c:2103` | `static void exec_worker_child(int rfd, int wfd)` |
| `execv` | function | `src/tab.c:2117` | `execv("/proc/self/exe", av);` |
| `fallback` | function | `src/tab.c:864` | `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it even ` |
| `fb_buffer_free` | function | `src/tab.c:1511` | `fb_buffer_free(&cs.log);` |
| `fb_buffer_init` | function | `src/tab.c:2335` | `fb_buffer_init(&console);` |
| `fb_buffer_reset` | function | `src/tab.c:1296` | `fb_buffer_reset(&cs->log);` |
| `free` | function | `src/tab.c:116` | `free(cs->extern_css);` |
| `gen_session_key` | function | `src/tab.c:1354` | `static uint64_t gen_session_key(void)` |
| `host` | function | `src/tab.c:235` | `* granted net access for this host (allow.conf AND js.conf). Otherwise they stay * undefined (Same-Origin-by-constructio` |
| `hp_free` | function | `src/tab.c:1069` | `hp_free(title);` |
| `hp_free_scripts` | function | `src/tab.c:963` | `hp_free_scripts(scripts, nscripts);` |
| `hp_free_stylesheet_hrefs` | function | `src/tab.c:790` | `hp_free_stylesheet_hrefs(hrefs, nhrefs);` |
| `ignore_sigpipe` | function | `src/tab.c:1570` | `static void ignore_sigpipe(void)` |
| `img_pixels_free` | function | `src/tab.c:1335` | `img_pixels_free(&px);` |
| `inject_video_into_view` | function | `src/tab.c:1031` | `inject_video_into_view(cs, &cs->preserved_view);` |
| `io_failure` | function | `src/tab.c:2094` | `static tab_status io_failure(tab *t)` |
| `js_context_free` | function | `src/tab.c:212` | `js_context_free(js);` |
| `js_result_free` | function | `src/tab.c:955` | `js_result_free(&r);` |
| `js_set_current_script` | function | `src/tab.c:947` | `js_set_current_script(cs->js, scripts[i].src, scripts[i].type);` |
| `js_set_time_budget` | function | `src/tab.c:900` | `js_set_time_budget(cs->js, rem);` |
| `kill` | function | `src/tab.c:2161` | `kill(pid, SIGKILL);` |
| `layout` | function | `src/tab.c:1760` | `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property. */ pv` |
| `load` | function | `src/tab.c:1557` | `* subresource requests this load (set per page: host in allow.conf AND js.conf);` |
| `log_external_skip` | function | `src/tab.c:699` | `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...` |
| `memcpy` | function | `src/tab.c:784` | `memcpy(cs->extern_css + cs->extern_css_len, body, blen);` |
| `memset` | function | `src/tab.c:950` | `memset(&r, 0, sizeof r);` |
| `once` | function | `src/tab.c:1029` | `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);` |
| `os_isolate_namespaces` | function | `src/tab.c:1403` | `os_isolate_namespaces();` |
| `os_landlock_restrict` | function | `src/tab.c:1405` | `os_landlock_restrict(NULL, 0);` |
| `os_no_dump` | function | `src/tab.c:1404` | `os_no_dump();` |
| `parse_worker_fd` | function | `src/tab.c:1518` | `static int parse_worker_fd(const char *s, int *out)` |
| `policy` | function | `src/tab.c:126` | `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a
 * compromi...` |
| `pv_append_video` | function | `src/tab.c:737` | `pv_append_video(*vp, 0, 1, NULL, src, NULL, -1, -1);` |
| `pv_free` | function | `src/tab.c:119` | `pv_free(cs->preserved_view);` |
| `pv_set_bgcolor` | function | `src/tab.c:1736` | `pv_set_bgcolor(v, (int)bg);` |
| `pv_set_block_id` | function | `src/tab.c:1796` | `pv_set_block_id(v, (int)blkid);` |
| `pv_set_box` | function | `src/tab.c:1758` | `pv_set_box(v, (int)bl, (int)br, (int)bw, (int)bcenter, (int)bmt, (int)bmb);` |
| `pv_set_color` | function | `src/tab.c:1735` | `pv_set_color(v, (int)fg);` |
| `pv_set_cont_box` | function | `src/tab.c:1742` | `pv_set_cont_box(v, (int)b[33]);` |
| `pv_set_cont_item` | function | `src/tab.c:1753` | `pv_set_cont_item(v, (int)citem);` |
| `pv_set_container` | function | `src/tab.c:1739` | `pv_set_container(v, (int)cid, (int)cdisp, (int)cgap, (int)cjust, (int)ccols, (int)cwrap, (int)crgap, (int)calign);` |
| `pv_set_emphasis` | function | `src/tab.c:1733` | `pv_set_emphasis(v, (int)bold, (int)italic);` |
| `pv_set_flex` | function | `src/tab.c:1751` | `pv_set_flex(v, (int)fgrow, (int)fshrink, (int)fbasis, (int)forder, (int)fdir, (int)fself);` |
| `pv_set_float` | function | `src/tab.c:1754` | `pv_set_float(v, (int)flside, (int)flid, (int)flclear, (int)flml, (int)flmlpct, (int)flmr, (int)flmrpct, (int)floid, (int` |
| `pv_set_grad_text` | function | `src/tab.c:1729` | `pv_set_grad_text(v, (int)b[27], (int)b[28], gtc);` |
| `pv_set_grid` | function | `src/tab.c:1746` | `pv_set_grid(v, gw, PV_GRID_TRACKS, (int)gtw[PV_GRID_TRACKS]);` |
| `pv_set_grid_area` | function | `src/tab.c:1749` | `pv_set_grid_area(v, (int)b[40], (int)b[41]);` |
| `pv_set_grid_rows` | function | `src/tab.c:1741` | `pv_set_grid_rows(v, (int)crows);` |
| `pv_set_indent` | function | `src/tab.c:1734` | `pv_set_indent(v, (int)indent);` |
| `pv_set_input_checked` | function | `src/tab.c:1700` | `pv_set_input_checked(v, (int)ckd);` |
| `pv_set_node_id` | function | `src/tab.c:1797` | `pv_set_node_id(v, (dom_node_id)nodeid);` |
| `pv_set_oof` | function | `src/tab.c:1806` | `pv_set_oof(v, (int)b[43]);` |
| `pv_set_own_box` | function | `src/tab.c:1803` | `pv_set_own_box(v, (int)b[42]);` |
| `pv_set_row_span` | function | `src/tab.c:1747` | `pv_set_row_span(v, (int)b[26]);` |
| `pv_set_text_ext` | function | `src/tab.c:1724` | `pv_set_text_ext(v, &e);` |
| `pv_set_text_style` | function | `src/tab.c:1737` | `pv_set_text_style(v, (int)talign, (int)fscale, (int)fabs_flag, (int)lscale, (int)deco);` |
| `pv_set_ua_tag` | function | `src/tab.c:1800` | `pv_set_ua_tag(v, (int)b[35]);` |
| `pv_text_ext_reset` | function | `src/tab.c:1709` | `pv_text_ext_reset(&e);` |
| `read_console` | function | `src/tab.c:2048` | `static int read_console(int fd, fb_buffer *out)` |
| `read_field` | function | `src/tab.c:1596` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `read_view` | function | `src/tab.c:1612` | `static int read_view(int fd, pv_view **out)` |
| `run` | function | `src/tab.c:717` | `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...` |
| `run_js` | function | `src/tab.c:180` | `* regardless of run_js (a no-JS load simply never records a request). */
static int child_load(ch...` |
| `send_request` | function | `src/tab.c:2085` | `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` |
| `sigaction` | function | `src/tab.c:1574` | `sigaction(SIGPIPE, &sa, NULL);` |
| `swap` | function | `src/tab.c:1038` | `* display:none hiding an element via class swap (CSS, not
     * DOM removal). */
    if (ok && v...` |
| `tab` | struct | `src/tab.c:1550` | `` |
| `tab_alive` | function | `src/tab.c:2685` | `int tab_alive(const tab *t)` |
| `tab_child_pid` | function | `src/tab.c:2691` | `pid_t tab_child_pid(const tab *t)` |
| `tab_click` | function | `src/tab.c:2402` | `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)` |
| `tab_close` | function | `src/tab.c:2695` | `void tab_close(tab *t)` |
| `tab_decode_image` | function | `src/tab.c:2661` | `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)` |
| `tab_decode_image_data_url` | function | `src/tab.c:2667` | `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)` |
| `tab_decode_image_op` | function | `src/tab.c:2620` | `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...` |
| `tab_eval` | function | `src/tab.c:2579` | `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)` |
| `tab_eval_result_free` | function | `src/tab.c:2726` | `void tab_eval_result_free(tab_eval_result *r)` |
| `tab_image_free` | function | `src/tab.c:2735` | `void tab_image_free(tab_image *img)` |
| `tab_load` | function | `src/tab.c:2248` | `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)` |
| `tab_load_ex` | function | `src/tab.c:2252` | `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)` |
| `tab_load_full` | function | `src/tab.c:2256` | `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...` |
| `tab_mutation_request` | function | `src/tab.c:2406` | `return tab_mutation_request(t, OP_CLICK, (int32_t)node_id, out);` |
| `tab_page_free` | function | `src/tab.c:2708` | `void tab_page_free(tab_page *p)` |
| `tab_parse_worker_args` | function | `src/tab.c:1529` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)` |
| `tab_read_view` | function | `src/tab.c:2524` | `tab_status tab_read_view(tab *t, tab_page *out)` |
| `tab_refresh_alive` | function | `src/tab.c:1576` | `static void tab_refresh_alive(tab *t)` |
| `tab_set_cookies` | function | `src/tab.c:2194` | `void tab_set_cookies(tab *t, const char *cookies)` |
| `tab_set_css_allowed` | function | `src/tab.c:2184` | `void tab_set_css_allowed(tab *t, int allowed)` |
| `tab_set_fetcher` | function | `src/tab.c:2173` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)` |
| `tab_set_net_allowed` | function | `src/tab.c:2179` | `void tab_set_net_allowed(tab *t, int allowed)` |
| `tab_set_viewport_w` | function | `src/tab.c:2189` | `void tab_set_viewport_w(tab *t, int px)` |
| `tab_submit` | function | `src/tab.c:2419` | `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` |
| `tab_subreq_permitted` | function | `src/tab.c:2200` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)` |
| `tab_tick` | function | `src/tab.c:2409` | `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)` |
| `tab_worker_dispatch` | function | `src/tab.c:1539` | `void tab_worker_dispatch(int argc, char **argv)` |
| `tab_worker_run` | function | `src/tab.c:1375` | `static void tab_worker_run(int rfd, int wfd)` |
| `tzset` | function | `src/tab.c:1393` | `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);` |
| `window` | function | `src/tab.c:750` | `* net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs)` |
| `write_field` | function | `src/tab.c:247` | `static int write_field(int fd, const char *s)` |
| `write_full` | function | `src/tab.c:1058` | `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 \|\| write_full(wfd, text, xl) == 0) && write_view(wfd, write_which)` |
| `FT_Done_Face` | function | `src/text_shape.c:129` | `FT_Done_Face(ft);` |
| `FT_Done_FreeType` | function | `src/text_shape.c:73` | `FT_Done_FreeType(g_ft);` |
| `FcConfigSubstitute` | function | `src/text_shape.c:102` | `FcConfigSubstitute(NULL, pat, FcMatchPattern);` |
| `FcDefaultSubstitute` | function | `src/text_shape.c:103` | `FcDefaultSubstitute(pat);` |
| `FcInit` | function | `src/text_shape.c:69` | `FcInit();` |
| `FcPatternAddInteger` | function | `src/text_shape.c:100` | `FcPatternAddInteger(pat, FC_WEIGHT, bold ? FC_WEIGHT_BOLD : FC_WEIGHT_NORMAL);` |
| `FcPatternDestroy` | function | `src/text_shape.c:106` | `FcPatternDestroy(pat);` |
| `FcPatternGetInteger` | function | `src/text_shape.c:115` | `FcPatternGetInteger(match, FC_INDEX, 0, &index);` |
| `TSH_CACHE_SLOTS` | macro | `src/text_shape.c:32` | `#define TSH_CACHE_SLOTS` |
| `TSH_MAX_FONT_BYTES` | macro | `src/text_shape.c:28` | `#define TSH_MAX_FONT_BYTES` |
| `_POSIX_C_SOURCE` | macro | `src/text_shape.c:11` | `#define _POSIX_C_SOURCE` |
| `backend_init` | function | `src/text_shape.c:63` | `static int backend_init(void)` |
| `cairo_font_face_destroy` | function | `src/text_shape.c:141` | `cairo_font_face_destroy(cf);` |
| `cairo_set_font_face` | function | `src/text_shape.c:232` | `cairo_set_font_face(cr, e->cface);` |
| `cairo_set_font_size` | function | `src/text_shape.c:234` | `cairo_set_font_size(cr, px);` |
| `cairo_show_glyphs` | function | `src/text_shape.c:239` | `cairo_show_glyphs(cr, g_scratch, (int)n);` |
| `fclose` | function | `src/text_shape.c:91` | `fclose(fp);` |
| `free` | function | `src/text_shape.c:123` | `free(bytes);` |
| `generic_name` | function | `src/text_shape.c:53` | `static const char *generic_name(int family)` |
| `get_entry` | function | `src/text_shape.c:151` | `static tsh_entry *get_entry(int family, int bold, int italic)` |
| `hb_blob_destroy` | function | `src/text_shape.c:140` | `hb_blob_destroy(blob);` |
| `hb_buffer_add_utf8` | function | `src/text_shape.c:190` | `hb_buffer_add_utf8(g_buf, text, (int)len, 0, (int)len);` |
| `hb_buffer_guess_segment_properties` | function | `src/text_shape.c:191` | `hb_buffer_guess_segment_properties(g_buf);` |
| `hb_buffer_reset` | function | `src/text_shape.c:188` | `hb_buffer_reset(g_buf);` |
| `hb_font_set_scale` | function | `src/text_shape.c:187` | `hb_font_set_scale(e->hbfont, scale, scale);` |
| `hb_shape` | function | `src/text_shape.c:192` | `hb_shape(e->hbfont, g_buf, NULL, 0);` |
| `load_entry` | function | `src/text_shape.c:96` | `static int load_entry(tsh_entry *e, int family, int bold, int italic)` |
| `loaded` | type_alias | `src/text_shape.c:33` | `typedef struct tsh_entry { int loaded;` |
| `memset` | function | `src/text_shape.c:253` | `memset(e, 0, sizeof *e);` |
| `read_font_file` | function | `src/text_shape.c:80` | `static unsigned char *read_font_file(const char *path, long *out_n)` |
| `tsh_draw` | function | `src/text_shape.c:220` | `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, doub...` |
| `tsh_entry` | struct | `src/text_shape.c:34` | `` |
| `tsh_measure` | function | `src/text_shape.c:213` | `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)` |
| `tsh_ready` | function | `src/text_shape.c:163` | `int tsh_ready(void)` |
| `tsh_shape` | function | `src/text_shape.c:168` | `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                ...` |
| `tsh_shutdown` | function | `src/text_shape.c:242` | `void tsh_shutdown(void)` |
| `memcpy` | function | `src/textfield.c:28` | `memcpy(f->buf, s, n);` |
| `memmove` | function | `src/textfield.c:39` | `memmove(f->buf + f->cursor + 1, f->buf + f->cursor, f->len - f->cursor);` |
| `tf_backspace` | function | `src/textfield.c:46` | `void tf_backspace(tf_field *f)` |
| `tf_clear` | function | `src/textfield.c:19` | `void tf_clear(tf_field *f)` |
| `tf_cursor` | function | `src/textfield.c:90` | `size_t tf_cursor(const tf_field *f)` |
| `tf_delete` | function | `src/textfield.c:54` | `void tf_delete(tf_field *f)` |
| `tf_end` | function | `src/textfield.c:77` | `void tf_end(tf_field *f)` |
| `tf_home` | function | `src/textfield.c:72` | `void tf_home(tf_field *f)` |
| `tf_init` | function | `src/textfield.c:21` | `tf_init(f);` |
| `tf_insert` | function | `src/textfield.c:34` | `tf_status tf_insert(tf_field *f, char c)` |
| `tf_len` | function | `src/textfield.c:86` | `size_t tf_len(const tf_field *f)` |
| `tf_move` | function | `src/textfield.c:61` | `void tf_move(tf_field *f, long delta)` |
| `tf_set` | function | `src/textfield.c:23` | `tf_status tf_set(tf_field *f, const char *s)` |
| `tf_text` | function | `src/textfield.c:82` | `const char *tf_text(const tf_field *f)` |
| `whole` | function | `src/textfield.c:6` | `* the buffer is rejected whole (fail closed), never applied partially.
 */

#include "textfield.h...` |
| `bounded_len` | function | `src/tls_impersonate.c:24` | `static size_t bounded_len(const char *s, size_t max)` |
| `free` | function | `src/tls_impersonate.c:157` | `free(url);` |
| `get_bytes` | function | `src/tls_impersonate.c:89` | `static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len)` |
| `get_str` | function | `src/tls_impersonate.c:103` | `static char *get_str(ti_rd *r, size_t cap)` |
| `get_u32` | function | `src/tls_impersonate.c:69` | `static uint32_t get_u32(ti_rd *r)` |
| `get_u64` | function | `src/tls_impersonate.c:79` | `static uint64_t get_u64(ti_rd *r)` |
| `get_u8` | function | `src/tls_impersonate.c:64` | `static uint8_t get_u8(ti_rd *r)` |
| `memcpy` | function | `src/tls_impersonate.c:97` | `memcpy(b, r->p + r->off, n);` |
| `memset` | function | `src/tls_impersonate.c:142` | `memset(out, 0, sizeof *out);` |
| `put_blob` | function | `src/tls_impersonate.c:52` | `static void put_blob(ti_wr *w, const uint8_t *b, size_t n)` |
| `put_u32` | function | `src/tls_impersonate.c:39` | `static void put_u32(ti_wr *w, uint32_t v)` |
| `put_u64` | function | `src/tls_impersonate.c:47` | `static void put_u64(ti_wr *w, uint64_t v)` |
| `put_u8` | function | `src/tls_impersonate.c:34` | `static void put_u8(ti_wr *w, uint8_t v)` |
| `ti_decode_req` | function | `src/tls_impersonate.c:139` | `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out)` |
| `ti_decode_resp` | function | `src/tls_impersonate.c:195` | `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out)` |
| `ti_encode_req` | function | `src/tls_impersonate.c:121` | `size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap)` |
| `ti_encode_resp` | function | `src/tls_impersonate.c:176` | `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap)` |
| `ti_rd` | struct | `src/tls_impersonate.c:63` | `` |
| `ti_req_free` | function | `src/tls_impersonate.c:165` | `void ti_req_free(ti_req *r)` |
| `ti_resp_free` | function | `src/tls_impersonate.c:229` | `void ti_resp_free(ti_resp *r)` |
| `ti_should_impersonate` | function | `src/tls_impersonate.c:17` | `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,
                          i...` |
| `ti_wr` | struct | `src/tls_impersonate.c:33` | `` |
| `valid_profile` | function | `src/tls_impersonate.c:115` | `static int valid_profile(int p)` |
| `free` | function | `src/ui_layout.c:93` | `free(lay->lines);` |
| `layout_push` | function | `src/ui_layout.c:12` | `static int layout_push(ui_layout *lay, size_t offset, size_t len)` |
| `ui_clamp_scroll` | function | `src/ui_layout.c:98` | `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines)` |
| `ui_layout_free` | function | `src/ui_layout.c:90` | `void ui_layout_free(ui_layout *lay)` |
| `ui_wrap_text` | function | `src/ui_layout.c:26` | `ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out)` |
| `_POSIX_C_SOURCE` | macro | `src/url.c:8` | `#define _POSIX_C_SOURCE` |
| `append_query_encoded` | function | `src/url.c:226` | `static int append_query_encoded(char *out, size_t outsz, const char *src)` |
| `assumed` | function | `src/url.c:251` | `* assumed (the caller already routed whitespace to search). */
static int looks_like_host(const c...` |
| `build_search` | function | `src/url.c:299` | `static url_status build_search(const char *query, char *out, size_t outsz)` |
| `cat_checked` | function | `src/url.c:39` | `static int cat_checked(char *out, size_t outsz, const char *src)` |
| `ci_prefix` | function | `src/url.c:19` | `static int ci_prefix(const char *haystack, const char *prefix)` |
| `copy_checked` | function | `src/url.c:31` | `static int copy_checked(char *out, size_t outsz, const char *src)` |
| `dir_len` | function | `src/url.c:156` | `static size_t dir_len(const char *base)` |
| `host_equals` | function | `src/url.c:375` | `static int host_equals(const url_parts *p, const char *want)` |
| `is_space` | function | `src/url.c:214` | `static int is_space(int c)` |
| `is_unreserved` | function | `src/url.c:218` | `static int is_unreserved(int c)` |
| `memcpy` | function | `src/url.c:34` | `memcpy(out, src, n + 1);` |
| `memset` | function | `src/url.c:584` | `memset(out, 0, sizeof *out);` |
| `ncat_checked` | function | `src/url.c:48` | `static int ncat_checked(char *out, size_t outsz, const char *src, size_t n)` |
| `out_pop_segment` | function | `src/url.c:99` | `static void out_pop_segment(char *out, size_t *olen)` |
| `query_find_q` | function | `src/url.c:390` | `static const char *query_find_q(const char *search, size_t len, size_t *vlen)` |
| `url_authority_len` | function | `src/url.c:89` | `size_t url_authority_len(const char *url)` |
| `url_extract_userinfo` | function | `src/url.c:427` | `url_status url_extract_userinfo(const char *url, char *out, size_t outsz,
                       ...` |
| `url_file_path` | function | `src/url.c:527` | `const char *url_file_path(const char *s)` |
| `url_has_scheme` | function | `src/url.c:57` | `int url_has_scheme(const char *s)` |
| `url_is_file` | function | `src/url.c:521` | `int url_is_file(const char *s)` |
| `url_is_https` | function | `src/url.c:71` | `int url_is_https(const char *s)` |
| `url_omnibox` | function | `src/url.c:305` | `url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz)` |
| `url_remove_dot_segments` | function | `src/url.c:105` | `url_status url_remove_dot_segments(const char *path, char *out, size_t outsz)` |
| `url_resolve_file` | function | `src/url.c:531` | `url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz)` |
| `url_resolve_https` | function | `src/url.c:166` | `url_status url_resolve_https(const char *base, const char *ref,
                             char...` |
| `url_search_rewrite` | function | `src/url.c:407` | `url_status url_search_rewrite(const char *url, char *out, size_t outsz)` |
| `url_split` | function | `src/url.c:580` | `url_status url_split(const char *url, url_parts *out)` |
| `url_validate_https` | function | `src/url.c:78` | `url_status url_validate_https(const char *url)` |
| `wc_derive` | function | `src/webcaps.c:14` | `wc_caps wc_derive(wc_input in)` |
| `wc_from_flags` | function | `src/webcaps.c:34` | `wc_caps wc_from_flags(bool js, bool css, bool images)` |
| `wc_render_caps` | function | `src/webcaps.c:45` | `rdp_caps wc_render_caps(wc_caps c)` |
| `wc_safe` | function | `src/webcaps.c:9` | `wc_caps wc_safe(void)` |
| `ZM_LADDER_N` | macro | `src/zoom.c:12` | `#define ZM_LADDER_N` |
| `zm_apply` | function | `src/zoom.c:43` | `double zm_apply(double base_px, int pct)` |
| `zm_clamp` | function | `src/zoom.c:13` | `int zm_clamp(int pct)` |
| `zm_reset` | function | `src/zoom.c:35` | `int zm_reset(void)` |
| `zm_scale` | function | `src/zoom.c:39` | `double zm_scale(int pct)` |
| `zm_zoom_in` | function | `src/zoom.c:19` | `int zm_zoom_in(int pct)` |
| `zm_zoom_out` | function | `src/zoom.c:27` | `int zm_zoom_out(int pct)` |
| `CHECK` | macro | `tests/itest_secure_fetch.c:15` | `#define CHECK(cond, msg)` |
| `CHECK` | function | `tests/itest_secure_fetch.c:32` | `CHECK(s0 == SF_ERR_INVALID_URL, "rejects http:// scheme before any I/O");` |
| `main` | function | `tests/itest_secure_fetch.c:25` | `int main(void)` |
| `printf` | function | `tests/itest_secure_fetch.c:19` | `printf(" ok : %s\n", (msg));` |
| `sf_response_free` | function | `tests/itest_secure_fetch.c:33` | `sf_response_free(&r0);` |
| `assert_int_equal` | function | `tests/test_anti_fp.c:22` | `assert_int_equal((int)fp_coarsen_time_ms(0), 0);` |
| `assert_memory_equal` | function | `tests/test_anti_fp.c:108` | `assert_memory_equal(a, b, sizeof a);` |
| `assert_memory_not_equal` | function | `tests/test_anti_fp.c:133` | `assert_memory_not_equal(a, b, sizeof a);` |
| `assert_non_null` | function | `tests/test_anti_fp.c:36` | `assert_non_null(fp_user_agent());` |
| `assert_null` | function | `tests/test_anti_fp.c:40` | `assert_null(strstr(fp_user_agent(), "Freedom"));` |
| `assert_string_equal` | function | `tests/test_anti_fp.c:42` | `assert_string_equal(fp_user_agent(), FP_USER_AGENT);` |
| `assert_true` | function | `tests/test_anti_fp.c:21` | `assert_true(res > 0);` |
| `cmocka_run_group_tests` | function | `tests/test_anti_fp.c:214` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `fp_bucket_screen` | function | `tests/test_anti_fp.c:86` | `fp_bucket_screen(1920, 1080, &w, &h);` |
| `fp_perturb` | function | `tests/test_anti_fp.c:106` | `fp_perturb(a, sizeof a, 0xABCDEF1234567890ULL);` |
| `main` | function | `tests/test_anti_fp.c:196` | `int main(void)` |
| `memcpy` | function | `tests/test_anti_fp.c:105` | `memcpy(b, a, sizeof b);` |
| `memset` | function | `tests/test_anti_fp.c:104` | `memset(a, 0x80, sizeof a);` |
| `test_boolean_props` | function | `tests/test_anti_fp.c:73` | `static void test_boolean_props(void **state)` |
| `test_bucket_screen` | function | `tests/test_anti_fp.c:82` | `static void test_bucket_screen(void **state)` |
| `test_coarsen_time` | function | `tests/test_anti_fp.c:17` | `static void test_coarsen_time(void **state)` |
| `test_identity_is_fixed` | function | `tests/test_anti_fp.c:33` | `static void test_identity_is_fixed(void **state)` |
| `test_legacy_identity_fixed` | function | `tests/test_anti_fp.c:60` | `static void test_legacy_identity_fixed(void **state)` |
| `test_origin_key_deterministic` | function | `tests/test_anti_fp.c:145` | `static void test_origin_key_deterministic(void **state)` |
| `test_origin_key_empty_namespace` | function | `tests/test_anti_fp.c:170` | `static void test_origin_key_empty_namespace(void **state)` |
| `test_origin_key_per_session` | function | `tests/test_anti_fp.c:164` | `static void test_origin_key_per_session(void **state)` |
| `test_origin_key_per_site` | function | `tests/test_anti_fp.c:152` | `static void test_origin_key_per_site(void **state)` |
| `test_origin_key_unlinks_readback` | function | `tests/test_anti_fp.c:183` | `static void test_origin_key_unlinks_readback(void **state)` |
| `test_perturb_bounded_lsb` | function | `tests/test_anti_fp.c:110` | `static void test_perturb_bounded_lsb(void **state)` |
| `test_perturb_deterministic` | function | `tests/test_anti_fp.c:100` | `static void test_perturb_deterministic(void **state)` |
| `test_perturb_key_sensitive` | function | `tests/test_anti_fp.c:125` | `static void test_perturb_key_sensitive(void **state)` |
| `test_perturb_safe_edges` | function | `tests/test_anti_fp.c:135` | `static void test_perturb_safe_edges(void **state)` |
| `assert_int_equal` | function | `tests/test_block_flow.c:97` | `assert_int_equal(bf_margins_adjoin(0.0, 0.0), 1);` |
| `assert_true` | function | `tests/test_block_flow.c:31` | `assert_true(dbl_eq(bf_collapse(30.0, 0.0), 30.0));` |
| `cmocka_run_group_tests` | function | `tests/test_block_flow.c:115` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `dbl_eq` | function | `tests/test_block_flow.c:20` | `static int dbl_eq(double a, double b)` |
| `main` | function | `tests/test_block_flow.c:104` | `int main(void)` |
| `test_collapse_n_edges` | function | `tests/test_block_flow.c:84` | `static void test_collapse_n_edges(void **state)` |
| `test_collapse_n_matches_binary` | function | `tests/test_block_flow.c:70` | `static void test_collapse_n_matches_binary(void **state)` |
| `test_margins_adjoin` | function | `tests/test_block_flow.c:95` | `static void test_margins_adjoin(void **state)` |
| `test_non_finite_is_absent` | function | `tests/test_block_flow.c:59` | `static void test_non_finite_is_absent(void **state)` |
| `test_two_negative_take_the_most_negative` | function | `tests/test_block_flow.c:50` | `static void test_two_negative_take_the_most_negative(void **state)` |
| `test_two_positive_collapse_to_max` | function | `tests/test_block_flow.c:29` | `static void test_two_positive_collapse_to_max(void **state)` |
| `assert_edges` | function | `tests/test_box_style.c:26` | `static void assert_edges(bx_edges e, double t, double r, double b, double l)` |
| `assert_false` | function | `tests/test_box_style.c:580` | `assert_false(bx_replaced_box(200, 0, 0, 0, 900.0, &w, &h));` |
| `assert_int_equal` | function | `tests/test_box_style.c:37` | `assert_int_equal(b.display, BX_DISPLAY_BLOCK);` |
| `assert_int_not_equal` | function | `tests/test_box_style.c:169` | `assert_int_not_equal(id, BX_UA_NONE);` |
| `assert_string_equal` | function | `tests/test_box_style.c:376` | `assert_string_equal(bx_display_name(BX_DISPLAY_BLOCK), "block");` |
| `assert_true` | function | `tests/test_box_style.c:28` | `assert_true(dbl_eq(e.top, t));` |
| `cmocka_run_group_tests` | function | `tests/test_box_style.c:634` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `dbl_eq` | function | `tests/test_box_style.c:22` | `static int dbl_eq(double a, double b)` |
| `main` | function | `tests/test_box_style.c:589` | `int main(void)` |
| `memset` | function | `tests/test_box_style.c:367` | `memset(big, 'a', sizeof big - 1);` |
| `percentage` | function | `tests/test_box_style.c:524` | `* percentage (a plain `width:50%` leaves the px half UNSET, a plain `width:300px`
 * leaves the p...` |
| `test_block_ua_box_heading_level_wins` | function | `tests/test_box_style.c:205` | `static void test_block_ua_box_heading_level_wins(void **state)` |
| `test_block_ua_box_is_content_independent` | function | `tests/test_box_style.c:194` | `static void test_block_ua_box_is_content_independent(void **state)` |
| `test_block_ua_box_is_total` | function | `tests/test_box_style.c:227` | `static void test_block_ua_box_is_total(void **state)` |
| `test_block_ua_box_list_item_wins_over_ancestor` | function | `tests/test_box_style.c:218` | `static void test_block_ua_box_list_item_wins_over_ancestor(void **state)` |
| `test_blockquote` | function | `tests/test_box_style.c:75` | `static void test_blockquote(void **state)` |
| `test_body_has_no_margin` | function | `tests/test_box_style.c:33` | `static void test_body_has_no_margin(void **state)` |
| `test_border_box_height` | function | `tests/test_box_style.c:474` | `static void test_border_box_height(void **state)` |
| `test_case_insensitive` | function | `tests/test_box_style.c:109` | `static void test_case_insensitive(void **state)` |
| `test_content_clipped` | function | `tests/test_box_style.c:492` | `static void test_content_clipped(void **state)` |
| `test_display_name` | function | `tests/test_box_style.c:373` | `static void test_display_name(void **state)` |
| `test_display_none_for_non_rendered` | function | `tests/test_box_style.c:100` | `static void test_display_none_for_non_rendered(void **state)` |
| `test_div_is_block` | function | `tests/test_box_style.c:132` | `static void test_div_is_block(void **state)` |
| `test_heading_ladder` | function | `tests/test_box_style.c:48` | `static void test_heading_ladder(void **state)` |
| `test_hr` | function | `tests/test_box_style.c:82` | `static void test_hr(void **state)` |
| `test_inline_and_inline_block` | function | `tests/test_box_style.c:89` | `static void test_inline_and_inline_block(void **state)` |
| `test_lists` | function | `tests/test_box_style.c:64` | `static void test_lists(void **state)` |
| `test_paragraph` | function | `tests/test_box_style.c:41` | `static void test_paragraph(void **state)` |
| `test_parse_display_case_and_trim` | function | `tests/test_box_style.c:346` | `static void test_parse_display_case_and_trim(void **state)` |
| `test_parse_display_errors` | function | `tests/test_box_style.c:355` | `static void test_parse_display_errors(void **state)` |
| `test_parse_display_inline_aliases` | function | `tests/test_box_style.c:337` | `static void test_parse_display_inline_aliases(void **state)` |
| `test_parse_display_keywords` | function | `tests/test_box_style.c:318` | `static void test_parse_display_keywords(void **state)` |
| `test_place_centering` | function | `tests/test_box_style.c:406` | `static void test_place_centering(void **state)` |
| `test_place_failclosed_bounds` | function | `tests/test_box_style.c:430` | `static void test_place_failclosed_bounds(void **state)` |
| `test_place_insets` | function | `tests/test_box_style.c:418` | `static void test_place_insets(void **state)` |
| `test_place_max_width_caps` | function | `tests/test_box_style.c:395` | `static void test_place_max_width_caps(void **state)` |
| `test_place_no_box_is_identity` | function | `tests/test_box_style.c:388` | `static void test_place_no_box_is_identity(void **state)` |
| `test_table_role_from_tag` | function | `tests/test_box_style.c:242` | `static void test_table_role_from_tag(void **state)` |
| `test_table_role_is_total` | function | `tests/test_box_style.c:272` | `static void test_table_role_is_total(void **state)` |
| `test_ua_case_insensitive_and_trimmed` | function | `tests/test_box_style.c:281` | `static void test_ua_case_insensitive_and_trimmed(void **state)` |
| `test_ua_code_space_is_total` | function | `tests/test_box_style.c:308` | `static void test_ua_code_space_is_total(void **state)` |
| `test_ua_fails_closed` | function | `tests/test_box_style.c:290` | `static void test_ua_fails_closed(void **state)` |
| `test_ua_list_item_is_distinct_but_unspaced` | function | `tests/test_box_style.c:181` | `static void test_ua_list_item_is_distinct_but_unspaced(void **state)` |
| `test_ua_spaced_tags_round_trip` | function | `tests/test_box_style.c:161` | `static void test_ua_spaced_tags_round_trip(void **state)` |
| `test_ua_structural_wrappers_have_no_margin` | function | `tests/test_box_style.c:144` | `static void test_ua_structural_wrappers_have_no_margin(void **state)` |
| `test_unknown_and_null_are_neutral_inline` | function | `tests/test_box_style.c:117` | `static void test_unknown_and_null_are_neutral_inline(void **state)` |
| `test_width_cap_pct` | function | `tests/test_box_style.c:507` | `static void test_width_cap_pct(void **state)` |
| `width` | function | `tests/test_box_style.c:534` | `* a negative width (CSS Values 4 section 10.1: out-of-range calc() results are * clamped at used-value time). */ assert_` |
| `UNSET4` | macro | `tests/test_box_tree.c:609` | `#define UNSET4` |
| `assert_int_equal` | function | `tests/test_box_tree.c:37` | `assert_int_equal(bt_layout(NULL, 200), BT_ERR_NULL_ARG);` |
| `assert_rect` | function | `tests/test_box_tree.c:27` | `static void assert_rect(const bt_node *n, double x, double y, double w, double h)` |
| `assert_true` | function | `tests/test_box_tree.c:29` | `assert_true(dbl_eq(n->x, x));` |
| `card` | function | `tests/test_box_tree.c:749` | `* containing block climbs the unplaced card(1) → placed ancestor(0, x=100). */ assert_true(dbl_eq(out[2].x, 100));` |
| `cmocka_run_group_tests` | function | `tests/test_box_tree.c:943` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_box_tree.c:888` | `int main(void)` |
| `test_abspos_resolves_against_placed_ancestor` | function | `tests/test_box_tree.c:724` | `static void test_abspos_resolves_against_placed_ancestor(void **state)` |
| `test_abspos_unplaced_without_anchor_falls_to_viewport` | function | `tests/test_box_tree.c:753` | `static void test_abspos_unplaced_without_anchor_falls_to_viewport(void **state)` |
| `test_block_stacking_with_collapse` | function | `tests/test_box_tree.c:61` | `static void test_block_stacking_with_collapse(void **state)` |
| `test_box_hidden_ancestor` | function | `tests/test_box_tree.c:785` | `static void test_box_hidden_ancestor(void **state)` |
| `test_box_hidden_fail_closed` | function | `tests/test_box_tree.c:798` | `static void test_box_hidden_fail_closed(void **state)` |
| `test_box_hidden_self` | function | `tests/test_box_tree.c:773` | `static void test_box_hidden_self(void **state)` |
| `test_children_cap` | function | `tests/test_box_tree.c:367` | `static void test_children_cap(void **state)` |
| `test_depth_cap` | function | `tests/test_box_tree.c:377` | `static void test_depth_cap(void **state)` |
| `test_display_none_skipped` | function | `tests/test_box_tree.c:332` | `static void test_display_none_skipped(void **state)` |
| `test_flex_cross_axis_align` | function | `tests/test_box_tree.c:192` | `static void test_flex_cross_axis_align(void **state)` |
| `test_flex_gap_and_justify_center` | function | `tests/test_box_tree.c:92` | `static void test_flex_gap_and_justify_center(void **state)` |
| `test_flex_negative_gap` | function | `tests/test_box_tree.c:357` | `static void test_flex_negative_gap(void **state)` |
| `test_flex_nowrap_default_single_line_unchanged` | function | `tests/test_box_tree.c:130` | `static void test_flex_nowrap_default_single_line_unchanged(void **state)` |
| `test_flex_row_grow` | function | `tests/test_box_tree.c:74` | `static void test_flex_row_grow(void **state)` |
| `test_flex_wrap_reverse_two_lines` | function | `tests/test_box_tree.c:150` | `static void test_flex_wrap_reverse_two_lines(void **state)` |
| `test_flex_wrap_row_gap_distinct_from_gap` | function | `tests/test_box_tree.c:172` | `static void test_flex_wrap_row_gap_distinct_from_gap(void **state)` |
| `test_flex_wrap_two_lines` | function | `tests/test_box_tree.c:108` | `static void test_flex_wrap_two_lines(void **state)` |
| `test_grid` | function | `tests/test_box_tree.c:249` | `static void test_grid(void **state)` |
| `test_grid_bad_columns` | function | `tests/test_box_tree.c:347` | `static void test_grid_bad_columns(void **state)` |
| `test_grid_column_span` | function | `tests/test_box_tree.c:288` | `static void test_grid_column_span(void **state)` |
| `test_grid_row_gap_distinct_from_gap` | function | `tests/test_box_tree.c:210` | `static void test_grid_row_gap_distinct_from_gap(void **state)` |
| `test_grid_weighted_tracks` | function | `tests/test_box_tree.c:270` | `static void test_grid_weighted_tracks(void **state)` |
| `test_grid_without_row_gap_falls_back_to_gap` | function | `tests/test_box_tree.c:233` | `static void test_grid_without_row_gap_falls_back_to_gap(void **state)` |
| `test_leaf` | function | `tests/test_box_tree.c:39` | `static void test_leaf(void **state)` |
| `test_leaf_with_padding` | function | `tests/test_box_tree.c:46` | `static void test_leaf_with_padding(void **state)` |
| `test_nested_flex_in_block` | function | `tests/test_box_tree.c:308` | `static void test_nested_flex_in_block(void **state)` |
| `test_null_root` | function | `tests/test_box_tree.c:34` | `static void test_null_root(void **state)` |
| `test_oof_anchor_none_on_static_chain` | function | `tests/test_box_tree.c:811` | `static void test_oof_anchor_none_on_static_chain(void **state)` |
| `test_oof_anchor_self` | function | `tests/test_box_tree.c:821` | `static void test_oof_anchor_self(void **state)` |
| `test_oof_anchor_via_ancestor` | function | `tests/test_box_tree.c:828` | `static void test_oof_anchor_via_ancestor(void **state)` |
| `test_oof_fail_open` | function | `tests/test_box_tree.c:870` | `static void test_oof_fail_open(void **state)` |
| `test_oof_nested_absolute_anchor_vs_root` | function | `tests/test_box_tree.c:841` | `static void test_oof_nested_absolute_anchor_vs_root(void **state)` |
| `test_oof_relative_does_not_anchor` | function | `tests/test_box_tree.c:856` | `static void test_oof_relative_does_not_anchor(void **state)` |
| `test_positioning_absolute_against_ancestor` | function | `tests/test_box_tree.c:441` | `static void test_positioning_absolute_against_ancestor(void **state)` |
| `test_positioning_absolute_against_viewport` | function | `tests/test_box_tree.c:464` | `static void test_positioning_absolute_against_viewport(void **state)` |
| `test_positioning_doc_order_tiebreak` | function | `tests/test_box_tree.c:538` | `static void test_positioning_doc_order_tiebreak(void **state)` |
| `test_positioning_fixed_against_viewport` | function | `tests/test_box_tree.c:481` | `static void test_positioning_fixed_against_viewport(void **state)` |
| `test_positioning_nbox_cap` | function | `tests/test_box_tree.c:590` | `static void test_positioning_nbox_cap(void **state)` |
| `test_positioning_no_insets` | function | `tests/test_box_tree.c:556` | `static void test_positioning_no_insets(void **state)` |
| `test_positioning_null_args` | function | `tests/test_box_tree.c:394` | `static void test_positioning_null_args(void **state)` |
| `test_positioning_null_geometry` | function | `tests/test_box_tree.c:573` | `static void test_positioning_null_geometry(void **state)` |
| `test_positioning_relative_offset` | function | `tests/test_box_tree.c:420` | `static void test_positioning_relative_offset(void **state)` |
| `test_positioning_stacking_order` | function | `tests/test_box_tree.c:518` | `static void test_positioning_stacking_order(void **state)` |
| `test_positioning_static_unchanged` | function | `tests/test_box_tree.c:408` | `static void test_positioning_static_unchanged(void **state)` |
| `test_positioning_sticky_treated_as_relative` | function | `tests/test_box_tree.c:500` | `static void test_positioning_sticky_treated_as_relative(void **state)` |
| `test_static_position_absolute_auto_insets` | function | `tests/test_box_tree.c:612` | `static void test_static_position_absolute_auto_insets(void **state)` |
| `test_static_position_explicit_insets_win` | function | `tests/test_box_tree.c:644` | `static void test_static_position_explicit_insets_win(void **state)` |
| `test_static_position_fixed_auto_insets` | function | `tests/test_box_tree.c:628` | `static void test_static_position_fixed_auto_insets(void **state)` |
| `test_static_position_mixed_axis` | function | `tests/test_box_tree.c:665` | `static void test_static_position_mixed_axis(void **state)` |
| `test_static_position_null_arrays_legacy` | function | `tests/test_box_tree.c:705` | `static void test_static_position_null_arrays_legacy(void **state)` |
| `test_static_position_right_inset_keeps_anchor` | function | `tests/test_box_tree.c:685` | `static void test_static_position_right_inset_keeps_anchor(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_browser.c:7` | `#define _POSIX_C_SOURCE` |
| `assert_false` | function | `tests/test_browser.c:26` | `assert_false(browser_can_back(&bs));` |
| `assert_int_equal` | function | `tests/test_browser.c:24` | `assert_int_equal(browser_init(&bs), BROWSER_OK);` |
| `assert_non_null` | function | `tests/test_browser.c:293` | `assert_non_null(browser_status_text(&bs, 0));` |
| `assert_null` | function | `tests/test_browser.c:282` | `assert_null(browser_status_text(&bs, 0));` |
| `assert_string_equal` | function | `tests/test_browser.c:25` | `assert_string_equal(bs.url_bar, "about:blank");` |
| `assert_true` | function | `tests/test_browser.c:43` | `assert_true(browser_can_back(&bs));` |
| `browser_back` | function | `tests/test_browser.c:70` | `browser_back(&bs);` |
| `browser_free` | function | `tests/test_browser.c:28` | `browser_free(&bs);` |
| `browser_navigate` | function | `tests/test_browser.c:66` | `browser_navigate(&bs, "/a.html");` |
| `browser_set_url_bar` | function | `tests/test_browser.c:157` | `browser_set_url_bar(&bs, "example.com");` |
| `browser_url_bar_backspace` | function | `tests/test_browser.c:139` | `browser_url_bar_backspace(&bs);` |
| `browser_url_bar_clear` | function | `tests/test_browser.c:127` | `browser_url_bar_clear(&bs);` |
| `browser_url_bar_delete` | function | `tests/test_browser.c:144` | `browser_url_bar_delete(&bs);` |
| `browser_url_bar_extend_cursor` | function | `tests/test_browser.c:176` | `browser_url_bar_extend_cursor(&bs, 3);` |
| `browser_url_bar_insert` | function | `tests/test_browser.c:130` | `browser_url_bar_insert(&bs, 'h');` |
| `browser_url_bar_move_cursor` | function | `tests/test_browser.c:135` | `browser_url_bar_move_cursor(&bs, -1);` |
| `browser_url_bar_select_all` | function | `tests/test_browser.c:163` | `browser_url_bar_select_all(&bs);` |
| `browser_url_bar_set_cursor` | function | `tests/test_browser.c:175` | `browser_url_bar_set_cursor(&bs, 2, 0);` |
| `cmocka_run_group_tests` | function | `tests/test_browser.c:342` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_browser.c:325` | `int main(void)` |
| `memset` | function | `tests/test_browser.c:23` | `memset(&bs, 0, sizeof bs);` |
| `test_accepts_https_and_file` | function | `tests/test_browser.c:107` | `static void test_accepts_https_and_file(void **state)` |
| `test_back_forward_bounds` | function | `tests/test_browser.c:78` | `static void test_back_forward_bounds(void **state)` |
| `test_exceptions` | function | `tests/test_browser.c:251` | `static void test_exceptions(void **state)` |
| `test_init` | function | `tests/test_browser.c:19` | `static void test_init(void **state)` |
| `test_navigate_from_middle_discards_future` | function | `tests/test_browser.c:60` | `static void test_navigate_from_middle_discards_future(void **state)` |
| `test_navigate_history` | function | `tests/test_browser.c:30` | `static void test_navigate_history(void **state)` |
| `test_rejects_invalid_url` | function | `tests/test_browser.c:94` | `static void test_rejects_invalid_url(void **state)` |
| `test_set_page` | function | `tests/test_browser.c:195` | `static void test_set_page(void **state)` |
| `test_set_page_sanitizes_invalid_utf8` | function | `tests/test_browser.c:218` | `static void test_set_page_sanitizes_invalid_utf8(void **state)` |
| `test_status_toast` | function | `tests/test_browser.c:277` | `static void test_status_toast(void **state)` |
| `test_status_truncates` | function | `tests/test_browser.c:308` | `static void test_status_truncates(void **state)` |
| `test_url_bar_editing` | function | `tests/test_browser.c:121` | `static void test_url_bar_editing(void **state)` |
| `test_url_bar_selection` | function | `tests/test_browser.c:152` | `static void test_url_bar_selection(void **state)` |
| `assert_int_equal` | function | `tests/test_compositor.c:63` | `assert_int_equal(cx_forms_stacking_context(&s), 1);` |
| `assert_true` | function | `tests/test_compositor.c:143` | `assert_true(cx_item_compare(&a, &b) < 0);` |
| `cmocka_run_group_tests` | function | `tests/test_compositor.c:253` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `cx_sort` | function | `tests/test_compositor.c:172` | `cx_sort(items, sizeof items / sizeof items[0]);` |
| `main` | function | `tests/test_compositor.c:230` | `int main(void)` |
| `mk` | function | `tests/test_compositor.c:132` | `static cx_item mk(cx_layer layer, int z, int z_auto, size_t doc, size_t ref)` |
| `test_compare_layer_then_z_then_doc` | function | `tests/test_compositor.c:138` | `static void test_compare_layer_then_z_then_doc(void **state)` |
| `test_layer_float` | function | `tests/test_compositor.c:115` | `static void test_layer_float(void **state)` |
| `test_layer_inline_and_block` | function | `tests/test_compositor.c:122` | `static void test_layer_inline_and_block(void **state)` |
| `test_layer_negative_z` | function | `tests/test_compositor.c:85` | `static void test_layer_negative_z(void **state)` |
| `test_layer_positive_z` | function | `tests/test_compositor.c:92` | `static void test_layer_positive_z(void **state)` |
| `test_layer_zero_z_context` | function | `tests/test_compositor.c:99` | `static void test_layer_zero_z_context(void **state)` |
| `test_layer_zero_z_positioned_auto` | function | `tests/test_compositor.c:108` | `static void test_layer_zero_z_positioned_auto(void **state)` |
| `test_sc_fixed_sticky_always` | function | `tests/test_compositor.c:69` | `static void test_sc_fixed_sticky_always(void **state)` |
| `test_sc_isolation` | function | `tests/test_compositor.c:42` | `static void test_sc_isolation(void **state)` |
| `test_sc_mix_blend` | function | `tests/test_compositor.c:34` | `static void test_sc_mix_blend(void **state)` |
| `test_sc_opacity` | function | `tests/test_compositor.c:25` | `static void test_sc_opacity(void **state)` |
| `test_sc_positioned_z` | function | `tests/test_compositor.c:57` | `static void test_sc_positioned_z(void **state)` |
| `test_sc_static_none` | function | `tests/test_compositor.c:76` | `static void test_sc_static_none(void **state)` |
| `test_sc_transform` | function | `tests/test_compositor.c:50` | `static void test_sc_transform(void **state)` |
| `test_sort_full_paint_order` | function | `tests/test_compositor.c:159` | `static void test_sort_full_paint_order(void **state)` |
| `test_sort_matches_zindex_only_ordering` | function | `tests/test_compositor.c:218` | `static void test_sort_matches_zindex_only_ordering(void **state)` |
| `test_sort_noop_guards` | function | `tests/test_compositor.c:206` | `static void test_sort_noop_guards(void **state)` |
| `test_sort_stability` | function | `tests/test_compositor.c:192` | `static void test_sort_stability(void **state)` |
| `test_sort_z_within_layer` | function | `tests/test_compositor.c:176` | `static void test_sort_z_within_layer(void **state)` |
| `assert_int_equal` | function | `tests/test_css.c:1192` | `assert_int_equal(css_parse("tr:nth-child(even)` |
| `assert_int_equal` | function | `tests/test_css.c:1215` | `assert_int_equal(css_parse("li:nth-last-child(2)` |
| `assert_int_equal` | function | `tests/test_css.c:1413` | `assert_int_equal(css_parse("li:nth-child()` |
| `assert_int_equal` | function | `tests/test_css.c:1448` | `assert_int_equal(css_parse("li:nth-of-type(2n)` |
| `assert_int_equal` | function | `tests/test_css.c:1480` | `assert_int_equal(css_parse("div:has(.x)` |
| `assert_int_equal` | function | `tests/test_css.c:1501` | `assert_int_equal(css_parse("html:lang(en)` |
| `assert_int_equal` | function | `tests/test_css.c:1857` | `assert_int_equal(css_parse(
        "@media (min-width: 600px)` |
| `assert_int_equal` | function | `tests/test_css.c:1872` | `assert_int_equal(css_parse(
        "@media screen and (min-width: 600px)` |
| `assert_int_equal` | function | `tests/test_css.c:1886` | `assert_int_equal(css_parse(
        "@media (hover: hover)` |
| `assert_int_equal` | function | `tests/test_css.c:4043` | `assert_int_equal(css_parse("@media (min-width: 200em)` |
| `assert_int_equal` | function | `tests/test_css.c:4049` | `assert_int_equal(css_parse("@media (min-width: 40em)` |
| `assert_int_not_equal` | function | `tests/test_css.c:1267` | `assert_int_not_equal(css_resolve_el(sh, &q, NULL, 0).color, -1);` |
| `assert_non_null` | function | `tests/test_css.c:1760` | `assert_non_null(buf);` |
| `assert_string_equal` | function | `tests/test_css.c:625` | `assert_string_equal(s.bg_image_url, "hero.jpg");` |
| `assert_true` | function | `tests/test_css.c:404` | `assert_true(r0 > 0 && (size_t)r0 < sizeof buf);` |
| `box` | function | `tests/test_css.c:228` | `* box (CSS 2.1 section 10.8.1). With one line box per line and no separate * parent content edge, they land on the same ` |
| `closed` | function | `tests/test_css.c:472` | `* fail closed (unset), never a wrong guess. */ assert_int_equal( css_parse_inline("grid-template-columns: repeat(auto-fi` |
| `cmocka_run_group_tests` | function | `tests/test_css.c:4364` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `css_free` | function | `tests/test_css.c:286` | `css_free(sh);` |
| `downstream` | function | `tests/test_css.c:643` | `* and deciding whether to fetch happens downstream (render_doc.c) */ assert_string_equal(css_parse_inline( "background-i` |
| `el_attr_node` | function | `tests/test_css.c:975` | `static css_element el_attr_node(const char *tag, const char *id,
                                ...` |
| `el_node` | function | `tests/test_css.c:940` | `static css_element el_node(const char *tag, const char *id,
                           const char...` |
| `el_sib_node` | function | `tests/test_css.c:955` | `static css_element el_sib_node(const char *tag, int nth, int nsib,
                              ...` |
| `el_type_node` | function | `tests/test_css.c:964` | `static css_element el_type_node(const char *tag, int nth, int nsib,
                             ...` |
| `free` | function | `tests/test_css.c:1781` | `free(buf);` |
| `geometry` | function | `tests/test_css.c:2138` | `* hostile sheet never sees real window geometry (anti-fingerprinting) yet 100vh
 * heroes and cal...` |
| `invalid` | function | `tests/test_css.c:745` | `* invalid (fail closed), not silently coerced into some default. */ css_style s = css_parse_inline("color: var(--missing` |
| `main` | function | `tests/test_css.c:4119` | `int main(void)` |
| `memset` | function | `tests/test_css.c:666` | `memset(big, 'a', sizeof big - 1);` |
| `silent` | function | `tests/test_css.c:1754` | `* silent (anti-DoS truncation, not a parse failure). 500 filler rules is well past
 * the OLD cap...` |
| `snprintf` | function | `tests/test_css.c:669` | `snprintf(val, sizeof val, "background-image: url(%s.png)", big);` |
| `test_adjacent_sibling_combinator` | function | `tests/test_css.c:1065` | `static void test_adjacent_sibling_combinator(void **state)` |
| `test_anim_keyframes_resolved_from_sheet` | function | `tests/test_css.c:3792` | `static void test_anim_keyframes_resolved_from_sheet(void **state)` |
| `test_anim_transform_keyframes_from_sheet` | function | `tests/test_css.c:3825` | `static void test_anim_transform_keyframes_from_sheet(void **state)` |
| `test_at_rules_skipped` | function | `tests/test_css.c:1801` | `static void test_at_rules_skipped(void **state)` |
| `test_attr_case_insensitive_flag` | function | `tests/test_css.c:1588` | `static void test_attr_case_insensitive_flag(void **state)` |
| `test_attr_equals` | function | `tests/test_css.c:1538` | `static void test_attr_equals(void **state)` |
| `test_attr_in_combinator` | function | `tests/test_css.c:1645` | `static void test_attr_in_combinator(void **state)` |
| `test_attr_malformed_fail_closed` | function | `tests/test_css.c:1661` | `static void test_attr_malformed_fail_closed(void **state)` |
| `test_attr_name_case_insensitive` | function | `tests/test_css.c:1603` | `static void test_attr_name_case_insensitive(void **state)` |
| `test_attr_operators` | function | `tests/test_css.c:1556` | `static void test_attr_operators(void **state)` |
| `test_attr_presence` | function | `tests/test_css.c:1525` | `static void test_attr_presence(void **state)` |
| `test_attr_quoted_value_with_space` | function | `tests/test_css.c:1614` | `static void test_attr_quoted_value_with_space(void **state)` |
| `test_attr_specificity_and_compound` | function | `tests/test_css.c:1628` | `static void test_attr_specificity_and_compound(void **state)` |
| `test_backdrop_filter_blur` | function | `tests/test_css.c:3752` | `static void test_backdrop_filter_blur(void **state)` |
| `test_background_clip_text` | function | `tests/test_css.c:3627` | `static void test_background_clip_text(void **state)` |
| `test_background_rgba_alpha` | function | `tests/test_css.c:3599` | `static void test_background_rgba_alpha(void **state)` |
| `test_background_shorthand_resets_gradient` | function | `tests/test_css.c:600` | `static void test_background_shorthand_resets_gradient(void **state)` |
| `test_bg_image_url_absolute` | function | `tests/test_css.c:639` | `static void test_bg_image_url_absolute(void **state)` |
| `test_bg_image_url_basic` | function | `tests/test_css.c:621` | `static void test_bg_image_url_basic(void **state)` |
| `test_bg_image_url_gradient_mutually_exclusive` | function | `tests/test_css.c:675` | `static void test_bg_image_url_gradient_mutually_exclusive(void **state)` |
| `test_bg_image_url_none_and_junk_reset` | function | `tests/test_css.c:648` | `static void test_bg_image_url_none_and_junk_reset(void **state)` |
| `test_bg_image_url_overlong_fails_closed` | function | `tests/test_css.c:662` | `static void test_bg_image_url_overlong_fails_closed(void **state)` |
| `test_bg_image_url_quoted` | function | `tests/test_css.c:628` | `static void test_bg_image_url_quoted(void **state)` |
| `test_bg_shorthand_captures_url_and_resets_color` | function | `tests/test_css.c:683` | `static void test_bg_shorthand_captures_url_and_resets_color(void **state)` |
| `test_bg_size_and_repeat` | function | `tests/test_css.c:702` | `static void test_bg_size_and_repeat(void **state)` |
| `test_border_longhands` | function | `tests/test_css.c:2600` | `static void test_border_longhands(void **state)` |
| `test_border_shorthand` | function | `tests/test_css.c:2570` | `static void test_border_shorthand(void **state)` |
| `test_box_auto_and_centering` | function | `tests/test_css.c:1970` | `static void test_box_auto_and_centering(void **state)` |
| `test_box_clamp_anti_dos` | function | `tests/test_css.c:2227` | `static void test_box_clamp_anti_dos(void **state)` |
| `test_box_extension_sheet_cascade` | function | `tests/test_css.c:2277` | `static void test_box_extension_sheet_cascade(void **state)` |
| `test_box_orient_maps_to_flex_direction` | function | `tests/test_css.c:2727` | `static void test_box_orient_maps_to_flex_direction(void **state)` |
| `test_box_shadow_and_outline` | function | `tests/test_css.c:2626` | `static void test_box_shadow_and_outline(void **state)` |
| `test_box_sheet_cascade_inline_wins` | function | `tests/test_css.c:2404` | `static void test_box_sheet_cascade_inline_wins(void **state)` |
| `test_box_shorthand_expansion` | function | `tests/test_css.c:1942` | `static void test_box_shorthand_expansion(void **state)` |
| `test_box_sizing` | function | `tests/test_css.c:2562` | `static void test_box_sizing(void **state)` |
| `test_box_units_and_failclosed` | function | `tests/test_css.c:1987` | `static void test_box_units_and_failclosed(void **state)` |
| `test_calc_basic_arithmetic` | function | `tests/test_css.c:2083` | `static void test_calc_basic_arithmetic(void **state)` |
| `test_calc_clamped_anti_dos` | function | `tests/test_css.c:2129` | `static void test_calc_clamped_anti_dos(void **state)` |
| `test_calc_dimension_errors_fail_closed` | function | `tests/test_css.c:2107` | `static void test_calc_dimension_errors_fail_closed(void **state)` |
| `test_calc_inside_shorthands` | function | `tests/test_css.c:2183` | `static void test_calc_inside_shorthands(void **state)` |
| `test_calc_precedence_and_parens` | function | `tests/test_css.c:2092` | `static void test_calc_precedence_and_parens(void **state)` |
| `test_calc_units_and_signs` | function | `tests/test_css.c:2099` | `static void test_calc_units_and_signs(void **state)` |
| `test_calc_with_custom_property` | function | `tests/test_css.c:2220` | `static void test_calc_with_custom_property(void **state)` |
| `test_cascade_document_order` | function | `tests/test_css.c:1783` | `static void test_cascade_document_order(void **state)` |
| `test_cascade_inline_wins` | function | `tests/test_css.c:1792` | `static void test_cascade_inline_wins(void **state)` |
| `test_cascade_specificity` | function | `tests/test_css.c:1737` | `static void test_cascade_specificity(void **state)` |
| `test_child_combinator` | function | `tests/test_css.c:1018` | `static void test_child_combinator(void **state)` |
| `test_clip_auto` | function | `tests/test_css.c:4066` | `static void test_clip_auto(void **state)` |
| `test_clip_rect` | function | `tests/test_css.c:4056` | `static void test_clip_rect(void **state)` |
| `test_combinator_class_chain` | function | `tests/test_css.c:1046` | `static void test_combinator_class_chain(void **state)` |
| `test_combinator_specificity_sum` | function | `tests/test_css.c:1031` | `static void test_combinator_specificity_sum(void **state)` |
| `test_conic_gradient_basic` | function | `tests/test_css.c:3647` | `static void test_conic_gradient_basic(void **state)` |
| `test_conic_gradient_deg_positions` | function | `tests/test_css.c:3688` | `static void test_conic_gradient_deg_positions(void **state)` |
| `test_conic_gradient_fails_closed` | function | `tests/test_css.c:3698` | `static void test_conic_gradient_fails_closed(void **state)` |
| `test_conic_gradient_from_angle` | function | `tests/test_css.c:3659` | `static void test_conic_gradient_from_angle(void **state)` |
| `test_conic_gradient_pie_hard_stop` | function | `tests/test_css.c:3673` | `static void test_conic_gradient_pie_hard_stop(void **state)` |
| `test_container_cascade_inline_wins` | function | `tests/test_css.c:375` | `static void test_container_cascade_inline_wins(void **state)` |
| `test_container_fail_closed_and_bounds` | function | `tests/test_css.c:390` | `static void test_container_fail_closed_and_bounds(void **state)` |
| `test_container_unset` | function | `tests/test_css.c:493` | `static void test_container_unset(void **state)` |
| `test_cursor` | function | `tests/test_css.c:2514` | `static void test_cursor(void **state)` |
| `test_custom_prop_class_scoped_applies_with_root_scope` | function | `tests/test_css.c:830` | `static void test_custom_prop_class_scoped_applies_with_root_scope(void **state)` |
| `test_custom_prop_class_scoped_skipped_without_scope` | function | `tests/test_css.c:818` | `static void test_custom_prop_class_scoped_skipped_without_scope(void **state)` |
| `test_custom_prop_dark_media_collected_in_dark` | function | `tests/test_css.c:805` | `static void test_custom_prop_dark_media_collected_in_dark(void **state)` |
| `test_custom_prop_dark_media_not_collected_in_light` | function | `tests/test_css.c:790` | `static void test_custom_prop_dark_media_not_collected_in_light(void **state)` |
| `test_custom_prop_descendant_scoped_skipped` | function | `tests/test_css.c:843` | `static void test_custom_prop_descendant_scoped_skipped(void **state)` |
| `test_custom_prop_table_holds_hundreds` | function | `tests/test_css.c:855` | `static void test_custom_prop_table_holds_hundreds(void **state)` |
| `test_custom_prop_var_basic` | function | `tests/test_css.c:724` | `static void test_custom_prop_var_basic(void **state)` |
| `test_custom_prop_var_chain` | function | `tests/test_css.c:750` | `static void test_custom_prop_var_chain(void **state)` |
| `test_custom_prop_var_fallback_used_when_missing` | function | `tests/test_css.c:735` | `static void test_custom_prop_var_fallback_used_when_missing(void **state)` |
| `test_custom_prop_var_in_shorthand` | function | `tests/test_css.c:767` | `static void test_custom_prop_var_in_shorthand(void **state)` |
| `test_custom_prop_var_later_declaration_wins` | function | `tests/test_css.c:777` | `static void test_custom_prop_var_later_declaration_wins(void **state)` |
| `test_custom_prop_var_never_phones_home` | function | `tests/test_css.c:881` | `static void test_custom_prop_var_never_phones_home(void **state)` |
| `test_custom_prop_var_no_fallback_drops_decl` | function | `tests/test_css.c:741` | `static void test_custom_prop_var_no_fallback_drops_decl(void **state)` |
| `test_custom_prop_var_self_reference_fails_closed` | function | `tests/test_css.c:758` | `static void test_custom_prop_var_self_reference_fails_closed(void **state)` |
| `test_custom_prop_var_unbalanced_paren_drops` | function | `tests/test_css.c:874` | `static void test_custom_prop_var_unbalanced_paren_drops(void **state)` |
| `test_descendant_combinator` | function | `tests/test_css.c:1002` | `static void test_descendant_combinator(void **state)` |
| `test_filter_blur_and_grayscale` | function | `tests/test_css.c:3764` | `static void test_filter_blur_and_grayscale(void **state)` |
| `test_filter_drop_shadow` | function | `tests/test_css.c:3725` | `static void test_filter_drop_shadow(void **state)` |
| `test_filter_drop_shadow_defaults_and_failclosed` | function | `tests/test_css.c:3738` | `static void test_filter_drop_shadow_defaults_and_failclosed(void **state)` |
| `test_flex_align` | function | `tests/test_css.c:2695` | `static void test_flex_align(void **state)` |
| `test_flex_item` | function | `tests/test_css.c:2651` | `static void test_flex_item(void **state)` |
| `test_float_and_clear` | function | `tests/test_css.c:2450` | `static void test_float_and_clear(void **state)` |
| `test_font_family` | function | `tests/test_css.c:136` | `static void test_font_family(void **state)` |
| `test_font_shorthand` | function | `tests/test_css.c:3569` | `static void test_font_shorthand(void **state)` |
| `test_gap_two_value` | function | `tests/test_css.c:3551` | `static void test_gap_two_value(void **state)` |
| `test_general_sibling_combinator` | function | `tests/test_css.c:1080` | `static void test_general_sibling_combinator(void **state)` |
| `test_grid_extras` | function | `tests/test_css.c:2749` | `static void test_grid_extras(void **state)` |
| `test_grid_minmax_counts_as_one_track` | function | `tests/test_css.c:460` | `static void test_grid_minmax_counts_as_one_track(void **state)` |
| `test_grid_repeat_autofill_fails_closed` | function | `tests/test_css.c:468` | `static void test_grid_repeat_autofill_fails_closed(void **state)` |
| `test_grid_repeat_clamped_anti_dos` | function | `tests/test_css.c:486` | `static void test_grid_repeat_clamped_anti_dos(void **state)` |
| `test_grid_repeat_expands_count` | function | `tests/test_css.c:449` | `static void test_grid_repeat_expands_count(void **state)` |
| `test_grid_repeat_malformed_fails_closed` | function | `tests/test_css.c:479` | `static void test_grid_repeat_malformed_fails_closed(void **state)` |
| `test_has_parses_and_fails_closed` | function | `tests/test_css.c:1473` | `static void test_has_parses_and_fails_closed(void **state)` |
| `test_important_beats_specificity` | function | `tests/test_css.c:1689` | `static void test_important_beats_specificity(void **state)` |
| `test_important_in_shorthand` | function | `tests/test_css.c:1720` | `static void test_important_in_shorthand(void **state)` |
| `test_important_inline_beats_sheet_important` | function | `tests/test_css.c:1708` | `static void test_important_inline_beats_sheet_important(void **state)` |
| `test_important_inline_not_dropped` | function | `tests/test_css.c:1679` | `static void test_important_inline_not_dropped(void **state)` |
| `test_important_tier_then_normal_order` | function | `tests/test_css.c:1698` | `static void test_important_tier_then_normal_order(void **state)` |
| `test_inline_accent_color` | function | `tests/test_css.c:3046` | `static void test_inline_accent_color(void **state)` |
| `test_inline_appearance` | function | `tests/test_css.c:2922` | `static void test_inline_appearance(void **state)` |
| `test_inline_aspect_ratio` | function | `tests/test_css.c:2343` | `static void test_inline_aspect_ratio(void **state)` |
| `test_inline_backface_visibility` | function | `tests/test_css.c:3435` | `static void test_inline_backface_visibility(void **state)` |
| `test_inline_bg_clip_origin_attachment` | function | `tests/test_css.c:2975` | `static void test_inline_bg_clip_origin_attachment(void **state)` |
| `test_inline_bg_repeat` | function | `tests/test_css.c:2955` | `static void test_inline_bg_repeat(void **state)` |
| `test_inline_bg_size` | function | `tests/test_css.c:2966` | `static void test_inline_bg_size(void **state)` |
| `test_inline_border_collapse` | function | `tests/test_css.c:2835` | `static void test_inline_border_collapse(void **state)` |
| `test_inline_border_spacing` | function | `tests/test_css.c:2844` | `static void test_inline_border_spacing(void **state)` |
| `test_inline_box_longhands` | function | `tests/test_css.c:1924` | `static void test_inline_box_longhands(void **state)` |
| `test_inline_caption_side` | function | `tests/test_css.c:2864` | `static void test_inline_caption_side(void **state)` |
| `test_inline_caret_color` | function | `tests/test_css.c:2912` | `static void test_inline_caret_color(void **state)` |
| `test_inline_color_scheme` | function | `tests/test_css.c:3036` | `static void test_inline_color_scheme(void **state)` |
| `test_inline_contain` | function | `tests/test_css.c:3003` | `static void test_inline_contain(void **state)` |
| `test_inline_container_props` | function | `tests/test_css.c:326` | `static void test_inline_container_props(void **state)` |
| `test_inline_content_visibility` | function | `tests/test_css.c:3018` | `static void test_inline_content_visibility(void **state)` |
| `test_inline_direction` | function | `tests/test_css.c:2373` | `static void test_inline_direction(void **state)` |
| `test_inline_display` | function | `tests/test_css.c:288` | `static void test_inline_display(void **state)` |
| `test_inline_display_table_family` | function | `tests/test_css.c:302` | `static void test_inline_display_table_family(void **state)` |
| `test_inline_empty_cells` | function | `tests/test_css.c:2855` | `static void test_inline_empty_cells(void **state)` |
| `test_inline_font_kerning` | function | `tests/test_css.c:3365` | `static void test_inline_font_kerning(void **state)` |
| `test_inline_font_size` | function | `tests/test_css.c:40` | `static void test_inline_font_size(void **state)` |
| `test_inline_font_size_absolute_flag` | function | `tests/test_css.c:56` | `static void test_inline_font_size_absolute_flag(void **state)` |
| `test_inline_font_stretch` | function | `tests/test_css.c:3384` | `static void test_inline_font_stretch(void **state)` |
| `test_inline_font_variant` | function | `tests/test_css.c:2882` | `static void test_inline_font_variant(void **state)` |
| `test_inline_font_weight_style` | function | `tests/test_css.c:97` | `static void test_inline_font_weight_style(void **state)` |
| `test_inline_hyphens` | function | `tests/test_css.c:2891` | `static void test_inline_hyphens(void **state)` |
| `test_inline_image_rendering` | function | `tests/test_css.c:3027` | `static void test_inline_image_rendering(void **state)` |
| `test_inline_isolation` | function | `tests/test_css.c:2995` | `static void test_inline_isolation(void **state)` |
| `test_inline_line_height` | function | `tests/test_css.c:82` | `static void test_inline_line_height(void **state)` |
| `test_inline_list_style_pos` | function | `tests/test_css.c:3357` | `static void test_inline_list_style_pos(void **state)` |
| `test_inline_min_max_height` | function | `tests/test_css.c:2263` | `static void test_inline_min_max_height(void **state)` |
| `test_inline_min_width_height` | function | `tests/test_css.c:2236` | `static void test_inline_min_width_height(void **state)` |
| `test_inline_mix_blend_mode` | function | `tests/test_css.c:3069` | `static void test_inline_mix_blend_mode(void **state)` |
| `test_inline_object_fit` | function | `tests/test_css.c:3346` | `static void test_inline_object_fit(void **state)` |
| `test_inline_outline_longhands` | function | `tests/test_css.c:2804` | `static void test_inline_outline_longhands(void **state)` |
| `test_inline_outline_offset` | function | `tests/test_css.c:2382` | `static void test_inline_outline_offset(void **state)` |
| `test_inline_overscroll_behavior` | function | `tests/test_css.c:3426` | `static void test_inline_overscroll_behavior(void **state)` |
| `test_inline_pointer_events` | function | `tests/test_css.c:2931` | `static void test_inline_pointer_events(void **state)` |
| `test_inline_print_forced_adjust` | function | `tests/test_css.c:3055` | `static void test_inline_print_forced_adjust(void **state)` |
| `test_inline_resize` | function | `tests/test_css.c:3399` | `static void test_inline_resize(void **state)` |
| `test_inline_scroll_behavior` | function | `tests/test_css.c:3409` | `static void test_inline_scroll_behavior(void **state)` |
| `test_inline_tab_size` | function | `tests/test_css.c:2394` | `static void test_inline_tab_size(void **state)` |
| `test_inline_table_layout` | function | `tests/test_css.c:2873` | `static void test_inline_table_layout(void **state)` |
| `test_inline_text_align` | function | `tests/test_css.c:32` | `static void test_inline_text_align(void **state)` |
| `test_inline_text_decoration` | function | `tests/test_css.c:109` | `static void test_inline_text_decoration(void **state)` |
| `test_inline_text_decoration_color_style` | function | `tests/test_css.c:2297` | `static void test_inline_text_decoration_color_style(void **state)` |
| `test_inline_text_decoration_thickness` | function | `tests/test_css.c:2326` | `static void test_inline_text_decoration_thickness(void **state)` |
| `test_inline_text_rendering` | function | `tests/test_css.c:3374` | `static void test_inline_text_rendering(void **state)` |
| `test_inline_touch_action` | function | `tests/test_css.c:3417` | `static void test_inline_touch_action(void **state)` |
| `test_inline_transform_independent_cascade_combines` | function | `tests/test_css.c:3333` | `static void test_inline_transform_independent_cascade_combines(void **state)` |
| `test_inline_transform_rotate` | function | `tests/test_css.c:3182` | `static void test_inline_transform_rotate(void **state)` |
| `test_inline_transform_scale` | function | `tests/test_css.c:3142` | `static void test_inline_transform_scale(void **state)` |
| `test_inline_transform_skew` | function | `tests/test_css.c:3212` | `static void test_inline_transform_skew(void **state)` |
| `test_inline_transform_translate` | function | `tests/test_css.c:3091` | `static void test_inline_transform_translate(void **state)` |
| `test_inline_user_select` | function | `tests/test_css.c:2901` | `static void test_inline_user_select(void **state)` |
| `test_keyframes_overflow_skips_block_not_sheet` | function | `tests/test_css.c:3897` | `static void test_keyframes_overflow_skips_block_not_sheet(void **state)` |
| `test_layout_sheet_cascade_and_unset` | function | `tests/test_css.c:2767` | `static void test_layout_sheet_cascade_and_unset(void **state)` |
| `test_letter_word_spacing` | function | `tests/test_css.c:171` | `static void test_letter_word_spacing(void **state)` |
| `test_linear_gradient_basic` | function | `tests/test_css.c:522` | `static void test_linear_gradient_basic(void **state)` |
| `test_linear_gradient_directions` | function | `tests/test_css.c:533` | `static void test_linear_gradient_directions(void **state)` |
| `test_linear_gradient_fail_closed` | function | `tests/test_css.c:570` | `static void test_linear_gradient_fail_closed(void **state)` |
| `test_linear_gradient_positions_emitted` | function | `tests/test_css.c:3708` | `static void test_linear_gradient_positions_emitted(void **state)` |
| `test_linear_gradient_stops` | function | `tests/test_css.c:552` | `static void test_linear_gradient_stops(void **state)` |
| `test_list_style_type` | function | `tests/test_css.c:259` | `static void test_list_style_type(void **state)` |
| `test_logical_inset_and_sizes` | function | `tests/test_css.c:3506` | `static void test_logical_inset_and_sizes(void **state)` |
| `test_logical_margin_padding` | function | `tests/test_css.c:3481` | `static void test_logical_margin_padding(void **state)` |
| `test_malformed_inline_no_crash` | function | `tests/test_css.c:716` | `static void test_malformed_inline_no_crash(void **state)` |
| `test_math_clamp` | function | `tests/test_css.c:3456` | `static void test_math_clamp(void **state)` |
| `test_math_min_max_top_level` | function | `tests/test_css.c:3445` | `static void test_math_min_max_top_level(void **state)` |
| `test_math_nested_in_calc` | function | `tests/test_css.c:3466` | `static void test_math_nested_in_calc(void **state)` |
| `test_media_and_or` | function | `tests/test_css.c:1869` | `static void test_media_and_or(void **state)` |
| `test_media_prefers_color_scheme` | function | `tests/test_css.c:1838` | `static void test_media_prefers_color_scheme(void **state)` |
| `test_media_query_length_honours_its_unit` | function | `tests/test_css.c:4035` | `static void test_media_query_length_honours_its_unit(void **state)` |
| `test_media_screen_and_print` | function | `tests/test_css.c:1819` | `static void test_media_screen_and_print(void **state)` |
| `test_media_unknown_fails_closed` | function | `tests/test_css.c:1883` | `static void test_media_unknown_fails_closed(void **state)` |
| `test_media_width_queries` | function | `tests/test_css.c:1854` | `static void test_media_width_queries(void **state)` |
| `test_opacity` | function | `tests/test_css.c:208` | `static void test_opacity(void **state)` |
| `test_overflow` | function | `tests/test_css.c:2491` | `static void test_overflow(void **state)` |
| `test_parse_null_args` | function | `tests/test_css.c:1900` | `static void test_parse_null_args(void **state)` |
| `test_place_shorthands` | function | `tests/test_css.c:3529` | `static void test_place_shorthands(void **state)` |
| `test_position_and_insets` | function | `tests/test_css.c:2419` | `static void test_position_and_insets(void **state)` |
| `test_pseudo_content_before_after_separate` | function | `tests/test_css.c:1273` | `static void test_pseudo_content_before_after_separate(void **state)` |
| `test_pseudo_content_empty_without_pseudo` | function | `tests/test_css.c:1285` | `static void test_pseudo_content_empty_without_pseudo(void **state)` |
| `test_pseudo_does_not_claim_cascade_slot` | function | `tests/test_css.c:1360` | `static void test_pseudo_does_not_claim_cascade_slot(void **state)` |
| `test_pseudo_empty` | function | `tests/test_css.c:1460` | `static void test_pseudo_empty(void **state)` |
| `test_pseudo_geometry_does_not_leak_to_element` | function | `tests/test_css.c:1304` | `static void test_pseudo_geometry_does_not_leak_to_element(void **state)` |
| `test_pseudo_lang` | function | `tests/test_css.c:1497` | `static void test_pseudo_lang(void **state)` |
| `test_pseudo_link` | function | `tests/test_css.c:1112` | `static void test_pseudo_link(void **state)` |
| `test_pseudo_never_match_keeps_group` | function | `tests/test_css.c:1130` | `static void test_pseudo_never_match_keeps_group(void **state)` |
| `test_pseudo_nth_child` | function | `tests/test_css.c:1188` | `static void test_pseudo_nth_child(void **state)` |
| `test_pseudo_nth_last_child` | function | `tests/test_css.c:1211` | `static void test_pseudo_nth_last_child(void **state)` |
| `test_pseudo_nth_malformed_drops` | function | `tests/test_css.c:1407` | `static void test_pseudo_nth_malformed_drops(void **state)` |
| `test_pseudo_nth_of_type` | function | `tests/test_css.c:1444` | `static void test_pseudo_nth_of_type(void **state)` |
| `test_pseudo_of_type` | function | `tests/test_css.c:1425` | `static void test_pseudo_of_type(void **state)` |
| `test_pseudo_root_and_form_state` | function | `tests/test_css.c:1222` | `static void test_pseudo_root_and_form_state(void **state)` |
| `test_pseudo_specificity` | function | `tests/test_css.c:1372` | `static void test_pseudo_specificity(void **state)` |
| `test_pseudo_structural` | function | `tests/test_css.c:1168` | `static void test_pseudo_structural(void **state)` |
| `test_pseudo_target` | function | `tests/test_css.c:1486` | `static void test_pseudo_target(void **state)` |
| `test_pseudo_unknown_drops_selector` | function | `tests/test_css.c:1246` | `static void test_pseudo_unknown_drops_selector(void **state)` |
| `test_pseudo_with_sibling_combinator` | function | `tests/test_css.c:1390` | `static void test_pseudo_with_sibling_combinator(void **state)` |
| `test_rem_rebase_62_5_percent_idiom` | function | `tests/test_css.c:4020` | `static void test_rem_rebase_62_5_percent_idiom(void **state)` |
| `test_rem_rebase_absent_root_declaration_is_byte_identical` | function | `tests/test_css.c:3949` | `static void test_rem_rebase_absent_root_declaration_is_byte_identical(void **state)` |
| `test_rem_rebase_applies_to_box_lengths` | function | `tests/test_css.c:3935` | `static void test_rem_rebase_applies_to_box_lengths(void **state)` |
| `test_rem_rebase_honours_root_pseudo_class` | function | `tests/test_css.c:3961` | `static void test_rem_rebase_honours_root_pseudo_class(void **state)` |
| `test_rem_rebase_ignores_identifier_lookalikes` | function | `tests/test_css.c:4005` | `static void test_rem_rebase_ignores_identifier_lookalikes(void **state)` |
| `test_rem_rebase_leaves_quoted_text_alone` | function | `tests/test_css.c:3994` | `static void test_rem_rebase_leaves_quoted_text_alone(void **state)` |
| `test_rem_rebase_skips_at_rule_prelude` | function | `tests/test_css.c:3971` | `static void test_rem_rebase_skips_at_rule_prelude(void **state)` |
| `test_rem_rebased_on_root_font_size` | function | `tests/test_css.c:3923` | `static void test_rem_rebased_on_root_font_size(void **state)` |
| `test_resolve_el_inline_only` | function | `tests/test_css.c:1518` | `static void test_resolve_el_inline_only(void **state)` |
| `test_resolve_null_safe` | function | `tests/test_css.c:1910` | `static void test_resolve_null_safe(void **state)` |
| `test_sheet_class_and_id` | function | `tests/test_css.c:906` | `static void test_sheet_class_and_id(void **state)` |
| `test_sheet_compound_selector` | function | `tests/test_css.c:926` | `static void test_sheet_compound_selector(void **state)` |
| `test_sheet_container_props` | function | `tests/test_css.c:354` | `static void test_sheet_container_props(void **state)` |
| `test_sheet_type_selector` | function | `tests/test_css.c:895` | `static void test_sheet_type_selector(void **state)` |
| `test_sheet_universal_and_group` | function | `tests/test_css.c:916` | `static void test_sheet_universal_and_group(void **state)` |
| `test_sibling_mixed_with_child` | function | `tests/test_css.c:1095` | `static void test_sibling_mixed_with_child(void **state)` |
| `test_table_sheet_cascade` | function | `tests/test_css.c:2940` | `static void test_table_sheet_cascade(void **state)` |
| `test_text_decoration_cascade` | function | `tests/test_css.c:983` | `static void test_text_decoration_cascade(void **state)` |
| `test_text_ext_cascade_and_important` | function | `tests/test_css.c:273` | `static void test_text_ext_cascade_and_important(void **state)` |
| `test_text_fill_color` | function | `tests/test_css.c:3636` | `static void test_text_fill_color(void **state)` |
| `test_text_indent` | function | `tests/test_css.c:239` | `static void test_text_indent(void **state)` |
| `test_text_overflow_and_word_break` | function | `tests/test_css.c:2530` | `static void test_text_overflow_and_word_break(void **state)` |
| `test_text_shadow` | function | `tests/test_css.c:186` | `static void test_text_shadow(void **state)` |
| `test_text_transform` | function | `tests/test_css.c:157` | `static void test_text_transform(void **state)` |
| `test_transform_origin` | function | `tests/test_css.c:3291` | `static void test_transform_origin(void **state)` |
| `test_unknown_props_ignored` | function | `tests/test_css.c:513` | `static void test_unknown_props_ignored(void **state)` |
| `test_url_value_dropped` | function | `tests/test_css.c:503` | `static void test_url_value_dropped(void **state)` |
| `test_vendor_prefixes` | function | `tests/test_css.c:4084` | `static void test_vendor_prefixes(void **state)` |
| `test_vertical_align` | function | `tests/test_css.c:218` | `static void test_vertical_align(void **state)` |
| `test_viewport_units_font_size` | function | `tests/test_css.c:2161` | `static void test_viewport_units_font_size(void **state)` |
| `test_viewport_units_in_calc_and_mathfn` | function | `tests/test_css.c:2153` | `static void test_viewport_units_in_calc_and_mathfn(void **state)` |
| `test_viewport_units_junk_fail_closed` | function | `tests/test_css.c:2169` | `static void test_viewport_units_junk_fail_closed(void **state)` |
| `test_visibility` | function | `tests/test_css.c:2474` | `static void test_visibility(void **state)` |
| `test_white_space` | function | `tests/test_css.c:248` | `static void test_white_space(void **state)` |
| `test_white_space_break_spaces` | function | `tests/test_css.c:3591` | `static void test_white_space_break_spaces(void **state)` |
| `assert_int_equal` | function | `tests/test_css_color.c:24` | `assert_int_equal(cc_parse(NULL, &C), CC_ERR_NULL_ARG);` |
| `assert_int_not_equal` | function | `tests/test_css_color.c:234` | `assert_int_not_equal(cc_parse("hsl(0,0%,150.5%)", &C), CC_OK);` |
| `assert_true` | function | `tests/test_css_color.c:180` | `assert_true(p >= 0);` |
| `cmocka_run_group_tests` | function | `tests/test_css_color.c:269` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_css_color.c:240` | `int main(void)` |
| `preprocessor` | function | `tests/test_css_color.c:193` | `* is how a page written by a preprocessor (`hsl(0,0%,15.8333333333%)`, the shape a
 * SASS/LESS c...` |
| `test_fractional_still_fails_closed` | function | `tests/test_css_color.c:232` | `static void test_fractional_still_fails_closed(void **state)` |
| `test_hex_bad` | function | `tests/test_css_color.c:58` | `static void test_hex_bad(void **state)` |
| `test_hex_long` | function | `tests/test_css_color.c:43` | `static void test_hex_long(void **state)` |
| `test_hex_long_alpha` | function | `tests/test_css_color.c:52` | `static void test_hex_long_alpha(void **state)` |
| `test_hex_short` | function | `tests/test_css_color.c:27` | `static void test_hex_short(void **state)` |
| `test_hex_short_alpha` | function | `tests/test_css_color.c:36` | `static void test_hex_short_alpha(void **state)` |
| `test_hsl` | function | `tests/test_css_color.c:133` | `static void test_hsl(void **state)` |
| `test_hsl_120` | function | `tests/test_css_color.c:139` | `static void test_hsl_120(void **state)` |
| `test_hsl_240` | function | `tests/test_css_color.c:146` | `static void test_hsl_240(void **state)` |
| `test_hsl_fractional_hue` | function | `tests/test_css_color.c:208` | `static void test_hsl_fractional_hue(void **state)` |
| `test_hsl_out_of_range` | function | `tests/test_css_color.c:159` | `static void test_hsl_out_of_range(void **state)` |
| `test_hsla` | function | `tests/test_css_color.c:153` | `static void test_hsla(void **state)` |
| `test_leading_dot_number` | function | `tests/test_css_color.c:224` | `static void test_leading_dot_number(void **state)` |
| `test_named` | function | `tests/test_css_color.c:99` | `static void test_named(void **state)` |
| `test_named_bad` | function | `tests/test_css_color.c:117` | `static void test_named_bad(void **state)` |
| `test_null_args` | function | `tests/test_css_color.c:21` | `static void test_null_args(void **state)` |
| `test_pack_unpack` | function | `tests/test_css_color.c:174` | `static void test_pack_unpack(void **state)` |
| `test_rgb_fractional` | function | `tests/test_css_color.c:215` | `static void test_rgb_fractional(void **state)` |
| `test_rgb_integer` | function | `tests/test_css_color.c:67` | `static void test_rgb_integer(void **state)` |
| `test_rgb_out_of_range` | function | `tests/test_css_color.c:89` | `static void test_rgb_out_of_range(void **state)` |
| `test_rgb_percent` | function | `tests/test_css_color.c:83` | `static void test_rgb_percent(void **state)` |
| `test_rgba_integer` | function | `tests/test_css_color.c:76` | `static void test_rgba_integer(void **state)` |
| `test_transparent_currentcolor` | function | `tests/test_css_color.c:125` | `static void test_transparent_currentcolor(void **state)` |
| `test_unsupported_syntax` | function | `tests/test_css_color.c:167` | `static void test_unsupported_syntax(void **state)` |
| `assert_int_equal` | function | `tests/test_css_drops.c:25` | `assert_int_equal(st, CSS_OK);` |
| `assert_non_null` | function | `tests/test_css_drops.c:103` | `assert_non_null(find_drop(&log, "color"));` |
| `assert_null` | function | `tests/test_css_drops.c:167` | `assert_null(strchr(it2[0].val, '\033'));` |
| `assert_string_equal` | function | `tests/test_css_drops.c:46` | `assert_string_equal(items[0].prop, "unknown-prop");` |
| `assert_true` | function | `tests/test_css_drops.c:158` | `assert_true(strlen(items[0].val) < CSS_DROP_VAL_MAX);` |
| `cmocka_run_group_tests` | function | `tests/test_css_drops.c:421` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `css_free` | function | `tests/test_css_drops.c:50` | `css_free(sh);` |
| `find_drop` | function | `tests/test_css_drops.c:31` | `static const css_drop *find_drop(const css_drop_log *log, const char *prop)` |
| `main` | function | `tests/test_css_drops.c:391` | `int main(void)` |
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
| `EPS` | macro | `tests/test_css_length.c:19` | `#define EPS` |
| `assert_false` | function | `tests/test_css_length.c:234` | `assert_false(cl_unit_is_font_relative("rem", 0));` |
| `assert_int_equal` | function | `tests/test_css_length.c:23` | `assert_int_equal(cl_resolve(value, ctx, &px), CL_OK);` |
| `assert_int_not_equal` | function | `tests/test_css_length.c:203` | `assert_int_not_equal(cl_resolve(big, &c, &px), CL_OK);` |
| `assert_string_equal` | function | `tests/test_css_length.c:287` | `assert_string_equal(e, "em");` |
| `assert_true` | function | `tests/test_css_length.c:30` | `assert_true(px == -12345.0);` |
| `cmocka_run_group_tests` | function | `tests/test_css_length.c:474` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `expect_err` | function | `tests/test_css_length.c:26` | `static void expect_err(const char *value, const cl_ctx *ctx, cl_status want)` |
| `main` | function | `tests/test_css_length.c:449` | `int main(void)` |
| `px_of` | function | `tests/test_css_length.c:20` | `static double px_of(const char *value, const cl_ctx *ctx)` |
| `test_absolute_units` | function | `tests/test_css_length.c:45` | `static void test_absolute_units(void **state)` |
| `test_case_insensitive` | function | `tests/test_css_length.c:129` | `static void test_case_insensitive(void **state)` |
| `test_cl_number` | function | `tests/test_css_length.c:273` | `static void test_cl_number(void **state)` |
| `test_em_derivative` | function | `tests/test_css_length.c:379` | `static void test_em_derivative(void **state)` |
| `test_em_refit` | function | `tests/test_css_length.c:425` | `static void test_em_refit(void **state)` |
| `test_font_metric_fallbacks` | function | `tests/test_css_length.c:75` | `static void test_font_metric_fallbacks(void **state)` |
| `test_font_relative_classifier` | function | `tests/test_css_length.c:226` | `static void test_font_relative_classifier(void **state)` |
| `test_font_relative_em_rem` | function | `tests/test_css_length.c:61` | `static void test_font_relative_em_rem(void **state)` |
| `test_initial_ctx` | function | `tests/test_css_length.c:258` | `static void test_initial_ctx(void **state)` |
| `test_is_length_unit` | function | `tests/test_css_length.c:243` | `static void test_is_length_unit(void **state)` |
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
| `assert_int_equal` | function | `tests/test_data_url.c:33` | `assert_int_equal(du_is_data_url("https://example.com/logo.png"), 0);` |
| `assert_int_not_equal` | function | `tests/test_data_url.c:27` | `assert_int_not_equal(du_is_data_url("Data:,plain"), 0);` |
| `assert_memory_equal` | function | `tests/test_data_url.c:51` | `assert_memory_equal(payload, "QQ==", 4);` |
| `assert_non_null` | function | `tests/test_data_url.c:49` | `assert_non_null(payload);` |
| `assert_null` | function | `tests/test_data_url.c:198` | `assert_null(out);` |
| `assert_true` | function | `tests/test_data_url.c:261` | `assert_true(out_len >= 8);` |
| `cmocka_run_group_tests` | function | `tests/test_data_url.c:293` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `free` | function | `tests/test_data_url.c:119` | `free(url);` |
| `main` | function | `tests/test_data_url.c:267` | `int main(void)` |
| `memset` | function | `tests/test_data_url.c:112` | `memset(url + strlen(url), 'A', huge_len);` |
| `test_decode_bad_length_not_multiple_of_4` | function | `tests/test_data_url.c:192` | `static void test_decode_bad_length_not_multiple_of_4(void **state)` |
| `test_decode_empty` | function | `tests/test_data_url.c:182` | `static void test_decode_empty(void **state)` |
| `test_decode_invalid_character` | function | `tests/test_data_url.c:209` | `static void test_decode_invalid_character(void **state)` |
| `test_decode_multi_group` | function | `tests/test_data_url.c:170` | `static void test_decode_multi_group(void **state)` |
| `test_decode_no_padding_needed` | function | `tests/test_data_url.c:158` | `static void test_decode_no_padding_needed(void **state)` |
| `test_decode_nulls` | function | `tests/test_data_url.c:235` | `static void test_decode_nulls(void **state)` |
| `test_decode_one_byte_double_pad` | function | `tests/test_data_url.c:134` | `static void test_decode_one_byte_double_pad(void **state)` |
| `test_decode_padding_in_wrong_position` | function | `tests/test_data_url.c:200` | `static void test_decode_padding_in_wrong_position(void **state)` |
| `test_decode_too_large` | function | `tests/test_data_url.c:220` | `static void test_decode_too_large(void **state)` |
| `test_decode_two_bytes_single_pad` | function | `tests/test_data_url.c:145` | `static void test_decode_two_bytes_single_pad(void **state)` |
| `test_end_to_end_png_data_uri` | function | `tests/test_data_url.c:246` | `static void test_end_to_end_png_data_uri(void **state)` |
| `test_is_data_url_false` | function | `tests/test_data_url.c:30` | `static void test_is_data_url_false(void **state)` |
| `test_is_data_url_true` | function | `tests/test_data_url.c:22` | `static void test_is_data_url_true(void **state)` |
| `test_payload_base64_flag_case_insensitive` | function | `tests/test_data_url.c:96` | `static void test_payload_base64_flag_case_insensitive(void **state)` |
| `test_payload_basic` | function | `tests/test_data_url.c:42` | `static void test_payload_basic(void **state)` |
| `test_payload_empty` | function | `tests/test_data_url.c:62` | `static void test_payload_empty(void **state)` |
| `test_payload_no_comma` | function | `tests/test_data_url.c:88` | `static void test_payload_no_comma(void **state)` |
| `test_payload_no_mediatype` | function | `tests/test_data_url.c:53` | `static void test_payload_no_mediatype(void **state)` |
| `test_payload_not_data_url` | function | `tests/test_data_url.c:72` | `static void test_payload_not_data_url(void **state)` |
| `test_payload_nulls` | function | `tests/test_data_url.c:121` | `static void test_payload_nulls(void **state)` |
| `test_payload_percent_encoded_not_supported` | function | `tests/test_data_url.c:80` | `static void test_payload_percent_encoded_not_supported(void **state)` |
| `test_payload_too_large` | function | `tests/test_data_url.c:105` | `static void test_payload_too_large(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_disk_store.c:7` | `#define _POSIX_C_SOURCE` |
| `assert_int_equal` | function | `tests/test_disk_store.c:80` | `assert_int_equal(ds_write(f->path, KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, sizeof PT - 1), DS_OK);` |
| `assert_memory_equal` | function | `tests/test_disk_store.c:85` | `assert_memory_equal(out, PT, sizeof PT - 1);` |
| `assert_null` | function | `tests/test_disk_store.c:147` | `assert_null(out);` |
| `assert_true` | function | `tests/test_disk_store.c:155` | `assert_true(fd >= 0);` |
| `close` | function | `tests/test_disk_store.c:160` | `close(fd);` |
| `closedir` | function | `tests/test_disk_store.c:57` | `closedir(d);` |
| `cmocka_run_group_tests` | function | `tests/test_disk_store.c:193` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `count_dir_entries` | function | `tests/test_disk_store.c:64` | `static size_t count_dir_entries(const char *dir)` |
| `dir` | type_alias | `tests/test_disk_store.c:32` | `typedef struct fixture { char dir[64];` |
| `ds_free` | function | `tests/test_disk_store.c:86` | `ds_free(out, out_len);` |
| `fixture` | struct | `tests/test_disk_store.c:33` | `` |
| `free` | function | `tests/test_disk_store.c:60` | `free(f);` |
| `main` | function | `tests/test_disk_store.c:180` | `int main(void)` |
| `memcpy` | function | `tests/test_disk_store.c:143` | `memcpy(bad, KEY, LS_KEY_LEN);` |
| `rmdir` | function | `tests/test_disk_store.c:59` | `rmdir(f->dir);` |
| `setup` | function | `tests/test_disk_store.c:34` | `static int setup(void **state)` |
| `snprintf` | function | `tests/test_disk_store.c:40` | `snprintf(f->path, sizeof f->path, "%s/state", f->dir);` |
| `strcpy` | function | `tests/test_disk_store.c:38` | `strcpy(f->dir, "/tmp/freedom_ds_XXXXXX");` |
| `teardown` | function | `tests/test_disk_store.c:44` | `static int teardown(void **state)` |
| `test_empty` | function | `tests/test_disk_store.c:98` | `static void test_empty(void **state)` |
| `test_missing_and_null` | function | `tests/test_disk_store.c:167` | `static void test_missing_and_null(void **state)` |
| `test_no_temp_left` | function | `tests/test_disk_store.c:116` | `static void test_no_temp_left(void **state)` |
| `test_overwrite` | function | `tests/test_disk_store.c:123` | `static void test_overwrite(void **state)` |
| `test_permissions` | function | `tests/test_disk_store.c:107` | `static void test_permissions(void **state)` |
| `test_roundtrip` | function | `tests/test_disk_store.c:77` | `static void test_roundtrip(void **state)` |
| `test_roundtrip_chacha` | function | `tests/test_disk_store.c:88` | `static void test_roundtrip_chacha(void **state)` |
| `test_tamper_on_disk` | function | `tests/test_disk_store.c:149` | `static void test_tamper_on_disk(void **state)` |
| `test_wrong_key` | function | `tests/test_disk_store.c:137` | `static void test_wrong_key(void **state)` |
| `unlink` | function | `tests/test_disk_store.c:55` | `unlink(p);` |
| `DOC` | macro | `tests/test_dom.c:54` | `#define DOC(state)` |
| `IDX` | macro | `tests/test_dom.c:56` | `#define IDX(state)` |
| `assert_false` | function | `tests/test_dom.c:142` | `assert_false(dom_precedes(idx, go, main_id));` |
| `assert_int_equal` | function | `tests/test_dom.c:63` | `assert_int_equal(dom_build(NULL, &idx), DOM_ERR_NULL_ARG);` |
| `assert_int_not_equal` | function | `tests/test_dom.c:91` | `assert_int_not_equal(main_id, DOM_NODE_NONE);` |
| `assert_non_null` | function | `tests/test_dom.c:94` | `assert_non_null(tag);` |
| `assert_null` | function | `tests/test_dom.c:179` | `assert_null(dom_get_attribute(idx, main_id, "data-missing", NULL));` |
| `assert_string_equal` | function | `tests/test_dom.c:95` | `assert_string_equal(tag, "div");` |
| `assert_true` | function | `tests/test_dom.c:82` | `assert_true(dom_node_count(IDX(state)) > 0);` |
| `cmocka_run_group_tests` | function | `tests/test_dom.c:526` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `dom_free` | function | `tests/test_dom.c:48` | `dom_free((dom_index *)pair[1]);` |
| `dom_get_by_tag` | function | `tests/test_dom.c:367` | `dom_get_by_tag(idx, "p", buf, 8);` |
| `free` | function | `tests/test_dom.c:50` | `free(pair);` |
| `hp_document_free` | function | `tests/test_dom.c:49` | `hp_document_free((hp_document *)pair[0]);` |
| `main` | function | `tests/test_dom.c:490` | `int main(void)` |
| `rule` | function | `tests/test_dom.c:405` | `* silently drops the whole rule (fail closed), so the title read black-on-teal
 * instead of the ...` |
| `setup_doc` | function | `tests/test_dom.c:32` | `static int setup_doc(void **state)` |
| `teardown_doc` | function | `tests/test_dom.c:44` | `static int teardown_doc(void **state)` |
| `test_append_rejects_cycle` | function | `tests/test_dom.c:258` | `static void test_append_rejects_cycle(void **state)` |
| `test_attributes` | function | `tests/test_dom.c:170` | `static void test_attributes(void **state)` |
| `test_build_null_args` | function | `tests/test_dom.c:59` | `static void test_build_null_args(void **state)` |
| `test_by_class` | function | `tests/test_dom.c:108` | `static void test_by_class(void **state)` |
| `test_by_tag` | function | `tests/test_dom.c:117` | `static void test_by_tag(void **state)` |
| `test_by_tag_results_in_document_order` | function | `tests/test_dom.c:126` | `static void test_by_tag_results_in_document_order(void **state)` |
| `test_construction_invalid_args` | function | `tests/test_dom.c:326` | `static void test_construction_invalid_args(void **state)` |
| `test_create_and_append` | function | `tests/test_dom.c:240` | `static void test_create_and_append(void **state)` |
| `test_document_order` | function | `tests/test_dom.c:136` | `static void test_document_order(void **state)` |
| `test_free_null_and_double` | function | `tests/test_dom.c:69` | `static void test_free_null_and_double(void **state)` |
| `test_get_by_id` | function | `tests/test_dom.c:87` | `static void test_get_by_id(void **state)` |
| `test_get_by_id_absent` | function | `tests/test_dom.c:101` | `static void test_get_by_id_absent(void **state)` |
| `test_get_inner_html` | function | `tests/test_dom.c:334` | `static void test_get_inner_html(void **state)` |
| `test_matches_and_closest` | function | `tests/test_dom.c:459` | `static void test_matches_and_closest(void **state)` |
| `test_navigation` | function | `tests/test_dom.c:150` | `static void test_navigation(void **state)` |
| `test_node_count` | function | `tests/test_dom.c:80` | `static void test_node_count(void **state)` |
| `test_query_selector_all_counts` | function | `tests/test_dom.c:376` | `static void test_query_selector_all_counts(void **state)` |
| `test_query_selector_combinators` | function | `tests/test_dom.c:387` | `static void test_query_selector_combinators(void **state)` |
| `test_query_selector_fail_closed` | function | `tests/test_dom.c:472` | `static void test_query_selector_fail_closed(void **state)` |
| `test_query_selector_nth_and_structural` | function | `tests/test_dom.c:434` | `static void test_query_selector_nth_and_structural(void **state)` |
| `test_query_selector_scope_is_descendants_only` | function | `tests/test_dom.c:447` | `static void test_query_selector_scope_is_descendants_only(void **state)` |
| `test_query_selector_type_class_id` | function | `tests/test_dom.c:362` | `static void test_query_selector_type_class_id(void **state)` |
| `test_remove_attribute` | function | `tests/test_dom.c:293` | `static void test_remove_attribute(void **state)` |
| `test_remove_child` | function | `tests/test_dom.c:268` | `static void test_remove_child(void **state)` |
| `test_set_and_get_document_title` | function | `tests/test_dom.c:228` | `static void test_set_and_get_document_title(void **state)` |
| `test_set_attribute_reindexes_id` | function | `tests/test_dom.c:280` | `static void test_set_attribute_reindexes_id(void **state)` |
| `test_set_inner_html` | function | `tests/test_dom.c:310` | `static void test_set_inner_html(void **state)` |
| `test_set_text_content_changes_tree` | function | `tests/test_dom.c:195` | `static void test_set_text_content_changes_tree(void **state)` |
| `test_set_text_content_empty_clears` | function | `tests/test_dom.c:213` | `static void test_set_text_content_empty_clears(void **state)` |
| `test_set_text_content_invalid_node` | function | `tests/test_dom.c:223` | `static void test_set_text_content_invalid_node(void **state)` |
| `test_text_content_read` | function | `tests/test_dom.c:184` | `static void test_text_content_read(void **state)` |
| `assert_int_equal` | function | `tests/test_dom_debug.c:38` | `assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK);` |
| `assert_non_null` | function | `tests/test_dom_debug.c:39` | `assert_non_null(d);` |
| `assert_null` | function | `tests/test_dom_debug.c:209` | `assert_null(strstr(buf, "[boxes]"));` |
| `assert_true` | function | `tests/test_dom_debug.c:49` | `assert_true(n > 0);` |
| `build` | function | `tests/test_dom_debug.c:36` | `static rd_doc *build(pv_view *v, rdp_caps caps)` |
| `caps_css_on` | function | `tests/test_dom_debug.c:28` | `static rdp_caps caps_css_on(void)` |
| `cmocka_run_group_tests` | function | `tests/test_dom_debug.c:280` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `dd_format` | function | `tests/test_dom_debug.c:207` | `dd_format(d, buf, sizeof buf);` |
| `main` | function | `tests/test_dom_debug.c:268` | `int main(void)` |
| `memset` | function | `tests/test_dom_debug.c:123` | `memset(&b, 0, sizeof b);` |
| `pv_free` | function | `tests/test_dom_debug.c:86` | `pv_free(v);` |
| `pv_set_block_id` | function | `tests/test_dom_debug.c:120` | `pv_set_block_id(v, 0);` |
| `pv_set_container` | function | `tests/test_dom_debug.c:98` | `pv_set_container(v, 7, BX_DISPLAY_GRID, 0, FX_JUSTIFY_START, 3, 0, -1, 0);` |
| `pv_set_text_ext` | function | `tests/test_dom_debug.c:164` | `pv_set_text_ext(v, &te);` |
| `pv_text_ext_reset` | function | `tests/test_dom_debug.c:160` | `pv_text_ext_reset(&te);` |
| `rd_free` | function | `tests/test_dom_debug.c:84` | `rd_free(d);` |
| `test_box_tree_width_cap` | function | `tests/test_dom_debug.c:115` | `static void test_box_tree_width_cap(void **state)` |
| `test_control_bytes_kept_on_one_line` | function | `tests/test_dom_debug.c:244` | `static void test_control_bytes_kept_on_one_line(void **state)` |
| `test_grid_container_annotation` | function | `tests/test_dom_debug.c:91` | `static void test_grid_container_annotation(void **state)` |
| `test_heading_paragraph_link` | function | `tests/test_dom_debug.c:58` | `static void test_heading_paragraph_link(void **state)` |
| `test_no_box_tree_without_css` | function | `tests/test_dom_debug.c:196` | `static void test_no_box_tree_without_css(void **state)` |
| `test_null_doc_is_empty_header` | function | `tests/test_dom_debug.c:44` | `static void test_null_doc_is_empty_header(void **state)` |
| `test_truncation_no_overflow` | function | `tests/test_dom_debug.c:216` | `static void test_truncation_no_overflow(void **state)` |
| `test_visibility_overflow_cursor_and_text_wrap` | function | `tests/test_dom_debug.c:153` | `static void test_visibility_overflow_cursor_and_text_wrap(void **state)` |
| `assert_int_equal` | function | `tests/test_download.c:26` | `assert_int_equal(dl_should_download(NULL, "ATTACHMENT"), 1);` |
| `assert_null` | function | `tests/test_download.c:124` | `assert_null(strchr(out, '/'));` |
| `assert_string_equal` | function | `tests/test_download.c:54` | `assert_string_equal(dl_ext_for_type("application/pdf"), ".pdf");` |
| `assert_true` | function | `tests/test_download.c:125` | `assert_true(out[0] != '.');` |
| `builder` | function | `tests/test_download.c:8` | `* builder (join, separator rejection, overflow, NULL), and the size cap.
 */

#include <setjmp.h>...` |
| `cmocka_run_group_tests` | function | `tests/test_download.c:227` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_download.c:203` | `int main(void)` |
| `test_build_path_basic` | function | `tests/test_download.c:157` | `static void test_build_path_basic(void **state)` |
| `test_build_path_null_args` | function | `tests/test_download.c:185` | `static void test_build_path_null_args(void **state)` |
| `test_build_path_overflow` | function | `tests/test_download.c:178` | `static void test_build_path_overflow(void **state)` |
| `test_build_path_rejects_separator_in_name` | function | `tests/test_download.c:171` | `static void test_build_path_rejects_separator_in_name(void **state)` |
| `test_build_path_trailing_slash` | function | `tests/test_download.c:164` | `static void test_build_path_trailing_slash(void **state)` |
| `test_check_size` | function | `tests/test_download.c:196` | `static void test_check_size(void **state)` |
| `test_ext_known_types` | function | `tests/test_download.c:51` | `static void test_ext_known_types(void **state)` |
| `test_ext_unknown_type` | function | `tests/test_download.c:62` | `static void test_ext_unknown_type(void **state)` |
| `test_pick_appends_extension_when_missing` | function | `tests/test_download.c:98` | `static void test_pick_appends_extension_when_missing(void **state)` |
| `test_pick_fallback_when_empty` | function | `tests/test_download.c:128` | `static void test_pick_fallback_when_empty(void **state)` |
| `test_pick_from_disposition_ext_form` | function | `tests/test_download.c:80` | `static void test_pick_from_disposition_ext_form(void **state)` |
| `test_pick_from_disposition_quoted` | function | `tests/test_download.c:71` | `static void test_pick_from_disposition_quoted(void **state)` |
| `test_pick_from_url_segment` | function | `tests/test_download.c:90` | `static void test_pick_from_url_segment(void **state)` |
| `test_pick_keeps_existing_extension` | function | `tests/test_download.c:107` | `static void test_pick_keeps_existing_extension(void **state)` |
| `test_pick_null_out` | function | `tests/test_download.c:140` | `static void test_pick_null_out(void **state)` |
| `test_pick_overflow_fails_closed` | function | `tests/test_download.c:147` | `static void test_pick_overflow_fails_closed(void **state)` |
| `test_pick_traversal_contained` | function | `tests/test_download.c:116` | `static void test_pick_traversal_contained(void **state)` |
| `test_should_binary_types` | function | `tests/test_download.c:40` | `static void test_should_binary_types(void **state)` |
| `test_should_renderable_types` | function | `tests/test_download.c:29` | `static void test_should_renderable_types(void **state)` |
| `article` | function | `tests/test_flex_layout.c:351` | `* article (slashdot-cols probe: score 13.41). */

static void test_float_pack_m_holy_grail_pull_u...` |
| `assert_float_equal` | function | `tests/test_flex_layout.c:645` | `assert_float_equal(fx_auto_min_size(40.0, 300.0, -1.0, 0), 40.0, 1e-9);` |
| `assert_int_equal` | function | `tests/test_flex_layout.c:35` | `assert_int_equal(fx_flex_line(it, 2, 300, 0, FX_JUSTIFY_START, out), FX_OK);` |
| `assert_item` | function | `tests/test_flex_layout.c:25` | `static void assert_item(fx_result r, double pos, double size)` |
| `assert_string_equal` | function | `tests/test_flex_layout.c:628` | `assert_string_equal(fx_justify_name(FX_JUSTIFY_START), "start");` |
| `assert_true` | function | `tests/test_flex_layout.c:27` | `assert_true(dbl_eq(r.pos, pos));` |
| `cmocka_run_group_tests` | function | `tests/test_flex_layout.c:1001` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `fx_grid_cell` | function | `tests/test_flex_layout.c:190` | `fx_grid_cell(0, 3, &r, &c);` |
| `main` | function | `tests/test_flex_layout.c:936` | `int main(void)` |
| `test_area_hash_basics` | function | `tests/test_flex_layout.c:775` | `static void test_area_hash_basics(void **state)` |
| `test_areas_non_rectangular_is_rejected` | function | `tests/test_flex_layout.c:853` | `static void test_areas_non_rectangular_is_rejected(void **state)` |
| `test_areas_null_cell` | function | `tests/test_flex_layout.c:821` | `static void test_areas_null_cell(void **state)` |
| `test_areas_parse_and_resolve` | function | `tests/test_flex_layout.c:787` | `static void test_areas_parse_and_resolve(void **state)` |
| `test_areas_parse_bounds` | function | `tests/test_flex_layout.c:885` | `static void test_areas_parse_bounds(void **state)` |
| `test_areas_parse_fails_closed` | function | `tests/test_flex_layout.c:867` | `static void test_areas_parse_fails_closed(void **state)` |
| `test_areas_rect_spans_rows_and_cols` | function | `tests/test_flex_layout.c:836` | `static void test_areas_rect_spans_rows_and_cols(void **state)` |
| `test_auto_min_size_is_min_content` | function | `tests/test_flex_layout.c:642` | `static void test_auto_min_size_is_min_content(void **state)` |
| `test_flex_errors` | function | `tests/test_flex_layout.c:145` | `static void test_flex_errors(void **state)` |
| `test_flex_zero_items_is_noop` | function | `tests/test_flex_layout.c:140` | `static void test_flex_zero_items_is_noop(void **state)` |
| `test_float_insets_both_sides_take_the_tightest` | function | `tests/test_flex_layout.c:483` | `static void test_float_insets_both_sides_take_the_tightest(void **state)` |
| `test_float_insets_edges` | function | `tests/test_flex_layout.c:520` | `static void test_float_insets_edges(void **state)` |
| `test_float_insets_left_overlapping_line` | function | `tests/test_flex_layout.c:446` | `static void test_float_insets_left_overlapping_line(void **state)` |
| `test_float_insets_line_past_bottom_is_full_width` | function | `tests/test_flex_layout.c:456` | `static void test_float_insets_line_past_bottom_is_full_width(void **state)` |
| `test_float_insets_never_starve_the_line` | function | `tests/test_flex_layout.c:498` | `static void test_float_insets_never_starve_the_line(void **state)` |
| `test_float_insets_right` | function | `tests/test_flex_layout.c:473` | `static void test_float_insets_right(void **state)` |
| `test_float_pack_edges` | function | `tests/test_flex_layout.c:540` | `static void test_float_pack_edges(void **state)` |
| `test_float_pack_left` | function | `tests/test_flex_layout.c:310` | `static void test_float_pack_left(void **state)` |
| `test_float_pack_left_and_right` | function | `tests/test_flex_layout.c:321` | `static void test_float_pack_left_and_right(void **state)` |
| `test_float_pack_m_errors` | function | `tests/test_flex_layout.c:421` | `static void test_float_pack_m_errors(void **state)` |
| `test_float_pack_m_positive_margin_widens` | function | `tests/test_flex_layout.c:389` | `static void test_float_pack_m_positive_margin_widens(void **state)` |
| `test_float_pack_m_right_float_negative_margin` | function | `tests/test_flex_layout.c:405` | `static void test_float_pack_m_right_float_negative_margin(void **state)` |
| `test_float_pack_m_zero_margins_match_wrap` | function | `tests/test_flex_layout.c:369` | `static void test_float_pack_m_zero_margins_match_wrap(void **state)` |
| `test_float_pack_two_right` | function | `tests/test_flex_layout.c:333` | `static void test_float_pack_two_right(void **state)` |
| `test_float_pack_wrap_errors` | function | `tests/test_flex_layout.c:616` | `static void test_float_pack_wrap_errors(void **state)` |
| `test_float_pack_wrap_fits_matches_v1` | function | `tests/test_flex_layout.c:571` | `static void test_float_pack_wrap_fits_matches_v1(void **state)` |
| `test_float_pack_wrap_full_width_stack` | function | `tests/test_flex_layout.c:557` | `static void test_float_pack_wrap_full_width_stack(void **state)` |
| `test_float_pack_wrap_partial` | function | `tests/test_flex_layout.c:594` | `static void test_float_pack_wrap_partial(void **state)` |
| `test_gap_start` | function | `tests/test_flex_layout.c:67` | `static void test_gap_start(void **state)` |
| `test_grid_cell` | function | `tests/test_flex_layout.c:186` | `static void test_grid_cell(void **state)` |
| `test_grid_columns` | function | `tests/test_flex_layout.c:157` | `static void test_grid_columns(void **state)` |
| `test_grid_columns_edges` | function | `tests/test_flex_layout.c:176` | `static void test_grid_columns_edges(void **state)` |
| `test_grid_columns_too_narrow_clamps_to_zero` | function | `tests/test_flex_layout.c:169` | `static void test_grid_columns_too_narrow_clamps_to_zero(void **state)` |
| `test_grid_place_explicit_out_of_range_clamps` | function | `tests/test_flex_layout.c:927` | `static void test_grid_place_explicit_out_of_range_clamps(void **state)` |
| `test_grid_place_null_fixed_is_unchanged` | function | `tests/test_flex_layout.c:915` | `static void test_grid_place_null_fixed_is_unchanged(void **state)` |
| `test_grid_place_rowspan` | function | `tests/test_flex_layout.c:293` | `static void test_grid_place_rowspan(void **state)` |
| `test_grid_place_span_basic` | function | `tests/test_flex_layout.c:254` | `static void test_grid_place_span_basic(void **state)` |
| `test_grid_place_span_clamps_and_defaults` | function | `tests/test_flex_layout.c:277` | `static void test_grid_place_span_clamps_and_defaults(void **state)` |
| `test_grid_place_span_wraps_when_it_does_not_fit` | function | `tests/test_flex_layout.c:265` | `static void test_grid_place_span_wraps_when_it_does_not_fit(void **state)` |
| `test_grid_weighted_all_auto_matches_equal` | function | `tests/test_flex_layout.c:221` | `static void test_grid_weighted_all_auto_matches_equal(void **state)` |
| `test_grid_weighted_errors` | function | `tests/test_flex_layout.c:244` | `static void test_grid_weighted_errors(void **state)` |
| `test_grid_weighted_fixed_overflow_zeroes_fr` | function | `tests/test_flex_layout.c:234` | `static void test_grid_weighted_fixed_overflow_zeroes_fr(void **state)` |
| `test_grid_weighted_fixed_px_reserved_first` | function | `tests/test_flex_layout.c:209` | `static void test_grid_weighted_fixed_px_reserved_first(void **state)` |
| `test_grid_weighted_fr` | function | `tests/test_flex_layout.c:197` | `static void test_grid_weighted_fr(void **state)` |
| `test_grow_equal` | function | `tests/test_flex_layout.c:30` | `static void test_grow_equal(void **state)` |
| `test_grow_weighted` | function | `tests/test_flex_layout.c:39` | `static void test_grow_weighted(void **state)` |
| `test_justify_center` | function | `tests/test_flex_layout.c:76` | `static void test_justify_center(void **state)` |
| `test_justify_end` | function | `tests/test_flex_layout.c:85` | `static void test_justify_end(void **state)` |
| `test_justify_name` | function | `tests/test_flex_layout.c:625` | `static void test_justify_name(void **state)` |
| `test_justify_space_around` | function | `tests/test_flex_layout.c:103` | `static void test_justify_space_around(void **state)` |
| `test_justify_space_between` | function | `tests/test_flex_layout.c:94` | `static void test_justify_space_between(void **state)` |
| `test_justify_space_evenly` | function | `tests/test_flex_layout.c:112` | `static void test_justify_space_evenly(void **state)` |
| `test_multicol_used_counts` | function | `tests/test_flex_layout.c:669` | `static void test_multicol_used_counts(void **state)` |
| `test_multicol_used_edges` | function | `tests/test_flex_layout.c:706` | `static void test_multicol_used_edges(void **state)` |
| `test_negative_fields_clamped` | function | `tests/test_flex_layout.c:130` | `static void test_negative_fields_clamped(void **state)` |
| `test_shrink_equal` | function | `tests/test_flex_layout.c:48` | `static void test_shrink_equal(void **state)` |
| `test_shrink_with_min_clamp` | function | `tests/test_flex_layout.c:57` | `static void test_shrink_with_min_clamp(void **state)` |
| `test_space_between_single_item_is_start` | function | `tests/test_flex_layout.c:122` | `static void test_space_between_single_item_is_start(void **state)` |
| `to` | function | `tests/test_flex_layout.c:269` | `* jumps to (1,0);` |
| `assert_int_equal` | function | `tests/test_form.c:29` | `assert_int_equal(fm_encode(f, 2, out, sizeof out, &len), FM_OK);` |
| `assert_null` | function | `tests/test_form.c:86` | `assert_null(p.content_type);` |
| `assert_string_equal` | function | `tests/test_form.c:30` | `assert_string_equal(out, "q=hello&lang=en");` |
| `cmocka_run_group_tests` | function | `tests/test_form.c:229` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_form.c:206` | `int main(void)` |
| `test_block_foreign_scheme` | function | `tests/test_form.c:154` | `static void test_block_foreign_scheme(void **state)` |
| `test_block_http_downgrade` | function | `tests/test_form.c:144` | `static void test_block_http_downgrade(void **state)` |
| `test_block_null_field_name` | function | `tests/test_form.c:182` | `static void test_block_null_field_name(void **state)` |
| `test_block_relative_action_on_local_base` | function | `tests/test_form.c:163` | `static void test_block_relative_action_on_local_base(void **state)` |
| `test_block_too_many_fields` | function | `tests/test_form.c:172` | `static void test_block_too_many_fields(void **state)` |
| `test_build_null_args` | function | `tests/test_form.c:191` | `static void test_build_null_args(void **state)` |
| `test_encode_basic` | function | `tests/test_form.c:23` | `static void test_encode_basic(void **state)` |
| `test_encode_empty_and_nameless` | function | `tests/test_form.c:50` | `static void test_encode_empty_and_nameless(void **state)` |
| `test_encode_null_args` | function | `tests/test_form.c:66` | `static void test_encode_null_args(void **state)` |
| `test_encode_overflow_fails_closed` | function | `tests/test_form.c:58` | `static void test_encode_overflow_fails_closed(void **state)` |
| `test_encode_space_and_reserved` | function | `tests/test_form.c:33` | `static void test_encode_space_and_reserved(void **state)` |
| `test_encode_unreserved_kept` | function | `tests/test_form.c:42` | `static void test_encode_unreserved_kept(void **state)` |
| `test_get_absolute_https_action_ignores_base` | function | `tests/test_form.c:88` | `static void test_get_absolute_https_action_ignores_base(void **state)` |
| `test_get_action_cleaned_of_whitespace` | function | `tests/test_form.c:118` | `static void test_get_action_cleaned_of_whitespace(void **state)` |
| `test_get_empty_action_submits_to_base` | function | `tests/test_form.c:99` | `static void test_get_empty_action_submits_to_base(void **state)` |
| `test_get_no_fields_still_navigates` | function | `tests/test_form.c:198` | `static void test_get_no_fields_still_navigates(void **state)` |
| `test_get_relative_action_on_https_base` | function | `tests/test_form.c:77` | `static void test_get_relative_action_on_https_base(void **state)` |
| `test_get_replaces_existing_query` | function | `tests/test_form.c:108` | `static void test_get_replaces_existing_query(void **state)` |
| `test_post_builds_body` | function | `tests/test_form.c:129` | `static void test_post_builds_body(void **state)` |
| `assert_int_equal` | function | `tests/test_frame_clock.c:18` | `assert_int_equal(c.active, 0);` |
| `cmocka_run_group_tests_name` | function | `tests/test_frame_clock.c:60` | `return cmocka_run_group_tests_name("frame_clock", tests, NULL, NULL);` |
| `fc_init` | function | `tests/test_frame_clock.c:17` | `fc_init(&c);` |
| `fc_set_active` | function | `tests/test_frame_clock.c:28` | `fc_set_active(&c, 1);` |
| `main` | function | `tests/test_frame_clock.c:52` | `int main(void)` |
| `test_null_safe` | function | `tests/test_frame_clock.c:44` | `static void test_null_safe(void **state)` |
| `test_set_active_and_needs_tick` | function | `tests/test_frame_clock.c:22` | `static void test_set_active_and_needs_tick(void **state)` |
| `test_set_active_twice` | function | `tests/test_frame_clock.c:35` | `static void test_set_active_twice(void **state)` |
| `assert_int_equal` | function | `tests/test_freebug.c:25` | `assert_int_equal((int)fb_buffer_count(&b), 0);` |
| `assert_non_null` | function | `tests/test_freebug.c:33` | `assert_non_null(e0);` |
| `assert_null` | function | `tests/test_freebug.c:40` | `assert_null(fb_buffer_at(&b, 2));` |
| `assert_string_equal` | function | `tests/test_freebug.c:37` | `assert_string_equal(e0->text, "hello");` |
| `assert_true` | function | `tests/test_freebug.c:110` | `assert_true(b.total_bytes <= FB_MAX_TOTAL_BYTES);` |
| `cmocka_run_group_tests` | function | `tests/test_freebug.c:243` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `fb_buffer_free` | function | `tests/test_freebug.c:43` | `fb_buffer_free(&b);` |
| `fb_buffer_init` | function | `tests/test_freebug.c:24` | `fb_buffer_init(&b);` |
| `fb_buffer_push` | function | `tests/test_freebug.c:165` | `fb_buffer_push(&b, FB_LOG, "x", 1);` |
| `fb_buffer_reset` | function | `tests/test_freebug.c:149` | `fb_buffer_reset(&b);` |
| `free` | function | `tests/test_freebug.c:89` | `free(huge);` |
| `main` | function | `tests/test_freebug.c:227` | `int main(void)` |
| `memset` | function | `tests/test_freebug.c:82` | `memset(huge, 'A', big);` |
| `test_count_cap_fails_closed` | function | `tests/test_freebug.c:58` | `static void test_count_cap_fails_closed(void **state)` |
| `test_empty_and_null_text` | function | `tests/test_freebug.c:45` | `static void test_empty_and_null_text(void **state)` |
| `test_entry_truncated_not_dropped` | function | `tests/test_freebug.c:74` | `static void test_entry_truncated_not_dropped(void **state)` |
| `test_free_idempotent` | function | `tests/test_freebug.c:160` | `static void test_free_idempotent(void **state)` |
| `test_level_clamped` | function | `tests/test_freebug.c:117` | `static void test_level_clamped(void **state)` |
| `test_level_name` | function | `tests/test_freebug.c:128` | `static void test_level_name(void **state)` |
| `test_push_and_read` | function | `tests/test_freebug.c:20` | `static void test_push_and_read(void **state)` |
| `test_push_loc_file_truncated` | function | `tests/test_freebug.c:213` | `static void test_push_loc_file_truncated(void **state)` |
| `test_push_loc_null_file_and_negative_nums` | function | `tests/test_freebug.c:196` | `static void test_push_loc_null_file_and_negative_nums(void **state)` |
| `test_push_loc_records_location` | function | `tests/test_freebug.c:174` | `static void test_push_loc_records_location(void **state)` |
| `test_reset_reuses_and_no_leak` | function | `tests/test_freebug.c:139` | `static void test_reset_reuses_and_no_leak(void **state)` |
| `test_total_bytes_cap_fails_closed` | function | `tests/test_freebug.c:92` | `static void test_total_bytes_cap_fails_closed(void **state)` |
| `ERR_FILE` | macro | `tests/test_freedom.c:28` | `#define ERR_FILE` |
| `FREEDOM_BIN` | macro | `tests/test_freedom.c:25` | `#define FREEDOM_BIN` |
| `OUT_FILE` | macro | `tests/test_freedom.c:27` | `#define OUT_FILE` |
| `_POSIX_C_SOURCE` | macro | `tests/test_freedom.c:10` | `#define _POSIX_C_SOURCE` |
| `assert_int_equal` | function | `tests/test_freedom.c:111` | `assert_int_equal(run_freedom("--help", out, sizeof out, &rc), 0);` |
| `assert_non_null` | function | `tests/test_freedom.c:113` | `assert_non_null(strstr(out, "usage"));` |
| `assert_null` | function | `tests/test_freedom.c:178` | `assert_null(strstr(out, "HIDDENMARKER"));` |
| `assert_true` | function | `tests/test_freedom.c:149` | `assert_true((size_t)snprintf(arg, sizeof arg, "%s", path) < sizeof arg);` |
| `ballooned` | function | `tests/test_freedom.c:1428` | `* ballooned (body + wrapper re-opened per child) and the LAST wrapper piece
 * became the contain...` |
| `blend` | function | `tests/test_freedom.c:393` | `* not some other blend (double-composited or wrong alpha). */
static void test_download_png_group...` |
| `blend` | function | `tests/test_freedom.c:1087` | `* visibly different from either input color or an OVER blend (which would show
 * opaque blue). E...` |
| `bottom` | function | `tests/test_freedom.c:1536` | `* at the page bottom (the grey-stripe bug had npositioned pushing it away). */ assert_non_null(strstr(out, "nbox=1"));` |
| `cleanup_files` | function | `tests/test_freedom.c:83` | `static void cleanup_files(void)` |
| `fclose` | function | `tests/test_freedom.c:46` | `fclose(f);` |
| `free` | function | `tests/test_freedom.c:369` | `free(bytes);` |
| `img_pixels_free` | function | `tests/test_freedom.c:380` | `img_pixels_free(&px);` |
| `ink_width` | function | `tests/test_freedom.c:532` | `static double ink_width(const char *html)` |
| `is_pdf_file` | function | `tests/test_freedom.c:64` | `static int is_pdf_file(const char *path)` |
| `is_png_file` | function | `tests/test_freedom.c:74` | `static int is_png_file(const char *path)` |
| `main` | function | `tests/test_freedom.c:1948` | `int main(void)` |
| `markup` | function | `tests/test_freedom.c:1217` | `* against an unrotated control render of the identical markup (a 50-char-wide box
 * at x:[24,975...` |
| `markup` | function | `tests/test_freedom.c:1276` | `* unscaled control render of the identical markup (box y:[24,49] at x=500,
 * center y~36.5): y=2...` |
| `read_file_all` | function | `tests/test_freedom.c:90` | `static uint8_t *read_file_all(const char *path, size_t *out_len)` |
| `rows` | function | `tests/test_freedom.c:894` | `* rows (the bug) made it several times taller. */ assert_true(px.height < 60);` |
| `run_freedom` | function | `tests/test_freedom.c:29` | `static int run_freedom(const char *arg, char *out, size_t out_size, int *exit_status)` |
| `run_freedom_raw` | function | `tests/test_freedom.c:52` | `static int run_freedom_raw(const char *args, int *exit_status)` |
| `sample_png_pixel` | function | `tests/test_freedom.c:1832` | `sample_png_pixel(html, "--author-css", "gradrow", 900, 85, &r, &g, &b);` |
| `test_absolute_font_size_lands_exact` | function | `tests/test_freedom.c:579` | `static void test_absolute_font_size_lands_exact(void **state)` |
| `test_absolute_span_honours_right_bottom` | function | `tests/test_freedom.c:691` | `static void test_absolute_span_honours_right_bottom(void **state)` |
| `test_author_can_unbold_a_heading` | function | `tests/test_freedom.c:672` | `static void test_author_can_unbold_a_heading(void **state)` |
| `test_author_font_size_on_heading_replaces_ua_scale` | function | `tests/test_freedom.c:597` | `static void test_author_font_size_on_heading_replaces_ua_scale(void **state)` |
| `test_download_pdf_local` | function | `tests/test_freedom.c:193` | `static void test_download_pdf_local(void **state)` |
| `test_download_pdf_requires_path` | function | `tests/test_freedom.c:220` | `static void test_download_pdf_requires_path(void **state)` |
| `test_download_png_absolute_shrinks_and_anchors_right` | function | `tests/test_freedom.c:458` | `static void test_download_png_absolute_shrinks_and_anchors_right(void **state)` |
| `test_download_png_flex_container_paints_one_band` | function | `tests/test_freedom.c:1844` | `static void test_download_png_flex_container_paints_one_band(void **state)` |
| `test_download_png_gradient_box_text_keeps_gradient` | function | `tests/test_freedom.c:1819` | `static void test_download_png_gradient_box_text_keeps_gradient(void **state)` |
| `test_download_png_images_local` | function | `tests/test_freedom.c:261` | `static void test_download_png_images_local(void **state)` |
| `test_download_png_inline_block_flows_in_line` | function | `tests/test_freedom.c:840` | `static void test_download_png_inline_block_flows_in_line(void **state)` |
| `test_download_png_inline_block_shrinks_and_centers` | function | `tests/test_freedom.c:1864` | `static void test_download_png_inline_block_shrinks_and_centers(void **state)` |
| `test_download_png_inline_svg_path_and_drops_image` | function | `tests/test_freedom.c:1908` | `static void test_download_png_inline_svg_path_and_drops_image(void **state)` |
| `test_download_png_line_height_zero_does_not_shrink_line` | function | `tests/test_freedom.c:956` | `static void test_download_png_line_height_zero_does_not_shrink_line(void **state)` |
| `test_download_png_local` | function | `tests/test_freedom.c:228` | `static void test_download_png_local(void **state)` |
| `test_download_png_negative_zindex_paints_behind_inflow` | function | `tests/test_freedom.c:338` | `static void test_download_png_negative_zindex_paints_behind_inflow(void **state)` |
| `test_download_png_nested_flex_lays_out_on_one_row` | function | `tests/test_freedom.c:761` | `static void test_download_png_nested_flex_lays_out_on_one_row(void **state)` |
| `test_download_png_requires_path` | function | `tests/test_freedom.c:322` | `static void test_download_png_requires_path(void **state)` |
| `test_dump_console_shows_output_and_error` | function | `tests/test_freedom.c:1335` | `static void test_dump_console_shows_output_and_error(void **state)` |
| `test_dump_dom_prints_render_tree` | function | `tests/test_freedom.c:1395` | `static void test_dump_dom_prints_render_tree(void **state)` |
| `test_dump_layout_pulled_rail_single_margin` | function | `tests/test_freedom.c:1550` | `static void test_dump_layout_pulled_rail_single_margin(void **state)` |
| `test_dump_timings_prints_stages` | function | `tests/test_freedom.c:1924` | `static void test_dump_timings_prints_stages(void **state)` |
| `test_heading_colour_matches_body_text` | function | `tests/test_freedom.c:617` | `static void test_heading_colour_matches_body_text(void **state)` |
| `test_help` | function | `tests/test_freedom.c:106` | `static void test_help(void **state)` |
| `test_inline_run_boundary_collapses_runs_of_space` | function | `tests/test_freedom.c:934` | `static void test_inline_run_boundary_collapses_runs_of_space(void **state)` |
| `test_inline_run_boundary_does_not_invent_space` | function | `tests/test_freedom.c:913` | `static void test_inline_run_boundary_does_not_invent_space(void **state)` |
| `test_local_form_renders_inputs` | function | `tests/test_freedom.c:157` | `static void test_local_form_renders_inputs(void **state)` |
| `test_local_html` | function | `tests/test_freedom.c:134` | `static void test_local_html(void **state)` |
| `test_missing_file` | function | `tests/test_freedom.c:183` | `static void test_missing_file(void **state)` |
| `test_no_args` | function | `tests/test_freedom.c:124` | `static void test_no_args(void **state)` |
| `test_no_dump_console_without_flag` | function | `tests/test_freedom.c:1370` | `static void test_no_dump_console_without_flag(void **state)` |
| `test_rejects_http_url` | function | `tests/test_freedom.c:1660` | `static void test_rejects_http_url(void **state)` |
| `test_version` | function | `tests/test_freedom.c:115` | `static void test_version(void **state)` |
| `unlink` | function | `tests/test_freedom.c:154` | `unlink(path);` |
| `white` | function | `tests/test_freedom.c:1723` | `* and not white (the old behaviour where only text rows got background fills). */
static void tes...` |
| `assert_false` | function | `tests/test_hls.c:79` | `assert_false(pl->is_variant);` |
| `assert_float_equal` | function | `tests/test_hls.c:42` | `assert_float_equal(pl->segments[0].duration, 10.5, 0.01);` |
| `assert_int_equal` | function | `tests/test_hls.c:18` | `assert_int_equal(hls_parse("this is not a playlist", 22, &pl), HLS_ERR_PARSE);` |
| `assert_int_not_equal` | function | `tests/test_hls.c:186` | `assert_int_not_equal((int)n, 0);` |
| `assert_non_null` | function | `tests/test_hls.c:26` | `assert_non_null(pl);` |
| `assert_null` | function | `tests/test_hls.c:19` | `assert_null(pl);` |
| `assert_string_equal` | function | `tests/test_hls.c:41` | `assert_string_equal(pl->segments[0].url, "seg1.ts");` |
| `assert_true` | function | `tests/test_hls.c:92` | `assert_true(pl->is_variant);` |
| `cmocka_run_group_tests` | function | `tests/test_hls.c:237` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `hls_playlist_free` | function | `tests/test_hls.c:28` | `hls_playlist_free(pl);` |
| `main` | function | `tests/test_hls.c:218` | `int main(void)` |
| `test_empty_m3u8_is_ok` | function | `tests/test_hls.c:21` | `static void test_empty_m3u8_is_ok(void **state)` |
| `test_handles_windows_line_endings` | function | `tests/test_hls.c:208` | `static void test_handles_windows_line_endings(void **state)` |
| `test_multi_variant_collects_all` | function | `tests/test_hls.c:113` | `static void test_multi_variant_collects_all(void **state)` |
| `test_multiple_segments` | function | `tests/test_hls.c:45` | `static void test_multiple_segments(void **state)` |
| `test_not_m3u8_returns_parse_error` | function | `tests/test_hls.c:14` | `static void test_not_m3u8_returns_parse_error(void **state)` |
| `test_resolve_url_absolute_passthrough` | function | `tests/test_hls.c:179` | `static void test_resolve_url_absolute_passthrough(void **state)` |
| `test_resolve_url_deep_relative` | function | `tests/test_hls.c:199` | `static void test_resolve_url_deep_relative(void **state)` |
| `test_resolve_url_relative` | function | `tests/test_hls.c:189` | `static void test_resolve_url_relative(void **state)` |
| `test_select_variant_empty_returns_error` | function | `tests/test_hls.c:169` | `static void test_select_variant_empty_returns_error(void **state)` |
| `test_select_variant_highest_bandwidth_no_limit` | function | `tests/test_hls.c:134` | `static void test_select_variant_highest_bandwidth_no_limit(void **state)` |
| `test_select_variant_respects_max_dimensions` | function | `tests/test_hls.c:151` | `static void test_select_variant_respects_max_dimensions(void **state)` |
| `test_single_segment` | function | `tests/test_hls.c:30` | `static void test_single_segment(void **state)` |
| `test_target_duration_is_parsed` | function | `tests/test_hls.c:67` | `static void test_target_duration_is_parsed(void **state)` |
| `test_variant_playlist_collects_variants` | function | `tests/test_hls.c:96` | `static void test_variant_playlist_collects_variants(void **state)` |
| `test_variant_playlist_detected` | function | `tests/test_hls.c:82` | `static void test_variant_playlist_detected(void **state)` |
| `assert_int_equal` | function | `tests/test_hostblock.c:27` | `assert_int_equal(hb_count(s, HB_LIST_BLOCK), 0);` |
| `assert_non_null` | function | `tests/test_hostblock.c:26` | `assert_non_null(s);` |
| `cmocka_run_group_tests` | function | `tests/test_hostblock.c:291` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `hb_free` | function | `tests/test_hostblock.c:29` | `hb_free(s);` |
| `main` | function | `tests/test_hostblock.c:265` | `int main(void)` |
| `memset` | function | `tests/test_hostblock.c:159` | `memset(big, 'a', sizeof big);` |
| `test_allow_wins_and_covers_subdomains` | function | `tests/test_hostblock.c:209` | `static void test_allow_wins_and_covers_subdomains(void **state)` |
| `test_bare_domain_per_line` | function | `tests/test_hostblock.c:72` | `static void test_bare_domain_per_line(void **state)` |
| `test_block_covers_subdomains` | function | `tests/test_hostblock.c:196` | `static void test_block_covers_subdomains(void **state)` |
| `test_check_fail_open_edges` | function | `tests/test_hostblock.c:251` | `static void test_check_fail_open_edges(void **state)` |
| `test_comments_and_blanks` | function | `tests/test_hostblock.c:82` | `static void test_comments_and_blanks(void **state)` |
| `test_count_null_set` | function | `tests/test_hostblock.c:36` | `static void test_count_null_set(void **state)` |
| `test_dedup_and_accumulate` | function | `tests/test_hostblock.c:173` | `static void test_dedup_and_accumulate(void **state)` |
| `test_free_null_idempotent` | function | `tests/test_hostblock.c:31` | `static void test_free_null_idempotent(void **state)` |
| `test_hosts_line_drops_ip` | function | `tests/test_hostblock.c:54` | `static void test_hosts_line_drops_ip(void **state)` |
| `test_invalid_tokens_skipped` | function | `tests/test_hostblock.c:138` | `static void test_invalid_tokens_skipped(void **state)` |
| `test_is_allowlisted` | function | `tests/test_hostblock.c:230` | `static void test_is_allowlisted(void **state)` |
| `test_lists_independent` | function | `tests/test_hostblock.c:184` | `static void test_lists_independent(void **state)` |
| `test_load_null_args` | function | `tests/test_hostblock.c:44` | `static void test_load_null_args(void **state)` |
| `test_lowercased` | function | `tests/test_hostblock.c:117` | `static void test_lowercased(void **state)` |
| `test_multiple_tokens_per_line` | function | `tests/test_hostblock.c:98` | `static void test_multiple_tokens_per_line(void **state)` |
| `test_no_lists_allows` | function | `tests/test_hostblock.c:223` | `static void test_no_lists_allows(void **state)` |
| `test_no_trailing_newline` | function | `tests/test_hostblock.c:106` | `static void test_no_trailing_newline(void **state)` |
| `test_oversize_token_skipped` | function | `tests/test_hostblock.c:154` | `static void test_oversize_token_skipped(void **state)` |
| `test_trailing_dot_trimmed` | function | `tests/test_hostblock.c:127` | `static void test_trailing_dot_trimmed(void **state)` |
| `test_underscore_and_hyphen_valid` | function | `tests/test_hostblock.c:165` | `static void test_underscore_and_hyphen_valid(void **state)` |
| `test_various_ip_tokens_ignored` | function | `tests/test_hostblock.c:63` | `static void test_various_ip_tokens_ignored(void **state)` |
| `assert_int_equal` | function | `tests/test_hostedit.c:14` | `assert_int_equal(he_make_line("News.YCombinator.com", out, sizeof out), HE_OK);` |
| `assert_string_equal` | function | `tests/test_hostedit.c:15` | `assert_string_equal(out, "news.ycombinator.com\n");` |
| `cmocka_run_group_tests` | function | `tests/test_hostedit.c:127` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_hostedit.c:113` | `int main(void)` |
| `test_make_line_lowercases` | function | `tests/test_hostedit.c:10` | `static void test_make_line_lowercases(void **state)` |
| `test_make_line_null_and_range` | function | `tests/test_hostedit.c:46` | `static void test_make_line_null_and_range(void **state)` |
| `test_make_line_plain_host` | function | `tests/test_hostedit.c:17` | `static void test_make_line_plain_host(void **state)` |
| `test_make_line_rejects_bad_labels` | function | `tests/test_hostedit.c:35` | `static void test_make_line_rejects_bad_labels(void **state)` |
| `test_make_line_rejects_path_scheme_garbage` | function | `tests/test_hostedit.c:24` | `static void test_make_line_rejects_path_scheme_garbage(void **state)` |
| `test_make_line_single_label_ok` | function | `tests/test_hostedit.c:55` | `static void test_make_line_single_label_ok(void **state)` |
| `test_suggest_case_insensitive_and_dedup` | function | `tests/test_hostedit.c:91` | `static void test_suggest_case_insensitive_and_dedup(void **state)` |
| `test_suggest_empty_query_and_cap` | function | `tests/test_hostedit.c:100` | `static void test_suggest_empty_query_and_cap(void **state)` |
| `test_suggest_prefix_first` | function | `tests/test_hostedit.c:75` | `static void test_suggest_prefix_first(void **state)` |
| `test_text_has_host` | function | `tests/test_hostedit.c:62` | `static void test_text_has_host(void **state)` |
| `LIT` | macro | `tests/test_html_parse.c:20` | `#define LIT(s)` |
| `assert_int_equal` | function | `tests/test_html_parse.c:40` | `assert_int_equal((unsigned long)c.max_bytes, (unsigned long)HP_DEFAULT_MAX_BYTES);` |
| `assert_int_not_equal` | function | `tests/test_html_parse.c:41` | `assert_int_not_equal(c.strip_scripts, 0);` |
| `assert_non_null` | function | `tests/test_html_parse.c:96` | `assert_non_null(doc);` |
| `assert_null` | function | `tests/test_html_parse.c:86` | `assert_null(doc);` |
| `assert_string_equal` | function | `tests/test_html_parse.c:102` | `assert_string_equal(title, "Hello Title");` |
| `assert_true` | function | `tests/test_html_parse.c:97` | `assert_true(hp_element_count(doc) > 0);` |
| `cmocka_run_group_tests` | function | `tests/test_html_parse.c:473` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `free` | function | `tests/test_html_parse.c:296` | `free(html);` |
| `hp_document_free` | function | `tests/test_html_parse.c:110` | `hp_document_free(doc);` |
| `hp_free` | function | `tests/test_html_parse.c:103` | `hp_free(title);` |
| `hp_free_scripts` | function | `tests/test_html_parse.c:192` | `hp_free_scripts(s, n);` |
| `hp_free_stylesheet_hrefs` | function | `tests/test_html_parse.c:322` | `hp_free_stylesheet_hrefs(s, n);` |
| `main` | function | `tests/test_html_parse.c:445` | `int main(void)` |
| `src` | function | `tests/test_html_parse.c:197` | `* ONLY the src (browser rule: when src is present the content is ignored);` |
| `test_config_default_is_secure` | function | `tests/test_html_parse.c:36` | `static void test_config_default_is_secure(void **state)` |
| `test_event_handlers_kept_when_disabled` | function | `tests/test_html_parse.c:149` | `static void test_event_handlers_kept_when_disabled(void **state)` |
| `test_event_handlers_stripped_by_default` | function | `tests/test_html_parse.c:140` | `static void test_event_handlers_stripped_by_default(void **state)` |
| `test_extract_script_list_empty` | function | `tests/test_html_parse.c:256` | `static void test_extract_script_list_empty(void **state)` |
| `test_extract_script_list_skips_non_js_type` | function | `tests/test_html_parse.c:227` | `static void test_extract_script_list_skips_non_js_type(void **state)` |
| `test_extract_stylesheets_basic` | function | `tests/test_html_parse.c:303` | `static void test_extract_stylesheets_basic(void **state)` |
| `test_extract_stylesheets_caps` | function | `tests/test_html_parse.c:397` | `static void test_extract_stylesheets_caps(void **state)` |
| `test_extract_stylesheets_none_and_null` | function | `tests/test_html_parse.c:380` | `static void test_extract_stylesheets_none_and_null(void **state)` |
| `test_extract_stylesheets_rel_tokens` | function | `tests/test_html_parse.c:330` | `static void test_extract_stylesheets_rel_tokens(void **state)` |
| `test_free_null_and_double` | function | `tests/test_html_parse.c:435` | `static void test_free_null_and_double(void **state)` |
| `test_parse_malformed_does_not_crash` | function | `tests/test_html_parse.c:423` | `static void test_parse_malformed_does_not_crash(void **state)` |
| `test_parse_rejects_null_args` | function | `tests/test_html_parse.c:71` | `static void test_parse_rejects_null_args(void **state)` |
| `test_parse_rejects_oversize` | function | `tests/test_html_parse.c:79` | `static void test_parse_rejects_oversize(void **state)` |
| `test_parse_simple_document` | function | `tests/test_html_parse.c:90` | `static void test_parse_simple_document(void **state)` |
| `test_scripts_kept_when_disabled` | function | `tests/test_html_parse.c:130` | `static void test_scripts_kept_when_disabled(void **state)` |
| `test_scripts_stripped_by_default` | function | `tests/test_html_parse.c:115` | `static void test_scripts_stripped_by_default(void **state)` |
| `test_validate_accepts_within_cap` | function | `tests/test_html_parse.c:63` | `static void test_validate_accepts_within_cap(void **state)` |
| `test_validate_rejects_empty` | function | `tests/test_html_parse.c:50` | `static void test_validate_rejects_empty(void **state)` |
| `test_validate_rejects_null` | function | `tests/test_html_parse.c:44` | `static void test_validate_rejects_null(void **state)` |
| `test_validate_rejects_oversize` | function | `tests/test_html_parse.c:56` | `static void test_validate_rejects_oversize(void **state)` |
| `assert_int_equal` | function | `tests/test_image_decode.c:77` | `assert_int_equal(img_sniff(PNG_2x2, sizeof PNG_2x2), IMG_FMT_PNG);` |
| `assert_int_not_equal` | function | `tests/test_image_decode.c:291` | `assert_int_not_equal(img_decode_jpeg(JPEG_RED_4x4, 40u, &p), IMG_OK);` |
| `assert_non_null` | function | `tests/test_image_decode.c:174` | `assert_non_null(p.data);` |
| `assert_null` | function | `tests/test_image_decode.c:196` | `assert_null(p.data);` |
| `assert_string_equal` | function | `tests/test_image_decode.c:229` | `assert_string_equal(img_format_name(IMG_FMT_PNG), "png");` |
| `assert_true` | function | `tests/test_image_decode.c:141` | `assert_true(w > 99.9 && w < 100.1);` |
| `cmocka_run_group_tests` | function | `tests/test_image_decode.c:530` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `img_fit` | function | `tests/test_image_decode.c:140` | `img_fit(200, 100, 100.0, 100.0, &w, &h);` |
| `img_pixels_free` | function | `tests/test_image_decode.c:175` | `img_pixels_free(&p);` |
| `main` | function | `tests/test_image_decode.c:491` | `int main(void)` |
| `memset` | function | `tests/test_image_decode.c:169` | `memset(&p, 0, sizeof p);` |
| `px` | function | `tests/test_image_decode.c:64` | `static uint32_t px(const img_pixels *p, uint32_t x, uint32_t y)` |
| `test_decode_dimensions_and_stride` | function | `tests/test_image_decode.c:165` | `static void test_decode_dimensions_and_stride(void **state)` |
| `test_decode_dispatch_rejects_unknown` | function | `tests/test_image_decode.c:278` | `static void test_decode_dispatch_rejects_unknown(void **state)` |
| `test_decode_dispatch_routes_gif` | function | `tests/test_image_decode.c:429` | `static void test_decode_dispatch_routes_gif(void **state)` |
| `test_decode_dispatch_routes_jpeg_and_png` | function | `tests/test_image_decode.c:266` | `static void test_decode_dispatch_routes_jpeg_and_png(void **state)` |
| `test_decode_dispatch_routes_webp` | function | `tests/test_image_decode.c:482` | `static void test_decode_dispatch_routes_webp(void **state)` |
| `test_decode_gif_animated_first_frame` | function | `tests/test_image_decode.c:404` | `static void test_decode_gif_animated_first_frame(void **state)` |
| `test_decode_gif_fail_closed` | function | `tests/test_image_decode.c:413` | `static void test_decode_gif_fail_closed(void **state)` |
| `test_decode_gif_interlaced` | function | `tests/test_image_decode.c:389` | `static void test_decode_gif_interlaced(void **state)` |
| `test_decode_gif_pixels` | function | `tests/test_image_decode.c:362` | `static void test_decode_gif_pixels(void **state)` |
| `test_decode_gif_transparency` | function | `tests/test_image_decode.c:377` | `static void test_decode_gif_transparency(void **state)` |
| `test_decode_jpeg_dimensions_and_alpha` | function | `tests/test_image_decode.c:243` | `static void test_decode_jpeg_dimensions_and_alpha(void **state)` |
| `test_decode_jpeg_null_args` | function | `tests/test_image_decode.c:301` | `static void test_decode_jpeg_null_args(void **state)` |
| `test_decode_jpeg_rejects_non_jpeg` | function | `tests/test_image_decode.c:294` | `static void test_decode_jpeg_rejects_non_jpeg(void **state)` |
| `test_decode_jpeg_rejects_truncated` | function | `tests/test_image_decode.c:286` | `static void test_decode_jpeg_rejects_truncated(void **state)` |
| `test_decode_null_args` | function | `tests/test_image_decode.c:209` | `static void test_decode_null_args(void **state)` |
| `test_decode_pixels_premultiplied` | function | `tests/test_image_decode.c:177` | `static void test_decode_pixels_premultiplied(void **state)` |
| `test_decode_rejects_non_png` | function | `tests/test_image_decode.c:189` | `static void test_decode_rejects_non_png(void **state)` |
| `test_decode_rejects_truncated` | function | `tests/test_image_decode.c:199` | `static void test_decode_rejects_truncated(void **state)` |
| `test_decode_webp_dimensions_and_pixels` | function | `tests/test_image_decode.c:453` | `static void test_decode_webp_dimensions_and_pixels(void **state)` |
| `test_decode_webp_fail_closed` | function | `tests/test_image_decode.c:470` | `static void test_decode_webp_fail_closed(void **state)` |
| `test_dimensions_from_ihdr` | function | `tests/test_image_decode.c:88` | `static void test_dimensions_from_ihdr(void **state)` |
| `test_dimensions_non_png` | function | `tests/test_image_decode.c:103` | `static void test_dimensions_non_png(void **state)` |
| `test_dimensions_null` | function | `tests/test_image_decode.c:110` | `static void test_dimensions_null(void **state)` |
| `test_dimensions_ok_bounds` | function | `tests/test_image_decode.c:119` | `static void test_dimensions_ok_bounds(void **state)` |
| `test_dimensions_truncated` | function | `tests/test_image_decode.c:96` | `static void test_dimensions_truncated(void **state)` |
| `test_fit_degenerate` | function | `tests/test_image_decode.c:153` | `static void test_fit_degenerate(void **state)` |
| `test_fit_landscape_into_square` | function | `tests/test_image_decode.c:135` | `static void test_fit_landscape_into_square(void **state)` |
| `test_fit_portrait_into_box` | function | `tests/test_image_decode.c:144` | `static void test_fit_portrait_into_box(void **state)` |
| `test_format_name` | function | `tests/test_image_decode.c:226` | `static void test_format_name(void **state)` |
| `test_pixels_free_idempotent` | function | `tests/test_image_decode.c:217` | `static void test_pixels_free_idempotent(void **state)` |
| `test_sniff_gif` | function | `tests/test_image_decode.c:355` | `static void test_sniff_gif(void **state)` |
| `test_sniff_jpeg` | function | `tests/test_image_decode.c:235` | `static void test_sniff_jpeg(void **state)` |
| `test_sniff_png` | function | `tests/test_image_decode.c:74` | `static void test_sniff_png(void **state)` |
| `test_sniff_unsupported` | function | `tests/test_image_decode.c:79` | `static void test_sniff_unsupported(void **state)` |
| `test_sniff_webp` | function | `tests/test_image_decode.c:447` | `static void test_sniff_webp(void **state)` |
| `assert_float_equal` | function | `tests/test_interp.c:64` | `assert_float_equal(ip_ease(0.0, &(ip_ease_fn)` |
| `assert_float_equal` | function | `tests/test_interp.c:66` | `assert_float_equal(ip_ease(0.0, &(ip_ease_fn)` |
| `assert_int_equal` | function | `tests/test_interp.c:175` | `assert_int_equal(got, 0x800080);` |
| `assert_true` | function | `tests/test_interp.c:96` | `assert_true(v > 0.0 && v < 0.5);` |
| `cmocka_run_group_tests_name` | function | `tests/test_interp.c:511` | `return cmocka_run_group_tests_name("interp", tests, NULL, NULL);` |
| `ip_anim_init` | function | `tests/test_interp.c:268` | `ip_anim_init(&a, IP_VAL_SCALAR, &e, kf, 2, 1000.0, 500.0, 1, IP_DIR_NORMAL, IP_FILL_NONE);` |
| `ip_anim_tick` | function | `tests/test_interp.c:306` | `ip_anim_tick(&a, 750.0);` |
| `linear_ease` | function | `tests/test_interp.c:257` | `static ip_ease_fn linear_ease(void)` |
| `main` | function | `tests/test_interp.c:473` | `int main(void)` |
| `test_anim_active_linear` | function | `tests/test_interp.c:291` | `static void test_anim_active_linear(void **state)` |
| `test_anim_alternate` | function | `tests/test_interp.c:392` | `static void test_anim_alternate(void **state)` |
| `test_anim_alternate_reverse` | function | `tests/test_interp.c:409` | `static void test_anim_alternate_reverse(void **state)` |
| `test_anim_delay_backwards_fill` | function | `tests/test_interp.c:277` | `static void test_anim_delay_backwards_fill(void **state)` |
| `test_anim_delay_no_fill` | function | `tests/test_interp.c:262` | `static void test_anim_delay_no_fill(void **state)` |
| `test_anim_forwards_fill` | function | `tests/test_interp.c:324` | `static void test_anim_forwards_fill(void **state)` |
| `test_anim_infinite` | function | `tests/test_interp.c:366` | `static void test_anim_infinite(void **state)` |
| `test_anim_negative_dt` | function | `tests/test_interp.c:447` | `static void test_anim_negative_dt(void **state)` |
| `test_anim_no_keyframes` | function | `tests/test_interp.c:435` | `static void test_anim_no_keyframes(void **state)` |
| `test_anim_null_init` | function | `tests/test_interp.c:462` | `static void test_anim_null_init(void **state)` |
| `test_anim_reverse_direction` | function | `tests/test_interp.c:379` | `static void test_anim_reverse_direction(void **state)` |
| `test_anim_single_iteration_done` | function | `tests/test_interp.c:309` | `static void test_anim_single_iteration_done(void **state)` |
| `test_anim_two_iterations` | function | `tests/test_interp.c:337` | `static void test_anim_two_iterations(void **state)` |
| `test_anim_zero_duration` | function | `tests/test_interp.c:422` | `static void test_anim_zero_duration(void **state)` |
| `test_ease_clamp` | function | `tests/test_interp.c:77` | `static void test_ease_clamp(void **state)` |
| `test_ease_ease_in_concave` | function | `tests/test_interp.c:91` | `static void test_ease_ease_in_concave(void **state)` |
| `test_ease_ease_out_convex` | function | `tests/test_interp.c:98` | `static void test_ease_ease_out_convex(void **state)` |
| `test_ease_endpoints` | function | `tests/test_interp.c:30` | `static void test_ease_endpoints(void **state)` |
| `test_ease_monotonic` | function | `tests/test_interp.c:105` | `static void test_ease_monotonic(void **state)` |
| `test_ease_null_fn` | function | `tests/test_interp.c:84` | `static void test_ease_null_fn(void **state)` |
| `test_ease_step_start_end_aliases` | function | `tests/test_interp.c:146` | `static void test_ease_step_start_end_aliases(void **state)` |
| `test_ease_steps_end` | function | `tests/test_interp.c:126` | `static void test_ease_steps_end(void **state)` |
| `test_ease_steps_start` | function | `tests/test_interp.c:137` | `static void test_ease_steps_start(void **state)` |
| `test_interp_dispatches` | function | `tests/test_interp.c:191` | `static void test_interp_dispatches(void **state)` |
| `test_kf_after_last` | function | `tests/test_interp.c:230` | `static void test_kf_after_last(void **state)` |
| `test_kf_before_first` | function | `tests/test_interp.c:224` | `static void test_kf_before_first(void **state)` |
| `test_kf_color_interp` | function | `tests/test_interp.c:246` | `static void test_kf_color_interp(void **state)` |
| `test_kf_exact_match` | function | `tests/test_interp.c:218` | `static void test_kf_exact_match(void **state)` |
| `test_kf_null_or_empty` | function | `tests/test_interp.c:236` | `static void test_kf_null_or_empty(void **state)` |
| `test_kf_three_keyframes` | function | `tests/test_interp.c:211` | `static void test_kf_three_keyframes(void **state)` |
| `test_kf_two_keyframes` | function | `tests/test_interp.c:204` | `static void test_kf_two_keyframes(void **state)` |
| `test_lerp_color_rgb` | function | `tests/test_interp.c:170` | `static void test_lerp_color_rgb(void **state)` |
| `test_lerp_scalar` | function | `tests/test_interp.c:162` | `static void test_lerp_scalar(void **state)` |
| `EXPECT` | macro | `tests/test_js_dom.c:72` | `#define EXPECT(f, src, expected)` |
| `EXPECT` | function | `tests/test_js_dom.c:266` | `EXPECT(f, "typeof (new MutationObserver(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:572` | `EXPECT(f,
        "setTimeout(function()` |
| `assert_int_equal` | function | `tests/test_js_dom.c:561` | `assert_int_equal(run(f,
        "window.onload=function()` |
| `assert_int_not_equal` | function | `tests/test_js_dom.c:505` | `assert_int_not_equal(dom_get_element_by_id(f->idx, "made"), DOM_NODE_NONE);` |
| `assert_non_null` | function | `tests/test_js_dom.c:77` | `assert_non_null(_r.value);` |
| `assert_null` | function | `tests/test_js_dom.c:641` | `assert_null(strstr(buf, "theme="));` |
| `assert_string_equal` | function | `tests/test_js_dom.c:78` | `assert_string_equal(_r.value, (expected));` |
| `assert_true` | function | `tests/test_js_dom.c:496` | `assert_true(dom_get_by_tag(f->idx, "span", span, 4) >= 1);` |
| `bundle` | function | `tests/test_js_dom.c:331` | `* library bundle (DuckDuckGo's l.js "cannot read property createElement of
 * undefined"). This l...` |
| `cmocka_run_group_tests` | function | `tests/test_js_dom.c:1621` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `console_fixture` | function | `tests/test_js_dom.c:755` | `static void console_fixture(hp_document **doc, dom_index **idx, js_context **ctx,
               ...` |
| `console_teardown` | function | `tests/test_js_dom.c:765` | `static void console_teardown(hp_document *doc, dom_index *idx, js_context *ctx,
                 ...` |
| `dom_free` | function | `tests/test_js_dom.c:60` | `dom_free(f->idx);` |
| `fb_buffer_free` | function | `tests/test_js_dom.c:768` | `fb_buffer_free(log);` |
| `fb_buffer_init` | function | `tests/test_js_dom.c:762` | `fb_buffer_init(log);` |
| `fixture` | struct | `tests/test_js_dom.c:38` | `` |
| `free` | function | `tests/test_js_dom.c:62` | `free(f);` |
| `hp_document_free` | function | `tests/test_js_dom.c:61` | `hp_document_free(f->doc);` |
| `identity` | function | `tests/test_js_dom.c:298` | `* identity (the same one innerWidth and the CSS viewport units use);` |
| `jQuery` | function | `tests/test_js_dom.c:242` | `* page that ships jQuery (Slashdot). The fragment must be complete enough that the
 * detection c...` |
| `jd_click_state_free` | function | `tests/test_js_dom.c:1196` | `jd_click_state_free(cs);` |
| `js_context_free` | function | `tests/test_js_dom.c:59` | `js_context_free(f->ctx);` |
| `js_eval` | function | `tests/test_js_dom.c:70` | `return js_eval(f->ctx, src, strlen(src), r);` |
| `js_result_free` | function | `tests/test_js_dom.c:79` | `js_result_free(&_r);` |
| `main` | function | `tests/test_js_dom.c:1518` | `int main(void)` |
| `methods` | function | `tests/test_js_dom.c:347` | `* backed by the sealed dom methods (this element's own attributes only). */
static void test_elem...` |
| `persisted` | function | `tests/test_js_dom.c:619` | `* never persisted (process-lifetime only). */
static void test_cookie_jar_enabled_for_trusted_hos...` |
| `run` | function | `tests/test_js_dom.c:69` | `static js_status run(fixture *f, const char *src, js_result *r)` |
| `set_https_location` | function | `tests/test_js_dom.c:655` | `static void set_https_location(fixture *f, const char *url)` |
| `setup` | function | `tests/test_js_dom.c:44` | `static int setup(void **state)` |
| `teardown` | function | `tests/test_js_dom.c:55` | `static int teardown(void **state)` |
| `test_ambient_apis_do_not_throw` | function | `tests/test_js_dom.c:643` | `static void test_ambient_apis_do_not_throw(void **state)` |
| `test_append_cycle_is_rejected` | function | `tests/test_js_dom.c:548` | `static void test_append_cycle_is_rejected(void **state)` |
| `test_attributes` | function | `tests/test_js_dom.c:125` | `static void test_attributes(void **state)` |
| `test_blur_onblur_fires` | function | `tests/test_js_dom.c:960` | `static void test_blur_onblur_fires(void **state)` |
| `test_by_class_and_tag` | function | `tests/test_js_dom.c:107` | `static void test_by_class_and_tag(void **state)` |
| `test_classlist_backs_class_attr` | function | `tests/test_js_dom.c:217` | `static void test_classlist_backs_class_attr(void **state)` |
| `test_click_add_event_listener_fires` | function | `tests/test_js_dom.c:1177` | `static void test_click_add_event_listener_fires(void **state)` |
| `test_click_install_null_args` | function | `tests/test_js_dom.c:1170` | `static void test_click_install_null_args(void **state)` |
| `test_click_no_handler_allows_default` | function | `tests/test_js_dom.c:1248` | `static void test_click_no_handler_allows_default(void **state)` |
| `test_click_onclick_fires` | function | `tests/test_js_dom.c:1201` | `static void test_click_onclick_fires(void **state)` |
| `test_click_prevent_default` | function | `tests/test_js_dom.c:1225` | `static void test_click_prevent_default(void **state)` |
| `test_console_captures_levels` | function | `tests/test_js_dom.c:773` | `static void test_console_captures_levels(void **state)` |
| `test_console_null_buffer_is_noop` | function | `tests/test_js_dom.c:822` | `static void test_console_null_buffer_is_noop(void **state)` |
| `test_console_null_ctx` | function | `tests/test_js_dom.c:843` | `static void test_console_null_ctx(void **state)` |
| `test_console_object_and_throwing_tostring` | function | `tests/test_js_dom.c:800` | `static void test_console_object_and_throwing_tostring(void **state)` |
| `test_cookie_and_referrer_leak_nothing` | function | `tests/test_js_dom.c:604` | `static void test_cookie_and_referrer_leak_nothing(void **state)` |
| `test_create_append_renders_in_tree` | function | `tests/test_js_dom.c:482` | `static void test_create_append_renders_in_tree(void **state)` |
| `test_document_fragment_reparents` | function | `tests/test_js_dom.c:227` | `static void test_document_fragment_reparents(void **state)` |
| `test_document_is_not_io` | function | `tests/test_js_dom.c:473` | `static void test_document_is_not_io(void **state)` |
| `test_document_order` | function | `tests/test_js_dom.c:132` | `static void test_document_order(void **state)` |
| `test_document_shim_present` | function | `tests/test_js_dom.c:170` | `static void test_document_shim_present(void **state)` |
| `test_document_title_set_reflects_in_tree` | function | `tests/test_js_dom.c:433` | `static void test_document_title_set_reflects_in_tree(void **state)` |
| `test_element_has_attribute` | function | `tests/test_js_dom.c:524` | `static void test_element_has_attribute(void **state)` |
| `test_element_matches_closest_query_from_js` | function | `tests/test_js_dom.c:191` | `static void test_element_matches_closest_query_from_js(void **state)` |
| `test_element_remove_attribute` | function | `tests/test_js_dom.c:530` | `static void test_element_remove_attribute(void **state)` |
| `test_element_src_href_are_strings` | function | `tests/test_js_dom.c:540` | `static void test_element_src_href_are_strings(void **state)` |
| `test_element_traversal` | function | `tests/test_js_dom.c:208` | `static void test_element_traversal(void **state)` |
| `test_event_add_event_listener_fires` | function | `tests/test_js_dom.c:852` | `static void test_event_add_event_listener_fires(void **state)` |
| `test_event_input_handler_fires_with_value` | function | `tests/test_js_dom.c:888` | `static void test_event_input_handler_fires_with_value(void **state)` |
| `test_event_no_handler_allows_default` | function | `tests/test_js_dom.c:923` | `static void test_event_no_handler_allows_default(void **state)` |
| `test_event_null_args` | function | `tests/test_js_dom.c:930` | `static void test_event_null_args(void **state)` |
| `test_event_onkeydown_fires` | function | `tests/test_js_dom.c:870` | `static void test_event_onkeydown_fires(void **state)` |
| `test_event_prevent_default_suppresses` | function | `tests/test_js_dom.c:906` | `static void test_event_prevent_default_suppresses(void **state)` |
| `test_focus_add_event_listener_fires` | function | `tests/test_js_dom.c:943` | `static void test_focus_add_event_listener_fires(void **state)` |
| `test_focus_blur_scroll_no_handler_allows_default` | function | `tests/test_js_dom.c:1037` | `static void test_focus_blur_scroll_no_handler_allows_default(void **state)` |
| `test_focus_blur_scroll_null_args` | function | `tests/test_js_dom.c:1045` | `static void test_focus_blur_scroll_null_args(void **state)` |
| `test_focus_blur_scroll_prevent_default` | function | `tests/test_js_dom.c:1009` | `static void test_focus_blur_scroll_prevent_default(void **state)` |
| `test_get_element_by_id` | function | `tests/test_js_dom.c:94` | `static void test_get_element_by_id(void **state)` |
| `test_inner_html_builds_and_queryable` | function | `tests/test_js_dom.c:577` | `static void test_inner_html_builds_and_queryable(void **state)` |
| `test_inner_html_getter_serializes` | function | `tests/test_js_dom.c:588` | `static void test_inner_html_getter_serializes(void **state)` |
| `test_install_null_args` | function | `tests/test_js_dom.c:83` | `static void test_install_null_args(void **state)` |
| `test_intersection_observer_fires_synthetically` | function | `tests/test_js_dom.c:284` | `static void test_intersection_observer_fires_synthetically(void **state)` |
| `test_intl_stub_does_not_throw` | function | `tests/test_js_dom.c:366` | `static void test_intl_stub_does_not_throw(void **state)` |
| `test_invalid_handles` | function | `tests/test_js_dom.c:141` | `static void test_invalid_handles(void **state)` |
| `test_local_page_captures_nav` | function | `tests/test_js_dom.c:733` | `static void test_local_page_captures_nav(void **state)` |
| `test_location_assign_and_window_last_wins` | function | `tests/test_js_dom.c:711` | `static void test_location_assign_and_window_last_wins(void **state)` |
| `test_location_href_set_captures_raw` | function | `tests/test_js_dom.c:685` | `static void test_location_href_set_captures_raw(void **state)` |
| `test_location_pathname_defaults_slash` | function | `tests/test_js_dom.c:677` | `static void test_location_pathname_defaults_slash(void **state)` |
| `test_location_reads_real_components` | function | `tests/test_js_dom.c:660` | `static void test_location_reads_real_components(void **state)` |
| `test_location_replace_sets_replace_flag` | function | `tests/test_js_dom.c:699` | `static void test_location_replace_sets_replace_flag(void **state)` |
| `test_methods_are_frozen` | function | `tests/test_js_dom.c:151` | `static void test_methods_are_frozen(void **state)` |
| `test_modern_globals_do_not_throw` | function | `tests/test_js_dom.c:260` | `static void test_modern_globals_do_not_throw(void **state)` |
| `test_mouse_add_event_listener_fires` | function | `tests/test_js_dom.c:1055` | `static void test_mouse_add_event_listener_fires(void **state)` |
| `test_mouse_mousemove_sees_coords` | function | `tests/test_js_dom.c:1088` | `static void test_mouse_mousemove_sees_coords(void **state)` |
| `test_mouse_multi_event_fires` | function | `tests/test_js_dom.c:1105` | `static void test_mouse_multi_event_fires(void **state)` |
| `test_mouse_no_handler_allows_default` | function | `tests/test_js_dom.c:1155` | `static void test_mouse_no_handler_allows_default(void **state)` |
| `test_mouse_null_args` | function | `tests/test_js_dom.c:1162` | `static void test_mouse_null_args(void **state)` |
| `test_mouse_onmouseout_fires` | function | `tests/test_js_dom.c:1072` | `static void test_mouse_onmouseout_fires(void **state)` |
| `test_mouse_prevent_default_suppresses` | function | `tests/test_js_dom.c:1139` | `static void test_mouse_prevent_default_suppresses(void **state)` |
| `test_navigation` | function | `tests/test_js_dom.c:115` | `static void test_navigation(void **state)` |
| `test_no_io_with_dom` | function | `tests/test_js_dom.c:162` | `static void test_no_io_with_dom(void **state)` |
| `test_no_nav_request_when_idle` | function | `tests/test_js_dom.c:723` | `static void test_no_nav_request_when_idle(void **state)` |
| `test_node_count` | function | `tests/test_js_dom.c:102` | `static void test_node_count(void **state)` |
| `test_node_identity_is_cached` | function | `tests/test_js_dom.c:201` | `static void test_node_identity_is_cached(void **state)` |
| `test_onload_runs_and_mutates` | function | `tests/test_js_dom.c:556` | `static void test_onload_runs_and_mutates(void **state)` |
| `test_query_selector_from_js` | function | `tests/test_js_dom.c:177` | `static void test_query_selector_from_js(void **state)` |
| `test_scroll_add_event_listener_fires` | function | `tests/test_js_dom.c:976` | `static void test_scroll_add_event_listener_fires(void **state)` |
| `test_scroll_onscroll_fires` | function | `tests/test_js_dom.c:993` | `static void test_scroll_onscroll_fires(void **state)` |
| `test_set_attribute_makes_queryable` | function | `tests/test_js_dom.c:498` | `static void test_set_attribute_makes_queryable(void **state)` |
| `test_set_location_null_ctx` | function | `tests/test_js_dom.c:744` | `static void test_set_location_null_ctx(void **state)` |
| `test_set_text_content_detach_is_memory_safe` | function | `tests/test_js_dom.c:458` | `static void test_set_text_content_detach_is_memory_safe(void **state)` |
| `test_set_text_content_reflects_in_tree` | function | `tests/test_js_dom.c:447` | `static void test_set_text_content_reflects_in_tree(void **state)` |
| `test_settimeout_chains_across_rounds` | function | `tests/test_js_dom.c:426` | `static void test_settimeout_chains_across_rounds(void **state)` |
| `test_settimeout_flushed_by_pump` | function | `tests/test_js_dom.c:569` | `static void test_settimeout_flushed_by_pump(void **state)` |
| `test_storage_is_ephemeral` | function | `tests/test_js_dom.c:598` | `static void test_storage_is_ephemeral(void **state)` |
| `test_submit_add_event_listener_fires` | function | `tests/test_js_dom.c:1262` | `static void test_submit_add_event_listener_fires(void **state)` |
| `test_submit_no_handler_allows_default` | function | `tests/test_js_dom.c:1319` | `static void test_submit_no_handler_allows_default(void **state)` |
| `test_submit_onsubmit_fires` | function | `tests/test_js_dom.c:1281` | `static void test_submit_onsubmit_fires(void **state)` |
| `test_submit_prevent_default` | function | `tests/test_js_dom.c:1300` | `static void test_submit_prevent_default(void **state)` |
| `test_url_constructor_parses_components` | function | `tests/test_js_dom.c:379` | `static void test_url_constructor_parses_components(void **state)` |
| `test_url_search_params` | function | `tests/test_js_dom.c:402` | `static void test_url_search_params(void **state)` |
| `test_video_from_scripts_no_video` | function | `tests/test_js_dom.c:1497` | `static void test_video_from_scripts_no_video(void **state)` |
| `test_video_from_scripts_null_args` | function | `tests/test_js_dom.c:1508` | `static void test_video_from_scripts_null_args(void **state)` |
| `test_video_from_scripts_relative_resolved` | function | `tests/test_js_dom.c:1462` | `static void test_video_from_scripts_relative_resolved(void **state)` |
| `test_video_from_scripts_video_data_is_variable` | function | `tests/test_js_dom.c:1447` | `static void test_video_from_scripts_video_data_is_variable(void **state)` |
| `test_video_from_scripts_video_data_string` | function | `tests/test_js_dom.c:1480` | `static void test_video_from_scripts_video_data_string(void **state)` |
| `test_video_shim_empty_html` | function | `tests/test_js_dom.c:1403` | `static void test_video_shim_empty_html(void **state)` |
| `test_video_shim_no_video` | function | `tests/test_js_dom.c:1329` | `static void test_video_shim_no_video(void **state)` |
| `test_video_shim_null_ctx` | function | `tests/test_js_dom.c:1415` | `static void test_video_shim_null_ctx(void **state)` |
| `test_video_shim_relative_url_resolved` | function | `tests/test_js_dom.c:1385` | `static void test_video_shim_relative_url_resolved(void **state)` |
| `test_video_shim_uses_index_1` | function | `tests/test_js_dom.c:1337` | `static void test_video_shim_uses_index_1(void **state)` |
| `test_video_shim_video_data_wins` | function | `tests/test_js_dom.c:1361` | `static void test_video_shim_video_data_wins(void **state)` |
| `EXPECT` | macro | `tests/test_js_env.c:50` | `#define EXPECT(f, src, expected)` |
| `EXPECT` | function | `tests/test_js_env.c:76` | `EXPECT(f, "navigator.userAgent.indexOf('Firefox') >= 0", "true");` |
| `assert_int_equal` | function | `tests/test_js_env.c:54` | `assert_int_equal(run((f), (src), &_r), JS_OK);` |
| `assert_non_null` | function | `tests/test_js_env.c:55` | `assert_non_null(_r.value);` |
| `assert_string_equal` | function | `tests/test_js_env.c:56` | `assert_string_equal(_r.value, (expected));` |
| `assert_string_not_equal` | function | `tests/test_js_env.c:300` | `assert_string_not_equal(a, b);` |
| `cmocka_run_group_tests` | function | `tests/test_js_env.c:377` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `dom_free` | function | `tests/test_js_env.c:351` | `dom_free(idx);` |
| `fixture` | struct | `tests/test_js_env.c:25` | `` |
| `free` | function | `tests/test_js_env.c:42` | `free(f);` |
| `hp_document_free` | function | `tests/test_js_env.c:352` | `hp_document_free(doc);` |
| `js_context_free` | function | `tests/test_js_env.c:41` | `js_context_free(f->ctx);` |
| `js_eval` | function | `tests/test_js_env.c:48` | `return js_eval(f->ctx, src, strlen(src), r);` |
| `js_result_free` | function | `tests/test_js_env.c:57` | `js_result_free(&_r);` |
| `main` | function | `tests/test_js_env.c:354` | `int main(void)` |
| `readback_checksum` | function | `tests/test_js_env.c:279` | `static void readback_checksum(uint64_t key, char *out, size_t out_size)` |
| `run` | function | `tests/test_js_env.c:46` | `static js_status run(fixture *f, const char *src, js_result *r)` |
| `setup` | function | `tests/test_js_env.c:28` | `static int setup(void **state)` |
| `snprintf` | function | `tests/test_js_env.c:290` | `snprintf(out, out_size, "%s", r.value);` |
| `teardown` | function | `tests/test_js_env.c:37` | `static int teardown(void **state)` |
| `test_bool_nav_props` | function | `tests/test_js_env.c:102` | `static void test_bool_nav_props(void **state)` |
| `test_canvas_readback` | function | `tests/test_js_env.c:238` | `static void test_canvas_readback(void **state)` |
| `test_canvas_unforgeable` | function | `tests/test_js_env.c:302` | `static void test_canvas_unforgeable(void **state)` |
| `test_canvas_unlinkable` | function | `tests/test_js_env.c:294` | `static void test_canvas_unlinkable(void **state)` |
| `test_clocks_coarse` | function | `tests/test_js_env.c:177` | `static void test_clocks_coarse(void **state)` |
| `test_coexists_with_dom` | function | `tests/test_js_env.c:325` | `static void test_coexists_with_dom(void **state)` |
| `test_crypto_present` | function | `tests/test_js_env.c:128` | `static void test_crypto_present(void **state)` |
| `test_crypto_random_uuid` | function | `tests/test_js_env.c:136` | `static void test_crypto_random_uuid(void **state)` |
| `test_crypto_random_values` | function | `tests/test_js_env.c:145` | `static void test_crypto_random_values(void **state)` |
| `test_install_null_args` | function | `tests/test_js_env.c:61` | `static void test_install_null_args(void **state)` |
| `test_legacy_nav_props` | function | `tests/test_js_env.c:91` | `static void test_legacy_nav_props(void **state)` |
| `test_navigator_identity` | function | `tests/test_js_env.c:73` | `static void test_navigator_identity(void **state)` |
| `test_navigator_mime_types` | function | `tests/test_js_env.c:119` | `static void test_navigator_mime_types(void **state)` |
| `test_navigator_plugins` | function | `tests/test_js_env.c:111` | `static void test_navigator_plugins(void **state)` |
| `test_performance_timing_identity_safe` | function | `tests/test_js_env.c:190` | `static void test_performance_timing_identity_safe(void **state)` |
| `test_screen_bucketed` | function | `tests/test_js_env.c:165` | `static void test_screen_bucketed(void **state)` |
| `test_screen_edges` | function | `tests/test_js_env.c:219` | `static void test_screen_edges(void **state)` |
| `test_screen_orientation` | function | `tests/test_js_env.c:155` | `static void test_screen_orientation(void **state)` |
| `test_unforgeable` | function | `tests/test_js_env.c:205` | `static void test_unforgeable(void **state)` |
| `assert_false` | function | `tests/test_js_policy.c:21` | `assert_false(jsp_enabled(JSP_OFF, 0));` |
| `assert_int_equal` | function | `tests/test_js_policy.c:38` | `assert_int_equal(jsp_mode_from_str("off"), JSP_OFF);` |
| `assert_string_equal` | function | `tests/test_js_policy.c:55` | `assert_string_equal(jsp_mode_str(JSP_OFF), "off");` |
| `assert_true` | function | `tests/test_js_policy.c:25` | `assert_true(jsp_enabled(JSP_ALLOWLIST, 1));` |
| `cmocka_run_group_tests` | function | `tests/test_js_policy.c:98` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_js_policy.c:88` | `int main(void)` |
| `test_enabled_fail_closed_on_bad_mode` | function | `tests/test_js_policy.c:30` | `static void test_enabled_fail_closed_on_bad_mode(void **state)` |
| `test_mode_from_str` | function | `tests/test_js_policy.c:35` | `static void test_mode_from_str(void **state)` |
| `test_mode_str_roundtrip` | function | `tests/test_js_policy.c:52` | `static void test_mode_str_roundtrip(void **state)` |
| `test_trusted_requires_both_signals` | function | `tests/test_js_policy.c:68` | `static void test_trusted_requires_both_signals(void **state)` |
| `assert_int_equal` | function | `tests/test_js_sandbox.c:154` | `assert_int_equal(js_eval_once("while(true)` |
| `assert_int_equal` | function | `tests/test_js_sandbox.c:169` | `assert_int_equal(js_eval(ctx, "while(true)` |
| `assert_non_null` | function | `tests/test_js_sandbox.c:62` | `assert_non_null(ctx);` |
| `assert_null` | function | `tests/test_js_sandbox.c:304` | `assert_null(r.file);` |
| `assert_string_equal` | function | `tests/test_js_sandbox.c:82` | `assert_string_equal(r.value, "3");` |
| `assert_true` | function | `tests/test_js_sandbox.c:26` | `assert_true(l.max_source_bytes > 0);` |
| `cmocka_run_group_tests` | function | `tests/test_js_sandbox.c:371` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `js_context_free` | function | `tests/test_js_sandbox.c:63` | `js_context_free(ctx);` |
| `js_result_free` | function | `tests/test_js_sandbox.c:83` | `js_result_free(&r);` |
| `js_set_time_budget` | function | `tests/test_js_sandbox.c:163` | `js_set_time_budget(NULL, 1000);` |
| `main` | function | `tests/test_js_sandbox.c:339` | `int main(void)` |
| `memset` | function | `tests/test_js_sandbox.c:78` | `memset(&r, 0, sizeof r);` |
| `test_context_free_null_and_double` | function | `tests/test_js_sandbox.c:202` | `static void test_context_free_null_and_double(void **state)` |
| `test_context_new_and_free` | function | `tests/test_js_sandbox.c:57` | `static void test_context_new_and_free(void **state)` |
| `test_context_new_null_out` | function | `tests/test_js_sandbox.c:65` | `static void test_context_new_null_out(void **state)` |
| `test_eval_arithmetic` | function | `tests/test_js_sandbox.c:72` | `static void test_eval_arithmetic(void **state)` |
| `test_eval_named_captures_location` | function | `tests/test_js_sandbox.c:287` | `static void test_eval_named_captures_location(void **state)` |
| `test_eval_named_null_filename_defaults` | function | `tests/test_js_sandbox.c:308` | `static void test_eval_named_null_filename_defaults(void **state)` |
| `test_eval_null_args` | function | `tests/test_js_sandbox.c:210` | `static void test_eval_null_args(void **state)` |
| `test_eval_runtime_exception` | function | `tests/test_js_sandbox.c:107` | `static void test_eval_runtime_exception(void **state)` |
| `test_eval_string_concat` | function | `tests/test_js_sandbox.c:86` | `static void test_eval_string_concat(void **state)` |
| `test_eval_syntax_error` | function | `tests/test_js_sandbox.c:98` | `static void test_eval_syntax_error(void **state)` |
| `test_eval_thrown_primitive_has_no_location` | function | `tests/test_js_sandbox.c:323` | `static void test_eval_thrown_primitive_has_no_location(void **state)` |
| `test_filesystem_access_is_reference_error` | function | `tests/test_js_sandbox.c:134` | `static void test_filesystem_access_is_reference_error(void **state)` |
| `test_infinite_loop_times_out` | function | `tests/test_js_sandbox.c:147` | `static void test_infinite_loop_times_out(void **state)` |
| `test_loc_file_may_contain_colons` | function | `tests/test_js_sandbox.c:244` | `static void test_loc_file_may_contain_colons(void **state)` |
| `test_loc_line_only_sets_col_zero` | function | `tests/test_js_sandbox.c:255` | `static void test_loc_line_only_sets_col_zero(void **state)` |
| `test_loc_parses_bare_frame` | function | `tests/test_js_sandbox.c:235` | `static void test_loc_parses_bare_frame(void **state)` |
| `test_loc_parses_named_frame` | function | `tests/test_js_sandbox.c:224` | `static void test_loc_parses_named_frame(void **state)` |
| `test_loc_rejects_garbage_and_null` | function | `tests/test_js_sandbox.c:272` | `static void test_loc_rejects_garbage_and_null(void **state)` |
| `test_loc_truncates_to_cap` | function | `tests/test_js_sandbox.c:264` | `static void test_loc_truncates_to_cap(void **state)` |
| `test_memory_limit_is_enforced` | function | `tests/test_js_sandbox.c:177` | `static void test_memory_limit_is_enforced(void **state)` |
| `test_no_io_globals` | function | `tests/test_js_sandbox.c:121` | `static void test_no_io_globals(void **state)` |
| `test_result_free_on_zeroed` | function | `tests/test_js_sandbox.c:193` | `static void test_result_free_on_zeroed(void **state)` |
| `test_set_time_budget_applies` | function | `tests/test_js_sandbox.c:161` | `static void test_set_time_budget_applies(void **state)` |
| `test_validate_accepts_within_cap` | function | `tests/test_js_sandbox.c:50` | `static void test_validate_accepts_within_cap(void **state)` |
| `test_validate_rejects_empty` | function | `tests/test_js_sandbox.c:38` | `static void test_validate_rejects_empty(void **state)` |
| `test_validate_rejects_null` | function | `tests/test_js_sandbox.c:33` | `static void test_validate_rejects_null(void **state)` |
| `test_validate_rejects_oversize` | function | `tests/test_js_sandbox.c:43` | `static void test_validate_rejects_oversize(void **state)` |
| `assert_int_equal` | function | `tests/test_link_nav.c:26` | `assert_int_equal(ln_resolve("https://h/", "/x", NULL), LN_ERR_NULL_ARG);` |
| `assert_non_null` | function | `tests/test_link_nav.c:237` | `assert_non_null(ln_block_reason_text(LN_BLOCK_FOREIGN_SCHEME));` |
| `assert_string_equal` | function | `tests/test_link_nav.c:41` | `assert_string_equal(R.target, "");` |
| `assert_true` | function | `tests/test_link_nav.c:109` | `assert_true(strlen(R.target) > 4096);` |
| `cmocka_run_group_tests` | function | `tests/test_link_nav.c:297` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_link_nav.c:272` | `int main(void)` |
| `memcpy` | function | `tests/test_link_nav.c:198` | `memcpy(big, "https://h.example/", 18);` |
| `memset` | function | `tests/test_link_nav.c:105` | `memset(href + 1, 'x', 4499);` |
| `test_block_reason_text` | function | `tests/test_link_nav.c:233` | `static void test_block_reason_text(void **state)` |
| `test_block_reasons` | function | `tests/test_link_nav.c:206` | `static void test_block_reasons(void **state)` |
| `test_file_absolute_path` | function | `tests/test_link_nav.c:140` | `static void test_file_absolute_path(void **state)` |
| `test_file_base_blocks_schemes_and_scheme_relative` | function | `tests/test_link_nav.c:164` | `static void test_file_base_blocks_schemes_and_scheme_relative(void **state)` |
| `test_file_base_to_https` | function | `tests/test_link_nav.c:156` | `static void test_file_base_to_https(void **state)` |
| `test_file_drops_fragment` | function | `tests/test_link_nav.c:148` | `static void test_file_drops_fragment(void **state)` |
| `test_file_parent` | function | `tests/test_link_nav.c:132` | `static void test_file_parent(void **state)` |
| `test_file_relative` | function | `tests/test_link_nav.c:124` | `static void test_file_relative(void **state)` |
| `test_fragment_capture` | function | `tests/test_link_nav.c:243` | `static void test_fragment_capture(void **state)` |
| `test_fragment_is_same_document` | function | `tests/test_link_nav.c:36` | `static void test_fragment_is_same_document(void **state)` |
| `test_href_cleaning` | function | `tests/test_link_nav.c:113` | `static void test_href_cleaning(void **state)` |
| `test_https_absolute` | function | `tests/test_link_nav.c:48` | `static void test_https_absolute(void **state)` |
| `test_https_absolute_path_and_parent` | function | `tests/test_link_nav.c:64` | `static void test_https_absolute_path_and_parent(void **state)` |
| `test_https_blocks_downgrade_and_schemes` | function | `tests/test_link_nav.c:75` | `static void test_https_blocks_downgrade_and_schemes(void **state)` |
| `test_https_relative` | function | `tests/test_link_nav.c:56` | `static void test_https_relative(void **state)` |
| `test_https_scheme_relative` | function | `tests/test_link_nav.c:90` | `static void test_https_scheme_relative(void **state)` |
| `test_no_base` | function | `tests/test_link_nav.c:178` | `static void test_no_base(void **state)` |
| `test_null_href_blocked` | function | `tests/test_link_nav.c:28` | `static void test_null_href_blocked(void **state)` |
| `test_null_out` | function | `tests/test_link_nav.c:23` | `static void test_null_out(void **state)` |
| `test_overflow_blocked` | function | `tests/test_link_nav.c:194` | `static void test_overflow_blocked(void **state)` |
| `test_resolve_long_bundle_target` | function | `tests/test_link_nav.c:101` | `static void test_resolve_long_bundle_target(void **state)` |
| `assert_int_equal` | function | `tests/test_local_store.c:33` | `assert_int_equal( ls_seal(KEY, aead, (const uint8_t *)PT, sizeof PT - 1, &blob, &blob_len), LS_OK);` |
| `assert_memory_equal` | function | `tests/test_local_store.c:42` | `assert_memory_equal(out, PT, sizeof PT - 1);` |
| `assert_memory_not_equal` | function | `tests/test_local_store.c:114` | `assert_memory_not_equal(a, b, al);` |
| `assert_non_null` | function | `tests/test_local_store.c:37` | `assert_non_null(blob);` |
| `assert_null` | function | `tests/test_local_store.c:79` | `assert_null(out);` |
| `assert_true` | function | `tests/test_local_store.c:91` | `assert_true(off < blob_len);` |
| `cmocka_run_group_tests` | function | `tests/test_local_store.c:210` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `local_store` | function | `tests/test_local_store.c:2` | `* TDD suite for local_store (Hito 5 - Zero Knowledge: encrypted local state). * * RED state until src/local_store.c exis` |
| `ls_free` | function | `tests/test_local_store.c:43` | `ls_free(blob, blob_len);` |
| `main` | function | `tests/test_local_store.c:192` | `int main(void)` |
| `memcpy` | function | `tests/test_local_store.c:76` | `memcpy(bad, KEY, LS_KEY_LEN);` |
| `memset` | function | `tests/test_local_store.c:153` | `memset(salt1, 0xAA, sizeof salt1);` |
| `roundtrip_raw` | function | `tests/test_local_store.c:29` | `static void roundtrip_raw(ls_aead aead)` |
| `tamper_at` | function | `tests/test_local_store.c:84` | `static void tamper_at(size_t off)` |
| `test_derive_key` | function | `tests/test_local_store.c:148` | `static void test_derive_key(void **s)` |
| `test_empty_plaintext` | function | `tests/test_local_store.c:52` | `static void test_empty_plaintext(void **s)` |
| `test_format_errors` | function | `tests/test_local_store.c:165` | `static void test_format_errors(void **s)` |
| `test_nondeterministic` | function | `tests/test_local_store.c:106` | `static void test_nondeterministic(void **s)` |
| `test_null_and_limits` | function | `tests/test_local_store.c:180` | `static void test_null_and_limits(void **s)` |
| `test_passphrase_roundtrip` | function | `tests/test_local_store.c:120` | `static void test_passphrase_roundtrip(void **s)` |
| `test_roundtrip_aes` | function | `tests/test_local_store.c:47` | `static void test_roundtrip_aes(void **s)` |
| `test_roundtrip_chacha` | function | `tests/test_local_store.c:49` | `static void test_roundtrip_chacha(void **s)` |
| `test_tamper_aead_id` | function | `tests/test_local_store.c:103` | `static void test_tamper_aead_id(void **s)` |
| `test_tamper_ciphertext` | function | `tests/test_local_store.c:98` | `static void test_tamper_ciphertext(void **s)` |
| `test_tamper_nonce` | function | `tests/test_local_store.c:101` | `static void test_tamper_nonce(void **s)` |
| `test_tamper_salt` | function | `tests/test_local_store.c:102` | `static void test_tamper_salt(void **s)` |
| `test_tamper_tag` | function | `tests/test_local_store.c:100` | `static void test_tamper_tag(void **s)` |
| `test_wrong_key` | function | `tests/test_local_store.c:66` | `static void test_wrong_key(void **s)` |
| `assert_int_equal` | function | `tests/test_media_decoder.c:21` | `assert_int_equal(md_pace_due_ms(&p, 1000, 7000000), 1000);` |
| `assert_true` | function | `tests/test_media_decoder.c:22` | `assert_true(p.primed);` |
| `cmocka_run_group_tests_name` | function | `tests/test_media_decoder.c:98` | `return cmocka_run_group_tests_name("media_decoder", tests, NULL, NULL);` |
| `main` | function | `tests/test_media_decoder.c:88` | `int main(void)` |
| `test_pacer_backwards_pts_reanchors` | function | `tests/test_media_decoder.c:40` | `static void test_pacer_backwards_pts_reanchors(void **state)` |
| `test_pacer_hostile_pts_bounded` | function | `tests/test_media_decoder.c:69` | `static void test_pacer_hostile_pts_bounded(void **state)` |
| `test_pacer_lag_reanchors` | function | `tests/test_media_decoder.c:52` | `static void test_pacer_lag_reanchors(void **state)` |
| `test_pacer_null_safe` | function | `tests/test_media_decoder.c:84` | `static void test_pacer_null_safe(void **state)` |
| `test_pacer_paces_by_pts_delta` | function | `tests/test_media_decoder.c:28` | `static void test_pacer_paces_by_pts_delta(void **state)` |
| `assert_int_equal` | function | `tests/test_net_realm.c:24` | `assert_int_equal(nr_classify_host("expyuzz4wqqyqhjn.onion"), NR_ONION);` |
| `assert_non_null` | function | `tests/test_net_realm.c:136` | `assert_non_null(nr_realm_name((nr_realm)999));` |
| `assert_string_equal` | function | `tests/test_net_realm.c:128` | `assert_string_equal(nr_realm_name(NR_CLEARNET), "clearnet");` |
| `cmocka_run_group_tests` | function | `tests/test_net_realm.c:155` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_net_realm.c:139` | `int main(void)` |
| `memset` | function | `tests/test_net_realm.c:60` | `memset(big, 'a', sizeof big);` |
| `test_classify_host_clearnet` | function | `tests/test_net_realm.c:36` | `static void test_classify_host_clearnet(void **state)` |
| `test_classify_host_edges` | function | `tests/test_net_realm.c:53` | `static void test_classify_host_edges(void **state)` |
| `test_classify_host_i2p` | function | `tests/test_net_realm.c:29` | `static void test_classify_host_i2p(void **state)` |
| `test_classify_host_lookalikes` | function | `tests/test_net_realm.c:44` | `static void test_classify_host_lookalikes(void **state)` |
| `test_classify_host_onion` | function | `tests/test_net_realm.c:21` | `static void test_classify_host_onion(void **state)` |
| `test_classify_url` | function | `tests/test_net_realm.c:66` | `static void test_classify_url(void **state)` |
| `test_names` | function | `tests/test_net_realm.c:125` | `static void test_names(void **state)` |
| `test_realm_allows_http` | function | `tests/test_net_realm.c:117` | `static void test_realm_allows_http(void **state)` |
| `test_route_clearnet` | function | `tests/test_net_realm.c:95` | `static void test_route_clearnet(void **state)` |
| `test_route_i2p` | function | `tests/test_net_realm.c:87` | `static void test_route_i2p(void **state)` |
| `test_route_null_blocked` | function | `tests/test_net_realm.c:109` | `static void test_route_null_blocked(void **state)` |
| `test_route_onion` | function | `tests/test_net_realm.c:78` | `static void test_route_onion(void **state)` |
| `_GNU_SOURCE` | macro | `tests/test_os_sandbox.c:13` | `#define _GNU_SOURCE` |
| `_exit` | function | `tests/test_os_sandbox.c:87` | `_exit(0);` |
| `assert_false` | function | `tests/test_os_sandbox.c:53` | `assert_false(os_policy_allows(__NR_socket));` |
| `assert_int_equal` | function | `tests/test_os_sandbox.c:90` | `assert_int_equal(waitpid(pid, &st, 0), pid);` |
| `assert_int_not_equal` | function | `tests/test_os_sandbox.c:319` | `assert_int_not_equal(pid, -1);` |
| `assert_non_null` | function | `tests/test_os_sandbox.c:260` | `assert_non_null(mkdtemp(dir));` |
| `assert_true` | function | `tests/test_os_sandbox.c:45` | `assert_true(os_policy_allows(__NR_read));` |
| `close` | function | `tests/test_os_sandbox.c:266` | `close(wfd);` |
| `cmocka_run_group_tests` | function | `tests/test_os_sandbox.c:356` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_os_sandbox.c:334` | `int main(void)` |
| `net_ns_inode` | function | `tests/test_os_sandbox.c:304` | `static unsigned long net_ns_inode(void)` |
| `rmdir` | function | `tests/test_os_sandbox.c:284` | `rmdir(dir);` |
| `snprintf` | function | `tests/test_os_sandbox.c:262` | `snprintf(file, sizeof file, "%s/f", dir);` |
| `suite` | function | `tests/test_os_sandbox.c:313` | `* suite (it is best-effort defense in depth), and on a host that allows them the
 * isolation mus...` |
| `test_harden_allows_permitted_syscall` | function | `tests/test_os_sandbox.c:96` | `static void test_harden_allows_permitted_syscall(void **state)` |
| `test_harden_blocks_exec_mmap` | function | `tests/test_os_sandbox.c:162` | `static void test_harden_blocks_exec_mmap(void **state)` |
| `test_harden_blocks_exec_mprotect` | function | `tests/test_os_sandbox.c:182` | `static void test_harden_blocks_exec_mprotect(void **state)` |
| `test_harden_errno_denies_with_eperm` | function | `tests/test_os_sandbox.c:112` | `static void test_harden_errno_denies_with_eperm(void **state)` |
| `test_harden_kills_denied_syscall` | function | `tests/test_os_sandbox.c:79` | `static void test_harden_kills_denied_syscall(void **state)` |
| `test_harden_kills_io_uring_setup` | function | `tests/test_os_sandbox.c:130` | `static void test_harden_kills_io_uring_setup(void **state)` |
| `test_landlock_abi_present` | function | `tests/test_os_sandbox.c:232` | `static void test_landlock_abi_present(void **state)` |
| `test_landlock_allow_read` | function | `tests/test_os_sandbox.c:257` | `static void test_landlock_allow_read(void **state)` |
| `test_landlock_deny_all` | function | `tests/test_os_sandbox.c:239` | `static void test_landlock_deny_all(void **state)` |
| `test_no_dump_undumpable` | function | `tests/test_os_sandbox.c:214` | `static void test_no_dump_undumpable(void **state)` |
| `test_policy_allows_safe` | function | `tests/test_os_sandbox.c:42` | `static void test_policy_allows_safe(void **state)` |
| `test_policy_denies_dangerous` | function | `tests/test_os_sandbox.c:50` | `static void test_policy_denies_dangerous(void **state)` |
| `test_policy_denies_io_uring` | function | `tests/test_os_sandbox.c:64` | `static void test_policy_denies_io_uring(void **state)` |
| `test_policy_size` | function | `tests/test_os_sandbox.c:70` | `static void test_policy_size(void **state)` |
| `test_prot_allowed_wx` | function | `tests/test_os_sandbox.c:151` | `static void test_prot_allowed_wx(void **state)` |
| `unlink` | function | `tests/test_os_sandbox.c:282` | `unlink(file);` |
| `applies` | function | `tests/test_page_view.c:3191` | `* <style>: an extern rule applies (presentation and display:none alike);` |
| `assert_false` | function | `tests/test_page_view.c:1619` | `assert_false(blank);` |
| `assert_int_equal` | function | `tests/test_page_view.c:29` | `assert_int_equal(hp_parse(html, strlen(html), NULL, &doc), HP_OK);` |
| `assert_int_not_equal` | function | `tests/test_page_view.c:492` | `assert_int_not_equal(rank->block_break, 0);` |
| `assert_non_null` | function | `tests/test_page_view.c:30` | `assert_non_null(doc);` |
| `assert_null` | function | `tests/test_page_view.c:77` | `assert_null(pv_at(v, 0));` |
| `assert_string_equal` | function | `tests/test_page_view.c:92` | `assert_string_equal(a->text, "hello");` |
| `assert_true` | function | `tests/test_page_view.c:346` | `assert_true(name->cont_id >= 0);` |
| `break` | function | `tests/test_page_view.c:659` | `* block break (from entering <p>);` |
| `cmocka_run_group_tests` | function | `tests/test_page_view.c:3793` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `dom_free` | function | `tests/test_page_view.c:3373` | `dom_free(idx);` |
| `find_image` | function | `tests/test_page_view.c:44` | `static const pv_run *find_image(const pv_view *v, const char *src)` |
| `find_input` | function | `tests/test_page_view.c:2661` | `static const pv_run *find_input(const pv_view *v, const char *name)` |
| `find_svg` | function | `tests/test_page_view.c:62` | `static const pv_run *find_svg(const pv_view *v)` |
| `find_text` | function | `tests/test_page_view.c:35` | `static const pv_run *find_text(const pv_view *v, const char *text)` |
| `find_video` | function | `tests/test_page_view.c:53` | `static const pv_run *find_video(const pv_view *v, const char *src)` |
| `float_id` | function | `tests/test_page_view.c:1453` | `* A run inside a float nested in another float reports the inner element as * float_id (unchanged) plus the outer elemen` |
| `height` | function | `tests/test_page_view.c:3165` | `* real height (jkanime's donghuas/ovas panes are display:none, yet all their
 * thumbnails flowed...` |
| `hp_document_free` | function | `tests/test_page_view.c:211` | `hp_document_free(doc);` |
| `it` | function | `tests/test_page_view.c:590` | `* the rest of the row share it (so an overflowing table degrades to one row per * line, not one blob). */ assert_int_equ` |
| `main` | function | `tests/test_page_view.c:3638` | `int main(void)` |
| `ordinal` | function | `tests/test_page_view.c:1680` | `* cont_item ordinal (they are one flex/grid item and must flow together in one * cell);` |
| `parse` | function | `tests/test_page_view.c:27` | `static hp_document *parse(const char *html)` |
| `pv_free` | function | `tests/test_page_view.c:78` | `pv_free(v);` |
| `pv_set_bgcolor` | function | `tests/test_page_view.c:1060` | `pv_set_bgcolor(v, 0x654321);` |
| `pv_set_box` | function | `tests/test_page_view.c:2120` | `pv_set_box(w, 12, 8, 500, 1, 40, 4);` |
| `pv_set_color` | function | `tests/test_page_view.c:1052` | `pv_set_color(v, 0x102030);` |
| `pv_set_container` | function | `tests/test_page_view.c:2025` | `pv_set_container(v, 2, BX_DISPLAY_GRID, 8, FX_JUSTIFY_END, 4, 0, -1, 0);` |
| `pv_set_node_id` | function | `tests/test_page_view.c:3326` | `pv_set_node_id(v, 42);` |
| `pv_set_text_style` | function | `tests/test_page_view.c:3380` | `pv_set_text_style(v, CSS_ALIGN_CENTER, 150, 1, 140, CSS_DECO_UNDERLINE);` |
| `reverted` | function | `tests/test_page_view.c:3150` | `* behavior of treating inline display:none as visible when JS is off * was reverted (commit 897f414 regression) because ` |
| `size` | function | `tests/test_page_view.c:728` | `* size (~100px) instead of the CSS 40px, blowing up flex rows (slashdot socials). */
static void ...` |
| `test_append_copies_fields` | function | `tests/test_page_view.c:80` | `static void test_append_copies_fields(void **state)` |
| `test_append_image_copies_fields` | function | `tests/test_page_view.c:107` | `static void test_append_image_copies_fields(void **state)` |
| `test_append_image_null_args` | function | `tests/test_page_view.c:123` | `static void test_append_image_null_args(void **state)` |
| `test_append_null_args` | function | `tests/test_page_view.c:187` | `static void test_append_null_args(void **state)` |
| `test_append_transcodes_cp1252_quotes` | function | `tests/test_page_view.c:160` | `static void test_append_transcodes_cp1252_quotes(void **state)` |
| `test_append_transcodes_latin1` | function | `tests/test_page_view.c:139` | `static void test_append_transcodes_latin1(void **state)` |
| `test_append_transcodes_word` | function | `tests/test_page_view.c:149` | `static void test_append_transcodes_word(void **state)` |
| `test_append_undefined_cp1252_is_qmark` | function | `tests/test_page_view.c:170` | `static void test_append_undefined_cp1252_is_qmark(void **state)` |
| `test_append_valid_utf8_passthrough` | function | `tests/test_page_view.c:180` | `static void test_append_valid_utf8_passthrough(void **state)` |
| `test_append_video_copies_fields` | function | `tests/test_page_view.c:3495` | `static void test_append_video_copies_fields(void **state)` |
| `test_append_video_no_poster` | function | `tests/test_page_view.c:3514` | `static void test_append_video_no_poster(void **state)` |
| `test_append_video_null_args` | function | `tests/test_page_view.c:3530` | `static void test_append_video_null_args(void **state)` |
| `test_box_defaults_and_setter` | function | `tests/test_page_view.c:2102` | `static void test_box_defaults_and_setter(void **state)` |
| `test_build_abs_child_is_not_a_flex_item` | function | `tests/test_page_view.c:1857` | `static void test_build_abs_child_is_not_a_flex_item(void **state)` |
| `test_build_absolute_inside_float_escapes` | function | `tests/test_page_view.c:1574` | `static void test_build_absolute_inside_float_escapes(void **state)` |
| `test_build_audio_as_video_kind` | function | `tests/test_page_view.c:3624` | `static void test_build_audio_as_video_kind(void **state)` |
| `test_build_author_color` | function | `tests/test_page_view.c:1071` | `static void test_build_author_color(void **state)` |
| `test_build_bgcolor_attr_fallback` | function | `tests/test_page_view.c:543` | `static void test_build_bgcolor_attr_fallback(void **state)` |
| `test_build_block_break_between_paragraphs` | function | `tests/test_page_view.c:626` | `static void test_build_block_break_between_paragraphs(void **state)` |
| `test_build_box_leaf_inline` | function | `tests/test_page_view.c:2067` | `static void test_build_box_leaf_inline(void **state)` |
| `test_build_box_tree_empty_no_box` | function | `tests/test_page_view.c:2649` | `static void test_build_box_tree_empty_no_box(void **state)` |
| `test_build_box_tree_textless_wrapper` | function | `tests/test_page_view.c:2624` | `static void test_build_box_tree_textless_wrapper(void **state)` |
| `test_build_boxdeco_border_padding` | function | `tests/test_page_view.c:2214` | `static void test_build_boxdeco_border_padding(void **state)` |
| `test_build_boxdeco_defaults_no_box` | function | `tests/test_page_view.c:2529` | `static void test_build_boxdeco_defaults_no_box(void **state)` |
| `test_build_boxdeco_dims_alone_trigger_box` | function | `tests/test_page_view.c:2425` | `static void test_build_boxdeco_dims_alone_trigger_box(void **state)` |
| `test_build_boxdeco_fit_content_height_is_auto` | function | `tests/test_page_view.c:2175` | `static void test_build_boxdeco_fit_content_height_is_auto(void **state)` |
| `test_build_boxdeco_h_margin_alone_creates_box` | function | `tests/test_page_view.c:2132` | `static void test_build_boxdeco_h_margin_alone_creates_box(void **state)` |
| `test_build_boxdeco_h_margin_zero_auto_no_box` | function | `tests/test_page_view.c:2152` | `static void test_build_boxdeco_h_margin_zero_auto_no_box(void **state)` |
| `test_build_boxdeco_min_content_height_is_auto` | function | `tests/test_page_view.c:2197` | `static void test_build_boxdeco_min_content_height_is_auto(void **state)` |
| `test_build_boxdeco_shadow_outline` | function | `tests/test_page_view.c:2322` | `static void test_build_boxdeco_shadow_outline(void **state)` |
| `test_build_boxdeco_shared_id_within_block` | function | `tests/test_page_view.c:2561` | `static void test_build_boxdeco_shared_id_within_block(void **state)` |
| `test_build_boxdeco_sibling_blocks_distinct_ids` | function | `tests/test_page_view.c:2543` | `static void test_build_boxdeco_sibling_blocks_distinct_ids(void **state)` |
| `test_build_boxdeco_visibility_overflow_cursor` | function | `tests/test_page_view.c:2345` | `static void test_build_boxdeco_visibility_overflow_cursor(void **state)` |
| `test_build_caret_color_inherited` | function | `tests/test_page_view.c:3472` | `static void test_build_caret_color_inherited(void **state)` |
| `test_build_combinator_selectors` | function | `tests/test_page_view.c:1197` | `static void test_build_combinator_selectors(void **state)` |
| `test_build_cont_item_identity` | function | `tests/test_page_view.c:1682` | `static void test_build_cont_item_identity(void **state)` |
| `test_build_content_visibility_hidden_folds` | function | `tests/test_page_view.c:3427` | `static void test_build_content_visibility_hidden_folds(void **state)` |
| `test_build_control_without_form` | function | `tests/test_page_view.c:2812` | `static void test_build_control_without_form(void **state)` |
| `test_build_css_bold_and_inline_wins` | function | `tests/test_page_view.c:3120` | `static void test_build_css_bold_and_inline_wins(void **state)` |
| `test_build_cursor_alone_triggers_box` | function | `tests/test_page_view.c:2370` | `static void test_build_cursor_alone_triggers_box(void **state)` |
| `test_build_display_none_hidden` | function | `tests/test_page_view.c:3139` | `static void test_build_display_none_hidden(void **state)` |
| `test_build_empty_box_gets_run_and_box` | function | `tests/test_page_view.c:2246` | `static void test_build_empty_box_gets_run_and_box(void **state)` |
| `test_build_empty_document` | function | `tests/test_page_view.c:1034` | `static void test_build_empty_document(void **state)` |
| `test_build_empty_flex_grow_spacer` | function | `tests/test_page_view.c:887` | `static void test_build_empty_flex_grow_spacer(void **state)` |
| `test_build_flex_container` | function | `tests/test_page_view.c:1235` | `static void test_build_flex_container(void **state)` |
| `test_build_flex_container_from_sheet` | function | `tests/test_page_view.c:1957` | `static void test_build_flex_container_from_sheet(void **state)` |
| `test_build_flex_item_values` | function | `tests/test_page_view.c:1348` | `static void test_build_flex_item_values(void **state)` |
| `test_build_flex_whitespace_not_item` | function | `tests/test_page_view.c:1604` | `static void test_build_flex_whitespace_not_item(void **state)` |
| `test_build_flex_wrap_align_row_gap` | function | `tests/test_page_view.c:1307` | `static void test_build_flex_wrap_align_row_gap(void **state)` |
| `test_build_float_outermost_founder` | function | `tests/test_page_view.c:1457` | `static void test_build_float_outermost_founder(void **state)` |
| `test_build_float_threading` | function | `tests/test_page_view.c:1411` | `static void test_build_float_threading(void **state)` |
| `test_build_float_widthless_stays_unset` | function | `tests/test_page_view.c:831` | `static void test_build_float_widthless_stays_unset(void **state)` |
| `test_build_flow_table_row_is_one_block` | function | `tests/test_page_view.c:2287` | `static void test_build_flow_table_row_is_one_block(void **state)` |
| `test_build_form_post_and_hidden` | function | `tests/test_page_view.c:2703` | `static void test_build_form_post_and_hidden(void **state)` |
| `test_build_grid_columns_from_sheet` | function | `tests/test_page_view.c:1979` | `static void test_build_grid_columns_from_sheet(void **state)` |
| `test_build_grid_container` | function | `tests/test_page_view.c:1793` | `static void test_build_grid_container(void **state)` |
| `test_build_hbox_container_width_never_seeds_items` | function | `tests/test_page_view.c:1545` | `static void test_build_hbox_container_width_never_seeds_items(void **state)` |
| `test_build_hbox_margin_above_container_merges` | function | `tests/test_page_view.c:1525` | `static void test_build_hbox_margin_above_container_merges(void **state)` |
| `test_build_heading_level` | function | `tests/test_page_view.c:226` | `static void test_build_heading_level(void **state)` |
| `test_build_image_auto_size_keeps_attr` | function | `tests/test_page_view.c:867` | `static void test_build_image_auto_size_keeps_attr(void **state)` |
| `test_build_image_css_size_overrides_attr` | function | `tests/test_page_view.c:850` | `static void test_build_image_css_size_overrides_attr(void **state)` |
| `test_build_image_in_skipped_subtree_ignored` | function | `tests/test_page_view.c:904` | `static void test_build_image_in_skipped_subtree_ignored(void **state)` |
| `test_build_image_no_src_and_no_srcset_ignored` | function | `tests/test_page_view.c:1021` | `static void test_build_image_no_src_and_no_srcset_ignored(void **state)` |
| `test_build_image_plain_src_wins_over_srcset` | function | `tests/test_page_view.c:978` | `static void test_build_image_plain_src_wins_over_srcset(void **state)` |
| `test_build_image_px_and_tracking_dims` | function | `tests/test_page_view.c:702` | `static void test_build_image_px_and_tracking_dims(void **state)` |
| `test_build_image_rendering_inherited` | function | `tests/test_page_view.c:3453` | `static void test_build_image_rendering_inherited(void **state)` |
| `test_build_image_srcset_data_url_not_truncated_at_comma` | function | `tests/test_page_view.c:1006` | `static void test_build_image_srcset_data_url_not_truncated_at_comma(void **state)` |
| `test_build_image_srcset_fallback_when_no_src` | function | `tests/test_page_view.c:962` | `static void test_build_image_srcset_fallback_when_no_src(void **state)` |
| `test_build_image_srcset_single_no_descriptor` | function | `tests/test_page_view.c:993` | `static void test_build_image_srcset_single_no_descriptor(void **state)` |
| `test_build_image_unknown_dims` | function | `tests/test_page_view.c:687` | `static void test_build_image_unknown_dims(void **state)` |
| `test_build_image_with_dims` | function | `tests/test_page_view.c:670` | `static void test_build_image_with_dims(void **state)` |
| `test_build_image_without_src_ignored` | function | `tests/test_page_view.c:943` | `static void test_build_image_without_src_ignored(void **state)` |
| `test_build_inline_emphasis` | function | `tests/test_page_view.c:244` | `static void test_build_inline_emphasis(void **state)` |
| `test_build_inline_link_no_break_within_paragraph` | function | `tests/test_page_view.c:652` | `static void test_build_inline_link_no_break_within_paragraph(void **state)` |
| `test_build_inline_whitespace_kept` | function | `tests/test_page_view.c:1660` | `static void test_build_inline_whitespace_kept(void **state)` |
| `test_build_link_with_href` | function | `tests/test_page_view.c:607` | `static void test_build_link_with_href(void **state)` |
| `test_build_nested_table_not_flattened` | function | `tests/test_page_view.c:558` | `static void test_build_nested_table_not_flattened(void **state)` |
| `test_build_node_id_matches_dom_index` | function | `tests/test_page_view.c:3338` | `static void test_build_node_id_matches_dom_index(void **state)` |
| `test_build_noscript_hidden_when_js_on` | function | `tests/test_page_view.c:930` | `static void test_build_noscript_hidden_when_js_on(void **state)` |
| `test_build_noscript_shown_when_js_off` | function | `tests/test_page_view.c:917` | `static void test_build_noscript_shown_when_js_off(void **state)` |
| `test_build_null_args` | function | `tests/test_page_view.c:204` | `static void test_build_null_args(void **state)` |
| `test_build_oof_flag_badges_idiom` | function | `tests/test_page_view.c:1938` | `static void test_build_oof_flag_badges_idiom(void **state)` |
| `test_build_oof_flag_via_cascade` | function | `tests/test_page_view.c:1914` | `static void test_build_oof_flag_via_cascade(void **state)` |
| `test_build_oof_image_carries_block_id` | function | `tests/test_page_view.c:1489` | `static void test_build_oof_image_carries_block_id(void **state)` |
| `test_build_ordered_and_nested_list` | function | `tests/test_page_view.c:303` | `static void test_build_ordered_and_nested_list(void **state)` |
| `test_build_plain_text` | function | `tests/test_page_view.c:213` | `static void test_build_plain_text(void **state)` |
| `test_build_pointer_events_on_box` | function | `tests/test_page_view.c:3408` | `static void test_build_pointer_events_on_box(void **state)` |
| `test_build_pseudo_classes_and_siblings` | function | `tests/test_page_view.c:2885` | `static void test_build_pseudo_classes_and_siblings(void **state)` |
| `test_build_reader_skips_boilerplate` | function | `tests/test_page_view.c:3294` | `static void test_build_reader_skips_boilerplate(void **state)` |
| `test_build_root_element_style_inherits` | function | `tests/test_page_view.c:1819` | `static void test_build_root_element_style_inherits(void **state)` |
| `test_build_root_font_size_is_overridable` | function | `tests/test_page_view.c:1837` | `static void test_build_root_font_size_is_overridable(void **state)` |
| `test_build_search_form_get` | function | `tests/test_page_view.c:2670` | `static void test_build_search_form_get(void **state)` |
| `test_build_select_defaults_to_first_option` | function | `tests/test_page_view.c:2796` | `static void test_build_select_defaults_to_first_option(void **state)` |
| `test_build_select_shows_selected_option` | function | `tests/test_page_view.c:2757` | `static void test_build_select_shows_selected_option(void **state)` |
| `test_build_skips_script_and_style` | function | `tests/test_page_view.c:638` | `static void test_build_skips_script_and_style(void **state)` |
| `test_build_style_cache_distinct_siblings` | function | `tests/test_page_view.c:3008` | `static void test_build_style_cache_distinct_siblings(void **state)` |
| `test_build_styled_external_css` | function | `tests/test_page_view.c:3195` | `static void test_build_styled_external_css(void **state)` |
| `test_build_svg_fills_border_box_ancestor` | function | `tests/test_page_view.c:770` | `static void test_build_svg_fills_border_box_ancestor(void **state)` |
| `test_build_svg_no_ancestor_width_unset` | function | `tests/test_page_view.c:790` | `static void test_build_svg_no_ancestor_width_unset(void **state)` |
| `test_build_table_cell_author_styles` | function | `tests/test_page_view.c:2948` | `static void test_build_table_cell_author_styles(void **state)` |
| `test_build_table_colspan_rowspan` | function | `tests/test_page_view.c:1747` | `static void test_build_table_colspan_rowspan(void **state)` |
| `test_build_table_flattens_cell` | function | `tests/test_page_view.c:407` | `static void test_build_table_flattens_cell(void **state)` |
| `test_build_table_grid` | function | `tests/test_page_view.c:326` | `static void test_build_table_grid(void **state)` |
| `test_build_table_intercell_whitespace_dropped` | function | `tests/test_page_view.c:366` | `static void test_build_table_intercell_whitespace_dropped(void **state)` |
| `test_build_text_align_and_font_size` | function | `tests/test_page_view.c:3050` | `static void test_build_text_align_and_font_size(void **state)` |
| `test_build_text_decoration` | function | `tests/test_page_view.c:3097` | `static void test_build_text_decoration(void **state)` |
| `test_build_text_overflow_and_word_break` | function | `tests/test_page_view.c:2470` | `static void test_build_text_overflow_and_word_break(void **state)` |
| `test_build_textarea_value` | function | `tests/test_page_view.c:2737` | `static void test_build_textarea_value(void **state)` |
| `test_build_two_forms_distinct_groups` | function | `tests/test_page_view.c:2825` | `static void test_build_two_forms_distinct_groups(void **state)` |
| `test_build_unordered_list` | function | `tests/test_page_view.c:285` | `static void test_build_unordered_list(void **state)` |
| `test_build_video_fallback_suppressed` | function | `tests/test_page_view.c:3599` | `static void test_build_video_fallback_suppressed(void **state)` |
| `test_build_video_source_type_preference` | function | `tests/test_page_view.c:3581` | `static void test_build_video_source_type_preference(void **state)` |
| `test_build_video_uses_source_child` | function | `tests/test_page_view.c:3560` | `static void test_build_video_uses_source_child(void **state)` |
| `test_build_video_with_source` | function | `tests/test_page_view.c:3540` | `static void test_build_video_with_source(void **state)` |
| `test_build_video_without_src_ignored` | function | `tests/test_page_view.c:3613` | `static void test_build_video_without_src_ignored(void **state)` |
| `test_build_zero_padding_is_not_a_box` | function | `tests/test_page_view.c:2270` | `static void test_build_zero_padding_is_not_a_box(void **state)` |
| `test_container_defaults` | function | `tests/test_page_view.c:2019` | `static void test_container_defaults(void **state)` |
| `test_free_null_and_double` | function | `tests/test_page_view.c:195` | `static void test_free_null_and_double(void **state)` |
| `test_gradient_text_runs` | function | `tests/test_page_view.c:1119` | `static void test_gradient_text_runs(void **state)` |
| `test_new_is_empty` | function | `tests/test_page_view.c:71` | `static void test_new_is_empty(void **state)` |
| `test_pseudo_after_on_element_with_children` | function | `tests/test_page_view.c:3246` | `static void test_pseudo_after_on_element_with_children(void **state)` |
| `test_pseudo_before_on_element_with_children` | function | `tests/test_page_view.c:3231` | `static void test_pseudo_before_on_element_with_children(void **state)` |
| `test_pseudo_before_on_empty` | function | `tests/test_page_view.c:3218` | `static void test_pseudo_before_on_empty(void **state)` |
| `test_pseudo_both_before_and_after` | function | `tests/test_page_view.c:3261` | `static void test_pseudo_both_before_and_after(void **state)` |
| `test_pseudo_no_content_no_run` | function | `tests/test_page_view.c:3279` | `static void test_pseudo_no_content_no_run(void **state)` |
| `test_set_color_model` | function | `tests/test_page_view.c:1049` | `static void test_set_color_model(void **state)` |
| `test_set_node_id_model` | function | `tests/test_page_view.c:3322` | `static void test_set_node_id_model(void **state)` |
| `test_set_text_style_model` | function | `tests/test_page_view.c:3376` | `static void test_set_text_style_model(void **state)` |
| `test_text_fill_color_runs` | function | `tests/test_page_view.c:1151` | `static void test_text_fill_color_runs(void **state)` |
| `unset` | function | `tests/test_page_view.c:750` | `* unset (-1) so the render step derives it from the viewBox aspect. */
static void test_build_svg...` |
| `wrapping` | function | `tests/test_page_view.c:1275` | `* sideways instead of wrapping (spec/page_view.md, 2026-08-11 correction). */
static void test_bu...` |
| `assert_int_equal` | function | `tests/test_pdf_export.c:27` | `assert_int_equal(pe_safe_basename("Report_v2.final-1", out, sizeof out), PE_OK);` |
| `assert_null` | function | `tests/test_pdf_export.c:45` | `assert_null(strchr(out, '/'));` |
| `assert_string_equal` | function | `tests/test_pdf_export.c:28` | `assert_string_equal(out, "Report_v2.final-1");` |
| `assert_true` | function | `tests/test_pdf_export.c:119` | `assert_true(strlen(out) <= PE_NAME_MAX);` |
| `cmocka_run_group_tests` | function | `tests/test_pdf_export.c:322` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_pdf_export.c:289` | `int main(void)` |
| `memset` | function | `tests/test_pdf_export.c:115` | `memset(in, 'a', sizeof in - 1);` |
| `pagination` | function | `tests/test_pdf_export.c:8` | `* deterministic pagination (single/multi page, no row splitting, oversized row,
 * gap preservati...` |
| `test_basename_all_separators_fall_back` | function | `tests/test_pdf_export.c:104` | `static void test_basename_all_separators_fall_back(void **state)` |
| `test_basename_collapses_underscores` | function | `tests/test_pdf_export.c:71` | `static void test_basename_collapses_underscores(void **state)` |
| `test_basename_control_bytes_mapped` | function | `tests/test_pdf_export.c:78` | `static void test_basename_control_bytes_mapped(void **state)` |
| `test_basename_dotdot_only_falls_back` | function | `tests/test_pdf_export.c:56` | `static void test_basename_dotdot_only_falls_back(void **state)` |
| `test_basename_empty_and_null_fall_back` | function | `tests/test_pdf_export.c:95` | `static void test_basename_empty_and_null_fall_back(void **state)` |
| `test_basename_length_bound` | function | `tests/test_pdf_export.c:111` | `static void test_basename_length_bound(void **state)` |
| `test_basename_maps_spaces_and_reserved` | function | `tests/test_pdf_export.c:30` | `static void test_basename_maps_spaces_and_reserved(void **state)` |
| `test_basename_neutralizes_traversal` | function | `tests/test_pdf_export.c:48` | `static void test_basename_neutralizes_traversal(void **state)` |
| `test_basename_non_ascii_mapped` | function | `tests/test_pdf_export.c:86` | `static void test_basename_non_ascii_mapped(void **state)` |
| `test_basename_null_out_and_zero_size` | function | `tests/test_pdf_export.c:122` | `static void test_basename_null_out_and_zero_size(void **state)` |
| `test_basename_overflow_fails_closed` | function | `tests/test_pdf_export.c:129` | `static void test_basename_overflow_fails_closed(void **state)` |
| `test_basename_rejects_path_separators` | function | `tests/test_pdf_export.c:38` | `static void test_basename_rejects_path_separators(void **state)` |
| `test_basename_trims_edges` | function | `tests/test_pdf_export.c:63` | `static void test_basename_trims_edges(void **state)` |
| `test_build_path_basic` | function | `tests/test_pdf_export.c:138` | `static void test_build_path_basic(void **state)` |
| `test_build_path_empty_title_fallback` | function | `tests/test_pdf_export.c:161` | `static void test_build_path_empty_title_fallback(void **state)` |
| `test_build_path_ext_hostile_title_contained` | function | `tests/test_pdf_export.c:201` | `static void test_build_path_ext_hostile_title_contained(void **state)` |
| `test_build_path_ext_null_ext` | function | `tests/test_pdf_export.c:193` | `static void test_build_path_ext_null_ext(void **state)` |
| `test_build_path_ext_overflow_fails_closed` | function | `tests/test_pdf_export.c:212` | `static void test_build_path_ext_overflow_fails_closed(void **state)` |
| `test_build_path_ext_png` | function | `tests/test_pdf_export.c:185` | `static void test_build_path_ext_png(void **state)` |
| `test_build_path_hostile_title_contained` | function | `tests/test_pdf_export.c:152` | `static void test_build_path_hostile_title_contained(void **state)` |
| `test_build_path_null_args` | function | `tests/test_pdf_export.c:175` | `static void test_build_path_null_args(void **state)` |
| `test_build_path_overflow_fails_closed` | function | `tests/test_pdf_export.c:168` | `static void test_build_path_overflow_fails_closed(void **state)` |
| `test_build_path_trailing_slash` | function | `tests/test_pdf_export.c:145` | `static void test_build_path_trailing_slash(void **state)` |
| `test_paginate_breaks_without_splitting` | function | `tests/test_pdf_export.c:237` | `static void test_paginate_breaks_without_splitting(void **state)` |
| `test_paginate_invalid_args` | function | `tests/test_pdf_export.c:275` | `static void test_paginate_invalid_args(void **state)` |
| `test_paginate_oversized_row_not_split` | function | `tests/test_pdf_export.c:251` | `static void test_paginate_oversized_row_not_split(void **state)` |
| `test_paginate_preserves_gaps` | function | `tests/test_pdf_export.c:263` | `static void test_paginate_preserves_gaps(void **state)` |
| `test_paginate_single_page` | function | `tests/test_pdf_export.c:222` | `static void test_paginate_single_page(void **state)` |
| `assert_int_equal` | function | `tests/test_perf_trace.c:20` | `assert_int_equal((int)pt_count(&t, (pt_stage)s), 0);` |
| `assert_memory_equal` | function | `tests/test_perf_trace.c:127` | `assert_memory_equal(buf1, buf2, n1);` |
| `assert_non_null` | function | `tests/test_perf_trace.c:129` | `assert_non_null(strstr(buf1, "stage=fetch"));` |
| `assert_null` | function | `tests/test_perf_trace.c:132` | `assert_null(strstr(buf1, "stage=layout"));` |
| `assert_string_equal` | function | `tests/test_perf_trace.c:103` | `assert_string_equal(pt_stage_name(PT_FETCH), "fetch");` |
| `assert_true` | function | `tests/test_perf_trace.c:128` | `assert_true(n1 > 0);` |
| `cmocka_run_group_tests_name` | function | `tests/test_perf_trace.c:189` | `return cmocka_run_group_tests_name("perf_trace", tests, NULL, NULL);` |
| `main` | function | `tests/test_perf_trace.c:173` | `int main(void)` |
| `pt_init` | function | `tests/test_perf_trace.c:18` | `pt_init(&t);` |
| `pt_record` | function | `tests/test_perf_trace.c:32` | `pt_record(&t, PT_LAYOUT, 1500);` |
| `test_elapsed_us_normal` | function | `tests/test_perf_trace.c:88` | `static void test_elapsed_us_normal(void **state)` |
| `test_elapsed_us_underflow_guard` | function | `tests/test_perf_trace.c:94` | `static void test_elapsed_us_underflow_guard(void **state)` |
| `test_format_deterministic_and_only_nonempty_stages` | function | `tests/test_perf_trace.c:114` | `static void test_format_deterministic_and_only_nonempty_stages(void **state)` |
| `test_format_null_or_zero_cap` | function | `tests/test_perf_trace.c:151` | `static void test_format_null_or_zero_cap(void **state)` |
| `test_format_truncates_never_overflows` | function | `tests/test_perf_trace.c:137` | `static void test_format_truncates_never_overflows(void **state)` |
| `test_min_max_median` | function | `tests/test_perf_trace.c:41` | `static void test_min_max_median(void **state)` |
| `test_null_safe` | function | `tests/test_perf_trace.c:162` | `static void test_null_safe(void **state)` |
| `test_ring_wraparound_fifo` | function | `tests/test_perf_trace.c:54` | `static void test_ring_wraparound_fifo(void **state)` |
| `test_single_record` | function | `tests/test_perf_trace.c:27` | `static void test_single_record(void **state)` |
| `test_stage_name` | function | `tests/test_perf_trace.c:100` | `static void test_stage_name(void **state)` |
| `test_stage_out_of_range_is_noop` | function | `tests/test_perf_trace.c:71` | `static void test_stage_out_of_range_is_noop(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_prefetch.c:4` | `#define _POSIX_C_SOURCE` |
| `assert_int_equal` | function | `tests/test_prefetch.c:25` | `assert_int_equal(pf_scan(NULL, 3, &l), -1);` |
| `assert_int_not_equal` | function | `tests/test_prefetch.c:213` | `assert_int_not_equal(rc, 0);` |
| `assert_non_null` | function | `tests/test_prefetch.c:107` | `assert_non_null(html);` |
| `assert_null` | function | `tests/test_prefetch.c:214` | `assert_null(b);` |
| `assert_string_equal` | function | `tests/test_prefetch.c:43` | `assert_string_equal(l.refs[0].url, "news.css");` |
| `assert_true` | function | `tests/test_prefetch.c:111` | `assert_true(r > 0 && (size_t)r < 64);` |
| `barrier` | type_alias | `tests/test_prefetch.c:126` | `typedef struct fake_ctx { pthread_barrier_t barrier;` |
| `cmocka_run_group_tests` | function | `tests/test_prefetch.c:302` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `fake_ctx` | struct | `tests/test_prefetch.c:126` | `` |
| `fake_fetch` | function | `tests/test_prefetch.c:134` | `static int fake_fetch(void *vctx, const char *method, const char *url,
                      cons...` |
| `free` | function | `tests/test_prefetch.c:118` | `free(html);` |
| `main` | function | `tests/test_prefetch.c:288` | `int main(void)` |
| `memset` | function | `tests/test_prefetch.c:157` | `memset(&c, 0, sizeof c);` |
| `pf_list_free` | function | `tests/test_prefetch.c:29` | `pf_list_free(&l);` |
| `pf_pool_finish` | function | `tests/test_prefetch.c:179` | `pf_pool_finish(&p);` |
| `pthread_barrier_destroy` | function | `tests/test_prefetch.c:181` | `pthread_barrier_destroy(&c.barrier);` |
| `pthread_barrier_init` | function | `tests/test_prefetch.c:159` | `pthread_barrier_init(&c.barrier, NULL, PF_MAX_THREADS);` |
| `pthread_mutex_destroy` | function | `tests/test_prefetch.c:182` | `pthread_mutex_destroy(&c.lock);` |
| `pthread_mutex_init` | function | `tests/test_prefetch.c:158` | `pthread_mutex_init(&c.lock, NULL);` |
| `pthread_mutex_lock` | function | `tests/test_prefetch.c:141` | `pthread_mutex_lock(&c->lock);` |
| `pthread_mutex_unlock` | function | `tests/test_prefetch.c:143` | `pthread_mutex_unlock(&c->lock);` |
| `test_pool_finish_unconsumed_and_empty` | function | `tests/test_prefetch.c:228` | `static void test_pool_finish_unconsumed_and_empty(void **state)` |
| `test_pool_miss_consume_and_failure` | function | `tests/test_prefetch.c:184` | `static void test_pool_miss_consume_and_failure(void **state)` |
| `test_pool_parallel_fetch_and_take` | function | `tests/test_prefetch.c:152` | `static void test_pool_parallel_fetch_and_take(void **state)` |
| `test_pooled_fetch_adapter` | function | `tests/test_prefetch.c:249` | `static void test_pooled_fetch_adapter(void **state)` |
| `test_scan_basic_stylesheet_and_script` | function | `tests/test_prefetch.c:31` | `static void test_scan_basic_stylesheet_and_script(void **state)` |
| `test_scan_null_args` | function | `tests/test_prefetch.c:21` | `static void test_scan_null_args(void **state)` |
| `test_scan_ref_cap` | function | `tests/test_prefetch.c:104` | `static void test_scan_ref_cap(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_prefs.c:8` | `#define _POSIX_C_SOURCE` |
| `assert_int_equal` | function | `tests/test_prefs.c:29` | `assert_int_equal(p.theme_mode, 0);` |
| `assert_non_null` | function | `tests/test_prefs.c:77` | `assert_non_null(text);` |
| `assert_null` | function | `tests/test_prefs.c:360` | `assert_null(strstr(html, "<script>"));` |
| `assert_string_equal` | function | `tests/test_prefs.c:95` | `assert_string_equal(q.bookmarks[0].url, "https://example.com/a");` |
| `assert_true` | function | `tests/test_prefs.c:229` | `assert_true(klen <= PREFS_MAX_TITLE);` |
| `cmocka_run_group_tests` | function | `tests/test_prefs.c:410` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `free` | function | `tests/test_prefs.c:102` | `free(text);` |
| `main` | function | `tests/test_prefs.c:393` | `int main(void)` |
| `memset` | function | `tests/test_prefs.c:194` | `memset(big, 'a', sizeof big - 1);` |
| `prefs_free` | function | `tests/test_prefs.c:42` | `prefs_free(&p);` |
| `prefs_init` | function | `tests/test_prefs.c:28` | `prefs_init(&p);` |
| `snprintf` | function | `tests/test_prefs.c:254` | `snprintf(url, sizeof url, "https://cap.test/%zu", i);` |
| `test_bookmark_toggle_and_cap` | function | `tests/test_prefs.c:236` | `static void test_bookmark_toggle_and_cap(void **state)` |
| `test_bookmarks_page_escapes` | function | `tests/test_prefs.c:344` | `static void test_bookmarks_page_escapes(void **state)` |
| `test_format_null_args` | function | `tests/test_prefs.c:381` | `static void test_format_null_args(void **state)` |
| `test_history_dedup_and_evict` | function | `tests/test_prefs.c:264` | `static void test_history_dedup_and_evict(void **state)` |
| `test_hostile_title_cleaned` | function | `tests/test_prefs.c:206` | `static void test_hostile_title_cleaned(void **state)` |
| `test_init_defaults` | function | `tests/test_prefs.c:24` | `static void test_init_defaults(void **state)` |
| `test_invalid_urls_rejected` | function | `tests/test_prefs.c:178` | `static void test_invalid_urls_rejected(void **state)` |
| `test_parse_bad_magic` | function | `tests/test_prefs.c:109` | `static void test_parse_bad_magic(void **state)` |
| `test_parse_clamps_out_of_range` | function | `tests/test_prefs.c:156` | `static void test_parse_clamps_out_of_range(void **state)` |
| `test_parse_too_large` | function | `tests/test_prefs.c:125` | `static void test_parse_too_large(void **state)` |
| `test_parse_unknown_and_malformed_skipped` | function | `tests/test_prefs.c:134` | `static void test_parse_unknown_and_malformed_skipped(void **state)` |
| `test_roundtrip` | function | `tests/test_prefs.c:49` | `static void test_roundtrip(void **state)` |
| `test_suggest_priorities` | function | `tests/test_prefs.c:289` | `static void test_suggest_priorities(void **state)` |
| `_GNU_SOURCE` | macro | `tests/test_profile.c:8` | `#define _GNU_SOURCE` |
| `assert_false` | function | `tests/test_profile.c:84` | `assert_false(ctx.ready);` |
| `assert_int_equal` | function | `tests/test_profile.c:75` | `assert_int_equal(profile_open(&ctx, f->dir), PROFILE_OK);` |
| `assert_non_null` | function | `tests/test_profile.c:189` | `assert_non_null(fp);` |
| `assert_null` | function | `tests/test_profile.c:194` | `assert_null(memmem(blob, blen, secret_url, strlen(secret_url)));` |
| `assert_string_equal` | function | `tests/test_profile.c:155` | `assert_string_equal(q.bookmarks[0].url, "https://example.com/");` |
| `assert_true` | function | `tests/test_profile.c:76` | `assert_true(ctx.ready);` |
| `close` | function | `tests/test_profile.c:96` | `close(fd);` |
| `closedir` | function | `tests/test_profile.c:52` | `closedir(d);` |
| `cmocka_run_group_tests` | function | `tests/test_profile.c:290` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `dir` | type_alias | `tests/test_profile.c:27` | `typedef struct fixture { char dir[64];` |
| `fclose` | function | `tests/test_profile.c:192` | `fclose(fp);` |
| `file_size` | function | `tests/test_profile.c:63` | `static size_t file_size(const char *path)` |
| `fixture` | struct | `tests/test_profile.c:28` | `` |
| `free` | function | `tests/test_profile.c:55` | `free(f);` |
| `main` | function | `tests/test_profile.c:277` | `int main(void)` |
| `memset` | function | `tests/test_profile.c:266` | `memset(&ctx, 0, sizeof ctx);` |
| `path_of` | function | `tests/test_profile.c:59` | `static void path_of(const fixture *f, const char *name, char *out, size_t cap)` |
| `prefs_free` | function | `tests/test_profile.c:124` | `prefs_free(&p);` |
| `prefs_init` | function | `tests/test_profile.c:120` | `prefs_init(&p);` |
| `profile_close` | function | `tests/test_profile.c:83` | `profile_close(&ctx);` |
| `rmdir` | function | `tests/test_profile.c:54` | `rmdir(f->dir);` |
| `setup` | function | `tests/test_profile.c:29` | `static int setup(void **state)` |
| `snprintf` | function | `tests/test_profile.c:49` | `snprintf(p, sizeof p, "%s/%s", f->dir, e->d_name);` |
| `strcpy` | function | `tests/test_profile.c:33` | `strcpy(f->dir, "/tmp/freedom_prof_XXXXXX");` |
| `teardown` | function | `tests/test_profile.c:38` | `static int teardown(void **state)` |
| `test_first_launch_defaults` | function | `tests/test_profile.c:114` | `static void test_first_launch_defaults(void **state)` |
| `test_foreign_key_auth_fails` | function | `tests/test_profile.c:235` | `static void test_foreign_key_auth_fails(void **state)` |
| `test_nothing_readable_on_disk` | function | `tests/test_profile.c:173` | `static void test_nothing_readable_on_disk(void **state)` |
| `test_null_and_not_ready` | function | `tests/test_profile.c:260` | `static void test_null_and_not_ready(void **state)` |
| `test_open_bad_dir` | function | `tests/test_profile.c:102` | `static void test_open_bad_dir(void **state)` |
| `test_open_creates_keyfile` | function | `tests/test_profile.c:71` | `static void test_open_creates_keyfile(void **state)` |
| `test_open_rejects_corrupt_keyfile` | function | `tests/test_profile.c:88` | `static void test_open_rejects_corrupt_keyfile(void **state)` |
| `test_save_load_roundtrip_two_ctx` | function | `tests/test_profile.c:127` | `static void test_save_load_roundtrip_two_ctx(void **state)` |
| `test_tampered_blob_auth_fails` | function | `tests/test_profile.c:203` | `static void test_tampered_blob_auth_fails(void **state)` |
| `unlink` | function | `tests/test_profile.c:50` | `unlink(p);` |
| `assert_int_equal` | function | `tests/test_render_doc.c:47` | `assert_int_equal(rd_build(v, rdp_caps_safe(), TOP, NULL), RD_ERR_NULL_ARG);` |
| `assert_non_null` | function | `tests/test_render_doc.c:55` | `assert_non_null(d);` |
| `assert_null` | function | `tests/test_render_doc.c:58` | `assert_null(rd_at(d, 0));` |
| `assert_string_equal` | function | `tests/test_render_doc.c:78` | `assert_string_equal(h->text, "Title");` |
| `assert_true` | function | `tests/test_render_doc.c:344` | `assert_true(strlen(rd_kind_name(all[i])) > 0);` |
| `caps_images_on` | function | `tests/test_render_doc.c:27` | `static rdp_caps caps_images_on(void)` |
| `cmocka_run_group_tests` | function | `tests/test_render_doc.c:851` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `first_kind` | function | `tests/test_render_doc.c:35` | `static const rd_block *first_kind(const rd_doc *d, rd_kind k)` |
| `main` | function | `tests/test_render_doc.c:813` | `int main(void)` |
| `memset` | function | `tests/test_render_doc.c:768` | `memset(&b, 0, sizeof b);` |
| `pv_free` | function | `tests/test_render_doc.c:48` | `pv_free(v);` |
| `pv_set_bgcolor` | function | `tests/test_render_doc.c:377` | `pv_set_bgcolor(v, 0xeeddcc);` |
| `pv_set_color` | function | `tests/test_render_doc.c:376` | `pv_set_color(v, 0x3366cc);` |
| `pv_set_cont_item` | function | `tests/test_render_doc.c:621` | `pv_set_cont_item(v, 7);` |
| `pv_set_container` | function | `tests/test_render_doc.c:588` | `pv_set_container(v, 0, BX_DISPLAY_FLEX, 12, FX_JUSTIFY_CENTER, 0, 0, -1, 0);` |
| `pv_set_emphasis` | function | `tests/test_render_doc.c:99` | `pv_set_emphasis(v, 1, 0);` |
| `pv_set_flex` | function | `tests/test_render_doc.c:690` | `pv_set_flex(v, 300, 0, 120, -2, CSS_FD_COLUMN, 0);` |
| `pv_set_float` | function | `tests/test_render_doc.c:653` | `pv_set_float(v, CSS_FLOAT_LEFT, 3, CSS_CLEAR_BOTH, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0);` |
| `pv_set_node_id` | function | `tests/test_render_doc.c:805` | `pv_set_node_id(v, 42);` |
| `pv_set_text_ext` | function | `tests/test_render_doc.c:411` | `pv_set_text_ext(v, &te);` |
| `pv_text_ext_reset` | function | `tests/test_render_doc.c:407` | `pv_text_ext_reset(&te);` |
| `rd_free` | function | `tests/test_render_doc.c:59` | `rd_free(d);` |
| `test_author_color_gated_by_css` | function | `tests/test_render_doc.c:372` | `static void test_author_color_gated_by_css(void **state)` |
| `test_block_tag_total` | function | `tests/test_render_doc.c:764` | `static void test_block_tag_total(void **state)` |
| `test_build_null_out` | function | `tests/test_render_doc.c:43` | `static void test_build_null_out(void **state)` |
| `test_build_null_view_is_empty` | function | `tests/test_render_doc.c:50` | `static void test_build_null_view_is_empty(void **state)` |
| `test_caret_color_gated_on_input` | function | `tests/test_render_doc.c:506` | `static void test_caret_color_gated_on_input(void **state)` |
| `test_cont_item_carried_by_default` | function | `tests/test_render_doc.c:616` | `static void test_cont_item_carried_by_default(void **state)` |
| `test_container_carried_by_default` | function | `tests/test_render_doc.c:584` | `static void test_container_carried_by_default(void **state)` |
| `test_emphasis_propagates` | function | `tests/test_render_doc.c:94` | `static void test_emphasis_propagates(void **state)` |
| `test_flex_item_carried_by_default` | function | `tests/test_render_doc.c:684` | `static void test_flex_item_carried_by_default(void **state)` |
| `test_flex_wrap_align_row_gap_carried_by_default` | function | `tests/test_render_doc.c:733` | `static void test_flex_wrap_align_row_gap_carried_by_default(void **state)` |
| `test_float_carried_by_default` | function | `tests/test_render_doc.c:649` | `static void test_float_carried_by_default(void **state)` |
| `test_free_null_and_double` | function | `tests/test_render_doc.c:361` | `static void test_free_null_and_double(void **state)` |
| `test_heading_paragraph_link` | function | `tests/test_render_doc.c:63` | `static void test_heading_paragraph_link(void **state)` |
| `test_href_sanitised` | function | `tests/test_render_doc.c:321` | `static void test_href_sanitised(void **state)` |
| `test_image_data_url_allowed_no_top` | function | `tests/test_render_doc.c:278` | `static void test_image_data_url_allowed_no_top(void **state)` |
| `test_image_data_url_allowed_remote_top` | function | `tests/test_render_doc.c:259` | `static void test_image_data_url_allowed_remote_top(void **state)` |
| `test_image_data_url_disabled_by_default` | function | `tests/test_render_doc.c:290` | `static void test_image_data_url_disabled_by_default(void **state)` |
| `test_image_data_url_percent_encoded_blocked_invalid` | function | `tests/test_render_doc.c:306` | `static void test_image_data_url_percent_encoded_blocked_invalid(void **state)` |
| `test_image_label_total` | function | `tests/test_render_doc.c:348` | `static void test_image_label_total(void **state)` |
| `test_image_off_emits_notice_and_blocked` | function | `tests/test_render_doc.c:124` | `static void test_image_off_emits_notice_and_blocked(void **state)` |
| `test_image_on_allows_normal` | function | `tests/test_render_doc.c:163` | `static void test_image_on_allows_normal(void **state)` |
| `test_image_on_blocks_non_https` | function | `tests/test_render_doc.c:224` | `static void test_image_on_blocks_non_https(void **state)` |
| `test_image_on_blocks_tracker` | function | `tests/test_render_doc.c:211` | `static void test_image_on_blocks_tracker(void **state)` |
| `test_image_on_resolves_doc_relative_src` | function | `tests/test_render_doc.c:198` | `static void test_image_on_resolves_doc_relative_src(void **state)` |
| `test_image_on_resolves_relative_src` | function | `tests/test_render_doc.c:182` | `static void test_image_on_resolves_relative_src(void **state)` |
| `test_image_rendering_gated_on_image` | function | `tests/test_render_doc.c:477` | `static void test_image_rendering_gated_on_image(void **state)` |
| `test_input_label_total` | function | `tests/test_render_doc.c:570` | `static void test_input_label_total(void **state)` |
| `test_input_passthrough` | function | `tests/test_render_doc.c:535` | `static void test_input_passthrough(void **state)` |
| `test_kind_name_total` | function | `tests/test_render_doc.c:338` | `static void test_kind_name_total(void **state)` |
| `test_no_images_no_notice` | function | `tests/test_render_doc.c:149` | `static void test_no_images_no_notice(void **state)` |
| `test_node_id_carried_by_default` | function | `tests/test_render_doc.c:801` | `static void test_node_id_carried_by_default(void **state)` |
| `test_text_ext_2026_07_10_batch_gated_by_css` | function | `tests/test_render_doc.c:437` | `static void test_text_ext_2026_07_10_batch_gated_by_css(void **state)` |
| `test_text_overflow_word_break_gated_by_css` | function | `tests/test_render_doc.c:402` | `static void test_text_overflow_word_break_gated_by_css(void **state)` |
| `assert_false` | function | `tests/test_render_policy.c:21` | `assert_false(c.images);` |
| `assert_int_equal` | function | `tests/test_render_policy.c:39` | `assert_int_equal(rdp_is_tracking_pixel(1, 1), 1);` |
| `assert_memory_equal` | function | `tests/test_render_policy.c:32` | `assert_memory_equal(&z, &s, sizeof(rdp_caps));` |
| `assert_non_null` | function | `tests/test_render_policy.c:225` | `assert_non_null(r);` |
| `assert_string_equal` | function | `tests/test_render_policy.c:229` | `assert_string_equal(rdp_img_reason((rdp_img_decision)999), "unknown");` |
| `assert_true` | function | `tests/test_render_policy.c:226` | `assert_true(strlen(r) > 0);` |
| `caps_images_on` | function | `tests/test_render_policy.c:89` | `static rdp_caps caps_images_on(void)` |
| `cmocka_run_group_tests` | function | `tests/test_render_policy.c:262` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `consulted` | function | `tests/test_render_policy.c:76` | `* is not even consulted (a bogus URL still yields BLOCK_DISABLED). */ assert_int_equal( rdp_image_decision(off, "https:/` |
| `main` | function | `tests/test_render_policy.c:240` | `int main(void)` |
| `test_caps_safe_is_all_off` | function | `tests/test_render_policy.c:17` | `static void test_caps_safe_is_all_off(void **state)` |
| `test_caps_zero_value_is_safe` | function | `tests/test_render_policy.c:25` | `static void test_caps_zero_value_is_safe(void **state)` |
| `test_image_allow_cross_site_when_enabled` | function | `tests/test_render_policy.c:107` | `static void test_image_allow_cross_site_when_enabled(void **state)` |
| `test_image_allow_data_url` | function | `tests/test_render_policy.c:164` | `static void test_image_allow_data_url(void **state)` |
| `test_image_allow_same_site` | function | `tests/test_render_policy.c:95` | `static void test_image_allow_same_site(void **state)` |
| `test_image_block_invalid` | function | `tests/test_render_policy.c:141` | `static void test_image_block_invalid(void **state)` |
| `test_image_block_scheme` | function | `tests/test_render_policy.c:133` | `static void test_image_block_scheme(void **state)` |
| `test_image_block_tracker` | function | `tests/test_render_policy.c:118` | `static void test_image_block_tracker(void **state)` |
| `test_image_data_url_disabled_by_default` | function | `tests/test_render_policy.c:182` | `static void test_image_data_url_disabled_by_default(void **state)` |
| `test_image_data_url_malformed_is_invalid` | function | `tests/test_render_policy.c:190` | `static void test_image_data_url_malformed_is_invalid(void **state)` |
| `test_image_disabled_by_default` | function | `tests/test_render_policy.c:71` | `static void test_image_disabled_by_default(void **state)` |
| `test_image_disabled_precedence` | function | `tests/test_render_policy.c:207` | `static void test_image_disabled_precedence(void **state)` |
| `test_images_warning_present` | function | `tests/test_render_policy.c:231` | `static void test_images_warning_present(void **state)` |
| `test_img_reason_total_and_stable` | function | `tests/test_render_policy.c:216` | `static void test_img_reason_total_and_stable(void **state)` |
| `test_tracking_pixel_normal` | function | `tests/test_render_policy.c:51` | `static void test_tracking_pixel_normal(void **state)` |
| `test_tracking_pixel_tiny` | function | `tests/test_render_policy.c:36` | `static void test_tracking_pixel_tiny(void **state)` |
| `test_tracking_pixel_unknown` | function | `tests/test_render_policy.c:61` | `static void test_tracking_pixel_unknown(void **state)` |
| `test_tracking_pixel_zero_area` | function | `tests/test_render_policy.c:44` | `static void test_tracking_pixel_zero_area(void **state)` |
| `assert_int_equal` | function | `tests/test_renderer.c:30` | `assert_int_equal(rd_render_html(HTML, sizeof HTML - 1, &r), RD_OK);` |
| `assert_non_null` | function | `tests/test_renderer.c:31` | `assert_non_null(r.title);` |
| `assert_null` | function | `tests/test_renderer.c:44` | `assert_null(strstr(r.text, "steal_cookies"));` |
| `assert_string_equal` | function | `tests/test_renderer.c:32` | `assert_string_equal(r.title, "Isolated");` |
| `assert_true` | function | `tests/test_renderer.c:69` | `assert_true(s == RD_OK \|\| s == RD_ERR_RENDER);` |
| `cmocka_run_group_tests` | function | `tests/test_renderer.c:103` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_renderer.c:92` | `int main(void)` |
| `rd_result_free` | function | `tests/test_renderer.c:36` | `rd_result_free(&r);` |
| `test_render_basic` | function | `tests/test_renderer.c:26` | `static void test_render_basic(void **state)` |
| `test_render_binary_does_not_crash_parent` | function | `tests/test_renderer.c:63` | `static void test_render_binary_does_not_crash_parent(void **state)` |
| `test_render_multiple_independent` | function | `tests/test_renderer.c:74` | `static void test_render_multiple_independent(void **state)` |
| `test_render_null_args` | function | `tests/test_renderer.c:47` | `static void test_render_null_args(void **state)` |
| `test_render_strips_script` | function | `tests/test_renderer.c:38` | `static void test_render_strips_script(void **state)` |
| `test_render_too_large` | function | `tests/test_renderer.c:54` | `static void test_render_too_large(void **state)` |
| `test_result_free_null_and_double` | function | `tests/test_renderer.c:83` | `static void test_result_free_null_and_double(void **state)` |
| `assert_int_equal` | function | `tests/test_request_policy.c:21` | `assert_int_equal(rp_host_of("https://example.com/path", h, sizeof h), 0);` |
| `assert_string_equal` | function | `tests/test_request_policy.c:22` | `assert_string_equal(h, "example.com");` |
| `cmocka_run_group_tests` | function | `tests/test_request_policy.c:153` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_request_policy.c:138` | `int main(void)` |
| `test_evaluate_allow_same_site` | function | `tests/test_request_policy.c:104` | `static void test_evaluate_allow_same_site(void **state)` |
| `test_evaluate_block_invalid` | function | `tests/test_request_policy.c:127` | `static void test_evaluate_block_invalid(void **state)` |
| `test_evaluate_block_scheme` | function | `tests/test_request_policy.c:119` | `static void test_evaluate_block_scheme(void **state)` |
| `test_evaluate_block_third_party` | function | `tests/test_request_policy.c:111` | `static void test_evaluate_block_third_party(void **state)` |
| `test_host_of_basic` | function | `tests/test_request_policy.c:17` | `static void test_host_of_basic(void **state)` |
| `test_host_of_invalid` | function | `tests/test_request_policy.c:28` | `static void test_host_of_invalid(void **state)` |
| `test_host_of_overflow` | function | `tests/test_request_policy.c:36` | `static void test_host_of_overflow(void **state)` |
| `test_same_site` | function | `tests/test_request_policy.c:90` | `static void test_same_site(void **state)` |
| `test_site_of` | function | `tests/test_request_policy.c:44` | `static void test_site_of(void **state)` |
| `test_site_of_multi_suffix` | function | `tests/test_request_policy.c:57` | `static void test_site_of_multi_suffix(void **state)` |
| `test_site_of_psl` | function | `tests/test_request_policy.c:70` | `static void test_site_of_psl(void **state)` |
| `assert_false` | function | `tests/test_secure_fetch.c:296` | `assert_false(sf_is_redirect_code(200));` |
| `assert_int_equal` | function | `tests/test_secure_fetch.c:26` | `assert_int_equal(c.policy, SF_POLICY_PQ_HYBRID_KE);` |
| `assert_non_null` | function | `tests/test_secure_fetch.c:29` | `assert_non_null(c.kex_groups);` |
| `assert_null` | function | `tests/test_secure_fetch.c:31` | `assert_null(c.user_agent);` |
| `assert_string_equal` | function | `tests/test_secure_fetch.c:30` | `assert_string_equal(c.kex_groups, SF_DEFAULT_KEX_GROUPS);` |
| `assert_true` | function | `tests/test_secure_fetch.c:287` | `assert_true(sf_is_redirect_code(301));` |
| `cmocka_run_group_tests` | function | `tests/test_secure_fetch.c:584` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_secure_fetch.c:531` | `int main(void)` |
| `memcpy` | function | `tests/test_secure_fetch.c:431` | `memcpy(r.location, u, n);` |
| `memset` | function | `tests/test_secure_fetch.c:416` | `memset(&r, 0, sizeof r);` |
| `sf_cookie_header_for` | function | `tests/test_secure_fetch.c:528` | `sf_cookie_header_for("https://example.com/", buf2, sizeof buf2);` |
| `sf_cookie_put` | function | `tests/test_secure_fetch.c:519` | `sf_cookie_put("https://www.google.com/", "SOCS=xyz123");` |
| `sf_global_init` | function | `tests/test_secure_fetch.c:518` | `sf_global_init();` |
| `sf_response_free` | function | `tests/test_secure_fetch.c:417` | `sf_response_free(&r);` |
| `test_chain_hybrid_allows_classical` | function | `tests/test_secure_fetch.c:148` | `static void test_chain_hybrid_allows_classical(void **state)` |
| `test_chain_permissive_allows_weak_certs` | function | `tests/test_secure_fetch.c:165` | `static void test_chain_permissive_allows_weak_certs(void **state)` |
| `test_chain_rejects_null` | function | `tests/test_secure_fetch.c:186` | `static void test_chain_rejects_null(void **state)` |
| `test_chain_rejects_sha1_in_any_policy` | function | `tests/test_secure_fetch.c:156` | `static void test_chain_rejects_sha1_in_any_policy(void **state)` |
| `test_chain_rejects_weak_rsa` | function | `tests/test_secure_fetch.c:178` | `static void test_chain_rejects_weak_rsa(void **state)` |
| `test_chain_strict_accepts_pq` | function | `tests/test_secure_fetch.c:140` | `static void test_chain_strict_accepts_pq(void **state)` |
| `test_chain_strict_rejects_classical` | function | `tests/test_secure_fetch.c:131` | `static void test_chain_strict_rejects_classical(void **state)` |
| `test_config_blend_fields_default_null` | function | `tests/test_secure_fetch.c:33` | `static void test_config_blend_fields_default_null(void **state)` |
| `test_cookie_jar_put_and_header` | function | `tests/test_secure_fetch.c:515` | `static void test_cookie_jar_put_and_header(void **state)` |
| `test_cookie_line_matches_pure` | function | `tests/test_secure_fetch.c:479` | `static void test_cookie_line_matches_pure(void **state)` |
| `test_enforce_all_good_hybrid` | function | `tests/test_secure_fetch.c:200` | `static void test_enforce_all_good_hybrid(void **state)` |
| `test_enforce_allow_classical_ke` | function | `tests/test_secure_fetch.c:243` | `static void test_enforce_allow_classical_ke(void **state)` |
| `test_enforce_allowlisted_insecure` | function | `tests/test_secure_fetch.c:263` | `static void test_enforce_allowlisted_insecure(void **state)` |
| `test_enforce_checks_group_after_version` | function | `tests/test_secure_fetch.c:215` | `static void test_enforce_checks_group_after_version(void **state)` |
| `test_enforce_checks_version_first` | function | `tests/test_secure_fetch.c:206` | `static void test_enforce_checks_version_first(void **state)` |
| `test_enforce_fails_closed_on_null_chain` | function | `tests/test_secure_fetch.c:223` | `static void test_enforce_fails_closed_on_null_chain(void **state)` |
| `test_enforce_strict_requires_pq_chain` | function | `tests/test_secure_fetch.c:230` | `static void test_enforce_strict_requires_pq_chain(void **state)` |
| `test_get_follow_null_args` | function | `tests/test_secure_fetch.c:435` | `static void test_get_follow_null_args(void **state)` |
| `test_get_null_args` | function | `tests/test_secure_fetch.c:444` | `static void test_get_null_args(void **state)` |
| `test_group_accepts_hybrid` | function | `tests/test_secure_fetch.c:122` | `static void test_group_accepts_hybrid(void **state)` |
| `test_group_rejects_classical` | function | `tests/test_secure_fetch.c:108` | `static void test_group_rejects_classical(void **state)` |
| `test_group_rejects_pure_pq` | function | `tests/test_secure_fetch.c:115` | `static void test_group_rejects_pure_pq(void **state)` |
| `test_location_is_case_insensitive_and_trims` | function | `tests/test_secure_fetch.c:312` | `static void test_location_is_case_insensitive_and_trims(void **state)` |
| `test_location_parses_value` | function | `tests/test_secure_fetch.c:304` | `static void test_location_parses_value(void **state)` |
| `test_location_rejects_non_location_and_empty` | function | `tests/test_secure_fetch.c:322` | `static void test_location_rejects_non_location_and_empty(void **state)` |
| `test_location_rejects_overflow` | function | `tests/test_secure_fetch.c:334` | `static void test_location_rejects_overflow(void **state)` |
| `test_post_null_args` | function | `tests/test_secure_fetch.c:453` | `static void test_post_null_args(void **state)` |
| `test_redirect_code_recognizes_3xx` | function | `tests/test_secure_fetch.c:284` | `static void test_redirect_code_recognizes_3xx(void **state)` |
| `test_redirect_code_rejects_others` | function | `tests/test_secure_fetch.c:293` | `static void test_redirect_code_rejects_others(void **state)` |
| `test_resolve_absolute_https` | function | `tests/test_secure_fetch.c:343` | `static void test_resolve_absolute_https(void **state)` |
| `test_resolve_absolute_path` | function | `tests/test_secure_fetch.c:377` | `static void test_resolve_absolute_path(void **state)` |
| `test_resolve_null_args` | function | `tests/test_secure_fetch.c:401` | `static void test_resolve_null_args(void **state)` |
| `test_resolve_refuses_dangerous_schemes` | function | `tests/test_secure_fetch.c:358` | `static void test_resolve_refuses_dangerous_schemes(void **state)` |
| `test_resolve_refuses_http_downgrade` | function | `tests/test_secure_fetch.c:351` | `static void test_resolve_refuses_http_downgrade(void **state)` |
| `test_resolve_relative_path` | function | `tests/test_secure_fetch.c:389` | `static void test_resolve_relative_path(void **state)` |
| `test_resolve_scheme_relative` | function | `tests/test_secure_fetch.c:369` | `static void test_resolve_scheme_relative(void **state)` |
| `test_response_free_on_zeroed` | function | `tests/test_secure_fetch.c:412` | `static void test_response_free_on_zeroed(void **state)` |
| `test_response_free_releases_location` | function | `tests/test_secure_fetch.c:421` | `static void test_response_free_releases_location(void **state)` |
| `test_tls_accepts_13` | function | `tests/test_secure_fetch.c:101` | `static void test_tls_accepts_13(void **state)` |
| `test_tls_rejects_12` | function | `tests/test_secure_fetch.c:87` | `static void test_tls_rejects_12(void **state)` |
| `test_tls_rejects_older_and_garbage` | function | `tests/test_secure_fetch.c:92` | `static void test_tls_rejects_older_and_garbage(void **state)` |
| `test_url_accepts_https` | function | `tests/test_secure_fetch.c:79` | `static void test_url_accepts_https(void **state)` |
| `test_url_rejects_dangerous_schemes` | function | `tests/test_secure_fetch.c:69` | `static void test_url_rejects_dangerous_schemes(void **state)` |
| `test_url_rejects_null` | function | `tests/test_secure_fetch.c:59` | `static void test_url_rejects_null(void **state)` |
| `test_url_rejects_plain_http` | function | `tests/test_secure_fetch.c:64` | `static void test_url_rejects_plain_http(void **state)` |
| `test_user_agent_default_when_unset` | function | `tests/test_secure_fetch.c:45` | `static void test_user_agent_default_when_unset(void **state)` |
| `test_user_agent_uses_override` | function | `tests/test_secure_fetch.c:51` | `static void test_user_agent_uses_override(void **state)` |
| `assert_int_equal` | function | `tests/test_svg_render.c:33` | `assert_int_equal(sv_parse(NULL, 5, im), SV_ERR_NULL_ARG);` |
| `assert_non_null` | function | `tests/test_svg_render.c:22` | `assert_non_null(im);` |
| `assert_string_equal` | function | `tests/test_svg_render.c:299` | `assert_string_equal(im->shapes[0].text, "Hi there");` |
| `assert_true` | function | `tests/test_svg_render.c:56` | `assert_true(fabs(im->width - 64.0) < 0.01);` |
| `cmocka_run_group_tests` | function | `tests/test_svg_render.c:345` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `free` | function | `tests/test_svg_render.c:35` | `free(im);` |
| `main` | function | `tests/test_svg_render.c:327` | `int main(void)` |
| `memset` | function | `tests/test_svg_render.c:261` | `memset(big, 'a', SV_MAX_INPUT + 8);` |
| `parse` | function | `tests/test_svg_render.c:25` | `static sv_status parse(sv_image *im, const char *s)` |
| `snprintf` | function | `tests/test_svg_render.c:243` | `snprintf(buf + o, cap - o, "</svg>");` |
| `sv_fit` | function | `tests/test_svg_render.c:311` | `sv_fit(im, 48.0, 48.0, &sc, &ox, &oy);` |
| `sv_parse` | function | `tests/test_svg_render.c:27` | `return sv_parse(s, strlen(s), im);` |
| `test_basic_shapes` | function | `tests/test_svg_render.c:70` | `static void test_basic_shapes(void **state)` |
| `test_bounds_are_enforced` | function | `tests/test_svg_render.c:232` | `static void test_bounds_are_enforced(void **state)` |
| `test_dimensions_and_viewbox` | function | `tests/test_svg_render.c:50` | `static void test_dimensions_and_viewbox(void **state)` |
| `test_empty_and_garbage_do_not_parse` | function | `tests/test_svg_render.c:37` | `static void test_empty_and_garbage_do_not_parse(void **state)` |
| `test_fit_uniform_and_centered` | function | `tests/test_svg_render.c:304` | `static void test_fit_uniform_and_centered(void **state)` |
| `test_group_inheritance_and_transform` | function | `tests/test_svg_render.c:118` | `static void test_group_inheritance_and_transform(void **state)` |
| `test_malformed_values_degrade` | function | `tests/test_svg_render.c:269` | `static void test_malformed_values_degrade(void **state)` |
| `test_null_args` | function | `tests/test_svg_render.c:29` | `static void test_null_args(void **state)` |
| `test_paint_attributes` | function | `tests/test_svg_render.c:96` | `static void test_paint_attributes(void **state)` |
| `test_path_arc_reaches_endpoint` | function | `tests/test_svg_render.c:192` | `static void test_path_arc_reaches_endpoint(void **state)` |
| `test_path_commands` | function | `tests/test_svg_render.c:159` | `static void test_path_commands(void **state)` |
| `test_polygon_points` | function | `tests/test_svg_render.c:139` | `static void test_polygon_points(void **state)` |
| `test_text_element` | function | `tests/test_svg_render.c:287` | `static void test_text_element(void **state)` |
| `test_url_bearing_elements_are_dropped` | function | `tests/test_svg_render.c:208` | `static void test_url_bearing_elements_are_dropped(void **state)` |
| `CSS_PAGE` | macro | `tests/test_tab.c:1686` | `#define CSS_PAGE(HREF)` |
| `EXT_PAGE` | macro | `tests/test_tab.c:1559` | `#define EXT_PAGE(SRC)` |
| `XHR_PAGE` | macro | `tests/test_tab.c:1469` | `#define XHR_PAGE(URL)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_tab.c:13` | `#define _POSIX_C_SOURCE` |
| `assert_false` | function | `tests/test_tab.c:388` | `assert_false(blank);` |
| `assert_int_equal` | function | `tests/test_tab.c:64` | `assert_int_equal(tab_eval(t, js, strlen(js), &r), TAB_OK);` |
| `assert_int_not_equal` | function | `tests/test_tab.c:394` | `assert_int_not_equal(item_second, item_lead);` |
| `assert_non_null` | function | `tests/test_tab.c:66` | `assert_non_null(r.value);` |
| `assert_null` | function | `tests/test_tab.c:900` | `assert_null(strstr(p.text, "steal_cookies"));` |
| `assert_string_equal` | function | `tests/test_tab.c:67` | `assert_string_equal(r.value, expected);` |
| `assert_true` | function | `tests/test_tab.c:78` | `assert_true(tab_alive(t));` |
| `cmocka_run_group_tests` | function | `tests/test_tab.c:2374` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `console_find` | function | `tests/test_tab.c:1118` | `static const fb_entry *console_find(const fb_buffer *log, int level, const char *needle)` |
| `expect_eval` | function | `tests/test_tab.c:62` | `static void expect_eval(tab *t, const char *js, const char *expected)` |
| `fixture` | struct | `tests/test_tab.c:39` | `` |
| `free` | function | `tests/test_tab.c:56` | `free(f);` |
| `main` | function | `tests/test_tab.c:2285` | `int main(int argc, char **argv)` |
| `nanosleep` | function | `tests/test_tab.c:1934` | `nanosleep(&ts, NULL);` |
| `read` | function | `tests/test_tab.c:1827` | `* vector no page may read (Zero Knowledge). Google's real JS hit exactly this. */
static void tes...` |
| `setup_loaded` | function | `tests/test_tab.c:40` | `static int setup_loaded(void **state)` |
| `stub_css_fetch` | function | `tests/test_tab.c:1670` | `static int stub_css_fetch(void *ctx, const char *method, const char *url,
                       ...` |
| `stub_fetch` | function | `tests/test_tab.c:1458` | `static int stub_fetch(void *ctx, const char *method, const char *url,
                      const...` |
| `stub_script_fetch` | function | `tests/test_tab.c:1536` | `static int stub_script_fetch(void *ctx, const char *method, const char *url,
                    ...` |
| `tab_close` | function | `tests/test_tab.c:55` | `tab_close(f->t);` |
| `tab_eval_result_free` | function | `tests/test_tab.c:68` | `tab_eval_result_free(&r);` |
| `tab_image_free` | function | `tests/test_tab.c:1997` | `tab_image_free(&img);` |
| `tab_page_free` | function | `tests/test_tab.c:47` | `tab_page_free(&p);` |
| `tab_set_cookies` | function | `tests/test_tab.c:1026` | `tab_set_cookies(t, "sid=abc");` |
| `tab_set_css_allowed` | function | `tests/test_tab.c:1708` | `tab_set_css_allowed(t, 1);` |
| `tab_set_fetcher` | function | `tests/test_tab.c:1481` | `tab_set_fetcher(t, stub_fetch, NULL);` |
| `tab_set_net_allowed` | function | `tests/test_tab.c:999` | `tab_set_net_allowed(t, 1);` |
| `tab_worker_dispatch` | function | `tests/test_tab.c:2289` | `tab_worker_dispatch(argc, argv);` |
| `teardown` | function | `tests/test_tab.c:51` | `static int teardown(void **state)` |
| `test_binary_does_not_crash_parent` | function | `tests/test_tab.c:1904` | `static void test_binary_does_not_crash_parent(void **state)` |
| `test_child_death_survived` | function | `tests/test_tab.c:1919` | `static void test_child_death_survived(void **state)` |
| `test_click_runs_handler_and_returns_view` | function | `tests/test_tab.c:472` | `static void test_click_runs_handler_and_returns_view(void **state)` |
| `test_decode_image_data_url_in_sandbox` | function | `tests/test_tab.c:2035` | `static void test_decode_image_data_url_in_sandbox(void **state)` |
| `test_decode_image_data_url_null_args` | function | `tests/test_tab.c:2077` | `static void test_decode_image_data_url_null_args(void **state)` |
| `test_decode_image_in_sandbox` | function | `tests/test_tab.c:1979` | `static void test_decode_image_in_sandbox(void **state)` |
| `test_decode_image_null_args` | function | `tests/test_tab.c:2016` | `static void test_decode_image_null_args(void **state)` |
| `test_decode_image_rejects_junk` | function | `tests/test_tab.c:2001` | `static void test_decode_image_rejects_junk(void **state)` |
| `test_eval_captures_console_output` | function | `tests/test_tab.c:1275` | `static void test_eval_captures_console_output(void **state)` |
| `test_eval_exception` | function | `tests/test_tab.c:1847` | `static void test_eval_exception(void **state)` |
| `test_eval_no_network_or_cross_origin_api` | function | `tests/test_tab.c:1439` | `static void test_eval_no_network_or_cross_origin_api(void **state)` |
| `test_eval_persistent_state` | function | `tests/test_tab.c:1859` | `static void test_eval_persistent_state(void **state)` |
| `test_eval_sees_dom` | function | `tests/test_tab.c:1411` | `static void test_eval_sees_dom(void **state)` |
| `test_eval_sees_env` | function | `tests/test_tab.c:1421` | `static void test_eval_sees_env(void **state)` |
| `test_eval_without_load` | function | `tests/test_tab.c:1892` | `static void test_eval_without_load(void **state)` |
| `test_event_ipc_via_tab_eval` | function | `tests/test_tab.c:510` | `static void test_event_ipc_via_tab_eval(void **state)` |
| `test_external_css_applied_when_allowed` | function | `tests/test_tab.c:1703` | `static void test_external_css_applied_when_allowed(void **state)` |
| `test_external_css_bad_ctype_not_parsed` | function | `tests/test_tab.c:1742` | `static void test_external_css_bad_ctype_not_parsed(void **state)` |
| `test_external_css_blocked_host_refused` | function | `tests/test_tab.c:1760` | `static void test_external_css_blocked_host_refused(void **state)` |
| `test_external_css_skipped_without_grant` | function | `tests/test_tab.c:1723` | `static void test_external_css_skipped_without_grant(void **state)` |
| `test_external_css_survives_click_rederive` | function | `tests/test_tab.c:1778` | `static void test_external_css_survives_click_rederive(void **state)` |
| `test_external_script_bad_ctype_not_executed` | function | `tests/test_tab.c:1630` | `static void test_external_script_bad_ctype_not_executed(void **state)` |
| `test_external_script_blocked_host_refused` | function | `tests/test_tab.c:1647` | `static void test_external_script_blocked_host_refused(void **state)` |
| `test_external_script_document_order` | function | `tests/test_tab.c:1583` | `static void test_external_script_document_order(void **state)` |
| `test_external_script_executes_when_net_allowed` | function | `tests/test_tab.c:1566` | `static void test_external_script_executes_when_net_allowed(void **state)` |
| `test_external_script_skipped_without_net` | function | `tests/test_tab.c:1606` | `static void test_external_script_skipped_without_net(void **state)` |
| `test_focus_ipc_round_trip` | function | `tests/test_tab.c:611` | `static void test_focus_ipc_round_trip(void **state)` |
| `test_free_null_and_double` | function | `tests/test_tab.c:1945` | `static void test_free_null_and_double(void **state)` |
| `test_js_navigation_relative_resolved` | function | `tests/test_tab.c:1340` | `static void test_js_navigation_relative_resolved(void **state)` |
| `test_js_navigation_unsafe_is_blocked` | function | `tests/test_tab.c:1360` | `static void test_js_navigation_unsafe_is_blocked(void **state)` |
| `test_load_basic` | function | `tests/test_tab.c:89` | `static void test_load_basic(void **state)` |
| `test_load_captures_console_and_error` | function | `tests/test_tab.c:1128` | `static void test_load_captures_console_and_error(void **state)` |
| `test_load_carries_author_color` | function | `tests/test_tab.c:165` | `static void test_load_carries_author_color(void **state)` |
| `test_load_carries_box_decoration` | function | `tests/test_tab.c:725` | `static void test_load_carries_box_decoration(void **state)` |
| `test_load_carries_box_tree` | function | `tests/test_tab.c:761` | `static void test_load_carries_box_tree(void **state)` |
| `test_load_carries_flex_item` | function | `tests/test_tab.c:192` | `static void test_load_carries_flex_item(void **state)` |
| `test_load_carries_flex_wrap_align_row_gap` | function | `tests/test_tab.c:236` | `static void test_load_carries_flex_wrap_align_row_gap(void **state)` |
| `test_load_carries_float` | function | `tests/test_tab.c:276` | `static void test_load_carries_float(void **state)` |
| `test_load_carries_input_box_and_clip` | function | `tests/test_tab.c:848` | `static void test_load_carries_input_box_and_clip(void **state)` |
| `test_load_carries_node_id` | function | `tests/test_tab.c:403` | `static void test_load_carries_node_id(void **state)` |
| `test_load_carries_oof_flag` | function | `tests/test_tab.c:437` | `static void test_load_carries_oof_flag(void **state)` |
| `test_load_carries_visibility_overflow_cursor_and_text_wrap` | function | `tests/test_tab.c:319` | `static void test_load_carries_visibility_overflow_cursor_and_text_wrap(void **state)` |
| `test_load_document_fonts_stub` | function | `tests/test_tab.c:1239` | `static void test_load_document_fonts_stub(void **state)` |
| `test_load_element_wrapper_idioms` | function | `tests/test_tab.c:1209` | `static void test_load_element_wrapper_idioms(void **state)` |
| `test_load_error_carries_location` | function | `tests/test_tab.c:1183` | `static void test_load_error_carries_location(void **state)` |
| `test_load_ex_builds_dom_and_fires_onload` | function | `tests/test_tab.c:1039` | `static void test_load_ex_builds_dom_and_fires_onload(void **state)` |
| `test_load_ex_inner_html_renders` | function | `tests/test_tab.c:1067` | `static void test_load_ex_inner_html_renders(void **state)` |
| `test_load_ex_noscript_hidden_with_js` | function | `tests/test_tab.c:940` | `static void test_load_ex_noscript_hidden_with_js(void **state)` |
| `test_load_full_location_is_real` | function | `tests/test_tab.c:1304` | `static void test_load_full_location_is_real(void **state)` |
| `test_load_isolates_script_errors` | function | `tests/test_tab.c:1155` | `static void test_load_isolates_script_errors(void **state)` |
| `test_load_no_session_cookies_when_untrusted` | function | `tests/test_tab.c:1017` | `static void test_load_no_session_cookies_when_untrusted(void **state)` |
| `test_load_null_and_too_large` | function | `tests/test_tab.c:1395` | `static void test_load_null_and_too_large(void **state)` |
| `test_load_returns_image_run` | function | `tests/test_tab.c:134` | `static void test_load_returns_image_run(void **state)` |
| `test_load_returns_view_with_link` | function | `tests/test_tab.c:107` | `static void test_load_returns_view_with_link(void **state)` |
| `test_load_strips_script` | function | `tests/test_tab.c:893` | `static void test_load_strips_script(void **state)` |
| `test_load_view_codec_full_roundtrip` | function | `tests/test_tab.c:2138` | `static void test_load_view_codec_full_roundtrip(void **state)` |
| `test_load_without_js_has_empty_console` | function | `tests/test_tab.c:1259` | `static void test_load_without_js_has_empty_console(void **state)` |
| `test_mouse_ipc_round_trip` | function | `tests/test_tab.c:566` | `static void test_mouse_ipc_round_trip(void **state)` |
| `test_no_js_no_navigation` | function | `tests/test_tab.c:1382` | `static void test_no_js_no_navigation(void **state)` |
| `test_open_close` | function | `tests/test_tab.c:72` | `static void test_open_close(void **state)` |
| `test_open_null` | function | `tests/test_tab.c:82` | `static void test_open_null(void **state)` |
| `test_reload_replaces_page` | function | `tests/test_tab.c:1868` | `static void test_reload_replaces_page(void **state)` |
| `test_subreq_permitted_pure` | function | `tests/test_tab.c:1806` | `static void test_subreq_permitted_pure(void **state)` |
| `test_tick_fires_delayed_timer` | function | `tests/test_tab.c:658` | `static void test_tick_fires_delayed_timer(void **state)` |
| `test_tick_interval_rearms` | function | `tests/test_tab.c:694` | `static void test_tick_interval_rearms(void **state)` |
| `test_worker_args_malformed` | function | `tests/test_tab.c:2106` | `static void test_worker_args_malformed(void **state)` |
| `test_worker_args_not_worker` | function | `tests/test_tab.c:2099` | `static void test_worker_args_not_worker(void **state)` |
| `test_worker_args_null_safe` | function | `tests/test_tab.c:2121` | `static void test_worker_args_null_safe(void **state)` |
| `test_worker_args_valid` | function | `tests/test_tab.c:2090` | `static void test_worker_args_valid(void **state)` |
| `test_xhr_undefined_when_net_not_allowed` | function | `tests/test_tab.c:1497` | `static void test_xhr_undefined_when_net_not_allowed(void **state)` |
| `test_xhr_works_when_net_allowed` | function | `tests/test_tab.c:1477` | `static void test_xhr_works_when_net_allowed(void **state)` |
| `view_find_text` | function | `tests/test_tab.c:1691` | `static const pv_run *view_find_text(const pv_view *v, const char *needle)` |
| `assert_int_equal` | function | `tests/test_text_shape.c:33` | `assert_int_equal(tsh_shape(NULL, 16.0, "x", 1, g, 64, &n, &adv), TSH_ERR_INPUT);` |
| `assert_true` | function | `tests/test_text_shape.c:53` | `assert_true(tsh_measure(NULL, 16.0, "x", 1) < 0.0);` |
| `cairo_destroy` | function | `tests/test_text_shape.c:139` | `cairo_destroy(cr);` |
| `cairo_set_source_rgb` | function | `tests/test_text_shape.c:135` | `cairo_set_source_rgb(cr, 0, 0, 0);` |
| `cairo_surface_destroy` | function | `tests/test_text_shape.c:140` | `cairo_surface_destroy(s);` |
| `cmocka_run_group_tests` | function | `tests/test_text_shape.c:159` | `return cmocka_run_group_tests(tests, NULL, teardown);` |
| `main` | function | `tests/test_text_shape.c:148` | `int main(void)` |
| `teardown` | function | `tests/test_text_shape.c:142` | `static int teardown(void **state)` |
| `test_determinism` | function | `tests/test_text_shape.c:91` | `static void test_determinism(void **state)` |
| `test_draw_paints` | function | `tests/test_text_shape.c:129` | `static void test_draw_paints(void **state)` |
| `test_empty_slice_is_ok` | function | `tests/test_text_shape.c:56` | `static void test_empty_slice_is_ok(void **state)` |
| `test_measure_matches_shape` | function | `tests/test_text_shape.c:107` | `static void test_measure_matches_shape(void **state)` |
| `test_null_and_bad_inputs` | function | `tests/test_text_shape.c:26` | `static void test_null_and_bad_inputs(void **state)` |
| `test_overflow_cap` | function | `tests/test_text_shape.c:119` | `static void test_overflow_cap(void **state)` |
| `test_shape_ascii` | function | `tests/test_text_shape.c:69` | `static void test_shape_ascii(void **state)` |
| `tsh_shutdown` | function | `tests/test_text_shape.c:145` | `tsh_shutdown();` |
| `assert_int_equal` | function | `tests/test_textfield.c:24` | `assert_int_equal(tf_len(&f), 0);` |
| `assert_string_equal` | function | `tests/test_textfield.c:26` | `assert_string_equal(tf_text(&f), "");` |
| `cmocka_run_group_tests` | function | `tests/test_textfield.c:150` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_textfield.c:139` | `int main(void)` |
| `memset` | function | `tests/test_textfield.c:134` | `memset(big, 'z', sizeof big);` |
| `test_backspace_delete` | function | `tests/test_textfield.c:75` | `static void test_backspace_delete(void **state)` |
| `test_full_fails_closed` | function | `tests/test_textfield.c:112` | `static void test_full_fails_closed(void **state)` |
| `test_init_and_accessors` | function | `tests/test_textfield.c:19` | `static void test_init_and_accessors(void **state)` |
| `test_insert_sequence` | function | `tests/test_textfield.c:58` | `static void test_insert_sequence(void **state)` |
| `test_move_saturates` | function | `tests/test_textfield.c:99` | `static void test_move_saturates(void **state)` |
| `test_null_safe` | function | `tests/test_textfield.c:28` | `static void test_null_safe(void **state)` |
| `test_set` | function | `tests/test_textfield.c:45` | `static void test_set(void **state)` |
| `tf_backspace` | function | `tests/test_textfield.c:34` | `tf_backspace(NULL);` |
| `tf_clear` | function | `tests/test_textfield.c:33` | `tf_clear(NULL);` |
| `tf_delete` | function | `tests/test_textfield.c:35` | `tf_delete(NULL);` |
| `tf_end` | function | `tests/test_textfield.c:38` | `tf_end(NULL);` |
| `tf_home` | function | `tests/test_textfield.c:37` | `tf_home(NULL);` |
| `tf_init` | function | `tests/test_textfield.c:23` | `tf_init(&f);` |
| `tf_move` | function | `tests/test_textfield.c:36` | `tf_move(NULL, 3);` |
| `assert_int_equal` | function | `tests/test_tls_impersonate.c:24` | `assert_int_equal(ti_should_impersonate(1, 1, 1), 1);` |
| `assert_memory_equal` | function | `tests/test_tls_impersonate.c:60` | `assert_memory_equal(out.body, in.body, in.body_len);` |
| `assert_non_null` | function | `tests/test_tls_impersonate.c:206` | `assert_non_null(huge);` |
| `assert_null` | function | `tests/test_tls_impersonate.c:137` | `assert_null(out.peer_chain_der);` |
| `assert_string_equal` | function | `tests/test_tls_impersonate.c:56` | `assert_string_equal(out.url, in.url);` |
| `assert_true` | function | `tests/test_tls_impersonate.c:52` | `assert_true(n > 0);` |
| `cmocka_run_group_tests` | function | `tests/test_tls_impersonate.c:231` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `free` | function | `tests/test_tls_impersonate.c:215` | `free(huge);` |
| `main` | function | `tests/test_tls_impersonate.c:217` | `int main(void)` |
| `memset` | function | `tests/test_tls_impersonate.c:207` | `memset(huge, 'a', TI_MAX_URL + 8);` |
| `strncpy` | function | `tests/test_tls_impersonate.c:102` | `strncpy(in.negotiated_group, "x25519", sizeof in.negotiated_group - 1);` |
| `test_decode_rejects_bad_magic` | function | `tests/test_tls_impersonate.c:162` | `static void test_decode_rejects_bad_magic(void **state)` |
| `test_decode_rejects_overlong_field` | function | `tests/test_tls_impersonate.c:176` | `static void test_decode_rejects_overlong_field(void **state)` |
| `test_decode_rejects_truncated` | function | `tests/test_tls_impersonate.c:143` | `static void test_decode_rejects_truncated(void **state)` |
| `test_encode_decode_req_empty_body` | function | `tests/test_tls_impersonate.c:64` | `static void test_encode_decode_req_empty_body(void **state)` |
| `test_encode_decode_req_roundtrip` | function | `tests/test_tls_impersonate.c:38` | `static void test_encode_decode_req_roundtrip(void **state)` |
| `test_encode_decode_resp_roundtrip` | function | `tests/test_tls_impersonate.c:88` | `static void test_encode_decode_resp_roundtrip(void **state)` |
| `test_encode_fails_when_no_room` | function | `tests/test_tls_impersonate.c:191` | `static void test_encode_fails_when_no_room(void **state)` |
| `test_encode_rejects_oversize_url` | function | `tests/test_tls_impersonate.c:202` | `static void test_encode_rejects_oversize_url(void **state)` |
| `test_gate_requires_all_three_signals` | function | `tests/test_tls_impersonate.c:21` | `static void test_gate_requires_all_three_signals(void **state)` |
| `test_resp_no_chain_ok` | function | `tests/test_tls_impersonate.c:120` | `static void test_resp_no_chain_ok(void **state)` |
| `ti_req_free` | function | `tests/test_tls_impersonate.c:62` | `ti_req_free(&out);` |
| `ti_resp_free` | function | `tests/test_tls_impersonate.c:118` | `ti_resp_free(&out);` |
| `assert_int_equal` | function | `tests/test_ui.c:24` | `assert_int_equal((int)lay->lines[n].len, (int)elen);` |
| `assert_line` | function | `tests/test_ui.c:20` | `static void assert_line(const char *text, const ui_layout *lay, size_t n,
                       ...` |
| `assert_memory_equal` | function | `tests/test_ui.c:25` | `assert_memory_equal(text + lay->lines[n].offset, expected, elen);` |
| `assert_true` | function | `tests/test_ui.c:22` | `assert_true(n < lay->count);` |
| `cmocka_run_group_tests` | function | `tests/test_ui.c:143` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_ui.c:129` | `int main(void)` |
| `test_clamp_scroll` | function | `tests/test_ui.c:112` | `static void test_clamp_scroll(void **state)` |
| `test_layout_free_null_and_double` | function | `tests/test_ui.c:120` | `static void test_layout_free_null_and_double(void **state)` |
| `test_wrap_breaks_at_space` | function | `tests/test_ui.c:52` | `static void test_wrap_breaks_at_space(void **state)` |
| `test_wrap_does_not_split_utf8` | function | `tests/test_ui.c:75` | `static void test_wrap_does_not_split_utf8(void **state)` |
| `test_wrap_empty` | function | `tests/test_ui.c:34` | `static void test_wrap_empty(void **state)` |
| `test_wrap_hard_breaks_long_word` | function | `tests/test_ui.c:63` | `static void test_wrap_hard_breaks_long_word(void **state)` |
| `test_wrap_null_args` | function | `tests/test_ui.c:27` | `static void test_wrap_null_args(void **state)` |
| `test_wrap_respects_newline` | function | `tests/test_ui.c:89` | `static void test_wrap_respects_newline(void **state)` |
| `test_wrap_short_single_line` | function | `tests/test_ui.c:42` | `static void test_wrap_short_single_line(void **state)` |
| `test_wrap_zero_cols_is_sanitised` | function | `tests/test_ui.c:100` | `static void test_wrap_zero_cols_is_sanitised(void **state)` |
| `ui_layout_free` | function | `tests/test_ui.c:40` | `ui_layout_free(&lay);` |
| `assert_int_equal` | function | `tests/test_url.c:25` | `assert_int_equal(url_is_https("https://example.com"), 1);` |
| `assert_memory_equal` | function | `tests/test_url.c:448` | `assert_memory_equal(p, expect, len);` |
| `assert_null` | function | `tests/test_url.c:385` | `assert_null(url_file_path("https://example.com"));` |
| `assert_ptr_equal` | function | `tests/test_url.c:547` | `assert_ptr_equal(user, NULL);` |
| `assert_span` | function | `tests/test_url.c:446` | `static void assert_span(const char *p, size_t len, const char *expect)` |
| `assert_string_equal` | function | `tests/test_url.c:100` | `assert_string_equal(out, "/a/b/c");` |
| `assert_true` | function | `tests/test_url.c:64` | `assert_true(url_validate_https(url) != URL_OK);` |
| `free` | function | `tests/test_url.c:523` | `free(user);` |
| `main` | function | `tests/test_url.c:635` | `int main(void)` |
| `memcpy` | function | `tests/test_url.c:53` | `memcpy(url, "https://e.example/", base);` |
| `memset` | function | `tests/test_url.c:54` | `memset(url + base, 'a', 4000 - base);` |
| `test_authority_len` | function | `tests/test_url.c:85` | `static void test_authority_len(void **state)` |
| `test_extract_userinfo_at_authority_start` | function | `tests/test_url.c:585` | `static void test_extract_userinfo_at_authority_start(void **state)` |
| `test_extract_userinfo_basic` | function | `tests/test_url.c:512` | `static void test_extract_userinfo_basic(void **state)` |
| `test_extract_userinfo_empty_password` | function | `tests/test_url.c:611` | `static void test_extract_userinfo_empty_password(void **state)` |
| `test_extract_userinfo_https_subresource_no_auth` | function | `tests/test_url.c:562` | `static void test_extract_userinfo_https_subresource_no_auth(void **state)` |
| `test_extract_userinfo_no_at_sign` | function | `tests/test_url.c:598` | `static void test_extract_userinfo_no_at_sign(void **state)` |
| `test_extract_userinfo_no_userinfo` | function | `tests/test_url.c:538` | `static void test_extract_userinfo_no_userinfo(void **state)` |
| `test_extract_userinfo_non_https_passthrough` | function | `tests/test_url.c:550` | `static void test_extract_userinfo_non_https_passthrough(void **state)` |
| `test_extract_userinfo_nulls` | function | `tests/test_url.c:575` | `static void test_extract_userinfo_nulls(void **state)` |
| `test_extract_userinfo_user_only` | function | `tests/test_url.c:525` | `static void test_extract_userinfo_user_only(void **state)` |
| `test_has_scheme` | function | `tests/test_url.c:68` | `static void test_has_scheme(void **state)` |
| `test_is_file_and_path` | function | `tests/test_url.c:375` | `static void test_is_file_and_path(void **state)` |
| `test_is_https` | function | `tests/test_url.c:22` | `static void test_is_https(void **state)` |
| `test_omnibox_bare_host_gets_https` | function | `tests/test_url.c:247` | `static void test_omnibox_bare_host_gets_https(void **state)` |
| `test_omnibox_foreign_scheme_is_searched_not_executed` | function | `tests/test_url.c:294` | `static void test_omnibox_foreign_scheme_is_searched_not_executed(void **state)` |
| `test_omnibox_http_upgraded_to_https` | function | `tests/test_url.c:264` | `static void test_omnibox_http_upgraded_to_https(void **state)` |
| `test_omnibox_navigate_https` | function | `tests/test_url.c:234` | `static void test_omnibox_navigate_https(void **state)` |
| `test_omnibox_nulls_and_empty` | function | `tests/test_url.c:307` | `static void test_omnibox_nulls_and_empty(void **state)` |
| `test_omnibox_search_for_queries` | function | `tests/test_url.c:274` | `static void test_omnibox_search_for_queries(void **state)` |
| `test_remove_dot_segments` | function | `tests/test_url.c:94` | `static void test_remove_dot_segments(void **state)` |
| `test_remove_dot_segments_nulls` | function | `tests/test_url.c:123` | `static void test_remove_dot_segments_nulls(void **state)` |
| `test_resolve_absolute` | function | `tests/test_url.c:134` | `static void test_resolve_absolute(void **state)` |
| `test_resolve_absolute_path` | function | `tests/test_url.c:165` | `static void test_resolve_absolute_path(void **state)` |
| `test_resolve_dot_segments` | function | `tests/test_url.c:189` | `static void test_resolve_dot_segments(void **state)` |
| `test_resolve_fail_closed_on_bad_base` | function | `tests/test_url.c:206` | `static void test_resolve_fail_closed_on_bad_base(void **state)` |
| `test_resolve_file_confinement_fail_closed` | function | `tests/test_url.c:407` | `static void test_resolve_file_confinement_fail_closed(void **state)` |
| `test_resolve_file_nulls` | function | `tests/test_url.c:433` | `static void test_resolve_file_nulls(void **state)` |
| `test_resolve_file_relative` | function | `tests/test_url.c:387` | `static void test_resolve_file_relative(void **state)` |
| `test_resolve_null_and_overflow` | function | `tests/test_url.c:218` | `static void test_resolve_null_and_overflow(void **state)` |
| `test_resolve_rejects_downgrade_and_schemes` | function | `tests/test_url.c:142` | `static void test_resolve_rejects_downgrade_and_schemes(void **state)` |
| `test_resolve_relative_path` | function | `tests/test_url.c:177` | `static void test_resolve_relative_path(void **state)` |
| `test_resolve_scheme_relative` | function | `tests/test_url.c:157` | `static void test_resolve_scheme_relative(void **state)` |
| `test_search_rewrite_ddg_spa` | function | `tests/test_url.c:323` | `static void test_search_rewrite_ddg_spa(void **state)` |
| `test_search_rewrite_leaves_others_alone` | function | `tests/test_url.c:340` | `static void test_search_rewrite_leaves_others_alone(void **state)` |
| `test_search_rewrite_nulls` | function | `tests/test_url.c:360` | `static void test_search_rewrite_nulls(void **state)` |
| `test_split_fail_closed_non_https` | function | `tests/test_url.c:624` | `static void test_split_fail_closed_non_https(void **state)` |
| `test_split_fragment_without_query` | function | `tests/test_url.c:491` | `static void test_split_fragment_without_query(void **state)` |
| `test_split_full_url` | function | `tests/test_url.c:450` | `static void test_split_full_url(void **state)` |
| `test_split_ipv6_literal_with_port` | function | `tests/test_url.c:500` | `static void test_split_ipv6_literal_with_port(void **state)` |
| `test_split_no_port_no_path` | function | `tests/test_url.c:469` | `static void test_split_no_port_no_path(void **state)` |
| `test_split_query_without_fragment` | function | `tests/test_url.c:482` | `static void test_split_query_without_fragment(void **state)` |
| `test_validate_https` | function | `tests/test_url.c:35` | `static void test_validate_https(void **state)` |
| `test_validate_long_bundle_url` | function | `tests/test_url.c:49` | `static void test_validate_long_bundle_url(void **state)` |
| `assert_false` | function | `tests/test_webcaps.c:59` | `assert_false(c.js);` |
| `assert_memory_equal` | function | `tests/test_webcaps.c:176` | `assert_memory_equal(&(rdp_caps)` |
| `assert_true` | function | `tests/test_webcaps.c:41` | `assert_true(c.js);` |
| `cmocka_run_group_tests` | function | `tests/test_webcaps.c:194` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_webcaps.c:180` | `int main(void)` |
| `memset` | function | `tests/test_webcaps.c:22` | `memset(&in, 0, sizeof in);` |
| `mk` | function | `tests/test_webcaps.c:20` | `static wc_input mk(jsp_mode mode, int in_js, int in_allow)` |
| `test_bad_mode_fails_closed` | function | `tests/test_webcaps.c:127` | `static void test_bad_mode_fails_closed(void **state)` |
| `test_from_flags_headless` | function | `tests/test_webcaps.c:153` | `static void test_from_flags_headless(void **state)` |
| `test_jspon_alone_is_not_trust` | function | `tests/test_webcaps.c:85` | `static void test_jspon_alone_is_not_trust(void **state)` |
| `test_present_trust_css_images_only` | function | `tests/test_webcaps.c:56` | `static void test_present_trust_css_images_only(void **state)` |
| `test_render_caps_projection` | function | `tests/test_webcaps.c:138` | `static void test_render_caps_projection(void **state)` |
| `test_safe_is_all_off` | function | `tests/test_webcaps.c:28` | `static void test_safe_is_all_off(void **state)` |
| `test_trusted_host_gets_all_caps` | function | `tests/test_webcaps.c:38` | `static void test_trusted_host_gets_all_caps(void **state)` |
| `test_user_toggles_grant_leakfree` | function | `tests/test_webcaps.c:100` | `static void test_user_toggles_grant_leakfree(void **state)` |
| `assert_int_equal` | function | `tests/test_zoom.c:19` | `assert_int_equal(zm_clamp(100), 100);` |
| `assert_true` | function | `tests/test_zoom.c:71` | `assert_true(pct >= prev);` |
| `cmocka_run_group_tests` | function | `tests/test_zoom.c:125` | `return cmocka_run_group_tests(tests, NULL, NULL);` |
| `main` | function | `tests/test_zoom.c:111` | `int main(void)` |
| `test_apply_scales_and_floors` | function | `tests/test_zoom.c:99` | `static void test_apply_scales_and_floors(void **state)` |
| `test_clamp_bounds` | function | `tests/test_zoom.c:16` | `static void test_clamp_bounds(void **state)` |
| `test_ends_are_idempotent` | function | `tests/test_zoom.c:58` | `static void test_ends_are_idempotent(void **state)` |
| `test_repeated_in_reaches_max` | function | `tests/test_zoom.c:66` | `static void test_repeated_in_reaches_max(void **state)` |
| `test_repeated_out_reaches_min` | function | `tests/test_zoom.c:78` | `static void test_repeated_out_reaches_min(void **state)` |
| `test_reset_is_default` | function | `tests/test_zoom.c:26` | `static void test_reset_is_default(void **state)` |
| `test_scale_factor` | function | `tests/test_zoom.c:90` | `static void test_scale_factor(void **state)` |
| `test_step_snaps_off_ladder` | function | `tests/test_zoom.c:48` | `static void test_step_snaps_off_ladder(void **state)` |
| `test_zoom_in_steps_ladder` | function | `tests/test_zoom.c:32` | `static void test_zoom_in_steps_ladder(void **state)` |
| `test_zoom_out_steps_ladder` | function | `tests/test_zoom.c:40` | `static void test_zoom_out_steps_ladder(void **state)` |
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
| `_POSIX_C_SOURCE` | macro | `tools/gen_psl.c:14` | `#define _POSIX_C_SOURCE` |
| `ascii_lower` | function | `tools/gen_psl.c:55` | `static void ascii_lower(char *s)` |
| `cmp_str` | function | `tools/gen_psl.c:37` | `static int cmp_str(const void *a, const void *b)` |
| `emit` | function | `tools/gen_psl.c:60` | `static void emit(const char *name, vec *v)` |
| `fclose` | function | `tools/gen_psl.c:96` | `fclose(f);` |
| `main` | function | `tools/gen_psl.c:66` | `int main(int argc, char **argv)` |
| `printf` | function | `tools/gen_psl.c:101` | `printf("/* Generated by tools/gen_psl from the vendored Public Suffix List.\n" " * Do not edit. Regenerate via the build` |
| `qsort` | function | `tools/gen_psl.c:44` | `qsort(v->items, v->len, sizeof *v->items, cmp_str);` |
| `sort_unique` | function | `tools/gen_psl.c:43` | `static void sort_unique(vec *v)` |
| `strcmp` | function | `tools/gen_psl.c:39` | `return strcmp(*(const char *const *)a, *(const char *const *)b);` |
| `vec` | struct | `tools/gen_psl.c:21` | `` |
| `vec_push` | function | `tools/gen_psl.c:26` | `static void vec_push(vec *v, const char *s)` |
| `find_modules` | function | `tools/mutate.py:107` | `def find_modules(root)` |
| `line_sites` | function | `tools/mutate.py:41` | `def line_sites(text)` |
| `main` | function | `tools/mutate.py:128` | `def main(argv)` |
| `mutate_line` | function | `tools/mutate.py:75` | `def mutate_line(line, op)` |
| `run_bin` | function | `tools/mutate.py:122` | `def run_bin(path)` |
| `run_make` | function | `tools/mutate.py:116` | `def run_make(root, target)` |
| `PD_COLS` | macro | `tools/pngdiff.c:57` | `#define PD_COLS` |
| `PD_INK_DELTA` | macro | `tools/pngdiff.c:63` | `#define PD_INK_DELTA` |
| `PD_ROWS` | macro | `tools/pngdiff.c:58` | `#define PD_ROWS` |
| `fprintf` | function | `tools/pngdiff.c:92` | `fprintf(stderr, "pngdiff: cannot open %s\n", path);` |
| `free` | function | `tools/pngdiff.c:81` | `free(r->row);` |
| `height` | type_alias | `tools/pngdiff.c:64` | `typedef struct pd_profile { uint32_t width, height;` |
| `main` | function | `tools/pngdiff.c:232` | `int main(int argc, char **argv)` |
| `memset` | function | `tools/pngdiff.c:83` | `memset(r, 0, sizeof *r);` |
| `pd_background` | function | `tools/pngdiff.c:147` | `static int pd_background(const char *path, double *out_bg)` |
| `pd_lum` | function | `tools/pngdiff.c:140` | `static double pd_lum(const png_byte *p)` |
| `pd_mae` | function | `tools/pngdiff.c:226` | `static double pd_mae(const double *a, const double *b, size_t n)` |
| `pd_profile` | struct | `tools/pngdiff.c:65` | `` |
| `pd_profile_of` | function | `tools/pngdiff.c:175` | `static int pd_profile_of(const char *path, pd_profile *out)` |
| `pd_reader` | struct | `tools/pngdiff.c:71` | `` |
| `pd_reader_close` | function | `tools/pngdiff.c:78` | `static void pd_reader_close(pd_reader *r)` |
| `pd_reader_open` | function | `tools/pngdiff.c:88` | `static int pd_reader_open(pd_reader *r, const char *path)` |
| `png_init_io` | function | `tools/pngdiff.c:104` | `png_init_io(r->png, r->fp);` |
| `png_read_info` | function | `tools/pngdiff.c:105` | `png_read_info(r->png, r->info);` |
| `png_read_row` | function | `tools/pngdiff.c:159` | `png_read_row(r.png, r.row, NULL);` |
| `png_read_update_info` | function | `tools/pngdiff.c:121` | `png_read_update_info(r->png, r->info);` |
| `png_set_background` | function | `tools/pngdiff.c:116` | `png_set_background(r->png, &(png_color_16)` |
| `png_set_strip_alpha` | function | `tools/pngdiff.c:118` | `png_set_strip_alpha(r->png);` |
| `printf` | function | `tools/pngdiff.c:264` | `printf("%u\t%u\t%.4f\t%.4f\t%.4f\t%.2f\n", fd.height, ff_real, h_ratio, col_mae, row_mae, score);` |
| `load_rows` | function | `tools/pngprof.py:41` | `def load_rows(path)` |
| `lum` | function | `tools/pngprof.py:95` | `def lum(p)` |
| `main` | function | `tools/pngprof.py:109` | `def main(argv)` |
| `render_glyph` | function | `tools/pngprof.py:99` | `def render_glyph(v)` |
