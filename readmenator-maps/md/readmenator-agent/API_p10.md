# API (page 10 of 11)
Previous: [API_p9.md](API_p9.md)

## src/profile.c
Depends on: `include/disk_store.h`, `include/profile.h`
- `join_path` (function) `src/profile.c:29` `static int join_path(const profile_ctx *ctx, const char *name,
                     char *out, si...`
- `keyfile_create` (function) `src/profile.c:36` `static profile_status keyfile_create(const char *dir, const char *path,
                         ...` -- #include <unistd.h> #include <openssl/crypto.h> #include <openssl/rand.h> #define PROFILE_KEYFILE_LEN (LS_SALT_LEN +...
- `profile_open` (function) `src/profile.c:59` `profile_status profile_open(profile_ctx *ctx, const char *dir)`
- `map_ds` (function) `src/profile.c:98` `static profile_status map_ds(ds_status ds)`
- `profile_load` (function) `src/profile.c:112` `profile_status profile_load(const profile_ctx *ctx, prefs_state *out)`
- `profile_save` (function) `src/profile.c:133` `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p)`
- `profile_close` (function) `src/profile.c:149` `void profile_close(profile_ctx *ctx)`

## src/render_doc.c
Depends on: `include/box_style.h`, `include/css.h`, `include/data_url.h`, `include/render_doc.h`, `include/url.h`, `include/util.h`
- `utf8_sanitized_dup` (function) `src/render_doc.c:28` `static char *utf8_sanitized_dup(const char *s)`
- `rd_push` (function) `src/render_doc.c:60` `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,
                 ...` -- Appends one block, taking owned copies of text (required) and href (optional). * Returns 0 on success, -1 on...
- `rd_push_input` (function) `src/render_doc.c:211` `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` -- Appends an RD_INPUT block, copying text (placeholder/label), the form action * (href), and the control name/value.
- `place` (function) `src/render_doc.c:237` `* judges it under the exact same policy an <img> already goes through: a data: * URI is judged in place (never...`
- `resolve_image_decision` (function) `src/render_doc.c:247` `static rdp_img_decision resolve_image_decision(rdp_caps caps, const char *top_level_url,
        ...` -- Resolves raw_src (possibly relative, or a data: URI) against top_level_url and judges it under the exact same policy...
- `rd_build` (function) `src/render_doc.c:269` `rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_u...`
- `unset` (function) `src/render_doc.c:677` `* background paints as if unset (no border/box-shadow-style
                 * "broken image" pla...`
- `rd_free` (function) `src/render_doc.c:742` `void rd_free(rd_doc *d)`
- `rd_count` (function) `src/render_doc.c:759` `size_t rd_count(const rd_doc *d)`
- `rd_at` (function) `src/render_doc.c:763` `const rd_block *rd_at(const rd_doc *d, size_t i)`
- `rd_box_count` (function) `src/render_doc.c:768` `size_t rd_box_count(const rd_doc *d)`
- `rd_box_at` (function) `src/render_doc.c:772` `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)`
- `rd_cont_count` (function) `src/render_doc.c:777` `size_t rd_cont_count(const rd_doc *d)`
- `rd_cont_at` (function) `src/render_doc.c:781` `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i)`
- `rd_kind_name` (function) `src/render_doc.c:786` `const char *rd_kind_name(rd_kind k)`
- `rd_block_heading_level` (function) `src/render_doc.c:800` `int rd_block_heading_level(const rd_block *b)`
- `rd_block_tag` (function) `src/render_doc.c:811` `const char *rd_block_tag(const rd_block *b)`
- `rd_input_label` (function) `src/render_doc.c:842` `const char *rd_input_label(int input_type)`
- `rd_input_invisible` (function) `src/render_doc.c:862` `int rd_input_invisible(int input_type)`
- `rd_image_label` (function) `src/render_doc.c:866` `const char *rd_image_label(rdp_img_decision d)`
- `rd_image_fail_label` (function) `src/render_doc.c:877` `const char *rd_image_fail_label(img_fail_reason reason)`

## src/render_policy.c
Depends on: `include/data_url.h`, `include/render_policy.h`, `include/request_policy.h`
- `rdp_caps_safe` (function) `src/render_policy.c:17` `rdp_caps rdp_caps_safe(void)`
- `rdp_is_tracking_pixel` (function) `src/render_policy.c:22` `int rdp_is_tracking_pixel(int w, int h)`
- `rdp_image_decision` (function) `src/render_policy.c:28` `rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char...`
- `rdp_img_reason` (function) `src/render_policy.c:63` `const char *rdp_img_reason(rdp_img_decision d)`
- `rdp_images_warning` (function) `src/render_policy.c:74` `const char *rdp_images_warning(void)`

