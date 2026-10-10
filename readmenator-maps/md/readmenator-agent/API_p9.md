# API (page 9 of 9)
Previous: [API_p8.md](API_p8.md)

## src/svg_render.c
Depends on: `include/css_color.h`, `include/svg_render.h`
- `sv_is_space` (function) `src/svg_render.c:21` `static int sv_is_space(char c)`
- `sv_is_digit` (function) `src/svg_render.c:25` `static int sv_is_digit(char c)`
- `sv_lower` (function) `src/svg_render.c:27` `static char sv_lower(char c)`
- `sv_span_eq` (function) `src/svg_render.c:32` `static int sv_span_eq(const char *s, size_t n, const char *lit)` -- /* --- small scanning helpers (no locale, no allocation) --- static int sv_is_space(char c) { return c == ' ' || c...
- `sv_sep` (function) `src/svg_render.c:82` `static void sv_sep(const char *s, size_t n, size_t *i)` -- if (ev > 300) ev = 300; double m = pow(10.0, eneg ? -(double)ev : (double)ev); v *= m; p = q; } } if (neg) v = -v...
- `sv_attr_get` (function) `src/svg_render.c:99` `static const char *sv_attr_get(const sv_attr *at, size_t nat, const char *name, size_t *len)` -- while (*i < n && sv_is_space(s[*i])) ++*i; } /* --- attribute lookup
- `sv_attr_num` (function) `src/svg_render.c:108` `static double sv_attr_num(const sv_attr *at, size_t nat, const char *name, double dflt)` -- Numeric attribute, or `dflt` when absent/malformed.
- `sv_mat_identity` (function) `src/svg_render.c:161` `static void sv_mat_identity(double *m)`
- `sv_mat_mul` (function) `src/svg_render.c:166` `static void sv_mat_mul(const double *a, const double *b, double *out)` -- int    fill, stroke; double stroke_w; int    opacity, fill_opacity, stroke_opacity; int    fill_even_odd; int...
- `sv_parse_transform` (function) `src/svg_render.c:179` `static void sv_parse_transform(const char *s, size_t n, double *m)` -- Parses a `transform` list and composes it onto ctx->m.
- `sv_style_next` (function) `src/svg_render.c:238` `static int sv_style_next(const char *s, size_t n, size_t *i,
                         const char ...` -- Reads one `name:value` declaration out of a style="" attribute.
- `sv_apply_prop` (function) `src/svg_render.c:260` `static void sv_apply_prop(sv_ctx *ctx, const char *nm, size_t nl,
                          const...` -- if (*i >= n || s[*i] != ':') { while (*i < n && s[*i] != ';') ++*i; return 1; } ++*i; size_t vs = *i; while (*i < n...
- `sv_ctx_from_attrs` (function) `src/svg_render.c:307` `static void sv_ctx_from_attrs(sv_ctx *ctx, const sv_attr *at, size_t nat)` -- Folds every presentation attribute of the current tag (and its style="") into a copy of the inherited context.
- `sv_new_shape` (function) `src/svg_render.c:324` `static sv_shape *sv_new_shape(sv_image *im, int kind, const sv_ctx *ctx)`
- `sv_parse_points` (function) `src/svg_render.c:343` `static void sv_parse_points(sv_image *im, sv_shape *sh, const char *s, size_t n)` -- sh->fill = ctx->fill; sh->stroke = ctx->stroke; sh->stroke_w = ctx->stroke_w; sh->opacity = ctx->opacity...
- `sv_new_seg` (function) `src/svg_render.c:363` `static sv_seg *sv_new_seg(sv_image *im, sv_shape *sh)`
- `sv_seg_move` (function) `src/svg_render.c:371` `static int sv_seg_move(sv_image *im, sv_shape *sh, double x, double y)`
- `sv_seg_line` (function) `src/svg_render.c:378` `static int sv_seg_line(sv_image *im, sv_shape *sh, double x, double y)`
- `sv_seg_cubic` (function) `src/svg_render.c:385` `static int sv_seg_cubic(sv_image *im, sv_shape *sh,
                        double x1, double y1,...`
- `sv_arc_to_cubics` (function) `src/svg_render.c:399` `static int sv_arc_to_cubics(sv_image *im, sv_shape *sh,
                            double x0, do...` -- Endpoint-parameterised elliptical arc -> up to 4 cubic segments (F.6.5 of the SVG spec).
- `sv_parse_path` (function) `src/svg_render.c:477` `static void sv_parse_path(sv_image *im, sv_shape *sh, const char *s, size_t n)` -- Parses path data.
- `point` (function) `src/svg_render.c:556` `* current point (SVG 8.3.6). */ int had = (prev == 'C' || prev == 'c' || prev == 'S' || prev == 's');`
- `sv_is_dropped_element` (function) `src/svg_render.c:635` `static int sv_is_dropped_element(const char *name, size_t n)` -- True for elements whose whole subtree is dropped. <image>/<use>/<foreignObject> can name external resources...
- `sv_scan_attrs` (function) `src/svg_render.c:647` `static void sv_scan_attrs(const char *s, size_t n, size_t *i,
                          sv_attr *...` -- Scans the attributes of a tag whose body starts at s[*i] (just past the name). * Stops at '>' and reports whether...
- `sv_skip_subtree` (function) `src/svg_render.c:693` `static void sv_skip_subtree(const char *s, size_t n, size_t *i, const char *name, size_t nlen)` -- Skips to just past the matching close tag of `name`, honouring nesting.
- `sv_collect_text` (function) `src/svg_render.c:725` `static void sv_collect_text(const char *s, size_t n, size_t *i, char *dst, size_t cap)` -- Collects the literal text of the element that just opened, up to its close tag, * into a bounded buffer.
- `sv_fit` (function) `src/svg_render.c:743` `void sv_fit(const sv_image *img, double dw, double dh,
            double *scale, double *off_x, ...`
- `sv_parse` (function) `src/svg_render.c:763` `sv_status sv_parse(const char *markup, size_t len, sv_image *out)`
- `sv_parse_ex` (function) `src/svg_render.c:767` `sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill)`

## src/tab.c
Depends on: `include/anti_fp.h`, `include/box_tree.h`, `include/css.h`, `include/data_url.h`, `include/dom.h`, `include/freebug.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/image_decode.h`, `include/import_map.h`, `include/js_dom.h`, `include/js_env.h`, `include/js_sandbox.h`, `include/js_trusted.h`, `include/link_nav.h`, `include/os_sandbox.h`, `include/page_view.h`, `include/request_policy.h`, `include/tab.h`, `include/url.h`, `include/util.h`, `include/web_storage.h`
- `child_reset_page` (function) `src/tab.c:155` `static void child_reset_page(child_state *cs)`
- `policy` (function) `src/tab.c:175` `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a
 * compromi...`
- `run_js` (function) `src/tab.c:229` `* regardless of run_js (a no-JS load simply never records a request). */
static int child_load(ch...`
- `buffer` (function) `src/tab.c:272` `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...`
- `host` (function) `src/tab.c:284` `* granted net access for this host (allow.conf AND js.conf). Otherwise they stay * undefined...`
- `write_field` (function) `src/tab.c:296` `static int write_field(int fd, const char *s)` -- Writes one length-prefixed string field (the write mirror of read_field): a size_t * length then the bytes, with...
- `blocks` (function) `src/tab.c:330` `*
 * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the
 * grid arr...`
- `FB_MAX_FILE_BYTES` (function) `src/tab.c:702` `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...`
- `budget_remaining_ms` (function) `src/tab.c:732` `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` -- Milliseconds of `budget_ms` still left since `start` (CLOCK_MONOTONIC), 0 if spent. * Used to share one page-wide JS...
- `ctype_is_javascript` (function) `src/tab.c:746` `static int ctype_is_javascript(const char *ctype)` -- Content-Type gate for an external script's response (anti type-confusion, fail closed for real content types)...
- `ctype_is_css` (function) `src/tab.c:755` `static int ctype_is_css(const char *ctype)` -- Content-Type gate for an external stylesheet (Hito 27), same shape as the script gate: a missing/empty type is...
- `log_external_skip` (function) `src/tab.c:763` `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...` -- Freebug note about an external subresource (script/stylesheet) that was not used (skipped or refused).
- `run` (function) `src/tab.c:781` `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...`
- `tab_url_resolve` (function) `src/tab.c:830` `static int tab_url_resolve(void *ctx, const char *base, const char *ref,
                        ...` -- Plain URL resolution of ref against base (https, or a local file confined to its * document's directory): the...
- `tab_mod_resolve` (function) `src/tab.c:839` `static int tab_mod_resolve(void *host, const char *base, const char *spec,
                      ...`
- `tab_mod_fetch` (function) `src/tab.c:861` `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` -- Loads a module's source through the trusted parent (TAG_SUBREQ: the full network policy applies), only inside a...
- `write_history` (function) `src/tab.c:883` `static int write_history(int wfd, child_state *cs)` -- Writes the history block of a response: [len][ops "K url\n"...][go:int32] * (spec/js_dom.md 7e).
- `window` (function) `src/tab.c:902` `* net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs)`
- `child_handle_load` (function) `src/tab.c:947` `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...`
- `fallback` (function) `src/tab.c:1023` `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it...`
- `WHERE` (function) `src/tab.c:1181` `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...`
- `content` (function) `src/tab.c:1214` `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...`
- `once` (function) `src/tab.c:1259` `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);`
- `swap` (function) `src/tab.c:1268` `* display:none hiding an element via class swap (CSS, not
     * DOM removal). */
    if (ok && v...`
- `write_full` (function) `src/tab.c:1288` `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0) && write_view(wfd...`
- `write_ws` (function) `src/tab.c:1310` `static int write_ws(int wfd, child_state *cs)` -- Writes the WebSocket block of a response: [n:int32] then per op * [kind:int32][id:int32][len][bytes] (spec/js_dom.md...
- `write_storage` (function) `src/tab.c:1327` `static int write_storage(int wfd, child_state *cs)` -- int32_t cnt = (int32_t)n; int rc = (write_full(wfd, &cnt, sizeof cnt) == 0) ?
- `write_opens` (function) `src/tab.c:1341` `static int write_opens(int wfd, child_state *cs)` -- static int write_storage(int wfd, child_state *cs) { char *blob = NULL; size_t len = 0; int32_t dirty = (cs->js !=...
- `child_next_timer_ms` (function) `src/tab.c:1353` `static int32_t child_next_timer_ms(child_state *cs)` -- Smallest pending JS timer delay (__nextTimerMs), or -1 when JS is absent, the * eval fails, or nothing is pending.
- `child_handle_mutation` (function) `src/tab.c:1368` `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...` -- Fire click handlers for node_id (OP_CLICK) or advance the virtual timer clock (OP_TICK), then re-derive the view so...
- `child_handle_click` (function) `src/tab.c:1447` `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)`
- `child_handle_tick` (function) `src/tab.c:1451` `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)`
- `child_handle_event` (function) `src/tab.c:1461` `static void child_handle_event(int wfd, child_state *cs)`
- `child_handle_mouse` (function) `src/tab.c:1509` `static void child_handle_mouse(int wfd, child_state *cs)` -- Handles a mouse DOM event (OP_MOUSE).
- `geom_parent` (function) `src/tab.c:1539` `static dom_node_id geom_parent(void *ctx, dom_node_id n)`
- `child_handle_geom` (function) `src/tab.c:1547` `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` -- OP_GEOM (spec/js_geom.md): installs the parent's laid-out geometry into the page's JS, aggregated into ancestors...
- `child_handle_submit` (function) `src/tab.c:1571` `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` -- Fires a submit event on the form enclosing node_id.
- `child_handle_eval` (function) `src/tab.c:1605` `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` -- Response: [ok:int32][is_exception:int32][value_len][value]. ok==0 means a worker-level failure (no page loaded); a...
- `child_handle_decode_image` (function) `src/tab.c:1638` `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` -- Response: [ok:int32] then, when ok, [w:u32][h:u32][stride:u32][len:size_t][data].
- `child_handle_decode_image_b64` (function) `src/tab.c:1660` `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)` -- data: URI images: the parent only sliced the base64 payload (pure pointer arithmetic, no interpretation); the base64...
- `gen_session_key` (function) `src/tab.c:1672` `static uint64_t gen_session_key(void)`
- `tab_worker_run` (function) `src/tab.c:1692` `static void tab_worker_run(int rfd, int wfd)` -- The confined request loop.
- `EPIPE` (function) `src/tab.c:1694` `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();`
- `tzset` (function) `src/tab.c:1710` `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);`
- `depth` (function) `src/tab.c:1715` `* defense in depth (seccomp already excludes open/socket/exec);`
- `parse_worker_fd` (function) `src/tab.c:1890` `static int parse_worker_fd(const char *s, int *out)` -- free(buf); free(url); free(cookies); free(storage); } child_reset_page(&cs); fb_buffer_free(&cs.log); _exit(0); } /*...
- `tab_parse_worker_args` (function) `src/tab.c:1902` `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)`
- `tab_worker_dispatch` (function) `src/tab.c:1912` `void tab_worker_dispatch(int argc, char **argv)`
- `load` (function) `src/tab.c:1929` `* subresource requests this load (set per page: host in allow.conf AND js.conf);`
- `ignore_sigpipe` (function) `src/tab.c:1946` `static void ignore_sigpipe(void)` -- A write to a dead child must not kill the parent with SIGPIPE.
- `tab_refresh_alive` (function) `src/tab.c:1953` `static void tab_refresh_alive(tab *t)`
- `read_field` (function) `src/tab.c:1972` `static int read_field(int fd, char **out, size_t *out_len)` -- Read one length-prefixed owned field from the child, capped against * amplification. *out is NUL-terminated.
- `read_view` (function) `src/tab.c:1988` `static int read_view(int fd, pv_view **out)` -- Reads a display list serialised by write_view into a fresh pv_view.
- `layout` (function) `src/tab.c:2138` `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....`
- `column` (function) `src/tab.c:2149` `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...`
- `read_console` (function) `src/tab.c:2431` `static int read_console(int fd, fb_buffer *out)` -- Reads the console section written by write_console into out (a zero-initialised fb_buffer).
- `send_request` (function) `src/tab.c:2468` `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` -- if (elen != 0) { txt = (char *)malloc(elen); if (txt == NULL) { free(file); return -1; } if (read_full(fd, txt...
- `io_failure` (function) `src/tab.c:2478` `static tab_status io_failure(tab *t)`
- `exec_worker_child` (function) `src/tab.c:2486` `static void exec_worker_child(int rfd, int wfd)` -- Child half of the fork: re-exec a fresh worker image so it inherits NONE of the parent's address space (no other...
- `tab_set_fetcher` (function) `src/tab.c:2557` `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)`
- `tab_set_net_allowed` (function) `src/tab.c:2563` `void tab_set_net_allowed(tab *t, int allowed)`
- `tab_set_css_allowed` (function) `src/tab.c:2568` `void tab_set_css_allowed(tab *t, int allowed)`
- `tab_set_viewport_w` (function) `src/tab.c:2573` `void tab_set_viewport_w(tab *t, int px)`
- `tab_set_cookies` (function) `src/tab.c:2578` `void tab_set_cookies(tab *t, const char *cookies)`
- `tab_subreq_permitted` (function) `src/tab.c:2584` `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)`
- `answered` (function) `src/tab.c:2596` `* A refused frame is still consumed and answered (status 0), so the protocol never
 * desyncs. Re...`
- `hist_ops_free` (function) `src/tab.c:2632` `static void hist_ops_free(tab_hist_op *ops, size_t n)`
- `is_activation_event` (function) `src/tab.c:2697` `static int is_activation_event(const char *type)` -- HTML 6.4.2 activation-triggering input events: only these let a page open a * window.
- `open_urls_free` (function) `src/tab.c:2706` `static void open_urls_free(char **u, size_t n)`
- `read_opens` (function) `src/tab.c:2716` `static tab_status read_opens(tab *t, const char *page_url, int gesture,
                         ...` -- Reads the window.open block (see write_opens).
- `ws_ops_free` (function) `src/tab.c:2745` `static void ws_ops_free(tab_ws_op *ops, size_t n)`
- `read_ws` (function) `src/tab.c:2754` `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` -- Reads the WebSocket block (see write_ws), bounded by JT_WS_MAX_OPS ops and JT_WS_MAX_BYTES of payload.
- `gate_js_nav` (function) `src/tab.c:2823` `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` -- Gates a raw JS navigation request against the page URL in the trusted parent (Zero Trust: a compromised worker...
- `tab_load` (function) `src/tab.c:2833` `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)`
- `tab_load_ex` (function) `src/tab.c:2837` `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)`
- `tab_load_full` (function) `src/tab.c:2841` `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...`
- `tab_click` (function) `src/tab.c:3027` `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)`
- `tab_tick` (function) `src/tab.c:3034` `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)`
- `tab_submit` (function) `src/tab.c:3043` `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` -- Dispatches a submit event on the form enclosing node_id.
- `tab_read_view` (function) `src/tab.c:3148` `tab_status tab_read_view(tab *t, tab_page *out)` -- Reads the TAG_RESULT + TAG_VIEW response into *out (titles + view + console). * Used by tab_mutation_request...
- `tab_read_view_ex` (function) `src/tab.c:3152` `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)`
- `tab_eval` (function) `src/tab.c:3248` `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)`
- `tab_decode_image_op` (function) `src/tab.c:3288` `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...` -- Shared by tab_decode_image and tab_decode_image_data_url: sends `bytes` under opcode `op` and parses the...
- `tab_decode_image` (function) `src/tab.c:3330` `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)`
- `tab_decode_image_data_url` (function) `src/tab.c:3336` `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)`
- `tab_alive` (function) `src/tab.c:3354` `int tab_alive(const tab *t)`
- `tab_child_pid` (function) `src/tab.c:3360` `pid_t tab_child_pid(const tab *t)`
- `tab_close` (function) `src/tab.c:3364` `void tab_close(tab *t)`
- `tab_page_free` (function) `src/tab.c:3379` `void tab_page_free(tab_page *p)`
- `tab_eval_result_free` (function) `src/tab.c:3409` `void tab_eval_result_free(tab_eval_result *r)`
- `tab_image_free` (function) `src/tab.c:3418` `void tab_image_free(tab_image *img)`
- `tab_set_geometry` (function) `src/tab.c:3428` `tab_status tab_set_geometry(tab *t, const jg_table *g)`
- `tab_popstate` (function) `src/tab.c:3454` `tab_status tab_popstate(tab *t, int index, tab_page *out)`
- `tab_ws_event` (function) `src/tab.c:3460` `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,
       ...`
- `tab_set_storage` (function) `src/tab.c:3479` `void tab_set_storage(tab *t, const char *blob, size_t len)`

## src/text_shape.c
Depends on: `include/css.h`, `include/text_shape.h`, `include/webfont.h`
- `generic_name` (function) `src/text_shape.c:55` `static const char *generic_name(int family)`
- `backend_init` (function) `src/text_shape.c:65` `static int backend_init(void)`
- `read_font_file` (function) `src/text_shape.c:82` `static unsigned char *read_font_file(const char *path, long *out_n)`
- `load_entry` (function) `src/text_shape.c:98` `static int load_entry(tsh_entry *e, int family, int bold, int italic)`
- `get_entry` (function) `src/text_shape.c:153` `static tsh_entry *get_entry(int family, int bold, int italic)`
- `web_entry_free` (function) `src/text_shape.c:181` `static void web_entry_free(tsh_web *w)`
- `slice` (function) `src/text_shape.c:193` `* woff2 slice (spec/webfont.md);`
- `web_magic_ok` (function) `src/text_shape.c:194` `static int web_magic_ok(const unsigned char *b, size_t n)` -- True for font programs FreeType parses without new decoders: wOFF/TrueType/ CFF-OpenType (and the mac aliases). wOF2...
- `web_make_entry` (function) `src/text_shape.c:207` `static int web_make_entry(tsh_entry *e, const unsigned char *bytes, size_t nbytes)` -- Builds the shaping faces over an OWNED copy of bytes[0,nbytes) into e (shared tail with load_entry's file path: same...
- `tsh_webfont_register` (function) `src/text_shape.c:247` `int tsh_webfont_register(const char *name,
                         const unsigned char *bytes, s...`
- `tsh_webfont_clear` (function) `src/text_shape.c:281` `void tsh_webfont_clear(void)`
- `web_find` (function) `src/text_shape.c:286` `static tsh_entry *web_find(unsigned h, int bold, int italic)`
- `get_entry_ex` (function) `src/text_shape.c:302` `static tsh_entry *get_entry_ex(const tsh_font *f)` -- Entry for a full font selector: a registered @font-face wins over the local bucket stack; a set-but-unregistered...
- `tsh_ready` (function) `src/text_shape.c:310` `int tsh_ready(void)`
- `tsh_shape` (function) `src/text_shape.c:315` `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                ...`
- `tsh_measure` (function) `src/text_shape.c:360` `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)`
- `tsh_draw` (function) `src/text_shape.c:367` `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, doub...`
- `tsh_shutdown` (function) `src/text_shape.c:389` `void tsh_shutdown(void)`

## src/textfield.c
Depends on: `include/textfield.h`
- `whole` (function) `src/textfield.c:6` `* the buffer is rejected whole (fail closed), never applied partially.
 */

