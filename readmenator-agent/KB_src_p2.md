# Subsystem: src (page 2 of 10)
Previous: [KB_src.md](KB_src.md)

## src/css.c
- Doc: len_rebase_ctx: int r = snprintf(out + *o, space, "%.4f", px); if (r < 0 || (size_t)r >= space)...
- Layer: utility
- Language: c
- Symbols:
  - `css_sheet` (struct, line 104)
  - `css_keyframe_stop` (struct, line 144)
  - `len_rebase_ctx` (struct, line 5702)
  - `css_match` (struct, line 6557)
  - `css_cand` (struct, line 6563)
  - `css_rule` (struct, line 102)
  - `rem_px` (type_alias, line 5702) `typedef struct len_rebase_ctx { double rem_px;`
  - `idx` (type_alias, line 6563) `typedef struct css_cand { int imp, espec, ord, idx;`
  - `parse_num` (function, line 181) `static int parse_num(const char *s, double *out, const char **endp)`
  - `parse_color` (function, line 192) `static int parse_color(const char *v)`
  - `interp_color` (function, line 196) `static int interp_color(const char *v)`
  - `through` (function, line 212) `* at the two SHARED chokepoints every property funnels through (the generic
 * dispatch tail, and...`
  - `bg_alpha_of` (function, line 236) `static int bg_alpha_of(const char *v)`
  - `interp_bg` (function, line 240) `static int interp_bg(const char *v)`
  - `expand_bg_image` (function, line 248) `static int expand_bg_image(const char *val, css_decl *dst, int cap,
                           ch...`
  - `expand_background` (function, line 256) `static int expand_background(const char *val, css_decl *dst, int cap,
                           ...`
  - `text` (function, line 268) `* source text (rem_rebase, see below) rather than by threading a context here.
 *
 * Viewport uni...`
  - `expand_box4` (function, line 288) `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,
            ...`
  - `expand_box2` (function, line 293) `static int expand_box2(const char *val, int slot_start, int slot_end,
                       int ...`
  - `interp_len` (function, line 298) `static int interp_len(const char *v, int allow_auto, int *out)`
  - `interp_lp` (function, line 302) `static int interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_...`
  - `lp_can_be_nonneg` (function, line 307) `static int lp_can_be_nonneg(int px_val, int pct_pm)`
  - `next_ws_token` (function, line 311) `static int next_ws_token(const char **p, char *tok, size_t cap)`
  - `interp_align` (function, line 315) `static int interp_align(const char *v)`
  - `interp_fontsize_ex` (function, line 319) `static int interp_fontsize_ex(const char *v, int *abs_out)`
  - `interp_lineheight` (function, line 323) `static int interp_lineheight(const char *v)`
  - `interp_weight` (function, line 327) `static int interp_weight(const char *v)`
  - `interp_style` (function, line 331) `static int interp_style(const char *v)`
  - `interp_textdeco` (function, line 335) `static int interp_textdeco(const char *v)`
  - `interp_display` (function, line 339) `static int interp_display(const char *v)`
  - `interp_gap` (function, line 343) `static int interp_gap(const char *v)`
  - `interp_justify` (function, line 347) `static int interp_justify(const char *v)`
  - `expand_grid_template_cols` (function, line 351) `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)`
  - `interp_fontfamily` (function, line 357) `static int interp_fontfamily(const char *v)`
  - `interp_texttransform` (function, line 358) `static int interp_texttransform(const char *v)`
  - `interp_opacity` (function, line 359) `static int interp_opacity(const char *v)`
  - `expand_valign` (function, line 360) `static int expand_valign(const char *val, css_decl *dst, int cap)`
  - `interp_transition_property` (function, line 361) `static int interp_transition_property(const char *v)`
  - `interp_whitespace` (function, line 362) `static int interp_whitespace(const char *v)`
  - `interp_tabsize` (function, line 363) `static int interp_tabsize(const char *v)`
  - `interp_textdeco_style` (function, line 364) `static int interp_textdeco_style(const char *v)`
  - `interp_textdeco_thickness` (function, line 365) `static int interp_textdeco_thickness(const char *v)`
  - `interp_aspect_ratio` (function, line 366) `static int interp_aspect_ratio(const char *v, int *num, int *den)`
  - `interp_direction` (function, line 367) `static int interp_direction(const char *v)`
  - `interp_liststyle` (function, line 368) `static int interp_liststyle(const char *v)`
  - `emit_spacing` (function, line 369) `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
  - `expand_shadow` (function, line 370) `static int expand_shadow(const char *val, css_decl *dst, int cap)`
  - `interp_position` (function, line 374) `static int interp_position(const char *v)`
  - `interp_boxsizing` (function, line 383) `static int interp_boxsizing(const char *v)`
  - `interp_float` (function, line 389) `static int interp_float(const char *v)`
  - `interp_clear` (function, line 396) `static int interp_clear(const char *v)`
  - `interp_visibility` (function, line 406) `static int interp_visibility(const char *v)`
  - `interp_overflow` (function, line 413) `static int interp_overflow(const char *v)`
  - `interp_cursor` (function, line 445) `static int interp_cursor(const char *v)`
  - `interp_text_overflow` (function, line 477) `static int interp_text_overflow(const char *v)`
  - `interp_word_break` (function, line 483) `static int interp_word_break(const char *v)`
  - `interp_overflow_wrap` (function, line 491) `static int interp_overflow_wrap(const char *v)`
  - `interp_border_collapse` (function, line 499) `static int interp_border_collapse(const char *v)`
  - `number` (function, line 508) `* number (no unit) as px (common in shorthand context like "10 5"). */
