# Subsystem: src

## src/anti_fp.c
- Layer: utility
- Language: c
- Symbols:
  - `fp_coarsen_time_ms` (function, line 17) `uint64_t fp_coarsen_time_ms(uint64_t raw_ms)`
  - `fp_user_agent` (function, line 23) `const char *fp_user_agent(void)`
  - `fp_accept_language` (function, line 27) `const char *fp_accept_language(void)`
  - `fp_accept_language_header` (function, line 31) `const char *fp_accept_language_header(void)`
  - `fp_timezone` (function, line 35) `const char *fp_timezone(void)`
  - `fp_platform` (function, line 39) `const char *fp_platform(void)`
  - `fp_vendor` (function, line 43) `const char *fp_vendor(void)`
  - `fp_hardware_concurrency` (function, line 47) `int fp_hardware_concurrency(void)`
  - `fp_device_memory_gb` (function, line 51) `int fp_device_memory_gb(void)`
  - `fp_app_version` (function, line 57) `const char *fp_app_version(void)`
  - `fp_app_code_name` (function, line 61) `const char *fp_app_code_name(void)`
  - `fp_product` (function, line 65) `const char *fp_product(void)`
  - `fp_app_name` (function, line 69) `const char *fp_app_name(void)`
  - `fp_product_sub` (function, line 73) `const char *fp_product_sub(void)`
  - `fp_oscpu` (function, line 77) `const char *fp_oscpu(void)`
  - `fp_build_id` (function, line 81) `const char *fp_build_id(void)`
  - `fp_max_touch_points` (function, line 85) `int fp_max_touch_points(void)`
  - `fp_on_line` (function, line 89) `int fp_on_line(void)`
  - `fp_cookie_enabled` (function, line 93) `int fp_cookie_enabled(void)`
  - `fp_bucket_screen` (function, line 99) `void fp_bucket_screen(int w, int h, int *out_w, int *out_h)`
  - `splitmix64` (function, line 121) `static uint64_t splitmix64(uint64_t *state)`
  - `fp_perturb` (function, line 128) `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key)`
  - `fp_origin_key` (function, line 139) `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain)`
- Depends on: `include/anti_fp.h`

## src/block_flow.c
- Layer: utility
- Doc: block_flow (bf_) -- vertical margin collapsing. See spec/block_flow.md.
- Language: c
- Symbols:
  - `finite_or_zero` (function, line 11) `static double finite_or_zero(double v)`
  - `bf_collapse_n` (function, line 15) `double bf_collapse_n(const double *m, size_t n)`
  - `bf_collapse` (function, line 30) `double bf_collapse(double a, double b)`
  - `bf_margins_adjoin` (function, line 35) `int bf_margins_adjoin(double border_px, double padding_px)`
- Depends on: `include/block_flow.h`

## src/box_style.c
- Layer: utility
- Language: c
- Symbols:
  - `tag_row` (struct, line 59)
  - `disp_row` (struct, line 239)
  - `is_ws` (function, line 29) `static int is_ws(char c)`
  - `copy_lower_trim` (function, line 35) `static int copy_lower_trim(const char *in, char *out, size_t out_size)`
  - `name_cmp` (function, line 48) `static int name_cmp(const void *key, const void *elem)`
  - `bx_default_for_tag` (function, line 161) `bx_box bx_default_for_tag(const char *tag)`
  - `bx_table_role_of` (function, line 169) `bx_table_role bx_table_role_of(const char *tag, css_display display)`
  - `bx_ua_of_tag` (function, line 208) `bx_ua_tag bx_ua_of_tag(const char *tag)`
  - `bx_default_for_ua` (function, line 217) `bx_box bx_default_for_ua(bx_ua_tag id)`
  - `bx_block_ua_box` (function, line 223) `bx_box bx_block_ua_box(int heading_level, int in_list, bx_ua_tag ua)`
  - `bx_parse_display` (function, line 259) `bx_status bx_parse_display(const char *token, bx_display *out)`
  - `bx_place` (function, line 269) `bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,
                ...`
  - `bx_width_cap` (function, line 286) `double bx_width_cap(int w_px, int w_pct, double avail_w)`
  - `bx_width_cap2` (function, line 311) `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w)`
  - `bx_replaced_box` (function, line 319) `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den,
                    doub...`
  - `bx_border_box_h` (function, line 333) `double bx_border_box_h(double declared_h, int border_box,
                       double pad_t, do...`
  - `bx_content_clipped` (function, line 344) `int bx_content_clipped(int overflow_x, int overflow_y)`
  - `bx_lp_px` (function, line 350) `double bx_lp_px(int px_val, int pct_pm, double basis)`
  - `bx_content_cap` (function, line 361) `double bx_content_cap(double width_cap, int border_box,
                      double pad_l, doubl...`
  - `bg_size_component` (function, line 375) `static double bg_size_component(int px_val, int pct_pm, double area)`
  - `bx_background_layer` (function, line 382) `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h,
                    ...`
  - `bx_display_name` (function, line 421) `const char *bx_display_name(bx_display d)`
  - `take` (function, line 293) `* caller has to take (Sizing 3 section 5.1), so to a resolver that only sums a * px and a percentage half they read exactly like `auto` -- no declared width. * Letting the sentinel through would have `
  - `BX_TAG_MAX` (macro, line 22) `#define BX_TAG_MAX`
  - `BX_DISPLAY_MAX` (macro, line 23) `#define BX_DISPLAY_MAX`
  - `BLOCK` (macro, line 65) `#define BLOCK`
  - `INLINE` (macro, line 66) `#define INLINE`
  - `IBLOCK` (macro, line 67) `#define IBLOCK`
  - `LITEM` (macro, line 68) `#define LITEM`
  - `NONE` (macro, line 69) `#define NONE`
  - `EDG` (macro, line 70) `#define EDG(t, r, b, l)`
  - `ZERO` (macro, line 71) `#define ZERO`
  - `T_NO` (macro, line 73) `#define T_NO`
  - `T_TBL` (macro, line 74) `#define T_TBL`
  - `T_GRP` (macro, line 75) `#define T_GRP`
  - `T_ROW` (macro, line 76) `#define T_ROW`
  - `T_CELL` (macro, line 77) `#define T_CELL`
  - `T_CAP` (macro, line 78) `#define T_CAP`
  - `T_COL` (macro, line 79) `#define T_COL`
  - `TAG_N` (macro, line 159) `#define TAG_N`
  - `DISP_N` (macro, line 257) `#define DISP_N`
- Depends on: `include/box_style.h`

## src/box_tree.c
- Layer: utility
- Language: c
- Symbols:
  - `layout_block` (function, line 37) `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,
                   ...`
  - `bt_nn` (function, line 58) `static double bt_nn(double v)`
  - `wrap_reverse` (function, line 79) `*
 * wrap_reverse (node->wrap_reverse): when node->wrap is active and node->wrap_reverse
 * is no...`
  - `layout_flex` (function, line 97) `static bt_status layout_flex(bt_node *node, bt_node *const *kids, size_t nk,
                    ...`
  - `layout_grid` (function, line 220) `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,
                    ...`
  - `layout_node` (function, line 327) `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)`
  - `bt_layout` (function, line 372) `bt_status bt_layout(bt_node *root, double avail_w)`
  - `assign_doc_order` (function, line 412) `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,
                  ...`
  - `find_positioned_ancestor` (function, line 429) `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,
                       ...`
  - `resolve_inset` (function, line 449) `static double resolve_inset(int v, int pct_pm, double basis)`
  - `inset_unset` (function, line 458) `static int inset_unset(int v, int pct_pm)`
  - `bt_containing_block` (function, line 462) `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i,
                        ...`
  - `block` (function, line 473) `* true block (same flow neighbourhood), strictly better than zeros. NULL
     * placed keeps lega...`
  - `bt_resolve_positioning` (function, line 492) `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,
                          ...`
  - `bt_resolve_positioning_ex` (function, line 503) `bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,
                       ...`
  - `oof_walk` (function, line 658) `static int oof_walk(const pv_box_def *boxes, size_t nbox, int bid, int nearest)`
  - `bt_oof_anchor` (function, line 675) `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)`
  - `bt_oof_root` (function, line 679) `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)`
  - `bt_box_hidden` (function, line 683) `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)`
  - `bt_oof_avail` (function, line 696) `double bt_oof_avail(int a, int a_pct, int b, int b_pct, double cb, int *both)`
  - `BT_LEN_AUTO` (macro, line 31) `#define BT_LEN_AUTO`
  - `BT_WRAP_EPS` (macro, line 62) `#define BT_WRAP_EPS`
- Depends on: `include/box_style.h`, `include/box_tree.h`, `include/compositor.h`, `include/css.h`

## src/browser.c
- Layer: utility
- Language: c
- Symbols:
  - `free_page` (function, line 15) `static void free_page(browser_state *bs)`
  - `clear_status` (function, line 25) `static void clear_status(browser_state *bs)`
  - `free_history` (function, line 30) `static void free_history(browser_state *bs)`
  - `free_exceptions` (function, line 42) `static void free_exceptions(browser_state *bs)`
  - `is_https_url` (function, line 51) `static int is_https_url(const char *s)`
  - `is_local_path` (function, line 55) `static int is_local_path(const char *s)`
  - `url_is_allowed` (function, line 60) `static int url_is_allowed(const char *url)`
  - `xstrdup` (function, line 74) `static char *xstrdup(const char *s)`
  - `cp1252_to_ucs` (function, line 88) `static unsigned int cp1252_to_ucs(unsigned char c)`
  - `utf8_encode` (function, line 102) `static size_t utf8_encode(unsigned int cp, char *out)`
  - `browser_init` (function, line 156) `browser_status browser_init(browser_state *bs)`
  - `browser_free` (function, line 167) `void browser_free(browser_state *bs)`
  - `browser_set_url_bar` (function, line 178) `browser_status browser_set_url_bar(browser_state *bs, const char *url)`
  - `browser_commit_url_bar` (function, line 190) `browser_status browser_commit_url_bar(browser_state *bs)`
  - `browser_navigate` (function, line 224) `browser_status browser_navigate(browser_state *bs, const char *url)`
  - `browser_push_state` (function, line 236) `browser_status browser_push_state(browser_state *bs, const char *url)`
  - `browser_replace_state` (function, line 243) `browser_status browser_replace_state(browser_state *bs, const char *url)`
  - `browser_entry_doc` (function, line 255) `int browser_entry_doc(const browser_state *bs, size_t pos)`
  - `browser_doc_index` (function, line 260) `int browser_doc_index(const browser_state *bs)`
  - `browser_back` (function, line 268) `browser_status browser_back(browser_state *bs)`
  - `browser_forward` (function, line 280) `browser_status browser_forward(browser_state *bs)`
  - `browser_can_back` (function, line 292) `int browser_can_back(const browser_state *bs)`
  - `browser_can_forward` (function, line 296) `int browser_can_forward(const browser_state *bs)`
  - `browser_current_url` (function, line 300) `const char *browser_current_url(const browser_state *bs)`
  - `browser_url_bar_selection` (function, line 305) `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)`
  - `browser_url_bar_delete_selection` (function, line 316) `int browser_url_bar_delete_selection(browser_state *bs)`
  - `browser_url_bar_insert` (function, line 326) `browser_status browser_url_bar_insert(browser_state *bs, char c)`
  - `browser_url_bar_backspace` (function, line 341) `browser_status browser_url_bar_backspace(browser_state *bs)`
  - `browser_url_bar_delete` (function, line 355) `browser_status browser_url_bar_delete(browser_state *bs)`
  - `browser_url_bar_move_cursor` (function, line 366) `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)`
  - `browser_url_bar_extend_cursor` (function, line 376) `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)`
  - `browser_url_bar_set_cursor` (function, line 385) `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)`
  - `browser_url_bar_select_all` (function, line 393) `browser_status browser_url_bar_select_all(browser_state *bs)`
  - `browser_url_bar_clear` (function, line 400) `browser_status browser_url_bar_clear(browser_state *bs)`
  - `browser_set_page` (function, line 409) `browser_status browser_set_page(browser_state *bs, const char *title,
                           ...`
  - `browser_set_status` (function, line 431) `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)`
  - `browser_status_text` (function, line 445) `const char *browser_status_text(const browser_state *bs, uint64_t now_ms)`
  - `host_equal` (function, line 453) `static int host_equal(const char *a, const char *b)`
  - `browser_is_exception` (function, line 464) `int browser_is_exception(const browser_state *bs, const char *host)`
  - `browser_add_exception` (function, line 472) `browser_status browser_add_exception(browser_state *bs, const char *host)`
  - `_POSIX_C_SOURCE` (macro, line 7) `#define _POSIX_C_SOURCE`
- Depends on: `include/browser.h`, `include/util.h`

## src/compositor.c
- Layer: utility
- Language: c
- Symbols:
  - `cx_forms_stacking_context` (function, line 16) `int cx_forms_stacking_context(const cx_style *s)`
  - `cx_box_layer` (function, line 34) `cx_layer cx_box_layer(const cx_style *s)`
  - `eff_z` (function, line 50) `static int eff_z(const cx_item *it)`
  - `cx_item_compare` (function, line 54) `int cx_item_compare(const cx_item *a, const cx_item *b)`
  - `cx_sort` (function, line 70) `void cx_sort(cx_item *items, size_t n)`
- Depends on: `include/compositor.h`, `include/css.h`

## src/css.c
- Layer: utility
- Language: c
- Symbols:
  - `css_sheet` (struct, line 99)
  - `css_keyframe_stop` (struct, line 132)
  - `css_match` (struct, line 4836)
  - `css_cand` (struct, line 4842)
  - `css_rule` (struct, line 97)
  - `idx` (type_alias, line 4842) `typedef struct css_cand { int imp, espec, ord, idx;`
  - `parse_num` (function, line 163) `static int parse_num(const char *s, double *out, const char **endp)`
  - `parse_color` (function, line 174) `static int parse_color(const char *v)`
  - `interp_color` (function, line 178) `static int interp_color(const char *v)`
  - `through` (function, line 194) `* at the two SHARED chokepoints every property funnels through (the generic
 * dispatch tail, and...`
  - `bg_alpha_of` (function, line 214) `static int bg_alpha_of(const char *v)`
  - `interp_bg` (function, line 218) `static int interp_bg(const char *v)`
  - `expand_bg_image` (function, line 226) `static int expand_bg_image(const char *val, css_decl *dst, int cap,
                           ch...`
  - `expand_background` (function, line 231) `static int expand_background(const char *val, css_decl *dst, int cap,
                           ...`
  - `text` (function, line 243) `* source text (rem_rebase, see below) rather than by threading a context here.
 *
 * Viewport uni...`
  - `expand_box4` (function, line 263) `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,
            ...`
  - `expand_box2` (function, line 268) `static int expand_box2(const char *val, int slot_start, int slot_end,
                       int ...`
  - `interp_len` (function, line 273) `static int interp_len(const char *v, int allow_auto, int *out)`
  - `interp_lp` (function, line 277) `static int interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_...`
  - `lp_can_be_nonneg` (function, line 282) `static int lp_can_be_nonneg(int px_val, int pct_pm)`
  - `next_ws_token` (function, line 286) `static int next_ws_token(const char **p, char *tok, size_t cap)`
  - `interp_align` (function, line 290) `static int interp_align(const char *v)`
  - `interp_fontsize_ex` (function, line 294) `static int interp_fontsize_ex(const char *v, int *abs_out)`
  - `interp_lineheight` (function, line 298) `static int interp_lineheight(const char *v)`
  - `interp_weight` (function, line 302) `static int interp_weight(const char *v)`
  - `interp_style` (function, line 306) `static int interp_style(const char *v)`
  - `interp_textdeco` (function, line 310) `static int interp_textdeco(const char *v)`
  - `interp_display` (function, line 314) `static int interp_display(const char *v)`
  - `interp_gap` (function, line 318) `static int interp_gap(const char *v)`
  - `interp_justify` (function, line 322) `static int interp_justify(const char *v)`
  - `interp_gridcols` (function, line 326) `static int interp_gridcols(const char *v)`
  - `expand_grid_template_cols` (function, line 330) `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)`
  - `interp_fontfamily` (function, line 336) `static int interp_fontfamily(const char *v)`
  - `interp_texttransform` (function, line 337) `static int interp_texttransform(const char *v)`
  - `interp_opacity` (function, line 338) `static int interp_opacity(const char *v)`
  - `expand_valign` (function, line 339) `static int expand_valign(const char *val, css_decl *dst, int cap)`
  - `interp_transition_property` (function, line 340) `static int interp_transition_property(const char *v)`
  - `interp_whitespace` (function, line 341) `static int interp_whitespace(const char *v)`
  - `interp_tabsize` (function, line 342) `static int interp_tabsize(const char *v)`
  - `interp_textdeco_style` (function, line 343) `static int interp_textdeco_style(const char *v)`
  - `interp_textdeco_thickness` (function, line 344) `static int interp_textdeco_thickness(const char *v)`
  - `interp_aspect_ratio` (function, line 345) `static int interp_aspect_ratio(const char *v, int *num, int *den)`
  - `interp_direction` (function, line 346) `static int interp_direction(const char *v)`
  - `interp_liststyle` (function, line 347) `static int interp_liststyle(const char *v)`
  - `emit_spacing` (function, line 348) `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
  - `expand_shadow` (function, line 349) `static int expand_shadow(const char *val, css_decl *dst, int cap)`
  - `interp_position` (function, line 353) `static int interp_position(const char *v)`
  - `interp_boxsizing` (function, line 362) `static int interp_boxsizing(const char *v)`
  - `interp_float` (function, line 368) `static int interp_float(const char *v)`
  - `interp_clear` (function, line 375) `static int interp_clear(const char *v)`
  - `interp_visibility` (function, line 385) `static int interp_visibility(const char *v)`
  - `interp_overflow` (function, line 392) `static int interp_overflow(const char *v)`
  - `interp_cursor` (function, line 424) `static int interp_cursor(const char *v)`
  - `interp_text_overflow` (function, line 440) `static int interp_text_overflow(const char *v)`
  - `interp_word_break` (function, line 446) `static int interp_word_break(const char *v)`
  - `interp_overflow_wrap` (function, line 454) `static int interp_overflow_wrap(const char *v)`
  - `interp_border_collapse` (function, line 462) `static int interp_border_collapse(const char *v)`
  - `number` (function, line 471) `* number (no unit) as px (common in shorthand context like "10 5"). */
