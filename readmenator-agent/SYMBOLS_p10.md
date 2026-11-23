# Symbols (page 10 of 18)
Previous: [SYMBOLS_p9.md](SYMBOLS_p9.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `drop` | function | `src/mask_cache.c:28` | `static void drop(mkc_cache *c, mkc_entry *e)` |
| `find` | function | `src/mask_cache.c:36` | `static mkc_entry *find(mkc_cache *c, const mkc_key *k)` |
| `key` | type_alias | `src/mask_cache.c:7` | `typedef struct mkc_entry { mkc_key key;` |
| `key_eq` | function | `src/mask_cache.c:22` | `static int key_eq(const mkc_key *a, const mkc_key *b)` |
| `mkc_bytes` | function | `src/mask_cache.c:111` | `size_t mkc_bytes(const mkc_cache *c)` |
| `mkc_cache` | struct | `src/mask_cache.c:15` | `` |
| `mkc_clear` | function | `src/mask_cache.c:60` | `void mkc_clear(mkc_cache *c)` |
| `mkc_count` | function | `src/mask_cache.c:113` | `size_t mkc_count(const mkc_cache *c)` |
| `mkc_entry` | struct | `src/mask_cache.c:7` | `` |
| `mkc_free` | function | `src/mask_cache.c:65` | `void mkc_free(mkc_cache *c)` |
| `mkc_get` | function | `src/mask_cache.c:72` | `const unsigned char *mkc_get(mkc_cache *c, const mkc_key *k, int *stride)` |
| `mkc_new` | function | `src/mask_cache.c:49` | `mkc_cache *mkc_new(size_t byte_budget, size_t max_entries)` |
| `mkc_put` | function | `src/mask_cache.c:81` | `unsigned char *mkc_put(mkc_cache *c, const mkc_key *k, int stride)` |
| `oldest` | function | `src/mask_cache.c:42` | `static mkc_entry *oldest(mkc_cache *c)` |
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
| `nt_cancel` | function | `src/nav_token.c:38` | `void nt_cancel(nt_token *t)` |
| `nt_cancelled` | function | `src/nav_token.c:42` | `int nt_cancelled(const nt_token *t)` |
| `nt_foreground` | function | `src/nav_token.c:51` | `int nt_foreground(const nt_token *t)` |
| `nt_id` | function | `src/nav_token.c:56` | `uint64_t nt_id(const nt_token *t)` |
| `nt_new` | function | `src/nav_token.c:16` | `nt_token *nt_new(void)` |
| `nt_ref` | function | `src/nav_token.c:26` | `nt_token *nt_ref(nt_token *t)` |
| `nt_route` | function | `src/nav_token.c:58` | `nt_route_kind nt_route(const nt_token *job, const nt_token *active, nt_token *const *parked,     ...` |
| `nt_set_foreground` | function | `src/nav_token.c:47` | `void nt_set_foreground(nt_token *t, int on)` |
| `nt_token` | struct | `src/nav_token.c:7` | `` |
| `nt_unref` | function | `src/nav_token.c:31` | `void nt_unref(nt_token **tp)` |
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
| `PV_CELL_NESTED` | macro | `src/page_view.c:5578` | `#define PV_CELL_NESTED` |
| `PV_CELL_RICH` | macro | `src/page_view.c:5579` | `#define PV_CELL_RICH` |
| `PV_COLOR_TOKEN_MAX` | macro | `src/page_view.c:1231` | `#define PV_COLOR_TOKEN_MAX` |
| `PV_CQ_NODES_MAX` | macro | `src/page_view.c:2453` | `#define PV_CQ_NODES_MAX` |
| `PV_FONT_CHAIN_MAX` | macro | `src/page_view.c:69` | `#define PV_FONT_CHAIN_MAX` |
| `PV_FONT_PCT_MAX` | macro | `src/page_view.c:71` | `#define PV_FONT_PCT_MAX` |
| `PV_FONT_PCT_MIN` | macro | `src/page_view.c:70` | `#define PV_FONT_PCT_MIN` |
| `PV_FONT_REL_MAX` | macro | `src/page_view.c:63` | `#define PV_FONT_REL_MAX` |
| `PV_FONT_REL_MIN` | macro | `src/page_view.c:62` | `#define PV_FONT_REL_MIN` |
| `PV_FRAME_DEF_H` | macro | `src/page_view.c:4669` | `#define PV_FRAME_DEF_H` |
| `PV_FRAME_DEF_W` | macro | `src/page_view.c:4668` | `#define PV_FRAME_DEF_W` |
| `PV_FRAME_URL_MAX` | macro | `src/page_view.c:4670` | `#define PV_FRAME_URL_MAX` |
| `PV_MAX_BOXES` | macro | `src/page_view.c:1271` | `#define PV_MAX_BOXES` |
| `PV_MAX_DIM` | macro | `src/page_view.c:57` | `#define PV_MAX_DIM` |
| `PV_MAX_GRID_COLS` | macro | `src/page_view.c:1263` | `#define PV_MAX_GRID_COLS` |
| `PV_MAX_INLINE_ROW_ITEMS` | macro | `src/page_view.c:3221` | `#define PV_MAX_INLINE_ROW_ITEMS` |
| `PV_MAX_STYLE_BYTES` | macro | `src/page_view.c:5658` | `#define PV_MAX_STYLE_BYTES` |
| `PV_NODE_MAP_INIT_CAP` | macro | `src/page_view.c:354` | `#define PV_NODE_MAP_INIT_CAP` |
| `PV_STYLE_RESERVE_MAX` | macro | `src/page_view.c:2475` | `#define PV_STYLE_RESERVE_MAX` |
| `PV_STYLE_RETIRE_MAX` | macro | `src/page_view.c:2409` | `#define PV_STYLE_RETIRE_MAX` |
| `PV_TEXTLESS_DEPTH_MAX` | macro | `src/page_view.c:3623` | `#define PV_TEXTLESS_DEPTH_MAX` |
| `URL` | function | `src/page_view.c:7022` | `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `_POSIX_C_SOURCE` | macro | `src/page_view.c:10` | `#define _POSIX_C_SOURCE` |
| `acquire_page_sheet` | function | `src/page_view.c:4948` | `static shc_sheet *acquire_page_sheet(lxb_dom_node_t *root, const char *extern_css,               ...` |
| `address` | function | `src/page_view.c:1274` | `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <=...` |
| `after_pending_emit` | function | `src/page_view.c:1969` | `static pv_status after_pending_emit(pv_view *v, pv_container_reg *reg, pv_item_track *items,     ...` |
| `annotate_flow_run` | function | `src/page_view.c:1920` | `static void annotate_flow_run(pv_view *v, pv_container_reg *reg, pv_item_track *items,           ...` |
| `annotate_replaced_run` | function | `src/page_view.c:5797` | `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,                             ...` |
| `ascii_ieq` | function | `src/page_view.c:5007` | `static int ascii_ieq(const char *s, const char *lit)` |
| `attr_dup` | function | `src/page_view.c:5019` | `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)` |
| `attributes` | function | `src/page_view.c:4898` | `* carries those attributes (spec/css.md, "Root matcher"). */ static int root_els_match(void *ctx,...` |
| `band` | function | `src/page_view.c:6696` | `* run: without its float annotation it cut the band (the icon row of a * `float:right` social list became one float...` |
| `block` | function | `src/page_view.c:7299` | `* block (Gecko): it never resolves as its own block here. */ int opens_line = block != n && (pending_break \|\| block...` |
| `block_id` | function | `src/page_view.c:6881` | `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it...` |
| `border_side_cleared` | function | `src/page_view.c:1621` | `static int border_side_cleared(int width, int style)` |
| `box_reg_free` | function | `src/page_view.c:2036` | `static void box_reg_free(pv_box_reg *r)` |
| `box_reg_id` | function | `src/page_view.c:2296` | `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,            ...` |
| `box_reg_id_ex` | function | `src/page_view.c:3010` | `static int box_reg_id_ex(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,         ...` |
| `boxdef_from_style` | function | `src/page_view.c:2045` | `static void boxdef_from_style(pv_box_def *d, const css_style *cs)` |
| `builder` | function | `src/page_view.c:3135` | `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box  * (the ...` |
| `cached_element_style` | function | `src/page_view.c:2906` | `static css_style cached_element_style(lxb_dom_element_t *el, const css_sheet *sheet,             ...` |
| `cached_element_style_ref` | function | `src/page_view.c:2821` | `static const css_style *cached_element_style_ref(lxb_dom_element_t *el, const css_sheet *sheet,  ...` |
| `cached_pseudo_style` | function | `src/page_view.c:3070` | `static css_style cached_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet,              ...` |
| `causes_block_break` | function | `src/page_view.c:1115` | `static int causes_block_break(lxb_tag_id_t t, css_display display)` |
| `cell_has_nested_table` | function | `src/page_view.c:5457` | `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)` |
| `cell_is_grid_item` | function | `src/page_view.c:5591` | `static int cell_is_grid_item(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,             ...` |
| `cell_is_rich` | function | `src/page_view.c:5555` | `static int cell_is_rich(const lxb_dom_node_t *cell)` |
| `cell_kind` | function | `src/page_view.c:5582` | `static unsigned cell_kind(pv_flow_reg *fr, const lxb_dom_node_t *cell)` |
| `cell_span_attr` | function | `src/page_view.c:5481` | `static int cell_span_attr(const lxb_dom_node_t *cell, const char *name, size_t name_len,         ...` |
| `chain` | type_alias | `src/page_view.c:2388` | `typedef struct pv_var_node { cvr_chain chain;` |
| `child` | function | `src/page_view.c:1282` | `* child (NULL = anonymous item: text directly inside the container);` |
| `children_all_inline_block` | function | `src/page_view.c:3281` | `static int children_all_inline_block(const lxb_dom_node_t *p, const css_sheet *sheet,            ...` |
| `classify_input` | function | `src/page_view.c:5101` | `static pv_input_type classify_input(const char *type)` |
| `col_free_share` | function | `src/page_view.c:2967` | `static int col_free_share(const lxb_dom_node_t *el, const css_style *cs, const css_sheet *sheet, pv_style_cache...` |
| `col_has_free_space` | function | `src/page_view.c:3334` | `static int col_has_free_space(const css_style *cs)` |
| `collapse_ws` | function | `src/page_view.c:4642` | `static char *collapse_ws(const char *s, size_t n)` |
| `collect_page_css` | function | `src/page_view.c:5882` | `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,                      ...` |
| `collect_text` | function | `src/page_view.c:5077` | `static char *collect_text(const lxb_dom_node_t *el)` |
| `cols` | type_alias | `src/page_view.c:1284` | `typedef struct pv_cont_info { int id, display, gap, justify, cols;` |
| `column_gap_candidate` | function | `src/page_view.c:3450` | `static int column_gap_candidate(const lxb_dom_node_t *el, const css_sheet *sheet,                ...` |
| `cont_def_reset` | function | `src/page_view.c:1793` | `static void cont_def_reset(pv_cont_def *d)` |
| `cont_reg_free` | function | `src/page_view.c:1826` | `static void cont_reg_free(pv_container_reg *reg)` |
| `cont_reg_init` | function | `src/page_view.c:1813` | `static int cont_reg_init(pv_container_reg *reg, size_t cap)` |
| `container` | function | `src/page_view.c:4293` | `* membership in this container (and none in any container further out,                  * since i...` |
| `container_id` | function | `src/page_view.c:1832` | `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)` |
| `content` | function | `src/page_view.c:1213` | `* a <noscript> ancestor also suppresses content (the script would run, so the * fallback is hidden);` |
| `control` | function | `src/page_view.c:6449` | `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);` |
| `cp1252_to_ucs` | function | `src/page_view.c:95` | `static unsigned int cp1252_to_ucs(unsigned char c)` |
| `css_has_boxdeco` | function | `src/page_view.c:1646` | `static int css_has_boxdeco(const css_style *cs)` |
| `css_has_hbox` | function | `src/page_view.c:1540` | `static int css_has_hbox(const css_style *cs)` |
| `css_has_hmargin` | function | `src/page_view.c:3486` | `static int css_has_hmargin(const css_style *cs)` |
| `css_has_position` | function | `src/page_view.c:1614` | `static int css_has_position(const css_style *cs)` |
| `css_hbox_resolve` | function | `src/page_view.c:1561` | `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)` |
| `css_inline_boxdeco` | function | `src/page_view.c:4127` | `css_inline_boxdeco(cs) &&                            !is_layout_item(p, sheet, style_cache))` |
| `css_replaced_h_fixed` | function | `src/page_view.c:3117` | `static int css_replaced_h_fixed(lxb_dom_element_t *el, const css_sheet *sheet,                   ...` |
| `css_to_fx_justify` | function | `src/page_view.c:3164` | `static int css_to_fx_justify(css_justify j)` |
| `css_width_declared` | function | `src/page_view.c:2994` | `static int css_width_declared(const css_style *cs)` |
| `dimensions` | function | `src/page_view.c:4839` | `* viewport dimensions (data: inline detection, <picture> <source> scanning). */ static void srcse...` |
| `dup_n` | function | `src/page_view.c:156` | `static char *dup_n(const char *s, size_t n)` |
| `element_is_content_leaf` | function | `src/page_view.c:3714` | `static int element_is_content_leaf(const lxb_dom_node_t *n, const css_sheet *sheet,              ...` |
| `element_is_content_leaf_d` | function | `src/page_view.c:3674` | `static int element_is_content_leaf_d(const lxb_dom_node_t *n, const css_sheet *sheet,            ...` |
| `engine` | function | `src/page_view.c:7587` | `* layout engine (contiguous item gather) drops every cell onto its own row and          * a 2-col...` |
| `find_body` | function | `src/page_view.c:4871` | `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)` |
| `find_root_els` | function | `src/page_view.c:4884` | `static pv_root_els find_root_els(lxb_dom_node_t *root)` |
| `flex_column_flows_as_block` | function | `src/page_view.c:3348` | `static int flex_column_flows_as_block(const lxb_dom_node_t *el, const css_style *cs,             ...` |
| `flex_column_flows_as_block_uncached` | function | `src/page_view.c:3357` | `static int flex_column_flows_as_block_uncached(const lxb_dom_node_t *el, const css_style *cs,    ...` |
| `float` | function | `src/page_view.c:4555` | `* genuinely nested float (oid != id) takes the deferred-column path. */     if (cont->float_oid =...` |
| `flow` | function | `src/page_view.c:7478` | `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through...` |
| `fold_column_gap` | function | `src/page_view.c:3425` | `static void fold_column_gap(const lxb_dom_node_t *el, css_style *cs,                             ...` |
| `font_color_attr` | function | `src/page_view.c:1253` | `static int font_color_attr(lxb_dom_element_t *el)` |
| `form_for` | function | `src/page_view.c:5048` | `static int form_for(const form_table *ft, const lxb_dom_node_t *n,                     const lxb_...` |
| `form_rec` | struct | `src/page_view.c:4989` | `` |
| `form_table` | struct | `src/page_view.c:4995` | `` |
| `forms_add` | function | `src/page_view.c:5028` | `static int forms_add(form_table *ft, const lxb_dom_node_t *node)` |
| `forms_free` | function | `src/page_view.c:5000` | `static void forms_free(form_table *ft)` |
| `generates_box` | function | `src/page_view.c:1096` | `static int generates_box(lxb_tag_id_t t, css_display display)` |
| `generates_box_style` | function | `src/page_view.c:1108` | `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)` |
| `glyphs` | function | `src/page_view.c:2198` | `* glyphs (the runs carry it as their fill source);` |
| `heading_level` | function | `src/page_view.c:1175` | `static int heading_level(lxb_tag_id_t t)` |
| `height` | function | `src/page_view.c:6723` | `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `here` | function | `src/page_view.c:2147` | `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3...` |
| `id` | function | `src/page_view.c:1306` | `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);` |
| `ignored` | function | `src/page_view.c:695` | `* source is ignored (fail-visible: never invisible text from half a      * pattern). A real text-...` |
| `in_boilerplate_subtree` | function | `src/page_view.c:5732` | `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` |
| `in_closed_details_subtree` | function | `src/page_view.c:5747` | `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` |
| `in_collected_cell` | function | `src/page_view.c:5601` | `static int in_collected_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,                ...` |
| `in_hidden_subtree` | function | `src/page_view.c:5705` | `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,                ...` |
| `in_mixed_line` | function | `src/page_view.c:3233` | `static int in_mixed_line(const lxb_dom_node_t *p, const css_sheet *sheet,                        ...` |
| `in_skipped_subtree` | function | `src/page_view.c:1216` | `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,               ...` |
| `inherited_text_color` | function | `src/page_view.c:2973` | `static int inherited_text_color(const lxb_dom_node_t *node, const css_sheet *sheet,              ...` |
| `inside` | function | `src/page_view.c:6139` | `* page inside (the top one collapses with the first child's margin), so a * margin-only body stays box-less. */...` |
| `is_block_like` | function | `src/page_view.c:1045` | `static int is_block_like(lxb_tag_id_t t, css_display display)` |
| `is_block_like_style` | function | `src/page_view.c:1084` | `static int is_block_like_style(lxb_tag_id_t t, const css_style *cs)` |
| `is_block_tag` | function | `src/page_view.c:1020` | `static int is_block_tag(lxb_tag_id_t t)` |
| `is_bold_tag` | function | `src/page_view.c:3183` | `static int is_bold_tag(lxb_tag_id_t t)` |
| `is_float_container_style` | function | `src/page_view.c:3254` | `static int is_float_container_style(const css_style *cs)` |
| `is_inline_container_style` | function | `src/page_view.c:2986` | `static int is_inline_container_style(const css_style *cs)` |
| `is_inline_level_style` | function | `src/page_view.c:3225` | `static int is_inline_level_style(lxb_tag_id_t t, const css_style *cs)` |
| `is_italic_tag` | function | `src/page_view.c:3188` | `static int is_italic_tag(lxb_tag_id_t t)` |
| `is_layout_container` | function | `src/page_view.c:3460` | `static int is_layout_container(const lxb_dom_node_t *el, const css_style *cs,                    ...` |
| `is_plain_wrapper` | function | `src/page_view.c:3662` | `static int is_plain_wrapper(const lxb_dom_node_t *c, const css_style *cs)` |
| `is_skipped_tag` | function | `src/page_view.c:1187` | `static int is_skipped_tag(lxb_tag_id_t t)` |
| `it` | function | `src/page_view.c:3309` | `* without it (minified markup) keeps the row gapless -- the mixed case is a known limit. */ stati...` |
| `item_ordinal` | function | `src/page_view.c:1396` | `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)` |
| `item_sizes_itself` | function | `src/page_view.c:3515` | `static int item_sizes_itself(const lxb_dom_node_t *el, const css_style *cs,                      ...` |
| `item_space_before` | function | `src/page_view.c:1381` | `static int item_space_before(const lxb_dom_node_t *item)` |
| `li_is_list_item` | function | `src/page_view.c:3531` | `static int li_is_list_item(const lxb_dom_node_t *li, const css_sheet *sheet,                     ...` |
| `li_ordinal` | function | `src/page_view.c:5272` | `static int li_ordinal(const lxb_dom_node_t *li)` |
| `line` | function | `src/page_view.c:7596` | `* to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);` |
| `list_marker` | function | `src/page_view.c:5323` | `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,                   ...` |
| `margins` | function | `src/page_view.c:4166` | `* margins (boxdef_from_style) and the painter applies them when                          * it ope...` |
| `mb` | type_alias | `src/page_view.c:1420` | `typedef struct pv_box_info { int l, r, w, center, mt, mb;` |
| `media_has_source` | function | `src/page_view.c:3700` | `static int media_has_source(const lxb_dom_node_t *n)` |
| `nearest_table` | function | `src/page_view.c:5386` | `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,  ...` |
| `next_skip` | function | `src/page_view.c:5471` | `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)` |
| `node_next` | function | `src/page_view.c:1010` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `node_table_role` | function | `src/page_view.c:5368` | `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `node_tag` | function | `src/page_view.c:1208` | `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)` |
| `none` | function | `src/page_view.c:3015` | `* inherited when it declares none (every hamburger bar and divider drawn as * a coloured empty box). A box cannot...` |
| `opens` | function | `src/page_view.c:4074` | `* painter applies it when the box opens (band/shared context) — seeding              * it onto ru...` |
| `outermost` | function | `src/page_view.c:4017` | `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);` |
| `paints` | function | `src/page_view.c:1128` | `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas  * vacías"). Comment a...` |
| `parent_is_author_container` | function | `src/page_view.c:3001` | `static int parent_is_author_container(const lxb_dom_node_t *node, const css_sheet *sheet,        ...` |
| `parent_is_table_internal` | function | `src/page_view.c:5425` | `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `parse_dim` | function | `src/page_view.c:4681` | `static int parse_dim(const lxb_char_t *s, size_t len)` |
| `positions` | function | `src/page_view.c:145` | `* positions (cp == 0) keep the legacy '?' fallback. */ unsigned int cp = cp1252_to_ucs(c);` |
| `present` | function | `src/page_view.c:4698` | `* when no width descriptors are present (density-only or bare URLs). */ static void srcset_best_u...` |
| `pseudo_box_reg` | function | `src/page_view.c:2325` | `static int pseudo_box_reg(pv_box_reg *r, const lxb_dom_node_t *el, int which,                    ...` |
| `pseudo_generates_box` | function | `src/page_view.c:2346` | `static int pseudo_generates_box(const css_style *ps)` |
| `pseudo_is_block` | function | `src/page_view.c:2363` | `static int pseudo_is_block(const css_style *ps)` |
| `pseudo_is_oof` | function | `src/page_view.c:2359` | `static int pseudo_is_oof(const css_style *ps)` |
| `pseudo_key` | function | `src/page_view.c:2369` | `static const void *pseudo_key(const lxb_dom_node_t *el, int which)` |
| `pv_add_box_def` | function | `src/page_view.c:958` | `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)` |
| `pv_add_cont_def` | function | `src/page_view.c:936` | `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)` |
| `pv_after_pending` | struct | `src/page_view.c:1955` | `` |
| `pv_append` | function | `src/page_view.c:441` | `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,                     c...` |
| `pv_append_image` | function | `src/page_view.c:476` | `pv_status pv_append_image(pv_view *v, int heading, int block_break,                           con...` |
| `pv_append_input` | function | `src/page_view.c:506` | `pv_status pv_append_input(pv_view *v, int heading, int block_break,                           pv_...` |
| `pv_append_svg` | function | `src/page_view.c:582` | `pv_status pv_append_svg(pv_view *v, int heading, int block_break,                         const c...` |
| `pv_append_video` | function | `src/page_view.c:546` | `pv_status pv_append_video(pv_view *v, int heading, int block_break,                           con...` |
| `pv_apply_pres_hints` | function | `src/page_view.c:2721` | `static void pv_apply_pres_hints(lxb_dom_element_t *el, css_style *cs)` |
| `pv_at` | function | `src/page_view.c:993` | `const pv_run *pv_at(const pv_view *v, size_t i)` |
| `pv_box_at` | function | `src/page_view.c:1002` | `const pv_box_def *pv_box_at(const pv_view *v, size_t i)` |
| `pv_box_count` | function | `src/page_view.c:998` | `size_t pv_box_count(const pv_view *v)` |
| `pv_box_info` | struct | `src/page_view.c:1420` | `` |
| `pv_box_reg` | struct | `src/page_view.c:1997` | `` |
| `pv_build` | function | `src/page_view.c:5767` | `pv_status pv_build(const hp_document *doc, pv_view **out)` |
| `pv_build_cached` | function | `src/page_view.c:6015` | `pv_status pv_build_cached(const hp_document *doc, int js_enabled, int reader,                    ...` |
| `pv_build_cq` | function | `src/page_view.c:6022` | `pv_status pv_build_cq(const hp_document *doc, int js_enabled, int reader,                       i...` |
| `pv_build_ex` | function | `src/page_view.c:5771` | `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)` |
| `pv_build_full` | function | `src/page_view.c:5775` | `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,                      ...` |
| `pv_build_live` | function | `src/page_view.c:6029` | `pv_status pv_build_live(const hp_document *doc, int js_enabled, int reader,                      ...` |
| `pv_build_styled` | function | `src/page_view.c:6008` | `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,                    ...` |
| `pv_cache_find` | function | `src/page_view.c:2545` | `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cache_put` | function | `src/page_view.c:2565` | `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,                      ...` |
| `pv_cache_reindex` | function | `src/page_view.c:2463` | `static void pv_cache_reindex(pv_style_cache *c)` |
| `pv_cached_font_px` | function | `src/page_view.c:2560` | `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cell_table` | function | `src/page_view.c:2705` | `static lxb_dom_element_t *pv_cell_table(lxb_dom_element_t *el)` |
| `pv_cnt_attr` | function | `src/page_view.c:5924` | `static const char *pv_cnt_attr(void *ctx, const char *name)` |
| `pv_cnt_attr_ctx` | struct | `src/page_view.c:5919` | `` |
| `pv_cnt_enter` | function | `src/page_view.c:5948` | `static int pv_cnt_enter(cnt_state *st, lxb_dom_node_t *n, int depth, const css_sheet *sheet,     ...` |
| `pv_cnt_exit` | function | `src/page_view.c:5972` | `static void pv_cnt_exit(cnt_state *st, lxb_dom_node_t *n, int depth, const css_sheet *sheet,     ...` |
| `pv_cnt_resolve_field` | function | `src/page_view.c:5937` | `static void pv_cnt_resolve_field(const cnt_state *st, lxb_dom_element_t *el, char *field)` |
| `pv_computed` | struct | `src/page_view.c:7784` | `` |
| `pv_computed_free` | function | `src/page_view.c:7830` | `void pv_computed_free(pv_computed *pc)` |
| `pv_computed_get` | function | `src/page_view.c:7808` | `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st,                     do...` |
| `pv_computed_new` | function | `src/page_view.c:7789` | `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css,   ...` |
| `pv_computed_new_cached` | function | `src/page_view.c:7794` | `pv_computed *pv_computed_new_cached(const hp_document *doc, int prefers_dark,                    ...` |
| `pv_cont_at` | function | `src/page_view.c:953` | `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)` |
| `pv_cont_count` | function | `src/page_view.c:949` | `size_t pv_cont_count(const pv_view *v)` |
| `pv_cont_info` | struct | `src/page_view.c:1284` | `` |
| `pv_container_reg` | struct | `src/page_view.c:1779` | `` |
| `pv_content_hidden` | function | `src/page_view.c:1441` | `int pv_content_hidden(int box_hidden, int run_visibility)` |
| `pv_control_frame_cleared` | function | `src/page_view.c:1627` | `static int pv_control_frame_cleared(const css_style *cs)` |
| `pv_count` | function | `src/page_view.c:989` | `size_t pv_count(const pv_view *v)` |
| `pv_counters_pass` | function | `src/page_view.c:5984` | `static void pv_counters_pass(lxb_dom_node_t *root, const css_sheet *sheet, pv_style_cache *cache)` |
| `pv_cq_push` | function | `src/page_view.c:2638` | `static const cmq_container *pv_cq_push(pv_style_cache *cache, const lxb_dom_node_t *node,        ...` |
| `pv_css_drops` | function | `src/page_view.c:7755` | `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,                        const cha...` |
| `pv_def_h` | struct | `src/page_view.c:2397` | `` |
| `pv_element_has_before` | function | `src/page_view.c:3608` | `static int pv_element_has_before(lxb_dom_node_t *n, const css_sheet *sheet,                      ...` |
| `pv_flow_reg` | struct | `src/page_view.c:3719` | `` |
| `pv_flow_reg` | struct | `src/page_view.c:5348` | `` |
| `pv_frame_marked` | function | `src/page_view.c:4672` | `static int pv_frame_marked(const lxb_dom_node_t *n)` |
| `pv_free` | function | `src/page_view.c:971` | `void pv_free(pv_view *v)` |
| `pv_hint_attr` | function | `src/page_view.c:2684` | `static const char *pv_hint_attr(void *ctx, const char *name, size_t *len)` |
| `pv_item_track` | struct | `src/page_view.c:1367` | `` |
| `pv_mauto_of` | function | `src/page_view.c:1554` | `static int pv_mauto_of(const css_style *cs)` |
| `pv_new` | function | `src/page_view.c:437` | `pv_view *pv_new(void)` |
| `pv_node_map` | struct | `src/page_view.c:356` | `` |
| `pv_node_map_build` | function | `src/page_view.c:426` | `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root,                         ...` |
| `pv_node_map_free` | function | `src/page_view.c:374` | `static void pv_node_map_free(pv_node_map *m)` |
| `pv_node_map_init` | function | `src/page_view.c:364` | `static int pv_node_map_init(pv_node_map *m)` |
| `pv_parent_element` | function | `src/page_view.c:2677` | `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)` |
| `pv_placeholder_color` | function | `src/page_view.c:920` | `int pv_placeholder_color(const css_style *ph)` |
| `pv_ptr_hash` | function | `src/page_view.c:2455` | `static size_t pv_ptr_hash(const void *p)` |
| `pv_ptrmap` | struct | `src/page_view.c:302` | `` |
| `pv_ptrmap_free` | function | `src/page_view.c:348` | `static void pv_ptrmap_free(pv_ptrmap *m)` |
| `pv_ptrmap_get` | function | `src/page_view.c:318` | `static int pv_ptrmap_get(const pv_ptrmap *m, const void *k, int *out)` |
| `pv_ptrmap_put` | function | `src/page_view.c:326` | `static void pv_ptrmap_put(pv_ptrmap *m, const void *k, int v)` |
| `pv_ptrmap_slot` | function | `src/page_view.c:308` | `static size_t pv_ptrmap_slot(const pv_ptrmap *m, const void *k)` |
| `pv_root_els` | struct | `src/page_view.c:4880` | `` |
| `pv_root_insets` | function | `src/page_view.c:5872` | `void pv_root_insets(const css_style *body, int out[4])` |
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
| `pv_style_cache` | struct | `src/page_view.c:2411` | `` |
| `pv_style_cache_free` | function | `src/page_view.c:2499` | `static void pv_style_cache_free(pv_style_cache *c)` |
| `pv_style_cache_reserve` | function | `src/page_view.c:2520` | `static void pv_style_cache_reserve(pv_style_cache *c, size_t n)` |
| `pv_svg_append_root_attrs` | function | `src/page_view.c:891` | `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs,                ...` |
| `pv_text_ext_merge` | function | `src/page_view.c:1475` | `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)` |
| `pv_text_ext_reset` | function | `src/page_view.c:1447` | `void pv_text_ext_reset(pv_text_ext *e)` |
| `pv_var_node` | struct | `src/page_view.c:2388` | `` |
| `pv_var_push` | function | `src/page_view.c:2615` | `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,                       ...` |
| `px` | function | `src/page_view.c:6630` | `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */                 if (iw <...` |
| `resolve_context` | function | `src/page_view.c:3731` | `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,                 ...` |
| `resolves` | function | `src/page_view.c:1074` | `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close  * button/tooltip w...` |
| `roman_marker` | function | `src/page_view.c:5298` | `static void roman_marker(int n, int upper, char *out, size_t cap)` |
| `row_lone_float_side` | function | `src/page_view.c:3262` | `static int row_lone_float_side(const lxb_dom_node_t *p, const css_sheet *sheet,                  ...` |
| `run_init_common` | function | `src/page_view.c:170` | `static void run_init_common(pv_run *r)` |
| `serialize_subtree` | function | `src/page_view.c:4623` | `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)` |
| `size` | function | `src/page_view.c:3108` | `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */ static void app...` |
| `srcset_slot_width` | function | `src/page_view.c:4793` | `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,                               ...` |
| `string` | function | `src/page_view.c:4909` | `* Returns a heap string (caller frees) or NULL when neither carries a class —  * NULL simply mean...` |
| `subtree_has_own_text` | function | `src/page_view.c:3640` | `static int subtree_has_own_text(const lxb_dom_node_t *n, const lxb_dom_node_t *base,             ...` |
| `subtree_is_oof` | function | `src/page_view.c:3088` | `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,                      ...` |
| `sz_count` | function | `src/page_view.c:4601` | `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)` |
| `sz_fill` | struct | `src/page_view.c:4609` | `` |
| `sz_write` | function | `src/page_view.c:4615` | `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)` |
| `table_cell_pos` | function | `src/page_view.c:3726` | `static int table_cell_pos(struct pv_flow_reg *fr, const lxb_dom_node_t *table, const lxb_dom_node_t *cell, int *row...` |
| `table_columns` | function | `src/page_view.c:5622` | `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)` |
| `table_columns_scan` | function | `src/page_view.c:5631` | `static int table_columns_scan(const lxb_dom_node_t *table, const pv_flow_reg *fr)` |
| `table_next_row` | function | `src/page_view.c:5494` | `static const lxb_dom_node_t *table_next_row(const lxb_dom_node_t *table,                         ...` |
| `text_node_is_blank` | function | `src/page_view.c:1380` | `static int text_node_is_blank(const lxb_dom_node_t *c);` |
| `them` | function | `src/page_view.c:1371` | `* them (PV_BR_ATOM_SPACE);` |
| `trying` | function | `src/page_view.c:2007` | `* a real page passes without trying (slashdot's front page saturates it), and past  * it box_reg_...` |
| `ua_field_background` | function | `src/page_view.c:1639` | `static void ua_field_background(pv_box_def *d, int frame_cleared)` |
| `ua_tag_of` | function | `src/page_view.c:1153` | `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)` |
| `under_unrendered` | function | `src/page_view.c:5064` | `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)` |
| `url` | function | `src/page_view.c:6054` | `* fetches and drops url()/@-rules). A NULL sheet is treated as empty by the css * module, so OOM here degrades to...` |
| `utf8_encode` | function | `src/page_view.c:109` | `static size_t utf8_encode(unsigned int cp, char *out)` |
| `utf8_sanitized_dup` | function | `src/page_view.c:122` | `static char *utf8_sanitized_dup(const char *s)` |
| `walk` | function | `src/page_view.c:4414` | `* far on this walk (they are all inside this element). */                          /* The innermo...` |
| `pe_build_path` | function | `src/pdf_export.c:91` | `pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz)` |
| `pe_build_path_ext` | function | `src/pdf_export.c:66` | `pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,                 ...` |
| `pe_paginate` | function | `src/pdf_export.c:95` | `size_t pe_paginate(const double *tops, const double *heights, size_t n,                    double...` |
| `pe_safe_basename` | function | `src/pdf_export.c:25` | `pe_status pe_safe_basename(const char *title, char *out, size_t outsz)` |
| `PT_LINE_CAP` | macro | `src/perf_trace.c:107` | `#define PT_LINE_CAP` |
| `cmp_u64` | function | `src/perf_trace.c:71` | `static int cmp_u64(const void *a, const void *b)` |
| `pt_count` | function | `src/perf_trace.c:35` | `size_t pt_count(const pt_trace *t, pt_stage stage)` |
| `pt_elapsed_us` | function | `src/perf_trace.c:21` | `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us)` |
| `pt_format` | function | `src/perf_trace.c:109` | `size_t pt_format(const pt_trace *t, char *buf, size_t cap)` |
| `pt_init` | function | `src/perf_trace.c:16` | `void pt_init(pt_trace *t)` |
| `pt_last_us` | function | `src/perf_trace.c:40` | `uint64_t pt_last_us(const pt_trace *t, pt_stage stage)` |
| `pt_max_us` | function | `src/perf_trace.c:60` | `uint64_t pt_max_us(const pt_trace *t, pt_stage stage)` |
| `pt_median_us` | function | `src/perf_trace.c:79` | `uint64_t pt_median_us(const pt_trace *t, pt_stage stage)` |
| `pt_min_us` | function | `src/perf_trace.c:49` | `uint64_t pt_min_us(const pt_trace *t, pt_stage stage)` |
| `pt_record` | function | `src/perf_trace.c:26` | `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us)` |
| `pt_stage_name` | function | `src/perf_trace.c:89` | `const char *pt_stage_name(pt_stage stage)` |
| `PQS_SS_LEN` | macro | `src/pq_seal.c:17` | `#define PQS_SS_LEN` |
| `derive_key` | function | `src/pq_seal.c:81` | `static int derive_key(const uint8_t ss[PQS_SS_LEN], const uint8_t wrap[LS_KEY_LEN],              ...` |
| `keys_wrap` | function | `src/pq_seal.c:35` | `static pqs_keys *keys_wrap(EVP_PKEY *pkey)` |
| `pqs_buf_free` | function | `src/pq_seal.c:23` | `void pqs_buf_free(uint8_t *buf, size_t len)` |
| `pqs_export` | function | `src/pq_seal.c:55` | `pqs_status pqs_export(const pqs_keys *k, uint8_t **der, size_t *len)` |
| `pqs_free` | function | `src/pq_seal.c:29` | `void pqs_free(pqs_keys *k)` |
| `pqs_generate` | function | `src/pq_seal.c:42` | `pqs_status pqs_generate(pqs_keys **out)` |
| `pqs_import` | function | `src/pq_seal.c:68` | `pqs_status pqs_import(const uint8_t *der, size_t len, pqs_keys **out)` |
| `pqs_keys` | struct | `src/pq_seal.c:19` | `` |
| `pqs_open` | function | `src/pq_seal.c:147` | `pqs_status pqs_open(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],                     const ...` |
| `pqs_seal` | function | `src/pq_seal.c:106` | `pqs_status pqs_seal(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],                     const ...` |
| `PF_MAX_URL` | macro | `src/prefetch.c:24` | `#define PF_MAX_URL` |
| `_POSIX_C_SOURCE` | macro | `src/prefetch.c:12` | `#define _POSIX_C_SOURCE` |
| `attr_span` | struct | `src/prefetch.c:65` | `` |
| `ci_eq_span` | function | `src/prefetch.c:58` | `static int ci_eq_span(const char *s, size_t n, const char *kw)` |
| `ci_find` | function | `src/prefetch.c:49` | `static const char *ci_find(const char *p, const char *end, const char *kw)` |
| `ci_starts` | function | `src/prefetch.c:40` | `static int ci_starts(const char *p, const char *end, const char *kw)` |
| `emit` | function | `src/prefetch.c:120` | `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)` |
| `is_name_char` | function | `src/prefetch.c:30` | `static int is_name_char(char c)` |
| `is_ws` | function | `src/prefetch.c:26` | `static int is_ws(char c)` |
| `js_ident_ch` | function | `src/prefetch.c:213` | `static int js_ident_ch(char c)` |
| `js_skip_string` | function | `src/prefetch.c:225` | `static size_t js_skip_string(const char *s, size_t i, size_t n)` |
| `js_skip_ws` | function | `src/prefetch.c:218` | `static size_t js_skip_ws(const char *s, size_t i, size_t n)` |
| `js_take_spec` | function | `src/prefetch.c:232` | `static void js_take_spec(const char *s, size_t i, size_t n,                          char (*out)[...` |
| `lower` | function | `src/prefetch.c:35` | `static int lower(int c)` |
| `pf_find_importmap` | function | `src/prefetch.c:489` | `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n)` |
| `pf_follow_imports` | function | `src/prefetch.c:339` | `static void pf_follow_imports(pf_pool *p, const char *base, const char *body, size_t len)` |
| `pf_is_js` | function | `src/prefetch.c:317` | `static int pf_is_js(const char *url, const char *ctype)` |
| `pf_list_free` | function | `src/prefetch.c:202` | `void pf_list_free(pf_list *l)` |
| `pf_pool_add` | function | `src/prefetch.c:294` | `int pf_pool_add(pf_pool *p, const char *url)` |
| `pf_pool_finish` | function | `src/prefetch.c:546` | `void pf_pool_finish(pf_pool *p)` |
| `pf_pool_start` | function | `src/prefetch.c:393` | `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,                   pf_fetch_f...` |
| `pf_pool_start_page` | function | `src/prefetch.c:510` | `int pf_pool_start_page(pf_pool *p, const char *html, size_t len, const char *page_url,           ...` |
| `pf_pool_take` | function | `src/prefetch.c:450` | `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,                  char **body,...` |
| `pf_pooled_fetch` | function | `src/prefetch.c:567` | `int pf_pooled_fetch(void *vctx, const char *method, const char *url,                     const ch...` |
| `pf_scan` | function | `src/prefetch.c:133` | `int pf_scan(const char *html, size_t len, pf_list *out)` |
| `pf_scan_imports` | function | `src/prefetch.c:247` | `size_t pf_scan_imports(const char *js, size_t len, char (*out)[PF_SPEC_MAX], size_t cap)` |
| `pf_url_cb` | function | `src/prefetch.c:325` | `static int pf_url_cb(void *ctx, const char *base, const char *ref, char *out, size_t outsz)` |
| `pf_url_shaped` | function | `src/prefetch.c:330` | `static int pf_url_shaped(const char *sp)` |
| `pf_worker` | function | `src/prefetch.c:355` | `static void *pf_worker(void *arg)` |
| `pool_start` | function | `src/prefetch.c:400` | `static int pool_start(pf_pool *p, const char *const *urls, size_t nurls,                       pf...` |
| `PREFS_MAGIC` | macro | `src/prefs.c:20` | `#define PREFS_MAGIC` |
| `_POSIX_C_SOURCE` | macro | `src/prefs.c:11` | `#define _POSIX_C_SOURCE` |
| `apply_kv` | function | `src/prefs.c:231` | `static void apply_kv(prefs_state *out, const char *key, long val)` |
| `bookmark_push` | function | `src/prefs.c:91` | `static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title)` |
| `ci_contains` | function | `src/prefs.c:327` | `static int ci_contains(const char *s, const char *q)` |
| `ci_eq` | function | `src/prefs.c:313` | `static int ci_eq(char a, char b)` |
| `ci_starts` | function | `src/prefs.c:319` | `static int ci_starts(const char *s, const char *q)` |
| `history_push_back` | function | `src/prefs.c:109` | `static prefs_status history_push_back(prefs_state *p, const char *url)` |
| `prefs_bookmark_index` | function | `src/prefs.c:125` | `int prefs_bookmark_index(const prefs_state *p, const char *url)` |
| `prefs_bookmark_toggle` | function | `src/prefs.c:132` | `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,                              ...` |
| `prefs_bookmarks_page` | function | `src/prefs.c:421` | `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)` |
| `prefs_format` | function | `src/prefs.c:183` | `prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len)` |
| `prefs_free` | function | `src/prefs.c:74` | `void prefs_free(prefs_state *p)` |
| `prefs_history_add` | function | `src/prefs.c:152` | `prefs_status prefs_history_add(prefs_state *p, const char *url)` |
| `prefs_init` | function | `src/prefs.c:66` | `void prefs_init(prefs_state *p)` |
| `prefs_parse` | function | `src/prefs.c:247` | `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)` |
| `prefs_suggest` | function | `src/prefs.c:357` | `int prefs_suggest(const prefs_state *p, const char *query,                   char *out, size_t ro...` |
| `sb_esc` | function | `src/prefs.c:400` | `static void sb_esc(sbuf *b, const char *s)` |
| `sb_link_item` | function | `src/prefs.c:413` | `static void sb_link_item(sbuf *b, const char *url, const char *label)` |
| `sb_put` | function | `src/prefs.c:382` | `static void sb_put(sbuf *b, const char *s, size_t n)` |
| `sb_str` | function | `src/prefs.c:397` | `static void sb_str(sbuf *b, const char *s)` |
| `sbuf` | struct | `src/prefs.c:380` | `` |
| `sugg_push` | function | `src/prefs.c:348` | `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,                       cons...` |
| `title_clean` | function | `src/prefs.c:39` | `static char *title_clean(const char *src)` |
| `url_prefix_match` | function | `src/prefs.c:336` | `static int url_prefix_match(const char *url, const char *q)` |

Next: [SYMBOLS_p11.md](SYMBOLS_p11.md)
