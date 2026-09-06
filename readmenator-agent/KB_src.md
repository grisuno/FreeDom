# Subsystem: src

## src/anti_fp.c
- Layer: utility
- Language: c
- Symbols:
  - `fp_coarsen_time_ms` (function, line 16) `uint64_t fp_coarsen_time_ms(uint64_t raw_ms)`
  - `fp_user_agent` (function, line 22) `const char *fp_user_agent(void)`
  - `fp_accept_language` (function, line 26) `const char *fp_accept_language(void)`
  - `fp_accept_language_header` (function, line 30) `const char *fp_accept_language_header(void)`
  - `fp_timezone` (function, line 34) `const char *fp_timezone(void)`
  - `fp_platform` (function, line 38) `const char *fp_platform(void)`
  - `fp_vendor` (function, line 42) `const char *fp_vendor(void)`
  - `fp_hardware_concurrency` (function, line 46) `int fp_hardware_concurrency(void)`
  - `fp_device_memory_gb` (function, line 50) `int fp_device_memory_gb(void)`
  - `fp_app_version` (function, line 56) `const char *fp_app_version(void)`
  - `fp_app_code_name` (function, line 60) `const char *fp_app_code_name(void)`
  - `fp_product` (function, line 64) `const char *fp_product(void)`
  - `fp_app_name` (function, line 68) `const char *fp_app_name(void)`
  - `fp_product_sub` (function, line 72) `const char *fp_product_sub(void)`
  - `fp_oscpu` (function, line 76) `const char *fp_oscpu(void)`
  - `fp_build_id` (function, line 80) `const char *fp_build_id(void)`
  - `fp_max_touch_points` (function, line 84) `int fp_max_touch_points(void)`
  - `fp_on_line` (function, line 88) `int fp_on_line(void)`
  - `fp_cookie_enabled` (function, line 92) `int fp_cookie_enabled(void)`
  - `fp_bucket_screen` (function, line 98) `void fp_bucket_screen(int w, int h, int *out_w, int *out_h)`
  - `splitmix64` (function, line 120) `static uint64_t splitmix64(uint64_t *state)`
  - `fp_perturb` (function, line 127) `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key)`
  - `fp_origin_key` (function, line 138) `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain)`

## src/block_flow.c
- Layer: utility
- Doc: block_flow (bf_) -- vertical margin collapsing. See spec/block_flow.md.
- Language: c
- Symbols:
  - `finite_or_zero` (function, line 11) `static double finite_or_zero(double v)`
  - `bf_collapse_n` (function, line 14) `double bf_collapse_n(const double *m, size_t n)`
  - `bf_collapse` (function, line 29) `double bf_collapse(double a, double b)`
  - `bf_margins_adjoin` (function, line 34) `int bf_margins_adjoin(double border_px, double padding_px)`

## src/box_style.c
- Layer: utility
- Language: c
- Symbols:
  - `tag_row` (struct, line 59)
  - `disp_row` (struct, line 239)
  - `is_ws` (function, line 28) `static int is_ws(char c)`
  - `copy_lower_trim` (function, line 35) `static int copy_lower_trim(const char *in, char *out, size_t out_size)`
  - `name_cmp` (function, line 48) `static int name_cmp(const void *key, const void *elem)`
  - `bx_default_for_tag` (function, line 160) `bx_box bx_default_for_tag(const char *tag)`
  - `bx_table_role_of` (function, line 168) `bx_table_role bx_table_role_of(const char *tag, css_display display)`
  - `bx_ua_of_tag` (function, line 207) `bx_ua_tag bx_ua_of_tag(const char *tag)`
  - `bx_default_for_ua` (function, line 216) `bx_box bx_default_for_ua(bx_ua_tag id)`
  - `bx_block_ua_box` (function, line 222) `bx_box bx_block_ua_box(int heading_level, int in_list, bx_ua_tag ua)`
  - `bx_parse_display` (function, line 258) `bx_status bx_parse_display(const char *token, bx_display *out)`
  - `bx_place` (function, line 268) `bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,
                ...`
  - `bx_width_cap` (function, line 285) `double bx_width_cap(int w_px, int w_pct, double avail_w)`
  - `bx_replaced_box` (function, line 309) `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den,
                    doub...`
  - `bx_border_box_h` (function, line 324) `double bx_border_box_h(double declared_h, int border_box,
                       double pad_t, do...`
  - `bx_lp_px` (function, line 335) `double bx_lp_px(int px_val, int pct_pm, double basis)`
  - `bx_content_cap` (function, line 346) `double bx_content_cap(double width_cap, int border_box,
                      double pad_l, doubl...`
  - `bg_size_component` (function, line 361) `static double bg_size_component(int px_val, int pct_pm, double area)`
  - `bx_background_layer` (function, line 367) `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h,
                    ...`
  - `bx_display_name` (function, line 406) `const char *bx_display_name(bx_display d)`
  - `BX_TAG_MAX` (macro, line 22)
  - `BX_DISPLAY_MAX` (macro, line 23)
  - `BLOCK` (macro, line 64)
  - `INLINE` (macro, line 66)
  - `IBLOCK` (macro, line 67)
  - `LITEM` (macro, line 68)
  - `NONE` (macro, line 69)
  - `EDG` (macro, line 70)
  - `ZERO` (macro, line 71)
  - `T_NO` (macro, line 73)
  - `T_TBL` (macro, line 74)
  - `T_GRP` (macro, line 75)
  - `T_ROW` (macro, line 76)
  - `T_CELL` (macro, line 77)
  - `T_CAP` (macro, line 78)
  - `T_COL` (macro, line 79)
  - `TAG_N` (macro, line 159)
  - `DISP_N` (macro, line 257)

## src/box_tree.c
- Layer: utility
- Language: c
- Symbols:
  - `layout_block` (function, line 37) `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,
                   ...`
  - `bt_nn` (function, line 58) `static double bt_nn(double v)`
  - `wrap_reverse` (function, line 78) `*
 * wrap_reverse (node->wrap_reverse): when node->wrap is active and node->wrap_reverse
 * is no...`
  - `layout_grid` (function, line 201) `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,
                    ...`
  - `layout_node` (function, line 307) `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)`
  - `bt_layout` (function, line 352) `bt_status bt_layout(bt_node *root, double avail_w)`
  - `assign_doc_order` (function, line 393) `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,
                  ...`
  - `find_positioned_ancestor` (function, line 410) `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,
                       ...`
  - `resolve_inset` (function, line 430) `static double resolve_inset(int v, int pct_pm, double basis)`
  - `inset_unset` (function, line 439) `static int inset_unset(int v, int pct_pm)`
  - `bt_resolve_positioning` (function, line 442) `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,
                          ...`
  - `bt_resolve_positioning_ex` (function, line 453) `bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,
                       ...`
  - `oof_walk` (function, line 620) `static int oof_walk(const pv_box_def *boxes, size_t nbox, int bid, int nearest)`
  - `bt_oof_anchor` (function, line 636) `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)`
  - `bt_oof_root` (function, line 640) `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)`
  - `bt_box_hidden` (function, line 644) `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)`
  - `BT_LEN_AUTO` (macro, line 31)
  - `BT_WRAP_EPS` (macro, line 61)

## src/browser.c
- Layer: utility
- Language: c
- Symbols:
  - `free_page` (function, line 14) `static void free_page(browser_state *bs)`
  - `clear_status` (function, line 25) `static void clear_status(browser_state *bs)`
  - `free_history` (function, line 29) `static void free_history(browser_state *bs)`
  - `free_exceptions` (function, line 39) `static void free_exceptions(browser_state *bs)`
  - `is_https_url` (function, line 48) `static int is_https_url(const char *s)`
  - `is_local_path` (function, line 52) `static int is_local_path(const char *s)`
  - `url_is_allowed` (function, line 57) `static int url_is_allowed(const char *url)`
  - `xstrdup` (function, line 71) `static char *xstrdup(const char *s)`
  - `cp1252_to_ucs` (function, line 86) `static unsigned int cp1252_to_ucs(unsigned char c)`
  - `utf8_encode` (function, line 100) `static size_t utf8_encode(unsigned int cp, char *out)`
  - `browser_init` (function, line 153) `browser_status browser_init(browser_state *bs)`
  - `browser_free` (function, line 164) `void browser_free(browser_state *bs)`
  - `browser_set_url_bar` (function, line 175) `browser_status browser_set_url_bar(browser_state *bs, const char *url)`
  - `browser_commit_url_bar` (function, line 187) `browser_status browser_commit_url_bar(browser_state *bs)`
  - `browser_navigate` (function, line 192) `browser_status browser_navigate(browser_state *bs, const char *url)`
  - `browser_back` (function, line 227) `browser_status browser_back(browser_state *bs)`
  - `browser_forward` (function, line 239) `browser_status browser_forward(browser_state *bs)`
  - `browser_can_back` (function, line 251) `int browser_can_back(const browser_state *bs)`
  - `browser_can_forward` (function, line 255) `int browser_can_forward(const browser_state *bs)`
  - `browser_current_url` (function, line 259) `const char *browser_current_url(const browser_state *bs)`
  - `browser_url_bar_selection` (function, line 264) `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)`
  - `browser_url_bar_delete_selection` (function, line 275) `int browser_url_bar_delete_selection(browser_state *bs)`
  - `browser_url_bar_insert` (function, line 285) `browser_status browser_url_bar_insert(browser_state *bs, char c)`
  - `browser_url_bar_backspace` (function, line 300) `browser_status browser_url_bar_backspace(browser_state *bs)`
  - `browser_url_bar_delete` (function, line 314) `browser_status browser_url_bar_delete(browser_state *bs)`
  - `browser_url_bar_move_cursor` (function, line 325) `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)`
  - `browser_url_bar_extend_cursor` (function, line 335) `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)`
  - `browser_url_bar_set_cursor` (function, line 344) `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)`
  - `browser_url_bar_select_all` (function, line 352) `browser_status browser_url_bar_select_all(browser_state *bs)`
  - `browser_url_bar_clear` (function, line 359) `browser_status browser_url_bar_clear(browser_state *bs)`
  - `browser_set_page` (function, line 368) `browser_status browser_set_page(browser_state *bs, const char *title,
                           ...`
  - `browser_set_status` (function, line 390) `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)`
  - `browser_status_text` (function, line 404) `const char *browser_status_text(const browser_state *bs, uint64_t now_ms)`
  - `host_equal` (function, line 412) `static int host_equal(const char *a, const char *b)`
  - `browser_is_exception` (function, line 423) `int browser_is_exception(const browser_state *bs, const char *host)`
  - `browser_add_exception` (function, line 431) `browser_status browser_add_exception(browser_state *bs, const char *host)`
  - `_POSIX_C_SOURCE` (macro, line 6)

## src/compositor.c
- Layer: utility
- Language: c
- Symbols:
  - `cx_forms_stacking_context` (function, line 15) `int cx_forms_stacking_context(const cx_style *s)`
  - `cx_box_layer` (function, line 33) `cx_layer cx_box_layer(const cx_style *s)`
  - `eff_z` (function, line 50) `static int eff_z(const cx_item *it)`
  - `cx_item_compare` (function, line 53) `int cx_item_compare(const cx_item *a, const cx_item *b)`
  - `cx_sort` (function, line 70) `void cx_sort(cx_item *items, size_t n)`

## src/css.c
- Layer: utility
- Language: c
- Symbols:
  - `css_decl` (struct, line 234)
  - `css_custom_prop` (struct, line 272)
  - `css_sheet` (struct, line 282)
  - `css_keyframe_stop` (struct, line 304)
  - `calc_val` (struct, line 1396)
  - `calc_parser` (struct, line 1397)
  - `parse_num` (function, line 335) `static int parse_num(const char *s, double *out, const char **endp)`
  - `round_clamp` (function, line 347) `static int round_clamp(double v, int lo, int hi)`
  - `parse_color` (function, line 356) `static int parse_color(const char *v)`
  - `interp_color` (function, line 364) `static int interp_color(const char *v)`
  - `through` (function, line 381) `* at the two SHARED chokepoints every property funnels through (the generic
 * dispatch tail, and...`
  - `bg_alpha_of` (function, line 401) `static int bg_alpha_of(const char *v)`
  - `interp_bg` (function, line 429) `static int interp_bg(const char *v)`
  - `gradient` (function, line 461) `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,
 * the whole decl...`
  - `find_gradient_call` (function, line 510) `static int find_gradient_call(const char *v, const char *fn, size_t *start,
                     ...`
  - `conic_prelude` (function, line 544) `static int conic_prelude(const char *seg, int *angle)`
  - `grad_stop_pos` (function, line 586) `static int grad_stop_pos(const char *pp, int conic, const char **endp)`
  - `CSS_GRAD_STOPS_MAX` (function, line 617) `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when
 * the gradient fai...`
  - `emit_gradient` (function, line 709) `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,
                         ...`
  - `find_radial_gradient` (function, line 766) `static int find_radial_gradient(const char *v, size_t *start, size_t *end,
                      ...`
  - `downstream` (function, line 811) `* happens downstream (render_doc.c), gated by caps.images like an <img>. */
static int expand_bg_...`
  - `expand_background` (function, line 872) `static int expand_background(const char *val, css_decl *dst, int cap,
                           ...`
  - `text` (function, line 957) `* source text (rem_rebase, see below) rather than by threading a context here.
 *
 * Viewport uni...`
  - `length_px` (function, line 971) `static int length_px(const char *v, double *px)`
  - `interp_align` (function, line 975) `static int interp_align(const char *v)`
  - `interp_lineheight` (function, line 1038) `static int interp_lineheight(const char *v)`
  - `interp_weight` (function, line 1058) `static int interp_weight(const char *v)`
  - `interp_style` (function, line 1067) `static int interp_style(const char *v)`
  - `interp_textdeco` (function, line 1078) `static int interp_textdeco(const char *v)`
  - `interp_display` (function, line 1097) `static int interp_display(const char *v)`
  - `interp_gap` (function, line 1173) `static int interp_gap(const char *v)`
  - `interp_justify` (function, line 1179) `static int interp_justify(const char *v)`
  - `count_tracks` (function, line 1205) `static int count_tracks(const char *s, size_t n)`
  - `track_size_of` (function, line 1214) `static int track_size_of(const char *tok)`
  - `count_one_repeat` (function, line 1243) `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,
                      ...`
  - `walk_tracks` (function, line 1286) `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)`
  - `expand_grid_template_cols` (function, line 1347) `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)`
  - `calc_skip_ws` (function, line 1398) `static void calc_skip_ws(calc_parser *p)`
  - `calc_match_fn` (function, line 1406) `static int calc_match_fn(calc_parser *p, const char *name)`
  - `calc_piecewise` (function, line 1433) `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)`
  - `calc_mathfn` (function, line 1448) `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)`
  - `calc_term` (function, line 1569) `static int calc_term(calc_parser *p, calc_val *out, int depth)`
  - `calc_expr` (function, line 1592) `static int calc_expr(calc_parser *p, calc_val *out, int depth)`
  - `calc_eval_full` (function, line 1612) `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,
           ...`
  - `calc_eval` (function, line 1628) `static int calc_eval(const char *v, size_t vlen, double *out_px)`
  - `calc_eval_em` (function, line 1635) `static int calc_eval_em(const char *v, size_t vlen, double *out_em)`
  - `calc_unwrap` (function, line 1643) `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)`
  - `interp_len` (function, line 1661) `static int interp_len(const char *v, int allow_auto, int *out)`
  - `pct_slot_of` (function, line 1706) `static int pct_slot_of(int slot)`
  - `value_em_milli` (function, line 1756) `static int value_em_milli(const char *v)`
  - `interp_lp` (function, line 1775) `static int interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_...`
  - `interp_len` (function, line 1952) `* this file that might hand a token to interp_len (transitively: margin/padding/
 * inset, flex-b...`
  - `expand_box2` (function, line 2019) `static int expand_box2(const char *val, int slot_start, int slot_end,
                       int ...`
  - `family_of` (function, line 2049) `static int family_of(const char *name)`
  - `interp_fontfamily` (function, line 2078) `static int interp_fontfamily(const char *v)`
  - `interp_texttransform` (function, line 2099) `static int interp_texttransform(const char *v)`
  - `interp_valign` (function, line 2121) `static int interp_valign(const char *v)`
  - `expand_valign` (function, line 2153) `static int expand_valign(const char *val, css_decl *dst, int cap)`
  - `interp_transition_property` (function, line 2170) `static int interp_transition_property(const char *v)`
  - `interp_whitespace` (function, line 2177) `static int interp_whitespace(const char *v)`
  - `interp_tabsize` (function, line 2191) `static int interp_tabsize(const char *v)`
  - `interp_textdeco_style` (function, line 2202) `static int interp_textdeco_style(const char *v)`
  - `interp_textdeco_thickness` (function, line 2213) `static int interp_textdeco_thickness(const char *v)`
  - `interp_aspect_ratio` (function, line 2225) `static int interp_aspect_ratio(const char *v, int *num, int *den)`
  - `interp_direction` (function, line 2258) `static int interp_direction(const char *v)`
  - `liststyle_kw` (function, line 2263) `static int liststyle_kw(const char *t)`
  - `liststyle_unknown_name` (function, line 2285) `static int liststyle_unknown_name(const char *t)`
  - `interp_liststyle` (function, line 2296) `static int interp_liststyle(const char *v)`
  - `emit_spacing` (function, line 2330) `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
  - `expand_shadow` (function, line 2344) `static int expand_shadow(const char *val, css_decl *dst, int cap)`
  - `interp_position` (function, line 2374) `static int interp_position(const char *v)`
  - `interp_boxsizing` (function, line 2383) `static int interp_boxsizing(const char *v)`
  - `interp_float` (function, line 2389) `static int interp_float(const char *v)`
  - `interp_clear` (function, line 2396) `static int interp_clear(const char *v)`
  - `interp_visibility` (function, line 2406) `static int interp_visibility(const char *v)`
  - `interp_overflow` (function, line 2413) `static int interp_overflow(const char *v)`
  - `interp_cursor` (function, line 2445) `static int interp_cursor(const char *v)`
  - `interp_text_overflow` (function, line 2461) `static int interp_text_overflow(const char *v)`
  - `interp_word_break` (function, line 2467) `static int interp_word_break(const char *v)`
  - `interp_overflow_wrap` (function, line 2475) `static int interp_overflow_wrap(const char *v)`
  - `interp_border_collapse` (function, line 2484) `static int interp_border_collapse(const char *v)`
  - `number` (function, line 2493) `* number (no unit) as px (common in shorthand context like "10 5"). */
