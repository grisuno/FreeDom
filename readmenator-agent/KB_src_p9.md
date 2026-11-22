# Subsystem: src (page 9 of 10)
Previous: [KB_src_p8.md](KB_src_p8.md)

## src/tab.c
- Doc: tab_iobuf: Batched pipe I/O for the view codec. write_view/read_view move one int32 block and...
- Layer: utility
- Language: c
- Symbols:
  - `tab_iobuf` (struct, line 61)
  - `child_state` (struct, line 232)
  - `net_reply` (struct, line 467)
  - `css_text` (struct, line 1426)
  - `tab` (struct, line 2790)
  - `tab_spawned` (struct, line 3514)
  - `fd` (type_alias, line 61) `typedef struct tab_iobuf { int fd;`
  - `status` (type_alias, line 467) `typedef struct net_reply { int32_t status;`
  - `tab_wflush` (function, line 70) `static int tab_wflush(void)`
  - `tab_write_full` (function, line 77) `static int tab_write_full(int fd, const void *buf, size_t n)`
  - `tab_read_full` (function, line 89) `static int tab_read_full(int fd, void *buf, size_t n)`
  - `clip_pm_ok` (function, line 149) `static int clip_pm_ok(int32_t v)`
  - `rad_len_ok` (function, line 155) `static int rad_len_ok(int32_t v, int dflt)`
  - `child_cq_width` (function, line 298) `static int child_cq_width(void *ctx, dom_node_id node)`
  - `child_cq` (function, line 312) `static pv_cq_src *child_cq(child_state *cs)`
  - `child_sheets` (function, line 338) `static shc_cache *child_sheets(child_state *cs)`
  - `child_reset_page` (function, line 343) `static void child_reset_page(child_state *cs)`
  - `sig_mix` (function, line 365) `static uint64_t sig_mix(uint64_t h, const char *s, size_t n)`
  - `computed_signature` (function, line 373) `static uint64_t computed_signature(const dom_index *idx)`
  - `net_reply_free` (function, line 475) `static void net_reply_free(net_reply *r)`
  - `child_write_subreq` (function, line 478) `static int child_write_subreq(child_state *cs, uint8_t tag, const char *method, const char *url,
...`
  - `child_read_reply` (function, line 503) `static int child_read_reply(child_state *cs, net_reply *out)`
  - `child_fetch` (function, line 531) `static int child_fetch(void *vctx, const char *method, const char *url,
                       co...`
  - `child_fetch_async` (function, line 547) `static int child_fetch_async(void *vctx, const char *method, const char *url,
                   ...`
  - `replies` (function, line 560) `* writing replies (no pipe deadlock). */
static void child_net_drain(child_state *cs)`
  - `prof_now_ms` (function, line 584) `static double prof_now_ms(void)`
  - `prof_on` (function, line 589) `static int prof_on(void)`
  - `prof_lap` (function, line 594) `static void prof_lap(const char *what, double *t0)`
  - `run_js` (function, line 605) `* regardless of run_js (a no-JS load simply never records a request). */
/* Installs the page-ind...`
  - `child_load` (function, line 632) `static int child_load(child_state *cs, const char *html, size_t len, int run_js,
                ...`
  - `write_field` (function, line 736) `static int write_field(int fd, const char *s)`
  - `write_view` (function, line 778) `static int write_view(int wfd, const pv_view *v)`
  - `write_view_raw` (function, line 789) `static int write_view_raw(int wfd, const pv_view *v)`
  - `FB_MAX_FILE_BYTES` (function, line 1222) `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...`
  - `budget_remaining_ms` (function, line 1252) `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)`
  - `ctype_is_javascript` (function, line 1266) `static int ctype_is_javascript(const char *ctype)`
  - `ctype_is_css` (function, line 1275) `static int ctype_is_css(const char *ctype)`
  - `log_external_skip` (function, line 1283) `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...`
  - `run` (function, line 1301) `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...`
  - `tab_url_resolve` (function, line 1350) `static int tab_url_resolve(void *ctx, const char *base, const char *ref,
                        ...`
  - `tab_mod_resolve` (function, line 1359) `static int tab_mod_resolve(void *host, const char *base, const char *spec,
                      ...`
  - `tab_mod_fetch` (function, line 1389) `static char *tab_mod_fetch(void *host, const char *url, size_t *len)`
  - `write_history` (function, line 1411) `static int write_history(int wfd, child_state *cs)`
  - `css_text_put` (function, line 1432) `static int css_text_put(css_text *t, const char *s, size_t n)`
  - `css_text_emit` (function, line 1449) `static int css_text_emit(void *ctx, const char *s, size_t n)`
  - `sheet_expand` (function, line 1487) `static int sheet_expand(child_state *cs, const char *base, const char *body, size_t blen,
       ...`
  - `sheets` (function, line 1564) `* sheets (their own text is read from the DOM by page_view). Every failure is
 * fail-open for th...`
  - `child_prescript_view` (function, line 1617) `static pv_view *child_prescript_view(child_state *cs, const char *html, size_t len,
             ...`
  - `child_handle_load` (function, line 1647) `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...`
  - `swap` (function, line 2048) `* display:none hiding an element via class swap (CSS, not
     * DOM removal). */
    if (ok && v...`
  - `write_ws` (function, line 2093) `static int write_ws(int wfd, child_state *cs)`
  - `write_storage` (function, line 2110) `static int write_storage(int wfd, child_state *cs)`
  - `write_opens` (function, line 2124) `static int write_opens(int wfd, child_state *cs)`
  - `child_next_timer_ms` (function, line 2136) `static int32_t child_next_timer_ms(child_state *cs)`
  - `child_handle_mutation` (function, line 2153) `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...`
  - `child_handle_mutation_ex` (function, line 2160) `static void child_handle_mutation_ex(int wfd, child_state *cs, int is_tick,
                     ...`
  - `child_handle_click` (function, line 2259) `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)`
  - `child_handle_event` (function, line 2269) `static void child_handle_event(int wfd, child_state *cs)`
  - `child_handle_mouse` (function, line 2317) `static void child_handle_mouse(int wfd, child_state *cs)`
  - `geom_parent` (function, line 2347) `static dom_node_id geom_parent(void *ctx, dom_node_id n)`
  - `child_handle_geom` (function, line 2355) `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)`
  - `child_handle_submit` (function, line 2382) `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)`
  - `child_handle_eval` (function, line 2416) `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)`
  - `child_handle_decode_image` (function, line 2457) `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)`
  - `child_handle_decode_image_data` (function, line 2484) `static void child_handle_decode_image_data(int wfd, const char *url, size_t len)`
  - `gen_session_key` (function, line 2504) `static uint64_t gen_session_key(void)`
  - `tab_worker_run` (function, line 2524) `static void tab_worker_run(int rfd, int wfd)`
  - `parse_worker_fd` (function, line 2758) `static int parse_worker_fd(const char *s, int *out)`
  - `tab_parse_worker_args` (function, line 2770) `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)`
  - `tab_worker_dispatch` (function, line 2780) `void tab_worker_dispatch(int argc, char **argv)`
  - `ignore_sigpipe` (function, line 2841) `static void ignore_sigpipe(void)`
  - `tab_refresh_alive` (function, line 2848) `static void tab_refresh_alive(tab *t)`
  - `read_field` (function, line 2867) `static int read_field(int fd, char **out, size_t *out_len)`
  - `read_view` (function, line 2884) `static int read_view(int fd, pv_view **out)`
  - `read_view_raw` (function, line 2892) `static int read_view_raw(int fd, pv_view **out)`
  - `read_console` (function, line 3439) `static int read_console(int fd, fb_buffer *out)`
  - `send_request` (function, line 3476) `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)`
  - `io_failure` (function, line 3486) `static tab_status io_failure(tab *t)`
  - `exec_worker_child` (function, line 3494) `static void exec_worker_child(int rfd, int wfd)`
  - `spawn_worker` (function, line 3526) `static tab_status spawn_worker(tab_spawned *sp)`
  - `reap_spawned` (function, line 3556) `static void reap_spawned(const tab_spawned *sp, int kill_it)`
  - `adopt_worker` (function, line 3565) `static tab_status adopt_worker(const tab_spawned *sp, tab **out)`
  - `tab_prewarm` (function, line 3587) `void tab_prewarm(void)`
  - `tab_prewarmed` (function, line 3593) `int tab_prewarmed(void)`
  - `tab_prewarmed_pid` (function, line 3600) `int tab_prewarmed_pid(void)`
  - `tab_shutdown_spare` (function, line 3607) `void tab_shutdown_spare(void)`
  - `tab_open` (function, line 3616) `tab_status tab_open(tab **out)`
  - `tab_set_fetcher` (function, line 3639) `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)`
  - `tab_set_css_sink` (function, line 3645) `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)`
  - `tab_set_op_net_budget_ms` (function, line 3651) `void tab_set_op_net_budget_ms(tab *t, int ms)`
  - `tab_set_net_allowed` (function, line 3655) `void tab_set_net_allowed(tab *t, int allowed)`
  - `tab_set_lazy_ticks` (function, line 3660) `void tab_set_lazy_ticks(tab *t, int on)`
  - `tab_page_keep_view` (function, line 3665) `void tab_page_keep_view(tab_page *prev, tab_page *next)`
  - `tab_set_css_allowed` (function, line 3676) `void tab_set_css_allowed(tab *t, int allowed)`
  - `tab_last_subreq_stats` (function, line 3681) `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)`
  - `tab_set_identity` (function, line 3686) `void tab_set_identity(tab *t, const char *serialized)`
  - `tab_set_frame_id` (function, line 3694) `void tab_set_frame_id(tab *t, int id)`
  - `tab_set_viewport_w` (function, line 3699) `void tab_set_viewport_w(tab *t, int px)`
  - `tab_set_cookies` (function, line 3704) `void tab_set_cookies(tab *t, const char *cookies)`
  - `tab_subreq_permitted` (function, line 3710) `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)`
  - `tab_report_response_headers` (function, line 3724) `void tab_report_response_headers(const char *lines)`
  - `tab_inflight_request_headers` (function, line 3736) `const char *tab_inflight_request_headers(void)`
  - `tab_write_reply` (function, line 3742) `static int tab_write_reply(tab *t, int ok, int status, const char *rbody, size_t rlen,
          ...`
  - `tab_read_subreq_fields` (function, line 3787) `static int tab_read_subreq_fields(tab *t, char **method, char **url, char **body, size_t *blen,
 ...`
  - `tab_op_budget_us` (function, line 3798) `static int64_t tab_op_budget_us(const tab *t)`
  - `tab_note_css_served` (function, line 3802) `static void tab_note_css_served(tab *t, int ok, int status, const char *url, const char *rbody,
 ...`
  - `tab_serve_subreq` (function, line 3818) `static int tab_serve_subreq(tab *t, int net_granted, int css_granted)`
  - `tab_batch_run` (function, line 3845) `static int tab_batch_run(void *vt, const sqb_req *rq, sqb_res *out)`
  - `tab_submit_async` (function, line 3860) `static int tab_submit_async(tab *t, int net_granted, int css_granted)`
  - `tab_serve_netwait` (function, line 3882) `static int tab_serve_netwait(tab *t)`
  - `tab_serve_tag` (function, line 3904) `static int tab_serve_tag(tab *t, uint8_t tag, int net_granted, int css_granted)`
  - `tab_batch_discard` (function, line 3912) `static void tab_batch_discard(tab *t)`
  - `hist_ops_free` (function, line 3917) `static void hist_ops_free(tab_hist_op *ops, size_t n)`
  - `is_activation_event` (function, line 3982) `static int is_activation_event(const char *type)`
  - `open_urls_free` (function, line 3991) `static void open_urls_free(char **u, size_t n)`
  - `read_opens` (function, line 4001) `static tab_status read_opens(tab *t, const char *page_url, int gesture,
                         ...`
  - `ws_ops_free` (function, line 4030) `static void ws_ops_free(tab_ws_op *ops, size_t n)`
  - `read_ws` (function, line 4039) `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)`
  - `gate_js_nav` (function, line 4108) `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)`
  - `tab_load` (function, line 4118) `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)`
  - `tab_load_ex` (function, line 4122) `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)`
  - `tab_load_full` (function, line 4126) `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...`
  - `tab_click` (function, line 4331) `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)`
  - `tab_tick` (function, line 4339) `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)`
  - `tab_submit` (function, line 4349) `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)`
  - `tab_read_view` (function, line 4457) `tab_status tab_read_view(tab *t, tab_page *out)`
  - `tab_await_result` (function, line 4466) `static tab_status tab_await_result(tab *t)`
  - `tab_await_result_inner` (function, line 4474) `static tab_status tab_await_result_inner(tab *t)`
  - `tab_read_view_ex` (function, line 4483) `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)`
  - `tab_eval` (function, line 4588) `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)`
  - `tab_decode_image_op` (function, line 4629) `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...`
  - `tab_decode_image` (function, line 4676) `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)`
  - `tab_decode_image_data_url` (function, line 4683) `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)`
  - `tab_alive` (function, line 4697) `int tab_alive(const tab *t)`
  - `tab_child_pid` (function, line 4703) `pid_t tab_child_pid(const tab *t)`
  - `tab_close` (function, line 4707) `void tab_close(tab *t)`
  - `tab_page_free` (function, line 4725) `void tab_page_free(tab_page *p)`
  - `tab_eval_result_free` (function, line 4755) `void tab_eval_result_free(tab_eval_result *r)`
  - `tab_image_free` (function, line 4764) `void tab_image_free(tab_image *img)`
  - `tab_geometry_send` (function, line 4776) `static tab_status tab_geometry_send(tab *t, const int32_t *buf, size_t words)`
  - `geometry_encode` (function, line 4794) `static int32_t *geometry_encode(const jg_table *g, size_t *words_out)`
  - `tab_set_geometry` (function, line 4804) `tab_status tab_set_geometry(tab *t, const jg_table *g)`
  - `job_discard` (function, line 4818) `static void job_discard(tab *t)`
  - `tab_async_sync` (function, line 4831) `static void tab_async_sync(tab *t)`
  - `job_main` (function, line 4841) `static void *job_main(void *arg)`
  - `tab_async_fd` (function, line 4857) `int tab_async_fd(tab *t)`
  - `tab_async_busy` (function, line 4866) `int tab_async_busy(const tab *t)`
  - `job_start` (function, line 4870) `static tab_status job_start(tab *t)`
  - `tab_tick_async` (function, line 4883) `tab_status tab_tick_async(tab *t, int elapsed_ms)`
  - `tab_geometry_async` (function, line 4893) `tab_status tab_geometry_async(tab *t, const jg_table *g)`
  - `tab_async_finish` (function, line 4908) `tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)`
  - `tab_popstate` (function, line 4930) `tab_status tab_popstate(tab *t, int index, tab_page *out)`
  - `tab_ws_event` (function, line 4937) `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,
       ...`
  - `tab_set_storage` (function, line 4957) `void tab_set_storage(tab *t, const char *blob, size_t len)`
  - `unchanged` (function, line 271) `* is unchanged (spec/sheet_cache.md);`
  - `buffer` (function, line 700) `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...`
  - `blocks` (function, line 770) `* * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the * grid array, block B[26])...`
  - `does` (function, line 1739) `* native browser does (spec/js_native.md). Best effort -- an unsealed page still runs. */ (void)jn_seal(cs->js);`
  - `libraries` (function, line 1756) `* load heavier libraries (jQuery, Bootstrap, etc.) that need more time. * Untrusted hosts get the default budget...`
  - `WHERE` (function, line 1921) `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...`
  - `content` (function, line 1986) `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...`
  - `once` (function, line 2039) `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);`
  - `write_full` (function, line 2069) `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0) && write_view(wfd...`
  - `EPIPE` (function, line 2526) `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();`
  - `tzset` (function, line 2542) `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);`
  - `depth` (function, line 2556) `* defense in depth (seccomp already excludes open/socket/exec);`
  - `load` (function, line 2797) `* subresource requests this load (set per page: host in allow.conf AND js.conf);`
  - `tests` (function, line 2967) `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...`
  - `layout` (function, line 3080) `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....`
  - `column` (function, line 3091) `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...`
  - `frames` (function, line 4463) `* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of...`
  - `_GNU_SOURCE` (macro, line 14) `#define _GNU_SOURCE`
  - `TAB_IOBUF_BYTES` (macro, line 60) `#define TAB_IOBUF_BYTES`
  - `write_full` (macro, line 114) `#define write_full(fd, buf, n)`
  - `read_full` (macro, line 115) `#define read_full(fd, buf, n)`
  - `TAB_SCREEN_W` (macro, line 136) `#define TAB_SCREEN_W`
  - `TAB_SCREEN_H` (macro, line 137) `#define TAB_SCREEN_H`
  - `TAB_WIRE_HEAD_N` (macro, line 141) `#define TAB_WIRE_HEAD_N`
  - `TAB_WIRE_A_N` (macro, line 142) `#define TAB_WIRE_A_N`
  - `TAB_WIRE_B_N` (macro, line 143) `#define TAB_WIRE_B_N`
  - `TAB_WIRE_BOX_F_N` (macro, line 144) `#define TAB_WIRE_BOX_F_N`
  - `TAB_WIRE_GRID_N` (macro, line 145) `#define TAB_WIRE_GRID_N`
  - `TAB_MAX_RUNS` (macro, line 164) `#define TAB_MAX_RUNS`
  - `PV_MAX_CONTAINERS_WIRE` (macro, line 168) `#define PV_MAX_CONTAINERS_WIRE`
  - `TAB_MAX_URL` (macro, line 171) `#define TAB_MAX_URL`
  - `TAB_MAX_WS_MSG` (macro, line 185) `#define TAB_MAX_WS_MSG`
  - `TAB_MAX_STORAGE` (macro, line 189) `#define TAB_MAX_STORAGE`
  - `TAB_MAX_HIST_OPS` (macro, line 193) `#define TAB_MAX_HIST_OPS`
  - `TAB_MAX_HIST_BYTES` (macro, line 194) `#define TAB_MAX_HIST_BYTES`
  - `TAB_MAX_OPENS` (macro, line 196) `#define TAB_MAX_OPENS`
  - `TAB_MAX_OPEN_BYTES` (macro, line 197) `#define TAB_MAX_OPEN_BYTES`
  - `TAB_MAX_GEOM_WORDS` (macro, line 200) `#define TAB_MAX_GEOM_WORDS`
  - `TAB_MAX_ASYNC_PENDING` (macro, line 212) `#define TAB_MAX_ASYNC_PENDING`
  - `TAB_MAX_NET_ROUNDS` (macro, line 213) `#define TAB_MAX_NET_ROUNDS`
  - `TAB_ASYNC_THREADS` (macro, line 214) `#define TAB_ASYNC_THREADS`
  - `TAB_MAX_BATCH_BYTES` (macro, line 215) `#define TAB_MAX_BATCH_BYTES`
  - `TAB_MAX_SUBREQ` (macro, line 219) `#define TAB_MAX_SUBREQ`
  - `TAB_MAX_SUBRESOURCE` (macro, line 220) `#define TAB_MAX_SUBRESOURCE`
  - `TAB_MAX_JS_JOBS` (macro, line 221) `#define TAB_MAX_JS_JOBS`
  - `TAB_CQ_REDERIVE_MAX` (macro, line 294) `#define TAB_CQ_REDERIVE_MAX`
  - `TAB_MAX_EXTERN_CSS` (macro, line 1295) `#define TAB_MAX_EXTERN_CSS`
