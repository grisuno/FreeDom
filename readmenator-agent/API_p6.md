# API (page 6 of 14)
Previous: [API_p5.md](API_p5.md)

## include/subreq_batch.h
Imported by: `src/subreq_batch.c`, `src/tab.c`, `tests/test_subreq_batch.c`
- `sqb_new` (function) `include/subreq_batch.h:37` `sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx);`
- `sqb_new_owned` (function) `include/subreq_batch.h:40` `sqb *sqb_new_owned(int max_threads, sqb_run_fn run, void *ctx, void (*free_ctx)(void *));` -- sqb_new whose ctx the batch OWNS: free_ctx(ctx) runs once the batch is freed AND every * abandoned request has...
- `sqb_abandon` (function) `include/subreq_batch.h:43` `void sqb_abandon(sqb *b);` -- Frees every finished job and ABANDONS every running one: its thread is detached, its result * is discarded when it...
- `sqb_submit` (function) `include/subreq_batch.h:47` `int sqb_submit(sqb *b, int refused, const sqb_req *req);` -- Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result count always equals...
- `sqb_count` (function) `include/subreq_batch.h:48` `size_t sqb_count(const sqb *b);`
- `sqb_wait_all` (function) `include/subreq_batch.h:50` `void sqb_wait_all(sqb *b);` -- Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result count always equals...
- `sqb_result` (function) `include/subreq_batch.h:52` `const sqb_res *sqb_result(const sqb *b, size_t i);` -- Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result count always equals...
- `sqb_wait_ready` (function) `include/subreq_batch.h:56` `size_t sqb_wait_ready(sqb *b, long wait_ms, size_t *idx, size_t cap);` -- Waits until every request finished or `wait_ms` elapsed (0 = do not wait), then writes the indices of EVERY finished...
- `sqb_remove` (function) `include/subreq_batch.h:59` `void sqb_remove(sqb *b, const size_t *idx, size_t k);` -- Joins and frees the jobs at the k ascending indices (unfinished or out-of-range ones are * skipped); the others keep...
- `sqb_reset` (function) `include/subreq_batch.h:61` `void sqb_reset(sqb *b);` -- Joins and frees the jobs at the k ascending indices (unfinished or out-of-range ones are * skipped); the others keep...
- `sqb_free` (function) `include/subreq_batch.h:64` `void sqb_free(sqb *b);` -- Abandons what is still running (sqb_abandon) and releases the batch; the memory goes when the * last abandoned...

## include/svg_paint.h
Depends on: `include/svg_render.h`
Imported by: `gui/browser_ui.c`, `src/svg_paint.c`, `src/svg_raster.c`
- `svp_draw` (function) `include/svg_paint.h:31` `void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, double h, int current_rgb);` -- Paints `img` into the rect [x, y, w, h] of `cr`, scaled uniformly and centred ("xMidYMid meet"). current_rgb is the...
- `way` (function) `include/svg_paint.h:35` `* worker rasterizes SVG images this way (spec/svg_raster.md section 3): drawing text * would open fontconfig, i.e....`

## include/svg_raster.h
Depends on: `include/image_decode.h`
Imported by: `fuzz/fuzz_image_decode.c`, `src/svg_raster.c`, `src/tab.c`, `tests/test_svg_raster.c`
- `sr_sniff` (function) `include/svg_raster.h:29` `int sr_sniff(const uint8_t *bytes, size_t len);` -- 1 when the first element of the document (after BOM, whitespace, the XML * declaration, comments and a doctype) is...

## include/svg_render.h
Imported by: `fuzz/fuzz_svg_render.c`, `gui/browser_ui.c`, `include/svg_paint.h`, `src/page_view.c`, `src/svg_raster.c`, `src/svg_render.c`, `tests/test_svg_render.c`
- `sv_fit` (function) `include/svg_render.h:131` `void sv_fit(const sv_image *img, double dw, double dh, double *scale, double *off_x, double *off_y);` -- Maps the image's user space onto the destination rect [dx, dy, dw, dh] the way a `preserveAspectRatio="xMidYMid...

