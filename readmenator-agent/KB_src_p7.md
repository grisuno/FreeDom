# Subsystem: src (page 7 of 10)
Previous: [KB_src_p6.md](KB_src_p6.md)

## src/page_view.c
- Doc: pv_ptrmap: A small open-addressed map pointer -> int: the per-element verdict on a generated box...
- Layer: presentation
- Language: c
- Symbols:
  - `pv_ptrmap` (struct, line 298)
  - `pv_node_map` (struct, line 352)
  - `pv_cont_info` (struct, line 1273)
  - `pv_item_track` (struct, line 1356)
  - `pv_box_info` (struct, line 1375)
  - `pv_container_reg` (struct, line 1723)
  - `pv_after_pending` (struct, line 1876)
  - `pv_box_reg` (struct, line 1918)
  - `pv_var_node` (struct, line 2306)
  - `pv_style_cache` (struct, line 2326)
  - `pv_flow_reg` (struct, line 3413)
  - `sz_fill` (struct, line 4219)
  - `pv_root_els` (struct, line 4490)
  - `form_rec` (struct, line 4556)
  - `form_table` (struct, line 4562)
  - `pv_flow_reg` (struct, line 4917)
  - `pv_computed` (struct, line 7246)
  - `pv_def_h` (struct, line 2315)
  - `pv_cnt_attr_ctx` (struct, line 5416)
  - `cols` (type_alias, line 1273) `typedef struct pv_cont_info { int id, display, gap, justify, cols;`
  - `mb` (type_alias, line 1375) `typedef struct pv_box_info { int l, r, w, center, mt, mb;`
  - `chain` (type_alias, line 2306) `typedef struct pv_var_node { cvr_chain chain;`
  - `cp1252_to_ucs` (function, line 91) `static unsigned int cp1252_to_ucs(unsigned char c)`
  - `utf8_encode` (function, line 105) `static size_t utf8_encode(unsigned int cp, char *out)`
  - `utf8_sanitized_dup` (function, line 118) `static char *utf8_sanitized_dup(const char *s)`
  - `dup_n` (function, line 152) `static char *dup_n(const char *s, size_t n)`
  - `run_init_common` (function, line 166) `static void run_init_common(pv_run *r)`
  - `pv_ptrmap_slot` (function, line 304) `static size_t pv_ptrmap_slot(const pv_ptrmap *m, const void *k)`
  - `pv_ptrmap_get` (function, line 314) `static int pv_ptrmap_get(const pv_ptrmap *m, const void *k, int *out)`
  - `pv_ptrmap_put` (function, line 322) `static void pv_ptrmap_put(pv_ptrmap *m, const void *k, int v)`
  - `pv_ptrmap_free` (function, line 344) `static void pv_ptrmap_free(pv_ptrmap *m)`
  - `pv_node_map_init` (function, line 359) `static int pv_node_map_init(pv_node_map *m)`
  - `pv_node_map_free` (function, line 368) `static void pv_node_map_free(pv_node_map *m)`
  - `pv_node_map_build` (function, line 410) `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root)`
  - `pv_new` (function, line 419) `pv_view *pv_new(void)`
  - `pv_append` (function, line 423) `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    c...`
  - `pv_append_image` (function, line 458) `pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          con...`
  - `pv_append_input` (function, line 488) `pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_...`
  - `pv_append_video` (function, line 528) `pv_status pv_append_video(pv_view *v, int heading, int block_break,
                          con...`
  - `pv_append_svg` (function, line 564) `pv_status pv_append_svg(pv_view *v, int heading, int block_break,
                        const c...`
  - `pv_set_emphasis` (function, line 593) `void pv_set_emphasis(pv_view *v, int bold, int italic)`
  - `pv_set_indent` (function, line 600) `void pv_set_indent(pv_view *v, int indent)`
  - `pv_set_color` (function, line 605) `void pv_set_color(pv_view *v, int fg_rgb)`
  - `pv_set_bgcolor` (function, line 610) `void pv_set_bgcolor(pv_view *v, int bg_rgb)`
  - `pv_set_text_style` (function, line 615) `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,
                ...`
  - `pv_set_grad_text` (function, line 626) `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)`
  - `pv_set_text_ext` (function, line 634) `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)`
  - `ignored` (function, line 677) `* source is ignored (fail-visible: never invisible text from half a
     * pattern). A real text-...`
  - `pv_set_container` (function, line 692) `void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_g...`
  - `pv_set_row_span` (function, line 707) `void pv_set_row_span(pv_view *v, int row_span)`
  - `pv_set_grid_area` (function, line 711) `void pv_set_grid_area(pv_view *v, int row_start, int col_start)`
  - `pv_set_grid` (function, line 718) `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)`
  - `pv_set_grid_rows` (function, line 728) `void pv_set_grid_rows(pv_view *v, int grid_rows)`
  - `pv_set_cont_box` (function, line 732) `void pv_set_cont_box(pv_view *v, int cont_box_id)`
  - `pv_set_flex` (function, line 736) `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                 int...`
  - `pv_set_flex_mauto` (function, line 748) `void pv_set_flex_mauto(pv_view *v, int mauto)`
  - `pv_set_cont_item` (function, line 754) `void pv_set_cont_item(pv_view *v, int cont_item)`
  - `pv_set_float_w` (function, line 759) `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box,
                    ...`
  - `pv_set_float` (function, line 770) `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear,
                int ...`
  - `pv_set_box` (function, line 792) `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                int box_center, int ...`
  - `pv_set_box_pct` (function, line 804) `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,
                    ...`
  - `pv_set_box_maxw` (function, line 815) `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct)`
  - `pv_set_ua_tag` (function, line 822) `void pv_set_ua_tag(pv_view *v, int ua_tag)`
  - `pv_set_node_id` (function, line 828) `void pv_set_node_id(pv_view *v, dom_node_id node_id)`
  - `pv_set_block_id` (function, line 833) `void pv_set_block_id(pv_view *v, int block_id)`
  - `pv_set_own_box` (function, line 838) `void pv_set_own_box(pv_view *v, int box_id)`
  - `pv_set_oof` (function, line 843) `void pv_set_oof(pv_view *v, int oof)`
  - `pv_set_justify_self` (function, line 848) `void pv_set_justify_self(pv_view *v, int justify_self)`
  - `pv_set_block_node` (function, line 853) `void pv_set_block_node(pv_view *v, dom_node_id id)`
  - `pv_set_br_line` (function, line 858) `void pv_set_br_line(pv_view *v, int br_line)`
  - `pv_set_input_checked` (function, line 863) `void pv_set_input_checked(pv_view *v, int checked)`
  - `pv_set_input_placeholder` (function, line 868) `void pv_set_input_placeholder(pv_view *v, int ph_color)`
  - `pv_svg_append_root_attrs` (function, line 873) `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs,
               ...`
  - `pv_placeholder_color` (function, line 902) `int pv_placeholder_color(const css_style *ph)`
  - `pv_set_input_select_opts` (function, line 910) `void pv_set_input_select_opts(pv_view *v, const char *select_opts)`
  - `pv_add_cont_def` (function, line 918) `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)`
  - `pv_cont_count` (function, line 931) `size_t pv_cont_count(const pv_view *v)`
  - `pv_cont_at` (function, line 935) `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)`
  - `pv_add_box_def` (function, line 940) `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)`
  - `pv_free` (function, line 953) `void pv_free(pv_view *v)`
  - `pv_count` (function, line 971) `size_t pv_count(const pv_view *v)`
  - `pv_at` (function, line 975) `const pv_run *pv_at(const pv_view *v, size_t i)`
  - `pv_box_count` (function, line 980) `size_t pv_box_count(const pv_view *v)`
  - `pv_box_at` (function, line 984) `const pv_box_def *pv_box_at(const pv_view *v, size_t i)`
  - `node_next` (function, line 992) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)`
  - `is_block_tag` (function, line 1002) `static int is_block_tag(lxb_tag_id_t t)`
  - `is_block_like` (function, line 1027) `static int is_block_like(lxb_tag_id_t t, css_display display)`
  - `resolves` (function, line 1056) `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close
 * button/tooltip w...`
  - `is_block_like_style` (function, line 1066) `static int is_block_like_style(lxb_tag_id_t t, const css_style *cs)`
  - `generates_box` (function, line 1078) `static int generates_box(lxb_tag_id_t t, css_display display)`
  - `generates_box_style` (function, line 1090) `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)`
  - `causes_block_break` (function, line 1097) `static int causes_block_break(lxb_tag_id_t t, css_display display)`
  - `paints` (function, line 1110) `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas
 * vacías"). Comment a...`
  - `ua_tag_of` (function, line 1135) `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)`
  - `heading_level` (function, line 1157) `static int heading_level(lxb_tag_id_t t)`
  - `is_skipped_tag` (function, line 1169) `static int is_skipped_tag(lxb_tag_id_t t)`
  - `node_tag` (function, line 1190) `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)`
  - `in_skipped_subtree` (function, line 1198) `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
              ...`
  - `font_color_attr` (function, line 1235) `static int font_color_attr(lxb_dom_element_t *el)`
  - `bgcolor_attr` (function, line 1241) `static int bgcolor_attr(lxb_dom_element_t *el)`
  - `item_ordinal` (function, line 1363) `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)`
  - `pv_content_hidden` (function, line 1396) `int pv_content_hidden(int box_hidden, int run_visibility)`
  - `pv_text_ext_reset` (function, line 1402) `void pv_text_ext_reset(pv_text_ext *e)`
  - `pv_text_ext_merge` (function, line 1430) `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)`
  - `css_has_hbox` (function, line 1495) `static int css_has_hbox(const css_style *cs)`
  - `pv_mauto_of` (function, line 1509) `static int pv_mauto_of(const css_style *cs)`
  - `css_hbox_resolve` (function, line 1516) `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)`
  - `css_has_position` (function, line 1569) `static int css_has_position(const css_style *cs)`
  - `border_side_cleared` (function, line 1576) `static int border_side_cleared(int width, int style)`
  - `pv_control_frame_cleared` (function, line 1582) `static int pv_control_frame_cleared(const css_style *cs)`
  - `css_has_boxdeco` (function, line 1590) `static int css_has_boxdeco(const css_style *cs)`
  - `cont_def_reset` (function, line 1734) `static void cont_def_reset(pv_cont_def *d)`
  - `container_id` (function, line 1753) `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)`
  - `annotate_flow_run` (function, line 1841) `static void annotate_flow_run(pv_view *v, pv_container_reg *reg, pv_item_track *items,
          ...`
  - `after_pending_emit` (function, line 1890) `static pv_status after_pending_emit(pv_view *v, pv_container_reg *reg, pv_item_track *items,
    ...`
  - `trying` (function, line 1928) `* a real page passes without trying (slashdot's front page saturates it), and past
 * it box_reg_...`
  - `box_reg_free` (function, line 1957) `static void box_reg_free(pv_box_reg *r)`
  - `boxdef_from_style` (function, line 1966) `static void boxdef_from_style(pv_box_def *d, const css_style *cs)`
  - `box_reg_id` (function, line 2214) `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,
           ...`
  - `pseudo_box_reg` (function, line 2243) `static int pseudo_box_reg(pv_box_reg *r, const lxb_dom_node_t *el, int which,
                   ...`
  - `pseudo_generates_box` (function, line 2264) `static int pseudo_generates_box(const css_style *ps)`
  - `pseudo_is_oof` (function, line 2277) `static int pseudo_is_oof(const css_style *ps)`
  - `pseudo_is_block` (function, line 2281) `static int pseudo_is_block(const css_style *ps)`
  - `pseudo_key` (function, line 2287) `static const void *pseudo_key(const lxb_dom_node_t *el, int which)`
  - `pv_ptr_hash` (function, line 2358) `static size_t pv_ptr_hash(const void *p)`
  - `pv_cache_reindex` (function, line 2366) `static void pv_cache_reindex(pv_style_cache *c)`
  - `pv_style_cache_free` (function, line 2402) `static void pv_style_cache_free(pv_style_cache *c)`
  - `pv_style_cache_reserve` (function, line 2421) `static void pv_style_cache_reserve(pv_style_cache *c, size_t n)`
  - `pv_cache_find` (function, line 2446) `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)`
  - `pv_cached_font_px` (function, line 2461) `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)`
  - `pv_cache_put` (function, line 2466) `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,
                     ...`
  - `pv_var_push` (function, line 2516) `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,
                      ...`
  - `pv_parent_element` (function, line 2537) `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)`
  - `cached_element_style_ref` (function, line 2621) `static const css_style *cached_element_style_ref(lxb_dom_element_t *el, const css_sheet *sheet,
 ...`
  - `cached_element_style` (function, line 2704) `static css_style cached_element_style(lxb_dom_element_t *el, const css_sheet *sheet,
            ...`
  - `inherited_text_color` (function, line 2771) `static int inherited_text_color(const lxb_dom_node_t *node, const css_sheet *sheet,
             ...`
  - `box_reg_id_ex` (function, line 2782) `static int box_reg_id_ex(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,
        ...`
  - `cached_pseudo_style` (function, line 2820) `static css_style cached_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet,
             ...`
  - `subtree_is_oof` (function, line 2838) `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,
                     ...`
  - `size` (function, line 2858) `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */
static void app...`
  - `css_replaced_h_fixed` (function, line 2867) `static int css_replaced_h_fixed(lxb_dom_element_t *el, const css_sheet *sheet,
                  ...`
  - `builder` (function, line 2885) `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box
 * (the ...`
  - `css_to_fx_justify` (function, line 2914) `static int css_to_fx_justify(css_justify j)`
  - `is_bold_tag` (function, line 2933) `static int is_bold_tag(lxb_tag_id_t t)`
  - `is_italic_tag` (function, line 2938) `static int is_italic_tag(lxb_tag_id_t t)`
  - `is_inline_level_style` (function, line 2975) `static int is_inline_level_style(lxb_tag_id_t t, const css_style *cs)`
  - `in_mixed_line` (function, line 2983) `static int in_mixed_line(const lxb_dom_node_t *p, const css_sheet *sheet,
                       ...`
  - `children_all_inline_block` (function, line 2999) `static int children_all_inline_block(const lxb_dom_node_t *p, const css_sheet *sheet,
           ...`
  - `col_has_free_space` (function, line 3024) `static int col_has_free_space(const css_style *cs)`
  - `flex_column_flows_as_block` (function, line 3038) `static int flex_column_flows_as_block(const lxb_dom_node_t *el, const css_style *cs,
            ...`
  - `flex_column_flows_as_block_uncached` (function, line 3047) `static int flex_column_flows_as_block_uncached(const lxb_dom_node_t *el, const css_style *cs,
   ...`
  - `fold_column_gap` (function, line 3115) `static void fold_column_gap(const lxb_dom_node_t *el, css_style *cs,
                            ...`
  - `column_gap_candidate` (function, line 3140) `static int column_gap_candidate(const lxb_dom_node_t *el, const css_sheet *sheet,
               ...`
  - `is_layout_container` (function, line 3150) `static int is_layout_container(const lxb_dom_node_t *el, const css_style *cs,
                   ...`
  - `css_has_hmargin` (function, line 3176) `static int css_has_hmargin(const css_style *cs)`
  - `item_sizes_itself` (function, line 3205) `static int item_sizes_itself(const lxb_dom_node_t *el, const css_style *cs,
                     ...`
  - `li_is_list_item` (function, line 3221) `static int li_is_list_item(const lxb_dom_node_t *li, const css_sheet *sheet,
                    ...`
  - `pv_element_has_before` (function, line 3298) `static int pv_element_has_before(lxb_dom_node_t *n, const css_sheet *sheet,
                     ...`
  - `subtree_has_own_text` (function, line 3330) `static int subtree_has_own_text(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
            ...`
  - `is_plain_wrapper` (function, line 3352) `static int is_plain_wrapper(const lxb_dom_node_t *c, const css_style *cs)`
  - `element_is_content_leaf_d` (function, line 3364) `static int element_is_content_leaf_d(const lxb_dom_node_t *n, const css_sheet *sheet,
           ...`
  - `media_has_source` (function, line 3390) `static int media_has_source(const lxb_dom_node_t *n)`
  - `element_is_content_leaf` (function, line 3404) `static int element_is_content_leaf(const lxb_dom_node_t *n, const css_sheet *sheet,
             ...`
  - `resolve_context` (function, line 3418) `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                ...`
  - `opens` (function, line 3739) `* painter applies it when the box opens (band/shared context) — seeding
             * it onto ru...`
  - `css_inline_boxdeco` (function, line 3779) `css_inline_boxdeco(cs) &&
                           !is_layout_item(p, sheet, style_cache))`
  - `margins` (function, line 3819) `* margins (boxdef_from_style) and the painter applies them when
                         * it ope...`
  - `container` (function, line 3942) `* membership in this container (and none in any container further out,
                 * since i...`
  - `walk` (function, line 4040) `* far on this walk (they are all inside this element). */

                        /* The innermo...`
  - `float` (function, line 4165) `* genuinely nested float (oid != id) takes the deferred-column path. */
    if (cont->float_oid =...`
  - `sz_count` (function, line 4211) `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)`
  - `sz_write` (function, line 4225) `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)`
  - `serialize_subtree` (function, line 4233) `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)`
  - `collapse_ws` (function, line 4252) `static char *collapse_ws(const char *s, size_t n)`
  - `pv_frame_marked` (function, line 4282) `static int pv_frame_marked(const lxb_dom_node_t *n)`
  - `parse_dim` (function, line 4291) `static int parse_dim(const lxb_char_t *s, size_t len)`
  - `present` (function, line 4308) `* when no width descriptors are present (density-only or bare URLs). */
static void srcset_best_u...`
  - `srcset_slot_width` (function, line 4403) `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,
                              ...`
  - `dimensions` (function, line 4449) `* viewport dimensions (data: inline detection, <picture> <source> scanning). */
static void srcse...`
  - `find_body` (function, line 4481) `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)`
  - `find_root_els` (function, line 4494) `static pv_root_els find_root_els(lxb_dom_node_t *root)`
  - `attributes` (function, line 4508) `* carries those attributes (spec/css.md, "Root matcher"). */
static int root_els_match(void *ctx,...`
  - `string` (function, line 4519) `* Returns a heap string (caller frees) or NULL when neither carries a class —
 * NULL simply mean...`
  - `forms_free` (function, line 4567) `static void forms_free(form_table *ft)`
  - `ascii_ieq` (function, line 4574) `static int ascii_ieq(const char *s, const char *lit)`
  - `attr_dup` (function, line 4586) `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)`
  - `forms_add` (function, line 4595) `static int forms_add(form_table *ft, const lxb_dom_node_t *node)`
  - `form_for` (function, line 4615) `static int form_for(const form_table *ft, const lxb_dom_node_t *n,
                    const lxb_...`
  - `under_unrendered` (function, line 4631) `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)`
  - `collect_text` (function, line 4644) `static char *collect_text(const lxb_dom_node_t *el)`
  - `classify_input` (function, line 4668) `static pv_input_type classify_input(const char *type)`
  - `li_ordinal` (function, line 4839) `static int li_ordinal(const lxb_dom_node_t *li)`
  - `roman_marker` (function, line 4865) `static void roman_marker(int n, int upper, char *out, size_t cap)`
  - `list_marker` (function, line 4890) `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,
                  ...`
  - `node_table_role` (function, line 4931) `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)`
  - `nearest_table` (function, line 4949) `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
 ...`
  - `parent_is_table_internal` (function, line 4988) `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)`
  - `nearest_cell` (function, line 5015) `static const lxb_dom_node_t *nearest_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
  ...`
  - `cell_has_nested_table` (function, line 5030) `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)`
  - `next_skip` (function, line 5039) `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)`
  - `cell_anchors` (function, line 5050) `static const lxb_dom_node_t *cell_anchors(const lxb_dom_node_t *cell, int *count)`
  - `links` (function, line 5068) `* its links (the Hacker News case: every story link lives inside a <td>), so the
 * caller flows ...`
  - `flow_table` (function, line 5089) `static int flow_table(pv_flow_reg *fr, const lxb_dom_node_t *table)`
  - `in_flow_table_cell` (function, line 5101) `static int in_flow_table_cell(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,
           ...`
  - `table` (function, line 5110) `* FLOW table (multi-link: walked so its links survive) do NOT suppress their
 * content -- their ...`
  - `table_columns` (function, line 5128) `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)`
  - `in_hidden_subtree` (function, line 5202) `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
               ...`
  - `in_boilerplate_subtree` (function, line 5229) `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)`
  - `in_closed_details_subtree` (function, line 5244) `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)`
  - `pv_build` (function, line 5264) `pv_status pv_build(const hp_document *doc, pv_view **out)`
  - `pv_build_ex` (function, line 5268) `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)`
  - `pv_build_full` (function, line 5272) `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                     ...`
  - `annotate_replaced_run` (function, line 5294) `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,
                            ...`
  - `pv_root_insets` (function, line 5369) `void pv_root_insets(const css_style *body, int out[4])`
  - `collect_page_css` (function, line 5379) `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,
                     ...`
  - `pv_cnt_attr` (function, line 5421) `static const char *pv_cnt_attr(void *ctx, const char *name)`
  - `pv_cnt_resolve_field` (function, line 5434) `static void pv_cnt_resolve_field(const cnt_state *st, lxb_dom_element_t *el, char *field)`
  - `pv_cnt_enter` (function, line 5445) `static int pv_cnt_enter(cnt_state *st, lxb_dom_node_t *n, int depth, const css_sheet *sheet,
    ...`
  - `pv_cnt_exit` (function, line 5469) `static void pv_cnt_exit(cnt_state *st, lxb_dom_node_t *n, int depth, const css_sheet *sheet,
    ...`
  - `pv_counters_pass` (function, line 5481) `static void pv_counters_pass(lxb_dom_node_t *root, const css_sheet *sheet, pv_style_cache *cache)`
  - `pv_build_styled` (function, line 5505) `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                   ...`
  - `px` (function, line 6110) `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */
                if (iw <...`
  - `engine` (function, line 7075) `* layout engine (contiguous item gather) drops every cell onto its own row and
         * a 2-col...`
  - `pv_css_drops` (function, line 7217) `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,
                       const cha...`
  - `pv_computed_new` (function, line 7251) `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css,
  ...`
  - `pv_computed_get` (function, line 7270) `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st,
                    do...`
  - `pv_computed_free` (function, line 7292) `void pv_computed_free(pv_computed *pc)`
  - `positions` (function, line 141) `* positions (cp == 0) keep the legacy '?' fallback. */ unsigned int cp = cp1252_to_ucs(c);`
  - `content` (function, line 1195) `* a <noscript> ancestor also suppresses content (the script would run, so the * fallback is hidden);`
  - `address` (function, line 1263) `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <=...`
  - `child` (function, line 1271) `* child (NULL = anonymous item: text directly inside the container);`
  - `id` (function, line 1295) `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);`
  - `it` (function, line 1392) `* it (they inherit in CSS). list_style drives the <li> marker (structural);`
  - `here` (function, line 2068) `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3...`
  - `glyphs` (function, line 2116) `* glyphs (the runs carry it as their fill source);`
  - `col_free_share` (function, line 2765) `static int col_free_share(const lxb_dom_node_t *el, const css_style *cs, const css_sheet *sheet, pv_style_cache...`
  - `none` (function, line 2787) `* inherited when it declares none (every hamburger bar and divider drawn as * a coloured empty box). A box cannot...`
  - `outermost` (function, line 3682) `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);`
  - `inside` (function, line 5623) `* page inside (the top one collapses with the first child's margin), so a * margin-only body stays box-less. */...`
  - `control` (function, line 5932) `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);`
  - `band` (function, line 6176) `* run: without its float annotation it cut the band (the icon row of a * `float:right` social list became one float...`
  - `height` (function, line 6203) `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
  - `block_id` (function, line 6361) `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it...`
  - `URL` (function, line 6502) `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
  - `block` (function, line 6790) `* block (Gecko): it never resolves as its own block here. */ int opens_line = block != n && (pending_break || block...`
  - `flow` (function, line 6969) `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through...`
  - `line` (function, line 7084) `* to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);`
  - `_POSIX_C_SOURCE` (macro, line 10) `#define _POSIX_C_SOURCE`
  - `PV_MAX_DIM` (macro, line 53) `#define PV_MAX_DIM`
  - `PV_FONT_REL_MIN` (macro, line 58) `#define PV_FONT_REL_MIN`
  - `PV_FONT_REL_MAX` (macro, line 59) `#define PV_FONT_REL_MAX`
  - `PV_FONT_CHAIN_MAX` (macro, line 65) `#define PV_FONT_CHAIN_MAX`
  - `PV_FONT_PCT_MIN` (macro, line 66) `#define PV_FONT_PCT_MIN`
  - `PV_FONT_PCT_MAX` (macro, line 67) `#define PV_FONT_PCT_MAX`
  - `PV_NODE_MAP_INIT_CAP` (macro, line 350) `#define PV_NODE_MAP_INIT_CAP`
  - `PV_COLOR_TOKEN_MAX` (macro, line 1213) `#define PV_COLOR_TOKEN_MAX`
  - `PV_MAX_CONTAINERS` (macro, line 1251) `#define PV_MAX_CONTAINERS`
  - `PV_MAX_GRID_COLS` (macro, line 1252) `#define PV_MAX_GRID_COLS`
  - `PV_MAX_BOXES` (macro, line 1260) `#define PV_MAX_BOXES`
  - `PV_STYLE_RETIRE_MAX` (macro, line 2324) `#define PV_STYLE_RETIRE_MAX`
  - `PV_STYLE_RESERVE_MAX` (macro, line 2378) `#define PV_STYLE_RESERVE_MAX`
  - `PV_MAX_INLINE_ROW_ITEMS` (macro, line 2971) `#define PV_MAX_INLINE_ROW_ITEMS`
  - `PV_TEXTLESS_DEPTH_MAX` (macro, line 3313) `#define PV_TEXTLESS_DEPTH_MAX`
  - `PV_FRAME_DEF_W` (macro, line 4278) `#define PV_FRAME_DEF_W`
  - `PV_FRAME_DEF_H` (macro, line 4279) `#define PV_FRAME_DEF_H`
  - `PV_FRAME_URL_MAX` (macro, line 4280) `#define PV_FRAME_URL_MAX`
  - `PV_MAX_STYLE_BYTES` (macro, line 5155) `#define PV_MAX_STYLE_BYTES`