- Depends on: `include/anti_fp.h`, `include/box_tree.h`, `include/css.h`, `include/css_computed.h`, `include/css_gradient.h`, `include/css_import.h`, `include/data_url.h`, `include/dom.h`, `include/flex_layout.h`, `include/freebug.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/identity.h`, `include/image_decode.h`, `include/import_map.h`, `include/js_dom.h`, `include/js_env.h`, `include/js_native.h`, `include/js_sandbox.h`, `include/js_trusted.h`, `include/link_nav.h`, `include/os_sandbox.h`, `include/page_view.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/sheet_cache.h`, `include/subreq_batch.h`, `include/svg_raster.h`, `include/tab.h`, `include/url.h`, `include/util.h`, `include/web_storage.h`

## src/table_layout.c
- Doc: table_layout (tl_) -- see include/table_layout.h and spec/table_layout.md.
- Layer: presentation
- Language: c
- Symbols:
  - `tl_spread` (function, line 14) `static void tl_spread(double *w, const double *weight, size_t c0, size_t c1, double extra)`
  - `tl_measure` (function, line 23) `static void tl_measure(const tl_cell *cells, size_t n, size_t ncols, double gap,
                ...`
  - `tl_intrinsic` (function, line 78) `void tl_intrinsic(const tl_cell *cells, size_t n, size_t ncols, double gap,
                  dou...`
  - `tl_distribute` (function, line 98) `static void tl_distribute(const double *minw, const double *maxw, const int *sized,
             ...`
  - `tl_columns` (function, line 134) `double tl_columns(const tl_cell *cells, size_t n, size_t ncols, double gap,
                  dou...`
