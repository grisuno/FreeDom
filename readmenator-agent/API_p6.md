# API (page 6 of 9)
Previous: [API_p5.md](API_p5.md)

## src/css_select.c
Depends on: `include/css_select.h`
- `csel_hex_val` (function) `src/css_select.c:23` `int csel_hex_val(char c)` -- CSS Syntax 4.3.7 escape consumption (moved from css.c; shared by quoted content values and selector identifiers).
- `csel_emit_utf8` (function) `src/css_select.c:30` `size_t csel_emit_utf8(unsigned int cp, char *out)`
- `csel_unescape` (function) `src/css_select.c:52` `void csel_unescape(char *dst, size_t cap, const char *src, size_t n)`
- `csel_escape_len` (function) `src/css_select.c:91` `size_t csel_escape_len(const char *s, size_t i, size_t b)`
- `csel_decl_end` (function) `src/css_select.c:104` `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace)`
- `ident_hash` (function) `src/css_select.c:121` `static unsigned long long ident_hash(const char *s, size_t n)` -- 64-bit FNV-1a of the whole identifier: what makes a folded long name exact up to * a hash collision -- and a...
- `csel_ident_fold` (function) `src/css_select.c:127` `void csel_ident_fold(const char *src, size_t len, char *dst)`
- `csel_ident_eq` (function) `src/css_select.c:142` `int csel_ident_eq(const char *stored, const char *tok, size_t tlen)`
- `csel_read_ident` (function) `src/css_select.c:150` `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower)`
- `parse_attr_sel` (function) `src/css_select.c:184` `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)` -- Parses one attribute selector starting at s[*ip] == '[' (within s[.,b)) into *am.
- `parse_nth_arg` (function) `src/css_select.c:241` `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)` -- Parses the An+B argument of the nth-child family, s[a,b) (surrounding space trimmed here).
- `take_sub_arg` (function) `src/css_select.c:293` `static int take_sub_arg(const char *s, size_t a, size_t b, css_sel *sel, int strict);`
- `between` (function) `src/css_select.c:376` `* between ( and ) is split on commas (not inside [] or ());`
- `simple_pseudo_kind` (function) `src/css_select.c:431` `static int simple_pseudo_kind(const char *nm)` -- The PSEUDO_* kind of an argument-less pseudo-class usable inside a * sub-selector, or -1.
- `parse_sub_compound` (function) `src/css_select.c:452` `static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub)` -- Parses one SIMPLE sub-selector span s[a,b) for :not()/:is()/:where(): only tag name, .class, #id, or [attr] (no...
- `parse_compound` (function) `src/css_select.c:517` `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,
                  ...` -- Parses one COMPOUND selector span s[a,b) (no combinators, no surrounding space) into *cp. sel holds the sub-selector...
- `selector` (function) `src/css_select.c:559` `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is
 * dropped. Whitespa...`
