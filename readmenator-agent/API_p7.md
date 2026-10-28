# API (page 7 of 12)
Previous: [API_p6.md](API_p6.md)

## src/css_index.c
Depends on: `include/css_index.h`
- `key_of` (function) `src/css_index.c:11` `static uint64_t key_of(int kind, const char *s, size_t n, int lower)` -- FNV-1a over the kind byte then the name; the tag is hashed lowercased because * compound_matches compares it with...
- `key_of_token` (function) `src/css_index.c:26` `static uint64_t key_of_token(int kind, const char *tok)` -- An element token in the canonical form csel_ident_eq compares against: as-is * when it fits CSS_TOK_MAX, folded...
- `entry_cmp` (function) `src/css_index.c:34` `static int entry_cmp(const void *a, const void *b)`
- `cix_free` (function) `src/css_index.c:40` `void cix_free(cix_index *idx)`
- `build` (function) `src/css_index.c:47` `static void build(const css_sel *arr, css_sel *const *ptrs, size_t n, cix_index *idx)`
- `lower_bound` (function) `src/css_index.c:86` `static size_t lower_bound(const cix_index *idx, uint64_t k)` -- keyed[nk].key = k; keyed[nk].sel = (uint32_t)i; ++nk; } qsort(keyed, nk, sizeof *keyed, entry_cmp); idx->keyed =...
- `run_head` (function) `src/css_index.c:104` `static uint32_t run_head(const cix_run *r)`
- `add_bucket` (function) `src/css_index.c:106` `static void add_bucket(const cix_index *idx, uint64_t k, cix_run *runs, size_t *nr)`
- `push` (function) `src/css_index.c:114` `static int push(uint32_t **buf, size_t *cap, size_t *n, uint32_t v)`
- `cix_candidates` (function) `src/css_index.c:129` `size_t cix_candidates(const cix_index *idx, const css_element *el,
                      uint32_t...` -- Candidates in ascending selector order without duplicates: a k-way merge of the (already * sorted) universal list...
- `cix_build` (function) `src/css_index.c:166` `void cix_build(const css_sel *sels, size_t n, cix_index *idx)`
- `cix_build_ptrs` (function) `src/css_index.c:168` `void cix_build_ptrs(css_sel *const *sels, size_t n, cix_index *idx)`

## src/css_length.c
Depends on: `include/css.h`, `include/css_length.h`
- `know` (function) `src/css_length.c:7` `* this module cannot know (real font metrics, the viewport) arrives through
 * cl_ctx rather than...`
- `cl_unit_eq` (function) `src/css_length.c:30` `static int cl_unit_eq(const char *unit, size_t len, const char *lit)` -- ASCII case-insensitive compare of a possibly-unterminated unit slice against a lowercase literal.
- `cl_font_size` (function) `src/css_length.c:56` `static double cl_font_size(const cl_ctx *ctx)` -- The element's font-size, falling back to the CSS initial value when the caller left it unset.
- `cl_root_font_size` (function) `src/css_length.c:60` `static double cl_root_font_size(const cl_ctx *ctx)`
- `cl_metric_or` (function) `src/css_length.c:67` `static double cl_metric_or(double measured, double ratio, const cl_ctx *ctx)` -- A font metric, or the fallback the spec itself names for when that metric is unavailable -- expressed as a ratio of...
- `cl_viewport_scale` (function) `src/css_length.c:80` `static int cl_viewport_scale(const char *u, size_t len, const cl_ctx *ctx, double *per)` -- Viewport-relative units (section 6.2).
- `cl_ctx_initial` (function) `src/css_length.c:100` `cl_ctx cl_ctx_initial(void)`
- `cl_unit_scale` (function) `src/css_length.c:117` `cl_status cl_unit_scale(const char *unit, size_t unit_len,
                        const cl_ctx *...`
- `cl_is_length_unit` (function) `src/css_length.c:167` `int cl_is_length_unit(const char *unit, size_t unit_len)`
- `cl_unit_is_font_relative` (function) `src/css_length.c:174` `int cl_unit_is_font_relative(const char *unit, size_t unit_len)`
- `cl_em_refit` (function) `src/css_length.c:219` `double cl_em_refit(double px, double em, double from_font_size, double font_size)`
- `cl_parse_number` (function) `src/css_length.c:233` `static int cl_parse_number(const char **pp, const char *end, double *out)` -- Parses a CSS <number> (CSS Syntax 4.3.12) without strtod -- strtod is locale-dependent, and a locale whose decimal...
- `cl_number` (function) `src/css_length.c:292` `int cl_number(const char *s, double *out, const char **endp)`
- `cl_resolve_core` (function) `src/css_length.c:309` `static cl_status cl_resolve_core(const char *value, const cl_ctx *ctx, cl_lp *out)` -- The shared core of cl_resolve and cl_resolve_lp: tokenize <number><unit> and resolve it into the two components of a...
- `cl_resolve` (function) `src/css_length.c:377` `cl_status cl_resolve(const char *value, const cl_ctx *ctx, double *out_px)`
- `cl_resolve_lp` (function) `src/css_length.c:391` `cl_status cl_resolve_lp(const char *value, const cl_ctx *ctx, cl_lp *out)`
- `cl_lp_used` (function) `src/css_length.c:395` `double cl_lp_used(cl_lp lp, double basis)`

