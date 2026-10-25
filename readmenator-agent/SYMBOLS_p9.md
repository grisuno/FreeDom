# Symbols (page 9 of 16)
Previous: [SYMBOLS_p8.md](SYMBOLS_p8.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `_GNU_SOURCE` | macro | `src/local_store.c:825` | `#define _GNU_SOURCE` |
| `aead_decrypt` | function | `src/local_store.c:956` | `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,                      ...` |
| `aead_encrypt` | function | `src/local_store.c:930` | `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,                      ...` |
| `argon2id_derive` | function | `src/local_store.c:892` | `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,                           ...` |
| `cipher_for` | function | `src/local_store.c:882` | `static const EVP_CIPHER *cipher_for(ls_aead aead)` |
| `decrypt_blob` | function | `src/local_store.c:1021` | `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,          ...` |
| `ls_derive_key` | function | `src/local_store.c:921` | `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,                         const...` |
| `ls_free` | function | `src/local_store.c:1117` | `void ls_free(uint8_t *buf, size_t len)` |
| `ls_open` | function | `src/local_store.c:1065` | `ls_status ls_open(const uint8_t key[LS_KEY_LEN],                   const uint8_t *blob, size_t bl...` |
| `ls_open_passphrase` | function | `src/local_store.c:1097` | `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,                         ...` |
| `ls_seal` | function | `src/local_store.c:1052` | `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,                   const uint8_t *p...` |
| `ls_seal_passphrase` | function | `src/local_store.c:1076` | `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,           ...` |
| `seal_core` | function | `src/local_store.c:984` | `static ls_status seal_core(const uint8_t *key, ls_aead aead, uint8_t kdf_id,                     ...` |
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
| `PV_MAX_INLINE_ROW_ITEMS` | macro | `src/page_view.c:2894` | `#define PV_MAX_INLINE_ROW_ITEMS` |
| `PV_MAX_STYLE_BYTES` | macro | `src/page_view.c:5052` | `#define PV_MAX_STYLE_BYTES` |
| `PV_NODE_MAP_INIT_CAP` | macro | `src/page_view.c:346` | `#define PV_NODE_MAP_INIT_CAP` |
| `PV_STYLE_RETIRE_MAX` | macro | `src/page_view.c:2292` | `#define PV_STYLE_RETIRE_MAX` |
| `PV_TEXTLESS_DEPTH_MAX` | macro | `src/page_view.c:3224` | `#define PV_TEXTLESS_DEPTH_MAX` |
| `URL` | function | `src/page_view.c:6270` | `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `_POSIX_C_SOURCE` | macro | `src/page_view.c:10` | `#define _POSIX_C_SOURCE` |
| `address` | function | `src/page_view.c:1257` | `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <=...` |
| `after_pending_emit` | function | `src/page_view.c:1862` | `static pv_status after_pending_emit(pv_view *v, pv_container_reg *reg, pv_item_track *items,     ...` |
| `annotate_flow_run` | function | `src/page_view.c:1814` | `static void annotate_flow_run(pv_view *v, pv_container_reg *reg, pv_item_track *items,           ...` |
| `annotate_replaced_run` | function | `src/page_view.c:5188` | `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,                             ...` |
| `ascii_ieq` | function | `src/page_view.c:4470` | `static int ascii_ieq(const char *s, const char *lit)` |
| `attr_dup` | function | `src/page_view.c:4482` | `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)` |
| `attributes` | function | `src/page_view.c:4404` | `* carries those attributes (spec/css.md, "Root matcher"). */ static int root_els_match(void *ctx,...` |
| `band` | function | `src/page_view.c:5961` | `* run: without its float annotation it cut the band (the icon row of a * `float:right` social list became one float...` |
| `bgcolor_attr` | function | `src/page_view.c:1235` | `static int bgcolor_attr(lxb_dom_element_t *el)` |
| `block` | function | `src/page_view.c:6558` | `* block (Gecko): it never resolves as its own block here. */ int opens_line = block != n && (pending_break \|\| block...` |
| `block_id` | function | `src/page_view.c:6129` | `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it...` |
| `box_reg_free` | function | `src/page_view.c:1929` | `static void box_reg_free(pv_box_reg *r)` |
| `box_reg_id` | function | `src/page_view.c:2186` | `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,            ...` |
| `box_reg_id_ex` | function | `src/page_view.c:2705` | `static int box_reg_id_ex(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,         ...` |
| `boxdef_from_style` | function | `src/page_view.c:1938` | `static void boxdef_from_style(pv_box_def *d, const css_style *cs)` |
| `builder` | function | `src/page_view.c:2808` | `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box  * (the ...` |
| `cached_element_style` | function | `src/page_view.c:2627` | `static css_style cached_element_style(lxb_dom_element_t *el, const css_sheet *sheet,             ...` |
| `cached_element_style_ref` | function | `src/page_view.c:2544` | `static const css_style *cached_element_style_ref(lxb_dom_element_t *el, const css_sheet *sheet,  ...` |
| `cached_pseudo_style` | function | `src/page_view.c:2743` | `static css_style cached_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet,              ...` |
| `causes_block_break` | function | `src/page_view.c:1091` | `static int causes_block_break(lxb_tag_id_t t, css_display display)` |
| `cell_anchors` | function | `src/page_view.c:4947` | `static const lxb_dom_node_t *cell_anchors(const lxb_dom_node_t *cell, int *count)` |
| `cell_has_nested_table` | function | `src/page_view.c:4927` | `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)` |
| `chain` | type_alias | `src/page_view.c:2278` | `typedef struct pv_var_node { cvr_chain chain;` |
| `child` | function | `src/page_view.c:1265` | `* child (NULL = anonymous item: text directly inside the container);` |
| `children_all_inline_block` | function | `src/page_view.c:2922` | `static int children_all_inline_block(const lxb_dom_node_t *p, const css_sheet *sheet,            ...` |
| `classify_input` | function | `src/page_view.c:4564` | `static pv_input_type classify_input(const char *type)` |
| `col_free_share` | function | `src/page_view.c:2688` | `static int col_free_share(const lxb_dom_node_t *el, const css_style *cs, const css_sheet *sheet, pv_style_cache...` |
| `col_has_free_space` | function | `src/page_view.c:2947` | `static int col_has_free_space(const css_style *cs)` |
| `collapse_ws` | function | `src/page_view.c:4163` | `static char *collapse_ws(const char *s, size_t n)` |
| `collect_page_css` | function | `src/page_view.c:5271` | `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,                      ...` |
| `collect_text` | function | `src/page_view.c:4540` | `static char *collect_text(const lxb_dom_node_t *el)` |
| `cols` | type_alias | `src/page_view.c:1267` | `typedef struct pv_cont_info { int id, display, gap, justify, cols;` |
| `column_gap_candidate` | function | `src/page_view.c:3051` | `static int column_gap_candidate(const lxb_dom_node_t *el, const css_sheet *sheet,                ...` |
| `cont_def_reset` | function | `src/page_view.c:1707` | `static void cont_def_reset(pv_cont_def *d)` |
| `container` | function | `src/page_view.c:3853` | `* membership in this container (and none in any container further out,                  * since i...` |
| `container_id` | function | `src/page_view.c:1726` | `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)` |
| `content` | function | `src/page_view.c:1189` | `* a <noscript> ancestor also suppresses content (the script would run, so the * fallback is hidden);` |
| `control` | function | `src/page_view.c:5719` | `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);` |
| `cp1252_to_ucs` | function | `src/page_view.c:90` | `static unsigned int cp1252_to_ucs(unsigned char c)` |
| `css_has_boxdeco` | function | `src/page_view.c:1563` | `static int css_has_boxdeco(const css_style *cs)` |
| `css_has_hbox` | function | `src/page_view.c:1484` | `static int css_has_hbox(const css_style *cs)` |
| `css_has_hmargin` | function | `src/page_view.c:3087` | `static int css_has_hmargin(const css_style *cs)` |
| `css_has_position` | function | `src/page_view.c:1558` | `static int css_has_position(const css_style *cs)` |
| `css_hbox_resolve` | function | `src/page_view.c:1505` | `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)` |
| `css_inline_boxdeco` | function | `src/page_view.c:3690` | `css_inline_boxdeco(cs) &&                            !is_layout_item(p, sheet, style_cache))` |
| `css_replaced_h_fixed` | function | `src/page_view.c:2790` | `static int css_replaced_h_fixed(lxb_dom_element_t *el, const css_sheet *sheet,                   ...` |
| `css_to_fx_justify` | function | `src/page_view.c:2837` | `static int css_to_fx_justify(css_justify j)` |
| `dimensions` | function | `src/page_view.c:4345` | `* viewport dimensions (data: inline detection, <picture> <source> scanning). */ static void srcse...` |
| `dup_n` | function | `src/page_view.c:151` | `static char *dup_n(const char *s, size_t n)` |
| `element_is_content_leaf` | function | `src/page_view.c:3315` | `static int element_is_content_leaf(const lxb_dom_node_t *n, const css_sheet *sheet,              ...` |
| `element_is_content_leaf_d` | function | `src/page_view.c:3275` | `static int element_is_content_leaf_d(const lxb_dom_node_t *n, const css_sheet *sheet,            ...` |
| `engine` | function | `src/page_view.c:6842` | `* layout engine (contiguous item gather) drops every cell onto its own row and          * a 2-col...` |
| `find_body` | function | `src/page_view.c:4377` | `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)` |
| `find_root_els` | function | `src/page_view.c:4390` | `static pv_root_els find_root_els(lxb_dom_node_t *root)` |
| `flex_column_flows_as_block` | function | `src/page_view.c:2958` | `static int flex_column_flows_as_block(const lxb_dom_node_t *el, const css_style *cs,             ...` |
| `float` | function | `src/page_view.c:4076` | `* genuinely nested float (oid != id) takes the deferred-column path. */     if (cont->float_oid =...` |
| `flow` | function | `src/page_view.c:6736` | `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through...` |
| `flow_table` | function | `src/page_view.c:4986` | `static int flow_table(pv_flow_reg *fr, const lxb_dom_node_t *table)` |
| `fold_column_gap` | function | `src/page_view.c:3026` | `static void fold_column_gap(const lxb_dom_node_t *el, css_style *cs,                             ...` |
| `font_color_attr` | function | `src/page_view.c:1229` | `static int font_color_attr(lxb_dom_element_t *el)` |
| `form_for` | function | `src/page_view.c:4511` | `static int form_for(const form_table *ft, const lxb_dom_node_t *n,                     const lxb_...` |
| `form_rec` | struct | `src/page_view.c:4452` | `` |
| `form_table` | struct | `src/page_view.c:4458` | `` |
| `forms_add` | function | `src/page_view.c:4491` | `static int forms_add(form_table *ft, const lxb_dom_node_t *node)` |
| `forms_free` | function | `src/page_view.c:4463` | `static void forms_free(form_table *ft)` |
| `generates_box` | function | `src/page_view.c:1072` | `static int generates_box(lxb_tag_id_t t, css_display display)` |
| `generates_box_style` | function | `src/page_view.c:1084` | `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)` |
| `glyphs` | function | `src/page_view.c:2088` | `* glyphs (the runs carry it as their fill source);` |
| `heading_level` | function | `src/page_view.c:1151` | `static int heading_level(lxb_tag_id_t t)` |
| `height` | function | `src/page_view.c:5988` | `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `here` | function | `src/page_view.c:2040` | `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3...` |
| `id` | function | `src/page_view.c:1289` | `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);` |
| `ignored` | function | `src/page_view.c:671` | `* source is ignored (fail-visible: never invisible text from half a      * pattern). A real text-...` |
| `in_boilerplate_subtree` | function | `src/page_view.c:5123` | `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` |
| `in_closed_details_subtree` | function | `src/page_view.c:5138` | `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` |
| `in_flow_table_cell` | function | `src/page_view.c:4998` | `static int in_flow_table_cell(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,            ...` |
| `in_hidden_subtree` | function | `src/page_view.c:5099` | `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,                ...` |
| `in_mixed_line` | function | `src/page_view.c:2906` | `static int in_mixed_line(const lxb_dom_node_t *p, const css_sheet *sheet,                        ...` |
| `in_skipped_subtree` | function | `src/page_view.c:1192` | `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,               ...` |
| `inherited_text_color` | function | `src/page_view.c:2694` | `static int inherited_text_color(const lxb_dom_node_t *node, const css_sheet *sheet,              ...` |
| `inside` | function | `src/page_view.c:5410` | `* page inside (the top one collapses with the first child's margin), so a * margin-only body stays box-less. */...` |
| `is_block_like` | function | `src/page_view.c:1021` | `static int is_block_like(lxb_tag_id_t t, css_display display)` |
| `is_block_like_style` | function | `src/page_view.c:1060` | `static int is_block_like_style(lxb_tag_id_t t, const css_style *cs)` |
| `is_block_tag` | function | `src/page_view.c:996` | `static int is_block_tag(lxb_tag_id_t t)` |
| `is_bold_tag` | function | `src/page_view.c:2856` | `static int is_bold_tag(lxb_tag_id_t t)` |
| `is_inline_level_style` | function | `src/page_view.c:2898` | `static int is_inline_level_style(lxb_tag_id_t t, const css_style *cs)` |
| `is_italic_tag` | function | `src/page_view.c:2861` | `static int is_italic_tag(lxb_tag_id_t t)` |
| `is_layout_container` | function | `src/page_view.c:3061` | `static int is_layout_container(const lxb_dom_node_t *el, const css_style *cs,                    ...` |
| `is_plain_wrapper` | function | `src/page_view.c:3263` | `static int is_plain_wrapper(const lxb_dom_node_t *c, const css_style *cs)` |
| `is_skipped_tag` | function | `src/page_view.c:1163` | `static int is_skipped_tag(lxb_tag_id_t t)` |
| `it` | function | `src/page_view.c:1386` | `* it (they inherit in CSS). list_style drives the <li> marker (structural);` |
| `item_ordinal` | function | `src/page_view.c:1357` | `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)` |
| `item_sizes_itself` | function | `src/page_view.c:3116` | `static int item_sizes_itself(const lxb_dom_node_t *el, const css_style *cs,                      ...` |
| `li_is_list_item` | function | `src/page_view.c:3132` | `static int li_is_list_item(const lxb_dom_node_t *li, const css_sheet *sheet,                     ...` |
| `li_ordinal` | function | `src/page_view.c:4736` | `static int li_ordinal(const lxb_dom_node_t *li)` |
| `line` | function | `src/page_view.c:6851` | `* to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);` |
| `links` | function | `src/page_view.c:4965` | `* its links (the Hacker News case: every story link lives inside a <td>), so the  * caller flows ...` |
| `list_marker` | function | `src/page_view.c:4787` | `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,                   ...` |
| `margins` | function | `src/page_view.c:3730` | `* margins (boxdef_from_style) and the painter applies them when                          * it ope...` |
| `mb` | type_alias | `src/page_view.c:1369` | `typedef struct pv_box_info { int l, r, w, center, mt, mb;` |
| `media_has_source` | function | `src/page_view.c:3301` | `static int media_has_source(const lxb_dom_node_t *n)` |
| `nearest_cell` | function | `src/page_view.c:4912` | `static const lxb_dom_node_t *nearest_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,   ...` |
| `nearest_table` | function | `src/page_view.c:4846` | `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,  ...` |
| `next_skip` | function | `src/page_view.c:4936` | `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)` |
| `node_next` | function | `src/page_view.c:986` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `node_table_role` | function | `src/page_view.c:4828` | `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `node_tag` | function | `src/page_view.c:1184` | `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)` |
| `none` | function | `src/page_view.c:2710` | `* inherited when it declares none (every hamburger bar and divider drawn as * a coloured empty box). A box cannot...` |
| `opens` | function | `src/page_view.c:3650` | `* painter applies it when the box opens (band/shared context) — seeding              * it onto ru...` |
| `outermost` | function | `src/page_view.c:3593` | `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);` |
| `paints` | function | `src/page_view.c:1104` | `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas  * vacías"). Comment a...` |
| `parent_is_table_internal` | function | `src/page_view.c:4885` | `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)` |
| `parse_dim` | function | `src/page_view.c:4187` | `static int parse_dim(const lxb_char_t *s, size_t len)` |
| `positions` | function | `src/page_view.c:140` | `* positions (cp == 0) keep the legacy '?' fallback. */ unsigned int cp = cp1252_to_ucs(c);` |
| `present` | function | `src/page_view.c:4204` | `* when no width descriptors are present (density-only or bare URLs). */ static void srcset_best_u...` |
| `pseudo_box_reg` | function | `src/page_view.c:2215` | `static int pseudo_box_reg(pv_box_reg *r, const lxb_dom_node_t *el, int which,                    ...` |
| `pseudo_generates_box` | function | `src/page_view.c:2236` | `static int pseudo_generates_box(const css_style *ps)` |
| `pseudo_is_block` | function | `src/page_view.c:2253` | `static int pseudo_is_block(const css_style *ps)` |
| `pseudo_is_oof` | function | `src/page_view.c:2249` | `static int pseudo_is_oof(const css_style *ps)` |
| `pseudo_key` | function | `src/page_view.c:2259` | `static const void *pseudo_key(const lxb_dom_node_t *el, int which)` |
| `pv_add_box_def` | function | `src/page_view.c:934` | `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)` |
| `pv_add_cont_def` | function | `src/page_view.c:912` | `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)` |
| `pv_after_pending` | struct | `src/page_view.c:1849` | `` |
| `pv_append` | function | `src/page_view.c:419` | `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,                     c...` |
| `pv_append_image` | function | `src/page_view.c:454` | `pv_status pv_append_image(pv_view *v, int heading, int block_break,                           con...` |
| `pv_append_input` | function | `src/page_view.c:484` | `pv_status pv_append_input(pv_view *v, int heading, int block_break,                           pv_...` |
| `pv_append_svg` | function | `src/page_view.c:560` | `pv_status pv_append_svg(pv_view *v, int heading, int block_break,                         const c...` |
| `pv_append_video` | function | `src/page_view.c:524` | `pv_status pv_append_video(pv_view *v, int heading, int block_break,                           con...` |
| `pv_at` | function | `src/page_view.c:969` | `const pv_run *pv_at(const pv_view *v, size_t i)` |
| `pv_box_at` | function | `src/page_view.c:978` | `const pv_box_def *pv_box_at(const pv_view *v, size_t i)` |
| `pv_box_count` | function | `src/page_view.c:974` | `size_t pv_box_count(const pv_view *v)` |
| `pv_box_info` | struct | `src/page_view.c:1369` | `` |
| `pv_box_reg` | struct | `src/page_view.c:1890` | `` |
| `pv_build` | function | `src/page_view.c:5158` | `pv_status pv_build(const hp_document *doc, pv_view **out)` |
| `pv_build_ex` | function | `src/page_view.c:5162` | `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)` |
| `pv_build_full` | function | `src/page_view.c:5166` | `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,                      ...` |
| `pv_build_styled` | function | `src/page_view.c:5300` | `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,                    ...` |
| `pv_cache_find` | function | `src/page_view.c:2376` | `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_cache_put` | function | `src/page_view.c:2396` | `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,                      ...` |
| `pv_cache_reindex` | function | `src/page_view.c:2330` | `static void pv_cache_reindex(pv_style_cache *c)` |
| `pv_cached_font_px` | function | `src/page_view.c:2391` | `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)` |
| `pv_computed` | struct | `src/page_view.c:7013` | `` |
| `pv_computed_free` | function | `src/page_view.c:7059` | `void pv_computed_free(pv_computed *pc)` |
| `pv_computed_get` | function | `src/page_view.c:7037` | `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st,                     do...` |
| `pv_computed_new` | function | `src/page_view.c:7018` | `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css,   ...` |
| `pv_cont_at` | function | `src/page_view.c:929` | `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)` |
| `pv_cont_count` | function | `src/page_view.c:925` | `size_t pv_cont_count(const pv_view *v)` |
| `pv_cont_info` | struct | `src/page_view.c:1267` | `` |
| `pv_container_reg` | struct | `src/page_view.c:1696` | `` |
| `pv_content_hidden` | function | `src/page_view.c:1390` | `int pv_content_hidden(int box_hidden, int run_visibility)` |
| `pv_count` | function | `src/page_view.c:965` | `size_t pv_count(const pv_view *v)` |
| `pv_css_drops` | function | `src/page_view.c:6984` | `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,                        const cha...` |
| `pv_def_h` | struct | `src/page_view.c:2287` | `` |
| `pv_element_has_before` | function | `src/page_view.c:3209` | `static int pv_element_has_before(lxb_dom_node_t *n, const css_sheet *sheet,                      ...` |
| `pv_flow_reg` | struct | `src/page_view.c:3324` | `` |
| `pv_flow_reg` | struct | `src/page_view.c:4814` | `` |
| `pv_free` | function | `src/page_view.c:947` | `void pv_free(pv_view *v)` |
| `pv_item_track` | struct | `src/page_view.c:1350` | `` |
| `pv_mauto_of` | function | `src/page_view.c:1498` | `static int pv_mauto_of(const css_style *cs)` |
| `pv_new` | function | `src/page_view.c:415` | `pv_view *pv_new(void)` |
| `pv_node_map` | struct | `src/page_view.c:348` | `` |
| `pv_node_map_build` | function | `src/page_view.c:406` | `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root)` |
| `pv_node_map_free` | function | `src/page_view.c:364` | `static void pv_node_map_free(pv_node_map *m)` |
| `pv_node_map_init` | function | `src/page_view.c:355` | `static int pv_node_map_init(pv_node_map *m)` |
| `pv_parent_element` | function | `src/page_view.c:2467` | `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)` |
| `pv_placeholder_color` | function | `src/page_view.c:896` | `int pv_placeholder_color(const css_style *ph)` |
| `pv_ptr_hash` | function | `src/page_view.c:2322` | `static size_t pv_ptr_hash(const void *p)` |
| `pv_ptrmap` | struct | `src/page_view.c:294` | `` |
| `pv_ptrmap_free` | function | `src/page_view.c:340` | `static void pv_ptrmap_free(pv_ptrmap *m)` |
| `pv_ptrmap_get` | function | `src/page_view.c:310` | `static int pv_ptrmap_get(const pv_ptrmap *m, const void *k, int *out)` |
| `pv_ptrmap_put` | function | `src/page_view.c:318` | `static void pv_ptrmap_put(pv_ptrmap *m, const void *k, int v)` |
| `pv_ptrmap_slot` | function | `src/page_view.c:300` | `static size_t pv_ptrmap_slot(const pv_ptrmap *m, const void *k)` |
| `pv_root_els` | struct | `src/page_view.c:4386` | `` |
| `pv_root_insets` | function | `src/page_view.c:5261` | `void pv_root_insets(const css_style *body, int out[4])` |
| `pv_set_bgcolor` | function | `src/page_view.c:606` | `void pv_set_bgcolor(pv_view *v, int bg_rgb)` |
| `pv_set_block_id` | function | `src/page_view.c:827` | `void pv_set_block_id(pv_view *v, int block_id)` |
| `pv_set_block_node` | function | `src/page_view.c:847` | `void pv_set_block_node(pv_view *v, dom_node_id id)` |
| `pv_set_box` | function | `src/page_view.c:786` | `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,                 int box_center, int ...` |
| `pv_set_box_maxw` | function | `src/page_view.c:809` | `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct)` |
| `pv_set_box_pct` | function | `src/page_view.c:798` | `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,                     ...` |
| `pv_set_br_line` | function | `src/page_view.c:852` | `void pv_set_br_line(pv_view *v, int br_line)` |
| `pv_set_color` | function | `src/page_view.c:601` | `void pv_set_color(pv_view *v, int fg_rgb)` |
| `pv_set_cont_box` | function | `src/page_view.c:726` | `void pv_set_cont_box(pv_view *v, int cont_box_id)` |
| `pv_set_cont_item` | function | `src/page_view.c:748` | `void pv_set_cont_item(pv_view *v, int cont_item)` |
| `pv_set_container` | function | `src/page_view.c:686` | `void pv_set_container(pv_view *v, int cont_id, int cont_display,                       int cont_g...` |
| `pv_set_emphasis` | function | `src/page_view.c:589` | `void pv_set_emphasis(pv_view *v, int bold, int italic)` |
| `pv_set_flex` | function | `src/page_view.c:730` | `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,                  int...` |
| `pv_set_flex_mauto` | function | `src/page_view.c:742` | `void pv_set_flex_mauto(pv_view *v, int mauto)` |
| `pv_set_float` | function | `src/page_view.c:764` | `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear,                 int ...` |
| `pv_set_float_w` | function | `src/page_view.c:753` | `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box,                     ...` |
| `pv_set_grad_text` | function | `src/page_view.c:622` | `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)` |
| `pv_set_grid` | function | `src/page_view.c:712` | `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)` |
| `pv_set_grid_area` | function | `src/page_view.c:705` | `void pv_set_grid_area(pv_view *v, int row_start, int col_start)` |
| `pv_set_grid_rows` | function | `src/page_view.c:722` | `void pv_set_grid_rows(pv_view *v, int grid_rows)` |
| `pv_set_indent` | function | `src/page_view.c:596` | `void pv_set_indent(pv_view *v, int indent)` |
| `pv_set_input_checked` | function | `src/page_view.c:857` | `void pv_set_input_checked(pv_view *v, int checked)` |
| `pv_set_input_placeholder` | function | `src/page_view.c:862` | `void pv_set_input_placeholder(pv_view *v, int ph_color)` |
| `pv_set_input_select_opts` | function | `src/page_view.c:904` | `void pv_set_input_select_opts(pv_view *v, const char *select_opts)` |
| `pv_set_justify_self` | function | `src/page_view.c:842` | `void pv_set_justify_self(pv_view *v, int justify_self)` |
| `pv_set_node_id` | function | `src/page_view.c:822` | `void pv_set_node_id(pv_view *v, dom_node_id node_id)` |
| `pv_set_oof` | function | `src/page_view.c:837` | `void pv_set_oof(pv_view *v, int oof)` |
| `pv_set_own_box` | function | `src/page_view.c:832` | `void pv_set_own_box(pv_view *v, int box_id)` |
| `pv_set_row_span` | function | `src/page_view.c:701` | `void pv_set_row_span(pv_view *v, int row_span)` |
| `pv_set_text_ext` | function | `src/page_view.c:630` | `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)` |
| `pv_set_text_style` | function | `src/page_view.c:611` | `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,                 ...` |
| `pv_set_ua_tag` | function | `src/page_view.c:816` | `void pv_set_ua_tag(pv_view *v, int ua_tag)` |
| `pv_style_cache` | struct | `src/page_view.c:2294` | `` |
| `pv_style_cache_free` | function | `src/page_view.c:2360` | `static void pv_style_cache_free(pv_style_cache *c)` |
| `pv_style_cache_init` | function | `src/page_view.c:2340` | `static int pv_style_cache_init(pv_style_cache *c)` |
| `pv_svg_append_root_attrs` | function | `src/page_view.c:867` | `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs,                ...` |
| `pv_text_ext_merge` | function | `src/page_view.c:1422` | `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)` |
| `pv_text_ext_reset` | function | `src/page_view.c:1396` | `void pv_text_ext_reset(pv_text_ext *e)` |
| `pv_var_node` | struct | `src/page_view.c:2278` | `` |
| `pv_var_push` | function | `src/page_view.c:2446` | `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,                       ...` |
| `px` | function | `src/page_view.c:5895` | `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */                 if (iw <...` |
| `resolve_context` | function | `src/page_view.c:3329` | `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,                 ...` |
| `resolves` | function | `src/page_view.c:1050` | `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close  * button/tooltip w...` |
| `roman_marker` | function | `src/page_view.c:4762` | `static void roman_marker(int n, int upper, char *out, size_t cap)` |
| `run_init_common` | function | `src/page_view.c:165` | `static void run_init_common(pv_run *r)` |
| `serialize_subtree` | function | `src/page_view.c:4144` | `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)` |
| `size` | function | `src/page_view.c:2781` | `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */ static void app...` |
| `srcset_slot_width` | function | `src/page_view.c:4299` | `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,                               ...` |
| `string` | function | `src/page_view.c:4415` | `* Returns a heap string (caller frees) or NULL when neither carries a class —  * NULL simply mean...` |
| `subtree_has_own_text` | function | `src/page_view.c:3241` | `static int subtree_has_own_text(const lxb_dom_node_t *n, const lxb_dom_node_t *base,             ...` |
| `subtree_is_oof` | function | `src/page_view.c:2761` | `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,                      ...` |
| `sz_count` | function | `src/page_view.c:4122` | `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)` |
| `sz_fill` | struct | `src/page_view.c:4130` | `` |
| `sz_write` | function | `src/page_view.c:4136` | `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)` |
| `table` | function | `src/page_view.c:5007` | `* FLOW table (multi-link: walked so its links survive) do NOT suppress their  * content -- their ...` |
| `table_columns` | function | `src/page_view.c:5025` | `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)` |
| `trying` | function | `src/page_view.c:1900` | `* a real page passes without trying (slashdot's front page saturates it), and past  * it box_reg_...` |
| `ua_tag_of` | function | `src/page_view.c:1129` | `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)` |
| `under_unrendered` | function | `src/page_view.c:4527` | `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)` |
| `utf8_encode` | function | `src/page_view.c:104` | `static size_t utf8_encode(unsigned int cp, char *out)` |
| `utf8_sanitized_dup` | function | `src/page_view.c:117` | `static char *utf8_sanitized_dup(const char *s)` |
| `walk` | function | `src/page_view.c:3951` | `* far on this walk (they are all inside this element). */                          /* The innermo...` |
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
| `js_ident_ch` | function | `src/prefetch.c:207` | `static int js_ident_ch(char c)` |
| `js_skip_string` | function | `src/prefetch.c:219` | `static size_t js_skip_string(const char *s, size_t i, size_t n)` |
| `js_skip_ws` | function | `src/prefetch.c:212` | `static size_t js_skip_ws(const char *s, size_t i, size_t n)` |
| `js_take_spec` | function | `src/prefetch.c:226` | `static void js_take_spec(const char *s, size_t i, size_t n,                          char (*out)[...` |
| `lower` | function | `src/prefetch.c:35` | `static int lower(int c)` |
| `pf_find_importmap` | function | `src/prefetch.c:483` | `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n)` |
| `pf_follow_imports` | function | `src/prefetch.c:333` | `static void pf_follow_imports(pf_pool *p, const char *base, const char *body, size_t len)` |
| `pf_is_js` | function | `src/prefetch.c:311` | `static int pf_is_js(const char *url, const char *ctype)` |
| `pf_list_free` | function | `src/prefetch.c:196` | `void pf_list_free(pf_list *l)` |
| `pf_pool_add` | function | `src/prefetch.c:288` | `int pf_pool_add(pf_pool *p, const char *url)` |
| `pf_pool_finish` | function | `src/prefetch.c:540` | `void pf_pool_finish(pf_pool *p)` |
| `pf_pool_start` | function | `src/prefetch.c:387` | `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,                   pf_fetch_f...` |
| `pf_pool_start_page` | function | `src/prefetch.c:504` | `int pf_pool_start_page(pf_pool *p, const char *html, size_t len, const char *page_url,           ...` |
| `pf_pool_take` | function | `src/prefetch.c:444` | `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,                  char **body,...` |
| `pf_pooled_fetch` | function | `src/prefetch.c:561` | `int pf_pooled_fetch(void *vctx, const char *method, const char *url,                     const ch...` |
| `pf_scan` | function | `src/prefetch.c:133` | `int pf_scan(const char *html, size_t len, pf_list *out)` |
| `pf_scan_imports` | function | `src/prefetch.c:241` | `size_t pf_scan_imports(const char *js, size_t len, char (*out)[PF_SPEC_MAX], size_t cap)` |
| `pf_url_cb` | function | `src/prefetch.c:319` | `static int pf_url_cb(void *ctx, const char *base, const char *ref, char *out, size_t outsz)` |
| `pf_url_shaped` | function | `src/prefetch.c:324` | `static int pf_url_shaped(const char *sp)` |
| `pf_worker` | function | `src/prefetch.c:349` | `static void *pf_worker(void *arg)` |
| `pool_start` | function | `src/prefetch.c:394` | `static int pool_start(pf_pool *p, const char *const *urls, size_t nurls,                       pf...` |
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
| `url_valid` | function | `src/prefs.c:26` | `static int url_valid(const char *url)` |
| `PROFILE_KEYFILE_LEN` | macro | `src/profile.c:27` | `#define PROFILE_KEYFILE_LEN` |
| `_POSIX_C_SOURCE` | macro | `src/profile.c:11` | `#define _POSIX_C_SOURCE` |
| `join_path` | function | `src/profile.c:29` | `static int join_path(const profile_ctx *ctx, const char *name,                      char *out, si...` |
| `keyfile_create` | function | `src/profile.c:36` | `static profile_status keyfile_create(const char *dir, const char *path,                          ...` |
| `map_ds` | function | `src/profile.c:98` | `static profile_status map_ds(ds_status ds)` |
| `profile_close` | function | `src/profile.c:149` | `void profile_close(profile_ctx *ctx)` |
| `profile_load` | function | `src/profile.c:112` | `profile_status profile_load(const profile_ctx *ctx, prefs_state *out)` |
| `profile_open` | function | `src/profile.c:59` | `profile_status profile_open(profile_ctx *ctx, const char *dir)` |
| `profile_save` | function | `src/profile.c:133` | `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p)` |
| `place` | function | `src/render_doc.c:237` | `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never...` |
| `rd_at` | function | `src/render_doc.c:763` | `const rd_block *rd_at(const rd_doc *d, size_t i)` |
| `rd_block_heading_level` | function | `src/render_doc.c:800` | `int rd_block_heading_level(const rd_block *b)` |
| `rd_block_tag` | function | `src/render_doc.c:811` | `const char *rd_block_tag(const rd_block *b)` |
| `rd_box_at` | function | `src/render_doc.c:772` | `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)` |
| `rd_box_count` | function | `src/render_doc.c:768` | `size_t rd_box_count(const rd_doc *d)` |
| `rd_build` | function | `src/render_doc.c:269` | `rd_status rd_build(const pv_view *view, rdp_caps caps,                    const char *top_level_u...` |
| `rd_cont_at` | function | `src/render_doc.c:781` | `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)` |
| `rd_cont_count` | function | `src/render_doc.c:777` | `size_t rd_cont_count(const rd_doc *d)` |
| `rd_count` | function | `src/render_doc.c:759` | `size_t rd_count(const rd_doc *d)` |
| `rd_free` | function | `src/render_doc.c:742` | `void rd_free(rd_doc *d)` |
| `rd_image_fail_label` | function | `src/render_doc.c:877` | `const char *rd_image_fail_label(img_fail_reason reason)` |
| `rd_image_label` | function | `src/render_doc.c:866` | `const char *rd_image_label(rdp_img_decision d)` |
| `rd_input_invisible` | function | `src/render_doc.c:862` | `int rd_input_invisible(int input_type)` |
| `rd_input_label` | function | `src/render_doc.c:842` | `const char *rd_input_label(int input_type)` |
| `rd_kind_name` | function | `src/render_doc.c:786` | `const char *rd_kind_name(rd_kind k)` |
| `rd_push` | function | `src/render_doc.c:60` | `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,                  ...` |
| `rd_push_input` | function | `src/render_doc.c:211` | `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` |
| `resolve_image_decision` | function | `src/render_doc.c:247` | `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,         ...` |
| `unset` | function | `src/render_doc.c:677` | `* background paints as if unset (no border/box-shadow-style                  * "broken image" pla...` |
| `utf8_sanitized_dup` | function | `src/render_doc.c:28` | `static char *utf8_sanitized_dup(const char *s)` |
| `rdp_caps_safe` | function | `src/render_policy.c:17` | `rdp_caps rdp_caps_safe(void)` |
| `rdp_image_decision` | function | `src/render_policy.c:28` | `rdp_img_decision rdp_image_decision(rdp_caps caps,                                     const char...` |
| `rdp_images_warning` | function | `src/render_policy.c:74` | `const char *rdp_images_warning(void)` |
| `rdp_img_reason` | function | `src/render_policy.c:63` | `const char *rdp_img_reason(rdp_img_decision d)` |
| `rdp_is_tracking_pixel` | function | `src/render_policy.c:22` | `int rdp_is_tracking_pixel(int w, int h)` |
| `_POSIX_C_SOURCE` | macro | `src/renderer.c:7` | `#define _POSIX_C_SOURCE` |
| `child_render` | function | `src/renderer.c:25` | `static void child_render(int wfd, const char *html, size_t len)` |
| `rd_render_html` | function | `src/renderer.c:70` | `rd_status rd_render_html(const char *html, size_t len, rd_result *out)` |
| `rd_result_free` | function | `src/renderer.c:120` | `void rd_result_free(rd_result *out)` |
| `read_field` | function | `src/renderer.c:53` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `write_full` | function | `src/renderer.c:40` | `&& write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 \|\| write_full(wfd, title, tl) == 0) && write_full(wfd, &xl...` |
| `RP_MAX_HOST` | macro | `src/request_policy.c:17` | `#define RP_MAX_HOST` |
| `RP_MAX_LABELS` | macro | `src/request_policy.c:18` | `#define RP_MAX_LABELS` |
| `ci_starts_with` | function | `src/request_policy.c:26` | `static int ci_starts_with(const char *s, const char *prefix)` |
| `hdr_forbidden` | function | `src/request_policy.c:184` | `static int hdr_forbidden(const char *n, size_t len)` |
| `hdr_lower` | function | `src/request_policy.c:162` | `static int hdr_lower(int c)` |
| `hdr_name_has_prefix` | function | `src/request_policy.c:171` | `static int hdr_name_has_prefix(const char *a, size_t alen, const char *lit)` |
| `hdr_name_ieq` | function | `src/request_policy.c:164` | `static int hdr_name_ieq(const char *a, size_t alen, const char *lit)` |
| `hdr_token_char` | function | `src/request_policy.c:178` | `static int hdr_token_char(unsigned char c)` |
| `lower` | function | `src/request_policy.c:22` | `static char lower(char c)` |
| `psl_cmp` | function | `src/request_policy.c:36` | `static int psl_cmp(const void *key, const void *elem)` |
| `psl_in` | function | `src/request_policy.c:40` | `static int psl_in(const char *const *arr, size_t n, const char *key)` |
| `public_suffix_labels` | function | `src/request_policy.c:48` | `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)` |
| `rp_evaluate` | function | `src/request_policy.c:143` | `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)` |
| `rp_host_of` | function | `src/request_policy.c:76` | `int rp_host_of(const char *url, char *out, size_t out_size)` |
| `rp_same_site` | function | `src/request_policy.c:134` | `int rp_same_site(const char *top_level_url, const char *request_url)` |

Next: [SYMBOLS_p10.md](SYMBOLS_p10.md)
