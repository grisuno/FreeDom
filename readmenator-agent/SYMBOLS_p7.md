# Symbols (page 7 of 16)
Previous: [SYMBOLS_p6.md](SYMBOLS_p6.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `cmp_op` | function | `src/css_mq.c:206` | `static int cmp_op(double lhs, int op, double rhs)` |
| `cmq_matches` | function | `src/css_mq.c:458` | `int cmq_matches(const char *s, size_t len, const cmq_env *env)` |
| `copy_trim_lower` | function | `src/css_mq.c:83` | `static int copy_trim_lower(const char *s, size_t a, size_t b, char *dst, size_t cap)` |
| `eval_cond` | function | `src/css_mq.c:380` | `static int eval_cond(mq_cur *c, int depth)` |
| `eval_feature` | function | `src/css_mq.c:328` | `static int eval_feature(const char *s, size_t a, size_t b, const cmq_env *env)` |
| `eval_in_parens` | function | `src/css_mq.c:353` | `static int eval_in_parens(mq_cur *c, int depth)` |
| `eval_plain` | function | `src/css_mq.c:237` | `static int eval_plain(const char *name, const char *value, const cmq_env *env)` |
| `eval_query` | function | `src/css_mq.c:404` | `static int eval_query(const char *s, size_t a, size_t b, const cmq_env *env)` |
| `eval_range` | function | `src/css_mq.c:280` | `static int eval_range(const char *t, const cmq_env *env)` |
| `feature_of` | function | `src/css_mq.c:106` | `static fval feature_of(const char *name, const cmq_env *env)` |
| `flip_op` | function | `src/css_mq.c:218` | `static int flip_op(int op)` |
| `fval` | struct | `src/css_mq.c:96` | `` |
| `is_ident_ch` | function | `src/css_mq.c:39` | `static int is_ident_ch(char c)` |
| `is_space` | function | `src/css_mq.c:35` | `static int is_space(char c)` |
| `kind` | type_alias | `src/css_mq.c:95` | `typedef struct fval { fv_kind kind;` |
| `lower_ch` | function | `src/css_mq.c:31` | `static char lower_ch(char c)` |
| `mq_cur` | struct | `src/css_mq.c:25` | `` |
| `not3` | function | `src/css_mq.c:78` | `static int not3(int a)` |
| `or3` | function | `src/css_mq.c:72` | `static int or3(int a, int b)` |
| `parse_value` | function | `src/css_mq.c:167` | `static int parse_value(const char *t, int unit, double *out)` |
| `peek_word` | function | `src/css_mq.c:61` | `static int peek_word(const mq_cur *c, char *w, size_t cap)` |
| `read_num` | function | `src/css_mq.c:162` | `static int read_num(const char *t, double *out, const char **end)` |
| `read_op` | function | `src/css_mq.c:266` | `static int read_op(const char **p)` |
| `read_word` | function | `src/css_mq.c:49` | `static int read_word(mq_cur *c, char *w, size_t cap)` |
| `skip_ws` | function | `src/css_mq.c:44` | `static void skip_ws(mq_cur *c)` |
| `HAS_MAX_DEPTH` | macro | `src/css_select.c:939` | `#define HAS_MAX_DEPTH` |
| `attr_matches` | function | `src/css_select.c:788` | `static int attr_matches(const css_attr_match *am, const css_element *el)` |
| `between` | function | `src/css_select.c:384` | `* between ( and ) is split on commas (not inside [] or ());` |
| `built` | function | `src/css_select.c:1115` | `* chains the caller built (an element without parent/prev links never matches  * through that com...` |
| `compound_matches` | function | `src/css_select.c:1080` | `static int compound_matches(const css_compound *c, const css_element *el,                        ...` |
| `compound_req` | function | `src/css_select.c:709` | `static unsigned long long compound_req(const css_compound *c)` |
| `compute_anc_req` | function | `src/css_select.c:602` | `static unsigned long long compute_anc_req(const css_sel *sel)` |
| `compute_subj_req` | function | `src/css_select.c:718` | `static unsigned long long compute_subj_req(const css_sel *sel)` |
| `csel_compact_dup` | function | `src/css_select.c:735` | `css_sel *csel_compact_dup(const css_sel *sel)` |
| `csel_compact_size` | function | `src/css_select.c:729` | `size_t csel_compact_size(int nparts)` |
| `csel_decl_end` | function | `src/css_select.c:106` | `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace)` |
| `csel_element_feature_bits` | function | `src/css_select.c:587` | `unsigned long long csel_element_feature_bits(const css_element *e)` |
| `csel_emit_utf8` | function | `src/css_select.c:32` | `size_t csel_emit_utf8(unsigned int cp, char *out)` |
| `csel_escape_len` | function | `src/css_select.c:93` | `size_t csel_escape_len(const char *s, size_t i, size_t b)` |
| `csel_hex_val` | function | `src/css_select.c:25` | `int csel_hex_val(char c)` |
| `csel_ident_eq` | function | `src/css_select.c:144` | `int csel_ident_eq(const char *stored, const char *tok, size_t tlen)` |
| `csel_ident_fold` | function | `src/css_select.c:129` | `void csel_ident_fold(const char *src, size_t len, char *dst)` |
| `csel_matches` | function | `src/css_select.c:1196` | `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,               ...` |
| `csel_needs_structure` | function | `src/css_select.c:1173` | `int csel_needs_structure(const css_sel *sel)` |
| `csel_parse` | function | `src/css_select.c:744` | `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel)` |
| `csel_parse_core` | function | `src/css_select.c:615` | `static int csel_parse_core(const char *s, size_t a, size_t b, css_sel *sel)` |
| `csel_read_ident` | function | `src/css_select.c:152` | `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower)` |
| `csel_unescape` | function | `src/css_select.c:54` | `void csel_unescape(char *dst, size_t cap, const char *src, size_t n)` |
| `el_attr_value` | function | `src/css_select.c:755` | `static const char *el_attr_value(const css_element *el, const char *name)` |
| `ends_with` | function | `src/css_select.c:765` | `static int ends_with(const char *v, const char *suf, int ci)` |
| `has_word` | function | `src/css_select.c:773` | `static int has_word(const char *v, const char *w, int ci)` |
| `ident_hash` | function | `src/css_select.c:123` | `static unsigned long long ident_hash(const char *s, size_t n)` |
| `is_form_control` | function | `src/css_select.c:817` | `static int is_form_control(const char *tag)` |
| `nth_matches` | function | `src/css_select.c:808` | `static int nth_matches(int A, int B, int idx)` |
| `parse_attr_sel` | function | `src/css_select.c:186` | `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)` |
| `parse_compound` | function | `src/css_select.c:525` | `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,                   ...` |
| `parse_nth_arg` | function | `src/css_select.c:243` | `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)` |
| `parse_sub_compound` | function | `src/css_select.c:460` | `static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub)` |
| `pseudo_is_local` | function | `src/css_select.c:1160` | `static int pseudo_is_local(int kind)` |
| `pseudo_matches` | function | `src/css_select.c:826` | `static int pseudo_matches(const css_pseudo_match *pm, const css_element *el, const css_sel *sel, const char...` |
| `selector` | function | `src/css_select.c:567` | `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is  * dropped. Whitespa...` |
| `seven` | function | `src/css_select.c:621` | `* pay for the other seven (a css_sel is ~12.8 KiB). */ memset(sel, 0, offsetof(css_sel, parts));` |
| `simple_pseudo_kind` | function | `src/css_select.c:439` | `static int simple_pseudo_kind(const char *nm)` |
| `sub_sel_matches` | function | `src/css_select.c:830` | `static int sub_sel_matches(const css_sub_sel *sub, const css_element *el)` |
| `take_sub_arg` | function | `src/css_select.c:295` | `static int take_sub_arg(const char *s, size_t a, size_t b, css_sel *sel, int strict);` |
| `ct_emit_spacing` | function | `src/css_text.c:309` | `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val)` |
| `ct_expand_shadow` | function | `src/css_text.c:322` | `int ct_expand_shadow(const char *val, css_decl *dst, int cap)` |
| `ct_expand_valign` | function | `src/css_text.c:122` | `int ct_expand_valign(const char *val, css_decl *dst, int cap)` |
| `ct_family_of` | function | `src/css_text.c:18` | `static int ct_family_of(const char *name)` |
| `ct_interp_aspect_ratio` | function | `src/css_text.c:194` | `int ct_interp_aspect_ratio(const char *v, int *num, int *den)` |
| `ct_interp_direction` | function | `src/css_text.c:236` | `int ct_interp_direction(const char *v)` |
| `ct_interp_fontfamily` | function | `src/css_text.c:47` | `int ct_interp_fontfamily(const char *v)` |
| `ct_interp_liststyle` | function | `src/css_text.c:274` | `int ct_interp_liststyle(const char *v)` |
| `ct_interp_tabsize` | function | `src/css_text.c:160` | `int ct_interp_tabsize(const char *v)` |
| `ct_interp_textdeco_style` | function | `src/css_text.c:171` | `int ct_interp_textdeco_style(const char *v)` |
| `ct_interp_textdeco_thickness` | function | `src/css_text.c:182` | `int ct_interp_textdeco_thickness(const char *v)` |
| `ct_interp_texttransform` | function | `src/css_text.c:69` | `int ct_interp_texttransform(const char *v)` |
| `ct_interp_transition_property` | function | `src/css_text.c:139` | `int ct_interp_transition_property(const char *v)` |
| `ct_interp_valign` | function | `src/css_text.c:91` | `int ct_interp_valign(const char *v)` |
| `ct_interp_whitespace` | function | `src/css_text.c:147` | `int ct_interp_whitespace(const char *v)` |
| `ct_liststyle_kw` | function | `src/css_text.c:242` | `static int ct_liststyle_kw(const char *t)` |
| `ct_liststyle_unknown_name` | function | `src/css_text.c:263` | `static int ct_liststyle_unknown_name(const char *t)` |
| `cv_bg_alpha_of` | function | `src/css_values.c:46` | `int cv_bg_alpha_of(const char *v)` |
| `cv_color_ok` | function | `src/css_values.c:41` | `int cv_color_ok(int c)` |
| `cv_filter_scale` | function | `src/css_values.c:231` | `double cv_filter_scale(int pct)` |
| `cv_interp_bg` | function | `src/css_values.c:160` | `int cv_interp_bg(const char *v)` |
| `cv_interp_color` | function | `src/css_values.c:36` | `int cv_interp_color(const char *v)` |
| `cv_parse_color` | function | `src/css_values.c:16` | `int cv_parse_color(const char *v)` |
| `cv_parse_color_t7` | function | `src/css_values.c:205` | `int cv_parse_color_t7(const char *v)` |
| `cv_parse_num` | function | `src/css_values.c:11` | `static int cv_parse_num(const char *s, double *out, const char **endp)` |
| `cv_text_color` | function | `src/css_values.c:222` | `int cv_text_color(const char *v)` |
| `cvr_collect_decls` | function | `src/css_vars.c:139` | `void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b)` |
| `cvr_count` | function | `src/css_vars.c:100` | `size_t cvr_count(const cvr_table *t)` |
| `cvr_free` | function | `src/css_vars.c:112` | `void cvr_free(cvr_table *t)` |
| `cvr_get` | function | `src/css_vars.c:94` | `const char *cvr_get(const cvr_table *t, const char *name, size_t nlen)` |
| `cvr_lookup` | function | `src/css_vars.c:239` | `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen)` |
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
| `DOM_QS_MAX_SELECTORS` | macro | `src/dom.c:413` | `#define DOM_QS_MAX_SELECTORS` |
| `IH_BLOCK_SIZE` | macro | `src/dom.c:848` | `#define IH_BLOCK_SIZE` |
| `_POSIX_C_SOURCE` | macro | `src/dom.c:11` | `#define _POSIX_C_SOURCE` |
| `char_kind` | function | `src/dom.c:1011` | `static int char_kind(const lxb_dom_node_t *n)` |
| `copy_ids` | function | `src/dom.c:387` | `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)` |
| `count` | function | `src/dom.c:467` | `* count (may exceed cap), and returns DOM_NODE_NONE. */ static dom_node_id qs_walk(const dom_inde...` |
| `dom_append_child` | function | `src/dom.c:740` | `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)` |
| `dom_attribute_names` | function | `src/dom.c:616` | `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,                            con...` |
| `dom_build` | function | `src/dom.c:291` | `dom_status dom_build(const hp_document *doc, dom_index **out)` |
| `dom_child_node` | function | `src/dom.c:1034` | `dom_node_id dom_child_node(dom_index *idx, dom_node_id node, int last)` |
| `dom_clone_node` | function | `src/dom.c:964` | `dom_status dom_clone_node(dom_index *idx, dom_node_id node, int deep, dom_node_id *out_id)` |
| `dom_closest` | function | `src/dom.c:526` | `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,                         const cha...` |
| `dom_create_char_node` | function | `src/dom.c:1048` | `dom_status dom_create_char_node(dom_index *idx, int kind, const char *text, size_t len,          ...` |
| `dom_create_element` | function | `src/dom.c:720` | `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)` |
| `dom_document_position` | function | `src/dom.c:542` | `size_t dom_document_position(const dom_index *idx, dom_node_id node)` |
| `dom_document_title` | function | `src/dom.c:644` | `const char *dom_document_title(const dom_index *idx, size_t *len)` |
| `dom_first_child` | function | `src/dom.c:567` | `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)` |
| `dom_free` | function | `src/dom.c:332` | `void dom_free(dom_index *idx)` |
| `dom_get_attribute` | function | `src/dom.c:594` | `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,                            ...` |
| `dom_get_by_class` | function | `src/dom.c:403` | `size_t dom_get_by_class(const dom_index *idx, const char *cls,                         dom_node_i...` |
| `dom_get_by_tag` | function | `src/dom.c:394` | `size_t dom_get_by_tag(const dom_index *idx, const char *tag,                       dom_node_id *o...` |
| `dom_get_connected_by_id` | function | `src/dom.c:364` | `dom_node_id dom_get_connected_by_id(const dom_index *idx, const char *id)` |
| `dom_get_element_by_id` | function | `src/dom.c:358` | `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)` |
| `dom_get_inner_html` | function | `src/dom.c:917` | `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,                            ...` |
| `dom_index` | struct | `src/dom.c:220` | `` |
| `dom_insert_before` | function | `src/dom.c:947` | `dom_status dom_insert_before(dom_index *idx, dom_node_id parent, dom_node_id child,              ...` |
| `dom_matches` | function | `src/dom.c:517` | `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)` |
| `dom_move_children` | function | `src/dom.c:978` | `dom_status dom_move_children(dom_index *idx, dom_node_id src, dom_node_id parent,                ...` |
| `dom_native_node` | function | `src/dom.c:1062` | `const void *dom_native_node(const dom_index *idx, dom_node_id node)` |
| `dom_next_sibling` | function | `src/dom.c:575` | `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)` |
| `dom_node_at` | function | `src/dom.c:552` | `dom_node_id dom_node_at(const dom_index *idx, size_t position)` |
| `dom_node_count` | function | `src/dom.c:344` | `size_t dom_node_count(const dom_index *idx)` |
| `dom_node_kind` | function | `src/dom.c:1030` | `int dom_node_kind(const dom_index *idx, dom_node_id node)` |
| `dom_parent` | function | `src/dom.c:557` | `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)` |
| `dom_precedes` | function | `src/dom.c:547` | `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)` |
| `dom_query_selector` | function | `src/dom.c:497` | `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,                           ...` |
| `dom_query_selector_all` | function | `src/dom.c:506` | `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,                            ...` |
| `dom_remove_attribute` | function | `src/dom.c:791` | `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)` |
| `dom_remove_child` | function | `src/dom.c:754` | `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)` |
| `dom_set_attribute` | function | `src/dom.c:762` | `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,                              const...` |
| `dom_set_document_title` | function | `src/dom.c:691` | `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)` |
| `dom_set_inner_html` | function | `src/dom.c:810` | `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,                               con...` |
| `dom_set_text_content` | function | `src/dom.c:657` | `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,                                ...` |
| `dom_sibling_node` | function | `src/dom.c:1041` | `dom_node_id dom_sibling_node(dom_index *idx, dom_node_id node, int prev)` |
| `dom_tag_name` | function | `src/dom.c:583` | `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)` |
| `dom_text_content` | function | `src/dom.c:634` | `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)` |
| `handle_of` | function | `src/dom.c:1022` | `static dom_node_id handle_of(dom_index *idx, lxb_dom_node_t *n)` |
| `id_of` | function | `src/dom.c:416` | `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)` |
| `idx_push` | function | `src/dom.c:702` | `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)` |
| `ih_acc` | struct | `src/dom.c:855` | `` |
| `ih_append` | function | `src/dom.c:863` | `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)` |
| `ih_block` | struct | `src/dom.c:850` | `` |
| `ih_free` | function | `src/dom.c:890` | `static void ih_free(ih_acc *a)` |
| `index_element` | function | `src/dom.c:254` | `static int index_element(dom_index *idx, lxb_dom_element_t *el, dom_node_id id)` |
| `index_subtree` | function | `src/dom.c:800` | `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)` |
| `node_in_document` | function | `src/dom.c:352` | `static int node_in_document(const lxb_dom_node_t *node)` |
| `node_matches_any` | function | `src/dom.c:459` | `static int node_matches_any(const lxb_dom_node_t *cn,                             const css_sel *...` |
| `node_next` | function | `src/dom.c:232` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `parse_selector_list` | function | `src/dom.c:426` | `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)` |
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
| `dd_block_line` | function | `src/dom_debug.c:323` | `static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b)` |
| `dd_border_style_name` | function | `src/dom_debug.c:228` | `static const char *dd_border_style_name(int s)` |
| `dd_box_line` | function | `src/dom_debug.c:261` | `static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b)` |
| `dd_color` | function | `src/dom_debug.c:83` | `static void dd_color(dd_cursor *c, int rgb)` |
| `dd_cursor` | struct | `src/dom_debug.c:24` | `` |
| `dd_cursor_name` | function | `src/dom_debug.c:166` | `static const char *dd_cursor_name(int c)` |
| `dd_display_name` | function | `src/dom_debug.c:88` | `static const char *dd_display_name(int d)` |
| `dd_emit` | function | `src/dom_debug.c:36` | `static void dd_emit(dd_cursor *c, const char *s, size_t len)` |
| `dd_format` | function | `src/dom_debug.c:399` | `size_t dd_format(const rd_doc *doc, char *out, size_t cap)` |
| `dd_format_css` | function | `src/dom_debug.c:431` | `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)` |
| `dd_image_rendering_name` | function | `src/dom_debug.c:219` | `static const char *dd_image_rendering_name(int r)` |
| `dd_inset` | function | `src/dom_debug.c:204` | `static int dd_inset(int v)` |
| `dd_justify_name` | function | `src/dom_debug.c:96` | `static const char *dd_justify_name(int j)` |
| `dd_mix_blend_name` | function | `src/dom_debug.c:137` | `static const char *dd_mix_blend_name(int m)` |
| `dd_object_fit_name` | function | `src/dom_debug.c:208` | `static const char *dd_object_fit_name(int o)` |
| `dd_overflow_name` | function | `src/dom_debug.c:157` | `static const char *dd_overflow_name(int o)` |
| `dd_position_name` | function | `src/dom_debug.c:118` | `static const char *dd_position_name(int p)` |
| `dd_printf` | function | `src/dom_debug.c:48` | `static void dd_printf(dd_cursor *c, const char *fmt, ...)` |
| `dd_putc` | function | `src/dom_debug.c:31` | `static void dd_putc(dd_cursor *c, char ch)` |
| `dd_puts` | function | `src/dom_debug.c:40` | `static void dd_puts(dd_cursor *c, const char *s)` |
| `dd_text_overflow_name` | function | `src/dom_debug.c:199` | `static const char *dd_text_overflow_name(int t)` |
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
| `dup_n` | function | `src/fb_cmdline.c:10` | `static char *dup_n(const char *s, size_t n)` |
| `fbc_complete_pick` | function | `src/fb_cmdline.c:118` | `size_t fbc_complete_pick(const char *names, const char *prefix, size_t plen,                     ...` |
| `fbc_complete_split` | function | `src/fb_cmdline.c:74` | `long fbc_complete_split(const char *text, size_t n, char *base, size_t cap, size_t *prefix_off)` |
| `fbc_filter_label` | function | `src/fb_cmdline.c:173` | `const char *fbc_filter_label(int filter)` |
| `fbc_filter_next` | function | `src/fb_cmdline.c:168` | `int fbc_filter_next(int filter)` |
| `fbc_filter_passes` | function | `src/fb_cmdline.c:159` | `int fbc_filter_passes(int filter, int level)` |
| `fbc_history_free` | function | `src/fb_cmdline.c:23` | `void fbc_history_free(fbc_history *h)` |
| `fbc_history_init` | function | `src/fb_cmdline.c:19` | `void fbc_history_init(fbc_history *h)` |
| `fbc_history_next` | function | `src/fb_cmdline.c:63` | `const char *fbc_history_next(fbc_history *h)` |
| `fbc_history_prev` | function | `src/fb_cmdline.c:53` | `const char *fbc_history_prev(fbc_history *h, const char *cur, size_t curlen)` |
| `fbc_history_push` | function | `src/fb_cmdline.c:32` | `int fbc_history_push(fbc_history *h, const char *text, size_t len)` |
| `fbc_names_expr` | function | `src/fb_cmdline.c:95` | `size_t fbc_names_expr(const char *base, char *out, size_t cap)` |
| `path_char` | function | `src/fb_cmdline.c:70` | `static int path_char(char c)` |
| `fbp_expr` | function | `src/fb_panes.c:186` | `size_t fbp_expr(int tab, const char *sel, size_t n, char *out, size_t cap)` |
| `fbp_is_pane` | function | `src/fb_panes.c:155` | `int fbp_is_pane(int tab)` |
| `fbp_js_quote` | function | `src/fb_panes.c:157` | `size_t fbp_js_quote(const char *s, size_t n, char *out, size_t cap)` |
| `fbp_tab_at` | function | `src/fb_panes.c:145` | `int fbp_tab_at(double px, double cell_w, double pad_cells)` |
| `fbp_tab_from_name` | function | `src/fb_panes.c:123` | `int fbp_tab_from_name(const char *name)` |
| `fbp_tab_label` | function | `src/fb_panes.c:112` | `const char *fbp_tab_label(int tab)` |
| `fbp_tab_span` | function | `src/fb_panes.c:136` | `void fbp_tab_span(int tab, double cell_w, double pad_cells, double *x, double *w)` |
| `fbp_tab_wrap` | function | `src/fb_panes.c:130` | `int fbp_tab_wrap(int tab, int dir)` |
| `ieq` | function | `src/fb_panes.c:114` | `static int ieq(const char *a, const char *b)` |
| `tab_ok` | function | `src/fb_panes.c:110` | `static int tab_ok(int tab)` |
| `FX_EPS` | macro | `src/flex_layout.c:16` | `#define FX_EPS` |
| `area_token_is_null_cell` | function | `src/flex_layout.c:343` | `static int area_token_is_null_cell(const char *tok, size_t len)` |
| `float_pack_impl` | function | `src/flex_layout.c:466` | `static fx_status float_pack_impl(const double *width, const int *side, size_t n,                 ...` |
| `fx_auto_margins` | function | `src/flex_layout.c:605` | `fx_status fx_auto_margins(fx_result *res, size_t n, const unsigned char *auto_l,                 ...` |
| `fx_auto_min_size` | function | `src/flex_layout.c:628` | `double fx_auto_min_size(double min_content, double basis, double author_min,                     ...` |
| `fx_autofill_count` | function | `src/flex_layout.c:133` | `size_t fx_autofill_count(double avail, double gap, double minw)` |
| `fx_col_free_split` | function | `src/flex_layout.c:930` | `fx_status fx_col_free_split(double free_px, const int *grow, const int *mauto, size_t n,         ...` |
| `fx_column_place` | function | `src/flex_layout.c:725` | `fx_status fx_column_place(const double *h, const double *grow, size_t n, double gap,             ...` |
| `fx_column_place_m` | function | `src/flex_layout.c:732` | `fx_status fx_column_place_m(const double *h, const double *grow, const int *mauto,               ...` |
| `fx_cross_offset` | function | `src/flex_layout.c:793` | `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r)` |
| `fx_flex_line` | function | `src/flex_layout.c:23` | `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,                 ...` |
| `fx_float_insets` | function | `src/flex_layout.c:506` | `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,                  ...` |
| `fx_float_pack` | function | `src/flex_layout.c:546` | `fx_status fx_float_pack(const double *width, const int *side, size_t n,                         d...` |
| `fx_float_pack_wrap` | function | `src/flex_layout.c:551` | `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,                     ...` |
| `fx_grid_area_hash` | function | `src/flex_layout.c:319` | `unsigned fx_grid_area_hash(const char *name)` |
| `fx_grid_area_rect` | function | `src/flex_layout.c:424` | `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,                             int ...` |
| `fx_grid_areas_parse` | function | `src/flex_layout.c:349` | `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)` |
| `fx_grid_cell` | function | `src/flex_layout.c:593` | `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)` |
| `fx_grid_columns` | function | `src/flex_layout.c:128` | `fx_status fx_grid_columns(double avail, size_t ncols, double gap,                           doubl...` |
| `fx_grid_columns_weighted` | function | `src/flex_layout.c:143` | `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,                       ...` |
| `fx_grid_line_parse` | function | `src/flex_layout.c:868` | `int fx_grid_line_parse(const char *v, int *start, int *end)` |
| `fx_grid_line_resolve` | function | `src/flex_layout.c:888` | `void fx_grid_line_resolve(int start, int end, int ntracks, int *pos0, int *span)` |
| `fx_grid_line_side` | function | `src/flex_layout.c:860` | `int fx_grid_line_side(const char *s, int *out)` |
| `fx_grid_place_span` | function | `src/flex_layout.c:177` | `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,                       ...` |
| `fx_justify_name` | function | `src/flex_layout.c:713` | `const char *fx_justify_name(fx_justify j)` |
| `fx_multicol_balance` | function | `src/flex_layout.c:682` | `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,                         ...` |
| `fx_multicol_used` | function | `src/flex_layout.c:645` | `fx_status fx_multicol_used(double avail_w, int column_count, double column_width,                ...` |
| `gl_int` | function | `src/flex_layout.c:822` | `static int gl_int(const char *p, const char *end, long cap, long *out)` |
| `gl_is_line` | function | `src/flex_layout.c:886` | `static int gl_is_line(int v)` |
| `gl_is_span` | function | `src/flex_layout.c:885` | `static int gl_is_span(int v)` |
| `gl_kw` | function | `src/flex_layout.c:812` | `static int gl_kw(const char *p, const char *end, const char *kw)` |
| `gl_lower` | function | `src/flex_layout.c:809` | `static int gl_lower(char c)` |
| `gl_side_range` | function | `src/flex_layout.c:837` | `static int gl_side_range(const char *p, const char *end, int *out)` |
| `gl_ws` | function | `src/flex_layout.c:805` | `static int gl_ws(char c)` |
| `nn` | function | `src/flex_layout.c:19` | `static double nn(double v)` |
| `clean_action` | function | `src/form.c:75` | `static int clean_action(const char *action, char *out, size_t outsz)` |
| `copy_fit` | function | `src/form.c:66` | `static int copy_fit(char *dst, size_t dstsz, const char *src)` |
| `enc_component` | function | `src/form.c:25` | `static int enc_component(const char *s, char *out, size_t outsz, size_t *pos)` |
| `fm_build` | function | `src/form.c:120` | `fm_status fm_build(const char *base, const char *action, fm_method method,                    con...` |
| `fm_encode` | function | `src/form.c:43` | `fm_status fm_encode(const fm_field *fields, size_t n,                     char *out, size_t outsz...` |
| `put_char` | function | `src/form.c:17` | `static int put_char(char *out, size_t outsz, size_t *pos, char c)` |
| `resolve_target` | function | `src/form.c:101` | `static fm_block_reason resolve_target(const char *base, const char *act,                         ...` |
| `strip_query` | function | `src/form.c:93` | `static void strip_query(char *url)` |
| `fbk_add` | function | `src/frame_broker.c:66` | `int fbk_add(fbk_table *t, int parent, const char *url, int *out_id)` |
| `fbk_init` | function | `src/frame_broker.c:53` | `int fbk_init(fbk_table *t, const char *top_url)` |
| `fbk_origin` | function | `src/frame_broker.c:96` | `const char *fbk_origin(const fbk_table *t, int id)` |
| `fbk_origin_of` | function | `src/frame_broker.c:15` | `int fbk_origin_of(const char *url, char *out, size_t cap)` |
| `fbk_remove` | function | `src/frame_broker.c:84` | `void fbk_remove(fbk_table *t, int id)` |
| `fbk_route` | function | `src/frame_broker.c:118` | `fbk_verdict fbk_route(const fbk_table *t, int from, fbk_rel rel, int child,                      ...` |
| `host_char_ok` | function | `src/frame_broker.c:11` | `static int host_char_ok(char c)` |
| `lc` | function | `src/frame_broker.c:9` | `static char lc(char c)` |
| `live` | function | `src/frame_broker.c:62` | `static int live(const fbk_table *t, int id)` |
| `target_admits` | function | `src/frame_broker.c:101` | `static int target_admits(const char *target, const char *snd, const char *recv)` |
| `FC_DEFAULT_INTERVAL_MS` | macro | `src/frame_clock.c:8` | `#define FC_DEFAULT_INTERVAL_MS` |
| `fc_interval_ms` | function | `src/frame_clock.c:26` | `int fc_interval_ms(const fc_clock *c)` |
| `fc_needs_tick` | function | `src/frame_clock.c:21` | `int fc_needs_tick(const fc_clock *c)` |
| `fc_set_active` | function | `src/frame_clock.c:16` | `void fc_set_active(fc_clock *c, int active)` |
| `apply_ops` | function | `src/frame_host.c:198` | `static void apply_ops(fh_host *h, int from, const tab_ws_op *ops, size_t n)` |
| `fh_apply_top` | function | `src/frame_host.c:221` | `void fh_apply_top(fh_host *h, const tab_page *page)` |
| `fh_count` | function | `src/frame_host.c:76` | `int fh_count(const fh_host *h)` |
| `fh_frame_view` | function | `src/frame_host.c:252` | `const pv_view *fh_frame_view(const fh_host *h, const char *url, tab **t_out)` |
| `fh_free` | function | `src/frame_host.c:67` | `void fh_free(fh_host *h)` |
| `fh_generation` | function | `src/frame_host.c:250` | `unsigned fh_generation(const fh_host *h)` |
| `fh_host` | struct | `src/frame_host.c:22` | `` |
| `fh_new` | function | `src/frame_host.c:35` | `fh_host *fh_new(const char *top_url, tab_fetch_fn fetch, void *fetch_ctx,                 fh_top_...` |
| `fh_slot` | struct | `src/frame_host.c:14` | `` |
| `fh_tick` | function | `src/frame_host.c:226` | `int fh_tick(fh_host *h, int elapsed_ms)` |
| `find_child` | function | `src/frame_host.c:129` | `static int find_child(const fh_host *h, int parent, int token)` |
| `load_frame` | function | `src/frame_host.c:85` | `static void load_frame(fh_host *h, int id, const char *url)` |
| `post_op` | function | `src/frame_host.c:143` | `static void post_op(fh_host *h, int from, const tab_ws_op *op)` |
| `reap` | function | `src/frame_host.c:55` | `static void reap(fh_host *h)` |
| `slot_release_view` | function | `src/frame_host.c:47` | `static void slot_release_view(fh_slot *sl)` |
| `token_seen_by` | function | `src/frame_host.c:137` | `static int token_seen_by(const fh_host *h, int dest, int from)` |
| `fb_buffer_at` | function | `src/freebug.c:105` | `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)` |
| `fb_buffer_count` | function | `src/freebug.c:101` | `size_t fb_buffer_count(const fb_buffer *b)` |
| `fb_buffer_free` | function | `src/freebug.c:91` | `void fb_buffer_free(fb_buffer *b)` |
| `fb_buffer_init` | function | `src/freebug.c:15` | `void fb_buffer_init(fb_buffer *b)` |
| `fb_buffer_push` | function | `src/freebug.c:19` | `int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)` |
| `fb_buffer_push_loc` | function | `src/freebug.c:23` | `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len,                    ...` |
| `fb_buffer_reset` | function | `src/freebug.c:78` | `void fb_buffer_reset(fb_buffer *b)` |
| `fb_level_name` | function | `src/freebug.c:110` | `const char *fb_level_name(int level)` |
| `whole` | function | `src/freebug.c:5` | `* FB_MAX_TOTAL_BYTES is dropped whole (overflow flag raised, prior entries kept);` |
| `BLOCKED` | function | `src/freedom.c:1041` | `* is BLOCKED (fail closed), never leaked over the clearnet. */ nr_route route = nr_route_for(url, global_net);` |
| `CSS_DROPS_REPORT_MAX` | macro | `src/freedom.c:174` | `#define CSS_DROPS_REPORT_MAX` |
| `EXIT_ERROR` | macro | `src/freedom.c:52` | `#define EXIT_ERROR` |
| `EXIT_OK` | macro | `src/freedom.c:51` | `#define EXIT_OK` |
| `EXIT_USAGE` | macro | `src/freedom.c:53` | `#define EXIT_USAGE` |
| `HL_FONT_MAX_BYTES` | macro | `src/freedom.c:632` | `#define HL_FONT_MAX_BYTES` |
| `HL_FONT_MAX_SHEETS` | macro | `src/freedom.c:631` | `#define HL_FONT_MAX_SHEETS` |
| `HL_JS_NAV_MAX` | macro | `src/freedom.c:1009` | `#define HL_JS_NAV_MAX` |
| `_DEFAULT_SOURCE` | macro | `src/freedom.c:10` | `#define _DEFAULT_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `src/freedom.c:9` | `#define _POSIX_C_SOURCE` |
| `apply_as_gui` | function | `src/freedom.c:286` | `static void apply_as_gui(const char *top_url, int flag_js, int flag_css, int flag_images)` |
| `apply_identity` | function | `src/freedom.c:281` | `static void apply_identity(sf_config *cfg)` |
| `elsewhere` | function | `src/freedom.c:1076` | `* page whose script immediately forwards elsewhere (e.g. a search engine's  * JS-capability inter...` |
| `fetch_and_render_one` | function | `src/freedom.c:1013` | `static int fetch_and_render_one(const char *url, char **out_nav)` |
| `first` | function | `src/freedom.c:798` | `* always cleared first (fetch_and_render may paint several pages per      * process). A NULL top_...` |
| `foldback_cookies` | function | `src/freedom.c:573` | `static void foldback_cookies(const char *url, const char *jar)` |
| `gets` | function | `src/freedom.c:482` | `* gate a click gets (https-only, no downgrade, no foreign scheme), so relative * subresources work. Realm-routed...` |
| `headless_fetch` | function | `src/freedom.c:486` | `static int headless_fetch(void *ctx, const char *method, const char *url,                        ...` |
| `headless_load_hosts` | function | `src/freedom.c:261` | `static void headless_load_hosts(void)` |
| `hl_css_sink` | function | `src/freedom.c:655` | `static void hl_css_sink(void *vctx, const char *url,                         const char *body, si...` |
| `hl_font_fetch` | function | `src/freedom.c:692` | `static int hl_font_fetch(void *vctx, const char *url,                          int *out_status, c...` |
| `hl_font_stash` | struct | `src/freedom.c:634` | `` |
| `hl_font_stash_free` | function | `src/freedom.c:642` | `static void hl_font_stash_free(hl_font_stash *s)` |
| `hl_frame_top_msg` | function | `src/freedom.c:215` | `static void hl_frame_top_msg(void *ctx, const char *data, size_t len)` |
| `hl_frames` | struct | `src/freedom.c:210` | `` |
| `is_blank_text` | function | `src/freedom.c:324` | `static int is_blank_text(const char *s)` |
| `is_http_url` | function | `src/freedom.c:88` | `static int is_http_url(const char *s)` |
| `is_https_url` | function | `src/freedom.c:84` | `static int is_https_url(const char *s)` |
| `is_overlay_http` | function | `src/freedom.c:93` | `static int is_overlay_http(const char *s)` |
| `main` | function | `src/freedom.c:1306` | `int main(int argc, char **argv)` |
| `now_us` | function | `src/freedom.c:149` | `static uint64_t now_us(void)` |
| `only` | function | `src/freedom.c:868` | `* styling for the local render only (no network). --images enables image loading * AND rendering, including remote...` |
| `parent` | function | `src/freedom.c:1102` | `* gated by the parent (ln_resolve: a local target stays under the document's  * directory, a remo...` |
| `pool` | function | `src/freedom.c:784` | `* the pool (unconsumed results freed, in-flight fetches joined). */ tab_set_fetcher(t, headless_fetch, (void...` |
| `print_console` | function | `src/freedom.c:430` | `static void print_console(const fb_buffer *log)` |
| `print_css_drops` | function | `src/freedom.c:597` | `static void print_css_drops(const char *html, size_t len)` |
| `print_doc` | function | `src/freedom.c:337` | `static void print_doc(const rd_doc *doc)` |
| `print_dom` | function | `src/freedom.c:447` | `static void print_dom(const rd_doc *doc)` |
| `print_dom_css` | function | `src/freedom.c:462` | `static void print_dom_css(const rd_doc *doc)` |
| `print_usage` | function | `src/freedom.c:55` | `static void print_usage(FILE *fp, const char *prog)` |
| `read_file` | function | `src/freedom.c:243` | `static char *read_file(const char *path, size_t *out_len)` |
| `render_page` | function | `src/freedom.c:720` | `static int render_page(const char *html, size_t len, const char *top_url,                        ...` |
| `run_dump_video` | function | `src/freedom.c:1287` | `static int run_dump_video(const char *url)` |
| `run_headless` | function | `src/freedom.c:1139` | `static int run_headless(const char *target)` |
| `sf_reason` | function | `src/freedom.c:994` | `static const char *sf_reason(sf_status ss)` |
| `timings_dump` | function | `src/freedom.c:163` | `static void timings_dump(void)` |
| `timings_enabled` | function | `src/freedom.c:159` | `static int timings_enabled(void)` |
| `timings_ensure_init` | function | `src/freedom.c:155` | `static void timings_ensure_init(void)` |
| `user_impersonate_enabled` | function | `src/freedom.c:236` | `static int user_impersonate_enabled(void)` |
| `video_fetch_with_fallback` | function | `src/freedom.c:1176` | `static sf_status video_fetch_with_fallback(const char *url, sf_config *cfg,                      ...` |
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
| `HCF_REPO_DIR` | macro | `src/host_conf.c:8` | `#define HCF_REPO_DIR` |
| `HCF_USER_SUBDIR` | macro | `src/host_conf.c:7` | `#define HCF_USER_SUBDIR` |
| `add_dir` | function | `src/host_conf.c:10` | `static void add_dir(hcf_dirs *out, const char *path)` |
| `hcf_load_allowlist` | function | `src/host_conf.c:76` | `hb_set *hcf_load_allowlist(const hcf_dirs *dirs, const char *fname)` |
| `hcf_load_filter` | function | `src/host_conf.c:65` | `hb_set *hcf_load_filter(const hcf_dirs *dirs)` |
| `hcf_search_dirs` | function | `src/host_conf.c:20` | `void hcf_search_dirs(const char *env, const char *home, hcf_dirs *out)` |
| `hcf_search_dirs_from_env` | function | `src/host_conf.c:32` | `void hcf_search_dirs_from_env(hcf_dirs *out)` |
| `load_into` | function | `src/host_conf.c:58` | `static void load_into(hb_set *s, const char *dir, const char *name, hb_list list)` |
| `read_conf` | function | `src/host_conf.c:37` | `static char *read_conf(const char *dir, const char *name)` |
| `HB_INIT_CAP` | macro | `src/hostblock.c:20` | `#define HB_INIT_CAP` |
| `HB_MAX_HOST` | macro | `src/hostblock.c:19` | `#define HB_MAX_HOST` |
| `hb_check` | function | `src/hostblock.c:193` | `hb_decision hb_check(const hb_set *s, const char *host)` |
| `hb_check_subresource` | function | `src/hostblock.c:218` | `hb_decision hb_check_subresource(const hb_set *s, const char *host, int page_trusted)` |
| `hb_count` | function | `src/hostblock.c:243` | `size_t hb_count(const hb_set *s, hb_list list)` |
| `hb_free` | function | `src/hostblock.c:149` | `void hb_free(hb_set *s)` |
| `hb_is_allowlisted` | function | `src/hostblock.c:223` | `int hb_is_allowlisted(const hb_set *s, const char *host)` |
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
| `HC_EVICT_EVERY` | macro | `src/http_cache.c:34` | `#define HC_EVICT_EVERY` |
| `HC_KEY_FILE` | macro | `src/http_cache.c:31` | `#define HC_KEY_FILE` |
| `HC_MAGIC` | macro | `src/http_cache.c:32` | `#define HC_MAGIC` |
| `HC_MAX_AGE_CAP` | macro | `src/http_cache.c:35` | `#define HC_MAX_AGE_CAP` |
| `HC_NAME_HEX` | macro | `src/http_cache.c:33` | `#define HC_NAME_HEX` |
| `_POSIX_C_SOURCE` | macro | `src/http_cache.c:7` | `#define _POSIX_C_SOURCE` |
| `cc_find` | function | `src/http_cache.c:74` | `static int cc_find(const char *cc, const char *name, const char **val)` |
| `cc_max_age` | function | `src/http_cache.c:92` | `static int cc_max_age(const char *cc, long *out)` |
| `days_from_civil` | function | `src/http_cache.c:46` | `static long days_from_civil(int y, int m, int d)` |
| `days_in_month` | function | `src/http_cache.c:39` | `static int days_in_month(int y, int m)` |
| `ent` | struct | `src/http_cache.c:397` | `` |
| `entry_path` | function | `src/http_cache.c:162` | `static int entry_path(const hc_store *s, char kind, const char *partition, const char *url,      ...` |
| `evict` | function | `src/http_cache.c:396` | `static void evict(hc_store *s)` |
| `get_locked` | function | `src/http_cache.c:385` | `static hc_status get_locked(hc_store *s, const char *partition, const char *url, hc_meta *meta,  ...` |
| `has_nl` | function | `src/http_cache.c:293` | `static int has_nl(const char *s)` |
| `hc_body_free` | function | `src/http_cache.c:287` | `void hc_body_free(uint8_t *body, size_t len)` |
| `hc_classify` | function | `src/http_cache.c:136` | `hc_class hc_classify(const hc_meta *m, time_t now)` |
| `hc_clear` | function | `src/http_cache.c:473` | `void hc_clear(hc_store *s)` |
| `hc_close` | function | `src/http_cache.c:279` | `void hc_close(hc_store *s)` |
| `hc_get` | function | `src/http_cache.c:480` | `hc_status hc_get(hc_store *s, const char *partition, const char *url, hc_meta *meta,             ...` |
| `hc_lifetime` | function | `src/http_cache.c:115` | `long hc_lifetime(const hc_meta *m)` |
| `hc_open` | function | `src/http_cache.c:230` | `hc_status hc_open(hc_store **out, const char *dir, const uint8_t wrap[LS_KEY_LEN])` |
| `hc_parse_http_date` | function | `src/http_cache.c:55` | `time_t hc_parse_http_date(const char *s)` |
| `hc_put` | function | `src/http_cache.c:489` | `hc_status hc_put(hc_store *s, const char *partition, const char *url, const hc_meta *meta,       ...` |

Next: [SYMBOLS_p8.md](SYMBOLS_p8.md)
