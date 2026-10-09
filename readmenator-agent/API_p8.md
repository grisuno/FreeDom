# API (page 8 of 9)
Previous: [API_p7.md](API_p7.md)

## src/page_view.c
Depends on: `include/box_style.h`, `include/box_tree.h`, `include/css.h`, `include/css_chain.h`, `include/css_color.h`, `include/css_length.h`, `include/css_vars.h`, `include/dom.h`, `include/flex_layout.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/page_view.h`, `include/svg_render.h`, `include/util.h`
- `cp1252_to_ucs` (function) `src/page_view.c:84` `static unsigned int cp1252_to_ucs(unsigned char c)` -- Unicode scalar for a Windows-1252 byte (only meaningful for c >= 0x80).
- `utf8_encode` (function) `src/page_view.c:98` `static size_t utf8_encode(unsigned int cp, char *out)` -- Encodes a BMP scalar (<= 0xFFFF, which covers all Windows-1252 targets) as * UTF-8 into out (up to 3 bytes); returns...
- `utf8_sanitized_dup` (function) `src/page_view.c:111` `static char *utf8_sanitized_dup(const char *s)`
- `positions` (function) `src/page_view.c:134` `* positions (cp == 0) keep the legacy '?' fallback. */ unsigned int cp = cp1252_to_ucs(c);`
- `dup_n` (function) `src/page_view.c:145` `static char *dup_n(const char *s, size_t n)`
- `run_init_common` (function) `src/page_view.c:159` `static void run_init_common(pv_run *r)` -- Common field initialization shared by all append helpers.
- `pv_node_map_init` (function) `src/page_view.c:278` `static int pv_node_map_init(pv_node_map *m)`
- `pv_node_map_free` (function) `src/page_view.c:286` `static void pv_node_map_free(pv_node_map *m)`
- `pv_node_map_build` (function) `src/page_view.c:322` `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root)` -- Builds a document-order map of all element nodes under root.
- `pv_new` (function) `src/page_view.c:331` `pv_view *pv_new(void)`
- `pv_append` (function) `src/page_view.c:335` `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    c...`
- `pv_append_image` (function) `src/page_view.c:369` `pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          con...`
- `pv_append_input` (function) `src/page_view.c:399` `pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_...`
- `pv_append_video` (function) `src/page_view.c:439` `pv_status pv_append_video(pv_view *v, int heading, int block_break,
                          con...`
- `pv_append_svg` (function) `src/page_view.c:475` `pv_status pv_append_svg(pv_view *v, int heading, int block_break,
                        const c...`
- `pv_set_emphasis` (function) `src/page_view.c:504` `void pv_set_emphasis(pv_view *v, int bold, int italic)`
- `pv_set_indent` (function) `src/page_view.c:511` `void pv_set_indent(pv_view *v, int indent)`
- `pv_set_color` (function) `src/page_view.c:516` `void pv_set_color(pv_view *v, int fg_rgb)`
- `pv_set_bgcolor` (function) `src/page_view.c:521` `void pv_set_bgcolor(pv_view *v, int bg_rgb)`
- `pv_set_text_style` (function) `src/page_view.c:526` `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,
                ...`
- `pv_set_grad_text` (function) `src/page_view.c:537` `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)`
- `pv_set_text_ext` (function) `src/page_view.c:545` `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)`
- `ignored` (function) `src/page_view.c:577` `* source is ignored (fail-visible: never invisible text from half a
     * pattern). A real text-...`
- `pv_set_container` (function) `src/page_view.c:592` `void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_g...`
- `pv_set_row_span` (function) `src/page_view.c:607` `void pv_set_row_span(pv_view *v, int row_span)`
- `pv_set_grid_area` (function) `src/page_view.c:611` `void pv_set_grid_area(pv_view *v, int row_start, int col_start)`
- `pv_set_grid` (function) `src/page_view.c:618` `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)`
- `pv_set_grid_rows` (function) `src/page_view.c:628` `void pv_set_grid_rows(pv_view *v, int grid_rows)`
- `pv_set_cont_box` (function) `src/page_view.c:632` `void pv_set_cont_box(pv_view *v, int cont_box_id)`
- `pv_set_flex` (function) `src/page_view.c:636` `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                 int...`
- `pv_set_flex_mauto` (function) `src/page_view.c:648` `void pv_set_flex_mauto(pv_view *v, int mauto)`
- `pv_set_cont_item` (function) `src/page_view.c:654` `void pv_set_cont_item(pv_view *v, int cont_item)`
- `pv_set_float` (function) `src/page_view.c:659` `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear,
                int ...`
- `pv_set_box` (function) `src/page_view.c:681` `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                int box_center, int ...`
- `pv_set_box_pct` (function) `src/page_view.c:693` `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,
                    ...`
