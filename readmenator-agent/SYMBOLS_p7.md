# Symbols (page 7 of 18)
Previous: [SYMBOLS_p6.md](SYMBOLS_p6.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `block_end` | function | `src/css.c:5190` | `static size_t block_end(const char *s, size_t open, size_t n)` |
| `blur` | function | `src/css.c:1787` | `* consumes ONLY blur(Npx);` |
| `box_shadow_layer` | function | `src/css.c:2309` | `static int box_shadow_layer(const char *val, size_t len, int out[6])` |
| `caller` | function | `src/css.c:3867` | `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached...` |
| `cand_cmp` | function | `src/css.c:6697` | `static int cand_cmp(const void *pa, const void *pb)` |
| `cap` | function | `src/css.c:2056` | `* string past the cap (emit_content): a conforming declaration must not * count as a discard just because an icon...` |
| `collect_custom_props_scoped` | function | `src/css.c:5394` | `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,                 ...` |
| `column` | function | `src/css.c:2410` | `* column (`flex: 1 1 0%`);` |
| `computed_font_size` | function | `src/css.c:6680` | `static double computed_font_size(const css_style *o, const css_element *el)` |
| `consumer` | function | `src/css.c:6080` | `* consumer (shorthands, calc(), var() values) gets it with no context          * threaded through...` |
| `content_attr_of` | function | `src/css.c:6163` | `static const char *content_attr_of(const css_element *el, const char *name)` |
| `copy_trim` | function | `src/css.c:2581` | `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `cq_holds` | function | `src/css.c:5337` | `static int cq_holds(const css_sheet *sheet, int id, const cmq_container *scope)` |
| `cq_register` | function | `src/css.c:5315` | `static int cq_register(css_sheet *sh, const char *text, size_t len, int max_w)` |
| `csel_substr` | function | `src/css.c:5245` | `return known && csel_substr(val, "var(", 1);` |
| `css_cand` | struct | `src/css.c:6692` | `` |
| `css_computed_font_size_for_tag` | function | `src/css.c:6672` | `double css_computed_font_size_for_tag(const css_style *o, double inherited_px, const char *tag)` |
| `css_cq` | struct | `src/css.c:141` | `` |
| `css_decl` | function | `src/css.c:91` | `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);` |
| `css_font_face_at` | function | `src/css.c:7216` | `int css_font_face_at(const css_sheet *sheet, size_t i,                      char *family, size_t ...` |
| `css_font_face_count` | function | `src/css.c:7212` | `size_t css_font_face_count(const css_sheet *sheet)` |
| `css_free` | function | `src/css.c:6138` | `void css_free(css_sheet *s)` |
| `css_keyframe_stop` | struct | `src/css.c:151` | `` |
| `css_match` | struct | `src/css.c:6686` | `` |
| `css_parse` | function | `src/css.c:6032` | `css_status css_parse(const char *text, size_t len, css_sheet **out)` |
| `css_parse_inline` | function | `src/css.c:7226` | `css_style css_parse_inline(const char *style, size_t len)` |
| `css_parse_logged` | function | `src/css.c:6046` | `css_status css_parse_logged(const char *text, size_t len, const css_media *media,                ...` |
| `css_parse_media` | function | `src/css.c:6036` | `css_status css_parse_media(const char *text, size_t len, const css_media *media,                 ...` |
| `css_parse_scoped` | function | `src/css.c:6041` | `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,                ...` |
| `css_resolve` | function | `src/css.c:7156` | `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,                   ...` |
| `css_resolve_el` | function | `src/css.c:6858` | `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,                          ...` |
| `css_resolve_el_ex` | function | `src/css.c:6867` | `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,                       ...` |
| `css_resolve_pseudo` | function | `src/css.c:6883` | `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)` |
| `css_rule` | struct | `src/css.c:102` | `` |
| `css_sheet` | struct | `src/css.c:104` | `` |
| `css_sheet_uses_containers` | function | `src/css.c:7230` | `int css_sheet_uses_containers(const css_sheet *sheet)` |
| `css_sheet_uses_counters` | function | `src/css.c:7234` | `int css_sheet_uses_counters(const css_sheet *sheet)` |
| `css_ua_heading_em` | function | `src/css.c:6667` | `double css_ua_heading_em(int level)` |
| `declaration` | function | `src/css.c:2345` | `* invalid layer drops the whole declaration (fail closed). `none` is an explicit  * no-shadow. ur...` |
| `download` | function | `src/css.c:5653` | `* the download (spec/webfont.md b3b). An empty src_url                      * simply never resolv...` |
| `drop_copy_text` | function | `src/css.c:4832` | `static void drop_copy_text(char *dst, size_t cap, const char *src)` |
| `drop_record` | function | `src/css.c:4851` | `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)` |
| `easing_steps` | function | `src/css.c:1471` | `static int easing_steps(const char *tok)` |
| `emit` | function | `src/css.c:64` | `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand...` |
| `emit_content` | function | `src/css.c:1980` | `static int emit_content(css_decl *dst, int cap, const char *str,                         char (*c...` |
| `emit_mask_image` | function | `src/css.c:797` | `static int emit_mask_image(const char *prop, const char *val, css_decl *dst, int cap,            ...` |
| `emit_radius_corner` | function | `src/css.c:1158` | `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)` |
| `emit_spacing` | function | `src/css.c:386` | `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `empty` | function | `src/css.c:2109` | `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and...` |
| `expand_animation` | function | `src/css.c:1526` | `static int expand_animation(const char *val, css_decl *dst, int cap)` |
| `expand_backdrop_filter` | function | `src/css.c:1790` | `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)` |
| `expand_background` | function | `src/css.c:263` | `static int expand_background(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_background_layer` | function | `src/css.c:679` | `static int expand_background_layer(const char *val, css_decl *dst, int cap)` |
| `expand_bg_image` | function | `src/css.c:255` | `static int expand_bg_image(const char *val, css_decl *dst, int cap,                            ch...` |
| `expand_bg_position` | function | `src/css.c:260` | `static int expand_bg_position(const char *val, css_decl *dst, int cap);` |
| `expand_bg_size` | function | `src/css.c:1940` | `static int expand_bg_size(const char *val, css_decl *dst, int cap)` |
| `expand_box2` | function | `src/css.c:300` | `static int expand_box2(const char *val, int slot_start, int slot_end,                        int ...` |
| `expand_box4` | function | `src/css.c:295` | `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,             ...` |
| `expand_clip_path` | function | `src/css.c:3620` | `static int expand_clip_path(const char *val, css_decl *dst, int cap)` |
| `expand_column_rule` | function | `src/css.c:1346` | `static int expand_column_rule(const char *val, css_decl *dst, int cap)` |
| `expand_columns` | function | `src/css.c:1290` | `static int expand_columns(const char *val, css_decl *dst, int cap)` |
| `expand_content` | function | `src/css.c:2105` | `static int expand_content(const char *val, css_decl *dst, int cap,                           char...` |
| `expand_counter_decls` | function | `src/css.c:2087` | `static int expand_counter_decls(const char *prop, const char *val, css_decl *dst, int cap,       ...` |
| `expand_flex` | function | `src/css.c:2431` | `static int expand_flex(const char *val, css_decl *dst, int cap)` |
| `expand_flex_flow` | function | `src/css.c:1324` | `static int expand_flex_flow(const char *val, css_decl *dst, int cap)` |
| `expand_gap` | function | `src/css.c:3517` | `static int expand_gap(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area` | function | `src/css.c:2218` | `static int expand_grid_area(const char *val, css_decl *dst, int cap)` |
| `expand_grid_area_lines` | function | `src/css.c:2184` | `static int expand_grid_area_lines(const char *val, css_decl *dst, int cap)` |
| `expand_grid_areas` | function | `src/css.c:2156` | `static int expand_grid_areas(const char *val, css_decl *dst, int cap,                            ...` |
| `expand_grid_line` | function | `src/css.c:2209` | `static int expand_grid_line(const char *val, css_decl *dst, int cap, int p_start, int p_end)` |
| `expand_grid_template` | function | `src/css.c:2257` | `static int expand_grid_template(const char *val, css_decl *dst, int cap,                         ...` |
| `expand_grid_template_cols` | function | `src/css.c:368` | `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)` |
| `expand_mask_geometry` | function | `src/css.c:778` | `static int expand_mask_geometry(const char *prop, const char *val, css_decl *dst, int cap)` |
| `expand_outline` | function | `src/css.c:1241` | `static int expand_outline(const char *val, css_decl *dst, int cap)` |
| `expand_shadow` | function | `src/css.c:387` | `static int expand_shadow(const char *val, css_decl *dst, int cap)` |
| `expand_transform_list` | function | `src/css.c:3254` | `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);` |
| `expand_transform_origin` | function | `src/css.c:3485` | `static int expand_transform_origin(const char *val, css_decl *dst, int cap)` |
| `expand_valign` | function | `src/css.c:377` | `static int expand_valign(const char *val, css_decl *dst, int cap)` |
| `filter_paren_body` | function | `src/css.c:1387` | `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)` |
| `first_comma_item` | function | `src/css.c:753` | `static void first_comma_item(const char *val, char *buf, size_t cap);` |
| `fold_font_relative` | function | `src/css.c:6827` | `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,                          ...` |
| `font_list_alias` | function | `src/css.c:3667` | `static void font_list_alias(const css_sheet *sheet, const char *ls, char *out, size_t cap)` |
| `font_list_norm` | function | `src/css.c:3701` | `static int font_list_norm(const char *val, char *out, size_t cap)` |
| `function` | function | `src/css.c:3258` | `* transform function (perspective/rotate3d/...), or unparseable syntax,  * rejects the WHOLE decl...` |
| `has_double_dash` | function | `src/css.c:2641` | `static int has_double_dash(const char *p, size_t n)` |
| `here` | function | `src/css.c:4503` | `* servers have no form here (fail closed). */ int o = csel_ci_eq(val, "none") ? CSS_SVG_PAINT_NONE : interp_color(val);` |
| `idx` | type_alias | `src/css.c:6692` | `typedef struct css_cand { int imp, espec, ord, idx;` |
| `interp_accent_color` | function | `src/css.c:904` | `static int interp_accent_color(const char *v)` |
| `interp_align` | function | `src/css.c:322` | `static int interp_align(const char *v)` |
| `interp_align_kw` | function | `src/css.c:2476` | `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` |
| `interp_appearance` | function | `src/css.c:608` | `static int interp_appearance(const char *v)` |
| `interp_aspect_ratio` | function | `src/css.c:383` | `static int interp_aspect_ratio(const char *v, int *num, int *den)` |
| `interp_backface_visibility` | function | `src/css.c:1067` | `static int interp_backface_visibility(const char *v)` |
| `interp_bc_tok` | function | `src/css.c:1168` | `static int interp_bc_tok(const char *t, int *o)` |
| `interp_bg` | function | `src/css.c:247` | `static int interp_bg(const char *v)` |
| `interp_bg_attachment` | function | `src/css.c:838` | `static int interp_bg_attachment(const char *v)` |
| `interp_bg_clip` | function | `src/css.c:823` | `static int interp_bg_clip(const char *v)` |
| `interp_bg_origin` | function | `src/css.c:831` | `static int interp_bg_origin(const char *v)` |
| `interp_bg_repeat` | function | `src/css.c:638` | `static int interp_bg_repeat(const char *v)` |
| `interp_bg_repeat2` | function | `src/css.c:649` | `static int interp_bg_repeat2(const char *v)` |
| `interp_bg_size` | function | `src/css.c:816` | `static int interp_bg_size(const char *v)` |
| `interp_border_collapse` | function | `src/css.c:516` | `static int interp_border_collapse(const char *v)` |
| `interp_border_style` | function | `src/css.c:1090` | `static int interp_border_style(const char *v)` |
| `interp_box_orient` | function | `src/css.c:2518` | `static int interp_box_orient(const char *v)` |
| `interp_boxsizing` | function | `src/css.c:400` | `static int interp_boxsizing(const char *v)` |
| `interp_bs_tok` | function | `src/css.c:1167` | `static int interp_bs_tok(const char *t, int *o)` |
| `interp_bw_tok` | function | `src/css.c:1166` | `static int interp_bw_tok(const char *t, int *o)` |
| `interp_bwidth1` | function | `src/css.c:1116` | `static int interp_bwidth1(const char *v)` |
| `interp_caption_side` | function | `src/css.c:557` | `static int interp_caption_side(const char *v)` |
| `interp_caret_color` | function | `src/css.c:596` | `static int interp_caret_color(const char *v)` |
| `interp_clear` | function | `src/css.c:413` | `static int interp_clear(const char *v)` |
| `interp_color` | function | `src/css.c:203` | `static int interp_color(const char *v)` |
| `interp_color_scheme` | function | `src/css.c:886` | `static int interp_color_scheme(const char *v)` |
| `interp_column_count` | function | `src/css.c:1267` | `static int interp_column_count(const char *v)` |
| `interp_column_width` | function | `src/css.c:1279` | `static int interp_column_width(const char *v)` |
| `interp_contain` | function | `src/css.c:851` | `static int interp_contain(const char *v)` |
| `interp_content_visibility` | function | `src/css.c:872` | `static int interp_content_visibility(const char *v)` |
| `interp_cursor` | function | `src/css.c:462` | `static int interp_cursor(const char *v)` |
| `interp_direction` | function | `src/css.c:384` | `static int interp_direction(const char *v)` |
| `interp_display` | function | `src/css.c:356` | `static int interp_display(const char *v)` |
| `interp_empty_cells` | function | `src/css.c:550` | `static int interp_empty_cells(const char *v)` |
| `interp_filter_deg` | function | `src/css.c:1372` | `static int interp_filter_deg(const char *s)` |
| `interp_filter_pct` | function | `src/css.c:1358` | `static int interp_filter_pct(const char *s)` |
| `interp_flex_basis` | function | `src/css.c:2397` | `static int interp_flex_basis(const char *v, int *out)` |
| `interp_flex_direction` | function | `src/css.c:2500` | `static int interp_flex_direction(const char *v)` |
| `interp_flex_factor` | function | `src/css.c:2387` | `static int interp_flex_factor(const char *v)` |
| `interp_flex_line_pack` | function | `src/css.c:2545` | `static int interp_flex_line_pack(const char *v)` |
| `interp_flex_wrap` | function | `src/css.c:2555` | `static int interp_flex_wrap(const char *v)` |
| `interp_float` | function | `src/css.c:406` | `static int interp_float(const char *v)` |
| `interp_font_kerning` | function | `src/css.c:1002` | `static int interp_font_kerning(const char *v)` |
| `interp_font_stretch` | function | `src/css.c:1017` | `static int interp_font_stretch(const char *v)` |
| `interp_font_variant` | function | `src/css.c:571` | `static int interp_font_variant(const char *v)` |
| `interp_fontfamily` | function | `src/css.c:374` | `static int interp_fontfamily(const char *v)` |
| `interp_fontsize_ex` | function | `src/css.c:326` | `static int interp_fontsize_ex(const char *v, int *abs_out)` |
| `interp_forced_color_adjust` | function | `src/css.c:915` | `static int interp_forced_color_adjust(const char *v)` |
| `interp_gap` | function | `src/css.c:360` | `static int interp_gap(const char *v)` |
| `interp_grid_flow` | function | `src/css.c:2563` | `static int interp_grid_flow(const char *v)` |
| `interp_hyphens` | function | `src/css.c:579` | `static int interp_hyphens(const char *v)` |
| `interp_image_rendering` | function | `src/css.c:879` | `static int interp_image_rendering(const char *v)` |
| `interp_isolation` | function | `src/css.c:845` | `static int interp_isolation(const char *v)` |
| `interp_justify` | function | `src/css.c:364` | `static int interp_justify(const char *v)` |
| `interp_len` | function | `src/css.c:305` | `static int interp_len(const char *v, int allow_auto, int *out)` |
| `interp_lineheight` | function | `src/css.c:340` | `static int interp_lineheight(const char *v)` |
| `interp_list_style_pos` | function | `src/css.c:996` | `static int interp_list_style_pos(const char *v)` |
| `interp_liststyle` | function | `src/css.c:385` | `static int interp_liststyle(const char *v)` |
| `interp_lp` | function | `src/css.c:309` | `static int interp_lp(const char *v, int allow_auto, int allow_pct,                      int *out_...` |
| `interp_mix_blend_mode` | function | `src/css.c:922` | `static int interp_mix_blend_mode(const char *v)` |
| `interp_object_fit` | function | `src/css.c:987` | `static int interp_object_fit(const char *v)` |
| `interp_object_pos` | function | `src/css.c:945` | `static int interp_object_pos(const char *v)` |
| `interp_opacity` | function | `src/css.c:376` | `static int interp_opacity(const char *v)` |
| `interp_outline_style` | function | `src/css.c:1236` | `static int interp_outline_style(const char *v)` |
| `interp_overflow` | function | `src/css.c:430` | `static int interp_overflow(const char *v)` |
| `interp_overflow_wrap` | function | `src/css.c:508` | `static int interp_overflow_wrap(const char *v)` |
| `interp_overscroll_behavior` | function | `src/css.c:1060` | `static int interp_overscroll_behavior(const char *v)` |
| `interp_pointer_events` | function | `src/css.c:626` | `static int interp_pointer_events(const char *v)` |
| `interp_position` | function | `src/css.c:391` | `static int interp_position(const char *v)` |
| `interp_print_color_adjust` | function | `src/css.c:909` | `static int interp_print_color_adjust(const char *v)` |
| `interp_resize` | function | `src/css.c:1030` | `static int interp_resize(const char *v)` |
| `interp_scroll_behavior` | function | `src/css.c:1038` | `static int interp_scroll_behavior(const char *v)` |
| `interp_style` | function | `src/css.c:348` | `static int interp_style(const char *v)` |
| `interp_table_layout` | function | `src/css.c:564` | `static int interp_table_layout(const char *v)` |
| `interp_tabsize` | function | `src/css.c:380` | `static int interp_tabsize(const char *v)` |
| `interp_text_overflow` | function | `src/css.c:494` | `static int interp_text_overflow(const char *v)` |
| `interp_text_rendering` | function | `src/css.c:1009` | `static int interp_text_rendering(const char *v)` |
| `interp_textdeco` | function | `src/css.c:352` | `static int interp_textdeco(const char *v)` |
| `interp_textdeco_style` | function | `src/css.c:381` | `static int interp_textdeco_style(const char *v)` |
| `interp_textdeco_thickness` | function | `src/css.c:382` | `static int interp_textdeco_thickness(const char *v)` |
| `interp_texttransform` | function | `src/css.c:375` | `static int interp_texttransform(const char *v)` |
| `interp_time_ms` | function | `src/css.c:1125` | `static int interp_time_ms(const char *v)` |
| `interp_transition_property` | function | `src/css.c:378` | `static int interp_transition_property(const char *v)` |
| `interp_user_select` | function | `src/css.c:587` | `static int interp_user_select(const char *v)` |
| `interp_visibility` | function | `src/css.c:423` | `static int interp_visibility(const char *v)` |
| `interp_weight` | function | `src/css.c:344` | `static int interp_weight(const char *v)` |
| `interp_whitespace` | function | `src/css.c:379` | `static int interp_whitespace(const char *v)` |
| `interp_word_break` | function | `src/css.c:500` | `static int interp_word_break(const char *v)` |
| `interpret_decls` | function | `src/css.c:4996` | `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,                ...` |
| `interpret_prop` | function | `src/css.c:4803` | `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,             ...` |
| `interpret_prop_dispatch` | function | `src/css.c:3960` | `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,    ...` |
| `is_anim_ident` | function | `src/css.c:1510` | `static int is_anim_ident(const char *tok)` |
| `is_inert_prop` | function | `src/css.c:3937` | `static int is_inert_prop(const char *prop)` |
| `item` | function | `src/css.c:1400` | `* timing list takes its first item (CSS Animations/Transitions 1: with one  * transition/animatio...` |
| `layer` | function | `src/css.c:670` | `* first layer (the one painted) -- so `background: url(x) no-repeat` stops tiling  * and a later ...` |
| `layer_register` | function | `src/css.c:5351` | `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,                      ...` |
| `len_rebase` | function | `src/css.c:5863` | `static char *len_rebase(const char *s, size_t n, const len_rebase_ctx *c, size_t *outlen)` |
| `len_rebase_ctx` | struct | `src/css.c:5821` | `` |
| `len_unit_px` | function | `src/css.c:5833` | `static double len_unit_px(const char *u, size_t len, const len_rebase_ctx *c)` |
| `lp_can_be_nonneg` | function | `src/css.c:314` | `static int lp_can_be_nonneg(int px_val, int pct_pm)` |
| `matrix` | function | `src/css.c:2840` | `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands...` |
| `multiplying` | function | `src/css.c:3884` | `* instead of the two multiplying (no page measured needs both on one element).  * A third (z) com...` |
| `next_ws_token` | function | `src/css.c:318` | `static int next_ws_token(const char **p, char *tok, size_t cap)` |
| `number` | function | `src/css.c:525` | `* number (no unit) as px (common in shorthand context like "10 5"). */ static int interp_border_s...` |
| `order` | function | `src/css.c:1752` | `* declaration order (dx, dy, optional blur >= 0);` |
| `origin_component` | function | `src/css.c:3459` | `static int origin_component(const char *tok, int axis, int *out)` |
| `page_view` | function | `src/css.c:6179` | `* the generated text reaches page_view (which materialises it as a synthetic * run);` |
| `parent` | function | `src/css.c:6212` | `* property from the parent (`inherit`), and an unset non-inherited one          * stands at its i...` |
| `parse_angle_deg` | function | `src/css.c:3251` | `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);` |
| `parse_block` | function | `src/css.c:5476` | `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,                  ...` |
| `parse_color` | function | `src/css.c:199` | `static int parse_color(const char *v)` |
| `parse_matrix6` | function | `src/css.c:2893` | `static int parse_matrix6(const char *p, size_t argn, double m6[6])` |
| `parse_num` | function | `src/css.c:188` | `static int parse_num(const char *s, double *out, const char **endp)` |
| `parse_numlist` | function | `src/css.c:2870` | `static int parse_numlist(const char *p, size_t argn, double *m6, int count)` |
| `property` | function | `src/css.c:3576` | `* error drops the whole property (fail closed). */ static int expand_clip(const char *val, css_de...` |
| `pseudo_of` | function | `src/css.c:6874` | `static int pseudo_of(int which)` |
| `raw_add` | function | `src/css.c:4877` | `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)` |
| `rem_emit_px` | function | `src/css.c:5803` | `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)` |
| `rem_ident_ch` | function | `src/css.c:5785` | `static int rem_ident_ch(char c)` |
| `rem_num_starts_after` | function | `src/css.c:5793` | `static int rem_num_starts_after(char prev)` |
| `rem_px` | type_alias | `src/css.c:5821` | `typedef struct len_rebase_ctx { double rem_px;` |
| `rem_rebase` | function | `src/css.c:5929` | `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)` |
| `remap_to_mask` | function | `src/css.c:769` | `static int remap_to_mask(css_decl *dst, int n)` |
| `resolve_core` | function | `src/css.c:6894` | `static css_style resolve_core(const css_sheet *sheet, const css_element *el,                     ...` |
| `sel_list_comma` | function | `src/css.c:2302` | `static size_t sel_list_comma(const char *s, size_t i, size_t end);` |
| `selector_matches_root` | function | `src/css.c:2698` | `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m,          ...` |
| `sentinel` | function | `src/css.c:4290` | `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);` |
| `sheet_index` | function | `src/css.c:5937` | `static void sheet_index(css_sheet *sh)` |
| `sheet_pools_reserve` | function | `src/css.c:5054` | `static void sheet_pools_reserve(css_sheet *sh)` |
| `sheet_rewind` | function | `src/css.c:5942` | `static void sheet_rewind(css_sheet *sh)` |
| `sheet_root_font_px` | function | `src/css.c:5989` | `static double sheet_root_font_px(const css_sheet *sh)` |
| `shorthand` | function | `src/css.c:3541` | `* An uninterpretable token drops the whole shorthand (fail closed). */ static int expand_place(co...` |
| `shorthand` | function | `src/css.c:3787` | `* generic bucket keeps the rest of the shorthand (same net effect as the  * font-family longhand ...` |
| `skip_at_rule` | function | `src/css.c:5174` | `static size_t skip_at_rule(const char *s, size_t i, size_t n)` |
| `slots` | function | `src/css.c:4150` | `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return...` |
| `split_top_args` | function | `src/css.c:2906` | `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,                ...` |
| `strip_comments` | function | `src/css.c:5997` | `static char *strip_comments(const char *text, size_t len, size_t *outlen)` |
| `strip_important` | function | `src/css.c:2594` | `static int strip_important(char *val)` |
| `subject_may_be_root` | function | `src/css.c:2650` | `static int subject_may_be_root(const char *s, size_t a, size_t b, const char *root_scope)` |
| `supports_matches` | function | `src/css.c:5257` | `static int supports_matches(const char *s, size_t a, size_t b)` |
| `supports_selector_ok` | function | `src/css.c:5248` | `static int supports_selector_ok(void *ctx, const char *sel)` |
| `text` | function | `src/css.c:275` | `* source text (rem_rebase, see below) rather than by threading a context here.  *  * Viewport uni...` |
| `through` | function | `src/css.c:219` | `* at the two SHARED chokepoints every property funnels through (the generic  * dispatch tail, and...` |
| `tr_decompose` | function | `src/css.c:2847` | `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,                         in...` |
| `tr_mul` | function | `src/css.c:2827` | `static void tr_mul(double out[6], const double l[6], const double r[6])` |
| `translate3d` | function | `src/css.c:2936` | `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine  * renders z as nothing,...` |
| `translateX` | function | `src/css.c:3247` | `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc...` |
| `translateZ` | function | `src/css.c:3256` | `* translateZ(), rotateX(0) and rotateY(0) emit the identity (with the stacking * context Firefox builds);` |
| `var` | function | `src/css.c:2619` | `* cvr_resolve then substitutes var() references when a declaration's value is  * interpreted (par...` |
| `var` | function | `src/css.c:6007` | `* collected and forty var() declarations -- font sizes, widths, radii, the      * whole theme -- ...` |
| `wide_claim` | function | `src/css.c:4763` | `static int wide_claim(const char *prop, css_decl *dst, int cap,                       char (*urlt...` |
| `writing` | function | `src/css.c:3745` | `* Wide keywords claim BOTH slots without writing (inheritance then flows, as  * the tail does for...` |
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
| `AUTO_REJECT` | macro | `src/css_box.c:1248` | `#define AUTO_REJECT` |
| `AUTO_RESET` | macro | `src/css_box.c:1250` | `#define AUTO_RESET` |
| `AUTO_RESET_NONE` | macro | `src/css_box.c:1254` | `#define AUTO_RESET_NONE` |
| `AUTO_VALUE` | macro | `src/css_box.c:1249` | `#define AUTO_VALUE` |
| `CSS_CALC_MAX_DEPTH` | macro | `src/css_box.c:714` | `#define CSS_CALC_MAX_DEPTH` |
| `CSS_MATHFN_MAX_ARGS` | macro | `src/css_box.c:718` | `#define CSS_MATHFN_MAX_ARGS` |
| `RELATIVE` | function | `src/css_box.c:63` | `* or RELATIVE (of the inherited size). Absolute: px/pt/rem/viewport units and the * absolute keywords. Relative: em...` |
| `accepts` | function | `src/css_box.c:706` | `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further...` |
| `calc_eval_em` | function | `src/css_box.c:974` | `static int calc_eval_em(const char *v, size_t vlen, double *out_em)` |
| `calc_eval_full` | function | `src/css_box.c:960` | `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,            ...` |
| `calc_expr` | function | `src/css_box.c:938` | `static int calc_expr(calc_parser *p, calc_val *out, int depth)` |
| `calc_match_fn` | function | `src/css_box.c:746` | `static int calc_match_fn(calc_parser *p, const char *name)` |
| `calc_mathfn` | function | `src/css_box.c:788` | `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` |
| `calc_parser` | struct | `src/css_box.c:737` | `` |
| `calc_piecewise` | function | `src/css_box.c:773` | `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)` |
| `calc_skip_ws` | function | `src/css_box.c:739` | `static void calc_skip_ws(calc_parser *p)` |
| `calc_term` | function | `src/css_box.c:911` | `static int calc_term(calc_parser *p, calc_val *out, int depth)` |
| `calc_unwrap` | function | `src/css_box.c:982` | `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` |
| `calc_val` | struct | `src/css_box.c:736` | `` |
| `cb_clip_inset` | function | `src/css_box.c:1141` | `int cb_clip_inset(const char *val, int px[4], int pm[4])` |
| `cb_copy_trim` | function | `src/css_box.c:25` | `static size_t cb_copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `cb_expand_box2` | function | `src/css_box.c:1422` | `int cb_expand_box2(const char *val, int slot_start, int slot_end,                        int allo...` |
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
| `cch_element_matches` | function | `src/css_chain.c:465` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)` |
| `cch_element_matches_any` | function | `src/css_chain.c:479` | `int cch_element_matches_any(lxb_dom_element_t *el, const css_sel *sels, size_t n)` |
| `cch_element_style` | function | `src/css_chain.c:461` | `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)` |
| `cch_element_style_path` | function | `src/css_chain.c:372` | `css_style cch_element_style_path(cch_path *pa, lxb_dom_element_t *el, const css_sheet *sheet,    ...` |
| `cch_element_style_vars` | function | `src/css_chain.c:310` | `css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,                  ...` |
| `cch_node` | struct | `src/css_chain.c:27` | `` |
| `cch_path` | struct | `src/css_chain.c:347` | `` |
| `cch_path_free` | function | `src/css_chain.c:365` | `void cch_path_free(cch_path *pa)` |
| `cch_path_new` | function | `src/css_chain.c:353` | `cch_path *cch_path_new(void)` |
| `cch_pseudo_style` | function | `src/css_chain.c:442` | `css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,             ...` |
| `cls_space` | function | `src/css_chain.c:42` | `static int cls_space(char c)` |
| `count_children` | function | `src/css_chain.c:227` | `static int count_children(lxb_dom_node_t *n)` |
| `fill_css_node` | function | `src/css_chain.c:99` | `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)` |
| `inputs` | function | `src/css_chain.c:241` | `* identical inputs (single source of truth). */ static const css_element *build_chain(lxb_dom_ele...` |
| `path_truncate` | function | `src/css_chain.c:357` | `static void path_truncate(cch_path *pa, int keep)` |
| `release_nodes` | function | `src/css_chain.c:90` | `static void release_nodes(cch_node *nodes, int n)` |
| `sibling_position` | function | `src/css_chain.c:181` | `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
| `sibling_type_position` | function | `src/css_chain.c:199` | `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)` |
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
| `CG_RAD_FLOOR` | macro | `src/css_gradient.c:772` | `#define CG_RAD_FLOOR` |
| `CG_RAD_PM_MAX` | macro | `src/css_gradient.c:615` | `#define CG_RAD_PM_MAX` |
| `CG_RAD_PX_MAX` | macro | `src/css_gradient.c:616` | `#define CG_RAD_PX_MAX` |
| `CG_RAD_TOKENS` | macro | `src/css_gradient.c:614` | `#define CG_RAD_TOKENS` |
| `CG_SQRT2` | macro | `src/css_gradient.c:773` | `#define CG_SQRT2` |
| `CSS_GRAD_STOPS_MAX` | function | `src/css_gradient.c:184` | `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when  * the gradient fai...` |
| `bg_layer_tokens_ok` | function | `src/css_gradient.c:490` | `static int bg_layer_tokens_ok(const char *s)` |
| `cg_dmax` | function | `src/css_gradient.c:776` | `static double cg_dmax(double a, double b)` |
| `cg_dmin` | function | `src/css_gradient.c:775` | `static double cg_dmin(double a, double b)` |
| `cg_expand_background` | function | `src/css_gradient.c:530` | `int cg_expand_background(const char *val, css_decl *dst, int cap,                              ch...` |
| `cg_first_url` | function | `src/css_gradient.c:398` | `int cg_first_url(const char *val, char *out, size_t outcap)` |
| `cg_parse_linear` | function | `src/css_gradient.c:815` | `int cg_parse_linear(const char *fn, int *angle, int *colors, int *positions)` |
| `cg_parse_num` | function | `src/css_gradient.c:13` | `static int cg_parse_num(const char *s, double *out, const char **endp)` |
| `cg_parse_radial_prelude` | function | `src/css_gradient.c:690` | `int cg_parse_radial_prelude(const char *seg, cg_radial *out)` |
| `cg_radial_geometry` | function | `src/css_gradient.c:778` | `void cg_radial_geometry(const cg_radial *r, double w, double h,                         double *c...` |
| `cg_radial_len_px` | function | `src/css_gradient.c:766` | `double cg_radial_len_px(int enc, double dim)` |
| `cg_wide_keyword` | function | `src/css_gradient.c:18` | `static int cg_wide_keyword(const char *v)` |
| `conic_prelude` | function | `src/css_gradient.c:111` | `static int conic_prelude(const char *seg, int *angle)` |
| `declaration` | function | `src/css_gradient.c:483` | `* declaration (fail closed);` |
| `downstream` | function | `src/css_gradient.c:422` | `* happens downstream (render_doc.c), gated by caps.images like an <img>. */ int cg_expand_bg_imag...` |
| `emit_gradient` | function | `src/css_gradient.c:291` | `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,                          ...` |
| `emit_radial_geom` | function | `src/css_gradient.c:405` | `static int emit_radial_geom(css_decl *dst, int cap, const cg_radial *r)` |
| `find_gradient_call` | function | `src/css_gradient.c:77` | `static int find_gradient_call(const char *v, const char *fn, size_t *start,                      ...` |
| `find_radial_gradient` | function | `src/css_gradient.c:360` | `static int find_radial_gradient(const char *v, size_t *start, size_t *end,                       ...` |
| `grad_stop_pos` | function | `src/css_gradient.c:153` | `static int grad_stop_pos(const char *pp, int conic, const char **endp)` |
| `gradient` | function | `src/css_gradient.c:28` | `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,  * the whole decl...` |
| `pool` | function | `src/css_gradient.c:418` | `* pool (gradient explicitly reset);` |
| `rad_ieq` | function | `src/css_gradient.c:618` | `static int rad_ieq(const char *a, const char *b)` |
| `rad_is_len_start` | function | `src/css_gradient.c:647` | `static int rad_is_len_start(const char *t)` |
| `rad_len` | function | `src/css_gradient.c:626` | `static int rad_len(const char *tok, int *enc)` |
| `rad_parse_position` | function | `src/css_gradient.c:661` | `static int rad_parse_position(char (*tok)[CSS_TOK_MAX], int n, int *cx, int *cy)` |
| `rad_pos_kw` | function | `src/css_gradient.c:652` | `static int rad_pos_kw(const char *t, int *axis)` |
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

Next: [SYMBOLS_p8.md](SYMBOLS_p8.md)
