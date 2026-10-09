# Subsystem: src (page 2 of 7)
Previous: [KB_src.md](KB_src.md)

## src/css_box.c
- Doc: calc_val: `pct` is the percentage component, carried through the arithmetic exactly like `em`...
- Layer: utility
- Language: c
- Symbols:
  - `calc_val` (struct, line 479)
  - `calc_parser` (struct, line 480)
  - `px` (type_alias, line 479) `typedef struct calc_val { double px;`
  - `cb_parse_num` (function, line 13) `static int cb_parse_num(const char *s, double *out, const char **endp)`
  - `cb_wide_keyword` (function, line 18) `static int cb_wide_keyword(const char *v)`
  - `cb_copy_trim` (function, line 25) `static size_t cb_copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)`
  - `cb_length_px` (function, line 49) `int cb_length_px(const char *v, double *px)`
  - `cb_interp_align` (function, line 54) `int cb_interp_align(const char *v)`
  - `cb_interp_lineheight` (function, line 116) `int cb_interp_lineheight(const char *v)`
  - `cb_interp_weight` (function, line 137) `int cb_interp_weight(const char *v)`
  - `cb_interp_style` (function, line 146) `int cb_interp_style(const char *v)`
  - `cb_interp_textdeco` (function, line 156) `int cb_interp_textdeco(const char *v)`
  - `cb_interp_display` (function, line 176) `int cb_interp_display(const char *v)`
  - `cb_interp_gap` (function, line 251) `int cb_interp_gap(const char *v)`
  - `cb_interp_justify` (function, line 258) `int cb_interp_justify(const char *v)`
  - `cb_starts_with_ci` (function, line 283) `static int cb_starts_with_ci(const char *s, const char *pre)`
  - `count_tracks` (function, line 289) `static int count_tracks(const char *s, size_t n)`
  - `track_size_of` (function, line 297) `static int track_size_of(const char *tok)`
  - `count_one_repeat` (function, line 327) `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,
                      ...`
  - `walk_tracks` (function, line 370) `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)`
  - `cb_expand_grid_template_cols` (function, line 430) `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap)`
  - `calc_skip_ws` (function, line 482) `static void calc_skip_ws(calc_parser *p)`
  - `calc_match_fn` (function, line 489) `static int calc_match_fn(calc_parser *p, const char *name)`
  - `calc_piecewise` (function, line 516) `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)`
  - `calc_mathfn` (function, line 531) `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)`
  - `calc_term` (function, line 652) `static int calc_term(calc_parser *p, calc_val *out, int depth)`
  - `calc_expr` (function, line 676) `static int calc_expr(calc_parser *p, calc_val *out, int depth)`
  - `calc_eval_full` (function, line 695) `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,
           ...`
  - `calc_eval` (function, line 711) `static int calc_eval(const char *v, size_t vlen, double *out_px)`
  - `calc_eval_em` (function, line 718) `static int calc_eval_em(const char *v, size_t vlen, double *out_em)`
  - `calc_unwrap` (function, line 726) `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)`
  - `cb_interp_len` (function, line 744) `int cb_interp_len(const char *v, int allow_auto, int *out)`
  - `pct_slot_of` (function, line 789) `static int pct_slot_of(int slot)`
  - `cb_value_em_milli` (function, line 839) `int cb_value_em_milli(const char *v)`
  - `cb_interp_lp` (function, line 859) `int cb_interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_px, ...`
  - `interp_len` (function, line 1035) `* this file that might hand a token to interp_len (transitively: margin/padding/
 * inset, flex-b...`
  - `cb_expand_box2` (function, line 1106) `int cb_expand_box2(const char *val, int slot_start, int slot_end,
                       int allo...`
  - `repeat` (function, line 272) `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill|...) /...`
  - `accepts` (function, line 452) `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further...`
  - `min` (function, line 550) `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the...`
  - `term` (function, line 866) `* the same expression and failed closed on the percentage term (its property * may not accept one);`
  - `CSS_CALC_MAX_DEPTH` (macro, line 460) `#define CSS_CALC_MAX_DEPTH`
  - `CSS_MATHFN_MAX_ARGS` (macro, line 464) `#define CSS_MATHFN_MAX_ARGS`
  - `AUTO_REJECT` (macro, line 932) `#define AUTO_REJECT`
  - `AUTO_VALUE` (macro, line 933) `#define AUTO_VALUE`
  - `AUTO_RESET` (macro, line 934) `#define AUTO_RESET`
  - `AUTO_RESET_NONE` (macro, line 938) `#define AUTO_RESET_NONE`
