# Symbols (page 1 of 19)
Pages: [SYMBOLS.md](SYMBOLS.md), [SYMBOLS_p2.md](SYMBOLS_p2.md), [SYMBOLS_p3.md](SYMBOLS_p3.md), [SYMBOLS_p4.md](SYMBOLS_p4.md), [SYMBOLS_p5.md](SYMBOLS_p5.md), [SYMBOLS_p6.md](SYMBOLS_p6.md), [SYMBOLS_p7.md](SYMBOLS_p7.md), [SYMBOLS_p8.md](SYMBOLS_p8.md), [SYMBOLS_p9.md](SYMBOLS_p9.md), [SYMBOLS_p10.md](SYMBOLS_p10.md), [SYMBOLS_p11.md](SYMBOLS_p11.md), [SYMBOLS_p12.md](SYMBOLS_p12.md), [SYMBOLS_p13.md](SYMBOLS_p13.md), [SYMBOLS_p14.md](SYMBOLS_p14.md), [SYMBOLS_p15.md](SYMBOLS_p15.md), [SYMBOLS_p16.md](SYMBOLS_p16.md), [SYMBOLS_p17.md](SYMBOLS_p17.md), [SYMBOLS_p18.md](SYMBOLS_p18.md), [SYMBOLS_p19.md](SYMBOLS_p19.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `list_unique_crashes` | function | `app.py:39` | `def list_unique_crashes()` |
| `read_fuzz_stats` | function | `app.py:30` | `def read_fuzz_stats()` |
| `run_freedom_headless` | function | `app.py:47` | `def run_freedom_headless(payload_path)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_anchor.c:37` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `check_decode` | function | `fuzz/fuzz_anchor.c:15` | `static void check_decode(const char *frag)` |
| `check_location` | function | `fuzz/fuzz_anchor.c:23` | `static void check_location(const char *frag)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_box_blur.c:25` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `ref_line` | function | `fuzz/fuzz_box_blur.c:12` | `static void ref_line(unsigned char *p, int n, int step, int bw, unsigned char *tmp)` |
| `FB_MAX` | macro | `fuzz/fuzz_box_tree.c:8` | `#define FB_MAX` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_browser.c:53` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `SNAP_MAX` | macro | `fuzz/fuzz_browser.c:17` | `#define SNAP_MAX` |
| `_POSIX_C_SOURCE` | macro | `fuzz/fuzz_browser.c:8` | `#define _POSIX_C_SOURCE` |
| `invariants` | function | `fuzz/fuzz_browser.c:48` | `static void invariants(const browser_state *bs)` |
| `pos` | type_alias | `fuzz/fuzz_browser.c:18` | `typedef struct snap { size_t n, pos;` |
| `snap` | struct | `fuzz/fuzz_browser.c:19` | `` |
| `snap_check` | function | `fuzz/fuzz_browser.c:41` | `static void snap_check(const snap *s, const browser_state *bs)` |
| `snap_free` | function | `fuzz/fuzz_browser.c:25` | `static void snap_free(snap *s)` |
| `snap_take` | function | `fuzz/fuzz_browser.c:30` | `static void snap_take(snap *s, const browser_state *bs)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_chrome_layout.c:30` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `check_rect` | function | `fuzz/fuzz_chrome_layout.c:25` | `static void check_rect(chl_rect r)` |
| `take_double` | function | `fuzz/fuzz_chrome_layout.c:15` | `static double take_double(const uint8_t **p, size_t *n)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_css.c:91` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `fuzz_root_match` | function | `fuzz/fuzz_css.c:77` | `static int fuzz_root_match(void *ctx, const css_sel *sel)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_css_counter.c:11` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_css_import.c:50` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `fz_emit` | function | `fuzz/fuzz_css_import.c:15` | `static int fz_emit(void *ctx, const char *s, size_t n)` |
| `fz_out` | struct | `fuzz/fuzz_css_import.c:13` | `` |
| `fz_resolve` | function | `fuzz/fuzz_css_import.c:25` | `static int fz_resolve(void *ctx, const char *base, const char *ref, char *out, size_t outsz)` |
| `worker` | function | `fuzz/fuzz_data_url.c:6` | `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, never  * interpreted...` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_doc_title.c:26` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_dom.c:48` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `ensure_built` | function | `fuzz/fuzz_dom.c:41` | `static void ensure_built(void)` |
| `pass` | function | `fuzz/fuzz_dom_debug.c:8` | `* the measure pass (cap 0) must agree with the would-write return value.  *  * Build & run: make ...` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_download.c:31` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_exact_key.c:22` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_fb_cmdline.c:5` | `int LLVMFuzzerTestOneInput(const uint8_t *d, size_t n)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_find_text.c:11` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `MAXP` | macro | `fuzz/fuzz_find_text.c:9` | `#define MAXP` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_freebug.c:37` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_group_index.c:9` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_hls.c:13` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_identity.c:13` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_image_decode.c:33` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `poke_and_free` | function | `fuzz/fuzz_image_decode.c:22` | `static void poke_and_free(img_pixels *px)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_import_map.c:24` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `fres` | function | `fuzz/fuzz_import_map.c:17` | `static int fres(void *ctx, const char *base, const char *ref, char *out, size_t outsz)` |
| `FUZZ_JSDOM_MAX_NODES` | macro | `fuzz/fuzz_js_dom.c:39` | `#define FUZZ_JSDOM_MAX_NODES` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_js_dom.c:41` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `fz_dom_parent` | function | `fuzz/fuzz_js_dom.c:34` | `static dom_node_id fz_dom_parent(void *ctx, dom_node_id n)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_js_geom.c:27` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `fz_parent` | struct | `fuzz/fuzz_js_geom.c:17` | `` |
| `fz_parent_of` | function | `fuzz/fuzz_js_geom.c:20` | `static dom_node_id fz_parent_of(void *ctx, dom_node_id n)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_js_sandbox.c:48` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `fz_fetch` | function | `fuzz/fuzz_js_sandbox.c:33` | `static char *fz_fetch(void *host, const char *url, size_t *len)` |
| `fz_mod` | struct | `fuzz/fuzz_js_sandbox.c:21` | `` |
| `fz_resolve` | function | `fuzz/fuzz_js_sandbox.c:23` | `static int fz_resolve(void *host, const char *base, const char *spec, char *out, size_t outsz)` |
| `js_sandbox` | function | `fuzz/fuzz_js_sandbox.c:2` | `* libFuzzer harness for js_sandbox (Hito 3). * * Goal: arbitrary bytes treated as untrusted script through the full...` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_link_preview.c:11` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `KEYS` | macro | `fuzz/fuzz_mask_cache.c:13` | `#define KEYS` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_mask_cache.c:21` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `key_for` | function | `fuzz/fuzz_mask_cache.c:15` | `static mkc_key key_for(unsigned id, int w, int h)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_nav_token.c:13` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `POOL` | macro | `fuzz/fuzz_nav_token.c:11` | `#define POOL` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_net_guard.c:15` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `private` | function | `fuzz/fuzz_net_guard.c:3` | `* for text the binary classifier would call private (the two cannot disagree);` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_pdf_export.c:30` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_prefetch.c:14` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_prefs.c:21` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_scroll_req.c:11` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_site_panel.c:33` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `check_rect` | function | `fuzz/fuzz_site_panel.c:28` | `static void check_rect(chl_rect r)` |
| `check_text` | function | `fuzz/fuzz_site_panel.c:20` | `static void check_text(const char *s, size_t cap)` |
| `take_double` | function | `fuzz/fuzz_site_panel.c:14` | `static double take_double(const uint8_t **p, size_t *n)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_smooth_scroll.c:18` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `take` | function | `fuzz/fuzz_smooth_scroll.c:11` | `static double take(const uint8_t **d, size_t *n)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_svg_render.c:24` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_table_layout.c:24` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `attr_get` | function | `fuzz/fuzz_table_layout.c:17` | `static const char *attr_get(void *ctx, const char *name, size_t *len)` |
| `attr_src` | struct | `fuzz/fuzz_table_layout.c:15` | `` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_text_case.c:13` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `ASCII` | function | `fuzz/fuzz_text_shape.c:56` | `* printable ASCII (one run, the requested face) the two must agree. */ double m = tsh_measure(&f, px, text, len);` |
| `FZ_CAP` | macro | `fuzz/fuzz_text_shape.c:23` | `#define FZ_CAP` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_text_shape.c:25` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `glyph` | function | `fuzz/fuzz_text_shape.c:54` | `* one lacks a glyph (spec/text_shape.md 8);` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_url.c:59` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `check_split` | function | `fuzz/fuzz_url.c:31` | `static void check_split(const char *url)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_video_controls.c:14` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `take` | function | `fuzz/fuzz_video_controls.c:8` | `static double take(const uint8_t **p, size_t *n)` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_webfont.c:11` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `FZ_GLYPHS` | macro | `fuzz/fuzz_webfont_register.c:24` | `#define FZ_GLYPHS` |
| `LLVMFuzzerTestOneInput` | function | `fuzz/fuzz_webfont_register.c:26` | `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` |
| `AA_QUEUE_MAX` | macro | `gui/browser_ui.c:184` | `#define AA_QUEUE_MAX` |
| `ALIVE` | function | `gui/browser_ui.c:3033` | `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or...` |
| `BALANCE_MAX_LINES` | macro | `gui/browser_ui.c:6421` | `#define BALANCE_MAX_LINES` |
| `BUI_CONIC_SLICES` | macro | `gui/browser_ui.c:13327` | `#define BUI_CONIC_SLICES` |
| `FBW_COPY_BTN_H` | macro | `gui/browser_ui.c:19387` | `#define FBW_COPY_BTN_H` |
| `FBW_COPY_BTN_W` | macro | `gui/browser_ui.c:19386` | `#define FBW_COPY_BTN_W` |
| `FBW_GUTTER` | macro | `gui/browser_ui.c:19383` | `#define FBW_GUTTER` |
| `FBW_H` | macro | `gui/browser_ui.c:19376` | `#define FBW_H` |
| `FBW_HEADER` | macro | `gui/browser_ui.c:19377` | `#define FBW_HEADER` |
| `FBW_LINE` | macro | `gui/browser_ui.c:19382` | `#define FBW_LINE` |
| `FBW_MAX_SPLIT` | macro | `gui/browser_ui.c:19385` | `#define FBW_MAX_SPLIT` |
| `FBW_MIN_SPLIT` | macro | `gui/browser_ui.c:19384` | `#define FBW_MIN_SPLIT` |
| `FBW_PAD` | macro | `gui/browser_ui.c:19381` | `#define FBW_PAD` |
| `FBW_TABBAR` | macro | `gui/browser_ui.c:19378` | `#define FBW_TABBAR` |
| `FBW_TAB_PAD` | macro | `gui/browser_ui.c:19380` | `#define FBW_TAB_PAD` |
| `FBW_TOP` | macro | `gui/browser_ui.c:19379` | `#define FBW_TOP` |
| `FBW_W` | macro | `gui/browser_ui.c:19375` | `#define FBW_W` |
| `FLEX_MEASURE_W` | macro | `gui/browser_ui.c:6212` | `#define FLEX_MEASURE_W` |
| `FLEX_MIN_MEASURE_W` | macro | `gui/browser_ui.c:6217` | `#define FLEX_MIN_MEASURE_W` |
| `FONT_STASH_MAX_BYTES` | macro | `gui/browser_ui.c:1950` | `#define FONT_STASH_MAX_BYTES` |
| `FONT_STASH_MAX_SHEETS` | macro | `gui/browser_ui.c:1949` | `#define FONT_STASH_MAX_SHEETS` |
| `FRAME_BOX_MAX` | macro | `gui/browser_ui.c:16911` | `#define FRAME_BOX_MAX` |
| `Firefox` | function | `gui/browser_ui.c:17489` | `* on its face does in Firefox (spec/page_view.md, tanda 40). */ static const rd_block *submit_pro...` |
| `GET` | function | `gui/browser_ui.c:18283` | `* the network under weaker rules than a GET (Zero Trust). */ static void do_submit_post(browser_w...` |
| `GUI_EVAL_DEFAULT_AFTER_MS` | macro | `gui/browser_ui.c:21918` | `#define GUI_EVAL_DEFAULT_AFTER_MS` |
| `H2R` | macro | `gui/browser_ui.c:14989` | `#define H2R(p,q,t)` |
| `HIST_STEP_DEPTH_MAX` | macro | `gui/browser_ui.c:2703` | `#define HIST_STEP_DEPTH_MAX` |
| `HarfBuzz` | function | `gui/browser_ui.c:4419` | `* descriptor via HarfBuzz (text_shape);` |
| `JS_NAV_MAX` | macro | `gui/browser_ui.c:2701` | `#define JS_NAV_MAX` |
| `JS_TICKS_PER_LOAD` | macro | `gui/browser_ui.c:2829` | `#define JS_TICKS_PER_LOAD` |
| `OMNI_MAX_SUGG` | macro | `gui/browser_ui.c:143` | `#define OMNI_MAX_SUGG` |
| `OV_MAX_DEPTH` | macro | `gui/browser_ui.c:14289` | `#define OV_MAX_DEPTH` |
| `PDF_MARGIN` | macro | `gui/browser_ui.c:16515` | `#define PDF_MARGIN` |
| `PDF_PAGE_H` | macro | `gui/browser_ui.c:16514` | `#define PDF_PAGE_H` |
| `PDF_PAGE_W` | macro | `gui/browser_ui.c:16513` | `#define PDF_PAGE_W` |
| `PNG_MARGIN` | macro | `gui/browser_ui.c:16705` | `#define PNG_MARGIN` |
| `PNG_MAX_H` | macro | `gui/browser_ui.c:16706` | `#define PNG_MAX_H` |
| `PNG_PAGE_W` | macro | `gui/browser_ui.c:16681` | `#define PNG_PAGE_W` |
| `RC_ATOM_SCAN` | macro | `gui/browser_ui.c:6734` | `#define RC_ATOM_SCAN` |
| `RC_BOX_STACK_MAX` | macro | `gui/browser_ui.c:4143` | `#define RC_BOX_STACK_MAX` |
| `RC_COL_FREE_MAX` | macro | `gui/browser_ui.c:8285` | `#define RC_COL_FREE_MAX` |
| `RC_DEFER_BAND_RUNS` | macro | `gui/browser_ui.c:9520` | `#define RC_DEFER_BAND_RUNS` |
| `RC_DEFER_COLS` | macro | `gui/browser_ui.c:9435` | `#define RC_DEFER_COLS` |
| `RC_DEFER_RANGES` | macro | `gui/browser_ui.c:9436` | `#define RC_DEFER_RANGES` |
| `RC_FLOAT_FIT_MIN` | macro | `gui/browser_ui.c:4154` | `#define RC_FLOAT_FIT_MIN` |
| `RC_FLOAT_MAX` | macro | `gui/browser_ui.c:4147` | `#define RC_FLOAT_MAX` |
| `RC_IBOX_MAX` | macro | `gui/browser_ui.c:4141` | `#define RC_IBOX_MAX` |
| `RC_MAX_OUT_OF_FLOW` | macro | `gui/browser_ui.c:9269` | `#define RC_MAX_OUT_OF_FLOW` |
| `RC_TABLE_SOLVED_N` | macro | `gui/browser_ui.c:3988` | `#define RC_TABLE_SOLVED_N` |
| `ROW_PAINT_ALL` | macro | `gui/browser_ui.c:14065` | `#define ROW_PAINT_ALL` |
| `ROW_PAINT_BAND` | macro | `gui/browser_ui.c:14066` | `#define ROW_PAINT_BAND` |
| `ROW_PAINT_CONTENT` | macro | `gui/browser_ui.c:14067` | `#define ROW_PAINT_CONTENT` |
| `SRQ_SMOOTH` | function | `gui/browser_ui.c:17569` | `* lets SRQ_SMOOTH (or SRQ_AUTO under root scroll-behavior: smooth) animate. Returns 1 when  * the...` |
| `TABLE` | function | `gui/browser_ui.c:6877` | `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all...` |
| `TIMING_QUIET_MS` | macro | `gui/browser_ui.c:21893` | `#define TIMING_QUIET_MS` |
| `UI_BTN_LEFT` | macro | `gui/browser_ui.c:111` | `#define UI_BTN_LEFT` |
| `UI_BTN_MIDDLE` | macro | `gui/browser_ui.c:112` | `#define UI_BTN_MIDDLE` |
| `UI_BUTTON_HPAD` | macro | `gui/browser_ui.c:160` | `#define UI_BUTTON_HPAD` |
| `UI_CHECK_SZ` | macro | `gui/browser_ui.c:136` | `#define UI_CHECK_SZ` |
| `UI_CONTROL_FONT` | macro | `gui/browser_ui.c:152` | `#define UI_CONTROL_FONT` |
| `UI_CURSOR_SIZE` | macro | `gui/browser_ui.c:141` | `#define UI_CURSOR_SIZE` |
| `UI_FORM_FIELDS_MAX` | macro | `gui/browser_ui.c:161` | `#define UI_FORM_FIELDS_MAX` |
| `UI_HAMBURGER_GAP` | macro | `gui/browser_ui.c:140` | `#define UI_HAMBURGER_GAP` |
| `UI_HAMBURGER_W` | macro | `gui/browser_ui.c:139` | `#define UI_HAMBURGER_W` |
| `UI_HOT_NONE` | macro | `gui/browser_ui.c:242` | `#define UI_HOT_NONE` |
| `UI_HOT_PART` | macro | `gui/browser_ui.c:243` | `#define UI_HOT_PART(h)` |
| `UI_HOT_TAB` | macro | `gui/browser_ui.c:244` | `#define UI_HOT_TAB(h)` |
| `UI_IMAGE_MAX_BODY` | macro | `gui/browser_ui.c:257` | `#define UI_IMAGE_MAX_BODY` |
| `UI_INPUT_MEASURE_W` | macro | `gui/browser_ui.c:158` | `#define UI_INPUT_MEASURE_W` |
| `UI_INPUT_PAD` | macro | `gui/browser_ui.c:149` | `#define UI_INPUT_PAD` |
| `UI_INPUT_WIDTH` | macro | `gui/browser_ui.c:159` | `#define UI_INPUT_WIDTH` |
| `UI_LAZY_PASSES` | macro | `gui/browser_ui.c:16084` | `#define UI_LAZY_PASSES` |
| `UI_LAZY_PER_PASS` | macro | `gui/browser_ui.c:16083` | `#define UI_LAZY_PER_PASS` |
| `UI_LIST_INDENT` | macro | `gui/browser_ui.c:116` | `#define UI_LIST_INDENT` |
| `UI_MARGIN` | macro | `gui/browser_ui.c:110` | `#define UI_MARGIN` |
| `UI_MAX_TABS` | macro | `gui/browser_ui.c:299` | `#define UI_MAX_TABS` |
| `UI_MENU_COUNT` | macro | `gui/browser_ui.c:235` | `#define UI_MENU_COUNT` |
| `UI_MENU_INPUT_H` | macro | `gui/browser_ui.c:138` | `#define UI_MENU_INPUT_H` |
| `UI_MENU_ITEM_H` | macro | `gui/browser_ui.c:133` | `#define UI_MENU_ITEM_H` |
| `UI_MENU_LABEL_H` | macro | `gui/browser_ui.c:137` | `#define UI_MENU_LABEL_H` |
| `UI_MENU_PAD` | macro | `gui/browser_ui.c:134` | `#define UI_MENU_PAD` |
| `UI_MENU_RADIUS` | macro | `gui/browser_ui.c:135` | `#define UI_MENU_RADIUS` |
| `UI_MENU_W` | macro | `gui/browser_ui.c:132` | `#define UI_MENU_W` |
| `UI_OMNI_ROW_H` | macro | `gui/browser_ui.c:144` | `#define UI_OMNI_ROW_H` |
| `UI_OVERLINE_OFFSET` | macro | `gui/browser_ui.c:169` | `#define UI_OVERLINE_OFFSET` |
| `UI_READER_COLUMN_W` | macro | `gui/browser_ui.c:769` | `#define UI_READER_COLUMN_W` |
| `UI_RESIZE_MARGIN` | macro | `gui/browser_ui.c:127` | `#define UI_RESIZE_MARGIN` |
| `UI_SCROLLBAR_MIN` | macro | `gui/browser_ui.c:122` | `#define UI_SCROLLBAR_MIN` |
| `UI_SCROLLBAR_PAD` | macro | `gui/browser_ui.c:123` | `#define UI_SCROLLBAR_PAD` |
| `UI_SCROLLBAR_W` | macro | `gui/browser_ui.c:121` | `#define UI_SCROLLBAR_W` |
| `UI_SLICE_MAX` | macro | `gui/browser_ui.c:173` | `#define UI_SLICE_MAX` |
| `UI_STRIKE_OFFSET` | macro | `gui/browser_ui.c:168` | `#define UI_STRIKE_OFFSET` |
| `UI_TOAST_PAD` | macro | `gui/browser_ui.c:142` | `#define UI_TOAST_PAD` |
| `UI_TOOLBAR_H` | macro | `gui/browser_ui.c:109` | `#define UI_TOOLBAR_H` |
| `UI_TWO_PI` | macro | `gui/browser_ui.c:145` | `#define UI_TWO_PI` |
| `UI_UNDERLINE_OFFSET` | macro | `gui/browser_ui.c:166` | `#define UI_UNDERLINE_OFFSET` |
| `UI_UNDERLINE_THICK` | macro | `gui/browser_ui.c:167` | `#define UI_UNDERLINE_THICK` |
| `_GNU_SOURCE` | macro | `gui/browser_ui.c:12` | `#define _GNU_SOURCE` |
| `aa_note` | function | `gui/browser_ui.c:1764` | `static void aa_note(browser_window *w, const char *abs, const char *host)` |
| `absolute_start` | function | `gui/browser_ui.c:21967` | `static const char *absolute_start(const char *start, char *abs, size_t cap)` |
| `add_current_host_to_list` | function | `gui/browser_ui.c:1058` | `static int add_current_host_to_list(browser_window *w, int sel)` |
| `addr` | type_alias | `gui/browser_ui.c:734` | `typedef struct fip_hit { uintptr_t addr;` |
| `again` | function | `gui/browser_ui.c:12401` | `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one...` |
| `allowlisted` | type_alias | `gui/browser_ui.c:2150` | `typedef struct fetch_prep { int allowlisted;` |
| `anchor` | function | `gui/browser_ui.c:10774` | `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is...` |
| `apply_click_result` | function | `gui/browser_ui.c:18059` | `static int apply_click_result(browser_window *w, tab_page *page)` |
| `apply_history_ops` | function | `gui/browser_ui.c:17961` | `static void apply_history_ops(browser_window *w, const tab_page *page)` |
| `apply_operator_override` | function | `gui/browser_ui.c:1747` | `static void apply_operator_override(sf_config *cfg)` |
| `apply_zoom` | function | `gui/browser_ui.c:785` | `static void apply_zoom(browser_window *w)` |
| `approximation` | function | `gui/browser_ui.c:11159` | `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */ static void oof_s...` |
| `area` | function | `gui/browser_ui.c:4631` | `* box spans its CONTENT area (the font's ascent + descent plus its vertical padding  * and border...` |
| `arrives` | function | `gui/browser_ui.c:3149` | `* on screen until the result arrives (deliver_fetch_result renders it). about:blank  * and local ...` |
| `atoms_extend_line` | function | `gui/browser_ui.c:4716` | `static void atoms_extend_line(const rc_layout *L, rc_state *s, double *h,                        ...` |
| `audio_mark_dead` | function | `gui/browser_ui.c:12360` | `static void audio_mark_dead(browser_window *w)` |
| `audio_spawn` | function | `gui/browser_ui.c:12306` | `static void audio_spawn(browser_window *w, int rate, int channels)` |
| `audio_stop` | function | `gui/browser_ui.c:12392` | `static void audio_stop(browser_window *w)` |
| `audio_write` | function | `gui/browser_ui.c:12377` | `static void audio_write(browser_window *w, const uint8_t *data, size_t len)` |
| `axis` | function | `gui/browser_ui.c:7405` | `* differs: items stack on the vertical main axis (fx_column_place) and align on * the horizontal cross axis...` |
| `balanced_wrap_width` | function | `gui/browser_ui.c:6422` | `static double balanced_wrap_width(cairo_t *cr, const browser_window *w, const ui_theme *th,      ...` |
| `band_common_box` | function | `gui/browser_ui.c:9341` | `static int band_common_box(const rd_doc *doc, size_t start, size_t end)` |
| `band_common_box_ex` | function | `gui/browser_ui.c:9316` | `static int band_common_box_ex(const rd_doc *doc, size_t start, size_t end, int skip_boxless)` |
| `band_parent_box` | function | `gui/browser_ui.c:9309` | `static int band_parent_box(const rd_doc *doc, const rd_block *bk)` |
| `band_shared_box` | function | `gui/browser_ui.c:6987` | `static int band_shared_box(const rd_doc *doc, const rc_state *s, size_t start, size_t end);` |
| `behind` | function | `gui/browser_ui.c:8559` | `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old...` |
| `beside` | function | `gui/browser_ui.c:9631` | `* margin: nothing to pull up beside (CSS 2.1 9.5.1 rule 5 -- a float's top is never * above an earlier block). They...` |
| `bg` | function | `gui/browser_ui.c:14136` | `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);` |
| `blit_image_box` | function | `gui/browser_ui.c:12068` | `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,                  ...` |
| `blit_video_frame` | function | `gui/browser_ui.c:12892` | `static int blit_video_frame(cairo_t *cr, browser_window *w,                             double x,...` |
| `block_id` | type_alias | `gui/browser_ui.c:4058` | `typedef struct rc_open_box { int block_id;` |
| `block_in_table_caption` | function | `gui/browser_ui.c:9411` | `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)` |
| `block_is_oof` | function | `gui/browser_ui.c:6889` | `static int block_is_oof(const rd_doc *doc, const rd_block *bk)` |
| `block_leaves_flow` | function | `gui/browser_ui.c:5379` | `static int block_leaves_flow(const rd_doc *doc, const rd_block *bk);` |
| `block_margins` | function | `gui/browser_ui.c:4594` | `static void block_margins(const ui_theme *th, const rd_block *b,                           double...` |
| `block_space_px` | function | `gui/browser_ui.c:6032` | `static double block_space_px(cairo_t *cr, const browser_window *w, const ui_theme *th,           ...` |
| `block_style` | function | `gui/browser_ui.c:4566` | `static void block_style(const ui_theme *th, const rd_block *b,                         double *si...` |
| `block_text_style` | function | `gui/browser_ui.c:5630` | `static void block_text_style(const browser_window *w, const ui_theme *th, const rd_block *b,     ...` |
| `blocking` | function | `gui/browser_ui.c:12730` | `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);` |
| `body` | function | `gui/browser_ui.c:2913` | `* every served CSS body (serial and pool paths alike). */ font_stash_reset(w);` |
| `bookmark_star_state` | function | `gui/browser_ui.c:1187` | `static int bookmark_star_state(const browser_window *w)` |
| `bookmark_toggle_current` | function | `gui/browser_ui.c:1194` | `static void bookmark_toggle_current(browser_window *w)` |
| `box` | function | `gui/browser_ui.c:15522` | `* content belongs to that box (painted by its own positioned entry). */     if (sub == NULL)` |
| `box_edge_px` | function | `gui/browser_ui.c:5901` | `static double box_edge_px(int wpx)` |
| `box_forms_stacking_context` | function | `gui/browser_ui.c:14418` | `static int box_forms_stacking_context(const pv_box_def *def)` |
| `box_is_strict_descendant` | function | `gui/browser_ui.c:6014` | `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)` |
| `box_line_visible` | function | `gui/browser_ui.c:8272` | `static int box_line_visible(int style)` |
| `box_margin_bottom` | function | `gui/browser_ui.c:8540` | `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)` |
| `box_margin_top` | function | `gui/browser_ui.c:8533` | `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)` |
| `box_pad_px` | function | `gui/browser_ui.c:1393` | `static double box_pad_px(int px_val, int pct_pm, double cb_w);` |
| `box_path` | function | `gui/browser_ui.c:13066` | `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)` |
| `box_path4` | function | `gui/browser_ui.c:5297` | `static void box_path4(cairo_t *cr, double x, double y, double w, double h, const double *rc);` |
| `box_path_has` | function | `gui/browser_ui.c:8896` | `static int box_path_has(const rd_doc *doc, int block_id, int want)` |
| `box_path_of` | function | `gui/browser_ui.c:9273` | `static int box_path_of(const rd_doc *doc, int block_id, int *out)` |
| `box_pointer_events_none` | function | `gui/browser_ui.c:17399` | `static int box_pointer_events_none(const rd_doc *doc, int block_id)` |
| `box_shadow_layers` | function | `gui/browser_ui.c:13079` | `static int box_shadow_layers(const rc_box *bx, int layers[PV_BSHADOW_LAYERS][6])` |
| `box_shrink_width` | function | `gui/browser_ui.c:9006` | `static double box_shrink_width(cairo_t *cr, const browser_window *w,                             ...` |
| `box_transform_matrix` | function | `gui/browser_ui.c:14469` | `static int box_transform_matrix(const pv_box_def *def, double box_x, double box_y,               ...` |
| `box_under` | function | `gui/browser_ui.c:6828` | `static int box_under(const rd_doc *doc, int child, int anc)` |
| `browser_window` | struct | `gui/browser_ui.c:329` | `` |
| `bs` | type_alias | `gui/browser_ui.c:307` | `typedef struct tab_ctx { browser_state bs;` |
| `buffer_release` | function | `gui/browser_ui.c:796` | `static void buffer_release(void *data, struct wl_buffer *wl_buffer)` |
| `bui_blend_operator` | function | `gui/browser_ui.c:14597` | `static cairo_operator_t bui_blend_operator(int mix_blend)` |
| `bui_build_mask` | function | `gui/browser_ui.c:14752` | `static cairo_surface_t *bui_build_mask(const pv_box_def *def, const rc_box *bx_in,               ...` |
| `bui_gaussian_blur_surface` | function | `gui/browser_ui.c:14623` | `static void bui_gaussian_blur_surface(cairo_surface_t *surf, double sigma)` |
| `bui_grad_color_at` | function | `gui/browser_ui.c:13300` | `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,                    ...` |
| `bui_mask_ctx` | struct | `gui/browser_ui.c:14728` | `` |
| `bui_mask_ref_rect` | function | `gui/browser_ui.c:14736` | `static int bui_mask_ref_rect(const rc_layout *L, int ref, rc_box *out)` |
| `bui_paint_backdrop_blur` | function | `gui/browser_ui.c:14666` | `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,                          ...` |
| `bui_pop_group_composite` | function | `gui/browser_ui.c:14868` | `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms,     ...` |
| `bui_pop_group_composite` | function | `gui/browser_ui.c:15309` | `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,              ...` |
| `bui_pop_group_composite` | function | `gui/browser_ui.c:15666` | `bui_pop_group_composite(cr, cdef, now_ms() - w->page_load_mono_ms, &L->boxes[j], left, origin,   ...` |
| `bui_pop_group_composite` | function | `gui/browser_ui.c:16037` | `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,              ...` |
| `bui_skew_tan` | function | `gui/browser_ui.c:14462` | `static double bui_skew_tan(int deg)` |
| `build_file_origin` | function | `gui/browser_ui.c:903` | `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)` |
| `build_host_filter` | function | `gui/browser_ui.c:917` | `static hb_set *build_host_filter(void)` |
| `build_impersonate_optin` | function | `gui/browser_ui.c:936` | `static int build_impersonate_optin(void)` |
| `build_js_filter` | function | `gui/browser_ui.c:933` | `static hb_set *build_js_filter(void)` |
| `builds` | function | `gui/browser_ui.c:7862` | `* wraps beside it: the same band the top level builds (spec/float.md). */ const rd_block *fk = rd_at(doc, k);` |
| `button_box_width` | function | `gui/browser_ui.c:11619` | `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,               ...` |
| `cairo_set_dash` | function | `gui/browser_ui.c:13640` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:13643` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:13689` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:13692` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:13750` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:13753` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:13845` | `cairo_set_dash(cr, (double[])` |
| `cairo_set_dash` | function | `gui/browser_ui.c:13847` | `cairo_set_dash(cr, (double[])` |
| `caller` | function | `gui/browser_ui.c:17030` | `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the  * out_path ve...` |
| `chain` | function | `gui/browser_ui.c:10659` | `* chain (the box that left the normal flow at this pen position);` |
| `child_cont_at_level` | function | `gui/browser_ui.c:6784` | `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)` |
| `children` | function | `gui/browser_ui.c:8550` | `* own content rect onto the stack so its children (text or nested boxes) place inside  * it. At t...` |
| `chrome_hot_at` | function | `gui/browser_ui.c:3766` | `static ui_hot chrome_hot_at(const browser_window *w, double px, double py)` |
| `chrome_of` | function | `gui/browser_ui.c:3534` | `static chl_layout chrome_of(const browser_window *w)` |
| `chrome_view_fill` | function | `gui/browser_ui.c:18971` | `static void chrome_view_fill(browser_window *w, const chl_layout *l, const char **titles,        ...` |
| `cid` | type_alias | `gui/browser_ui.c:3981` | `typedef struct rc_table_ctx { int cid;` |
| `clear_doc` | function | `gui/browser_ui.c:1595` | `static void clear_doc(browser_window *w)` |
| `clipboard_copy` | function | `gui/browser_ui.c:21001` | `static void clipboard_copy(browser_window *w)` |
| `close_all_boxes` | function | `gui/browser_ui.c:6707` | `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);` |
| `close_top_box` | function | `gui/browser_ui.c:8331` | `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)` |
| `col` | type_alias | `gui/browser_ui.c:9454` | `typedef struct rc_defer { rc_defer_col col[RC_DEFER_COLS];` |
| `col_founder_box` | type_alias | `gui/browser_ui.c:4155` | `typedef struct rc_state { /* Inside a float band column whose width was SHRUNK TO FIT: the float * founder's own box...` |
| `col_spend_free_space` | function | `gui/browser_ui.c:8286` | `static void col_spend_free_space(rc_layout *L, const rc_open_box *ob, double free_px)` |
| `collect_local_storage` | function | `gui/browser_ui.c:2776` | `static void collect_local_storage(browser_window *w, const tab_page *page)` |
| `column` | function | `gui/browser_ui.c:8802` | `*  * Returns the height of the tallest column (0 when there is nothing to fragment). */ static do...` |
| `columns` | function | `gui/browser_ui.c:8910` | `* each card made 1080px columns (huggingface, github). */ static int deepest_open_on_path(const r...` |
| `compositing` | function | `gui/browser_ui.c:15325` | `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context...` |
| `compute_page_js` | function | `gui/browser_ui.c:2723` | `static int compute_page_js(const browser_window *w)` |
| `cont_gap_px` | function | `gui/browser_ui.c:6522` | `static double cont_gap_px(cairo_t *cr, const browser_window *w, const ui_theme *th,              ...` |
| `cont_in_view` | function | `gui/browser_ui.c:6803` | `static int cont_in_view(const rd_doc *doc, int cid)` |
| `cont_next_item` | function | `gui/browser_ui.c:6998` | `static int cont_next_item(const rd_doc *doc, int cid, size_t end, size_t *k, size_t *e)` |
| `container` | function | `gui/browser_ui.c:6170` | `* were the container (github's tab pill). */ int item = item_at_level(doc, rd_at(doc, k), cid);` |
| `container_box_of` | function | `gui/browser_ui.c:6138` | `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)` |
| `container_inner_h` | function | `gui/browser_ui.c:6955` | `static double container_inner_h(const rd_doc *doc, const pv_cont_def *cdv, double content_w)` |
| `content_font` | function | `gui/browser_ui.c:4452` | `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,             ...` |
| `content_font_ex` | function | `gui/browser_ui.c:4430` | `static void content_font_ex(cairo_t *cr, double size, int bold, int italic, int family,          ...` |
| `content_geometry` | function | `gui/browser_ui.c:3608` | `static void content_geometry(const browser_window *w, double *top, double *height)` |
| `content_margin_x` | function | `gui/browser_ui.c:3642` | `static double content_margin_x(const browser_window *w)` |
| `content_margins_x` | function | `gui/browser_ui.c:3653` | `static double content_margins_x(const browser_window *w)` |
| `content_width` | function | `gui/browser_ui.c:3658` | `static double content_width(const browser_window *w)` |
| `context` | function | `gui/browser_ui.c:9400` | `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document...` |
| `convention` | function | `gui/browser_ui.c:13712` | `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE \|\| style...` |
| `cost` | function | `gui/browser_ui.c:22468` | `* measured cost (floor 33 ms = the existing ~30 fps ceiling):              * cheap pages paint at...` |
| `count` | function | `gui/browser_ui.c:11140` | `* the box count (a hostile parent cycle terminates). */ static int oof_depth(const rd_doc *doc, s...` |
| `cr_mask_cache` | function | `gui/browser_ui.c:13103` | `static mkc_cache *cr_mask_cache(cairo_t *cr)` |
| `css_replaced_box` | function | `gui/browser_ui.c:5508` | `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,                ...` |
| `cursor_at_point` | function | `gui/browser_ui.c:17415` | `static int cursor_at_point(browser_window *w, double px, double py)` |
| `data_device_data_offer` | function | `gui/browser_ui.c:20784` | `static void data_device_data_offer(void *data, struct wl_data_device *dev,                       ...` |
| `data_device_drop` | function | `gui/browser_ui.c:20825` | `static void data_device_drop(void *d, struct wl_data_device *dev)` |
| `data_device_enter` | function | `gui/browser_ui.c:20815` | `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,              ...` |
| `data_device_leave` | function | `gui/browser_ui.c:20820` | `static void data_device_leave(void *d, struct wl_data_device *dev)` |
| `data_device_motion` | function | `gui/browser_ui.c:20821` | `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,                  ...` |
| `data_device_selection` | function | `gui/browser_ui.c:20796` | `static void data_device_selection(void *data, struct wl_data_device *dev,                        ...` |
| `data_offer_action` | function | `gui/browser_ui.c:20774` | `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)` |
| `data_offer_source_actions` | function | `gui/browser_ui.c:20771` | `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)` |
| `data_source_cancelled` | function | `gui/browser_ui.c:20836` | `static void data_source_cancelled(void *data, struct wl_data_source *src)` |
| `data_source_send` | function | `gui/browser_ui.c:20842` | `static void data_source_send(void *data, struct wl_data_source *src,                             ...` |
| `data_source_target` | function | `gui/browser_ui.c:20855` | `static void data_source_target(void *d, struct wl_data_source *s, const char *m)` |
| `deco_configure` | function | `gui/browser_ui.c:19263` | `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)` |
| `deepest_open_on_path` | function | `gui/browser_ui.c:6762` | `static int deepest_open_on_path(const rc_state *outer, const rd_doc *doc, int block_id);` |
| `def_declared_width` | function | `gui/browser_ui.c:6513` | `static double def_declared_width(const pv_box_def *d, double avail_w)` |
| `def_width_cap` | function | `gui/browser_ui.c:6507` | `static double def_width_cap(const pv_box_def *d, double avail_w)` |
| `defer_append` | function | `gui/browser_ui.c:9677` | `static int defer_append(rc_defer *d, int key, int side,                         int ml, int mlpct...` |
| `defer_col_shrink_w` | function | `gui/browser_ui.c:9757` | `static double defer_col_shrink_w(cairo_t *cr, const browser_window *w, const ui_theme *th,       ...` |
| `defer_flush` | function | `gui/browser_ui.c:9812` | `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,                      ...` |
| `defer_key_block` | function | `gui/browser_ui.c:9477` | `static int defer_key_block(const rd_block *bk)` |
| `defer_root_before` | function | `gui/browser_ui.c:15786` | `static int defer_root_before(const rd_doc *doc, const rc_layout *L, size_t a, size_t b)` |
| `defer_root_of` | function | `gui/browser_ui.c:11596` | `static int defer_root_of(const rc_layout *L, int bid)` |
| `defer_root_z` | function | `gui/browser_ui.c:15780` | `static int defer_root_z(const rd_doc *doc, size_t root)` |
| `defer_wants` | function | `gui/browser_ui.c:11604` | `static int defer_wants(const rc_layout *L, int bid, int only_root)` |
| `delay` | function | `gui/browser_ui.c:459` | `* timer delay (tab_page.next_timer_ms);` |
| `deliver_fetch_result` | function | `gui/browser_ui.c:18398` | `static void deliver_fetch_result(browser_window *w, fetch_job *j)` |
| `descriptor` | function | `gui/browser_ui.c:7618` | `* placement rides the nested descriptor (spec/grid_areas.md 6). */ int nbc = child_cont_at_level(doc, bk, cid);` |
| `descriptors` | function | `gui/browser_ui.c:12320` | `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection —...` |
| `destroy_buffer` | function | `gui/browser_ui.c:810` | `static void destroy_buffer(browser_window *w)` |
| `dies` | function | `gui/browser_ui.c:12297` | `* child dies (exec failed, device busy, daemon absent) is detected on the  * next PCM write (EPIP...` |
| `dispatch_js_event` | function | `gui/browser_ui.c:21138` | `static void dispatch_js_event(browser_window *w, dom_node_id node_id,                            ...` |
| `do_load` | function | `gui/browser_ui.c:2680` | `static void do_load(browser_window *w, const char *url);` |
| `down` | function | `gui/browser_ui.c:20192` | `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void...` |
| `drain_fetch_results` | function | `gui/browser_ui.c:18468` | `static void drain_fetch_results(browser_window *w)` |
| `draw_findbar` | function | `gui/browser_ui.c:19049` | `static void draw_findbar(cairo_t *cr, browser_window *w)` |
| `draw_menu` | function | `gui/browser_ui.c:18768` | `static void draw_menu(cairo_t *cr, browser_window *w)` |
| `draw_omnibox` | function | `gui/browser_ui.c:19014` | `static void draw_omnibox(cairo_t *cr, browser_window *w)` |
| `draw_scrollbar` | function | `gui/browser_ui.c:3727` | `static void draw_scrollbar(cairo_t *cr, const browser_window *w)` |
| `draw_site_panel` | function | `gui/browser_ui.c:18956` | `static void draw_site_panel(cairo_t *cr, browser_window *w)` |
| `draw_slice` | function | `gui/browser_ui.c:4501` | `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)` |
| `draw_toast` | function | `gui/browser_ui.c:18904` | `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)` |
| `drop_repl_worker` | function | `gui/browser_ui.c:2819` | `static void drop_repl_worker(browser_window *w)` |
| `element` | function | `gui/browser_ui.c:19305` | `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand  * even without...` |
| `emit_replaced_row` | function | `gui/browser_ui.c:5517` | `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,                 ...` |
| `empty_atom_continues_line` | function | `gui/browser_ui.c:6273` | `static int empty_atom_continues_line(const rd_doc *doc, size_t run_i, int box_id);` |
| `empty_atom_outer_w` | function | `gui/browser_ui.c:6277` | `static double empty_atom_outer_w(const rd_doc *doc, size_t k, const rd_block *bk)` |
| `ensure_buffer` | function | `gui/browser_ui.c:845` | `static int ensure_buffer(browser_window *w)` |
| `ensure_download_dir` | function | `gui/browser_ui.c:18318` | `static int ensure_download_dir(char *out, size_t outsz)` |
| `exactly` | function | `gui/browser_ui.c:13907` | `* the resolved size exactly (like the SVG path above): routing through * paint_image_row would re-resolve a % width...` |
| `export_pdf` | function | `gui/browser_ui.c:16639` | `static void export_pdf(browser_window *w)` |
| `export_png` | function | `gui/browser_ui.c:16996` | `static void export_png(browser_window *w)` |
| `family` | type_alias | `gui/browser_ui.c:4865` | `typedef struct rc_ext { int family;` |
| `family_face` | function | `gui/browser_ui.c:4408` | `static const char *family_face(int family)` |
| `fb_buffer_release` | function | `gui/browser_ui.c:807` | `static void fb_buffer_release(void *data, struct wl_buffer *wl_buffer)` |
| `fbw_arg_hint` | function | `gui/browser_ui.c:19493` | `static const char *fbw_arg_hint(int which)` |
| `fbw_cell_w` | function | `gui/browser_ui.c:19480` | `static double fbw_cell_w(cairo_t *cr)` |
| `fbw_console_lines` | function | `gui/browser_ui.c:19465` | `static size_t fbw_console_lines(const fb_buffer *log, int filter)` |
| `fbw_level_rgb` | function | `gui/browser_ui.c:19454` | `static void fbw_level_rgb(int level, double *r, double *g, double *b)` |
| `fbw_paint_pane` | function | `gui/browser_ui.c:19537` | `static void fbw_paint_pane(cairo_t *cr, const freebug_window *fb, double y, double split_y)` |
| `fbw_paint_tabs` | function | `gui/browser_ui.c:19504` | `static void fbw_paint_tabs(cairo_t *cr, const freebug_window *fb)` |
| `fbw_split_y` | function | `gui/browser_ui.c:19418` | `static double fbw_split_y(const freebug_window *fb)` |
| `fbw_text_lines` | function | `gui/browser_ui.c:19486` | `static size_t fbw_text_lines(const char *t)` |
| `fbw_toplevel_close` | function | `gui/browser_ui.c:19826` | `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)` |
| `fbw_toplevel_configure` | function | `gui/browser_ui.c:19817` | `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,                           ...` |
| `fbw_xdg_surface_configure` | function | `gui/browser_ui.c:19809` | `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)` |
| `fetch_follow_navigable` | function | `gui/browser_ui.c:1697` | `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,                         ...` |
| `fetch_get_cached` | function | `gui/browser_ui.c:1705` | `static sf_status fetch_get_cached(const browser_window *w, const char *url, sf_config *cfg,      ...` |
| `fetch_job` | struct | `gui/browser_ui.c:2231` | `` |
| `fetch_job_cancelled` | function | `gui/browser_ui.c:2313` | `static int fetch_job_cancelled(void *ctx)` |
| `fetch_job_free` | function | `gui/browser_ui.c:2266` | `static void fetch_job_free(fetch_job *j)` |
| `fetch_launch` | function | `gui/browser_ui.c:2395` | `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,                ...` |
| `fetch_post_navigable` | function | `gui/browser_ui.c:1713` | `static sf_status fetch_post_navigable(const char *url, sf_config *cfg,                           ...` |
| `fetch_prep` | struct | `gui/browser_ui.c:2150` | `` |
| `fetch_thread` | function | `gui/browser_ui.c:2321` | `static void *fetch_thread(void *arg)` |
| `fields` | function | `gui/browser_ui.c:303` | `* fields (so the 200+ render/event call sites stay unchanged);` |
| `fill` | function | `gui/browser_ui.c:15222` | `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in...` |
| `fill_frame_slot` | function | `gui/browser_ui.c:16929` | `static void fill_frame_slot(browser_window *w, const rd_block *b, ui_image *slot,                ...` |
| `find_bg_image` | function | `gui/browser_ui.c:1369` | `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)` |
| `find_input_state` | function | `gui/browser_ui.c:1580` | `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)` |
| `fip_clear_hits` | function | `gui/browser_ui.c:13966` | `static void fip_clear_hits(browser_window *w)` |
| `fip_click` | function | `gui/browser_ui.c:21285` | `static int fip_click(browser_window *w, double x, double y)` |
| `fip_close_bar` | function | `gui/browser_ui.c:21215` | `static void fip_close_bar(browser_window *w)` |
| `fip_collect` | function | `gui/browser_ui.c:13983` | `static void fip_collect(const rc_layout *L, double dy, ft_piece *p, double *ys, size_t cap,      ...` |
| `fip_edited` | function | `gui/browser_ui.c:21235` | `static void fip_edited(browser_window *w)` |
| `fip_focus` | function | `gui/browser_ui.c:21195` | `static void fip_focus(browser_window *w)` |
| `fip_hit` | struct | `gui/browser_ui.c:735` | `` |
| `fip_hit_cmp` | function | `gui/browser_ui.c:13977` | `static int fip_hit_cmp(const void *a, const void *b)` |
| `fip_hot_at` | function | `gui/browser_ui.c:21300` | `static chl_find_part fip_hot_at(const browser_window *w, double x, double y)` |
| `fip_key` | function | `gui/browser_ui.c:21252` | `static int fip_key(browser_window *w, xkb_keysym_t sym, const char *utf8, int n, int ctrl,       ...` |
| `fip_lower` | function | `gui/browser_ui.c:13934` | `static size_t fip_lower(const browser_window *w, uintptr_t addr)` |
| `fip_open_bar` | function | `gui/browser_ui.c:21204` | `static void fip_open_bar(browser_window *w)` |
| `fip_paint_frag` | function | `gui/browser_ui.c:13945` | `static void fip_paint_frag(cairo_t *cr, const browser_window *w, const rc_frag *f,               ...` |
| `fip_reveal` | function | `gui/browser_ui.c:14055` | `static void fip_reveal(browser_window *w, double content_h)` |
| `fip_step` | function | `gui/browser_ui.c:21226` | `static void fip_step(browser_window *w, int dir)` |
| `fip_sync` | function | `gui/browser_ui.c:14005` | `static void fip_sync(browser_window *w, const rc_layout *L)` |
| `fip_type` | function | `gui/browser_ui.c:21241` | `static void fip_type(browser_window *w, const char *s, size_t n)` |
| `first` | function | `gui/browser_ui.c:2045` | `* Navigation: clear the registry first (faces are per document). Untrusted:  * no-op (fetch NULL)...` |
| `flex_item_basis` | function | `gui/browser_ui.c:6629` | `static double flex_item_basis(cairo_t *cr, const browser_window *w,                              ...` |
| `flex_item_min_main` | function | `gui/browser_ui.c:6677` | `static double flex_item_min_main(cairo_t *cr, const browser_window *w,                           ...` |
| `float_founder_edges` | function | `gui/browser_ui.c:9742` | `static double float_founder_edges(const rd_doc *doc, int float_box, double ctx_w)` |
| `float_item_stop` | function | `gui/browser_ui.c:8927` | `static int float_item_stop(const rd_doc *doc, const rd_block *bk, int founder_key, int base_stop)` |
| `flow` | function | `gui/browser_ui.c:7958` | `* it collapse their vertical margins with each other exactly as in * the main flow (CSS 2.1 8.3.1), and none escapes...` |
| `flow_box_of` | function | `gui/browser_ui.c:15865` | `static const rc_box *flow_box_of(const screen_flow_ctx *c, int bid)` |
| `flow_emit_frag` | function | `gui/browser_ui.c:4898` | `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,                  ...` |
| `flow_index_build` | function | `gui/browser_ui.c:15879` | `static void flow_index_build(screen_flow_ctx *c, void **blob)` |
| `flow_index_free` | function | `gui/browser_ui.c:15943` | `static void flow_index_free(void **blob)` |
| `flow_smallcaps_word` | function | `gui/browser_ui.c:4960` | `static double flow_smallcaps_word(cairo_t *cr, rc_layout *L, rc_state *s,                        ...` |
| `flow_text` | function | `gui/browser_ui.c:5024` | `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,                ...` |
| `flow_text_block` | function | `gui/browser_ui.c:5641` | `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,                  ...` |
| `flush_line` | function | `gui/browser_ui.c:4758` | `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)` |
| `foldback_session_cookies` | function | `gui/browser_ui.c:2786` | `static void foldback_session_cookies(const char *url, const char *jar)` |
| `font_size` | type_alias | `gui/browser_ui.c:3825` | `typedef struct rc_frag { double x, width, font_size;` |
| `frag_at_point` | function | `gui/browser_ui.c:17508` | `static dom_node_id frag_at_point(browser_window *w, double px, double py,                        ...` |
| `frag_hold_check` | function | `gui/browser_ui.c:17715` | `static void frag_hold_check(browser_window *w)` |
| `frag_styled` | function | `gui/browser_ui.c:4514` | `static int frag_styled(const rc_frag *f)` |
| `fragment` | function | `gui/browser_ui.c:14363` | `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using  * blk->block_id alo...` |
| `frame_undo` | struct | `gui/browser_ui.c:16347` | `` |
| `frame_undo_restore` | function | `gui/browser_ui.c:16353` | `static void frame_undo_restore(rc_layout *L, frame_undo *u)` |
| `frames_apply` | function | `gui/browser_ui.c:17909` | `static void frames_apply(browser_window *w, const tab_page *page)` |
| `frames_drain` | function | `gui/browser_ui.c:17891` | `static void frames_drain(browser_window *w)` |
| `free_images` | function | `gui/browser_ui.c:1330` | `static void free_images(browser_window *w)` |
| `free_inputs` | function | `gui/browser_ui.c:1322` | `static void free_inputs(browser_window *w)` |
| `free_live_page` | function | `gui/browser_ui.c:3376` | `static void free_live_page(browser_window *w)` |
| `freebug_complete` | function | `gui/browser_ui.c:20046` | `static void freebug_complete(browser_window *w)` |
| `freebug_copy_console` | function | `gui/browser_ui.c:20867` | `static void freebug_copy_console(browser_window *w)` |
| `freebug_destroy` | function | `gui/browser_ui.c:19871` | `static void freebug_destroy(browser_window *w)` |
| `freebug_ensure_buffer` | function | `gui/browser_ui.c:19427` | `static int freebug_ensure_buffer(freebug_window *fb)` |
| `freebug_eval` | function | `gui/browser_ui.c:19995` | `static void freebug_eval(browser_window *w)` |
| `freebug_handle_key` | function | `gui/browser_ui.c:20076` | `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,                              ...` |
| `freebug_hide` | function | `gui/browser_ui.c:19793` | `static void freebug_hide(browser_window *w)` |
| `freebug_is_open` | function | `gui/browser_ui.c:19884` | `static int freebug_is_open(const browser_window *w)` |
| `freebug_owns_surface` | function | `gui/browser_ui.c:19880` | `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)` |
| `freebug_paint` | function | `gui/browser_ui.c:19568` | `static void freebug_paint(freebug_window *fb)` |
| `freebug_pane_refresh` | function | `gui/browser_ui.c:19933` | `static void freebug_pane_refresh(browser_window *w)` |
| `freebug_panes_invalidate` | function | `gui/browser_ui.c:19988` | `static void freebug_panes_invalidate(browser_window *w)` |
| `freebug_pointer_axis` | function | `gui/browser_ui.c:20180` | `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)` |
| `freebug_pointer_button` | function | `gui/browser_ui.c:20129` | `static void freebug_pointer_button(browser_window *w, uint32_t serial,                           ...` |
| `freebug_pointer_motion` | function | `gui/browser_ui.c:20158` | `static void freebug_pointer_motion(browser_window *w)` |
| `freebug_redraw` | function | `gui/browser_ui.c:19789` | `static void freebug_redraw(browser_window *w)` |
| `freebug_redraw_fb` | function | `gui/browser_ui.c:19780` | `static void freebug_redraw_fb(freebug_window *fb)` |
| `freebug_repl_worker` | function | `gui/browser_ui.c:19891` | `static tab *freebug_repl_worker(browser_window *w)` |
| `freebug_set_editor` | function | `gui/browser_ui.c:20038` | `static void freebug_set_editor(freebug_window *fb, const char *s)` |
| `freebug_set_tab` | function | `gui/browser_ui.c:19970` | `static void freebug_set_tab(browser_window *w, int which)` |
| `freebug_show` | function | `gui/browser_ui.c:19836` | `static void freebug_show(browser_window *w)` |
| `freebug_toggle` | function | `gui/browser_ui.c:19866` | `static void freebug_toggle(browser_window *w)` |
| `freebug_window` | type_alias | `gui/browser_ui.c:744` | `typedef struct freebug_window freebug_window;` |
| `freebug_window` | struct | `gui/browser_ui.c:19389` | `` |
| `freedom_write_dir` | function | `gui/browser_ui.c:945` | `static int freedom_write_dir(char *out, size_t cap)` |
| `geom_from_layout` | function | `gui/browser_ui.c:15687` | `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,                 ...` |
| `go_omnibox` | function | `gui/browser_ui.c:20288` | `static void go_omnibox(browser_window *w)` |
| `grad_stop` | function | `gui/browser_ui.c:13285` | `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)` |
| `gui_async_fetch` | function | `gui/browser_ui.c:1930` | `static int gui_async_fetch(void *vctx, const char *method, const char *url,                      ...` |
| `gui_css_sink` | function | `gui/browser_ui.c:1977` | `static void gui_css_sink(void *vctx, const char *url,                          const char *body, ...` |
| `gui_frame_top_msg` | function | `gui/browser_ui.c:17878` | `static void gui_frame_top_msg(void *ctx, const char *data, size_t len)` |
| `gui_is_idle` | function | `gui/browser_ui.c:21883` | `static int gui_is_idle(const browser_window *w)` |
| `gui_navigate` | function | `gui/browser_ui.c:18030` | `static browser_status gui_navigate(browser_window *w, const char *url)` |
| `gui_net_ctx` | struct | `gui/browser_ui.c:1890` | `` |
| `gui_net_ctx_free` | function | `gui/browser_ui.c:1898` | `static void gui_net_ctx_free(void *p)` |
| `gui_net_ctx_new` | function | `gui/browser_ui.c:1906` | `static gui_net_ctx *gui_net_ctx_new(browser_window *w)` |
| `gui_net_ctx_retire` | function | `gui/browser_ui.c:1923` | `static void gui_net_ctx_retire(gui_net_ctx *c)` |
| `gui_prof_log` | function | `gui/browser_ui.c:16198` | `static void gui_prof_log(const char *what, double ms)` |
| `gui_prof_now_ms` | function | `gui/browser_ui.c:16193` | `static double gui_prof_now_ms(void)` |
| `gui_quiesce` | function | `gui/browser_ui.c:18153` | `static void gui_quiesce(browser_window *w)` |
| `gui_sub_perform` | function | `gui/browser_ui.c:1844` | `static int gui_sub_perform(gui_sub_prep *p, const char *method, const void *body, size_t body_len...` |
| `gui_sub_prep` | struct | `gui/browser_ui.c:1796` | `` |
| `gui_sub_prepare` | function | `gui/browser_ui.c:1803` | `static int gui_sub_prepare(browser_window *w, const char *top, int trusted, int top_allowed,     ...` |
| `gui_subresource_fetch` | function | `gui/browser_ui.c:1873` | `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,                ...` |
| `gui_timing_step` | function | `gui/browser_ui.c:21894` | `static int gui_timing_step(browser_window *w, uint64_t now)` |
| `gui_viewport_w` | function | `gui/browser_ui.c:2836` | `static int gui_viewport_w(const browser_window *w)` |
| `gutter` | function | `gui/browser_ui.c:765` | `* gutter (content_margin) is intentionally left unzoomed, like a browser's text  * zoom. The PDF ...` |
| `h` | type_alias | `gui/browser_ui.c:3916` | `typedef struct rc_box { double x, top, w, h;` |
| `handle_key_press` | function | `gui/browser_ui.c:21310` | `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,              ...` |
| `have` | function | `gui/browser_ui.c:10880` | `* as they always have (spec/float.md §6b.3). The line still open beside * the previous float is committed first, at...` |
| `hb_is_allowlisted` | function | `gui/browser_ui.c:2109` | `&& hb_is_allowlisted(w->hosts, ihost);` |
| `history_step` | function | `gui/browser_ui.c:17973` | `static void history_step(browser_window *w, int steps)` |
| `hit_layout` | function | `gui/browser_ui.c:17253` | `static const rc_layout *hit_layout(cairo_t *cr, browser_window *w, double content_w,             ...` |
| `hit_layout_done` | function | `gui/browser_ui.c:17263` | `static void hit_layout_done(rc_layout *own, int owned)` |
| `host_from_url` | function | `gui/browser_ui.c:1257` | `static int host_from_url(const char *url, char *out, size_t outsz)` |

Next: [SYMBOLS_p2.md](SYMBOLS_p2.md)
