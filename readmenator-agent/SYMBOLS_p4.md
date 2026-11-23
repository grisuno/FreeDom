# Symbols (page 4 of 18)
Previous: [SYMBOLS_p3.md](SYMBOLS_p3.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `dom_get_attribute` | function | `include/dom.h:126` | `const char *dom_get_attribute(const dom_index *idx, dom_node_id node, const char *name, size_t *len);` |
| `dom_get_by_class` | function | `include/dom.h:67` | `size_t dom_get_by_class(const dom_index *idx, const char *cls, dom_node_id *out, size_t cap);` |
| `dom_index` | type_alias | `include/dom.h:40` | `typedef struct dom_index dom_index;` |
| `dom_matches` | function | `include/dom.h:96` | `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector);` |
| `dom_node_count` | function | `include/dom.h:51` | `size_t dom_node_count(const dom_index *idx);` |
| `dom_node_id` | type_alias | `include/dom.h:34` | `typedef uint32_t dom_node_id;` |
| `dom_node_kind` | function | `include/dom.h:219` | `int dom_node_kind(const dom_index *idx, dom_node_id node);` |
| `dom_place` | enum | `include/dom.h:194` | `` |
| `dom_precedes` | function | `include/dom.h:109` | `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);` |
| `dom_status` | enum | `include/dom.h:26` | `` |
| `dom_tag_name` | function | `include/dom.h:123` | `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);` |
| `dom_text_content` | function | `include/dom.h:138` | `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len);` |
| `index` | function | `include/dom.h:235` | `* stays valid in the index (not freed). Invalid handle / not-a-child => DOM_ERR_NULL_ARG. */ dom_status...` |
| `length` | function | `include/dom.h:260` | `* length (no children => an owned empty string). Uses a chain of fixed-size * blocks internally so there is no hard...` |
| `parent` | function | `include/dom.h:203` | `* child of parent (for the *_REF places) or an invalid handle => DOM_ERR_NULL_ARG. */ dom_status...` |
| `process` | function | `include/dom.h:267` | `* modules in the same process (style resolution). NULL for a bad or non-element * handle. Valid until the next...` |
| `sight` | function | `include/dom.h:272` | `* first sight (an innerHTML subtree has no handles until something asks). Registration * is not a tree change...` |
| `tree` | function | `include/dom.h:59` | `* tree (the index only grows, so a node a script removed is still registered and must not be * found);` |
| `valid` | function | `include/dom.h:146` | `* detached node stays valid (it just becomes unreachable from the root and is no * longer rendered). These never...` |
| `DD_FIELD_MAX` | macro | `include/dom_debug.h:28` | `#define DD_FIELD_MAX` |
| `FREEDOM_DOM_DEBUG_H` | macro | `include/dom_debug.h:2` | `#define FREEDOM_DOM_DEBUG_H` |
| `dd_format` | function | `include/dom_debug.h:36` | `size_t dd_format(const rd_doc *doc, char *out, size_t cap);` |
| `dd_format_css` | function | `include/dom_debug.h:41` | `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap);` |
| `DL_ERR_OVERFLOW` | function | `include/download.h:56` | `* DL_ERR_OVERFLOW (out left empty). url/content_disposition NULL => absent. */ dl_status dl_pick_name(const char...` |
| `DL_FALLBACK_NAME` | macro | `include/download.h:30` | `#define DL_FALLBACK_NAME` |
| `DL_MAX_BYTES` | macro | `include/download.h:31` | `#define DL_MAX_BYTES` |
| `DL_NAME_MAX` | macro | `include/download.h:29` | `#define DL_NAME_MAX` |
| `FREEDOM_DOWNLOAD_H` | macro | `include/download.h:2` | `#define FREEDOM_DOWNLOAD_H` |
| `basename` | function | `include/download.h:61` | `* sanitized basename (a name still containing '/' is rejected => DL_ERR_OVERFLOW, * so the path can never escape...` |
| `dl_should_download` | function | `include/download.h:43` | `int dl_should_download(const char *content_type, const char *content_disposition);` |
| `dl_status` | enum | `include/download.h:33` | `` |
| `literal` | function | `include/download.h:47` | `* a static string literal (never freed). */ const char *dl_ext_for_type(const char *content_type);` |
| `EK_MAX_BYTES` | macro | `include/exact_key.h:15` | `#define EK_MAX_BYTES` |
| `FREEDOM_EXACT_KEY_H` | macro | `include/exact_key.h:2` | `#define FREEDOM_EXACT_KEY_H` |
| `ek_equal` | function | `include/exact_key.h:34` | `int ek_equal(const ek_key *a, const ek_key *b);` |
| `ek_free` | function | `include/exact_key.h:40` | `void ek_free(ek_key *k);` |
| `ek_init` | function | `include/exact_key.h:24` | `void ek_init(ek_key *k);` |
| `ek_key` | struct | `include/exact_key.h:17` | `` |
| `ek_put` | function | `include/exact_key.h:31` | `void ek_put(ek_key *k, const void *p, size_t len);` |
| `ek_reset` | function | `include/exact_key.h:27` | `void ek_reset(ek_key *k);` |
| `ek_swap` | function | `include/exact_key.h:37` | `void ek_swap(ek_key *a, ek_key *b);` |
| `FBC_BASE_MAX` | macro | `include/fb_cmdline.h:17` | `#define FBC_BASE_MAX` |
| `FBC_ENTRY_MAX` | macro | `include/fb_cmdline.h:16` | `#define FBC_ENTRY_MAX` |
| `FBC_HIST_MAX` | macro | `include/fb_cmdline.h:15` | `#define FBC_HIST_MAX` |
| `FBC_LIST_NAMES` | macro | `include/fb_cmdline.h:18` | `#define FBC_LIST_NAMES` |
| `FREEDOM_FB_CMDLINE_H` | macro | `include/fb_cmdline.h:2` | `#define FREEDOM_FB_CMDLINE_H` |
| `fbc_complete_pick` | function | `include/fb_cmdline.h:51` | `size_t fbc_complete_pick(const char *names, const char *prefix, size_t plen, char *ins, size_t ins_cap, char *list...` |
| `fbc_complete_split` | function | `include/fb_cmdline.h:42` | `long fbc_complete_split(const char *text, size_t n, char *base, size_t cap, size_t *prefix_off);` |
| `fbc_filter` | enum | `include/fb_cmdline.h:54` | `` |
| `fbc_filter_label` | function | `include/fb_cmdline.h:64` | `const char *fbc_filter_label(int filter);` |
| `fbc_filter_next` | function | `include/fb_cmdline.h:63` | `int fbc_filter_next(int filter);` |
| `fbc_filter_passes` | function | `include/fb_cmdline.h:62` | `int fbc_filter_passes(int filter, int level);` |
| `fbc_history` | struct | `include/fb_cmdline.h:20` | `` |
| `fbc_history_free` | function | `include/fb_cmdline.h:28` | `void fbc_history_free(fbc_history *h);` |
| `fbc_history_init` | function | `include/fb_cmdline.h:27` | `void fbc_history_init(fbc_history *h);` |
| `fbc_history_next` | function | `include/fb_cmdline.h:38` | `const char *fbc_history_next(fbc_history *h);` |
| `fbc_history_prev` | function | `include/fb_cmdline.h:35` | `const char *fbc_history_prev(fbc_history *h, const char *cur, size_t curlen);` |
| `fbc_history_push` | function | `include/fb_cmdline.h:31` | `int fbc_history_push(fbc_history *h, const char *text, size_t len);` |
| `fbc_names_expr` | function | `include/fb_cmdline.h:46` | `size_t fbc_names_expr(const char *base, char *out, size_t cap);` |
| `FBP_EXPR_MAX` | macro | `include/fb_panes.h:31` | `#define FBP_EXPR_MAX` |
| `FBP_SELECTOR_MAX` | macro | `include/fb_panes.h:30` | `#define FBP_SELECTOR_MAX` |
| `FREEDOM_FB_PANES_H` | macro | `include/fb_panes.h:2` | `#define FREEDOM_FB_PANES_H` |
| `fbp_expr` | function | `include/fb_panes.h:57` | `size_t fbp_expr(int tab, const char *sel, size_t n, char *out, size_t cap);` |
| `fbp_is_pane` | function | `include/fb_panes.h:49` | `int fbp_is_pane(int tab);` |
| `fbp_js_quote` | function | `include/fb_panes.h:53` | `size_t fbp_js_quote(const char *s, size_t n, char *out, size_t cap);` |
| `fbp_tab` | enum | `include/fb_panes.h:17` | `` |
| `fbp_tab_at` | function | `include/fb_panes.h:46` | `int fbp_tab_at(double x, double cell_w, double pad_cells);` |
| `fbp_tab_from_name` | function | `include/fb_panes.h:37` | `int fbp_tab_from_name(const char *name);` |
| `fbp_tab_label` | function | `include/fb_panes.h:34` | `const char *fbp_tab_label(int tab);` |
| `fbp_tab_span` | function | `include/fb_panes.h:43` | `void fbp_tab_span(int tab, double cell_w, double pad_cells, double *x, double *w);` |
| `fbp_tab_wrap` | function | `include/fb_panes.h:40` | `int fbp_tab_wrap(int tab, int dir);` |
| `FREEDOM_FIND_TEXT_H` | macro | `include/find_text.h:8` | `#define FREEDOM_FIND_TEXT_H` |
| `FT_MATCH_MAX` | macro | `include/find_text.h:18` | `#define FT_MATCH_MAX` |
| `FT_QUERY_MAX` | macro | `include/find_text.h:17` | `#define FT_QUERY_MAX` |
| `end` | type_alias | `include/find_text.h:31` | `typedef struct ft_match { ft_pos start, end;` |
| `exist` | function | `include/find_text.h:42` | `* cap matches exist (truncated may be NULL). */ ft_status ft_search(const ft_piece *pieces, size_t n, const uint32_t...` |
| `find_text` | function | `include/find_text.h:2` | `* find_text (ft_) -- find in page over the rendered text (spec/find_text.md). * * Pure: no I/O, no global state...` |
| `ft_compile` | function | `include/find_text.h:39` | `size_t ft_compile(const char *q, size_t qlen, uint32_t *out, size_t cap);` |
| `ft_fold` | function | `include/find_text.h:35` | `uint32_t ft_fold(uint32_t cp);` |
| `ft_match` | struct | `include/find_text.h:31` | `` |
| `ft_piece` | struct | `include/find_text.h:24` | `` |
| `ft_pos` | struct | `include/find_text.h:30` | `` |
| `ft_span` | struct | `include/find_text.h:32` | `` |
| `ft_spans` | function | `include/find_text.h:48` | `size_t ft_spans(const ft_piece *pieces, size_t n, const ft_match *m, size_t nm, ft_span *out, size_t cap);` |
| `ft_status` | enum | `include/find_text.h:20` | `` |
| `ft_step` | function | `include/find_text.h:53` | `long ft_step(long cur, size_t n, int dir);` |
| `match` | type_alias | `include/find_text.h:32` | `typedef struct ft_span { size_t piece, start, end, match;` |
| `piece` | type_alias | `include/find_text.h:29` | `typedef struct ft_pos { size_t piece;` |
| `written` | function | `include/find_text.h:38` | `* number of code points written (<= cap, <= FT_QUERY_MAX);` |
| `FREEDOM_FLEX_LAYOUT_H` | macro | `include/flex_layout.h:2` | `#define FREEDOM_FLEX_LAYOUT_H` |
| `FX_AREA_MAX_CELLS` | macro | `include/flex_layout.h:148` | `#define FX_AREA_MAX_CELLS` |
| `FX_AREA_MAX_COLS` | macro | `include/flex_layout.h:147` | `#define FX_AREA_MAX_COLS` |
| `FX_AREA_MAX_ROWS` | macro | `include/flex_layout.h:146` | `#define FX_AREA_MAX_ROWS` |
| `FX_AREA_NAME_MAX` | macro | `include/flex_layout.h:149` | `#define FX_AREA_NAME_MAX` |
| `FX_ERR_NULL_ARG` | function | `include/flex_layout.h:238` | `* Returns FX_ERR_NULL_ARG (a required pointer NULL with n > 0), FX_ERR_RANGE * (negative h/avail, or n > FX_MAX_ITEMS);` |
| `FX_FLOAT_MIN_LINE` | macro | `include/flex_layout.h:218` | `#define FX_FLOAT_MIN_LINE` |
| `FX_GL_AUTO` | macro | `include/flex_layout.h:107` | `#define FX_GL_AUTO` |
| `FX_GL_LINE_MAX` | macro | `include/flex_layout.h:110` | `#define FX_GL_LINE_MAX` |
| `FX_GL_SPAN_BASE` | macro | `include/flex_layout.h:108` | `#define FX_GL_SPAN_BASE` |
| `FX_GL_SPAN_MAX` | macro | `include/flex_layout.h:109` | `#define FX_GL_SPAN_MAX` |
| `FX_GRID_COLS_MAX` | macro | `include/flex_layout.h:132` | `#define FX_GRID_COLS_MAX` |
| `FX_MAUTO_BOTTOM` | macro | `include/flex_layout.h:348` | `#define FX_MAUTO_BOTTOM` |
| `FX_MAUTO_TOP` | macro | `include/flex_layout.h:347` | `#define FX_MAUTO_TOP` |
| `FX_MAX_COLUMNS` | macro | `include/flex_layout.h:280` | `#define FX_MAX_COLUMNS` |
| `FX_MAX_ITEMS` | macro | `include/flex_layout.h:28` | `#define FX_MAX_ITEMS` |
| `basis` | type_alias | `include/flex_layout.h:40` | `typedef struct fx_item { double basis;` |
| `bottom` | type_alias | `include/flex_layout.h:224` | `typedef struct fx_float_rect { double top, bottom;` |
| `cols` | type_alias | `include/flex_layout.h:154` | `typedef struct fx_area_map { int rows, cols;` |
| `fx_area_map` | struct | `include/flex_layout.h:154` | `` |
| `fx_auto_min_size` | function | `include/flex_layout.h:275` | `double fx_auto_min_size(double min_content, double basis, double author_min, int scroll_container);` |
| `fx_autofill_count` | function | `include/flex_layout.h:129` | `size_t fx_autofill_count(double avail, double gap, double minw);` |
| `fx_cross_offset` | function | `include/flex_layout.h:364` | `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r);` |
| `fx_float_rect` | struct | `include/flex_layout.h:224` | `` |
| `fx_grid_area_hash` | function | `include/flex_layout.h:163` | `unsigned fx_grid_area_hash(const char *name);` |
| `fx_grid_cell` | function | `include/flex_layout.h:74` | `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col);` |
| `fx_grid_column_count` | function | `include/flex_layout.h:139` | `int fx_grid_column_count(int flow, int cols, int rows, size_t items);` |
| `fx_grid_line_parse` | function | `include/flex_layout.h:117` | `int fx_grid_line_parse(const char *v, int *start, int *end);` |
| `fx_grid_line_resolve` | function | `include/flex_layout.h:122` | `void fx_grid_line_resolve(int start, int end, int ntracks, int *pos0, int *span);` |
| `fx_item` | struct | `include/flex_layout.h:40` | `` |
| `fx_justify` | enum | `include/flex_layout.h:30` | `` |
| `fx_justify_name` | function | `include/flex_layout.h:331` | `const char *fx_justify_name(fx_justify j);` |
| `fx_result` | struct | `include/flex_layout.h:48` | `` |
| `fx_status` | enum | `include/flex_layout.h:53` | `` |
| `height` | function | `include/flex_layout.h:337` | `* used height (h_out);` |
| `it` | function | `include/flex_layout.h:354` | `* children that claim it (spec/flex_layout.md, tanda 44): proportionally to * grow[i] (x100) when any grows, else...` |
| `number` | function | `include/flex_layout.h:106` | `* line number (negative counts from the end). */ #define FX_GL_AUTO 0 #define FX_GL_SPAN_BASE (1 << 20) #define...` |
| `offset` | function | `include/flex_layout.h:181` | `* offset (from the content start, clamped to >= 0) to out_x[n]. The band does NOT wrap * (v1): an item that would...` |
| `out` | function | `include/flex_layout.h:62` | `* fx_result to out (caller-owned). n == 0 is a no-op (out may be NULL). */ fx_status fx_flex_line(const fx_item...` |
| `pos` | type_alias | `include/flex_layout.h:48` | `typedef struct fx_result { double pos;` |
| `required` | function | `include/flex_layout.h:194` | `* out_row is required (NULL with n > 0 yields FX_ERR_NULL_ARG);` |
| `size` | function | `include/flex_layout.h:60` | `* content size (px);` |
| `space` | function | `include/flex_layout.h:244` | `* line order: positive free space (avail - sizes - gaps) is split equally among every * auto margin...` |
| `widths` | function | `include/flex_layout.h:204` | `* the OUTER widths (width + ml + mr, clamped >= 0, so a negative margin narrows * the slot and a positive one widens...` |
| `win` | function | `include/flex_layout.h:362` | `* margins win (both = centre, left only = end);` |
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
| `FBK_MAX_DEPTH` | macro | `include/frame_broker.h:17` | `#define FBK_MAX_DEPTH` |
| `FBK_MAX_FRAMES` | macro | `include/frame_broker.h:16` | `#define FBK_MAX_FRAMES` |
| `FBK_MAX_MSG` | macro | `include/frame_broker.h:18` | `#define FBK_MAX_MSG` |
| `FBK_ORIGIN_MAX` | macro | `include/frame_broker.h:19` | `#define FBK_ORIGIN_MAX` |
| `FBK_URL_MAX` | macro | `include/frame_broker.h:20` | `#define FBK_URL_MAX` |
| `FREEDOM_FRAME_BROKER_H` | macro | `include/frame_broker.h:2` | `#define FREEDOM_FRAME_BROKER_H` |
| `f` | type_alias | `include/frame_broker.h:37` | `typedef struct fbk_table { fbk_frame f[FBK_MAX_FRAMES];` |
| `fbk_add` | function | `include/frame_broker.h:49` | `int fbk_add(fbk_table *t, int parent, const char *url, int *out_id);` |
| `fbk_frame` | struct | `include/frame_broker.h:31` | `` |
| `fbk_init` | function | `include/frame_broker.h:45` | `int fbk_init(fbk_table *t, const char *top_url);` |
| `fbk_origin` | function | `include/frame_broker.h:55` | `const char *fbk_origin(const fbk_table *t, int id);` |
| `fbk_origin_of` | function | `include/frame_broker.h:42` | `int fbk_origin_of(const char *url, char *out, size_t cap);` |
| `fbk_rel` | enum | `include/frame_broker.h:22` | `` |
| `fbk_remove` | function | `include/frame_broker.h:52` | `void fbk_remove(fbk_table *t, int id);` |
| `fbk_table` | struct | `include/frame_broker.h:38` | `` |
| `fbk_verdict` | enum | `include/frame_broker.h:24` | `` |
| `used` | type_alias | `include/frame_broker.h:30` | `typedef struct fbk_frame { int used;` |
| `FREEDOM_FRAME_CLOCK_H` | macro | `include/frame_clock.h:2` | `#define FREEDOM_FRAME_CLOCK_H` |
| `active` | type_alias | `include/frame_clock.h:14` | `typedef struct fc_clock { int active;` |
| `fc_clock` | struct | `include/frame_clock.h:15` | `` |
| `fc_init` | function | `include/frame_clock.h:20` | `void fc_init(fc_clock *c);` |
| `fc_interval_ms` | function | `include/frame_clock.h:23` | `int fc_interval_ms(const fc_clock *c);` |
| `fc_needs_tick` | function | `include/frame_clock.h:22` | `int fc_needs_tick(const fc_clock *c);` |
| `fc_set_active` | function | `include/frame_clock.h:21` | `void fc_set_active(fc_clock *c, int active);` |
| `FH_MAX_DEPTH` | macro | `include/frame_host.h:18` | `#define FH_MAX_DEPTH` |
| `FH_POLL_MS` | macro | `include/frame_host.h:19` | `#define FH_POLL_MS` |
| `FREEDOM_FRAME_HOST_H` | macro | `include/frame_host.h:2` | `#define FREEDOM_FRAME_HOST_H` |
| `fh_apply_top` | function | `include/frame_host.h:43` | `void fh_apply_top(fh_host *h, const tab_page *page);` |
| `fh_count` | function | `include/frame_host.h:50` | `int fh_count(const fh_host *h);` |
| `fh_frame_view` | function | `include/frame_host.h:56` | `const pv_view *fh_frame_view(const fh_host *h, const char *url, tab **t_out);` |
| `fh_free` | function | `include/frame_host.h:39` | `void fh_free(fh_host *h);` |
| `fh_generation` | function | `include/frame_host.h:59` | `unsigned fh_generation(const fh_host *h);` |
| `fh_host` | type_alias | `include/frame_host.h:20` | `typedef struct fh_host fh_host;` |
| `fh_new` | function | `include/frame_host.h:29` | `fh_host *fh_new(const char *top_url, tab_fetch_fn fetch, void *fetch_ctx, fh_top_msg_fn top_msg, void *top_ctx);` |
| `fh_set_async` | function | `include/frame_host.h:35` | `void fh_set_async(fh_host *h, int on);` |
| `fh_tick` | function | `include/frame_host.h:47` | `int fh_tick(fh_host *h, int elapsed_ms);` |
| `it` | function | `include/frame_host.h:53` | `* confined worker last built it (NULL when no live frame has that URL);` |
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
| `truncated` | function | `include/freebug.h:69` | `* A message longer than FB_MAX_ENTRY_BYTES is stored truncated (not dropped). A * dropped push raises b->overflow...` |
| `FC_FLEX_MEASURE_W` | macro | `include/freedom_config.h:45` | `#define FC_FLEX_MEASURE_W` |
| `FC_FLEX_MIN_MEASURE_W` | macro | `include/freedom_config.h:51` | `#define FC_FLEX_MIN_MEASURE_W` |
| `FC_FONT_CHAIN_MAX` | macro | `include/freedom_config.h:56` | `#define FC_FONT_CHAIN_MAX` |
| `FC_FONT_FALLBACK_PX` | macro | `include/freedom_config.h:66` | `#define FC_FONT_FALLBACK_PX` |
| `FC_HEADLESS_VIEW_H` | macro | `include/freedom_config.h:24` | `#define FC_HEADLESS_VIEW_H` |
| `FC_LAZY_IMAGE_MARGIN_PX` | macro | `include/freedom_config.h:99` | `#define FC_LAZY_IMAGE_MARGIN_PX` |
| `FC_MASK_CACHE_BYTES` | macro | `include/freedom_config.h:95` | `#define FC_MASK_CACHE_BYTES` |
| `FC_MASK_CACHE_ENTRIES` | macro | `include/freedom_config.h:96` | `#define FC_MASK_CACHE_ENTRIES` |
| `FC_MAX_AUTHOR_CSS_BYTES` | macro | `include/freedom_config.h:78` | `#define FC_MAX_AUTHOR_CSS_BYTES` |
| `FC_MAX_BOXES` | macro | `include/freedom_config.h:61` | `#define FC_MAX_BOXES` |
| `FC_NET_LOAD_SETTLE_MS` | macro | `include/freedom_config.h:112` | `#define FC_NET_LOAD_SETTLE_MS` |
| `FC_NET_POLL_MS` | macro | `include/freedom_config.h:113` | `#define FC_NET_POLL_MS` |
| `FC_NET_TICK_SETTLE_MS` | macro | `include/freedom_config.h:116` | `#define FC_NET_TICK_SETTLE_MS` |
| `FC_PNG_MARGIN` | macro | `include/freedom_config.h:34` | `#define FC_PNG_MARGIN` |
| `FC_PNG_MAX_H` | macro | `include/freedom_config.h:39` | `#define FC_PNG_MAX_H` |
| `FC_PNG_PAGE_W` | macro | `include/freedom_config.h:20` | `#define FC_PNG_PAGE_W` |
| `FC_SHC_MAX_QUERIES` | macro | `include/freedom_config.h:90` | `#define FC_SHC_MAX_QUERIES` |
| `FC_SHC_MAX_TEXT_BYTES` | macro | `include/freedom_config.h:84` | `#define FC_SHC_MAX_TEXT_BYTES` |
| `FC_TABLE_TRACK_MAX_PX` | macro | `include/freedom_config.h:120` | `#define FC_TABLE_TRACK_MAX_PX` |
| `FC_TAB_OP_NET_BUDGET_MS` | macro | `include/freedom_config.h:105` | `#define FC_TAB_OP_NET_BUDGET_MS` |
| `FC_TRUSTED_JS_BUDGET_MS` | macro | `include/freedom_config.h:30` | `#define FC_TRUSTED_JS_BUDGET_MS` |
| `FC_UI_FONT_SIZE` | macro | `include/freedom_config.h:70` | `#define FC_UI_FONT_SIZE` |
| `FREEDOM_CONFIG_H` | macro | `include/freedom_config.h:14` | `#define FREEDOM_CONFIG_H` |
| `FREEDOM_HLS_H` | macro | `include/hls.h:2` | `#define FREEDOM_HLS_H` |
| `HLS_MAX_MIRRORS` | macro | `include/hls.h:83` | `#define HLS_MAX_MIRRORS` |
| `domain` | function | `include/hls.h:87` | `* domain (everything after the first label). Writes NUL-terminated into out and * returns the length, or 0 when...` |
| `hls_playlist` | struct | `include/hls.h:45` | `` |
| `hls_playlist_free` | function | `include/hls.h:74` | `void hls_playlist_free(hls_playlist *pl);` |
| `hls_segment` | struct | `include/hls.h:29` | `` |
| `hls_select_variant` | function | `include/hls.h:65` | `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h);` |
| `hls_status` | enum | `include/hls.h:21` | `` |
| `hls_variant` | struct | `include/hls.h:36` | `` |
| `media` | function | `include/hls.h:77` | `* media (non-2xx status, HTML/text error body, empty). Recognises MPEG-TS (also * behind a fake image prefix, probed...` |
| `resolved` | function | `include/hls.h:68` | `* Writes the absolute URL into resolved (bounded by resolved_sz). Returns the * written length, or 0 on failure. */...` |
| `FREEDOM_HOST_CONF_H` | macro | `include/host_conf.h:2` | `#define FREEDOM_HOST_CONF_H` |
| `HCF_MAX_DIRS` | macro | `include/host_conf.h:15` | `#define HCF_MAX_DIRS` |
| `HCF_MAX_FILE_BYTES` | macro | `include/host_conf.h:18` | `#define HCF_MAX_FILE_BYTES` |
| `HCF_PATH_MAX` | macro | `include/host_conf.h:16` | `#define HCF_PATH_MAX` |
| `hcf_dirs` | struct | `include/host_conf.h:20` | `` |
| `hcf_load_allowlist` | function | `include/host_conf.h:39` | `hb_set *hcf_load_allowlist(const hcf_dirs *dirs, const char *fname);` |
| `hcf_load_filter` | function | `include/host_conf.h:35` | `hb_set *hcf_load_filter(const hcf_dirs *dirs);` |
| `hcf_search_dirs` | function | `include/host_conf.h:28` | `void hcf_search_dirs(const char *env, const char *home, hcf_dirs *out);` |
| `hcf_search_dirs_from_env` | function | `include/host_conf.h:31` | `void hcf_search_dirs_from_env(hcf_dirs *out);` |
| `FREEDOM_HOSTBLOCK_H` | macro | `include/hostblock.h:2` | `#define FREEDOM_HOSTBLOCK_H` |
| `hb_count` | function | `include/hostblock.h:85` | `size_t hb_count(const hb_set *s, hb_list list);` |
| `hb_decision` | enum | `include/hostblock.h:37` | `` |
| `hb_free` | function | `include/hostblock.h:52` | `void hb_free(hb_set *s);` |
| `hb_is_allowlisted` | function | `include/hostblock.h:75` | `int hb_is_allowlisted(const hb_set *s, const char *host);` |
| `hb_list` | enum | `include/hostblock.h:32` | `` |
| `hb_new` | function | `include/hostblock.h:49` | `hb_set *hb_new(void);` |
| `hb_set` | type_alias | `include/hostblock.h:29` | `typedef struct hb_set hb_set;` |
| `hb_status` | enum | `include/hostblock.h:42` | `` |
| `walked` | function | `include/hostblock.h:65` | `* walked (the host, then without its first label, ...): any suffix on the allowlist * => HB_ALLOW (allow wins...` |
| `FREEDOM_HOSTEDIT_H` | macro | `include/hostedit.h:2` | `#define FREEDOM_HOSTEDIT_H` |
| `HE_MAX_HOST` | macro | `include/hostedit.h:32` | `#define HE_MAX_HOST` |
| `he_cdn_kind` | function | `include/hostedit.h:62` | `he_cdn_kind_t he_cdn_kind(const char *url);` |
| `he_cdn_kind_t` | enum | `include/hostedit.h:61` | `` |
| `he_status` | enum | `include/hostedit.h:24` | `` |
| `he_suggest` | function | `include/hostedit.h:55` | `int he_suggest(const char *text, const char *query, char results[][HE_MAX_HOST + 1], int max);` |
| `he_text_has_host` | function | `include/hostedit.h:46` | `int he_text_has_host(const char *text, const char *host);` |
| `FREEDOM_HTML_PARSE_H` | macro | `include/html_parse.h:2` | `#define FREEDOM_HTML_PARSE_H` |
| `HP_DEFAULT_MAX_BYTES` | macro | `include/html_parse.h:41` | `#define HP_DEFAULT_MAX_BYTES` |
| `HP_MAX_SCRIPTS` | macro | `include/html_parse.h:48` | `#define HP_MAX_SCRIPTS` |
| `HP_MAX_STYLESHEETS` | macro | `include/html_parse.h:115` | `#define HP_MAX_STYLESHEETS` |
| `cfg` | function | `include/html_parse.h:57` | `* policy in cfg (cfg == NULL => secure defaults). No script is ever executed. * html == NULL or out == NULL =>...` |
| `dropped` | function | `include/html_parse.h:47` | `* dropped (not executed). */ #define HP_MAX_SCRIPTS ((size_t)4096) /* Returns a configuration with the secure...` |
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
| `modules` | function | `include/html_parse.h:94` | `* ES modules (import/export cannot run as a classic script), and template blocks * (text/x-jquery-tmpl, text/html...` |
| `src` | function | `include/html_parse.h:90` | `* carry their raw src (a <script src> with an inline body lists ONLY the src -- * browser rule: when src is present...` |
| `FREEDOM_HTTP_CACHE_H` | macro | `include/http_cache.h:2` | `#define FREEDOM_HTTP_CACHE_H` |
| `HC_HEURISTIC_CAP` | macro | `include/http_cache.h:26` | `#define HC_HEURISTIC_CAP` |
| `HC_MAX_ENTRY` | macro | `include/http_cache.h:23` | `#define HC_MAX_ENTRY` |
| `HC_MAX_TOTAL` | macro | `include/http_cache.h:24` | `#define HC_MAX_TOTAL` |
| `HC_REDIRECT_TTL` | macro | `include/http_cache.h:25` | `#define HC_REDIRECT_TTL` |
| `HC_TYPE_MAX` | macro | `include/http_cache.h:22` | `#define HC_TYPE_MAX` |
| `HC_URL_MAX` | macro | `include/http_cache.h:21` | `#define HC_URL_MAX` |
| `HC_VAL_MAX` | macro | `include/http_cache.h:20` | `#define HC_VAL_MAX` |
| `by` | function | `include/http_cache.h:59` | `* something to reuse it by (validator, max-age or Expires). */ int hc_storable(long http_code, const hc_meta *m...` |
| `final_url` | type_alias | `include/http_cache.h:43` | `typedef struct hc_meta { char final_url[HC_URL_MAX];` |
| `hc_body_free` | function | `include/http_cache.h:78` | `void hc_body_free(uint8_t *body, size_t len);` |
| `hc_class` | enum | `include/http_cache.h:38` | `` |
| `hc_clear` | function | `include/http_cache.h:84` | `void hc_clear(hc_store *s);` |
| `hc_close` | function | `include/http_cache.h:72` | `void hc_close(hc_store *s);` |
| `hc_lifetime` | function | `include/http_cache.h:63` | `long hc_lifetime(const hc_meta *m);` |
| `hc_meta` | struct | `include/http_cache.h:44` | `` |
| `hc_parse_http_date` | function | `include/http_cache.h:56` | `time_t hc_parse_http_date(const char *s);` |
| `hc_status` | enum | `include/http_cache.h:28` | `` |
| `hc_store` | type_alias | `include/http_cache.h:66` | `typedef struct hc_store hc_store;` |
| `FREEDOM_IDENTITY_H` | macro | `include/identity.h:2` | `#define FREEDOM_IDENTITY_H` |
| `IDN_GEO_ACC_MAX` | macro | `include/identity.h:23` | `#define IDN_GEO_ACC_MAX` |
| `IDN_GEO_ACC_MIN` | macro | `include/identity.h:22` | `#define IDN_GEO_ACC_MIN` |
| `IDN_LANG_MAX` | macro | `include/identity.h:17` | `#define IDN_LANG_MAX` |
| `IDN_LANG_TAGS_MAX` | macro | `include/identity.h:18` | `#define IDN_LANG_TAGS_MAX` |
| `IDN_PAGE_MAX` | macro | `include/identity.h:20` | `#define IDN_PAGE_MAX` |
| `IDN_SERIAL_MAX` | macro | `include/identity.h:19` | `#define IDN_SERIAL_MAX` |
| `IDN_UA_MAX` | macro | `include/identity.h:16` | `#define IDN_UA_MAX` |
| `idn_accept_language` | function | `include/identity.h:63` | `size_t idn_accept_language(const idn_config *c, char *out, size_t cap);` |
| `idn_apply_query` | function | `include/identity.h:75` | `unsigned idn_apply_query(idn_config *c, const char *query);` |
| `idn_clear_geo` | function | `include/identity.h:59` | `void idn_clear_geo(idn_config *c);` |
| `idn_config` | struct | `include/identity.h:37` | `` |
| `idn_defaults` | function | `include/identity.h:50` | `void idn_defaults(idn_config *c);` |
| `idn_geo_mode` | enum | `include/identity.h:25` | `` |
| `idn_is_default` | function | `include/identity.h:53` | `int idn_is_default(const idn_config *c);` |
| `idn_parse` | function | `include/identity.h:72` | `void idn_parse(idn_config *c, const char *text);` |
| `idn_primary_language` | function | `include/identity.h:64` | `size_t idn_primary_language(const idn_config *c, char *out, size_t cap);` |
| `idn_render_page` | function | `include/identity.h:78` | `size_t idn_render_page(const idn_config *c, char *out, size_t cap);` |
| `idn_serialize` | function | `include/identity.h:68` | `size_t idn_serialize(const idn_config *c, char *out, size_t cap);` |
| `idn_set_geo` | function | `include/identity.h:58` | `int idn_set_geo(idn_config *c, double lat, double lon, double accuracy_m);` |
| `idn_set_languages` | function | `include/identity.h:57` | `int idn_set_languages(idn_config *c, const char *list);` |
| `idn_set_user_agent` | function | `include/identity.h:56` | `int idn_set_user_agent(idn_config *c, const char *ua);` |
| `idn_user_agent` | function | `include/identity.h:62` | `const char *idn_user_agent(const idn_config *c);` |
| `user_agent` | type_alias | `include/identity.h:36` | `typedef struct idn_config { char user_agent[IDN_UA_MAX];` |
| `FREEDOM_IMAGE_DECODE_H` | macro | `include/image_decode.h:2` | `#define FREEDOM_IMAGE_DECODE_H` |
| `IMG_MAX_DIM` | macro | `include/image_decode.h:71` | `#define IMG_MAX_DIM` |
| `IMG_MAX_PIXELS` | macro | `include/image_decode.h:72` | `#define IMG_MAX_PIXELS` |
| `IMG_MAX_SCALE` | macro | `include/image_decode.h:67` | `#define IMG_MAX_SCALE` |
| `decode` | function | `include/image_decode.h:98` | `* the declared dimensions BEFORE the full decode (anti-bomb), decodes to RGB and * expands to BGRA. Rejects non-JPEG...` |
| `guards` | function | `include/image_decode.h:25` | `* guards (in-memory source only, longjmp error manager so a bad stream never * calls exit(), dimension caps before...` |
| `img_dimensions_ok` | function | `include/image_decode.h:84` | `int img_dimensions_ok(uint32_t w, uint32_t h);` |
| `img_format` | enum | `include/image_decode.h:33` | `` |
| `img_format_name` | function | `include/image_decode.h:130` | `const char *img_format_name(img_format f);` |
| `img_pixels` | struct | `include/image_decode.h:56` | `` |
| `img_pixels_free` | function | `include/image_decode.h:127` | `void img_pixels_free(img_pixels *p);` |
| `img_status` | enum | `include/image_decode.h:41` | `` |
| `inputs` | function | `include/image_decode.h:87` | `* Degenerate inputs (<= 0) yield (0,0). Pure. */ void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h...` |
| `width` | type_alias | `include/image_decode.h:56` | `typedef struct img_pixels { uint32_t width;` |
| `FREEDOM_IMPORT_MAP_H` | macro | `include/import_map.h:2` | `#define FREEDOM_IMPORT_MAP_H` |
| `IM_MAX_ENTRIES` | macro | `include/import_map.h:18` | `#define IM_MAX_ENTRIES` |
| `IM_MAX_SCOPES` | macro | `include/import_map.h:19` | `#define IM_MAX_SCOPES` |
| `IM_MAX_TEXT` | macro | `include/import_map.h:17` | `#define IM_MAX_TEXT` |
| `algorithm` | function | `include/import_map.h:13` | `* resolution algorithm (scopes, exact and prefix matches). URL resolution is the * caller's (the same resolver the...` |
| `im_count` | function | `include/import_map.h:37` | `size_t im_count(const im_map *m);` |
| `im_free` | function | `include/import_map.h:40` | `void im_free(im_map *m);` |
| `im_map` | type_alias | `include/import_map.h:23` | `typedef struct im_map im_map;` |
| `im_resolve` | function | `include/import_map.h:33` | `int im_resolve(const im_map *m, const char *base, const char *specifier, im_url_fn resolve, void *ctx, char *out...` |
| `map` | function | `include/import_map.h:28` | `* map (fail closed = no mapping). NULL only on OOM. */ im_map *im_parse(const char *json, size_t len, const char...` |
| `FREEDOM_INTERP_H` | macro | `include/interp.h:2` | `#define FREEDOM_INTERP_H` |
| `IP_ITERATION_INFINITE` | macro | `include/interp.h:85` | `#define IP_ITERATION_INFINITE` |
| `IP_MAX_KEYFRAMES` | macro | `include/interp.h:68` | `#define IP_MAX_KEYFRAMES` |
| `ip_anim` | struct | `include/interp.h:101` | `` |
| `ip_anim_current` | function | `include/interp.h:131` | `double ip_anim_current(const ip_anim *a);` |
| `ip_anim_done` | function | `include/interp.h:134` | `int ip_anim_done(const ip_anim *a);` |
| `ip_anim_init` | function | `include/interp.h:121` | `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease, const ip_keyframe *kf, int n_kf, double...` |
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
| `JD_REPL_CSS_MAX` | macro | `include/js_dom.h:86` | `#define JD_REPL_CSS_MAX` |
| `URLs` | function | `include/js_dom.h:238` | `* video URLs (.m3u8 then .mp4 patterns), and creates <video> elements in the document for * any found. Does NOT...` |
| `getComputedStyle` | function | `include/js_dom.h:115` | `* getComputedStyle (spec/js_computed_style.md). fn writes the computed value of the * kebab-case `prop` of element h...` |
| `global` | function | `include/js_dom.h:80` | `* globals: page scripts never see them and an existing page global (jQuery's `$`) is * never replaced. Read-only...` |
| `host` | function | `include/js_dom.h:170` | `* for a trusted host (allow.conf AND js.conf);` |
| `jd_click_state` | type_alias | `include/js_dom.h:35` | `typedef struct jd_click_state jd_click_state;` |
| `jd_click_state_free` | function | `include/js_dom.h:125` | `* jd_click_state_free(). Bound to one context via jd_install_events(). */ jd_click_state *jd_click_state_new(void);` |
| `jd_flush_custom_elements` | function | `include/js_dom.h:263` | `void jd_flush_custom_elements(js_context *ctx);` |
| `jd_get_cookies` | function | `include/js_dom.h:181` | `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz);` |
| `jd_iframe_track` | struct | `include/js_dom.h:41` | `` |
| `jd_install_repl_api` | function | `include/js_dom.h:89` | `* jd_install_repl_api (the shim reads and deletes the carrier global, so a page script never * sees it). css == NULL...` |
| `jd_opaque` | struct | `include/js_dom.h:46` | `` |
| `jd_process_iframes` | function | `include/js_dom.h:231` | `* BEFORE jd_process_iframes() (so iframes are in the DOM for it to process). * ctx == NULL => JD_ERR_NULL_ARG. */...` |
| `jd_status` | enum | `include/js_dom.h:25` | `` |
| `jd_video_from_scripts` | function | `include/js_dom.h:252` | `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts, const size_t *script_lens, size_t...` |
| `opaque` | function | `include/js_dom.h:73` | `* the engine runtime opaque (unreachable from script);` |
| `out_status` | function | `include/js_dom.h:189` | `* On success returns 0 and sets *out_status (HTTP status, 0 if unknown), *out_body / * *out_body_len (response...` |
| `place` | function | `include/js_dom.h:94` | `* configured place (spec/identity.md), no sensor, no network. Call it ONLY for a trusted host * with geolocation set...` |
| `preventDefault` | function | `include/js_dom.h:141` | `* preventDefault() was called, 1 if the default (form submission) should proceed. * ctx == NULL or no form found =>...` |
| `processed` | type_alias | `include/js_dom.h:41` | `typedef struct jd_iframe_track { dom_node_id processed[JD_IFRAME_TRACK_MAX];` |
| `run` | function | `include/js_dom.h:134` | `* run (no handler registered, or handlers ran without calling preventDefault()), * and 0 if a handler called...` |
| `FREEDOM_JS_ENV_H` | macro | `include/js_env.h:2` | `#define FREEDOM_JS_ENV_H` |
| `JE_READBACK_EXACT` | macro | `include/js_env.h:59` | `#define JE_READBACK_EXACT` |
| `je_status` | enum | `include/js_env.h:27` | `` |
| `poisoned` | function | `include/js_env.h:49` | `* readback is poisoned (deterministic within an origin, unlinkable across * sessions and across origins) to defeat...` |
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
| `FREEDOM_JS_INTL_H` | macro | `include/js_intl.h:6` | `#define FREEDOM_JS_INTL_H` |
| `ji_install` | function | `include/js_intl.h:16` | `int ji_install(js_context *ctx);` |
| `FREEDOM_JS_LOCATION_H` | macro | `include/js_location.h:2` | `#define FREEDOM_JS_LOCATION_H` |
| `JD_HIST_MAX` | macro | `include/js_location.h:31` | `#define JD_HIST_MAX` |
| `acting` | function | `include/js_location.h:49` | `* The caller MUST gate the raw target with ln_resolve before acting (Zero Trust). */ int...` |
| `jd_pop_state` | function | `include/js_location.h:44` | `int jd_pop_state(js_context *ctx, int index);` |
| `jd_take_history` | function | `include/js_location.h:38` | `char *jd_take_history(js_context *ctx, int *go);` |
| `reads` | function | `include/js_location.h:25` | `* reads (NULL => only href is known, the rest fall back to stub defaults). Call after * jd_install, on the page's...` |
| `FREEDOM_JS_NATIVE_H` | macro | `include/js_native.h:12` | `#define FREEDOM_JS_NATIVE_H` |
| `failure` | function | `include/js_native.h:22` | `* engine failure (the page then simply runs with the unsealed surface). */ int jn_seal(js_context *ctx);` |
| `FREEDOM_JS_POLICY_H` | macro | `include/js_policy.h:2` | `#define FREEDOM_JS_POLICY_H` |
| `allowlist` | function | `include/js_policy.h:34` | `* allowlist (e.g. hb_is_allowlisted over js.conf). Fails closed: an unknown mode * yields false. */ bool...` |
| `jsp_mode` | enum | `include/js_policy.h:27` | `` |
| `jsp_mode_str` | function | `include/js_policy.h:64` | `const char *jsp_mode_str(jsp_mode mode);` |
| `jsp_present_trusted` | function | `include/js_policy.h:54` | `bool jsp_present_trusted(int host_allowlisted);` |
| `jsp_trusted` | function | `include/js_policy.h:45` | `bool jsp_trusted(bool js_enabled, int host_allowlisted);` |
| `membership` | function | `include/js_policy.h:16` | `* membership (the allowlist itself is matched by the hostblock module, which * already covers subdomains). No I/O...` |
| `FREEDOM_JS_SANDBOX_H` | macro | `include/js_sandbox.h:2` | `#define FREEDOM_JS_SANDBOX_H` |
| `JS_DEFAULT_MAX_SOURCE` | macro | `include/js_sandbox.h:66` | `#define JS_DEFAULT_MAX_SOURCE` |
| `JS_DEFAULT_MEM_LIMIT` | macro | `include/js_sandbox.h:67` | `#define JS_DEFAULT_MEM_LIMIT` |
| `JS_DEFAULT_STACK_LIMIT` | macro | `include/js_sandbox.h:70` | `#define JS_DEFAULT_STACK_LIMIT` |
| `JS_DEFAULT_TIME_BUDGET` | macro | `include/js_sandbox.h:71` | `#define JS_DEFAULT_TIME_BUDGET` |
| `JS_LOC_FILE_MAX` | macro | `include/js_sandbox.h:64` | `#define JS_LOC_FILE_MAX` |
| `JS_MAX_STACK_LIMIT` | macro | `include/js_sandbox.h:69` | `#define JS_MAX_STACK_LIMIT` |
| `JS_MIN_STACK_LIMIT` | macro | `include/js_sandbox.h:68` | `#define JS_MIN_STACK_LIMIT` |
| `JS_MODULE_BYTES_MAX` | macro | `include/js_sandbox.h:116` | `#define JS_MODULE_BYTES_MAX` |
| `JS_MODULE_MAX` | macro | `include/js_sandbox.h:115` | `#define JS_MODULE_MAX` |
| `JS_PROFILE_PERIOD_MS` | macro | `include/js_sandbox.h:165` | `#define JS_PROFILE_PERIOD_MS` |
| `JS_REALM_MAX` | macro | `include/js_sandbox.h:215` | `#define JS_REALM_MAX` |
| `JS_REJECT_MAX` | macro | `include/js_sandbox.h:218` | `#define JS_REJECT_MAX` |
| `JS_THROW_SLOTS` | macro | `include/js_sandbox.h:174` | `#define JS_THROW_SLOTS` |
| `global` | function | `include/js_sandbox.h:181` | `* Freebug REPL installs: its shim takes them once and deletes them from the global (like * __netLog), because the...` |
| `handle` | function | `include/js_sandbox.h:198` | `* as an opaque handle (so this header stays free of backend types), or NULL. * Valid only while ctx is alive....` |
| `js_context` | type_alias | `include/js_sandbox.h:47` | `typedef struct js_context js_context;` |
| `js_context_free` | function | `include/js_sandbox.h:96` | `void js_context_free(js_context *ctx);` |
| `js_limits` | struct | `include/js_sandbox.h:39` | `` |
| `js_loc_from_stack` | function | `include/js_sandbox.h:150` | `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap, int *line, int *col);` |
| `js_prime_stack_limit` | function | `include/js_sandbox.h:79` | `void js_prime_stack_limit(void);` |
| `js_profile_enable` | function | `include/js_sandbox.h:166` | `void js_profile_enable(js_context *ctx);` |
| `js_profile_report` | function | `include/js_sandbox.h:167` | `size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n);` |
| `js_pump_jobs` | function | `include/js_sandbox.h:195` | `int js_pump_jobs(js_context *ctx, int max_jobs);` |
| `js_result` | struct | `include/js_sandbox.h:49` | `` |
| `js_result_free` | function | `include/js_sandbox.h:187` | `void js_result_free(js_result *res);` |
| `js_set_current_script` | function | `include/js_sandbox.h:207` | `void js_set_current_script(js_context *ctx, const char *src, const char *type);` |
| `js_set_module_host` | function | `include/js_sandbox.h:129` | `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve, js_module_fetch_fn fetch, void *host);` |
| `js_set_time_budget` | function | `include/js_sandbox.h:158` | `void js_set_time_budget(js_context *ctx, uint64_t budget_ms);` |
| `js_stack_limit_for` | function | `include/js_sandbox.h:75` | `size_t js_stack_limit_for(size_t soft_stack);` |
| `js_status` | enum | `include/js_sandbox.h:24` | `` |
| `js_throws_report` | function | `include/js_sandbox.h:176` | `size_t js_throws_report(js_context *ctx, char *out, size_t cap, size_t top_n);` |
| `loaded` | function | `include/js_sandbox.h:124` | `* NULL when it cannot be loaded (policy refusal, network error, not JavaScript). */ typedef char...` |
| `max_source_bytes` | type_alias | `include/js_sandbox.h:39` | `typedef struct js_limits { size_t max_source_bytes;` |
| `out` | function | `include/js_sandbox.h:163` | `* into out (NUL-terminated, truncated at cap);` |
| `silently` | function | `include/js_sandbox.h:171` | `* fails silently (an exception swallowed by a try/catch, a rejected promise nobody awaits) shows * its real first...` |
| `status` | type_alias | `include/js_sandbox.h:48` | `typedef struct js_result { js_status status;` |
| `FREEDOM_JS_TRUSTED_H` | macro | `include/js_trusted.h:2` | `#define FREEDOM_JS_TRUSTED_H` |
| `JT_WS_MAX` | macro | `include/js_trusted.h:46` | `#define JT_WS_MAX` |
| `JT_WS_MAX_BYTES` | macro | `include/js_trusted.h:48` | `#define JT_WS_MAX_BYTES` |
| `JT_WS_MAX_OPS` | macro | `include/js_trusted.h:47` | `#define JT_WS_MAX_OPS` |
| `jt_take_opens` | function | `include/js_trusted.h:42` | `char *jt_take_opens(js_context *ctx);` |
| `jt_take_storage` | function | `include/js_trusted.h:104` | `int jt_take_storage(js_context *ctx, char **out, size_t *len);` |
| `jt_take_ws` | function | `include/js_trusted.h:86` | `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap);` |
| `jt_ws_event` | function | `include/js_trusted.h:92` | `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len);` |
| `jt_ws_event_kind` | enum | `include/js_trusted.h:68` | `` |
| `jt_ws_kind` | enum | `include/js_trusted.h:50` | `` |
| `jt_ws_op` | struct | `include/js_trusted.h:61` | `` |
| `jt_ws_ops_free` | function | `include/js_trusted.h:87` | `void jt_ws_ops_free(jt_ws_op *ops, size_t n);` |
| `kind` | type_alias | `include/js_trusted.h:60` | `typedef struct jt_ws_op { int kind;` |
| `null` | function | `include/js_trusted.h:24` | `* noopener semantics: it returns null (no cross-window reference, so no same-origin * channel) and only records up...` |
| `parent` | function | `include/js_trusted.h:80` | `* socket: the object records operations for the parent (jt_take_ws). */ jd_status jt_enable_ws(js_context *ctx);` |
| `realm` | function | `include/js_trusted.h:107` | `* runs in its own realm (js_install_realms) of this context's runtime, inside the * same confined process and...` |
| `FREEDOM_LAZY_LOAD_H` | macro | `include/lazy_load.h:2` | `#define FREEDOM_LAZY_LOAD_H` |
| `FREEDOM_LINK_NAV_H` | macro | `include/link_nav.h:2` | `#define FREEDOM_LINK_NAV_H` |
| `LN_MAX_FRAGMENT` | macro | `include/link_nav.h:38` | `#define LN_MAX_FRAGMENT` |

Next: [SYMBOLS_p5.md](SYMBOLS_p5.md)
