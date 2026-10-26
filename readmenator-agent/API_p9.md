# API (page 9 of 11)
Previous: [API_p8.md](API_p8.md)

## src/js_sandbox.c
Depends on: `include/js_sandbox.h`
- `rej_remove` (function) `src/js_sandbox.c:75` `static void rej_remove(js_context *c, size_t i)`
- `js_rejection_cb` (function) `src/js_sandbox.c:83` `static void js_rejection_cb(JSContext *jc, JSValueConst promise, JSValueConst reason,
           ...`
- `rej_report` (function) `src/js_sandbox.c:102` `static void rej_report(js_context *c)` -- Hands each still-unhandled rejection to the page, oldest first.
- `jm_malloc` (function) `src/js_sandbox.c:127` `static void *jm_malloc(void *opaque, size_t size)`
- `jm_calloc` (function) `src/js_sandbox.c:135` `static void *jm_calloc(void *opaque, size_t count, size_t size)`
- `jm_free` (function) `src/js_sandbox.c:145` `static void jm_free(void *opaque, void *ptr)`
- `jm_realloc` (function) `src/js_sandbox.c:151` `static void *jm_realloc(void *opaque, void *ptr, size_t size)`
- `jm_usable_size` (function) `src/js_sandbox.c:161` `static size_t jm_usable_size(const void *ptr)`
- `host_dup` (function) `src/js_sandbox.c:171` `static char *host_dup(const char *src, size_t len)`
- `timespec_reached` (function) `src/js_sandbox.c:180` `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)`
- `timespec_diff_ms` (function) `src/js_sandbox.c:185` `static long timespec_diff_ms(const struct timespec *a, const struct timespec *b)`
- `profile_sample` (function) `src/js_sandbox.c:190` `static void profile_sample(js_context *c, unsigned weight_ms)` -- out[len] = '\0'; return out; } static int timespec_reached(const struct timespec *now, const struct timespec...
- `js_profile_enable` (function) `src/js_sandbox.c:222` `void js_profile_enable(js_context *ctx)`
- `js_profile_report` (function) `src/js_sandbox.c:228` `size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n)`
- `throw_key` (function) `src/js_sandbox.c:251` `static void throw_key(JSContext *ctx, JSValueConst obj, char *key, size_t cap)` -- if (!used[i] && (best == ctx->prof_n || ctx->prof[i].hits > ctx->prof[best].hits)) best = i; if (best ==...
- `throw_hook_cb` (function) `src/js_sandbox.c:308` `static void throw_hook_cb(JSContext *ctx, JSValueConst obj, void *opaque)`
- `js_throws_enable` (function) `src/js_sandbox.c:328` `void js_throws_enable(js_context *ctx)`
- `js_throws_report` (function) `src/js_sandbox.c:334` `size_t js_throws_report(js_context *ctx, char *out, size_t cap, size_t top_n)`
- `m_fb_report` (function) `src/js_sandbox.c:356` `static JSValue m_fb_report(JSContext *jsctx, JSValueConst this_val, int argc, JSValueConst *argv,...` -- for (size_t i = 0; i < ctx->thr_n; i++) if (!used[i] && (best == ctx->thr_n || ctx->thr[i].hits >...
- `js_devtools_enable` (function) `src/js_sandbox.c:372` `void js_devtools_enable(js_context *ctx)`
- `js_devtools_expose` (function) `src/js_sandbox.c:378` `js_status js_devtools_expose(js_context *ctx)`
- `js_interrupt_cb` (function) `src/js_sandbox.c:394` `static int js_interrupt_cb(JSRuntime *rt, void *opaque)` -- uint64_t u = (uint64_t)(uintptr_t)ctx; static const char *const names[2] = { "__fbProfile", "__fbThrows" }; JSValue...
- `is_ascii_digit` (function) `src/js_sandbox.c:418` `static int is_ascii_digit(char c)`
- `js_loc_from_stack` (function) `src/js_sandbox.c:420` `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      i...`
- `undefined` (function) `src/js_sandbox.c:512` `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx...`
- `js_stack_limit_for` (function) `src/js_sandbox.c:539` `size_t js_stack_limit_for(size_t soft_stack)`
- `process_soft_stack` (function) `src/js_sandbox.c:550` `static size_t process_soft_stack(void)`
- `js_prime_stack_limit` (function) `src/js_sandbox.c:560` `void js_prime_stack_limit(void)`
- `js_limits_default` (function) `src/js_sandbox.c:562` `js_limits js_limits_default(void)`
- `limits_resolve` (function) `src/js_sandbox.c:571` `static js_limits limits_resolve(const js_limits *lim)`
- `js_validate_source` (function) `src/js_sandbox.c:580` `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)`
- `js_context_new` (function) `src/js_sandbox.c:591` `js_status js_context_new(const js_limits *lim, js_context **out)`
- `js_context_free` (function) `src/js_sandbox.c:631` `void js_context_free(js_context *ctx)`
- `arm_deadline` (function) `src/js_sandbox.c:643` `static void arm_deadline(js_context *ctx, uint64_t budget_ms)`
- `js_set_time_budget` (function) `src/js_sandbox.c:658` `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)`
- `js_eval` (function) `src/js_sandbox.c:663` `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)`
- `js_eval_named` (function) `src/js_sandbox.c:667` `js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        con...`
- `js_pump_jobs` (function) `src/js_sandbox.c:750` `int js_pump_jobs(js_context *ctx, int max_jobs)`
- `js_eval_once` (function) `src/js_sandbox.c:769` `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)`
- `js_result_free` (function) `src/js_sandbox.c:782` `void js_result_free(js_result *res)`
- `js_set_current_script` (function) `src/js_sandbox.c:810` `void js_set_current_script(js_context *ctx, const char *src, const char *type)`
- `js_context_raw` (function) `src/js_sandbox.c:843` `void *js_context_raw(js_context *ctx)`
- `mod_set_meta` (function) `src/js_sandbox.c:875` `static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url)` -- size_t cap = nlen + JS_MODULE_URL_MAX; char *out = (char *)calloc(cap, 1); if (out == NULL) {...
- `mod_loader` (function) `src/js_sandbox.c:884` `static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque)` -- free(out); return r; } /* Sets import.meta.url of a compiled module to its absolute URL. static void...
- `mod_normalize` (function) `src/js_sandbox.c:920` `static char *mod_normalize(JSContext *jc, const char *base, const char *name, void *opaque);`
- `js_set_module_host` (function) `src/js_sandbox.c:923` `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,
                        js...`
- `mod_fail` (function) `src/js_sandbox.c:938` `static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,
      ...` -- Fills res from the pending exception (or the given rejection value, which is * thrown first so the one capture path...
- `js_eval_module` (function) `src/js_sandbox.c:953` `js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,
        ...`
- `realm_of` (function) `src/js_sandbox.c:1020` `static JSContext *realm_of(js_context *c, JSValueConst g)` -- The owning js_context rides in each native's closure data, split into 32-bit * halves (no assumption about JS number...
- `throw_named` (function) `src/js_sandbox.c:1033` `static JSValue throw_named(JSContext *ctx, const char *name, const char *msg)`
- `m_realm_new` (function) `src/js_sandbox.c:1043` `static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,
                     ...`
- `m_realm_eval` (function) `src/js_sandbox.c:1057` `static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,
                    ...` -- __realmEval(global, code, name): a classic script in that realm.
- `m_realm_clone` (function) `src/js_sandbox.c:1093` `static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,
                   ...` -- __realmClone(value, global): structured copy into global's realm through the * serializer WITHOUT bytecode -- a...
- `js_install_realms` (function) `src/js_sandbox.c:1115` `js_status js_install_realms(js_context *ctx)`

## src/js_trusted.c
Depends on: `include/js_trusted.h`, `include/web_storage.h`
- `jt_enable_open` (function) `src/js_trusted.c:48` `jd_status jt_enable_open(js_context *ctx)`
- `jt_enable_observers` (function) `src/js_trusted.c:129` `jd_status jt_enable_observers(js_context *ctx)`
- `jt_geometry_changed` (function) `src/js_trusted.c:143` `jd_status jt_geometry_changed(js_context *ctx)`
- `jt_take_opens` (function) `src/js_trusted.c:159` `char *jt_take_opens(js_context *ctx)`
- `jt_enable_ws` (function) `src/js_trusted.c:237` `jd_status jt_enable_ws(js_context *ctx)`
- `jt_ws_ops_free` (function) `src/js_trusted.c:249` `void jt_ws_ops_free(jt_ws_op *ops, size_t n)`
- `hex_nibble` (function) `src/js_trusted.c:254` `static int hex_nibble(char c)`
- `ws_payload` (function) `src/js_trusted.c:261` `static char *ws_payload(int kind, const char *s, size_t n, size_t *out_len)` -- } void jt_ws_ops_free(jt_ws_op *ops, size_t n) { if (ops == NULL) return; for (size_t i = 0; i < n; ++i) {...
- `jt_take_ws` (function) `src/js_trusted.c:285` `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap)`
- `jt_ws_event` (function) `src/js_trusted.c:327` `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len)`
- `jt_seed_pair` (function) `src/js_trusted.c:382` `static void jt_seed_pair(void *vctx, const char *k, size_t kl, const char *v, size_t vl)`
- `jt_enable_storage` (function) `src/js_trusted.c:392` `jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len)`
- `jt_take_storage` (function) `src/js_trusted.c:413` `int jt_take_storage(js_context *ctx, char **out, size_t *len)`
- `explicitly` (function) `src/js_trusted.c:461` `* explicitly (no window, no document). Delivery is always a timer task. */
static const char JT_W...`
- `jt_enable_worker` (function) `src/js_trusted.c:542` `jd_status jt_enable_worker(js_context *ctx)`

## src/link_nav.c
Depends on: `include/link_nav.h`, `include/url.h`
- `clean_href` (function) `src/link_nav.c:19` `static int clean_href(const char *href, char *out, size_t outsz)` -- Removes tab/newline/CR anywhere and trims leading/trailing spaces, in place * into out.
- `ci_prefix` (function) `src/link_nav.c:38` `static int ci_prefix(const char *s, const char *prefix)` -- if (o + 1 >= outsz) return -1; out[o++] = (char)c; } out[o] = '\0'; size_t start = 0; while (out[start] == ' ')...
- `classify_block` (function) `src/link_nav.c:62` `static ln_block_reason classify_block(const char *ref)` -- Splits the fragment (everything after the first '#') out of ref: copies the fragment id (without '#') into frag...
- `file_dir_len` (function) `src/link_nav.c:69` `static size_t file_dir_len(const char *base)` -- const char *f = hash + 1; size_t fl = strlen(f); if (fl + 1 <= fragsz) memcpy(frag, f, fl + 1); hash = '\0'; } /*...
- `last_seg_is_dotdot` (function) `src/link_nav.c:79` `static int last_seg_is_dotdot(const char *body, size_t blen)` -- return LN_BLOCK_UNSUPPORTED; } /* Length of base up to and including the last '/'; 0 when base has no '/'. static...
- `append_seg` (function) `src/link_nav.c:86` `static int append_seg(char *body, size_t bodysz, size_t *blen,
                      const char *...` -- for (size_t i = 0; base[i] != '\0'; ++i) { if (base[i] == '/') { last = i; found = 1; } } return found ? last + 1...
- `pop_seg` (function) `src/link_nav.c:98` `static void pop_seg(char *body, size_t *blen)` -- /* Appends seg to body (with a '/' separator when non-empty).
- `resolve_file` (function) `src/link_nav.c:149` `static int resolve_file(const char *base, const char *ref, char *out, size_t outsz)` -- Resolves a local file reference (relative or absolute path) against base into * out.
- `ln_resolve` (function) `src/link_nav.c:172` `ln_status ln_resolve(const char *base, const char *href, ln_result *out)`
- `ln_block_reason_text` (function) `src/link_nav.c:241` `const char *ln_block_reason_text(ln_block_reason reason)`

## src/local_store.c
Depends on: `include/local_store.h`
- `cipher_for` (function) `src/local_store.c:904` `static const EVP_CIPHER *cipher_for(ls_aead aead)`
- `argon2id_derive` (function) `src/local_store.c:914` `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,
                          ...`
- `ls_derive_key` (function) `src/local_store.c:943` `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,
                        const...`
- `aead_encrypt` (function) `src/local_store.c:952` `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...`
- `aead_decrypt` (function) `src/local_store.c:978` `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...`
- `seal_core` (function) `src/local_store.c:1006` `static ls_status seal_core(const uint8_t *key, ls_aead aead, uint8_t kdf_id,
                    ...`
- `decrypt_blob` (function) `src/local_store.c:1043` `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,
         ...`
- `ls_seal` (function) `src/local_store.c:1074` `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,
                  const uint8_t *p...`
- `ls_open` (function) `src/local_store.c:1087` `ls_status ls_open(const uint8_t key[LS_KEY_LEN],
                  const uint8_t *blob, size_t bl...`
- `ls_seal_passphrase` (function) `src/local_store.c:1098` `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,
          ...`
- `ls_open_passphrase` (function) `src/local_store.c:1119` `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,
                        ...`
- `ls_free` (function) `src/local_store.c:1139` `void ls_free(uint8_t *buf, size_t len)`

## src/media_decoder.c
Depends on: `include/media_decoder.h`, `include/util.h`
- `open` (function) `src/media_decoder.c:18` `*
 * Sandbox: the decoder needs open() for shared libraries (.so loading) and
 * brk/mmap for FFm...`
- `decoder_close` (function) `src/media_decoder.c:78` `static void decoder_close(decoder_ctx *dc)` -- AVFrame         *frame;  /* decoded frame (YUV) AVFrame         *rgb;    /* converted frame (ARGB) AVFrame...
- `decoder_init` (function) `src/media_decoder.c:96` `static int decoder_init(decoder_ctx *dc, const uint8_t *data, size_t len)` -- Initialises the decoder from the first TS segment bytes.
- `frame_pts_us` (function) `src/media_decoder.c:215` `static int64_t frame_pts_us(const AVFrame *f, AVRational tb, int64_t fallback)` -- Rescales a decoded frame's PTS to microseconds using the time base of the * stream it came from; frames without a...
- `av_rescale_q` (function) `src/media_decoder.c:217` `return av_rescale_q(f->pts, tb, (AVRational)`
- `send_video_frame` (function) `src/media_decoder.c:222` `static void send_video_frame(decoder_ctx *dc, int64_t pts_us)` -- Converts the current dc->frame (YUV) to BGRA and sends it as MD_FRAME with * the given PTS in microseconds.
- `send_audio_frame` (function) `src/media_decoder.c:242` `static void send_audio_frame(decoder_ctx *dc, int64_t pts_us)` -- Converts the current dc->audio_frame to interleaved S16LE PCM and sends it as MD_AUDIO_FRAME with the given PTS in...
- `decode_segment` (function) `src/media_decoder.c:276` `static int decode_segment(decoder_ctx *dc, const uint8_t *data, size_t len)` -- Decodes one segment of TS data and sends frames.
- `dropped` (function) `src/media_decoder.c:369` `* the codec in permanent EOF state: every segment after the first decoded * one was silently dropped ("plays a...`
- `media_decoder_run` (function) `src/media_decoder.c:379` `void media_decoder_run(int out_fd, int cmd_fd)`
- `media_decoder_spawn` (function) `src/media_decoder.c:449` `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd)`
- `fd` (function) `src/media_decoder.c:469` `* prevent the Wayland display fd (inherited from the parent) from * surviving the exec. An inherited Wayland fd...`

## src/net_realm.c
Depends on: `include/net_realm.h`
- `lower` (function) `src/net_realm.c:17` `static char lower(char c)`
- `ends_with_realm` (function) `src/net_realm.c:23` `static int ends_with_realm(const char *host, size_t n, const char *suffix)` -- True if the lowercased host (length n) ends with ".suffix" AND has at least one * non-empty label before the dot....
- `nr_classify_host` (function) `src/net_realm.c:34` `nr_realm nr_classify_host(const char *host)`
- `host_of` (function) `src/net_realm.c:52` `static int host_of(const char *url, char *out, size_t out_size)` -- Extracts the host of scheme://host[:port][/...] into out (lowercased not required * here; nr_classify_host lowercases).
- `nr_classify_url` (function) `src/net_realm.c:68` `nr_realm nr_classify_url(const char *url)`
- `nr_route_for` (function) `src/net_realm.c:74` `nr_route nr_route_for(const char *url, nr_config cfg)`
- `nr_realm_allows_http` (function) `src/net_realm.c:88` `int nr_realm_allows_http(nr_realm r)`
- `nr_realm_name` (function) `src/net_realm.c:94` `const char *nr_realm_name(nr_realm r)`
- `nr_route_name` (function) `src/net_realm.c:103` `const char *nr_route_name(nr_route r)`

## src/os_sandbox.c
Depends on: `include/os_sandbox.h`
- `os_policy_allows` (function) `src/os_sandbox.c:52` `int os_policy_allows(long syscall_nr)`
- `os_policy_size` (function) `src/os_sandbox.c:59` `size_t os_policy_size(void)`
- `os_prot_allowed` (function) `src/os_sandbox.c:65` `int os_prot_allowed(long syscall_nr, unsigned long prot)` -- W^X mirror: mmap/mprotect keep their membership but lose any request that asks * for executable memory.
- `os_no_dump` (function) `src/os_sandbox.c:75` `os_status os_no_dump(void)` -- Anti-dump defense in depth: undumpable + no core file, so neither a crash nor a foreign ptrace can exfiltrate worker...
- `excluded` (function) `src/os_sandbox.c:89` `* intentionally excluded (they need /proc remounting and a post-unshare fork). */
int os_namespac...`
- `os_isolate_namespaces` (function) `src/os_sandbox.c:94` `os_status os_isolate_namespaces(void)`
- `os_policy_allows` (function) `src/os_sandbox.c:106` `int os_policy_allows(long syscall_nr)`
- `os_policy_size` (function) `src/os_sandbox.c:107` `size_t os_policy_size(void)`
- `os_prot_allowed` (function) `src/os_sandbox.c:108` `int os_prot_allowed(long syscall_nr, unsigned long prot)`
- `os_no_dump` (function) `src/os_sandbox.c:111` `os_status os_no_dump(void)`
- `os_harden` (function) `src/os_sandbox.c:113` `os_status os_harden(os_violation action)`
- `os_namespace_flags` (function) `src/os_sandbox.c:115` `int os_namespace_flags(void)`
- `os_isolate_namespaces` (function) `src/os_sandbox.c:116` `os_status os_isolate_namespaces(void)`
- `os_harden` (function) `src/os_sandbox.c:145` `os_status os_harden(os_violation action)`
- `number` (function) `src/os_sandbox.c:157` `* number (x32/i386 on x86_64, AArch32 on aarch64). */ prog[n++] = (struct sock_filter)BPF_STMT(BPF_LD | BPF_W |...`
- `headroom` (function) `src/os_sandbox.c:203` `* wide headroom (room for ~125 allowed syscalls). */ prog[at_mmap].jt = (unsigned char)(prot_check - (at_mmap + 1));`
- `ll_create_ruleset` (function) `src/os_sandbox.c:239` `static long ll_create_ruleset(const struct landlock_ruleset_attr *attr,
                         ...`
- `ll_add_rule` (function) `src/os_sandbox.c:244` `static long ll_add_rule(int fd, enum landlock_rule_type type,
                        const void ...`
- `ll_restrict_self` (function) `src/os_sandbox.c:249` `static long ll_restrict_self(int fd, uint32_t flags)`
- `ll_handled` (function) `src/os_sandbox.c:265` `static uint64_t ll_handled(int abi)` -- The set of FS rights the ruleset handles, masked to what this ABI supports so * landlock_create_ruleset does not...
- `ll_read_access` (function) `src/os_sandbox.c:279` `static uint64_t ll_read_access(uint64_t handled)`
- `os_landlock_abi` (function) `src/os_sandbox.c:285` `int os_landlock_abi(void)`
- `os_landlock_restrict` (function) `src/os_sandbox.c:291` `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)`
- `fields` (function) `src/os_sandbox.c:303` `* long as the unknown trailing fields (net/scoped) are zero, which they are. */ int rfd =...`
- `os_landlock_abi` (function) `src/os_sandbox.c:331` `int os_landlock_abi(void)`
- `os_landlock_restrict` (function) `src/os_sandbox.c:332` `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)`

## src/page_view.c
Depends on: `include/box_style.h`, `include/box_tree.h`, `include/css.h`, `include/css_chain.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_vars.h`, `include/dom.h`, `include/flex_layout.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/page_view.h`, `include/svg_render.h`, `include/util.h`
- `cp1252_to_ucs` (function) `src/page_view.c:90` `static unsigned int cp1252_to_ucs(unsigned char c)` -- Unicode scalar for a Windows-1252 byte (only meaningful for c >= 0x80).
- `utf8_encode` (function) `src/page_view.c:104` `static size_t utf8_encode(unsigned int cp, char *out)` -- Encodes a BMP scalar (<= 0xFFFF, which covers all Windows-1252 targets) as * UTF-8 into out (up to 3 bytes); returns...
- `utf8_sanitized_dup` (function) `src/page_view.c:117` `static char *utf8_sanitized_dup(const char *s)`
- `positions` (function) `src/page_view.c:140` `* positions (cp == 0) keep the legacy '?' fallback. */ unsigned int cp = cp1252_to_ucs(c);`
- `dup_n` (function) `src/page_view.c:151` `static char *dup_n(const char *s, size_t n)`
- `run_init_common` (function) `src/page_view.c:165` `static void run_init_common(pv_run *r)` -- Common field initialization shared by all append helpers.
- `pv_ptrmap_slot` (function) `src/page_view.c:301` `static size_t pv_ptrmap_slot(const pv_ptrmap *m, const void *k)`
- `pv_ptrmap_get` (function) `src/page_view.c:311` `static int pv_ptrmap_get(const pv_ptrmap *m, const void *k, int *out)`
- `pv_ptrmap_put` (function) `src/page_view.c:319` `static void pv_ptrmap_put(pv_ptrmap *m, const void *k, int v)`
- `pv_ptrmap_free` (function) `src/page_view.c:341` `static void pv_ptrmap_free(pv_ptrmap *m)`
- `pv_node_map_init` (function) `src/page_view.c:356` `static int pv_node_map_init(pv_node_map *m)`
- `pv_node_map_free` (function) `src/page_view.c:365` `static void pv_node_map_free(pv_node_map *m)`
- `pv_node_map_build` (function) `src/page_view.c:407` `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root)` -- Builds a document-order map of all element nodes under root.
- `pv_new` (function) `src/page_view.c:416` `pv_view *pv_new(void)`
- `pv_append` (function) `src/page_view.c:420` `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    c...`
- `pv_append_image` (function) `src/page_view.c:455` `pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          con...`
- `pv_append_input` (function) `src/page_view.c:485` `pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_...`
- `pv_append_video` (function) `src/page_view.c:525` `pv_status pv_append_video(pv_view *v, int heading, int block_break,
                          con...`
- `pv_append_svg` (function) `src/page_view.c:561` `pv_status pv_append_svg(pv_view *v, int heading, int block_break,
                        const c...`
- `pv_set_emphasis` (function) `src/page_view.c:590` `void pv_set_emphasis(pv_view *v, int bold, int italic)`
- `pv_set_indent` (function) `src/page_view.c:597` `void pv_set_indent(pv_view *v, int indent)`
- `pv_set_color` (function) `src/page_view.c:602` `void pv_set_color(pv_view *v, int fg_rgb)`
- `pv_set_bgcolor` (function) `src/page_view.c:607` `void pv_set_bgcolor(pv_view *v, int bg_rgb)`
- `pv_set_text_style` (function) `src/page_view.c:612` `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,
                ...`
- `pv_set_grad_text` (function) `src/page_view.c:623` `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)`
- `pv_set_text_ext` (function) `src/page_view.c:631` `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)`
- `ignored` (function) `src/page_view.c:672` `* source is ignored (fail-visible: never invisible text from half a
     * pattern). A real text-...`
- `pv_set_container` (function) `src/page_view.c:687` `void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_g...`
- `pv_set_row_span` (function) `src/page_view.c:702` `void pv_set_row_span(pv_view *v, int row_span)`
- `pv_set_grid_area` (function) `src/page_view.c:706` `void pv_set_grid_area(pv_view *v, int row_start, int col_start)`
- `pv_set_grid` (function) `src/page_view.c:713` `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)`
- `pv_set_grid_rows` (function) `src/page_view.c:723` `void pv_set_grid_rows(pv_view *v, int grid_rows)`
- `pv_set_cont_box` (function) `src/page_view.c:727` `void pv_set_cont_box(pv_view *v, int cont_box_id)`
- `pv_set_flex` (function) `src/page_view.c:731` `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                 int...`
- `pv_set_flex_mauto` (function) `src/page_view.c:743` `void pv_set_flex_mauto(pv_view *v, int mauto)`
- `pv_set_cont_item` (function) `src/page_view.c:749` `void pv_set_cont_item(pv_view *v, int cont_item)`
- `pv_set_float_w` (function) `src/page_view.c:754` `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box,
                    ...`
- `pv_set_float` (function) `src/page_view.c:765` `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear,
                int ...`
- `pv_set_box` (function) `src/page_view.c:787` `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                int box_center, int ...`
- `pv_set_box_pct` (function) `src/page_view.c:799` `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,
                    ...`
- `pv_set_box_maxw` (function) `src/page_view.c:810` `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct)`
- `pv_set_ua_tag` (function) `src/page_view.c:817` `void pv_set_ua_tag(pv_view *v, int ua_tag)`
- `pv_set_node_id` (function) `src/page_view.c:823` `void pv_set_node_id(pv_view *v, dom_node_id node_id)`
- `pv_set_block_id` (function) `src/page_view.c:828` `void pv_set_block_id(pv_view *v, int block_id)`
- `pv_set_own_box` (function) `src/page_view.c:833` `void pv_set_own_box(pv_view *v, int box_id)`
- `pv_set_oof` (function) `src/page_view.c:838` `void pv_set_oof(pv_view *v, int oof)`
- `pv_set_justify_self` (function) `src/page_view.c:843` `void pv_set_justify_self(pv_view *v, int justify_self)`
- `pv_set_block_node` (function) `src/page_view.c:848` `void pv_set_block_node(pv_view *v, dom_node_id id)`
- `pv_set_br_line` (function) `src/page_view.c:853` `void pv_set_br_line(pv_view *v, int br_line)`
- `pv_set_input_checked` (function) `src/page_view.c:858` `void pv_set_input_checked(pv_view *v, int checked)`
- `pv_set_input_placeholder` (function) `src/page_view.c:863` `void pv_set_input_placeholder(pv_view *v, int ph_color)`
- `pv_svg_append_root_attrs` (function) `src/page_view.c:868` `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs,
               ...`
- `pv_placeholder_color` (function) `src/page_view.c:897` `int pv_placeholder_color(const css_style *ph)`
- `pv_set_input_select_opts` (function) `src/page_view.c:905` `void pv_set_input_select_opts(pv_view *v, const char *select_opts)`
- `pv_add_cont_def` (function) `src/page_view.c:913` `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)`
- `pv_cont_count` (function) `src/page_view.c:926` `size_t pv_cont_count(const pv_view *v)`
- `pv_cont_at` (function) `src/page_view.c:930` `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)`
- `pv_add_box_def` (function) `src/page_view.c:935` `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)`
- `pv_free` (function) `src/page_view.c:948` `void pv_free(pv_view *v)`
- `pv_count` (function) `src/page_view.c:966` `size_t pv_count(const pv_view *v)`
- `pv_at` (function) `src/page_view.c:970` `const pv_run *pv_at(const pv_view *v, size_t i)`
- `pv_box_count` (function) `src/page_view.c:975` `size_t pv_box_count(const pv_view *v)`
- `pv_box_at` (function) `src/page_view.c:979` `const pv_box_def *pv_box_at(const pv_view *v, size_t i)`
- `node_next` (function) `src/page_view.c:987` `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` -- } size_t pv_box_count(const pv_view *v) { return (v != NULL) ? v->nbox : 0; } const pv_box_def *pv_box_at(const...
- `is_block_tag` (function) `src/page_view.c:997` `static int is_block_tag(lxb_tag_id_t t)`
- `is_block_like` (function) `src/page_view.c:1022` `static int is_block_like(lxb_tag_id_t t, css_display display)` -- An element should be treated as block-like (eligible for box registration, hbox, float) when its CSS display...
- `resolves` (function) `src/page_view.c:1051` `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close
 * button/tooltip w...`
- `is_block_like_style` (function) `src/page_view.c:1061` `static int is_block_like_style(lxb_tag_id_t t, const css_style *cs)` -- is_block_like with the out-of-flow coercion applied.
- `generates_box` (function) `src/page_view.c:1073` `static int generates_box(lxb_tag_id_t t, css_display display)`
- `generates_box_style` (function) `src/page_view.c:1085` `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)` -- Form controls (input/select/textarea/button) are inline-block by default but can carry author CSS like...
- `causes_block_break` (function) `src/page_view.c:1092` `static int causes_block_break(lxb_tag_id_t t, css_display display)` -- Returns 1 when the element should cause a block break (start a new line). display:inline-block and display:inline do...
- `paints` (function) `src/page_view.c:1105` `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas
 * vacías"). Comment a...`
- `ua_tag_of` (function) `src/page_view.c:1130` `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)` -- User-agent box identity of a block-level element, from its lexbor tag id.
- `heading_level` (function) `src/page_view.c:1152` `static int heading_level(lxb_tag_id_t t)`
- `is_skipped_tag` (function) `src/page_view.c:1164` `static int is_skipped_tag(lxb_tag_id_t t)`
- `node_tag` (function) `src/page_view.c:1185` `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)`
- `content` (function) `src/page_view.c:1190` `* a <noscript> ancestor also suppresses content (the script would run, so the * fallback is hidden);`
- `in_skipped_subtree` (function) `src/page_view.c:1193` `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
              ...` -- Nonzero if any ancestor up to base is a non-rendered container.
- `font_color_attr` (function) `src/page_view.c:1230` `static int font_color_attr(lxb_dom_element_t *el)`
- `bgcolor_attr` (function) `src/page_view.c:1236` `static int bgcolor_attr(lxb_dom_element_t *el)` -- Legacy bgcolor attribute (body/table/tr/td), the background twin of <font * color>: pre-CSS sites (Hacker News'...
- `address` (function) `src/page_view.c:1258` `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <=...`
- `child` (function) `src/page_view.c:1266` `* child (NULL = anonymous item: text directly inside the container);`
- `id` (function) `src/page_view.c:1290` `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);`
- `item_ordinal` (function) `src/page_view.c:1358` `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)` -- Ordinal for a run of container `cid` whose direct-child item is `item` (NULL = * anonymous: every such run is its...
- `it` (function) `src/page_view.c:1387` `* it (they inherit in CSS). list_style drives the <li> marker (structural);`
- `pv_content_hidden` (function) `src/page_view.c:1391` `int pv_content_hidden(int box_hidden, int run_visibility)` -- The author text-presentation extensions struct (pv_text_ext) is public now (include/page_view.h): each field...
- `pv_text_ext_reset` (function) `src/page_view.c:1397` `void pv_text_ext_reset(pv_text_ext *e)`
- `pv_text_ext_merge` (function) `src/page_view.c:1423` `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)` -- Merges one ancestor's resolved css_style into ext, nearest ancestor first (a field * already set is not overwritten...
- `css_has_hbox` (function) `src/page_view.c:1485` `static int css_has_hbox(const css_style *cs)` -- True if the resolved style declares any HORIZONTAL box property, in either half of the <length-percentage>: `width...
- `pv_mauto_of` (function) `src/page_view.c:1499` `static int pv_mauto_of(const css_style *cs)` -- Pre-resolves the horizontal box (px) into a run's wire fields: l/r insets = padding + non-auto margin of each side...
- `css_hbox_resolve` (function) `src/page_view.c:1506` `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)`
- `css_has_position` (function) `src/page_view.c:1559` `static int css_has_position(const css_style *cs)` -- A real (non-static) position makes a block box-carrying too, so its position/insets/ * z-index ride the box-def tree...
- `border_side_cleared` (function) `src/page_view.c:1566` `static int border_side_cleared(int width, int style)` -- A side whose border the author zeroed (`border:0`, `border-width:0`) or switched off * (`border:none`); an unset...
- `pv_control_frame_cleared` (function) `src/page_view.c:1572` `static int pv_control_frame_cleared(const css_style *cs)` -- The author cleared the control's frame on all four sides (pure): Firefox then paints * no native field chrome at all.
- `css_has_boxdeco` (function) `src/page_view.c:1580` `static int css_has_boxdeco(const css_style *cs)`
- `cont_def_reset` (function) `src/page_view.c:1724` `static void cont_def_reset(pv_cont_def *d)` -- Per-container parameters + parent linkage (2026-07-31).
- `container_id` (function) `src/page_view.c:1743` `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)` -- d->box_id = -1; d->item_grow = -1; d->item_shrink = -1; d->item_basis = CSS_LEN_UNSET; d->item_order =...
- `annotate_flow_run` (function) `src/page_view.c:1831` `static void annotate_flow_run(pv_view *v, pv_container_reg *reg, pv_item_track *items,
          ...` -- Stamps the last run with its element's layout annotation: container membership and item slot, flex/grid item...
- `after_pending_emit` (function) `src/page_view.c:1879` `static pv_status after_pending_emit(pv_view *v, pv_container_reg *reg, pv_item_track *items,
    ...`
- `trying` (function) `src/page_view.c:1917` `* a real page passes without trying (slashdot's front page saturates it), and past
 * it box_reg_...`
- `box_reg_free` (function) `src/page_view.c:1946` `static void box_reg_free(pv_box_reg *r)`
- `boxdef_from_style` (function) `src/page_view.c:1955` `static void boxdef_from_style(pv_box_def *d, const css_style *cs)` -- Fills *d (decoration + hbox + bg; parent_id defaults to -1) from a resolved style.
- `here` (function) `src/page_view.c:2057` `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3...`
- `glyphs` (function) `src/page_view.c:2105` `* glyphs (the runs carry it as their fill source);`
- `box_reg_id` (function) `src/page_view.c:2203` `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,
           ...` -- Registers (or finds) the box for `node`. font_px is the element's COMPUTED font-size, needed because the user-agent...
- `pseudo_box_reg` (function) `src/page_view.c:2232` `static int pseudo_box_reg(pv_box_reg *r, const lxb_dom_node_t *el, int which,
                   ...` -- Registers (or finds) the GENERATED box of el's ::before / ::after (which = CSS_PSEUDO_BEFORE / CSS_PSEUDO_AFTER)...
- `pseudo_generates_box` (function) `src/page_view.c:2253` `static int pseudo_generates_box(const css_style *ps)` -- True iff a generated box paints or sizes something of its own: the same gate as any element's box, plus a declared...
- `pseudo_is_oof` (function) `src/page_view.c:2266` `static int pseudo_is_oof(const css_style *ps)`
- `pseudo_is_block` (function) `src/page_view.c:2270` `static int pseudo_is_block(const css_style *ps)`
- `pseudo_key` (function) `src/page_view.c:2276` `static const void *pseudo_key(const lxb_dom_node_t *el, int which)` -- return css_has_boxdeco(ps) || ps->width > 0 || ps->pct[CSS_PCT_WIDTH] > 0 || ps->background >= 0 ||...
- `pv_ptr_hash` (function) `src/page_view.c:2339` `static size_t pv_ptr_hash(const void *p)`
- `pv_cache_reindex` (function) `src/page_view.c:2347` `static void pv_cache_reindex(pv_style_cache *c)`
- `pv_style_cache_init` (function) `src/page_view.c:2357` `static int pv_style_cache_init(pv_style_cache *c)`
- `pv_style_cache_free` (function) `src/page_view.c:2377` `static void pv_style_cache_free(pv_style_cache *c)`
- `pv_cache_find` (function) `src/page_view.c:2393` `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)` -- cch_element_style(el, sheet), memoized in *cache.
- `pv_cached_font_px` (function) `src/page_view.c:2408` `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)` -- The COMPUTED font-size memoized for `node`, or 0 when it is not in the cache (no cache, or the element's style was...
- `pv_cache_put` (function) `src/page_view.c:2413` `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,
                     ...`
- `pv_var_push` (function) `src/page_view.c:2463` `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,
                      ...` -- Takes ownership of *own (left zeroed) as a new chain node over `parent`. * Returns the node's chain, or `parent`...
- `pv_parent_element` (function) `src/page_view.c:2484` `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)` -- cache->vn = g; cache->vncap = nc; } pv_var_node *n = (pv_var_node *)calloc(1, sizeof *n); if (n == NULL) {...
- `cached_element_style_ref` (function) `src/page_view.c:2561` `static const css_style *cached_element_style_ref(lxb_dom_element_t *el, const css_sheet *sheet,
 ...` -- The same, returning a pointer to the memoized entry instead of a copy: css_style is ~7 KB, and the ancestor/subtree...
- `cached_element_style` (function) `src/page_view.c:2644` `static css_style cached_element_style(lxb_dom_element_t *el, const css_sheet *sheet,
            ...`
- `col_free_share` (function) `src/page_view.c:2705` `static int col_free_share(const lxb_dom_node_t *el, const css_style *cs, const css_sheet *sheet, pv_style_cache...` -- box_reg_id plus the line alignment an inline-level box needs (see * pv_box_def.line_align).
- `inherited_text_color` (function) `src/page_view.c:2711` `static int inherited_text_color(const lxb_dom_node_t *node, const css_sheet *sheet,
             ...` -- The computed `color` of an element: its own declaration, else its nearest ancestor's (`color` inherits). -1 when no...
- `box_reg_id_ex` (function) `src/page_view.c:2722` `static int box_reg_id_ex(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,
        ...`
- `none` (function) `src/page_view.c:2727` `* inherited when it declares none (every hamburger bar and divider drawn as * a coloured empty box). A box cannot...`
- `cached_pseudo_style` (function) `src/page_view.c:2760` `static css_style cached_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet,
             ...` -- The ::before/::after generated box's style of el (spec/page_view.md "Cajas generadas"): resolved against el's...
- `subtree_is_oof` (function) `src/page_view.c:2778` `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,
                     ...` -- True iff the element itself is out of flow (position:absolute/fixed) or descends from one.
- `size` (function) `src/page_view.c:2798` `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */
static void app...`
- `css_replaced_h_fixed` (function) `src/page_view.c:2807` `static int css_replaced_h_fixed(lxb_dom_element_t *el, const css_sheet *sheet,
                  ...` -- flat model, and auto keeps the intrinsic/attribute size (so the common `img{max-width:100%;height:auto}` rule does...
- `builder` (function) `src/page_view.c:2825` `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box
 * (the ...`
- `css_to_fx_justify` (function) `src/page_view.c:2854` `static int css_to_fx_justify(css_justify j)` -- Maps a css_justify (resolved by the css cascade) to a flex_layout fx_justify. * Unset / start / unknown all fall to...
- `is_bold_tag` (function) `src/page_view.c:2873` `static int is_bold_tag(lxb_tag_id_t t)` -- Tags the user-agent sheet renders bold.
- `is_italic_tag` (function) `src/page_view.c:2878` `static int is_italic_tag(lxb_tag_id_t t)`
- `is_inline_level_style` (function) `src/page_view.c:2915` `static int is_inline_level_style(lxb_tag_id_t t, const css_style *cs)` -- Inline-level box (CSS 2.1 9.2.2): display inline or inline-block, or a tag the UA * sheet makes inline, and not...
- `in_mixed_line` (function) `src/page_view.c:2923` `static int in_mixed_line(const lxb_dom_node_t *p, const css_sheet *sheet,
                       ...` -- True when `p` shares a line with inline content: a sibling that is non-blank text * or an inline-level element.
- `children_all_inline_block` (function) `src/page_view.c:2939` `static int children_all_inline_block(const lxb_dom_node_t *p, const css_sheet *sheet,
           ...`
- `col_has_free_space` (function) `src/page_view.c:2964` `static int col_has_free_space(const css_style *cs)` -- True iff a column can have FREE space on its main axis: a px height or a px min-height floor.
- `flex_column_flows_as_block` (function) `src/page_view.c:2975` `static int flex_column_flows_as_block(const lxb_dom_node_t *el, const css_style *cs,
            ...` -- A flex COLUMN with the initial geometry (no reverse, no wrap, justify-content start, align-items stretch) stacks...
- `fold_column_gap` (function) `src/page_view.c:3043` `static void fold_column_gap(const lxb_dom_node_t *el, css_style *cs,
                            ...` -- The gap of a column that flows as block (above) is the space BETWEEN its items (Flexbox 8.1), so every item but the...
- `column_gap_candidate` (function) `src/page_view.c:3068` `static int column_gap_candidate(const lxb_dom_node_t *el, const css_sheet *sheet,
               ...` -- Cheap prefilter: could fold_column_gap change this element's style?
- `is_layout_container` (function) `src/page_view.c:3078` `static int is_layout_container(const lxb_dom_node_t *el, const css_style *cs,
                   ...` -- Cheap prefilter: could fold_column_gap change this element's style?
- `css_has_hmargin` (function) `src/page_view.c:3104` `static int css_has_hmargin(const css_style *cs)` -- A flex/grid ITEM: its parent element is a layout container.
- `item_sizes_itself` (function) `src/page_view.c:3133` `static int item_sizes_itself(const lxb_dom_node_t *el, const css_style *cs,
                     ...`
- `li_is_list_item` (function) `src/page_view.c:3149` `static int li_is_list_item(const lxb_dom_node_t *li, const css_sheet *sheet,
                    ...` -- A marker is generated by a `display:list-item` box (CSS Lists 3 3.1), which is what the UA sheet makes an <li>; an...
- `pv_element_has_before` (function) `src/page_view.c:3226` `static int pv_element_has_before(lxb_dom_node_t *n, const css_sheet *sheet,
                     ...` -- True when the element's resolved style carries ::before generated content (spec/css.md ::before/::after: only...
- `subtree_has_own_text` (function) `src/page_view.c:3258` `static int subtree_has_own_text(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
            ...` -- True when the subtree holds no non-blank text of its own outside skipped / hidden / closed-details subtrees...
- `is_plain_wrapper` (function) `src/page_view.c:3280` `static int is_plain_wrapper(const lxb_dom_node_t *c, const css_style *cs)` -- A plain wrapper: a generic container with no decoration and no size of its own, so * it adds nothing to its parent's...
- `element_is_content_leaf_d` (function) `src/page_view.c:3292` `static int element_is_content_leaf_d(const lxb_dom_node_t *n, const css_sheet *sheet,
           ...`
- `media_has_source` (function) `src/page_view.c:3318` `static int media_has_source(const lxb_dom_node_t *n)` -- Whether a <video>/<audio> names anything to play: its own `src`, or a <source> child with one.
- `element_is_content_leaf` (function) `src/page_view.c:3332` `static int element_is_content_leaf(const lxb_dom_node_t *n, const css_sheet *sheet,
             ...`
- `resolve_context` (function) `src/page_view.c:3346` `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                ...`
- `outermost` (function) `src/page_view.c:3610` `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);`
- `opens` (function) `src/page_view.c:3667` `* painter applies it when the box opens (band/shared context) — seeding
             * it onto ru...`
- `css_inline_boxdeco` (function) `src/page_view.c:3707` `css_inline_boxdeco(cs) &&
                           !is_layout_item(p, sheet, style_cache))`
- `margins` (function) `src/page_view.c:3747` `* margins (boxdef_from_style) and the painter applies them when
                         * it ope...`
- `container` (function) `src/page_view.c:3870` `* membership in this container (and none in any container further out,
                 * since i...`
- `walk` (function) `src/page_view.c:3968` `* far on this walk (they are all inside this element). */

                        /* The innermo...`
- `float` (function) `src/page_view.c:4093` `* genuinely nested float (oid != id) takes the deferred-column path. */
    if (cont->float_oid =...`
- `sz_count` (function) `src/page_view.c:4139` `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)` -- Serialises an element subtree (the element itself included) into a fresh NUL-terminated buffer.
- `sz_write` (function) `src/page_view.c:4153` `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)`
- `serialize_subtree` (function) `src/page_view.c:4161` `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)`
- `collapse_ws` (function) `src/page_view.c:4180` `static char *collapse_ws(const char *s, size_t n)` -- if (total == 0 || total > SV_MAX_INPUT) return NULL; char *buf = (char *)calloc(1, total + 1u); if (buf == NULL)...
- `parse_dim` (function) `src/page_view.c:4204` `static int parse_dim(const lxb_char_t *s, size_t len)` -- Parses the leading non-negative integer of an HTML length attribute value (e.g. "640", "640px", "50%").
- `present` (function) `src/page_view.c:4221` `* when no width descriptors are present (density-only or bare URLs). */
static void srcset_best_u...`
- `srcset_slot_width` (function) `src/page_view.c:4316` `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,
                              ...` -- Parses a sizes attribute ("(max-width: 600px) 100vw, 50vw") and returns the effective slot width in px for the given...
- `dimensions` (function) `src/page_view.c:4362` `* viewport dimensions (data: inline detection, <picture> <source> scanning). */
static void srcse...`
- `find_body` (function) `src/page_view.c:4394` `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)`
- `find_root_els` (function) `src/page_view.c:4407` `static pv_root_els find_root_els(lxb_dom_node_t *root)`
- `attributes` (function) `src/page_view.c:4421` `* carries those attributes (spec/css.md, "Root matcher"). */
static int root_els_match(void *ctx,...`
- `string` (function) `src/page_view.c:4432` `* Returns a heap string (caller frees) or NULL when neither carries a class —
 * NULL simply mean...`
- `forms_free` (function) `src/page_view.c:4480` `static void forms_free(form_table *ft)`
- `ascii_ieq` (function) `src/page_view.c:4487` `static int ascii_ieq(const char *s, const char *lit)` -- } form_rec; typedef struct form_table { form_rec *recs; size_t    count, cap; } form_table; static void...
- `attr_dup` (function) `src/page_view.c:4499` `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)` -- Owned NUL-terminated copy of an attribute value, or NULL when the attribute is * absent.
- `forms_add` (function) `src/page_view.c:4508` `static int forms_add(form_table *ft, const lxb_dom_node_t *node)` -- Owned NUL-terminated copy of an attribute value, or NULL when the attribute is * absent.
- `form_for` (function) `src/page_view.c:4528` `static int form_for(const form_table *ft, const lxb_dom_node_t *n,
                    const lxb_...` -- } lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)node); char *method = attr_dup(el, "method"...
- `under_unrendered` (function) `src/page_view.c:4544` `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)` -- Nonzero if a descendant text node sits under a non-rendered element (a <style> or <script> nested in the collected...
- `collect_text` (function) `src/page_view.c:4557` `static char *collect_text(const lxb_dom_node_t *el)` -- Concatenates the descendant text of el into an owned NUL-terminated string (the value of a <textarea> / the label of...
- `classify_input` (function) `src/page_view.c:4581` `static pv_input_type classify_input(const char *type)`
- `li_ordinal` (function) `src/page_view.c:4753` `static int li_ordinal(const lxb_dom_node_t *li)` -- 1-based position of an <li> among its <li> siblings (an <ol> counter, basic: the `start`/`value` attributes are out...
- `roman_marker` (function) `src/page_view.c:4779` `static void roman_marker(int n, int upper, char *out, size_t cap)` -- int k = 0; if (n < 1) n = 1; while (n > 0 && k < (int)sizeof buf) { int r = (n - 1) % 26; buf[k++] = (char)((upper ?...
- `list_marker` (function) `src/page_view.c:4804` `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,
                  ...` -- Builds the list marker for the first run of an <li>.
- `node_table_role` (function) `src/page_view.c:4845` `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)` -- The table role of an element: its computed `display` when that names one, else the role the HTML user-agent sheet...
- `nearest_table` (function) `src/page_view.c:4863` `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
 ...` -- const lxb_char_t *nm = lxb_dom_element_local_name(el, &nl); char tag[BX_TAG_NAME_MAX]; const char *tagp = NULL; if...
- `parent_is_table_internal` (function) `src/page_view.c:4902` `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)` -- Nonzero when n's DIRECT parent is table structure that is not a cell -- a table, a row group, a row or a column group.
- `nearest_cell` (function) `src/page_view.c:4929` `static const lxb_dom_node_t *nearest_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
  ...` -- if (s->type == LXB_DOM_NODE_TYPE_TEXT && text_node_is_blank(s)) continue; if (s->type == LXB_DOM_NODE_TYPE_ELEMENT...
- `cell_has_nested_table` (function) `src/page_view.c:4944` `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)` -- Nonzero if cell has a descendant table box: it is then a structural CONTAINER, not a leaf cell.
- `next_skip` (function) `src/page_view.c:4953` `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)` -- Pre-order successor that does NOT descend into n's children (used to skip an * already-decided subtree during the...
- `cell_anchors` (function) `src/page_view.c:4964` `static const lxb_dom_node_t *cell_anchors(const lxb_dom_node_t *cell, int *count)` -- First <a href> element in the cell's subtree, with *count receiving how many * such anchors exist, capped at 2 (only...
- `links` (function) `src/page_view.c:4982` `* its links (the Hacker News case: every story link lives inside a <td>), so the
 * caller flows ...`
- `flow_table` (function) `src/page_view.c:5003` `static int flow_table(pv_flow_reg *fr, const lxb_dom_node_t *table)`
- `in_flow_table_cell` (function) `src/page_view.c:5015` `static int in_flow_table_cell(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,
           ...`
- `table` (function) `src/page_view.c:5024` `* FLOW table (multi-link: walked so its links survive) do NOT suppress their
 * content -- their ...`
- `table_columns` (function) `src/page_view.c:5042` `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)` -- Grid column count of a table: the maximum number of logical columns across all its rows, computed by summing each...
- `in_hidden_subtree` (function) `src/page_view.c:5116` `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
               ...` -- Nonzero if n or any ancestor up to base has display:none (from the <style> sheet or its inline style=). display:none...
- `in_boilerplate_subtree` (function) `src/page_view.c:5140` `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` -- Nonzero if n or any ancestor up to base is page boilerplate (<nav>/<header>/ <footer>/<aside>).
- `in_closed_details_subtree` (function) `src/page_view.c:5155` `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` -- Nonzero if n or any ancestor up to base is inside a <details> without an `open` attribute and n is NOT inside its...
- `pv_build` (function) `src/page_view.c:5175` `pv_status pv_build(const hp_document *doc, pv_view **out)`
- `pv_build_ex` (function) `src/page_view.c:5179` `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)`
- `pv_build_full` (function) `src/page_view.c:5183` `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                     ...`
- `annotate_replaced_run` (function) `src/page_view.c:5205` `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,
                            ...` -- Attaches the layout membership a replaced run needs to take part in its surroundings: flex/grid container identity...
- `pv_root_insets` (function) `src/page_view.c:5278` `void pv_root_insets(const css_style *body, int out[4])`
- `collect_page_css` (function) `src/page_view.c:5288` `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,
                     ...`
- `pv_build_styled` (function) `src/page_view.c:5317` `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                   ...`
- `inside` (function) `src/page_view.c:5427` `* page inside (the top one collapses with the first child's margin), so a * margin-only body stays box-less. */...`
- `control` (function) `src/page_view.c:5736` `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);`
- `px` (function) `src/page_view.c:5914` `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */
                if (iw <...`
- `band` (function) `src/page_view.c:5980` `* run: without its float annotation it cut the band (the icon row of a * `float:right` social list became one float...`
- `height` (function) `src/page_view.c:6007` `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
- `block_id` (function) `src/page_view.c:6148` `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it...`
- `URL` (function) `src/page_view.c:6289` `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
- `block` (function) `src/page_view.c:6577` `* block (Gecko): it never resolves as its own block here. */ int opens_line = block != n && (pending_break || block...`
- `flow` (function) `src/page_view.c:6755` `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through...`
- `engine` (function) `src/page_view.c:6861` `* layout engine (contiguous item gather) drops every cell onto its own row and
         * a 2-col...`
- `line` (function) `src/page_view.c:6870` `* to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);`
- `pv_css_drops` (function) `src/page_view.c:7003` `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,
                       const cha...` -- Diagnostic counterpart to pv_build_styled: same document, same collected CSS text, same @media/root-scope context...
- `pv_computed_new` (function) `src/page_view.c:7037` `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css,
  ...`
- `pv_computed_get` (function) `src/page_view.c:7056` `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st,
                    do...`
- `pv_computed_free` (function) `src/page_view.c:7078` `void pv_computed_free(pv_computed *pc)`

## src/pdf_export.c
Depends on: `include/pdf_export.h`
- `pe_safe_basename` (function) `src/pdf_export.c:25` `pe_status pe_safe_basename(const char *title, char *out, size_t outsz)`
- `pe_build_path_ext` (function) `src/pdf_export.c:66` `pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,
                ...`
- `pe_build_path` (function) `src/pdf_export.c:91` `pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz)`
- `pe_paginate` (function) `src/pdf_export.c:95` `size_t pe_paginate(const double *tops, const double *heights, size_t n,
                   double...`


Next: [API_p10.md](API_p10.md)
