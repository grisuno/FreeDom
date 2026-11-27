# Symbols (page 4 of 19)
Previous: [SYMBOLS_p3.md](SYMBOLS_p3.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `FREEDOM_CSS_IMPORT_H` | macro | `include/css_import.h:2` | `#define FREEDOM_CSS_IMPORT_H` |
| `ci_balanced` | function | `include/css_import.h:45` | `int ci_balanced(const char *css, size_t len);` |
| `ci_import` | struct | `include/css_import.h:25` | `` |
| `ci_scan` | function | `include/css_import.h:36` | `size_t ci_scan(const char *css, size_t len, ci_import *out, size_t cap);` |
| `ci_wrap` | function | `include/css_import.h:41` | `int ci_wrap(const ci_import *im, char *open, size_t ocap, char *close, size_t ccap);` |
| `url` | type_alias | `include/css_import.h:24` | `typedef struct ci_import { char url[CI_URL_MAX];` |
| `url` | function | `include/css_import.h:55` | `* rewritten to url("ABS"), ABS = resolve(base, ref) (spec/css_import.md, "Rebase"). * Fragment-only, schemed, empty...` |
| `FREEDOM_CSS_INDEX_H` | macro | `include/css_index.h:11` | `#define FREEDOM_CSS_INDEX_H` |
| `cix_build` | function | `include/css_index.h:34` | `void cix_build(const css_sel *sels, size_t n, cix_index *idx);` |
| `cix_build_ptrs` | function | `include/css_index.h:37` | `void cix_build_ptrs(css_sel *const *sels, size_t n, cix_index *idx);` |
| `cix_entry` | struct | `include/css_index.h:18` | `` |
| `cix_free` | function | `include/css_index.h:40` | `void cix_free(cix_index *idx);` |
| `cix_index` | struct | `include/css_index.h:23` | `` |
| `index` | function | `include/css_index.h:44` | `* index (the caller then scans linearly). */ size_t cix_candidates(const cix_index *idx, const css_element *el...` |
| `key` | type_alias | `include/css_index.h:17` | `typedef struct cix_entry { uint64_t key;` |
| `CL_FALLBACK_CAP_RATIO` | macro | `include/css_length.h:65` | `#define CL_FALLBACK_CAP_RATIO` |
| `CL_FALLBACK_CH_RATIO` | macro | `include/css_length.h:64` | `#define CL_FALLBACK_CH_RATIO` |
| `CL_FALLBACK_EX_RATIO` | macro | `include/css_length.h:57` | `#define CL_FALLBACK_EX_RATIO` |
| `CL_FALLBACK_IC_RATIO` | macro | `include/css_length.h:66` | `#define CL_FALLBACK_IC_RATIO` |
| `CL_INITIAL_FONT_SIZE` | macro | `include/css_length.h:39` | `#define CL_INITIAL_FONT_SIZE` |
| `CL_MAX_TOKEN` | macro | `include/css_length.h:33` | `#define CL_MAX_TOKEN` |
| `CL_NORMAL_LINE_RATIO` | macro | `include/css_length.h:45` | `#define CL_NORMAL_LINE_RATIO` |
| `FREEDOM_CSS_LENGTH_H` | macro | `include/css_length.h:2` | `#define FREEDOM_CSS_LENGTH_H` |
| `cl_ctx` | struct | `include/css_length.h:91` | `` |
| `cl_is_length_unit` | function | `include/css_length.h:253` | `int cl_is_length_unit(const char *unit, size_t unit_len);` |
| `cl_lp` | struct | `include/css_length.h:139` | `` |
| `cl_number` | function | `include/css_length.h:237` | `int cl_number(const char *s, double *out, const char **endp);` |
| `cl_status` | enum | `include/css_length.h:68` | `` |
| `cl_unit_font_ratio` | function | `include/css_length.h:189` | `double cl_unit_font_ratio(const char *unit, size_t unit_len);` |
| `cl_unit_is_font_relative` | function | `include/css_length.h:164` | `* cl_unit_is_font_relative() draws. */ /* * Re-fits a resolved length to a different font-size: * * used = px + em *...` |
| `font_size` | type_alias | `include/css_length.h:91` | `typedef struct cl_ctx { double font_size;` |
| `here` | function | `include/css_length.h:193` | `* Every input cl_resolve accepts resolves identically here (with has_pct 0);` |
| `length` | function | `include/css_length.h:213` | `* * A basis that is not a usable length (negative, zero, non-finite) contributes * nothing, but the absolute...` |
| `prelude` | function | `include/css_length.h:106` | `* correct context for a media query prelude (whose `em` is defined to use the * initial font size, never the...` |
| `px` | type_alias | `include/css_length.h:139` | `typedef struct cl_lp { double px;` |
| `CM_LAYERS` | macro | `include/css_mask.h:12` | `#define CM_LAYERS` |
| `FREEDOM_CSS_MASK_H` | macro | `include/css_mask.h:2` | `#define FREEDOM_CSS_MASK_H` |
| `cm_clip` | enum | `include/css_mask.h:15` | `` |
| `cm_comp` | enum | `include/css_mask.h:14` | `` |
| `cm_decode_layer` | function | `include/css_mask.h:36` | `void cm_decode_layer(int meta, int alphas, int poss, cm_layer *out);` |
| `cm_encode_layer` | function | `include/css_mask.h:35` | `void cm_encode_layer(const cm_layer *l, int *meta, int *alphas, int *poss);` |
| `cm_is_mask_prop` | function | `include/css_mask.h:28` | `int cm_is_mask_prop(const char *prop);` |
| `cm_layer` | struct | `include/css_mask.h:19` | `` |
| `kind` | type_alias | `include/css_mask.h:19` | `typedef struct cm_layer { int kind;` |
| `malformed` | function | `include/css_mask.h:31` | `* the value is unsupported or malformed (the caller drops the declaration). */ int cm_expand(const char *prop, const...` |
| `CMQ_CONTAINER_NAMES` | macro | `include/css_mq.h:37` | `#define CMQ_CONTAINER_NAMES` |
| `CMQ_MAX_DEPTH` | macro | `include/css_mq.h:16` | `#define CMQ_MAX_DEPTH` |
| `CMQ_TOK_MAX` | macro | `include/css_mq.h:17` | `#define CMQ_TOK_MAX` |
| `FREEDOM_CSS_MQ_H` | macro | `include/css_mq.h:2` | `#define FREEDOM_CSS_MQ_H` |
| `cmq_container` | struct | `include/css_mq.h:41` | `` |
| `cmq_container_decl` | function | `include/css_mq.h:63` | `int cmq_container_decl(const char *prop, const char *val, int *type, unsigned names[CMQ_CONTAINER_NAMES], int...` |
| `cmq_container_surely` | function | `include/css_mq.h:34` | `int cmq_container_surely(const char *s, size_t len, int max_width);` |
| `cmq_env` | struct | `include/css_mq.h:19` | `` |
| `cmq_matches` | function | `include/css_mq.h:28` | `int cmq_matches(const char *s, size_t len, const cmq_env *env);` |
| `cmq_name_hash` | function | `include/css_mq.h:50` | `unsigned cmq_name_hash(const char *s, size_t n);` |
| `names` | type_alias | `include/css_mq.h:41` | `typedef struct cmq_container { unsigned names[CMQ_CONTAINER_NAMES];` |
| `width_px` | type_alias | `include/css_mq.h:18` | `typedef struct cmq_env { int width_px;` |
| `CSEL_FOLD_MARK` | macro | `include/css_select.h:217` | `#define CSEL_FOLD_MARK` |
| `CSEL_FOLD_PREFIX` | macro | `include/css_select.h:216` | `#define CSEL_FOLD_PREFIX` |
| `CSEL_IDENT_SCRATCH` | macro | `include/css_select.h:218` | `#define CSEL_IDENT_SCRATCH` |
| `CSS_MAX_CLASSES_PER_SEL` | macro | `include/css_select.h:28` | `#define CSS_MAX_CLASSES_PER_SEL` |
| `CSS_MAX_SUB_SELS` | macro | `include/css_select.h:84` | `#define CSS_MAX_SUB_SELS` |
| `CSS_SUB_MAX_ATTRS` | macro | `include/css_select.h:85` | `#define CSS_SUB_MAX_ATTRS` |
| `CSS_SUB_MAX_PSEUDOS` | macro | `include/css_select.h:86` | `#define CSS_SUB_MAX_PSEUDOS` |
| `CSS_TOK_MAX` | macro | `include/css_select.h:27` | `#define CSS_TOK_MAX` |
| `FREEDOM_CSS_SELECT_H` | macro | `include/css_select.h:2` | `#define FREEDOM_CSS_SELECT_H` |
| `comb` | type_alias | `include/css_select.h:140` | `typedef struct css_sel { int comb[CSS_MAX_COMPOUNDS];` |
| `conservative` | function | `include/css_select.h:203` | `* Pure and conservative (anything unrecognised answers 1). A selector that answers 0 matches * from the element's...` |
| `csel_anc_reject` | function | `include/css_select.h:196` | `static inline int csel_anc_reject(const css_sel *sel, const css_element *el)` |
| `csel_ci_eq` | function | `include/css_select.h:245` | `static inline int csel_ci_eq(const char *a, const char *b)` |
| `csel_ci_starts` | function | `include/css_select.h:254` | `static inline int csel_ci_starts(const char *a, const char *p)` |
| `csel_compact_dup` | function | `include/css_select.h:174` | `css_sel *csel_compact_dup(const css_sel *sel);` |
| `csel_compact_size` | function | `include/css_select.h:169` | `size_t csel_compact_size(int nparts);` |
| `csel_decl_end` | function | `include/css_select.h:237` | `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace);` |
| `csel_element_feature_bits` | function | `include/css_select.h:195` | `unsigned long long csel_element_feature_bits(const css_element *e);` |
| `csel_emit_utf8` | function | `include/css_select.h:221` | `size_t csel_emit_utf8(unsigned int cp, char *out);` |
| `csel_escape_len` | function | `include/css_select.h:225` | `size_t csel_escape_len(const char *s, size_t i, size_t b);` |
| `csel_ident_ch` | function | `include/css_select.h:282` | `static inline int csel_ident_ch(char c)` |
| `csel_ident_eq` | function | `include/css_select.h:229` | `int csel_ident_eq(const char *stored, const char *tok, size_t tlen);` |
| `csel_ident_fold` | function | `include/css_select.h:227` | `void csel_ident_fold(const char *src, size_t len, char *dst);` |
| `csel_lower_ch` | function | `include/css_select.h:241` | `static inline char csel_lower_ch(char c)` |
| `csel_matches` | function | `include/css_select.h:187` | `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id, int allow_pseudo_el, int...` |
| `csel_parse` | function | `include/css_select.h:178` | `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel);` |
| `csel_read_ident` | function | `include/css_select.h:232` | `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower);` |
| `csel_span_eq` | function | `include/css_select.h:263` | `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)` |
| `csel_substr` | function | `include/css_select.h:274` | `static inline int csel_substr(const char *hay, const char *needle, int ci)` |
| `csel_unescape` | function | `include/css_select.h:223` | `void csel_unescape(char *dst, size_t cap, const char *src, size_t n);` |
| `css_attr_match` | struct | `include/css_select.h:89` | `` |
| `css_compound` | struct | `include/css_select.h:123` | `` |
| `css_pseudo_match` | struct | `include/css_select.h:113` | `` |
| `css_sel` | struct | `include/css_select.h:140` | `` |
| `css_sub_sel` | struct | `include/css_select.h:96` | `` |
| `identifier` | function | `include/css_select.h:209` | `* A selector identifier (tag, .class, #id) is read with CSS escapes decoded * (`.md\:flex` is the class "md:flex")...` |
| `kind` | type_alias | `include/css_select.h:113` | `typedef struct css_pseudo_match { int kind;` |
| `name` | type_alias | `include/css_select.h:89` | `typedef struct css_attr_match { char name[CSS_TOK_MAX];` |
| `tag` | type_alias | `include/css_select.h:95` | `typedef struct css_sub_sel { char tag[CSS_TOK_MAX];` |
| `tag` | type_alias | `include/css_select.h:123` | `typedef struct css_compound { char tag[CSS_TOK_MAX];` |
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
| `black` | function | `include/css_values.h:27` | `* transparent black (127 << 24) -- text that paints nothing, not an absent * value. CC_COLOR_CURRENT and -1...` |
| `cv_bg_alpha_of` | function | `include/css_values.h:15` | `int cv_bg_alpha_of(const char *v);` |
| `cv_color_ok` | function | `include/css_values.h:14` | `int cv_color_ok(int c);` |
| `cv_filter_scale` | function | `include/css_values.h:20` | `double cv_filter_scale(int pct);` |
| `cv_interp_bg` | function | `include/css_values.h:30` | `int cv_interp_bg(const char *v);` |
| `cv_interp_color` | function | `include/css_values.h:13` | `int cv_interp_color(const char *v);` |
| `cv_parse_color` | function | `include/css_values.h:12` | `int cv_parse_color(const char *v);` |
| `cv_parse_color_t7` | function | `include/css_values.h:24` | `int cv_parse_color_t7(const char *v);` |
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
| `declaration` | function | `include/css_vars.h:91` | `* then drops the whole declaration (CSS Variables 1: invalid at computed time). */ int cvr_resolve(const char *val...` |
| `name` | function | `include/css_vars.h:62` | `* name (last declaration wins). Returns 1 when stored, 0 when dropped: a name that * is not "--" + at least one...` |
| `DU_MAX_ENCODED_LEN` | macro | `include/data_url.h:43` | `#define DU_MAX_ENCODED_LEN` |
| `FREEDOM_DATA_URL_H` | macro | `include/data_url.h:2` | `#define FREEDOM_DATA_URL_H` |
| `allocation` | function | `include/data_url.h:21` | `* * du_base64_payload does no allocation (it only slices the caller's url string);` |
| `closed` | function | `include/data_url.h:65` | `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/out/out_len == NULL (with b64_len !=...` |
| `du_is_data_url` | function | `include/data_url.h:46` | `int du_is_data_url(const char *url);` |
| `du_status` | enum | `include/data_url.h:27` | `` |
| `worker` | function | `include/data_url.h:59` | `* the confined worker (du_decode). */ du_status du_shape_ok(const char *url);` |
| `FREEDOM_DISK_STORE_H` | macro | `include/disk_store.h:2` | `#define FREEDOM_DISK_STORE_H` |
| `ds_free` | function | `include/disk_store.h:47` | `void ds_free(uint8_t *buf, size_t len);` |
| `ds_status` | enum | `include/disk_store.h:25` | `` |
| `DT_SCAN_MAX` | macro | `include/doc_title.h:14` | `#define DT_SCAN_MAX` |
| `FREEDOM_DOC_TITLE_H` | macro | `include/doc_title.h:5` | `#define FREEDOM_DOC_TITLE_H` |
| `dt_scan` | function | `include/doc_title.h:20` | `int dt_scan(const char *html, size_t len, char *out, size_t cap);` |
| `DOM_KIND_COMMENT` | macro | `include/dom.h:217` | `#define DOM_KIND_COMMENT` |
| `DOM_KIND_ELEMENT` | macro | `include/dom.h:215` | `#define DOM_KIND_ELEMENT` |
| `DOM_KIND_NONE` | macro | `include/dom.h:214` | `#define DOM_KIND_NONE` |
| `DOM_KIND_TEXT` | macro | `include/dom.h:216` | `#define DOM_KIND_TEXT` |
| `DOM_MAX_HANDLES` | macro | `include/dom.h:220` | `#define DOM_MAX_HANDLES` |
| `DOM_NODE_NONE` | macro | `include/dom.h:37` | `#define DOM_NODE_NONE` |
| `FREEDOM_DOM_H` | macro | `include/dom.h:2` | `#define FREEDOM_DOM_H` |
| `count` | function | `include/dom.h:68` | `* match count (which may exceed cap, so the caller can size a buffer). */ size_t dom_get_by_tag(const dom_index...` |
| `cycle` | function | `include/dom.h:180` | `* Rejects a cycle (child being an ancestor of parent). Invalid handle / self / cycle * => DOM_ERR_NULL_ARG. */...` |
| `dom_attribute_names` | function | `include/dom.h:137` | `size_t dom_attribute_names(const dom_index *idx, dom_node_id node, const char **names, size_t *lens, size_t cap);` |
| `dom_document_position` | function | `include/dom.h:110` | `size_t dom_document_position(const dom_index *idx, dom_node_id node);` |
| `dom_document_title` | function | `include/dom.h:145` | `const char *dom_document_title(const dom_index *idx, size_t *len);` |
| `dom_free` | function | `include/dom.h:48` | `void dom_free(dom_index *idx);` |
| `dom_get_attribute` | function | `include/dom.h:130` | `const char *dom_get_attribute(const dom_index *idx, dom_node_id node, const char *name, size_t *len);` |
| `dom_get_by_class` | function | `include/dom.h:71` | `size_t dom_get_by_class(const dom_index *idx, const char *cls, dom_node_id *out, size_t cap);` |
| `dom_index` | type_alias | `include/dom.h:40` | `typedef struct dom_index dom_index;` |
| `dom_is_connected` | function | `include/dom.h:65` | `int dom_is_connected(const dom_index *idx, dom_node_id node);` |
| `dom_matches` | function | `include/dom.h:100` | `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector);` |
| `dom_node_count` | function | `include/dom.h:51` | `size_t dom_node_count(const dom_index *idx);` |
| `dom_node_id` | type_alias | `include/dom.h:34` | `typedef uint32_t dom_node_id;` |
| `dom_node_kind` | function | `include/dom.h:223` | `int dom_node_kind(const dom_index *idx, dom_node_id node);` |
| `dom_place` | enum | `include/dom.h:198` | `` |
| `dom_precedes` | function | `include/dom.h:113` | `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);` |
| `dom_status` | enum | `include/dom.h:26` | `` |
| `dom_tag_name` | function | `include/dom.h:127` | `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);` |
| `dom_text_content` | function | `include/dom.h:142` | `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len);` |
| `index` | function | `include/dom.h:239` | `* stays valid in the index (not freed). Invalid handle / not-a-child => DOM_ERR_NULL_ARG. */ dom_status...` |
| `length` | function | `include/dom.h:264` | `* length (no children => an owned empty string). Uses a chain of fixed-size * blocks internally so there is no hard...` |
| `parent` | function | `include/dom.h:207` | `* child of parent (for the *_REF places) or an invalid handle => DOM_ERR_NULL_ARG. */ dom_status...` |
| `process` | function | `include/dom.h:271` | `* modules in the same process (style resolution). NULL for a bad or non-element * handle. Valid until the next...` |
| `sight` | function | `include/dom.h:276` | `* first sight (an innerHTML subtree has no handles until something asks). Registration * is not a tree change...` |
| `tree` | function | `include/dom.h:59` | `* tree (the index only grows, so a node a script removed is still registered and must not be * found);` |
| `valid` | function | `include/dom.h:150` | `* detached node stays valid (it just becomes unreachable from the root and is no * longer rendered). These never...` |
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
| `FC_ANCHOR_HOLD_MS` | macro | `include/freedom_config.h:38` | `#define FC_ANCHOR_HOLD_MS` |
| `FC_FLEX_MEASURE_W` | macro | `include/freedom_config.h:66` | `#define FC_FLEX_MEASURE_W` |
| `FC_FLEX_MIN_MEASURE_W` | macro | `include/freedom_config.h:72` | `#define FC_FLEX_MIN_MEASURE_W` |
| `FC_FONT_CHAIN_MAX` | macro | `include/freedom_config.h:77` | `#define FC_FONT_CHAIN_MAX` |
| `FC_FONT_FALLBACK_PX` | macro | `include/freedom_config.h:87` | `#define FC_FONT_FALLBACK_PX` |
| `FC_HEADLESS_VIEW_H` | macro | `include/freedom_config.h:45` | `#define FC_HEADLESS_VIEW_H` |
| `FC_JS_FRAGMENT_DEPTH` | macro | `include/freedom_config.h:41` | `#define FC_JS_FRAGMENT_DEPTH` |
| `FC_LAZY_IMAGE_MARGIN_PX` | macro | `include/freedom_config.h:120` | `#define FC_LAZY_IMAGE_MARGIN_PX` |
| `FC_MASK_CACHE_BYTES` | macro | `include/freedom_config.h:116` | `#define FC_MASK_CACHE_BYTES` |
| `FC_MASK_CACHE_ENTRIES` | macro | `include/freedom_config.h:117` | `#define FC_MASK_CACHE_ENTRIES` |
| `FC_MAX_AUTHOR_CSS_BYTES` | macro | `include/freedom_config.h:99` | `#define FC_MAX_AUTHOR_CSS_BYTES` |
| `FC_MAX_BOXES` | macro | `include/freedom_config.h:82` | `#define FC_MAX_BOXES` |
| `FC_MONO_DEFAULT_PX` | macro | `include/freedom_config.h:26` | `#define FC_MONO_DEFAULT_PX` |
| `FC_NET_LOAD_SETTLE_MS` | macro | `include/freedom_config.h:133` | `#define FC_NET_LOAD_SETTLE_MS` |
| `FC_NET_POLL_MS` | macro | `include/freedom_config.h:134` | `#define FC_NET_POLL_MS` |
| `FC_NET_TICK_SETTLE_MS` | macro | `include/freedom_config.h:137` | `#define FC_NET_TICK_SETTLE_MS` |
| `FC_PNG_MARGIN` | macro | `include/freedom_config.h:55` | `#define FC_PNG_MARGIN` |
| `FC_PNG_MAX_H` | macro | `include/freedom_config.h:60` | `#define FC_PNG_MAX_H` |
| `FC_PNG_PAGE_W` | macro | `include/freedom_config.h:20` | `#define FC_PNG_PAGE_W` |
| `FC_SHC_MAX_QUERIES` | macro | `include/freedom_config.h:111` | `#define FC_SHC_MAX_QUERIES` |
| `FC_SHC_MAX_TEXT_BYTES` | macro | `include/freedom_config.h:105` | `#define FC_SHC_MAX_TEXT_BYTES` |
| `FC_SMOOTH_SCROLL_ANCHOR_MS` | macro | `include/freedom_config.h:35` | `#define FC_SMOOTH_SCROLL_ANCHOR_MS` |
| `FC_SMOOTH_SCROLL_FRAME_MS` | macro | `include/freedom_config.h:32` | `#define FC_SMOOTH_SCROLL_FRAME_MS` |
| `FC_SMOOTH_SCROLL_MS` | macro | `include/freedom_config.h:31` | `#define FC_SMOOTH_SCROLL_MS` |
| `FC_TABLE_TRACK_MAX_PX` | macro | `include/freedom_config.h:141` | `#define FC_TABLE_TRACK_MAX_PX` |
| `FC_TAB_OP_NET_BUDGET_MS` | macro | `include/freedom_config.h:126` | `#define FC_TAB_OP_NET_BUDGET_MS` |
| `FC_TRUSTED_JS_BUDGET_MS` | macro | `include/freedom_config.h:51` | `#define FC_TRUSTED_JS_BUDGET_MS` |
| `FC_UI_FONT_SIZE` | macro | `include/freedom_config.h:91` | `#define FC_UI_FONT_SIZE` |
| `FREEDOM_CONFIG_H` | macro | `include/freedom_config.h:14` | `#define FREEDOM_CONFIG_H` |
| `FREEDOM_GROUP_INDEX_H` | macro | `include/group_index.h:2` | `#define FREEDOM_GROUP_INDEX_H` |
| `gi_build` | function | `include/group_index.h:20` | `size_t gi_build(const int *keys, size_t n, size_t nkeys, size_t *offs, size_t *items);` |
| `group_index` | function | `include/group_index.h:9` | `* group_index (gi_) -- stable group-by of n items by an integer key, in CSR form, so a * per-group pass visits only...` |
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

Next: [SYMBOLS_p5.md](SYMBOLS_p5.md)
