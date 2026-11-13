# API (page 7 of 12)
Previous: [API_p6.md](API_p6.md)

## src/css_box.c
Depends on: `include/css.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`
- `cb_parse_num` (function) `src/css_box.c:13` `static int cb_parse_num(const char *s, double *out, const char **endp)`
- `cb_wide_keyword` (function) `src/css_box.c:18` `static int cb_wide_keyword(const char *v)`
- `cb_copy_trim` (function) `src/css_box.c:25` `static size_t cb_copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)`
- `cb_length_px` (function) `src/css_box.c:49` `int cb_length_px(const char *v, double *px)` -- Resolves a NUL-terminated <length> token to px through the canonical resolver.
- `cb_interp_align` (function) `src/css_box.c:54` `int cb_interp_align(const char *v)`
- `RELATIVE` (function) `src/css_box.c:63` `* or RELATIVE (of the inherited size). Absolute: px/pt/rem/viewport units and the * absolute keywords. Relative: em...`
- `cb_interp_fontsize_ex` (function) `src/css_box.c:72` `int cb_interp_fontsize_ex(const char *v, int *abs_out)`
- `cb_interp_lineheight` (function) `src/css_box.c:145` `int cb_interp_lineheight(const char *v)` -- line-height as a percent of the natural line box.
- `cb_interp_weight` (function) `src/css_box.c:194` `int cb_interp_weight(const char *v)`
- `cb_interp_style` (function) `src/css_box.c:203` `int cb_interp_style(const char *v)`
- `cb_interp_textdeco` (function) `src/css_box.c:213` `int cb_interp_textdeco(const char *v)` -- text-decoration / text-decoration-line: OR of the line keywords underline / overline / line-through found in the...
- `cb_interp_display` (function) `src/css_box.c:233` `int cb_interp_display(const char *v)`
- `cb_interp_gap` (function) `src/css_box.c:313` `int cb_interp_gap(const char *v)` -- One gap length.
- `cb_interp_justify` (function) `src/css_box.c:320` `int cb_interp_justify(const char *v)`
- `repeat` (function) `src/css_box.c:341` `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill|...) /...`
- `cb_starts_with_ci` (function) `src/css_box.c:352` `static int cb_starts_with_ci(const char *s, const char *pre)`
- `count_tracks` (function) `src/css_box.c:358` `static int count_tracks(const char *s, size_t n)`
- `track_size_of` (function) `src/css_box.c:366` `static int track_size_of(const char *tok)` -- Size of ONE track token: `<N>fr` -> -(N*100); a px/em/rem length -> px (> 0); minmax(a,b) -> the size of its max...
- `count_one_repeat` (function) `src/css_box.c:396` `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,
                      ...`
