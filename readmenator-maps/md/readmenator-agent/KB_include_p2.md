# Subsystem: include (page 2 of 4)
Previous: [KB_include.md](KB_include.md)

## include/css_select.h
- Doc: css_attr_match: Sub-selector for :not()/:is()/:where(): a simple compound with only...
- Layer: utility
- Language: h
- Symbols:
  - `css_attr_match` (struct, line 85)
  - `css_sub_sel` (struct, line 92)
  - `css_pseudo_match` (struct, line 109)
  - `css_compound` (struct, line 119)
  - `css_sel` (struct, line 136)
  - `name` (type_alias, line 85) `typedef struct css_attr_match { char name[CSS_TOK_MAX];`
  - `tag` (type_alias, line 91) `typedef struct css_sub_sel { char tag[CSS_TOK_MAX];`
  - `kind` (type_alias, line 109) `typedef struct css_pseudo_match { int kind;`
  - `tag` (type_alias, line 119) `typedef struct css_compound { char tag[CSS_TOK_MAX];`
  - `parts` (type_alias, line 136) `typedef struct css_sel { css_compound parts[CSS_MAX_COMPOUNDS];`
  - `csel_lower_ch` (function, line 195) `static inline char csel_lower_ch(char c)`
  - `csel_ci_eq` (function, line 199) `static inline int csel_ci_eq(const char *a, const char *b)`
  - `csel_span_eq` (function, line 208) `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)`
  - `csel_substr` (function, line 219) `static inline int csel_substr(const char *hay, const char *needle, int ci)`
  - `csel_ident_ch` (function, line 227) `static inline int csel_ident_ch(char c)`
  - `csel_parse` (function, line 150) `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel);`
  - `csel_matches` (function, line 159) `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id, int allow_pseudo_el, int...`
  - `identifier` (function, line 163) `* A selector identifier (tag, .class, #id) is read with CSS escapes decoded * (`.md\:flex` is the class "md:flex")...`
  - `csel_emit_utf8` (function, line 175) `size_t csel_emit_utf8(unsigned int cp, char *out);`
  - `csel_unescape` (function, line 177) `void csel_unescape(char *dst, size_t cap, const char *src, size_t n);`
  - `csel_escape_len` (function, line 179) `size_t csel_escape_len(const char *s, size_t i, size_t b);`
  - `csel_ident_fold` (function, line 181) `void csel_ident_fold(const char *src, size_t len, char *dst);`
  - `csel_ident_eq` (function, line 183) `int csel_ident_eq(const char *stored, const char *tok, size_t tlen);`
  - `csel_read_ident` (function, line 186) `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower);`
  - `csel_decl_end` (function, line 191) `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace);`
  - `FREEDOM_CSS_SELECT_H` (macro, line 2) `#define FREEDOM_CSS_SELECT_H`
  - `CSS_TOK_MAX` (macro, line 27) `#define CSS_TOK_MAX`
  - `CSS_MAX_CLASSES_PER_SEL` (macro, line 28) `#define CSS_MAX_CLASSES_PER_SEL`
  - `CSS_MAX_SUB_SELS` (macro, line 80) `#define CSS_MAX_SUB_SELS`
  - `CSS_SUB_MAX_ATTRS` (macro, line 81) `#define CSS_SUB_MAX_ATTRS`
  - `CSS_SUB_MAX_PSEUDOS` (macro, line 82) `#define CSS_SUB_MAX_PSEUDOS`
  - `CSEL_FOLD_PREFIX` (macro, line 170) `#define CSEL_FOLD_PREFIX`
  - `CSEL_FOLD_MARK` (macro, line 171) `#define CSEL_FOLD_MARK`
  - `CSEL_IDENT_SCRATCH` (macro, line 172) `#define CSEL_IDENT_SCRATCH`
- Depends on: `include/css.h`
- Imported by: `fuzz/fuzz_css.c`, `include/css_chain.h`, `include/css_decl.h`, `src/css.c`, `src/css_atrule.c`, `src/css_box.c`, `src/css_chain.c`, `src/css_gradient.c`, `src/css_select.c`, `src/css_text.c`, `src/css_values.c`, `src/css_vars.c`, `src/dom.c`, `tests/test_css.c`