- `el_attr_value` (function) `src/css_select.c:655` `static const char *el_attr_value(const css_element *el, const char *name)` -- The value of element attribute `name` (case-insensitive name), or NULL if absent. * A present attribute with no...
- `ends_with` (function) `src/css_select.c:665` `static int ends_with(const char *v, const char *suf, int ci)` -- The value of element attribute `name` (case-insensitive name), or NULL if absent. * A present attribute with no...
- `has_word` (function) `src/css_select.c:673` `static int has_word(const char *v, const char *w, int ci)` -- True if `v` is a whitespace-separated list containing the word `w` (non-empty), * case-folded when ci (the `~=`...
- `attr_matches` (function) `src/css_select.c:688` `static int attr_matches(const css_attr_match *am, const css_element *el)` -- size_t wl = strlen(w); if (wl == 0) return 0; const char *p = v; while (*p != '\0') { while (*p == ' ' || *p == '\t'...
- `nth_matches` (function) `src/css_select.c:708` `static int nth_matches(int A, int B, int idx)` -- True if the 1-based index idx satisfies idx = A*m + B for some integer m >= 0. * idx <= 0 means "unknown sibling...
- `is_form_control` (function) `src/css_select.c:717` `static int is_form_control(const char *tag)` -- True if the 1-based index idx satisfies idx = A*m + B for some integer m >= 0. * idx <= 0 means "unknown sibling...
- `pseudo_matches` (function) `src/css_select.c:726` `static int pseudo_matches(const css_pseudo_match *pm, const css_element *el, const css_sel *sel, const char...` -- if (A > 0) return d >= 0 && d % A == 0; return d <= 0 && (-d) % (long)(-A) == 0; } /* Form controls for :enabled...
- `sub_sel_matches` (function) `src/css_select.c:730` `static int sub_sel_matches(const css_sub_sel *sub, const css_element *el)`
- `compound_matches` (function) `src/css_select.c:979` `static int compound_matches(const css_compound *c, const css_element *el,
                       ...` -- True if one compound matches one element (no ancestor context).
- `built` (function) `src/css_select.c:1014` `* chains the caller built (an element without parent/prev links never matches
 * through that com...`
- `csel_matches` (function) `src/css_select.c:1055` `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,
              ...`

## src/css_text.c
Depends on: `include/css.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_text.h`, `include/css_values.h`
- `ct_family_of` (function) `src/css_text.c:18` `static int ct_family_of(const char *name)` -- Maps one font-family name (a generic keyword or a common family) to a generic css_font_family bucket; -1 if...
- `ct_interp_fontfamily` (function) `src/css_text.c:47` `int ct_interp_fontfamily(const char *v)` -- font-family: the first recognised name in the comma-separated stack wins (its * generic bucket).
- `ct_interp_texttransform` (function) `src/css_text.c:69` `int ct_interp_texttransform(const char *v)`
- `ct_interp_valign` (function) `src/css_text.c:91` `int ct_interp_valign(const char *v)`
- `ct_expand_valign` (function) `src/css_text.c:122` `int ct_expand_valign(const char *val, css_decl *dst, int cap)` -- vertical-align (CSS 2.1 section 10.8.1) has two productions: a keyword, and a <length-percentage> baseline SHIFT...
- `ct_interp_transition_property` (function) `src/css_text.c:139` `int ct_interp_transition_property(const char *v)`
- `ct_interp_whitespace` (function) `src/css_text.c:147` `int ct_interp_whitespace(const char *v)`
- `ct_interp_tabsize` (function) `src/css_text.c:160` `int ct_interp_tabsize(const char *v)` -- break-spaces preserves whitespace and wraps; this engine only models the * wrap/keep distinction, so it collapses to...
- `ct_interp_textdeco_style` (function) `src/css_text.c:171` `int ct_interp_textdeco_style(const char *v)` -- } /* tab-size: a non-negative integer (number of spaces). -1 if unsupported. int ct_interp_tabsize(const char *v) {...
- `ct_interp_textdeco_thickness` (function) `src/css_text.c:182` `int ct_interp_textdeco_thickness(const char *v)` -- text-decoration-thickness: `from-font` (keyword -> 0), or a non-negative length * (px -> px, em/rem x16). -1 if...
- `ct_interp_aspect_ratio` (function) `src/css_text.c:194` `int ct_interp_aspect_ratio(const char *v, int *num, int *den)` -- aspect-ratio: `auto`, a `<ratio>` such as `16/9` or `1.5`, or `auto <ratio>` (auto fallback).
- `ct_interp_direction` (function) `src/css_text.c:227` `int ct_interp_direction(const char *v)` -- num = css_round_clamp(nv * 1000.0, 1, CSS_LEN_MAX); den = css_round_clamp(dv * 1000.0, 1, CSS_LEN_MAX); return 1; }...
- `ct_liststyle_kw` (function) `src/css_text.c:233` `static int ct_liststyle_kw(const char *t)`
- `ct_liststyle_unknown_name` (function) `src/css_text.c:254` `static int ct_liststyle_unknown_name(const char *t)` -- A <counter-style> name this engine has no glyph set for.
- `ct_interp_liststyle` (function) `src/css_text.c:265` `int ct_interp_liststyle(const char *v)` -- list-style-type, or the type token of the list-style shorthand: the first * recognised keyword wins. url() (a...
- `ct_emit_spacing` (function) `src/css_text.c:300` `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
- `ct_expand_shadow` (function) `src/css_text.c:313` `int ct_expand_shadow(const char *val, css_decl *dst, int cap)` -- text-shadow (single layer): collects up to three lengths (dx, dy, blur — blur is ignored) and an optional color, in...

## src/css_values.c
Depends on: `include/css.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`
- `cv_parse_num` (function) `src/css_values.c:11` `static int cv_parse_num(const char *s, double *out, const char **endp)`
- `cv_parse_color` (function) `src/css_values.c:16` `int cv_parse_color(const char *v)`
- `cv_interp_color` (function) `src/css_values.c:36` `int cv_interp_color(const char *v)`
- `cv_color_ok` (function) `src/css_values.c:41` `int cv_color_ok(int c)`
- `cv_bg_alpha_of` (function) `src/css_values.c:46` `int cv_bg_alpha_of(const char *v)`
- `cv_interp_bg` (function) `src/css_values.c:160` `int cv_interp_bg(const char *v)`

## src/css_vars.c
Depends on: `include/css_select.h`, `include/css_vars.h`
- `name_hash` (function) `src/css_vars.c:12` `static size_t name_hash(const char *s, size_t n)`
- `dup_n` (function) `src/css_vars.c:21` `static char *dup_n(const char *s, size_t n)`
- `find_slot` (function) `src/css_vars.c:32` `static size_t find_slot(const cvr_table *t, const char *name, size_t nlen)` -- Index into t->slot where name lives, or the empty slot where it would go. * Requires t->nslot > t->n (the index is...
- `grow` (function) `src/css_vars.c:45` `static int grow(cvr_table *t)` -- Requires t->nslot > t->n (the index is never full). static size_t find_slot(const cvr_table *t, const char *name...
- `cvr_set` (function) `src/css_vars.c:67` `int cvr_set(cvr_table *t, const char *name, size_t nlen, const char *value, size_t vlen)`
- `cvr_get` (function) `src/css_vars.c:94` `const char *cvr_get(const cvr_table *t, const char *name, size_t nlen)`
- `cvr_count` (function) `src/css_vars.c:100` `size_t cvr_count(const cvr_table *t)`
- `cvr_reset` (function) `src/css_vars.c:102` `void cvr_reset(cvr_table *t)`
- `cvr_free` (function) `src/css_vars.c:112` `void cvr_free(cvr_table *t)`
- `is_ws` (function) `src/css_vars.c:120` `static int is_ws(char c)`
- `without_important` (function) `src/css_vars.c:124` `static size_t without_important(const char *val, size_t n)` -- Length of val[0,n) once a trailing !important (optional blanks around the '!') * is removed, trailing blanks included.
- `cvr_collect_decls` (function) `src/css_vars.c:139` `void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b)`
- `scope_get` (function) `src/css_vars.c:164` `static const char *scope_get(const cvr_scope *sc, const char *name, size_t nlen)`
- `resolve_rec` (function) `src/css_vars.c:178` `static int resolve_rec(const char *val, size_t vlen, char *out, size_t outcap,
                  ...`
- `cvr_resolve` (function) `src/css_vars.c:230` `int cvr_resolve(const char *val, char *out, size_t outcap, const cvr_scope *sc)`
- `cvr_lookup` (function) `src/css_vars.c:239` `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen)`

## src/data_url.c
Depends on: `include/data_url.h`
- `lower` (function) `src/data_url.c:16` `static int lower(char c)`
- `ci_starts_with` (function) `src/data_url.c:20` `static int ci_starts_with(const char *s, const char *prefix)`
- `du_is_data_url` (function) `src/data_url.c:28` `int du_is_data_url(const char *url)`
- `du_base64_payload` (function) `src/data_url.c:32` `du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len)`
- `b64_val` (function) `src/data_url.c:61` `static int b64_val(unsigned char c)` -- 0-63 for a base64 alphabet character, -1 otherwise.
- `du_base64_decode` (function) `src/data_url.c:70` `du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len)`
- `hexval` (function) `src/data_url.c:108` `static int hexval(char c)`
- `ascii_ws` (function) `src/data_url.c:115` `static int ascii_ws(char c)`
- `ends_ci` (function) `src/data_url.c:120` `static int ends_ci(const char *s, size_t n, const char *suf)` -- } static int hexval(char c) { if (c >= '0' && c <= '9') return c - '0'; if (c >= 'a' && c <= 'f') return c - 'a' +...
- `du_decode` (function) `src/data_url.c:131` `du_status du_decode(const char *url, char *mime, size_t mime_cap, uint8_t **out, size_t *out_len)`

## src/disk_store.c
Depends on: `include/disk_store.h`, `include/local_store.h`, `include/util.h`
- `fsync_dir` (function) `src/disk_store.c:32` `static void fsync_dir(const char *path)` -- Best-effort fsync of the directory holding path, for crash durability of the * rename.
- `map_ls` (function) `src/disk_store.c:50` `static ds_status map_ls(ls_status s)`
- `ds_write` (function) `src/disk_store.c:66` `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,
               ...`
- `ds_read` (function) `src/disk_store.c:103` `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],
                  uint8_t **ou...`
- `ds_free` (function) `src/disk_store.c:136` `void ds_free(uint8_t *buf, size_t len)`

## src/dom.c
Depends on: `include/css_chain.h`, `include/css_select.h`, `include/dom.h`, `include/html_parse.h`, `include/util.h`
- `to_lower_buf` (function) `src/dom.c:33` `static int to_lower_buf(const char *s, size_t n, char *out, size_t outcap)` -- #include <stdint.h> #include <stdlib.h> #include <string.h> #include <lexbor/dom/dom.h> #include...
- `ptr_hash` (function) `src/dom.c:45` `static size_t ptr_hash(const void *p)`
- `sm_entry_append` (function) `src/dom.c:70` `static int sm_entry_append(sm_entry *e, dom_node_id id)`
- `sm_grow` (function) `src/dom.c:82` `static int sm_grow(strmap *m)`
- `sm_put` (function) `src/dom.c:99` `static int sm_put(strmap *m, const char *key, size_t klen, dom_node_id id)`
- `sm_find` (function) `src/dom.c:127` `static const sm_entry *sm_find(const strmap *m, const char *key, size_t klen)`
- `sm_free` (function) `src/dom.c:139` `static void sm_free(strmap *m)`
- `pm_grow` (function) `src/dom.c:166` `static int pm_grow(ptrmap *m)`
- `pm_put` (function) `src/dom.c:183` `static int pm_put(ptrmap *m, const void *key, dom_node_id id)`
- `pm_get` (function) `src/dom.c:200` `static int pm_get(const ptrmap *m, const void *key, dom_node_id *out)`
- `pm_free` (function) `src/dom.c:211` `static void pm_free(ptrmap *m)`
- `node_next` (function) `src/dom.c:232` `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` -- /* --- the index --- struct dom_index { lxb_dom_node_t      **nodes;    /* arena: id -> element node, in document...
- `valid` (function) `src/dom.c:242` `static int valid(const dom_index *idx, dom_node_id n)`
- `index_element` (function) `src/dom.c:254` `static int index_element(dom_index *idx, lxb_dom_element_t *el, dom_node_id id)` -- A handle that is an ELEMENT: every element-only operation (tag, attributes, selectors, innerHTML, being a parent)...
- `dom_build` (function) `src/dom.c:291` `dom_status dom_build(const hp_document *doc, dom_index **out)`
- `dom_free` (function) `src/dom.c:332` `void dom_free(dom_index *idx)`
- `dom_node_count` (function) `src/dom.c:344` `size_t dom_node_count(const dom_index *idx)`
- `dom_get_element_by_id` (function) `src/dom.c:348` `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)`
- `copy_ids` (function) `src/dom.c:354` `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)`
- `dom_get_by_tag` (function) `src/dom.c:361` `size_t dom_get_by_tag(const dom_index *idx, const char *tag,
                      dom_node_id *o...`
- `dom_get_by_class` (function) `src/dom.c:370` `size_t dom_get_by_class(const dom_index *idx, const char *cls,
                        dom_node_i...`
- `id_of` (function) `src/dom.c:383` `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)` -- Max complex selectors in one comma-separated list.
- `parse_selector_list` (function) `src/dom.c:393` `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)` -- Parses a selector list "a, b, c" into up to cap css_sel.
- `node_matches_any` (function) `src/dom.c:426` `static int node_matches_any(const lxb_dom_node_t *cn,
                            const css_sel *...` -- s.order = (int)n; s.rule = 0; out[n++] = s; } } start = i + 1; } break; default: break; } } return n; } /* Nonzero...
- `count` (function) `src/dom.c:437` `* count (may exceed cap), and returns DOM_NODE_NONE. */
static dom_node_id qs_walk(const dom_inde...`
- `dom_query_selector` (function) `src/dom.c:467` `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,
                          ...`
- `dom_query_selector_all` (function) `src/dom.c:476` `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,
                           ...`
- `dom_matches` (function) `src/dom.c:487` `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)`
- `dom_closest` (function) `src/dom.c:496` `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,
                        const cha...`
- `dom_document_position` (function) `src/dom.c:512` `size_t dom_document_position(const dom_index *idx, dom_node_id node)`
- `dom_precedes` (function) `src/dom.c:517` `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)`
- `dom_node_at` (function) `src/dom.c:522` `dom_node_id dom_node_at(const dom_index *idx, size_t position)`
- `dom_parent` (function) `src/dom.c:527` `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)`
- `dom_first_child` (function) `src/dom.c:537` `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)`
- `dom_next_sibling` (function) `src/dom.c:545` `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)`
- `dom_tag_name` (function) `src/dom.c:553` `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)`
- `dom_get_attribute` (function) `src/dom.c:564` `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,
                           ...`
- `dom_attribute_names` (function) `src/dom.c:586` `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,
                           con...`
- `dom_text_content` (function) `src/dom.c:604` `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)`
- `dom_document_title` (function) `src/dom.c:614` `const char *dom_document_title(const dom_index *idx, size_t *len)`
- `dom_set_text_content` (function) `src/dom.c:627` `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,
                               ...`
- `dom_set_document_title` (function) `src/dom.c:661` `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)`
- `idx_push` (function) `src/dom.c:672` `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)` -- return DOM_OK; } dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len) { if (idx == NULL...
- `dom_create_element` (function) `src/dom.c:690` `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)`
- `dom_append_child` (function) `src/dom.c:710` `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
- `dom_remove_child` (function) `src/dom.c:724` `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
- `dom_set_attribute` (function) `src/dom.c:732` `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,
                             const...`
- `dom_remove_attribute` (function) `src/dom.c:761` `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)`
- `index_subtree` (function) `src/dom.c:770` `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)` -- } } return DOM_OK; } dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name) { if...
- `dom_set_inner_html` (function) `src/dom.c:780` `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,
                              con...`
- `ih_append` (function) `src/dom.c:833` `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)`
- `ih_free` (function) `src/dom.c:860` `static void ih_free(ih_acc *a)`
- `dom_get_inner_html` (function) `src/dom.c:887` `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,
                           ...`
- `dom_insert_before` (function) `src/dom.c:917` `dom_status dom_insert_before(dom_index *idx, dom_node_id parent, dom_node_id child,
             ...`
- `dom_clone_node` (function) `src/dom.c:934` `dom_status dom_clone_node(dom_index *idx, dom_node_id node, int deep, dom_node_id *out_id)`
- `dom_move_children` (function) `src/dom.c:948` `dom_status dom_move_children(dom_index *idx, dom_node_id src, dom_node_id parent,
               ...`
- `char_kind` (function) `src/dom.c:981` `static int char_kind(const lxb_dom_node_t *n)`
- `handle_of` (function) `src/dom.c:992` `static dom_node_id handle_of(dom_index *idx, lxb_dom_node_t *n)` -- /* --- text and comment nodes (spec/dom.md 9) --- static int char_kind(const lxb_dom_node_t *n) { switch (n->type) {...
- `dom_node_kind` (function) `src/dom.c:1000` `int dom_node_kind(const dom_index *idx, dom_node_id node)`
- `dom_child_node` (function) `src/dom.c:1004` `dom_node_id dom_child_node(dom_index *idx, dom_node_id node, int last)`
- `dom_sibling_node` (function) `src/dom.c:1011` `dom_node_id dom_sibling_node(dom_index *idx, dom_node_id node, int prev)`
- `dom_create_char_node` (function) `src/dom.c:1018` `dom_status dom_create_char_node(dom_index *idx, int kind, const char *text, size_t len,
         ...`

## src/dom_debug.c
Depends on: `include/box_style.h`, `include/css.h`, `include/dom_debug.h`, `include/flex_layout.h`, `include/page_view.h`
- `dd_putc` (function) `src/dom_debug.c:31` `static void dd_putc(dd_cursor *c, char ch)`
- `dd_emit` (function) `src/dom_debug.c:36` `static void dd_emit(dd_cursor *c, const char *s, size_t len)`
- `dd_puts` (function) `src/dom_debug.c:40` `static void dd_puts(dd_cursor *c, const char *s)`
- `dd_printf` (function) `src/dom_debug.c:48` `static void dd_printf(dd_cursor *c, const char *fmt, ...)` -- Formats short fixed fields (ints, hex colours, fixed tokens) only; the variable hostile fields go through dd_field.
- `dd_w` (function) `src/dom_debug.c:80` `static int dd_w(int v)` -- A border/outline width or radius that is unset (PV_LEN_UNSET) or negative reads as * 0 ("no border"); otherwise the...
- `dd_color` (function) `src/dom_debug.c:83` `static void dd_color(dd_cursor *c, int rgb)` -- A border/outline width or radius that is unset (PV_LEN_UNSET) or negative reads as * 0 ("no border"); otherwise the...
- `dd_display_name` (function) `src/dom_debug.c:88` `static const char *dd_display_name(int d)`
- `dd_justify_name` (function) `src/dom_debug.c:96` `static const char *dd_justify_name(int j)`
- `dd_align_name` (function) `src/dom_debug.c:108` `static const char *dd_align_name(int a)`
- `dd_position_name` (function) `src/dom_debug.c:118` `static const char *dd_position_name(int p)`
- `dd_visibility_name` (function) `src/dom_debug.c:129` `static const char *dd_visibility_name(int v)`
- `dd_mix_blend_name` (function) `src/dom_debug.c:137` `static const char *dd_mix_blend_name(int m)`
- `dd_overflow_name` (function) `src/dom_debug.c:156` `static const char *dd_overflow_name(int o)`
- `dd_cursor_name` (function) `src/dom_debug.c:165` `static const char *dd_cursor_name(int c)`
- `dd_text_overflow_name` (function) `src/dom_debug.c:182` `static const char *dd_text_overflow_name(int t)`
- `dd_inset` (function) `src/dom_debug.c:187` `static int dd_inset(int v)` -- case CSS_CUR_WAIT:        return "wait"; case CSS_CUR_CROSSHAIR:   return "crosshair"; case CSS_CUR_GRAB...
- `dd_object_fit_name` (function) `src/dom_debug.c:191` `static const char *dd_object_fit_name(int o)`
- `dd_image_rendering_name` (function) `src/dom_debug.c:202` `static const char *dd_image_rendering_name(int r)`
- `dd_border_style_name` (function) `src/dom_debug.c:211` `static const char *dd_border_style_name(int s)`
- `dd_box_line` (function) `src/dom_debug.c:244` `static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b)`
- `dd_block_line` (function) `src/dom_debug.c:304` `static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b)`
- `dd_format` (function) `src/dom_debug.c:380` `size_t dd_format(const rd_doc *doc, char *out, size_t cap)`
- `dd_format_css` (function) `src/dom_debug.c:412` `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)` -- } dd_puts(&c, "[blocks]\n"); for (size_t i = 0; i < nblocks; ++i) { const rd_block *b = rd_at(doc, i); if (b !=...

## src/download.c
Depends on: `include/download.h`, `include/pdf_export.h`
- `lc` (function) `src/download.c:13` `static int lc(int c)` -- download — pure helpers for "save this resource to disk".
- `ci_find` (function) `src/download.c:19` `static const char *ci_find(const char *hay, const char *needle)` -- #include "download.h" #include "pdf_export.h"   /* pe_safe_basename: the single audited sanitizer #include <ctype.h>...
- `media_type` (function) `src/download.c:33` `static void media_type(const char *content_type, char *buf, size_t bufsz)` -- Writes the lowercased media type of content_type (the part before ';', with * surrounding spaces trimmed) into buf.
- `dl_should_download` (function) `src/download.c:47` `int dl_should_download(const char *content_type, const char *content_disposition)`
- `dl_ext_for_type` (function) `src/download.c:58` `const char *dl_ext_for_type(const char *content_type)`
- `copy_span` (function) `src/download.c:85` `static void copy_span(const char *src, const char *end, char *buf, size_t bufsz)` -- { "application/xhtml+xml",  ".html" }, { "text/plain",            ".txt"  }, { "image/png",             ".png"  }, {...
- `extract_disposition_name` (function) `src/download.c:96` `static int extract_disposition_name(const char *cd, char *buf, size_t bufsz)` -- Extracts a filename candidate from a Content-Disposition value into buf.
- `extract_url_name` (function) `src/download.c:134` `static int extract_url_name(const char *url, char *buf, size_t bufsz)` -- Extracts the last path segment of url (without ?query or #fragment) into buf. * Returns 1 if a non-empty candidate...
- `has_extension` (function) `src/download.c:148` `static int has_extension(const char *name)` -- Does name already carry an extension (a '.' past the first byte with at least * one character after it)?
- `dl_pick_name` (function) `src/download.c:153` `dl_status dl_pick_name(const char *url, const char *content_disposition,
                       c...`
- `dl_build_path` (function) `src/download.c:195` `dl_status dl_build_path(const char *dir, const char *name, char *out, size_t outsz)`
- `dl_check_size` (function) `src/download.c:213` `dl_status dl_check_size(size_t len)`

## src/flex_layout.c
Depends on: `include/flex_layout.h`
- `nn` (function) `src/flex_layout.c:18` `static double nn(double v)` -- No I/O, no global state, no dynamic allocation: fixed-size stack scratch buffers bounded by FX_MAX_ITEMS (no VLAs).
- `fx_flex_line` (function) `src/flex_layout.c:22` `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                ...`
- `fx_grid_columns` (function) `src/flex_layout.c:127` `fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          doubl...`
- `fx_grid_columns_weighted` (function) `src/flex_layout.c:132` `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                      ...`
- `fx_grid_place_span` (function) `src/flex_layout.c:166` `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                      ...`
- `fx_grid_area_hash` (function) `src/flex_layout.c:270` `unsigned fx_grid_area_hash(const char *name)`
- `area_token_is_null_cell` (function) `src/flex_layout.c:294` `static int area_token_is_null_cell(const char *tok, size_t len)` -- 0 is reserved for "no name" (the null cell token), so a name that hashes to * it is nudged; the alternative is a...
- `fx_grid_areas_parse` (function) `src/flex_layout.c:300` `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)`
- `fx_grid_area_rect` (function) `src/flex_layout.c:375` `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,
                            int ...`
- `float_pack_impl` (function) `src/flex_layout.c:417` `static fx_status float_pack_impl(const double *width, const int *side, size_t n,
                ...` -- Shared packer: wrap == 0 is the single-row v1 contract (overflow clamps in place); wrap != 0 starts a new row...
- `fx_float_insets` (function) `src/flex_layout.c:457` `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,
                 ...`
- `fx_float_pack` (function) `src/flex_layout.c:497` `fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        d...`
- `fx_float_pack_wrap` (function) `src/flex_layout.c:502` `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,
                    ...`
- `fx_grid_cell` (function) `src/flex_layout.c:544` `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)`
- `fx_auto_margins` (function) `src/flex_layout.c:556` `fx_status fx_auto_margins(fx_result *res, size_t n, const unsigned char *auto_l,
                ...` -- } void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col) { if (row == NULL || col == NULL) return...
- `fx_auto_min_size` (function) `src/flex_layout.c:579` `double fx_auto_min_size(double min_content, double basis, double author_min,
                    ...`
- `fx_multicol_used` (function) `src/flex_layout.c:593` `fx_status fx_multicol_used(double avail_w, int column_count, double column_width,
               ...`
- `fx_multicol_balance` (function) `src/flex_layout.c:630` `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,
                        ...`
- `fx_justify_name` (function) `src/flex_layout.c:661` `const char *fx_justify_name(fx_justify j)`
- `fx_column_place` (function) `src/flex_layout.c:673` `fx_status fx_column_place(const double *h, const double *grow, size_t n, double gap,
            ...`
- `fx_column_place_m` (function) `src/flex_layout.c:680` `fx_status fx_column_place_m(const double *h, const double *grow, const int *mauto,
              ...`
- `fx_cross_offset` (function) `src/flex_layout.c:741` `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r)`

## src/form.c
Depends on: `include/form.h`
- `put_char` (function) `src/form.c:17` `static int put_char(char *out, size_t outsz, size_t *pos, char c)` -- No I/O, no global state.
- `enc_component` (function) `src/form.c:25` `static int enc_component(const char *s, char *out, size_t outsz, size_t *pos)` -- Encodes one component per the WHATWG application/x-www-form-urlencoded byte * serialiser.
- `fm_encode` (function) `src/form.c:43` `fm_status fm_encode(const fm_field *fields, size_t n,
                    char *out, size_t outsz...`
- `copy_fit` (function) `src/form.c:66` `static int copy_fit(char *dst, size_t dstsz, const char *src)` -- if (fields[i].name == NULL) continue; /* a nameless control is not submitted if (!first && put_char(out, outsz...
- `clean_action` (function) `src/form.c:75` `static int clean_action(const char *action, char *out, size_t outsz)` -- Removes TAB/LF/CR and trims leading/trailing ASCII spaces (WHATWG cleaning of a * URL-bearing attribute).
- `strip_query` (function) `src/form.c:93` `static void strip_query(char *url)` -- if (c == '\t' || c == '\n' || c == '\r') continue; if (o + 1 >= outsz) return -1; out[o++] = c; } out[o] = '\0'...
- `resolve_target` (function) `src/form.c:101` `static fm_block_reason resolve_target(const char *base, const char *act,
                        ...` -- Resolves the cleaned action into a validated absolute https URL R, or returns a * block reason.
- `fm_build` (function) `src/form.c:120` `fm_status fm_build(const char *base, const char *action, fm_method method,
                   con...`

## src/frame_clock.c
Depends on: `include/frame_clock.h`
- `fc_set_active` (function) `src/frame_clock.c:16` `void fc_set_active(fc_clock *c, int active)`
- `fc_needs_tick` (function) `src/frame_clock.c:21` `int fc_needs_tick(const fc_clock *c)`
- `fc_interval_ms` (function) `src/frame_clock.c:26` `int fc_interval_ms(const fc_clock *c)`

## src/freebug.c
Depends on: `include/freebug.h`
- `whole` (function) `src/freebug.c:5` `* FB_MAX_TOTAL_BYTES is dropped whole (overflow flag raised, prior entries kept);`
- `fb_buffer_init` (function) `src/freebug.c:15` `void fb_buffer_init(fb_buffer *b)`
- `fb_buffer_push` (function) `src/freebug.c:19` `int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)`
- `fb_buffer_push_loc` (function) `src/freebug.c:23` `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len,
                   ...`
- `fb_buffer_reset` (function) `src/freebug.c:78` `void fb_buffer_reset(fb_buffer *b)`
- `fb_buffer_free` (function) `src/freebug.c:91` `void fb_buffer_free(fb_buffer *b)`
- `fb_buffer_count` (function) `src/freebug.c:101` `size_t fb_buffer_count(const fb_buffer *b)`
- `fb_buffer_at` (function) `src/freebug.c:105` `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)`
- `fb_level_name` (function) `src/freebug.c:110` `const char *fb_level_name(int level)`

## src/freedom.c
Depends on: `include/dom_debug.h`, `include/freebug.h`, `include/hls.h`, `include/hostblock.h`, `include/html_parse.h`, `include/js_policy.h`, `include/link_nav.h`, `include/media_decoder.h`, `include/net_realm.h`, `include/page_view.h`, `include/perf_trace.h`, `include/prefetch.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/tab.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/webcaps.h`
- `print_usage` (function) `src/freedom.c:47` `static void print_usage(FILE *fp, const char *prog)`
- `is_https_url` (function) `src/freedom.c:73` `static int is_https_url(const char *s)`
- `is_http_url` (function) `src/freedom.c:77` `static int is_http_url(const char *s)`
- `is_overlay_http` (function) `src/freedom.c:82` `static int is_overlay_http(const char *s)` -- fprintf(fp, "  --dump-video-url: headless, print the first detected video source URL to stdout (no truncation)\n")...
- `now_us` (function) `src/freedom.c:136` `static uint64_t now_us(void)`
- `timings_ensure_init` (function) `src/freedom.c:142` `static void timings_ensure_init(void)`
- `timings_enabled` (function) `src/freedom.c:146` `static int timings_enabled(void)`
- `timings_dump` (function) `src/freedom.c:150` `static void timings_dump(void)`
- `user_impersonate_enabled` (function) `src/freedom.c:198` `static int user_impersonate_enabled(void)`
- `read_file` (function) `src/freedom.c:205` `static char *read_file(const char *path, size_t *out_len)` -- User opt-in for TLS-impersonation blend: --impersonate or FREEDOM_IMPERSONATE=1.
- `headless_load_hosts` (function) `src/freedom.c:223` `static void headless_load_hosts(void)`
- `is_blank_text` (function) `src/freedom.c:253` `static int is_blank_text(const char *s)` -- No impersonate.conf: third signal is the user flag (--impersonate / * FREEDOM_IMPERSONATE=1). impersonate.conf on...
- `print_doc` (function) `src/freedom.c:266` `static void print_doc(const rd_doc *doc)` -- Writes the render document as deterministic, flowing plain text for a terminal and for an AI agent (content as data...
- `print_console` (function) `src/freedom.c:359` `static void print_console(const fb_buffer *log)` -- Prints the captured Freebug console (the developer-visible JS transcript) to stdout, one entry per line, prefixed...
- `print_dom` (function) `src/freedom.c:376` `static void print_dom(const rd_doc *doc)` -- Prints the paint-ready render tree (dom_debug) to stdout.
- `print_dom_css` (function) `src/freedom.c:391` `static void print_dom_css(const rd_doc *doc)` -- Prints the CSS property inspector (dd_format_css) to stdout.
- `gets` (function) `src/freedom.c:411` `* gate a click gets (https-only, no downgrade, no foreign scheme), so relative * subresources work. Realm-routed...`
- `headless_fetch` (function) `src/freedom.c:415` `static int headless_fetch(void *ctx, const char *method, const char *url,
                       ...` -- tab_fetch_fn for the headless renderer: a policy-checked subresource fetch for page XHR/fetch and external <script...
- `foldback_cookies` (function) `src/freedom.c:477` `static void foldback_cookies(const char *url, const char *jar)` -- Folds a page's document.cookie jar ("a=1; b=2") back into the ephemeral network * jar, one pair at a time, so JS-set...
- `print_css_drops` (function) `src/freedom.c:501` `static void print_css_drops(const char *html, size_t len)` -- Prints the author-CSS drop report for `html`, sorted by occurrence count.
- `render_page` (function) `src/freedom.c:532` `static int render_page(const char *html, size_t len, const char *top_url,
                       ...`
- `pool` (function) `src/freedom.c:592` `* the pool (unconsumed results freed, in-flight fetches joined). */ tab_set_fetcher(t, headless_fetch, (void...`
- `only` (function) `src/freedom.c:645` `* styling for the local render only (no network). --images enables image loading * AND rendering, including remote...`
- `sf_reason` (function) `src/freedom.c:757` `static const char *sf_reason(sf_status ss)`
- `fetch_and_render_one` (function) `src/freedom.c:776` `static int fetch_and_render_one(const char *url, char **out_nav)` -- Fetches one url with secure_fetch and renders the result.
- `BLOCKED` (function) `src/freedom.c:802` `* is BLOCKED (fail closed), never leaked over the clearnet. */ nr_route route = nr_route_for(url, global_net);`
- `elsewhere` (function) `src/freedom.c:837` `* page whose script immediately forwards elsewhere (e.g. a search engine's
 * JS-capability inter...`
- `parent` (function) `src/freedom.c:863` `* gated by the parent (ln_resolve: a local target stays under the document's
 * directory, a remo...`
- `run_headless` (function) `src/freedom.c:900` `static int run_headless(const char *target)`
- `video_fetch_with_fallback` (function) `src/freedom.c:936` `static sf_status video_fetch_with_fallback(const char *url, sf_config *cfg,
                     ...` -- Fetches a URL with TLS fallbacks (PQ-hybrid -> classical KE -> allowlisted insecure), same chain as...
- `run_dump_video` (function) `src/freedom.c:1047` `static int run_dump_video(const char *url)` -- -dump-video handler: fetches a video URL and writes the stream to a file * or stdout.
- `main` (function) `src/freedom.c:1066` `int main(int argc, char **argv)`

## src/hls.c
Depends on: `include/hls.h`
- `last_char` (function) `src/hls.c:38` `static const char *last_char(const char *s, size_t n, int c)` -- Finds the last occurrence of character `c` in `s` (length `n`). * Returns NULL if not found.
- `name` (function) `src/hls.c:46` `* attr is the attribute name (e.g. "BANDWIDTH=");`
- `parse_attr_long` (function) `src/hls.c:48` `static int parse_attr_long(const char *attrs, const char *end,
                           const c...` -- Extracts a named attribute value from an #EXT-X-STREAM-INF attribute string. attr is the attribute name (e.g....
- `parse_attr_resolution` (function) `src/hls.c:62` `static void parse_attr_resolution(const char *attrs, const char *end,
                           ...` -- static int parse_attr_long(const char *attrs, const char *end, const char *attr, long *val) { size_t alen =...
- `hls_parse` (function) `src/hls.c:80` `hls_status hls_parse(const char *text, size_t len, hls_playlist **out)`
- `hls_select_variant` (function) `src/hls.c:202` `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h)`
- `hls_resolve_url` (function) `src/hls.c:223` `size_t hls_resolve_url(const char *base_url, const char *segment_url,
                       char...`
- `hls_playlist_free` (function) `src/hls.c:253` `void hls_playlist_free(hls_playlist *pl)`

## src/hostblock.c
Depends on: `include/hostblock.h`, `include/util.h`
- `table_probe` (function) `src/hostblock.c:38` `static size_t table_probe(const hb_table *t, const char *key, size_t klen)` -- Finds the slot for key (length klen) in t, which must have a free slot.
- `table_grow` (function) `src/hostblock.c:49` `static int table_grow(hb_table *t, size_t newcap)` -- Finds the slot for key (length klen) in t, which must have a free slot.
- `table_insert` (function) `src/hostblock.c:71` `static int table_insert(hb_table *t, const char *key, size_t klen)` -- Inserts key (length klen) into t, deduping.
- `table_contains` (function) `src/hostblock.c:92` `static int table_contains(const hb_table *t, const char *key)`
- `table_free` (function) `src/hostblock.c:98` `static void table_free(hb_table *t)`
- `lower` (function) `src/hostblock.c:107` `static char lower(char c)`
- `is_ip_token` (function) `src/hostblock.c:113` `static int is_ip_token(const char *s, size_t n)` -- A token made only of digits, '.' and ':' is an IP literal (v4 or v6), not a * domain.
- `is_domain_char` (function) `src/hostblock.c:122` `static int is_domain_char(char c)` -- A token made only of digits, '.' and ':' is an IP literal (v4 or v6), not a * domain.
- `hb_new` (function) `src/hostblock.c:144` `hb_set *hb_new(void)`
- `hb_free` (function) `src/hostblock.c:149` `void hb_free(hb_set *s)`
- `hb_load` (function) `src/hostblock.c:156` `hb_status hb_load(hb_set *s, const char *text, hb_list list)`
- `hb_check` (function) `src/hostblock.c:193` `hb_decision hb_check(const hb_set *s, const char *host)`
- `hb_is_allowlisted` (function) `src/hostblock.c:218` `int hb_is_allowlisted(const hb_set *s, const char *host)`
- `hb_count` (function) `src/hostblock.c:238` `size_t hb_count(const hb_set *s, hb_list list)`

## src/hostedit.c
Depends on: `include/hostedit.h`
- `he_lower` (function) `src/hostedit.c:12` `static char he_lower(char c)`
- `is_label_char` (function) `src/hostedit.c:16` `static int is_label_char(char c)`
- `valid_host` (function) `src/hostedit.c:22` `static int valid_host(const char *host, size_t n)` -- #include "hostedit.h" #include <string.h> static char he_lower(char c) { return (c >= 'A' && c <= 'Z') ?
- `he_make_line` (function) `src/hostedit.c:41` `he_status he_make_line(const char *host, char *out, size_t cap)`
- `is_ip_token` (function) `src/hostedit.c:67` `static int is_ip_token(const char *ts, const char *te)` -- True if the token looks like an IPv4 dotted-quad / contains only digits and dots * (matches hostblock's is_ip_token...
- `he_scan` (function) `src/hostedit.c:80` `static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), void *ctx)` -- Visits each domain token (non-comment, non-IP) of a hosts-format text in document order, calling fn(ts, tl, ctx).
- `has_host_cb` (function) `src/hostedit.c:105` `static int has_host_cb(const char *ts, size_t tl, void *ctx)`
- `he_text_has_host` (function) `src/hostedit.c:109` `int he_text_has_host(const char *text, const char *host)`
- `contains_ci` (function) `src/hostedit.c:115` `static int contains_ci(const char *hs, size_t hl, const char *needle)` -- } return 0; } static int has_host_cb(const char *ts, size_t tl, void *ctx) { return token_eq_host(ts, ts + tl...
- `starts_with_ci` (function) `src/hostedit.c:128` `static int starts_with_ci(const char *hs, size_t hl, const char *pfx)`
- `suggest_cb` (function) `src/hostedit.c:144` `static int suggest_cb(const char *ts, size_t tl, void *vctx)`
- `he_suggest` (function) `src/hostedit.c:164` `int he_suggest(const char *text, const char *query,
               char results[][HE_MAX_HOST + 1...`

## src/html_parse.c
Depends on: `include/dom.h`, `include/html_parse.h`, `include/util.h`
- `dup_bytes` (function) `src/html_parse.c:27` `static char *dup_bytes(const lxb_char_t *src, size_t len)`
- `node_next` (function) `src/html_parse.c:37` `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` -- }; /* --- helpers --- static char *dup_bytes(const lxb_char_t *src, size_t len) { if (len == (size_t)-1) return...
- `attr_is_event_handler` (function) `src/html_parse.c:47` `static int attr_is_event_handler(const lxb_dom_attr_t *attr)`
- `node_is_script` (function) `src/html_parse.c:54` `static int node_is_script(const lxb_dom_node_t *node)`
- `strip_scripts` (function) `src/html_parse.c:60` `static void strip_scripts(lxb_html_document_t *document)`
- `type_is` (function) `src/html_parse.c:100` `static int type_is(const lxb_char_t *t, size_t len, const char *word)` -- HTML "the script element": type="module" (ASCII case-insensitive, whitespace * stripped) is an ES module; nothing...
- `type_is_module` (function) `src/html_parse.c:117` `static int type_is_module(const lxb_char_t *t, size_t len)`
- `script_classify` (function) `src/html_parse.c:121` `static int script_classify(const lxb_dom_node_t *n,
                           const lxb_char_t *...`
- `hp_extract_script_list` (function) `src/html_parse.c:164` `hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count)` -- Collects each executable <script> as its own entry, in document order: inline source for classic inline scripts, the...
- `lxb_dom_element_has_attribute` (function) `src/html_parse.c:230` `&& lxb_dom_element_has_attribute(sel, (const lxb_char_t *)"nomodule", 8);`
- `hp_free_scripts` (function) `src/html_parse.c:238` `void hp_free_scripts(hp_script *scripts, size_t count)`
- `attr_has_token_ci` (function) `src/html_parse.c:251` `static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle)` -- Whitespace-separated token test over a length-delimited attribute value, ASCII case-insensitive: rel="preload...
- `link_is_active_stylesheet` (function) `src/html_parse.c:272` `static int link_is_active_stylesheet(lxb_dom_element_t *el,
                                     ...` -- An applicable stylesheet <link>: rel token "stylesheet" and not "alternate"; a non-empty href; media absent/empty or...
- `hp_extract_stylesheet_hrefs` (function) `src/html_parse.c:294` `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count)`
- `hp_free_stylesheet_hrefs` (function) `src/html_parse.c:328` `void hp_free_stylesheet_hrefs(char **hrefs, size_t count)`
- `strip_event_handlers` (function) `src/html_parse.c:334` `static void strip_event_handlers(lxb_html_document_t *document)`
- `hp_config_default` (function) `src/html_parse.c:357` `hp_config hp_config_default(void)`
- `hp_validate_input` (function) `src/html_parse.c:365` `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg)`
- `hp_parse` (function) `src/html_parse.c:375` `hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out)`
- `hp_element_count` (function) `src/html_parse.c:409` `size_t hp_element_count(const hp_document *doc)`
- `hp_script_count` (function) `src/html_parse.c:419` `size_t hp_script_count(const hp_document *doc)`
- `hp_event_handler_count` (function) `src/html_parse.c:429` `size_t hp_event_handler_count(const hp_document *doc)`
- `hp_extract_text` (function) `src/html_parse.c:445` `char *hp_extract_text(const hp_document *doc, size_t *out_len)`
- `hp_get_title` (function) `src/html_parse.c:464` `char *hp_get_title(const hp_document *doc, size_t *out_len)`
- `hp_free` (function) `src/html_parse.c:479` `void hp_free(char *buf)`
- `hp_document_free` (function) `src/html_parse.c:483` `void hp_document_free(hp_document *doc)`
- `hp_document_root` (function) `src/html_parse.c:489` `const void *hp_document_root(const hp_document *doc)`

## src/image_decode.c
Depends on: `include/image_decode.h`
- `exit` (function) `src/image_decode.c:6` `* malformed stream fails closed instead of calling exit(). GIF uses an own pure-C * bounded LZW decoder (no giflib)....`
- `read_be32` (function) `src/image_decode.c:52` `static uint32_t read_be32(const uint8_t *p)`
- `img_png_dimensions` (function) `src/image_decode.c:57` `img_status img_png_dimensions(const uint8_t *bytes, size_t len,
                              uin...`
- `img_dimensions_ok` (function) `src/image_decode.c:68` `int img_dimensions_ok(uint32_t w, uint32_t h)`
- `img_fit` (function) `src/image_decode.c:76` `void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,
             double *out_w, do...`
- `premultiply` (function) `src/image_decode.c:90` `static void premultiply(uint8_t *data, size_t pixels)` -- void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h, double *out_w, double *out_h) { if (out_w == NULL...
- `img_decode_png` (function) `src/image_decode.c:102` `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)`
- `jpeg_error_longjmp` (function) `src/image_decode.c:158` `static void jpeg_error_longjmp(j_common_ptr cinfo)`
- `jpeg_silence` (function) `src/image_decode.c:164` `static void jpeg_silence(j_common_ptr cinfo)` -- libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG * fails closed (IMG_ERR_DECODE)...
- `img_decode_jpeg` (function) `src/image_decode.c:166` `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)`
- `gr_u8` (function) `src/image_decode.c:260` `static int gr_u8(gif_reader *r, uint8_t *out)`
- `gr_u16le` (function) `src/image_decode.c:266` `static int gr_u16le(gif_reader *r, uint16_t *out)`
- `gr_skip` (function) `src/image_decode.c:273` `static int gr_skip(gif_reader *r, size_t n)`
- `gr_skip_subblocks` (function) `src/image_decode.c:280` `static int gr_skip_subblocks(gif_reader *r)` -- static int gr_u16le(gif_reader *r, uint16_t *out) { if (r->pos + 2u > r->len) return 0; out =...
- `gb_next_code` (function) `src/image_decode.c:298` `static int gb_next_code(gif_bits *b, unsigned width, unsigned *out)`
- `gif_deinterlace_row` (function) `src/image_decode.c:319` `static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh)` -- } uint8_t byte; if (!gr_u8(b->r, &byte)) return 0; b->block_left--; b->acc |= (uint32_t)byte << b->nbits; b->nbits...
- `gif_put_pixel` (function) `src/image_decode.c:334` `static void gif_put_pixel(uint32_t *canvas, uint32_t cw, uint32_t ch,
                          u...` -- Writes one palette pixel into the canvas at frame-relative index i (clipped to * the canvas; transparent index ->...
- `img_decode_gif` (function) `src/image_decode.c:354` `img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out)`
- `img_decode_webp` (function) `src/image_decode.c:520` `img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out)`
- `img_decode` (function) `src/image_decode.c:553` `img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out)`
- `img_pixels_free` (function) `src/image_decode.c:566` `void img_pixels_free(img_pixels *p)`
- `img_format_name` (function) `src/image_decode.c:575` `const char *img_format_name(img_format f)`

## src/import_map.c
Depends on: `include/import_map.h`
- `ws` (function) `src/import_map.c:39` `static void ws(jr *r)`
- `eat` (function) `src/import_map.c:44` `static int eat(jr *r, char c)`
- `hex4` (function) `src/import_map.c:50` `static int hex4(const char *s, uint32_t *out)`
- `put_utf8` (function) `src/import_map.c:64` `static size_t put_utf8(char *o, uint32_t cp)`
- `str` (function) `src/import_map.c:78` `static char *str(jr *r)` -- A JSON string into an owned UTF-8 buffer (escapes decoded; a lone surrogate or a * raw control character is malformed).
- `skip` (function) `src/import_map.c:128` `static void skip(jr *r, int depth)` -- } n += put_utf8(o + n, cp);   /* <= the 6/12 escape bytes it replaces break; } default: goto fail; } } fail...
- `url_like` (function) `src/import_map.c:156` `static int url_like(const char *s)`
- `dup_s` (function) `src/import_map.c:168` `static char *dup_s(const char *s)`
- `clear` (function) `src/import_map.c:175` `static void clear(im_map *m)`
- `add` (function) `src/import_map.c:185` `static int add(im_map *m, int scope, const char *key, const char *addr, const char *doc_url,
    ...` -- if (d != NULL) memcpy(d, s, n + 1); return d; } static void clear(im_map *m) { for (size_t i = 0; i < m->n; ++i) {...
- `specifier_map` (function) `src/import_map.c:209` `static void specifier_map(jr *r, im_map *m, int scope, const char *doc_url,
                     ...` -- if (m->n == m->cap) { size_t nc = m->cap ? m->cap * 2 : 16; im_entry *g = (im_entry *)realloc(m->e, nc * sizeof *g)...
- `im_parse` (function) `src/import_map.c:225` `im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn resolve, void *ctx)`
- `match` (function) `src/import_map.c:272` `static int match(const im_map *m, int scope, const char *key, char *out, size_t outsz)` -- WHATWG "resolve an imports match" within one specifier map (scope).
- `im_resolve` (function) `src/import_map.c:301` `int im_resolve(const im_map *m, const char *base, const char *specifier,
               im_url_fn...`
- `im_count` (function) `src/import_map.c:339` `size_t im_count(const im_map *m)`
- `im_free` (function) `src/import_map.c:343` `void im_free(im_map *m)`


Next: [API_p7.md](API_p7.md)
