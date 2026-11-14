# Subsystem: src (page 3 of 10)
Previous: [KB_src_p2.md](KB_src_p2.md)

## src/css_color.c
- Doc: normalize: Trims surrounding ASCII spaces and lowercases into out (CC_TOKEN_MAX bytes). *...
- Layer: utility
- Language: c
- Symbols:
  - `cc_named` (struct, line 34)
  - `cc_cv` (struct, line 223)
  - `cc_cp` (struct, line 224)
  - `v` (type_alias, line 222) `typedef struct cc_cv { double v;`
  - `ascii_lower` (function, line 119) `static int ascii_lower(int c)`
  - `hex_val` (function, line 123) `static int hex_val(int c)`
  - `normalize` (function, line 132) `static int normalize(const char *token, char *out)`
  - `parse_hex` (function, line 146) `static int parse_hex(const char *s, cc_rgb *out)`
  - `cc_cws` (function, line 226) `static void cc_cws(cc_cp *c)`
  - `cc_cfactor` (function, line 229) `static int cc_cfactor(cc_cp *c, cc_cv *out, int depth)`
  - `cc_cterm` (function, line 250) `static int cc_cterm(cc_cp *c, cc_cv *out, int depth)`
  - `cc_cexpr` (function, line 269) `static int cc_cexpr(cc_cp *c, cc_cv *out, int depth)`
  - `cc_fold_calc` (function, line 285) `static int cc_fold_calc(const char **b, const char **e, char *buf, size_t cap)`
  - `cc_round` (function, line 305) `static long cc_round(double v)`
  - `parse_component` (function, line 310) `static int parse_component(const char *b, const char *e, int is_alpha, int *out)`
  - `parse_hsl_comp` (function, line 343) `static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out)`
  - `span` (function, line 431) `* span (when a slash is present) into ab/ae, and returns the component count,
 * or -1. Bounded: ...`
  - `parse_func` (function, line 508) `static int parse_func(const char *s, cc_rgb *out)`
  - `lab_comp` (function, line 581) `static int lab_comp(const char *b, const char *e, double pct_ref, int is_hue, double *out)`
  - `srgb_encode` (function, line 609) `static unsigned char srgb_encode(double lin)`
  - `oklab_to_rgb` (function, line 616) `static void oklab_to_rgb(double L, double a, double b, cc_rgb *out)`
  - `lab_to_rgb` (function, line 627) `static void lab_to_rgb(double L, double a, double b, cc_rgb *out)`
  - `parse_lab_family` (function, line 643) `static int parse_lab_family(const char *s, cc_rgb *out)`
  - `named_cmp` (function, line 681) `static int named_cmp(const void *key, const void *element)`
  - `parse_named` (function, line 715) `static int parse_named(const char *s, cc_rgb *out)`
  - `cc_parse` (function, line 728) `cc_status cc_parse(const char *token, cc_rgb *out)`
  - `strncmp` (function, line 743) `strncmp(buf, "oklab(", 6) == 0 || strncmp(buf, "oklch(", 6) == 0)`
  - `cc_pack` (function, line 768) `int cc_pack(cc_rgb c)`
  - `cc_unpack` (function, line 772) `cc_rgb cc_unpack(int packed)`
  - `CC_TOKEN_MAX` (macro, line 20) `#define CC_TOKEN_MAX`
  - `CC_CHANNEL_MAX` (macro, line 23) `#define CC_CHANNEL_MAX`
  - `CC_PERCENT_MAX` (macro, line 24) `#define CC_PERCENT_MAX`
  - `CC_NUMBER_MAX_DIGITS` (macro, line 29) `#define CC_NUMBER_MAX_DIGITS`
  - `CC_HSL_SCALE` (macro, line 32) `#define CC_HSL_SCALE`
  - `CC_CALC_DEPTH` (macro, line 221) `#define CC_CALC_DEPTH`
  - `CC_PI` (macro, line 577) `#define CC_PI`
- Depends on: `include/css_color.h`

