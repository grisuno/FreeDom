# Subsystem: src (page 6 of 7)
Previous: [KB_src_p5.md](KB_src_p5.md)

## src/page_view.c
- Doc: pv_cont_info: Nearest-container info attached to a run, plus the flex per-item values (Stage 3)...
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
  - `address` (function, line 1090) `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <=...`
  - `child` (function, line 1098) `* child (NULL = anonymous item: text directly inside the container);`
  - `id` (function, line 1118) `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);`
  - `it` (function, line 1209) `* it (they inherit in CSS). list_style drives the <li> marker (structural);`
  - `here` (function, line 1749) `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3...`
  - `glyphs` (function, line 1787) `* glyphs (the runs carry it as their fill source);`
  - `outermost` (function, line 2871) `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);`
  - `control` (function, line 4857) `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);`
  - `height` (function, line 5075) `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
  - `block_id` (function, line 5173) `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it...`
  - `URL` (function, line 5304) `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
  - `flow` (function, line 5726) `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through...`
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
- Doc: ci_starts: static int is_ws(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' ||...
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
- Doc: url_valid: A representable URL: 1..PREFS_MAX_URL-1 bytes, no control bytes, no DEL. * Space is...
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
- Doc: keyfile_create: #include <unistd.h> #include <openssl/crypto.h> #include <openssl/rand.h>...
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
- Doc: rd_push: Appends one block, taking owned copies of text (required) and href (optional). *...
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
  - `place` (function, line 220) `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never...`
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
  - `write_full` (function, line 40) `&& write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 || write_full(wfd, title, tl) == 0) && write_full(wfd, &xl...`
  - `_POSIX_C_SOURCE` (macro, line 7) `#define _POSIX_C_SOURCE`
- Depends on: `include/html_parse.h`, `include/os_sandbox.h`, `include/renderer.h`, `include/util.h`

## src/request_policy.c
- Doc: public_suffix_labels: Number of labels of the public suffix (eTLD) of a lowercased host...
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


Next: [KB_src_p7.md](KB_src_p7.md)
