# Symbols (page 5 of 18)
Previous: [SYMBOLS_p4.md](SYMBOLS_p4.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `tor_enabled` | type_alias | `include/net_realm.h:41` | `typedef struct nr_config { int tor_enabled;` |
| `FREEDOM_OS_SANDBOX_H` | macro | `include/os_sandbox.h:2` | `#define FREEDOM_OS_SANDBOX_H` |
| `denied` | function | `include/os_sandbox.h:59` | `* request PROT_EXEC are denied (see os_prot_allowed). * Returns OS_ERR_UNSUPPORTED on platforms without seccomp-bpf...` |
| `flags` | function | `include/os_sandbox.h:39` | `* permission also depends on the protection flags (see os_prot_allowed / W^X). */ int os_policy_allows(long syscall_nr);` |
| `namespace` | function | `include/os_sandbox.h:75` | `* namespace (the unprivileged enabler), network (the worker never needs the * network -- the parent fetches and...` |
| `os_fs_access` | enum | `include/os_sandbox.h:102` | `` |
| `os_fs_rule` | struct | `include/os_sandbox.h:108` | `` |
| `os_landlock_abi` | function | `include/os_sandbox.h:114` | `int os_landlock_abi(void);` |
| `os_namespace_flags` | function | `include/os_sandbox.h:81` | `int os_namespace_flags(void);` |
| `os_policy_size` | function | `include/os_sandbox.h:43` | `size_t os_policy_size(void);` |
| `os_prot_allowed` | function | `include/os_sandbox.h:52` | `int os_prot_allowed(long syscall_nr, unsigned long prot);` |
| `os_status` | enum | `include/os_sandbox.h:21` | `` |
| `os_violation` | enum | `include/os_sandbox.h:30` | `` |
| `CSS_LEN_UNSET` | function | `include/page_view.h:570` | `* CSS_LEN_UNSET (unset) / CSS_LEN_AUTO. z_index is signed, or CSS_LEN_UNSET. v1 * paints only position:relative (an...` |
| `FREEDOM_PAGE_VIEW_H` | macro | `include/page_view.h:2` | `#define FREEDOM_PAGE_VIEW_H` |
| `PV_BG_URL_MAX` | macro | `include/page_view.h:78` | `#define PV_BG_URL_MAX` |
| `PV_BR_ATOM_SPACE` | macro | `include/page_view.h:1276` | `#define PV_BR_ATOM_SPACE` |
| `PV_BR_CONT` | macro | `include/page_view.h:1272` | `#define PV_BR_CONT` |
| `PV_BR_EMPTY` | macro | `include/page_view.h:1271` | `#define PV_BR_EMPTY` |
| `PV_BSHADOW_LAYERS` | macro | `include/page_view.h:44` | `#define PV_BSHADOW_LAYERS` |
| `PV_CONT_DEPTH` | macro | `include/page_view.h:72` | `#define PV_CONT_DEPTH` |
| `PV_CQ_MAX` | macro | `include/page_view.h:942` | `#define PV_CQ_MAX` |
| `PV_FRAME_SCHEME` | macro | `include/page_view.h:1334` | `#define PV_FRAME_SCHEME` |
| `PV_GAP_WORD_SPACE` | macro | `include/page_view.h:808` | `#define PV_GAP_WORD_SPACE` |
| `PV_GRID_TRACKS` | macro | `include/page_view.h:58` | `#define PV_GRID_TRACKS` |
| `PV_LEN_AUTO` | macro | `include/page_view.h:54` | `#define PV_LEN_AUTO` |
| `PV_LEN_END` | macro | `include/page_view.h:55` | `#define PV_LEN_END` |
| `PV_LEN_UNSET` | macro | `include/page_view.h:53` | `#define PV_LEN_UNSET` |
| `PV_MASK_GEO_N` | macro | `include/page_view.h:79` | `#define PV_MASK_GEO_N` |
| `PV_MAUTO_BOTTOM` | macro | `include/page_view.h:49` | `#define PV_MAUTO_BOTTOM` |
| `PV_MAUTO_LEFT` | macro | `include/page_view.h:46` | `#define PV_MAUTO_LEFT` |
| `PV_MAUTO_RIGHT` | macro | `include/page_view.h:47` | `#define PV_MAUTO_RIGHT` |
| `PV_MAUTO_TOP` | macro | `include/page_view.h:48` | `#define PV_MAUTO_TOP` |
| `PV_MAX_CONTAINERS` | macro | `include/page_view.h:65` | `#define PV_MAX_CONTAINERS` |
| `PV_MAX_FLOATS` | macro | `include/page_view.h:67` | `#define PV_MAX_FLOATS` |
| `PV_PH_HIDDEN` | macro | `include/page_view.h:1302` | `#define PV_PH_HIDDEN` |
| `PV_PH_THEME` | macro | `include/page_view.h:1301` | `#define PV_PH_THEME` |
| `PV_UA_BODY_MARGIN` | macro | `include/page_view.h:881` | `#define PV_UA_BODY_MARGIN` |
| `ancestors` | function | `include/page_view.h:1147` | `* itself by walking its ancestors (css_visibility, 0 = unset). * * An explicit value on the run WINS over the box...` |
| `bx_display` | function | `include/page_view.h:243` | `* bx_display (flex/grid);` |
| `cause` | function | `include/page_view.h:998` | `* cause (spec/css_drops.md). Builds no view and changes nothing -- it exists so * "what is this page's CSS losing?"...` |
| `container` | function | `include/page_view.h:242` | `* cont_id groups runs of one container (-1 = none);` |
| `declare` | function | `include/page_view.h:884` | `* margin the author did not declare (px or %), 0 on a declared side (the body's * own box, or nothing for 0, owns...` |
| `default` | function | `include/page_view.h:1066` | `* structure is carried by default (not gated by caps.css). */ void pv_set_indent(pv_view *v, int indent);` |
| `form` | function | `include/page_view.h:1029` | `* form (-1 if none);` |
| `itself` | function | `include/page_view.h:371` | `* by itself (bx_width_cap2);` |
| `kind` | type_alias | `include/page_view.h:131` | `typedef struct pv_run { pv_kind kind;` |
| `nonzero` | function | `include/page_view.h:896` | `* when nonzero (JS allowed for this page) the <noscript> subtree is suppressed. */ pv_status pv_build_ex(const...` |
| `order` | function | `include/page_view.h:307` | `* groups the runs of ONE floated element in document order (-1 = not in a float);` |
| `parent_id` | type_alias | `include/page_view.h:472` | `typedef struct pv_box_def { int parent_id;` |
| `parent_id` | type_alias | `include/page_view.h:809` | `typedef struct pv_cont_def { int parent_id;` |
| `policy` | function | `include/page_view.h:911` | `* TRUSTED parent under full network policy (spec/tab.md §8) -- page_view stays * pure and never fetches. The...` |
| `pv_at` | function | `include/page_view.h:1324` | `const pv_run *pv_at(const pv_view *v, size_t i);` |
| `pv_box_at` | function | `include/page_view.h:1329` | `const pv_box_def *pv_box_at(const pv_view *v, size_t i);` |
| `pv_box_count` | function | `include/page_view.h:1328` | `size_t pv_box_count(const pv_view *v);` |
| `pv_box_def` | struct | `include/page_view.h:472` | `` |
| `pv_computed` | type_alias | `include/page_view.h:979` | `typedef struct pv_computed pv_computed;` |
| `pv_computed_free` | function | `include/page_view.h:994` | `void pv_computed_free(pv_computed *pc);` |
| `pv_computed_get` | function | `include/page_view.h:991` | `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st, double *font_px, int *inherited_color);` |
| `pv_computed_new` | function | `include/page_view.h:980` | `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css, size_t extern_len...` |
| `pv_computed_new_cached` | function | `include/page_view.h:983` | `pv_computed *pv_computed_new_cached(const hp_document *doc, int prefers_dark, const char *extern_css, size_t...` |
| `pv_cont_at` | function | `include/page_view.h:1296` | `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i);` |
| `pv_cont_count` | function | `include/page_view.h:1295` | `size_t pv_cont_count(const pv_view *v);` |
| `pv_cont_def` | struct | `include/page_view.h:810` | `` |
| `pv_count` | function | `include/page_view.h:1323` | `size_t pv_count(const pv_view *v);` |
| `pv_cq_src` | struct | `include/page_view.h:943` | `` |
| `pv_form_method` | enum | `include/page_view.h:117` | `` |
| `pv_free` | function | `include/page_view.h:1320` | `void pv_free(pv_view *v);` |
| `pv_input_type` | enum | `include/page_view.h:97` | `` |
| `pv_kind` | enum | `include/page_view.h:81` | `` |
| `pv_new` | function | `include/page_view.h:1010` | `pv_view *pv_new(void);` |
| `pv_node_ids` | struct | `include/page_view.h:963` | `` |
| `pv_placeholder_color` | function | `include/page_view.h:1313` | `int pv_placeholder_color(const css_style *ph);` |
| `pv_run` | struct | `include/page_view.h:131` | `` |
| `pv_set_bgcolor` | function | `include/page_view.h:1076` | `void pv_set_bgcolor(pv_view *v, int bg_rgb);` |
| `pv_set_block_id` | function | `include/page_view.h:1254` | `void pv_set_block_id(pv_view *v, int block_id);` |
| `pv_set_block_node` | function | `include/page_view.h:1268` | `void pv_set_block_node(pv_view *v, dom_node_id id);` |
| `pv_set_box` | function | `include/page_view.h:1233` | `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w, int box_center, int box_mt, int box_mb);` |
| `pv_set_box_maxw` | function | `include/page_view.h:1244` | `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct);` |
| `pv_set_box_pct` | function | `include/page_view.h:1239` | `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct, int box_mt_pct, int box_mb_pct);` |
| `pv_set_br_line` | function | `include/page_view.h:1280` | `void pv_set_br_line(pv_view *v, int br_line);` |
| `pv_set_color` | function | `include/page_view.h:1069` | `void pv_set_color(pv_view *v, int fg_rgb);` |
| `pv_set_cont_box` | function | `include/page_view.h:1193` | `void pv_set_cont_box(pv_view *v, int cont_box_id);` |
| `pv_set_cont_item` | function | `include/page_view.h:1209` | `void pv_set_cont_item(pv_view *v, int cont_item);` |
| `pv_set_emphasis` | function | `include/page_view.h:1061` | `void pv_set_emphasis(pv_view *v, int bold, int italic);` |
| `pv_set_flex` | function | `include/page_view.h:1202` | `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis, int flex_order, int flex_direction, int...` |
| `pv_set_flex_mauto` | function | `include/page_view.h:1205` | `void pv_set_flex_mauto(pv_view *v, int mauto);` |
| `pv_set_float` | function | `include/page_view.h:1223` | `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear, int float_ml, int float_ml_pct, int...` |
| `pv_set_float_w` | function | `include/page_view.h:1220` | `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box, int float_ow, int float_ow_pct, int...` |
| `pv_set_grad_text` | function | `include/page_view.h:1163` | `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4);` |
| `pv_set_grid` | function | `include/page_view.h:1194` | `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span);` |
| `pv_set_grid_area` | function | `include/page_view.h:1183` | `void pv_set_grid_area(pv_view *v, int row_start, int col_start);` |
| `pv_set_grid_rows` | function | `include/page_view.h:1184` | `void pv_set_grid_rows(pv_view *v, int grid_rows);` |
| `pv_set_input_checked` | function | `include/page_view.h:1300` | `void pv_set_input_checked(pv_view *v, int checked);` |
| `pv_set_input_placeholder` | function | `include/page_view.h:1304` | `void pv_set_input_placeholder(pv_view *v, int ph_color);` |
| `pv_set_input_select_opts` | function | `include/page_view.h:1317` | `void pv_set_input_select_opts(pv_view *v, const char *select_opts);` |
| `pv_set_justify_self` | function | `include/page_view.h:1265` | `void pv_set_justify_self(pv_view *v, int justify_self);` |
| `pv_set_node_id` | function | `include/page_view.h:1249` | `void pv_set_node_id(pv_view *v, dom_node_id node_id);` |
| `pv_set_oof` | function | `include/page_view.h:1262` | `void pv_set_oof(pv_view *v, int oof);` |
| `pv_set_own_box` | function | `include/page_view.h:1258` | `void pv_set_own_box(pv_view *v, int box_id);` |
| `pv_set_row_span` | function | `include/page_view.h:1179` | `void pv_set_row_span(pv_view *v, int row_span);` |
| `pv_set_text_ext` | function | `include/page_view.h:1157` | `void pv_set_text_ext(pv_view *v, const pv_text_ext *e);` |
| `pv_set_text_style` | function | `include/page_view.h:1085` | `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs, int line_scale, int text_decoration);` |
| `pv_set_ua_tag` | function | `include/page_view.h:1189` | `void pv_set_ua_tag(pv_view *v, int ua_tag);` |
| `pv_status` | enum | `include/page_view.h:34` | `` |
| `pv_svg_append_root_attrs` | function | `include/page_view.h:1310` | `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs, size_t *out_len);` |
| `pv_text_ext` | struct | `include/page_view.h:1101` | `` |
| `pv_text_ext_reset` | function | `include/page_view.h:1142` | `void pv_text_ext_reset(pv_text_ext *e);` |
| `pv_view` | struct | `include/page_view.h:860` | `` |
| `resolved` | function | `include/page_view.h:903` | `* author CSS is still resolved (the presentation layer decides whether to apply it). * pv_build_ex is pv_build_full...` |
| `run` | function | `include/page_view.h:1166` | `* run (cont_id, the bx_display, the parsed gap/justify/cols, plus flex-wrap/ * row-gap/align-items). No-op on an...` |
| `scale` | function | `include/page_view.h:645` | `* scale(1)) and rotate in whole degrees (transform_rotate);` |
| `shc_cache` | struct | `include/page_view.h:932` | `` |
| `tree` | function | `include/page_view.h:690` | `* box tree (a mask covers its whole subtree);` |
| `word_spacing` | type_alias | `include/page_view.h:1101` | `typedef struct pv_text_ext { int font_family, text_transform, letter_spacing, word_spacing;` |
| `FREEDOM_PDF_EXPORT_H` | macro | `include/pdf_export.h:2` | `#define FREEDOM_PDF_EXPORT_H` |
| `PE_EXT` | macro | `include/pdf_export.h:29` | `#define PE_EXT` |
| `PE_EXT_PNG` | macro | `include/pdf_export.h:30` | `#define PE_EXT_PNG` |
| `PE_FALLBACK_NAME` | macro | `include/pdf_export.h:31` | `#define PE_FALLBACK_NAME` |
| `PE_NAME_MAX` | macro | `include/pdf_export.h:28` | `#define PE_NAME_MAX` |
| `fallback` | function | `include/pdf_export.h:46` | `* fallback (PE_ERR_OVERFLOW, out left empty). title == NULL is treated as empty. * Does NOT append the extension...` |
| `literal` | function | `include/pdf_export.h:52` | `* trusted literal (e.g. PE_EXT / PE_EXT_PNG);` |
| `pe_paginate` | function | `include/pdf_export.h:70` | `size_t pe_paginate(const double *tops, const double *heights, size_t n, double page_h, int *out_page, double...` |
| `pe_status` | enum | `include/pdf_export.h:33` | `` |
| `trusted` | function | `include/pdf_export.h:51` | `* dir is trusted (chosen by the app from XDG/$HOME);` |
| `FREEDOM_PERF_TRACE_H` | macro | `include/perf_trace.h:2` | `#define FREEDOM_PERF_TRACE_H` |
| `PT_MAX_SAMPLES` | macro | `include/perf_trace.h:32` | `#define PT_MAX_SAMPLES` |
| `order` | enum | `include/perf_trace.h:71` | `` |
| `pt_count` | function | `include/perf_trace.h:57` | `size_t pt_count(const pt_trace *t, pt_stage stage);` |
| `pt_elapsed_us` | function | `include/perf_trace.h:50` | `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us);` |
| `pt_format` | function | `include/perf_trace.h:76` | `size_t pt_format(const pt_trace *t, char *buf, size_t cap);` |
| `pt_init` | function | `include/perf_trace.h:46` | `void pt_init(pt_trace *t);` |
| `pt_last_us` | function | `include/perf_trace.h:60` | `uint64_t pt_last_us(const pt_trace *t, pt_stage stage);` |
| `pt_max_us` | function | `include/perf_trace.h:64` | `uint64_t pt_max_us(const pt_trace *t, pt_stage stage);` |
| `pt_median_us` | function | `include/perf_trace.h:65` | `uint64_t pt_median_us(const pt_trace *t, pt_stage stage);` |
| `pt_min_us` | function | `include/perf_trace.h:63` | `uint64_t pt_min_us(const pt_trace *t, pt_stage stage);` |
| `pt_record` | function | `include/perf_trace.h:54` | `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us);` |
| `pt_stage_name` | function | `include/perf_trace.h:69` | `const char *pt_stage_name(pt_stage stage);` |
| `pt_stage_stats` | struct | `include/perf_trace.h:34` | `` |
| `pt_trace` | struct | `include/perf_trace.h:41` | `` |
| `samples` | type_alias | `include/perf_trace.h:33` | `typedef struct pt_stage_stats { uint64_t samples[PT_MAX_SAMPLES];` |
| `stage` | type_alias | `include/perf_trace.h:40` | `typedef struct pt_trace { pt_stage_stats stage[PT_STAGE_COUNT];` |
| `FREEDOM_PQ_SEAL_H` | macro | `include/pq_seal.h:2` | `#define FREEDOM_PQ_SEAL_H` |
| `PQS_CT_LEN` | macro | `include/pq_seal.h:22` | `#define PQS_CT_LEN` |
| `PQS_MAGIC` | macro | `include/pq_seal.h:20` | `#define PQS_MAGIC` |
| `PQS_MAGIC_LEN` | macro | `include/pq_seal.h:21` | `#define PQS_MAGIC_LEN` |
| `pqs_buf_free` | function | `include/pq_seal.h:51` | `void pqs_buf_free(uint8_t *buf, size_t len);` |
| `pqs_free` | function | `include/pq_seal.h:41` | `void pqs_free(pqs_keys *k);` |
| `pqs_keys` | type_alias | `include/pq_seal.h:33` | `typedef struct pqs_keys pqs_keys;` |
| `pqs_status` | enum | `include/pq_seal.h:24` | `` |
| `FREEDOM_PREFETCH_H` | macro | `include/prefetch.h:2` | `#define FREEDOM_PREFETCH_H` |
| `PF_MAX_IMPORTS` | macro | `include/prefetch.h:50` | `#define PF_MAX_IMPORTS` |
| `PF_MAX_JOBS` | macro | `include/prefetch.h:49` | `#define PF_MAX_JOBS` |
| `PF_MAX_REFS` | macro | `include/prefetch.h:47` | `#define PF_MAX_REFS` |
| `PF_MAX_THREADS` | macro | `include/prefetch.h:48` | `#define PF_MAX_THREADS` |
| `PF_SPEC_MAX` | macro | `include/prefetch.h:51` | `#define PF_SPEC_MAX` |
| `fetch` | function | `include/prefetch.h:132` | `* claiming jobs and running fetch(ctx, "GET", url, ...). Returns 0 on success or * -1 when no thread could start...` |
| `inner` | type_alias | `include/prefetch.h:159` | `typedef struct pf_gated_fetch { pf_fetch_fn inner;` |
| `jobs` | type_alias | `include/prefetch.h:89` | `typedef struct pf_pool { pf_job jobs[PF_MAX_JOBS];` |
| `kind` | type_alias | `include/prefetch.h:42` | `typedef struct pf_ref { pf_kind kind;` |
| `pf_find_importmap` | function | `include/prefetch.h:115` | `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n);` |
| `pf_gated_fetch` | struct | `include/prefetch.h:159` | `` |
| `pf_job` | struct | `include/prefetch.h:80` | `` |
| `pf_job_state` | enum | `include/prefetch.h:73` | `` |
| `pf_kind` | enum | `include/prefetch.h:35` | `` |
| `pf_list` | struct | `include/prefetch.h:53` | `` |
| `pf_list_free` | function | `include/prefetch.h:63` | `void pf_list_free(pf_list *l);` |
| `pf_pool` | struct | `include/prefetch.h:90` | `` |
| `pf_pool_add` | function | `include/prefetch.h:127` | `int pf_pool_add(pf_pool *p, const char *url);` |
| `pf_pool_finish` | function | `include/prefetch.h:151` | `void pf_pool_finish(pf_pool *p);` |
| `pf_pool_take` | function | `include/prefetch.h:145` | `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status, char **body, size_t *len, char **ctype);` |
| `pf_pooled_fetch` | function | `include/prefetch.h:165` | `int pf_pooled_fetch(void *vctx, const char *method, const char *url, const char *body, size_t body_len, int...` |
| `pf_ref` | struct | `include/prefetch.h:42` | `` |
| `pf_scan` | function | `include/prefetch.h:62` | `int pf_scan(const char *html, size_t len, pf_list *out);` |
| `pool` | function | `include/prefetch.h:155` | `* whose URL is pooled is served from the pool (a failed prefetch propagates the * failure -- never refetched);` |
| `refs` | type_alias | `include/prefetch.h:52` | `typedef struct pf_list { pf_ref refs[PF_MAX_REFS];` |
| `specifiers` | function | `include/prefetch.h:110` | `* specifiers (each < PF_SPEC_MAX) into out[k] and returns how many. Pure. */ size_t pf_scan_imports(const char *js...` |
| `started` | function | `include/prefetch.h:121` | `* to fetch or no thread started (the caller fetches serially). */ int pf_pool_start_page(pf_pool *p, const char...` |
| `FREEDOM_PREFS_H` | macro | `include/prefs.h:2` | `#define FREEDOM_PREFS_H` |
| `PREFS_MAX_BOOKMARKS` | macro | `include/prefs.h:29` | `#define PREFS_MAX_BOOKMARKS` |
| `PREFS_MAX_HISTORY` | macro | `include/prefs.h:30` | `#define PREFS_MAX_HISTORY` |
| `PREFS_MAX_TEXT` | macro | `include/prefs.h:31` | `#define PREFS_MAX_TEXT` |
| `PREFS_MAX_TITLE` | macro | `include/prefs.h:28` | `#define PREFS_MAX_TITLE` |
| `PREFS_MAX_URL` | macro | `include/prefs.h:27` | `#define PREFS_MAX_URL` |
| `PREFS_PAGE_HISTORY` | macro | `include/prefs.h:34` | `#define PREFS_PAGE_HISTORY` |
| `PREFS_VERSION` | macro | `include/prefs.h:26` | `#define PREFS_VERSION` |
| `anyway` | function | `include/prefs.h:106` | `* page is rendered by the normal confined pipeline anyway (defence in depth). * *out is owned (free());` |
| `free` | function | `include/prefs.h:72` | `* free(). */ prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len);` |
| `prefs_bookmark_index` | function | `include/prefs.h:82` | `int prefs_bookmark_index(const prefs_state *p, const char *url);` |
| `prefs_entry` | struct | `include/prefs.h:45` | `` |
| `prefs_free` | function | `include/prefs.h:69` | `void prefs_free(prefs_state *p);` |
| `prefs_init` | function | `include/prefs.h:66` | `void prefs_init(prefs_state *p);` |
| `prefs_state` | struct | `include/prefs.h:50` | `` |
| `prefs_status` | enum | `include/prefs.h:36` | `` |
| `prefs_suggest` | function | `include/prefs.h:101` | `int prefs_suggest(const prefs_state *p, const char *query, char *out, size_t row_len, int max_rows);` |
| `theme_mode` | type_alias | `include/prefs.h:49` | `typedef struct prefs_state { int theme_mode;` |
| `FREEDOM_PRES_HINTS_H` | macro | `include/pres_hints.h:8` | `#define FREEDOM_PRES_HINTS_H` |
| `PH_ATTR_MAX` | macro | `include/pres_hints.h:17` | `#define PH_ATTR_MAX` |
| `PH_CENTERED` | macro | `include/pres_hints.h:26` | `#define PH_CENTERED` |
| `PH_DIM_MAX_PX` | macro | `include/pres_hints.h:18` | `#define PH_DIM_MAX_PX` |
| `PH_QUIRKS` | macro | `include/pres_hints.h:27` | `#define PH_QUIRKS` |
| `ph_apply` | function | `include/pres_hints.h:31` | `void ph_apply(const char *tag, ph_attr_fn get, void *ctx, unsigned flags, css_style *cs);` |
| `ph_cell_padding` | function | `include/pres_hints.h:41` | `void ph_cell_padding(int cellpad, css_style *cs);` |
| `ph_parse_dimension` | function | `include/pres_hints.h:24` | `int ph_parse_dimension(const char *s, size_t len, int *px, int *per_mille);` |
| `ph_parse_nonneg` | function | `include/pres_hints.h:34` | `int ph_parse_nonneg(const char *s, size_t len, int *out);` |
| `ph_table_cellpadding` | function | `include/pres_hints.h:37` | `int ph_table_cellpadding(ph_attr_fn get, void *ctx);` |
| `FREEDOM_PROFILE_H` | macro | `include/profile.h:2` | `#define FREEDOM_PROFILE_H` |
| `PROFILE_KEY_FILE` | macro | `include/profile.h:32` | `#define PROFILE_KEY_FILE` |
| `PROFILE_PREFS_FILE` | macro | `include/profile.h:33` | `#define PROFILE_PREFS_FILE` |
| `absent` | function | `include/profile.h:53` | `* the keyfile when absent (0600, atomic write);` |
| `closed` | function | `include/profile.h:54` | `* wrong size fails closed (PROFILE_ERR_KEY, never overwritten). Derives the * AEAD key (Argon2id, per-device salt)...` |
| `dir` | type_alias | `include/profile.h:45` | `typedef struct profile_ctx { char dir[1024];` |
| `profile_close` | function | `include/profile.h:67` | `void profile_close(profile_ctx *ctx);` |
| `profile_ctx` | struct | `include/profile.h:46` | `` |
| `profile_status` | enum | `include/profile.h:35` | `` |
| `FREEDOM_PSL_DATA_H` | macro | `include/psl_data.h:2` | `#define FREEDOM_PSL_DATA_H` |
| `psl_exceptions` | variable | `include/psl_data.h:25` | `extern const char *const psl_exceptions[];` |
| `psl_exceptions_n` | variable | `include/psl_data.h:26` | `extern const size_t psl_exceptions_n;` |
| `psl_rules` | variable | `include/psl_data.h:21` | `extern const char *const psl_rules[];` |
| `psl_rules_n` | variable | `include/psl_data.h:22` | `extern const size_t psl_rules_n;` |
| `psl_wildcards` | variable | `include/psl_data.h:23` | `extern const char *const psl_wildcards[];` |
| `psl_wildcards_n` | variable | `include/psl_data.h:24` | `extern const size_t psl_wildcards_n;` |
| `FREEDOM_RENDER_DOC_H` | macro | `include/render_doc.h:2` | `#define FREEDOM_RENDER_DOC_H` |
| `IMG_FAIL_OK` | function | `include/render_doc.h:360` | `* IMG_FAIL_OK (not a failure) or the reason is unknown. */ const char *rd_image_fail_label(img_fail_reason reason);` |
| `RD_IMAGE` | function | `include/render_doc.h:59` | `* RD_IMAGE (image src) and RD_INPUT (the owning form's action);` |
| `decision` | function | `include/render_doc.h:354` | `* decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never * NULL. */ const char...` |
| `default` | function | `include/render_doc.h:153` | `* default (layout is structure, not author styling, and leaks nothing to the * network) so the presentation layer...` |
| `form` | function | `include/render_doc.h:63` | `* form (-1 = none);` |
| `img_fail_reason` | enum | `include/render_doc.h:34` | `` |
| `kind` | type_alias | `include/render_doc.h:64` | `typedef struct rd_block { rd_kind kind;` |
| `list` | function | `include/render_doc.h:18` | `* inert display list (page_view) and the presentation orchestrator (the GUI and * the --headless writer). It decides...` |
| `rd_at` | function | `include/render_doc.h:322` | `const rd_block *rd_at(const rd_doc *d, size_t i);` |
| `rd_block` | struct | `include/render_doc.h:64` | `` |
| `rd_block_heading_level` | function | `include/render_doc.h:351` | `int rd_block_heading_level(const rd_block *b);` |
| `rd_block_tag` | function | `include/render_doc.h:344` | `const char *rd_block_tag(const rd_block *b);` |
| `rd_box_at` | function | `include/render_doc.h:327` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i);` |
| `rd_box_count` | function | `include/render_doc.h:326` | `size_t rd_box_count(const rd_doc *d);` |
| `rd_cont_at` | function | `include/render_doc.h:332` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i);` |
| `rd_cont_count` | function | `include/render_doc.h:331` | `size_t rd_cont_count(const rd_doc *d);` |
| `rd_count` | function | `include/render_doc.h:321` | `size_t rd_count(const rd_doc *d);` |
| `rd_doc` | struct | `include/render_doc.h:267` | `` |
| `rd_free` | function | `include/render_doc.h:318` | `void rd_free(rd_doc *d);` |
| `rd_input_invisible` | function | `include/render_doc.h:370` | `int rd_input_invisible(int input_type);` |
| `rd_input_label` | function | `include/render_doc.h:365` | `const char *rd_input_label(int input_type);` |
| `rd_kind` | enum | `include/render_doc.h:42` | `` |
| `rd_kind_name` | function | `include/render_doc.h:336` | `const char *rd_kind_name(rd_kind k);` |
| `rd_status` | enum | `include/render_doc.h:299` | `` |
| `rdp_images_warning` | function | `include/render_doc.h:308` | `* rdp_images_warning() is prepended so the user is always told. Each image * becomes an RD_IMAGE block whose...` |
| `to` | function | `include/render_doc.h:253` | `* belongs to (-1 = none);` |
| `FREEDOM_RENDER_POLICY_H` | macro | `include/render_policy.h:2` | `#define FREEDOM_RENDER_POLICY_H` |
| `RDP_TRACKER_MAX_DIM` | macro | `include/render_policy.h:27` | `#define RDP_TRACKER_MAX_DIM` |
| `images` | type_alias | `include/render_policy.h:32` | `typedef struct rdp_caps { bool images;` |
| `rdp_caps` | struct | `include/render_policy.h:32` | `` |
| `rdp_images_warning` | function | `include/render_policy.h:69` | `const char *rdp_images_warning(void);` |
| `rdp_img_decision` | enum | `include/render_policy.h:39` | `` |
| `rdp_img_reason` | function | `include/render_policy.h:66` | `const char *rdp_img_reason(rdp_img_decision d);` |
| `rdp_is_tracking_pixel` | function | `include/render_policy.h:53` | `int rdp_is_tracking_pixel(int w, int h);` |
| `size` | function | `include/render_policy.h:56` | `* announced size (e.g. <img width height>);` |
| `FREEDOM_RENDERER_H` | macro | `include/renderer.h:2` | `#define FREEDOM_RENDERER_H` |
| `RD_MAX_FIELD` | macro | `include/renderer.h:38` | `#define RD_MAX_FIELD` |
| `RD_MAX_INPUT` | macro | `include/renderer.h:37` | `#define RD_MAX_INPUT` |
| `rd_result` | struct | `include/renderer.h:29` | `` |
| `rd_result_free` | function | `include/renderer.h:46` | `void rd_result_free(rd_result *out);` |
| `rd_status` | enum | `include/renderer.h:20` | `` |
| `status` | type_alias | `include/renderer.h:28` | `typedef struct rd_result { rd_status status;` |
| `FREEDOM_REQUEST_POLICY_H` | macro | `include/request_policy.h:2` | `#define FREEDOM_REQUEST_POLICY_H` |
| `RP_HDR_MAX_BYTES` | macro | `include/request_policy.h:44` | `#define RP_HDR_MAX_BYTES` |
| `RP_HDR_MAX_COUNT` | macro | `include/request_policy.h:43` | `#define RP_HDR_MAX_COUNT` |
| `RP_HDR_NAME_MAX` | macro | `include/request_policy.h:45` | `#define RP_HDR_NAME_MAX` |
| `RP_HDR_VALUE_MAX` | macro | `include/request_policy.h:46` | `#define RP_HDR_VALUE_MAX` |
| `rp_decision` | enum | `include/request_policy.h:21` | `` |
| `rp_headers_have` | function | `include/request_policy.h:61` | `static inline int rp_headers_have(const char *lines, const char *name)` |
| `rp_host_of` | function | `include/request_policy.h:30` | `int rp_host_of(const char *url, char *out, size_t out_size);` |
| `rp_same_site` | function | `include/request_policy.h:37` | `int rp_same_site(const char *top_level_url, const char *request_url);` |
| `rp_sanitize_request_headers` | function | `include/request_policy.h:57` | `int rp_sanitize_request_headers(const char *raw, char *out, size_t cap);` |
| `rp_site_of` | function | `include/request_policy.h:34` | `int rp_site_of(const char *host, char *out, size_t out_size);` |
| `EXCLUDED` | function | `include/secure_fetch.h:245` | `* cookies are EXCLUDED (network-only, never exposed to JS) and expired cookies skipped. * Only for a TRUSTED host...` |
| `FREEDOM_SECURE_FETCH_H` | macro | `include/secure_fetch.h:2` | `#define FREEDOM_SECURE_FETCH_H` |
| `SF_CONNECT_TIMEOUT_MS` | macro | `include/secure_fetch.h:228` | `#define SF_CONNECT_TIMEOUT_MS` |
| `SF_DEFAULT_KEX_GROUPS` | macro | `include/secure_fetch.h:178` | `#define SF_DEFAULT_KEX_GROUPS` |
| `SF_DEFAULT_MAX_BODY` | macro | `include/secure_fetch.h:204` | `#define SF_DEFAULT_MAX_BODY` |
| `SF_DEFAULT_MAX_REDIRECTS` | macro | `include/secure_fetch.h:230` | `#define SF_DEFAULT_MAX_REDIRECTS` |
| `SF_DEFAULT_TIMEOUT_MS` | macro | `include/secure_fetch.h:205` | `#define SF_DEFAULT_TIMEOUT_MS` |
| `SF_DEFAULT_USER_AGENT` | macro | `include/secure_fetch.h:203` | `#define SF_DEFAULT_USER_AGENT` |
| `SF_IMPERSONATE_KEX_GROUPS` | macro | `include/secure_fetch.h:187` | `#define SF_IMPERSONATE_KEX_GROUPS` |
| `SF_IMPERSONATE_TLS12_CIPHERS` | macro | `include/secure_fetch.h:192` | `#define SF_IMPERSONATE_TLS12_CIPHERS` |
| `SF_IMPERSONATE_TLS13_CIPHERS` | macro | `include/secure_fetch.h:188` | `#define SF_IMPERSONATE_TLS13_CIPHERS` |
| `SF_MAX_URL` | macro | `include/secure_fetch.h:231` | `#define SF_MAX_URL` |
| `SF_META_MAX` | macro | `include/secure_fetch.h:80` | `#define SF_META_MAX` |
| `SF_RESPONSE_HEADERS_MAX` | macro | `include/secure_fetch.h:81` | `#define SF_RESPONSE_HEADERS_MAX` |
| `SF_SUBRESOURCE_TIMEOUT_MS` | macro | `include/secure_fetch.h:229` | `#define SF_SUBRESOURCE_TIMEOUT_MS` |
| `SF_WS_MAX_MESSAGE` | macro | `include/secure_fetch.h:336` | `#define SF_WS_MAX_MESSAGE` |
| `bits` | function | `include/secure_fetch.h:354` | `* *flags receives CURLWS_* bits (text/binary/close/cont);` |
| `connection` | function | `include/secure_fetch.h:368` | `* on each connection (Zero Trust). Each target is re-validated and a downgrade * to http:// is refused. Exceeding...` |
| `exhausted` | function | `include/secure_fetch.h:399` | `* is exhausted (*next untouched). `allowlisted` enables the sovereignty rung. */ int sf_fallback_policy(sf_status...` |
| `policy` | type_alias | `include/secure_fetch.h:82` | `typedef struct sf_config { sf_policy policy;` |
| `rp_sanitize_request_headers` | function | `include/secure_fetch.h:112` | `* rp_sanitize_request_headers ("Name: value\n" lines);` |
| `sf_accept_language_or_default` | function | `include/secure_fetch.h:270` | `const char *sf_accept_language_or_default(const char *lang);` |
| `sf_chain_info` | struct | `include/secure_fetch.h:64` | `` |
| `sf_config` | struct | `include/secure_fetch.h:83` | `` |
| `sf_cookie_line_matches` | function | `include/secure_fetch.h:257` | `int sf_cookie_line_matches(const char *line, const char *host, const char *path, long now, char *out, size_t outsz);` |
| `sf_cookie_put` | function | `include/secure_fetch.h:252` | `void sf_cookie_put(const char *url, const char *namevalue);` |
| `sf_get` | function | `include/secure_fetch.h:377` | `* sf_get (Zero Trust): an insecure POST is not representable. Does not follow * redirects (the caller inspects...` |
| `sf_global_init` | function | `include/secure_fetch.h:239` | `void sf_global_init(void);` |
| `sf_header_value` | function | `include/secure_fetch.h:317` | `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz);` |
| `sf_impersonate_kex_groups` | function | `include/secure_fetch.h:274` | `const char *sf_impersonate_kex_groups(void);` |
| `sf_impersonate_tls13_ciphers` | function | `include/secure_fetch.h:275` | `const char *sf_impersonate_tls13_ciphers(void);` |
| `sf_is_redirect_code` | function | `include/secure_fetch.h:306` | `int sf_is_redirect_code(long http_code);` |
| `sf_policy` | enum | `include/secure_fetch.h:44` | `` |
| `sf_proxy_type` | enum | `include/secure_fetch.h:73` | `` |
| `sf_rcache_clear` | function | `include/secure_fetch.h:414` | `void sf_rcache_clear(void);` |
| `sf_rcache_get` | function | `include/secure_fetch.h:413` | `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap);` |
| `sf_rcache_put` | function | `include/secure_fetch.h:412` | `int sf_rcache_put(const char *from, const char *to, time_t now);` |
| `sf_rcache_set_backing` | function | `include/secure_fetch.h:423` | `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx);` |
| `sf_response` | struct | `include/secure_fetch.h:142` | `` |
| `sf_response_free` | function | `include/secure_fetch.h:388` | `void sf_response_free(sf_response *resp);` |
| `sf_status` | enum | `include/secure_fetch.h:24` | `` |
| `sf_user_agent_or_default` | function | `include/secure_fetch.h:266` | `const char *sf_user_agent_or_default(const char *ua);` |
| `sf_ws` | type_alias | `include/secure_fetch.h:337` | `typedef struct sf_ws sf_ws;` |
| `sf_ws_close` | function | `include/secure_fetch.h:364` | `void sf_ws_close(sf_ws *ws);` |
| `sf_ws_fd` | function | `include/secure_fetch.h:361` | `int sf_ws_fd(const sf_ws *ws);` |
| `skipped` | function | `include/secure_fetch.h:295` | `* skipped (a classical key exchange is accepted);` |
| `status` | type_alias | `include/secure_fetch.h:141` | `typedef struct sf_response { sf_status status;` |
| `validators` | function | `include/secure_fetch.h:18` | `* The security logic lives in pure validators (no I/O);` |
| `FREEDOM_SHA2_H` | macro | `include/sha2.h:2` | `#define FREEDOM_SHA2_H` |
| `SHA_MAX_DIGEST` | macro | `include/sha2.h:18` | `#define SHA_MAX_DIGEST` |
| `sha_alg` | enum | `include/sha2.h:16` | `` |
| `sha_alg_from_name` | function | `include/sha2.h:24` | `int sha_alg_from_name(const char *name, sha_alg *out);` |
| `sha_digest` | function | `include/sha2.h:28` | `int sha_digest(sha_alg alg, const void *data, size_t len, uint8_t *out);` |
| `sha_digest_len` | function | `include/sha2.h:21` | `size_t sha_digest_len(sha_alg alg);` |
| `FREEDOM_SHEET_CACHE_H` | macro | `include/sheet_cache.h:14` | `#define FREEDOM_SHEET_CACHE_H` |
| `hits` | type_alias | `include/sheet_cache.h:42` | `typedef struct shc_stats { unsigned long hits;` |
| `shc_acquire` | function | `include/sheet_cache.h:60` | `shc_sheet *shc_acquire(shc_cache *cache, const shc_key *key);` |
| `shc_cache` | type_alias | `include/sheet_cache.h:26` | `typedef struct shc_cache shc_cache;` |
| `shc_css` | function | `include/sheet_cache.h:64` | `const css_sheet *shc_css(const shc_sheet *s);` |
| `shc_free` | function | `include/sheet_cache.h:55` | `void shc_free(shc_cache *c);` |
| `shc_key` | struct | `include/sheet_cache.h:36` | `` |
| `shc_new` | function | `include/sheet_cache.h:52` | `shc_cache *shc_new(size_t max_text_bytes);` |
| `shc_release` | function | `include/sheet_cache.h:67` | `void shc_release(shc_sheet *s);` |
| `shc_sheet` | type_alias | `include/sheet_cache.h:28` | `typedef struct shc_sheet shc_sheet;` |
| `shc_stats` | struct | `include/sheet_cache.h:43` | `` |
| `shc_stats_get` | function | `include/sheet_cache.h:70` | `void shc_stats_get(const shc_cache *c, shc_stats *out);` |
| `FREEDOM_SHM_SLOTS_H` | macro | `include/shm_slots.h:2` | `#define FREEDOM_SHM_SLOTS_H` |
| `SS_COUNT` | macro | `include/shm_slots.h:17` | `#define SS_COUNT` |
| `busy` | type_alias | `include/shm_slots.h:18` | `typedef struct ss_state { int busy[SS_COUNT];` |
| `ss_committed` | function | `include/shm_slots.h:41` | `static inline void ss_committed(ss_state *s, int i)` |
| `ss_init` | function | `include/shm_slots.h:24` | `static inline void ss_init(ss_state *s)` |
| `ss_released` | function | `include/shm_slots.h:49` | `static inline int ss_released(ss_state *s, int i)` |
| `ss_state` | struct | `include/shm_slots.h:19` | `` |
| `SQB_MAX_JOBS` | macro | `include/subreq_batch.h:14` | `#define SQB_MAX_JOBS` |
| `SUBREQ_BATCH_H` | macro | `include/subreq_batch.h:10` | `#define SUBREQ_BATCH_H` |
| `ok` | type_alias | `include/subreq_batch.h:23` | `typedef struct sqb_res { int ok;` |
| `sqb` | type_alias | `include/subreq_batch.h:34` | `typedef struct sqb sqb;` |
| `sqb_count` | function | `include/subreq_batch.h:42` | `size_t sqb_count(const sqb *b);` |
| `sqb_free` | function | `include/subreq_batch.h:49` | `void sqb_free(sqb *b);` |
| `sqb_new` | function | `include/subreq_batch.h:37` | `sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx);` |
| `sqb_req` | struct | `include/subreq_batch.h:16` | `` |
| `sqb_res` | struct | `include/subreq_batch.h:23` | `` |
| `sqb_reset` | function | `include/subreq_batch.h:48` | `void sqb_reset(sqb *b);` |
| `sqb_result` | function | `include/subreq_batch.h:46` | `const sqb_res *sqb_result(const sqb *b, size_t i);` |
| `sqb_submit` | function | `include/subreq_batch.h:41` | `int sqb_submit(sqb *b, int refused, const sqb_req *req);` |
| `sqb_wait_all` | function | `include/subreq_batch.h:44` | `void sqb_wait_all(sqb *b);` |
| `FREEDOM_SVG_PAINT_H` | macro | `include/svg_paint.h:2` | `#define FREEDOM_SVG_PAINT_H` |
| `svp_draw` | function | `include/svg_paint.h:31` | `void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, double h, int current_rgb);` |
| `way` | function | `include/svg_paint.h:35` | `* worker rasterizes SVG images this way (spec/svg_raster.md section 3): drawing text * would open fontconfig, i.e....` |
| `FREEDOM_SVG_RASTER_H` | macro | `include/svg_raster.h:2` | `#define FREEDOM_SVG_RASTER_H` |
| `SR_MAX_DIM` | macro | `include/svg_raster.h:24` | `#define SR_MAX_DIM` |
| `SR_MIN_RASTER` | macro | `include/svg_raster.h:25` | `#define SR_MIN_RASTER` |
| `SR_SNIFF_MAX` | macro | `include/svg_raster.h:23` | `#define SR_SNIFF_MAX` |
| `sr_sniff` | function | `include/svg_raster.h:29` | `int sr_sniff(const uint8_t *bytes, size_t len);` |
| `FREEDOM_SVG_RENDER_H` | macro | `include/svg_render.h:2` | `#define FREEDOM_SVG_RENDER_H` |
| `SV_DEFAULT_H` | macro | `include/svg_render.h:42` | `#define SV_DEFAULT_H` |
| `SV_DEFAULT_W` | macro | `include/svg_render.h:41` | `#define SV_DEFAULT_W` |
| `SV_MAX_DEPTH` | macro | `include/svg_render.h:35` | `#define SV_MAX_DEPTH` |
| `SV_MAX_INPUT` | macro | `include/svg_render.h:37` | `#define SV_MAX_INPUT` |
| `SV_MAX_POINTS` | macro | `include/svg_render.h:33` | `#define SV_MAX_POINTS` |
| `SV_MAX_SEGS` | macro | `include/svg_render.h:34` | `#define SV_MAX_SEGS` |
| `SV_MAX_SHAPES` | macro | `include/svg_render.h:32` | `#define SV_MAX_SHAPES` |
| `SV_TEXT_MAX` | macro | `include/svg_render.h:36` | `#define SV_TEXT_MAX` |
| `height` | type_alias | `include/svg_render.h:104` | `typedef struct sv_image { double width, height;` |
| `kind` | type_alias | `include/svg_render.h:75` | `typedef struct sv_shape { int kind;` |
| `sv_fit` | function | `include/svg_render.h:131` | `void sv_fit(const sv_image *img, double dw, double dh, double *scale, double *off_x, double *off_y);` |
| `sv_image` | struct | `include/svg_render.h:104` | `` |
| `sv_seg` | struct | `include/svg_render.h:65` | `` |
| `sv_shape` | struct | `include/svg_render.h:75` | `` |
| `sv_shape_kind` | enum | `include/svg_render.h:44` | `` |
| `sv_status` | enum | `include/svg_render.h:25` | `` |
| `sv_verb` | enum | `include/svg_render.h:58` | `` |
| `verb` | type_alias | `include/svg_render.h:64` | `typedef struct sv_seg { int verb;` |
| `FREEDOM_TAB_H` | macro | `include/tab.h:2` | `#define FREEDOM_TAB_H` |
| `TAB_MAX_INPUT` | macro | `include/tab.h:157` | `#define TAB_MAX_INPUT` |
| `bytes` | function | `include/tab.h:223` | `* so the parent can retain the bytes (spec/webfont.md b3b feeds them to the * @font-face loader as extern sheets)....` |
| `decode` | function | `include/tab.h:417` | `* could not decode (caller shows the placeholder), which is not a transport error. * TAB_ERR_* is reserved for...` |
| `exclusively` | function | `include/tab.h:285` | `* exclusively (tab_subreq_permitted). Default 0: zero fetches, Privacy by Default. */ void tab_set_css_allowed(tab...` |
| `granted` | function | `include/tab.h:391` | `* granted (allow.conf AND js.conf);` |
| `jar` | function | `include/tab.h:270` | `* the trusted parent read from its ephemeral network jar (sf_cookie_header_for). Only * meaningful for a trusted...` |
| `kind` | type_alias | `include/tab.h:71` | `typedef struct tab_ws_op { int kind;` |
| `load` | function | `include/tab.h:297` | `* trusted load (net granted). */ void tab_set_frame_id(tab *t, int id);` |
| `none` | function | `include/tab.h:241` | `* worker sent carries none (tab_page.unchanged) -- on a live page that is almost every tick. * The caller must then...` |
| `origin` | function | `include/tab.h:277` | `* page origin (web_storage snapshot, copied). Used only when the load is trusted * (net granted);` |
| `out_status` | function | `include/tab.h:198` | `* On success return 0 and set *out_status (HTTP status), *out_body / *out_body_len * (malloc'd response bytes, tab...` |
| `popstate` | function | `include/tab.h:398` | `* popstate (+ hashchange) and re-derives the view like a click. */ tab_status tab_popstate(tab *t, int index...` |
| `replace` | type_alias | `include/tab.h:54` | `typedef struct tab_hist_op { int replace;` |
| `returned` | function | `include/tab.h:392` | `* returned (the page keeps its zeros). The worker re-checks the same condition. * g must be finished (jg_finish). */...` |
| `string` | function | `include/tab.h:342` | `* event_type is a JS event type string (e.g. "keydown", "input", "change"). * key is the keyboard key value (may be...` |
| `tab` | type_alias | `include/tab.h:46` | `typedef struct tab tab;` |
| `tab_alive` | function | `include/tab.h:430` | `int tab_alive(const tab *t);` |
| `tab_async_busy` | function | `include/tab.h:263` | `int tab_async_busy(const tab *t);` |
| `tab_async_fd` | function | `include/tab.h:257` | `* the completion is signalled on tab_async_fd (readable). The pipe to the worker is a single * channel, so EVERY...` |
| `tab_child_pid` | function | `include/tab.h:433` | `pid_t tab_child_pid(const tab *t);` |
| `tab_close` | function | `include/tab.h:436` | `void tab_close(tab *t);` |
| `tab_eval_result` | struct | `include/tab.h:135` | `` |
| `tab_eval_result_free` | function | `include/tab.h:440` | `void tab_eval_result_free(tab_eval_result *r);` |
| `tab_hist_op` | struct | `include/tab.h:54` | `` |
| `tab_image` | struct | `include/tab.h:148` | `` |
| `tab_image_free` | function | `include/tab.h:441` | `void tab_image_free(tab_image *img);` |
| `tab_inflight_request_headers` | function | `include/tab.h:214` | `const char *tab_inflight_request_headers(void);` |
| `tab_last_subreq_stats` | function | `include/tab.h:309` | `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us);` |
| `tab_open` | function | `include/tab.h:165` | `* and reaches tab_open (the app and the test harness) must call this first. */ void tab_worker_dispatch(int argc...` |
| `tab_page` | struct | `include/tab.h:79` | `` |
| `tab_page_free` | function | `include/tab.h:439` | `void tab_page_free(tab_page *p);` |
| `tab_page_keep_view` | function | `include/tab.h:248` | `void tab_page_keep_view(tab_page *prev, tab_page *next);` |
| `tab_parse_worker_args` | function | `include/tab.h:172` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd);` |
| `tab_prewarm` | function | `include/tab.h:181` | `void tab_prewarm(void);` |
| `tab_prewarmed` | function | `include/tab.h:184` | `int tab_prewarmed(void);` |
| `tab_prewarmed_pid` | function | `include/tab.h:187` | `int tab_prewarmed_pid(void);` |
| `tab_report_response_headers` | function | `include/tab.h:219` | `void tab_report_response_headers(const char *lines);` |
| `tab_set_cookies` | function | `include/tab.h:274` | `void tab_set_cookies(tab *t, const char *cookies);` |
| `tab_set_css_sink` | function | `include/tab.h:232` | `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx);` |
| `tab_set_fetcher` | function | `include/tab.h:209` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx);` |
| `tab_set_identity` | function | `include/tab.h:303` | `void tab_set_identity(tab *t, const char *serialized);` |
| `tab_set_net_allowed` | function | `include/tab.h:237` | `void tab_set_net_allowed(tab *t, int allowed);` |
| `tab_set_op_net_budget_ms` | function | `include/tab.h:252` | `void tab_set_op_net_budget_ms(tab *t, int ms);` |
| `tab_set_storage` | function | `include/tab.h:279` | `void tab_set_storage(tab *t, const char *blob, size_t len);` |
| `tab_set_viewport_w` | function | `include/tab.h:293` | `void tab_set_viewport_w(tab *t, int px);` |
| `tab_shutdown_spare` | function | `include/tab.h:190` | `void tab_shutdown_spare(void);` |
| `tab_status` | enum | `include/tab.h:31` | `` |
| `tab_subreq_permitted` | function | `include/tab.h:314` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method);` |
| `tab_worker_dispatch` | function | `include/tab.h:161` | `* Call tab_worker_dispatch(argc, argv) as the FIRST thing in main(): if argv is the * internal "--tab-worker <rfd>...` |
| `tab_ws_event_kind` | enum | `include/tab.h:67` | `` |
| `tab_ws_kind` | enum | `include/tab.h:61` | `` |
| `tab_ws_op` | struct | `include/tab.h:72` | `` |
| `view` | function | `include/tab.h:322` | `* <noscript> handling in the built view (off => fallback shown, on => suppressed) * and is where allowlisted...` |
| `width` | type_alias | `include/tab.h:148` | `typedef struct tab_image { uint32_t width;` |
| `FREEDOM_TABLE_LAYOUT_H` | macro | `include/table_layout.h:11` | `#define FREEDOM_TABLE_LAYOUT_H` |
| `TL_MAX_COLS` | macro | `include/table_layout.h:20` | `#define TL_MAX_COLS` |
| `TL_PER_MILLE` | macro | `include/table_layout.h:26` | `#define TL_PER_MILLE` |
| `TL_WIDTH_MAX` | macro | `include/table_layout.h:23` | `#define TL_WIDTH_MAX` |
| `col` | type_alias | `include/table_layout.h:27` | `typedef struct tl_cell { int col;` |
| `px` | function | `include/table_layout.h:41` | `* px (< 0 = auto: the table is as wide as its content, capped at avail). gap is the space * between adjacent...` |
| `tl_cell` | struct | `include/table_layout.h:28` | `` |
| `tl_intrinsic` | function | `include/table_layout.h:53` | `void tl_intrinsic(const tl_cell *cells, size_t n, size_t ncols, double gap, double *min_total, double *max_total);` |
| `FREEDOM_TEXT_CASE_H` | macro | `include/text_case.h:2` | `#define FREEDOM_TEXT_CASE_H` |
| `TC_SMALLCAPS_SCALE` | macro | `include/text_case.h:15` | `#define TC_SMALLCAPS_SCALE` |
| `cp` | function | `include/text_case.h:19` | `* cp (identity otherwise), so a transformed text keeps its length. */ uint32_t tc_upper(uint32_t cp);` |
| `tc_is_lower` | function | `include/text_case.h:24` | `int tc_is_lower(uint32_t cp);` |
| `tc_lower` | function | `include/text_case.h:21` | `uint32_t tc_lower(uint32_t cp);` |
| `tc_run` | struct | `include/text_case.h:33` | `` |
| `tc_smallcaps_runs` | function | `include/text_case.h:41` | `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap);` |
| `tc_transform` | function | `include/text_case.h:29` | `size_t tc_transform(const char *s, size_t n, int transform, int word_start, char *out, size_t cap);` |
| `FREEDOM_TEXT_SHAPE_H` | macro | `include/text_shape.h:19` | `#define FREEDOM_TEXT_SHAPE_H` |
| `TSH_FAMILY_MAX` | macro | `include/text_shape.h:48` | `#define TSH_FAMILY_MAX` |
| `TSH_LOCAL_FAMILIES` | macro | `include/text_shape.h:47` | `#define TSH_LOCAL_FAMILIES` |
| `TSH_LOCAL_LISTS` | macro | `include/text_shape.h:46` | `#define TSH_LOCAL_LISTS` |
| `TSH_MAX_GLYPHS` | macro | `include/text_shape.h:77` | `#define TSH_MAX_GLYPHS` |
| `TSH_MAX_TEXT` | macro | `include/text_shape.h:78` | `#define TSH_MAX_TEXT` |
| `content` | function | `include/text_shape.h:11` | `* TEXT is hostile remote content (sanitised UTF-8) and is fuzzed (make fuzz-tsh);` |
| `end` | type_alias | `include/text_shape.h:138` | `typedef struct tsh_run { size_t start, end;` |
| `family` | type_alias | `include/text_shape.h:33` | `typedef struct tsh_font { int family;` |
| `origin` | function | `include/text_shape.h:92` | `* glyphs are written with positions relative to origin (0,0) on the baseline, * and *out_adv holds the total pen...` |
| `own` | function | `include/text_shape.h:142` | `* face of their own (controls, combining marks, variation selectors, ZWJ/ZWNJ) * stay in the run before them....` |
| `tsh_face` | function | `include/text_shape.h:133` | `cairo_font_face_t *tsh_face(const tsh_font *f);` |
| `tsh_face_generation` | function | `include/text_shape.h:122` | `unsigned tsh_face_generation(void);` |
| `tsh_family_is_generic` | function | `include/text_shape.h:52` | `int tsh_family_is_generic(const char *name);` |
| `tsh_font` | struct | `include/text_shape.h:33` | `` |
| `tsh_local_handle` | function | `include/text_shape.h:75` | `int tsh_local_handle(const char *list);` |
| `tsh_measure` | function | `include/text_shape.h:101` | `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len);` |
| `tsh_pick_family` | function | `include/text_shape.h:68` | `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong, size_t n, int...` |
| `tsh_ready` | function | `include/text_shape.h:89` | `int tsh_ready(void);` |
| `tsh_run` | struct | `include/text_shape.h:138` | `` |
| `tsh_shutdown` | function | `include/text_shape.h:149` | `void tsh_shutdown(void);` |
| `tsh_status` | enum | `include/text_shape.h:80` | `` |
| `tsh_webfont_clear` | function | `include/text_shape.h:126` | `void tsh_webfont_clear(void);` |
| `tsh_webfont_register` | function | `include/text_shape.h:114` | `int tsh_webfont_register(const char *name, const unsigned char *bytes, size_t nbytes, int bold, int italic);` |
| `wins` | function | `include/text_shape.h:58` | `* the first name the resolver accepts wins (returns 1, family in out). Pure: the * resolver is injected (fontconfig...` |
| `FREEDOM_TEXTFIELD_H` | macro | `include/textfield.h:2` | `#define FREEDOM_TEXTFIELD_H` |
| `TF_CAP` | macro | `include/textfield.h:23` | `#define TF_CAP` |
| `buf` | type_alias | `include/textfield.h:24` | `typedef struct tf_field { char buf[TF_CAP];` |
| `tf_backspace` | function | `include/textfield.h:53` | `void tf_backspace(tf_field *f);` |
| `tf_clear` | function | `include/textfield.h:45` | `void tf_clear(tf_field *f);` |
| `tf_cursor` | function | `include/textfield.h:68` | `size_t tf_cursor(const tf_field *f);` |
| `tf_delete` | function | `include/textfield.h:56` | `void tf_delete(tf_field *f);` |
| `tf_end` | function | `include/textfield.h:63` | `void tf_end(tf_field *f);` |

Next: [SYMBOLS_p6.md](SYMBOLS_p6.md)