static int interp_border_s...`
  - `interp_empty_cells` (function, line 496) `static int interp_empty_cells(const char *v)`
  - `interp_caption_side` (function, line 503) `static int interp_caption_side(const char *v)`
  - `interp_table_layout` (function, line 510) `static int interp_table_layout(const char *v)`
  - `interp_font_variant` (function, line 517) `static int interp_font_variant(const char *v)`
  - `interp_hyphens` (function, line 525) `static int interp_hyphens(const char *v)`
  - `interp_user_select` (function, line 533) `static int interp_user_select(const char *v)`
  - `interp_caret_color` (function, line 542) `static int interp_caret_color(const char *v)`
  - `interp_appearance` (function, line 554) `static int interp_appearance(const char *v)`
  - `interp_pointer_events` (function, line 572) `static int interp_pointer_events(const char *v)`
  - `interp_bg_repeat` (function, line 584) `static int interp_bg_repeat(const char *v)`
  - `interp_bg_size` (function, line 594) `static int interp_bg_size(const char *v)`
  - `interp_bg_clip` (function, line 601) `static int interp_bg_clip(const char *v)`
  - `interp_bg_origin` (function, line 609) `static int interp_bg_origin(const char *v)`
  - `interp_bg_attachment` (function, line 616) `static int interp_bg_attachment(const char *v)`
  - `interp_isolation` (function, line 623) `static int interp_isolation(const char *v)`
  - `interp_contain` (function, line 629) `static int interp_contain(const char *v)`
  - `interp_content_visibility` (function, line 650) `static int interp_content_visibility(const char *v)`
  - `interp_image_rendering` (function, line 657) `static int interp_image_rendering(const char *v)`
  - `interp_color_scheme` (function, line 664) `static int interp_color_scheme(const char *v)`
  - `interp_accent_color` (function, line 682) `static int interp_accent_color(const char *v)`
  - `interp_print_color_adjust` (function, line 687) `static int interp_print_color_adjust(const char *v)`
  - `interp_forced_color_adjust` (function, line 693) `static int interp_forced_color_adjust(const char *v)`
  - `interp_mix_blend_mode` (function, line 700) `static int interp_mix_blend_mode(const char *v)`
  - `interp_object_fit` (function, line 718) `static int interp_object_fit(const char *v)`
  - `interp_list_style_pos` (function, line 727) `static int interp_list_style_pos(const char *v)`
  - `interp_font_kerning` (function, line 733) `static int interp_font_kerning(const char *v)`
  - `interp_text_rendering` (function, line 740) `static int interp_text_rendering(const char *v)`
  - `interp_font_stretch` (function, line 748) `static int interp_font_stretch(const char *v)`
  - `interp_resize` (function, line 761) `static int interp_resize(const char *v)`
  - `interp_scroll_behavior` (function, line 769) `static int interp_scroll_behavior(const char *v)`
  - `interp_touch_action` (function, line 775) `static int interp_touch_action(const char *v)`
  - `interp_overscroll_behavior` (function, line 782) `static int interp_overscroll_behavior(const char *v)`
  - `interp_backface_visibility` (function, line 789) `static int interp_backface_visibility(const char *v)`
  - `interp_border_style` (function, line 812) `static int interp_border_style(const char *v)`
  - `interp_bwidth1` (function, line 838) `static int interp_bwidth1(const char *v)`
  - `interp_time_ms` (function, line 847) `static int interp_time_ms(const char *v)`
  - `emit_radius_corner` (function, line 880) `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)`
  - `interp_bw_tok` (function, line 888) `static int interp_bw_tok(const char *t, int *o)`
  - `interp_bs_tok` (function, line 889) `static int interp_bs_tok(const char *t, int *o)`
  - `interp_bc_tok` (function, line 890) `static int interp_bc_tok(const char *t, int *o)`
  - `expand_outline` (function, line 955) `static int expand_outline(const char *val, css_decl *dst, int cap)`
  - `interp_column_count` (function, line 971) `static int interp_column_count(const char *v)`
  - `interp_column_width` (function, line 983) `static int interp_column_width(const char *v)`
  - `expand_columns` (function, line 994) `static int expand_columns(const char *val, css_decl *dst, int cap)`
  - `expand_flex_flow` (function, line 1028) `static int expand_flex_flow(const char *val, css_decl *dst, int cap)`
  - `expand_column_rule` (function, line 1050) `static int expand_column_rule(const char *val, css_decl *dst, int cap)`
  - `interp_filter_pct` (function, line 1062) `static int interp_filter_pct(const char *s)`
  - `interp_filter_deg` (function, line 1076) `static int interp_filter_deg(const char *s)`
  - `filter_paren_body` (function, line 1091) `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)`
  - `expand_backdrop_filter` (function, line 1254) `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)`
  - `expand_bg_position` (function, line 1287) `static int expand_bg_position(const char *val, css_decl *dst, int cap)`
  - `expand_bg_size` (function, line 1347) `static int expand_bg_size(const char *val, css_decl *dst, int cap)`
  - `emit_content` (function, line 1387) `static int emit_content(css_decl *dst, int cap, const char *str,
                        char (*c...`
  - `expand_content` (function, line 1403) `static int expand_content(const char *val, css_decl *dst, int cap,
                          char...`
  - `expand_grid_areas` (function, line 1439) `static int expand_grid_areas(const char *val, css_decl *dst, int cap,
                           ...`
  - `expand_grid_template` (function, line 1506) `static int expand_grid_template(const char *val, css_decl *dst, int cap,
                        ...`
  - `expand_box_shadow` (function, line 1557) `static int expand_box_shadow(const char *val, css_decl *dst, int cap)`
  - `interp_flex_factor` (function, line 1585) `static int interp_flex_factor(const char *v)`
  - `interp_flex_basis` (function, line 1595) `static int interp_flex_basis(const char *v, int *out)`
  - `expand_flex` (function, line 1629) `static int expand_flex(const char *val, css_decl *dst, int cap)`
  - `interp_align_kw` (function, line 1674) `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)`
  - `interp_flex_direction` (function, line 1687) `static int interp_flex_direction(const char *v)`
  - `interp_box_orient` (function, line 1705) `static int interp_box_orient(const char *v)`
  - `interp_flex_wrap` (function, line 1711) `static int interp_flex_wrap(const char *v)`
  - `interp_grid_flow` (function, line 1719) `static int interp_grid_flow(const char *v)`
  - `interp_grid_span` (function, line 1745) `static int interp_grid_span(const char *v)`
  - `copy_trim` (function, line 1764) `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)`
  - `strip_important` (function, line 1777) `static int strip_important(char *val)`
  - `var` (function, line 1802) `* cvr_resolve then substitutes var() references when a declaration's value is
 * interpreted (par...`
  - `selector_matches_root` (function, line 1824) `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m)`
  - `tr_mul` (function, line 1948) `static void tr_mul(double out[6], const double l[6], const double r[6])`
  - `tr_decompose` (function, line 1968) `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,
                        in...`
  - `parse_matrix6` (function, line 1991) `static int parse_matrix6(const char *p, size_t argn, double m6[6])`
  - `split_top_args` (function, line 2023) `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,
               ...`
  - `translate3d` (function, line 2053) `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine
 * renders z as nothing,...`
  - `translate3d` (function, line 2303) `* translate3d()/translateZ() flatten to their 2D projection. Any other
 * transform function (per...`
  - `origin_component` (function, line 2496) `static int origin_component(const char *tok, int axis, int *out)`
  - `expand_transform_origin` (function, line 2522) `static int expand_transform_origin(const char *val, css_decl *dst, int cap)`
  - `expand_gap` (function, line 2554) `static int expand_gap(const char *val, css_decl *dst, int cap)`
  - `ignored` (function, line 2573) `* engine slot and is ignored (documented simplification, like list-style's
 * ignored tokens). An...`
  - `property` (function, line 2608) `* error drops the whole property (fail closed). */
static int expand_clip(const char *val, css_de...`
  - `shorthand` (function, line 2651) `* generic bucket keeps the rest of the shorthand (same net effect as the
 * font-family longhand ...`
  - `interpret_prop_dispatch` (function, line 2722) `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,
   ...`
  - `grammar` (function, line 2740) `* grammar (`justify`/`distribute`) is not `justify-content`'s. Guessing
     * there would be inv...`
  - `wide_claim` (function, line 3293) `static int wide_claim(const char *prop, css_decl *dst, int cap,
                      char (*urlt...`
  - `interpret_prop` (function, line 3333) `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,
            ...`
  - `drop_copy_text` (function, line 3360) `static void drop_copy_text(char *dst, size_t cap, const char *src)`
  - `drop_record` (function, line 3379) `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)`
  - `raw_add` (function, line 3405) `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)`
  - `interpret_decls` (function, line 3518) `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,
               ...`
  - `add_rule` (function, line 3562) `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,
                     siz...`
  - `skip_at_rule` (function, line 3649) `static size_t skip_at_rule(const char *s, size_t i, size_t n)`
  - `block_end` (function, line 3665) `static size_t block_end(const char *s, size_t open, size_t n)`
  - `at_is_media` (function, line 3687) `static int at_is_media(const char *s, size_t i, size_t n)`
  - `at_keyword` (function, line 3698) `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)`
  - `supports_selector_ok` (function, line 3723) `static int supports_selector_ok(void *ctx, const char *sel)`
  - `supports_matches` (function, line 3732) `static int supports_matches(const char *s, size_t a, size_t b)`
  - `layer_register` (function, line 3786) `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,
                     ...`
  - `collect_custom_props_scoped` (function, line 3829) `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,
                ...`
  - `parse_block` (function, line 3904) `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                 ...`
  - `rem_ident_ch` (function, line 4156) `static int rem_ident_ch(char c)`
  - `rem_num_starts_after` (function, line 4164) `static int rem_num_starts_after(char prev)`
  - `rem_emit_px` (function, line 4174) `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)`
  - `rem_rebase` (function, line 4204) `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)`
  - `sheet_rewind` (function, line 4271) `static void sheet_rewind(css_sheet *sh)`
  - `sheet_root_font_px` (function, line 4314) `static double sheet_root_font_px(const css_sheet *sh)`
  - `strip_comments` (function, line 4322) `static char *strip_comments(const char *text, size_t len, size_t *outlen)`
  - `var` (function, line 4332) `* collected and forty var() declarations -- font sizes, widths, radii, the
     * whole theme -- ...`
  - `css_parse` (function, line 4357) `css_status css_parse(const char *text, size_t len, css_sheet **out)`
  - `css_parse_media` (function, line 4361) `css_status css_parse_media(const char *text, size_t len, const css_media *media,
                ...`
  - `css_parse_scoped` (function, line 4366) `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,
               ...`
  - `css_parse_logged` (function, line 4371) `css_status css_parse_logged(const char *text, size_t len, const css_media *media,
               ...`
  - `css_free` (function, line 4441) `void css_free(css_sheet *s)`
  - `apply_decl` (function, line 4458) `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...`
  - `parent` (function, line 4496) `* property from the parent (`inherit`), and an unset non-inherited one
         * stands at its i...`
  - `computed_font_size` (function, line 4831) `static double computed_font_size(const css_style *o, const css_element *el)`
  - `cand_cmp` (function, line 4847) `static int cand_cmp(const void *pa, const void *pb)`
  - `apply_var_source` (function, line 4912) `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
        ...`
  - `apply_rule` (function, line 4938) `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...`
  - `fold_font_relative` (function, line 4976) `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,
                         ...`
  - `css_resolve_el` (function, line 5005) `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         ...`
  - `css_resolve_el_ex` (function, line 5014) `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,
                      ...`
  - `css_resolve_pseudo` (function, line 5020) `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)`
  - `resolve_core` (function, line 5030) `static css_style resolve_core(const css_sheet *sheet, const css_element *el,
                    ...`
  - `css_resolve` (function, line 5238) `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                  ...`
  - `NULL` (function, line 5262) `* Sheet can be NULL (inline style, no @keyframes). */
void css_resolve_anim_keyframes(css_style *...`
  - `css_font_face_count` (function, line 5294) `size_t css_font_face_count(const css_sheet *sheet)`
  - `css_font_face_at` (function, line 5298) `int css_font_face_at(const css_sheet *sheet, size_t i,
                     char *family, size_t ...`
  - `css_parse_inline` (function, line 5308) `css_style css_parse_inline(const char *style, size_t len)`
  - `emit` (function, line 59) `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand at 12), so that finishing with this much slack * proves no declaration in the rule w`
  - `css_decl` (function, line 86) `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);`
  - `order` (function, line 1216) `* Lengths in declaration order (dx, dy, optional blur >= 0);`
  - `function` (function, line 1218) `* function (the rest of the list still applies). Emits the whole * 4-decl group in lock-step or nothing. */ const char *body = filter_paren_body(tok, "drop-shadow(", 12);`
  - `blur` (function, line 1251) `* consumes ONLY blur(Npx);`
  - `empty` (function, line 1407) `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and the drops gate would count * a conforming declaration as a discard. */ if (csel_ci_`
  - `column` (function, line 1608) `* column (`flex: 1 1 0%`);`
  - `matrix` (function, line 1961) `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands on skx only (the decomposition * convention: a shear pair has a family of factoriza`
  - `LIST` (function, line 2046) `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose into one * affine matrix, QR-decomposed into the seven slots (shared with matrix()). `
  - `translateX` (function, line 2295) `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc numbers all fail closed, same as any other * box-model length here);`
  - `parse_angle_deg` (function, line 2299) `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);`
  - `expand_transform_list` (function, line 2302) `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);`
  - `caller` (function, line 2710) `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached a branch of the * dispatch below, which is what separates "not implemented" from "im`
  - `slots` (function, line 2832) `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return emit_len(dst, cap, P_INSET_TOP, val, 1, 1);`
  - `sentinel` (function, line 2944) `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);`
  - `csel_substr` (function, line 3720) `return known && csel_substr(val, "var(", 1);`
  - `page_view` (function, line 4464) `* the generated text reaches page_view (which materialises it as a synthetic * run);`
  - `CSS_INIT_SELS` (macro, line 46) `#define CSS_INIT_SELS`
  - `CSS_INIT_DECLS` (macro, line 47) `#define CSS_INIT_DECLS`
  - `CSS_DECL_SLOTS_MIN` (macro, line 62) `#define CSS_DECL_SLOTS_MIN`
  - `CSS_INIT_RULES` (macro, line 63) `#define CSS_INIT_RULES`
  - `CSS_SELS_PER_GROUP` (macro, line 64) `#define CSS_SELS_PER_GROUP`
  - `CSS_INLINE_DECLS` (macro, line 65) `#define CSS_INLINE_DECLS`
  - `P_META_CUSTOM` (macro, line 78) `#define P_META_CUSTOM`
  - `P_META_VARSRC` (macro, line 79) `#define P_META_VARSRC`
  - `CSS_MAX_RAW` (macro, line 82) `#define CSS_MAX_RAW`
  - `CSS_MAX_FONT_FACES` (macro, line 150) `#define CSS_MAX_FONT_FACES`
  - `AUTO_REJECT` (macro, line 253) `#define AUTO_REJECT`
  - `AUTO_VALUE` (macro, line 254) `#define AUTO_VALUE`
  - `AUTO_RESET` (macro, line 255) `#define AUTO_RESET`
  - `AUTO_RESET_NONE` (macro, line 256) `#define AUTO_RESET_NONE`
  - `CSS_MEDIA_MAX_DEPTH` (macro, line 3820) `#define CSS_MEDIA_MAX_DEPTH`
  - `CSS_VAR_POOL` (macro, line 4908) `#define CSS_VAR_POOL`
- Depends on: `include/css.h`, `include/css_atrule.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_gradient.h`, `include/css_length.h`, `include/css_mq.h`, `include/css_select.h`, `include/css_text.h`, `include/css_values.h`, `include/css_vars.h`, `include/flex_layout.h`

## src/css_atrule.c
- Layer: business_logic
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
  - `repeat` (function, line 272) `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill|...) / repeat(auto-fit|...) need an available width this pure * parser does not have, so they fail the W`
  - `accepts` (function, line 452) `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further than interp_len already can). Bounded: * the whole expression already lives inside o`
  - `min` (function, line 550) `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the element to zero width. Dropping the declaration * leaves the element at its content size, `
  - `term` (function, line 866) `* the same expression and failed closed on the percentage term (its property * may not accept one);`
  - `CSS_CALC_MAX_DEPTH` (macro, line 460) `#define CSS_CALC_MAX_DEPTH`
  - `CSS_MATHFN_MAX_ARGS` (macro, line 464) `#define CSS_MATHFN_MAX_ARGS`
  - `AUTO_REJECT` (macro, line 932) `#define AUTO_REJECT`
  - `AUTO_VALUE` (macro, line 933) `#define AUTO_VALUE`
  - `AUTO_RESET` (macro, line 934) `#define AUTO_RESET`
  - `AUTO_RESET_NONE` (macro, line 938) `#define AUTO_RESET_NONE`
- Depends on: `include/css.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`

## src/css_chain.c
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
- Layer: infrastructure
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
  - `pseudo_matches` (function, line 726) `static int pseudo_matches(const css_pseudo_match *pm, const css_element *el, const css_sel *sel, const char *target_id, int allow_pseudo_el);`
  - `HAS_MAX_DEPTH` (macro, line 839) `#define HAS_MAX_DEPTH`
- Depends on: `include/css_select.h`

## src/css_text.c
- Layer: utility
- Doc: --- text-presentation extensions (Hito 23b-6) ---
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

## src/download.c
- Layer: utility
- Language: c
- Symbols:
  - `lc` (function, line 13) `static int lc(int c)`
  - `ci_find` (function, line 19) `static const char *ci_find(const char *hay, const char *needle)`
  - `media_type` (function, line 33) `static void media_type(const char *content_type, char *buf, size_t bufsz)`
  - `dl_should_download` (function, line 47) `int dl_should_download(const char *content_type, const char *content_disposition)`
  - `dl_ext_for_type` (function, line 58) `const char *dl_ext_for_type(const char *content_type)`
  - `copy_span` (function, line 85) `static void copy_span(const char *src, const char *end, char *buf, size_t bufsz)`
  - `extract_disposition_name` (function, line 96) `static int extract_disposition_name(const char *cd, char *buf, size_t bufsz)`
  - `extract_url_name` (function, line 134) `static int extract_url_name(const char *url, char *buf, size_t bufsz)`
  - `has_extension` (function, line 148) `static int has_extension(const char *name)`
  - `dl_pick_name` (function, line 153) `dl_status dl_pick_name(const char *url, const char *content_disposition,
                       c...`
  - `dl_build_path` (function, line 195) `dl_status dl_build_path(const char *dir, const char *name, char *out, size_t outsz)`
  - `dl_check_size` (function, line 213) `dl_status dl_check_size(size_t len)`
- Depends on: `include/download.h`, `include/pdf_export.h`

## src/flex_layout.c
- Layer: presentation
- Language: c
- Symbols:
  - `nn` (function, line 18) `static double nn(double v)`
  - `fx_flex_line` (function, line 22) `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                ...`
  - `fx_grid_columns` (function, line 127) `fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          doubl...`
  - `fx_grid_columns_weighted` (function, line 132) `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                      ...`
  - `fx_grid_place_span` (function, line 166) `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                      ...`
  - `fx_grid_area_hash` (function, line 270) `unsigned fx_grid_area_hash(const char *name)`
  - `area_token_is_null_cell` (function, line 294) `static int area_token_is_null_cell(const char *tok, size_t len)`
  - `fx_grid_areas_parse` (function, line 300) `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)`
  - `fx_grid_area_rect` (function, line 375) `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,
                            int ...`
  - `float_pack_impl` (function, line 417) `static fx_status float_pack_impl(const double *width, const int *side, size_t n,
                ...`
  - `fx_float_insets` (function, line 457) `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,
                 ...`
  - `fx_float_pack` (function, line 497) `fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        d...`
  - `fx_float_pack_wrap` (function, line 502) `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,
                    ...`
  - `fx_grid_cell` (function, line 544) `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)`
  - `fx_auto_margins` (function, line 556) `fx_status fx_auto_margins(fx_result *res, size_t n, const unsigned char *auto_l,
                ...`
  - `fx_auto_min_size` (function, line 579) `double fx_auto_min_size(double min_content, double basis, double author_min,
                    ...`
  - `fx_multicol_used` (function, line 593) `fx_status fx_multicol_used(double avail_w, int column_count, double column_width,
               ...`
  - `fx_multicol_balance` (function, line 630) `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,
                        ...`
  - `fx_justify_name` (function, line 661) `const char *fx_justify_name(fx_justify j)`
  - `fx_column_place` (function, line 673) `fx_status fx_column_place(const double *h, const double *grow, size_t n, double gap,
            ...`
  - `fx_column_place_m` (function, line 680) `fx_status fx_column_place_m(const double *h, const double *grow, const int *mauto,
              ...`
  - `fx_cross_offset` (function, line 741) `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r)`
  - `FX_EPS` (macro, line 15) `#define FX_EPS`
- Depends on: `include/flex_layout.h`

## src/form.c
- Layer: data_access
- Language: c
- Symbols:
  - `put_char` (function, line 17) `static int put_char(char *out, size_t outsz, size_t *pos, char c)`
  - `enc_component` (function, line 25) `static int enc_component(const char *s, char *out, size_t outsz, size_t *pos)`
  - `fm_encode` (function, line 43) `fm_status fm_encode(const fm_field *fields, size_t n,
                    char *out, size_t outsz...`
  - `copy_fit` (function, line 66) `static int copy_fit(char *dst, size_t dstsz, const char *src)`
  - `clean_action` (function, line 75) `static int clean_action(const char *action, char *out, size_t outsz)`
  - `strip_query` (function, line 93) `static void strip_query(char *url)`
  - `resolve_target` (function, line 101) `static fm_block_reason resolve_target(const char *base, const char *act,
                        ...`
  - `fm_build` (function, line 120) `fm_status fm_build(const char *base, const char *action, fm_method method,
                   con...`
- Depends on: `include/form.h`

## src/frame_clock.c
- Layer: utility
- Language: c
- Symbols:
  - `fc_set_active` (function, line 16) `void fc_set_active(fc_clock *c, int active)`
  - `fc_needs_tick` (function, line 21) `int fc_needs_tick(const fc_clock *c)`
  - `fc_interval_ms` (function, line 26) `int fc_interval_ms(const fc_clock *c)`
  - `FC_DEFAULT_INTERVAL_MS` (macro, line 8) `#define FC_DEFAULT_INTERVAL_MS`
- Depends on: `include/frame_clock.h`

## src/freebug.c
- Layer: utility
- Language: c
- Symbols:
  - `fb_buffer_init` (function, line 15) `void fb_buffer_init(fb_buffer *b)`
  - `fb_buffer_push` (function, line 19) `int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)`
  - `fb_buffer_push_loc` (function, line 23) `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len,
                   ...`
  - `fb_buffer_reset` (function, line 78) `void fb_buffer_reset(fb_buffer *b)`
  - `fb_buffer_free` (function, line 91) `void fb_buffer_free(fb_buffer *b)`
  - `fb_buffer_count` (function, line 101) `size_t fb_buffer_count(const fb_buffer *b)`
  - `fb_buffer_at` (function, line 105) `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)`
  - `fb_level_name` (function, line 110) `const char *fb_level_name(int level)`
  - `whole` (function, line 5) `* FB_MAX_TOTAL_BYTES is dropped whole (overflow flag raised, prior entries kept);`
- Depends on: `include/freebug.h`

## src/freedom.c
- Layer: utility
- Language: c
- Symbols:
  - `print_usage` (function, line 47) `static void print_usage(FILE *fp, const char *prog)`
  - `is_https_url` (function, line 73) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 77) `static int is_http_url(const char *s)`
  - `is_overlay_http` (function, line 82) `static int is_overlay_http(const char *s)`
  - `now_us` (function, line 136) `static uint64_t now_us(void)`
  - `timings_ensure_init` (function, line 142) `static void timings_ensure_init(void)`
  - `timings_enabled` (function, line 146) `static int timings_enabled(void)`
  - `timings_dump` (function, line 150) `static void timings_dump(void)`
  - `user_impersonate_enabled` (function, line 198) `static int user_impersonate_enabled(void)`
  - `read_file` (function, line 205) `static char *read_file(const char *path, size_t *out_len)`
  - `headless_load_hosts` (function, line 223) `static void headless_load_hosts(void)`
  - `is_blank_text` (function, line 253) `static int is_blank_text(const char *s)`
  - `print_doc` (function, line 266) `static void print_doc(const rd_doc *doc)`
  - `print_console` (function, line 359) `static void print_console(const fb_buffer *log)`
  - `print_dom` (function, line 376) `static void print_dom(const rd_doc *doc)`
  - `print_dom_css` (function, line 391) `static void print_dom_css(const rd_doc *doc)`
  - `headless_fetch` (function, line 415) `static int headless_fetch(void *ctx, const char *method, const char *url,
                       ...`
  - `foldback_cookies` (function, line 477) `static void foldback_cookies(const char *url, const char *jar)`
  - `print_css_drops` (function, line 501) `static void print_css_drops(const char *html, size_t len)`
  - `render_page` (function, line 532) `static int render_page(const char *html, size_t len, const char *top_url,
                       ...`
  - `sf_reason` (function, line 757) `static const char *sf_reason(sf_status ss)`
  - `fetch_and_render_one` (function, line 776) `static int fetch_and_render_one(const char *url, char **out_nav)`
  - `elsewhere` (function, line 837) `* page whose script immediately forwards elsewhere (e.g. a search engine's
 * JS-capability inter...`
  - `parent` (function, line 863) `* gated by the parent (ln_resolve: a local target stays under the document's
 * directory, a remo...`
  - `run_headless` (function, line 900) `static int run_headless(const char *target)`
  - `video_fetch_with_fallback` (function, line 936) `static sf_status video_fetch_with_fallback(const char *url, sf_config *cfg,
                     ...`
  - `run_dump_video` (function, line 1047) `static int run_dump_video(const char *url)`
  - `main` (function, line 1066) `int main(int argc, char **argv)`
  - `gets` (function, line 411) `* gate a click gets (https-only, no downgrade, no foreign scheme), so relative * subresources work. Realm-routed (fail-closed);`
  - `pool` (function, line 592) `* the pool (unconsumed results freed, in-flight fetches joined). */ tab_set_fetcher(t, headless_fetch, (void *)(uintptr_t)top_url);`
  - `only` (function, line 645) `* styling for the local render only (no network). --images enables image loading * AND rendering, including remote fetches (so --download-png --images actually * shows images in the bitmap). */ rdp_ca`
  - `BLOCKED` (function, line 802) `* is BLOCKED (fail closed), never leaked over the clearnet. */ nr_route route = nr_route_for(url, global_net);`
  - `_POSIX_C_SOURCE` (macro, line 9) `#define _POSIX_C_SOURCE`
  - `_DEFAULT_SOURCE` (macro, line 10) `#define _DEFAULT_SOURCE`
  - `EXIT_OK` (macro, line 43) `#define EXIT_OK`
  - `EXIT_ERROR` (macro, line 44) `#define EXIT_ERROR`
  - `EXIT_USAGE` (macro, line 45) `#define EXIT_USAGE`
  - `CSS_DROPS_REPORT_MAX` (macro, line 161) `#define CSS_DROPS_REPORT_MAX`
  - `HL_JS_NAV_MAX` (macro, line 772) `#define HL_JS_NAV_MAX`
- Depends on: `include/dom_debug.h`, `include/freebug.h`, `include/hls.h`, `include/hostblock.h`, `include/html_parse.h`, `include/js_policy.h`, `include/link_nav.h`, `include/media_decoder.h`, `include/net_realm.h`, `include/page_view.h`, `include/perf_trace.h`, `include/prefetch.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/tab.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/webcaps.h`

## src/hls.c
- Layer: utility
- Language: c
- Symbols:
  - `last_char` (function, line 38) `static const char *last_char(const char *s, size_t n, int c)`
  - `parse_attr_long` (function, line 48) `static int parse_attr_long(const char *attrs, const char *end,
                           const c...`
  - `parse_attr_resolution` (function, line 62) `static void parse_attr_resolution(const char *attrs, const char *end,
                           ...`
  - `hls_parse` (function, line 80) `hls_status hls_parse(const char *text, size_t len, hls_playlist **out)`
  - `hls_select_variant` (function, line 202) `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h)`
  - `hls_resolve_url` (function, line 223) `size_t hls_resolve_url(const char *base_url, const char *segment_url,
                       char...`
  - `hls_playlist_free` (function, line 253) `void hls_playlist_free(hls_playlist *pl)`
  - `name` (function, line 46) `* attr is the attribute name (e.g. "BANDWIDTH=");`
  - `_GNU_SOURCE` (macro, line 21) `#define _GNU_SOURCE`
  - `_POSIX_C_SOURCE` (macro, line 22) `#define _POSIX_C_SOURCE`
- Depends on: `include/hls.h`

## src/hostblock.c
- Layer: utility
- Language: c
- Symbols:
  - `hb_table` (struct, line 24)
  - `hb_set` (struct, line 30)
  - `table_probe` (function, line 38) `static size_t table_probe(const hb_table *t, const char *key, size_t klen)`
  - `table_grow` (function, line 49) `static int table_grow(hb_table *t, size_t newcap)`
  - `table_insert` (function, line 71) `static int table_insert(hb_table *t, const char *key, size_t klen)`
  - `table_contains` (function, line 92) `static int table_contains(const hb_table *t, const char *key)`
  - `table_free` (function, line 98) `static void table_free(hb_table *t)`
  - `lower` (function, line 107) `static char lower(char c)`
  - `is_ip_token` (function, line 113) `static int is_ip_token(const char *s, size_t n)`
  - `is_domain_char` (function, line 122) `static int is_domain_char(char c)`
  - `hb_new` (function, line 144) `hb_set *hb_new(void)`
  - `hb_free` (function, line 149) `void hb_free(hb_set *s)`
  - `hb_load` (function, line 156) `hb_status hb_load(hb_set *s, const char *text, hb_list list)`
  - `hb_check` (function, line 193) `hb_decision hb_check(const hb_set *s, const char *host)`
  - `hb_is_allowlisted` (function, line 218) `int hb_is_allowlisted(const hb_set *s, const char *host)`
  - `hb_count` (function, line 238) `size_t hb_count(const hb_set *s, hb_list list)`
  - `HB_MAX_HOST` (macro, line 19) `#define HB_MAX_HOST`
  - `HB_INIT_CAP` (macro, line 20) `#define HB_INIT_CAP`
- Depends on: `include/hostblock.h`, `include/util.h`

## src/hostedit.c
- Layer: infrastructure
- Language: c
- Symbols:
  - `suggest_ctx` (struct, line 136)
  - `he_lower` (function, line 12) `static char he_lower(char c)`
  - `is_label_char` (function, line 16) `static int is_label_char(char c)`
  - `valid_host` (function, line 22) `static int valid_host(const char *host, size_t n)`
  - `he_make_line` (function, line 41) `he_status he_make_line(const char *host, char *out, size_t cap)`
  - `is_ip_token` (function, line 67) `static int is_ip_token(const char *ts, const char *te)`
  - `he_scan` (function, line 80) `static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), void *ctx)`
  - `has_host_cb` (function, line 105) `static int has_host_cb(const char *ts, size_t tl, void *ctx)`
  - `he_text_has_host` (function, line 109) `int he_text_has_host(const char *text, const char *host)`
  - `contains_ci` (function, line 115) `static int contains_ci(const char *hs, size_t hl, const char *needle)`
  - `starts_with_ci` (function, line 128) `static int starts_with_ci(const char *hs, size_t hl, const char *pfx)`
  - `suggest_cb` (function, line 144) `static int suggest_cb(const char *ts, size_t tl, void *vctx)`
  - `he_suggest` (function, line 164) `int he_suggest(const char *text, const char *query,
               char results[][HE_MAX_HOST + 1...`
- Depends on: `include/hostedit.h`

## src/html_parse.c
- Layer: utility
- Language: c
- Symbols:
  - `hp_document` (struct, line 21)
  - `dup_bytes` (function, line 27) `static char *dup_bytes(const lxb_char_t *src, size_t len)`
  - `node_next` (function, line 37) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)`
  - `attr_is_event_handler` (function, line 47) `static int attr_is_event_handler(const lxb_dom_attr_t *attr)`
  - `node_is_script` (function, line 54) `static int node_is_script(const lxb_dom_node_t *node)`
  - `strip_scripts` (function, line 60) `static void strip_scripts(lxb_html_document_t *document)`
  - `type_is` (function, line 100) `static int type_is(const lxb_char_t *t, size_t len, const char *word)`
  - `type_is_module` (function, line 117) `static int type_is_module(const lxb_char_t *t, size_t len)`
  - `script_classify` (function, line 121) `static int script_classify(const lxb_dom_node_t *n,
                           const lxb_char_t *...`
  - `hp_extract_script_list` (function, line 164) `hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count)`
  - `hp_free_scripts` (function, line 238) `void hp_free_scripts(hp_script *scripts, size_t count)`
  - `attr_has_token_ci` (function, line 251) `static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle)`
  - `link_is_active_stylesheet` (function, line 272) `static int link_is_active_stylesheet(lxb_dom_element_t *el,
                                     ...`
  - `hp_extract_stylesheet_hrefs` (function, line 294) `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count)`
  - `hp_free_stylesheet_hrefs` (function, line 328) `void hp_free_stylesheet_hrefs(char **hrefs, size_t count)`
  - `strip_event_handlers` (function, line 334) `static void strip_event_handlers(lxb_html_document_t *document)`
  - `hp_config_default` (function, line 357) `hp_config hp_config_default(void)`
  - `hp_validate_input` (function, line 365) `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg)`
  - `hp_parse` (function, line 375) `hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out)`
  - `hp_element_count` (function, line 409) `size_t hp_element_count(const hp_document *doc)`
  - `hp_script_count` (function, line 419) `size_t hp_script_count(const hp_document *doc)`
  - `hp_event_handler_count` (function, line 429) `size_t hp_event_handler_count(const hp_document *doc)`
  - `hp_extract_text` (function, line 445) `char *hp_extract_text(const hp_document *doc, size_t *out_len)`
  - `hp_get_title` (function, line 464) `char *hp_get_title(const hp_document *doc, size_t *out_len)`
  - `hp_free` (function, line 479) `void hp_free(char *buf)`
  - `hp_document_free` (function, line 483) `void hp_document_free(hp_document *doc)`
  - `hp_document_root` (function, line 489) `const void *hp_document_root(const hp_document *doc)`
  - `lxb_dom_element_has_attribute` (function, line 230) `&& lxb_dom_element_has_attribute(sel, (const lxb_char_t *)"nomodule", 8);`
  - `_POSIX_C_SOURCE` (macro, line 9) `#define _POSIX_C_SOURCE`