## src/css_computed.c
- Doc: ua_display: The HTML Rendering UA sheet's `display` for a tag when the cascade declared none *...
- Layer: utility
- Language: c
- Symbols:
  - `ccm_prop` (struct, line 278)
  - `put` (function, line 9) `static size_t put(char *out, size_t cap, const char *s)`
  - `putf` (function, line 17) `static size_t putf(char *out, size_t cap, const char *fmt, ...)`
  - `put_rgb` (function, line 26) `static size_t put_rgb(char *out, size_t cap, int rgb, int alpha_pct)`
  - `put_len` (function, line 37) `static size_t put_len(char *out, size_t cap, int v, const char *unset_text)`
  - `put_enum` (function, line 42) `static size_t put_enum(char *out, size_t cap, int v, const char *const *names, size_t n,
        ...`
  - `ua_display` (function, line 49) `static const char *ua_display(const char *tag)`
  - `f_display` (function, line 77) `static size_t f_display(const ccm_input *in, char *out, size_t cap)`
  - `f_position` (function, line 97) `static size_t f_position(const ccm_input *in, char *out, size_t cap)`
  - `f_visibility` (function, line 102) `static size_t f_visibility(const ccm_input *in, char *out, size_t cap)`
  - `f_float` (function, line 107) `static size_t f_float(const ccm_input *in, char *out, size_t cap)`
  - `f_clear` (function, line 112) `static size_t f_clear(const ccm_input *in, char *out, size_t cap)`
  - `f_overflow_x` (function, line 117) `static size_t f_overflow_x(const ccm_input *in, char *out, size_t cap)`
  - `f_overflow_y` (function, line 122) `static size_t f_overflow_y(const ccm_input *in, char *out, size_t cap)`
  - `f_text_align` (function, line 127) `static size_t f_text_align(const ccm_input *in, char *out, size_t cap)`
  - `f_box_sizing` (function, line 132) `static size_t f_box_sizing(const ccm_input *in, char *out, size_t cap)`
  - `f_flex_direction` (function, line 137) `static size_t f_flex_direction(const ccm_input *in, char *out, size_t cap)`
  - `f_flex_wrap` (function, line 142) `static size_t f_flex_wrap(const ccm_input *in, char *out, size_t cap)`
  - `f_justify` (function, line 147) `static size_t f_justify(const ccm_input *in, char *out, size_t cap)`
  - `f_align_items` (function, line 153) `static size_t f_align_items(const ccm_input *in, char *out, size_t cap)`
  - `f_cursor` (function, line 159) `static size_t f_cursor(const ccm_input *in, char *out, size_t cap)`
  - `f_white_space` (function, line 165) `static size_t f_white_space(const ccm_input *in, char *out, size_t cap)`
  - `f_text_transform` (function, line 170) `static size_t f_text_transform(const ccm_input *in, char *out, size_t cap)`
  - `f_font_style` (function, line 175) `static size_t f_font_style(const ccm_input *in, char *out, size_t cap)`
  - `f_font_weight` (function, line 179) `static size_t f_font_weight(const ccm_input *in, char *out, size_t cap)`
  - `f_font_size` (function, line 183) `static size_t f_font_size(const ccm_input *in, char *out, size_t cap)`
  - `f_line_height` (function, line 189) `static size_t f_line_height(const ccm_input *in, char *out, size_t cap)`
  - `f_color` (function, line 195) `static size_t f_color(const ccm_input *in, char *out, size_t cap)`
  - `f_background_color` (function, line 200) `static size_t f_background_color(const ccm_input *in, char *out, size_t cap)`
  - `f_opacity` (function, line 206) `static size_t f_opacity(const ccm_input *in, char *out, size_t cap)`
  - `f_z_index` (function, line 214) `static size_t f_z_index(const ccm_input *in, char *out, size_t cap)`
  - `f_border_style` (function, line 219) `static size_t f_border_style(int v, char *out, size_t cap)`
  - `NAME` (function, line 226) `static size_t NAME(const ccm_input *in, char *out, size_t cap)`
  - `f_gap` (function, line 246) `static size_t f_gap(const ccm_input *in, char *out, size_t cap)`
  - `f_border_top_style` (function, line 258) `static size_t f_border_top_style(const ccm_input *in, char *out, size_t cap)`
  - `f_border_right_style` (function, line 261) `static size_t f_border_right_style(const ccm_input *in, char *out, size_t cap)`
  - `f_border_bottom_style` (function, line 264) `static size_t f_border_bottom_style(const ccm_input *in, char *out, size_t cap)`
  - `f_border_left_style` (function, line 267) `static size_t f_border_left_style(const ccm_input *in, char *out, size_t cap)`
  - `f_flex_grow` (function, line 271) `static size_t f_flex_grow(const ccm_input *in, char *out, size_t cap)`
  - `f_flex_shrink` (function, line 274) `static size_t f_flex_shrink(const ccm_input *in, char *out, size_t cap)`
  - `ccm_get` (function, line 312) `size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap)`
  - `ccm_property_count` (function, line 325) `size_t ccm_property_count(void)`
  - `ccm_property_name` (function, line 327) `const char *ccm_property_name(size_t i)`
  - `LEN_FIELD` (macro, line 225) `#define LEN_FIELD(NAME, FIELD, UNSET)`
  - `CCM_NPROPS` (macro, line 310) `#define CCM_NPROPS`