- Depends on: `include/css.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`

## src/css_chain.c
- Doc: cch_node: One element's selector inputs (tag/id/classes) plus its css_element view, with *...
- Layer: utility
- Language: c
- Symbols:
  - `cch_node` (struct, line 23)
  - `tag` (type_alias, line 23) `typedef struct cch_node { char tag[CCH_TAG_MAX];`
  - `fill_css_node` (function, line 35) `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)`
  - `sibling_position` (function, line 133) `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)`
  - `sibling_type_position` (function, line 151) `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)`
  - `count_children` (function, line 179) `static int count_children(lxb_dom_node_t *n)`
  - `inputs` (function, line 193) `* identical inputs (single source of truth). */
static const css_element *build_chain(lxb_dom_ele...`
  - `cch_element_style_vars` (function, line 246) `css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,
                 ...`
  - `cch_pseudo_style` (function, line 273) `css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,
            ...`
  - `cch_element_style` (function, line 288) `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)`
  - `cch_element_matches` (function, line 292) `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)`
  - `CCH_TAG_MAX` (macro, line 14) `#define CCH_TAG_MAX`
  - `CCH_ID_MAX` (macro, line 15) `#define CCH_ID_MAX`
  - `CCH_CLASS_BUF` (macro, line 16) `#define CCH_CLASS_BUF`
  - `CCH_MAX_CLASSES` (macro, line 17) `#define CCH_MAX_CLASSES`
  - `CCH_MAX_ATTRS` (macro, line 18) `#define CCH_MAX_ATTRS`
  - `CCH_ATTR_BUF` (macro, line 19) `#define CCH_ATTR_BUF`
- Depends on: `include/css_chain.h`, `include/css_select.h`

## src/css_color.c
- Doc: normalize: Trims surrounding ASCII spaces and lowercases into out (CC_TOKEN_MAX bytes). *...
- Layer: utility
- Language: c
- Symbols:
  - `cc_named` (struct, line 33)
  - `ascii_lower` (function, line 118) `static int ascii_lower(int c)`
  - `hex_val` (function, line 122) `static int hex_val(int c)`
  - `normalize` (function, line 131) `static int normalize(const char *token, char *out)`
  - `parse_hex` (function, line 145) `static int parse_hex(const char *s, cc_rgb *out)`
  - `cc_round` (function, line 215) `static long cc_round(double v)`
  - `parse_component` (function, line 220) `static int parse_component(const char *b, const char *e, int is_alpha, int *out)`
  - `parse_hsl_comp` (function, line 253) `static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out)`
  - `span` (function, line 325) `* span (when a slash is present) into ab/ae, and returns the component count,
 * or -1. Bounded: ...`
  - `parse_func` (function, line 397) `static int parse_func(const char *s, cc_rgb *out)`
  - `lab_comp` (function, line 467) `static int lab_comp(const char *b, const char *e, double pct_ref, int is_hue, double *out)`
  - `srgb_encode` (function, line 495) `static unsigned char srgb_encode(double lin)`
  - `oklab_to_rgb` (function, line 502) `static void oklab_to_rgb(double L, double a, double b, cc_rgb *out)`
  - `lab_to_rgb` (function, line 513) `static void lab_to_rgb(double L, double a, double b, cc_rgb *out)`
  - `parse_lab_family` (function, line 529) `static int parse_lab_family(const char *s, cc_rgb *out)`
  - `named_cmp` (function, line 567) `static int named_cmp(const void *key, const void *element)`
  - `parse_named` (function, line 573) `static int parse_named(const char *s, cc_rgb *out)`
  - `cc_parse` (function, line 583) `cc_status cc_parse(const char *token, cc_rgb *out)`
  - `strncmp` (function, line 598) `strncmp(buf, "oklab(", 6) == 0 || strncmp(buf, "oklch(", 6) == 0)`
  - `cc_pack` (function, line 623) `int cc_pack(cc_rgb c)`
  - `cc_unpack` (function, line 627) `cc_rgb cc_unpack(int packed)`
  - `CC_TOKEN_MAX` (macro, line 19) `#define CC_TOKEN_MAX`
  - `CC_CHANNEL_MAX` (macro, line 22) `#define CC_CHANNEL_MAX`
  - `CC_PERCENT_MAX` (macro, line 23) `#define CC_PERCENT_MAX`
  - `CC_NUMBER_MAX_DIGITS` (macro, line 28) `#define CC_NUMBER_MAX_DIGITS`
  - `CC_HSL_SCALE` (macro, line 31) `#define CC_HSL_SCALE`
  - `CC_PI` (macro, line 463) `#define CC_PI`