## include/css_text.h
- Layer: utility
- Language: h
- Symbols:
  - `ct_interp_fontfamily` (function, line 10) `int ct_interp_fontfamily(const char *v);`
  - `ct_interp_texttransform` (function, line 11) `int ct_interp_texttransform(const char *v);`
  - `ct_interp_opacity` (function, line 12) `int ct_interp_opacity(const char *v);`
  - `ct_interp_valign` (function, line 13) `int ct_interp_valign(const char *v);`
  - `ct_expand_valign` (function, line 14) `int ct_expand_valign(const char *val, css_decl *dst, int cap);`
  - `ct_interp_transition_property` (function, line 15) `int ct_interp_transition_property(const char *v);`
  - `ct_interp_whitespace` (function, line 16) `int ct_interp_whitespace(const char *v);`
  - `ct_interp_tabsize` (function, line 17) `int ct_interp_tabsize(const char *v);`
  - `ct_interp_textdeco_style` (function, line 18) `int ct_interp_textdeco_style(const char *v);`
  - `ct_interp_textdeco_thickness` (function, line 19) `int ct_interp_textdeco_thickness(const char *v);`
  - `ct_interp_aspect_ratio` (function, line 20) `int ct_interp_aspect_ratio(const char *v, int *num, int *den);`
  - `ct_interp_direction` (function, line 21) `int ct_interp_direction(const char *v);`
  - `ct_interp_liststyle` (function, line 22) `int ct_interp_liststyle(const char *v);`
  - `ct_interp_spacing` (function, line 23) `int ct_interp_spacing(const char *v, int *out);`
  - `ct_emit_spacing` (function, line 24) `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val);`
  - `ct_expand_shadow` (function, line 25) `int ct_expand_shadow(const char *val, css_decl *dst, int cap);`
  - `FREEDOM_CSS_TEXT_H` (macro, line 2) `#define FREEDOM_CSS_TEXT_H`
- Depends on: `include/css_decl.h`
- Imported by: `src/css.c`, `src/css_text.c`, `tests/test_css_text.c`

## include/css_values.h
- Doc: Single owner of CSS value interpretation for colors and backgrounds.
- Layer: utility
- Language: h
- Symbols:
  - `cv_parse_color` (function, line 12) `int cv_parse_color(const char *v);`
  - `cv_interp_color` (function, line 13) `int cv_interp_color(const char *v);`
  - `cv_color_ok` (function, line 14) `int cv_color_ok(int c);`
  - `cv_bg_alpha_of` (function, line 15) `int cv_bg_alpha_of(const char *v);`
  - `cv_interp_bg` (function, line 16) `int cv_interp_bg(const char *v);`
  - `FREEDOM_CSS_VALUES_H` (macro, line 2) `#define FREEDOM_CSS_VALUES_H`
- Imported by: `src/css.c`, `src/css_box.c`, `src/css_gradient.c`, `src/css_text.c`, `src/css_values.c`, `tests/test_css_values.c`

## include/css_vars.h
- Doc: cvr_table: Zero-initialise ({0}) before first use.
- Layer: utility
- Language: h
- Symbols:
  - `cvr_ent` (struct, line 28)
  - `cvr_table` (struct, line 35)
  - `cvr_chain` (struct, line 46)
  - `cvr_scope` (struct, line 54)
  - `name` (function, line 62) `* name (last declaration wins). Returns 1 when stored, 0 when dropped: a name that * is not "--" + at least one...`
  - `cvr_get` (function, line 69) `const char *cvr_get(const cvr_table *t, const char *name, size_t nlen);`
  - `cvr_count` (function, line 71) `size_t cvr_count(const cvr_table *t);`
  - `cvr_reset` (function, line 75) `void cvr_reset(cvr_table *t);`
  - `cvr_free` (function, line 78) `void cvr_free(cvr_table *t);`
  - `cvr_collect_decls` (function, line 83) `void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b);`
  - `declaration` (function, line 91) `* then drops the whole declaration (CSS Variables 1: invalid at computed time). */ int cvr_resolve(const char *val...`
  - `cvr_lookup` (function, line 96) `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen);`
  - `FREEDOM_CSS_VARS_H` (macro, line 2) `#define FREEDOM_CSS_VARS_H`
  - `CVR_NAME_MAX` (macro, line 19) `#define CVR_NAME_MAX`
  - `CVR_VALUE_MAX` (macro, line 20) `#define CVR_VALUE_MAX`
  - `CVR_MAX_ENTRIES` (macro, line 21) `#define CVR_MAX_ENTRIES`
  - `CVR_MAX_DEPTH` (macro, line 22) `#define CVR_MAX_DEPTH`
  - `CVR_MAX_LOOKUPS` (macro, line 26) `#define CVR_MAX_LOOKUPS`
  - `CVR_CHAIN_MAX` (macro, line 45) `#define CVR_CHAIN_MAX`
- Imported by: `src/css.c`, `src/css_vars.c`, `src/page_view.c`, `tests/test_css.c`, `tests/test_css_vars.c`

## include/data_url.h
- Doc: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/...
- Layer: data_access
- Language: h
- Symbols:
  - `du_status` (enum, line 27)
  - `allocation` (function, line 21) `* * du_base64_payload does no allocation (it only slices the caller's url string);`
  - `du_is_data_url` (function, line 46) `int du_is_data_url(const char *url);`
  - `closed` (function, line 59) `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/out/out_len == NULL (with b64_len !=...`
  - `FREEDOM_DATA_URL_H` (macro, line 2) `#define FREEDOM_DATA_URL_H`
  - `DU_MAX_ENCODED_LEN` (macro, line 43) `#define DU_MAX_ENCODED_LEN`
- Imported by: `fuzz/fuzz_data_url.c`, `gui/browser_ui.c`, `src/data_url.c`, `src/render_doc.c`, `src/render_policy.c`, `src/tab.c`, `src/webfont.c`, `src/webfont_load.c`, `tests/test_data_url.c`

