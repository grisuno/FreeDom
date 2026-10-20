# API (page 10 of 11)
Previous: [API_p9.md](API_p9.md)

## src/secure_fetch.c
Depends on: `include/anti_fp.h`, `include/secure_fetch.h`, `include/url.h`
- `ci_starts_with` (function) `src/secure_fetch.c:44` `static int ci_starts_with(const char *haystack, const char *prefix)` -- /* --- small helpers (no libc locale dependence) --- static int ci_equal(const char *a, const char *b) { while (*a...
- `ci_index` (function) `src/secure_fetch.c:56` `static long ci_index(const char *haystack, const char *needle)` -- /* Case-insensitive: does haystack start with prefix? static int ci_starts_with(const char *haystack, const char...
- `sf_share_lock` (function) `src/secure_fetch.c:68` `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...`
- `sf_share_unlock` (function) `src/secure_fetch.c:74` `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)`
- `sf_global_init` (function) `src/secure_fetch.c:81` `void sf_global_init(void)`
- `sf_cookie_line_matches` (function) `src/secure_fetch.c:96` `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...`
- `sf_url_host_path` (function) `src/secure_fetch.c:151` `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...` -- Extracts host + path from a validated https url into caller buffers (path defaults * to "/").
- `sf_cookie_header_for` (function) `src/secure_fetch.c:166` `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)`
- `sf_cookie_put` (function) `src/secure_fetch.c:195` `void sf_cookie_put(const char *url, const char *namevalue)`
- `sf_config_default` (function) `src/secure_fetch.c:216` `sf_config sf_config_default(void)`
- `sf_user_agent_or_default` (function) `src/secure_fetch.c:241` `const char *sf_user_agent_or_default(const char *ua)`
- `sf_impersonate_kex_groups` (function) `src/secure_fetch.c:245` `const char *sf_impersonate_kex_groups(void)`
- `sf_impersonate_tls13_ciphers` (function) `src/secure_fetch.c:246` `const char *sf_impersonate_tls13_ciphers(void)`
- `sf_validate_url` (function) `src/secure_fetch.c:250` `sf_status sf_validate_url(const char *url)`
- `sf_url_is_http` (function) `src/secure_fetch.c:258` `static int sf_url_is_http(const char *url)` -- Nonzero iff url is "http://host..." (case-insensitive) with a non-empty host.
- `sf_check_tls_version` (function) `src/secure_fetch.c:270` `sf_status sf_check_tls_version(const char *negotiated_version)`
- `sf_check_group_is_pq` (function) `src/secure_fetch.c:275` `sf_status sf_check_group_is_pq(const char *negotiated_group)`
- `sf_check_chain_policy` (function) `src/secure_fetch.c:284` `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)`
- `sf_enforce_policy` (function) `src/secure_fetch.c:294` `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...`
- `copy_checked` (function) `src/secure_fetch.c:325` `static int copy_checked(char *dst, size_t dstsz, const char *src)`
- `sf_is_redirect_code` (function) `src/secure_fetch.c:334` `int sf_is_redirect_code(long http_code)`
- `sf_parse_location_header` (function) `src/secure_fetch.c:341` `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)`
- `sf_resolve_redirect` (function) `src/secure_fetch.c:359` `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...`
- `module` (function) `src/secure_fetch.c:364` `* pure url module (DRY);`
- `sf_ci_prefix` (function) `src/secure_fetch.c:371` `static int sf_ci_prefix(const char *s, const char *p)` -- Reference resolution + the https-only / no-downgrade policy live in the pure url module (DRY); a redirect is just a...
- `sf_response_free` (function) `src/secure_fetch.c:411` `void sf_response_free(sf_response *resp)`
- `progress` (function) `src/secure_fetch.c:443` `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);`
- `copy_bounded` (function) `src/secure_fetch.c:470` `static void copy_bounded(char *dst, size_t dstsz, const char *src)`
- `get_negotiated_group_name` (function) `src/secure_fetch.c:481` `static const char *get_negotiated_group_name(SSL *ssl)` -- static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len); static void...
- `database` (function) `src/secure_fetch.c:485` `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid...`
- `group` (function) `src/secure_fetch.c:499` `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);`
- `tls_capture_try` (function) `src/secure_fetch.c:514` `static void tls_capture_try(tls_capture *cap)` -- nid = SSL_get_shared_group(ssl, 0); #endif if (nid == 0) { return NULL; /* There is no negotiated group (e.g., TLS...
- `tls_capture_from_ssl` (function) `src/secure_fetch.c:524` `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)` -- static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl); /* Idempotent: takes the TLS snapshot the first time...
- `this` (function) `src/secure_fetch.c:531` `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and...`
- `header_cb` (function) `src/secure_fetch.c:550` `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` -- Fires for every HTTP response (status line + headers) even when there is no * body, so it is the reliable point to...
- `write_cb` (function) `src/secure_fetch.c:586` `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)`
- `name_is_pq_sig` (function) `src/secure_fetch.c:618` `static int name_is_pq_sig(int pknid)` -- if (grown == NULL) { sink->overflow = 2; /* OOM marker return 0; } sink->data = grown; sink->cap = newcap; }...
- `inspect_chain` (function) `src/secure_fetch.c:628` `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` -- Walks the verified chain into *info. sigbuf receives the leaf signature alg name. * Returns 0 on success, nonzero if...
- `map_curl_error` (function) `src/secure_fetch.c:681` `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)`
- `add_header` (function) `src/secure_fetch.c:722` `static int add_header(struct curl_slist **h, const char *line)` -- Appends one header line without losing the list on OOM (the plain "h = curl_slist_append(h, ...)" idiom dropped the...
- `sf_setup_handle` (function) `src/secure_fetch.c:736` `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,
           ...` -- The ONE place a curl handle is configured for a request (spec/secure_fetch.md): URL, realm proxy, TLS floor + KE...
- `redirect` (function) `src/secure_fetch.c:811` `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...`
- `sf_perform` (function) `src/secure_fetch.c:879` `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...` -- The shared request engine for sf_get and sf_post.
- `sf_get` (function) `src/secure_fetch.c:1014` `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)`
- `sf_post` (function) `src/secure_fetch.c:1018` `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...`
- `sf_get_follow` (function) `src/secure_fetch.c:1032` `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...`
- `ws_ssl_info_cb` (function) `src/secure_fetch.c:1084` `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)` -- An upgraded (CONNECT_ONLY) connection never runs the header callback that snapshots TLS for a fetch, and curl no...
- `ws_ssl_ctx_cb` (function) `src/secure_fetch.c:1091` `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)`
- `sf_ws_url_check` (function) `src/secure_fetch.c:1105` `sf_status sf_ws_url_check(const char *url)`
- `ws_free` (function) `src/secure_fetch.c:1117` `static void ws_free(sf_ws *ws)`
- `sf_ws_open` (function) `src/secure_fetch.c:1126` `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)`
- `sf_ws_send` (function) `src/secure_fetch.c:1181` `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)`
- `sf_ws_recv` (function) `src/secure_fetch.c:1204` `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)`
- `sf_ws_fd` (function) `src/secure_fetch.c:1226` `int sf_ws_fd(const sf_ws *ws)`
- `sf_ws_close` (function) `src/secure_fetch.c:1233` `void sf_ws_close(sf_ws *ws)`

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
- `sv_flag` (function) `src/svg_render.c:477` `static int sv_flag(const char *s, size_t n, size_t *i, double *out)` -- An arc flag (SVG 1.1 path grammar): exactly one '0' or '1' character, with no separator required after it -- `a5 5 0...
- `sv_parse_path` (function) `src/svg_render.c:488` `static void sv_parse_path(sv_image *im, sv_shape *sh, const char *s, size_t n)` -- Parses path data.
- `point` (function) `src/svg_render.c:567` `* current point (SVG 8.3.6). */ int had = (prev == 'C' || prev == 'c' || prev == 'S' || prev == 's');`
- `sv_is_dropped_element` (function) `src/svg_render.c:646` `static int sv_is_dropped_element(const char *name, size_t n)` -- True for elements whose whole subtree is dropped. <image>/<use>/<foreignObject> can name external resources...
- `sv_scan_attrs` (function) `src/svg_render.c:658` `static void sv_scan_attrs(const char *s, size_t n, size_t *i,
                          sv_attr *...` -- Scans the attributes of a tag whose body starts at s[*i] (just past the name). * Stops at '>' and reports whether...
- `sv_skip_subtree` (function) `src/svg_render.c:704` `static void sv_skip_subtree(const char *s, size_t n, size_t *i, const char *name, size_t nlen)` -- Skips to just past the matching close tag of `name`, honouring nesting.
- `sv_collect_text` (function) `src/svg_render.c:736` `static void sv_collect_text(const char *s, size_t n, size_t *i, char *dst, size_t cap)` -- Collects the literal text of the element that just opened, up to its close tag, * into a bounded buffer.
- `sv_fit` (function) `src/svg_render.c:754` `void sv_fit(const sv_image *img, double dw, double dh,
            double *scale, double *off_x, ...`
- `sv_parse` (function) `src/svg_render.c:774` `sv_status sv_parse(const char *markup, size_t len, sv_image *out)`
- `sv_parse_ex` (function) `src/svg_render.c:778` `sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill)`

## src/tab.c
Depends on: `include/anti_fp.h`, `include/box_tree.h`, `include/css.h`, `include/css_gradient.h`, `include/data_url.h`, `include/dom.h`, `include/flex_layout.h`, `include/freebug.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/image_decode.h`, `include/import_map.h`, `include/js_dom.h`, `include/js_env.h`, `include/js_sandbox.h`, `include/js_trusted.h`, `include/link_nav.h`, `include/os_sandbox.h`, `include/page_view.h`, `include/request_policy.h`, `include/tab.h`, `include/url.h`, `include/util.h`, `include/web_storage.h`
- `rad_len_ok` (function) `src/tab.c:72` `static int rad_len_ok(int32_t v, int dflt)` -- A radial-gradient length off the wire (cg_radial encoding): per-mille 0..1e6, or * -(px)-1 with px <= 100000, or...
- `child_reset_page` (function) `src/tab.c:166` `static void child_reset_page(child_state *cs)`
- `policy` (function) `src/tab.c:186` `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a
 * compromi...`
- `run_js` (function) `src/tab.c:240` `* regardless of run_js (a no-JS load simply never records a request). */
static int child_load(ch...`
- `buffer` (function) `src/tab.c:283` `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...`
- `host` (function) `src/tab.c:295` `* granted net access for this host (allow.conf AND js.conf). Otherwise they stay * undefined...`
- `write_field` (function) `src/tab.c:307` `static int write_field(int fd, const char *s)` -- Writes one length-prefixed string field (the write mirror of read_field): a size_t * length then the bytes, with...
- `blocks` (function) `src/tab.c:341` `*
 * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the
 * grid arr...`
- `FB_MAX_FILE_BYTES` (function) `src/tab.c:767` `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...`
- `budget_remaining_ms` (function) `src/tab.c:797` `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` -- Milliseconds of `budget_ms` still left since `start` (CLOCK_MONOTONIC), 0 if spent. * Used to share one page-wide JS...
- `ctype_is_javascript` (function) `src/tab.c:811` `static int ctype_is_javascript(const char *ctype)` -- Content-Type gate for an external script's response (anti type-confusion, fail closed for real content types)...
- `ctype_is_css` (function) `src/tab.c:820` `static int ctype_is_css(const char *ctype)` -- Content-Type gate for an external stylesheet (Hito 27), same shape as the script gate: a missing/empty type is...
- `log_external_skip` (function) `src/tab.c:828` `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...` -- Freebug note about an external subresource (script/stylesheet) that was not used (skipped or refused).
- `run` (function) `src/tab.c:846` `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...`
- `tab_url_resolve` (function) `src/tab.c:895` `static int tab_url_resolve(void *ctx, const char *base, const char *ref,
                        ...` -- Plain URL resolution of ref against base (https, or a local file confined to its * document's directory): the...
- `tab_mod_resolve` (function) `src/tab.c:904` `static int tab_mod_resolve(void *host, const char *base, const char *spec,
                      ...`
- `tab_mod_fetch` (function) `src/tab.c:926` `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` -- Loads a module's source through the trusted parent (TAG_SUBREQ: the full network policy applies), only inside a...
- `write_history` (function) `src/tab.c:948` `static int write_history(int wfd, child_state *cs)` -- Writes the history block of a response: [len][ops "K url\n"...][go:int32] * (spec/js_dom.md 7e).
- `window` (function) `src/tab.c:967` `* net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs)`
- `child_handle_load` (function) `src/tab.c:1012` `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...`
- `fallback` (function) `src/tab.c:1088` `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it...`
- `WHERE` (function) `src/tab.c:1246` `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...`
- `content` (function) `src/tab.c:1282` `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...`
- `once` (function) `src/tab.c:1327` `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);`
- `swap` (function) `src/tab.c:1336` `* display:none hiding an element via class swap (CSS, not
     * DOM removal). */
    if (ok && v...`
- `write_full` (function) `src/tab.c:1356` `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0) && write_view(wfd...`
- `write_ws` (function) `src/tab.c:1378` `static int write_ws(int wfd, child_state *cs)` -- Writes the WebSocket block of a response: [n:int32] then per op * [kind:int32][id:int32][len][bytes] (spec/js_dom.md...
- `write_storage` (function) `src/tab.c:1395` `static int write_storage(int wfd, child_state *cs)` -- int32_t cnt = (int32_t)n; int rc = (write_full(wfd, &cnt, sizeof cnt) == 0) ?
- `write_opens` (function) `src/tab.c:1409` `static int write_opens(int wfd, child_state *cs)` -- static int write_storage(int wfd, child_state *cs) { char *blob = NULL; size_t len = 0; int32_t dirty = (cs->js !=...
- `child_next_timer_ms` (function) `src/tab.c:1421` `static int32_t child_next_timer_ms(child_state *cs)` -- Smallest pending JS timer delay (__nextTimerMs), or -1 when JS is absent, the * eval fails, or nothing is pending.
- `child_handle_mutation` (function) `src/tab.c:1436` `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...` -- Fire click handlers for node_id (OP_CLICK) or advance the virtual timer clock (OP_TICK), then re-derive the view so...
- `child_handle_click` (function) `src/tab.c:1515` `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)`
- `child_handle_tick` (function) `src/tab.c:1519` `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)`
- `child_handle_event` (function) `src/tab.c:1529` `static void child_handle_event(int wfd, child_state *cs)`
- `child_handle_mouse` (function) `src/tab.c:1577` `static void child_handle_mouse(int wfd, child_state *cs)` -- Handles a mouse DOM event (OP_MOUSE).
- `geom_parent` (function) `src/tab.c:1607` `static dom_node_id geom_parent(void *ctx, dom_node_id n)`
- `child_handle_geom` (function) `src/tab.c:1615` `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` -- OP_GEOM (spec/js_geom.md): installs the parent's laid-out geometry into the page's JS, aggregated into ancestors...
- `child_handle_submit` (function) `src/tab.c:1639` `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` -- Fires a submit event on the form enclosing node_id.
- `child_handle_eval` (function) `src/tab.c:1673` `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` -- Response: [ok:int32][is_exception:int32][value_len][value]. ok==0 means a worker-level failure (no page loaded); a...
- `child_handle_decode_image` (function) `src/tab.c:1706` `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` -- Response: [ok:int32] then, when ok, [w:u32][h:u32][stride:u32][len:size_t][data].
- `child_handle_decode_image_b64` (function) `src/tab.c:1728` `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)` -- data: URI images: the parent only sliced the base64 payload (pure pointer arithmetic, no interpretation); the base64...
- `gen_session_key` (function) `src/tab.c:1740` `static uint64_t gen_session_key(void)`
- `tab_worker_run` (function) `src/tab.c:1760` `static void tab_worker_run(int rfd, int wfd)` -- The confined request loop.
- `EPIPE` (function) `src/tab.c:1762` `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();`
- `tzset` (function) `src/tab.c:1778` `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);`
- `depth` (function) `src/tab.c:1783` `* defense in depth (seccomp already excludes open/socket/exec);`
- `parse_worker_fd` (function) `src/tab.c:1958` `static int parse_worker_fd(const char *s, int *out)` -- free(buf); free(url); free(cookies); free(storage); } child_reset_page(&cs); fb_buffer_free(&cs.log); _exit(0); } /*...
- `tab_parse_worker_args` (function) `src/tab.c:1970` `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)`
- `tab_worker_dispatch` (function) `src/tab.c:1980` `void tab_worker_dispatch(int argc, char **argv)`
- `load` (function) `src/tab.c:1997` `* subresource requests this load (set per page: host in allow.conf AND js.conf);`
- `ignore_sigpipe` (function) `src/tab.c:2018` `static void ignore_sigpipe(void)` -- A write to a dead child must not kill the parent with SIGPIPE.
- `tab_refresh_alive` (function) `src/tab.c:2025` `static void tab_refresh_alive(tab *t)`
- `read_field` (function) `src/tab.c:2044` `static int read_field(int fd, char **out, size_t *out_len)` -- Read one length-prefixed owned field from the child, capped against * amplification. *out is NUL-terminated.
- `read_view` (function) `src/tab.c:2060` `static int read_view(int fd, pv_view **out)` -- Reads a display list serialised by write_view into a fresh pv_view.
- `tests` (function) `src/tab.c:2135` `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...`
- `layout` (function) `src/tab.c:2240` `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....`
- `column` (function) `src/tab.c:2251` `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...`
- `read_console` (function) `src/tab.c:2582` `static int read_console(int fd, fb_buffer *out)` -- Reads the console section written by write_console into out (a zero-initialised fb_buffer).
- `send_request` (function) `src/tab.c:2619` `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` -- if (elen != 0) { txt = (char *)malloc(elen); if (txt == NULL) { free(file); return -1; } if (read_full(fd, txt...
- `io_failure` (function) `src/tab.c:2629` `static tab_status io_failure(tab *t)`
- `exec_worker_child` (function) `src/tab.c:2637` `static void exec_worker_child(int rfd, int wfd)` -- Child half of the fork: re-exec a fresh worker image so it inherits NONE of the parent's address space (no other...
- `tab_set_fetcher` (function) `src/tab.c:2708` `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)`
- `tab_set_css_sink` (function) `src/tab.c:2714` `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)`
- `tab_set_net_allowed` (function) `src/tab.c:2720` `void tab_set_net_allowed(tab *t, int allowed)`
- `tab_set_css_allowed` (function) `src/tab.c:2725` `void tab_set_css_allowed(tab *t, int allowed)`
- `tab_last_subreq_stats` (function) `src/tab.c:2730` `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)`
- `tab_set_viewport_w` (function) `src/tab.c:2735` `void tab_set_viewport_w(tab *t, int px)`
- `tab_set_cookies` (function) `src/tab.c:2740` `void tab_set_cookies(tab *t, const char *cookies)`
- `tab_subreq_permitted` (function) `src/tab.c:2746` `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)`
- `answered` (function) `src/tab.c:2758` `* A refused frame is still consumed and answered (status 0), so the protocol never
 * desyncs. Re...`
- `hist_ops_free` (function) `src/tab.c:2801` `static void hist_ops_free(tab_hist_op *ops, size_t n)`
- `is_activation_event` (function) `src/tab.c:2866` `static int is_activation_event(const char *type)` -- HTML 6.4.2 activation-triggering input events: only these let a page open a * window.
- `open_urls_free` (function) `src/tab.c:2875` `static void open_urls_free(char **u, size_t n)`
- `read_opens` (function) `src/tab.c:2885` `static tab_status read_opens(tab *t, const char *page_url, int gesture,
                         ...` -- Reads the window.open block (see write_opens).
- `ws_ops_free` (function) `src/tab.c:2914` `static void ws_ops_free(tab_ws_op *ops, size_t n)`
- `read_ws` (function) `src/tab.c:2923` `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` -- Reads the WebSocket block (see write_ws), bounded by JT_WS_MAX_OPS ops and JT_WS_MAX_BYTES of payload.
- `gate_js_nav` (function) `src/tab.c:2992` `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` -- Gates a raw JS navigation request against the page URL in the trusted parent (Zero Trust: a compromised worker...
- `tab_load` (function) `src/tab.c:3002` `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)`
- `tab_load_ex` (function) `src/tab.c:3006` `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)`
- `tab_load_full` (function) `src/tab.c:3010` `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...`
- `tab_click` (function) `src/tab.c:3205` `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)`
- `tab_tick` (function) `src/tab.c:3212` `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)`
- `tab_submit` (function) `src/tab.c:3221` `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` -- Dispatches a submit event on the form enclosing node_id.
- `tab_read_view` (function) `src/tab.c:3326` `tab_status tab_read_view(tab *t, tab_page *out)` -- Reads the TAG_RESULT + TAG_VIEW response into *out (titles + view + console). * Used by tab_mutation_request...
- `tab_read_view_ex` (function) `src/tab.c:3330` `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)`
- `tab_eval` (function) `src/tab.c:3426` `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)`
- `tab_decode_image_op` (function) `src/tab.c:3466` `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...` -- Shared by tab_decode_image and tab_decode_image_data_url: sends `bytes` under opcode `op` and parses the...
- `tab_decode_image` (function) `src/tab.c:3508` `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)`
- `tab_decode_image_data_url` (function) `src/tab.c:3514` `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)`
- `tab_alive` (function) `src/tab.c:3532` `int tab_alive(const tab *t)`
- `tab_child_pid` (function) `src/tab.c:3538` `pid_t tab_child_pid(const tab *t)`
- `tab_close` (function) `src/tab.c:3542` `void tab_close(tab *t)`
- `tab_page_free` (function) `src/tab.c:3557` `void tab_page_free(tab_page *p)`
- `tab_eval_result_free` (function) `src/tab.c:3587` `void tab_eval_result_free(tab_eval_result *r)`
- `tab_image_free` (function) `src/tab.c:3596` `void tab_image_free(tab_image *img)`
- `tab_set_geometry` (function) `src/tab.c:3606` `tab_status tab_set_geometry(tab *t, const jg_table *g)`
- `tab_popstate` (function) `src/tab.c:3632` `tab_status tab_popstate(tab *t, int index, tab_page *out)`
- `tab_ws_event` (function) `src/tab.c:3638` `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,
       ...`
- `tab_set_storage` (function) `src/tab.c:3657` `void tab_set_storage(tab *t, const char *blob, size_t len)`

## src/text_case.c
Depends on: `include/css.h`, `include/text_case.h`
- `pair_parity` (function) `src/text_case.c:8` `static int pair_parity(uint32_t cp)` -- Latin Extended-A and the Cyrillic historic block pair letters on adjacent code points, uppercase first.
- `tc_upper` (function) `src/text_case.c:18` `uint32_t tc_upper(uint32_t cp)`
- `tc_lower` (function) `src/text_case.c:37` `uint32_t tc_lower(uint32_t cp)`
- `tc_is_lower` (function) `src/text_case.c:54` `int tc_is_lower(uint32_t cp)`
- `utf8_decode` (function) `src/text_case.c:61` `static size_t utf8_decode(const unsigned char *s, size_t n, uint32_t *cp)` -- Decodes one UTF-8 code point of s[0,n) into *cp.
- `utf8_put` (function) `src/text_case.c:79` `static void utf8_put(uint32_t cp, size_t len, unsigned char *out)` -- if ((c >> 5) == 0x6) { if (n < 2 || (s[1] & 0xC0) != 0x80) return 0; cp = ((c & 0x1Fu) << 6) | (s[1] & 0x3Fu)...
- `utf8_len_of` (function) `src/text_case.c:91` `static size_t utf8_len_of(uint32_t cp)`
- `tc_transform` (function) `src/text_case.c:95` `size_t tc_transform(const char *s, size_t n, int transform, int word_start,
                    c...`
- `tc_smallcaps_runs` (function) `src/text_case.c:117` `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap)`

## src/text_shape.c
Depends on: `include/css.h`, `include/text_shape.h`, `include/webfont.h`
- `generic_name` (function) `src/text_shape.c:55` `static const char *generic_name(int family)`
- `backend_init` (function) `src/text_shape.c:65` `static int backend_init(void)`
- `read_font_file` (function) `src/text_shape.c:82` `static unsigned char *read_font_file(const char *path, long *out_n)`
- `characters` (function) `src/text_shape.c:100` `* hold characters ('-', ':') that the pattern syntax treats specially. */ static int load_entry_file(tsh_entry *e...`
- `load_entry_named` (function) `src/text_shape.c:103` `static int load_entry_named(tsh_entry *e, const char *fam, int bold, int italic)`
- `load_entry_file` (function) `src/text_shape.c:133` `static int load_entry_file(tsh_entry *e, const char *path, int index)` -- Loads face `index` of the font file at `path` into e (FreeType + cairo + * HarfBuzz over one owned copy of the bytes).
- `load_entry` (function) `src/text_shape.c:169` `static int load_entry(tsh_entry *e, int family, int bold, int italic)`
- `get_entry` (function) `src/text_shape.c:173` `static tsh_entry *get_entry(int family, int bold, int italic)`
- `web_entry_free` (function) `src/text_shape.c:201` `static void web_entry_free(tsh_web *w)`
- `slice` (function) `src/text_shape.c:213` `* woff2 slice (spec/webfont.md);`
- `web_magic_ok` (function) `src/text_shape.c:214` `static int web_magic_ok(const unsigned char *b, size_t n)` -- True for font programs FreeType parses without new decoders: wOFF/TrueType/ CFF-OpenType (and the mac aliases). wOF2...
- `web_make_entry` (function) `src/text_shape.c:227` `static int web_make_entry(tsh_entry *e, const unsigned char *bytes, size_t nbytes)` -- Builds the shaping faces over an OWNED copy of bytes[0,nbytes) into e (shared tail with load_entry's file path: same...
- `tsh_webfont_register` (function) `src/text_shape.c:267` `int tsh_webfont_register(const char *name,
                         const unsigned char *bytes, s...`
- `tsh_webfont_clear` (function) `src/text_shape.c:301` `void tsh_webfont_clear(void)`
- `web_find` (function) `src/text_shape.c:306` `static tsh_entry *web_find(unsigned h, int bold, int italic)`
- `entry_free` (function) `src/text_shape.c:318` `static void entry_free(tsh_entry *e)`
- `ascii_ieq` (function) `src/text_shape.c:331` `static int ascii_ieq(const char *a, const char *b)`
- `tsh_family_is_generic` (function) `src/text_shape.c:340` `int tsh_family_is_generic(const char *name)`
- `tsh_pick_from_list` (function) `src/text_shape.c:352` `int tsh_pick_from_list(const char *list, tsh_name_resolver resolve, void *ctx,
                  ...`
- `tsh_pick_family` (function) `src/text_shape.c:373` `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong,
        ...`
- `fc_installed` (function) `src/text_shape.c:386` `static int fc_installed(const char *name, void *ctx)` -- const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong, size_t n, int...
- `fc_resolve` (function) `src/text_shape.c:429` `static int fc_resolve(const char *name, char *out, size_t cap, void *ctx)`
- `local_clear` (function) `src/text_shape.c:474` `static void local_clear(void)`
- `lfam_index` (function) `src/text_shape.c:484` `static int lfam_index(const char *fam)`
- `tsh_local_handle` (function) `src/text_shape.c:492` `int tsh_local_handle(const char *list)`
- `local_entry` (function) `src/text_shape.c:511` `static tsh_entry *local_entry(int handle, int bold, int italic)`
- `get_entry_ex` (function) `src/text_shape.c:531` `static tsh_entry *get_entry_ex(const tsh_font *f)` -- Entry for a full font selector: a registered @font-face wins over the local bucket stack; a set-but-unregistered...
- `tsh_ready` (function) `src/text_shape.c:543` `int tsh_ready(void)`
- `tsh_shape` (function) `src/text_shape.c:548` `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                ...`
- `utf8_next` (function) `src/text_shape.c:597` `static unsigned utf8_next(const char *s, size_t n, size_t *len)` -- Decodes one UTF-8 sequence at s[0..n): the code point (U+FFFD for a malformed * sequence) and its byte length (>= 1...
- `rides_previous` (function) `src/text_shape.c:614` `static int rides_previous(unsigned cp)` -- size_t l = (c < 0x80) ?
- `tsh_segment` (function) `src/text_shape.c:622` `int tsh_segment(const char *text, size_t len, tsh_cover_fn cover, void *ctx,
                tsh_...`
- `fb_clear` (function) `src/text_shape.c:662` `static void fb_clear(void)`
- `fb_entry` (function) `src/text_shape.c:672` `static tsh_entry *fb_entry(unsigned cp, int bold)` -- The fallback entry covering cp (bold or regular), or NULL.
- `cover_cp` (function) `src/text_shape.c:743` `static int cover_cp(unsigned cp, void *vctx)` -- cover callback: 0 when the requested face has the glyph (or nothing else * does), else the id of the fallback face...
- `shape_entry` (function) `src/text_shape.c:756` `static tsh_status shape_entry(tsh_entry *e, double px, const char *text, size_t len,
            ...` -- does), else the id of the fallback face that has it. static int cover_cp(unsigned cp, void *vctx) { tsh_cover_ctx *c...
- `shape_runs` (function) `src/text_shape.c:787` `static tsh_status shape_runs(cairo_t *cr, const tsh_font *f, double px, double x,
               ...` -- Measures (cr == NULL) or draws [text,len) run by run, each with the face that * has its glyphs.
- `tsh_measure` (function) `src/text_shape.c:829` `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)`
- `tsh_draw` (function) `src/text_shape.c:835` `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, doub...`
- `tsh_face` (function) `src/text_shape.c:842` `cairo_font_face_t *tsh_face(const tsh_font *f)`
- `tsh_shutdown` (function) `src/text_shape.c:848` `void tsh_shutdown(void)`

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

## src/wl_display.c
Depends on: `include/wl_display.h`
- `wd_index` (function) `src/wl_display.c:13` `static int wd_index(const char *name, unsigned long *idx)`
- `wd_pick` (function) `src/wl_display.c:27` `int wd_pick(const char *const *names, size_t n, char *out, size_t cap)`
- `wd_resolve_env` (function) `src/wl_display.c:42` `int wd_resolve_env(void)`

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

## tools/fbench.py
- `load_baseline` (function) `tools/fbench.py:46` `def load_baseline()`
- `load_current` (function) `tools/fbench.py:59` `def load_current()`
- `luma` (function) `tools/fbench.py:72` `def luma(img)`
- `bands` (function) `tools/fbench.py:76` `def bands(fd, ff, band)`
- `sbs` (function) `tools/fbench.py:88` `def sbs(name, start, nrows)`
- `publish_readme` (function) `tools/fbench.py:107` `def publish_readme(name, score)` -- Rewrite the README picture of `name` and the score printed beside its label.
- `main` (function) `tools/fbench.py:127` `def main()`

## tools/ffgeom.py
- `load_rows` (function) `tools/ffgeom.py:116` `def load_rows(path)`
- `lum` (function) `tools/ffgeom.py:169` `def lum(p)`
- `lum_at` (function) `tools/ffgeom.py:181` `def lum_at(x, y)`
- `bit` (function) `tools/ffgeom.py:206` `def bit(grid_row, cell, origin)`
- `word` (function) `tools/ffgeom.py:209` `def word(grid_row, origin)`
- `decode` (function) `tools/ffgeom.py:239` `def decode(path)`
- `probe` (function) `tools/ffgeom.py:265` `def probe(page, selector, out_html)`
- `height_probe` (function) `tools/ffgeom.py:279` `def height_probe(page, out_html)`
- `height` (function) `tools/ffgeom.py:292` `def height(path)` -- Decodes the scrollHeight carried by the #__ffh sentinel: the probe encodes one rect (its height), which decode()...
- `main` (function) `tools/ffgeom.py:301` `def main(argv)`

## tools/ffq.py
- `main` (function) `tools/ffq.py:22` `def main()`


Next: [API_p11.md](API_p11.md)
