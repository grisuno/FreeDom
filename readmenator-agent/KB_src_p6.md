# Subsystem: src (page 6 of 10)
Previous: [KB_src_p5.md](KB_src_p5.md)

## src/js_geom.c
- Doc: unite: Bounding box of a and b into a; returns 1 if a changed.
- Layer: utility
- Language: c
- Symbols:
  - `jg_init` (function, line 17) `void jg_init(jg_table *t)`
  - `jg_free` (function, line 21) `void jg_free(jg_table *t)`
  - `clamp_coord` (function, line 27) `static int32_t clamp_coord(double v, double lo)`
  - `grow` (function, line 33) `static int grow(jg_table *t)`
  - `push` (function, line 45) `static int push(jg_table *t, dom_node_id node, int32_t x, int32_t y, int32_t w, int32_t h)`
  - `jg_add` (function, line 52) `int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h)`
  - `unite` (function, line 63) `static int unite(jg_rect *a, const jg_rect *b)`
  - `cmp_node` (function, line 78) `static int cmp_node(const void *pa, const void *pb)`
  - `jg_finish` (function, line 83) `int jg_finish(jg_table *t)`
  - `jg_find` (function, line 96) `const jg_rect *jg_find(const jg_table *t, dom_node_id node)`
  - `slot_of` (function, line 102) `static uint32_t slot_of(dom_node_id n)`
  - `index_of` (function, line 109) `static size_t index_of(jg_table *t, uint32_t *slots, dom_node_id node, const jg_rect *seed,
     ...`
  - `jg_aggregate` (function, line 124) `int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx)`
  - `jg_wire_len` (function, line 163) `size_t jg_wire_len(const jg_table *t)`
  - `jg_encode` (function, line 167) `int jg_encode(const jg_table *t, int32_t *out, size_t cap)`
  - `in_range` (function, line 182) `static int in_range(int32_t v, int32_t lo)`
  - `jg_decode` (function, line 186) `int jg_decode(const int32_t *in, size_t n, jg_table *out)`
  - `fnv` (function, line 212) `static uint64_t fnv(uint64_t h, int32_t v)`
  - `jg_hash` (function, line 221) `uint64_t jg_hash(const jg_table *t)`
  - `JG_INDEX_SLOTS` (macro, line 14) `#define JG_INDEX_SLOTS`
  - `JG_SLOT_EMPTY` (macro, line 15) `#define JG_SLOT_EMPTY`
- Depends on: `include/js_geom.h`

## src/js_intl.c
- Layer: utility
- Language: c
- Symbols:
  - `ji_install` (function, line 423) `int ji_install(js_context *ctx)`
- Depends on: `include/js_intl.h`

## src/js_location.c
- Doc: jd_lp_set: Defines a string property on the __locParts data object from a (ptr,len) span. * The...
- Layer: utility
- Language: c
- Symbols:
  - `jd_lp_set` (function, line 25) `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,
                      const ...`
  - `jl_m_hist_target` (function, line 36) `JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `jd_set_location` (function, line 140) `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)`
  - `jd_take_nav_request` (function, line 174) `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)`
  - `jd_take_history` (function, line 220) `char *jd_take_history(js_context *ctx, int *go)`
  - `jd_pop_state` (function, line 251) `int jd_pop_state(js_context *ctx, int index)`
- Depends on: `include/js_dom.h`, `include/url.h`, `src/js_location_internal.h`, `src/js_native_internal.h`

## src/js_location_internal.h
- Doc: Private to js_dom.c / js_location.c: the dom.histTarget native lives with the
- Layer: utility
- Language: h
- Symbols:
  - `header` (function, line 6) `* stay out of every public header (include/ never sees quickjs.h). */ #include "quickjs.h" JSValue...`
  - `FREEDOM_JS_LOCATION_INTERNAL_H` (macro, line 2) `#define FREEDOM_JS_LOCATION_INTERNAL_H`