- Depends on: `include/table_layout.h`

## src/text_case.c
- Doc: Latin Extended-A and the Cyrillic historic block pair letters on adjacent code
- Layer: utility
- Language: c
- Symbols:
  - `pair_parity` (function, line 8) `static int pair_parity(uint32_t cp)`
  - `tc_upper` (function, line 18) `uint32_t tc_upper(uint32_t cp)`
  - `tc_lower` (function, line 37) `uint32_t tc_lower(uint32_t cp)`
  - `tc_is_lower` (function, line 54) `int tc_is_lower(uint32_t cp)`
  - `utf8_decode` (function, line 61) `static size_t utf8_decode(const unsigned char *s, size_t n, uint32_t *cp)`
  - `utf8_put` (function, line 79) `static void utf8_put(uint32_t cp, size_t len, unsigned char *out)`
  - `utf8_len_of` (function, line 91) `static size_t utf8_len_of(uint32_t cp)`
  - `tc_transform` (function, line 95) `size_t tc_transform(const char *s, size_t n, int transform, int word_start,
                    c...`
  - `tc_smallcaps_runs` (function, line 117) `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap)`
- Depends on: `include/css.h`, `include/text_case.h`

## src/text_shape.c
- Doc: tsh_fb_cp: Per-code-point verdicts of fb_entry.
- Layer: utility
- Language: c
- Symbols:
  - `tsh_entry` (struct, line 39)
  - `tsh_web` (struct, line 229)
  - `tsh_lfam` (struct, line 588)
  - `tsh_llist` (struct, line 594)
  - `tsh_fb` (struct, line 790)
  - `tsh_cover_ctx` (struct, line 934)
  - `tsh_fb_cp` (struct, line 806)
  - `tsh_measure_slot` (struct, line 1065)
  - `loaded` (type_alias, line 38) `typedef struct tsh_entry { int loaded;`
  - `used` (type_alias, line 228) `typedef struct tsh_web { int used;`
  - `name` (type_alias, line 587) `typedef struct tsh_lfam { char name[TSH_FAMILY_MAX];`
  - `file` (type_alias, line 789) `typedef struct tsh_fb { char file[512];`
  - `entry_opsz_for` (function, line 57) `static int entry_opsz_for(const tsh_entry *e, double px)`
  - `entry_apply_size` (function, line 66) `static void entry_apply_size(tsh_entry *e, double px)`
  - `generic_name` (function, line 93) `static const char *generic_name(int family)`
  - `backend_init` (function, line 103) `static int backend_init(void)`
  - `read_font_file` (function, line 120) `static unsigned char *read_font_file(const char *path, long *out_n)`
  - `load_entry_named` (function, line 141) `static int load_entry_named(tsh_entry *e, const char *fam, int bold, int italic)`
  - `load_entry_file` (function, line 171) `static int load_entry_file(tsh_entry *e, const char *path, int index)`
  - `load_entry` (function, line 207) `static int load_entry(tsh_entry *e, int family, int bold, int italic)`
  - `get_entry` (function, line 211) `static tsh_entry *get_entry(int family, int bold, int italic)`
  - `web_entry_free` (function, line 239) `static void web_entry_free(tsh_web *w)`
  - `web_magic_ok` (function, line 252) `static int web_magic_ok(const unsigned char *b, size_t n)`
  - `web_make_entry` (function, line 309) `static int web_make_entry(tsh_entry *e, const unsigned char *bytes, size_t nbytes, int bold,
    ...`
  - `tsh_face_generation` (function, line 371) `unsigned tsh_face_generation(void)`
  - `tsh_webfont_register` (function, line 373) `int tsh_webfont_register(const char *name,
                         const unsigned char *bytes, s...`
  - `tsh_webfont_clear` (function, line 430) `void tsh_webfont_clear(void)`
  - `web_find` (function, line 436) `static tsh_entry *web_find(unsigned h, int bold, int italic)`
  - `entry_free` (function, line 448) `static void entry_free(tsh_entry *e)`
  - `ascii_ieq` (function, line 461) `static int ascii_ieq(const char *a, const char *b)`
  - `tsh_family_is_generic` (function, line 470) `int tsh_family_is_generic(const char *name)`
  - `tsh_pick_from_list` (function, line 482) `int tsh_pick_from_list(const char *list, tsh_name_resolver resolve, void *ctx,
                  ...`
  - `tsh_pick_family` (function, line 503) `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong,
        ...`
  - `fc_installed` (function, line 516) `static int fc_installed(const char *name, void *ctx)`
  - `fc_resolve` (function, line 559) `static int fc_resolve(const char *name, char *out, size_t cap, void *ctx)`
  - `local_clear` (function, line 604) `static void local_clear(void)`
  - `lfam_index` (function, line 615) `static int lfam_index(const char *fam)`
  - `tsh_local_handle` (function, line 623) `int tsh_local_handle(const char *list)`
  - `local_entry` (function, line 642) `static tsh_entry *local_entry(int handle, int bold, int italic)`
  - `get_entry_ex` (function, line 662) `static tsh_entry *get_entry_ex(const tsh_font *f)`
  - `tsh_ready` (function, line 674) `int tsh_ready(void)`
  - `tsh_shape` (function, line 679) `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                ...`
  - `utf8_next` (function, line 729) `static unsigned utf8_next(const char *s, size_t n, size_t *len)`
  - `is_private_use` (function, line 748) `static int is_private_use(unsigned cp)`
  - `rides_previous` (function, line 753) `static int rides_previous(unsigned cp)`
  - `tsh_segment` (function, line 761) `int tsh_segment(const char *text, size_t len, tsh_cover_fn cover, void *ctx,
                tsh_...`
  - `fb_clear` (function, line 814) `static void fb_clear(void)`
  - `fb_match_covering` (function, line 834) `static FcPattern *fb_match_covering(FcPattern *pat, FcCharSet *cs)`
  - `fb_entry` (function, line 856) `static tsh_entry *fb_entry(unsigned cp, int bold)`
  - `fb_entry_uncached` (function, line 873) `static tsh_entry *fb_entry_uncached(unsigned cp, int bold)`
  - `cover_cp` (function, line 943) `static int cover_cp(unsigned cp, void *vctx)`
  - `shape_entry` (function, line 957) `static tsh_status shape_entry(tsh_entry *e, double px, const char *text, size_t len,
            ...`
  - `shape_runs` (function, line 994) `static tsh_status shape_runs(cairo_t *cr, const tsh_font *f, double px, double x,
               ...`
  - `tsh_measure` (function, line 1075) `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)`
  - `tsh_draw` (function, line 1110) `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, doub...`
  - `tsh_face` (function, line 1117) `cairo_font_face_t *tsh_face(const tsh_font *f)`
  - `tsh_shutdown` (function, line 1123) `void tsh_shutdown(void)`
  - `characters` (function, line 138) `* hold characters ('-', ':') that the pattern syntax treats specially. */ static int load_entry_file(tsh_entry *e...`
  - `slice` (function, line 251) `* woff2 slice (spec/webfont.md);`
  - `blob` (function, line 333) `* blob (it shaped every character to .notdef): its face is built over the tables * FreeType already decoded. A bare...`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
  - `TSH_MAX_FONT_BYTES` (macro, line 33) `#define TSH_MAX_FONT_BYTES`
  - `TSH_CACHE_SLOTS` (macro, line 37) `#define TSH_CACHE_SLOTS`
  - `TSH_WEB_SLOTS` (macro, line 227) `#define TSH_WEB_SLOTS`
  - `TSH_WGHT_REGULAR` (macro, line 267) `#define TSH_WGHT_REGULAR`
  - `TSH_WGHT_BOLD` (macro, line 268) `#define TSH_WGHT_BOLD`
  - `TSH_VAR_AXES_MAX` (macro, line 269) `#define TSH_VAR_AXES_MAX`
  - `TSH_SUBS_MAX` (macro, line 530) `#define TSH_SUBS_MAX`
  - `TSH_BLANK_GLYPH` (macro, line 745) `#define TSH_BLANK_GLYPH`
  - `TSH_FB_SLOTS` (macro, line 787) `#define TSH_FB_SLOTS`
  - `TSH_FB_BLOCKS` (macro, line 788) `#define TSH_FB_BLOCKS`
  - `TSH_FB_CP_SLOTS` (macro, line 805) `#define TSH_FB_CP_SLOTS`
  - `TSH_MAX_RUNS` (macro, line 990) `#define TSH_MAX_RUNS`
  - `TSH_MEASURE_SLOTS` (macro, line 1063) `#define TSH_MEASURE_SLOTS`
  - `TSH_MEASURE_TEXT_MAX` (macro, line 1064) `#define TSH_MEASURE_TEXT_MAX`
