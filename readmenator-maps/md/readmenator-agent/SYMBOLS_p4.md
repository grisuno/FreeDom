# Symbols (page 4 of 15)
Previous: [SYMBOLS_p3.md](SYMBOLS_p3.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `processed` | type_alias | `include/js_dom.h:41` | `typedef struct jd_iframe_track { dom_node_id processed[JD_IFRAME_TRACK_MAX];` |
| `run` | function | `include/js_dom.h:127` | `* run (no handler registered, or handlers ran without calling preventDefault()), * and 0 if a handler called...` |
| `FREEDOM_JS_ENV_H` | macro | `include/js_env.h:2` | `#define FREEDOM_JS_ENV_H` |
| `je_status` | enum | `include/js_env.h:27` | `` |
| `poisoned` | function | `include/js_env.h:49` | `* readback is poisoned (deterministic within an origin, unlinkable across * sessions and across origins) to defeat...` |
| `FREEDOM_JS_GEOM_H` | macro | `include/js_geom.h:2` | `#define FREEDOM_JS_GEOM_H` |
| `JG_COORD_MAX` | macro | `include/js_geom.h:26` | `#define JG_COORD_MAX` |
| `JG_HEADER_N` | macro | `include/js_geom.h:27` | `#define JG_HEADER_N` |
| `JG_MAX_DEPTH` | macro | `include/js_geom.h:25` | `#define JG_MAX_DEPTH` |
| `JG_MAX_RECTS` | macro | `include/js_geom.h:24` | `#define JG_MAX_RECTS` |
| `JG_RECT_N` | macro | `include/js_geom.h:28` | `#define JG_RECT_N` |
| `jg_add` | function | `include/js_geom.h:52` | `int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h);` |
| `jg_aggregate` | function | `include/js_geom.h:65` | `int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx);` |
| `jg_decode` | function | `include/js_geom.h:77` | `int jg_decode(const int32_t *in, size_t n, jg_table *out);` |
| `jg_encode` | function | `include/js_geom.h:71` | `int jg_encode(const jg_table *t, int32_t *out, size_t cap);` |
| `jg_find` | function | `include/js_geom.h:59` | `const jg_rect *jg_find(const jg_table *t, dom_node_id node);` |
| `jg_finish` | function | `include/js_geom.h:56` | `int jg_finish(jg_table *t);` |
| `jg_free` | function | `include/js_geom.h:47` | `void jg_free(jg_table *t);` |
| `jg_hash` | function | `include/js_geom.h:80` | `uint64_t jg_hash(const jg_table *t);` |
| `jg_init` | function | `include/js_geom.h:44` | `void jg_init(jg_table *t);` |
| `jg_rect` | struct | `include/js_geom.h:30` | `` |
| `jg_table` | struct | `include/js_geom.h:35` | `` |
| `jg_wire_len` | function | `include/js_geom.h:68` | `size_t jg_wire_len(const jg_table *t);` |
| `node` | type_alias | `include/js_geom.h:29` | `typedef struct jg_rect { dom_node_id node;` |
| `FREEDOM_JS_LOCATION_H` | macro | `include/js_location.h:2` | `#define FREEDOM_JS_LOCATION_H` |
| `JD_HIST_MAX` | macro | `include/js_location.h:31` | `#define JD_HIST_MAX` |
| `acting` | function | `include/js_location.h:49` | `* The caller MUST gate the raw target with ln_resolve before acting (Zero Trust). */ int...` |
| `jd_pop_state` | function | `include/js_location.h:44` | `int jd_pop_state(js_context *ctx, int index);` |
| `jd_take_history` | function | `include/js_location.h:38` | `char *jd_take_history(js_context *ctx, int *go);` |
| `reads` | function | `include/js_location.h:25` | `* reads (NULL => only href is known, the rest fall back to stub defaults). Call after * jd_install, on the page's...` |
| `FREEDOM_JS_POLICY_H` | macro | `include/js_policy.h:2` | `#define FREEDOM_JS_POLICY_H` |
| `allowlist` | function | `include/js_policy.h:34` | `* allowlist (e.g. hb_is_allowlisted over js.conf). Fails closed: an unknown mode * yields false. */ bool...` |
| `jsp_mode` | enum | `include/js_policy.h:27` | `` |
| `jsp_mode_str` | function | `include/js_policy.h:64` | `const char *jsp_mode_str(jsp_mode mode);` |
| `jsp_present_trusted` | function | `include/js_policy.h:54` | `bool jsp_present_trusted(int host_allowlisted);` |
| `jsp_trusted` | function | `include/js_policy.h:45` | `bool jsp_trusted(bool js_enabled, int host_allowlisted);` |
| `membership` | function | `include/js_policy.h:16` | `* membership (the allowlist itself is matched by the hostblock module, which * already covers subdomains). No I/O...` |
| `FREEDOM_JS_SANDBOX_H` | macro | `include/js_sandbox.h:2` | `#define FREEDOM_JS_SANDBOX_H` |
| `JS_DEFAULT_MAX_SOURCE` | macro | `include/js_sandbox.h:66` | `#define JS_DEFAULT_MAX_SOURCE` |
| `JS_DEFAULT_MEM_LIMIT` | macro | `include/js_sandbox.h:67` | `#define JS_DEFAULT_MEM_LIMIT` |
| `JS_DEFAULT_STACK_LIMIT` | macro | `include/js_sandbox.h:68` | `#define JS_DEFAULT_STACK_LIMIT` |
| `JS_DEFAULT_TIME_BUDGET` | macro | `include/js_sandbox.h:69` | `#define JS_DEFAULT_TIME_BUDGET` |
| `JS_LOC_FILE_MAX` | macro | `include/js_sandbox.h:64` | `#define JS_LOC_FILE_MAX` |
| `JS_MODULE_BYTES_MAX` | macro | `include/js_sandbox.h:106` | `#define JS_MODULE_BYTES_MAX` |
| `JS_MODULE_MAX` | macro | `include/js_sandbox.h:105` | `#define JS_MODULE_MAX` |
| `JS_REALM_MAX` | macro | `include/js_sandbox.h:179` | `#define JS_REALM_MAX` |
| `JS_REJECT_MAX` | macro | `include/js_sandbox.h:182` | `#define JS_REJECT_MAX` |
| `handle` | function | `include/js_sandbox.h:162` | `* as an opaque handle (so this header stays free of backend types), or NULL. * Valid only while ctx is alive....` |
| `js_context` | type_alias | `include/js_sandbox.h:47` | `typedef struct js_context js_context;` |
| `js_context_free` | function | `include/js_sandbox.h:86` | `void js_context_free(js_context *ctx);` |
| `js_limits` | struct | `include/js_sandbox.h:39` | `` |
| `js_loc_from_stack` | function | `include/js_sandbox.h:140` | `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap, int *line, int *col);` |
| `js_pump_jobs` | function | `include/js_sandbox.h:159` | `int js_pump_jobs(js_context *ctx, int max_jobs);` |
| `js_result` | struct | `include/js_sandbox.h:49` | `` |
| `js_result_free` | function | `include/js_sandbox.h:151` | `void js_result_free(js_result *res);` |
| `js_set_current_script` | function | `include/js_sandbox.h:171` | `void js_set_current_script(js_context *ctx, const char *src, const char *type);` |
| `js_set_module_host` | function | `include/js_sandbox.h:119` | `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve, js_module_fetch_fn fetch, void *host);` |
| `js_set_time_budget` | function | `include/js_sandbox.h:148` | `void js_set_time_budget(js_context *ctx, uint64_t budget_ms);` |
| `js_status` | enum | `include/js_sandbox.h:24` | `` |
| `loaded` | function | `include/js_sandbox.h:114` | `* NULL when it cannot be loaded (policy refusal, network error, not JavaScript). */ typedef char...` |
| `max_source_bytes` | type_alias | `include/js_sandbox.h:39` | `typedef struct js_limits { size_t max_source_bytes;` |
| `status` | type_alias | `include/js_sandbox.h:48` | `typedef struct js_result { js_status status;` |
| `FREEDOM_JS_TRUSTED_H` | macro | `include/js_trusted.h:2` | `#define FREEDOM_JS_TRUSTED_H` |
| `JT_WS_MAX` | macro | `include/js_trusted.h:46` | `#define JT_WS_MAX` |
| `JT_WS_MAX_BYTES` | macro | `include/js_trusted.h:48` | `#define JT_WS_MAX_BYTES` |
| `JT_WS_MAX_OPS` | macro | `include/js_trusted.h:47` | `#define JT_WS_MAX_OPS` |
| `jt_take_opens` | function | `include/js_trusted.h:42` | `char *jt_take_opens(js_context *ctx);` |
| `jt_take_storage` | function | `include/js_trusted.h:93` | `int jt_take_storage(js_context *ctx, char **out, size_t *len);` |
| `jt_take_ws` | function | `include/js_trusted.h:75` | `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap);` |
| `jt_ws_event` | function | `include/js_trusted.h:81` | `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len);` |
| `jt_ws_event_kind` | enum | `include/js_trusted.h:64` | `` |
| `jt_ws_kind` | enum | `include/js_trusted.h:50` | `` |
| `jt_ws_op` | struct | `include/js_trusted.h:57` | `` |
| `jt_ws_ops_free` | function | `include/js_trusted.h:76` | `void jt_ws_ops_free(jt_ws_op *ops, size_t n);` |
| `kind` | type_alias | `include/js_trusted.h:56` | `typedef struct jt_ws_op { int kind;` |
| `null` | function | `include/js_trusted.h:24` | `* noopener semantics: it returns null (no cross-window reference, so no same-origin * channel) and only records up...` |
| `parent` | function | `include/js_trusted.h:69` | `* socket: the object records operations for the parent (jt_take_ws). */ jd_status jt_enable_ws(js_context *ctx);` |
| `realm` | function | `include/js_trusted.h:96` | `* runs in its own realm (js_install_realms) of this context's runtime, inside the * same confined process and...` |
| `FREEDOM_LINK_NAV_H` | macro | `include/link_nav.h:2` | `#define FREEDOM_LINK_NAV_H` |
| `LN_MAX_FRAGMENT` | macro | `include/link_nav.h:38` | `#define LN_MAX_FRAGMENT` |
| `LN_MAX_TARGET` | macro | `include/link_nav.h:33` | `#define LN_MAX_TARGET` |
| `action` | type_alias | `include/link_nav.h:61` | `typedef struct ln_result { ln_action action;` |
| `dropped` | function | `include/link_nav.h:36` | `* A longer fragment is dropped (stored as "");` |
| `ln_action` | enum | `include/link_nav.h:40` | `` |
| `ln_block_reason` | enum | `include/link_nav.h:54` | `` |
| `ln_block_reason_text` | function | `include/link_nav.h:85` | `const char *ln_block_reason_text(ln_block_reason reason);` |
| `ln_result` | struct | `include/link_nav.h:62` | `` |
| `ln_status` | enum | `include/link_nav.h:70` | `` |
| `ln_target_kind` | enum | `include/link_nav.h:46` | `` |
| `FREEDOM_LOCAL_STORE_H` | macro | `include/local_store.h:2` | `#define FREEDOM_LOCAL_STORE_H` |
| `LS_HEADER_LEN` | macro | `include/local_store.h:30` | `#define LS_HEADER_LEN` |
| `LS_KEY_LEN` | macro | `include/local_store.h:26` | `#define LS_KEY_LEN` |
| `LS_MAX_PLAINTEXT` | macro | `include/local_store.h:32` | `#define LS_MAX_PLAINTEXT` |
| `LS_NONCE_LEN` | macro | `include/local_store.h:28` | `#define LS_NONCE_LEN` |
| `LS_OVERHEAD` | macro | `include/local_store.h:31` | `#define LS_OVERHEAD` |
| `LS_SALT_LEN` | macro | `include/local_store.h:27` | `#define LS_SALT_LEN` |
| `LS_TAG_LEN` | macro | `include/local_store.h:29` | `#define LS_TAG_LEN` |
| `ls_aead` | enum | `include/local_store.h:34` | `` |
| `ls_free` | function | `include/local_store.h:80` | `void ls_free(uint8_t *buf, size_t len);` |
| `ls_status` | enum | `include/local_store.h:39` | `` |
| `FREEDOM_MEDIA_DECODER_H` | macro | `include/media_decoder.h:2` | `#define FREEDOM_MEDIA_DECODER_H` |
| `MD_MAX_CATCHUP_READS` | macro | `include/media_decoder.h:65` | `#define MD_MAX_CATCHUP_READS` |
| `MD_MAX_SEGMENT_BYTES` | macro | `include/media_decoder.h:46` | `#define MD_MAX_SEGMENT_BYTES` |
| `MD_PACE_MAX_LAG_MS` | macro | `include/media_decoder.h:58` | `#define MD_PACE_MAX_LAG_MS` |
| `MD_PACE_MAX_STEP_MS` | macro | `include/media_decoder.h:62` | `#define MD_PACE_MAX_STEP_MS` |
| `epoch_ms` | type_alias | `include/media_decoder.h:66` | `typedef struct md_pacer { uint64_t epoch_ms;` |
| `md_cmd` | enum | `include/media_decoder.h:29` | `` |
| `md_pace_due_ms` | function | `include/media_decoder.h:79` | `static inline uint64_t md_pace_due_ms(md_pacer *p, uint64_t now_ms,                              ...` |
| `md_pacer` | struct | `include/media_decoder.h:67` | `` |
| `md_resp` | enum | `include/media_decoder.h:38` | `` |
| `media_decoder_run` | function | `include/media_decoder.h:99` | `void media_decoder_run(int out_fd, int cmd_fd);` |
| `media_decoder_spawn` | function | `include/media_decoder.h:104` | `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd);` |
| `FREEDOM_NET_REALM_H` | macro | `include/net_realm.h:2` | `#define FREEDOM_NET_REALM_H` |
| `NR_ROUTE_BLOCKED` | function | `include/net_realm.h:57` | `* NR_ROUTE_BLOCKED (fail closed: never route what cannot be classified). A realm * whose proxy is not enabled =>...` |
| `address` | function | `include/net_realm.h:62` | `* and encrypts by its address (the I2P destination / onion key), so http over it is * not a downgrade. Currently...` |
| `nr_config` | struct | `include/net_realm.h:42` | `` |
| `nr_realm` | enum | `include/net_realm.h:29` | `` |
| `nr_realm_allows_http` | function | `include/net_realm.h:66` | `int nr_realm_allows_http(nr_realm r);` |
| `nr_realm_name` | function | `include/net_realm.h:69` | `const char *nr_realm_name(nr_realm r);` |
| `nr_route` | enum | `include/net_realm.h:35` | `` |
| `nr_route_name` | function | `include/net_realm.h:70` | `const char *nr_route_name(nr_route r);` |
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
| `CSS_LEN_UNSET` | function | `include/page_view.h:555` | `* CSS_LEN_UNSET (unset) / CSS_LEN_AUTO. z_index is signed, or CSS_LEN_UNSET. v1 * paints only position:relative (an...` |
| `FREEDOM_PAGE_VIEW_H` | macro | `include/page_view.h:2` | `#define FREEDOM_PAGE_VIEW_H` |
| `PV_BG_URL_MAX` | macro | `include/page_view.h:69` | `#define PV_BG_URL_MAX` |
| `PV_BR_CONT` | macro | `include/page_view.h:1195` | `#define PV_BR_CONT` |
| `PV_BR_EMPTY` | macro | `include/page_view.h:1194` | `#define PV_BR_EMPTY` |
| `PV_BSHADOW_LAYERS` | macro | `include/page_view.h:44` | `#define PV_BSHADOW_LAYERS` |
| `PV_CONT_DEPTH` | macro | `include/page_view.h:63` | `#define PV_CONT_DEPTH` |
| `PV_GRID_TRACKS` | macro | `include/page_view.h:58` | `#define PV_GRID_TRACKS` |
| `PV_LEN_AUTO` | macro | `include/page_view.h:54` | `#define PV_LEN_AUTO` |
| `PV_LEN_END` | macro | `include/page_view.h:55` | `#define PV_LEN_END` |
| `PV_LEN_UNSET` | macro | `include/page_view.h:53` | `#define PV_LEN_UNSET` |
| `PV_MAUTO_BOTTOM` | macro | `include/page_view.h:49` | `#define PV_MAUTO_BOTTOM` |
| `PV_MAUTO_LEFT` | macro | `include/page_view.h:46` | `#define PV_MAUTO_LEFT` |
| `PV_MAUTO_RIGHT` | macro | `include/page_view.h:47` | `#define PV_MAUTO_RIGHT` |
| `PV_MAUTO_TOP` | macro | `include/page_view.h:48` | `#define PV_MAUTO_TOP` |
| `PV_PH_HIDDEN` | macro | `include/page_view.h:1221` | `#define PV_PH_HIDDEN` |
| `PV_PH_THEME` | macro | `include/page_view.h:1220` | `#define PV_PH_THEME` |
| `PV_UA_BODY_MARGIN` | macro | `include/page_view.h:857` | `#define PV_UA_BODY_MARGIN` |
| `ancestors` | function | `include/page_view.h:1070` | `* itself by walking its ancestors (css_visibility, 0 = unset). * * An explicit value on the run WINS over the box...` |
| `bx_display` | function | `include/page_view.h:231` | `* bx_display (flex/grid);` |
| `cause` | function | `include/page_view.h:923` | `* cause (spec/css_drops.md). Builds no view and changes nothing -- it exists so * "what is this page's CSS losing?"...` |
| `container` | function | `include/page_view.h:230` | `* cont_id groups runs of one container (-1 = none);` |
| `declare` | function | `include/page_view.h:860` | `* margin the author did not declare (px or %), 0 on a declared side (the body's * own box, or nothing for 0, owns...` |
| `default` | function | `include/page_view.h:991` | `* structure is carried by default (not gated by caps.css). */ void pv_set_indent(pv_view *v, int indent);` |
| `form` | function | `include/page_view.h:954` | `* form (-1 if none);` |
| `itself` | function | `include/page_view.h:359` | `* by itself (bx_width_cap2);` |
| `kind` | type_alias | `include/page_view.h:121` | `typedef struct pv_run { pv_kind kind;` |
| `nonzero` | function | `include/page_view.h:872` | `* when nonzero (JS allowed for this page) the <noscript> subtree is suppressed. */ pv_status pv_build_ex(const...` |
| `order` | function | `include/page_view.h:295` | `* groups the runs of ONE floated element in document order (-1 = not in a float);` |
| `parent_id` | type_alias | `include/page_view.h:457` | `typedef struct pv_box_def { int parent_id;` |
| `parent_id` | type_alias | `include/page_view.h:786` | `typedef struct pv_cont_def { int parent_id;` |
| `policy` | function | `include/page_view.h:887` | `* TRUSTED parent under full network policy (spec/tab.md §8) -- page_view stays * pure and never fetches. The...` |
| `pv_at` | function | `include/page_view.h:1243` | `const pv_run *pv_at(const pv_view *v, size_t i);` |
| `pv_box_at` | function | `include/page_view.h:1248` | `const pv_box_def *pv_box_at(const pv_view *v, size_t i);` |
| `pv_box_count` | function | `include/page_view.h:1247` | `size_t pv_box_count(const pv_view *v);` |
| `pv_box_def` | struct | `include/page_view.h:457` | `` |
| `pv_computed` | type_alias | `include/page_view.h:908` | `typedef struct pv_computed pv_computed;` |
| `pv_computed_free` | function | `include/page_view.h:919` | `void pv_computed_free(pv_computed *pc);` |
| `pv_computed_get` | function | `include/page_view.h:916` | `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st, double *font_px, int *inherited_color);` |
| `pv_computed_new` | function | `include/page_view.h:909` | `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css, size_t extern_len...` |
| `pv_cont_at` | function | `include/page_view.h:1215` | `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i);` |
| `pv_cont_count` | function | `include/page_view.h:1214` | `size_t pv_cont_count(const pv_view *v);` |
| `pv_cont_def` | struct | `include/page_view.h:786` | `` |
| `pv_count` | function | `include/page_view.h:1242` | `size_t pv_count(const pv_view *v);` |
| `pv_form_method` | enum | `include/page_view.h:107` | `` |
| `pv_free` | function | `include/page_view.h:1239` | `void pv_free(pv_view *v);` |
| `pv_input_type` | enum | `include/page_view.h:87` | `` |
| `pv_kind` | enum | `include/page_view.h:71` | `` |
| `pv_new` | function | `include/page_view.h:935` | `pv_view *pv_new(void);` |
| `pv_placeholder_color` | function | `include/page_view.h:1232` | `int pv_placeholder_color(const css_style *ph);` |
| `pv_run` | struct | `include/page_view.h:121` | `` |
| `pv_set_bgcolor` | function | `include/page_view.h:1001` | `void pv_set_bgcolor(pv_view *v, int bg_rgb);` |
| `pv_set_block_id` | function | `include/page_view.h:1177` | `void pv_set_block_id(pv_view *v, int block_id);` |
| `pv_set_block_node` | function | `include/page_view.h:1191` | `void pv_set_block_node(pv_view *v, dom_node_id id);` |
| `pv_set_box` | function | `include/page_view.h:1156` | `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w, int box_center, int box_mt, int box_mb);` |
| `pv_set_box_maxw` | function | `include/page_view.h:1167` | `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct);` |
| `pv_set_box_pct` | function | `include/page_view.h:1162` | `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct, int box_mt_pct, int box_mb_pct);` |
| `pv_set_br_line` | function | `include/page_view.h:1199` | `void pv_set_br_line(pv_view *v, int br_line);` |
| `pv_set_color` | function | `include/page_view.h:994` | `void pv_set_color(pv_view *v, int fg_rgb);` |
| `pv_set_cont_box` | function | `include/page_view.h:1116` | `void pv_set_cont_box(pv_view *v, int cont_box_id);` |
| `pv_set_cont_item` | function | `include/page_view.h:1132` | `void pv_set_cont_item(pv_view *v, int cont_item);` |
| `pv_set_emphasis` | function | `include/page_view.h:986` | `void pv_set_emphasis(pv_view *v, int bold, int italic);` |
| `pv_set_flex` | function | `include/page_view.h:1125` | `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis, int flex_order, int flex_direction, int...` |
| `pv_set_flex_mauto` | function | `include/page_view.h:1128` | `void pv_set_flex_mauto(pv_view *v, int mauto);` |
| `pv_set_float` | function | `include/page_view.h:1146` | `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear, int float_ml, int float_ml_pct, int...` |
| `pv_set_float_w` | function | `include/page_view.h:1143` | `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box, int float_ow, int float_ow_pct, int...` |
| `pv_set_grad_text` | function | `include/page_view.h:1086` | `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4);` |
| `pv_set_grid` | function | `include/page_view.h:1117` | `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span);` |
| `pv_set_grid_area` | function | `include/page_view.h:1106` | `void pv_set_grid_area(pv_view *v, int row_start, int col_start);` |
| `pv_set_grid_rows` | function | `include/page_view.h:1107` | `void pv_set_grid_rows(pv_view *v, int grid_rows);` |
| `pv_set_input_checked` | function | `include/page_view.h:1219` | `void pv_set_input_checked(pv_view *v, int checked);` |
| `pv_set_input_placeholder` | function | `include/page_view.h:1223` | `void pv_set_input_placeholder(pv_view *v, int ph_color);` |
| `pv_set_input_select_opts` | function | `include/page_view.h:1236` | `void pv_set_input_select_opts(pv_view *v, const char *select_opts);` |
| `pv_set_justify_self` | function | `include/page_view.h:1188` | `void pv_set_justify_self(pv_view *v, int justify_self);` |
| `pv_set_node_id` | function | `include/page_view.h:1172` | `void pv_set_node_id(pv_view *v, dom_node_id node_id);` |
| `pv_set_oof` | function | `include/page_view.h:1185` | `void pv_set_oof(pv_view *v, int oof);` |
| `pv_set_own_box` | function | `include/page_view.h:1181` | `void pv_set_own_box(pv_view *v, int box_id);` |
| `pv_set_row_span` | function | `include/page_view.h:1102` | `void pv_set_row_span(pv_view *v, int row_span);` |
| `pv_set_text_ext` | function | `include/page_view.h:1080` | `void pv_set_text_ext(pv_view *v, const pv_text_ext *e);` |
| `pv_set_text_style` | function | `include/page_view.h:1010` | `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs, int line_scale, int text_decoration);` |
| `pv_set_ua_tag` | function | `include/page_view.h:1112` | `void pv_set_ua_tag(pv_view *v, int ua_tag);` |
| `pv_status` | enum | `include/page_view.h:34` | `` |
| `pv_svg_append_root_attrs` | function | `include/page_view.h:1229` | `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs, size_t *out_len);` |
| `pv_text_ext` | struct | `include/page_view.h:1026` | `` |
| `pv_text_ext_reset` | function | `include/page_view.h:1065` | `void pv_text_ext_reset(pv_text_ext *e);` |
| `pv_view` | struct | `include/page_view.h:836` | `` |
| `resolved` | function | `include/page_view.h:879` | `* author CSS is still resolved (the presentation layer decides whether to apply it). * pv_build_ex is pv_build_full...` |
| `run` | function | `include/page_view.h:1089` | `* run (cont_id, the bx_display, the parsed gap/justify/cols, plus flex-wrap/ * row-gap/align-items). No-op on an...` |
| `scale` | function | `include/page_view.h:630` | `* scale(1)) and rotate in whole degrees (transform_rotate);` |
| `tree` | function | `include/page_view.h:671` | `* box tree (a mask covers its whole subtree);` |
| `word_spacing` | type_alias | `include/page_view.h:1026` | `typedef struct pv_text_ext { int font_family, text_transform, letter_spacing, word_spacing;` |
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
| `IMG_FAIL_OK` | function | `include/render_doc.h:357` | `* IMG_FAIL_OK (not a failure) or the reason is unknown. */ const char *rd_image_fail_label(img_fail_reason reason);` |
| `RD_IMAGE` | function | `include/render_doc.h:59` | `* RD_IMAGE (image src) and RD_INPUT (the owning form's action);` |
| `decision` | function | `include/render_doc.h:351` | `* decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never * NULL. */ const char...` |
| `default` | function | `include/render_doc.h:150` | `* default (layout is structure, not author styling, and leaks nothing to the * network) so the presentation layer...` |
| `form` | function | `include/render_doc.h:63` | `* form (-1 = none);` |
| `img_fail_reason` | enum | `include/render_doc.h:34` | `` |
| `kind` | type_alias | `include/render_doc.h:64` | `typedef struct rd_block { rd_kind kind;` |
| `list` | function | `include/render_doc.h:18` | `* inert display list (page_view) and the presentation orchestrator (the GUI and * the --headless writer). It decides...` |
| `rd_at` | function | `include/render_doc.h:319` | `const rd_block *rd_at(const rd_doc *d, size_t i);` |
| `rd_block` | struct | `include/render_doc.h:64` | `` |
| `rd_block_heading_level` | function | `include/render_doc.h:348` | `int rd_block_heading_level(const rd_block *b);` |
| `rd_block_tag` | function | `include/render_doc.h:341` | `const char *rd_block_tag(const rd_block *b);` |
| `rd_box_at` | function | `include/render_doc.h:324` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i);` |
| `rd_box_count` | function | `include/render_doc.h:323` | `size_t rd_box_count(const rd_doc *d);` |
| `rd_cont_at` | function | `include/render_doc.h:329` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i);` |
| `rd_cont_count` | function | `include/render_doc.h:328` | `size_t rd_cont_count(const rd_doc *d);` |
| `rd_count` | function | `include/render_doc.h:318` | `size_t rd_count(const rd_doc *d);` |
| `rd_doc` | struct | `include/render_doc.h:264` | `` |
| `rd_free` | function | `include/render_doc.h:315` | `void rd_free(rd_doc *d);` |
| `rd_input_invisible` | function | `include/render_doc.h:367` | `int rd_input_invisible(int input_type);` |
| `rd_input_label` | function | `include/render_doc.h:362` | `const char *rd_input_label(int input_type);` |
| `rd_kind` | enum | `include/render_doc.h:42` | `` |
| `rd_kind_name` | function | `include/render_doc.h:333` | `const char *rd_kind_name(rd_kind k);` |
| `rd_status` | enum | `include/render_doc.h:296` | `` |
| `rdp_images_warning` | function | `include/render_doc.h:305` | `* rdp_images_warning() is prepended so the user is always told. Each image * becomes an RD_IMAGE block whose...` |
| `to` | function | `include/render_doc.h:250` | `* belongs to (-1 = none);` |
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
| `rp_decision` | enum | `include/request_policy.h:21` | `` |
| `rp_host_of` | function | `include/request_policy.h:30` | `int rp_host_of(const char *url, char *out, size_t out_size);` |
| `rp_same_site` | function | `include/request_policy.h:37` | `int rp_same_site(const char *top_level_url, const char *request_url);` |
| `rp_site_of` | function | `include/request_policy.h:34` | `int rp_site_of(const char *host, char *out, size_t out_size);` |
| `EXCLUDED` | function | `include/secure_fetch.h:225` | `* cookies are EXCLUDED (network-only, never exposed to JS) and expired cookies skipped. * Only for a TRUSTED host...` |
| `FREEDOM_SECURE_FETCH_H` | macro | `include/secure_fetch.h:2` | `#define FREEDOM_SECURE_FETCH_H` |
| `SF_CONNECT_TIMEOUT_MS` | macro | `include/secure_fetch.h:208` | `#define SF_CONNECT_TIMEOUT_MS` |
| `SF_DEFAULT_KEX_GROUPS` | macro | `include/secure_fetch.h:158` | `#define SF_DEFAULT_KEX_GROUPS` |
| `SF_DEFAULT_MAX_BODY` | macro | `include/secure_fetch.h:184` | `#define SF_DEFAULT_MAX_BODY` |
| `SF_DEFAULT_MAX_REDIRECTS` | macro | `include/secure_fetch.h:210` | `#define SF_DEFAULT_MAX_REDIRECTS` |
| `SF_DEFAULT_TIMEOUT_MS` | macro | `include/secure_fetch.h:185` | `#define SF_DEFAULT_TIMEOUT_MS` |
| `SF_DEFAULT_USER_AGENT` | macro | `include/secure_fetch.h:183` | `#define SF_DEFAULT_USER_AGENT` |
| `SF_IMPERSONATE_KEX_GROUPS` | macro | `include/secure_fetch.h:167` | `#define SF_IMPERSONATE_KEX_GROUPS` |
| `SF_IMPERSONATE_TLS12_CIPHERS` | macro | `include/secure_fetch.h:172` | `#define SF_IMPERSONATE_TLS12_CIPHERS` |
| `SF_IMPERSONATE_TLS13_CIPHERS` | macro | `include/secure_fetch.h:168` | `#define SF_IMPERSONATE_TLS13_CIPHERS` |
| `SF_MAX_URL` | macro | `include/secure_fetch.h:211` | `#define SF_MAX_URL` |
| `SF_META_MAX` | macro | `include/secure_fetch.h:77` | `#define SF_META_MAX` |
| `SF_SUBRESOURCE_TIMEOUT_MS` | macro | `include/secure_fetch.h:209` | `#define SF_SUBRESOURCE_TIMEOUT_MS` |
| `SF_WS_MAX_MESSAGE` | macro | `include/secure_fetch.h:316` | `#define SF_WS_MAX_MESSAGE` |
| `bits` | function | `include/secure_fetch.h:334` | `* *flags receives CURLWS_* bits (text/binary/close/cont);` |
| `connection` | function | `include/secure_fetch.h:348` | `* on each connection (Zero Trust). Each target is re-validated and a downgrade * to http:// is refused. Exceeding...` |
| `exhausted` | function | `include/secure_fetch.h:379` | `* is exhausted (*next untouched). `allowlisted` enables the sovereignty rung. */ int sf_fallback_policy(sf_status...` |
| `policy` | type_alias | `include/secure_fetch.h:78` | `typedef struct sf_config { sf_policy policy;` |
| `sf_accept_language_or_default` | function | `include/secure_fetch.h:250` | `const char *sf_accept_language_or_default(const char *lang);` |
| `sf_chain_info` | struct | `include/secure_fetch.h:61` | `` |
| `sf_config` | struct | `include/secure_fetch.h:79` | `` |
| `sf_cookie_line_matches` | function | `include/secure_fetch.h:237` | `int sf_cookie_line_matches(const char *line, const char *host, const char *path, long now, char *out, size_t outsz);` |
| `sf_cookie_put` | function | `include/secure_fetch.h:232` | `void sf_cookie_put(const char *url, const char *namevalue);` |
| `sf_get` | function | `include/secure_fetch.h:357` | `* sf_get (Zero Trust): an insecure POST is not representable. Does not follow * redirects (the caller inspects...` |
| `sf_global_init` | function | `include/secure_fetch.h:219` | `void sf_global_init(void);` |
| `sf_header_value` | function | `include/secure_fetch.h:297` | `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz);` |
| `sf_impersonate_kex_groups` | function | `include/secure_fetch.h:254` | `const char *sf_impersonate_kex_groups(void);` |
| `sf_impersonate_tls13_ciphers` | function | `include/secure_fetch.h:255` | `const char *sf_impersonate_tls13_ciphers(void);` |
| `sf_is_redirect_code` | function | `include/secure_fetch.h:286` | `int sf_is_redirect_code(long http_code);` |
| `sf_policy` | enum | `include/secure_fetch.h:41` | `` |
| `sf_proxy_type` | enum | `include/secure_fetch.h:70` | `` |
| `sf_rcache_clear` | function | `include/secure_fetch.h:394` | `void sf_rcache_clear(void);` |
| `sf_rcache_get` | function | `include/secure_fetch.h:393` | `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap);` |
| `sf_rcache_put` | function | `include/secure_fetch.h:392` | `int sf_rcache_put(const char *from, const char *to, time_t now);` |
| `sf_rcache_set_backing` | function | `include/secure_fetch.h:403` | `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx);` |
| `sf_response` | struct | `include/secure_fetch.h:126` | `` |
| `sf_response_free` | function | `include/secure_fetch.h:368` | `void sf_response_free(sf_response *resp);` |
| `sf_status` | enum | `include/secure_fetch.h:24` | `` |
| `sf_user_agent_or_default` | function | `include/secure_fetch.h:246` | `const char *sf_user_agent_or_default(const char *ua);` |
| `sf_ws` | type_alias | `include/secure_fetch.h:317` | `typedef struct sf_ws sf_ws;` |
| `sf_ws_close` | function | `include/secure_fetch.h:344` | `void sf_ws_close(sf_ws *ws);` |
| `sf_ws_fd` | function | `include/secure_fetch.h:341` | `int sf_ws_fd(const sf_ws *ws);` |
| `skipped` | function | `include/secure_fetch.h:275` | `* skipped (a classical key exchange is accepted);` |
| `status` | type_alias | `include/secure_fetch.h:125` | `typedef struct sf_response { sf_status status;` |
| `validators` | function | `include/secure_fetch.h:18` | `* The security logic lives in pure validators (no I/O);` |
| `FREEDOM_SHM_SLOTS_H` | macro | `include/shm_slots.h:2` | `#define FREEDOM_SHM_SLOTS_H` |
| `SS_COUNT` | macro | `include/shm_slots.h:17` | `#define SS_COUNT` |
| `busy` | type_alias | `include/shm_slots.h:18` | `typedef struct ss_state { int busy[SS_COUNT];` |
| `ss_committed` | function | `include/shm_slots.h:41` | `static inline void ss_committed(ss_state *s, int i)` |
| `ss_init` | function | `include/shm_slots.h:24` | `static inline void ss_init(ss_state *s)` |
| `ss_released` | function | `include/shm_slots.h:49` | `static inline int ss_released(ss_state *s, int i)` |
| `ss_state` | struct | `include/shm_slots.h:19` | `` |
| `FREEDOM_SVG_PAINT_H` | macro | `include/svg_paint.h:2` | `#define FREEDOM_SVG_PAINT_H` |
| `svp_draw` | function | `include/svg_paint.h:31` | `void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, double h, int current_rgb);` |
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
| `TAB_MAX_INPUT` | macro | `include/tab.h:149` | `#define TAB_MAX_INPUT` |
| `bytes` | function | `include/tab.h:191` | `* so the parent can retain the bytes (spec/webfont.md b3b feeds them to the * @font-face loader as extern sheets)....` |
| `decode` | function | `include/tab.h:369` | `* could not decode (caller shows the placeholder), which is not a transport error. * TAB_ERR_* is reserved for...` |
| `exclusively` | function | `include/tab.h:242` | `* exclusively (tab_subreq_permitted). Default 0: zero fetches, Privacy by Default. */ void tab_set_css_allowed(tab...` |
| `granted` | function | `include/tab.h:343` | `* granted (allow.conf AND js.conf);` |
| `jar` | function | `include/tab.h:227` | `* the trusted parent read from its ephemeral network jar (sf_cookie_header_for). Only * meaningful for a trusted...` |
| `kind` | type_alias | `include/tab.h:68` | `typedef struct tab_ws_op { int kind;` |
| `origin` | function | `include/tab.h:234` | `* page origin (web_storage snapshot, copied). Used only when the load is trusted * (net granted);` |
| `out_status` | function | `include/tab.h:176` | `* On success return 0 and set *out_status (HTTP status), *out_body / *out_body_len * (malloc'd response bytes, tab...` |
| `popstate` | function | `include/tab.h:350` | `* popstate (+ hashchange) and re-derives the view like a click. */ tab_status tab_popstate(tab *t, int index...` |
| `replace` | type_alias | `include/tab.h:54` | `typedef struct tab_hist_op { int replace;` |
| `returned` | function | `include/tab.h:344` | `* returned (the page keeps its zeros). The worker re-checks the same condition. * g must be finished (jg_finish). */...` |
| `string` | function | `include/tab.h:294` | `* event_type is a JS event type string (e.g. "keydown", "input", "change"). * key is the keyboard key value (may be...` |
| `tab` | type_alias | `include/tab.h:46` | `typedef struct tab tab;` |
| `tab_alive` | function | `include/tab.h:382` | `int tab_alive(const tab *t);` |
| `tab_async_busy` | function | `include/tab.h:220` | `int tab_async_busy(const tab *t);` |
| `tab_async_fd` | function | `include/tab.h:214` | `* the completion is signalled on tab_async_fd (readable). The pipe to the worker is a single * channel, so EVERY...` |
| `tab_child_pid` | function | `include/tab.h:385` | `pid_t tab_child_pid(const tab *t);` |
| `tab_close` | function | `include/tab.h:388` | `void tab_close(tab *t);` |
| `tab_eval_result` | struct | `include/tab.h:128` | `` |
| `tab_eval_result_free` | function | `include/tab.h:392` | `void tab_eval_result_free(tab_eval_result *r);` |
| `tab_hist_op` | struct | `include/tab.h:54` | `` |
| `tab_image` | struct | `include/tab.h:141` | `` |
| `tab_image_free` | function | `include/tab.h:393` | `void tab_image_free(tab_image *img);` |
| `tab_last_subreq_stats` | function | `include/tab.h:261` | `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us);` |
| `tab_open` | function | `include/tab.h:157` | `* and reaches tab_open (the app and the test harness) must call this first. */ void tab_worker_dispatch(int argc...` |
| `tab_page` | struct | `include/tab.h:76` | `` |
| `tab_page_free` | function | `include/tab.h:391` | `void tab_page_free(tab_page *p);` |
| `tab_parse_worker_args` | function | `include/tab.h:164` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd);` |
| `tab_set_cookies` | function | `include/tab.h:231` | `void tab_set_cookies(tab *t, const char *cookies);` |
| `tab_set_css_sink` | function | `include/tab.h:200` | `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx);` |
| `tab_set_fetcher` | function | `include/tab.h:187` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx);` |
| `tab_set_identity` | function | `include/tab.h:255` | `void tab_set_identity(tab *t, const char *serialized);` |
| `tab_set_net_allowed` | function | `include/tab.h:205` | `void tab_set_net_allowed(tab *t, int allowed);` |
| `tab_set_op_net_budget_ms` | function | `include/tab.h:209` | `void tab_set_op_net_budget_ms(tab *t, int ms);` |
| `tab_set_storage` | function | `include/tab.h:236` | `void tab_set_storage(tab *t, const char *blob, size_t len);` |
| `tab_set_viewport_w` | function | `include/tab.h:250` | `void tab_set_viewport_w(tab *t, int px);` |
| `tab_status` | enum | `include/tab.h:31` | `` |
| `tab_subreq_permitted` | function | `include/tab.h:266` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method);` |
| `tab_worker_dispatch` | function | `include/tab.h:153` | `* Call tab_worker_dispatch(argc, argv) as the FIRST thing in main(): if argv is the * internal "--tab-worker <rfd>...` |
| `tab_ws_event_kind` | enum | `include/tab.h:65` | `` |
| `tab_ws_kind` | enum | `include/tab.h:61` | `` |
| `tab_ws_op` | struct | `include/tab.h:69` | `` |
| `view` | function | `include/tab.h:274` | `* <noscript> handling in the built view (off => fallback shown, on => suppressed) * and is where allowlisted...` |
| `width` | type_alias | `include/tab.h:141` | `typedef struct tab_image { uint32_t width;` |
| `FREEDOM_TEXT_CASE_H` | macro | `include/text_case.h:2` | `#define FREEDOM_TEXT_CASE_H` |
| `TC_SMALLCAPS_SCALE` | macro | `include/text_case.h:15` | `#define TC_SMALLCAPS_SCALE` |
| `cp` | function | `include/text_case.h:19` | `* cp (identity otherwise), so a transformed text keeps its length. */ uint32_t tc_upper(uint32_t cp);` |

Next: [SYMBOLS_p5.md](SYMBOLS_p5.md)