static int interp_border_s...`
  - `interp_empty_cells` (function, line 533) `static int interp_empty_cells(const char *v)`
  - `interp_caption_side` (function, line 540) `static int interp_caption_side(const char *v)`
  - `interp_table_layout` (function, line 547) `static int interp_table_layout(const char *v)`
  - `interp_font_variant` (function, line 554) `static int interp_font_variant(const char *v)`
  - `interp_hyphens` (function, line 562) `static int interp_hyphens(const char *v)`
  - `interp_user_select` (function, line 570) `static int interp_user_select(const char *v)`
  - `interp_caret_color` (function, line 579) `static int interp_caret_color(const char *v)`
  - `interp_appearance` (function, line 591) `static int interp_appearance(const char *v)`
  - `interp_pointer_events` (function, line 609) `static int interp_pointer_events(const char *v)`
  - `interp_bg_repeat` (function, line 621) `static int interp_bg_repeat(const char *v)`
  - `interp_bg_repeat2` (function, line 632) `static int interp_bg_repeat2(const char *v)`
  - `layer` (function, line 653) `* first layer (the one painted) -- so `background: url(x) no-repeat` stops tiling
 * and a later ...`
  - `expand_background_layer` (function, line 662) `static int expand_background_layer(const char *val, css_decl *dst, int cap)`
  - `bg_to_mask_slot` (function, line 738) `static int bg_to_mask_slot(int prop)`
  - `remap_to_mask` (function, line 752) `static int remap_to_mask(css_decl *dst, int n)`
  - `expand_mask_geometry` (function, line 761) `static int expand_mask_geometry(const char *prop, const char *val, css_decl *dst, int cap)`
  - `emit_mask_image` (function, line 780) `static int emit_mask_image(const char *prop, const char *val, css_decl *dst, int cap,
           ...`
  - `interp_bg_size` (function, line 799) `static int interp_bg_size(const char *v)`
  - `interp_bg_clip` (function, line 806) `static int interp_bg_clip(const char *v)`
  - `interp_bg_origin` (function, line 814) `static int interp_bg_origin(const char *v)`
  - `interp_bg_attachment` (function, line 821) `static int interp_bg_attachment(const char *v)`
  - `interp_isolation` (function, line 828) `static int interp_isolation(const char *v)`
  - `interp_contain` (function, line 834) `static int interp_contain(const char *v)`
  - `interp_content_visibility` (function, line 855) `static int interp_content_visibility(const char *v)`
  - `interp_image_rendering` (function, line 862) `static int interp_image_rendering(const char *v)`
  - `interp_color_scheme` (function, line 869) `static int interp_color_scheme(const char *v)`
  - `interp_accent_color` (function, line 887) `static int interp_accent_color(const char *v)`
  - `interp_print_color_adjust` (function, line 892) `static int interp_print_color_adjust(const char *v)`
  - `interp_forced_color_adjust` (function, line 898) `static int interp_forced_color_adjust(const char *v)`
  - `interp_mix_blend_mode` (function, line 905) `static int interp_mix_blend_mode(const char *v)`
  - `interp_object_pos` (function, line 928) `static int interp_object_pos(const char *v)`
  - `interp_object_fit` (function, line 970) `static int interp_object_fit(const char *v)`
  - `interp_list_style_pos` (function, line 979) `static int interp_list_style_pos(const char *v)`
  - `interp_font_kerning` (function, line 985) `static int interp_font_kerning(const char *v)`
  - `interp_text_rendering` (function, line 992) `static int interp_text_rendering(const char *v)`
  - `interp_font_stretch` (function, line 1000) `static int interp_font_stretch(const char *v)`
  - `interp_resize` (function, line 1013) `static int interp_resize(const char *v)`
  - `interp_scroll_behavior` (function, line 1021) `static int interp_scroll_behavior(const char *v)`
  - `interp_overscroll_behavior` (function, line 1043) `static int interp_overscroll_behavior(const char *v)`
  - `interp_backface_visibility` (function, line 1050) `static int interp_backface_visibility(const char *v)`
  - `interp_border_style` (function, line 1073) `static int interp_border_style(const char *v)`
  - `interp_bwidth1` (function, line 1099) `static int interp_bwidth1(const char *v)`
  - `interp_time_ms` (function, line 1108) `static int interp_time_ms(const char *v)`
  - `emit_radius_corner` (function, line 1141) `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)`
  - `interp_bw_tok` (function, line 1149) `static int interp_bw_tok(const char *t, int *o)`
  - `interp_bs_tok` (function, line 1150) `static int interp_bs_tok(const char *t, int *o)`
  - `interp_bc_tok` (function, line 1151) `static int interp_bc_tok(const char *t, int *o)`
  - `expand_outline` (function, line 1216) `static int expand_outline(const char *val, css_decl *dst, int cap)`
  - `interp_column_count` (function, line 1232) `static int interp_column_count(const char *v)`
  - `interp_column_width` (function, line 1244) `static int interp_column_width(const char *v)`
  - `expand_columns` (function, line 1255) `static int expand_columns(const char *val, css_decl *dst, int cap)`
  - `expand_flex_flow` (function, line 1289) `static int expand_flex_flow(const char *val, css_decl *dst, int cap)`
  - `expand_column_rule` (function, line 1311) `static int expand_column_rule(const char *val, css_decl *dst, int cap)`
  - `interp_filter_pct` (function, line 1323) `static int interp_filter_pct(const char *s)`
  - `interp_filter_deg` (function, line 1337) `static int interp_filter_deg(const char *s)`
  - `filter_paren_body` (function, line 1352) `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)`
  - `item` (function, line 1365) `* timing list takes its first item (CSS Animations/Transitions 1: with one
 * transition/animatio...`
  - `easing_steps` (function, line 1436) `static int easing_steps(const char *tok)`
  - `anim_easing_iv` (function, line 1458) `static int anim_easing_iv(const char *tok)`
  - `is_anim_ident` (function, line 1475) `static int is_anim_ident(const char *tok)`
  - `expand_animation` (function, line 1491) `static int expand_animation(const char *val, css_decl *dst, int cap)`
  - `expand_backdrop_filter` (function, line 1755) `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)`
  - `axis` (function, line 1789) `* bare center displaces it to the free axis (`center right` = x:right, y:center).
 * Any other co...`
  - `expand_bg_size` (function, line 1905) `static int expand_bg_size(const char *val, css_decl *dst, int cap)`
  - `emit_content` (function, line 1945) `static int emit_content(css_decl *dst, int cap, const char *str,
                        char (*c...`
  - `expand_counter_decls` (function, line 2052) `static int expand_counter_decls(const char *prop, const char *val, css_decl *dst, int cap,
      ...`
  - `expand_content` (function, line 2070) `static int expand_content(const char *val, css_decl *dst, int cap,
                          char...`
  - `expand_grid_areas` (function, line 2121) `static int expand_grid_areas(const char *val, css_decl *dst, int cap,
                           ...`
  - `expand_grid_area_lines` (function, line 2149) `static int expand_grid_area_lines(const char *val, css_decl *dst, int cap)`
  - `expand_grid_line` (function, line 2174) `static int expand_grid_line(const char *val, css_decl *dst, int cap, int p_start, int p_end)`
  - `expand_grid_area` (function, line 2183) `static int expand_grid_area(const char *val, css_decl *dst, int cap)`
  - `expand_grid_template` (function, line 2222) `static int expand_grid_template(const char *val, css_decl *dst, int cap,
                        ...`
  - `box_shadow_layer` (function, line 2274) `static int box_shadow_layer(const char *val, size_t len, int out[6])`
  - `declaration` (function, line 2310) `* invalid layer drops the whole declaration (fail closed). `none` is an explicit
 * no-shadow. ur...`
  - `interp_flex_factor` (function, line 2352) `static int interp_flex_factor(const char *v)`
  - `interp_flex_basis` (function, line 2362) `static int interp_flex_basis(const char *v, int *out)`
  - `expand_flex` (function, line 2396) `static int expand_flex(const char *val, css_decl *dst, int cap)`
  - `interp_align_kw` (function, line 2441) `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)`
  - `interp_flex_direction` (function, line 2465) `static int interp_flex_direction(const char *v)`
  - `interp_box_orient` (function, line 2483) `static int interp_box_orient(const char *v)`
  - `interp_flex_line_pack` (function, line 2510) `static int interp_flex_line_pack(const char *v)`
  - `interp_flex_wrap` (function, line 2520) `static int interp_flex_wrap(const char *v)`
  - `interp_grid_flow` (function, line 2528) `static int interp_grid_flow(const char *v)`
  - `copy_trim` (function, line 2546) `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)`
  - `strip_important` (function, line 2559) `static int strip_important(char *val)`
  - `var` (function, line 2584) `* cvr_resolve then substitutes var() references when a declaration's value is
 * interpreted (par...`
  - `has_double_dash` (function, line 2606) `static int has_double_dash(const char *p, size_t n)`
  - `subject_may_be_root` (function, line 2615) `static int subject_may_be_root(const char *s, size_t a, size_t b, const char *root_scope)`
  - `selector_matches_root` (function, line 2663) `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m,
         ...`
  - `tr_mul` (function, line 2792) `static void tr_mul(double out[6], const double l[6], const double r[6])`
  - `tr_decompose` (function, line 2812) `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,
                        in...`
  - `parse_numlist` (function, line 2835) `static int parse_numlist(const char *p, size_t argn, double *m6, int count)`
  - `parse_matrix6` (function, line 2858) `static int parse_matrix6(const char *p, size_t argn, double m6[6])`
  - `split_top_args` (function, line 2871) `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,
               ...`
  - `translate3d` (function, line 2901) `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine
 * renders z as nothing,...`
  - `function` (function, line 3223) `* transform function (perspective/rotate3d/...), or unparseable syntax,
 * rejects the WHOLE decl...`
  - `origin_component` (function, line 3424) `static int origin_component(const char *tok, int axis, int *out)`
  - `expand_transform_origin` (function, line 3450) `static int expand_transform_origin(const char *val, css_decl *dst, int cap)`
  - `expand_gap` (function, line 3482) `static int expand_gap(const char *val, css_decl *dst, int cap)`
  - `shorthand` (function, line 3506) `* An uninterpretable token drops the whole shorthand (fail closed). */
static int expand_place(co...`
  - `property` (function, line 3541) `* error drops the whole property (fail closed). */
static int expand_clip(const char *val, css_de...`
  - `expand_clip_path` (function, line 3585) `static int expand_clip_path(const char *val, css_decl *dst, int cap)`
  - `font_list_alias` (function, line 3632) `static void font_list_alias(const css_sheet *sheet, const char *ls, char *out, size_t cap)`
  - `font_list_norm` (function, line 3666) `static int font_list_norm(const char *val, char *out, size_t cap)`
  - `writing` (function, line 3710) `* Wide keywords claim BOTH slots without writing (inheritance then flows, as
 * the tail does for...`
  - `shorthand` (function, line 3752) `* generic bucket keeps the rest of the shorthand (same net effect as the
 * font-family longhand ...`
  - `multiplying` (function, line 3849) `* instead of the two multiplying (no page measured needs both on one element).
 * A third (z) com...`
  - `is_inert_prop` (function, line 3902) `static int is_inert_prop(const char *prop)`
  - `interpret_prop_dispatch` (function, line 3925) `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,
   ...`
  - `wide_claim` (function, line 4695) `static int wide_claim(const char *prop, css_decl *dst, int cap,
                      char (*urlt...`
  - `interpret_prop` (function, line 4735) `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,
            ...`
  - `drop_copy_text` (function, line 4764) `static void drop_copy_text(char *dst, size_t cap, const char *src)`
  - `drop_record` (function, line 4783) `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)`
  - `raw_add` (function, line 4809) `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)`
  - `interpret_decls` (function, line 4928) `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,
               ...`
  - `sheet_pools_reserve` (function, line 4986) `static void sheet_pools_reserve(css_sheet *sh)`
  - `add_rule` (function, line 4992) `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,
                     siz...`
  - `skip_at_rule` (function, line 5105) `static size_t skip_at_rule(const char *s, size_t i, size_t n)`
  - `block_end` (function, line 5121) `static size_t block_end(const char *s, size_t open, size_t n)`
  - `at_is_media` (function, line 5143) `static int at_is_media(const char *s, size_t i, size_t n)`
  - `at_keyword` (function, line 5154) `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)`
  - `supports_selector_ok` (function, line 5179) `static int supports_selector_ok(void *ctx, const char *sel)`
  - `supports_matches` (function, line 5188) `static int supports_matches(const char *s, size_t a, size_t b)`
  - `layer_register` (function, line 5242) `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,
                     ...`
  - `collect_custom_props_scoped` (function, line 5285) `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,
                ...`
  - `parse_block` (function, line 5367) `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                 ...`
  - `download` (function, line 5534) `* the download (spec/webfont.md b3b). An empty src_url
                     * simply never resolv...`
  - `rem_ident_ch` (function, line 5666) `static int rem_ident_ch(char c)`
  - `rem_num_starts_after` (function, line 5674) `static int rem_num_starts_after(char prev)`
  - `rem_emit_px` (function, line 5684) `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)`
  - `len_unit_px` (function, line 5714) `static double len_unit_px(const char *u, size_t len, const len_rebase_ctx *c)`
  - `len_rebase` (function, line 5744) `static char *len_rebase(const char *s, size_t n, const len_rebase_ctx *c, size_t *outlen)`
  - `rem_rebase` (function, line 5810) `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)`
  - `sheet_index` (function, line 5818) `static void sheet_index(css_sheet *sh)`
  - `sheet_rewind` (function, line 5823) `static void sheet_rewind(css_sheet *sh)`
  - `sheet_root_font_px` (function, line 5868) `static double sheet_root_font_px(const css_sheet *sh)`
  - `strip_comments` (function, line 5876) `static char *strip_comments(const char *text, size_t len, size_t *outlen)`
  - `var` (function, line 5886) `* collected and forty var() declarations -- font sizes, widths, radii, the
     * whole theme -- ...`
  - `css_parse` (function, line 5911) `css_status css_parse(const char *text, size_t len, css_sheet **out)`
  - `css_parse_media` (function, line 5915) `css_status css_parse_media(const char *text, size_t len, const css_media *media,
                ...`
  - `css_parse_scoped` (function, line 5920) `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,
               ...`
  - `css_parse_logged` (function, line 5925) `css_status css_parse_logged(const char *text, size_t len, const css_media *media,
               ...`
  - `consumer` (function, line 5959) `* consumer (shorthands, calc(), var() values) gets it with no context
         * threaded through...`
  - `css_free` (function, line 6017) `void css_free(css_sheet *s)`
  - `content_attr_of` (function, line 6040) `static const char *content_attr_of(const css_element *el, const char *name)`
  - `apply_decl` (function, line 6049) `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...`
  - `parent` (function, line 6089) `* property from the parent (`inherit`), and an unset non-inherited one
         * stands at its i...`
  - `css_ua_heading_em` (function, line 6538) `double css_ua_heading_em(int level)`
  - `css_computed_font_size_for_tag` (function, line 6543) `double css_computed_font_size_for_tag(const css_style *o, double inherited_px, const char *tag)`
  - `computed_font_size` (function, line 6551) `static double computed_font_size(const css_style *o, const css_element *el)`
  - `cand_cmp` (function, line 6568) `static int cand_cmp(const void *pa, const void *pb)`
  - `apply_var_source` (function, line 6633) `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
        ...`
  - `apply_rule` (function, line 6660) `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...`
  - `fold_font_relative` (function, line 6698) `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,
                         ...`
  - `css_resolve_el` (function, line 6729) `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         ...`
  - `css_resolve_el_ex` (function, line 6738) `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,
                      ...`
  - `pseudo_of` (function, line 6745) `static int pseudo_of(int which)`
  - `css_resolve_pseudo` (function, line 6754) `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)`
  - `resolve_core` (function, line 6765) `static css_style resolve_core(const css_sheet *sheet, const css_element *el,
                    ...`
  - `css_resolve` (function, line 7026) `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                  ...`
  - `NULL` (function, line 7050) `* Sheet can be NULL (inline style, no @keyframes). */
void css_resolve_anim_keyframes(css_style *...`
  - `css_font_face_count` (function, line 7082) `size_t css_font_face_count(const css_sheet *sheet)`
  - `css_font_face_at` (function, line 7086) `int css_font_face_at(const css_sheet *sheet, size_t i,
                     char *family, size_t ...`
  - `css_parse_inline` (function, line 7096) `css_style css_parse_inline(const char *style, size_t len)`
  - `css_sheet_uses_counters` (function, line 7100) `int css_sheet_uses_counters(const css_sheet *sheet)`
  - `emit` (function, line 64) `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand...`
  - `css_decl` (function, line 91) `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);`
  - `expand_bg_position` (function, line 253) `static int expand_bg_position(const char *val, css_decl *dst, int cap);`
  - `first_comma_item` (function, line 736) `static void first_comma_item(const char *val, char *buf, size_t cap);`
  - `order` (function, line 1717) `* declaration order (dx, dy, optional blur >= 0);`
  - `blur` (function, line 1752) `* consumes ONLY blur(Npx);`
  - `cap` (function, line 2021) `* string past the cap (emit_content): a conforming declaration must not * count as a discard just because an icon...`
  - `empty` (function, line 2074) `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and...`
  - `sel_list_comma` (function, line 2267) `static size_t sel_list_comma(const char *s, size_t i, size_t end);`
  - `column` (function, line 2375) `* column (`flex: 1 1 0%`);`
  - `matrix` (function, line 2805) `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands...`
  - `LIST` (function, line 2894) `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose...`
  - `translateX` (function, line 3212) `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc...`
  - `parse_angle_deg` (function, line 3216) `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);`
  - `expand_transform_list` (function, line 3219) `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);`
  - `translateZ` (function, line 3221) `* translateZ(), rotateX(0) and rotateY(0) emit the identity (with the stacking * context Firefox builds);`
  - `caller` (function, line 3832) `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached...`
  - `evaluated` (function, line 3910) `* queries that read it are evaluated (or not) on their own (cmq_container_surely);`
  - `slots` (function, line 4094) `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return...`
  - `sentinel` (function, line 4222) `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);`
  - `here` (function, line 4435) `* servers have no form here (fail closed). */ int o = csel_ci_eq(val, "none") ? CSS_SVG_PAINT_NONE : interp_color(val);`
  - `csel_substr` (function, line 5176) `return known && csel_substr(val, "var(", 1);`
  - `page_view` (function, line 6056) `* the generated text reaches page_view (which materialises it as a synthetic * run);`
  - `CSS_INIT_SELS` (macro, line 51) `#define CSS_INIT_SELS`
  - `CSS_INIT_DECLS` (macro, line 52) `#define CSS_INIT_DECLS`
  - `CSS_DECL_SLOTS_MIN` (macro, line 67) `#define CSS_DECL_SLOTS_MIN`
  - `CSS_INIT_RULES` (macro, line 68) `#define CSS_INIT_RULES`
  - `CSS_SELS_PER_GROUP` (macro, line 69) `#define CSS_SELS_PER_GROUP`
  - `CSS_INLINE_DECLS` (macro, line 70) `#define CSS_INLINE_DECLS`
  - `P_META_CUSTOM` (macro, line 83) `#define P_META_CUSTOM`
  - `P_META_VARSRC` (macro, line 84) `#define P_META_VARSRC`
  - `CSS_MAX_RAW` (macro, line 87) `#define CSS_MAX_RAW`
  - `CSS_MAX_FONT_FACES` (macro, line 165) `#define CSS_MAX_FONT_FACES`
  - `CSS_WIDE_RESET` (macro, line 222) `#define CSS_WIDE_RESET`
  - `AUTO_REJECT` (macro, line 278) `#define AUTO_REJECT`
  - `AUTO_VALUE` (macro, line 279) `#define AUTO_VALUE`
  - `AUTO_RESET` (macro, line 280) `#define AUTO_RESET`
  - `AUTO_RESET_NONE` (macro, line 281) `#define AUTO_RESET_NONE`
  - `CSS_ATTR_MARK` (macro, line 1962) `#define CSS_ATTR_MARK`
  - `CSS_ATTR_SEP` (macro, line 1963) `#define CSS_ATTR_SEP`
  - `CSS_MEDIA_MAX_DEPTH` (macro, line 5276) `#define CSS_MEDIA_MAX_DEPTH`
  - `CSS_VAR_POOL` (macro, line 6629) `#define CSS_VAR_POOL`
- Depends on: `include/css.h`, `include/css_atrule.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_gradient.h`, `include/css_index.h`, `include/css_length.h`, `include/css_mask.h`, `include/css_mq.h`, `include/css_select.h`, `include/css_text.h`, `include/css_values.h`, `include/css_vars.h`, `include/flex_layout.h`, `include/interp.h`, `include/webfont.h`

## src/css_atrule.c
- Doc: keyword_at: Scratch size for one declaration or selector handed to the caller.
- Layer: utility
- Language: c
- Symbols:
  - `skip_ws` (function, line 17) `static size_t skip_ws(const char *s, size_t i, size_t b)`
  - `keyword_at` (function, line 23) `static int keyword_at(const char *s, size_t i, size_t b, const char *kw)`
  - `close_paren` (function, line 33) `static size_t close_paren(const char *s, size_t open, size_t b)`
  - `copy_trimmed` (function, line 54) `static int copy_trimmed(const char *s, size_t a, size_t b, char *dst, size_t cap, int lower)`
  - `eval_declaration` (function, line 68) `static int eval_declaration(const char *s, size_t a, size_t b, const car_ops *ops, int *ok)`
  - `eval_in_parens` (function, line 85) `static int eval_in_parens(const char *s, size_t *i, size_t b, const car_ops *ops,
               ...`
  - `eval_condition` (function, line 114) `static int eval_condition(const char *s, size_t a, size_t b, const car_ops *ops,
                ...`
  - `car_supports` (function, line 141) `int car_supports(const char *s, size_t a, size_t b, const car_ops *ops)`
  - `car_layer_rank` (function, line 148) `int car_layer_rank(car_layers *L, const char *name, size_t len)`
  - `car_effective_spec` (function, line 171) `int car_effective_spec(int spec, int layer, int important)`
  - `CAR_TEXT_MAX` (macro, line 13) `#define CAR_TEXT_MAX`
- Depends on: `include/css_atrule.h`, `include/css_select.h`

## src/css_box.c
- Doc: calc_val: bare0: the token was a unitless 0.
- Layer: utility
- Language: c
- Symbols:
  - `calc_val` (struct, line 711)
  - `calc_parser` (struct, line 712)
  - `px` (type_alias, line 711) `typedef struct calc_val { double px;`
  - `cb_parse_num` (function, line 13) `static int cb_parse_num(const char *s, double *out, const char **endp)`
  - `cb_wide_keyword` (function, line 18) `static int cb_wide_keyword(const char *v)`
  - `cb_copy_trim` (function, line 25) `static size_t cb_copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)`
  - `cb_length_px` (function, line 49) `int cb_length_px(const char *v, double *px)`
  - `cb_interp_align` (function, line 54) `int cb_interp_align(const char *v)`
  - `cb_interp_fontsize_ex` (function, line 72) `int cb_interp_fontsize_ex(const char *v, int *abs_out)`
  - `cb_interp_lineheight` (function, line 145) `int cb_interp_lineheight(const char *v)`
  - `cb_interp_weight` (function, line 174) `int cb_interp_weight(const char *v)`
  - `cb_interp_style` (function, line 183) `int cb_interp_style(const char *v)`
  - `cb_interp_textdeco` (function, line 193) `int cb_interp_textdeco(const char *v)`
  - `cb_interp_display` (function, line 213) `int cb_interp_display(const char *v)`
  - `cb_interp_gap` (function, line 288) `int cb_interp_gap(const char *v)`
  - `cb_interp_justify` (function, line 295) `int cb_interp_justify(const char *v)`
  - `cb_starts_with_ci` (function, line 327) `static int cb_starts_with_ci(const char *s, const char *pre)`
  - `count_tracks` (function, line 333) `static int count_tracks(const char *s, size_t n)`
  - `track_size_of` (function, line 341) `static int track_size_of(const char *tok)`
  - `count_one_repeat` (function, line 371) `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,
                      ...`
  - `walk_tracks` (function, line 414) `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)`
  - `track_min_of` (function, line 482) `static int track_min_of(const char *tok)`
  - `expand_auto_fill` (function, line 520) `static int expand_auto_fill(const char *val, css_decl *dst, int cap)`
  - `cb_expand_grid_template_cols` (function, line 598) `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap)`
  - `cb_expand_grid_template_rows` (function, line 621) `int cb_expand_grid_template_rows(const char *val, css_decl *dst, int cap)`
  - `calc_skip_ws` (function, line 714) `static void calc_skip_ws(calc_parser *p)`
  - `calc_match_fn` (function, line 721) `static int calc_match_fn(calc_parser *p, const char *name)`
  - `calc_piecewise` (function, line 748) `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)`
  - `calc_mathfn` (function, line 763) `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)`
  - `calc_term` (function, line 886) `static int calc_term(calc_parser *p, calc_val *out, int depth)`
  - `calc_expr` (function, line 913) `static int calc_expr(calc_parser *p, calc_val *out, int depth)`
  - `calc_eval_full` (function, line 935) `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,
           ...`
  - `calc_eval_em` (function, line 949) `static int calc_eval_em(const char *v, size_t vlen, double *out_em)`
  - `calc_unwrap` (function, line 957) `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)`
  - `cb_interp_len` (function, line 1008) `int cb_interp_len(const char *v, int allow_auto, int *out)`
  - `pct_slot_of` (function, line 1037) `static int pct_slot_of(int slot)`
  - `cb_value_em_milli` (function, line 1087) `int cb_value_em_milli(const char *v)`
  - `cb_clip_inset` (function, line 1107) `int cb_clip_inset(const char *val, int px[4], int pm[4])`
  - `cb_interp_lp` (function, line 1141) `int cb_interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_px, ...`
  - `interp_len` (function, line 1317) `* this file that might hand a token to interp_len (transitively: margin/padding/
 * inset, flex-b...`
  - `cb_expand_box2` (function, line 1388) `int cb_expand_box2(const char *val, int slot_start, int slot_end,
                       int allo...`
  - `RELATIVE` (function, line 63) `* or RELATIVE (of the inherited size). Absolute: px/pt/rem/viewport units and the * absolute keywords. Relative: em...`
  - `repeat` (function, line 316) `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill|...) /...`
  - `accepts` (function, line 681) `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further...`
  - `min` (function, line 782) `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the...`
  - `term` (function, line 1148) `* the same expression and failed closed on the percentage term (its property * may not accept one);`
  - `CSS_CALC_MAX_DEPTH` (macro, line 689) `#define CSS_CALC_MAX_DEPTH`
  - `CSS_MATHFN_MAX_ARGS` (macro, line 693) `#define CSS_MATHFN_MAX_ARGS`
  - `AUTO_REJECT` (macro, line 1214) `#define AUTO_REJECT`
  - `AUTO_VALUE` (macro, line 1215) `#define AUTO_VALUE`
  - `AUTO_RESET` (macro, line 1216) `#define AUTO_RESET`
  - `AUTO_RESET_NONE` (macro, line 1220) `#define AUTO_RESET_NONE`
- Depends on: `include/css.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`

## src/css_chain.c
- Doc: cch_node: One element's selector inputs (tag/id/classes) plus its css_element view, with *...
- Layer: utility
- Language: c
- Symbols:
  - `cch_node` (struct, line 27)
  - `cch_path` (struct, line 347)
  - `tag` (type_alias, line 27) `typedef struct cch_node { char tag[CCH_TAG_MAX];`
  - `cls_space` (function, line 42) `static int cls_space(char c)`
  - `release_nodes` (function, line 90) `static void release_nodes(cch_node *nodes, int n)`
  - `fill_css_node` (function, line 99) `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)`
  - `sibling_position` (function, line 181) `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)`
  - `sibling_type_position` (function, line 199) `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)`
  - `count_children` (function, line 227) `static int count_children(lxb_dom_node_t *n)`
  - `inputs` (function, line 241) `* identical inputs (single source of truth). */
static const css_element *build_chain(lxb_dom_ele...`
  - `cch_element_style_vars` (function, line 310) `css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,
                 ...`
  - `cch_path_new` (function, line 353) `cch_path *cch_path_new(void)`
  - `path_truncate` (function, line 357) `static void path_truncate(cch_path *pa, int keep)`
  - `cch_path_free` (function, line 365) `void cch_path_free(cch_path *pa)`
  - `cch_element_style_path` (function, line 372) `css_style cch_element_style_path(cch_path *pa, lxb_dom_element_t *el, const css_sheet *sheet,
   ...`
  - `cch_pseudo_style` (function, line 439) `css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,
            ...`
  - `cch_element_style` (function, line 458) `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)`
  - `cch_element_matches` (function, line 462) `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)`
  - `cch_element_matches_any` (function, line 476) `int cch_element_matches_any(lxb_dom_element_t *el, const css_sel *sels, size_t n)`
  - `CCH_TAG_MAX` (macro, line 15) `#define CCH_TAG_MAX`
  - `CCH_ID_MAX` (macro, line 16) `#define CCH_ID_MAX`
  - `CCH_CLASS_BUF` (macro, line 17) `#define CCH_CLASS_BUF`
  - `CCH_MAX_CLASSES` (macro, line 18) `#define CCH_MAX_CLASSES`
  - `CCH_CLASS_SPILL_MAX` (macro, line 21) `#define CCH_CLASS_SPILL_MAX`
  - `CCH_MAX_ATTRS` (macro, line 22) `#define CCH_MAX_ATTRS`
  - `CCH_ATTR_BUF` (macro, line 23) `#define CCH_ATTR_BUF`
- Depends on: `include/css_chain.h`, `include/css_select.h`

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
  - `parse_named` (function, line 687) `static int parse_named(const char *s, cc_rgb *out)`
  - `cc_parse` (function, line 697) `cc_status cc_parse(const char *token, cc_rgb *out)`
  - `strncmp` (function, line 712) `strncmp(buf, "oklab(", 6) == 0 || strncmp(buf, "oklch(", 6) == 0)`
  - `cc_pack` (function, line 737) `int cc_pack(cc_rgb c)`
  - `cc_unpack` (function, line 741) `cc_rgb cc_unpack(int packed)`
  - `CC_TOKEN_MAX` (macro, line 20) `#define CC_TOKEN_MAX`
  - `CC_CHANNEL_MAX` (macro, line 23) `#define CC_CHANNEL_MAX`
  - `CC_PERCENT_MAX` (macro, line 24) `#define CC_PERCENT_MAX`
  - `CC_NUMBER_MAX_DIGITS` (macro, line 29) `#define CC_NUMBER_MAX_DIGITS`
  - `CC_HSL_SCALE` (macro, line 32) `#define CC_HSL_SCALE`
  - `CC_CALC_DEPTH` (macro, line 221) `#define CC_CALC_DEPTH`
  - `CC_PI` (macro, line 577) `#define CC_PI`
- Depends on: `include/css_color.h`


Next: [KB_src_p3.md](KB_src_p3.md)
