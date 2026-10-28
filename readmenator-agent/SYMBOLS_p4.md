# Symbols (page 4 of 16)
Previous: [SYMBOLS_p3.md](SYMBOLS_p3.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `IDN_GEO_ACC_MIN` | macro | `include/identity.h:22` | `#define IDN_GEO_ACC_MIN` |
| `IDN_LANG_MAX` | macro | `include/identity.h:17` | `#define IDN_LANG_MAX` |
| `IDN_LANG_TAGS_MAX` | macro | `include/identity.h:18` | `#define IDN_LANG_TAGS_MAX` |
| `IDN_PAGE_MAX` | macro | `include/identity.h:20` | `#define IDN_PAGE_MAX` |
| `IDN_SERIAL_MAX` | macro | `include/identity.h:19` | `#define IDN_SERIAL_MAX` |
| `IDN_UA_MAX` | macro | `include/identity.h:16` | `#define IDN_UA_MAX` |
| `idn_accept_language` | function | `include/identity.h:58` | `size_t idn_accept_language(const idn_config *c, char *out, size_t cap);` |
| `idn_apply_query` | function | `include/identity.h:70` | `unsigned idn_apply_query(idn_config *c, const char *query);` |
| `idn_clear_geo` | function | `include/identity.h:54` | `void idn_clear_geo(idn_config *c);` |
| `idn_config` | struct | `include/identity.h:37` | `` |
| `idn_defaults` | function | `include/identity.h:45` | `void idn_defaults(idn_config *c);` |
| `idn_geo_mode` | enum | `include/identity.h:25` | `` |
| `idn_is_default` | function | `include/identity.h:48` | `int idn_is_default(const idn_config *c);` |
| `idn_parse` | function | `include/identity.h:67` | `void idn_parse(idn_config *c, const char *text);` |
| `idn_primary_language` | function | `include/identity.h:59` | `size_t idn_primary_language(const idn_config *c, char *out, size_t cap);` |
| `idn_render_page` | function | `include/identity.h:73` | `size_t idn_render_page(const idn_config *c, char *out, size_t cap);` |
| `idn_serialize` | function | `include/identity.h:63` | `size_t idn_serialize(const idn_config *c, char *out, size_t cap);` |
| `idn_set_geo` | function | `include/identity.h:53` | `int idn_set_geo(idn_config *c, double lat, double lon, double accuracy_m);` |
| `idn_set_languages` | function | `include/identity.h:52` | `int idn_set_languages(idn_config *c, const char *list);` |
| `idn_set_user_agent` | function | `include/identity.h:51` | `int idn_set_user_agent(idn_config *c, const char *ua);` |
| `idn_user_agent` | function | `include/identity.h:57` | `const char *idn_user_agent(const idn_config *c);` |
| `user_agent` | type_alias | `include/identity.h:36` | `typedef struct idn_config { char user_agent[IDN_UA_MAX];` |
| `FREEDOM_IMAGE_DECODE_H` | macro | `include/image_decode.h:2` | `#define FREEDOM_IMAGE_DECODE_H` |
| `IMG_MAX_DIM` | macro | `include/image_decode.h:65` | `#define IMG_MAX_DIM` |
| `IMG_MAX_PIXELS` | macro | `include/image_decode.h:66` | `#define IMG_MAX_PIXELS` |
| `decode` | function | `include/image_decode.h:92` | `* the declared dimensions BEFORE the full decode (anti-bomb), decodes to RGB and * expands to BGRA. Rejects non-JPEG...` |
| `guards` | function | `include/image_decode.h:25` | `* guards (in-memory source only, longjmp error manager so a bad stream never * calls exit(), dimension caps before...` |
| `img_dimensions_ok` | function | `include/image_decode.h:78` | `int img_dimensions_ok(uint32_t w, uint32_t h);` |
| `img_format` | enum | `include/image_decode.h:33` | `` |
| `img_format_name` | function | `include/image_decode.h:124` | `const char *img_format_name(img_format f);` |
| `img_pixels` | struct | `include/image_decode.h:56` | `` |
| `img_pixels_free` | function | `include/image_decode.h:121` | `void img_pixels_free(img_pixels *p);` |
| `img_status` | enum | `include/image_decode.h:41` | `` |
| `inputs` | function | `include/image_decode.h:81` | `* Degenerate inputs (<= 0) yield (0,0). Pure. */ void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h...` |
| `width` | type_alias | `include/image_decode.h:56` | `typedef struct img_pixels { uint32_t width;` |
| `FREEDOM_IMPORT_MAP_H` | macro | `include/import_map.h:2` | `#define FREEDOM_IMPORT_MAP_H` |
| `IM_MAX_ENTRIES` | macro | `include/import_map.h:18` | `#define IM_MAX_ENTRIES` |
| `IM_MAX_SCOPES` | macro | `include/import_map.h:19` | `#define IM_MAX_SCOPES` |
| `IM_MAX_TEXT` | macro | `include/import_map.h:17` | `#define IM_MAX_TEXT` |
| `algorithm` | function | `include/import_map.h:13` | `* resolution algorithm (scopes, exact and prefix matches). URL resolution is the * caller's (the same resolver the...` |
| `im_count` | function | `include/import_map.h:37` | `size_t im_count(const im_map *m);` |
| `im_free` | function | `include/import_map.h:40` | `void im_free(im_map *m);` |
| `im_map` | type_alias | `include/import_map.h:23` | `typedef struct im_map im_map;` |
| `im_resolve` | function | `include/import_map.h:33` | `int im_resolve(const im_map *m, const char *base, const char *specifier, im_url_fn resolve, void *ctx, char *out...` |
| `map` | function | `include/import_map.h:28` | `* map (fail closed = no mapping). NULL only on OOM. */ im_map *im_parse(const char *json, size_t len, const char...` |
| `FREEDOM_INTERP_H` | macro | `include/interp.h:2` | `#define FREEDOM_INTERP_H` |
| `IP_ITERATION_INFINITE` | macro | `include/interp.h:85` | `#define IP_ITERATION_INFINITE` |
| `IP_MAX_KEYFRAMES` | macro | `include/interp.h:68` | `#define IP_MAX_KEYFRAMES` |
| `ip_anim` | struct | `include/interp.h:101` | `` |
| `ip_anim_current` | function | `include/interp.h:131` | `double ip_anim_current(const ip_anim *a);` |
| `ip_anim_done` | function | `include/interp.h:134` | `int ip_anim_done(const ip_anim *a);` |
| `ip_anim_init` | function | `include/interp.h:121` | `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease, const ip_keyframe *kf, int n_kf, double...` |
| `ip_anim_tick` | function | `include/interp.h:128` | `int ip_anim_tick(ip_anim *a, double dt_ms);` |
| `ip_direction` | enum | `include/interp.h:87` | `` |
| `ip_ease` | function | `include/interp.h:48` | `double ip_ease(double t, const ip_ease_fn *fn);` |
| `ip_ease_fn` | struct | `include/interp.h:38` | `` |
| `ip_easing` | enum | `include/interp.h:25` | `` |
| `ip_fill_mode` | enum | `include/interp.h:94` | `` |
| `ip_interp` | function | `include/interp.h:62` | `double ip_interp(ip_val_kind kind, double a, double b, double t);` |
| `ip_keyframe` | struct | `include/interp.h:70` | `` |
| `ip_kf_interp` | function | `include/interp.h:78` | `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf, int n_kf, double pct);` |
| `ip_lerp` | function | `include/interp.h:60` | `double ip_lerp(double a, double b, double t);` |
| `ip_lerp_color` | function | `include/interp.h:61` | `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t);` |
| `ip_val_kind` | enum | `include/interp.h:54` | `` |
| `kind` | type_alias | `include/interp.h:37` | `typedef struct ip_ease_fn { ip_easing kind;` |
| `pct` | type_alias | `include/interp.h:69` | `typedef struct ip_keyframe { double pct;` |
| `val_kind` | type_alias | `include/interp.h:100` | `typedef struct ip_anim { ip_val_kind val_kind;` |
| `FREEDOM_JS_DOM_H` | macro | `include/js_dom.h:2` | `#define FREEDOM_JS_DOM_H` |
| `JD_IFRAME_TRACK_MAX` | macro | `include/js_dom.h:40` | `#define JD_IFRAME_TRACK_MAX` |
| `JD_REPL_CSS_MAX` | macro | `include/js_dom.h:79` | `#define JD_REPL_CSS_MAX` |
| `URLs` | function | `include/js_dom.h:229` | `* video URLs (.m3u8 then .mp4 patterns), and creates <video> elements in the document for * any found. Does NOT...` |
| `getComputedStyle` | function | `include/js_dom.h:108` | `* getComputedStyle (spec/js_computed_style.md). fn writes the computed value of the * kebab-case `prop` of element h...` |
| `global` | function | `include/js_dom.h:73` | `* globals: page scripts never see them and an existing page global (jQuery's `$`) is * never replaced. Read-only...` |
| `host` | function | `include/js_dom.h:163` | `* for a trusted host (allow.conf AND js.conf);` |
| `jd_click_state` | type_alias | `include/js_dom.h:35` | `typedef struct jd_click_state jd_click_state;` |
| `jd_click_state_free` | function | `include/js_dom.h:118` | `* jd_click_state_free(). Bound to one context via jd_install_events(). */ jd_click_state *jd_click_state_new(void);` |
| `jd_flush_custom_elements` | function | `include/js_dom.h:254` | `void jd_flush_custom_elements(js_context *ctx);` |
| `jd_get_cookies` | function | `include/js_dom.h:174` | `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz);` |
| `jd_iframe_track` | struct | `include/js_dom.h:41` | `` |
| `jd_install_repl_api` | function | `include/js_dom.h:82` | `* jd_install_repl_api (the shim reads and deletes the carrier global, so a page script never * sees it). css == NULL...` |
| `jd_opaque` | struct | `include/js_dom.h:46` | `` |
| `jd_process_iframes` | function | `include/js_dom.h:222` | `* BEFORE jd_process_iframes() (so iframes are in the DOM for it to process). * ctx == NULL => JD_ERR_NULL_ARG. */...` |
| `jd_status` | enum | `include/js_dom.h:25` | `` |
| `jd_video_from_scripts` | function | `include/js_dom.h:243` | `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts, const size_t *script_lens, size_t...` |
| `opaque` | function | `include/js_dom.h:66` | `* the engine runtime opaque (unreachable from script);` |
| `out_status` | function | `include/js_dom.h:182` | `* On success returns 0 and sets *out_status (HTTP status, 0 if unknown), *out_body / * *out_body_len (response...` |
| `place` | function | `include/js_dom.h:87` | `* configured place (spec/identity.md), no sensor, no network. Call it ONLY for a trusted host * with geolocation set...` |
| `preventDefault` | function | `include/js_dom.h:134` | `* preventDefault() was called, 1 if the default (form submission) should proceed. * ctx == NULL or no form found =>...` |
| `processed` | type_alias | `include/js_dom.h:41` | `typedef struct jd_iframe_track { dom_node_id processed[JD_IFRAME_TRACK_MAX];` |
| `run` | function | `include/js_dom.h:127` | `* run (no handler registered, or handlers ran without calling preventDefault()), * and 0 if a handler called...` |
| `FREEDOM_JS_ENV_H` | macro | `include/js_env.h:2` | `#define FREEDOM_JS_ENV_H` |
| `JE_READBACK_EXACT` | macro | `include/js_env.h:59` | `#define JE_READBACK_EXACT` |
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
| `JS_DEFAULT_STACK_LIMIT` | macro | `include/js_sandbox.h:70` | `#define JS_DEFAULT_STACK_LIMIT` |
| `JS_DEFAULT_TIME_BUDGET` | macro | `include/js_sandbox.h:71` | `#define JS_DEFAULT_TIME_BUDGET` |
| `JS_LOC_FILE_MAX` | macro | `include/js_sandbox.h:64` | `#define JS_LOC_FILE_MAX` |
| `JS_MAX_STACK_LIMIT` | macro | `include/js_sandbox.h:69` | `#define JS_MAX_STACK_LIMIT` |
| `JS_MIN_STACK_LIMIT` | macro | `include/js_sandbox.h:68` | `#define JS_MIN_STACK_LIMIT` |
| `JS_MODULE_BYTES_MAX` | macro | `include/js_sandbox.h:116` | `#define JS_MODULE_BYTES_MAX` |
| `JS_MODULE_MAX` | macro | `include/js_sandbox.h:115` | `#define JS_MODULE_MAX` |
| `JS_PROFILE_PERIOD_MS` | macro | `include/js_sandbox.h:165` | `#define JS_PROFILE_PERIOD_MS` |
| `JS_REALM_MAX` | macro | `include/js_sandbox.h:215` | `#define JS_REALM_MAX` |
| `JS_REJECT_MAX` | macro | `include/js_sandbox.h:218` | `#define JS_REJECT_MAX` |
| `JS_THROW_SLOTS` | macro | `include/js_sandbox.h:174` | `#define JS_THROW_SLOTS` |
| `global` | function | `include/js_sandbox.h:181` | `* Freebug REPL installs: its shim takes them once and deletes them from the global (like * __netLog), because the...` |
| `handle` | function | `include/js_sandbox.h:198` | `* as an opaque handle (so this header stays free of backend types), or NULL. * Valid only while ctx is alive....` |
| `js_context` | type_alias | `include/js_sandbox.h:47` | `typedef struct js_context js_context;` |
| `js_context_free` | function | `include/js_sandbox.h:96` | `void js_context_free(js_context *ctx);` |
| `js_limits` | struct | `include/js_sandbox.h:39` | `` |
| `js_loc_from_stack` | function | `include/js_sandbox.h:150` | `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap, int *line, int *col);` |
| `js_prime_stack_limit` | function | `include/js_sandbox.h:79` | `void js_prime_stack_limit(void);` |
| `js_profile_enable` | function | `include/js_sandbox.h:166` | `void js_profile_enable(js_context *ctx);` |
| `js_profile_report` | function | `include/js_sandbox.h:167` | `size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n);` |
| `js_pump_jobs` | function | `include/js_sandbox.h:195` | `int js_pump_jobs(js_context *ctx, int max_jobs);` |
| `js_result` | struct | `include/js_sandbox.h:49` | `` |
| `js_result_free` | function | `include/js_sandbox.h:187` | `void js_result_free(js_result *res);` |
| `js_set_current_script` | function | `include/js_sandbox.h:207` | `void js_set_current_script(js_context *ctx, const char *src, const char *type);` |
| `js_set_module_host` | function | `include/js_sandbox.h:129` | `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve, js_module_fetch_fn fetch, void *host);` |
| `js_set_time_budget` | function | `include/js_sandbox.h:158` | `void js_set_time_budget(js_context *ctx, uint64_t budget_ms);` |
| `js_stack_limit_for` | function | `include/js_sandbox.h:75` | `size_t js_stack_limit_for(size_t soft_stack);` |
| `js_status` | enum | `include/js_sandbox.h:24` | `` |
| `js_throws_report` | function | `include/js_sandbox.h:176` | `size_t js_throws_report(js_context *ctx, char *out, size_t cap, size_t top_n);` |
| `loaded` | function | `include/js_sandbox.h:124` | `* NULL when it cannot be loaded (policy refusal, network error, not JavaScript). */ typedef char...` |
| `max_source_bytes` | type_alias | `include/js_sandbox.h:39` | `typedef struct js_limits { size_t max_source_bytes;` |
| `out` | function | `include/js_sandbox.h:163` | `* into out (NUL-terminated, truncated at cap);` |
| `silently` | function | `include/js_sandbox.h:171` | `* fails silently (an exception swallowed by a try/catch, a rejected promise nobody awaits) shows * its real first...` |
| `status` | type_alias | `include/js_sandbox.h:48` | `typedef struct js_result { js_status status;` |
| `FREEDOM_JS_TRUSTED_H` | macro | `include/js_trusted.h:2` | `#define FREEDOM_JS_TRUSTED_H` |
| `JT_WS_MAX` | macro | `include/js_trusted.h:46` | `#define JT_WS_MAX` |
| `JT_WS_MAX_BYTES` | macro | `include/js_trusted.h:48` | `#define JT_WS_MAX_BYTES` |
| `JT_WS_MAX_OPS` | macro | `include/js_trusted.h:47` | `#define JT_WS_MAX_OPS` |
| `jt_take_opens` | function | `include/js_trusted.h:42` | `char *jt_take_opens(js_context *ctx);` |
| `jt_take_storage` | function | `include/js_trusted.h:104` | `int jt_take_storage(js_context *ctx, char **out, size_t *len);` |
| `jt_take_ws` | function | `include/js_trusted.h:86` | `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap);` |
| `jt_ws_event` | function | `include/js_trusted.h:92` | `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len);` |
| `jt_ws_event_kind` | enum | `include/js_trusted.h:68` | `` |
| `jt_ws_kind` | enum | `include/js_trusted.h:50` | `` |
| `jt_ws_op` | struct | `include/js_trusted.h:61` | `` |
| `jt_ws_ops_free` | function | `include/js_trusted.h:87` | `void jt_ws_ops_free(jt_ws_op *ops, size_t n);` |
| `kind` | type_alias | `include/js_trusted.h:60` | `typedef struct jt_ws_op { int kind;` |
| `null` | function | `include/js_trusted.h:24` | `* noopener semantics: it returns null (no cross-window reference, so no same-origin * channel) and only records up...` |
| `parent` | function | `include/js_trusted.h:80` | `* socket: the object records operations for the parent (jt_take_ws). */ jd_status jt_enable_ws(js_context *ctx);` |
| `realm` | function | `include/js_trusted.h:107` | `* runs in its own realm (js_install_realms) of this context's runtime, inside the * same confined process and...` |
| `FREEDOM_LAZY_LOAD_H` | macro | `include/lazy_load.h:2` | `#define FREEDOM_LAZY_LOAD_H` |
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
| `CSS_LEN_UNSET` | function | `include/page_view.h:558` | `* CSS_LEN_UNSET (unset) / CSS_LEN_AUTO. z_index is signed, or CSS_LEN_UNSET. v1 * paints only position:relative (an...` |
| `FREEDOM_PAGE_VIEW_H` | macro | `include/page_view.h:2` | `#define FREEDOM_PAGE_VIEW_H` |
| `PV_BG_URL_MAX` | macro | `include/page_view.h:69` | `#define PV_BG_URL_MAX` |
| `PV_BR_CONT` | macro | `include/page_view.h:1198` | `#define PV_BR_CONT` |
| `PV_BR_EMPTY` | macro | `include/page_view.h:1197` | `#define PV_BR_EMPTY` |
| `PV_BSHADOW_LAYERS` | macro | `include/page_view.h:44` | `#define PV_BSHADOW_LAYERS` |
| `PV_CONT_DEPTH` | macro | `include/page_view.h:63` | `#define PV_CONT_DEPTH` |
| `PV_FRAME_SCHEME` | macro | `include/page_view.h:1256` | `#define PV_FRAME_SCHEME` |
| `PV_GRID_TRACKS` | macro | `include/page_view.h:58` | `#define PV_GRID_TRACKS` |
| `PV_LEN_AUTO` | macro | `include/page_view.h:54` | `#define PV_LEN_AUTO` |
| `PV_LEN_END` | macro | `include/page_view.h:55` | `#define PV_LEN_END` |
| `PV_LEN_UNSET` | macro | `include/page_view.h:53` | `#define PV_LEN_UNSET` |
| `PV_MAUTO_BOTTOM` | macro | `include/page_view.h:49` | `#define PV_MAUTO_BOTTOM` |
| `PV_MAUTO_LEFT` | macro | `include/page_view.h:46` | `#define PV_MAUTO_LEFT` |
| `PV_MAUTO_RIGHT` | macro | `include/page_view.h:47` | `#define PV_MAUTO_RIGHT` |
| `PV_MAUTO_TOP` | macro | `include/page_view.h:48` | `#define PV_MAUTO_TOP` |
| `PV_PH_HIDDEN` | macro | `include/page_view.h:1224` | `#define PV_PH_HIDDEN` |
| `PV_PH_THEME` | macro | `include/page_view.h:1223` | `#define PV_PH_THEME` |
| `PV_UA_BODY_MARGIN` | macro | `include/page_view.h:860` | `#define PV_UA_BODY_MARGIN` |
| `ancestors` | function | `include/page_view.h:1073` | `* itself by walking its ancestors (css_visibility, 0 = unset). * * An explicit value on the run WINS over the box...` |
| `bx_display` | function | `include/page_view.h:231` | `* bx_display (flex/grid);` |
| `cause` | function | `include/page_view.h:926` | `* cause (spec/css_drops.md). Builds no view and changes nothing -- it exists so * "what is this page's CSS losing?"...` |
| `container` | function | `include/page_view.h:230` | `* cont_id groups runs of one container (-1 = none);` |
| `declare` | function | `include/page_view.h:863` | `* margin the author did not declare (px or %), 0 on a declared side (the body's * own box, or nothing for 0, owns...` |
| `default` | function | `include/page_view.h:994` | `* structure is carried by default (not gated by caps.css). */ void pv_set_indent(pv_view *v, int indent);` |
| `form` | function | `include/page_view.h:957` | `* form (-1 if none);` |
| `itself` | function | `include/page_view.h:359` | `* by itself (bx_width_cap2);` |
| `kind` | type_alias | `include/page_view.h:121` | `typedef struct pv_run { pv_kind kind;` |
| `nonzero` | function | `include/page_view.h:875` | `* when nonzero (JS allowed for this page) the <noscript> subtree is suppressed. */ pv_status pv_build_ex(const...` |
| `order` | function | `include/page_view.h:295` | `* groups the runs of ONE floated element in document order (-1 = not in a float);` |
| `parent_id` | type_alias | `include/page_view.h:460` | `typedef struct pv_box_def { int parent_id;` |
| `parent_id` | type_alias | `include/page_view.h:789` | `typedef struct pv_cont_def { int parent_id;` |
| `policy` | function | `include/page_view.h:890` | `* TRUSTED parent under full network policy (spec/tab.md §8) -- page_view stays * pure and never fetches. The...` |
| `pv_at` | function | `include/page_view.h:1246` | `const pv_run *pv_at(const pv_view *v, size_t i);` |
| `pv_box_at` | function | `include/page_view.h:1251` | `const pv_box_def *pv_box_at(const pv_view *v, size_t i);` |
| `pv_box_count` | function | `include/page_view.h:1250` | `size_t pv_box_count(const pv_view *v);` |
| `pv_box_def` | struct | `include/page_view.h:460` | `` |
| `pv_computed` | type_alias | `include/page_view.h:911` | `typedef struct pv_computed pv_computed;` |
| `pv_computed_free` | function | `include/page_view.h:922` | `void pv_computed_free(pv_computed *pc);` |
| `pv_computed_get` | function | `include/page_view.h:919` | `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st, double *font_px, int *inherited_color);` |
| `pv_computed_new` | function | `include/page_view.h:912` | `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css, size_t extern_len...` |
| `pv_cont_at` | function | `include/page_view.h:1218` | `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i);` |
| `pv_cont_count` | function | `include/page_view.h:1217` | `size_t pv_cont_count(const pv_view *v);` |
| `pv_cont_def` | struct | `include/page_view.h:789` | `` |
| `pv_count` | function | `include/page_view.h:1245` | `size_t pv_count(const pv_view *v);` |
| `pv_form_method` | enum | `include/page_view.h:107` | `` |
| `pv_free` | function | `include/page_view.h:1242` | `void pv_free(pv_view *v);` |
| `pv_input_type` | enum | `include/page_view.h:87` | `` |
| `pv_kind` | enum | `include/page_view.h:71` | `` |
| `pv_new` | function | `include/page_view.h:938` | `pv_view *pv_new(void);` |
| `pv_placeholder_color` | function | `include/page_view.h:1235` | `int pv_placeholder_color(const css_style *ph);` |
| `pv_run` | struct | `include/page_view.h:121` | `` |
| `pv_set_bgcolor` | function | `include/page_view.h:1004` | `void pv_set_bgcolor(pv_view *v, int bg_rgb);` |
| `pv_set_block_id` | function | `include/page_view.h:1180` | `void pv_set_block_id(pv_view *v, int block_id);` |
| `pv_set_block_node` | function | `include/page_view.h:1194` | `void pv_set_block_node(pv_view *v, dom_node_id id);` |
| `pv_set_box` | function | `include/page_view.h:1159` | `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w, int box_center, int box_mt, int box_mb);` |
| `pv_set_box_maxw` | function | `include/page_view.h:1170` | `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct);` |
| `pv_set_box_pct` | function | `include/page_view.h:1165` | `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct, int box_mt_pct, int box_mb_pct);` |
| `pv_set_br_line` | function | `include/page_view.h:1202` | `void pv_set_br_line(pv_view *v, int br_line);` |
| `pv_set_color` | function | `include/page_view.h:997` | `void pv_set_color(pv_view *v, int fg_rgb);` |
| `pv_set_cont_box` | function | `include/page_view.h:1119` | `void pv_set_cont_box(pv_view *v, int cont_box_id);` |
| `pv_set_cont_item` | function | `include/page_view.h:1135` | `void pv_set_cont_item(pv_view *v, int cont_item);` |
| `pv_set_emphasis` | function | `include/page_view.h:989` | `void pv_set_emphasis(pv_view *v, int bold, int italic);` |
| `pv_set_flex` | function | `include/page_view.h:1128` | `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis, int flex_order, int flex_direction, int...` |
| `pv_set_flex_mauto` | function | `include/page_view.h:1131` | `void pv_set_flex_mauto(pv_view *v, int mauto);` |
| `pv_set_float` | function | `include/page_view.h:1149` | `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear, int float_ml, int float_ml_pct, int...` |
| `pv_set_float_w` | function | `include/page_view.h:1146` | `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box, int float_ow, int float_ow_pct, int...` |
| `pv_set_grad_text` | function | `include/page_view.h:1089` | `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4);` |
| `pv_set_grid` | function | `include/page_view.h:1120` | `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span);` |
| `pv_set_grid_area` | function | `include/page_view.h:1109` | `void pv_set_grid_area(pv_view *v, int row_start, int col_start);` |
| `pv_set_grid_rows` | function | `include/page_view.h:1110` | `void pv_set_grid_rows(pv_view *v, int grid_rows);` |
| `pv_set_input_checked` | function | `include/page_view.h:1222` | `void pv_set_input_checked(pv_view *v, int checked);` |
| `pv_set_input_placeholder` | function | `include/page_view.h:1226` | `void pv_set_input_placeholder(pv_view *v, int ph_color);` |
| `pv_set_input_select_opts` | function | `include/page_view.h:1239` | `void pv_set_input_select_opts(pv_view *v, const char *select_opts);` |
| `pv_set_justify_self` | function | `include/page_view.h:1191` | `void pv_set_justify_self(pv_view *v, int justify_self);` |
| `pv_set_node_id` | function | `include/page_view.h:1175` | `void pv_set_node_id(pv_view *v, dom_node_id node_id);` |
| `pv_set_oof` | function | `include/page_view.h:1188` | `void pv_set_oof(pv_view *v, int oof);` |
| `pv_set_own_box` | function | `include/page_view.h:1184` | `void pv_set_own_box(pv_view *v, int box_id);` |
| `pv_set_row_span` | function | `include/page_view.h:1105` | `void pv_set_row_span(pv_view *v, int row_span);` |
| `pv_set_text_ext` | function | `include/page_view.h:1083` | `void pv_set_text_ext(pv_view *v, const pv_text_ext *e);` |
| `pv_set_text_style` | function | `include/page_view.h:1013` | `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs, int line_scale, int text_decoration);` |
| `pv_set_ua_tag` | function | `include/page_view.h:1115` | `void pv_set_ua_tag(pv_view *v, int ua_tag);` |
| `pv_status` | enum | `include/page_view.h:34` | `` |
| `pv_svg_append_root_attrs` | function | `include/page_view.h:1232` | `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs, size_t *out_len);` |
| `pv_text_ext` | struct | `include/page_view.h:1029` | `` |
| `pv_text_ext_reset` | function | `include/page_view.h:1068` | `void pv_text_ext_reset(pv_text_ext *e);` |
| `pv_view` | struct | `include/page_view.h:839` | `` |
| `resolved` | function | `include/page_view.h:882` | `* author CSS is still resolved (the presentation layer decides whether to apply it). * pv_build_ex is pv_build_full...` |
| `run` | function | `include/page_view.h:1092` | `* run (cont_id, the bx_display, the parsed gap/justify/cols, plus flex-wrap/ * row-gap/align-items). No-op on an...` |
| `scale` | function | `include/page_view.h:633` | `* scale(1)) and rotate in whole degrees (transform_rotate);` |
| `tree` | function | `include/page_view.h:674` | `* box tree (a mask covers its whole subtree);` |
| `word_spacing` | type_alias | `include/page_view.h:1029` | `typedef struct pv_text_ext { int font_family, text_transform, letter_spacing, word_spacing;` |
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
| `IMG_FAIL_OK` | function | `include/render_doc.h:358` | `* IMG_FAIL_OK (not a failure) or the reason is unknown. */ const char *rd_image_fail_label(img_fail_reason reason);` |
| `RD_IMAGE` | function | `include/render_doc.h:59` | `* RD_IMAGE (image src) and RD_INPUT (the owning form's action);` |
| `decision` | function | `include/render_doc.h:352` | `* decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never * NULL. */ const char...` |
| `default` | function | `include/render_doc.h:151` | `* default (layout is structure, not author styling, and leaks nothing to the * network) so the presentation layer...` |
| `form` | function | `include/render_doc.h:63` | `* form (-1 = none);` |
| `img_fail_reason` | enum | `include/render_doc.h:34` | `` |
| `kind` | type_alias | `include/render_doc.h:64` | `typedef struct rd_block { rd_kind kind;` |
| `list` | function | `include/render_doc.h:18` | `* inert display list (page_view) and the presentation orchestrator (the GUI and * the --headless writer). It decides...` |
| `rd_at` | function | `include/render_doc.h:320` | `const rd_block *rd_at(const rd_doc *d, size_t i);` |
| `rd_block` | struct | `include/render_doc.h:64` | `` |
| `rd_block_heading_level` | function | `include/render_doc.h:349` | `int rd_block_heading_level(const rd_block *b);` |
| `rd_block_tag` | function | `include/render_doc.h:342` | `const char *rd_block_tag(const rd_block *b);` |
| `rd_box_at` | function | `include/render_doc.h:325` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i);` |
| `rd_box_count` | function | `include/render_doc.h:324` | `size_t rd_box_count(const rd_doc *d);` |
| `rd_cont_at` | function | `include/render_doc.h:330` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i);` |
| `rd_cont_count` | function | `include/render_doc.h:329` | `size_t rd_cont_count(const rd_doc *d);` |
| `rd_count` | function | `include/render_doc.h:319` | `size_t rd_count(const rd_doc *d);` |
| `rd_doc` | struct | `include/render_doc.h:265` | `` |
| `rd_free` | function | `include/render_doc.h:316` | `void rd_free(rd_doc *d);` |
| `rd_input_invisible` | function | `include/render_doc.h:368` | `int rd_input_invisible(int input_type);` |
| `rd_input_label` | function | `include/render_doc.h:363` | `const char *rd_input_label(int input_type);` |
| `rd_kind` | enum | `include/render_doc.h:42` | `` |
| `rd_kind_name` | function | `include/render_doc.h:334` | `const char *rd_kind_name(rd_kind k);` |
| `rd_status` | enum | `include/render_doc.h:297` | `` |
| `rdp_images_warning` | function | `include/render_doc.h:306` | `* rdp_images_warning() is prepended so the user is always told. Each image * becomes an RD_IMAGE block whose...` |
| `to` | function | `include/render_doc.h:251` | `* belongs to (-1 = none);` |
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
| `EXCLUDED` | function | `include/secure_fetch.h:233` | `* cookies are EXCLUDED (network-only, never exposed to JS) and expired cookies skipped. * Only for a TRUSTED host...` |
| `FREEDOM_SECURE_FETCH_H` | macro | `include/secure_fetch.h:2` | `#define FREEDOM_SECURE_FETCH_H` |
| `SF_CONNECT_TIMEOUT_MS` | macro | `include/secure_fetch.h:216` | `#define SF_CONNECT_TIMEOUT_MS` |
| `SF_DEFAULT_KEX_GROUPS` | macro | `include/secure_fetch.h:166` | `#define SF_DEFAULT_KEX_GROUPS` |
| `SF_DEFAULT_MAX_BODY` | macro | `include/secure_fetch.h:192` | `#define SF_DEFAULT_MAX_BODY` |
| `SF_DEFAULT_MAX_REDIRECTS` | macro | `include/secure_fetch.h:218` | `#define SF_DEFAULT_MAX_REDIRECTS` |
| `SF_DEFAULT_TIMEOUT_MS` | macro | `include/secure_fetch.h:193` | `#define SF_DEFAULT_TIMEOUT_MS` |
| `SF_DEFAULT_USER_AGENT` | macro | `include/secure_fetch.h:191` | `#define SF_DEFAULT_USER_AGENT` |
| `SF_IMPERSONATE_KEX_GROUPS` | macro | `include/secure_fetch.h:175` | `#define SF_IMPERSONATE_KEX_GROUPS` |
| `SF_IMPERSONATE_TLS12_CIPHERS` | macro | `include/secure_fetch.h:180` | `#define SF_IMPERSONATE_TLS12_CIPHERS` |
| `SF_IMPERSONATE_TLS13_CIPHERS` | macro | `include/secure_fetch.h:176` | `#define SF_IMPERSONATE_TLS13_CIPHERS` |
| `SF_MAX_URL` | macro | `include/secure_fetch.h:219` | `#define SF_MAX_URL` |
| `SF_META_MAX` | macro | `include/secure_fetch.h:77` | `#define SF_META_MAX` |
| `SF_RESPONSE_HEADERS_MAX` | macro | `include/secure_fetch.h:78` | `#define SF_RESPONSE_HEADERS_MAX` |

Next: [SYMBOLS_p5.md](SYMBOLS_p5.md)
