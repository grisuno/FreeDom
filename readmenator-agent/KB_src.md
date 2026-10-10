# Subsystem: src (page 1 of 8)
Pages: [KB_src.md](KB_src.md), [KB_src_p2.md](KB_src_p2.md), [KB_src_p3.md](KB_src_p3.md), [KB_src_p4.md](KB_src_p4.md), [KB_src_p5.md](KB_src_p5.md), [KB_src_p6.md](KB_src_p6.md), [KB_src_p7.md](KB_src_p7.md), [KB_src_p8.md](KB_src_p8.md)

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
- Doc: block_flow (bf_) -- vertical margin collapsing.
- Layer: utility
- Language: c
- Symbols:
  - `finite_or_zero` (function, line 11) `static double finite_or_zero(double v)`
  - `bf_collapse_n` (function, line 15) `double bf_collapse_n(const double *m, size_t n)`
  - `bf_collapse` (function, line 30) `double bf_collapse(double a, double b)`
  - `bf_margins_adjoin` (function, line 35) `int bf_margins_adjoin(double border_px, double padding_px)`
- Depends on: `include/block_flow.h`

## src/box_style.c
- Doc: tag_row: One row of the user-agent sheet.
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
  - `take` (function, line 293) `* caller has to take (Sizing 3 section 5.1), so to a resolver that only sums a * px and a percentage half they read...`
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
- Doc: layout_block: Block container: stack non-none children vertically, collapsing each child's top *...
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
- Doc: clear_status: #include <stdlib.h> #include <string.h> static void free_page(browser_state *bs) {...
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
- Doc: eff_z: Not a stacking context: a positioned box with z:auto still paints in the *...
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
- Doc: css_match: if (!(inherited_px > 0.0)) inherited_px = CL_INITIAL_FONT_SIZE; if (o->font_scale ==...
- Layer: utility
- Language: c
- Symbols:
  - `css_sheet` (struct, line 100)
  - `css_keyframe_stop` (struct, line 133)
  - `css_match` (struct, line 5485)
  - `css_cand` (struct, line 5491)
  - `css_rule` (struct, line 98)
  - `idx` (type_alias, line 5491) `typedef struct css_cand { int imp, espec, ord, idx;`
  - `parse_num` (function, line 167) `static int parse_num(const char *s, double *out, const char **endp)`
  - `parse_color` (function, line 178) `static int parse_color(const char *v)`
  - `interp_color` (function, line 182) `static int interp_color(const char *v)`
  - `through` (function, line 198) `* at the two SHARED chokepoints every property funnels through (the generic
 * dispatch tail, and...`
  - `bg_alpha_of` (function, line 218) `static int bg_alpha_of(const char *v)`
  - `interp_bg` (function, line 222) `static int interp_bg(const char *v)`
  - `expand_bg_image` (function, line 230) `static int expand_bg_image(const char *val, css_decl *dst, int cap,
                           ch...`
  - `expand_background` (function, line 235) `static int expand_background(const char *val, css_decl *dst, int cap,
                           ...`
  - `text` (function, line 247) `* source text (rem_rebase, see below) rather than by threading a context here.
 *
 * Viewport uni...`
  - `expand_box4` (function, line 267) `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,
            ...`
  - `expand_box2` (function, line 272) `static int expand_box2(const char *val, int slot_start, int slot_end,
                       int ...`
  - `interp_len` (function, line 277) `static int interp_len(const char *v, int allow_auto, int *out)`
  - `interp_lp` (function, line 281) `static int interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_...`
  - `lp_can_be_nonneg` (function, line 286) `static int lp_can_be_nonneg(int px_val, int pct_pm)`
  - `next_ws_token` (function, line 290) `static int next_ws_token(const char **p, char *tok, size_t cap)`
  - `interp_align` (function, line 294) `static int interp_align(const char *v)`
  - `interp_fontsize_ex` (function, line 298) `static int interp_fontsize_ex(const char *v, int *abs_out)`
  - `interp_lineheight` (function, line 302) `static int interp_lineheight(const char *v)`
  - `interp_weight` (function, line 306) `static int interp_weight(const char *v)`
  - `interp_style` (function, line 310) `static int interp_style(const char *v)`
  - `interp_textdeco` (function, line 314) `static int interp_textdeco(const char *v)`
  - `interp_display` (function, line 318) `static int interp_display(const char *v)`
  - `interp_gap` (function, line 322) `static int interp_gap(const char *v)`
  - `interp_justify` (function, line 326) `static int interp_justify(const char *v)`
  - `interp_gridcols` (function, line 330) `static int interp_gridcols(const char *v)`
  - `expand_grid_template_cols` (function, line 334) `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)`
  - `interp_fontfamily` (function, line 340) `static int interp_fontfamily(const char *v)`
  - `interp_texttransform` (function, line 341) `static int interp_texttransform(const char *v)`
  - `interp_opacity` (function, line 342) `static int interp_opacity(const char *v)`
  - `expand_valign` (function, line 343) `static int expand_valign(const char *val, css_decl *dst, int cap)`
  - `interp_transition_property` (function, line 344) `static int interp_transition_property(const char *v)`
  - `interp_whitespace` (function, line 345) `static int interp_whitespace(const char *v)`
  - `interp_tabsize` (function, line 346) `static int interp_tabsize(const char *v)`
  - `interp_textdeco_style` (function, line 347) `static int interp_textdeco_style(const char *v)`
  - `interp_textdeco_thickness` (function, line 348) `static int interp_textdeco_thickness(const char *v)`
  - `interp_aspect_ratio` (function, line 349) `static int interp_aspect_ratio(const char *v, int *num, int *den)`
  - `interp_direction` (function, line 350) `static int interp_direction(const char *v)`
  - `interp_liststyle` (function, line 351) `static int interp_liststyle(const char *v)`
  - `emit_spacing` (function, line 352) `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
  - `expand_shadow` (function, line 353) `static int expand_shadow(const char *val, css_decl *dst, int cap)`
  - `interp_position` (function, line 357) `static int interp_position(const char *v)`
  - `interp_boxsizing` (function, line 366) `static int interp_boxsizing(const char *v)`
  - `interp_float` (function, line 372) `static int interp_float(const char *v)`
  - `interp_clear` (function, line 379) `static int interp_clear(const char *v)`
  - `interp_visibility` (function, line 389) `static int interp_visibility(const char *v)`
  - `interp_overflow` (function, line 396) `static int interp_overflow(const char *v)`
  - `interp_cursor` (function, line 428) `static int interp_cursor(const char *v)`
  - `interp_text_overflow` (function, line 460) `static int interp_text_overflow(const char *v)`
  - `interp_word_break` (function, line 466) `static int interp_word_break(const char *v)`
  - `interp_overflow_wrap` (function, line 474) `static int interp_overflow_wrap(const char *v)`
  - `interp_border_collapse` (function, line 482) `static int interp_border_collapse(const char *v)`
  - `number` (function, line 491) `* number (no unit) as px (common in shorthand context like "10 5"). */
static int interp_border_s...`
  - `interp_empty_cells` (function, line 516) `static int interp_empty_cells(const char *v)`
  - `interp_caption_side` (function, line 523) `static int interp_caption_side(const char *v)`
  - `interp_table_layout` (function, line 530) `static int interp_table_layout(const char *v)`
  - `interp_font_variant` (function, line 537) `static int interp_font_variant(const char *v)`
  - `interp_hyphens` (function, line 545) `static int interp_hyphens(const char *v)`
  - `interp_user_select` (function, line 553) `static int interp_user_select(const char *v)`
  - `interp_caret_color` (function, line 562) `static int interp_caret_color(const char *v)`
  - `interp_appearance` (function, line 574) `static int interp_appearance(const char *v)`
  - `interp_pointer_events` (function, line 592) `static int interp_pointer_events(const char *v)`
  - `interp_bg_repeat` (function, line 604) `static int interp_bg_repeat(const char *v)`
  - `interp_bg_size` (function, line 614) `static int interp_bg_size(const char *v)`
  - `interp_bg_clip` (function, line 621) `static int interp_bg_clip(const char *v)`
  - `interp_bg_origin` (function, line 629) `static int interp_bg_origin(const char *v)`
  - `interp_bg_attachment` (function, line 636) `static int interp_bg_attachment(const char *v)`
  - `interp_isolation` (function, line 643) `static int interp_isolation(const char *v)`
  - `interp_contain` (function, line 649) `static int interp_contain(const char *v)`
  - `interp_content_visibility` (function, line 670) `static int interp_content_visibility(const char *v)`
  - `interp_image_rendering` (function, line 677) `static int interp_image_rendering(const char *v)`
  - `interp_color_scheme` (function, line 684) `static int interp_color_scheme(const char *v)`
  - `interp_accent_color` (function, line 702) `static int interp_accent_color(const char *v)`
  - `interp_print_color_adjust` (function, line 707) `static int interp_print_color_adjust(const char *v)`
  - `interp_forced_color_adjust` (function, line 713) `static int interp_forced_color_adjust(const char *v)`
  - `interp_mix_blend_mode` (function, line 720) `static int interp_mix_blend_mode(const char *v)`
  - `interp_object_fit` (function, line 738) `static int interp_object_fit(const char *v)`
  - `interp_list_style_pos` (function, line 747) `static int interp_list_style_pos(const char *v)`
  - `interp_font_kerning` (function, line 753) `static int interp_font_kerning(const char *v)`
  - `interp_text_rendering` (function, line 760) `static int interp_text_rendering(const char *v)`
  - `interp_font_stretch` (function, line 768) `static int interp_font_stretch(const char *v)`
  - `interp_resize` (function, line 781) `static int interp_resize(const char *v)`
  - `interp_scroll_behavior` (function, line 789) `static int interp_scroll_behavior(const char *v)`
  - `interp_overscroll_behavior` (function, line 811) `static int interp_overscroll_behavior(const char *v)`
  - `interp_backface_visibility` (function, line 818) `static int interp_backface_visibility(const char *v)`
  - `interp_border_style` (function, line 841) `static int interp_border_style(const char *v)`
  - `interp_bwidth1` (function, line 867) `static int interp_bwidth1(const char *v)`
  - `interp_time_ms` (function, line 876) `static int interp_time_ms(const char *v)`
  - `emit_radius_corner` (function, line 909) `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)`
  - `interp_bw_tok` (function, line 917) `static int interp_bw_tok(const char *t, int *o)`
  - `interp_bs_tok` (function, line 918) `static int interp_bs_tok(const char *t, int *o)`
  - `interp_bc_tok` (function, line 919) `static int interp_bc_tok(const char *t, int *o)`
  - `expand_outline` (function, line 984) `static int expand_outline(const char *val, css_decl *dst, int cap)`
  - `interp_column_count` (function, line 1000) `static int interp_column_count(const char *v)`
  - `interp_column_width` (function, line 1012) `static int interp_column_width(const char *v)`
  - `expand_columns` (function, line 1023) `static int expand_columns(const char *val, css_decl *dst, int cap)`
  - `expand_flex_flow` (function, line 1057) `static int expand_flex_flow(const char *val, css_decl *dst, int cap)`
  - `expand_column_rule` (function, line 1079) `static int expand_column_rule(const char *val, css_decl *dst, int cap)`
  - `interp_filter_pct` (function, line 1091) `static int interp_filter_pct(const char *s)`
  - `interp_filter_deg` (function, line 1105) `static int interp_filter_deg(const char *s)`
  - `filter_paren_body` (function, line 1120) `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)`
  - `item` (function, line 1133) `* timing list takes its first item (CSS Animations/Transitions 1: with one
 * transition/animatio...`
  - `anim_easing_iv` (function, line 1172) `static int anim_easing_iv(const char *tok)`
  - `is_anim_ident` (function, line 1184) `static int is_anim_ident(const char *tok)`
  - `expand_animation` (function, line 1200) `static int expand_animation(const char *val, css_decl *dst, int cap)`
  - `expand_backdrop_filter` (function, line 1468) `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)`
  - `axis` (function, line 1502) `* bare center displaces it to the free axis (`center right` = x:right, y:center).
 * Any other co...`
  - `expand_bg_size` (function, line 1618) `static int expand_bg_size(const char *val, css_decl *dst, int cap)`
  - `emit_content` (function, line 1658) `static int emit_content(css_decl *dst, int cap, const char *str,
                        char (*c...`
  - `expand_content` (function, line 1764) `static int expand_content(const char *val, css_decl *dst, int cap,
                          char...`
  - `expand_grid_areas` (function, line 1807) `static int expand_grid_areas(const char *val, css_decl *dst, int cap,
                           ...`
  - `expand_grid_template` (function, line 1874) `static int expand_grid_template(const char *val, css_decl *dst, int cap,
                        ...`
  - `expand_box_shadow` (function, line 1925) `static int expand_box_shadow(const char *val, css_decl *dst, int cap)`
  - `interp_flex_factor` (function, line 1953) `static int interp_flex_factor(const char *v)`
  - `interp_flex_basis` (function, line 1963) `static int interp_flex_basis(const char *v, int *out)`
  - `expand_flex` (function, line 1997) `static int expand_flex(const char *val, css_decl *dst, int cap)`
  - `interp_align_kw` (function, line 2042) `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)`
  - `interp_flex_direction` (function, line 2055) `static int interp_flex_direction(const char *v)`
  - `interp_box_orient` (function, line 2073) `static int interp_box_orient(const char *v)`
  - `interp_flex_line_pack` (function, line 2100) `static int interp_flex_line_pack(const char *v)`
  - `interp_flex_wrap` (function, line 2110) `static int interp_flex_wrap(const char *v)`
  - `interp_grid_flow` (function, line 2118) `static int interp_grid_flow(const char *v)`
  - `interp_grid_span` (function, line 2144) `static int interp_grid_span(const char *v)`
  - `copy_trim` (function, line 2163) `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)`
  - `strip_important` (function, line 2176) `static int strip_important(char *val)`
  - `var` (function, line 2201) `* cvr_resolve then substitutes var() references when a declaration's value is
 * interpreted (par...`
  - `selector_matches_root` (function, line 2223) `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m)`
  - `tr_mul` (function, line 2347) `static void tr_mul(double out[6], const double l[6], const double r[6])`
  - `tr_decompose` (function, line 2367) `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,
                        in...`
  - `parse_matrix6` (function, line 2390) `static int parse_matrix6(const char *p, size_t argn, double m6[6])`
  - `split_top_args` (function, line 2422) `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,
               ...`
  - `translate3d` (function, line 2452) `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine
 * renders z as nothing,...`
  - `function` (function, line 2726) `* transform function (perspective/rotate3d/...), or unparseable syntax,
 * rejects the WHOLE decl...`
  - `origin_component` (function, line 2923) `static int origin_component(const char *tok, int axis, int *out)`
  - `expand_transform_origin` (function, line 2949) `static int expand_transform_origin(const char *val, css_decl *dst, int cap)`
  - `expand_gap` (function, line 2981) `static int expand_gap(const char *val, css_decl *dst, int cap)`
  - `ignored` (function, line 3000) `* engine slot and is ignored (documented simplification, like list-style's
 * ignored tokens). An...`
  - `property` (function, line 3035) `* error drops the whole property (fail closed). */
static int expand_clip(const char *val, css_de...`
  - `font_first_name` (function, line 3079) `static int font_first_name(const char *val, char *out, size_t cap)`
  - `writing` (function, line 3112) `* Wide keywords claim BOTH slots without writing (inheritance then flows, as
 * the tail does for...`
  - `shorthand` (function, line 3154) `* generic bucket keeps the rest of the shorthand (same net effect as the
 * font-family longhand ...`
  - `interpret_prop_dispatch` (function, line 3246) `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,
   ...`
  - `wide_claim` (function, line 3856) `static int wide_claim(const char *prop, css_decl *dst, int cap,
                      char (*urlt...`
  - `interpret_prop` (function, line 3896) `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,
            ...`
  - `drop_copy_text` (function, line 3923) `static void drop_copy_text(char *dst, size_t cap, const char *src)`
  - `drop_record` (function, line 3942) `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)`
  - `raw_add` (function, line 3968) `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)`
  - `interpret_decls` (function, line 4081) `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,
               ...`
  - `add_rule` (function, line 4125) `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,
                     siz...`
  - `skip_at_rule` (function, line 4237) `static size_t skip_at_rule(const char *s, size_t i, size_t n)`
  - `block_end` (function, line 4253) `static size_t block_end(const char *s, size_t open, size_t n)`
  - `at_is_media` (function, line 4275) `static int at_is_media(const char *s, size_t i, size_t n)`
  - `at_keyword` (function, line 4286) `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)`
  - `supports_selector_ok` (function, line 4311) `static int supports_selector_ok(void *ctx, const char *sel)`
  - `supports_matches` (function, line 4320) `static int supports_matches(const char *s, size_t a, size_t b)`
  - `layer_register` (function, line 4374) `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,
                     ...`
  - `collect_custom_props_scoped` (function, line 4417) `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,
                ...`
  - `parse_block` (function, line 4492) `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                 ...`
  - `download` (function, line 4619) `* the download (spec/webfont.md b3b). An empty src_url
                     * simply never resolv...`
  - `rem_ident_ch` (function, line 4749) `static int rem_ident_ch(char c)`
  - `rem_num_starts_after` (function, line 4757) `static int rem_num_starts_after(char prev)`
  - `rem_emit_px` (function, line 4767) `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)`
  - `rem_rebase` (function, line 4797) `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)`
  - `sheet_rewind` (function, line 4864) `static void sheet_rewind(css_sheet *sh)`
  - `sheet_root_font_px` (function, line 4907) `static double sheet_root_font_px(const css_sheet *sh)`
  - `strip_comments` (function, line 4915) `static char *strip_comments(const char *text, size_t len, size_t *outlen)`
  - `var` (function, line 4925) `* collected and forty var() declarations -- font sizes, widths, radii, the
     * whole theme -- ...`
  - `css_parse` (function, line 4950) `css_status css_parse(const char *text, size_t len, css_sheet **out)`
  - `css_parse_media` (function, line 4954) `css_status css_parse_media(const char *text, size_t len, const css_media *media,
                ...`
  - `css_parse_scoped` (function, line 4959) `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,
               ...`
  - `css_parse_logged` (function, line 4964) `css_status css_parse_logged(const char *text, size_t len, const css_media *media,
               ...`
  - `css_free` (function, line 5034) `void css_free(css_sheet *s)`
  - `content_attr_of` (function, line 5053) `static const char *content_attr_of(const css_element *el, const char *name)`
  - `apply_decl` (function, line 5062) `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...`
  - `parent` (function, line 5101) `* property from the parent (`inherit`), and an unset non-inherited one
         * stands at its i...`
  - `computed_font_size` (function, line 5480) `static double computed_font_size(const css_style *o, const css_element *el)`
  - `cand_cmp` (function, line 5496) `static int cand_cmp(const void *pa, const void *pb)`
  - `apply_var_source` (function, line 5561) `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
        ...`
  - `apply_rule` (function, line 5588) `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...`
  - `fold_font_relative` (function, line 5626) `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,
                         ...`
  - `css_resolve_el` (function, line 5656) `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         ...`
  - `css_resolve_el_ex` (function, line 5665) `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,
                      ...`
  - `css_resolve_pseudo` (function, line 5671) `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)`
  - `resolve_core` (function, line 5681) `static css_style resolve_core(const css_sheet *sheet, const css_element *el,
                    ...`
  - `css_resolve` (function, line 5890) `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                  ...`
  - `NULL` (function, line 5914) `* Sheet can be NULL (inline style, no @keyframes). */
void css_resolve_anim_keyframes(css_style *...`
  - `css_font_face_count` (function, line 5946) `size_t css_font_face_count(const css_sheet *sheet)`
  - `css_font_face_at` (function, line 5950) `int css_font_face_at(const css_sheet *sheet, size_t i,
                     char *family, size_t ...`
  - `css_parse_inline` (function, line 5960) `css_style css_parse_inline(const char *style, size_t len)`
  - `emit` (function, line 60) `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand...`
  - `css_decl` (function, line 87) `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);`
  - `declaration` (function, line 1199) `* declaration (precedent: expand_filter);`
  - `order` (function, line 1430) `* Lengths in declaration order (dx, dy, optional blur >= 0);`
  - `blur` (function, line 1465) `* consumes ONLY blur(Npx);`
  - `cap` (function, line 1734) `* string past the cap (emit_content): a conforming declaration must not * count as a discard just because an icon...`
  - `empty` (function, line 1768) `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and...`
  - `column` (function, line 1976) `* column (`flex: 1 1 0%`);`
  - `matrix` (function, line 2360) `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands...`
  - `LIST` (function, line 2445) `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose...`
  - `translateX` (function, line 2715) `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc...`
  - `parse_angle_deg` (function, line 2719) `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);`
  - `expand_transform_list` (function, line 2722) `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);`
  - `translateZ` (function, line 2724) `* translateZ(), rotateX(0) and rotateY(0) emit the identity (with the stacking * context Firefox builds);`
  - `caller` (function, line 3234) `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached...`
  - `slots` (function, line 3358) `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return...`
  - `sentinel` (function, line 3470) `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);`
  - `csel_substr` (function, line 4308) `return known && csel_substr(val, "var(", 1);`
  - `page_view` (function, line 5069) `* the generated text reaches page_view (which materialises it as a synthetic * run);`
  - `CSS_INIT_SELS` (macro, line 47) `#define CSS_INIT_SELS`
  - `CSS_INIT_DECLS` (macro, line 48) `#define CSS_INIT_DECLS`
  - `CSS_DECL_SLOTS_MIN` (macro, line 63) `#define CSS_DECL_SLOTS_MIN`
  - `CSS_INIT_RULES` (macro, line 64) `#define CSS_INIT_RULES`
  - `CSS_SELS_PER_GROUP` (macro, line 65) `#define CSS_SELS_PER_GROUP`
  - `CSS_INLINE_DECLS` (macro, line 66) `#define CSS_INLINE_DECLS`
  - `P_META_CUSTOM` (macro, line 79) `#define P_META_CUSTOM`
  - `P_META_VARSRC` (macro, line 80) `#define P_META_VARSRC`
  - `CSS_MAX_RAW` (macro, line 83) `#define CSS_MAX_RAW`
  - `CSS_MAX_FONT_FACES` (macro, line 154) `#define CSS_MAX_FONT_FACES`
  - `AUTO_REJECT` (macro, line 257) `#define AUTO_REJECT`
  - `AUTO_VALUE` (macro, line 258) `#define AUTO_VALUE`
  - `AUTO_RESET` (macro, line 259) `#define AUTO_RESET`
  - `AUTO_RESET_NONE` (macro, line 260) `#define AUTO_RESET_NONE`
  - `CSS_ATTR_MARK` (macro, line 1675) `#define CSS_ATTR_MARK`
  - `CSS_ATTR_SEP` (macro, line 1676) `#define CSS_ATTR_SEP`
  - `CSS_MEDIA_MAX_DEPTH` (macro, line 4408) `#define CSS_MEDIA_MAX_DEPTH`
  - `CSS_VAR_POOL` (macro, line 5557) `#define CSS_VAR_POOL`
- Depends on: `include/css.h`, `include/css_atrule.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_gradient.h`, `include/css_length.h`, `include/css_mq.h`, `include/css_select.h`, `include/css_text.h`, `include/css_values.h`, `include/css_vars.h`, `include/flex_layout.h`, `include/webfont.h`


Next: [KB_src_p2.md](KB_src_p2.md)
