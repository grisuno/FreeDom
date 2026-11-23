# Symbols (page 11 of 19)
Previous: [SYMBOLS_p10.md](SYMBOLS_p10.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `is_italic_tag` | function | `src/page_view.c:3192` | `static int is_italic_tag(lxb_tag_id_t t)` |
| `is_layout_container` | function | `src/page_view.c:3480` | `static int is_layout_container(const lxb_dom_node_t *el, const css_style *cs,                    ...` |
| `is_mono_tag` | function | `src/page_view.c:3198` | `static int is_mono_tag(lxb_tag_id_t t)` |
| `is_plain_wrapper` | function | `src/page_view.c:3682` | `static int is_plain_wrapper(const lxb_dom_node_t *c, const css_style *cs)` |
| `is_skipped_tag` | function | `src/page_view.c:1187` | `static int is_skipped_tag(lxb_tag_id_t t)` |
| `it` | function | `src/page_view.c:3329` | `* without it (minified markup) keeps the row gapless -- the mixed case is a known limit. */ stati...` |
| `item_ordinal` | function | `src/page_view.c:1396` | `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)` |
| `item_sizes_itself` | function | `src/page_view.c:3535` | `static int item_sizes_itself(const lxb_dom_node_t *el, const css_style *cs,                      ...` |
| `item_space_before` | function | `src/page_view.c:1381` | `static int item_space_before(const lxb_dom_node_t *item)` |
| `li_is_list_item` | function | `src/page_view.c:3551` | `static int li_is_list_item(const lxb_dom_node_t *li, const css_sheet *sheet,                     ...` |
| `li_ordinal` | function | `src/page_view.c:5300` | `static int li_ordinal(const lxb_dom_node_t *li)` |
| `line` | function | `src/page_view.c:7639` | `* to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);` |
| `list_marker` | function | `src/page_view.c:5351` | `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,                   ...` |
| `margins` | function | `src/page_view.c:4193` | `* margins (boxdef_from_style) and the painter applies them when                          * it ope...` |
| `mb` | type_alias | `src/page_view.c:1420` | `typedef struct pv_box_info { int l, r, w, center, mt, mb;` |
| `media_has_source` | function | `src/page_view.c:3720` | `static int media_has_source(const lxb_dom_node_t *n)` |
| `mono_generic_size` | function | `src/page_view.c:3205` | `static void mono_generic_size(const pv_text_ext *ext, int *font_scale)` |
| `nearest_table` | function | `src/page_view.c:5414` | `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,  ...` |
| `next_skip` | function | `src/page_view.c:5499` | `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)` |
| `node_next` | function | `src/page_view.c:1010` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `node_table_role` | function | `src/page_view.c:5396` | `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `node_tag` | function | `src/page_view.c:1208` | `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)` |
| `none` | function | `src/page_view.c:3019` | `* inherited when it declares none (every hamburger bar and divider drawn as * a coloured empty box). A box cannot...` |
| `opens` | function | `src/page_view.c:4101` | `* painter applies it when the box opens (band/shared context) — seeding              * it onto ru...` |
| `outermost` | function | `src/page_view.c:4044` | `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);` |
| `paints` | function | `src/page_view.c:1128` | `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas  * vacías"). Comment a...` |
| `parent_is_author_container` | function | `src/page_view.c:3005` | `static int parent_is_author_container(const lxb_dom_node_t *node, const css_sheet *sheet,        ...` |
| `parent_is_table_internal` | function | `src/page_view.c:5453` | `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `parse_dim` | function | `src/page_view.c:4709` | `static int parse_dim(const lxb_char_t *s, size_t len)` |
| `positions` | function | `src/page_view.c:145` | `* positions (cp == 0) keep the legacy '?' fallback. */ unsigned int cp = cp1252_to_ucs(c);` |
| `present` | function | `src/page_view.c:4726` | `* when no width descriptors are present (density-only or bare URLs). */ static void srcset_best_u...` |
| `pseudo_box_reg` | function | `src/page_view.c:2329` | `static int pseudo_box_reg(pv_box_reg *r, const lxb_dom_node_t *el, int which,                    ...` |
| `pseudo_generates_box` | function | `src/page_view.c:2350` | `static int pseudo_generates_box(const css_style *ps)` |
| `pseudo_is_block` | function | `src/page_view.c:2367` | `static int pseudo_is_block(const css_style *ps)` |
| `pseudo_is_oof` | function | `src/page_view.c:2363` | `static int pseudo_is_oof(const css_style *ps)` |
| `pseudo_key` | function | `src/page_view.c:2373` | `static const void *pseudo_key(const lxb_dom_node_t *el, int which)` |
| `pv_add_box_def` | function | `src/page_view.c:958` | `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)` |
| `pv_add_cont_def` | function | `src/page_view.c:936` | `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)` |
| `pv_after_pending` | struct | `src/page_view.c:1959` | `` |
| `pv_append` | function | `src/page_view.c:441` | `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,                     c...` |
| `pv_append_image` | function | `src/page_view.c:476` | `pv_status pv_append_image(pv_view *v, int heading, int block_break,                           con...` |
| `pv_append_input` | function | `src/page_view.c:506` | `pv_status pv_append_input(pv_view *v, int heading, int block_break,                           pv_...` |
| `pv_append_svg` | function | `src/page_view.c:582` | `pv_status pv_append_svg(pv_view *v, int heading, int block_break,                         const c...` |
| `pv_append_video` | function | `src/page_view.c:546` | `pv_status pv_append_video(pv_view *v, int heading, int block_break,                           con...` |
| `pv_apply_pres_hints` | function | `src/page_view.c:2725` | `static void pv_apply_pres_hints(lxb_dom_element_t *el, css_style *cs)` |
| `pv_at` | function | `src/page_view.c:993` | `const pv_run *pv_at(const pv_view *v, size_t i)` |
| `pv_box_at` | function | `src/page_view.c:1002` | `const pv_box_def *pv_box_at(const pv_view *v, size_t i)` |
| `pv_box_count` | function | `src/page_view.c:998` | `size_t pv_box_count(const pv_view *v)` |
| `pv_box_info` | struct | `src/page_view.c:1420` | `` |
| `pv_box_reg` | struct | `src/page_view.c:2001` | `` |
| `pv_build` | function | `src/page_view.c:5795` | `pv_status pv_build(const hp_document *doc, pv_view **out)` |
| `pv_build_cached` | function | `src/page_view.c:6043` | `pv_status pv_build_cached(const hp_document *doc, int js_enabled, int reader,                    ...` |
| `pv_build_cq` | function | `src/page_view.c:6050` | `pv_status pv_build_cq(const hp_document *doc, int js_enabled, int reader,                       i...` |
| `pv_build_ex` | function | `src/page_view.c:5799` | `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)` |
| `pv_build_full` | function | `src/page_view.c:5803` | `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,                      ...` |
| `pv_build_live` | function | `src/page_view.c:6057` | `pv_status pv_build_live(const hp_document *doc, int js_enabled, int reader,                      ...` |
| `pv_build_styled` | function | `src/page_view.c:6036` | `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,                    ...` |
| `pv_cache_find` | function | `src/page_view.c:2549` | `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cache_put` | function | `src/page_view.c:2569` | `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,                      ...` |
| `pv_cache_reindex` | function | `src/page_view.c:2467` | `static void pv_cache_reindex(pv_style_cache *c)` |
| `pv_cached_font_px` | function | `src/page_view.c:2564` | `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cell_table` | function | `src/page_view.c:2709` | `static lxb_dom_element_t *pv_cell_table(lxb_dom_element_t *el)` |
| `pv_cnt_attr` | function | `src/page_view.c:5952` | `static const char *pv_cnt_attr(void *ctx, const char *name)` |
| `pv_cnt_attr_ctx` | struct | `src/page_view.c:5947` | `` |
| `pv_cnt_enter` | function | `src/page_view.c:5976` | `static int pv_cnt_enter(cnt_state *st, lxb_dom_node_t *n, int depth, const css_sheet *sheet,     ...` |
| `pv_cnt_exit` | function | `src/page_view.c:6000` | `static void pv_cnt_exit(cnt_state *st, lxb_dom_node_t *n, int depth, const css_sheet *sheet,     ...` |
| `pv_cnt_resolve_field` | function | `src/page_view.c:5965` | `static void pv_cnt_resolve_field(const cnt_state *st, lxb_dom_element_t *el, char *field)` |
| `pv_computed` | struct | `src/page_view.c:7827` | `` |
| `pv_computed_free` | function | `src/page_view.c:7873` | `void pv_computed_free(pv_computed *pc)` |
| `pv_computed_get` | function | `src/page_view.c:7851` | `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st,                     do...` |
| `pv_computed_new` | function | `src/page_view.c:7832` | `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css,   ...` |
| `pv_computed_new_cached` | function | `src/page_view.c:7837` | `pv_computed *pv_computed_new_cached(const hp_document *doc, int prefers_dark,                    ...` |
| `pv_cont_at` | function | `src/page_view.c:953` | `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)` |
| `pv_cont_count` | function | `src/page_view.c:949` | `size_t pv_cont_count(const pv_view *v)` |
| `pv_cont_info` | struct | `src/page_view.c:1284` | `` |
| `pv_container_reg` | struct | `src/page_view.c:1783` | `` |
| `pv_content_hidden` | function | `src/page_view.c:1441` | `int pv_content_hidden(int box_hidden, int run_visibility)` |
| `pv_control_frame_cleared` | function | `src/page_view.c:1631` | `static int pv_control_frame_cleared(const css_style *cs)` |
| `pv_count` | function | `src/page_view.c:989` | `size_t pv_count(const pv_view *v)` |
| `pv_counters_pass` | function | `src/page_view.c:6012` | `static void pv_counters_pass(lxb_dom_node_t *root, const css_sheet *sheet, pv_style_cache *cache)` |
| `pv_cq_push` | function | `src/page_view.c:2642` | `static const cmq_container *pv_cq_push(pv_style_cache *cache, const lxb_dom_node_t *node,        ...` |
| `pv_css_drops` | function | `src/page_view.c:7798` | `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,                        const cha...` |
| `pv_def_h` | struct | `src/page_view.c:2401` | `` |
| `pv_element_has_before` | function | `src/page_view.c:3628` | `static int pv_element_has_before(lxb_dom_node_t *n, const css_sheet *sheet,                      ...` |
| `pv_flow_reg` | struct | `src/page_view.c:3739` | `` |
| `pv_flow_reg` | struct | `src/page_view.c:5376` | `` |
| `pv_frame_marked` | function | `src/page_view.c:4700` | `static int pv_frame_marked(const lxb_dom_node_t *n)` |
| `pv_free` | function | `src/page_view.c:971` | `void pv_free(pv_view *v)` |
| `pv_hint_attr` | function | `src/page_view.c:2688` | `static const char *pv_hint_attr(void *ctx, const char *name, size_t *len)` |
| `pv_item_track` | struct | `src/page_view.c:1367` | `` |
| `pv_mauto_of` | function | `src/page_view.c:1558` | `static int pv_mauto_of(const css_style *cs)` |
| `pv_new` | function | `src/page_view.c:437` | `pv_view *pv_new(void)` |
| `pv_node_map` | struct | `src/page_view.c:356` | `` |
| `pv_node_map_build` | function | `src/page_view.c:426` | `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root,                         ...` |
| `pv_node_map_free` | function | `src/page_view.c:374` | `static void pv_node_map_free(pv_node_map *m)` |
| `pv_node_map_init` | function | `src/page_view.c:364` | `static int pv_node_map_init(pv_node_map *m)` |
| `pv_parent_element` | function | `src/page_view.c:2681` | `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)` |
| `pv_placeholder_color` | function | `src/page_view.c:920` | `int pv_placeholder_color(const css_style *ph)` |
| `pv_ptr_hash` | function | `src/page_view.c:2459` | `static size_t pv_ptr_hash(const void *p)` |
| `pv_ptrmap` | struct | `src/page_view.c:302` | `` |
| `pv_ptrmap_free` | function | `src/page_view.c:348` | `static void pv_ptrmap_free(pv_ptrmap *m)` |
| `pv_ptrmap_get` | function | `src/page_view.c:318` | `static int pv_ptrmap_get(const pv_ptrmap *m, const void *k, int *out)` |
| `pv_ptrmap_put` | function | `src/page_view.c:326` | `static void pv_ptrmap_put(pv_ptrmap *m, const void *k, int v)` |
| `pv_ptrmap_slot` | function | `src/page_view.c:308` | `static size_t pv_ptrmap_slot(const pv_ptrmap *m, const void *k)` |
| `pv_root_els` | struct | `src/page_view.c:4908` | `` |
| `pv_root_insets` | function | `src/page_view.c:5900` | `void pv_root_insets(const css_style *body, int out[4])` |
| `pv_set_bgcolor` | function | `src/page_view.c:628` | `void pv_set_bgcolor(pv_view *v, int bg_rgb)` |
| `pv_set_block_id` | function | `src/page_view.c:851` | `void pv_set_block_id(pv_view *v, int block_id)` |
| `pv_set_block_node` | function | `src/page_view.c:871` | `void pv_set_block_node(pv_view *v, dom_node_id id)` |
| `pv_set_box` | function | `src/page_view.c:810` | `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,                 int box_center, int ...` |
| `pv_set_box_maxw` | function | `src/page_view.c:833` | `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct)` |
| `pv_set_box_pct` | function | `src/page_view.c:822` | `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,                     ...` |
| `pv_set_br_line` | function | `src/page_view.c:876` | `void pv_set_br_line(pv_view *v, int br_line)` |
| `pv_set_color` | function | `src/page_view.c:623` | `void pv_set_color(pv_view *v, int fg_rgb)` |
| `pv_set_cont_box` | function | `src/page_view.c:750` | `void pv_set_cont_box(pv_view *v, int cont_box_id)` |
| `pv_set_cont_item` | function | `src/page_view.c:772` | `void pv_set_cont_item(pv_view *v, int cont_item)` |
| `pv_set_container` | function | `src/page_view.c:710` | `void pv_set_container(pv_view *v, int cont_id, int cont_display,                       int cont_g...` |
| `pv_set_emphasis` | function | `src/page_view.c:611` | `void pv_set_emphasis(pv_view *v, int bold, int italic)` |
| `pv_set_flex` | function | `src/page_view.c:754` | `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,                  int...` |
| `pv_set_flex_mauto` | function | `src/page_view.c:766` | `void pv_set_flex_mauto(pv_view *v, int mauto)` |
| `pv_set_float` | function | `src/page_view.c:788` | `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear,                 int ...` |
| `pv_set_float_w` | function | `src/page_view.c:777` | `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box,                     ...` |
| `pv_set_grad_text` | function | `src/page_view.c:644` | `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)` |
| `pv_set_grid` | function | `src/page_view.c:736` | `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)` |
| `pv_set_grid_area` | function | `src/page_view.c:729` | `void pv_set_grid_area(pv_view *v, int row_start, int col_start)` |
| `pv_set_grid_rows` | function | `src/page_view.c:746` | `void pv_set_grid_rows(pv_view *v, int grid_rows)` |
| `pv_set_indent` | function | `src/page_view.c:618` | `void pv_set_indent(pv_view *v, int indent)` |
| `pv_set_input_checked` | function | `src/page_view.c:881` | `void pv_set_input_checked(pv_view *v, int checked)` |
| `pv_set_input_placeholder` | function | `src/page_view.c:886` | `void pv_set_input_placeholder(pv_view *v, int ph_color)` |
| `pv_set_input_select_opts` | function | `src/page_view.c:928` | `void pv_set_input_select_opts(pv_view *v, const char *select_opts)` |
| `pv_set_justify_self` | function | `src/page_view.c:866` | `void pv_set_justify_self(pv_view *v, int justify_self)` |
| `pv_set_node_id` | function | `src/page_view.c:846` | `void pv_set_node_id(pv_view *v, dom_node_id node_id)` |
| `pv_set_oof` | function | `src/page_view.c:861` | `void pv_set_oof(pv_view *v, int oof)` |
| `pv_set_own_box` | function | `src/page_view.c:856` | `void pv_set_own_box(pv_view *v, int box_id)` |
| `pv_set_row_span` | function | `src/page_view.c:725` | `void pv_set_row_span(pv_view *v, int row_span)` |
| `pv_set_text_ext` | function | `src/page_view.c:652` | `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)` |
| `pv_set_text_style` | function | `src/page_view.c:633` | `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,                 ...` |
| `pv_set_ua_tag` | function | `src/page_view.c:840` | `void pv_set_ua_tag(pv_view *v, int ua_tag)` |
| `pv_style_cache` | struct | `src/page_view.c:2415` | `` |
| `pv_style_cache_free` | function | `src/page_view.c:2503` | `static void pv_style_cache_free(pv_style_cache *c)` |
| `pv_style_cache_reserve` | function | `src/page_view.c:2524` | `static void pv_style_cache_reserve(pv_style_cache *c, size_t n)` |
| `pv_svg_append_root_attrs` | function | `src/page_view.c:891` | `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs,                ...` |
| `pv_text_ext_merge` | function | `src/page_view.c:1477` | `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)` |
| `pv_text_ext_reset` | function | `src/page_view.c:1447` | `void pv_text_ext_reset(pv_text_ext *e)` |
| `pv_var_node` | struct | `src/page_view.c:2392` | `` |
| `pv_var_push` | function | `src/page_view.c:2619` | `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,                       ...` |
| `px` | function | `src/page_view.c:6664` | `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */                 if (iw <...` |
| `resolve_context` | function | `src/page_view.c:3751` | `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,                 ...` |
| `resolves` | function | `src/page_view.c:1074` | `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close  * button/tooltip w...` |
| `roman_marker` | function | `src/page_view.c:5326` | `static void roman_marker(int n, int upper, char *out, size_t cap)` |
| `row_lone_float_side` | function | `src/page_view.c:3282` | `static int row_lone_float_side(const lxb_dom_node_t *p, const css_sheet *sheet,                  ...` |
| `run_init_common` | function | `src/page_view.c:170` | `static void run_init_common(pv_run *r)` |
| `serialize_subtree` | function | `src/page_view.c:4651` | `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)` |
| `size` | function | `src/page_view.c:3112` | `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */ static void app...` |
| `srcset_slot_width` | function | `src/page_view.c:4821` | `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,                               ...` |
| `string` | function | `src/page_view.c:4937` | `* Returns a heap string (caller frees) or NULL when neither carries a class —  * NULL simply mean...` |
| `subtree_has_own_text` | function | `src/page_view.c:3660` | `static int subtree_has_own_text(const lxb_dom_node_t *n, const lxb_dom_node_t *base,             ...` |
| `subtree_is_oof` | function | `src/page_view.c:3092` | `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,                      ...` |
| `sz_count` | function | `src/page_view.c:4629` | `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)` |
| `sz_fill` | struct | `src/page_view.c:4637` | `` |
| `sz_write` | function | `src/page_view.c:4643` | `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)` |
| `table_cell_pos` | function | `src/page_view.c:3746` | `static int table_cell_pos(struct pv_flow_reg *fr, const lxb_dom_node_t *table, const lxb_dom_node_t *cell, int *row...` |
| `table_columns` | function | `src/page_view.c:5650` | `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)` |
| `table_columns_scan` | function | `src/page_view.c:5659` | `static int table_columns_scan(const lxb_dom_node_t *table, const pv_flow_reg *fr)` |
| `table_next_row` | function | `src/page_view.c:5522` | `static const lxb_dom_node_t *table_next_row(const lxb_dom_node_t *table,                         ...` |
| `text_node_is_blank` | function | `src/page_view.c:1380` | `static int text_node_is_blank(const lxb_dom_node_t *c);` |
| `them` | function | `src/page_view.c:1371` | `* them (PV_BR_ATOM_SPACE);` |
| `trying` | function | `src/page_view.c:2011` | `* a real page passes without trying (slashdot's front page saturates it), and past  * it box_reg_...` |
| `ua_field_background` | function | `src/page_view.c:1643` | `static void ua_field_background(pv_box_def *d, int frame_cleared)` |
| `ua_tag_of` | function | `src/page_view.c:1153` | `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)` |
| `under_unrendered` | function | `src/page_view.c:5092` | `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)` |
| `url` | function | `src/page_view.c:6082` | `* fetches and drops url()/@-rules). A NULL sheet is treated as empty by the css * module, so OOM here degrades to...` |
| `utf8_encode` | function | `src/page_view.c:109` | `static size_t utf8_encode(unsigned int cp, char *out)` |
| `utf8_sanitized_dup` | function | `src/page_view.c:122` | `static char *utf8_sanitized_dup(const char *s)` |
| `walk` | function | `src/page_view.c:4441` | `* far on this walk (they are all inside this element). */                          /* The innermo...` |
| `pe_build_path` | function | `src/pdf_export.c:91` | `pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz)` |
| `pe_build_path_ext` | function | `src/pdf_export.c:66` | `pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,                 ...` |
| `pe_paginate` | function | `src/pdf_export.c:95` | `size_t pe_paginate(const double *tops, const double *heights, size_t n,                    double...` |
| `pe_safe_basename` | function | `src/pdf_export.c:25` | `pe_status pe_safe_basename(const char *title, char *out, size_t outsz)` |
| `PT_LINE_CAP` | macro | `src/perf_trace.c:107` | `#define PT_LINE_CAP` |
| `cmp_u64` | function | `src/perf_trace.c:71` | `static int cmp_u64(const void *a, const void *b)` |
| `pt_count` | function | `src/perf_trace.c:35` | `size_t pt_count(const pt_trace *t, pt_stage stage)` |
| `pt_elapsed_us` | function | `src/perf_trace.c:21` | `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us)` |
| `pt_format` | function | `src/perf_trace.c:109` | `size_t pt_format(const pt_trace *t, char *buf, size_t cap)` |
| `pt_init` | function | `src/perf_trace.c:16` | `void pt_init(pt_trace *t)` |
| `pt_last_us` | function | `src/perf_trace.c:40` | `uint64_t pt_last_us(const pt_trace *t, pt_stage stage)` |
| `pt_max_us` | function | `src/perf_trace.c:60` | `uint64_t pt_max_us(const pt_trace *t, pt_stage stage)` |
| `pt_median_us` | function | `src/perf_trace.c:79` | `uint64_t pt_median_us(const pt_trace *t, pt_stage stage)` |
| `pt_min_us` | function | `src/perf_trace.c:49` | `uint64_t pt_min_us(const pt_trace *t, pt_stage stage)` |
| `pt_record` | function | `src/perf_trace.c:26` | `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us)` |
| `pt_stage_name` | function | `src/perf_trace.c:89` | `const char *pt_stage_name(pt_stage stage)` |
| `PQS_SS_LEN` | macro | `src/pq_seal.c:17` | `#define PQS_SS_LEN` |
| `derive_key` | function | `src/pq_seal.c:81` | `static int derive_key(const uint8_t ss[PQS_SS_LEN], const uint8_t wrap[LS_KEY_LEN],              ...` |
| `keys_wrap` | function | `src/pq_seal.c:35` | `static pqs_keys *keys_wrap(EVP_PKEY *pkey)` |
| `pqs_buf_free` | function | `src/pq_seal.c:23` | `void pqs_buf_free(uint8_t *buf, size_t len)` |
| `pqs_export` | function | `src/pq_seal.c:55` | `pqs_status pqs_export(const pqs_keys *k, uint8_t **der, size_t *len)` |
| `pqs_free` | function | `src/pq_seal.c:29` | `void pqs_free(pqs_keys *k)` |
| `pqs_generate` | function | `src/pq_seal.c:42` | `pqs_status pqs_generate(pqs_keys **out)` |
| `pqs_import` | function | `src/pq_seal.c:68` | `pqs_status pqs_import(const uint8_t *der, size_t len, pqs_keys **out)` |
| `pqs_keys` | struct | `src/pq_seal.c:19` | `` |
| `pqs_open` | function | `src/pq_seal.c:147` | `pqs_status pqs_open(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],                     const ...` |
| `pqs_seal` | function | `src/pq_seal.c:106` | `pqs_status pqs_seal(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],                     const ...` |
| `PF_MAX_URL` | macro | `src/prefetch.c:24` | `#define PF_MAX_URL` |
| `_POSIX_C_SOURCE` | macro | `src/prefetch.c:12` | `#define _POSIX_C_SOURCE` |
| `attr_span` | struct | `src/prefetch.c:65` | `` |
| `ci_eq_span` | function | `src/prefetch.c:58` | `static int ci_eq_span(const char *s, size_t n, const char *kw)` |
| `ci_find` | function | `src/prefetch.c:49` | `static const char *ci_find(const char *p, const char *end, const char *kw)` |
| `ci_starts` | function | `src/prefetch.c:40` | `static int ci_starts(const char *p, const char *end, const char *kw)` |
| `emit` | function | `src/prefetch.c:120` | `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)` |
| `is_name_char` | function | `src/prefetch.c:30` | `static int is_name_char(char c)` |
| `is_ws` | function | `src/prefetch.c:26` | `static int is_ws(char c)` |
| `js_ident_ch` | function | `src/prefetch.c:213` | `static int js_ident_ch(char c)` |
| `js_skip_string` | function | `src/prefetch.c:225` | `static size_t js_skip_string(const char *s, size_t i, size_t n)` |
| `js_skip_ws` | function | `src/prefetch.c:218` | `static size_t js_skip_ws(const char *s, size_t i, size_t n)` |
| `js_take_spec` | function | `src/prefetch.c:232` | `static void js_take_spec(const char *s, size_t i, size_t n,                          char (*out)[...` |
| `lower` | function | `src/prefetch.c:35` | `static int lower(int c)` |
| `pf_find_importmap` | function | `src/prefetch.c:489` | `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n)` |
| `pf_follow_imports` | function | `src/prefetch.c:339` | `static void pf_follow_imports(pf_pool *p, const char *base, const char *body, size_t len)` |
| `pf_is_js` | function | `src/prefetch.c:317` | `static int pf_is_js(const char *url, const char *ctype)` |
| `pf_list_free` | function | `src/prefetch.c:202` | `void pf_list_free(pf_list *l)` |
| `pf_pool_add` | function | `src/prefetch.c:294` | `int pf_pool_add(pf_pool *p, const char *url)` |
| `pf_pool_finish` | function | `src/prefetch.c:546` | `void pf_pool_finish(pf_pool *p)` |
| `pf_pool_start` | function | `src/prefetch.c:393` | `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,                   pf_fetch_f...` |
| `pf_pool_start_page` | function | `src/prefetch.c:510` | `int pf_pool_start_page(pf_pool *p, const char *html, size_t len, const char *page_url,           ...` |
| `pf_pool_take` | function | `src/prefetch.c:450` | `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,                  char **body,...` |
| `pf_pooled_fetch` | function | `src/prefetch.c:567` | `int pf_pooled_fetch(void *vctx, const char *method, const char *url,                     const ch...` |
| `pf_scan` | function | `src/prefetch.c:133` | `int pf_scan(const char *html, size_t len, pf_list *out)` |
| `pf_scan_imports` | function | `src/prefetch.c:247` | `size_t pf_scan_imports(const char *js, size_t len, char (*out)[PF_SPEC_MAX], size_t cap)` |
| `pf_url_cb` | function | `src/prefetch.c:325` | `static int pf_url_cb(void *ctx, const char *base, const char *ref, char *out, size_t outsz)` |
| `pf_url_shaped` | function | `src/prefetch.c:330` | `static int pf_url_shaped(const char *sp)` |
| `pf_worker` | function | `src/prefetch.c:355` | `static void *pf_worker(void *arg)` |
| `pool_start` | function | `src/prefetch.c:400` | `static int pool_start(pf_pool *p, const char *const *urls, size_t nurls,                       pf...` |
| `PREFS_MAGIC` | macro | `src/prefs.c:20` | `#define PREFS_MAGIC` |
| `_POSIX_C_SOURCE` | macro | `src/prefs.c:11` | `#define _POSIX_C_SOURCE` |
| `apply_kv` | function | `src/prefs.c:231` | `static void apply_kv(prefs_state *out, const char *key, long val)` |
| `bookmark_push` | function | `src/prefs.c:91` | `static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title)` |
| `ci_contains` | function | `src/prefs.c:327` | `static int ci_contains(const char *s, const char *q)` |
| `ci_eq` | function | `src/prefs.c:313` | `static int ci_eq(char a, char b)` |
| `ci_starts` | function | `src/prefs.c:319` | `static int ci_starts(const char *s, const char *q)` |
| `history_push_back` | function | `src/prefs.c:109` | `static prefs_status history_push_back(prefs_state *p, const char *url)` |
| `prefs_bookmark_index` | function | `src/prefs.c:125` | `int prefs_bookmark_index(const prefs_state *p, const char *url)` |
| `prefs_bookmark_toggle` | function | `src/prefs.c:132` | `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,                              ...` |
| `prefs_bookmarks_page` | function | `src/prefs.c:421` | `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)` |
| `prefs_format` | function | `src/prefs.c:183` | `prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len)` |
| `prefs_free` | function | `src/prefs.c:74` | `void prefs_free(prefs_state *p)` |
| `prefs_history_add` | function | `src/prefs.c:152` | `prefs_status prefs_history_add(prefs_state *p, const char *url)` |
| `prefs_init` | function | `src/prefs.c:66` | `void prefs_init(prefs_state *p)` |
| `prefs_parse` | function | `src/prefs.c:247` | `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)` |
| `prefs_suggest` | function | `src/prefs.c:357` | `int prefs_suggest(const prefs_state *p, const char *query,                   char *out, size_t ro...` |
| `sb_esc` | function | `src/prefs.c:400` | `static void sb_esc(sbuf *b, const char *s)` |
| `sb_link_item` | function | `src/prefs.c:413` | `static void sb_link_item(sbuf *b, const char *url, const char *label)` |
| `sb_put` | function | `src/prefs.c:382` | `static void sb_put(sbuf *b, const char *s, size_t n)` |
| `sb_str` | function | `src/prefs.c:397` | `static void sb_str(sbuf *b, const char *s)` |
| `sbuf` | struct | `src/prefs.c:380` | `` |
| `sugg_push` | function | `src/prefs.c:348` | `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,                       cons...` |
| `title_clean` | function | `src/prefs.c:39` | `static char *title_clean(const char *src)` |
| `url_prefix_match` | function | `src/prefs.c:336` | `static int url_prefix_match(const char *url, const char *q)` |
| `url_valid` | function | `src/prefs.c:26` | `static int url_valid(const char *url)` |
| `PH_PER_MILLE_MAX` | macro | `src/pres_hints.c:8` | `#define PH_PER_MILLE_MAX` |
| `ph_align` | function | `src/pres_hints.c:53` | `static css_align ph_align(ph_attr_fn get, void *ctx)` |
| `ph_apply` | function | `src/pres_hints.c:93` | `void ph_apply(const char *tag, ph_attr_fn get, void *ctx, unsigned flags, css_style *cs)` |
| `ph_bgcolor` | function | `src/pres_hints.c:81` | `static void ph_bgcolor(ph_attr_fn get, void *ctx, css_style *cs)` |
| `ph_cell_padding` | function | `src/pres_hints.c:164` | `void ph_cell_padding(int cellpad, css_style *cs)` |
| `ph_ci_eq` | function | `src/pres_hints.c:42` | `static int ph_ci_eq(const char *s, size_t len, const char *word)` |
| `ph_is_heading` | function | `src/pres_hints.c:76` | `static int ph_is_heading(const char *tag)` |
| `ph_is_space` | function | `src/pres_hints.c:10` | `static int ph_is_space(char c)` |
| `ph_parse_dimension` | function | `src/pres_hints.c:14` | `int ph_parse_dimension(const char *s, size_t len, int *px, int *per_mille)` |
| `ph_parse_nonneg` | function | `src/pres_hints.c:140` | `int ph_parse_nonneg(const char *s, size_t len, int *out)` |
| `ph_table_cellpadding` | function | `src/pres_hints.c:156` | `int ph_table_cellpadding(ph_attr_fn get, void *ctx)` |
| `ph_width` | function | `src/pres_hints.c:64` | `static void ph_width(ph_attr_fn get, void *ctx, css_style *cs)` |
| `PROFILE_KEYFILE_LEN` | macro | `src/profile.c:27` | `#define PROFILE_KEYFILE_LEN` |
| `_POSIX_C_SOURCE` | macro | `src/profile.c:11` | `#define _POSIX_C_SOURCE` |
| `join_path` | function | `src/profile.c:29` | `static int join_path(const profile_ctx *ctx, const char *name,                      char *out, si...` |
| `keyfile_create` | function | `src/profile.c:36` | `static profile_status keyfile_create(const char *dir, const char *path,                          ...` |
| `map_ds` | function | `src/profile.c:98` | `static profile_status map_ds(ds_status ds)` |
| `profile_close` | function | `src/profile.c:149` | `void profile_close(profile_ctx *ctx)` |
| `profile_load` | function | `src/profile.c:112` | `profile_status profile_load(const profile_ctx *ctx, prefs_state *out)` |
| `profile_open` | function | `src/profile.c:59` | `profile_status profile_open(profile_ctx *ctx, const char *dir)` |
| `profile_save` | function | `src/profile.c:133` | `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p)` |
| `place` | function | `src/render_doc.c:240` | `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never...` |
| `rd_at` | function | `src/render_doc.c:768` | `const rd_block *rd_at(const rd_doc *d, size_t i)` |
| `rd_block_heading_level` | function | `src/render_doc.c:805` | `int rd_block_heading_level(const rd_block *b)` |
| `rd_block_tag` | function | `src/render_doc.c:816` | `const char *rd_block_tag(const rd_block *b)` |
| `rd_box_at` | function | `src/render_doc.c:777` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)` |
| `rd_box_count` | function | `src/render_doc.c:773` | `size_t rd_box_count(const rd_doc *d)` |
| `rd_build` | function | `src/render_doc.c:293` | `rd_status rd_build(const pv_view *view, rdp_caps caps,                    const char *top_level_u...` |
| `rd_cont_at` | function | `src/render_doc.c:786` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)` |
| `rd_cont_count` | function | `src/render_doc.c:782` | `size_t rd_cont_count(const rd_doc *d)` |
| `rd_count` | function | `src/render_doc.c:764` | `size_t rd_count(const rd_doc *d)` |
| `rd_free` | function | `src/render_doc.c:747` | `void rd_free(rd_doc *d)` |
| `rd_image_fail_label` | function | `src/render_doc.c:882` | `const char *rd_image_fail_label(img_fail_reason reason)` |
| `rd_image_label` | function | `src/render_doc.c:871` | `const char *rd_image_label(rdp_img_decision d)` |
| `rd_input_invisible` | function | `src/render_doc.c:867` | `int rd_input_invisible(int input_type)` |
| `rd_input_label` | function | `src/render_doc.c:847` | `const char *rd_input_label(int input_type)` |
| `rd_kind_name` | function | `src/render_doc.c:791` | `const char *rd_kind_name(rd_kind k)` |
| `rd_push` | function | `src/render_doc.c:60` | `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,                  ...` |
| `rd_push_input` | function | `src/render_doc.c:214` | `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` |
| `resolve_image_decision` | function | `src/render_doc.c:250` | `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,         ...` |
| `too` | function | `src/render_doc.c:281` | `* that would not fit is cleared too (never truncated-and-fetched). */ static void gate_box_image_...` |
| `unset` | function | `src/render_doc.c:709` | `* background paints as if unset (no border/box-shadow-style * "broken image" placeholder) -- it is decoration, not...` |
| `utf8_sanitized_dup` | function | `src/render_doc.c:28` | `static char *utf8_sanitized_dup(const char *s)` |
| `rdp_caps_safe` | function | `src/render_policy.c:17` | `rdp_caps rdp_caps_safe(void)` |
| `rdp_image_decision` | function | `src/render_policy.c:28` | `rdp_img_decision rdp_image_decision(rdp_caps caps,                                     const char...` |
| `rdp_images_warning` | function | `src/render_policy.c:71` | `const char *rdp_images_warning(void)` |
| `rdp_img_reason` | function | `src/render_policy.c:60` | `const char *rdp_img_reason(rdp_img_decision d)` |
| `rdp_is_tracking_pixel` | function | `src/render_policy.c:22` | `int rdp_is_tracking_pixel(int w, int h)` |
| `_POSIX_C_SOURCE` | macro | `src/renderer.c:7` | `#define _POSIX_C_SOURCE` |
| `child_render` | function | `src/renderer.c:25` | `static void child_render(int wfd, const char *html, size_t len)` |
| `rd_render_html` | function | `src/renderer.c:70` | `rd_status rd_render_html(const char *html, size_t len, rd_result *out)` |
| `rd_result_free` | function | `src/renderer.c:120` | `void rd_result_free(rd_result *out)` |
| `read_field` | function | `src/renderer.c:53` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `write_full` | function | `src/renderer.c:40` | `&& write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 \|\| write_full(wfd, title, tl) == 0) && write_full(wfd, &xl...` |
| `RP_MAX_HOST` | macro | `src/request_policy.c:17` | `#define RP_MAX_HOST` |
| `RP_MAX_LABELS` | macro | `src/request_policy.c:18` | `#define RP_MAX_LABELS` |
| `ci_starts_with` | function | `src/request_policy.c:26` | `static int ci_starts_with(const char *s, const char *prefix)` |
| `hdr_forbidden` | function | `src/request_policy.c:184` | `static int hdr_forbidden(const char *n, size_t len)` |
| `hdr_lower` | function | `src/request_policy.c:162` | `static int hdr_lower(int c)` |
| `hdr_name_has_prefix` | function | `src/request_policy.c:171` | `static int hdr_name_has_prefix(const char *a, size_t alen, const char *lit)` |
| `hdr_name_ieq` | function | `src/request_policy.c:164` | `static int hdr_name_ieq(const char *a, size_t alen, const char *lit)` |
| `hdr_token_char` | function | `src/request_policy.c:178` | `static int hdr_token_char(unsigned char c)` |
| `lower` | function | `src/request_policy.c:22` | `static char lower(char c)` |
| `psl_cmp` | function | `src/request_policy.c:36` | `static int psl_cmp(const void *key, const void *elem)` |
| `psl_in` | function | `src/request_policy.c:40` | `static int psl_in(const char *const *arr, size_t n, const char *key)` |
| `public_suffix_labels` | function | `src/request_policy.c:48` | `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)` |
| `rp_evaluate` | function | `src/request_policy.c:143` | `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)` |
| `rp_host_of` | function | `src/request_policy.c:76` | `int rp_host_of(const char *url, char *out, size_t out_size)` |
| `rp_same_site` | function | `src/request_policy.c:134` | `int rp_same_site(const char *top_level_url, const char *request_url)` |
| `rp_sanitize_request_headers` | function | `src/request_policy.c:197` | `int rp_sanitize_request_headers(const char *raw, char *out, size_t cap)` |
| `rp_site_of` | function | `src/request_policy.c:102` | `int rp_site_of(const char *host, char *out, size_t out_size)` |
| `clamp_coord` | function | `src/scroll_req.c:10` | `static int32_t clamp_coord(double v)` |
| `clamp_count` | function | `src/scroll_req.c:17` | `static int32_t clamp_count(size_t n)` |
| `coord_ok` | function | `src/scroll_req.c:33` | `static int coord_ok(int32_t v)` |
| `element_scroll` | function | `src/scroll_req.c:60` | `static double element_scroll(int block, double cur, double h, double pt, double pb,              ...` |
| `srq_decode` | function | `src/scroll_req.c:37` | `int srq_decode(const int32_t in[SRQ_WIRE_N], size_t max_handles, srq_req *out)` |
| `srq_encode` | function | `src/scroll_req.c:21` | `void srq_encode(const srq_req *r, int32_t out[SRQ_WIRE_N])` |
| `srq_smooth` | function | `src/scroll_req.c:110` | `int srq_smooth(const srq_req *r, int root_smooth)` |
| `srq_target` | function | `src/scroll_req.c:80` | `int srq_target(const srq_req *r, const srq_view *v, double el_top, double el_bottom,             ...` |
| `SF_GUARD_HOST_MAX` | macro | `src/secure_fetch.c:522` | `#define SF_GUARD_HOST_MAX` |
| `SF_RCACHE_SLOTS` | macro | `src/secure_fetch.c:1273` | `#define SF_RCACHE_SLOTS` |
| `SF_RCACHE_TTL_S` | macro | `src/secure_fetch.c:1274` | `#define SF_RCACHE_TTL_S` |
| `_POSIX_C_SOURCE` | macro | `src/secure_fetch.c:12` | `#define _POSIX_C_SOURCE` |
| `add_header` | function | `src/secure_fetch.c:903` | `static int add_header(struct curl_slist **h, const char *line)` |
| `body_sink` | struct | `src/secure_fetch.c:499` | `` |
| `ci_index` | function | `src/secure_fetch.c:61` | `static long ci_index(const char *haystack, const char *needle)` |
| `ci_starts_with` | function | `src/secure_fetch.c:49` | `static int ci_starts_with(const char *haystack, const char *prefix)` |
| `copy_bounded` | function | `src/secure_fetch.c:548` | `static void copy_bounded(char *dst, size_t dstsz, const char *src)` |
| `copy_checked` | function | `src/secure_fetch.c:361` | `static int copy_checked(char *dst, size_t dstsz, const char *src)` |
| `database` | function | `src/secure_fetch.c:563` | `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid...` |
| `fetch_ctx` | struct | `src/secure_fetch.c:524` | `` |
| `get_negotiated_group_name` | function | `src/secure_fetch.c:559` | `static const char *get_negotiated_group_name(SSL *ssl)` |
| `group` | function | `src/secure_fetch.c:577` | `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);` |
| `header_cb` | function | `src/secure_fetch.c:628` | `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` |
| `header_value_clean` | function | `src/secure_fetch.c:267` | `static int header_value_clean(const char *s)` |
| `inspect_chain` | function | `src/secure_fetch.c:727` | `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` |
| `module` | function | `src/secure_fetch.c:422` | `* pure url module (DRY);` |
| `name_is_pq_sig` | function | `src/secure_fetch.c:717` | `static int name_is_pq_sig(int pknid)` |
| `progress` | function | `src/secure_fetch.c:508` | `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);` |
| `rcache_put_ram` | function | `src/secure_fetch.c:1306` | `static int rcache_put_ram(const char *from, const char *to, time_t now)` |
| `redirect` | function | `src/secure_fetch.c:999` | `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a      * different orig...` |
| `refused` | function | `src/secure_fetch.c:785` | `* a private peer is then refused (fail closed). */ static void sf_guard_init(fetch_ctx *ctx, cons...` |
| `sf_accept_language_or_default` | function | `src/secure_fetch.c:277` | `const char *sf_accept_language_or_default(const char *lang)` |
| `sf_attempt_get` | function | `src/secure_fetch.c:1627` | `static sf_status sf_attempt_get(const char *url, const sf_config *cfg, sf_response *out,         ...` |
| `sf_attempt_post` | function | `src/secure_fetch.c:1633` | `static sf_status sf_attempt_post(const char *url, const sf_config *cfg, sf_response *out,        ...` |
| `sf_check_chain_policy` | function | `src/secure_fetch.c:320` | `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)` |
| `sf_check_group_is_pq` | function | `src/secure_fetch.c:311` | `sf_status sf_check_group_is_pq(const char *negotiated_group)` |
| `sf_check_tls_version` | function | `src/secure_fetch.c:306` | `sf_status sf_check_tls_version(const char *negotiated_version)` |
| `sf_ci_prefix` | function | `src/secure_fetch.c:429` | `static int sf_ci_prefix(const char *s, const char *p)` |
| `sf_config_default` | function | `src/secure_fetch.c:238` | `sf_config sf_config_default(void)` |
| `sf_cookie_header_for` | function | `src/secure_fetch.c:188` | `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)` |
| `sf_cookie_line_matches` | function | `src/secure_fetch.c:118` | `int sf_cookie_line_matches(const char *line, const char *host, const char *path,                 ...` |
| `sf_cookie_put` | function | `src/secure_fetch.c:217` | `void sf_cookie_put(const char *url, const char *namevalue)` |
| `sf_downgrade_of` | function | `src/secure_fetch.c:1618` | `static int sf_downgrade_of(sf_policy p)` |
| `sf_enforce_policy` | function | `src/secure_fetch.c:330` | `sf_status sf_enforce_policy(const char *tls_version, const char *group,                          ...` |
| `sf_fallback_policy` | function | `src/secure_fetch.c:1597` | `int sf_fallback_policy(sf_status failed, sf_policy tried, int allowlisted, sf_policy *next)` |
| `sf_get` | function | `src/secure_fetch.c:1253` | `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)` |
| `sf_get_follow` | function | `src/secure_fetch.c:1364` | `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,                 ...` |
| `sf_get_follow_navigable` | function | `src/secure_fetch.c:1658` | `sf_status sf_get_follow_navigable(const char *url, sf_config *cfg, sf_response *out,             ...` |
| `sf_global_init` | function | `src/secure_fetch.c:90` | `void sf_global_init(void)` |
| `sf_guard_opensocket` | function | `src/secure_fetch.c:812` | `static curl_socket_t sf_guard_opensocket(void *clientp, curlsocktype purpose,                    ...` |
| `sf_guard_prereq` | function | `src/secure_fetch.c:839` | `static int sf_guard_prereq(void *clientp, char *conn_primary_ip, char *conn_local_ip,            ...` |
| `sf_header_value` | function | `src/secure_fetch.c:377` | `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz)` |
| `sf_impersonate_kex_groups` | function | `src/secure_fetch.c:281` | `const char *sf_impersonate_kex_groups(void)` |
| `sf_impersonate_tls13_ciphers` | function | `src/secure_fetch.c:282` | `const char *sf_impersonate_tls13_ciphers(void)` |
| `sf_is_redirect_code` | function | `src/secure_fetch.c:370` | `int sf_is_redirect_code(long http_code)` |
| `sf_navigable` | function | `src/secure_fetch.c:1638` | `static sf_status sf_navigable(sf_attempt_fn attempt, const char *url, sf_config *cfg,            ...` |
| `sf_parse_location_header` | function | `src/secure_fetch.c:399` | `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)` |
| `sf_perform` | function | `src/secure_fetch.c:1091` | `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,             ...` |
| `sf_post` | function | `src/secure_fetch.c:1257` | `sf_status sf_post(const char *url, const sf_config *cfg,                   const void *body, size...` |
| `sf_post_navigable` | function | `src/secure_fetch.c:1663` | `sf_status sf_post_navigable(const char *url, sf_config *cfg, const void *body,                   ...` |
| `sf_rcache_clear` | function | `src/secure_fetch.c:1287` | `void sf_rcache_clear(void)` |
| `sf_rcache_entry` | struct | `src/secure_fetch.c:1276` | `` |
| `sf_rcache_get` | function | `src/secure_fetch.c:1335` | `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap)` |
| `sf_rcache_put` | function | `src/secure_fetch.c:1325` | `int sf_rcache_put(const char *from, const char *to, time_t now)` |
| `sf_rcache_set_backing` | function | `src/secure_fetch.c:1298` | `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx)` |
| `sf_resolve_redirect` | function | `src/secure_fetch.c:417` | `sf_status sf_resolve_redirect(const char *base_url, const char *location,                        ...` |
| `sf_response_free` | function | `src/secure_fetch.c:469` | `void sf_response_free(sf_response *resp)` |
| `sf_setup_handle` | function | `src/secure_fetch.c:917` | `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,            ...` |
| `sf_share_lock` | function | `src/secure_fetch.c:77` | `static void sf_share_lock(CURL *handle, curl_lock_data data,                           curl_lock_...` |
| `sf_share_unlock` | function | `src/secure_fetch.c:83` | `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)` |
| `sf_url_host_path` | function | `src/secure_fetch.c:173` | `static int sf_url_host_path(const char *url, char *host, size_t hostsz,                          ...` |
| `sf_url_is_http` | function | `src/secure_fetch.c:294` | `static int sf_url_is_http(const char *url)` |
| `sf_user_agent_or_default` | function | `src/secure_fetch.c:273` | `const char *sf_user_agent_or_default(const char *ua)` |
| `sf_validate_url` | function | `src/secure_fetch.c:286` | `sf_status sf_validate_url(const char *url)` |
| `sf_ws` | struct | `src/secure_fetch.c:1450` | `` |
| `sf_ws_close` | function | `src/secure_fetch.c:1586` | `void sf_ws_close(sf_ws *ws)` |
| `sf_ws_fd` | function | `src/secure_fetch.c:1579` | `int sf_ws_fd(const sf_ws *ws)` |
| `sf_ws_open` | function | `src/secure_fetch.c:1478` | `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)` |
| `sf_ws_recv` | function | `src/secure_fetch.c:1557` | `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)` |
| `sf_ws_send` | function | `src/secure_fetch.c:1534` | `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)` |
| `sf_ws_url_check` | function | `src/secure_fetch.c:1457` | `sf_status sf_ws_url_check(const char *url)` |
| `sink` | type_alias | `src/secure_fetch.c:523` | `typedef struct fetch_ctx { body_sink sink;` |
| `this` | function | `src/secure_fetch.c:609` | `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and...` |
| `tls_capture` | struct | `src/secure_fetch.c:512` | `` |
| `tls_capture_from_ssl` | function | `src/secure_fetch.c:602` | `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)` |
| `tls_capture_try` | function | `src/secure_fetch.c:592` | `static void tls_capture_try(tls_capture *cap)` |
| `write_cb` | function | `src/secure_fetch.c:685` | `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)` |
| `ws_free` | function | `src/secure_fetch.c:1469` | `static void ws_free(sf_ws *ws)` |
| `ws_ssl_ctx_cb` | function | `src/secure_fetch.c:1443` | `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)` |
| `ws_ssl_info_cb` | function | `src/secure_fetch.c:1436` | `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)` |
| `ROL32` | macro | `src/sha2.c:9` | `#define ROL32(x, n)` |
| `ROR32` | macro | `src/sha2.c:8` | `#define ROR32(x, n)` |
| `ROR64` | macro | `src/sha2.c:10` | `#define ROR64(x, n)` |
| `be32` | function | `src/sha2.c:40` | `static uint32_t be32(const uint8_t *p)` |
| `be64` | function | `src/sha2.c:43` | `static uint64_t be64(const uint8_t *p)` |
| `ieq` | function | `src/sha2.c:22` | `static int ieq(const char *a, const char *b)` |
| `pad_tail` | function | `src/sha2.c:49` | `static size_t pad_tail(uint8_t *blk, size_t bs, size_t lenbytes, const uint8_t *tail, size_t tl, ...` |
| `put32` | function | `src/sha2.c:44` | `static void put32(uint8_t *p, uint32_t v)` |
| `put64` | function | `src/sha2.c:45` | `static void put64(uint8_t *p, uint64_t v)` |
| `sha1_block` | function | `src/sha2.c:61` | `static void sha1_block(uint32_t h[5], const uint8_t *p)` |
| `sha256_block` | function | `src/sha2.c:88` | `static void sha256_block(uint32_t h[8], const uint8_t *p)` |
| `sha512_block` | function | `src/sha2.c:131` | `static void sha512_block(uint64_t h[8], const uint8_t *p)` |
| `sha_alg_from_name` | function | `src/sha2.c:31` | `int sha_alg_from_name(const char *name, sha_alg *out)` |
| `sha_digest` | function | `src/sha2.c:152` | `int sha_digest(sha_alg alg, const void *data, size_t len, uint8_t *out)` |
| `sha_digest_len` | function | `src/sha2.c:12` | `size_t sha_digest_len(sha_alg alg)` |
| `shc_acquire` | function | `src/sheet_cache.c:155` | `shc_sheet *shc_acquire(shc_cache *cache, const shc_key *key)` |
| `shc_cache` | struct | `src/sheet_cache.c:30` | `` |
| `shc_css` | function | `src/sheet_cache.c:107` | `const css_sheet *shc_css(const shc_sheet *s)` |
| `shc_dup` | function | `src/sheet_cache.c:72` | `static char *shc_dup(const char *src, size_t len)` |
| `shc_free` | function | `src/sheet_cache.c:101` | `void shc_free(shc_cache *c)` |
| `shc_key_matches` | function | `src/sheet_cache.c:117` | `static int shc_key_matches(const shc_sheet *s, const shc_key *k)` |
| `shc_key_store` | function | `src/sheet_cache.c:136` | `static int shc_key_store(shc_sheet *s, const shc_key *k)` |
| `shc_new` | function | `src/sheet_cache.c:89` | `shc_cache *shc_new(size_t max_text_bytes)` |
| `shc_probe` | struct | `src/sheet_cache.c:39` | `` |
| `shc_probe_match` | function | `src/sheet_cache.c:47` | `static int shc_probe_match(void *ctx, const struct css_sel *sel)` |
| `shc_queries_free` | function | `src/sheet_cache.c:67` | `static void shc_queries_free(shc_query *q, size_t n)` |
| `shc_query` | struct | `src/sheet_cache.c:12` | `` |
| `shc_release` | function | `src/sheet_cache.c:96` | `void shc_release(shc_sheet *s)` |
| `shc_sheet` | struct | `src/sheet_cache.c:17` | `` |
| `shc_sheet_destroy` | function | `src/sheet_cache.c:81` | `static void shc_sheet_destroy(shc_sheet *s)` |
| `shc_stats_get` | function | `src/sheet_cache.c:111` | `void shc_stats_get(const shc_cache *c, shc_stats *out)` |
| `sms_active` | function | `src/smooth_scroll.c:64` | `int sms_active(const sms_state *s)` |
| `sms_goal` | function | `src/smooth_scroll.c:59` | `double sms_goal(const sms_state *s)` |
| `sms_init` | function | `src/smooth_scroll.c:7` | `void sms_init(sms_state *s, double pos)` |
| `sms_jump` | function | `src/smooth_scroll.c:15` | `void sms_jump(sms_state *s, double pos)` |
| `sms_retarget` | function | `src/smooth_scroll.c:21` | `void sms_retarget(sms_state *s, double target, double now_ms, double dur_ms)` |
| `sms_sample` | function | `src/smooth_scroll.c:35` | `double sms_sample(sms_state *s, double now_ms)` |
| `_GNU_SOURCE` | macro | `src/subreq_batch.c:2` | `#define _GNU_SOURCE` |
| `all_done_locked` | function | `src/subreq_batch.c:164` | `static int all_done_locked(const sqb *b)` |
| `batch_destroy` | function | `src/subreq_batch.c:58` | `static void batch_destroy(sqb *b)` |
| `dup_n` | function | `src/subreq_batch.c:37` | `static char *dup_n(const char *s, size_t n)` |
| `job_free` | function | `src/subreq_batch.c:51` | `static void job_free(sqb_job *j)` |
| `job_main` | function | `src/subreq_batch.c:65` | `static void *job_main(void *arg)` |
| `res_clear` | function | `src/subreq_batch.c:46` | `static void res_clear(sqb_res *r)` |
| `sqb` | struct | `src/subreq_batch.c:23` | `` |
| `sqb_abandon` | function | `src/subreq_batch.c:224` | `void sqb_abandon(sqb *b)` |
| `sqb_count` | function | `src/subreq_batch.c:154` | `size_t sqb_count(const sqb *b)` |
| `sqb_free` | function | `src/subreq_batch.c:247` | `void sqb_free(sqb *b)` |
| `sqb_job` | struct | `src/subreq_batch.c:11` | `` |
| `sqb_new` | function | `src/subreq_batch.c:97` | `sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx)` |
| `sqb_new_owned` | function | `src/subreq_batch.c:101` | `sqb *sqb_new_owned(int max_threads, sqb_run_fn run, void *ctx, void (*free_ctx)(void *))` |
| `sqb_remove` | function | `src/subreq_batch.c:191` | `void sqb_remove(sqb *b, const size_t *idx, size_t k)` |
| `sqb_reset` | function | `src/subreq_batch.c:217` | `void sqb_reset(sqb *b)` |
| `sqb_result` | function | `src/subreq_batch.c:213` | `const sqb_res *sqb_result(const sqb *b, size_t i)` |
| `sqb_submit` | function | `src/subreq_batch.c:127` | `int sqb_submit(sqb *b, int refused, const sqb_req *req)` |
| `sqb_wait_all` | function | `src/subreq_batch.c:156` | `void sqb_wait_all(sqb *b)` |
| `sqb_wait_ready` | function | `src/subreq_batch.c:169` | `size_t sqb_wait_ready(sqb *b, long wait_ms, size_t *idx, size_t cap)` |
| `svp_alpha` | function | `src/svg_paint.c:31` | `static double svp_alpha(int opacity, int paint_opacity)` |
| `svp_draw` | function | `src/svg_paint.c:139` | `void svp_draw(cairo_t *cr, const sv_image *img,               double x, double y, double w, doubl...` |
| `svp_draw_ex` | function | `src/svg_paint.c:144` | `void svp_draw_ex(cairo_t *cr, const sv_image *img,                  double x, double y, double w,...` |
| `svp_draw_text` | function | `src/svg_paint.c:126` | `static void svp_draw_text(cairo_t *cr, const sv_shape *sh, int current_rgb)` |
| `svp_rect_path` | function | `src/svg_paint.c:38` | `static void svp_rect_path(cairo_t *cr, const sv_shape *sh)` |
| `svp_shape_path` | function | `src/svg_paint.c:73` | `static void svp_shape_path(cairo_t *cr, const sv_image *img, const sv_shape *sh)` |
| `sr_rasterize` | function | `src/svg_raster.c:50` | `img_status sr_rasterize(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `sr_skip_past` | function | `src/svg_raster.c:18` | `static size_t sr_skip_past(const uint8_t *b, size_t i, size_t n, const char *end)` |
| `sr_sniff` | function | `src/svg_raster.c:25` | `int sr_sniff(const uint8_t *bytes, size_t len)` |
| `sr_ws` | function | `src/svg_raster.c:14` | `static int sr_ws(uint8_t c)` |
| `SV_MAX_ATTRS` | macro | `src/svg_render.c:96` | `#define SV_MAX_ATTRS` |
| `point` | function | `src/svg_render.c:567` | `* current point (SVG 8.3.6). */ int had = (prev == 'C' \|\| prev == 'c' \|\| prev == 'S' \|\| prev == 's');` |
| `stroke` | type_alias | `src/svg_render.c:151` | `typedef struct sv_ctx { int fill, stroke;` |
| `sv_apply_prop` | function | `src/svg_render.c:260` | `static void sv_apply_prop(sv_ctx *ctx, const char *nm, size_t nl,                           const...` |
| `sv_arc_to_cubics` | function | `src/svg_render.c:399` | `static int sv_arc_to_cubics(sv_image *im, sv_shape *sh,                             double x0, do...` |
| `sv_attr` | struct | `src/svg_render.c:91` | `` |
| `sv_attr_get` | function | `src/svg_render.c:99` | `static const char *sv_attr_get(const sv_attr *at, size_t nat, const char *name, size_t *len)` |

Next: [SYMBOLS_p12.md](SYMBOLS_p12.md)
