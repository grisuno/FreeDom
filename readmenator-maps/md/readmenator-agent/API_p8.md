# API (page 8 of 12)
Previous: [API_p7.md](API_p7.md)

## src/flex_layout.c
Depends on: `include/flex_layout.h`
- `nn` (function) `src/flex_layout.c:19` `static double nn(double v)` -- bounded by FX_MAX_ITEMS (no VLAs).
- `fx_flex_line` (function) `src/flex_layout.c:23` `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                ...`
- `fx_grid_columns` (function) `src/flex_layout.c:128` `fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          doubl...`
- `fx_grid_column_count` (function) `src/flex_layout.c:133` `int fx_grid_column_count(int flow, int cols, int rows, size_t items)`
- `fx_autofill_count` (function) `src/flex_layout.c:141` `size_t fx_autofill_count(double avail, double gap, double minw)`
- `fx_grid_columns_weighted` (function) `src/flex_layout.c:151` `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                      ...`
- `fx_grid_place_span` (function) `src/flex_layout.c:185` `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                      ...`
- `fx_grid_area_hash` (function) `src/flex_layout.c:327` `unsigned fx_grid_area_hash(const char *name)`
- `area_token_is_null_cell` (function) `src/flex_layout.c:351` `static int area_token_is_null_cell(const char *tok, size_t len)` -- 0 is reserved for "no name" (the null cell token), so a name that hashes to * it is nudged; the alternative is a...
- `fx_grid_areas_parse` (function) `src/flex_layout.c:357` `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)`
- `fx_grid_area_rect` (function) `src/flex_layout.c:432` `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,
                            int ...`
- `float_pack_impl` (function) `src/flex_layout.c:474` `static fx_status float_pack_impl(const double *width, const int *side, size_t n,
                ...` -- Shared packer: wrap == 0 is the single-row v1 contract (overflow clamps in place); wrap != 0 starts a new row...
- `fx_float_insets` (function) `src/flex_layout.c:514` `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,
                 ...`
- `fx_float_pack` (function) `src/flex_layout.c:554` `fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        d...`
- `fx_float_pack_wrap` (function) `src/flex_layout.c:559` `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,
                    ...`