- Depends on: `include/dom.h`, `include/html_parse.h`, `include/util.h`

## src/image_decode.c
- Layer: utility
- Language: c
- Symbols:
  - `jpeg_err_ctx` (struct, line 153)
  - `gif_reader` (struct, line 255)
  - `gif_bits` (struct, line 290)
  - `read_be32` (function, line 52) `static uint32_t read_be32(const uint8_t *p)`
  - `img_png_dimensions` (function, line 57) `img_status img_png_dimensions(const uint8_t *bytes, size_t len,
                              uin...`
  - `img_dimensions_ok` (function, line 68) `int img_dimensions_ok(uint32_t w, uint32_t h)`
  - `img_fit` (function, line 76) `void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,
             double *out_w, do...`
  - `premultiply` (function, line 90) `static void premultiply(uint8_t *data, size_t pixels)`
  - `img_decode_png` (function, line 102) `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `jpeg_error_longjmp` (function, line 158) `static void jpeg_error_longjmp(j_common_ptr cinfo)`
  - `jpeg_silence` (function, line 164) `static void jpeg_silence(j_common_ptr cinfo)`
  - `img_decode_jpeg` (function, line 166) `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `gr_u8` (function, line 260) `static int gr_u8(gif_reader *r, uint8_t *out)`
  - `gr_u16le` (function, line 266) `static int gr_u16le(gif_reader *r, uint16_t *out)`
  - `gr_skip` (function, line 273) `static int gr_skip(gif_reader *r, size_t n)`
  - `gr_skip_subblocks` (function, line 280) `static int gr_skip_subblocks(gif_reader *r)`
  - `gb_next_code` (function, line 298) `static int gb_next_code(gif_bits *b, unsigned width, unsigned *out)`
  - `gif_deinterlace_row` (function, line 319) `static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh)`
  - `gif_put_pixel` (function, line 334) `static void gif_put_pixel(uint32_t *canvas, uint32_t cw, uint32_t ch,
                          u...`
  - `img_decode_gif` (function, line 354) `img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `img_decode_webp` (function, line 520) `img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `img_decode` (function, line 553) `img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `img_pixels_free` (function, line 566) `void img_pixels_free(img_pixels *p)`
  - `img_format_name` (function, line 575) `const char *img_format_name(img_format f)`
  - `exit` (function, line 6) `* malformed stream fails closed instead of calling exit(). GIF uses an own pure-C * bounded LZW decoder (no giflib). WebP uses libwebp's WebPDecodeBGRA in-memory * API. Output is tightly packed BGRA (`
  - `PNG_IHDR_MIN` (macro, line 34) `#define PNG_IHDR_MIN`
  - `GIF_LZW_MAX_CODES` (macro, line 253) `#define GIF_LZW_MAX_CODES`
- Depends on: `include/image_decode.h`

## src/import_map.c
- Layer: utility
- Language: c
- Symbols:
  - `im_entry` (struct, line 19)
  - `im_map` (struct, line 25)
  - `jr` (struct, line 34)
  - `scope` (type_alias, line 18) `typedef struct im_entry { int scope;`
  - `ws` (function, line 39) `static void ws(jr *r)`
  - `eat` (function, line 44) `static int eat(jr *r, char c)`
  - `hex4` (function, line 50) `static int hex4(const char *s, uint32_t *out)`
  - `put_utf8` (function, line 64) `static size_t put_utf8(char *o, uint32_t cp)`
  - `str` (function, line 78) `static char *str(jr *r)`
  - `skip` (function, line 128) `static void skip(jr *r, int depth)`
  - `url_like` (function, line 156) `static int url_like(const char *s)`
  - `dup_s` (function, line 168) `static char *dup_s(const char *s)`
  - `clear` (function, line 175) `static void clear(im_map *m)`
  - `add` (function, line 185) `static int add(im_map *m, int scope, const char *key, const char *addr, const char *doc_url,
    ...`
  - `specifier_map` (function, line 209) `static void specifier_map(jr *r, im_map *m, int scope, const char *doc_url,
                     ...`
  - `im_parse` (function, line 225) `im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn resolve, void *ctx)`
  - `match` (function, line 272) `static int match(const im_map *m, int scope, const char *key, char *out, size_t outsz)`
  - `im_resolve` (function, line 301) `int im_resolve(const im_map *m, const char *base, const char *specifier,
               im_url_fn...`
  - `im_count` (function, line 339) `size_t im_count(const im_map *m)`
  - `im_free` (function, line 343) `void im_free(im_map *m)`
  - `IM_MAX_DEPTH` (macro, line 16) `#define IM_MAX_DEPTH`
  - `IM_URL_MAX` (macro, line 17) `#define IM_URL_MAX`
- Depends on: `include/import_map.h`

## src/interp.c
- Layer: utility
- Language: c
- Symbols:
  - `sample_bezier_x` (function, line 18) `static double sample_bezier_x(double t, double cx1, double cx2)`
  - `sample_bezier_dx` (function, line 23) `static double sample_bezier_dx(double t, double cx1, double cx2)`
  - `sample_bezier_y` (function, line 29) `static double sample_bezier_y(double t, double cy1, double cy2)`
  - `solve_bezier_t` (function, line 35) `static double solve_bezier_t(double x, double cx1, double cx2)`
  - `ip_ease` (function, line 55) `double ip_ease(double t, const ip_ease_fn *fn)`
  - `ip_ease` (function, line 64) `case IP_EASE_EASE:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_ease` (function, line 70) `case IP_EASE_EASE_IN:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_ease` (function, line 76) `case IP_EASE_EASE_OUT:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_ease` (function, line 82) `case IP_EASE_EASE_IN_OUT:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_lerp` (function, line 134) `double ip_lerp(double a, double b, double t)`
  - `ip_lerp_color` (function, line 139) `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t)`
  - `ip_interp` (function, line 162) `double ip_interp(ip_val_kind kind, double a, double b, double t)`
  - `ip_kf_interp` (function, line 175) `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf,
                    int n_kf, do...`
  - `ip_anim_init` (function, line 196) `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease,
                  const ip_...`
  - `anim_effective_dir_for` (function, line 222) `static int anim_effective_dir_for(const ip_anim *a, int iter)`
  - `anim_effective_dir` (function, line 232) `static int anim_effective_dir(const ip_anim *a)`
  - `ip_anim_tick` (function, line 236) `int ip_anim_tick(ip_anim *a, double dt_ms)`
  - `ip_anim_current` (function, line 282) `double ip_anim_current(const ip_anim *a)`
  - `ip_anim_done` (function, line 320) `int ip_anim_done(const ip_anim *a)`
