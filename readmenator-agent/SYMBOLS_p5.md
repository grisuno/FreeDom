# Symbols (page 5 of 13)
Previous: [SYMBOLS_p4.md](SYMBOLS_p4.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `AUTO_RESET` | macro | `src/css.c:255` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css.c:256` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css.c:254` | `#define AUTO_VALUE` |
| `CSS_DECL_SLOTS_MIN` | macro | `src/css.c:62` | `#define CSS_DECL_SLOTS_MIN` |
| `CSS_INIT_DECLS` | macro | `src/css.c:47` | `#define CSS_INIT_DECLS` |
| `CSS_INIT_RULES` | macro | `src/css.c:63` | `#define CSS_INIT_RULES` |
| `CSS_INIT_SELS` | macro | `src/css.c:46` | `#define CSS_INIT_SELS` |
| `CSS_INLINE_DECLS` | macro | `src/css.c:65` | `#define CSS_INLINE_DECLS` |
| `CSS_MAX_FONT_FACES` | macro | `src/css.c:150` | `#define CSS_MAX_FONT_FACES` |
| `CSS_MAX_RAW` | macro | `src/css.c:82` | `#define CSS_MAX_RAW` |
| `CSS_MEDIA_MAX_DEPTH` | macro | `src/css.c:3820` | `#define CSS_MEDIA_MAX_DEPTH` |
| `CSS_SELS_PER_GROUP` | macro | `src/css.c:64` | `#define CSS_SELS_PER_GROUP` |
| `CSS_VAR_POOL` | macro | `src/css.c:4908` | `#define CSS_VAR_POOL` |
| `LIST` | function | `src/css.c:2046` | `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose...` |
| `NULL` | function | `src/css.c:5262` | `* Sheet can be NULL (inline style, no @keyframes). */ void css_resolve_anim_keyframes(css_style *...` |
| `P_META_CUSTOM` | macro | `src/css.c:78` | `#define P_META_CUSTOM` |
| `P_META_VARSRC` | macro | `src/css.c:79` | `#define P_META_VARSRC` |
| `add_rule` | function | `src/css.c:3562` | `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,                      siz...` |
| `apply_decl` | function | `src/css.c:4458` | `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_rule` | function | `src/css.c:4938` | `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_var_source` | function | `src/css.c:4912` | `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,         ...` |
| `at_is_media` | function | `src/css.c:3687` | `static int at_is_media(const char *s, size_t i, size_t n)` |
| `at_keyword` | function | `src/css.c:3698` | `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)` |
| `bg_alpha_of` | function | `src/css.c:214` | `static int bg_alpha_of(const char *v)` |
| `block_end` | function | `src/css.c:3665` | `static size_t block_end(const char *s, size_t open, size_t n)` |
| `blur` | function | `src/css.c:1251` | `* consumes ONLY blur(Npx);` |
| `caller` | function | `src/css.c:2710` | `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached...` |
| `cand_cmp` | function | `src/css.c:4847` | `static int cand_cmp(const void *pa, const void *pb)` |
| `collect_custom_props_scoped` | function | `src/css.c:3829` | `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,                 ...` |
| `column` | function | `src/css.c:1608` | `* column (`flex: 1 1 0%`);` |
| `computed_font_size` | function | `src/css.c:4831` | `static double computed_font_size(const css_style *o, const css_element *el)` |
| `copy_trim` | function | `src/css.c:1764` | `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `csel_substr` | function | `src/css.c:3720` | `return known && csel_substr(val, "var(", 1);` |
| `css_cand` | struct | `src/css.c:4842` | `` |
| `css_decl` | function | `src/css.c:86` | `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);` |
| `css_font_face_at` | function | `src/css.c:5298` | `int css_font_face_at(const css_sheet *sheet, size_t i,                      char *family, size_t ...` |
| `css_font_face_count` | function | `src/css.c:5294` | `size_t css_font_face_count(const css_sheet *sheet)` |
| `css_free` | function | `src/css.c:4441` | `void css_free(css_sheet *s)` |
| `css_keyframe_stop` | struct | `src/css.c:132` | `` |
| `css_match` | struct | `src/css.c:4836` | `` |
| `css_parse` | function | `src/css.c:4357` | `css_status css_parse(const char *text, size_t len, css_sheet **out)` |
| `css_parse_inline` | function | `src/css.c:5308` | `css_style css_parse_inline(const char *style, size_t len)` |
| `css_parse_logged` | function | `src/css.c:4371` | `css_status css_parse_logged(const char *text, size_t len, const css_media *media,                ...` |
| `css_parse_media` | function | `src/css.c:4361` | `css_status css_parse_media(const char *text, size_t len, const css_media *media,                 ...` |
| `css_parse_scoped` | function | `src/css.c:4366` | `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,                ...` |
| `css_resolve` | function | `src/css.c:5238` | `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,                   ...` |
| `css_resolve_el` | function | `src/css.c:5005` | `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,                          ...` |
| `css_resolve_el_ex` | function | `src/css.c:5014` | `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,                       ...` |
| `css_resolve_pseudo` | function | `src/css.c:5020` | `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)` |
| `css_rule` | struct | `src/css.c:97` | `` |
| `css_sheet` | struct | `src/css.c:99` | `` |
| `drop_copy_text` | function | `src/css.c:3360` | `static void drop_copy_text(char *dst, size_t cap, const char *src)` |
| `drop_record` | function | `src/css.c:3379` | `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)` |
| `emit` | function | `src/css.c:59` | `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand...` |
| `emit_content` | function | `src/css.c:1387` | `static int emit_content(css_decl *dst, int cap, const char *str,                         char (*c...` |
| `emit_radius_corner` | function | `src/css.c:880` | `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)` |
| `emit_spacing` | function | `src/css.c:348` | `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `empty` | function | `src/css.c:1407` | `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and...` |
| `expand_backdrop_filter` | function | `src/css.c:1254` | `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)` |
| `expand_background` | function | `src/css.c:231` | `static int expand_background(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_bg_image` | function | `src/css.c:226` | `static int expand_bg_image(const char *val, css_decl *dst, int cap,                            ch...` |
| `expand_bg_position` | function | `src/css.c:1287` | `static int expand_bg_position(const char *val, css_decl *dst, int cap)` |
| `expand_bg_size` | function | `src/css.c:1347` | `static int expand_bg_size(const char *val, css_decl *dst, int cap)` |
| `expand_box2` | function | `src/css.c:268` | `static int expand_box2(const char *val, int slot_start, int slot_end,                        int ...` |
| `expand_box4` | function | `src/css.c:263` | `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,             ...` |
| `expand_box_shadow` | function | `src/css.c:1557` | `static int expand_box_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_column_rule` | function | `src/css.c:1050` | `static int expand_column_rule(const char *val, css_decl *dst, int cap)` |
| `expand_columns` | function | `src/css.c:994` | `static int expand_columns(const char *val, css_decl *dst, int cap)` |
| `expand_content` | function | `src/css.c:1403` | `static int expand_content(const char *val, css_decl *dst, int cap,                           char...` |
| `expand_flex` | function | `src/css.c:1629` | `static int expand_flex(const char *val, css_decl *dst, int cap)` |
| `expand_flex_flow` | function | `src/css.c:1028` | `static int expand_flex_flow(const char *val, css_decl *dst, int cap)` |
| `expand_gap` | function | `src/css.c:2554` | `static int expand_gap(const char *val, css_decl *dst, int cap)` |
| `expand_grid_areas` | function | `src/css.c:1439` | `static int expand_grid_areas(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_grid_template` | function | `src/css.c:1506` | `static int expand_grid_template(const char *val, css_decl *dst, int cap,                         ...` |
| `expand_grid_template_cols` | function | `src/css.c:330` | `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `expand_outline` | function | `src/css.c:955` | `static int expand_outline(const char *val, css_decl *dst, int cap)` |
| `expand_shadow` | function | `src/css.c:349` | `static int expand_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_transform_list` | function | `src/css.c:2302` | `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);` |
| `expand_transform_origin` | function | `src/css.c:2522` | `static int expand_transform_origin(const char *val, css_decl *dst, int cap)` |
| `expand_valign` | function | `src/css.c:339` | `static int expand_valign(const char *val, css_decl *dst, int cap)` |
| `filter_paren_body` | function | `src/css.c:1091` | `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)` |
| `fold_font_relative` | function | `src/css.c:4976` | `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,                          ...` |
| `function` | function | `src/css.c:1218` | `* function (the rest of the list still applies). Emits the whole * 4-decl group in lock-step or nothing. */ const...` |
| `grammar` | function | `src/css.c:2740` | `* grammar (`justify`/`distribute`) is not `justify-content`'s. Guessing      * there would be inv...` |
| `idx` | type_alias | `src/css.c:4842` | `typedef struct css_cand { int imp, espec, ord, idx;` |
| `ignored` | function | `src/css.c:2573` | `* engine slot and is ignored (documented simplification, like list-style's  * ignored tokens). An...` |
| `interp_accent_color` | function | `src/css.c:682` | `static int interp_accent_color(const char *v)` |
| `interp_align` | function | `src/css.c:290` | `static int interp_align(const char *v)` |
| `interp_align_kw` | function | `src/css.c:1674` | `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` |
| `interp_appearance` | function | `src/css.c:554` | `static int interp_appearance(const char *v)` |
| `interp_aspect_ratio` | function | `src/css.c:345` | `static int interp_aspect_ratio(const char *v, int *num, int *den)` |
| `interp_backface_visibility` | function | `src/css.c:789` | `static int interp_backface_visibility(const char *v)` |
| `interp_bc_tok` | function | `src/css.c:890` | `static int interp_bc_tok(const char *t, int *o)` |
| `interp_bg` | function | `src/css.c:218` | `static int interp_bg(const char *v)` |
| `interp_bg_attachment` | function | `src/css.c:616` | `static int interp_bg_attachment(const char *v)` |
| `interp_bg_clip` | function | `src/css.c:601` | `static int interp_bg_clip(const char *v)` |
| `interp_bg_origin` | function | `src/css.c:609` | `static int interp_bg_origin(const char *v)` |
| `interp_bg_repeat` | function | `src/css.c:584` | `static int interp_bg_repeat(const char *v)` |
| `interp_bg_size` | function | `src/css.c:594` | `static int interp_bg_size(const char *v)` |
| `interp_border_collapse` | function | `src/css.c:462` | `static int interp_border_collapse(const char *v)` |
| `interp_border_style` | function | `src/css.c:812` | `static int interp_border_style(const char *v)` |
| `interp_box_orient` | function | `src/css.c:1705` | `static int interp_box_orient(const char *v)` |
| `interp_boxsizing` | function | `src/css.c:362` | `static int interp_boxsizing(const char *v)` |
| `interp_bs_tok` | function | `src/css.c:889` | `static int interp_bs_tok(const char *t, int *o)` |
| `interp_bw_tok` | function | `src/css.c:888` | `static int interp_bw_tok(const char *t, int *o)` |
| `interp_bwidth1` | function | `src/css.c:838` | `static int interp_bwidth1(const char *v)` |
| `interp_caption_side` | function | `src/css.c:503` | `static int interp_caption_side(const char *v)` |
| `interp_caret_color` | function | `src/css.c:542` | `static int interp_caret_color(const char *v)` |
| `interp_clear` | function | `src/css.c:375` | `static int interp_clear(const char *v)` |
| `interp_color` | function | `src/css.c:178` | `static int interp_color(const char *v)` |
| `interp_color_scheme` | function | `src/css.c:664` | `static int interp_color_scheme(const char *v)` |
| `interp_column_count` | function | `src/css.c:971` | `static int interp_column_count(const char *v)` |
| `interp_column_width` | function | `src/css.c:983` | `static int interp_column_width(const char *v)` |
| `interp_contain` | function | `src/css.c:629` | `static int interp_contain(const char *v)` |
| `interp_content_visibility` | function | `src/css.c:650` | `static int interp_content_visibility(const char *v)` |
| `interp_cursor` | function | `src/css.c:424` | `static int interp_cursor(const char *v)` |
| `interp_direction` | function | `src/css.c:346` | `static int interp_direction(const char *v)` |
| `interp_display` | function | `src/css.c:314` | `static int interp_display(const char *v)` |
| `interp_empty_cells` | function | `src/css.c:496` | `static int interp_empty_cells(const char *v)` |
| `interp_filter_deg` | function | `src/css.c:1076` | `static int interp_filter_deg(const char *s)` |
| `interp_filter_pct` | function | `src/css.c:1062` | `static int interp_filter_pct(const char *s)` |
| `interp_flex_basis` | function | `src/css.c:1595` | `static int interp_flex_basis(const char *v, int *out)` |
| `interp_flex_direction` | function | `src/css.c:1687` | `static int interp_flex_direction(const char *v)` |
| `interp_flex_factor` | function | `src/css.c:1585` | `static int interp_flex_factor(const char *v)` |
| `interp_flex_wrap` | function | `src/css.c:1711` | `static int interp_flex_wrap(const char *v)` |
| `interp_float` | function | `src/css.c:368` | `static int interp_float(const char *v)` |
| `interp_font_kerning` | function | `src/css.c:733` | `static int interp_font_kerning(const char *v)` |
| `interp_font_stretch` | function | `src/css.c:748` | `static int interp_font_stretch(const char *v)` |
| `interp_font_variant` | function | `src/css.c:517` | `static int interp_font_variant(const char *v)` |
| `interp_fontfamily` | function | `src/css.c:336` | `static int interp_fontfamily(const char *v)` |
| `interp_fontsize_ex` | function | `src/css.c:294` | `static int interp_fontsize_ex(const char *v, int *abs_out)` |
| `interp_forced_color_adjust` | function | `src/css.c:693` | `static int interp_forced_color_adjust(const char *v)` |
| `interp_gap` | function | `src/css.c:318` | `static int interp_gap(const char *v)` |
| `interp_grid_flow` | function | `src/css.c:1719` | `static int interp_grid_flow(const char *v)` |
| `interp_grid_span` | function | `src/css.c:1745` | `static int interp_grid_span(const char *v)` |
| `interp_gridcols` | function | `src/css.c:326` | `static int interp_gridcols(const char *v)` |
| `interp_hyphens` | function | `src/css.c:525` | `static int interp_hyphens(const char *v)` |
| `interp_image_rendering` | function | `src/css.c:657` | `static int interp_image_rendering(const char *v)` |
| `interp_isolation` | function | `src/css.c:623` | `static int interp_isolation(const char *v)` |
| `interp_justify` | function | `src/css.c:322` | `static int interp_justify(const char *v)` |
| `interp_len` | function | `src/css.c:273` | `static int interp_len(const char *v, int allow_auto, int *out)` |
| `interp_lineheight` | function | `src/css.c:298` | `static int interp_lineheight(const char *v)` |
| `interp_list_style_pos` | function | `src/css.c:727` | `static int interp_list_style_pos(const char *v)` |
| `interp_liststyle` | function | `src/css.c:347` | `static int interp_liststyle(const char *v)` |
| `interp_lp` | function | `src/css.c:277` | `static int interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_...` |
| `interp_mix_blend_mode` | function | `src/css.c:700` | `static int interp_mix_blend_mode(const char *v)` |
| `interp_object_fit` | function | `src/css.c:718` | `static int interp_object_fit(const char *v)` |
| `interp_opacity` | function | `src/css.c:338` | `static int interp_opacity(const char *v)` |
| `interp_overflow` | function | `src/css.c:392` | `static int interp_overflow(const char *v)` |
| `interp_overflow_wrap` | function | `src/css.c:454` | `static int interp_overflow_wrap(const char *v)` |
| `interp_overscroll_behavior` | function | `src/css.c:782` | `static int interp_overscroll_behavior(const char *v)` |
| `interp_pointer_events` | function | `src/css.c:572` | `static int interp_pointer_events(const char *v)` |
| `interp_position` | function | `src/css.c:353` | `static int interp_position(const char *v)` |
| `interp_print_color_adjust` | function | `src/css.c:687` | `static int interp_print_color_adjust(const char *v)` |
| `interp_resize` | function | `src/css.c:761` | `static int interp_resize(const char *v)` |
| `interp_scroll_behavior` | function | `src/css.c:769` | `static int interp_scroll_behavior(const char *v)` |
| `interp_style` | function | `src/css.c:306` | `static int interp_style(const char *v)` |
| `interp_table_layout` | function | `src/css.c:510` | `static int interp_table_layout(const char *v)` |
| `interp_tabsize` | function | `src/css.c:342` | `static int interp_tabsize(const char *v)` |
| `interp_text_overflow` | function | `src/css.c:440` | `static int interp_text_overflow(const char *v)` |
| `interp_text_rendering` | function | `src/css.c:740` | `static int interp_text_rendering(const char *v)` |
| `interp_textdeco` | function | `src/css.c:310` | `static int interp_textdeco(const char *v)` |
| `interp_textdeco_style` | function | `src/css.c:343` | `static int interp_textdeco_style(const char *v)` |
| `interp_textdeco_thickness` | function | `src/css.c:344` | `static int interp_textdeco_thickness(const char *v)` |
| `interp_texttransform` | function | `src/css.c:337` | `static int interp_texttransform(const char *v)` |
| `interp_time_ms` | function | `src/css.c:847` | `static int interp_time_ms(const char *v)` |
| `interp_touch_action` | function | `src/css.c:775` | `static int interp_touch_action(const char *v)` |
| `interp_transition_property` | function | `src/css.c:340` | `static int interp_transition_property(const char *v)` |
| `interp_user_select` | function | `src/css.c:533` | `static int interp_user_select(const char *v)` |
| `interp_visibility` | function | `src/css.c:385` | `static int interp_visibility(const char *v)` |
| `interp_weight` | function | `src/css.c:302` | `static int interp_weight(const char *v)` |
| `interp_whitespace` | function | `src/css.c:341` | `static int interp_whitespace(const char *v)` |
| `interp_word_break` | function | `src/css.c:446` | `static int interp_word_break(const char *v)` |
| `interpret_decls` | function | `src/css.c:3518` | `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,                ...` |
| `interpret_prop` | function | `src/css.c:3333` | `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,             ...` |
| `interpret_prop_dispatch` | function | `src/css.c:2722` | `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,    ...` |
| `layer_register` | function | `src/css.c:3786` | `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,                      ...` |
| `lp_can_be_nonneg` | function | `src/css.c:282` | `static int lp_can_be_nonneg(int px_val, int pct_pm)` |
| `matrix` | function | `src/css.c:1961` | `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands...` |
| `next_ws_token` | function | `src/css.c:286` | `static int next_ws_token(const char **p, char *tok, size_t cap)` |
| `number` | function | `src/css.c:471` | `* number (no unit) as px (common in shorthand context like "10 5"). */ static int interp_border_s...` |
| `order` | function | `src/css.c:1216` | `* Lengths in declaration order (dx, dy, optional blur >= 0);` |
| `origin_component` | function | `src/css.c:2496` | `static int origin_component(const char *tok, int axis, int *out)` |
| `page_view` | function | `src/css.c:4464` | `* the generated text reaches page_view (which materialises it as a synthetic * run);` |
| `parent` | function | `src/css.c:4496` | `* property from the parent (`inherit`), and an unset non-inherited one          * stands at its i...` |
| `parse_angle_deg` | function | `src/css.c:2299` | `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);` |
| `parse_block` | function | `src/css.c:3904` | `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,                  ...` |
| `parse_color` | function | `src/css.c:174` | `static int parse_color(const char *v)` |
| `parse_matrix6` | function | `src/css.c:1991` | `static int parse_matrix6(const char *p, size_t argn, double m6[6])` |
| `parse_num` | function | `src/css.c:163` | `static int parse_num(const char *s, double *out, const char **endp)` |
| `property` | function | `src/css.c:2608` | `* error drops the whole property (fail closed). */ static int expand_clip(const char *val, css_de...` |
| `raw_add` | function | `src/css.c:3405` | `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)` |
| `rem_emit_px` | function | `src/css.c:4174` | `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)` |
| `rem_ident_ch` | function | `src/css.c:4156` | `static int rem_ident_ch(char c)` |
| `rem_num_starts_after` | function | `src/css.c:4164` | `static int rem_num_starts_after(char prev)` |
| `rem_rebase` | function | `src/css.c:4204` | `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)` |
| `resolve_core` | function | `src/css.c:5030` | `static css_style resolve_core(const css_sheet *sheet, const css_element *el,                     ...` |
| `selector_matches_root` | function | `src/css.c:1824` | `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m)` |
| `sentinel` | function | `src/css.c:2944` | `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);` |
| `sheet_rewind` | function | `src/css.c:4271` | `static void sheet_rewind(css_sheet *sh)` |
| `sheet_root_font_px` | function | `src/css.c:4314` | `static double sheet_root_font_px(const css_sheet *sh)` |
| `shorthand` | function | `src/css.c:2651` | `* generic bucket keeps the rest of the shorthand (same net effect as the  * font-family longhand ...` |
| `skip_at_rule` | function | `src/css.c:3649` | `static size_t skip_at_rule(const char *s, size_t i, size_t n)` |
| `slots` | function | `src/css.c:2832` | `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return...` |
| `split_top_args` | function | `src/css.c:2023` | `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,                ...` |
| `strip_comments` | function | `src/css.c:4322` | `static char *strip_comments(const char *text, size_t len, size_t *outlen)` |
| `strip_important` | function | `src/css.c:1777` | `static int strip_important(char *val)` |
| `supports_matches` | function | `src/css.c:3732` | `static int supports_matches(const char *s, size_t a, size_t b)` |
| `supports_selector_ok` | function | `src/css.c:3723` | `static int supports_selector_ok(void *ctx, const char *sel)` |
| `text` | function | `src/css.c:243` | `* source text (rem_rebase, see below) rather than by threading a context here.  *  * Viewport uni...` |
| `through` | function | `src/css.c:194` | `* at the two SHARED chokepoints every property funnels through (the generic  * dispatch tail, and...` |
| `tr_decompose` | function | `src/css.c:1968` | `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,                         in...` |
| `tr_mul` | function | `src/css.c:1948` | `static void tr_mul(double out[6], const double l[6], const double r[6])` |
| `translate3d` | function | `src/css.c:2053` | `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine  * renders z as nothing,...` |
| `translate3d` | function | `src/css.c:2303` | `* translate3d()/translateZ() flatten to their 2D projection. Any other  * transform function (per...` |
| `translateX` | function | `src/css.c:2295` | `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc...` |
| `var` | function | `src/css.c:1802` | `* cvr_resolve then substitutes var() references when a declaration's value is  * interpreted (par...` |
| `var` | function | `src/css.c:4332` | `* collected and forty var() declarations -- font sizes, widths, radii, the      * whole theme -- ...` |
| `wide_claim` | function | `src/css.c:3293` | `static int wide_claim(const char *prop, css_decl *dst, int cap,                       char (*urlt...` |
| `CAR_TEXT_MAX` | macro | `src/css_atrule.c:13` | `#define CAR_TEXT_MAX` |
| `car_effective_spec` | function | `src/css_atrule.c:171` | `int car_effective_spec(int spec, int layer, int important)` |
| `car_layer_rank` | function | `src/css_atrule.c:148` | `int car_layer_rank(car_layers *L, const char *name, size_t len)` |
| `car_supports` | function | `src/css_atrule.c:141` | `int car_supports(const char *s, size_t a, size_t b, const car_ops *ops)` |
| `close_paren` | function | `src/css_atrule.c:33` | `static size_t close_paren(const char *s, size_t open, size_t b)` |
| `copy_trimmed` | function | `src/css_atrule.c:54` | `static int copy_trimmed(const char *s, size_t a, size_t b, char *dst, size_t cap, int lower)` |
| `eval_condition` | function | `src/css_atrule.c:114` | `static int eval_condition(const char *s, size_t a, size_t b, const car_ops *ops,                 ...` |
| `eval_declaration` | function | `src/css_atrule.c:68` | `static int eval_declaration(const char *s, size_t a, size_t b, const car_ops *ops, int *ok)` |
| `eval_in_parens` | function | `src/css_atrule.c:85` | `static int eval_in_parens(const char *s, size_t *i, size_t b, const car_ops *ops,                ...` |
| `keyword_at` | function | `src/css_atrule.c:23` | `static int keyword_at(const char *s, size_t i, size_t b, const char *kw)` |
| `skip_ws` | function | `src/css_atrule.c:17` | `static size_t skip_ws(const char *s, size_t i, size_t b)` |
| `AUTO_REJECT` | macro | `src/css_box.c:932` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css_box.c:934` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css_box.c:938` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css_box.c:933` | `#define AUTO_VALUE` |
| `CSS_CALC_MAX_DEPTH` | macro | `src/css_box.c:460` | `#define CSS_CALC_MAX_DEPTH` |
| `CSS_MATHFN_MAX_ARGS` | macro | `src/css_box.c:464` | `#define CSS_MATHFN_MAX_ARGS` |
| `accepts` | function | `src/css_box.c:452` | `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further...` |
| `calc_eval` | function | `src/css_box.c:711` | `static int calc_eval(const char *v, size_t vlen, double *out_px)` |
| `calc_eval_em` | function | `src/css_box.c:718` | `static int calc_eval_em(const char *v, size_t vlen, double *out_em)` |
| `calc_eval_full` | function | `src/css_box.c:695` | `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,            ...` |
| `calc_expr` | function | `src/css_box.c:676` | `static int calc_expr(calc_parser *p, calc_val *out, int depth)` |
| `calc_match_fn` | function | `src/css_box.c:489` | `static int calc_match_fn(calc_parser *p, const char *name)` |
| `calc_mathfn` | function | `src/css_box.c:531` | `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` |
| `calc_parser` | struct | `src/css_box.c:480` | `` |
| `calc_piecewise` | function | `src/css_box.c:516` | `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)` |
| `calc_skip_ws` | function | `src/css_box.c:482` | `static void calc_skip_ws(calc_parser *p)` |
| `calc_term` | function | `src/css_box.c:652` | `static int calc_term(calc_parser *p, calc_val *out, int depth)` |
| `calc_unwrap` | function | `src/css_box.c:726` | `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` |
| `calc_val` | struct | `src/css_box.c:479` | `` |
| `cb_copy_trim` | function | `src/css_box.c:25` | `static size_t cb_copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `cb_expand_box2` | function | `src/css_box.c:1106` | `int cb_expand_box2(const char *val, int slot_start, int slot_end,                        int allo...` |
| `cb_expand_grid_template_cols` | function | `src/css_box.c:430` | `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `cb_interp_align` | function | `src/css_box.c:54` | `int cb_interp_align(const char *v)` |
| `cb_interp_display` | function | `src/css_box.c:176` | `int cb_interp_display(const char *v)` |
| `cb_interp_gap` | function | `src/css_box.c:251` | `int cb_interp_gap(const char *v)` |
| `cb_interp_justify` | function | `src/css_box.c:258` | `int cb_interp_justify(const char *v)` |
| `cb_interp_len` | function | `src/css_box.c:744` | `int cb_interp_len(const char *v, int allow_auto, int *out)` |
| `cb_interp_lineheight` | function | `src/css_box.c:116` | `int cb_interp_lineheight(const char *v)` |
| `cb_interp_lp` | function | `src/css_box.c:859` | `int cb_interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_px, ...` |
| `cb_interp_style` | function | `src/css_box.c:146` | `int cb_interp_style(const char *v)` |
| `cb_interp_textdeco` | function | `src/css_box.c:156` | `int cb_interp_textdeco(const char *v)` |
| `cb_interp_weight` | function | `src/css_box.c:137` | `int cb_interp_weight(const char *v)` |
| `cb_length_px` | function | `src/css_box.c:49` | `int cb_length_px(const char *v, double *px)` |
| `cb_parse_num` | function | `src/css_box.c:13` | `static int cb_parse_num(const char *s, double *out, const char **endp)` |
| `cb_starts_with_ci` | function | `src/css_box.c:283` | `static int cb_starts_with_ci(const char *s, const char *pre)` |
| `cb_value_em_milli` | function | `src/css_box.c:839` | `int cb_value_em_milli(const char *v)` |
| `cb_wide_keyword` | function | `src/css_box.c:18` | `static int cb_wide_keyword(const char *v)` |
| `count_one_repeat` | function | `src/css_box.c:327` | `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,                       ...` |
| `count_tracks` | function | `src/css_box.c:289` | `static int count_tracks(const char *s, size_t n)` |
| `interp_len` | function | `src/css_box.c:1035` | `* this file that might hand a token to interp_len (transitively: margin/padding/  * inset, flex-b...` |
| `min` | function | `src/css_box.c:550` | `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the...` |
| `pct_slot_of` | function | `src/css_box.c:789` | `static int pct_slot_of(int slot)` |
| `px` | type_alias | `src/css_box.c:479` | `typedef struct calc_val { double px;` |
| `repeat` | function | `src/css_box.c:272` | `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill\|...) /...` |
| `term` | function | `src/css_box.c:866` | `* the same expression and failed closed on the percentage term (its property * may not accept one);` |
| `track_size_of` | function | `src/css_box.c:297` | `static int track_size_of(const char *tok)` |
| `walk_tracks` | function | `src/css_box.c:370` | `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)` |
| `CCH_ATTR_BUF` | macro | `src/css_chain.c:19` | `#define CCH_ATTR_BUF` |
| `CCH_CLASS_BUF` | macro | `src/css_chain.c:16` | `#define CCH_CLASS_BUF` |
| `CCH_ID_MAX` | macro | `src/css_chain.c:15` | `#define CCH_ID_MAX` |
| `CCH_MAX_ATTRS` | macro | `src/css_chain.c:18` | `#define CCH_MAX_ATTRS` |
| `CCH_MAX_CLASSES` | macro | `src/css_chain.c:17` | `#define CCH_MAX_CLASSES` |
| `CCH_TAG_MAX` | macro | `src/css_chain.c:14` | `#define CCH_TAG_MAX` |
| `cch_element_matches` | function | `src/css_chain.c:292` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)` |
| `cch_element_style` | function | `src/css_chain.c:288` | `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)` |
| `cch_element_style_vars` | function | `src/css_chain.c:246` | `css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,                  ...` |
| `cch_node` | struct | `src/css_chain.c:23` | `` |
| `cch_pseudo_style` | function | `src/css_chain.c:273` | `css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,             ...` |
| `count_children` | function | `src/css_chain.c:179` | `static int count_children(lxb_dom_node_t *n)` |
| `fill_css_node` | function | `src/css_chain.c:35` | `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)` |
| `inputs` | function | `src/css_chain.c:193` | `* identical inputs (single source of truth). */ static const css_element *build_chain(lxb_dom_ele...` |
| `sibling_position` | function | `src/css_chain.c:133` | `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `sibling_type_position` | function | `src/css_chain.c:151` | `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `tag` | type_alias | `src/css_chain.c:23` | `typedef struct cch_node { char tag[CCH_TAG_MAX];` |
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
| `CSS_GRAD_STOPS_MAX` | function | `src/css_gradient.c:183` | `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when  * the gradient fai...` |
| `bg_layer_tokens_ok` | function | `src/css_gradient.c:458` | `static int bg_layer_tokens_ok(const char *s)` |
| `cg_expand_background` | function | `src/css_gradient.c:498` | `int cg_expand_background(const char *val, css_decl *dst, int cap,                              ch...` |
| `cg_parse_num` | function | `src/css_gradient.c:12` | `static int cg_parse_num(const char *s, double *out, const char **endp)` |
| `cg_wide_keyword` | function | `src/css_gradient.c:17` | `static int cg_wide_keyword(const char *v)` |
| `conic_prelude` | function | `src/css_gradient.c:110` | `static int conic_prelude(const char *seg, int *angle)` |
| `declaration` | function | `src/css_gradient.c:451` | `* declaration (fail closed);` |
| `downstream` | function | `src/css_gradient.c:392` | `* happens downstream (render_doc.c), gated by caps.images like an <img>. */ int cg_expand_bg_imag...` |
| `emit_gradient` | function | `src/css_gradient.c:290` | `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,                          ...` |
| `find_gradient_call` | function | `src/css_gradient.c:76` | `static int find_gradient_call(const char *v, const char *fn, size_t *start,                      ...` |
| `find_radial_gradient` | function | `src/css_gradient.c:347` | `static int find_radial_gradient(const char *v, size_t *start, size_t *end,                       ...` |
| `grad_stop_pos` | function | `src/css_gradient.c:152` | `static int grad_stop_pos(const char *pp, int conic, const char **endp)` |
| `gradient` | function | `src/css_gradient.c:27` | `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,  * the whole decl...` |
| `pool` | function | `src/css_gradient.c:388` | `* pool (gradient explicitly reset);` |
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
| `HAS_MAX_DEPTH` | macro | `src/css_select.c:839` | `#define HAS_MAX_DEPTH` |
| `attr_matches` | function | `src/css_select.c:688` | `static int attr_matches(const css_attr_match *am, const css_element *el)` |
| `between` | function | `src/css_select.c:376` | `* between ( and ) is split on commas (not inside [] or ());` |
| `built` | function | `src/css_select.c:1014` | `* chains the caller built (an element without parent/prev links never matches  * through that com...` |
| `compound_matches` | function | `src/css_select.c:979` | `static int compound_matches(const css_compound *c, const css_element *el,                        ...` |
| `csel_decl_end` | function | `src/css_select.c:104` | `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace)` |
| `csel_emit_utf8` | function | `src/css_select.c:30` | `size_t csel_emit_utf8(unsigned int cp, char *out)` |
| `csel_escape_len` | function | `src/css_select.c:91` | `size_t csel_escape_len(const char *s, size_t i, size_t b)` |
| `csel_hex_val` | function | `src/css_select.c:23` | `int csel_hex_val(char c)` |
| `csel_ident_eq` | function | `src/css_select.c:142` | `int csel_ident_eq(const char *stored, const char *tok, size_t tlen)` |
| `csel_ident_fold` | function | `src/css_select.c:127` | `void csel_ident_fold(const char *src, size_t len, char *dst)` |
| `csel_matches` | function | `src/css_select.c:1055` | `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,               ...` |
| `csel_read_ident` | function | `src/css_select.c:150` | `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower)` |
| `csel_unescape` | function | `src/css_select.c:52` | `void csel_unescape(char *dst, size_t cap, const char *src, size_t n)` |
| `el_attr_value` | function | `src/css_select.c:655` | `static const char *el_attr_value(const css_element *el, const char *name)` |
| `ends_with` | function | `src/css_select.c:665` | `static int ends_with(const char *v, const char *suf, int ci)` |
| `has_word` | function | `src/css_select.c:673` | `static int has_word(const char *v, const char *w, int ci)` |
| `ident_hash` | function | `src/css_select.c:121` | `static unsigned long long ident_hash(const char *s, size_t n)` |
| `is_form_control` | function | `src/css_select.c:717` | `static int is_form_control(const char *tag)` |
| `nth_matches` | function | `src/css_select.c:708` | `static int nth_matches(int A, int B, int idx)` |
| `parse_attr_sel` | function | `src/css_select.c:184` | `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)` |
| `parse_compound` | function | `src/css_select.c:517` | `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,                   ...` |
| `parse_nth_arg` | function | `src/css_select.c:241` | `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)` |
| `parse_sub_compound` | function | `src/css_select.c:452` | `static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub)` |
| `pseudo_matches` | function | `src/css_select.c:726` | `static int pseudo_matches(const css_pseudo_match *pm, const css_element *el, const css_sel *sel, const char...` |
| `selector` | function | `src/css_select.c:559` | `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is  * dropped. Whitespa...` |
| `simple_pseudo_kind` | function | `src/css_select.c:431` | `static int simple_pseudo_kind(const char *nm)` |
| `sub_sel_matches` | function | `src/css_select.c:730` | `static int sub_sel_matches(const css_sub_sel *sub, const css_element *el)` |
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
| `cv_interp_bg` | function | `src/css_values.c:160` | `int cv_interp_bg(const char *v)` |
| `cv_interp_color` | function | `src/css_values.c:36` | `int cv_interp_color(const char *v)` |
| `cv_parse_color` | function | `src/css_values.c:16` | `int cv_parse_color(const char *v)` |
| `cv_parse_num` | function | `src/css_values.c:11` | `static int cv_parse_num(const char *s, double *out, const char **endp)` |
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

Next: [SYMBOLS_p6.md](SYMBOLS_p6.md)
