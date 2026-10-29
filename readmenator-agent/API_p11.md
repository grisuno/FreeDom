# API (page 11 of 12)
Previous: [API_p10.md](API_p10.md)

## src/secure_fetch.c
Depends on: `include/anti_fp.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/url.h`
- `ci_starts_with` (function) `src/secure_fetch.c:46` `static int ci_starts_with(const char *haystack, const char *prefix)` -- /* --- small helpers (no libc locale dependence) --- static int ci_equal(const char *a, const char *b) { while (*a...
- `ci_index` (function) `src/secure_fetch.c:58` `static long ci_index(const char *haystack, const char *needle)` -- /* Case-insensitive: does haystack start with prefix? static int ci_starts_with(const char *haystack, const char...
- `sf_share_lock` (function) `src/secure_fetch.c:74` `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...`
- `sf_share_unlock` (function) `src/secure_fetch.c:80` `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)`
- `sf_global_init` (function) `src/secure_fetch.c:87` `void sf_global_init(void)`
- `sf_cookie_line_matches` (function) `src/secure_fetch.c:112` `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...`
- `sf_url_host_path` (function) `src/secure_fetch.c:167` `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...` -- Extracts host + path from a validated https url into caller buffers (path defaults * to "/").
- `sf_cookie_header_for` (function) `src/secure_fetch.c:182` `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)`
- `sf_cookie_put` (function) `src/secure_fetch.c:211` `void sf_cookie_put(const char *url, const char *namevalue)`
- `sf_config_default` (function) `src/secure_fetch.c:232` `sf_config sf_config_default(void)`
- `header_value_clean` (function) `src/secure_fetch.c:258` `static int header_value_clean(const char *s)` -- c.password = NULL; c.insecure = 0; c.impersonate = 0; /* default hardened PQ-hybrid ClientHello; opt-in per trusted...
- `sf_user_agent_or_default` (function) `src/secure_fetch.c:264` `const char *sf_user_agent_or_default(const char *ua)`
- `sf_accept_language_or_default` (function) `src/secure_fetch.c:268` `const char *sf_accept_language_or_default(const char *lang)`
- `sf_impersonate_kex_groups` (function) `src/secure_fetch.c:272` `const char *sf_impersonate_kex_groups(void)`
- `sf_impersonate_tls13_ciphers` (function) `src/secure_fetch.c:273` `const char *sf_impersonate_tls13_ciphers(void)`
- `sf_validate_url` (function) `src/secure_fetch.c:277` `sf_status sf_validate_url(const char *url)`
- `sf_url_is_http` (function) `src/secure_fetch.c:285` `static int sf_url_is_http(const char *url)` -- Nonzero iff url is "http://host..." (case-insensitive) with a non-empty host.
- `sf_check_tls_version` (function) `src/secure_fetch.c:297` `sf_status sf_check_tls_version(const char *negotiated_version)`
- `sf_check_group_is_pq` (function) `src/secure_fetch.c:302` `sf_status sf_check_group_is_pq(const char *negotiated_group)`
- `sf_check_chain_policy` (function) `src/secure_fetch.c:311` `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)`
- `sf_enforce_policy` (function) `src/secure_fetch.c:321` `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...`
- `copy_checked` (function) `src/secure_fetch.c:352` `static int copy_checked(char *dst, size_t dstsz, const char *src)`
- `sf_is_redirect_code` (function) `src/secure_fetch.c:361` `int sf_is_redirect_code(long http_code)`
- `sf_header_value` (function) `src/secure_fetch.c:368` `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz)`
- `sf_parse_location_header` (function) `src/secure_fetch.c:390` `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)`
- `sf_resolve_redirect` (function) `src/secure_fetch.c:408` `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...`
- `module` (function) `src/secure_fetch.c:413` `* pure url module (DRY);`
- `sf_ci_prefix` (function) `src/secure_fetch.c:420` `static int sf_ci_prefix(const char *s, const char *p)` -- Reference resolution + the https-only / no-downgrade policy live in the pure url module (DRY); a redirect is just a...
- `sf_response_free` (function) `src/secure_fetch.c:460` `void sf_response_free(sf_response *resp)`
- `progress` (function) `src/secure_fetch.c:499` `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);`
- `copy_bounded` (function) `src/secure_fetch.c:530` `static void copy_bounded(char *dst, size_t dstsz, const char *src)`
- `get_negotiated_group_name` (function) `src/secure_fetch.c:541` `static const char *get_negotiated_group_name(SSL *ssl)` -- static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len); static void...
- `database` (function) `src/secure_fetch.c:545` `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid...`
- `group` (function) `src/secure_fetch.c:559` `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);`
- `tls_capture_try` (function) `src/secure_fetch.c:574` `static void tls_capture_try(tls_capture *cap)` -- nid = SSL_get_shared_group(ssl, 0); #endif if (nid == 0) { return NULL; /* There is no negotiated group (e.g., TLS...
- `tls_capture_from_ssl` (function) `src/secure_fetch.c:584` `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)` -- static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl); /* Idempotent: takes the TLS snapshot the first time...
- `this` (function) `src/secure_fetch.c:591` `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and...`
- `header_cb` (function) `src/secure_fetch.c:610` `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` -- Fires for every HTTP response (status line + headers) even when there is no * body, so it is the reliable point to...
- `write_cb` (function) `src/secure_fetch.c:667` `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)`
- `name_is_pq_sig` (function) `src/secure_fetch.c:699` `static int name_is_pq_sig(int pknid)` -- if (grown == NULL) { sink->overflow = 2; /* OOM marker return 0; } sink->data = grown; sink->cap = newcap; }...
- `inspect_chain` (function) `src/secure_fetch.c:709` `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` -- Walks the verified chain into *info. sigbuf receives the leaf signature alg name. * Returns 0 on success, nonzero if...
- `map_curl_error` (function) `src/secure_fetch.c:762` `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)`
- `add_header` (function) `src/secure_fetch.c:803` `static int add_header(struct curl_slist **h, const char *line)` -- Appends one header line without losing the list on OOM (the plain "h = curl_slist_append(h, ...)" idiom dropped the...
- `sf_setup_handle` (function) `src/secure_fetch.c:817` `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,
           ...` -- The ONE place a curl handle is configured for a request (spec/secure_fetch.md): URL, realm proxy, TLS floor + KE...
- `redirect` (function) `src/secure_fetch.c:892` `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...`
- `sf_perform` (function) `src/secure_fetch.c:984` `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...` -- The shared request engine for sf_get and sf_post.
- `sf_get` (function) `src/secure_fetch.c:1144` `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)`
- `sf_post` (function) `src/secure_fetch.c:1148` `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...`
- `sf_rcache_clear` (function) `src/secure_fetch.c:1178` `void sf_rcache_clear(void)`
- `sf_rcache_set_backing` (function) `src/secure_fetch.c:1189` `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx)`
- `rcache_put_ram` (function) `src/secure_fetch.c:1197` `static int rcache_put_ram(const char *from, const char *to, time_t now)`
- `sf_rcache_put` (function) `src/secure_fetch.c:1216` `int sf_rcache_put(const char *from, const char *to, time_t now)`
- `sf_rcache_get` (function) `src/secure_fetch.c:1226` `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap)`
- `sf_get_follow` (function) `src/secure_fetch.c:1255` `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...`
- `ws_ssl_info_cb` (function) `src/secure_fetch.c:1318` `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)` -- An upgraded (CONNECT_ONLY) connection never runs the header callback that snapshots TLS for a fetch, and curl no...
- `ws_ssl_ctx_cb` (function) `src/secure_fetch.c:1325` `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)`
- `sf_ws_url_check` (function) `src/secure_fetch.c:1339` `sf_status sf_ws_url_check(const char *url)`
- `ws_free` (function) `src/secure_fetch.c:1351` `static void ws_free(sf_ws *ws)`
- `sf_ws_open` (function) `src/secure_fetch.c:1360` `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)`
- `sf_ws_send` (function) `src/secure_fetch.c:1415` `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)`
- `sf_ws_recv` (function) `src/secure_fetch.c:1438` `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)`
- `sf_ws_fd` (function) `src/secure_fetch.c:1460` `int sf_ws_fd(const sf_ws *ws)`
- `sf_ws_close` (function) `src/secure_fetch.c:1467` `void sf_ws_close(sf_ws *ws)`
- `sf_fallback_policy` (function) `src/secure_fetch.c:1478` `int sf_fallback_policy(sf_status failed, sf_policy tried, int allowlisted, sf_policy *next)`
- `sf_downgrade_of` (function) `src/secure_fetch.c:1492` `static int sf_downgrade_of(sf_policy p)`
- `sf_attempt_get` (function) `src/secure_fetch.c:1501` `static sf_status sf_attempt_get(const char *url, const sf_config *cfg, sf_response *out,
        ...`
- `sf_attempt_post` (function) `src/secure_fetch.c:1507` `static sf_status sf_attempt_post(const char *url, const sf_config *cfg, sf_response *out,
       ...`
- `sf_navigable` (function) `src/secure_fetch.c:1512` `static sf_status sf_navigable(sf_attempt_fn attempt, const char *url, sf_config *cfg,
           ...`
- `sf_get_follow_navigable` (function) `src/secure_fetch.c:1532` `sf_status sf_get_follow_navigable(const char *url, sf_config *cfg, sf_response *out,
            ...`
- `sf_post_navigable` (function) `src/secure_fetch.c:1537` `sf_status sf_post_navigable(const char *url, sf_config *cfg, const void *body,
                  ...`

## src/sha2.c
Depends on: `include/sha2.h`
- `sha_digest_len` (function) `src/sha2.c:12` `size_t sha_digest_len(sha_alg alg)`
- `ieq` (function) `src/sha2.c:22` `static int ieq(const char *a, const char *b)`
- `sha_alg_from_name` (function) `src/sha2.c:31` `int sha_alg_from_name(const char *name, sha_alg *out)`
- `be32` (function) `src/sha2.c:40` `static uint32_t be32(const uint8_t *p)`
- `be64` (function) `src/sha2.c:43` `static uint64_t be64(const uint8_t *p)`
- `put32` (function) `src/sha2.c:44` `static void put32(uint8_t *p, uint32_t v)`
- `put64` (function) `src/sha2.c:45` `static void put64(uint8_t *p, uint64_t v)`
- `pad_tail` (function) `src/sha2.c:49` `static size_t pad_tail(uint8_t *blk, size_t bs, size_t lenbytes, const uint8_t *tail, size_t tl,
...` -- Pads the tail of a message into at most two blocks of `bs` bytes with a `lenbytes`-byte * big-endian bit length.
- `sha1_block` (function) `src/sha2.c:61` `static void sha1_block(uint32_t h[5], const uint8_t *p)`
- `sha256_block` (function) `src/sha2.c:88` `static void sha256_block(uint32_t h[8], const uint8_t *p)`
- `sha512_block` (function) `src/sha2.c:131` `static void sha512_block(uint64_t h[8], const uint8_t *p)`
- `sha_digest` (function) `src/sha2.c:152` `int sha_digest(sha_alg alg, const void *data, size_t len, uint8_t *out)`

## src/subreq_batch.c
Depends on: `include/subreq_batch.h`
- `dup_n` (function) `src/subreq_batch.c:30` `static char *dup_n(const char *s, size_t n)`
- `res_clear` (function) `src/subreq_batch.c:39` `static void res_clear(sqb_res *r)`
- `job_free` (function) `src/subreq_batch.c:44` `static void job_free(sqb_job *j)`
- `job_main` (function) `src/subreq_batch.c:51` `static void *job_main(void *arg)`
- `sqb_new` (function) `src/subreq_batch.c:75` `sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx)`
- `sqb_submit` (function) `src/subreq_batch.c:86` `int sqb_submit(sqb *b, int refused, const sqb_req *req)`
- `sqb_count` (function) `src/subreq_batch.c:112` `size_t sqb_count(const sqb *b)`
- `sqb_wait_all` (function) `src/subreq_batch.c:114` `void sqb_wait_all(sqb *b)`
- `sqb_result` (function) `src/subreq_batch.c:122` `const sqb_res *sqb_result(const sqb *b, size_t i)`
- `sqb_reset` (function) `src/subreq_batch.c:126` `void sqb_reset(sqb *b)`
- `sqb_free` (function) `src/subreq_batch.c:133` `void sqb_free(sqb *b)`

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
Depends on: `include/anti_fp.h`, `include/box_tree.h`, `include/css.h`, `include/css_computed.h`, `include/css_gradient.h`, `include/data_url.h`, `include/dom.h`, `include/flex_layout.h`, `include/freebug.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/identity.h`, `include/image_decode.h`, `include/import_map.h`, `include/js_dom.h`, `include/js_env.h`, `include/js_sandbox.h`, `include/js_trusted.h`, `include/link_nav.h`, `include/os_sandbox.h`, `include/page_view.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/subreq_batch.h`, `include/tab.h`, `include/url.h`, `include/util.h`, `include/web_storage.h`
- `tab_wflush` (function) `src/tab.c:66` `static int tab_wflush(void)`
- `tab_write_full` (function) `src/tab.c:73` `static int tab_write_full(int fd, const void *buf, size_t n)`
- `tab_read_full` (function) `src/tab.c:85` `static int tab_read_full(int fd, void *buf, size_t n)`
- `clip_pm_ok` (function) `src/tab.c:145` `static int clip_pm_ok(int32_t v)` -- A clip-edge percentage off the wire: per-mille, bounded like CSS_PCT_MAX (a hostile * worker cannot hand the painter...
- `rad_len_ok` (function) `src/tab.c:151` `static int rad_len_ok(int32_t v, int dflt)` -- A radial-gradient length off the wire (cg_radial encoding): per-mille 0..1e6, or * -(px)-1 with px <= 100000, or...
- `child_reset_page` (function) `src/tab.c:270` `static void child_reset_page(child_state *cs)`
- `sig_mix` (function) `src/tab.c:290` `static uint64_t sig_mix(uint64_t h, const char *s, size_t n)`
- `computed_signature` (function) `src/tab.c:298` `static uint64_t computed_signature(const dom_index *idx)` -- What the retained cascade depends on: every <style> text plus the attributes of <html>/<body> (class/data-* theme...
- `net_reply_free` (function) `src/tab.c:399` `static void net_reply_free(net_reply *r)`
- `child_write_subreq` (function) `src/tab.c:402` `static int child_write_subreq(child_state *cs, uint8_t tag, const char *method, const char *url,
...` -- compromised worker still cannot reach a blocked host.
- `child_read_reply` (function) `src/tab.c:427` `static int child_read_reply(child_state *cs, net_reply *out)` -- if (write_full(cs->wfd, &tag, 1) != 0 || write_full(cs->wfd, &mlen, sizeof mlen) != 0 || (mlen != 0 &&...
- `child_fetch` (function) `src/tab.c:455` `static int child_fetch(void *vctx, const char *method, const char *url,
                       co...`
- `child_fetch_async` (function) `src/tab.c:471` `static int child_fetch_async(void *vctx, const char *method, const char *url,
                   ...` -- int *out_status, char **out_body, size_t *out_body_len, char **out_ctype, char **out_headers) { child_state *cs =...
- `replies` (function) `src/tab.c:484` `* writing replies (no pipe deadlock). */
static void child_net_drain(child_state *cs)`
- `prof_now_ms` (function) `src/tab.c:508` `static double prof_now_ms(void)` -- int got = 0; for (; got < n; ++got) if (child_read_reply(cs, &rep[got]) != 0) break; for (int i = 0; i < got; ++i) {...
- `prof_on` (function) `src/tab.c:513` `static int prof_on(void)`
- `prof_lap` (function) `src/tab.c:518` `static void prof_lap(const char *what, double *t0)`
- `run_js` (function) `src/tab.c:529` `* regardless of run_js (a no-JS load simply never records a request). */
/* Installs the page-ind...`
- `child_load` (function) `src/tab.c:553` `static int child_load(child_state *cs, const char *html, size_t len, int run_js,
                ...`
- `buffer` (function) `src/tab.c:621` `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...`
- `write_field` (function) `src/tab.c:652` `static int write_field(int fd, const char *s)` -- Writes one length-prefixed string field (the write mirror of read_field): a size_t * length then the bytes, with...
- `blocks` (function) `src/tab.c:686` `* * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the * grid array, block B[26])...`
- `write_view` (function) `src/tab.c:694` `static int write_view(int wfd, const pv_view *v)`
- `write_view_raw` (function) `src/tab.c:705` `static int write_view_raw(int wfd, const pv_view *v)`
- `FB_MAX_FILE_BYTES` (function) `src/tab.c:1130` `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...`
- `budget_remaining_ms` (function) `src/tab.c:1160` `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` -- Milliseconds of `budget_ms` still left since `start` (CLOCK_MONOTONIC), 0 if spent. * Used to share one page-wide JS...
- `ctype_is_javascript` (function) `src/tab.c:1174` `static int ctype_is_javascript(const char *ctype)` -- Content-Type gate for an external script's response (anti type-confusion, fail closed for real content types)...
- `ctype_is_css` (function) `src/tab.c:1183` `static int ctype_is_css(const char *ctype)` -- Content-Type gate for an external stylesheet (Hito 27), same shape as the script gate: a missing/empty type is...
- `log_external_skip` (function) `src/tab.c:1191` `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...` -- Freebug note about an external subresource (script/stylesheet) that was not used (skipped or refused).
- `run` (function) `src/tab.c:1209` `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...`
- `tab_url_resolve` (function) `src/tab.c:1258` `static int tab_url_resolve(void *ctx, const char *base, const char *ref,
                        ...` -- Plain URL resolution of ref against base (https, or a local file confined to its * document's directory): the...
- `tab_mod_resolve` (function) `src/tab.c:1267` `static int tab_mod_resolve(void *host, const char *base, const char *spec,
                      ...`
- `tab_mod_fetch` (function) `src/tab.c:1297` `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` -- Loads a module's source through the trusted parent (TAG_SUBREQ: the full network policy applies), only inside a...
- `write_history` (function) `src/tab.c:1319` `static int write_history(int wfd, child_state *cs)` -- Writes the history block of a response: [len][ops "K url\n"...][go:int32] * (spec/js_dom.md 7e).
- `window` (function) `src/tab.c:1338` `* net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs)`
- `child_prescript_view` (function) `src/tab.c:1391` `static pv_view *child_prescript_view(child_state *cs, const char *html, size_t len,
             ...` -- The pre-script view, rebuilt on demand.
- `child_handle_load` (function) `src/tab.c:1421` `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...`
- `libraries` (function) `src/tab.c:1526` `* load heavier libraries (jQuery, Bootstrap, etc.) that need more time. * Untrusted hosts get the default budget...`
- `WHERE` (function) `src/tab.c:1691` `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...`
- `content` (function) `src/tab.c:1756` `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...`
- `once` (function) `src/tab.c:1807` `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);`
- `swap` (function) `src/tab.c:1816` `* display:none hiding an element via class swap (CSS, not
     * DOM removal). */
    if (ok && v...`
- `write_full` (function) `src/tab.c:1837` `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0) && write_view(wfd...`
- `write_ws` (function) `src/tab.c:1861` `static int write_ws(int wfd, child_state *cs)` -- Writes the WebSocket block of a response: [n:int32] then per op * [kind:int32][id:int32][len][bytes] (spec/js_dom.md...
- `write_storage` (function) `src/tab.c:1878` `static int write_storage(int wfd, child_state *cs)` -- int32_t cnt = (int32_t)n; int rc = (write_full(wfd, &cnt, sizeof cnt) == 0) ?
- `write_opens` (function) `src/tab.c:1892` `static int write_opens(int wfd, child_state *cs)` -- static int write_storage(int wfd, child_state *cs) { char *blob = NULL; size_t len = 0; int32_t dirty = (cs->js !=...
- `child_next_timer_ms` (function) `src/tab.c:1904` `static int32_t child_next_timer_ms(child_state *cs)` -- Smallest pending JS timer delay (__nextTimerMs), or -1 when JS is absent, the * eval fails, or nothing is pending.
- `child_handle_mutation` (function) `src/tab.c:1919` `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...` -- Fire click handlers for node_id (OP_CLICK) or advance the virtual timer clock (OP_TICK), then re-derive the view so...
- `child_handle_click` (function) `src/tab.c:2000` `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)`
- `child_handle_tick` (function) `src/tab.c:2004` `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)`
- `child_handle_event` (function) `src/tab.c:2014` `static void child_handle_event(int wfd, child_state *cs)`
- `child_handle_mouse` (function) `src/tab.c:2062` `static void child_handle_mouse(int wfd, child_state *cs)` -- Handles a mouse DOM event (OP_MOUSE).
- `geom_parent` (function) `src/tab.c:2092` `static dom_node_id geom_parent(void *ctx, dom_node_id n)`
- `child_handle_geom` (function) `src/tab.c:2100` `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` -- OP_GEOM (spec/js_geom.md): installs the parent's laid-out geometry into the page's JS, aggregated into ancestors...
- `child_handle_submit` (function) `src/tab.c:2126` `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` -- Fires a submit event on the form enclosing node_id.
- `child_handle_eval` (function) `src/tab.c:2160` `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` -- Response: [ok:int32][is_exception:int32][value_len][value]. ok==0 means a worker-level failure (no page loaded); a...
- `child_handle_decode_image` (function) `src/tab.c:2201` `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` -- Response: [ok:int32] then, when ok, [w:u32][h:u32][stride:u32][len:size_t][data].
- `child_handle_decode_image_b64` (function) `src/tab.c:2223` `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)` -- data: URI images: the parent only sliced the base64 payload (pure pointer arithmetic, no interpretation); the base64...
- `gen_session_key` (function) `src/tab.c:2235` `static uint64_t gen_session_key(void)`
- `tab_worker_run` (function) `src/tab.c:2255` `static void tab_worker_run(int rfd, int wfd)` -- The confined request loop.
- `EPIPE` (function) `src/tab.c:2257` `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();`
- `tzset` (function) `src/tab.c:2273` `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);`
- `depth` (function) `src/tab.c:2287` `* defense in depth (seccomp already excludes open/socket/exec);`
- `parse_worker_fd` (function) `src/tab.c:2486` `static int parse_worker_fd(const char *s, int *out)` -- free(buf); free(url); free(cookies); free(storage); } child_reset_page(&cs); fb_buffer_free(&cs.log); _exit(0); } /*...
- `tab_parse_worker_args` (function) `src/tab.c:2498` `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)`
- `tab_worker_dispatch` (function) `src/tab.c:2508` `void tab_worker_dispatch(int argc, char **argv)`
- `load` (function) `src/tab.c:2525` `* subresource requests this load (set per page: host in allow.conf AND js.conf);`
- `ignore_sigpipe` (function) `src/tab.c:2565` `static void ignore_sigpipe(void)` -- A write to a dead child must not kill the parent with SIGPIPE.
- `tab_refresh_alive` (function) `src/tab.c:2572` `static void tab_refresh_alive(tab *t)`
- `read_field` (function) `src/tab.c:2591` `static int read_field(int fd, char **out, size_t *out_len)` -- Read one length-prefixed owned field from the child, capped against * amplification. *out is NUL-terminated.
- `read_view` (function) `src/tab.c:2608` `static int read_view(int fd, pv_view **out)`
- `read_view_raw` (function) `src/tab.c:2616` `static int read_view_raw(int fd, pv_view **out)`
- `tests` (function) `src/tab.c:2691` `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...`
- `layout` (function) `src/tab.c:2798` `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....`
- `column` (function) `src/tab.c:2809` `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...`
- `read_console` (function) `src/tab.c:3144` `static int read_console(int fd, fb_buffer *out)` -- Reads the console section written by write_console into out (a zero-initialised fb_buffer).
- `send_request` (function) `src/tab.c:3181` `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` -- if (elen != 0) { txt = (char *)malloc(elen); if (txt == NULL) { free(file); return -1; } if (read_full(fd, txt...
- `io_failure` (function) `src/tab.c:3191` `static tab_status io_failure(tab *t)`
- `exec_worker_child` (function) `src/tab.c:3199` `static void exec_worker_child(int rfd, int wfd)` -- Child half of the fork: re-exec a fresh worker image so it inherits NONE of the parent's address space (no other...
- `spawn_worker` (function) `src/tab.c:3231` `static tab_status spawn_worker(tab_spawned *sp)` -- Forks and execs one confined worker WITHOUT waiting for its handshake.
- `reap_spawned` (function) `src/tab.c:3261` `static void reap_spawned(const tab_spawned *sp, int kill_it)`
- `adopt_worker` (function) `src/tab.c:3270` `static tab_status adopt_worker(const tab_spawned *sp, tab **out)` -- sp->resp_r = resp[0]; sp->pid = pid; return TAB_OK; } static void reap_spawned(const tab_spawned *sp, int kill_it) {...
- `tab_prewarm` (function) `src/tab.c:3292` `void tab_prewarm(void)`
- `tab_prewarmed` (function) `src/tab.c:3298` `int tab_prewarmed(void)`
- `tab_prewarmed_pid` (function) `src/tab.c:3305` `int tab_prewarmed_pid(void)`
- `tab_shutdown_spare` (function) `src/tab.c:3312` `void tab_shutdown_spare(void)`
- `tab_open` (function) `src/tab.c:3321` `tab_status tab_open(tab **out)`
- `tab_set_fetcher` (function) `src/tab.c:3344` `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)`
- `tab_set_css_sink` (function) `src/tab.c:3350` `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)`
- `tab_set_op_net_budget_ms` (function) `src/tab.c:3356` `void tab_set_op_net_budget_ms(tab *t, int ms)`
- `tab_set_net_allowed` (function) `src/tab.c:3360` `void tab_set_net_allowed(tab *t, int allowed)`
- `tab_set_css_allowed` (function) `src/tab.c:3365` `void tab_set_css_allowed(tab *t, int allowed)`
- `tab_last_subreq_stats` (function) `src/tab.c:3370` `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)`
- `tab_set_identity` (function) `src/tab.c:3375` `void tab_set_identity(tab *t, const char *serialized)`
- `tab_set_frame_id` (function) `src/tab.c:3383` `void tab_set_frame_id(tab *t, int id)`
- `tab_set_viewport_w` (function) `src/tab.c:3388` `void tab_set_viewport_w(tab *t, int px)`
- `tab_set_cookies` (function) `src/tab.c:3393` `void tab_set_cookies(tab *t, const char *cookies)`
- `tab_subreq_permitted` (function) `src/tab.c:3399` `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)`
- `tab_report_response_headers` (function) `src/tab.c:3413` `void tab_report_response_headers(const char *lines)`
- `tab_inflight_request_headers` (function) `src/tab.c:3425` `const char *tab_inflight_request_headers(void)`
- `tab_write_reply` (function) `src/tab.c:3431` `static int tab_write_reply(tab *t, int ok, int status, const char *rbody, size_t rlen,
          ...` -- Writes one reply [status:int32][body_len][body][ctype_len][ctype][hdr_len][hdrs][ms:int32] on req_fd * (the worker...
- `tab_read_subreq_fields` (function) `src/tab.c:3476` `static int tab_read_subreq_fields(tab *t, char **method, char **url, char **body, size_t *blen,
 ...` -- g_inflight_headers = hdrs; free(g_inflight_resp); g_inflight_resp = NULL; g_inflight_active = 1; int ok =...
- `tab_op_budget_us` (function) `src/tab.c:3487` `static int64_t tab_op_budget_us(const tab *t)`
- `tab_note_css_served` (function) `src/tab.c:3491` `static void tab_note_css_served(tab *t, int ok, int status, const char *url, const char *rbody,
 ...`
- `tab_serve_subreq` (function) `src/tab.c:3507` `static int tab_serve_subreq(tab *t, int net_granted, int css_granted)` -- Handles one TAG_SUBREQ frame on the response pipe: reads the worker's subresource request, gates it on the grants...
- `tab_batch_run` (function) `src/tab.c:3534` `static int tab_batch_run(void *vt, const sqb_req *rq, sqb_res *out)` -- The fetch of one deferred request, on a batch thread.
- `tab_submit_async` (function) `src/tab.c:3549` `static int tab_submit_async(tab *t, int net_granted, int css_granted)` -- TAG_SUBREQ_ASYNC: reads and gates the frame like tab_serve_subreq, then starts the fetch on a batch thread and goes...
- `tab_serve_netwait` (function) `src/tab.c:3571` `static int tab_serve_netwait(tab *t)` -- TAG_NETWAIT: joins the batch and writes one reply per deferred request, in issue order.
- `tab_serve_tag` (function) `src/tab.c:3593` `static int tab_serve_tag(tab *t, uint8_t tag, int net_granted, int css_granted)` -- Serves the frame kinds the worker may send while it runs: 1 = served, 0 = not a subrequest * tag, -1 = pipe/protocol...
- `tab_batch_discard` (function) `src/tab.c:3601` `static void tab_batch_discard(tab *t)` -- Serves the frame kinds the worker may send while it runs: 1 = served, 0 = not a subrequest * tag, -1 = pipe/protocol...
- `hist_ops_free` (function) `src/tab.c:3606` `static void hist_ops_free(tab_hist_op *ops, size_t n)`
- `is_activation_event` (function) `src/tab.c:3671` `static int is_activation_event(const char *type)` -- HTML 6.4.2 activation-triggering input events: only these let a page open a * window.
- `open_urls_free` (function) `src/tab.c:3680` `static void open_urls_free(char **u, size_t n)`
- `read_opens` (function) `src/tab.c:3690` `static tab_status read_opens(tab *t, const char *page_url, int gesture,
                         ...` -- Reads the window.open block (see write_opens).
- `ws_ops_free` (function) `src/tab.c:3719` `static void ws_ops_free(tab_ws_op *ops, size_t n)`
- `read_ws` (function) `src/tab.c:3728` `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` -- Reads the WebSocket block (see write_ws), bounded by JT_WS_MAX_OPS ops and JT_WS_MAX_BYTES of payload.
- `gate_js_nav` (function) `src/tab.c:3797` `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` -- Gates a raw JS navigation request against the page URL in the trusted parent (Zero Trust: a compromised worker...
- `tab_load` (function) `src/tab.c:3807` `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)`
- `tab_load_ex` (function) `src/tab.c:3811` `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)`
- `tab_load_full` (function) `src/tab.c:3815` `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...`
- `tab_click` (function) `src/tab.c:4016` `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)`
- `tab_tick` (function) `src/tab.c:4024` `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)`
- `tab_submit` (function) `src/tab.c:4034` `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` -- Dispatches a submit event on the form enclosing node_id.
- `tab_read_view` (function) `src/tab.c:4142` `tab_status tab_read_view(tab *t, tab_page *out)` -- Reads the TAG_RESULT + TAG_VIEW response into *out (titles + view + console). * Used by tab_mutation_request...
- `frames` (function) `src/tab.c:4148` `* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of...`
- `tab_await_result` (function) `src/tab.c:4151` `static tab_status tab_await_result(tab *t)`
- `tab_await_result_inner` (function) `src/tab.c:4159` `static tab_status tab_await_result_inner(tab *t)`
- `tab_read_view_ex` (function) `src/tab.c:4168` `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)`
- `tab_eval` (function) `src/tab.c:4263` `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)`
- `tab_decode_image_op` (function) `src/tab.c:4304` `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...` -- Shared by tab_decode_image and tab_decode_image_data_url: sends `bytes` under opcode `op` and parses the...
- `tab_decode_image` (function) `src/tab.c:4346` `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)`
- `tab_decode_image_data_url` (function) `src/tab.c:4353` `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)`
- `tab_alive` (function) `src/tab.c:4372` `int tab_alive(const tab *t)`
- `tab_child_pid` (function) `src/tab.c:4378` `pid_t tab_child_pid(const tab *t)`
- `tab_close` (function) `src/tab.c:4382` `void tab_close(tab *t)`
- `tab_page_free` (function) `src/tab.c:4400` `void tab_page_free(tab_page *p)`
- `tab_eval_result_free` (function) `src/tab.c:4430` `void tab_eval_result_free(tab_eval_result *r)`
- `tab_image_free` (function) `src/tab.c:4439` `void tab_image_free(tab_image *img)`
- `tab_geometry_send` (function) `src/tab.c:4451` `static tab_status tab_geometry_send(tab *t, const int32_t *buf, size_t words)` -- Writes one encoded geometry table and waits for its acknowledgement (serving any network the * observer callbacks it...
- `geometry_encode` (function) `src/tab.c:4469` `static int32_t *geometry_encode(const jg_table *g, size_t *words_out)`
- `tab_set_geometry` (function) `src/tab.c:4479` `tab_status tab_set_geometry(tab *t, const jg_table *g)`
- `job_discard` (function) `src/tab.c:4493` `static void job_discard(tab *t)`
- `tab_async_sync` (function) `src/tab.c:4505` `static void tab_async_sync(tab *t)` -- Waits for a running job and DISCARDS its result: any other worker call is about to change * the page, so the...
- `job_main` (function) `src/tab.c:4515` `static void *job_main(void *arg)`
- `tab_async_fd` (function) `src/tab.c:4531` `int tab_async_fd(tab *t)`
- `tab_async_busy` (function) `src/tab.c:4540` `int tab_async_busy(const tab *t)`
- `job_start` (function) `src/tab.c:4544` `static tab_status job_start(tab *t)`
- `tab_tick_async` (function) `src/tab.c:4557` `tab_status tab_tick_async(tab *t, int elapsed_ms)`
- `tab_geometry_async` (function) `src/tab.c:4567` `tab_status tab_geometry_async(tab *t, const jg_table *g)`
- `tab_async_finish` (function) `src/tab.c:4582` `tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)`
- `tab_popstate` (function) `src/tab.c:4604` `tab_status tab_popstate(tab *t, int index, tab_page *out)`
- `tab_ws_event` (function) `src/tab.c:4611` `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,
       ...`
- `tab_set_storage` (function) `src/tab.c:4631` `void tab_set_storage(tab *t, const char *blob, size_t len)`

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
- `generic_name` (function) `src/text_shape.c:56` `static const char *generic_name(int family)`
- `backend_init` (function) `src/text_shape.c:66` `static int backend_init(void)`
- `read_font_file` (function) `src/text_shape.c:83` `static unsigned char *read_font_file(const char *path, long *out_n)`
- `characters` (function) `src/text_shape.c:101` `* hold characters ('-', ':') that the pattern syntax treats specially. */ static int load_entry_file(tsh_entry *e...`
- `load_entry_named` (function) `src/text_shape.c:104` `static int load_entry_named(tsh_entry *e, const char *fam, int bold, int italic)`
- `load_entry_file` (function) `src/text_shape.c:134` `static int load_entry_file(tsh_entry *e, const char *path, int index)` -- Loads face `index` of the font file at `path` into e (FreeType + cairo + * HarfBuzz over one owned copy of the bytes).
- `load_entry` (function) `src/text_shape.c:170` `static int load_entry(tsh_entry *e, int family, int bold, int italic)`
- `get_entry` (function) `src/text_shape.c:174` `static tsh_entry *get_entry(int family, int bold, int italic)`
- `web_entry_free` (function) `src/text_shape.c:202` `static void web_entry_free(tsh_web *w)`
- `slice` (function) `src/text_shape.c:214` `* woff2 slice (spec/webfont.md);`
- `web_magic_ok` (function) `src/text_shape.c:215` `static int web_magic_ok(const unsigned char *b, size_t n)` -- True for font programs FreeType parses without new decoders: wOFF/TrueType/ CFF-OpenType (and the mac aliases). wOF2...
- `web_make_entry` (function) `src/text_shape.c:228` `static int web_make_entry(tsh_entry *e, const unsigned char *bytes, size_t nbytes)` -- Builds the shaping faces over an OWNED copy of bytes[0,nbytes) into e (shared tail with load_entry's file path: same...
- `tsh_webfont_register` (function) `src/text_shape.c:271` `int tsh_webfont_register(const char *name,
                         const unsigned char *bytes, s...`
- `tsh_webfont_clear` (function) `src/text_shape.c:306` `void tsh_webfont_clear(void)`
- `web_find` (function) `src/text_shape.c:312` `static tsh_entry *web_find(unsigned h, int bold, int italic)`
- `entry_free` (function) `src/text_shape.c:324` `static void entry_free(tsh_entry *e)`
- `ascii_ieq` (function) `src/text_shape.c:337` `static int ascii_ieq(const char *a, const char *b)`
- `tsh_family_is_generic` (function) `src/text_shape.c:346` `int tsh_family_is_generic(const char *name)`
- `tsh_pick_from_list` (function) `src/text_shape.c:358` `int tsh_pick_from_list(const char *list, tsh_name_resolver resolve, void *ctx,
                  ...`
- `tsh_pick_family` (function) `src/text_shape.c:379` `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong,
        ...`
- `fc_installed` (function) `src/text_shape.c:392` `static int fc_installed(const char *name, void *ctx)` -- const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong, size_t n, int...
- `fc_resolve` (function) `src/text_shape.c:435` `static int fc_resolve(const char *name, char *out, size_t cap, void *ctx)`
- `local_clear` (function) `src/text_shape.c:480` `static void local_clear(void)`
- `lfam_index` (function) `src/text_shape.c:491` `static int lfam_index(const char *fam)`
- `tsh_local_handle` (function) `src/text_shape.c:499` `int tsh_local_handle(const char *list)`
- `local_entry` (function) `src/text_shape.c:518` `static tsh_entry *local_entry(int handle, int bold, int italic)`
- `get_entry_ex` (function) `src/text_shape.c:538` `static tsh_entry *get_entry_ex(const tsh_font *f)` -- Entry for a full font selector: a registered @font-face wins over the local bucket stack; a set-but-unregistered...
- `tsh_ready` (function) `src/text_shape.c:550` `int tsh_ready(void)`
- `tsh_shape` (function) `src/text_shape.c:555` `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                ...`
- `utf8_next` (function) `src/text_shape.c:604` `static unsigned utf8_next(const char *s, size_t n, size_t *len)` -- Decodes one UTF-8 sequence at s[0..n): the code point (U+FFFD for a malformed * sequence) and its byte length (>= 1...
- `is_private_use` (function) `src/text_shape.c:623` `static int is_private_use(unsigned cp)` -- if (l > n) l = 1; if (l == 1) { *len = 1; return (c < 0x80) ? c : 0xFFFDu; } unsigned cp = c & (0x7fu >> l); for...
- `rides_previous` (function) `src/text_shape.c:628` `static int rides_previous(unsigned cp)` -- cp = (cp << 6) | (u[k] & 0x3fu); } len = l; return cp; } #define TSH_BLANK_GLYPH ((unsigned long)-1) /* Private Use...
- `tsh_segment` (function) `src/text_shape.c:636` `int tsh_segment(const char *text, size_t len, tsh_cover_fn cover, void *ctx,
                tsh_...`
- `fb_clear` (function) `src/text_shape.c:689` `static void fb_clear(void)`
- `fb_match_covering` (function) `src/text_shape.c:709` `static FcPattern *fb_match_covering(FcPattern *pat, FcCharSet *cs)` -- Best fontconfig match for `pat` among the installed fonts that contain every code point of `cs`.
- `fb_entry` (function) `src/text_shape.c:731` `static tsh_entry *fb_entry(unsigned cp, int bold)`
- `fb_entry_uncached` (function) `src/text_shape.c:748` `static tsh_entry *fb_entry_uncached(unsigned cp, int bold)`
- `cover_cp` (function) `src/text_shape.c:818` `static int cover_cp(unsigned cp, void *vctx)` -- cover callback: 0 when the requested face has the glyph (or nothing else * does), else the id of the fallback face...
- `shape_entry` (function) `src/text_shape.c:832` `static tsh_status shape_entry(tsh_entry *e, double px, const char *text, size_t len,
            ...` -- static int cover_cp(unsigned cp, void *vctx) { tsh_cover_ctx *c = (tsh_cover_ctx *)vctx; hb_codepoint_t g; if (cp ==...
- `shape_runs` (function) `src/text_shape.c:868` `static tsh_status shape_runs(cairo_t *cr, const tsh_font *f, double px, double x,
               ...` -- Measures (cr == NULL) or draws [text,len) run by run, each with the face that * has its glyphs.
- `tsh_measure` (function) `src/text_shape.c:929` `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)`
- `tsh_draw` (function) `src/text_shape.c:964` `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, doub...`
- `tsh_face` (function) `src/text_shape.c:971` `cairo_font_face_t *tsh_face(const tsh_font *f)`
- `tsh_shutdown` (function) `src/text_shape.c:977` `void tsh_shutdown(void)`

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


Next: [API_p12.md](API_p12.md)
