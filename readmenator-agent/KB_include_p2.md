# Subsystem: include (page 2 of 6)
Previous: [KB_include.md](KB_include.md)

## include/css_chain.h
- Doc: cch_element_matches: Nonzero iff the parsed selector *sel matches element `el`, built against...
- Layer: utility
- Language: h
- Symbols:
  - `cvr_chain` (struct, line 51)
  - `cvr_table` (struct, line 52)
  - `cch_path` (type_alias, line 69) `typedef struct cch_path cch_path;`
  - `cch_path_new` (function, line 70) `cch_path *cch_path_new(void);`
  - `cch_path_free` (function, line 71) `void cch_path_free(cch_path *pa);`
  - `cch_element_matches` (function, line 82) `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel);`
  - `lacks` (function, line 86) `* the element lacks (csel's subj_req) is rejected before the ancestor chain is built: on a * query that scans a...`
  - `COMPARED` (function, line 94) `* pointer is only ever COMPARED (a detached element is never freed while the document * lives). Returns 1 when the...`
  - `box` (function, line 99) `* generated box (css_resolve_pseudo) against the same element context. * font_size is el's own COMPUTED font-size...`
  - `FREEDOM_CSS_CHAIN_H` (macro, line 2) `#define FREEDOM_CSS_CHAIN_H`
  - `CCH_CHAIN_MAX` (macro, line 26) `#define CCH_CHAIN_MAX`
  - `CCH_SIB_MAX` (macro, line 27) `#define CCH_SIB_MAX`
  - `CCH_NTH_MAX` (macro, line 28) `#define CCH_NTH_MAX`
- Depends on: `include/css.h`, `include/css_select.h`
- Imported by: `src/css_chain.c`, `src/dom.c`, `src/page_view.c`, `src/tab.c`, `tests/test_page_view.c`

## include/css_color.h
- Doc: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for...
- Layer: utility
- Language: h
- Symbols:
  - `cc_rgb` (struct, line 27)
  - `cc_status` (enum, line 31)
  - `b` (type_alias, line 26) `typedef struct cc_rgb { unsigned char r, g, b;`
  - `cc_pack` (function, line 49) `int cc_pack(cc_rgb c);`
  - `FREEDOM_CSS_COLOR_H` (macro, line 2) `#define FREEDOM_CSS_COLOR_H`
  - `CC_COLOR_CURRENT` (macro, line 59) `#define CC_COLOR_CURRENT`
  - `CC_COLOR_TRANSPARENT` (macro, line 60) `#define CC_COLOR_TRANSPARENT`
- Imported by: `gui/browser_ui.c`, `gui/bui_theme.c`, `include/css.h`, `src/css.c`, `src/css_box.c`, `src/css_color.c`, `src/css_gradient.c`, `src/css_text.c`, `src/css_values.c`, `src/page_view.c`, `src/pres_hints.c`, `src/svg_paint.c`, `src/svg_render.c`, `tests/test_css_color.c`

