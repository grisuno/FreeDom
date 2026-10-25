# API (page 4 of 11)
Previous: [API_p3.md](API_p3.md)

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
- `process` (function) `include/dom.h:255` `* modules in the same process (style resolution). NULL for a bad or non-element * handle. Valid until the next...`

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

## include/fb_panes.h
Imported by: `gui/browser_ui.c`, `src/fb_panes.c`, `src/freedom.c`, `tests/test_fb_panes.c`, `tests/test_js_dom.c`
- `fbp_tab_label` (function) `include/fb_panes.h:30` `const char *fbp_tab_label(int tab);` -- typedef enum fbp_tab { FBP_CONSOLE = 0, FBP_HTML, FBP_CSS, FBP_SCRIPT, FBP_NET, FBP_COUNT } fbp_tab; #define...
- `fbp_tab_from_name` (function) `include/fb_panes.h:33` `int fbp_tab_from_name(const char *name);` -- FBP_HTML, FBP_CSS, FBP_SCRIPT, FBP_NET, FBP_COUNT } fbp_tab; #define FBP_SELECTOR_MAX 256   /* bytes of the user's...
- `fbp_tab_wrap` (function) `include/fb_panes.h:36` `int fbp_tab_wrap(int tab, int dir);` -- FBP_NET, FBP_COUNT } fbp_tab; #define FBP_SELECTOR_MAX 256   /* bytes of the user's argument (selector / index /...
- `fbp_tab_span` (function) `include/fb_panes.h:39` `void fbp_tab_span(int tab, double cell_w, double pad_cells, double *x, double *w);` -- #define FBP_SELECTOR_MAX 256   /* bytes of the user's argument (selector / index / filter) #define FBP_EXPR_MAX...
- `fbp_tab_at` (function) `include/fb_panes.h:42` `int fbp_tab_at(double x, double cell_w, double pad_cells);` -- /* Label of a tab; an out-of-range id is the console.
- `fbp_is_pane` (function) `include/fb_panes.h:45` `int fbp_is_pane(int tab);` -- /* Tab named `name` (case-insensitive), or -1 when unknown / NULL. int fbp_tab_from_name(const char *name); /* The...
- `fbp_js_quote` (function) `include/fb_panes.h:49` `size_t fbp_js_quote(const char *s, size_t n, char *out, size_t cap);` -- JS string literal for s[0,n) (double-quoted).
- `fbp_expr` (function) `include/fb_panes.h:53` `size_t fbp_expr(int tab, const char *sel, size_t n, char *out, size_t cap);` -- The expression that fills `tab`'s panel for argument sel[0,n); NUL-terminated in out. * Returns its length, or 0 for...

## include/flex_layout.h
Imported by: `include/box_tree.h`, `src/css.c`, `src/dom_debug.c`, `src/flex_layout.c`, `src/page_view.c`, `src/tab.c`, `tests/test_css.c`, `tests/test_dom_debug.c`, `tests/test_flex_layout.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`
- `size` (function) `include/flex_layout.h:60` `* content size (px);`
- `out` (function) `include/flex_layout.h:62` `* fx_result to out (caller-owned). n == 0 is a no-op (out may be NULL). */ fx_status fx_flex_line(const fx_item...`
- `fx_grid_cell` (function) `include/flex_layout.h:74` `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col);` -- Row and column of the index-th item placed row-major into ncols columns. * ncols == 0 yields row = col = 0...
- `number` (function) `include/flex_layout.h:106` `* line number (negative counts from the end). */ #define FX_GL_AUTO 0 #define FX_GL_SPAN_BASE (1 << 20) #define...`
- `fx_grid_line_parse` (function) `include/flex_layout.h:117` `int fx_grid_line_parse(const char *v, int *start, int *end);` -- The shorthand `<side> [ / <side> ]` (no slash => end is auto).
- `fx_grid_line_resolve` (function) `include/flex_layout.h:122` `void fx_grid_line_resolve(int start, int end, int ntracks, int *pos0, int *span);` -- Resolves a start/end pair against ntracks explicit tracks: *pos0 = 0-based start track or -1 (auto-place), *span >= 1.
- `fx_autofill_count` (function) `include/flex_layout.h:129` `size_t fx_autofill_count(double avail, double gap, double minw);` -- repeat(auto-fill, minmax(min, max)): how many min-wide tracks fit in avail (CSS Grid 1 7.2.3.2; one gap between tracks).
- `fx_grid_area_hash` (function) `include/flex_layout.h:153` `unsigned fx_grid_area_hash(const char *name);` -- FNV-1a of a trimmed, case-sensitive CSS identifier; never returns 0 for a non-empty name (0 is reserved for "unnamed").
- `offset` (function) `include/flex_layout.h:171` `* offset (from the content start, clamped to >= 0) to out_x[n]. The band does NOT wrap * (v1): an item that would...`
- `required` (function) `include/flex_layout.h:184` `* out_row is required (NULL with n > 0 yields FX_ERR_NULL_ARG);`
- `widths` (function) `include/flex_layout.h:194` `* the OUTER widths (width + ml + mr, clamped >= 0, so a negative margin narrows * the slot and a positive one widens...`
- `FX_ERR_NULL_ARG` (function) `include/flex_layout.h:228` `* Returns FX_ERR_NULL_ARG (a required pointer NULL with n > 0), FX_ERR_RANGE * (negative h/avail, or n > FX_MAX_ITEMS);`
- `space` (function) `include/flex_layout.h:234` `* line order: positive free space (avail - sizes - gaps) is split equally among every * auto margin...`
- `fx_auto_min_size` (function) `include/flex_layout.h:265` `double fx_auto_min_size(double min_content, double basis, double author_min, int scroll_container);` -- units as fx_item.basis.
- `fx_justify_name` (function) `include/flex_layout.h:321` `const char *fx_justify_name(fx_justify j);` -- Stable, short English name of a justify mode for structured/agent output.
- `height` (function) `include/flex_layout.h:327` `* used height (h_out);`
- `it` (function) `include/flex_layout.h:344` `* children that claim it (spec/flex_layout.md, tanda 44): proportionally to * grow[i] (x100) when any grows, else...`
- `win` (function) `include/flex_layout.h:352` `* margins win (both = centre, left only = end);`
- `fx_cross_offset` (function) `include/flex_layout.h:354` `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r);` -- Cross-axis (horizontal) offset of a column item of width w in avail px. auto margins win (both = centre, left only =...

## include/frame_clock.h
Imported by: `gui/browser_ui.c`, `src/frame_clock.c`, `tests/test_frame_clock.c`
- `fc_init` (function) `include/frame_clock.h:20` `void fc_init(fc_clock *c);`
- `fc_set_active` (function) `include/frame_clock.h:21` `void fc_set_active(fc_clock *c, int active);`
- `fc_needs_tick` (function) `include/frame_clock.h:22` `int fc_needs_tick(const fc_clock *c);`
- `fc_interval_ms` (function) `include/frame_clock.h:23` `int fc_interval_ms(const fc_clock *c);`

## include/freebug.h
Imported by: `gui/browser_ui.c`, `include/js_dom.h`, `include/tab.h`, `src/freebug.c`, `src/freedom.c`, `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/tab.c`, `tests/test_freebug.c`
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
- `hb_count` (function) `include/hostblock.h:79` `size_t hb_count(const hb_set *s, hb_list list);` -- Number of unique domains on the given list (for tests/diagnostics).

## include/hostedit.h
Imported by: `gui/browser_ui.c`, `src/hostedit.c`, `tests/test_hostedit.c`
- `he_text_has_host` (function) `include/hostedit.h:46` `int he_text_has_host(const char *text, const char *host);` -- Returns 1 if text (the body of a hosts-format file) already lists host as a domain token on a non-comment line...
- `he_suggest` (function) `include/hostedit.h:55` `int he_suggest(const char *text, const char *query, char results[][HE_MAX_HOST + 1], int max);` -- Omnibar autocomplete: treats allow.conf (a hosts-format text) as a favorites list.

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
- `idn_defaults` (function) `include/identity.h:45` `void idn_defaults(idn_config *c);` -- enum { IDN_REJ_UA   = 1 << 0, IDN_REJ_LANG = 1 << 1, IDN_REJ_GEO  = 1 << 2 }; typedef struct idn_config { char...
- `idn_is_default` (function) `include/identity.h:48` `int idn_is_default(const idn_config *c);` -- IDN_REJ_GEO  = 1 << 2 }; typedef struct idn_config { char   user_agent[IDN_UA_MAX];  /* "" = FP_USER_AGENT char...
- `idn_set_user_agent` (function) `include/identity.h:51` `int idn_set_user_agent(idn_config *c, const char *ua);` -- typedef struct idn_config { char   user_agent[IDN_UA_MAX];  /* "" = FP_USER_AGENT char   languages[IDN_LANG_MAX]; /*...
- `idn_set_languages` (function) `include/identity.h:52` `int idn_set_languages(idn_config *c, const char *list);`
- `idn_set_geo` (function) `include/identity.h:53` `int idn_set_geo(idn_config *c, double lat, double lon, double accuracy_m);`
- `idn_clear_geo` (function) `include/identity.h:54` `void idn_clear_geo(idn_config *c);`
- `idn_user_agent` (function) `include/identity.h:57` `const char *idn_user_agent(const idn_config *c);` -- /* The anti_fp identity, geolocation off.
- `idn_accept_language` (function) `include/identity.h:58` `size_t idn_accept_language(const idn_config *c, char *out, size_t cap);`
- `idn_primary_language` (function) `include/identity.h:59` `size_t idn_primary_language(const idn_config *c, char *out, size_t cap);`
- `idn_serialize` (function) `include/identity.h:63` `size_t idn_serialize(const idn_config *c, char *out, size_t cap);` -- One-line text form for prefs and the worker IPC.
- `idn_parse` (function) `include/identity.h:67` `void idn_parse(idn_config *c, const char *text);` -- Parses idn_serialize output field by field; an invalid field keeps its default.
- `idn_apply_query` (function) `include/identity.h:70` `unsigned idn_apply_query(idn_config *c, const char *query);` -- Parses idn_serialize output field by field; an invalid field keeps its default.
- `idn_render_page` (function) `include/identity.h:73` `size_t idn_render_page(const idn_config *c, char *out, size_t cap);` -- Parses idn_serialize output field by field; an invalid field keeps its default.

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
- `opaque` (function) `include/js_dom.h:66` `* the engine runtime opaque (unreachable from script);`
- `global` (function) `include/js_dom.h:73` `* globals: page scripts never see them and an existing page global (jQuery's `$`) is * never replaced. Read-only...`
- `jd_install_repl_api` (function) `include/js_dom.h:82` `* jd_install_repl_api (the shim reads and deletes the carrier global, so a page script never * sees it). css == NULL...`
- `place` (function) `include/js_dom.h:87` `* configured place (spec/identity.md), no sensor, no network. Call it ONLY for a trusted host * with geolocation set...`
- `getComputedStyle` (function) `include/js_dom.h:108` `* getComputedStyle (spec/js_computed_style.md). fn writes the computed value of the * kebab-case `prop` of element h...`
- `jd_click_state_free` (function) `include/js_dom.h:118` `* jd_click_state_free(). Bound to one context via jd_install_events(). */ jd_click_state *jd_click_state_new(void);`
- `run` (function) `include/js_dom.h:127` `* run (no handler registered, or handlers ran without calling preventDefault()), * and 0 if a handler called...`
- `preventDefault` (function) `include/js_dom.h:134` `* preventDefault() was called, 1 if the default (form submission) should proceed. * ctx == NULL or no form found =>...`
- `host` (function) `include/js_dom.h:163` `* for a trusted host (allow.conf AND js.conf);`
- `jd_get_cookies` (function) `include/js_dom.h:174` `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz);` -- Serialises the page's current cookie jar ("name=value; ...") into buf (bounded, NUL-terminated) and returns its...
- `out_status` (function) `include/js_dom.h:182` `* On success returns 0 and sets *out_status (HTTP status, 0 if unknown), *out_body / * *out_body_len (response...`
- `jd_process_iframes` (function) `include/js_dom.h:203` `* BEFORE jd_process_iframes() (so iframes are in the DOM for it to process). * ctx == NULL => JD_ERR_NULL_ARG. */...`
- `URLs` (function) `include/js_dom.h:210` `* video URLs (.m3u8 then .mp4 patterns), and creates <video> elements in the document for * any found. Does NOT...`
- `jd_video_from_scripts` (function) `include/js_dom.h:224` `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts, const size_t *script_lens, size_t...` -- Creates <iframe> elements in the DOM from video data (`video[N]` / `video_data`) found in inline script text...
- `jd_flush_custom_elements` (function) `include/js_dom.h:235` `void jd_flush_custom_elements(js_context *ctx);` -- Reconciles Custom Elements (spec/js_custom_elements.md): upgrades the elements whose tag was just defined and fires...

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
- `js_result_free` (function) `include/js_sandbox.h:161` `void js_result_free(js_result *res);` -- Adjusts the wall-clock budget armed on each subsequent js_eval.
- `js_pump_jobs` (function) `include/js_sandbox.h:169` `int js_pump_jobs(js_context *ctx, int max_jobs);` -- Runs up to max_jobs pending microtasks/jobs (promise reactions queued by the last eval), under the context's current...
- `handle` (function) `include/js_sandbox.h:172` `* as an opaque handle (so this header stays free of backend types), or NULL. * Valid only while ctx is alive....`
- `js_set_current_script` (function) `include/js_sandbox.h:181` `void js_set_current_script(js_context *ctx, const char *src, const char *type);` -- Sets document.currentScript on the global object so external scripts can read their own src / type / data-*...

## include/js_trusted.h
Depends on: `include/js_dom.h`, `include/js_sandbox.h`
Imported by: `src/js_trusted.c`, `src/tab.c`, `tests/test_js_dom.c`
- `null` (function) `include/js_trusted.h:24` `* noopener semantics: it returns null (no cross-window reference, so no same-origin * channel) and only records up...`
- `jt_take_opens` (function) `include/js_trusted.h:42` `char *jt_take_opens(js_context *ctx);` -- The parent installed a new geometry table (layout or scroll changed): re-evaluates every observed target and fires a...
- `parent` (function) `include/js_trusted.h:69` `* socket: the object records operations for the parent (jt_take_ws). */ jd_status jt_enable_ws(js_context *ctx);`
- `jt_take_ws` (function) `include/js_trusted.h:75` `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap);` -- Drains up to cap recorded operations into ops (each data owned; release with jt_ws_ops_free).
- `jt_ws_ops_free` (function) `include/js_trusted.h:76` `void jt_ws_ops_free(jt_ws_op *ops, size_t n);`
- `jt_ws_event` (function) `include/js_trusted.h:81` `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len);` -- Delivers a socket event from the parent: data enters JS as a VALUE (a string for text, an ArrayBuffer for binary...
- `jt_take_storage` (function) `include/js_trusted.h:93` `int jt_take_storage(js_context *ctx, char **out, size_t *len);` -- When the store changed since the last call, returns 1 with an owned snapshot of * the whole store in *out (length...
- `realm` (function) `include/js_trusted.h:96` `* runs in its own realm (js_install_realms) of this context's runtime, inside the * same confined process and...`

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
Imported by: `include/box_tree.h`, `include/render_doc.h`, `include/tab.h`, `src/dom_debug.c`, `src/freedom.c`, `src/page_view.c`, `src/tab.c`, `tests/test_box_tree.c`, `tests/test_dom_debug.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`
- `container` (function) `include/page_view.h:230` `* cont_id groups runs of one container (-1 = none);`
- `bx_display` (function) `include/page_view.h:231` `* bx_display (flex/grid);`
- `order` (function) `include/page_view.h:295` `* groups the runs of ONE floated element in document order (-1 = not in a float);`
- `itself` (function) `include/page_view.h:359` `* by itself (bx_width_cap2);`
- `CSS_LEN_UNSET` (function) `include/page_view.h:555` `* CSS_LEN_UNSET (unset) / CSS_LEN_AUTO. z_index is signed, or CSS_LEN_UNSET. v1 * paints only position:relative (an...`
- `scale` (function) `include/page_view.h:630` `* scale(1)) and rotate in whole degrees (transform_rotate);`
- `tree` (function) `include/page_view.h:671` `* box tree (a mask covers its whole subtree);`
- `declare` (function) `include/page_view.h:860` `* margin the author did not declare (px or %), 0 on a declared side (the body's * own box, or nothing for 0, owns...`
- `nonzero` (function) `include/page_view.h:872` `* when nonzero (JS allowed for this page) the <noscript> subtree is suppressed. */ pv_status pv_build_ex(const...`
- `resolved` (function) `include/page_view.h:879` `* author CSS is still resolved (the presentation layer decides whether to apply it). * pv_build_ex is pv_build_full...`
- `policy` (function) `include/page_view.h:887` `* TRUSTED parent under full network policy (spec/tab.md §8) -- page_view stays * pure and never fetches. The...`
- `pv_computed_new` (function) `include/page_view.h:909` `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css, size_t extern_len...`
- `pv_computed_get` (function) `include/page_view.h:916` `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st, double *font_px, int *inherited_color);` -- Resolves native_el (a dom_native_node pointer of the SAME document) into *st; when non-NULL, *font_px receives its...
- `pv_computed_free` (function) `include/page_view.h:919` `void pv_computed_free(pv_computed *pc);`
- `cause` (function) `include/page_view.h:923` `* cause (spec/css_drops.md). Builds no view and changes nothing -- it exists so * "what is this page's CSS losing?"...`
- `pv_new` (function) `include/page_view.h:935` `pv_view *pv_new(void);` -- Allocates an empty view (used by the IPC deserialiser to rebuild a view on the * receiving side).
- `form` (function) `include/page_view.h:954` `* form (-1 if none);`
- `pv_set_emphasis` (function) `include/page_view.h:986` `void pv_set_emphasis(pv_view *v, int bold, int italic);` -- Sets the inline emphasis flags (bold from <b>/<strong>/<th>, italic from <i>/<em>) on the most recently appended run.
- `default` (function) `include/page_view.h:991` `* structure is carried by default (not gated by caps.css). */ void pv_set_indent(pv_view *v, int indent);`
- `pv_set_color` (function) `include/page_view.h:994` `void pv_set_color(pv_view *v, int fg_rgb);`
- `pv_set_bgcolor` (function) `include/page_view.h:1001` `void pv_set_bgcolor(pv_view *v, int bg_rgb);` -- Sets the author background-color (packed 0xRRGGBB, or -1 for none) on the most recently appended run.
- `pv_set_text_style` (function) `include/page_view.h:1010` `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs, int line_scale, int text_decoration);` -- Sets the author text presentation (text_align as a css_align, font_scale as a font-size percent or 0, font_abs as 1...
- `pv_text_ext_reset` (function) `include/page_view.h:1065` `void pv_text_ext_reset(pv_text_ext *e);` -- Gradient text (2026-07-19). text_fill: -webkit-text-fill-color from the nearest ancestor that sets it (packed /...
- `ancestors` (function) `include/page_view.h:1070` `* itself by walking its ancestors (css_visibility, 0 = unset). * * An explicit value on the run WINS over the box...`
- `pv_set_text_ext` (function) `include/page_view.h:1080` `void pv_set_text_ext(pv_view *v, const pv_text_ext *e);`
- `pv_set_grad_text` (function) `include/page_view.h:1086` `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4);` -- Sets the gradient-text fill (grad_text_*) verbatim on the most recently appended run. n < 2 is a no-op (no gradient).
- `run` (function) `include/page_view.h:1089` `* run (cont_id, the bx_display, the parsed gap/justify/cols, plus flex-wrap/ * row-gap/align-items). No-op on an...`
- `pv_set_row_span` (function) `include/page_view.h:1102` `void pv_set_row_span(pv_view *v, int row_span);` -- Sets the container's grid track sizes and this run's ITEM column span on the most recently appended run...
- `pv_set_grid_area` (function) `include/page_view.h:1106` `void pv_set_grid_area(pv_view *v, int row_start, int col_start);` -- Sets the last run's RESOLVED named-grid cell (-1, -1 = auto-placed).
- `pv_set_grid_rows` (function) `include/page_view.h:1107` `void pv_set_grid_rows(pv_view *v, int grid_rows);`
- `pv_set_ua_tag` (function) `include/page_view.h:1112` `void pv_set_ua_tag(pv_view *v, int ua_tag);` -- Sets the last run's ua_tag (a bx_ua_tag code: the user-agent box identity of its nearest block-level ancestor).
- `pv_set_cont_box` (function) `include/page_view.h:1116` `void pv_set_cont_box(pv_view *v, int cont_box_id);` -- Sets the last run's cont_box_id (the box enclosing its container's items; -1 = * none).
- `pv_set_grid` (function) `include/page_view.h:1117` `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span);`
- `pv_set_flex` (function) `include/page_view.h:1125` `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis, int flex_order, int flex_direction, int...` -- Stage 3: sets the flex per-item values on the most recently appended run — the ITEM's resolved grow/shrink (x100, -1...
- `pv_set_flex_mauto` (function) `include/page_view.h:1128` `void pv_set_flex_mauto(pv_view *v, int mauto);` -- Stage 3: sets the flex per-item values on the most recently appended run — the ITEM's resolved grow/shrink (x100, -1...
- `pv_set_cont_item` (function) `include/page_view.h:1132` `void pv_set_cont_item(pv_view *v, int cont_item);` -- Sets the container-item ordinal on the most recently appended run (-1 = none). * No-op on an empty or NULL view; the...
- `pv_set_float_w` (function) `include/page_view.h:1143` `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box, int float_ow, int float_ow_pct, int...` -- Stamps the float founder's own declared width halves (pv_run.float_w) on the * most recently appended run.
- `pv_set_float` (function) `include/page_view.h:1146` `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear, int float_ml, int float_ml_pct, int...`
- `pv_set_box` (function) `include/page_view.h:1156` `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w, int box_center, int box_mt, int box_mb);` -- Sets the author box model on the most recently appended run (left/right insets, width cap, centered flag, and...
- `pv_set_box_pct` (function) `include/page_view.h:1162` `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct, int box_mt_pct, int box_mb_pct);` -- Sets the symbolic percentage width cap (per-mille, 0 = none; Hito 32) on the most recently appended run.
- `pv_set_box_maxw` (function) `include/page_view.h:1167` `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct);` -- Sets the max-width cap (px half, 0 = none; per-mille half, 0 = none) on the most * recently appended run.
- `pv_set_node_id` (function) `include/page_view.h:1172` `void pv_set_node_id(pv_view *v, dom_node_id node_id);` -- Keystone (Stage 0) setter for the most recently appended run: the dom_node_id of the source element.
- `pv_set_block_id` (function) `include/page_view.h:1177` `void pv_set_block_id(pv_view *v, int block_id);` -- Box engine (Hito 23b-8) setter for the most recently appended run: the block_id of the box-carrying block it belongs...
- `pv_set_own_box` (function) `include/page_view.h:1181` `void pv_set_own_box(pv_view *v, int box_id);` -- Records the replaced element's own box def index on the last appended run.
- `pv_set_oof` (function) `include/page_view.h:1185` `void pv_set_oof(pv_view *v, int oof);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_justify_self` (function) `include/page_view.h:1188` `void pv_set_justify_self(pv_view *v, int justify_self);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_block_node` (function) `include/page_view.h:1191` `void pv_set_block_node(pv_view *v, dom_node_id id);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_br_line` (function) `include/page_view.h:1199` `void pv_set_br_line(pv_view *v, int br_line);` -- Sets the last appended run's PV_BR_* flags (see pv_run.br_line); other bits * are dropped.
- `pv_cont_count` (function) `include/page_view.h:1214` `size_t pv_cont_count(const pv_view *v);` -- pv_cont_count is v->ncont (0 when v is NULL); pv_cont_at returns conts[i] * (i == a cont_id) or NULL when out of...
- `pv_cont_at` (function) `include/page_view.h:1215` `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i);`
- `pv_set_input_checked` (function) `include/page_view.h:1219` `void pv_set_input_checked(pv_view *v, int checked);` -- Sets the input's checked state (-1 n/a, 0 unchecked, 1 checked) on the most * recently appended run.
- `pv_set_input_placeholder` (function) `include/page_view.h:1223` `void pv_set_input_placeholder(pv_view *v, int ph_color);` -- Sets the input's checked state (-1 n/a, 0 unchecked, 1 checked) on the most * recently appended run.
- `pv_svg_append_root_attrs` (function) `include/page_view.h:1229` `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs, size_t *out_len);` -- Appends attrs (e.g.
- `pv_placeholder_color` (function) `include/page_view.h:1232` `int pv_placeholder_color(const css_style *ph);` -- Appends attrs (e.g.
- `pv_set_input_select_opts` (function) `include/page_view.h:1236` `void pv_set_input_select_opts(pv_view *v, const char *select_opts);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_free` (function) `include/page_view.h:1239` `void pv_free(pv_view *v);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_count` (function) `include/page_view.h:1242` `size_t pv_count(const pv_view *v);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_at` (function) `include/page_view.h:1243` `const pv_run *pv_at(const pv_view *v, size_t i);`
- `pv_box_count` (function) `include/page_view.h:1247` `size_t pv_box_count(const pv_view *v);` -- Box tree accessors (Step D). pv_box_count is the number of box definitions; * pv_box_at returns boxes[i] (i == a...
- `pv_box_at` (function) `include/page_view.h:1248` `const pv_box_def *pv_box_at(const pv_view *v, size_t i);`

## include/pdf_export.h
Imported by: `gui/browser_ui.c`, `src/download.c`, `src/pdf_export.c`, `tests/test_pdf_export.c`
- `fallback` (function) `include/pdf_export.h:46` `* fallback (PE_ERR_OVERFLOW, out left empty). title == NULL is treated as empty. * Does NOT append the extension...`
- `trusted` (function) `include/pdf_export.h:51` `* dir is trusted (chosen by the app from XDG/$HOME);`
- `literal` (function) `include/pdf_export.h:52` `* trusted literal (e.g. PE_EXT / PE_EXT_PNG);`
- `pe_paginate` (function) `include/pdf_export.h:70` `size_t pe_paginate(const double *tops, const double *heights, size_t n, double page_h, int *out_page, double...` -- Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h...

## include/perf_trace.h
Imported by: `src/freedom.c`, `src/perf_trace.c`, `tests/test_perf_trace.c`
- `pt_init` (function) `include/perf_trace.h:46` `void pt_init(pt_trace *t);` -- #define PT_MAX_SAMPLES 256 typedef struct pt_stage_stats { uint64_t samples[PT_MAX_SAMPLES]; size_t   fill;   /*...
- `pt_elapsed_us` (function) `include/perf_trace.h:50` `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us);` -- end_us - start_us with an anti-underflow guard: end < start yields 0 * instead of wrapping to a huge uint64_t.
- `pt_record` (function) `include/perf_trace.h:54` `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us);` -- Record one sample (microseconds) for the given stage.
- `pt_count` (function) `include/perf_trace.h:57` `size_t pt_count(const pt_trace *t, pt_stage stage);` -- Record one sample (microseconds) for the given stage.
- `pt_last_us` (function) `include/perf_trace.h:60` `uint64_t pt_last_us(const pt_trace *t, pt_stage stage);` -- Record one sample (microseconds) for the given stage.
- `pt_min_us` (function) `include/perf_trace.h:63` `uint64_t pt_min_us(const pt_trace *t, pt_stage stage);` -- Record one sample (microseconds) for the given stage.
- `pt_max_us` (function) `include/perf_trace.h:64` `uint64_t pt_max_us(const pt_trace *t, pt_stage stage);`
- `pt_median_us` (function) `include/perf_trace.h:65` `uint64_t pt_median_us(const pt_trace *t, pt_stage stage);`
- `pt_stage_name` (function) `include/perf_trace.h:69` `const char *pt_stage_name(pt_stage stage);` -- Short lowercase stage name ("fetch".."shape"); "unknown" if out of range. * Static string, never NULL.
- `pt_format` (function) `include/perf_trace.h:76` `size_t pt_format(const pt_trace *t, char *buf, size_t cap);` -- Deterministic dump, one line per stage with count > 0, enum order: stage=<name> n=<total> last_us=<n> min_us=<n>...

## include/pq_seal.h
Depends on: `include/local_store.h`
Imported by: `src/http_cache.c`, `src/pq_seal.c`, `tests/test_pq_seal.c`
- `pqs_free` (function) `include/pq_seal.h:41` `void pqs_free(pqs_keys *k);`
- `pqs_buf_free` (function) `include/pq_seal.h:51` `void pqs_buf_free(uint8_t *buf, size_t len);` -- DER of the PRIVATE key: secret, the caller seals it before it touches disk. *der is owned * (release with...

## include/prefetch.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/prefetch.c`, `tests/test_prefetch.c`
- `pf_scan` (function) `include/prefetch.h:62` `int pf_scan(const char *html, size_t len, pf_list *out);` -- Lookahead scan of hostile HTML.
- `pf_list_free` (function) `include/prefetch.h:63` `void pf_list_free(pf_list *l);`
- `specifiers` (function) `include/prefetch.h:110` `* specifiers (each < PF_SPEC_MAX) into out[k] and returns how many. Pure. */ size_t pf_scan_imports(const char *js...`
- `pf_find_importmap` (function) `include/prefetch.h:115` `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n);` -- Span of the first <script type=importmap> body in html (pure, bounded): 1 with * [*start, *start + *n) set, or 0...
- `started` (function) `include/prefetch.h:121` `* to fetch or no thread started (the caller fetches serially). */ int pf_pool_start_page(pf_pool *p, const char...`
- `pf_pool_add` (function) `include/prefetch.h:127` `int pf_pool_add(pf_pool *p, const char *url);` -- Queues one more URL on a started pool (deduplicated, bounded by PF_MAX_JOBS). * Returns 1 when added, 0 when already...
- `fetch` (function) `include/prefetch.h:132` `* claiming jobs and running fetch(ctx, "GET", url, ...). Returns 0 on success or * -1 when no thread could start...`
- `pf_pool_take` (function) `include/prefetch.h:145` `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status, char **body, size_t *len, char **ctype);` -- Cache-first take.
- `pf_pool_finish` (function) `include/prefetch.h:151` `void pf_pool_finish(pf_pool *p);` -- Joins the worker threads and frees every unconsumed result.
- `pool` (function) `include/prefetch.h:155` `* whose URL is pooled is served from the pool (a failed prefetch propagates the * failure -- never refetched);`
- `pf_pooled_fetch` (function) `include/prefetch.h:165` `int pf_pooled_fetch(void *vctx, const char *method, const char *url, const char *body, size_t body_len, int...`

## include/prefs.h
Imported by: `gui/browser_ui.c`, `include/profile.h`, `include/ui.h`, `src/prefs.c`, `tests/test_prefs.c`, `tests/test_profile.c`
- `prefs_init` (function) `include/prefs.h:66` `void prefs_init(prefs_state *p);` -- Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `prefs_free` (function) `include/prefs.h:69` `void prefs_free(prefs_state *p);` -- Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `free` (function) `include/prefs.h:72` `* free(). */ prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len);`
- `prefs_bookmark_index` (function) `include/prefs.h:82` `int prefs_bookmark_index(const prefs_state *p, const char *url);` -- Parses text[0..len) over an out ALREADY initialised with prefs_init.
- `prefs_suggest` (function) `include/prefs.h:101` `int prefs_suggest(const prefs_state *p, const char *query, char *out, size_t row_len, int max_rows);` -- Omnibox autocomplete: up to max_rows distinct URLs matching query (case- insensitive) written to out (rows of...
- `anyway` (function) `include/prefs.h:106` `* page is rendered by the normal confined pipeline anyway (defence in depth). * *out is owned (free());`

## include/profile.h
Depends on: `include/local_store.h`, `include/prefs.h`
Imported by: `gui/browser_ui.c`, `src/profile.c`, `tests/test_profile.c`
- `absent` (function) `include/profile.h:53` `* the keyfile when absent (0600, atomic write);`
- `closed` (function) `include/profile.h:54` `* wrong size fails closed (PROFILE_ERR_KEY, never overwritten). Derives the * AEAD key (Argon2id, per-device salt)...`
- `profile_close` (function) `include/profile.h:67` `void profile_close(profile_ctx *ctx);` -- Loads and decrypts prefs.bin over an out ALREADY initialised (prefs_init).

## include/render_doc.h
Depends on: `include/page_view.h`, `include/render_policy.h`
Imported by: `gui/browser_ui.c`, `include/dom_debug.h`, `src/freedom.c`, `src/render_doc.c`, `tests/test_dom_debug.c`, `tests/test_render_doc.c`
- `list` (function) `include/render_doc.h:18` `* inert display list (page_view) and the presentation orchestrator (the GUI and * the --headless writer). It decides...`
- `RD_IMAGE` (function) `include/render_doc.h:59` `* RD_IMAGE (image src) and RD_INPUT (the owning form's action);`
- `form` (function) `include/render_doc.h:63` `* form (-1 = none);`
- `default` (function) `include/render_doc.h:150` `* default (layout is structure, not author styling, and leaks nothing to the * network) so the presentation layer...`
- `to` (function) `include/render_doc.h:250` `* belongs to (-1 = none);`
- `rdp_images_warning` (function) `include/render_doc.h:305` `* rdp_images_warning() is prepended so the user is always told. Each image * becomes an RD_IMAGE block whose...`
- `rd_free` (function) `include/render_doc.h:315` `void rd_free(rd_doc *d);` -- Builds the paint-ready document from an inert display list and the page's capabilities. view == NULL is treated as...
- `rd_count` (function) `include/render_doc.h:318` `size_t rd_count(const rd_doc *d);` -- images and caps.images is false, a single RD_NOTICE block carrying rdp_images_warning() is prepended so the user is...
- `rd_at` (function) `include/render_doc.h:319` `const rd_block *rd_at(const rd_doc *d, size_t i);`
- `rd_box_count` (function) `include/render_doc.h:323` `size_t rd_box_count(const rd_doc *d);` -- Box tree accessors (Step D). rd_box_count is the number of box definitions (0 when * caps.css is off); rd_box_at...
- `rd_box_at` (function) `include/render_doc.h:324` `const pv_box_def *rd_box_at(const rd_doc *d, size_t i);`
- `rd_cont_count` (function) `include/render_doc.h:328` `size_t rd_cont_count(const rd_doc *d);` -- Container table accessors. rd_cont_count is the number of containers; rd_cont_at * returns conts[i] (i == a run's...
- `rd_cont_at` (function) `include/render_doc.h:329` `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i);`
- `rd_kind_name` (function) `include/render_doc.h:333` `const char *rd_kind_name(rd_kind k);` -- Stable, short English name of a block kind for structured/agent output.
- `rd_block_tag` (function) `include/render_doc.h:341` `const char *rd_block_tag(const rd_block *b);` -- Canonical HTML tag name for a block, so the presentation layer can look up its user-agent box (box_style) without...
- `rd_block_heading_level` (function) `include/render_doc.h:348` `int rd_block_heading_level(const rd_block *b);` -- Effective heading level of a block, 0 when it is not heading content.
- `decision` (function) `include/render_doc.h:351` `* decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never * NULL. */ const char...`
- `IMG_FAIL_OK` (function) `include/render_doc.h:357` `* IMG_FAIL_OK (not a failure) or the reason is unknown. */ const char *rd_image_fail_label(img_fail_reason reason);`
- `rd_input_label` (function) `include/render_doc.h:362` `const char *rd_input_label(int input_type);` -- Stable, short English name of a form control type (a pv_input_type value), e.g. * "text" / "password" / "submit".
- `rd_input_invisible` (function) `include/render_doc.h:367` `int rd_input_invisible(int input_type);` -- Nonzero iff a control of this type has no face of its own and is therefore never laid out or painted: a hidden...

## include/render_policy.h
Imported by: `gui/browser_ui.c`, `include/render_doc.h`, `include/webcaps.h`, `src/freedom.c`, `src/render_policy.c`, `tests/test_dom_debug.c`, `tests/test_render_doc.c`, `tests/test_render_policy.c`
- `rdp_is_tracking_pixel` (function) `include/render_policy.h:53` `int rdp_is_tracking_pixel(int w, int h);` -- Tracking-pixel heuristic over an image's declared dimensions. w/h negative means "unknown".
- `size` (function) `include/render_policy.h:56` `* announced size (e.g. <img width height>);`
- `rdp_img_reason` (function) `include/render_policy.h:66` `const char *rdp_img_reason(rdp_img_decision d);` -- Stable, short, English reason string for structured/agent-friendly output. * Never NULL; an unknown enum value...
- `rdp_images_warning` (function) `include/render_policy.h:69` `const char *rdp_images_warning(void);` -- Stable, short, English reason string for structured/agent-friendly output. * Never NULL; an unknown enum value...

## include/renderer.h
Imported by: `src/renderer.c`, `tests/test_renderer.c`
- `rd_result_free` (function) `include/renderer.h:46` `void rd_result_free(rd_result *out);` -- Renders untrusted HTML out-of-process and returns an inert title + text. html == NULL or out == NULL => RD_ERR_NULL_ARG.

## include/request_policy.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/render_policy.c`, `src/request_policy.c`, `src/tab.c`, `tests/test_request_policy.c`
- `rp_host_of` (function) `include/request_policy.h:30` `int rp_host_of(const char *url, char *out, size_t out_size);` -- Lowercased host of an absolute URL into out.
- `rp_site_of` (function) `include/request_policy.h:34` `int rp_site_of(const char *host, char *out, size_t out_size);` -- Registrable domain ("site") of a host into out (simplified public-suffix * rule).
- `rp_same_site` (function) `include/request_policy.h:37` `int rp_same_site(const char *top_level_url, const char *request_url);` -- Registrable domain ("site") of a host into out (simplified public-suffix * rule).


Next: [API_p5.md](API_p5.md)