- Depends on: `include/css.h`, `include/text_shape.h`, `include/webfont.h`

## src/textfield.c
- Layer: utility
- Language: c
- Symbols:
  - `whole` (function, line 6) `* the buffer is rejected whole (fail closed), never applied partially.
 */

#include "textfield.h...`
  - `tf_clear` (function, line 20) `void tf_clear(tf_field *f)`
  - `tf_set` (function, line 24) `tf_status tf_set(tf_field *f, const char *s)`
  - `tf_insert` (function, line 35) `tf_status tf_insert(tf_field *f, char c)`
  - `tf_backspace` (function, line 47) `void tf_backspace(tf_field *f)`
  - `tf_delete` (function, line 55) `void tf_delete(tf_field *f)`
  - `tf_move` (function, line 62) `void tf_move(tf_field *f, long delta)`
  - `tf_home` (function, line 73) `void tf_home(tf_field *f)`
  - `tf_end` (function, line 78) `void tf_end(tf_field *f)`
  - `tf_text` (function, line 83) `const char *tf_text(const tf_field *f)`
  - `tf_len` (function, line 87) `size_t tf_len(const tf_field *f)`
  - `tf_cursor` (function, line 91) `size_t tf_cursor(const tf_field *f)`
- Depends on: `include/textfield.h`