- Imported by: `src/js_dom.c`, `src/js_location.c`

## src/js_native.c
- Doc: jn_css_ok: __cssOk(decl): 1 when the cascade keeps `decl` ("prop: value") whole.
- Layer: utility
- Language: c
- Symbols:
  - `jn_host_eval` (function, line 15) `JSValue jn_host_eval(JSContext *c, const char *src, size_t len, const char *name)`
  - `jn_css_ok` (function, line 25) `static JSValue jn_css_ok(JSContext *c, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `jn_seal` (function, line 144) `int jn_seal(js_context *ctx)`
  - `JN_SUPPORTS_MAX` (macro, line 13) `#define JN_SUPPORTS_MAX`
- Depends on: `include/css.h`, `include/js_native.h`, `src/js_native_internal.h`

## src/js_native_internal.h
- Doc: js_context: One engine value the host keeps for the lifetime of a context, out of the page's...
- Layer: utility
- Language: h
- Symbols:
  - `js_context` (struct, line 20)
  - `js_host_slot` (function, line 21) `JSValue *js_host_slot(struct js_context *ctx);`
  - `FREEDOM_JS_NATIVE_INTERNAL_H` (macro, line 6) `#define FREEDOM_JS_NATIVE_INTERNAL_H`
- Imported by: `src/js_custom_elements.c`, `src/js_dom.c`, `src/js_dom_ext.c`, `src/js_embed.c`, `src/js_env.c`, `src/js_events.c`, `src/js_fetch.c`, `src/js_location.c`, `src/js_native.c`, `src/js_trusted.c`

## src/js_policy.c
- Doc: eq_ci: js_policy — implementation: pure per-host JavaScript policy decision.
- Layer: business_logic
- Language: c
- Symbols:
  - `eq_ci` (function, line 12) `static int eq_ci(const char *a, const char *b)`
  - `jsp_enabled` (function, line 22) `bool jsp_enabled(jsp_mode mode, int host_allowlisted)`
  - `jsp_trusted` (function, line 31) `bool jsp_trusted(bool js_enabled, int host_allowlisted)`
  - `jsp_present_trusted` (function, line 35) `bool jsp_present_trusted(int host_allowlisted)`
  - `jsp_mode_from_str` (function, line 39) `jsp_mode jsp_mode_from_str(const char *s)`
  - `jsp_mode_str` (function, line 51) `const char *jsp_mode_str(jsp_mode mode)`
- Depends on: `include/js_policy.h`

