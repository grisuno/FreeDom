# Symbols (page 6 of 14)
Previous: [SYMBOLS_p5.md](SYMBOLS_p5.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `calc_eval_full` | function | `src/css_box.c:913` | `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,            ...` |
| `calc_expr` | function | `src/css_box.c:894` | `static int calc_expr(calc_parser *p, calc_val *out, int depth)` |
| `calc_match_fn` | function | `src/css_box.c:707` | `static int calc_match_fn(calc_parser *p, const char *name)` |
| `calc_mathfn` | function | `src/css_box.c:749` | `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` |
| `calc_parser` | struct | `src/css_box.c:698` | `` |
| `calc_piecewise` | function | `src/css_box.c:734` | `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)` |
| `calc_skip_ws` | function | `src/css_box.c:700` | `static void calc_skip_ws(calc_parser *p)` |
| `calc_term` | function | `src/css_box.c:870` | `static int calc_term(calc_parser *p, calc_val *out, int depth)` |
| `calc_unwrap` | function | `src/css_box.c:935` | `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` |
| `calc_val` | struct | `src/css_box.c:697` | `` |
| `cb_copy_trim` | function | `src/css_box.c:25` | `static size_t cb_copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `cb_expand_box2` | function | `src/css_box.c:1332` | `int cb_expand_box2(const char *val, int slot_start, int slot_end,                        int allo...` |
| `cb_expand_grid_template_cols` | function | `src/css_box.c:591` | `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `cb_expand_grid_template_rows` | function | `src/css_box.c:614` | `int cb_expand_grid_template_rows(const char *val, css_decl *dst, int cap)` |
| `cb_interp_align` | function | `src/css_box.c:54` | `int cb_interp_align(const char *v)` |
| `cb_interp_display` | function | `src/css_box.c:213` | `int cb_interp_display(const char *v)` |
| `cb_interp_fontsize_ex` | function | `src/css_box.c:72` | `int cb_interp_fontsize_ex(const char *v, int *abs_out)` |
| `cb_interp_gap` | function | `src/css_box.c:288` | `int cb_interp_gap(const char *v)` |
| `cb_interp_justify` | function | `src/css_box.c:295` | `int cb_interp_justify(const char *v)` |
| `cb_interp_len` | function | `src/css_box.c:986` | `int cb_interp_len(const char *v, int allow_auto, int *out)` |
| `cb_interp_lineheight` | function | `src/css_box.c:145` | `int cb_interp_lineheight(const char *v)` |
| `cb_interp_lp` | function | `src/css_box.c:1085` | `int cb_interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_px, ...` |
| `cb_interp_style` | function | `src/css_box.c:183` | `int cb_interp_style(const char *v)` |
| `cb_interp_textdeco` | function | `src/css_box.c:193` | `int cb_interp_textdeco(const char *v)` |
| `cb_interp_weight` | function | `src/css_box.c:174` | `int cb_interp_weight(const char *v)` |
| `cb_length_px` | function | `src/css_box.c:49` | `int cb_length_px(const char *v, double *px)` |
| `cb_parse_num` | function | `src/css_box.c:13` | `static int cb_parse_num(const char *s, double *out, const char **endp)` |
| `cb_starts_with_ci` | function | `src/css_box.c:320` | `static int cb_starts_with_ci(const char *s, const char *pre)` |
| `cb_value_em_milli` | function | `src/css_box.c:1065` | `int cb_value_em_milli(const char *v)` |
| `cb_wide_keyword` | function | `src/css_box.c:18` | `static int cb_wide_keyword(const char *v)` |
| `count_one_repeat` | function | `src/css_box.c:364` | `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,                       ...` |
| `count_tracks` | function | `src/css_box.c:326` | `static int count_tracks(const char *s, size_t n)` |
| `expand_auto_fill` | function | `src/css_box.c:513` | `static int expand_auto_fill(const char *val, css_decl *dst, int cap)` |
| `interp_len` | function | `src/css_box.c:1261` | `* this file that might hand a token to interp_len (transitively: margin/padding/  * inset, flex-b...` |
| `min` | function | `src/css_box.c:768` | `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the...` |
| `pct_slot_of` | function | `src/css_box.c:1015` | `static int pct_slot_of(int slot)` |
| `px` | type_alias | `src/css_box.c:697` | `typedef struct calc_val { double px;` |
| `repeat` | function | `src/css_box.c:309` | `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill\|...) /...` |
| `term` | function | `src/css_box.c:1092` | `* the same expression and failed closed on the percentage term (its property * may not accept one);` |
| `track_min_of` | function | `src/css_box.c:475` | `static int track_min_of(const char *tok)` |
| `track_size_of` | function | `src/css_box.c:334` | `static int track_size_of(const char *tok)` |
| `walk_tracks` | function | `src/css_box.c:407` | `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)` |
| `CCH_ATTR_BUF` | macro | `src/css_chain.c:23` | `#define CCH_ATTR_BUF` |
| `CCH_CLASS_BUF` | macro | `src/css_chain.c:17` | `#define CCH_CLASS_BUF` |
| `CCH_CLASS_SPILL_MAX` | macro | `src/css_chain.c:21` | `#define CCH_CLASS_SPILL_MAX` |
| `CCH_ID_MAX` | macro | `src/css_chain.c:16` | `#define CCH_ID_MAX` |
| `CCH_MAX_ATTRS` | macro | `src/css_chain.c:22` | `#define CCH_MAX_ATTRS` |
| `CCH_MAX_CLASSES` | macro | `src/css_chain.c:18` | `#define CCH_MAX_CLASSES` |
| `CCH_TAG_MAX` | macro | `src/css_chain.c:15` | `#define CCH_TAG_MAX` |
| `cch_element_matches` | function | `src/css_chain.c:351` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)` |
| `cch_element_style` | function | `src/css_chain.c:347` | `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)` |
| `cch_element_style_vars` | function | `src/css_chain.c:297` | `css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,                  ...` |
| `cch_node` | struct | `src/css_chain.c:27` | `` |
| `cch_pseudo_style` | function | `src/css_chain.c:328` | `css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,             ...` |
| `cls_space` | function | `src/css_chain.c:42` | `static int cls_space(char c)` |
| `count_children` | function | `src/css_chain.c:227` | `static int count_children(lxb_dom_node_t *n)` |
| `fill_css_node` | function | `src/css_chain.c:99` | `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)` |
| `inputs` | function | `src/css_chain.c:241` | `* identical inputs (single source of truth). */ static const css_element *build_chain(lxb_dom_ele...` |
| `release_nodes` | function | `src/css_chain.c:90` | `static void release_nodes(cch_node *nodes, int n)` |
| `sibling_position` | function | `src/css_chain.c:181` | `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `sibling_type_position` | function | `src/css_chain.c:199` | `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `tag` | type_alias | `src/css_chain.c:27` | `typedef struct cch_node { char tag[CCH_TAG_MAX];` |
| `CC_CHANNEL_MAX` | macro | `src/css_color.c:22` | `#define CC_CHANNEL_MAX` |
| `CC_HSL_SCALE` | macro | `src/css_color.c:31` | `#define CC_HSL_SCALE` |
| `CC_NUMBER_MAX_DIGITS` | macro | `src/css_color.c:28` | `#define CC_NUMBER_MAX_DIGITS` |
| `CC_PERCENT_MAX` | macro | `src/css_color.c:23` | `#define CC_PERCENT_MAX` |
| `CC_PI` | macro | `src/css_color.c:463` | `#define CC_PI` |
| `CC_TOKEN_MAX` | macro | `src/css_color.c:19` | `#define CC_TOKEN_MAX` |
| `ascii_lower` | function | `src/css_color.c:118` | `static int ascii_lower(int c)` |
| `cc_named` | struct | `src/css_color.c:33` | `` |
| `cc_pack` | function | `src/css_color.c:623` | `int cc_pack(cc_rgb c)` |
| `cc_parse` | function | `src/css_color.c:583` | `cc_status cc_parse(const char *token, cc_rgb *out)` |
| `cc_round` | function | `src/css_color.c:215` | `static long cc_round(double v)` |
| `cc_unpack` | function | `src/css_color.c:627` | `cc_rgb cc_unpack(int packed)` |
| `hex_val` | function | `src/css_color.c:122` | `static int hex_val(int c)` |
| `lab_comp` | function | `src/css_color.c:467` | `static int lab_comp(const char *b, const char *e, double pct_ref, int is_hue, double *out)` |
| `lab_to_rgb` | function | `src/css_color.c:513` | `static void lab_to_rgb(double L, double a, double b, cc_rgb *out)` |
| `named_cmp` | function | `src/css_color.c:567` | `static int named_cmp(const void *key, const void *element)` |
| `normalize` | function | `src/css_color.c:131` | `static int normalize(const char *token, char *out)` |
| `oklab_to_rgb` | function | `src/css_color.c:502` | `static void oklab_to_rgb(double L, double a, double b, cc_rgb *out)` |
| `parse_component` | function | `src/css_color.c:220` | `static int parse_component(const char *b, const char *e, int is_alpha, int *out)` |
| `parse_func` | function | `src/css_color.c:397` | `static int parse_func(const char *s, cc_rgb *out)` |
| `parse_hex` | function | `src/css_color.c:145` | `static int parse_hex(const char *s, cc_rgb *out)` |
| `parse_hsl_comp` | function | `src/css_color.c:253` | `static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out)` |
| `parse_lab_family` | function | `src/css_color.c:529` | `static int parse_lab_family(const char *s, cc_rgb *out)` |
| `parse_named` | function | `src/css_color.c:573` | `static int parse_named(const char *s, cc_rgb *out)` |
| `span` | function | `src/css_color.c:325` | `* span (when a slash is present) into ab/ae, and returns the component count,  * or -1. Bounded: ...` |
| `srgb_encode` | function | `src/css_color.c:495` | `static unsigned char srgb_encode(double lin)` |
| `strncmp` | function | `src/css_color.c:598` | `strncmp(buf, "oklab(", 6) == 0 \|\| strncmp(buf, "oklch(", 6) == 0)` |
| `CG_RAD_FLOOR` | macro | `src/css_gradient.c:754` | `#define CG_RAD_FLOOR` |
| `CG_RAD_PM_MAX` | macro | `src/css_gradient.c:597` | `#define CG_RAD_PM_MAX` |
| `CG_RAD_PX_MAX` | macro | `src/css_gradient.c:598` | `#define CG_RAD_PX_MAX` |
| `CG_RAD_TOKENS` | macro | `src/css_gradient.c:596` | `#define CG_RAD_TOKENS` |
| `CG_SQRT2` | macro | `src/css_gradient.c:755` | `#define CG_SQRT2` |
| `CSS_GRAD_STOPS_MAX` | function | `src/css_gradient.c:184` | `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when  * the gradient fai...` |
| `bg_layer_tokens_ok` | function | `src/css_gradient.c:472` | `static int bg_layer_tokens_ok(const char *s)` |
| `cg_dmax` | function | `src/css_gradient.c:758` | `static double cg_dmax(double a, double b)` |
| `cg_dmin` | function | `src/css_gradient.c:757` | `static double cg_dmin(double a, double b)` |
| `cg_expand_background` | function | `src/css_gradient.c:512` | `int cg_expand_background(const char *val, css_decl *dst, int cap,                              ch...` |
| `cg_parse_linear` | function | `src/css_gradient.c:797` | `int cg_parse_linear(const char *fn, int *angle, int *colors, int *positions)` |
| `cg_parse_num` | function | `src/css_gradient.c:13` | `static int cg_parse_num(const char *s, double *out, const char **endp)` |
| `cg_parse_radial_prelude` | function | `src/css_gradient.c:672` | `int cg_parse_radial_prelude(const char *seg, cg_radial *out)` |
| `cg_radial_geometry` | function | `src/css_gradient.c:760` | `void cg_radial_geometry(const cg_radial *r, double w, double h,                         double *c...` |
| `cg_radial_len_px` | function | `src/css_gradient.c:748` | `double cg_radial_len_px(int enc, double dim)` |
| `cg_wide_keyword` | function | `src/css_gradient.c:18` | `static int cg_wide_keyword(const char *v)` |
| `conic_prelude` | function | `src/css_gradient.c:111` | `static int conic_prelude(const char *seg, int *angle)` |
| `declaration` | function | `src/css_gradient.c:465` | `* declaration (fail closed);` |
| `downstream` | function | `src/css_gradient.c:404` | `* happens downstream (render_doc.c), gated by caps.images like an <img>. */ int cg_expand_bg_imag...` |
| `emit_gradient` | function | `src/css_gradient.c:291` | `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,                          ...` |
| `emit_radial_geom` | function | `src/css_gradient.c:387` | `static int emit_radial_geom(css_decl *dst, int cap, const cg_radial *r)` |
| `find_gradient_call` | function | `src/css_gradient.c:77` | `static int find_gradient_call(const char *v, const char *fn, size_t *start,                      ...` |
| `find_radial_gradient` | function | `src/css_gradient.c:348` | `static int find_radial_gradient(const char *v, size_t *start, size_t *end,                       ...` |
| `grad_stop_pos` | function | `src/css_gradient.c:153` | `static int grad_stop_pos(const char *pp, int conic, const char **endp)` |
| `gradient` | function | `src/css_gradient.c:28` | `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,  * the whole decl...` |
| `pool` | function | `src/css_gradient.c:400` | `* pool (gradient explicitly reset);` |
| `rad_ieq` | function | `src/css_gradient.c:600` | `static int rad_ieq(const char *a, const char *b)` |
| `rad_is_len_start` | function | `src/css_gradient.c:629` | `static int rad_is_len_start(const char *t)` |
| `rad_len` | function | `src/css_gradient.c:608` | `static int rad_len(const char *tok, int *enc)` |
| `rad_parse_position` | function | `src/css_gradient.c:643` | `static int rad_parse_position(char (*tok)[CSS_TOK_MAX], int n, int *cx, int *cy)` |
| `rad_pos_kw` | function | `src/css_gradient.c:634` | `static int rad_pos_kw(const char *t, int *axis)` |
| `cix_build` | function | `src/css_index.c:52` | `void cix_build(const css_sel *sels, size_t n, cix_index *idx)` |
| `cix_candidates` | function | `src/css_index.c:120` | `size_t cix_candidates(const cix_index *idx, const css_element *el,                       uint32_t...` |
| `cix_free` | function | `src/css_index.c:45` | `void cix_free(cix_index *idx)` |
| `entry_cmp` | function | `src/css_index.c:34` | `static int entry_cmp(const void *a, const void *b)` |
| `key_of` | function | `src/css_index.c:11` | `static uint64_t key_of(int kind, const char *s, size_t n, int lower)` |
| `key_of_token` | function | `src/css_index.c:26` | `static uint64_t key_of_token(int kind, const char *tok)` |
| `lower_bound` | function | `src/css_index.c:90` | `static size_t lower_bound(const cix_index *idx, uint64_t k)` |
| `push` | function | `src/css_index.c:100` | `static int push(uint32_t **buf, size_t *cap, size_t *n, uint32_t v)` |
| `push_bucket` | function | `src/css_index.c:113` | `static int push_bucket(const cix_index *idx, uint64_t k,                        uint32_t **buf, s...` |
| `u32_cmp` | function | `src/css_index.c:40` | `static int u32_cmp(const void *a, const void *b)` |
| `CL_PX_PER_IN` | macro | `src/css_length.c:21` | `#define CL_PX_PER_IN` |
| `cl_ctx_initial` | function | `src/css_length.c:100` | `cl_ctx cl_ctx_initial(void)` |
| `cl_em_refit` | function | `src/css_length.c:219` | `double cl_em_refit(double px, double em, double from_font_size, double font_size)` |
| `cl_font_size` | function | `src/css_length.c:56` | `static double cl_font_size(const cl_ctx *ctx)` |
| `cl_is_length_unit` | function | `src/css_length.c:167` | `int cl_is_length_unit(const char *unit, size_t unit_len)` |
| `cl_lp_used` | function | `src/css_length.c:395` | `double cl_lp_used(cl_lp lp, double basis)` |
| `cl_metric_or` | function | `src/css_length.c:67` | `static double cl_metric_or(double measured, double ratio, const cl_ctx *ctx)` |
| `cl_number` | function | `src/css_length.c:292` | `int cl_number(const char *s, double *out, const char **endp)` |
| `cl_parse_number` | function | `src/css_length.c:233` | `static int cl_parse_number(const char **pp, const char *end, double *out)` |
| `cl_resolve` | function | `src/css_length.c:377` | `cl_status cl_resolve(const char *value, const cl_ctx *ctx, double *out_px)` |
| `cl_resolve_core` | function | `src/css_length.c:309` | `static cl_status cl_resolve_core(const char *value, const cl_ctx *ctx, cl_lp *out)` |
| `cl_resolve_lp` | function | `src/css_length.c:391` | `cl_status cl_resolve_lp(const char *value, const cl_ctx *ctx, cl_lp *out)` |
| `cl_root_font_size` | function | `src/css_length.c:60` | `static double cl_root_font_size(const cl_ctx *ctx)` |
| `cl_unit_eq` | function | `src/css_length.c:30` | `static int cl_unit_eq(const char *unit, size_t len, const char *lit)` |
| `cl_unit_is_font_relative` | function | `src/css_length.c:174` | `int cl_unit_is_font_relative(const char *unit, size_t unit_len)` |
| `cl_unit_scale` | function | `src/css_length.c:117` | `cl_status cl_unit_scale(const char *unit, size_t unit_len,                         const cl_ctx *...` |
| `cl_viewport_scale` | function | `src/css_length.c:80` | `static int cl_viewport_scale(const char *u, size_t len, const cl_ctx *ctx, double *per)` |
| `know` | function | `src/css_length.c:7` | `* this module cannot know (real font metrics, the viewport) arrives through  * cl_ctx rather than...` |
| `CM_MAX_TOKS` | macro | `src/css_mask.c:9` | `#define CM_MAX_TOKS` |
| `CM_TOK_MAX` | macro | `src/css_mask.c:8` | `#define CM_TOK_MAX` |
| `clip_word` | function | `src/css_mask.c:104` | `static int clip_word(const char *t)` |
| `cm_decode_layer` | function | `src/css_mask.c:45` | `void cm_decode_layer(int meta, int alphas, int poss, cm_layer *out)` |
| `cm_encode_layer` | function | `src/css_mask.c:24` | `void cm_encode_layer(const cm_layer *l, int *meta, int *alphas, int *poss)` |
| `cm_expand` | function | `src/css_mask.c:181` | `int cm_expand(const char *prop, const char *val, css_decl *dst, int cap, int webkit_vocab)` |
| `cm_is_mask_prop` | function | `src/css_mask.c:17` | `int cm_is_mask_prop(const char *prop)` |
| `composite_word` | function | `src/css_mask.c:90` | `static int composite_word(const char *t, int webkit)` |
| `emit_layers` | function | `src/css_mask.c:130` | `static int emit_layers(css_decl *dst, int cap, int shorthand, const char *val)` |
| `ieq` | function | `src/css_mask.c:11` | `static int ieq(const char *a, const char *b)` |
| `image_layer` | function | `src/css_mask.c:112` | `static int image_layer(const char *tok, cm_layer *l)` |
| `split` | function | `src/css_mask.c:63` | `static int split(const char *s, int comma, char (*out)[CM_TOK_MAX], int max)` |
| `CMQ_CM_PER_IN` | macro | `src/css_mq.c:23` | `#define CMQ_CM_PER_IN` |
| `CMQ_COLOR_BITS` | macro | `src/css_mq.c:21` | `#define CMQ_COLOR_BITS` |
| `CMQ_DEVICE_H` | macro | `src/css_mq.c:19` | `#define CMQ_DEVICE_H` |
| `CMQ_DEVICE_W` | macro | `src/css_mq.c:18` | `#define CMQ_DEVICE_W` |
| `CMQ_DPI_PER_DPPX` | macro | `src/css_mq.c:22` | `#define CMQ_DPI_PER_DPPX` |
| `CMQ_DPPX` | macro | `src/css_mq.c:20` | `#define CMQ_DPPX` |
| `MQ_EPS` | macro | `src/css_mq.c:203` | `#define MQ_EPS` |
| `and3` | function | `src/css_mq.c:66` | `static int and3(int a, int b)` |
| `bool_ctx` | function | `src/css_mq.c:229` | `static int bool_ctx(const fval *v)` |
| `cmp_op` | function | `src/css_mq.c:206` | `static int cmp_op(double lhs, int op, double rhs)` |
| `cmq_matches` | function | `src/css_mq.c:458` | `int cmq_matches(const char *s, size_t len, const cmq_env *env)` |
| `copy_trim_lower` | function | `src/css_mq.c:83` | `static int copy_trim_lower(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `eval_cond` | function | `src/css_mq.c:380` | `static int eval_cond(mq_cur *c, int depth)` |
| `eval_feature` | function | `src/css_mq.c:328` | `static int eval_feature(const char *s, size_t a, size_t b, const cmq_env *env)` |
| `eval_in_parens` | function | `src/css_mq.c:353` | `static int eval_in_parens(mq_cur *c, int depth)` |
| `eval_plain` | function | `src/css_mq.c:237` | `static int eval_plain(const char *name, const char *value, const cmq_env *env)` |
| `eval_query` | function | `src/css_mq.c:404` | `static int eval_query(const char *s, size_t a, size_t b, const cmq_env *env)` |
| `eval_range` | function | `src/css_mq.c:280` | `static int eval_range(const char *t, const cmq_env *env)` |
| `feature_of` | function | `src/css_mq.c:106` | `static fval feature_of(const char *name, const cmq_env *env)` |
| `flip_op` | function | `src/css_mq.c:218` | `static int flip_op(int op)` |
| `fval` | struct | `src/css_mq.c:96` | `` |
| `is_ident_ch` | function | `src/css_mq.c:39` | `static int is_ident_ch(char c)` |
| `is_space` | function | `src/css_mq.c:35` | `static int is_space(char c)` |
| `kind` | type_alias | `src/css_mq.c:95` | `typedef struct fval { fv_kind kind;` |
| `lower_ch` | function | `src/css_mq.c:31` | `static char lower_ch(char c)` |
| `mq_cur` | struct | `src/css_mq.c:25` | `` |
| `not3` | function | `src/css_mq.c:78` | `static int not3(int a)` |
| `or3` | function | `src/css_mq.c:72` | `static int or3(int a, int b)` |
| `parse_value` | function | `src/css_mq.c:167` | `static int parse_value(const char *t, int unit, double *out)` |
| `peek_word` | function | `src/css_mq.c:61` | `static int peek_word(const mq_cur *c, char *w, size_t cap)` |
| `read_num` | function | `src/css_mq.c:162` | `static int read_num(const char *t, double *out, const char **end)` |
| `read_op` | function | `src/css_mq.c:266` | `static int read_op(const char **p)` |
| `read_word` | function | `src/css_mq.c:49` | `static int read_word(mq_cur *c, char *w, size_t cap)` |
| `skip_ws` | function | `src/css_mq.c:44` | `static void skip_ws(mq_cur *c)` |
| `HAS_MAX_DEPTH` | macro | `src/css_select.c:845` | `#define HAS_MAX_DEPTH` |
| `attr_matches` | function | `src/css_select.c:694` | `static int attr_matches(const css_attr_match *am, const css_element *el)` |
| `between` | function | `src/css_select.c:382` | `* between ( and ) is split on commas (not inside [] or ());` |
| `built` | function | `src/css_select.c:1021` | `* chains the caller built (an element without parent/prev links never matches  * through that com...` |
| `compound_matches` | function | `src/css_select.c:986` | `static int compound_matches(const css_compound *c, const css_element *el,                        ...` |
| `csel_decl_end` | function | `src/css_select.c:104` | `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace)` |
| `csel_emit_utf8` | function | `src/css_select.c:30` | `size_t csel_emit_utf8(unsigned int cp, char *out)` |
| `csel_escape_len` | function | `src/css_select.c:91` | `size_t csel_escape_len(const char *s, size_t i, size_t b)` |
| `csel_hex_val` | function | `src/css_select.c:23` | `int csel_hex_val(char c)` |
| `csel_ident_eq` | function | `src/css_select.c:142` | `int csel_ident_eq(const char *stored, const char *tok, size_t tlen)` |
| `csel_ident_fold` | function | `src/css_select.c:127` | `void csel_ident_fold(const char *src, size_t len, char *dst)` |
| `csel_matches` | function | `src/css_select.c:1062` | `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,               ...` |
| `csel_read_ident` | function | `src/css_select.c:150` | `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower)` |
| `csel_unescape` | function | `src/css_select.c:52` | `void csel_unescape(char *dst, size_t cap, const char *src, size_t n)` |
| `el_attr_value` | function | `src/css_select.c:661` | `static const char *el_attr_value(const css_element *el, const char *name)` |
| `ends_with` | function | `src/css_select.c:671` | `static int ends_with(const char *v, const char *suf, int ci)` |
| `has_word` | function | `src/css_select.c:679` | `static int has_word(const char *v, const char *w, int ci)` |
| `ident_hash` | function | `src/css_select.c:121` | `static unsigned long long ident_hash(const char *s, size_t n)` |
| `is_form_control` | function | `src/css_select.c:723` | `static int is_form_control(const char *tag)` |
| `nth_matches` | function | `src/css_select.c:714` | `static int nth_matches(int A, int B, int idx)` |
| `parse_attr_sel` | function | `src/css_select.c:184` | `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)` |
| `parse_compound` | function | `src/css_select.c:523` | `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,                   ...` |
| `parse_nth_arg` | function | `src/css_select.c:241` | `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)` |
| `parse_sub_compound` | function | `src/css_select.c:458` | `static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub)` |
| `pseudo_matches` | function | `src/css_select.c:732` | `static int pseudo_matches(const css_pseudo_match *pm, const css_element *el, const css_sel *sel, const char...` |
| `selector` | function | `src/css_select.c:565` | `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is  * dropped. Whitespa...` |
| `simple_pseudo_kind` | function | `src/css_select.c:437` | `static int simple_pseudo_kind(const char *nm)` |
| `sub_sel_matches` | function | `src/css_select.c:736` | `static int sub_sel_matches(const css_sub_sel *sub, const css_element *el)` |
| `take_sub_arg` | function | `src/css_select.c:293` | `static int take_sub_arg(const char *s, size_t a, size_t b, css_sel *sel, int strict);` |
| `ct_emit_spacing` | function | `src/css_text.c:300` | `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `ct_expand_shadow` | function | `src/css_text.c:313` | `int ct_expand_shadow(const char *val, css_decl *dst, int cap)` |
| `ct_expand_valign` | function | `src/css_text.c:122` | `int ct_expand_valign(const char *val, css_decl *dst, int cap)` |
| `ct_family_of` | function | `src/css_text.c:18` | `static int ct_family_of(const char *name)` |
| `ct_interp_aspect_ratio` | function | `src/css_text.c:194` | `int ct_interp_aspect_ratio(const char *v, int *num, int *den)` |
| `ct_interp_direction` | function | `src/css_text.c:227` | `int ct_interp_direction(const char *v)` |
| `ct_interp_fontfamily` | function | `src/css_text.c:47` | `int ct_interp_fontfamily(const char *v)` |
| `ct_interp_liststyle` | function | `src/css_text.c:265` | `int ct_interp_liststyle(const char *v)` |
| `ct_interp_tabsize` | function | `src/css_text.c:160` | `int ct_interp_tabsize(const char *v)` |
| `ct_interp_textdeco_style` | function | `src/css_text.c:171` | `int ct_interp_textdeco_style(const char *v)` |
| `ct_interp_textdeco_thickness` | function | `src/css_text.c:182` | `int ct_interp_textdeco_thickness(const char *v)` |
| `ct_interp_texttransform` | function | `src/css_text.c:69` | `int ct_interp_texttransform(const char *v)` |
| `ct_interp_transition_property` | function | `src/css_text.c:139` | `int ct_interp_transition_property(const char *v)` |
| `ct_interp_valign` | function | `src/css_text.c:91` | `int ct_interp_valign(const char *v)` |
| `ct_interp_whitespace` | function | `src/css_text.c:147` | `int ct_interp_whitespace(const char *v)` |
| `ct_liststyle_kw` | function | `src/css_text.c:233` | `static int ct_liststyle_kw(const char *t)` |
| `ct_liststyle_unknown_name` | function | `src/css_text.c:254` | `static int ct_liststyle_unknown_name(const char *t)` |
| `cv_bg_alpha_of` | function | `src/css_values.c:46` | `int cv_bg_alpha_of(const char *v)` |
| `cv_color_ok` | function | `src/css_values.c:41` | `int cv_color_ok(int c)` |
| `cv_filter_scale` | function | `src/css_values.c:231` | `double cv_filter_scale(int pct)` |
| `cv_interp_bg` | function | `src/css_values.c:160` | `int cv_interp_bg(const char *v)` |
| `cv_interp_color` | function | `src/css_values.c:36` | `int cv_interp_color(const char *v)` |
| `cv_parse_color` | function | `src/css_values.c:16` | `int cv_parse_color(const char *v)` |
| `cv_parse_color_t7` | function | `src/css_values.c:205` | `int cv_parse_color_t7(const char *v)` |
| `cv_parse_num` | function | `src/css_values.c:11` | `static int cv_parse_num(const char *s, double *out, const char **endp)` |
| `cv_text_color` | function | `src/css_values.c:222` | `int cv_text_color(const char *v)` |
| `cvr_collect_decls` | function | `src/css_vars.c:139` | `void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b)` |
| `cvr_count` | function | `src/css_vars.c:100` | `size_t cvr_count(const cvr_table *t)` |
| `cvr_free` | function | `src/css_vars.c:112` | `void cvr_free(cvr_table *t)` |
| `cvr_get` | function | `src/css_vars.c:94` | `const char *cvr_get(const cvr_table *t, const char *name, size_t nlen)` |
| `cvr_lookup` | function | `src/css_vars.c:239` | `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen)` |
| `cvr_reset` | function | `src/css_vars.c:102` | `void cvr_reset(cvr_table *t)` |
| `cvr_resolve` | function | `src/css_vars.c:230` | `int cvr_resolve(const char *val, char *out, size_t outcap, const cvr_scope *sc)` |
| `cvr_set` | function | `src/css_vars.c:67` | `int cvr_set(cvr_table *t, const char *name, size_t nlen, const char *value, size_t vlen)` |
| `dup_n` | function | `src/css_vars.c:21` | `static char *dup_n(const char *s, size_t n)` |
| `find_slot` | function | `src/css_vars.c:32` | `static size_t find_slot(const cvr_table *t, const char *name, size_t nlen)` |
| `grow` | function | `src/css_vars.c:45` | `static int grow(cvr_table *t)` |
| `is_ws` | function | `src/css_vars.c:120` | `static int is_ws(char c)` |
| `name_hash` | function | `src/css_vars.c:12` | `static size_t name_hash(const char *s, size_t n)` |
| `resolve_rec` | function | `src/css_vars.c:178` | `static int resolve_rec(const char *val, size_t vlen, char *out, size_t outcap,                   ...` |
| `scope_get` | function | `src/css_vars.c:164` | `static const char *scope_get(const cvr_scope *sc, const char *name, size_t nlen)` |
| `without_important` | function | `src/css_vars.c:124` | `static size_t without_important(const char *val, size_t n)` |
| `ascii_ws` | function | `src/data_url.c:115` | `static int ascii_ws(char c)` |
| `b64_val` | function | `src/data_url.c:61` | `static int b64_val(unsigned char c)` |
| `ci_starts_with` | function | `src/data_url.c:20` | `static int ci_starts_with(const char *s, const char *prefix)` |
| `du_base64_decode` | function | `src/data_url.c:70` | `du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len)` |
| `du_base64_payload` | function | `src/data_url.c:32` | `du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len)` |
| `du_decode` | function | `src/data_url.c:131` | `du_status du_decode(const char *url, char *mime, size_t mime_cap, uint8_t **out, size_t *out_len)` |
| `du_is_data_url` | function | `src/data_url.c:28` | `int du_is_data_url(const char *url)` |
| `ends_ci` | function | `src/data_url.c:120` | `static int ends_ci(const char *s, size_t n, const char *suf)` |
| `hexval` | function | `src/data_url.c:108` | `static int hexval(char c)` |
| `lower` | function | `src/data_url.c:16` | `static int lower(char c)` |
| `_POSIX_C_SOURCE` | macro | `src/disk_store.c:11` | `#define _POSIX_C_SOURCE` |
| `ds_free` | function | `src/disk_store.c:136` | `void ds_free(uint8_t *buf, size_t len)` |
| `ds_read` | function | `src/disk_store.c:103` | `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],                   uint8_t **ou...` |
| `ds_write` | function | `src/disk_store.c:66` | `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,                ...` |
| `fsync_dir` | function | `src/disk_store.c:32` | `static void fsync_dir(const char *path)` |
| `map_ls` | function | `src/disk_store.c:50` | `static ds_status map_ls(ls_status s)` |
| `DOM_QS_MAX_SELECTORS` | macro | `src/dom.c:380` | `#define DOM_QS_MAX_SELECTORS` |
| `IH_BLOCK_SIZE` | macro | `src/dom.c:818` | `#define IH_BLOCK_SIZE` |
| `_POSIX_C_SOURCE` | macro | `src/dom.c:11` | `#define _POSIX_C_SOURCE` |
| `char_kind` | function | `src/dom.c:981` | `static int char_kind(const lxb_dom_node_t *n)` |
| `copy_ids` | function | `src/dom.c:354` | `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)` |
| `count` | function | `src/dom.c:437` | `* count (may exceed cap), and returns DOM_NODE_NONE. */ static dom_node_id qs_walk(const dom_inde...` |
| `dom_append_child` | function | `src/dom.c:710` | `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)` |
| `dom_attribute_names` | function | `src/dom.c:586` | `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,                            con...` |
| `dom_build` | function | `src/dom.c:291` | `dom_status dom_build(const hp_document *doc, dom_index **out)` |
| `dom_child_node` | function | `src/dom.c:1004` | `dom_node_id dom_child_node(dom_index *idx, dom_node_id node, int last)` |
| `dom_clone_node` | function | `src/dom.c:934` | `dom_status dom_clone_node(dom_index *idx, dom_node_id node, int deep, dom_node_id *out_id)` |
| `dom_closest` | function | `src/dom.c:496` | `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,                         const cha...` |
| `dom_create_char_node` | function | `src/dom.c:1018` | `dom_status dom_create_char_node(dom_index *idx, int kind, const char *text, size_t len,          ...` |
| `dom_create_element` | function | `src/dom.c:690` | `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)` |
| `dom_document_position` | function | `src/dom.c:512` | `size_t dom_document_position(const dom_index *idx, dom_node_id node)` |
| `dom_document_title` | function | `src/dom.c:614` | `const char *dom_document_title(const dom_index *idx, size_t *len)` |
| `dom_first_child` | function | `src/dom.c:537` | `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)` |
| `dom_free` | function | `src/dom.c:332` | `void dom_free(dom_index *idx)` |
| `dom_get_attribute` | function | `src/dom.c:564` | `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,                            ...` |
| `dom_get_by_class` | function | `src/dom.c:370` | `size_t dom_get_by_class(const dom_index *idx, const char *cls,                         dom_node_i...` |
| `dom_get_by_tag` | function | `src/dom.c:361` | `size_t dom_get_by_tag(const dom_index *idx, const char *tag,                       dom_node_id *o...` |
| `dom_get_element_by_id` | function | `src/dom.c:348` | `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)` |
| `dom_get_inner_html` | function | `src/dom.c:887` | `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,                            ...` |
| `dom_index` | struct | `src/dom.c:220` | `` |
| `dom_insert_before` | function | `src/dom.c:917` | `dom_status dom_insert_before(dom_index *idx, dom_node_id parent, dom_node_id child,              ...` |
| `dom_matches` | function | `src/dom.c:487` | `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)` |
| `dom_move_children` | function | `src/dom.c:948` | `dom_status dom_move_children(dom_index *idx, dom_node_id src, dom_node_id parent,                ...` |
| `dom_next_sibling` | function | `src/dom.c:545` | `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)` |
| `dom_node_at` | function | `src/dom.c:522` | `dom_node_id dom_node_at(const dom_index *idx, size_t position)` |
| `dom_node_count` | function | `src/dom.c:344` | `size_t dom_node_count(const dom_index *idx)` |
| `dom_node_kind` | function | `src/dom.c:1000` | `int dom_node_kind(const dom_index *idx, dom_node_id node)` |
| `dom_parent` | function | `src/dom.c:527` | `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)` |
| `dom_precedes` | function | `src/dom.c:517` | `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)` |
| `dom_query_selector` | function | `src/dom.c:467` | `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,                           ...` |
| `dom_query_selector_all` | function | `src/dom.c:476` | `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,                            ...` |
| `dom_remove_attribute` | function | `src/dom.c:761` | `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)` |
| `dom_remove_child` | function | `src/dom.c:724` | `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)` |
| `dom_set_attribute` | function | `src/dom.c:732` | `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,                              const...` |
| `dom_set_document_title` | function | `src/dom.c:661` | `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)` |
| `dom_set_inner_html` | function | `src/dom.c:780` | `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,                               con...` |
| `dom_set_text_content` | function | `src/dom.c:627` | `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,                                ...` |
| `dom_sibling_node` | function | `src/dom.c:1011` | `dom_node_id dom_sibling_node(dom_index *idx, dom_node_id node, int prev)` |
| `dom_tag_name` | function | `src/dom.c:553` | `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)` |
| `dom_text_content` | function | `src/dom.c:604` | `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)` |
| `handle_of` | function | `src/dom.c:992` | `static dom_node_id handle_of(dom_index *idx, lxb_dom_node_t *n)` |
| `id_of` | function | `src/dom.c:383` | `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)` |
| `idx_push` | function | `src/dom.c:672` | `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)` |
| `ih_acc` | struct | `src/dom.c:825` | `` |
| `ih_append` | function | `src/dom.c:833` | `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)` |
| `ih_block` | struct | `src/dom.c:820` | `` |
| `ih_free` | function | `src/dom.c:860` | `static void ih_free(ih_acc *a)` |
| `index_element` | function | `src/dom.c:254` | `static int index_element(dom_index *idx, lxb_dom_element_t *el, dom_node_id id)` |
| `index_subtree` | function | `src/dom.c:770` | `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)` |
| `node_matches_any` | function | `src/dom.c:426` | `static int node_matches_any(const lxb_dom_node_t *cn,                             const css_sel *...` |
| `node_next` | function | `src/dom.c:232` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `parse_selector_list` | function | `src/dom.c:393` | `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)` |
| `pm_entry` | struct | `src/dom.c:154` | `` |
| `pm_free` | function | `src/dom.c:211` | `static void pm_free(ptrmap *m)` |
| `pm_get` | function | `src/dom.c:200` | `static int pm_get(const ptrmap *m, const void *key, dom_node_id *out)` |
| `pm_grow` | function | `src/dom.c:166` | `static int pm_grow(ptrmap *m)` |
| `pm_put` | function | `src/dom.c:183` | `static int pm_put(ptrmap *m, const void *key, dom_node_id id)` |
| `ptr_hash` | function | `src/dom.c:45` | `static size_t ptr_hash(const void *p)` |
| `ptrmap` | struct | `src/dom.c:160` | `` |
| `sm_entry` | struct | `src/dom.c:55` | `` |
| `sm_entry_append` | function | `src/dom.c:70` | `static int sm_entry_append(sm_entry *e, dom_node_id id)` |
| `sm_find` | function | `src/dom.c:127` | `static const sm_entry *sm_find(const strmap *m, const char *key, size_t klen)` |
| `sm_free` | function | `src/dom.c:139` | `static void sm_free(strmap *m)` |
| `sm_grow` | function | `src/dom.c:82` | `static int sm_grow(strmap *m)` |
| `sm_put` | function | `src/dom.c:99` | `static int sm_put(strmap *m, const char *key, size_t klen, dom_node_id id)` |
| `strmap` | struct | `src/dom.c:64` | `` |
| `to_lower_buf` | function | `src/dom.c:33` | `static int to_lower_buf(const char *s, size_t n, char *out, size_t outcap)` |
| `valid` | function | `src/dom.c:242` | `static int valid(const dom_index *idx, dom_node_id n)` |
| `dd_align_name` | function | `src/dom_debug.c:108` | `static const char *dd_align_name(int a)` |
| `dd_block_line` | function | `src/dom_debug.c:323` | `static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b)` |
| `dd_border_style_name` | function | `src/dom_debug.c:228` | `static const char *dd_border_style_name(int s)` |
| `dd_box_line` | function | `src/dom_debug.c:261` | `static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b)` |
| `dd_color` | function | `src/dom_debug.c:83` | `static void dd_color(dd_cursor *c, int rgb)` |
| `dd_cursor` | struct | `src/dom_debug.c:24` | `` |
| `dd_cursor_name` | function | `src/dom_debug.c:166` | `static const char *dd_cursor_name(int c)` |
| `dd_display_name` | function | `src/dom_debug.c:88` | `static const char *dd_display_name(int d)` |
| `dd_emit` | function | `src/dom_debug.c:36` | `static void dd_emit(dd_cursor *c, const char *s, size_t len)` |
| `dd_format` | function | `src/dom_debug.c:399` | `size_t dd_format(const rd_doc *doc, char *out, size_t cap)` |
| `dd_format_css` | function | `src/dom_debug.c:431` | `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)` |
| `dd_image_rendering_name` | function | `src/dom_debug.c:219` | `static const char *dd_image_rendering_name(int r)` |
| `dd_inset` | function | `src/dom_debug.c:204` | `static int dd_inset(int v)` |
| `dd_justify_name` | function | `src/dom_debug.c:96` | `static const char *dd_justify_name(int j)` |
| `dd_mix_blend_name` | function | `src/dom_debug.c:137` | `static const char *dd_mix_blend_name(int m)` |
| `dd_object_fit_name` | function | `src/dom_debug.c:208` | `static const char *dd_object_fit_name(int o)` |
| `dd_overflow_name` | function | `src/dom_debug.c:157` | `static const char *dd_overflow_name(int o)` |
| `dd_position_name` | function | `src/dom_debug.c:118` | `static const char *dd_position_name(int p)` |
| `dd_printf` | function | `src/dom_debug.c:48` | `static void dd_printf(dd_cursor *c, const char *fmt, ...)` |
| `dd_putc` | function | `src/dom_debug.c:31` | `static void dd_putc(dd_cursor *c, char ch)` |
| `dd_puts` | function | `src/dom_debug.c:40` | `static void dd_puts(dd_cursor *c, const char *s)` |
| `dd_text_overflow_name` | function | `src/dom_debug.c:199` | `static const char *dd_text_overflow_name(int t)` |
| `dd_visibility_name` | function | `src/dom_debug.c:129` | `static const char *dd_visibility_name(int v)` |
| `dd_w` | function | `src/dom_debug.c:80` | `static int dd_w(int v)` |
| `ci_find` | function | `src/download.c:19` | `static const char *ci_find(const char *hay, const char *needle)` |
| `copy_span` | function | `src/download.c:85` | `static void copy_span(const char *src, const char *end, char *buf, size_t bufsz)` |
| `dl_build_path` | function | `src/download.c:195` | `dl_status dl_build_path(const char *dir, const char *name, char *out, size_t outsz)` |
| `dl_check_size` | function | `src/download.c:213` | `dl_status dl_check_size(size_t len)` |
| `dl_ext_for_type` | function | `src/download.c:58` | `const char *dl_ext_for_type(const char *content_type)` |
| `dl_pick_name` | function | `src/download.c:153` | `dl_status dl_pick_name(const char *url, const char *content_disposition,                        c...` |
| `dl_should_download` | function | `src/download.c:47` | `int dl_should_download(const char *content_type, const char *content_disposition)` |
| `extract_disposition_name` | function | `src/download.c:96` | `static int extract_disposition_name(const char *cd, char *buf, size_t bufsz)` |
| `extract_url_name` | function | `src/download.c:134` | `static int extract_url_name(const char *url, char *buf, size_t bufsz)` |
| `has_extension` | function | `src/download.c:148` | `static int has_extension(const char *name)` |
| `lc` | function | `src/download.c:13` | `static int lc(int c)` |
| `media_type` | function | `src/download.c:33` | `static void media_type(const char *content_type, char *buf, size_t bufsz)` |
| `FX_EPS` | macro | `src/flex_layout.c:16` | `#define FX_EPS` |
| `area_token_is_null_cell` | function | `src/flex_layout.c:343` | `static int area_token_is_null_cell(const char *tok, size_t len)` |
| `float_pack_impl` | function | `src/flex_layout.c:466` | `static fx_status float_pack_impl(const double *width, const int *side, size_t n,                 ...` |
| `fx_auto_margins` | function | `src/flex_layout.c:605` | `fx_status fx_auto_margins(fx_result *res, size_t n, const unsigned char *auto_l,                 ...` |
| `fx_auto_min_size` | function | `src/flex_layout.c:628` | `double fx_auto_min_size(double min_content, double basis, double author_min,                     ...` |
| `fx_autofill_count` | function | `src/flex_layout.c:133` | `size_t fx_autofill_count(double avail, double gap, double minw)` |
| `fx_col_free_split` | function | `src/flex_layout.c:930` | `fx_status fx_col_free_split(double free_px, const int *grow, const int *mauto, size_t n,         ...` |
| `fx_column_place` | function | `src/flex_layout.c:725` | `fx_status fx_column_place(const double *h, const double *grow, size_t n, double gap,             ...` |
| `fx_column_place_m` | function | `src/flex_layout.c:732` | `fx_status fx_column_place_m(const double *h, const double *grow, const int *mauto,               ...` |
| `fx_cross_offset` | function | `src/flex_layout.c:793` | `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r)` |
| `fx_flex_line` | function | `src/flex_layout.c:23` | `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,                 ...` |
| `fx_float_insets` | function | `src/flex_layout.c:506` | `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,                  ...` |
| `fx_float_pack` | function | `src/flex_layout.c:546` | `fx_status fx_float_pack(const double *width, const int *side, size_t n,                         d...` |
| `fx_float_pack_wrap` | function | `src/flex_layout.c:551` | `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,                     ...` |
| `fx_grid_area_hash` | function | `src/flex_layout.c:319` | `unsigned fx_grid_area_hash(const char *name)` |
| `fx_grid_area_rect` | function | `src/flex_layout.c:424` | `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,                             int ...` |
| `fx_grid_areas_parse` | function | `src/flex_layout.c:349` | `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)` |
| `fx_grid_cell` | function | `src/flex_layout.c:593` | `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)` |
| `fx_grid_columns` | function | `src/flex_layout.c:128` | `fx_status fx_grid_columns(double avail, size_t ncols, double gap,                           doubl...` |
| `fx_grid_columns_weighted` | function | `src/flex_layout.c:143` | `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,                       ...` |
| `fx_grid_line_parse` | function | `src/flex_layout.c:868` | `int fx_grid_line_parse(const char *v, int *start, int *end)` |
| `fx_grid_line_resolve` | function | `src/flex_layout.c:888` | `void fx_grid_line_resolve(int start, int end, int ntracks, int *pos0, int *span)` |
| `fx_grid_line_side` | function | `src/flex_layout.c:860` | `int fx_grid_line_side(const char *s, int *out)` |
| `fx_grid_place_span` | function | `src/flex_layout.c:177` | `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,                       ...` |
| `fx_justify_name` | function | `src/flex_layout.c:713` | `const char *fx_justify_name(fx_justify j)` |
| `fx_multicol_balance` | function | `src/flex_layout.c:682` | `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,                         ...` |
| `fx_multicol_used` | function | `src/flex_layout.c:645` | `fx_status fx_multicol_used(double avail_w, int column_count, double column_width,                ...` |
| `gl_int` | function | `src/flex_layout.c:822` | `static int gl_int(const char *p, const char *end, long cap, long *out)` |
| `gl_is_line` | function | `src/flex_layout.c:886` | `static int gl_is_line(int v)` |
| `gl_is_span` | function | `src/flex_layout.c:885` | `static int gl_is_span(int v)` |
| `gl_kw` | function | `src/flex_layout.c:812` | `static int gl_kw(const char *p, const char *end, const char *kw)` |
| `gl_lower` | function | `src/flex_layout.c:809` | `static int gl_lower(char c)` |
| `gl_side_range` | function | `src/flex_layout.c:837` | `static int gl_side_range(const char *p, const char *end, int *out)` |
| `gl_ws` | function | `src/flex_layout.c:805` | `static int gl_ws(char c)` |
| `nn` | function | `src/flex_layout.c:19` | `static double nn(double v)` |
| `clean_action` | function | `src/form.c:75` | `static int clean_action(const char *action, char *out, size_t outsz)` |
| `copy_fit` | function | `src/form.c:66` | `static int copy_fit(char *dst, size_t dstsz, const char *src)` |
| `enc_component` | function | `src/form.c:25` | `static int enc_component(const char *s, char *out, size_t outsz, size_t *pos)` |
| `fm_build` | function | `src/form.c:120` | `fm_status fm_build(const char *base, const char *action, fm_method method,                    con...` |
| `fm_encode` | function | `src/form.c:43` | `fm_status fm_encode(const fm_field *fields, size_t n,                     char *out, size_t outsz...` |
| `put_char` | function | `src/form.c:17` | `static int put_char(char *out, size_t outsz, size_t *pos, char c)` |
| `resolve_target` | function | `src/form.c:101` | `static fm_block_reason resolve_target(const char *base, const char *act,                         ...` |
| `strip_query` | function | `src/form.c:93` | `static void strip_query(char *url)` |
| `FC_DEFAULT_INTERVAL_MS` | macro | `src/frame_clock.c:8` | `#define FC_DEFAULT_INTERVAL_MS` |
| `fc_interval_ms` | function | `src/frame_clock.c:26` | `int fc_interval_ms(const fc_clock *c)` |
| `fc_needs_tick` | function | `src/frame_clock.c:21` | `int fc_needs_tick(const fc_clock *c)` |
| `fc_set_active` | function | `src/frame_clock.c:16` | `void fc_set_active(fc_clock *c, int active)` |
| `fb_buffer_at` | function | `src/freebug.c:105` | `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)` |
| `fb_buffer_count` | function | `src/freebug.c:101` | `size_t fb_buffer_count(const fb_buffer *b)` |
| `fb_buffer_free` | function | `src/freebug.c:91` | `void fb_buffer_free(fb_buffer *b)` |
| `fb_buffer_init` | function | `src/freebug.c:15` | `void fb_buffer_init(fb_buffer *b)` |
| `fb_buffer_push` | function | `src/freebug.c:19` | `int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)` |
| `fb_buffer_push_loc` | function | `src/freebug.c:23` | `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len,                    ...` |
| `fb_buffer_reset` | function | `src/freebug.c:78` | `void fb_buffer_reset(fb_buffer *b)` |
| `fb_level_name` | function | `src/freebug.c:110` | `const char *fb_level_name(int level)` |
| `whole` | function | `src/freebug.c:5` | `* FB_MAX_TOTAL_BYTES is dropped whole (overflow flag raised, prior entries kept);` |
| `BLOCKED` | function | `src/freedom.c:917` | `* is BLOCKED (fail closed), never leaked over the clearnet. */ nr_route route = nr_route_for(url, global_net);` |
| `CSS_DROPS_REPORT_MAX` | macro | `src/freedom.c:167` | `#define CSS_DROPS_REPORT_MAX` |
| `EXIT_ERROR` | macro | `src/freedom.c:48` | `#define EXIT_ERROR` |
| `EXIT_OK` | macro | `src/freedom.c:47` | `#define EXIT_OK` |
| `EXIT_USAGE` | macro | `src/freedom.c:49` | `#define EXIT_USAGE` |
| `HL_FONT_MAX_BYTES` | macro | `src/freedom.c:556` | `#define HL_FONT_MAX_BYTES` |
| `HL_FONT_MAX_SHEETS` | macro | `src/freedom.c:555` | `#define HL_FONT_MAX_SHEETS` |
| `HL_JS_NAV_MAX` | macro | `src/freedom.c:886` | `#define HL_JS_NAV_MAX` |
| `_DEFAULT_SOURCE` | macro | `src/freedom.c:10` | `#define _DEFAULT_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `src/freedom.c:9` | `#define _POSIX_C_SOURCE` |
| `apply_as_gui` | function | `src/freedom.c:247` | `static void apply_as_gui(const char *top_url, int flag_js, int flag_css, int flag_images)` |
| `elsewhere` | function | `src/freedom.c:952` | `* page whose script immediately forwards elsewhere (e.g. a search engine's  * JS-capability inter...` |
| `fetch_and_render_one` | function | `src/freedom.c:890` | `static int fetch_and_render_one(const char *url, char **out_nav)` |
| `first` | function | `src/freedom.c:702` | `* always cleared first (fetch_and_render may paint several pages per      * process). A NULL top_...` |
| `foldback_cookies` | function | `src/freedom.c:497` | `static void foldback_cookies(const char *url, const char *jar)` |
| `gets` | function | `src/freedom.c:431` | `* gate a click gets (https-only, no downgrade, no foreign scheme), so relative * subresources work. Realm-routed...` |
| `headless_fetch` | function | `src/freedom.c:435` | `static int headless_fetch(void *ctx, const char *method, const char *url,                        ...` |
| `headless_load_hosts` | function | `src/freedom.c:236` | `static void headless_load_hosts(void)` |
| `hl_css_sink` | function | `src/freedom.c:579` | `static void hl_css_sink(void *vctx, const char *url,                         const char *body, si...` |
| `hl_font_fetch` | function | `src/freedom.c:616` | `static int hl_font_fetch(void *vctx, const char *url,                          int *out_status, c...` |
| `hl_font_stash` | struct | `src/freedom.c:558` | `` |
| `hl_font_stash_free` | function | `src/freedom.c:566` | `static void hl_font_stash_free(hl_font_stash *s)` |
| `is_blank_text` | function | `src/freedom.c:273` | `static int is_blank_text(const char *s)` |
| `is_http_url` | function | `src/freedom.c:83` | `static int is_http_url(const char *s)` |
| `is_https_url` | function | `src/freedom.c:79` | `static int is_https_url(const char *s)` |
| `is_overlay_http` | function | `src/freedom.c:88` | `static int is_overlay_http(const char *s)` |
| `main` | function | `src/freedom.c:1181` | `int main(int argc, char **argv)` |
| `now_us` | function | `src/freedom.c:142` | `static uint64_t now_us(void)` |
| `only` | function | `src/freedom.c:759` | `* styling for the local render only (no network). --images enables image loading * AND rendering, including remote...` |
| `parent` | function | `src/freedom.c:978` | `* gated by the parent (ln_resolve: a local target stays under the document's  * directory, a remo...` |
| `pool` | function | `src/freedom.c:688` | `* the pool (unconsumed results freed, in-flight fetches joined). */ tab_set_fetcher(t, headless_fetch, (void...` |
| `print_console` | function | `src/freedom.c:379` | `static void print_console(const fb_buffer *log)` |
| `print_css_drops` | function | `src/freedom.c:521` | `static void print_css_drops(const char *html, size_t len)` |
| `print_doc` | function | `src/freedom.c:286` | `static void print_doc(const rd_doc *doc)` |
| `print_dom` | function | `src/freedom.c:396` | `static void print_dom(const rd_doc *doc)` |
| `print_dom_css` | function | `src/freedom.c:411` | `static void print_dom_css(const rd_doc *doc)` |
| `print_usage` | function | `src/freedom.c:51` | `static void print_usage(FILE *fp, const char *prog)` |
| `read_file` | function | `src/freedom.c:218` | `static char *read_file(const char *path, size_t *out_len)` |
| `render_page` | function | `src/freedom.c:625` | `static int render_page(const char *html, size_t len, const char *top_url,                        ...` |
| `run_dump_video` | function | `src/freedom.c:1162` | `static int run_dump_video(const char *url)` |
| `run_headless` | function | `src/freedom.c:1015` | `static int run_headless(const char *target)` |
| `sf_reason` | function | `src/freedom.c:871` | `static const char *sf_reason(sf_status ss)` |
| `timings_dump` | function | `src/freedom.c:156` | `static void timings_dump(void)` |
| `timings_enabled` | function | `src/freedom.c:152` | `static int timings_enabled(void)` |
| `timings_ensure_init` | function | `src/freedom.c:148` | `static void timings_ensure_init(void)` |
| `user_impersonate_enabled` | function | `src/freedom.c:211` | `static int user_impersonate_enabled(void)` |
| `video_fetch_with_fallback` | function | `src/freedom.c:1051` | `static sf_status video_fetch_with_fallback(const char *url, sf_config *cfg,                      ...` |
| `_GNU_SOURCE` | macro | `src/hls.c:21` | `#define _GNU_SOURCE` |

Next: [SYMBOLS_p7.md](SYMBOLS_p7.md)