## include/disk_store.h
- Doc: ds_free: Reads and decrypts path.
- Layer: data_access
- Language: h
- Symbols:
  - `ds_status` (enum, line 25)
  - `ds_free` (function, line 47) `void ds_free(uint8_t *buf, size_t len);`
  - `FREEDOM_DISK_STORE_H` (macro, line 2) `#define FREEDOM_DISK_STORE_H`
- Depends on: `include/local_store.h`
- Imported by: `src/disk_store.c`, `src/profile.c`, `tests/test_disk_store.c`

## include/dom.h
- Doc: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: *...
- Layer: utility
- Language: h
- Symbols:
  - `dom_status` (enum, line 26)
  - `dom_place` (enum, line 182)
  - `dom_node_id` (type_alias, line 34) `typedef uint32_t dom_node_id;`
  - `dom_index` (type_alias, line 40) `typedef struct dom_index dom_index;`
  - `dom_free` (function, line 48) `void dom_free(dom_index *idx);`
  - `dom_node_count` (function, line 51) `size_t dom_node_count(const dom_index *idx);`
  - `count` (function, line 59) `* match count (which may exceed cap, so the caller can size a buffer). */ size_t dom_get_by_tag(const dom_index...`
  - `dom_get_by_class` (function, line 62) `size_t dom_get_by_class(const dom_index *idx, const char *cls, dom_node_id *out, size_t cap);`
  - `dom_matches` (function, line 91) `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector);`
  - `dom_document_position` (function, line 101) `size_t dom_document_position(const dom_index *idx, dom_node_id node);`
  - `dom_precedes` (function, line 104) `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);`
  - `dom_tag_name` (function, line 118) `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);`
  - `dom_get_attribute` (function, line 121) `const char *dom_get_attribute(const dom_index *idx, dom_node_id node, const char *name, size_t *len);`
  - `dom_attribute_names` (function, line 128) `size_t dom_attribute_names(const dom_index *idx, dom_node_id node, const char **names, size_t *lens, size_t cap);`
  - `dom_text_content` (function, line 133) `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len);`
  - `dom_document_title` (function, line 136) `const char *dom_document_title(const dom_index *idx, size_t *len);`
  - `cycle` (function, line 164) `* Rejects a cycle (child being an ancestor of parent). Invalid handle / self / cycle * => DOM_ERR_NULL_ARG. */...`
  - `parent` (function, line 191) `* child of parent (for the *_REF places) or an invalid handle => DOM_ERR_NULL_ARG. */ dom_status...`
  - `dom_node_kind` (function, line 207) `int dom_node_kind(const dom_index *idx, dom_node_id node);`
  - `index` (function, line 223) `* stays valid in the index (not freed). Invalid handle / not-a-child => DOM_ERR_NULL_ARG. */ dom_status...`
  - `length` (function, line 248) `* length (no children => an owned empty string). Uses a chain of fixed-size * blocks internally so there is no hard...`
  - `FREEDOM_DOM_H` (macro, line 2) `#define FREEDOM_DOM_H`
  - `DOM_NODE_NONE` (macro, line 37) `#define DOM_NODE_NONE`
  - `DOM_KIND_NONE` (macro, line 198) `#define DOM_KIND_NONE`
  - `DOM_KIND_ELEMENT` (macro, line 199) `#define DOM_KIND_ELEMENT`
  - `DOM_KIND_TEXT` (macro, line 200) `#define DOM_KIND_TEXT`
  - `DOM_KIND_COMMENT` (macro, line 201) `#define DOM_KIND_COMMENT`
  - `DOM_MAX_HANDLES` (macro, line 204) `#define DOM_MAX_HANDLES`
- Depends on: `include/html_parse.h`
- Imported by: `fuzz/fuzz_dom.c`, `fuzz/fuzz_js_dom.c`, `include/js_dom.h`, `include/js_geom.h`, `include/page_view.h`, `src/dom.c`, `src/html_parse.c`, `src/js_dom.c`, `src/js_dom_internal.h`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/page_view.c`, `src/tab.c`, `tests/test_dom.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_page_view.c`

## include/dom_debug.h
- Doc: dd_format: Formats doc into out[0..cap) as a NUL-terminated, line-oriented dump (see the spec...
- Layer: utility
- Language: h
- Symbols:
  - `dd_format` (function, line 36) `size_t dd_format(const rd_doc *doc, char *out, size_t cap);`
  - `dd_format_css` (function, line 41) `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap);`
  - `FREEDOM_DOM_DEBUG_H` (macro, line 2) `#define FREEDOM_DOM_DEBUG_H`
  - `DD_FIELD_MAX` (macro, line 28) `#define DD_FIELD_MAX`
- Depends on: `include/render_doc.h`
- Imported by: `fuzz/fuzz_dom_debug.c`, `src/dom_debug.c`, `src/freedom.c`, `tests/test_dom_debug.c`

