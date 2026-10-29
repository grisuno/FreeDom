# Subsystem: src (page 7 of 10)
Previous: [KB_src_p6.md](KB_src_p6.md)

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

## src/page_view.c
- Doc: pv_ptrmap: A small open-addressed map pointer -> int: the per-element verdict on a generated box...
- Layer: presentation
- Language: c
- Symbols:
  - `pv_ptrmap` (struct, line 296)
  - `pv_node_map` (struct, line 350)
  - `pv_cont_info` (struct, line 1269)
  - `pv_item_track` (struct, line 1352)
  - `pv_box_info` (struct, line 1371)
  - `pv_container_reg` (struct, line 1714)
  - `pv_after_pending` (struct, line 1867)
  - `pv_box_reg` (struct, line 1908)
  - `pv_var_node` (struct, line 2296)
  - `pv_style_cache` (struct, line 2312)
  - `pv_flow_reg` (struct, line 3392)
  - `sz_fill` (struct, line 4198)
  - `pv_root_els` (struct, line 4469)
  - `form_rec` (struct, line 4535)
  - `form_table` (struct, line 4541)
  - `pv_flow_reg` (struct, line 4897)
  - `pv_computed` (struct, line 7127)
  - `pv_def_h` (struct, line 2305)
  - `cols` (type_alias, line 1269) `typedef struct pv_cont_info { int id, display, gap, justify, cols;`
  - `mb` (type_alias, line 1371) `typedef struct pv_box_info { int l, r, w, center, mt, mb;`
  - `chain` (type_alias, line 2296) `typedef struct pv_var_node { cvr_chain chain;`
  - `cp1252_to_ucs` (function, line 91) `static unsigned int cp1252_to_ucs(unsigned char c)`
  - `utf8_encode` (function, line 105) `static size_t utf8_encode(unsigned int cp, char *out)`
  - `utf8_sanitized_dup` (function, line 118) `static char *utf8_sanitized_dup(const char *s)`
  - `dup_n` (function, line 152) `static char *dup_n(const char *s, size_t n)`
  - `run_init_common` (function, line 166) `static void run_init_common(pv_run *r)`
  - `pv_ptrmap_slot` (function, line 302) `static size_t pv_ptrmap_slot(const pv_ptrmap *m, const void *k)`
  - `pv_ptrmap_get` (function, line 312) `static int pv_ptrmap_get(const pv_ptrmap *m, const void *k, int *out)`
  - `pv_ptrmap_put` (function, line 320) `static void pv_ptrmap_put(pv_ptrmap *m, const void *k, int v)`
  - `pv_ptrmap_free` (function, line 342) `static void pv_ptrmap_free(pv_ptrmap *m)`
  - `pv_node_map_init` (function, line 357) `static int pv_node_map_init(pv_node_map *m)`
  - `pv_node_map_free` (function, line 366) `static void pv_node_map_free(pv_node_map *m)`
  - `pv_node_map_build` (function, line 408) `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root)`
  - `pv_new` (function, line 417) `pv_view *pv_new(void)`
  - `pv_append` (function, line 421) `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    c...`
  - `pv_append_image` (function, line 456) `pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          con...`
  - `pv_append_input` (function, line 486) `pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_...`
  - `pv_append_video` (function, line 526) `pv_status pv_append_video(pv_view *v, int heading, int block_break,
                          con...`
  - `pv_append_svg` (function, line 562) `pv_status pv_append_svg(pv_view *v, int heading, int block_break,
                        const c...`
  - `pv_set_emphasis` (function, line 591) `void pv_set_emphasis(pv_view *v, int bold, int italic)`
  - `pv_set_indent` (function, line 598) `void pv_set_indent(pv_view *v, int indent)`
  - `pv_set_color` (function, line 603) `void pv_set_color(pv_view *v, int fg_rgb)`
  - `pv_set_bgcolor` (function, line 608) `void pv_set_bgcolor(pv_view *v, int bg_rgb)`
  - `pv_set_text_style` (function, line 613) `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,
                ...`
  - `pv_set_grad_text` (function, line 624) `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4)`
  - `pv_set_text_ext` (function, line 632) `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)`
  - `ignored` (function, line 673) `* source is ignored (fail-visible: never invisible text from half a
     * pattern). A real text-...`
  - `pv_set_container` (function, line 688) `void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_g...`
  - `pv_set_row_span` (function, line 703) `void pv_set_row_span(pv_view *v, int row_span)`
  - `pv_set_grid_area` (function, line 707) `void pv_set_grid_area(pv_view *v, int row_start, int col_start)`
  - `pv_set_grid` (function, line 714) `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)`
  - `pv_set_grid_rows` (function, line 724) `void pv_set_grid_rows(pv_view *v, int grid_rows)`
  - `pv_set_cont_box` (function, line 728) `void pv_set_cont_box(pv_view *v, int cont_box_id)`
  - `pv_set_flex` (function, line 732) `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                 int...`
  - `pv_set_flex_mauto` (function, line 744) `void pv_set_flex_mauto(pv_view *v, int mauto)`
  - `pv_set_cont_item` (function, line 750) `void pv_set_cont_item(pv_view *v, int cont_item)`
  - `pv_set_float_w` (function, line 755) `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box,
                    ...`
  - `pv_set_float` (function, line 766) `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear,
                int ...`
  - `pv_set_box` (function, line 788) `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                int box_center, int ...`
  - `pv_set_box_pct` (function, line 800) `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,
                    ...`
  - `pv_set_box_maxw` (function, line 811) `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct)`
  - `pv_set_ua_tag` (function, line 818) `void pv_set_ua_tag(pv_view *v, int ua_tag)`
  - `pv_set_node_id` (function, line 824) `void pv_set_node_id(pv_view *v, dom_node_id node_id)`
  - `pv_set_block_id` (function, line 829) `void pv_set_block_id(pv_view *v, int block_id)`
  - `pv_set_own_box` (function, line 834) `void pv_set_own_box(pv_view *v, int box_id)`
  - `pv_set_oof` (function, line 839) `void pv_set_oof(pv_view *v, int oof)`
  - `pv_set_justify_self` (function, line 844) `void pv_set_justify_self(pv_view *v, int justify_self)`
  - `pv_set_block_node` (function, line 849) `void pv_set_block_node(pv_view *v, dom_node_id id)`
  - `pv_set_br_line` (function, line 854) `void pv_set_br_line(pv_view *v, int br_line)`
  - `pv_set_input_checked` (function, line 859) `void pv_set_input_checked(pv_view *v, int checked)`
  - `pv_set_input_placeholder` (function, line 864) `void pv_set_input_placeholder(pv_view *v, int ph_color)`
  - `pv_svg_append_root_attrs` (function, line 869) `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs,
               ...`
  - `pv_placeholder_color` (function, line 898) `int pv_placeholder_color(const css_style *ph)`
  - `pv_set_input_select_opts` (function, line 906) `void pv_set_input_select_opts(pv_view *v, const char *select_opts)`
  - `pv_add_cont_def` (function, line 914) `pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d)`
  - `pv_cont_count` (function, line 927) `size_t pv_cont_count(const pv_view *v)`
  - `pv_cont_at` (function, line 931) `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i)`
  - `pv_add_box_def` (function, line 936) `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)`
  - `pv_free` (function, line 949) `void pv_free(pv_view *v)`
  - `pv_count` (function, line 967) `size_t pv_count(const pv_view *v)`
  - `pv_at` (function, line 971) `const pv_run *pv_at(const pv_view *v, size_t i)`
  - `pv_box_count` (function, line 976) `size_t pv_box_count(const pv_view *v)`
  - `pv_box_at` (function, line 980) `const pv_box_def *pv_box_at(const pv_view *v, size_t i)`
  - `node_next` (function, line 988) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)`
  - `is_block_tag` (function, line 998) `static int is_block_tag(lxb_tag_id_t t)`
  - `is_block_like` (function, line 1023) `static int is_block_like(lxb_tag_id_t t, css_display display)`
  - `resolves` (function, line 1052) `* box_tree already resolves (R4/R8) had nothing to place -- every badge/close
 * button/tooltip w...`
  - `is_block_like_style` (function, line 1062) `static int is_block_like_style(lxb_tag_id_t t, const css_style *cs)`
  - `generates_box` (function, line 1074) `static int generates_box(lxb_tag_id_t t, css_display display)`
  - `generates_box_style` (function, line 1086) `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)`
  - `causes_block_break` (function, line 1093) `static int causes_block_break(lxb_tag_id_t t, css_display display)`
  - `paints` (function, line 1106) `* for it so its box reserves space and paints (spec/page_view.md §4 "Cajas
 * vacías"). Comment a...`
  - `ua_tag_of` (function, line 1131) `static bx_ua_tag ua_tag_of(lxb_tag_id_t t)`
  - `heading_level` (function, line 1153) `static int heading_level(lxb_tag_id_t t)`
  - `is_skipped_tag` (function, line 1165) `static int is_skipped_tag(lxb_tag_id_t t)`
  - `node_tag` (function, line 1186) `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)`
  - `in_skipped_subtree` (function, line 1194) `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
              ...`
  - `font_color_attr` (function, line 1231) `static int font_color_attr(lxb_dom_element_t *el)`
  - `bgcolor_attr` (function, line 1237) `static int bgcolor_attr(lxb_dom_element_t *el)`
  - `item_ordinal` (function, line 1359) `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)`
  - `pv_content_hidden` (function, line 1392) `int pv_content_hidden(int box_hidden, int run_visibility)`
  - `pv_text_ext_reset` (function, line 1398) `void pv_text_ext_reset(pv_text_ext *e)`
  - `pv_text_ext_merge` (function, line 1424) `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)`
  - `css_has_hbox` (function, line 1486) `static int css_has_hbox(const css_style *cs)`
  - `pv_mauto_of` (function, line 1500) `static int pv_mauto_of(const css_style *cs)`
  - `css_hbox_resolve` (function, line 1507) `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)`
  - `css_has_position` (function, line 1560) `static int css_has_position(const css_style *cs)`
  - `border_side_cleared` (function, line 1567) `static int border_side_cleared(int width, int style)`
  - `pv_control_frame_cleared` (function, line 1573) `static int pv_control_frame_cleared(const css_style *cs)`
  - `css_has_boxdeco` (function, line 1581) `static int css_has_boxdeco(const css_style *cs)`
  - `cont_def_reset` (function, line 1725) `static void cont_def_reset(pv_cont_def *d)`
  - `container_id` (function, line 1744) `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)`
  - `annotate_flow_run` (function, line 1832) `static void annotate_flow_run(pv_view *v, pv_container_reg *reg, pv_item_track *items,
          ...`
  - `after_pending_emit` (function, line 1880) `static pv_status after_pending_emit(pv_view *v, pv_container_reg *reg, pv_item_track *items,
    ...`
  - `trying` (function, line 1918) `* a real page passes without trying (slashdot's front page saturates it), and past
 * it box_reg_...`
  - `box_reg_free` (function, line 1947) `static void box_reg_free(pv_box_reg *r)`
  - `boxdef_from_style` (function, line 1956) `static void boxdef_from_style(pv_box_def *d, const css_style *cs)`
  - `box_reg_id` (function, line 2204) `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,
           ...`
  - `pseudo_box_reg` (function, line 2233) `static int pseudo_box_reg(pv_box_reg *r, const lxb_dom_node_t *el, int which,
                   ...`
  - `pseudo_generates_box` (function, line 2254) `static int pseudo_generates_box(const css_style *ps)`
  - `pseudo_is_oof` (function, line 2267) `static int pseudo_is_oof(const css_style *ps)`
  - `pseudo_is_block` (function, line 2271) `static int pseudo_is_block(const css_style *ps)`
  - `pseudo_key` (function, line 2277) `static const void *pseudo_key(const lxb_dom_node_t *el, int which)`
  - `pv_ptr_hash` (function, line 2344) `static size_t pv_ptr_hash(const void *p)`
  - `pv_cache_reindex` (function, line 2352) `static void pv_cache_reindex(pv_style_cache *c)`
  - `pv_style_cache_free` (function, line 2388) `static void pv_style_cache_free(pv_style_cache *c)`
  - `pv_style_cache_reserve` (function, line 2407) `static void pv_style_cache_reserve(pv_style_cache *c, size_t n)`
  - `pv_cache_find` (function, line 2432) `static long pv_cache_find(const pv_style_cache *cache, const lxb_dom_node_t *node)`
  - `pv_cached_font_px` (function, line 2447) `static double pv_cached_font_px(const pv_style_cache *cache, const lxb_dom_node_t *node)`
  - `pv_cache_put` (function, line 2452) `static void pv_cache_put(pv_style_cache *cache, const lxb_dom_node_t *node,
                     ...`
  - `pv_var_push` (function, line 2502) `static const cvr_chain *pv_var_push(pv_style_cache *cache, cvr_table *own,
                      ...`
  - `pv_parent_element` (function, line 2523) `static lxb_dom_element_t *pv_parent_element(lxb_dom_element_t *el)`
  - `cached_element_style_ref` (function, line 2600) `static const css_style *cached_element_style_ref(lxb_dom_element_t *el, const css_sheet *sheet,
 ...`
  - `cached_element_style` (function, line 2683) `static css_style cached_element_style(lxb_dom_element_t *el, const css_sheet *sheet,
            ...`
  - `inherited_text_color` (function, line 2750) `static int inherited_text_color(const lxb_dom_node_t *node, const css_sheet *sheet,
             ...`
  - `box_reg_id_ex` (function, line 2761) `static int box_reg_id_ex(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,
        ...`
  - `cached_pseudo_style` (function, line 2799) `static css_style cached_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet,
             ...`
  - `subtree_is_oof` (function, line 2817) `static int subtree_is_oof(const lxb_dom_node_t *el, const css_sheet *sheet,
                     ...`
  - `size` (function, line 2837) `* viewBox natural size (~100px) instead of the CSS 40px, blowing up flex rows. */
static void app...`
  - `css_replaced_h_fixed` (function, line 2846) `static int css_replaced_h_fixed(lxb_dom_element_t *el, const css_sheet *sheet,
                  ...`
  - `builder` (function, line 2864) `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box
 * (the ...`
  - `css_to_fx_justify` (function, line 2893) `static int css_to_fx_justify(css_justify j)`
  - `is_bold_tag` (function, line 2912) `static int is_bold_tag(lxb_tag_id_t t)`
  - `is_italic_tag` (function, line 2917) `static int is_italic_tag(lxb_tag_id_t t)`
  - `is_inline_level_style` (function, line 2954) `static int is_inline_level_style(lxb_tag_id_t t, const css_style *cs)`
  - `in_mixed_line` (function, line 2962) `static int in_mixed_line(const lxb_dom_node_t *p, const css_sheet *sheet,
                       ...`
  - `children_all_inline_block` (function, line 2978) `static int children_all_inline_block(const lxb_dom_node_t *p, const css_sheet *sheet,
           ...`
  - `col_has_free_space` (function, line 3003) `static int col_has_free_space(const css_style *cs)`
  - `flex_column_flows_as_block` (function, line 3017) `static int flex_column_flows_as_block(const lxb_dom_node_t *el, const css_style *cs,
            ...`
  - `flex_column_flows_as_block_uncached` (function, line 3026) `static int flex_column_flows_as_block_uncached(const lxb_dom_node_t *el, const css_style *cs,
   ...`
  - `fold_column_gap` (function, line 3094) `static void fold_column_gap(const lxb_dom_node_t *el, css_style *cs,
                            ...`
  - `column_gap_candidate` (function, line 3119) `static int column_gap_candidate(const lxb_dom_node_t *el, const css_sheet *sheet,
               ...`
  - `is_layout_container` (function, line 3129) `static int is_layout_container(const lxb_dom_node_t *el, const css_style *cs,
                   ...`
  - `css_has_hmargin` (function, line 3155) `static int css_has_hmargin(const css_style *cs)`
  - `item_sizes_itself` (function, line 3184) `static int item_sizes_itself(const lxb_dom_node_t *el, const css_style *cs,
                     ...`
  - `li_is_list_item` (function, line 3200) `static int li_is_list_item(const lxb_dom_node_t *li, const css_sheet *sheet,
                    ...`
  - `pv_element_has_before` (function, line 3277) `static int pv_element_has_before(lxb_dom_node_t *n, const css_sheet *sheet,
                     ...`
  - `subtree_has_own_text` (function, line 3309) `static int subtree_has_own_text(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
            ...`
  - `is_plain_wrapper` (function, line 3331) `static int is_plain_wrapper(const lxb_dom_node_t *c, const css_style *cs)`
  - `element_is_content_leaf_d` (function, line 3343) `static int element_is_content_leaf_d(const lxb_dom_node_t *n, const css_sheet *sheet,
           ...`
  - `media_has_source` (function, line 3369) `static int media_has_source(const lxb_dom_node_t *n)`
  - `element_is_content_leaf` (function, line 3383) `static int element_is_content_leaf(const lxb_dom_node_t *n, const css_sheet *sheet,
             ...`
  - `resolve_context` (function, line 3397) `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                ...`
  - `opens` (function, line 3718) `* painter applies it when the box opens (band/shared context) — seeding
             * it onto ru...`
  - `css_inline_boxdeco` (function, line 3758) `css_inline_boxdeco(cs) &&
                           !is_layout_item(p, sheet, style_cache))`
  - `margins` (function, line 3798) `* margins (boxdef_from_style) and the painter applies them when
                         * it ope...`
  - `container` (function, line 3921) `* membership in this container (and none in any container further out,
                 * since i...`
  - `walk` (function, line 4019) `* far on this walk (they are all inside this element). */

                        /* The innermo...`
  - `float` (function, line 4144) `* genuinely nested float (oid != id) takes the deferred-column path. */
    if (cont->float_oid =...`
  - `sz_count` (function, line 4190) `static lxb_status_t sz_count(const lxb_char_t *data, size_t len, void *ctx)`
  - `sz_write` (function, line 4204) `static lxb_status_t sz_write(const lxb_char_t *data, size_t len, void *ctx)`
  - `serialize_subtree` (function, line 4212) `static char *serialize_subtree(const lxb_dom_node_t *n, size_t *out_len)`
  - `collapse_ws` (function, line 4231) `static char *collapse_ws(const char *s, size_t n)`
  - `pv_frame_marked` (function, line 4261) `static int pv_frame_marked(const lxb_dom_node_t *n)`
  - `parse_dim` (function, line 4270) `static int parse_dim(const lxb_char_t *s, size_t len)`
  - `present` (function, line 4287) `* when no width descriptors are present (density-only or bare URLs). */
static void srcset_best_u...`
  - `srcset_slot_width` (function, line 4382) `static int srcset_slot_width(const lxb_char_t *sizes, size_t slen,
                              ...`
  - `dimensions` (function, line 4428) `* viewport dimensions (data: inline detection, <picture> <source> scanning). */
static void srcse...`
  - `find_body` (function, line 4460) `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)`
  - `find_root_els` (function, line 4473) `static pv_root_els find_root_els(lxb_dom_node_t *root)`
  - `attributes` (function, line 4487) `* carries those attributes (spec/css.md, "Root matcher"). */
static int root_els_match(void *ctx,...`
  - `string` (function, line 4498) `* Returns a heap string (caller frees) or NULL when neither carries a class —
 * NULL simply mean...`
  - `forms_free` (function, line 4546) `static void forms_free(form_table *ft)`
  - `ascii_ieq` (function, line 4553) `static int ascii_ieq(const char *s, const char *lit)`
  - `attr_dup` (function, line 4565) `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)`
  - `forms_add` (function, line 4574) `static int forms_add(form_table *ft, const lxb_dom_node_t *node)`
  - `form_for` (function, line 4594) `static int form_for(const form_table *ft, const lxb_dom_node_t *n,
                    const lxb_...`
  - `under_unrendered` (function, line 4610) `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)`
  - `collect_text` (function, line 4623) `static char *collect_text(const lxb_dom_node_t *el)`
  - `classify_input` (function, line 4647) `static pv_input_type classify_input(const char *type)`
  - `li_ordinal` (function, line 4819) `static int li_ordinal(const lxb_dom_node_t *li)`
  - `roman_marker` (function, line 4845) `static void roman_marker(int n, int upper, char *out, size_t cap)`
  - `list_marker` (function, line 4870) `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,
                  ...`
  - `node_table_role` (function, line 4911) `static bx_table_role node_table_role(const lxb_dom_node_t *n, const pv_flow_reg *fr)`
  - `nearest_table` (function, line 4929) `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
 ...`
  - `parent_is_table_internal` (function, line 4968) `static int parent_is_table_internal(const lxb_dom_node_t *n, const pv_flow_reg *fr)`
  - `nearest_cell` (function, line 4995) `static const lxb_dom_node_t *nearest_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
  ...`
  - `cell_has_nested_table` (function, line 5010) `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)`
  - `next_skip` (function, line 5019) `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)`
  - `cell_anchors` (function, line 5030) `static const lxb_dom_node_t *cell_anchors(const lxb_dom_node_t *cell, int *count)`
  - `links` (function, line 5048) `* its links (the Hacker News case: every story link lives inside a <td>), so the
 * caller flows ...`
  - `flow_table` (function, line 5069) `static int flow_table(pv_flow_reg *fr, const lxb_dom_node_t *table)`
  - `in_flow_table_cell` (function, line 5081) `static int in_flow_table_cell(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,
           ...`
  - `table` (function, line 5090) `* FLOW table (multi-link: walked so its links survive) do NOT suppress their
 * content -- their ...`
  - `table_columns` (function, line 5108) `static int table_columns(const lxb_dom_node_t *table, const pv_flow_reg *fr)`
  - `in_hidden_subtree` (function, line 5182) `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
               ...`
  - `in_boilerplate_subtree` (function, line 5209) `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)`
  - `in_closed_details_subtree` (function, line 5224) `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)`
  - `pv_build` (function, line 5244) `pv_status pv_build(const hp_document *doc, pv_view **out)`
  - `pv_build_ex` (function, line 5248) `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)`
  - `pv_build_full` (function, line 5252) `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                     ...`
  - `annotate_replaced_run` (function, line 5274) `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,
                            ...`
  - `pv_root_insets` (function, line 5349) `void pv_root_insets(const css_style *body, int out[4])`
  - `collect_page_css` (function, line 5359) `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,
                     ...`
  - `pv_build_styled` (function, line 5388) `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                   ...`
  - `px` (function, line 5992) `* the viewBox extent for intrinsic px (slashdot social-icon balloon). */
                if (iw <...`
  - `engine` (function, line 6956) `* layout engine (contiguous item gather) drops every cell onto its own row and
         * a 2-col...`
  - `pv_css_drops` (function, line 7098) `pv_status pv_css_drops(const hp_document *doc, int prefers_dark,
                       const cha...`
  - `pv_computed_new` (function, line 7132) `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css,
  ...`
  - `pv_computed_get` (function, line 7151) `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st,
                    do...`
  - `pv_computed_free` (function, line 7173) `void pv_computed_free(pv_computed *pc)`
  - `positions` (function, line 141) `* positions (cp == 0) keep the legacy '?' fallback. */ unsigned int cp = cp1252_to_ucs(c);`
  - `content` (function, line 1191) `* a <noscript> ancestor also suppresses content (the script would run, so the * fallback is hidden);`
  - `address` (function, line 1259) `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <=...`
  - `child` (function, line 1267) `* child (NULL = anonymous item: text directly inside the container);`
  - `id` (function, line 1291) `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);`
  - `it` (function, line 1388) `* it (they inherit in CSS). list_style drives the <li> marker (structural);`
  - `here` (function, line 2058) `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3...`
  - `glyphs` (function, line 2106) `* glyphs (the runs carry it as their fill source);`
  - `col_free_share` (function, line 2744) `static int col_free_share(const lxb_dom_node_t *el, const css_style *cs, const css_sheet *sheet, pv_style_cache...`
  - `none` (function, line 2766) `* inherited when it declares none (every hamburger bar and divider drawn as * a coloured empty box). A box cannot...`
  - `outermost` (function, line 3661) `* nearest IS the outermost (single-level float, old path). */ cont->float_oid = container_id(float_reg, p);`
  - `inside` (function, line 5505) `* page inside (the top one collapses with the first child's margin), so a * margin-only body stays box-less. */...`
  - `control` (function, line 5814) `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);`
  - `band` (function, line 6058) `* run: without its float annotation it cut the band (the icon row of a * `float:right` social list became one float...`
  - `height` (function, line 6085) `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
  - `block_id` (function, line 6243) `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it...`
  - `URL` (function, line 6384) `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);`
  - `block` (function, line 6672) `* block (Gecko): it never resolves as its own block here. */ int opens_line = block != n && (pending_break || block...`
  - `flow` (function, line 6850) `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through...`
  - `line` (function, line 6965) `* to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);`
  - `_POSIX_C_SOURCE` (macro, line 10) `#define _POSIX_C_SOURCE`
  - `PV_MAX_DIM` (macro, line 53) `#define PV_MAX_DIM`
  - `PV_FONT_REL_MIN` (macro, line 58) `#define PV_FONT_REL_MIN`
  - `PV_FONT_REL_MAX` (macro, line 59) `#define PV_FONT_REL_MAX`
  - `PV_FONT_CHAIN_MAX` (macro, line 65) `#define PV_FONT_CHAIN_MAX`
  - `PV_FONT_PCT_MIN` (macro, line 66) `#define PV_FONT_PCT_MIN`
  - `PV_FONT_PCT_MAX` (macro, line 67) `#define PV_FONT_PCT_MAX`
  - `PV_NODE_MAP_INIT_CAP` (macro, line 348) `#define PV_NODE_MAP_INIT_CAP`
  - `PV_COLOR_TOKEN_MAX` (macro, line 1209) `#define PV_COLOR_TOKEN_MAX`
  - `PV_MAX_CONTAINERS` (macro, line 1247) `#define PV_MAX_CONTAINERS`
  - `PV_MAX_GRID_COLS` (macro, line 1248) `#define PV_MAX_GRID_COLS`
  - `PV_MAX_BOXES` (macro, line 1256) `#define PV_MAX_BOXES`
  - `PV_STYLE_RETIRE_MAX` (macro, line 2310) `#define PV_STYLE_RETIRE_MAX`
  - `PV_STYLE_RESERVE_MAX` (macro, line 2364) `#define PV_STYLE_RESERVE_MAX`
  - `PV_MAX_INLINE_ROW_ITEMS` (macro, line 2950) `#define PV_MAX_INLINE_ROW_ITEMS`
  - `PV_TEXTLESS_DEPTH_MAX` (macro, line 3292) `#define PV_TEXTLESS_DEPTH_MAX`
  - `PV_FRAME_DEF_W` (macro, line 4257) `#define PV_FRAME_DEF_W`
  - `PV_FRAME_DEF_H` (macro, line 4258) `#define PV_FRAME_DEF_H`
  - `PV_FRAME_URL_MAX` (macro, line 4259) `#define PV_FRAME_URL_MAX`
  - `PV_MAX_STYLE_BYTES` (macro, line 5135) `#define PV_MAX_STYLE_BYTES`
