# API (page 10 of 14)
Previous: [API_p9.md](API_p9.md)

## src/js_dom.c
Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_intl.h`, `include/js_sandbox.h`, `include/web_storage.h`, `src/js_custom_elements.h`, `src/js_dom_ext.h`, `src/js_dom_internal.h`, `src/js_location_internal.h`, `src/js_native_internal.h`
- `jd_opaque_get` (function) `src/js_dom.c:27` `jd_opaque *jd_opaque_get(JSContext *ctx)`
- `jd_idx` (function) `src/js_dom.c:31` `dom_index *jd_idx(JSContext *ctx)`
- `jd_handle` (function) `src/js_dom.c:40` `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out)` -- Coerces a JS argument to a node handle.
- `jd_handle_or_null` (function) `src/js_dom.c:47` `JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h)`
- `m_node_count` (function) `src/js_dom.c:53` `static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,
                            in...`
- `m_get_element_by_id` (function) `src/js_dom.c:59` `static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val,
                       ...`
- `jd_query_list` (function) `src/js_dom.c:70` `static JSValue jd_query_list(JSContext *ctx, JSValueConst arg, int by_class)` -- return JS_NewInt64(ctx, (int64_t)dom_node_count(jd_idx(ctx))); } static JSValue m_get_element_by_id(JSContext *ctx...
- `m_get_by_tag` (function) `src/js_dom.c:100` `static JSValue m_get_by_tag(JSContext *ctx, JSValueConst this_val,
                            in...`
- `m_get_by_class` (function) `src/js_dom.c:106` `static JSValue m_get_by_class(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_tag_name` (function) `src/js_dom.c:112` `static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_get_attribute` (function) `src/js_dom.c:122` `static JSValue m_get_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
- `m_parent` (function) `src/js_dom.c:135` `static JSValue m_parent(JSContext *ctx, JSValueConst this_val,
                        int argc, ...`
- `m_first_child` (function) `src/js_dom.c:143` `static JSValue m_first_child(JSContext *ctx, JSValueConst this_val,
                             ...`
- `m_node_kind` (function) `src/js_dom.c:152` `static JSValue m_node_kind(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` -- dom_node_id h; if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION; return jd_handle_or_null(ctx...
- `m_child_node` (function) `src/js_dom.c:159` `static JSValue m_child_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
- `m_sibling_node` (function) `src/js_dom.c:166` `static JSValue m_sibling_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
- `m_create_char` (function) `src/js_dom.c:174` `static JSValue m_create_char(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` -- (void)this_val; (void)argc; dom_node_id h; if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION; return...
- `m_next_sibling` (function) `src/js_dom.c:188` `static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_precedes` (function) `src/js_dom.c:196` `static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_text_content` (function) `src/js_dom.c:207` `static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_set_text` (function) `src/js_dom.c:217` `static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_get_title` (function) `src/js_dom.c:231` `static JSValue m_get_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
- `m_set_title` (function) `src/js_dom.c:239` `static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
- `m_create_element` (function) `src/js_dom.c:252` `static JSValue m_create_element(JSContext *ctx, JSValueConst this_val,
                          ...`
- `m_append_child` (function) `src/js_dom.c:264` `static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_move_children` (function) `src/js_dom.c:275` `static JSValue m_move_children(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` -- dom.moveChildren(src, parent, where, ref|null): every child node of src (text * included) into parent at where (0...
- `m_clone_node` (function) `src/js_dom.c:289` `static JSValue m_clone_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` -- static JSValue m_move_children(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {...
- `m_insert_before` (function) `src/js_dom.c:299` `static JSValue m_insert_before(JSContext *ctx, JSValueConst this_val,
                           ...` -- return JS_NewBool(ctx, dom_move_children(jd_idx(ctx), src, parent, (dom_place)where, ref) == DOM_OK); } /*...
- `m_remove_child` (function) `src/js_dom.c:311` `static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_set_attribute` (function) `src/js_dom.c:320` `static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
- `m_remove_attribute` (function) `src/js_dom.c:336` `static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,
                        ...`
- `m_set_inner_html` (function) `src/js_dom.c:348` `static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...`
- `m_get_inner_html` (function) `src/js_dom.c:364` `static JSValue m_get_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...` -- innerHTML getter (2026-07-11): serializes the node's children (bounded in dom.c; * over-cap or invalid handle yields...
- `m_rect` (function) `src/js_dom.c:399` `static JSValue m_rect(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` -- dom.rect(h): [x, y, w, h] of h in document coordinates from the installed * layout geometry, or null (no table, or...
- `m_computed` (function) `src/js_dom.c:420` `static JSValue m_computed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` -- dom.computed(h, prop): the cascade's computed value of `prop` (kebab-case) for h as a string, "" for an unknown...
- `m_query_selector` (function) `src/js_dom.c:465` `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,
                          ...` -- return a; } /* --- install --- typedef struct jd_method { const char *name; JSCFunction *fn; int          nargs; }...
- `m_query_selector_all` (function) `src/js_dom.c:480` `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,
                      ...` -- int argc, JSValueConst *argv) { (void)this_val; (void)argc; dom_node_id root; if (jd_handle(ctx, argv[0], &root) <...
- `m_matches` (function) `src/js_dom.c:514` `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,
                         int argc...`
- `m_closest` (function) `src/js_dom.c:526` `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,
                         int argc...`
- `m_attr_names` (function) `src/js_dom.c:538` `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,
                            in...`
- `jd_is_mutator` (function) `src/js_dom.c:605` `static int jd_is_mutator(const char *name)`
- `jd_freeze_mutators` (function) `src/js_dom.c:611` `static int jd_freeze_mutators(JSContext *jsctx)`
- `table` (function) `src/js_dom.c:645` `* a table (dom.viewport() non-null);`
- `attrNames` (function) `src/js_dom.c:697` `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so
     * a missing '...`
- `scripts` (function) `src/js_dom.c:916` `* player scripts (canPlayType feature-detection, play/pause, muted/loop * reflection, buffered ranges) run without...`
- `enough` (function) `src/js_dom.c:1089` `* enough (cloneNode/lastChild/removeChild/insertBefore) that library feature * detection does not throw: jQuery...`
- `ms` (function) `src/js_dom.c:1236` `* due is the remaining virtual ms (the trusted parent advances the clock via * OP_TICK -> __tickTimers(elapsed);`
- `empty` (function) `src/js_dom.c:1437` `* inert: DOM interface constructors are empty (instanceof yields false, harmless);`
- `geometry` (function) `src/js_dom.c:1439` `* constant geometry (zero real leak);`
- `size` (function) `src/js_dom.c:1442` `* the viewport reads a fixed normalized size (matches the 1920 width * anti_fp uses for @media, not the real window);`
- `js_env` (function) `src/js_dom.c:1445` `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the
 * document shim (uses...`
- `jd_install` (function) `src/js_dom.c:1999` `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)`
- `jd_rebind` (function) `src/js_dom.c:2083` `jd_status jd_rebind(js_context *ctx, dom_index *idx, jd_opaque *from, jd_opaque *to)`
- `jd_flush_custom_elements` (function) `src/js_dom.c:2093` `void jd_flush_custom_elements(js_context *ctx)`
- `fails` (function) `src/js_dom.c:2107` `* cap is reached or an allocation fails (caller stops), else 0. */
static int cb_append(char **bu...`
- `jd_install_console` (function) `src/js_dom.c:2221` `jd_status jd_install_console(js_context *ctx, fb_buffer *log)`
- `jd_set_cookies` (function) `src/js_dom.c:2258` `jd_status jd_set_cookies(js_context *ctx, const char *cookies)`
- `jd_get_cookies` (function) `src/js_dom.c:2278` `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)`
- `jd_set_computed` (function) `src/js_dom.c:2301` `jd_status jd_set_computed(js_context *ctx, jd_computed_fn fn, void *fn_ctx)`
- `jd_set_geometry` (function) `src/js_dom.c:2312` `jd_status jd_set_geometry(js_context *ctx, const jg_table *geom)`

## src/js_dom_ext.c
Depends on: `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_ext.h`, `src/js_native_internal.h`
- `identity` (function) `src/js_dom_ext.c:105` `* identity (host/shadowRoot/mode preserved) but every mutation ALSO mirrors * into the host's light DOM via dom.*...`
- `registration` (function) `src/js_dom_ext.c:482` `* registration (options, attributeFilter, subtree) and delivered in one microtask. An
 * observer...`
- `cancels` (function) `src/js_dom_ext.c:1001` `* toggled BEFORE the dispatch and restored when a listener cancels (legacy pre-activation);`
- `run` (function) `src/js_dom_ext.c:1350` `static int run(JSContext *ctx, const char *src, size_t len, const char *name)`
- `order` (function) `src/js_dom_ext.c:1365` `* run in insertion order (HTML's "list of scripts that will execute in order as soon as
 * possib...`
- `jdx_install` (function) `src/js_dom_ext.c:1431` `int jdx_install(JSContext *ctx)`
- `jd_install_repl_api` (function) `src/js_dom_ext.c:1440` `jd_status jd_install_repl_api(js_context *ctx)`
- `jd_set_repl_css` (function) `src/js_dom_ext.c:1448` `jd_status jd_set_repl_css(js_context *ctx, const char *css, size_t len)`
- `jd_install_geolocation` (function) `src/js_dom_ext.c:1461` `jd_status jd_install_geolocation(js_context *ctx, double lat, double lon, double accuracy_m)`
- `jd_install_indexeddb` (function) `src/js_dom_ext.c:1480` `jd_status jd_install_indexeddb(js_context *ctx)`

## src/js_dom_ext.h
Imported by: `src/js_dom.c`, `src/js_dom_ext.c`
- `jdx_install` (function) `src/js_dom_ext.h:10` `int jdx_install(JSContext *ctx);`

## src/js_dom_internal.h
Depends on: `include/dom.h`, `include/js_dom.h`
Imported by: `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`
- `jd_opaque_get` (function) `src/js_dom_internal.h:11` `jd_opaque *jd_opaque_get(JSContext *ctx);`
- `jd_idx` (function) `src/js_dom_internal.h:12` `dom_index *jd_idx(JSContext *ctx);`
- `jd_handle` (function) `src/js_dom_internal.h:14` `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out);` -- Private to the js_dom family (js_dom.c, js_fetch.c, js_events.c, js_embed.c): * the context accessors every native...

## src/js_embed.c
Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`, `src/js_native_internal.h`
- `try_create_iframe_from_script` (function) `src/js_embed.c:87` `static int try_create_iframe_from_script(dom_index *idx,
                                        ...` -- Scans an inline script body for `video[N]` or `video_data` assignment and extracts the first usable iframe src.
- `jd_video_from_scripts` (function) `src/js_embed.c:204` `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,
                   ...`
- `jd_inject_video_shim` (function) `src/js_embed.c:243` `jd_status jd_inject_video_shim(js_context *ctx)`
- `scan_video_url` (function) `src/js_embed.c:257` `static int scan_video_url(const char *body, size_t blen,
                           char *out, si...` -- Scans a body buffer for `.m3u8` (HLS) or `.mp4` (progressive) video URLs.
- `jd_process_iframes` (function) `src/js_embed.c:295` `void jd_process_iframes(js_context *ctx, dom_index *idx,
                        jd_fetch_fn fn, ...`

## src/js_env.c
Depends on: `include/anti_fp.h`, `include/js_env.h`, `include/js_sandbox.h`, `include/sha2.h`, `src/js_native_internal.h`
- `primitives` (function) `src/js_env.c:6` `* the pure anti_fp primitives (one audited source of normalized constants);`
- `wall_clock_ms` (function) `src/js_env.c:37` `static uint64_t wall_clock_ms(void)`
- `monotonic_ms` (function) `src/js_env.c:43` `static double monotonic_ms(void)`
- `m_date_now` (function) `src/js_env.c:51` `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_perf_now` (function) `src/js_env.c:59` `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,
                          int ar...` -- performance.now: coarsened elapsed since the origin bound at install time, so * it never leaks the host uptime.
- `m_date_now_exact` (function) `src/js_env.c:73` `static JSValue m_date_now_exact(JSContext *ctx, JSValueConst this_val,
                          ...` -- Trusted-host clocks (owner decision 2026-10-26): 1 ms like a stock Firefox, no coarse grid, and *...
- `m_perf_now_exact` (function) `src/js_env.c:79` `static JSValue m_perf_now_exact(JSContext *ctx, JSValueConst this_val,
                          ...`
- `m_empty_array` (function) `src/js_env.c:99` `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,
                             ...`
- `m_get_random_values` (function) `src/js_env.c:117` `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,
                       ...`
- `m_random_uuid` (function) `src/js_env.c:147` `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,
                             ...`
- `m_subtle_null` (function) `src/js_env.c:164` `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,
                             ...`
- `reject_named` (function) `src/js_env.c:173` `static JSValue reject_named(JSContext *ctx, const char *name, const char *msg)` -- Rejected promise carrying an Error of the given name (WebCrypto reports through DOMException * names; the engine has...
- `m_subtle_digest` (function) `src/js_env.c:190` `static JSValue m_subtle_digest(JSContext *ctx, JSValueConst this_val,
                           ...` -- crypto.subtle.digest(algorithm, data): a Promise of the ArrayBuffer digest.
- `def_val` (function) `src/js_env.c:243` `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)` -- Always takes ownership of v: JS_DefinePropertyValueStr consumes it (freeing it even when the define fails).
- `def_str` (function) `src/js_env.c:249` `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)`
- `def_int` (function) `src/js_env.c:253` `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)`
- `def_fn` (function) `src/js_env.c:257` `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,
                  JSCFuncti...`
- `build_languages` (function) `src/js_env.c:264` `static JSValue build_languages(JSContext *ctx, const char *langs)` -- navigator.languages: a sealed array built by splitting fp_accept_language() * (e.g. "en-US,en") on commas.
- `m_captured` (function) `src/js_env.c:299` `static JSValue m_captured(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv,
  ...` -- An object with a prototype of its own. jn_seal turns that private prototype into the interface prototype...
- `promote_to_getters` (function) `src/js_env.c:307` `static int promote_to_getters(JSContext *ctx, JSValueConst vals, JSValueConst proto)` -- Moves every own property of `vals` onto `proto` as an enumerable, configurable getter * named "get <key>" with no...
- `build_navigator` (function) `src/js_env.c:332` `static int build_navigator(JSContext *ctx, JSValueConst global, const char *ua_override,
        ...`
- `build_screen` (function) `src/js_env.c:424` `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)`
- `build_crypto` (function) `src/js_env.c:468` `static int build_crypto(JSContext *ctx, JSValueConst global)`
- `build_perf_timing` (function) `src/js_env.c:496` `static int build_perf_timing(JSContext *ctx, JSValueConst perf)`
- `build_perf_navigation` (function) `src/js_env.c:510` `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)`
- `build_performance` (function) `src/js_env.c:522` `static int build_performance(JSContext *ctx, JSValueConst global, int exact)`
- `override_date_now` (function) `src/js_env.c:554` `static int override_date_now(JSContext *ctx, JSValueConst global, int exact)` -- Replaces the built-in Date.now with the coarsened version, non-writable and * non-configurable so a script cannot...
- `make_readback` (function) `src/js_env.c:598` `static JSValue make_readback(JSContext *ctx, uint64_t key)`
- `build_readback_obj` (function) `src/js_env.c:606` `static int build_readback_obj(JSContext *ctx, JSValueConst global,
                              ...`
- `je_install` (function) `src/js_env.c:619` `je_status je_install(js_context *ctx, int screen_w, int screen_h)`
- `je_install_identity` (function) `src/js_env.c:623` `je_status je_install_identity(js_context *ctx, int screen_w, int screen_h,
                      ...`
- `je_install_identity_trusted` (function) `src/js_env.c:628` `je_status je_install_identity_trusted(js_context *ctx, int screen_w, int screen_h,
              ...`
- `je_install_canvas` (function) `src/js_env.c:649` `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)`

## src/js_events.c
Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`, `src/js_native_internal.h`
- `jd_click_state_new` (function) `src/js_events.c:30` `jd_click_state *jd_click_state_new(void)`
- `jd_click_state_free` (function) `src/js_events.c:35` `void jd_click_state_free(jd_click_state *s)`
- `jd_install_events` (function) `src/js_events.c:39` `jd_status jd_install_events(js_context *ctx, jd_click_state *state)`
- `jd_eval_default_action` (function) `src/js_events.c:53` `static int jd_eval_default_action(JSContext *jsctx, const char *src, size_t n,
                  ...` -- Runs one engine event-dispatch expression and maps its result to the C contract: 1 = default action proceeds, 0 = a...
- `jd_fire_click` (function) `src/js_events.c:67` `int jd_fire_click(js_context *ctx, dom_node_id node_id)`
- `jd_fire_submit` (function) `src/js_events.c:79` `int jd_fire_submit(js_context *ctx, dom_node_id form_node_id)` -- Fires the submit event for form_node_id.
- `jd_escape_js_str` (function) `src/js_events.c:92` `static size_t jd_escape_js_str(const char *src, char *dst, size_t dstsz)` -- Escapes a string for safe interpolation into JS double-quoted string literal: replaces backslash with \\ and...
- `jd_fire_mouse_event` (function) `src/js_events.c:164` `int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,
                        const char ...`

## src/js_fetch.c
Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`, `src/js_native_internal.h`
- `jd_pack_ptr` (function) `src/js_fetch.c:29` `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)` -- Carry the host fetch fn + its ctx as a function's closure data, each split into 32-bit halves (no assumption about...
- `jd_unpack_ptr` (function) `src/js_fetch.c:34` `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)`
- `jd_reply_object` (function) `src/js_fetch.c:44` `static JSValue jd_reply_object(JSContext *ctx, int rc, int status, const char *rbody,
           ...` -- The object the shim sees for one reply (shared by the synchronous host call and the deferred * delivery).
- `m_host_fetch` (function) `src/js_fetch.c:74` `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,
                            in...` -- __hostFetch(method, url, body) -> { status, body, contentType }.
- `m_host_fetch_async` (function) `src/js_fetch.c:105` `static JSValue m_host_fetch_async(JSContext *ctx, JSValueConst this_val,
                        ...` -- __hostFetchAsync(method, url, body, headers) -> bool: queues the request with the host and * returns at once; the...
- `send` (function) `src/js_fetch.c:128` `* callbacks fire right after send();`
- `task` (function) `src/js_fetch.c:312` `* current task (the page never waits on it);`
- `jd_install_xhr` (function) `src/js_fetch.c:336` `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)`
- `jd_net_deliver` (function) `src/js_fetch.c:340` `jd_status jd_net_deliver(js_context *ctx, int pos, int rc, int status, const char *body, size_t l...`
- `jd_install_xhr_ex` (function) `src/js_fetch.c:363` `jd_status jd_install_xhr_ex(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx,
                   ...`

## src/js_geom.c
Depends on: `include/js_geom.h`
- `jg_init` (function) `src/js_geom.c:17` `void jg_init(jg_table *t)`
- `jg_free` (function) `src/js_geom.c:21` `void jg_free(jg_table *t)`
- `clamp_coord` (function) `src/js_geom.c:27` `static int32_t clamp_coord(double v, double lo)`
- `grow` (function) `src/js_geom.c:33` `static int grow(jg_table *t)`
- `push` (function) `src/js_geom.c:45` `static int push(jg_table *t, dom_node_id node, int32_t x, int32_t y, int32_t w, int32_t h)`
- `jg_add` (function) `src/js_geom.c:52` `int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h)`
- `unite` (function) `src/js_geom.c:63` `static int unite(jg_rect *a, const jg_rect *b)` -- Bounding box of a and b into a; returns 1 if a changed.
- `cmp_node` (function) `src/js_geom.c:78` `static int cmp_node(const void *pa, const void *pb)`
- `jg_finish` (function) `src/js_geom.c:83` `int jg_finish(jg_table *t)`
- `jg_find` (function) `src/js_geom.c:96` `const jg_rect *jg_find(const jg_table *t, dom_node_id node)`
- `slot_of` (function) `src/js_geom.c:102` `static uint32_t slot_of(dom_node_id n)`
- `index_of` (function) `src/js_geom.c:109` `static size_t index_of(jg_table *t, uint32_t *slots, dom_node_id node, const jg_rect *seed,
     ...` -- Index of node in t->r via the local hash, inserting an empty-at-rect entry * (a copy of seed) when absent.
- `jg_aggregate` (function) `src/js_geom.c:124` `int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx)`
- `jg_wire_len` (function) `src/js_geom.c:163` `size_t jg_wire_len(const jg_table *t)`
- `jg_encode` (function) `src/js_geom.c:167` `int jg_encode(const jg_table *t, int32_t *out, size_t cap)`
- `in_range` (function) `src/js_geom.c:182` `static int in_range(int32_t v, int32_t lo)`
- `jg_decode` (function) `src/js_geom.c:186` `int jg_decode(const int32_t *in, size_t n, jg_table *out)`
- `fnv` (function) `src/js_geom.c:212` `static uint64_t fnv(uint64_t h, int32_t v)`
- `jg_hash` (function) `src/js_geom.c:221` `uint64_t jg_hash(const jg_table *t)`

## src/js_intl.c
Depends on: `include/js_intl.h`
- `ji_install` (function) `src/js_intl.c:423` `int ji_install(js_context *ctx)`

## src/js_location.c
Depends on: `include/js_dom.h`, `include/url.h`, `src/js_location_internal.h`, `src/js_native_internal.h`
- `jd_lp_set` (function) `src/js_location.c:25` `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,
                      const ...` -- Defines a string property on the __locParts data object from a (ptr,len) span. * The span is copied into an engine...
- `jl_m_hist_target` (function) `src/js_location.c:36` `JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` -- dom.histTarget(base, ref): the same-origin target of history.pushState/replaceState (url_history_target) as a...
- `jd_set_location` (function) `src/js_location.c:160` `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)`
- `jd_take_nav_request` (function) `src/js_location.c:194` `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)`
- `numbers` (function) `src/js_location.c:233` `* numbers (never as source);`
- `jd_take_scroll` (function) `src/js_location.c:237` `int jd_take_scroll(js_context *ctx, double out[JD_SCROLL_N])`
- `jd_take_history` (function) `src/js_location.c:272` `char *jd_take_history(js_context *ctx, int *go)`
- `jd_frag_push` (function) `src/js_location.c:303` `int jd_frag_push(js_context *ctx, const char *url, int replace)`
- `jd_pop_state` (function) `src/js_location.c:327` `int jd_pop_state(js_context *ctx, int index)`

## src/js_location_internal.h
Imported by: `src/js_dom.c`, `src/js_location.c`
- `header` (function) `src/js_location_internal.h:6` `* stay out of every public header (include/ never sees quickjs.h). */ #include "quickjs.h" JSValue...`

## src/js_native.c
Depends on: `include/css.h`, `include/js_native.h`, `src/js_native_internal.h`
- `jn_host_eval` (function) `src/js_native.c:15` `JSValue jn_host_eval(JSContext *c, const char *src, size_t len, const char *name)`
- `jn_css_ok` (function) `src/js_native.c:25` `static JSValue jn_css_ok(JSContext *c, JSValueConst this_val, int argc, JSValueConst *argv)` -- __cssOk(decl): 1 when the cascade keeps `decl` ("prop: value") whole.
- `jn_seal` (function) `src/js_native.c:144` `int jn_seal(js_context *ctx)`

## src/js_native_internal.h
Imported by: `src/js_custom_elements.c`, `src/js_dom.c`, `src/js_dom_ext.c`, `src/js_embed.c`, `src/js_env.c`, `src/js_events.c`, `src/js_fetch.c`, `src/js_location.c`, `src/js_native.c`, `src/js_trusted.c`
- `js_host_slot` (function) `src/js_native_internal.h:21` `JSValue *js_host_slot(struct js_context *ctx);`

## src/js_policy.c
Depends on: `include/js_policy.h`
- `eq_ci` (function) `src/js_policy.c:12` `static int eq_ci(const char *a, const char *b)` -- js_policy — implementation: pure per-host JavaScript policy decision.
- `jsp_enabled` (function) `src/js_policy.c:22` `bool jsp_enabled(jsp_mode mode, int host_allowlisted)`
- `jsp_trusted` (function) `src/js_policy.c:31` `bool jsp_trusted(bool js_enabled, int host_allowlisted)`
- `jsp_present_trusted` (function) `src/js_policy.c:35` `bool jsp_present_trusted(int host_allowlisted)`
- `jsp_mode_from_str` (function) `src/js_policy.c:39` `jsp_mode jsp_mode_from_str(const char *s)`
- `jsp_mode_str` (function) `src/js_policy.c:51` `const char *jsp_mode_str(jsp_mode mode)`

## src/js_sandbox.c
Depends on: `include/js_sandbox.h`
- `js_host_slot` (function) `src/js_sandbox.c:76` `JSValue *js_host_slot(struct js_context *ctx)` -- int                  prof_on; struct timespec      prof_last; unsigned             prof_total; size_t...
- `rej_remove` (function) `src/js_sandbox.c:82` `static void rej_remove(js_context *c, size_t i)`
- `js_rejection_cb` (function) `src/js_sandbox.c:90` `static void js_rejection_cb(JSContext *jc, JSValueConst promise, JSValueConst reason,
           ...`
- `rej_report` (function) `src/js_sandbox.c:109` `static void rej_report(js_context *c)` -- Hands each still-unhandled rejection to the page, oldest first.
- `jm_malloc` (function) `src/js_sandbox.c:134` `static void *jm_malloc(void *opaque, size_t size)`
- `jm_calloc` (function) `src/js_sandbox.c:142` `static void *jm_calloc(void *opaque, size_t count, size_t size)`
- `jm_free` (function) `src/js_sandbox.c:152` `static void jm_free(void *opaque, void *ptr)`
- `jm_realloc` (function) `src/js_sandbox.c:158` `static void *jm_realloc(void *opaque, void *ptr, size_t size)`
- `jm_usable_size` (function) `src/js_sandbox.c:168` `static size_t jm_usable_size(const void *ptr)`
- `host_dup` (function) `src/js_sandbox.c:178` `static char *host_dup(const char *src, size_t len)`
- `timespec_reached` (function) `src/js_sandbox.c:187` `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)`
- `timespec_diff_ms` (function) `src/js_sandbox.c:192` `static long timespec_diff_ms(const struct timespec *a, const struct timespec *b)`
- `profile_sample` (function) `src/js_sandbox.c:197` `static void profile_sample(js_context *c, unsigned weight_ms)` -- out[len] = '\0'; return out; } static int timespec_reached(const struct timespec *now, const struct timespec...
- `js_profile_enable` (function) `src/js_sandbox.c:229` `void js_profile_enable(js_context *ctx)`
- `js_profile_report` (function) `src/js_sandbox.c:235` `size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n)`
- `throw_key` (function) `src/js_sandbox.c:258` `static void throw_key(JSContext *ctx, JSValueConst obj, char *key, size_t cap)` -- if (!used[i] && (best == ctx->prof_n || ctx->prof[i].hits > ctx->prof[best].hits)) best = i; if (best ==...
- `throw_hook_cb` (function) `src/js_sandbox.c:315` `static void throw_hook_cb(JSContext *ctx, JSValueConst obj, void *opaque)`
- `js_throws_enable` (function) `src/js_sandbox.c:335` `void js_throws_enable(js_context *ctx)`
- `js_throws_report` (function) `src/js_sandbox.c:341` `size_t js_throws_report(js_context *ctx, char *out, size_t cap, size_t top_n)`
- `m_fb_report` (function) `src/js_sandbox.c:363` `static JSValue m_fb_report(JSContext *jsctx, JSValueConst this_val, int argc, JSValueConst *argv,...` -- for (size_t i = 0; i < ctx->thr_n; i++) if (!used[i] && (best == ctx->thr_n || ctx->thr[i].hits >...
- `js_devtools_enable` (function) `src/js_sandbox.c:379` `void js_devtools_enable(js_context *ctx)`
- `js_devtools_expose` (function) `src/js_sandbox.c:385` `js_status js_devtools_expose(js_context *ctx)`
- `js_interrupt_cb` (function) `src/js_sandbox.c:401` `static int js_interrupt_cb(JSRuntime *rt, void *opaque)` -- uint64_t u = (uint64_t)(uintptr_t)ctx; static const char *const names[2] = { "__fbProfile", "__fbThrows" }; JSValue...
- `is_ascii_digit` (function) `src/js_sandbox.c:425` `static int is_ascii_digit(char c)`
- `js_loc_from_stack` (function) `src/js_sandbox.c:427` `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      i...`
- `undefined` (function) `src/js_sandbox.c:519` `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx...`
- `js_stack_limit_for` (function) `src/js_sandbox.c:546` `size_t js_stack_limit_for(size_t soft_stack)`
- `process_soft_stack` (function) `src/js_sandbox.c:557` `static size_t process_soft_stack(void)`
- `js_prime_stack_limit` (function) `src/js_sandbox.c:567` `void js_prime_stack_limit(void)`
- `js_limits_default` (function) `src/js_sandbox.c:569` `js_limits js_limits_default(void)`
- `limits_resolve` (function) `src/js_sandbox.c:578` `static js_limits limits_resolve(const js_limits *lim)`
- `js_validate_source` (function) `src/js_sandbox.c:587` `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)`
- `js_context_new` (function) `src/js_sandbox.c:598` `js_status js_context_new(const js_limits *lim, js_context **out)`
- `js_context_free` (function) `src/js_sandbox.c:639` `void js_context_free(js_context *ctx)`
- `arm_deadline` (function) `src/js_sandbox.c:652` `static void arm_deadline(js_context *ctx, uint64_t budget_ms)`
- `js_set_time_budget` (function) `src/js_sandbox.c:667` `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)`
- `js_eval` (function) `src/js_sandbox.c:672` `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)`
- `js_eval_named` (function) `src/js_sandbox.c:676` `js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        con...`
- `js_pump_jobs` (function) `src/js_sandbox.c:759` `int js_pump_jobs(js_context *ctx, int max_jobs)`
- `js_eval_once` (function) `src/js_sandbox.c:778` `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)`
- `js_result_free` (function) `src/js_sandbox.c:791` `void js_result_free(js_result *res)`
- `js_set_current_script` (function) `src/js_sandbox.c:819` `void js_set_current_script(js_context *ctx, const char *src, const char *type)`
- `js_context_raw` (function) `src/js_sandbox.c:855` `void *js_context_raw(js_context *ctx)`
- `mod_set_meta` (function) `src/js_sandbox.c:887` `static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url)` -- size_t cap = nlen + JS_MODULE_URL_MAX; char *out = (char *)calloc(cap, 1); if (out == NULL) {...
- `mod_loader` (function) `src/js_sandbox.c:896` `static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque)` -- free(out); return r; } /* Sets import.meta.url of a compiled module to its absolute URL. static void...
- `mod_normalize` (function) `src/js_sandbox.c:932` `static char *mod_normalize(JSContext *jc, const char *base, const char *name, void *opaque);`
- `js_set_module_host` (function) `src/js_sandbox.c:935` `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,
                        js...`
- `mod_fail` (function) `src/js_sandbox.c:950` `static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,
      ...` -- Fills res from the pending exception (or the given rejection value, which is * thrown first so the one capture path...
- `js_eval_module` (function) `src/js_sandbox.c:965` `js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,
        ...`
- `realm_of` (function) `src/js_sandbox.c:1032` `static JSContext *realm_of(js_context *c, JSValueConst g)` -- The owning js_context rides in each native's closure data, split into 32-bit * halves (no assumption about JS number...
- `throw_named` (function) `src/js_sandbox.c:1045` `static JSValue throw_named(JSContext *ctx, const char *name, const char *msg)`
- `m_realm_new` (function) `src/js_sandbox.c:1055` `static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,
                     ...`
- `m_realm_eval` (function) `src/js_sandbox.c:1069` `static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,
                    ...` -- __realmEval(global, code, name): a classic script in that realm.
- `m_realm_clone` (function) `src/js_sandbox.c:1105` `static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,
                   ...` -- __realmClone(value, global): structured copy into global's realm through the * serializer WITHOUT bytecode -- a...
- `js_install_realms` (function) `src/js_sandbox.c:1127` `js_status js_install_realms(js_context *ctx)`

## src/js_trusted.c
Depends on: `include/js_trusted.h`, `include/web_storage.h`, `src/js_native_internal.h`
- `jt_enable_open` (function) `src/js_trusted.c:49` `jd_status jt_enable_open(js_context *ctx)`
- `jt_enable_observers` (function) `src/js_trusted.c:129` `jd_status jt_enable_observers(js_context *ctx)`
- `jt_geometry_changed` (function) `src/js_trusted.c:142` `jd_status jt_geometry_changed(js_context *ctx)`
- `jt_take_opens` (function) `src/js_trusted.c:157` `char *jt_take_opens(js_context *ctx)`
- `jt_enable_ws` (function) `src/js_trusted.c:234` `jd_status jt_enable_ws(js_context *ctx)`
- `jt_ws_ops_free` (function) `src/js_trusted.c:245` `void jt_ws_ops_free(jt_ws_op *ops, size_t n)`
- `hex_nibble` (function) `src/js_trusted.c:250` `static int hex_nibble(char c)`
- `ws_payload` (function) `src/js_trusted.c:257` `static char *ws_payload(int kind, const char *s, size_t n, size_t *out_len)` -- } void jt_ws_ops_free(jt_ws_op *ops, size_t n) { if (ops == NULL) return; for (size_t i = 0; i < n; ++i) {...
- `jt_take_ws` (function) `src/js_trusted.c:281` `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap)`
- `jt_ws_event` (function) `src/js_trusted.c:332` `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len)`
- `jt_enable_frames` (function) `src/js_trusted.c:428` `jd_status jt_enable_frames(js_context *ctx, int frame_id)`
- `jt_seed_pair` (function) `src/js_trusted.c:474` `static void jt_seed_pair(void *vctx, const char *k, size_t kl, const char *v, size_t vl)`
- `jt_enable_storage` (function) `src/js_trusted.c:484` `jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len)`
- `jt_take_storage` (function) `src/js_trusted.c:504` `int jt_take_storage(js_context *ctx, char **out, size_t *len)`
- `explicitly` (function) `src/js_trusted.c:552` `* explicitly (no window, no document). Delivery is always a timer task. */
static const char JT_W...`
- `jt_enable_worker` (function) `src/js_trusted.c:633` `jd_status jt_enable_worker(js_context *ctx)`

## src/link_nav.c
Depends on: `include/link_nav.h`, `include/url.h`
- `clean_href` (function) `src/link_nav.c:19` `static int clean_href(const char *href, char *out, size_t outsz)` -- Removes tab/newline/CR anywhere and trims leading/trailing spaces, in place * into out.
- `ci_prefix` (function) `src/link_nav.c:38` `static int ci_prefix(const char *s, const char *prefix)` -- if (o + 1 >= outsz) return -1; out[o++] = (char)c; } out[o] = '\0'; size_t start = 0; while (out[start] == ' ')...
- `classify_block` (function) `src/link_nav.c:62` `static ln_block_reason classify_block(const char *ref)` -- Splits the fragment (everything after the first '#') out of ref: copies the fragment id (without '#') into frag...
- `file_dir_len` (function) `src/link_nav.c:69` `static size_t file_dir_len(const char *base)` -- const char *f = hash + 1; size_t fl = strlen(f); if (fl + 1 <= fragsz) memcpy(frag, f, fl + 1); hash = '\0'; } /*...
- `last_seg_is_dotdot` (function) `src/link_nav.c:79` `static int last_seg_is_dotdot(const char *body, size_t blen)` -- return LN_BLOCK_UNSUPPORTED; } /* Length of base up to and including the last '/'; 0 when base has no '/'. static...
- `append_seg` (function) `src/link_nav.c:86` `static int append_seg(char *body, size_t bodysz, size_t *blen,
                      const char *...` -- for (size_t i = 0; base[i] != '\0'; ++i) { if (base[i] == '/') { last = i; found = 1; } } return found ? last + 1...
- `pop_seg` (function) `src/link_nav.c:98` `static void pop_seg(char *body, size_t *blen)` -- /* Appends seg to body (with a '/' separator when non-empty).
- `resolve_file` (function) `src/link_nav.c:149` `static int resolve_file(const char *base, const char *ref, char *out, size_t outsz)` -- Resolves a local file reference (relative or absolute path) against base into * out.
- `ln_resolve` (function) `src/link_nav.c:172` `ln_status ln_resolve(const char *base, const char *href, ln_result *out)`
- `ln_block_reason_text` (function) `src/link_nav.c:241` `const char *ln_block_reason_text(ln_block_reason reason)`

## src/link_preview.c
Depends on: `include/link_nav.h`, `include/link_preview.h`
- `put_raw` (function) `src/link_preview.c:17` `static void put_raw(lp_sink *s, const char *src, size_t n)`
- `put_escaped` (function) `src/link_preview.c:22` `static void put_escaped(lp_sink *s, const char *src, size_t n)`
- `host_span` (function) `src/link_preview.c:37` `static void host_span(const char *s, size_t n, size_t *off, size_t *len)` -- static const char hex[] = "0123456789ABCDEF"; for (size_t i = 0; i < n; ++i) { unsigned char c = (unsigned...
- `fit` (function) `src/link_preview.c:64` `static void fit(const char *s, size_t n, size_t hoff, size_t hlen, lp_preview *out)` -- Copies s[0..n) into out->text, eliding the middle of the path when it does not fit * and keeping scheme + host (+...
- `frag_free_len` (function) `src/link_preview.c:100` `static size_t frag_free_len(const char *base)`
- `lp_describe` (function) `src/link_preview.c:105` `lp_status lp_describe(const char *base, const char *href, lp_preview *out)`

## src/local_store.c
Depends on: `include/local_store.h`
- `cipher_for` (function) `src/local_store.c:69` `static const EVP_CIPHER *cipher_for(ls_aead aead)`
- `argon2id_derive` (function) `src/local_store.c:79` `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,
                          ...`
- `ls_derive_key` (function) `src/local_store.c:108` `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,
                        const...`
- `aead_encrypt` (function) `src/local_store.c:117` `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...`
- `aead_decrypt` (function) `src/local_store.c:143` `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...`
- `seal_core` (function) `src/local_store.c:171` `static ls_status seal_core(const uint8_t *key, ls_aead aead, uint8_t kdf_id,
                    ...`
- `decrypt_blob` (function) `src/local_store.c:208` `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,
         ...`
- `ls_seal` (function) `src/local_store.c:239` `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,
                  const uint8_t *p...`
- `ls_open` (function) `src/local_store.c:252` `ls_status ls_open(const uint8_t key[LS_KEY_LEN],
                  const uint8_t *blob, size_t bl...`
- `ls_seal_passphrase` (function) `src/local_store.c:263` `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,
          ...`
- `ls_open_passphrase` (function) `src/local_store.c:284` `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,
                        ...`
- `ls_free` (function) `src/local_store.c:304` `void ls_free(uint8_t *buf, size_t len)`

## src/mask_cache.c
Depends on: `include/mask_cache.h`
- `key_eq` (function) `src/mask_cache.c:22` `static int key_eq(const mkc_key *a, const mkc_key *b)` -- mkc_key        key; unsigned char *buf; size_t         bytes; int            stride; uint64_t       tick; }...
- `drop` (function) `src/mask_cache.c:28` `static void drop(mkc_cache *c, mkc_entry *e)`
- `find` (function) `src/mask_cache.c:36` `static mkc_entry *find(mkc_cache *c, const mkc_key *k)`
- `oldest` (function) `src/mask_cache.c:42` `static mkc_entry *oldest(mkc_cache *c)`
- `mkc_new` (function) `src/mask_cache.c:49` `mkc_cache *mkc_new(size_t byte_budget, size_t max_entries)`
- `mkc_clear` (function) `src/mask_cache.c:60` `void mkc_clear(mkc_cache *c)`
- `mkc_free` (function) `src/mask_cache.c:65` `void mkc_free(mkc_cache *c)`
- `mkc_get` (function) `src/mask_cache.c:72` `const unsigned char *mkc_get(mkc_cache *c, const mkc_key *k, int *stride)`
- `mkc_put` (function) `src/mask_cache.c:81` `unsigned char *mkc_put(mkc_cache *c, const mkc_key *k, int stride)`
- `mkc_bytes` (function) `src/mask_cache.c:111` `size_t mkc_bytes(const mkc_cache *c)`
- `mkc_count` (function) `src/mask_cache.c:113` `size_t mkc_count(const mkc_cache *c)`

## src/media_decoder.c
Depends on: `include/media_decoder.h`, `include/util.h`
- `open` (function) `src/media_decoder.c:18` `*
 * Sandbox: the decoder needs open() for shared libraries (.so loading) and
 * brk/mmap for FFm...`
- `decoder_close` (function) `src/media_decoder.c:78` `static void decoder_close(decoder_ctx *dc)` -- AVFrame         *frame;  /* decoded frame (YUV) AVFrame         *rgb;    /* converted frame (ARGB) AVFrame...
- `decoder_init` (function) `src/media_decoder.c:96` `static int decoder_init(decoder_ctx *dc, const uint8_t *data, size_t len)` -- Initialises the decoder from the first TS segment bytes.
- `frame_pts_us` (function) `src/media_decoder.c:215` `static int64_t frame_pts_us(const AVFrame *f, AVRational tb, int64_t fallback)` -- Rescales a decoded frame's PTS to microseconds using the time base of the * stream it came from; frames without a...
- `av_rescale_q` (function) `src/media_decoder.c:217` `return av_rescale_q(f->pts, tb, (AVRational)`
- `send_video_frame` (function) `src/media_decoder.c:222` `static void send_video_frame(decoder_ctx *dc, int64_t pts_us)` -- Converts the current dc->frame (YUV) to BGRA and sends it as MD_FRAME with * the given PTS in microseconds.
- `send_audio_frame` (function) `src/media_decoder.c:242` `static void send_audio_frame(decoder_ctx *dc, int64_t pts_us)` -- Converts the current dc->audio_frame to interleaved S16LE PCM and sends it as MD_AUDIO_FRAME with the given PTS in...
- `decode_segment` (function) `src/media_decoder.c:276` `static int decode_segment(decoder_ctx *dc, const uint8_t *data, size_t len)` -- Decodes one segment of TS data and sends frames.
- `dropped` (function) `src/media_decoder.c:369` `* the codec in permanent EOF state: every segment after the first decoded * one was silently dropped ("plays a...`
- `media_decoder_run` (function) `src/media_decoder.c:379` `void media_decoder_run(int out_fd, int cmd_fd)`
- `media_decoder_spawn` (function) `src/media_decoder.c:449` `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd)`
- `fd` (function) `src/media_decoder.c:469` `* prevent the Wayland display fd (inherited from the parent) from * surviving the exec. An inherited Wayland fd...`

## src/nav_token.c
Depends on: `include/nav_token.h`
- `nt_new` (function) `src/nav_token.c:16` `nt_token *nt_new(void)`
- `nt_ref` (function) `src/nav_token.c:26` `nt_token *nt_ref(nt_token *t)`
- `nt_unref` (function) `src/nav_token.c:31` `void nt_unref(nt_token **tp)`
- `nt_cancel` (function) `src/nav_token.c:38` `void nt_cancel(nt_token *t)`
- `nt_cancelled` (function) `src/nav_token.c:42` `int nt_cancelled(const nt_token *t)`
- `nt_set_foreground` (function) `src/nav_token.c:47` `void nt_set_foreground(nt_token *t, int on)`
- `nt_foreground` (function) `src/nav_token.c:51` `int nt_foreground(const nt_token *t)`
- `nt_id` (function) `src/nav_token.c:56` `uint64_t nt_id(const nt_token *t)`
- `nt_route` (function) `src/nav_token.c:58` `nt_route_kind nt_route(const nt_token *job, const nt_token *active, nt_token *const *parked,
    ...`

## src/net_guard.c
Depends on: `include/net_guard.h`
- `ng_v4_is_private` (function) `src/net_guard.c:12` `static int ng_v4_is_private(const unsigned char o[NG_V4_LEN])`
- `ng_seg` (function) `src/net_guard.c:29` `static unsigned ng_seg(const unsigned char a[NG_V6_LEN], int i)`
- `ng_v6_is_private` (function) `src/net_guard.c:33` `static int ng_v6_is_private(const unsigned char a[NG_V6_LEN])`
- `decides` (function) `src/net_guard.c:40` `* IPv4 decides (:: and ::1 embed 0.0.0.0 and 0.0.0.1, both in 0/8). */ if (head_zero && (s[5] == 0 || s[5] ==...`
- `ng_addr_is_private` (function) `src/net_guard.c:63` `int ng_addr_is_private(int family, const unsigned char *addr, size_t len)`
- `ng_parse` (function) `src/net_guard.c:71` `static int ng_parse(const char *text, int *family, unsigned char out[NG_V6_LEN])` -- if (s[0] == 0x2001 && s[1] == 0x0db8) return 1;              /* documentation if (s[0] == 0x3fff && (s[1] & 0xf000)...
- `ng_text_is_private` (function) `src/net_guard.c:84` `int ng_text_is_private(const char *ip_text)`
- `ng_host_is_ip` (function) `src/net_guard.c:91` `int ng_host_is_ip(const char *host)`
- `ng_ci_eq` (function) `src/net_guard.c:97` `static int ng_ci_eq(const char *a, const char *b, size_t n)`
- `ng_host_is_local` (function) `src/net_guard.c:107` `int ng_host_is_local(const char *host)`
- `ng_decide` (function) `src/net_guard.c:121` `ng_verdict ng_decide(const ng_request *r, int peer_private)`

## src/net_realm.c
Depends on: `include/net_realm.h`
- `lower` (function) `src/net_realm.c:17` `static char lower(char c)`
- `ends_with_realm` (function) `src/net_realm.c:23` `static int ends_with_realm(const char *host, size_t n, const char *suffix)` -- True if the lowercased host (length n) ends with ".suffix" AND has at least one * non-empty label before the dot....
- `nr_classify_host` (function) `src/net_realm.c:34` `nr_realm nr_classify_host(const char *host)`
- `host_of` (function) `src/net_realm.c:52` `static int host_of(const char *url, char *out, size_t out_size)` -- Extracts the host of scheme://host[:port][/...] into out (lowercased not required * here; nr_classify_host lowercases).
- `nr_classify_url` (function) `src/net_realm.c:68` `nr_realm nr_classify_url(const char *url)`
- `nr_route_for` (function) `src/net_realm.c:74` `nr_route nr_route_for(const char *url, nr_config cfg)`
- `nr_realm_allows_http` (function) `src/net_realm.c:88` `int nr_realm_allows_http(nr_realm r)`
- `nr_realm_name` (function) `src/net_realm.c:94` `const char *nr_realm_name(nr_realm r)`
- `nr_route_name` (function) `src/net_realm.c:103` `const char *nr_route_name(nr_route r)`


Next: [API_p11.md](API_p11.md)