- Depends on: `include/css_computed.h`

## src/css_counter.c
- Doc: valid_name: A <custom-ident> usable as a counter name: identifier syntax, not a CSS-wide *...
- Layer: utility
- Language: c
- Symbols:
  - `cnt_state` (struct, line 361)
  - `sink` (struct, line 190)
  - `cnt_inst` (struct, line 359)
  - `cnt_hash` (function, line 18) `unsigned cnt_hash(const char *name, size_t len)`
  - `is_ws` (function, line 27) `static int is_ws(char c)`
  - `is_ident_start` (function, line 29) `static int is_ident_start(unsigned char c)`
  - `is_ident_char` (function, line 32) `static int is_ident_char(unsigned char c)`
  - `ci_eq` (function, line 34) `static int ci_eq(const char *a, const char *b)`
  - `valid_name` (function, line 45) `static int valid_name(const char *s, size_t n)`
  - `cnt_parse_decls` (function, line 59) `int cnt_parse_decls(const char *val, int dflt, cnt_decl out[CNT_MAX_DECL])`
  - `put` (function, line 102) `static size_t put(char *out, size_t cap, size_t o, const char *s)`
  - `utf8_put` (function, line 107) `static void utf8_put(char *buf, unsigned cp)`
  - `cnt_format` (function, line 120) `size_t cnt_format(int style, long value, char *out, size_t cap)`
  - `style_of` (function, line 174) `static int style_of(const char *name)`
  - `sk_char` (function, line 192) `static void sk_char(sink *k, char c)`
  - `sk_str` (function, line 196) `static void sk_str(sink *k, const char *s)`
  - `read_string` (function, line 201) `static const char *read_string(const char *p, char *dst, size_t cap)`
  - `split_args` (function, line 238) `static int split_args(const char *a, const char *b, char (*f)[CNT_STR_MAX], int max)`
  - `cnt_is_marker` (function, line 272) `int cnt_is_marker(const char *s)`
  - `has_counter_fn` (function, line 276) `static int has_counter_fn(const char *v)`
  - `cnt_parse_content` (function, line 286) `int cnt_parse_content(const char *val, char *out, size_t cap)`
  - `cnt_state_new` (function, line 366) `cnt_state *cnt_state_new(void)`
  - `cnt_state_free` (function, line 367) `void cnt_state_free(cnt_state *s)`
  - `top_of` (function, line 369) `static cnt_inst *top_of(cnt_state *s, unsigned name)`
  - `clampv` (function, line 375) `static int clampv(long v)`
  - `cnt_reset` (function, line 379) `void cnt_reset(cnt_state *s, int depth, const cnt_decl *d, int n)`
  - `cnt_increment` (function, line 392) `void cnt_increment(cnt_state *s, int depth, const cnt_decl *d, int n)`
  - `cnt_leave` (function, line 407) `void cnt_leave(cnt_state *s, int depth)`
  - `cnt_resolve` (function, line 412) `size_t cnt_resolve(const cnt_state *s, const char *marker, cnt_attr_fn attr, void *ctx,
         ...`
  - `CNT_SEQ_MARK` (macro, line 12) `#define CNT_SEQ_MARK`
  - `CNT_ITEM_END` (macro, line 13) `#define CNT_ITEM_END`
  - `CNT_FIELD_SEP` (macro, line 14) `#define CNT_FIELD_SEP`
  - `CNT_VALUE_LIMIT` (macro, line 15) `#define CNT_VALUE_LIMIT`
  - `CNT_STR_MAX` (macro, line 16) `#define CNT_STR_MAX`
- Depends on: `include/css_counter.h`