static int interp_border_s...`
  - `interp_empty_cells` (function, line 2518) `static int interp_empty_cells(const char *v)`
  - `interp_caption_side` (function, line 2525) `static int interp_caption_side(const char *v)`
  - `interp_table_layout` (function, line 2532) `static int interp_table_layout(const char *v)`
  - `interp_font_variant` (function, line 2539) `static int interp_font_variant(const char *v)`
  - `interp_hyphens` (function, line 2547) `static int interp_hyphens(const char *v)`
  - `interp_user_select` (function, line 2555) `static int interp_user_select(const char *v)`
  - `interp_caret_color` (function, line 2564) `static int interp_caret_color(const char *v)`
  - `interp_appearance` (function, line 2576) `static int interp_appearance(const char *v)`
  - `interp_pointer_events` (function, line 2594) `static int interp_pointer_events(const char *v)`
  - `interp_bg_repeat` (function, line 2606) `static int interp_bg_repeat(const char *v)`
  - `interp_bg_size` (function, line 2616) `static int interp_bg_size(const char *v)`
  - `interp_bg_clip` (function, line 2623) `static int interp_bg_clip(const char *v)`
  - `interp_bg_origin` (function, line 2631) `static int interp_bg_origin(const char *v)`
  - `interp_bg_attachment` (function, line 2638) `static int interp_bg_attachment(const char *v)`
  - `interp_isolation` (function, line 2645) `static int interp_isolation(const char *v)`
  - `interp_contain` (function, line 2651) `static int interp_contain(const char *v)`
  - `interp_content_visibility` (function, line 2672) `static int interp_content_visibility(const char *v)`
  - `interp_image_rendering` (function, line 2679) `static int interp_image_rendering(const char *v)`
  - `interp_color_scheme` (function, line 2686) `static int interp_color_scheme(const char *v)`
  - `interp_accent_color` (function, line 2704) `static int interp_accent_color(const char *v)`
  - `interp_print_color_adjust` (function, line 2709) `static int interp_print_color_adjust(const char *v)`
  - `interp_forced_color_adjust` (function, line 2715) `static int interp_forced_color_adjust(const char *v)`
  - `interp_mix_blend_mode` (function, line 2722) `static int interp_mix_blend_mode(const char *v)`
  - `interp_object_fit` (function, line 2740) `static int interp_object_fit(const char *v)`
  - `interp_list_style_pos` (function, line 2749) `static int interp_list_style_pos(const char *v)`
  - `interp_font_kerning` (function, line 2755) `static int interp_font_kerning(const char *v)`
  - `interp_text_rendering` (function, line 2762) `static int interp_text_rendering(const char *v)`
  - `interp_font_stretch` (function, line 2770) `static int interp_font_stretch(const char *v)`
  - `interp_resize` (function, line 2783) `static int interp_resize(const char *v)`
  - `interp_scroll_behavior` (function, line 2791) `static int interp_scroll_behavior(const char *v)`
  - `interp_touch_action` (function, line 2797) `static int interp_touch_action(const char *v)`
  - `interp_overscroll_behavior` (function, line 2804) `static int interp_overscroll_behavior(const char *v)`
  - `interp_backface_visibility` (function, line 2811) `static int interp_backface_visibility(const char *v)`
  - `interp_border_style` (function, line 2833) `static int interp_border_style(const char *v)`
  - `interp_bwidth1` (function, line 2859) `static int interp_bwidth1(const char *v)`
  - `interp_time_ms` (function, line 2869) `static int interp_time_ms(const char *v)`
  - `emit_radius_corner` (function, line 2902) `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)`
  - `interp_bw_tok` (function, line 2910) `static int interp_bw_tok(const char *t, int *o)`
  - `interp_bs_tok` (function, line 2911) `static int interp_bs_tok(const char *t, int *o)`
  - `interp_bc_tok` (function, line 2912) `static int interp_bc_tok(const char *t, int *o)`
  - `expand_outline` (function, line 2976) `static int expand_outline(const char *val, css_decl *dst, int cap)`
  - `interp_column_count` (function, line 2993) `static int interp_column_count(const char *v)`
  - `interp_column_width` (function, line 3005) `static int interp_column_width(const char *v)`
  - `expand_columns` (function, line 3016) `static int expand_columns(const char *val, css_decl *dst, int cap)`
  - `expand_flex_flow` (function, line 3050) `static int expand_flex_flow(const char *val, css_decl *dst, int cap)`
  - `expand_column_rule` (function, line 3072) `static int expand_column_rule(const char *val, css_decl *dst, int cap)`
  - `interp_filter_pct` (function, line 3084) `static int interp_filter_pct(const char *s)`
  - `interp_filter_deg` (function, line 3098) `static int interp_filter_deg(const char *s)`
  - `filter_paren_body` (function, line 3113) `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)`
  - `expand_backdrop_filter` (function, line 3276) `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)`
  - `expand_bg_position` (function, line 3309) `static int expand_bg_position(const char *val, css_decl *dst, int cap)`
  - `expand_bg_size` (function, line 3369) `static int expand_bg_size(const char *val, css_decl *dst, int cap)`
  - `emit_content` (function, line 3408) `static int emit_content(css_decl *dst, int cap, const char *str,
                        char (*c...`
  - `expand_content` (function, line 3421) `static int expand_content(const char *val, css_decl *dst, int cap,
                          char...`
  - `expand_grid_areas` (function, line 3453) `static int expand_grid_areas(const char *val, css_decl *dst, int cap,
                           ...`
  - `expand_grid_template` (function, line 3520) `static int expand_grid_template(const char *val, css_decl *dst, int cap,
                        ...`
  - `expand_box_shadow` (function, line 3571) `static int expand_box_shadow(const char *val, css_decl *dst, int cap)`
  - `interp_flex_factor` (function, line 3599) `static int interp_flex_factor(const char *v)`
  - `interp_flex_basis` (function, line 3609) `static int interp_flex_basis(const char *v, int *out)`
  - `expand_flex` (function, line 3643) `static int expand_flex(const char *val, css_decl *dst, int cap)`
  - `interp_align_kw` (function, line 3688) `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)`
  - `interp_flex_direction` (function, line 3700) `static int interp_flex_direction(const char *v)`
  - `interp_flex_wrap` (function, line 3708) `static int interp_flex_wrap(const char *v)`
  - `interp_grid_flow` (function, line 3717) `static int interp_grid_flow(const char *v)`
  - `interp_grid_span` (function, line 3743) `static int interp_grid_span(const char *v)`
  - `copy_trim` (function, line 3762) `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)`
  - `strip_important` (function, line 3775) `static int strip_important(char *val)`
  - `scope_has_class` (function, line 3855) `static int scope_has_class(const char *list, const char *name, size_t len)`
  - `var_append` (function, line 3924) `static int var_append(char *out, size_t outcap, size_t *o, const char *s, size_t n)`
  - `value` (function, line 3951) `* any other unsupported value (fail closed, never a partially-substituted value). */
static int r...`
  - `overflowed` (function, line 4011) `* overflowed (caller drops the declaration). */
static int resolve_var(const char *val, char *out...`
  - `parse_rotate_deg` (function, line 4045) `static int parse_rotate_deg(const char *s, int *out)`
  - `function` (function, line 4062) `* function (perspective/3D), multiple space-separated functions, or
 * unparseable syntax reject ...`
  - `origin_component` (function, line 4271) `static int origin_component(const char *tok, int axis, int *out)`
  - `expand_transform_origin` (function, line 4291) `static int expand_transform_origin(const char *val, css_decl *dst, int cap)`
  - `expand_gap` (function, line 4323) `static int expand_gap(const char *val, css_decl *dst, int cap)`
  - `ignored` (function, line 4342) `* engine slot and is ignored (documented simplification, like list-style's
 * ignored tokens). An...`
  - `property` (function, line 4377) `* error drops the whole property (fail closed). */
static int expand_clip(const char *val, css_de...`
  - `shorthand` (function, line 4420) `* generic bucket keeps the rest of the shorthand (same net effect as the
 * font-family longhand ...`
  - `interpret_prop_dispatch` (function, line 4490) `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,
   ...`
  - `grammar` (function, line 4509) `* grammar (`justify`/`distribute`) is not `justify-content`'s. Guessing
     * there would be inv...`
  - `wide_claim` (function, line 5037) `static int wide_claim(const char *prop, css_decl *dst, int cap,
                      char (*urlt...`
  - `interpret_prop` (function, line 5077) `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,
            ...`
  - `drop_copy_text` (function, line 5104) `static void drop_copy_text(char *dst, size_t cap, const char *src)`
  - `drop_record` (function, line 5123) `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)`
  - `interpret_decls` (function, line 5201) `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,
               ...`
  - `add_rule` (function, line 5219) `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,
                     siz...`
  - `skip_at_rule` (function, line 5304) `static size_t skip_at_rule(const char *s, size_t i, size_t n)`
  - `block_end` (function, line 5320) `static size_t block_end(const char *s, size_t open, size_t n)`
  - `trim_inplace` (function, line 5356) `static void trim_inplace(char *s)`
  - `copy_lower_trim` (function, line 5365) `static size_t copy_lower_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)`
  - `media_part_matches` (function, line 5374) `static int media_part_matches(const char *p, const css_media *m)`
  - `media_segment_matches` (function, line 5403) `static int media_segment_matches(const char *s, size_t a, size_t b, const css_media *m)`
  - `media_matches` (function, line 5440) `static int media_matches(const char *s, size_t a, size_t b, const css_media *m)`
  - `at_is_media` (function, line 5454) `static int at_is_media(const char *s, size_t i, size_t n)`
  - `collect_custom_props_scoped` (function, line 5472) `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,
                ...`
  - `parse_block` (function, line 5528) `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                 ...`
  - `rem_ident_ch` (function, line 5734) `static int rem_ident_ch(char c)`
  - `rem_num_starts_after` (function, line 5742) `static int rem_num_starts_after(char prev)`
  - `rem_emit_px` (function, line 5752) `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)`
  - `rem_rebase` (function, line 5782) `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)`
  - `sheet_rewind` (function, line 5849) `static void sheet_rewind(css_sheet *sh)`
  - `sheet_root_font_px` (function, line 5889) `static double sheet_root_font_px(const css_sheet *sh)`
  - `strip_comments` (function, line 5897) `static char *strip_comments(const char *text, size_t len, size_t *outlen)`
  - `var` (function, line 5907) `* collected and forty var() declarations -- font sizes, widths, radii, the
     * whole theme -- ...`
  - `css_parse` (function, line 5931) `css_status css_parse(const char *text, size_t len, css_sheet **out)`
  - `css_parse_media` (function, line 5935) `css_status css_parse_media(const char *text, size_t len, const css_media *media,
                ...`
  - `css_parse_scoped` (function, line 5940) `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,
               ...`
  - `css_parse_logged` (function, line 5945) `css_status css_parse_logged(const char *text, size_t len, const css_media *media,
               ...`
  - `css_free` (function, line 6015) `void css_free(css_sheet *s)`
  - `apply_decl` (function, line 6029) `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...`
  - `parent` (function, line 6064) `* property from the parent (`inherit`), and an unset non-inherited one
         * stands at its i...`
  - `computed_font_size` (function, line 6382) `static double computed_font_size(const css_style *o, const css_element *el)`
  - `fold_font_relative` (function, line 6403) `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,
                         ...`
  - `css_resolve_el` (function, line 6431) `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         ...`
  - `css_resolve` (function, line 6611) `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                  ...`
  - `NULL` (function, line 6636) `* Sheet can be NULL (inline style, no @keyframes). */
void css_resolve_anim_keyframes(css_style *...`
  - `css_font_face_count` (function, line 6667) `size_t css_font_face_count(const css_sheet *sheet)`
  - `css_font_face_at` (function, line 6671) `int css_font_face_at(const css_sheet *sheet, size_t i,
                     char *family, size_t ...`
  - `css_parse_inline` (function, line 6681) `css_style css_parse_inline(const char *style, size_t len)`
  - `CSS_INIT_SELS` (macro, line 42)
  - `CSS_INIT_DECLS` (macro, line 43)
  - `CSS_DECL_SLOTS_MIN` (macro, line 58)
  - `CSS_INIT_RULES` (macro, line 59)
  - `CSS_SELS_PER_GROUP` (macro, line 60)
  - `CSS_INLINE_DECLS` (macro, line 61)
  - `CSS_INLINE_SPEC` (macro, line 62)
  - `CSS_MAX_CUSTOM_PROPS` (macro, line 73)
  - `CSS_VAR_MAX_DEPTH` (macro, line 74)
  - `CSS_MAX_BG_URLS` (macro, line 83)
  - `CSS_MAX_KEYFRAMES` (macro, line 84)
  - `CSS_MAX_KEYFRAME_STOPS` (macro, line 86)
  - `CSS_MAX_KEYFRAME_DECLS` (macro, line 87)
  - `CSS_INLINE_BG_URLS` (macro, line 88)
  - `CSS_WIDE_PROBE_DECLS` (macro, line 94)
  - `CSS_MAX_FONT_FACES` (macro, line 322)
  - `CSS_CALC_MAX_DEPTH` (macro, line 1377)
  - `CSS_MATHFN_MAX_ARGS` (macro, line 1381)
  - `AUTO_REJECT` (macro, line 1849)
  - `AUTO_VALUE` (macro, line 1850)
  - `AUTO_RESET` (macro, line 1851)
  - `AUTO_RESET_NONE` (macro, line 1855)
  - `CSS_MEDIA_TOK` (macro, line 5331)
  - `CSS_MEDIA_MAX_DEPTH` (macro, line 5462)

## src/css_chain.c
- Layer: utility
- Language: c
- Symbols:
  - `cch_node` (struct, line 23)
  - `fill_css_node` (function, line 35) `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)`
  - `sibling_position` (function, line 133) `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)`
  - `sibling_type_position` (function, line 151) `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)`
  - `count_children` (function, line 179) `static int count_children(lxb_dom_node_t *n)`
  - `inputs` (function, line 193) `* identical inputs (single source of truth). */
static const css_element *build_chain(lxb_dom_ele...`
  - `cch_element_style` (function, line 262) `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)`
  - `cch_element_matches` (function, line 266) `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)`
  - `CCH_TAG_MAX` (macro, line 14)
  - `CCH_ID_MAX` (macro, line 15)
  - `CCH_CLASS_BUF` (macro, line 16)
  - `CCH_MAX_CLASSES` (macro, line 17)
  - `CCH_MAX_ATTRS` (macro, line 18)
  - `CCH_ATTR_BUF` (macro, line 19)

## src/css_color.c
- Layer: utility
- Language: c
- Symbols:
  - `cc_named` (struct, line 32)
  - `ascii_lower` (function, line 116) `static int ascii_lower(int c)`
  - `hex_val` (function, line 120) `static int hex_val(int c)`
  - `normalize` (function, line 130) `static int normalize(const char *token, char *out)`
  - `parse_hex` (function, line 144) `static int parse_hex(const char *s, cc_rgb *out)`
  - `cc_round` (function, line 210) `static long cc_round(double v)`
  - `parse_component` (function, line 215) `static int parse_component(const char *b, const char *e, int is_alpha, int *out)`
  - `parse_hsl_comp` (function, line 248) `static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out)`
  - `parse_func` (function, line 318) `static int parse_func(const char *s, cc_rgb *out)`
  - `named_cmp` (function, line 387) `static int named_cmp(const void *key, const void *element)`
  - `parse_named` (function, line 393) `static int parse_named(const char *s, cc_rgb *out)`
  - `cc_parse` (function, line 403) `cc_status cc_parse(const char *token, cc_rgb *out)`
  - `cc_pack` (function, line 434) `int cc_pack(cc_rgb c)`
  - `cc_unpack` (function, line 438) `cc_rgb cc_unpack(int packed)`
  - `CC_TOKEN_MAX` (macro, line 18)
  - `CC_CHANNEL_MAX` (macro, line 21)
  - `CC_PERCENT_MAX` (macro, line 22)
  - `CC_NUMBER_MAX_DIGITS` (macro, line 27)
  - `CC_HSL_SCALE` (macro, line 30)

## src/css_length.c
- Layer: utility
- Language: c
- Symbols:
  - `know` (function, line 7) `* this module cannot know (real font metrics, the viewport) arrives through
 * cl_ctx rather than...`
  - `cl_unit_eq` (function, line 30) `static int cl_unit_eq(const char *unit, size_t len, const char *lit)`
  - `cl_font_size` (function, line 56) `static double cl_font_size(const cl_ctx *ctx)`
  - `cl_root_font_size` (function, line 59) `static double cl_root_font_size(const cl_ctx *ctx)`
  - `cl_metric_or` (function, line 67) `static double cl_metric_or(double measured, double ratio, const cl_ctx *ctx)`
  - `cl_viewport_scale` (function, line 80) `static int cl_viewport_scale(const char *u, size_t len, const cl_ctx *ctx, double *per)`
  - `cl_ctx_initial` (function, line 99) `cl_ctx cl_ctx_initial(void)`
  - `cl_unit_scale` (function, line 116) `cl_status cl_unit_scale(const char *unit, size_t unit_len,
                        const cl_ctx *...`
  - `cl_is_length_unit` (function, line 166) `int cl_is_length_unit(const char *unit, size_t unit_len)`
  - `cl_unit_is_font_relative` (function, line 173) `int cl_unit_is_font_relative(const char *unit, size_t unit_len)`
  - `cl_em_refit` (function, line 218) `double cl_em_refit(double px, double em, double from_font_size, double font_size)`
  - `cl_parse_number` (function, line 233) `static int cl_parse_number(const char **pp, const char *end, double *out)`
  - `cl_number` (function, line 291) `int cl_number(const char *s, double *out, const char **endp)`
  - `cl_resolve_core` (function, line 309) `static cl_status cl_resolve_core(const char *value, const cl_ctx *ctx, cl_lp *out)`
  - `cl_resolve` (function, line 376) `cl_status cl_resolve(const char *value, const cl_ctx *ctx, double *out_px)`
  - `cl_resolve_lp` (function, line 390) `cl_status cl_resolve_lp(const char *value, const cl_ctx *ctx, cl_lp *out)`
  - `cl_lp_used` (function, line 394) `double cl_lp_used(cl_lp lp, double basis)`
  - `CL_PX_PER_IN` (macro, line 21)

## src/css_select.c
- Layer: utility
- Language: c
- Symbols:
  - `parse_attr_sel` (function, line 19) `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)`
  - `parse_nth_arg` (function, line 76) `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)`
  - `parse_sub_compound` (function, line 270) `static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub)`
  - `parse_compound` (function, line 321) `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,
                  ...`
  - `selector` (function, line 380) `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is
 * dropped. Whitespa...`
  - `el_attr_value` (function, line 474) `static const char *el_attr_value(const css_element *el, const char *name)`
  - `ends_with` (function, line 484) `static int ends_with(const char *v, const char *suf, int ci)`
  - `has_word` (function, line 492) `static int has_word(const char *v, const char *w, int ci)`
  - `attr_matches` (function, line 507) `static int attr_matches(const css_attr_match *am, const css_element *el)`
  - `nth_matches` (function, line 527) `static int nth_matches(int A, int B, int idx)`
  - `is_form_control` (function, line 536) `static int is_form_control(const char *tag)`
  - `sub_sel_matches` (function, line 545) `static int sub_sel_matches(const css_sub_sel *sub, const css_element *el)`
  - `compound_matches` (function, line 787) `static int compound_matches(const css_compound *c, const css_element *el,
                       ...`
  - `built` (function, line 820) `* chains the caller built (an element without parent/prev links never matches
 * through that com...`
  - `csel_matches` (function, line 860) `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,
              ...`
  - `HAS_MAX_DEPTH` (macro, line 646)

## src/data_url.c
- Layer: data_access
- Language: c
- Symbols:
  - `lower` (function, line 15) `static int lower(char c)`
  - `ci_starts_with` (function, line 19) `static int ci_starts_with(const char *s, const char *prefix)`
  - `du_is_data_url` (function, line 27) `int du_is_data_url(const char *url)`
  - `du_base64_payload` (function, line 31) `du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len)`
  - `b64_val` (function, line 61) `static int b64_val(unsigned char c)`
  - `du_base64_decode` (function, line 69) `du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len)`

## src/disk_store.c
- Layer: data_access
- Language: c
- Symbols:
  - `fsync_dir` (function, line 32) `static void fsync_dir(const char *path)`
  - `map_ls` (function, line 49) `static ds_status map_ls(ls_status s)`
  - `ds_write` (function, line 65) `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,
               ...`
  - `ds_read` (function, line 102) `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],
                  uint8_t **ou...`
  - `ds_free` (function, line 135) `void ds_free(uint8_t *buf, size_t len)`
  - `_POSIX_C_SOURCE` (macro, line 10)

## src/dom.c
- Layer: utility
- Language: c
- Symbols:
  - `sm_entry` (struct, line 55)
  - `strmap` (struct, line 64)
  - `pm_entry` (struct, line 154)
  - `ptrmap` (struct, line 160)
  - `dom_index` (struct, line 220)
  - `ih_block` (struct, line 803)
  - `ih_acc` (struct, line 808)
  - `to_lower_buf` (function, line 33) `static int to_lower_buf(const char *s, size_t n, char *out, size_t outcap)`
  - `ptr_hash` (function, line 43) `static size_t ptr_hash(const void *p)`
  - `sm_entry_append` (function, line 69) `static int sm_entry_append(sm_entry *e, dom_node_id id)`
  - `sm_grow` (function, line 81) `static int sm_grow(strmap *m)`
  - `sm_put` (function, line 98) `static int sm_put(strmap *m, const char *key, size_t klen, dom_node_id id)`
  - `sm_find` (function, line 126) `static const sm_entry *sm_find(const strmap *m, const char *key, size_t klen)`
  - `sm_free` (function, line 138) `static void sm_free(strmap *m)`
  - `pm_grow` (function, line 165) `static int pm_grow(ptrmap *m)`
  - `pm_put` (function, line 182) `static int pm_put(ptrmap *m, const void *key, dom_node_id id)`
  - `pm_get` (function, line 199) `static int pm_get(const ptrmap *m, const void *key, dom_node_id *out)`
  - `pm_free` (function, line 210) `static void pm_free(ptrmap *m)`
  - `node_next` (function, line 232) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)`
  - `valid` (function, line 241) `static int valid(const dom_index *idx, dom_node_id n)`
  - `index_element` (function, line 247) `static int index_element(dom_index *idx, lxb_dom_element_t *el, dom_node_id id)`
  - `dom_build` (function, line 283) `dom_status dom_build(const hp_document *doc, dom_index **out)`
  - `dom_free` (function, line 324) `void dom_free(dom_index *idx)`
  - `dom_node_count` (function, line 336) `size_t dom_node_count(const dom_index *idx)`
  - `dom_get_element_by_id` (function, line 340) `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)`
  - `copy_ids` (function, line 346) `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)`
  - `dom_get_by_tag` (function, line 353) `size_t dom_get_by_tag(const dom_index *idx, const char *tag,
                      dom_node_id *o...`
  - `dom_get_by_class` (function, line 362) `size_t dom_get_by_class(const dom_index *idx, const char *cls,
                        dom_node_i...`
  - `id_of` (function, line 376) `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)`
  - `parse_selector_list` (function, line 386) `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)`
  - `node_matches_any` (function, line 419) `static int node_matches_any(const lxb_dom_node_t *cn,
                            const css_sel *...`
  - `count` (function, line 430) `* count (may exceed cap), and returns DOM_NODE_NONE. */
static dom_node_id qs_walk(const dom_inde...`
  - `dom_query_selector` (function, line 459) `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,
                          ...`
  - `dom_query_selector_all` (function, line 468) `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,
                           ...`
  - `dom_matches` (function, line 479) `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)`
  - `dom_closest` (function, line 488) `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,
                        const cha...`
  - `dom_document_position` (function, line 504) `size_t dom_document_position(const dom_index *idx, dom_node_id node)`
  - `dom_precedes` (function, line 509) `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)`
  - `dom_node_at` (function, line 514) `dom_node_id dom_node_at(const dom_index *idx, size_t position)`
  - `dom_parent` (function, line 519) `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)`
  - `dom_first_child` (function, line 529) `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)`
  - `dom_next_sibling` (function, line 537) `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)`
  - `dom_tag_name` (function, line 545) `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)`
  - `dom_get_attribute` (function, line 556) `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,
                           ...`
  - `dom_attribute_names` (function, line 578) `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,
                           con...`
  - `dom_text_content` (function, line 596) `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)`
  - `dom_document_title` (function, line 606) `const char *dom_document_title(const dom_index *idx, size_t *len)`
  - `dom_set_text_content` (function, line 619) `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,
                               ...`
  - `dom_set_document_title` (function, line 644) `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)`
  - `idx_push` (function, line 656) `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)`
  - `dom_create_element` (function, line 672) `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)`
  - `dom_append_child` (function, line 692) `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
  - `dom_remove_child` (function, line 706) `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
  - `dom_set_attribute` (function, line 714) `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,
                             const...`
  - `dom_remove_attribute` (function, line 743) `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)`
  - `index_subtree` (function, line 753) `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)`
  - `dom_set_inner_html` (function, line 762) `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,
                              con...`
  - `ih_append` (function, line 815) `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)`
  - `ih_free` (function, line 842) `static void ih_free(ih_acc *a)`
  - `dom_get_inner_html` (function, line 869) `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,
                           ...`
  - `_POSIX_C_SOURCE` (macro, line 10)
  - `DOM_QS_MAX_SELECTORS` (macro, line 373)
  - `IH_BLOCK_SIZE` (macro, line 801)

