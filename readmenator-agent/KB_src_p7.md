# Subsystem: src (page 7 of 10)
Previous: [KB_src_p6.md](KB_src_p6.md)

## src/page_view.c
- Doc: pv_ptrmap: A small open-addressed map pointer -> int: the per-element verdict on a generated box...
- Layer: presentation
- Language: c
- Symbols:
  - `pv_ptrmap` (struct, line 302)
  - `pv_node_map` (struct, line 356)
  - `pv_cont_info` (struct, line 1284)
  - `pv_item_track` (struct, line 1367)
  - `pv_box_info` (struct, line 1420)
  - `pv_container_reg` (struct, line 1768)
  - `pv_after_pending` (struct, line 1944)
  - `pv_box_reg` (struct, line 1986)
  - `pv_var_node` (struct, line 2377)
  - `pv_style_cache` (struct, line 2400)
  - `pv_flow_reg` (struct, line 3708)
  - `sz_fill` (struct, line 4593)
  - `pv_root_els` (struct, line 4864)
  - `form_rec` (struct, line 4973)
  - `form_table` (struct, line 4979)
  - `pv_flow_reg` (struct, line 5332)
  - `pv_computed` (struct, line 7765)
  - `pv_def_h` (struct, line 2386)
  - `pv_cnt_attr_ctx` (struct, line 5903)
  - `cols` (type_alias, line 1284) `typedef struct pv_cont_info { int id, display, gap, justify, cols;`
  - `mb` (type_alias, line 1420) `typedef struct pv_box_info { int l, r, w, center, mt, mb;`
  - `chain` (type_alias, line 2377) `typedef struct pv_var_node { cvr_chain chain;`
  - `cp1252_to_ucs` (function, line 95) `static unsigned int cp1252_to_ucs(unsigned char c)`
  - `utf8_encode` (function, line 109) `static size_t utf8_encode(unsigned int cp, char *out)`
  - `utf8_sanitized_dup` (function, line 122) `static char *utf8_sanitized_dup(const char *s)`
  - `dup_n` (function, line 156) `static char *dup_n(const char *s, size_t n)`
  - `run_init_common` (function, line 170) `static void run_init_common(pv_run *r)`
  - `pv_ptrmap_slot` (function, line 308) `static size_t pv_ptrmap_slot(const pv_ptrmap *m, const void *k)`
  - `pv_ptrmap_get` (function, line 318) `static int pv_ptrmap_get(const pv_ptrmap *m, const void *k, int *out)`
  - `pv_ptrmap_put` (function, line 326) `static void pv_ptrmap_put(pv_ptrmap *m, const void *k, int v)`
  - `pv_ptrmap_free` (function, line 348) `static void pv_ptrmap_free(pv_ptrmap *m)`
  - `pv_node_map_init` (function, line 364) `static int pv_node_map_init(pv_node_map *m)`
  - `pv_node_map_free` (function, line 374) `static void pv_node_map_free(pv_node_map *m)`
  - `pv_node_map_build` (function, line 426) `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root,
                        ...`
  - `pv_new` (function, line 437) `pv_view *pv_new(void)`
  - `pv_append` (function, line 441) `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    c...`
  - `pv_append_image` (function, line 476) `pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          con...`
  - `pv_append_input` (function, line 506) `pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_...`
  - `pv_append_video` (function, line 546) `pv_status pv_append_video(pv_view *v, int heading, int block_break,
                          con...`
  - `pv_append_svg` (function, line 582) `pv_status pv_append_svg(pv_view *v, int heading, int block_break,
                        const c...`
  - `pv_set_emphasis` (function, line 611) `void pv_set_emphasis(pv_view *v, int bold, int italic)`
  - `pv_set_indent` (function, line 618) `void pv_set_indent(pv_view *v, int indent)`
  - `pv_set_color` (function, line 623) `void pv_set_color(pv_view *v, int fg_rgb)`
  - `pv_set_bgcolor` (function, line 628) `void pv_set_bgcolor(pv_view *v, int bg_rgb)`
  - `pv_set_text_style` (function, line 633) `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,
                ...`
  - `pv_set_grad_text` (function, line 644) `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)`
  - `pv_set_text_ext` (function, line 652) `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)`
  - `ignored` (function, line 695) `* source is ignored (fail-visible: never invisible text from half a
     * pattern). A real text-...`
  - `pv_set_container` (function, line 710) `void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_g...`
  - `pv_set_row_span` (function, line 725) `void pv_set_row_span(pv_view *v, int row_span)`
  - `pv_set_grid_area` (function, line 729) `void pv_set_grid_area(pv_view *v, int row_start, int col_start)`
  - `pv_set_grid` (function, line 736) `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)`
  - `pv_set_grid_rows` (function, line 746) `void pv_set_grid_rows(pv_view *v, int grid_rows)`
  - `pv_set_cont_box` (function, line 750) `void pv_set_cont_box(pv_view *v, int cont_box_id)`
  - `pv_set_flex` (function, line 754) `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                 int...`
  - `pv_set_flex_mauto` (function, line 766) `void pv_set_flex_mauto(pv_view *v, int mauto)`
  - `pv_set_cont_item` (function, line 772) `void pv_set_cont_item(pv_view *v, int cont_item)`
  - `pv_set_float_w` (function, line 777) `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box,
                    ...`
  - `pv_set_float` (function, line 788) `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear,
                int ...`
  - `pv_set_box` (function, line 810) `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                int box_center, int ...`
  - `pv_set_box_pct` (function, line 822) `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,
                    ...`
  - `pv_set_box_maxw` (function, line 833) `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct)`
  - `pv_set_ua_tag` (function, line 840) `void pv_set_ua_tag(pv_view *v, int ua_tag)`
  - `pv_set_node_id` (function, line 846) `void pv_set_node_id(pv_view *v, dom_node_id node_id)`
  - `pv_set_block_id` (function, line 851) `void pv_set_block_id(pv_view *v, int block_id)`
  - `pv_set_own_box` (function, line 856) `void pv_set_own_box(pv_view *v, int box_id)`
  - `pv_set_oof` (function, line 861) `void pv_set_oof(pv_view *v, int oof)`
  - `pv_set_justify_self` (function, line 866) `void pv_set_justify_self(pv_view *v, int justify_self)`
  - `pv_set_block_node` (function, line 871) `void pv_set_block_node(pv_view *v, dom_node_id id)`
  - `pv_set_br_line` (function, line 876) `void pv_set_br_line(pv_view *v, int br_line)`
  - `pv_set_input_checked` (function, line 881) `void pv_set_input_checked(pv_view *v, int checked)`
  - `pv_set_input_placeholder` (function, line 886) `void pv_set_input_placeholder(pv_view *v, int ph_color)`
  - `pv_svg_append_root_attrs` (function, line 891) `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs,
               ...`
  - `pv_placeholder_color` (function, line 920) `int pv_placeholder_color(const css_style *ph)`
  - `pv_set_input_select_opts` (function, line 928) `void pv_set_input_select_opts(pv_view *v, const char *select_opts)`
  - `pv_add_cont_def` (function, line 936) `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)`
  - `pv_cont_count` (function, line 949) `size_t pv_cont_count(const pv_view *v)`
  - `pv_cont_at` (function, line 953) `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)`
  - `pv_add_box_def` (function, line 958) `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)`
  - `pv_free` (function, line 971) `void pv_free(pv_view *v)`
  - `pv_count` (function, line 989) `size_t pv_count(const pv_view *v)`
  - `pv_at` (function, line 993) `const pv_run *pv_at(const pv_view *v, size_t i)`
  - `pv_box_count` (function, line 998) `size_t pv_box_count(const pv_view *v)`
  - `pv_box_at` (function, line 1002) `const pv_box_def *pv_box_at(const pv_view *v, size_t i)`
  - `node_next` (function, line 1010) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)`
  - `is_block_tag` (function, line 1020) `static int is_block_tag(lxb_tag_id_t t)`
  - `is_block_like` (function, line 1045) `static int is_block_like(lxb_tag_id_t t, css_display display)`
  - `resolves` (function, line 1074) `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close
 * button/tooltip w...`
  - `is_block_like_style` (function, line 1084) `static int is_block_like_style(lxb_tag_id_t t, const css_style *cs)`
  - `generates_box` (function, line 1096) `static int generates_box(lxb_tag_id_t t, css_display display)`
  - `generates_box_style` (function, line 1108) `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)`
  - `causes_block_break` (function, line 1115) `static int causes_block_break(lxb_tag_id_t t, css_display display)`
  - `paints` (function, line 1128) `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas
 * vacías"). Comment a...`
  - `ua_tag_of` (function, line 1153) `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)`
  - `heading_level` (function, line 1175) `static int heading_level(lxb_tag_id_t t)`
  - `is_skipped_tag` (function, line 1187) `static int is_skipped_tag(lxb_tag_id_t t)`
  - `node_tag` (function, line 1208) `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)`
  - `in_skipped_subtree` (function, line 1216) `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
              ...`
  - `font_color_attr` (function, line 1253) `static int font_color_attr(lxb_dom_element_t *el)`
  - `item_space_before` (function, line 1381) `static int item_space_before(const lxb_dom_node_t *item)`
  - `item_ordinal` (function, line 1396) `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)`
  - `pv_content_hidden` (function, line 1441) `int pv_content_hidden(int box_hidden, int run_visibility)`
  - `pv_text_ext_reset` (function, line 1447) `void pv_text_ext_reset(pv_text_ext *e)`
  - `pv_text_ext_merge` (function, line 1475) `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)`
  - `css_has_hbox` (function, line 1540) `static int css_has_hbox(const css_style *cs)`
  - `pv_mauto_of` (function, line 1554) `static int pv_mauto_of(const css_style *cs)`
  - `css_hbox_resolve` (function, line 1561) `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)`
  - `css_has_position` (function, line 1614) `static int css_has_position(const css_style *cs)`
  - `border_side_cleared` (function, line 1621) `static int border_side_cleared(int width, int style)`
  - `pv_control_frame_cleared` (function, line 1627) `static int pv_control_frame_cleared(const css_style *cs)`
  - `css_has_boxdeco` (function, line 1635) `static int css_has_boxdeco(const css_style *cs)`
  - `cont_def_reset` (function, line 1782) `static void cont_def_reset(pv_cont_def *d)`
  - `cont_reg_init` (function, line 1802) `static int cont_reg_init(pv_container_reg *reg, size_t cap)`
  - `cont_reg_free` (function, line 1815) `static void cont_reg_free(pv_container_reg *reg)`
  - `container_id` (function, line 1821) `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)`
  - `annotate_flow_run` (function, line 1909) `static void annotate_flow_run(pv_view *v, pv_container_reg *reg, pv_item_track *items,
          ...`
  - `after_pending_emit` (function, line 1958) `static pv_status after_pending_emit(pv_view *v, pv_container_reg *reg, pv_item_track *items,
    ...`
  - `trying` (function, line 1996) `* a real page passes without trying (slashdot's front page saturates it), and past
 * it box_reg_...`
  - `box_reg_free` (function, line 2025) `static void box_reg_free(pv_box_reg *r)`
  - `boxdef_from_style` (function, line 2034) `static void boxdef_from_style(pv_box_def *d, const css_style *cs)`
  - `box_reg_id` (function, line 2285) `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,
           ...`
  - `pseudo_box_reg` (function, line 2314) `static int pseudo_box_reg(pv_box_reg *r, const lxb_dom_node_t *el, int which,
                   ...`
  - `pseudo_generates_box` (function, line 2335) `static int pseudo_generates_box(const css_style *ps)`
  - `pseudo_is_oof` (function, line 2348) `static int pseudo_is_oof(const css_style *ps)`
  - `pseudo_is_block` (function, line 2352) `static int pseudo_is_block(const css_style *ps)`
  - `pseudo_key` (function, line 2358) `static const void *pseudo_key(const lxb_dom_node_t *el, int which)`
  - `pv_ptr_hash` (function, line 2444) `static size_t pv_ptr_hash(const void *p)`
  - `pv_cache_reindex` (function, line 2452) `static void pv_cache_reindex(pv_style_cache *c)`
  - `pv_style_cache_free` (function, line 2488) `static void pv_style_cache_free(pv_style_cache *c)`
  - `pv_style_cache_reserve` (function, line 2509) `static void pv_style_cache_reserve(pv_style_cache *c, size_t n)`
  - `pv_cache_find` (function, line 2534) `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)`
  - `pv_cached_font_px` (function, line 2549) `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)`
  - `pv_cache_put` (function, line 2554) `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,
                     ...`
  - `pv_var_push` (function, line 2604) `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,
                      ...`
  - `pv_cq_push` (function, line 2627) `static const cmq_container *pv_cq_push(pv_style_cache *cache, const lxb_dom_node_t *node,
       ...`
  - `pv_parent_element` (function, line 2666) `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)`
  - `pv_hint_attr` (function, line 2673) `static const char *pv_hint_attr(void *ctx, const char *name, size_t *len)`
  - `pv_cell_table` (function, line 2694) `static lxb_dom_element_t *pv_cell_table(lxb_dom_element_t *el)`
  - `pv_apply_pres_hints` (function, line 2710) `static void pv_apply_pres_hints(lxb_dom_element_t *el, css_style *cs)`
  - `cached_element_style_ref` (function, line 2810) `static const css_style *cached_element_style_ref(lxb_dom_element_t *el, const css_sheet *sheet,
 ...`
  - `cached_element_style` (function, line 2895) `static css_style cached_element_style(lxb_dom_element_t *el, const css_sheet *sheet,
            ...`
  - `inherited_text_color` (function, line 2962) `static int inherited_text_color(const lxb_dom_node_t *node, const css_sheet *sheet,
             ...`
  - `is_inline_container_style` (function, line 2975) `static int is_inline_container_style(const css_style *cs)`
  - `css_width_declared` (function, line 2983) `static int css_width_declared(const css_style *cs)`
  - `parent_is_author_container` (function, line 2990) `static int parent_is_author_container(const lxb_dom_node_t *node, const css_sheet *sheet,
       ...`
  - `box_reg_id_ex` (function, line 2999) `static int box_reg_id_ex(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,
        ...`
  - `cached_pseudo_style` (function, line 3059) `static css_style cached_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet,
             ...`
  - `subtree_is_oof` (function, line 3077) `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,
                     ...`
  - `size` (function, line 3097) `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */
static void app...`
  - `css_replaced_h_fixed` (function, line 3106) `static int css_replaced_h_fixed(lxb_dom_element_t *el, const css_sheet *sheet,
                  ...`
  - `builder` (function, line 3124) `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box
 * (the ...`
  - `css_to_fx_justify` (function, line 3153) `static int css_to_fx_justify(css_justify j)`
  - `is_bold_tag` (function, line 3172) `static int is_bold_tag(lxb_tag_id_t t)`
  - `is_italic_tag` (function, line 3177) `static int is_italic_tag(lxb_tag_id_t t)`
  - `is_inline_level_style` (function, line 3214) `static int is_inline_level_style(lxb_tag_id_t t, const css_style *cs)`
  - `in_mixed_line` (function, line 3222) `static int in_mixed_line(const lxb_dom_node_t *p, const css_sheet *sheet,
                       ...`
  - `is_float_container_style` (function, line 3243) `static int is_float_container_style(const css_style *cs)`
  - `row_lone_float_side` (function, line 3251) `static int row_lone_float_side(const lxb_dom_node_t *p, const css_sheet *sheet,
                 ...`
  - `children_all_inline_block` (function, line 3270) `static int children_all_inline_block(const lxb_dom_node_t *p, const css_sheet *sheet,
           ...`
  - `it` (function, line 3298) `* without it (minified markup) keeps the row gapless -- the mixed case is a known limit. */
stati...`
  - `col_has_free_space` (function, line 3323) `static int col_has_free_space(const css_style *cs)`
  - `flex_column_flows_as_block` (function, line 3337) `static int flex_column_flows_as_block(const lxb_dom_node_t *el, const css_style *cs,
            ...`
  - `flex_column_flows_as_block_uncached` (function, line 3346) `static int flex_column_flows_as_block_uncached(const lxb_dom_node_t *el, const css_style *cs,
   ...`
  - `fold_column_gap` (function, line 3414) `static void fold_column_gap(const lxb_dom_node_t *el, css_style *cs,
                            ...`
  - `column_gap_candidate` (function, line 3439) `static int column_gap_candidate(const lxb_dom_node_t *el, const css_sheet *sheet,
               ...`
  - `is_layout_container` (function, line 3449) `static int is_layout_container(const lxb_dom_node_t *el, const css_style *cs,
                   ...`
  - `css_has_hmargin` (function, line 3475) `static int css_has_hmargin(const css_style *cs)`
  - `item_sizes_itself` (function, line 3504) `static int item_sizes_itself(const lxb_dom_node_t *el, const css_style *cs,
                     ...`
  - `li_is_list_item` (function, line 3520) `static int li_is_list_item(const lxb_dom_node_t *li, const css_sheet *sheet,
                    ...`
  - `pv_element_has_before` (function, line 3597) `static int pv_element_has_before(lxb_dom_node_t *n, const css_sheet *sheet,
                     ...`
  - `subtree_has_own_text` (function, line 3629) `static int subtree_has_own_text(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
            ...`
  - `is_plain_wrapper` (function, line 3651) `static int is_plain_wrapper(const lxb_dom_node_t *c, const css_style *cs)`
  - `element_is_content_leaf_d` (function, line 3663) `static int element_is_content_leaf_d(const lxb_dom_node_t *n, const css_sheet *sheet,
           ...`
  - `media_has_source` (function, line 3689) `static int media_has_source(const lxb_dom_node_t *n)`
  - `element_is_content_leaf` (function, line 3703) `static int element_is_content_leaf(const lxb_dom_node_t *n, const css_sheet *sheet,
             ...`
  - `resolve_context` (function, line 3720) `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                ...`
  - `opens` (function, line 4058) `* painter applies it when the box opens (band/shared context) — seeding
             * it onto ru...`
  - `css_inline_boxdeco` (function, line 4111) `css_inline_boxdeco(cs) &&
                           !is_layout_item(p, sheet, style_cache))`
  - `margins` (function, line 4150) `* margins (boxdef_from_style) and the painter applies them when
                         * it ope...`
  - `container` (function, line 4277) `* membership in this container (and none in any container further out,
                 * since i...`
  - `walk` (function, line 4398) `* far on this walk (they are all inside this element). */

                        /* The innermo...`
  - `float` (function, line 4539) `* genuinely nested float (oid != id) takes the deferred-column path. */
    if (cont->float_oid =...`
  - `sz_count` (function, line 4585) `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)`
  - `sz_write` (function, line 4599) `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)`
  - `serialize_subtree` (function, line 4607) `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)`
  - `collapse_ws` (function, line 4626) `static char *collapse_ws(const char *s, size_t n)`
  - `pv_frame_marked` (function, line 4656) `static int pv_frame_marked(const lxb_dom_node_t *n)`
  - `parse_dim` (function, line 4665) `static int parse_dim(const lxb_char_t *s, size_t len)`
  - `present` (function, line 4682) `* when no width descriptors are present (density-only or bare URLs). */
static void srcset_best_u...`
  - `srcset_slot_width` (function, line 4777) `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,
                              ...`
  - `dimensions` (function, line 4823) `* viewport dimensions (data: inline detection, <picture> <source> scanning). */
static void srcse...`
  - `find_body` (function, line 4855) `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)`
  - `find_root_els` (function, line 4868) `static pv_root_els find_root_els(lxb_dom_node_t *root)`
  - `attributes` (function, line 4882) `* carries those attributes (spec/css.md, "Root matcher"). */
static int root_els_match(void *ctx,...`
  - `string` (function, line 4893) `* Returns a heap string (caller frees) or NULL when neither carries a class —
 * NULL simply mean...`
  - `acquire_page_sheet` (function, line 4932) `static shc_sheet *acquire_page_sheet(lxb_dom_node_t *root, const char *extern_css,
              ...`
  - `forms_free` (function, line 4984) `static void forms_free(form_table *ft)`
  - `ascii_ieq` (function, line 4991) `static int ascii_ieq(const char *s, const char *lit)`
  - `attr_dup` (function, line 5003) `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)`
  - `forms_add` (function, line 5012) `static int forms_add(form_table *ft, const lxb_dom_node_t *node)`
  - `form_for` (function, line 5032) `static int form_for(const form_table *ft, const lxb_dom_node_t *n,
                    const lxb_...`
  - `under_unrendered` (function, line 5048) `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)`
  - `collect_text` (function, line 5061) `static char *collect_text(const lxb_dom_node_t *el)`
  - `classify_input` (function, line 5085) `static pv_input_type classify_input(const char *type)`
  - `li_ordinal` (function, line 5256) `static int li_ordinal(const lxb_dom_node_t *li)`
  - `roman_marker` (function, line 5282) `static void roman_marker(int n, int upper, char *out, size_t cap)`
  - `list_marker` (function, line 5307) `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,
                  ...`
  - `node_table_role` (function, line 5352) `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)`
  - `nearest_table` (function, line 5370) `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
 ...`
  - `parent_is_table_internal` (function, line 5409) `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)`
  - `cell_has_nested_table` (function, line 5441) `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)`
  - `next_skip` (function, line 5455) `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)`
  - `cell_span_attr` (function, line 5465) `static int cell_span_attr(const lxb_dom_node_t *cell, const char *name, size_t name_len,
        ...`
  - `table_next_row` (function, line 5478) `static const lxb_dom_node_t *table_next_row(const lxb_dom_node_t *table,
                        ...`
  - `cell_is_rich` (function, line 5539) `static int cell_is_rich(const lxb_dom_node_t *cell)`
  - `cell_kind` (function, line 5566) `static unsigned cell_kind(pv_flow_reg *fr, const lxb_dom_node_t *cell)`
  - `cell_is_grid_item` (function, line 5575) `static int cell_is_grid_item(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,
            ...`
  - `in_collected_cell` (function, line 5585) `static int in_collected_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
               ...`
  - `table_columns` (function, line 5606) `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)`
  - `table_columns_scan` (function, line 5615) `static int table_columns_scan(const lxb_dom_node_t *table, const pv_flow_reg *fr)`
  - `in_hidden_subtree` (function, line 5689) `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
               ...`
  - `in_boilerplate_subtree` (function, line 5716) `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)`
  - `in_closed_details_subtree` (function, line 5731) `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)`
  - `pv_build` (function, line 5751) `pv_status pv_build(const hp_document *doc, pv_view **out)`
  - `pv_build_ex` (function, line 5755) `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)`
  - `pv_build_full` (function, line 5759) `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                     ...`
  - `annotate_replaced_run` (function, line 5781) `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,
                            ...`
  - `pv_root_insets` (function, line 5856) `void pv_root_insets(const css_style *body, int out[4])`
  - `collect_page_css` (function, line 5866) `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,
                     ...`
  - `pv_cnt_attr` (function, line 5908) `static const char *pv_cnt_attr(void *ctx, const char *name)`
  - `pv_cnt_resolve_field` (function, line 5921) `static void pv_cnt_resolve_field(const cnt_state *st, lxb_dom_element_t *el, char *field)`
  - `pv_cnt_enter` (function, line 5932) `static int pv_cnt_enter(cnt_state *st, lxb_dom_node_t *n, int depth, const css_sheet *sheet,
    ...`
  - `pv_cnt_exit` (function, line 5956) `static void pv_cnt_exit(cnt_state *st, lxb_dom_node_t *n, int depth, const css_sheet *sheet,
    ...`
  - `pv_counters_pass` (function, line 5968) `static void pv_counters_pass(lxb_dom_node_t *root, const css_sheet *sheet, pv_style_cache *cache)`
  - `pv_build_styled` (function, line 5992) `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                   ...`
  - `pv_build_cached` (function, line 5999) `pv_status pv_build_cached(const hp_document *doc, int js_enabled, int reader,
                   ...`
  - `pv_build_cq` (function, line 6006) `pv_status pv_build_cq(const hp_document *doc, int js_enabled, int reader,
                      i...`
  - `pv_build_live` (function, line 6013) `pv_status pv_build_live(const hp_document *doc, int js_enabled, int reader,
                     ...`
  - `px` (function, line 6611) `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */
                if (iw <...`
  - `engine` (function, line 7568) `* layout engine (contiguous item gather) drops every cell onto its own row and
         * a 2-col...`
  - `pv_css_drops` (function, line 7736) `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,
                       const cha...`
  - `pv_computed_new` (function, line 7770) `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css,
  ...`
  - `pv_computed_new_cached` (function, line 7775) `pv_computed *pv_computed_new_cached(const hp_document *doc, int prefers_dark,
                   ...`
  - `pv_computed_get` (function, line 7789) `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st,
                    do...`
  - `pv_computed_free` (function, line 7811) `void pv_computed_free(pv_computed *pc)`
  - `positions` (function, line 145) `* positions (cp == 0) keep the legacy '?' fallback. */ unsigned int cp = cp1252_to_ucs(c);`
  - `content` (function, line 1213) `* a <noscript> ancestor also suppresses content (the script would run, so the * fallback is hidden);`
  - `address` (function, line 1274) `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <=...`
  - `child` (function, line 1282) `* child (NULL = anonymous item: text directly inside the container);`
  - `id` (function, line 1306) `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);`
  - `them` (function, line 1371) `* them (PV_BR_ATOM_SPACE);`
  - `text_node_is_blank` (function, line 1380) `static int text_node_is_blank(const lxb_dom_node_t *c);`
  - `here` (function, line 2136) `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3...`
  - `glyphs` (function, line 2187) `* glyphs (the runs carry it as their fill source);`
  - `col_free_share` (function, line 2956) `static int col_free_share(const lxb_dom_node_t *el, const css_style *cs, const css_sheet *sheet, pv_style_cache...`
  - `none` (function, line 3004) `* inherited when it declares none (every hamburger bar and divider drawn as * a coloured empty box). A box cannot...`
  - `table_cell_pos` (function, line 3715) `static int table_cell_pos(struct pv_flow_reg *fr, const lxb_dom_node_t *table, const lxb_dom_node_t *cell, int *row...`
  - `outermost` (function, line 4001) `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);`
  - `url` (function, line 6038) `* fetches and drops url()/@-rules). A NULL sheet is treated as empty by the css * module, so OOM here degrades to...`
  - `inside` (function, line 6123) `* page inside (the top one collapses with the first child's margin), so a * margin-only body stays box-less. */...`
  - `control` (function, line 6433) `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);`
  - `band` (function, line 6677) `* run: without its float annotation it cut the band (the icon row of a * `float:right` social list became one float...`
  - `height` (function, line 6704) `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
  - `block_id` (function, line 6862) `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it...`
  - `URL` (function, line 7003) `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
  - `block` (function, line 7280) `* block (Gecko): it never resolves as its own block here. */ int opens_line = block != n && (pending_break || block...`
  - `flow` (function, line 7459) `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through...`
  - `line` (function, line 7577) `* to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);`
  - `_POSIX_C_SOURCE` (macro, line 10) `#define _POSIX_C_SOURCE`
  - `PV_MAX_DIM` (macro, line 57) `#define PV_MAX_DIM`
  - `PV_FONT_REL_MIN` (macro, line 62) `#define PV_FONT_REL_MIN`
  - `PV_FONT_REL_MAX` (macro, line 63) `#define PV_FONT_REL_MAX`
  - `PV_FONT_CHAIN_MAX` (macro, line 69) `#define PV_FONT_CHAIN_MAX`
  - `PV_FONT_PCT_MIN` (macro, line 70) `#define PV_FONT_PCT_MIN`
  - `PV_FONT_PCT_MAX` (macro, line 71) `#define PV_FONT_PCT_MAX`
  - `PV_NODE_MAP_INIT_CAP` (macro, line 354) `#define PV_NODE_MAP_INIT_CAP`
  - `PV_COLOR_TOKEN_MAX` (macro, line 1231) `#define PV_COLOR_TOKEN_MAX`
  - `PV_MAX_GRID_COLS` (macro, line 1263) `#define PV_MAX_GRID_COLS`
  - `PV_MAX_BOXES` (macro, line 1271) `#define PV_MAX_BOXES`
  - `PV_ATOM_SPACE_MAX` (macro, line 1376) `#define PV_ATOM_SPACE_MAX`
  - `PV_STYLE_RETIRE_MAX` (macro, line 2398) `#define PV_STYLE_RETIRE_MAX`
  - `PV_CQ_NODES_MAX` (macro, line 2442) `#define PV_CQ_NODES_MAX`
  - `PV_STYLE_RESERVE_MAX` (macro, line 2464) `#define PV_STYLE_RESERVE_MAX`
  - `PV_MAX_INLINE_ROW_ITEMS` (macro, line 3210) `#define PV_MAX_INLINE_ROW_ITEMS`
  - `PV_TEXTLESS_DEPTH_MAX` (macro, line 3612) `#define PV_TEXTLESS_DEPTH_MAX`
  - `PV_FRAME_DEF_W` (macro, line 4652) `#define PV_FRAME_DEF_W`
  - `PV_FRAME_DEF_H` (macro, line 4653) `#define PV_FRAME_DEF_H`
  - `PV_FRAME_URL_MAX` (macro, line 4654) `#define PV_FRAME_URL_MAX`
  - `PV_CELL_NESTED` (macro, line 5562) `#define PV_CELL_NESTED`
  - `PV_CELL_RICH` (macro, line 5563) `#define PV_CELL_RICH`
  - `PV_MAX_STYLE_BYTES` (macro, line 5642) `#define PV_MAX_STYLE_BYTES`
