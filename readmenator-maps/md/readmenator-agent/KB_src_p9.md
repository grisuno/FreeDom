# Subsystem: src (page 9 of 10)
Previous: [KB_src_p8.md](KB_src_p8.md)

## src/tab.c
- Doc: clip_pm_ok: A clip-edge percentage off the wire: per-mille, bounded like CSS_PCT_MAX (a hostile...
- Layer: utility
- Language: c
- Symbols:
  - `child_state` (struct, line 146)
  - `tab` (struct, line 2274)
  - `clip_pm_ok` (function, line 77) `static int clip_pm_ok(int32_t v)`
  - `rad_len_ok` (function, line 83) `static int rad_len_ok(int32_t v, int dflt)`
  - `child_reset_page` (function, line 185) `static void child_reset_page(child_state *cs)`
  - `sig_mix` (function, line 205) `static uint64_t sig_mix(uint64_t h, const char *s, size_t n)`
  - `computed_signature` (function, line 213) `static uint64_t computed_signature(const dom_index *idx)`
  - `policy` (function, line 302) `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a
 * compromi...`
  - `prof_now_ms` (function, line 368) `static double prof_now_ms(void)`
  - `prof_on` (function, line 373) `static int prof_on(void)`
  - `prof_lap` (function, line 378) `static void prof_lap(const char *what, double *t0)`
  - `run_js` (function, line 389) `* regardless of run_js (a no-JS load simply never records a request). */
static int child_load(ch...`
  - `write_field` (function, line 469) `static int write_field(int fd, const char *s)`
  - `blocks` (function, line 503) `*
 * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the
 * grid arr...`
  - `FB_MAX_FILE_BYTES` (function, line 935) `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...`
  - `budget_remaining_ms` (function, line 965) `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)`
  - `ctype_is_javascript` (function, line 979) `static int ctype_is_javascript(const char *ctype)`
  - `ctype_is_css` (function, line 988) `static int ctype_is_css(const char *ctype)`
  - `log_external_skip` (function, line 996) `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...`
  - `run` (function, line 1014) `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...`
  - `tab_url_resolve` (function, line 1063) `static int tab_url_resolve(void *ctx, const char *base, const char *ref,
                        ...`
  - `tab_mod_resolve` (function, line 1072) `static int tab_mod_resolve(void *host, const char *base, const char *spec,
                      ...`
  - `tab_mod_fetch` (function, line 1102) `static char *tab_mod_fetch(void *host, const char *url, size_t *len)`
  - `write_history` (function, line 1124) `static int write_history(int wfd, child_state *cs)`
  - `window` (function, line 1143) `* net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs)`
  - `child_handle_load` (function, line 1188) `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...`
  - `swap` (function, line 1577) `* display:none hiding an element via class swap (CSS, not
     * DOM removal). */
    if (ok && v...`
  - `write_ws` (function, line 1622) `static int write_ws(int wfd, child_state *cs)`
  - `write_storage` (function, line 1639) `static int write_storage(int wfd, child_state *cs)`
  - `write_opens` (function, line 1653) `static int write_opens(int wfd, child_state *cs)`
  - `child_next_timer_ms` (function, line 1665) `static int32_t child_next_timer_ms(child_state *cs)`
  - `child_handle_mutation` (function, line 1680) `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...`
  - `child_handle_click` (function, line 1760) `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)`
  - `child_handle_tick` (function, line 1764) `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)`
  - `child_handle_event` (function, line 1774) `static void child_handle_event(int wfd, child_state *cs)`
  - `child_handle_mouse` (function, line 1822) `static void child_handle_mouse(int wfd, child_state *cs)`
  - `geom_parent` (function, line 1852) `static dom_node_id geom_parent(void *ctx, dom_node_id n)`
  - `child_handle_geom` (function, line 1860) `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)`
  - `child_handle_submit` (function, line 1886) `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)`
  - `child_handle_eval` (function, line 1920) `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)`
  - `child_handle_decode_image` (function, line 1961) `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)`
  - `child_handle_decode_image_b64` (function, line 1983) `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)`
  - `gen_session_key` (function, line 1995) `static uint64_t gen_session_key(void)`
  - `tab_worker_run` (function, line 2015) `static void tab_worker_run(int rfd, int wfd)`
  - `parse_worker_fd` (function, line 2242) `static int parse_worker_fd(const char *s, int *out)`
  - `tab_parse_worker_args` (function, line 2254) `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)`
  - `tab_worker_dispatch` (function, line 2264) `void tab_worker_dispatch(int argc, char **argv)`
  - `ignore_sigpipe` (function, line 2319) `static void ignore_sigpipe(void)`
  - `tab_refresh_alive` (function, line 2326) `static void tab_refresh_alive(tab *t)`
  - `read_field` (function, line 2345) `static int read_field(int fd, char **out, size_t *out_len)`
  - `read_view` (function, line 2361) `static int read_view(int fd, pv_view **out)`
  - `read_console` (function, line 2889) `static int read_console(int fd, fb_buffer *out)`
  - `send_request` (function, line 2926) `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)`
  - `io_failure` (function, line 2936) `static tab_status io_failure(tab *t)`
  - `exec_worker_child` (function, line 2944) `static void exec_worker_child(int rfd, int wfd)`
  - `tab_set_fetcher` (function, line 3016) `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)`
  - `tab_set_css_sink` (function, line 3022) `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)`
  - `tab_set_op_net_budget_ms` (function, line 3028) `void tab_set_op_net_budget_ms(tab *t, int ms)`
  - `tab_set_net_allowed` (function, line 3032) `void tab_set_net_allowed(tab *t, int allowed)`
  - `tab_set_css_allowed` (function, line 3037) `void tab_set_css_allowed(tab *t, int allowed)`
  - `tab_last_subreq_stats` (function, line 3042) `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)`
  - `tab_set_identity` (function, line 3047) `void tab_set_identity(tab *t, const char *serialized)`
  - `tab_set_frame_id` (function, line 3055) `void tab_set_frame_id(tab *t, int id)`
  - `tab_set_viewport_w` (function, line 3060) `void tab_set_viewport_w(tab *t, int px)`
  - `tab_set_cookies` (function, line 3065) `void tab_set_cookies(tab *t, const char *cookies)`
  - `tab_subreq_permitted` (function, line 3071) `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)`
  - `tab_report_response_headers` (function, line 3085) `void tab_report_response_headers(const char *lines)`
  - `tab_inflight_request_headers` (function, line 3097) `const char *tab_inflight_request_headers(void)`
  - `answered` (function, line 3106) `* A refused frame is still consumed and answered (status 0), so the protocol never
 * desyncs. Re...`
  - `hist_ops_free` (function, line 3179) `static void hist_ops_free(tab_hist_op *ops, size_t n)`
  - `is_activation_event` (function, line 3244) `static int is_activation_event(const char *type)`
  - `open_urls_free` (function, line 3253) `static void open_urls_free(char **u, size_t n)`
  - `read_opens` (function, line 3263) `static tab_status read_opens(tab *t, const char *page_url, int gesture,
                         ...`
  - `ws_ops_free` (function, line 3292) `static void ws_ops_free(tab_ws_op *ops, size_t n)`
  - `read_ws` (function, line 3301) `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)`
  - `gate_js_nav` (function, line 3370) `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)`
  - `tab_load` (function, line 3380) `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)`
  - `tab_load_ex` (function, line 3384) `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)`
  - `tab_load_full` (function, line 3388) `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...`
  - `tab_click` (function, line 3589) `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)`
  - `tab_tick` (function, line 3597) `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)`
  - `tab_submit` (function, line 3607) `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)`
  - `tab_read_view` (function, line 3715) `tab_status tab_read_view(tab *t, tab_page *out)`
  - `tab_await_result` (function, line 3724) `static tab_status tab_await_result(tab *t)`
  - `tab_await_result_inner` (function, line 3732) `static tab_status tab_await_result_inner(tab *t)`
  - `tab_read_view_ex` (function, line 3742) `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)`
  - `tab_eval` (function, line 3837) `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)`
  - `tab_decode_image_op` (function, line 3878) `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...`
  - `tab_decode_image` (function, line 3920) `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)`
  - `tab_decode_image_data_url` (function, line 3927) `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)`
  - `tab_alive` (function, line 3946) `int tab_alive(const tab *t)`
  - `tab_child_pid` (function, line 3952) `pid_t tab_child_pid(const tab *t)`
  - `tab_close` (function, line 3956) `void tab_close(tab *t)`
  - `tab_page_free` (function, line 3973) `void tab_page_free(tab_page *p)`
  - `tab_eval_result_free` (function, line 4003) `void tab_eval_result_free(tab_eval_result *r)`
  - `tab_image_free` (function, line 4012) `void tab_image_free(tab_image *img)`
  - `tab_geometry_send` (function, line 4024) `static tab_status tab_geometry_send(tab *t, const int32_t *buf, size_t words)`
  - `geometry_encode` (function, line 4042) `static int32_t *geometry_encode(const jg_table *g, size_t *words_out)`
  - `tab_set_geometry` (function, line 4052) `tab_status tab_set_geometry(tab *t, const jg_table *g)`
  - `job_discard` (function, line 4066) `static void job_discard(tab *t)`
  - `tab_async_sync` (function, line 4078) `static void tab_async_sync(tab *t)`
  - `job_main` (function, line 4088) `static void *job_main(void *arg)`
  - `tab_async_fd` (function, line 4104) `int tab_async_fd(tab *t)`
  - `tab_async_busy` (function, line 4113) `int tab_async_busy(const tab *t)`
  - `job_start` (function, line 4117) `static tab_status job_start(tab *t)`
  - `tab_tick_async` (function, line 4130) `tab_status tab_tick_async(tab *t, int elapsed_ms)`
  - `tab_geometry_async` (function, line 4140) `tab_status tab_geometry_async(tab *t, const jg_table *g)`
  - `tab_async_finish` (function, line 4155) `tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)`
  - `tab_popstate` (function, line 4177) `tab_status tab_popstate(tab *t, int index, tab_page *out)`
  - `tab_ws_event` (function, line 4184) `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,
       ...`
  - `tab_set_storage` (function, line 4204) `void tab_set_storage(tab *t, const char *blob, size_t len)`
  - `buffer` (function, line 438) `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...`
  - `fallback` (function, line 1269) `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it...`
  - `WHERE` (function, line 1459) `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...`
  - `content` (function, line 1519) `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...`
  - `once` (function, line 1568) `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);`
  - `write_full` (function, line 1598) `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0) && write_view(wfd...`
  - `EPIPE` (function, line 2017) `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();`
  - `tzset` (function, line 2033) `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);`
  - `depth` (function, line 2047) `* defense in depth (seccomp already excludes open/socket/exec);`
  - `load` (function, line 2281) `* subresource requests this load (set per page: host in allow.conf AND js.conf);`
  - `tests` (function, line 2436) `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...`
  - `layout` (function, line 2543) `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....`
  - `column` (function, line 2554) `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...`
  - `frames` (function, line 3721) `* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of...`
  - `_GNU_SOURCE` (macro, line 14) `#define _GNU_SOURCE`
  - `TAB_SCREEN_W` (macro, line 64) `#define TAB_SCREEN_W`
  - `TAB_SCREEN_H` (macro, line 65) `#define TAB_SCREEN_H`
  - `TAB_WIRE_HEAD_N` (macro, line 69) `#define TAB_WIRE_HEAD_N`
  - `TAB_WIRE_A_N` (macro, line 70) `#define TAB_WIRE_A_N`
  - `TAB_WIRE_B_N` (macro, line 71) `#define TAB_WIRE_B_N`
  - `TAB_WIRE_BOX_F_N` (macro, line 72) `#define TAB_WIRE_BOX_F_N`
  - `TAB_WIRE_GRID_N` (macro, line 73) `#define TAB_WIRE_GRID_N`
  - `TAB_MAX_RUNS` (macro, line 92) `#define TAB_MAX_RUNS`
  - `PV_MAX_CONTAINERS_WIRE` (macro, line 96) `#define PV_MAX_CONTAINERS_WIRE`
  - `TAB_MAX_URL` (macro, line 99) `#define TAB_MAX_URL`
  - `TAB_MAX_WS_MSG` (macro, line 108) `#define TAB_MAX_WS_MSG`
  - `TAB_MAX_STORAGE` (macro, line 112) `#define TAB_MAX_STORAGE`
  - `TAB_MAX_HIST_OPS` (macro, line 116) `#define TAB_MAX_HIST_OPS`
  - `TAB_MAX_HIST_BYTES` (macro, line 117) `#define TAB_MAX_HIST_BYTES`
  - `TAB_MAX_OPENS` (macro, line 119) `#define TAB_MAX_OPENS`
  - `TAB_MAX_OPEN_BYTES` (macro, line 120) `#define TAB_MAX_OPEN_BYTES`
  - `TAB_MAX_GEOM_WORDS` (macro, line 123) `#define TAB_MAX_GEOM_WORDS`
  - `TAB_MAX_SUBREQ` (macro, line 133) `#define TAB_MAX_SUBREQ`
  - `TAB_MAX_SUBRESOURCE` (macro, line 134) `#define TAB_MAX_SUBRESOURCE`
  - `TAB_MAX_JS_JOBS` (macro, line 135) `#define TAB_MAX_JS_JOBS`
  - `TAB_MAX_EXTERN_CSS` (macro, line 1008) `#define TAB_MAX_EXTERN_CSS`
- Depends on: `include/anti_fp.h`, `include/box_tree.h`, `include/css.h`, `include/css_computed.h`, `include/css_gradient.h`, `include/data_url.h`, `include/dom.h`, `include/flex_layout.h`, `include/freebug.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/identity.h`, `include/image_decode.h`, `include/import_map.h`, `include/js_dom.h`, `include/js_env.h`, `include/js_sandbox.h`, `include/js_trusted.h`, `include/link_nav.h`, `include/os_sandbox.h`, `include/page_view.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/tab.h`, `include/url.h`, `include/util.h`, `include/web_storage.h`

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
- Doc: load_entry_file: Loads face `index` of the font file at `path` into e (FreeType + cairo + *...
- Layer: utility
- Language: c
- Symbols:
  - `tsh_entry` (struct, line 35)
  - `tsh_web` (struct, line 191)
  - `tsh_lfam` (struct, line 458)
  - `tsh_llist` (struct, line 464)
  - `tsh_fb` (struct, line 658)
  - `tsh_cover_ctx` (struct, line 741)
  - `loaded` (type_alias, line 34) `typedef struct tsh_entry { int loaded;`
  - `used` (type_alias, line 190) `typedef struct tsh_web { int used;`
  - `name` (type_alias, line 457) `typedef struct tsh_lfam { char name[TSH_FAMILY_MAX];`
  - `file` (type_alias, line 657) `typedef struct tsh_fb { char file[512];`
  - `generic_name` (function, line 55) `static const char *generic_name(int family)`
  - `backend_init` (function, line 65) `static int backend_init(void)`
  - `read_font_file` (function, line 82) `static unsigned char *read_font_file(const char *path, long *out_n)`
  - `load_entry_named` (function, line 103) `static int load_entry_named(tsh_entry *e, const char *fam, int bold, int italic)`
  - `load_entry_file` (function, line 133) `static int load_entry_file(tsh_entry *e, const char *path, int index)`
  - `load_entry` (function, line 169) `static int load_entry(tsh_entry *e, int family, int bold, int italic)`
  - `get_entry` (function, line 173) `static tsh_entry *get_entry(int family, int bold, int italic)`
  - `web_entry_free` (function, line 201) `static void web_entry_free(tsh_web *w)`
  - `web_magic_ok` (function, line 214) `static int web_magic_ok(const unsigned char *b, size_t n)`
  - `web_make_entry` (function, line 227) `static int web_make_entry(tsh_entry *e, const unsigned char *bytes, size_t nbytes)`
  - `tsh_webfont_register` (function, line 267) `int tsh_webfont_register(const char *name,
                         const unsigned char *bytes, s...`
  - `tsh_webfont_clear` (function, line 301) `void tsh_webfont_clear(void)`
  - `web_find` (function, line 306) `static tsh_entry *web_find(unsigned h, int bold, int italic)`
  - `entry_free` (function, line 318) `static void entry_free(tsh_entry *e)`
  - `ascii_ieq` (function, line 331) `static int ascii_ieq(const char *a, const char *b)`
  - `tsh_family_is_generic` (function, line 340) `int tsh_family_is_generic(const char *name)`
  - `tsh_pick_from_list` (function, line 352) `int tsh_pick_from_list(const char *list, tsh_name_resolver resolve, void *ctx,
                  ...`
  - `tsh_pick_family` (function, line 373) `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong,
        ...`
  - `fc_installed` (function, line 386) `static int fc_installed(const char *name, void *ctx)`
  - `fc_resolve` (function, line 429) `static int fc_resolve(const char *name, char *out, size_t cap, void *ctx)`
  - `local_clear` (function, line 474) `static void local_clear(void)`
  - `lfam_index` (function, line 484) `static int lfam_index(const char *fam)`
  - `tsh_local_handle` (function, line 492) `int tsh_local_handle(const char *list)`
  - `local_entry` (function, line 511) `static tsh_entry *local_entry(int handle, int bold, int italic)`
  - `get_entry_ex` (function, line 531) `static tsh_entry *get_entry_ex(const tsh_font *f)`
  - `tsh_ready` (function, line 543) `int tsh_ready(void)`
  - `tsh_shape` (function, line 548) `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                ...`
  - `utf8_next` (function, line 597) `static unsigned utf8_next(const char *s, size_t n, size_t *len)`
  - `is_private_use` (function, line 616) `static int is_private_use(unsigned cp)`
  - `rides_previous` (function, line 621) `static int rides_previous(unsigned cp)`
  - `tsh_segment` (function, line 629) `int tsh_segment(const char *text, size_t len, tsh_cover_fn cover, void *ctx,
                tsh_...`
  - `fb_clear` (function, line 669) `static void fb_clear(void)`
  - `fb_entry` (function, line 679) `static tsh_entry *fb_entry(unsigned cp, int bold)`
  - `cover_cp` (function, line 750) `static int cover_cp(unsigned cp, void *vctx)`
  - `shape_entry` (function, line 764) `static tsh_status shape_entry(tsh_entry *e, double px, const char *text, size_t len,
            ...`
  - `shape_runs` (function, line 800) `static tsh_status shape_runs(cairo_t *cr, const tsh_font *f, double px, double x,
               ...`
  - `tsh_measure` (function, line 846) `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)`
  - `tsh_draw` (function, line 852) `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, doub...`
  - `tsh_face` (function, line 859) `cairo_font_face_t *tsh_face(const tsh_font *f)`
  - `tsh_shutdown` (function, line 865) `void tsh_shutdown(void)`
  - `characters` (function, line 100) `* hold characters ('-', ':') that the pattern syntax treats specially. */ static int load_entry_file(tsh_entry *e...`
  - `slice` (function, line 213) `* woff2 slice (spec/webfont.md);`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
  - `TSH_MAX_FONT_BYTES` (macro, line 29) `#define TSH_MAX_FONT_BYTES`
  - `TSH_CACHE_SLOTS` (macro, line 33) `#define TSH_CACHE_SLOTS`
  - `TSH_WEB_SLOTS` (macro, line 189) `#define TSH_WEB_SLOTS`
  - `TSH_SUBS_MAX` (macro, line 400) `#define TSH_SUBS_MAX`
  - `TSH_BLANK_GLYPH` (macro, line 613) `#define TSH_BLANK_GLYPH`
  - `TSH_FB_SLOTS` (macro, line 655) `#define TSH_FB_SLOTS`
  - `TSH_FB_BLOCKS` (macro, line 656) `#define TSH_FB_BLOCKS`
  - `TSH_MAX_RUNS` (macro, line 796) `#define TSH_MAX_RUNS`
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

## src/webfont.c
- Doc: ci_eq_span: #include <stdint.h> #include <stdlib.h> #include <string.h> static int is_ws(char c)...
- Layer: utility
- Language: c
- Symbols:
  - `is_ws` (function, line 19) `static int is_ws(char c)`
  - `lower_ch` (function, line 23) `static int lower_ch(char c)`
  - `ci_eq_span` (function, line 28) `static int ci_eq_span(const char *s, size_t n, const char *kw)`
  - `wf_list_free` (function, line 49) `void wf_list_free(wf_list *l)`
  - `wf_ref_move` (function, line 64) `void wf_ref_move(wf_ref *dst, wf_ref *src)`
  - `wf_supported_format` (function, line 74) `int wf_supported_format(const char *fmt)`
  - `emit_slot` (function, line 83) `static wf_ref *emit_slot(wf_list *out)`
  - `emit_family_format` (function, line 98) `static void emit_family_format(wf_ref *r, const char *family, const char *format)`
  - `span_is_data` (function, line 114) `static int span_is_data(const char *span, size_t slen)`
  - `emit` (function, line 126) `static void emit(wf_list *out, const char *family,
                 const char *url, size_t ulen,...`
  - `emit_data` (function, line 142) `static void emit_data(wf_list *out, const char *family,
                      const char *span, s...`
  - `scan_face_block` (function, line 179) `static void scan_face_block(const char *s, size_t bstart, size_t bend,
                          ...`
  - `lower_ch` (function, line 306) `&& lower_ch(s[k]) == 's' && k + 3 < bend
                && lower_ch(s[k + 1]) == 'r' && lower_ch...`
  - `wf_scan` (function, line 422) `int wf_scan(const char *css, size_t len, wf_list *out)`
  - `candidates` (function, line 7) `* understanding just far enough to find candidates (family + first url() per * src entry + weight/style descriptors);`
- Depends on: `include/data_url.h`, `include/webfont.h`

## src/webfont_load.c
- Doc: wf_key: size_t k = 0; while (PREF[i][k] != '\0') ++k; size_t j = 0; for (; j < k; ++j) { char a...
- Layer: utility
- Language: c
- Symbols:
  - `wf_key` (struct, line 46)
  - `wf_cursor` (struct, line 56)
  - `hash` (type_alias, line 46) `typedef struct wf_key { unsigned hash;`
  - `fetch` (type_alias, line 56) `typedef struct wf_cursor { wf_fetch_fn fetch;`
  - `ctype_ok` (function, line 24) `static int ctype_ok(const char *ct)`
  - `key_find` (function, line 66) `static int key_find(wf_key *keys, size_t nkeys, unsigned h, int b, int i)`
  - `scan_inline` (function, line 178) `static void scan_inline(const char *html, size_t len, const char *page_url,
                     ...`
  - `wf_load_document` (function, line 229) `int wf_load_document(wf_fetch_fn fetch, void *fctx, const char *page_url,
                     co...`
  - `here` (function, line 22) `* filtered here (a "" hint may still name one);`
  - `ref` (function, line 167) `* their ref (the register call copies what it keeps). */ if (!is_data) free(fbytes);`
  - `WF_DATA_URL_MAX` (macro, line 91) `#define WF_DATA_URL_MAX`
- Depends on: `include/data_url.h`, `include/text_shape.h`, `include/url.h`, `include/webfont.h`, `include/webfont_load.h`

## src/wl_display.c
- Layer: utility
- Language: c
- Symbols:
  - `wd_index` (function, line 13) `static int wd_index(const char *name, unsigned long *idx)`
  - `wd_pick` (function, line 27) `int wd_pick(const char *const *names, size_t n, char *out, size_t cap)`
  - `wd_resolve_env` (function, line 42) `int wd_resolve_env(void)`
  - `_POSIX_C_SOURCE` (macro, line 1) `#define _POSIX_C_SOURCE`
  - `WD_PREFIX` (macro, line 8) `#define WD_PREFIX`
  - `WD_PREFIX_LEN` (macro, line 9) `#define WD_PREFIX_LEN`
  - `WD_MAX_NAMES` (macro, line 10) `#define WD_MAX_NAMES`
  - `WD_NAME_MAX` (macro, line 11) `#define WD_NAME_MAX`
- Depends on: `include/wl_display.h`

## src/wl_guard.c
- Layer: utility
- Language: c
- Symbols:
  - `wl_guard` (struct, line 19)
  - `guard_main` (function, line 26) `static void *guard_main(void *arg)`
  - `wlg_start` (function, line 45) `wl_guard *wlg_start(struct wl_display *display)`
  - `wlg_stop` (function, line 61) `void wlg_stop(wl_guard *g)`
  - `_DEFAULT_SOURCE` (macro, line 5) `#define _DEFAULT_SOURCE`
  - `WLG_POLL_MS` (macro, line 17) `#define WLG_POLL_MS`
- Depends on: `include/wl_guard.h`


Next: [KB_src_p10.md](KB_src_p10.md)