- Depends on: `include/box_style.h`, `include/box_tree.h`, `include/css.h`, `include/css_chain.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_vars.h`, `include/dom.h`, `include/flex_layout.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/page_view.h`, `include/svg_render.h`, `include/util.h`

## src/pdf_export.c
- Layer: utility
- Language: c
- Symbols:
  - `pe_safe_basename` (function, line 25) `pe_status pe_safe_basename(const char *title, char *out, size_t outsz)`
  - `pe_build_path_ext` (function, line 66) `pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,
                ...`
  - `pe_build_path` (function, line 91) `pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz)`
  - `pe_paginate` (function, line 95) `size_t pe_paginate(const double *tops, const double *heights, size_t n,
                   double...`
- Depends on: `include/pdf_export.h`

## src/perf_trace.c
- Layer: utility
- Language: c
- Symbols:
  - `pt_init` (function, line 16) `void pt_init(pt_trace *t)`
  - `pt_elapsed_us` (function, line 21) `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us)`
  - `pt_record` (function, line 26) `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us)`
  - `pt_count` (function, line 35) `size_t pt_count(const pt_trace *t, pt_stage stage)`
  - `pt_last_us` (function, line 40) `uint64_t pt_last_us(const pt_trace *t, pt_stage stage)`
  - `pt_min_us` (function, line 49) `uint64_t pt_min_us(const pt_trace *t, pt_stage stage)`
  - `pt_max_us` (function, line 60) `uint64_t pt_max_us(const pt_trace *t, pt_stage stage)`
  - `cmp_u64` (function, line 71) `static int cmp_u64(const void *a, const void *b)`
  - `pt_median_us` (function, line 79) `uint64_t pt_median_us(const pt_trace *t, pt_stage stage)`
  - `pt_stage_name` (function, line 89) `const char *pt_stage_name(pt_stage stage)`
  - `pt_format` (function, line 109) `size_t pt_format(const pt_trace *t, char *buf, size_t cap)`
  - `PT_LINE_CAP` (macro, line 107) `#define PT_LINE_CAP`