## src/css_gradient.c
- Doc: find_gradient_call: Locates a gradient function call `fn` (e.g. "linear-gradient(") in v...
- Layer: utility
- Language: c
- Symbols:
  - `cg_parse_num` (function, line 13) `static int cg_parse_num(const char *s, double *out, const char **endp)`
  - `cg_wide_keyword` (function, line 18) `static int cg_wide_keyword(const char *v)`
  - `gradient` (function, line 28) `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,
 * the whole decl...`
  - `find_gradient_call` (function, line 77) `static int find_gradient_call(const char *v, const char *fn, size_t *start,
                     ...`
  - `conic_prelude` (function, line 111) `static int conic_prelude(const char *seg, int *angle)`
  - `grad_stop_pos` (function, line 153) `static int grad_stop_pos(const char *pp, int conic, const char **endp)`
  - `CSS_GRAD_STOPS_MAX` (function, line 184) `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when
 * the gradient fai...`
  - `emit_gradient` (function, line 291) `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,
                         ...`
  - `find_radial_gradient` (function, line 360) `static int find_radial_gradient(const char *v, size_t *start, size_t *end,
                      ...`
  - `cg_first_url` (function, line 398) `int cg_first_url(const char *val, char *out, size_t outcap)`
  - `emit_radial_geom` (function, line 405) `static int emit_radial_geom(css_decl *dst, int cap, const cg_radial *r)`
  - `downstream` (function, line 422) `* happens downstream (render_doc.c), gated by caps.images like an <img>. */
int cg_expand_bg_imag...`
  - `bg_layer_tokens_ok` (function, line 490) `static int bg_layer_tokens_ok(const char *s)`
  - `cg_expand_background` (function, line 530) `int cg_expand_background(const char *val, css_decl *dst, int cap,
                             ch...`
  - `rad_ieq` (function, line 618) `static int rad_ieq(const char *a, const char *b)`
  - `rad_len` (function, line 626) `static int rad_len(const char *tok, int *enc)`
  - `rad_is_len_start` (function, line 647) `static int rad_is_len_start(const char *t)`
  - `rad_pos_kw` (function, line 652) `static int rad_pos_kw(const char *t, int *axis)`
  - `rad_parse_position` (function, line 661) `static int rad_parse_position(char (*tok)[CSS_TOK_MAX], int n, int *cx, int *cy)`
  - `cg_parse_radial_prelude` (function, line 690) `int cg_parse_radial_prelude(const char *seg, cg_radial *out)`
  - `cg_radial_len_px` (function, line 766) `double cg_radial_len_px(int enc, double dim)`
  - `cg_dmin` (function, line 775) `static double cg_dmin(double a, double b)`
  - `cg_dmax` (function, line 776) `static double cg_dmax(double a, double b)`
  - `cg_radial_geometry` (function, line 778) `void cg_radial_geometry(const cg_radial *r, double w, double h,
                        double *c...`
  - `cg_parse_linear` (function, line 815) `int cg_parse_linear(const char *fn, int *angle, int *colors, int *positions)`
  - `pool` (function, line 418) `* pool (gradient explicitly reset);`
  - `declaration` (function, line 483) `* declaration (fail closed);`
  - `CG_RAD_TOKENS` (macro, line 614) `#define CG_RAD_TOKENS`
  - `CG_RAD_PM_MAX` (macro, line 615) `#define CG_RAD_PM_MAX`
  - `CG_RAD_PX_MAX` (macro, line 616) `#define CG_RAD_PX_MAX`
  - `CG_RAD_FLOOR` (macro, line 772) `#define CG_RAD_FLOOR`
  - `CG_SQRT2` (macro, line 773) `#define CG_SQRT2`
- Depends on: `include/css_color.h`, `include/css_decl.h`, `include/css_gradient.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`

