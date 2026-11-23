# API (page 8 of 14)
Previous: [API_p7.md](API_p7.md)

## src/css_counter.c
Depends on: `include/css_counter.h`
- `cnt_hash` (function) `src/css_counter.c:18` `unsigned cnt_hash(const char *name, size_t len)`
- `is_ws` (function) `src/css_counter.c:27` `static int is_ws(char c)`
- `is_ident_start` (function) `src/css_counter.c:29` `static int is_ident_start(unsigned char c)`
- `is_ident_char` (function) `src/css_counter.c:32` `static int is_ident_char(unsigned char c)`
- `ci_eq` (function) `src/css_counter.c:34` `static int ci_eq(const char *a, const char *b)`
- `valid_name` (function) `src/css_counter.c:45` `static int valid_name(const char *s, size_t n)` -- A <custom-ident> usable as a counter name: identifier syntax, not a CSS-wide * keyword or `none`, and short enough...
- `cnt_parse_decls` (function) `src/css_counter.c:59` `int cnt_parse_decls(const char *val, int dflt, cnt_decl out[CNT_MAX_DECL])`
- `put` (function) `src/css_counter.c:102` `static size_t put(char *out, size_t cap, size_t o, const char *s)`
- `utf8_put` (function) `src/css_counter.c:107` `static void utf8_put(char *buf, unsigned cp)`
- `cnt_format` (function) `src/css_counter.c:120` `size_t cnt_format(int style, long value, char *out, size_t cap)`
- `style_of` (function) `src/css_counter.c:174` `static int style_of(const char *name)`
- `sk_char` (function) `src/css_counter.c:192` `static void sk_char(sink *k, char c)`
- `sk_str` (function) `src/css_counter.c:196` `static void sk_str(sink *k, const char *s)`
- `read_string` (function) `src/css_counter.c:201` `static const char *read_string(const char *p, char *dst, size_t cap)` -- A quoted string at p (p[0] is the quote).
- `split_args` (function) `src/css_counter.c:238` `static int split_args(const char *a, const char *b, char (*f)[CNT_STR_MAX], int max)` -- continue; } cp = (unsigned char)*p; } if (cp >= 0x20 && o + 1 < cap) dst[o++] = (char)cp; else if (cp >= 0x20)...
- `cnt_is_marker` (function) `src/css_counter.c:272` `int cnt_is_marker(const char *s)`
- `has_counter_fn` (function) `src/css_counter.c:276` `static int has_counter_fn(const char *v)`
- `cnt_parse_content` (function) `src/css_counter.c:286` `int cnt_parse_content(const char *val, char *out, size_t cap)`
- `cnt_state_new` (function) `src/css_counter.c:366` `cnt_state *cnt_state_new(void)`
- `cnt_state_free` (function) `src/css_counter.c:367` `void cnt_state_free(cnt_state *s)`
- `top_of` (function) `src/css_counter.c:369` `static cnt_inst *top_of(cnt_state *s, unsigned name)`
- `clampv` (function) `src/css_counter.c:375` `static int clampv(long v)`
- `cnt_reset` (function) `src/css_counter.c:379` `void cnt_reset(cnt_state *s, int depth, const cnt_decl *d, int n)`
- `cnt_increment` (function) `src/css_counter.c:392` `void cnt_increment(cnt_state *s, int depth, const cnt_decl *d, int n)`
- `cnt_leave` (function) `src/css_counter.c:407` `void cnt_leave(cnt_state *s, int depth)`
- `cnt_resolve` (function) `src/css_counter.c:412` `size_t cnt_resolve(const cnt_state *s, const char *marker, cnt_attr_fn attr, void *ctx,
         ...`

## src/css_gradient.c
Depends on: `include/css_color.h`, `include/css_decl.h`, `include/css_gradient.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`
- `cg_parse_num` (function) `src/css_gradient.c:13` `static int cg_parse_num(const char *s, double *out, const char **endp)`
- `cg_wide_keyword` (function) `src/css_gradient.c:18` `static int cg_wide_keyword(const char *v)`
- `gradient` (function) `src/css_gradient.c:28` `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,
 * the whole decl...`