- Depends on: `include/box_style.h`, `include/box_tree.h`, `include/css.h`, `include/css_chain.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_vars.h`, `include/dom.h`, `include/flex_layout.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/page_view.h`, `include/svg_render.h`, `include/util.h`

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

## src/prefs.c
- Doc: url_valid: A representable URL: 1..PREFS_MAX_URL-1 bytes, no control bytes, no DEL. * Space is...
- Layer: utility
- Language: c
- Symbols:
  - `sbuf` (struct, line 380)
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
  - `apply_kv` (function, line 231) `static void apply_kv(prefs_state *out, const char *key, long val)`
  - `prefs_parse` (function, line 247) `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)`
  - `ci_eq` (function, line 313) `static int ci_eq(char a, char b)`
  - `ci_starts` (function, line 319) `static int ci_starts(const char *s, const char *q)`
  - `ci_contains` (function, line 327) `static int ci_contains(const char *s, const char *q)`
  - `url_prefix_match` (function, line 336) `static int url_prefix_match(const char *url, const char *q)`
  - `sugg_push` (function, line 348) `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,
                      cons...`
  - `prefs_suggest` (function, line 357) `int prefs_suggest(const prefs_state *p, const char *query,
                  char *out, size_t ro...`
  - `sb_put` (function, line 382) `static void sb_put(sbuf *b, const char *s, size_t n)`
  - `sb_str` (function, line 397) `static void sb_str(sbuf *b, const char *s)`
  - `sb_esc` (function, line 400) `static void sb_esc(sbuf *b, const char *s)`
  - `sb_link_item` (function, line 413) `static void sb_link_item(sbuf *b, const char *url, const char *label)`
  - `prefs_bookmarks_page` (function, line 421) `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)`
  - `_POSIX_C_SOURCE` (macro, line 11) `#define _POSIX_C_SOURCE`
  - `PREFS_MAGIC` (macro, line 20) `#define PREFS_MAGIC`
- Depends on: `include/prefs.h`, `include/zoom.h`


Next: [KB_src_p8.md](KB_src_p8.md)