## src/dom_debug.c
- Layer: utility
- Language: c
- Symbols:
  - `dd_cursor` (struct, line 24)
  - `dd_putc` (function, line 30) `static void dd_putc(dd_cursor *c, char ch)`
  - `dd_emit` (function, line 35) `static void dd_emit(dd_cursor *c, const char *s, size_t len)`
  - `dd_puts` (function, line 39) `static void dd_puts(dd_cursor *c, const char *s)`
  - `dd_printf` (function, line 48) `static void dd_printf(dd_cursor *c, const char *fmt, ...)`
  - `dd_w` (function, line 80) `static int dd_w(int v)`
  - `dd_color` (function, line 83) `static void dd_color(dd_cursor *c, int rgb)`
  - `dd_display_name` (function, line 87) `static const char *dd_display_name(int d)`
  - `dd_justify_name` (function, line 95) `static const char *dd_justify_name(int j)`
  - `dd_align_name` (function, line 107) `static const char *dd_align_name(int a)`
  - `dd_position_name` (function, line 117) `static const char *dd_position_name(int p)`
  - `dd_visibility_name` (function, line 128) `static const char *dd_visibility_name(int v)`
  - `dd_mix_blend_name` (function, line 136) `static const char *dd_mix_blend_name(int m)`
  - `dd_overflow_name` (function, line 155) `static const char *dd_overflow_name(int o)`
  - `dd_cursor_name` (function, line 164) `static const char *dd_cursor_name(int c)`
  - `dd_text_overflow_name` (function, line 181) `static const char *dd_text_overflow_name(int t)`
  - `dd_inset` (function, line 187) `static int dd_inset(int v)`
  - `dd_object_fit_name` (function, line 190) `static const char *dd_object_fit_name(int o)`
  - `dd_image_rendering_name` (function, line 201) `static const char *dd_image_rendering_name(int r)`
  - `dd_border_style_name` (function, line 210) `static const char *dd_border_style_name(int s)`
  - `dd_box_line` (function, line 243) `static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b)`
  - `dd_block_line` (function, line 301) `static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b)`
  - `dd_format` (function, line 364) `size_t dd_format(const rd_doc *doc, char *out, size_t cap)`
  - `dd_format_css` (function, line 397) `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)`

## src/download.c
- Layer: utility
- Language: c
- Symbols:
  - `lc` (function, line 13) `static int lc(int c)`
  - `ci_find` (function, line 19) `static const char *ci_find(const char *hay, const char *needle)`
  - `media_type` (function, line 33) `static void media_type(const char *content_type, char *buf, size_t bufsz)`
  - `dl_should_download` (function, line 46) `int dl_should_download(const char *content_type, const char *content_disposition)`
  - `dl_ext_for_type` (function, line 57) `const char *dl_ext_for_type(const char *content_type)`
  - `copy_span` (function, line 85) `static void copy_span(const char *src, const char *end, char *buf, size_t bufsz)`
  - `extract_disposition_name` (function, line 96) `static int extract_disposition_name(const char *cd, char *buf, size_t bufsz)`
  - `extract_url_name` (function, line 134) `static int extract_url_name(const char *url, char *buf, size_t bufsz)`
  - `has_extension` (function, line 148) `static int has_extension(const char *name)`
  - `dl_pick_name` (function, line 152) `dl_status dl_pick_name(const char *url, const char *content_disposition,
                       c...`
  - `dl_build_path` (function, line 194) `dl_status dl_build_path(const char *dir, const char *name, char *out, size_t outsz)`
  - `dl_check_size` (function, line 212) `dl_status dl_check_size(size_t len)`

## src/flex_layout.c
- Layer: presentation
- Language: c
- Symbols:
  - `nn` (function, line 18) `static double nn(double v)`
  - `fx_flex_line` (function, line 21) `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                ...`
  - `fx_grid_columns` (function, line 126) `fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          doubl...`
  - `fx_grid_columns_weighted` (function, line 131) `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                      ...`
  - `fx_grid_place_span` (function, line 165) `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                      ...`
  - `fx_grid_area_hash` (function, line 269) `unsigned fx_grid_area_hash(const char *name)`
  - `area_token_is_null_cell` (function, line 294) `static int area_token_is_null_cell(const char *tok, size_t len)`
  - `fx_grid_areas_parse` (function, line 299) `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)`
  - `fx_grid_area_rect` (function, line 374) `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,
                            int ...`
  - `float_pack_impl` (function, line 417) `static fx_status float_pack_impl(const double *width, const int *side, size_t n,
                ...`
  - `fx_float_insets` (function, line 456) `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,
                 ...`
  - `fx_float_pack` (function, line 496) `fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        d...`
  - `fx_float_pack_wrap` (function, line 501) `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,
                    ...`
  - `fx_grid_cell` (function, line 507) `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)`
  - `fx_auto_min_size` (function, line 520) `double fx_auto_min_size(double min_content, double basis, double author_min,
                    ...`
  - `fx_multicol_used` (function, line 533) `fx_status fx_multicol_used(double avail_w, int column_count, double column_width,
               ...`
  - `fx_multicol_balance` (function, line 570) `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,
                        ...`
  - `fx_justify_name` (function, line 601) `const char *fx_justify_name(fx_justify j)`
  - `FX_EPS` (macro, line 14)

## src/form.c
- Layer: data_access
- Language: c
- Symbols:
  - `put_char` (function, line 17) `static int put_char(char *out, size_t outsz, size_t *pos, char c)`
  - `enc_component` (function, line 25) `static int enc_component(const char *s, char *out, size_t outsz, size_t *pos)`
  - `fm_encode` (function, line 42) `fm_status fm_encode(const fm_field *fields, size_t n,
                    char *out, size_t outsz...`
  - `copy_fit` (function, line 66) `static int copy_fit(char *dst, size_t dstsz, const char *src)`
  - `clean_action` (function, line 75) `static int clean_action(const char *action, char *out, size_t outsz)`
  - `strip_query` (function, line 93) `static void strip_query(char *url)`
  - `resolve_target` (function, line 101) `static fm_block_reason resolve_target(const char *base, const char *act,
                        ...`
  - `fm_build` (function, line 119) `fm_status fm_build(const char *base, const char *action, fm_method method,
                   con...`