## src/js_sandbox.c
- Doc: js_mem_state: We enforce the heap cap ourselves (not via JS_SetMemoryLimit, whose check runs...
- Layer: utility
- Language: c
- Symbols:
  - `js_mem_state` (struct, line 29)
  - `js_context` (struct, line 38)
  - `limit` (type_alias, line 29) `typedef struct js_mem_state { size_t limit;`
  - `js_host_slot` (function, line 76) `JSValue *js_host_slot(struct js_context *ctx)`
  - `rej_remove` (function, line 82) `static void rej_remove(js_context *c, size_t i)`
  - `js_rejection_cb` (function, line 90) `static void js_rejection_cb(JSContext *jc, JSValueConst promise, JSValueConst reason,
           ...`
  - `rej_report` (function, line 109) `static void rej_report(js_context *c)`
  - `jm_malloc` (function, line 134) `static void *jm_malloc(void *opaque, size_t size)`
  - `jm_calloc` (function, line 142) `static void *jm_calloc(void *opaque, size_t count, size_t size)`
  - `jm_free` (function, line 152) `static void jm_free(void *opaque, void *ptr)`
  - `jm_realloc` (function, line 158) `static void *jm_realloc(void *opaque, void *ptr, size_t size)`
  - `jm_usable_size` (function, line 168) `static size_t jm_usable_size(const void *ptr)`
  - `host_dup` (function, line 178) `static char *host_dup(const char *src, size_t len)`
  - `timespec_reached` (function, line 187) `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)`
  - `timespec_diff_ms` (function, line 192) `static long timespec_diff_ms(const struct timespec *a, const struct timespec *b)`
  - `profile_sample` (function, line 197) `static void profile_sample(js_context *c, unsigned weight_ms)`
  - `js_profile_enable` (function, line 229) `void js_profile_enable(js_context *ctx)`
  - `js_profile_report` (function, line 235) `size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n)`
  - `throw_key` (function, line 258) `static void throw_key(JSContext *ctx, JSValueConst obj, char *key, size_t cap)`
  - `throw_hook_cb` (function, line 315) `static void throw_hook_cb(JSContext *ctx, JSValueConst obj, void *opaque)`
  - `js_throws_enable` (function, line 335) `void js_throws_enable(js_context *ctx)`
  - `js_throws_report` (function, line 341) `size_t js_throws_report(js_context *ctx, char *out, size_t cap, size_t top_n)`
  - `m_fb_report` (function, line 363) `static JSValue m_fb_report(JSContext *jsctx, JSValueConst this_val, int argc, JSValueConst *argv,...`
  - `js_devtools_enable` (function, line 379) `void js_devtools_enable(js_context *ctx)`
  - `js_devtools_expose` (function, line 385) `js_status js_devtools_expose(js_context *ctx)`
  - `js_interrupt_cb` (function, line 401) `static int js_interrupt_cb(JSRuntime *rt, void *opaque)`
  - `is_ascii_digit` (function, line 425) `static int is_ascii_digit(char c)`
  - `js_loc_from_stack` (function, line 427) `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      i...`
  - `js_stack_limit_for` (function, line 546) `size_t js_stack_limit_for(size_t soft_stack)`
  - `process_soft_stack` (function, line 557) `static size_t process_soft_stack(void)`
  - `js_prime_stack_limit` (function, line 567) `void js_prime_stack_limit(void)`
  - `js_limits_default` (function, line 569) `js_limits js_limits_default(void)`
  - `limits_resolve` (function, line 578) `static js_limits limits_resolve(const js_limits *lim)`
  - `js_validate_source` (function, line 587) `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)`
  - `js_context_new` (function, line 598) `js_status js_context_new(const js_limits *lim, js_context **out)`
  - `js_context_free` (function, line 639) `void js_context_free(js_context *ctx)`
  - `arm_deadline` (function, line 652) `static void arm_deadline(js_context *ctx, uint64_t budget_ms)`
  - `js_set_time_budget` (function, line 667) `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)`
  - `js_eval` (function, line 672) `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)`
  - `js_eval_named` (function, line 676) `js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        con...`
  - `js_pump_jobs` (function, line 759) `int js_pump_jobs(js_context *ctx, int max_jobs)`
  - `js_eval_once` (function, line 778) `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)`
  - `js_result_free` (function, line 791) `void js_result_free(js_result *res)`
  - `js_set_current_script` (function, line 819) `void js_set_current_script(js_context *ctx, const char *src, const char *type)`
  - `js_context_raw` (function, line 855) `void *js_context_raw(js_context *ctx)`
  - `mod_set_meta` (function, line 887) `static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url)`
  - `mod_loader` (function, line 896) `static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque)`
  - `js_set_module_host` (function, line 935) `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,
                        js...`
  - `mod_fail` (function, line 950) `static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,
      ...`
  - `js_eval_module` (function, line 965) `js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,
        ...`
  - `realm_of` (function, line 1032) `static JSContext *realm_of(js_context *c, JSValueConst g)`
  - `throw_named` (function, line 1045) `static JSValue throw_named(JSContext *ctx, const char *name, const char *msg)`
  - `m_realm_new` (function, line 1055) `static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,
                     ...`
  - `m_realm_eval` (function, line 1069) `static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,
                    ...`
  - `m_realm_clone` (function, line 1105) `static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,
                   ...`
  - `js_install_realms` (function, line 1127) `js_status js_install_realms(js_context *ctx)`
  - `undefined` (function, line 519) `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx...`
  - `mod_normalize` (function, line 932) `static char *mod_normalize(JSContext *jc, const char *base, const char *name, void *opaque);`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
  - `JS_PROFILE_SLOTS` (macro, line 35) `#define JS_PROFILE_SLOTS`
  - `JS_PROFILE_KEY_MAX` (macro, line 36) `#define JS_PROFILE_KEY_MAX`
  - `JS_MODULE_URL_MAX` (macro, line 860) `#define JS_MODULE_URL_MAX`
- Depends on: `include/js_sandbox.h`

## src/js_trusted.c
- Doc: ws_payload: } void jt_ws_ops_free(jt_ws_op *ops, size_t n) { if (ops == NULL) return; for...
- Layer: utility
- Language: c
- Symbols:
  - `jt_seed_ctx` (struct, line 472)
  - `jt_enable_open` (function, line 49) `jd_status jt_enable_open(js_context *ctx)`
  - `jt_enable_observers` (function, line 129) `jd_status jt_enable_observers(js_context *ctx)`
  - `jt_geometry_changed` (function, line 142) `jd_status jt_geometry_changed(js_context *ctx)`
  - `jt_take_opens` (function, line 157) `char *jt_take_opens(js_context *ctx)`
  - `jt_enable_ws` (function, line 234) `jd_status jt_enable_ws(js_context *ctx)`
  - `jt_ws_ops_free` (function, line 245) `void jt_ws_ops_free(jt_ws_op *ops, size_t n)`
  - `hex_nibble` (function, line 250) `static int hex_nibble(char c)`
  - `ws_payload` (function, line 257) `static char *ws_payload(int kind, const char *s, size_t n, size_t *out_len)`
  - `jt_take_ws` (function, line 281) `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap)`
  - `jt_ws_event` (function, line 332) `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len)`
  - `jt_enable_frames` (function, line 428) `jd_status jt_enable_frames(js_context *ctx, int frame_id)`
  - `jt_seed_pair` (function, line 474) `static void jt_seed_pair(void *vctx, const char *k, size_t kl, const char *v, size_t vl)`
  - `jt_enable_storage` (function, line 484) `jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len)`
  - `jt_take_storage` (function, line 504) `int jt_take_storage(js_context *ctx, char **out, size_t *len)`
  - `explicitly` (function, line 552) `* explicitly (no window, no document). Delivery is always a timer task. */
static const char JT_W...`
  - `jt_enable_worker` (function, line 633) `jd_status jt_enable_worker(js_context *ctx)`
  - `JT_IO_MAX_STR` (macro, line 62) `#define JT_IO_MAX_STR`
- Depends on: `include/js_trusted.h`, `include/web_storage.h`, `src/js_native_internal.h`

## src/link_nav.c
- Doc: clean_href: Removes tab/newline/CR anywhere and trims leading/trailing spaces, in place * into out.
- Layer: utility
- Language: c
- Symbols:
  - `clean_href` (function, line 19) `static int clean_href(const char *href, char *out, size_t outsz)`
  - `ci_prefix` (function, line 38) `static int ci_prefix(const char *s, const char *prefix)`
  - `classify_block` (function, line 62) `static ln_block_reason classify_block(const char *ref)`
  - `file_dir_len` (function, line 69) `static size_t file_dir_len(const char *base)`
  - `last_seg_is_dotdot` (function, line 79) `static int last_seg_is_dotdot(const char *body, size_t blen)`
  - `append_seg` (function, line 86) `static int append_seg(char *body, size_t bodysz, size_t *blen,
                      const char *...`
  - `pop_seg` (function, line 98) `static void pop_seg(char *body, size_t *blen)`
  - `resolve_file` (function, line 149) `static int resolve_file(const char *base, const char *ref, char *out, size_t outsz)`
  - `ln_resolve` (function, line 172) `ln_status ln_resolve(const char *base, const char *href, ln_result *out)`
  - `ln_block_reason_text` (function, line 241) `const char *ln_block_reason_text(ln_block_reason reason)`
- Depends on: `include/link_nav.h`, `include/url.h`

## src/local_store.c
- Layer: data_access
- Language: c
- Symbols:
  - `cipher_for` (function, line 69) `static const EVP_CIPHER *cipher_for(ls_aead aead)`
  - `argon2id_derive` (function, line 79) `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,
                          ...`
  - `ls_derive_key` (function, line 108) `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,
                        const...`
  - `aead_encrypt` (function, line 117) `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...`
  - `aead_decrypt` (function, line 143) `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...`
  - `seal_core` (function, line 171) `static ls_status seal_core(const uint8_t *key, ls_aead aead, uint8_t kdf_id,
                    ...`
  - `decrypt_blob` (function, line 208) `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,
         ...`
  - `ls_seal` (function, line 239) `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,
                  const uint8_t *p...`
  - `ls_open` (function, line 252) `ls_status ls_open(const uint8_t key[LS_KEY_LEN],
                  const uint8_t *blob, size_t bl...`
  - `ls_seal_passphrase` (function, line 263) `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,
          ...`
  - `ls_open_passphrase` (function, line 284) `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,
                        ...`
  - `ls_free` (function, line 304) `void ls_free(uint8_t *buf, size_t len)`
  - `_GNU_SOURCE` (macro, line 13) `#define _GNU_SOURCE`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 25) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 28) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 31) `#define OSSL_KDF_PARAM_THREADS`
  - `OSSL_KDF_PARAM_ARGON2_LANES` (macro, line 39) `#define OSSL_KDF_PARAM_ARGON2_LANES`
  - `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, line 42) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
  - `OSSL_KDF_PARAM_THREADS` (macro, line 45) `#define OSSL_KDF_PARAM_THREADS`
  - `LS_VERSION` (macro, line 48) `#define LS_VERSION`
  - `LS_KDF_NONE` (macro, line 49) `#define LS_KDF_NONE`
  - `LS_KDF_ARGON2ID` (macro, line 50) `#define LS_KDF_ARGON2ID`
  - `LS_ARGON2_T` (macro, line 53) `#define LS_ARGON2_T`
  - `LS_ARGON2_M_KIB` (macro, line 54) `#define LS_ARGON2_M_KIB`
  - `LS_ARGON2_P` (macro, line 55) `#define LS_ARGON2_P`
  - `OFF_MAGIC` (macro, line 58) `#define OFF_MAGIC`
  - `OFF_VERSION` (macro, line 59) `#define OFF_VERSION`
  - `OFF_AEAD` (macro, line 60) `#define OFF_AEAD`
  - `OFF_KDF` (macro, line 61) `#define OFF_KDF`
  - `OFF_SALT` (macro, line 62) `#define OFF_SALT`
  - `OFF_NONCE` (macro, line 63) `#define OFF_NONCE`
