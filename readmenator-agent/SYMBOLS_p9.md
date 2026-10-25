# Symbols (page 9 of 15)
Previous: [SYMBOLS_p8.md](SYMBOLS_p8.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `os_isolate_namespaces` | function | `src/os_sandbox.c:116` | `os_status os_isolate_namespaces(void)` |
| `os_landlock_abi` | function | `src/os_sandbox.c:285` | `int os_landlock_abi(void)` |
| `os_landlock_abi` | function | `src/os_sandbox.c:331` | `int os_landlock_abi(void)` |
| `os_landlock_restrict` | function | `src/os_sandbox.c:291` | `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)` |
| `os_landlock_restrict` | function | `src/os_sandbox.c:332` | `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)` |
| `os_namespace_flags` | function | `src/os_sandbox.c:115` | `int os_namespace_flags(void)` |
| `os_no_dump` | function | `src/os_sandbox.c:75` | `os_status os_no_dump(void)` |
| `os_no_dump` | function | `src/os_sandbox.c:111` | `os_status os_no_dump(void)` |
| `os_policy_allows` | function | `src/os_sandbox.c:52` | `int os_policy_allows(long syscall_nr)` |
| `os_policy_allows` | function | `src/os_sandbox.c:106` | `int os_policy_allows(long syscall_nr)` |
| `os_policy_size` | function | `src/os_sandbox.c:59` | `size_t os_policy_size(void)` |
| `os_policy_size` | function | `src/os_sandbox.c:107` | `size_t os_policy_size(void)` |
| `os_prot_allowed` | function | `src/os_sandbox.c:65` | `int os_prot_allowed(long syscall_nr, unsigned long prot)` |
| `os_prot_allowed` | function | `src/os_sandbox.c:108` | `int os_prot_allowed(long syscall_nr, unsigned long prot)` |
| `PV_COLOR_TOKEN_MAX` | macro | `src/page_view.c:1207` | `#define PV_COLOR_TOKEN_MAX` |
| `PV_FONT_CHAIN_MAX` | macro | `src/page_view.c:64` | `#define PV_FONT_CHAIN_MAX` |
| `PV_FONT_PCT_MAX` | macro | `src/page_view.c:66` | `#define PV_FONT_PCT_MAX` |
| `PV_FONT_PCT_MIN` | macro | `src/page_view.c:65` | `#define PV_FONT_PCT_MIN` |
| `PV_FONT_REL_MAX` | macro | `src/page_view.c:58` | `#define PV_FONT_REL_MAX` |
| `PV_FONT_REL_MIN` | macro | `src/page_view.c:57` | `#define PV_FONT_REL_MIN` |
| `PV_MAX_BOXES` | macro | `src/page_view.c:1254` | `#define PV_MAX_BOXES` |
| `PV_MAX_CONTAINERS` | macro | `src/page_view.c:1245` | `#define PV_MAX_CONTAINERS` |
| `PV_MAX_DIM` | macro | `src/page_view.c:52` | `#define PV_MAX_DIM` |
| `PV_MAX_GRID_COLS` | macro | `src/page_view.c:1246` | `#define PV_MAX_GRID_COLS` |
| `PV_MAX_INLINE_ROW_ITEMS` | macro | `src/page_view.c:2836` | `#define PV_MAX_INLINE_ROW_ITEMS` |
| `PV_MAX_STYLE_BYTES` | macro | `src/page_view.c:4977` | `#define PV_MAX_STYLE_BYTES` |
| `PV_NODE_MAP_INIT_CAP` | macro | `src/page_view.c:346` | `#define PV_NODE_MAP_INIT_CAP` |
| `PV_STYLE_RETIRE_MAX` | macro | `src/page_view.c:2248` | `#define PV_STYLE_RETIRE_MAX` |
| `PV_TEXTLESS_DEPTH_MAX` | macro | `src/page_view.c:3151` | `#define PV_TEXTLESS_DEPTH_MAX` |
| `URL` | function | `src/page_view.c:6218` | `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `_POSIX_C_SOURCE` | macro | `src/page_view.c:10` | `#define _POSIX_C_SOURCE` |
| `address` | function | `src/page_view.c:1257` | `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <=...` |
| `annotate_flow_run` | function | `src/page_view.c:1814` | `static void annotate_flow_run(pv_view *v, pv_container_reg *reg, pv_item_track *items,           ...` |
| `annotate_replaced_run` | function | `src/page_view.c:5113` | `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,                             ...` |
| `ascii_ieq` | function | `src/page_view.c:4395` | `static int ascii_ieq(const char *s, const char *lit)` |
| `attr_dup` | function | `src/page_view.c:4407` | `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)` |
| `attributes` | function | `src/page_view.c:4329` | `* carries those attributes (spec/css.md, "Root matcher"). */ static int root_els_match(void *ctx,...` |
| `band` | function | `src/page_view.c:5909` | `* run: without its float annotation it cut the band (the icon row of a * `float:right` social list became one float...` |
| `bgcolor_attr` | function | `src/page_view.c:1235` | `static int bgcolor_attr(lxb_dom_element_t *el)` |
| `block` | function | `src/page_view.c:6506` | `* block (Gecko): it never resolves as its own block here. */ int opens_line = block != n && (pending_break \|\| block...` |
| `block_id` | function | `src/page_view.c:6077` | `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it...` |
| `box_reg_free` | function | `src/page_view.c:1885` | `static void box_reg_free(pv_box_reg *r)` |
| `box_reg_id` | function | `src/page_view.c:2142` | `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,            ...` |
| `box_reg_id_ex` | function | `src/page_view.c:2647` | `static int box_reg_id_ex(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,         ...` |
| `boxdef_from_style` | function | `src/page_view.c:1894` | `static void boxdef_from_style(pv_box_def *d, const css_style *cs)` |
| `builder` | function | `src/page_view.c:2750` | `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box  * (the ...` |
| `cached_element_style` | function | `src/page_view.c:2569` | `static css_style cached_element_style(lxb_dom_element_t *el, const css_sheet *sheet,             ...` |
| `cached_element_style_ref` | function | `src/page_view.c:2500` | `static const css_style *cached_element_style_ref(lxb_dom_element_t *el, const css_sheet *sheet,  ...` |
| `cached_pseudo_style` | function | `src/page_view.c:2685` | `static css_style cached_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet,              ...` |
| `causes_block_break` | function | `src/page_view.c:1091` | `static int causes_block_break(lxb_tag_id_t t, css_display display)` |
| `cell_anchors` | function | `src/page_view.c:4872` | `static const lxb_dom_node_t *cell_anchors(const lxb_dom_node_t *cell, int *count)` |
| `cell_has_nested_table` | function | `src/page_view.c:4852` | `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)` |
| `chain` | type_alias | `src/page_view.c:2234` | `typedef struct pv_var_node { cvr_chain chain;` |
| `child` | function | `src/page_view.c:1265` | `* child (NULL = anonymous item: text directly inside the container);` |
| `children_all_inline_block` | function | `src/page_view.c:2864` | `static int children_all_inline_block(const lxb_dom_node_t *p, const css_sheet *sheet,            ...` |
| `classify_input` | function | `src/page_view.c:4489` | `static pv_input_type classify_input(const char *type)` |
| `col_free_share` | function | `src/page_view.c:2630` | `static int col_free_share(const lxb_dom_node_t *el, const css_style *cs, const css_sheet *sheet, pv_style_cache...` |
| `col_has_free_space` | function | `src/page_view.c:2889` | `static int col_has_free_space(const css_style *cs)` |
| `collapse_ws` | function | `src/page_view.c:4088` | `static char *collapse_ws(const char *s, size_t n)` |
| `collect_page_css` | function | `src/page_view.c:5196` | `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,                      ...` |
| `collect_text` | function | `src/page_view.c:4465` | `static char *collect_text(const lxb_dom_node_t *el)` |
| `cols` | type_alias | `src/page_view.c:1267` | `typedef struct pv_cont_info { int id, display, gap, justify, cols;` |
| `column_gap_candidate` | function | `src/page_view.c:2978` | `static int column_gap_candidate(const lxb_dom_node_t *el, const css_sheet *sheet,                ...` |
| `cont_def_reset` | function | `src/page_view.c:1707` | `static void cont_def_reset(pv_cont_def *d)` |
| `container` | function | `src/page_view.c:3778` | `* membership in this container (and none in any container further out,                  * since i...` |
| `container_id` | function | `src/page_view.c:1726` | `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)` |
| `content` | function | `src/page_view.c:1189` | `* a <noscript> ancestor also suppresses content (the script would run, so the * fallback is hidden);` |
| `control` | function | `src/page_view.c:5667` | `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);` |
| `cp1252_to_ucs` | function | `src/page_view.c:90` | `static unsigned int cp1252_to_ucs(unsigned char c)` |
| `css_has_boxdeco` | function | `src/page_view.c:1563` | `static int css_has_boxdeco(const css_style *cs)` |
| `css_has_hbox` | function | `src/page_view.c:1484` | `static int css_has_hbox(const css_style *cs)` |
| `css_has_hmargin` | function | `src/page_view.c:3014` | `static int css_has_hmargin(const css_style *cs)` |
| `css_has_position` | function | `src/page_view.c:1558` | `static int css_has_position(const css_style *cs)` |
| `css_hbox_resolve` | function | `src/page_view.c:1505` | `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)` |
| `css_inline_boxdeco` | function | `src/page_view.c:3615` | `css_inline_boxdeco(cs) &&                            !is_layout_item(p, sheet, style_cache))` |
| `css_replaced_h_fixed` | function | `src/page_view.c:2732` | `static int css_replaced_h_fixed(lxb_dom_element_t *el, const css_sheet *sheet,                   ...` |
| `css_to_fx_justify` | function | `src/page_view.c:2779` | `static int css_to_fx_justify(css_justify j)` |
| `dimensions` | function | `src/page_view.c:4270` | `* viewport dimensions (data: inline detection, <picture> <source> scanning). */ static void srcse...` |
| `dup_n` | function | `src/page_view.c:151` | `static char *dup_n(const char *s, size_t n)` |
| `element_is_content_leaf` | function | `src/page_view.c:3242` | `static int element_is_content_leaf(const lxb_dom_node_t *n, const css_sheet *sheet,              ...` |
| `element_is_content_leaf_d` | function | `src/page_view.c:3202` | `static int element_is_content_leaf_d(const lxb_dom_node_t *n, const css_sheet *sheet,            ...` |
| `engine` | function | `src/page_view.c:6782` | `* layout engine (contiguous item gather) drops every cell onto its own row and          * a 2-col...` |
| `find_body` | function | `src/page_view.c:4302` | `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)` |
| `find_root_els` | function | `src/page_view.c:4315` | `static pv_root_els find_root_els(lxb_dom_node_t *root)` |
| `flex_column_flows_as_block` | function | `src/page_view.c:2900` | `static int flex_column_flows_as_block(const lxb_dom_node_t *el, const css_style *cs,             ...` |
| `float` | function | `src/page_view.c:4001` | `* genuinely nested float (oid != id) takes the deferred-column path. */     if (cont->float_oid =...` |
| `flow` | function | `src/page_view.c:6676` | `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through...` |
| `flow_table` | function | `src/page_view.c:4911` | `static int flow_table(pv_flow_reg *fr, const lxb_dom_node_t *table)` |
| `fold_column_gap` | function | `src/page_view.c:2953` | `static void fold_column_gap(const lxb_dom_node_t *el, css_style *cs,                             ...` |
| `font_color_attr` | function | `src/page_view.c:1229` | `static int font_color_attr(lxb_dom_element_t *el)` |
| `form_for` | function | `src/page_view.c:4436` | `static int form_for(const form_table *ft, const lxb_dom_node_t *n,                     const lxb_...` |
| `form_rec` | struct | `src/page_view.c:4377` | `` |
| `form_table` | struct | `src/page_view.c:4383` | `` |
| `forms_add` | function | `src/page_view.c:4416` | `static int forms_add(form_table *ft, const lxb_dom_node_t *node)` |
| `forms_free` | function | `src/page_view.c:4388` | `static void forms_free(form_table *ft)` |
| `generates_box` | function | `src/page_view.c:1072` | `static int generates_box(lxb_tag_id_t t, css_display display)` |
| `generates_box_style` | function | `src/page_view.c:1084` | `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)` |
| `glyphs` | function | `src/page_view.c:2044` | `* glyphs (the runs carry it as their fill source);` |
| `heading_level` | function | `src/page_view.c:1151` | `static int heading_level(lxb_tag_id_t t)` |
| `height` | function | `src/page_view.c:5936` | `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `here` | function | `src/page_view.c:1996` | `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3...` |
| `id` | function | `src/page_view.c:1289` | `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);` |
| `ignored` | function | `src/page_view.c:671` | `* source is ignored (fail-visible: never invisible text from half a      * pattern). A real text-...` |
| `in_boilerplate_subtree` | function | `src/page_view.c:5048` | `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` |
| `in_closed_details_subtree` | function | `src/page_view.c:5063` | `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` |
| `in_flow_table_cell` | function | `src/page_view.c:4923` | `static int in_flow_table_cell(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,            ...` |
| `in_hidden_subtree` | function | `src/page_view.c:5024` | `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,                ...` |
| `in_mixed_line` | function | `src/page_view.c:2848` | `static int in_mixed_line(const lxb_dom_node_t *p, const css_sheet *sheet,                        ...` |
| `in_skipped_subtree` | function | `src/page_view.c:1192` | `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,               ...` |
| `inherited_text_color` | function | `src/page_view.c:2636` | `static int inherited_text_color(const lxb_dom_node_t *node, const css_sheet *sheet,              ...` |
| `inside` | function | `src/page_view.c:5342` | `* page inside (the top one collapses with the first child's margin), so a * margin-only body stays box-less. */...` |
| `is_block_like` | function | `src/page_view.c:1021` | `static int is_block_like(lxb_tag_id_t t, css_display display)` |
| `is_block_like_style` | function | `src/page_view.c:1060` | `static int is_block_like_style(lxb_tag_id_t t, const css_style *cs)` |
| `is_block_tag` | function | `src/page_view.c:996` | `static int is_block_tag(lxb_tag_id_t t)` |
| `is_bold_tag` | function | `src/page_view.c:2798` | `static int is_bold_tag(lxb_tag_id_t t)` |
| `is_inline_level_style` | function | `src/page_view.c:2840` | `static int is_inline_level_style(lxb_tag_id_t t, const css_style *cs)` |
| `is_italic_tag` | function | `src/page_view.c:2803` | `static int is_italic_tag(lxb_tag_id_t t)` |
| `is_layout_container` | function | `src/page_view.c:2988` | `static int is_layout_container(const lxb_dom_node_t *el, const css_style *cs,                    ...` |
| `is_plain_wrapper` | function | `src/page_view.c:3190` | `static int is_plain_wrapper(const lxb_dom_node_t *c, const css_style *cs)` |
| `is_skipped_tag` | function | `src/page_view.c:1163` | `static int is_skipped_tag(lxb_tag_id_t t)` |
| `it` | function | `src/page_view.c:1386` | `* it (they inherit in CSS). list_style drives the <li> marker (structural);` |
| `item_ordinal` | function | `src/page_view.c:1357` | `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)` |
| `item_sizes_itself` | function | `src/page_view.c:3043` | `static int item_sizes_itself(const lxb_dom_node_t *el, const css_style *cs,                      ...` |
| `li_is_list_item` | function | `src/page_view.c:3059` | `static int li_is_list_item(const lxb_dom_node_t *li, const css_sheet *sheet,                     ...` |
| `li_ordinal` | function | `src/page_view.c:4661` | `static int li_ordinal(const lxb_dom_node_t *li)` |
| `line` | function | `src/page_view.c:6791` | `* to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);` |
| `links` | function | `src/page_view.c:4890` | `* its links (the Hacker News case: every story link lives inside a <td>), so the  * caller flows ...` |
| `list_marker` | function | `src/page_view.c:4712` | `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,                   ...` |
| `margins` | function | `src/page_view.c:3655` | `* margins (boxdef_from_style) and the painter applies them when                          * it ope...` |
| `mb` | type_alias | `src/page_view.c:1369` | `typedef struct pv_box_info { int l, r, w, center, mt, mb;` |
| `media_has_source` | function | `src/page_view.c:3228` | `static int media_has_source(const lxb_dom_node_t *n)` |
| `nearest_cell` | function | `src/page_view.c:4837` | `static const lxb_dom_node_t *nearest_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,   ...` |
| `nearest_table` | function | `src/page_view.c:4771` | `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,  ...` |
| `next_skip` | function | `src/page_view.c:4861` | `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)` |
| `node_next` | function | `src/page_view.c:986` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `node_table_role` | function | `src/page_view.c:4753` | `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `node_tag` | function | `src/page_view.c:1184` | `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)` |
| `none` | function | `src/page_view.c:2652` | `* inherited when it declares none (every hamburger bar and divider drawn as * a coloured empty box). A box cannot...` |
| `opens` | function | `src/page_view.c:3575` | `* painter applies it when the box opens (band/shared context) — seeding              * it onto ru...` |
| `outermost` | function | `src/page_view.c:3518` | `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);` |
| `paints` | function | `src/page_view.c:1104` | `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas  * vacías"). Comment a...` |
| `parent_is_table_internal` | function | `src/page_view.c:4810` | `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `parse_dim` | function | `src/page_view.c:4112` | `static int parse_dim(const lxb_char_t *s, size_t len)` |
| `positions` | function | `src/page_view.c:140` | `* positions (cp == 0) keep the legacy '?' fallback. */ unsigned int cp = cp1252_to_ucs(c);` |
| `present` | function | `src/page_view.c:4129` | `* when no width descriptors are present (density-only or bare URLs). */ static void srcset_best_u...` |
| `pseudo_box_reg` | function | `src/page_view.c:2171` | `static int pseudo_box_reg(pv_box_reg *r, const lxb_dom_node_t *el, int which,                    ...` |
| `pseudo_generates_box` | function | `src/page_view.c:2192` | `static int pseudo_generates_box(const css_style *ps)` |
| `pseudo_is_block` | function | `src/page_view.c:2209` | `static int pseudo_is_block(const css_style *ps)` |
| `pseudo_is_oof` | function | `src/page_view.c:2205` | `static int pseudo_is_oof(const css_style *ps)` |
| `pseudo_key` | function | `src/page_view.c:2215` | `static const void *pseudo_key(const lxb_dom_node_t *el, int which)` |
| `pv_add_box_def` | function | `src/page_view.c:934` | `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)` |
| `pv_add_cont_def` | function | `src/page_view.c:912` | `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)` |
| `pv_append` | function | `src/page_view.c:419` | `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,                     c...` |
| `pv_append_image` | function | `src/page_view.c:454` | `pv_status pv_append_image(pv_view *v, int heading, int block_break,                           con...` |
| `pv_append_input` | function | `src/page_view.c:484` | `pv_status pv_append_input(pv_view *v, int heading, int block_break,                           pv_...` |
| `pv_append_svg` | function | `src/page_view.c:560` | `pv_status pv_append_svg(pv_view *v, int heading, int block_break,                         const c...` |
| `pv_append_video` | function | `src/page_view.c:524` | `pv_status pv_append_video(pv_view *v, int heading, int block_break,                           con...` |
| `pv_at` | function | `src/page_view.c:969` | `const pv_run *pv_at(const pv_view *v, size_t i)` |
| `pv_box_at` | function | `src/page_view.c:978` | `const pv_box_def *pv_box_at(const pv_view *v, size_t i)` |
| `pv_box_count` | function | `src/page_view.c:974` | `size_t pv_box_count(const pv_view *v)` |
| `pv_box_info` | struct | `src/page_view.c:1369` | `` |
| `pv_box_reg` | struct | `src/page_view.c:1846` | `` |
| `pv_build` | function | `src/page_view.c:5083` | `pv_status pv_build(const hp_document *doc, pv_view **out)` |
| `pv_build_ex` | function | `src/page_view.c:5087` | `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)` |
| `pv_build_full` | function | `src/page_view.c:5091` | `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,                      ...` |
| `pv_build_styled` | function | `src/page_view.c:5225` | `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,                    ...` |
| `pv_cache_find` | function | `src/page_view.c:2332` | `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cache_put` | function | `src/page_view.c:2352` | `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,                      ...` |
| `pv_cache_reindex` | function | `src/page_view.c:2286` | `static void pv_cache_reindex(pv_style_cache *c)` |
| `pv_cached_font_px` | function | `src/page_view.c:2347` | `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_computed` | struct | `src/page_view.c:6961` | `` |
| `pv_computed_free` | function | `src/page_view.c:7007` | `void pv_computed_free(pv_computed *pc)` |
| `pv_computed_get` | function | `src/page_view.c:6985` | `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st,                     do...` |
| `pv_computed_new` | function | `src/page_view.c:6966` | `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css,   ...` |
| `pv_cont_at` | function | `src/page_view.c:929` | `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)` |
| `pv_cont_count` | function | `src/page_view.c:925` | `size_t pv_cont_count(const pv_view *v)` |
| `pv_cont_info` | struct | `src/page_view.c:1267` | `` |
| `pv_container_reg` | struct | `src/page_view.c:1696` | `` |
| `pv_content_hidden` | function | `src/page_view.c:1390` | `int pv_content_hidden(int box_hidden, int run_visibility)` |
| `pv_count` | function | `src/page_view.c:965` | `size_t pv_count(const pv_view *v)` |
| `pv_css_drops` | function | `src/page_view.c:6932` | `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,                        const cha...` |
| `pv_def_h` | struct | `src/page_view.c:2243` | `` |
| `pv_element_has_before` | function | `src/page_view.c:3136` | `static int pv_element_has_before(lxb_dom_node_t *n, const css_sheet *sheet,                      ...` |
| `pv_flow_reg` | struct | `src/page_view.c:3251` | `` |
| `pv_flow_reg` | struct | `src/page_view.c:4739` | `` |
| `pv_free` | function | `src/page_view.c:947` | `void pv_free(pv_view *v)` |
| `pv_item_track` | struct | `src/page_view.c:1350` | `` |
| `pv_mauto_of` | function | `src/page_view.c:1498` | `static int pv_mauto_of(const css_style *cs)` |
| `pv_new` | function | `src/page_view.c:415` | `pv_view *pv_new(void)` |
| `pv_node_map` | struct | `src/page_view.c:348` | `` |
| `pv_node_map_build` | function | `src/page_view.c:406` | `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root)` |
| `pv_node_map_free` | function | `src/page_view.c:364` | `static void pv_node_map_free(pv_node_map *m)` |
| `pv_node_map_init` | function | `src/page_view.c:355` | `static int pv_node_map_init(pv_node_map *m)` |
| `pv_parent_element` | function | `src/page_view.c:2423` | `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)` |
| `pv_placeholder_color` | function | `src/page_view.c:896` | `int pv_placeholder_color(const css_style *ph)` |
| `pv_ptr_hash` | function | `src/page_view.c:2278` | `static size_t pv_ptr_hash(const void *p)` |
| `pv_ptrmap` | struct | `src/page_view.c:294` | `` |
| `pv_ptrmap_free` | function | `src/page_view.c:340` | `static void pv_ptrmap_free(pv_ptrmap *m)` |
| `pv_ptrmap_get` | function | `src/page_view.c:310` | `static int pv_ptrmap_get(const pv_ptrmap *m, const void *k, int *out)` |
| `pv_ptrmap_put` | function | `src/page_view.c:318` | `static void pv_ptrmap_put(pv_ptrmap *m, const void *k, int v)` |
| `pv_ptrmap_slot` | function | `src/page_view.c:300` | `static size_t pv_ptrmap_slot(const pv_ptrmap *m, const void *k)` |
| `pv_root_els` | struct | `src/page_view.c:4311` | `` |
| `pv_root_insets` | function | `src/page_view.c:5186` | `void pv_root_insets(const css_style *body, int out[4])` |
| `pv_set_bgcolor` | function | `src/page_view.c:606` | `void pv_set_bgcolor(pv_view *v, int bg_rgb)` |
| `pv_set_block_id` | function | `src/page_view.c:827` | `void pv_set_block_id(pv_view *v, int block_id)` |
| `pv_set_block_node` | function | `src/page_view.c:847` | `void pv_set_block_node(pv_view *v, dom_node_id id)` |
| `pv_set_box` | function | `src/page_view.c:786` | `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,                 int box_center, int ...` |
| `pv_set_box_maxw` | function | `src/page_view.c:809` | `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct)` |
| `pv_set_box_pct` | function | `src/page_view.c:798` | `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,                     ...` |
| `pv_set_br_line` | function | `src/page_view.c:852` | `void pv_set_br_line(pv_view *v, int br_line)` |
| `pv_set_color` | function | `src/page_view.c:601` | `void pv_set_color(pv_view *v, int fg_rgb)` |
| `pv_set_cont_box` | function | `src/page_view.c:726` | `void pv_set_cont_box(pv_view *v, int cont_box_id)` |
| `pv_set_cont_item` | function | `src/page_view.c:748` | `void pv_set_cont_item(pv_view *v, int cont_item)` |
| `pv_set_container` | function | `src/page_view.c:686` | `void pv_set_container(pv_view *v, int cont_id, int cont_display,                       int cont_g...` |
| `pv_set_emphasis` | function | `src/page_view.c:589` | `void pv_set_emphasis(pv_view *v, int bold, int italic)` |
| `pv_set_flex` | function | `src/page_view.c:730` | `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,                  int...` |
| `pv_set_flex_mauto` | function | `src/page_view.c:742` | `void pv_set_flex_mauto(pv_view *v, int mauto)` |
| `pv_set_float` | function | `src/page_view.c:764` | `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear,                 int ...` |
| `pv_set_float_w` | function | `src/page_view.c:753` | `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box,                     ...` |
| `pv_set_grad_text` | function | `src/page_view.c:622` | `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)` |
| `pv_set_grid` | function | `src/page_view.c:712` | `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)` |
| `pv_set_grid_area` | function | `src/page_view.c:705` | `void pv_set_grid_area(pv_view *v, int row_start, int col_start)` |
| `pv_set_grid_rows` | function | `src/page_view.c:722` | `void pv_set_grid_rows(pv_view *v, int grid_rows)` |
| `pv_set_indent` | function | `src/page_view.c:596` | `void pv_set_indent(pv_view *v, int indent)` |
| `pv_set_input_checked` | function | `src/page_view.c:857` | `void pv_set_input_checked(pv_view *v, int checked)` |
| `pv_set_input_placeholder` | function | `src/page_view.c:862` | `void pv_set_input_placeholder(pv_view *v, int ph_color)` |
| `pv_set_input_select_opts` | function | `src/page_view.c:904` | `void pv_set_input_select_opts(pv_view *v, const char *select_opts)` |
| `pv_set_justify_self` | function | `src/page_view.c:842` | `void pv_set_justify_self(pv_view *v, int justify_self)` |
| `pv_set_node_id` | function | `src/page_view.c:822` | `void pv_set_node_id(pv_view *v, dom_node_id node_id)` |
| `pv_set_oof` | function | `src/page_view.c:837` | `void pv_set_oof(pv_view *v, int oof)` |
| `pv_set_own_box` | function | `src/page_view.c:832` | `void pv_set_own_box(pv_view *v, int box_id)` |
| `pv_set_row_span` | function | `src/page_view.c:701` | `void pv_set_row_span(pv_view *v, int row_span)` |
| `pv_set_text_ext` | function | `src/page_view.c:630` | `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)` |
| `pv_set_text_style` | function | `src/page_view.c:611` | `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,                 ...` |
| `pv_set_ua_tag` | function | `src/page_view.c:816` | `void pv_set_ua_tag(pv_view *v, int ua_tag)` |
| `pv_style_cache` | struct | `src/page_view.c:2250` | `` |
| `pv_style_cache_free` | function | `src/page_view.c:2316` | `static void pv_style_cache_free(pv_style_cache *c)` |
| `pv_style_cache_init` | function | `src/page_view.c:2296` | `static int pv_style_cache_init(pv_style_cache *c)` |
| `pv_svg_append_root_attrs` | function | `src/page_view.c:867` | `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs,                ...` |
| `pv_text_ext_merge` | function | `src/page_view.c:1422` | `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)` |
| `pv_text_ext_reset` | function | `src/page_view.c:1396` | `void pv_text_ext_reset(pv_text_ext *e)` |
| `pv_var_node` | struct | `src/page_view.c:2234` | `` |
| `pv_var_push` | function | `src/page_view.c:2402` | `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,                       ...` |
| `px` | function | `src/page_view.c:5843` | `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */                 if (iw <...` |
| `resolve_context` | function | `src/page_view.c:3256` | `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,                 ...` |
| `resolves` | function | `src/page_view.c:1050` | `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close  * button/tooltip w...` |
| `roman_marker` | function | `src/page_view.c:4687` | `static void roman_marker(int n, int upper, char *out, size_t cap)` |
| `run_init_common` | function | `src/page_view.c:165` | `static void run_init_common(pv_run *r)` |
| `serialize_subtree` | function | `src/page_view.c:4069` | `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)` |
| `size` | function | `src/page_view.c:2723` | `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */ static void app...` |
| `srcset_slot_width` | function | `src/page_view.c:4224` | `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,                               ...` |
| `string` | function | `src/page_view.c:4340` | `* Returns a heap string (caller frees) or NULL when neither carries a class —  * NULL simply mean...` |
| `subtree_has_own_text` | function | `src/page_view.c:3168` | `static int subtree_has_own_text(const lxb_dom_node_t *n, const lxb_dom_node_t *base,             ...` |
| `subtree_is_oof` | function | `src/page_view.c:2703` | `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,                      ...` |
| `sz_count` | function | `src/page_view.c:4047` | `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)` |
| `sz_fill` | struct | `src/page_view.c:4055` | `` |
| `sz_write` | function | `src/page_view.c:4061` | `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)` |
| `table` | function | `src/page_view.c:4932` | `* FLOW table (multi-link: walked so its links survive) do NOT suppress their  * content -- their ...` |
| `table_columns` | function | `src/page_view.c:4950` | `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)` |
| `trying` | function | `src/page_view.c:1856` | `* a real page passes without trying (slashdot's front page saturates it), and past  * it box_reg_...` |
| `ua_tag_of` | function | `src/page_view.c:1129` | `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)` |
| `under_unrendered` | function | `src/page_view.c:4452` | `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)` |
| `utf8_encode` | function | `src/page_view.c:104` | `static size_t utf8_encode(unsigned int cp, char *out)` |
| `utf8_sanitized_dup` | function | `src/page_view.c:117` | `static char *utf8_sanitized_dup(const char *s)` |
| `walk` | function | `src/page_view.c:3876` | `* far on this walk (they are all inside this element). */                          /* The innermo...` |
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
| `js_ident_ch` | function | `src/prefetch.c:207` | `static int js_ident_ch(char c)` |
| `js_skip_string` | function | `src/prefetch.c:219` | `static size_t js_skip_string(const char *s, size_t i, size_t n)` |
| `js_skip_ws` | function | `src/prefetch.c:212` | `static size_t js_skip_ws(const char *s, size_t i, size_t n)` |
| `js_take_spec` | function | `src/prefetch.c:226` | `static void js_take_spec(const char *s, size_t i, size_t n,                          char (*out)[...` |
| `lower` | function | `src/prefetch.c:35` | `static int lower(int c)` |
| `pf_find_importmap` | function | `src/prefetch.c:483` | `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n)` |
| `pf_follow_imports` | function | `src/prefetch.c:333` | `static void pf_follow_imports(pf_pool *p, const char *base, const char *body, size_t len)` |
| `pf_is_js` | function | `src/prefetch.c:311` | `static int pf_is_js(const char *url, const char *ctype)` |
| `pf_list_free` | function | `src/prefetch.c:196` | `void pf_list_free(pf_list *l)` |
| `pf_pool_add` | function | `src/prefetch.c:288` | `int pf_pool_add(pf_pool *p, const char *url)` |
| `pf_pool_finish` | function | `src/prefetch.c:540` | `void pf_pool_finish(pf_pool *p)` |
| `pf_pool_start` | function | `src/prefetch.c:387` | `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,                   pf_fetch_f...` |
| `pf_pool_start_page` | function | `src/prefetch.c:504` | `int pf_pool_start_page(pf_pool *p, const char *html, size_t len, const char *page_url,           ...` |
| `pf_pool_take` | function | `src/prefetch.c:444` | `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,                  char **body,...` |
| `pf_pooled_fetch` | function | `src/prefetch.c:561` | `int pf_pooled_fetch(void *vctx, const char *method, const char *url,                     const ch...` |
| `pf_scan` | function | `src/prefetch.c:133` | `int pf_scan(const char *html, size_t len, pf_list *out)` |
| `pf_scan_imports` | function | `src/prefetch.c:241` | `size_t pf_scan_imports(const char *js, size_t len, char (*out)[PF_SPEC_MAX], size_t cap)` |
| `pf_url_cb` | function | `src/prefetch.c:319` | `static int pf_url_cb(void *ctx, const char *base, const char *ref, char *out, size_t outsz)` |
| `pf_url_shaped` | function | `src/prefetch.c:324` | `static int pf_url_shaped(const char *sp)` |
| `pf_worker` | function | `src/prefetch.c:349` | `static void *pf_worker(void *arg)` |
| `pool_start` | function | `src/prefetch.c:394` | `static int pool_start(pf_pool *p, const char *const *urls, size_t nurls,                       pf...` |
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
| `PROFILE_KEYFILE_LEN` | macro | `src/profile.c:27` | `#define PROFILE_KEYFILE_LEN` |
| `_POSIX_C_SOURCE` | macro | `src/profile.c:11` | `#define _POSIX_C_SOURCE` |
| `join_path` | function | `src/profile.c:29` | `static int join_path(const profile_ctx *ctx, const char *name,                      char *out, si...` |
| `keyfile_create` | function | `src/profile.c:36` | `static profile_status keyfile_create(const char *dir, const char *path,                          ...` |
| `map_ds` | function | `src/profile.c:98` | `static profile_status map_ds(ds_status ds)` |
| `profile_close` | function | `src/profile.c:149` | `void profile_close(profile_ctx *ctx)` |
| `profile_load` | function | `src/profile.c:112` | `profile_status profile_load(const profile_ctx *ctx, prefs_state *out)` |
| `profile_open` | function | `src/profile.c:59` | `profile_status profile_open(profile_ctx *ctx, const char *dir)` |
| `profile_save` | function | `src/profile.c:133` | `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p)` |
| `place` | function | `src/render_doc.c:237` | `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never...` |
| `rd_at` | function | `src/render_doc.c:763` | `const rd_block *rd_at(const rd_doc *d, size_t i)` |
| `rd_block_heading_level` | function | `src/render_doc.c:800` | `int rd_block_heading_level(const rd_block *b)` |
| `rd_block_tag` | function | `src/render_doc.c:811` | `const char *rd_block_tag(const rd_block *b)` |
| `rd_box_at` | function | `src/render_doc.c:772` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)` |
| `rd_box_count` | function | `src/render_doc.c:768` | `size_t rd_box_count(const rd_doc *d)` |
| `rd_build` | function | `src/render_doc.c:269` | `rd_status rd_build(const pv_view *view, rdp_caps caps,                    const char *top_level_u...` |
| `rd_cont_at` | function | `src/render_doc.c:781` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)` |
| `rd_cont_count` | function | `src/render_doc.c:777` | `size_t rd_cont_count(const rd_doc *d)` |
| `rd_count` | function | `src/render_doc.c:759` | `size_t rd_count(const rd_doc *d)` |
| `rd_free` | function | `src/render_doc.c:742` | `void rd_free(rd_doc *d)` |
| `rd_image_fail_label` | function | `src/render_doc.c:877` | `const char *rd_image_fail_label(img_fail_reason reason)` |
| `rd_image_label` | function | `src/render_doc.c:866` | `const char *rd_image_label(rdp_img_decision d)` |
| `rd_input_invisible` | function | `src/render_doc.c:862` | `int rd_input_invisible(int input_type)` |
| `rd_input_label` | function | `src/render_doc.c:842` | `const char *rd_input_label(int input_type)` |
| `rd_kind_name` | function | `src/render_doc.c:786` | `const char *rd_kind_name(rd_kind k)` |
| `rd_push` | function | `src/render_doc.c:60` | `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,                  ...` |
| `rd_push_input` | function | `src/render_doc.c:211` | `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` |
| `resolve_image_decision` | function | `src/render_doc.c:247` | `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,         ...` |
| `unset` | function | `src/render_doc.c:677` | `* background paints as if unset (no border/box-shadow-style                  * "broken image" pla...` |
| `utf8_sanitized_dup` | function | `src/render_doc.c:28` | `static char *utf8_sanitized_dup(const char *s)` |
| `rdp_caps_safe` | function | `src/render_policy.c:17` | `rdp_caps rdp_caps_safe(void)` |
| `rdp_image_decision` | function | `src/render_policy.c:28` | `rdp_img_decision rdp_image_decision(rdp_caps caps,                                     const char...` |
| `rdp_images_warning` | function | `src/render_policy.c:74` | `const char *rdp_images_warning(void)` |
| `rdp_img_reason` | function | `src/render_policy.c:63` | `const char *rdp_img_reason(rdp_img_decision d)` |
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
| `lower` | function | `src/request_policy.c:22` | `static char lower(char c)` |
| `psl_cmp` | function | `src/request_policy.c:36` | `static int psl_cmp(const void *key, const void *elem)` |
| `psl_in` | function | `src/request_policy.c:40` | `static int psl_in(const char *const *arr, size_t n, const char *key)` |
| `public_suffix_labels` | function | `src/request_policy.c:48` | `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)` |
| `rp_evaluate` | function | `src/request_policy.c:143` | `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)` |
| `rp_host_of` | function | `src/request_policy.c:76` | `int rp_host_of(const char *url, char *out, size_t out_size)` |
| `rp_same_site` | function | `src/request_policy.c:134` | `int rp_same_site(const char *top_level_url, const char *request_url)` |
| `rp_site_of` | function | `src/request_policy.c:102` | `int rp_site_of(const char *host, char *out, size_t out_size)` |
| `SF_RCACHE_SLOTS` | macro | `src/secure_fetch.c:1105` | `#define SF_RCACHE_SLOTS` |
| `SF_RCACHE_TTL_S` | macro | `src/secure_fetch.c:1106` | `#define SF_RCACHE_TTL_S` |
| `_POSIX_C_SOURCE` | macro | `src/secure_fetch.c:12` | `#define _POSIX_C_SOURCE` |
| `add_header` | function | `src/secure_fetch.c:770` | `static int add_header(struct curl_slist **h, const char *line)` |
| `body_sink` | struct | `src/secure_fetch.c:473` | `` |
| `ci_index` | function | `src/secure_fetch.c:57` | `static long ci_index(const char *haystack, const char *needle)` |
| `ci_starts_with` | function | `src/secure_fetch.c:45` | `static int ci_starts_with(const char *haystack, const char *prefix)` |
| `copy_bounded` | function | `src/secure_fetch.c:511` | `static void copy_bounded(char *dst, size_t dstsz, const char *src)` |
| `copy_checked` | function | `src/secure_fetch.c:337` | `static int copy_checked(char *dst, size_t dstsz, const char *src)` |
| `database` | function | `src/secure_fetch.c:526` | `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid...` |
| `fetch_ctx` | struct | `src/secure_fetch.c:496` | `` |
| `get_negotiated_group_name` | function | `src/secure_fetch.c:522` | `static const char *get_negotiated_group_name(SSL *ssl)` |
| `group` | function | `src/secure_fetch.c:540` | `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);` |
| `header_cb` | function | `src/secure_fetch.c:591` | `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` |
| `header_value_clean` | function | `src/secure_fetch.c:243` | `static int header_value_clean(const char *s)` |
| `inspect_chain` | function | `src/secure_fetch.c:676` | `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` |
| `map_curl_error` | function | `src/secure_fetch.c:729` | `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)` |
| `module` | function | `src/secure_fetch.c:398` | `* pure url module (DRY);` |
| `name_is_pq_sig` | function | `src/secure_fetch.c:666` | `static int name_is_pq_sig(int pknid)` |
| `progress` | function | `src/secure_fetch.c:482` | `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);` |
| `rcache_put_ram` | function | `src/secure_fetch.c:1138` | `static int rcache_put_ram(const char *from, const char *to, time_t now)` |
| `redirect` | function | `src/secure_fetch.c:859` | `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a      * different orig...` |
| `sf_accept_language_or_default` | function | `src/secure_fetch.c:253` | `const char *sf_accept_language_or_default(const char *lang)` |
| `sf_attempt_get` | function | `src/secure_fetch.c:1442` | `static sf_status sf_attempt_get(const char *url, const sf_config *cfg, sf_response *out,         ...` |
| `sf_attempt_post` | function | `src/secure_fetch.c:1448` | `static sf_status sf_attempt_post(const char *url, const sf_config *cfg, sf_response *out,        ...` |
| `sf_check_chain_policy` | function | `src/secure_fetch.c:296` | `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)` |
| `sf_check_group_is_pq` | function | `src/secure_fetch.c:287` | `sf_status sf_check_group_is_pq(const char *negotiated_group)` |
| `sf_check_tls_version` | function | `src/secure_fetch.c:282` | `sf_status sf_check_tls_version(const char *negotiated_version)` |
| `sf_ci_prefix` | function | `src/secure_fetch.c:405` | `static int sf_ci_prefix(const char *s, const char *p)` |
| `sf_config_default` | function | `src/secure_fetch.c:217` | `sf_config sf_config_default(void)` |
| `sf_cookie_header_for` | function | `src/secure_fetch.c:167` | `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)` |
| `sf_cookie_line_matches` | function | `src/secure_fetch.c:97` | `int sf_cookie_line_matches(const char *line, const char *host, const char *path,                 ...` |
| `sf_cookie_put` | function | `src/secure_fetch.c:196` | `void sf_cookie_put(const char *url, const char *namevalue)` |
| `sf_downgrade_of` | function | `src/secure_fetch.c:1433` | `static int sf_downgrade_of(sf_policy p)` |
| `sf_enforce_policy` | function | `src/secure_fetch.c:306` | `sf_status sf_enforce_policy(const char *tls_version, const char *group,                          ...` |
| `sf_fallback_policy` | function | `src/secure_fetch.c:1419` | `int sf_fallback_policy(sf_status failed, sf_policy tried, int allowlisted, sf_policy *next)` |
| `sf_get` | function | `src/secure_fetch.c:1085` | `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)` |
| `sf_get_follow` | function | `src/secure_fetch.c:1196` | `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,                 ...` |
| `sf_get_follow_navigable` | function | `src/secure_fetch.c:1473` | `sf_status sf_get_follow_navigable(const char *url, sf_config *cfg, sf_response *out,             ...` |
| `sf_global_init` | function | `src/secure_fetch.c:82` | `void sf_global_init(void)` |
| `sf_header_value` | function | `src/secure_fetch.c:353` | `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz)` |
| `sf_impersonate_kex_groups` | function | `src/secure_fetch.c:257` | `const char *sf_impersonate_kex_groups(void)` |
| `sf_impersonate_tls13_ciphers` | function | `src/secure_fetch.c:258` | `const char *sf_impersonate_tls13_ciphers(void)` |
| `sf_is_redirect_code` | function | `src/secure_fetch.c:346` | `int sf_is_redirect_code(long http_code)` |
| `sf_navigable` | function | `src/secure_fetch.c:1453` | `static sf_status sf_navigable(sf_attempt_fn attempt, const char *url, sf_config *cfg,            ...` |
| `sf_parse_location_header` | function | `src/secure_fetch.c:375` | `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)` |
| `sf_perform` | function | `src/secure_fetch.c:933` | `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,             ...` |
| `sf_post` | function | `src/secure_fetch.c:1089` | `sf_status sf_post(const char *url, const sf_config *cfg,                   const void *body, size...` |
| `sf_post_navigable` | function | `src/secure_fetch.c:1478` | `sf_status sf_post_navigable(const char *url, sf_config *cfg, const void *body,                   ...` |
| `sf_rcache_clear` | function | `src/secure_fetch.c:1119` | `void sf_rcache_clear(void)` |
| `sf_rcache_entry` | struct | `src/secure_fetch.c:1108` | `` |
| `sf_rcache_get` | function | `src/secure_fetch.c:1167` | `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap)` |
| `sf_rcache_put` | function | `src/secure_fetch.c:1157` | `int sf_rcache_put(const char *from, const char *to, time_t now)` |
| `sf_rcache_set_backing` | function | `src/secure_fetch.c:1130` | `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx)` |
| `sf_resolve_redirect` | function | `src/secure_fetch.c:393` | `sf_status sf_resolve_redirect(const char *base_url, const char *location,                        ...` |
| `sf_response_free` | function | `src/secure_fetch.c:445` | `void sf_response_free(sf_response *resp)` |
| `sf_setup_handle` | function | `src/secure_fetch.c:784` | `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,            ...` |
| `sf_share_lock` | function | `src/secure_fetch.c:69` | `static void sf_share_lock(CURL *handle, curl_lock_data data,                           curl_lock_...` |
| `sf_share_unlock` | function | `src/secure_fetch.c:75` | `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)` |
| `sf_url_host_path` | function | `src/secure_fetch.c:152` | `static int sf_url_host_path(const char *url, char *host, size_t hostsz,                          ...` |
| `sf_url_is_http` | function | `src/secure_fetch.c:270` | `static int sf_url_is_http(const char *url)` |
| `sf_user_agent_or_default` | function | `src/secure_fetch.c:249` | `const char *sf_user_agent_or_default(const char *ua)` |
| `sf_validate_url` | function | `src/secure_fetch.c:262` | `sf_status sf_validate_url(const char *url)` |
| `sf_ws` | struct | `src/secure_fetch.c:1273` | `` |
| `sf_ws_close` | function | `src/secure_fetch.c:1408` | `void sf_ws_close(sf_ws *ws)` |
| `sf_ws_fd` | function | `src/secure_fetch.c:1401` | `int sf_ws_fd(const sf_ws *ws)` |
| `sf_ws_open` | function | `src/secure_fetch.c:1301` | `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)` |
| `sf_ws_recv` | function | `src/secure_fetch.c:1379` | `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)` |
| `sf_ws_send` | function | `src/secure_fetch.c:1356` | `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)` |
| `sf_ws_url_check` | function | `src/secure_fetch.c:1280` | `sf_status sf_ws_url_check(const char *url)` |
| `sink` | type_alias | `src/secure_fetch.c:495` | `typedef struct fetch_ctx { body_sink sink;` |
| `this` | function | `src/secure_fetch.c:572` | `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and...` |
| `tls_capture` | struct | `src/secure_fetch.c:486` | `` |
| `tls_capture_from_ssl` | function | `src/secure_fetch.c:565` | `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)` |
| `tls_capture_try` | function | `src/secure_fetch.c:555` | `static void tls_capture_try(tls_capture *cap)` |
| `write_cb` | function | `src/secure_fetch.c:634` | `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)` |
| `ws_free` | function | `src/secure_fetch.c:1292` | `static void ws_free(sf_ws *ws)` |
| `ws_ssl_ctx_cb` | function | `src/secure_fetch.c:1266` | `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)` |
| `ws_ssl_info_cb` | function | `src/secure_fetch.c:1259` | `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)` |
| `SV_MAX_ATTRS` | macro | `src/svg_render.c:96` | `#define SV_MAX_ATTRS` |
| `point` | function | `src/svg_render.c:567` | `* current point (SVG 8.3.6). */ int had = (prev == 'C' \|\| prev == 'c' \|\| prev == 'S' \|\| prev == 's');` |
| `stroke` | type_alias | `src/svg_render.c:151` | `typedef struct sv_ctx { int fill, stroke;` |
| `sv_apply_prop` | function | `src/svg_render.c:260` | `static void sv_apply_prop(sv_ctx *ctx, const char *nm, size_t nl,                           const...` |
| `sv_arc_to_cubics` | function | `src/svg_render.c:399` | `static int sv_arc_to_cubics(sv_image *im, sv_shape *sh,                             double x0, do...` |
| `sv_attr` | struct | `src/svg_render.c:91` | `` |
| `sv_attr_get` | function | `src/svg_render.c:99` | `static const char *sv_attr_get(const sv_attr *at, size_t nat, const char *name, size_t *len)` |
| `sv_attr_num` | function | `src/svg_render.c:108` | `static double sv_attr_num(const sv_attr *at, size_t nat, const char *name, double dflt)` |
| `sv_collect_text` | function | `src/svg_render.c:736` | `static void sv_collect_text(const char *s, size_t n, size_t *i, char *dst, size_t cap)` |
| `sv_ctx` | struct | `src/svg_render.c:151` | `` |
| `sv_ctx_from_attrs` | function | `src/svg_render.c:307` | `static void sv_ctx_from_attrs(sv_ctx *ctx, const sv_attr *at, size_t nat)` |
| `sv_fit` | function | `src/svg_render.c:754` | `void sv_fit(const sv_image *img, double dw, double dh,             double *scale, double *off_x, ...` |
| `sv_flag` | function | `src/svg_render.c:477` | `static int sv_flag(const char *s, size_t n, size_t *i, double *out)` |
| `sv_is_digit` | function | `src/svg_render.c:25` | `static int sv_is_digit(char c)` |

Next: [SYMBOLS_p10.md](SYMBOLS_p10.md)
