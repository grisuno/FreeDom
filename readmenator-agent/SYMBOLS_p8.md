# Symbols (page 8 of 19)
Previous: [SYMBOLS_p7.md](SYMBOLS_p7.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `cb_expand_grid_template_cols` | function | `src/css_box.c:623` | `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `cb_expand_grid_template_rows` | function | `src/css_box.c:646` | `int cb_expand_grid_template_rows(const char *val, css_decl *dst, int cap)` |
| `cb_interp_align` | function | `src/css_box.c:54` | `int cb_interp_align(const char *v)` |
| `cb_interp_display` | function | `src/css_box.c:233` | `int cb_interp_display(const char *v)` |
| `cb_interp_fontsize_ex` | function | `src/css_box.c:72` | `int cb_interp_fontsize_ex(const char *v, int *abs_out)` |
| `cb_interp_gap` | function | `src/css_box.c:313` | `int cb_interp_gap(const char *v)` |
| `cb_interp_justify` | function | `src/css_box.c:320` | `int cb_interp_justify(const char *v)` |
| `cb_interp_len` | function | `src/css_box.c:1042` | `int cb_interp_len(const char *v, int allow_auto, int *out)` |
| `cb_interp_lineheight` | function | `src/css_box.c:145` | `int cb_interp_lineheight(const char *v)` |
| `cb_interp_lp` | function | `src/css_box.c:1175` | `int cb_interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_px, ...` |
| `cb_interp_style` | function | `src/css_box.c:203` | `int cb_interp_style(const char *v)` |
| `cb_interp_textdeco` | function | `src/css_box.c:213` | `int cb_interp_textdeco(const char *v)` |
| `cb_interp_weight` | function | `src/css_box.c:194` | `int cb_interp_weight(const char *v)` |
| `cb_length_px` | function | `src/css_box.c:49` | `int cb_length_px(const char *v, double *px)` |
| `cb_math_length_px` | function | `src/css_box.c:1033` | `int cb_math_length_px(const char *v, double *px)` |
| `cb_parse_num` | function | `src/css_box.c:13` | `static int cb_parse_num(const char *s, double *out, const char **endp)` |
| `cb_starts_with_ci` | function | `src/css_box.c:352` | `static int cb_starts_with_ci(const char *s, const char *pre)` |
| `cb_value_em_milli` | function | `src/css_box.c:1121` | `int cb_value_em_milli(const char *v)` |
| `cb_wide_keyword` | function | `src/css_box.c:18` | `static int cb_wide_keyword(const char *v)` |
| `count_one_repeat` | function | `src/css_box.c:396` | `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,                       ...` |
| `count_tracks` | function | `src/css_box.c:358` | `static int count_tracks(const char *s, size_t n)` |
| `expand_auto_fill` | function | `src/css_box.c:545` | `static int expand_auto_fill(const char *val, css_decl *dst, int cap)` |
| `interp_len` | function | `src/css_box.c:1351` | `* this file that might hand a token to interp_len (transitively: margin/padding/  * inset, flex-b...` |
| `min` | function | `src/css_box.c:807` | `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the...` |
| `pct_slot_of` | function | `src/css_box.c:1071` | `static int pct_slot_of(int slot)` |
| `px` | type_alias | `src/css_box.c:736` | `typedef struct calc_val { double px;` |
| `repeat` | function | `src/css_box.c:341` | `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill\|...) /...` |
| `term` | function | `src/css_box.c:1182` | `* the same expression and failed closed on the percentage term (its property * may not accept one);` |
| `track_min_of` | function | `src/css_box.c:507` | `static int track_min_of(const char *tok)` |
| `track_size_of` | function | `src/css_box.c:366` | `static int track_size_of(const char *tok)` |
| `walk_tracks` | function | `src/css_box.c:439` | `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)` |
| `CCH_ATTR_BUF` | macro | `src/css_chain.c:23` | `#define CCH_ATTR_BUF` |
| `CCH_CLASS_BUF` | macro | `src/css_chain.c:17` | `#define CCH_CLASS_BUF` |
| `CCH_CLASS_SPILL_MAX` | macro | `src/css_chain.c:21` | `#define CCH_CLASS_SPILL_MAX` |
| `CCH_ID_MAX` | macro | `src/css_chain.c:16` | `#define CCH_ID_MAX` |
| `CCH_MAX_ATTRS` | macro | `src/css_chain.c:22` | `#define CCH_MAX_ATTRS` |
| `CCH_MAX_CLASSES` | macro | `src/css_chain.c:18` | `#define CCH_MAX_CLASSES` |
| `CCH_TAG_MAX` | macro | `src/css_chain.c:15` | `#define CCH_TAG_MAX` |
| `cch_element_matches` | function | `src/css_chain.c:467` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)` |
| `cch_element_matches_any` | function | `src/css_chain.c:481` | `int cch_element_matches_any(lxb_dom_element_t *el, const css_sel *sels, size_t n)` |
| `cch_element_style` | function | `src/css_chain.c:463` | `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)` |
| `cch_element_style_path` | function | `src/css_chain.c:374` | `css_style cch_element_style_path(cch_path *pa, lxb_dom_element_t *el, const css_sheet *sheet,    ...` |
| `cch_element_style_vars` | function | `src/css_chain.c:312` | `css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,                  ...` |
| `cch_node` | struct | `src/css_chain.c:27` | `` |
| `cch_path` | struct | `src/css_chain.c:349` | `` |
| `cch_path_free` | function | `src/css_chain.c:367` | `void cch_path_free(cch_path *pa)` |
| `cch_path_new` | function | `src/css_chain.c:355` | `cch_path *cch_path_new(void)` |
| `cch_pseudo_style` | function | `src/css_chain.c:444` | `css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,             ...` |
| `cch_set_target` | function | `src/css_chain.c:494` | `int cch_set_target(lxb_dom_node_t *doc_node, lxb_dom_element_t *el)` |
| `cls_space` | function | `src/css_chain.c:42` | `static int cls_space(char c)` |
| `count_children` | function | `src/css_chain.c:229` | `static int count_children(lxb_dom_node_t *n)` |
| `fill_css_node` | function | `src/css_chain.c:99` | `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)` |
| `inputs` | function | `src/css_chain.c:243` | `* identical inputs (single source of truth). */ static const css_element *build_chain(lxb_dom_ele...` |
| `path_truncate` | function | `src/css_chain.c:359` | `static void path_truncate(cch_path *pa, int keep)` |
| `release_nodes` | function | `src/css_chain.c:90` | `static void release_nodes(cch_node *nodes, int n)` |
| `sibling_position` | function | `src/css_chain.c:183` | `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `sibling_type_position` | function | `src/css_chain.c:201` | `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `tag` | type_alias | `src/css_chain.c:27` | `typedef struct cch_node { char tag[CCH_TAG_MAX];` |
| `CC_CALC_DEPTH` | macro | `src/css_color.c:221` | `#define CC_CALC_DEPTH` |
| `CC_CHANNEL_MAX` | macro | `src/css_color.c:23` | `#define CC_CHANNEL_MAX` |
| `CC_HSL_SCALE` | macro | `src/css_color.c:32` | `#define CC_HSL_SCALE` |
| `CC_NUMBER_MAX_DIGITS` | macro | `src/css_color.c:29` | `#define CC_NUMBER_MAX_DIGITS` |
| `CC_PERCENT_MAX` | macro | `src/css_color.c:24` | `#define CC_PERCENT_MAX` |
| `CC_PI` | macro | `src/css_color.c:577` | `#define CC_PI` |
| `CC_TOKEN_MAX` | macro | `src/css_color.c:20` | `#define CC_TOKEN_MAX` |
| `ascii_lower` | function | `src/css_color.c:119` | `static int ascii_lower(int c)` |
| `cc_cexpr` | function | `src/css_color.c:269` | `static int cc_cexpr(cc_cp *c, cc_cv *out, int depth)` |
| `cc_cfactor` | function | `src/css_color.c:229` | `static int cc_cfactor(cc_cp *c, cc_cv *out, int depth)` |
| `cc_cp` | struct | `src/css_color.c:224` | `` |
| `cc_cterm` | function | `src/css_color.c:250` | `static int cc_cterm(cc_cp *c, cc_cv *out, int depth)` |
| `cc_cv` | struct | `src/css_color.c:223` | `` |
| `cc_cws` | function | `src/css_color.c:226` | `static void cc_cws(cc_cp *c)` |
| `cc_fold_calc` | function | `src/css_color.c:285` | `static int cc_fold_calc(const char **b, const char **e, char *buf, size_t cap)` |
| `cc_named` | struct | `src/css_color.c:34` | `` |
| `cc_pack` | function | `src/css_color.c:768` | `int cc_pack(cc_rgb c)` |
| `cc_parse` | function | `src/css_color.c:728` | `cc_status cc_parse(const char *token, cc_rgb *out)` |
| `cc_round` | function | `src/css_color.c:305` | `static long cc_round(double v)` |
| `cc_unpack` | function | `src/css_color.c:772` | `cc_rgb cc_unpack(int packed)` |
| `hex_val` | function | `src/css_color.c:123` | `static int hex_val(int c)` |
| `lab_comp` | function | `src/css_color.c:581` | `static int lab_comp(const char *b, const char *e, double pct_ref, int is_hue, double *out)` |
| `lab_to_rgb` | function | `src/css_color.c:627` | `static void lab_to_rgb(double L, double a, double b, cc_rgb *out)` |
| `named_cmp` | function | `src/css_color.c:681` | `static int named_cmp(const void *key, const void *element)` |
| `normalize` | function | `src/css_color.c:132` | `static int normalize(const char *token, char *out)` |
| `oklab_to_rgb` | function | `src/css_color.c:616` | `static void oklab_to_rgb(double L, double a, double b, cc_rgb *out)` |
| `parse_component` | function | `src/css_color.c:310` | `static int parse_component(const char *b, const char *e, int is_alpha, int *out)` |
| `parse_func` | function | `src/css_color.c:508` | `static int parse_func(const char *s, cc_rgb *out)` |
| `parse_hex` | function | `src/css_color.c:146` | `static int parse_hex(const char *s, cc_rgb *out)` |
| `parse_hsl_comp` | function | `src/css_color.c:343` | `static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out)` |
| `parse_lab_family` | function | `src/css_color.c:643` | `static int parse_lab_family(const char *s, cc_rgb *out)` |
| `parse_named` | function | `src/css_color.c:715` | `static int parse_named(const char *s, cc_rgb *out)` |
| `span` | function | `src/css_color.c:431` | `* span (when a slash is present) into ab/ae, and returns the component count,  * or -1. Bounded: ...` |
| `srgb_encode` | function | `src/css_color.c:609` | `static unsigned char srgb_encode(double lin)` |
| `strncmp` | function | `src/css_color.c:743` | `strncmp(buf, "oklab(", 6) == 0 \|\| strncmp(buf, "oklch(", 6) == 0)` |
| `v` | type_alias | `src/css_color.c:222` | `typedef struct cc_cv { double v;` |
| `CCM_NPROPS` | macro | `src/css_computed.c:310` | `#define CCM_NPROPS` |
| `LEN_FIELD` | macro | `src/css_computed.c:225` | `#define LEN_FIELD(NAME, FIELD, UNSET)` |
| `NAME` | function | `src/css_computed.c:226` | `static size_t NAME(const ccm_input *in, char *out, size_t cap)` |
| `ccm_get` | function | `src/css_computed.c:312` | `size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap)` |
| `ccm_prop` | struct | `src/css_computed.c:278` | `` |
| `ccm_property_count` | function | `src/css_computed.c:325` | `size_t ccm_property_count(void)` |
| `ccm_property_name` | function | `src/css_computed.c:327` | `const char *ccm_property_name(size_t i)` |
| `f_align_items` | function | `src/css_computed.c:153` | `static size_t f_align_items(const ccm_input *in, char *out, size_t cap)` |
| `f_background_color` | function | `src/css_computed.c:200` | `static size_t f_background_color(const ccm_input *in, char *out, size_t cap)` |
| `f_border_bottom_style` | function | `src/css_computed.c:264` | `static size_t f_border_bottom_style(const ccm_input *in, char *out, size_t cap)` |
| `f_border_left_style` | function | `src/css_computed.c:267` | `static size_t f_border_left_style(const ccm_input *in, char *out, size_t cap)` |
| `f_border_right_style` | function | `src/css_computed.c:261` | `static size_t f_border_right_style(const ccm_input *in, char *out, size_t cap)` |
| `f_border_style` | function | `src/css_computed.c:219` | `static size_t f_border_style(int v, char *out, size_t cap)` |
| `f_border_top_style` | function | `src/css_computed.c:258` | `static size_t f_border_top_style(const ccm_input *in, char *out, size_t cap)` |
| `f_box_sizing` | function | `src/css_computed.c:132` | `static size_t f_box_sizing(const ccm_input *in, char *out, size_t cap)` |
| `f_clear` | function | `src/css_computed.c:112` | `static size_t f_clear(const ccm_input *in, char *out, size_t cap)` |
| `f_color` | function | `src/css_computed.c:195` | `static size_t f_color(const ccm_input *in, char *out, size_t cap)` |
| `f_cursor` | function | `src/css_computed.c:159` | `static size_t f_cursor(const ccm_input *in, char *out, size_t cap)` |
| `f_display` | function | `src/css_computed.c:77` | `static size_t f_display(const ccm_input *in, char *out, size_t cap)` |
| `f_flex_direction` | function | `src/css_computed.c:137` | `static size_t f_flex_direction(const ccm_input *in, char *out, size_t cap)` |
| `f_flex_grow` | function | `src/css_computed.c:271` | `static size_t f_flex_grow(const ccm_input *in, char *out, size_t cap)` |
| `f_flex_shrink` | function | `src/css_computed.c:274` | `static size_t f_flex_shrink(const ccm_input *in, char *out, size_t cap)` |
| `f_flex_wrap` | function | `src/css_computed.c:142` | `static size_t f_flex_wrap(const ccm_input *in, char *out, size_t cap)` |
| `f_float` | function | `src/css_computed.c:107` | `static size_t f_float(const ccm_input *in, char *out, size_t cap)` |
| `f_font_size` | function | `src/css_computed.c:183` | `static size_t f_font_size(const ccm_input *in, char *out, size_t cap)` |
| `f_font_style` | function | `src/css_computed.c:175` | `static size_t f_font_style(const ccm_input *in, char *out, size_t cap)` |
| `f_font_weight` | function | `src/css_computed.c:179` | `static size_t f_font_weight(const ccm_input *in, char *out, size_t cap)` |
| `f_gap` | function | `src/css_computed.c:246` | `static size_t f_gap(const ccm_input *in, char *out, size_t cap)` |
| `f_justify` | function | `src/css_computed.c:147` | `static size_t f_justify(const ccm_input *in, char *out, size_t cap)` |
| `f_line_height` | function | `src/css_computed.c:189` | `static size_t f_line_height(const ccm_input *in, char *out, size_t cap)` |
| `f_opacity` | function | `src/css_computed.c:206` | `static size_t f_opacity(const ccm_input *in, char *out, size_t cap)` |
| `f_overflow_x` | function | `src/css_computed.c:117` | `static size_t f_overflow_x(const ccm_input *in, char *out, size_t cap)` |
| `f_overflow_y` | function | `src/css_computed.c:122` | `static size_t f_overflow_y(const ccm_input *in, char *out, size_t cap)` |
| `f_position` | function | `src/css_computed.c:97` | `static size_t f_position(const ccm_input *in, char *out, size_t cap)` |
| `f_text_align` | function | `src/css_computed.c:127` | `static size_t f_text_align(const ccm_input *in, char *out, size_t cap)` |
| `f_text_transform` | function | `src/css_computed.c:170` | `static size_t f_text_transform(const ccm_input *in, char *out, size_t cap)` |
| `f_visibility` | function | `src/css_computed.c:102` | `static size_t f_visibility(const ccm_input *in, char *out, size_t cap)` |
| `f_white_space` | function | `src/css_computed.c:165` | `static size_t f_white_space(const ccm_input *in, char *out, size_t cap)` |
| `f_z_index` | function | `src/css_computed.c:214` | `static size_t f_z_index(const ccm_input *in, char *out, size_t cap)` |
| `put` | function | `src/css_computed.c:9` | `static size_t put(char *out, size_t cap, const char *s)` |
| `put_enum` | function | `src/css_computed.c:42` | `static size_t put_enum(char *out, size_t cap, int v, const char *const *names, size_t n,         ...` |
| `put_len` | function | `src/css_computed.c:37` | `static size_t put_len(char *out, size_t cap, int v, const char *unset_text)` |
| `put_rgb` | function | `src/css_computed.c:26` | `static size_t put_rgb(char *out, size_t cap, int rgb, int alpha_pct)` |
| `putf` | function | `src/css_computed.c:17` | `static size_t putf(char *out, size_t cap, const char *fmt, ...)` |
| `ua_display` | function | `src/css_computed.c:49` | `static const char *ua_display(const char *tag)` |
| `CNT_FIELD_SEP` | macro | `src/css_counter.c:14` | `#define CNT_FIELD_SEP` |
| `CNT_ITEM_END` | macro | `src/css_counter.c:13` | `#define CNT_ITEM_END` |
| `CNT_SEQ_MARK` | macro | `src/css_counter.c:12` | `#define CNT_SEQ_MARK` |
| `CNT_STR_MAX` | macro | `src/css_counter.c:16` | `#define CNT_STR_MAX` |
| `CNT_VALUE_LIMIT` | macro | `src/css_counter.c:15` | `#define CNT_VALUE_LIMIT` |
| `ci_eq` | function | `src/css_counter.c:34` | `static int ci_eq(const char *a, const char *b)` |
| `clampv` | function | `src/css_counter.c:375` | `static int clampv(long v)` |
| `cnt_format` | function | `src/css_counter.c:120` | `size_t cnt_format(int style, long value, char *out, size_t cap)` |
| `cnt_hash` | function | `src/css_counter.c:18` | `unsigned cnt_hash(const char *name, size_t len)` |
| `cnt_increment` | function | `src/css_counter.c:392` | `void cnt_increment(cnt_state *s, int depth, const cnt_decl *d, int n)` |
| `cnt_inst` | struct | `src/css_counter.c:359` | `` |
| `cnt_is_marker` | function | `src/css_counter.c:272` | `int cnt_is_marker(const char *s)` |
| `cnt_leave` | function | `src/css_counter.c:407` | `void cnt_leave(cnt_state *s, int depth)` |
| `cnt_parse_content` | function | `src/css_counter.c:286` | `int cnt_parse_content(const char *val, char *out, size_t cap)` |
| `cnt_parse_decls` | function | `src/css_counter.c:59` | `int cnt_parse_decls(const char *val, int dflt, cnt_decl out[CNT_MAX_DECL])` |
| `cnt_reset` | function | `src/css_counter.c:379` | `void cnt_reset(cnt_state *s, int depth, const cnt_decl *d, int n)` |
| `cnt_resolve` | function | `src/css_counter.c:412` | `size_t cnt_resolve(const cnt_state *s, const char *marker, cnt_attr_fn attr, void *ctx,          ...` |
| `cnt_state` | struct | `src/css_counter.c:361` | `` |
| `cnt_state_free` | function | `src/css_counter.c:367` | `void cnt_state_free(cnt_state *s)` |
| `cnt_state_new` | function | `src/css_counter.c:366` | `cnt_state *cnt_state_new(void)` |
| `has_counter_fn` | function | `src/css_counter.c:276` | `static int has_counter_fn(const char *v)` |
| `is_ident_char` | function | `src/css_counter.c:32` | `static int is_ident_char(unsigned char c)` |
| `is_ident_start` | function | `src/css_counter.c:29` | `static int is_ident_start(unsigned char c)` |
| `is_ws` | function | `src/css_counter.c:27` | `static int is_ws(char c)` |
| `put` | function | `src/css_counter.c:102` | `static size_t put(char *out, size_t cap, size_t o, const char *s)` |
| `read_string` | function | `src/css_counter.c:201` | `static const char *read_string(const char *p, char *dst, size_t cap)` |
| `sink` | struct | `src/css_counter.c:190` | `` |
| `sk_char` | function | `src/css_counter.c:192` | `static void sk_char(sink *k, char c)` |
| `sk_str` | function | `src/css_counter.c:196` | `static void sk_str(sink *k, const char *s)` |
| `split_args` | function | `src/css_counter.c:238` | `static int split_args(const char *a, const char *b, char (*f)[CNT_STR_MAX], int max)` |
| `style_of` | function | `src/css_counter.c:174` | `static int style_of(const char *name)` |
| `top_of` | function | `src/css_counter.c:369` | `static cnt_inst *top_of(cnt_state *s, unsigned name)` |
| `utf8_put` | function | `src/css_counter.c:107` | `static void utf8_put(char *buf, unsigned cp)` |
| `valid_name` | function | `src/css_counter.c:45` | `static int valid_name(const char *s, size_t n)` |
| `CG_RAD_FLOOR` | macro | `src/css_gradient.c:833` | `#define CG_RAD_FLOOR` |
| `CG_RAD_PM_MAX` | macro | `src/css_gradient.c:676` | `#define CG_RAD_PM_MAX` |
| `CG_RAD_PX_MAX` | macro | `src/css_gradient.c:677` | `#define CG_RAD_PX_MAX` |
| `CG_RAD_TOKENS` | macro | `src/css_gradient.c:675` | `#define CG_RAD_TOKENS` |
| `CG_SQRT2` | macro | `src/css_gradient.c:834` | `#define CG_SQRT2` |
| `CSS_GRAD_STOPS_MAX` | function | `src/css_gradient.c:241` | `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when  * the gradient fai...` |
| `bg_layer_tokens_ok` | function | `src/css_gradient.c:551` | `static int bg_layer_tokens_ok(const char *s)` |
| `cg_dmax` | function | `src/css_gradient.c:837` | `static double cg_dmax(double a, double b)` |
| `cg_dmin` | function | `src/css_gradient.c:836` | `static double cg_dmin(double a, double b)` |
| `cg_expand_background` | function | `src/css_gradient.c:591` | `int cg_expand_background(const char *val, css_decl *dst, int cap,                              ch...` |
| `cg_first_url` | function | `src/css_gradient.c:459` | `int cg_first_url(const char *val, char *out, size_t outcap)` |
| `cg_parse_linear` | function | `src/css_gradient.c:876` | `int cg_parse_linear(const char *fn, int *angle, int *colors, int *positions)` |
| `cg_parse_num` | function | `src/css_gradient.c:13` | `static int cg_parse_num(const char *s, double *out, const char **endp)` |
| `cg_parse_radial_prelude` | function | `src/css_gradient.c:751` | `int cg_parse_radial_prelude(const char *seg, cg_radial *out)` |
| `cg_radial_geometry` | function | `src/css_gradient.c:839` | `void cg_radial_geometry(const cg_radial *r, double w, double h,                         double *c...` |
| `cg_radial_len_px` | function | `src/css_gradient.c:827` | `double cg_radial_len_px(int enc, double dim)` |
| `cg_wide_keyword` | function | `src/css_gradient.c:18` | `static int cg_wide_keyword(const char *v)` |
| `conic_prelude` | function | `src/css_gradient.c:111` | `static int conic_prelude(const char *seg, int *angle)` |
| `declaration` | function | `src/css_gradient.c:544` | `* declaration (fail closed);` |
| `downstream` | function | `src/css_gradient.c:483` | `* happens downstream (render_doc.c), gated by caps.images like an <img>. */ int cg_expand_bg_imag...` |
| `emit_gradient` | function | `src/css_gradient.c:352` | `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,                          ...` |
| `emit_radial_geom` | function | `src/css_gradient.c:466` | `static int emit_radial_geom(css_decl *dst, int cap, const cg_radial *r)` |
| `find_gradient_call` | function | `src/css_gradient.c:77` | `static int find_gradient_call(const char *v, const char *fn, size_t *start,                      ...` |
| `find_radial_gradient` | function | `src/css_gradient.c:421` | `static int find_radial_gradient(const char *v, size_t *start, size_t *end,                       ...` |
| `grad_stop_pos` | function | `src/css_gradient.c:210` | `static int grad_stop_pos(const char *pp, int conic, const char **endp)` |
| `gradient` | function | `src/css_gradient.c:28` | `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,  * the whole decl...` |
| `pool` | function | `src/css_gradient.c:479` | `* pool (gradient explicitly reset);` |
| `rad_ieq` | function | `src/css_gradient.c:679` | `static int rad_ieq(const char *a, const char *b)` |
| `rad_is_len_start` | function | `src/css_gradient.c:708` | `static int rad_is_len_start(const char *t)` |
| `rad_len` | function | `src/css_gradient.c:687` | `static int rad_len(const char *tok, int *enc)` |
| `rad_parse_position` | function | `src/css_gradient.c:722` | `static int rad_parse_position(char (*tok)[CSS_TOK_MAX], int n, int *cx, int *cy)` |
| `rad_pos_kw` | function | `src/css_gradient.c:713` | `static int rad_pos_kw(const char *t, int *axis)` |
| `sRGB` | function | `src/css_gradient.c:154` | `* sRGB (spec/css_gradient.md §3b). */ static int strip_interp(char *seg)` |
| `abs_ok` | function | `src/css_import.c:297` | `static int abs_ok(const char *u)` |
| `ci_balanced` | function | `src/css_import.c:220` | `int ci_balanced(const char *css, size_t len)` |
| `ci_rebase_urls` | function | `src/css_import.c:303` | `int ci_rebase_urls(const char *css, size_t len, const char *base,                    ci_resolve_f...` |
| `ci_scan` | function | `src/css_import.c:156` | `size_t ci_scan(const char *css, size_t len, ci_import *out, size_t cap)` |
| `ci_wrap` | function | `src/css_import.c:194` | `int ci_wrap(const ci_import *im, char *open, size_t ocap, char *close, size_t ccap)` |
| `copy_trim` | function | `src/css_import.c:53` | `static int copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `has_scheme` | function | `src/css_import.c:250` | `static int has_scheme(const char *r)` |
| `is_ident_ch` | function | `src/css_import.c:243` | `static int is_ident_ch(char c)` |
| `is_ident_char` | function | `src/css_import.c:21` | `static int is_ident_char(char c)` |
| `is_ws` | function | `src/css_import.c:8` | `static int is_ws(char c)` |
| `kw_at` | function | `src/css_import.c:13` | `static int kw_at(const char *s, size_t i, size_t e, const char *kw)` |
| `lower` | function | `src/css_import.c:10` | `static char lower(char c)` |
| `match_paren` | function | `src/css_import.c:79` | `static size_t match_paren(const char *s, size_t i, size_t e)` |
| `parse_prelude` | function | `src/css_import.c:97` | `static int parse_prelude(const char *s, size_t a, size_t b, ci_import *im)` |
| `read_string` | function | `src/css_import.c:64` | `static size_t read_string(const char *s, size_t a, size_t e, char *dst, size_t cap)` |
| `skip_ws` | function | `src/css_import.c:27` | `static size_t skip_ws(const char *s, size_t i, size_t e)` |
| `url_arg` | function | `src/css_import.c:266` | `static int url_arg(const char *s, size_t a, size_t e, char *ref, size_t cap, size_t *end)` |
| `add_bucket` | function | `src/css_index.c:106` | `static void add_bucket(const cix_index *idx, uint64_t k, cix_run *runs, size_t *nr)` |
| `build` | function | `src/css_index.c:47` | `static void build(const css_sel *arr, css_sel *const *ptrs, size_t n, cix_index *idx)` |
| `cix_build` | function | `src/css_index.c:166` | `void cix_build(const css_sel *sels, size_t n, cix_index *idx)` |
| `cix_build_ptrs` | function | `src/css_index.c:168` | `void cix_build_ptrs(css_sel *const *sels, size_t n, cix_index *idx)` |
| `cix_candidates` | function | `src/css_index.c:129` | `size_t cix_candidates(const cix_index *idx, const css_element *el,                       uint32_t...` |
| `cix_free` | function | `src/css_index.c:40` | `void cix_free(cix_index *idx)` |
| `cix_run` | struct | `src/css_index.c:98` | `` |
| `entry_cmp` | function | `src/css_index.c:34` | `static int entry_cmp(const void *a, const void *b)` |
| `key_of` | function | `src/css_index.c:11` | `static uint64_t key_of(int kind, const char *s, size_t n, int lower)` |
| `key_of_token` | function | `src/css_index.c:26` | `static uint64_t key_of_token(int kind, const char *tok)` |
| `lower_bound` | function | `src/css_index.c:86` | `static size_t lower_bound(const cix_index *idx, uint64_t k)` |
| `push` | function | `src/css_index.c:114` | `static int push(uint32_t **buf, size_t *cap, size_t *n, uint32_t v)` |
| `run_head` | function | `src/css_index.c:104` | `static uint32_t run_head(const cix_run *r)` |
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
| `CM_MAX_TOKS` | macro | `src/css_mask.c:11` | `#define CM_MAX_TOKS` |
| `CM_TOK_MAX` | macro | `src/css_mask.c:10` | `#define CM_TOK_MAX` |
| `clip_word` | function | `src/css_mask.c:106` | `static int clip_word(const char *t)` |
| `cm_decode_layer` | function | `src/css_mask.c:47` | `void cm_decode_layer(int meta, int alphas, int poss, cm_layer *out)` |
| `cm_encode_layer` | function | `src/css_mask.c:26` | `void cm_encode_layer(const cm_layer *l, int *meta, int *alphas, int *poss)` |
| `cm_expand` | function | `src/css_mask.c:201` | `int cm_expand(const char *prop, const char *val, css_decl *dst, int cap, int webkit_vocab)` |
| `cm_is_mask_prop` | function | `src/css_mask.c:19` | `int cm_is_mask_prop(const char *prop)` |
| `composite_word` | function | `src/css_mask.c:92` | `static int composite_word(const char *t, int webkit)` |
| `emit_layers` | function | `src/css_mask.c:132` | `static int emit_layers(css_decl *dst, int cap, int shorthand, const char *val)` |
| `ieq` | function | `src/css_mask.c:13` | `static int ieq(const char *a, const char *b)` |
| `image_layer` | function | `src/css_mask.c:114` | `static int image_layer(const char *tok, cm_layer *l)` |
| `split` | function | `src/css_mask.c:65` | `static int split(const char *s, int comma, char (*out)[CM_TOK_MAX], int max)` |
| `CMQ_CM_PER_IN` | macro | `src/css_mq.c:24` | `#define CMQ_CM_PER_IN` |
| `CMQ_COLOR_BITS` | macro | `src/css_mq.c:22` | `#define CMQ_COLOR_BITS` |
| `CMQ_DEVICE_H` | macro | `src/css_mq.c:20` | `#define CMQ_DEVICE_H` |
| `CMQ_DEVICE_W` | macro | `src/css_mq.c:19` | `#define CMQ_DEVICE_W` |
| `CMQ_DPI_PER_DPPX` | macro | `src/css_mq.c:23` | `#define CMQ_DPI_PER_DPPX` |
| `CMQ_DPPX` | macro | `src/css_mq.c:21` | `#define CMQ_DPPX` |
| `MQ_EPS` | macro | `src/css_mq.c:205` | `#define MQ_EPS` |
| `and3` | function | `src/css_mq.c:67` | `static int and3(int a, int b)` |
| `bool_ctx` | function | `src/css_mq.c:231` | `static int bool_ctx(const fval *v)` |
| `cmp_op` | function | `src/css_mq.c:208` | `static int cmp_op(double lhs, int op, double rhs)` |
| `cmq_container_decl` | function | `src/css_mq.c:618` | `int cmq_container_decl(const char *prop, const char *val, int *type,                        unsig...` |
| `cmq_container_holds` | function | `src/css_mq.c:556` | `int cmq_container_holds(const char *s, size_t len, const cmq_container *scope, int max_width)` |
| `cmq_container_surely` | function | `src/css_mq.c:537` | `int cmq_container_surely(const char *s, size_t len, int max_width)` |
| `cmq_matches` | function | `src/css_mq.c:460` | `int cmq_matches(const char *s, size_t len, const cmq_env *env)` |
| `cmq_name_hash` | function | `src/css_mq.c:549` | `unsigned cmq_name_hash(const char *s, size_t n)` |
| `container_names` | function | `src/css_mq.c:596` | `static int container_names(const char *s, size_t n, unsigned names[CMQ_CONTAINER_NAMES])` |
| `container_type_kw` | function | `src/css_mq.c:580` | `static int container_type_kw(const char *s, size_t n, int *type)` |
| `copy_trim_lower` | function | `src/css_mq.c:84` | `static int copy_trim_lower(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `eval_cond` | function | `src/css_mq.c:382` | `static int eval_cond(mq_cur *c, int depth)` |
| `eval_feature` | function | `src/css_mq.c:330` | `static int eval_feature(const char *s, size_t a, size_t b, const cmq_env *env)` |
| `eval_in_parens` | function | `src/css_mq.c:355` | `static int eval_in_parens(mq_cur *c, int depth)` |
| `eval_plain` | function | `src/css_mq.c:239` | `static int eval_plain(const char *name, const char *value, const cmq_env *env)` |
| `eval_query` | function | `src/css_mq.c:406` | `static int eval_query(const char *s, size_t a, size_t b, const cmq_env *env)` |
| `eval_range` | function | `src/css_mq.c:282` | `static int eval_range(const char *t, const cmq_env *env)` |
| `feature_of` | function | `src/css_mq.c:107` | `static fval feature_of(const char *name, const cmq_env *env)` |
| `flip_op` | function | `src/css_mq.c:220` | `static int flip_op(int op)` |
| `fval` | struct | `src/css_mq.c:97` | `` |
| `has_word` | function | `src/css_mq.c:481` | `static int has_word(const char *t, const char *w)` |
| `is_ident_ch` | function | `src/css_mq.c:40` | `static int is_ident_ch(char c)` |
| `is_space` | function | `src/css_mq.c:36` | `static int is_space(char c)` |
| `kind` | type_alias | `src/css_mq.c:96` | `typedef struct fval { fv_kind kind;` |
| `lower_ch` | function | `src/css_mq.c:32` | `static char lower_ch(char c)` |
| `mq_cur` | struct | `src/css_mq.c:26` | `` |
| `not3` | function | `src/css_mq.c:79` | `static int not3(int a)` |
| `or3` | function | `src/css_mq.c:73` | `static int or3(int a, int b)` |
| `parse_value` | function | `src/css_mq.c:168` | `static int parse_value(const char *t, int unit, double *out)` |
| `peek_word` | function | `src/css_mq.c:62` | `static int peek_word(const mq_cur *c, char *w, size_t cap)` |
| `read_num` | function | `src/css_mq.c:163` | `static int read_num(const char *t, double *out, const char **end)` |
| `read_op` | function | `src/css_mq.c:268` | `static int read_op(const char **p)` |
| `read_word` | function | `src/css_mq.c:50` | `static int read_word(mq_cur *c, char *w, size_t cap)` |
| `skip_ws` | function | `src/css_mq.c:45` | `static void skip_ws(mq_cur *c)` |
| `HAS_MAX_DEPTH` | macro | `src/css_select.c:940` | `#define HAS_MAX_DEPTH` |
| `attr_matches` | function | `src/css_select.c:788` | `static int attr_matches(const css_attr_match *am, const css_element *el)` |
| `between` | function | `src/css_select.c:384` | `* between ( and ) is split on commas (not inside [] or ());` |
| `built` | function | `src/css_select.c:1116` | `* chains the caller built (an element without parent/prev links never matches  * through that com...` |
| `compound_matches` | function | `src/css_select.c:1081` | `static int compound_matches(const css_compound *c, const css_element *el,                        ...` |
| `compound_req` | function | `src/css_select.c:709` | `static unsigned long long compound_req(const css_compound *c)` |
| `compute_anc_req` | function | `src/css_select.c:602` | `static unsigned long long compute_anc_req(const css_sel *sel)` |
| `compute_subj_req` | function | `src/css_select.c:718` | `static unsigned long long compute_subj_req(const css_sel *sel)` |
| `csel_compact_dup` | function | `src/css_select.c:735` | `css_sel *csel_compact_dup(const css_sel *sel)` |
| `csel_compact_size` | function | `src/css_select.c:729` | `size_t csel_compact_size(int nparts)` |
| `csel_decl_end` | function | `src/css_select.c:106` | `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace)` |
| `csel_element_feature_bits` | function | `src/css_select.c:587` | `unsigned long long csel_element_feature_bits(const css_element *e)` |
| `csel_emit_utf8` | function | `src/css_select.c:32` | `size_t csel_emit_utf8(unsigned int cp, char *out)` |
| `csel_escape_len` | function | `src/css_select.c:93` | `size_t csel_escape_len(const char *s, size_t i, size_t b)` |
| `csel_hex_val` | function | `src/css_select.c:25` | `int csel_hex_val(char c)` |
| `csel_ident_eq` | function | `src/css_select.c:144` | `int csel_ident_eq(const char *stored, const char *tok, size_t tlen)` |
| `csel_ident_fold` | function | `src/css_select.c:129` | `void csel_ident_fold(const char *src, size_t len, char *dst)` |
| `csel_matches` | function | `src/css_select.c:1197` | `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,               ...` |
| `csel_needs_structure` | function | `src/css_select.c:1174` | `int csel_needs_structure(const css_sel *sel)` |
| `csel_parse` | function | `src/css_select.c:744` | `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel)` |
| `csel_parse_core` | function | `src/css_select.c:615` | `static int csel_parse_core(const char *s, size_t a, size_t b, css_sel *sel)` |
| `csel_read_ident` | function | `src/css_select.c:152` | `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower)` |
| `csel_unescape` | function | `src/css_select.c:54` | `void csel_unescape(char *dst, size_t cap, const char *src, size_t n)` |
| `el_attr_value` | function | `src/css_select.c:755` | `static const char *el_attr_value(const css_element *el, const char *name)` |
| `ends_with` | function | `src/css_select.c:765` | `static int ends_with(const char *v, const char *suf, int ci)` |
| `has_word` | function | `src/css_select.c:773` | `static int has_word(const char *v, const char *w, int ci)` |
| `ident_hash` | function | `src/css_select.c:123` | `static unsigned long long ident_hash(const char *s, size_t n)` |
| `is_form_control` | function | `src/css_select.c:817` | `static int is_form_control(const char *tag)` |
| `nth_matches` | function | `src/css_select.c:808` | `static int nth_matches(int A, int B, int idx)` |
| `parse_attr_sel` | function | `src/css_select.c:186` | `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)` |
| `parse_compound` | function | `src/css_select.c:525` | `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,                   ...` |
| `parse_nth_arg` | function | `src/css_select.c:243` | `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)` |
| `parse_sub_compound` | function | `src/css_select.c:460` | `static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub)` |
| `pseudo_is_local` | function | `src/css_select.c:1161` | `static int pseudo_is_local(int kind)` |
| `pseudo_matches` | function | `src/css_select.c:826` | `static int pseudo_matches(const css_pseudo_match *pm, const css_element *el, const css_sel *sel, const char...` |
| `selector` | function | `src/css_select.c:567` | `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is  * dropped. Whitespa...` |
| `seven` | function | `src/css_select.c:621` | `* pay for the other seven (a css_sel is ~12.8 KiB). */ memset(sel, 0, offsetof(css_sel, parts));` |
| `simple_pseudo_kind` | function | `src/css_select.c:439` | `static int simple_pseudo_kind(const char *nm)` |
| `sub_sel_matches` | function | `src/css_select.c:830` | `static int sub_sel_matches(const css_sub_sel *sub, const css_element *el)` |
| `take_sub_arg` | function | `src/css_select.c:295` | `static int take_sub_arg(const char *s, size_t a, size_t b, css_sel *sel, int strict);` |
| `ct_emit_spacing` | function | `src/css_text.c:344` | `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `ct_expand_shadow` | function | `src/css_text.c:357` | `int ct_expand_shadow(const char *val, css_decl *dst, int cap)` |
| `ct_expand_valign` | function | `src/css_text.c:122` | `int ct_expand_valign(const char *val, css_decl *dst, int cap)` |
| `ct_family_of` | function | `src/css_text.c:18` | `static int ct_family_of(const char *name)` |
| `ct_interp_aspect_ratio` | function | `src/css_text.c:229` | `int ct_interp_aspect_ratio(const char *v, int *num, int *den)` |
| `ct_interp_direction` | function | `src/css_text.c:271` | `int ct_interp_direction(const char *v)` |
| `ct_interp_fontfamily` | function | `src/css_text.c:47` | `int ct_interp_fontfamily(const char *v)` |
| `ct_interp_liststyle` | function | `src/css_text.c:309` | `int ct_interp_liststyle(const char *v)` |
| `ct_interp_tabsize` | function | `src/css_text.c:195` | `int ct_interp_tabsize(const char *v)` |
| `ct_interp_textdeco_style` | function | `src/css_text.c:206` | `int ct_interp_textdeco_style(const char *v)` |
| `ct_interp_textdeco_thickness` | function | `src/css_text.c:217` | `int ct_interp_textdeco_thickness(const char *v)` |
| `ct_interp_texttransform` | function | `src/css_text.c:69` | `int ct_interp_texttransform(const char *v)` |
| `ct_interp_valign` | function | `src/css_text.c:91` | `int ct_interp_valign(const char *v)` |
| `ct_interp_whitespace` | function | `src/css_text.c:182` | `int ct_interp_whitespace(const char *v)` |
| `ct_liststyle_kw` | function | `src/css_text.c:277` | `static int ct_liststyle_kw(const char *t)` |
| `ct_liststyle_unknown_name` | function | `src/css_text.c:298` | `static int ct_liststyle_unknown_name(const char *t)` |
| `transition_prop_one` | function | `src/css_text.c:139` | `static int transition_prop_one(const char *v)` |
| `alpha_of_depth` | function | `src/css_values.c:204` | `static int alpha_of_depth(const char *v, int depth)` |
| `cv_bg_alpha_of` | function | `src/css_values.c:199` | `int cv_bg_alpha_of(const char *v)` |
| `cv_color_ok` | function | `src/css_values.c:52` | `int cv_color_ok(int c)` |
| `cv_filter_scale` | function | `src/css_values.c:395` | `double cv_filter_scale(int pct)` |
| `cv_interp_bg` | function | `src/css_values.c:324` | `int cv_interp_bg(const char *v)` |
| `cv_interp_color` | function | `src/css_values.c:47` | `int cv_interp_color(const char *v)` |
| `cv_parse_color` | function | `src/css_values.c:42` | `int cv_parse_color(const char *v)` |
| `cv_parse_color_t7` | function | `src/css_values.c:369` | `int cv_parse_color_t7(const char *v)` |
| `cv_parse_num` | function | `src/css_values.c:11` | `static int cv_parse_num(const char *s, double *out, const char **endp)` |
| `cv_text_color` | function | `src/css_values.c:386` | `int cv_text_color(const char *v)` |
| `mix_alpha` | function | `src/css_values.c:179` | `static int mix_alpha(const char *v, int depth)` |
| `mix_arg` | function | `src/css_values.c:61` | `static int mix_arg(const char *s, size_t n, double *pct, double *alpha, int *rgb, int depth)` |
| `mix_color` | function | `src/css_values.c:171` | `static int mix_color(const char *v, int depth)` |
| `mix_solve` | function | `src/css_values.c:110` | `static int mix_solve(const char *v, int depth, int *rgb_out, double *alpha_out)` |
| `parse_color_depth` | function | `src/css_values.c:18` | `static int parse_color_depth(const char *v, int depth)` |
| `cvr_collect_decls` | function | `src/css_vars.c:139` | `void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b)` |
| `cvr_count` | function | `src/css_vars.c:100` | `size_t cvr_count(const cvr_table *t)` |
| `cvr_free` | function | `src/css_vars.c:112` | `void cvr_free(cvr_table *t)` |
| `cvr_get` | function | `src/css_vars.c:94` | `const char *cvr_get(const cvr_table *t, const char *name, size_t nlen)` |
| `cvr_lookup` | function | `src/css_vars.c:312` | `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen)` |
| `cvr_reset` | function | `src/css_vars.c:102` | `void cvr_reset(cvr_table *t)` |
| `cvr_resolve` | function | `src/css_vars.c:303` | `int cvr_resolve(const char *val, char *out, size_t outcap, const cvr_scope *sc)` |
| `cvr_set` | function | `src/css_vars.c:67` | `int cvr_set(cvr_table *t, const char *name, size_t nlen, const char *value, size_t vlen)` |
| `dup_n` | function | `src/css_vars.c:21` | `static char *dup_n(const char *s, size_t n)` |
| `env_value` | function | `src/css_vars.c:204` | `static const char *env_value(const char *name, size_t n)` |
| `find_slot` | function | `src/css_vars.c:32` | `static size_t find_slot(const cvr_table *t, const char *name, size_t nlen)` |
| `grow` | function | `src/css_vars.c:45` | `static int grow(cvr_table *t)` |
| `is_ws` | function | `src/css_vars.c:120` | `static int is_ws(char c)` |
| `name_hash` | function | `src/css_vars.c:12` | `static size_t name_hash(const char *s, size_t n)` |
| `resolve_rec` | function | `src/css_vars.c:214` | `static int resolve_rec(const char *val, size_t vlen, char *out, size_t outcap,                   ...` |
| `scope_get` | function | `src/css_vars.c:179` | `static const char *scope_get(const cvr_scope *sc, const char *name, size_t nlen)` |
| `wide_keyword` | function | `src/css_vars.c:168` | `static int wide_keyword(const char *v)` |
| `without_important` | function | `src/css_vars.c:124` | `static size_t without_important(const char *val, size_t n)` |
| `ascii_ws` | function | `src/data_url.c:124` | `static int ascii_ws(char c)` |
| `b64_val` | function | `src/data_url.c:70` | `static int b64_val(unsigned char c)` |
| `ci_starts_with` | function | `src/data_url.c:20` | `static int ci_starts_with(const char *s, const char *prefix)` |
| `du_base64_decode` | function | `src/data_url.c:79` | `du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len)` |
| `du_base64_payload` | function | `src/data_url.c:32` | `du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len)` |
| `du_decode` | function | `src/data_url.c:140` | `du_status du_decode(const char *url, char *mime, size_t mime_cap, uint8_t **out, size_t *out_len)` |
| `du_is_data_url` | function | `src/data_url.c:28` | `int du_is_data_url(const char *url)` |
| `du_shape_ok` | function | `src/data_url.c:59` | `du_status du_shape_ok(const char *url)` |
| `ends_ci` | function | `src/data_url.c:129` | `static int ends_ci(const char *s, size_t n, const char *suf)` |
| `hexval` | function | `src/data_url.c:117` | `static int hexval(char c)` |
| `lower` | function | `src/data_url.c:16` | `static int lower(char c)` |
| `_POSIX_C_SOURCE` | macro | `src/disk_store.c:11` | `#define _POSIX_C_SOURCE` |
| `ds_free` | function | `src/disk_store.c:136` | `void ds_free(uint8_t *buf, size_t len)` |
| `ds_read` | function | `src/disk_store.c:103` | `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],                   uint8_t **ou...` |
| `ds_write` | function | `src/disk_store.c:66` | `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,                ...` |
| `fsync_dir` | function | `src/disk_store.c:32` | `static void fsync_dir(const char *path)` |
| `map_ls` | function | `src/disk_store.c:50` | `static ds_status map_ls(ls_status s)` |
| `DT_MAX_CP` | macro | `src/doc_title.c:9` | `#define DT_MAX_CP` |
| `DT_REF_DIGITS` | macro | `src/doc_title.c:10` | `#define DT_REF_DIGITS` |
| `DT_REPLACEMENT` | macro | `src/doc_title.c:8` | `#define DT_REPLACEMENT` |
| `at_end_tag` | function | `src/doc_title.c:116` | `static int at_end_tag(const unsigned char *s, size_t i, size_t n, const char *name)` |
| `char_ref` | function | `src/doc_title.c:83` | `static size_t char_ref(const unsigned char *s, size_t n, uint32_t *cp)` |
| `dt_scan` | function | `src/doc_title.c:131` | `int dt_scan(const char *html, size_t len, char *out, size_t cap)` |
| `dt_writer` | struct | `src/doc_title.c:12` | `` |
| `find_end_tag` | function | `src/doc_title.c:125` | `static size_t find_end_tag(const unsigned char *s, size_t i, size_t n, const char *name)` |
| `is_ascii_space` | function | `src/doc_title.c:19` | `static int is_ascii_space(unsigned c)` |
| `is_bidi_control` | function | `src/doc_title.c:23` | `static int is_bidi_control(uint32_t cp)` |
| `lower` | function | `src/doc_title.c:28` | `static unsigned lower(unsigned c)` |
| `utf8_next` | function | `src/doc_title.c:62` | `static size_t utf8_next(const unsigned char *s, size_t n, uint32_t *cp)` |
| `DOM_QS_MAX_SELECTORS` | macro | `src/dom.c:422` | `#define DOM_QS_MAX_SELECTORS` |
| `IH_BLOCK_SIZE` | macro | `src/dom.c:864` | `#define IH_BLOCK_SIZE` |
| `_POSIX_C_SOURCE` | macro | `src/dom.c:11` | `#define _POSIX_C_SOURCE` |
| `char_kind` | function | `src/dom.c:1029` | `static int char_kind(const lxb_dom_node_t *n)` |
| `copy_ids` | function | `src/dom.c:396` | `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)` |
| `count` | function | `src/dom.c:476` | `* count (may exceed cap), and returns DOM_NODE_NONE. */ static dom_node_id qs_walk(const dom_inde...` |
| `dom_append_child` | function | `src/dom.c:751` | `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)` |
| `dom_attribute_names` | function | `src/dom.c:625` | `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,                            con...` |
| `dom_build` | function | `src/dom.c:292` | `dom_status dom_build(const hp_document *doc, dom_index **out)` |
| `dom_child_node` | function | `src/dom.c:1052` | `dom_node_id dom_child_node(dom_index *idx, dom_node_id node, int last)` |
| `dom_clone_node` | function | `src/dom.c:981` | `dom_status dom_clone_node(dom_index *idx, dom_node_id node, int deep, dom_node_id *out_id)` |
| `dom_closest` | function | `src/dom.c:535` | `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,                         const cha...` |
| `dom_create_char_node` | function | `src/dom.c:1066` | `dom_status dom_create_char_node(dom_index *idx, int kind, const char *text, size_t len,          ...` |
| `dom_create_element` | function | `src/dom.c:731` | `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)` |
| `dom_document_position` | function | `src/dom.c:551` | `size_t dom_document_position(const dom_index *idx, dom_node_id node)` |
| `dom_document_title` | function | `src/dom.c:653` | `const char *dom_document_title(const dom_index *idx, size_t *len)` |
| `dom_first_child` | function | `src/dom.c:576` | `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)` |
| `dom_free` | function | `src/dom.c:333` | `void dom_free(dom_index *idx)` |
| `dom_get_attribute` | function | `src/dom.c:603` | `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,                            ...` |
| `dom_get_by_class` | function | `src/dom.c:412` | `size_t dom_get_by_class(const dom_index *idx, const char *cls,                         dom_node_i...` |
| `dom_get_by_tag` | function | `src/dom.c:403` | `size_t dom_get_by_tag(const dom_index *idx, const char *tag,                       dom_node_id *o...` |
| `dom_get_connected_by_id` | function | `src/dom.c:373` | `dom_node_id dom_get_connected_by_id(const dom_index *idx, const char *id)` |
| `dom_get_element_by_id` | function | `src/dom.c:363` | `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)` |
| `dom_get_inner_html` | function | `src/dom.c:933` | `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,                            ...` |
| `dom_handle_of_native` | function | `src/dom.c:1080` | `dom_node_id dom_handle_of_native(dom_index *idx, const void *native)` |
| `dom_index` | struct | `src/dom.c:220` | `` |
| `dom_insert_before` | function | `src/dom.c:963` | `dom_status dom_insert_before(dom_index *idx, dom_node_id parent, dom_node_id child,              ...` |
| `dom_is_connected` | function | `src/dom.c:369` | `int dom_is_connected(const dom_index *idx, dom_node_id node)` |
| `dom_matches` | function | `src/dom.c:526` | `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)` |
| `dom_move_children` | function | `src/dom.c:995` | `dom_status dom_move_children(dom_index *idx, dom_node_id src, dom_node_id parent,                ...` |
| `dom_mutation_count` | function | `src/dom.c:345` | `uint64_t dom_mutation_count(const dom_index *idx)` |
| `dom_native_node` | function | `src/dom.c:1086` | `const void *dom_native_node(const dom_index *idx, dom_node_id node)` |
| `dom_next_sibling` | function | `src/dom.c:584` | `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)` |
| `dom_node_at` | function | `src/dom.c:561` | `dom_node_id dom_node_at(const dom_index *idx, size_t position)` |
| `dom_node_count` | function | `src/dom.c:349` | `size_t dom_node_count(const dom_index *idx)` |
| `dom_node_kind` | function | `src/dom.c:1048` | `int dom_node_kind(const dom_index *idx, dom_node_id node)` |
| `dom_parent` | function | `src/dom.c:566` | `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)` |
| `dom_precedes` | function | `src/dom.c:556` | `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)` |
| `dom_query_selector` | function | `src/dom.c:506` | `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,                           ...` |
| `dom_query_selector_all` | function | `src/dom.c:515` | `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,                            ...` |
| `dom_remove_attribute` | function | `src/dom.c:805` | `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)` |
| `dom_remove_child` | function | `src/dom.c:766` | `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)` |
| `dom_set_attribute` | function | `src/dom.c:775` | `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,                              const...` |
| `dom_set_document_title` | function | `src/dom.c:701` | `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)` |
| `dom_set_inner_html` | function | `src/dom.c:825` | `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,                               con...` |
| `dom_set_text_content` | function | `src/dom.c:666` | `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,                                ...` |
| `dom_sibling_node` | function | `src/dom.c:1059` | `dom_node_id dom_sibling_node(dom_index *idx, dom_node_id node, int prev)` |
| `dom_tag_name` | function | `src/dom.c:592` | `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)` |
| `dom_text_content` | function | `src/dom.c:643` | `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)` |
| `handle_of` | function | `src/dom.c:1040` | `static dom_node_id handle_of(dom_index *idx, lxb_dom_node_t *n)` |
| `id_of` | function | `src/dom.c:425` | `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)` |
| `idx_push` | function | `src/dom.c:713` | `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)` |
| `ih_acc` | struct | `src/dom.c:871` | `` |
| `ih_append` | function | `src/dom.c:879` | `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)` |
| `ih_block` | struct | `src/dom.c:866` | `` |
| `ih_free` | function | `src/dom.c:906` | `static void ih_free(ih_acc *a)` |
| `index_element` | function | `src/dom.c:255` | `static int index_element(dom_index *idx, lxb_dom_element_t *el, dom_node_id id)` |
| `index_subtree` | function | `src/dom.c:815` | `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)` |
| `node_in_document` | function | `src/dom.c:357` | `static int node_in_document(const lxb_dom_node_t *node)` |
| `node_matches_any` | function | `src/dom.c:468` | `static int node_matches_any(const lxb_dom_node_t *cn,                             const css_sel *...` |
| `node_next` | function | `src/dom.c:233` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `parse_selector_list` | function | `src/dom.c:435` | `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)` |
| `pm_entry` | struct | `src/dom.c:154` | `` |
| `pm_free` | function | `src/dom.c:211` | `static void pm_free(ptrmap *m)` |
| `pm_get` | function | `src/dom.c:200` | `static int pm_get(const ptrmap *m, const void *key, dom_node_id *out)` |
| `pm_grow` | function | `src/dom.c:166` | `static int pm_grow(ptrmap *m)` |
| `pm_put` | function | `src/dom.c:183` | `static int pm_put(ptrmap *m, const void *key, dom_node_id id)` |

Next: [SYMBOLS_p9.md](SYMBOLS_p9.md)
