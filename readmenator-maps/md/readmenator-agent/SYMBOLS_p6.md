# Symbols (page 6 of 13)
Previous: [SYMBOLS_p5.md](SYMBOLS_p5.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `cvr_reset` | function | `src/css_vars.c:102` | `void cvr_reset(cvr_table *t)` |
| `cvr_resolve` | function | `src/css_vars.c:230` | `int cvr_resolve(const char *val, char *out, size_t outcap, const cvr_scope *sc)` |
| `cvr_set` | function | `src/css_vars.c:67` | `int cvr_set(cvr_table *t, const char *name, size_t nlen, const char *value, size_t vlen)` |
| `dup_n` | function | `src/css_vars.c:21` | `static char *dup_n(const char *s, size_t n)` |
| `find_slot` | function | `src/css_vars.c:32` | `static size_t find_slot(const cvr_table *t, const char *name, size_t nlen)` |
| `grow` | function | `src/css_vars.c:45` | `static int grow(cvr_table *t)` |
| `is_ws` | function | `src/css_vars.c:120` | `static int is_ws(char c)` |
| `name_hash` | function | `src/css_vars.c:12` | `static size_t name_hash(const char *s, size_t n)` |
| `resolve_rec` | function | `src/css_vars.c:178` | `static int resolve_rec(const char *val, size_t vlen, char *out, size_t outcap,                   ...` |
| `scope_get` | function | `src/css_vars.c:164` | `static const char *scope_get(const cvr_scope *sc, const char *name, size_t nlen)` |
| `without_important` | function | `src/css_vars.c:124` | `static size_t without_important(const char *val, size_t n)` |
| `ascii_ws` | function | `src/data_url.c:115` | `static int ascii_ws(char c)` |
| `b64_val` | function | `src/data_url.c:61` | `static int b64_val(unsigned char c)` |
| `ci_starts_with` | function | `src/data_url.c:20` | `static int ci_starts_with(const char *s, const char *prefix)` |
| `du_base64_decode` | function | `src/data_url.c:70` | `du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len)` |
| `du_base64_payload` | function | `src/data_url.c:32` | `du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len)` |
| `du_decode` | function | `src/data_url.c:131` | `du_status du_decode(const char *url, char *mime, size_t mime_cap, uint8_t **out, size_t *out_len)` |
| `du_is_data_url` | function | `src/data_url.c:28` | `int du_is_data_url(const char *url)` |
| `ends_ci` | function | `src/data_url.c:120` | `static int ends_ci(const char *s, size_t n, const char *suf)` |
| `hexval` | function | `src/data_url.c:108` | `static int hexval(char c)` |
| `lower` | function | `src/data_url.c:16` | `static int lower(char c)` |
| `_POSIX_C_SOURCE` | macro | `src/disk_store.c:11` | `#define _POSIX_C_SOURCE` |
| `ds_free` | function | `src/disk_store.c:136` | `void ds_free(uint8_t *buf, size_t len)` |
| `ds_read` | function | `src/disk_store.c:103` | `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],                   uint8_t **ou...` |
| `ds_write` | function | `src/disk_store.c:66` | `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,                ...` |
| `fsync_dir` | function | `src/disk_store.c:32` | `static void fsync_dir(const char *path)` |
| `map_ls` | function | `src/disk_store.c:50` | `static ds_status map_ls(ls_status s)` |
| `DOM_QS_MAX_SELECTORS` | macro | `src/dom.c:380` | `#define DOM_QS_MAX_SELECTORS` |
| `IH_BLOCK_SIZE` | macro | `src/dom.c:818` | `#define IH_BLOCK_SIZE` |
| `_POSIX_C_SOURCE` | macro | `src/dom.c:11` | `#define _POSIX_C_SOURCE` |
| `char_kind` | function | `src/dom.c:981` | `static int char_kind(const lxb_dom_node_t *n)` |
| `copy_ids` | function | `src/dom.c:354` | `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)` |
| `count` | function | `src/dom.c:437` | `* count (may exceed cap), and returns DOM_NODE_NONE. */ static dom_node_id qs_walk(const dom_inde...` |
| `dom_append_child` | function | `src/dom.c:710` | `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)` |
| `dom_attribute_names` | function | `src/dom.c:586` | `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,                            con...` |
| `dom_build` | function | `src/dom.c:291` | `dom_status dom_build(const hp_document *doc, dom_index **out)` |
| `dom_child_node` | function | `src/dom.c:1004` | `dom_node_id dom_child_node(dom_index *idx, dom_node_id node, int last)` |
| `dom_clone_node` | function | `src/dom.c:934` | `dom_status dom_clone_node(dom_index *idx, dom_node_id node, int deep, dom_node_id *out_id)` |
| `dom_closest` | function | `src/dom.c:496` | `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,                         const cha...` |
| `dom_create_char_node` | function | `src/dom.c:1018` | `dom_status dom_create_char_node(dom_index *idx, int kind, const char *text, size_t len,          ...` |
| `dom_create_element` | function | `src/dom.c:690` | `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)` |
| `dom_document_position` | function | `src/dom.c:512` | `size_t dom_document_position(const dom_index *idx, dom_node_id node)` |
| `dom_document_title` | function | `src/dom.c:614` | `const char *dom_document_title(const dom_index *idx, size_t *len)` |
| `dom_first_child` | function | `src/dom.c:537` | `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)` |
| `dom_free` | function | `src/dom.c:332` | `void dom_free(dom_index *idx)` |
| `dom_get_attribute` | function | `src/dom.c:564` | `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,                            ...` |
| `dom_get_by_class` | function | `src/dom.c:370` | `size_t dom_get_by_class(const dom_index *idx, const char *cls,                         dom_node_i...` |
| `dom_get_by_tag` | function | `src/dom.c:361` | `size_t dom_get_by_tag(const dom_index *idx, const char *tag,                       dom_node_id *o...` |
| `dom_get_element_by_id` | function | `src/dom.c:348` | `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)` |
| `dom_get_inner_html` | function | `src/dom.c:887` | `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,                            ...` |
| `dom_index` | struct | `src/dom.c:220` | `` |
| `dom_insert_before` | function | `src/dom.c:917` | `dom_status dom_insert_before(dom_index *idx, dom_node_id parent, dom_node_id child,              ...` |
| `dom_matches` | function | `src/dom.c:487` | `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)` |
| `dom_move_children` | function | `src/dom.c:948` | `dom_status dom_move_children(dom_index *idx, dom_node_id src, dom_node_id parent,                ...` |
| `dom_next_sibling` | function | `src/dom.c:545` | `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)` |
| `dom_node_at` | function | `src/dom.c:522` | `dom_node_id dom_node_at(const dom_index *idx, size_t position)` |
| `dom_node_count` | function | `src/dom.c:344` | `size_t dom_node_count(const dom_index *idx)` |
| `dom_node_kind` | function | `src/dom.c:1000` | `int dom_node_kind(const dom_index *idx, dom_node_id node)` |
| `dom_parent` | function | `src/dom.c:527` | `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)` |
| `dom_precedes` | function | `src/dom.c:517` | `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)` |
| `dom_query_selector` | function | `src/dom.c:467` | `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,                           ...` |
| `dom_query_selector_all` | function | `src/dom.c:476` | `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,                            ...` |
| `dom_remove_attribute` | function | `src/dom.c:761` | `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)` |
| `dom_remove_child` | function | `src/dom.c:724` | `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)` |
| `dom_set_attribute` | function | `src/dom.c:732` | `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,                              const...` |
| `dom_set_document_title` | function | `src/dom.c:661` | `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)` |
| `dom_set_inner_html` | function | `src/dom.c:780` | `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,                               con...` |
| `dom_set_text_content` | function | `src/dom.c:627` | `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,                                ...` |
| `dom_sibling_node` | function | `src/dom.c:1011` | `dom_node_id dom_sibling_node(dom_index *idx, dom_node_id node, int prev)` |
| `dom_tag_name` | function | `src/dom.c:553` | `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)` |
| `dom_text_content` | function | `src/dom.c:604` | `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)` |
| `handle_of` | function | `src/dom.c:992` | `static dom_node_id handle_of(dom_index *idx, lxb_dom_node_t *n)` |
| `id_of` | function | `src/dom.c:383` | `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)` |
| `idx_push` | function | `src/dom.c:672` | `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)` |
| `ih_acc` | struct | `src/dom.c:825` | `` |
| `ih_append` | function | `src/dom.c:833` | `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)` |
| `ih_block` | struct | `src/dom.c:820` | `` |
| `ih_free` | function | `src/dom.c:860` | `static void ih_free(ih_acc *a)` |
| `index_element` | function | `src/dom.c:254` | `static int index_element(dom_index *idx, lxb_dom_element_t *el, dom_node_id id)` |
| `index_subtree` | function | `src/dom.c:770` | `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)` |
| `node_matches_any` | function | `src/dom.c:426` | `static int node_matches_any(const lxb_dom_node_t *cn,                             const css_sel *...` |
| `node_next` | function | `src/dom.c:232` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `parse_selector_list` | function | `src/dom.c:393` | `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)` |
| `pm_entry` | struct | `src/dom.c:154` | `` |
| `pm_free` | function | `src/dom.c:211` | `static void pm_free(ptrmap *m)` |
| `pm_get` | function | `src/dom.c:200` | `static int pm_get(const ptrmap *m, const void *key, dom_node_id *out)` |
| `pm_grow` | function | `src/dom.c:166` | `static int pm_grow(ptrmap *m)` |
| `pm_put` | function | `src/dom.c:183` | `static int pm_put(ptrmap *m, const void *key, dom_node_id id)` |
| `ptr_hash` | function | `src/dom.c:45` | `static size_t ptr_hash(const void *p)` |
| `ptrmap` | struct | `src/dom.c:160` | `` |
| `sm_entry` | struct | `src/dom.c:55` | `` |
| `sm_entry_append` | function | `src/dom.c:70` | `static int sm_entry_append(sm_entry *e, dom_node_id id)` |
| `sm_find` | function | `src/dom.c:127` | `static const sm_entry *sm_find(const strmap *m, const char *key, size_t klen)` |
| `sm_free` | function | `src/dom.c:139` | `static void sm_free(strmap *m)` |
| `sm_grow` | function | `src/dom.c:82` | `static int sm_grow(strmap *m)` |
| `sm_put` | function | `src/dom.c:99` | `static int sm_put(strmap *m, const char *key, size_t klen, dom_node_id id)` |
| `strmap` | struct | `src/dom.c:64` | `` |
| `to_lower_buf` | function | `src/dom.c:33` | `static int to_lower_buf(const char *s, size_t n, char *out, size_t outcap)` |
| `valid` | function | `src/dom.c:242` | `static int valid(const dom_index *idx, dom_node_id n)` |
| `dd_align_name` | function | `src/dom_debug.c:108` | `static const char *dd_align_name(int a)` |
| `dd_block_line` | function | `src/dom_debug.c:320` | `static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b)` |
| `dd_border_style_name` | function | `src/dom_debug.c:227` | `static const char *dd_border_style_name(int s)` |
| `dd_box_line` | function | `src/dom_debug.c:260` | `static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b)` |
| `dd_color` | function | `src/dom_debug.c:83` | `static void dd_color(dd_cursor *c, int rgb)` |
| `dd_cursor` | struct | `src/dom_debug.c:24` | `` |
| `dd_cursor_name` | function | `src/dom_debug.c:165` | `static const char *dd_cursor_name(int c)` |
| `dd_display_name` | function | `src/dom_debug.c:88` | `static const char *dd_display_name(int d)` |
| `dd_emit` | function | `src/dom_debug.c:36` | `static void dd_emit(dd_cursor *c, const char *s, size_t len)` |
| `dd_format` | function | `src/dom_debug.c:396` | `size_t dd_format(const rd_doc *doc, char *out, size_t cap)` |
| `dd_format_css` | function | `src/dom_debug.c:428` | `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)` |
| `dd_image_rendering_name` | function | `src/dom_debug.c:218` | `static const char *dd_image_rendering_name(int r)` |
| `dd_inset` | function | `src/dom_debug.c:203` | `static int dd_inset(int v)` |
| `dd_justify_name` | function | `src/dom_debug.c:96` | `static const char *dd_justify_name(int j)` |
| `dd_mix_blend_name` | function | `src/dom_debug.c:137` | `static const char *dd_mix_blend_name(int m)` |
| `dd_object_fit_name` | function | `src/dom_debug.c:207` | `static const char *dd_object_fit_name(int o)` |
| `dd_overflow_name` | function | `src/dom_debug.c:156` | `static const char *dd_overflow_name(int o)` |
| `dd_position_name` | function | `src/dom_debug.c:118` | `static const char *dd_position_name(int p)` |
| `dd_printf` | function | `src/dom_debug.c:48` | `static void dd_printf(dd_cursor *c, const char *fmt, ...)` |
| `dd_putc` | function | `src/dom_debug.c:31` | `static void dd_putc(dd_cursor *c, char ch)` |
| `dd_puts` | function | `src/dom_debug.c:40` | `static void dd_puts(dd_cursor *c, const char *s)` |
| `dd_text_overflow_name` | function | `src/dom_debug.c:198` | `static const char *dd_text_overflow_name(int t)` |
| `dd_visibility_name` | function | `src/dom_debug.c:129` | `static const char *dd_visibility_name(int v)` |
| `dd_w` | function | `src/dom_debug.c:80` | `static int dd_w(int v)` |
| `ci_find` | function | `src/download.c:19` | `static const char *ci_find(const char *hay, const char *needle)` |
| `copy_span` | function | `src/download.c:85` | `static void copy_span(const char *src, const char *end, char *buf, size_t bufsz)` |
| `dl_build_path` | function | `src/download.c:195` | `dl_status dl_build_path(const char *dir, const char *name, char *out, size_t outsz)` |
| `dl_check_size` | function | `src/download.c:213` | `dl_status dl_check_size(size_t len)` |
| `dl_ext_for_type` | function | `src/download.c:58` | `const char *dl_ext_for_type(const char *content_type)` |
| `dl_pick_name` | function | `src/download.c:153` | `dl_status dl_pick_name(const char *url, const char *content_disposition,                        c...` |
| `dl_should_download` | function | `src/download.c:47` | `int dl_should_download(const char *content_type, const char *content_disposition)` |
| `extract_disposition_name` | function | `src/download.c:96` | `static int extract_disposition_name(const char *cd, char *buf, size_t bufsz)` |
| `extract_url_name` | function | `src/download.c:134` | `static int extract_url_name(const char *url, char *buf, size_t bufsz)` |
| `has_extension` | function | `src/download.c:148` | `static int has_extension(const char *name)` |
| `lc` | function | `src/download.c:13` | `static int lc(int c)` |
| `media_type` | function | `src/download.c:33` | `static void media_type(const char *content_type, char *buf, size_t bufsz)` |
| `FX_EPS` | macro | `src/flex_layout.c:15` | `#define FX_EPS` |
| `area_token_is_null_cell` | function | `src/flex_layout.c:304` | `static int area_token_is_null_cell(const char *tok, size_t len)` |
| `float_pack_impl` | function | `src/flex_layout.c:427` | `static fx_status float_pack_impl(const double *width, const int *side, size_t n,                 ...` |
| `fx_auto_margins` | function | `src/flex_layout.c:566` | `fx_status fx_auto_margins(fx_result *res, size_t n, const unsigned char *auto_l,                 ...` |
| `fx_auto_min_size` | function | `src/flex_layout.c:589` | `double fx_auto_min_size(double min_content, double basis, double author_min,                     ...` |
| `fx_autofill_count` | function | `src/flex_layout.c:132` | `size_t fx_autofill_count(double avail, double gap, double minw)` |
| `fx_column_place` | function | `src/flex_layout.c:683` | `fx_status fx_column_place(const double *h, const double *grow, size_t n, double gap,             ...` |
| `fx_column_place_m` | function | `src/flex_layout.c:690` | `fx_status fx_column_place_m(const double *h, const double *grow, const int *mauto,               ...` |
| `fx_cross_offset` | function | `src/flex_layout.c:751` | `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r)` |
| `fx_flex_line` | function | `src/flex_layout.c:22` | `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,                 ...` |
| `fx_float_insets` | function | `src/flex_layout.c:467` | `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,                  ...` |
| `fx_float_pack` | function | `src/flex_layout.c:507` | `fx_status fx_float_pack(const double *width, const int *side, size_t n,                         d...` |
| `fx_float_pack_wrap` | function | `src/flex_layout.c:512` | `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,                     ...` |
| `fx_grid_area_hash` | function | `src/flex_layout.c:280` | `unsigned fx_grid_area_hash(const char *name)` |
| `fx_grid_area_rect` | function | `src/flex_layout.c:385` | `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,                             int ...` |
| `fx_grid_areas_parse` | function | `src/flex_layout.c:310` | `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)` |
| `fx_grid_cell` | function | `src/flex_layout.c:554` | `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)` |
| `fx_grid_columns` | function | `src/flex_layout.c:127` | `fx_status fx_grid_columns(double avail, size_t ncols, double gap,                           doubl...` |
| `fx_grid_columns_weighted` | function | `src/flex_layout.c:142` | `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,                       ...` |
| `fx_grid_place_span` | function | `src/flex_layout.c:176` | `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,                       ...` |
| `fx_justify_name` | function | `src/flex_layout.c:671` | `const char *fx_justify_name(fx_justify j)` |
| `fx_multicol_balance` | function | `src/flex_layout.c:640` | `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,                         ...` |
| `fx_multicol_used` | function | `src/flex_layout.c:603` | `fx_status fx_multicol_used(double avail_w, int column_count, double column_width,                ...` |
| `nn` | function | `src/flex_layout.c:18` | `static double nn(double v)` |
| `clean_action` | function | `src/form.c:75` | `static int clean_action(const char *action, char *out, size_t outsz)` |
| `copy_fit` | function | `src/form.c:66` | `static int copy_fit(char *dst, size_t dstsz, const char *src)` |
| `enc_component` | function | `src/form.c:25` | `static int enc_component(const char *s, char *out, size_t outsz, size_t *pos)` |
| `fm_build` | function | `src/form.c:120` | `fm_status fm_build(const char *base, const char *action, fm_method method,                    con...` |
| `fm_encode` | function | `src/form.c:43` | `fm_status fm_encode(const fm_field *fields, size_t n,                     char *out, size_t outsz...` |
| `put_char` | function | `src/form.c:17` | `static int put_char(char *out, size_t outsz, size_t *pos, char c)` |
| `resolve_target` | function | `src/form.c:101` | `static fm_block_reason resolve_target(const char *base, const char *act,                         ...` |
| `strip_query` | function | `src/form.c:93` | `static void strip_query(char *url)` |
| `FC_DEFAULT_INTERVAL_MS` | macro | `src/frame_clock.c:8` | `#define FC_DEFAULT_INTERVAL_MS` |
| `fc_interval_ms` | function | `src/frame_clock.c:26` | `int fc_interval_ms(const fc_clock *c)` |
| `fc_needs_tick` | function | `src/frame_clock.c:21` | `int fc_needs_tick(const fc_clock *c)` |
| `fc_set_active` | function | `src/frame_clock.c:16` | `void fc_set_active(fc_clock *c, int active)` |
| `fb_buffer_at` | function | `src/freebug.c:105` | `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)` |
| `fb_buffer_count` | function | `src/freebug.c:101` | `size_t fb_buffer_count(const fb_buffer *b)` |
| `fb_buffer_free` | function | `src/freebug.c:91` | `void fb_buffer_free(fb_buffer *b)` |
| `fb_buffer_init` | function | `src/freebug.c:15` | `void fb_buffer_init(fb_buffer *b)` |
| `fb_buffer_push` | function | `src/freebug.c:19` | `int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)` |
| `fb_buffer_push_loc` | function | `src/freebug.c:23` | `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len,                    ...` |
| `fb_buffer_reset` | function | `src/freebug.c:78` | `void fb_buffer_reset(fb_buffer *b)` |
| `fb_level_name` | function | `src/freebug.c:110` | `const char *fb_level_name(int level)` |
| `whole` | function | `src/freebug.c:5` | `* FB_MAX_TOTAL_BYTES is dropped whole (overflow flag raised, prior entries kept);` |
| `BLOCKED` | function | `src/freedom.c:903` | `* is BLOCKED (fail closed), never leaked over the clearnet. */ nr_route route = nr_route_for(url, global_net);` |
| `CSS_DROPS_REPORT_MAX` | macro | `src/freedom.c:164` | `#define CSS_DROPS_REPORT_MAX` |
| `EXIT_ERROR` | macro | `src/freedom.c:47` | `#define EXIT_ERROR` |
| `EXIT_OK` | macro | `src/freedom.c:46` | `#define EXIT_OK` |
| `EXIT_USAGE` | macro | `src/freedom.c:48` | `#define EXIT_USAGE` |
| `HL_FONT_MAX_BYTES` | macro | `src/freedom.c:539` | `#define HL_FONT_MAX_BYTES` |
| `HL_FONT_MAX_SHEETS` | macro | `src/freedom.c:538` | `#define HL_FONT_MAX_SHEETS` |
| `HL_JS_NAV_MAX` | macro | `src/freedom.c:873` | `#define HL_JS_NAV_MAX` |
| `_DEFAULT_SOURCE` | macro | `src/freedom.c:10` | `#define _DEFAULT_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `src/freedom.c:9` | `#define _POSIX_C_SOURCE` |
| `elsewhere` | function | `src/freedom.c:938` | `* page whose script immediately forwards elsewhere (e.g. a search engine's  * JS-capability inter...` |
| `fetch_and_render_one` | function | `src/freedom.c:877` | `static int fetch_and_render_one(const char *url, char **out_nav)` |
| `first` | function | `src/freedom.c:689` | `* always cleared first (fetch_and_render may paint several pages per      * process). A NULL top_...` |
| `foldback_cookies` | function | `src/freedom.c:480` | `static void foldback_cookies(const char *url, const char *jar)` |
| `gets` | function | `src/freedom.c:414` | `* gate a click gets (https-only, no downgrade, no foreign scheme), so relative * subresources work. Realm-routed...` |
| `headless_fetch` | function | `src/freedom.c:418` | `static int headless_fetch(void *ctx, const char *method, const char *url,                        ...` |
| `headless_load_hosts` | function | `src/freedom.c:226` | `static void headless_load_hosts(void)` |
| `hl_css_sink` | function | `src/freedom.c:562` | `static void hl_css_sink(void *vctx, const char *url,                         const char *body, si...` |
| `hl_font_fetch` | function | `src/freedom.c:599` | `static int hl_font_fetch(void *vctx, const char *url,                          int *out_status, c...` |
| `hl_font_stash` | struct | `src/freedom.c:541` | `` |
| `hl_font_stash_free` | function | `src/freedom.c:549` | `static void hl_font_stash_free(hl_font_stash *s)` |
| `is_blank_text` | function | `src/freedom.c:256` | `static int is_blank_text(const char *s)` |
| `is_http_url` | function | `src/freedom.c:80` | `static int is_http_url(const char *s)` |
| `is_https_url` | function | `src/freedom.c:76` | `static int is_https_url(const char *s)` |
| `is_overlay_http` | function | `src/freedom.c:85` | `static int is_overlay_http(const char *s)` |
| `main` | function | `src/freedom.c:1167` | `int main(int argc, char **argv)` |
| `now_us` | function | `src/freedom.c:139` | `static uint64_t now_us(void)` |
| `only` | function | `src/freedom.c:746` | `* styling for the local render only (no network). --images enables image loading * AND rendering, including remote...` |
| `parent` | function | `src/freedom.c:964` | `* gated by the parent (ln_resolve: a local target stays under the document's  * directory, a remo...` |
| `pool` | function | `src/freedom.c:674` | `* the pool (unconsumed results freed, in-flight fetches joined). */ tab_set_fetcher(t, headless_fetch, (void...` |
| `print_console` | function | `src/freedom.c:362` | `static void print_console(const fb_buffer *log)` |
| `print_css_drops` | function | `src/freedom.c:504` | `static void print_css_drops(const char *html, size_t len)` |
| `print_doc` | function | `src/freedom.c:269` | `static void print_doc(const rd_doc *doc)` |
| `print_dom` | function | `src/freedom.c:379` | `static void print_dom(const rd_doc *doc)` |
| `print_dom_css` | function | `src/freedom.c:394` | `static void print_dom_css(const rd_doc *doc)` |
| `print_usage` | function | `src/freedom.c:50` | `static void print_usage(FILE *fp, const char *prog)` |
| `read_file` | function | `src/freedom.c:208` | `static char *read_file(const char *path, size_t *out_len)` |
| `render_page` | function | `src/freedom.c:608` | `static int render_page(const char *html, size_t len, const char *top_url,                        ...` |
| `run_dump_video` | function | `src/freedom.c:1148` | `static int run_dump_video(const char *url)` |
| `run_headless` | function | `src/freedom.c:1001` | `static int run_headless(const char *target)` |
| `sf_reason` | function | `src/freedom.c:858` | `static const char *sf_reason(sf_status ss)` |
| `timings_dump` | function | `src/freedom.c:153` | `static void timings_dump(void)` |
| `timings_enabled` | function | `src/freedom.c:149` | `static int timings_enabled(void)` |
| `timings_ensure_init` | function | `src/freedom.c:145` | `static void timings_ensure_init(void)` |
| `user_impersonate_enabled` | function | `src/freedom.c:201` | `static int user_impersonate_enabled(void)` |
| `video_fetch_with_fallback` | function | `src/freedom.c:1037` | `static sf_status video_fetch_with_fallback(const char *url, sf_config *cfg,                      ...` |
| `_GNU_SOURCE` | macro | `src/hls.c:21` | `#define _GNU_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `src/hls.c:22` | `#define _POSIX_C_SOURCE` |
| `hls_parse` | function | `src/hls.c:80` | `hls_status hls_parse(const char *text, size_t len, hls_playlist **out)` |
| `hls_playlist_free` | function | `src/hls.c:253` | `void hls_playlist_free(hls_playlist *pl)` |
| `hls_resolve_url` | function | `src/hls.c:223` | `size_t hls_resolve_url(const char *base_url, const char *segment_url,                        char...` |
| `hls_select_variant` | function | `src/hls.c:202` | `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h)` |
| `last_char` | function | `src/hls.c:38` | `static const char *last_char(const char *s, size_t n, int c)` |
| `name` | function | `src/hls.c:46` | `* attr is the attribute name (e.g. "BANDWIDTH=");` |
| `parse_attr_long` | function | `src/hls.c:48` | `static int parse_attr_long(const char *attrs, const char *end,                            const c...` |
| `parse_attr_resolution` | function | `src/hls.c:62` | `static void parse_attr_resolution(const char *attrs, const char *end,                            ...` |
| `HB_INIT_CAP` | macro | `src/hostblock.c:20` | `#define HB_INIT_CAP` |
| `HB_MAX_HOST` | macro | `src/hostblock.c:19` | `#define HB_MAX_HOST` |
| `hb_check` | function | `src/hostblock.c:193` | `hb_decision hb_check(const hb_set *s, const char *host)` |
| `hb_count` | function | `src/hostblock.c:238` | `size_t hb_count(const hb_set *s, hb_list list)` |
| `hb_free` | function | `src/hostblock.c:149` | `void hb_free(hb_set *s)` |
| `hb_is_allowlisted` | function | `src/hostblock.c:218` | `int hb_is_allowlisted(const hb_set *s, const char *host)` |
| `hb_load` | function | `src/hostblock.c:156` | `hb_status hb_load(hb_set *s, const char *text, hb_list list)` |
| `hb_new` | function | `src/hostblock.c:144` | `hb_set *hb_new(void)` |
| `hb_set` | struct | `src/hostblock.c:30` | `` |
| `hb_table` | struct | `src/hostblock.c:24` | `` |
| `is_domain_char` | function | `src/hostblock.c:122` | `static int is_domain_char(char c)` |
| `is_ip_token` | function | `src/hostblock.c:113` | `static int is_ip_token(const char *s, size_t n)` |
| `lower` | function | `src/hostblock.c:107` | `static char lower(char c)` |
| `table_contains` | function | `src/hostblock.c:92` | `static int table_contains(const hb_table *t, const char *key)` |
| `table_free` | function | `src/hostblock.c:98` | `static void table_free(hb_table *t)` |
| `table_grow` | function | `src/hostblock.c:49` | `static int table_grow(hb_table *t, size_t newcap)` |
| `table_insert` | function | `src/hostblock.c:71` | `static int table_insert(hb_table *t, const char *key, size_t klen)` |
| `table_probe` | function | `src/hostblock.c:38` | `static size_t table_probe(const hb_table *t, const char *key, size_t klen)` |
| `contains_ci` | function | `src/hostedit.c:115` | `static int contains_ci(const char *hs, size_t hl, const char *needle)` |
| `has_host_cb` | function | `src/hostedit.c:105` | `static int has_host_cb(const char *ts, size_t tl, void *ctx)` |
| `he_lower` | function | `src/hostedit.c:12` | `static char he_lower(char c)` |
| `he_make_line` | function | `src/hostedit.c:41` | `he_status he_make_line(const char *host, char *out, size_t cap)` |
| `he_scan` | function | `src/hostedit.c:80` | `static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), void *ctx)` |
| `he_suggest` | function | `src/hostedit.c:164` | `int he_suggest(const char *text, const char *query,                char results[][HE_MAX_HOST + 1...` |
| `he_text_has_host` | function | `src/hostedit.c:109` | `int he_text_has_host(const char *text, const char *host)` |
| `is_ip_token` | function | `src/hostedit.c:67` | `static int is_ip_token(const char *ts, const char *te)` |
| `is_label_char` | function | `src/hostedit.c:16` | `static int is_label_char(char c)` |
| `starts_with_ci` | function | `src/hostedit.c:128` | `static int starts_with_ci(const char *hs, size_t hl, const char *pfx)` |
| `suggest_cb` | function | `src/hostedit.c:144` | `static int suggest_cb(const char *ts, size_t tl, void *vctx)` |
| `suggest_ctx` | struct | `src/hostedit.c:136` | `` |
| `valid_host` | function | `src/hostedit.c:22` | `static int valid_host(const char *host, size_t n)` |
| `_POSIX_C_SOURCE` | macro | `src/html_parse.c:9` | `#define _POSIX_C_SOURCE` |
| `attr_has_token_ci` | function | `src/html_parse.c:251` | `static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle)` |
| `attr_is_event_handler` | function | `src/html_parse.c:47` | `static int attr_is_event_handler(const lxb_dom_attr_t *attr)` |
| `dup_bytes` | function | `src/html_parse.c:27` | `static char *dup_bytes(const lxb_char_t *src, size_t len)` |
| `hp_config_default` | function | `src/html_parse.c:357` | `hp_config hp_config_default(void)` |
| `hp_document` | struct | `src/html_parse.c:21` | `` |
| `hp_document_free` | function | `src/html_parse.c:483` | `void hp_document_free(hp_document *doc)` |
| `hp_document_root` | function | `src/html_parse.c:489` | `const void *hp_document_root(const hp_document *doc)` |
| `hp_element_count` | function | `src/html_parse.c:409` | `size_t hp_element_count(const hp_document *doc)` |
| `hp_event_handler_count` | function | `src/html_parse.c:429` | `size_t hp_event_handler_count(const hp_document *doc)` |
| `hp_extract_script_list` | function | `src/html_parse.c:164` | `hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count)` |
| `hp_extract_stylesheet_hrefs` | function | `src/html_parse.c:294` | `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count)` |
| `hp_extract_text` | function | `src/html_parse.c:445` | `char *hp_extract_text(const hp_document *doc, size_t *out_len)` |
| `hp_free` | function | `src/html_parse.c:479` | `void hp_free(char *buf)` |
| `hp_free_scripts` | function | `src/html_parse.c:238` | `void hp_free_scripts(hp_script *scripts, size_t count)` |
| `hp_free_stylesheet_hrefs` | function | `src/html_parse.c:328` | `void hp_free_stylesheet_hrefs(char **hrefs, size_t count)` |
| `hp_get_title` | function | `src/html_parse.c:464` | `char *hp_get_title(const hp_document *doc, size_t *out_len)` |
| `hp_parse` | function | `src/html_parse.c:375` | `hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out)` |
| `hp_script_count` | function | `src/html_parse.c:419` | `size_t hp_script_count(const hp_document *doc)` |
| `hp_validate_input` | function | `src/html_parse.c:365` | `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg)` |
| `link_is_active_stylesheet` | function | `src/html_parse.c:272` | `static int link_is_active_stylesheet(lxb_dom_element_t *el,                                      ...` |
| `lxb_dom_element_has_attribute` | function | `src/html_parse.c:230` | `&& lxb_dom_element_has_attribute(sel, (const lxb_char_t *)"nomodule", 8);` |
| `node_is_script` | function | `src/html_parse.c:54` | `static int node_is_script(const lxb_dom_node_t *node)` |
| `node_next` | function | `src/html_parse.c:37` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `script_classify` | function | `src/html_parse.c:121` | `static int script_classify(const lxb_dom_node_t *n,                            const lxb_char_t *...` |
| `strip_event_handlers` | function | `src/html_parse.c:334` | `static void strip_event_handlers(lxb_html_document_t *document)` |
| `strip_scripts` | function | `src/html_parse.c:60` | `static void strip_scripts(lxb_html_document_t *document)` |
| `type_is` | function | `src/html_parse.c:100` | `static int type_is(const lxb_char_t *t, size_t len, const char *word)` |
| `type_is_module` | function | `src/html_parse.c:117` | `static int type_is_module(const lxb_char_t *t, size_t len)` |
| `GIF_LZW_MAX_CODES` | macro | `src/image_decode.c:253` | `#define GIF_LZW_MAX_CODES` |
| `PNG_IHDR_MIN` | macro | `src/image_decode.c:34` | `#define PNG_IHDR_MIN` |
| `exit` | function | `src/image_decode.c:6` | `* malformed stream fails closed instead of calling exit(). GIF uses an own pure-C * bounded LZW decoder (no giflib)....` |
| `gb_next_code` | function | `src/image_decode.c:298` | `static int gb_next_code(gif_bits *b, unsigned width, unsigned *out)` |
| `gif_bits` | struct | `src/image_decode.c:290` | `` |
| `gif_deinterlace_row` | function | `src/image_decode.c:319` | `static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh)` |
| `gif_put_pixel` | function | `src/image_decode.c:334` | `static void gif_put_pixel(uint32_t *canvas, uint32_t cw, uint32_t ch,                           u...` |
| `gif_reader` | struct | `src/image_decode.c:255` | `` |
| `gr_skip` | function | `src/image_decode.c:273` | `static int gr_skip(gif_reader *r, size_t n)` |
| `gr_skip_subblocks` | function | `src/image_decode.c:280` | `static int gr_skip_subblocks(gif_reader *r)` |
| `gr_u16le` | function | `src/image_decode.c:266` | `static int gr_u16le(gif_reader *r, uint16_t *out)` |
| `gr_u8` | function | `src/image_decode.c:260` | `static int gr_u8(gif_reader *r, uint8_t *out)` |
| `img_decode` | function | `src/image_decode.c:553` | `img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_gif` | function | `src/image_decode.c:354` | `img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_jpeg` | function | `src/image_decode.c:166` | `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_png` | function | `src/image_decode.c:102` | `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_webp` | function | `src/image_decode.c:520` | `img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_dimensions_ok` | function | `src/image_decode.c:68` | `int img_dimensions_ok(uint32_t w, uint32_t h)` |
| `img_fit` | function | `src/image_decode.c:76` | `void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,              double *out_w, do...` |
| `img_format_name` | function | `src/image_decode.c:575` | `const char *img_format_name(img_format f)` |
| `img_pixels_free` | function | `src/image_decode.c:566` | `void img_pixels_free(img_pixels *p)` |
| `img_png_dimensions` | function | `src/image_decode.c:57` | `img_status img_png_dimensions(const uint8_t *bytes, size_t len,                               uin...` |
| `jpeg_err_ctx` | struct | `src/image_decode.c:153` | `` |
| `jpeg_error_longjmp` | function | `src/image_decode.c:158` | `static void jpeg_error_longjmp(j_common_ptr cinfo)` |
| `jpeg_silence` | function | `src/image_decode.c:164` | `static void jpeg_silence(j_common_ptr cinfo)` |
| `premultiply` | function | `src/image_decode.c:90` | `static void premultiply(uint8_t *data, size_t pixels)` |
| `read_be32` | function | `src/image_decode.c:52` | `static uint32_t read_be32(const uint8_t *p)` |
| `IM_MAX_DEPTH` | macro | `src/import_map.c:16` | `#define IM_MAX_DEPTH` |
| `IM_URL_MAX` | macro | `src/import_map.c:17` | `#define IM_URL_MAX` |
| `add` | function | `src/import_map.c:185` | `static int add(im_map *m, int scope, const char *key, const char *addr, const char *doc_url,     ...` |
| `clear` | function | `src/import_map.c:175` | `static void clear(im_map *m)` |
| `dup_s` | function | `src/import_map.c:168` | `static char *dup_s(const char *s)` |
| `eat` | function | `src/import_map.c:44` | `static int eat(jr *r, char c)` |
| `hex4` | function | `src/import_map.c:50` | `static int hex4(const char *s, uint32_t *out)` |
| `im_count` | function | `src/import_map.c:339` | `size_t im_count(const im_map *m)` |
| `im_entry` | struct | `src/import_map.c:19` | `` |
| `im_free` | function | `src/import_map.c:343` | `void im_free(im_map *m)` |
| `im_map` | struct | `src/import_map.c:25` | `` |
| `im_parse` | function | `src/import_map.c:225` | `im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn resolve, void *ctx)` |
| `im_resolve` | function | `src/import_map.c:301` | `int im_resolve(const im_map *m, const char *base, const char *specifier,                im_url_fn...` |
| `jr` | struct | `src/import_map.c:34` | `` |
| `match` | function | `src/import_map.c:272` | `static int match(const im_map *m, int scope, const char *key, char *out, size_t outsz)` |
| `put_utf8` | function | `src/import_map.c:64` | `static size_t put_utf8(char *o, uint32_t cp)` |
| `scope` | type_alias | `src/import_map.c:18` | `typedef struct im_entry { int scope;` |
| `skip` | function | `src/import_map.c:128` | `static void skip(jr *r, int depth)` |
| `specifier_map` | function | `src/import_map.c:209` | `static void specifier_map(jr *r, im_map *m, int scope, const char *doc_url,                      ...` |
| `str` | function | `src/import_map.c:78` | `static char *str(jr *r)` |
| `url_like` | function | `src/import_map.c:156` | `static int url_like(const char *s)` |
| `ws` | function | `src/import_map.c:39` | `static void ws(jr *r)` |
| `anim_effective_dir` | function | `src/interp.c:232` | `static int anim_effective_dir(const ip_anim *a)` |
| `anim_effective_dir_for` | function | `src/interp.c:222` | `static int anim_effective_dir_for(const ip_anim *a, int iter)` |
| `ip_anim_current` | function | `src/interp.c:282` | `double ip_anim_current(const ip_anim *a)` |
| `ip_anim_done` | function | `src/interp.c:320` | `int ip_anim_done(const ip_anim *a)` |
| `ip_anim_init` | function | `src/interp.c:196` | `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease,                   const ip_...` |
| `ip_anim_tick` | function | `src/interp.c:236` | `int ip_anim_tick(ip_anim *a, double dt_ms)` |
| `ip_ease` | function | `src/interp.c:55` | `double ip_ease(double t, const ip_ease_fn *fn)` |
| `ip_ease` | function | `src/interp.c:64` | `case IP_EASE_EASE:         return ip_ease(t, &(ip_ease_fn)` |
| `ip_ease` | function | `src/interp.c:70` | `case IP_EASE_EASE_IN:         return ip_ease(t, &(ip_ease_fn)` |
| `ip_ease` | function | `src/interp.c:76` | `case IP_EASE_EASE_OUT:         return ip_ease(t, &(ip_ease_fn)` |
| `ip_ease` | function | `src/interp.c:82` | `case IP_EASE_EASE_IN_OUT:         return ip_ease(t, &(ip_ease_fn)` |
| `ip_interp` | function | `src/interp.c:162` | `double ip_interp(ip_val_kind kind, double a, double b, double t)` |
| `ip_kf_interp` | function | `src/interp.c:175` | `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf,                     int n_kf, do...` |
| `ip_lerp` | function | `src/interp.c:134` | `double ip_lerp(double a, double b, double t)` |
| `ip_lerp_color` | function | `src/interp.c:139` | `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t)` |
| `sample_bezier_dx` | function | `src/interp.c:23` | `static double sample_bezier_dx(double t, double cx1, double cx2)` |
| `sample_bezier_x` | function | `src/interp.c:18` | `static double sample_bezier_x(double t, double cx1, double cx2)` |
| `sample_bezier_y` | function | `src/interp.c:29` | `static double sample_bezier_y(double t, double cy1, double cy2)` |
| `solve_bezier_t` | function | `src/interp.c:35` | `static double solve_bezier_t(double x, double cx1, double cx2)` |
| `_GNU_SOURCE` | macro | `src/js_dom.c:10` | `#define _GNU_SOURCE` |
| `attrNames` | function | `src/js_dom.c:610` | `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so      * a missing '...` |
| `empty` | function | `src/js_dom.c:1215` | `* inert: DOM interface constructors are empty (instanceof yields false, harmless);` |
| `enough` | function | `src/js_dom.c:931` | `* enough (cloneNode/lastChild/removeChild/insertBefore) that library feature * detection does not throw: jQuery...` |
| `fails` | function | `src/js_dom.c:1852` | `* cap is reached or an allocation fails (caller stops), else 0. */ static int cb_append(char **bu...` |
| `geometry` | function | `src/js_dom.c:1217` | `* constant geometry (zero real leak);` |
| `jd_get_cookies` | function | `src/js_dom.c:2023` | `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)` |
| `jd_handle` | function | `src/js_dom.c:40` | `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out)` |
| `jd_handle_or_null` | function | `src/js_dom.c:47` | `JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h)` |
| `jd_idx` | function | `src/js_dom.c:31` | `dom_index *jd_idx(JSContext *ctx)` |
| `jd_install` | function | `src/js_dom.c:1775` | `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)` |
| `jd_install_console` | function | `src/js_dom.c:1966` | `jd_status jd_install_console(js_context *ctx, fb_buffer *log)` |
| `jd_method` | struct | `src/js_dom.c:428` | `` |
| `jd_opaque_get` | function | `src/js_dom.c:27` | `jd_opaque *jd_opaque_get(JSContext *ctx)` |
| `jd_query_list` | function | `src/js_dom.c:70` | `static JSValue jd_query_list(JSContext *ctx, JSValueConst arg, int by_class)` |
| `jd_set_cookies` | function | `src/js_dom.c:2003` | `jd_status jd_set_cookies(js_context *ctx, const char *cookies)` |
| `jd_set_geometry` | function | `src/js_dom.c:2046` | `jd_status jd_set_geometry(js_context *ctx, const jg_table *geom)` |
| `js_env` | function | `src/js_dom.c:1223` | `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the  * document shim (uses...` |
| `m_append_child` | function | `src/js_dom.c:264` | `static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,                             ...` |
| `m_attr_names` | function | `src/js_dom.c:503` | `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,                             in...` |
| `m_child_node` | function | `src/js_dom.c:159` | `static JSValue m_child_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_clone_node` | function | `src/js_dom.c:289` | `static JSValue m_clone_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_closest` | function | `src/js_dom.c:491` | `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,                          int argc...` |
| `m_create_char` | function | `src/js_dom.c:174` | `static JSValue m_create_char(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_create_element` | function | `src/js_dom.c:252` | `static JSValue m_create_element(JSContext *ctx, JSValueConst this_val,                           ...` |
| `m_first_child` | function | `src/js_dom.c:143` | `static JSValue m_first_child(JSContext *ctx, JSValueConst this_val,                              ...` |
| `m_get_attribute` | function | `src/js_dom.c:122` | `static JSValue m_get_attribute(JSContext *ctx, JSValueConst this_val,                            ...` |
| `m_get_by_class` | function | `src/js_dom.c:106` | `static JSValue m_get_by_class(JSContext *ctx, JSValueConst this_val,                             ...` |
| `m_get_by_tag` | function | `src/js_dom.c:100` | `static JSValue m_get_by_tag(JSContext *ctx, JSValueConst this_val,                             in...` |
| `m_get_element_by_id` | function | `src/js_dom.c:59` | `static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val,                        ...` |
| `m_get_inner_html` | function | `src/js_dom.c:364` | `static JSValue m_get_inner_html(JSContext *ctx, JSValueConst this_val,                           ...` |
| `m_get_title` | function | `src/js_dom.c:231` | `static JSValue m_get_title(JSContext *ctx, JSValueConst this_val,                            int ...` |
| `m_insert_before` | function | `src/js_dom.c:299` | `static JSValue m_insert_before(JSContext *ctx, JSValueConst this_val,                            ...` |
| `m_matches` | function | `src/js_dom.c:479` | `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,                          int argc...` |
| `m_move_children` | function | `src/js_dom.c:275` | `static JSValue m_move_children(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_next_sibling` | function | `src/js_dom.c:188` | `static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,                             ...` |
| `m_node_count` | function | `src/js_dom.c:53` | `static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,                             in...` |
| `m_node_kind` | function | `src/js_dom.c:152` | `static JSValue m_node_kind(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_parent` | function | `src/js_dom.c:135` | `static JSValue m_parent(JSContext *ctx, JSValueConst this_val,                         int argc, ...` |
| `m_precedes` | function | `src/js_dom.c:196` | `static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_query_selector` | function | `src/js_dom.c:437` | `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,                           ...` |
| `m_query_selector_all` | function | `src/js_dom.c:450` | `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,                       ...` |
| `m_rect` | function | `src/js_dom.c:396` | `static JSValue m_rect(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_remove_attribute` | function | `src/js_dom.c:336` | `static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,                         ...` |
| `m_remove_child` | function | `src/js_dom.c:311` | `static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,                             ...` |
| `m_set_attribute` | function | `src/js_dom.c:320` | `static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,                            ...` |
| `m_set_inner_html` | function | `src/js_dom.c:348` | `static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,                           ...` |
| `m_set_text` | function | `src/js_dom.c:217` | `static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_set_title` | function | `src/js_dom.c:239` | `static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,                            int ...` |
| `m_sibling_node` | function | `src/js_dom.c:166` | `static JSValue m_sibling_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_tag_name` | function | `src/js_dom.c:112` | `static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_text_content` | function | `src/js_dom.c:207` | `static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,                             ...` |
| `ms` | function | `src/js_dom.c:1067` | `* due is the remaining virtual ms (the trusted parent advances the clock via * OP_TICK -> __tickTimers(elapsed);` |
| `scripts` | function | `src/js_dom.c:768` | `* player scripts (canPlayType feature-detection, play/pause, muted/loop * reflection, buffered ranges) run without...` |
| `size` | function | `src/js_dom.c:1220` | `* the viewport reads a fixed normalized size (matches the 1920 width * anti_fp uses for @media, not the real window);` |
| `table` | function | `src/js_dom.c:571` | `* a table (dom.viewport() non-null);` |
| `identity` | function | `src/js_dom_ext.c:96` | `* identity (host/shadowRoot/mode preserved) but every mutation ALSO mirrors * into the host's light DOM via dom.*...` |
| `jdx_install` | function | `src/js_dom_ext.c:374` | `int jdx_install(JSContext *ctx)` |
| `run` | function | `src/js_dom_ext.c:366` | `static int run(JSContext *ctx, const char *src, size_t len, const char *name)` |
| `FREEDOM_JS_DOM_EXT_H` | macro | `src/js_dom_ext.h:2` | `#define FREEDOM_JS_DOM_EXT_H` |
| `jdx_install` | function | `src/js_dom_ext.h:10` | `int jdx_install(JSContext *ctx);` |
| `FREEDOM_JS_DOM_INTERNAL_H` | macro | `src/js_dom_internal.h:2` | `#define FREEDOM_JS_DOM_INTERNAL_H` |
| `jd_handle` | function | `src/js_dom_internal.h:14` | `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out);` |
| `jd_idx` | function | `src/js_dom_internal.h:12` | `dom_index *jd_idx(JSContext *ctx);` |
| `jd_opaque_get` | function | `src/js_dom_internal.h:11` | `jd_opaque *jd_opaque_get(JSContext *ctx);` |
| `_GNU_SOURCE` | macro | `src/js_embed.c:6` | `#define _GNU_SOURCE` |
| `jd_inject_video_shim` | function | `src/js_embed.c:242` | `jd_status jd_inject_video_shim(js_context *ctx)` |
| `jd_process_iframes` | function | `src/js_embed.c:294` | `void jd_process_iframes(js_context *ctx, dom_index *idx,                         jd_fetch_fn fn, ...` |
| `jd_video_from_scripts` | function | `src/js_embed.c:203` | `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,                    ...` |
| `scan_video_url` | function | `src/js_embed.c:256` | `static int scan_video_url(const char *body, size_t blen,                            char *out, si...` |
| `try_create_iframe_from_script` | function | `src/js_embed.c:86` | `static int try_create_iframe_from_script(dom_index *idx,                                         ...` |
| `FP_MIME_COUNT` | macro | `src/js_env.c:260` | `#define FP_MIME_COUNT` |
| `PERF_ORIGIN_EPOCH` | macro | `src/js_env.c:344` | `#define PERF_ORIGIN_EPOCH` |
| `_POSIX_C_SOURCE` | macro | `src/js_env.c:17` | `#define _POSIX_C_SOURCE` |
| `build_crypto` | function | `src/js_env.c:346` | `static int build_crypto(JSContext *ctx, JSValueConst global)` |
| `build_languages` | function | `src/js_env.c:174` | `static JSValue build_languages(JSContext *ctx)` |
| `build_navigator` | function | `src/js_env.c:198` | `static int build_navigator(JSContext *ctx, JSValueConst global)` |
| `build_perf_navigation` | function | `src/js_env.c:388` | `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)` |
| `build_perf_timing` | function | `src/js_env.c:374` | `static int build_perf_timing(JSContext *ctx, JSValueConst perf)` |
| `build_performance` | function | `src/js_env.c:400` | `static int build_performance(JSContext *ctx, JSValueConst global)` |
| `build_readback_obj` | function | `src/js_env.c:484` | `static int build_readback_obj(JSContext *ctx, JSValueConst global,                               ...` |
| `build_screen` | function | `src/js_env.c:302` | `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)` |
| `def_fn` | function | `src/js_env.c:167` | `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,                   JSCFuncti...` |
| `def_int` | function | `src/js_env.c:163` | `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)` |
| `def_str` | function | `src/js_env.c:159` | `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)` |
| `def_val` | function | `src/js_env.c:153` | `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)` |
| `je_install` | function | `src/js_env.c:497` | `je_status je_install(js_context *ctx, int screen_w, int screen_h)` |
| `je_install_canvas` | function | `src/js_env.c:516` | `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)` |
| `m_date_now` | function | `src/js_env.c:49` | `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_empty_array` | function | `src/js_env.c:77` | `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,                              ...` |
| `m_get_random_values` | function | `src/js_env.c:85` | `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,                        ...` |
| `m_perf_now` | function | `src/js_env.c:57` | `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_random_uuid` | function | `src/js_env.c:125` | `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,                              ...` |
| `m_subtle_null` | function | `src/js_env.c:142` | `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,                              ...` |
| `make_readback` | function | `src/js_env.c:476` | `static JSValue make_readback(JSContext *ctx, uint64_t key)` |
| `methods` | function | `src/js_env.c:201` | `* capability methods (sendBeacon, spec/js_dom.md 7h) without touching any * fingerprintable field. An untrusted...` |
| `monotonic_ms` | function | `src/js_env.c:41` | `static double monotonic_ms(void)` |
| `override_date_now` | function | `src/js_env.c:432` | `static int override_date_now(JSContext *ctx, JSValueConst global)` |
| `primitives` | function | `src/js_env.c:6` | `* the pure anti_fp primitives (one audited source of normalized constants);` |
| `wall_clock_ms` | function | `src/js_env.c:35` | `static uint64_t wall_clock_ms(void)` |
| `_GNU_SOURCE` | macro | `src/js_events.c:6` | `#define _GNU_SOURCE` |
| `jd_click_state` | struct | `src/js_events.c:25` | `` |
| `jd_click_state_free` | function | `src/js_events.c:34` | `void jd_click_state_free(jd_click_state *s)` |
| `jd_click_state_new` | function | `src/js_events.c:29` | `jd_click_state *jd_click_state_new(void)` |
| `jd_escape_js_str` | function | `src/js_events.c:91` | `static size_t jd_escape_js_str(const char *src, char *dst, size_t dstsz)` |
| `jd_eval_default_action` | function | `src/js_events.c:52` | `static int jd_eval_default_action(JSContext *jsctx, const char *src, size_t n,                   ...` |
| `jd_fire_click` | function | `src/js_events.c:66` | `int jd_fire_click(js_context *ctx, dom_node_id node_id)` |
| `jd_fire_mouse_event` | function | `src/js_events.c:163` | `int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,                         const char ...` |
| `jd_fire_submit` | function | `src/js_events.c:78` | `int jd_fire_submit(js_context *ctx, dom_node_id form_node_id)` |
| `jd_install_events` | function | `src/js_events.c:38` | `jd_status jd_install_events(js_context *ctx, jd_click_state *state)` |
| `_GNU_SOURCE` | macro | `src/js_fetch.c:6` | `#define _GNU_SOURCE` |
| `jd_install_xhr` | function | `src/js_fetch.c:197` | `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)` |
| `jd_pack_ptr` | function | `src/js_fetch.c:28` | `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)` |
| `jd_unpack_ptr` | function | `src/js_fetch.c:33` | `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)` |
| `m_host_fetch` | function | `src/js_fetch.c:46` | `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,                             in...` |
| `send` | function | `src/js_fetch.c:92` | `* callbacks fire right after send();` |
| `task` | function | `src/js_fetch.c:179` | `* current task (the page never waits on it);` |
| `JG_INDEX_SLOTS` | macro | `src/js_geom.c:14` | `#define JG_INDEX_SLOTS` |
| `JG_SLOT_EMPTY` | macro | `src/js_geom.c:15` | `#define JG_SLOT_EMPTY` |
| `clamp_coord` | function | `src/js_geom.c:27` | `static int32_t clamp_coord(double v, double lo)` |
| `cmp_node` | function | `src/js_geom.c:78` | `static int cmp_node(const void *pa, const void *pb)` |
| `fnv` | function | `src/js_geom.c:212` | `static uint64_t fnv(uint64_t h, int32_t v)` |
| `grow` | function | `src/js_geom.c:33` | `static int grow(jg_table *t)` |
| `in_range` | function | `src/js_geom.c:182` | `static int in_range(int32_t v, int32_t lo)` |
| `index_of` | function | `src/js_geom.c:109` | `static size_t index_of(jg_table *t, uint32_t *slots, dom_node_id node, const jg_rect *seed,      ...` |
| `jg_add` | function | `src/js_geom.c:52` | `int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h)` |
| `jg_aggregate` | function | `src/js_geom.c:124` | `int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx)` |
| `jg_decode` | function | `src/js_geom.c:186` | `int jg_decode(const int32_t *in, size_t n, jg_table *out)` |
| `jg_encode` | function | `src/js_geom.c:167` | `int jg_encode(const jg_table *t, int32_t *out, size_t cap)` |

Next: [SYMBOLS_p7.md](SYMBOLS_p7.md)
