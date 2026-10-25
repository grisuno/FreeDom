# Symbols (page 8 of 16)
Previous: [SYMBOLS_p7.md](SYMBOLS_p7.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `jdx_install` | function | `src/js_dom_ext.c:1200` | `int jdx_install(JSContext *ctx)` |
| `registration` | function | `src/js_dom_ext.c:385` | `* registration (options, attributeFilter, subtree) and delivered in one microtask. An  * observer...` |
| `run` | function | `src/js_dom_ext.c:1135` | `static int run(JSContext *ctx, const char *src, size_t len, const char *name)` |
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
| `FP_MIME_COUNT` | macro | `src/js_env.c:267` | `#define FP_MIME_COUNT` |
| `PERF_ORIGIN_EPOCH` | macro | `src/js_env.c:351` | `#define PERF_ORIGIN_EPOCH` |
| `_POSIX_C_SOURCE` | macro | `src/js_env.c:17` | `#define _POSIX_C_SOURCE` |
| `build_crypto` | function | `src/js_env.c:353` | `static int build_crypto(JSContext *ctx, JSValueConst global)` |
| `build_languages` | function | `src/js_env.c:174` | `static JSValue build_languages(JSContext *ctx, const char *langs)` |
| `build_navigator` | function | `src/js_env.c:197` | `static int build_navigator(JSContext *ctx, JSValueConst global, const char *ua_override,         ...` |
| `build_perf_navigation` | function | `src/js_env.c:395` | `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)` |
| `build_perf_timing` | function | `src/js_env.c:381` | `static int build_perf_timing(JSContext *ctx, JSValueConst perf)` |
| `build_performance` | function | `src/js_env.c:407` | `static int build_performance(JSContext *ctx, JSValueConst global)` |
| `build_readback_obj` | function | `src/js_env.c:491` | `static int build_readback_obj(JSContext *ctx, JSValueConst global,                               ...` |
| `build_screen` | function | `src/js_env.c:309` | `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)` |
| `def_fn` | function | `src/js_env.c:167` | `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,                   JSCFuncti...` |
| `def_int` | function | `src/js_env.c:163` | `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)` |
| `def_str` | function | `src/js_env.c:159` | `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)` |
| `def_val` | function | `src/js_env.c:153` | `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)` |
| `je_install` | function | `src/js_env.c:504` | `je_status je_install(js_context *ctx, int screen_w, int screen_h)` |
| `je_install_canvas` | function | `src/js_env.c:528` | `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)` |
| `je_install_identity` | function | `src/js_env.c:508` | `je_status je_install_identity(js_context *ctx, int screen_w, int screen_h,                       ...` |
| `m_date_now` | function | `src/js_env.c:49` | `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_empty_array` | function | `src/js_env.c:77` | `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,                              ...` |
| `m_get_random_values` | function | `src/js_env.c:85` | `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,                        ...` |
| `m_perf_now` | function | `src/js_env.c:57` | `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_random_uuid` | function | `src/js_env.c:125` | `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,                              ...` |
| `m_subtle_null` | function | `src/js_env.c:142` | `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,                              ...` |
| `make_readback` | function | `src/js_env.c:483` | `static JSValue make_readback(JSContext *ctx, uint64_t key)` |
| `methods` | function | `src/js_env.c:201` | `* capability methods (sendBeacon, spec/js_dom.md 7h) without touching any * fingerprintable field. An untrusted...` |
| `monotonic_ms` | function | `src/js_env.c:41` | `static double monotonic_ms(void)` |
| `override_date_now` | function | `src/js_env.c:439` | `static int override_date_now(JSContext *ctx, JSValueConst global)` |
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
| `jd_install_xhr` | function | `src/js_fetch.c:212` | `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)` |
| `jd_pack_ptr` | function | `src/js_fetch.c:28` | `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)` |
| `jd_unpack_ptr` | function | `src/js_fetch.c:33` | `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)` |
| `m_host_fetch` | function | `src/js_fetch.c:46` | `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,                             in...` |
| `send` | function | `src/js_fetch.c:92` | `* callbacks fire right after send();` |
| `task` | function | `src/js_fetch.c:188` | `* current task (the page never waits on it);` |
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
| `jg_find` | function | `src/js_geom.c:96` | `const jg_rect *jg_find(const jg_table *t, dom_node_id node)` |
| `jg_finish` | function | `src/js_geom.c:83` | `int jg_finish(jg_table *t)` |
| `jg_free` | function | `src/js_geom.c:21` | `void jg_free(jg_table *t)` |
| `jg_hash` | function | `src/js_geom.c:221` | `uint64_t jg_hash(const jg_table *t)` |
| `jg_init` | function | `src/js_geom.c:17` | `void jg_init(jg_table *t)` |
| `jg_wire_len` | function | `src/js_geom.c:163` | `size_t jg_wire_len(const jg_table *t)` |
| `push` | function | `src/js_geom.c:45` | `static int push(jg_table *t, dom_node_id node, int32_t x, int32_t y, int32_t w, int32_t h)` |
| `slot_of` | function | `src/js_geom.c:102` | `static uint32_t slot_of(dom_node_id n)` |
| `unite` | function | `src/js_geom.c:63` | `static int unite(jg_rect *a, const jg_rect *b)` |
| `jd_lp_set` | function | `src/js_location.c:24` | `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,                       const ...` |
| `jd_pop_state` | function | `src/js_location.c:250` | `int jd_pop_state(js_context *ctx, int index)` |
| `jd_set_location` | function | `src/js_location.c:139` | `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)` |
| `jd_take_history` | function | `src/js_location.c:219` | `char *jd_take_history(js_context *ctx, int *go)` |
| `jd_take_nav_request` | function | `src/js_location.c:173` | `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)` |
| `jl_m_hist_target` | function | `src/js_location.c:35` | `JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `FREEDOM_JS_LOCATION_INTERNAL_H` | macro | `src/js_location_internal.h:2` | `#define FREEDOM_JS_LOCATION_INTERNAL_H` |
| `header` | function | `src/js_location_internal.h:6` | `* stay out of every public header (include/ never sees quickjs.h). */ #include "quickjs.h" JSValue...` |
| `eq_ci` | function | `src/js_policy.c:12` | `static int eq_ci(const char *a, const char *b)` |
| `jsp_enabled` | function | `src/js_policy.c:22` | `bool jsp_enabled(jsp_mode mode, int host_allowlisted)` |
| `jsp_mode_from_str` | function | `src/js_policy.c:39` | `jsp_mode jsp_mode_from_str(const char *s)` |
| `jsp_mode_str` | function | `src/js_policy.c:51` | `const char *jsp_mode_str(jsp_mode mode)` |
| `jsp_present_trusted` | function | `src/js_policy.c:35` | `bool jsp_present_trusted(int host_allowlisted)` |
| `jsp_trusted` | function | `src/js_policy.c:31` | `bool jsp_trusted(bool js_enabled, int host_allowlisted)` |
| `JS_MODULE_URL_MAX` | macro | `src/js_sandbox.c:612` | `#define JS_MODULE_URL_MAX` |
| `_POSIX_C_SOURCE` | macro | `src/js_sandbox.c:12` | `#define _POSIX_C_SOURCE` |
| `arm_deadline` | function | `src/js_sandbox.c:411` | `static void arm_deadline(js_context *ctx, uint64_t budget_ms)` |
| `host_dup` | function | `src/js_sandbox.c:158` | `static char *host_dup(const char *src, size_t len)` |
| `is_ascii_digit` | function | `src/js_sandbox.c:186` | `static int is_ascii_digit(char c)` |
| `jm_calloc` | function | `src/js_sandbox.c:122` | `static void *jm_calloc(void *opaque, size_t count, size_t size)` |
| `jm_free` | function | `src/js_sandbox.c:132` | `static void jm_free(void *opaque, void *ptr)` |
| `jm_malloc` | function | `src/js_sandbox.c:114` | `static void *jm_malloc(void *opaque, size_t size)` |
| `jm_realloc` | function | `src/js_sandbox.c:138` | `static void *jm_realloc(void *opaque, void *ptr, size_t size)` |
| `jm_usable_size` | function | `src/js_sandbox.c:148` | `static size_t jm_usable_size(const void *ptr)` |
| `js_context` | struct | `src/js_sandbox.c:35` | `` |
| `js_context_free` | function | `src/js_sandbox.c:399` | `void js_context_free(js_context *ctx)` |
| `js_context_new` | function | `src/js_sandbox.c:359` | `js_status js_context_new(const js_limits *lim, js_context **out)` |
| `js_context_raw` | function | `src/js_sandbox.c:607` | `void *js_context_raw(js_context *ctx)` |
| `js_eval` | function | `src/js_sandbox.c:431` | `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)` |
| `js_eval_module` | function | `src/js_sandbox.c:717` | `js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,         ...` |
| `js_eval_named` | function | `src/js_sandbox.c:435` | `js_status js_eval_named(js_context *ctx, const char *src, size_t len,                         con...` |
| `js_eval_once` | function | `src/js_sandbox.c:537` | `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)` |
| `js_install_realms` | function | `src/js_sandbox.c:879` | `js_status js_install_realms(js_context *ctx)` |
| `js_interrupt_cb` | function | `src/js_sandbox.c:173` | `static int js_interrupt_cb(JSRuntime *rt, void *opaque)` |
| `js_limits_default` | function | `src/js_sandbox.c:330` | `js_limits js_limits_default(void)` |
| `js_loc_from_stack` | function | `src/js_sandbox.c:188` | `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,                       i...` |
| `js_mem_state` | struct | `src/js_sandbox.c:29` | `` |
| `js_prime_stack_limit` | function | `src/js_sandbox.c:328` | `void js_prime_stack_limit(void)` |
| `js_pump_jobs` | function | `src/js_sandbox.c:518` | `int js_pump_jobs(js_context *ctx, int max_jobs)` |
| `js_rejection_cb` | function | `src/js_sandbox.c:70` | `static void js_rejection_cb(JSContext *jc, JSValueConst promise, JSValueConst reason,            ...` |
| `js_result_free` | function | `src/js_sandbox.c:550` | `void js_result_free(js_result *res)` |
| `js_set_current_script` | function | `src/js_sandbox.c:574` | `void js_set_current_script(js_context *ctx, const char *src, const char *type)` |
| `js_set_module_host` | function | `src/js_sandbox.c:687` | `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,                         js...` |
| `js_set_time_budget` | function | `src/js_sandbox.c:426` | `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)` |
| `js_stack_limit_for` | function | `src/js_sandbox.c:307` | `size_t js_stack_limit_for(size_t soft_stack)` |
| `js_validate_source` | function | `src/js_sandbox.c:348` | `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)` |
| `limit` | type_alias | `src/js_sandbox.c:29` | `typedef struct js_mem_state { size_t limit;` |
| `limits_resolve` | function | `src/js_sandbox.c:339` | `static js_limits limits_resolve(const js_limits *lim)` |
| `m_realm_clone` | function | `src/js_sandbox.c:857` | `static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,                    ...` |
| `m_realm_eval` | function | `src/js_sandbox.c:821` | `static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,                     ...` |
| `m_realm_new` | function | `src/js_sandbox.c:807` | `static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,                      ...` |
| `mod_fail` | function | `src/js_sandbox.c:702` | `static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,       ...` |
| `mod_loader` | function | `src/js_sandbox.c:648` | `static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque)` |
| `mod_normalize` | function | `src/js_sandbox.c:684` | `static char *mod_normalize(JSContext *jc, const char *base, const char *name, void *opaque);` |
| `mod_set_meta` | function | `src/js_sandbox.c:639` | `static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url)` |
| `process_soft_stack` | function | `src/js_sandbox.c:318` | `static size_t process_soft_stack(void)` |
| `realm_of` | function | `src/js_sandbox.c:784` | `static JSContext *realm_of(js_context *c, JSValueConst g)` |
| `rej_remove` | function | `src/js_sandbox.c:62` | `static void rej_remove(js_context *c, size_t i)` |
| `rej_report` | function | `src/js_sandbox.c:89` | `static void rej_report(js_context *c)` |
| `throw_named` | function | `src/js_sandbox.c:797` | `static JSValue throw_named(JSContext *ctx, const char *name, const char *msg)` |
| `timespec_reached` | function | `src/js_sandbox.c:167` | `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)` |
| `undefined` | function | `src/js_sandbox.c:280` | `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx...` |
| `JT_IO_MAX_STR` | macro | `src/js_trusted.c:62` | `#define JT_IO_MAX_STR` |
| `explicitly` | function | `src/js_trusted.c:461` | `* explicitly (no window, no document). Delivery is always a timer task. */ static const char JT_W...` |
| `hex_nibble` | function | `src/js_trusted.c:254` | `static int hex_nibble(char c)` |
| `jt_enable_observers` | function | `src/js_trusted.c:129` | `jd_status jt_enable_observers(js_context *ctx)` |
| `jt_enable_open` | function | `src/js_trusted.c:48` | `jd_status jt_enable_open(js_context *ctx)` |
| `jt_enable_storage` | function | `src/js_trusted.c:392` | `jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len)` |
| `jt_enable_worker` | function | `src/js_trusted.c:542` | `jd_status jt_enable_worker(js_context *ctx)` |
| `jt_enable_ws` | function | `src/js_trusted.c:237` | `jd_status jt_enable_ws(js_context *ctx)` |
| `jt_geometry_changed` | function | `src/js_trusted.c:143` | `jd_status jt_geometry_changed(js_context *ctx)` |
| `jt_seed_ctx` | struct | `src/js_trusted.c:380` | `` |
| `jt_seed_pair` | function | `src/js_trusted.c:382` | `static void jt_seed_pair(void *vctx, const char *k, size_t kl, const char *v, size_t vl)` |
| `jt_take_opens` | function | `src/js_trusted.c:159` | `char *jt_take_opens(js_context *ctx)` |
| `jt_take_storage` | function | `src/js_trusted.c:413` | `int jt_take_storage(js_context *ctx, char **out, size_t *len)` |
| `jt_take_ws` | function | `src/js_trusted.c:285` | `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap)` |
| `jt_ws_event` | function | `src/js_trusted.c:327` | `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len)` |
| `jt_ws_ops_free` | function | `src/js_trusted.c:249` | `void jt_ws_ops_free(jt_ws_op *ops, size_t n)` |
| `ws_payload` | function | `src/js_trusted.c:261` | `static char *ws_payload(int kind, const char *s, size_t n, size_t *out_len)` |
| `append_seg` | function | `src/link_nav.c:86` | `static int append_seg(char *body, size_t bodysz, size_t *blen,                       const char *...` |
| `ci_prefix` | function | `src/link_nav.c:38` | `static int ci_prefix(const char *s, const char *prefix)` |
| `classify_block` | function | `src/link_nav.c:62` | `static ln_block_reason classify_block(const char *ref)` |
| `clean_href` | function | `src/link_nav.c:19` | `static int clean_href(const char *href, char *out, size_t outsz)` |
| `file_dir_len` | function | `src/link_nav.c:69` | `static size_t file_dir_len(const char *base)` |
| `last_seg_is_dotdot` | function | `src/link_nav.c:79` | `static int last_seg_is_dotdot(const char *body, size_t blen)` |
| `ln_block_reason_text` | function | `src/link_nav.c:241` | `const char *ln_block_reason_text(ln_block_reason reason)` |
| `ln_resolve` | function | `src/link_nav.c:172` | `ln_status ln_resolve(const char *base, const char *href, ln_result *out)` |
| `pop_seg` | function | `src/link_nav.c:98` | `static void pop_seg(char *body, size_t *blen)` |
| `resolve_file` | function | `src/link_nav.c:149` | `static int resolve_file(const char *base, const char *ref, char *out, size_t outsz)` |
| `LS_ARGON2_M_KIB` | macro | `src/local_store.c:856` | `#define LS_ARGON2_M_KIB` |
| `LS_ARGON2_P` | macro | `src/local_store.c:857` | `#define LS_ARGON2_P` |
| `LS_ARGON2_T` | macro | `src/local_store.c:855` | `#define LS_ARGON2_T` |
| `LS_KDF_ARGON2ID` | macro | `src/local_store.c:852` | `#define LS_KDF_ARGON2ID` |
| `LS_KDF_NONE` | macro | `src/local_store.c:851` | `#define LS_KDF_NONE` |
| `LS_VERSION` | macro | `src/local_store.c:850` | `#define LS_VERSION` |
| `OFF_AEAD` | macro | `src/local_store.c:862` | `#define OFF_AEAD` |
| `OFF_KDF` | macro | `src/local_store.c:863` | `#define OFF_KDF` |
| `OFF_MAGIC` | macro | `src/local_store.c:860` | `#define OFF_MAGIC` |
| `OFF_NONCE` | macro | `src/local_store.c:865` | `#define OFF_NONCE` |
| `OFF_SALT` | macro | `src/local_store.c:864` | `#define OFF_SALT` |
| `OFF_VERSION` | macro | `src/local_store.c:861` | `#define OFF_VERSION` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:3` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:14` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:25` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:36` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:47` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:58` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:69` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:80` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:91` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:102` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:113` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:124` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:135` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:146` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:157` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:168` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:179` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:190` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:201` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:212` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:223` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:234` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:245` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:256` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:267` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:278` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:289` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:300` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:311` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:322` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:333` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:344` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:355` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:366` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:377` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:388` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:399` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:410` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:421` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:432` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:443` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:454` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:465` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:476` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:487` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:498` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:509` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:520` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:531` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:542` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:553` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:564` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:575` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:586` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:597` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:608` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:619` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:630` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:641` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:652` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:663` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:674` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:685` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:696` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:707` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:718` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:729` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:740` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:751` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:762` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:773` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:784` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:795` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:806` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:841` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:6` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:17` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:28` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:39` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:50` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:61` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:72` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:83` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:94` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:105` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:116` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:127` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:138` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:149` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:160` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:171` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:182` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:193` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:204` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:215` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:226` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:237` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:248` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:259` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:270` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:281` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:292` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:303` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:314` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:325` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:336` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:347` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:358` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:369` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:380` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:391` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:402` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:413` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:424` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:435` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:446` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:457` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:468` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:479` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:490` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:501` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:512` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:523` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:534` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:545` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:556` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:567` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:578` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:589` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:600` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:611` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:622` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:633` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:644` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:655` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:666` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:677` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:688` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:699` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:710` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:721` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:732` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:743` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:754` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:765` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:776` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:787` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:798` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:809` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:844` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:9` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:20` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:31` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:42` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:53` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:64` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:75` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:86` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:97` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:108` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:119` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:130` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:141` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:152` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:163` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:174` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:185` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:196` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:207` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:218` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:229` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:240` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:251` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:262` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:273` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:284` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:295` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:306` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:317` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:328` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:339` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:350` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:361` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:372` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:383` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:394` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:405` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:416` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:427` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:438` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:449` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:460` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:471` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:482` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:493` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:504` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:515` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:526` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:537` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:548` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:559` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:570` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:581` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:592` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:603` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:614` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:625` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:636` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:647` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:658` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:669` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:680` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:691` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:702` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:713` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:724` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:735` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:746` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:757` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:768` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:779` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:790` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:801` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:812` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:847` | `#define OSSL_KDF_PARAM_THREADS` |
| `_GNU_SOURCE` | macro | `src/local_store.c:11` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:22` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:33` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:44` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:55` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:66` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:77` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:88` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:99` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:110` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:121` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:132` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:143` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:154` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:165` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:176` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:187` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:198` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:209` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:220` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:231` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:242` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:253` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:264` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:275` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:286` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:297` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:308` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:319` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:330` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:341` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:352` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:363` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:374` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:385` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:396` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:407` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:418` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:429` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:440` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:451` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:462` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:473` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:484` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:495` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:506` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:517` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:528` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:539` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:550` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:561` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:572` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:583` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:594` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:605` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:616` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:627` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:638` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:649` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:660` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:671` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:682` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:693` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:704` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:715` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:726` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:737` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:748` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:759` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:770` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:781` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:792` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:803` | `#define _GNU_SOURCE` |
| `_GNU_SOURCE` | macro | `src/local_store.c:814` | `#define _GNU_SOURCE` |
| `aead_decrypt` | function | `src/local_store.c:945` | `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,                      ...` |
| `aead_encrypt` | function | `src/local_store.c:919` | `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,                      ...` |
| `argon2id_derive` | function | `src/local_store.c:881` | `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,                           ...` |
| `cipher_for` | function | `src/local_store.c:871` | `static const EVP_CIPHER *cipher_for(ls_aead aead)` |
| `decrypt_blob` | function | `src/local_store.c:1010` | `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,          ...` |
| `ls_derive_key` | function | `src/local_store.c:910` | `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,                         const...` |
| `ls_free` | function | `src/local_store.c:1106` | `void ls_free(uint8_t *buf, size_t len)` |
| `ls_open` | function | `src/local_store.c:1054` | `ls_status ls_open(const uint8_t key[LS_KEY_LEN],                   const uint8_t *blob, size_t bl...` |
| `ls_open_passphrase` | function | `src/local_store.c:1086` | `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,                         ...` |
| `ls_seal` | function | `src/local_store.c:1041` | `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,                   const uint8_t *p...` |

Next: [SYMBOLS_p9.md](SYMBOLS_p9.md)