## src/renderer.c
Depends on: `include/html_parse.h`, `include/os_sandbox.h`, `include/renderer.h`, `include/util.h`
- `child_render` (function) `src/renderer.c:25` `static void child_render(int wfd, const char *html, size_t len)`
- `write_full` (function) `src/renderer.c:40` `&& write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 || write_full(wfd, title, tl) == 0) && write_full(wfd, &xl...`
- `read_field` (function) `src/renderer.c:53` `static int read_field(int fd, char **out, size_t *out_len)`
- `rd_render_html` (function) `src/renderer.c:70` `rd_status rd_render_html(const char *html, size_t len, rd_result *out)`
- `rd_result_free` (function) `src/renderer.c:120` `void rd_result_free(rd_result *out)`

## src/request_policy.c
Depends on: `include/psl_data.h`, `include/request_policy.h`
- `lower` (function) `src/request_policy.c:22` `static char lower(char c)`
- `ci_starts_with` (function) `src/request_policy.c:26` `static int ci_starts_with(const char *s, const char *prefix)`
- `psl_cmp` (function) `src/request_policy.c:36` `static int psl_cmp(const void *key, const void *elem)`
- `psl_in` (function) `src/request_policy.c:40` `static int psl_in(const char *const *arr, size_t n, const char *key)`
- `public_suffix_labels` (function) `src/request_policy.c:48` `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)` -- Number of labels of the public suffix (eTLD) of a lowercased host, applying the full PSL algorithm: exception rules...
- `rp_host_of` (function) `src/request_policy.c:76` `int rp_host_of(const char *url, char *out, size_t out_size)`
- `rp_site_of` (function) `src/request_policy.c:102` `int rp_site_of(const char *host, char *out, size_t out_size)`
- `rp_same_site` (function) `src/request_policy.c:134` `int rp_same_site(const char *top_level_url, const char *request_url)`
- `rp_evaluate` (function) `src/request_policy.c:143` `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)`