- `walk_tracks` (function) `src/css_box.c:439` `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)`
- `track_min_of` (function) `src/css_box.c:507` `static int track_min_of(const char *tok)` -- Minimum width of ONE track token for repeat(auto-fill): minmax(a,b) takes a's length; a plain track takes itself....
- `expand_auto_fill` (function) `src/css_box.c:545` `static int expand_auto_fill(const char *val, css_decl *dst, int cap)` -- repeat(auto-fill|auto-fit, <single-track pattern>) tried as a whole value: returns 1 and emits grid_cols = -min_px...
- `cb_expand_grid_template_cols` (function) `src/css_box.c:623` `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap)` -- grid-template-columns: track count PLUS the first CSS_GRID_TRACKS_MAX track sizes, emitted in lock-step (P_GRIDCOLS...
- `cb_expand_grid_template_rows` (function) `src/css_box.c:646` `int cb_expand_grid_template_rows(const char *val, css_decl *dst, int cap)`
- `accepts` (function) `src/css_box.c:706` `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further...`
- `calc_skip_ws` (function) `src/css_box.c:739` `static void calc_skip_ws(calc_parser *p)`
- `calc_match_fn` (function) `src/css_box.c:746` `static int calc_match_fn(calc_parser *p, const char *name)` -- bare0: the token was a unitless 0.
- `calc_piecewise` (function) `src/css_box.c:773` `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)` -- Shared by BOTH symbolic components: the percentage is piecewise for exactly the same reason the em derivative is...
- `calc_mathfn` (function) `src/css_box.c:788` `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` -- min()/max()/clamp() (2026-07-10): comma-separated full expressions, every argument the same shape (all lengths or...
- `min` (function) `src/css_box.c:807` `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the...`
- `calc_term` (function) `src/css_box.c:911` `static int calc_term(calc_parser *p, calc_val *out, int depth)` -- out->pct = num; out->is_length = 1;   /* a <percentage> is dimensional, like a length ++p->i; return 1; } out->px =...
- `calc_expr` (function) `src/css_box.c:938` `static int calc_expr(calc_parser *p, calc_val *out, int depth)`
- `calc_eval_full` (function) `src/css_box.c:960` `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,
           ...` -- Evaluates the inside of a calc(...) (v[0,vlen), the "calc(" prefix and matching ")" already stripped by the caller).
- `calc_eval_em` (function) `src/css_box.c:974` `static int calc_eval_em(const char *v, size_t vlen, double *out_em)` -- static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em, double *out_pct) { calc_parser...
- `calc_unwrap` (function) `src/css_box.c:982` `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` -- True if s (already trimmed) is a "calc(...)" call spanning the whole string (case-insensitive keyword, balanced...
- `cb_interp_len` (function) `src/css_box.c:1033` `int cb_interp_len(const char *v, int allow_auto, int *out)`
- `pct_slot_of` (function) `src/css_box.c:1062` `static int pct_slot_of(int slot)` -- The css_pct_slot mirroring a px length slot, or -1 when the property does not accept the <length-percentage> type.
- `cb_value_em_milli` (function) `src/css_box.c:1112` `int cb_value_em_milli(const char *v)` -- The font-relative derivative of `v`, in thousandths of an em, saturating at CSS_EM_MILLI_MAX.
- `cb_clip_inset` (function) `src/css_box.c:1132` `int cb_clip_inset(const char *val, int px[4], int pm[4])`
- `cb_interp_lp` (function) `src/css_box.c:1166` `int cb_interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_px, ...`
- `term` (function) `src/css_box.c:1173` `* the same expression and failed closed on the percentage term (its property * may not accept one);`
- `interp_len` (function) `src/css_box.c:1342` `* this file that might hand a token to interp_len (transitively: margin/padding/
 * inset, flex-b...`
- `cb_expand_box2` (function) `src/css_box.c:1413` `int cb_expand_box2(const char *val, int slot_start, int slot_end,
                       int allo...` -- Expands a two-slot logical shorthand (margin-inline / padding-block / inset-inline: one value sets both sides, two...

## src/css_chain.c
Depends on: `include/css_chain.h`, `include/css_select.h`
- `cls_space` (function) `src/css_chain.c:42` `static int cls_space(char c)`
- `release_nodes` (function) `src/css_chain.c:90` `static void release_nodes(cch_node *nodes, int n)` -- memcpy(buf, v, n); buf[n] = '\0'; size_t nc = 0; for (size_t i = 0; i < n && nc < cap_tok; ) { while (i < n &&...
- `fill_css_node` (function) `src/css_chain.c:99` `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)` -- Fills *node with element e's tag/id/class tokens (no style=, no parent link yet). * Over-long tokens are simply...
- `sibling_position` (function) `src/css_chain.c:181` `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)` -- Computes the 1-based index of n among its ELEMENT siblings and the total element-sibling count (both walks bounded...
- `sibling_type_position` (function) `src/css_chain.c:199` `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)` -- Like sibling_position but only counts siblings with the SAME local name as n. * R2: for :nth-of-type() /...
- `count_children` (function) `src/css_chain.c:227` `static int count_children(lxb_dom_node_t *n)` -- Counts ALL child nodes (elements, text, comments) of the DOM element n. * R2: for :empty matching.
- `inputs` (function) `src/css_chain.c:241` `* identical inputs (single source of truth). */
static const css_element *build_chain(lxb_dom_ele...`
- `cch_element_style_vars` (function) `src/css_chain.c:310` `css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,
                 ...`
- `cch_path_new` (function) `src/css_chain.c:353` `cch_path *cch_path_new(void)`
- `path_truncate` (function) `src/css_chain.c:357` `static void path_truncate(cch_path *pa, int keep)`
- `cch_path_free` (function) `src/css_chain.c:365` `void cch_path_free(cch_path *pa)`
- `cch_element_style_path` (function) `src/css_chain.c:372` `css_style cch_element_style_path(cch_path *pa, lxb_dom_element_t *el, const css_sheet *sheet,
   ...`
- `cch_pseudo_style` (function) `src/css_chain.c:439` `css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,
            ...`
- `cch_element_style` (function) `src/css_chain.c:458` `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)`
- `cch_element_matches` (function) `src/css_chain.c:462` `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)`
- `cch_element_matches_any` (function) `src/css_chain.c:476` `int cch_element_matches_any(lxb_dom_element_t *el, const css_sel *sels, size_t n)`

## src/css_color.c
Depends on: `include/css_color.h`
- `ascii_lower` (function) `src/css_color.c:119` `static int ascii_lower(int c)`
- `hex_val` (function) `src/css_color.c:123` `static int hex_val(int c)`
- `normalize` (function) `src/css_color.c:132` `static int normalize(const char *token, char *out)` -- Trims surrounding ASCII spaces and lowercases into out (CC_TOKEN_MAX bytes). * Returns 0, or -1 if the trimmed token...
- `parse_hex` (function) `src/css_color.c:146` `static int parse_hex(const char *s, cc_rgb *out)` -- static int normalize(const char *token, char *out) { size_t start = 0; while (token[start] == ' ' || token[start] ==...
- `cc_cws` (function) `src/css_color.c:226` `static void cc_cws(cc_cp *c)`
- `cc_cfactor` (function) `src/css_color.c:229` `static int cc_cfactor(cc_cp *c, cc_cv *out, int depth)`
- `cc_cterm` (function) `src/css_color.c:250` `static int cc_cterm(cc_cp *c, cc_cv *out, int depth)`
- `cc_cexpr` (function) `src/css_color.c:269` `static int cc_cexpr(cc_cp *c, cc_cv *out, int depth)`
- `cc_fold_calc` (function) `src/css_color.c:285` `static int cc_fold_calc(const char **b, const char **e, char *buf, size_t cap)` -- When [*b, *e) is exactly one calc(...), folds it into buf (cap bytes) and repoints the span there.
- `cc_round` (function) `src/css_color.c:305` `static long cc_round(double v)` -- cc_cv r; if (cc_cfactor(&c, &r, 0) != 0) return -1; cc_cws(&c); if (c.p != y || r.v != r.v) return -1; if (r.v >...
- `parse_component` (function) `src/css_color.c:310` `static int parse_component(const char *b, const char *e, int is_alpha, int *out)` -- Parses one rgb() component in [b, e).
- `parse_hsl_comp` (function) `src/css_color.c:343` `static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out)` -- Parses one hsl() component: H is integer 0..360, S/L are 0%..100%. * Returns 0 / -1.
- `span` (function) `src/css_color.c:431` `* span (when a slash is present) into ab/ae, and returns the component count,
 * or -1. Bounded: ...`
- `parse_func` (function) `src/css_color.c:508` `static int parse_func(const char *s, cc_rgb *out)` -- Parses the functional rgb()/rgba()/hsl()/hsla() form (lowercased token).
- `lab_comp` (function) `src/css_color.c:581` `static int lab_comp(const char *b, const char *e, double pct_ref, int is_hue, double *out)` -- One component: a <number>, a <percentage> (scaled so 100% == pct_ref), `none` * (0), or -- when is_hue -- an <angle>...
- `srgb_encode` (function) `src/css_color.c:609` `static unsigned char srgb_encode(double lin)`
- `oklab_to_rgb` (function) `src/css_color.c:616` `static void oklab_to_rgb(double L, double a, double b, cc_rgb *out)`
- `lab_to_rgb` (function) `src/css_color.c:627` `static void lab_to_rgb(double L, double a, double b, cc_rgb *out)` -- return (unsigned char)cc_round(v * 255.0); } static void oklab_to_rgb(double L, double a, double b, cc_rgb *out) {...
- `parse_lab_family` (function) `src/css_color.c:643` `static int parse_lab_family(const char *s, cc_rgb *out)` -- double fy = (L + 16.0) / 116.0, fx = a / 500.0 + fy, fz = fy - b / 200.0; double xr = (fx * fx * fx > e) ? fx * fx *...
- `named_cmp` (function) `src/css_color.c:681` `static int named_cmp(const void *key, const void *element)`
- `parse_named` (function) `src/css_color.c:715` `static int parse_named(const char *s, cc_rgb *out)`
- `cc_parse` (function) `src/css_color.c:728` `cc_status cc_parse(const char *token, cc_rgb *out)`
- `strncmp` (function) `src/css_color.c:743` `strncmp(buf, "oklab(", 6) == 0 || strncmp(buf, "oklch(", 6) == 0)`
- `cc_pack` (function) `src/css_color.c:768` `int cc_pack(cc_rgb c)`
- `cc_unpack` (function) `src/css_color.c:772` `cc_rgb cc_unpack(int packed)`

## src/css_computed.c
Depends on: `include/css_computed.h`
- `put` (function) `src/css_computed.c:9` `static size_t put(char *out, size_t cap, const char *s)`
- `putf` (function) `src/css_computed.c:17` `static size_t putf(char *out, size_t cap, const char *fmt, ...)`
- `put_rgb` (function) `src/css_computed.c:26` `static size_t put_rgb(char *out, size_t cap, int rgb, int alpha_pct)`
- `put_len` (function) `src/css_computed.c:37` `static size_t put_len(char *out, size_t cap, int v, const char *unset_text)`
- `put_enum` (function) `src/css_computed.c:42` `static size_t put_enum(char *out, size_t cap, int v, const char *const *names, size_t n,
        ...`
- `ua_display` (function) `src/css_computed.c:49` `static const char *ua_display(const char *tag)` -- The HTML Rendering UA sheet's `display` for a tag when the cascade declared none * (the engine keeps block-ness of...
- `f_display` (function) `src/css_computed.c:77` `static size_t f_display(const ccm_input *in, char *out, size_t cap)`
- `f_position` (function) `src/css_computed.c:97` `static size_t f_position(const ccm_input *in, char *out, size_t cap)`
- `f_visibility` (function) `src/css_computed.c:102` `static size_t f_visibility(const ccm_input *in, char *out, size_t cap)`
- `f_float` (function) `src/css_computed.c:107` `static size_t f_float(const ccm_input *in, char *out, size_t cap)`
- `f_clear` (function) `src/css_computed.c:112` `static size_t f_clear(const ccm_input *in, char *out, size_t cap)`
- `f_overflow_x` (function) `src/css_computed.c:117` `static size_t f_overflow_x(const ccm_input *in, char *out, size_t cap)`
- `f_overflow_y` (function) `src/css_computed.c:122` `static size_t f_overflow_y(const ccm_input *in, char *out, size_t cap)`
- `f_text_align` (function) `src/css_computed.c:127` `static size_t f_text_align(const ccm_input *in, char *out, size_t cap)`
- `f_box_sizing` (function) `src/css_computed.c:132` `static size_t f_box_sizing(const ccm_input *in, char *out, size_t cap)`
- `f_flex_direction` (function) `src/css_computed.c:137` `static size_t f_flex_direction(const ccm_input *in, char *out, size_t cap)`
- `f_flex_wrap` (function) `src/css_computed.c:142` `static size_t f_flex_wrap(const ccm_input *in, char *out, size_t cap)`
- `f_justify` (function) `src/css_computed.c:147` `static size_t f_justify(const ccm_input *in, char *out, size_t cap)`
- `f_align_items` (function) `src/css_computed.c:153` `static size_t f_align_items(const ccm_input *in, char *out, size_t cap)`
- `f_cursor` (function) `src/css_computed.c:159` `static size_t f_cursor(const ccm_input *in, char *out, size_t cap)`
- `f_white_space` (function) `src/css_computed.c:165` `static size_t f_white_space(const ccm_input *in, char *out, size_t cap)`
- `f_text_transform` (function) `src/css_computed.c:170` `static size_t f_text_transform(const ccm_input *in, char *out, size_t cap)`
- `f_font_style` (function) `src/css_computed.c:175` `static size_t f_font_style(const ccm_input *in, char *out, size_t cap)`
- `f_font_weight` (function) `src/css_computed.c:179` `static size_t f_font_weight(const ccm_input *in, char *out, size_t cap)`
- `f_font_size` (function) `src/css_computed.c:183` `static size_t f_font_size(const ccm_input *in, char *out, size_t cap)`
- `f_line_height` (function) `src/css_computed.c:189` `static size_t f_line_height(const ccm_input *in, char *out, size_t cap)`
- `f_color` (function) `src/css_computed.c:195` `static size_t f_color(const ccm_input *in, char *out, size_t cap)`
- `f_background_color` (function) `src/css_computed.c:200` `static size_t f_background_color(const ccm_input *in, char *out, size_t cap)`
- `f_opacity` (function) `src/css_computed.c:206` `static size_t f_opacity(const ccm_input *in, char *out, size_t cap)`
- `f_z_index` (function) `src/css_computed.c:214` `static size_t f_z_index(const ccm_input *in, char *out, size_t cap)`
- `f_border_style` (function) `src/css_computed.c:219` `static size_t f_border_style(int v, char *out, size_t cap)`
- `NAME` (function) `src/css_computed.c:226` `static size_t NAME(const ccm_input *in, char *out, size_t cap)` -- define LEN_FIELD(NAME, FIELD, UNSET) \
- `f_gap` (function) `src/css_computed.c:246` `static size_t f_gap(const ccm_input *in, char *out, size_t cap)`
- `f_border_top_style` (function) `src/css_computed.c:258` `static size_t f_border_top_style(const ccm_input *in, char *out, size_t cap)`
- `f_border_right_style` (function) `src/css_computed.c:261` `static size_t f_border_right_style(const ccm_input *in, char *out, size_t cap)`
- `f_border_bottom_style` (function) `src/css_computed.c:264` `static size_t f_border_bottom_style(const ccm_input *in, char *out, size_t cap)`
- `f_border_left_style` (function) `src/css_computed.c:267` `static size_t f_border_left_style(const ccm_input *in, char *out, size_t cap)`
- `f_flex_grow` (function) `src/css_computed.c:271` `static size_t f_flex_grow(const ccm_input *in, char *out, size_t cap)`
- `f_flex_shrink` (function) `src/css_computed.c:274` `static size_t f_flex_shrink(const ccm_input *in, char *out, size_t cap)`
- `ccm_get` (function) `src/css_computed.c:312` `size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap)`
- `ccm_property_count` (function) `src/css_computed.c:325` `size_t ccm_property_count(void)`
- `ccm_property_name` (function) `src/css_computed.c:327` `const char *ccm_property_name(size_t i)`

## src/css_counter.c
Depends on: `include/css_counter.h`
- `cnt_hash` (function) `src/css_counter.c:18` `unsigned cnt_hash(const char *name, size_t len)`
- `is_ws` (function) `src/css_counter.c:27` `static int is_ws(char c)`
- `is_ident_start` (function) `src/css_counter.c:29` `static int is_ident_start(unsigned char c)`
- `is_ident_char` (function) `src/css_counter.c:32` `static int is_ident_char(unsigned char c)`
- `ci_eq` (function) `src/css_counter.c:34` `static int ci_eq(const char *a, const char *b)`
- `valid_name` (function) `src/css_counter.c:45` `static int valid_name(const char *s, size_t n)` -- A <custom-ident> usable as a counter name: identifier syntax, not a CSS-wide * keyword or `none`, and short enough...
- `cnt_parse_decls` (function) `src/css_counter.c:59` `int cnt_parse_decls(const char *val, int dflt, cnt_decl out[CNT_MAX_DECL])`
- `put` (function) `src/css_counter.c:102` `static size_t put(char *out, size_t cap, size_t o, const char *s)`
- `utf8_put` (function) `src/css_counter.c:107` `static void utf8_put(char *buf, unsigned cp)`
- `cnt_format` (function) `src/css_counter.c:120` `size_t cnt_format(int style, long value, char *out, size_t cap)`
- `style_of` (function) `src/css_counter.c:174` `static int style_of(const char *name)`
- `sk_char` (function) `src/css_counter.c:192` `static void sk_char(sink *k, char c)`
- `sk_str` (function) `src/css_counter.c:196` `static void sk_str(sink *k, const char *s)`
- `read_string` (function) `src/css_counter.c:201` `static const char *read_string(const char *p, char *dst, size_t cap)` -- A quoted string at p (p[0] is the quote).
- `split_args` (function) `src/css_counter.c:238` `static int split_args(const char *a, const char *b, char (*f)[CNT_STR_MAX], int max)` -- continue; } cp = (unsigned char)*p; } if (cp >= 0x20 && o + 1 < cap) dst[o++] = (char)cp; else if (cp >= 0x20)...
- `cnt_is_marker` (function) `src/css_counter.c:272` `int cnt_is_marker(const char *s)`
- `has_counter_fn` (function) `src/css_counter.c:276` `static int has_counter_fn(const char *v)`
- `cnt_parse_content` (function) `src/css_counter.c:286` `int cnt_parse_content(const char *val, char *out, size_t cap)`
- `cnt_state_new` (function) `src/css_counter.c:366` `cnt_state *cnt_state_new(void)`
- `cnt_state_free` (function) `src/css_counter.c:367` `void cnt_state_free(cnt_state *s)`
- `top_of` (function) `src/css_counter.c:369` `static cnt_inst *top_of(cnt_state *s, unsigned name)`
- `clampv` (function) `src/css_counter.c:375` `static int clampv(long v)`
- `cnt_reset` (function) `src/css_counter.c:379` `void cnt_reset(cnt_state *s, int depth, const cnt_decl *d, int n)`
- `cnt_increment` (function) `src/css_counter.c:392` `void cnt_increment(cnt_state *s, int depth, const cnt_decl *d, int n)`
- `cnt_leave` (function) `src/css_counter.c:407` `void cnt_leave(cnt_state *s, int depth)`
- `cnt_resolve` (function) `src/css_counter.c:412` `size_t cnt_resolve(const cnt_state *s, const char *marker, cnt_attr_fn attr, void *ctx,
         ...`

## src/css_gradient.c
Depends on: `include/css_color.h`, `include/css_decl.h`, `include/css_gradient.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`
- `cg_parse_num` (function) `src/css_gradient.c:13` `static int cg_parse_num(const char *s, double *out, const char **endp)`
- `cg_wide_keyword` (function) `src/css_gradient.c:18` `static int cg_wide_keyword(const char *v)`
- `gradient` (function) `src/css_gradient.c:28` `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,
 * the whole decl...`
- `find_gradient_call` (function) `src/css_gradient.c:77` `static int find_gradient_call(const char *v, const char *fn, size_t *start,
                     ...` -- Locates a gradient function call `fn` (e.g. "linear-gradient(") in v (case-insensitive; an occurrence that is the...
- `conic_prelude` (function) `src/css_gradient.c:111` `static int conic_prelude(const char *seg, int *angle)` -- conic-gradient prelude: `from <int>deg`, optionally followed by `at <pos>` (position accepted and ignored -- always...
- `grad_stop_pos` (function) `src/css_gradient.c:153` `static int grad_stop_pos(const char *pp, int conic, const char **endp)` -- One stop position after a color: `N%` -> 0-1000 (x10); conic also accepts `Ndeg` -> the same 0-1000 turn fraction...
- `CSS_GRAD_STOPS_MAX` (function) `src/css_gradient.c:184` `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when
 * the gradient fai...`
- `emit_gradient` (function) `src/css_gradient.c:291` `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,
                         ...` -- Emits the gradient decl group. nstops == 0 emits only the explicit reset * (P_BG_GRAD_N = 0), which is how a...
- `find_radial_gradient` (function) `src/css_gradient.c:360` `static int find_radial_gradient(const char *v, size_t *start, size_t *end,
                      ...` -- R5c: detects radial-gradient(circle at center, color1, color2).
- `cg_first_url` (function) `src/css_gradient.c:398` `int cg_first_url(const char *val, char *out, size_t outcap)`
- `emit_radial_geom` (function) `src/css_gradient.c:405` `static int emit_radial_geom(css_decl *dst, int cap, const cg_radial *r)` -- } memcpy(urltab[*nurl], url, strlen(url) + 1); dst[0].ival = (int)*nurl; ++*nurl; return 1; } int cg_first_url(const...
- `pool` (function) `src/css_gradient.c:418` `* pool (gradient explicitly reset);`
- `downstream` (function) `src/css_gradient.c:422` `* happens downstream (render_doc.c), gated by caps.images like an <img>. */
int cg_expand_bg_imag...`
- `declaration` (function) `src/css_gradient.c:483` `* declaration (fail closed);`
- `bg_layer_tokens_ok` (function) `src/css_gradient.c:490` `static int bg_layer_tokens_ok(const char *s)` -- True iff every token of s (split on whitespace, '/' and ',') is a valid non-colour component of a background layer...
- `cg_expand_background` (function) `src/css_gradient.c:530` `int cg_expand_background(const char *val, css_decl *dst, int cap,
                             ch...`
- `rad_ieq` (function) `src/css_gradient.c:618` `static int rad_ieq(const char *a, const char *b)`
- `rad_len` (function) `src/css_gradient.c:626` `static int rad_len(const char *tok, int *enc)` -- One <length-percentage> token (`12px`, `40%`, `0`) -> the cg_radial encoding; 1 = ok.
- `rad_is_len_start` (function) `src/css_gradient.c:647` `static int rad_is_len_start(const char *t)`
- `rad_pos_kw` (function) `src/css_gradient.c:652` `static int rad_pos_kw(const char *t, int *axis)` -- if (*e == '\0' && v == 0.0) { *enc = 0; return 1; }   /* unitless 0 is a zero length if (rad_ieq(e, "px")) { if (v >...
- `rad_parse_position` (function) `src/css_gradient.c:661` `static int rad_parse_position(char (*tok)[CSS_TOK_MAX], int n, int *cx, int *cy)`
- `cg_parse_radial_prelude` (function) `src/css_gradient.c:690` `int cg_parse_radial_prelude(const char *seg, cg_radial *out)`
- `cg_radial_len_px` (function) `src/css_gradient.c:766` `double cg_radial_len_px(int enc, double dim)`
- `cg_dmin` (function) `src/css_gradient.c:775` `static double cg_dmin(double a, double b)`
- `cg_dmax` (function) `src/css_gradient.c:776` `static double cg_dmax(double a, double b)`
- `cg_radial_geometry` (function) `src/css_gradient.c:778` `void cg_radial_geometry(const cg_radial *r, double w, double h,
                        double *c...`
- `cg_parse_linear` (function) `src/css_gradient.c:815` `int cg_parse_linear(const char *fn, int *angle, int *colors, int *positions)`

## src/css_index.c
Depends on: `include/css_index.h`
- `key_of` (function) `src/css_index.c:11` `static uint64_t key_of(int kind, const char *s, size_t n, int lower)` -- FNV-1a over the kind byte then the name; the tag is hashed lowercased because * compound_matches compares it with...
- `key_of_token` (function) `src/css_index.c:26` `static uint64_t key_of_token(int kind, const char *tok)` -- An element token in the canonical form csel_ident_eq compares against: as-is * when it fits CSS_TOK_MAX, folded...
- `entry_cmp` (function) `src/css_index.c:34` `static int entry_cmp(const void *a, const void *b)`
- `cix_free` (function) `src/css_index.c:40` `void cix_free(cix_index *idx)`
- `build` (function) `src/css_index.c:47` `static void build(const css_sel *arr, css_sel *const *ptrs, size_t n, cix_index *idx)`
- `lower_bound` (function) `src/css_index.c:86` `static size_t lower_bound(const cix_index *idx, uint64_t k)` -- keyed[nk].key = k; keyed[nk].sel = (uint32_t)i; ++nk; } qsort(keyed, nk, sizeof *keyed, entry_cmp); idx->keyed =...
- `run_head` (function) `src/css_index.c:104` `static uint32_t run_head(const cix_run *r)`
- `add_bucket` (function) `src/css_index.c:106` `static void add_bucket(const cix_index *idx, uint64_t k, cix_run *runs, size_t *nr)`
- `push` (function) `src/css_index.c:114` `static int push(uint32_t **buf, size_t *cap, size_t *n, uint32_t v)`
- `cix_candidates` (function) `src/css_index.c:129` `size_t cix_candidates(const cix_index *idx, const css_element *el,
                      uint32_t...` -- Candidates in ascending selector order without duplicates: a k-way merge of the (already * sorted) universal list...
- `cix_build` (function) `src/css_index.c:166` `void cix_build(const css_sel *sels, size_t n, cix_index *idx)`
- `cix_build_ptrs` (function) `src/css_index.c:168` `void cix_build_ptrs(css_sel *const *sels, size_t n, cix_index *idx)`

## src/css_length.c
Depends on: `include/css.h`, `include/css_length.h`
- `know` (function) `src/css_length.c:7` `* this module cannot know (real font metrics, the viewport) arrives through
 * cl_ctx rather than...`
- `cl_unit_eq` (function) `src/css_length.c:30` `static int cl_unit_eq(const char *unit, size_t len, const char *lit)` -- ASCII case-insensitive compare of a possibly-unterminated unit slice against a lowercase literal.
- `cl_font_size` (function) `src/css_length.c:56` `static double cl_font_size(const cl_ctx *ctx)` -- The element's font-size, falling back to the CSS initial value when the caller left it unset.
- `cl_root_font_size` (function) `src/css_length.c:60` `static double cl_root_font_size(const cl_ctx *ctx)`
- `cl_metric_or` (function) `src/css_length.c:67` `static double cl_metric_or(double measured, double ratio, const cl_ctx *ctx)` -- A font metric, or the fallback the spec itself names for when that metric is unavailable -- expressed as a ratio of...
- `cl_viewport_scale` (function) `src/css_length.c:80` `static int cl_viewport_scale(const char *u, size_t len, const cl_ctx *ctx, double *per)` -- Viewport-relative units (section 6.2).
- `cl_ctx_initial` (function) `src/css_length.c:100` `cl_ctx cl_ctx_initial(void)`
- `cl_unit_scale` (function) `src/css_length.c:117` `cl_status cl_unit_scale(const char *unit, size_t unit_len,
                        const cl_ctx *...`
- `cl_is_length_unit` (function) `src/css_length.c:167` `int cl_is_length_unit(const char *unit, size_t unit_len)`
- `cl_unit_is_font_relative` (function) `src/css_length.c:174` `int cl_unit_is_font_relative(const char *unit, size_t unit_len)`
- `cl_em_refit` (function) `src/css_length.c:219` `double cl_em_refit(double px, double em, double from_font_size, double font_size)`
- `cl_parse_number` (function) `src/css_length.c:233` `static int cl_parse_number(const char **pp, const char *end, double *out)` -- Parses a CSS <number> (CSS Syntax 4.3.12) without strtod -- strtod is locale-dependent, and a locale whose decimal...
- `cl_number` (function) `src/css_length.c:292` `int cl_number(const char *s, double *out, const char **endp)`
- `cl_resolve_core` (function) `src/css_length.c:309` `static cl_status cl_resolve_core(const char *value, const cl_ctx *ctx, cl_lp *out)` -- The shared core of cl_resolve and cl_resolve_lp: tokenize <number><unit> and resolve it into the two components of a...
- `cl_resolve` (function) `src/css_length.c:377` `cl_status cl_resolve(const char *value, const cl_ctx *ctx, double *out_px)`
- `cl_resolve_lp` (function) `src/css_length.c:391` `cl_status cl_resolve_lp(const char *value, const cl_ctx *ctx, cl_lp *out)`
- `cl_lp_used` (function) `src/css_length.c:395` `double cl_lp_used(cl_lp lp, double basis)`

## src/css_mask.c
Depends on: `include/css_gradient.h`, `include/css_mask.h`
- `ieq` (function) `src/css_mask.c:13` `static int ieq(const char *a, const char *b)`
- `cm_is_mask_prop` (function) `src/css_mask.c:19` `int cm_is_mask_prop(const char *prop)`
- `cm_encode_layer` (function) `src/css_mask.c:26` `void cm_encode_layer(const cm_layer *l, int *meta, int *alphas, int *poss)`
- `cm_decode_layer` (function) `src/css_mask.c:47` `void cm_decode_layer(int meta, int alphas, int poss, cm_layer *out)`
- `split` (function) `src/css_mask.c:65` `static int split(const char *s, int comma, char (*out)[CM_TOK_MAX], int max)` -- out->kind = 1; out->nst = (meta >> 4) & 0xf; if (out->nst < 2) out->nst = 2; if (out->nst > 4) out->nst = 4...
- `composite_word` (function) `src/css_mask.c:92` `static int composite_word(const char *t, int webkit)`
- `clip_word` (function) `src/css_mask.c:106` `static int clip_word(const char *t)`
- `image_layer` (function) `src/css_mask.c:114` `static int image_layer(const char *tok, cm_layer *l)` -- if (ieq(t, "source-in")) return CM_COMP_INTERSECT; if (ieq(t, "xor")) return CM_COMP_EXCLUDE; } return -1; } static...
- `emit_layers` (function) `src/css_mask.c:132` `static int emit_layers(css_decl *dst, int cap, int shorthand, const char *val)`
- `cm_expand` (function) `src/css_mask.c:201` `int cm_expand(const char *prop, const char *val, css_decl *dst, int cap, int webkit_vocab)`

## src/css_mq.c
Depends on: `include/css_length.h`, `include/css_mq.h`
- `lower_ch` (function) `src/css_mq.c:31` `static char lower_ch(char c)`
- `is_space` (function) `src/css_mq.c:35` `static int is_space(char c)`
- `is_ident_ch` (function) `src/css_mq.c:39` `static int is_ident_ch(char c)`
- `skip_ws` (function) `src/css_mq.c:44` `static void skip_ws(mq_cur *c)`
- `read_word` (function) `src/css_mq.c:49` `static int read_word(mq_cur *c, char *w, size_t cap)` -- static int is_space(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'; } static int...
- `peek_word` (function) `src/css_mq.c:61` `static int peek_word(const mq_cur *c, char *w, size_t cap)` -- /* Reads one identifier at the cursor (lowercased into w); 0 if none. static int read_word(mq_cur *c, char *w...
- `and3` (function) `src/css_mq.c:66` `static int and3(int a, int b)`
- `or3` (function) `src/css_mq.c:72` `static int or3(int a, int b)`
- `not3` (function) `src/css_mq.c:78` `static int not3(int a)`
- `copy_trim_lower` (function) `src/css_mq.c:83` `static int copy_trim_lower(const char *s, size_t a, size_t b, char *dst, size_t cap)` -- return MQ_TRUE; } static int or3(int a, int b) { if (a == MQ_TRUE || b == MQ_TRUE) return MQ_TRUE; if (a ==...
- `feature_of` (function) `src/css_mq.c:106` `static fval feature_of(const char *name, const cmq_env *env)` -- /* --- feature values --- typedef enum { FV_NONE, FV_NUM, FV_KW } fv_kind; typedef struct fval { fv_kind     kind...
- `read_num` (function) `src/css_mq.c:162` `static int read_num(const char *t, double *out, const char **end)` -- } else if (strcmp(name, "update") == 0) { v.kind = FV_KW; v.kw = "fast"; } else if (strcmp(name, "overflow-block")...
- `parse_value` (function) `src/css_mq.c:167` `static int parse_value(const char *t, int unit, double *out)` -- || strcmp(name, "video-dynamic-range") == 0) { v.kind = FV_KW; v.kw = "standard"; } else if (strcmp(name, "scan") ==...
- `cmp_op` (function) `src/css_mq.c:206` `static int cmp_op(double lhs, int op, double rhs)` -- if (strcmp(e, "dpcm") == 0) { out = n * CMQ_CM_PER_IN / CMQ_DPI_PER_DPPX; return 1; } return 0; } if (*e != '\0')...
- `flip_op` (function) `src/css_mq.c:218` `static int flip_op(int op)` -- /* op: '<' '<=' '>' '>=' '=' encoded as 1..5.
- `bool_ctx` (function) `src/css_mq.c:229` `static int bool_ctx(const fval *v)` -- } /* Flips an operator so that `v op name` reads `name op' v`. static int flip_op(int op) { switch (op) { case 1...
- `eval_plain` (function) `src/css_mq.c:237` `static int eval_plain(const char *name, const char *value, const cmq_env *env)` -- case 4: return 2; default: return op; } } /* Boolean context (MQ4 2.4.2): true unless the value is 0 or `none`....
- `read_op` (function) `src/css_mq.c:266` `static int read_op(const char **p)` -- fval f = feature_of(base, env); if (f.kind == FV_NONE) return MQ_UNKNOWN; if (f.kind == FV_KW) { if (range != 0)...
- `eval_range` (function) `src/css_mq.c:280` `static int eval_range(const char *t, const cmq_env *env)` -- static int read_op(const char **p) { const char *q = *p; int op = 0; if (q[0] == '<' && q[1] == '=') { op = 2; q +=...
- `eval_feature` (function) `src/css_mq.c:328` `static int eval_feature(const char *s, size_t a, size_t b, const cmq_env *env)` -- } /* v1 op name op v2: both operators point the same way (MQ4 grammar). int lt = (ops[0] == 1 || ops[0] == 2) &&...
- `eval_in_parens` (function) `src/css_mq.c:353` `static int eval_in_parens(mq_cur *c, int depth)` -- if (name[0] == '\0' || value[0] == '\0') return MQ_UNKNOWN; return eval_plain(name, value, env); } if (strpbrk(t...
- `eval_cond` (function) `src/css_mq.c:380` `static int eval_cond(mq_cur *c, int depth)` -- mq_cur in = { c->s, open + 1, close, c->env }; skip_ws(&in); char w[16]; int nested = (in.i < in.b && in.s[in.i] ==...
- `eval_query` (function) `src/css_mq.c:404` `static int eval_query(const char *s, size_t a, size_t b, const cmq_env *env)` -- skip_ws(c); if (c->i >= c->b) break; mq_cur save = *c; if (!read_word(c, w, sizeof w)) { *c = save; break; } int m =...
- `cmq_matches` (function) `src/css_mq.c:458` `int cmq_matches(const char *s, size_t len, const cmq_env *env)`
- `has_word` (function) `src/css_mq.c:479` `static int has_word(const char *t, const char *w)` -- while (i < len && !(s[i] == ',' && d == 0)) { if (s[i] == '(') ++d; else if (s[i] == ')') --d; ++i; } if...
- `cmq_container_surely` (function) `src/css_mq.c:489` `int cmq_container_surely(const char *s, size_t len, int max_width)`

## src/css_select.c
Depends on: `include/css_select.h`
- `csel_hex_val` (function) `src/css_select.c:25` `int csel_hex_val(char c)` -- CSS Syntax 4.3.7 escape consumption (moved from css.c; shared by quoted content values and selector identifiers).
- `csel_emit_utf8` (function) `src/css_select.c:32` `size_t csel_emit_utf8(unsigned int cp, char *out)`
- `csel_unescape` (function) `src/css_select.c:54` `void csel_unescape(char *dst, size_t cap, const char *src, size_t n)`
- `csel_escape_len` (function) `src/css_select.c:93` `size_t csel_escape_len(const char *s, size_t i, size_t b)`
- `csel_decl_end` (function) `src/css_select.c:106` `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace)`
- `ident_hash` (function) `src/css_select.c:123` `static unsigned long long ident_hash(const char *s, size_t n)` -- 64-bit FNV-1a of the whole identifier: what makes a folded long name exact up to * a hash collision -- and a...
- `csel_ident_fold` (function) `src/css_select.c:129` `void csel_ident_fold(const char *src, size_t len, char *dst)`
- `csel_ident_eq` (function) `src/css_select.c:144` `int csel_ident_eq(const char *stored, const char *tok, size_t tlen)`
- `csel_read_ident` (function) `src/css_select.c:152` `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower)`
- `parse_attr_sel` (function) `src/css_select.c:186` `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)` -- Parses one attribute selector starting at s[*ip] == '[' (within s[.,b)) into *am.
- `parse_nth_arg` (function) `src/css_select.c:243` `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)` -- Parses the An+B argument of the nth-child family, s[a,b) (surrounding space trimmed here).
- `take_sub_arg` (function) `src/css_select.c:295` `static int take_sub_arg(const char *s, size_t a, size_t b, css_sel *sel, int strict);`
- `between` (function) `src/css_select.c:384` `* between ( and ) is split on commas (not inside [] or ());`
- `simple_pseudo_kind` (function) `src/css_select.c:439` `static int simple_pseudo_kind(const char *nm)` -- The PSEUDO_* kind of an argument-less pseudo-class usable inside a * sub-selector, or -1.
- `parse_sub_compound` (function) `src/css_select.c:460` `static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub)` -- Parses one SIMPLE sub-selector span s[a,b) for :not()/:is()/:where(): only tag name, .class, #id, or [attr] (no...
- `parse_compound` (function) `src/css_select.c:525` `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,
                  ...` -- Parses one COMPOUND selector span s[a,b) (no combinators, no surrounding space) into *cp. sel holds the sub-selector...
- `selector` (function) `src/css_select.c:567` `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is
 * dropped. Whitespa...`
- `csel_element_feature_bits` (function) `src/css_select.c:587` `unsigned long long csel_element_feature_bits(const css_element *e)`
- `compute_anc_req` (function) `src/css_select.c:602` `static unsigned long long compute_anc_req(const css_sel *sel)` -- What the ancestors of the subject must contain: walk left from the subject while the combinator is descendant or...
- `csel_parse_core` (function) `src/css_select.c:615` `static int csel_parse_core(const char *s, size_t a, size_t b, css_sel *sel)`
- `seven` (function) `src/css_select.c:621` `* pay for the other seven (a css_sel is ~12.8 KiB). */ memset(sel, 0, offsetof(css_sel, parts));`
- `compound_req` (function) `src/css_select.c:709` `static unsigned long long compound_req(const css_compound *c)` -- } else { psel += 10; } } spec += 100 * (sel->parts[k].has_id ?
- `compute_subj_req` (function) `src/css_select.c:718` `static unsigned long long compute_subj_req(const css_sel *sel)`
- `csel_compact_size` (function) `src/css_select.c:729` `size_t csel_compact_size(int nparts)`
- `csel_compact_dup` (function) `src/css_select.c:735` `css_sel *csel_compact_dup(const css_sel *sel)`
- `csel_parse` (function) `src/css_select.c:744` `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel)`
- `el_attr_value` (function) `src/css_select.c:755` `static const char *el_attr_value(const css_element *el, const char *name)` -- The value of element attribute `name` (case-insensitive name), or NULL if absent. * A present attribute with no...
- `ends_with` (function) `src/css_select.c:765` `static int ends_with(const char *v, const char *suf, int ci)` -- The value of element attribute `name` (case-insensitive name), or NULL if absent. * A present attribute with no...
- `has_word` (function) `src/css_select.c:773` `static int has_word(const char *v, const char *w, int ci)` -- True if `v` is a whitespace-separated list containing the word `w` (non-empty), * case-folded when ci (the `~=`...
- `attr_matches` (function) `src/css_select.c:788` `static int attr_matches(const css_attr_match *am, const css_element *el)` -- size_t wl = strlen(w); if (wl == 0) return 0; const char *p = v; while (*p != '\0') { while (*p == ' ' || *p == '\t'...
- `nth_matches` (function) `src/css_select.c:808` `static int nth_matches(int A, int B, int idx)` -- True if the 1-based index idx satisfies idx = A*m + B for some integer m >= 0. * idx <= 0 means "unknown sibling...
- `is_form_control` (function) `src/css_select.c:817` `static int is_form_control(const char *tag)` -- True if the 1-based index idx satisfies idx = A*m + B for some integer m >= 0. * idx <= 0 means "unknown sibling...
- `pseudo_matches` (function) `src/css_select.c:826` `static int pseudo_matches(const css_pseudo_match *pm, const css_element *el, const css_sel *sel, const char...` -- if (A > 0) return d >= 0 && d % A == 0; return d <= 0 && (-d) % (long)(-A) == 0; } /* Form controls for :enabled...
- `sub_sel_matches` (function) `src/css_select.c:830` `static int sub_sel_matches(const css_sub_sel *sub, const css_element *el)`
- `compound_matches` (function) `src/css_select.c:1080` `static int compound_matches(const css_compound *c, const css_element *el,
                       ...` -- True if one compound matches one element (no ancestor context).
- `built` (function) `src/css_select.c:1115` `* chains the caller built (an element without parent/prev links never matches
 * through that com...`
- `pseudo_is_local` (function) `src/css_select.c:1160` `static int pseudo_is_local(int kind)` -- case COMB_ADJACENT: return (el->prev != NULL) && complex_matches(sel, k - 1, el->prev, target_id, allow_pseudo_el...
- `csel_needs_structure` (function) `src/css_select.c:1173` `int csel_needs_structure(const css_sel *sel)`
- `csel_matches` (function) `src/css_select.c:1196` `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,
              ...`

## src/css_text.c
Depends on: `include/css.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_text.h`, `include/css_values.h`
- `ct_family_of` (function) `src/css_text.c:18` `static int ct_family_of(const char *name)` -- Maps one font-family name (a generic keyword or a common family) to a generic css_font_family bucket; -1 if...
- `ct_interp_fontfamily` (function) `src/css_text.c:47` `int ct_interp_fontfamily(const char *v)` -- font-family: the first recognised name in the comma-separated stack wins (its * generic bucket).
- `ct_interp_texttransform` (function) `src/css_text.c:69` `int ct_interp_texttransform(const char *v)`
- `ct_interp_valign` (function) `src/css_text.c:91` `int ct_interp_valign(const char *v)`
- `ct_expand_valign` (function) `src/css_text.c:122` `int ct_expand_valign(const char *val, css_decl *dst, int cap)` -- vertical-align (CSS 2.1 section 10.8.1) has two productions: a keyword, and a <length-percentage> baseline SHIFT...
- `transition_prop_one` (function) `src/css_text.c:139` `static int transition_prop_one(const char *v)`
- `ct_interp_whitespace` (function) `src/css_text.c:182` `int ct_interp_whitespace(const char *v)`
- `ct_interp_tabsize` (function) `src/css_text.c:195` `int ct_interp_tabsize(const char *v)` -- break-spaces preserves whitespace and wraps; this engine only models the * wrap/keep distinction, so it collapses to...
- `ct_interp_textdeco_style` (function) `src/css_text.c:206` `int ct_interp_textdeco_style(const char *v)` -- } /* tab-size: a non-negative integer (number of spaces). -1 if unsupported. int ct_interp_tabsize(const char *v) {...
- `ct_interp_textdeco_thickness` (function) `src/css_text.c:217` `int ct_interp_textdeco_thickness(const char *v)` -- text-decoration-thickness: `from-font` (keyword -> 0), or a non-negative length * (px -> px, em/rem x16). -1 if...
- `ct_interp_aspect_ratio` (function) `src/css_text.c:229` `int ct_interp_aspect_ratio(const char *v, int *num, int *den)` -- aspect-ratio: `auto`, a `<ratio>` such as `16/9` or `1.5`, or `auto <ratio>` (auto fallback).
- `ct_interp_direction` (function) `src/css_text.c:271` `int ct_interp_direction(const char *v)` -- Both halves share ONE scale, so the ratio keeps its shape: clamping each half to * CSS_LEN_MAX on its own turned...
- `ct_liststyle_kw` (function) `src/css_text.c:277` `static int ct_liststyle_kw(const char *t)`
- `ct_liststyle_unknown_name` (function) `src/css_text.c:298` `static int ct_liststyle_unknown_name(const char *t)` -- A <counter-style> name this engine has no glyph set for.
- `ct_interp_liststyle` (function) `src/css_text.c:309` `int ct_interp_liststyle(const char *v)` -- list-style-type, or the type token of the list-style shorthand: the first * recognised keyword wins. url() (a...
- `ct_emit_spacing` (function) `src/css_text.c:344` `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
- `ct_expand_shadow` (function) `src/css_text.c:357` `int ct_expand_shadow(const char *val, css_decl *dst, int cap)` -- text-shadow (single layer): collects up to three lengths (dx, dy, blur — blur is ignored) and an optional color, in...

## src/css_values.c
Depends on: `include/css.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`
- `cv_parse_num` (function) `src/css_values.c:11` `static int cv_parse_num(const char *s, double *out, const char **endp)`
- `cv_parse_color` (function) `src/css_values.c:16` `int cv_parse_color(const char *v)`
- `cv_interp_color` (function) `src/css_values.c:36` `int cv_interp_color(const char *v)`
- `cv_color_ok` (function) `src/css_values.c:41` `int cv_color_ok(int c)`
- `cv_bg_alpha_of` (function) `src/css_values.c:46` `int cv_bg_alpha_of(const char *v)`
- `cv_interp_bg` (function) `src/css_values.c:160` `int cv_interp_bg(const char *v)`
- `cv_parse_color_t7` (function) `src/css_values.c:205` `int cv_parse_color_t7(const char *v)`
- `cv_text_color` (function) `src/css_values.c:222` `int cv_text_color(const char *v)`
- `cv_filter_scale` (function) `src/css_values.c:231` `double cv_filter_scale(int pct)`

## src/css_vars.c
Depends on: `include/css_select.h`, `include/css_vars.h`
- `name_hash` (function) `src/css_vars.c:12` `static size_t name_hash(const char *s, size_t n)`
- `dup_n` (function) `src/css_vars.c:21` `static char *dup_n(const char *s, size_t n)`
- `find_slot` (function) `src/css_vars.c:32` `static size_t find_slot(const cvr_table *t, const char *name, size_t nlen)` -- Index into t->slot where name lives, or the empty slot where it would go. * Requires t->nslot > t->n (the index is...
- `grow` (function) `src/css_vars.c:45` `static int grow(cvr_table *t)` -- Requires t->nslot > t->n (the index is never full). static size_t find_slot(const cvr_table *t, const char *name...
- `cvr_set` (function) `src/css_vars.c:67` `int cvr_set(cvr_table *t, const char *name, size_t nlen, const char *value, size_t vlen)`
- `cvr_get` (function) `src/css_vars.c:94` `const char *cvr_get(const cvr_table *t, const char *name, size_t nlen)`
- `cvr_count` (function) `src/css_vars.c:100` `size_t cvr_count(const cvr_table *t)`
- `cvr_reset` (function) `src/css_vars.c:102` `void cvr_reset(cvr_table *t)`
- `cvr_free` (function) `src/css_vars.c:112` `void cvr_free(cvr_table *t)`
- `is_ws` (function) `src/css_vars.c:120` `static int is_ws(char c)`
- `without_important` (function) `src/css_vars.c:124` `static size_t without_important(const char *val, size_t n)` -- Length of val[0,n) once a trailing !important (optional blanks around the '!') * is removed, trailing blanks included.
- `cvr_collect_decls` (function) `src/css_vars.c:139` `void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b)`
- `scope_get` (function) `src/css_vars.c:164` `static const char *scope_get(const cvr_scope *sc, const char *name, size_t nlen)`
- `env_value` (function) `src/css_vars.c:182` `static const char *env_value(const char *name, size_t n)` -- The value an env() name resolves to on this device class (CSS Environment Variables 1): a desktop window has no...
- `resolve_rec` (function) `src/css_vars.c:192` `static int resolve_rec(const char *val, size_t vlen, char *out, size_t outcap,
                  ...`
- `cvr_resolve` (function) `src/css_vars.c:281` `int cvr_resolve(const char *val, char *out, size_t outcap, const cvr_scope *sc)`
- `cvr_lookup` (function) `src/css_vars.c:290` `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen)`

## src/data_url.c
Depends on: `include/data_url.h`
- `lower` (function) `src/data_url.c:16` `static int lower(char c)`
- `ci_starts_with` (function) `src/data_url.c:20` `static int ci_starts_with(const char *s, const char *prefix)`
- `du_is_data_url` (function) `src/data_url.c:28` `int du_is_data_url(const char *url)`
- `du_base64_payload` (function) `src/data_url.c:32` `du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len)`
- `du_shape_ok` (function) `src/data_url.c:59` `du_status du_shape_ok(const char *url)`
- `b64_val` (function) `src/data_url.c:70` `static int b64_val(unsigned char c)` -- 0-63 for a base64 alphabet character, -1 otherwise.
- `du_base64_decode` (function) `src/data_url.c:79` `du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len)`
- `hexval` (function) `src/data_url.c:117` `static int hexval(char c)`
- `ascii_ws` (function) `src/data_url.c:124` `static int ascii_ws(char c)`
- `ends_ci` (function) `src/data_url.c:129` `static int ends_ci(const char *s, size_t n, const char *suf)` -- } static int hexval(char c) { if (c >= '0' && c <= '9') return c - '0'; if (c >= 'a' && c <= 'f') return c - 'a' +...
- `du_decode` (function) `src/data_url.c:140` `du_status du_decode(const char *url, char *mime, size_t mime_cap, uint8_t **out, size_t *out_len)`

## src/disk_store.c
Depends on: `include/disk_store.h`, `include/local_store.h`, `include/util.h`
- `fsync_dir` (function) `src/disk_store.c:32` `static void fsync_dir(const char *path)` -- Best-effort fsync of the directory holding path, for crash durability of the * rename.
- `map_ls` (function) `src/disk_store.c:50` `static ds_status map_ls(ls_status s)`
- `ds_write` (function) `src/disk_store.c:66` `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,
               ...`
- `ds_read` (function) `src/disk_store.c:103` `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],
                  uint8_t **ou...`
- `ds_free` (function) `src/disk_store.c:136` `void ds_free(uint8_t *buf, size_t len)`


Next: [API_p8.md](API_p8.md)
