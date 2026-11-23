# Symbols (page 12 of 19)
Previous: [SYMBOLS_p11.md](SYMBOLS_p11.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `TAB_MAX_STORAGE` | macro | `src/tab.c:190` | `#define TAB_MAX_STORAGE` |
| `TAB_MAX_SUBREQ` | macro | `src/tab.c:220` | `#define TAB_MAX_SUBREQ` |
| `TAB_MAX_SUBRESOURCE` | macro | `src/tab.c:221` | `#define TAB_MAX_SUBRESOURCE` |
| `TAB_MAX_URL` | macro | `src/tab.c:172` | `#define TAB_MAX_URL` |
| `TAB_MAX_WS_MSG` | macro | `src/tab.c:186` | `#define TAB_MAX_WS_MSG` |
| `TAB_SCREEN_H` | macro | `src/tab.c:138` | `#define TAB_SCREEN_H` |
| `TAB_SCREEN_W` | macro | `src/tab.c:137` | `#define TAB_SCREEN_W` |
| `TAB_WIRE_A_N` | macro | `src/tab.c:143` | `#define TAB_WIRE_A_N` |
| `TAB_WIRE_BOX_F_N` | macro | `src/tab.c:145` | `#define TAB_WIRE_BOX_F_N` |
| `TAB_WIRE_B_N` | macro | `src/tab.c:144` | `#define TAB_WIRE_B_N` |
| `TAB_WIRE_GRID_N` | macro | `src/tab.c:146` | `#define TAB_WIRE_GRID_N` |
| `TAB_WIRE_HEAD_N` | macro | `src/tab.c:142` | `#define TAB_WIRE_HEAD_N` |
| `WHERE` | function | `src/tab.c:1986` | `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...` |
| `_GNU_SOURCE` | macro | `src/tab.c:14` | `#define _GNU_SOURCE` |
| `adopt_worker` | function | `src/tab.c:3693` | `static tab_status adopt_worker(const tab_spawned *sp, tab **out)` |
| `blocks` | function | `src/tab.c:829` | `* * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the * grid array, block B[26])...` |
| `budget_remaining_ms` | function | `src/tab.c:1312` | `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` |
| `buffer` | function | `src/tab.c:759` | `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...` |
| `child_cq` | function | `src/tab.c:313` | `static pv_cq_src *child_cq(child_state *cs)` |
| `child_cq_width` | function | `src/tab.c:299` | `static int child_cq_width(void *ctx, dom_node_id node)` |
| `child_fetch` | function | `src/tab.c:532` | `static int child_fetch(void *vctx, const char *method, const char *url,                        co...` |
| `child_fetch_async` | function | `src/tab.c:548` | `static int child_fetch_async(void *vctx, const char *method, const char *url,                    ...` |
| `child_handle_click` | function | `src/tab.c:2340` | `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_handle_decode_image` | function | `src/tab.c:2565` | `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` |
| `child_handle_decode_image_data` | function | `src/tab.c:2592` | `static void child_handle_decode_image_data(int wfd, const char *url, size_t len)` |
| `child_handle_eval` | function | `src/tab.c:2524` | `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` |
| `child_handle_event` | function | `src/tab.c:2377` | `static void child_handle_event(int wfd, child_state *cs)` |
| `child_handle_geom` | function | `src/tab.c:2463` | `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` |
| `child_handle_load` | function | `src/tab.c:1707` | `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,            ...` |
| `child_handle_mouse` | function | `src/tab.c:2425` | `static void child_handle_mouse(int wfd, child_state *cs)` |
| `child_handle_mutation` | function | `src/tab.c:2232` | `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,                         ...` |
| `child_handle_mutation_ex` | function | `src/tab.c:2239` | `static void child_handle_mutation_ex(int wfd, child_state *cs, int is_tick,                      ...` |
| `child_handle_submit` | function | `src/tab.c:2490` | `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` |
| `child_load` | function | `src/tab.c:691` | `static int child_load(child_state *cs, const char *html, size_t len, int run_js,                 ...` |
| `child_net_drain` | function | `src/tab.c:564` | `static void child_net_drain(child_state *cs, int settle_ms)` |
| `child_next_timer_ms` | function | `src/tab.c:2213` | `static int32_t child_next_timer_ms(child_state *cs)` |
| `child_prescript_view` | function | `src/tab.c:1677` | `static pv_view *child_prescript_view(child_state *cs, const char *html, size_t len,              ...` |
| `child_read_reply` | function | `src/tab.c:504` | `static int child_read_reply(child_state *cs, net_reply *out)` |
| `child_reset_page` | function | `src/tab.c:344` | `static void child_reset_page(child_state *cs)` |
| `child_sheets` | function | `src/tab.c:339` | `static shc_cache *child_sheets(child_state *cs)` |
| `child_start_parser_async` | function | `src/tab.c:608` | `static int child_start_parser_async(child_state *cs, const char *src)` |
| `child_state` | struct | `src/tab.c:233` | `` |
| `child_write_subreq` | function | `src/tab.c:479` | `static int child_write_subreq(child_state *cs, uint8_t tag, const char *method, const char *url, ...` |
| `clip_pm_ok` | function | `src/tab.c:150` | `static int clip_pm_ok(int32_t v)` |
| `column` | function | `src/tab.c:3218` | `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...` |
| `computed_signature` | function | `src/tab.c:374` | `static uint64_t computed_signature(const dom_index *idx)` |
| `content` | function | `src/tab.c:2063` | `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...` |
| `css_text` | struct | `src/tab.c:1486` | `` |
| `css_text_emit` | function | `src/tab.c:1509` | `static int css_text_emit(void *ctx, const char *s, size_t n)` |
| `css_text_put` | function | `src/tab.c:1492` | `static int css_text_put(css_text *t, const char *s, size_t n)` |
| `ctype_is_css` | function | `src/tab.c:1335` | `static int ctype_is_css(const char *ctype)` |
| `ctype_is_javascript` | function | `src/tab.c:1326` | `static int ctype_is_javascript(const char *ctype)` |
| `depth` | function | `src/tab.c:2664` | `* defense in depth (seccomp already excludes open/socket/exec);` |
| `does` | function | `src/tab.c:1799` | `* native browser does (spec/js_native.md). Best effort -- an unsealed page still runs. */ (void)jn_seal(cs->js);` |
| `exec_worker_child` | function | `src/tab.c:3622` | `static void exec_worker_child(int rfd, int wfd)` |
| `fd` | type_alias | `src/tab.c:62` | `typedef struct tab_iobuf { int fd;` |
| `fn` | function | `src/tab.c:3925` | `&& fn(fctx, method, url, body, blen, status, rbody, rlen, rctype) == 0);` |
| `fn` | type_alias | `src/tab.c:4000` | `typedef struct tab_net_fn { tab_fetch_fn fn;` |
| `frames` | function | `src/tab.c:4675` | `* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of...` |
| `gate_js_nav` | function | `src/tab.c:4320` | `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` |
| `gen_session_key` | function | `src/tab.c:2612` | `static uint64_t gen_session_key(void)` |
| `geom_parent` | function | `src/tab.c:2455` | `static dom_node_id geom_parent(void *ctx, dom_node_id n)` |
| `geometry_encode` | function | `src/tab.c:5008` | `static int32_t *geometry_encode(const jg_table *g, size_t *words_out)` |
| `hist_ops_free` | function | `src/tab.c:4129` | `static void hist_ops_free(tab_hist_op *ops, size_t n)` |
| `ignore_sigpipe` | function | `src/tab.c:2968` | `static void ignore_sigpipe(void)` |
| `io_failure` | function | `src/tab.c:3614` | `static tab_status io_failure(tab *t)` |
| `is_activation_event` | function | `src/tab.c:4194` | `static int is_activation_event(const char *type)` |
| `job_discard` | function | `src/tab.c:5032` | `static void job_discard(tab *t)` |
| `job_main` | function | `src/tab.c:5055` | `static void *job_main(void *arg)` |
| `job_start` | function | `src/tab.c:5084` | `static tab_status job_start(tab *t)` |
| `layout` | function | `src/tab.c:3207` | `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....` |
| `libraries` | function | `src/tab.c:1816` | `* load heavier libraries (jQuery, Bootstrap, etc.) that need more time. * Untrusted hosts get the default budget...` |
| `load` | function | `src/tab.c:2920` | `* subresource requests this load (set per page: host in allow.conf AND js.conf);` |
| `log_external_skip` | function | `src/tab.c:1343` | `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,                 ...` |
| `net_reply` | struct | `src/tab.c:468` | `` |
| `net_reply_free` | function | `src/tab.c:476` | `static void net_reply_free(net_reply *r)` |
| `once` | function | `src/tab.c:2116` | `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);` |
| `open_urls_free` | function | `src/tab.c:4203` | `static void open_urls_free(char **u, size_t n)` |
| `parse_worker_fd` | function | `src/tab.c:2881` | `static int parse_worker_fd(const char *s, int *out)` |
| `prof_lap` | function | `src/tab.c:653` | `static void prof_lap(const char *what, double *t0)` |
| `prof_now_ms` | function | `src/tab.c:643` | `static double prof_now_ms(void)` |
| `prof_on` | function | `src/tab.c:648` | `static int prof_on(void)` |
| `rad_len_ok` | function | `src/tab.c:156` | `static int rad_len_ok(int32_t v, int dflt)` |
| `read_console` | function | `src/tab.c:3567` | `static int read_console(int fd, fb_buffer *out)` |
| `read_field` | function | `src/tab.c:2994` | `static int read_field(int fd, char **out, size_t *out_len)` |
| `read_full` | macro | `src/tab.c:116` | `#define read_full(fd, buf, n)` |
| `read_opens` | function | `src/tab.c:4213` | `static tab_status read_opens(tab *t, const char *page_url, int gesture,                          ...` |
| `read_view` | function | `src/tab.c:3011` | `static int read_view(int fd, pv_view **out)` |
| `read_view_raw` | function | `src/tab.c:3019` | `static int read_view_raw(int fd, pv_view **out)` |
| `read_ws` | function | `src/tab.c:4251` | `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` |
| `reap_spawned` | function | `src/tab.c:3684` | `static void reap_spawned(const tab_spawned *sp, int kill_it)` |
| `run` | function | `src/tab.c:1361` | `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).  * Call after every ...` |
| `run_js` | function | `src/tab.c:664` | `* regardless of run_js (a no-JS load simply never records a request). */ /* Installs the page-ind...` |
| `send_request` | function | `src/tab.c:3604` | `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` |
| `sheet_expand` | function | `src/tab.c:1547` | `static int sheet_expand(child_state *cs, const char *base, const char *body, size_t blen,        ...` |
| `sheets` | function | `src/tab.c:1624` | `* sheets (their own text is read from the DOM by page_view). Every failure is  * fail-open for th...` |
| `sig_mix` | function | `src/tab.c:366` | `static uint64_t sig_mix(uint64_t h, const char *s, size_t n)` |
| `spawn_worker` | function | `src/tab.c:3654` | `static tab_status spawn_worker(tab_spawned *sp)` |
| `status` | type_alias | `src/tab.c:468` | `typedef struct net_reply { int32_t status;` |
| `swap` | function | `src/tab.c:2125` | `* display:none hiding an element via class swap (CSS, not      * DOM removal). */     if (ok && v...` |
| `tab` | struct | `src/tab.c:2913` | `` |
| `tab_alive` | function | `src/tab.c:4911` | `int tab_alive(const tab *t)` |
| `tab_anchor_free` | function | `src/tab.c:5184` | `void tab_anchor_free(tab_anchor *a)` |
| `tab_anchor_query` | function | `src/tab.c:5190` | `tab_status tab_anchor_query(tab *t, const char *fragment, const char *push_url,                  ...` |
| `tab_async_busy` | function | `src/tab.c:5080` | `int tab_async_busy(const tab *t)` |
| `tab_async_fd` | function | `src/tab.c:5071` | `int tab_async_fd(tab *t)` |
| `tab_async_finish` | function | `src/tab.c:5122` | `tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)` |
| `tab_async_sync` | function | `src/tab.c:5045` | `static void tab_async_sync(tab *t)` |
| `tab_await_result` | function | `src/tab.c:4678` | `static tab_status tab_await_result(tab *t)` |
| `tab_await_result_inner` | function | `src/tab.c:4686` | `static tab_status tab_await_result_inner(tab *t)` |
| `tab_batch` | function | `src/tab.c:4035` | `static sqb *tab_batch(tab *t)` |
| `tab_batch_discard` | function | `src/tab.c:4121` | `static void tab_batch_discard(tab *t)` |
| `tab_batch_fill` | function | `src/tab.c:4009` | `static int tab_batch_fill(int ok, int status, char *rbody, size_t rlen, char *rctype, char *rhdrs...` |
| `tab_batch_run` | function | `src/tab.c:4025` | `static int tab_batch_run(void *vt, const sqb_req *rq, sqb_res *out)` |
| `tab_batch_run_stable` | function | `src/tab.c:4017` | `static int tab_batch_run_stable(void *vn, const sqb_req *rq, sqb_res *out)` |
| `tab_child_pid` | function | `src/tab.c:4917` | `pid_t tab_child_pid(const tab *t)` |
| `tab_click` | function | `src/tab.c:4543` | `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)` |
| `tab_close` | function | `src/tab.c:4921` | `void tab_close(tab *t)` |
| `tab_decode_image` | function | `src/tab.c:4890` | `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)` |
| `tab_decode_image_data_url` | function | `src/tab.c:4897` | `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)` |
| `tab_decode_image_op` | function | `src/tab.c:4843` | `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,         ...` |
| `tab_eval` | function | `src/tab.c:4802` | `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)` |
| `tab_eval_result_free` | function | `src/tab.c:4969` | `void tab_eval_result_free(tab_eval_result *r)` |
| `tab_fetch_one` | function | `src/tab.c:3933` | `static int tab_fetch_one(tab *t, const char *method, const char *url, const char *body, size_t bl...` |
| `tab_geometry_async` | function | `src/tab.c:5107` | `tab_status tab_geometry_async(tab *t, const jg_table *g)` |
| `tab_geometry_send` | function | `src/tab.c:4990` | `static tab_status tab_geometry_send(tab *t, const int32_t *buf, size_t words)` |
| `tab_image_free` | function | `src/tab.c:4978` | `void tab_image_free(tab_image *img)` |
| `tab_inflight_request_headers` | function | `src/tab.c:3883` | `const char *tab_inflight_request_headers(void)` |
| `tab_iobuf` | struct | `src/tab.c:62` | `` |
| `tab_last_subreq_stats` | function | `src/tab.c:3828` | `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)` |
| `tab_load` | function | `src/tab.c:4330` | `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)` |
| `tab_load_ex` | function | `src/tab.c:4334` | `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)` |
| `tab_load_full` | function | `src/tab.c:4338` | `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,             ...` |
| `tab_mod_fetch` | function | `src/tab.c:1449` | `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` |
| `tab_mod_resolve` | function | `src/tab.c:1419` | `static int tab_mod_resolve(void *host, const char *base, const char *spec,                       ...` |
| `tab_net_fn` | struct | `src/tab.c:4000` | `` |
| `tab_net_fn_free` | function | `src/tab.c:4002` | `static void tab_net_fn_free(void *p)` |
| `tab_note_css_served` | function | `src/tab.c:3956` | `static void tab_note_css_served(tab *t, int ok, int status, const char *url, const char *rbody,  ...` |
| `tab_op_budget_us` | function | `src/tab.c:3952` | `static int64_t tab_op_budget_us(const tab *t)` |
| `tab_open` | function | `src/tab.c:3744` | `tab_status tab_open(tab **out)` |
| `tab_page_free` | function | `src/tab.c:4939` | `void tab_page_free(tab_page *p)` |
| `tab_page_keep_view` | function | `src/tab.c:3812` | `void tab_page_keep_view(tab_page *prev, tab_page *next)` |
| `tab_parse_worker_args` | function | `src/tab.c:2893` | `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)` |
| `tab_popstate` | function | `src/tab.c:5144` | `tab_status tab_popstate(tab *t, int index, tab_page *out)` |
| `tab_prewarm` | function | `src/tab.c:3715` | `void tab_prewarm(void)` |
| `tab_prewarmed` | function | `src/tab.c:3721` | `int tab_prewarmed(void)` |
| `tab_prewarmed_pid` | function | `src/tab.c:3728` | `int tab_prewarmed_pid(void)` |
| `tab_read_full` | function | `src/tab.c:90` | `static int tab_read_full(int fd, void *buf, size_t n)` |
| `tab_read_subreq_fields` | function | `src/tab.c:3941` | `static int tab_read_subreq_fields(tab *t, char **method, char **url, char **body, size_t *blen,  ...` |
| `tab_read_view` | function | `src/tab.c:4669` | `tab_status tab_read_view(tab *t, tab_page *out)` |
| `tab_read_view_ex` | function | `src/tab.c:4695` | `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)` |
| `tab_refresh_alive` | function | `src/tab.c:2975` | `static void tab_refresh_alive(tab *t)` |
| `tab_report_response_headers` | function | `src/tab.c:3871` | `void tab_report_response_headers(const char *lines)` |
| `tab_retire_batch` | function | `src/tab.c:3773` | `static void tab_retire_batch(tab *t)` |
| `tab_serve_netwait` | function | `src/tab.c:4082` | `static int tab_serve_netwait(tab *t)` |
| `tab_serve_subreq` | function | `src/tab.c:3972` | `static int tab_serve_subreq(tab *t, int net_granted, int css_granted)` |
| `tab_serve_tag` | function | `src/tab.c:4113` | `static int tab_serve_tag(tab *t, uint8_t tag, int net_granted, int css_granted)` |
| `tab_set_async_fetcher` | function | `src/tab.c:3784` | `void tab_set_async_fetcher(tab *t, tab_fetch_fn fn, void *ctx, void (*free_ctx)(void *))` |
| `tab_set_cookies` | function | `src/tab.c:3851` | `void tab_set_cookies(tab *t, const char *cookies)` |
| `tab_set_css_allowed` | function | `src/tab.c:3823` | `void tab_set_css_allowed(tab *t, int allowed)` |
| `tab_set_css_sink` | function | `src/tab.c:3792` | `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)` |
| `tab_set_fetcher` | function | `src/tab.c:3767` | `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)` |
| `tab_set_frame_id` | function | `src/tab.c:3841` | `void tab_set_frame_id(tab *t, int id)` |
| `tab_set_geometry` | function | `src/tab.c:5018` | `tab_status tab_set_geometry(tab *t, const jg_table *g)` |
| `tab_set_identity` | function | `src/tab.c:3833` | `void tab_set_identity(tab *t, const char *serialized)` |
| `tab_set_lazy_ticks` | function | `src/tab.c:3807` | `void tab_set_lazy_ticks(tab *t, int on)` |
| `tab_set_net_allowed` | function | `src/tab.c:3802` | `void tab_set_net_allowed(tab *t, int allowed)` |
| `tab_set_op_net_budget_ms` | function | `src/tab.c:3798` | `void tab_set_op_net_budget_ms(tab *t, int ms)` |
| `tab_set_storage` | function | `src/tab.c:5171` | `void tab_set_storage(tab *t, const char *blob, size_t len)` |
| `tab_set_viewport_w` | function | `src/tab.c:3846` | `void tab_set_viewport_w(tab *t, int px)` |
| `tab_shutdown_spare` | function | `src/tab.c:3735` | `void tab_shutdown_spare(void)` |
| `tab_spawned` | struct | `src/tab.c:3642` | `` |
| `tab_submit` | function | `src/tab.c:4561` | `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` |
| `tab_submit_async` | function | `src/tab.c:4058` | `static int tab_submit_async(tab *t, int net_granted, int css_granted)` |
| `tab_subreq_permitted` | function | `src/tab.c:3857` | `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)` |
| `tab_tick` | function | `src/tab.c:4551` | `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)` |
| `tab_tick_async` | function | `src/tab.c:5097` | `tab_status tab_tick_async(tab *t, int elapsed_ms)` |
| `tab_url_resolve` | function | `src/tab.c:1410` | `static int tab_url_resolve(void *ctx, const char *base, const char *ref,                         ...` |
| `tab_wflush` | function | `src/tab.c:71` | `static int tab_wflush(void)` |
| `tab_worker_dispatch` | function | `src/tab.c:2903` | `void tab_worker_dispatch(int argc, char **argv)` |
| `tab_worker_run` | function | `src/tab.c:2632` | `static void tab_worker_run(int rfd, int wfd)` |
| `tab_write_full` | function | `src/tab.c:78` | `static int tab_write_full(int fd, const void *buf, size_t n)` |
| `tab_write_reply` | function | `src/tab.c:3889` | `static int tab_write_reply(tab *t, int ok, int status, const char *rbody, size_t rlen,           ...` |
| `tab_ws_event` | function | `src/tab.c:5151` | `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,        ...` |
| `tests` | function | `src/tab.c:3094` | `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...` |
| `tzset` | function | `src/tab.c:2650` | `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);` |
| `unchanged` | function | `src/tab.c:272` | `* is unchanged (spec/sheet_cache.md);` |
| `write_field` | function | `src/tab.c:795` | `static int write_field(int fd, const char *s)` |
| `write_full` | macro | `src/tab.c:115` | `#define write_full(fd, buf, n)` |
| `write_full` | function | `src/tab.c:2146` | `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 \|\| write_full(wfd, text, xl) == 0) && write_view(wfd...` |
| `write_history` | function | `src/tab.c:1471` | `static int write_history(int wfd, child_state *cs)` |
| `write_opens` | function | `src/tab.c:2201` | `static int write_opens(int wfd, child_state *cs)` |
| `write_storage` | function | `src/tab.c:2187` | `static int write_storage(int wfd, child_state *cs)` |
| `write_view` | function | `src/tab.c:837` | `static int write_view(int wfd, const pv_view *v)` |
| `write_view_raw` | function | `src/tab.c:848` | `static int write_view_raw(int wfd, const pv_view *v)` |
| `write_ws` | function | `src/tab.c:2170` | `static int write_ws(int wfd, child_state *cs)` |
| `ws_ops_free` | function | `src/tab.c:4242` | `static void ws_ops_free(tab_ws_op *ops, size_t n)` |
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
| `_POSIX_C_SOURCE` | macro | `src/ws_hub.c:6` | `#define _POSIX_C_SOURCE` |
| `conn_clear` | function | `src/ws_hub.c:98` | `static void conn_clear(wh_conn *c)` |
| `dup_str` | function | `src/ws_hub.c:54` | `static char *dup_str(const char *s)` |
| `fail_conn` | function | `src/ws_hub.c:258` | `static void fail_conn(wh_conn *c, int id, wh_emit_fn emit, void *ctx)` |
| `find_id` | function | `src/ws_hub.c:104` | `static wh_conn *find_id(wh_hub *h, int id)` |
| `find_token` | function | `src/ws_hub.c:110` | `static wh_conn *find_token(wh_hub *h, uint64_t token)` |
| `job_free` | function | `src/ws_hub.c:63` | `static void job_free(wh_job *j)` |
| `job_str` | function | `src/ws_hub.c:71` | `static int job_str(wh_job *j, size_t slot, const char **field)` |
| `open_thread` | function | `src/ws_hub.c:79` | `static void *open_thread(void *arg)` |
| `used` | type_alias | `src/ws_hub.c:23` | `typedef struct wh_conn { int used;` |
| `wfd` | type_alias | `src/ws_hub.c:43` | `typedef struct wh_job { int wfd;` |
| `wh_close` | function | `src/ws_hub.c:228` | `void wh_close(wh_hub *h, int id)` |
| `wh_close_all` | function | `src/ws_hub.c:234` | `void wh_close_all(wh_hub *h)` |
| `wh_conn` | struct | `src/ws_hub.c:24` | `` |
| `wh_count` | function | `src/ws_hub.c:314` | `size_t wh_count(const wh_hub *h)` |
| `wh_free` | function | `src/ws_hub.c:129` | `void wh_free(wh_hub *h)` |
| `wh_hub` | struct | `src/ws_hub.c:35` | `` |
| `wh_job` | struct | `src/ws_hub.c:43` | `` |
| `wh_new` | function | `src/ws_hub.c:116` | `wh_hub *wh_new(void)` |
| `wh_notify_fd` | function | `src/ws_hub.c:144` | `int wh_notify_fd(const wh_hub *h)` |
| `wh_on_notify` | function | `src/ws_hub.c:192` | `void wh_on_notify(wh_hub *h, wh_emit_fn emit, void *ctx)` |
| `wh_on_readable` | function | `src/ws_hub.c:266` | `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx)` |
| `wh_open_async` | function | `src/ws_hub.c:148` | `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg)` |
| `wh_poll_fds` | function | `src/ws_hub.c:240` | `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap)` |
| `wh_send` | function | `src/ws_hub.c:221` | `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary)` |
| `ZM_LADDER_N` | macro | `src/zoom.c:12` | `#define ZM_LADDER_N` |
| `zm_apply` | function | `src/zoom.c:44` | `double zm_apply(double base_px, int pct)` |
| `zm_clamp` | function | `src/zoom.c:14` | `int zm_clamp(int pct)` |
| `zm_reset` | function | `src/zoom.c:36` | `int zm_reset(void)` |
| `zm_scale` | function | `src/zoom.c:40` | `double zm_scale(int pct)` |
| `zm_zoom_in` | function | `src/zoom.c:20` | `int zm_zoom_in(int pct)` |
| `zm_zoom_out` | function | `src/zoom.c:28` | `int zm_zoom_out(int pct)` |
| `CHECK` | macro | `tests/itest_secure_fetch.c:18` | `#define CHECK(cond, msg)` |
| `always_cancel` | function | `tests/itest_secure_fetch.c:16` | `static int always_cancel(void *ctx)` |
| `main` | function | `tests/itest_secure_fetch.c:28` | `int main(void)` |
| `attr` | function | `tests/test_anchor.c:33` | `static const char *attr(const fixture *f, dom_node_id n, const char *name)` |
| `fixture` | struct | `tests/test_anchor.c:15` | `` |
| `load` | function | `tests/test_anchor.c:17` | `static int load(fixture *f, const char *html)` |
| `main` | function | `tests/test_anchor.c:198` | `int main(void)` |
| `tag` | function | `tests/test_anchor.c:29` | `static const char *tag(const fixture *f, dom_node_id n)` |
| `test_collect_subtree_then_following` | function | `tests/test_anchor.c:134` | `static void test_collect_subtree_then_following(void **state)` |
| `test_percent_decode` | function | `tests/test_anchor.c:37` | `static void test_percent_decode(void **state)` |
| `test_resolve_decoded` | function | `tests/test_anchor.c:97` | `static void test_resolve_decoded(void **state)` |
| `test_resolve_id_then_name` | function | `tests/test_anchor.c:54` | `static void test_resolve_id_then_name(void **state)` |
| `test_resolve_name_only_on_a` | function | `tests/test_anchor.c:71` | `static void test_resolve_name_only_on_a(void **state)` |
| `test_resolve_rejects_detached_and_bad_args` | function | `tests/test_anchor.c:112` | `static void test_resolve_rejects_detached_and_bad_args(void **state)` |
| `test_resolve_top_and_empty` | function | `tests/test_anchor.c:80` | `static void test_resolve_top_and_empty(void **state)` |
| `test_scroll_for` | function | `tests/test_anchor.c:188` | `static void test_scroll_for(void **state)` |
| `test_target_top` | function | `tests/test_anchor.c:162` | `static void test_target_top(void **state)` |
| `unload` | function | `tests/test_anchor.c:24` | `static void unload(fixture *f)` |
| `main` | function | `tests/test_anti_fp.c:197` | `int main(void)` |
| `test_boolean_props` | function | `tests/test_anti_fp.c:74` | `static void test_boolean_props(void **state)` |
| `test_bucket_screen` | function | `tests/test_anti_fp.c:83` | `static void test_bucket_screen(void **state)` |
| `test_coarsen_time` | function | `tests/test_anti_fp.c:18` | `static void test_coarsen_time(void **state)` |
| `test_identity_is_fixed` | function | `tests/test_anti_fp.c:34` | `static void test_identity_is_fixed(void **state)` |
| `test_legacy_identity_fixed` | function | `tests/test_anti_fp.c:61` | `static void test_legacy_identity_fixed(void **state)` |
| `test_origin_key_deterministic` | function | `tests/test_anti_fp.c:146` | `static void test_origin_key_deterministic(void **state)` |
| `test_origin_key_empty_namespace` | function | `tests/test_anti_fp.c:171` | `static void test_origin_key_empty_namespace(void **state)` |
| `test_origin_key_per_session` | function | `tests/test_anti_fp.c:165` | `static void test_origin_key_per_session(void **state)` |
| `test_origin_key_per_site` | function | `tests/test_anti_fp.c:153` | `static void test_origin_key_per_site(void **state)` |
| `test_origin_key_unlinks_readback` | function | `tests/test_anti_fp.c:183` | `static void test_origin_key_unlinks_readback(void **state)` |
| `test_perturb_bounded_lsb` | function | `tests/test_anti_fp.c:111` | `static void test_perturb_bounded_lsb(void **state)` |
| `test_perturb_deterministic` | function | `tests/test_anti_fp.c:101` | `static void test_perturb_deterministic(void **state)` |
| `test_perturb_key_sensitive` | function | `tests/test_anti_fp.c:126` | `static void test_perturb_key_sensitive(void **state)` |
| `test_perturb_safe_edges` | function | `tests/test_anti_fp.c:136` | `static void test_perturb_safe_edges(void **state)` |

Next: [SYMBOLS_p13.md](SYMBOLS_p13.md)
