# API (page 5 of 12)
Previous: [API_p4.md](API_p4.md)

## include/page_view.h
Depends on: `include/css.h`, `include/dom.h`, `include/html_parse.h`
Imported by: `include/box_tree.h`, `include/frame_host.h`, `include/render_doc.h`, `include/tab.h`, `src/dom_debug.c`, `src/freedom.c`, `src/page_view.c`, `src/tab.c`, `tests/test_box_tree.c`, `tests/test_dom_debug.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`
- `container` (function) `include/page_view.h:242` `* cont_id groups runs of one container (-1 = none);`
- `bx_display` (function) `include/page_view.h:243` `* bx_display (flex/grid);`
- `order` (function) `include/page_view.h:307` `* groups the runs of ONE floated element in document order (-1 = not in a float);`
- `itself` (function) `include/page_view.h:371` `* by itself (bx_width_cap2);`
- `CSS_LEN_UNSET` (function) `include/page_view.h:570` `* CSS_LEN_UNSET (unset) / CSS_LEN_AUTO. z_index is signed, or CSS_LEN_UNSET. v1 * paints only position:relative (an...`
- `scale` (function) `include/page_view.h:645` `* scale(1)) and rotate in whole degrees (transform_rotate);`
- `tree` (function) `include/page_view.h:690` `* box tree (a mask covers its whole subtree);`
- `declare` (function) `include/page_view.h:879` `* margin the author did not declare (px or %), 0 on a declared side (the body's * own box, or nothing for 0, owns...`
- `nonzero` (function) `include/page_view.h:891` `* when nonzero (JS allowed for this page) the <noscript> subtree is suppressed. */ pv_status pv_build_ex(const...`
- `resolved` (function) `include/page_view.h:898` `* author CSS is still resolved (the presentation layer decides whether to apply it). * pv_build_ex is pv_build_full...`
- `policy` (function) `include/page_view.h:906` `* TRUSTED parent under full network policy (spec/tab.md §8) -- page_view stays * pure and never fetches. The...`
- `pv_computed_new` (function) `include/page_view.h:938` `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css, size_t extern_len...`
- `pv_computed_new_cached` (function) `include/page_view.h:941` `pv_computed *pv_computed_new_cached(const hp_document *doc, int prefers_dark, const char *extern_css, size_t...` -- getComputedStyle bridge (spec/js_computed_style.md).
- `pv_computed_get` (function) `include/page_view.h:949` `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st, double *font_px, int *inherited_color);` -- Resolves native_el (a dom_native_node pointer of the SAME document) into *st; when non-NULL, *font_px receives its...
- `pv_computed_free` (function) `include/page_view.h:952` `void pv_computed_free(pv_computed *pc);`
- `cause` (function) `include/page_view.h:956` `* cause (spec/css_drops.md). Builds no view and changes nothing -- it exists so * "what is this page's CSS losing?"...`
- `pv_new` (function) `include/page_view.h:968` `pv_view *pv_new(void);` -- Allocates an empty view (used by the IPC deserialiser to rebuild a view on the * receiving side).
- `form` (function) `include/page_view.h:987` `* form (-1 if none);`
- `pv_set_emphasis` (function) `include/page_view.h:1019` `void pv_set_emphasis(pv_view *v, int bold, int italic);` -- Sets the inline emphasis flags (bold from <b>/<strong>/<th>, italic from <i>/<em>) on the most recently appended run.
- `default` (function) `include/page_view.h:1024` `* structure is carried by default (not gated by caps.css). */ void pv_set_indent(pv_view *v, int indent);`
- `pv_set_color` (function) `include/page_view.h:1027` `void pv_set_color(pv_view *v, int fg_rgb);`
- `pv_set_bgcolor` (function) `include/page_view.h:1034` `void pv_set_bgcolor(pv_view *v, int bg_rgb);` -- Sets the author background-color (packed 0xRRGGBB, or -1 for none) on the most recently appended run.
- `pv_set_text_style` (function) `include/page_view.h:1043` `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs, int line_scale, int text_decoration);` -- Sets the author text presentation (text_align as a css_align, font_scale as a font-size percent or 0, font_abs as 1...
- `pv_text_ext_reset` (function) `include/page_view.h:1100` `void pv_text_ext_reset(pv_text_ext *e);` -- Gradient text (2026-07-19). text_fill: -webkit-text-fill-color from the nearest ancestor that sets it (packed /...
- `ancestors` (function) `include/page_view.h:1105` `* itself by walking its ancestors (css_visibility, 0 = unset). * * An explicit value on the run WINS over the box...`
- `pv_set_text_ext` (function) `include/page_view.h:1115` `void pv_set_text_ext(pv_view *v, const pv_text_ext *e);`
- `pv_set_grad_text` (function) `include/page_view.h:1121` `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4);` -- Sets the gradient-text fill (grad_text_*) verbatim on the most recently appended run. n < 2 is a no-op (no gradient).
- `run` (function) `include/page_view.h:1124` `* run (cont_id, the bx_display, the parsed gap/justify/cols, plus flex-wrap/ * row-gap/align-items). No-op on an...`
- `pv_set_row_span` (function) `include/page_view.h:1137` `void pv_set_row_span(pv_view *v, int row_span);` -- Sets the container's grid track sizes and this run's ITEM column span on the most recently appended run...
- `pv_set_grid_area` (function) `include/page_view.h:1141` `void pv_set_grid_area(pv_view *v, int row_start, int col_start);` -- Sets the last run's RESOLVED named-grid cell (-1, -1 = auto-placed).
- `pv_set_grid_rows` (function) `include/page_view.h:1142` `void pv_set_grid_rows(pv_view *v, int grid_rows);`
- `pv_set_ua_tag` (function) `include/page_view.h:1147` `void pv_set_ua_tag(pv_view *v, int ua_tag);` -- Sets the last run's ua_tag (a bx_ua_tag code: the user-agent box identity of its nearest block-level ancestor).
- `pv_set_cont_box` (function) `include/page_view.h:1151` `void pv_set_cont_box(pv_view *v, int cont_box_id);` -- Sets the last run's cont_box_id (the box enclosing its container's items; -1 = * none).
- `pv_set_grid` (function) `include/page_view.h:1152` `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span);`
- `pv_set_flex` (function) `include/page_view.h:1160` `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis, int flex_order, int flex_direction, int...` -- Stage 3: sets the flex per-item values on the most recently appended run — the ITEM's resolved grow/shrink (x100, -1...
- `pv_set_flex_mauto` (function) `include/page_view.h:1163` `void pv_set_flex_mauto(pv_view *v, int mauto);` -- Stage 3: sets the flex per-item values on the most recently appended run — the ITEM's resolved grow/shrink (x100, -1...
- `pv_set_cont_item` (function) `include/page_view.h:1167` `void pv_set_cont_item(pv_view *v, int cont_item);` -- Sets the container-item ordinal on the most recently appended run (-1 = none). * No-op on an empty or NULL view; the...
- `pv_set_float_w` (function) `include/page_view.h:1178` `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box, int float_ow, int float_ow_pct, int...` -- Stamps the float founder's own declared width halves (pv_run.float_w) on the * most recently appended run.
- `pv_set_float` (function) `include/page_view.h:1181` `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear, int float_ml, int float_ml_pct, int...`
- `pv_set_box` (function) `include/page_view.h:1191` `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w, int box_center, int box_mt, int box_mb);` -- Sets the author box model on the most recently appended run (left/right insets, width cap, centered flag, and...
- `pv_set_box_pct` (function) `include/page_view.h:1197` `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct, int box_mt_pct, int box_mb_pct);` -- Sets the symbolic percentage width cap (per-mille, 0 = none; Hito 32) on the most recently appended run.
- `pv_set_box_maxw` (function) `include/page_view.h:1202` `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct);` -- Sets the max-width cap (px half, 0 = none; per-mille half, 0 = none) on the most * recently appended run.
- `pv_set_node_id` (function) `include/page_view.h:1207` `void pv_set_node_id(pv_view *v, dom_node_id node_id);` -- Keystone (Stage 0) setter for the most recently appended run: the dom_node_id of the source element.
- `pv_set_block_id` (function) `include/page_view.h:1212` `void pv_set_block_id(pv_view *v, int block_id);` -- Box engine (Hito 23b-8) setter for the most recently appended run: the block_id of the box-carrying block it belongs...
- `pv_set_own_box` (function) `include/page_view.h:1216` `void pv_set_own_box(pv_view *v, int box_id);` -- Records the replaced element's own box def index on the last appended run.
- `pv_set_oof` (function) `include/page_view.h:1220` `void pv_set_oof(pv_view *v, int oof);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_justify_self` (function) `include/page_view.h:1223` `void pv_set_justify_self(pv_view *v, int justify_self);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_block_node` (function) `include/page_view.h:1226` `void pv_set_block_node(pv_view *v, dom_node_id id);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_br_line` (function) `include/page_view.h:1234` `void pv_set_br_line(pv_view *v, int br_line);` -- Sets the last appended run's PV_BR_* flags (see pv_run.br_line); other bits * are dropped.
- `pv_cont_count` (function) `include/page_view.h:1249` `size_t pv_cont_count(const pv_view *v);` -- pv_cont_count is v->ncont (0 when v is NULL); pv_cont_at returns conts[i] * (i == a cont_id) or NULL when out of...
- `pv_cont_at` (function) `include/page_view.h:1250` `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i);`
- `pv_set_input_checked` (function) `include/page_view.h:1254` `void pv_set_input_checked(pv_view *v, int checked);` -- Sets the input's checked state (-1 n/a, 0 unchecked, 1 checked) on the most * recently appended run.
- `pv_set_input_placeholder` (function) `include/page_view.h:1258` `void pv_set_input_placeholder(pv_view *v, int ph_color);` -- Sets the input's checked state (-1 n/a, 0 unchecked, 1 checked) on the most * recently appended run.
- `pv_svg_append_root_attrs` (function) `include/page_view.h:1264` `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs, size_t *out_len);` -- Appends attrs (e.g.
- `pv_placeholder_color` (function) `include/page_view.h:1267` `int pv_placeholder_color(const css_style *ph);` -- Appends attrs (e.g.
- `pv_set_input_select_opts` (function) `include/page_view.h:1271` `void pv_set_input_select_opts(pv_view *v, const char *select_opts);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_free` (function) `include/page_view.h:1274` `void pv_free(pv_view *v);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_count` (function) `include/page_view.h:1277` `size_t pv_count(const pv_view *v);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_at` (function) `include/page_view.h:1278` `const pv_run *pv_at(const pv_view *v, size_t i);`
- `pv_box_count` (function) `include/page_view.h:1282` `size_t pv_box_count(const pv_view *v);` -- Box tree accessors (Step D). pv_box_count is the number of box definitions; * pv_box_at returns boxes[i] (i == a...
- `pv_box_at` (function) `include/page_view.h:1283` `const pv_box_def *pv_box_at(const pv_view *v, size_t i);`

## include/pdf_export.h
Imported by: `gui/browser_ui.c`, `src/download.c`, `src/pdf_export.c`, `tests/test_pdf_export.c`
- `fallback` (function) `include/pdf_export.h:46` `* fallback (PE_ERR_OVERFLOW, out left empty). title == NULL is treated as empty. * Does NOT append the extension...`
- `trusted` (function) `include/pdf_export.h:51` `* dir is trusted (chosen by the app from XDG/$HOME);`
- `literal` (function) `include/pdf_export.h:52` `* trusted literal (e.g. PE_EXT / PE_EXT_PNG);`
- `pe_paginate` (function) `include/pdf_export.h:70` `size_t pe_paginate(const double *tops, const double *heights, size_t n, double page_h, int *out_page, double...` -- Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h...

## include/perf_trace.h
Imported by: `src/freedom.c`, `src/perf_trace.c`, `tests/test_perf_trace.c`
- `pt_init` (function) `include/perf_trace.h:46` `void pt_init(pt_trace *t);` -- #define PT_MAX_SAMPLES 256 typedef struct pt_stage_stats { uint64_t samples[PT_MAX_SAMPLES]; size_t   fill;   /*...
- `pt_elapsed_us` (function) `include/perf_trace.h:50` `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us);` -- end_us - start_us with an anti-underflow guard: end < start yields 0 * instead of wrapping to a huge uint64_t.
- `pt_record` (function) `include/perf_trace.h:54` `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us);` -- Record one sample (microseconds) for the given stage.
- `pt_count` (function) `include/perf_trace.h:57` `size_t pt_count(const pt_trace *t, pt_stage stage);` -- Record one sample (microseconds) for the given stage.
- `pt_last_us` (function) `include/perf_trace.h:60` `uint64_t pt_last_us(const pt_trace *t, pt_stage stage);` -- Record one sample (microseconds) for the given stage.
- `pt_min_us` (function) `include/perf_trace.h:63` `uint64_t pt_min_us(const pt_trace *t, pt_stage stage);` -- Record one sample (microseconds) for the given stage.
- `pt_max_us` (function) `include/perf_trace.h:64` `uint64_t pt_max_us(const pt_trace *t, pt_stage stage);`
- `pt_median_us` (function) `include/perf_trace.h:65` `uint64_t pt_median_us(const pt_trace *t, pt_stage stage);`
- `pt_stage_name` (function) `include/perf_trace.h:69` `const char *pt_stage_name(pt_stage stage);` -- Short lowercase stage name ("fetch".."shape"); "unknown" if out of range. * Static string, never NULL.
- `pt_format` (function) `include/perf_trace.h:76` `size_t pt_format(const pt_trace *t, char *buf, size_t cap);` -- Deterministic dump, one line per stage with count > 0, enum order: stage=<name> n=<total> last_us=<n> min_us=<n>...

## include/pq_seal.h
Depends on: `include/local_store.h`
Imported by: `src/http_cache.c`, `src/pq_seal.c`, `tests/test_pq_seal.c`
- `pqs_free` (function) `include/pq_seal.h:41` `void pqs_free(pqs_keys *k);`
- `pqs_buf_free` (function) `include/pq_seal.h:51` `void pqs_buf_free(uint8_t *buf, size_t len);` -- DER of the PRIVATE key: secret, the caller seals it before it touches disk. *der is owned * (release with...

## include/prefetch.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/prefetch.c`, `tests/test_prefetch.c`
- `pf_scan` (function) `include/prefetch.h:62` `int pf_scan(const char *html, size_t len, pf_list *out);` -- Lookahead scan of hostile HTML.
- `pf_list_free` (function) `include/prefetch.h:63` `void pf_list_free(pf_list *l);`
- `specifiers` (function) `include/prefetch.h:110` `* specifiers (each < PF_SPEC_MAX) into out[k] and returns how many. Pure. */ size_t pf_scan_imports(const char *js...`
- `pf_find_importmap` (function) `include/prefetch.h:115` `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n);` -- Span of the first <script type=importmap> body in html (pure, bounded): 1 with * [*start, *start + *n) set, or 0...
- `started` (function) `include/prefetch.h:121` `* to fetch or no thread started (the caller fetches serially). */ int pf_pool_start_page(pf_pool *p, const char...`
- `pf_pool_add` (function) `include/prefetch.h:127` `int pf_pool_add(pf_pool *p, const char *url);` -- Queues one more URL on a started pool (deduplicated, bounded by PF_MAX_JOBS). * Returns 1 when added, 0 when already...
- `fetch` (function) `include/prefetch.h:132` `* claiming jobs and running fetch(ctx, "GET", url, ...). Returns 0 on success or * -1 when no thread could start...`
- `pf_pool_take` (function) `include/prefetch.h:145` `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status, char **body, size_t *len, char **ctype);` -- Cache-first take.
- `pf_pool_finish` (function) `include/prefetch.h:151` `void pf_pool_finish(pf_pool *p);` -- Joins the worker threads and frees every unconsumed result.
- `pool` (function) `include/prefetch.h:155` `* whose URL is pooled is served from the pool (a failed prefetch propagates the * failure -- never refetched);`
- `pf_pooled_fetch` (function) `include/prefetch.h:165` `int pf_pooled_fetch(void *vctx, const char *method, const char *url, const char *body, size_t body_len, int...`

## include/prefs.h
Imported by: `gui/browser_ui.c`, `include/profile.h`, `include/ui.h`, `src/prefs.c`, `tests/test_prefs.c`, `tests/test_profile.c`
- `prefs_init` (function) `include/prefs.h:66` `void prefs_init(prefs_state *p);` -- Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `prefs_free` (function) `include/prefs.h:69` `void prefs_free(prefs_state *p);` -- Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `free` (function) `include/prefs.h:72` `* free(). */ prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len);`
- `prefs_bookmark_index` (function) `include/prefs.h:82` `int prefs_bookmark_index(const prefs_state *p, const char *url);` -- Parses text[0..len) over an out ALREADY initialised with prefs_init.
- `prefs_suggest` (function) `include/prefs.h:101` `int prefs_suggest(const prefs_state *p, const char *query, char *out, size_t row_len, int max_rows);` -- Omnibox autocomplete: up to max_rows distinct URLs matching query (case- insensitive) written to out (rows of...
- `anyway` (function) `include/prefs.h:106` `* page is rendered by the normal confined pipeline anyway (defence in depth). * *out is owned (free());`

## include/profile.h
Depends on: `include/local_store.h`, `include/prefs.h`
Imported by: `gui/browser_ui.c`, `src/profile.c`, `tests/test_profile.c`
- `absent` (function) `include/profile.h:53` `* the keyfile when absent (0600, atomic write);`
- `closed` (function) `include/profile.h:54` `* wrong size fails closed (PROFILE_ERR_KEY, never overwritten). Derives the * AEAD key (Argon2id, per-device salt)...`
- `profile_close` (function) `include/profile.h:67` `void profile_close(profile_ctx *ctx);` -- Loads and decrypts prefs.bin over an out ALREADY initialised (prefs_init).

## include/render_doc.h
Depends on: `include/page_view.h`, `include/render_policy.h`
Imported by: `gui/browser_ui.c`, `include/dom_debug.h`, `src/freedom.c`, `src/render_doc.c`, `tests/test_dom_debug.c`, `tests/test_render_doc.c`
- `list` (function) `include/render_doc.h:18` `* inert display list (page_view) and the presentation orchestrator (the GUI and * the --headless writer). It decides...`
- `RD_IMAGE` (function) `include/render_doc.h:59` `* RD_IMAGE (image src) and RD_INPUT (the owning form's action);`
- `form` (function) `include/render_doc.h:63` `* form (-1 = none);`
- `default` (function) `include/render_doc.h:153` `* default (layout is structure, not author styling, and leaks nothing to the * network) so the presentation layer...`
- `to` (function) `include/render_doc.h:253` `* belongs to (-1 = none);`
- `rdp_images_warning` (function) `include/render_doc.h:308` `* rdp_images_warning() is prepended so the user is always told. Each image * becomes an RD_IMAGE block whose...`
- `rd_free` (function) `include/render_doc.h:318` `void rd_free(rd_doc *d);` -- Builds the paint-ready document from an inert display list and the page's capabilities. view == NULL is treated as...
- `rd_count` (function) `include/render_doc.h:321` `size_t rd_count(const rd_doc *d);` -- images and caps.images is false, a single RD_NOTICE block carrying rdp_images_warning() is prepended so the user is...
- `rd_at` (function) `include/render_doc.h:322` `const rd_block *rd_at(const rd_doc *d, size_t i);`
- `rd_box_count` (function) `include/render_doc.h:326` `size_t rd_box_count(const rd_doc *d);` -- Box tree accessors (Step D). rd_box_count is the number of box definitions (0 when * caps.css is off); rd_box_at...
- `rd_box_at` (function) `include/render_doc.h:327` `const pv_box_def *rd_box_at(const rd_doc *d, size_t i);`
- `rd_cont_count` (function) `include/render_doc.h:331` `size_t rd_cont_count(const rd_doc *d);` -- Container table accessors. rd_cont_count is the number of containers; rd_cont_at * returns conts[i] (i == a run's...
- `rd_cont_at` (function) `include/render_doc.h:332` `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i);`
- `rd_kind_name` (function) `include/render_doc.h:336` `const char *rd_kind_name(rd_kind k);` -- Stable, short English name of a block kind for structured/agent output.
- `rd_block_tag` (function) `include/render_doc.h:344` `const char *rd_block_tag(const rd_block *b);` -- Canonical HTML tag name for a block, so the presentation layer can look up its user-agent box (box_style) without...
- `rd_block_heading_level` (function) `include/render_doc.h:351` `int rd_block_heading_level(const rd_block *b);` -- Effective heading level of a block, 0 when it is not heading content.
- `decision` (function) `include/render_doc.h:354` `* decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never * NULL. */ const char...`
- `IMG_FAIL_OK` (function) `include/render_doc.h:360` `* IMG_FAIL_OK (not a failure) or the reason is unknown. */ const char *rd_image_fail_label(img_fail_reason reason);`
- `rd_input_label` (function) `include/render_doc.h:365` `const char *rd_input_label(int input_type);` -- Stable, short English name of a form control type (a pv_input_type value), e.g. * "text" / "password" / "submit".
- `rd_input_invisible` (function) `include/render_doc.h:370` `int rd_input_invisible(int input_type);` -- Nonzero iff a control of this type has no face of its own and is therefore never laid out or painted: a hidden...

## include/render_policy.h
Imported by: `gui/browser_ui.c`, `include/render_doc.h`, `include/webcaps.h`, `src/freedom.c`, `src/render_policy.c`, `tests/test_dom_debug.c`, `tests/test_render_doc.c`, `tests/test_render_policy.c`
- `rdp_is_tracking_pixel` (function) `include/render_policy.h:53` `int rdp_is_tracking_pixel(int w, int h);` -- Tracking-pixel heuristic over an image's declared dimensions. w/h negative means "unknown".
- `size` (function) `include/render_policy.h:56` `* announced size (e.g. <img width height>);`
- `rdp_img_reason` (function) `include/render_policy.h:66` `const char *rdp_img_reason(rdp_img_decision d);` -- Stable, short, English reason string for structured/agent-friendly output. * Never NULL; an unknown enum value...
- `rdp_images_warning` (function) `include/render_policy.h:69` `const char *rdp_images_warning(void);` -- Stable, short, English reason string for structured/agent-friendly output. * Never NULL; an unknown enum value...

## include/renderer.h
Imported by: `src/renderer.c`, `tests/test_renderer.c`
- `rd_result_free` (function) `include/renderer.h:46` `void rd_result_free(rd_result *out);` -- Renders untrusted HTML out-of-process and returns an inert title + text. html == NULL or out == NULL => RD_ERR_NULL_ARG.

## include/request_policy.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/render_policy.c`, `src/request_policy.c`, `src/secure_fetch.c`, `src/tab.c`, `tests/test_request_policy.c`
- `rp_host_of` (function) `include/request_policy.h:30` `int rp_host_of(const char *url, char *out, size_t out_size);` -- Lowercased host of an absolute URL into out.
- `rp_site_of` (function) `include/request_policy.h:34` `int rp_site_of(const char *host, char *out, size_t out_size);` -- Registrable domain ("site") of a host into out (simplified public-suffix * rule).
- `rp_same_site` (function) `include/request_policy.h:37` `int rp_same_site(const char *top_level_url, const char *request_url);` -- Registrable domain ("site") of a host into out (simplified public-suffix * rule).
- `rp_sanitize_request_headers` (function) `include/request_policy.h:57` `int rp_sanitize_request_headers(const char *raw, char *out, size_t cap);` -- Filters the page-supplied header block `raw` ("Name: value" lines separated by '\n') into `out` (same format...
- `rp_headers_have` (function) `include/request_policy.h:61` `static inline int rp_headers_have(const char *lines, const char *name)` -- 1 when the sanitized block `lines` carries a header called `name` (case-insensitive).

## include/secure_fetch.h
Depends on: `include/anti_fp.h`
Imported by: `gui/browser_ui.c`, `include/cached_fetch.h`, `include/ws_hub.h`, `src/freedom.c`, `src/secure_fetch.c`, `src/tab.c`, `tests/itest_secure_fetch.c`, `tests/test_secure_fetch.c`
- `validators` (function) `include/secure_fetch.h:18` `* The security logic lives in pure validators (no I/O);`
- `rp_sanitize_request_headers` (function) `include/secure_fetch.h:111` `* rp_sanitize_request_headers ("Name: value\n" lines);`
- `sf_global_init` (function) `include/secure_fetch.h:233` `void sf_global_init(void);` -- Initialises process-global transport state (libcurl/OpenSSL) once, from the main thread, before any concurrent...
- `EXCLUDED` (function) `include/secure_fetch.h:239` `* cookies are EXCLUDED (network-only, never exposed to JS) and expired cookies skipped. * Only for a TRUSTED host...`
- `sf_cookie_put` (function) `include/secure_fetch.h:246` `void sf_cookie_put(const char *url, const char *namevalue);` -- Injects a JS-set cookie ("name=value") into the shared jar, scoped to url's host, as if it arrived via Set-Cookie...
- `sf_cookie_line_matches` (function) `include/secure_fetch.h:251` `int sf_cookie_line_matches(const char *line, const char *host, const char *path, long now, char *out, size_t outsz);` -- Pure: parses one CURLINFO_COOKIELIST Netscape line ("domain\\tflag\\tpath\\tsecure\\t expiry\\tname\\tvalue"); if...
- `sf_user_agent_or_default` (function) `include/secure_fetch.h:260` `const char *sf_user_agent_or_default(const char *ua);` -- Returns ua when it is a non-empty string, else SF_DEFAULT_USER_AGENT.
- `sf_accept_language_or_default` (function) `include/secure_fetch.h:264` `const char *sf_accept_language_or_default(const char *lang);` -- As sf_user_agent_or_default for Accept-Language.
- `sf_impersonate_kex_groups` (function) `include/secure_fetch.h:268` `const char *sf_impersonate_kex_groups(void);` -- The interim impersonation ClientHello strings (pure; single source of truth so the * shaping is unit-testable...
- `sf_impersonate_tls13_ciphers` (function) `include/secure_fetch.h:269` `const char *sf_impersonate_tls13_ciphers(void);`
- `skipped` (function) `include/secure_fetch.h:289` `* skipped (a classical key exchange is accepted);`
- `sf_is_redirect_code` (function) `include/secure_fetch.h:300` `int sf_is_redirect_code(long http_code);` -- Enforces the full connection policy in order: TLS version, then KE group, then certificate chain.
- `sf_header_value` (function) `include/secure_fetch.h:311` `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz);` -- Generic header-line reader for the cache validators: when header_line is `name:` (matched case-insensitively, name...
- `bits` (function) `include/secure_fetch.h:348` `* *flags receives CURLWS_* bits (text/binary/close/cont);`
- `sf_ws_fd` (function) `include/secure_fetch.h:355` `int sf_ws_fd(const sf_ws *ws);` -- Non-blocking: reads one frame chunk into buf. *got == 0 when nothing is pending. *flags receives CURLWS_* bits...
- `sf_ws_close` (function) `include/secure_fetch.h:358` `void sf_ws_close(sf_ws *ws);` -- Non-blocking: reads one frame chunk into buf. *got == 0 when nothing is pending. *flags receives CURLWS_* bits...
- `connection` (function) `include/secure_fetch.h:362` `* on each connection (Zero Trust). Each target is re-validated and a downgrade * to http:// is refused. Exceeding...`
- `sf_get` (function) `include/secure_fetch.h:371` `* sf_get (Zero Trust): an insecure POST is not representable. Does not follow * redirects (the caller inspects...`
- `sf_response_free` (function) `include/secure_fetch.h:382` `void sf_response_free(sf_response *resp);` -- Performs an HTTPS POST under the given policy, sending body (body_len bytes) with the given Content-Type.
- `exhausted` (function) `include/secure_fetch.h:393` `* is exhausted (*next untouched). `allowlisted` enables the sovereignty rung. */ int sf_fallback_policy(sf_status...`
- `sf_rcache_put` (function) `include/secure_fetch.h:406` `int sf_rcache_put(const char *from, const char *to, time_t now);` -- Permanent-redirect memory: a 301/308 seen by sf_get_follow is remembered in RAM only (never on disk) for a day, so...
- `sf_rcache_get` (function) `include/secure_fetch.h:407` `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap);`
- `sf_rcache_clear` (function) `include/secure_fetch.h:408` `void sf_rcache_clear(void);` -- Permanent-redirect memory: a 301/308 seen by sf_get_follow is remembered in RAM only (never on disk) for a day, so...
- `sf_rcache_set_backing` (function) `include/secure_fetch.h:417` `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx);`

## include/sha2.h
Imported by: `src/js_env.c`, `src/sha2.c`, `tests/test_sha2.c`
- `sha_digest_len` (function) `include/sha2.h:21` `size_t sha_digest_len(sha_alg alg);` -- sha2 -- one-shot SHA-1 / SHA-256 / SHA-384 / SHA-512 (FIPS 180-4), pure and allocation-free.
- `sha_alg_from_name` (function) `include/sha2.h:24` `int sha_alg_from_name(const char *name, sha_alg *out);` -- sha2 -- one-shot SHA-1 / SHA-256 / SHA-384 / SHA-512 (FIPS 180-4), pure and allocation-free.
- `sha_digest` (function) `include/sha2.h:28` `int sha_digest(sha_alg alg, const void *data, size_t len, uint8_t *out);` -- Hashes data[0..len) into out (>= sha_digest_len(alg) bytes).

## include/sheet_cache.h
Depends on: `include/css.h`
Imported by: `src/page_view.c`, `src/sheet_cache.c`, `src/tab.c`, `tests/test_page_view.c`, `tests/test_sheet_cache.c`
- `shc_new` (function) `include/sheet_cache.h:52` `shc_cache *shc_new(size_t max_text_bytes);` -- max_text_bytes: texts longer than this are parsed but never retained; 0 selects * FC_SHC_MAX_TEXT_BYTES.
- `shc_free` (function) `include/sheet_cache.h:55` `void shc_free(shc_cache *c);` -- max_text_bytes: texts longer than this are parsed but never retained; 0 selects * FC_SHC_MAX_TEXT_BYTES.
- `shc_acquire` (function) `include/sheet_cache.h:60` `shc_sheet *shc_acquire(shc_cache *cache, const shc_key *key);` -- The parsed sheet for *key: the retained one when every input matches, a fresh parse otherwise. cache == NULL parses...
- `shc_css` (function) `include/sheet_cache.h:64` `const css_sheet *shc_css(const shc_sheet *s);` -- The read-only sheet behind a handle; NULL when the parse itself failed (the css * module treats a NULL sheet as...
- `shc_release` (function) `include/sheet_cache.h:67` `void shc_release(shc_sheet *s);` -- The read-only sheet behind a handle; NULL when the parse itself failed (the css * module treats a NULL sheet as...
- `shc_stats_get` (function) `include/sheet_cache.h:70` `void shc_stats_get(const shc_cache *c, shc_stats *out);` -- The read-only sheet behind a handle; NULL when the parse itself failed (the css * module treats a NULL sheet as...

## include/shm_slots.h
Imported by: `gui/browser_ui.c`, `tests/test_shm_slots.c`
- `ss_init` (function) `include/shm_slots.h:24` `static inline void ss_init(ss_state *s)`
- `ss_committed` (function) `include/shm_slots.h:41` `static inline void ss_committed(ss_state *s, int i)` -- Chooses the slot to paint into: the current one if free, else the other free one.
- `ss_released` (function) `include/shm_slots.h:49` `static inline int ss_released(ss_state *s, int i)` -- if (!s->busy[i]) { s->back = i; return i; } } return -1; } /* The painted slot was attached and committed. static...

## include/subreq_batch.h
Imported by: `src/subreq_batch.c`, `src/tab.c`, `tests/test_subreq_batch.c`
- `sqb_new` (function) `include/subreq_batch.h:37` `sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx);`
- `sqb_submit` (function) `include/subreq_batch.h:41` `int sqb_submit(sqb *b, int refused, const sqb_req *req);` -- Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result count always equals...
- `sqb_count` (function) `include/subreq_batch.h:42` `size_t sqb_count(const sqb *b);`
- `sqb_wait_all` (function) `include/subreq_batch.h:44` `void sqb_wait_all(sqb *b);` -- Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result count always equals...
- `sqb_result` (function) `include/subreq_batch.h:46` `const sqb_res *sqb_result(const sqb *b, size_t i);` -- Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result count always equals...
- `sqb_reset` (function) `include/subreq_batch.h:48` `void sqb_reset(sqb *b);` -- Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result count always equals...
- `sqb_free` (function) `include/subreq_batch.h:49` `void sqb_free(sqb *b);`

## include/svg_paint.h
Depends on: `include/svg_render.h`
Imported by: `gui/browser_ui.c`, `src/svg_paint.c`, `src/svg_raster.c`
- `svp_draw` (function) `include/svg_paint.h:31` `void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, double h, int current_rgb);` -- Paints `img` into the rect [x, y, w, h] of `cr`, scaled uniformly and centred ("xMidYMid meet"). current_rgb is the...
- `way` (function) `include/svg_paint.h:35` `* worker rasterizes SVG images this way (spec/svg_raster.md section 3): drawing text * would open fontconfig, i.e....`

## include/svg_raster.h
Depends on: `include/image_decode.h`
Imported by: `src/svg_raster.c`, `src/tab.c`, `tests/test_svg_raster.c`
- `sr_sniff` (function) `include/svg_raster.h:29` `int sr_sniff(const uint8_t *bytes, size_t len);` -- 1 when the first element of the document (after BOM, whitespace, the XML * declaration, comments and a doctype) is...

## include/svg_render.h
Imported by: `gui/browser_ui.c`, `include/svg_paint.h`, `src/page_view.c`, `src/svg_raster.c`, `src/svg_render.c`, `tests/test_svg_render.c`
- `sv_fit` (function) `include/svg_render.h:131` `void sv_fit(const sv_image *img, double dw, double dh, double *scale, double *off_x, double *off_y);` -- Maps the image's user space onto the destination rect [dx, dy, dw, dh] the way a `preserveAspectRatio="xMidYMid...

## include/tab.h
Depends on: `include/freebug.h`, `include/js_geom.h`, `include/page_view.h`
Imported by: `gui/browser_ui.c`, `include/frame_host.h`, `src/freedom.c`, `src/tab.c`, `tests/test_frame_host.c`, `tests/test_tab.c`
- `tab_worker_dispatch` (function) `include/tab.h:161` `* Call tab_worker_dispatch(argc, argv) as the FIRST thing in main(): if argv is the * internal "--tab-worker <rfd>...`
- `tab_open` (function) `include/tab.h:165` `* and reaches tab_open (the app and the test harness) must call this first. */ void tab_worker_dispatch(int argc...`
- `tab_parse_worker_args` (function) `include/tab.h:172` `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd);` -- Pure validator of the worker handoff arguments (the security-relevant surface of the exec): returns nonzero and...
- `tab_prewarm` (function) `include/tab.h:181` `void tab_prewarm(void);` -- Starts one idle, confined worker in advance so the next tab_open does not wait for fork + exec + sandbox setup...
- `tab_prewarmed` (function) `include/tab.h:184` `int tab_prewarmed(void);` -- Starts one idle, confined worker in advance so the next tab_open does not wait for fork + exec + sandbox setup...
- `tab_prewarmed_pid` (function) `include/tab.h:187` `int tab_prewarmed_pid(void);` -- Starts one idle, confined worker in advance so the next tab_open does not wait for fork + exec + sandbox setup...
- `tab_shutdown_spare` (function) `include/tab.h:190` `void tab_shutdown_spare(void);` -- Starts one idle, confined worker in advance so the next tab_open does not wait for fork + exec + sandbox setup...
- `out_status` (function) `include/tab.h:198` `* On success return 0 and set *out_status (HTTP status), *out_body / *out_body_len * (malloc'd response bytes, tab...`
- `tab_set_fetcher` (function) `include/tab.h:209` `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx);` -- Installs the subresource fetcher used for XHR/fetch (NULL clears it: requests are then * refused). fn/ctx must...
- `tab_inflight_request_headers` (function) `include/tab.h:214` `const char *tab_inflight_request_headers(void);` -- Inside a tab_fetch_fn call: the request headers the page attached to this XHR/fetch, already filtered by...
- `tab_report_response_headers` (function) `include/tab.h:219` `void tab_report_response_headers(const char *lines);` -- Inside a tab_fetch_fn call: reports the response header lines ("name: value\n", no Set-Cookie) the page's XHR/fetch...
- `bytes` (function) `include/tab.h:223` `* so the parent can retain the bytes (spec/webfont.md b3b feeds them to the * @font-face loader as extern sheets)....`
- `tab_set_css_sink` (function) `include/tab.h:232` `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx);`
- `tab_set_net_allowed` (function) `include/tab.h:237` `void tab_set_net_allowed(tab *t, int allowed);` -- Grants/revokes page-JS network access (XMLHttpRequest/fetch) for the NEXT load.
- `none` (function) `include/tab.h:241` `* worker sent carries none (tab_page.unchanged) -- on a live page that is almost every tick. * The caller must then...`
- `tab_page_keep_view` (function) `include/tab.h:248` `void tab_page_keep_view(tab_page *prev, tab_page *next);` -- For a caller that replaces its page with each tick's: when `next` is unchanged, moves the * title, text and view of...
- `tab_set_op_net_budget_ms` (function) `include/tab.h:252` `void tab_set_op_net_budget_ms(tab *t, int ms);` -- Per-operation network time budget in ms for requests the worker issues AFTER the load * (default...
- `tab_async_fd` (function) `include/tab.h:257` `* the completion is signalled on tab_async_fd (readable). The pipe to the worker is a single * channel, so EVERY...`
- `tab_async_busy` (function) `include/tab.h:263` `int tab_async_busy(const tab *t);`
- `jar` (function) `include/tab.h:270` `* the trusted parent read from its ephemeral network jar (sf_cookie_header_for). Only * meaningful for a trusted...`
- `tab_set_cookies` (function) `include/tab.h:274` `void tab_set_cookies(tab *t, const char *cookies);` -- Seeds the page's document.cookie jar for the NEXT load with cookies ("name=value; ...") the trusted parent read from...
- `origin` (function) `include/tab.h:277` `* page origin (web_storage snapshot, copied). Used only when the load is trusted * (net granted);`
- `tab_set_storage` (function) `include/tab.h:279` `void tab_set_storage(tab *t, const char *blob, size_t len);` -- Seeds localStorage for the next load from the parent's in-memory store for the page origin (web_storage snapshot...
- `exclusively` (function) `include/tab.h:285` `* exclusively (tab_subreq_permitted). Default 0: zero fetches, Privacy by Default. */ void tab_set_css_allowed(tab...`
- `tab_set_viewport_w` (function) `include/tab.h:293` `void tab_set_viewport_w(tab *t, int px);` -- Sets the render viewport width (px) used to evaluate @media width queries on the NEXT load, so a responsive page...
- `load` (function) `include/tab.h:297` `* trusted load (net granted). */ void tab_set_frame_id(tab *t, int id);`
- `tab_set_identity` (function) `include/tab.h:303` `void tab_set_identity(tab *t, const char *serialized);` -- The user's identity override (idn_serialize text, spec/identity.md) for the NEXT loads: the worker applies it to...
- `tab_last_subreq_stats` (function) `include/tab.h:309` `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us);` -- Subresources the parent served for the LAST load (the worker's TAG_SUBREQ: XHR, fetch, external scripts, ES...
- `tab_subreq_permitted` (function) `include/tab.h:314` `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method);` -- Pure parent-side subresource gate (Zero Trust: decided from the PARENT's grants for this load, never the worker's...
- `view` (function) `include/tab.h:322` `* <noscript> handling in the built view (off => fallback shown, on => suppressed) * and is where allowlisted...`
- `string` (function) `include/tab.h:342` `* event_type is a JS event type string (e.g. "keydown", "input", "change"). * key is the keyboard key value (may be...`
- `granted` (function) `include/tab.h:391` `* granted (allow.conf AND js.conf);`
- `returned` (function) `include/tab.h:392` `* returned (the page keeps its zeros). The worker re-checks the same condition. * g must be finished (jg_finish). */...`
- `popstate` (function) `include/tab.h:398` `* popstate (+ hashchange) and re-derives the view like a click. */ tab_status tab_popstate(tab *t, int index...`
- `decode` (function) `include/tab.h:417` `* could not decode (caller shows the placeholder), which is not a transport error. * TAB_ERR_* is reserved for...`
- `tab_alive` (function) `include/tab.h:430` `int tab_alive(const tab *t);` -- Same contract as tab_decode_image, for an inline data: URI image (RFC 2397 base64 variant): data_url slices the...
- `tab_child_pid` (function) `include/tab.h:433` `pid_t tab_child_pid(const tab *t);` -- Same contract as tab_decode_image, for an inline data: URI image (RFC 2397 base64 variant): data_url slices the...
- `tab_close` (function) `include/tab.h:436` `void tab_close(tab *t);` -- variant): data_url slices the base64 payload out of `data_url` (no allocation, no network -- the bytes are already...
- `tab_page_free` (function) `include/tab.h:439` `void tab_page_free(tab_page *p);` -- malformed data: URI is not a transport error: *out stays zeroed, same as an * undecodable format, and the caller...
- `tab_eval_result_free` (function) `include/tab.h:440` `void tab_eval_result_free(tab_eval_result *r);`
- `tab_image_free` (function) `include/tab.h:441` `void tab_image_free(tab_image *img);`

## include/text_case.h
Imported by: `gui/browser_ui.c`, `src/text_case.c`, `tests/test_text_case.c`
- `cp` (function) `include/text_case.h:19` `* cp (identity otherwise), so a transformed text keeps its length. */ uint32_t tc_upper(uint32_t cp);`
- `tc_lower` (function) `include/text_case.h:21` `uint32_t tc_lower(uint32_t cp);`
- `tc_is_lower` (function) `include/text_case.h:24` `int tc_is_lower(uint32_t cp);` -- Simple 1:1 case mapping for ASCII, Latin-1, Latin Extended-A, basic Greek and basic Cyrillic.
- `tc_transform` (function) `include/text_case.h:29` `size_t tc_transform(const char *s, size_t n, int transform, int word_start, char *out, size_t cap);` -- Copies s[0,n) to out applying transform (CSS_TT_UPPERCASE / _LOWERCASE / _CAPITALIZE; any other value copies...
- `tc_smallcaps_runs` (function) `include/text_case.h:41` `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap);` -- Splits s[0,n) into consecutive maximal runs of lowercase letters vs the rest, covering the whole text in order.

## include/text_shape.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/text_shape.c`, `src/webfont_load.c`, `tests/test_text_shape.c`, `tests/test_webfont_load.c`
- `content` (function) `include/text_shape.h:11` `* TEXT is hostile remote content (sanitised UTF-8) and is fuzzed (make fuzz-tsh);`
- `tsh_family_is_generic` (function) `include/text_shape.h:52` `int tsh_family_is_generic(const char *name);` -- 1 for a CSS generic family keyword (serif, sans-serif, monospace, cursive, * fantasy, system-ui, ui-*, emoji, math...
- `wins` (function) `include/text_shape.h:58` `* the first name the resolver accepts wins (returns 1, family in out). Pure: the * resolver is injected (fontconfig...`
- `tsh_pick_family` (function) `include/text_shape.h:68` `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong, size_t n, int...` -- The acceptance rule for one requested name given fontconfig's substituted family list subs[0..n) and their bindings...
- `tsh_local_handle` (function) `include/text_shape.h:75` `int tsh_local_handle(const char *list);` -- Handle (>0) for an author family list that resolves to a local family, cached per list; 0 when nothing resolves, the...
- `tsh_ready` (function) `include/text_shape.h:89` `int tsh_ready(void);` -- 1 once a fallback (sans) font resolves; lazily initialises on first call. * 0 means no font backend: the caller must...
- `origin` (function) `include/text_shape.h:92` `* glyphs are written with positions relative to origin (0,0) on the baseline, * and *out_adv holds the total pen...`
- `tsh_measure` (function) `include/text_shape.h:101` `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len);` -- Total advance (px) of [text,len).
- `tsh_webfont_register` (function) `include/text_shape.h:114` `int tsh_webfont_register(const char *name, const unsigned char *bytes, size_t nbytes, int bold, int italic);` -- Registers one fetched @font-face for this document (spec/webfont.md): name is the author family (hashed with...
- `tsh_webfont_clear` (function) `include/text_shape.h:120` `void tsh_webfont_clear(void);` -- Drops every registered webfont (document teardown / navigation).
- `tsh_face` (function) `include/text_shape.h:127` `cairo_font_face_t *tsh_face(const tsh_font *f);` -- The cairo face tsh_draw paints f with (webfont, local family or bucket), or NULL when no face resolves.
- `own` (function) `include/text_shape.h:136` `* face of their own (controls, combining marks, variation selectors, ZWJ/ZWNJ) * stay in the run before them....`
- `tsh_shutdown` (function) `include/text_shape.h:143` `void tsh_shutdown(void);` -- Splits [text,len) into maximal runs of one face.

## include/textfield.h
Imported by: `gui/browser_ui.c`, `src/textfield.c`, `tests/test_textfield.c`
- `tf_init` (function) `include/textfield.h:38` `void tf_init(tf_field *f);` -- typedef struct tf_field { char   buf[TF_CAP]; /* content, always NUL-terminated at [len] size_t len;         /*...
- `tf_clear` (function) `include/textfield.h:45` `void tf_clear(tf_field *f);` -- Replaces the whole content and places the cursor at the end. s == NULL => * TF_ERR_NULL_ARG. strlen(s) >= TF_CAP =>...
- `tf_backspace` (function) `include/textfield.h:53` `void tf_backspace(tf_field *f);` -- Inserts one byte at the cursor, shifting the tail right; the cursor advances by one.
- `tf_delete` (function) `include/textfield.h:56` `void tf_delete(tf_field *f);` -- Inserts one byte at the cursor, shifting the tail right; the cursor advances by one.
- `tf_move` (function) `include/textfield.h:59` `void tf_move(tf_field *f, long delta);` -- Inserts one byte at the cursor, shifting the tail right; the cursor advances by one.
- `tf_home` (function) `include/textfield.h:62` `void tf_home(tf_field *f);` -- one.
- `tf_end` (function) `include/textfield.h:63` `void tf_end(tf_field *f);`
- `tf_text` (function) `include/textfield.h:66` `const char *tf_text(const tf_field *f);` -- /* Deletes the byte before the cursor (no-op at the start).
- `tf_len` (function) `include/textfield.h:67` `size_t tf_len(const tf_field *f);`
- `tf_cursor` (function) `include/textfield.h:68` `size_t tf_cursor(const tf_field *f);`

## include/tls_impersonate.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/tls_impersonate.c`, `tests/test_tls_impersonate.c`
- `path` (function) `include/tls_impersonate.h:26` `* Zero Knowledge path (PQ-hybrid, VERIFYPEER). * * 2. ti_encode_x / ti_decode_x — the length-prefixed, fail-closed...`
- `chain` (function) `include/tls_impersonate.h:32` `* * The response carries the peer certificate chain (DER) and the negotiated group so * the TRUSTED PARENT...`
- `ti_should_impersonate` (function) `include/tls_impersonate.h:56` `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled, int user_opt_in);` -- The double opt-in + user-flag gate (pure).
- `success` (function) `include/tls_impersonate.h:97` `* ti_decode_* returns 0 on success (out fully populated), <0 on any malformed, * truncated or over-cap input (out...`
- `ti_decode_req` (function) `include/tls_impersonate.h:101` `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out);`
- `ti_req_free` (function) `include/tls_impersonate.h:102` `void ti_req_free(ti_req *r);`
- `ti_encode_resp` (function) `include/tls_impersonate.h:104` `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap);`
- `ti_decode_resp` (function) `include/tls_impersonate.h:105` `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out);`
- `ti_resp_free` (function) `include/tls_impersonate.h:106` `void ti_resp_free(ti_resp *r);`

## include/ui.h
Depends on: `include/prefs.h`
Imported by: `gui/browser_ui.c`, `gui/freedom_view.c`, `gui/ui_render.c`, `src/freedom.c`, `src/ui_layout.c`, `tests/test_ui.c`
- `space` (function) `include/ui.h:44` `* Breaks at the last fitting space (the break space is consumed), hard-breaks * words longer than max_cols, and...`
- `ui_layout_free` (function) `include/ui.h:52` `void ui_layout_free(ui_layout *lay);` -- Word-wraps text into lines of at most max_cols columns (monospace model).
- `ui_clamp_scroll` (function) `include/ui.h:55` `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines);` -- Word-wraps text into lines of at most max_cols columns (monospace model).
- `shortcut` (function) `include/ui.h:71` `* from a keyboard shortcut (Ctrl+Shift+E only relaxes a weak-but-valid certificate). */ void...`
- `available` (function) `include/ui.h:91` `* cheapest artifact to inspect a render where no display is available (CI, an AI * agent): export, then read the PNG...`
- `out` (function) `include/ui.h:103` `* ui_render_png does and fills *out (jg_init'ed by the caller) with one rect per * element in document coordinates...`
- `placeholders` (function) `include/ui.h:113` `* above always draw image placeholders (no worker to decode hostile bytes);`
- `disk` (function) `include/ui.h:118` `* images are read from disk (confined to the document directory by render_doc). * top_url is the page origin (https...`
- `images` (function) `include/ui.h:120` `* fetcher loads no images (placeholders, as before). Any image that fails falls back * to its placeholder...`
- `ui_render_viewport_w` (function) `include/ui.h:156` `int ui_render_viewport_w(void);` -- The fixed canvas width (px) every headless render (ui_render_png/pdf, ui_dump_layout) lays out at.
- `ui_persisted_prefs` (function) `include/ui.h:161` `int ui_persisted_prefs(prefs_state *out);` -- The GUI's persisted choices (JS mode, images/CSS toggles, reader) from the encrypted profile, so `--as-gui` shows...

## include/url.h
Imported by: `gui/browser_ui.c`, `include/form.h`, `include/js_dom.h`, `include/js_location.h`, `src/freedom.c`, `src/js_location.c`, `src/link_nav.c`, `src/prefetch.c`, `src/render_doc.c`, `src/secure_fetch.c`, `src/tab.c`, `src/url.c`, `src/webfont_load.c`, `tests/test_js_dom.c`, `tests/test_tab.c`, `tests/test_url.c`
- `url_is_https` (function) `include/url.h:42` `int url_is_https(const char *s);` -- Nonzero iff s begins (case-insensitively) with "https://" and the host is * neither empty nor a leading '/'.
- `url_has_scheme` (function) `include/url.h:46` `int url_has_scheme(const char *s);` -- Nonzero iff s begins with "<scheme>:" per RFC 3986 * (ALPHA *( ALPHA / DIGIT / "+" / "-" / "." ) ":").
- `url_authority_len` (function) `include/url.h:51` `size_t url_authority_len(const char *url);` -- Length of "https://host[:port]" within a validated absolute https URL: the index of the first '/', '?' or '#' after...
- `URL_ERR_NOT_HTTPS` (function) `include/url.h:109` `* URL_ERR_NOT_HTTPS (out untouched);`
- `path` (function) `include/url.h:115` `* absolute path ("file:///..."). NULL => 0. */ int url_is_file(const char *s);`
- `url_file_path` (function) `include/url.h:121` `const char *url_file_path(const char *s);` -- Returns the absolute filesystem path inside a "file:///path" URL (i.e. the "/path" part), or NULL when s is not a...
- `url` (function) `include/url.h:126` `* Every field ALIASES the input url (not owned, valid while url is alive);`
- `password` (function) `include/url.h:152` `* username and password (owned, must be freed) into *username_out and * *password_out, and returns URL_OK. When...`

## include/util.h
Imported by: `src/browser.c`, `src/disk_store.c`, `src/dom.c`, `src/hostblock.c`, `src/html_parse.c`, `src/media_decoder.c`, `src/page_view.c`, `src/render_doc.c`, `src/renderer.c`, `src/tab.c`
- `write_full` (function) `include/util.h:15` `static inline int write_full(int fd, const void *buf, size_t n)`
- `read_full` (function) `include/util.h:26` `static inline int read_full(int fd, void *buf, size_t n)`
- `mem_contains_ci` (function) `include/util.h:43` `static inline int mem_contains_ci(const void *hay, size_t hlen, const char *needle)` -- Returns 1 when the trusted lowercase-ASCII needle (letters/digits) occurs in the hostile, length-delimited haystack...
- `utf8_seq_len` (function) `include/util.h:57` `static inline size_t utf8_seq_len(unsigned char c)`
- `fnv1a` (function) `include/util.h:67` `static inline uint64_t fnv1a(const char *s, size_t n)`

## include/web_storage.h
Imported by: `gui/browser_ui.c`, `src/js_dom.c`, `src/js_trusted.c`, `src/tab.c`, `src/web_storage.c`, `tests/test_js_dom.c`, `tests/test_tab.c`, `tests/test_web_storage.c`
- `wst_new` (function) `include/web_storage.h:25` `wst_db *wst_new(void);` -- web_storage — in-MEMORY localStorage for trusted hosts (owner decision: nothing persists to disk).
- `wst_free` (function) `include/web_storage.h:28` `void wst_free(wst_db *db);` -- before it may touch the database.
- `wst_encode` (function) `include/web_storage.h:33` `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len);` -- Snapshot of origin's pairs ([n:u32]([klen:u32][key][vlen:u32][val])*, little-endian) into an owned *out of *len bytes.
- `wst_decode_check` (function) `include/web_storage.h:37` `int wst_decode_check(const char *blob, size_t len);` -- Pure validation of a snapshot: 0 when it is complete and well-formed (counts and * lengths fit, total <= WST_QUOTA...
- `wst_replace` (function) `include/web_storage.h:42` `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len);` -- Replaces origin's contents with the snapshot after wst_decode_check.
- `full` (function) `include/web_storage.h:45` `* validating it in full (wst_decode_check). Returns 0, or -1 when invalid (fn is then * never called). The one...`
- `wst_origin_bytes` (function) `include/web_storage.h:59` `size_t wst_origin_bytes(const wst_db *db, const char *origin);` -- Builds a snapshot from n pairs into an owned *out.

## include/webfont.h
Imported by: `gui/browser_ui.c`, `src/css.c`, `src/freedom.c`, `src/text_shape.c`, `src/webfont.c`, `src/webfont_load.c`, `tests/test_css.c`, `tests/test_page_view.c`, `tests/test_text_shape.c`, `tests/test_webfont.c`, `tests/test_webfont_load.c`
- `here` (function) `include/webfont.h:38` `* set with the decoded bytes owned here (freed by wf_list_free);`
- `wf_scan` (function) `include/webfont.h:52` `int wf_scan(const char *css, size_t len, wf_list *out);`
- `wf_list_free` (function) `include/webfont.h:53` `void wf_list_free(wf_list *l);`
- `boundaries` (function) `include/webfont.h:57` `* boundaries (scan_inline accumulation, loader collection). */ void wf_ref_move(wf_ref *dst, wf_ref *src);`
- `wf_supported_format` (function) `include/webfont.h:60` `int wf_supported_format(const char *fmt);`
- `wf_name_hash` (function) `include/webfont.h:69` `static inline unsigned wf_name_hash(const char *s, size_t n)` -- FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.

## include/webfont_load.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/webfont_load.c`, `tests/test_webfont_load.c`
- `free` (function) `include/webfont_load.h:31` `* free()), *out_status the HTTP status. Nonzero on refusal/error (fail-closed: * the face is skipped, never the...`
- `skipped` (function) `include/webfont_load.h:47` `* URLs are skipped (no base). Returns faces registered (>= 0) otherwise. */ int wf_load_document(wf_fetch_fn fetch...`

## include/wl_display.h
Imported by: `src/freedom.c`, `src/wl_display.c`, `tests/test_wl_display.c`
- `pure` (function) `include/wl_display.h:3` `* wd_pick is pure (no I/O);`
- `wd_pick` (function) `include/wl_display.h:16` `int wd_pick(const char *const *names, size_t n, char *out, size_t cap);` -- Choose the lowest-numbered "wayland-N" (N = digits only) from names[0..n).
- `wd_resolve_env` (function) `include/wl_display.h:20` `int wd_resolve_env(void);` -- If WAYLAND_DISPLAY is unset/empty, set it from the sockets found in XDG_RUNTIME_DIR. * Returns WD_OK if the variable...

## include/wl_guard.h
Imported by: `gui/browser_ui.c`, `src/wl_guard.c`, `tests/test_wl_guard.c`
- `wlg_start` (function) `include/wl_guard.h:25` `wl_guard *wlg_start(struct wl_display *display);` -- wl_guard -- keeps the Wayland connection drained while the GUI thread is busy.
- `wlg_stop` (function) `include/wl_guard.h:28` `void wlg_stop(wl_guard *g);` -- client that does not read for a few seconds while the pointer moves gets DISCONNECTED ("libwayland: Data too big for...

## include/ws_hub.h
Depends on: `include/secure_fetch.h`
Imported by: `gui/browser_ui.c`, `src/ws_hub.c`, `tests/test_ws_hub.c`
- `wh_new` (function) `include/ws_hub.h:34` `wh_hub *wh_new(void);` -- #define WH_MAX 8   /* == JD_WS_MAX: sockets per page /* Event kinds delivered to the page; values match...
- `wh_free` (function) `include/ws_hub.h:38` `void wh_free(wh_hub *h);` -- Closes every connection and frees the hub.
- `wh_notify_fd` (function) `include/ws_hub.h:41` `int wh_notify_fd(const wh_hub *h);` -- Closes every connection and frees the hub.
- `wh_open_async` (function) `include/ws_hub.h:46` `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg);` -- Starts opening url for page socket id on a thread (cfg and all its strings are copied).
- `generation` (function) `include/ws_hub.h:50` `* previous generation (before wh_close_all) are closed and dropped silently. */ void wh_on_notify(wh_hub *h...`
- `wh_send` (function) `include/ws_hub.h:54` `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary);` -- Drains finished opens: success => the connection joins the hub and WH_EV_OPEN is emitted; failure => WH_EV_ERROR...
- `wh_close` (function) `include/ws_hub.h:58` `void wh_close(wh_hub *h, int id);` -- The page closed socket id: sends a close frame and frees it (also cancels a * pending open for that id: its result...
- `wh_close_all` (function) `include/ws_hub.h:61` `void wh_close_all(wh_hub *h);` -- The page closed socket id: sends a close frame and frees it (also cancels a * pending open for that id: its result...
- `wh_poll_fds` (function) `include/ws_hub.h:65` `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap);` -- Fills up to cap pollfds (POLLIN) and the matching page ids for the open * connections.
- `wh_on_readable` (function) `include/ws_hub.h:70` `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx);` -- Reads everything pending on socket id without blocking, emitting each complete message; a close frame emits...
- `wh_count` (function) `include/ws_hub.h:73` `size_t wh_count(const wh_hub *h);` -- Reads everything pending on socket id without blocking, emitting each complete message; a close frame emits...

## include/zoom.h
Imported by: `gui/browser_ui.c`, `src/prefs.c`, `src/zoom.c`, `tests/test_prefs.c`, `tests/test_zoom.c`
- `zm_clamp` (function) `include/zoom.h:26` `int zm_clamp(int pct);` -- stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser.
- `zm_zoom_in` (function) `include/zoom.h:29` `int zm_zoom_in(int pct);` -- never escape the bounds.
- `zm_zoom_out` (function) `include/zoom.h:32` `int zm_zoom_out(int pct);` -- only calls these.
- `zm_reset` (function) `include/zoom.h:35` `int zm_reset(void);` -- #define ZM_MIN_PCT     50 #define ZM_MAX_PCT     300 #define ZM_DEFAULT_PCT 100 /* Clamp pct to [ZM_MIN_PCT...
- `zm_scale` (function) `include/zoom.h:38` `double zm_scale(int pct);` -- /* Clamp pct to [ZM_MIN_PCT, ZM_MAX_PCT]. int zm_clamp(int pct); /* Smallest ladder stop strictly greater than...
- `zm_apply` (function) `include/zoom.h:42` `double zm_apply(double base_px, int pct);` -- base_px * zm_scale(pct), floored to 1.0 when base_px > 0 so a font can never * scale away to nothing. base_px <= 0...

## src/anti_fp.c
Depends on: `include/anti_fp.h`
- `fp_coarsen_time_ms` (function) `src/anti_fp.c:17` `uint64_t fp_coarsen_time_ms(uint64_t raw_ms)`
- `fp_user_agent` (function) `src/anti_fp.c:23` `const char *fp_user_agent(void)`
- `fp_accept_language` (function) `src/anti_fp.c:27` `const char *fp_accept_language(void)`
- `fp_accept_language_header` (function) `src/anti_fp.c:31` `const char *fp_accept_language_header(void)`
- `fp_timezone` (function) `src/anti_fp.c:35` `const char *fp_timezone(void)`
- `fp_platform` (function) `src/anti_fp.c:39` `const char *fp_platform(void)`
- `fp_vendor` (function) `src/anti_fp.c:43` `const char *fp_vendor(void)`
- `fp_hardware_concurrency` (function) `src/anti_fp.c:47` `int fp_hardware_concurrency(void)`
- `fp_device_memory_gb` (function) `src/anti_fp.c:51` `int fp_device_memory_gb(void)`
- `fp_app_version` (function) `src/anti_fp.c:57` `const char *fp_app_version(void)`
- `fp_app_code_name` (function) `src/anti_fp.c:61` `const char *fp_app_code_name(void)`
- `fp_product` (function) `src/anti_fp.c:65` `const char *fp_product(void)`
- `fp_app_name` (function) `src/anti_fp.c:69` `const char *fp_app_name(void)`
- `fp_product_sub` (function) `src/anti_fp.c:73` `const char *fp_product_sub(void)`
- `fp_oscpu` (function) `src/anti_fp.c:77` `const char *fp_oscpu(void)`
- `fp_build_id` (function) `src/anti_fp.c:81` `const char *fp_build_id(void)`
- `fp_max_touch_points` (function) `src/anti_fp.c:85` `int fp_max_touch_points(void)`
- `fp_on_line` (function) `src/anti_fp.c:89` `int fp_on_line(void)`
- `fp_cookie_enabled` (function) `src/anti_fp.c:93` `int fp_cookie_enabled(void)`
- `fp_bucket_screen` (function) `src/anti_fp.c:99` `void fp_bucket_screen(int w, int h, int *out_w, int *out_h)`
- `splitmix64` (function) `src/anti_fp.c:121` `static uint64_t splitmix64(uint64_t *state)`
- `fp_perturb` (function) `src/anti_fp.c:128` `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key)`
- `fp_origin_key` (function) `src/anti_fp.c:139` `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain)`

## src/block_flow.c
Depends on: `include/block_flow.h`
- `finite_or_zero` (function) `src/block_flow.c:11` `static double finite_or_zero(double v)` -- A margin the caller could not compute (NaN from a hostile calc(), an infinity from an overflowing unit conversion)...
- `bf_collapse_n` (function) `src/block_flow.c:15` `double bf_collapse_n(const double *m, size_t n)`
- `bf_collapse` (function) `src/block_flow.c:30` `double bf_collapse(double a, double b)`
- `bf_margins_adjoin` (function) `src/block_flow.c:35` `int bf_margins_adjoin(double border_px, double padding_px)`

## src/box_blur.c
Depends on: `include/box_blur.h`
- `bb_box_sizes` (function) `src/box_blur.c:7` `int bb_box_sizes(double sigma, int sizes[3])`
- `variance` (function) `src/box_blur.c:10` `* width w has variance (w^2 - 1) / 12): the ideal common width, rounded down * to an odd wl and up to wu = wl + 2...`
- `box_line` (function) `src/box_blur.c:28` `static void box_line(unsigned char *p, int n, int step, int bw, unsigned char *tmp)` -- One box pass of odd width bw over n samples spaced `step` apart, through tmp * (n bytes).
- `bb_blur_a8` (function) `src/box_blur.c:41` `int bb_blur_a8(unsigned char *buf, int w, int h, int stride, double sigma)`
- `bb_ink_rect` (function) `src/box_blur.c:57` `int bb_ink_rect(const unsigned char *argb, int w, int h, int stride, double sigma, int rect[4])`


Next: [API_p6.md](API_p6.md)