## src/css_index.c
- Doc: css_index -- see include/css_index.h and spec/css_index.md.
- Layer: utility
- Language: c
- Symbols:
  - `cix_run` (struct, line 98)
  - `key_of` (function, line 11) `static uint64_t key_of(int kind, const char *s, size_t n, int lower)`
  - `key_of_token` (function, line 26) `static uint64_t key_of_token(int kind, const char *tok)`
  - `entry_cmp` (function, line 34) `static int entry_cmp(const void *a, const void *b)`
  - `cix_free` (function, line 40) `void cix_free(cix_index *idx)`
  - `build` (function, line 47) `static void build(const css_sel *arr, css_sel *const *ptrs, size_t n, cix_index *idx)`
  - `lower_bound` (function, line 86) `static size_t lower_bound(const cix_index *idx, uint64_t k)`
  - `run_head` (function, line 104) `static uint32_t run_head(const cix_run *r)`
  - `add_bucket` (function, line 106) `static void add_bucket(const cix_index *idx, uint64_t k, cix_run *runs, size_t *nr)`
  - `push` (function, line 114) `static int push(uint32_t **buf, size_t *cap, size_t *n, uint32_t v)`
  - `cix_candidates` (function, line 129) `size_t cix_candidates(const cix_index *idx, const css_element *el,
                      uint32_t...`
  - `cix_build` (function, line 166) `void cix_build(const css_sel *sels, size_t n, cix_index *idx)`
  - `cix_build_ptrs` (function, line 168) `void cix_build_ptrs(css_sel *const *sels, size_t n, cix_index *idx)`
- Depends on: `include/css_index.h`

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

## src/css_mask.c
- Doc: A layer token can be a whole url(...) (a data: SVG icon is routinely 400-900 bytes): the token...
- Layer: utility
- Language: c
- Symbols:
  - `ieq` (function, line 13) `static int ieq(const char *a, const char *b)`
  - `cm_is_mask_prop` (function, line 19) `int cm_is_mask_prop(const char *prop)`
  - `cm_encode_layer` (function, line 26) `void cm_encode_layer(const cm_layer *l, int *meta, int *alphas, int *poss)`
  - `cm_decode_layer` (function, line 47) `void cm_decode_layer(int meta, int alphas, int poss, cm_layer *out)`
  - `split` (function, line 65) `static int split(const char *s, int comma, char (*out)[CM_TOK_MAX], int max)`
  - `composite_word` (function, line 92) `static int composite_word(const char *t, int webkit)`
  - `clip_word` (function, line 106) `static int clip_word(const char *t)`
  - `image_layer` (function, line 114) `static int image_layer(const char *tok, cm_layer *l)`
  - `emit_layers` (function, line 132) `static int emit_layers(css_decl *dst, int cap, int shorthand, const char *val)`
  - `cm_expand` (function, line 201) `int cm_expand(const char *prop, const char *val, css_decl *dst, int cap, int webkit_vocab)`
  - `CM_TOK_MAX` (macro, line 10) `#define CM_TOK_MAX`
  - `CM_MAX_TOKS` (macro, line 11) `#define CM_MAX_TOKS`
- Depends on: `include/css_gradient.h`, `include/css_mask.h`