## src/tls_impersonate.c
- Doc: get_bytes: | ((uint32_t)r->p[r->off + 3] << 24); r->off += 4; return v; } static uint64_t...
- Layer: utility
- Language: c
- Symbols:
  - `ti_wr` (struct, line 33)
  - `ti_rd` (struct, line 63)
  - `ti_should_impersonate` (function, line 18) `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,
                          i...`
  - `bounded_len` (function, line 25) `static size_t bounded_len(const char *s, size_t max)`
  - `put_u8` (function, line 35) `static void put_u8(ti_wr *w, uint8_t v)`
  - `put_u32` (function, line 40) `static void put_u32(ti_wr *w, uint32_t v)`
  - `put_u64` (function, line 48) `static void put_u64(ti_wr *w, uint64_t v)`
  - `put_blob` (function, line 53) `static void put_blob(ti_wr *w, const uint8_t *b, size_t n)`
  - `get_u8` (function, line 65) `static uint8_t get_u8(ti_rd *r)`
  - `get_u32` (function, line 70) `static uint32_t get_u32(ti_rd *r)`
  - `get_u64` (function, line 80) `static uint64_t get_u64(ti_rd *r)`
  - `get_bytes` (function, line 89) `static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len)`
  - `get_str` (function, line 103) `static char *get_str(ti_rd *r, size_t cap)`
  - `valid_profile` (function, line 116) `static int valid_profile(int p)`
  - `ti_encode_req` (function, line 122) `size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap)`
  - `ti_decode_req` (function, line 140) `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out)`
  - `ti_req_free` (function, line 166) `void ti_req_free(ti_req *r)`
  - `ti_encode_resp` (function, line 177) `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap)`
  - `ti_decode_resp` (function, line 196) `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out)`
  - `ti_resp_free` (function, line 230) `void ti_resp_free(ti_resp *r)`