## include/tab.h
Depends on: `include/freebug.h`, `include/js_geom.h`, `include/page_view.h`, `include/scroll_req.h`
Imported by: `gui/browser_ui.c`, `include/frame_host.h`, `src/freedom.c`, `src/tab.c`, `tests/test_frame_host.c`, `tests/test_tab.c`
- `tab_worker_dispatch` (function) `include/tab.h:176` `* Call tab_worker_dispatch(argc, argv) as the FIRST thing in main(): if argv is the * internal "--tab-worker <rfd>...`
- `tab_open` (function) `include/tab.h:180` `* and reaches tab_open (the app and the test harness) must call this first. */ void tab_worker_dispatch(int argc...`
- `tab_parse_worker_args` (function) `include/tab.h:187` `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd);` -- Pure validator of the worker handoff arguments (the security-relevant surface of the exec): returns nonzero and...
- `tab_prewarm` (function) `include/tab.h:196` `void tab_prewarm(void);` -- Starts one idle, confined worker in advance so the next tab_open does not wait for fork + exec + sandbox setup...
- `tab_prewarmed` (function) `include/tab.h:199` `int tab_prewarmed(void);` -- Starts one idle, confined worker in advance so the next tab_open does not wait for fork + exec + sandbox setup...
- `tab_prewarmed_pid` (function) `include/tab.h:202` `int tab_prewarmed_pid(void);` -- Starts one idle, confined worker in advance so the next tab_open does not wait for fork + exec + sandbox setup...
- `tab_shutdown_spare` (function) `include/tab.h:205` `void tab_shutdown_spare(void);` -- Starts one idle, confined worker in advance so the next tab_open does not wait for fork + exec + sandbox setup...
- `out_status` (function) `include/tab.h:213` `* On success return 0 and set *out_status (HTTP status), *out_body / *out_body_len * (malloc'd response bytes, tab...`
- `tab_set_fetcher` (function) `include/tab.h:224` `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx);` -- Installs the subresource fetcher used for XHR/fetch (NULL clears it: requests are then * refused). fn/ctx must...
- `tab_inflight_request_headers` (function) `include/tab.h:229` `const char *tab_inflight_request_headers(void);` -- Inside a tab_fetch_fn call: the request headers the page attached to this XHR/fetch, already filtered by...
- `tab_report_response_headers` (function) `include/tab.h:234` `void tab_report_response_headers(const char *lines);` -- Inside a tab_fetch_fn call: reports the response header lines ("name: value\n", no Set-Cookie) the page's XHR/fetch...
- `bytes` (function) `include/tab.h:238` `* so the parent can retain the bytes (spec/webfont.md b3b feeds them to the * @font-face loader as extern sheets)....`
- `tab_set_css_sink` (function) `include/tab.h:247` `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx);`
- `free_ctx` (function) `include/tab.h:254` `* free_ctx(ctx) (may be NULL) runs once the tab is closed AND its last abandoned request ended, * so the fetcher may...`
- `tab_set_net_allowed` (function) `include/tab.h:262` `void tab_set_net_allowed(tab *t, int allowed);` -- Grants/revokes page-JS network access (XMLHttpRequest/fetch) for the NEXT load.
- `none` (function) `include/tab.h:266` `* worker sent carries none (tab_page.unchanged) -- on a live page that is almost every tick. * The caller must then...`
- `tab_page_keep_view` (function) `include/tab.h:273` `void tab_page_keep_view(tab_page *prev, tab_page *next);` -- For a caller that replaces its page with each tick's: when `next` is unchanged, moves the * title, text and view of...
- `tab_set_op_net_budget_ms` (function) `include/tab.h:277` `void tab_set_op_net_budget_ms(tab *t, int ms);` -- Per-operation network time budget in ms for requests the worker issues AFTER the load * (default...
- `tab_async_fd` (function) `include/tab.h:282` `* the completion is signalled on tab_async_fd (readable). The pipe to the worker is a single * channel, so EVERY...`
- `tab_async_busy` (function) `include/tab.h:288` `int tab_async_busy(const tab *t);`
- `jar` (function) `include/tab.h:295` `* the trusted parent read from its ephemeral network jar (sf_cookie_header_for). Only * meaningful for a trusted...`
- `tab_set_cookies` (function) `include/tab.h:299` `void tab_set_cookies(tab *t, const char *cookies);` -- Seeds the page's document.cookie jar for the NEXT load with cookies ("name=value; ...") the trusted parent read from...
- `origin` (function) `include/tab.h:302` `* page origin (web_storage snapshot, copied). Used only when the load is trusted * (net granted);`
- `tab_set_storage` (function) `include/tab.h:304` `void tab_set_storage(tab *t, const char *blob, size_t len);` -- Seeds localStorage for the next load from the parent's in-memory store for the page origin (web_storage snapshot...
- `exclusively` (function) `include/tab.h:310` `* exclusively (tab_subreq_permitted). Default 0: zero fetches, Privacy by Default. */ void tab_set_css_allowed(tab...`
- `tab_set_viewport_w` (function) `include/tab.h:318` `void tab_set_viewport_w(tab *t, int px);` -- Sets the render viewport width (px) used to evaluate @media width queries on the NEXT load, so a responsive page...
- `load` (function) `include/tab.h:322` `* trusted load (net granted). */ void tab_set_frame_id(tab *t, int id);`
- `tab_set_identity` (function) `include/tab.h:328` `void tab_set_identity(tab *t, const char *serialized);` -- The user's identity override (idn_serialize text, spec/identity.md) for the NEXT loads: the worker applies it to...
- `tab_last_subreq_stats` (function) `include/tab.h:334` `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us);` -- Subresources the parent served for the LAST load (the worker's TAG_SUBREQ: XHR, fetch, external scripts, ES...
- `tab_subreq_permitted` (function) `include/tab.h:339` `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method);` -- Pure parent-side subresource gate (Zero Trust: decided from the PARENT's grants for this load, never the worker's...
- `view` (function) `include/tab.h:347` `* <noscript> handling in the built view (off => fallback shown, on => suppressed) * and is where allowlisted...`
- `string` (function) `include/tab.h:367` `* event_type is a JS event type string (e.g. "keydown", "input", "change"). * key is the keyboard key value (may be...`
- `granted` (function) `include/tab.h:416` `* granted (allow.conf AND js.conf);`
- `returned` (function) `include/tab.h:417` `* returned (the page keeps its zeros). The worker re-checks the same condition. * g must be finished (jg_finish). */...`
- `popstate` (function) `include/tab.h:423` `* popstate (+ hashchange) and re-derives the view like a click. */ tab_status tab_popstate(tab *t, int index...`
- `preorder` (function) `include/tab.h:428` `* preorder (out->nsub handles) followed by the elements after it, at most * ANC_MAX_HANDLES -- live DOM handles, the...`
- `one` (function) `include/tab.h:445` `* history entry with push_url instead of adding one (location.replace('#x'), a fragment * set while the document...`
- `tab_anchor_free` (function) `include/tab.h:450` `void tab_anchor_free(tab_anchor *a);`
- `decode` (function) `include/tab.h:468` `* could not decode (caller shows the placeholder), which is not a transport error. * TAB_ERR_* is reserved for...`
- `tab_alive` (function) `include/tab.h:481` `int tab_alive(const tab *t);` -- Same contract as tab_decode_image, for an inline data: URI image (RFC 2397 base64 variant): data_url slices the...
- `tab_child_pid` (function) `include/tab.h:484` `pid_t tab_child_pid(const tab *t);` -- Same contract as tab_decode_image, for an inline data: URI image (RFC 2397 base64 variant): data_url slices the...
- `tab_close` (function) `include/tab.h:487` `void tab_close(tab *t);` -- variant): data_url slices the base64 payload out of `data_url` (no allocation, no network -- the bytes are already...
- `tab_page_free` (function) `include/tab.h:490` `void tab_page_free(tab_page *p);` -- malformed data: URI is not a transport error: *out stays zeroed, same as an * undecodable format, and the caller...
- `tab_eval_result_free` (function) `include/tab.h:491` `void tab_eval_result_free(tab_eval_result *r);`
- `tab_image_free` (function) `include/tab.h:492` `void tab_image_free(tab_image *img);`

## include/table_layout.h
Imported by: `fuzz/fuzz_table_layout.c`, `gui/browser_ui.c`, `src/table_layout.c`, `tests/test_table_layout.c`
- `px` (function) `include/table_layout.h:41` `* px (< 0 = auto: the table is as wide as its content, capped at avail). gap is the space * between adjacent...`
- `tl_intrinsic` (function) `include/table_layout.h:53` `void tl_intrinsic(const tl_cell *cells, size_t n, size_t ncols, double gap, double *min_total, double *max_total);` -- The table's min-content and max-content widths (columns plus gaps): what it contributes when it is itself a cell of...

## include/text_case.h
Imported by: `fuzz/fuzz_text_case.c`, `gui/browser_ui.c`, `src/text_case.c`, `tests/test_text_case.c`
- `cp` (function) `include/text_case.h:19` `* cp (identity otherwise), so a transformed text keeps its length. */ uint32_t tc_upper(uint32_t cp);`
- `tc_lower` (function) `include/text_case.h:21` `uint32_t tc_lower(uint32_t cp);`
- `tc_is_lower` (function) `include/text_case.h:24` `int tc_is_lower(uint32_t cp);` -- Simple 1:1 case mapping for ASCII, Latin-1, Latin Extended-A, basic Greek and basic Cyrillic.
- `tc_transform` (function) `include/text_case.h:29` `size_t tc_transform(const char *s, size_t n, int transform, int word_start, char *out, size_t cap);` -- Copies s[0,n) to out applying transform (CSS_TT_UPPERCASE / _LOWERCASE / _CAPITALIZE; any other value copies...
- `tc_smallcaps_runs` (function) `include/text_case.h:41` `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap);` -- Splits s[0,n) into consecutive maximal runs of lowercase letters vs the rest, covering the whole text in order.

## include/text_shape.h
Imported by: `fuzz/fuzz_text_shape.c`, `fuzz/fuzz_webfont_register.c`, `gui/browser_ui.c`, `src/freedom.c`, `src/text_shape.c`, `src/webfont_load.c`, `tests/test_text_shape.c`, `tests/test_webfont_load.c`
- `content` (function) `include/text_shape.h:11` `* TEXT is hostile remote content (sanitised UTF-8) and is fuzzed (make fuzz-tsh);`
- `tsh_family_is_generic` (function) `include/text_shape.h:52` `int tsh_family_is_generic(const char *name);` -- 1 for a CSS generic family keyword (serif, sans-serif, monospace, cursive, * fantasy, system-ui, ui-*, emoji, math...
- `wins` (function) `include/text_shape.h:58` `* the first name the resolver accepts wins (returns 1, family in out). Pure: the * resolver is injected (fontconfig...`
- `tsh_pick_family` (function) `include/text_shape.h:68` `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong, size_t n, int...` -- The acceptance rule for one requested name given fontconfig's substituted family list subs[0..n) and their bindings...
- `tsh_local_handle` (function) `include/text_shape.h:75` `int tsh_local_handle(const char *list);` -- Handle (>0) for an author family list that resolves to a local family, cached per list; 0 when nothing resolves, the...
- `tsh_ready` (function) `include/text_shape.h:89` `int tsh_ready(void);` -- 1 once a fallback (sans) font resolves; lazily initialises on first call. * 0 means no font backend: the caller must...
- `origin` (function) `include/text_shape.h:92` `* glyphs are written with positions relative to origin (0,0) on the baseline, * and *out_adv holds the total pen...`
- `tsh_measure` (function) `include/text_shape.h:101` `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len);` -- Total advance (px) of [text,len).
- `tsh_webfont_register` (function) `include/text_shape.h:114` `int tsh_webfont_register(const char *name, const unsigned char *bytes, size_t nbytes, int bold, int italic);` -- Registers one fetched @font-face for this document (spec/webfont.md): name is the author family (hashed with...
- `tsh_face_generation` (function) `include/text_shape.h:122` `unsigned tsh_face_generation(void);` -- Advances whenever a face text is measured with may have been added, freed or replaced (a webfont registered or...
- `tsh_webfont_clear` (function) `include/text_shape.h:126` `void tsh_webfont_clear(void);` -- Drops every registered webfont (document teardown / navigation).
- `tsh_face` (function) `include/text_shape.h:133` `cairo_font_face_t *tsh_face(const tsh_font *f);` -- The cairo face tsh_draw paints f with (webfont, local family or bucket), or NULL when no face resolves.
- `own` (function) `include/text_shape.h:142` `* face of their own (controls, combining marks, variation selectors, ZWJ/ZWNJ) * stay in the run before them....`
- `tsh_shutdown` (function) `include/text_shape.h:149` `void tsh_shutdown(void);` -- Splits [text,len) into maximal runs of one face.

## include/textfield.h
Imported by: `gui/browser_ui.c`, `src/textfield.c`, `tests/test_textfield.c`
- `tf_init` (function) `include/textfield.h:38` `void tf_init(tf_field *f);` -- typedef struct tf_field { char   buf[TF_CAP]; /* content, always NUL-terminated at [len] size_t len;         /*...
- `tf_clear` (function) `include/textfield.h:45` `void tf_clear(tf_field *f);` -- Replaces the whole content and places the cursor at the end. s == NULL => * TF_ERR_NULL_ARG. strlen(s) >= TF_CAP =>...
- `tf_backspace` (function) `include/textfield.h:53` `void tf_backspace(tf_field *f);` -- Inserts one byte at the cursor, shifting the tail right; the cursor advances by one.
- `tf_delete` (function) `include/textfield.h:56` `void tf_delete(tf_field *f);` -- Inserts one byte at the cursor, shifting the tail right; the cursor advances by one.
- `tf_move` (function) `include/textfield.h:59` `void tf_move(tf_field *f, long delta);` -- Inserts one byte at the cursor, shifting the tail right; the cursor advances by one.
- `tf_home` (function) `include/textfield.h:62` `void tf_home(tf_field *f);` -- one.
- `tf_end` (function) `include/textfield.h:63` `void tf_end(tf_field *f);`
- `tf_text` (function) `include/textfield.h:66` `const char *tf_text(const tf_field *f);` -- /* Deletes the byte before the cursor (no-op at the start).
- `tf_len` (function) `include/textfield.h:67` `size_t tf_len(const tf_field *f);`
- `tf_cursor` (function) `include/textfield.h:68` `size_t tf_cursor(const tf_field *f);`

## include/tls_impersonate.h
Imported by: `fuzz/fuzz_tls_impersonate.c`, `gui/browser_ui.c`, `src/freedom.c`, `src/tls_impersonate.c`, `tests/test_tls_impersonate.c`
- `path` (function) `include/tls_impersonate.h:26` `* Zero Knowledge path (PQ-hybrid, VERIFYPEER). * * 2. ti_encode_x / ti_decode_x — the length-prefixed, fail-closed...`
- `chain` (function) `include/tls_impersonate.h:32` `* * The response carries the peer certificate chain (DER) and the negotiated group so * the TRUSTED PARENT...`
- `ti_should_impersonate` (function) `include/tls_impersonate.h:56` `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled, int user_opt_in);` -- The double opt-in + user-flag gate (pure).
- `success` (function) `include/tls_impersonate.h:97` `* ti_decode_* returns 0 on success (out fully populated), <0 on any malformed, * truncated or over-cap input (out...`
- `ti_decode_req` (function) `include/tls_impersonate.h:101` `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out);`
- `ti_req_free` (function) `include/tls_impersonate.h:102` `void ti_req_free(ti_req *r);`
- `ti_encode_resp` (function) `include/tls_impersonate.h:104` `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap);`
- `ti_decode_resp` (function) `include/tls_impersonate.h:105` `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out);`
- `ti_resp_free` (function) `include/tls_impersonate.h:106` `void ti_resp_free(ti_resp *r);`

## include/ui.h
Depends on: `include/prefs.h`
Imported by: `gui/browser_ui.c`, `gui/freedom_view.c`, `gui/ui_render.c`, `src/freedom.c`, `src/ui_layout.c`, `tests/test_ui.c`
- `space` (function) `include/ui.h:44` `* Breaks at the last fitting space (the break space is consumed), hard-breaks * words longer than max_cols, and...`
- `ui_layout_free` (function) `include/ui.h:52` `void ui_layout_free(ui_layout *lay);` -- Word-wraps text into lines of at most max_cols columns (monospace model).
- `ui_clamp_scroll` (function) `include/ui.h:55` `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines);` -- Word-wraps text into lines of at most max_cols columns (monospace model).
- `shortcut` (function) `include/ui.h:71` `* from a keyboard shortcut (Ctrl+Shift+E only relaxes a weak-but-valid certificate). */ void...`
- `available` (function) `include/ui.h:91` `* cheapest artifact to inspect a render where no display is available (CI, an AI * agent): export, then read the PNG...`
- `out` (function) `include/ui.h:103` `* ui_render_png does and fills *out (jg_init'ed by the caller) with one rect per * element in document coordinates...`
- `placeholders` (function) `include/ui.h:113` `* above always draw image placeholders (no worker to decode hostile bytes);`
- `disk` (function) `include/ui.h:118` `* images are read from disk (confined to the document directory by render_doc). * top_url is the page origin (https...`
- `images` (function) `include/ui.h:120` `* fetcher loads no images (placeholders, as before). Any image that fails falls back * to its placeholder...`
- `ui_render_viewport_w` (function) `include/ui.h:156` `int ui_render_viewport_w(void);` -- The fixed canvas width (px) every headless render (ui_render_png/pdf, ui_dump_layout) lays out at.
- `ui_persisted_prefs` (function) `include/ui.h:161` `int ui_persisted_prefs(prefs_state *out);` -- The GUI's persisted choices (JS mode, images/CSS toggles, reader) from the encrypted profile, so `--as-gui` shows...

## include/url.h
Imported by: `fuzz/fuzz_anchor.c`, `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_url.c`, `gui/browser_ui.c`, `include/form.h`, `include/js_dom.h`, `include/js_location.h`, `src/freedom.c`, `src/js_location.c`, `src/link_nav.c`, `src/prefetch.c`, `src/render_doc.c`, `src/secure_fetch.c`, `src/tab.c`, `src/url.c`, `src/webfont_load.c`, `tests/test_js_dom.c`, `tests/test_tab.c`, `tests/test_url.c`
- `url_is_https` (function) `include/url.h:42` `int url_is_https(const char *s);` -- Nonzero iff s begins (case-insensitively) with "https://" and the host is * neither empty nor a leading '/'.
- `url_has_scheme` (function) `include/url.h:46` `int url_has_scheme(const char *s);` -- Nonzero iff s begins with "<scheme>:" per RFC 3986 * (ALPHA *( ALPHA / DIGIT / "+" / "-" / "." ) ":").
- `url_authority_len` (function) `include/url.h:51` `size_t url_authority_len(const char *url);` -- Length of "https://host[:port]" within a validated absolute https URL: the index of the first '/', '?' or '#' after...
- `URL_ERR_NOT_HTTPS` (function) `include/url.h:109` `* URL_ERR_NOT_HTTPS (out untouched);`
- `path` (function) `include/url.h:115` `* absolute path ("file:///..."). NULL => 0. */ int url_is_file(const char *s);`
- `url_file_path` (function) `include/url.h:121` `const char *url_file_path(const char *s);` -- Returns the absolute filesystem path inside a "file:///path" URL (i.e. the "/path" part), or NULL when s is not a...
- `url` (function) `include/url.h:126` `* Every field ALIASES the input url (not owned, valid while url is alive);`
- `url_split` (function) `include/url.h:153` `* it for a network or storage decision: those take url_split (https-only). */ url_status url_split_location(const...`
- `password` (function) `include/url.h:159` `* username and password (owned, must be freed) into *username_out and * *password_out, and returns URL_OK. When...`

## include/util.h
Imported by: `src/browser.c`, `src/disk_store.c`, `src/dom.c`, `src/hostblock.c`, `src/html_parse.c`, `src/media_decoder.c`, `src/page_view.c`, `src/render_doc.c`, `src/renderer.c`, `src/tab.c`
- `write_full` (function) `include/util.h:15` `static inline int write_full(int fd, const void *buf, size_t n)`
- `read_full` (function) `include/util.h:26` `static inline int read_full(int fd, void *buf, size_t n)`
- `mem_contains_ci` (function) `include/util.h:43` `static inline int mem_contains_ci(const void *hay, size_t hlen, const char *needle)` -- Returns 1 when the trusted lowercase-ASCII needle (letters/digits) occurs in the hostile, length-delimited haystack...
- `utf8_seq_len` (function) `include/util.h:57` `static inline size_t utf8_seq_len(unsigned char c)`
- `fnv1a` (function) `include/util.h:67` `static inline uint64_t fnv1a(const char *s, size_t n)`

## include/video_controls.h
Depends on: `include/hls.h`
Imported by: `fuzz/fuzz_video_controls.c`, `gui/browser_ui.c`, `gui/browser_ui_internal.h`, `src/video_controls.c`, `tests/test_video_controls.c`
- `vcl_layout` (function) `include/video_controls.h:47` `int vcl_layout(double x, double y, double w, double h, vcl_geom *g);` -- Lays out the bar inside the video rect (x,y,w,h).
- `frac` (function) `include/video_controls.h:50` `* *frac (may be NULL) receives the track position for VCL_HIT_SEEK, else 0. */ vcl_hit_kind vcl_hit(const vcl_geom...`
- `vcl_seg_duration` (function) `include/video_controls.h:55` `double vcl_seg_duration(double d);` -- Classifies a pointer at (px,py). g may be NULL (no bar: the surface toggles). * *frac (may be NULL) receives the...
- `vcl_total` (function) `include/video_controls.h:58` `double vcl_total(const hls_playlist *pl);` -- Classifies a pointer at (px,py). g may be NULL (no bar: the surface toggles). * *frac (may be NULL) receives the...
- `start` (function) `include/video_controls.h:61` `* in *start (may be NULL). NULL/empty playlist => 0 and *start = 0. */ size_t vcl_segment_at(const hls_playlist *pl...`
- `vcl_segment_start` (function) `include/video_controls.h:65` `double vcl_segment_start(const hls_playlist *pl, size_t idx);` -- Index of the segment containing t (clamped to the playlist) and its start time * in *start (may be NULL).
- `vcl_position` (function) `include/video_controls.h:68` `double vcl_position(double base_s, int64_t pts0_us, int64_t pts_us, double total);` -- Index of the segment containing t (clamped to the playlist) and its start time * in *start (may be NULL).
- `vcl_clamp_frac` (function) `include/video_controls.h:71` `double vcl_clamp_frac(double f);` -- Index of the segment containing t (clamped to the playlist) and its start time * in *start (may be NULL).
- `vcl_format_time` (function) `include/video_controls.h:75` `size_t vcl_format_time(double seconds, char *buf, size_t cap);` -- Writes "m:ss" (or "h:mm:ss" from one hour) into buf; returns the length, or 0 * when buf is NULL/too small (buf then...

## include/video_pick.h
Depends on: `include/page_view.h`
Imported by: `gui/browser_ui.c`, `src/video_pick.c`, `tests/test_video_pick.c`
- `vpk_playable` (function) `include/video_pick.h:15` `int vpk_playable(const char *src);` -- 1 when src is an absolute http(s) URL with something after the scheme (the only * kind the decoder can fetch); 0 for...
- `vpk_first_video` (function) `include/video_pick.h:18` `const char *vpk_first_video(const pv_view *v);` -- 1 when src is an absolute http(s) URL with something after the scheme (the only * kind the decoder can fetch); 0 for...
- `vpk_for_frame` (function) `include/video_pick.h:23` `const char *vpk_for_frame(const pv_view *frame_view, const char *top_video);` -- Video for a click on a live frame's box: the frame's own first video, else top_video (the top document's first...

## include/web_storage.h
Imported by: `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_web_storage.c`, `gui/browser_ui.c`, `src/js_dom.c`, `src/js_trusted.c`, `src/tab.c`, `src/web_storage.c`, `tests/test_js_dom.c`, `tests/test_tab.c`, `tests/test_web_storage.c`
- `wst_new` (function) `include/web_storage.h:25` `wst_db *wst_new(void);` -- web_storage — in-MEMORY localStorage for trusted hosts (owner decision: nothing persists to disk).
- `wst_free` (function) `include/web_storage.h:28` `void wst_free(wst_db *db);` -- before it may touch the database.
- `wst_encode` (function) `include/web_storage.h:33` `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len);` -- Snapshot of origin's pairs ([n:u32]([klen:u32][key][vlen:u32][val])*, little-endian) into an owned *out of *len bytes.
- `wst_decode_check` (function) `include/web_storage.h:37` `int wst_decode_check(const char *blob, size_t len);` -- Pure validation of a snapshot: 0 when it is complete and well-formed (counts and * lengths fit, total <= WST_QUOTA...
- `wst_replace` (function) `include/web_storage.h:42` `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len);` -- Replaces origin's contents with the snapshot after wst_decode_check.
- `full` (function) `include/web_storage.h:45` `* validating it in full (wst_decode_check). Returns 0, or -1 when invalid (fn is then * never called). The one...`
- `wst_origin_bytes` (function) `include/web_storage.h:59` `size_t wst_origin_bytes(const wst_db *db, const char *origin);` -- Builds a snapshot from n pairs into an owned *out.

## include/webfont.h
Imported by: `fuzz/fuzz_webfont.c`, `fuzz/fuzz_webfont_register.c`, `gui/browser_ui.c`, `src/css.c`, `src/freedom.c`, `src/text_shape.c`, `src/webfont.c`, `src/webfont_load.c`, `tests/test_css.c`, `tests/test_page_view.c`, `tests/test_text_shape.c`, `tests/test_webfont.c`, `tests/test_webfont_load.c`
- `here` (function) `include/webfont.h:38` `* set with the decoded bytes owned here (freed by wf_list_free);`
- `wf_scan` (function) `include/webfont.h:52` `int wf_scan(const char *css, size_t len, wf_list *out);`
- `wf_list_free` (function) `include/webfont.h:53` `void wf_list_free(wf_list *l);`
- `boundaries` (function) `include/webfont.h:57` `* boundaries (scan_inline accumulation, loader collection). */ void wf_ref_move(wf_ref *dst, wf_ref *src);`
- `wf_supported_format` (function) `include/webfont.h:60` `int wf_supported_format(const char *fmt);`
- `wf_name_hash` (function) `include/webfont.h:69` `static inline unsigned wf_name_hash(const char *s, size_t n)` -- FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.

## include/webfont_load.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/webfont_load.c`, `tests/test_webfont_load.c`
- `free` (function) `include/webfont_load.h:31` `* free()), *out_status the HTTP status. Nonzero on refusal/error (fail-closed: * the face is skipped, never the...`
- `skipped` (function) `include/webfont_load.h:47` `* URLs are skipped (no base). Returns faces registered (>= 0) otherwise. */ int wf_load_document(wf_fetch_fn fetch...`

## include/wl_display.h
Imported by: `src/freedom.c`, `src/wl_display.c`, `tests/test_wl_display.c`
- `pure` (function) `include/wl_display.h:3` `* wd_pick is pure (no I/O);`
- `wd_pick` (function) `include/wl_display.h:16` `int wd_pick(const char *const *names, size_t n, char *out, size_t cap);` -- Choose the lowest-numbered "wayland-N" (N = digits only) from names[0..n).
- `wd_resolve_env` (function) `include/wl_display.h:20` `int wd_resolve_env(void);` -- If WAYLAND_DISPLAY is unset/empty, set it from the sockets found in XDG_RUNTIME_DIR. * Returns WD_OK if the variable...

## include/wl_guard.h
Imported by: `gui/browser_ui.c`, `src/wl_guard.c`, `tests/test_wl_guard.c`
- `wlg_start` (function) `include/wl_guard.h:25` `wl_guard *wlg_start(struct wl_display *display);` -- wl_guard -- keeps the Wayland connection drained while the GUI thread is busy.
- `wlg_stop` (function) `include/wl_guard.h:28` `void wlg_stop(wl_guard *g);` -- client that does not read for a few seconds while the pointer moves gets DISCONNECTED ("libwayland: Data too big for...

## include/ws_hub.h
Depends on: `include/secure_fetch.h`
Imported by: `gui/browser_ui.c`, `src/ws_hub.c`, `tests/test_ws_hub.c`
- `wh_new` (function) `include/ws_hub.h:34` `wh_hub *wh_new(void);` -- #define WH_MAX 8   /* == JD_WS_MAX: sockets per page /* Event kinds delivered to the page; values match...
- `wh_free` (function) `include/ws_hub.h:38` `void wh_free(wh_hub *h);` -- Closes every connection and frees the hub.
- `wh_notify_fd` (function) `include/ws_hub.h:41` `int wh_notify_fd(const wh_hub *h);` -- Closes every connection and frees the hub.
- `wh_open_async` (function) `include/ws_hub.h:46` `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg);` -- Starts opening url for page socket id on a thread (cfg and all its strings are copied).
- `generation` (function) `include/ws_hub.h:50` `* previous generation (before wh_close_all) are closed and dropped silently. */ void wh_on_notify(wh_hub *h...`
- `wh_send` (function) `include/ws_hub.h:54` `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary);` -- Drains finished opens: success => the connection joins the hub and WH_EV_OPEN is emitted; failure => WH_EV_ERROR...
- `wh_close` (function) `include/ws_hub.h:58` `void wh_close(wh_hub *h, int id);` -- The page closed socket id: sends a close frame and frees it (also cancels a * pending open for that id: its result...
- `wh_close_all` (function) `include/ws_hub.h:61` `void wh_close_all(wh_hub *h);` -- The page closed socket id: sends a close frame and frees it (also cancels a * pending open for that id: its result...
- `wh_poll_fds` (function) `include/ws_hub.h:65` `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap);` -- Fills up to cap pollfds (POLLIN) and the matching page ids for the open * connections.
- `wh_on_readable` (function) `include/ws_hub.h:70` `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx);` -- Reads everything pending on socket id without blocking, emitting each complete message; a close frame emits...
- `wh_count` (function) `include/ws_hub.h:73` `size_t wh_count(const wh_hub *h);` -- Reads everything pending on socket id without blocking, emitting each complete message; a close frame emits...

## include/zoom.h
Imported by: `gui/browser_ui.c`, `src/prefs.c`, `src/zoom.c`, `tests/test_prefs.c`, `tests/test_zoom.c`
- `zm_clamp` (function) `include/zoom.h:26` `int zm_clamp(int pct);` -- stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser.
- `zm_zoom_in` (function) `include/zoom.h:29` `int zm_zoom_in(int pct);` -- never escape the bounds.
- `zm_zoom_out` (function) `include/zoom.h:32` `int zm_zoom_out(int pct);` -- only calls these.
- `zm_reset` (function) `include/zoom.h:35` `int zm_reset(void);` -- #define ZM_MIN_PCT     50 #define ZM_MAX_PCT     300 #define ZM_DEFAULT_PCT 100 /* Clamp pct to [ZM_MIN_PCT...
- `zm_scale` (function) `include/zoom.h:38` `double zm_scale(int pct);` -- /* Clamp pct to [ZM_MIN_PCT, ZM_MAX_PCT]. int zm_clamp(int pct); /* Smallest ladder stop strictly greater than...
- `zm_apply` (function) `include/zoom.h:42` `double zm_apply(double base_px, int pct);` -- base_px * zm_scale(pct), floored to 1.0 when base_px > 0 so a font can never * scale away to nothing. base_px <= 0...

## src/anchor.c
Depends on: `include/anchor.h`
- `hex_val` (function) `src/anchor.c:8` `static int hex_val(int c)`
- `anc_percent_decode` (function) `src/anchor.c:15` `size_t anc_percent_decode(const char *in, char *out, size_t cap)`
- `first_named_a` (function) `src/anchor.c:35` `static dom_node_id first_named_a(const dom_index *idx, const char *name)` -- unsigned char b = (unsigned char)in[i]; if (b == '%') { int hi = hex_val((unsigned char)in[i + 1]); int lo = (hi >=...
- `potential_indicated` (function) `src/anchor.c:54` `static dom_node_id potential_indicated(const dom_index *idx, const char *s)` -- size_t n = dom_get_by_tag(idx, "a", ids, total); if (n > total) n = total; dom_node_id best = DOM_NODE_NONE; for...
- `is_top` (function) `src/anchor.c:59` `static int is_top(const char *s)`
- `anc_resolve` (function) `src/anchor.c:63` `anc_kind anc_resolve(const dom_index *idx, const char *fragment, dom_node_id *out)`
- `next_preorder` (function) `src/anchor.c:81` `static dom_node_id next_preorder(const dom_index *idx, dom_node_id cur, dom_node_id root,
       ...` -- if (len == 0) return ANC_TOP; dom_node_id t = potential_indicated(idx, fragment); if (t != DOM_NODE_NONE) { *out =...
- `anc_collect` (function) `src/anchor.c:93` `size_t anc_collect(const dom_index *idx, dom_node_id target, dom_node_id *out, size_t cap,
      ...`
- `anc_target_box` (function) `src/anchor.c:110` `int anc_target_box(const jg_table *g, const dom_node_id *h, size_t n, size_t nsub,
              ...`
- `anc_target_top` (function) `src/anchor.c:134` `int anc_target_top(const jg_table *g, const dom_node_id *h, size_t n, size_t nsub,
              ...`
- `anc_scroll_for` (function) `src/anchor.c:142` `double anc_scroll_for(double top, double max_scroll)`

## src/anti_fp.c
Depends on: `include/anti_fp.h`
- `fp_coarsen_time_ms` (function) `src/anti_fp.c:17` `uint64_t fp_coarsen_time_ms(uint64_t raw_ms)`
- `fp_user_agent` (function) `src/anti_fp.c:23` `const char *fp_user_agent(void)`
- `fp_accept_language` (function) `src/anti_fp.c:27` `const char *fp_accept_language(void)`
- `fp_accept_language_header` (function) `src/anti_fp.c:31` `const char *fp_accept_language_header(void)`
- `fp_timezone` (function) `src/anti_fp.c:35` `const char *fp_timezone(void)`
- `fp_platform` (function) `src/anti_fp.c:39` `const char *fp_platform(void)`
- `fp_vendor` (function) `src/anti_fp.c:43` `const char *fp_vendor(void)`
- `fp_hardware_concurrency` (function) `src/anti_fp.c:47` `int fp_hardware_concurrency(void)`
- `fp_device_memory_gb` (function) `src/anti_fp.c:51` `int fp_device_memory_gb(void)`
- `fp_app_version` (function) `src/anti_fp.c:57` `const char *fp_app_version(void)`
- `fp_app_code_name` (function) `src/anti_fp.c:61` `const char *fp_app_code_name(void)`
- `fp_product` (function) `src/anti_fp.c:65` `const char *fp_product(void)`
- `fp_app_name` (function) `src/anti_fp.c:69` `const char *fp_app_name(void)`
- `fp_product_sub` (function) `src/anti_fp.c:73` `const char *fp_product_sub(void)`
- `fp_oscpu` (function) `src/anti_fp.c:77` `const char *fp_oscpu(void)`
- `fp_build_id` (function) `src/anti_fp.c:81` `const char *fp_build_id(void)`
- `fp_max_touch_points` (function) `src/anti_fp.c:85` `int fp_max_touch_points(void)`
- `fp_on_line` (function) `src/anti_fp.c:89` `int fp_on_line(void)`
- `fp_cookie_enabled` (function) `src/anti_fp.c:93` `int fp_cookie_enabled(void)`
- `fp_bucket_screen` (function) `src/anti_fp.c:99` `void fp_bucket_screen(int w, int h, int *out_w, int *out_h)`
- `splitmix64` (function) `src/anti_fp.c:121` `static uint64_t splitmix64(uint64_t *state)`
- `fp_perturb` (function) `src/anti_fp.c:128` `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key)`
- `fp_origin_key` (function) `src/anti_fp.c:139` `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain)`

## src/block_flow.c
Depends on: `include/block_flow.h`
- `finite_or_zero` (function) `src/block_flow.c:11` `static double finite_or_zero(double v)` -- A margin the caller could not compute (NaN from a hostile calc(), an infinity from an overflowing unit conversion)...
- `bf_collapse_n` (function) `src/block_flow.c:15` `double bf_collapse_n(const double *m, size_t n)`
- `bf_collapse` (function) `src/block_flow.c:30` `double bf_collapse(double a, double b)`
- `bf_margins_adjoin` (function) `src/block_flow.c:35` `int bf_margins_adjoin(double border_px, double padding_px)`

## src/box_blur.c
Depends on: `include/box_blur.h`
- `bb_box_sizes` (function) `src/box_blur.c:8` `int bb_box_sizes(double sigma, int sizes[3])`
- `variance` (function) `src/box_blur.c:11` `* width w has variance (w^2 - 1) / 12): the ideal common width, rounded down * to an odd wl and up to wu = wl + 2...`
- `box_recip` (function) `src/box_blur.c:32` `static uint64_t box_recip(int bw)` -- floor((sum + bw/2) / bw) without a division: m = floor(2^32 / bw) + 1 makes (n * m) >> 32 exact for every n < 2^32 /...
- `box_avg` (function) `src/box_blur.c:33` `static unsigned char box_avg(long sum, int bw, uint64_t m)`
- `box_line` (function) `src/box_blur.c:39` `static void box_line(unsigned char *p, int n, int step, int bw, unsigned char *tmp)` -- One box pass of odd width bw over n samples spaced `step` apart, through tmp * (n bytes).
- `box_cols` (function) `src/box_blur.c:56` `static void box_cols(unsigned char *buf, int w, int h, int stride, int bw,
                     u...` -- One box pass of odd width bw down every column at once: the same running sums as box_line with step = stride, but...
- `bb_blur_a8` (function) `src/box_blur.c:82` `int bb_blur_a8(unsigned char *buf, int w, int h, int stride, double sigma)`
- `bb_ink_rect` (function) `src/box_blur.c:102` `int bb_ink_rect(const unsigned char *argb, int w, int h, int stride, double sigma, int rect[4])`

## src/box_style.c
Depends on: `include/box_style.h`
- `is_ws` (function) `src/box_style.c:31` `static int is_ws(char c)`
- `copy_lower_trim` (function) `src/box_style.c:37` `static int copy_lower_trim(const char *in, char *out, size_t out_size)` -- Copies in into out, trimming ASCII whitespace and lowercasing.
- `name_cmp` (function) `src/box_style.c:50` `static int name_cmp(const void *key, const void *elem)` -- Both row structs start with `const char *name`, so a pointer to a row is also a * pointer to its name field: one...
- `bx_default_for_tag` (function) `src/box_style.c:163` `bx_box bx_default_for_tag(const char *tag)`
- `bx_table_role_of` (function) `src/box_style.c:171` `bx_table_role bx_table_role_of(const char *tag, css_display display)`
- `bx_ua_of_tag` (function) `src/box_style.c:210` `bx_ua_tag bx_ua_of_tag(const char *tag)`
- `bx_default_for_ua` (function) `src/box_style.c:219` `bx_box bx_default_for_ua(bx_ua_tag id)`
- `bx_block_ua_box` (function) `src/box_style.c:225` `bx_box bx_block_ua_box(int heading_level, int in_list, bx_ua_tag ua)`
- `bx_parse_display` (function) `src/box_style.c:261` `bx_status bx_parse_display(const char *token, bx_display *out)`
- `bx_place` (function) `src/box_style.c:271` `bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,
                ...`
- `bx_width_cap` (function) `src/box_style.c:288` `double bx_width_cap(int w_px, int w_pct, double avail_w)`
- `take` (function) `src/box_style.c:295` `* caller has to take (Sizing 3 section 5.1), so to a resolver that only sums a * px and a percentage half they read...`
- `bx_width_cap2` (function) `src/box_style.c:313` `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w)`
- `bx_replaced_box` (function) `src/box_style.c:321` `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den,
                    doub...`
- `bx_border_box_h` (function) `src/box_style.c:335` `double bx_border_box_h(double declared_h, int border_box,
                       double pad_t, do...`
- `bx_pct_block_size` (function) `src/box_style.c:346` `double bx_pct_block_size(int px_val, int pct_pm, double cb_h)`
- `bx_definite_content_h` (function) `src/box_style.c:352` `double bx_definite_content_h(double h, double min_h, double max_h,
                             i...`
- `bx_content_clipped` (function) `src/box_style.c:361` `int bx_content_clipped(int overflow_x, int overflow_y)`
- `bx_lp_px` (function) `src/box_style.c:367` `double bx_lp_px(int px_val, int pct_pm, double basis)`
- `bx_content_cap` (function) `src/box_style.c:378` `double bx_content_cap(double width_cap, int border_box,
                      double pad_l, doubl...`
- `bx_flex_min_clamp` (function) `src/box_style.c:389` `double bx_flex_min_clamp(double outer_basis, double min_w, int border_box,
                      ...`
- `bx_border_span` (function) `src/box_style.c:396` `double bx_border_span(double width_cap, int border_box,
                      double pad_l, doubl...`
- `bg_size_component` (function) `src/box_style.c:408` `static double bg_size_component(int px_val, int pct_pm, double area)` -- One background-size component in px, or -1 when it is `auto` (Backgrounds 3 section 3.9).
- `bx_background_layer` (function) `src/box_style.c:415` `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h,
                    ...`
- `bx_display_name` (function) `src/box_style.c:454` `const char *bx_display_name(bx_display d)`
- `bx_flex_max_clamp` (function) `src/box_style.c:467` `double bx_flex_max_clamp(double outer_basis, double mw_cap, int border_box,
                     ...`
- `bx_place_ex` (function) `src/box_style.c:474` `bx_hplace bx_place_ex(double inset_l, double inset_r, double width_cap, int center,
             ...`
- `bx_line_height_px` (function) `src/box_style.c:484` `double bx_line_height_px(int line_scale, double font_px)`

## src/box_tree.c
Depends on: `include/box_style.h`, `include/box_tree.h`, `include/compositor.h`, `include/css.h`
- `layout_block` (function) `src/box_tree.c:40` `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,
                   ...` -- Block container: stack non-none children vertically, collapsing each child's top * margin with the previous child's...
- `bt_nn` (function) `src/box_tree.c:61` `static double bt_nn(double v)` -- if (cavail < 0.0) cavail = 0.0; bt_status r = layout_node(c, cavail, depth + 1); if (r != BT_OK) return r; double...
- `height` (function) `src/box_tree.c:81` `* exactly that height (Flexbox 9.4 step 15).
 *
 * wrap_reverse (node->wrap_reverse): when node->...`
- `layout_flex` (function) `src/box_tree.c:101` `static bt_status layout_flex(bt_node *node, bt_node *const *kids, size_t nk,
                    ...`
- `layout_grid` (function) `src/box_tree.c:283` `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,
                    ...`
- `sized` (function) `src/box_tree.c:353` `* the tracks are sized (CSS Grid 1 11.5, items spanning several tracks come * last);`
- `layout_node` (function) `src/box_tree.c:423` `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)`
- `bt_layout` (function) `src/box_tree.c:468` `bt_status bt_layout(bt_node *root, double avail_w)`
- `assign_doc_order` (function) `src/box_tree.c:508` `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,
                  ...` -- Recursive doc_order assignment.
- `find_positioned_ancestor` (function) `src/box_tree.c:525` `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,
                       ...` -- Walk the parent_id chain from `start` to find the nearest ancestor with position != STATIC.
- `resolve_inset` (function) `src/box_tree.c:545` `static double resolve_inset(int v, int pct_pm, double basis)` -- Resolves an inset <length-percentage>: PV_LEN_UNSET or BT_LEN_AUTO with no percentage half → 0 (anchor at the...
- `inset_unset` (function) `src/box_tree.c:554` `static int inset_unset(int v, int pct_pm)` -- Stage 2b: an inset axis the author left undeclared (UNSET) or `auto`.
- `bt_containing_block` (function) `src/box_tree.c:558` `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i,
                        ...`
- `block` (function) `src/box_tree.c:569` `* true block (same flow neighbourhood), strictly better than zeros. NULL
     * placed keeps lega...`
- `bt_resolve_positioning` (function) `src/box_tree.c:588` `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,
                          ...`
- `sc_forms` (function) `src/box_tree.c:616` `static int sc_forms(const pv_box_def *b)`
- `sc_chain_compare` (function) `src/box_tree.c:629` `static int sc_chain_compare(const sc_chain *a, const sc_chain *b, const cx_item *by_ref)`
- `nest_in_contexts` (function) `src/box_tree.c:638` `static void nest_in_contexts(const pv_box_def *boxes, size_t nbox, const bt_positioned *tmp,
    ...`
- `bt_resolve_positioning_ex` (function) `src/box_tree.c:706` `bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,
                       ...`
- `oof_walk` (function) `src/box_tree.c:862` `static int oof_walk(const pv_box_def *boxes, size_t nbox, int bid, int nearest)` -- Shared walk for the Stage 2d classifiers: nearest==1 stops at the first * ABSOLUTE/FIXED box, nearest==0 remembers...
- `bt_oof_anchor` (function) `src/box_tree.c:879` `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)`
- `bt_oof_root` (function) `src/box_tree.c:883` `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)`
- `bt_box_hidden` (function) `src/box_tree.c:887` `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)`
- `bt_in_subtree` (function) `src/box_tree.c:900` `int bt_in_subtree(const pv_box_def *boxes, size_t nbox, size_t root, size_t bid)`
- `bt_oof_avail` (function) `src/box_tree.c:911` `double bt_oof_avail(int a, int a_pct, int b, int b_pct, double cb, int *both)`
- `bt_defer_roots` (function) `src/box_tree.c:919` `size_t bt_defer_roots(const pv_box_def *boxes, size_t nbox,
                      const bt_positi...`

## src/browser.c
Depends on: `include/browser.h`, `include/util.h`
- `free_page` (function) `src/browser.c:16` `static void free_page(browser_state *bs)`
- `clear_status` (function) `src/browser.c:26` `static void clear_status(browser_state *bs)` -- #include <stdlib.h> #include <math.h> #include <string.h> static void free_page(browser_state *bs) { if (bs == NULL)...
- `free_history` (function) `src/browser.c:31` `static void free_history(browser_state *bs)`
- `free_stash` (function) `src/browser.c:47` `static void free_stash(browser_state *bs)`
- `free_pending` (function) `src/browser.c:59` `static void free_pending(browser_state *bs)` -- enum { PENDING_NONE = 0, PENDING_NEW = 1, PENDING_MOVE = 2 }; static void free_stash(browser_state *bs) { for...
- `begin_pending` (function) `src/browser.c:72` `static void begin_pending(browser_state *bs, int kind)` -- Opens a pending navigation of kind: the committed position and page are saved * (the page moves, it is not copied)...
- `free_exceptions` (function) `src/browser.c:83` `static void free_exceptions(browser_state *bs)`
- `is_https_url` (function) `src/browser.c:92` `static int is_https_url(const char *s)`
- `is_local_path` (function) `src/browser.c:96` `static int is_local_path(const char *s)`
- `url_is_allowed` (function) `src/browser.c:101` `static int url_is_allowed(const char *url)`
- `xstrdup` (function) `src/browser.c:115` `static char *xstrdup(const char *s)`
- `cp1252_to_ucs` (function) `src/browser.c:129` `static unsigned int cp1252_to_ucs(unsigned char c)` -- Unicode scalar for a Windows-1252 byte (only meaningful for c >= 0x80).
- `utf8_encode` (function) `src/browser.c:143` `static size_t utf8_encode(unsigned int cp, char *out)` -- Encodes a BMP scalar (<= 0xFFFF) as UTF-8 into out (up to 3 bytes); returns the * byte count written.
- `browser_init` (function) `src/browser.c:197` `browser_status browser_init(browser_state *bs)`
- `browser_free` (function) `src/browser.c:208` `void browser_free(browser_state *bs)`
- `browser_set_url_bar` (function) `src/browser.c:220` `browser_status browser_set_url_bar(browser_state *bs, const char *url)`
- `browser_commit_url_bar` (function) `src/browser.c:232` `browser_status browser_commit_url_bar(browser_state *bs)`
- `browser_navigate` (function) `src/browser.c:288` `browser_status browser_navigate(browser_state *bs, const char *url)`
- `browser_push_state` (function) `src/browser.c:320` `browser_status browser_push_state(browser_state *bs, const char *url)`
- `browser_replace_state` (function) `src/browser.c:328` `browser_status browser_replace_state(browser_state *bs, const char *url)`
- `browser_set_entry_scroll` (function) `src/browser.c:341` `void browser_set_entry_scroll(browser_state *bs, double scroll)`
- `browser_entry_scroll` (function) `src/browser.c:346` `double browser_entry_scroll(const browser_state *bs)`
- `browser_entry_doc` (function) `src/browser.c:351` `int browser_entry_doc(const browser_state *bs, size_t pos)`
- `browser_doc_index` (function) `src/browser.c:356` `int browser_doc_index(const browser_state *bs)`
- `browser_back` (function) `src/browser.c:364` `browser_status browser_back(browser_state *bs)`
- `browser_forward` (function) `src/browser.c:377` `browser_status browser_forward(browser_state *bs)`
- `browser_can_back` (function) `src/browser.c:390` `int browser_can_back(const browser_state *bs)`
- `browser_can_forward` (function) `src/browser.c:394` `int browser_can_forward(const browser_state *bs)`
- `browser_current_url` (function) `src/browser.c:398` `const char *browser_current_url(const browser_state *bs)`
- `browser_url_bar_selection` (function) `src/browser.c:403` `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)`
- `browser_url_bar_delete_selection` (function) `src/browser.c:414` `int browser_url_bar_delete_selection(browser_state *bs)`
- `browser_url_bar_insert` (function) `src/browser.c:424` `browser_status browser_url_bar_insert(browser_state *bs, char c)`
- `browser_url_bar_backspace` (function) `src/browser.c:439` `browser_status browser_url_bar_backspace(browser_state *bs)`
- `browser_url_bar_delete` (function) `src/browser.c:453` `browser_status browser_url_bar_delete(browser_state *bs)`
- `browser_url_bar_move_cursor` (function) `src/browser.c:464` `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)`
- `browser_url_bar_extend_cursor` (function) `src/browser.c:474` `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)`
- `browser_url_bar_set_cursor` (function) `src/browser.c:483` `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)`
- `browser_url_bar_select_all` (function) `src/browser.c:491` `browser_status browser_url_bar_select_all(browser_state *bs)`
- `browser_url_bar_clear` (function) `src/browser.c:498` `browser_status browser_url_bar_clear(browser_state *bs)`
- `browser_set_page` (function) `src/browser.c:507` `browser_status browser_set_page(browser_state *bs, const char *title,
                           ...`
- `browser_set_status` (function) `src/browser.c:529` `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)`
- `browser_status_text` (function) `src/browser.c:543` `const char *browser_status_text(const browser_state *bs, uint64_t now_ms)`
- `host_equal` (function) `src/browser.c:551` `static int host_equal(const char *a, const char *b)`
- `browser_is_exception` (function) `src/browser.c:562` `int browser_is_exception(const browser_state *bs, const char *host)`
- `browser_add_exception` (function) `src/browser.c:570` `browser_status browser_add_exception(browser_state *bs, const char *host)`
- `browser_closed_push` (function) `src/browser.c:588` `browser_status browser_closed_push(browser_closed *c, const char *url)`
- `browser_closed_pop` (function) `src/browser.c:603` `int browser_closed_pop(browser_closed *c, char *out, size_t cap)`
- `browser_commit_pending` (function) `src/browser.c:615` `void browser_commit_pending(browser_state *bs)`
- `browser_abort_pending` (function) `src/browser.c:620` `int browser_abort_pending(browser_state *bs)`
- `browser_has_pending` (function) `src/browser.c:650` `int browser_has_pending(const browser_state *bs)`

## src/cached_fetch.c
Depends on: `include/cached_fetch.h`
- `trace` (function) `src/cached_fetch.c:18` `static void trace(const char *what, const char *url)` -- fetcher, and so the same policy, as an uncached request.  #define _POSIX_C_SOURCE 200809L #include "cached_fetch.h"...
- `cf_set_store` (function) `src/cached_fetch.c:22` `void cf_set_store(hc_store *store)`
- `cf_store` (function) `src/cached_fetch.c:23` `hc_store *cf_store(void)`
- `cacheable_request` (function) `src/cached_fetch.c:26` `static int cacheable_request(const sf_config *cfg, const char *url)` -- #include <stdlib.h> #include <string.h> static hc_store *g_store; /* FREEDOM_TRACE_FETCH=1: one line per cache...
- `copy_val` (function) `src/cached_fetch.c:33` `static void copy_val(char *dst, size_t cap, const char *src)`
- `meta_from_response` (function) `src/cached_fetch.c:40` `static void meta_from_response(hc_meta *m, const sf_response *r, const char *url, time_t now)`
- `response_from_cache` (function) `src/cached_fetch.c:53` `static int response_from_cache(sf_response *out, const hc_meta *m, uint8_t *body, size_t len)` -- static void meta_from_response(hc_meta *m, const sf_response *r, const char *url, time_t now) { memset(m, 0, sizeof...
- `remember` (function) `src/cached_fetch.c:77` `static void remember(hc_store *store, const char *partition, const char *url,
                   ...`
- `cf_get_with` (function) `src/cached_fetch.c:85` `sf_status cf_get_with(hc_store *store, cf_fetch_fn fetch, const char *partition, const char *url,...`
- `cf_get` (function) `src/cached_fetch.c:133` `sf_status cf_get(const char *partition, const char *url, sf_config *cfg, sf_response *out,
      ...`
- `redirect_load` (function) `src/cached_fetch.c:140` `static int redirect_load(void *ctx, const char *from, time_t now, char *out, size_t cap)` -- } trace("miss", url); sf_status st = fetch(url, cfg, out, downgraded, allowlisted); if (st == SF_OK) remember(store...
- `redirect_save` (function) `src/cached_fetch.c:144` `static void redirect_save(void *ctx, const char *from, const char *to, time_t now)`
- `cf_attach_redirect_memory` (function) `src/cached_fetch.c:148` `void cf_attach_redirect_memory(hc_store *store)`

## src/chrome_layout.c
Depends on: `include/chrome_layout.h`
- `rect` (function) `src/chrome_layout.c:17` `static chl_rect rect(double x, double y, double w, double h)`
- `chl_rect_has` (function) `src/chrome_layout.c:26` `int chl_rect_has(chl_rect r, double x, double y)`
- `chl_compute` (function) `src/chrome_layout.c:30` `chl_status chl_compute(double width, int csd, int tab_count, int active, chl_layout *out)`
- `chl_tab_rect` (function) `src/chrome_layout.c:115` `int chl_tab_rect(const chl_layout *l, int i, chl_rect *r)`
- `chl_tab_close_rect` (function) `src/chrome_layout.c:125` `int chl_tab_close_rect(const chl_layout *l, int i, chl_rect *r)`
- `chl_hit` (function) `src/chrome_layout.c:135` `chl_part chl_hit(const chl_layout *l, double x, double y, int *tab)`
- `chl_tab_drop_index` (function) `src/chrome_layout.c:169` `int chl_tab_drop_index(const chl_layout *l, double x)`
- `chl_move_index` (function) `src/chrome_layout.c:179` `int chl_move_index(int i, int from, int to)`
- `chl_tab_for_digit` (function) `src/chrome_layout.c:186` `int chl_tab_for_digit(int digit, int tab_count)`
- `lower` (function) `src/chrome_layout.c:194` `static int lower(int c)`
- `has_prefix_ci` (function) `src/chrome_layout.c:197` `static int has_prefix_ci(const char *s, const char *prefix)` -- return i; } int chl_tab_for_digit(int digit, int tab_count) { if (tab_count < 1 || digit < 1 || digit > 9) return...
- `host_ends_with` (function) `src/chrome_layout.c:204` `static int host_ends_with(const char *h, size_t n, const char *suffix)` -- } /* --- identity badge --- static int lower(int c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; } /* 1 if...
- `url_host` (function) `src/chrome_layout.c:214` `static size_t url_host(const char *rest, const char **out)` -- Host of an authority-bearing URL after "scheme://": userinfo, port and one trailing * dot removed.
- `chl_identity_of` (function) `src/chrome_layout.c:232` `chl_identity chl_identity_of(const char *url, int transport_known, int downgrade,
               ...`
- `chl_identity_label` (function) `src/chrome_layout.c:256` `const char *chl_identity_label(chl_identity id)`
- `chl_findbar_compute` (function) `src/chrome_layout.c:273` `chl_status chl_findbar_compute(double width, double height, chl_findbar *out)` -- Find bar: the field at the left, prev/next right after it, the match count, and the * close button at the right edge.
- `chl_findbar_hit` (function) `src/chrome_layout.c:309` `chl_find_part chl_findbar_hit(const chl_findbar *f, double x, double y)`
- `chl_tab_fallback_title` (function) `src/chrome_layout.c:321` `void chl_tab_fallback_title(const char *url, char *out, size_t cap)`


Next: [API_p7.md](API_p7.md)