## src/secure_fetch.c
Depends on: `include/anti_fp.h`, `include/secure_fetch.h`, `include/url.h`
- `ci_starts_with` (function) `src/secure_fetch.c:45` `static int ci_starts_with(const char *haystack, const char *prefix)` -- /* --- small helpers (no libc locale dependence) --- static int ci_equal(const char *a, const char *b) { while (*a...
- `ci_index` (function) `src/secure_fetch.c:57` `static long ci_index(const char *haystack, const char *needle)` -- /* Case-insensitive: does haystack start with prefix? static int ci_starts_with(const char *haystack, const char...
- `sf_share_lock` (function) `src/secure_fetch.c:69` `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...`
- `sf_share_unlock` (function) `src/secure_fetch.c:75` `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)`
- `sf_global_init` (function) `src/secure_fetch.c:82` `void sf_global_init(void)`
- `sf_cookie_line_matches` (function) `src/secure_fetch.c:97` `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...`
- `sf_url_host_path` (function) `src/secure_fetch.c:152` `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...` -- Extracts host + path from a validated https url into caller buffers (path defaults * to "/").
- `sf_cookie_header_for` (function) `src/secure_fetch.c:167` `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)`
- `sf_cookie_put` (function) `src/secure_fetch.c:196` `void sf_cookie_put(const char *url, const char *namevalue)`
- `sf_config_default` (function) `src/secure_fetch.c:217` `sf_config sf_config_default(void)`
- `header_value_clean` (function) `src/secure_fetch.c:243` `static int header_value_clean(const char *s)` -- c.password = NULL; c.insecure = 0; c.impersonate = 0; /* default hardened PQ-hybrid ClientHello; opt-in per trusted...
- `sf_user_agent_or_default` (function) `src/secure_fetch.c:249` `const char *sf_user_agent_or_default(const char *ua)`
- `sf_accept_language_or_default` (function) `src/secure_fetch.c:253` `const char *sf_accept_language_or_default(const char *lang)`
- `sf_impersonate_kex_groups` (function) `src/secure_fetch.c:257` `const char *sf_impersonate_kex_groups(void)`
- `sf_impersonate_tls13_ciphers` (function) `src/secure_fetch.c:258` `const char *sf_impersonate_tls13_ciphers(void)`
- `sf_validate_url` (function) `src/secure_fetch.c:262` `sf_status sf_validate_url(const char *url)`
- `sf_url_is_http` (function) `src/secure_fetch.c:270` `static int sf_url_is_http(const char *url)` -- Nonzero iff url is "http://host..." (case-insensitive) with a non-empty host.
- `sf_check_tls_version` (function) `src/secure_fetch.c:282` `sf_status sf_check_tls_version(const char *negotiated_version)`
- `sf_check_group_is_pq` (function) `src/secure_fetch.c:287` `sf_status sf_check_group_is_pq(const char *negotiated_group)`
- `sf_check_chain_policy` (function) `src/secure_fetch.c:296` `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)`
- `sf_enforce_policy` (function) `src/secure_fetch.c:306` `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...`
- `copy_checked` (function) `src/secure_fetch.c:337` `static int copy_checked(char *dst, size_t dstsz, const char *src)`
- `sf_is_redirect_code` (function) `src/secure_fetch.c:346` `int sf_is_redirect_code(long http_code)`
- `sf_header_value` (function) `src/secure_fetch.c:353` `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz)`
- `sf_parse_location_header` (function) `src/secure_fetch.c:375` `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)`
- `sf_resolve_redirect` (function) `src/secure_fetch.c:393` `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...`
- `module` (function) `src/secure_fetch.c:398` `* pure url module (DRY);`
- `sf_ci_prefix` (function) `src/secure_fetch.c:405` `static int sf_ci_prefix(const char *s, const char *p)` -- Reference resolution + the https-only / no-downgrade policy live in the pure url module (DRY); a redirect is just a...
- `sf_response_free` (function) `src/secure_fetch.c:445` `void sf_response_free(sf_response *resp)`
- `progress` (function) `src/secure_fetch.c:482` `* transfer is in progress (via CURLINFO_TLS_SSL_PTR);`
- `copy_bounded` (function) `src/secure_fetch.c:511` `static void copy_bounded(char *dst, size_t dstsz, const char *src)`
- `get_negotiated_group_name` (function) `src/secure_fetch.c:522` `static const char *get_negotiated_group_name(SSL *ssl)` -- static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len); static void...
- `database` (function) `src/secure_fetch.c:526` `* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid...`
- `group` (function) `src/secure_fetch.c:540` `* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);`
- `tls_capture_try` (function) `src/secure_fetch.c:555` `static void tls_capture_try(tls_capture *cap)` -- nid = SSL_get_shared_group(ssl, 0); #endif if (nid == 0) { return NULL; /* There is no negotiated group (e.g., TLS...
- `tls_capture_from_ssl` (function) `src/secure_fetch.c:565` `static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl)` -- static void tls_capture_from_ssl(tls_capture *cap, SSL *ssl); /* Idempotent: takes the TLS snapshot the first time...
- `this` (function) `src/secure_fetch.c:572` `* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and...`
- `header_cb` (function) `src/secure_fetch.c:591` `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` -- Fires for every HTTP response (status line + headers) even when there is no * body, so it is the reliable point to...
- `write_cb` (function) `src/secure_fetch.c:634` `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)`
- `name_is_pq_sig` (function) `src/secure_fetch.c:666` `static int name_is_pq_sig(int pknid)` -- if (grown == NULL) { sink->overflow = 2; /* OOM marker return 0; } sink->data = grown; sink->cap = newcap; }...
- `inspect_chain` (function) `src/secure_fetch.c:676` `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` -- Walks the verified chain into *info. sigbuf receives the leaf signature alg name. * Returns 0 on success, nonzero if...
- `map_curl_error` (function) `src/secure_fetch.c:729` `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)`
- `add_header` (function) `src/secure_fetch.c:770` `static int add_header(struct curl_slist **h, const char *line)` -- Appends one header line without losing the list on OOM (the plain "h = curl_slist_append(h, ...)" idiom dropped the...
- `sf_setup_handle` (function) `src/secure_fetch.c:784` `static sf_status sf_setup_handle(CURL *curl, const char *url, const sf_config *local,
           ...` -- The ONE place a curl handle is configured for a request (spec/secure_fetch.md): URL, realm proxy, TLS floor + KE...
- `redirect` (function) `src/secure_fetch.c:859` `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...`
- `sf_perform` (function) `src/secure_fetch.c:933` `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...` -- The shared request engine for sf_get and sf_post.
- `sf_get` (function) `src/secure_fetch.c:1085` `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)`
- `sf_post` (function) `src/secure_fetch.c:1089` `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...`
- `sf_rcache_clear` (function) `src/secure_fetch.c:1119` `void sf_rcache_clear(void)`
- `sf_rcache_set_backing` (function) `src/secure_fetch.c:1130` `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx)`
- `rcache_put_ram` (function) `src/secure_fetch.c:1138` `static int rcache_put_ram(const char *from, const char *to, time_t now)`
- `sf_rcache_put` (function) `src/secure_fetch.c:1157` `int sf_rcache_put(const char *from, const char *to, time_t now)`
- `sf_rcache_get` (function) `src/secure_fetch.c:1167` `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap)`
- `sf_get_follow` (function) `src/secure_fetch.c:1196` `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...`
- `ws_ssl_info_cb` (function) `src/secure_fetch.c:1259` `static void ws_ssl_info_cb(const SSL *ssl, int where, int ret)` -- An upgraded (CONNECT_ONLY) connection never runs the header callback that snapshots TLS for a fetch, and curl no...
- `ws_ssl_ctx_cb` (function) `src/secure_fetch.c:1266` `static CURLcode ws_ssl_ctx_cb(CURL *curl, void *sslctx, void *userdata)`
- `sf_ws_url_check` (function) `src/secure_fetch.c:1280` `sf_status sf_ws_url_check(const char *url)`
- `ws_free` (function) `src/secure_fetch.c:1292` `static void ws_free(sf_ws *ws)`
- `sf_ws_open` (function) `src/secure_fetch.c:1301` `sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)`
- `sf_ws_send` (function) `src/secure_fetch.c:1356` `sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)`
- `sf_ws_recv` (function) `src/secure_fetch.c:1379` `sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)`
- `sf_ws_fd` (function) `src/secure_fetch.c:1401` `int sf_ws_fd(const sf_ws *ws)`
- `sf_ws_close` (function) `src/secure_fetch.c:1408` `void sf_ws_close(sf_ws *ws)`
- `sf_fallback_policy` (function) `src/secure_fetch.c:1419` `int sf_fallback_policy(sf_status failed, sf_policy tried, int allowlisted, sf_policy *next)`
- `sf_downgrade_of` (function) `src/secure_fetch.c:1433` `static int sf_downgrade_of(sf_policy p)`
- `sf_attempt_get` (function) `src/secure_fetch.c:1442` `static sf_status sf_attempt_get(const char *url, const sf_config *cfg, sf_response *out,
        ...`
- `sf_attempt_post` (function) `src/secure_fetch.c:1448` `static sf_status sf_attempt_post(const char *url, const sf_config *cfg, sf_response *out,
       ...`
- `sf_navigable` (function) `src/secure_fetch.c:1453` `static sf_status sf_navigable(sf_attempt_fn attempt, const char *url, sf_config *cfg,
           ...`
- `sf_get_follow_navigable` (function) `src/secure_fetch.c:1473` `sf_status sf_get_follow_navigable(const char *url, sf_config *cfg, sf_response *out,
            ...`
- `sf_post_navigable` (function) `src/secure_fetch.c:1478` `sf_status sf_post_navigable(const char *url, sf_config *cfg, const void *body,
                  ...`

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
Depends on: `include/anti_fp.h`, `include/box_tree.h`, `include/css.h`, `include/css_computed.h`, `include/css_gradient.h`, `include/data_url.h`, `include/dom.h`, `include/flex_layout.h`, `include/freebug.h`, `include/freedom_config.h`, `include/html_parse.h`, `include/identity.h`, `include/image_decode.h`, `include/import_map.h`, `include/js_dom.h`, `include/js_env.h`, `include/js_sandbox.h`, `include/js_trusted.h`, `include/link_nav.h`, `include/os_sandbox.h`, `include/page_view.h`, `include/request_policy.h`, `include/tab.h`, `include/url.h`, `include/util.h`, `include/web_storage.h`
- `clip_pm_ok` (function) `src/tab.c:76` `static int clip_pm_ok(int32_t v)` -- A clip-edge percentage off the wire: per-mille, bounded like CSS_PCT_MAX (a hostile * worker cannot hand the painter...
- `rad_len_ok` (function) `src/tab.c:82` `static int rad_len_ok(int32_t v, int dflt)` -- A radial-gradient length off the wire (cg_radial encoding): per-mille 0..1e6, or * -(px)-1 with px <= 100000, or...
- `child_reset_page` (function) `src/tab.c:181` `static void child_reset_page(child_state *cs)`
- `sig_mix` (function) `src/tab.c:201` `static uint64_t sig_mix(uint64_t h, const char *s, size_t n)`
- `computed_signature` (function) `src/tab.c:209` `static uint64_t computed_signature(const dom_index *idx)` -- What the retained cascade depends on: every <style> text plus the attributes of <html>/<body> (class/data-* theme...
- `policy` (function) `src/tab.c:289` `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a
 * compromi...`
- `run_js` (function) `src/tab.c:343` `* regardless of run_js (a no-JS load simply never records a request). */
static int child_load(ch...`
- `buffer` (function) `src/tab.c:388` `* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of...`
- `host` (function) `src/tab.c:400` `* granted net access for this host (allow.conf AND js.conf). Otherwise they stay * undefined...`
- `write_field` (function) `src/tab.c:417` `static int write_field(int fd, const char *s)` -- Writes one length-prefixed string field (the write mirror of read_field): a size_t * length then the bytes, with...
- `blocks` (function) `src/tab.c:451` `*
 * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the
 * grid arr...`
- `FB_MAX_FILE_BYTES` (function) `src/tab.c:882` `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...`
- `budget_remaining_ms` (function) `src/tab.c:912` `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` -- Milliseconds of `budget_ms` still left since `start` (CLOCK_MONOTONIC), 0 if spent. * Used to share one page-wide JS...
- `ctype_is_javascript` (function) `src/tab.c:926` `static int ctype_is_javascript(const char *ctype)` -- Content-Type gate for an external script's response (anti type-confusion, fail closed for real content types)...
- `ctype_is_css` (function) `src/tab.c:935` `static int ctype_is_css(const char *ctype)` -- Content-Type gate for an external stylesheet (Hito 27), same shape as the script gate: a missing/empty type is...
- `log_external_skip` (function) `src/tab.c:943` `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...` -- Freebug note about an external subresource (script/stylesheet) that was not used (skipped or refused).
- `run` (function) `src/tab.c:961` `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...`
- `tab_url_resolve` (function) `src/tab.c:1010` `static int tab_url_resolve(void *ctx, const char *base, const char *ref,
                        ...` -- Plain URL resolution of ref against base (https, or a local file confined to its * document's directory): the...
- `tab_mod_resolve` (function) `src/tab.c:1019` `static int tab_mod_resolve(void *host, const char *base, const char *spec,
                      ...`
- `tab_mod_fetch` (function) `src/tab.c:1045` `static char *tab_mod_fetch(void *host, const char *url, size_t *len)` -- Loads a module's source through the trusted parent (TAG_SUBREQ: the full network policy applies), only inside a...
- `write_history` (function) `src/tab.c:1067` `static int write_history(int wfd, child_state *cs)` -- Writes the history block of a response: [len][ops "K url\n"...][go:int32] * (spec/js_dom.md 7e).
- `window` (function) `src/tab.c:1086` `* net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs)`
- `child_handle_load` (function) `src/tab.c:1131` `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...`
- `fallback` (function) `src/tab.c:1207` `* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it...`
- `WHERE` (function) `src/tab.c:1385` `* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value...`
- `content` (function) `src/tab.c:1430` `* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video>...`
- `once` (function) `src/tab.c:1475` `* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);`
- `swap` (function) `src/tab.c:1484` `* display:none hiding an element via class swap (CSS, not
     * DOM removal). */
    if (ok && v...`
- `write_full` (function) `src/tab.c:1504` `&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0) && write_view(wfd...`
- `write_ws` (function) `src/tab.c:1526` `static int write_ws(int wfd, child_state *cs)` -- Writes the WebSocket block of a response: [n:int32] then per op * [kind:int32][id:int32][len][bytes] (spec/js_dom.md...
- `write_storage` (function) `src/tab.c:1543` `static int write_storage(int wfd, child_state *cs)` -- int32_t cnt = (int32_t)n; int rc = (write_full(wfd, &cnt, sizeof cnt) == 0) ?
- `write_opens` (function) `src/tab.c:1557` `static int write_opens(int wfd, child_state *cs)` -- static int write_storage(int wfd, child_state *cs) { char *blob = NULL; size_t len = 0; int32_t dirty = (cs->js !=...
- `child_next_timer_ms` (function) `src/tab.c:1569` `static int32_t child_next_timer_ms(child_state *cs)` -- Smallest pending JS timer delay (__nextTimerMs), or -1 when JS is absent, the * eval fails, or nothing is pending.
- `child_handle_mutation` (function) `src/tab.c:1584` `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...` -- Fire click handlers for node_id (OP_CLICK) or advance the virtual timer clock (OP_TICK), then re-derive the view so...
- `child_handle_click` (function) `src/tab.c:1663` `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)`
- `child_handle_tick` (function) `src/tab.c:1667` `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)`
- `child_handle_event` (function) `src/tab.c:1677` `static void child_handle_event(int wfd, child_state *cs)`
- `child_handle_mouse` (function) `src/tab.c:1725` `static void child_handle_mouse(int wfd, child_state *cs)` -- Handles a mouse DOM event (OP_MOUSE).
- `geom_parent` (function) `src/tab.c:1755` `static dom_node_id geom_parent(void *ctx, dom_node_id n)`
- `child_handle_geom` (function) `src/tab.c:1763` `static void child_handle_geom(int wfd, child_state *cs, const int32_t *words, size_t n)` -- OP_GEOM (spec/js_geom.md): installs the parent's laid-out geometry into the page's JS, aggregated into ancestors...
- `child_handle_submit` (function) `src/tab.c:1789` `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` -- Fires a submit event on the form enclosing node_id.
- `child_handle_eval` (function) `src/tab.c:1823` `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` -- Response: [ok:int32][is_exception:int32][value_len][value]. ok==0 means a worker-level failure (no page loaded); a...
- `child_handle_decode_image` (function) `src/tab.c:1863` `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` -- Response: [ok:int32] then, when ok, [w:u32][h:u32][stride:u32][len:size_t][data].
- `child_handle_decode_image_b64` (function) `src/tab.c:1885` `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)` -- data: URI images: the parent only sliced the base64 payload (pure pointer arithmetic, no interpretation); the base64...
- `gen_session_key` (function) `src/tab.c:1897` `static uint64_t gen_session_key(void)`
- `tab_worker_run` (function) `src/tab.c:1917` `static void tab_worker_run(int rfd, int wfd)` -- The confined request loop.
- `EPIPE` (function) `src/tab.c:1919` `* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();`
- `tzset` (function) `src/tab.c:1935` `* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);`
- `depth` (function) `src/tab.c:1940` `* defense in depth (seccomp already excludes open/socket/exec);`
- `parse_worker_fd` (function) `src/tab.c:2132` `static int parse_worker_fd(const char *s, int *out)` -- free(buf); free(url); free(cookies); free(storage); } child_reset_page(&cs); fb_buffer_free(&cs.log); _exit(0); } /*...
- `tab_parse_worker_args` (function) `src/tab.c:2144` `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)`
- `tab_worker_dispatch` (function) `src/tab.c:2154` `void tab_worker_dispatch(int argc, char **argv)`
- `load` (function) `src/tab.c:2171` `* subresource requests this load (set per page: host in allow.conf AND js.conf);`
- `ignore_sigpipe` (function) `src/tab.c:2208` `static void ignore_sigpipe(void)` -- A write to a dead child must not kill the parent with SIGPIPE.
- `tab_refresh_alive` (function) `src/tab.c:2215` `static void tab_refresh_alive(tab *t)`
- `read_field` (function) `src/tab.c:2234` `static int read_field(int fd, char **out, size_t *out_len)` -- Read one length-prefixed owned field from the child, capped against * amplification. *out is NUL-terminated.
- `read_view` (function) `src/tab.c:2250` `static int read_view(int fd, pv_view **out)` -- Reads a display list serialised by write_view into a fresh pv_view.
- `tests` (function) `src/tab.c:2325` `* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed...`
- `layout` (function) `src/tab.c:2431` `* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property....`
- `column` (function) `src/tab.c:2442` `* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation...`
- `read_console` (function) `src/tab.c:2777` `static int read_console(int fd, fb_buffer *out)` -- Reads the console section written by write_console into out (a zero-initialised fb_buffer).
- `send_request` (function) `src/tab.c:2814` `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` -- if (elen != 0) { txt = (char *)malloc(elen); if (txt == NULL) { free(file); return -1; } if (read_full(fd, txt...
- `io_failure` (function) `src/tab.c:2824` `static tab_status io_failure(tab *t)`
- `exec_worker_child` (function) `src/tab.c:2832` `static void exec_worker_child(int rfd, int wfd)` -- Child half of the fork: re-exec a fresh worker image so it inherits NONE of the parent's address space (no other...
- `tab_set_fetcher` (function) `src/tab.c:2904` `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)`
- `tab_set_css_sink` (function) `src/tab.c:2910` `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)`
- `tab_set_op_net_budget_ms` (function) `src/tab.c:2916` `void tab_set_op_net_budget_ms(tab *t, int ms)`
- `tab_set_net_allowed` (function) `src/tab.c:2920` `void tab_set_net_allowed(tab *t, int allowed)`
- `tab_set_css_allowed` (function) `src/tab.c:2925` `void tab_set_css_allowed(tab *t, int allowed)`
- `tab_last_subreq_stats` (function) `src/tab.c:2930` `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)`
- `tab_set_identity` (function) `src/tab.c:2935` `void tab_set_identity(tab *t, const char *serialized)`
- `tab_set_viewport_w` (function) `src/tab.c:2943` `void tab_set_viewport_w(tab *t, int px)`
- `tab_set_cookies` (function) `src/tab.c:2948` `void tab_set_cookies(tab *t, const char *cookies)`
- `tab_subreq_permitted` (function) `src/tab.c:2954` `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)`
- `answered` (function) `src/tab.c:2966` `* A refused frame is still consumed and answered (status 0), so the protocol never
 * desyncs. Re...`
- `hist_ops_free` (function) `src/tab.c:3018` `static void hist_ops_free(tab_hist_op *ops, size_t n)`
- `is_activation_event` (function) `src/tab.c:3083` `static int is_activation_event(const char *type)` -- HTML 6.4.2 activation-triggering input events: only these let a page open a * window.
- `open_urls_free` (function) `src/tab.c:3092` `static void open_urls_free(char **u, size_t n)`
- `read_opens` (function) `src/tab.c:3102` `static tab_status read_opens(tab *t, const char *page_url, int gesture,
                         ...` -- Reads the window.open block (see write_opens).
- `ws_ops_free` (function) `src/tab.c:3131` `static void ws_ops_free(tab_ws_op *ops, size_t n)`
- `read_ws` (function) `src/tab.c:3140` `static tab_status read_ws(tab *t, tab_ws_op **out, size_t *nout)` -- Reads the WebSocket block (see write_ws), bounded by JT_WS_MAX_OPS ops and JT_WS_MAX_BYTES of payload.
- `gate_js_nav` (function) `src/tab.c:3209` `static char *gate_js_nav(const char *page_url, const char *navreq, size_t nlen, int *oom)` -- Gates a raw JS navigation request against the page URL in the trusted parent (Zero Trust: a compromised worker...
- `tab_load` (function) `src/tab.c:3219` `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)`
- `tab_load_ex` (function) `src/tab.c:3223` `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)`
- `tab_load_full` (function) `src/tab.c:3227` `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...`
- `tab_click` (function) `src/tab.c:3426` `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)`
- `tab_tick` (function) `src/tab.c:3434` `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)`
- `tab_submit` (function) `src/tab.c:3444` `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` -- Dispatches a submit event on the form enclosing node_id.
- `tab_read_view` (function) `src/tab.c:3552` `tab_status tab_read_view(tab *t, tab_page *out)` -- Reads the TAG_RESULT + TAG_VIEW response into *out (titles + view + console). * Used by tab_mutation_request...
- `frames` (function) `src/tab.c:3558` `* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of...`
- `tab_await_result` (function) `src/tab.c:3561` `static tab_status tab_await_result(tab *t)`
- `tab_await_result_inner` (function) `src/tab.c:3569` `static tab_status tab_await_result_inner(tab *t)`
- `tab_read_view_ex` (function) `src/tab.c:3579` `static tab_status tab_read_view_ex(tab *t, tab_page *out, int gesture)`
- `tab_eval` (function) `src/tab.c:3674` `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)`
- `tab_decode_image_op` (function) `src/tab.c:3715` `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...` -- Shared by tab_decode_image and tab_decode_image_data_url: sends `bytes` under opcode `op` and parses the...
- `tab_decode_image` (function) `src/tab.c:3757` `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)`
- `tab_decode_image_data_url` (function) `src/tab.c:3764` `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)`
- `tab_alive` (function) `src/tab.c:3783` `int tab_alive(const tab *t)`
- `tab_child_pid` (function) `src/tab.c:3789` `pid_t tab_child_pid(const tab *t)`
- `tab_close` (function) `src/tab.c:3793` `void tab_close(tab *t)`
- `tab_page_free` (function) `src/tab.c:3810` `void tab_page_free(tab_page *p)`
- `tab_eval_result_free` (function) `src/tab.c:3840` `void tab_eval_result_free(tab_eval_result *r)`
- `tab_image_free` (function) `src/tab.c:3849` `void tab_image_free(tab_image *img)`
- `tab_geometry_send` (function) `src/tab.c:3861` `static tab_status tab_geometry_send(tab *t, const int32_t *buf, size_t words)` -- Writes one encoded geometry table and waits for its acknowledgement (serving any network the * observer callbacks it...
- `geometry_encode` (function) `src/tab.c:3879` `static int32_t *geometry_encode(const jg_table *g, size_t *words_out)`
- `tab_set_geometry` (function) `src/tab.c:3889` `tab_status tab_set_geometry(tab *t, const jg_table *g)`
- `job_discard` (function) `src/tab.c:3903` `static void job_discard(tab *t)`
- `tab_async_sync` (function) `src/tab.c:3915` `static void tab_async_sync(tab *t)` -- Waits for a running job and DISCARDS its result: any other worker call is about to change * the page, so the...
- `job_main` (function) `src/tab.c:3925` `static void *job_main(void *arg)`
- `tab_async_fd` (function) `src/tab.c:3941` `int tab_async_fd(tab *t)`
- `tab_async_busy` (function) `src/tab.c:3950` `int tab_async_busy(const tab *t)`
- `job_start` (function) `src/tab.c:3954` `static tab_status job_start(tab *t)`
- `tab_tick_async` (function) `src/tab.c:3967` `tab_status tab_tick_async(tab *t, int elapsed_ms)`
- `tab_geometry_async` (function) `src/tab.c:3977` `tab_status tab_geometry_async(tab *t, const jg_table *g)`
- `tab_async_finish` (function) `src/tab.c:3992` `tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)`
- `tab_popstate` (function) `src/tab.c:4014` `tab_status tab_popstate(tab *t, int index, tab_page *out)`
- `tab_ws_event` (function) `src/tab.c:4021` `tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len,
       ...`
- `tab_set_storage` (function) `src/tab.c:4041` `void tab_set_storage(tab *t, const char *blob, size_t len)`

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
- `is_private_use` (function) `src/text_shape.c:616` `static int is_private_use(unsigned cp)` -- if (l > n) l = 1; if (l == 1) { *len = 1; return (c < 0x80) ? c : 0xFFFDu; } unsigned cp = c & (0x7fu >> l); for...
- `rides_previous` (function) `src/text_shape.c:621` `static int rides_previous(unsigned cp)` -- cp = (cp << 6) | (u[k] & 0x3fu); } len = l; return cp; } #define TSH_BLANK_GLYPH ((unsigned long)-1) /* Private Use...
- `tsh_segment` (function) `src/text_shape.c:629` `int tsh_segment(const char *text, size_t len, tsh_cover_fn cover, void *ctx,
                tsh_...`
- `fb_clear` (function) `src/text_shape.c:669` `static void fb_clear(void)`
- `fb_entry` (function) `src/text_shape.c:679` `static tsh_entry *fb_entry(unsigned cp, int bold)` -- The fallback entry covering cp (bold or regular), or NULL.
- `cover_cp` (function) `src/text_shape.c:750` `static int cover_cp(unsigned cp, void *vctx)` -- cover callback: 0 when the requested face has the glyph (or nothing else * does), else the id of the fallback face...
- `shape_entry` (function) `src/text_shape.c:764` `static tsh_status shape_entry(tsh_entry *e, double px, const char *text, size_t len,
            ...` -- static int cover_cp(unsigned cp, void *vctx) { tsh_cover_ctx *c = (tsh_cover_ctx *)vctx; hb_codepoint_t g; if (cp ==...
- `shape_runs` (function) `src/text_shape.c:800` `static tsh_status shape_runs(cairo_t *cr, const tsh_font *f, double px, double x,
               ...` -- Measures (cr == NULL) or draws [text,len) run by run, each with the face that * has its glyphs.
- `tsh_measure` (function) `src/text_shape.c:846` `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)`
- `tsh_draw` (function) `src/text_shape.c:852` `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, doub...`
- `tsh_face` (function) `src/text_shape.c:859` `cairo_font_face_t *tsh_face(const tsh_font *f)`
- `tsh_shutdown` (function) `src/text_shape.c:865` `void tsh_shutdown(void)`

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


Next: [API_p11.md](API_p11.md)