## src/css_mask.c
Depends on: `include/css_gradient.h`, `include/css_mask.h`
- `ieq` (function) `src/css_mask.c:11` `static int ieq(const char *a, const char *b)`
- `cm_is_mask_prop` (function) `src/css_mask.c:17` `int cm_is_mask_prop(const char *prop)`
- `cm_encode_layer` (function) `src/css_mask.c:24` `void cm_encode_layer(const cm_layer *l, int *meta, int *alphas, int *poss)`
- `cm_decode_layer` (function) `src/css_mask.c:45` `void cm_decode_layer(int meta, int alphas, int poss, cm_layer *out)`
- `split` (function) `src/css_mask.c:63` `static int split(const char *s, int comma, char (*out)[CM_TOK_MAX], int max)` -- out->kind = 1; out->nst = (meta >> 4) & 0xf; if (out->nst < 2) out->nst = 2; if (out->nst > 4) out->nst = 4...
- `composite_word` (function) `src/css_mask.c:90` `static int composite_word(const char *t, int webkit)`
- `clip_word` (function) `src/css_mask.c:104` `static int clip_word(const char *t)`
- `image_layer` (function) `src/css_mask.c:112` `static int image_layer(const char *tok, cm_layer *l)` -- if (ieq(t, "source-in")) return CM_COMP_INTERSECT; if (ieq(t, "xor")) return CM_COMP_EXCLUDE; } return -1; } static...
- `emit_layers` (function) `src/css_mask.c:130` `static int emit_layers(css_decl *dst, int cap, int shorthand, const char *val)`
- `cm_expand` (function) `src/css_mask.c:197` `int cm_expand(const char *prop, const char *val, css_decl *dst, int cap, int webkit_vocab)`