## src/frame_clock.c
- Layer: utility
- Language: c
- Symbols:
  - `fc_set_active` (function, line 15) `void fc_set_active(fc_clock *c, int active)`
  - `fc_needs_tick` (function, line 20) `int fc_needs_tick(const fc_clock *c)`
  - `fc_interval_ms` (function, line 25) `int fc_interval_ms(const fc_clock *c)`
  - `FC_DEFAULT_INTERVAL_MS` (macro, line 7)

## src/freebug.c
- Layer: utility
- Language: c
- Symbols:
  - `fb_buffer_init` (function, line 14) `void fb_buffer_init(fb_buffer *b)`
  - `fb_buffer_push` (function, line 18) `int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)`
  - `fb_buffer_push_loc` (function, line 22) `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len,
                   ...`
  - `fb_buffer_reset` (function, line 77) `void fb_buffer_reset(fb_buffer *b)`
  - `fb_buffer_free` (function, line 90) `void fb_buffer_free(fb_buffer *b)`
  - `fb_buffer_count` (function, line 100) `size_t fb_buffer_count(const fb_buffer *b)`
  - `fb_buffer_at` (function, line 104) `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)`
  - `fb_level_name` (function, line 109) `const char *fb_level_name(int level)`

## src/freedom.c
- Layer: utility
- Language: c
- Symbols:
  - `print_usage` (function, line 46) `static void print_usage(FILE *fp, const char *prog)`
  - `is_https_url` (function, line 71) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 75) `static int is_http_url(const char *s)`
  - `is_overlay_http` (function, line 81) `static int is_overlay_http(const char *s)`
  - `now_us` (function, line 134) `static uint64_t now_us(void)`
  - `timings_ensure_init` (function, line 140) `static void timings_ensure_init(void)`
  - `timings_enabled` (function, line 144) `static int timings_enabled(void)`
  - `timings_dump` (function, line 148) `static void timings_dump(void)`
  - `read_file` (function, line 195) `static char *read_file(const char *path, size_t *out_len)`
  - `headless_load_hosts` (function, line 212) `static void headless_load_hosts(void)`
  - `is_blank_text` (function, line 251) `static int is_blank_text(const char *s)`
  - `print_doc` (function, line 264) `static void print_doc(const rd_doc *doc)`
  - `print_console` (function, line 357) `static void print_console(const fb_buffer *log)`
  - `print_dom` (function, line 374) `static void print_dom(const rd_doc *doc)`
  - `print_dom_css` (function, line 389) `static void print_dom_css(const rd_doc *doc)`
  - `headless_fetch` (function, line 413) `static int headless_fetch(void *ctx, const char *method, const char *url,
                       ...`
  - `foldback_cookies` (function, line 471) `static void foldback_cookies(const char *url, const char *jar)`
  - `print_css_drops` (function, line 495) `static void print_css_drops(const char *html, size_t len)`
  - `render_page` (function, line 525) `static int render_page(const char *html, size_t len, const char *top_url,
                       ...`
  - `sf_reason` (function, line 733) `static const char *sf_reason(sf_status ss)`
  - `fetch_and_render_one` (function, line 753) `static int fetch_and_render_one(const char *url, char **out_nav)`
  - `elsewhere` (function, line 814) `* page whose script immediately forwards elsewhere (e.g. a search engine's
 * JS-capability inter...`
  - `run_headless` (function, line 832) `static int run_headless(const char *target)`
  - `video_fetch_with_fallback` (function, line 896) `static sf_status video_fetch_with_fallback(const char *url, sf_config *cfg,
                     ...`
  - `run_dump_video` (function, line 1007) `static int run_dump_video(const char *url)`
  - `main` (function, line 1025) `int main(int argc, char **argv)`
  - `_POSIX_C_SOURCE` (macro, line 8)
  - `_DEFAULT_SOURCE` (macro, line 10)
  - `EXIT_OK` (macro, line 42)
  - `EXIT_ERROR` (macro, line 44)
  - `EXIT_USAGE` (macro, line 45)
  - `CSS_DROPS_REPORT_MAX` (macro, line 160)
  - `HL_JS_NAV_MAX` (macro, line 749)

## src/hls.c
- Layer: utility
- Language: c
- Symbols:
  - `last_char` (function, line 38) `static const char *last_char(const char *s, size_t n, int c)`
  - `parse_attr_long` (function, line 48) `static int parse_attr_long(const char *attrs, const char *end,
                           const c...`
  - `parse_attr_resolution` (function, line 62) `static void parse_attr_resolution(const char *attrs, const char *end,
                           ...`
  - `hls_parse` (function, line 79) `hls_status hls_parse(const char *text, size_t len, hls_playlist **out)`
  - `hls_select_variant` (function, line 201) `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h)`
  - `hls_resolve_url` (function, line 222) `size_t hls_resolve_url(const char *base_url, const char *segment_url,
                       char...`
  - `hls_playlist_free` (function, line 252) `void hls_playlist_free(hls_playlist *pl)`
  - `_GNU_SOURCE` (macro, line 20)
  - `_POSIX_C_SOURCE` (macro, line 22)

## src/hostblock.c
- Layer: utility
- Language: c
- Symbols:
  - `hb_table` (struct, line 24)
  - `hb_set` (struct, line 30)
  - `table_probe` (function, line 38) `static size_t table_probe(const hb_table *t, const char *key, size_t klen)`
  - `table_grow` (function, line 49) `static int table_grow(hb_table *t, size_t newcap)`
  - `table_insert` (function, line 71) `static int table_insert(hb_table *t, const char *key, size_t klen)`
  - `table_contains` (function, line 91) `static int table_contains(const hb_table *t, const char *key)`
  - `table_free` (function, line 97) `static void table_free(hb_table *t)`
  - `lower` (function, line 106) `static char lower(char c)`
  - `is_ip_token` (function, line 113) `static int is_ip_token(const char *s, size_t n)`
  - `is_domain_char` (function, line 122) `static int is_domain_char(char c)`
  - `hb_new` (function, line 143) `hb_set *hb_new(void)`
  - `hb_free` (function, line 148) `void hb_free(hb_set *s)`
  - `hb_load` (function, line 155) `hb_status hb_load(hb_set *s, const char *text, hb_list list)`
  - `hb_check` (function, line 192) `hb_decision hb_check(const hb_set *s, const char *host)`
  - `hb_is_allowlisted` (function, line 217) `int hb_is_allowlisted(const hb_set *s, const char *host)`
  - `hb_count` (function, line 237) `size_t hb_count(const hb_set *s, hb_list list)`
  - `HB_MAX_HOST` (macro, line 18)
  - `HB_INIT_CAP` (macro, line 20)

## src/hostedit.c
- Layer: infrastructure
- Language: c
- Symbols:
  - `suggest_ctx` (struct, line 136)
  - `he_lower` (function, line 11) `static char he_lower(char c)`
  - `is_label_char` (function, line 15) `static int is_label_char(char c)`
  - `valid_host` (function, line 22) `static int valid_host(const char *host, size_t n)`
  - `he_make_line` (function, line 40) `he_status he_make_line(const char *host, char *out, size_t cap)`
  - `is_ip_token` (function, line 67) `static int is_ip_token(const char *ts, const char *te)`
  - `he_scan` (function, line 80) `static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), void *ctx)`
  - `has_host_cb` (function, line 104) `static int has_host_cb(const char *ts, size_t tl, void *ctx)`
  - `he_text_has_host` (function, line 108) `int he_text_has_host(const char *text, const char *host)`
  - `contains_ci` (function, line 115) `static int contains_ci(const char *hs, size_t hl, const char *needle)`
  - `starts_with_ci` (function, line 127) `static int starts_with_ci(const char *hs, size_t hl, const char *pfx)`
  - `suggest_cb` (function, line 143) `static int suggest_cb(const char *ts, size_t tl, void *vctx)`
  - `he_suggest` (function, line 163) `int he_suggest(const char *text, const char *query,
               char results[][HE_MAX_HOST + 1...`