- Depends on: `include/tls_impersonate.h`

## src/ui_layout.c
- Layer: presentation
- Language: c
- Symbols:
  - `layout_push` (function, line 13) `static int layout_push(ui_layout *lay, size_t offset, size_t len)`
  - `ui_wrap_text` (function, line 27) `ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out)`
  - `ui_layout_free` (function, line 91) `void ui_layout_free(ui_layout *lay)`
  - `ui_clamp_scroll` (function, line 99) `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines)`
- Depends on: `include/ui.h`

## src/url.c
- Doc: ci_prefix: produced; every assembly is bounded and reports overflow rather than truncate....
- Layer: utility
- Language: c
- Symbols:
  - `ci_prefix` (function, line 20) `static int ci_prefix(const char *haystack, const char *prefix)`
  - `copy_checked` (function, line 32) `static int copy_checked(char *out, size_t outsz, const char *src)`
  - `cat_checked` (function, line 40) `static int cat_checked(char *out, size_t outsz, const char *src)`
  - `ncat_checked` (function, line 49) `static int ncat_checked(char *out, size_t outsz, const char *src, size_t n)`
  - `url_has_scheme` (function, line 59) `int url_has_scheme(const char *s)`
  - `url_is_https` (function, line 73) `int url_is_https(const char *s)`
  - `url_validate_https` (function, line 80) `url_status url_validate_https(const char *url)`
  - `url_authority_len` (function, line 91) `size_t url_authority_len(const char *url)`
  - `out_pop_segment` (function, line 102) `static void out_pop_segment(char *out, size_t *olen)`
  - `url_remove_dot_segments` (function, line 109) `url_status url_remove_dot_segments(const char *path, char *out, size_t outsz)`
  - `dir_len` (function, line 159) `static size_t dir_len(const char *base)`
  - `url_resolve_https` (function, line 170) `url_status url_resolve_https(const char *base, const char *ref,
                             char...`
  - `is_space` (function, line 218) `static int is_space(int c)`
  - `is_unreserved` (function, line 222) `static int is_unreserved(int c)`
  - `append_query_encoded` (function, line 229) `static int append_query_encoded(char *out, size_t outsz, const char *src)`
  - `assumed` (function, line 254) `* assumed (the caller already routed whitespace to search). */
static int looks_like_host(const c...`
  - `build_search` (function, line 303) `static url_status build_search(const char *query, char *out, size_t outsz)`
  - `url_omnibox` (function, line 309) `url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz)`
  - `host_equals` (function, line 378) `static int host_equals(const url_parts *p, const char *want)`
  - `query_find_q` (function, line 393) `static const char *query_find_q(const char *search, size_t len, size_t *vlen)`
  - `url_search_rewrite` (function, line 411) `url_status url_search_rewrite(const char *url, char *out, size_t outsz)`
  - `url_extract_userinfo` (function, line 431) `url_status url_extract_userinfo(const char *url, char *out, size_t outsz,
                       ...`
  - `url_is_file` (function, line 525) `int url_is_file(const char *s)`
  - `url_file_path` (function, line 531) `const char *url_file_path(const char *s)`
  - `url_resolve_file` (function, line 535) `url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz)`
  - `url_split` (function, line 584) `url_status url_split(const char *url, url_parts *out)`
  - `copy_bounded` (function, line 645) `static url_status copy_bounded(char *out, size_t outsz, const char *a, size_t alen,
             ...`
  - `url_history_target` (function, line 654) `url_status url_history_target(const char *base, const char *ref, char *out, size_t outsz)`
  - `_POSIX_C_SOURCE` (macro, line 9) `#define _POSIX_C_SOURCE`