- Depends on: `include/box_style.h`, `include/box_tree.h`, `include/css.h`, `include/css_chain.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_vars.h`, `include/dom.h`, `include/flex_layout.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/page_view.h`, `include/pres_hints.h`, `include/sheet_cache.h`, `include/svg_render.h`, `include/util.h`

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

## src/pq_seal.c
- Doc: derive_key: pqs_status pqs_import(const uint8_t *der, size_t len, pqs_keys **out) { if (der ==...
- Layer: utility
- Language: c
- Symbols:
  - `pqs_keys` (struct, line 19)
  - `pqs_buf_free` (function, line 23) `void pqs_buf_free(uint8_t *buf, size_t len)`
  - `pqs_free` (function, line 29) `void pqs_free(pqs_keys *k)`
  - `keys_wrap` (function, line 35) `static pqs_keys *keys_wrap(EVP_PKEY *pkey)`
  - `pqs_generate` (function, line 42) `pqs_status pqs_generate(pqs_keys **out)`
  - `pqs_export` (function, line 55) `pqs_status pqs_export(const pqs_keys *k, uint8_t **der, size_t *len)`
  - `pqs_import` (function, line 68) `pqs_status pqs_import(const uint8_t *der, size_t len, pqs_keys **out)`
  - `derive_key` (function, line 81) `static int derive_key(const uint8_t ss[PQS_SS_LEN], const uint8_t wrap[LS_KEY_LEN],
             ...`
  - `pqs_seal` (function, line 106) `pqs_status pqs_seal(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],
                    const ...`
  - `pqs_open` (function, line 147) `pqs_status pqs_open(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],
                    const ...`
  - `PQS_SS_LEN` (macro, line 17) `#define PQS_SS_LEN`
- Depends on: `include/pq_seal.h`

## src/prefetch.c
- Doc: ci_starts: static int is_ws(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' ||...
- Layer: utility
- Language: c
- Symbols:
  - `attr_span` (struct, line 65)
  - `is_ws` (function, line 26) `static int is_ws(char c)`
  - `is_name_char` (function, line 30) `static int is_name_char(char c)`
  - `lower` (function, line 35) `static int lower(int c)`
  - `ci_starts` (function, line 40) `static int ci_starts(const char *p, const char *end, const char *kw)`
  - `ci_find` (function, line 49) `static const char *ci_find(const char *p, const char *end, const char *kw)`
  - `ci_eq_span` (function, line 58) `static int ci_eq_span(const char *s, size_t n, const char *kw)`
  - `emit` (function, line 120) `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)`
  - `pf_scan` (function, line 133) `int pf_scan(const char *html, size_t len, pf_list *out)`
  - `pf_list_free` (function, line 196) `void pf_list_free(pf_list *l)`
  - `js_ident_ch` (function, line 207) `static int js_ident_ch(char c)`
  - `js_skip_ws` (function, line 212) `static size_t js_skip_ws(const char *s, size_t i, size_t n)`
  - `js_skip_string` (function, line 219) `static size_t js_skip_string(const char *s, size_t i, size_t n)`
  - `js_take_spec` (function, line 226) `static void js_take_spec(const char *s, size_t i, size_t n,
                         char (*out)[...`
  - `pf_scan_imports` (function, line 241) `size_t pf_scan_imports(const char *js, size_t len, char (*out)[PF_SPEC_MAX], size_t cap)`
  - `pf_pool_add` (function, line 288) `int pf_pool_add(pf_pool *p, const char *url)`
  - `pf_is_js` (function, line 311) `static int pf_is_js(const char *url, const char *ctype)`
  - `pf_url_cb` (function, line 319) `static int pf_url_cb(void *ctx, const char *base, const char *ref, char *out, size_t outsz)`
  - `pf_url_shaped` (function, line 324) `static int pf_url_shaped(const char *sp)`
  - `pf_follow_imports` (function, line 333) `static void pf_follow_imports(pf_pool *p, const char *base, const char *body, size_t len)`
  - `pf_worker` (function, line 349) `static void *pf_worker(void *arg)`
  - `pf_pool_start` (function, line 387) `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                  pf_fetch_f...`
  - `pool_start` (function, line 394) `static int pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                      pf...`
  - `pf_pool_take` (function, line 444) `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,
                 char **body,...`
  - `pf_find_importmap` (function, line 483) `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n)`
  - `pf_pool_start_page` (function, line 504) `int pf_pool_start_page(pf_pool *p, const char *html, size_t len, const char *page_url,
          ...`
  - `pf_pool_finish` (function, line 540) `void pf_pool_finish(pf_pool *p)`
  - `pf_pooled_fetch` (function, line 561) `int pf_pooled_fetch(void *vctx, const char *method, const char *url,
                    const ch...`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
  - `PF_MAX_URL` (macro, line 24) `#define PF_MAX_URL`
- Depends on: `include/import_map.h`, `include/prefetch.h`, `include/url.h`


Next: [KB_src_p8.md](KB_src_p8.md)