## src/html_parse.c
- Layer: utility
- Language: c
- Symbols:
  - `hp_document` (struct, line 21)
  - `dup_bytes` (function, line 26) `static char *dup_bytes(const lxb_char_t *src, size_t len)`
  - `node_next` (function, line 37) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)`
  - `attr_is_event_handler` (function, line 46) `static int attr_is_event_handler(const lxb_dom_attr_t *attr)`
  - `node_is_script` (function, line 53) `static int node_is_script(const lxb_dom_node_t *node)`
  - `strip_scripts` (function, line 59) `static void strip_scripts(lxb_html_document_t *document)`
  - `script_classify` (function, line 97) `static int script_classify(const lxb_dom_node_t *n,
                           const lxb_char_t *...`
  - `hp_extract_script_list` (function, line 126) `hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count)`
  - `hp_free_scripts` (function, line 196) `void hp_free_scripts(hp_script *scripts, size_t count)`
  - `attr_has_token_ci` (function, line 210) `static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle)`
  - `link_is_active_stylesheet` (function, line 231) `static int link_is_active_stylesheet(lxb_dom_element_t *el,
                                     ...`
  - `hp_extract_stylesheet_hrefs` (function, line 252) `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count)`
  - `hp_free_stylesheet_hrefs` (function, line 286) `void hp_free_stylesheet_hrefs(char **hrefs, size_t count)`
  - `strip_event_handlers` (function, line 292) `static void strip_event_handlers(lxb_html_document_t *document)`
  - `hp_config_default` (function, line 315) `hp_config hp_config_default(void)`
  - `hp_validate_input` (function, line 323) `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg)`
  - `hp_parse` (function, line 333) `hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out)`
  - `hp_element_count` (function, line 367) `size_t hp_element_count(const hp_document *doc)`
  - `hp_script_count` (function, line 377) `size_t hp_script_count(const hp_document *doc)`
  - `hp_event_handler_count` (function, line 387) `size_t hp_event_handler_count(const hp_document *doc)`
  - `hp_extract_text` (function, line 403) `char *hp_extract_text(const hp_document *doc, size_t *out_len)`
  - `hp_get_title` (function, line 422) `char *hp_get_title(const hp_document *doc, size_t *out_len)`
  - `hp_free` (function, line 437) `void hp_free(char *buf)`
  - `hp_document_free` (function, line 441) `void hp_document_free(hp_document *doc)`
  - `hp_document_root` (function, line 447) `const void *hp_document_root(const hp_document *doc)`
  - `_POSIX_C_SOURCE` (macro, line 8)

## src/image_decode.c
- Layer: utility
- Language: c
- Symbols:
  - `jpeg_err_ctx` (struct, line 153)
  - `gif_reader` (struct, line 255)
  - `gif_bits` (struct, line 290)
  - `read_be32` (function, line 51) `static uint32_t read_be32(const uint8_t *p)`
  - `img_png_dimensions` (function, line 56) `img_status img_png_dimensions(const uint8_t *bytes, size_t len,
                              uin...`
  - `img_dimensions_ok` (function, line 67) `int img_dimensions_ok(uint32_t w, uint32_t h)`
  - `img_fit` (function, line 75) `void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,
             double *out_w, do...`
  - `premultiply` (function, line 90) `static void premultiply(uint8_t *data, size_t pixels)`
  - `img_decode_png` (function, line 101) `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `jpeg_error_longjmp` (function, line 157) `static void jpeg_error_longjmp(j_common_ptr cinfo)`
  - `jpeg_silence` (function, line 164) `static void jpeg_silence(j_common_ptr cinfo)`
  - `img_decode_jpeg` (function, line 165) `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `gr_u8` (function, line 259) `static int gr_u8(gif_reader *r, uint8_t *out)`
  - `gr_u16le` (function, line 265) `static int gr_u16le(gif_reader *r, uint16_t *out)`
  - `gr_skip` (function, line 272) `static int gr_skip(gif_reader *r, size_t n)`
  - `gr_skip_subblocks` (function, line 280) `static int gr_skip_subblocks(gif_reader *r)`
  - `gb_next_code` (function, line 297) `static int gb_next_code(gif_bits *b, unsigned width, unsigned *out)`
  - `gif_deinterlace_row` (function, line 319) `static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh)`
  - `gif_put_pixel` (function, line 334) `static void gif_put_pixel(uint32_t *canvas, uint32_t cw, uint32_t ch,
                          u...`
  - `img_decode_gif` (function, line 353) `img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `img_decode_webp` (function, line 519) `img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `img_decode` (function, line 552) `img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `img_pixels_free` (function, line 565) `void img_pixels_free(img_pixels *p)`
  - `img_format_name` (function, line 574) `const char *img_format_name(img_format f)`
  - `PNG_IHDR_MIN` (macro, line 34)
  - `GIF_LZW_MAX_CODES` (macro, line 252)

## src/interp.c
- Layer: utility
- Language: c
- Symbols:
  - `sample_bezier_x` (function, line 17) `static double sample_bezier_x(double t, double cx1, double cx2)`
  - `sample_bezier_dx` (function, line 22) `static double sample_bezier_dx(double t, double cx1, double cx2)`
  - `sample_bezier_y` (function, line 28) `static double sample_bezier_y(double t, double cy1, double cy2)`
  - `solve_bezier_t` (function, line 35) `static double solve_bezier_t(double x, double cx1, double cx2)`
  - `ip_ease` (function, line 54) `double ip_ease(double t, const ip_ease_fn *fn)`
  - `ip_ease` (function, line 62) `case IP_EASE_EASE:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_ease` (function, line 68) `case IP_EASE_EASE_IN:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_ease` (function, line 74) `case IP_EASE_EASE_OUT:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_ease` (function, line 80) `case IP_EASE_EASE_IN_OUT:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_lerp` (function, line 133) `double ip_lerp(double a, double b, double t)`
  - `ip_lerp_color` (function, line 138) `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t)`
  - `ip_interp` (function, line 161) `double ip_interp(ip_val_kind kind, double a, double b, double t)`
  - `ip_kf_interp` (function, line 174) `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf,
                    int n_kf, do...`
  - `ip_anim_init` (function, line 195) `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease,
                  const ip_...`
  - `anim_effective_dir_for` (function, line 221) `static int anim_effective_dir_for(const ip_anim *a, int iter)`
  - `anim_effective_dir` (function, line 231) `static int anim_effective_dir(const ip_anim *a)`
  - `ip_anim_tick` (function, line 235) `int ip_anim_tick(ip_anim *a, double dt_ms)`
  - `ip_anim_current` (function, line 281) `double ip_anim_current(const ip_anim *a)`
  - `ip_anim_done` (function, line 319) `int ip_anim_done(const ip_anim *a)`

## src/js_dom.c
- Layer: utility
- Language: c
- Symbols:
  - `jd_method` (struct, line 303)
  - `jd_click_state` (struct, line 1940)
  - `jd_opaque_get` (function, line 24) `static jd_opaque *jd_opaque_get(JSContext *ctx)`
  - `jd_idx` (function, line 28) `static dom_index *jd_idx(JSContext *ctx)`
  - `jd_handle` (function, line 38) `static int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out)`
  - `jd_handle_or_null` (function, line 44) `static JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h)`
  - `m_node_count` (function, line 50) `static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `m_get_element_by_id` (function, line 56) `static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val,
                       ...`
  - `jd_query_list` (function, line 68) `static JSValue jd_query_list(JSContext *ctx, JSValueConst arg, int by_class)`
  - `m_get_by_tag` (function, line 97) `static JSValue m_get_by_tag(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `m_get_by_class` (function, line 103) `static JSValue m_get_by_class(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_tag_name` (function, line 109) `static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_get_attribute` (function, line 119) `static JSValue m_get_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
  - `m_parent` (function, line 132) `static JSValue m_parent(JSContext *ctx, JSValueConst this_val,
                        int argc, ...`
  - `m_first_child` (function, line 140) `static JSValue m_first_child(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_next_sibling` (function, line 148) `static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_precedes` (function, line 156) `static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_text_content` (function, line 167) `static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_set_text` (function, line 177) `static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_get_title` (function, line 191) `static JSValue m_get_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
  - `m_set_title` (function, line 199) `static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
  - `m_create_element` (function, line 212) `static JSValue m_create_element(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_append_child` (function, line 224) `static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_remove_child` (function, line 233) `static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_set_attribute` (function, line 242) `static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
  - `m_remove_attribute` (function, line 258) `static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,
                        ...`
  - `m_set_inner_html` (function, line 270) `static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_get_inner_html` (function, line 287) `static JSValue m_get_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_register_click` (function, line 308) `static JSValue m_register_click(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_register_submit` (function, line 330) `static JSValue m_register_submit(JSContext *ctx, JSValueConst this_val,
                         ...`
  - `m_register_event` (function, line 355) `static JSValue m_register_event(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_query_selector` (function, line 416) `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_query_selector_all` (function, line 429) `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,
                      ...`
  - `m_matches` (function, line 457) `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,
                         int argc...`
  - `m_closest` (function, line 469) `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,
                         int argc...`
  - `m_attr_names` (function, line 481) `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `attrNames` (function, line 561) `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so
     * a missing '...`
  - `js_env` (function, line 1012) `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the
 * document shim (uses...`
  - `jd_lp_set` (function, line 1477) `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,
                      const ...`
  - `jd_install` (function, line 1518) `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)`
  - `fails` (function, line 1579) `* cap is reached or an allocation fails (caller stops), else 0. */
static int cb_append(char **bu...`
  - `jd_install_console` (function, line 1648) `jd_status jd_install_console(js_context *ctx, fb_buffer *log)`
  - `jd_set_location` (function, line 1684) `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)`
  - `jd_set_cookies` (function, line 1718) `jd_status jd_set_cookies(js_context *ctx, const char *cookies)`
  - `jd_get_cookies` (function, line 1738) `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)`
  - `jd_take_nav_request` (function, line 1760) `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)`
  - `jd_pack_ptr` (function, line 1803) `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)`
  - `jd_unpack_ptr` (function, line 1808) `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)`
  - `m_host_fetch` (function, line 1821) `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `jd_install_xhr` (function, line 1913) `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)`
  - `jd_click_state_new` (function, line 1943) `jd_click_state *jd_click_state_new(void)`
  - `jd_click_state_free` (function, line 1948) `void jd_click_state_free(jd_click_state *s)`
  - `jd_install_events` (function, line 1952) `jd_status jd_install_events(js_context *ctx, jd_click_state *state)`
  - `jd_fire_click` (function, line 1963) `int jd_fire_click(js_context *ctx, dom_node_id node_id)`
  - `jd_fire_submit` (function, line 1992) `int jd_fire_submit(js_context *ctx, dom_node_id form_node_id)`
  - `jd_escape_js_str` (function, line 2020) `static size_t jd_escape_js_str(const char *src, char *dst, size_t dstsz)`
  - `jd_fire_mouse_event` (function, line 2099) `int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,
                        const char ...`
  - `try_create_iframe_from_script` (function, line 2192) `static int try_create_iframe_from_script(dom_index *idx,
                                        ...`
  - `jd_video_from_scripts` (function, line 2308) `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,
                   ...`
  - `jd_inject_video_shim` (function, line 2347) `jd_status jd_inject_video_shim(js_context *ctx)`
  - `scan_video_url` (function, line 2362) `static int scan_video_url(const char *body, size_t blen,
                           char *out, si...`
  - `jd_process_iframes` (function, line 2399) `void jd_process_iframes(js_context *ctx, dom_index *idx,
                        jd_fetch_fn fn, ...`
  - `_GNU_SOURCE` (macro, line 9)

## src/js_env.c
- Layer: infrastructure
- Language: c
- Symbols:
  - `wall_clock_ms` (function, line 34) `static uint64_t wall_clock_ms(void)`
  - `monotonic_ms` (function, line 40) `static double monotonic_ms(void)`
  - `m_date_now` (function, line 48) `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_perf_now` (function, line 57) `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_empty_array` (function, line 76) `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_get_random_values` (function, line 84) `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,
                       ...`
  - `m_random_uuid` (function, line 124) `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_subtle_null` (function, line 141) `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `def_val` (function, line 153) `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)`
  - `def_str` (function, line 158) `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)`
  - `def_int` (function, line 162) `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)`
  - `def_fn` (function, line 166) `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,
                  JSCFuncti...`
  - `build_languages` (function, line 174) `static JSValue build_languages(JSContext *ctx)`
  - `build_navigator` (function, line 197) `static int build_navigator(JSContext *ctx, JSValueConst global)`
  - `build_screen` (function, line 294) `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)`
  - `build_crypto` (function, line 338) `static int build_crypto(JSContext *ctx, JSValueConst global)`
  - `build_perf_timing` (function, line 366) `static int build_perf_timing(JSContext *ctx, JSValueConst perf)`
  - `build_perf_navigation` (function, line 380) `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)`
  - `build_performance` (function, line 392) `static int build_performance(JSContext *ctx, JSValueConst global)`
  - `override_date_now` (function, line 425) `static int override_date_now(JSContext *ctx, JSValueConst global)`
  - `make_readback` (function, line 468) `static JSValue make_readback(JSContext *ctx, uint64_t key)`
  - `build_readback_obj` (function, line 476) `static int build_readback_obj(JSContext *ctx, JSValueConst global,
                              ...`
  - `je_install` (function, line 489) `je_status je_install(js_context *ctx, int screen_w, int screen_h)`
  - `je_install_canvas` (function, line 508) `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)`
  - `_POSIX_C_SOURCE` (macro, line 16)
  - `FP_MIME_COUNT` (macro, line 253)
  - `PERF_ORIGIN_EPOCH` (macro, line 337)

## src/js_policy.c
- Layer: business_logic
- Language: c
- Symbols:
  - `eq_ci` (function, line 12) `static int eq_ci(const char *a, const char *b)`
  - `jsp_enabled` (function, line 21) `bool jsp_enabled(jsp_mode mode, int host_allowlisted)`
  - `jsp_trusted` (function, line 30) `bool jsp_trusted(bool js_enabled, int host_allowlisted)`
  - `jsp_present_trusted` (function, line 34) `bool jsp_present_trusted(int host_allowlisted)`
  - `jsp_mode_from_str` (function, line 38) `jsp_mode jsp_mode_from_str(const char *s)`
  - `jsp_mode_str` (function, line 50) `const char *jsp_mode_str(jsp_mode mode)`

## src/js_sandbox.c
- Layer: utility
- Language: c
- Symbols:
  - `js_mem_state` (struct, line 27)
  - `js_context` (struct, line 33)
  - `jm_malloc` (function, line 44) `static void *jm_malloc(void *opaque, size_t size)`
  - `jm_calloc` (function, line 52) `static void *jm_calloc(void *opaque, size_t count, size_t size)`
  - `jm_free` (function, line 62) `static void jm_free(void *opaque, void *ptr)`
  - `jm_realloc` (function, line 68) `static void *jm_realloc(void *opaque, void *ptr, size_t size)`
  - `jm_usable_size` (function, line 78) `static size_t jm_usable_size(const void *ptr)`
  - `host_dup` (function, line 88) `static char *host_dup(const char *src, size_t len)`
  - `timespec_reached` (function, line 97) `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)`
  - `js_interrupt_cb` (function, line 104) `static int js_interrupt_cb(JSRuntime *rt, void *opaque)`
  - `is_ascii_digit` (function, line 116) `static int is_ascii_digit(char c)`
  - `js_loc_from_stack` (function, line 118) `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      i...`
  - `js_limits_default` (function, line 236) `js_limits js_limits_default(void)`
  - `limits_resolve` (function, line 245) `static js_limits limits_resolve(const js_limits *lim)`
  - `js_validate_source` (function, line 254) `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)`
  - `js_context_new` (function, line 265) `js_status js_context_new(const js_limits *lim, js_context **out)`
  - `js_context_free` (function, line 304) `void js_context_free(js_context *ctx)`
  - `arm_deadline` (function, line 313) `static void arm_deadline(js_context *ctx, uint64_t budget_ms)`
  - `js_set_time_budget` (function, line 328) `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)`
  - `js_eval` (function, line 333) `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)`
  - `js_eval_named` (function, line 337) `js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        con...`
  - `js_pump_jobs` (function, line 420) `int js_pump_jobs(js_context *ctx, int max_jobs)`
  - `js_eval_once` (function, line 438) `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)`
  - `js_result_free` (function, line 451) `void js_result_free(js_result *res)`
  - `js_set_current_script` (function, line 464) `void js_set_current_script(js_context *ctx, const char *src, const char *type)`
  - `js_context_raw` (function, line 513) `void *js_context_raw(js_context *ctx)`
  - `_POSIX_C_SOURCE` (macro, line 11)

## src/link_nav.c
- Layer: utility
- Language: c
- Symbols:
  - `clean_href` (function, line 19) `static int clean_href(const char *href, char *out, size_t outsz)`
  - `ci_prefix` (function, line 38) `static int ci_prefix(const char *s, const char *prefix)`
  - `classify_block` (function, line 62) `static ln_block_reason classify_block(const char *ref)`
  - `file_dir_len` (function, line 69) `static size_t file_dir_len(const char *base)`
  - `last_seg_is_dotdot` (function, line 79) `static int last_seg_is_dotdot(const char *body, size_t blen)`
  - `append_seg` (function, line 86) `static int append_seg(char *body, size_t bodysz, size_t *blen,
                      const char *...`
  - `pop_seg` (function, line 98) `static void pop_seg(char *body, size_t *blen)`
  - `resolve_file` (function, line 149) `static int resolve_file(const char *base, const char *ref, char *out, size_t outsz)`
  - `ln_resolve` (function, line 171) `ln_status ln_resolve(const char *base, const char *href, ln_result *out)`
  - `ln_block_reason_text` (function, line 240) `const char *ln_block_reason_text(ln_block_reason reason)`

## src/local_store.c
- Layer: data_access
- Doc: include <openssl/kdf.h> ifndef OSSL_KDF_PARAM_ARGON2_LANES define OSSL_KDF_PARAM_ARGON2_LANES "lanes" endif ifndef OSSL_
- Language: c
- Symbols:
  - `cipher_for` (function, line 727) `static const EVP_CIPHER *cipher_for(ls_aead aead)`
  - `argon2id_derive` (function, line 737) `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,
                          ...`
  - `ls_derive_key` (function, line 766) `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,
                        const...`
  - `aead_encrypt` (function, line 775) `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...`
  - `aead_decrypt` (function, line 801) `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...`
  - `seal_core` (function, line 829) `static ls_status seal_core(const uint8_t *key, ls_aead aead, uint8_t kdf_id,
                    ...`
  - `decrypt_blob` (function, line 866) `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,
         ...`
  - `ls_seal` (function, line 897) `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,
                  const uint8_t *p...`
  - `ls_open` (function, line 910) `ls_status ls_open(const uint8_t key[LS_KEY_LEN],
                  const uint8_t *blob, size_t bl...`
  - `ls_seal_passphrase` (function, line 921) `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,
          ...`
  - `ls_open_passphrase` (function, line 942) `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,
                        ...`
  - `ls_free` (function, line 962) `void ls_free(uint8_t *buf, size_t len)`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 3)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 6)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 9)
  - `_GNU_SOURCE` (macro, line 11)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 14)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 17)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 20)
  - `_GNU_SOURCE` (macro, line 22)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 25)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 28)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 31)
  - `_GNU_SOURCE` (macro, line 33)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 36)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 39)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 42)
  - `_GNU_SOURCE` (macro, line 44)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 47)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 50)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 53)
  - `_GNU_SOURCE` (macro, line 55)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 58)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 61)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 64)
  - `_GNU_SOURCE` (macro, line 66)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 69)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 72)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 75)
  - `_GNU_SOURCE` (macro, line 77)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 80)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 83)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 86)
  - `_GNU_SOURCE` (macro, line 88)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 91)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 94)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 97)
  - `_GNU_SOURCE` (macro, line 99)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 102)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 105)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 108)
  - `_GNU_SOURCE` (macro, line 110)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 113)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 116)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 119)
  - `_GNU_SOURCE` (macro, line 121)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 124)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 127)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 130)
  - `_GNU_SOURCE` (macro, line 132)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 135)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 138)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 141)
  - `_GNU_SOURCE` (macro, line 143)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 146)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 149)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 152)
  - `_GNU_SOURCE` (macro, line 154)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 157)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 160)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 163)
  - `_GNU_SOURCE` (macro, line 165)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 168)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 171)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 174)
  - `_GNU_SOURCE` (macro, line 176)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 179)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 182)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 185)
  - `_GNU_SOURCE` (macro, line 187)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 190)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 193)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 196)
  - `_GNU_SOURCE` (macro, line 198)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 201)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 204)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 207)
  - `_GNU_SOURCE` (macro, line 209)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 212)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 215)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 218)
  - `_GNU_SOURCE` (macro, line 220)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 223)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 226)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 229)
  - `_GNU_SOURCE` (macro, line 231)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 234)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 237)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 240)
  - `_GNU_SOURCE` (macro, line 242)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 245)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 248)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 251)
  - `_GNU_SOURCE` (macro, line 253)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 256)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 259)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 262)
  - `_GNU_SOURCE` (macro, line 264)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 267)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 270)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 273)
  - `_GNU_SOURCE` (macro, line 275)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 278)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 281)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 284)
  - `_GNU_SOURCE` (macro, line 286)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 289)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 292)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 295)
  - `_GNU_SOURCE` (macro, line 297)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 300)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 303)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 306)
  - `_GNU_SOURCE` (macro, line 308)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 311)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 314)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 317)
  - `_GNU_SOURCE` (macro, line 319)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 322)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 325)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 328)
  - `_GNU_SOURCE` (macro, line 330)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 333)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 336)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 339)
  - `_GNU_SOURCE` (macro, line 341)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 344)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 347)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 350)
  - `_GNU_SOURCE` (macro, line 352)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 355)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 358)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 361)
  - `_GNU_SOURCE` (macro, line 363)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 366)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 369)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 372)
  - `_GNU_SOURCE` (macro, line 374)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 377)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 380)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 383)
  - `_GNU_SOURCE` (macro, line 385)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 388)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 391)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 394)
  - `_GNU_SOURCE` (macro, line 396)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 399)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 402)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 405)
  - `_GNU_SOURCE` (macro, line 407)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 410)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 413)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 416)
  - `_GNU_SOURCE` (macro, line 418)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 421)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 424)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 427)
  - `_GNU_SOURCE` (macro, line 429)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 432)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 435)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 438)
  - `_GNU_SOURCE` (macro, line 440)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 443)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 446)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 449)
  - `_GNU_SOURCE` (macro, line 451)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 454)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 457)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 460)
  - `_GNU_SOURCE` (macro, line 462)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 465)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 468)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 471)
  - `_GNU_SOURCE` (macro, line 473)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 476)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 479)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 482)
  - `_GNU_SOURCE` (macro, line 484)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 487)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 490)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 493)
  - `_GNU_SOURCE` (macro, line 495)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 498)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 501)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 504)
  - `_GNU_SOURCE` (macro, line 506)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 509)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 512)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 515)
  - `_GNU_SOURCE` (macro, line 517)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 520)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 523)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 526)
  - `_GNU_SOURCE` (macro, line 528)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 531)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 534)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 537)
  - `_GNU_SOURCE` (macro, line 539)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 542)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 545)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 548)
  - `_GNU_SOURCE` (macro, line 550)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 553)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 556)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 559)
  - `_GNU_SOURCE` (macro, line 561)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 564)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 567)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 570)
  - `_GNU_SOURCE` (macro, line 572)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 575)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 578)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 581)
  - `_GNU_SOURCE` (macro, line 583)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 586)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 589)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 592)
  - `_GNU_SOURCE` (macro, line 594)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 597)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 600)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 603)
  - `_GNU_SOURCE` (macro, line 605)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 608)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 611)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 614)
  - `_GNU_SOURCE` (macro, line 616)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 619)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 622)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 625)
  - `_GNU_SOURCE` (macro, line 627)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 630)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 633)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 636)
  - `_GNU_SOURCE` (macro, line 638)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 641)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 644)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 647)
  - `_GNU_SOURCE` (macro, line 649)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 652)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 655)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 658)
  - `_GNU_SOURCE` (macro, line 660)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 663)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 666)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 669)
  - `_GNU_SOURCE` (macro, line 671)
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 698)
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 701)
  - `OSSL_KDF_PARAM_THREADS` (macro, line 704)
  - `LS_VERSION` (macro, line 706)
  - `LS_KDF_NONE` (macro, line 708)
  - `LS_KDF_ARGON2ID` (macro, line 709)
  - `LS_ARGON2_T` (macro, line 712)
  - `LS_ARGON2_M_KIB` (macro, line 713)
  - `LS_ARGON2_P` (macro, line 714)
  - `OFF_MAGIC` (macro, line 717)
  - `OFF_VERSION` (macro, line 718)
  - `OFF_AEAD` (macro, line 719)
  - `OFF_KDF` (macro, line 720)
  - `OFF_SALT` (macro, line 721)
  - `OFF_NONCE` (macro, line 722)

