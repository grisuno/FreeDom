# Symbols (page 3 of 16)
Previous: [SYMBOLS_p2.md](SYMBOLS_p2.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `cb_expand_box2` | function | `include/css_box.h:21` | `int cb_expand_box2(const char *val, int slot_start, int slot_end, int allow_auto, int allow_neg, css_decl *dst, int...` |
| `cb_expand_box4` | function | `include/css_box.h:19` | `int cb_expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg, css_decl *dst, int cap);` |
| `cb_expand_grid_template_cols` | function | `include/css_box.h:43` | `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap);` |
| `cb_interp_align` | function | `include/css_box.h:33` | `int cb_interp_align(const char *v);` |
| `cb_interp_display` | function | `include/css_box.h:39` | `int cb_interp_display(const char *v);` |
| `cb_interp_fontsize_ex` | function | `include/css_box.h:34` | `int cb_interp_fontsize_ex(const char *v, int *abs_out);` |
| `cb_interp_gap` | function | `include/css_box.h:40` | `int cb_interp_gap(const char *v);` |
| `cb_interp_gridcols` | function | `include/css_box.h:42` | `int cb_interp_gridcols(const char *v);` |
| `cb_interp_justify` | function | `include/css_box.h:41` | `int cb_interp_justify(const char *v);` |
| `cb_interp_len` | function | `include/css_box.h:16` | `int cb_interp_len(const char *v, int allow_auto, int *out);` |
| `cb_interp_lineheight` | function | `include/css_box.h:35` | `int cb_interp_lineheight(const char *v);` |
| `cb_interp_lp` | function | `include/css_box.h:23` | `int cb_interp_lp(const char *v, int allow_auto, int allow_pct, int *out_px, int *out_pm);` |
| `cb_interp_style` | function | `include/css_box.h:37` | `int cb_interp_style(const char *v);` |
| `cb_interp_textdeco` | function | `include/css_box.h:38` | `int cb_interp_textdeco(const char *v);` |
| `cb_interp_weight` | function | `include/css_box.h:36` | `int cb_interp_weight(const char *v);` |
| `cb_length_px` | function | `include/css_box.h:15` | `int cb_length_px(const char *v, double *px);` |
| `cb_lp_can_be_nonneg` | function | `include/css_box.h:31` | `int cb_lp_can_be_nonneg(int px_val, int pct_pm);` |
| `cb_next_ws_token` | function | `include/css_box.h:32` | `int cb_next_ws_token(const char **p, char *tok, size_t cap);` |
| `cb_value_em_milli` | function | `include/css_box.h:25` | `int cb_value_em_milli(const char *v);` |
| `rectangle` | function | `include/css_box.h:27` | `* rectangle (top, right, bottom, left): px[i] + pm[i]/1000 of the border box (height for * top/bottom, width for...` |
| `strings` | function | `include/css_box.h:45` | `* Quoted area strings (the grid-template shorthand's row half) are skipped. */ int...` |
| `CCH_CHAIN_MAX` | macro | `include/css_chain.h:26` | `#define CCH_CHAIN_MAX` |
| `CCH_NTH_MAX` | macro | `include/css_chain.h:28` | `#define CCH_NTH_MAX` |
| `CCH_SIB_MAX` | macro | `include/css_chain.h:27` | `#define CCH_SIB_MAX` |
| `FREEDOM_CSS_CHAIN_H` | macro | `include/css_chain.h:2` | `#define FREEDOM_CSS_CHAIN_H` |
| `box` | function | `include/css_chain.h:91` | `* generated box (css_resolve_pseudo) against the same element context. * font_size is el's own COMPUTED font-size...` |
| `cch_element_matches` | function | `include/css_chain.h:81` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel);` |
| `cch_path` | type_alias | `include/css_chain.h:69` | `typedef struct cch_path cch_path;` |
| `cch_path_free` | function | `include/css_chain.h:71` | `void cch_path_free(cch_path *pa);` |
| `cch_path_new` | function | `include/css_chain.h:70` | `cch_path *cch_path_new(void);` |
| `cvr_chain` | struct | `include/css_chain.h:51` | `` |
| `cvr_table` | struct | `include/css_chain.h:52` | `` |
| `lacks` | function | `include/css_chain.h:85` | `* the element lacks (csel's subj_req) is rejected before the ancestor chain is built: on a * query that scans a...` |
| `CC_COLOR_CURRENT` | macro | `include/css_color.h:59` | `#define CC_COLOR_CURRENT` |
| `CC_COLOR_TRANSPARENT` | macro | `include/css_color.h:60` | `#define CC_COLOR_TRANSPARENT` |
| `FREEDOM_CSS_COLOR_H` | macro | `include/css_color.h:2` | `#define FREEDOM_CSS_COLOR_H` |
| `b` | type_alias | `include/css_color.h:26` | `typedef struct cc_rgb { unsigned char r, g, b;` |
| `cc_pack` | function | `include/css_color.h:49` | `int cc_pack(cc_rgb c);` |
| `cc_rgb` | struct | `include/css_color.h:27` | `` |
| `cc_status` | enum | `include/css_color.h:31` | `` |
| `CCM_VALUE_MAX` | macro | `include/css_computed.h:17` | `#define CCM_VALUE_MAX` |
| `FREEDOM_CSS_COMPUTED_H` | macro | `include/css_computed.h:2` | `#define FREEDOM_CSS_COMPUTED_H` |
| `ccm_get` | function | `include/css_computed.h:29` | `size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap);` |
| `ccm_input` | struct | `include/css_computed.h:19` | `` |
| `ccm_property_count` | function | `include/css_computed.h:32` | `size_t ccm_property_count(void);` |
| `ccm_property_name` | function | `include/css_computed.h:33` | `const char *ccm_property_name(size_t i);` |
| `CSS_INLINE_BG_URLS` | macro | `include/css_decl.h:28` | `#define CSS_INLINE_BG_URLS` |
| `CSS_MAX_BG_URLS` | macro | `include/css_decl.h:22` | `#define CSS_MAX_BG_URLS` |
| `CSS_MAX_CONTENT_URLS` | macro | `include/css_decl.h:23` | `#define CSS_MAX_CONTENT_URLS` |
| `CSS_MAX_KEYFRAMES` | macro | `include/css_decl.h:25` | `#define CSS_MAX_KEYFRAMES` |
| `CSS_MAX_KEYFRAME_DECLS` | macro | `include/css_decl.h:27` | `#define CSS_MAX_KEYFRAME_DECLS` |
| `CSS_MAX_KEYFRAME_STOPS` | macro | `include/css_decl.h:26` | `#define CSS_MAX_KEYFRAME_STOPS` |
| `CSS_POOL_HEADROOM` | macro | `include/css_decl.h:21` | `#define CSS_POOL_HEADROOM` |
| `CSS_POOL_INIT` | macro | `include/css_decl.h:20` | `#define CSS_POOL_INIT` |
| `CSS_WIDE_PROBE_DECLS` | macro | `include/css_decl.h:35` | `#define CSS_WIDE_PROBE_DECLS` |
| `FREEDOM_CSS_DECL_H` | macro | `include/css_decl.h:2` | `#define FREEDOM_CSS_DECL_H` |
| `contiguous` | function | `include/css_decl.h:65` | `* contiguous (dx,dy,color) so expand_shadow writes them as a group. */ P_FONTFAMILY, P_TEXTTRANSFORM...` |
| `css_decl` | struct | `include/css_decl.h:220` | `` |
| `order` | function | `include/css_decl.h:50` | `* The four margin slots are contiguous in CSS shorthand order (top,right,bottom, * left);` |
| `prop` | type_alias | `include/css_decl.h:219` | `typedef struct css_decl { int prop;` |
| `CG_LEN_UNSET` | macro | `include/css_gradient.h:18` | `#define CG_LEN_UNSET` |
| `FREEDOM_CSS_GRADIENT_H` | macro | `include/css_gradient.h:2` | `#define FREEDOM_CSS_GRADIENT_H` |
| `cg_expand_background` | function | `include/css_gradient.h:13` | `int cg_expand_background(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...` |
| `cg_expand_bg_image` | function | `include/css_gradient.h:11` | `int cg_expand_bg_image(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...` |
| `cg_parse_linear` | function | `include/css_gradient.h:51` | `int cg_parse_linear(const char *fn, int *angle, int *colors, int *positions);` |
| `cg_radial` | struct | `include/css_gradient.h:24` | `` |
| `cg_radial_len_px` | function | `include/css_gradient.h:37` | `double cg_radial_len_px(int enc, double dim);` |
| `cg_radial_shape` | enum | `include/css_gradient.h:19` | `` |
| `cg_radial_size` | enum | `include/css_gradient.h:20` | `` |
| `out` | function | `include/css_gradient.h:32` | `* Returns 1 and fills *out (defaults first) when seg is a valid prelude, 0 when seg is not * one (it is a colour...` |
| `shape` | type_alias | `include/css_gradient.h:24` | `typedef struct cg_radial { int shape;` |
| `width` | function | `include/css_gradient.h:17` | `* width (x, rx) or height (y, ry);` |
| `zero` | function | `include/css_gradient.h:41` | `* floored at a hair above zero (the spec paints the last colour for a degenerate size) and * never non-finite. Pure....` |
| `FREEDOM_CSS_INDEX_H` | macro | `include/css_index.h:11` | `#define FREEDOM_CSS_INDEX_H` |
| `cix_build` | function | `include/css_index.h:34` | `void cix_build(const css_sel *sels, size_t n, cix_index *idx);` |
| `cix_build_ptrs` | function | `include/css_index.h:37` | `void cix_build_ptrs(css_sel *const *sels, size_t n, cix_index *idx);` |
| `cix_entry` | struct | `include/css_index.h:18` | `` |
| `cix_free` | function | `include/css_index.h:40` | `void cix_free(cix_index *idx);` |
| `cix_index` | struct | `include/css_index.h:23` | `` |
| `index` | function | `include/css_index.h:44` | `* index (the caller then scans linearly). */ size_t cix_candidates(const cix_index *idx, const css_element *el...` |
| `key` | type_alias | `include/css_index.h:17` | `typedef struct cix_entry { uint64_t key;` |
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
| `cl_unit_is_font_relative` | function | `include/css_length.h:157` | `* cl_unit_is_font_relative() draws. */ /* * Re-fits a resolved length to a different font-size: * * used = px + em *...` |
| `font_size` | type_alias | `include/css_length.h:84` | `typedef struct cl_ctx { double font_size;` |
| `here` | function | `include/css_length.h:186` | `* Every input cl_resolve accepts resolves identically here (with has_pct 0);` |
| `length` | function | `include/css_length.h:206` | `* * A basis that is not a usable length (negative, zero, non-finite) contributes * nothing, but the absolute...` |
| `prelude` | function | `include/css_length.h:99` | `* correct context for a media query prelude (whose `em` is defined to use the * initial font size, never the...` |
| `px` | type_alias | `include/css_length.h:132` | `typedef struct cl_lp { double px;` |
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
| `CMQ_MAX_DEPTH` | macro | `include/css_mq.h:16` | `#define CMQ_MAX_DEPTH` |
| `CMQ_TOK_MAX` | macro | `include/css_mq.h:17` | `#define CMQ_TOK_MAX` |
| `FREEDOM_CSS_MQ_H` | macro | `include/css_mq.h:2` | `#define FREEDOM_CSS_MQ_H` |
| `cmq_env` | struct | `include/css_mq.h:19` | `` |
| `cmq_matches` | function | `include/css_mq.h:28` | `int cmq_matches(const char *s, size_t len, const cmq_env *env);` |
| `width_px` | type_alias | `include/css_mq.h:18` | `typedef struct cmq_env { int width_px;` |
| `CSEL_FOLD_MARK` | macro | `include/css_select.h:215` | `#define CSEL_FOLD_MARK` |
| `CSEL_FOLD_PREFIX` | macro | `include/css_select.h:214` | `#define CSEL_FOLD_PREFIX` |
| `CSEL_IDENT_SCRATCH` | macro | `include/css_select.h:216` | `#define CSEL_IDENT_SCRATCH` |
| `CSS_MAX_CLASSES_PER_SEL` | macro | `include/css_select.h:28` | `#define CSS_MAX_CLASSES_PER_SEL` |
| `CSS_MAX_SUB_SELS` | macro | `include/css_select.h:83` | `#define CSS_MAX_SUB_SELS` |
| `CSS_SUB_MAX_ATTRS` | macro | `include/css_select.h:84` | `#define CSS_SUB_MAX_ATTRS` |
| `CSS_SUB_MAX_PSEUDOS` | macro | `include/css_select.h:85` | `#define CSS_SUB_MAX_PSEUDOS` |
| `CSS_TOK_MAX` | macro | `include/css_select.h:27` | `#define CSS_TOK_MAX` |
| `FREEDOM_CSS_SELECT_H` | macro | `include/css_select.h:2` | `#define FREEDOM_CSS_SELECT_H` |
| `comb` | type_alias | `include/css_select.h:139` | `typedef struct css_sel { int comb[CSS_MAX_COMPOUNDS];` |
| `conservative` | function | `include/css_select.h:201` | `* Pure and conservative (anything unrecognised answers 1). A selector that answers 0 matches * from the element's...` |
| `csel_anc_reject` | function | `include/css_select.h:194` | `static inline int csel_anc_reject(const css_sel *sel, const css_element *el)` |
| `csel_ci_eq` | function | `include/css_select.h:243` | `static inline int csel_ci_eq(const char *a, const char *b)` |
| `csel_compact_dup` | function | `include/css_select.h:172` | `css_sel *csel_compact_dup(const css_sel *sel);` |
| `csel_compact_size` | function | `include/css_select.h:167` | `size_t csel_compact_size(int nparts);` |
| `csel_decl_end` | function | `include/css_select.h:235` | `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace);` |
| `csel_element_feature_bits` | function | `include/css_select.h:193` | `unsigned long long csel_element_feature_bits(const css_element *e);` |
| `csel_emit_utf8` | function | `include/css_select.h:219` | `size_t csel_emit_utf8(unsigned int cp, char *out);` |
| `csel_escape_len` | function | `include/css_select.h:223` | `size_t csel_escape_len(const char *s, size_t i, size_t b);` |
| `csel_ident_ch` | function | `include/css_select.h:271` | `static inline int csel_ident_ch(char c)` |
| `csel_ident_eq` | function | `include/css_select.h:227` | `int csel_ident_eq(const char *stored, const char *tok, size_t tlen);` |
| `csel_ident_fold` | function | `include/css_select.h:225` | `void csel_ident_fold(const char *src, size_t len, char *dst);` |
| `csel_lower_ch` | function | `include/css_select.h:239` | `static inline char csel_lower_ch(char c)` |
| `csel_matches` | function | `include/css_select.h:185` | `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id, int allow_pseudo_el, int...` |
| `csel_parse` | function | `include/css_select.h:176` | `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel);` |
| `csel_read_ident` | function | `include/css_select.h:230` | `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower);` |
| `csel_span_eq` | function | `include/css_select.h:252` | `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)` |
| `csel_substr` | function | `include/css_select.h:263` | `static inline int csel_substr(const char *hay, const char *needle, int ci)` |
| `csel_unescape` | function | `include/css_select.h:221` | `void csel_unescape(char *dst, size_t cap, const char *src, size_t n);` |
| `css_attr_match` | struct | `include/css_select.h:88` | `` |
| `css_compound` | struct | `include/css_select.h:122` | `` |
| `css_pseudo_match` | struct | `include/css_select.h:112` | `` |
| `css_sel` | struct | `include/css_select.h:139` | `` |
| `css_sub_sel` | struct | `include/css_select.h:95` | `` |
| `identifier` | function | `include/css_select.h:207` | `* A selector identifier (tag, .class, #id) is read with CSS escapes decoded * (`.md\:flex` is the class "md:flex")...` |
| `kind` | type_alias | `include/css_select.h:112` | `typedef struct css_pseudo_match { int kind;` |
| `name` | type_alias | `include/css_select.h:88` | `typedef struct css_attr_match { char name[CSS_TOK_MAX];` |
| `tag` | type_alias | `include/css_select.h:94` | `typedef struct css_sub_sel { char tag[CSS_TOK_MAX];` |
| `tag` | type_alias | `include/css_select.h:122` | `typedef struct css_compound { char tag[CSS_TOK_MAX];` |
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
| `closed` | function | `include/data_url.h:59` | `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/out/out_len == NULL (with b64_len !=...` |
| `du_is_data_url` | function | `include/data_url.h:46` | `int du_is_data_url(const char *url);` |
| `du_status` | enum | `include/data_url.h:27` | `` |
| `FREEDOM_DISK_STORE_H` | macro | `include/disk_store.h:2` | `#define FREEDOM_DISK_STORE_H` |
| `ds_free` | function | `include/disk_store.h:47` | `void ds_free(uint8_t *buf, size_t len);` |
| `ds_status` | enum | `include/disk_store.h:25` | `` |
| `DOM_KIND_COMMENT` | macro | `include/dom.h:206` | `#define DOM_KIND_COMMENT` |
| `DOM_KIND_ELEMENT` | macro | `include/dom.h:204` | `#define DOM_KIND_ELEMENT` |
| `DOM_KIND_NONE` | macro | `include/dom.h:203` | `#define DOM_KIND_NONE` |
| `DOM_KIND_TEXT` | macro | `include/dom.h:205` | `#define DOM_KIND_TEXT` |
| `DOM_MAX_HANDLES` | macro | `include/dom.h:209` | `#define DOM_MAX_HANDLES` |
| `DOM_NODE_NONE` | macro | `include/dom.h:37` | `#define DOM_NODE_NONE` |
| `FREEDOM_DOM_H` | macro | `include/dom.h:2` | `#define FREEDOM_DOM_H` |
| `count` | function | `include/dom.h:64` | `* match count (which may exceed cap, so the caller can size a buffer). */ size_t dom_get_by_tag(const dom_index...` |
| `cycle` | function | `include/dom.h:169` | `* Rejects a cycle (child being an ancestor of parent). Invalid handle / self / cycle * => DOM_ERR_NULL_ARG. */...` |
| `dom_attribute_names` | function | `include/dom.h:133` | `size_t dom_attribute_names(const dom_index *idx, dom_node_id node, const char **names, size_t *lens, size_t cap);` |
| `dom_document_position` | function | `include/dom.h:106` | `size_t dom_document_position(const dom_index *idx, dom_node_id node);` |
| `dom_document_title` | function | `include/dom.h:141` | `const char *dom_document_title(const dom_index *idx, size_t *len);` |
| `dom_free` | function | `include/dom.h:48` | `void dom_free(dom_index *idx);` |
| `dom_get_attribute` | function | `include/dom.h:126` | `const char *dom_get_attribute(const dom_index *idx, dom_node_id node, const char *name, size_t *len);` |
| `dom_get_by_class` | function | `include/dom.h:67` | `size_t dom_get_by_class(const dom_index *idx, const char *cls, dom_node_id *out, size_t cap);` |
| `dom_index` | type_alias | `include/dom.h:40` | `typedef struct dom_index dom_index;` |
| `dom_matches` | function | `include/dom.h:96` | `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector);` |
| `dom_node_count` | function | `include/dom.h:51` | `size_t dom_node_count(const dom_index *idx);` |
| `dom_node_id` | type_alias | `include/dom.h:34` | `typedef uint32_t dom_node_id;` |
| `dom_node_kind` | function | `include/dom.h:212` | `int dom_node_kind(const dom_index *idx, dom_node_id node);` |
| `dom_place` | enum | `include/dom.h:187` | `` |
| `dom_precedes` | function | `include/dom.h:109` | `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);` |
| `dom_status` | enum | `include/dom.h:26` | `` |
| `dom_tag_name` | function | `include/dom.h:123` | `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);` |
| `dom_text_content` | function | `include/dom.h:138` | `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len);` |
| `index` | function | `include/dom.h:228` | `* stays valid in the index (not freed). Invalid handle / not-a-child => DOM_ERR_NULL_ARG. */ dom_status...` |
| `length` | function | `include/dom.h:253` | `* length (no children => an owned empty string). Uses a chain of fixed-size * blocks internally so there is no hard...` |
| `parent` | function | `include/dom.h:196` | `* child of parent (for the *_REF places) or an invalid handle => DOM_ERR_NULL_ARG. */ dom_status...` |
| `process` | function | `include/dom.h:260` | `* modules in the same process (style resolution). NULL for a bad or non-element * handle. Valid until the next...` |
| `tree` | function | `include/dom.h:59` | `* tree (the index only grows, so a node a script removed is still registered and must not be * found);` |
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
| `FREEDOM_FLEX_LAYOUT_H` | macro | `include/flex_layout.h:2` | `#define FREEDOM_FLEX_LAYOUT_H` |
| `FX_AREA_MAX_CELLS` | macro | `include/flex_layout.h:138` | `#define FX_AREA_MAX_CELLS` |
| `FX_AREA_MAX_COLS` | macro | `include/flex_layout.h:137` | `#define FX_AREA_MAX_COLS` |
| `FX_AREA_MAX_ROWS` | macro | `include/flex_layout.h:136` | `#define FX_AREA_MAX_ROWS` |
| `FX_AREA_NAME_MAX` | macro | `include/flex_layout.h:139` | `#define FX_AREA_NAME_MAX` |
| `FX_ERR_NULL_ARG` | function | `include/flex_layout.h:228` | `* Returns FX_ERR_NULL_ARG (a required pointer NULL with n > 0), FX_ERR_RANGE * (negative h/avail, or n > FX_MAX_ITEMS);` |
| `FX_FLOAT_MIN_LINE` | macro | `include/flex_layout.h:208` | `#define FX_FLOAT_MIN_LINE` |
| `FX_GL_AUTO` | macro | `include/flex_layout.h:107` | `#define FX_GL_AUTO` |
| `FX_GL_LINE_MAX` | macro | `include/flex_layout.h:110` | `#define FX_GL_LINE_MAX` |
| `FX_GL_SPAN_BASE` | macro | `include/flex_layout.h:108` | `#define FX_GL_SPAN_BASE` |
| `FX_GL_SPAN_MAX` | macro | `include/flex_layout.h:109` | `#define FX_GL_SPAN_MAX` |
| `FX_MAUTO_BOTTOM` | macro | `include/flex_layout.h:338` | `#define FX_MAUTO_BOTTOM` |
| `FX_MAUTO_TOP` | macro | `include/flex_layout.h:337` | `#define FX_MAUTO_TOP` |
| `FX_MAX_COLUMNS` | macro | `include/flex_layout.h:270` | `#define FX_MAX_COLUMNS` |
| `FX_MAX_ITEMS` | macro | `include/flex_layout.h:28` | `#define FX_MAX_ITEMS` |
| `basis` | type_alias | `include/flex_layout.h:40` | `typedef struct fx_item { double basis;` |
| `bottom` | type_alias | `include/flex_layout.h:214` | `typedef struct fx_float_rect { double top, bottom;` |
| `cols` | type_alias | `include/flex_layout.h:144` | `typedef struct fx_area_map { int rows, cols;` |
| `fx_area_map` | struct | `include/flex_layout.h:144` | `` |
| `fx_auto_min_size` | function | `include/flex_layout.h:265` | `double fx_auto_min_size(double min_content, double basis, double author_min, int scroll_container);` |
| `fx_autofill_count` | function | `include/flex_layout.h:129` | `size_t fx_autofill_count(double avail, double gap, double minw);` |
| `fx_cross_offset` | function | `include/flex_layout.h:354` | `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r);` |
| `fx_float_rect` | struct | `include/flex_layout.h:214` | `` |
| `fx_grid_area_hash` | function | `include/flex_layout.h:153` | `unsigned fx_grid_area_hash(const char *name);` |
| `fx_grid_cell` | function | `include/flex_layout.h:74` | `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col);` |
| `fx_grid_line_parse` | function | `include/flex_layout.h:117` | `int fx_grid_line_parse(const char *v, int *start, int *end);` |
| `fx_grid_line_resolve` | function | `include/flex_layout.h:122` | `void fx_grid_line_resolve(int start, int end, int ntracks, int *pos0, int *span);` |
| `fx_item` | struct | `include/flex_layout.h:40` | `` |
| `fx_justify` | enum | `include/flex_layout.h:30` | `` |
| `fx_justify_name` | function | `include/flex_layout.h:321` | `const char *fx_justify_name(fx_justify j);` |
| `fx_result` | struct | `include/flex_layout.h:48` | `` |
| `fx_status` | enum | `include/flex_layout.h:53` | `` |
| `height` | function | `include/flex_layout.h:327` | `* used height (h_out);` |
| `it` | function | `include/flex_layout.h:344` | `* children that claim it (spec/flex_layout.md, tanda 44): proportionally to * grow[i] (x100) when any grows, else...` |
| `number` | function | `include/flex_layout.h:106` | `* line number (negative counts from the end). */ #define FX_GL_AUTO 0 #define FX_GL_SPAN_BASE (1 << 20) #define...` |
| `offset` | function | `include/flex_layout.h:171` | `* offset (from the content start, clamped to >= 0) to out_x[n]. The band does NOT wrap * (v1): an item that would...` |
| `out` | function | `include/flex_layout.h:62` | `* fx_result to out (caller-owned). n == 0 is a no-op (out may be NULL). */ fx_status fx_flex_line(const fx_item...` |
| `pos` | type_alias | `include/flex_layout.h:48` | `typedef struct fx_result { double pos;` |
| `required` | function | `include/flex_layout.h:184` | `* out_row is required (NULL with n > 0 yields FX_ERR_NULL_ARG);` |
| `size` | function | `include/flex_layout.h:60` | `* content size (px);` |
| `space` | function | `include/flex_layout.h:234` | `* line order: positive free space (avail - sizes - gaps) is split equally among every * auto margin...` |
| `widths` | function | `include/flex_layout.h:194` | `* the OUTER widths (width + ml + mr, clamped >= 0, so a negative margin narrows * the slot and a positive one widens...` |
| `win` | function | `include/flex_layout.h:352` | `* margins win (both = centre, left only = end);` |
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
| `FREEDOM_FRAME_HOST_H` | macro | `include/frame_host.h:2` | `#define FREEDOM_FRAME_HOST_H` |
| `fh_apply_top` | function | `include/frame_host.h:36` | `void fh_apply_top(fh_host *h, const tab_page *page);` |
| `fh_count` | function | `include/frame_host.h:43` | `int fh_count(const fh_host *h);` |
| `fh_frame_view` | function | `include/frame_host.h:49` | `const pv_view *fh_frame_view(const fh_host *h, const char *url, tab **t_out);` |
| `fh_free` | function | `include/frame_host.h:32` | `void fh_free(fh_host *h);` |
| `fh_generation` | function | `include/frame_host.h:52` | `unsigned fh_generation(const fh_host *h);` |
| `fh_host` | type_alias | `include/frame_host.h:19` | `typedef struct fh_host fh_host;` |
| `fh_new` | function | `include/frame_host.h:28` | `fh_host *fh_new(const char *top_url, tab_fetch_fn fetch, void *fetch_ctx, fh_top_msg_fn top_msg, void *top_ctx);` |
| `fh_tick` | function | `include/frame_host.h:40` | `int fh_tick(fh_host *h, int elapsed_ms);` |
| `it` | function | `include/frame_host.h:46` | `* confined worker last built it (NULL when no live frame has that URL);` |
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
| `FC_LAZY_IMAGE_MARGIN_PX` | macro | `include/freedom_config.h:81` | `#define FC_LAZY_IMAGE_MARGIN_PX` |
| `FC_MAX_AUTHOR_CSS_BYTES` | macro | `include/freedom_config.h:78` | `#define FC_MAX_AUTHOR_CSS_BYTES` |
| `FC_MAX_BOXES` | macro | `include/freedom_config.h:61` | `#define FC_MAX_BOXES` |
| `FC_PNG_MARGIN` | macro | `include/freedom_config.h:34` | `#define FC_PNG_MARGIN` |
| `FC_PNG_MAX_H` | macro | `include/freedom_config.h:39` | `#define FC_PNG_MAX_H` |
| `FC_PNG_PAGE_W` | macro | `include/freedom_config.h:20` | `#define FC_PNG_PAGE_W` |
| `FC_TAB_OP_NET_BUDGET_MS` | macro | `include/freedom_config.h:87` | `#define FC_TAB_OP_NET_BUDGET_MS` |
| `FC_TRUSTED_JS_BUDGET_MS` | macro | `include/freedom_config.h:30` | `#define FC_TRUSTED_JS_BUDGET_MS` |
| `FC_UI_FONT_SIZE` | macro | `include/freedom_config.h:70` | `#define FC_UI_FONT_SIZE` |
| `FREEDOM_CONFIG_H` | macro | `include/freedom_config.h:14` | `#define FREEDOM_CONFIG_H` |
| `FREEDOM_HLS_H` | macro | `include/hls.h:2` | `#define FREEDOM_HLS_H` |
| `hls_playlist` | struct | `include/hls.h:45` | `` |
| `hls_playlist_free` | function | `include/hls.h:74` | `void hls_playlist_free(hls_playlist *pl);` |
| `hls_segment` | struct | `include/hls.h:29` | `` |
| `hls_select_variant` | function | `include/hls.h:65` | `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h);` |
| `hls_status` | enum | `include/hls.h:21` | `` |
| `hls_variant` | struct | `include/hls.h:36` | `` |
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

Next: [SYMBOLS_p4.md](SYMBOLS_p4.md)
