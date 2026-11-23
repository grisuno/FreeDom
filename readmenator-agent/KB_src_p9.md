# Subsystem: src (page 9 of 10)
Previous: [KB_src_p8.md](KB_src_p8.md)

## src/tab.c
- Doc: tab_iobuf: Batched pipe I/O for the view codec. write_view/read_view move one int32 block and...
- Layer: utility
- Language: c
- Symbols:
  - `tab_iobuf` (struct, line 62)
  - `child_state` (struct, line 233)
  - `net_reply` (struct, line 468)
  - `css_text` (struct, line 1486)
  - `tab` (struct, line 2913)
  - `tab_net_fn` (struct, line 4000)
  - `tab_spawned` (struct, line 3642)
  - `fd` (type_alias, line 62) `typedef struct tab_iobuf { int fd;`
  - `status` (type_alias, line 468) `typedef struct net_reply { int32_t status;`
  - `fn` (type_alias, line 4000) `typedef struct tab_net_fn { tab_fetch_fn fn;`
  - `tab_wflush` (function, line 71) `static int tab_wflush(void)`
  - `tab_write_full` (function, line 78) `static int tab_write_full(int fd, const void *buf, size_t n)`
  - `tab_read_full` (function, line 90) `static int tab_read_full(int fd, void *buf, size_t n)`
  - `clip_pm_ok` (function, line 150) `static int clip_pm_ok(int32_t v)`
  - `rad_len_ok` (function, line 156) `static int rad_len_ok(int32_t v, int dflt)`
  - `child_cq_width` (function, line 299) `static int child_cq_width(void *ctx, dom_node_id node)`
  - `child_cq` (function, line 313) `static pv_cq_src *child_cq(child_state *cs)`
  - `child_sheets` (function, line 339) `static shc_cache *child_sheets(child_state *cs)`
  - `child_reset_page` (function, line 344) `static void child_reset_page(child_state *cs)`
  - `sig_mix` (function, line 366) `static uint64_t sig_mix(uint64_t h, const char *s, size_t n)`
  - `computed_signature` (function, line 374) `static uint64_t computed_signature(const dom_index *idx)`
  - `net_reply_free` (function, line 476) `static void net_reply_free(net_reply *r)`
  - `child_write_subreq` (function, line 479) `static int child_write_subreq(child_state *cs, uint8_t tag, const char *method, const char *url,
...`
  - `child_read_reply` (function, line 504) `static int child_read_reply(child_state *cs, net_reply *out)`
  - `child_fetch` (function, line 532) `static int child_fetch(void *vctx, const char *method, const char *url,
                       co...`
  - `child_fetch_async` (function, line 548) `static int child_fetch_async(void *vctx, const char *method, const char *url,
                   ...`
  - `child_net_drain` (function, line 564) `static void child_net_drain(child_state *cs, int settle_ms)`
  - `child_start_parser_async` (function, line 608) `static int child_start_parser_async(child_state *cs, const char *src)`
  - `prof_now_ms` (function, line 643) `static double prof_now_ms(void)`
  - `prof_on` (function, line 648) `static int prof_on(void)`
  - `prof_lap` (function, line 653) `static void prof_lap(const char *what, double *t0)`
  - `run_js` (function, line 664) `* regardless of run_js (a no-JS load simply never records a request). */
/* Installs the page-ind...`
  - `child_load` (function, line 691) `static int child_load(child_state *cs, const char *html, size_t len, int run_js,
                ...`
  - `write_field` (function, line 795) `static int write_field(int fd, const char *s)`
  - `write_view` (function, line 837) `static int write_view(int wfd, const pv_view *v)`
  - `write_view_raw` (function, line 848) `static int write_view_raw(int wfd, const pv_view *v)`
  - `FB_MAX_FILE_BYTES` (function, line 1282) `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...`
  - `budget_remaining_ms` (function, line 1312) `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)`
  - `ctype_is_javascript` (function, line 1326) `static int ctype_is_javascript(const char *ctype)`
  - `ctype_is_css` (function, line 1335) `static int ctype_is_css(const char *ctype)`
  - `log_external_skip` (function, line 1343) `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...`
  - `run` (function, line 1361) `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...`
  - `tab_url_resolve` (function, line 1410) `static int tab_url_resolve(void *ctx, const char *base, const char *ref,
                        ...`
  - `tab_mod_resolve` (function, line 1419) `static int tab_mod_resolve(void *host, const char *base, const char *spec,
                      ...`
  - `tab_mod_fetch` (function, line 1449) `static char *tab_mod_fetch(void *host, const char *url, size_t *len)`
  - `write_history` (function, line 1471) `static int write_history(int wfd, child_state *cs)`
  - `css_text_put` (function, line 1492) `static int css_text_put(css_text *t, const char *s, size_t n)`
  - `css_text_emit` (function, line 1509) `static int css_text_emit(void *ctx, const char *s, size_t n)`
  - `sheet_expand` (function, line 1547) `static int sheet_expand(child_state *cs, const char *base, const char *body, size_t blen,
       ...`
  - `sheets` (function, line 1624) `* sheets (their own text is read from the DOM by page_view). Every failure is
 * fail-open for th...`
  - `child_prescript_view` (function, line 1677) `static pv_view *child_prescript_view(child_state *cs, const char *html, size_t len,
             ...`
  - `child_handle_load` (function, line 1707) `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...`
  - `swap` (function, line 2125) `* display:none hiding an element via class swap (CSS, not
     * DOM removal). */
    if (ok && v...`
  - `write_ws` (function, line 2170) `static int write_ws(int wfd, child_state *cs)`
  - `write_storage` (function, line 2187) `static int write_storage(int wfd, child_state *cs)`
  - `write_opens` (function, line 2201) `static int write_opens(int wfd, child_state *cs)`
  - `child_next_timer_ms` (function, line 2213) `static int32_t child_next_timer_ms(child_state *cs)`
  - `child_handle_mutation` (function, line 2232) `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...`
  - `child_handle_mutation_ex` (function, line 2239) `static void child_handle_mutation_ex(int wfd, child_state *cs, int is_tick,
                     ...`
  - `child_handle_click` (function, line 2340) `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)`
  - `child_handle_event` (function, line 2377) `static void child_handle_event(int wfd, child_state *cs)`
  - `child_handle_mouse` (function, line 2425) `static void child_handle_mouse(int wfd, child_state *cs)`
  - `geom_parent` (function, line 2455) `static dom_node_id geom_parent(void *ctx, dom_node_id n)`
  - `child_handle_geom` (function, line 2463) `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)`
  - `child_handle_submit` (function, line 2490) `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)`
  - `child_handle_eval` (function, line 2524) `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)`
  - `child_handle_decode_image` (function, line 2565) `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)`
  - `child_handle_decode_image_data` (function, line 2592) `static void child_handle_decode_image_data(int wfd, const char *url, size_t len)`
  - `gen_session_key` (function, line 2612) `static uint64_t gen_session_key(void)`
  - `tab_worker_run` (function, line 2632) `static void tab_worker_run(int rfd, int wfd)`
  - `parse_worker_fd` (function, line 2881) `static int parse_worker_fd(const char *s, int *out)`
  - `tab_parse_worker_args` (function, line 2893) `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)`
  - `tab_worker_dispatch` (function, line 2903) `void tab_worker_dispatch(int argc, char **argv)`
  - `ignore_sigpipe` (function, line 2968) `static void ignore_sigpipe(void)`
  - `tab_refresh_alive` (function, line 2975) `static void tab_refresh_alive(tab *t)`
  - `read_field` (function, line 2994) `static int read_field(int fd, char **out, size_t *out_len)`
  - `read_view` (function, line 3011) `static int read_view(int fd, pv_view **out)`
  - `read_view_raw` (function, line 3019) `static int read_view_raw(int fd, pv_view **out)`
  - `read_console` (function, line 3567) `static int read_console(int fd, fb_buffer *out)`
  - `send_request` (function, line 3604) `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)`
  - `io_failure` (function, line 3614) `static tab_status io_failure(tab *t)`
  - `exec_worker_child` (function, line 3622) `static void exec_worker_child(int rfd, int wfd)`
  - `spawn_worker` (function, line 3654) `static tab_status spawn_worker(tab_spawned *sp)`
  - `reap_spawned` (function, line 3684) `static void reap_spawned(const tab_spawned *sp, int kill_it)`
  - `adopt_worker` (function, line 3693) `static tab_status adopt_worker(const tab_spawned *sp, tab **out)`
  - `tab_prewarm` (function, line 3715) `void tab_prewarm(void)`
  - `tab_prewarmed` (function, line 3721) `int tab_prewarmed(void)`
  - `tab_prewarmed_pid` (function, line 3728) `int tab_prewarmed_pid(void)`
  - `tab_shutdown_spare` (function, line 3735) `void tab_shutdown_spare(void)`
  - `tab_open` (function, line 3744) `tab_status tab_open(tab **out)`
  - `tab_set_fetcher` (function, line 3767) `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)`
  - `tab_retire_batch` (function, line 3773) `static void tab_retire_batch(tab *t)`
  - `tab_set_async_fetcher` (function, line 3784) `void tab_set_async_fetcher(tab *t, tab_fetch_fn fn, void *ctx, void (*free_ctx)(void *))`
  - `tab_set_css_sink` (function, line 3792) `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)`
  - `tab_set_op_net_budget_ms` (function, line 3798) `void tab_set_op_net_budget_ms(tab *t, int ms)`
  - `tab_set_net_allowed` (function, line 3802) `void tab_set_net_allowed(tab *t, int allowed)`
  - `tab_set_lazy_ticks` (function, line 3807) `void tab_set_lazy_ticks(tab *t, int on)`
  - `tab_page_keep_view` (function, line 3812) `void tab_page_keep_view(tab_page *prev, tab_page *next)`
  - `tab_set_css_allowed` (function, line 3823) `void tab_set_css_allowed(tab *t, int allowed)`
  - `tab_last_subreq_stats` (function, line 3828) `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)`
  - `tab_set_identity` (function, line 3833) `void tab_set_identity(tab *t, const char *serialized)`
  - `tab_set_frame_id` (function, line 3841) `void tab_set_frame_id(tab *t, int id)`
  - `tab_set_viewport_w` (function, line 3846) `void tab_set_viewport_w(tab *t, int px)`
  - `tab_set_cookies` (function, line 3851) `void tab_set_cookies(tab *t, const char *cookies)`
  - `tab_subreq_permitted` (function, line 3857) `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)`
  - `tab_report_response_headers` (function, line 3871) `void tab_report_response_headers(const char *lines)`
  - `tab_inflight_request_headers` (function, line 3883) `const char *tab_inflight_request_headers(void)`
  - `tab_write_reply` (function, line 3889) `static int tab_write_reply(tab *t, int ok, int status, const char *rbody, size_t rlen,
          ...`
  - `tab_fetch_one` (function, line 3933) `static int tab_fetch_one(tab *t, const char *method, const char *url, const char *body, size_t bl...`
  - `tab_read_subreq_fields` (function, line 3941) `static int tab_read_subreq_fields(tab *t, char **method, char **url, char **body, size_t *blen,
 ...`
  - `tab_op_budget_us` (function, line 3952) `static int64_t tab_op_budget_us(const tab *t)`
  - `tab_note_css_served` (function, line 3956) `static void tab_note_css_served(tab *t, int ok, int status, const char *url, const char *rbody,
 ...`
  - `tab_serve_subreq` (function, line 3972) `static int tab_serve_subreq(tab *t, int net_granted, int css_granted)`
  - `tab_net_fn_free` (function, line 4002) `static void tab_net_fn_free(void *p)`
  - `tab_batch_fill` (function, line 4009) `static int tab_batch_fill(int ok, int status, char *rbody, size_t rlen, char *rctype, char *rhdrs...`
  - `tab_batch_run_stable` (function, line 4017) `static int tab_batch_run_stable(void *vn, const sqb_req *rq, sqb_res *out)`
  - `tab_batch_run` (function, line 4025) `static int tab_batch_run(void *vt, const sqb_req *rq, sqb_res *out)`
  - `tab_batch` (function, line 4035) `static sqb *tab_batch(tab *t)`
  - `tab_submit_async` (function, line 4058) `static int tab_submit_async(tab *t, int net_granted, int css_granted)`
  - `tab_serve_netwait` (function, line 4082) `static int tab_serve_netwait(tab *t)`
  - `tab_serve_tag` (function, line 4113) `static int tab_serve_tag(tab *t, uint8_t tag, int net_granted, int css_granted)`
  - `tab_batch_discard` (function, line 4121) `static void tab_batch_discard(tab *t)`
  - `hist_ops_free` (function, line 4129) `static void hist_ops_free(tab_hist_op *ops, size_t n)`
  - `is_activation_event` (function, line 4194) `static int is_activation_event(const char *type)`
  - `open_urls_free` (function, line 4203) `static void open_urls_free(char **u, size_t n)`
  - `read_opens` (function, line 4213) `static tab_status read_opens(tab *t, const char *page_url, int gesture,
                         ...`
  - `ws_ops_free` (function, line 4242) `static void ws_ops_free(tab_ws_op *ops, size_t n)`
  - `read_ws` (function, line 4251) `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)`
  - `gate_js_nav` (function, line 4320) `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)`
  - `tab_load` (function, line 4330) `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)`
  - `tab_load_ex` (function, line 4334) `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)`
  - `tab_load_full` (function, line 4338) `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...`
  - `tab_click` (function, line 4543) `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)`
  - `tab_tick` (function, line 4551) `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)`
  - `tab_submit` (function, line 4561) `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)`
  - `tab_read_view` (function, line 4669) `tab_status tab_read_view(tab *t, tab_page *out)`
  - `tab_await_result` (function, line 4678) `static tab_status tab_await_result(tab *t)`
  - `tab_await_result_inner` (function, line 4686) `static tab_status tab_await_result_inner(tab *t)`
  - `tab_read_view_ex` (function, line 4695) `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)`
  - `tab_eval` (function, line 4802) `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)`
  - `tab_decode_image_op` (function, line 4843) `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...`
  - `tab_decode_image` (function, line 4890) `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)`
  - `tab_decode_image_data_url` (function, line 4897) `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)`
  - `tab_alive` (function, line 4911) `int tab_alive(const tab *t)`
  - `tab_child_pid` (function, line 4917) `pid_t tab_child_pid(const tab *t)`
  - `tab_close` (function, line 4921) `void tab_close(tab *t)`
  - `tab_page_free` (function, line 4939) `void tab_page_free(tab_page *p)`
  - `tab_eval_result_free` (function, line 4969) `void tab_eval_result_free(tab_eval_result *r)`
  - `tab_image_free` (function, line 4978) `void tab_image_free(tab_image *img)`
  - `tab_geometry_send` (function, line 4990) `static tab_status tab_geometry_send(tab *t, const int32_t *buf, size_t words)`
  - `geometry_encode` (function, line 5008) `static int32_t *geometry_encode(const jg_table *g, size_t *words_out)`
  - `tab_set_geometry` (function, line 5018) `tab_status tab_set_geometry(tab *t, const jg_table *g)`
  - `job_discard` (function, line 5032) `static void job_discard(tab *t)`
  - `tab_async_sync` (function, line 5045) `static void tab_async_sync(tab *t)`
  - `job_main` (function, line 5055) `static void *job_main(void *arg)`
  - `tab_async_fd` (function, line 5071) `int tab_async_fd(tab *t)`
  - `tab_async_busy` (function, line 5080) `int tab_async_busy(const tab *t)`
  - `job_start` (function, line 5084) `static tab_status job_start(tab *t)`
  - `tab_tick_async` (function, line 5097) `tab_status tab_tick_async(tab *t, int elapsed_ms)`
  - `tab_geometry_async` (function, line 5107) `tab_status tab_geometry_async(tab *t, const jg_table *g)`
  - `tab_async_finish` (function, line 5122) `tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)`
  - `tab_popstate` (function, line 5144) `tab_status tab_popstate(tab *t, int index, tab_page *out)`
  - `tab_ws_event` (function, line 5151) `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,
       ...`
  - `tab_set_storage` (function, line 5171) `void tab_set_storage(tab *t, const char *blob, size_t len)`
  - `tab_anchor_free` (function, line 5184) `void tab_anchor_free(tab_anchor *a)`
  - `tab_anchor_query` (function, line 5190) `tab_status tab_anchor_query(tab *t, const char *fragment, const char *push_url,
                 ...`
  - `unchanged` (function, line 272) `* is unchanged (spec/sheet_cache.md);`
  - `buffer` (function, line 759) `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...`
  - `blocks` (function, line 829) `* * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the * grid array, block B[26])...`
  - `does` (function, line 1799) `* native browser does (spec/js_native.md). Best effort -- an unsealed page still runs. */ (void)jn_seal(cs->js);`
  - `libraries` (function, line 1816) `* load heavier libraries (jQuery, Bootstrap, etc.) that need more time. * Untrusted hosts get the default budget...`
  - `WHERE` (function, line 1986) `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...`
  - `content` (function, line 2063) `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...`
  - `once` (function, line 2116) `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);`
  - `write_full` (function, line 2146) `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0) && write_view(wfd...`
  - `EPIPE` (function, line 2634) `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();`
  - `tzset` (function, line 2650) `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);`
  - `depth` (function, line 2664) `* defense in depth (seccomp already excludes open/socket/exec);`
  - `load` (function, line 2920) `* subresource requests this load (set per page: host in allow.conf AND js.conf);`
  - `tests` (function, line 3094) `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...`
  - `layout` (function, line 3207) `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....`
  - `column` (function, line 3218) `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...`
  - `fn` (function, line 3925) `&& fn(fctx, method, url, body, blen, status, rbody, rlen, rctype) == 0);`
  - `frames` (function, line 4675) `* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of...`
  - `_GNU_SOURCE` (macro, line 14) `#define _GNU_SOURCE`
  - `TAB_IOBUF_BYTES` (macro, line 61) `#define TAB_IOBUF_BYTES`
  - `write_full` (macro, line 115) `#define write_full(fd, buf, n)`
  - `read_full` (macro, line 116) `#define read_full(fd, buf, n)`
  - `TAB_SCREEN_W` (macro, line 137) `#define TAB_SCREEN_W`
  - `TAB_SCREEN_H` (macro, line 138) `#define TAB_SCREEN_H`
  - `TAB_WIRE_HEAD_N` (macro, line 142) `#define TAB_WIRE_HEAD_N`
  - `TAB_WIRE_A_N` (macro, line 143) `#define TAB_WIRE_A_N`
  - `TAB_WIRE_B_N` (macro, line 144) `#define TAB_WIRE_B_N`
  - `TAB_WIRE_BOX_F_N` (macro, line 145) `#define TAB_WIRE_BOX_F_N`
  - `TAB_WIRE_GRID_N` (macro, line 146) `#define TAB_WIRE_GRID_N`
  - `TAB_MAX_RUNS` (macro, line 165) `#define TAB_MAX_RUNS`
  - `PV_MAX_CONTAINERS_WIRE` (macro, line 169) `#define PV_MAX_CONTAINERS_WIRE`
  - `TAB_MAX_URL` (macro, line 172) `#define TAB_MAX_URL`
  - `TAB_MAX_WS_MSG` (macro, line 186) `#define TAB_MAX_WS_MSG`
  - `TAB_MAX_STORAGE` (macro, line 190) `#define TAB_MAX_STORAGE`
  - `TAB_MAX_HIST_OPS` (macro, line 194) `#define TAB_MAX_HIST_OPS`
  - `TAB_MAX_HIST_BYTES` (macro, line 195) `#define TAB_MAX_HIST_BYTES`
  - `TAB_MAX_OPENS` (macro, line 197) `#define TAB_MAX_OPENS`
  - `TAB_MAX_OPEN_BYTES` (macro, line 198) `#define TAB_MAX_OPEN_BYTES`
  - `TAB_MAX_GEOM_WORDS` (macro, line 201) `#define TAB_MAX_GEOM_WORDS`
  - `TAB_MAX_ASYNC_PENDING` (macro, line 213) `#define TAB_MAX_ASYNC_PENDING`
  - `TAB_MAX_NET_ROUNDS` (macro, line 214) `#define TAB_MAX_NET_ROUNDS`
  - `TAB_ASYNC_THREADS` (macro, line 215) `#define TAB_ASYNC_THREADS`
  - `TAB_MAX_BATCH_BYTES` (macro, line 216) `#define TAB_MAX_BATCH_BYTES`
  - `TAB_MAX_SUBREQ` (macro, line 220) `#define TAB_MAX_SUBREQ`
  - `TAB_MAX_SUBRESOURCE` (macro, line 221) `#define TAB_MAX_SUBRESOURCE`
  - `TAB_MAX_JS_JOBS` (macro, line 222) `#define TAB_MAX_JS_JOBS`
  - `TAB_CQ_REDERIVE_MAX` (macro, line 295) `#define TAB_CQ_REDERIVE_MAX`
  - `TAB_MAX_EXTERN_CSS` (macro, line 1355) `#define TAB_MAX_EXTERN_CSS`