## src/media_decoder.c
- Layer: infrastructure
- Language: c
- Symbols:
  - `decoder_ctx` (struct, line 54)
  - `open` (function, line 17) `*
 * Sandbox: the decoder needs open() for shared libraries (.so loading) and
 * brk/mmap for FFm...`
  - `decoder_close` (function, line 78) `static void decoder_close(decoder_ctx *dc)`
  - `decoder_init` (function, line 96) `static int decoder_init(decoder_ctx *dc, const uint8_t *data, size_t len)`
  - `frame_pts_us` (function, line 215) `static int64_t frame_pts_us(const AVFrame *f, AVRational tb, int64_t fallback)`
  - `av_rescale_q` (function, line 217) `return av_rescale_q(f->pts, tb, (AVRational)`
  - `send_video_frame` (function, line 222) `static void send_video_frame(decoder_ctx *dc, int64_t pts_us)`
  - `send_audio_frame` (function, line 242) `static void send_audio_frame(decoder_ctx *dc, int64_t pts_us)`
  - `decode_segment` (function, line 276) `static int decode_segment(decoder_ctx *dc, const uint8_t *data, size_t len)`
  - `media_decoder_run` (function, line 378) `void media_decoder_run(int out_fd, int cmd_fd)`
  - `media_decoder_spawn` (function, line 448) `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd)`
  - `_POSIX_C_SOURCE` (macro, line 22)

## src/net_realm.c
- Layer: utility
- Language: c
- Symbols:
  - `lower` (function, line 16) `static char lower(char c)`
  - `ends_with_realm` (function, line 23) `static int ends_with_realm(const char *host, size_t n, const char *suffix)`
  - `nr_classify_host` (function, line 33) `nr_realm nr_classify_host(const char *host)`
  - `host_of` (function, line 52) `static int host_of(const char *url, char *out, size_t out_size)`
  - `nr_classify_url` (function, line 67) `nr_realm nr_classify_url(const char *url)`
  - `nr_route_for` (function, line 73) `nr_route nr_route_for(const char *url, nr_config cfg)`
  - `nr_realm_allows_http` (function, line 87) `int nr_realm_allows_http(nr_realm r)`
  - `nr_realm_name` (function, line 93) `const char *nr_realm_name(nr_realm r)`
  - `nr_route_name` (function, line 102) `const char *nr_route_name(nr_route r)`
  - `NR_MAX_HOST` (macro, line 14)

## src/os_sandbox.c
- Layer: utility
- Language: c
- Symbols:
  - `os_policy_allows` (function, line 51) `int os_policy_allows(long syscall_nr)`
  - `os_policy_size` (function, line 58) `size_t os_policy_size(void)`
  - `os_prot_allowed` (function, line 65) `int os_prot_allowed(long syscall_nr, unsigned long prot)`
  - `os_no_dump` (function, line 75) `os_status os_no_dump(void)`
  - `excluded` (function, line 89) `* intentionally excluded (they need /proc remounting and a post-unshare fork). */
int os_namespac...`
  - `os_isolate_namespaces` (function, line 93) `os_status os_isolate_namespaces(void)`
  - `os_policy_allows` (function, line 105) `int os_policy_allows(long syscall_nr)`
  - `os_policy_size` (function, line 107) `size_t os_policy_size(void)`
  - `os_prot_allowed` (function, line 108) `int os_prot_allowed(long syscall_nr, unsigned long prot)`
  - `os_no_dump` (function, line 111) `os_status os_no_dump(void)`
  - `os_harden` (function, line 112) `os_status os_harden(os_violation action)`
  - `os_namespace_flags` (function, line 114) `int os_namespace_flags(void)`
  - `os_isolate_namespaces` (function, line 116) `os_status os_isolate_namespaces(void)`
  - `os_harden` (function, line 144) `os_status os_harden(os_violation action)`
  - `ll_create_ruleset` (function, line 238) `static long ll_create_ruleset(const struct landlock_ruleset_attr *attr,
                         ...`
  - `ll_add_rule` (function, line 243) `static long ll_add_rule(int fd, enum landlock_rule_type type,
                        const void ...`
  - `ll_restrict_self` (function, line 248) `static long ll_restrict_self(int fd, uint32_t flags)`
  - `ll_handled` (function, line 265) `static uint64_t ll_handled(int abi)`
  - `ll_read_access` (function, line 278) `static uint64_t ll_read_access(uint64_t handled)`
  - `os_landlock_abi` (function, line 284) `int os_landlock_abi(void)`
  - `os_landlock_restrict` (function, line 290) `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)`
  - `os_landlock_abi` (function, line 330) `int os_landlock_abi(void)`
  - `os_landlock_restrict` (function, line 332) `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)`
  - `_GNU_SOURCE` (macro, line 12)
  - `OS_ALLOWED_N` (macro, line 49)
  - `OS_SECCOMP_ARCH` (macro, line 140)
  - `OS_SECCOMP_ARCH` (macro, line 142)
  - `LL_FS_BASE` (macro, line 254)

## src/page_view.c
- Layer: presentation
- Language: c
- Symbols:
  - `pv_node_map` (struct, line 258)
  - `pv_cont_info` (struct, line 1049)
  - `pv_item_track` (struct, line 1106)
  - `pv_box_info` (struct, line 1125)
  - `pv_container_reg` (struct, line 1425)
  - `pv_box_reg` (struct, line 1492)
  - `pv_style_cache` (struct, line 1789)
  - `pv_flow_reg` (struct, line 2079)
  - `sz_fill` (struct, line 2637)
  - `form_rec` (struct, line 2931)
  - `form_table` (struct, line 2937)
  - `pv_flow_reg` (struct, line 3300)
  - `cp1252_to_ucs` (function, line 82) `static unsigned int cp1252_to_ucs(unsigned char c)`
  - `utf8_encode` (function, line 96) `static size_t utf8_encode(unsigned int cp, char *out)`
  - `utf8_sanitized_dup` (function, line 108) `static char *utf8_sanitized_dup(const char *s)`
  - `dup_n` (function, line 142) `static char *dup_n(const char *s, size_t n)`
  - `run_init_common` (function, line 157) `static void run_init_common(pv_run *r)`
  - `pv_node_map_init` (function, line 263) `static int pv_node_map_init(pv_node_map *m)`
  - `pv_node_map_free` (function, line 271) `static void pv_node_map_free(pv_node_map *m)`
  - `pv_node_map_build` (function, line 308) `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root)`
  - `pv_new` (function, line 316) `pv_view *pv_new(void)`
  - `pv_append` (function, line 320) `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    c...`
  - `pv_append_image` (function, line 354) `pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          con...`
  - `pv_append_input` (function, line 384) `pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_...`
  - `pv_append_video` (function, line 424) `pv_status pv_append_video(pv_view *v, int heading, int block_break,
                          con...`
  - `pv_append_svg` (function, line 460) `pv_status pv_append_svg(pv_view *v, int heading, int block_break,
                        const c...`
  - `pv_set_emphasis` (function, line 489) `void pv_set_emphasis(pv_view *v, int bold, int italic)`
  - `pv_set_indent` (function, line 496) `void pv_set_indent(pv_view *v, int indent)`
  - `pv_set_color` (function, line 501) `void pv_set_color(pv_view *v, int fg_rgb)`
  - `pv_set_bgcolor` (function, line 506) `void pv_set_bgcolor(pv_view *v, int bg_rgb)`
  - `pv_set_text_style` (function, line 511) `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,
                ...`
  - `pv_set_grad_text` (function, line 522) `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)`
  - `pv_set_text_ext` (function, line 530) `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)`
  - `ignored` (function, line 563) `* source is ignored (fail-visible: never invisible text from half a
     * pattern). A real text-...`
  - `pv_set_container` (function, line 577) `void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_g...`
  - `pv_set_row_span` (function, line 592) `void pv_set_row_span(pv_view *v, int row_span)`
  - `pv_set_grid_area` (function, line 596) `void pv_set_grid_area(pv_view *v, int row_start, int col_start)`
  - `pv_set_grid` (function, line 603) `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)`
  - `pv_set_grid_rows` (function, line 613) `void pv_set_grid_rows(pv_view *v, int grid_rows)`
  - `pv_set_cont_box` (function, line 617) `void pv_set_cont_box(pv_view *v, int cont_box_id)`
  - `pv_set_flex` (function, line 621) `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                 int...`
  - `pv_set_cont_item` (function, line 633) `void pv_set_cont_item(pv_view *v, int cont_item)`
  - `pv_set_float` (function, line 638) `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear)`
  - `pv_set_box` (function, line 646) `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                int box_center, int ...`
  - `pv_set_box_pct` (function, line 658) `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,
                    ...`
  - `pv_set_ua_tag` (function, line 669) `void pv_set_ua_tag(pv_view *v, int ua_tag)`
  - `pv_set_node_id` (function, line 675) `void pv_set_node_id(pv_view *v, dom_node_id node_id)`
  - `pv_set_block_id` (function, line 680) `void pv_set_block_id(pv_view *v, int block_id)`
  - `pv_set_own_box` (function, line 685) `void pv_set_own_box(pv_view *v, int box_id)`
  - `pv_set_input_checked` (function, line 690) `void pv_set_input_checked(pv_view *v, int checked)`
  - `pv_set_input_select_opts` (function, line 695) `void pv_set_input_select_opts(pv_view *v, const char *select_opts)`
  - `pv_add_cont_def` (function, line 703) `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)`
  - `pv_cont_count` (function, line 716) `size_t pv_cont_count(const pv_view *v)`
  - `pv_cont_at` (function, line 720) `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)`
  - `pv_add_box_def` (function, line 725) `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)`
  - `pv_free` (function, line 738) `void pv_free(pv_view *v)`
  - `pv_count` (function, line 755) `size_t pv_count(const pv_view *v)`
  - `pv_at` (function, line 759) `const pv_run *pv_at(const pv_view *v, size_t i)`
  - `pv_box_count` (function, line 764) `size_t pv_box_count(const pv_view *v)`
  - `pv_box_at` (function, line 768) `const pv_box_def *pv_box_at(const pv_view *v, size_t i)`
  - `node_next` (function, line 777) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)`
  - `is_block_tag` (function, line 786) `static int is_block_tag(lxb_tag_id_t t)`
  - `is_block_like` (function, line 812) `static int is_block_like(lxb_tag_id_t t, css_display display)`
  - `resolves` (function, line 837) `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close
 * button/tooltip w...`
  - `is_block_like_style` (function, line 847) `static int is_block_like_style(lxb_tag_id_t t, const css_style *cs)`
  - `generates_box` (function, line 858) `static int generates_box(lxb_tag_id_t t, css_display display)`
  - `generates_box_style` (function, line 871) `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)`
  - `causes_block_break` (function, line 878) `static int causes_block_break(lxb_tag_id_t t, css_display display)`
  - `paints` (function, line 887) `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas
 * vacías"). Comment a...`
  - `ua_tag_of` (function, line 912) `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)`
  - `heading_level` (function, line 933) `static int heading_level(lxb_tag_id_t t)`
  - `is_skipped_tag` (function, line 945) `static int is_skipped_tag(lxb_tag_id_t t)`
  - `node_tag` (function, line 965) `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)`
  - `in_skipped_subtree` (function, line 974) `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
              ...`
  - `font_color_attr` (function, line 1010) `static int font_color_attr(lxb_dom_element_t *el)`
  - `bgcolor_attr` (function, line 1017) `static int bgcolor_attr(lxb_dom_element_t *el)`
  - `item_ordinal` (function, line 1113) `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)`
  - `pv_content_hidden` (function, line 1144) `int pv_content_hidden(int box_hidden, int run_visibility)`
  - `pv_text_ext_reset` (function, line 1149) `void pv_text_ext_reset(pv_text_ext *e)`
  - `pv_text_ext_merge` (function, line 1176) `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)`
  - `css_has_hbox` (function, line 1234) `static int css_has_hbox(const css_style *cs)`
  - `css_hbox_resolve` (function, line 1247) `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)`
  - `css_has_position` (function, line 1291) `static int css_has_position(const css_style *cs)`
  - `css_has_boxdeco` (function, line 1295) `static int css_has_boxdeco(const css_style *cs)`
  - `cont_def_reset` (function, line 1435) `static void cont_def_reset(pv_cont_def *d)`
  - `container_id` (function, line 1449) `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)`
  - `trying` (function, line 1502) `* a real page passes without trying (slashdot's front page saturates it), and past
 * it box_reg_...`
  - `box_reg_free` (function, line 1530) `static void box_reg_free(pv_box_reg *r)`
  - `boxdef_from_style` (function, line 1540) `static void boxdef_from_style(pv_box_def *d, const css_style *cs)`
  - `box_reg_id` (function, line 1756) `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,
           ...`
  - `pv_style_cache_init` (function, line 1799) `static int pv_style_cache_init(pv_style_cache *c)`
  - `pv_style_cache_free` (function, line 1813) `static void pv_style_cache_free(pv_style_cache *c)`
  - `pv_cache_find` (function, line 1824) `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)`
  - `pv_cached_font_px` (function, line 1835) `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)`
  - `pv_cache_put` (function, line 1839) `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,
                     ...`
  - `pv_parent_element` (function, line 1863) `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)`
  - `size` (function, line 1924) `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */
static void app...`
  - `builder` (function, line 1944) `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box
 * (the ...`
  - `css_to_fx_justify` (function, line 1973) `static int css_to_fx_justify(css_justify j)`
  - `is_bold_tag` (function, line 1992) `static int is_bold_tag(lxb_tag_id_t t)`
  - `is_italic_tag` (function, line 1997) `static int is_italic_tag(lxb_tag_id_t t)`
  - `is_inline_block_row` (function, line 2031) `static int is_inline_block_row(const lxb_dom_node_t *p, const css_sheet *sheet,
                 ...`
  - `paints` (function, line 2051) `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas vacías").
 *
 * A chil...`
  - `resolve_context` (function, line 2082) `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                ...`
  - `margins` (function, line 2311) `* margins (boxdef_from_style) and the painter applies them when
                         * it ope...`
  - `container` (function, line 2427) `* membership in this container (and none in any container further out,
                 * since i...`
  - `walk` (function, line 2510) `* far on this walk (they are all inside this element). */

                        /* The innermo...`
  - `sz_count` (function, line 2629) `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)`
  - `sz_write` (function, line 2642) `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)`
  - `serialize_subtree` (function, line 2650) `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)`
  - `collapse_ws` (function, line 2670) `static char *collapse_ws(const char *s, size_t n)`
  - `parse_dim` (function, line 2694) `static int parse_dim(const lxb_char_t *s, size_t len)`
  - `present` (function, line 2711) `* when no width descriptors are present (density-only or bare URLs). */
static void srcset_best_u...`
  - `srcset_slot_width` (function, line 2806) `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,
                              ...`
  - `dimensions` (function, line 2852) `* viewport dimensions (data: inline detection, <picture> <source> scanning). */
static void srcse...`
  - `find_body` (function, line 2883) `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)`
  - `string` (function, line 2894) `* Returns a heap string (caller frees) or NULL when neither carries a class —
 * NULL simply mean...`
  - `forms_free` (function, line 2941) `static void forms_free(form_table *ft)`
  - `ascii_ieq` (function, line 2949) `static int ascii_ieq(const char *s, const char *lit)`
  - `attr_dup` (function, line 2961) `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)`
  - `forms_add` (function, line 2970) `static int forms_add(form_table *ft, const lxb_dom_node_t *node)`
  - `form_for` (function, line 2990) `static int form_for(const form_table *ft, const lxb_dom_node_t *n,
                    const lxb_...`
  - `under_unrendered` (function, line 3006) `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)`
  - `collect_text` (function, line 3019) `static char *collect_text(const lxb_dom_node_t *el)`
  - `classify_input` (function, line 3042) `static pv_input_type classify_input(const char *type)`
  - `li_ordinal` (function, line 3222) `static int li_ordinal(const lxb_dom_node_t *li)`
  - `roman_marker` (function, line 3248) `static void roman_marker(int n, int upper, char *out, size_t cap)`
  - `list_marker` (function, line 3273) `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,
                  ...`
  - `node_table_role` (function, line 3314) `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)`
  - `nearest_table` (function, line 3332) `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
 ...`
  - `parent_is_table_internal` (function, line 3360) `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)`
  - `nearest_cell` (function, line 3371) `static const lxb_dom_node_t *nearest_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
  ...`
  - `cell_has_nested_table` (function, line 3386) `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)`
  - `next_skip` (function, line 3395) `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)`
  - `cell_anchors` (function, line 3406) `static const lxb_dom_node_t *cell_anchors(const lxb_dom_node_t *cell, int *count)`
  - `links` (function, line 3424) `* its links (the Hacker News case: every story link lives inside a <td>), so the
 * caller flows ...`
  - `flow_table` (function, line 3444) `static int flow_table(pv_flow_reg *fr, const lxb_dom_node_t *table)`
  - `in_flow_table_cell` (function, line 3456) `static int in_flow_table_cell(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,
           ...`
  - `table` (function, line 3466) `* FLOW table (multi-link: walked so its links survive) do NOT suppress their
 * content -- their ...`
  - `table_columns` (function, line 3484) `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)`
  - `collect_style_text` (function, line 3517) `static char *collect_style_text(lxb_dom_node_t *root, size_t *outlen)`
  - `in_hidden_subtree` (function, line 3558) `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
               ...`
  - `in_boilerplate_subtree` (function, line 3575) `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)`
  - `in_closed_details_subtree` (function, line 3590) `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)`
  - `pv_build` (function, line 3609) `pv_status pv_build(const hp_document *doc, pv_view **out)`
  - `pv_build_ex` (function, line 3613) `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)`
  - `pv_build_full` (function, line 3617) `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                     ...`
  - `annotate_replaced_run` (function, line 3640) `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,
                            ...`
  - `collect_page_css` (function, line 3672) `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,
                     ...`
  - `pv_build_styled` (function, line 3697) `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                   ...`
  - `px` (function, line 4228) `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */
                if (iw <...`
  - `engine` (function, line 4808) `* layout engine (contiguous item gather) drops every cell onto its own row and
         * a 2-col...`
  - `appended` (function, line 4862) `* AFTER the run is appended (so THIS run's brk stays) but BEFORE the next. */
        if (cont.fl...`
  - `pv_css_drops` (function, line 4946) `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,
                       const cha...`
  - `_POSIX_C_SOURCE` (macro, line 9)
  - `PV_MAX_DIM` (macro, line 44)
  - `PV_FONT_REL_MIN` (macro, line 49)
  - `PV_FONT_REL_MAX` (macro, line 50)
  - `PV_FONT_CHAIN_MAX` (macro, line 56)
  - `PV_FONT_PCT_MIN` (macro, line 57)
  - `PV_FONT_PCT_MAX` (macro, line 58)
  - `PV_NODE_MAP_INIT_CAP` (macro, line 256)
  - `PV_COLOR_TOKEN_MAX` (macro, line 989)
  - `PV_MAX_CONTAINERS` (macro, line 1026)
  - `PV_MAX_GRID_COLS` (macro, line 1028)
  - `PV_MAX_BOXES` (macro, line 1036)
  - `PV_MAX_INLINE_ROW_ITEMS` (macro, line 2030)
  - `PV_MAX_STYLE_BYTES` (macro, line 3511)