## include/download.h
- Doc: dl_should_download: 1 if the response should be saved (attachment, or a non-renderable media...
- Layer: utility
- Language: h
- Symbols:
  - `dl_status` (enum, line 33)
  - `dl_should_download` (function, line 43) `int dl_should_download(const char *content_type, const char *content_disposition);`
  - `literal` (function, line 47) `* a static string literal (never freed). */ const char *dl_ext_for_type(const char *content_type);`
  - `DL_ERR_OVERFLOW` (function, line 56) `* DL_ERR_OVERFLOW (out left empty). url/content_disposition NULL => absent. */ dl_status dl_pick_name(const char...`
  - `basename` (function, line 61) `* sanitized basename (a name still containing '/' is rejected => DL_ERR_OVERFLOW, * so the path can never escape...`
  - `FREEDOM_DOWNLOAD_H` (macro, line 2) `#define FREEDOM_DOWNLOAD_H`
  - `DL_NAME_MAX` (macro, line 29) `#define DL_NAME_MAX`
  - `DL_FALLBACK_NAME` (macro, line 30) `#define DL_FALLBACK_NAME`
  - `DL_MAX_BYTES` (macro, line 31) `#define DL_MAX_BYTES`
- Imported by: `fuzz/fuzz_download.c`, `gui/browser_ui.c`, `src/download.c`, `tests/test_download.c`

## include/flex_layout.h
- Doc: fx_item: Upper bound on items per flex line / grid columns.
- Layer: presentation
- Language: h
- Symbols:
  - `fx_item` (struct, line 40)
  - `fx_result` (struct, line 48)
  - `fx_area_map` (struct, line 123)
  - `fx_float_rect` (struct, line 193)
  - `fx_justify` (enum, line 30)
  - `fx_status` (enum, line 53)
  - `basis` (type_alias, line 40) `typedef struct fx_item { double basis;`
  - `pos` (type_alias, line 48) `typedef struct fx_result { double pos;`
  - `cols` (type_alias, line 123) `typedef struct fx_area_map { int rows, cols;`
  - `bottom` (type_alias, line 193) `typedef struct fx_float_rect { double top, bottom;`
  - `size` (function, line 60) `* content size (px);`
  - `out` (function, line 62) `* fx_result to out (caller-owned). n == 0 is a no-op (out may be NULL). */ fx_status fx_flex_line(const fx_item...`
  - `fx_grid_cell` (function, line 74) `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col);`
  - `fx_autofill_count` (function, line 108) `size_t fx_autofill_count(double avail, double gap, double minw);`
  - `fx_grid_area_hash` (function, line 132) `unsigned fx_grid_area_hash(const char *name);`
  - `offset` (function, line 150) `* offset (from the content start, clamped to >= 0) to out_x[n]. The band does NOT wrap * (v1): an item that would...`
  - `required` (function, line 163) `* out_row is required (NULL with n > 0 yields FX_ERR_NULL_ARG);`
  - `widths` (function, line 173) `* the OUTER widths (width + ml + mr, clamped >= 0, so a negative margin narrows * the slot and a positive one widens...`
  - `FX_ERR_NULL_ARG` (function, line 207) `* Returns FX_ERR_NULL_ARG (a required pointer NULL with n > 0), FX_ERR_RANGE * (negative h/avail, or n > FX_MAX_ITEMS);`
  - `space` (function, line 213) `* line order: positive free space (avail - sizes - gaps) is split equally among every * auto margin...`
  - `fx_auto_min_size` (function, line 242) `double fx_auto_min_size(double min_content, double basis, double author_min, int scroll_container);`
  - `fx_justify_name` (function, line 298) `const char *fx_justify_name(fx_justify j);`
  - `height` (function, line 304) `* used height (h_out);`
  - `win` (function, line 321) `* margins win (both = centre, left only = end);`
  - `fx_cross_offset` (function, line 323) `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r);`
  - `FREEDOM_FLEX_LAYOUT_H` (macro, line 2) `#define FREEDOM_FLEX_LAYOUT_H`
  - `FX_MAX_ITEMS` (macro, line 28) `#define FX_MAX_ITEMS`
  - `FX_AREA_MAX_ROWS` (macro, line 115) `#define FX_AREA_MAX_ROWS`
  - `FX_AREA_MAX_COLS` (macro, line 116) `#define FX_AREA_MAX_COLS`
  - `FX_AREA_MAX_CELLS` (macro, line 117) `#define FX_AREA_MAX_CELLS`
  - `FX_AREA_NAME_MAX` (macro, line 118) `#define FX_AREA_NAME_MAX`
  - `FX_FLOAT_MIN_LINE` (macro, line 187) `#define FX_FLOAT_MIN_LINE`
  - `FX_MAX_COLUMNS` (macro, line 247) `#define FX_MAX_COLUMNS`
  - `FX_MAUTO_TOP` (macro, line 314) `#define FX_MAUTO_TOP`
  - `FX_MAUTO_BOTTOM` (macro, line 315) `#define FX_MAUTO_BOTTOM`
- Imported by: `include/box_tree.h`, `src/css.c`, `src/dom_debug.c`, `src/flex_layout.c`, `src/page_view.c`, `tests/test_dom_debug.c`, `tests/test_flex_layout.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`

## include/form.h
- Doc: fm_field: One named control. value == NULL is treated as the empty value; name == NULL is *...
- Layer: utility
- Language: h
- Symbols:
  - `fm_field` (struct, line 37)
  - `fm_plan` (struct, line 52)
  - `fm_method` (enum, line 33)
  - `fm_kind` (enum, line 39)
  - `fm_block_reason` (enum, line 45)
  - `fm_status` (enum, line 61)
  - `kind` (type_alias, line 51) `typedef struct fm_plan { fm_kind kind;`
  - `FM_CONTENT_TYPE_URLENCODED` (variable, line 68) `extern const char FM_CONTENT_TYPE_URLENCODED[];`
  - `FREEDOM_FORM_H` (macro, line 2) `#define FREEDOM_FORM_H`
  - `FM_URL_MAX` (macro, line 29) `#define FM_URL_MAX`
  - `FM_BODY_MAX` (macro, line 30) `#define FM_BODY_MAX`
  - `FM_MAX_FIELDS` (macro, line 31) `#define FM_MAX_FIELDS`
- Depends on: `include/url.h`
- Imported by: `gui/browser_ui.c`, `src/form.c`, `tests/test_form.c`

## include/frame_clock.h
- Doc: active: frame_clock (fc_) — pure animation frame scheduler.
- Layer: utility
- Language: h
- Symbols:
  - `fc_clock` (struct, line 15)
  - `active` (type_alias, line 14) `typedef struct fc_clock { int active;`
  - `fc_init` (function, line 20) `void fc_init(fc_clock *c);`
  - `fc_set_active` (function, line 21) `void fc_set_active(fc_clock *c, int active);`
  - `fc_needs_tick` (function, line 22) `int fc_needs_tick(const fc_clock *c);`
  - `fc_interval_ms` (function, line 23) `int fc_interval_ms(const fc_clock *c);`
  - `FREEDOM_FRAME_CLOCK_H` (macro, line 2) `#define FREEDOM_FRAME_CLOCK_H`
- Imported by: `gui/browser_ui.c`, `src/frame_clock.c`, `tests/test_frame_clock.c`

## include/freebug.h
- Doc: fb_entry: One captured console message. text and file are owned by the buffer (NUL-terminated)....
- Layer: utility
- Language: h
- Symbols:
  - `fb_entry` (struct, line 36)
  - `fb_buffer` (struct, line 46)
  - `fb_level` (enum, line 24)
  - `level` (type_alias, line 36) `typedef struct fb_entry { int level;`
  - `fb_buffer_init` (function, line 65) `void fb_buffer_init(fb_buffer *b);`
  - `truncated` (function, line 69) `* A message longer than FB_MAX_ENTRY_BYTES is stored truncated (not dropped). A * dropped push raises b->overflow...`
  - `copied` (function, line 75) `* copied (truncated to FB_MAX_FILE_BYTES);`
  - `fb_buffer_push_loc` (function, line 78) `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len, const char *file, int line, int col);`
  - `fb_buffer_reset` (function, line 83) `void fb_buffer_reset(fb_buffer *b);`
  - `fb_buffer_free` (function, line 86) `void fb_buffer_free(fb_buffer *b);`
  - `fb_buffer_count` (function, line 89) `size_t fb_buffer_count(const fb_buffer *b);`
  - `fb_buffer_at` (function, line 92) `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i);`
  - `fb_level_name` (function, line 96) `const char *fb_level_name(int level);`
  - `FREEDOM_FREEBUG_H` (macro, line 2) `#define FREEDOM_FREEBUG_H`
  - `FB_MAX_ENTRIES` (macro, line 56) `#define FB_MAX_ENTRIES`
  - `FB_MAX_ENTRY_BYTES` (macro, line 57) `#define FB_MAX_ENTRY_BYTES`
  - `FB_MAX_TOTAL_BYTES` (macro, line 58) `#define FB_MAX_TOTAL_BYTES`
  - `FB_MAX_FILE_BYTES` (macro, line 62) `#define FB_MAX_FILE_BYTES`
- Imported by: `fuzz/fuzz_freebug.c`, `gui/browser_ui.c`, `include/js_dom.h`, `include/tab.h`, `src/freebug.c`, `src/freedom.c`, `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/tab.c`, `tests/test_freebug.c`

## include/freedom_config.h
- Layer: infrastructure
- Language: h
- Symbols:
  - `FREEDOM_CONFIG_H` (macro, line 14) `#define FREEDOM_CONFIG_H`
  - `FC_PNG_PAGE_W` (macro, line 20) `#define FC_PNG_PAGE_W`
  - `FC_HEADLESS_VIEW_H` (macro, line 24) `#define FC_HEADLESS_VIEW_H`
  - `FC_TRUSTED_JS_BUDGET_MS` (macro, line 29) `#define FC_TRUSTED_JS_BUDGET_MS`
  - `FC_PNG_MARGIN` (macro, line 33) `#define FC_PNG_MARGIN`
  - `FC_PNG_MAX_H` (macro, line 38) `#define FC_PNG_MAX_H`
  - `FC_FLEX_MEASURE_W` (macro, line 44) `#define FC_FLEX_MEASURE_W`
  - `FC_FLEX_MIN_MEASURE_W` (macro, line 50) `#define FC_FLEX_MIN_MEASURE_W`
  - `FC_FONT_CHAIN_MAX` (macro, line 55) `#define FC_FONT_CHAIN_MAX`
  - `FC_MAX_BOXES` (macro, line 60) `#define FC_MAX_BOXES`
  - `FC_FONT_FALLBACK_PX` (macro, line 65) `#define FC_FONT_FALLBACK_PX`
  - `FC_UI_FONT_SIZE` (macro, line 69) `#define FC_UI_FONT_SIZE`
  - `FC_MAX_AUTHOR_CSS_BYTES` (macro, line 77) `#define FC_MAX_AUTHOR_CSS_BYTES`
- Imported by: `fuzz/fuzz_page_view.c`, `gui/browser_ui_internal.h`, `gui/svg_paint.c`, `gui/ui_render.c`, `src/page_view.c`, `src/tab.c`

## include/hls.h
- Doc: hls_segment: or variant info.
- Layer: utility
- Language: h
- Symbols:
  - `hls_segment` (struct, line 29)
  - `hls_variant` (struct, line 36)
  - `hls_playlist` (struct, line 45)
  - `hls_status` (enum, line 21)
  - `hls_select_variant` (function, line 65) `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h);`
  - `resolved` (function, line 68) `* Writes the absolute URL into resolved (bounded by resolved_sz). Returns the * written length, or 0 on failure. */...`
  - `hls_playlist_free` (function, line 74) `void hls_playlist_free(hls_playlist *pl);`
  - `FREEDOM_HLS_H` (macro, line 2) `#define FREEDOM_HLS_H`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/hls.c`, `tests/test_hls.c`

## include/hostblock.h
- Doc: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted...
- Layer: utility
- Language: h
- Symbols:
  - `hb_list` (enum, line 32)
  - `hb_decision` (enum, line 37)
  - `hb_status` (enum, line 42)
  - `hb_set` (type_alias, line 29) `typedef struct hb_set hb_set;`
  - `hb_new` (function, line 49) `hb_set *hb_new(void);`
  - `hb_free` (function, line 52) `void hb_free(hb_set *s);`
  - `walked` (function, line 65) `* walked (the host, then without its first label, ...): any suffix on the allowlist * => HB_ALLOW (allow wins...`
  - `hb_is_allowlisted` (function, line 75) `int hb_is_allowlisted(const hb_set *s, const char *host);`
  - `hb_count` (function, line 79) `size_t hb_count(const hb_set *s, hb_list list);`
  - `FREEDOM_HOSTBLOCK_H` (macro, line 2) `#define FREEDOM_HOSTBLOCK_H`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/hostblock.c`, `tests/test_hostblock.c`

## include/hostedit.h
- Doc: he_text_has_host: Returns 1 if text (the body of a hosts-format file) already lists host as a...
- Layer: utility
- Language: h
- Symbols:
  - `he_status` (enum, line 24)
  - `he_text_has_host` (function, line 46) `int he_text_has_host(const char *text, const char *host);`
  - `he_suggest` (function, line 55) `int he_suggest(const char *text, const char *query, char results[][HE_MAX_HOST + 1], int max);`
  - `FREEDOM_HOSTEDIT_H` (macro, line 2) `#define FREEDOM_HOSTEDIT_H`
  - `HE_MAX_HOST` (macro, line 32) `#define HE_MAX_HOST`
- Imported by: `gui/browser_ui.c`, `src/hostedit.c`, `tests/test_hostedit.c`

## include/html_parse.h
- Doc: hp_script: One executable <script>.
- Layer: utility
- Language: h
- Symbols:
  - `hp_config` (struct, line 32)
  - `hp_script` (struct, line 76)
  - `hp_status` (enum, line 22)
  - `max_bytes` (type_alias, line 31) `typedef struct hp_config { size_t max_bytes;`
  - `hp_document` (type_alias, line 39) `typedef struct hp_document hp_document;`
  - `dropped` (function, line 47) `* dropped (not executed). */ #define HP_MAX_SCRIPTS ((size_t)4096) /* Returns a configuration with the secure...`
  - `cfg` (function, line 57) `* policy in cfg (cfg == NULL => secure defaults). No script is ever executed. * html == NULL or out == NULL =>...`
  - `hp_element_count` (function, line 63) `size_t hp_element_count(const hp_document *doc);`
  - `hp_script_count` (function, line 64) `size_t hp_script_count(const hp_document *doc);`
  - `hp_event_handler_count` (function, line 65) `size_t hp_event_handler_count(const hp_document *doc);`
  - `hp_extract_text` (function, line 69) `char *hp_extract_text(const hp_document *doc, size_t *out_len);`
  - `hp_get_title` (function, line 70) `char *hp_get_title(const hp_document *doc, size_t *out_len);`
  - `src` (function, line 90) `* carry their raw src (a <script src> with an inline body lists ONLY the src -- * browser rule: when src is present...`
  - `modules` (function, line 94) `* ES modules (import/export cannot run as a classic script), and template blocks * (text/x-jquery-tmpl, text/html...`
  - `hp_free_scripts` (function, line 111) `void hp_free_scripts(hp_script *scripts, size_t count);`
  - `hp_extract_stylesheet_hrefs` (function, line 127) `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count);`
  - `hp_free_stylesheet_hrefs` (function, line 130) `void hp_free_stylesheet_hrefs(char **hrefs, size_t count);`
  - `hp_free` (function, line 133) `void hp_free(char *buf);`
  - `hp_document_free` (function, line 136) `void hp_document_free(hp_document *doc);`
  - `hp_document_root` (function, line 142) `const void *hp_document_root(const hp_document *doc);`
  - `FREEDOM_HTML_PARSE_H` (macro, line 2) `#define FREEDOM_HTML_PARSE_H`
  - `HP_DEFAULT_MAX_BYTES` (macro, line 41) `#define HP_DEFAULT_MAX_BYTES`
  - `HP_MAX_SCRIPTS` (macro, line 48) `#define HP_MAX_SCRIPTS`
  - `HP_MAX_STYLESHEETS` (macro, line 115) `#define HP_MAX_STYLESHEETS`
- Imported by: `fuzz/fuzz_dom.c`, `fuzz/fuzz_dom_debug.c`, `fuzz/fuzz_html_parse.c`, `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_page_view.c`, `gui/freedom_view.c`, `include/dom.h`, `include/page_view.h`, `src/dom.c`, `src/freedom.c`, `src/html_parse.c`, `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/page_view.c`, `src/renderer.c`, `src/tab.c`, `tests/test_dom.c`, `tests/test_html_parse.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_page_view.c`

## include/image_decode.h
- Doc: img_pixels: A decoded bitmap that owns its pixel buffer.
- Layer: utility
- Language: h
- Symbols:
  - `img_pixels` (struct, line 56)
  - `img_format` (enum, line 33)
  - `img_status` (enum, line 41)
  - `width` (type_alias, line 56) `typedef struct img_pixels { uint32_t width;`
  - `guards` (function, line 25) `* guards (in-memory source only, longjmp error manager so a bad stream never * calls exit(), dimension caps before...`
  - `img_dimensions_ok` (function, line 78) `int img_dimensions_ok(uint32_t w, uint32_t h);`
  - `inputs` (function, line 81) `* Degenerate inputs (<= 0) yield (0,0). Pure. */ void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h...`
  - `decode` (function, line 92) `* the declared dimensions BEFORE the full decode (anti-bomb), decodes to RGB and * expands to BGRA. Rejects non-JPEG...`
  - `img_pixels_free` (function, line 121) `void img_pixels_free(img_pixels *p);`
  - `img_format_name` (function, line 124) `const char *img_format_name(img_format f);`
  - `FREEDOM_IMAGE_DECODE_H` (macro, line 2) `#define FREEDOM_IMAGE_DECODE_H`
  - `IMG_MAX_DIM` (macro, line 65) `#define IMG_MAX_DIM`
  - `IMG_MAX_PIXELS` (macro, line 66) `#define IMG_MAX_PIXELS`
- Imported by: `fuzz/fuzz_image_decode.c`, `gui/browser_ui.c`, `src/image_decode.c`, `src/tab.c`, `tests/test_freedom.c`, `tests/test_image_decode.c`

## include/import_map.h
- Doc: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- Layer: utility
- Language: h
- Symbols:
  - `im_map` (type_alias, line 23) `typedef struct im_map im_map;`
  - `algorithm` (function, line 13) `* resolution algorithm (scopes, exact and prefix matches). URL resolution is the * caller's (the same resolver the...`
  - `map` (function, line 28) `* map (fail closed = no mapping). NULL only on OOM. */ im_map *im_parse(const char *json, size_t len, const char...`
  - `im_resolve` (function, line 33) `int im_resolve(const im_map *m, const char *base, const char *specifier, im_url_fn resolve, void *ctx, char *out...`
  - `im_count` (function, line 37) `size_t im_count(const im_map *m);`
  - `im_free` (function, line 40) `void im_free(im_map *m);`
  - `FREEDOM_IMPORT_MAP_H` (macro, line 2) `#define FREEDOM_IMPORT_MAP_H`
  - `IM_MAX_TEXT` (macro, line 17) `#define IM_MAX_TEXT`
  - `IM_MAX_ENTRIES` (macro, line 18) `#define IM_MAX_ENTRIES`
  - `IM_MAX_SCOPES` (macro, line 19) `#define IM_MAX_SCOPES`
- Imported by: `fuzz/fuzz_import_map.c`, `src/import_map.c`, `src/tab.c`, `tests/test_import_map.c`

## include/interp.h
- Doc: ip_ease: Compute eased t for normalized t ∈ [0,1].
- Layer: utility
- Language: h
- Symbols:
  - `ip_ease_fn` (struct, line 38)
  - `ip_keyframe` (struct, line 70)
  - `ip_anim` (struct, line 101)
  - `ip_easing` (enum, line 25)
  - `ip_val_kind` (enum, line 54)
  - `ip_direction` (enum, line 87)
  - `ip_fill_mode` (enum, line 94)
  - `kind` (type_alias, line 37) `typedef struct ip_ease_fn { ip_easing kind;`
  - `pct` (type_alias, line 69) `typedef struct ip_keyframe { double pct;`
  - `val_kind` (type_alias, line 100) `typedef struct ip_anim { ip_val_kind val_kind;`
  - `ip_ease` (function, line 48) `double ip_ease(double t, const ip_ease_fn *fn);`
  - `ip_lerp` (function, line 60) `double ip_lerp(double a, double b, double t);`
  - `ip_lerp_color` (function, line 61) `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t);`
  - `ip_interp` (function, line 62) `double ip_interp(ip_val_kind kind, double a, double b, double t);`
  - `ip_kf_interp` (function, line 78) `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf, int n_kf, double pct);`
  - `ip_anim_init` (function, line 121) `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease, const ip_keyframe *kf, int n_kf, double...`
  - `ip_anim_tick` (function, line 128) `int ip_anim_tick(ip_anim *a, double dt_ms);`
  - `ip_anim_current` (function, line 131) `double ip_anim_current(const ip_anim *a);`
  - `ip_anim_done` (function, line 134) `int ip_anim_done(const ip_anim *a);`
  - `FREEDOM_INTERP_H` (macro, line 2) `#define FREEDOM_INTERP_H`
  - `IP_MAX_KEYFRAMES` (macro, line 68) `#define IP_MAX_KEYFRAMES`
  - `IP_ITERATION_INFINITE` (macro, line 85) `#define IP_ITERATION_INFINITE`
- Imported by: `gui/browser_ui.c`, `src/interp.c`, `tests/test_interp.c`

## include/js_dom.h
- Doc: jd_iframe_track: Tracks iframes already processed by jd_process_iframes, to avoid re-fetching...
- Layer: utility
- Language: h
- Symbols:
  - `jd_iframe_track` (struct, line 41)
  - `jd_opaque` (struct, line 46)
  - `jd_status` (enum, line 25)
  - `jd_click_state` (type_alias, line 35) `typedef struct jd_click_state jd_click_state;`
  - `processed` (type_alias, line 41) `typedef struct jd_iframe_track { dom_node_id processed[JD_IFRAME_TRACK_MAX];`
  - `opaque` (function, line 64) `* the engine runtime opaque (unreachable from script);`
  - `jd_click_state_free` (function, line 78) `* jd_click_state_free(). Bound to one context via jd_install_events(). */ jd_click_state *jd_click_state_new(void);`
  - `run` (function, line 87) `* run (no handler registered, or handlers ran without calling preventDefault()), * and 0 if a handler called...`
  - `preventDefault` (function, line 94) `* preventDefault() was called, 1 if the default (form submission) should proceed. * ctx == NULL or no form found =>...`
  - `host` (function, line 123) `* for a trusted host (allow.conf AND js.conf);`
  - `jd_get_cookies` (function, line 134) `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz);`
  - `out_status` (function, line 142) `* On success returns 0 and sets *out_status (HTTP status, 0 if unknown), *out_body / * *out_body_len (response...`
  - `jd_process_iframes` (function, line 163) `* BEFORE jd_process_iframes() (so iframes are in the DOM for it to process). * ctx == NULL => JD_ERR_NULL_ARG. */...`
  - `URLs` (function, line 170) `* video URLs (.m3u8 then .mp4 patterns), and creates <video> elements in the document for * any found. Does NOT...`
  - `jd_video_from_scripts` (function, line 184) `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts, const size_t *script_lens, size_t...`
  - `FREEDOM_JS_DOM_H` (macro, line 2) `#define FREEDOM_JS_DOM_H`
  - `JD_IFRAME_TRACK_MAX` (macro, line 40) `#define JD_IFRAME_TRACK_MAX`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/js_geom.h`, `include/js_location.h`, `include/js_sandbox.h`, `include/url.h`
- Imported by: `fuzz/fuzz_js_dom.c`, `include/js_location.h`, `include/js_trusted.h`, `src/js_dom.c`, `src/js_dom_internal.h`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/js_location.c`, `src/tab.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`

## include/js_env.h
- Layer: infrastructure
- Language: h
- Symbols:
  - `je_status` (enum, line 27)
  - `poisoned` (function, line 43) `* readback is poisoned (deterministic within an origin, unlinkable across * sessions and across origins) to defeat...`
  - `FREEDOM_JS_ENV_H` (macro, line 2) `#define FREEDOM_JS_ENV_H`
- Depends on: `include/js_sandbox.h`
- Imported by: `src/js_env.c`, `src/tab.c`, `tests/test_js_env.c`


Next: [KB_include_p3.md](KB_include_p3.md)