- Depends on: `include/css_color.h`

## src/css_gradient.c
- Doc: find_gradient_call: Locates a gradient function call `fn` (e.g. "linear-gradient(") in v...
- Layer: utility
- Language: c
- Symbols:
  - `cg_parse_num` (function, line 12) `static int cg_parse_num(const char *s, double *out, const char **endp)`
  - `cg_wide_keyword` (function, line 17) `static int cg_wide_keyword(const char *v)`
  - `gradient` (function, line 27) `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,
 * the whole decl...`
  - `find_gradient_call` (function, line 76) `static int find_gradient_call(const char *v, const char *fn, size_t *start,
                     ...`
  - `conic_prelude` (function, line 110) `static int conic_prelude(const char *seg, int *angle)`
  - `grad_stop_pos` (function, line 152) `static int grad_stop_pos(const char *pp, int conic, const char **endp)`
  - `CSS_GRAD_STOPS_MAX` (function, line 183) `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when
 * the gradient fai...`
  - `emit_gradient` (function, line 290) `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,
                         ...`
  - `find_radial_gradient` (function, line 347) `static int find_radial_gradient(const char *v, size_t *start, size_t *end,
                      ...`
  - `downstream` (function, line 392) `* happens downstream (render_doc.c), gated by caps.images like an <img>. */
int cg_expand_bg_imag...`
  - `bg_layer_tokens_ok` (function, line 458) `static int bg_layer_tokens_ok(const char *s)`
  - `cg_expand_background` (function, line 498) `int cg_expand_background(const char *val, css_decl *dst, int cap,
                             ch...`
  - `pool` (function, line 388) `* pool (gradient explicitly reset);`
  - `declaration` (function, line 451) `* declaration (fail closed);`
- Depends on: `include/css_color.h`, `include/css_decl.h`, `include/css_gradient.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`

## src/css_length.c
- Doc: cl_unit_eq: ASCII case-insensitive compare of a possibly-unterminated unit slice against a...
- Layer: utility
- Language: c
- Symbols:
  - `know` (function, line 7) `* this module cannot know (real font metrics, the viewport) arrives through
 * cl_ctx rather than...`
  - `cl_unit_eq` (function, line 30) `static int cl_unit_eq(const char *unit, size_t len, const char *lit)`
  - `cl_font_size` (function, line 56) `static double cl_font_size(const cl_ctx *ctx)`
  - `cl_root_font_size` (function, line 60) `static double cl_root_font_size(const cl_ctx *ctx)`
  - `cl_metric_or` (function, line 67) `static double cl_metric_or(double measured, double ratio, const cl_ctx *ctx)`
  - `cl_viewport_scale` (function, line 80) `static int cl_viewport_scale(const char *u, size_t len, const cl_ctx *ctx, double *per)`
  - `cl_ctx_initial` (function, line 100) `cl_ctx cl_ctx_initial(void)`
  - `cl_unit_scale` (function, line 117) `cl_status cl_unit_scale(const char *unit, size_t unit_len,
                        const cl_ctx *...`
  - `cl_is_length_unit` (function, line 167) `int cl_is_length_unit(const char *unit, size_t unit_len)`
  - `cl_unit_is_font_relative` (function, line 174) `int cl_unit_is_font_relative(const char *unit, size_t unit_len)`
  - `cl_em_refit` (function, line 219) `double cl_em_refit(double px, double em, double from_font_size, double font_size)`
  - `cl_parse_number` (function, line 233) `static int cl_parse_number(const char **pp, const char *end, double *out)`
  - `cl_number` (function, line 292) `int cl_number(const char *s, double *out, const char **endp)`
  - `cl_resolve_core` (function, line 309) `static cl_status cl_resolve_core(const char *value, const cl_ctx *ctx, cl_lp *out)`
  - `cl_resolve` (function, line 377) `cl_status cl_resolve(const char *value, const cl_ctx *ctx, double *out_px)`
  - `cl_resolve_lp` (function, line 391) `cl_status cl_resolve_lp(const char *value, const cl_ctx *ctx, cl_lp *out)`
  - `cl_lp_used` (function, line 395) `double cl_lp_used(cl_lp lp, double basis)`
  - `CL_PX_PER_IN` (macro, line 21) `#define CL_PX_PER_IN`
