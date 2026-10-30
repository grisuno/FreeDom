# API (page 4 of 12)
Previous: [API_p3.md](API_p3.md)

## include/css_select.h
Depends on: `include/css.h`
Imported by: `include/css_chain.h`, `include/css_decl.h`, `include/css_index.h`, `src/css.c`, `src/css_atrule.c`, `src/css_box.c`, `src/css_chain.c`, `src/css_gradient.c`, `src/css_select.c`, `src/css_text.c`, `src/css_values.c`, `src/css_vars.c`, `src/dom.c`, `tests/test_css.c`
- `csel_compact_size` (function) `include/css_select.h:167` `size_t csel_compact_size(int nparts);` -- Bytes a selector with `nparts` compounds needs: the header plus the compounds it uses.
- `csel_compact_dup` (function) `include/css_select.h:172` `css_sel *csel_compact_dup(const css_sel *sel);` -- Heap copy of *sel holding only the compounds in use (free()d by the caller); NULL on OOM or a selector with nparts...
- `csel_parse` (function) `include/css_select.h:176` `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel);` -- Parses the complex selector s[a,b) into *sel (spec computed; order/rule left to * the caller).
- `csel_matches` (function) `include/css_select.h:185` `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id, int allow_pseudo_el, int...` -- True if *sel matches element *el against its ancestor chain. target_id (optional) is the URL fragment for :target...
- `csel_element_feature_bits` (function) `include/css_select.h:193` `unsigned long long csel_element_feature_bits(const css_element *e);` -- Ancestor filter. csel_element_feature_bits: the bits of one element's tag, id and classes (two bits per feature...
- `csel_anc_reject` (function) `include/css_select.h:194` `static inline int csel_anc_reject(const css_sel *sel, const css_element *el)`
- `conservative` (function) `include/css_select.h:201` `* Pure and conservative (anything unrecognised answers 1). A selector that answers 0 matches * from the element's...`
- `identifier` (function) `include/css_select.h:207` `* A selector identifier (tag, .class, #id) is read with CSS escapes decoded * (`.md\:flex` is the class "md:flex")...`
- `csel_emit_utf8` (function) `include/css_select.h:219` `size_t csel_emit_utf8(unsigned int cp, char *out);`
- `csel_unescape` (function) `include/css_select.h:221` `void csel_unescape(char *dst, size_t cap, const char *src, size_t n);` -- A selector identifier (tag, .class, #id) is read with CSS escapes decoded (`.md\:flex` is the class "md:flex") and...
- `csel_escape_len` (function) `include/css_select.h:223` `size_t csel_escape_len(const char *s, size_t i, size_t b);` -- does not fit is FOLDED: its first CSEL_FOLD_PREFIX bytes, CSEL_FOLD_MARK (a byte no identifier contains) and 16 hex...
- `csel_ident_fold` (function) `include/css_select.h:225` `void csel_ident_fold(const char *src, size_t len, char *dst);` -- csel_ident_eq folds the element's token the same way, so a CSS Modules name such as...
- `csel_ident_eq` (function) `include/css_select.h:227` `int csel_ident_eq(const char *stored, const char *tok, size_t tlen);` -- instead of being truncated and never matching. #define CSEL_FOLD_PREFIX   40u #define CSEL_FOLD_MARK     '\x1f'...
- `csel_read_ident` (function) `include/css_select.h:230` `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower);` -- Reads an identifier at s[*ip] (escapes decoded, non-ASCII kept, lowercased when * lower != 0) into dst (CSS_TOK_MAX).
- `csel_decl_end` (function) `include/css_select.h:235` `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace);` -- Index of the ';' ending the declaration that starts at s[i] (or of a '}' when stop_brace), or b: separators inside...
- `csel_lower_ch` (function) `include/css_select.h:239` `static inline char csel_lower_ch(char c)`
- `csel_ci_eq` (function) `include/css_select.h:243` `static inline int csel_ci_eq(const char *a, const char *b)`
- `csel_span_eq` (function) `include/css_select.h:252` `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)` -- static inline char csel_lower_ch(char c) { return (c >= 'A' && c <= 'Z') ?
- `csel_substr` (function) `include/css_select.h:263` `static inline int csel_substr(const char *hay, const char *needle, int ci)` -- Substring test (used both to drop any value carrying url() — always ci — and by * the attribute `*=` operator).
- `csel_ident_ch` (function) `include/css_select.h:271` `static inline int csel_ident_ch(char c)`

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
Imported by: `gui/browser_ui.c`, `src/data_url.c`, `src/render_doc.c`, `src/render_policy.c`, `src/tab.c`, `src/webfont.c`, `src/webfont_load.c`, `tests/test_data_url.c`
- `allocation` (function) `include/data_url.h:21` `* * du_base64_payload does no allocation (it only slices the caller's url string);`
- `du_is_data_url` (function) `include/data_url.h:46` `int du_is_data_url(const char *url);` -- 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation...
- `closed` (function) `include/data_url.h:59` `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/out/out_len == NULL (with b64_len !=...`

## include/disk_store.h
Depends on: `include/local_store.h`
Imported by: `src/disk_store.c`, `src/http_cache.c`, `src/profile.c`, `tests/test_disk_store.c`
- `ds_free` (function) `include/disk_store.h:47` `void ds_free(uint8_t *buf, size_t len);` -- Reads and decrypts path.

## include/dom.h
Depends on: `include/html_parse.h`
Imported by: `include/js_dom.h`, `include/js_geom.h`, `include/page_view.h`, `src/dom.c`, `src/html_parse.c`, `src/js_dom.c`, `src/js_dom_internal.h`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/page_view.c`, `src/tab.c`, `tests/test_dom.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_page_view.c`
- `dom_free` (function) `include/dom.h:48` `void dom_free(dom_index *idx);` -- Builds the index over an already-parsed document. doc must outlive *out. doc == NULL / out == NULL =>...
- `dom_node_count` (function) `include/dom.h:51` `size_t dom_node_count(const dom_index *idx);` -- Builds the index over an already-parsed document. doc must outlive *out. doc == NULL / out == NULL =>...
- `tree` (function) `include/dom.h:59` `* tree (the index only grows, so a node a script removed is still registered and must not be * found);`
- `count` (function) `include/dom.h:64` `* match count (which may exceed cap, so the caller can size a buffer). */ size_t dom_get_by_tag(const dom_index...`
- `dom_get_by_class` (function) `include/dom.h:67` `size_t dom_get_by_class(const dom_index *idx, const char *cls, dom_node_id *out, size_t cap);`
- `dom_matches` (function) `include/dom.h:96` `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector);` -- Writes up to cap matching ids (document order) into out; returns the total * match count (may exceed cap, so the...
- `dom_document_position` (function) `include/dom.h:106` `size_t dom_document_position(const dom_index *idx, dom_node_id node);` -- Nearest element at or above node matching the selector list, or DOM_NODE_NONE * (Element.closest). dom_node_id...
- `dom_precedes` (function) `include/dom.h:109` `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);` -- Nearest element at or above node matching the selector list, or DOM_NODE_NONE * (Element.closest). dom_node_id...
- `dom_tag_name` (function) `include/dom.h:123` `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);` -- int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b); /* Node at the given document-order position...
- `dom_get_attribute` (function) `include/dom.h:126` `const char *dom_get_attribute(const dom_index *idx, dom_node_id node, const char *name, size_t *len);` -- dom_node_id dom_node_at(const dom_index *idx, size_t position); /* --- navigation (element-only; DOM_NODE_NONE at...
- `dom_attribute_names` (function) `include/dom.h:133` `size_t dom_attribute_names(const dom_index *idx, dom_node_id node, const char **names, size_t *lens, size_t cap);` -- Qualified names of node's attributes, in document order, written to names[] (borrowed, valid while idx/doc are...
- `dom_text_content` (function) `include/dom.h:138` `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len);` -- Concatenated text content of node's subtree (borrowed, valid while idx/doc are * alive), or NULL. *len (optional)...
- `dom_document_title` (function) `include/dom.h:141` `const char *dom_document_title(const dom_index *idx, size_t *len);` -- Concatenated text content of node's subtree (borrowed, valid while idx/doc are * alive), or NULL. *len (optional)...
- `cycle` (function) `include/dom.h:169` `* Rejects a cycle (child being an ancestor of parent). Invalid handle / self / cycle * => DOM_ERR_NULL_ARG. */...`
- `parent` (function) `include/dom.h:196` `* child of parent (for the *_REF places) or an invalid handle => DOM_ERR_NULL_ARG. */ dom_status...`
- `dom_node_kind` (function) `include/dom.h:212` `int dom_node_kind(const dom_index *idx, dom_node_id node);` -- -- text and comment nodes (spec/dom.md 9) --- Character-data nodes get LAZY handles in the same arena: registered...
- `index` (function) `include/dom.h:228` `* stays valid in the index (not freed). Invalid handle / not-a-child => DOM_ERR_NULL_ARG. */ dom_status...`
- `length` (function) `include/dom.h:253` `* length (no children => an owned empty string). Uses a chain of fixed-size * blocks internally so there is no hard...`
- `process` (function) `include/dom.h:260` `* modules in the same process (style resolution). NULL for a bad or non-element * handle. Valid until the next...`

## include/dom_debug.h
Depends on: `include/render_doc.h`
Imported by: `src/dom_debug.c`, `src/freedom.c`, `tests/test_dom_debug.c`
- `dd_format` (function) `include/dom_debug.h:36` `size_t dd_format(const rd_doc *doc, char *out, size_t cap);` -- Formats doc into out[0..cap) as a NUL-terminated, line-oriented dump (see the spec for the stable format).
- `dd_format_css` (function) `include/dom_debug.h:41` `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap);` -- CSS inspector: dumps every block with its FULL resolved css_style fields as a compact property list.

## include/download.h
Imported by: `gui/browser_ui.c`, `src/download.c`, `tests/test_download.c`
- `dl_should_download` (function) `include/download.h:43` `int dl_should_download(const char *content_type, const char *content_disposition);` -- 1 if the response should be saved (attachment, or a non-renderable media type), 0 if it should be rendered.
- `literal` (function) `include/download.h:47` `* a static string literal (never freed). */ const char *dl_ext_for_type(const char *content_type);`
- `DL_ERR_OVERFLOW` (function) `include/download.h:56` `* DL_ERR_OVERFLOW (out left empty). url/content_disposition NULL => absent. */ dl_status dl_pick_name(const char...`
- `basename` (function) `include/download.h:61` `* sanitized basename (a name still containing '/' is rejected => DL_ERR_OVERFLOW, * so the path can never escape...`

## include/fb_cmdline.h
Imported by: `gui/browser_ui.c`, `src/fb_cmdline.c`, `tests/test_fb_cmdline.c`, `tests/test_js_dom.c`
- `fbc_history_init` (function) `include/fb_cmdline.h:27` `void fbc_history_init(fbc_history *h);`
- `fbc_history_free` (function) `include/fb_cmdline.h:28` `void fbc_history_free(fbc_history *h);`
- `fbc_history_push` (function) `include/fb_cmdline.h:31` `int fbc_history_push(fbc_history *h, const char *text, size_t len);` -- #define FBC_BASE_MAX   256    /* bytes of a completion base path #define FBC_LIST_NAMES 40     /* candidates shown...
- `fbc_history_prev` (function) `include/fb_cmdline.h:35` `const char *fbc_history_prev(fbc_history *h, const char *cur, size_t curlen);` -- Older entry (saves cur as the draft when leaving the live line), or NULL when there is none. * The pointer is valid...
- `fbc_history_next` (function) `include/fb_cmdline.h:38` `const char *fbc_history_next(fbc_history *h);` -- Older entry (saves cur as the draft when leaving the live line), or NULL when there is none. * The pointer is valid...
- `fbc_complete_split` (function) `include/fb_cmdline.h:42` `long fbc_complete_split(const char *text, size_t n, char *base, size_t cap, size_t *prefix_off);` -- Splits the trailing property path of text[0,n): base ("a.b" of "a.b.c", "" = global) into base[cap], * *prefix_off =...
- `fbc_names_expr` (function) `include/fb_cmdline.h:46` `size_t fbc_names_expr(const char *base, char *out, size_t cap);` -- JS expression returning the newline-joined property names reachable from the path `base` * (no getter is run).
- `fbc_complete_pick` (function) `include/fb_cmdline.h:51` `size_t fbc_complete_pick(const char *names, const char *prefix, size_t plen, char *ins, size_t ins_cap, char *list...` -- From the newline-separated `names`, those starting with prefix[0,plen): `ins` gets the longest common extension...
- `fbc_filter_passes` (function) `include/fb_cmdline.h:62` `int fbc_filter_passes(int filter, int level);`
- `fbc_filter_next` (function) `include/fb_cmdline.h:63` `int fbc_filter_next(int filter);` -- extension beyond the prefix, `list` the candidates space-separated; *count how many matched.
- `fbc_filter_label` (function) `include/fb_cmdline.h:64` `const char *fbc_filter_label(int filter);` -- the length of the insertion. size_t fbc_complete_pick(const char *names, const char *prefix, size_t plen, char *ins...

## include/fb_panes.h
Imported by: `gui/browser_ui.c`, `src/fb_cmdline.c`, `src/fb_panes.c`, `src/freedom.c`, `tests/test_fb_panes.c`, `tests/test_js_dom.c`
- `fbp_tab_label` (function) `include/fb_panes.h:34` `const char *fbp_tab_label(int tab);` -- FBP_CSS, FBP_SCRIPT, FBP_NET, FBP_PROFILE,   /* where the JS time went (sampling profiler, time-weighted)...
- `fbp_tab_from_name` (function) `include/fb_panes.h:37` `int fbp_tab_from_name(const char *name);` -- FBP_PROFILE,   /* where the JS time went (sampling profiler, time-weighted) FBP_THROWS,    /* every exception...
- `fbp_tab_wrap` (function) `include/fb_panes.h:40` `int fbp_tab_wrap(int tab, int dir);` -- FBP_STORAGE,   /* cookies, localStorage and sessionStorage of the page FBP_COUNT } fbp_tab; #define FBP_SELECTOR_MAX...
- `fbp_tab_span` (function) `include/fb_panes.h:43` `void fbp_tab_span(int tab, double cell_w, double pad_cells, double *x, double *w);` -- #define FBP_SELECTOR_MAX 256   /* bytes of the user's argument (selector / index / filter) #define FBP_EXPR_MAX...
- `fbp_tab_at` (function) `include/fb_panes.h:46` `int fbp_tab_at(double x, double cell_w, double pad_cells);` -- /* Label of a tab; an out-of-range id is the console.
- `fbp_is_pane` (function) `include/fb_panes.h:49` `int fbp_is_pane(int tab);` -- /* Tab named `name` (case-insensitive), or -1 when unknown / NULL. int fbp_tab_from_name(const char *name); /* The...
- `fbp_js_quote` (function) `include/fb_panes.h:53` `size_t fbp_js_quote(const char *s, size_t n, char *out, size_t cap);` -- JS string literal for s[0,n) (double-quoted).
- `fbp_expr` (function) `include/fb_panes.h:57` `size_t fbp_expr(int tab, const char *sel, size_t n, char *out, size_t cap);` -- The expression that fills `tab`'s panel for argument sel[0,n); NUL-terminated in out. * Returns its length, or 0 for...

## include/flex_layout.h
Imported by: `include/box_tree.h`, `src/css.c`, `src/dom_debug.c`, `src/flex_layout.c`, `src/page_view.c`, `src/tab.c`, `tests/test_css.c`, `tests/test_dom_debug.c`, `tests/test_flex_layout.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`
- `size` (function) `include/flex_layout.h:60` `* content size (px);`
- `out` (function) `include/flex_layout.h:62` `* fx_result to out (caller-owned). n == 0 is a no-op (out may be NULL). */ fx_status fx_flex_line(const fx_item...`
- `fx_grid_cell` (function) `include/flex_layout.h:74` `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col);` -- Row and column of the index-th item placed row-major into ncols columns. * ncols == 0 yields row = col = 0...
- `number` (function) `include/flex_layout.h:106` `* line number (negative counts from the end). */ #define FX_GL_AUTO 0 #define FX_GL_SPAN_BASE (1 << 20) #define...`
- `fx_grid_line_parse` (function) `include/flex_layout.h:117` `int fx_grid_line_parse(const char *v, int *start, int *end);` -- The shorthand `<side> [ / <side> ]` (no slash => end is auto).
- `fx_grid_line_resolve` (function) `include/flex_layout.h:122` `void fx_grid_line_resolve(int start, int end, int ntracks, int *pos0, int *span);` -- Resolves a start/end pair against ntracks explicit tracks: *pos0 = 0-based start track or -1 (auto-place), *span >= 1.
- `fx_autofill_count` (function) `include/flex_layout.h:129` `size_t fx_autofill_count(double avail, double gap, double minw);` -- repeat(auto-fill, minmax(min, max)): how many min-wide tracks fit in avail (CSS Grid 1 7.2.3.2; one gap between tracks).
- `fx_grid_column_count` (function) `include/flex_layout.h:139` `int fx_grid_column_count(int flow, int cols, int rows, size_t items);` -- Column count of a grid container (CSS Grid 1 8.5).
- `fx_grid_area_hash` (function) `include/flex_layout.h:163` `unsigned fx_grid_area_hash(const char *name);` -- FNV-1a of a trimmed, case-sensitive CSS identifier; never returns 0 for a non-empty name (0 is reserved for "unnamed").
- `offset` (function) `include/flex_layout.h:181` `* offset (from the content start, clamped to >= 0) to out_x[n]. The band does NOT wrap * (v1): an item that would...`
- `required` (function) `include/flex_layout.h:194` `* out_row is required (NULL with n > 0 yields FX_ERR_NULL_ARG);`
- `widths` (function) `include/flex_layout.h:204` `* the OUTER widths (width + ml + mr, clamped >= 0, so a negative margin narrows * the slot and a positive one widens...`
- `FX_ERR_NULL_ARG` (function) `include/flex_layout.h:238` `* Returns FX_ERR_NULL_ARG (a required pointer NULL with n > 0), FX_ERR_RANGE * (negative h/avail, or n > FX_MAX_ITEMS);`
- `space` (function) `include/flex_layout.h:244` `* line order: positive free space (avail - sizes - gaps) is split equally among every * auto margin...`
- `fx_auto_min_size` (function) `include/flex_layout.h:275` `double fx_auto_min_size(double min_content, double basis, double author_min, int scroll_container);` -- units as fx_item.basis.
- `fx_justify_name` (function) `include/flex_layout.h:331` `const char *fx_justify_name(fx_justify j);` -- Stable, short English name of a justify mode for structured/agent output.
- `height` (function) `include/flex_layout.h:337` `* used height (h_out);`
- `it` (function) `include/flex_layout.h:354` `* children that claim it (spec/flex_layout.md, tanda 44): proportionally to * grow[i] (x100) when any grows, else...`
- `win` (function) `include/flex_layout.h:362` `* margins win (both = centre, left only = end);`
- `fx_cross_offset` (function) `include/flex_layout.h:364` `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r);` -- Cross-axis (horizontal) offset of a column item of width w in avail px. auto margins win (both = centre, left only =...

## include/frame_broker.h
Imported by: `src/frame_broker.c`, `src/frame_host.c`, `tests/test_frame_broker.c`
- `fbk_origin_of` (function) `include/frame_broker.h:42` `int fbk_origin_of(const char *url, char *out, size_t cap);` -- Serialized origin ("https://host[:port]", lowercase) or "null" for opaque/non-https/unparseable. * 0 on success, -1...
- `fbk_init` (function) `include/frame_broker.h:45` `int fbk_init(fbk_table *t, const char *top_url);` -- Serialized origin ("https://host[:port]", lowercase) or "null" for opaque/non-https/unparseable. * 0 on success, -1...
- `fbk_add` (function) `include/frame_broker.h:49` `int fbk_add(fbk_table *t, int parent, const char *url, int *out_id);` -- Adds a child of `parent` for url.
- `fbk_remove` (function) `include/frame_broker.h:52` `void fbk_remove(fbk_table *t, int id);` -- Adds a child of `parent` for url.
- `fbk_origin` (function) `include/frame_broker.h:55` `const char *fbk_origin(const fbk_table *t, int id);` -- Adds a child of `parent` for url.

## include/frame_clock.h
Imported by: `gui/browser_ui.c`, `src/frame_clock.c`, `tests/test_frame_clock.c`
- `fc_init` (function) `include/frame_clock.h:20` `void fc_init(fc_clock *c);`
- `fc_set_active` (function) `include/frame_clock.h:21` `void fc_set_active(fc_clock *c, int active);`
- `fc_needs_tick` (function) `include/frame_clock.h:22` `int fc_needs_tick(const fc_clock *c);`
- `fc_interval_ms` (function) `include/frame_clock.h:23` `int fc_interval_ms(const fc_clock *c);`

## include/frame_host.h
Depends on: `include/page_view.h`, `include/tab.h`
Imported by: `gui/browser_ui.c`, `src/frame_host.c`, `src/freedom.c`, `tests/test_frame_host.c`
- `fh_new` (function) `include/frame_host.h:28` `fh_host *fh_new(const char *top_url, tab_fetch_fn fetch, void *fetch_ctx, fh_top_msg_fn top_msg, void *top_ctx);` -- top_url: the trusted top document; fetch/fetch_ctx: the page's policy-gated subresource fetcher (used for the frame...
- `fh_free` (function) `include/frame_host.h:32` `void fh_free(fh_host *h);` -- top_url: the trusted top document; fetch/fetch_ctx: the page's policy-gated subresource fetcher (used for the frame...
- `fh_apply_top` (function) `include/frame_host.h:36` `void fh_apply_top(fh_host *h, const tab_page *page);` -- Processes the frame ops (kinds FRAME_OPEN/CLOSE/POST) among page->ws of the TOP document; other * kinds are ignored.
- `fh_tick` (function) `include/frame_host.h:40` `int fh_tick(fh_host *h, int elapsed_ms);` -- Advances every frame's virtual clock by elapsed_ms and processes what they posted.
- `fh_count` (function) `include/frame_host.h:43` `int fh_count(const fh_host *h);` -- Advances every frame's virtual clock by elapsed_ms and processes what they posted.
- `it` (function) `include/frame_host.h:46` `* confined worker last built it (NULL when no live frame has that URL);`
- `fh_frame_view` (function) `include/frame_host.h:49` `const pv_view *fh_frame_view(const fh_host *h, const char *url, tab **t_out);` -- Painting (spec/frame_broker.md section 5).
- `fh_generation` (function) `include/frame_host.h:52` `unsigned fh_generation(const fh_host *h);` -- Painting (spec/frame_broker.md section 5).

## include/freebug.h
Imported by: `gui/browser_ui.c`, `include/js_dom.h`, `include/tab.h`, `src/fb_cmdline.c`, `src/freebug.c`, `src/freedom.c`, `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/tab.c`, `tests/test_fb_cmdline.c`, `tests/test_freebug.c`
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

## include/host_conf.h
Depends on: `include/hostblock.h`
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/host_conf.c`, `tests/test_host_conf.c`
- `hcf_search_dirs` (function) `include/host_conf.h:28` `void hcf_search_dirs(const char *env, const char *home, hcf_dirs *out);` -- Pure.
- `hcf_search_dirs_from_env` (function) `include/host_conf.h:31` `void hcf_search_dirs_from_env(hcf_dirs *out);` -- Pure.
- `hcf_load_filter` (function) `include/host_conf.h:35` `hb_set *hcf_load_filter(const hcf_dirs *dirs);` -- block.conf (BLOCK) + allow.conf (ALLOW) from every directory, cumulative.
- `hcf_load_allowlist` (function) `include/host_conf.h:39` `hb_set *hcf_load_allowlist(const hcf_dirs *dirs, const char *fname);` -- One file (js.conf, allow.conf, ...) from every directory as an ALLOW list.

## include/hostblock.h
Imported by: `gui/browser_ui.c`, `include/host_conf.h`, `src/freedom.c`, `src/hostblock.c`, `tests/test_hostblock.c`
- `hb_new` (function) `include/hostblock.h:49` `hb_set *hb_new(void);` -- } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on...
- `hb_free` (function) `include/hostblock.h:52` `void hb_free(hb_set *s);` -- HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) }...
- `walked` (function) `include/hostblock.h:65` `* walked (the host, then without its first label, ...): any suffix on the allowlist * => HB_ALLOW (allow wins...`
- `hb_is_allowlisted` (function) `include/hostblock.h:75` `int hb_is_allowlisted(const hb_set *s, const char *host);` -- 1 iff a domain suffix of host is explicitly on the allowlist (covers subdomains), else 0.
- `hb_count` (function) `include/hostblock.h:85` `size_t hb_count(const hb_set *s, hb_list list);` -- Number of unique domains on the given list (for tests/diagnostics).

## include/hostedit.h
Imported by: `gui/browser_ui.c`, `src/hostedit.c`, `tests/test_hostedit.c`
- `he_text_has_host` (function) `include/hostedit.h:46` `int he_text_has_host(const char *text, const char *host);` -- Returns 1 if text (the body of a hosts-format file) already lists host as a domain token on a non-comment line...
- `he_suggest` (function) `include/hostedit.h:55` `int he_suggest(const char *text, const char *query, char results[][HE_MAX_HOST + 1], int max);` -- Omnibar autocomplete: treats allow.conf (a hosts-format text) as a favorites list.
- `he_cdn_kind` (function) `include/hostedit.h:62` `he_cdn_kind_t he_cdn_kind(const char *url);`

## include/html_parse.h
Imported by: `gui/freedom_view.c`, `include/dom.h`, `include/page_view.h`, `src/dom.c`, `src/freedom.c`, `src/html_parse.c`, `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/page_view.c`, `src/renderer.c`, `src/tab.c`, `tests/test_dom.c`, `tests/test_html_parse.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_page_view.c`
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

## include/http_cache.h
Depends on: `include/local_store.h`
Imported by: `include/cached_fetch.h`, `src/http_cache.c`, `tests/test_http_cache.c`
- `hc_parse_http_date` (function) `include/http_cache.h:56` `time_t hc_parse_http_date(const char *s);` -- } hc_class; typedef struct hc_meta { char   final_url[HC_URL_MAX]; char   content_type[HC_TYPE_MAX]; char...
- `by` (function) `include/http_cache.h:59` `* something to reuse it by (validator, max-age or Expires). */ int hc_storable(long http_code, const hc_meta *m...`
- `hc_lifetime` (function) `include/http_cache.h:63` `long hc_lifetime(const hc_meta *m);` -- True when a response may be stored: 200, no `no-store`, body within HC_MAX_ENTRY, and * something to reuse it by...
- `hc_close` (function) `include/http_cache.h:72` `void hc_close(hc_store *s);`
- `hc_body_free` (function) `include/http_cache.h:78` `void hc_body_free(uint8_t *body, size_t len);`
- `hc_clear` (function) `include/http_cache.h:84` `void hc_clear(hc_store *s);` -- ML-KEM keys and empties the directory when the sealed key cannot be opened. hc_status hc_open(hc_store **out, const...

## include/identity.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/identity.c`, `src/tab.c`, `tests/test_identity.c`
- `idn_defaults` (function) `include/identity.h:50` `void idn_defaults(idn_config *c);` -- typedef struct idn_config { char   user_agent[IDN_UA_MAX];  /* "" = FP_USER_AGENT char   languages[IDN_LANG_MAX]; /*...
- `idn_is_default` (function) `include/identity.h:53` `int idn_is_default(const idn_config *c);` -- char   languages[IDN_LANG_MAX]; /* "" = the anti_fp default; comma-separated tags int    geo_mode;                /*...
- `idn_set_user_agent` (function) `include/identity.h:56` `int idn_set_user_agent(idn_config *c, const char *ua);` -- unsigned auto_allow;            /* IDN_AA_* switches: hosts a page on allow.conf pulls CSS/JS/ resources from are...
- `idn_set_languages` (function) `include/identity.h:57` `int idn_set_languages(idn_config *c, const char *list);`
- `idn_set_geo` (function) `include/identity.h:58` `int idn_set_geo(idn_config *c, double lat, double lon, double accuracy_m);`
- `idn_clear_geo` (function) `include/identity.h:59` `void idn_clear_geo(idn_config *c);`
- `idn_user_agent` (function) `include/identity.h:62` `const char *idn_user_agent(const idn_config *c);` -- /* The anti_fp identity, geolocation off.
- `idn_accept_language` (function) `include/identity.h:63` `size_t idn_accept_language(const idn_config *c, char *out, size_t cap);`
- `idn_primary_language` (function) `include/identity.h:64` `size_t idn_primary_language(const idn_config *c, char *out, size_t cap);`
- `idn_serialize` (function) `include/identity.h:68` `size_t idn_serialize(const idn_config *c, char *out, size_t cap);` -- One-line text form for prefs and the worker IPC.
- `idn_parse` (function) `include/identity.h:72` `void idn_parse(idn_config *c, const char *text);` -- Parses idn_serialize output field by field; an invalid field keeps its default.
- `idn_apply_query` (function) `include/identity.h:75` `unsigned idn_apply_query(idn_config *c, const char *query);` -- Parses idn_serialize output field by field; an invalid field keeps its default.
- `idn_render_page` (function) `include/identity.h:78` `size_t idn_render_page(const idn_config *c, char *out, size_t cap);` -- Parses idn_serialize output field by field; an invalid field keeps its default.

## include/image_decode.h
Imported by: `gui/browser_ui.c`, `src/image_decode.c`, `src/tab.c`, `tests/test_freedom.c`, `tests/test_image_decode.c`
- `guards` (function) `include/image_decode.h:25` `* guards (in-memory source only, longjmp error manager so a bad stream never * calls exit(), dimension caps before...`
- `img_dimensions_ok` (function) `include/image_decode.h:78` `int img_dimensions_ok(uint32_t w, uint32_t h);` -- 1 iff (w,h) is non-zero and fits the anti-DoS caps (per-side and area, no * overflow of width*height*4); 0 otherwise.
- `inputs` (function) `include/image_decode.h:81` `* Degenerate inputs (<= 0) yield (0,0). Pure. */ void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h...`
- `decode` (function) `include/image_decode.h:92` `* the declared dimensions BEFORE the full decode (anti-bomb), decodes to RGB and * expands to BGRA. Rejects non-JPEG...`
- `img_pixels_free` (function) `include/image_decode.h:121` `void img_pixels_free(img_pixels *p);` -- Releases data and zeroes the struct.
- `img_format_name` (function) `include/image_decode.h:124` `const char *img_format_name(img_format f);` -- Releases data and zeroes the struct.

## include/import_map.h
Imported by: `src/import_map.c`, `src/prefetch.c`, `src/tab.c`, `tests/test_import_map.c`
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
Imported by: `include/js_location.h`, `include/js_trusted.h`, `src/js_dom.c`, `src/js_dom_ext.c`, `src/js_dom_internal.h`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/js_location.c`, `src/tab.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`
- `opaque` (function) `include/js_dom.h:73` `* the engine runtime opaque (unreachable from script);`
- `global` (function) `include/js_dom.h:80` `* globals: page scripts never see them and an existing page global (jQuery's `$`) is * never replaced. Read-only...`
- `jd_install_repl_api` (function) `include/js_dom.h:89` `* jd_install_repl_api (the shim reads and deletes the carrier global, so a page script never * sees it). css == NULL...`
- `place` (function) `include/js_dom.h:94` `* configured place (spec/identity.md), no sensor, no network. Call it ONLY for a trusted host * with geolocation set...`
- `getComputedStyle` (function) `include/js_dom.h:115` `* getComputedStyle (spec/js_computed_style.md). fn writes the computed value of the * kebab-case `prop` of element h...`
- `jd_click_state_free` (function) `include/js_dom.h:125` `* jd_click_state_free(). Bound to one context via jd_install_events(). */ jd_click_state *jd_click_state_new(void);`
- `run` (function) `include/js_dom.h:134` `* run (no handler registered, or handlers ran without calling preventDefault()), * and 0 if a handler called...`
- `preventDefault` (function) `include/js_dom.h:141` `* preventDefault() was called, 1 if the default (form submission) should proceed. * ctx == NULL or no form found =>...`
- `host` (function) `include/js_dom.h:170` `* for a trusted host (allow.conf AND js.conf);`
- `jd_get_cookies` (function) `include/js_dom.h:181` `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz);` -- Serialises the page's current cookie jar ("name=value; ...") into buf (bounded, NUL-terminated) and returns its...
- `out_status` (function) `include/js_dom.h:189` `* On success returns 0 and sets *out_status (HTTP status, 0 if unknown), *out_body / * *out_body_len (response...`
- `jd_process_iframes` (function) `include/js_dom.h:229` `* BEFORE jd_process_iframes() (so iframes are in the DOM for it to process). * ctx == NULL => JD_ERR_NULL_ARG. */...`
- `URLs` (function) `include/js_dom.h:236` `* video URLs (.m3u8 then .mp4 patterns), and creates <video> elements in the document for * any found. Does NOT...`
- `jd_video_from_scripts` (function) `include/js_dom.h:250` `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts, const size_t *script_lens, size_t...` -- Creates <iframe> elements in the DOM from video data (`video[N]` / `video_data`) found in inline script text...
- `jd_flush_custom_elements` (function) `include/js_dom.h:261` `void jd_flush_custom_elements(js_context *ctx);` -- Reconciles Custom Elements (spec/js_custom_elements.md): upgrades the elements whose tag was just defined and fires...

## include/js_env.h
Depends on: `include/js_sandbox.h`
Imported by: `src/js_env.c`, `src/tab.c`, `tests/test_js_env.c`
- `poisoned` (function) `include/js_env.h:49` `* readback is poisoned (deterministic within an origin, unlinkable across * sessions and across origins) to defeat...`

## include/js_geom.h
Depends on: `include/dom.h`
Imported by: `include/js_dom.h`, `include/tab.h`, `src/js_geom.c`, `tests/test_js_dom.c`, `tests/test_js_geom.c`, `tests/test_tab.c`
- `jg_init` (function) `include/js_geom.h:44` `void jg_init(jg_table *t);` -- typedef struct jg_rect { dom_node_id node; int32_t     x, y, w, h;       /* document coordinates, px } jg_rect...
- `jg_free` (function) `include/js_geom.h:47` `void jg_free(jg_table *t);` -- } jg_rect; typedef struct jg_table { jg_rect *r; size_t   n, cap; int32_t  scroll_x, scroll_y;  /* document scroll...
- `jg_add` (function) `include/js_geom.h:52` `int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h);` -- Appends one rect.
- `jg_finish` (function) `include/js_geom.h:56` `int jg_finish(jg_table *t);` -- Sorts by node and merges rects of the same node into their bounding box. * Returns 0, or -1 on NULL.
- `jg_find` (function) `include/js_geom.h:59` `const jg_rect *jg_find(const jg_table *t, dom_node_id node);` -- Sorts by node and merges rects of the same node into their bounding box. * Returns 0, or -1 on NULL. int...
- `jg_aggregate` (function) `include/js_geom.h:65` `int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx);` -- Unions every rect into each of its ancestors (parent(ctx, n) until DOM_NODE_NONE, at most JG_MAX_DEPTH steps, so a...
- `jg_wire_len` (function) `include/js_geom.h:68` `size_t jg_wire_len(const jg_table *t);` -- Unions every rect into each of its ancestors (parent(ctx, n) until DOM_NODE_NONE, at most JG_MAX_DEPTH steps, so a...
- `jg_encode` (function) `include/js_geom.h:71` `int jg_encode(const jg_table *t, int32_t *out, size_t cap);` -- Unions every rect into each of its ancestors (parent(ctx, n) until DOM_NODE_NONE, at most JG_MAX_DEPTH steps, so a...
- `jg_decode` (function) `include/js_geom.h:77` `int jg_decode(const int32_t *in, size_t n, jg_table *out);` -- Parses a wire array into out (which must be jg_init'ed or empty; previous contents are freed).
- `jg_hash` (function) `include/js_geom.h:80` `uint64_t jg_hash(const jg_table *t);` -- Parses a wire array into out (which must be jg_init'ed or empty; previous contents are freed).

## include/js_location.h
Depends on: `include/js_dom.h`, `include/js_sandbox.h`, `include/url.h`
Imported by: `include/js_dom.h`
- `reads` (function) `include/js_location.h:25` `* reads (NULL => only href is known, the rest fall back to stub defaults). Call after * jd_install, on the page's...`
- `jd_take_history` (function) `include/js_location.h:38` `char *jd_take_history(js_context *ctx, int *go);` -- Drains the history operations page JS performed since the last call: an owned string of lines "P <url>\n"...
- `jd_pop_state` (function) `include/js_location.h:44` `int jd_pop_state(js_context *ctx, int index);` -- Moves the page's history to entry index (the parent went Back/Forward within the same document): updates location...
- `acting` (function) `include/js_location.h:49` `* The caller MUST gate the raw target with ln_resolve before acting (Zero Trust). */ int...`

## include/js_policy.h
Imported by: `gui/browser_ui.c`, `include/webcaps.h`, `src/freedom.c`, `src/js_policy.c`, `tests/test_js_policy.c`
- `membership` (function) `include/js_policy.h:16` `* membership (the allowlist itself is matched by the hostblock module, which * already covers subdomains). No I/O...`
- `allowlist` (function) `include/js_policy.h:34` `* allowlist (e.g. hb_is_allowlisted over js.conf). Fails closed: an unknown mode * yields false. */ bool...`
- `jsp_trusted` (function) `include/js_policy.h:45` `bool jsp_trusted(bool js_enabled, int host_allowlisted);` -- Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g....
- `jsp_present_trusted` (function) `include/js_policy.h:54` `bool jsp_present_trusted(int host_allowlisted);` -- Presentation-trust (2026-07-11): a host EXPLICITLY on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- `jsp_mode_str` (function) `include/js_policy.h:64` `const char *jsp_mode_str(jsp_mode mode);` -- Stable lowercase name of a mode ("off"/"allowlist"/"on"); an unknown value * yields "off" (fail closed).

## include/js_sandbox.h
Imported by: `include/js_dom.h`, `include/js_env.h`, `include/js_location.h`, `include/js_trusted.h`, `src/js_dom.c`, `src/js_dom_ext.c`, `src/js_embed.c`, `src/js_env.c`, `src/js_events.c`, `src/js_fetch.c`, `src/js_sandbox.c`, `src/tab.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_js_sandbox.c`
- `js_stack_limit_for` (function) `include/js_sandbox.h:75` `size_t js_stack_limit_for(size_t soft_stack);` -- Engine stack cap for a process whose soft stack limit is `soft_stack` bytes (0 = unknown): * 75 % of it (the rest is...
- `js_prime_stack_limit` (function) `include/js_sandbox.h:79` `void js_prime_stack_limit(void);` -- Reads the process stack limit now.
- `js_context_free` (function) `include/js_sandbox.h:96` `void js_context_free(js_context *ctx);` -- Creates an isolated, hardened sandbox (memory/stack/time limits armed; no I/O modules). lim == NULL =>...
- `loaded` (function) `include/js_sandbox.h:124` `* NULL when it cannot be loaded (policy refusal, network error, not JavaScript). */ typedef char...`
- `js_set_module_host` (function) `include/js_sandbox.h:129` `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve, js_module_fetch_fn fetch, void *host);` -- Installs the host every static import and dynamic import() goes through. host must * outlive ctx.
- `js_loc_from_stack` (function) `include/js_sandbox.h:150` `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap, int *line, int *col);` -- Pure parser: extracts the throw site (file, line, column) from the FIRST frame of a QuickJS .stack string.
- `js_set_time_budget` (function) `include/js_sandbox.h:158` `void js_set_time_budget(js_context *ctx, uint64_t budget_ms);` -- Adjusts the wall-clock budget armed on each subsequent js_eval.
- `out` (function) `include/js_sandbox.h:163` `* into out (NUL-terminated, truncated at cap);`
- `js_profile_enable` (function) `include/js_sandbox.h:166` `void js_profile_enable(js_context *ctx);` -- Sampling profiler (FREEDOM_JS_PROFILE=2).
- `js_profile_report` (function) `include/js_sandbox.h:167` `size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n);`
- `silently` (function) `include/js_sandbox.h:171` `* fails silently (an exception swallowed by a try/catch, a rejected promise nobody awaits) shows * its real first...`
- `js_throws_report` (function) `include/js_sandbox.h:176` `size_t js_throws_report(js_context *ctx, char *out, size_t cap, size_t top_n);`
- `global` (function) `include/js_sandbox.h:181` `* Freebug REPL installs: its shim takes them once and deletes them from the global (like * __netLog), because the...`
- `js_result_free` (function) `include/js_sandbox.h:187` `void js_result_free(js_result *res);` -- Devtools for a TRUSTED page. js_devtools_enable turns the profiler and the throw tracer on when the page loads...
- `js_pump_jobs` (function) `include/js_sandbox.h:195` `int js_pump_jobs(js_context *ctx, int max_jobs);` -- Runs up to max_jobs pending microtasks/jobs (promise reactions queued by the last eval), under the context's current...
- `handle` (function) `include/js_sandbox.h:198` `* as an opaque handle (so this header stays free of backend types), or NULL. * Valid only while ctx is alive....`
- `js_set_current_script` (function) `include/js_sandbox.h:207` `void js_set_current_script(js_context *ctx, const char *src, const char *type);` -- Sets document.currentScript on the global object so external scripts can read their own src / type / data-*...

## include/js_trusted.h
Depends on: `include/js_dom.h`, `include/js_sandbox.h`
Imported by: `src/js_trusted.c`, `src/tab.c`, `tests/test_js_dom.c`
- `null` (function) `include/js_trusted.h:24` `* noopener semantics: it returns null (no cross-window reference, so no same-origin * channel) and only records up...`
- `jt_take_opens` (function) `include/js_trusted.h:42` `char *jt_take_opens(js_context *ctx);` -- The parent installed a new geometry table (layout or scroll changed): re-evaluates every observed target and fires a...
- `parent` (function) `include/js_trusted.h:80` `* socket: the object records operations for the parent (jt_take_ws). */ jd_status jt_enable_ws(js_context *ctx);`
- `jt_take_ws` (function) `include/js_trusted.h:86` `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap);` -- Drains up to cap recorded operations into ops (each data owned; release with jt_ws_ops_free).
- `jt_ws_ops_free` (function) `include/js_trusted.h:87` `void jt_ws_ops_free(jt_ws_op *ops, size_t n);`
- `jt_ws_event` (function) `include/js_trusted.h:92` `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len);` -- Delivers a socket event from the parent: data enters JS as a VALUE (a string for text, an ArrayBuffer for binary...
- `jt_take_storage` (function) `include/js_trusted.h:104` `int jt_take_storage(js_context *ctx, char **out, size_t *len);` -- When the store changed since the last call, returns 1 with an owned snapshot of * the whole store in *out (length...
- `realm` (function) `include/js_trusted.h:107` `* runs in its own realm (js_install_realms) of this context's runtime, inside the * same confined process and...`

## include/link_nav.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/link_nav.c`, `src/tab.c`, `tests/test_link_nav.c`
- `dropped` (function) `include/link_nav.h:36` `* A longer fragment is dropped (stored as "");`
- `ln_block_reason_text` (function) `include/link_nav.h:85` `const char *ln_block_reason_text(ln_block_reason reason);` -- Stable, short English notice for a block reason (e.g. for a UI toast or agent * output).

## include/local_store.h
Imported by: `include/disk_store.h`, `include/http_cache.h`, `include/pq_seal.h`, `include/profile.h`, `src/disk_store.c`, `src/local_store.c`, `tests/test_disk_store.c`, `tests/test_local_store.c`
- `ls_free` (function) `include/local_store.h:80` `void ls_free(uint8_t *buf, size_t len);` -- Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container...

## include/media_decoder.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/media_decoder.c`, `tests/test_media_decoder.c`
- `md_pace_due_ms` (function) `include/media_decoder.h:79` `static inline uint64_t md_pace_due_ms(md_pacer *p, uint64_t now_ms,
                             ...` -- Returns the wall-clock instant (ms) at which the frame carrying pts_us is due for display.
- `media_decoder_run` (function) `include/media_decoder.h:99` `void media_decoder_run(int out_fd, int cmd_fd);` -- Entry point for the decoder child process.
- `media_decoder_spawn` (function) `include/media_decoder.h:104` `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd);` -- Spawns a media decoder child via fork+exec.

## include/net_realm.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/net_realm.c`, `tests/test_net_realm.c`
- `NR_ROUTE_BLOCKED` (function) `include/net_realm.h:57` `* NR_ROUTE_BLOCKED (fail closed: never route what cannot be classified). A realm * whose proxy is not enabled =>...`
- `address` (function) `include/net_realm.h:62` `* and encrypts by its address (the I2P destination / onion key), so http over it is * not a downgrade. Currently...`
- `nr_realm_allows_http` (function) `include/net_realm.h:66` `int nr_realm_allows_http(nr_realm r);` -- 1 iff plain http:// is acceptable for this realm.
- `nr_realm_name` (function) `include/net_realm.h:69` `const char *nr_realm_name(nr_realm r);` -- 1 iff plain http:// is acceptable for this realm.
- `nr_route_name` (function) `include/net_realm.h:70` `const char *nr_route_name(nr_route r);`

## include/os_sandbox.h
Imported by: `src/os_sandbox.c`, `src/renderer.c`, `src/tab.c`, `tests/test_os_sandbox.c`
- `flags` (function) `include/os_sandbox.h:39` `* permission also depends on the protection flags (see os_prot_allowed / W^X). */ int os_policy_allows(long syscall_nr);`
- `os_policy_size` (function) `include/os_sandbox.h:43` `size_t os_policy_size(void);` -- Nonzero iff syscall_nr is on the strict allowlist (mirrors the BPF program).
- `os_prot_allowed` (function) `include/os_sandbox.h:52` `int os_prot_allowed(long syscall_nr, unsigned long prot);` -- Pure mirror of the BPF program's EFFECTIVE decision for memory syscalls (W^X).
- `denied` (function) `include/os_sandbox.h:59` `* request PROT_EXEC are denied (see os_prot_allowed). * Returns OS_ERR_UNSUPPORTED on platforms without seccomp-bpf...`
- `namespace` (function) `include/os_sandbox.h:75` `* namespace (the unprivileged enabler), network (the worker never needs the * network -- the parent fetches and...`
- `os_namespace_flags` (function) `include/os_sandbox.h:81` `int os_namespace_flags(void);` -- The set of CLONE_* namespace flags the worker isolates into: a new user namespace (the unprivileged enabler)...
- `os_landlock_abi` (function) `include/os_sandbox.h:114` `int os_landlock_abi(void);` -- /* What a Landlock rule permits at/below a path. typedef enum os_fs_access { OS_FS_NONE       = 0, /* no access (not...

## include/page_view.h
Depends on: `include/css.h`, `include/dom.h`, `include/html_parse.h`
Imported by: `include/box_tree.h`, `include/frame_host.h`, `include/render_doc.h`, `include/tab.h`, `src/dom_debug.c`, `src/freedom.c`, `src/page_view.c`, `src/tab.c`, `tests/test_box_tree.c`, `tests/test_dom_debug.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`
- `container` (function) `include/page_view.h:232` `* cont_id groups runs of one container (-1 = none);`
- `bx_display` (function) `include/page_view.h:233` `* bx_display (flex/grid);`
- `order` (function) `include/page_view.h:297` `* groups the runs of ONE floated element in document order (-1 = not in a float);`
- `itself` (function) `include/page_view.h:361` `* by itself (bx_width_cap2);`
- `CSS_LEN_UNSET` (function) `include/page_view.h:560` `* CSS_LEN_UNSET (unset) / CSS_LEN_AUTO. z_index is signed, or CSS_LEN_UNSET. v1 * paints only position:relative (an...`
- `scale` (function) `include/page_view.h:635` `* scale(1)) and rotate in whole degrees (transform_rotate);`
- `tree` (function) `include/page_view.h:676` `* box tree (a mask covers its whole subtree);`
- `declare` (function) `include/page_view.h:865` `* margin the author did not declare (px or %), 0 on a declared side (the body's * own box, or nothing for 0, owns...`
- `nonzero` (function) `include/page_view.h:877` `* when nonzero (JS allowed for this page) the <noscript> subtree is suppressed. */ pv_status pv_build_ex(const...`
- `resolved` (function) `include/page_view.h:884` `* author CSS is still resolved (the presentation layer decides whether to apply it). * pv_build_ex is pv_build_full...`
- `policy` (function) `include/page_view.h:892` `* TRUSTED parent under full network policy (spec/tab.md §8) -- page_view stays * pure and never fetches. The...`
- `pv_computed_new` (function) `include/page_view.h:914` `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css, size_t extern_len...`
- `pv_computed_get` (function) `include/page_view.h:921` `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st, double *font_px, int *inherited_color);` -- Resolves native_el (a dom_native_node pointer of the SAME document) into *st; when non-NULL, *font_px receives its...
- `pv_computed_free` (function) `include/page_view.h:924` `void pv_computed_free(pv_computed *pc);`
- `cause` (function) `include/page_view.h:928` `* cause (spec/css_drops.md). Builds no view and changes nothing -- it exists so * "what is this page's CSS losing?"...`
- `pv_new` (function) `include/page_view.h:940` `pv_view *pv_new(void);` -- Allocates an empty view (used by the IPC deserialiser to rebuild a view on the * receiving side).
- `form` (function) `include/page_view.h:959` `* form (-1 if none);`
- `pv_set_emphasis` (function) `include/page_view.h:991` `void pv_set_emphasis(pv_view *v, int bold, int italic);` -- Sets the inline emphasis flags (bold from <b>/<strong>/<th>, italic from <i>/<em>) on the most recently appended run.
- `default` (function) `include/page_view.h:996` `* structure is carried by default (not gated by caps.css). */ void pv_set_indent(pv_view *v, int indent);`
- `pv_set_color` (function) `include/page_view.h:999` `void pv_set_color(pv_view *v, int fg_rgb);`
- `pv_set_bgcolor` (function) `include/page_view.h:1006` `void pv_set_bgcolor(pv_view *v, int bg_rgb);` -- Sets the author background-color (packed 0xRRGGBB, or -1 for none) on the most recently appended run.
- `pv_set_text_style` (function) `include/page_view.h:1015` `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs, int line_scale, int text_decoration);` -- Sets the author text presentation (text_align as a css_align, font_scale as a font-size percent or 0, font_abs as 1...
- `pv_text_ext_reset` (function) `include/page_view.h:1072` `void pv_text_ext_reset(pv_text_ext *e);` -- Gradient text (2026-07-19). text_fill: -webkit-text-fill-color from the nearest ancestor that sets it (packed /...
- `ancestors` (function) `include/page_view.h:1077` `* itself by walking its ancestors (css_visibility, 0 = unset). * * An explicit value on the run WINS over the box...`
- `pv_set_text_ext` (function) `include/page_view.h:1087` `void pv_set_text_ext(pv_view *v, const pv_text_ext *e);`
- `pv_set_grad_text` (function) `include/page_view.h:1093` `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4);` -- Sets the gradient-text fill (grad_text_*) verbatim on the most recently appended run. n < 2 is a no-op (no gradient).
- `run` (function) `include/page_view.h:1096` `* run (cont_id, the bx_display, the parsed gap/justify/cols, plus flex-wrap/ * row-gap/align-items). No-op on an...`
- `pv_set_row_span` (function) `include/page_view.h:1109` `void pv_set_row_span(pv_view *v, int row_span);` -- Sets the container's grid track sizes and this run's ITEM column span on the most recently appended run...
- `pv_set_grid_area` (function) `include/page_view.h:1113` `void pv_set_grid_area(pv_view *v, int row_start, int col_start);` -- Sets the last run's RESOLVED named-grid cell (-1, -1 = auto-placed).
- `pv_set_grid_rows` (function) `include/page_view.h:1114` `void pv_set_grid_rows(pv_view *v, int grid_rows);`
- `pv_set_ua_tag` (function) `include/page_view.h:1119` `void pv_set_ua_tag(pv_view *v, int ua_tag);` -- Sets the last run's ua_tag (a bx_ua_tag code: the user-agent box identity of its nearest block-level ancestor).
- `pv_set_cont_box` (function) `include/page_view.h:1123` `void pv_set_cont_box(pv_view *v, int cont_box_id);` -- Sets the last run's cont_box_id (the box enclosing its container's items; -1 = * none).
- `pv_set_grid` (function) `include/page_view.h:1124` `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span);`
- `pv_set_flex` (function) `include/page_view.h:1132` `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis, int flex_order, int flex_direction, int...` -- Stage 3: sets the flex per-item values on the most recently appended run — the ITEM's resolved grow/shrink (x100, -1...
- `pv_set_flex_mauto` (function) `include/page_view.h:1135` `void pv_set_flex_mauto(pv_view *v, int mauto);` -- Stage 3: sets the flex per-item values on the most recently appended run — the ITEM's resolved grow/shrink (x100, -1...
- `pv_set_cont_item` (function) `include/page_view.h:1139` `void pv_set_cont_item(pv_view *v, int cont_item);` -- Sets the container-item ordinal on the most recently appended run (-1 = none). * No-op on an empty or NULL view; the...
- `pv_set_float_w` (function) `include/page_view.h:1150` `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box, int float_ow, int float_ow_pct, int...` -- Stamps the float founder's own declared width halves (pv_run.float_w) on the * most recently appended run.
- `pv_set_float` (function) `include/page_view.h:1153` `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear, int float_ml, int float_ml_pct, int...`
- `pv_set_box` (function) `include/page_view.h:1163` `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w, int box_center, int box_mt, int box_mb);` -- Sets the author box model on the most recently appended run (left/right insets, width cap, centered flag, and...
- `pv_set_box_pct` (function) `include/page_view.h:1169` `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct, int box_mt_pct, int box_mb_pct);` -- Sets the symbolic percentage width cap (per-mille, 0 = none; Hito 32) on the most recently appended run.
- `pv_set_box_maxw` (function) `include/page_view.h:1174` `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct);` -- Sets the max-width cap (px half, 0 = none; per-mille half, 0 = none) on the most * recently appended run.
- `pv_set_node_id` (function) `include/page_view.h:1179` `void pv_set_node_id(pv_view *v, dom_node_id node_id);` -- Keystone (Stage 0) setter for the most recently appended run: the dom_node_id of the source element.
- `pv_set_block_id` (function) `include/page_view.h:1184` `void pv_set_block_id(pv_view *v, int block_id);` -- Box engine (Hito 23b-8) setter for the most recently appended run: the block_id of the box-carrying block it belongs...
- `pv_set_own_box` (function) `include/page_view.h:1188` `void pv_set_own_box(pv_view *v, int box_id);` -- Records the replaced element's own box def index on the last appended run.
- `pv_set_oof` (function) `include/page_view.h:1192` `void pv_set_oof(pv_view *v, int oof);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_justify_self` (function) `include/page_view.h:1195` `void pv_set_justify_self(pv_view *v, int justify_self);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_block_node` (function) `include/page_view.h:1198` `void pv_set_block_node(pv_view *v, dom_node_id id);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_br_line` (function) `include/page_view.h:1206` `void pv_set_br_line(pv_view *v, int br_line);` -- Sets the last appended run's PV_BR_* flags (see pv_run.br_line); other bits * are dropped.
- `pv_cont_count` (function) `include/page_view.h:1221` `size_t pv_cont_count(const pv_view *v);` -- pv_cont_count is v->ncont (0 when v is NULL); pv_cont_at returns conts[i] * (i == a cont_id) or NULL when out of...
- `pv_cont_at` (function) `include/page_view.h:1222` `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i);`
- `pv_set_input_checked` (function) `include/page_view.h:1226` `void pv_set_input_checked(pv_view *v, int checked);` -- Sets the input's checked state (-1 n/a, 0 unchecked, 1 checked) on the most * recently appended run.
- `pv_set_input_placeholder` (function) `include/page_view.h:1230` `void pv_set_input_placeholder(pv_view *v, int ph_color);` -- Sets the input's checked state (-1 n/a, 0 unchecked, 1 checked) on the most * recently appended run.
- `pv_svg_append_root_attrs` (function) `include/page_view.h:1236` `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs, size_t *out_len);` -- Appends attrs (e.g.
- `pv_placeholder_color` (function) `include/page_view.h:1239` `int pv_placeholder_color(const css_style *ph);` -- Appends attrs (e.g.
- `pv_set_input_select_opts` (function) `include/page_view.h:1243` `void pv_set_input_select_opts(pv_view *v, const char *select_opts);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_free` (function) `include/page_view.h:1246` `void pv_free(pv_view *v);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_count` (function) `include/page_view.h:1249` `size_t pv_count(const pv_view *v);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_at` (function) `include/page_view.h:1250` `const pv_run *pv_at(const pv_view *v, size_t i);`
- `pv_box_count` (function) `include/page_view.h:1254` `size_t pv_box_count(const pv_view *v);` -- Box tree accessors (Step D). pv_box_count is the number of box definitions; * pv_box_at returns boxes[i] (i == a...
- `pv_box_at` (function) `include/page_view.h:1255` `const pv_box_def *pv_box_at(const pv_view *v, size_t i);`

## include/pdf_export.h
Imported by: `gui/browser_ui.c`, `src/download.c`, `src/pdf_export.c`, `tests/test_pdf_export.c`
- `fallback` (function) `include/pdf_export.h:46` `* fallback (PE_ERR_OVERFLOW, out left empty). title == NULL is treated as empty. * Does NOT append the extension...`
- `trusted` (function) `include/pdf_export.h:51` `* dir is trusted (chosen by the app from XDG/$HOME);`
- `literal` (function) `include/pdf_export.h:52` `* trusted literal (e.g. PE_EXT / PE_EXT_PNG);`
- `pe_paginate` (function) `include/pdf_export.h:70` `size_t pe_paginate(const double *tops, const double *heights, size_t n, double page_h, int *out_page, double...` -- Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h...


Next: [API_p5.md](API_p5.md)