- `find_gradient_call` (function) `src/css_gradient.c:77` `static int find_gradient_call(const char *v, const char *fn, size_t *start,
                     ...` -- Locates a gradient function call `fn` (e.g. "linear-gradient(") in v (case-insensitive; an occurrence that is the...
- `conic_prelude` (function) `src/css_gradient.c:111` `static int conic_prelude(const char *seg, int *angle)` -- conic-gradient prelude: `from <int>deg`, optionally followed by `at <pos>` (position accepted and ignored -- always...
- `sRGB` (function) `src/css_gradient.c:154` `* sRGB (spec/css_gradient.md §3b). */
static int strip_interp(char *seg)`
- `grad_stop_pos` (function) `src/css_gradient.c:210` `static int grad_stop_pos(const char *pp, int conic, const char **endp)` -- One stop position after a color: `N%` -> 0-1000 (x10); conic also accepts `Ndeg` -> the same 0-1000 turn fraction...
- `CSS_GRAD_STOPS_MAX` (function) `src/css_gradient.c:241` `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when
 * the gradient fai...`
- `emit_gradient` (function) `src/css_gradient.c:352` `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,
                         ...` -- Emits the gradient decl group. nstops == 0 emits only the explicit reset * (P_BG_GRAD_N = 0), which is how a...
- `find_radial_gradient` (function) `src/css_gradient.c:421` `static int find_radial_gradient(const char *v, size_t *start, size_t *end,
                      ...` -- R5c: detects radial-gradient(circle at center, color1, color2).
- `cg_first_url` (function) `src/css_gradient.c:459` `int cg_first_url(const char *val, char *out, size_t outcap)`
- `emit_radial_geom` (function) `src/css_gradient.c:466` `static int emit_radial_geom(css_decl *dst, int cap, const cg_radial *r)` -- } memcpy(urltab[*nurl], url, strlen(url) + 1); dst[0].ival = (int)*nurl; ++*nurl; return 1; } int cg_first_url(const...
- `pool` (function) `src/css_gradient.c:479` `* pool (gradient explicitly reset);`
- `downstream` (function) `src/css_gradient.c:483` `* happens downstream (render_doc.c), gated by caps.images like an <img>. */
int cg_expand_bg_imag...`
- `declaration` (function) `src/css_gradient.c:544` `* declaration (fail closed);`
- `bg_layer_tokens_ok` (function) `src/css_gradient.c:551` `static int bg_layer_tokens_ok(const char *s)` -- True iff every token of s (split on whitespace, '/' and ',') is a valid non-colour component of a background layer...
- `cg_expand_background` (function) `src/css_gradient.c:591` `int cg_expand_background(const char *val, css_decl *dst, int cap,
                             ch...`
- `rad_ieq` (function) `src/css_gradient.c:679` `static int rad_ieq(const char *a, const char *b)`
- `rad_len` (function) `src/css_gradient.c:687` `static int rad_len(const char *tok, int *enc)` -- One <length-percentage> token (`12px`, `40%`, `0`) -> the cg_radial encoding; 1 = ok.
- `rad_is_len_start` (function) `src/css_gradient.c:708` `static int rad_is_len_start(const char *t)`
- `rad_pos_kw` (function) `src/css_gradient.c:713` `static int rad_pos_kw(const char *t, int *axis)` -- if (*e == '\0' && v == 0.0) { *enc = 0; return 1; }   /* unitless 0 is a zero length if (rad_ieq(e, "px")) { if (v >...
- `rad_parse_position` (function) `src/css_gradient.c:722` `static int rad_parse_position(char (*tok)[CSS_TOK_MAX], int n, int *cx, int *cy)`
- `cg_parse_radial_prelude` (function) `src/css_gradient.c:751` `int cg_parse_radial_prelude(const char *seg, cg_radial *out)`
- `cg_radial_len_px` (function) `src/css_gradient.c:827` `double cg_radial_len_px(int enc, double dim)`
- `cg_dmin` (function) `src/css_gradient.c:836` `static double cg_dmin(double a, double b)`
- `cg_dmax` (function) `src/css_gradient.c:837` `static double cg_dmax(double a, double b)`
- `cg_radial_geometry` (function) `src/css_gradient.c:839` `void cg_radial_geometry(const cg_radial *r, double w, double h,
                        double *c...`
- `cg_parse_linear` (function) `src/css_gradient.c:876` `int cg_parse_linear(const char *fn, int *angle, int *colors, int *positions)`

## src/css_import.c
Depends on: `include/css_import.h`
- `is_ws` (function) `src/css_import.c:8` `static int is_ws(char c)`
- `lower` (function) `src/css_import.c:10` `static char lower(char c)`
- `kw_at` (function) `src/css_import.c:13` `static int kw_at(const char *s, size_t i, size_t e, const char *kw)` -- css_import -- @import prelude reader (spec/css_import.md).
- `is_ident_char` (function) `src/css_import.c:21` `static int is_ident_char(char c)`
- `skip_ws` (function) `src/css_import.c:27` `static size_t skip_ws(const char *s, size_t i, size_t e)` -- static int kw_at(const char *s, size_t i, size_t e, const char *kw) { size_t n = strlen(kw); if (e - i < n) return...
- `copy_trim` (function) `src/css_import.c:53` `static int copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` -- Past the string that opens at s[i] (a quote), or (size_t)-1 when it does not * terminate before e or a newline (a...
- `read_string` (function) `src/css_import.c:64` `static size_t read_string(const char *s, size_t a, size_t e, char *dst, size_t cap)` -- Copies the body of the string opening at s[a] (quotes stripped, escapes kept * verbatim except an escaped quote).
- `match_paren` (function) `src/css_import.c:79` `static size_t match_paren(const char *s, size_t i, size_t e)` -- size_t end = skip_string(s, a, e); if (end == (size_t)-1) return end; size_t n = 0; for (size_t j = a + 1; j + 1 <...
- `parse_prelude` (function) `src/css_import.c:97` `static int parse_prelude(const char *s, size_t a, size_t b, ci_import *im)` -- Parses one import prelude s[a, b) (after "@import", before ';') into im. * Returns 0, or -1 when the import is...
- `ci_scan` (function) `src/css_import.c:156` `size_t ci_scan(const char *css, size_t len, ci_import *out, size_t cap)`
- `ci_wrap` (function) `src/css_import.c:194` `int ci_wrap(const ci_import *im, char *open, size_t ocap, char *close, size_t ccap)`
- `ci_balanced` (function) `src/css_import.c:220` `int ci_balanced(const char *css, size_t len)`
- `is_ident_ch` (function) `src/css_import.c:243` `static int is_ident_ch(char c)`
- `has_scheme` (function) `src/css_import.c:250` `static int has_scheme(const char *r)` -- } else if (c == '}') { if (--depth < 0) return 0; } } return depth == 0; } static int is_ident_ch(char c) { unsigned...
- `url_arg` (function) `src/css_import.c:266` `static int url_arg(const char *s, size_t a, size_t e, char *ref, size_t cap, size_t *end)` -- Reads the argument of the url( whose '(' ends at s[a-1]: the raw reference into ref and the index past ')' into...
- `abs_ok` (function) `src/css_import.c:297` `static int abs_ok(const char *u)`
- `ci_rebase_urls` (function) `src/css_import.c:303` `int ci_rebase_urls(const char *css, size_t len, const char *base,
                   ci_resolve_f...`

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
- `ieq` (function) `src/css_mask.c:13` `static int ieq(const char *a, const char *b)`
- `cm_is_mask_prop` (function) `src/css_mask.c:19` `int cm_is_mask_prop(const char *prop)`
- `cm_encode_layer` (function) `src/css_mask.c:26` `void cm_encode_layer(const cm_layer *l, int *meta, int *alphas, int *poss)`
- `cm_decode_layer` (function) `src/css_mask.c:47` `void cm_decode_layer(int meta, int alphas, int poss, cm_layer *out)`
- `split` (function) `src/css_mask.c:65` `static int split(const char *s, int comma, char (*out)[CM_TOK_MAX], int max)` -- out->kind = 1; out->nst = (meta >> 4) & 0xf; if (out->nst < 2) out->nst = 2; if (out->nst > 4) out->nst = 4...
- `composite_word` (function) `src/css_mask.c:92` `static int composite_word(const char *t, int webkit)`
- `clip_word` (function) `src/css_mask.c:106` `static int clip_word(const char *t)`
- `image_layer` (function) `src/css_mask.c:114` `static int image_layer(const char *tok, cm_layer *l)` -- if (ieq(t, "source-in")) return CM_COMP_INTERSECT; if (ieq(t, "xor")) return CM_COMP_EXCLUDE; } return -1; } static...
- `emit_layers` (function) `src/css_mask.c:132` `static int emit_layers(css_decl *dst, int cap, int shorthand, const char *val)`
- `cm_expand` (function) `src/css_mask.c:201` `int cm_expand(const char *prop, const char *val, css_decl *dst, int cap, int webkit_vocab)`

## src/css_mq.c
Depends on: `include/css_box.h`, `include/css_length.h`, `include/css_mq.h`
- `lower_ch` (function) `src/css_mq.c:32` `static char lower_ch(char c)`
- `is_space` (function) `src/css_mq.c:36` `static int is_space(char c)`
- `is_ident_ch` (function) `src/css_mq.c:40` `static int is_ident_ch(char c)`
- `skip_ws` (function) `src/css_mq.c:45` `static void skip_ws(mq_cur *c)`
- `read_word` (function) `src/css_mq.c:50` `static int read_word(mq_cur *c, char *w, size_t cap)` -- static int is_space(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'; } static int...
- `peek_word` (function) `src/css_mq.c:62` `static int peek_word(const mq_cur *c, char *w, size_t cap)` -- /* Reads one identifier at the cursor (lowercased into w); 0 if none. static int read_word(mq_cur *c, char *w...
- `and3` (function) `src/css_mq.c:67` `static int and3(int a, int b)`
- `or3` (function) `src/css_mq.c:73` `static int or3(int a, int b)`
- `not3` (function) `src/css_mq.c:79` `static int not3(int a)`
- `copy_trim_lower` (function) `src/css_mq.c:84` `static int copy_trim_lower(const char *s, size_t a, size_t b, char *dst, size_t cap)` -- return MQ_TRUE; } static int or3(int a, int b) { if (a == MQ_TRUE || b == MQ_TRUE) return MQ_TRUE; if (a ==...
- `feature_of` (function) `src/css_mq.c:107` `static fval feature_of(const char *name, const cmq_env *env)` -- /* --- feature values --- typedef enum { FV_NONE, FV_NUM, FV_KW } fv_kind; typedef struct fval { fv_kind     kind...
- `read_num` (function) `src/css_mq.c:163` `static int read_num(const char *t, double *out, const char **end)` -- } else if (strcmp(name, "update") == 0) { v.kind = FV_KW; v.kw = "fast"; } else if (strcmp(name, "overflow-block")...
- `parse_value` (function) `src/css_mq.c:168` `static int parse_value(const char *t, int unit, double *out)` -- || strcmp(name, "video-dynamic-range") == 0) { v.kind = FV_KW; v.kw = "standard"; } else if (strcmp(name, "scan") ==...
- `cmp_op` (function) `src/css_mq.c:208` `static int cmp_op(double lhs, int op, double rhs)` -- if (strcmp(e, "dpcm") == 0) { out = n * CMQ_CM_PER_IN / CMQ_DPI_PER_DPPX; return 1; } return 0; } if (*e != '\0')...
- `flip_op` (function) `src/css_mq.c:220` `static int flip_op(int op)` -- /* op: '<' '<=' '>' '>=' '=' encoded as 1..5.
- `bool_ctx` (function) `src/css_mq.c:231` `static int bool_ctx(const fval *v)` -- } /* Flips an operator so that `v op name` reads `name op' v`. static int flip_op(int op) { switch (op) { case 1...
- `eval_plain` (function) `src/css_mq.c:239` `static int eval_plain(const char *name, const char *value, const cmq_env *env)` -- case 4: return 2; default: return op; } } /* Boolean context (MQ4 2.4.2): true unless the value is 0 or `none`....
- `read_op` (function) `src/css_mq.c:268` `static int read_op(const char **p)` -- fval f = feature_of(base, env); if (f.kind == FV_NONE) return MQ_UNKNOWN; if (f.kind == FV_KW) { if (range != 0)...
- `eval_range` (function) `src/css_mq.c:282` `static int eval_range(const char *t, const cmq_env *env)` -- static int read_op(const char **p) { const char *q = *p; int op = 0; if (q[0] == '<' && q[1] == '=') { op = 2; q +=...
- `eval_feature` (function) `src/css_mq.c:330` `static int eval_feature(const char *s, size_t a, size_t b, const cmq_env *env)` -- } /* v1 op name op v2: both operators point the same way (MQ4 grammar). int lt = (ops[0] == 1 || ops[0] == 2) &&...
- `eval_in_parens` (function) `src/css_mq.c:355` `static int eval_in_parens(mq_cur *c, int depth)` -- if (name[0] == '\0' || value[0] == '\0') return MQ_UNKNOWN; return eval_plain(name, value, env); } if (strpbrk(t...
- `eval_cond` (function) `src/css_mq.c:382` `static int eval_cond(mq_cur *c, int depth)` -- mq_cur in = { c->s, open + 1, close, c->env }; skip_ws(&in); char w[16]; int nested = (in.i < in.b && in.s[in.i] ==...
- `eval_query` (function) `src/css_mq.c:406` `static int eval_query(const char *s, size_t a, size_t b, const cmq_env *env)` -- skip_ws(c); if (c->i >= c->b) break; mq_cur save = *c; if (!read_word(c, w, sizeof w)) { *c = save; break; } int m =...
- `cmq_matches` (function) `src/css_mq.c:460` `int cmq_matches(const char *s, size_t len, const cmq_env *env)`
- `has_word` (function) `src/css_mq.c:481` `static int has_word(const char *t, const char *w)` -- while (i < len && !(s[i] == ',' && d == 0)) { if (s[i] == '(') ++d; else if (s[i] == ')') --d; ++i; } if...
- `cmq_container_surely` (function) `src/css_mq.c:537` `int cmq_container_surely(const char *s, size_t len, int max_width)`
- `cmq_name_hash` (function) `src/css_mq.c:549` `unsigned cmq_name_hash(const char *s, size_t n)`
- `cmq_container_holds` (function) `src/css_mq.c:556` `int cmq_container_holds(const char *s, size_t len, const cmq_container *scope, int max_width)`
- `container_type_kw` (function) `src/css_mq.c:580` `static int container_type_kw(const char *s, size_t n, int *type)`
- `container_names` (function) `src/css_mq.c:596` `static int container_names(const char *s, size_t n, unsigned names[CMQ_CONTAINER_NAMES])`
- `cmq_container_decl` (function) `src/css_mq.c:618` `int cmq_container_decl(const char *prop, const char *val, int *type,
                       unsig...`

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
- `compound_matches` (function) `src/css_select.c:1081` `static int compound_matches(const css_compound *c, const css_element *el,
                       ...` -- True if one compound matches one element (no ancestor context).
- `built` (function) `src/css_select.c:1116` `* chains the caller built (an element without parent/prev links never matches
 * through that com...`
- `pseudo_is_local` (function) `src/css_select.c:1161` `static int pseudo_is_local(int kind)` -- case COMB_ADJACENT: return (el->prev != NULL) && complex_matches(sel, k - 1, el->prev, target_id, allow_pseudo_el...
- `csel_needs_structure` (function) `src/css_select.c:1174` `int csel_needs_structure(const css_sel *sel)`
- `csel_matches` (function) `src/css_select.c:1197` `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,
              ...`

## src/css_text.c
Depends on: `include/css.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_text.h`, `include/css_values.h`
- `ct_family_of` (function) `src/css_text.c:18` `static int ct_family_of(const char *name)` -- Maps one font-family name (a generic keyword or a common family) to a generic css_font_family bucket; -1 if...
- `ct_interp_fontfamily` (function) `src/css_text.c:47` `int ct_interp_fontfamily(const char *v)` -- font-family: the first recognised name in the comma-separated stack wins (its * generic bucket).
- `ct_interp_texttransform` (function) `src/css_text.c:69` `int ct_interp_texttransform(const char *v)`
- `ct_interp_valign` (function) `src/css_text.c:91` `int ct_interp_valign(const char *v)`
- `ct_expand_valign` (function) `src/css_text.c:122` `int ct_expand_valign(const char *val, css_decl *dst, int cap)` -- vertical-align (CSS 2.1 section 10.8.1) has two productions: a keyword, and a <length-percentage> baseline SHIFT...
- `transition_prop_one` (function) `src/css_text.c:139` `static int transition_prop_one(const char *v)`
- `ct_interp_whitespace` (function) `src/css_text.c:182` `int ct_interp_whitespace(const char *v)`
- `ct_interp_tabsize` (function) `src/css_text.c:195` `int ct_interp_tabsize(const char *v)` -- break-spaces preserves whitespace and wraps; this engine only models the * wrap/keep distinction, so it collapses to...
- `ct_interp_textdeco_style` (function) `src/css_text.c:206` `int ct_interp_textdeco_style(const char *v)` -- } /* tab-size: a non-negative integer (number of spaces). -1 if unsupported. int ct_interp_tabsize(const char *v) {...
- `ct_interp_textdeco_thickness` (function) `src/css_text.c:217` `int ct_interp_textdeco_thickness(const char *v)` -- text-decoration-thickness: `from-font` (keyword -> 0), or a non-negative length * (px -> px, em/rem x16). -1 if...
- `ct_interp_aspect_ratio` (function) `src/css_text.c:229` `int ct_interp_aspect_ratio(const char *v, int *num, int *den)` -- aspect-ratio: `auto`, a `<ratio>` such as `16/9` or `1.5`, or `auto <ratio>` (auto fallback).
- `ct_interp_direction` (function) `src/css_text.c:271` `int ct_interp_direction(const char *v)` -- Both halves share ONE scale, so the ratio keeps its shape: clamping each half to * CSS_LEN_MAX on its own turned...
- `ct_liststyle_kw` (function) `src/css_text.c:277` `static int ct_liststyle_kw(const char *t)`
- `ct_liststyle_unknown_name` (function) `src/css_text.c:298` `static int ct_liststyle_unknown_name(const char *t)` -- A <counter-style> name this engine has no glyph set for.
- `ct_interp_liststyle` (function) `src/css_text.c:309` `int ct_interp_liststyle(const char *v)` -- list-style-type, or the type token of the list-style shorthand: the first * recognised keyword wins. url() (a...
- `ct_emit_spacing` (function) `src/css_text.c:344` `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
- `ct_expand_shadow` (function) `src/css_text.c:357` `int ct_expand_shadow(const char *val, css_decl *dst, int cap)` -- text-shadow (single layer): collects up to three lengths (dx, dy, blur — blur is ignored) and an optional color, in...

## src/css_values.c
Depends on: `include/css.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`
- `cv_parse_num` (function) `src/css_values.c:11` `static int cv_parse_num(const char *s, double *out, const char **endp)`
- `parse_color_depth` (function) `src/css_values.c:18` `static int parse_color_depth(const char *v, int depth)`
- `cv_parse_color` (function) `src/css_values.c:42` `int cv_parse_color(const char *v)`
- `cv_interp_color` (function) `src/css_values.c:47` `int cv_interp_color(const char *v)`
- `cv_color_ok` (function) `src/css_values.c:52` `int cv_color_ok(int c)`
- `mix_arg` (function) `src/css_values.c:61` `static int mix_arg(const char *s, size_t n, double *pct, double *alpha, int *rgb, int depth)` -- One color-mix() argument `[<pct>] <color> [<pct>]` in s[0,n): its percentage (-1 when * absent) and its alpha in...
- `mix_solve` (function) `src/css_values.c:110` `static int mix_solve(const char *v, int depth, int *rgb_out, double *alpha_out)` -- color-mix(in <space>, c1 [p1], c2 [p2]) (CSS Color 5 §2): percentages normalised to 100, a sum under 100 scales the...
- `mix_color` (function) `src/css_values.c:171` `static int mix_color(const char *v, int depth)`
- `mix_alpha` (function) `src/css_values.c:179` `static int mix_alpha(const char *v, int depth)`
- `cv_bg_alpha_of` (function) `src/css_values.c:199` `int cv_bg_alpha_of(const char *v)`
- `alpha_of_depth` (function) `src/css_values.c:204` `static int alpha_of_depth(const char *v, int depth)`
- `cv_interp_bg` (function) `src/css_values.c:324` `int cv_interp_bg(const char *v)`
- `cv_parse_color_t7` (function) `src/css_values.c:369` `int cv_parse_color_t7(const char *v)`
- `cv_text_color` (function) `src/css_values.c:386` `int cv_text_color(const char *v)`
- `cv_filter_scale` (function) `src/css_values.c:395` `double cv_filter_scale(int pct)`

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
- `wide_keyword` (function) `src/css_vars.c:168` `static int wide_keyword(const char *v)` -- A stored value that is a CSS-wide keyword (Cascade 5 §7.3), compared whole and case-insensitively: 1 = initial /...
- `scope_get` (function) `src/css_vars.c:179` `static const char *scope_get(const cvr_scope *sc, const char *name, size_t nlen)`
- `env_value` (function) `src/css_vars.c:204` `static const char *env_value(const char *name, size_t n)` -- The value an env() name resolves to on this device class (CSS Environment Variables 1): a desktop window has no...
- `resolve_rec` (function) `src/css_vars.c:214` `static int resolve_rec(const char *val, size_t vlen, char *out, size_t outcap,
                  ...`
- `cvr_resolve` (function) `src/css_vars.c:303` `int cvr_resolve(const char *val, char *out, size_t outcap, const cvr_scope *sc)`
- `cvr_lookup` (function) `src/css_vars.c:312` `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen)`

## src/data_url.c
Depends on: `include/data_url.h`
- `lower` (function) `src/data_url.c:16` `static int lower(char c)`
- `ci_starts_with` (function) `src/data_url.c:20` `static int ci_starts_with(const char *s, const char *prefix)`
- `du_is_data_url` (function) `src/data_url.c:28` `int du_is_data_url(const char *url)`
- `du_base64_payload` (function) `src/data_url.c:32` `du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len)`
- `du_shape_ok` (function) `src/data_url.c:59` `du_status du_shape_ok(const char *url)`
- `b64_val` (function) `src/data_url.c:70` `static int b64_val(unsigned char c)` -- 0-63 for a base64 alphabet character, -1 otherwise.
- `du_base64_decode` (function) `src/data_url.c:79` `du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len)`
- `hexval` (function) `src/data_url.c:117` `static int hexval(char c)`
- `ascii_ws` (function) `src/data_url.c:124` `static int ascii_ws(char c)`
- `ends_ci` (function) `src/data_url.c:129` `static int ends_ci(const char *s, size_t n, const char *suf)` -- } static int hexval(char c) { if (c >= '0' && c <= '9') return c - '0'; if (c >= 'a' && c <= 'f') return c - 'a' +...
- `du_decode` (function) `src/data_url.c:140` `du_status du_decode(const char *url, char *mime, size_t mime_cap, uint8_t **out, size_t *out_len)`

## src/disk_store.c
Depends on: `include/disk_store.h`, `include/local_store.h`, `include/util.h`
- `fsync_dir` (function) `src/disk_store.c:32` `static void fsync_dir(const char *path)` -- Best-effort fsync of the directory holding path, for crash durability of the * rename.
- `map_ls` (function) `src/disk_store.c:50` `static ds_status map_ls(ls_status s)`
- `ds_write` (function) `src/disk_store.c:66` `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,
               ...`
- `ds_read` (function) `src/disk_store.c:103` `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],
                  uint8_t **ou...`
- `ds_free` (function) `src/disk_store.c:136` `void ds_free(uint8_t *buf, size_t len)`

## src/doc_title.c
Depends on: `include/doc_title.h`
- `is_ascii_space` (function) `src/doc_title.c:19` `static int is_ascii_space(unsigned c)`
- `is_bidi_control` (function) `src/doc_title.c:23` `static int is_bidi_control(uint32_t cp)`
- `lower` (function) `src/doc_title.c:28` `static unsigned lower(unsigned c)`
- `utf8_next` (function) `src/doc_title.c:62` `static size_t utf8_next(const unsigned char *s, size_t n, uint32_t *cp)` -- } else { b[0] = (unsigned char)(0xF0u | (cp >> 18)); b[1] = (unsigned char)(0x80u | ((cp >> 12) & 0x3Fu)); b[2] =...
- `char_ref` (function) `src/doc_title.c:83` `static size_t char_ref(const unsigned char *s, size_t n, uint32_t *cp)` -- A character reference at s[0] == '&'.
- `at_end_tag` (function) `src/doc_title.c:116` `static int at_end_tag(const unsigned char *s, size_t i, size_t n, const char *name)` -- } if (i == d0) return 0; if (i < n && s[i] == ';') ++i; cp = v; return i; } for (size_t k = 0; k < sizeof named /...
- `find_end_tag` (function) `src/doc_title.c:125` `static size_t find_end_tag(const unsigned char *s, size_t i, size_t n, const char *name)`
- `dt_scan` (function) `src/doc_title.c:131` `int dt_scan(const char *html, size_t len, char *out, size_t cap)`

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
- `node_next` (function) `src/dom.c:233` `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` -- struct dom_index { lxb_dom_node_t      **nodes;    /* arena: id -> element node, in document order size_t...
- `valid` (function) `src/dom.c:243` `static int valid(const dom_index *idx, dom_node_id n)`
- `index_element` (function) `src/dom.c:255` `static int index_element(dom_index *idx, lxb_dom_element_t *el, dom_node_id id)` -- A handle that is an ELEMENT: every element-only operation (tag, attributes, selectors, innerHTML, being a parent)...
- `dom_build` (function) `src/dom.c:292` `dom_status dom_build(const hp_document *doc, dom_index **out)`
- `dom_free` (function) `src/dom.c:333` `void dom_free(dom_index *idx)`
- `dom_mutation_count` (function) `src/dom.c:345` `uint64_t dom_mutation_count(const dom_index *idx)`
- `dom_node_count` (function) `src/dom.c:349` `size_t dom_node_count(const dom_index *idx)`
- `node_in_document` (function) `src/dom.c:357` `static int node_in_document(const lxb_dom_node_t *node)` -- 1 when `node` is in the document tree (its topmost ancestor is the document node).
- `dom_get_element_by_id` (function) `src/dom.c:363` `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)`
- `dom_is_connected` (function) `src/dom.c:369` `int dom_is_connected(const dom_index *idx, dom_node_id node)`
- `dom_get_connected_by_id` (function) `src/dom.c:373` `dom_node_id dom_get_connected_by_id(const dom_index *idx, const char *id)`
- `copy_ids` (function) `src/dom.c:396` `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)`
- `dom_get_by_tag` (function) `src/dom.c:403` `size_t dom_get_by_tag(const dom_index *idx, const char *tag,
                      dom_node_id *o...`
- `dom_get_by_class` (function) `src/dom.c:412` `size_t dom_get_by_class(const dom_index *idx, const char *cls,
                        dom_node_i...`
- `id_of` (function) `src/dom.c:425` `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)` -- Max complex selectors in one comma-separated list.
- `parse_selector_list` (function) `src/dom.c:435` `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)` -- Parses a selector list "a, b, c" into up to cap css_sel.
- `node_matches_any` (function) `src/dom.c:468` `static int node_matches_any(const lxb_dom_node_t *cn,
                            const css_sel *...` -- s.order = (int)n; s.rule = 0; out[n++] = s; } } start = i + 1; } break; default: break; } } return n; } /* Nonzero...
- `count` (function) `src/dom.c:476` `* count (may exceed cap), and returns DOM_NODE_NONE. */
static dom_node_id qs_walk(const dom_inde...`
- `dom_query_selector` (function) `src/dom.c:506` `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,
                          ...`
- `dom_query_selector_all` (function) `src/dom.c:515` `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,
                           ...`
- `dom_matches` (function) `src/dom.c:526` `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)`
- `dom_closest` (function) `src/dom.c:535` `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,
                        const cha...`
- `dom_document_position` (function) `src/dom.c:551` `size_t dom_document_position(const dom_index *idx, dom_node_id node)`
- `dom_precedes` (function) `src/dom.c:556` `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)`
- `dom_node_at` (function) `src/dom.c:561` `dom_node_id dom_node_at(const dom_index *idx, size_t position)`
- `dom_parent` (function) `src/dom.c:566` `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)`
- `dom_first_child` (function) `src/dom.c:576` `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)`
- `dom_next_sibling` (function) `src/dom.c:584` `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)`
- `dom_tag_name` (function) `src/dom.c:592` `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)`
- `dom_get_attribute` (function) `src/dom.c:603` `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,
                           ...`
- `dom_attribute_names` (function) `src/dom.c:625` `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,
                           con...`
- `dom_text_content` (function) `src/dom.c:643` `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)`
- `dom_document_title` (function) `src/dom.c:653` `const char *dom_document_title(const dom_index *idx, size_t *len)`
- `dom_set_text_content` (function) `src/dom.c:666` `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,
                               ...`
- `dom_set_document_title` (function) `src/dom.c:701` `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)`
- `idx_push` (function) `src/dom.c:713` `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)` -- } dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len) { if (idx != NULL)...
- `dom_create_element` (function) `src/dom.c:731` `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)`
- `dom_append_child` (function) `src/dom.c:751` `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
- `dom_remove_child` (function) `src/dom.c:766` `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
- `dom_set_attribute` (function) `src/dom.c:775` `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,
                             const...`
- `dom_remove_attribute` (function) `src/dom.c:805` `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)`
- `index_subtree` (function) `src/dom.c:815` `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)` -- } return DOM_OK; } dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name) { if (idx !=...
- `dom_set_inner_html` (function) `src/dom.c:825` `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,
                              con...`
- `ih_append` (function) `src/dom.c:879` `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)`
- `ih_free` (function) `src/dom.c:906` `static void ih_free(ih_acc *a)`
- `dom_get_inner_html` (function) `src/dom.c:933` `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,
                           ...`
- `dom_insert_before` (function) `src/dom.c:963` `dom_status dom_insert_before(dom_index *idx, dom_node_id parent, dom_node_id child,
             ...`
- `dom_clone_node` (function) `src/dom.c:981` `dom_status dom_clone_node(dom_index *idx, dom_node_id node, int deep, dom_node_id *out_id)`
- `dom_move_children` (function) `src/dom.c:995` `dom_status dom_move_children(dom_index *idx, dom_node_id src, dom_node_id parent,
               ...`
- `char_kind` (function) `src/dom.c:1029` `static int char_kind(const lxb_dom_node_t *n)`
- `handle_of` (function) `src/dom.c:1040` `static dom_node_id handle_of(dom_index *idx, lxb_dom_node_t *n)` -- /* --- text and comment nodes (spec/dom.md 9) --- static int char_kind(const lxb_dom_node_t *n) { switch (n->type) {...
- `dom_node_kind` (function) `src/dom.c:1048` `int dom_node_kind(const dom_index *idx, dom_node_id node)`
- `dom_child_node` (function) `src/dom.c:1052` `dom_node_id dom_child_node(dom_index *idx, dom_node_id node, int last)`
- `dom_sibling_node` (function) `src/dom.c:1059` `dom_node_id dom_sibling_node(dom_index *idx, dom_node_id node, int prev)`
- `dom_create_char_node` (function) `src/dom.c:1066` `dom_status dom_create_char_node(dom_index *idx, int kind, const char *text, size_t len,
         ...`
- `dom_handle_of_native` (function) `src/dom.c:1080` `dom_node_id dom_handle_of_native(dom_index *idx, const void *native)`
- `dom_native_node` (function) `src/dom.c:1086` `const void *dom_native_node(const dom_index *idx, dom_node_id node)`

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
- `dd_format` (function) `src/dom_debug.c:400` `size_t dd_format(const rd_doc *doc, char *out, size_t cap)`
- `dd_format_css` (function) `src/dom_debug.c:432` `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)` -- } dd_puts(&c, "[blocks]\n"); for (size_t i = 0; i < nblocks; ++i) { const rd_block *b = rd_at(doc, i); if (b !=...

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

## src/exact_key.c
Depends on: `include/exact_key.h`
- `ek_init` (function) `src/exact_key.c:6` `void ek_init(ek_key *k)`
- `ek_reset` (function) `src/exact_key.c:13` `void ek_reset(ek_key *k)`
- `ek_put` (function) `src/exact_key.c:19` `void ek_put(ek_key *k, const void *p, size_t len)`
- `ek_equal` (function) `src/exact_key.c:36` `int ek_equal(const ek_key *a, const ek_key *b)`
- `ek_swap` (function) `src/exact_key.c:41` `void ek_swap(ek_key *a, ek_key *b)`
- `ek_free` (function) `src/exact_key.c:48` `void ek_free(ek_key *k)`

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


Next: [API_p9.md](API_p9.md)