## src/css_mq.c
- Doc: read_word: static int is_space(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'...
- Layer: utility
- Language: c
- Symbols:
  - `mq_cur` (struct, line 26)
  - `fval` (struct, line 97)
  - `kind` (type_alias, line 96) `typedef struct fval { fv_kind kind;`
  - `lower_ch` (function, line 32) `static char lower_ch(char c)`
  - `is_space` (function, line 36) `static int is_space(char c)`
  - `is_ident_ch` (function, line 40) `static int is_ident_ch(char c)`
  - `skip_ws` (function, line 45) `static void skip_ws(mq_cur *c)`
  - `read_word` (function, line 50) `static int read_word(mq_cur *c, char *w, size_t cap)`
  - `peek_word` (function, line 62) `static int peek_word(const mq_cur *c, char *w, size_t cap)`
  - `and3` (function, line 67) `static int and3(int a, int b)`
  - `or3` (function, line 73) `static int or3(int a, int b)`
  - `not3` (function, line 79) `static int not3(int a)`
  - `copy_trim_lower` (function, line 84) `static int copy_trim_lower(const char *s, size_t a, size_t b, char *dst, size_t cap)`
  - `feature_of` (function, line 107) `static fval feature_of(const char *name, const cmq_env *env)`
  - `read_num` (function, line 163) `static int read_num(const char *t, double *out, const char **end)`
  - `parse_value` (function, line 168) `static int parse_value(const char *t, int unit, double *out)`
  - `cmp_op` (function, line 208) `static int cmp_op(double lhs, int op, double rhs)`
  - `flip_op` (function, line 220) `static int flip_op(int op)`
  - `bool_ctx` (function, line 231) `static int bool_ctx(const fval *v)`
  - `eval_plain` (function, line 239) `static int eval_plain(const char *name, const char *value, const cmq_env *env)`
  - `read_op` (function, line 268) `static int read_op(const char **p)`
  - `eval_range` (function, line 282) `static int eval_range(const char *t, const cmq_env *env)`
  - `eval_feature` (function, line 330) `static int eval_feature(const char *s, size_t a, size_t b, const cmq_env *env)`
  - `eval_in_parens` (function, line 355) `static int eval_in_parens(mq_cur *c, int depth)`
  - `eval_cond` (function, line 382) `static int eval_cond(mq_cur *c, int depth)`
  - `eval_query` (function, line 406) `static int eval_query(const char *s, size_t a, size_t b, const cmq_env *env)`
  - `cmq_matches` (function, line 460) `int cmq_matches(const char *s, size_t len, const cmq_env *env)`
  - `has_word` (function, line 481) `static int has_word(const char *t, const char *w)`
  - `cmq_container_surely` (function, line 491) `int cmq_container_surely(const char *s, size_t len, int max_width)`
  - `CMQ_DEVICE_W` (macro, line 19) `#define CMQ_DEVICE_W`
  - `CMQ_DEVICE_H` (macro, line 20) `#define CMQ_DEVICE_H`
  - `CMQ_DPPX` (macro, line 21) `#define CMQ_DPPX`
  - `CMQ_COLOR_BITS` (macro, line 22) `#define CMQ_COLOR_BITS`
  - `CMQ_DPI_PER_DPPX` (macro, line 23) `#define CMQ_DPI_PER_DPPX`
  - `CMQ_CM_PER_IN` (macro, line 24) `#define CMQ_CM_PER_IN`
  - `MQ_EPS` (macro, line 205) `#define MQ_EPS`
- Depends on: `include/css_box.h`, `include/css_length.h`, `include/css_mq.h`

## src/css_select.c
- Doc: csel_hex_val: CSS Syntax 4.3.7 escape consumption (moved from css.c; shared by quoted content...
- Layer: utility
- Language: c
- Symbols:
  - `csel_hex_val` (function, line 25) `int csel_hex_val(char c)`
  - `csel_emit_utf8` (function, line 32) `size_t csel_emit_utf8(unsigned int cp, char *out)`
  - `csel_unescape` (function, line 54) `void csel_unescape(char *dst, size_t cap, const char *src, size_t n)`
  - `csel_escape_len` (function, line 93) `size_t csel_escape_len(const char *s, size_t i, size_t b)`
  - `csel_decl_end` (function, line 106) `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace)`
  - `ident_hash` (function, line 123) `static unsigned long long ident_hash(const char *s, size_t n)`
  - `csel_ident_fold` (function, line 129) `void csel_ident_fold(const char *src, size_t len, char *dst)`
  - `csel_ident_eq` (function, line 144) `int csel_ident_eq(const char *stored, const char *tok, size_t tlen)`
  - `csel_read_ident` (function, line 152) `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower)`
  - `parse_attr_sel` (function, line 186) `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)`
  - `parse_nth_arg` (function, line 243) `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)`
  - `simple_pseudo_kind` (function, line 439) `static int simple_pseudo_kind(const char *nm)`
  - `parse_sub_compound` (function, line 460) `static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub)`
  - `parse_compound` (function, line 525) `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,
                  ...`
  - `selector` (function, line 567) `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is
 * dropped. Whitespa...`
  - `csel_element_feature_bits` (function, line 587) `unsigned long long csel_element_feature_bits(const css_element *e)`
  - `compute_anc_req` (function, line 602) `static unsigned long long compute_anc_req(const css_sel *sel)`
  - `csel_parse_core` (function, line 615) `static int csel_parse_core(const char *s, size_t a, size_t b, css_sel *sel)`
  - `compound_req` (function, line 709) `static unsigned long long compound_req(const css_compound *c)`
  - `compute_subj_req` (function, line 718) `static unsigned long long compute_subj_req(const css_sel *sel)`
  - `csel_compact_size` (function, line 729) `size_t csel_compact_size(int nparts)`
  - `csel_compact_dup` (function, line 735) `css_sel *csel_compact_dup(const css_sel *sel)`
  - `csel_parse` (function, line 744) `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel)`
  - `el_attr_value` (function, line 755) `static const char *el_attr_value(const css_element *el, const char *name)`
  - `ends_with` (function, line 765) `static int ends_with(const char *v, const char *suf, int ci)`
  - `has_word` (function, line 773) `static int has_word(const char *v, const char *w, int ci)`
  - `attr_matches` (function, line 788) `static int attr_matches(const css_attr_match *am, const css_element *el)`
  - `nth_matches` (function, line 808) `static int nth_matches(int A, int B, int idx)`
  - `is_form_control` (function, line 817) `static int is_form_control(const char *tag)`
  - `sub_sel_matches` (function, line 830) `static int sub_sel_matches(const css_sub_sel *sub, const css_element *el)`
  - `compound_matches` (function, line 1080) `static int compound_matches(const css_compound *c, const css_element *el,
                       ...`
  - `built` (function, line 1115) `* chains the caller built (an element without parent/prev links never matches
 * through that com...`
  - `pseudo_is_local` (function, line 1160) `static int pseudo_is_local(int kind)`
  - `csel_needs_structure` (function, line 1173) `int csel_needs_structure(const css_sel *sel)`
  - `csel_matches` (function, line 1196) `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,
              ...`
  - `take_sub_arg` (function, line 295) `static int take_sub_arg(const char *s, size_t a, size_t b, css_sel *sel, int strict);`
  - `between` (function, line 384) `* between ( and ) is split on commas (not inside [] or ());`
  - `seven` (function, line 621) `* pay for the other seven (a css_sel is ~12.8 KiB). */ memset(sel, 0, offsetof(css_sel, parts));`
  - `pseudo_matches` (function, line 826) `static int pseudo_matches(const css_pseudo_match *pm, const css_element *el, const css_sel *sel, const char...`
  - `HAS_MAX_DEPTH` (macro, line 939) `#define HAS_MAX_DEPTH`
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
  - `transition_prop_one` (function, line 139) `static int transition_prop_one(const char *v)`
  - `ct_interp_whitespace` (function, line 182) `int ct_interp_whitespace(const char *v)`
  - `ct_interp_tabsize` (function, line 195) `int ct_interp_tabsize(const char *v)`
  - `ct_interp_textdeco_style` (function, line 206) `int ct_interp_textdeco_style(const char *v)`
  - `ct_interp_textdeco_thickness` (function, line 217) `int ct_interp_textdeco_thickness(const char *v)`
  - `ct_interp_aspect_ratio` (function, line 229) `int ct_interp_aspect_ratio(const char *v, int *num, int *den)`
  - `ct_interp_direction` (function, line 271) `int ct_interp_direction(const char *v)`
  - `ct_liststyle_kw` (function, line 277) `static int ct_liststyle_kw(const char *t)`
  - `ct_liststyle_unknown_name` (function, line 298) `static int ct_liststyle_unknown_name(const char *t)`
  - `ct_interp_liststyle` (function, line 309) `int ct_interp_liststyle(const char *v)`
  - `ct_emit_spacing` (function, line 344) `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
  - `ct_expand_shadow` (function, line 357) `int ct_expand_shadow(const char *val, css_decl *dst, int cap)`
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
  - `cv_parse_color_t7` (function, line 205) `int cv_parse_color_t7(const char *v)`
  - `cv_text_color` (function, line 222) `int cv_text_color(const char *v)`
  - `cv_filter_scale` (function, line 231) `double cv_filter_scale(int pct)`
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
  - `env_value` (function, line 182) `static const char *env_value(const char *name, size_t n)`
  - `resolve_rec` (function, line 192) `static int resolve_rec(const char *val, size_t vlen, char *out, size_t outcap,
                  ...`
  - `cvr_resolve` (function, line 281) `int cvr_resolve(const char *val, char *out, size_t outcap, const cvr_scope *sc)`
  - `cvr_lookup` (function, line 290) `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen)`
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
  - `du_shape_ok` (function, line 59) `du_status du_shape_ok(const char *url)`
  - `b64_val` (function, line 70) `static int b64_val(unsigned char c)`
  - `du_base64_decode` (function, line 79) `du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len)`
  - `hexval` (function, line 117) `static int hexval(char c)`
  - `ascii_ws` (function, line 124) `static int ascii_ws(char c)`
  - `ends_ci` (function, line 129) `static int ends_ci(const char *s, size_t n, const char *suf)`
  - `du_decode` (function, line 140) `du_status du_decode(const char *url, char *mime, size_t mime_cap, uint8_t **out, size_t *out_len)`
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


Next: [KB_src_p4.md](KB_src_p4.md)