- Depends on: `include/interp.h`

## src/js_dom.c
- Layer: utility
- Language: c
- Symbols:
  - `jd_method` (struct, line 428)
  - `jd_opaque_get` (function, line 27) `jd_opaque *jd_opaque_get(JSContext *ctx)`
  - `jd_idx` (function, line 31) `dom_index *jd_idx(JSContext *ctx)`
  - `jd_handle` (function, line 40) `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out)`
  - `jd_handle_or_null` (function, line 47) `JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h)`
  - `m_node_count` (function, line 53) `static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `m_get_element_by_id` (function, line 59) `static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val,
                       ...`
  - `jd_query_list` (function, line 70) `static JSValue jd_query_list(JSContext *ctx, JSValueConst arg, int by_class)`
  - `m_get_by_tag` (function, line 100) `static JSValue m_get_by_tag(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `m_get_by_class` (function, line 106) `static JSValue m_get_by_class(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_tag_name` (function, line 112) `static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_get_attribute` (function, line 122) `static JSValue m_get_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
  - `m_parent` (function, line 135) `static JSValue m_parent(JSContext *ctx, JSValueConst this_val,
                        int argc, ...`
  - `m_first_child` (function, line 143) `static JSValue m_first_child(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_node_kind` (function, line 152) `static JSValue m_node_kind(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_child_node` (function, line 159) `static JSValue m_child_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_sibling_node` (function, line 166) `static JSValue m_sibling_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_create_char` (function, line 174) `static JSValue m_create_char(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_next_sibling` (function, line 188) `static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_precedes` (function, line 196) `static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_text_content` (function, line 207) `static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_set_text` (function, line 217) `static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_get_title` (function, line 231) `static JSValue m_get_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
  - `m_set_title` (function, line 239) `static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
  - `m_create_element` (function, line 252) `static JSValue m_create_element(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_append_child` (function, line 264) `static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_move_children` (function, line 275) `static JSValue m_move_children(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_clone_node` (function, line 289) `static JSValue m_clone_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_insert_before` (function, line 299) `static JSValue m_insert_before(JSContext *ctx, JSValueConst this_val,
                           ...`
  - `m_remove_child` (function, line 311) `static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_set_attribute` (function, line 320) `static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
  - `m_remove_attribute` (function, line 336) `static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,
                        ...`
  - `m_set_inner_html` (function, line 348) `static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_get_inner_html` (function, line 364) `static JSValue m_get_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_rect` (function, line 396) `static JSValue m_rect(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_query_selector` (function, line 437) `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_query_selector_all` (function, line 450) `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,
                      ...`
  - `m_matches` (function, line 479) `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,
                         int argc...`
  - `m_closest` (function, line 491) `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,
                         int argc...`
  - `m_attr_names` (function, line 503) `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `attrNames` (function, line 610) `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so
     * a missing '...`
  - `js_env` (function, line 1199) `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the
 * document shim (uses...`
  - `jd_install` (function, line 1721) `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)`
  - `fails` (function, line 1798) `* cap is reached or an allocation fails (caller stops), else 0. */
static int cb_append(char **bu...`
  - `jd_install_console` (function, line 1912) `jd_status jd_install_console(js_context *ctx, fb_buffer *log)`
  - `jd_set_cookies` (function, line 1949) `jd_status jd_set_cookies(js_context *ctx, const char *cookies)`
  - `jd_get_cookies` (function, line 1969) `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)`
  - `jd_set_geometry` (function, line 1992) `jd_status jd_set_geometry(js_context *ctx, const jg_table *geom)`
  - `table` (function, line 571) `* a table (dom.viewport() non-null);`
  - `scripts` (function, line 746) `* player scripts (canPlayType feature-detection, play/pause, muted/loop * reflection, buffered ranges) run without throwing. No network, no real * playback in the worker -- actual decoding happens in `
  - `enough` (function, line 909) `* enough (cloneNode/lastChild/removeChild/insertBefore) that library feature * detection does not throw: jQuery clones a fragment twice and reads .lastChild * (b.checkClone);`
  - `ms` (function, line 1045) `* due is the remaining virtual ms (the trusted parent advances the clock via * OP_TICK -> __tickTimers(elapsed);`
  - `empty` (function, line 1193) `* inert: DOM interface constructors are empty (instanceof yields false, harmless);`
  - `fire` (function, line 1194) `* observers never fire (no observation -> no info leak);`
  - `_GNU_SOURCE` (macro, line 10) `#define _GNU_SOURCE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `include/web_storage.h`, `src/js_dom_ext.h`, `src/js_dom_internal.h`, `src/js_location_internal.h`

## src/js_dom_ext.c
- Layer: utility
- Language: c
- Symbols:
  - `run` (function, line 326) `static int run(JSContext *ctx, const char *src, size_t len, const char *name)`
  - `jdx_install` (function, line 334) `int jdx_install(JSContext *ctx)`
- Depends on: `src/js_dom_ext.h`

## src/js_dom_ext.h
- Layer: utility
- Doc: Private to js_dom.c / js_dom_ext.c: installs the DOM Standard extras (tree
- Language: h
- Symbols:
  - `jdx_install` (function, line 10) `int jdx_install(JSContext *ctx);`
  - `FREEDOM_JS_DOM_EXT_H` (macro, line 2) `#define FREEDOM_JS_DOM_EXT_H`
- Imported by: `src/js_dom.c`, `src/js_dom_ext.c`

## src/js_dom_internal.h
- Layer: utility
- Doc: Private to the js_dom family (js_dom.c, js_fetch.c, js_events.c, js_embed.c): the context accessors every native needs. 
- Language: h
- Symbols:
  - `jd_opaque_get` (function, line 11) `jd_opaque *jd_opaque_get(JSContext *ctx);`
  - `jd_idx` (function, line 12) `dom_index *jd_idx(JSContext *ctx);`
  - `jd_handle` (function, line 14) `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out);`
  - `FREEDOM_JS_DOM_INTERNAL_H` (macro, line 2) `#define FREEDOM_JS_DOM_INTERNAL_H`
- Depends on: `include/dom.h`, `include/js_dom.h`
- Imported by: `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`

## src/js_embed.c
- Layer: utility
- Language: c
- Symbols:
  - `try_create_iframe_from_script` (function, line 86) `static int try_create_iframe_from_script(dom_index *idx,
                                        ...`
  - `jd_video_from_scripts` (function, line 203) `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,
                   ...`
  - `jd_inject_video_shim` (function, line 242) `jd_status jd_inject_video_shim(js_context *ctx)`
  - `scan_video_url` (function, line 256) `static int scan_video_url(const char *body, size_t blen,
                           char *out, si...`
  - `jd_process_iframes` (function, line 294) `void jd_process_iframes(js_context *ctx, dom_index *idx,
                        jd_fetch_fn fn, ...`
  - `_GNU_SOURCE` (macro, line 6) `#define _GNU_SOURCE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`

## src/js_env.c
- Layer: infrastructure
- Language: c
- Symbols:
  - `wall_clock_ms` (function, line 35) `static uint64_t wall_clock_ms(void)`
  - `monotonic_ms` (function, line 41) `static double monotonic_ms(void)`
  - `m_date_now` (function, line 49) `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_perf_now` (function, line 57) `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_empty_array` (function, line 77) `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_get_random_values` (function, line 85) `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,
                       ...`
  - `m_random_uuid` (function, line 125) `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_subtle_null` (function, line 142) `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `def_val` (function, line 153) `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)`
  - `def_str` (function, line 159) `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)`
  - `def_int` (function, line 163) `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)`
  - `def_fn` (function, line 167) `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,
                  JSCFuncti...`
  - `build_languages` (function, line 174) `static JSValue build_languages(JSContext *ctx)`
  - `build_navigator` (function, line 198) `static int build_navigator(JSContext *ctx, JSValueConst global)`
  - `build_screen` (function, line 302) `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)`
  - `build_crypto` (function, line 346) `static int build_crypto(JSContext *ctx, JSValueConst global)`
  - `build_perf_timing` (function, line 374) `static int build_perf_timing(JSContext *ctx, JSValueConst perf)`
  - `build_perf_navigation` (function, line 388) `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)`
  - `build_performance` (function, line 400) `static int build_performance(JSContext *ctx, JSValueConst global)`
  - `override_date_now` (function, line 432) `static int override_date_now(JSContext *ctx, JSValueConst global)`
  - `make_readback` (function, line 476) `static JSValue make_readback(JSContext *ctx, uint64_t key)`
  - `build_readback_obj` (function, line 484) `static int build_readback_obj(JSContext *ctx, JSValueConst global,
                              ...`
  - `je_install` (function, line 497) `je_status je_install(js_context *ctx, int screen_w, int screen_h)`
  - `je_install_canvas` (function, line 516) `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)`
  - `primitives` (function, line 6) `* the pure anti_fp primitives (one audited source of normalized constants);`
  - `methods` (function, line 201) `* capability methods (sendBeacon, spec/js_dom.md 7h) without touching any * fingerprintable field. An untrusted page's prototype stays empty. */ JSValue proto = JS_NewObject(ctx);`
  - `_POSIX_C_SOURCE` (macro, line 17) `#define _POSIX_C_SOURCE`
  - `FP_MIME_COUNT` (macro, line 260) `#define FP_MIME_COUNT`
  - `PERF_ORIGIN_EPOCH` (macro, line 344) `#define PERF_ORIGIN_EPOCH`
- Depends on: `include/anti_fp.h`, `include/js_env.h`, `include/js_sandbox.h`

## src/js_events.c
- Layer: infrastructure
- Language: c
- Symbols:
  - `jd_click_state` (struct, line 25)
  - `jd_click_state_new` (function, line 29) `jd_click_state *jd_click_state_new(void)`
  - `jd_click_state_free` (function, line 34) `void jd_click_state_free(jd_click_state *s)`
  - `jd_install_events` (function, line 38) `jd_status jd_install_events(js_context *ctx, jd_click_state *state)`
  - `jd_eval_default_action` (function, line 52) `static int jd_eval_default_action(JSContext *jsctx, const char *src, size_t n,
                  ...`
  - `jd_fire_click` (function, line 66) `int jd_fire_click(js_context *ctx, dom_node_id node_id)`
  - `jd_fire_submit` (function, line 78) `int jd_fire_submit(js_context *ctx, dom_node_id form_node_id)`
  - `jd_escape_js_str` (function, line 91) `static size_t jd_escape_js_str(const char *src, char *dst, size_t dstsz)`
  - `jd_fire_mouse_event` (function, line 163) `int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,
                        const char ...`
  - `_GNU_SOURCE` (macro, line 6) `#define _GNU_SOURCE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`

## src/js_fetch.c
- Layer: utility
- Language: c
- Symbols:
  - `jd_pack_ptr` (function, line 28) `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)`
  - `jd_unpack_ptr` (function, line 33) `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)`
  - `m_host_fetch` (function, line 46) `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `jd_install_xhr` (function, line 197) `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)`
  - `send` (function, line 92) `* callbacks fire right after send();`
  - `task` (function, line 179) `* current task (the page never waits on it);`
  - `_GNU_SOURCE` (macro, line 6) `#define _GNU_SOURCE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`

## src/js_geom.c
- Layer: utility
- Language: c
- Symbols:
  - `jg_init` (function, line 17) `void jg_init(jg_table *t)`
  - `jg_free` (function, line 21) `void jg_free(jg_table *t)`
  - `clamp_coord` (function, line 27) `static int32_t clamp_coord(double v, double lo)`
  - `grow` (function, line 33) `static int grow(jg_table *t)`
  - `push` (function, line 45) `static int push(jg_table *t, dom_node_id node, int32_t x, int32_t y, int32_t w, int32_t h)`
  - `jg_add` (function, line 52) `int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h)`
  - `unite` (function, line 63) `static int unite(jg_rect *a, const jg_rect *b)`
  - `cmp_node` (function, line 78) `static int cmp_node(const void *pa, const void *pb)`
  - `jg_finish` (function, line 83) `int jg_finish(jg_table *t)`
  - `jg_find` (function, line 96) `const jg_rect *jg_find(const jg_table *t, dom_node_id node)`
  - `slot_of` (function, line 102) `static uint32_t slot_of(dom_node_id n)`
  - `index_of` (function, line 109) `static size_t index_of(jg_table *t, uint32_t *slots, dom_node_id node, const jg_rect *seed,
     ...`
  - `jg_aggregate` (function, line 124) `int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx)`
  - `jg_wire_len` (function, line 163) `size_t jg_wire_len(const jg_table *t)`
  - `jg_encode` (function, line 167) `int jg_encode(const jg_table *t, int32_t *out, size_t cap)`
  - `in_range` (function, line 182) `static int in_range(int32_t v, int32_t lo)`
  - `jg_decode` (function, line 186) `int jg_decode(const int32_t *in, size_t n, jg_table *out)`
  - `fnv` (function, line 212) `static uint64_t fnv(uint64_t h, int32_t v)`
  - `jg_hash` (function, line 221) `uint64_t jg_hash(const jg_table *t)`
  - `JG_INDEX_SLOTS` (macro, line 14) `#define JG_INDEX_SLOTS`
  - `JG_SLOT_EMPTY` (macro, line 15) `#define JG_SLOT_EMPTY`
- Depends on: `include/js_geom.h`

## src/js_location.c
- Layer: utility
- Language: c
- Symbols:
  - `jd_lp_set` (function, line 24) `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,
                      const ...`
  - `jl_m_hist_target` (function, line 35) `JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `jd_set_location` (function, line 139) `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)`
  - `jd_take_nav_request` (function, line 173) `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)`
  - `jd_take_history` (function, line 219) `char *jd_take_history(js_context *ctx, int *go)`
  - `jd_pop_state` (function, line 250) `int jd_pop_state(js_context *ctx, int index)`
- Depends on: `include/js_dom.h`, `include/url.h`, `src/js_location_internal.h`

## src/js_location_internal.h
- Layer: utility
- Doc: Private to js_dom.c / js_location.c: the dom.histTarget native lives with the
- Language: h
- Symbols:
  - `header` (function, line 6) `* stay out of every public header (include/ never sees quickjs.h). */ #include "quickjs.h" JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);`
  - `FREEDOM_JS_LOCATION_INTERNAL_H` (macro, line 2) `#define FREEDOM_JS_LOCATION_INTERNAL_H`
- Imported by: `src/js_dom.c`, `src/js_location.c`

## src/js_policy.c
- Layer: business_logic
- Language: c
- Symbols:
  - `eq_ci` (function, line 12) `static int eq_ci(const char *a, const char *b)`
  - `jsp_enabled` (function, line 22) `bool jsp_enabled(jsp_mode mode, int host_allowlisted)`
  - `jsp_trusted` (function, line 31) `bool jsp_trusted(bool js_enabled, int host_allowlisted)`
  - `jsp_present_trusted` (function, line 35) `bool jsp_present_trusted(int host_allowlisted)`
  - `jsp_mode_from_str` (function, line 39) `jsp_mode jsp_mode_from_str(const char *s)`
  - `jsp_mode_str` (function, line 51) `const char *jsp_mode_str(jsp_mode mode)`
- Depends on: `include/js_policy.h`

## src/js_sandbox.c
- Layer: utility
- Language: c
- Symbols:
  - `js_mem_state` (struct, line 27)
  - `js_context` (struct, line 33)
  - `limit` (type_alias, line 27) `typedef struct js_mem_state { size_t limit;`
  - `jm_malloc` (function, line 55) `static void *jm_malloc(void *opaque, size_t size)`
  - `jm_calloc` (function, line 63) `static void *jm_calloc(void *opaque, size_t count, size_t size)`
  - `jm_free` (function, line 73) `static void jm_free(void *opaque, void *ptr)`
  - `jm_realloc` (function, line 79) `static void *jm_realloc(void *opaque, void *ptr, size_t size)`
  - `jm_usable_size` (function, line 89) `static size_t jm_usable_size(const void *ptr)`
  - `host_dup` (function, line 99) `static char *host_dup(const char *src, size_t len)`
  - `timespec_reached` (function, line 108) `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)`
  - `js_interrupt_cb` (function, line 114) `static int js_interrupt_cb(JSRuntime *rt, void *opaque)`
  - `is_ascii_digit` (function, line 127) `static int is_ascii_digit(char c)`
  - `js_loc_from_stack` (function, line 129) `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      i...`
  - `js_limits_default` (function, line 248) `js_limits js_limits_default(void)`
  - `limits_resolve` (function, line 257) `static js_limits limits_resolve(const js_limits *lim)`
  - `js_validate_source` (function, line 266) `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)`
  - `js_context_new` (function, line 277) `js_status js_context_new(const js_limits *lim, js_context **out)`
  - `js_context_free` (function, line 316) `void js_context_free(js_context *ctx)`
  - `arm_deadline` (function, line 327) `static void arm_deadline(js_context *ctx, uint64_t budget_ms)`
  - `js_set_time_budget` (function, line 342) `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)`
  - `js_eval` (function, line 347) `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)`
  - `js_eval_named` (function, line 351) `js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        con...`
  - `js_pump_jobs` (function, line 434) `int js_pump_jobs(js_context *ctx, int max_jobs)`
  - `js_eval_once` (function, line 452) `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)`
  - `js_result_free` (function, line 465) `void js_result_free(js_result *res)`
  - `js_set_current_script` (function, line 489) `void js_set_current_script(js_context *ctx, const char *src, const char *type)`
  - `js_context_raw` (function, line 522) `void *js_context_raw(js_context *ctx)`
  - `mod_set_meta` (function, line 543) `static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url)`
  - `mod_loader` (function, line 552) `static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque)`
  - `js_set_module_host` (function, line 588) `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,
                        js...`
  - `mod_fail` (function, line 598) `static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,
      ...`
  - `js_eval_module` (function, line 613) `js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,
        ...`
  - `realm_of` (function, line 680) `static JSContext *realm_of(js_context *c, JSValueConst g)`
  - `throw_named` (function, line 693) `static JSValue throw_named(JSContext *ctx, const char *name, const char *msg)`
  - `m_realm_new` (function, line 703) `static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,
                     ...`
  - `m_realm_eval` (function, line 717) `static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,
                    ...`
  - `m_realm_clone` (function, line 753) `static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,
                   ...`
  - `js_install_realms` (function, line 775) `js_status js_install_realms(js_context *ctx)`
  - `undefined` (function, line 221) `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx, exc, "stack");`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
  - `JS_MODULE_URL_MAX` (macro, line 527) `#define JS_MODULE_URL_MAX`
- Depends on: `include/js_sandbox.h`