- `pv_set_box_maxw` (function) `src/page_view.c:704` `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct)`
- `pv_set_ua_tag` (function) `src/page_view.c:711` `void pv_set_ua_tag(pv_view *v, int ua_tag)`
- `pv_set_node_id` (function) `src/page_view.c:717` `void pv_set_node_id(pv_view *v, dom_node_id node_id)`
- `pv_set_block_id` (function) `src/page_view.c:722` `void pv_set_block_id(pv_view *v, int block_id)`
- `pv_set_own_box` (function) `src/page_view.c:727` `void pv_set_own_box(pv_view *v, int box_id)`
- `pv_set_oof` (function) `src/page_view.c:732` `void pv_set_oof(pv_view *v, int oof)`
- `pv_set_input_checked` (function) `src/page_view.c:737` `void pv_set_input_checked(pv_view *v, int checked)`
- `pv_set_input_select_opts` (function) `src/page_view.c:742` `void pv_set_input_select_opts(pv_view *v, const char *select_opts)`
- `pv_add_cont_def` (function) `src/page_view.c:750` `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)`
- `pv_cont_count` (function) `src/page_view.c:763` `size_t pv_cont_count(const pv_view *v)`
- `pv_cont_at` (function) `src/page_view.c:767` `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)`
- `pv_add_box_def` (function) `src/page_view.c:772` `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)`
- `pv_free` (function) `src/page_view.c:785` `void pv_free(pv_view *v)`
- `pv_count` (function) `src/page_view.c:802` `size_t pv_count(const pv_view *v)`
- `pv_at` (function) `src/page_view.c:806` `const pv_run *pv_at(const pv_view *v, size_t i)`
- `pv_box_count` (function) `src/page_view.c:811` `size_t pv_box_count(const pv_view *v)`
- `pv_box_at` (function) `src/page_view.c:815` `const pv_box_def *pv_box_at(const pv_view *v, size_t i)`
- `node_next` (function) `src/page_view.c:823` `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` -- } size_t pv_box_count(const pv_view *v) { return (v != NULL) ? v->nbox : 0; } const pv_box_def *pv_box_at(const...
- `is_block_tag` (function) `src/page_view.c:833` `static int is_block_tag(lxb_tag_id_t t)`
- `is_block_like` (function) `src/page_view.c:858` `static int is_block_like(lxb_tag_id_t t, css_display display)` -- An element should be treated as block-like (eligible for box registration, hbox, float) when its CSS display...
- `resolves` (function) `src/page_view.c:887` `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close
 * button/tooltip w...`
- `is_block_like_style` (function) `src/page_view.c:897` `static int is_block_like_style(lxb_tag_id_t t, const css_style *cs)` -- is_block_like with the out-of-flow coercion applied.
- `generates_box` (function) `src/page_view.c:909` `static int generates_box(lxb_tag_id_t t, css_display display)`
- `generates_box_style` (function) `src/page_view.c:921` `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)` -- Form controls (input/select/textarea/button) are inline-block by default but can carry author CSS like...
- `causes_block_break` (function) `src/page_view.c:928` `static int causes_block_break(lxb_tag_id_t t, css_display display)` -- Returns 1 when the element should cause a block break (start a new line). display:inline-block and display:inline do...
- `paints` (function) `src/page_view.c:937` `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas
 * vacías"). Comment a...`
- `ua_tag_of` (function) `src/page_view.c:962` `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)` -- User-agent box identity of a block-level element, from its lexbor tag id.
- `heading_level` (function) `src/page_view.c:984` `static int heading_level(lxb_tag_id_t t)`
- `is_skipped_tag` (function) `src/page_view.c:996` `static int is_skipped_tag(lxb_tag_id_t t)`
- `node_tag` (function) `src/page_view.c:1017` `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)`
- `content` (function) `src/page_view.c:1022` `* a <noscript> ancestor also suppresses content (the script would run, so the * fallback is hidden);`
- `in_skipped_subtree` (function) `src/page_view.c:1025` `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
              ...` -- Nonzero if any ancestor up to base is a non-rendered container.
- `font_color_attr` (function) `src/page_view.c:1062` `static int font_color_attr(lxb_dom_element_t *el)`
- `bgcolor_attr` (function) `src/page_view.c:1068` `static int bgcolor_attr(lxb_dom_element_t *el)` -- Legacy bgcolor attribute (body/table/tr/td), the background twin of <font * color>: pre-CSS sites (Hacker News'...
- `address` (function) `src/page_view.c:1090` `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <=...`
- `child` (function) `src/page_view.c:1098` `* child (NULL = anonymous item: text directly inside the container);`
- `id` (function) `src/page_view.c:1118` `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);`
- `item_ordinal` (function) `src/page_view.c:1181` `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)` -- Ordinal for a run of container `cid` whose direct-child item is `item` (NULL = * anonymous: every such run is its...
- `it` (function) `src/page_view.c:1209` `* it (they inherit in CSS). list_style drives the <li> marker (structural);`
- `pv_content_hidden` (function) `src/page_view.c:1213` `int pv_content_hidden(int box_hidden, int run_visibility)` -- The author text-presentation extensions struct (pv_text_ext) is public now (include/page_view.h): each field...
- `pv_text_ext_reset` (function) `src/page_view.c:1219` `void pv_text_ext_reset(pv_text_ext *e)`
- `pv_text_ext_merge` (function) `src/page_view.c:1245` `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)` -- Merges one ancestor's resolved css_style into ext, nearest ancestor first (a field * already set is not overwritten...
- `css_has_hbox` (function) `src/page_view.c:1303` `static int css_has_hbox(const css_style *cs)` -- True if the resolved style declares any HORIZONTAL box property, in either half of the <length-percentage>: `width...
- `pv_mauto_of` (function) `src/page_view.c:1317` `static int pv_mauto_of(const css_style *cs)` -- Pre-resolves the horizontal box (px) into a run's wire fields: l/r insets = padding + non-auto margin of each side...
- `css_hbox_resolve` (function) `src/page_view.c:1324` `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)`
- `css_has_position` (function) `src/page_view.c:1372` `static int css_has_position(const css_style *cs)` -- A real (non-static) position makes a block box-carrying too, so its position/insets/ * z-index ride the box-def tree...
- `css_has_boxdeco` (function) `src/page_view.c:1377` `static int css_has_boxdeco(const css_style *cs)`
- `cont_def_reset` (function) `src/page_view.c:1520` `static void cont_def_reset(pv_cont_def *d)` -- Per-container parameters + parent linkage (2026-07-31).
- `container_id` (function) `src/page_view.c:1535` `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)` -- memset(d, 0, sizeof *d); d->parent_id = -1; d->parent_item = -1; d->row_gap = -1; d->box_id = -1; d->item_grow = -1...
- `annotate_flow_run` (function) `src/page_view.c:1581` `static void annotate_flow_run(pv_view *v, pv_container_reg *reg, pv_item_track *items,
          ...` -- Stamps the last run with its element's layout annotation: container membership and item slot, flex/grid item...
- `trying` (function) `src/page_view.c:1620` `* a real page passes without trying (slashdot's front page saturates it), and past
 * it box_reg_...`
- `box_reg_free` (function) `src/page_view.c:1649` `static void box_reg_free(pv_box_reg *r)`
- `boxdef_from_style` (function) `src/page_view.c:1658` `static void boxdef_from_style(pv_box_def *d, const css_style *cs)` -- Fills *d (decoration + hbox + bg; parent_id defaults to -1) from a resolved style.
- `here` (function) `src/page_view.c:1749` `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3...`
- `glyphs` (function) `src/page_view.c:1787` `* glyphs (the runs carry it as their fill source);`
- `box_reg_id` (function) `src/page_view.c:1881` `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,
           ...` -- Registers (or finds) the box for `node`. font_px is the element's COMPUTED font-size, needed because the user-agent...
- `pseudo_box_reg` (function) `src/page_view.c:1910` `static int pseudo_box_reg(pv_box_reg *r, const lxb_dom_node_t *el, int which,
                   ...` -- Registers (or finds) the GENERATED box of el's ::before / ::after (which = CSS_PSEUDO_BEFORE / CSS_PSEUDO_AFTER)...
- `pseudo_generates_box` (function) `src/page_view.c:1931` `static int pseudo_generates_box(const css_style *ps)` -- True iff a generated box paints or sizes something of its own: the same gate as any element's box, plus a declared...
- `pseudo_is_oof` (function) `src/page_view.c:1944` `static int pseudo_is_oof(const css_style *ps)`
- `pseudo_is_block` (function) `src/page_view.c:1948` `static int pseudo_is_block(const css_style *ps)`
- `pseudo_key` (function) `src/page_view.c:1954` `static const void *pseudo_key(const lxb_dom_node_t *el, int which)` -- return css_has_boxdeco(ps) || ps->width > 0 || ps->pct[CSS_PCT_WIDTH] > 0 || ps->background >= 0 ||...
- `pv_ptrmap_slot` (function) `src/page_view.c:1968` `static size_t pv_ptrmap_slot(const pv_ptrmap *m, const void *k)`
- `pv_ptrmap_get` (function) `src/page_view.c:1978` `static int pv_ptrmap_get(const pv_ptrmap *m, const void *k, int *out)`
- `pv_ptrmap_put` (function) `src/page_view.c:1986` `static void pv_ptrmap_put(pv_ptrmap *m, const void *k, int v)`
- `pv_ptrmap_free` (function) `src/page_view.c:2008` `static void pv_ptrmap_free(pv_ptrmap *m)`
- `pv_ptr_hash` (function) `src/page_view.c:2053` `static size_t pv_ptr_hash(const void *p)`
- `pv_cache_reindex` (function) `src/page_view.c:2061` `static void pv_cache_reindex(pv_style_cache *c)`
- `pv_style_cache_init` (function) `src/page_view.c:2071` `static int pv_style_cache_init(pv_style_cache *c)`
- `pv_style_cache_free` (function) `src/page_view.c:2089` `static void pv_style_cache_free(pv_style_cache *c)`
- `pv_cache_find` (function) `src/page_view.c:2103` `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)` -- cch_element_style(el, sheet), memoized in *cache.
- `pv_cached_font_px` (function) `src/page_view.c:2118` `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)` -- The COMPUTED font-size memoized for `node`, or 0 when it is not in the cache (no cache, or the element's style was...
- `pv_cache_put` (function) `src/page_view.c:2123` `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,
                     ...`
- `pv_var_push` (function) `src/page_view.c:2162` `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,
                      ...` -- Takes ownership of *own (left zeroed) as a new chain node over `parent`. * Returns the node's chain, or `parent`...
- `pv_parent_element` (function) `src/page_view.c:2183` `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)` -- cache->vn = g; cache->vncap = nc; } pv_var_node *n = (pv_var_node *)calloc(1, sizeof *n); if (n == NULL) {...
- `cached_pseudo_style` (function) `src/page_view.c:2244` `static css_style cached_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet,
             ...` -- The ::before/::after generated box's style of el (spec/page_view.md "Cajas generadas"): resolved against el's...
- `subtree_is_oof` (function) `src/page_view.c:2262` `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,
                     ...` -- True iff the element itself is out of flow (position:absolute/fixed) or descends from one.
- `size` (function) `src/page_view.c:2282` `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */
static void app...`
- `builder` (function) `src/page_view.c:2302` `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box
 * (the ...`
- `css_to_fx_justify` (function) `src/page_view.c:2331` `static int css_to_fx_justify(css_justify j)` -- Maps a css_justify (resolved by the css cascade) to a flex_layout fx_justify. * Unset / start / unknown all fall to...
- `is_bold_tag` (function) `src/page_view.c:2350` `static int is_bold_tag(lxb_tag_id_t t)` -- Tags the user-agent sheet renders bold.
- `is_italic_tag` (function) `src/page_view.c:2355` `static int is_italic_tag(lxb_tag_id_t t)`
- `is_inline_level_style` (function) `src/page_view.c:2392` `static int is_inline_level_style(lxb_tag_id_t t, const css_style *cs)` -- Inline-level box (CSS 2.1 9.2.2): display inline or inline-block, or a tag the UA * sheet makes inline, and not...
- `in_mixed_line` (function) `src/page_view.c:2400` `static int in_mixed_line(const lxb_dom_node_t *p, const css_sheet *sheet,
                       ...` -- True when `p` shares a line with inline content: a sibling that is non-blank text * or an inline-level element.
- `children_all_inline_block` (function) `src/page_view.c:2416` `static int children_all_inline_block(const lxb_dom_node_t *p, const css_sheet *sheet,
           ...`
- `col_has_free_space` (function) `src/page_view.c:2435` `static int col_has_free_space(const css_style *cs)` -- True iff a column can have FREE space on its main axis: a px height or a px min-height floor.
- `flex_column_flows_as_block` (function) `src/page_view.c:2446` `static int flex_column_flows_as_block(const lxb_dom_node_t *el, const css_style *cs,
            ...` -- A flex COLUMN with the initial geometry (no reverse, no wrap, justify-content start, align-items stretch) stacks...
- `fold_column_gap` (function) `src/page_view.c:2478` `static void fold_column_gap(const lxb_dom_node_t *el, css_style *cs,
                            ...` -- The gap of a column that flows as block (above) is the space BETWEEN its items (Flexbox 8.1), so every item but the...
- `is_layout_container` (function) `src/page_view.c:2502` `static int is_layout_container(const lxb_dom_node_t *el, const css_style *cs,
                   ...` -- int prev = 0; for (const lxb_dom_node_t *c = el->prev; c != NULL && !prev; c = c->prev) { if (c->type !=...
- `item_sizes_itself` (function) `src/page_view.c:2516` `static int item_sizes_itself(const lxb_dom_node_t *el, const css_style *cs,
                     ...` -- An element with a declared width (or max-width) needs a box even with no decoration: the width bounds EVERYTHING...
- `li_is_list_item` (function) `src/page_view.c:2538` `static int li_is_list_item(const lxb_dom_node_t *li, const css_sheet *sheet,
                    ...` -- A marker is generated by a `display:list-item` box (CSS Lists 3 3.1), which is what the UA sheet makes an <li>; an...
- `paints` (function) `src/page_view.c:2565` `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas vacías").
 *
 * A chil...`
- `subtree_has_own_text` (function) `src/page_view.c:2608` `static int subtree_has_own_text(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
            ...` -- True when the subtree holds no non-blank text of its own outside skipped / hidden / closed-details subtrees...
- `element_is_content_leaf` (function) `src/page_view.c:2628` `static int element_is_content_leaf(const lxb_dom_node_t *n, const css_sheet *sheet,
             ...`
- `resolve_context` (function) `src/page_view.c:2651` `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                ...`
- `outermost` (function) `src/page_view.c:2871` `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);`
- `opens` (function) `src/page_view.c:2920` `* painter applies it when the box opens (band/shared context) — seeding
             * it onto ru...`
- `margins` (function) `src/page_view.c:2948` `* margins (boxdef_from_style) and the painter applies them when
                         * it ope...`
- `container` (function) `src/page_view.c:3066` `* membership in this container (and none in any container further out,
                 * since i...`
- `walk` (function) `src/page_view.c:3150` `* far on this walk (they are all inside this element). */

                        /* The innermo...`
- `float` (function) `src/page_view.c:3243` `* genuinely nested float (oid != id) takes the deferred-column path. */
    if (cont->float_oid =...`
- `sz_count` (function) `src/page_view.c:3286` `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)` -- Serialises an element subtree (the element itself included) into a fresh NUL-terminated buffer.
- `sz_write` (function) `src/page_view.c:3300` `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)`
- `serialize_subtree` (function) `src/page_view.c:3308` `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)`
- `collapse_ws` (function) `src/page_view.c:3327` `static char *collapse_ws(const char *s, size_t n)` -- if (total == 0 || total > SV_MAX_INPUT) return NULL; char *buf = (char *)calloc(1, total + 1u); if (buf == NULL)...
- `parse_dim` (function) `src/page_view.c:3351` `static int parse_dim(const lxb_char_t *s, size_t len)` -- Parses the leading non-negative integer of an HTML length attribute value (e.g. "640", "640px", "50%").
- `present` (function) `src/page_view.c:3368` `* when no width descriptors are present (density-only or bare URLs). */
static void srcset_best_u...`
- `srcset_slot_width` (function) `src/page_view.c:3463` `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,
                              ...` -- Parses a sizes attribute ("(max-width: 600px) 100vw, 50vw") and returns the effective slot width in px for the given...
- `dimensions` (function) `src/page_view.c:3509` `* viewport dimensions (data: inline detection, <picture> <source> scanning). */
static void srcse...`
- `find_body` (function) `src/page_view.c:3541` `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)`
- `find_root_els` (function) `src/page_view.c:3554` `static pv_root_els find_root_els(lxb_dom_node_t *root)`
- `attributes` (function) `src/page_view.c:3568` `* carries those attributes (spec/css.md, "Root matcher"). */
static int root_els_match(void *ctx,...`
- `string` (function) `src/page_view.c:3579` `* Returns a heap string (caller frees) or NULL when neither carries a class —
 * NULL simply mean...`
- `forms_free` (function) `src/page_view.c:3627` `static void forms_free(form_table *ft)`
- `ascii_ieq` (function) `src/page_view.c:3634` `static int ascii_ieq(const char *s, const char *lit)` -- } form_rec; typedef struct form_table { form_rec *recs; size_t    count, cap; } form_table; static void...
- `attr_dup` (function) `src/page_view.c:3646` `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)` -- Owned NUL-terminated copy of an attribute value, or NULL when the attribute is * absent.
- `forms_add` (function) `src/page_view.c:3655` `static int forms_add(form_table *ft, const lxb_dom_node_t *node)` -- Owned NUL-terminated copy of an attribute value, or NULL when the attribute is * absent.
- `form_for` (function) `src/page_view.c:3675` `static int form_for(const form_table *ft, const lxb_dom_node_t *n,
                    const lxb_...` -- } lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)node); char *method = attr_dup(el, "method"...
- `under_unrendered` (function) `src/page_view.c:3691` `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)` -- Nonzero if a descendant text node sits under a non-rendered element (a <style> or <script> nested in the collected...
- `collect_text` (function) `src/page_view.c:3704` `static char *collect_text(const lxb_dom_node_t *el)` -- Concatenates the descendant text of el into an owned NUL-terminated string (the value of a <textarea> / the label of...
- `classify_input` (function) `src/page_view.c:3728` `static pv_input_type classify_input(const char *type)`
- `li_ordinal` (function) `src/page_view.c:3900` `static int li_ordinal(const lxb_dom_node_t *li)` -- 1-based position of an <li> among its <li> siblings (an <ol> counter, basic: the `start`/`value` attributes are out...
- `roman_marker` (function) `src/page_view.c:3926` `static void roman_marker(int n, int upper, char *out, size_t cap)` -- int k = 0; if (n < 1) n = 1; while (n > 0 && k < (int)sizeof buf) { int r = (n - 1) % 26; buf[k++] = (char)((upper ?...
- `list_marker` (function) `src/page_view.c:3951` `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,
                  ...` -- Builds the list marker for the first run of an <li>.
- `node_table_role` (function) `src/page_view.c:3992` `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)` -- The table role of an element: its computed `display` when that names one, else the role the HTML user-agent sheet...
- `nearest_table` (function) `src/page_view.c:4010` `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
 ...` -- const lxb_char_t *nm = lxb_dom_element_local_name(el, &nl); char tag[BX_TAG_NAME_MAX]; const char *tagp = NULL; if...
- `parent_is_table_internal` (function) `src/page_view.c:4044` `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)` -- Nonzero when n's DIRECT parent is table structure that is not a cell -- a table, a row group, a row or a column group.
- `nearest_cell` (function) `src/page_view.c:4071` `static const lxb_dom_node_t *nearest_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
  ...` -- if (s->type == LXB_DOM_NODE_TYPE_TEXT && text_node_is_blank(s)) continue; if (s->type == LXB_DOM_NODE_TYPE_ELEMENT...
- `cell_has_nested_table` (function) `src/page_view.c:4086` `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)` -- Nonzero if cell has a descendant table box: it is then a structural CONTAINER, not a leaf cell.
- `next_skip` (function) `src/page_view.c:4095` `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)` -- Pre-order successor that does NOT descend into n's children (used to skip an * already-decided subtree during the...
- `cell_anchors` (function) `src/page_view.c:4106` `static const lxb_dom_node_t *cell_anchors(const lxb_dom_node_t *cell, int *count)` -- First <a href> element in the cell's subtree, with *count receiving how many * such anchors exist, capped at 2 (only...
- `links` (function) `src/page_view.c:4124` `* its links (the Hacker News case: every story link lives inside a <td>), so the
 * caller flows ...`
- `flow_table` (function) `src/page_view.c:4145` `static int flow_table(pv_flow_reg *fr, const lxb_dom_node_t *table)`
- `in_flow_table_cell` (function) `src/page_view.c:4157` `static int in_flow_table_cell(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,
           ...`
- `table` (function) `src/page_view.c:4166` `* FLOW table (multi-link: walked so its links survive) do NOT suppress their
 * content -- their ...`
- `table_columns` (function) `src/page_view.c:4184` `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)` -- Grid column count of a table: the maximum number of logical columns across all its rows, computed by summing each...
- `in_hidden_subtree` (function) `src/page_view.c:4258` `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
               ...` -- Nonzero if n or any ancestor up to base has display:none (from the <style> sheet or its inline style=). display:none...
- `in_boilerplate_subtree` (function) `src/page_view.c:4275` `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` -- Nonzero if n or any ancestor up to base is page boilerplate (<nav>/<header>/ <footer>/<aside>).
- `in_closed_details_subtree` (function) `src/page_view.c:4290` `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` -- Nonzero if n or any ancestor up to base is inside a <details> without an `open` attribute and n is NOT inside its...
- `pv_build` (function) `src/page_view.c:4310` `pv_status pv_build(const hp_document *doc, pv_view **out)`
- `pv_build_ex` (function) `src/page_view.c:4314` `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)`
- `pv_build_full` (function) `src/page_view.c:4318` `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                     ...`
- `annotate_replaced_run` (function) `src/page_view.c:4340` `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,
                            ...` -- Attaches the layout membership a replaced run needs to take part in its surroundings: flex/grid container identity...
- `collect_page_css` (function) `src/page_view.c:4406` `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,
                     ...`
- `pv_build_styled` (function) `src/page_view.c:4435` `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                   ...`
- `control` (function) `src/page_view.c:4857` `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);`
- `px` (function) `src/page_view.c:5008` `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */
                if (iw <...`
- `height` (function) `src/page_view.c:5075` `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
- `block_id` (function) `src/page_view.c:5173` `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it...`
- `URL` (function) `src/page_view.c:5304` `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
- `flow` (function) `src/page_view.c:5726` `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through...`
- `engine` (function) `src/page_view.c:5826` `* layout engine (contiguous item gather) drops every cell onto its own row and
         * a 2-col...`
- `line` (function) `src/page_view.c:5835` `* to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);`
- `appended` (function) `src/page_view.c:5881` `* AFTER the run is appended (so THIS run's brk stays) but BEFORE the next. */
        if (cont.fl...`
- `pv_css_drops` (function) `src/page_view.c:5961` `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,
                       const cha...` -- Diagnostic counterpart to pv_build_styled: same document, same collected CSS text, same @media/root-scope context...

## src/pdf_export.c
Depends on: `include/pdf_export.h`
- `pe_safe_basename` (function) `src/pdf_export.c:25` `pe_status pe_safe_basename(const char *title, char *out, size_t outsz)`
- `pe_build_path_ext` (function) `src/pdf_export.c:66` `pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,
                ...`
- `pe_build_path` (function) `src/pdf_export.c:91` `pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz)`
- `pe_paginate` (function) `src/pdf_export.c:95` `size_t pe_paginate(const double *tops, const double *heights, size_t n,
                   double...`

## src/perf_trace.c
Depends on: `include/perf_trace.h`
- `pt_init` (function) `src/perf_trace.c:16` `void pt_init(pt_trace *t)`
- `pt_elapsed_us` (function) `src/perf_trace.c:21` `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us)`
- `pt_record` (function) `src/perf_trace.c:26` `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us)`
- `pt_count` (function) `src/perf_trace.c:35` `size_t pt_count(const pt_trace *t, pt_stage stage)`
- `pt_last_us` (function) `src/perf_trace.c:40` `uint64_t pt_last_us(const pt_trace *t, pt_stage stage)`
- `pt_min_us` (function) `src/perf_trace.c:49` `uint64_t pt_min_us(const pt_trace *t, pt_stage stage)`
- `pt_max_us` (function) `src/perf_trace.c:60` `uint64_t pt_max_us(const pt_trace *t, pt_stage stage)`
- `cmp_u64` (function) `src/perf_trace.c:71` `static int cmp_u64(const void *a, const void *b)`
- `pt_median_us` (function) `src/perf_trace.c:79` `uint64_t pt_median_us(const pt_trace *t, pt_stage stage)`
- `pt_stage_name` (function) `src/perf_trace.c:89` `const char *pt_stage_name(pt_stage stage)`
- `pt_format` (function) `src/perf_trace.c:109` `size_t pt_format(const pt_trace *t, char *buf, size_t cap)`

## src/prefetch.c
Depends on: `include/prefetch.h`
- `is_ws` (function) `src/prefetch.c:23` `static int is_ws(char c)`
- `is_name_char` (function) `src/prefetch.c:27` `static int is_name_char(char c)`
- `lower` (function) `src/prefetch.c:32` `static int lower(int c)`
- `ci_starts` (function) `src/prefetch.c:37` `static int ci_starts(const char *p, const char *end, const char *kw)` -- static int is_ws(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'; } static int...
- `ci_find` (function) `src/prefetch.c:46` `static const char *ci_find(const char *p, const char *end, const char *kw)` -- static int lower(int c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; } /* Case-insensitive: [p,end) starts...
- `ci_eq_span` (function) `src/prefetch.c:55` `static int ci_eq_span(const char *s, size_t n, const char *kw)`
- `emit` (function) `src/prefetch.c:117` `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)`
- `pf_scan` (function) `src/prefetch.c:130` `int pf_scan(const char *html, size_t len, pf_list *out)`
- `pf_list_free` (function) `src/prefetch.c:193` `void pf_list_free(pf_list *l)`
- `pf_worker` (function) `src/prefetch.c:201` `static void *pf_worker(void *arg)`
- `pf_pool_start` (function) `src/prefetch.c:227` `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                  pf_fetch_f...`
- `pf_pool_take` (function) `src/prefetch.c:271` `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,
                 char **body,...`
- `pf_pool_finish` (function) `src/prefetch.c:310` `void pf_pool_finish(pf_pool *p)`
- `pf_pooled_fetch` (function) `src/prefetch.c:324` `int pf_pooled_fetch(void *vctx, const char *method, const char *url,
                    const ch...`

## src/prefs.c
Depends on: `include/prefs.h`, `include/zoom.h`
- `url_valid` (function) `src/prefs.c:26` `static int url_valid(const char *url)` -- A representable URL: 1..PREFS_MAX_URL-1 bytes, no control bytes, no DEL. * Space is allowed (local paths may carry...
- `title_clean` (function) `src/prefs.c:39` `static char *title_clean(const char *src)` -- Copies src into a fresh buffer, mapping control bytes/DEL to ' ' and truncating to PREFS_MAX_TITLE bytes on a UTF-8...
- `prefs_init` (function) `src/prefs.c:66` `void prefs_init(prefs_state *p)`
- `prefs_free` (function) `src/prefs.c:74` `void prefs_free(prefs_state *p)`
- `bookmark_push` (function) `src/prefs.c:91` `static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title)` -- Appends a cleaned bookmark.
- `history_push_back` (function) `src/prefs.c:109` `static prefs_status history_push_back(prefs_state *p, const char *url)` -- Appends a history entry at the BACK preserving document order (parser path; * the API path inserts at the front).
- `prefs_bookmark_index` (function) `src/prefs.c:125` `int prefs_bookmark_index(const prefs_state *p, const char *url)`
- `prefs_bookmark_toggle` (function) `src/prefs.c:132` `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,
                             ...`
- `prefs_history_add` (function) `src/prefs.c:152` `prefs_status prefs_history_add(prefs_state *p, const char *url)`
- `prefs_format` (function) `src/prefs.c:183` `prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len)`
- `apply_kv` (function) `src/prefs.c:225` `static void apply_kv(prefs_state *out, const char *key, long val)` -- } for (size_t i = 0; i < p->history_len; ++i) { size_t space = cap - n; if (space == 0) break; int r = snprintf(buf...
- `prefs_parse` (function) `src/prefs.c:241` `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)`
- `ci_eq` (function) `src/prefs.c:300` `static int ci_eq(char a, char b)`
- `ci_starts` (function) `src/prefs.c:306` `static int ci_starts(const char *s, const char *q)`
- `ci_contains` (function) `src/prefs.c:314` `static int ci_contains(const char *s, const char *q)`
- `url_prefix_match` (function) `src/prefs.c:323` `static int url_prefix_match(const char *url, const char *q)` -- Prefix match as the user types it: the raw URL, past the scheme, and past a * leading "www." ("wiki" hits...
- `sugg_push` (function) `src/prefs.c:335` `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,
                      cons...` -- Prefix match as the user types it: the raw URL, past the scheme, and past a * leading "www." ("wiki" hits...
- `prefs_suggest` (function) `src/prefs.c:344` `int prefs_suggest(const prefs_state *p, const char *query,
                  char *out, size_t ro...`
- `sb_put` (function) `src/prefs.c:369` `static void sb_put(sbuf *b, const char *s, size_t n)`
- `sb_str` (function) `src/prefs.c:384` `static void sb_str(sbuf *b, const char *s)`
- `sb_esc` (function) `src/prefs.c:387` `static void sb_esc(sbuf *b, const char *s)` -- while (nc < b->len + n + 1) nc *= 2; char *nd = (char *)realloc(b->data, nc); if (nd == NULL) { b->oom = 1; return...
- `sb_link_item` (function) `src/prefs.c:400` `static void sb_link_item(sbuf *b, const char *url, const char *label)`
- `prefs_bookmarks_page` (function) `src/prefs.c:408` `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)`

## src/profile.c
Depends on: `include/disk_store.h`, `include/profile.h`
- `join_path` (function) `src/profile.c:29` `static int join_path(const profile_ctx *ctx, const char *name,
                     char *out, si...`
- `keyfile_create` (function) `src/profile.c:36` `static profile_status keyfile_create(const char *dir, const char *path,
                         ...` -- #include <unistd.h> #include <openssl/crypto.h> #include <openssl/rand.h> #define PROFILE_KEYFILE_LEN (LS_SALT_LEN +...
- `profile_open` (function) `src/profile.c:59` `profile_status profile_open(profile_ctx *ctx, const char *dir)`
- `map_ds` (function) `src/profile.c:98` `static profile_status map_ds(ds_status ds)`
- `profile_load` (function) `src/profile.c:112` `profile_status profile_load(const profile_ctx *ctx, prefs_state *out)`
- `profile_save` (function) `src/profile.c:133` `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p)`
- `profile_close` (function) `src/profile.c:149` `void profile_close(profile_ctx *ctx)`

## src/render_doc.c
Depends on: `include/box_style.h`, `include/css.h`, `include/data_url.h`, `include/render_doc.h`, `include/url.h`, `include/util.h`
- `utf8_sanitized_dup` (function) `src/render_doc.c:28` `static char *utf8_sanitized_dup(const char *s)`
- `rd_push` (function) `src/render_doc.c:60` `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,
                 ...` -- Appends one block, taking owned copies of text (required) and href (optional). * Returns 0 on success, -1 on...
- `rd_push_input` (function) `src/render_doc.c:195` `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` -- Appends an RD_INPUT block, copying text (placeholder/label), the form action * (href), and the control name/value.
- `place` (function) `src/render_doc.c:220` `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never...`
- `resolve_image_decision` (function) `src/render_doc.c:230` `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,
        ...` -- Resolves raw_src (possibly relative, or a data: URI) against top_level_url and judges it under the exact same policy...
- `rd_build` (function) `src/render_doc.c:252` `rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_u...`
- `unset` (function) `src/render_doc.c:619` `* background paints as if unset (no border/box-shadow-style
                 * "broken image" pla...`
- `rd_free` (function) `src/render_doc.c:684` `void rd_free(rd_doc *d)`
- `rd_count` (function) `src/render_doc.c:700` `size_t rd_count(const rd_doc *d)`
- `rd_at` (function) `src/render_doc.c:704` `const rd_block *rd_at(const rd_doc *d, size_t i)`
- `rd_box_count` (function) `src/render_doc.c:709` `size_t rd_box_count(const rd_doc *d)`
- `rd_box_at` (function) `src/render_doc.c:713` `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)`
- `rd_cont_count` (function) `src/render_doc.c:718` `size_t rd_cont_count(const rd_doc *d)`
- `rd_cont_at` (function) `src/render_doc.c:722` `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)`
- `rd_kind_name` (function) `src/render_doc.c:727` `const char *rd_kind_name(rd_kind k)`
- `rd_block_tag` (function) `src/render_doc.c:741` `const char *rd_block_tag(const rd_block *b)`
- `rd_input_label` (function) `src/render_doc.c:772` `const char *rd_input_label(int input_type)`
- `rd_input_invisible` (function) `src/render_doc.c:792` `int rd_input_invisible(int input_type)`
- `rd_image_label` (function) `src/render_doc.c:796` `const char *rd_image_label(rdp_img_decision d)`
- `rd_image_fail_label` (function) `src/render_doc.c:807` `const char *rd_image_fail_label(img_fail_reason reason)`

## src/render_policy.c
Depends on: `include/data_url.h`, `include/render_policy.h`, `include/request_policy.h`
- `rdp_caps_safe` (function) `src/render_policy.c:17` `rdp_caps rdp_caps_safe(void)`
- `rdp_is_tracking_pixel` (function) `src/render_policy.c:22` `int rdp_is_tracking_pixel(int w, int h)`
- `rdp_image_decision` (function) `src/render_policy.c:28` `rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char...`
- `rdp_img_reason` (function) `src/render_policy.c:63` `const char *rdp_img_reason(rdp_img_decision d)`
- `rdp_images_warning` (function) `src/render_policy.c:74` `const char *rdp_images_warning(void)`

## src/renderer.c
Depends on: `include/html_parse.h`, `include/os_sandbox.h`, `include/renderer.h`, `include/util.h`
- `child_render` (function) `src/renderer.c:25` `static void child_render(int wfd, const char *html, size_t len)`
- `write_full` (function) `src/renderer.c:40` `&& write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 || write_full(wfd, title, tl) == 0) && write_full(wfd, &xl...`
- `read_field` (function) `src/renderer.c:53` `static int read_field(int fd, char **out, size_t *out_len)`
- `rd_render_html` (function) `src/renderer.c:70` `rd_status rd_render_html(const char *html, size_t len, rd_result *out)`
- `rd_result_free` (function) `src/renderer.c:120` `void rd_result_free(rd_result *out)`

## src/request_policy.c
Depends on: `include/psl_data.h`, `include/request_policy.h`
- `lower` (function) `src/request_policy.c:22` `static char lower(char c)`
- `ci_starts_with` (function) `src/request_policy.c:26` `static int ci_starts_with(const char *s, const char *prefix)`
- `psl_cmp` (function) `src/request_policy.c:36` `static int psl_cmp(const void *key, const void *elem)`
- `psl_in` (function) `src/request_policy.c:40` `static int psl_in(const char *const *arr, size_t n, const char *key)`
- `public_suffix_labels` (function) `src/request_policy.c:48` `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)` -- Number of labels of the public suffix (eTLD) of a lowercased host, applying the full PSL algorithm: exception rules...
- `rp_host_of` (function) `src/request_policy.c:76` `int rp_host_of(const char *url, char *out, size_t out_size)`
- `rp_site_of` (function) `src/request_policy.c:102` `int rp_site_of(const char *host, char *out, size_t out_size)`
- `rp_same_site` (function) `src/request_policy.c:134` `int rp_same_site(const char *top_level_url, const char *request_url)`
- `rp_evaluate` (function) `src/request_policy.c:143` `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)`

## src/secure_fetch.c
Depends on: `include/anti_fp.h`, `include/secure_fetch.h`, `include/url.h`
- `ci_starts_with` (function) `src/secure_fetch.c:44` `static int ci_starts_with(const char *haystack, const char *prefix)` -- /* --- small helpers (no libc locale dependence) --- static int ci_equal(const char *a, const char *b) { while (*a...
- `ci_index` (function) `src/secure_fetch.c:56` `static long ci_index(const char *haystack, const char *needle)` -- /* Case-insensitive: does haystack start with prefix? static int ci_starts_with(const char *haystack, const char...
- `sf_share_lock` (function) `src/secure_fetch.c:68` `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...`
- `sf_share_unlock` (function) `src/secure_fetch.c:74` `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)`
- `sf_global_init` (function) `src/secure_fetch.c:81` `void sf_global_init(void)`
- `sf_cookie_line_matches` (function) `src/secure_fetch.c:96` `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...`
- `sf_url_host_path` (function) `src/secure_fetch.c:151` `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...` -- Extracts host + path from a validated https url into caller buffers (path defaults * to "/").
- `sf_cookie_header_for` (function) `src/secure_fetch.c:166` `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)`
- `sf_cookie_put` (function) `src/secure_fetch.c:195` `void sf_cookie_put(const char *url, const char *namevalue)`
- `sf_config_default` (function) `src/secure_fetch.c:216` `sf_config sf_config_default(void)`
- `sf_user_agent_or_default` (function) `src/secure_fetch.c:241` `const char *sf_user_agent_or_default(const char *ua)`
- `sf_impersonate_kex_groups` (function) `src/secure_fetch.c:245` `const char *sf_impersonate_kex_groups(void)`
- `sf_impersonate_tls13_ciphers` (function) `src/secure_fetch.c:246` `const char *sf_impersonate_tls13_ciphers(void)`
- `sf_validate_url` (function) `src/secure_fetch.c:250` `sf_status sf_validate_url(const char *url)`
- `sf_url_is_http` (function) `src/secure_fetch.c:258` `static int sf_url_is_http(const char *url)` -- Nonzero iff url is "http://host..." (case-insensitive) with a non-empty host.
- `sf_check_tls_version` (function) `src/secure_fetch.c:270` `sf_status sf_check_tls_version(const char *negotiated_version)`
- `sf_check_group_is_pq` (function) `src/secure_fetch.c:275` `sf_status sf_check_group_is_pq(const char *negotiated_group)`
- `sf_check_chain_policy` (function) `src/secure_fetch.c:284` `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)`
- `sf_enforce_policy` (function) `src/secure_fetch.c:294` `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...`
- `copy_checked` (function) `src/secure_fetch.c:325` `static int copy_checked(char *dst, size_t dstsz, const char *src)`
- `sf_is_redirect_code` (function) `src/secure_fetch.c:334` `int sf_is_redirect_code(long http_code)`
- `sf_parse_location_header` (function) `src/secure_fetch.c:341` `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)`
- `sf_resolve_redirect` (function) `src/secure_fetch.c:359` `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...`
- `module` (function) `src/secure_fetch.c:364` `* pure url module (DRY);`
- `sf_ci_prefix` (function) `src/secure_fetch.c:371` `static int sf_ci_prefix(const char *s, const char *p)` -- Reference resolution + the https-only / no-downgrade policy live in the pure url module (DRY); a redirect is just a...
- `sf_response_free` (function) `src/secure_fetch.c:411` `void sf_response_free(sf_response *resp)`
- `progress` (function) `src/secure_fetch.c:443` `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);`
- `copy_bounded` (function) `src/secure_fetch.c:470` `static void copy_bounded(char *dst, size_t dstsz, const char *src)`
- `get_negotiated_group_name` (function) `src/secure_fetch.c:481` `static const char *get_negotiated_group_name(SSL *ssl)` -- static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len); static void...
- `database` (function) `src/secure_fetch.c:485` `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid...`
- `group` (function) `src/secure_fetch.c:499` `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);`
- `tls_capture_try` (function) `src/secure_fetch.c:514` `static void tls_capture_try(tls_capture *cap)` -- nid = SSL_get_shared_group(ssl, 0); #endif if (nid == 0) { return NULL; /* There is no negotiated group (e.g., TLS...
- `tls_capture_from_ssl` (function) `src/secure_fetch.c:524` `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)` -- static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl); /* Idempotent: takes the TLS snapshot the first time...
- `this` (function) `src/secure_fetch.c:531` `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and...`
- `header_cb` (function) `src/secure_fetch.c:550` `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` -- Fires for every HTTP response (status line + headers) even when there is no * body, so it is the reliable point to...
- `write_cb` (function) `src/secure_fetch.c:586` `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)`
- `name_is_pq_sig` (function) `src/secure_fetch.c:618` `static int name_is_pq_sig(int pknid)` -- if (grown == NULL) { sink->overflow = 2; /* OOM marker return 0; } sink->data = grown; sink->cap = newcap; }...
- `inspect_chain` (function) `src/secure_fetch.c:628` `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` -- Walks the verified chain into *info. sigbuf receives the leaf signature alg name. * Returns 0 on success, nonzero if...
- `map_curl_error` (function) `src/secure_fetch.c:681` `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)`
- `add_header` (function) `src/secure_fetch.c:722` `static int add_header(struct curl_slist **h, const char *line)` -- Appends one header line without losing the list on OOM (the plain "h = curl_slist_append(h, ...)" idiom dropped the...
- `sf_setup_handle` (function) `src/secure_fetch.c:736` `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,
           ...` -- The ONE place a curl handle is configured for a request (spec/secure_fetch.md): URL, realm proxy, TLS floor + KE...
- `redirect` (function) `src/secure_fetch.c:811` `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...`
- `sf_perform` (function) `src/secure_fetch.c:879` `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...` -- The shared request engine for sf_get and sf_post.
- `sf_get` (function) `src/secure_fetch.c:1014` `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)`
- `sf_post` (function) `src/secure_fetch.c:1018` `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...`
- `sf_get_follow` (function) `src/secure_fetch.c:1032` `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...`
- `ws_ssl_info_cb` (function) `src/secure_fetch.c:1084` `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)` -- An upgraded (CONNECT_ONLY) connection never runs the header callback that snapshots TLS for a fetch, and curl no...
- `ws_ssl_ctx_cb` (function) `src/secure_fetch.c:1091` `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)`
- `sf_ws_url_check` (function) `src/secure_fetch.c:1105` `sf_status sf_ws_url_check(const char *url)`
- `ws_free` (function) `src/secure_fetch.c:1117` `static void ws_free(sf_ws *ws)`
- `sf_ws_open` (function) `src/secure_fetch.c:1126` `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)`
- `sf_ws_send` (function) `src/secure_fetch.c:1181` `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)`
- `sf_ws_recv` (function) `src/secure_fetch.c:1204` `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)`
- `sf_ws_fd` (function) `src/secure_fetch.c:1226` `int sf_ws_fd(const sf_ws *ws)`
- `sf_ws_close` (function) `src/secure_fetch.c:1233` `void sf_ws_close(sf_ws *ws)`


Next: [API_p9.md](API_p9.md)