## include/css_computed.h
- Doc: ccm_get: Writes the computed value of the kebab-case property `prop` into out (cap bytes, NUL...
- Layer: utility
- Language: h
- Symbols:
  - `ccm_input` (struct, line 19)
  - `ccm_get` (function, line 29) `size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap);`
  - `ccm_property_count` (function, line 32) `size_t ccm_property_count(void);`
  - `ccm_property_name` (function, line 33) `const char *ccm_property_name(size_t i);`
  - `FREEDOM_CSS_COMPUTED_H` (macro, line 2) `#define FREEDOM_CSS_COMPUTED_H`
  - `CCM_VALUE_MAX` (macro, line 17) `#define CCM_VALUE_MAX`
- Depends on: `include/css.h`
- Imported by: `src/css_computed.c`, `src/tab.c`, `tests/test_css_computed.c`

## include/css_counter.h
- Doc: cnt_hash: FNV-1a over `len` bytes of an identifier, ASCII case preserved (identifiers are *...
- Layer: utility
- Language: h
- Symbols:
  - `cnt_decl` (struct, line 21)
  - `cnt_style` (enum, line 26)
  - `name` (type_alias, line 20) `typedef struct cnt_decl { unsigned name;`
  - `cnt_state` (type_alias, line 50) `typedef struct cnt_state cnt_state;`
  - `cnt_hash` (function, line 34) `unsigned cnt_hash(const char *name, size_t len);`
  - `written` (function, line 37) `* written (0 for `none`) or -1 when invalid. `dflt` is the value of an entry with no * integer: 0 for reset, 1 for...`
  - `cnt_parse_content` (function, line 44) `int cnt_parse_content(const char *val, char *out, size_t cap);`
  - `cnt_is_marker` (function, line 45) `int cnt_is_marker(const char *s);`
  - `cnt_format` (function, line 49) `size_t cnt_format(int style, long value, char *out, size_t cap);`
  - `cnt_state_new` (function, line 52) `cnt_state *cnt_state_new(void);`
  - `cnt_state_free` (function, line 53) `void cnt_state_free(cnt_state *s);`
  - `cnt_reset` (function, line 56) `void cnt_reset(cnt_state *s, int depth, const cnt_decl *d, int n);`
  - `cnt_increment` (function, line 57) `void cnt_increment(cnt_state *s, int depth, const cnt_decl *d, int n);`
  - `cnt_leave` (function, line 60) `void cnt_leave(cnt_state *s, int depth);`
  - `cnt_resolve` (function, line 67) `size_t cnt_resolve(const cnt_state *s, const char *marker, cnt_attr_fn attr, void *ctx, char *out, size_t cap);`
  - `FREEDOM_CSS_COUNTER_H` (macro, line 9) `#define FREEDOM_CSS_COUNTER_H`
  - `CNT_MAX_DECL` (macro, line 17) `#define CNT_MAX_DECL`
  - `CNT_MAX_INSTANCES` (macro, line 18) `#define CNT_MAX_INSTANCES`
  - `CNT_NAME_MAX` (macro, line 19) `#define CNT_NAME_MAX`
- Imported by: `fuzz/fuzz_css_counter.c`, `include/css.h`, `src/css_counter.c`, `tests/test_css_counter.c`

## include/css_decl.h
- Doc: The sheet's two string pools -- background url()s, and the ::before/::after
- Layer: utility
- Language: h
- Symbols:
  - `css_decl` (struct, line 243)
  - `prop` (type_alias, line 242) `typedef struct css_decl { int prop;`
  - `order` (function, line 50) `* The four margin slots are contiguous in CSS shorthand order (top,right,bottom, * left);`
  - `contiguous` (function, line 65) `* contiguous (dx,dy,color) so expand_shadow writes them as a group. */ P_FONTFAMILY, P_TEXTTRANSFORM...`
  - `part` (function, line 216) `* each P_CLIP_* edge adds to its px part (the other half of a <length-percentage>). */ P_CLIP_TOP_PM...`
  - `FREEDOM_CSS_DECL_H` (macro, line 2) `#define FREEDOM_CSS_DECL_H`
  - `CSS_POOL_INIT` (macro, line 20) `#define CSS_POOL_INIT`
  - `CSS_POOL_HEADROOM` (macro, line 21) `#define CSS_POOL_HEADROOM`
  - `CSS_MAX_BG_URLS` (macro, line 22) `#define CSS_MAX_BG_URLS`
  - `CSS_MAX_CONTENT_URLS` (macro, line 23) `#define CSS_MAX_CONTENT_URLS`
  - `CSS_MAX_KEYFRAMES` (macro, line 25) `#define CSS_MAX_KEYFRAMES`
  - `CSS_MAX_KEYFRAME_STOPS` (macro, line 26) `#define CSS_MAX_KEYFRAME_STOPS`
  - `CSS_MAX_KEYFRAME_DECLS` (macro, line 27) `#define CSS_MAX_KEYFRAME_DECLS`
  - `CSS_INLINE_BG_URLS` (macro, line 28) `#define CSS_INLINE_BG_URLS`
  - `CSS_WIDE_PROBE_DECLS` (macro, line 35) `#define CSS_WIDE_PROBE_DECLS`
- Depends on: `include/css.h`, `include/css_select.h`
- Imported by: `include/css_box.h`, `include/css_gradient.h`, `include/css_mask.h`, `include/css_text.h`, `src/css.c`, `src/css_box.c`, `src/css_gradient.c`, `src/css_text.c`, `src/css_values.c`, `src/page_view.c`, `tests/test_css_box.c`, `tests/test_css_text.c`

## include/css_gradient.h
- Doc: The first url(...) token of val, unquoted and trimmed, into out.
- Layer: utility
- Language: h
- Symbols:
  - `cg_radial` (struct, line 28)
  - `cg_radial_shape` (enum, line 23)
  - `cg_radial_size` (enum, line 24)
  - `shape` (type_alias, line 28) `typedef struct cg_radial { int shape;`
  - `cg_first_url` (function, line 13) `int cg_first_url(const char *val, char *out, size_t outcap);`
  - `cg_expand_bg_image` (function, line 15) `int cg_expand_bg_image(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...`
  - `cg_expand_background` (function, line 17) `int cg_expand_background(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...`
  - `width` (function, line 21) `* width (x, rx) or height (y, ry);`
  - `out` (function, line 36) `* Returns 1 and fills *out (defaults first) when seg is a valid prelude, 0 when seg is not * one (it is a colour...`
  - `cg_radial_len_px` (function, line 41) `double cg_radial_len_px(int enc, double dim);`
  - `zero` (function, line 45) `* floored at a hair above zero (the spec paints the last colour for a degenerate size) and * never non-finite. Pure....`
  - `cg_parse_linear` (function, line 55) `int cg_parse_linear(const char *fn, int *angle, int *colors, int *positions);`
  - `FREEDOM_CSS_GRADIENT_H` (macro, line 2) `#define FREEDOM_CSS_GRADIENT_H`
  - `CG_LEN_UNSET` (macro, line 22) `#define CG_LEN_UNSET`
- Depends on: `include/css_decl.h`
- Imported by: `gui/browser_ui.c`, `src/css.c`, `src/css_gradient.c`, `src/css_mask.c`, `src/tab.c`, `tests/test_css_gradient.c`

## include/css_import.h
- Doc: ci_scan: Reads the leading @import rules of css[0,len) into out (at most cap).
- Layer: utility
- Language: h
- Symbols:
  - `ci_import` (struct, line 25)
  - `url` (type_alias, line 24) `typedef struct ci_import { char url[CI_URL_MAX];`
  - `ci_scan` (function, line 36) `size_t ci_scan(const char *css, size_t len, ci_import *out, size_t cap);`
  - `ci_wrap` (function, line 41) `int ci_wrap(const ci_import *im, char *open, size_t ocap, char *close, size_t ccap);`
  - `ci_balanced` (function, line 45) `int ci_balanced(const char *css, size_t len);`
  - `url` (function, line 55) `* rewritten to url("ABS"), ABS = resolve(base, ref) (spec/css_import.md, "Rebase"). * Fragment-only, schemed, empty...`
  - `FREEDOM_CSS_IMPORT_H` (macro, line 2) `#define FREEDOM_CSS_IMPORT_H`
  - `CI_URL_MAX` (macro, line 19) `#define CI_URL_MAX`
  - `CI_COND_MAX` (macro, line 20) `#define CI_COND_MAX`
  - `CI_MAX_DEPTH` (macro, line 21) `#define CI_MAX_DEPTH`
  - `CI_MAX_PER_PAGE` (macro, line 22) `#define CI_MAX_PER_PAGE`
  - `CI_MAX_PER_SHEET` (macro, line 23) `#define CI_MAX_PER_SHEET`
- Imported by: `fuzz/fuzz_css_import.c`, `src/css_import.c`, `src/tab.c`, `tests/test_css_import.c`, `tests/test_tab.c`

## include/css_index.h
- Doc: cix_build: Builds the index over sels[0,n) into *idx, overwriting it (a built index must be *...
- Layer: utility
- Language: h
- Symbols:
  - `cix_entry` (struct, line 18)
  - `cix_index` (struct, line 23)
  - `key` (type_alias, line 17) `typedef struct cix_entry { uint64_t key;`
  - `cix_build` (function, line 34) `void cix_build(const css_sel *sels, size_t n, cix_index *idx);`
  - `cix_build_ptrs` (function, line 37) `void cix_build_ptrs(css_sel *const *sels, size_t n, cix_index *idx);`
  - `cix_free` (function, line 40) `void cix_free(cix_index *idx);`
  - `index` (function, line 44) `* index (the caller then scans linearly). */ size_t cix_candidates(const cix_index *idx, const css_element *el...`
  - `FREEDOM_CSS_INDEX_H` (macro, line 11) `#define FREEDOM_CSS_INDEX_H`
- Depends on: `include/css_select.h`
- Imported by: `src/css.c`, `src/css_index.c`, `tests/test_css_index.c`

## include/css_length.h
- Doc: cl_ctx: The state a <length> is measured against.
- Layer: utility
- Language: h
- Symbols:
  - `cl_ctx` (struct, line 91)
  - `cl_lp` (struct, line 139)
  - `cl_status` (enum, line 68)
  - `font_size` (type_alias, line 91) `typedef struct cl_ctx { double font_size;`
  - `px` (type_alias, line 139) `typedef struct cl_lp { double px;`
  - `prelude` (function, line 106) `* correct context for a media query prelude (whose `em` is defined to use the * initial font size, never the...`
  - `cl_unit_is_font_relative` (function, line 164) `* cl_unit_is_font_relative() draws. */ /* * Re-fits a resolved length to a different font-size: * * used = px + em *...`
  - `cl_unit_font_ratio` (function, line 189) `double cl_unit_font_ratio(const char *unit, size_t unit_len);`
  - `here` (function, line 193) `* Every input cl_resolve accepts resolves identically here (with has_pct 0);`
  - `length` (function, line 213) `* * A basis that is not a usable length (negative, zero, non-finite) contributes * nothing, but the absolute...`
  - `cl_number` (function, line 237) `int cl_number(const char *s, double *out, const char **endp);`
  - `cl_is_length_unit` (function, line 253) `int cl_is_length_unit(const char *unit, size_t unit_len);`
  - `FREEDOM_CSS_LENGTH_H` (macro, line 2) `#define FREEDOM_CSS_LENGTH_H`
  - `CL_MAX_TOKEN` (macro, line 33) `#define CL_MAX_TOKEN`
  - `CL_INITIAL_FONT_SIZE` (macro, line 39) `#define CL_INITIAL_FONT_SIZE`
  - `CL_NORMAL_LINE_RATIO` (macro, line 45) `#define CL_NORMAL_LINE_RATIO`
  - `CL_FALLBACK_EX_RATIO` (macro, line 57) `#define CL_FALLBACK_EX_RATIO`
  - `CL_FALLBACK_CH_RATIO` (macro, line 64) `#define CL_FALLBACK_CH_RATIO`
  - `CL_FALLBACK_CAP_RATIO` (macro, line 65) `#define CL_FALLBACK_CAP_RATIO`
  - `CL_FALLBACK_IC_RATIO` (macro, line 66) `#define CL_FALLBACK_IC_RATIO`
- Imported by: `src/css.c`, `src/css_box.c`, `src/css_gradient.c`, `src/css_length.c`, `src/css_mq.c`, `src/css_text.c`, `src/css_values.c`, `src/page_view.c`, `tests/test_css_length.c`

## include/css_mask.h
- Doc: CSS Masking 1, alpha gradients only (spec/css_mask.md).
- Layer: utility
- Language: h
- Symbols:
  - `cm_layer` (struct, line 19)
  - `cm_comp` (enum, line 14)
  - `cm_clip` (enum, line 15)
  - `kind` (type_alias, line 19) `typedef struct cm_layer { int kind;`
  - `cm_is_mask_prop` (function, line 28) `int cm_is_mask_prop(const char *prop);`
  - `malformed` (function, line 31) `* the value is unsupported or malformed (the caller drops the declaration). */ int cm_expand(const char *prop, const...`
  - `cm_encode_layer` (function, line 35) `void cm_encode_layer(const cm_layer *l, int *meta, int *alphas, int *poss);`
  - `cm_decode_layer` (function, line 36) `void cm_decode_layer(int meta, int alphas, int poss, cm_layer *out);`
  - `FREEDOM_CSS_MASK_H` (macro, line 2) `#define FREEDOM_CSS_MASK_H`
  - `CM_LAYERS` (macro, line 12) `#define CM_LAYERS`
- Depends on: `include/css_decl.h`
- Imported by: `gui/browser_ui.c`, `src/css.c`, `src/css_mask.c`, `tests/test_css_mask.c`

## include/css_mq.h
- Doc: cmq_container: @container condition s[0,len) (optionally led by a container name) is SURELY true...
- Layer: utility
- Language: h
- Symbols:
  - `cmq_env` (struct, line 19)
  - `cmq_container` (struct, line 41)
  - `width_px` (type_alias, line 18) `typedef struct cmq_env { int width_px;`
  - `names` (type_alias, line 41) `typedef struct cmq_container { unsigned names[CMQ_CONTAINER_NAMES];`
  - `cmq_matches` (function, line 28) `int cmq_matches(const char *s, size_t len, const cmq_env *env);`
  - `cmq_container_surely` (function, line 34) `int cmq_container_surely(const char *s, size_t len, int max_width);`
  - `cmq_name_hash` (function, line 50) `unsigned cmq_name_hash(const char *s, size_t n);`
  - `cmq_container_decl` (function, line 63) `int cmq_container_decl(const char *prop, const char *val, int *type, unsigned names[CMQ_CONTAINER_NAMES], int...`
  - `FREEDOM_CSS_MQ_H` (macro, line 2) `#define FREEDOM_CSS_MQ_H`
  - `CMQ_MAX_DEPTH` (macro, line 16) `#define CMQ_MAX_DEPTH`
  - `CMQ_TOK_MAX` (macro, line 17) `#define CMQ_TOK_MAX`
  - `CMQ_CONTAINER_NAMES` (macro, line 37) `#define CMQ_CONTAINER_NAMES`
- Imported by: `fuzz/fuzz_css.c`, `include/css.h`, `src/css.c`, `src/css_mq.c`, `tests/test_css_mq.c`

## include/css_select.h
- Doc: css_attr_match: Sub-selector for :not()/:is()/:where(): a simple compound with only...
- Layer: utility
- Language: h
- Symbols:
  - `css_attr_match` (struct, line 89)
  - `css_sub_sel` (struct, line 96)
  - `css_pseudo_match` (struct, line 113)
  - `css_compound` (struct, line 123)
  - `css_sel` (struct, line 140)
  - `name` (type_alias, line 89) `typedef struct css_attr_match { char name[CSS_TOK_MAX];`
  - `tag` (type_alias, line 95) `typedef struct css_sub_sel { char tag[CSS_TOK_MAX];`
  - `kind` (type_alias, line 113) `typedef struct css_pseudo_match { int kind;`
  - `tag` (type_alias, line 123) `typedef struct css_compound { char tag[CSS_TOK_MAX];`
  - `comb` (type_alias, line 140) `typedef struct css_sel { int comb[CSS_MAX_COMPOUNDS];`
  - `csel_anc_reject` (function, line 196) `static inline int csel_anc_reject(const css_sel *sel, const css_element *el)`
  - `csel_lower_ch` (function, line 241) `static inline char csel_lower_ch(char c)`
  - `csel_ci_eq` (function, line 245) `static inline int csel_ci_eq(const char *a, const char *b)`
  - `csel_ci_starts` (function, line 254) `static inline int csel_ci_starts(const char *a, const char *p)`
  - `csel_span_eq` (function, line 263) `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)`
  - `csel_substr` (function, line 274) `static inline int csel_substr(const char *hay, const char *needle, int ci)`
  - `csel_ident_ch` (function, line 282) `static inline int csel_ident_ch(char c)`
  - `csel_compact_size` (function, line 169) `size_t csel_compact_size(int nparts);`
  - `csel_compact_dup` (function, line 174) `css_sel *csel_compact_dup(const css_sel *sel);`
  - `csel_parse` (function, line 178) `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel);`
  - `csel_matches` (function, line 187) `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id, int allow_pseudo_el, int...`
  - `csel_element_feature_bits` (function, line 195) `unsigned long long csel_element_feature_bits(const css_element *e);`
  - `conservative` (function, line 203) `* Pure and conservative (anything unrecognised answers 1). A selector that answers 0 matches * from the element's...`
  - `identifier` (function, line 209) `* A selector identifier (tag, .class, #id) is read with CSS escapes decoded * (`.md\:flex` is the class "md:flex")...`
  - `csel_emit_utf8` (function, line 221) `size_t csel_emit_utf8(unsigned int cp, char *out);`
  - `csel_unescape` (function, line 223) `void csel_unescape(char *dst, size_t cap, const char *src, size_t n);`
  - `csel_escape_len` (function, line 225) `size_t csel_escape_len(const char *s, size_t i, size_t b);`
  - `csel_ident_fold` (function, line 227) `void csel_ident_fold(const char *src, size_t len, char *dst);`
  - `csel_ident_eq` (function, line 229) `int csel_ident_eq(const char *stored, const char *tok, size_t tlen);`
  - `csel_read_ident` (function, line 232) `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower);`
  - `csel_decl_end` (function, line 237) `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace);`
  - `FREEDOM_CSS_SELECT_H` (macro, line 2) `#define FREEDOM_CSS_SELECT_H`
  - `CSS_TOK_MAX` (macro, line 27) `#define CSS_TOK_MAX`
  - `CSS_MAX_CLASSES_PER_SEL` (macro, line 28) `#define CSS_MAX_CLASSES_PER_SEL`
  - `CSS_MAX_SUB_SELS` (macro, line 84) `#define CSS_MAX_SUB_SELS`
  - `CSS_SUB_MAX_ATTRS` (macro, line 85) `#define CSS_SUB_MAX_ATTRS`
  - `CSS_SUB_MAX_PSEUDOS` (macro, line 86) `#define CSS_SUB_MAX_PSEUDOS`
  - `CSEL_FOLD_PREFIX` (macro, line 216) `#define CSEL_FOLD_PREFIX`
  - `CSEL_FOLD_MARK` (macro, line 217) `#define CSEL_FOLD_MARK`
  - `CSEL_IDENT_SCRATCH` (macro, line 218) `#define CSEL_IDENT_SCRATCH`
- Depends on: `include/css.h`
- Imported by: `fuzz/fuzz_css.c`, `include/css_chain.h`, `include/css_decl.h`, `include/css_index.h`, `src/css.c`, `src/css_atrule.c`, `src/css_box.c`, `src/css_chain.c`, `src/css_gradient.c`, `src/css_select.c`, `src/css_text.c`, `src/css_values.c`, `src/css_vars.c`, `src/dom.c`, `src/sheet_cache.c`, `tests/test_css.c`

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
  - `cv_filter_scale` (function, line 20) `double cv_filter_scale(int pct);`
  - `cv_parse_color_t7` (function, line 24) `int cv_parse_color_t7(const char *v);`
  - `black` (function, line 27) `* transparent black (127 << 24) -- text that paints nothing, not an absent * value. CC_COLOR_CURRENT and -1...`
  - `cv_interp_bg` (function, line 30) `int cv_interp_bg(const char *v);`
  - `FREEDOM_CSS_VALUES_H` (macro, line 2) `#define FREEDOM_CSS_VALUES_H`
- Imported by: `gui/browser_ui.c`, `src/css.c`, `src/css_box.c`, `src/css_gradient.c`, `src/css_text.c`, `src/css_values.c`, `tests/test_css_values.c`

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
  - `worker` (function, line 59) `* the confined worker (du_decode). */ du_status du_shape_ok(const char *url);`
  - `closed` (function, line 65) `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/out/out_len == NULL (with b64_len !=...`
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
- Imported by: `src/disk_store.c`, `src/http_cache.c`, `src/profile.c`, `tests/test_disk_store.c`

## include/doc_title.h
- Doc: doc_title -- the <title> of a received document that has not been laid out yet
- Layer: utility
- Language: h
- Symbols:
  - `dt_scan` (function, line 20) `int dt_scan(const char *html, size_t len, char *out, size_t cap);`
  - `FREEDOM_DOC_TITLE_H` (macro, line 5) `#define FREEDOM_DOC_TITLE_H`
  - `DT_SCAN_MAX` (macro, line 14) `#define DT_SCAN_MAX`
- Imported by: `fuzz/fuzz_doc_title.c`, `gui/browser_ui.c`, `src/doc_title.c`, `tests/test_doc_title.c`

## include/dom.h
- Doc: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: *...
- Layer: utility
- Language: h
- Symbols:
  - `dom_status` (enum, line 26)
  - `dom_place` (enum, line 198)
  - `dom_node_id` (type_alias, line 34) `typedef uint32_t dom_node_id;`
  - `dom_index` (type_alias, line 40) `typedef struct dom_index dom_index;`
  - `dom_free` (function, line 48) `void dom_free(dom_index *idx);`
  - `dom_node_count` (function, line 51) `size_t dom_node_count(const dom_index *idx);`
  - `tree` (function, line 59) `* tree (the index only grows, so a node a script removed is still registered and must not be * found);`
  - `dom_is_connected` (function, line 65) `int dom_is_connected(const dom_index *idx, dom_node_id node);`
  - `count` (function, line 68) `* match count (which may exceed cap, so the caller can size a buffer). */ size_t dom_get_by_tag(const dom_index...`
  - `dom_get_by_class` (function, line 71) `size_t dom_get_by_class(const dom_index *idx, const char *cls, dom_node_id *out, size_t cap);`
  - `dom_matches` (function, line 100) `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector);`
  - `dom_document_position` (function, line 110) `size_t dom_document_position(const dom_index *idx, dom_node_id node);`
  - `dom_precedes` (function, line 113) `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);`
  - `dom_tag_name` (function, line 127) `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);`
  - `dom_get_attribute` (function, line 130) `const char *dom_get_attribute(const dom_index *idx, dom_node_id node, const char *name, size_t *len);`
  - `dom_attribute_names` (function, line 137) `size_t dom_attribute_names(const dom_index *idx, dom_node_id node, const char **names, size_t *lens, size_t cap);`
  - `dom_text_content` (function, line 142) `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len);`
  - `dom_document_title` (function, line 145) `const char *dom_document_title(const dom_index *idx, size_t *len);`
  - `valid` (function, line 150) `* detached node stays valid (it just becomes unreachable from the root and is no * longer rendered). These never...`
  - `cycle` (function, line 180) `* Rejects a cycle (child being an ancestor of parent). Invalid handle / self / cycle * => DOM_ERR_NULL_ARG. */...`
  - `parent` (function, line 207) `* child of parent (for the *_REF places) or an invalid handle => DOM_ERR_NULL_ARG. */ dom_status...`
  - `dom_node_kind` (function, line 223) `int dom_node_kind(const dom_index *idx, dom_node_id node);`
  - `index` (function, line 239) `* stays valid in the index (not freed). Invalid handle / not-a-child => DOM_ERR_NULL_ARG. */ dom_status...`
  - `length` (function, line 264) `* length (no children => an owned empty string). Uses a chain of fixed-size * blocks internally so there is no hard...`
  - `process` (function, line 271) `* modules in the same process (style resolution). NULL for a bad or non-element * handle. Valid until the next...`
  - `sight` (function, line 276) `* first sight (an innerHTML subtree has no handles until something asks). Registration * is not a tree change...`
  - `FREEDOM_DOM_H` (macro, line 2) `#define FREEDOM_DOM_H`
  - `DOM_NODE_NONE` (macro, line 37) `#define DOM_NODE_NONE`
  - `DOM_KIND_NONE` (macro, line 214) `#define DOM_KIND_NONE`
  - `DOM_KIND_ELEMENT` (macro, line 215) `#define DOM_KIND_ELEMENT`
  - `DOM_KIND_TEXT` (macro, line 216) `#define DOM_KIND_TEXT`
  - `DOM_KIND_COMMENT` (macro, line 217) `#define DOM_KIND_COMMENT`
  - `DOM_MAX_HANDLES` (macro, line 220) `#define DOM_MAX_HANDLES`
- Depends on: `include/html_parse.h`
- Imported by: `fuzz/fuzz_anchor.c`, `fuzz/fuzz_dom.c`, `fuzz/fuzz_js_dom.c`, `include/anchor.h`, `include/js_dom.h`, `include/js_geom.h`, `include/page_view.h`, `src/dom.c`, `src/html_parse.c`, `src/js_dom.c`, `src/js_dom_internal.h`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/page_view.c`, `src/tab.c`, `tests/test_anchor.c`, `tests/test_dom.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_js_native.c`, `tests/test_page_view.c`

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

## include/exact_key.h
- Doc: exact_key (ek_) -- a cache key built by OBSERVING every input of what is cached, compared
- Layer: utility
- Language: h
- Symbols:
  - `ek_key` (struct, line 17)
  - `ek_init` (function, line 24) `void ek_init(ek_key *k);`
  - `ek_reset` (function, line 27) `void ek_reset(ek_key *k);`
  - `ek_put` (function, line 31) `void ek_put(ek_key *k, const void *p, size_t len);`
  - `ek_equal` (function, line 34) `int ek_equal(const ek_key *a, const ek_key *b);`
  - `ek_swap` (function, line 37) `void ek_swap(ek_key *a, ek_key *b);`
  - `ek_free` (function, line 40) `void ek_free(ek_key *k);`
  - `FREEDOM_EXACT_KEY_H` (macro, line 2) `#define FREEDOM_EXACT_KEY_H`
  - `EK_MAX_BYTES` (macro, line 15) `#define EK_MAX_BYTES`
- Imported by: `fuzz/fuzz_exact_key.c`, `gui/browser_ui.c`, `src/exact_key.c`, `tests/test_exact_key.c`

## include/fb_cmdline.h
- Doc: fbc_history_push: #define FBC_BASE_MAX   256    /* bytes of a completion base path #define...
- Layer: utility
- Language: h
- Symbols:
  - `fbc_history` (struct, line 20)
  - `fbc_filter` (enum, line 54)
  - `fbc_history_init` (function, line 27) `void fbc_history_init(fbc_history *h);`
  - `fbc_history_free` (function, line 28) `void fbc_history_free(fbc_history *h);`
  - `fbc_history_push` (function, line 31) `int fbc_history_push(fbc_history *h, const char *text, size_t len);`
  - `fbc_history_prev` (function, line 35) `const char *fbc_history_prev(fbc_history *h, const char *cur, size_t curlen);`
  - `fbc_history_next` (function, line 38) `const char *fbc_history_next(fbc_history *h);`
  - `fbc_complete_split` (function, line 42) `long fbc_complete_split(const char *text, size_t n, char *base, size_t cap, size_t *prefix_off);`
  - `fbc_names_expr` (function, line 46) `size_t fbc_names_expr(const char *base, char *out, size_t cap);`
  - `fbc_complete_pick` (function, line 51) `size_t fbc_complete_pick(const char *names, const char *prefix, size_t plen, char *ins, size_t ins_cap, char *list...`
  - `fbc_filter_passes` (function, line 62) `int fbc_filter_passes(int filter, int level);`
  - `fbc_filter_next` (function, line 63) `int fbc_filter_next(int filter);`
  - `fbc_filter_label` (function, line 64) `const char *fbc_filter_label(int filter);`
  - `FREEDOM_FB_CMDLINE_H` (macro, line 2) `#define FREEDOM_FB_CMDLINE_H`
  - `FBC_HIST_MAX` (macro, line 15) `#define FBC_HIST_MAX`
  - `FBC_ENTRY_MAX` (macro, line 16) `#define FBC_ENTRY_MAX`
  - `FBC_BASE_MAX` (macro, line 17) `#define FBC_BASE_MAX`
  - `FBC_LIST_NAMES` (macro, line 18) `#define FBC_LIST_NAMES`
- Imported by: `fuzz/fuzz_fb_cmdline.c`, `gui/browser_ui.c`, `src/fb_cmdline.c`, `tests/test_fb_cmdline.c`, `tests/test_js_dom.c`


Next: [KB_include_p3.md](KB_include_p3.md)