#include "textfield.h...`
- `tf_clear` (function) `src/textfield.c:20` `void tf_clear(tf_field *f)`
- `tf_set` (function) `src/textfield.c:24` `tf_status tf_set(tf_field *f, const char *s)`
- `tf_insert` (function) `src/textfield.c:35` `tf_status tf_insert(tf_field *f, char c)`
- `tf_backspace` (function) `src/textfield.c:47` `void tf_backspace(tf_field *f)`
- `tf_delete` (function) `src/textfield.c:55` `void tf_delete(tf_field *f)`
- `tf_move` (function) `src/textfield.c:62` `void tf_move(tf_field *f, long delta)`
- `tf_home` (function) `src/textfield.c:73` `void tf_home(tf_field *f)`
- `tf_end` (function) `src/textfield.c:78` `void tf_end(tf_field *f)`
- `tf_text` (function) `src/textfield.c:83` `const char *tf_text(const tf_field *f)`
- `tf_len` (function) `src/textfield.c:87` `size_t tf_len(const tf_field *f)`
- `tf_cursor` (function) `src/textfield.c:91` `size_t tf_cursor(const tf_field *f)`

## src/tls_impersonate.c
Depends on: `include/tls_impersonate.h`
- `ti_should_impersonate` (function) `src/tls_impersonate.c:18` `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,
                          i...`
