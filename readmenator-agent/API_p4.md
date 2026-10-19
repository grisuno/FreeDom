# API (page 4 of 10)
Previous: [API_p3.md](API_p3.md)

## include/freebug.h
Imported by: `fuzz/fuzz_freebug.c`, `gui/browser_ui.c`, `include/js_dom.h`, `include/tab.h`, `src/freebug.c`, `src/freedom.c`, `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/tab.c`, `tests/test_freebug.c`
- `fb_buffer_init` (function) `include/freebug.h:65` `void fb_buffer_init(fb_buffer *b);` -- A stored source name is truncated to this many bytes (NUL excluded).
- `truncated` (function) `include/freebug.h:69` `* A message longer than FB_MAX_ENTRY_BYTES is stored truncated (not dropped). A * dropped push raises b->overflow...`
- `copied` (function) `include/freebug.h:75` `* copied (truncated to FB_MAX_FILE_BYTES);`
- `fb_buffer_push_loc` (function) `include/freebug.h:78` `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len, const char *file, int line, int col);` -- As fb_buffer_push, but also records a source location. file (may be NULL) is copied (truncated to...
- `fb_buffer_reset` (function) `include/freebug.h:83` `void fb_buffer_reset(fb_buffer *b);` -- Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the * entry array allocation for reuse.
- `fb_buffer_free` (function) `include/freebug.h:86` `void fb_buffer_free(fb_buffer *b);` -- Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the * entry array allocation for reuse.
- `fb_buffer_count` (function) `include/freebug.h:89` `size_t fb_buffer_count(const fb_buffer *b);` -- Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the * entry array allocation for reuse.
- `fb_buffer_at` (function) `include/freebug.h:92` `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i);` -- Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the * entry array allocation for reuse.
- `fb_level_name` (function) `include/freebug.h:96` `const char *fb_level_name(int level);` -- A stable lowercase level name ("log"/"info"/"warn"/"error"/"debug"); an * out-of-range level clamps to "log".

## include/hls.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/hls.c`, `tests/test_hls.c`
- `hls_select_variant` (function) `include/hls.h:65` `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h);` -- Selects the best variant from a multi-variant playlist.
- `resolved` (function) `include/hls.h:68` `* Writes the absolute URL into resolved (bounded by resolved_sz). Returns the * written length, or 0 on failure. */...`
- `hls_playlist_free` (function) `include/hls.h:74` `void hls_playlist_free(hls_playlist *pl);` -- Resolves a (possibly relative) segment URL against the playlist base URL.

## include/hostblock.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/hostblock.c`, `tests/test_hostblock.c`
- `hb_new` (function) `include/hostblock.h:49` `hb_set *hb_new(void);` -- } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on...
- `hb_free` (function) `include/hostblock.h:52` `void hb_free(hb_set *s);` -- HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) }...
- `walked` (function) `include/hostblock.h:65` `* walked (the host, then without its first label, ...): any suffix on the allowlist * => HB_ALLOW (allow wins...`
- `hb_is_allowlisted` (function) `include/hostblock.h:75` `int hb_is_allowlisted(const hb_set *s, const char *host);` -- 1 iff a domain suffix of host is explicitly on the allowlist (covers subdomains), else 0.
- `hb_count` (function) `include/hostblock.h:79` `size_t hb_count(const hb_set *s, hb_list list);` -- Number of unique domains on the given list (for tests/diagnostics).

## include/hostedit.h
Imported by: `gui/browser_ui.c`, `src/hostedit.c`, `tests/test_hostedit.c`
- `he_text_has_host` (function) `include/hostedit.h:46` `int he_text_has_host(const char *text, const char *host);` -- Returns 1 if text (the body of a hosts-format file) already lists host as a domain token on a non-comment line...
- `he_suggest` (function) `include/hostedit.h:55` `int he_suggest(const char *text, const char *query, char results[][HE_MAX_HOST + 1], int max);` -- Omnibar autocomplete: treats allow.conf (a hosts-format text) as a favorites list.

