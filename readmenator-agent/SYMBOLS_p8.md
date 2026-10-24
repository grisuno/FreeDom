# Symbols (page 8 of 15)
Previous: [SYMBOLS_p7.md](SYMBOLS_p7.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `JS_MODULE_URL_MAX` | macro | `src/js_sandbox.c:587` | `#define JS_MODULE_URL_MAX` |
| `_POSIX_C_SOURCE` | macro | `src/js_sandbox.c:12` | `#define _POSIX_C_SOURCE` |
| `arm_deadline` | function | `src/js_sandbox.c:386` | `static void arm_deadline(js_context *ctx, uint64_t budget_ms)` |
| `host_dup` | function | `src/js_sandbox.c:156` | `static char *host_dup(const char *src, size_t len)` |
| `is_ascii_digit` | function | `src/js_sandbox.c:184` | `static int is_ascii_digit(char c)` |
| `jm_calloc` | function | `src/js_sandbox.c:120` | `static void *jm_calloc(void *opaque, size_t count, size_t size)` |
| `jm_free` | function | `src/js_sandbox.c:130` | `static void jm_free(void *opaque, void *ptr)` |
| `jm_malloc` | function | `src/js_sandbox.c:112` | `static void *jm_malloc(void *opaque, size_t size)` |
| `jm_realloc` | function | `src/js_sandbox.c:136` | `static void *jm_realloc(void *opaque, void *ptr, size_t size)` |
| `jm_usable_size` | function | `src/js_sandbox.c:146` | `static size_t jm_usable_size(const void *ptr)` |
| `js_context` | struct | `src/js_sandbox.c:33` | `` |
| `js_context_free` | function | `src/js_sandbox.c:374` | `void js_context_free(js_context *ctx)` |
| `js_context_new` | function | `src/js_sandbox.c:334` | `js_status js_context_new(const js_limits *lim, js_context **out)` |
| `js_context_raw` | function | `src/js_sandbox.c:582` | `void *js_context_raw(js_context *ctx)` |
| `js_eval` | function | `src/js_sandbox.c:406` | `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)` |
| `js_eval_module` | function | `src/js_sandbox.c:692` | `js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,         ...` |
| `js_eval_named` | function | `src/js_sandbox.c:410` | `js_status js_eval_named(js_context *ctx, const char *src, size_t len,                         con...` |
| `js_eval_once` | function | `src/js_sandbox.c:512` | `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)` |
| `js_install_realms` | function | `src/js_sandbox.c:854` | `js_status js_install_realms(js_context *ctx)` |
| `js_interrupt_cb` | function | `src/js_sandbox.c:171` | `static int js_interrupt_cb(JSRuntime *rt, void *opaque)` |
| `js_limits_default` | function | `src/js_sandbox.c:305` | `js_limits js_limits_default(void)` |
| `js_loc_from_stack` | function | `src/js_sandbox.c:186` | `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,                       i...` |
| `js_mem_state` | struct | `src/js_sandbox.c:27` | `` |
| `js_pump_jobs` | function | `src/js_sandbox.c:493` | `int js_pump_jobs(js_context *ctx, int max_jobs)` |
| `js_rejection_cb` | function | `src/js_sandbox.c:68` | `static void js_rejection_cb(JSContext *jc, JSValueConst promise, JSValueConst reason,            ...` |
| `js_result_free` | function | `src/js_sandbox.c:525` | `void js_result_free(js_result *res)` |
| `js_set_current_script` | function | `src/js_sandbox.c:549` | `void js_set_current_script(js_context *ctx, const char *src, const char *type)` |
| `js_set_module_host` | function | `src/js_sandbox.c:662` | `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,                         js...` |
| `js_set_time_budget` | function | `src/js_sandbox.c:401` | `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)` |
| `js_validate_source` | function | `src/js_sandbox.c:323` | `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)` |
| `limit` | type_alias | `src/js_sandbox.c:27` | `typedef struct js_mem_state { size_t limit;` |
| `limits_resolve` | function | `src/js_sandbox.c:314` | `static js_limits limits_resolve(const js_limits *lim)` |
| `m_realm_clone` | function | `src/js_sandbox.c:832` | `static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,                    ...` |
| `m_realm_eval` | function | `src/js_sandbox.c:796` | `static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,                     ...` |
| `m_realm_new` | function | `src/js_sandbox.c:782` | `static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,                      ...` |
| `mod_fail` | function | `src/js_sandbox.c:677` | `static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,       ...` |
| `mod_loader` | function | `src/js_sandbox.c:623` | `static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque)` |
| `mod_normalize` | function | `src/js_sandbox.c:659` | `static char *mod_normalize(JSContext *jc, const char *base, const char *name, void *opaque);` |
| `mod_set_meta` | function | `src/js_sandbox.c:614` | `static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url)` |
| `realm_of` | function | `src/js_sandbox.c:759` | `static JSContext *realm_of(js_context *c, JSValueConst g)` |
| `rej_remove` | function | `src/js_sandbox.c:60` | `static void rej_remove(js_context *c, size_t i)` |
| `rej_report` | function | `src/js_sandbox.c:87` | `static void rej_report(js_context *c)` |
| `throw_named` | function | `src/js_sandbox.c:772` | `static JSValue throw_named(JSContext *ctx, const char *name, const char *msg)` |
| `timespec_reached` | function | `src/js_sandbox.c:165` | `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)` |
| `undefined` | function | `src/js_sandbox.c:278` | `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx...` |
| `JT_IO_MAX_STR` | macro | `src/js_trusted.c:49` | `#define JT_IO_MAX_STR` |
| `explicitly` | function | `src/js_trusted.c:448` | `* explicitly (no window, no document). Delivery is always a timer task. */ static const char JT_W...` |
| `hex_nibble` | function | `src/js_trusted.c:241` | `static int hex_nibble(char c)` |
| `jt_enable_observers` | function | `src/js_trusted.c:116` | `jd_status jt_enable_observers(js_context *ctx)` |
| `jt_enable_open` | function | `src/js_trusted.c:35` | `jd_status jt_enable_open(js_context *ctx)` |
| `jt_enable_storage` | function | `src/js_trusted.c:379` | `jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len)` |
| `jt_enable_worker` | function | `src/js_trusted.c:529` | `jd_status jt_enable_worker(js_context *ctx)` |
| `jt_enable_ws` | function | `src/js_trusted.c:224` | `jd_status jt_enable_ws(js_context *ctx)` |
| `jt_geometry_changed` | function | `src/js_trusted.c:130` | `jd_status jt_geometry_changed(js_context *ctx)` |
| `jt_seed_ctx` | struct | `src/js_trusted.c:367` | `` |
| `jt_seed_pair` | function | `src/js_trusted.c:369` | `static void jt_seed_pair(void *vctx, const char *k, size_t kl, const char *v, size_t vl)` |
| `jt_take_opens` | function | `src/js_trusted.c:146` | `char *jt_take_opens(js_context *ctx)` |
| `jt_take_storage` | function | `src/js_trusted.c:400` | `int jt_take_storage(js_context *ctx, char **out, size_t *len)` |
| `jt_take_ws` | function | `src/js_trusted.c:272` | `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap)` |
| `jt_ws_event` | function | `src/js_trusted.c:314` | `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len)` |
| `jt_ws_ops_free` | function | `src/js_trusted.c:236` | `void jt_ws_ops_free(jt_ws_op *ops, size_t n)` |
| `ws_payload` | function | `src/js_trusted.c:248` | `static char *ws_payload(int kind, const char *s, size_t n, size_t *out_len)` |
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
| `LS_ARGON2_M_KIB` | macro | `src/local_store.c:823` | `#define LS_ARGON2_M_KIB` |
| `LS_ARGON2_P` | macro | `src/local_store.c:824` | `#define LS_ARGON2_P` |
| `LS_ARGON2_T` | macro | `src/local_store.c:822` | `#define LS_ARGON2_T` |
| `LS_KDF_ARGON2ID` | macro | `src/local_store.c:819` | `#define LS_KDF_ARGON2ID` |
| `LS_KDF_NONE` | macro | `src/local_store.c:818` | `#define LS_KDF_NONE` |
| `LS_VERSION` | macro | `src/local_store.c:817` | `#define LS_VERSION` |
| `OFF_AEAD` | macro | `src/local_store.c:829` | `#define OFF_AEAD` |
| `OFF_KDF` | macro | `src/local_store.c:830` | `#define OFF_KDF` |
| `OFF_MAGIC` | macro | `src/local_store.c:827` | `#define OFF_MAGIC` |
| `OFF_NONCE` | macro | `src/local_store.c:832` | `#define OFF_NONCE` |
| `OFF_SALT` | macro | `src/local_store.c:831` | `#define OFF_SALT` |
| `OFF_VERSION` | macro | `src/local_store.c:828` | `#define OFF_VERSION` |
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
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:808` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
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
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:811` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
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
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:814` | `#define OSSL_KDF_PARAM_THREADS` |
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
| `aead_decrypt` | function | `src/local_store.c:912` | `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,                      ...` |
| `aead_encrypt` | function | `src/local_store.c:886` | `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,                      ...` |
| `argon2id_derive` | function | `src/local_store.c:848` | `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,                           ...` |
| `cipher_for` | function | `src/local_store.c:838` | `static const EVP_CIPHER *cipher_for(ls_aead aead)` |
| `decrypt_blob` | function | `src/local_store.c:977` | `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,          ...` |
| `ls_derive_key` | function | `src/local_store.c:877` | `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,                         const...` |
| `ls_free` | function | `src/local_store.c:1073` | `void ls_free(uint8_t *buf, size_t len)` |
| `ls_open` | function | `src/local_store.c:1021` | `ls_status ls_open(const uint8_t key[LS_KEY_LEN],                   const uint8_t *blob, size_t bl...` |
| `ls_open_passphrase` | function | `src/local_store.c:1053` | `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,                         ...` |
| `ls_seal` | function | `src/local_store.c:1008` | `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,                   const uint8_t *p...` |
| `ls_seal_passphrase` | function | `src/local_store.c:1032` | `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,           ...` |
| `seal_core` | function | `src/local_store.c:940` | `static ls_status seal_core(const uint8_t *key, ls_aead aead, uint8_t kdf_id,                     ...` |
| `_POSIX_C_SOURCE` | macro | `src/media_decoder.c:23` | `#define _POSIX_C_SOURCE` |
| `av_rescale_q` | function | `src/media_decoder.c:217` | `return av_rescale_q(f->pts, tb, (AVRational)` |
| `decode_segment` | function | `src/media_decoder.c:276` | `static int decode_segment(decoder_ctx *dc, const uint8_t *data, size_t len)` |
| `decoder_close` | function | `src/media_decoder.c:78` | `static void decoder_close(decoder_ctx *dc)` |
| `decoder_ctx` | struct | `src/media_decoder.c:54` | `` |
| `decoder_init` | function | `src/media_decoder.c:96` | `static int decoder_init(decoder_ctx *dc, const uint8_t *data, size_t len)` |
| `dropped` | function | `src/media_decoder.c:369` | `* the codec in permanent EOF state: every segment after the first decoded * one was silently dropped ("plays a...` |
| `fd` | function | `src/media_decoder.c:469` | `* prevent the Wayland display fd (inherited from the parent) from * surviving the exec. An inherited Wayland fd...` |
| `frame_pts_us` | function | `src/media_decoder.c:215` | `static int64_t frame_pts_us(const AVFrame *f, AVRational tb, int64_t fallback)` |
| `media_decoder_run` | function | `src/media_decoder.c:379` | `void media_decoder_run(int out_fd, int cmd_fd)` |
| `media_decoder_spawn` | function | `src/media_decoder.c:449` | `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd)` |
| `open` | function | `src/media_decoder.c:18` | `*  * Sandbox: the decoder needs open() for shared libraries (.so loading) and  * brk/mmap for FFm...` |
| `out_fd` | type_alias | `src/media_decoder.c:53` | `typedef struct decoder_ctx { int out_fd;` |
| `send_audio_frame` | function | `src/media_decoder.c:242` | `static void send_audio_frame(decoder_ctx *dc, int64_t pts_us)` |
| `send_video_frame` | function | `src/media_decoder.c:222` | `static void send_video_frame(decoder_ctx *dc, int64_t pts_us)` |
| `NR_MAX_HOST` | macro | `src/net_realm.c:15` | `#define NR_MAX_HOST` |
| `ends_with_realm` | function | `src/net_realm.c:23` | `static int ends_with_realm(const char *host, size_t n, const char *suffix)` |
| `host_of` | function | `src/net_realm.c:52` | `static int host_of(const char *url, char *out, size_t out_size)` |
| `lower` | function | `src/net_realm.c:17` | `static char lower(char c)` |
| `nr_classify_host` | function | `src/net_realm.c:34` | `nr_realm nr_classify_host(const char *host)` |
| `nr_classify_url` | function | `src/net_realm.c:68` | `nr_realm nr_classify_url(const char *url)` |
| `nr_realm_allows_http` | function | `src/net_realm.c:88` | `int nr_realm_allows_http(nr_realm r)` |
| `nr_realm_name` | function | `src/net_realm.c:94` | `const char *nr_realm_name(nr_realm r)` |
| `nr_route_for` | function | `src/net_realm.c:74` | `nr_route nr_route_for(const char *url, nr_config cfg)` |
| `nr_route_name` | function | `src/net_realm.c:103` | `const char *nr_route_name(nr_route r)` |
| `LL_FS_BASE` | macro | `src/os_sandbox.c:254` | `#define LL_FS_BASE` |
| `OS_ALLOWED_N` | macro | `src/os_sandbox.c:50` | `#define OS_ALLOWED_N` |
| `OS_SECCOMP_ARCH` | macro | `src/os_sandbox.c:140` | `#  define OS_SECCOMP_ARCH` |
| `OS_SECCOMP_ARCH` | macro | `src/os_sandbox.c:142` | `#  define OS_SECCOMP_ARCH` |
| `_GNU_SOURCE` | macro | `src/os_sandbox.c:13` | `#define _GNU_SOURCE` |
| `excluded` | function | `src/os_sandbox.c:89` | `* intentionally excluded (they need /proc remounting and a post-unshare fork). */ int os_namespac...` |
| `fields` | function | `src/os_sandbox.c:303` | `* long as the unknown trailing fields (net/scoped) are zero, which they are. */ int rfd =...` |
| `headroom` | function | `src/os_sandbox.c:203` | `* wide headroom (room for ~125 allowed syscalls). */ prog[at_mmap].jt = (unsigned char)(prot_check - (at_mmap + 1));` |
| `ll_add_rule` | function | `src/os_sandbox.c:244` | `static long ll_add_rule(int fd, enum landlock_rule_type type,                         const void ...` |
| `ll_create_ruleset` | function | `src/os_sandbox.c:239` | `static long ll_create_ruleset(const struct landlock_ruleset_attr *attr,                          ...` |
| `ll_handled` | function | `src/os_sandbox.c:265` | `static uint64_t ll_handled(int abi)` |
| `ll_read_access` | function | `src/os_sandbox.c:279` | `static uint64_t ll_read_access(uint64_t handled)` |
| `ll_restrict_self` | function | `src/os_sandbox.c:249` | `static long ll_restrict_self(int fd, uint32_t flags)` |
| `number` | function | `src/os_sandbox.c:157` | `* number (x32/i386 on x86_64, AArch32 on aarch64). */ prog[n++] = (struct sock_filter)BPF_STMT(BPF_LD \| BPF_W \|...` |
| `os_harden` | function | `src/os_sandbox.c:113` | `os_status os_harden(os_violation action)` |
| `os_harden` | function | `src/os_sandbox.c:145` | `os_status os_harden(os_violation action)` |
| `os_isolate_namespaces` | function | `src/os_sandbox.c:94` | `os_status os_isolate_namespaces(void)` |
| `os_isolate_namespaces` | function | `src/os_sandbox.c:116` | `os_status os_isolate_namespaces(void)` |
| `os_landlock_abi` | function | `src/os_sandbox.c:285` | `int os_landlock_abi(void)` |
| `os_landlock_abi` | function | `src/os_sandbox.c:331` | `int os_landlock_abi(void)` |
| `os_landlock_restrict` | function | `src/os_sandbox.c:291` | `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)` |
| `os_landlock_restrict` | function | `src/os_sandbox.c:332` | `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)` |
| `os_namespace_flags` | function | `src/os_sandbox.c:115` | `int os_namespace_flags(void)` |
| `os_no_dump` | function | `src/os_sandbox.c:75` | `os_status os_no_dump(void)` |
| `os_no_dump` | function | `src/os_sandbox.c:111` | `os_status os_no_dump(void)` |
| `os_policy_allows` | function | `src/os_sandbox.c:52` | `int os_policy_allows(long syscall_nr)` |
| `os_policy_allows` | function | `src/os_sandbox.c:106` | `int os_policy_allows(long syscall_nr)` |
| `os_policy_size` | function | `src/os_sandbox.c:59` | `size_t os_policy_size(void)` |
| `os_policy_size` | function | `src/os_sandbox.c:107` | `size_t os_policy_size(void)` |
| `os_prot_allowed` | function | `src/os_sandbox.c:65` | `int os_prot_allowed(long syscall_nr, unsigned long prot)` |
| `os_prot_allowed` | function | `src/os_sandbox.c:108` | `int os_prot_allowed(long syscall_nr, unsigned long prot)` |
| `PV_COLOR_TOKEN_MAX` | macro | `src/page_view.c:1207` | `#define PV_COLOR_TOKEN_MAX` |
| `PV_FONT_CHAIN_MAX` | macro | `src/page_view.c:64` | `#define PV_FONT_CHAIN_MAX` |
| `PV_FONT_PCT_MAX` | macro | `src/page_view.c:66` | `#define PV_FONT_PCT_MAX` |
| `PV_FONT_PCT_MIN` | macro | `src/page_view.c:65` | `#define PV_FONT_PCT_MIN` |
| `PV_FONT_REL_MAX` | macro | `src/page_view.c:58` | `#define PV_FONT_REL_MAX` |
| `PV_FONT_REL_MIN` | macro | `src/page_view.c:57` | `#define PV_FONT_REL_MIN` |
| `PV_MAX_BOXES` | macro | `src/page_view.c:1254` | `#define PV_MAX_BOXES` |
| `PV_MAX_CONTAINERS` | macro | `src/page_view.c:1245` | `#define PV_MAX_CONTAINERS` |
| `PV_MAX_DIM` | macro | `src/page_view.c:52` | `#define PV_MAX_DIM` |
| `PV_MAX_GRID_COLS` | macro | `src/page_view.c:1246` | `#define PV_MAX_GRID_COLS` |
| `PV_MAX_INLINE_ROW_ITEMS` | macro | `src/page_view.c:2802` | `#define PV_MAX_INLINE_ROW_ITEMS` |
| `PV_MAX_STYLE_BYTES` | macro | `src/page_view.c:4923` | `#define PV_MAX_STYLE_BYTES` |
| `PV_NODE_MAP_INIT_CAP` | macro | `src/page_view.c:346` | `#define PV_NODE_MAP_INIT_CAP` |
| `PV_TEXTLESS_DEPTH_MAX` | macro | `src/page_view.c:3106` | `#define PV_TEXTLESS_DEPTH_MAX` |
| `URL` | function | `src/page_view.c:6164` | `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `_POSIX_C_SOURCE` | macro | `src/page_view.c:10` | `#define _POSIX_C_SOURCE` |
| `address` | function | `src/page_view.c:1257` | `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <=...` |
| `annotate_flow_run` | function | `src/page_view.c:1814` | `static void annotate_flow_run(pv_view *v, pv_container_reg *reg, pv_item_track *items,           ...` |
| `annotate_replaced_run` | function | `src/page_view.c:5059` | `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,                             ...` |
| `ascii_ieq` | function | `src/page_view.c:4341` | `static int ascii_ieq(const char *s, const char *lit)` |
| `attr_dup` | function | `src/page_view.c:4353` | `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)` |
| `attributes` | function | `src/page_view.c:4275` | `* carries those attributes (spec/css.md, "Root matcher"). */ static int root_els_match(void *ctx,...` |
| `band` | function | `src/page_view.c:5855` | `* run: without its float annotation it cut the band (the icon row of a * `float:right` social list became one float...` |

Next: [SYMBOLS_p9.md](SYMBOLS_p9.md)