- `bounded_len` (function) `src/tls_impersonate.c:25` `static size_t bounded_len(const char *s, size_t max)`
- `put_u8` (function) `src/tls_impersonate.c:35` `static void put_u8(ti_wr *w, uint8_t v)`
- `put_u32` (function) `src/tls_impersonate.c:40` `static void put_u32(ti_wr *w, uint32_t v)`
- `put_u64` (function) `src/tls_impersonate.c:48` `static void put_u64(ti_wr *w, uint64_t v)`
- `put_blob` (function) `src/tls_impersonate.c:53` `static void put_blob(ti_wr *w, const uint8_t *b, size_t n)`
- `get_u8` (function) `src/tls_impersonate.c:65` `static uint8_t get_u8(ti_rd *r)`
- `get_u32` (function) `src/tls_impersonate.c:70` `static uint32_t get_u32(ti_rd *r)`
- `get_u64` (function) `src/tls_impersonate.c:80` `static uint64_t get_u64(ti_rd *r)`
- `get_bytes` (function) `src/tls_impersonate.c:89` `static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len)` -- | ((uint32_t)r->p[r->off + 3] << 24); r->off += 4; return v; } static uint64_t get_u64(ti_rd *r) { if (r->err ||...
- `get_str` (function) `src/tls_impersonate.c:103` `static char *get_str(ti_rd *r, size_t cap)` -- static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len) { out = NULL; *out_len = 0; uint32_t n =...
- `valid_profile` (function) `src/tls_impersonate.c:116` `static int valid_profile(int p)`
- `ti_encode_req` (function) `src/tls_impersonate.c:122` `size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap)`
- `ti_decode_req` (function) `src/tls_impersonate.c:140` `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out)`
- `ti_req_free` (function) `src/tls_impersonate.c:166` `void ti_req_free(ti_req *r)`
- `ti_encode_resp` (function) `src/tls_impersonate.c:177` `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap)`
- `ti_decode_resp` (function) `src/tls_impersonate.c:196` `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out)`
- `ti_resp_free` (function) `src/tls_impersonate.c:230` `void ti_resp_free(ti_resp *r)`

## src/ui_layout.c
Depends on: `include/ui.h`
- `layout_push` (function) `src/ui_layout.c:13` `static int layout_push(ui_layout *lay, size_t offset, size_t len)`
- `ui_wrap_text` (function) `src/ui_layout.c:27` `ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out)`
- `ui_layout_free` (function) `src/ui_layout.c:91` `void ui_layout_free(ui_layout *lay)`
- `ui_clamp_scroll` (function) `src/ui_layout.c:99` `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines)`

## src/url.c
Depends on: `include/url.h`
- `ci_prefix` (function) `src/url.c:20` `static int ci_prefix(const char *haystack, const char *prefix)` -- produced; every assembly is bounded and reports overflow rather than truncate.  #define _POSIX_C_SOURCE 200809L...
- `copy_checked` (function) `src/url.c:32` `static int copy_checked(char *out, size_t outsz, const char *src)` -- /* Case-insensitive: does haystack start with prefix? static int ci_prefix(const char *haystack, const char *prefix)...
- `cat_checked` (function) `src/url.c:40` `static int cat_checked(char *out, size_t outsz, const char *src)` -- +haystack; ++prefix; } return 1; } /* Bounded copy: out gets src (NUL-terminated).
- `ncat_checked` (function) `src/url.c:49` `static int ncat_checked(char *out, size_t outsz, const char *src, size_t n)` -- memcpy(out, src, n + 1); return 0; } /* Bounded append: out += src.
- `url_has_scheme` (function) `src/url.c:59` `int url_has_scheme(const char *s)`
- `url_is_https` (function) `src/url.c:73` `int url_is_https(const char *s)`
- `url_validate_https` (function) `src/url.c:80` `url_status url_validate_https(const char *url)`
- `url_authority_len` (function) `src/url.c:91` `size_t url_authority_len(const char *url)`
- `out_pop_segment` (function) `src/url.c:102` `static void out_pop_segment(char *out, size_t *olen)` -- RFC 3986 3.2: the authority ends at the first '/', '?' or '#'.
- `url_remove_dot_segments` (function) `src/url.c:109` `url_status url_remove_dot_segments(const char *path, char *out, size_t outsz)`
- `dir_len` (function) `src/url.c:159` `static size_t dir_len(const char *base)` -- Length of base up to and including the last path '/', ignoring query/fragment. * If the path carries no slash...
- `url_resolve_https` (function) `src/url.c:170` `url_status url_resolve_https(const char *base, const char *ref,
                             char...`
- `is_space` (function) `src/url.c:218` `static int is_space(int c)`
- `is_unreserved` (function) `src/url.c:222` `static int is_unreserved(int c)`
- `append_query_encoded` (function) `src/url.c:229` `static int append_query_encoded(char *out, size_t outsz, const char *src)` -- Percent-encodes src into a query value appended to out (space -> '+', every * non-unreserved byte -> %XX).
- `assumed` (function) `src/url.c:254` `* assumed (the caller already routed whitespace to search). */
static int looks_like_host(const c...`
- `build_search` (function) `src/url.c:303` `static url_status build_search(const char *query, char *out, size_t outsz)`
- `url_omnibox` (function) `src/url.c:309` `url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz)`
- `host_equals` (function) `src/url.c:378` `static int host_equals(const url_parts *p, const char *want)` -- Any remaining explicit scheme is never executed nor downgraded: search for it * (so "javascript:...", "file:..."...
- `query_find_q` (function) `src/url.c:393` `static const char *query_find_q(const char *search, size_t len, size_t *vlen)` -- Returns a pointer to the value of the "q" parameter within a "?a=b&q=v&..." search span, with its length in *vlen...
- `url_search_rewrite` (function) `src/url.c:411` `url_status url_search_rewrite(const char *url, char *out, size_t outsz)`
- `url_extract_userinfo` (function) `src/url.c:431` `url_status url_extract_userinfo(const char *url, char *out, size_t outsz,
                       ...`
- `url_is_file` (function) `src/url.c:525` `int url_is_file(const char *s)`
- `url_file_path` (function) `src/url.c:531` `const char *url_file_path(const char *s)`
- `url_resolve_file` (function) `src/url.c:535` `url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz)`
- `url_split` (function) `src/url.c:584` `url_status url_split(const char *url, url_parts *out)`
- `copy_bounded` (function) `src/url.c:645` `static url_status copy_bounded(char *out, size_t outsz, const char *a, size_t alen,
             ...`
- `url_history_target` (function) `src/url.c:654` `url_status url_history_target(const char *base, const char *ref, char *out, size_t outsz)`

## src/web_storage.c
Depends on: `include/web_storage.h`
- `get_u32` (function) `src/web_storage.c:25` `static uint32_t get_u32(const unsigned char *p)`
- `utf8_ok` (function) `src/web_storage.c:32` `static int utf8_ok(const unsigned char *s, size_t n)` -- Well-formed UTF-8, allowing encoded surrogates (WTF-8): a JS string may hold a lone surrogate and rejecting it would...
- `key_cmp` (function) `src/web_storage.c:56` `static int key_cmp(const void *a, const void *b)`
- `check` (function) `src/web_storage.c:65` `static int check(const char *blob, size_t len, size_t *bytes_out)` -- return 1; } typedef struct key_ref { const unsigned char *p; uint32_t n; } key_ref; static int key_cmp(const void...
- `wst_decode_check` (function) `src/web_storage.c:101` `int wst_decode_check(const char *blob, size_t len)`
- `wst_new` (function) `src/web_storage.c:105` `wst_db *wst_new(void)`
- `wst_free` (function) `src/web_storage.c:109` `void wst_free(wst_db *db)`
- `find` (function) `src/web_storage.c:118` `static wst_origin *find(const wst_db *db, const char *origin)`
- `wst_encode` (function) `src/web_storage.c:125` `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len)`
- `wst_replace` (function) `src/web_storage.c:140` `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len)`
- `wst_origin_bytes` (function) `src/web_storage.c:175` `size_t wst_origin_bytes(const wst_db *db, const char *origin)`
- `wst_foreach` (function) `src/web_storage.c:181` `int wst_foreach(const char *blob, size_t len,
                void (*fn)(void *ctx, const char *k...`
- `put_u32` (function) `src/web_storage.c:201` `static void put_u32(char *b, uint32_t v)`
- `wst_pack` (function) `src/web_storage.c:206` `int wst_pack(const char *const *keys, const size_t *klens,
             const char *const *vals, ...`

## src/webcaps.c
Depends on: `include/webcaps.h`
- `wc_safe` (function) `src/webcaps.c:10` `wc_caps wc_safe(void)`
- `wc_derive` (function) `src/webcaps.c:15` `wc_caps wc_derive(wc_input in)`
- `wc_from_flags` (function) `src/webcaps.c:35` `wc_caps wc_from_flags(bool js, bool css, bool images)`
- `wc_render_caps` (function) `src/webcaps.c:46` `rdp_caps wc_render_caps(wc_caps c)`

## src/webfont.c
Depends on: `include/data_url.h`, `include/webfont.h`
- `candidates` (function) `src/webfont.c:7` `* understanding just far enough to find candidates (family + first url() per * src entry + weight/style descriptors);`
- `is_ws` (function) `src/webfont.c:19` `static int is_ws(char c)`
- `lower_ch` (function) `src/webfont.c:23` `static int lower_ch(char c)`
- `ci_eq_span` (function) `src/webfont.c:28` `static int ci_eq_span(const char *s, size_t n, const char *kw)` -- #include <stdint.h> #include <stdlib.h> #include <string.h> static int is_ws(char c) { return c == ' ' || c == '\t'...
- `wf_list_free` (function) `src/webfont.c:49` `void wf_list_free(wf_list *l)`
- `wf_ref_move` (function) `src/webfont.c:64` `void wf_ref_move(wf_ref *dst, wf_ref *src)`
- `wf_supported_format` (function) `src/webfont.c:74` `int wf_supported_format(const char *fmt)`
- `emit_slot` (function) `src/webfont.c:83` `static wf_ref *emit_slot(wf_list *out)` -- src->is_data = 0; } int wf_supported_format(const char *fmt) { if (fmt == NULL) return 0; if (fmt[0] == '\0') return...
- `emit_family_format` (function) `src/webfont.c:98` `static void emit_family_format(wf_ref *r, const char *family, const char *format)`
- `span_is_data` (function) `src/webfont.c:114` `static int span_is_data(const char *span, size_t slen)` -- if (fl >= WF_FAMILY_MAX) fl = WF_FAMILY_MAX - 1; memcpy(r->family, family, fl); r->family[fl] = '\0'; if (format !=...
- `emit` (function) `src/webfont.c:126` `static void emit(wf_list *out, const char *family,
                 const char *url, size_t ulen,...` -- /* True when span[0,slen) is a data: URL (case-insensitive scheme). static int span_is_data(const char *span, size_t...
- `emit_data` (function) `src/webfont.c:142` `static void emit_data(wf_list *out, const char *family,
                      const char *span, s...` -- Appends one data: ref, decoding the bytes NOW (a data: URL never fits url[]; * the bytes ride the ref instead).
- `scan_face_block` (function) `src/webfont.c:179` `static void scan_face_block(const char *s, size_t bstart, size_t bend,
                          ...` -- Parses one @font-face {...} body (bstart..bend, braces excluded) into the block's family/weight/style, then emits...
- `lower_ch` (function) `src/webfont.c:306` `&& lower_ch(s[k]) == 's' && k + 3 < bend
                && lower_ch(s[k + 1]) == 'r' && lower_ch...`
- `wf_scan` (function) `src/webfont.c:422` `int wf_scan(const char *css, size_t len, wf_list *out)`

## src/webfont_load.c
Depends on: `include/data_url.h`, `include/text_shape.h`, `include/url.h`, `include/webfont.h`, `include/webfont_load.h`
- `here` (function) `src/webfont_load.c:22` `* filtered here (a "" hint may still name one);`
- `ctype_ok` (function) `src/webfont_load.c:24` `static int ctype_ok(const char *ct)` -- Content types worth downloading as fonts.
- `key_find` (function) `src/webfont_load.c:66` `static int key_find(wf_key *keys, size_t nkeys, unsigned h, int b, int i)`
- `ref` (function) `src/webfont_load.c:167` `* their ref (the register call copies what it keeps). */ if (!is_data) free(fbytes);`
- `scan_inline` (function) `src/webfont_load.c:178` `static void scan_inline(const char *html, size_t len, const char *page_url,
                     ...` -- Finds inline <style>...</style> bodies in html (case-insensitive tags) and processes each sheet's refs against the...
- `wf_load_document` (function) `src/webfont_load.c:229` `int wf_load_document(wf_fetch_fn fetch, void *fctx, const char *page_url,
                     co...`

## src/ws_hub.c
Depends on: `include/ws_hub.h`
- `dup_str` (function) `src/ws_hub.c:54` `static char *dup_str(const char *s)`
- `job_free` (function) `src/ws_hub.c:63` `static void job_free(wh_job *j)`
- `job_str` (function) `src/ws_hub.c:71` `static int job_str(wh_job *j, size_t slot, const char **field)` -- if (n == (size_t)-1) return NULL; char *d = (char *)malloc(n + 1); if (d != NULL) memcpy(d, s, n + 1); return d; }...
- `open_thread` (function) `src/ws_hub.c:79` `static void *open_thread(void *arg)`
- `conn_clear` (function) `src/ws_hub.c:98` `static void conn_clear(wh_conn *c)`
- `find_id` (function) `src/ws_hub.c:104` `static wh_conn *find_id(wh_hub *h, int id)`
- `find_token` (function) `src/ws_hub.c:110` `static wh_conn *find_token(wh_hub *h, uint64_t token)`
- `wh_new` (function) `src/ws_hub.c:116` `wh_hub *wh_new(void)`
- `wh_free` (function) `src/ws_hub.c:129` `void wh_free(wh_hub *h)`
- `wh_notify_fd` (function) `src/ws_hub.c:144` `int wh_notify_fd(const wh_hub *h)`
- `wh_open_async` (function) `src/ws_hub.c:148` `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg)`
- `wh_on_notify` (function) `src/ws_hub.c:192` `void wh_on_notify(wh_hub *h, wh_emit_fn emit, void *ctx)`
- `wh_send` (function) `src/ws_hub.c:221` `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary)`
- `wh_close` (function) `src/ws_hub.c:228` `void wh_close(wh_hub *h, int id)`
- `wh_close_all` (function) `src/ws_hub.c:234` `void wh_close_all(wh_hub *h)`
- `wh_poll_fds` (function) `src/ws_hub.c:240` `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap)`
- `fail_conn` (function) `src/ws_hub.c:258` `static void fail_conn(wh_conn *c, int id, wh_emit_fn emit, void *ctx)` -- const wh_conn *c = &h->c[i]; if (!c->used || c->pending || c->ws == NULL) continue; int fd = sf_ws_fd(c->ws); if (fd...
- `wh_on_readable` (function) `src/ws_hub.c:266` `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx)`
- `wh_count` (function) `src/ws_hub.c:314` `size_t wh_count(const wh_hub *h)`

## src/zoom.c
Depends on: `include/zoom.h`
- `zm_clamp` (function) `src/zoom.c:14` `int zm_clamp(int pct)`
- `zm_zoom_in` (function) `src/zoom.c:20` `int zm_zoom_in(int pct)`
- `zm_zoom_out` (function) `src/zoom.c:28` `int zm_zoom_out(int pct)`
- `zm_reset` (function) `src/zoom.c:36` `int zm_reset(void)`
- `zm_scale` (function) `src/zoom.c:40` `double zm_scale(int pct)`
- `zm_apply` (function) `src/zoom.c:44` `double zm_apply(double base_px, int pct)`

## tools/ffgeom.py
- `load_rows` (function) `tools/ffgeom.py:99` `def load_rows(path)`
- `lum` (function) `tools/ffgeom.py:152` `def lum(p)`
- `lum_at` (function) `tools/ffgeom.py:164` `def lum_at(x, y)`
- `bit` (function) `tools/ffgeom.py:189` `def bit(grid_row, cell, origin)`
- `word` (function) `tools/ffgeom.py:192` `def word(grid_row, origin)`
- `decode` (function) `tools/ffgeom.py:222` `def decode(path)`
- `probe` (function) `tools/ffgeom.py:248` `def probe(page, selector, out_html)`
- `height_probe` (function) `tools/ffgeom.py:262` `def height_probe(page, out_html)`
- `height` (function) `tools/ffgeom.py:275` `def height(path)` -- Decodes the scrollHeight carried by the #__ffh sentinel: the probe encodes one rect (its height), which decode()...
- `main` (function) `tools/ffgeom.py:284` `def main(argv)`

## tools/gen_psl.c
- `vec_push` (function) `tools/gen_psl.c:27` `static void vec_push(vec *v, const char *s)`
- `cmp_str` (function) `tools/gen_psl.c:38` `static int cmp_str(const void *a, const void *b)`
- `sort_unique` (function) `tools/gen_psl.c:43` `static void sort_unique(vec *v)` -- v->cap = v->cap ? v->cap * 2 : 1024; v->items = (char **)realloc(v->items, v->cap * sizeof *v->items); if (v->items...
- `ascii_lower` (function) `tools/gen_psl.c:55` `static void ascii_lower(char *s)` -- /* Sorts then drops adjacent duplicates in place. static void sort_unique(vec *v) { qsort(v->items, v->len, sizeof...
- `emit` (function) `tools/gen_psl.c:61` `static void emit(const char *name, vec *v)`
- `main` (function) `tools/gen_psl.c:67` `int main(int argc, char **argv)`

## tools/mutate.py
- `line_sites` (function) `tools/mutate.py:41` `def line_sites(text)`
- `mutate_line` (function) `tools/mutate.py:75` `def mutate_line(line, op)`
- `find_modules` (function) `tools/mutate.py:107` `def find_modules(root)`
- `run_make` (function) `tools/mutate.py:116` `def run_make(root, target)`
- `run_bin` (function) `tools/mutate.py:125` `def run_bin(path)`
- `main` (function) `tools/mutate.py:137` `def main(argv)`

## tools/pngdiff.c
- `pd_reader_close` (function) `tools/pngdiff.c:79` `static void pd_reader_close(pd_reader *r)`
- `pd_reader_open` (function) `tools/pngdiff.c:88` `static int pd_reader_open(pd_reader *r, const char *path)` -- Opens `path` and normalises whatever colour type it carries into 8-bit RGB, so * the two passes below can assume...
- `png_set_background` (function) `tools/pngdiff.c:116` `png_set_background(r->png, &(png_color_16)` -- Compose against white rather than dropping alpha: a transparent region of a screenshot is what the viewer would see...
- `pd_lum` (function) `tools/pngdiff.c:141` `static double pd_lum(const png_byte *p)`
- `pd_background` (function) `tools/pngdiff.c:147` `static int pd_background(const char *path, double *out_bg)` -- Pass 1: the modal luminance IS the page background.
- `pd_profile_of` (function) `tools/pngdiff.c:175` `static int pd_profile_of(const char *path, pd_profile *out)` -- int b = (int)(pd_lum(&r.row[(size_t)x * 3u]) + 0.5); if (b < 0) b = 0; if (b > 255) b = 255; hist[b]++; } } int best...
- `pd_mae` (function) `tools/pngdiff.c:227` `static double pd_mae(const double *a, const double *b, size_t n)`
- `main` (function) `tools/pngdiff.c:233` `int main(int argc, char **argv)`

## tools/pngprof.py
- `load_rows` (function) `tools/pngprof.py:41` `def load_rows(path)`
- `lum` (function) `tools/pngprof.py:95` `def lum(p)`
- `render_glyph` (function) `tools/pngprof.py:99` `def render_glyph(v)`
- `main` (function) `tools/pngprof.py:109` `def main(argv)`

## tools/snapshot.py
- `fetch` (function) `tools/snapshot.py:17` `def fetch(url)`
- `expand_imports` (function) `tools/snapshot.py:31` `def expand_imports(css, base, depth)` -- Replace each @import with the imported text (wrapped in @media when the import carries a media condition), resolved...
- `repl` (function) `tools/snapshot.py:34` `def repl(m)`
- `inline_css` (function) `tools/snapshot.py:48` `def inline_css(html, base)`
- `repl` (function) `tools/snapshot.py:49` `def repl(m)`
- `main` (function) `tools/snapshot.py:69` `def main()`