## src/js_trusted.c
- Layer: utility
- Language: c
- Symbols:
  - `jt_seed_ctx` (struct, line 263)
  - `jt_enable_open` (function, line 26) `jd_status jt_enable_open(js_context *ctx)`
  - `jt_take_opens` (function, line 42) `char *jt_take_opens(js_context *ctx)`
  - `jt_enable_ws` (function, line 120) `jd_status jt_enable_ws(js_context *ctx)`
  - `jt_ws_ops_free` (function, line 132) `void jt_ws_ops_free(jt_ws_op *ops, size_t n)`
  - `hex_nibble` (function, line 137) `static int hex_nibble(char c)`
  - `ws_payload` (function, line 144) `static char *ws_payload(int kind, const char *s, size_t n, size_t *out_len)`
  - `jt_take_ws` (function, line 168) `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap)`
  - `jt_ws_event` (function, line 210) `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len)`
  - `jt_seed_pair` (function, line 265) `static void jt_seed_pair(void *vctx, const char *k, size_t kl, const char *v, size_t vl)`
  - `jt_enable_storage` (function, line 275) `jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len)`
  - `jt_take_storage` (function, line 296) `int jt_take_storage(js_context *ctx, char **out, size_t *len)`
  - `explicitly` (function, line 344) `* explicitly (no window, no document). Delivery is always a timer task. */
static const char JT_W...`
  - `jt_enable_worker` (function, line 425) `jd_status jt_enable_worker(js_context *ctx)`
- Depends on: `include/js_trusted.h`, `include/web_storage.h`

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
  - `ln_resolve` (function, line 172) `ln_status ln_resolve(const char *base, const char *href, ln_result *out)`
  - `ln_block_reason_text` (function, line 241) `const char *ln_block_reason_text(ln_block_reason reason)`
- Depends on: `include/link_nav.h`, `include/url.h`

## src/local_store.c
- Layer: data_access
- Language: c
- Symbols:
  - `cipher_for` (function, line 728) `static const EVP_CIPHER *cipher_for(ls_aead aead)`
  - `argon2id_derive` (function, line 738) `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,
                          ...`
  - `ls_derive_key` (function, line 767) `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,
                        const...`
  - `aead_encrypt` (function, line 776) `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...`
  - `aead_decrypt` (function, line 802) `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...`
  - `seal_core` (function, line 830) `static ls_status seal_core(const uint8_t *key, ls_aead aead, uint8_t kdf_id,
                    ...`
  - `decrypt_blob` (function, line 867) `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,
         ...`
  - `ls_seal` (function, line 898) `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,
                  const uint8_t *p...`
  - `ls_open` (function, line 911) `ls_status ls_open(const uint8_t key[LS_KEY_LEN],
                  const uint8_t *blob, size_t bl...`
  - `ls_seal_passphrase` (function, line 922) `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,
          ...`
  - `ls_open_passphrase` (function, line 943) `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,
                        ...`
  - `ls_free` (function, line 963) `void ls_free(uint8_t *buf, size_t len)`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 3) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 6) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 9) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 11) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 14) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 17) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 20) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 22) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 25) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 28) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 31) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 33) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 36) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 39) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 42) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 44) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 47) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 50) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 53) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 55) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 58) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 61) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 64) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 66) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 69) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 72) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 75) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 77) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 80) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 83) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 86) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 88) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 91) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 94) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 97) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 99) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 102) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 105) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 108) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 110) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 113) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 116) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 119) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 121) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 124) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 127) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 130) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 132) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 135) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 138) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 141) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 143) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 146) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 149) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 152) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 154) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 157) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 160) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 163) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 165) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 168) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 171) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 174) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 176) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 179) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 182) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 185) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 187) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 190) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 193) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 196) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 198) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 201) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 204) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 207) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 209) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 212) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 215) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 218) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 220) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 223) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 226) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 229) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 231) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 234) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 237) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 240) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 242) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 245) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 248) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 251) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 253) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 256) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 259) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 262) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 264) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 267) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 270) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 273) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 275) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 278) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 281) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 284) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 286) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 289) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 292) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 295) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 297) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 300) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 303) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 306) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 308) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 311) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 314) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 317) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 319) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 322) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 325) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 328) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 330) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 333) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 336) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 339) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 341) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 344) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 347) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 350) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 352) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 355) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 358) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 361) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 363) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 366) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 369) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 372) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 374) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 377) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 380) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 383) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 385) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 388) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 391) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 394) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 396) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 399) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 402) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 405) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 407) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 410) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 413) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 416) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 418) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 421) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 424) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 427) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 429) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 432) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 435) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 438) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 440) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 443) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 446) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 449) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 451) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 454) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 457) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 460) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 462) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 465) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 468) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 471) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 473) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 476) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 479) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 482) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 484) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 487) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 490) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 493) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 495) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 498) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 501) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 504) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 506) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 509) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 512) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 515) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 517) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 520) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 523) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 526) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 528) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 531) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 534) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 537) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 539) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 542) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 545) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 548) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 550) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 553) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 556) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 559) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 561) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 564) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 567) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 570) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 572) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 575) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 578) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 581) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 583) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 586) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 589) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 592) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 594) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 597) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 600) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 603) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 605) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 608) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 611) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 614) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 616) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 619) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 622) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 625) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 627) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 630) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 633) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 636) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 638) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 641) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 644) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 647) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 649) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 652) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 655) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 658) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 660) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 663) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 666) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 669) `#define OSSL_KDF_PARAM_THREADS`
  - `_GNU_SOURCE` (macro, line 671) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 698) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 701) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 704) `#define OSSL_KDF_PARAM_THREADS`
  - `LS_VERSION` (macro, line 707) `#define LS_VERSION`
  - `LS_KDF_NONE` (macro, line 708) `#define LS_KDF_NONE`
  - `LS_KDF_ARGON2ID` (macro, line 709) `#define LS_KDF_ARGON2ID`
  - `LS_ARGON2_T` (macro, line 712) `#define LS_ARGON2_T`
  - `LS_ARGON2_M_KIB` (macro, line 713) `#define LS_ARGON2_M_KIB`
  - `LS_ARGON2_P` (macro, line 714) `#define LS_ARGON2_P`
  - `OFF_MAGIC` (macro, line 717) `#define OFF_MAGIC`
  - `OFF_VERSION` (macro, line 718) `#define OFF_VERSION`
  - `OFF_AEAD` (macro, line 719) `#define OFF_AEAD`
  - `OFF_KDF` (macro, line 720) `#define OFF_KDF`
  - `OFF_SALT` (macro, line 721) `#define OFF_SALT`
  - `OFF_NONCE` (macro, line 722) `#define OFF_NONCE`
- Depends on: `include/local_store.h`

## src/media_decoder.c
- Layer: infrastructure
- Language: c
- Symbols:
  - `decoder_ctx` (struct, line 54)
  - `out_fd` (type_alias, line 53) `typedef struct decoder_ctx { int out_fd;`
  - `open` (function, line 18) `*
 * Sandbox: the decoder needs open() for shared libraries (.so loading) and
 * brk/mmap for FFm...`
  - `decoder_close` (function, line 78) `static void decoder_close(decoder_ctx *dc)`
  - `decoder_init` (function, line 96) `static int decoder_init(decoder_ctx *dc, const uint8_t *data, size_t len)`
  - `frame_pts_us` (function, line 215) `static int64_t frame_pts_us(const AVFrame *f, AVRational tb, int64_t fallback)`
  - `av_rescale_q` (function, line 217) `return av_rescale_q(f->pts, tb, (AVRational)`
  - `send_video_frame` (function, line 222) `static void send_video_frame(decoder_ctx *dc, int64_t pts_us)`
  - `send_audio_frame` (function, line 242) `static void send_audio_frame(decoder_ctx *dc, int64_t pts_us)`
  - `decode_segment` (function, line 276) `static int decode_segment(decoder_ctx *dc, const uint8_t *data, size_t len)`
  - `media_decoder_run` (function, line 379) `void media_decoder_run(int out_fd, int cmd_fd)`
  - `media_decoder_spawn` (function, line 449) `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd)`
  - `dropped` (function, line 369) `* the codec in permanent EOF state: every segment after the first decoded * one was silently dropped ("plays a couple of seconds then stops"). * Reorder-buffered frames flush with the next segment's p`
  - `fd` (function, line 469) `* prevent the Wayland display fd (inherited from the parent) from * surviving the exec. An inherited Wayland fd would be leaked to the * decoder child and, if accidentally written to (e.g. by an FFmpe`
  - `_POSIX_C_SOURCE` (macro, line 23) `#define _POSIX_C_SOURCE`
- Depends on: `include/media_decoder.h`, `include/util.h`

## src/net_realm.c
- Layer: utility
- Language: c
- Symbols:
  - `lower` (function, line 17) `static char lower(char c)`
  - `ends_with_realm` (function, line 23) `static int ends_with_realm(const char *host, size_t n, const char *suffix)`
  - `nr_classify_host` (function, line 34) `nr_realm nr_classify_host(const char *host)`
  - `host_of` (function, line 52) `static int host_of(const char *url, char *out, size_t out_size)`
  - `nr_classify_url` (function, line 68) `nr_realm nr_classify_url(const char *url)`
  - `nr_route_for` (function, line 74) `nr_route nr_route_for(const char *url, nr_config cfg)`
  - `nr_realm_allows_http` (function, line 88) `int nr_realm_allows_http(nr_realm r)`
  - `nr_realm_name` (function, line 94) `const char *nr_realm_name(nr_realm r)`
  - `nr_route_name` (function, line 103) `const char *nr_route_name(nr_route r)`
  - `NR_MAX_HOST` (macro, line 15) `#define NR_MAX_HOST`
- Depends on: `include/net_realm.h`

## src/os_sandbox.c
- Layer: utility
- Language: c
- Symbols:
  - `os_policy_allows` (function, line 52) `int os_policy_allows(long syscall_nr)`
  - `os_policy_size` (function, line 59) `size_t os_policy_size(void)`
  - `os_prot_allowed` (function, line 65) `int os_prot_allowed(long syscall_nr, unsigned long prot)`
  - `os_no_dump` (function, line 75) `os_status os_no_dump(void)`
  - `excluded` (function, line 89) `* intentionally excluded (they need /proc remounting and a post-unshare fork). */
int os_namespac...`
  - `os_isolate_namespaces` (function, line 94) `os_status os_isolate_namespaces(void)`
  - `os_policy_allows` (function, line 106) `int os_policy_allows(long syscall_nr)`
  - `os_policy_size` (function, line 107) `size_t os_policy_size(void)`
  - `os_prot_allowed` (function, line 108) `int os_prot_allowed(long syscall_nr, unsigned long prot)`
  - `os_no_dump` (function, line 111) `os_status os_no_dump(void)`
  - `os_harden` (function, line 113) `os_status os_harden(os_violation action)`
  - `os_namespace_flags` (function, line 115) `int os_namespace_flags(void)`
  - `os_isolate_namespaces` (function, line 116) `os_status os_isolate_namespaces(void)`
  - `os_harden` (function, line 145) `os_status os_harden(os_violation action)`
  - `ll_create_ruleset` (function, line 239) `static long ll_create_ruleset(const struct landlock_ruleset_attr *attr,
                         ...`
  - `ll_add_rule` (function, line 244) `static long ll_add_rule(int fd, enum landlock_rule_type type,
                        const void ...`
  - `ll_restrict_self` (function, line 249) `static long ll_restrict_self(int fd, uint32_t flags)`
  - `ll_handled` (function, line 265) `static uint64_t ll_handled(int abi)`
  - `ll_read_access` (function, line 279) `static uint64_t ll_read_access(uint64_t handled)`
  - `os_landlock_abi` (function, line 285) `int os_landlock_abi(void)`
  - `os_landlock_restrict` (function, line 291) `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)`
  - `os_landlock_abi` (function, line 331) `int os_landlock_abi(void)`
  - `os_landlock_restrict` (function, line 332) `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)`
  - `number` (function, line 157) `* number (x32/i386 on x86_64, AArch32 on aarch64). */ prog[n++] = (struct sock_filter)BPF_STMT(BPF_LD | BPF_W | BPF_ABS, offsetof(struct seccomp_data, arch));`
  - `headroom` (function, line 203) `* wide headroom (room for ~125 allowed syscalls). */ prog[at_mmap].jt = (unsigned char)(prot_check - (at_mmap + 1));`
  - `fields` (function, line 303) `* long as the unknown trailing fields (net/scoped) are zero, which they are. */ int rfd = (int)ll_create_ruleset(&attr, sizeof attr, 0);`
  - `_GNU_SOURCE` (macro, line 13) `#define _GNU_SOURCE`
  - `OS_ALLOWED_N` (macro, line 50) `#define OS_ALLOWED_N`
  - `OS_SECCOMP_ARCH` (macro, line 140) `#  define OS_SECCOMP_ARCH`
  - `OS_SECCOMP_ARCH` (macro, line 142) `#  define OS_SECCOMP_ARCH`
  - `LL_FS_BASE` (macro, line 254) `#define LL_FS_BASE`
- Depends on: `include/os_sandbox.h`