- Depends on: `include/css.h`, `include/css_length.h`

## src/css_mq.c
- Doc: read_word: static int is_space(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'...
- Layer: utility
- Language: c
- Symbols:
  - `mq_cur` (struct, line 25)
  - `fval` (struct, line 96)
  - `kind` (type_alias, line 95) `typedef struct fval { fv_kind kind;`
  - `lower_ch` (function, line 31) `static char lower_ch(char c)`
  - `is_space` (function, line 35) `static int is_space(char c)`
  - `is_ident_ch` (function, line 39) `static int is_ident_ch(char c)`
  - `skip_ws` (function, line 44) `static void skip_ws(mq_cur *c)`
  - `read_word` (function, line 49) `static int read_word(mq_cur *c, char *w, size_t cap)`
  - `peek_word` (function, line 61) `static int peek_word(const mq_cur *c, char *w, size_t cap)`
  - `and3` (function, line 66) `static int and3(int a, int b)`
  - `or3` (function, line 72) `static int or3(int a, int b)`
  - `not3` (function, line 78) `static int not3(int a)`
  - `copy_trim_lower` (function, line 83) `static int copy_trim_lower(const char *s, size_t a, size_t b, char *dst, size_t cap)`
  - `feature_of` (function, line 106) `static fval feature_of(const char *name, const cmq_env *env)`
  - `read_num` (function, line 162) `static int read_num(const char *t, double *out, const char **end)`
  - `parse_value` (function, line 167) `static int parse_value(const char *t, int unit, double *out)`
  - `cmp_op` (function, line 206) `static int cmp_op(double lhs, int op, double rhs)`
  - `flip_op` (function, line 218) `static int flip_op(int op)`
  - `bool_ctx` (function, line 229) `static int bool_ctx(const fval *v)`
  - `eval_plain` (function, line 237) `static int eval_plain(const char *name, const char *value, const cmq_env *env)`
  - `read_op` (function, line 266) `static int read_op(const char **p)`
  - `eval_range` (function, line 280) `static int eval_range(const char *t, const cmq_env *env)`
  - `eval_feature` (function, line 328) `static int eval_feature(const char *s, size_t a, size_t b, const cmq_env *env)`
  - `eval_in_parens` (function, line 353) `static int eval_in_parens(mq_cur *c, int depth)`
  - `eval_cond` (function, line 380) `static int eval_cond(mq_cur *c, int depth)`
  - `eval_query` (function, line 404) `static int eval_query(const char *s, size_t a, size_t b, const cmq_env *env)`
  - `cmq_matches` (function, line 458) `int cmq_matches(const char *s, size_t len, const cmq_env *env)`
  - `CMQ_DEVICE_W` (macro, line 18) `#define CMQ_DEVICE_W`
  - `CMQ_DEVICE_H` (macro, line 19) `#define CMQ_DEVICE_H`
  - `CMQ_DPPX` (macro, line 20) `#define CMQ_DPPX`
  - `CMQ_COLOR_BITS` (macro, line 21) `#define CMQ_COLOR_BITS`
  - `CMQ_DPI_PER_DPPX` (macro, line 22) `#define CMQ_DPI_PER_DPPX`
  - `CMQ_CM_PER_IN` (macro, line 23) `#define CMQ_CM_PER_IN`
  - `MQ_EPS` (macro, line 203) `#define MQ_EPS`
- Depends on: `include/css_length.h`, `include/css_mq.h`

## src/css_select.c
- Doc: csel_hex_val: CSS Syntax 4.3.7 escape consumption (moved from css.c; shared by quoted content...
- Layer: utility
- Language: c
- Symbols:
  - `csel_hex_val` (function, line 23) `int csel_hex_val(char c)`
  - `csel_emit_utf8` (function, line 30) `size_t csel_emit_utf8(unsigned int cp, char *out)`
  - `csel_unescape` (function, line 52) `void csel_unescape(char *dst, size_t cap, const char *src, size_t n)`
  - `csel_escape_len` (function, line 91) `size_t csel_escape_len(const char *s, size_t i, size_t b)`
  - `csel_decl_end` (function, line 104) `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace)`
  - `ident_hash` (function, line 121) `static unsigned long long ident_hash(const char *s, size_t n)`
  - `csel_ident_fold` (function, line 127) `void csel_ident_fold(const char *src, size_t len, char *dst)`
  - `csel_ident_eq` (function, line 142) `int csel_ident_eq(const char *stored, const char *tok, size_t tlen)`
  - `csel_read_ident` (function, line 150) `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower)`
  - `parse_attr_sel` (function, line 184) `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)`
  - `parse_nth_arg` (function, line 241) `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)`
  - `simple_pseudo_kind` (function, line 431) `static int simple_pseudo_kind(const char *nm)`
  - `parse_sub_compound` (function, line 452) `static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub)`
  - `parse_compound` (function, line 517) `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,
                  ...`
  - `selector` (function, line 559) `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is
 * dropped. Whitespa...`
  - `el_attr_value` (function, line 655) `static const char *el_attr_value(const css_element *el, const char *name)`
  - `ends_with` (function, line 665) `static int ends_with(const char *v, const char *suf, int ci)`
  - `has_word` (function, line 673) `static int has_word(const char *v, const char *w, int ci)`
  - `attr_matches` (function, line 688) `static int attr_matches(const css_attr_match *am, const css_element *el)`
  - `nth_matches` (function, line 708) `static int nth_matches(int A, int B, int idx)`
  - `is_form_control` (function, line 717) `static int is_form_control(const char *tag)`
  - `sub_sel_matches` (function, line 730) `static int sub_sel_matches(const css_sub_sel *sub, const css_element *el)`
  - `compound_matches` (function, line 979) `static int compound_matches(const css_compound *c, const css_element *el,
                       ...`
  - `built` (function, line 1014) `* chains the caller built (an element without parent/prev links never matches
 * through that com...`
  - `csel_matches` (function, line 1055) `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,
              ...`
  - `take_sub_arg` (function, line 293) `static int take_sub_arg(const char *s, size_t a, size_t b, css_sel *sel, int strict);`
  - `between` (function, line 376) `* between ( and ) is split on commas (not inside [] or ());`
  - `pseudo_matches` (function, line 726) `static int pseudo_matches(const css_pseudo_match *pm, const css_element *el, const css_sel *sel, const char...`
  - `HAS_MAX_DEPTH` (macro, line 839) `#define HAS_MAX_DEPTH`
- Depends on: `include/css_select.h`

## src/css_text.c
- Doc: --- text-presentation extensions (Hito 23b-6) ---
- Layer: utility
- Language: c
- Symbols:
  - `ct_family_of` (function, line 18) `static int ct_family_of(const char *name)`
  - `ct_interp_fontfamily` (function, line 47) `int ct_interp_fontfamily(const char *v)`
  - `ct_interp_texttransform` (function, line 69) `int ct_interp_texttransform(const char *v)`
  - `ct_interp_valign` (function, line 91) `int ct_interp_valign(const char *v)`
  - `ct_expand_valign` (function, line 122) `int ct_expand_valign(const char *val, css_decl *dst, int cap)`
  - `ct_interp_transition_property` (function, line 139) `int ct_interp_transition_property(const char *v)`
  - `ct_interp_whitespace` (function, line 147) `int ct_interp_whitespace(const char *v)`
  - `ct_interp_tabsize` (function, line 160) `int ct_interp_tabsize(const char *v)`
  - `ct_interp_textdeco_style` (function, line 171) `int ct_interp_textdeco_style(const char *v)`
  - `ct_interp_textdeco_thickness` (function, line 182) `int ct_interp_textdeco_thickness(const char *v)`
  - `ct_interp_aspect_ratio` (function, line 194) `int ct_interp_aspect_ratio(const char *v, int *num, int *den)`
  - `ct_interp_direction` (function, line 227) `int ct_interp_direction(const char *v)`
  - `ct_liststyle_kw` (function, line 233) `static int ct_liststyle_kw(const char *t)`
  - `ct_liststyle_unknown_name` (function, line 254) `static int ct_liststyle_unknown_name(const char *t)`
  - `ct_interp_liststyle` (function, line 265) `int ct_interp_liststyle(const char *v)`
  - `ct_emit_spacing` (function, line 300) `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
  - `ct_expand_shadow` (function, line 313) `int ct_expand_shadow(const char *val, css_decl *dst, int cap)`
- Depends on: `include/css.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_text.h`, `include/css_values.h`

## src/css_values.c
- Layer: utility
- Language: c
- Symbols:
  - `cv_parse_num` (function, line 11) `static int cv_parse_num(const char *s, double *out, const char **endp)`
  - `cv_parse_color` (function, line 16) `int cv_parse_color(const char *v)`
  - `cv_interp_color` (function, line 36) `int cv_interp_color(const char *v)`
  - `cv_color_ok` (function, line 41) `int cv_color_ok(int c)`
  - `cv_bg_alpha_of` (function, line 46) `int cv_bg_alpha_of(const char *v)`
  - `cv_interp_bg` (function, line 160) `int cv_interp_bg(const char *v)`
- Depends on: `include/css.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`

## src/css_vars.c
- Doc: find_slot: Index into t->slot where name lives, or the empty slot where it would go. * Requires...
- Layer: utility
- Language: c
- Symbols:
  - `name_hash` (function, line 12) `static size_t name_hash(const char *s, size_t n)`
  - `dup_n` (function, line 21) `static char *dup_n(const char *s, size_t n)`
  - `find_slot` (function, line 32) `static size_t find_slot(const cvr_table *t, const char *name, size_t nlen)`
  - `grow` (function, line 45) `static int grow(cvr_table *t)`
  - `cvr_set` (function, line 67) `int cvr_set(cvr_table *t, const char *name, size_t nlen, const char *value, size_t vlen)`
  - `cvr_get` (function, line 94) `const char *cvr_get(const cvr_table *t, const char *name, size_t nlen)`
  - `cvr_count` (function, line 100) `size_t cvr_count(const cvr_table *t)`
  - `cvr_reset` (function, line 102) `void cvr_reset(cvr_table *t)`
  - `cvr_free` (function, line 112) `void cvr_free(cvr_table *t)`
  - `is_ws` (function, line 120) `static int is_ws(char c)`
  - `without_important` (function, line 124) `static size_t without_important(const char *val, size_t n)`
  - `cvr_collect_decls` (function, line 139) `void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b)`
  - `scope_get` (function, line 164) `static const char *scope_get(const cvr_scope *sc, const char *name, size_t nlen)`
  - `resolve_rec` (function, line 178) `static int resolve_rec(const char *val, size_t vlen, char *out, size_t outcap,
                  ...`
  - `cvr_resolve` (function, line 230) `int cvr_resolve(const char *val, char *out, size_t outcap, const cvr_scope *sc)`
  - `cvr_lookup` (function, line 239) `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen)`
- Depends on: `include/css_select.h`, `include/css_vars.h`

## src/data_url.c
- Doc: b64_val: 0-63 for a base64 alphabet character, -1 otherwise.
- Layer: data_access
- Language: c
- Symbols:
  - `lower` (function, line 16) `static int lower(char c)`
  - `ci_starts_with` (function, line 20) `static int ci_starts_with(const char *s, const char *prefix)`
  - `du_is_data_url` (function, line 28) `int du_is_data_url(const char *url)`
  - `du_base64_payload` (function, line 32) `du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len)`
  - `b64_val` (function, line 61) `static int b64_val(unsigned char c)`
  - `du_base64_decode` (function, line 70) `du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len)`
  - `hexval` (function, line 108) `static int hexval(char c)`
  - `ascii_ws` (function, line 115) `static int ascii_ws(char c)`
  - `ends_ci` (function, line 120) `static int ends_ci(const char *s, size_t n, const char *suf)`
  - `du_decode` (function, line 131) `du_status du_decode(const char *url, char *mime, size_t mime_cap, uint8_t **out, size_t *out_len)`
- Depends on: `include/data_url.h`

## src/disk_store.c
- Doc: fsync_dir: Best-effort fsync of the directory holding path, for crash durability of the * rename.
- Layer: data_access
- Language: c
- Symbols:
  - `fsync_dir` (function, line 32) `static void fsync_dir(const char *path)`
  - `map_ls` (function, line 50) `static ds_status map_ls(ls_status s)`
  - `ds_write` (function, line 66) `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,
               ...`
  - `ds_read` (function, line 103) `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],
                  uint8_t **ou...`
  - `ds_free` (function, line 136) `void ds_free(uint8_t *buf, size_t len)`
  - `_POSIX_C_SOURCE` (macro, line 11) `#define _POSIX_C_SOURCE`