- `fx_grid_cell` (function) `src/flex_layout.c:601` `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)`
- `fx_auto_margins` (function) `src/flex_layout.c:613` `fx_status fx_auto_margins(fx_result *res, size_t n, const unsigned char *auto_l,
                ...` -- } void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col) { if (row == NULL || col == NULL) return...
- `fx_auto_min_size` (function) `src/flex_layout.c:636` `double fx_auto_min_size(double min_content, double basis, double author_min,
                    ...`
- `fx_multicol_used` (function) `src/flex_layout.c:653` `fx_status fx_multicol_used(double avail_w, int column_count, double column_width,
               ...`
- `fx_multicol_balance` (function) `src/flex_layout.c:690` `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,
                        ...`
- `fx_justify_name` (function) `src/flex_layout.c:721` `const char *fx_justify_name(fx_justify j)`
- `fx_column_place` (function) `src/flex_layout.c:733` `fx_status fx_column_place(const double *h, const double *grow, size_t n, double gap,
            ...`
- `fx_column_place_m` (function) `src/flex_layout.c:740` `fx_status fx_column_place_m(const double *h, const double *grow, const int *mauto,
              ...`
- `fx_cross_offset` (function) `src/flex_layout.c:801` `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r)`
- `gl_ws` (function) `src/flex_layout.c:813` `static int gl_ws(char c)` -- } double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r) { double room = avail - w; if...
- `gl_lower` (function) `src/flex_layout.c:817` `static int gl_lower(char c)`
- `gl_kw` (function) `src/flex_layout.c:820` `static int gl_kw(const char *p, const char *end, const char *kw)` -- if (mauto_r) return 0.0; if (align == 1) return room / 2.0; if (align == 2) return room; return 0.0; } /* ASCII...
- `gl_int` (function) `src/flex_layout.c:830` `static int gl_int(const char *p, const char *end, long cap, long *out)` -- A CSS <integer> (optional sign, digits only) filling exactly [p, end).
- `gl_side_range` (function) `src/flex_layout.c:845` `static int gl_side_range(const char *p, const char *end, int *out)` -- int neg = 0; if (p < end && (*p == '+' || *p == '-')) { neg = (*p == '-'); ++p; } if (p >= end) return 0; long v =...
- `fx_grid_line_side` (function) `src/flex_layout.c:868` `int fx_grid_line_side(const char *s, int *out)`
- `fx_grid_line_parse` (function) `src/flex_layout.c:876` `int fx_grid_line_parse(const char *v, int *start, int *end)`
- `gl_is_span` (function) `src/flex_layout.c:893` `static int gl_is_span(int v)`
- `gl_is_line` (function) `src/flex_layout.c:894` `static int gl_is_line(int v)`
- `fx_grid_line_resolve` (function) `src/flex_layout.c:896` `void fx_grid_line_resolve(int start, int end, int ntracks, int *pos0, int *span)`
- `fx_col_free_split` (function) `src/flex_layout.c:938` `fx_status fx_col_free_split(double free_px, const int *grow, const int *mauto, size_t n,
        ...`

## src/form.c
Depends on: `include/form.h`
- `put_char` (function) `src/form.c:17` `static int put_char(char *out, size_t outsz, size_t *pos, char c)` -- No I/O, no global state.
- `enc_component` (function) `src/form.c:25` `static int enc_component(const char *s, char *out, size_t outsz, size_t *pos)` -- Encodes one component per the WHATWG application/x-www-form-urlencoded byte * serialiser.
- `fm_encode` (function) `src/form.c:43` `fm_status fm_encode(const fm_field *fields, size_t n,
                    char *out, size_t outsz...`
- `copy_fit` (function) `src/form.c:66` `static int copy_fit(char *dst, size_t dstsz, const char *src)` -- if (fields[i].name == NULL) continue; /* a nameless control is not submitted if (!first && put_char(out, outsz...
- `clean_action` (function) `src/form.c:75` `static int clean_action(const char *action, char *out, size_t outsz)` -- Removes TAB/LF/CR and trims leading/trailing ASCII spaces (WHATWG cleaning of a * URL-bearing attribute).
- `strip_query` (function) `src/form.c:93` `static void strip_query(char *url)` -- if (c == '\t' || c == '\n' || c == '\r') continue; if (o + 1 >= outsz) return -1; out[o++] = c; } out[o] = '\0'...
- `resolve_target` (function) `src/form.c:101` `static fm_block_reason resolve_target(const char *base, const char *act,
                        ...` -- Resolves the cleaned action into a validated absolute https URL R, or returns a * block reason.
- `fm_build` (function) `src/form.c:120` `fm_status fm_build(const char *base, const char *action, fm_method method,
                   con...`

## src/frame_broker.c
Depends on: `include/frame_broker.h`
- `lc` (function) `src/frame_broker.c:9` `static char lc(char c)`
- `host_char_ok` (function) `src/frame_broker.c:11` `static int host_char_ok(char c)`
- `fbk_origin_of` (function) `src/frame_broker.c:15` `int fbk_origin_of(const char *url, char *out, size_t cap)`
- `fbk_init` (function) `src/frame_broker.c:53` `int fbk_init(fbk_table *t, const char *top_url)`
- `live` (function) `src/frame_broker.c:62` `static int live(const fbk_table *t, int id)`
- `fbk_add` (function) `src/frame_broker.c:66` `int fbk_add(fbk_table *t, int parent, const char *url, int *out_id)`
- `fbk_remove` (function) `src/frame_broker.c:84` `void fbk_remove(fbk_table *t, int id)`
- `fbk_origin` (function) `src/frame_broker.c:96` `const char *fbk_origin(const fbk_table *t, int id)`
- `target_admits` (function) `src/frame_broker.c:101` `static int target_admits(const char *target, const char *snd, const char *recv)` -- int changed = 1;                                  /* fixpoint: slots are reused, order is not a tree order while...
- `fbk_route` (function) `src/frame_broker.c:118` `fbk_verdict fbk_route(const fbk_table *t, int from, fbk_rel rel, int child,
                     ...`

## src/frame_clock.c
Depends on: `include/frame_clock.h`
- `fc_set_active` (function) `src/frame_clock.c:16` `void fc_set_active(fc_clock *c, int active)`
- `fc_needs_tick` (function) `src/frame_clock.c:21` `int fc_needs_tick(const fc_clock *c)`
- `fc_interval_ms` (function) `src/frame_clock.c:26` `int fc_interval_ms(const fc_clock *c)`

## src/frame_host.c
Depends on: `include/frame_broker.h`, `include/frame_host.h`
- `fh_new` (function) `src/frame_host.c:35` `fh_host *fh_new(const char *top_url, tab_fetch_fn fetch, void *fetch_ctx,
                fh_top_...`
- `slot_release_view` (function) `src/frame_host.c:47` `static void slot_release_view(fh_slot *sl)`
- `reap` (function) `src/frame_host.c:55` `static void reap(fh_host *h)` -- h->fetch = fetch; h->fetch_ctx = fetch_ctx; h->top_msg = top_msg; h->top_ctx = top_ctx; for (int i = 0; i <...
- `fh_free` (function) `src/frame_host.c:67` `void fh_free(fh_host *h)`
- `fh_count` (function) `src/frame_host.c:76` `int fh_count(const fh_host *h)`
- `load_frame` (function) `src/frame_host.c:85` `static void load_frame(fh_host *h, int id, const char *url)` -- Loads the document of frame `id` (already registered in the table).
- `find_child` (function) `src/frame_host.c:129` `static int find_child(const fh_host *h, int parent, int token)`
- `token_seen_by` (function) `src/frame_host.c:137` `static int token_seen_by(const fh_host *h, int dest, int from)` -- Token a receiving frame knows `from` by: from's own token when it is a direct child, otherwise * that of the...
- `post_op` (function) `src/frame_host.c:143` `static void post_op(fh_host *h, int from, const tab_ws_op *op)`
- `apply_ops` (function) `src/frame_host.c:198` `static void apply_ops(fh_host *h, int from, const tab_ws_op *ops, size_t n)`
- `fh_apply_top` (function) `src/frame_host.c:221` `void fh_apply_top(fh_host *h, const tab_page *page)`
- `fh_tick` (function) `src/frame_host.c:226` `int fh_tick(fh_host *h, int elapsed_ms)`
- `fh_generation` (function) `src/frame_host.c:250` `unsigned fh_generation(const fh_host *h)`
- `fh_frame_view` (function) `src/frame_host.c:252` `const pv_view *fh_frame_view(const fh_host *h, const char *url, tab **t_out)`

## src/freebug.c
Depends on: `include/freebug.h`
- `whole` (function) `src/freebug.c:5` `* FB_MAX_TOTAL_BYTES is dropped whole (overflow flag raised, prior entries kept);`
- `fb_buffer_init` (function) `src/freebug.c:15` `void fb_buffer_init(fb_buffer *b)`
- `fb_buffer_push` (function) `src/freebug.c:19` `int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)`
- `fb_buffer_push_loc` (function) `src/freebug.c:23` `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len,
                   ...`
- `fb_buffer_reset` (function) `src/freebug.c:78` `void fb_buffer_reset(fb_buffer *b)`
- `fb_buffer_free` (function) `src/freebug.c:91` `void fb_buffer_free(fb_buffer *b)`
- `fb_buffer_count` (function) `src/freebug.c:101` `size_t fb_buffer_count(const fb_buffer *b)`
- `fb_buffer_at` (function) `src/freebug.c:105` `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)`
- `fb_level_name` (function) `src/freebug.c:110` `const char *fb_level_name(int level)`

## src/freedom.c
Depends on: `include/dom_debug.h`, `include/fb_panes.h`, `include/frame_host.h`, `include/freebug.h`, `include/hls.h`, `include/host_conf.h`, `include/hostblock.h`, `include/html_parse.h`, `include/identity.h`, `include/js_policy.h`, `include/link_nav.h`, `include/media_decoder.h`, `include/net_realm.h`, `include/page_view.h`, `include/perf_trace.h`, `include/prefetch.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/tab.h`, `include/text_shape.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/webcaps.h`, `include/webfont.h`, `include/webfont_load.h`, `include/wl_display.h`
- `print_usage` (function) `src/freedom.c:55` `static void print_usage(FILE *fp, const char *prog)`
- `is_https_url` (function) `src/freedom.c:84` `static int is_https_url(const char *s)`
- `is_http_url` (function) `src/freedom.c:88` `static int is_http_url(const char *s)`
- `is_overlay_http` (function) `src/freedom.c:93` `static int is_overlay_http(const char *s)` -- fprintf(fp, "  --dump-video-url: headless, print the first detected video source URL to stdout (no truncation)\n")...
- `now_us` (function) `src/freedom.c:149` `static uint64_t now_us(void)`
- `timings_ensure_init` (function) `src/freedom.c:155` `static void timings_ensure_init(void)`
- `timings_enabled` (function) `src/freedom.c:159` `static int timings_enabled(void)`
- `timings_dump` (function) `src/freedom.c:163` `static void timings_dump(void)`
- `hl_frame_top_msg` (function) `src/freedom.c:215` `static void hl_frame_top_msg(void *ctx, const char *data, size_t len)`
- `user_impersonate_enabled` (function) `src/freedom.c:236` `static int user_impersonate_enabled(void)`
- `read_file` (function) `src/freedom.c:243` `static char *read_file(const char *path, size_t *out_len)` -- User opt-in for TLS-impersonation blend: --impersonate or FREEDOM_IMPERSONATE=1.
- `headless_load_hosts` (function) `src/freedom.c:261` `static void headless_load_hosts(void)`
- `apply_identity` (function) `src/freedom.c:281` `static void apply_identity(sf_config *cfg)`
- `apply_as_gui` (function) `src/freedom.c:286` `static void apply_as_gui(const char *top_url, int flag_js, int flag_css, int flag_images)`
- `is_blank_text` (function) `src/freedom.c:324` `static int is_blank_text(const char *s)` -- .js_mode       = mode, .host_in_js    = host[0] != '\0' && g_js_hosts != NULL && hb_is_allowlisted(g_js_hosts...
- `print_doc` (function) `src/freedom.c:337` `static void print_doc(const rd_doc *doc)` -- Writes the render document as deterministic, flowing plain text for a terminal and for an AI agent (content as data...
- `print_console` (function) `src/freedom.c:430` `static void print_console(const fb_buffer *log)` -- Prints the captured Freebug console (the developer-visible JS transcript) to stdout, one entry per line, prefixed...
- `print_dom` (function) `src/freedom.c:447` `static void print_dom(const rd_doc *doc)` -- Prints the paint-ready render tree (dom_debug) to stdout.
- `print_dom_css` (function) `src/freedom.c:462` `static void print_dom_css(const rd_doc *doc)` -- Prints the CSS property inspector (dd_format_css) to stdout.
- `gets` (function) `src/freedom.c:482` `* gate a click gets (https-only, no downgrade, no foreign scheme), so relative * subresources work. Realm-routed...`
- `headless_fetch` (function) `src/freedom.c:486` `static int headless_fetch(void *ctx, const char *method, const char *url,
                       ...` -- tab_fetch_fn for the headless renderer: a policy-checked subresource fetch for page XHR/fetch and external <script...
- `foldback_cookies` (function) `src/freedom.c:573` `static void foldback_cookies(const char *url, const char *jar)` -- Folds a page's document.cookie jar ("a=1; b=2") back into the ephemeral network * jar, one pair at a time, so JS-set...
- `print_css_drops` (function) `src/freedom.c:597` `static void print_css_drops(const char *html, size_t len)` -- Prints the author-CSS drop report for `html`, sorted by occurrence count.
- `hl_font_stash_free` (function) `src/freedom.c:642` `static void hl_font_stash_free(hl_font_stash *s)`
- `hl_css_sink` (function) `src/freedom.c:655` `static void hl_css_sink(void *vctx, const char *url,
                        const char *body, si...` -- tab_css_sink_fn for headless: retains served 2xx CSS bodies (serial and pool paths alike) with an absolute https...
- `hl_font_fetch` (function) `src/freedom.c:692` `static int hl_font_fetch(void *vctx, const char *url,
                         int *out_status, c...` -- wf_fetch_fn around the headless policy gate (font bytes download like any * other subresource of this page). data...
- `render_page` (function) `src/freedom.c:720` `static int render_page(const char *html, size_t len, const char *top_url,
                       ...`
- `pool` (function) `src/freedom.c:784` `* the pool (unconsumed results freed, in-flight fetches joined). */ tab_set_fetcher(t, headless_fetch, (void...`
- `first` (function) `src/freedom.c:798` `* always cleared first (fetch_and_render may paint several pages per
     * process). A NULL top_...`
- `only` (function) `src/freedom.c:868` `* styling for the local render only (no network). --images enables image loading * AND rendering, including remote...`
- `sf_reason` (function) `src/freedom.c:994` `static const char *sf_reason(sf_status ss)`
- `fetch_and_render_one` (function) `src/freedom.c:1013` `static int fetch_and_render_one(const char *url, char **out_nav)` -- Fetches one url with secure_fetch and renders the result.
- `BLOCKED` (function) `src/freedom.c:1041` `* is BLOCKED (fail closed), never leaked over the clearnet. */ nr_route route = nr_route_for(url, global_net);`
- `elsewhere` (function) `src/freedom.c:1076` `* page whose script immediately forwards elsewhere (e.g. a search engine's
 * JS-capability inter...`
- `parent` (function) `src/freedom.c:1102` `* gated by the parent (ln_resolve: a local target stays under the document's
 * directory, a remo...`
- `run_headless` (function) `src/freedom.c:1139` `static int run_headless(const char *target)`
- `video_fetch_with_fallback` (function) `src/freedom.c:1176` `static sf_status video_fetch_with_fallback(const char *url, sf_config *cfg,
                     ...` -- Fetches a URL with TLS fallbacks (PQ-hybrid -> classical KE -> allowlisted insecure), same chain as...
- `run_dump_video` (function) `src/freedom.c:1287` `static int run_dump_video(const char *url)` -- -dump-video handler: fetches a video URL and writes the stream to a file * or stdout.
- `main` (function) `src/freedom.c:1306` `int main(int argc, char **argv)`

## src/hls.c
Depends on: `include/hls.h`
- `last_char` (function) `src/hls.c:38` `static const char *last_char(const char *s, size_t n, int c)` -- Finds the last occurrence of character `c` in `s` (length `n`). * Returns NULL if not found.
- `name` (function) `src/hls.c:46` `* attr is the attribute name (e.g. "BANDWIDTH=");`
- `parse_attr_long` (function) `src/hls.c:48` `static int parse_attr_long(const char *attrs, const char *end,
                           const c...` -- Extracts a named attribute value from an #EXT-X-STREAM-INF attribute string. attr is the attribute name (e.g....
- `parse_attr_resolution` (function) `src/hls.c:62` `static void parse_attr_resolution(const char *attrs, const char *end,
                           ...` -- static int parse_attr_long(const char *attrs, const char *end, const char *attr, long *val) { size_t alen =...
- `hls_parse` (function) `src/hls.c:80` `hls_status hls_parse(const char *text, size_t len, hls_playlist **out)`
- `hls_select_variant` (function) `src/hls.c:202` `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h)`
- `hls_resolve_url` (function) `src/hls.c:223` `size_t hls_resolve_url(const char *base_url, const char *segment_url,
                       char...`
- `hls_playlist_free` (function) `src/hls.c:253` `void hls_playlist_free(hls_playlist *pl)`

## src/host_conf.c
Depends on: `include/host_conf.h`
- `add_dir` (function) `src/host_conf.c:10` `static void add_dir(hcf_dirs *out, const char *path)`
- `hcf_search_dirs` (function) `src/host_conf.c:20` `void hcf_search_dirs(const char *env, const char *home, hcf_dirs *out)`
- `hcf_search_dirs_from_env` (function) `src/host_conf.c:32` `void hcf_search_dirs_from_env(hcf_dirs *out)`
- `read_conf` (function) `src/host_conf.c:37` `static char *read_conf(const char *dir, const char *name)` -- add_dir(out, env); if (home != NULL && home[0] != '\0') { char user[HCF_PATH_MAX]; int n = snprintf(user, sizeof...
- `load_into` (function) `src/host_conf.c:58` `static void load_into(hb_set *s, const char *dir, const char *name, hb_list list)`
- `hcf_load_filter` (function) `src/host_conf.c:65` `hb_set *hcf_load_filter(const hcf_dirs *dirs)`
- `hcf_load_allowlist` (function) `src/host_conf.c:76` `hb_set *hcf_load_allowlist(const hcf_dirs *dirs, const char *fname)`

## src/hostblock.c
Depends on: `include/hostblock.h`, `include/util.h`
- `table_probe` (function) `src/hostblock.c:38` `static size_t table_probe(const hb_table *t, const char *key, size_t klen)` -- Finds the slot for key (length klen) in t, which must have a free slot.
- `table_grow` (function) `src/hostblock.c:49` `static int table_grow(hb_table *t, size_t newcap)` -- Finds the slot for key (length klen) in t, which must have a free slot.
- `table_insert` (function) `src/hostblock.c:71` `static int table_insert(hb_table *t, const char *key, size_t klen)` -- Inserts key (length klen) into t, deduping.
- `table_contains` (function) `src/hostblock.c:92` `static int table_contains(const hb_table *t, const char *key)`
- `table_free` (function) `src/hostblock.c:98` `static void table_free(hb_table *t)`
- `lower` (function) `src/hostblock.c:107` `static char lower(char c)`
- `is_ip_token` (function) `src/hostblock.c:113` `static int is_ip_token(const char *s, size_t n)` -- A token made only of digits, '.' and ':' is an IP literal (v4 or v6), not a * domain.
- `is_domain_char` (function) `src/hostblock.c:122` `static int is_domain_char(char c)` -- A token made only of digits, '.' and ':' is an IP literal (v4 or v6), not a * domain.
- `hb_new` (function) `src/hostblock.c:144` `hb_set *hb_new(void)`
- `hb_free` (function) `src/hostblock.c:149` `void hb_free(hb_set *s)`
- `hb_load` (function) `src/hostblock.c:156` `hb_status hb_load(hb_set *s, const char *text, hb_list list)`
- `hb_check` (function) `src/hostblock.c:193` `hb_decision hb_check(const hb_set *s, const char *host)`
- `hb_check_subresource` (function) `src/hostblock.c:218` `hb_decision hb_check_subresource(const hb_set *s, const char *host, int page_trusted)`
- `hb_is_allowlisted` (function) `src/hostblock.c:223` `int hb_is_allowlisted(const hb_set *s, const char *host)`
- `hb_count` (function) `src/hostblock.c:243` `size_t hb_count(const hb_set *s, hb_list list)`

## src/hostedit.c
Depends on: `include/hostedit.h`
- `he_lower` (function) `src/hostedit.c:12` `static char he_lower(char c)`
- `is_label_char` (function) `src/hostedit.c:16` `static int is_label_char(char c)`
- `valid_host` (function) `src/hostedit.c:22` `static int valid_host(const char *host, size_t n)` -- #include "hostedit.h" #include <string.h> static char he_lower(char c) { return (c >= 'A' && c <= 'Z') ?
- `he_make_line` (function) `src/hostedit.c:41` `he_status he_make_line(const char *host, char *out, size_t cap)`
- `is_ip_token` (function) `src/hostedit.c:67` `static int is_ip_token(const char *ts, const char *te)` -- True if the token looks like an IPv4 dotted-quad / contains only digits and dots * (matches hostblock's is_ip_token...
- `he_scan` (function) `src/hostedit.c:80` `static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), void *ctx)` -- Visits each domain token (non-comment, non-IP) of a hosts-format text in document order, calling fn(ts, tl, ctx).
- `has_host_cb` (function) `src/hostedit.c:105` `static int has_host_cb(const char *ts, size_t tl, void *ctx)`
- `he_text_has_host` (function) `src/hostedit.c:109` `int he_text_has_host(const char *text, const char *host)`
- `contains_ci` (function) `src/hostedit.c:115` `static int contains_ci(const char *hs, size_t hl, const char *needle)` -- } return 0; } static int has_host_cb(const char *ts, size_t tl, void *ctx) { return token_eq_host(ts, ts + tl...
- `starts_with_ci` (function) `src/hostedit.c:128` `static int starts_with_ci(const char *hs, size_t hl, const char *pfx)`
- `suggest_cb` (function) `src/hostedit.c:144` `static int suggest_cb(const char *ts, size_t tl, void *vctx)`
- `he_suggest` (function) `src/hostedit.c:164` `int he_suggest(const char *text, const char *query,
               char results[][HE_MAX_HOST + 1...`
- `he_cdn_kind` (function) `src/hostedit.c:173` `he_cdn_kind_t he_cdn_kind(const char *url)`

## src/html_parse.c
Depends on: `include/dom.h`, `include/html_parse.h`, `include/util.h`
- `dup_bytes` (function) `src/html_parse.c:27` `static char *dup_bytes(const lxb_char_t *src, size_t len)`
- `node_next` (function) `src/html_parse.c:37` `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` -- }; /* --- helpers --- static char *dup_bytes(const lxb_char_t *src, size_t len) { if (len == (size_t)-1) return...
- `attr_is_event_handler` (function) `src/html_parse.c:47` `static int attr_is_event_handler(const lxb_dom_attr_t *attr)`
- `node_is_script` (function) `src/html_parse.c:54` `static int node_is_script(const lxb_dom_node_t *node)`
- `strip_scripts` (function) `src/html_parse.c:60` `static void strip_scripts(lxb_html_document_t *document)`
- `type_is` (function) `src/html_parse.c:100` `static int type_is(const lxb_char_t *t, size_t len, const char *word)` -- HTML "the script element": type="module" (ASCII case-insensitive, whitespace * stripped) is an ES module; nothing...
- `type_is_module` (function) `src/html_parse.c:117` `static int type_is_module(const lxb_char_t *t, size_t len)`
- `script_classify` (function) `src/html_parse.c:121` `static int script_classify(const lxb_dom_node_t *n,
                           const lxb_char_t *...`
- `hp_extract_script_list` (function) `src/html_parse.c:164` `hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count)` -- Collects each executable <script> as its own entry, in document order: inline source for classic inline scripts, the...
- `lxb_dom_element_has_attribute` (function) `src/html_parse.c:230` `&& lxb_dom_element_has_attribute(sel, (const lxb_char_t *)"nomodule", 8);`
- `hp_free_scripts` (function) `src/html_parse.c:238` `void hp_free_scripts(hp_script *scripts, size_t count)`
- `attr_has_token_ci` (function) `src/html_parse.c:251` `static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle)` -- Whitespace-separated token test over a length-delimited attribute value, ASCII case-insensitive: rel="preload...
- `link_is_active_stylesheet` (function) `src/html_parse.c:272` `static int link_is_active_stylesheet(lxb_dom_element_t *el,
                                     ...` -- An applicable stylesheet <link>: rel token "stylesheet" and not "alternate"; a non-empty href; media absent/empty or...
- `hp_extract_stylesheet_hrefs` (function) `src/html_parse.c:294` `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count)`
- `hp_free_stylesheet_hrefs` (function) `src/html_parse.c:328` `void hp_free_stylesheet_hrefs(char **hrefs, size_t count)`
- `strip_event_handlers` (function) `src/html_parse.c:334` `static void strip_event_handlers(lxb_html_document_t *document)`
- `hp_config_default` (function) `src/html_parse.c:357` `hp_config hp_config_default(void)`
- `hp_validate_input` (function) `src/html_parse.c:365` `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg)`
- `hp_parse` (function) `src/html_parse.c:375` `hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out)`
- `hp_element_count` (function) `src/html_parse.c:409` `size_t hp_element_count(const hp_document *doc)`
- `hp_script_count` (function) `src/html_parse.c:419` `size_t hp_script_count(const hp_document *doc)`
- `hp_event_handler_count` (function) `src/html_parse.c:429` `size_t hp_event_handler_count(const hp_document *doc)`
- `hp_extract_text` (function) `src/html_parse.c:445` `char *hp_extract_text(const hp_document *doc, size_t *out_len)`
- `hp_get_title` (function) `src/html_parse.c:464` `char *hp_get_title(const hp_document *doc, size_t *out_len)`
- `hp_free` (function) `src/html_parse.c:479` `void hp_free(char *buf)`
- `hp_document_free` (function) `src/html_parse.c:483` `void hp_document_free(hp_document *doc)`
- `hp_document_root` (function) `src/html_parse.c:489` `const void *hp_document_root(const hp_document *doc)`

## src/http_cache.c
Depends on: `include/disk_store.h`, `include/http_cache.h`, `include/pq_seal.h`
- `days_in_month` (function) `src/http_cache.c:39` `static int days_in_month(int y, int m)`
- `days_from_civil` (function) `src/http_cache.c:46` `static long days_from_civil(int y, int m, int d)` -- #define HC_MAGIC      "FHC1\n" #define HC_NAME_HEX   64u #define HC_EVICT_EVERY 16u #define HC_MAX_AGE_CAP 31536000L...
- `hc_parse_http_date` (function) `src/http_cache.c:55` `time_t hc_parse_http_date(const char *s)`
- `cc_find` (function) `src/http_cache.c:74` `static int cc_find(const char *cc, const char *name, const char **val)` -- char mon[4] = ""; if (sscanf(c + 1, " %d %3s %d %d:%d:%d GMT", &d, mon, &y, &hh, &mm, &ss) != 6) return (time_t)-1...
- `cc_max_age` (function) `src/http_cache.c:92` `static int cc_max_age(const char *cc, long *out)` -- while (*p == ',' || *p == ' ' || *p == '\t') ++p; const char *e = p; while (*e != '\0' && *e != ',' && *e != '=' &&...
- `hc_storable` (function) `src/http_cache.c:107` `int hc_storable(long http_code, const hc_meta *m, size_t body_len)`
- `hc_lifetime` (function) `src/http_cache.c:115` `long hc_lifetime(const hc_meta *m)`
- `hc_classify` (function) `src/http_cache.c:136` `hc_class hc_classify(const hc_meta *m, time_t now)`
- `hex_of` (function) `src/http_cache.c:155` `static void hex_of(const uint8_t *b, size_t n, char *out)`
- `entry_path` (function) `src/http_cache.c:162` `static int entry_path(const hc_store *s, char kind, const char *partition, const char *url,
     ...` -- uint8_t    wrap[LS_KEY_LEN]; uint8_t    name_key[LS_KEY_LEN]; pqs_keys  *keys; unsigned   puts; pthread_mutex_t...
- `remove_entries` (function) `src/http_cache.c:180` `static void remove_entries(const char *dir)`
- `write_atomic` (function) `src/http_cache.c:192` `static int write_atomic(const char *path, const uint8_t *data, size_t len)`
- `read_file` (function) `src/http_cache.c:208` `static uint8_t *read_file(const char *path, size_t max, size_t *len)`
- `hc_open` (function) `src/http_cache.c:230` `hc_status hc_open(hc_store **out, const char *dir, const uint8_t wrap[LS_KEY_LEN])`
- `hc_close` (function) `src/http_cache.c:279` `void hc_close(hc_store *s)`
- `hc_body_free` (function) `src/http_cache.c:287` `void hc_body_free(uint8_t *body, size_t len)`
- `has_nl` (function) `src/http_cache.c:293` `static int has_nl(const char *s)`
- `meta_ok` (function) `src/http_cache.c:295` `static int meta_ok(const hc_meta *m)`
- `store_entry` (function) `src/http_cache.c:302` `static hc_status store_entry(hc_store *s, const char *path, const hc_meta *m,
                   ...` -- if (body == NULL) return; OPENSSL_cleanse(body, len); free(body); } static int has_nl(const char *s) { return...
- `load_entry` (function) `src/http_cache.c:327` `static hc_status load_entry(hc_store *s, const char *path, hc_meta *m, uint8_t **body,
          ...` -- memcpy(pt, head, (size_t)hn); if (body_len != 0) memcpy(pt + hn, body, body_len); uint8_t *blob = NULL; size_t bl =...
- `get_locked` (function) `src/http_cache.c:385` `static hc_status get_locked(hc_store *s, const char *partition, const char *url, hc_meta *meta,
 ...`
- `evict` (function) `src/http_cache.c:396` `static void evict(hc_store *s)` -- return rc; } static hc_status get_locked(hc_store *s, const char *partition, const char *url, hc_meta *meta, uint8_t...
- `put_locked` (function) `src/http_cache.c:434` `static hc_status put_locked(hc_store *s, const char *partition, const char *url, const hc_meta *m...`
- `redirect_put_locked` (function) `src/http_cache.c:446` `static hc_status redirect_put_locked(hc_store *s, const char *from, const char *to, time_t now)`
- `redirect_get_locked` (function) `src/http_cache.c:459` `static hc_status redirect_get_locked(hc_store *s, const char *from, time_t now, char *out, size_t...`
- `hc_clear` (function) `src/http_cache.c:473` `void hc_clear(hc_store *s)`
- `hc_get` (function) `src/http_cache.c:480` `hc_status hc_get(hc_store *s, const char *partition, const char *url, hc_meta *meta,
            ...`
- `hc_put` (function) `src/http_cache.c:489` `hc_status hc_put(hc_store *s, const char *partition, const char *url, const hc_meta *meta,
      ...`
- `hc_redirect_put` (function) `src/http_cache.c:498` `hc_status hc_redirect_put(hc_store *s, const char *from, const char *to, time_t now)`
- `hc_redirect_get` (function) `src/http_cache.c:506` `hc_status hc_redirect_get(hc_store *s, const char *from, time_t now, char *out, size_t cap)`

## src/identity.c
Depends on: `include/anti_fp.h`, `include/identity.h`
- `is_alpha` (function) `src/identity.c:20` `static int is_alpha(char c)`
- `is_alnum` (function) `src/identity.c:21` `static int is_alnum(char c)`
- `idn_defaults` (function) `src/identity.c:23` `void idn_defaults(idn_config *c)`
- `idn_is_default` (function) `src/identity.c:29` `int idn_is_default(const idn_config *c)`
- `idn_set_user_agent` (function) `src/identity.c:35` `int idn_set_user_agent(idn_config *c, const char *ua)`
- `tag_valid` (function) `src/identity.c:51` `static int tag_valid(const char *s, size_t n)` -- size_t n = strlen(ua); if (n >= IDN_UA_MAX) return -1; int printable = 0; for (size_t i = 0; i < n; ++i) { unsigned...
- `idn_set_languages` (function) `src/identity.c:64` `int idn_set_languages(idn_config *c, const char *list)`
- `idn_set_geo` (function) `src/identity.c:92` `int idn_set_geo(idn_config *c, double lat, double lon, double accuracy_m)`
- `idn_clear_geo` (function) `src/identity.c:104` `void idn_clear_geo(idn_config *c)`
- `idn_user_agent` (function) `src/identity.c:110` `const char *idn_user_agent(const idn_config *c)`
- `idn_accept_language` (function) `src/identity.c:114` `size_t idn_accept_language(const idn_config *c, char *out, size_t cap)`
- `idn_primary_language` (function) `src/identity.c:144` `size_t idn_primary_language(const idn_config *c, char *out, size_t cap)`
- `hexval` (function) `src/identity.c:158` `static int hexval(int ch)`
- `pct_decode` (function) `src/identity.c:167` `static long pct_decode(const char *s, size_t n, char *out, size_t cap, int plus)` -- Decodes %XX (and '+' when plus) from [s, s+n) into out.
- `append` (function) `src/identity.c:187` `static int append(char *buf, size_t *n, size_t cap, const char *fmt, ...)`
- `append_pct` (function) `src/identity.c:198` `static int append_pct(char *buf, size_t *n, size_t cap, const char *s)`
- `idn_serialize` (function) `src/identity.c:207` `size_t idn_serialize(const idn_config *c, char *out, size_t cap)`
- `parse_geo` (function) `src/identity.c:228` `static int parse_geo(const char *s, double *lat, double *lon, double *acc)` -- || append(out, &n, cap, "|geo=") != 0) { out[0] = '\0'; return 0; } if (c->geo_mode == IDN_GEO_FIXED && append(out...
- `idn_parse` (function) `src/identity.c:241` `void idn_parse(idn_config *c, const char *text)`
- `parse_number` (function) `src/identity.c:275` `static int parse_number(const char *s, double *out)`
- `idn_apply_query` (function) `src/identity.c:282` `unsigned idn_apply_query(idn_config *c, const char *query)`
- `esc_append` (function) `src/identity.c:361` `static int esc_append(char *buf, size_t *n, size_t cap, const char *s)`
- `idn_render_page` (function) `src/identity.c:377` `size_t idn_render_page(const idn_config *c, char *out, size_t cap)`

## src/image_decode.c
Depends on: `include/image_decode.h`
- `exit` (function) `src/image_decode.c:6` `* malformed stream fails closed instead of calling exit(). GIF uses an own pure-C * bounded LZW decoder (no giflib)....`
- `read_be32` (function) `src/image_decode.c:52` `static uint32_t read_be32(const uint8_t *p)`
- `img_png_dimensions` (function) `src/image_decode.c:57` `img_status img_png_dimensions(const uint8_t *bytes, size_t len,
                              uin...`
- `img_dimensions_ok` (function) `src/image_decode.c:68` `int img_dimensions_ok(uint32_t w, uint32_t h)`
- `img_fit` (function) `src/image_decode.c:76` `void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,
             double *out_w, do...`
- `premultiply` (function) `src/image_decode.c:90` `static void premultiply(uint8_t *data, size_t pixels)` -- void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h, double *out_w, double *out_h) { if (out_w == NULL...
- `img_decode_png` (function) `src/image_decode.c:102` `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)`
- `jpeg_error_longjmp` (function) `src/image_decode.c:158` `static void jpeg_error_longjmp(j_common_ptr cinfo)`
- `jpeg_silence` (function) `src/image_decode.c:164` `static void jpeg_silence(j_common_ptr cinfo)` -- libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG * fails closed (IMG_ERR_DECODE)...
- `img_decode_jpeg` (function) `src/image_decode.c:166` `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)`
- `gr_u8` (function) `src/image_decode.c:260` `static int gr_u8(gif_reader *r, uint8_t *out)`
- `gr_u16le` (function) `src/image_decode.c:266` `static int gr_u16le(gif_reader *r, uint16_t *out)`
- `gr_skip` (function) `src/image_decode.c:273` `static int gr_skip(gif_reader *r, size_t n)`
- `gr_skip_subblocks` (function) `src/image_decode.c:280` `static int gr_skip_subblocks(gif_reader *r)` -- static int gr_u16le(gif_reader *r, uint16_t *out) { if (r->pos + 2u > r->len) return 0; out =...
- `gb_next_code` (function) `src/image_decode.c:298` `static int gb_next_code(gif_bits *b, unsigned width, unsigned *out)`
- `gif_deinterlace_row` (function) `src/image_decode.c:319` `static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh)` -- } uint8_t byte; if (!gr_u8(b->r, &byte)) return 0; b->block_left--; b->acc |= (uint32_t)byte << b->nbits; b->nbits...
- `gif_put_pixel` (function) `src/image_decode.c:334` `static void gif_put_pixel(uint32_t *canvas, uint32_t cw, uint32_t ch,
                          u...` -- Writes one palette pixel into the canvas at frame-relative index i (clipped to * the canvas; transparent index ->...
- `img_decode_gif` (function) `src/image_decode.c:354` `img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out)`
- `img_decode_webp` (function) `src/image_decode.c:520` `img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out)`
- `img_decode` (function) `src/image_decode.c:553` `img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out)`
- `img_pixels_free` (function) `src/image_decode.c:566` `void img_pixels_free(img_pixels *p)`
- `img_format_name` (function) `src/image_decode.c:575` `const char *img_format_name(img_format f)`

## src/import_map.c
Depends on: `include/import_map.h`
- `ws` (function) `src/import_map.c:39` `static void ws(jr *r)`
- `eat` (function) `src/import_map.c:44` `static int eat(jr *r, char c)`
- `hex4` (function) `src/import_map.c:50` `static int hex4(const char *s, uint32_t *out)`
- `put_utf8` (function) `src/import_map.c:64` `static size_t put_utf8(char *o, uint32_t cp)`
- `str` (function) `src/import_map.c:78` `static char *str(jr *r)` -- A JSON string into an owned UTF-8 buffer (escapes decoded; a lone surrogate or a * raw control character is malformed).
- `skip` (function) `src/import_map.c:128` `static void skip(jr *r, int depth)` -- } n += put_utf8(o + n, cp);   /* <= the 6/12 escape bytes it replaces break; } default: goto fail; } } fail...
- `url_like` (function) `src/import_map.c:156` `static int url_like(const char *s)`
- `dup_s` (function) `src/import_map.c:168` `static char *dup_s(const char *s)`
- `clear` (function) `src/import_map.c:175` `static void clear(im_map *m)`
- `add` (function) `src/import_map.c:185` `static int add(im_map *m, int scope, const char *key, const char *addr, const char *doc_url,
    ...` -- if (d != NULL) memcpy(d, s, n + 1); return d; } static void clear(im_map *m) { for (size_t i = 0; i < m->n; ++i) {...
- `specifier_map` (function) `src/import_map.c:209` `static void specifier_map(jr *r, im_map *m, int scope, const char *doc_url,
                     ...` -- if (m->n == m->cap) { size_t nc = m->cap ? m->cap * 2 : 16; im_entry *g = (im_entry *)realloc(m->e, nc * sizeof *g)...
- `im_parse` (function) `src/import_map.c:225` `im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn resolve, void *ctx)`
- `match` (function) `src/import_map.c:272` `static int match(const im_map *m, int scope, const char *key, char *out, size_t outsz)` -- WHATWG "resolve an imports match" within one specifier map (scope).
- `im_resolve` (function) `src/import_map.c:301` `int im_resolve(const im_map *m, const char *base, const char *specifier,
               im_url_fn...`
- `im_count` (function) `src/import_map.c:339` `size_t im_count(const im_map *m)`
- `im_free` (function) `src/import_map.c:343` `void im_free(im_map *m)`

## src/interp.c
Depends on: `include/interp.h`
- `sample_bezier_x` (function) `src/interp.c:18` `static double sample_bezier_x(double t, double cx1, double cx2)`
- `sample_bezier_dx` (function) `src/interp.c:23` `static double sample_bezier_dx(double t, double cx1, double cx2)`
- `sample_bezier_y` (function) `src/interp.c:29` `static double sample_bezier_y(double t, double cy1, double cy2)`
- `solve_bezier_t` (function) `src/interp.c:35` `static double solve_bezier_t(double x, double cx1, double cx2)` -- } static double sample_bezier_dx(double t, double cx1, double cx2) { return 3.0 * cx1 * (1.0 - 4.0 * t + 3.0 * t *...
- `ip_ease` (function) `src/interp.c:55` `double ip_ease(double t, const ip_ease_fn *fn)`
- `ip_ease` (function) `src/interp.c:64` `case IP_EASE_EASE:
        return ip_ease(t, &(ip_ease_fn)`
- `ip_ease` (function) `src/interp.c:70` `case IP_EASE_EASE_IN:
        return ip_ease(t, &(ip_ease_fn)`
- `ip_ease` (function) `src/interp.c:76` `case IP_EASE_EASE_OUT:
        return ip_ease(t, &(ip_ease_fn)`
- `ip_ease` (function) `src/interp.c:82` `case IP_EASE_EASE_IN_OUT:
        return ip_ease(t, &(ip_ease_fn)`
- `ip_lerp` (function) `src/interp.c:134` `double ip_lerp(double a, double b, double t)`
- `ip_lerp_color` (function) `src/interp.c:139` `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t)`
- `ip_interp` (function) `src/interp.c:162` `double ip_interp(ip_val_kind kind, double a, double b, double t)`
- `ip_kf_interp` (function) `src/interp.c:175` `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf,
                    int n_kf, do...`
- `ip_anim_init` (function) `src/interp.c:196` `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease,
                  const ip_...`
- `anim_effective_dir_for` (function) `src/interp.c:222` `static int anim_effective_dir_for(const ip_anim *a, int iter)`
- `anim_effective_dir` (function) `src/interp.c:232` `static int anim_effective_dir(const ip_anim *a)`
- `ip_anim_tick` (function) `src/interp.c:236` `int ip_anim_tick(ip_anim *a, double dt_ms)`
- `ip_anim_current` (function) `src/interp.c:282` `double ip_anim_current(const ip_anim *a)`
- `ip_anim_done` (function) `src/interp.c:320` `int ip_anim_done(const ip_anim *a)`

## src/js_custom_elements.c
Depends on: `src/js_custom_elements.h`
- `jdce_install` (function) `src/js_custom_elements.c:199` `int jdce_install(JSContext *ctx)`

## src/js_custom_elements.h
Imported by: `src/js_custom_elements.c`, `src/js_dom.c`
- `jdce_install` (function) `src/js_custom_elements.h:9` `int jdce_install(JSContext *ctx);`


Next: [API_p9.md](API_p9.md)
