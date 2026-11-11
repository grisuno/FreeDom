# Subsystem: src (page 4 of 10)
Previous: [KB_src_p3.md](KB_src_p3.md)

## src/dom.c
- Doc: to_lower_buf: #include <stdint.h> #include <stdlib.h> #include <string.h> #include...
- Layer: utility
- Language: c
- Symbols:
  - `sm_entry` (struct, line 55)
  - `strmap` (struct, line 64)
  - `pm_entry` (struct, line 154)
  - `ptrmap` (struct, line 160)
  - `dom_index` (struct, line 220)
  - `ih_block` (struct, line 850)
  - `ih_acc` (struct, line 855)
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
  - `node_in_document` (function, line 352) `static int node_in_document(const lxb_dom_node_t *node)`
  - `dom_get_element_by_id` (function, line 358) `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)`
  - `dom_get_connected_by_id` (function, line 364) `dom_node_id dom_get_connected_by_id(const dom_index *idx, const char *id)`
  - `copy_ids` (function, line 387) `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)`
  - `dom_get_by_tag` (function, line 394) `size_t dom_get_by_tag(const dom_index *idx, const char *tag,
                      dom_node_id *o...`
  - `dom_get_by_class` (function, line 403) `size_t dom_get_by_class(const dom_index *idx, const char *cls,
                        dom_node_i...`
  - `id_of` (function, line 416) `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)`
  - `parse_selector_list` (function, line 426) `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)`
  - `node_matches_any` (function, line 459) `static int node_matches_any(const lxb_dom_node_t *cn,
                            const css_sel *...`
  - `count` (function, line 467) `* count (may exceed cap), and returns DOM_NODE_NONE. */
static dom_node_id qs_walk(const dom_inde...`
  - `dom_query_selector` (function, line 497) `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,
                          ...`
  - `dom_query_selector_all` (function, line 506) `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,
                           ...`
  - `dom_matches` (function, line 517) `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)`
  - `dom_closest` (function, line 526) `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,
                        const cha...`
  - `dom_document_position` (function, line 542) `size_t dom_document_position(const dom_index *idx, dom_node_id node)`
  - `dom_precedes` (function, line 547) `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)`
  - `dom_node_at` (function, line 552) `dom_node_id dom_node_at(const dom_index *idx, size_t position)`
  - `dom_parent` (function, line 557) `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)`
  - `dom_first_child` (function, line 567) `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)`
  - `dom_next_sibling` (function, line 575) `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)`
  - `dom_tag_name` (function, line 583) `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)`
  - `dom_get_attribute` (function, line 594) `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,
                           ...`
  - `dom_attribute_names` (function, line 616) `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,
                           con...`
  - `dom_text_content` (function, line 634) `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)`
  - `dom_document_title` (function, line 644) `const char *dom_document_title(const dom_index *idx, size_t *len)`
  - `dom_set_text_content` (function, line 657) `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,
                               ...`
  - `dom_set_document_title` (function, line 691) `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)`
  - `idx_push` (function, line 702) `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)`
  - `dom_create_element` (function, line 720) `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)`
  - `dom_append_child` (function, line 740) `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
  - `dom_remove_child` (function, line 754) `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
  - `dom_set_attribute` (function, line 762) `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,
                             const...`
  - `dom_remove_attribute` (function, line 791) `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)`
  - `index_subtree` (function, line 800) `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)`
  - `dom_set_inner_html` (function, line 810) `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,
                              con...`
  - `ih_append` (function, line 863) `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)`
  - `ih_free` (function, line 890) `static void ih_free(ih_acc *a)`
  - `dom_get_inner_html` (function, line 917) `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,
                           ...`
  - `dom_insert_before` (function, line 947) `dom_status dom_insert_before(dom_index *idx, dom_node_id parent, dom_node_id child,
             ...`
  - `dom_clone_node` (function, line 964) `dom_status dom_clone_node(dom_index *idx, dom_node_id node, int deep, dom_node_id *out_id)`
  - `dom_move_children` (function, line 978) `dom_status dom_move_children(dom_index *idx, dom_node_id src, dom_node_id parent,
               ...`
  - `char_kind` (function, line 1011) `static int char_kind(const lxb_dom_node_t *n)`
  - `handle_of` (function, line 1022) `static dom_node_id handle_of(dom_index *idx, lxb_dom_node_t *n)`
  - `dom_node_kind` (function, line 1030) `int dom_node_kind(const dom_index *idx, dom_node_id node)`
  - `dom_child_node` (function, line 1034) `dom_node_id dom_child_node(dom_index *idx, dom_node_id node, int last)`
  - `dom_sibling_node` (function, line 1041) `dom_node_id dom_sibling_node(dom_index *idx, dom_node_id node, int prev)`
  - `dom_create_char_node` (function, line 1048) `dom_status dom_create_char_node(dom_index *idx, int kind, const char *text, size_t len,
         ...`
  - `dom_native_node` (function, line 1062) `const void *dom_native_node(const dom_index *idx, dom_node_id node)`
  - `_POSIX_C_SOURCE` (macro, line 11) `#define _POSIX_C_SOURCE`
  - `DOM_QS_MAX_SELECTORS` (macro, line 413) `#define DOM_QS_MAX_SELECTORS`
  - `IH_BLOCK_SIZE` (macro, line 848) `#define IH_BLOCK_SIZE`
