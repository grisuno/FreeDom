# Symbols (page 12 of 19)
Previous: [SYMBOLS_p11.md](SYMBOLS_p11.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `svp_draw` | function | `src/svg_paint.c:139` | `void svp_draw(cairo_t *cr, const sv_image *img,               double x, double y, double w, doubl...` |
| `svp_draw_ex` | function | `src/svg_paint.c:144` | `void svp_draw_ex(cairo_t *cr, const sv_image *img,                  double x, double y, double w,...` |
| `svp_draw_text` | function | `src/svg_paint.c:126` | `static void svp_draw_text(cairo_t *cr, const sv_shape *sh, int current_rgb)` |
| `svp_rect_path` | function | `src/svg_paint.c:38` | `static void svp_rect_path(cairo_t *cr, const sv_shape *sh)` |
| `svp_shape_path` | function | `src/svg_paint.c:73` | `static void svp_shape_path(cairo_t *cr, const sv_image *img, const sv_shape *sh)` |
| `sr_rasterize` | function | `src/svg_raster.c:50` | `img_status sr_rasterize(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `sr_skip_past` | function | `src/svg_raster.c:18` | `static size_t sr_skip_past(const uint8_t *b, size_t i, size_t n, const char *end)` |
| `sr_sniff` | function | `src/svg_raster.c:25` | `int sr_sniff(const uint8_t *bytes, size_t len)` |
| `sr_ws` | function | `src/svg_raster.c:14` | `static int sr_ws(uint8_t c)` |
| `SV_MAX_ATTRS` | macro | `src/svg_render.c:96` | `#define SV_MAX_ATTRS` |
| `point` | function | `src/svg_render.c:567` | `* current point (SVG 8.3.6). */ int had = (prev == 'C' \|\| prev == 'c' \|\| prev == 'S' \|\| prev == 's');` |
| `stroke` | type_alias | `src/svg_render.c:151` | `typedef struct sv_ctx { int fill, stroke;` |
| `sv_apply_prop` | function | `src/svg_render.c:260` | `static void sv_apply_prop(sv_ctx *ctx, const char *nm, size_t nl,                           const...` |
| `sv_arc_to_cubics` | function | `src/svg_render.c:399` | `static int sv_arc_to_cubics(sv_image *im, sv_shape *sh,                             double x0, do...` |
| `sv_attr` | struct | `src/svg_render.c:91` | `` |
| `sv_attr_get` | function | `src/svg_render.c:99` | `static const char *sv_attr_get(const sv_attr *at, size_t nat, const char *name, size_t *len)` |
| `sv_attr_num` | function | `src/svg_render.c:108` | `static double sv_attr_num(const sv_attr *at, size_t nat, const char *name, double dflt)` |
| `sv_collect_text` | function | `src/svg_render.c:736` | `static void sv_collect_text(const char *s, size_t n, size_t *i, char *dst, size_t cap)` |
| `sv_ctx` | struct | `src/svg_render.c:151` | `` |
| `sv_ctx_from_attrs` | function | `src/svg_render.c:307` | `static void sv_ctx_from_attrs(sv_ctx *ctx, const sv_attr *at, size_t nat)` |
| `sv_fit` | function | `src/svg_render.c:754` | `void sv_fit(const sv_image *img, double dw, double dh,             double *scale, double *off_x, ...` |
| `sv_flag` | function | `src/svg_render.c:477` | `static int sv_flag(const char *s, size_t n, size_t *i, double *out)` |
| `sv_is_digit` | function | `src/svg_render.c:25` | `static int sv_is_digit(char c)` |
| `sv_is_dropped_element` | function | `src/svg_render.c:646` | `static int sv_is_dropped_element(const char *name, size_t n)` |
| `sv_is_space` | function | `src/svg_render.c:21` | `static int sv_is_space(char c)` |
| `sv_lower` | function | `src/svg_render.c:27` | `static char sv_lower(char c)` |
| `sv_mat_identity` | function | `src/svg_render.c:161` | `static void sv_mat_identity(double *m)` |
| `sv_mat_mul` | function | `src/svg_render.c:166` | `static void sv_mat_mul(const double *a, const double *b, double *out)` |
| `sv_new_seg` | function | `src/svg_render.c:363` | `static sv_seg *sv_new_seg(sv_image *im, sv_shape *sh)` |
| `sv_new_shape` | function | `src/svg_render.c:324` | `static sv_shape *sv_new_shape(sv_image *im, int kind, const sv_ctx *ctx)` |
| `sv_parse` | function | `src/svg_render.c:774` | `sv_status sv_parse(const char *markup, size_t len, sv_image *out)` |
| `sv_parse_ex` | function | `src/svg_render.c:778` | `sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill)` |
| `sv_parse_path` | function | `src/svg_render.c:488` | `static void sv_parse_path(sv_image *im, sv_shape *sh, const char *s, size_t n)` |
| `sv_parse_points` | function | `src/svg_render.c:343` | `static void sv_parse_points(sv_image *im, sv_shape *sh, const char *s, size_t n)` |
| `sv_parse_transform` | function | `src/svg_render.c:179` | `static void sv_parse_transform(const char *s, size_t n, double *m)` |
| `sv_scan_attrs` | function | `src/svg_render.c:658` | `static void sv_scan_attrs(const char *s, size_t n, size_t *i,                           sv_attr *...` |
| `sv_seg_cubic` | function | `src/svg_render.c:385` | `static int sv_seg_cubic(sv_image *im, sv_shape *sh,                         double x1, double y1,...` |
| `sv_seg_line` | function | `src/svg_render.c:378` | `static int sv_seg_line(sv_image *im, sv_shape *sh, double x, double y)` |
| `sv_seg_move` | function | `src/svg_render.c:371` | `static int sv_seg_move(sv_image *im, sv_shape *sh, double x, double y)` |
| `sv_sep` | function | `src/svg_render.c:82` | `static void sv_sep(const char *s, size_t n, size_t *i)` |
| `sv_skip_subtree` | function | `src/svg_render.c:704` | `static void sv_skip_subtree(const char *s, size_t n, size_t *i, const char *name, size_t nlen)` |
| `sv_span_eq` | function | `src/svg_render.c:32` | `static int sv_span_eq(const char *s, size_t n, const char *lit)` |
| `sv_style_next` | function | `src/svg_render.c:238` | `static int sv_style_next(const char *s, size_t n, size_t *i,                          const char ...` |
| `EPIPE` | function | `src/tab.c:2734` | `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();` |
| `FB_MAX_FILE_BYTES` | function | `src/tab.c:1296` | `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify  * the stream. ...` |
| `PV_MAX_CONTAINERS_WIRE` | macro | `src/tab.c:172` | `#define PV_MAX_CONTAINERS_WIRE` |
| `TAB_ASYNC_THREADS` | macro | `src/tab.c:218` | `#define TAB_ASYNC_THREADS` |
| `TAB_CQ_REDERIVE_MAX` | macro | `src/tab.c:299` | `#define TAB_CQ_REDERIVE_MAX` |
| `TAB_IOBUF_BYTES` | macro | `src/tab.c:63` | `#define TAB_IOBUF_BYTES` |
| `TAB_MAX_ASYNC_PENDING` | macro | `src/tab.c:216` | `#define TAB_MAX_ASYNC_PENDING` |
| `TAB_MAX_BATCH_BYTES` | macro | `src/tab.c:219` | `#define TAB_MAX_BATCH_BYTES` |
| `TAB_MAX_EXTERN_CSS` | macro | `src/tab.c:1369` | `#define TAB_MAX_EXTERN_CSS` |
| `TAB_MAX_GEOM_WORDS` | macro | `src/tab.c:204` | `#define TAB_MAX_GEOM_WORDS` |
| `TAB_MAX_HIST_BYTES` | macro | `src/tab.c:198` | `#define TAB_MAX_HIST_BYTES` |
| `TAB_MAX_HIST_OPS` | macro | `src/tab.c:197` | `#define TAB_MAX_HIST_OPS` |
| `TAB_MAX_JS_JOBS` | macro | `src/tab.c:225` | `#define TAB_MAX_JS_JOBS` |
| `TAB_MAX_NET_ROUNDS` | macro | `src/tab.c:217` | `#define TAB_MAX_NET_ROUNDS` |
| `TAB_MAX_OPENS` | macro | `src/tab.c:200` | `#define TAB_MAX_OPENS` |
| `TAB_MAX_OPEN_BYTES` | macro | `src/tab.c:201` | `#define TAB_MAX_OPEN_BYTES` |
| `TAB_MAX_RUNS` | macro | `src/tab.c:168` | `#define TAB_MAX_RUNS` |
| `TAB_MAX_STORAGE` | macro | `src/tab.c:193` | `#define TAB_MAX_STORAGE` |
| `TAB_MAX_SUBREQ` | macro | `src/tab.c:223` | `#define TAB_MAX_SUBREQ` |
| `TAB_MAX_SUBRESOURCE` | macro | `src/tab.c:224` | `#define TAB_MAX_SUBRESOURCE` |
| `TAB_MAX_URL` | macro | `src/tab.c:175` | `#define TAB_MAX_URL` |
| `TAB_MAX_WS_MSG` | macro | `src/tab.c:189` | `#define TAB_MAX_WS_MSG` |
| `TAB_SCREEN_H` | macro | `src/tab.c:141` | `#define TAB_SCREEN_H` |
| `TAB_SCREEN_W` | macro | `src/tab.c:140` | `#define TAB_SCREEN_W` |
| `TAB_WIRE_A_N` | macro | `src/tab.c:146` | `#define TAB_WIRE_A_N` |
| `TAB_WIRE_BOX_F_N` | macro | `src/tab.c:148` | `#define TAB_WIRE_BOX_F_N` |
| `TAB_WIRE_B_N` | macro | `src/tab.c:147` | `#define TAB_WIRE_B_N` |
| `TAB_WIRE_GRID_N` | macro | `src/tab.c:149` | `#define TAB_WIRE_GRID_N` |
| `TAB_WIRE_HEAD_N` | macro | `src/tab.c:145` | `#define TAB_WIRE_HEAD_N` |
| `WHERE` | function | `src/tab.c:2057` | `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...` |
| `_GNU_SOURCE` | macro | `src/tab.c:14` | `#define _GNU_SOURCE` |
| `adopt_worker` | function | `src/tab.c:3802` | `static tab_status adopt_worker(const tab_spawned *sp, tab **out)` |
| `blocks` | function | `src/tab.c:842` | `* * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the * grid array, block B[26])...` |
| `budget_remaining_ms` | function | `src/tab.c:1326` | `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` |
| `buffer` | function | `src/tab.c:772` | `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...` |
| `child_computed_style` | function | `src/tab.c:421` | `static int child_computed_style(child_state *cs, dom_node_id h, css_style *st,                   ...` |
| `child_cq` | function | `src/tab.c:317` | `static pv_cq_src *child_cq(child_state *cs)` |
| `child_cq_width` | function | `src/tab.c:303` | `static int child_cq_width(void *ctx, dom_node_id node)` |
| `child_fetch` | function | `src/tab.c:545` | `static int child_fetch(void *vctx, const char *method, const char *url,                        co...` |
| `child_fetch_async` | function | `src/tab.c:561` | `static int child_fetch_async(void *vctx, const char *method, const char *url,                    ...` |
| `child_handle_click` | function | `src/tab.c:2423` | `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_decode_image` | function | `src/tab.c:2665` | `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` |
| `child_handle_decode_image_data` | function | `src/tab.c:2692` | `static void child_handle_decode_image_data(int wfd, const char *url, size_t len)` |
| `child_handle_eval` | function | `src/tab.c:2624` | `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` |
| `child_handle_event` | function | `src/tab.c:2477` | `static void child_handle_event(int wfd, child_state *cs)` |
| `child_handle_geom` | function | `src/tab.c:2563` | `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` |
| `child_handle_load` | function | `src/tab.c:1778` | `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,            ...` |
| `child_handle_mouse` | function | `src/tab.c:2525` | `static void child_handle_mouse(int wfd, child_state *cs)` |
| `child_handle_mutation` | function | `src/tab.c:2304` | `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,                         ...` |
| `child_handle_mutation_ex` | function | `src/tab.c:2311` | `static void child_handle_mutation_ex(int wfd, child_state *cs, int is_tick,                      ...` |
| `child_handle_submit` | function | `src/tab.c:2590` | `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_load` | function | `src/tab.c:704` | `static int child_load(child_state *cs, const char *html, size_t len, int run_js,                 ...` |
| `child_net_drain` | function | `src/tab.c:577` | `static void child_net_drain(child_state *cs, int settle_ms)` |
| `child_next_timer_ms` | function | `src/tab.c:2285` | `static int32_t child_next_timer_ms(child_state *cs)` |
| `child_prescript_view` | function | `src/tab.c:1748` | `static pv_view *child_prescript_view(child_state *cs, const char *html, size_t len,              ...` |
| `child_read_reply` | function | `src/tab.c:517` | `static int child_read_reply(child_state *cs, net_reply *out)` |
| `child_reset_page` | function | `src/tab.c:348` | `static void child_reset_page(child_state *cs)` |
| `child_sheets` | function | `src/tab.c:343` | `static shc_cache *child_sheets(child_state *cs)` |
| `child_start_parser_async` | function | `src/tab.c:621` | `static int child_start_parser_async(child_state *cs, const char *src)` |
| `child_state` | struct | `src/tab.c:236` | `` |
| `child_write_subreq` | function | `src/tab.c:492` | `static int child_write_subreq(child_state *cs, uint8_t tag, const char *method, const char *url, ...` |
| `clip_pm_ok` | function | `src/tab.c:153` | `static int clip_pm_ok(int32_t v)` |
| `column` | function | `src/tab.c:3320` | `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...` |
| `computed_signature` | function | `src/tab.c:378` | `static uint64_t computed_signature(const dom_index *idx)` |
| `content` | function | `src/tab.c:2134` | `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...` |
| `css_text` | struct | `src/tab.c:1557` | `` |
| `css_text_emit` | function | `src/tab.c:1580` | `static int css_text_emit(void *ctx, const char *s, size_t n)` |
| `css_text_put` | function | `src/tab.c:1563` | `static int css_text_put(css_text *t, const char *s, size_t n)` |
| `ctype_is_css` | function | `src/tab.c:1349` | `static int ctype_is_css(const char *ctype)` |
| `ctype_is_javascript` | function | `src/tab.c:1340` | `static int ctype_is_javascript(const char *ctype)` |
| `depth` | function | `src/tab.c:2764` | `* defense in depth (seccomp already excludes open/socket/exec);` |
| `does` | function | `src/tab.c:1870` | `* native browser does (spec/js_native.md). Best effort -- an unsealed page still runs. */ (void)jn_seal(cs->js);` |
| `exec_worker_child` | function | `src/tab.c:3731` | `static void exec_worker_child(int rfd, int wfd)` |
| `fd` | type_alias | `src/tab.c:64` | `typedef struct tab_iobuf { int fd;` |
| `fn` | function | `src/tab.c:4034` | `&& fn(fctx, method, url, body, blen, status, rbody, rlen, rctype) == 0);` |
| `fn` | type_alias | `src/tab.c:4109` | `typedef struct tab_net_fn { tab_fetch_fn fn;` |
| `frames` | function | `src/tab.c:4833` | `* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of...` |
| `gate_js_nav` | function | `src/tab.c:4456` | `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom,        ...` |
| `gen_session_key` | function | `src/tab.c:2712` | `static uint64_t gen_session_key(void)` |
| `geom_parent` | function | `src/tab.c:2555` | `static dom_node_id geom_parent(void *ctx, dom_node_id n)` |
| `geometry_encode` | function | `src/tab.c:5181` | `static int32_t *geometry_encode(const jg_table *g, size_t *words_out)` |
| `hist_ops_free` | function | `src/tab.c:4238` | `static void hist_ops_free(tab_hist_op *ops, size_t n)` |
| `ignore_sigpipe` | function | `src/tab.c:3070` | `static void ignore_sigpipe(void)` |
| `io_failure` | function | `src/tab.c:3723` | `static tab_status io_failure(tab *t)` |
| `is_activation_event` | function | `src/tab.c:4303` | `static int is_activation_event(const char *type)` |
| `job_discard` | function | `src/tab.c:5205` | `static void job_discard(tab *t)` |
| `job_main` | function | `src/tab.c:5228` | `static void *job_main(void *arg)` |
| `job_start` | function | `src/tab.c:5257` | `static tab_status job_start(tab *t)` |
| `layout` | function | `src/tab.c:3309` | `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....` |
| `libraries` | function | `src/tab.c:1887` | `* load heavier libraries (jQuery, Bootstrap, etc.) that need more time. * Untrusted hosts get the default budget...` |
| `load` | function | `src/tab.c:3022` | `* subresource requests this load (set per page: host in allow.conf AND js.conf);` |
| `log_external_skip` | function | `src/tab.c:1357` | `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,                 ...` |
| `navigation` | function | `src/tab.c:2429` | `* the navigation (HTML 7.4.6.4: scroll, then queue hashchange), and the header is written  * befo...` |
| `net_reply` | struct | `src/tab.c:481` | `` |
| `net_reply_free` | function | `src/tab.c:489` | `static void net_reply_free(net_reply *r)` |
| `once` | function | `src/tab.c:2187` | `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);` |
| `open_urls_free` | function | `src/tab.c:4312` | `static void open_urls_free(char **u, size_t n)` |
| `parse_worker_fd` | function | `src/tab.c:2983` | `static int parse_worker_fd(const char *s, int *out)` |
| `prof_lap` | function | `src/tab.c:666` | `static void prof_lap(const char *what, double *t0)` |
| `prof_now_ms` | function | `src/tab.c:656` | `static double prof_now_ms(void)` |
| `prof_on` | function | `src/tab.c:661` | `static int prof_on(void)` |
| `rad_len_ok` | function | `src/tab.c:159` | `static int rad_len_ok(int32_t v, int dflt)` |
| `read_console` | function | `src/tab.c:3676` | `static int read_console(int fd, fb_buffer *out)` |
| `read_field` | function | `src/tab.c:3096` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `read_full` | macro | `src/tab.c:118` | `#define read_full(fd, buf, n)` |
| `read_opens` | function | `src/tab.c:4323` | `static tab_status read_opens(tab *t, const char *page_url, int gesture,                          ...` |
| `read_scroll` | function | `src/tab.c:4430` | `static tab_status read_scroll(tab *t, tab_page *out)` |
| `read_view` | function | `src/tab.c:3113` | `static int read_view(int fd, pv_view **out)` |
| `read_view_raw` | function | `src/tab.c:3121` | `static int read_view_raw(int fd, pv_view **out)` |
| `read_ws` | function | `src/tab.c:4363` | `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` |
| `reap_spawned` | function | `src/tab.c:3793` | `static void reap_spawned(const tab_spawned *sp, int kill_it)` |
| `run` | function | `src/tab.c:1375` | `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).  * Call after every ...` |
| `run_js` | function | `src/tab.c:677` | `* regardless of run_js (a no-JS load simply never records a request). */ /* Installs the page-ind...` |
| `send_request` | function | `src/tab.c:3713` | `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` |
| `sheet_expand` | function | `src/tab.c:1618` | `static int sheet_expand(child_state *cs, const char *base, const char *body, size_t blen,        ...` |
| `sheets` | function | `src/tab.c:1695` | `* sheets (their own text is read from the DOM by page_view). Every failure is  * fail-open for th...` |
| `sig_mix` | function | `src/tab.c:370` | `static uint64_t sig_mix(uint64_t h, const char *s, size_t n)` |
| `spawn_worker` | function | `src/tab.c:3763` | `static tab_status spawn_worker(tab_spawned *sp)` |
| `status` | type_alias | `src/tab.c:481` | `typedef struct net_reply { int32_t status;` |
| `swap` | function | `src/tab.c:2196` | `* display:none hiding an element via class swap (CSS, not      * DOM removal). */     if (ok && v...` |
| `tab` | struct | `src/tab.c:3015` | `` |
| `tab_alive` | function | `src/tab.c:5078` | `int tab_alive(const tab *t)` |
| `tab_anchor_free` | function | `src/tab.c:5357` | `void tab_anchor_free(tab_anchor *a)` |
| `tab_anchor_query` | function | `src/tab.c:5363` | `tab_status tab_anchor_query(tab *t, const char *fragment, const char *push_url,                  ...` |
| `tab_anchor_query_ex` | function | `src/tab.c:5368` | `tab_status tab_anchor_query_ex(tab *t, const char *fragment, const char *push_url,               ...` |
| `tab_async_busy` | function | `src/tab.c:5253` | `int tab_async_busy(const tab *t)` |
| `tab_async_fd` | function | `src/tab.c:5244` | `int tab_async_fd(tab *t)` |
| `tab_async_finish` | function | `src/tab.c:5295` | `tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)` |
| `tab_async_sync` | function | `src/tab.c:5218` | `static void tab_async_sync(tab *t)` |
| `tab_await_result` | function | `src/tab.c:4836` | `static tab_status tab_await_result(tab *t)` |
| `tab_await_result_inner` | function | `src/tab.c:4844` | `static tab_status tab_await_result_inner(tab *t)` |
| `tab_batch` | function | `src/tab.c:4144` | `static sqb *tab_batch(tab *t)` |
| `tab_batch_discard` | function | `src/tab.c:4230` | `static void tab_batch_discard(tab *t)` |
| `tab_batch_fill` | function | `src/tab.c:4118` | `static int tab_batch_fill(int ok, int status, char *rbody, size_t rlen, char *rctype, char *rhdrs...` |
| `tab_batch_run` | function | `src/tab.c:4134` | `static int tab_batch_run(void *vt, const sqb_req *rq, sqb_res *out)` |
| `tab_batch_run_stable` | function | `src/tab.c:4126` | `static int tab_batch_run_stable(void *vn, const sqb_req *rq, sqb_res *out)` |
| `tab_child_pid` | function | `src/tab.c:5084` | `pid_t tab_child_pid(const tab *t)` |
| `tab_click` | function | `src/tab.c:4701` | `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)` |
| `tab_close` | function | `src/tab.c:5088` | `void tab_close(tab *t)` |
| `tab_decode_image` | function | `src/tab.c:5057` | `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)` |
| `tab_decode_image_data_url` | function | `src/tab.c:5064` | `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)` |
| `tab_decode_image_op` | function | `src/tab.c:5010` | `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,         ...` |
| `tab_eval` | function | `src/tab.c:4969` | `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)` |
| `tab_eval_result_free` | function | `src/tab.c:5142` | `void tab_eval_result_free(tab_eval_result *r)` |
| `tab_fetch_one` | function | `src/tab.c:4042` | `static int tab_fetch_one(tab *t, const char *method, const char *url, const char *body, size_t bl...` |
| `tab_geometry_async` | function | `src/tab.c:5280` | `tab_status tab_geometry_async(tab *t, const jg_table *g)` |
| `tab_geometry_send` | function | `src/tab.c:5163` | `static tab_status tab_geometry_send(tab *t, const int32_t *buf, size_t words)` |
| `tab_image_free` | function | `src/tab.c:5151` | `void tab_image_free(tab_image *img)` |
| `tab_inflight_request_headers` | function | `src/tab.c:3992` | `const char *tab_inflight_request_headers(void)` |
| `tab_iobuf` | struct | `src/tab.c:64` | `` |
| `tab_last_subreq_stats` | function | `src/tab.c:3937` | `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)` |
| `tab_load` | function | `src/tab.c:4478` | `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)` |
| `tab_load_ex` | function | `src/tab.c:4482` | `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)` |
| `tab_load_full` | function | `src/tab.c:4486` | `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,             ...` |
| `tab_mod_fetch` | function | `src/tab.c:1463` | `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` |
| `tab_mod_resolve` | function | `src/tab.c:1433` | `static int tab_mod_resolve(void *host, const char *base, const char *spec,                       ...` |
| `tab_net_fn` | struct | `src/tab.c:4109` | `` |
| `tab_net_fn_free` | function | `src/tab.c:4111` | `static void tab_net_fn_free(void *p)` |
| `tab_note_css_served` | function | `src/tab.c:4065` | `static void tab_note_css_served(tab *t, int ok, int status, const char *url, const char *rbody,  ...` |
| `tab_op_budget_us` | function | `src/tab.c:4061` | `static int64_t tab_op_budget_us(const tab *t)` |
| `tab_open` | function | `src/tab.c:3853` | `tab_status tab_open(tab **out)` |
| `tab_page_free` | function | `src/tab.c:5106` | `void tab_page_free(tab_page *p)` |
| `tab_page_keep_view` | function | `src/tab.c:3921` | `void tab_page_keep_view(tab_page *prev, tab_page *next)` |
| `tab_parse_worker_args` | function | `src/tab.c:2995` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)` |
| `tab_popstate` | function | `src/tab.c:5317` | `tab_status tab_popstate(tab *t, int index, tab_page *out)` |
| `tab_prewarm` | function | `src/tab.c:3824` | `void tab_prewarm(void)` |
| `tab_prewarmed` | function | `src/tab.c:3830` | `int tab_prewarmed(void)` |
| `tab_prewarmed_pid` | function | `src/tab.c:3837` | `int tab_prewarmed_pid(void)` |
| `tab_read_full` | function | `src/tab.c:92` | `static int tab_read_full(int fd, void *buf, size_t n)` |
| `tab_read_subreq_fields` | function | `src/tab.c:4050` | `static int tab_read_subreq_fields(tab *t, char **method, char **url, char **body, size_t *blen,  ...` |
| `tab_read_view` | function | `src/tab.c:4827` | `tab_status tab_read_view(tab *t, tab_page *out)` |
| `tab_read_view_ex` | function | `src/tab.c:4853` | `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)` |
| `tab_refresh_alive` | function | `src/tab.c:3077` | `static void tab_refresh_alive(tab *t)` |
| `tab_report_response_headers` | function | `src/tab.c:3980` | `void tab_report_response_headers(const char *lines)` |
| `tab_retire_batch` | function | `src/tab.c:3882` | `static void tab_retire_batch(tab *t)` |
| `tab_serve_netwait` | function | `src/tab.c:4191` | `static int tab_serve_netwait(tab *t)` |
| `tab_serve_subreq` | function | `src/tab.c:4081` | `static int tab_serve_subreq(tab *t, int net_granted, int css_granted)` |
| `tab_serve_tag` | function | `src/tab.c:4222` | `static int tab_serve_tag(tab *t, uint8_t tag, int net_granted, int css_granted)` |
| `tab_set_async_fetcher` | function | `src/tab.c:3893` | `void tab_set_async_fetcher(tab *t, tab_fetch_fn fn, void *ctx, void (*free_ctx)(void *))` |
| `tab_set_cookies` | function | `src/tab.c:3960` | `void tab_set_cookies(tab *t, const char *cookies)` |
| `tab_set_css_allowed` | function | `src/tab.c:3932` | `void tab_set_css_allowed(tab *t, int allowed)` |
| `tab_set_css_sink` | function | `src/tab.c:3901` | `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)` |
| `tab_set_fetcher` | function | `src/tab.c:3876` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)` |
| `tab_set_frame_id` | function | `src/tab.c:3950` | `void tab_set_frame_id(tab *t, int id)` |
| `tab_set_geometry` | function | `src/tab.c:5191` | `tab_status tab_set_geometry(tab *t, const jg_table *g)` |
| `tab_set_identity` | function | `src/tab.c:3942` | `void tab_set_identity(tab *t, const char *serialized)` |
| `tab_set_lazy_ticks` | function | `src/tab.c:3916` | `void tab_set_lazy_ticks(tab *t, int on)` |
| `tab_set_net_allowed` | function | `src/tab.c:3911` | `void tab_set_net_allowed(tab *t, int allowed)` |
| `tab_set_op_net_budget_ms` | function | `src/tab.c:3907` | `void tab_set_op_net_budget_ms(tab *t, int ms)` |
| `tab_set_storage` | function | `src/tab.c:5344` | `void tab_set_storage(tab *t, const char *blob, size_t len)` |
| `tab_set_viewport_w` | function | `src/tab.c:3955` | `void tab_set_viewport_w(tab *t, int px)` |
| `tab_shutdown_spare` | function | `src/tab.c:3844` | `void tab_shutdown_spare(void)` |
| `tab_spawned` | struct | `src/tab.c:3751` | `` |
| `tab_submit` | function | `src/tab.c:4719` | `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` |
| `tab_submit_async` | function | `src/tab.c:4167` | `static int tab_submit_async(tab *t, int net_granted, int css_granted)` |
| `tab_subreq_permitted` | function | `src/tab.c:3966` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)` |
| `tab_tick` | function | `src/tab.c:4709` | `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)` |
| `tab_tick_async` | function | `src/tab.c:5270` | `tab_status tab_tick_async(tab *t, int elapsed_ms)` |
| `tab_url_resolve` | function | `src/tab.c:1424` | `static int tab_url_resolve(void *ctx, const char *base, const char *ref,                         ...` |
| `tab_wflush` | function | `src/tab.c:73` | `static int tab_wflush(void)` |
| `tab_worker_dispatch` | function | `src/tab.c:3005` | `void tab_worker_dispatch(int argc, char **argv)` |
| `tab_worker_run` | function | `src/tab.c:2732` | `static void tab_worker_run(int rfd, int wfd)` |
| `tab_write_full` | function | `src/tab.c:80` | `static int tab_write_full(int fd, const void *buf, size_t n)` |
| `tab_write_reply` | function | `src/tab.c:3998` | `static int tab_write_reply(tab *t, int ok, int status, const char *rbody, size_t rlen,           ...` |
| `tab_ws_event` | function | `src/tab.c:5324` | `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,        ...` |
| `tests` | function | `src/tab.c:3196` | `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...` |
| `tzset` | function | `src/tab.c:2750` | `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);` |
| `unchanged` | function | `src/tab.c:276` | `* is unchanged (spec/sheet_cache.md);` |
| `write_field` | function | `src/tab.c:808` | `static int write_field(int fd, const char *s)` |
| `write_full` | macro | `src/tab.c:117` | `#define write_full(fd, buf, n)` |
| `write_full` | function | `src/tab.c:2217` | `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 \|\| write_full(wfd, text, xl) == 0) && write_view(wfd...` |
| `write_history` | function | `src/tab.c:1485` | `static int write_history(int wfd, child_state *cs)` |
| `write_opens` | function | `src/tab.c:2273` | `static int write_opens(int wfd, child_state *cs)` |
| `write_scroll` | function | `src/tab.c:1516` | `static int write_scroll(int wfd, child_state *cs)` |
| `write_storage` | function | `src/tab.c:2259` | `static int write_storage(int wfd, child_state *cs)` |
| `write_view` | function | `src/tab.c:850` | `static int write_view(int wfd, const pv_view *v)` |
| `write_view_raw` | function | `src/tab.c:861` | `static int write_view_raw(int wfd, const pv_view *v)` |
| `write_ws` | function | `src/tab.c:2242` | `static int write_ws(int wfd, child_state *cs)` |
| `ws_ops_free` | function | `src/tab.c:4354` | `static void ws_ops_free(tab_ws_op *ops, size_t n)` |
| `tl_columns` | function | `src/table_layout.c:134` | `double tl_columns(const tl_cell *cells, size_t n, size_t ncols, double gap,                   dou...` |
| `tl_distribute` | function | `src/table_layout.c:98` | `static void tl_distribute(const double *minw, const double *maxw, const int *sized,              ...` |
| `tl_intrinsic` | function | `src/table_layout.c:78` | `void tl_intrinsic(const tl_cell *cells, size_t n, size_t ncols, double gap,                   dou...` |
| `tl_measure` | function | `src/table_layout.c:23` | `static void tl_measure(const tl_cell *cells, size_t n, size_t ncols, double gap,                 ...` |
| `tl_spread` | function | `src/table_layout.c:14` | `static void tl_spread(double *w, const double *weight, size_t c0, size_t c1, double extra)` |
| `pair_parity` | function | `src/text_case.c:8` | `static int pair_parity(uint32_t cp)` |
| `tc_is_lower` | function | `src/text_case.c:54` | `int tc_is_lower(uint32_t cp)` |
| `tc_lower` | function | `src/text_case.c:37` | `uint32_t tc_lower(uint32_t cp)` |
| `tc_smallcaps_runs` | function | `src/text_case.c:117` | `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap)` |
| `tc_transform` | function | `src/text_case.c:95` | `size_t tc_transform(const char *s, size_t n, int transform, int word_start,                     c...` |
| `tc_upper` | function | `src/text_case.c:18` | `uint32_t tc_upper(uint32_t cp)` |
| `utf8_decode` | function | `src/text_case.c:61` | `static size_t utf8_decode(const unsigned char *s, size_t n, uint32_t *cp)` |
| `utf8_len_of` | function | `src/text_case.c:91` | `static size_t utf8_len_of(uint32_t cp)` |
| `utf8_put` | function | `src/text_case.c:79` | `static void utf8_put(uint32_t cp, size_t len, unsigned char *out)` |
| `TSH_BLANK_GLYPH` | macro | `src/text_shape.c:745` | `#define TSH_BLANK_GLYPH` |
| `TSH_CACHE_SLOTS` | macro | `src/text_shape.c:37` | `#define TSH_CACHE_SLOTS` |
| `TSH_FB_BLOCKS` | macro | `src/text_shape.c:788` | `#define TSH_FB_BLOCKS` |
| `TSH_FB_CP_SLOTS` | macro | `src/text_shape.c:805` | `#define TSH_FB_CP_SLOTS` |
| `TSH_FB_SLOTS` | macro | `src/text_shape.c:787` | `#define TSH_FB_SLOTS` |
| `TSH_MAX_FONT_BYTES` | macro | `src/text_shape.c:33` | `#define TSH_MAX_FONT_BYTES` |
| `TSH_MAX_RUNS` | macro | `src/text_shape.c:990` | `#define TSH_MAX_RUNS` |
| `TSH_MEASURE_SLOTS` | macro | `src/text_shape.c:1063` | `#define TSH_MEASURE_SLOTS` |
| `TSH_MEASURE_TEXT_MAX` | macro | `src/text_shape.c:1064` | `#define TSH_MEASURE_TEXT_MAX` |
| `TSH_SUBS_MAX` | macro | `src/text_shape.c:530` | `#define TSH_SUBS_MAX` |
| `TSH_VAR_AXES_MAX` | macro | `src/text_shape.c:269` | `#define TSH_VAR_AXES_MAX` |
| `TSH_WEB_SLOTS` | macro | `src/text_shape.c:227` | `#define TSH_WEB_SLOTS` |
| `TSH_WGHT_BOLD` | macro | `src/text_shape.c:268` | `#define TSH_WGHT_BOLD` |
| `TSH_WGHT_REGULAR` | macro | `src/text_shape.c:267` | `#define TSH_WGHT_REGULAR` |
| `_POSIX_C_SOURCE` | macro | `src/text_shape.c:12` | `#define _POSIX_C_SOURCE` |
| `ascii_ieq` | function | `src/text_shape.c:461` | `static int ascii_ieq(const char *a, const char *b)` |
| `backend_init` | function | `src/text_shape.c:103` | `static int backend_init(void)` |
| `blob` | function | `src/text_shape.c:333` | `* blob (it shaped every character to .notdef): its face is built over the tables * FreeType already decoded. A bare...` |
| `characters` | function | `src/text_shape.c:138` | `* hold characters ('-', ':') that the pattern syntax treats specially. */ static int load_entry_file(tsh_entry *e...` |
| `cover_cp` | function | `src/text_shape.c:943` | `static int cover_cp(unsigned cp, void *vctx)` |
| `entry_apply_size` | function | `src/text_shape.c:66` | `static void entry_apply_size(tsh_entry *e, double px)` |
| `entry_free` | function | `src/text_shape.c:448` | `static void entry_free(tsh_entry *e)` |
| `entry_opsz_for` | function | `src/text_shape.c:57` | `static int entry_opsz_for(const tsh_entry *e, double px)` |
| `fb_clear` | function | `src/text_shape.c:814` | `static void fb_clear(void)` |
| `fb_entry` | function | `src/text_shape.c:856` | `static tsh_entry *fb_entry(unsigned cp, int bold)` |
| `fb_entry_uncached` | function | `src/text_shape.c:873` | `static tsh_entry *fb_entry_uncached(unsigned cp, int bold)` |
| `fb_match_covering` | function | `src/text_shape.c:834` | `static FcPattern *fb_match_covering(FcPattern *pat, FcCharSet *cs)` |
| `fc_installed` | function | `src/text_shape.c:516` | `static int fc_installed(const char *name, void *ctx)` |
| `fc_resolve` | function | `src/text_shape.c:559` | `static int fc_resolve(const char *name, char *out, size_t cap, void *ctx)` |
| `file` | type_alias | `src/text_shape.c:789` | `typedef struct tsh_fb { char file[512];` |
| `generic_name` | function | `src/text_shape.c:93` | `static const char *generic_name(int family)` |
| `get_entry` | function | `src/text_shape.c:211` | `static tsh_entry *get_entry(int family, int bold, int italic)` |
| `get_entry_ex` | function | `src/text_shape.c:662` | `static tsh_entry *get_entry_ex(const tsh_font *f)` |
| `is_private_use` | function | `src/text_shape.c:748` | `static int is_private_use(unsigned cp)` |
| `lfam_index` | function | `src/text_shape.c:615` | `static int lfam_index(const char *fam)` |
| `load_entry` | function | `src/text_shape.c:207` | `static int load_entry(tsh_entry *e, int family, int bold, int italic)` |
| `load_entry_file` | function | `src/text_shape.c:171` | `static int load_entry_file(tsh_entry *e, const char *path, int index)` |
| `load_entry_named` | function | `src/text_shape.c:141` | `static int load_entry_named(tsh_entry *e, const char *fam, int bold, int italic)` |
| `loaded` | type_alias | `src/text_shape.c:38` | `typedef struct tsh_entry { int loaded;` |
| `local_clear` | function | `src/text_shape.c:604` | `static void local_clear(void)` |
| `local_entry` | function | `src/text_shape.c:642` | `static tsh_entry *local_entry(int handle, int bold, int italic)` |
| `name` | type_alias | `src/text_shape.c:587` | `typedef struct tsh_lfam { char name[TSH_FAMILY_MAX];` |
| `read_font_file` | function | `src/text_shape.c:120` | `static unsigned char *read_font_file(const char *path, long *out_n)` |
| `rides_previous` | function | `src/text_shape.c:753` | `static int rides_previous(unsigned cp)` |
| `shape_entry` | function | `src/text_shape.c:957` | `static tsh_status shape_entry(tsh_entry *e, double px, const char *text, size_t len,             ...` |
| `shape_runs` | function | `src/text_shape.c:994` | `static tsh_status shape_runs(cairo_t *cr, const tsh_font *f, double px, double x,                ...` |
| `slice` | function | `src/text_shape.c:251` | `* woff2 slice (spec/webfont.md);` |
| `tsh_cover_ctx` | struct | `src/text_shape.c:934` | `` |
| `tsh_draw` | function | `src/text_shape.c:1110` | `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,                     double x, doub...` |
| `tsh_entry` | struct | `src/text_shape.c:39` | `` |
| `tsh_face` | function | `src/text_shape.c:1117` | `cairo_font_face_t *tsh_face(const tsh_font *f)` |
| `tsh_face_generation` | function | `src/text_shape.c:371` | `unsigned tsh_face_generation(void)` |
| `tsh_family_is_generic` | function | `src/text_shape.c:470` | `int tsh_family_is_generic(const char *name)` |
| `tsh_fb` | struct | `src/text_shape.c:790` | `` |
| `tsh_fb_cp` | struct | `src/text_shape.c:806` | `` |
| `tsh_lfam` | struct | `src/text_shape.c:588` | `` |
| `tsh_llist` | struct | `src/text_shape.c:594` | `` |
| `tsh_local_handle` | function | `src/text_shape.c:623` | `int tsh_local_handle(const char *list)` |
| `tsh_measure` | function | `src/text_shape.c:1075` | `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)` |
| `tsh_measure_slot` | struct | `src/text_shape.c:1065` | `` |
| `tsh_pick_family` | function | `src/text_shape.c:503` | `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong,         ...` |
| `tsh_pick_from_list` | function | `src/text_shape.c:482` | `int tsh_pick_from_list(const char *list, tsh_name_resolver resolve, void *ctx,                   ...` |
| `tsh_ready` | function | `src/text_shape.c:674` | `int tsh_ready(void)` |
| `tsh_segment` | function | `src/text_shape.c:761` | `int tsh_segment(const char *text, size_t len, tsh_cover_fn cover, void *ctx,                 tsh_...` |
| `tsh_shape` | function | `src/text_shape.c:679` | `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,                 ...` |
| `tsh_shutdown` | function | `src/text_shape.c:1123` | `void tsh_shutdown(void)` |
| `tsh_web` | struct | `src/text_shape.c:229` | `` |
| `tsh_webfont_clear` | function | `src/text_shape.c:430` | `void tsh_webfont_clear(void)` |
| `tsh_webfont_register` | function | `src/text_shape.c:373` | `int tsh_webfont_register(const char *name,                          const unsigned char *bytes, s...` |
| `used` | type_alias | `src/text_shape.c:228` | `typedef struct tsh_web { int used;` |
| `utf8_next` | function | `src/text_shape.c:729` | `static unsigned utf8_next(const char *s, size_t n, size_t *len)` |
| `web_entry_free` | function | `src/text_shape.c:239` | `static void web_entry_free(tsh_web *w)` |
| `web_find` | function | `src/text_shape.c:436` | `static tsh_entry *web_find(unsigned h, int bold, int italic)` |
| `web_magic_ok` | function | `src/text_shape.c:252` | `static int web_magic_ok(const unsigned char *b, size_t n)` |
| `web_make_entry` | function | `src/text_shape.c:309` | `static int web_make_entry(tsh_entry *e, const unsigned char *bytes, size_t nbytes, int bold,     ...` |
| `tf_backspace` | function | `src/textfield.c:47` | `void tf_backspace(tf_field *f)` |
| `tf_clear` | function | `src/textfield.c:20` | `void tf_clear(tf_field *f)` |
| `tf_cursor` | function | `src/textfield.c:91` | `size_t tf_cursor(const tf_field *f)` |
| `tf_delete` | function | `src/textfield.c:55` | `void tf_delete(tf_field *f)` |
| `tf_end` | function | `src/textfield.c:78` | `void tf_end(tf_field *f)` |
| `tf_home` | function | `src/textfield.c:73` | `void tf_home(tf_field *f)` |
| `tf_insert` | function | `src/textfield.c:35` | `tf_status tf_insert(tf_field *f, char c)` |
| `tf_len` | function | `src/textfield.c:87` | `size_t tf_len(const tf_field *f)` |
| `tf_move` | function | `src/textfield.c:62` | `void tf_move(tf_field *f, long delta)` |
| `tf_set` | function | `src/textfield.c:24` | `tf_status tf_set(tf_field *f, const char *s)` |
| `tf_text` | function | `src/textfield.c:83` | `const char *tf_text(const tf_field *f)` |
| `whole` | function | `src/textfield.c:6` | `* the buffer is rejected whole (fail closed), never applied partially.  */  #include "textfield.h...` |
| `bounded_len` | function | `src/tls_impersonate.c:25` | `static size_t bounded_len(const char *s, size_t max)` |
| `get_bytes` | function | `src/tls_impersonate.c:89` | `static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len)` |
| `get_str` | function | `src/tls_impersonate.c:103` | `static char *get_str(ti_rd *r, size_t cap)` |
| `get_u32` | function | `src/tls_impersonate.c:70` | `static uint32_t get_u32(ti_rd *r)` |
| `get_u64` | function | `src/tls_impersonate.c:80` | `static uint64_t get_u64(ti_rd *r)` |
| `get_u8` | function | `src/tls_impersonate.c:65` | `static uint8_t get_u8(ti_rd *r)` |
| `put_blob` | function | `src/tls_impersonate.c:53` | `static void put_blob(ti_wr *w, const uint8_t *b, size_t n)` |
| `put_u32` | function | `src/tls_impersonate.c:40` | `static void put_u32(ti_wr *w, uint32_t v)` |
| `put_u64` | function | `src/tls_impersonate.c:48` | `static void put_u64(ti_wr *w, uint64_t v)` |
| `put_u8` | function | `src/tls_impersonate.c:35` | `static void put_u8(ti_wr *w, uint8_t v)` |
| `ti_decode_req` | function | `src/tls_impersonate.c:140` | `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out)` |
| `ti_decode_resp` | function | `src/tls_impersonate.c:196` | `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out)` |
| `ti_encode_req` | function | `src/tls_impersonate.c:122` | `size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap)` |
| `ti_encode_resp` | function | `src/tls_impersonate.c:177` | `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap)` |
| `ti_rd` | struct | `src/tls_impersonate.c:63` | `` |
| `ti_req_free` | function | `src/tls_impersonate.c:166` | `void ti_req_free(ti_req *r)` |
| `ti_resp_free` | function | `src/tls_impersonate.c:230` | `void ti_resp_free(ti_resp *r)` |
| `ti_should_impersonate` | function | `src/tls_impersonate.c:18` | `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,                           i...` |
| `ti_wr` | struct | `src/tls_impersonate.c:33` | `` |
| `valid_profile` | function | `src/tls_impersonate.c:116` | `static int valid_profile(int p)` |
| `layout_push` | function | `src/ui_layout.c:13` | `static int layout_push(ui_layout *lay, size_t offset, size_t len)` |
| `ui_clamp_scroll` | function | `src/ui_layout.c:99` | `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines)` |
| `ui_layout_free` | function | `src/ui_layout.c:91` | `void ui_layout_free(ui_layout *lay)` |
| `ui_wrap_text` | function | `src/ui_layout.c:27` | `ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out)` |
| `_POSIX_C_SOURCE` | macro | `src/url.c:9` | `#define _POSIX_C_SOURCE` |
| `append_query_encoded` | function | `src/url.c:229` | `static int append_query_encoded(char *out, size_t outsz, const char *src)` |
| `assumed` | function | `src/url.c:254` | `* assumed (the caller already routed whitespace to search). */ static int looks_like_host(const c...` |
| `build_search` | function | `src/url.c:303` | `static url_status build_search(const char *query, char *out, size_t outsz)` |
| `cat_checked` | function | `src/url.c:40` | `static int cat_checked(char *out, size_t outsz, const char *src)` |
| `ci_prefix` | function | `src/url.c:20` | `static int ci_prefix(const char *haystack, const char *prefix)` |
| `copy_bounded` | function | `src/url.c:645` | `static url_status copy_bounded(char *out, size_t outsz, const char *a, size_t alen,              ...` |
| `copy_checked` | function | `src/url.c:32` | `static int copy_checked(char *out, size_t outsz, const char *src)` |
| `dir_len` | function | `src/url.c:159` | `static size_t dir_len(const char *base)` |
| `host_equals` | function | `src/url.c:378` | `static int host_equals(const url_parts *p, const char *want)` |
| `is_space` | function | `src/url.c:218` | `static int is_space(int c)` |
| `is_unreserved` | function | `src/url.c:222` | `static int is_unreserved(int c)` |
| `ncat_checked` | function | `src/url.c:49` | `static int ncat_checked(char *out, size_t outsz, const char *src, size_t n)` |
| `out_pop_segment` | function | `src/url.c:102` | `static void out_pop_segment(char *out, size_t *olen)` |
| `query_find_q` | function | `src/url.c:393` | `static const char *query_find_q(const char *search, size_t len, size_t *vlen)` |
| `url_authority_len` | function | `src/url.c:91` | `size_t url_authority_len(const char *url)` |
| `url_extract_userinfo` | function | `src/url.c:431` | `url_status url_extract_userinfo(const char *url, char *out, size_t outsz,                        ...` |
| `url_file_path` | function | `src/url.c:531` | `const char *url_file_path(const char *s)` |
| `url_has_scheme` | function | `src/url.c:59` | `int url_has_scheme(const char *s)` |
| `url_history_target` | function | `src/url.c:654` | `url_status url_history_target(const char *base, const char *ref, char *out, size_t outsz)` |
| `url_is_file` | function | `src/url.c:525` | `int url_is_file(const char *s)` |
| `url_is_https` | function | `src/url.c:73` | `int url_is_https(const char *s)` |
| `url_omnibox` | function | `src/url.c:309` | `url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz)` |
| `url_remove_dot_segments` | function | `src/url.c:109` | `url_status url_remove_dot_segments(const char *path, char *out, size_t outsz)` |
| `url_resolve_file` | function | `src/url.c:535` | `url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz)` |
| `url_resolve_https` | function | `src/url.c:170` | `url_status url_resolve_https(const char *base, const char *ref,                              char...` |
| `url_search_rewrite` | function | `src/url.c:411` | `url_status url_search_rewrite(const char *url, char *out, size_t outsz)` |
| `url_split` | function | `src/url.c:584` | `url_status url_split(const char *url, url_parts *out)` |
| `url_split_location` | function | `src/url.c:688` | `url_status url_split_location(const char *url, url_parts *out)` |
| `url_validate_https` | function | `src/url.c:80` | `url_status url_validate_https(const char *url)` |
| `finite4` | function | `src/video_controls.c:7` | `static int finite4(double a, double b, double c, double d)` |
| `in_rect` | function | `src/video_controls.c:11` | `static int in_rect(const vcl_rect *r, double px, double py)` |
| `vcl_clamp_frac` | function | `src/video_controls.c:34` | `double vcl_clamp_frac(double f)` |
| `vcl_format_time` | function | `src/video_controls.c:99` | `size_t vcl_format_time(double seconds, char *buf, size_t cap)` |
| `vcl_hit` | function | `src/video_controls.c:39` | `vcl_hit_kind vcl_hit(const vcl_geom *g, const vcl_rect *video, double px, double py,             ...` |
| `vcl_layout` | function | `src/video_controls.c:15` | `int vcl_layout(double x, double y, double w, double h, vcl_geom *g)` |
| `vcl_position` | function | `src/video_controls.c:90` | `double vcl_position(double base_s, int64_t pts0_us, int64_t pts_us, double total)` |
| `vcl_seg_duration` | function | `src/video_controls.c:54` | `double vcl_seg_duration(double d)` |
| `vcl_segment_at` | function | `src/video_controls.c:66` | `size_t vcl_segment_at(const hls_playlist *pl, double t, double *start)` |
| `vcl_segment_start` | function | `src/video_controls.c:82` | `double vcl_segment_start(const hls_playlist *pl, size_t idx)` |
| `vcl_total` | function | `src/video_controls.c:59` | `double vcl_total(const hls_playlist *pl)` |
| `vpk_first_video` | function | `src/video_pick.c:15` | `const char *vpk_first_video(const pv_view *v)` |
| `vpk_for_frame` | function | `src/video_pick.c:26` | `const char *vpk_for_frame(const pv_view *frame_view, const char *top_video)` |
| `check` | function | `src/web_storage.c:65` | `static int check(const char *blob, size_t len, size_t *bytes_out)` |
| `find` | function | `src/web_storage.c:118` | `static wst_origin *find(const wst_db *db, const char *origin)` |
| `get_u32` | function | `src/web_storage.c:25` | `static uint32_t get_u32(const unsigned char *p)` |
| `key_cmp` | function | `src/web_storage.c:56` | `static int key_cmp(const void *a, const void *b)` |
| `key_ref` | struct | `src/web_storage.c:54` | `` |
| `put_u32` | function | `src/web_storage.c:201` | `static void put_u32(char *b, uint32_t v)` |
| `utf8_ok` | function | `src/web_storage.c:32` | `static int utf8_ok(const unsigned char *s, size_t n)` |
| `wst_db` | struct | `src/web_storage.c:20` | `` |
| `wst_decode_check` | function | `src/web_storage.c:101` | `int wst_decode_check(const char *blob, size_t len)` |
| `wst_encode` | function | `src/web_storage.c:125` | `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len)` |
| `wst_foreach` | function | `src/web_storage.c:181` | `int wst_foreach(const char *blob, size_t len,                 void (*fn)(void *ctx, const char *k...` |
| `wst_free` | function | `src/web_storage.c:109` | `void wst_free(wst_db *db)` |
| `wst_new` | function | `src/web_storage.c:105` | `wst_db *wst_new(void)` |
| `wst_origin` | struct | `src/web_storage.c:12` | `` |
| `wst_origin_bytes` | function | `src/web_storage.c:175` | `size_t wst_origin_bytes(const wst_db *db, const char *origin)` |
| `wst_pack` | function | `src/web_storage.c:206` | `int wst_pack(const char *const *keys, const size_t *klens,              const char *const *vals, ...` |
| `wst_replace` | function | `src/web_storage.c:140` | `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len)` |
| `wc_derive` | function | `src/webcaps.c:15` | `wc_caps wc_derive(wc_input in)` |
| `wc_from_flags` | function | `src/webcaps.c:35` | `wc_caps wc_from_flags(bool js, bool css, bool images)` |
| `wc_render_caps` | function | `src/webcaps.c:46` | `rdp_caps wc_render_caps(wc_caps c)` |
| `wc_safe` | function | `src/webcaps.c:10` | `wc_caps wc_safe(void)` |
| `candidates` | function | `src/webfont.c:7` | `* understanding just far enough to find candidates (family + first url() per * src entry + weight/style descriptors);` |
| `ci_eq_span` | function | `src/webfont.c:28` | `static int ci_eq_span(const char *s, size_t n, const char *kw)` |
| `emit` | function | `src/webfont.c:129` | `static void emit(wf_list *out, const char *family,                  const char *url, size_t ulen,...` |
| `emit_data` | function | `src/webfont.c:145` | `static void emit_data(wf_list *out, const char *family,                       const char *span, s...` |
| `emit_family_format` | function | `src/webfont.c:101` | `static void emit_family_format(wf_ref *r, const char *family, const char *format)` |
| `emit_slot` | function | `src/webfont.c:86` | `static wf_ref *emit_slot(wf_list *out)` |
| `is_ws` | function | `src/webfont.c:19` | `static int is_ws(char c)` |
| `lower_ch` | function | `src/webfont.c:23` | `static int lower_ch(char c)` |
| `lower_ch` | function | `src/webfont.c:313` | `&& lower_ch(s[k]) == 's' && k + 3 < bend                 && lower_ch(s[k + 1]) == 'r' && lower_ch...` |
| `scan_face_block` | function | `src/webfont.c:182` | `static void scan_face_block(const char *s, size_t bstart, size_t bend,                           ...` |
| `span_is_data` | function | `src/webfont.c:117` | `static int span_is_data(const char *span, size_t slen)` |
| `wf_list_free` | function | `src/webfont.c:49` | `void wf_list_free(wf_list *l)` |
| `wf_ref_move` | function | `src/webfont.c:64` | `void wf_ref_move(wf_ref *dst, wf_ref *src)` |
| `wf_scan` | function | `src/webfont.c:429` | `int wf_scan(const char *css, size_t len, wf_list *out)` |
| `wf_supported_format` | function | `src/webfont.c:74` | `int wf_supported_format(const char *fmt)` |
| `WF_DATA_URL_MAX` | macro | `src/webfont_load.c:91` | `#define WF_DATA_URL_MAX` |
| `ctype_ok` | function | `src/webfont_load.c:24` | `static int ctype_ok(const char *ct)` |
| `fetch` | type_alias | `src/webfont_load.c:56` | `typedef struct wf_cursor { wf_fetch_fn fetch;` |
| `hash` | type_alias | `src/webfont_load.c:46` | `typedef struct wf_key { unsigned hash;` |
| `here` | function | `src/webfont_load.c:22` | `* filtered here (a "" hint may still name one);` |
| `key_find` | function | `src/webfont_load.c:66` | `static int key_find(wf_key *keys, size_t nkeys, unsigned h, int b, int i)` |
| `ref` | function | `src/webfont_load.c:167` | `* their ref (the register call copies what it keeps). */ if (!is_data) free(fbytes);` |
| `scan_inline` | function | `src/webfont_load.c:178` | `static void scan_inline(const char *html, size_t len, const char *page_url,                      ...` |
| `wf_cursor` | struct | `src/webfont_load.c:56` | `` |
| `wf_key` | struct | `src/webfont_load.c:46` | `` |
| `wf_load_document` | function | `src/webfont_load.c:229` | `int wf_load_document(wf_fetch_fn fetch, void *fctx, const char *page_url,                      co...` |
| `WD_MAX_NAMES` | macro | `src/wl_display.c:10` | `#define WD_MAX_NAMES` |
| `WD_NAME_MAX` | macro | `src/wl_display.c:11` | `#define WD_NAME_MAX` |
| `WD_PREFIX` | macro | `src/wl_display.c:8` | `#define WD_PREFIX` |
| `WD_PREFIX_LEN` | macro | `src/wl_display.c:9` | `#define WD_PREFIX_LEN` |
| `_POSIX_C_SOURCE` | macro | `src/wl_display.c:1` | `#define _POSIX_C_SOURCE` |
| `wd_index` | function | `src/wl_display.c:13` | `static int wd_index(const char *name, unsigned long *idx)` |
| `wd_pick` | function | `src/wl_display.c:27` | `int wd_pick(const char *const *names, size_t n, char *out, size_t cap)` |
| `wd_resolve_env` | function | `src/wl_display.c:42` | `int wd_resolve_env(void)` |
| `WLG_POLL_MS` | macro | `src/wl_guard.c:17` | `#define WLG_POLL_MS` |
| `_DEFAULT_SOURCE` | macro | `src/wl_guard.c:5` | `#define _DEFAULT_SOURCE` |
| `guard_main` | function | `src/wl_guard.c:26` | `static void *guard_main(void *arg)` |
| `wl_guard` | struct | `src/wl_guard.c:19` | `` |
| `wlg_start` | function | `src/wl_guard.c:45` | `wl_guard *wlg_start(struct wl_display *display)` |
| `wlg_stop` | function | `src/wl_guard.c:61` | `void wlg_stop(wl_guard *g)` |
| `WH_READS_PER_PUMP` | macro | `src/ws_hub.c:21` | `#define WH_READS_PER_PUMP` |
| `WH_RECV_CHUNK` | macro | `src/ws_hub.c:22` | `#define WH_RECV_CHUNK` |

Next: [SYMBOLS_p13.md](SYMBOLS_p13.md)
