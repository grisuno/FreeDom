# Subsystem: src (page 6 of 10)
Previous: [KB_src_p5.md](KB_src_p5.md)

## src/js_sandbox.c
- Doc: js_mem_state: We enforce the heap cap ourselves (not via JS_SetMemoryLimit, whose check runs...
- Layer: utility
- Language: c
- Symbols:
  - `js_mem_state` (struct, line 29)
  - `js_context` (struct, line 38)
  - `limit` (type_alias, line 29) `typedef struct js_mem_state { size_t limit;`
  - `rej_remove` (function, line 75) `static void rej_remove(js_context *c, size_t i)`
  - `js_rejection_cb` (function, line 83) `static void js_rejection_cb(JSContext *jc, JSValueConst promise, JSValueConst reason,
           ...`
  - `rej_report` (function, line 102) `static void rej_report(js_context *c)`
  - `jm_malloc` (function, line 127) `static void *jm_malloc(void *opaque, size_t size)`
  - `jm_calloc` (function, line 135) `static void *jm_calloc(void *opaque, size_t count, size_t size)`
  - `jm_free` (function, line 145) `static void jm_free(void *opaque, void *ptr)`
  - `jm_realloc` (function, line 151) `static void *jm_realloc(void *opaque, void *ptr, size_t size)`
  - `jm_usable_size` (function, line 161) `static size_t jm_usable_size(const void *ptr)`
  - `host_dup` (function, line 171) `static char *host_dup(const char *src, size_t len)`
  - `timespec_reached` (function, line 180) `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)`
  - `timespec_diff_ms` (function, line 185) `static long timespec_diff_ms(const struct timespec *a, const struct timespec *b)`
  - `profile_sample` (function, line 190) `static void profile_sample(js_context *c, unsigned weight_ms)`
  - `js_profile_enable` (function, line 222) `void js_profile_enable(js_context *ctx)`
  - `js_profile_report` (function, line 228) `size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n)`
  - `throw_key` (function, line 251) `static void throw_key(JSContext *ctx, JSValueConst obj, char *key, size_t cap)`
  - `throw_hook_cb` (function, line 308) `static void throw_hook_cb(JSContext *ctx, JSValueConst obj, void *opaque)`
  - `js_throws_enable` (function, line 328) `void js_throws_enable(js_context *ctx)`
  - `js_throws_report` (function, line 334) `size_t js_throws_report(js_context *ctx, char *out, size_t cap, size_t top_n)`
  - `m_fb_report` (function, line 356) `static JSValue m_fb_report(JSContext *jsctx, JSValueConst this_val, int argc, JSValueConst *argv,...`
  - `js_devtools_enable` (function, line 372) `void js_devtools_enable(js_context *ctx)`
  - `js_devtools_expose` (function, line 378) `js_status js_devtools_expose(js_context *ctx)`
  - `js_interrupt_cb` (function, line 394) `static int js_interrupt_cb(JSRuntime *rt, void *opaque)`
  - `is_ascii_digit` (function, line 418) `static int is_ascii_digit(char c)`
  - `js_loc_from_stack` (function, line 420) `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      i...`
  - `js_stack_limit_for` (function, line 539) `size_t js_stack_limit_for(size_t soft_stack)`
  - `process_soft_stack` (function, line 550) `static size_t process_soft_stack(void)`
  - `js_prime_stack_limit` (function, line 560) `void js_prime_stack_limit(void)`
  - `js_limits_default` (function, line 562) `js_limits js_limits_default(void)`
  - `limits_resolve` (function, line 571) `static js_limits limits_resolve(const js_limits *lim)`
  - `js_validate_source` (function, line 580) `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)`
  - `js_context_new` (function, line 591) `js_status js_context_new(const js_limits *lim, js_context **out)`
  - `js_context_free` (function, line 631) `void js_context_free(js_context *ctx)`
  - `arm_deadline` (function, line 643) `static void arm_deadline(js_context *ctx, uint64_t budget_ms)`
  - `js_set_time_budget` (function, line 658) `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)`
  - `js_eval` (function, line 663) `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)`
  - `js_eval_named` (function, line 667) `js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        con...`
  - `js_pump_jobs` (function, line 750) `int js_pump_jobs(js_context *ctx, int max_jobs)`
  - `js_eval_once` (function, line 769) `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)`
  - `js_result_free` (function, line 782) `void js_result_free(js_result *res)`
  - `js_set_current_script` (function, line 810) `void js_set_current_script(js_context *ctx, const char *src, const char *type)`
  - `js_context_raw` (function, line 843) `void *js_context_raw(js_context *ctx)`
  - `mod_set_meta` (function, line 875) `static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url)`
  - `mod_loader` (function, line 884) `static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque)`
  - `js_set_module_host` (function, line 923) `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,
                        js...`
  - `mod_fail` (function, line 938) `static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,
      ...`
  - `js_eval_module` (function, line 953) `js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,
        ...`
  - `realm_of` (function, line 1020) `static JSContext *realm_of(js_context *c, JSValueConst g)`
  - `throw_named` (function, line 1033) `static JSValue throw_named(JSContext *ctx, const char *name, const char *msg)`
  - `m_realm_new` (function, line 1043) `static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,
                     ...`
  - `m_realm_eval` (function, line 1057) `static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,
                    ...`
  - `m_realm_clone` (function, line 1093) `static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,
                   ...`
  - `js_install_realms` (function, line 1115) `js_status js_install_realms(js_context *ctx)`
  - `undefined` (function, line 512) `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx...`
  - `mod_normalize` (function, line 920) `static char *mod_normalize(JSContext *jc, const char *base, const char *name, void *opaque);`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
  - `JS_PROFILE_SLOTS` (macro, line 35) `#define JS_PROFILE_SLOTS`
  - `JS_PROFILE_KEY_MAX` (macro, line 36) `#define JS_PROFILE_KEY_MAX`
  - `JS_MODULE_URL_MAX` (macro, line 848) `#define JS_MODULE_URL_MAX`
- Depends on: `include/js_sandbox.h`

## src/js_trusted.c
- Doc: ws_payload: } void jt_ws_ops_free(jt_ws_op *ops, size_t n) { if (ops == NULL) return; for...
- Layer: utility
- Language: c
- Symbols:
  - `jt_seed_ctx` (struct, line 476)
  - `jt_enable_open` (function, line 48) `jd_status jt_enable_open(js_context *ctx)`
  - `jt_enable_observers` (function, line 129) `jd_status jt_enable_observers(js_context *ctx)`
  - `jt_geometry_changed` (function, line 143) `jd_status jt_geometry_changed(js_context *ctx)`
  - `jt_take_opens` (function, line 159) `char *jt_take_opens(js_context *ctx)`
  - `jt_enable_ws` (function, line 237) `jd_status jt_enable_ws(js_context *ctx)`
  - `jt_ws_ops_free` (function, line 249) `void jt_ws_ops_free(jt_ws_op *ops, size_t n)`
  - `hex_nibble` (function, line 254) `static int hex_nibble(char c)`
  - `ws_payload` (function, line 261) `static char *ws_payload(int kind, const char *s, size_t n, size_t *out_len)`
  - `jt_take_ws` (function, line 285) `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap)`
  - `jt_ws_event` (function, line 336) `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len)`
  - `jt_enable_frames` (function, line 432) `jd_status jt_enable_frames(js_context *ctx, int frame_id)`
  - `jt_seed_pair` (function, line 478) `static void jt_seed_pair(void *vctx, const char *k, size_t kl, const char *v, size_t vl)`
  - `jt_enable_storage` (function, line 488) `jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len)`
  - `jt_take_storage` (function, line 509) `int jt_take_storage(js_context *ctx, char **out, size_t *len)`
  - `explicitly` (function, line 557) `* explicitly (no window, no document). Delivery is always a timer task. */
static const char JT_W...`
  - `jt_enable_worker` (function, line 638) `jd_status jt_enable_worker(js_context *ctx)`
  - `JT_IO_MAX_STR` (macro, line 62) `#define JT_IO_MAX_STR`
- Depends on: `include/js_trusted.h`, `include/web_storage.h`

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