- Depends on: `include/local_store.h`

## src/media_decoder.c
- Doc: decoder_close: AVFrame         *frame;  /* decoded frame (YUV) AVFrame         *rgb;    /*...
- Layer: utility
- Language: c
- Symbols:
  - `decoder_ctx` (struct, line 54)
  - `out_fd` (type_alias, line 53) `typedef struct decoder_ctx { int out_fd;`
  - `open` (function, line 18) `*
 * Sandbox: the decoder needs open() for shared libraries (.so loading) and
 * brk/mmap for FFm...`
  - `decoder_close` (function, line 78) `static void decoder_close(decoder_ctx *dc)`
  - `decoder_init` (function, line 96) `static int decoder_init(decoder_ctx *dc, const uint8_t *data, size_t len)`
  - `frame_pts_us` (function, line 215) `static int64_t frame_pts_us(const AVFrame *f, AVRational tb, int64_t fallback)`
  - `av_rescale_q` (function, line 217) `return av_rescale_q(f->pts, tb, (AVRational)`
  - `send_video_frame` (function, line 222) `static void send_video_frame(decoder_ctx *dc, int64_t pts_us)`
  - `send_audio_frame` (function, line 242) `static void send_audio_frame(decoder_ctx *dc, int64_t pts_us)`
  - `decode_segment` (function, line 276) `static int decode_segment(decoder_ctx *dc, const uint8_t *data, size_t len)`
  - `media_decoder_run` (function, line 379) `void media_decoder_run(int out_fd, int cmd_fd)`
  - `media_decoder_spawn` (function, line 449) `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd)`
  - `dropped` (function, line 369) `* the codec in permanent EOF state: every segment after the first decoded * one was silently dropped ("plays a...`
  - `fd` (function, line 469) `* prevent the Wayland display fd (inherited from the parent) from * surviving the exec. An inherited Wayland fd...`
  - `_POSIX_C_SOURCE` (macro, line 23) `#define _POSIX_C_SOURCE`
- Depends on: `include/media_decoder.h`, `include/util.h`

## src/net_guard.c
- Doc: net_guard -- see include/net_guard.h and spec/net_guard.md.
- Layer: utility
- Language: c
- Symbols:
  - `ng_v4_is_private` (function, line 12) `static int ng_v4_is_private(const unsigned char o[NG_V4_LEN])`
  - `ng_seg` (function, line 29) `static unsigned ng_seg(const unsigned char a[NG_V6_LEN], int i)`
  - `ng_v6_is_private` (function, line 33) `static int ng_v6_is_private(const unsigned char a[NG_V6_LEN])`
  - `ng_addr_is_private` (function, line 63) `int ng_addr_is_private(int family, const unsigned char *addr, size_t len)`
  - `ng_parse` (function, line 71) `static int ng_parse(const char *text, int *family, unsigned char out[NG_V6_LEN])`
  - `ng_text_is_private` (function, line 84) `int ng_text_is_private(const char *ip_text)`
  - `ng_host_is_ip` (function, line 91) `int ng_host_is_ip(const char *host)`
  - `ng_ci_eq` (function, line 97) `static int ng_ci_eq(const char *a, const char *b, size_t n)`
  - `ng_host_is_local` (function, line 107) `int ng_host_is_local(const char *host)`
  - `ng_decide` (function, line 121) `ng_verdict ng_decide(const ng_request *r, int peer_private)`
  - `decides` (function, line 40) `* IPv4 decides (:: and ::1 embed 0.0.0.0 and 0.0.0.1, both in 0/8). */ if (head_zero && (s[5] == 0 || s[5] ==...`
  - `NG_V4_LEN` (macro, line 8) `#define NG_V4_LEN`
  - `NG_V6_LEN` (macro, line 9) `#define NG_V6_LEN`
  - `NG_TEXT_MAX` (macro, line 10) `#define NG_TEXT_MAX`
- Depends on: `include/net_guard.h`

## src/net_realm.c
- Doc: ends_with_realm: True if the lowercased host (length n) ends with ".suffix" AND has at least one...
- Layer: utility
- Language: c
- Symbols:
  - `lower` (function, line 17) `static char lower(char c)`
  - `ends_with_realm` (function, line 23) `static int ends_with_realm(const char *host, size_t n, const char *suffix)`
  - `nr_classify_host` (function, line 34) `nr_realm nr_classify_host(const char *host)`
  - `host_of` (function, line 52) `static int host_of(const char *url, char *out, size_t out_size)`
  - `nr_classify_url` (function, line 68) `nr_realm nr_classify_url(const char *url)`
  - `nr_route_for` (function, line 74) `nr_route nr_route_for(const char *url, nr_config cfg)`
  - `nr_realm_allows_http` (function, line 88) `int nr_realm_allows_http(nr_realm r)`
  - `nr_realm_name` (function, line 94) `const char *nr_realm_name(nr_realm r)`
  - `nr_route_name` (function, line 103) `const char *nr_route_name(nr_route r)`
  - `NR_MAX_HOST` (macro, line 15) `#define NR_MAX_HOST`
- Depends on: `include/net_realm.h`

## src/os_sandbox.c
- Doc: os_prot_allowed: W^X mirror: mmap/mprotect keep their membership but lose any request that asks...
- Layer: utility
- Language: c
- Symbols:
  - `os_policy_allows` (function, line 52) `int os_policy_allows(long syscall_nr)`
  - `os_policy_size` (function, line 59) `size_t os_policy_size(void)`
  - `os_prot_allowed` (function, line 65) `int os_prot_allowed(long syscall_nr, unsigned long prot)`
  - `os_no_dump` (function, line 75) `os_status os_no_dump(void)`
  - `excluded` (function, line 89) `* intentionally excluded (they need /proc remounting and a post-unshare fork). */
int os_namespac...`
  - `os_isolate_namespaces` (function, line 94) `os_status os_isolate_namespaces(void)`
  - `os_policy_allows` (function, line 106) `int os_policy_allows(long syscall_nr)`
  - `os_policy_size` (function, line 107) `size_t os_policy_size(void)`
  - `os_prot_allowed` (function, line 108) `int os_prot_allowed(long syscall_nr, unsigned long prot)`
  - `os_no_dump` (function, line 111) `os_status os_no_dump(void)`
  - `os_harden` (function, line 113) `os_status os_harden(os_violation action)`
  - `os_namespace_flags` (function, line 115) `int os_namespace_flags(void)`
  - `os_isolate_namespaces` (function, line 116) `os_status os_isolate_namespaces(void)`
  - `os_harden` (function, line 145) `os_status os_harden(os_violation action)`
  - `ll_create_ruleset` (function, line 239) `static long ll_create_ruleset(const struct landlock_ruleset_attr *attr,
                         ...`
  - `ll_add_rule` (function, line 244) `static long ll_add_rule(int fd, enum landlock_rule_type type,
                        const void ...`
  - `ll_restrict_self` (function, line 249) `static long ll_restrict_self(int fd, uint32_t flags)`
  - `ll_handled` (function, line 265) `static uint64_t ll_handled(int abi)`
  - `ll_read_access` (function, line 279) `static uint64_t ll_read_access(uint64_t handled)`
  - `os_landlock_abi` (function, line 285) `int os_landlock_abi(void)`
  - `os_landlock_restrict` (function, line 291) `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)`
  - `os_landlock_abi` (function, line 331) `int os_landlock_abi(void)`
  - `os_landlock_restrict` (function, line 332) `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)`
  - `number` (function, line 157) `* number (x32/i386 on x86_64, AArch32 on aarch64). */ prog[n++] = (struct sock_filter)BPF_STMT(BPF_LD | BPF_W |...`
  - `headroom` (function, line 203) `* wide headroom (room for ~125 allowed syscalls). */ prog[at_mmap].jt = (unsigned char)(prot_check - (at_mmap + 1));`
  - `fields` (function, line 303) `* long as the unknown trailing fields (net/scoped) are zero, which they are. */ int rfd =...`
  - `_GNU_SOURCE` (macro, line 13) `#define _GNU_SOURCE`
  - `OS_ALLOWED_N` (macro, line 50) `#define OS_ALLOWED_N`
  - `OS_SECCOMP_ARCH` (macro, line 140) `#  define OS_SECCOMP_ARCH`
  - `OS_SECCOMP_ARCH` (macro, line 142) `#  define OS_SECCOMP_ARCH`
  - `LL_FS_BASE` (macro, line 254) `#define LL_FS_BASE`
- Depends on: `include/os_sandbox.h`


Next: [KB_src_p7.md](KB_src_p7.md)