## src/pdf_export.c
- Layer: utility
- Language: c
- Symbols:
  - `pe_safe_basename` (function, line 24) `pe_status pe_safe_basename(const char *title, char *out, size_t outsz)`
  - `pe_build_path_ext` (function, line 65) `pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,
                ...`
  - `pe_build_path` (function, line 90) `pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz)`
  - `pe_paginate` (function, line 94) `size_t pe_paginate(const double *tops, const double *heights, size_t n,
                   double...`

## src/perf_trace.c
- Layer: utility
- Language: c
- Symbols:
  - `pt_init` (function, line 15) `void pt_init(pt_trace *t)`
  - `pt_elapsed_us` (function, line 20) `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us)`
  - `pt_record` (function, line 25) `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us)`
  - `pt_count` (function, line 34) `size_t pt_count(const pt_trace *t, pt_stage stage)`
  - `pt_last_us` (function, line 39) `uint64_t pt_last_us(const pt_trace *t, pt_stage stage)`
  - `pt_min_us` (function, line 48) `uint64_t pt_min_us(const pt_trace *t, pt_stage stage)`
  - `pt_max_us` (function, line 59) `uint64_t pt_max_us(const pt_trace *t, pt_stage stage)`
  - `cmp_u64` (function, line 70) `static int cmp_u64(const void *a, const void *b)`
  - `pt_median_us` (function, line 78) `uint64_t pt_median_us(const pt_trace *t, pt_stage stage)`
  - `pt_stage_name` (function, line 88) `const char *pt_stage_name(pt_stage stage)`
  - `pt_format` (function, line 108) `size_t pt_format(const pt_trace *t, char *buf, size_t cap)`
  - `PT_LINE_CAP` (macro, line 107)

## src/prefetch.c
- Layer: utility
- Language: c
- Symbols:
  - `attr_span` (struct, line 62)
  - `is_ws` (function, line 22) `static int is_ws(char c)`
  - `is_name_char` (function, line 26) `static int is_name_char(char c)`
  - `lower` (function, line 31) `static int lower(int c)`
  - `ci_starts` (function, line 37) `static int ci_starts(const char *p, const char *end, const char *kw)`
  - `ci_find` (function, line 46) `static const char *ci_find(const char *p, const char *end, const char *kw)`
  - `ci_eq_span` (function, line 54) `static int ci_eq_span(const char *s, size_t n, const char *kw)`
  - `emit` (function, line 116) `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)`
  - `pf_scan` (function, line 129) `int pf_scan(const char *html, size_t len, pf_list *out)`
  - `pf_list_free` (function, line 192) `void pf_list_free(pf_list *l)`
  - `pf_worker` (function, line 200) `static void *pf_worker(void *arg)`
  - `pf_pool_start` (function, line 226) `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                  pf_fetch_f...`
  - `pf_pool_take` (function, line 270) `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,
                 char **body,...`
  - `pf_pool_finish` (function, line 309) `void pf_pool_finish(pf_pool *p)`
  - `pf_pooled_fetch` (function, line 323) `int pf_pooled_fetch(void *vctx, const char *method, const char *url,
                    const ch...`
  - `_POSIX_C_SOURCE` (macro, line 11)
  - `PF_MAX_URL` (macro, line 21)

## src/prefs.c
- Layer: utility
- Language: c
- Symbols:
  - `sbuf` (struct, line 367)
  - `url_valid` (function, line 26) `static int url_valid(const char *url)`
  - `title_clean` (function, line 39) `static char *title_clean(const char *src)`
  - `prefs_init` (function, line 65) `void prefs_init(prefs_state *p)`
  - `prefs_free` (function, line 73) `void prefs_free(prefs_state *p)`
  - `bookmark_push` (function, line 91) `static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title)`
  - `history_push_back` (function, line 109) `static prefs_status history_push_back(prefs_state *p, const char *url)`
  - `prefs_bookmark_index` (function, line 124) `int prefs_bookmark_index(const prefs_state *p, const char *url)`
  - `prefs_bookmark_toggle` (function, line 131) `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,
                             ...`
  - `prefs_history_add` (function, line 151) `prefs_status prefs_history_add(prefs_state *p, const char *url)`
  - `prefs_format` (function, line 182) `prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len)`
  - `apply_kv` (function, line 225) `static void apply_kv(prefs_state *out, const char *key, long val)`
  - `prefs_parse` (function, line 240) `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)`
  - `ci_eq` (function, line 299) `static int ci_eq(char a, char b)`
  - `ci_starts` (function, line 305) `static int ci_starts(const char *s, const char *q)`
  - `ci_contains` (function, line 313) `static int ci_contains(const char *s, const char *q)`
  - `url_prefix_match` (function, line 323) `static int url_prefix_match(const char *url, const char *q)`
  - `sugg_push` (function, line 335) `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,
                      cons...`
  - `prefs_suggest` (function, line 343) `int prefs_suggest(const prefs_state *p, const char *query,
                  char *out, size_t ro...`
  - `sb_put` (function, line 368) `static void sb_put(sbuf *b, const char *s, size_t n)`
  - `sb_str` (function, line 383) `static void sb_str(sbuf *b, const char *s)`
  - `sb_esc` (function, line 387) `static void sb_esc(sbuf *b, const char *s)`
  - `sb_link_item` (function, line 399) `static void sb_link_item(sbuf *b, const char *url, const char *label)`
  - `prefs_bookmarks_page` (function, line 407) `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)`
  - `_POSIX_C_SOURCE` (macro, line 10)
  - `PREFS_MAGIC` (macro, line 19)

## src/profile.c
- Layer: utility
- Language: c
- Symbols:
  - `join_path` (function, line 28) `static int join_path(const profile_ctx *ctx, const char *name,
                     char *out, si...`
  - `keyfile_create` (function, line 36) `static profile_status keyfile_create(const char *dir, const char *path,
                         ...`
  - `profile_open` (function, line 58) `profile_status profile_open(profile_ctx *ctx, const char *dir)`
  - `map_ds` (function, line 97) `static profile_status map_ds(ds_status ds)`
  - `profile_load` (function, line 111) `profile_status profile_load(const profile_ctx *ctx, prefs_state *out)`
  - `profile_save` (function, line 132) `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p)`
  - `profile_close` (function, line 148) `void profile_close(profile_ctx *ctx)`
  - `_POSIX_C_SOURCE` (macro, line 10)
  - `PROFILE_KEYFILE_LEN` (macro, line 26)

## src/render_doc.c
- Layer: presentation
- Language: c
- Symbols:
  - `utf8_sanitized_dup` (function, line 26) `static char *utf8_sanitized_dup(const char *s)`
  - `rd_push` (function, line 60) `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,
                 ...`
  - `rd_push_input` (function, line 181) `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)`
  - `resolve_image_decision` (function, line 216) `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,
        ...`
  - `rd_build` (function, line 237) `rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_u...`
  - `unset` (function, line 570) `* background paints as if unset (no border/box-shadow-style
                 * "broken image" pla...`
  - `rd_free` (function, line 634) `void rd_free(rd_doc *d)`
  - `rd_count` (function, line 650) `size_t rd_count(const rd_doc *d)`
  - `rd_at` (function, line 654) `const rd_block *rd_at(const rd_doc *d, size_t i)`
  - `rd_box_count` (function, line 659) `size_t rd_box_count(const rd_doc *d)`
  - `rd_box_at` (function, line 663) `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)`
  - `rd_cont_count` (function, line 668) `size_t rd_cont_count(const rd_doc *d)`
  - `rd_cont_at` (function, line 672) `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)`
  - `rd_kind_name` (function, line 677) `const char *rd_kind_name(rd_kind k)`
  - `rd_block_tag` (function, line 691) `const char *rd_block_tag(const rd_block *b)`
  - `rd_input_label` (function, line 722) `const char *rd_input_label(int input_type)`
  - `rd_image_label` (function, line 741) `const char *rd_image_label(rdp_img_decision d)`
  - `rd_image_fail_label` (function, line 752) `const char *rd_image_fail_label(img_fail_reason reason)`

## src/render_policy.c
- Layer: presentation
- Language: c
- Symbols:
  - `rdp_caps_safe` (function, line 16) `rdp_caps rdp_caps_safe(void)`
  - `rdp_is_tracking_pixel` (function, line 21) `int rdp_is_tracking_pixel(int w, int h)`
  - `rdp_image_decision` (function, line 27) `rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char...`
  - `rdp_img_reason` (function, line 62) `const char *rdp_img_reason(rdp_img_decision d)`
  - `rdp_images_warning` (function, line 73) `const char *rdp_images_warning(void)`

## src/renderer.c
- Layer: presentation
- Language: c
- Symbols:
  - `child_render` (function, line 24) `static void child_render(int wfd, const char *html, size_t len)`
  - `read_field` (function, line 52) `static int read_field(int fd, char **out, size_t *out_len)`
  - `rd_render_html` (function, line 69) `rd_status rd_render_html(const char *html, size_t len, rd_result *out)`
  - `rd_result_free` (function, line 119) `void rd_result_free(rd_result *out)`
  - `_POSIX_C_SOURCE` (macro, line 6)

## src/request_policy.c
- Layer: business_logic
- Language: c
- Symbols:
  - `lower` (function, line 21) `static char lower(char c)`
  - `ci_starts_with` (function, line 25) `static int ci_starts_with(const char *s, const char *prefix)`
  - `psl_cmp` (function, line 35) `static int psl_cmp(const void *key, const void *elem)`
  - `psl_in` (function, line 39) `static int psl_in(const char *const *arr, size_t n, const char *key)`
  - `public_suffix_labels` (function, line 48) `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)`
  - `rp_host_of` (function, line 75) `int rp_host_of(const char *url, char *out, size_t out_size)`
  - `rp_site_of` (function, line 101) `int rp_site_of(const char *host, char *out, size_t out_size)`
  - `rp_same_site` (function, line 133) `int rp_same_site(const char *top_level_url, const char *request_url)`
  - `rp_evaluate` (function, line 142) `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)`
  - `RP_MAX_HOST` (macro, line 16)
  - `RP_MAX_LABELS` (macro, line 18)

## src/secure_fetch.c
- Layer: utility
- Language: c
- Symbols:
  - `body_sink` (struct, line 433)
  - `tls_capture` (struct, line 446)
  - `fetch_ctx` (struct, line 456)
  - `ci_starts_with` (function, line 43) `static int ci_starts_with(const char *haystack, const char *prefix)`
  - `ci_index` (function, line 55) `static long ci_index(const char *haystack, const char *needle)`
  - `sf_share_lock` (function, line 66) `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...`
  - `sf_share_unlock` (function, line 72) `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)`
  - `sf_global_init` (function, line 79) `void sf_global_init(void)`
  - `sf_cookie_line_matches` (function, line 94) `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...`
  - `sf_url_host_path` (function, line 150) `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...`
  - `sf_cookie_header_for` (function, line 164) `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)`
  - `sf_cookie_put` (function, line 193) `void sf_cookie_put(const char *url, const char *namevalue)`
  - `sf_config_default` (function, line 214) `sf_config sf_config_default(void)`
  - `sf_user_agent_or_default` (function, line 239) `const char *sf_user_agent_or_default(const char *ua)`
  - `sf_impersonate_kex_groups` (function, line 243) `const char *sf_impersonate_kex_groups(void)`
  - `sf_impersonate_tls13_ciphers` (function, line 245) `const char *sf_impersonate_tls13_ciphers(void)`
  - `sf_validate_url` (function, line 248) `sf_status sf_validate_url(const char *url)`
  - `sf_url_is_http` (function, line 257) `static int sf_url_is_http(const char *url)`
  - `sf_check_tls_version` (function, line 268) `sf_status sf_check_tls_version(const char *negotiated_version)`
  - `sf_check_group_is_pq` (function, line 273) `sf_status sf_check_group_is_pq(const char *negotiated_group)`
  - `sf_check_chain_policy` (function, line 282) `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)`
  - `sf_enforce_policy` (function, line 292) `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...`
  - `copy_checked` (function, line 323) `static int copy_checked(char *dst, size_t dstsz, const char *src)`
  - `sf_is_redirect_code` (function, line 332) `int sf_is_redirect_code(long http_code)`
  - `sf_parse_location_header` (function, line 339) `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)`
  - `sf_resolve_redirect` (function, line 357) `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...`
  - `sf_ci_prefix` (function, line 370) `static int sf_ci_prefix(const char *s, const char *p)`
  - `sf_response_free` (function, line 409) `void sf_response_free(sf_response *resp)`
  - `copy_bounded` (function, line 468) `static void copy_bounded(char *dst, size_t dstsz, const char *src)`
  - `get_negotiated_group_name` (function, line 480) `static const char *get_negotiated_group_name(SSL *ssl)`
  - `tls_capture_try` (function, line 511) `static void tls_capture_try(tls_capture *cap)`
  - `header_cb` (function, line 543) `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)`
  - `write_cb` (function, line 578) `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)`
  - `name_is_pq_sig` (function, line 611) `static int name_is_pq_sig(int pknid)`
  - `inspect_chain` (function, line 621) `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)`
  - `map_curl_error` (function, line 673) `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)`
  - `sf_perform` (function, line 716) `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...`
  - `redirect` (function, line 832) `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...`
  - `sf_get` (function, line 988) `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)`
  - `sf_post` (function, line 992) `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...`
  - `sf_get_follow` (function, line 1006) `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...`
  - `_POSIX_C_SOURCE` (macro, line 11)