- Depends on: `include/url.h`

## src/web_storage.c
- Doc: utf8_ok: Well-formed UTF-8, allowing encoded surrogates (WTF-8): a JS string may hold a lone...
- Layer: data_access
- Language: c
- Symbols:
  - `wst_origin` (struct, line 12)
  - `wst_db` (struct, line 20)
  - `key_ref` (struct, line 54)
  - `get_u32` (function, line 25) `static uint32_t get_u32(const unsigned char *p)`
  - `utf8_ok` (function, line 32) `static int utf8_ok(const unsigned char *s, size_t n)`
  - `key_cmp` (function, line 56) `static int key_cmp(const void *a, const void *b)`
  - `check` (function, line 65) `static int check(const char *blob, size_t len, size_t *bytes_out)`
  - `wst_decode_check` (function, line 101) `int wst_decode_check(const char *blob, size_t len)`
  - `wst_new` (function, line 105) `wst_db *wst_new(void)`
  - `wst_free` (function, line 109) `void wst_free(wst_db *db)`
  - `find` (function, line 118) `static wst_origin *find(const wst_db *db, const char *origin)`
  - `wst_encode` (function, line 125) `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len)`
  - `wst_replace` (function, line 140) `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len)`
  - `wst_origin_bytes` (function, line 175) `size_t wst_origin_bytes(const wst_db *db, const char *origin)`
  - `wst_foreach` (function, line 181) `int wst_foreach(const char *blob, size_t len,
                void (*fn)(void *ctx, const char *k...`
  - `put_u32` (function, line 201) `static void put_u32(char *b, uint32_t v)`
  - `wst_pack` (function, line 206) `int wst_pack(const char *const *keys, const size_t *klens,
             const char *const *vals, ...`
- Depends on: `include/web_storage.h`

## src/webcaps.c
- Layer: utility
- Language: c
- Symbols:
  - `wc_safe` (function, line 10) `wc_caps wc_safe(void)`
  - `wc_derive` (function, line 15) `wc_caps wc_derive(wc_input in)`
  - `wc_from_flags` (function, line 35) `wc_caps wc_from_flags(bool js, bool css, bool images)`
  - `wc_render_caps` (function, line 46) `rdp_caps wc_render_caps(wc_caps c)`
- Depends on: `include/webcaps.h`


Next: [KB_src_p10.md](KB_src_p10.md)