- Depends on: `include/perf_trace.h`

## src/pq_seal.c
- Doc: derive_key: pqs_status pqs_import(const uint8_t *der, size_t len, pqs_keys **out) { if (der ==...
- Layer: utility
- Language: c
- Symbols:
  - `pqs_keys` (struct, line 19)
  - `pqs_buf_free` (function, line 23) `void pqs_buf_free(uint8_t *buf, size_t len)`
  - `pqs_free` (function, line 29) `void pqs_free(pqs_keys *k)`
  - `keys_wrap` (function, line 35) `static pqs_keys *keys_wrap(EVP_PKEY *pkey)`
  - `pqs_generate` (function, line 42) `pqs_status pqs_generate(pqs_keys **out)`
  - `pqs_export` (function, line 55) `pqs_status pqs_export(const pqs_keys *k, uint8_t **der, size_t *len)`
  - `pqs_import` (function, line 68) `pqs_status pqs_import(const uint8_t *der, size_t len, pqs_keys **out)`
  - `derive_key` (function, line 81) `static int derive_key(const uint8_t ss[PQS_SS_LEN], const uint8_t wrap[LS_KEY_LEN],
             ...`
  - `pqs_seal` (function, line 106) `pqs_status pqs_seal(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],
                    const ...`
  - `pqs_open` (function, line 147) `pqs_status pqs_open(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],
                    const ...`
  - `PQS_SS_LEN` (macro, line 17) `#define PQS_SS_LEN`
- Depends on: `include/pq_seal.h`


Next: [KB_src_p8.md](KB_src_p8.md)