## src/svg_render.c
- Layer: presentation
- Doc: svg_render — inline <svg> markup -> a bounded list of geometric shapes.
- Language: c
- Symbols:
  - `sv_attr` (struct, line 91)
  - `sv_ctx` (struct, line 151)
  - `sv_is_space` (function, line 20) `static int sv_is_space(char c)`
  - `sv_is_digit` (function, line 24) `static int sv_is_digit(char c)`
  - `sv_lower` (function, line 26) `static char sv_lower(char c)`
  - `sv_span_eq` (function, line 32) `static int sv_span_eq(const char *s, size_t n, const char *lit)`
  - `sv_sep` (function, line 82) `static void sv_sep(const char *s, size_t n, size_t *i)`
  - `sv_attr_get` (function, line 99) `static const char *sv_attr_get(const sv_attr *at, size_t nat, const char *name, size_t *len)`
  - `sv_attr_num` (function, line 108) `static double sv_attr_num(const sv_attr *at, size_t nat, const char *name, double dflt)`
  - `sv_mat_identity` (function, line 160) `static void sv_mat_identity(double *m)`
  - `sv_mat_mul` (function, line 166) `static void sv_mat_mul(const double *a, const double *b, double *out)`
  - `sv_parse_transform` (function, line 179) `static void sv_parse_transform(const char *s, size_t n, double *m)`
  - `sv_style_next` (function, line 238) `static int sv_style_next(const char *s, size_t n, size_t *i,
                         const char ...`
  - `sv_apply_prop` (function, line 260) `static void sv_apply_prop(sv_ctx *ctx, const char *nm, size_t nl,
                          const...`
  - `sv_ctx_from_attrs` (function, line 307) `static void sv_ctx_from_attrs(sv_ctx *ctx, const sv_attr *at, size_t nat)`
  - `sv_new_shape` (function, line 323) `static sv_shape *sv_new_shape(sv_image *im, int kind, const sv_ctx *ctx)`
  - `sv_parse_points` (function, line 343) `static void sv_parse_points(sv_image *im, sv_shape *sh, const char *s, size_t n)`
  - `sv_new_seg` (function, line 362) `static sv_seg *sv_new_seg(sv_image *im, sv_shape *sh)`
  - `sv_seg_move` (function, line 370) `static int sv_seg_move(sv_image *im, sv_shape *sh, double x, double y)`
  - `sv_seg_line` (function, line 377) `static int sv_seg_line(sv_image *im, sv_shape *sh, double x, double y)`
  - `sv_seg_cubic` (function, line 384) `static int sv_seg_cubic(sv_image *im, sv_shape *sh,
                        double x1, double y1,...`
  - `sv_arc_to_cubics` (function, line 399) `static int sv_arc_to_cubics(sv_image *im, sv_shape *sh,
                            double x0, do...`
  - `sv_parse_path` (function, line 477) `static void sv_parse_path(sv_image *im, sv_shape *sh, const char *s, size_t n)`
  - `sv_is_dropped_element` (function, line 635) `static int sv_is_dropped_element(const char *name, size_t n)`
  - `sv_scan_attrs` (function, line 647) `static void sv_scan_attrs(const char *s, size_t n, size_t *i,
                          sv_attr *...`
  - `sv_skip_subtree` (function, line 693) `static void sv_skip_subtree(const char *s, size_t n, size_t *i, const char *name, size_t nlen)`
  - `sv_collect_text` (function, line 725) `static void sv_collect_text(const char *s, size_t n, size_t *i, char *dst, size_t cap)`
  - `sv_fit` (function, line 742) `void sv_fit(const sv_image *img, double dw, double dh,
            double *scale, double *off_x, ...`
  - `sv_parse` (function, line 762) `sv_status sv_parse(const char *markup, size_t len, sv_image *out)`
  - `sv_parse_ex` (function, line 766) `sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill)`
  - `SV_MAX_ATTRS` (macro, line 95)

## src/tab.c
- Layer: utility
- Language: c
- Symbols:
  - `child_state` (struct, line 89)
  - `tab` (struct, line 1531)
  - `child_reset_page` (function, line 110) `static void child_reset_page(child_state *cs)`
  - `policy` (function, line 126) `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a
 * compromi...`
  - `run_js` (function, line 180) `* regardless of run_js (a no-JS load simply never records a request). */
static int child_load(ch...`
  - `write_field` (function, line 247) `static int write_field(int fd, const char *s)`
  - `blocks` (function, line 277) `*
 * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the
 * grid arr...`
  - `FB_MAX_FILE_BYTES` (function, line 619) `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...`
  - `budget_remaining_ms` (function, line 649) `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)`
  - `ctype_is_javascript` (function, line 663) `static int ctype_is_javascript(const char *ctype)`
  - `ctype_is_css` (function, line 672) `static int ctype_is_css(const char *ctype)`
  - `log_external_skip` (function, line 680) `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...`
  - `run` (function, line 698) `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...`
  - `window` (function, line 731) `* net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs)`
  - `child_handle_load` (function, line 775) `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...`
  - `swap` (function, line 1019) `* display:none hiding an element via class swap (CSS, not
     * DOM removal). */
    if (ok && v...`
  - `child_next_timer_ms` (function, line 1057) `static int32_t child_next_timer_ms(child_state *cs)`
  - `child_handle_mutation` (function, line 1072) `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...`
  - `child_handle_click` (function, line 1138) `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)`
  - `child_handle_tick` (function, line 1142) `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)`
  - `child_handle_event` (function, line 1152) `static void child_handle_event(int wfd, child_state *cs)`
  - `child_handle_mouse` (function, line 1201) `static void child_handle_mouse(int wfd, child_state *cs)`
  - `child_handle_submit` (function, line 1235) `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)`
  - `child_handle_eval` (function, line 1269) `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)`
  - `child_handle_decode_image` (function, line 1302) `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)`
  - `child_handle_decode_image_b64` (function, line 1324) `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)`
  - `gen_session_key` (function, line 1335) `static uint64_t gen_session_key(void)`
  - `tab_worker_run` (function, line 1356) `static void tab_worker_run(int rfd, int wfd)`
  - `parse_worker_fd` (function, line 1499) `static int parse_worker_fd(const char *s, int *out)`
  - `tab_parse_worker_args` (function, line 1510) `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)`
  - `tab_worker_dispatch` (function, line 1520) `void tab_worker_dispatch(int argc, char **argv)`
  - `ignore_sigpipe` (function, line 1551) `static void ignore_sigpipe(void)`
  - `tab_refresh_alive` (function, line 1557) `static void tab_refresh_alive(tab *t)`
  - `read_field` (function, line 1577) `static int read_field(int fd, char **out, size_t *out_len)`
  - `read_view` (function, line 1593) `static int read_view(int fd, pv_view **out)`
  - `read_console` (function, line 2017) `static int read_console(int fd, fb_buffer *out)`
  - `send_request` (function, line 2054) `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)`
  - `io_failure` (function, line 2063) `static tab_status io_failure(tab *t)`
  - `exec_worker_child` (function, line 2072) `static void exec_worker_child(int rfd, int wfd)`
  - `tab_set_fetcher` (function, line 2142) `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)`
  - `tab_set_net_allowed` (function, line 2148) `void tab_set_net_allowed(tab *t, int allowed)`
  - `tab_set_css_allowed` (function, line 2153) `void tab_set_css_allowed(tab *t, int allowed)`
  - `tab_set_viewport_w` (function, line 2158) `void tab_set_viewport_w(tab *t, int px)`
  - `tab_set_cookies` (function, line 2163) `void tab_set_cookies(tab *t, const char *cookies)`
  - `tab_subreq_permitted` (function, line 2169) `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)`
  - `answered` (function, line 2182) `* A refused frame is still consumed and answered (status 0), so the protocol never
 * desyncs. Re...`
  - `tab_load` (function, line 2217) `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)`
  - `tab_load_ex` (function, line 2221) `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)`
  - `tab_load_full` (function, line 2225) `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...`
  - `tab_click` (function, line 2371) `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)`
  - `tab_tick` (function, line 2378) `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)`
  - `tab_submit` (function, line 2388) `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)`
  - `tab_read_view` (function, line 2493) `tab_status tab_read_view(tab *t, tab_page *out)`
  - `tab_eval` (function, line 2548) `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)`
  - `tab_decode_image_op` (function, line 2589) `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...`
  - `tab_decode_image` (function, line 2630) `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)`
  - `tab_decode_image_data_url` (function, line 2636) `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)`
  - `tab_alive` (function, line 2654) `int tab_alive(const tab *t)`
  - `tab_child_pid` (function, line 2660) `pid_t tab_child_pid(const tab *t)`
  - `tab_close` (function, line 2664) `void tab_close(tab *t)`
  - `tab_page_free` (function, line 2677) `void tab_page_free(tab_page *p)`
  - `tab_eval_result_free` (function, line 2695) `void tab_eval_result_free(tab_eval_result *r)`
  - `tab_image_free` (function, line 2704) `void tab_image_free(tab_image *img)`
  - `_GNU_SOURCE` (macro, line 13)
  - `TAB_SCREEN_W` (macro, line 52)
  - `TAB_SCREEN_H` (macro, line 53)
  - `TAB_MAX_RUNS` (macro, line 57)
  - `PV_MAX_CONTAINERS_WIRE` (macro, line 61)
  - `TAB_MAX_URL` (macro, line 64)
  - `TAB_MAX_SUBREQ` (macro, line 79)
  - `TAB_MAX_SUBRESOURCE` (macro, line 80)
  - `TAB_MAX_JS_JOBS` (macro, line 81)
  - `TAB_MAX_EXTERN_CSS` (macro, line 692)

## src/text_shape.c
- Layer: utility
- Language: c
- Symbols:
  - `tsh_entry` (struct, line 34)
  - `generic_name` (function, line 53) `static const char *generic_name(int family)`
  - `backend_init` (function, line 63) `static int backend_init(void)`
  - `read_font_file` (function, line 80) `static unsigned char *read_font_file(const char *path, long *out_n)`
  - `load_entry` (function, line 96) `static int load_entry(tsh_entry *e, int family, int bold, int italic)`
  - `get_entry` (function, line 151) `static tsh_entry *get_entry(int family, int bold, int italic)`
  - `tsh_ready` (function, line 163) `int tsh_ready(void)`
  - `tsh_shape` (function, line 168) `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                ...`
  - `tsh_measure` (function, line 213) `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)`
  - `tsh_draw` (function, line 220) `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, doub...`
  - `tsh_shutdown` (function, line 242) `void tsh_shutdown(void)`
  - `_POSIX_C_SOURCE` (macro, line 11)
  - `TSH_MAX_FONT_BYTES` (macro, line 28)
  - `TSH_CACHE_SLOTS` (macro, line 32)

## src/textfield.c
- Layer: utility
- Language: c
- Symbols:
  - `whole` (function, line 6) `* the buffer is rejected whole (fail closed), never applied partially.
 */

#include "textfield.h...`
  - `tf_clear` (function, line 19) `void tf_clear(tf_field *f)`
  - `tf_set` (function, line 23) `tf_status tf_set(tf_field *f, const char *s)`
  - `tf_insert` (function, line 34) `tf_status tf_insert(tf_field *f, char c)`
  - `tf_backspace` (function, line 46) `void tf_backspace(tf_field *f)`
  - `tf_delete` (function, line 54) `void tf_delete(tf_field *f)`
  - `tf_move` (function, line 61) `void tf_move(tf_field *f, long delta)`
  - `tf_home` (function, line 72) `void tf_home(tf_field *f)`
  - `tf_end` (function, line 77) `void tf_end(tf_field *f)`
  - `tf_text` (function, line 82) `const char *tf_text(const tf_field *f)`
  - `tf_len` (function, line 86) `size_t tf_len(const tf_field *f)`
  - `tf_cursor` (function, line 90) `size_t tf_cursor(const tf_field *f)`

## src/tls_impersonate.c
- Layer: utility
- Language: c
- Symbols:
  - `ti_should_impersonate` (function, line 17) `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,
                          i...`
  - `bounded_len` (function, line 24) `static size_t bounded_len(const char *s, size_t max)`
  - `put_u8` (function, line 34) `static void put_u8(ti_wr *w, uint8_t v)`
  - `put_u32` (function, line 39) `static void put_u32(ti_wr *w, uint32_t v)`
  - `put_u64` (function, line 47) `static void put_u64(ti_wr *w, uint64_t v)`
  - `put_blob` (function, line 52) `static void put_blob(ti_wr *w, const uint8_t *b, size_t n)`
  - `get_u8` (function, line 64) `static uint8_t get_u8(ti_rd *r)`
  - `get_u32` (function, line 69) `static uint32_t get_u32(ti_rd *r)`
  - `get_u64` (function, line 79) `static uint64_t get_u64(ti_rd *r)`
  - `get_bytes` (function, line 89) `static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len)`
  - `get_str` (function, line 103) `static char *get_str(ti_rd *r, size_t cap)`
  - `valid_profile` (function, line 115) `static int valid_profile(int p)`
  - `ti_encode_req` (function, line 121) `size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap)`
  - `ti_decode_req` (function, line 139) `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out)`
  - `ti_req_free` (function, line 165) `void ti_req_free(ti_req *r)`
  - `ti_encode_resp` (function, line 176) `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap)`
  - `ti_decode_resp` (function, line 195) `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out)`
  - `ti_resp_free` (function, line 229) `void ti_resp_free(ti_resp *r)`

## src/ui_layout.c
- Layer: presentation
- Language: c
- Symbols:
  - `layout_push` (function, line 12) `static int layout_push(ui_layout *lay, size_t offset, size_t len)`
  - `ui_wrap_text` (function, line 26) `ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out)`
  - `ui_layout_free` (function, line 90) `void ui_layout_free(ui_layout *lay)`
  - `ui_clamp_scroll` (function, line 98) `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines)`

## src/url.c
- Layer: utility
- Language: c
- Symbols:
  - `ci_prefix` (function, line 19) `static int ci_prefix(const char *haystack, const char *prefix)`
  - `copy_checked` (function, line 31) `static int copy_checked(char *out, size_t outsz, const char *src)`
  - `cat_checked` (function, line 39) `static int cat_checked(char *out, size_t outsz, const char *src)`
  - `ncat_checked` (function, line 48) `static int ncat_checked(char *out, size_t outsz, const char *src, size_t n)`
  - `url_has_scheme` (function, line 57) `int url_has_scheme(const char *s)`
  - `url_is_https` (function, line 71) `int url_is_https(const char *s)`
  - `url_validate_https` (function, line 78) `url_status url_validate_https(const char *url)`
  - `url_authority_len` (function, line 89) `size_t url_authority_len(const char *url)`
  - `out_pop_segment` (function, line 99) `static void out_pop_segment(char *out, size_t *olen)`
  - `url_remove_dot_segments` (function, line 105) `url_status url_remove_dot_segments(const char *path, char *out, size_t outsz)`
  - `dir_len` (function, line 156) `static size_t dir_len(const char *base)`
  - `url_resolve_https` (function, line 166) `url_status url_resolve_https(const char *base, const char *ref,
                             char...`
  - `is_space` (function, line 214) `static int is_space(int c)`
  - `is_unreserved` (function, line 218) `static int is_unreserved(int c)`
  - `append_query_encoded` (function, line 226) `static int append_query_encoded(char *out, size_t outsz, const char *src)`
  - `assumed` (function, line 251) `* assumed (the caller already routed whitespace to search). */
static int looks_like_host(const c...`
  - `build_search` (function, line 299) `static url_status build_search(const char *query, char *out, size_t outsz)`
  - `url_omnibox` (function, line 305) `url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz)`
  - `host_equals` (function, line 375) `static int host_equals(const url_parts *p, const char *want)`
  - `query_find_q` (function, line 390) `static const char *query_find_q(const char *search, size_t len, size_t *vlen)`
  - `url_search_rewrite` (function, line 407) `url_status url_search_rewrite(const char *url, char *out, size_t outsz)`
  - `url_extract_userinfo` (function, line 427) `url_status url_extract_userinfo(const char *url, char *out, size_t outsz,
                       ...`
  - `url_is_file` (function, line 521) `int url_is_file(const char *s)`
  - `url_file_path` (function, line 527) `const char *url_file_path(const char *s)`
  - `url_resolve_file` (function, line 531) `url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz)`
  - `url_split` (function, line 580) `url_status url_split(const char *url, url_parts *out)`
  - `_POSIX_C_SOURCE` (macro, line 8)

## src/webcaps.c
- Layer: utility
- Language: c
- Symbols:
  - `wc_safe` (function, line 9) `wc_caps wc_safe(void)`
  - `wc_derive` (function, line 14) `wc_caps wc_derive(wc_input in)`
  - `wc_from_flags` (function, line 34) `wc_caps wc_from_flags(bool js, bool css, bool images)`
  - `wc_render_caps` (function, line 45) `rdp_caps wc_render_caps(wc_caps c)`

## src/zoom.c
- Layer: utility
- Language: c
- Symbols:
  - `zm_clamp` (function, line 13) `int zm_clamp(int pct)`
  - `zm_zoom_in` (function, line 19) `int zm_zoom_in(int pct)`
  - `zm_zoom_out` (function, line 27) `int zm_zoom_out(int pct)`
  - `zm_reset` (function, line 35) `int zm_reset(void)`
  - `zm_scale` (function, line 39) `double zm_scale(int pct)`
  - `zm_apply` (function, line 43) `double zm_apply(double base_px, int pct)`
  - `ZM_LADDER_N` (macro, line 12)