## src/page_view.c
- Layer: presentation
- Language: c
- Symbols:
  - `pv_node_map` (struct, line 272)
  - `pv_cont_info` (struct, line 1100)
  - `pv_item_track` (struct, line 1174)
  - `pv_box_info` (struct, line 1193)
  - `pv_container_reg` (struct, line 1510)
  - `pv_box_reg` (struct, line 1610)
  - `pv_ptrmap` (struct, line 1962)
  - `pv_var_node` (struct, line 2028)
  - `pv_style_cache` (struct, line 2033)
  - `pv_flow_reg` (struct, line 2647)
  - `sz_fill` (struct, line 3294)
  - `pv_root_els` (struct, line 3550)
  - `form_rec` (struct, line 3616)
  - `form_table` (struct, line 3622)
  - `pv_flow_reg` (struct, line 3978)
  - `cols` (type_alias, line 1100) `typedef struct pv_cont_info { int id, display, gap, justify, cols;`
  - `mb` (type_alias, line 1193) `typedef struct pv_box_info { int l, r, w, center, mt, mb;`
  - `chain` (type_alias, line 2028) `typedef struct pv_var_node { cvr_chain chain;`
  - `cp1252_to_ucs` (function, line 84) `static unsigned int cp1252_to_ucs(unsigned char c)`
  - `utf8_encode` (function, line 98) `static size_t utf8_encode(unsigned int cp, char *out)`
  - `utf8_sanitized_dup` (function, line 111) `static char *utf8_sanitized_dup(const char *s)`
  - `dup_n` (function, line 145) `static char *dup_n(const char *s, size_t n)`
  - `run_init_common` (function, line 159) `static void run_init_common(pv_run *r)`
  - `pv_node_map_init` (function, line 278) `static int pv_node_map_init(pv_node_map *m)`
  - `pv_node_map_free` (function, line 286) `static void pv_node_map_free(pv_node_map *m)`
  - `pv_node_map_build` (function, line 322) `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root)`
  - `pv_new` (function, line 331) `pv_view *pv_new(void)`
  - `pv_append` (function, line 335) `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    c...`
  - `pv_append_image` (function, line 369) `pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          con...`
  - `pv_append_input` (function, line 399) `pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_...`
  - `pv_append_video` (function, line 439) `pv_status pv_append_video(pv_view *v, int heading, int block_break,
                          con...`
  - `pv_append_svg` (function, line 475) `pv_status pv_append_svg(pv_view *v, int heading, int block_break,
                        const c...`
  - `pv_set_emphasis` (function, line 504) `void pv_set_emphasis(pv_view *v, int bold, int italic)`
  - `pv_set_indent` (function, line 511) `void pv_set_indent(pv_view *v, int indent)`
  - `pv_set_color` (function, line 516) `void pv_set_color(pv_view *v, int fg_rgb)`
  - `pv_set_bgcolor` (function, line 521) `void pv_set_bgcolor(pv_view *v, int bg_rgb)`
  - `pv_set_text_style` (function, line 526) `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,
                ...`
  - `pv_set_grad_text` (function, line 537) `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)`
  - `pv_set_text_ext` (function, line 545) `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)`
  - `ignored` (function, line 577) `* source is ignored (fail-visible: never invisible text from half a
     * pattern). A real text-...`
  - `pv_set_container` (function, line 592) `void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_g...`
  - `pv_set_row_span` (function, line 607) `void pv_set_row_span(pv_view *v, int row_span)`
  - `pv_set_grid_area` (function, line 611) `void pv_set_grid_area(pv_view *v, int row_start, int col_start)`
  - `pv_set_grid` (function, line 618) `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)`
  - `pv_set_grid_rows` (function, line 628) `void pv_set_grid_rows(pv_view *v, int grid_rows)`
  - `pv_set_cont_box` (function, line 632) `void pv_set_cont_box(pv_view *v, int cont_box_id)`
  - `pv_set_flex` (function, line 636) `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                 int...`
  - `pv_set_flex_mauto` (function, line 648) `void pv_set_flex_mauto(pv_view *v, int mauto)`
  - `pv_set_cont_item` (function, line 654) `void pv_set_cont_item(pv_view *v, int cont_item)`
  - `pv_set_float` (function, line 659) `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear,
                int ...`
  - `pv_set_box` (function, line 681) `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                int box_center, int ...`
  - `pv_set_box_pct` (function, line 693) `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,
                    ...`
  - `pv_set_box_maxw` (function, line 704) `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct)`
  - `pv_set_ua_tag` (function, line 711) `void pv_set_ua_tag(pv_view *v, int ua_tag)`
  - `pv_set_node_id` (function, line 717) `void pv_set_node_id(pv_view *v, dom_node_id node_id)`
  - `pv_set_block_id` (function, line 722) `void pv_set_block_id(pv_view *v, int block_id)`
  - `pv_set_own_box` (function, line 727) `void pv_set_own_box(pv_view *v, int box_id)`
  - `pv_set_oof` (function, line 732) `void pv_set_oof(pv_view *v, int oof)`
  - `pv_set_input_checked` (function, line 737) `void pv_set_input_checked(pv_view *v, int checked)`
  - `pv_set_input_select_opts` (function, line 742) `void pv_set_input_select_opts(pv_view *v, const char *select_opts)`
  - `pv_add_cont_def` (function, line 750) `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)`
  - `pv_cont_count` (function, line 763) `size_t pv_cont_count(const pv_view *v)`
  - `pv_cont_at` (function, line 767) `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)`
  - `pv_add_box_def` (function, line 772) `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)`
  - `pv_free` (function, line 785) `void pv_free(pv_view *v)`
  - `pv_count` (function, line 802) `size_t pv_count(const pv_view *v)`
  - `pv_at` (function, line 806) `const pv_run *pv_at(const pv_view *v, size_t i)`
  - `pv_box_count` (function, line 811) `size_t pv_box_count(const pv_view *v)`
  - `pv_box_at` (function, line 815) `const pv_box_def *pv_box_at(const pv_view *v, size_t i)`
  - `node_next` (function, line 823) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)`
  - `is_block_tag` (function, line 833) `static int is_block_tag(lxb_tag_id_t t)`
  - `is_block_like` (function, line 858) `static int is_block_like(lxb_tag_id_t t, css_display display)`
  - `resolves` (function, line 887) `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close
 * button/tooltip w...`
  - `is_block_like_style` (function, line 897) `static int is_block_like_style(lxb_tag_id_t t, const css_style *cs)`
  - `generates_box` (function, line 909) `static int generates_box(lxb_tag_id_t t, css_display display)`
  - `generates_box_style` (function, line 921) `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)`
  - `causes_block_break` (function, line 928) `static int causes_block_break(lxb_tag_id_t t, css_display display)`
  - `paints` (function, line 937) `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas
 * vacías"). Comment a...`
  - `ua_tag_of` (function, line 962) `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)`
  - `heading_level` (function, line 984) `static int heading_level(lxb_tag_id_t t)`
  - `is_skipped_tag` (function, line 996) `static int is_skipped_tag(lxb_tag_id_t t)`
  - `node_tag` (function, line 1017) `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)`
  - `in_skipped_subtree` (function, line 1025) `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
              ...`
  - `font_color_attr` (function, line 1062) `static int font_color_attr(lxb_dom_element_t *el)`
  - `bgcolor_attr` (function, line 1068) `static int bgcolor_attr(lxb_dom_element_t *el)`
  - `item_ordinal` (function, line 1181) `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)`
  - `pv_content_hidden` (function, line 1213) `int pv_content_hidden(int box_hidden, int run_visibility)`
  - `pv_text_ext_reset` (function, line 1219) `void pv_text_ext_reset(pv_text_ext *e)`
  - `pv_text_ext_merge` (function, line 1245) `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)`
  - `css_has_hbox` (function, line 1303) `static int css_has_hbox(const css_style *cs)`
  - `pv_mauto_of` (function, line 1317) `static int pv_mauto_of(const css_style *cs)`
  - `css_hbox_resolve` (function, line 1324) `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)`
  - `css_has_position` (function, line 1372) `static int css_has_position(const css_style *cs)`
  - `css_has_boxdeco` (function, line 1377) `static int css_has_boxdeco(const css_style *cs)`
  - `cont_def_reset` (function, line 1520) `static void cont_def_reset(pv_cont_def *d)`
  - `container_id` (function, line 1535) `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)`
  - `annotate_flow_run` (function, line 1581) `static void annotate_flow_run(pv_view *v, pv_container_reg *reg, pv_item_track *items,
          ...`
  - `trying` (function, line 1620) `* a real page passes without trying (slashdot's front page saturates it), and past
 * it box_reg_...`
  - `box_reg_free` (function, line 1649) `static void box_reg_free(pv_box_reg *r)`
  - `boxdef_from_style` (function, line 1658) `static void boxdef_from_style(pv_box_def *d, const css_style *cs)`
  - `box_reg_id` (function, line 1881) `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,
           ...`
  - `pseudo_box_reg` (function, line 1910) `static int pseudo_box_reg(pv_box_reg *r, const lxb_dom_node_t *el, int which,
                   ...`
  - `pseudo_generates_box` (function, line 1931) `static int pseudo_generates_box(const css_style *ps)`
  - `pseudo_is_oof` (function, line 1944) `static int pseudo_is_oof(const css_style *ps)`
  - `pseudo_is_block` (function, line 1948) `static int pseudo_is_block(const css_style *ps)`
  - `pseudo_key` (function, line 1954) `static const void *pseudo_key(const lxb_dom_node_t *el, int which)`
  - `pv_ptrmap_slot` (function, line 1968) `static size_t pv_ptrmap_slot(const pv_ptrmap *m, const void *k)`
  - `pv_ptrmap_get` (function, line 1978) `static int pv_ptrmap_get(const pv_ptrmap *m, const void *k, int *out)`
  - `pv_ptrmap_put` (function, line 1986) `static void pv_ptrmap_put(pv_ptrmap *m, const void *k, int v)`
  - `pv_ptrmap_free` (function, line 2008) `static void pv_ptrmap_free(pv_ptrmap *m)`
  - `pv_ptr_hash` (function, line 2053) `static size_t pv_ptr_hash(const void *p)`
  - `pv_cache_reindex` (function, line 2061) `static void pv_cache_reindex(pv_style_cache *c)`
  - `pv_style_cache_init` (function, line 2071) `static int pv_style_cache_init(pv_style_cache *c)`
  - `pv_style_cache_free` (function, line 2089) `static void pv_style_cache_free(pv_style_cache *c)`
  - `pv_cache_find` (function, line 2103) `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)`
  - `pv_cached_font_px` (function, line 2118) `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)`
  - `pv_cache_put` (function, line 2123) `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,
                     ...`
  - `pv_var_push` (function, line 2162) `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,
                      ...`
  - `pv_parent_element` (function, line 2183) `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)`
  - `cached_pseudo_style` (function, line 2244) `static css_style cached_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet,
             ...`
  - `subtree_is_oof` (function, line 2262) `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,
                     ...`
  - `size` (function, line 2282) `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */
static void app...`
  - `builder` (function, line 2302) `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box
 * (the ...`
  - `css_to_fx_justify` (function, line 2331) `static int css_to_fx_justify(css_justify j)`
  - `is_bold_tag` (function, line 2350) `static int is_bold_tag(lxb_tag_id_t t)`
  - `is_italic_tag` (function, line 2355) `static int is_italic_tag(lxb_tag_id_t t)`
  - `is_inline_level_style` (function, line 2392) `static int is_inline_level_style(lxb_tag_id_t t, const css_style *cs)`
  - `in_mixed_line` (function, line 2400) `static int in_mixed_line(const lxb_dom_node_t *p, const css_sheet *sheet,
                       ...`
  - `children_all_inline_block` (function, line 2416) `static int children_all_inline_block(const lxb_dom_node_t *p, const css_sheet *sheet,
           ...`
  - `col_has_free_space` (function, line 2435) `static int col_has_free_space(const css_style *cs)`
  - `flex_column_flows_as_block` (function, line 2446) `static int flex_column_flows_as_block(const lxb_dom_node_t *el, const css_style *cs,
            ...`
  - `fold_column_gap` (function, line 2478) `static void fold_column_gap(const lxb_dom_node_t *el, css_style *cs,
                            ...`
  - `is_layout_container` (function, line 2502) `static int is_layout_container(const lxb_dom_node_t *el, const css_style *cs,
                   ...`
  - `item_sizes_itself` (function, line 2516) `static int item_sizes_itself(const lxb_dom_node_t *el, const css_style *cs,
                     ...`
  - `li_is_list_item` (function, line 2538) `static int li_is_list_item(const lxb_dom_node_t *li, const css_sheet *sheet,
                    ...`
  - `paints` (function, line 2565) `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas vacías").
 *
 * A chil...`
  - `subtree_has_own_text` (function, line 2608) `static int subtree_has_own_text(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
            ...`
  - `element_is_content_leaf` (function, line 2628) `static int element_is_content_leaf(const lxb_dom_node_t *n, const css_sheet *sheet,
             ...`
  - `resolve_context` (function, line 2651) `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                ...`
  - `opens` (function, line 2920) `* painter applies it when the box opens (band/shared context) — seeding
             * it onto ru...`
  - `margins` (function, line 2948) `* margins (boxdef_from_style) and the painter applies them when
                         * it ope...`
  - `container` (function, line 3066) `* membership in this container (and none in any container further out,
                 * since i...`
  - `walk` (function, line 3150) `* far on this walk (they are all inside this element). */

                        /* The innermo...`
  - `float` (function, line 3243) `* genuinely nested float (oid != id) takes the deferred-column path. */
    if (cont->float_oid =...`
  - `sz_count` (function, line 3286) `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)`
  - `sz_write` (function, line 3300) `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)`
  - `serialize_subtree` (function, line 3308) `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)`
  - `collapse_ws` (function, line 3327) `static char *collapse_ws(const char *s, size_t n)`
  - `parse_dim` (function, line 3351) `static int parse_dim(const lxb_char_t *s, size_t len)`
  - `present` (function, line 3368) `* when no width descriptors are present (density-only or bare URLs). */
static void srcset_best_u...`
  - `srcset_slot_width` (function, line 3463) `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,
                              ...`
  - `dimensions` (function, line 3509) `* viewport dimensions (data: inline detection, <picture> <source> scanning). */
static void srcse...`
  - `find_body` (function, line 3541) `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)`
  - `find_root_els` (function, line 3554) `static pv_root_els find_root_els(lxb_dom_node_t *root)`
  - `attributes` (function, line 3568) `* carries those attributes (spec/css.md, "Root matcher"). */
static int root_els_match(void *ctx,...`
  - `string` (function, line 3579) `* Returns a heap string (caller frees) or NULL when neither carries a class —
 * NULL simply mean...`
  - `forms_free` (function, line 3627) `static void forms_free(form_table *ft)`
  - `ascii_ieq` (function, line 3634) `static int ascii_ieq(const char *s, const char *lit)`
  - `attr_dup` (function, line 3646) `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)`
  - `forms_add` (function, line 3655) `static int forms_add(form_table *ft, const lxb_dom_node_t *node)`
  - `form_for` (function, line 3675) `static int form_for(const form_table *ft, const lxb_dom_node_t *n,
                    const lxb_...`
  - `under_unrendered` (function, line 3691) `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)`
  - `collect_text` (function, line 3704) `static char *collect_text(const lxb_dom_node_t *el)`
  - `classify_input` (function, line 3728) `static pv_input_type classify_input(const char *type)`
  - `li_ordinal` (function, line 3900) `static int li_ordinal(const lxb_dom_node_t *li)`
  - `roman_marker` (function, line 3926) `static void roman_marker(int n, int upper, char *out, size_t cap)`
  - `list_marker` (function, line 3951) `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,
                  ...`
  - `node_table_role` (function, line 3992) `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)`
  - `nearest_table` (function, line 4010) `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
 ...`
  - `parent_is_table_internal` (function, line 4044) `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)`
  - `nearest_cell` (function, line 4071) `static const lxb_dom_node_t *nearest_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
  ...`
  - `cell_has_nested_table` (function, line 4086) `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)`
  - `next_skip` (function, line 4095) `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)`
  - `cell_anchors` (function, line 4106) `static const lxb_dom_node_t *cell_anchors(const lxb_dom_node_t *cell, int *count)`
  - `links` (function, line 4124) `* its links (the Hacker News case: every story link lives inside a <td>), so the
 * caller flows ...`
  - `flow_table` (function, line 4145) `static int flow_table(pv_flow_reg *fr, const lxb_dom_node_t *table)`
  - `in_flow_table_cell` (function, line 4157) `static int in_flow_table_cell(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,
           ...`
  - `table` (function, line 4166) `* FLOW table (multi-link: walked so its links survive) do NOT suppress their
 * content -- their ...`
  - `table_columns` (function, line 4184) `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)`
  - `in_hidden_subtree` (function, line 4258) `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
               ...`
  - `in_boilerplate_subtree` (function, line 4275) `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)`
  - `in_closed_details_subtree` (function, line 4290) `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)`
  - `pv_build` (function, line 4310) `pv_status pv_build(const hp_document *doc, pv_view **out)`
  - `pv_build_ex` (function, line 4314) `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)`
  - `pv_build_full` (function, line 4318) `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                     ...`
  - `annotate_replaced_run` (function, line 4340) `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,
                            ...`
  - `collect_page_css` (function, line 4406) `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,
                     ...`
  - `pv_build_styled` (function, line 4435) `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                   ...`
  - `px` (function, line 5008) `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */
                if (iw <...`
  - `engine` (function, line 5826) `* layout engine (contiguous item gather) drops every cell onto its own row and
         * a 2-col...`
  - `appended` (function, line 5881) `* AFTER the run is appended (so THIS run's brk stays) but BEFORE the next. */
        if (cont.fl...`
  - `pv_css_drops` (function, line 5961) `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,
                       const cha...`
  - `positions` (function, line 134) `* positions (cp == 0) keep the legacy '?' fallback. */ unsigned int cp = cp1252_to_ucs(c);`
  - `content` (function, line 1022) `* a <noscript> ancestor also suppresses content (the script would run, so the * fallback is hidden);`
  - `address` (function, line 1090) `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <= BT_MAX_POSITIONED, "PV_MAX_BOXES must fit the out-of-flow solver's per-box arrays");`
  - `child` (function, line 1098) `* child (NULL = anonymous item: text directly inside the container);`
  - `id` (function, line 1118) `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);`
  - `it` (function, line 1209) `* it (they inherit in CSS). list_style drives the <li> marker (structural);`
  - `here` (function, line 1749) `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3 section 5.1) is content height * with indefinite available space, i.e. `auto`: letting`
  - `glyphs` (function, line 1787) `* glyphs (the runs carry it as their fill source);`
  - `outermost` (function, line 2871) `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);`
  - `control` (function, line 4857) `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);`
  - `height` (function, line 5075) `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
  - `block_id` (function, line 5173) `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it falls * into flow as a full-width row. Gated on img_oof, so every * in-flow image keep`
  - `URL` (function, line 5304) `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
  - `flow` (function, line 5726) `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through it. Subtree-wide: the run * may sit deep inside an undecorated abspos wrapper, where`
  - `line` (function, line 5835) `* to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);`
  - `_POSIX_C_SOURCE` (macro, line 10) `#define _POSIX_C_SOURCE`
  - `PV_MAX_DIM` (macro, line 46) `#define PV_MAX_DIM`
  - `PV_FONT_REL_MIN` (macro, line 51) `#define PV_FONT_REL_MIN`
  - `PV_FONT_REL_MAX` (macro, line 52) `#define PV_FONT_REL_MAX`
  - `PV_FONT_CHAIN_MAX` (macro, line 58) `#define PV_FONT_CHAIN_MAX`
  - `PV_FONT_PCT_MIN` (macro, line 59) `#define PV_FONT_PCT_MIN`
  - `PV_FONT_PCT_MAX` (macro, line 60) `#define PV_FONT_PCT_MAX`
  - `PV_NODE_MAP_INIT_CAP` (macro, line 270) `#define PV_NODE_MAP_INIT_CAP`
  - `PV_COLOR_TOKEN_MAX` (macro, line 1040) `#define PV_COLOR_TOKEN_MAX`
  - `PV_MAX_CONTAINERS` (macro, line 1078) `#define PV_MAX_CONTAINERS`
  - `PV_MAX_GRID_COLS` (macro, line 1079) `#define PV_MAX_GRID_COLS`
  - `PV_MAX_BOXES` (macro, line 1087) `#define PV_MAX_BOXES`
  - `PV_MAX_INLINE_ROW_ITEMS` (macro, line 2388) `#define PV_MAX_INLINE_ROW_ITEMS`
  - `PV_TEXTLESS_DEPTH_MAX` (macro, line 2591) `#define PV_TEXTLESS_DEPTH_MAX`
  - `PV_MAX_STYLE_BYTES` (macro, line 4211) `#define PV_MAX_STYLE_BYTES`
- Depends on: `include/box_style.h`, `include/box_tree.h`, `include/css.h`, `include/css_chain.h`, `include/css_color.h`, `include/css_length.h`, `include/css_vars.h`, `include/dom.h`, `include/flex_layout.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/page_view.h`, `include/svg_render.h`, `include/util.h`

## src/pdf_export.c
- Layer: utility
- Language: c
- Symbols:
  - `pe_safe_basename` (function, line 25) `pe_status pe_safe_basename(const char *title, char *out, size_t outsz)`
  - `pe_build_path_ext` (function, line 66) `pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,
                ...`
  - `pe_build_path` (function, line 91) `pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz)`
  - `pe_paginate` (function, line 95) `size_t pe_paginate(const double *tops, const double *heights, size_t n,
                   double...`
- Depends on: `include/pdf_export.h`

## src/perf_trace.c
- Layer: utility
- Language: c
- Symbols:
  - `pt_init` (function, line 16) `void pt_init(pt_trace *t)`
  - `pt_elapsed_us` (function, line 21) `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us)`
  - `pt_record` (function, line 26) `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us)`
  - `pt_count` (function, line 35) `size_t pt_count(const pt_trace *t, pt_stage stage)`
  - `pt_last_us` (function, line 40) `uint64_t pt_last_us(const pt_trace *t, pt_stage stage)`
  - `pt_min_us` (function, line 49) `uint64_t pt_min_us(const pt_trace *t, pt_stage stage)`
  - `pt_max_us` (function, line 60) `uint64_t pt_max_us(const pt_trace *t, pt_stage stage)`
  - `cmp_u64` (function, line 71) `static int cmp_u64(const void *a, const void *b)`
  - `pt_median_us` (function, line 79) `uint64_t pt_median_us(const pt_trace *t, pt_stage stage)`
  - `pt_stage_name` (function, line 89) `const char *pt_stage_name(pt_stage stage)`
  - `pt_format` (function, line 109) `size_t pt_format(const pt_trace *t, char *buf, size_t cap)`
  - `PT_LINE_CAP` (macro, line 107) `#define PT_LINE_CAP`
- Depends on: `include/perf_trace.h`

## src/prefetch.c
- Layer: utility
- Language: c
- Symbols:
  - `attr_span` (struct, line 62)
  - `is_ws` (function, line 23) `static int is_ws(char c)`
  - `is_name_char` (function, line 27) `static int is_name_char(char c)`
  - `lower` (function, line 32) `static int lower(int c)`
  - `ci_starts` (function, line 37) `static int ci_starts(const char *p, const char *end, const char *kw)`
  - `ci_find` (function, line 46) `static const char *ci_find(const char *p, const char *end, const char *kw)`
  - `ci_eq_span` (function, line 55) `static int ci_eq_span(const char *s, size_t n, const char *kw)`
  - `emit` (function, line 117) `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)`
  - `pf_scan` (function, line 130) `int pf_scan(const char *html, size_t len, pf_list *out)`
  - `pf_list_free` (function, line 193) `void pf_list_free(pf_list *l)`
  - `pf_worker` (function, line 201) `static void *pf_worker(void *arg)`
  - `pf_pool_start` (function, line 227) `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                  pf_fetch_f...`
  - `pf_pool_take` (function, line 271) `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,
                 char **body,...`
  - `pf_pool_finish` (function, line 310) `void pf_pool_finish(pf_pool *p)`
  - `pf_pooled_fetch` (function, line 324) `int pf_pooled_fetch(void *vctx, const char *method, const char *url,
                    const ch...`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
  - `PF_MAX_URL` (macro, line 21) `#define PF_MAX_URL`
- Depends on: `include/prefetch.h`

## src/prefs.c
- Layer: utility
- Language: c
- Symbols:
  - `sbuf` (struct, line 367)
  - `url_valid` (function, line 26) `static int url_valid(const char *url)`
  - `title_clean` (function, line 39) `static char *title_clean(const char *src)`
  - `prefs_init` (function, line 66) `void prefs_init(prefs_state *p)`
  - `prefs_free` (function, line 74) `void prefs_free(prefs_state *p)`
  - `bookmark_push` (function, line 91) `static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title)`
  - `history_push_back` (function, line 109) `static prefs_status history_push_back(prefs_state *p, const char *url)`
  - `prefs_bookmark_index` (function, line 125) `int prefs_bookmark_index(const prefs_state *p, const char *url)`
  - `prefs_bookmark_toggle` (function, line 132) `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,
                             ...`
  - `prefs_history_add` (function, line 152) `prefs_status prefs_history_add(prefs_state *p, const char *url)`
  - `prefs_format` (function, line 183) `prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len)`
  - `apply_kv` (function, line 225) `static void apply_kv(prefs_state *out, const char *key, long val)`
  - `prefs_parse` (function, line 241) `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)`
  - `ci_eq` (function, line 300) `static int ci_eq(char a, char b)`
  - `ci_starts` (function, line 306) `static int ci_starts(const char *s, const char *q)`
  - `ci_contains` (function, line 314) `static int ci_contains(const char *s, const char *q)`
  - `url_prefix_match` (function, line 323) `static int url_prefix_match(const char *url, const char *q)`
  - `sugg_push` (function, line 335) `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,
                      cons...`
  - `prefs_suggest` (function, line 344) `int prefs_suggest(const prefs_state *p, const char *query,
                  char *out, size_t ro...`
  - `sb_put` (function, line 369) `static void sb_put(sbuf *b, const char *s, size_t n)`
  - `sb_str` (function, line 384) `static void sb_str(sbuf *b, const char *s)`
  - `sb_esc` (function, line 387) `static void sb_esc(sbuf *b, const char *s)`
  - `sb_link_item` (function, line 400) `static void sb_link_item(sbuf *b, const char *url, const char *label)`
  - `prefs_bookmarks_page` (function, line 408) `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)`
  - `_POSIX_C_SOURCE` (macro, line 11) `#define _POSIX_C_SOURCE`
  - `PREFS_MAGIC` (macro, line 20) `#define PREFS_MAGIC`