- Depends on: `include/disk_store.h`, `include/local_store.h`, `include/util.h`

## src/dom.c
- Doc: to_lower_buf: #include <stdint.h> #include <stdlib.h> #include <string.h> #include...
- Layer: utility
- Language: c
- Symbols:
  - `sm_entry` (struct, line 55)
  - `strmap` (struct, line 64)
  - `pm_entry` (struct, line 154)
  - `ptrmap` (struct, line 160)
  - `dom_index` (struct, line 220)
  - `ih_block` (struct, line 820)
  - `ih_acc` (struct, line 825)
  - `to_lower_buf` (function, line 33) `static int to_lower_buf(const char *s, size_t n, char *out, size_t outcap)`
  - `ptr_hash` (function, line 45) `static size_t ptr_hash(const void *p)`
  - `sm_entry_append` (function, line 70) `static int sm_entry_append(sm_entry *e, dom_node_id id)`
  - `sm_grow` (function, line 82) `static int sm_grow(strmap *m)`
  - `sm_put` (function, line 99) `static int sm_put(strmap *m, const char *key, size_t klen, dom_node_id id)`
  - `sm_find` (function, line 127) `static const sm_entry *sm_find(const strmap *m, const char *key, size_t klen)`
  - `sm_free` (function, line 139) `static void sm_free(strmap *m)`
  - `pm_grow` (function, line 166) `static int pm_grow(ptrmap *m)`
  - `pm_put` (function, line 183) `static int pm_put(ptrmap *m, const void *key, dom_node_id id)`
  - `pm_get` (function, line 200) `static int pm_get(const ptrmap *m, const void *key, dom_node_id *out)`
  - `pm_free` (function, line 211) `static void pm_free(ptrmap *m)`
  - `node_next` (function, line 232) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)`
  - `valid` (function, line 242) `static int valid(const dom_index *idx, dom_node_id n)`
  - `index_element` (function, line 254) `static int index_element(dom_index *idx, lxb_dom_element_t *el, dom_node_id id)`
  - `dom_build` (function, line 291) `dom_status dom_build(const hp_document *doc, dom_index **out)`
  - `dom_free` (function, line 332) `void dom_free(dom_index *idx)`
  - `dom_node_count` (function, line 344) `size_t dom_node_count(const dom_index *idx)`
  - `dom_get_element_by_id` (function, line 348) `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)`
  - `copy_ids` (function, line 354) `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)`
  - `dom_get_by_tag` (function, line 361) `size_t dom_get_by_tag(const dom_index *idx, const char *tag,
                      dom_node_id *o...`
  - `dom_get_by_class` (function, line 370) `size_t dom_get_by_class(const dom_index *idx, const char *cls,
                        dom_node_i...`
  - `id_of` (function, line 383) `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)`
  - `parse_selector_list` (function, line 393) `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)`
  - `node_matches_any` (function, line 426) `static int node_matches_any(const lxb_dom_node_t *cn,
                            const css_sel *...`
  - `count` (function, line 437) `* count (may exceed cap), and returns DOM_NODE_NONE. */
static dom_node_id qs_walk(const dom_inde...`
  - `dom_query_selector` (function, line 467) `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,
                          ...`
  - `dom_query_selector_all` (function, line 476) `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,
                           ...`
  - `dom_matches` (function, line 487) `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)`
  - `dom_closest` (function, line 496) `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,
                        const cha...`
  - `dom_document_position` (function, line 512) `size_t dom_document_position(const dom_index *idx, dom_node_id node)`
  - `dom_precedes` (function, line 517) `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)`
  - `dom_node_at` (function, line 522) `dom_node_id dom_node_at(const dom_index *idx, size_t position)`
  - `dom_parent` (function, line 527) `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)`
  - `dom_first_child` (function, line 537) `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)`
  - `dom_next_sibling` (function, line 545) `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)`
  - `dom_tag_name` (function, line 553) `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)`
  - `dom_get_attribute` (function, line 564) `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,
                           ...`
  - `dom_attribute_names` (function, line 586) `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,
                           con...`
  - `dom_text_content` (function, line 604) `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)`
  - `dom_document_title` (function, line 614) `const char *dom_document_title(const dom_index *idx, size_t *len)`
  - `dom_set_text_content` (function, line 627) `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,
                               ...`
  - `dom_set_document_title` (function, line 661) `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)`
  - `idx_push` (function, line 672) `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)`
  - `dom_create_element` (function, line 690) `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)`
  - `dom_append_child` (function, line 710) `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
  - `dom_remove_child` (function, line 724) `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
  - `dom_set_attribute` (function, line 732) `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,
                             const...`
  - `dom_remove_attribute` (function, line 761) `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)`
  - `index_subtree` (function, line 770) `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)`
  - `dom_set_inner_html` (function, line 780) `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,
                              con...`
  - `ih_append` (function, line 833) `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)`
  - `ih_free` (function, line 860) `static void ih_free(ih_acc *a)`
  - `dom_get_inner_html` (function, line 887) `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,
                           ...`
  - `dom_insert_before` (function, line 917) `dom_status dom_insert_before(dom_index *idx, dom_node_id parent, dom_node_id child,
             ...`
  - `dom_clone_node` (function, line 934) `dom_status dom_clone_node(dom_index *idx, dom_node_id node, int deep, dom_node_id *out_id)`
  - `dom_move_children` (function, line 948) `dom_status dom_move_children(dom_index *idx, dom_node_id src, dom_node_id parent,
               ...`
  - `char_kind` (function, line 981) `static int char_kind(const lxb_dom_node_t *n)`
  - `handle_of` (function, line 992) `static dom_node_id handle_of(dom_index *idx, lxb_dom_node_t *n)`
  - `dom_node_kind` (function, line 1000) `int dom_node_kind(const dom_index *idx, dom_node_id node)`
  - `dom_child_node` (function, line 1004) `dom_node_id dom_child_node(dom_index *idx, dom_node_id node, int last)`
  - `dom_sibling_node` (function, line 1011) `dom_node_id dom_sibling_node(dom_index *idx, dom_node_id node, int prev)`
  - `dom_create_char_node` (function, line 1018) `dom_status dom_create_char_node(dom_index *idx, int kind, const char *text, size_t len,
         ...`
  - `_POSIX_C_SOURCE` (macro, line 11) `#define _POSIX_C_SOURCE`
  - `DOM_QS_MAX_SELECTORS` (macro, line 380) `#define DOM_QS_MAX_SELECTORS`
  - `IH_BLOCK_SIZE` (macro, line 818) `#define IH_BLOCK_SIZE`
- Depends on: `include/css_chain.h`, `include/css_select.h`, `include/dom.h`, `include/html_parse.h`, `include/util.h`

## src/dom_debug.c
- Doc: dd_cursor: Bounded write cursor: `pos` bytes are committed to `out` (always leaving room for the...
- Layer: utility
- Language: c
- Symbols:
  - `dd_cursor` (struct, line 24)
  - `dd_putc` (function, line 31) `static void dd_putc(dd_cursor *c, char ch)`
  - `dd_emit` (function, line 36) `static void dd_emit(dd_cursor *c, const char *s, size_t len)`
  - `dd_puts` (function, line 40) `static void dd_puts(dd_cursor *c, const char *s)`
  - `dd_printf` (function, line 48) `static void dd_printf(dd_cursor *c, const char *fmt, ...)`
  - `dd_w` (function, line 80) `static int dd_w(int v)`
  - `dd_color` (function, line 83) `static void dd_color(dd_cursor *c, int rgb)`
  - `dd_display_name` (function, line 88) `static const char *dd_display_name(int d)`
  - `dd_justify_name` (function, line 96) `static const char *dd_justify_name(int j)`
  - `dd_align_name` (function, line 108) `static const char *dd_align_name(int a)`
  - `dd_position_name` (function, line 118) `static const char *dd_position_name(int p)`
  - `dd_visibility_name` (function, line 129) `static const char *dd_visibility_name(int v)`
  - `dd_mix_blend_name` (function, line 137) `static const char *dd_mix_blend_name(int m)`
  - `dd_overflow_name` (function, line 156) `static const char *dd_overflow_name(int o)`
  - `dd_cursor_name` (function, line 165) `static const char *dd_cursor_name(int c)`
  - `dd_text_overflow_name` (function, line 182) `static const char *dd_text_overflow_name(int t)`
  - `dd_inset` (function, line 187) `static int dd_inset(int v)`
  - `dd_object_fit_name` (function, line 191) `static const char *dd_object_fit_name(int o)`
  - `dd_image_rendering_name` (function, line 202) `static const char *dd_image_rendering_name(int r)`
  - `dd_border_style_name` (function, line 211) `static const char *dd_border_style_name(int s)`
  - `dd_box_line` (function, line 244) `static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b)`
  - `dd_block_line` (function, line 304) `static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b)`
  - `dd_format` (function, line 380) `size_t dd_format(const rd_doc *doc, char *out, size_t cap)`
  - `dd_format_css` (function, line 412) `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)`
- Depends on: `include/box_style.h`, `include/css.h`, `include/dom_debug.h`, `include/flex_layout.h`, `include/page_view.h`


Next: [KB_src_p3.md](KB_src_p3.md)