## include/html_parse.h
Imported by: `fuzz/fuzz_dom.c`, `fuzz/fuzz_dom_debug.c`, `fuzz/fuzz_html_parse.c`, `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_page_view.c`, `gui/freedom_view.c`, `include/dom.h`, `include/page_view.h`, `src/dom.c`, `src/freedom.c`, `src/html_parse.c`, `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/page_view.c`, `src/renderer.c`, `src/tab.c`, `tests/test_dom.c`, `tests/test_html_parse.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_page_view.c`
- `dropped` (function) `include/html_parse.h:47` `* dropped (not executed). */ #define HP_MAX_SCRIPTS ((size_t)4096) /* Returns a configuration with the secure...`
- `cfg` (function) `include/html_parse.h:57` `* policy in cfg (cfg == NULL => secure defaults). No script is ever executed. * html == NULL or out == NULL =>...`
- `hp_element_count` (function) `include/html_parse.h:63` `size_t hp_element_count(const hp_document *doc);` -- Parses untrusted HTML into an inert document and applies the sanitisation policy in cfg (cfg == NULL => secure...
- `hp_script_count` (function) `include/html_parse.h:64` `size_t hp_script_count(const hp_document *doc);`
- `hp_event_handler_count` (function) `include/html_parse.h:65` `size_t hp_event_handler_count(const hp_document *doc);`
- `hp_extract_text` (function) `include/html_parse.h:69` `char *hp_extract_text(const hp_document *doc, size_t *out_len);` -- Owned, NUL-terminated buffers; release with hp_free. *out_len (optional) * excludes the trailing NUL.
- `hp_get_title` (function) `include/html_parse.h:70` `char *hp_get_title(const hp_document *doc, size_t *out_len);`
- `src` (function) `include/html_parse.h:90` `* carry their raw src (a <script src> with an inline body lists ONLY the src -- * browser rule: when src is present...`
- `modules` (function) `include/html_parse.h:94` `* ES modules (import/export cannot run as a classic script), and template blocks * (text/x-jquery-tmpl, text/html...`
- `hp_free_scripts` (function) `include/html_parse.h:111` `void hp_free_scripts(hp_script *scripts, size_t count);` -- Releases an array returned by hp_extract_script_list (each text/src and the * array).
- `hp_extract_stylesheet_hrefs` (function) `include/html_parse.h:127` `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count);` -- Returns the RAW href of every applicable <link rel=stylesheet>, in document order, as an owned array of...
- `hp_free_stylesheet_hrefs` (function) `include/html_parse.h:130` `void hp_free_stylesheet_hrefs(char **hrefs, size_t count);` -- Returns the RAW href of every applicable <link rel=stylesheet>, in document order, as an owned array of...
- `hp_free` (function) `include/html_parse.h:133` `void hp_free(char *buf);` -- number found.
- `hp_document_free` (function) `include/html_parse.h:136` `void hp_document_free(hp_document *doc);` -- (ASCII case-insensitive) and NOT the token "alternate"; href is present and non-empty; and media is absent/empty or...
- `hp_document_root` (function) `include/html_parse.h:142` `const void *hp_document_root(const hp_document *doc);` -- Internal seam for the dom layer: returns the document's root node as an opaque handle (so html_parse.h stays free of...

## include/image_decode.h
Imported by: `fuzz/fuzz_image_decode.c`, `gui/browser_ui.c`, `src/image_decode.c`, `src/tab.c`, `tests/test_freedom.c`, `tests/test_image_decode.c`
- `guards` (function) `include/image_decode.h:25` `* guards (in-memory source only, longjmp error manager so a bad stream never * calls exit(), dimension caps before...`
- `img_dimensions_ok` (function) `include/image_decode.h:78` `int img_dimensions_ok(uint32_t w, uint32_t h);` -- 1 iff (w,h) is non-zero and fits the anti-DoS caps (per-side and area, no * overflow of width*height*4); 0 otherwise.
- `inputs` (function) `include/image_decode.h:81` `* Degenerate inputs (<= 0) yield (0,0). Pure. */ void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h...`
- `decode` (function) `include/image_decode.h:92` `* the declared dimensions BEFORE the full decode (anti-bomb), decodes to RGB and * expands to BGRA. Rejects non-JPEG...`
- `img_pixels_free` (function) `include/image_decode.h:121` `void img_pixels_free(img_pixels *p);` -- Releases data and zeroes the struct.
- `img_format_name` (function) `include/image_decode.h:124` `const char *img_format_name(img_format f);` -- Releases data and zeroes the struct.

## include/import_map.h
Imported by: `fuzz/fuzz_import_map.c`, `src/import_map.c`, `src/prefetch.c`, `src/tab.c`, `tests/test_import_map.c`
- `algorithm` (function) `include/import_map.h:13` `* resolution algorithm (scopes, exact and prefix matches). URL resolution is the * caller's (the same resolver the...`
- `map` (function) `include/import_map.h:28` `* map (fail closed = no mapping). NULL only on OOM. */ im_map *im_parse(const char *json, size_t len, const char...`
- `im_resolve` (function) `include/import_map.h:33` `int im_resolve(const im_map *m, const char *base, const char *specifier, im_url_fn resolve, void *ctx, char *out...` -- Resolves specifier as imported from base (the importing module's URL).
- `im_count` (function) `include/import_map.h:37` `size_t im_count(const im_map *m);` -- Resolves specifier as imported from base (the importing module's URL).
- `im_free` (function) `include/import_map.h:40` `void im_free(im_map *m);` -- Resolves specifier as imported from base (the importing module's URL).

## include/interp.h
Imported by: `gui/browser_ui.c`, `src/interp.c`, `tests/test_interp.c`
- `ip_ease` (function) `include/interp.h:48` `double ip_ease(double t, const ip_ease_fn *fn);` -- Compute eased t for normalized t ∈ [0,1].
- `ip_lerp` (function) `include/interp.h:60` `double ip_lerp(double a, double b, double t);`
- `ip_lerp_color` (function) `include/interp.h:61` `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t);`
- `ip_interp` (function) `include/interp.h:62` `double ip_interp(ip_val_kind kind, double a, double b, double t);`
- `ip_kf_interp` (function) `include/interp.h:78` `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf, int n_kf, double pct);` -- Interpolate between the two keyframes bracketing `pct` (0..100).
- `ip_anim_init` (function) `include/interp.h:121` `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease, const ip_keyframe *kf, int n_kf, double...` -- double duration_ms; double delay_ms; int iteration_count; int direction; int fill_mode; /* Runtime state double...
- `ip_anim_tick` (function) `include/interp.h:128` `int ip_anim_tick(ip_anim *a, double dt_ms);` -- Advance time by dt_ms.
- `ip_anim_current` (function) `include/interp.h:131` `double ip_anim_current(const ip_anim *a);` -- Advance time by dt_ms.
- `ip_anim_done` (function) `include/interp.h:134` `int ip_anim_done(const ip_anim *a);` -- Advance time by dt_ms.

## include/js_dom.h
Depends on: `include/dom.h`, `include/freebug.h`, `include/js_geom.h`, `include/js_location.h`, `include/js_sandbox.h`, `include/url.h`
Imported by: `fuzz/fuzz_js_dom.c`, `include/js_location.h`, `include/js_trusted.h`, `src/js_dom.c`, `src/js_dom_internal.h`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/js_location.c`, `src/tab.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`
- `opaque` (function) `include/js_dom.h:64` `* the engine runtime opaque (unreachable from script);`
- `jd_click_state_free` (function) `include/js_dom.h:78` `* jd_click_state_free(). Bound to one context via jd_install_events(). */ jd_click_state *jd_click_state_new(void);`
- `run` (function) `include/js_dom.h:87` `* run (no handler registered, or handlers ran without calling preventDefault()), * and 0 if a handler called...`
- `preventDefault` (function) `include/js_dom.h:94` `* preventDefault() was called, 1 if the default (form submission) should proceed. * ctx == NULL or no form found =>...`
- `host` (function) `include/js_dom.h:123` `* for a trusted host (allow.conf AND js.conf);`
- `jd_get_cookies` (function) `include/js_dom.h:134` `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz);` -- Serialises the page's current cookie jar ("name=value; ...") into buf (bounded, NUL-terminated) and returns its...
- `out_status` (function) `include/js_dom.h:142` `* On success returns 0 and sets *out_status (HTTP status, 0 if unknown), *out_body / * *out_body_len (response...`
- `jd_process_iframes` (function) `include/js_dom.h:163` `* BEFORE jd_process_iframes() (so iframes are in the DOM for it to process). * ctx == NULL => JD_ERR_NULL_ARG. */...`
- `URLs` (function) `include/js_dom.h:170` `* video URLs (.m3u8 then .mp4 patterns), and creates <video> elements in the document for * any found. Does NOT...`
- `jd_video_from_scripts` (function) `include/js_dom.h:184` `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts, const size_t *script_lens, size_t...` -- Creates <iframe> elements in the DOM from video data (`video[N]` / `video_data`) found in inline script text...

## include/js_env.h
Depends on: `include/js_sandbox.h`
Imported by: `src/js_env.c`, `src/tab.c`, `tests/test_js_env.c`
- `poisoned` (function) `include/js_env.h:43` `* readback is poisoned (deterministic within an origin, unlinkable across * sessions and across origins) to defeat...`

## include/js_geom.h
Depends on: `include/dom.h`
Imported by: `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_js_geom.c`, `include/js_dom.h`, `include/tab.h`, `src/js_geom.c`, `tests/test_js_dom.c`, `tests/test_js_geom.c`, `tests/test_tab.c`
- `jg_init` (function) `include/js_geom.h:44` `void jg_init(jg_table *t);` -- typedef struct jg_rect { dom_node_id node; int32_t     x, y, w, h;       /* document coordinates, px } jg_rect...
- `jg_free` (function) `include/js_geom.h:47` `void jg_free(jg_table *t);` -- } jg_rect; typedef struct jg_table { jg_rect *r; size_t   n, cap; int32_t  scroll_x, scroll_y;  /* document scroll...
- `jg_add` (function) `include/js_geom.h:52` `int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h);` -- Appends one rect.
- `jg_finish` (function) `include/js_geom.h:56` `int jg_finish(jg_table *t);` -- Sorts by node and merges rects of the same node into their bounding box. * Returns 0, or -1 on NULL.
- `jg_find` (function) `include/js_geom.h:59` `const jg_rect *jg_find(const jg_table *t, dom_node_id node);` -- Sorts by node and merges rects of the same node into their bounding box. * Returns 0, or -1 on NULL. int...
- `jg_aggregate` (function) `include/js_geom.h:65` `int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx);` -- Unions every rect into each of its ancestors (parent(ctx, n) until DOM_NODE_NONE, at most JG_MAX_DEPTH steps, so a...
- `jg_wire_len` (function) `include/js_geom.h:68` `size_t jg_wire_len(const jg_table *t);` -- Unions every rect into each of its ancestors (parent(ctx, n) until DOM_NODE_NONE, at most JG_MAX_DEPTH steps, so a...
- `jg_encode` (function) `include/js_geom.h:71` `int jg_encode(const jg_table *t, int32_t *out, size_t cap);` -- Unions every rect into each of its ancestors (parent(ctx, n) until DOM_NODE_NONE, at most JG_MAX_DEPTH steps, so a...
- `jg_decode` (function) `include/js_geom.h:77` `int jg_decode(const int32_t *in, size_t n, jg_table *out);` -- Parses a wire array into out (which must be jg_init'ed or empty; previous contents are freed).
- `jg_hash` (function) `include/js_geom.h:80` `uint64_t jg_hash(const jg_table *t);` -- Parses a wire array into out (which must be jg_init'ed or empty; previous contents are freed).

## include/js_location.h
Depends on: `include/js_dom.h`, `include/js_sandbox.h`, `include/url.h`
Imported by: `include/js_dom.h`
- `reads` (function) `include/js_location.h:25` `* reads (NULL => only href is known, the rest fall back to stub defaults). Call after * jd_install, on the page's...`
- `jd_take_history` (function) `include/js_location.h:38` `char *jd_take_history(js_context *ctx, int *go);` -- Drains the history operations page JS performed since the last call: an owned string of lines "P <url>\n"...
- `jd_pop_state` (function) `include/js_location.h:44` `int jd_pop_state(js_context *ctx, int index);` -- Moves the page's history to entry index (the parent went Back/Forward within the same document): updates location...
- `acting` (function) `include/js_location.h:49` `* The caller MUST gate the raw target with ln_resolve before acting (Zero Trust). */ int...`

## include/js_policy.h
Imported by: `gui/browser_ui.c`, `include/webcaps.h`, `src/freedom.c`, `src/js_policy.c`, `tests/test_js_policy.c`
- `membership` (function) `include/js_policy.h:16` `* membership (the allowlist itself is matched by the hostblock module, which * already covers subdomains). No I/O...`
- `allowlist` (function) `include/js_policy.h:34` `* allowlist (e.g. hb_is_allowlisted over js.conf). Fails closed: an unknown mode * yields false. */ bool...`
- `jsp_trusted` (function) `include/js_policy.h:45` `bool jsp_trusted(bool js_enabled, int host_allowlisted);` -- Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g....
- `jsp_present_trusted` (function) `include/js_policy.h:54` `bool jsp_present_trusted(int host_allowlisted);` -- Presentation-trust (2026-07-11): a host EXPLICITLY on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- `jsp_mode_str` (function) `include/js_policy.h:64` `const char *jsp_mode_str(jsp_mode mode);` -- Stable lowercase name of a mode ("off"/"allowlist"/"on"); an unknown value * yields "off" (fail closed).

## include/js_sandbox.h
Imported by: `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_js_sandbox.c`, `include/js_dom.h`, `include/js_env.h`, `include/js_location.h`, `include/js_trusted.h`, `src/js_dom.c`, `src/js_embed.c`, `src/js_env.c`, `src/js_events.c`, `src/js_fetch.c`, `src/js_sandbox.c`, `src/tab.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_js_sandbox.c`
- `js_context_free` (function) `include/js_sandbox.h:86` `void js_context_free(js_context *ctx);` -- Creates an isolated, hardened sandbox (memory/stack/time limits armed; no I/O modules). lim == NULL =>...
- `loaded` (function) `include/js_sandbox.h:114` `* NULL when it cannot be loaded (policy refusal, network error, not JavaScript). */ typedef char...`
- `js_set_module_host` (function) `include/js_sandbox.h:119` `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve, js_module_fetch_fn fetch, void *host);` -- Installs the host every static import and dynamic import() goes through. host must * outlive ctx.
- `js_loc_from_stack` (function) `include/js_sandbox.h:140` `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap, int *line, int *col);` -- Pure parser: extracts the throw site (file, line, column) from the FIRST frame of a QuickJS .stack string.
- `js_set_time_budget` (function) `include/js_sandbox.h:148` `void js_set_time_budget(js_context *ctx, uint64_t budget_ms);` -- Adjusts the wall-clock budget armed on each subsequent js_eval.
- `js_result_free` (function) `include/js_sandbox.h:151` `void js_result_free(js_result *res);` -- Adjusts the wall-clock budget armed on each subsequent js_eval.
- `js_pump_jobs` (function) `include/js_sandbox.h:159` `int js_pump_jobs(js_context *ctx, int max_jobs);` -- Runs up to max_jobs pending microtasks/jobs (promise reactions queued by the last eval), under the context's current...
- `handle` (function) `include/js_sandbox.h:162` `* as an opaque handle (so this header stays free of backend types), or NULL. * Valid only while ctx is alive....`
- `js_set_current_script` (function) `include/js_sandbox.h:171` `void js_set_current_script(js_context *ctx, const char *src, const char *type);` -- Sets document.currentScript on the global object so external scripts can read their own src / type / data-*...

## include/js_trusted.h
Depends on: `include/js_dom.h`, `include/js_sandbox.h`
Imported by: `fuzz/fuzz_js_dom.c`, `src/js_trusted.c`, `src/tab.c`, `tests/test_js_dom.c`
- `null` (function) `include/js_trusted.h:24` `* noopener semantics: it returns null (no cross-window reference, so no same-origin * channel) and only records up...`
- `jt_take_opens` (function) `include/js_trusted.h:31` `char *jt_take_opens(js_context *ctx);` -- Installs window.open for a TRUSTED host (allow.conf AND js.conf) only (plan B4c). noopener semantics: it returns...
- `parent` (function) `include/js_trusted.h:58` `* socket: the object records operations for the parent (jt_take_ws). */ jd_status jt_enable_ws(js_context *ctx);`
- `jt_take_ws` (function) `include/js_trusted.h:64` `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap);` -- Drains up to cap recorded operations into ops (each data owned; release with jt_ws_ops_free).
- `jt_ws_ops_free` (function) `include/js_trusted.h:65` `void jt_ws_ops_free(jt_ws_op *ops, size_t n);`
- `jt_ws_event` (function) `include/js_trusted.h:70` `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len);` -- Delivers a socket event from the parent: data enters JS as a VALUE (a string for text, an ArrayBuffer for binary...
- `jt_take_storage` (function) `include/js_trusted.h:82` `int jt_take_storage(js_context *ctx, char **out, size_t *len);` -- When the store changed since the last call, returns 1 with an owned snapshot of * the whole store in *out (length...
- `realm` (function) `include/js_trusted.h:85` `* runs in its own realm (js_install_realms) of this context's runtime, inside the * same confined process and...`

## include/link_nav.h
Imported by: `fuzz/fuzz_url.c`, `gui/browser_ui.c`, `src/freedom.c`, `src/link_nav.c`, `src/tab.c`, `tests/test_link_nav.c`
- `dropped` (function) `include/link_nav.h:36` `* A longer fragment is dropped (stored as "");`
- `ln_block_reason_text` (function) `include/link_nav.h:85` `const char *ln_block_reason_text(ln_block_reason reason);` -- Stable, short English notice for a block reason (e.g. for a UI toast or agent * output).

## include/local_store.h
Imported by: `include/disk_store.h`, `include/profile.h`, `src/disk_store.c`, `src/local_store.c`, `tests/test_disk_store.c`, `tests/test_local_store.c`
- `ls_free` (function) `include/local_store.h:80` `void ls_free(uint8_t *buf, size_t len);` -- Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container...

## include/media_decoder.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/media_decoder.c`, `tests/test_media_decoder.c`
- `md_pace_due_ms` (function) `include/media_decoder.h:79` `static inline uint64_t md_pace_due_ms(md_pacer *p, uint64_t now_ms,
                             ...` -- Returns the wall-clock instant (ms) at which the frame carrying pts_us is due for display.
- `media_decoder_run` (function) `include/media_decoder.h:99` `void media_decoder_run(int out_fd, int cmd_fd);` -- Entry point for the decoder child process.
- `media_decoder_spawn` (function) `include/media_decoder.h:104` `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd);` -- Spawns a media decoder child via fork+exec.

## include/net_realm.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/net_realm.c`, `tests/test_net_realm.c`
- `NR_ROUTE_BLOCKED` (function) `include/net_realm.h:57` `* NR_ROUTE_BLOCKED (fail closed: never route what cannot be classified). A realm * whose proxy is not enabled =>...`
- `address` (function) `include/net_realm.h:62` `* and encrypts by its address (the I2P destination / onion key), so http over it is * not a downgrade. Currently...`
- `nr_realm_allows_http` (function) `include/net_realm.h:66` `int nr_realm_allows_http(nr_realm r);` -- 1 iff plain http:// is acceptable for this realm.
- `nr_realm_name` (function) `include/net_realm.h:69` `const char *nr_realm_name(nr_realm r);` -- 1 iff plain http:// is acceptable for this realm.
- `nr_route_name` (function) `include/net_realm.h:70` `const char *nr_route_name(nr_route r);`

## include/os_sandbox.h
Imported by: `src/os_sandbox.c`, `src/renderer.c`, `src/tab.c`, `tests/test_os_sandbox.c`
- `flags` (function) `include/os_sandbox.h:39` `* permission also depends on the protection flags (see os_prot_allowed / W^X). */ int os_policy_allows(long syscall_nr);`
- `os_policy_size` (function) `include/os_sandbox.h:43` `size_t os_policy_size(void);` -- Nonzero iff syscall_nr is on the strict allowlist (mirrors the BPF program).
- `os_prot_allowed` (function) `include/os_sandbox.h:52` `int os_prot_allowed(long syscall_nr, unsigned long prot);` -- Pure mirror of the BPF program's EFFECTIVE decision for memory syscalls (W^X).
- `denied` (function) `include/os_sandbox.h:59` `* request PROT_EXEC are denied (see os_prot_allowed). * Returns OS_ERR_UNSUPPORTED on platforms without seccomp-bpf...`
- `namespace` (function) `include/os_sandbox.h:75` `* namespace (the unprivileged enabler), network (the worker never needs the * network -- the parent fetches and...`
- `os_namespace_flags` (function) `include/os_sandbox.h:81` `int os_namespace_flags(void);` -- The set of CLONE_* namespace flags the worker isolates into: a new user namespace (the unprivileged enabler)...
- `os_landlock_abi` (function) `include/os_sandbox.h:114` `int os_landlock_abi(void);` -- /* What a Landlock rule permits at/below a path. typedef enum os_fs_access { OS_FS_NONE       = 0, /* no access (not...

## include/page_view.h
Depends on: `include/css.h`, `include/dom.h`, `include/html_parse.h`
Imported by: `fuzz/fuzz_dom_debug.c`, `fuzz/fuzz_page_view.c`, `include/box_tree.h`, `include/render_doc.h`, `include/tab.h`, `src/dom_debug.c`, `src/freedom.c`, `src/page_view.c`, `src/tab.c`, `tests/test_box_tree.c`, `tests/test_dom_debug.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`
- `container` (function) `include/page_view.h:228` `* cont_id groups runs of one container (-1 = none);`
- `bx_display` (function) `include/page_view.h:229` `* bx_display (flex/grid);`
- `order` (function) `include/page_view.h:293` `* groups the runs of ONE floated element in document order (-1 = not in a float);`
- `itself` (function) `include/page_view.h:351` `* by itself (bx_width_cap2);`
- `CSS_LEN_UNSET` (function) `include/page_view.h:546` `* CSS_LEN_UNSET (unset) / CSS_LEN_AUTO. z_index is signed, or CSS_LEN_UNSET. v1 * paints only position:relative (an...`
- `scale` (function) `include/page_view.h:621` `* scale(1)) and rotate in whole degrees (transform_rotate);`
- `declare` (function) `include/page_view.h:836` `* margin the author did not declare (px or %), 0 on a declared side (the body's * own box, or nothing for 0, owns...`
- `nonzero` (function) `include/page_view.h:848` `* when nonzero (JS allowed for this page) the <noscript> subtree is suppressed. */ pv_status pv_build_ex(const...`
- `resolved` (function) `include/page_view.h:855` `* author CSS is still resolved (the presentation layer decides whether to apply it). * pv_build_ex is pv_build_full...`
- `policy` (function) `include/page_view.h:863` `* TRUSTED parent under full network policy (spec/tab.md §8) -- page_view stays * pure and never fetches. The...`
- `cause` (function) `include/page_view.h:881` `* cause (spec/css_drops.md). Builds no view and changes nothing -- it exists so * "what is this page's CSS losing?"...`
- `pv_new` (function) `include/page_view.h:893` `pv_view *pv_new(void);` -- Allocates an empty view (used by the IPC deserialiser to rebuild a view on the * receiving side).
- `form` (function) `include/page_view.h:912` `* form (-1 if none);`
- `pv_set_emphasis` (function) `include/page_view.h:944` `void pv_set_emphasis(pv_view *v, int bold, int italic);` -- Sets the inline emphasis flags (bold from <b>/<strong>/<th>, italic from <i>/<em>) on the most recently appended run.
- `default` (function) `include/page_view.h:949` `* structure is carried by default (not gated by caps.css). */ void pv_set_indent(pv_view *v, int indent);`
- `pv_set_color` (function) `include/page_view.h:952` `void pv_set_color(pv_view *v, int fg_rgb);`
- `pv_set_bgcolor` (function) `include/page_view.h:959` `void pv_set_bgcolor(pv_view *v, int bg_rgb);` -- Sets the author background-color (packed 0xRRGGBB, or -1 for none) on the most recently appended run.
- `pv_set_text_style` (function) `include/page_view.h:968` `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs, int line_scale, int text_decoration);` -- Sets the author text presentation (text_align as a css_align, font_scale as a font-size percent or 0, font_abs as 1...
- `pv_text_ext_reset` (function) `include/page_view.h:1023` `void pv_text_ext_reset(pv_text_ext *e);` -- Gradient text (2026-07-19). text_fill: -webkit-text-fill-color from the nearest ancestor that sets it (packed /...
- `ancestors` (function) `include/page_view.h:1028` `* itself by walking its ancestors (css_visibility, 0 = unset). * * An explicit value on the run WINS over the box...`
- `pv_set_text_ext` (function) `include/page_view.h:1038` `void pv_set_text_ext(pv_view *v, const pv_text_ext *e);`
- `pv_set_grad_text` (function) `include/page_view.h:1044` `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4);` -- Sets the gradient-text fill (grad_text_*) verbatim on the most recently appended run. n < 2 is a no-op (no gradient).
- `run` (function) `include/page_view.h:1047` `* run (cont_id, the bx_display, the parsed gap/justify/cols, plus flex-wrap/ * row-gap/align-items). No-op on an...`
- `pv_set_row_span` (function) `include/page_view.h:1060` `void pv_set_row_span(pv_view *v, int row_span);` -- Sets the container's grid track sizes and this run's ITEM column span on the most recently appended run...
- `pv_set_grid_area` (function) `include/page_view.h:1064` `void pv_set_grid_area(pv_view *v, int row_start, int col_start);` -- Sets the last run's RESOLVED named-grid cell (-1, -1 = auto-placed).
- `pv_set_grid_rows` (function) `include/page_view.h:1065` `void pv_set_grid_rows(pv_view *v, int grid_rows);`
- `pv_set_ua_tag` (function) `include/page_view.h:1070` `void pv_set_ua_tag(pv_view *v, int ua_tag);` -- Sets the last run's ua_tag (a bx_ua_tag code: the user-agent box identity of its nearest block-level ancestor).
- `pv_set_cont_box` (function) `include/page_view.h:1074` `void pv_set_cont_box(pv_view *v, int cont_box_id);` -- Sets the last run's cont_box_id (the box enclosing its container's items; -1 = * none).
- `pv_set_grid` (function) `include/page_view.h:1075` `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span);`
- `pv_set_flex` (function) `include/page_view.h:1083` `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis, int flex_order, int flex_direction, int...` -- Stage 3: sets the flex per-item values on the most recently appended run — the ITEM's resolved grow/shrink (x100, -1...
- `pv_set_flex_mauto` (function) `include/page_view.h:1086` `void pv_set_flex_mauto(pv_view *v, int mauto);` -- Stage 3: sets the flex per-item values on the most recently appended run — the ITEM's resolved grow/shrink (x100, -1...
- `pv_set_cont_item` (function) `include/page_view.h:1090` `void pv_set_cont_item(pv_view *v, int cont_item);` -- Sets the container-item ordinal on the most recently appended run (-1 = none). * No-op on an empty or NULL view; the...
- `pv_set_float_w` (function) `include/page_view.h:1101` `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box);` -- Stamps the float founder's own declared width halves (pv_run.float_w) on the * most recently appended run.
- `pv_set_float` (function) `include/page_view.h:1103` `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear, int float_ml, int float_ml_pct, int...`
- `pv_set_box` (function) `include/page_view.h:1113` `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w, int box_center, int box_mt, int box_mb);` -- Sets the author box model on the most recently appended run (left/right insets, width cap, centered flag, and...
- `pv_set_box_pct` (function) `include/page_view.h:1119` `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct, int box_mt_pct, int box_mb_pct);` -- Sets the symbolic percentage width cap (per-mille, 0 = none; Hito 32) on the most recently appended run.
- `pv_set_box_maxw` (function) `include/page_view.h:1124` `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct);` -- Sets the max-width cap (px half, 0 = none; per-mille half, 0 = none) on the most * recently appended run.
- `pv_set_node_id` (function) `include/page_view.h:1129` `void pv_set_node_id(pv_view *v, dom_node_id node_id);` -- Keystone (Stage 0) setter for the most recently appended run: the dom_node_id of the source element.
- `pv_set_block_id` (function) `include/page_view.h:1134` `void pv_set_block_id(pv_view *v, int block_id);` -- Box engine (Hito 23b-8) setter for the most recently appended run: the block_id of the box-carrying block it belongs...
- `pv_set_own_box` (function) `include/page_view.h:1138` `void pv_set_own_box(pv_view *v, int box_id);` -- Records the replaced element's own box def index on the last appended run.
- `pv_set_oof` (function) `include/page_view.h:1142` `void pv_set_oof(pv_view *v, int oof);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_justify_self` (function) `include/page_view.h:1145` `void pv_set_justify_self(pv_view *v, int justify_self);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_block_node` (function) `include/page_view.h:1148` `void pv_set_block_node(pv_view *v, dom_node_id id);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_br_line` (function) `include/page_view.h:1156` `void pv_set_br_line(pv_view *v, int br_line);` -- Sets the last appended run's PV_BR_* flags (see pv_run.br_line); other bits * are dropped.
- `pv_cont_count` (function) `include/page_view.h:1171` `size_t pv_cont_count(const pv_view *v);` -- pv_cont_count is v->ncont (0 when v is NULL); pv_cont_at returns conts[i] * (i == a cont_id) or NULL when out of...
- `pv_cont_at` (function) `include/page_view.h:1172` `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i);`
- `pv_set_input_checked` (function) `include/page_view.h:1176` `void pv_set_input_checked(pv_view *v, int checked);` -- Sets the input's checked state (-1 n/a, 0 unchecked, 1 checked) on the most * recently appended run.
- `pv_set_input_placeholder` (function) `include/page_view.h:1180` `void pv_set_input_placeholder(pv_view *v, int ph_color);` -- Sets the input's checked state (-1 n/a, 0 unchecked, 1 checked) on the most * recently appended run.
- `pv_svg_append_root_attrs` (function) `include/page_view.h:1186` `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs, size_t *out_len);` -- Appends attrs (e.g.
- `pv_placeholder_color` (function) `include/page_view.h:1189` `int pv_placeholder_color(const css_style *ph);` -- Appends attrs (e.g.
- `pv_set_input_select_opts` (function) `include/page_view.h:1193` `void pv_set_input_select_opts(pv_view *v, const char *select_opts);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_free` (function) `include/page_view.h:1196` `void pv_free(pv_view *v);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_count` (function) `include/page_view.h:1199` `size_t pv_count(const pv_view *v);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_at` (function) `include/page_view.h:1200` `const pv_run *pv_at(const pv_view *v, size_t i);`
- `pv_box_count` (function) `include/page_view.h:1204` `size_t pv_box_count(const pv_view *v);` -- Box tree accessors (Step D). pv_box_count is the number of box definitions; * pv_box_at returns boxes[i] (i == a...
- `pv_box_at` (function) `include/page_view.h:1205` `const pv_box_def *pv_box_at(const pv_view *v, size_t i);`

## include/pdf_export.h
Imported by: `fuzz/fuzz_pdf_export.c`, `gui/browser_ui.c`, `src/download.c`, `src/pdf_export.c`, `tests/test_pdf_export.c`
- `fallback` (function) `include/pdf_export.h:46` `* fallback (PE_ERR_OVERFLOW, out left empty). title == NULL is treated as empty. * Does NOT append the extension...`
- `trusted` (function) `include/pdf_export.h:51` `* dir is trusted (chosen by the app from XDG/$HOME);`
- `literal` (function) `include/pdf_export.h:52` `* trusted literal (e.g. PE_EXT / PE_EXT_PNG);`
- `pe_paginate` (function) `include/pdf_export.h:70` `size_t pe_paginate(const double *tops, const double *heights, size_t n, double page_h, int *out_page, double...` -- Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h...

## include/perf_trace.h
Imported by: `src/freedom.c`, `src/perf_trace.c`, `tests/test_perf_trace.c`
- `pt_init` (function) `include/perf_trace.h:46` `void pt_init(pt_trace *t);` -- #define PT_MAX_SAMPLES 256 typedef struct pt_stage_stats { uint64_t samples[PT_MAX_SAMPLES]; size_t   fill;   /*...
- `pt_elapsed_us` (function) `include/perf_trace.h:50` `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us);` -- end_us - start_us with an anti-underflow guard: end < start yields 0 * instead of wrapping to a huge uint64_t.
- `pt_record` (function) `include/perf_trace.h:54` `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us);` -- Record one sample (microseconds) for the given stage.
- `pt_count` (function) `include/perf_trace.h:57` `size_t pt_count(const pt_trace *t, pt_stage stage);` -- Record one sample (microseconds) for the given stage.
- `pt_last_us` (function) `include/perf_trace.h:60` `uint64_t pt_last_us(const pt_trace *t, pt_stage stage);` -- Record one sample (microseconds) for the given stage.
- `pt_min_us` (function) `include/perf_trace.h:63` `uint64_t pt_min_us(const pt_trace *t, pt_stage stage);` -- Record one sample (microseconds) for the given stage.
- `pt_max_us` (function) `include/perf_trace.h:64` `uint64_t pt_max_us(const pt_trace *t, pt_stage stage);`
- `pt_median_us` (function) `include/perf_trace.h:65` `uint64_t pt_median_us(const pt_trace *t, pt_stage stage);`
- `pt_stage_name` (function) `include/perf_trace.h:69` `const char *pt_stage_name(pt_stage stage);` -- Short lowercase stage name ("fetch".."shape"); "unknown" if out of range. * Static string, never NULL.
- `pt_format` (function) `include/perf_trace.h:76` `size_t pt_format(const pt_trace *t, char *buf, size_t cap);` -- Deterministic dump, one line per stage with count > 0, enum order: stage=<name> n=<total> last_us=<n> min_us=<n>...

## include/prefetch.h
Imported by: `fuzz/fuzz_prefetch.c`, `gui/browser_ui.c`, `src/freedom.c`, `src/prefetch.c`, `tests/test_prefetch.c`
- `pf_scan` (function) `include/prefetch.h:62` `int pf_scan(const char *html, size_t len, pf_list *out);` -- Lookahead scan of hostile HTML.
- `pf_list_free` (function) `include/prefetch.h:63` `void pf_list_free(pf_list *l);`
- `specifiers` (function) `include/prefetch.h:110` `* specifiers (each < PF_SPEC_MAX) into out[k] and returns how many. Pure. */ size_t pf_scan_imports(const char *js...`
- `pf_find_importmap` (function) `include/prefetch.h:115` `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n);` -- Span of the first <script type=importmap> body in html (pure, bounded): 1 with * [*start, *start + *n) set, or 0...
- `started` (function) `include/prefetch.h:121` `* to fetch or no thread started (the caller fetches serially). */ int pf_pool_start_page(pf_pool *p, const char...`
- `pf_pool_add` (function) `include/prefetch.h:127` `int pf_pool_add(pf_pool *p, const char *url);` -- Queues one more URL on a started pool (deduplicated, bounded by PF_MAX_JOBS). * Returns 1 when added, 0 when already...
- `fetch` (function) `include/prefetch.h:132` `* claiming jobs and running fetch(ctx, "GET", url, ...). Returns 0 on success or * -1 when no thread could start...`
- `pf_pool_take` (function) `include/prefetch.h:145` `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status, char **body, size_t *len, char **ctype);` -- Cache-first take.
- `pf_pool_finish` (function) `include/prefetch.h:151` `void pf_pool_finish(pf_pool *p);` -- Joins the worker threads and frees every unconsumed result.
- `pool` (function) `include/prefetch.h:155` `* whose URL is pooled is served from the pool (a failed prefetch propagates the * failure -- never refetched);`
- `pf_pooled_fetch` (function) `include/prefetch.h:165` `int pf_pooled_fetch(void *vctx, const char *method, const char *url, const char *body, size_t body_len, int...`

## include/prefs.h
Imported by: `fuzz/fuzz_prefs.c`, `gui/browser_ui.c`, `include/profile.h`, `src/prefs.c`, `tests/test_prefs.c`, `tests/test_profile.c`
- `prefs_init` (function) `include/prefs.h:65` `void prefs_init(prefs_state *p);` -- Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `prefs_free` (function) `include/prefs.h:68` `void prefs_free(prefs_state *p);` -- Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `free` (function) `include/prefs.h:71` `* free(). */ prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len);`
- `prefs_bookmark_index` (function) `include/prefs.h:81` `int prefs_bookmark_index(const prefs_state *p, const char *url);` -- Parses text[0..len) over an out ALREADY initialised with prefs_init.
- `prefs_suggest` (function) `include/prefs.h:100` `int prefs_suggest(const prefs_state *p, const char *query, char *out, size_t row_len, int max_rows);` -- Omnibox autocomplete: up to max_rows distinct URLs matching query (case- insensitive) written to out (rows of...
- `anyway` (function) `include/prefs.h:105` `* page is rendered by the normal confined pipeline anyway (defence in depth). * *out is owned (free());`

## include/profile.h
Depends on: `include/local_store.h`, `include/prefs.h`
Imported by: `gui/browser_ui.c`, `src/profile.c`, `tests/test_profile.c`
- `absent` (function) `include/profile.h:53` `* the keyfile when absent (0600, atomic write);`
- `closed` (function) `include/profile.h:54` `* wrong size fails closed (PROFILE_ERR_KEY, never overwritten). Derives the * AEAD key (Argon2id, per-device salt)...`
- `profile_close` (function) `include/profile.h:67` `void profile_close(profile_ctx *ctx);` -- Loads and decrypts prefs.bin over an out ALREADY initialised (prefs_init).

## include/render_doc.h
Depends on: `include/page_view.h`, `include/render_policy.h`
Imported by: `fuzz/fuzz_dom_debug.c`, `gui/browser_ui.c`, `include/dom_debug.h`, `src/freedom.c`, `src/render_doc.c`, `tests/test_dom_debug.c`, `tests/test_render_doc.c`
- `list` (function) `include/render_doc.h:18` `* inert display list (page_view) and the presentation orchestrator (the GUI and * the --headless writer). It decides...`
- `RD_IMAGE` (function) `include/render_doc.h:59` `* RD_IMAGE (image src) and RD_INPUT (the owning form's action);`
- `form` (function) `include/render_doc.h:63` `* form (-1 = none);`
- `default` (function) `include/render_doc.h:150` `* default (layout is structure, not author styling, and leaks nothing to the * network) so the presentation layer...`
- `to` (function) `include/render_doc.h:247` `* belongs to (-1 = none);`
- `rdp_images_warning` (function) `include/render_doc.h:302` `* rdp_images_warning() is prepended so the user is always told. Each image * becomes an RD_IMAGE block whose...`
- `rd_free` (function) `include/render_doc.h:312` `void rd_free(rd_doc *d);` -- Builds the paint-ready document from an inert display list and the page's capabilities. view == NULL is treated as...
- `rd_count` (function) `include/render_doc.h:315` `size_t rd_count(const rd_doc *d);` -- images and caps.images is false, a single RD_NOTICE block carrying rdp_images_warning() is prepended so the user is...
- `rd_at` (function) `include/render_doc.h:316` `const rd_block *rd_at(const rd_doc *d, size_t i);`
- `rd_box_count` (function) `include/render_doc.h:320` `size_t rd_box_count(const rd_doc *d);` -- Box tree accessors (Step D). rd_box_count is the number of box definitions (0 when * caps.css is off); rd_box_at...
- `rd_box_at` (function) `include/render_doc.h:321` `const pv_box_def *rd_box_at(const rd_doc *d, size_t i);`
- `rd_cont_count` (function) `include/render_doc.h:325` `size_t rd_cont_count(const rd_doc *d);` -- Container table accessors. rd_cont_count is the number of containers; rd_cont_at * returns conts[i] (i == a run's...
- `rd_cont_at` (function) `include/render_doc.h:326` `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i);`
- `rd_kind_name` (function) `include/render_doc.h:330` `const char *rd_kind_name(rd_kind k);` -- Stable, short English name of a block kind for structured/agent output.
- `rd_block_tag` (function) `include/render_doc.h:338` `const char *rd_block_tag(const rd_block *b);` -- Canonical HTML tag name for a block, so the presentation layer can look up its user-agent box (box_style) without...
- `decision` (function) `include/render_doc.h:341` `* decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never * NULL. */ const char...`
- `IMG_FAIL_OK` (function) `include/render_doc.h:347` `* IMG_FAIL_OK (not a failure) or the reason is unknown. */ const char *rd_image_fail_label(img_fail_reason reason);`
- `rd_input_label` (function) `include/render_doc.h:352` `const char *rd_input_label(int input_type);` -- Stable, short English name of a form control type (a pv_input_type value), e.g. * "text" / "password" / "submit".
- `rd_input_invisible` (function) `include/render_doc.h:357` `int rd_input_invisible(int input_type);` -- Nonzero iff a control of this type has no face of its own and is therefore never laid out or painted: a hidden...

## include/render_policy.h
Imported by: `fuzz/fuzz_dom_debug.c`, `gui/browser_ui.c`, `include/render_doc.h`, `include/webcaps.h`, `src/freedom.c`, `src/render_policy.c`, `tests/test_dom_debug.c`, `tests/test_render_doc.c`, `tests/test_render_policy.c`
- `rdp_is_tracking_pixel` (function) `include/render_policy.h:53` `int rdp_is_tracking_pixel(int w, int h);` -- Tracking-pixel heuristic over an image's declared dimensions. w/h negative means "unknown".
- `size` (function) `include/render_policy.h:56` `* announced size (e.g. <img width height>);`
- `rdp_img_reason` (function) `include/render_policy.h:66` `const char *rdp_img_reason(rdp_img_decision d);` -- Stable, short, English reason string for structured/agent-friendly output. * Never NULL; an unknown enum value...
- `rdp_images_warning` (function) `include/render_policy.h:69` `const char *rdp_images_warning(void);` -- Stable, short, English reason string for structured/agent-friendly output. * Never NULL; an unknown enum value...

## include/renderer.h
Imported by: `src/renderer.c`, `tests/test_renderer.c`
- `rd_result_free` (function) `include/renderer.h:46` `void rd_result_free(rd_result *out);` -- Renders untrusted HTML out-of-process and returns an inert title + text. html == NULL or out == NULL => RD_ERR_NULL_ARG.

## include/request_policy.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/render_policy.c`, `src/request_policy.c`, `src/tab.c`, `tests/test_request_policy.c`
- `rp_host_of` (function) `include/request_policy.h:30` `int rp_host_of(const char *url, char *out, size_t out_size);` -- Lowercased host of an absolute URL into out.
- `rp_site_of` (function) `include/request_policy.h:34` `int rp_site_of(const char *host, char *out, size_t out_size);` -- Registrable domain ("site") of a host into out (simplified public-suffix * rule).
- `rp_same_site` (function) `include/request_policy.h:37` `int rp_same_site(const char *top_level_url, const char *request_url);` -- Registrable domain ("site") of a host into out (simplified public-suffix * rule).

## include/secure_fetch.h
Depends on: `include/anti_fp.h`
Imported by: `gui/browser_ui.c`, `include/ws_hub.h`, `src/freedom.c`, `src/secure_fetch.c`, `tests/itest_secure_fetch.c`, `tests/test_secure_fetch.c`
- `validators` (function) `include/secure_fetch.h:17` `* The security logic lives in pure validators (no I/O);`
- `sf_global_init` (function) `include/secure_fetch.h:204` `void sf_global_init(void);` -- Initialises process-global transport state (libcurl/OpenSSL) once, from the main thread, before any concurrent...
- `EXCLUDED` (function) `include/secure_fetch.h:210` `* cookies are EXCLUDED (network-only, never exposed to JS) and expired cookies skipped. * Only for a TRUSTED host...`
- `sf_cookie_put` (function) `include/secure_fetch.h:217` `void sf_cookie_put(const char *url, const char *namevalue);` -- Injects a JS-set cookie ("name=value") into the shared jar, scoped to url's host, as if it arrived via Set-Cookie...
- `sf_cookie_line_matches` (function) `include/secure_fetch.h:222` `int sf_cookie_line_matches(const char *line, const char *host, const char *path, long now, char *out, size_t outsz);` -- Pure: parses one CURLINFO_COOKIELIST Netscape line ("domain\\tflag\\tpath\\tsecure\\t expiry\\tname\\tvalue"); if...
- `sf_user_agent_or_default` (function) `include/secure_fetch.h:231` `const char *sf_user_agent_or_default(const char *ua);` -- Returns ua when it is a non-empty string, else SF_DEFAULT_USER_AGENT.
- `sf_impersonate_kex_groups` (function) `include/secure_fetch.h:235` `const char *sf_impersonate_kex_groups(void);` -- The interim impersonation ClientHello strings (pure; single source of truth so the * shaping is unit-testable...
- `sf_impersonate_tls13_ciphers` (function) `include/secure_fetch.h:236` `const char *sf_impersonate_tls13_ciphers(void);`
- `skipped` (function) `include/secure_fetch.h:256` `* skipped (a classical key exchange is accepted);`
- `sf_is_redirect_code` (function) `include/secure_fetch.h:267` `int sf_is_redirect_code(long http_code);` -- Enforces the full connection policy in order: TLS version, then KE group, then certificate chain.
- `bits` (function) `include/secure_fetch.h:310` `* *flags receives CURLWS_* bits (text/binary/close/cont);`
- `sf_ws_fd` (function) `include/secure_fetch.h:317` `int sf_ws_fd(const sf_ws *ws);` -- Non-blocking: reads one frame chunk into buf. *got == 0 when nothing is pending. *flags receives CURLWS_* bits...
- `sf_ws_close` (function) `include/secure_fetch.h:320` `void sf_ws_close(sf_ws *ws);` -- Non-blocking: reads one frame chunk into buf. *got == 0 when nothing is pending. *flags receives CURLWS_* bits...
- `connection` (function) `include/secure_fetch.h:324` `* on each connection (Zero Trust). Each target is re-validated and a downgrade * to http:// is refused. Exceeding...`
- `sf_get` (function) `include/secure_fetch.h:333` `* sf_get (Zero Trust): an insecure POST is not representable. Does not follow * redirects (the caller inspects...`
- `sf_response_free` (function) `include/secure_fetch.h:344` `void sf_response_free(sf_response *resp);` -- Performs an HTTPS POST under the given policy, sending body (body_len bytes) with the given Content-Type.

## include/svg_paint.h
Depends on: `include/svg_render.h`
Imported by: `gui/browser_ui.c`, `gui/svg_paint.c`
- `svp_draw` (function) `include/svg_paint.h:31` `void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, double h, int current_rgb);` -- Paints `img` into the rect [x, y, w, h] of `cr`, scaled uniformly and centred ("xMidYMid meet"). current_rgb is the...

## include/svg_render.h
Imported by: `fuzz/fuzz_svg_render.c`, `gui/browser_ui.c`, `include/svg_paint.h`, `src/page_view.c`, `src/svg_render.c`, `tests/test_svg_render.c`
- `sv_fit` (function) `include/svg_render.h:131` `void sv_fit(const sv_image *img, double dw, double dh, double *scale, double *off_x, double *off_y);` -- Maps the image's user space onto the destination rect [dx, dy, dw, dh] the way a `preserveAspectRatio="xMidYMid...

## include/tab.h
Depends on: `include/freebug.h`, `include/js_geom.h`, `include/page_view.h`
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/tab.c`, `tests/test_tab.c`
- `tab_worker_dispatch` (function) `include/tab.h:152` `* Call tab_worker_dispatch(argc, argv) as the FIRST thing in main(): if argv is the * internal "--tab-worker <rfd>...`
- `tab_open` (function) `include/tab.h:156` `* and reaches tab_open (the app and the test harness) must call this first. */ void tab_worker_dispatch(int argc...`
- `tab_parse_worker_args` (function) `include/tab.h:163` `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd);` -- Pure validator of the worker handoff arguments (the security-relevant surface of the exec): returns nonzero and...
- `out_status` (function) `include/tab.h:175` `* On success return 0 and set *out_status (HTTP status), *out_body / *out_body_len * (malloc'd response bytes, tab...`
- `tab_set_fetcher` (function) `include/tab.h:186` `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx);` -- Installs the subresource fetcher used for XHR/fetch (NULL clears it: requests are then * refused). fn/ctx must...
- `bytes` (function) `include/tab.h:190` `* so the parent can retain the bytes (spec/webfont.md b3b feeds them to the * @font-face loader as extern sheets)....`
- `tab_set_css_sink` (function) `include/tab.h:199` `void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx);`
- `tab_set_net_allowed` (function) `include/tab.h:204` `void tab_set_net_allowed(tab *t, int allowed);` -- Grants/revokes page-JS network access (XMLHttpRequest/fetch) for the NEXT load.
- `jar` (function) `include/tab.h:207` `* the trusted parent read from its ephemeral network jar (sf_cookie_header_for). Only * meaningful for a trusted...`
- `tab_set_cookies` (function) `include/tab.h:211` `void tab_set_cookies(tab *t, const char *cookies);` -- Seeds the page's document.cookie jar for the NEXT load with cookies ("name=value; ...") the trusted parent read from...
- `origin` (function) `include/tab.h:214` `* page origin (web_storage snapshot, copied). Used only when the load is trusted * (net granted);`
- `tab_set_storage` (function) `include/tab.h:216` `void tab_set_storage(tab *t, const char *blob, size_t len);` -- Seeds localStorage for the next load from the parent's in-memory store for the page origin (web_storage snapshot...
- `exclusively` (function) `include/tab.h:222` `* exclusively (tab_subreq_permitted). Default 0: zero fetches, Privacy by Default. */ void tab_set_css_allowed(tab...`
- `tab_set_viewport_w` (function) `include/tab.h:230` `void tab_set_viewport_w(tab *t, int px);` -- Sets the render viewport width (px) used to evaluate @media width queries on the NEXT load, so a responsive page...
- `tab_last_subreq_stats` (function) `include/tab.h:236` `void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us);` -- Subresources the parent served for the LAST load (the worker's TAG_SUBREQ: XHR, fetch, external scripts, ES...
- `tab_subreq_permitted` (function) `include/tab.h:241` `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method);` -- Pure parent-side subresource gate (Zero Trust: decided from the PARENT's grants for this load, never the worker's...
- `view` (function) `include/tab.h:249` `* <noscript> handling in the built view (off => fallback shown, on => suppressed) * and is where allowlisted...`
- `string` (function) `include/tab.h:269` `* event_type is a JS event type string (e.g. "keydown", "input", "change"). * key is the keyboard key value (may be...`
- `granted` (function) `include/tab.h:318` `* granted (allow.conf AND js.conf);`
- `returned` (function) `include/tab.h:319` `* returned (the page keeps its zeros). The worker re-checks the same condition. * g must be finished (jg_finish). */...`
- `popstate` (function) `include/tab.h:325` `* popstate (+ hashchange) and re-derives the view like a click. */ tab_status tab_popstate(tab *t, int index...`
- `decode` (function) `include/tab.h:344` `* could not decode (caller shows the placeholder), which is not a transport error. * TAB_ERR_* is reserved for...`
- `tab_alive` (function) `include/tab.h:357` `int tab_alive(const tab *t);` -- Same contract as tab_decode_image, for an inline data: URI image (RFC 2397 base64 variant): data_url slices the...
- `tab_child_pid` (function) `include/tab.h:360` `pid_t tab_child_pid(const tab *t);` -- Same contract as tab_decode_image, for an inline data: URI image (RFC 2397 base64 variant): data_url slices the...
- `tab_close` (function) `include/tab.h:363` `void tab_close(tab *t);` -- variant): data_url slices the base64 payload out of `data_url` (no allocation, no network -- the bytes are already...
- `tab_page_free` (function) `include/tab.h:366` `void tab_page_free(tab_page *p);` -- malformed data: URI is not a transport error: *out stays zeroed, same as an * undecodable format, and the caller...
- `tab_eval_result_free` (function) `include/tab.h:367` `void tab_eval_result_free(tab_eval_result *r);`
- `tab_image_free` (function) `include/tab.h:368` `void tab_image_free(tab_image *img);`

## include/text_case.h
Imported by: `fuzz/fuzz_text_case.c`, `gui/browser_ui.c`, `src/text_case.c`, `tests/test_text_case.c`
- `cp` (function) `include/text_case.h:19` `* cp (identity otherwise), so a transformed text keeps its length. */ uint32_t tc_upper(uint32_t cp);`
- `tc_lower` (function) `include/text_case.h:21` `uint32_t tc_lower(uint32_t cp);`
- `tc_is_lower` (function) `include/text_case.h:24` `int tc_is_lower(uint32_t cp);` -- Simple 1:1 case mapping for ASCII, Latin-1, Latin Extended-A, basic Greek and basic Cyrillic.
- `tc_transform` (function) `include/text_case.h:29` `size_t tc_transform(const char *s, size_t n, int transform, int word_start, char *out, size_t cap);` -- Copies s[0,n) to out applying transform (CSS_TT_UPPERCASE / _LOWERCASE / _CAPITALIZE; any other value copies...
- `tc_smallcaps_runs` (function) `include/text_case.h:41` `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap);` -- Splits s[0,n) into consecutive maximal runs of lowercase letters vs the rest, covering the whole text in order.

## include/text_shape.h
Imported by: `fuzz/fuzz_text_shape.c`, `gui/browser_ui.c`, `src/freedom.c`, `src/text_shape.c`, `src/webfont_load.c`, `tests/test_text_shape.c`, `tests/test_webfont_load.c`
- `content` (function) `include/text_shape.h:11` `* TEXT is hostile remote content (sanitised UTF-8) and is fuzzed (make fuzz-tsh);`
- `tsh_family_is_generic` (function) `include/text_shape.h:52` `int tsh_family_is_generic(const char *name);` -- 1 for a CSS generic family keyword (serif, sans-serif, monospace, cursive, * fantasy, system-ui, ui-*, emoji, math...
- `wins` (function) `include/text_shape.h:58` `* the first name the resolver accepts wins (returns 1, family in out). Pure: the * resolver is injected (fontconfig...`
- `tsh_pick_family` (function) `include/text_shape.h:68` `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong, size_t n, int...` -- The acceptance rule for one requested name given fontconfig's substituted family list subs[0..n) and their bindings...
- `tsh_local_handle` (function) `include/text_shape.h:75` `int tsh_local_handle(const char *list);` -- Handle (>0) for an author family list that resolves to a local family, cached per list; 0 when nothing resolves, the...
- `tsh_ready` (function) `include/text_shape.h:89` `int tsh_ready(void);` -- 1 once a fallback (sans) font resolves; lazily initialises on first call. * 0 means no font backend: the caller must...
- `origin` (function) `include/text_shape.h:92` `* glyphs are written with positions relative to origin (0,0) on the baseline, * and *out_adv holds the total pen...`
- `tsh_measure` (function) `include/text_shape.h:101` `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len);` -- Total advance (px) of [text,len).
- `tsh_webfont_register` (function) `include/text_shape.h:114` `int tsh_webfont_register(const char *name, const unsigned char *bytes, size_t nbytes, int bold, int italic);` -- Registers one fetched @font-face for this document (spec/webfont.md): name is the author family (hashed with...
- `tsh_webfont_clear` (function) `include/text_shape.h:120` `void tsh_webfont_clear(void);` -- Drops every registered webfont (document teardown / navigation).
- `tsh_face` (function) `include/text_shape.h:127` `cairo_font_face_t *tsh_face(const tsh_font *f);` -- The cairo face tsh_draw paints f with (webfont, local family or bucket), or NULL when no face resolves.
- `own` (function) `include/text_shape.h:136` `* face of their own (controls, combining marks, variation selectors, ZWJ/ZWNJ) * stay in the run before them....`
- `tsh_shutdown` (function) `include/text_shape.h:143` `void tsh_shutdown(void);` -- Splits [text,len) into maximal runs of one face.

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
Imported by: `gui/browser_ui.c`, `gui/freedom_view.c`, `gui/ui_render.c`, `src/freedom.c`, `src/ui_layout.c`, `tests/test_ui.c`
- `space` (function) `include/ui.h:43` `* Breaks at the last fitting space (the break space is consumed), hard-breaks * words longer than max_cols, and...`
- `ui_layout_free` (function) `include/ui.h:51` `void ui_layout_free(ui_layout *lay);` -- Word-wraps text into lines of at most max_cols columns (monospace model).
- `ui_clamp_scroll` (function) `include/ui.h:54` `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines);` -- Word-wraps text into lines of at most max_cols columns (monospace model).
- `available` (function) `include/ui.h:85` `* cheapest artifact to inspect a render where no display is available (CI, an AI * agent): export, then read the PNG...`
- `out` (function) `include/ui.h:97` `* ui_render_png does and fills *out (jg_init'ed by the caller) with one rect per * element in document coordinates...`
- `placeholders` (function) `include/ui.h:107` `* above always draw image placeholders (no worker to decode hostile bytes);`
- `disk` (function) `include/ui.h:112` `* images are read from disk (confined to the document directory by render_doc). * top_url is the page origin (https...`
- `images` (function) `include/ui.h:114` `* fetcher loads no images (placeholders, as before). Any image that fails falls back * to its placeholder...`
- `ui_render_viewport_w` (function) `include/ui.h:141` `int ui_render_viewport_w(void);` -- The fixed canvas width (px) every headless render (ui_render_png/pdf, ui_dump_layout) lays out at.

## include/url.h
Imported by: `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_url.c`, `gui/browser_ui.c`, `include/form.h`, `include/js_dom.h`, `include/js_location.h`, `src/freedom.c`, `src/js_location.c`, `src/link_nav.c`, `src/prefetch.c`, `src/render_doc.c`, `src/secure_fetch.c`, `src/tab.c`, `src/url.c`, `src/webfont_load.c`, `tests/test_js_dom.c`, `tests/test_tab.c`, `tests/test_url.c`
- `url_is_https` (function) `include/url.h:42` `int url_is_https(const char *s);` -- Nonzero iff s begins (case-insensitively) with "https://" and the host is * neither empty nor a leading '/'.
- `url_has_scheme` (function) `include/url.h:46` `int url_has_scheme(const char *s);` -- Nonzero iff s begins with "<scheme>:" per RFC 3986 * (ALPHA *( ALPHA / DIGIT / "+" / "-" / "." ) ":").
- `url_authority_len` (function) `include/url.h:51` `size_t url_authority_len(const char *url);` -- Length of "https://host[:port]" within a validated absolute https URL: the index of the first '/', '?' or '#' after...
- `URL_ERR_NOT_HTTPS` (function) `include/url.h:109` `* URL_ERR_NOT_HTTPS (out untouched);`
- `path` (function) `include/url.h:115` `* absolute path ("file:///..."). NULL => 0. */ int url_is_file(const char *s);`
- `url_file_path` (function) `include/url.h:121` `const char *url_file_path(const char *s);` -- Returns the absolute filesystem path inside a "file:///path" URL (i.e. the "/path" part), or NULL when s is not a...
- `url` (function) `include/url.h:126` `* Every field ALIASES the input url (not owned, valid while url is alive);`
- `password` (function) `include/url.h:152` `* username and password (owned, must be freed) into *username_out and * *password_out, and returns URL_OK. When...`

## include/util.h
Imported by: `src/browser.c`, `src/disk_store.c`, `src/dom.c`, `src/hostblock.c`, `src/html_parse.c`, `src/media_decoder.c`, `src/page_view.c`, `src/render_doc.c`, `src/renderer.c`, `src/tab.c`
- `write_full` (function) `include/util.h:15` `static inline int write_full(int fd, const void *buf, size_t n)`
- `read_full` (function) `include/util.h:26` `static inline int read_full(int fd, void *buf, size_t n)`
- `mem_contains_ci` (function) `include/util.h:43` `static inline int mem_contains_ci(const void *hay, size_t hlen, const char *needle)` -- Returns 1 when the trusted lowercase-ASCII needle (letters/digits) occurs in the hostile, length-delimited haystack...
- `utf8_seq_len` (function) `include/util.h:57` `static inline size_t utf8_seq_len(unsigned char c)`
- `fnv1a` (function) `include/util.h:67` `static inline uint64_t fnv1a(const char *s, size_t n)`

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
Imported by: `fuzz/fuzz_webfont.c`, `gui/browser_ui.c`, `src/css.c`, `src/freedom.c`, `src/text_shape.c`, `src/webfont.c`, `src/webfont_load.c`, `tests/test_css.c`, `tests/test_page_view.c`, `tests/test_text_shape.c`, `tests/test_webfont.c`, `tests/test_webfont_load.c`
- `here` (function) `include/webfont.h:38` `* set with the decoded bytes owned here (freed by wf_list_free);`
- `wf_scan` (function) `include/webfont.h:52` `int wf_scan(const char *css, size_t len, wf_list *out);`
- `wf_list_free` (function) `include/webfont.h:53` `void wf_list_free(wf_list *l);`
- `boundaries` (function) `include/webfont.h:57` `* boundaries (scan_inline accumulation, loader collection). */ void wf_ref_move(wf_ref *dst, wf_ref *src);`
- `wf_supported_format` (function) `include/webfont.h:60` `int wf_supported_format(const char *fmt);`
- `wf_name_hash` (function) `include/webfont.h:69` `static inline unsigned wf_name_hash(const char *s, size_t n)` -- FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.


Next: [API_p5.md](API_p5.md)
