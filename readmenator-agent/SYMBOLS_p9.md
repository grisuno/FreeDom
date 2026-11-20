# Symbols (page 9 of 17)
Previous: [SYMBOLS_p8.md](SYMBOLS_p8.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `ji_install` | function | `src/js_intl.c:423` | `int ji_install(js_context *ctx)` |
| `jd_lp_set` | function | `src/js_location.c:25` | `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,                       const ...` |
| `jd_pop_state` | function | `src/js_location.c:251` | `int jd_pop_state(js_context *ctx, int index)` |
| `jd_set_location` | function | `src/js_location.c:140` | `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)` |
| `jd_take_history` | function | `src/js_location.c:220` | `char *jd_take_history(js_context *ctx, int *go)` |
| `jd_take_nav_request` | function | `src/js_location.c:174` | `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)` |
| `jl_m_hist_target` | function | `src/js_location.c:36` | `JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `FREEDOM_JS_LOCATION_INTERNAL_H` | macro | `src/js_location_internal.h:2` | `#define FREEDOM_JS_LOCATION_INTERNAL_H` |
| `header` | function | `src/js_location_internal.h:6` | `* stay out of every public header (include/ never sees quickjs.h). */ #include "quickjs.h" JSValue...` |
| `JN_SUPPORTS_MAX` | macro | `src/js_native.c:13` | `#define JN_SUPPORTS_MAX` |
| `jn_css_ok` | function | `src/js_native.c:25` | `static JSValue jn_css_ok(JSContext *c, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `jn_host_eval` | function | `src/js_native.c:15` | `JSValue jn_host_eval(JSContext *c, const char *src, size_t len, const char *name)` |
| `jn_seal` | function | `src/js_native.c:144` | `int jn_seal(js_context *ctx)` |
| `FREEDOM_JS_NATIVE_INTERNAL_H` | macro | `src/js_native_internal.h:6` | `#define FREEDOM_JS_NATIVE_INTERNAL_H` |
| `js_context` | struct | `src/js_native_internal.h:20` | `` |
| `js_host_slot` | function | `src/js_native_internal.h:21` | `JSValue *js_host_slot(struct js_context *ctx);` |
| `eq_ci` | function | `src/js_policy.c:12` | `static int eq_ci(const char *a, const char *b)` |
| `jsp_enabled` | function | `src/js_policy.c:22` | `bool jsp_enabled(jsp_mode mode, int host_allowlisted)` |
| `jsp_mode_from_str` | function | `src/js_policy.c:39` | `jsp_mode jsp_mode_from_str(const char *s)` |
| `jsp_mode_str` | function | `src/js_policy.c:51` | `const char *jsp_mode_str(jsp_mode mode)` |
| `jsp_present_trusted` | function | `src/js_policy.c:35` | `bool jsp_present_trusted(int host_allowlisted)` |
| `jsp_trusted` | function | `src/js_policy.c:31` | `bool jsp_trusted(bool js_enabled, int host_allowlisted)` |
| `JS_MODULE_URL_MAX` | macro | `src/js_sandbox.c:860` | `#define JS_MODULE_URL_MAX` |
| `JS_PROFILE_KEY_MAX` | macro | `src/js_sandbox.c:36` | `#define JS_PROFILE_KEY_MAX` |
| `JS_PROFILE_SLOTS` | macro | `src/js_sandbox.c:35` | `#define JS_PROFILE_SLOTS` |
| `_POSIX_C_SOURCE` | macro | `src/js_sandbox.c:12` | `#define _POSIX_C_SOURCE` |
| `arm_deadline` | function | `src/js_sandbox.c:652` | `static void arm_deadline(js_context *ctx, uint64_t budget_ms)` |
| `host_dup` | function | `src/js_sandbox.c:178` | `static char *host_dup(const char *src, size_t len)` |
| `is_ascii_digit` | function | `src/js_sandbox.c:425` | `static int is_ascii_digit(char c)` |
| `jm_calloc` | function | `src/js_sandbox.c:142` | `static void *jm_calloc(void *opaque, size_t count, size_t size)` |
| `jm_free` | function | `src/js_sandbox.c:152` | `static void jm_free(void *opaque, void *ptr)` |
| `jm_malloc` | function | `src/js_sandbox.c:134` | `static void *jm_malloc(void *opaque, size_t size)` |
| `jm_realloc` | function | `src/js_sandbox.c:158` | `static void *jm_realloc(void *opaque, void *ptr, size_t size)` |
| `jm_usable_size` | function | `src/js_sandbox.c:168` | `static size_t jm_usable_size(const void *ptr)` |
| `js_context` | struct | `src/js_sandbox.c:38` | `` |
| `js_context_free` | function | `src/js_sandbox.c:639` | `void js_context_free(js_context *ctx)` |
| `js_context_new` | function | `src/js_sandbox.c:598` | `js_status js_context_new(const js_limits *lim, js_context **out)` |
| `js_context_raw` | function | `src/js_sandbox.c:855` | `void *js_context_raw(js_context *ctx)` |
| `js_devtools_enable` | function | `src/js_sandbox.c:379` | `void js_devtools_enable(js_context *ctx)` |
| `js_devtools_expose` | function | `src/js_sandbox.c:385` | `js_status js_devtools_expose(js_context *ctx)` |
| `js_eval` | function | `src/js_sandbox.c:672` | `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)` |
| `js_eval_module` | function | `src/js_sandbox.c:965` | `js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,         ...` |
| `js_eval_named` | function | `src/js_sandbox.c:676` | `js_status js_eval_named(js_context *ctx, const char *src, size_t len,                         con...` |
| `js_eval_once` | function | `src/js_sandbox.c:778` | `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)` |
| `js_host_slot` | function | `src/js_sandbox.c:76` | `JSValue *js_host_slot(struct js_context *ctx)` |
| `js_install_realms` | function | `src/js_sandbox.c:1127` | `js_status js_install_realms(js_context *ctx)` |
| `js_interrupt_cb` | function | `src/js_sandbox.c:401` | `static int js_interrupt_cb(JSRuntime *rt, void *opaque)` |
| `js_limits_default` | function | `src/js_sandbox.c:569` | `js_limits js_limits_default(void)` |
| `js_loc_from_stack` | function | `src/js_sandbox.c:427` | `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,                       i...` |
| `js_mem_state` | struct | `src/js_sandbox.c:29` | `` |
| `js_prime_stack_limit` | function | `src/js_sandbox.c:567` | `void js_prime_stack_limit(void)` |
| `js_profile_enable` | function | `src/js_sandbox.c:229` | `void js_profile_enable(js_context *ctx)` |
| `js_profile_report` | function | `src/js_sandbox.c:235` | `size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n)` |
| `js_pump_jobs` | function | `src/js_sandbox.c:759` | `int js_pump_jobs(js_context *ctx, int max_jobs)` |
| `js_rejection_cb` | function | `src/js_sandbox.c:90` | `static void js_rejection_cb(JSContext *jc, JSValueConst promise, JSValueConst reason,            ...` |
| `js_result_free` | function | `src/js_sandbox.c:791` | `void js_result_free(js_result *res)` |
| `js_set_current_script` | function | `src/js_sandbox.c:819` | `void js_set_current_script(js_context *ctx, const char *src, const char *type)` |
| `js_set_module_host` | function | `src/js_sandbox.c:935` | `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,                         js...` |
| `js_set_time_budget` | function | `src/js_sandbox.c:667` | `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)` |
| `js_stack_limit_for` | function | `src/js_sandbox.c:546` | `size_t js_stack_limit_for(size_t soft_stack)` |
| `js_throws_enable` | function | `src/js_sandbox.c:335` | `void js_throws_enable(js_context *ctx)` |
| `js_throws_report` | function | `src/js_sandbox.c:341` | `size_t js_throws_report(js_context *ctx, char *out, size_t cap, size_t top_n)` |
| `js_validate_source` | function | `src/js_sandbox.c:587` | `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)` |
| `limit` | type_alias | `src/js_sandbox.c:29` | `typedef struct js_mem_state { size_t limit;` |
| `limits_resolve` | function | `src/js_sandbox.c:578` | `static js_limits limits_resolve(const js_limits *lim)` |
| `m_fb_report` | function | `src/js_sandbox.c:363` | `static JSValue m_fb_report(JSContext *jsctx, JSValueConst this_val, int argc, JSValueConst *argv,...` |
| `m_realm_clone` | function | `src/js_sandbox.c:1105` | `static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,                    ...` |
| `m_realm_eval` | function | `src/js_sandbox.c:1069` | `static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,                     ...` |
| `m_realm_new` | function | `src/js_sandbox.c:1055` | `static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,                      ...` |
| `mod_fail` | function | `src/js_sandbox.c:950` | `static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,       ...` |
| `mod_loader` | function | `src/js_sandbox.c:896` | `static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque)` |
| `mod_normalize` | function | `src/js_sandbox.c:932` | `static char *mod_normalize(JSContext *jc, const char *base, const char *name, void *opaque);` |
| `mod_set_meta` | function | `src/js_sandbox.c:887` | `static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url)` |
| `process_soft_stack` | function | `src/js_sandbox.c:557` | `static size_t process_soft_stack(void)` |
| `profile_sample` | function | `src/js_sandbox.c:197` | `static void profile_sample(js_context *c, unsigned weight_ms)` |
| `realm_of` | function | `src/js_sandbox.c:1032` | `static JSContext *realm_of(js_context *c, JSValueConst g)` |
| `rej_remove` | function | `src/js_sandbox.c:82` | `static void rej_remove(js_context *c, size_t i)` |
| `rej_report` | function | `src/js_sandbox.c:109` | `static void rej_report(js_context *c)` |
| `throw_hook_cb` | function | `src/js_sandbox.c:315` | `static void throw_hook_cb(JSContext *ctx, JSValueConst obj, void *opaque)` |
| `throw_key` | function | `src/js_sandbox.c:258` | `static void throw_key(JSContext *ctx, JSValueConst obj, char *key, size_t cap)` |
| `throw_named` | function | `src/js_sandbox.c:1045` | `static JSValue throw_named(JSContext *ctx, const char *name, const char *msg)` |
| `timespec_diff_ms` | function | `src/js_sandbox.c:192` | `static long timespec_diff_ms(const struct timespec *a, const struct timespec *b)` |
| `timespec_reached` | function | `src/js_sandbox.c:187` | `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)` |
| `undefined` | function | `src/js_sandbox.c:519` | `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx...` |
| `JT_IO_MAX_STR` | macro | `src/js_trusted.c:62` | `#define JT_IO_MAX_STR` |
| `explicitly` | function | `src/js_trusted.c:552` | `* explicitly (no window, no document). Delivery is always a timer task. */ static const char JT_W...` |
| `hex_nibble` | function | `src/js_trusted.c:250` | `static int hex_nibble(char c)` |
| `jt_enable_frames` | function | `src/js_trusted.c:428` | `jd_status jt_enable_frames(js_context *ctx, int frame_id)` |
| `jt_enable_observers` | function | `src/js_trusted.c:129` | `jd_status jt_enable_observers(js_context *ctx)` |
| `jt_enable_open` | function | `src/js_trusted.c:49` | `jd_status jt_enable_open(js_context *ctx)` |
| `jt_enable_storage` | function | `src/js_trusted.c:484` | `jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len)` |
| `jt_enable_worker` | function | `src/js_trusted.c:633` | `jd_status jt_enable_worker(js_context *ctx)` |
| `jt_enable_ws` | function | `src/js_trusted.c:234` | `jd_status jt_enable_ws(js_context *ctx)` |
| `jt_geometry_changed` | function | `src/js_trusted.c:142` | `jd_status jt_geometry_changed(js_context *ctx)` |
| `jt_seed_ctx` | struct | `src/js_trusted.c:472` | `` |
| `jt_seed_pair` | function | `src/js_trusted.c:474` | `static void jt_seed_pair(void *vctx, const char *k, size_t kl, const char *v, size_t vl)` |
| `jt_take_opens` | function | `src/js_trusted.c:157` | `char *jt_take_opens(js_context *ctx)` |
| `jt_take_storage` | function | `src/js_trusted.c:504` | `int jt_take_storage(js_context *ctx, char **out, size_t *len)` |
| `jt_take_ws` | function | `src/js_trusted.c:281` | `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap)` |
| `jt_ws_event` | function | `src/js_trusted.c:332` | `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len)` |
| `jt_ws_ops_free` | function | `src/js_trusted.c:245` | `void jt_ws_ops_free(jt_ws_op *ops, size_t n)` |
| `ws_payload` | function | `src/js_trusted.c:257` | `static char *ws_payload(int kind, const char *s, size_t n, size_t *out_len)` |
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
| `LS_ARGON2_M_KIB` | macro | `src/local_store.c:54` | `#define LS_ARGON2_M_KIB` |
| `LS_ARGON2_P` | macro | `src/local_store.c:55` | `#define LS_ARGON2_P` |
| `LS_ARGON2_T` | macro | `src/local_store.c:53` | `#define LS_ARGON2_T` |
| `LS_KDF_ARGON2ID` | macro | `src/local_store.c:50` | `#define LS_KDF_ARGON2ID` |
| `LS_KDF_NONE` | macro | `src/local_store.c:49` | `#define LS_KDF_NONE` |
| `LS_VERSION` | macro | `src/local_store.c:48` | `#define LS_VERSION` |
| `OFF_AEAD` | macro | `src/local_store.c:60` | `#define OFF_AEAD` |
| `OFF_KDF` | macro | `src/local_store.c:61` | `#define OFF_KDF` |
| `OFF_MAGIC` | macro | `src/local_store.c:58` | `#define OFF_MAGIC` |
| `OFF_NONCE` | macro | `src/local_store.c:63` | `#define OFF_NONCE` |
| `OFF_SALT` | macro | `src/local_store.c:62` | `#define OFF_SALT` |
| `OFF_VERSION` | macro | `src/local_store.c:59` | `#define OFF_VERSION` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:25` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:39` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:28` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:42` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:31` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:45` | `#define OSSL_KDF_PARAM_THREADS` |
| `_GNU_SOURCE` | macro | `src/local_store.c:13` | `#define _GNU_SOURCE` |
| `aead_decrypt` | function | `src/local_store.c:143` | `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,                      ...` |
| `aead_encrypt` | function | `src/local_store.c:117` | `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,                      ...` |
| `argon2id_derive` | function | `src/local_store.c:79` | `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,                           ...` |
| `cipher_for` | function | `src/local_store.c:69` | `static const EVP_CIPHER *cipher_for(ls_aead aead)` |
| `decrypt_blob` | function | `src/local_store.c:208` | `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,          ...` |
| `ls_derive_key` | function | `src/local_store.c:108` | `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,                         const...` |
| `ls_free` | function | `src/local_store.c:304` | `void ls_free(uint8_t *buf, size_t len)` |
| `ls_open` | function | `src/local_store.c:252` | `ls_status ls_open(const uint8_t key[LS_KEY_LEN],                   const uint8_t *blob, size_t bl...` |
| `ls_open_passphrase` | function | `src/local_store.c:284` | `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,                         ...` |
| `ls_seal` | function | `src/local_store.c:239` | `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,                   const uint8_t *p...` |
| `ls_seal_passphrase` | function | `src/local_store.c:263` | `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,           ...` |
| `seal_core` | function | `src/local_store.c:171` | `static ls_status seal_core(const uint8_t *key, ls_aead aead, uint8_t kdf_id,                     ...` |
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
| `NG_TEXT_MAX` | macro | `src/net_guard.c:10` | `#define NG_TEXT_MAX` |
| `NG_V4_LEN` | macro | `src/net_guard.c:8` | `#define NG_V4_LEN` |
| `NG_V6_LEN` | macro | `src/net_guard.c:9` | `#define NG_V6_LEN` |
| `decides` | function | `src/net_guard.c:40` | `* IPv4 decides (:: and ::1 embed 0.0.0.0 and 0.0.0.1, both in 0/8). */ if (head_zero && (s[5] == 0 \|\| s[5] ==...` |
| `ng_addr_is_private` | function | `src/net_guard.c:63` | `int ng_addr_is_private(int family, const unsigned char *addr, size_t len)` |
| `ng_ci_eq` | function | `src/net_guard.c:97` | `static int ng_ci_eq(const char *a, const char *b, size_t n)` |
| `ng_decide` | function | `src/net_guard.c:121` | `ng_verdict ng_decide(const ng_request *r, int peer_private)` |
| `ng_host_is_ip` | function | `src/net_guard.c:91` | `int ng_host_is_ip(const char *host)` |
| `ng_host_is_local` | function | `src/net_guard.c:107` | `int ng_host_is_local(const char *host)` |
| `ng_parse` | function | `src/net_guard.c:71` | `static int ng_parse(const char *text, int *family, unsigned char out[NG_V6_LEN])` |
| `ng_seg` | function | `src/net_guard.c:29` | `static unsigned ng_seg(const unsigned char a[NG_V6_LEN], int i)` |
| `ng_text_is_private` | function | `src/net_guard.c:84` | `int ng_text_is_private(const char *ip_text)` |
| `ng_v4_is_private` | function | `src/net_guard.c:12` | `static int ng_v4_is_private(const unsigned char o[NG_V4_LEN])` |
| `ng_v6_is_private` | function | `src/net_guard.c:33` | `static int ng_v6_is_private(const unsigned char a[NG_V6_LEN])` |
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
| `PV_ATOM_SPACE_MAX` | macro | `src/page_view.c:1376` | `#define PV_ATOM_SPACE_MAX` |
| `PV_CELL_NESTED` | macro | `src/page_view.c:5535` | `#define PV_CELL_NESTED` |
| `PV_CELL_RICH` | macro | `src/page_view.c:5536` | `#define PV_CELL_RICH` |
| `PV_COLOR_TOKEN_MAX` | macro | `src/page_view.c:1231` | `#define PV_COLOR_TOKEN_MAX` |
| `PV_CQ_NODES_MAX` | macro | `src/page_view.c:2442` | `#define PV_CQ_NODES_MAX` |
| `PV_FONT_CHAIN_MAX` | macro | `src/page_view.c:69` | `#define PV_FONT_CHAIN_MAX` |
| `PV_FONT_PCT_MAX` | macro | `src/page_view.c:71` | `#define PV_FONT_PCT_MAX` |
| `PV_FONT_PCT_MIN` | macro | `src/page_view.c:70` | `#define PV_FONT_PCT_MIN` |
| `PV_FONT_REL_MAX` | macro | `src/page_view.c:63` | `#define PV_FONT_REL_MAX` |
| `PV_FONT_REL_MIN` | macro | `src/page_view.c:62` | `#define PV_FONT_REL_MIN` |
| `PV_FRAME_DEF_H` | macro | `src/page_view.c:4626` | `#define PV_FRAME_DEF_H` |
| `PV_FRAME_DEF_W` | macro | `src/page_view.c:4625` | `#define PV_FRAME_DEF_W` |
| `PV_FRAME_URL_MAX` | macro | `src/page_view.c:4627` | `#define PV_FRAME_URL_MAX` |
| `PV_MAX_BOXES` | macro | `src/page_view.c:1271` | `#define PV_MAX_BOXES` |
| `PV_MAX_DIM` | macro | `src/page_view.c:57` | `#define PV_MAX_DIM` |
| `PV_MAX_GRID_COLS` | macro | `src/page_view.c:1263` | `#define PV_MAX_GRID_COLS` |
| `PV_MAX_INLINE_ROW_ITEMS` | macro | `src/page_view.c:3189` | `#define PV_MAX_INLINE_ROW_ITEMS` |
| `PV_MAX_STYLE_BYTES` | macro | `src/page_view.c:5615` | `#define PV_MAX_STYLE_BYTES` |
| `PV_NODE_MAP_INIT_CAP` | macro | `src/page_view.c:354` | `#define PV_NODE_MAP_INIT_CAP` |
| `PV_STYLE_RESERVE_MAX` | macro | `src/page_view.c:2464` | `#define PV_STYLE_RESERVE_MAX` |
| `PV_STYLE_RETIRE_MAX` | macro | `src/page_view.c:2398` | `#define PV_STYLE_RETIRE_MAX` |
| `PV_TEXTLESS_DEPTH_MAX` | macro | `src/page_view.c:3591` | `#define PV_TEXTLESS_DEPTH_MAX` |
| `URL` | function | `src/page_view.c:6972` | `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `_POSIX_C_SOURCE` | macro | `src/page_view.c:10` | `#define _POSIX_C_SOURCE` |
| `acquire_page_sheet` | function | `src/page_view.c:4905` | `static shc_sheet *acquire_page_sheet(lxb_dom_node_t *root, const char *extern_css,               ...` |
| `address` | function | `src/page_view.c:1274` | `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <=...` |
| `after_pending_emit` | function | `src/page_view.c:1958` | `static pv_status after_pending_emit(pv_view *v, pv_container_reg *reg, pv_item_track *items,     ...` |
| `annotate_flow_run` | function | `src/page_view.c:1909` | `static void annotate_flow_run(pv_view *v, pv_container_reg *reg, pv_item_track *items,           ...` |
| `annotate_replaced_run` | function | `src/page_view.c:5754` | `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,                             ...` |
| `ascii_ieq` | function | `src/page_view.c:4964` | `static int ascii_ieq(const char *s, const char *lit)` |
| `attr_dup` | function | `src/page_view.c:4976` | `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)` |
| `attributes` | function | `src/page_view.c:4855` | `* carries those attributes (spec/css.md, "Root matcher"). */ static int root_els_match(void *ctx,...` |
| `band` | function | `src/page_view.c:6646` | `* run: without its float annotation it cut the band (the icon row of a * `float:right` social list became one float...` |
| `block` | function | `src/page_view.c:7249` | `* block (Gecko): it never resolves as its own block here. */ int opens_line = block != n && (pending_break \|\| block...` |
| `block_id` | function | `src/page_view.c:6831` | `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it...` |
| `border_side_cleared` | function | `src/page_view.c:1621` | `static int border_side_cleared(int width, int style)` |
| `box_reg_free` | function | `src/page_view.c:2025` | `static void box_reg_free(pv_box_reg *r)` |
| `box_reg_id` | function | `src/page_view.c:2285` | `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,            ...` |
| `box_reg_id_ex` | function | `src/page_view.c:2978` | `static int box_reg_id_ex(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,         ...` |
| `boxdef_from_style` | function | `src/page_view.c:2034` | `static void boxdef_from_style(pv_box_def *d, const css_style *cs)` |
| `builder` | function | `src/page_view.c:3103` | `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box  * (the ...` |
| `cached_element_style` | function | `src/page_view.c:2874` | `static css_style cached_element_style(lxb_dom_element_t *el, const css_sheet *sheet,             ...` |
| `cached_element_style_ref` | function | `src/page_view.c:2789` | `static const css_style *cached_element_style_ref(lxb_dom_element_t *el, const css_sheet *sheet,  ...` |
| `cached_pseudo_style` | function | `src/page_view.c:3038` | `static css_style cached_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet,              ...` |
| `causes_block_break` | function | `src/page_view.c:1115` | `static int causes_block_break(lxb_tag_id_t t, css_display display)` |
| `cell_has_nested_table` | function | `src/page_view.c:5414` | `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)` |
| `cell_is_grid_item` | function | `src/page_view.c:5548` | `static int cell_is_grid_item(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,             ...` |
| `cell_is_rich` | function | `src/page_view.c:5512` | `static int cell_is_rich(const lxb_dom_node_t *cell)` |
| `cell_kind` | function | `src/page_view.c:5539` | `static unsigned cell_kind(pv_flow_reg *fr, const lxb_dom_node_t *cell)` |
| `cell_span_attr` | function | `src/page_view.c:5438` | `static int cell_span_attr(const lxb_dom_node_t *cell, const char *name, size_t name_len,         ...` |
| `chain` | type_alias | `src/page_view.c:2377` | `typedef struct pv_var_node { cvr_chain chain;` |
| `child` | function | `src/page_view.c:1282` | `* child (NULL = anonymous item: text directly inside the container);` |
| `children_all_inline_block` | function | `src/page_view.c:3249` | `static int children_all_inline_block(const lxb_dom_node_t *p, const css_sheet *sheet,            ...` |
| `classify_input` | function | `src/page_view.c:5058` | `static pv_input_type classify_input(const char *type)` |
| `col_free_share` | function | `src/page_view.c:2935` | `static int col_free_share(const lxb_dom_node_t *el, const css_style *cs, const css_sheet *sheet, pv_style_cache...` |
| `col_has_free_space` | function | `src/page_view.c:3302` | `static int col_has_free_space(const css_style *cs)` |
| `collapse_ws` | function | `src/page_view.c:4599` | `static char *collapse_ws(const char *s, size_t n)` |
| `collect_page_css` | function | `src/page_view.c:5839` | `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,                      ...` |
| `collect_text` | function | `src/page_view.c:5034` | `static char *collect_text(const lxb_dom_node_t *el)` |
| `cols` | type_alias | `src/page_view.c:1284` | `typedef struct pv_cont_info { int id, display, gap, justify, cols;` |
| `column_gap_candidate` | function | `src/page_view.c:3418` | `static int column_gap_candidate(const lxb_dom_node_t *el, const css_sheet *sheet,                ...` |
| `cont_def_reset` | function | `src/page_view.c:1782` | `static void cont_def_reset(pv_cont_def *d)` |
| `cont_reg_free` | function | `src/page_view.c:1815` | `static void cont_reg_free(pv_container_reg *reg)` |
| `cont_reg_init` | function | `src/page_view.c:1802` | `static int cont_reg_init(pv_container_reg *reg, size_t cap)` |
| `container` | function | `src/page_view.c:4251` | `* membership in this container (and none in any container further out,                  * since i...` |
| `container_id` | function | `src/page_view.c:1821` | `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)` |
| `content` | function | `src/page_view.c:1213` | `* a <noscript> ancestor also suppresses content (the script would run, so the * fallback is hidden);` |
| `control` | function | `src/page_view.c:6402` | `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);` |
| `cp1252_to_ucs` | function | `src/page_view.c:95` | `static unsigned int cp1252_to_ucs(unsigned char c)` |
| `css_has_boxdeco` | function | `src/page_view.c:1635` | `static int css_has_boxdeco(const css_style *cs)` |
| `css_has_hbox` | function | `src/page_view.c:1540` | `static int css_has_hbox(const css_style *cs)` |
| `css_has_hmargin` | function | `src/page_view.c:3454` | `static int css_has_hmargin(const css_style *cs)` |
| `css_has_position` | function | `src/page_view.c:1614` | `static int css_has_position(const css_style *cs)` |
| `css_hbox_resolve` | function | `src/page_view.c:1561` | `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)` |
| `css_inline_boxdeco` | function | `src/page_view.c:4085` | `css_inline_boxdeco(cs) &&                            !is_layout_item(p, sheet, style_cache))` |
| `css_replaced_h_fixed` | function | `src/page_view.c:3085` | `static int css_replaced_h_fixed(lxb_dom_element_t *el, const css_sheet *sheet,                   ...` |
| `css_to_fx_justify` | function | `src/page_view.c:3132` | `static int css_to_fx_justify(css_justify j)` |
| `css_width_declared` | function | `src/page_view.c:2962` | `static int css_width_declared(const css_style *cs)` |
| `dimensions` | function | `src/page_view.c:4796` | `* viewport dimensions (data: inline detection, <picture> <source> scanning). */ static void srcse...` |
| `dup_n` | function | `src/page_view.c:156` | `static char *dup_n(const char *s, size_t n)` |
| `element_is_content_leaf` | function | `src/page_view.c:3682` | `static int element_is_content_leaf(const lxb_dom_node_t *n, const css_sheet *sheet,              ...` |
| `element_is_content_leaf_d` | function | `src/page_view.c:3642` | `static int element_is_content_leaf_d(const lxb_dom_node_t *n, const css_sheet *sheet,            ...` |
| `engine` | function | `src/page_view.c:7537` | `* layout engine (contiguous item gather) drops every cell onto its own row and          * a 2-col...` |
| `find_body` | function | `src/page_view.c:4828` | `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)` |
| `find_root_els` | function | `src/page_view.c:4841` | `static pv_root_els find_root_els(lxb_dom_node_t *root)` |
| `flex_column_flows_as_block` | function | `src/page_view.c:3316` | `static int flex_column_flows_as_block(const lxb_dom_node_t *el, const css_style *cs,             ...` |
| `flex_column_flows_as_block_uncached` | function | `src/page_view.c:3325` | `static int flex_column_flows_as_block_uncached(const lxb_dom_node_t *el, const css_style *cs,    ...` |
| `float` | function | `src/page_view.c:4512` | `* genuinely nested float (oid != id) takes the deferred-column path. */     if (cont->float_oid =...` |
| `flow` | function | `src/page_view.c:7428` | `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through...` |
| `fold_column_gap` | function | `src/page_view.c:3393` | `static void fold_column_gap(const lxb_dom_node_t *el, css_style *cs,                             ...` |
| `font_color_attr` | function | `src/page_view.c:1253` | `static int font_color_attr(lxb_dom_element_t *el)` |
| `form_for` | function | `src/page_view.c:5005` | `static int form_for(const form_table *ft, const lxb_dom_node_t *n,                     const lxb_...` |
| `form_rec` | struct | `src/page_view.c:4946` | `` |
| `form_table` | struct | `src/page_view.c:4952` | `` |
| `forms_add` | function | `src/page_view.c:4985` | `static int forms_add(form_table *ft, const lxb_dom_node_t *node)` |
| `forms_free` | function | `src/page_view.c:4957` | `static void forms_free(form_table *ft)` |
| `generates_box` | function | `src/page_view.c:1096` | `static int generates_box(lxb_tag_id_t t, css_display display)` |
| `generates_box_style` | function | `src/page_view.c:1108` | `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)` |
| `glyphs` | function | `src/page_view.c:2187` | `* glyphs (the runs carry it as their fill source);` |
| `heading_level` | function | `src/page_view.c:1175` | `static int heading_level(lxb_tag_id_t t)` |
| `height` | function | `src/page_view.c:6673` | `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `here` | function | `src/page_view.c:2136` | `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3...` |
| `id` | function | `src/page_view.c:1306` | `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);` |
| `ignored` | function | `src/page_view.c:695` | `* source is ignored (fail-visible: never invisible text from half a      * pattern). A real text-...` |
| `in_boilerplate_subtree` | function | `src/page_view.c:5689` | `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` |
| `in_closed_details_subtree` | function | `src/page_view.c:5704` | `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` |
| `in_collected_cell` | function | `src/page_view.c:5558` | `static int in_collected_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,                ...` |
| `in_hidden_subtree` | function | `src/page_view.c:5662` | `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,                ...` |
| `in_mixed_line` | function | `src/page_view.c:3201` | `static int in_mixed_line(const lxb_dom_node_t *p, const css_sheet *sheet,                        ...` |
| `in_skipped_subtree` | function | `src/page_view.c:1216` | `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,               ...` |
| `inherited_text_color` | function | `src/page_view.c:2941` | `static int inherited_text_color(const lxb_dom_node_t *node, const css_sheet *sheet,              ...` |
| `inside` | function | `src/page_view.c:6096` | `* page inside (the top one collapses with the first child's margin), so a * margin-only body stays box-less. */...` |
| `is_block_like` | function | `src/page_view.c:1045` | `static int is_block_like(lxb_tag_id_t t, css_display display)` |
| `is_block_like_style` | function | `src/page_view.c:1084` | `static int is_block_like_style(lxb_tag_id_t t, const css_style *cs)` |
| `is_block_tag` | function | `src/page_view.c:1020` | `static int is_block_tag(lxb_tag_id_t t)` |
| `is_bold_tag` | function | `src/page_view.c:3151` | `static int is_bold_tag(lxb_tag_id_t t)` |
| `is_float_container_style` | function | `src/page_view.c:3222` | `static int is_float_container_style(const css_style *cs)` |
| `is_inline_container_style` | function | `src/page_view.c:2954` | `static int is_inline_container_style(const css_style *cs)` |
| `is_inline_level_style` | function | `src/page_view.c:3193` | `static int is_inline_level_style(lxb_tag_id_t t, const css_style *cs)` |
| `is_italic_tag` | function | `src/page_view.c:3156` | `static int is_italic_tag(lxb_tag_id_t t)` |
| `is_layout_container` | function | `src/page_view.c:3428` | `static int is_layout_container(const lxb_dom_node_t *el, const css_style *cs,                    ...` |
| `is_plain_wrapper` | function | `src/page_view.c:3630` | `static int is_plain_wrapper(const lxb_dom_node_t *c, const css_style *cs)` |
| `is_skipped_tag` | function | `src/page_view.c:1187` | `static int is_skipped_tag(lxb_tag_id_t t)` |
| `it` | function | `src/page_view.c:3277` | `* without it (minified markup) keeps the row gapless -- the mixed case is a known limit. */ stati...` |
| `item_ordinal` | function | `src/page_view.c:1396` | `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)` |
| `item_sizes_itself` | function | `src/page_view.c:3483` | `static int item_sizes_itself(const lxb_dom_node_t *el, const css_style *cs,                      ...` |
| `item_space_before` | function | `src/page_view.c:1381` | `static int item_space_before(const lxb_dom_node_t *item)` |
| `li_is_list_item` | function | `src/page_view.c:3499` | `static int li_is_list_item(const lxb_dom_node_t *li, const css_sheet *sheet,                     ...` |
| `li_ordinal` | function | `src/page_view.c:5229` | `static int li_ordinal(const lxb_dom_node_t *li)` |
| `line` | function | `src/page_view.c:7546` | `* to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);` |
| `list_marker` | function | `src/page_view.c:5280` | `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,                   ...` |
| `margins` | function | `src/page_view.c:4124` | `* margins (boxdef_from_style) and the painter applies them when                          * it ope...` |
| `mb` | type_alias | `src/page_view.c:1420` | `typedef struct pv_box_info { int l, r, w, center, mt, mb;` |
| `media_has_source` | function | `src/page_view.c:3668` | `static int media_has_source(const lxb_dom_node_t *n)` |
| `nearest_table` | function | `src/page_view.c:5343` | `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,  ...` |
| `next_skip` | function | `src/page_view.c:5428` | `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)` |
| `node_next` | function | `src/page_view.c:1010` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `node_table_role` | function | `src/page_view.c:5325` | `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `node_tag` | function | `src/page_view.c:1208` | `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)` |
| `none` | function | `src/page_view.c:2983` | `* inherited when it declares none (every hamburger bar and divider drawn as * a coloured empty box). A box cannot...` |
| `opens` | function | `src/page_view.c:4037` | `* painter applies it when the box opens (band/shared context) — seeding              * it onto ru...` |
| `outermost` | function | `src/page_view.c:3980` | `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);` |
| `paints` | function | `src/page_view.c:1128` | `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas  * vacías"). Comment a...` |
| `parent_is_author_container` | function | `src/page_view.c:2969` | `static int parent_is_author_container(const lxb_dom_node_t *node, const css_sheet *sheet,        ...` |
| `parent_is_table_internal` | function | `src/page_view.c:5382` | `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `parse_dim` | function | `src/page_view.c:4638` | `static int parse_dim(const lxb_char_t *s, size_t len)` |
| `positions` | function | `src/page_view.c:145` | `* positions (cp == 0) keep the legacy '?' fallback. */ unsigned int cp = cp1252_to_ucs(c);` |
| `present` | function | `src/page_view.c:4655` | `* when no width descriptors are present (density-only or bare URLs). */ static void srcset_best_u...` |
| `pseudo_box_reg` | function | `src/page_view.c:2314` | `static int pseudo_box_reg(pv_box_reg *r, const lxb_dom_node_t *el, int which,                    ...` |
| `pseudo_generates_box` | function | `src/page_view.c:2335` | `static int pseudo_generates_box(const css_style *ps)` |
| `pseudo_is_block` | function | `src/page_view.c:2352` | `static int pseudo_is_block(const css_style *ps)` |
| `pseudo_is_oof` | function | `src/page_view.c:2348` | `static int pseudo_is_oof(const css_style *ps)` |
| `pseudo_key` | function | `src/page_view.c:2358` | `static const void *pseudo_key(const lxb_dom_node_t *el, int which)` |
| `pv_add_box_def` | function | `src/page_view.c:958` | `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)` |
| `pv_add_cont_def` | function | `src/page_view.c:936` | `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)` |
| `pv_after_pending` | struct | `src/page_view.c:1944` | `` |
| `pv_append` | function | `src/page_view.c:441` | `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,                     c...` |
| `pv_append_image` | function | `src/page_view.c:476` | `pv_status pv_append_image(pv_view *v, int heading, int block_break,                           con...` |
| `pv_append_input` | function | `src/page_view.c:506` | `pv_status pv_append_input(pv_view *v, int heading, int block_break,                           pv_...` |
| `pv_append_svg` | function | `src/page_view.c:582` | `pv_status pv_append_svg(pv_view *v, int heading, int block_break,                         const c...` |
| `pv_append_video` | function | `src/page_view.c:546` | `pv_status pv_append_video(pv_view *v, int heading, int block_break,                           con...` |
| `pv_apply_pres_hints` | function | `src/page_view.c:2694` | `static void pv_apply_pres_hints(lxb_dom_element_t *el, css_style *cs)` |
| `pv_at` | function | `src/page_view.c:993` | `const pv_run *pv_at(const pv_view *v, size_t i)` |
| `pv_box_at` | function | `src/page_view.c:1002` | `const pv_box_def *pv_box_at(const pv_view *v, size_t i)` |
| `pv_box_count` | function | `src/page_view.c:998` | `size_t pv_box_count(const pv_view *v)` |
| `pv_box_info` | struct | `src/page_view.c:1420` | `` |
| `pv_box_reg` | struct | `src/page_view.c:1986` | `` |
| `pv_build` | function | `src/page_view.c:5724` | `pv_status pv_build(const hp_document *doc, pv_view **out)` |
| `pv_build_cached` | function | `src/page_view.c:5972` | `pv_status pv_build_cached(const hp_document *doc, int js_enabled, int reader,                    ...` |
| `pv_build_cq` | function | `src/page_view.c:5979` | `pv_status pv_build_cq(const hp_document *doc, int js_enabled, int reader,                       i...` |
| `pv_build_ex` | function | `src/page_view.c:5728` | `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)` |
| `pv_build_full` | function | `src/page_view.c:5732` | `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,                      ...` |
| `pv_build_live` | function | `src/page_view.c:5986` | `pv_status pv_build_live(const hp_document *doc, int js_enabled, int reader,                      ...` |
| `pv_build_styled` | function | `src/page_view.c:5965` | `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,                    ...` |
| `pv_cache_find` | function | `src/page_view.c:2534` | `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cache_put` | function | `src/page_view.c:2554` | `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,                      ...` |
| `pv_cache_reindex` | function | `src/page_view.c:2452` | `static void pv_cache_reindex(pv_style_cache *c)` |
| `pv_cached_font_px` | function | `src/page_view.c:2549` | `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cnt_attr` | function | `src/page_view.c:5881` | `static const char *pv_cnt_attr(void *ctx, const char *name)` |
| `pv_cnt_attr_ctx` | struct | `src/page_view.c:5876` | `` |
| `pv_cnt_enter` | function | `src/page_view.c:5905` | `static int pv_cnt_enter(cnt_state *st, lxb_dom_node_t *n, int depth, const css_sheet *sheet,     ...` |
| `pv_cnt_exit` | function | `src/page_view.c:5929` | `static void pv_cnt_exit(cnt_state *st, lxb_dom_node_t *n, int depth, const css_sheet *sheet,     ...` |
| `pv_cnt_resolve_field` | function | `src/page_view.c:5894` | `static void pv_cnt_resolve_field(const cnt_state *st, lxb_dom_element_t *el, char *field)` |
| `pv_computed` | struct | `src/page_view.c:7734` | `` |
| `pv_computed_free` | function | `src/page_view.c:7780` | `void pv_computed_free(pv_computed *pc)` |
| `pv_computed_get` | function | `src/page_view.c:7758` | `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st,                     do...` |
| `pv_computed_new` | function | `src/page_view.c:7739` | `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css,   ...` |
| `pv_computed_new_cached` | function | `src/page_view.c:7744` | `pv_computed *pv_computed_new_cached(const hp_document *doc, int prefers_dark,                    ...` |
| `pv_cont_at` | function | `src/page_view.c:953` | `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)` |
| `pv_cont_count` | function | `src/page_view.c:949` | `size_t pv_cont_count(const pv_view *v)` |
| `pv_cont_info` | struct | `src/page_view.c:1284` | `` |
| `pv_container_reg` | struct | `src/page_view.c:1768` | `` |
| `pv_content_hidden` | function | `src/page_view.c:1441` | `int pv_content_hidden(int box_hidden, int run_visibility)` |
| `pv_control_frame_cleared` | function | `src/page_view.c:1627` | `static int pv_control_frame_cleared(const css_style *cs)` |
| `pv_count` | function | `src/page_view.c:989` | `size_t pv_count(const pv_view *v)` |
| `pv_counters_pass` | function | `src/page_view.c:5941` | `static void pv_counters_pass(lxb_dom_node_t *root, const css_sheet *sheet, pv_style_cache *cache)` |
| `pv_cq_push` | function | `src/page_view.c:2627` | `static const cmq_container *pv_cq_push(pv_style_cache *cache, const lxb_dom_node_t *node,        ...` |
| `pv_css_drops` | function | `src/page_view.c:7705` | `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,                        const cha...` |
| `pv_def_h` | struct | `src/page_view.c:2386` | `` |
| `pv_element_has_before` | function | `src/page_view.c:3576` | `static int pv_element_has_before(lxb_dom_node_t *n, const css_sheet *sheet,                      ...` |
| `pv_flow_reg` | struct | `src/page_view.c:3687` | `` |
| `pv_flow_reg` | struct | `src/page_view.c:5305` | `` |
| `pv_frame_marked` | function | `src/page_view.c:4629` | `static int pv_frame_marked(const lxb_dom_node_t *n)` |
| `pv_free` | function | `src/page_view.c:971` | `void pv_free(pv_view *v)` |
| `pv_hint_attr` | function | `src/page_view.c:2673` | `static const char *pv_hint_attr(void *ctx, const char *name, size_t *len)` |
| `pv_item_track` | struct | `src/page_view.c:1367` | `` |
| `pv_mauto_of` | function | `src/page_view.c:1554` | `static int pv_mauto_of(const css_style *cs)` |
| `pv_new` | function | `src/page_view.c:437` | `pv_view *pv_new(void)` |
| `pv_node_map` | struct | `src/page_view.c:356` | `` |
| `pv_node_map_build` | function | `src/page_view.c:426` | `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root,                         ...` |
| `pv_node_map_free` | function | `src/page_view.c:374` | `static void pv_node_map_free(pv_node_map *m)` |
| `pv_node_map_init` | function | `src/page_view.c:364` | `static int pv_node_map_init(pv_node_map *m)` |
| `pv_parent_element` | function | `src/page_view.c:2666` | `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)` |
| `pv_placeholder_color` | function | `src/page_view.c:920` | `int pv_placeholder_color(const css_style *ph)` |
| `pv_ptr_hash` | function | `src/page_view.c:2444` | `static size_t pv_ptr_hash(const void *p)` |
| `pv_ptrmap` | struct | `src/page_view.c:302` | `` |
| `pv_ptrmap_free` | function | `src/page_view.c:348` | `static void pv_ptrmap_free(pv_ptrmap *m)` |
| `pv_ptrmap_get` | function | `src/page_view.c:318` | `static int pv_ptrmap_get(const pv_ptrmap *m, const void *k, int *out)` |
| `pv_ptrmap_put` | function | `src/page_view.c:326` | `static void pv_ptrmap_put(pv_ptrmap *m, const void *k, int v)` |
| `pv_ptrmap_slot` | function | `src/page_view.c:308` | `static size_t pv_ptrmap_slot(const pv_ptrmap *m, const void *k)` |
| `pv_root_els` | struct | `src/page_view.c:4837` | `` |
| `pv_root_insets` | function | `src/page_view.c:5829` | `void pv_root_insets(const css_style *body, int out[4])` |
| `pv_set_bgcolor` | function | `src/page_view.c:628` | `void pv_set_bgcolor(pv_view *v, int bg_rgb)` |
| `pv_set_block_id` | function | `src/page_view.c:851` | `void pv_set_block_id(pv_view *v, int block_id)` |
| `pv_set_block_node` | function | `src/page_view.c:871` | `void pv_set_block_node(pv_view *v, dom_node_id id)` |
| `pv_set_box` | function | `src/page_view.c:810` | `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,                 int box_center, int ...` |
| `pv_set_box_maxw` | function | `src/page_view.c:833` | `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct)` |
| `pv_set_box_pct` | function | `src/page_view.c:822` | `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,                     ...` |
| `pv_set_br_line` | function | `src/page_view.c:876` | `void pv_set_br_line(pv_view *v, int br_line)` |
| `pv_set_color` | function | `src/page_view.c:623` | `void pv_set_color(pv_view *v, int fg_rgb)` |
| `pv_set_cont_box` | function | `src/page_view.c:750` | `void pv_set_cont_box(pv_view *v, int cont_box_id)` |
| `pv_set_cont_item` | function | `src/page_view.c:772` | `void pv_set_cont_item(pv_view *v, int cont_item)` |
| `pv_set_container` | function | `src/page_view.c:710` | `void pv_set_container(pv_view *v, int cont_id, int cont_display,                       int cont_g...` |
| `pv_set_emphasis` | function | `src/page_view.c:611` | `void pv_set_emphasis(pv_view *v, int bold, int italic)` |
| `pv_set_flex` | function | `src/page_view.c:754` | `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,                  int...` |
| `pv_set_flex_mauto` | function | `src/page_view.c:766` | `void pv_set_flex_mauto(pv_view *v, int mauto)` |
| `pv_set_float` | function | `src/page_view.c:788` | `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear,                 int ...` |
| `pv_set_float_w` | function | `src/page_view.c:777` | `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box,                     ...` |
| `pv_set_grad_text` | function | `src/page_view.c:644` | `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)` |
| `pv_set_grid` | function | `src/page_view.c:736` | `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)` |
| `pv_set_grid_area` | function | `src/page_view.c:729` | `void pv_set_grid_area(pv_view *v, int row_start, int col_start)` |
| `pv_set_grid_rows` | function | `src/page_view.c:746` | `void pv_set_grid_rows(pv_view *v, int grid_rows)` |
| `pv_set_indent` | function | `src/page_view.c:618` | `void pv_set_indent(pv_view *v, int indent)` |
| `pv_set_input_checked` | function | `src/page_view.c:881` | `void pv_set_input_checked(pv_view *v, int checked)` |
| `pv_set_input_placeholder` | function | `src/page_view.c:886` | `void pv_set_input_placeholder(pv_view *v, int ph_color)` |
| `pv_set_input_select_opts` | function | `src/page_view.c:928` | `void pv_set_input_select_opts(pv_view *v, const char *select_opts)` |
| `pv_set_justify_self` | function | `src/page_view.c:866` | `void pv_set_justify_self(pv_view *v, int justify_self)` |
| `pv_set_node_id` | function | `src/page_view.c:846` | `void pv_set_node_id(pv_view *v, dom_node_id node_id)` |
| `pv_set_oof` | function | `src/page_view.c:861` | `void pv_set_oof(pv_view *v, int oof)` |
| `pv_set_own_box` | function | `src/page_view.c:856` | `void pv_set_own_box(pv_view *v, int box_id)` |
| `pv_set_row_span` | function | `src/page_view.c:725` | `void pv_set_row_span(pv_view *v, int row_span)` |
| `pv_set_text_ext` | function | `src/page_view.c:652` | `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)` |
| `pv_set_text_style` | function | `src/page_view.c:633` | `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,                 ...` |
| `pv_set_ua_tag` | function | `src/page_view.c:840` | `void pv_set_ua_tag(pv_view *v, int ua_tag)` |
| `pv_style_cache` | struct | `src/page_view.c:2400` | `` |
| `pv_style_cache_free` | function | `src/page_view.c:2488` | `static void pv_style_cache_free(pv_style_cache *c)` |
| `pv_style_cache_reserve` | function | `src/page_view.c:2509` | `static void pv_style_cache_reserve(pv_style_cache *c, size_t n)` |
| `pv_svg_append_root_attrs` | function | `src/page_view.c:891` | `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs,                ...` |
| `pv_text_ext_merge` | function | `src/page_view.c:1475` | `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)` |
| `pv_text_ext_reset` | function | `src/page_view.c:1447` | `void pv_text_ext_reset(pv_text_ext *e)` |
| `pv_var_node` | struct | `src/page_view.c:2377` | `` |
| `pv_var_push` | function | `src/page_view.c:2604` | `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,                       ...` |
| `px` | function | `src/page_view.c:6580` | `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */                 if (iw <...` |
| `resolve_context` | function | `src/page_view.c:3699` | `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,                 ...` |
| `resolves` | function | `src/page_view.c:1074` | `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close  * button/tooltip w...` |
| `roman_marker` | function | `src/page_view.c:5255` | `static void roman_marker(int n, int upper, char *out, size_t cap)` |
| `row_lone_float_side` | function | `src/page_view.c:3230` | `static int row_lone_float_side(const lxb_dom_node_t *p, const css_sheet *sheet,                  ...` |
| `run_init_common` | function | `src/page_view.c:170` | `static void run_init_common(pv_run *r)` |

Next: [SYMBOLS_p10.md](SYMBOLS_p10.md)