- Depends on: `include/prefs.h`, `include/zoom.h`

## src/profile.c
- Layer: utility
- Language: c
- Symbols:
  - `join_path` (function, line 29) `static int join_path(const profile_ctx *ctx, const char *name,
                     char *out, si...`
  - `keyfile_create` (function, line 36) `static profile_status keyfile_create(const char *dir, const char *path,
                         ...`
  - `profile_open` (function, line 59) `profile_status profile_open(profile_ctx *ctx, const char *dir)`
  - `map_ds` (function, line 98) `static profile_status map_ds(ds_status ds)`
  - `profile_load` (function, line 112) `profile_status profile_load(const profile_ctx *ctx, prefs_state *out)`
  - `profile_save` (function, line 133) `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p)`
  - `profile_close` (function, line 149) `void profile_close(profile_ctx *ctx)`
  - `_POSIX_C_SOURCE` (macro, line 11) `#define _POSIX_C_SOURCE`
  - `PROFILE_KEYFILE_LEN` (macro, line 27) `#define PROFILE_KEYFILE_LEN`
- Depends on: `include/disk_store.h`, `include/profile.h`

## src/render_doc.c
- Layer: presentation
- Language: c
- Symbols:
  - `utf8_sanitized_dup` (function, line 28) `static char *utf8_sanitized_dup(const char *s)`
  - `rd_push` (function, line 60) `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,
                 ...`
  - `rd_push_input` (function, line 195) `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)`
  - `resolve_image_decision` (function, line 230) `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,
        ...`
  - `rd_build` (function, line 252) `rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_u...`
  - `unset` (function, line 619) `* background paints as if unset (no border/box-shadow-style
                 * "broken image" pla...`
  - `rd_free` (function, line 684) `void rd_free(rd_doc *d)`
  - `rd_count` (function, line 700) `size_t rd_count(const rd_doc *d)`
  - `rd_at` (function, line 704) `const rd_block *rd_at(const rd_doc *d, size_t i)`
  - `rd_box_count` (function, line 709) `size_t rd_box_count(const rd_doc *d)`
  - `rd_box_at` (function, line 713) `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)`
  - `rd_cont_count` (function, line 718) `size_t rd_cont_count(const rd_doc *d)`
  - `rd_cont_at` (function, line 722) `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)`
  - `rd_kind_name` (function, line 727) `const char *rd_kind_name(rd_kind k)`
  - `rd_block_tag` (function, line 741) `const char *rd_block_tag(const rd_block *b)`
  - `rd_input_label` (function, line 772) `const char *rd_input_label(int input_type)`
  - `rd_input_invisible` (function, line 792) `int rd_input_invisible(int input_type)`
  - `rd_image_label` (function, line 796) `const char *rd_image_label(rdp_img_decision d)`
  - `rd_image_fail_label` (function, line 807) `const char *rd_image_fail_label(img_fail_reason reason)`
  - `place` (function, line 220) `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never resolved, never touches the network either way);`
- Depends on: `include/box_style.h`, `include/css.h`, `include/data_url.h`, `include/render_doc.h`, `include/url.h`, `include/util.h`

## src/render_policy.c
- Layer: presentation
- Language: c
- Symbols:
  - `rdp_caps_safe` (function, line 17) `rdp_caps rdp_caps_safe(void)`
  - `rdp_is_tracking_pixel` (function, line 22) `int rdp_is_tracking_pixel(int w, int h)`
  - `rdp_image_decision` (function, line 28) `rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char...`
  - `rdp_img_reason` (function, line 63) `const char *rdp_img_reason(rdp_img_decision d)`
  - `rdp_images_warning` (function, line 74) `const char *rdp_images_warning(void)`
- Depends on: `include/data_url.h`, `include/render_policy.h`, `include/request_policy.h`

## src/renderer.c
- Layer: presentation
- Language: c
- Symbols:
  - `child_render` (function, line 25) `static void child_render(int wfd, const char *html, size_t len)`
  - `read_field` (function, line 53) `static int read_field(int fd, char **out, size_t *out_len)`
  - `rd_render_html` (function, line 70) `rd_status rd_render_html(const char *html, size_t len, rd_result *out)`
  - `rd_result_free` (function, line 120) `void rd_result_free(rd_result *out)`
  - `write_full` (function, line 40) `&& write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 || write_full(wfd, title, tl) == 0) && write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0);`
  - `_POSIX_C_SOURCE` (macro, line 7) `#define _POSIX_C_SOURCE`
- Depends on: `include/html_parse.h`, `include/os_sandbox.h`, `include/renderer.h`, `include/util.h`

## src/request_policy.c
- Layer: business_logic
- Language: c
- Symbols:
  - `lower` (function, line 22) `static char lower(char c)`
  - `ci_starts_with` (function, line 26) `static int ci_starts_with(const char *s, const char *prefix)`
  - `psl_cmp` (function, line 36) `static int psl_cmp(const void *key, const void *elem)`
  - `psl_in` (function, line 40) `static int psl_in(const char *const *arr, size_t n, const char *key)`
  - `public_suffix_labels` (function, line 48) `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)`
  - `rp_host_of` (function, line 76) `int rp_host_of(const char *url, char *out, size_t out_size)`
  - `rp_site_of` (function, line 102) `int rp_site_of(const char *host, char *out, size_t out_size)`
  - `rp_same_site` (function, line 134) `int rp_same_site(const char *top_level_url, const char *request_url)`
  - `rp_evaluate` (function, line 143) `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)`
  - `RP_MAX_HOST` (macro, line 17) `#define RP_MAX_HOST`
  - `RP_MAX_LABELS` (macro, line 18) `#define RP_MAX_LABELS`
- Depends on: `include/psl_data.h`, `include/request_policy.h`

## src/secure_fetch.c
- Layer: utility
- Language: c
- Symbols:
  - `body_sink` (struct, line 434)
  - `tls_capture` (struct, line 447)
  - `fetch_ctx` (struct, line 457)
  - `sf_ws` (struct, line 1098)
  - `sink` (type_alias, line 456) `typedef struct fetch_ctx { body_sink sink;`
  - `ci_starts_with` (function, line 44) `static int ci_starts_with(const char *haystack, const char *prefix)`
  - `ci_index` (function, line 56) `static long ci_index(const char *haystack, const char *needle)`
  - `sf_share_lock` (function, line 68) `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...`
  - `sf_share_unlock` (function, line 74) `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)`
  - `sf_global_init` (function, line 81) `void sf_global_init(void)`
  - `sf_cookie_line_matches` (function, line 96) `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...`
  - `sf_url_host_path` (function, line 151) `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...`
  - `sf_cookie_header_for` (function, line 166) `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)`
  - `sf_cookie_put` (function, line 195) `void sf_cookie_put(const char *url, const char *namevalue)`
  - `sf_config_default` (function, line 216) `sf_config sf_config_default(void)`
  - `sf_user_agent_or_default` (function, line 241) `const char *sf_user_agent_or_default(const char *ua)`
  - `sf_impersonate_kex_groups` (function, line 245) `const char *sf_impersonate_kex_groups(void)`
  - `sf_impersonate_tls13_ciphers` (function, line 246) `const char *sf_impersonate_tls13_ciphers(void)`
  - `sf_validate_url` (function, line 250) `sf_status sf_validate_url(const char *url)`
  - `sf_url_is_http` (function, line 258) `static int sf_url_is_http(const char *url)`
  - `sf_check_tls_version` (function, line 270) `sf_status sf_check_tls_version(const char *negotiated_version)`
  - `sf_check_group_is_pq` (function, line 275) `sf_status sf_check_group_is_pq(const char *negotiated_group)`
  - `sf_check_chain_policy` (function, line 284) `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)`
  - `sf_enforce_policy` (function, line 294) `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...`
  - `copy_checked` (function, line 325) `static int copy_checked(char *dst, size_t dstsz, const char *src)`
  - `sf_is_redirect_code` (function, line 334) `int sf_is_redirect_code(long http_code)`
  - `sf_parse_location_header` (function, line 341) `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)`
  - `sf_resolve_redirect` (function, line 359) `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...`
  - `sf_ci_prefix` (function, line 371) `static int sf_ci_prefix(const char *s, const char *p)`
  - `sf_response_free` (function, line 411) `void sf_response_free(sf_response *resp)`
  - `copy_bounded` (function, line 470) `static void copy_bounded(char *dst, size_t dstsz, const char *src)`
  - `get_negotiated_group_name` (function, line 481) `static const char *get_negotiated_group_name(SSL *ssl)`
  - `tls_capture_try` (function, line 514) `static void tls_capture_try(tls_capture *cap)`
  - `tls_capture_from_ssl` (function, line 524) `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)`
  - `header_cb` (function, line 550) `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)`
  - `write_cb` (function, line 586) `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)`
  - `name_is_pq_sig` (function, line 618) `static int name_is_pq_sig(int pknid)`
  - `inspect_chain` (function, line 628) `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)`
  - `map_curl_error` (function, line 681) `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)`
  - `add_header` (function, line 722) `static int add_header(struct curl_slist **h, const char *line)`
  - `sf_setup_handle` (function, line 736) `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,
           ...`
  - `redirect` (function, line 811) `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...`
  - `sf_perform` (function, line 879) `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...`
  - `sf_get` (function, line 1014) `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)`
  - `sf_post` (function, line 1018) `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...`
  - `sf_get_follow` (function, line 1032) `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...`
  - `ws_ssl_info_cb` (function, line 1084) `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)`
  - `ws_ssl_ctx_cb` (function, line 1091) `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)`
  - `sf_ws_url_check` (function, line 1105) `sf_status sf_ws_url_check(const char *url)`
  - `ws_free` (function, line 1117) `static void ws_free(sf_ws *ws)`
  - `sf_ws_open` (function, line 1126) `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)`
  - `sf_ws_send` (function, line 1181) `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)`
  - `sf_ws_recv` (function, line 1204) `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)`
  - `sf_ws_fd` (function, line 1226) `int sf_ws_fd(const sf_ws *ws)`
  - `sf_ws_close` (function, line 1233) `void sf_ws_close(sf_ws *ws)`
  - `module` (function, line 364) `* pure url module (DRY);`
  - `progress` (function, line 443) `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);`
  - `database` (function, line 485) `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid handshake as unnamed and the * policy check rejects it -- exactly the sites doing TLS r`
  - `group` (function, line 499) `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);`
  - `this` (function, line 531) `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and causes false rejections. * If it is NULL (no group / not TLS 1.3 / no PFS), we copy ""`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
- Depends on: `include/anti_fp.h`, `include/secure_fetch.h`, `include/url.h`

## src/svg_render.c
- Layer: presentation
- Doc: svg_render — inline <svg> markup -> a bounded list of geometric shapes.
- Language: c
- Symbols:
  - `sv_attr` (struct, line 91)
  - `sv_ctx` (struct, line 151)
  - `stroke` (type_alias, line 151) `typedef struct sv_ctx { int fill, stroke;`
  - `sv_is_space` (function, line 21) `static int sv_is_space(char c)`
  - `sv_is_digit` (function, line 25) `static int sv_is_digit(char c)`
  - `sv_lower` (function, line 27) `static char sv_lower(char c)`
  - `sv_span_eq` (function, line 32) `static int sv_span_eq(const char *s, size_t n, const char *lit)`
  - `sv_sep` (function, line 82) `static void sv_sep(const char *s, size_t n, size_t *i)`
  - `sv_attr_get` (function, line 99) `static const char *sv_attr_get(const sv_attr *at, size_t nat, const char *name, size_t *len)`
  - `sv_attr_num` (function, line 108) `static double sv_attr_num(const sv_attr *at, size_t nat, const char *name, double dflt)`
  - `sv_mat_identity` (function, line 161) `static void sv_mat_identity(double *m)`
  - `sv_mat_mul` (function, line 166) `static void sv_mat_mul(const double *a, const double *b, double *out)`
  - `sv_parse_transform` (function, line 179) `static void sv_parse_transform(const char *s, size_t n, double *m)`
  - `sv_style_next` (function, line 238) `static int sv_style_next(const char *s, size_t n, size_t *i,
                         const char ...`
  - `sv_apply_prop` (function, line 260) `static void sv_apply_prop(sv_ctx *ctx, const char *nm, size_t nl,
                          const...`
  - `sv_ctx_from_attrs` (function, line 307) `static void sv_ctx_from_attrs(sv_ctx *ctx, const sv_attr *at, size_t nat)`
  - `sv_new_shape` (function, line 324) `static sv_shape *sv_new_shape(sv_image *im, int kind, const sv_ctx *ctx)`
  - `sv_parse_points` (function, line 343) `static void sv_parse_points(sv_image *im, sv_shape *sh, const char *s, size_t n)`
  - `sv_new_seg` (function, line 363) `static sv_seg *sv_new_seg(sv_image *im, sv_shape *sh)`
  - `sv_seg_move` (function, line 371) `static int sv_seg_move(sv_image *im, sv_shape *sh, double x, double y)`
  - `sv_seg_line` (function, line 378) `static int sv_seg_line(sv_image *im, sv_shape *sh, double x, double y)`
  - `sv_seg_cubic` (function, line 385) `static int sv_seg_cubic(sv_image *im, sv_shape *sh,
                        double x1, double y1,...`
  - `sv_arc_to_cubics` (function, line 399) `static int sv_arc_to_cubics(sv_image *im, sv_shape *sh,
                            double x0, do...`
  - `sv_parse_path` (function, line 477) `static void sv_parse_path(sv_image *im, sv_shape *sh, const char *s, size_t n)`
  - `sv_is_dropped_element` (function, line 635) `static int sv_is_dropped_element(const char *name, size_t n)`
  - `sv_scan_attrs` (function, line 647) `static void sv_scan_attrs(const char *s, size_t n, size_t *i,
                          sv_attr *...`
  - `sv_skip_subtree` (function, line 693) `static void sv_skip_subtree(const char *s, size_t n, size_t *i, const char *name, size_t nlen)`
  - `sv_collect_text` (function, line 725) `static void sv_collect_text(const char *s, size_t n, size_t *i, char *dst, size_t cap)`
  - `sv_fit` (function, line 743) `void sv_fit(const sv_image *img, double dw, double dh,
            double *scale, double *off_x, ...`
  - `sv_parse` (function, line 763) `sv_status sv_parse(const char *markup, size_t len, sv_image *out)`
  - `sv_parse_ex` (function, line 767) `sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill)`
  - `point` (function, line 556) `* current point (SVG 8.3.6). */ int had = (prev == 'C' || prev == 'c' || prev == 'S' || prev == 's');`
  - `SV_MAX_ATTRS` (macro, line 96) `#define SV_MAX_ATTRS`
- Depends on: `include/css_color.h`, `include/svg_render.h`