- Depends on: `include/css_chain.h`, `include/css_select.h`, `include/dom.h`, `include/html_parse.h`, `include/util.h`

## src/dom_debug.c
- Doc: dd_cursor: Bounded write cursor: `pos` bytes are committed to `out` (always leaving room for the...
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
  - `dd_overflow_name` (function, line 157) `static const char *dd_overflow_name(int o)`
  - `dd_cursor_name` (function, line 166) `static const char *dd_cursor_name(int c)`
  - `dd_text_overflow_name` (function, line 199) `static const char *dd_text_overflow_name(int t)`
  - `dd_inset` (function, line 204) `static int dd_inset(int v)`
  - `dd_object_fit_name` (function, line 208) `static const char *dd_object_fit_name(int o)`
  - `dd_image_rendering_name` (function, line 219) `static const char *dd_image_rendering_name(int r)`
  - `dd_border_style_name` (function, line 228) `static const char *dd_border_style_name(int s)`
  - `dd_box_line` (function, line 261) `static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b)`
  - `dd_block_line` (function, line 323) `static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b)`
  - `dd_format` (function, line 400) `size_t dd_format(const rd_doc *doc, char *out, size_t cap)`
  - `dd_format_css` (function, line 432) `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)`
- Depends on: `include/box_style.h`, `include/css.h`, `include/dom_debug.h`, `include/flex_layout.h`, `include/page_view.h`

## src/download.c
- Doc: lc: download — pure helpers for "save this resource to disk".
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

## src/fb_cmdline.c
- Layer: utility
- Language: c
- Symbols:
  - `dup_n` (function, line 10) `static char *dup_n(const char *s, size_t n)`
  - `fbc_history_init` (function, line 19) `void fbc_history_init(fbc_history *h)`
  - `fbc_history_free` (function, line 23) `void fbc_history_free(fbc_history *h)`
  - `fbc_history_push` (function, line 32) `int fbc_history_push(fbc_history *h, const char *text, size_t len)`
  - `fbc_history_prev` (function, line 53) `const char *fbc_history_prev(fbc_history *h, const char *cur, size_t curlen)`
  - `fbc_history_next` (function, line 63) `const char *fbc_history_next(fbc_history *h)`
  - `path_char` (function, line 70) `static int path_char(char c)`
  - `fbc_complete_split` (function, line 74) `long fbc_complete_split(const char *text, size_t n, char *base, size_t cap, size_t *prefix_off)`
  - `fbc_names_expr` (function, line 95) `size_t fbc_names_expr(const char *base, char *out, size_t cap)`
  - `fbc_complete_pick` (function, line 118) `size_t fbc_complete_pick(const char *names, const char *prefix, size_t plen,
                    ...`
  - `fbc_filter_passes` (function, line 159) `int fbc_filter_passes(int filter, int level)`
  - `fbc_filter_next` (function, line 168) `int fbc_filter_next(int filter)`
  - `fbc_filter_label` (function, line 173) `const char *fbc_filter_label(int filter)`
- Depends on: `include/fb_cmdline.h`, `include/fb_panes.h`, `include/freebug.h`

## src/fb_panes.c
- Layer: utility
- Language: c
- Symbols:
  - `tab_ok` (function, line 110) `static int tab_ok(int tab)`
  - `fbp_tab_label` (function, line 112) `const char *fbp_tab_label(int tab)`
  - `ieq` (function, line 114) `static int ieq(const char *a, const char *b)`
  - `fbp_tab_from_name` (function, line 123) `int fbp_tab_from_name(const char *name)`
  - `fbp_tab_wrap` (function, line 130) `int fbp_tab_wrap(int tab, int dir)`
  - `fbp_tab_span` (function, line 136) `void fbp_tab_span(int tab, double cell_w, double pad_cells, double *x, double *w)`
  - `fbp_tab_at` (function, line 145) `int fbp_tab_at(double px, double cell_w, double pad_cells)`
  - `fbp_is_pane` (function, line 155) `int fbp_is_pane(int tab)`
  - `fbp_js_quote` (function, line 157) `size_t fbp_js_quote(const char *s, size_t n, char *out, size_t cap)`
  - `fbp_expr` (function, line 186) `size_t fbp_expr(int tab, const char *sel, size_t n, char *out, size_t cap)`
- Depends on: `include/fb_panes.h`

## src/flex_layout.c
- Doc: nn: bounded by FX_MAX_ITEMS (no VLAs).
- Layer: presentation
- Language: c
- Symbols:
  - `nn` (function, line 19) `static double nn(double v)`
  - `fx_flex_line` (function, line 23) `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                ...`
  - `fx_grid_columns` (function, line 128) `fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          doubl...`
  - `fx_grid_column_count` (function, line 133) `int fx_grid_column_count(int flow, int cols, int rows, size_t items)`
  - `fx_autofill_count` (function, line 141) `size_t fx_autofill_count(double avail, double gap, double minw)`
  - `fx_grid_columns_weighted` (function, line 151) `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                      ...`
  - `fx_grid_place_span` (function, line 185) `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                      ...`
  - `fx_grid_area_hash` (function, line 327) `unsigned fx_grid_area_hash(const char *name)`
  - `area_token_is_null_cell` (function, line 351) `static int area_token_is_null_cell(const char *tok, size_t len)`
  - `fx_grid_areas_parse` (function, line 357) `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)`
  - `fx_grid_area_rect` (function, line 432) `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,
                            int ...`
  - `float_pack_impl` (function, line 474) `static fx_status float_pack_impl(const double *width, const int *side, size_t n,
                ...`
  - `fx_float_insets` (function, line 514) `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,
                 ...`
  - `fx_float_pack` (function, line 554) `fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        d...`
  - `fx_float_pack_wrap` (function, line 559) `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,
                    ...`
  - `fx_grid_cell` (function, line 601) `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)`
  - `fx_auto_margins` (function, line 613) `fx_status fx_auto_margins(fx_result *res, size_t n, const unsigned char *auto_l,
                ...`
  - `fx_auto_min_size` (function, line 636) `double fx_auto_min_size(double min_content, double basis, double author_min,
                    ...`
  - `fx_multicol_used` (function, line 653) `fx_status fx_multicol_used(double avail_w, int column_count, double column_width,
               ...`
  - `fx_multicol_balance` (function, line 690) `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,
                        ...`
  - `fx_justify_name` (function, line 721) `const char *fx_justify_name(fx_justify j)`
  - `fx_column_place` (function, line 733) `fx_status fx_column_place(const double *h, const double *grow, size_t n, double gap,
            ...`
  - `fx_column_place_m` (function, line 740) `fx_status fx_column_place_m(const double *h, const double *grow, const int *mauto,
              ...`
  - `fx_cross_offset` (function, line 801) `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r)`
  - `gl_ws` (function, line 813) `static int gl_ws(char c)`
  - `gl_lower` (function, line 817) `static int gl_lower(char c)`
  - `gl_kw` (function, line 820) `static int gl_kw(const char *p, const char *end, const char *kw)`
  - `gl_int` (function, line 830) `static int gl_int(const char *p, const char *end, long cap, long *out)`
  - `gl_side_range` (function, line 845) `static int gl_side_range(const char *p, const char *end, int *out)`
  - `fx_grid_line_side` (function, line 868) `int fx_grid_line_side(const char *s, int *out)`
  - `fx_grid_line_parse` (function, line 876) `int fx_grid_line_parse(const char *v, int *start, int *end)`
  - `gl_is_span` (function, line 893) `static int gl_is_span(int v)`
  - `gl_is_line` (function, line 894) `static int gl_is_line(int v)`
  - `fx_grid_line_resolve` (function, line 896) `void fx_grid_line_resolve(int start, int end, int ntracks, int *pos0, int *span)`
  - `fx_col_free_split` (function, line 938) `fx_status fx_col_free_split(double free_px, const int *grow, const int *mauto, size_t n,
        ...`
  - `FX_EPS` (macro, line 16) `#define FX_EPS`
- Depends on: `include/flex_layout.h`

## src/form.c
- Doc: put_char: No I/O, no global state.
- Layer: utility
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

## src/frame_broker.c
- Doc: target_admits: int changed = 1;                                  /* fixpoint: slots are reused...
- Layer: utility
- Language: c
- Symbols:
  - `lc` (function, line 9) `static char lc(char c)`
  - `host_char_ok` (function, line 11) `static int host_char_ok(char c)`
  - `fbk_origin_of` (function, line 15) `int fbk_origin_of(const char *url, char *out, size_t cap)`
  - `fbk_init` (function, line 53) `int fbk_init(fbk_table *t, const char *top_url)`
  - `live` (function, line 62) `static int live(const fbk_table *t, int id)`
  - `fbk_add` (function, line 66) `int fbk_add(fbk_table *t, int parent, const char *url, int *out_id)`
  - `fbk_remove` (function, line 84) `void fbk_remove(fbk_table *t, int id)`
  - `fbk_origin` (function, line 96) `const char *fbk_origin(const fbk_table *t, int id)`
  - `target_admits` (function, line 101) `static int target_admits(const char *target, const char *snd, const char *recv)`
  - `fbk_route` (function, line 118) `fbk_verdict fbk_route(const fbk_table *t, int from, fbk_rel rel, int child,
                     ...`
- Depends on: `include/frame_broker.h`

## src/frame_clock.c
- Layer: utility
- Language: c
- Symbols:
  - `fc_set_active` (function, line 16) `void fc_set_active(fc_clock *c, int active)`
  - `fc_needs_tick` (function, line 21) `int fc_needs_tick(const fc_clock *c)`
  - `fc_interval_ms` (function, line 26) `int fc_interval_ms(const fc_clock *c)`
  - `FC_DEFAULT_INTERVAL_MS` (macro, line 8) `#define FC_DEFAULT_INTERVAL_MS`
- Depends on: `include/frame_clock.h`

## src/frame_host.c
- Doc: reap: h->fetch = fetch; h->fetch_ctx = fetch_ctx; h->top_msg = top_msg; h->top_ctx = top_ctx...
- Layer: utility
- Language: c
- Symbols:
  - `fh_slot` (struct, line 14)
  - `fh_host` (struct, line 22)
  - `fh_new` (function, line 35) `fh_host *fh_new(const char *top_url, tab_fetch_fn fetch, void *fetch_ctx,
                fh_top_...`
  - `slot_release_view` (function, line 47) `static void slot_release_view(fh_slot *sl)`
  - `reap` (function, line 55) `static void reap(fh_host *h)`
  - `fh_free` (function, line 67) `void fh_free(fh_host *h)`
  - `fh_count` (function, line 76) `int fh_count(const fh_host *h)`
  - `load_frame` (function, line 85) `static void load_frame(fh_host *h, int id, const char *url)`
  - `find_child` (function, line 129) `static int find_child(const fh_host *h, int parent, int token)`
  - `token_seen_by` (function, line 137) `static int token_seen_by(const fh_host *h, int dest, int from)`
  - `post_op` (function, line 143) `static void post_op(fh_host *h, int from, const tab_ws_op *op)`
  - `apply_ops` (function, line 198) `static void apply_ops(fh_host *h, int from, const tab_ws_op *ops, size_t n)`
  - `fh_apply_top` (function, line 221) `void fh_apply_top(fh_host *h, const tab_page *page)`
  - `fh_tick` (function, line 226) `int fh_tick(fh_host *h, int elapsed_ms)`
  - `fh_generation` (function, line 250) `unsigned fh_generation(const fh_host *h)`
  - `fh_frame_view` (function, line 252) `const pv_view *fh_frame_view(const fh_host *h, const char *url, tab **t_out)`
- Depends on: `include/frame_broker.h`, `include/frame_host.h`

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
- Doc: hl_frames: Frames of a trusted page, headless: the same frame_host the window drives, so the...
- Layer: utility
- Language: c
- Symbols:
  - `hl_frames` (struct, line 210)
  - `hl_font_stash` (struct, line 634)
  - `print_usage` (function, line 55) `static void print_usage(FILE *fp, const char *prog)`
  - `is_https_url` (function, line 84) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 88) `static int is_http_url(const char *s)`
  - `is_overlay_http` (function, line 93) `static int is_overlay_http(const char *s)`
  - `now_us` (function, line 149) `static uint64_t now_us(void)`
  - `timings_ensure_init` (function, line 155) `static void timings_ensure_init(void)`
  - `timings_enabled` (function, line 159) `static int timings_enabled(void)`
  - `timings_dump` (function, line 163) `static void timings_dump(void)`
  - `hl_frame_top_msg` (function, line 215) `static void hl_frame_top_msg(void *ctx, const char *data, size_t len)`
  - `user_impersonate_enabled` (function, line 236) `static int user_impersonate_enabled(void)`
  - `read_file` (function, line 243) `static char *read_file(const char *path, size_t *out_len)`
  - `headless_load_hosts` (function, line 261) `static void headless_load_hosts(void)`
  - `apply_identity` (function, line 281) `static void apply_identity(sf_config *cfg)`
  - `apply_as_gui` (function, line 286) `static void apply_as_gui(const char *top_url, int flag_js, int flag_css, int flag_images)`
  - `is_blank_text` (function, line 324) `static int is_blank_text(const char *s)`
  - `print_doc` (function, line 337) `static void print_doc(const rd_doc *doc)`
  - `print_console` (function, line 430) `static void print_console(const fb_buffer *log)`
  - `print_dom` (function, line 447) `static void print_dom(const rd_doc *doc)`
  - `print_dom_css` (function, line 462) `static void print_dom_css(const rd_doc *doc)`
  - `headless_fetch` (function, line 486) `static int headless_fetch(void *ctx, const char *method, const char *url,
                       ...`
  - `foldback_cookies` (function, line 573) `static void foldback_cookies(const char *url, const char *jar)`
  - `print_css_drops` (function, line 597) `static void print_css_drops(const char *html, size_t len)`
  - `hl_font_stash_free` (function, line 642) `static void hl_font_stash_free(hl_font_stash *s)`
  - `hl_css_sink` (function, line 655) `static void hl_css_sink(void *vctx, const char *url,
                        const char *body, si...`
  - `hl_font_fetch` (function, line 692) `static int hl_font_fetch(void *vctx, const char *url,
                         int *out_status, c...`
  - `render_page` (function, line 720) `static int render_page(const char *html, size_t len, const char *top_url,
                       ...`
  - `first` (function, line 798) `* always cleared first (fetch_and_render may paint several pages per
     * process). A NULL top_...`
  - `sf_reason` (function, line 994) `static const char *sf_reason(sf_status ss)`
  - `fetch_and_render_one` (function, line 1014) `static int fetch_and_render_one(const char *url, char **out_nav)`
  - `elsewhere` (function, line 1077) `* page whose script immediately forwards elsewhere (e.g. a search engine's
 * JS-capability inter...`
  - `parent` (function, line 1103) `* gated by the parent (ln_resolve: a local target stays under the document's
 * directory, a remo...`
  - `run_headless` (function, line 1140) `static int run_headless(const char *target)`
  - `video_fetch_with_fallback` (function, line 1177) `static sf_status video_fetch_with_fallback(const char *url, sf_config *cfg,
                     ...`
  - `run_dump_video` (function, line 1288) `static int run_dump_video(const char *url)`
  - `main` (function, line 1307) `int main(int argc, char **argv)`
  - `gets` (function, line 482) `* gate a click gets (https-only, no downgrade, no foreign scheme), so relative * subresources work. Realm-routed...`
  - `pool` (function, line 784) `* the pool (unconsumed results freed, in-flight fetches joined). */ tab_set_fetcher(t, headless_fetch, (void...`
  - `only` (function, line 868) `* styling for the local render only (no network). --images enables image loading * AND rendering, including remote...`
  - `BLOCKED` (function, line 1042) `* is BLOCKED (fail closed), never leaked over the clearnet. */ nr_route route = nr_route_for(url, global_net);`
  - `_POSIX_C_SOURCE` (macro, line 9) `#define _POSIX_C_SOURCE`
  - `_DEFAULT_SOURCE` (macro, line 10) `#define _DEFAULT_SOURCE`
  - `EXIT_OK` (macro, line 51) `#define EXIT_OK`
  - `EXIT_ERROR` (macro, line 52) `#define EXIT_ERROR`
  - `EXIT_USAGE` (macro, line 53) `#define EXIT_USAGE`
  - `CSS_DROPS_REPORT_MAX` (macro, line 174) `#define CSS_DROPS_REPORT_MAX`
  - `HL_FONT_MAX_SHEETS` (macro, line 631) `#define HL_FONT_MAX_SHEETS`
  - `HL_FONT_MAX_BYTES` (macro, line 632) `#define HL_FONT_MAX_BYTES`
  - `HL_JS_NAV_MAX` (macro, line 1010) `#define HL_JS_NAV_MAX`
- Depends on: `include/dom_debug.h`, `include/fb_panes.h`, `include/frame_host.h`, `include/freebug.h`, `include/hls.h`, `include/host_conf.h`, `include/hostblock.h`, `include/html_parse.h`, `include/identity.h`, `include/js_policy.h`, `include/link_nav.h`, `include/media_decoder.h`, `include/net_realm.h`, `include/page_view.h`, `include/perf_trace.h`, `include/prefetch.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/tab.h`, `include/text_shape.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/webcaps.h`, `include/webfont.h`, `include/webfont_load.h`, `include/wl_display.h`

## src/hls.c
- Doc: last_char: Finds the last occurrence of character `c` in `s` (length `n`). * Returns NULL if not...
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

## src/host_conf.c
- Doc: read_conf: add_dir(out, env); if (home != NULL && home[0] != '\0') { char user[HCF_PATH_MAX]...
- Layer: utility
- Language: c
- Symbols:
  - `add_dir` (function, line 10) `static void add_dir(hcf_dirs *out, const char *path)`
  - `hcf_search_dirs` (function, line 20) `void hcf_search_dirs(const char *env, const char *home, hcf_dirs *out)`
  - `hcf_search_dirs_from_env` (function, line 32) `void hcf_search_dirs_from_env(hcf_dirs *out)`
  - `read_conf` (function, line 37) `static char *read_conf(const char *dir, const char *name)`
  - `load_into` (function, line 58) `static void load_into(hb_set *s, const char *dir, const char *name, hb_list list)`
  - `hcf_load_filter` (function, line 65) `hb_set *hcf_load_filter(const hcf_dirs *dirs)`
  - `hcf_load_allowlist` (function, line 76) `hb_set *hcf_load_allowlist(const hcf_dirs *dirs, const char *fname)`
  - `HCF_USER_SUBDIR` (macro, line 7) `#define HCF_USER_SUBDIR`
  - `HCF_REPO_DIR` (macro, line 8) `#define HCF_REPO_DIR`
- Depends on: `include/host_conf.h`

## src/hostblock.c
- Doc: table_probe: Finds the slot for key (length klen) in t, which must have a free slot.
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
  - `hb_check_subresource` (function, line 218) `hb_decision hb_check_subresource(const hb_set *s, const char *host, int page_trusted)`
  - `hb_is_allowlisted` (function, line 223) `int hb_is_allowlisted(const hb_set *s, const char *host)`
  - `hb_count` (function, line 243) `size_t hb_count(const hb_set *s, hb_list list)`
  - `HB_MAX_HOST` (macro, line 19) `#define HB_MAX_HOST`
  - `HB_INIT_CAP` (macro, line 20) `#define HB_INIT_CAP`
- Depends on: `include/hostblock.h`, `include/util.h`

## src/hostedit.c
- Doc: valid_host: #include "hostedit.h" #include <string.h> static char he_lower(char c) { return (c...
- Layer: utility
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
  - `he_cdn_kind` (function, line 173) `he_cdn_kind_t he_cdn_kind(const char *url)`
- Depends on: `include/hostedit.h`


Next: [KB_src_p5.md](KB_src_p5.md)