- Depends on: `include/anchor.h`, `include/anti_fp.h`, `include/box_tree.h`, `include/css.h`, `include/css_computed.h`, `include/css_gradient.h`, `include/css_import.h`, `include/data_url.h`, `include/dom.h`, `include/flex_layout.h`, `include/freebug.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/identity.h`, `include/image_decode.h`, `include/import_map.h`, `include/js_dom.h`, `include/js_env.h`, `include/js_native.h`, `include/js_sandbox.h`, `include/js_trusted.h`, `include/link_nav.h`, `include/os_sandbox.h`, `include/page_view.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/sheet_cache.h`, `include/subreq_batch.h`, `include/svg_raster.h`, `include/tab.h`, `include/url.h`, `include/util.h`, `include/web_storage.h`

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
  - `url_split_location` (function, line 688) `url_status url_split_location(const char *url, url_parts *out)`
  - `_POSIX_C_SOURCE` (macro, line 9) `#define _POSIX_C_SOURCE`
- Depends on: `include/url.h`

## src/video_controls.c
- Layer: utility
- Language: c
- Symbols:
  - `finite4` (function, line 7) `static int finite4(double a, double b, double c, double d)`
  - `in_rect` (function, line 11) `static int in_rect(const vcl_rect *r, double px, double py)`
  - `vcl_layout` (function, line 15) `int vcl_layout(double x, double y, double w, double h, vcl_geom *g)`
  - `vcl_clamp_frac` (function, line 34) `double vcl_clamp_frac(double f)`
  - `vcl_hit` (function, line 39) `vcl_hit_kind vcl_hit(const vcl_geom *g, const vcl_rect *video, double px, double py,
            ...`
  - `vcl_seg_duration` (function, line 54) `double vcl_seg_duration(double d)`
  - `vcl_total` (function, line 59) `double vcl_total(const hls_playlist *pl)`
  - `vcl_segment_at` (function, line 66) `size_t vcl_segment_at(const hls_playlist *pl, double t, double *start)`
  - `vcl_segment_start` (function, line 82) `double vcl_segment_start(const hls_playlist *pl, size_t idx)`
  - `vcl_position` (function, line 90) `double vcl_position(double base_s, int64_t pts0_us, int64_t pts_us, double total)`
  - `vcl_format_time` (function, line 99) `size_t vcl_format_time(double seconds, char *buf, size_t cap)`
- Depends on: `include/video_controls.h`


Next: [KB_src_p10.md](KB_src_p10.md)