## src/tab.c
- Layer: utility
- Language: c
- Symbols:
  - `child_state` (struct, line 124)
  - `tab` (struct, line 1918)
  - `child_reset_page` (function, line 155) `static void child_reset_page(child_state *cs)`
  - `policy` (function, line 175) `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a
 * compromi...`
  - `run_js` (function, line 229) `* regardless of run_js (a no-JS load simply never records a request). */
static int child_load(ch...`
  - `write_field` (function, line 296) `static int write_field(int fd, const char *s)`
  - `blocks` (function, line 330) `*
 * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the
 * grid arr...`
  - `FB_MAX_FILE_BYTES` (function, line 698) `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...`
  - `budget_remaining_ms` (function, line 728) `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)`
  - `ctype_is_javascript` (function, line 742) `static int ctype_is_javascript(const char *ctype)`
  - `ctype_is_css` (function, line 751) `static int ctype_is_css(const char *ctype)`
  - `log_external_skip` (function, line 759) `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...`
  - `run` (function, line 777) `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...`
  - `tab_url_resolve` (function, line 826) `static int tab_url_resolve(void *ctx, const char *base, const char *ref,
                        ...`
  - `tab_mod_resolve` (function, line 835) `static int tab_mod_resolve(void *host, const char *base, const char *spec,
                      ...`
  - `tab_mod_fetch` (function, line 857) `static char *tab_mod_fetch(void *host, const char *url, size_t *len)`
  - `write_history` (function, line 879) `static int write_history(int wfd, child_state *cs)`
  - `window` (function, line 898) `* net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs)`
  - `child_handle_load` (function, line 943) `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...`
  - `swap` (function, line 1264) `* display:none hiding an element via class swap (CSS, not
     * DOM removal). */
    if (ok && v...`
  - `write_ws` (function, line 1306) `static int write_ws(int wfd, child_state *cs)`
  - `write_storage` (function, line 1323) `static int write_storage(int wfd, child_state *cs)`
  - `write_opens` (function, line 1337) `static int write_opens(int wfd, child_state *cs)`
  - `child_next_timer_ms` (function, line 1349) `static int32_t child_next_timer_ms(child_state *cs)`
  - `child_handle_mutation` (function, line 1364) `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...`
  - `child_handle_click` (function, line 1443) `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)`
  - `child_handle_tick` (function, line 1447) `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)`
  - `child_handle_event` (function, line 1457) `static void child_handle_event(int wfd, child_state *cs)`
  - `child_handle_mouse` (function, line 1505) `static void child_handle_mouse(int wfd, child_state *cs)`
  - `geom_parent` (function, line 1535) `static dom_node_id geom_parent(void *ctx, dom_node_id n)`
  - `child_handle_geom` (function, line 1543) `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)`
  - `child_handle_submit` (function, line 1567) `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)`
  - `child_handle_eval` (function, line 1601) `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)`
  - `child_handle_decode_image` (function, line 1634) `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)`
  - `child_handle_decode_image_b64` (function, line 1656) `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)`
  - `gen_session_key` (function, line 1668) `static uint64_t gen_session_key(void)`
  - `tab_worker_run` (function, line 1688) `static void tab_worker_run(int rfd, int wfd)`
  - `parse_worker_fd` (function, line 1886) `static int parse_worker_fd(const char *s, int *out)`
  - `tab_parse_worker_args` (function, line 1898) `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)`
  - `tab_worker_dispatch` (function, line 1908) `void tab_worker_dispatch(int argc, char **argv)`
  - `ignore_sigpipe` (function, line 1942) `static void ignore_sigpipe(void)`
  - `tab_refresh_alive` (function, line 1949) `static void tab_refresh_alive(tab *t)`
  - `read_field` (function, line 1968) `static int read_field(int fd, char **out, size_t *out_len)`
  - `read_view` (function, line 1984) `static int read_view(int fd, pv_view **out)`
  - `read_console` (function, line 2426) `static int read_console(int fd, fb_buffer *out)`
  - `send_request` (function, line 2463) `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)`
  - `io_failure` (function, line 2473) `static tab_status io_failure(tab *t)`
  - `exec_worker_child` (function, line 2481) `static void exec_worker_child(int rfd, int wfd)`
  - `tab_set_fetcher` (function, line 2552) `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)`
  - `tab_set_net_allowed` (function, line 2558) `void tab_set_net_allowed(tab *t, int allowed)`
  - `tab_set_css_allowed` (function, line 2563) `void tab_set_css_allowed(tab *t, int allowed)`
  - `tab_set_viewport_w` (function, line 2568) `void tab_set_viewport_w(tab *t, int px)`
  - `tab_set_cookies` (function, line 2573) `void tab_set_cookies(tab *t, const char *cookies)`
  - `tab_subreq_permitted` (function, line 2579) `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)`
  - `answered` (function, line 2591) `* A refused frame is still consumed and answered (status 0), so the protocol never
 * desyncs. Re...`
  - `hist_ops_free` (function, line 2627) `static void hist_ops_free(tab_hist_op *ops, size_t n)`
  - `is_activation_event` (function, line 2692) `static int is_activation_event(const char *type)`
  - `open_urls_free` (function, line 2701) `static void open_urls_free(char **u, size_t n)`
  - `read_opens` (function, line 2711) `static tab_status read_opens(tab *t, const char *page_url, int gesture,
                         ...`
  - `ws_ops_free` (function, line 2740) `static void ws_ops_free(tab_ws_op *ops, size_t n)`
  - `read_ws` (function, line 2749) `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)`
  - `gate_js_nav` (function, line 2818) `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)`
  - `tab_load` (function, line 2828) `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)`
  - `tab_load_ex` (function, line 2832) `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)`
  - `tab_load_full` (function, line 2836) `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...`
  - `tab_click` (function, line 3022) `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)`
  - `tab_tick` (function, line 3029) `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)`
  - `tab_submit` (function, line 3038) `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)`
  - `tab_read_view` (function, line 3143) `tab_status tab_read_view(tab *t, tab_page *out)`
  - `tab_read_view_ex` (function, line 3147) `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)`
  - `tab_eval` (function, line 3243) `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)`
  - `tab_decode_image_op` (function, line 3283) `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...`
  - `tab_decode_image` (function, line 3325) `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)`
  - `tab_decode_image_data_url` (function, line 3331) `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)`
  - `tab_alive` (function, line 3349) `int tab_alive(const tab *t)`
  - `tab_child_pid` (function, line 3355) `pid_t tab_child_pid(const tab *t)`
  - `tab_close` (function, line 3359) `void tab_close(tab *t)`
  - `tab_page_free` (function, line 3374) `void tab_page_free(tab_page *p)`
  - `tab_eval_result_free` (function, line 3404) `void tab_eval_result_free(tab_eval_result *r)`
  - `tab_image_free` (function, line 3413) `void tab_image_free(tab_image *img)`
  - `tab_set_geometry` (function, line 3423) `tab_status tab_set_geometry(tab *t, const jg_table *g)`
  - `tab_popstate` (function, line 3449) `tab_status tab_popstate(tab *t, int index, tab_page *out)`
  - `tab_ws_event` (function, line 3455) `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,
       ...`
  - `tab_set_storage` (function, line 3474) `void tab_set_storage(tab *t, const char *blob, size_t len)`
  - `buffer` (function, line 272) `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of run_js so the REPL works on any page. */ fb_buffer_reset(&cs->log);`
  - `host` (function, line 284) `* granted net access for this host (allow.conf AND js.conf). Otherwise they stay * undefined (Same-Origin-by-construction holds). child_fetch still refuses unless * net_active is set during the script`
  - `fallback` (function, line 1019) `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it even with JS on. */ (void)pv_build_styled(cs->doc, run_js, reader, prefers_dark, cs->`
  - `WHERE` (function, line 1177) `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value != NULL) fb_buffer_push_loc(&cs->log, FB_ERROR, r.value, r.value_len, r.file != NUL`
  - `content` (function, line 1210) `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video> elements in the DOM for any * found. */ if (cs->idx != NULL) jd_process_iframes(cs->js, cs`
  - `once` (function, line 1255) `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);`
  - `write_full` (function, line 1284) `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0) && write_view(wfd, write_which) == 0 && write_full(wfd, &nlen, sizeof nlen) == 0 && (nlen == 0 || write_full(wfd,`
  - `EPIPE` (function, line 1690) `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();`
  - `tzset` (function, line 1706) `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);`
  - `depth` (function, line 1711) `* defense in depth (seccomp already excludes open/socket/exec);`
  - `load` (function, line 1925) `* subresource requests this load (set per page: host in allow.conf AND js.conf);`
  - `layout` (function, line 2133) `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property. */ pv_set_box_pct(v, (int)bwpct, (int)b[36], (int)b[37], (int)b[38], (int)b[39]);`
  - `column` (function, line 2144) `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation as text runs. */ pv_set_container(v, (int)cid, (int)cdisp, (int)cgap, (int)cjust, (in`
  - `_GNU_SOURCE` (macro, line 14) `#define _GNU_SOURCE`
  - `TAB_SCREEN_W` (macro, line 57) `#define TAB_SCREEN_W`
  - `TAB_SCREEN_H` (macro, line 58) `#define TAB_SCREEN_H`
  - `TAB_WIRE_HEAD_N` (macro, line 62) `#define TAB_WIRE_HEAD_N`
  - `TAB_WIRE_A_N` (macro, line 63) `#define TAB_WIRE_A_N`
  - `TAB_WIRE_B_N` (macro, line 64) `#define TAB_WIRE_B_N`
  - `TAB_WIRE_BOX_F_N` (macro, line 65) `#define TAB_WIRE_BOX_F_N`
  - `TAB_WIRE_GRID_N` (macro, line 66) `#define TAB_WIRE_GRID_N`
  - `TAB_MAX_RUNS` (macro, line 70) `#define TAB_MAX_RUNS`
  - `PV_MAX_CONTAINERS_WIRE` (macro, line 74) `#define PV_MAX_CONTAINERS_WIRE`
  - `TAB_MAX_URL` (macro, line 77) `#define TAB_MAX_URL`
  - `TAB_MAX_WS_MSG` (macro, line 86) `#define TAB_MAX_WS_MSG`
  - `TAB_MAX_STORAGE` (macro, line 90) `#define TAB_MAX_STORAGE`
  - `TAB_MAX_HIST_OPS` (macro, line 94) `#define TAB_MAX_HIST_OPS`
  - `TAB_MAX_HIST_BYTES` (macro, line 95) `#define TAB_MAX_HIST_BYTES`
  - `TAB_MAX_OPENS` (macro, line 97) `#define TAB_MAX_OPENS`
  - `TAB_MAX_OPEN_BYTES` (macro, line 98) `#define TAB_MAX_OPEN_BYTES`
  - `TAB_MAX_GEOM_WORDS` (macro, line 101) `#define TAB_MAX_GEOM_WORDS`
  - `TAB_MAX_SUBREQ` (macro, line 111) `#define TAB_MAX_SUBREQ`
  - `TAB_MAX_SUBRESOURCE` (macro, line 112) `#define TAB_MAX_SUBRESOURCE`
  - `TAB_MAX_JS_JOBS` (macro, line 113) `#define TAB_MAX_JS_JOBS`
  - `TAB_MAX_EXTERN_CSS` (macro, line 771) `#define TAB_MAX_EXTERN_CSS`
- Depends on: `include/anti_fp.h`, `include/box_tree.h`, `include/css.h`, `include/data_url.h`, `include/dom.h`, `include/freebug.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/image_decode.h`, `include/import_map.h`, `include/js_dom.h`, `include/js_env.h`, `include/js_sandbox.h`, `include/js_trusted.h`, `include/link_nav.h`, `include/os_sandbox.h`, `include/page_view.h`, `include/request_policy.h`, `include/tab.h`, `include/url.h`, `include/util.h`, `include/web_storage.h`

## src/text_shape.c
- Layer: utility
- Language: c
- Symbols:
  - `tsh_entry` (struct, line 34)
  - `loaded` (type_alias, line 33) `typedef struct tsh_entry { int loaded;`
  - `generic_name` (function, line 54) `static const char *generic_name(int family)`
  - `backend_init` (function, line 64) `static int backend_init(void)`
  - `read_font_file` (function, line 81) `static unsigned char *read_font_file(const char *path, long *out_n)`
  - `load_entry` (function, line 97) `static int load_entry(tsh_entry *e, int family, int bold, int italic)`
  - `get_entry` (function, line 152) `static tsh_entry *get_entry(int family, int bold, int italic)`
  - `tsh_ready` (function, line 164) `int tsh_ready(void)`
  - `tsh_shape` (function, line 169) `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                ...`
  - `tsh_measure` (function, line 214) `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)`
  - `tsh_draw` (function, line 221) `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, doub...`
  - `tsh_shutdown` (function, line 243) `void tsh_shutdown(void)`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
  - `TSH_MAX_FONT_BYTES` (macro, line 28) `#define TSH_MAX_FONT_BYTES`
  - `TSH_CACHE_SLOTS` (macro, line 32) `#define TSH_CACHE_SLOTS`
- Depends on: `include/css.h`, `include/text_shape.h`

## src/textfield.c
- Layer: utility
- Language: c
- Symbols:
  - `whole` (function, line 6) `* the buffer is rejected whole (fail closed), never applied partially.
 */

#include "textfield.h...`
  - `tf_clear` (function, line 20) `void tf_clear(tf_field *f)`
  - `tf_set` (function, line 24) `tf_status tf_set(tf_field *f, const char *s)`
  - `tf_insert` (function, line 35) `tf_status tf_insert(tf_field *f, char c)`
  - `tf_backspace` (function, line 47) `void tf_backspace(tf_field *f)`
  - `tf_delete` (function, line 55) `void tf_delete(tf_field *f)`
  - `tf_move` (function, line 62) `void tf_move(tf_field *f, long delta)`
  - `tf_home` (function, line 73) `void tf_home(tf_field *f)`
  - `tf_end` (function, line 78) `void tf_end(tf_field *f)`
  - `tf_text` (function, line 83) `const char *tf_text(const tf_field *f)`
  - `tf_len` (function, line 87) `size_t tf_len(const tf_field *f)`
  - `tf_cursor` (function, line 91) `size_t tf_cursor(const tf_field *f)`
- Depends on: `include/textfield.h`

## src/tls_impersonate.c
- Layer: utility
- Language: c
- Symbols:
  - `ti_wr` (struct, line 33)
  - `ti_rd` (struct, line 63)
  - `ti_should_impersonate` (function, line 18) `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,
                          i...`
  - `bounded_len` (function, line 25) `static size_t bounded_len(const char *s, size_t max)`
  - `put_u8` (function, line 35) `static void put_u8(ti_wr *w, uint8_t v)`
  - `put_u32` (function, line 40) `static void put_u32(ti_wr *w, uint32_t v)`
  - `put_u64` (function, line 48) `static void put_u64(ti_wr *w, uint64_t v)`
  - `put_blob` (function, line 53) `static void put_blob(ti_wr *w, const uint8_t *b, size_t n)`
  - `get_u8` (function, line 65) `static uint8_t get_u8(ti_rd *r)`
  - `get_u32` (function, line 70) `static uint32_t get_u32(ti_rd *r)`
  - `get_u64` (function, line 80) `static uint64_t get_u64(ti_rd *r)`
  - `get_bytes` (function, line 89) `static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len)`
  - `get_str` (function, line 103) `static char *get_str(ti_rd *r, size_t cap)`
  - `valid_profile` (function, line 116) `static int valid_profile(int p)`
  - `ti_encode_req` (function, line 122) `size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap)`
  - `ti_decode_req` (function, line 140) `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out)`
  - `ti_req_free` (function, line 166) `void ti_req_free(ti_req *r)`
  - `ti_encode_resp` (function, line 177) `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap)`
  - `ti_decode_resp` (function, line 196) `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out)`
  - `ti_resp_free` (function, line 230) `void ti_resp_free(ti_resp *r)`
- Depends on: `include/tls_impersonate.h`

## src/ui_layout.c
- Layer: presentation
- Language: c
- Symbols:
  - `layout_push` (function, line 13) `static int layout_push(ui_layout *lay, size_t offset, size_t len)`
  - `ui_wrap_text` (function, line 27) `ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out)`
  - `ui_layout_free` (function, line 91) `void ui_layout_free(ui_layout *lay)`
  - `ui_clamp_scroll` (function, line 99) `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines)`
- Depends on: `include/ui.h`

## src/url.c
- Layer: utility
- Language: c
- Symbols:
  - `ci_prefix` (function, line 20) `static int ci_prefix(const char *haystack, const char *prefix)`
  - `copy_checked` (function, line 32) `static int copy_checked(char *out, size_t outsz, const char *src)`
  - `cat_checked` (function, line 40) `static int cat_checked(char *out, size_t outsz, const char *src)`
  - `ncat_checked` (function, line 49) `static int ncat_checked(char *out, size_t outsz, const char *src, size_t n)`
  - `url_has_scheme` (function, line 59) `int url_has_scheme(const char *s)`
  - `url_is_https` (function, line 73) `int url_is_https(const char *s)`
  - `url_validate_https` (function, line 80) `url_status url_validate_https(const char *url)`
  - `url_authority_len` (function, line 91) `size_t url_authority_len(const char *url)`
  - `out_pop_segment` (function, line 102) `static void out_pop_segment(char *out, size_t *olen)`
  - `url_remove_dot_segments` (function, line 109) `url_status url_remove_dot_segments(const char *path, char *out, size_t outsz)`
  - `dir_len` (function, line 159) `static size_t dir_len(const char *base)`
  - `url_resolve_https` (function, line 170) `url_status url_resolve_https(const char *base, const char *ref,
                             char...`
  - `is_space` (function, line 218) `static int is_space(int c)`
  - `is_unreserved` (function, line 222) `static int is_unreserved(int c)`
  - `append_query_encoded` (function, line 229) `static int append_query_encoded(char *out, size_t outsz, const char *src)`
  - `assumed` (function, line 254) `* assumed (the caller already routed whitespace to search). */
static int looks_like_host(const c...`
  - `build_search` (function, line 303) `static url_status build_search(const char *query, char *out, size_t outsz)`
  - `url_omnibox` (function, line 309) `url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz)`
  - `host_equals` (function, line 378) `static int host_equals(const url_parts *p, const char *want)`
  - `query_find_q` (function, line 393) `static const char *query_find_q(const char *search, size_t len, size_t *vlen)`
  - `url_search_rewrite` (function, line 411) `url_status url_search_rewrite(const char *url, char *out, size_t outsz)`
  - `url_extract_userinfo` (function, line 431) `url_status url_extract_userinfo(const char *url, char *out, size_t outsz,
                       ...`
  - `url_is_file` (function, line 525) `int url_is_file(const char *s)`
  - `url_file_path` (function, line 531) `const char *url_file_path(const char *s)`
  - `url_resolve_file` (function, line 535) `url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz)`
  - `url_split` (function, line 584) `url_status url_split(const char *url, url_parts *out)`
  - `copy_bounded` (function, line 645) `static url_status copy_bounded(char *out, size_t outsz, const char *a, size_t alen,
             ...`
  - `url_history_target` (function, line 654) `url_status url_history_target(const char *base, const char *ref, char *out, size_t outsz)`
  - `_POSIX_C_SOURCE` (macro, line 9) `#define _POSIX_C_SOURCE`
- Depends on: `include/url.h`

## src/web_storage.c
- Layer: data_access
- Language: c
- Symbols:
  - `wst_origin` (struct, line 12)
  - `wst_db` (struct, line 20)
  - `key_ref` (struct, line 54)
  - `get_u32` (function, line 25) `static uint32_t get_u32(const unsigned char *p)`
  - `utf8_ok` (function, line 32) `static int utf8_ok(const unsigned char *s, size_t n)`
  - `key_cmp` (function, line 56) `static int key_cmp(const void *a, const void *b)`
  - `check` (function, line 65) `static int check(const char *blob, size_t len, size_t *bytes_out)`
  - `wst_decode_check` (function, line 101) `int wst_decode_check(const char *blob, size_t len)`
  - `wst_new` (function, line 105) `wst_db *wst_new(void)`
  - `wst_free` (function, line 109) `void wst_free(wst_db *db)`
  - `find` (function, line 118) `static wst_origin *find(const wst_db *db, const char *origin)`
  - `wst_encode` (function, line 125) `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len)`
  - `wst_replace` (function, line 140) `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len)`
  - `wst_origin_bytes` (function, line 175) `size_t wst_origin_bytes(const wst_db *db, const char *origin)`
  - `wst_foreach` (function, line 181) `int wst_foreach(const char *blob, size_t len,
                void (*fn)(void *ctx, const char *k...`
  - `put_u32` (function, line 201) `static void put_u32(char *b, uint32_t v)`
  - `wst_pack` (function, line 206) `int wst_pack(const char *const *keys, const size_t *klens,
             const char *const *vals, ...`
- Depends on: `include/web_storage.h`

## src/webcaps.c
- Layer: utility
- Language: c
- Symbols:
  - `wc_safe` (function, line 10) `wc_caps wc_safe(void)`
  - `wc_derive` (function, line 15) `wc_caps wc_derive(wc_input in)`
  - `wc_from_flags` (function, line 35) `wc_caps wc_from_flags(bool js, bool css, bool images)`
  - `wc_render_caps` (function, line 46) `rdp_caps wc_render_caps(wc_caps c)`
- Depends on: `include/webcaps.h`

## src/ws_hub.c
- Layer: utility
- Language: c
- Symbols:
  - `wh_conn` (struct, line 24)
  - `wh_hub` (struct, line 35)
  - `wh_job` (struct, line 43)
  - `used` (type_alias, line 23) `typedef struct wh_conn { int used;`
  - `wfd` (type_alias, line 43) `typedef struct wh_job { int wfd;`
  - `dup_str` (function, line 54) `static char *dup_str(const char *s)`
  - `job_free` (function, line 63) `static void job_free(wh_job *j)`
  - `job_str` (function, line 71) `static int job_str(wh_job *j, size_t slot, const char **field)`
  - `open_thread` (function, line 79) `static void *open_thread(void *arg)`
  - `conn_clear` (function, line 98) `static void conn_clear(wh_conn *c)`
  - `find_id` (function, line 104) `static wh_conn *find_id(wh_hub *h, int id)`
  - `find_token` (function, line 110) `static wh_conn *find_token(wh_hub *h, uint64_t token)`
  - `wh_new` (function, line 116) `wh_hub *wh_new(void)`
  - `wh_free` (function, line 129) `void wh_free(wh_hub *h)`
  - `wh_notify_fd` (function, line 144) `int wh_notify_fd(const wh_hub *h)`
  - `wh_open_async` (function, line 148) `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg)`
  - `wh_on_notify` (function, line 192) `void wh_on_notify(wh_hub *h, wh_emit_fn emit, void *ctx)`
  - `wh_send` (function, line 221) `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary)`
  - `wh_close` (function, line 228) `void wh_close(wh_hub *h, int id)`
  - `wh_close_all` (function, line 234) `void wh_close_all(wh_hub *h)`
  - `wh_poll_fds` (function, line 240) `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap)`
  - `fail_conn` (function, line 258) `static void fail_conn(wh_conn *c, int id, wh_emit_fn emit, void *ctx)`
  - `wh_on_readable` (function, line 266) `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx)`
  - `wh_count` (function, line 314) `size_t wh_count(const wh_hub *h)`
  - `_POSIX_C_SOURCE` (macro, line 6) `#define _POSIX_C_SOURCE`
  - `WH_READS_PER_PUMP` (macro, line 21) `#define WH_READS_PER_PUMP`
  - `WH_RECV_CHUNK` (macro, line 22) `#define WH_RECV_CHUNK`
- Depends on: `include/ws_hub.h`

## src/zoom.c
- Layer: utility
- Language: c
- Symbols:
  - `zm_clamp` (function, line 14) `int zm_clamp(int pct)`
  - `zm_zoom_in` (function, line 20) `int zm_zoom_in(int pct)`
  - `zm_zoom_out` (function, line 28) `int zm_zoom_out(int pct)`
  - `zm_reset` (function, line 36) `int zm_reset(void)`
  - `zm_scale` (function, line 40) `double zm_scale(int pct)`
  - `zm_apply` (function, line 44) `double zm_apply(double base_px, int pct)`
  - `ZM_LADDER_N` (macro, line 12) `#define ZM_LADDER_N`
- Depends on: `include/zoom.h`