## src/css_mq.c
Depends on: `include/css_length.h`, `include/css_mq.h`
- `lower_ch` (function) `src/css_mq.c:31` `static char lower_ch(char c)`
- `is_space` (function) `src/css_mq.c:35` `static int is_space(char c)`
- `is_ident_ch` (function) `src/css_mq.c:39` `static int is_ident_ch(char c)`
- `skip_ws` (function) `src/css_mq.c:44` `static void skip_ws(mq_cur *c)`
- `read_word` (function) `src/css_mq.c:49` `static int read_word(mq_cur *c, char *w, size_t cap)` -- static int is_space(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'; } static int...
- `peek_word` (function) `src/css_mq.c:61` `static int peek_word(const mq_cur *c, char *w, size_t cap)` -- /* Reads one identifier at the cursor (lowercased into w); 0 if none. static int read_word(mq_cur *c, char *w...
- `and3` (function) `src/css_mq.c:66` `static int and3(int a, int b)`
- `or3` (function) `src/css_mq.c:72` `static int or3(int a, int b)`
- `not3` (function) `src/css_mq.c:78` `static int not3(int a)`
- `copy_trim_lower` (function) `src/css_mq.c:83` `static int copy_trim_lower(const char *s, size_t a, size_t b, char *dst, size_t cap)` -- return MQ_TRUE; } static int or3(int a, int b) { if (a == MQ_TRUE || b == MQ_TRUE) return MQ_TRUE; if (a ==...
- `feature_of` (function) `src/css_mq.c:106` `static fval feature_of(const char *name, const cmq_env *env)` -- /* --- feature values --- typedef enum { FV_NONE, FV_NUM, FV_KW } fv_kind; typedef struct fval { fv_kind     kind...
- `read_num` (function) `src/css_mq.c:162` `static int read_num(const char *t, double *out, const char **end)` -- } else if (strcmp(name, "update") == 0) { v.kind = FV_KW; v.kw = "fast"; } else if (strcmp(name, "overflow-block")...
- `parse_value` (function) `src/css_mq.c:167` `static int parse_value(const char *t, int unit, double *out)` -- || strcmp(name, "video-dynamic-range") == 0) { v.kind = FV_KW; v.kw = "standard"; } else if (strcmp(name, "scan") ==...
- `cmp_op` (function) `src/css_mq.c:206` `static int cmp_op(double lhs, int op, double rhs)` -- if (strcmp(e, "dpcm") == 0) { out = n * CMQ_CM_PER_IN / CMQ_DPI_PER_DPPX; return 1; } return 0; } if (*e != '\0')...
- `flip_op` (function) `src/css_mq.c:218` `static int flip_op(int op)` -- /* op: '<' '<=' '>' '>=' '=' encoded as 1..5.
- `bool_ctx` (function) `src/css_mq.c:229` `static int bool_ctx(const fval *v)` -- } /* Flips an operator so that `v op name` reads `name op' v`. static int flip_op(int op) { switch (op) { case 1...
- `eval_plain` (function) `src/css_mq.c:237` `static int eval_plain(const char *name, const char *value, const cmq_env *env)` -- case 4: return 2; default: return op; } } /* Boolean context (MQ4 2.4.2): true unless the value is 0 or `none`....
- `read_op` (function) `src/css_mq.c:266` `static int read_op(const char **p)` -- fval f = feature_of(base, env); if (f.kind == FV_NONE) return MQ_UNKNOWN; if (f.kind == FV_KW) { if (range != 0)...
- `eval_range` (function) `src/css_mq.c:280` `static int eval_range(const char *t, const cmq_env *env)` -- static int read_op(const char **p) { const char *q = *p; int op = 0; if (q[0] == '<' && q[1] == '=') { op = 2; q +=...
- `eval_feature` (function) `src/css_mq.c:328` `static int eval_feature(const char *s, size_t a, size_t b, const cmq_env *env)` -- } /* v1 op name op v2: both operators point the same way (MQ4 grammar). int lt = (ops[0] == 1 || ops[0] == 2) &&...
- `eval_in_parens` (function) `src/css_mq.c:353` `static int eval_in_parens(mq_cur *c, int depth)` -- if (name[0] == '\0' || value[0] == '\0') return MQ_UNKNOWN; return eval_plain(name, value, env); } if (strpbrk(t...
- `eval_cond` (function) `src/css_mq.c:380` `static int eval_cond(mq_cur *c, int depth)` -- mq_cur in = { c->s, open + 1, close, c->env }; skip_ws(&in); char w[16]; int nested = (in.i < in.b && in.s[in.i] ==...
- `eval_query` (function) `src/css_mq.c:404` `static int eval_query(const char *s, size_t a, size_t b, const cmq_env *env)` -- skip_ws(c); if (c->i >= c->b) break; mq_cur save = *c; if (!read_word(c, w, sizeof w)) { *c = save; break; } int m =...
- `cmq_matches` (function) `src/css_mq.c:458` `int cmq_matches(const char *s, size_t len, const cmq_env *env)`

## src/css_select.c
Depends on: `include/css_select.h`
- `csel_hex_val` (function) `src/css_select.c:25` `int csel_hex_val(char c)` -- CSS Syntax 4.3.7 escape consumption (moved from css.c; shared by quoted content values and selector identifiers).
- `csel_emit_utf8` (function) `src/css_select.c:32` `size_t csel_emit_utf8(unsigned int cp, char *out)`
- `csel_unescape` (function) `src/css_select.c:54` `void csel_unescape(char *dst, size_t cap, const char *src, size_t n)`
- `csel_escape_len` (function) `src/css_select.c:93` `size_t csel_escape_len(const char *s, size_t i, size_t b)`
- `csel_decl_end` (function) `src/css_select.c:106` `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace)`
- `ident_hash` (function) `src/css_select.c:123` `static unsigned long long ident_hash(const char *s, size_t n)` -- 64-bit FNV-1a of the whole identifier: what makes a folded long name exact up to * a hash collision -- and a...
- `csel_ident_fold` (function) `src/css_select.c:129` `void csel_ident_fold(const char *src, size_t len, char *dst)`
- `csel_ident_eq` (function) `src/css_select.c:144` `int csel_ident_eq(const char *stored, const char *tok, size_t tlen)`
- `csel_read_ident` (function) `src/css_select.c:152` `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower)`
- `parse_attr_sel` (function) `src/css_select.c:186` `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)` -- Parses one attribute selector starting at s[*ip] == '[' (within s[.,b)) into *am.
- `parse_nth_arg` (function) `src/css_select.c:243` `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)` -- Parses the An+B argument of the nth-child family, s[a,b) (surrounding space trimmed here).
- `take_sub_arg` (function) `src/css_select.c:295` `static int take_sub_arg(const char *s, size_t a, size_t b, css_sel *sel, int strict);`
- `between` (function) `src/css_select.c:384` `* between ( and ) is split on commas (not inside [] or ());`
- `simple_pseudo_kind` (function) `src/css_select.c:439` `static int simple_pseudo_kind(const char *nm)` -- The PSEUDO_* kind of an argument-less pseudo-class usable inside a * sub-selector, or -1.
- `parse_sub_compound` (function) `src/css_select.c:460` `static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub)` -- Parses one SIMPLE sub-selector span s[a,b) for :not()/:is()/:where(): only tag name, .class, #id, or [attr] (no...
- `parse_compound` (function) `src/css_select.c:525` `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,
                  ...` -- Parses one COMPOUND selector span s[a,b) (no combinators, no surrounding space) into *cp. sel holds the sub-selector...
- `selector` (function) `src/css_select.c:567` `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is
 * dropped. Whitespa...`
- `csel_element_feature_bits` (function) `src/css_select.c:587` `unsigned long long csel_element_feature_bits(const css_element *e)`
- `compute_anc_req` (function) `src/css_select.c:602` `static unsigned long long compute_anc_req(const css_sel *sel)` -- What the ancestors of the subject must contain: walk left from the subject while the combinator is descendant or...
- `csel_parse_core` (function) `src/css_select.c:615` `static int csel_parse_core(const char *s, size_t a, size_t b, css_sel *sel)`
- `seven` (function) `src/css_select.c:621` `* pay for the other seven (a css_sel is ~12.8 KiB). */ memset(sel, 0, offsetof(css_sel, parts));`
- `compound_req` (function) `src/css_select.c:709` `static unsigned long long compound_req(const css_compound *c)` -- } else { psel += 10; } } spec += 100 * (sel->parts[k].has_id ?
- `compute_subj_req` (function) `src/css_select.c:718` `static unsigned long long compute_subj_req(const css_sel *sel)`
- `csel_compact_size` (function) `src/css_select.c:729` `size_t csel_compact_size(int nparts)`
- `csel_compact_dup` (function) `src/css_select.c:735` `css_sel *csel_compact_dup(const css_sel *sel)`
- `csel_parse` (function) `src/css_select.c:744` `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel)`
- `el_attr_value` (function) `src/css_select.c:755` `static const char *el_attr_value(const css_element *el, const char *name)` -- The value of element attribute `name` (case-insensitive name), or NULL if absent. * A present attribute with no...
- `ends_with` (function) `src/css_select.c:765` `static int ends_with(const char *v, const char *suf, int ci)` -- The value of element attribute `name` (case-insensitive name), or NULL if absent. * A present attribute with no...
- `has_word` (function) `src/css_select.c:773` `static int has_word(const char *v, const char *w, int ci)` -- True if `v` is a whitespace-separated list containing the word `w` (non-empty), * case-folded when ci (the `~=`...
- `attr_matches` (function) `src/css_select.c:788` `static int attr_matches(const css_attr_match *am, const css_element *el)` -- size_t wl = strlen(w); if (wl == 0) return 0; const char *p = v; while (*p != '\0') { while (*p == ' ' || *p == '\t'...
- `nth_matches` (function) `src/css_select.c:808` `static int nth_matches(int A, int B, int idx)` -- True if the 1-based index idx satisfies idx = A*m + B for some integer m >= 0. * idx <= 0 means "unknown sibling...
- `is_form_control` (function) `src/css_select.c:817` `static int is_form_control(const char *tag)` -- True if the 1-based index idx satisfies idx = A*m + B for some integer m >= 0. * idx <= 0 means "unknown sibling...
- `pseudo_matches` (function) `src/css_select.c:826` `static int pseudo_matches(const css_pseudo_match *pm, const css_element *el, const css_sel *sel, const char...` -- if (A > 0) return d >= 0 && d % A == 0; return d <= 0 && (-d) % (long)(-A) == 0; } /* Form controls for :enabled...
- `sub_sel_matches` (function) `src/css_select.c:830` `static int sub_sel_matches(const css_sub_sel *sub, const css_element *el)`
- `compound_matches` (function) `src/css_select.c:1080` `static int compound_matches(const css_compound *c, const css_element *el,
                       ...` -- True if one compound matches one element (no ancestor context).
- `built` (function) `src/css_select.c:1115` `* chains the caller built (an element without parent/prev links never matches
 * through that com...`
- `pseudo_is_local` (function) `src/css_select.c:1160` `static int pseudo_is_local(int kind)` -- case COMB_ADJACENT: return (el->prev != NULL) && complex_matches(sel, k - 1, el->prev, target_id, allow_pseudo_el...
- `csel_needs_structure` (function) `src/css_select.c:1173` `int csel_needs_structure(const css_sel *sel)`
- `csel_matches` (function) `src/css_select.c:1196` `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,
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
- `ct_interp_direction` (function) `src/css_text.c:236` `int ct_interp_direction(const char *v)` -- Both halves share ONE scale, so the ratio keeps its shape: clamping each half to * CSS_LEN_MAX on its own turned...
- `ct_liststyle_kw` (function) `src/css_text.c:242` `static int ct_liststyle_kw(const char *t)`
- `ct_liststyle_unknown_name` (function) `src/css_text.c:263` `static int ct_liststyle_unknown_name(const char *t)` -- A <counter-style> name this engine has no glyph set for.
- `ct_interp_liststyle` (function) `src/css_text.c:274` `int ct_interp_liststyle(const char *v)` -- list-style-type, or the type token of the list-style shorthand: the first * recognised keyword wins. url() (a...
- `ct_emit_spacing` (function) `src/css_text.c:309` `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
- `ct_expand_shadow` (function) `src/css_text.c:322` `int ct_expand_shadow(const char *val, css_decl *dst, int cap)` -- text-shadow (single layer): collects up to three lengths (dx, dy, blur — blur is ignored) and an optional color, in...

## src/css_values.c
Depends on: `include/css.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`
- `cv_parse_num` (function) `src/css_values.c:11` `static int cv_parse_num(const char *s, double *out, const char **endp)`
- `cv_parse_color` (function) `src/css_values.c:16` `int cv_parse_color(const char *v)`
- `cv_interp_color` (function) `src/css_values.c:36` `int cv_interp_color(const char *v)`
- `cv_color_ok` (function) `src/css_values.c:41` `int cv_color_ok(int c)`
- `cv_bg_alpha_of` (function) `src/css_values.c:46` `int cv_bg_alpha_of(const char *v)`
- `cv_interp_bg` (function) `src/css_values.c:160` `int cv_interp_bg(const char *v)`
- `cv_parse_color_t7` (function) `src/css_values.c:205` `int cv_parse_color_t7(const char *v)`
- `cv_text_color` (function) `src/css_values.c:222` `int cv_text_color(const char *v)`
- `cv_filter_scale` (function) `src/css_values.c:231` `double cv_filter_scale(int pct)`

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
- `node_in_document` (function) `src/dom.c:352` `static int node_in_document(const lxb_dom_node_t *node)` -- 1 when `node` is in the document tree (its topmost ancestor is the document node).
- `dom_get_element_by_id` (function) `src/dom.c:358` `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)`
- `dom_get_connected_by_id` (function) `src/dom.c:364` `dom_node_id dom_get_connected_by_id(const dom_index *idx, const char *id)`
- `copy_ids` (function) `src/dom.c:387` `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)`
- `dom_get_by_tag` (function) `src/dom.c:394` `size_t dom_get_by_tag(const dom_index *idx, const char *tag,
                      dom_node_id *o...`
- `dom_get_by_class` (function) `src/dom.c:403` `size_t dom_get_by_class(const dom_index *idx, const char *cls,
                        dom_node_i...`
- `id_of` (function) `src/dom.c:416` `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)` -- Max complex selectors in one comma-separated list.
- `parse_selector_list` (function) `src/dom.c:426` `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)` -- Parses a selector list "a, b, c" into up to cap css_sel.
- `node_matches_any` (function) `src/dom.c:459` `static int node_matches_any(const lxb_dom_node_t *cn,
                            const css_sel *...` -- s.order = (int)n; s.rule = 0; out[n++] = s; } } start = i + 1; } break; default: break; } } return n; } /* Nonzero...
- `count` (function) `src/dom.c:467` `* count (may exceed cap), and returns DOM_NODE_NONE. */
static dom_node_id qs_walk(const dom_inde...`
- `dom_query_selector` (function) `src/dom.c:497` `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,
                          ...`
- `dom_query_selector_all` (function) `src/dom.c:506` `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,
                           ...`
- `dom_matches` (function) `src/dom.c:517` `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)`
- `dom_closest` (function) `src/dom.c:526` `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,
                        const cha...`
- `dom_document_position` (function) `src/dom.c:542` `size_t dom_document_position(const dom_index *idx, dom_node_id node)`
- `dom_precedes` (function) `src/dom.c:547` `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)`
- `dom_node_at` (function) `src/dom.c:552` `dom_node_id dom_node_at(const dom_index *idx, size_t position)`
- `dom_parent` (function) `src/dom.c:557` `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)`
- `dom_first_child` (function) `src/dom.c:567` `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)`
- `dom_next_sibling` (function) `src/dom.c:575` `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)`
- `dom_tag_name` (function) `src/dom.c:583` `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)`
- `dom_get_attribute` (function) `src/dom.c:594` `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,
                           ...`
- `dom_attribute_names` (function) `src/dom.c:616` `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,
                           con...`
- `dom_text_content` (function) `src/dom.c:634` `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)`
- `dom_document_title` (function) `src/dom.c:644` `const char *dom_document_title(const dom_index *idx, size_t *len)`
- `dom_set_text_content` (function) `src/dom.c:657` `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,
                               ...`
- `dom_set_document_title` (function) `src/dom.c:691` `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)`
- `idx_push` (function) `src/dom.c:702` `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)` -- return DOM_OK; } dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len) { if (idx == NULL...
- `dom_create_element` (function) `src/dom.c:720` `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)`
- `dom_append_child` (function) `src/dom.c:740` `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
- `dom_remove_child` (function) `src/dom.c:754` `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
- `dom_set_attribute` (function) `src/dom.c:762` `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,
                             const...`
- `dom_remove_attribute` (function) `src/dom.c:791` `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)`
- `index_subtree` (function) `src/dom.c:800` `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)` -- } } return DOM_OK; } dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name) { if...
- `dom_set_inner_html` (function) `src/dom.c:810` `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,
                              con...`
- `ih_append` (function) `src/dom.c:863` `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)`
- `ih_free` (function) `src/dom.c:890` `static void ih_free(ih_acc *a)`
- `dom_get_inner_html` (function) `src/dom.c:917` `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,
                           ...`
- `dom_insert_before` (function) `src/dom.c:947` `dom_status dom_insert_before(dom_index *idx, dom_node_id parent, dom_node_id child,
             ...`
- `dom_clone_node` (function) `src/dom.c:964` `dom_status dom_clone_node(dom_index *idx, dom_node_id node, int deep, dom_node_id *out_id)`
- `dom_move_children` (function) `src/dom.c:978` `dom_status dom_move_children(dom_index *idx, dom_node_id src, dom_node_id parent,
               ...`
- `char_kind` (function) `src/dom.c:1011` `static int char_kind(const lxb_dom_node_t *n)`
- `handle_of` (function) `src/dom.c:1022` `static dom_node_id handle_of(dom_index *idx, lxb_dom_node_t *n)` -- /* --- text and comment nodes (spec/dom.md 9) --- static int char_kind(const lxb_dom_node_t *n) { switch (n->type) {...
- `dom_node_kind` (function) `src/dom.c:1030` `int dom_node_kind(const dom_index *idx, dom_node_id node)`
- `dom_child_node` (function) `src/dom.c:1034` `dom_node_id dom_child_node(dom_index *idx, dom_node_id node, int last)`
- `dom_sibling_node` (function) `src/dom.c:1041` `dom_node_id dom_sibling_node(dom_index *idx, dom_node_id node, int prev)`
- `dom_create_char_node` (function) `src/dom.c:1048` `dom_status dom_create_char_node(dom_index *idx, int kind, const char *text, size_t len,
         ...`
- `dom_native_node` (function) `src/dom.c:1062` `const void *dom_native_node(const dom_index *idx, dom_node_id node)`

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
- `dd_overflow_name` (function) `src/dom_debug.c:157` `static const char *dd_overflow_name(int o)`
- `dd_cursor_name` (function) `src/dom_debug.c:166` `static const char *dd_cursor_name(int c)`
- `dd_text_overflow_name` (function) `src/dom_debug.c:199` `static const char *dd_text_overflow_name(int t)`
- `dd_inset` (function) `src/dom_debug.c:204` `static int dd_inset(int v)` -- case CSS_CUR_PROGRESS:    return "progress"; case CSS_CUR_NO_DROP:     return "no-drop"; case CSS_CUR_VERTICAL_TEXT...
- `dd_object_fit_name` (function) `src/dom_debug.c:208` `static const char *dd_object_fit_name(int o)`
- `dd_image_rendering_name` (function) `src/dom_debug.c:219` `static const char *dd_image_rendering_name(int r)`
- `dd_border_style_name` (function) `src/dom_debug.c:228` `static const char *dd_border_style_name(int s)`
- `dd_box_line` (function) `src/dom_debug.c:261` `static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b)`
- `dd_block_line` (function) `src/dom_debug.c:323` `static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b)`
- `dd_format` (function) `src/dom_debug.c:399` `size_t dd_format(const rd_doc *doc, char *out, size_t cap)`
- `dd_format_css` (function) `src/dom_debug.c:431` `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)` -- } dd_puts(&c, "[blocks]\n"); for (size_t i = 0; i < nblocks; ++i) { const rd_block *b = rd_at(doc, i); if (b !=...

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

## src/fb_cmdline.c
Depends on: `include/fb_cmdline.h`, `include/fb_panes.h`, `include/freebug.h`
- `dup_n` (function) `src/fb_cmdline.c:10` `static char *dup_n(const char *s, size_t n)`
- `fbc_history_init` (function) `src/fb_cmdline.c:19` `void fbc_history_init(fbc_history *h)`
- `fbc_history_free` (function) `src/fb_cmdline.c:23` `void fbc_history_free(fbc_history *h)`
- `fbc_history_push` (function) `src/fb_cmdline.c:32` `int fbc_history_push(fbc_history *h, const char *text, size_t len)`
- `fbc_history_prev` (function) `src/fb_cmdline.c:53` `const char *fbc_history_prev(fbc_history *h, const char *cur, size_t curlen)`
- `fbc_history_next` (function) `src/fb_cmdline.c:63` `const char *fbc_history_next(fbc_history *h)`
- `path_char` (function) `src/fb_cmdline.c:70` `static int path_char(char c)`
- `fbc_complete_split` (function) `src/fb_cmdline.c:74` `long fbc_complete_split(const char *text, size_t n, char *base, size_t cap, size_t *prefix_off)`
- `fbc_names_expr` (function) `src/fb_cmdline.c:95` `size_t fbc_names_expr(const char *base, char *out, size_t cap)`
- `fbc_complete_pick` (function) `src/fb_cmdline.c:118` `size_t fbc_complete_pick(const char *names, const char *prefix, size_t plen,
                    ...`
- `fbc_filter_passes` (function) `src/fb_cmdline.c:159` `int fbc_filter_passes(int filter, int level)`
- `fbc_filter_next` (function) `src/fb_cmdline.c:168` `int fbc_filter_next(int filter)`
- `fbc_filter_label` (function) `src/fb_cmdline.c:173` `const char *fbc_filter_label(int filter)`

## src/fb_panes.c
Depends on: `include/fb_panes.h`
- `tab_ok` (function) `src/fb_panes.c:110` `static int tab_ok(int tab)`
- `fbp_tab_label` (function) `src/fb_panes.c:112` `const char *fbp_tab_label(int tab)`
- `ieq` (function) `src/fb_panes.c:114` `static int ieq(const char *a, const char *b)`
- `fbp_tab_from_name` (function) `src/fb_panes.c:123` `int fbp_tab_from_name(const char *name)`
- `fbp_tab_wrap` (function) `src/fb_panes.c:130` `int fbp_tab_wrap(int tab, int dir)`
- `fbp_tab_span` (function) `src/fb_panes.c:136` `void fbp_tab_span(int tab, double cell_w, double pad_cells, double *x, double *w)`
- `fbp_tab_at` (function) `src/fb_panes.c:145` `int fbp_tab_at(double px, double cell_w, double pad_cells)`
- `fbp_is_pane` (function) `src/fb_panes.c:155` `int fbp_is_pane(int tab)`
- `fbp_js_quote` (function) `src/fb_panes.c:157` `size_t fbp_js_quote(const char *s, size_t n, char *out, size_t cap)`
- `fbp_expr` (function) `src/fb_panes.c:186` `size_t fbp_expr(int tab, const char *sel, size_t n, char *out, size_t cap)`

## src/flex_layout.c
Depends on: `include/flex_layout.h`
- `nn` (function) `src/flex_layout.c:19` `static double nn(double v)` -- bounded by FX_MAX_ITEMS (no VLAs).
- `fx_flex_line` (function) `src/flex_layout.c:23` `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                ...`
- `fx_grid_columns` (function) `src/flex_layout.c:128` `fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          doubl...`
- `fx_autofill_count` (function) `src/flex_layout.c:133` `size_t fx_autofill_count(double avail, double gap, double minw)`
- `fx_grid_columns_weighted` (function) `src/flex_layout.c:143` `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                      ...`
- `fx_grid_place_span` (function) `src/flex_layout.c:177` `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                      ...`
- `fx_grid_area_hash` (function) `src/flex_layout.c:319` `unsigned fx_grid_area_hash(const char *name)`
- `area_token_is_null_cell` (function) `src/flex_layout.c:343` `static int area_token_is_null_cell(const char *tok, size_t len)` -- 0 is reserved for "no name" (the null cell token), so a name that hashes to * it is nudged; the alternative is a...
- `fx_grid_areas_parse` (function) `src/flex_layout.c:349` `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)`
- `fx_grid_area_rect` (function) `src/flex_layout.c:424` `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,
                            int ...`
- `float_pack_impl` (function) `src/flex_layout.c:466` `static fx_status float_pack_impl(const double *width, const int *side, size_t n,
                ...` -- Shared packer: wrap == 0 is the single-row v1 contract (overflow clamps in place); wrap != 0 starts a new row...
- `fx_float_insets` (function) `src/flex_layout.c:506` `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,
                 ...`
- `fx_float_pack` (function) `src/flex_layout.c:546` `fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        d...`
- `fx_float_pack_wrap` (function) `src/flex_layout.c:551` `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,
                    ...`
- `fx_grid_cell` (function) `src/flex_layout.c:593` `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)`
- `fx_auto_margins` (function) `src/flex_layout.c:605` `fx_status fx_auto_margins(fx_result *res, size_t n, const unsigned char *auto_l,
                ...` -- } void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col) { if (row == NULL || col == NULL) return...
- `fx_auto_min_size` (function) `src/flex_layout.c:628` `double fx_auto_min_size(double min_content, double basis, double author_min,
                    ...`
- `fx_multicol_used` (function) `src/flex_layout.c:645` `fx_status fx_multicol_used(double avail_w, int column_count, double column_width,
               ...`
- `fx_multicol_balance` (function) `src/flex_layout.c:682` `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,
                        ...`
- `fx_justify_name` (function) `src/flex_layout.c:713` `const char *fx_justify_name(fx_justify j)`
- `fx_column_place` (function) `src/flex_layout.c:725` `fx_status fx_column_place(const double *h, const double *grow, size_t n, double gap,
            ...`
- `fx_column_place_m` (function) `src/flex_layout.c:732` `fx_status fx_column_place_m(const double *h, const double *grow, const int *mauto,
              ...`
- `fx_cross_offset` (function) `src/flex_layout.c:793` `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r)`
- `gl_ws` (function) `src/flex_layout.c:805` `static int gl_ws(char c)` -- } double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r) { double room = avail - w; if...
- `gl_lower` (function) `src/flex_layout.c:809` `static int gl_lower(char c)`
- `gl_kw` (function) `src/flex_layout.c:812` `static int gl_kw(const char *p, const char *end, const char *kw)` -- if (mauto_r) return 0.0; if (align == 1) return room / 2.0; if (align == 2) return room; return 0.0; } /* ASCII...
- `gl_int` (function) `src/flex_layout.c:822` `static int gl_int(const char *p, const char *end, long cap, long *out)` -- A CSS <integer> (optional sign, digits only) filling exactly [p, end).
- `gl_side_range` (function) `src/flex_layout.c:837` `static int gl_side_range(const char *p, const char *end, int *out)` -- int neg = 0; if (p < end && (*p == '+' || *p == '-')) { neg = (*p == '-'); ++p; } if (p >= end) return 0; long v =...
- `fx_grid_line_side` (function) `src/flex_layout.c:860` `int fx_grid_line_side(const char *s, int *out)`
- `fx_grid_line_parse` (function) `src/flex_layout.c:868` `int fx_grid_line_parse(const char *v, int *start, int *end)`
- `gl_is_span` (function) `src/flex_layout.c:885` `static int gl_is_span(int v)`
- `gl_is_line` (function) `src/flex_layout.c:886` `static int gl_is_line(int v)`
- `fx_grid_line_resolve` (function) `src/flex_layout.c:888` `void fx_grid_line_resolve(int start, int end, int ntracks, int *pos0, int *span)`
- `fx_col_free_split` (function) `src/flex_layout.c:930` `fx_status fx_col_free_split(double free_px, const int *grow, const int *mauto, size_t n,
        ...`

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

## src/frame_broker.c
Depends on: `include/frame_broker.h`
- `lc` (function) `src/frame_broker.c:9` `static char lc(char c)`
- `host_char_ok` (function) `src/frame_broker.c:11` `static int host_char_ok(char c)`
- `fbk_origin_of` (function) `src/frame_broker.c:15` `int fbk_origin_of(const char *url, char *out, size_t cap)`
- `fbk_init` (function) `src/frame_broker.c:53` `int fbk_init(fbk_table *t, const char *top_url)`
- `live` (function) `src/frame_broker.c:62` `static int live(const fbk_table *t, int id)`
- `fbk_add` (function) `src/frame_broker.c:66` `int fbk_add(fbk_table *t, int parent, const char *url, int *out_id)`
- `fbk_remove` (function) `src/frame_broker.c:84` `void fbk_remove(fbk_table *t, int id)`
- `fbk_origin` (function) `src/frame_broker.c:96` `const char *fbk_origin(const fbk_table *t, int id)`
- `target_admits` (function) `src/frame_broker.c:101` `static int target_admits(const char *target, const char *snd, const char *recv)` -- int changed = 1;                                  /* fixpoint: slots are reused, order is not a tree order while...
- `fbk_route` (function) `src/frame_broker.c:118` `fbk_verdict fbk_route(const fbk_table *t, int from, fbk_rel rel, int child,
                     ...`

## src/frame_clock.c
Depends on: `include/frame_clock.h`
- `fc_set_active` (function) `src/frame_clock.c:16` `void fc_set_active(fc_clock *c, int active)`
- `fc_needs_tick` (function) `src/frame_clock.c:21` `int fc_needs_tick(const fc_clock *c)`
- `fc_interval_ms` (function) `src/frame_clock.c:26` `int fc_interval_ms(const fc_clock *c)`

## src/frame_host.c
Depends on: `include/frame_broker.h`, `include/frame_host.h`
- `fh_new` (function) `src/frame_host.c:35` `fh_host *fh_new(const char *top_url, tab_fetch_fn fetch, void *fetch_ctx,
                fh_top_...`
- `slot_release_view` (function) `src/frame_host.c:47` `static void slot_release_view(fh_slot *sl)`
- `reap` (function) `src/frame_host.c:55` `static void reap(fh_host *h)` -- h->fetch = fetch; h->fetch_ctx = fetch_ctx; h->top_msg = top_msg; h->top_ctx = top_ctx; for (int i = 0; i <...
- `fh_free` (function) `src/frame_host.c:67` `void fh_free(fh_host *h)`
- `fh_count` (function) `src/frame_host.c:76` `int fh_count(const fh_host *h)`
- `load_frame` (function) `src/frame_host.c:85` `static void load_frame(fh_host *h, int id, const char *url)` -- Loads the document of frame `id` (already registered in the table).
- `find_child` (function) `src/frame_host.c:129` `static int find_child(const fh_host *h, int parent, int token)`
- `token_seen_by` (function) `src/frame_host.c:137` `static int token_seen_by(const fh_host *h, int dest, int from)` -- Token a receiving frame knows `from` by: from's own token when it is a direct child, otherwise * that of the...
- `post_op` (function) `src/frame_host.c:143` `static void post_op(fh_host *h, int from, const tab_ws_op *op)`
- `apply_ops` (function) `src/frame_host.c:198` `static void apply_ops(fh_host *h, int from, const tab_ws_op *ops, size_t n)`
- `fh_apply_top` (function) `src/frame_host.c:221` `void fh_apply_top(fh_host *h, const tab_page *page)`
- `fh_tick` (function) `src/frame_host.c:226` `int fh_tick(fh_host *h, int elapsed_ms)`
- `fh_generation` (function) `src/frame_host.c:250` `unsigned fh_generation(const fh_host *h)`
- `fh_frame_view` (function) `src/frame_host.c:252` `const pv_view *fh_frame_view(const fh_host *h, const char *url, tab **t_out)`

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


Next: [API_p8.md](API_p8.md)
