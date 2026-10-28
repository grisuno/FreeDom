# Symbols (page 6 of 16)
Previous: [SYMBOLS_p5.md](SYMBOLS_p5.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `CSS_INLINE_DECLS` | macro | `src/css.c:69` | `#define CSS_INLINE_DECLS` |
| `CSS_MAX_FONT_FACES` | macro | `src/css.c:164` | `#define CSS_MAX_FONT_FACES` |
| `CSS_MAX_RAW` | macro | `src/css.c:86` | `#define CSS_MAX_RAW` |
| `CSS_MEDIA_MAX_DEPTH` | macro | `src/css.c:4695` | `#define CSS_MEDIA_MAX_DEPTH` |
| `CSS_SELS_PER_GROUP` | macro | `src/css.c:68` | `#define CSS_SELS_PER_GROUP` |
| `CSS_VAR_POOL` | macro | `src/css.c:6003` | `#define CSS_VAR_POOL` |
| `CSS_WIDE_RESET` | macro | `src/css.c:221` | `#define CSS_WIDE_RESET` |
| `LIST` | function | `src/css.c:2516` | `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose...` |
| `NULL` | function | `src/css.c:6422` | `* Sheet can be NULL (inline style, no @keyframes). */ void css_resolve_anim_keyframes(css_style *...` |
| `P_META_CUSTOM` | macro | `src/css.c:82` | `#define P_META_CUSTOM` |
| `P_META_VARSRC` | macro | `src/css.c:83` | `#define P_META_VARSRC` |
| `add_rule` | function | `src/css.c:4411` | `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,                      siz...` |
| `anim_easing_iv` | function | `src/css.c:1186` | `static int anim_easing_iv(const char *tok)` |
| `apply_decl` | function | `src/css.c:5449` | `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_rule` | function | `src/css.c:6034` | `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,               ...` |
| `apply_var_source` | function | `src/css.c:6007` | `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,         ...` |
| `at_is_media` | function | `src/css.c:4562` | `static int at_is_media(const char *s, size_t i, size_t n)` |
| `at_keyword` | function | `src/css.c:4573` | `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)` |
| `axis` | function | `src/css.c:1512` | `* bare center displaces it to the free axis (`center right` = x:right, y:center).  * Any other co...` |
| `bg_alpha_of` | function | `src/css.c:235` | `static int bg_alpha_of(const char *v)` |
| `block_end` | function | `src/css.c:4540` | `static size_t block_end(const char *s, size_t open, size_t n)` |
| `blur` | function | `src/css.c:1475` | `* consumes ONLY blur(Npx);` |
| `box_shadow_layer` | function | `src/css.c:1970` | `static int box_shadow_layer(const char *val, size_t len, int out[6])` |
| `caller` | function | `src/css.c:3402` | `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached...` |
| `cand_cmp` | function | `src/css.c:5942` | `static int cand_cmp(const void *pa, const void *pb)` |
| `cap` | function | `src/css.c:1744` | `* string past the cap (emit_content): a conforming declaration must not * count as a discard just because an icon...` |
| `collect_custom_props_scoped` | function | `src/css.c:4704` | `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,                 ...` |
| `column` | function | `src/css.c:2071` | `* column (`flex: 1 1 0%`);` |
| `computed_font_size` | function | `src/css.c:5925` | `static double computed_font_size(const css_style *o, const css_element *el)` |
| `consumer` | function | `src/css.c:5360` | `* consumer (shorthands, calc(), var() values) gets it with no context          * threaded through...` |
| `content_attr_of` | function | `src/css.c:5440` | `static const char *content_attr_of(const css_element *el, const char *name)` |
| `copy_trim` | function | `src/css.c:2231` | `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `csel_substr` | function | `src/css.c:4595` | `return known && csel_substr(val, "var(", 1);` |
| `css_cand` | struct | `src/css.c:5937` | `` |
| `css_computed_font_size_for_tag` | function | `src/css.c:5917` | `double css_computed_font_size_for_tag(const css_style *o, double inherited_px, const char *tag)` |
| `css_decl` | function | `src/css.c:90` | `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);` |
| `css_font_face_at` | function | `src/css.c:6458` | `int css_font_face_at(const css_sheet *sheet, size_t i,                      char *family, size_t ...` |
| `css_font_face_count` | function | `src/css.c:6454` | `size_t css_font_face_count(const css_sheet *sheet)` |
| `css_free` | function | `src/css.c:5418` | `void css_free(css_sheet *s)` |
| `css_keyframe_stop` | struct | `src/css.c:143` | `` |
| `css_match` | struct | `src/css.c:5931` | `` |
| `css_parse` | function | `src/css.c:5312` | `css_status css_parse(const char *text, size_t len, css_sheet **out)` |
| `css_parse_inline` | function | `src/css.c:6468` | `css_style css_parse_inline(const char *style, size_t len)` |
| `css_parse_logged` | function | `src/css.c:5326` | `css_status css_parse_logged(const char *text, size_t len, const css_media *media,                ...` |
| `css_parse_media` | function | `src/css.c:5316` | `css_status css_parse_media(const char *text, size_t len, const css_media *media,                 ...` |
| `css_parse_scoped` | function | `src/css.c:5321` | `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,                ...` |
| `css_resolve` | function | `src/css.c:6398` | `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,                   ...` |
| `css_resolve_el` | function | `src/css.c:6103` | `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,                          ...` |
| `css_resolve_el_ex` | function | `src/css.c:6112` | `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,                       ...` |
| `css_resolve_pseudo` | function | `src/css.c:6128` | `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)` |
| `css_rule` | struct | `src/css.c:101` | `` |
| `css_sheet` | struct | `src/css.c:103` | `` |
| `css_ua_heading_em` | function | `src/css.c:5912` | `double css_ua_heading_em(int level)` |
| `declaration` | function | `src/css.c:2006` | `* invalid layer drops the whole declaration (fail closed). `none` is an explicit  * no-shadow. ur...` |
| `download` | function | `src/css.c:4935` | `* the download (spec/webfont.md b3b). An empty src_url                      * simply never resolv...` |
| `drop_copy_text` | function | `src/css.c:4189` | `static void drop_copy_text(char *dst, size_t cap, const char *src)` |
| `drop_record` | function | `src/css.c:4208` | `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)` |
| `emit` | function | `src/css.c:63` | `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand...` |
| `emit_content` | function | `src/css.c:1668` | `static int emit_content(css_decl *dst, int cap, const char *str,                         char (*c...` |
| `emit_radius_corner` | function | `src/css.c:923` | `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)` |
| `emit_spacing` | function | `src/css.c:365` | `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `empty` | function | `src/css.c:1778` | `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and...` |
| `expand_animation` | function | `src/css.c:1214` | `static int expand_animation(const char *val, css_decl *dst, int cap)` |
| `expand_backdrop_filter` | function | `src/css.c:1478` | `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)` |
| `expand_background` | function | `src/css.c:252` | `static int expand_background(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_bg_image` | function | `src/css.c:247` | `static int expand_bg_image(const char *val, css_decl *dst, int cap,                            ch...` |
| `expand_bg_size` | function | `src/css.c:1628` | `static int expand_bg_size(const char *val, css_decl *dst, int cap)` |
| `expand_box2` | function | `src/css.c:289` | `static int expand_box2(const char *val, int slot_start, int slot_end,                        int ...` |
| `expand_box4` | function | `src/css.c:284` | `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,             ...` |
| `expand_clip_path` | function | `src/css.c:3155` | `static int expand_clip_path(const char *val, css_decl *dst, int cap)` |
| `expand_column_rule` | function | `src/css.c:1093` | `static int expand_column_rule(const char *val, css_decl *dst, int cap)` |
| `expand_columns` | function | `src/css.c:1037` | `static int expand_columns(const char *val, css_decl *dst, int cap)` |
| `expand_content` | function | `src/css.c:1774` | `static int expand_content(const char *val, css_decl *dst, int cap,                           char...` |
| `expand_flex` | function | `src/css.c:2092` | `static int expand_flex(const char *val, css_decl *dst, int cap)` |
| `expand_flex_flow` | function | `src/css.c:1071` | `static int expand_flex_flow(const char *val, css_decl *dst, int cap)` |
| `expand_gap` | function | `src/css.c:3052` | `static int expand_gap(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area` | function | `src/css.c:1879` | `static int expand_grid_area(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area_lines` | function | `src/css.c:1845` | `static int expand_grid_area_lines(const char *val, css_decl *dst, int cap)` |
| `expand_grid_areas` | function | `src/css.c:1817` | `static int expand_grid_areas(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_grid_line` | function | `src/css.c:1870` | `static int expand_grid_line(const char *val, css_decl *dst, int cap, int p_start, int p_end)` |
| `expand_grid_template` | function | `src/css.c:1918` | `static int expand_grid_template(const char *val, css_decl *dst, int cap,                         ...` |
| `expand_grid_template_cols` | function | `src/css.c:347` | `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `expand_outline` | function | `src/css.c:998` | `static int expand_outline(const char *val, css_decl *dst, int cap)` |
| `expand_shadow` | function | `src/css.c:366` | `static int expand_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_transform_list` | function | `src/css.c:2793` | `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);` |
| `expand_transform_origin` | function | `src/css.c:3020` | `static int expand_transform_origin(const char *val, css_decl *dst, int cap)` |
| `expand_valign` | function | `src/css.c:356` | `static int expand_valign(const char *val, css_decl *dst, int cap)` |
| `filter_paren_body` | function | `src/css.c:1134` | `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)` |
| `fold_font_relative` | function | `src/css.c:6072` | `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,                          ...` |
| `font_list_alias` | function | `src/css.c:3202` | `static void font_list_alias(const css_sheet *sheet, const char *ls, char *out, size_t cap)` |
| `font_list_norm` | function | `src/css.c:3236` | `static int font_list_norm(const char *val, char *out, size_t cap)` |
| `function` | function | `src/css.c:2797` | `* transform function (perspective/rotate3d/...), or unparseable syntax,  * rejects the WHOLE decl...` |
| `here` | function | `src/css.c:3891` | `* servers have no form here (fail closed). */ int o = csel_ci_eq(val, "none") ? CSS_SVG_PAINT_NONE : interp_color(val);` |
| `idx` | type_alias | `src/css.c:5937` | `typedef struct css_cand { int imp, espec, ord, idx;` |
| `interp_accent_color` | function | `src/css.c:715` | `static int interp_accent_color(const char *v)` |
| `interp_align` | function | `src/css.c:311` | `static int interp_align(const char *v)` |
| `interp_align_kw` | function | `src/css.c:2137` | `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` |
| `interp_appearance` | function | `src/css.c:587` | `static int interp_appearance(const char *v)` |
| `interp_aspect_ratio` | function | `src/css.c:362` | `static int interp_aspect_ratio(const char *v, int *num, int *den)` |
| `interp_backface_visibility` | function | `src/css.c:832` | `static int interp_backface_visibility(const char *v)` |
| `interp_bc_tok` | function | `src/css.c:933` | `static int interp_bc_tok(const char *t, int *o)` |
| `interp_bg` | function | `src/css.c:239` | `static int interp_bg(const char *v)` |
| `interp_bg_attachment` | function | `src/css.c:649` | `static int interp_bg_attachment(const char *v)` |
| `interp_bg_clip` | function | `src/css.c:634` | `static int interp_bg_clip(const char *v)` |
| `interp_bg_origin` | function | `src/css.c:642` | `static int interp_bg_origin(const char *v)` |
| `interp_bg_repeat` | function | `src/css.c:617` | `static int interp_bg_repeat(const char *v)` |
| `interp_bg_size` | function | `src/css.c:627` | `static int interp_bg_size(const char *v)` |
| `interp_border_collapse` | function | `src/css.c:495` | `static int interp_border_collapse(const char *v)` |
| `interp_border_style` | function | `src/css.c:855` | `static int interp_border_style(const char *v)` |
| `interp_box_orient` | function | `src/css.c:2168` | `static int interp_box_orient(const char *v)` |
| `interp_boxsizing` | function | `src/css.c:379` | `static int interp_boxsizing(const char *v)` |
| `interp_bs_tok` | function | `src/css.c:932` | `static int interp_bs_tok(const char *t, int *o)` |
| `interp_bw_tok` | function | `src/css.c:931` | `static int interp_bw_tok(const char *t, int *o)` |
| `interp_bwidth1` | function | `src/css.c:881` | `static int interp_bwidth1(const char *v)` |
| `interp_caption_side` | function | `src/css.c:536` | `static int interp_caption_side(const char *v)` |
| `interp_caret_color` | function | `src/css.c:575` | `static int interp_caret_color(const char *v)` |
| `interp_clear` | function | `src/css.c:392` | `static int interp_clear(const char *v)` |
| `interp_color` | function | `src/css.c:195` | `static int interp_color(const char *v)` |
| `interp_color_scheme` | function | `src/css.c:697` | `static int interp_color_scheme(const char *v)` |
| `interp_column_count` | function | `src/css.c:1014` | `static int interp_column_count(const char *v)` |
| `interp_column_width` | function | `src/css.c:1026` | `static int interp_column_width(const char *v)` |
| `interp_contain` | function | `src/css.c:662` | `static int interp_contain(const char *v)` |
| `interp_content_visibility` | function | `src/css.c:683` | `static int interp_content_visibility(const char *v)` |
| `interp_cursor` | function | `src/css.c:441` | `static int interp_cursor(const char *v)` |
| `interp_direction` | function | `src/css.c:363` | `static int interp_direction(const char *v)` |
| `interp_display` | function | `src/css.c:335` | `static int interp_display(const char *v)` |
| `interp_empty_cells` | function | `src/css.c:529` | `static int interp_empty_cells(const char *v)` |
| `interp_filter_deg` | function | `src/css.c:1119` | `static int interp_filter_deg(const char *s)` |
| `interp_filter_pct` | function | `src/css.c:1105` | `static int interp_filter_pct(const char *s)` |
| `interp_flex_basis` | function | `src/css.c:2058` | `static int interp_flex_basis(const char *v, int *out)` |
| `interp_flex_direction` | function | `src/css.c:2150` | `static int interp_flex_direction(const char *v)` |
| `interp_flex_factor` | function | `src/css.c:2048` | `static int interp_flex_factor(const char *v)` |
| `interp_flex_line_pack` | function | `src/css.c:2195` | `static int interp_flex_line_pack(const char *v)` |
| `interp_flex_wrap` | function | `src/css.c:2205` | `static int interp_flex_wrap(const char *v)` |
| `interp_float` | function | `src/css.c:385` | `static int interp_float(const char *v)` |
| `interp_font_kerning` | function | `src/css.c:767` | `static int interp_font_kerning(const char *v)` |
| `interp_font_stretch` | function | `src/css.c:782` | `static int interp_font_stretch(const char *v)` |
| `interp_font_variant` | function | `src/css.c:550` | `static int interp_font_variant(const char *v)` |
| `interp_fontfamily` | function | `src/css.c:353` | `static int interp_fontfamily(const char *v)` |
| `interp_fontsize_ex` | function | `src/css.c:315` | `static int interp_fontsize_ex(const char *v, int *abs_out)` |
| `interp_forced_color_adjust` | function | `src/css.c:726` | `static int interp_forced_color_adjust(const char *v)` |
| `interp_gap` | function | `src/css.c:339` | `static int interp_gap(const char *v)` |
| `interp_grid_flow` | function | `src/css.c:2213` | `static int interp_grid_flow(const char *v)` |
| `interp_hyphens` | function | `src/css.c:558` | `static int interp_hyphens(const char *v)` |
| `interp_image_rendering` | function | `src/css.c:690` | `static int interp_image_rendering(const char *v)` |
| `interp_isolation` | function | `src/css.c:656` | `static int interp_isolation(const char *v)` |
| `interp_justify` | function | `src/css.c:343` | `static int interp_justify(const char *v)` |
| `interp_len` | function | `src/css.c:294` | `static int interp_len(const char *v, int allow_auto, int *out)` |
| `interp_lineheight` | function | `src/css.c:319` | `static int interp_lineheight(const char *v)` |
| `interp_list_style_pos` | function | `src/css.c:761` | `static int interp_list_style_pos(const char *v)` |
| `interp_liststyle` | function | `src/css.c:364` | `static int interp_liststyle(const char *v)` |
| `interp_lp` | function | `src/css.c:298` | `static int interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_...` |
| `interp_mix_blend_mode` | function | `src/css.c:733` | `static int interp_mix_blend_mode(const char *v)` |
| `interp_object_fit` | function | `src/css.c:752` | `static int interp_object_fit(const char *v)` |
| `interp_opacity` | function | `src/css.c:355` | `static int interp_opacity(const char *v)` |
| `interp_overflow` | function | `src/css.c:409` | `static int interp_overflow(const char *v)` |
| `interp_overflow_wrap` | function | `src/css.c:487` | `static int interp_overflow_wrap(const char *v)` |
| `interp_overscroll_behavior` | function | `src/css.c:825` | `static int interp_overscroll_behavior(const char *v)` |
| `interp_pointer_events` | function | `src/css.c:605` | `static int interp_pointer_events(const char *v)` |
| `interp_position` | function | `src/css.c:370` | `static int interp_position(const char *v)` |
| `interp_print_color_adjust` | function | `src/css.c:720` | `static int interp_print_color_adjust(const char *v)` |
| `interp_resize` | function | `src/css.c:795` | `static int interp_resize(const char *v)` |
| `interp_scroll_behavior` | function | `src/css.c:803` | `static int interp_scroll_behavior(const char *v)` |
| `interp_style` | function | `src/css.c:327` | `static int interp_style(const char *v)` |
| `interp_table_layout` | function | `src/css.c:543` | `static int interp_table_layout(const char *v)` |
| `interp_tabsize` | function | `src/css.c:359` | `static int interp_tabsize(const char *v)` |
| `interp_text_overflow` | function | `src/css.c:473` | `static int interp_text_overflow(const char *v)` |
| `interp_text_rendering` | function | `src/css.c:774` | `static int interp_text_rendering(const char *v)` |
| `interp_textdeco` | function | `src/css.c:331` | `static int interp_textdeco(const char *v)` |
| `interp_textdeco_style` | function | `src/css.c:360` | `static int interp_textdeco_style(const char *v)` |
| `interp_textdeco_thickness` | function | `src/css.c:361` | `static int interp_textdeco_thickness(const char *v)` |
| `interp_texttransform` | function | `src/css.c:354` | `static int interp_texttransform(const char *v)` |
| `interp_time_ms` | function | `src/css.c:890` | `static int interp_time_ms(const char *v)` |
| `interp_transition_property` | function | `src/css.c:357` | `static int interp_transition_property(const char *v)` |
| `interp_user_select` | function | `src/css.c:566` | `static int interp_user_select(const char *v)` |
| `interp_visibility` | function | `src/css.c:402` | `static int interp_visibility(const char *v)` |
| `interp_weight` | function | `src/css.c:323` | `static int interp_weight(const char *v)` |
| `interp_whitespace` | function | `src/css.c:358` | `static int interp_whitespace(const char *v)` |
| `interp_word_break` | function | `src/css.c:479` | `static int interp_word_break(const char *v)` |
| `interpret_decls` | function | `src/css.c:4347` | `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,                ...` |
| `interpret_prop` | function | `src/css.c:4162` | `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,             ...` |
| `interpret_prop_dispatch` | function | `src/css.c:3414` | `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,    ...` |
| `is_anim_ident` | function | `src/css.c:1198` | `static int is_anim_ident(const char *tok)` |
| `item` | function | `src/css.c:1147` | `* timing list takes its first item (CSS Animations/Transitions 1: with one  * transition/animatio...` |
| `layer_register` | function | `src/css.c:4661` | `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,                      ...` |
| `len_rebase` | function | `src/css.c:5145` | `static char *len_rebase(const char *s, size_t n, const len_rebase_ctx *c, size_t *outlen)` |
| `len_rebase_ctx` | struct | `src/css.c:5103` | `` |
| `len_unit_px` | function | `src/css.c:5115` | `static double len_unit_px(const char *u, size_t len, const len_rebase_ctx *c)` |
| `lp_can_be_nonneg` | function | `src/css.c:303` | `static int lp_can_be_nonneg(int px_val, int pct_pm)` |
| `matrix` | function | `src/css.c:2431` | `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands...` |
| `next_ws_token` | function | `src/css.c:307` | `static int next_ws_token(const char **p, char *tok, size_t cap)` |
| `number` | function | `src/css.c:504` | `* number (no unit) as px (common in shorthand context like "10 5"). */ static int interp_border_s...` |
| `order` | function | `src/css.c:1440` | `* declaration order (dx, dy, optional blur >= 0);` |
| `origin_component` | function | `src/css.c:2994` | `static int origin_component(const char *tok, int axis, int *out)` |
| `page_view` | function | `src/css.c:5456` | `* the generated text reaches page_view (which materialises it as a synthetic * run);` |
| `parent` | function | `src/css.c:5489` | `* property from the parent (`inherit`), and an unset non-inherited one          * stands at its i...` |
| `parse_angle_deg` | function | `src/css.c:2790` | `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);` |
| `parse_block` | function | `src/css.c:4779` | `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,                  ...` |
| `parse_color` | function | `src/css.c:191` | `static int parse_color(const char *v)` |
| `parse_matrix6` | function | `src/css.c:2461` | `static int parse_matrix6(const char *p, size_t argn, double m6[6])` |
| `parse_num` | function | `src/css.c:180` | `static int parse_num(const char *s, double *out, const char **endp)` |
| `property` | function | `src/css.c:3111` | `* error drops the whole property (fail closed). */ static int expand_clip(const char *val, css_de...` |
| `pseudo_of` | function | `src/css.c:6119` | `static int pseudo_of(int which)` |
| `raw_add` | function | `src/css.c:4234` | `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)` |
| `rem_emit_px` | function | `src/css.c:5085` | `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)` |
| `rem_ident_ch` | function | `src/css.c:5067` | `static int rem_ident_ch(char c)` |
| `rem_num_starts_after` | function | `src/css.c:5075` | `static int rem_num_starts_after(char prev)` |
| `rem_px` | type_alias | `src/css.c:5103` | `typedef struct len_rebase_ctx { double rem_px;` |
| `rem_rebase` | function | `src/css.c:5211` | `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)` |
| `resolve_core` | function | `src/css.c:6139` | `static css_style resolve_core(const css_sheet *sheet, const css_element *el,                     ...` |
| `sel_list_comma` | function | `src/css.c:1963` | `static size_t sel_list_comma(const char *s, size_t i, size_t end);` |
| `selector_matches_root` | function | `src/css.c:2291` | `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m)` |
| `sentinel` | function | `src/css.c:3688` | `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);` |
| `sheet_index` | function | `src/css.c:5219` | `static void sheet_index(css_sheet *sh)` |
| `sheet_pools_reserve` | function | `src/css.c:4405` | `static void sheet_pools_reserve(css_sheet *sh)` |
| `sheet_rewind` | function | `src/css.c:5224` | `static void sheet_rewind(css_sheet *sh)` |
| `sheet_root_font_px` | function | `src/css.c:5269` | `static double sheet_root_font_px(const css_sheet *sh)` |
| `shorthand` | function | `src/css.c:3076` | `* An uninterpretable token drops the whole shorthand (fail closed). */ static int expand_place(co...` |
| `shorthand` | function | `src/css.c:3322` | `* generic bucket keeps the rest of the shorthand (same net effect as the  * font-family longhand ...` |
| `skip_at_rule` | function | `src/css.c:4524` | `static size_t skip_at_rule(const char *s, size_t i, size_t n)` |
| `slots` | function | `src/css.c:3573` | `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return...` |
| `split_top_args` | function | `src/css.c:2493` | `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,                ...` |
| `strip_comments` | function | `src/css.c:5277` | `static char *strip_comments(const char *text, size_t len, size_t *outlen)` |
| `strip_important` | function | `src/css.c:2244` | `static int strip_important(char *val)` |
| `supports_matches` | function | `src/css.c:4607` | `static int supports_matches(const char *s, size_t a, size_t b)` |
| `supports_selector_ok` | function | `src/css.c:4598` | `static int supports_selector_ok(void *ctx, const char *sel)` |
| `text` | function | `src/css.c:264` | `* source text (rem_rebase, see below) rather than by threading a context here.  *  * Viewport uni...` |
| `through` | function | `src/css.c:211` | `* at the two SHARED chokepoints every property funnels through (the generic  * dispatch tail, and...` |
| `tr_decompose` | function | `src/css.c:2438` | `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,                         in...` |
| `tr_mul` | function | `src/css.c:2418` | `static void tr_mul(double out[6], const double l[6], const double r[6])` |
| `translate3d` | function | `src/css.c:2523` | `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine  * renders z as nothing,...` |
| `translateX` | function | `src/css.c:2786` | `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc...` |
| `translateZ` | function | `src/css.c:2795` | `* translateZ(), rotateX(0) and rotateY(0) emit the identity (with the stacking * context Firefox builds);` |
| `var` | function | `src/css.c:2269` | `* cvr_resolve then substitutes var() references when a declaration's value is  * interpreted (par...` |
| `var` | function | `src/css.c:5287` | `* collected and forty var() declarations -- font sizes, widths, radii, the      * whole theme -- ...` |
| `wide_claim` | function | `src/css.c:4122` | `static int wide_claim(const char *prop, css_decl *dst, int cap,                       char (*urlt...` |
| `writing` | function | `src/css.c:3280` | `* Wide keywords claim BOTH slots without writing (inheritance then flows, as  * the tail does for...` |
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
| `AUTO_REJECT` | macro | `src/css_box.c:1196` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css_box.c:1198` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css_box.c:1202` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css_box.c:1197` | `#define AUTO_VALUE` |
| `CSS_CALC_MAX_DEPTH` | macro | `src/css_box.c:682` | `#define CSS_CALC_MAX_DEPTH` |
| `CSS_MATHFN_MAX_ARGS` | macro | `src/css_box.c:686` | `#define CSS_MATHFN_MAX_ARGS` |
| `RELATIVE` | function | `src/css_box.c:63` | `* or RELATIVE (of the inherited size). Absolute: px/pt/rem/viewport units and the * absolute keywords. Relative: em...` |
| `accepts` | function | `src/css_box.c:674` | `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further...` |
| `calc_eval_em` | function | `src/css_box.c:931` | `static int calc_eval_em(const char *v, size_t vlen, double *out_em)` |
| `calc_eval_full` | function | `src/css_box.c:917` | `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,            ...` |
| `calc_expr` | function | `src/css_box.c:898` | `static int calc_expr(calc_parser *p, calc_val *out, int depth)` |
| `calc_match_fn` | function | `src/css_box.c:711` | `static int calc_match_fn(calc_parser *p, const char *name)` |
| `calc_mathfn` | function | `src/css_box.c:753` | `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` |
| `calc_parser` | struct | `src/css_box.c:702` | `` |
| `calc_piecewise` | function | `src/css_box.c:738` | `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)` |
| `calc_skip_ws` | function | `src/css_box.c:704` | `static void calc_skip_ws(calc_parser *p)` |
| `calc_term` | function | `src/css_box.c:874` | `static int calc_term(calc_parser *p, calc_val *out, int depth)` |
| `calc_unwrap` | function | `src/css_box.c:939` | `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` |
| `calc_val` | struct | `src/css_box.c:701` | `` |
| `cb_clip_inset` | function | `src/css_box.c:1089` | `int cb_clip_inset(const char *val, int px[4], int pm[4])` |
| `cb_copy_trim` | function | `src/css_box.c:25` | `static size_t cb_copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `cb_expand_box2` | function | `src/css_box.c:1370` | `int cb_expand_box2(const char *val, int slot_start, int slot_end,                        int allo...` |
| `cb_expand_grid_template_cols` | function | `src/css_box.c:591` | `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `cb_expand_grid_template_rows` | function | `src/css_box.c:614` | `int cb_expand_grid_template_rows(const char *val, css_decl *dst, int cap)` |
| `cb_interp_align` | function | `src/css_box.c:54` | `int cb_interp_align(const char *v)` |
| `cb_interp_display` | function | `src/css_box.c:213` | `int cb_interp_display(const char *v)` |
| `cb_interp_fontsize_ex` | function | `src/css_box.c:72` | `int cb_interp_fontsize_ex(const char *v, int *abs_out)` |
| `cb_interp_gap` | function | `src/css_box.c:288` | `int cb_interp_gap(const char *v)` |
| `cb_interp_justify` | function | `src/css_box.c:295` | `int cb_interp_justify(const char *v)` |
| `cb_interp_len` | function | `src/css_box.c:990` | `int cb_interp_len(const char *v, int allow_auto, int *out)` |
| `cb_interp_lineheight` | function | `src/css_box.c:145` | `int cb_interp_lineheight(const char *v)` |
| `cb_interp_lp` | function | `src/css_box.c:1123` | `int cb_interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_px, ...` |
| `cb_interp_style` | function | `src/css_box.c:183` | `int cb_interp_style(const char *v)` |
| `cb_interp_textdeco` | function | `src/css_box.c:193` | `int cb_interp_textdeco(const char *v)` |
| `cb_interp_weight` | function | `src/css_box.c:174` | `int cb_interp_weight(const char *v)` |
| `cb_length_px` | function | `src/css_box.c:49` | `int cb_length_px(const char *v, double *px)` |
| `cb_parse_num` | function | `src/css_box.c:13` | `static int cb_parse_num(const char *s, double *out, const char **endp)` |
| `cb_starts_with_ci` | function | `src/css_box.c:320` | `static int cb_starts_with_ci(const char *s, const char *pre)` |
| `cb_value_em_milli` | function | `src/css_box.c:1069` | `int cb_value_em_milli(const char *v)` |
| `cb_wide_keyword` | function | `src/css_box.c:18` | `static int cb_wide_keyword(const char *v)` |
| `count_one_repeat` | function | `src/css_box.c:364` | `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,                       ...` |
| `count_tracks` | function | `src/css_box.c:326` | `static int count_tracks(const char *s, size_t n)` |
| `expand_auto_fill` | function | `src/css_box.c:513` | `static int expand_auto_fill(const char *val, css_decl *dst, int cap)` |
| `interp_len` | function | `src/css_box.c:1299` | `* this file that might hand a token to interp_len (transitively: margin/padding/  * inset, flex-b...` |
| `min` | function | `src/css_box.c:772` | `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the...` |
| `pct_slot_of` | function | `src/css_box.c:1019` | `static int pct_slot_of(int slot)` |
| `px` | type_alias | `src/css_box.c:701` | `typedef struct calc_val { double px;` |
| `repeat` | function | `src/css_box.c:309` | `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill\|...) /...` |
| `term` | function | `src/css_box.c:1130` | `* the same expression and failed closed on the percentage term (its property * may not accept one);` |
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
| `cch_element_matches` | function | `src/css_chain.c:364` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)` |
| `cch_element_matches_any` | function | `src/css_chain.c:378` | `int cch_element_matches_any(lxb_dom_element_t *el, const css_sel *sels, size_t n)` |
| `cch_element_style` | function | `src/css_chain.c:360` | `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)` |
| `cch_element_style_vars` | function | `src/css_chain.c:310` | `css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,                  ...` |
| `cch_node` | struct | `src/css_chain.c:27` | `` |
| `cch_pseudo_style` | function | `src/css_chain.c:341` | `css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,             ...` |
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
| `CCM_NPROPS` | macro | `src/css_computed.c:308` | `#define CCM_NPROPS` |
| `LEN_FIELD` | macro | `src/css_computed.c:223` | `#define LEN_FIELD(NAME, FIELD, UNSET)` |
| `NAME` | function | `src/css_computed.c:224` | `static size_t NAME(const ccm_input *in, char *out, size_t cap)` |
| `ccm_get` | function | `src/css_computed.c:310` | `size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap)` |
| `ccm_prop` | struct | `src/css_computed.c:276` | `` |
| `ccm_property_count` | function | `src/css_computed.c:323` | `size_t ccm_property_count(void)` |
| `ccm_property_name` | function | `src/css_computed.c:325` | `const char *ccm_property_name(size_t i)` |
| `f_align_items` | function | `src/css_computed.c:151` | `static size_t f_align_items(const ccm_input *in, char *out, size_t cap)` |
| `f_background_color` | function | `src/css_computed.c:198` | `static size_t f_background_color(const ccm_input *in, char *out, size_t cap)` |
| `f_border_bottom_style` | function | `src/css_computed.c:262` | `static size_t f_border_bottom_style(const ccm_input *in, char *out, size_t cap)` |
| `f_border_left_style` | function | `src/css_computed.c:265` | `static size_t f_border_left_style(const ccm_input *in, char *out, size_t cap)` |
| `f_border_right_style` | function | `src/css_computed.c:259` | `static size_t f_border_right_style(const ccm_input *in, char *out, size_t cap)` |
| `f_border_style` | function | `src/css_computed.c:217` | `static size_t f_border_style(int v, char *out, size_t cap)` |
| `f_border_top_style` | function | `src/css_computed.c:256` | `static size_t f_border_top_style(const ccm_input *in, char *out, size_t cap)` |
| `f_box_sizing` | function | `src/css_computed.c:130` | `static size_t f_box_sizing(const ccm_input *in, char *out, size_t cap)` |
| `f_clear` | function | `src/css_computed.c:110` | `static size_t f_clear(const ccm_input *in, char *out, size_t cap)` |
| `f_color` | function | `src/css_computed.c:193` | `static size_t f_color(const ccm_input *in, char *out, size_t cap)` |
| `f_cursor` | function | `src/css_computed.c:157` | `static size_t f_cursor(const ccm_input *in, char *out, size_t cap)` |
| `f_display` | function | `src/css_computed.c:77` | `static size_t f_display(const ccm_input *in, char *out, size_t cap)` |
| `f_flex_direction` | function | `src/css_computed.c:135` | `static size_t f_flex_direction(const ccm_input *in, char *out, size_t cap)` |
| `f_flex_grow` | function | `src/css_computed.c:269` | `static size_t f_flex_grow(const ccm_input *in, char *out, size_t cap)` |
| `f_flex_shrink` | function | `src/css_computed.c:272` | `static size_t f_flex_shrink(const ccm_input *in, char *out, size_t cap)` |
| `f_flex_wrap` | function | `src/css_computed.c:140` | `static size_t f_flex_wrap(const ccm_input *in, char *out, size_t cap)` |
| `f_float` | function | `src/css_computed.c:105` | `static size_t f_float(const ccm_input *in, char *out, size_t cap)` |
| `f_font_size` | function | `src/css_computed.c:181` | `static size_t f_font_size(const ccm_input *in, char *out, size_t cap)` |
| `f_font_style` | function | `src/css_computed.c:173` | `static size_t f_font_style(const ccm_input *in, char *out, size_t cap)` |
| `f_font_weight` | function | `src/css_computed.c:177` | `static size_t f_font_weight(const ccm_input *in, char *out, size_t cap)` |
| `f_gap` | function | `src/css_computed.c:244` | `static size_t f_gap(const ccm_input *in, char *out, size_t cap)` |
| `f_justify` | function | `src/css_computed.c:145` | `static size_t f_justify(const ccm_input *in, char *out, size_t cap)` |
| `f_line_height` | function | `src/css_computed.c:187` | `static size_t f_line_height(const ccm_input *in, char *out, size_t cap)` |
| `f_opacity` | function | `src/css_computed.c:204` | `static size_t f_opacity(const ccm_input *in, char *out, size_t cap)` |
| `f_overflow_x` | function | `src/css_computed.c:115` | `static size_t f_overflow_x(const ccm_input *in, char *out, size_t cap)` |
| `f_overflow_y` | function | `src/css_computed.c:120` | `static size_t f_overflow_y(const ccm_input *in, char *out, size_t cap)` |
| `f_position` | function | `src/css_computed.c:95` | `static size_t f_position(const ccm_input *in, char *out, size_t cap)` |
| `f_text_align` | function | `src/css_computed.c:125` | `static size_t f_text_align(const ccm_input *in, char *out, size_t cap)` |
| `f_text_transform` | function | `src/css_computed.c:168` | `static size_t f_text_transform(const ccm_input *in, char *out, size_t cap)` |
| `f_visibility` | function | `src/css_computed.c:100` | `static size_t f_visibility(const ccm_input *in, char *out, size_t cap)` |
| `f_white_space` | function | `src/css_computed.c:163` | `static size_t f_white_space(const ccm_input *in, char *out, size_t cap)` |
| `f_z_index` | function | `src/css_computed.c:212` | `static size_t f_z_index(const ccm_input *in, char *out, size_t cap)` |
| `put` | function | `src/css_computed.c:9` | `static size_t put(char *out, size_t cap, const char *s)` |
| `put_enum` | function | `src/css_computed.c:42` | `static size_t put_enum(char *out, size_t cap, int v, const char *const *names, size_t n,         ...` |
| `put_len` | function | `src/css_computed.c:37` | `static size_t put_len(char *out, size_t cap, int v, const char *unset_text)` |
| `put_rgb` | function | `src/css_computed.c:26` | `static size_t put_rgb(char *out, size_t cap, int rgb, int alpha_pct)` |
| `putf` | function | `src/css_computed.c:17` | `static size_t putf(char *out, size_t cap, const char *fmt, ...)` |
| `ua_display` | function | `src/css_computed.c:49` | `static const char *ua_display(const char *tag)` |
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
| `cm_expand` | function | `src/css_mask.c:197` | `int cm_expand(const char *prop, const char *val, css_decl *dst, int cap, int webkit_vocab)` |
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

Next: [SYMBOLS_p7.md](SYMBOLS_p7.md)
