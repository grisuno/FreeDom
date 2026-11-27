# Symbols (page 10 of 19)
Previous: [SYMBOLS_p9.md](SYMBOLS_p9.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `jd_rebind` | function | `src/js_dom.c:2083` | `jd_status jd_rebind(js_context *ctx, dom_index *idx, jd_opaque *from, jd_opaque *to)` |
| `jd_set_computed` | function | `src/js_dom.c:2301` | `jd_status jd_set_computed(js_context *ctx, jd_computed_fn fn, void *fn_ctx)` |
| `jd_set_cookies` | function | `src/js_dom.c:2258` | `jd_status jd_set_cookies(js_context *ctx, const char *cookies)` |
| `jd_set_geometry` | function | `src/js_dom.c:2312` | `jd_status jd_set_geometry(js_context *ctx, const jg_table *geom)` |
| `js_env` | function | `src/js_dom.c:1445` | `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the  * document shim (uses...` |
| `m_append_child` | function | `src/js_dom.c:264` | `static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,                             ...` |
| `m_attr_names` | function | `src/js_dom.c:538` | `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,                             in...` |
| `m_child_node` | function | `src/js_dom.c:159` | `static JSValue m_child_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_clone_node` | function | `src/js_dom.c:289` | `static JSValue m_clone_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_closest` | function | `src/js_dom.c:526` | `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,                          int argc...` |
| `m_computed` | function | `src/js_dom.c:420` | `static JSValue m_computed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_create_char` | function | `src/js_dom.c:174` | `static JSValue m_create_char(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_create_element` | function | `src/js_dom.c:252` | `static JSValue m_create_element(JSContext *ctx, JSValueConst this_val,                           ...` |
| `m_first_child` | function | `src/js_dom.c:143` | `static JSValue m_first_child(JSContext *ctx, JSValueConst this_val,                              ...` |
| `m_get_attribute` | function | `src/js_dom.c:122` | `static JSValue m_get_attribute(JSContext *ctx, JSValueConst this_val,                            ...` |
| `m_get_by_class` | function | `src/js_dom.c:106` | `static JSValue m_get_by_class(JSContext *ctx, JSValueConst this_val,                             ...` |
| `m_get_by_tag` | function | `src/js_dom.c:100` | `static JSValue m_get_by_tag(JSContext *ctx, JSValueConst this_val,                             in...` |
| `m_get_element_by_id` | function | `src/js_dom.c:59` | `static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val,                        ...` |
| `m_get_inner_html` | function | `src/js_dom.c:364` | `static JSValue m_get_inner_html(JSContext *ctx, JSValueConst this_val,                           ...` |
| `m_get_title` | function | `src/js_dom.c:231` | `static JSValue m_get_title(JSContext *ctx, JSValueConst this_val,                            int ...` |
| `m_insert_before` | function | `src/js_dom.c:299` | `static JSValue m_insert_before(JSContext *ctx, JSValueConst this_val,                            ...` |
| `m_matches` | function | `src/js_dom.c:514` | `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,                          int argc...` |
| `m_move_children` | function | `src/js_dom.c:275` | `static JSValue m_move_children(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_next_sibling` | function | `src/js_dom.c:188` | `static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,                             ...` |
| `m_node_count` | function | `src/js_dom.c:53` | `static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,                             in...` |
| `m_node_kind` | function | `src/js_dom.c:152` | `static JSValue m_node_kind(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_parent` | function | `src/js_dom.c:135` | `static JSValue m_parent(JSContext *ctx, JSValueConst this_val,                         int argc, ...` |
| `m_precedes` | function | `src/js_dom.c:196` | `static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_query_selector` | function | `src/js_dom.c:465` | `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,                           ...` |
| `m_query_selector_all` | function | `src/js_dom.c:480` | `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,                       ...` |
| `m_rect` | function | `src/js_dom.c:399` | `static JSValue m_rect(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_remove_attribute` | function | `src/js_dom.c:336` | `static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,                         ...` |
| `m_remove_child` | function | `src/js_dom.c:311` | `static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,                             ...` |
| `m_set_attribute` | function | `src/js_dom.c:320` | `static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,                            ...` |
| `m_set_inner_html` | function | `src/js_dom.c:348` | `static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,                           ...` |
| `m_set_text` | function | `src/js_dom.c:217` | `static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_set_title` | function | `src/js_dom.c:239` | `static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,                            int ...` |
| `m_sibling_node` | function | `src/js_dom.c:166` | `static JSValue m_sibling_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_tag_name` | function | `src/js_dom.c:112` | `static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_text_content` | function | `src/js_dom.c:207` | `static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,                             ...` |
| `ms` | function | `src/js_dom.c:1236` | `* due is the remaining virtual ms (the trusted parent advances the clock via * OP_TICK -> __tickTimers(elapsed);` |
| `scripts` | function | `src/js_dom.c:916` | `* player scripts (canPlayType feature-detection, play/pause, muted/loop * reflection, buffered ranges) run without...` |
| `size` | function | `src/js_dom.c:1442` | `* the viewport reads a fixed normalized size (matches the 1920 width * anti_fp uses for @media, not the real window);` |
| `table` | function | `src/js_dom.c:645` | `* a table (dom.viewport() non-null);` |
| `cancels` | function | `src/js_dom_ext.c:1001` | `* toggled BEFORE the dispatch and restored when a listener cancels (legacy pre-activation);` |
| `identity` | function | `src/js_dom_ext.c:105` | `* identity (host/shadowRoot/mode preserved) but every mutation ALSO mirrors * into the host's light DOM via dom.*...` |
| `jd_install_geolocation` | function | `src/js_dom_ext.c:1461` | `jd_status jd_install_geolocation(js_context *ctx, double lat, double lon, double accuracy_m)` |
| `jd_install_indexeddb` | function | `src/js_dom_ext.c:1480` | `jd_status jd_install_indexeddb(js_context *ctx)` |
| `jd_install_repl_api` | function | `src/js_dom_ext.c:1440` | `jd_status jd_install_repl_api(js_context *ctx)` |
| `jd_set_repl_css` | function | `src/js_dom_ext.c:1448` | `jd_status jd_set_repl_css(js_context *ctx, const char *css, size_t len)` |
| `jdx_install` | function | `src/js_dom_ext.c:1431` | `int jdx_install(JSContext *ctx)` |
| `order` | function | `src/js_dom_ext.c:1365` | `* run in insertion order (HTML's "list of scripts that will execute in order as soon as  * possib...` |
| `registration` | function | `src/js_dom_ext.c:482` | `* registration (options, attributeFilter, subtree) and delivered in one microtask. An  * observer...` |
| `run` | function | `src/js_dom_ext.c:1350` | `static int run(JSContext *ctx, const char *src, size_t len, const char *name)` |
| `FREEDOM_JS_DOM_EXT_H` | macro | `src/js_dom_ext.h:2` | `#define FREEDOM_JS_DOM_EXT_H` |
| `jdx_install` | function | `src/js_dom_ext.h:10` | `int jdx_install(JSContext *ctx);` |
| `FREEDOM_JS_DOM_INTERNAL_H` | macro | `src/js_dom_internal.h:2` | `#define FREEDOM_JS_DOM_INTERNAL_H` |
| `jd_handle` | function | `src/js_dom_internal.h:14` | `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out);` |
| `jd_idx` | function | `src/js_dom_internal.h:12` | `dom_index *jd_idx(JSContext *ctx);` |
| `jd_opaque_get` | function | `src/js_dom_internal.h:11` | `jd_opaque *jd_opaque_get(JSContext *ctx);` |
| `_GNU_SOURCE` | macro | `src/js_embed.c:6` | `#define _GNU_SOURCE` |
| `jd_inject_video_shim` | function | `src/js_embed.c:243` | `jd_status jd_inject_video_shim(js_context *ctx)` |
| `jd_process_iframes` | function | `src/js_embed.c:295` | `void jd_process_iframes(js_context *ctx, dom_index *idx,                         jd_fetch_fn fn, ...` |
| `jd_video_from_scripts` | function | `src/js_embed.c:204` | `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,                    ...` |
| `scan_video_url` | function | `src/js_embed.c:257` | `static int scan_video_url(const char *body, size_t blen,                            char *out, si...` |
| `try_create_iframe_from_script` | function | `src/js_embed.c:87` | `static int try_create_iframe_from_script(dom_index *idx,                                         ...` |
| `PERF_ORIGIN_EPOCH` | macro | `src/js_env.c:466` | `#define PERF_ORIGIN_EPOCH` |
| `_POSIX_C_SOURCE` | macro | `src/js_env.c:17` | `#define _POSIX_C_SOURCE` |
| `build_crypto` | function | `src/js_env.c:468` | `static int build_crypto(JSContext *ctx, JSValueConst global)` |
| `build_languages` | function | `src/js_env.c:264` | `static JSValue build_languages(JSContext *ctx, const char *langs)` |
| `build_navigator` | function | `src/js_env.c:332` | `static int build_navigator(JSContext *ctx, JSValueConst global, const char *ua_override,         ...` |
| `build_perf_navigation` | function | `src/js_env.c:510` | `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)` |
| `build_perf_timing` | function | `src/js_env.c:496` | `static int build_perf_timing(JSContext *ctx, JSValueConst perf)` |
| `build_performance` | function | `src/js_env.c:522` | `static int build_performance(JSContext *ctx, JSValueConst global, int exact)` |
| `build_readback_obj` | function | `src/js_env.c:606` | `static int build_readback_obj(JSContext *ctx, JSValueConst global,                               ...` |
| `build_screen` | function | `src/js_env.c:424` | `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)` |
| `def_fn` | function | `src/js_env.c:257` | `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,                   JSCFuncti...` |
| `def_int` | function | `src/js_env.c:253` | `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)` |
| `def_str` | function | `src/js_env.c:249` | `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)` |
| `def_val` | function | `src/js_env.c:243` | `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)` |
| `je_install` | function | `src/js_env.c:619` | `je_status je_install(js_context *ctx, int screen_w, int screen_h)` |
| `je_install_canvas` | function | `src/js_env.c:649` | `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)` |
| `je_install_identity` | function | `src/js_env.c:623` | `je_status je_install_identity(js_context *ctx, int screen_w, int screen_h,                       ...` |
| `je_install_identity_trusted` | function | `src/js_env.c:628` | `je_status je_install_identity_trusted(js_context *ctx, int screen_w, int screen_h,               ...` |
| `m_captured` | function | `src/js_env.c:299` | `static JSValue m_captured(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv,   ...` |
| `m_date_now` | function | `src/js_env.c:51` | `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_date_now_exact` | function | `src/js_env.c:73` | `static JSValue m_date_now_exact(JSContext *ctx, JSValueConst this_val,                           ...` |
| `m_empty_array` | function | `src/js_env.c:99` | `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,                              ...` |
| `m_get_random_values` | function | `src/js_env.c:117` | `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,                        ...` |
| `m_perf_now` | function | `src/js_env.c:59` | `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_perf_now_exact` | function | `src/js_env.c:79` | `static JSValue m_perf_now_exact(JSContext *ctx, JSValueConst this_val,                           ...` |
| `m_random_uuid` | function | `src/js_env.c:147` | `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,                              ...` |
| `m_subtle_digest` | function | `src/js_env.c:190` | `static JSValue m_subtle_digest(JSContext *ctx, JSValueConst this_val,                            ...` |
| `m_subtle_null` | function | `src/js_env.c:164` | `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,                              ...` |
| `make_readback` | function | `src/js_env.c:598` | `static JSValue make_readback(JSContext *ctx, uint64_t key)` |
| `monotonic_ms` | function | `src/js_env.c:43` | `static double monotonic_ms(void)` |
| `override_date_now` | function | `src/js_env.c:554` | `static int override_date_now(JSContext *ctx, JSValueConst global, int exact)` |
| `primitives` | function | `src/js_env.c:6` | `* the pure anti_fp primitives (one audited source of normalized constants);` |
| `promote_to_getters` | function | `src/js_env.c:307` | `static int promote_to_getters(JSContext *ctx, JSValueConst vals, JSValueConst proto)` |
| `reject_named` | function | `src/js_env.c:173` | `static JSValue reject_named(JSContext *ctx, const char *name, const char *msg)` |
| `wall_clock_ms` | function | `src/js_env.c:37` | `static uint64_t wall_clock_ms(void)` |
| `_GNU_SOURCE` | macro | `src/js_events.c:6` | `#define _GNU_SOURCE` |
| `jd_click_state` | struct | `src/js_events.c:26` | `` |
| `jd_click_state_free` | function | `src/js_events.c:35` | `void jd_click_state_free(jd_click_state *s)` |
| `jd_click_state_new` | function | `src/js_events.c:30` | `jd_click_state *jd_click_state_new(void)` |
| `jd_escape_js_str` | function | `src/js_events.c:92` | `static size_t jd_escape_js_str(const char *src, char *dst, size_t dstsz)` |
| `jd_eval_default_action` | function | `src/js_events.c:53` | `static int jd_eval_default_action(JSContext *jsctx, const char *src, size_t n,                   ...` |
| `jd_fire_click` | function | `src/js_events.c:67` | `int jd_fire_click(js_context *ctx, dom_node_id node_id)` |
| `jd_fire_mouse_event` | function | `src/js_events.c:164` | `int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,                         const char ...` |
| `jd_fire_submit` | function | `src/js_events.c:79` | `int jd_fire_submit(js_context *ctx, dom_node_id form_node_id)` |
| `jd_install_events` | function | `src/js_events.c:39` | `jd_status jd_install_events(js_context *ctx, jd_click_state *state)` |
| `_GNU_SOURCE` | macro | `src/js_fetch.c:6` | `#define _GNU_SOURCE` |
| `jd_install_xhr` | function | `src/js_fetch.c:336` | `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)` |
| `jd_install_xhr_ex` | function | `src/js_fetch.c:363` | `jd_status jd_install_xhr_ex(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx,                    ...` |
| `jd_net_deliver` | function | `src/js_fetch.c:340` | `jd_status jd_net_deliver(js_context *ctx, int pos, int rc, int status, const char *body, size_t l...` |
| `jd_pack_ptr` | function | `src/js_fetch.c:29` | `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)` |
| `jd_reply_object` | function | `src/js_fetch.c:44` | `static JSValue jd_reply_object(JSContext *ctx, int rc, int status, const char *rbody,            ...` |
| `jd_unpack_ptr` | function | `src/js_fetch.c:34` | `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)` |
| `m_host_fetch` | function | `src/js_fetch.c:74` | `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,                             in...` |
| `m_host_fetch_async` | function | `src/js_fetch.c:105` | `static JSValue m_host_fetch_async(JSContext *ctx, JSValueConst this_val,                         ...` |
| `send` | function | `src/js_fetch.c:128` | `* callbacks fire right after send();` |
| `task` | function | `src/js_fetch.c:312` | `* current task (the page never waits on it);` |
| `JG_INDEX_SLOTS` | macro | `src/js_geom.c:14` | `#define JG_INDEX_SLOTS` |
| `JG_SLOT_EMPTY` | macro | `src/js_geom.c:15` | `#define JG_SLOT_EMPTY` |
| `clamp_coord` | function | `src/js_geom.c:27` | `static int32_t clamp_coord(double v, double lo)` |
| `cmp_node` | function | `src/js_geom.c:78` | `static int cmp_node(const void *pa, const void *pb)` |
| `fnv` | function | `src/js_geom.c:212` | `static uint64_t fnv(uint64_t h, int32_t v)` |
| `grow` | function | `src/js_geom.c:33` | `static int grow(jg_table *t)` |
| `in_range` | function | `src/js_geom.c:182` | `static int in_range(int32_t v, int32_t lo)` |
| `index_of` | function | `src/js_geom.c:109` | `static size_t index_of(jg_table *t, uint32_t *slots, dom_node_id node, const jg_rect *seed,      ...` |
| `jg_add` | function | `src/js_geom.c:52` | `int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h)` |
| `jg_aggregate` | function | `src/js_geom.c:124` | `int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx)` |
| `jg_decode` | function | `src/js_geom.c:186` | `int jg_decode(const int32_t *in, size_t n, jg_table *out)` |
| `jg_encode` | function | `src/js_geom.c:167` | `int jg_encode(const jg_table *t, int32_t *out, size_t cap)` |
| `jg_find` | function | `src/js_geom.c:96` | `const jg_rect *jg_find(const jg_table *t, dom_node_id node)` |
| `jg_finish` | function | `src/js_geom.c:83` | `int jg_finish(jg_table *t)` |
| `jg_free` | function | `src/js_geom.c:21` | `void jg_free(jg_table *t)` |
| `jg_hash` | function | `src/js_geom.c:221` | `uint64_t jg_hash(const jg_table *t)` |
| `jg_init` | function | `src/js_geom.c:17` | `void jg_init(jg_table *t)` |
| `jg_wire_len` | function | `src/js_geom.c:163` | `size_t jg_wire_len(const jg_table *t)` |
| `push` | function | `src/js_geom.c:45` | `static int push(jg_table *t, dom_node_id node, int32_t x, int32_t y, int32_t w, int32_t h)` |
| `slot_of` | function | `src/js_geom.c:102` | `static uint32_t slot_of(dom_node_id n)` |
| `unite` | function | `src/js_geom.c:63` | `static int unite(jg_rect *a, const jg_rect *b)` |
| `ji_install` | function | `src/js_intl.c:423` | `int ji_install(js_context *ctx)` |
| `jd_frag_push` | function | `src/js_location.c:303` | `int jd_frag_push(js_context *ctx, const char *url, int replace)` |
| `jd_lp_set` | function | `src/js_location.c:25` | `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,                       const ...` |
| `jd_pop_state` | function | `src/js_location.c:327` | `int jd_pop_state(js_context *ctx, int index)` |
| `jd_set_location` | function | `src/js_location.c:160` | `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)` |
| `jd_take_history` | function | `src/js_location.c:272` | `char *jd_take_history(js_context *ctx, int *go)` |
| `jd_take_nav_request` | function | `src/js_location.c:194` | `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)` |
| `jd_take_scroll` | function | `src/js_location.c:237` | `int jd_take_scroll(js_context *ctx, double out[JD_SCROLL_N])` |
| `jl_m_hist_target` | function | `src/js_location.c:36` | `JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `numbers` | function | `src/js_location.c:233` | `* numbers (never as source);` |
| `FREEDOM_JS_LOCATION_INTERNAL_H` | macro | `src/js_location_internal.h:2` | `#define FREEDOM_JS_LOCATION_INTERNAL_H` |
| `header` | function | `src/js_location_internal.h:6` | `* stay out of every public header (include/ never sees quickjs.h). */ #include "quickjs.h" JSValue...` |
| `JN_SUPPORTS_MAX` | macro | `src/js_native.c:13` | `#define JN_SUPPORTS_MAX` |
| `jn_css_ok` | function | `src/js_native.c:25` | `static JSValue jn_css_ok(JSContext *c, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `jn_host_eval` | function | `src/js_native.c:15` | `JSValue jn_host_eval(JSContext *c, const char *src, size_t len, const char *name)` |
| `jn_seal` | function | `src/js_native.c:144` | `int jn_seal(js_context *ctx)` |
| `FREEDOM_JS_NATIVE_INTERNAL_H` | macro | `src/js_native_internal.h:6` | `#define FREEDOM_JS_NATIVE_INTERNAL_H` |
| `js_context` | struct | `src/js_native_internal.h:20` | `` |
| `js_host_slot` | function | `src/js_native_internal.h:21` | `JSValue *js_host_slot(struct js_context *ctx);` |
| `eq_ci` | function | `src/js_policy.c:12` | `static int eq_ci(const char *a, const char *b)` |
| `jsp_enabled` | function | `src/js_policy.c:22` | `bool jsp_enabled(jsp_mode mode, int host_allowlisted)` |
| `jsp_mode_from_str` | function | `src/js_policy.c:39` | `jsp_mode jsp_mode_from_str(const char *s)` |
| `jsp_mode_str` | function | `src/js_policy.c:51` | `const char *jsp_mode_str(jsp_mode mode)` |
| `jsp_present_trusted` | function | `src/js_policy.c:35` | `bool jsp_present_trusted(int host_allowlisted)` |
| `jsp_trusted` | function | `src/js_policy.c:31` | `bool jsp_trusted(bool js_enabled, int host_allowlisted)` |
| `JS_MODULE_URL_MAX` | macro | `src/js_sandbox.c:860` | `#define JS_MODULE_URL_MAX` |
| `JS_PROFILE_KEY_MAX` | macro | `src/js_sandbox.c:36` | `#define JS_PROFILE_KEY_MAX` |
| `JS_PROFILE_SLOTS` | macro | `src/js_sandbox.c:35` | `#define JS_PROFILE_SLOTS` |
| `_POSIX_C_SOURCE` | macro | `src/js_sandbox.c:12` | `#define _POSIX_C_SOURCE` |
| `arm_deadline` | function | `src/js_sandbox.c:652` | `static void arm_deadline(js_context *ctx, uint64_t budget_ms)` |
| `host_dup` | function | `src/js_sandbox.c:178` | `static char *host_dup(const char *src, size_t len)` |
| `is_ascii_digit` | function | `src/js_sandbox.c:425` | `static int is_ascii_digit(char c)` |
| `jm_calloc` | function | `src/js_sandbox.c:142` | `static void *jm_calloc(void *opaque, size_t count, size_t size)` |
| `jm_free` | function | `src/js_sandbox.c:152` | `static void jm_free(void *opaque, void *ptr)` |
| `jm_malloc` | function | `src/js_sandbox.c:134` | `static void *jm_malloc(void *opaque, size_t size)` |
| `jm_realloc` | function | `src/js_sandbox.c:158` | `static void *jm_realloc(void *opaque, void *ptr, size_t size)` |
| `jm_usable_size` | function | `src/js_sandbox.c:168` | `static size_t jm_usable_size(const void *ptr)` |
| `js_context` | struct | `src/js_sandbox.c:38` | `` |
| `js_context_free` | function | `src/js_sandbox.c:639` | `void js_context_free(js_context *ctx)` |
| `js_context_new` | function | `src/js_sandbox.c:598` | `js_status js_context_new(const js_limits *lim, js_context **out)` |
| `js_context_raw` | function | `src/js_sandbox.c:855` | `void *js_context_raw(js_context *ctx)` |
| `js_devtools_enable` | function | `src/js_sandbox.c:379` | `void js_devtools_enable(js_context *ctx)` |
| `js_devtools_expose` | function | `src/js_sandbox.c:385` | `js_status js_devtools_expose(js_context *ctx)` |
| `js_eval` | function | `src/js_sandbox.c:672` | `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)` |
| `js_eval_module` | function | `src/js_sandbox.c:965` | `js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,         ...` |
| `js_eval_named` | function | `src/js_sandbox.c:676` | `js_status js_eval_named(js_context *ctx, const char *src, size_t len,                         con...` |
| `js_eval_once` | function | `src/js_sandbox.c:778` | `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)` |
| `js_host_slot` | function | `src/js_sandbox.c:76` | `JSValue *js_host_slot(struct js_context *ctx)` |
| `js_install_realms` | function | `src/js_sandbox.c:1127` | `js_status js_install_realms(js_context *ctx)` |
| `js_interrupt_cb` | function | `src/js_sandbox.c:401` | `static int js_interrupt_cb(JSRuntime *rt, void *opaque)` |
| `js_limits_default` | function | `src/js_sandbox.c:569` | `js_limits js_limits_default(void)` |
| `js_loc_from_stack` | function | `src/js_sandbox.c:427` | `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,                       i...` |
| `js_mem_state` | struct | `src/js_sandbox.c:29` | `` |
| `js_prime_stack_limit` | function | `src/js_sandbox.c:567` | `void js_prime_stack_limit(void)` |
| `js_profile_enable` | function | `src/js_sandbox.c:229` | `void js_profile_enable(js_context *ctx)` |
| `js_profile_report` | function | `src/js_sandbox.c:235` | `size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n)` |
| `js_pump_jobs` | function | `src/js_sandbox.c:759` | `int js_pump_jobs(js_context *ctx, int max_jobs)` |
| `js_rejection_cb` | function | `src/js_sandbox.c:90` | `static void js_rejection_cb(JSContext *jc, JSValueConst promise, JSValueConst reason,            ...` |
| `js_result_free` | function | `src/js_sandbox.c:791` | `void js_result_free(js_result *res)` |
| `js_set_current_script` | function | `src/js_sandbox.c:819` | `void js_set_current_script(js_context *ctx, const char *src, const char *type)` |
| `js_set_module_host` | function | `src/js_sandbox.c:935` | `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,                         js...` |
| `js_set_time_budget` | function | `src/js_sandbox.c:667` | `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)` |
| `js_stack_limit_for` | function | `src/js_sandbox.c:546` | `size_t js_stack_limit_for(size_t soft_stack)` |
| `js_throws_enable` | function | `src/js_sandbox.c:335` | `void js_throws_enable(js_context *ctx)` |
| `js_throws_report` | function | `src/js_sandbox.c:341` | `size_t js_throws_report(js_context *ctx, char *out, size_t cap, size_t top_n)` |
| `js_validate_source` | function | `src/js_sandbox.c:587` | `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)` |
| `limit` | type_alias | `src/js_sandbox.c:29` | `typedef struct js_mem_state { size_t limit;` |
| `limits_resolve` | function | `src/js_sandbox.c:578` | `static js_limits limits_resolve(const js_limits *lim)` |
| `m_fb_report` | function | `src/js_sandbox.c:363` | `static JSValue m_fb_report(JSContext *jsctx, JSValueConst this_val, int argc, JSValueConst *argv,...` |
| `m_realm_clone` | function | `src/js_sandbox.c:1105` | `static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,                    ...` |
| `m_realm_eval` | function | `src/js_sandbox.c:1069` | `static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,                     ...` |
| `m_realm_new` | function | `src/js_sandbox.c:1055` | `static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,                      ...` |
| `mod_fail` | function | `src/js_sandbox.c:950` | `static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,       ...` |
| `mod_loader` | function | `src/js_sandbox.c:896` | `static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque)` |
| `mod_normalize` | function | `src/js_sandbox.c:932` | `static char *mod_normalize(JSContext *jc, const char *base, const char *name, void *opaque);` |
| `mod_set_meta` | function | `src/js_sandbox.c:887` | `static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url)` |
| `process_soft_stack` | function | `src/js_sandbox.c:557` | `static size_t process_soft_stack(void)` |
| `profile_sample` | function | `src/js_sandbox.c:197` | `static void profile_sample(js_context *c, unsigned weight_ms)` |
| `realm_of` | function | `src/js_sandbox.c:1032` | `static JSContext *realm_of(js_context *c, JSValueConst g)` |
| `rej_remove` | function | `src/js_sandbox.c:82` | `static void rej_remove(js_context *c, size_t i)` |
| `rej_report` | function | `src/js_sandbox.c:109` | `static void rej_report(js_context *c)` |
| `throw_hook_cb` | function | `src/js_sandbox.c:315` | `static void throw_hook_cb(JSContext *ctx, JSValueConst obj, void *opaque)` |
| `throw_key` | function | `src/js_sandbox.c:258` | `static void throw_key(JSContext *ctx, JSValueConst obj, char *key, size_t cap)` |
| `throw_named` | function | `src/js_sandbox.c:1045` | `static JSValue throw_named(JSContext *ctx, const char *name, const char *msg)` |
| `timespec_diff_ms` | function | `src/js_sandbox.c:192` | `static long timespec_diff_ms(const struct timespec *a, const struct timespec *b)` |
| `timespec_reached` | function | `src/js_sandbox.c:187` | `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)` |
| `undefined` | function | `src/js_sandbox.c:519` | `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx...` |
| `JT_IO_MAX_STR` | macro | `src/js_trusted.c:62` | `#define JT_IO_MAX_STR` |
| `explicitly` | function | `src/js_trusted.c:552` | `* explicitly (no window, no document). Delivery is always a timer task. */ static const char JT_W...` |
| `hex_nibble` | function | `src/js_trusted.c:250` | `static int hex_nibble(char c)` |
| `jt_enable_frames` | function | `src/js_trusted.c:428` | `jd_status jt_enable_frames(js_context *ctx, int frame_id)` |
| `jt_enable_observers` | function | `src/js_trusted.c:129` | `jd_status jt_enable_observers(js_context *ctx)` |
| `jt_enable_open` | function | `src/js_trusted.c:49` | `jd_status jt_enable_open(js_context *ctx)` |
| `jt_enable_storage` | function | `src/js_trusted.c:484` | `jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len)` |
| `jt_enable_worker` | function | `src/js_trusted.c:633` | `jd_status jt_enable_worker(js_context *ctx)` |
| `jt_enable_ws` | function | `src/js_trusted.c:234` | `jd_status jt_enable_ws(js_context *ctx)` |
| `jt_geometry_changed` | function | `src/js_trusted.c:142` | `jd_status jt_geometry_changed(js_context *ctx)` |
| `jt_seed_ctx` | struct | `src/js_trusted.c:472` | `` |
| `jt_seed_pair` | function | `src/js_trusted.c:474` | `static void jt_seed_pair(void *vctx, const char *k, size_t kl, const char *v, size_t vl)` |
| `jt_take_opens` | function | `src/js_trusted.c:157` | `char *jt_take_opens(js_context *ctx)` |
| `jt_take_storage` | function | `src/js_trusted.c:504` | `int jt_take_storage(js_context *ctx, char **out, size_t *len)` |
| `jt_take_ws` | function | `src/js_trusted.c:281` | `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap)` |
| `jt_ws_event` | function | `src/js_trusted.c:332` | `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len)` |
| `jt_ws_ops_free` | function | `src/js_trusted.c:245` | `void jt_ws_ops_free(jt_ws_op *ops, size_t n)` |
| `ws_payload` | function | `src/js_trusted.c:257` | `static char *ws_payload(int kind, const char *s, size_t n, size_t *out_len)` |
| `append_seg` | function | `src/link_nav.c:86` | `static int append_seg(char *body, size_t bodysz, size_t *blen,                       const char *...` |
| `ci_prefix` | function | `src/link_nav.c:38` | `static int ci_prefix(const char *s, const char *prefix)` |
| `classify_block` | function | `src/link_nav.c:62` | `static ln_block_reason classify_block(const char *ref)` |
| `clean_href` | function | `src/link_nav.c:19` | `static int clean_href(const char *href, char *out, size_t outsz)` |
| `file_dir_len` | function | `src/link_nav.c:69` | `static size_t file_dir_len(const char *base)` |
| `last_seg_is_dotdot` | function | `src/link_nav.c:79` | `static int last_seg_is_dotdot(const char *body, size_t blen)` |
| `ln_block_reason_text` | function | `src/link_nav.c:241` | `const char *ln_block_reason_text(ln_block_reason reason)` |
| `ln_resolve` | function | `src/link_nav.c:172` | `ln_status ln_resolve(const char *base, const char *href, ln_result *out)` |
| `pop_seg` | function | `src/link_nav.c:98` | `static void pop_seg(char *body, size_t *blen)` |
| `resolve_file` | function | `src/link_nav.c:149` | `static int resolve_file(const char *base, const char *ref, char *out, size_t outsz)` |
| `fit` | function | `src/link_preview.c:64` | `static void fit(const char *s, size_t n, size_t hoff, size_t hlen, lp_preview *out)` |
| `frag_free_len` | function | `src/link_preview.c:100` | `static size_t frag_free_len(const char *base)` |
| `host_span` | function | `src/link_preview.c:37` | `static void host_span(const char *s, size_t n, size_t *off, size_t *len)` |
| `lp_describe` | function | `src/link_preview.c:105` | `lp_status lp_describe(const char *base, const char *href, lp_preview *out)` |
| `lp_sink` | struct | `src/link_preview.c:12` | `` |
| `put_escaped` | function | `src/link_preview.c:22` | `static void put_escaped(lp_sink *s, const char *src, size_t n)` |
| `put_raw` | function | `src/link_preview.c:17` | `static void put_raw(lp_sink *s, const char *src, size_t n)` |
| `LS_ARGON2_M_KIB` | macro | `src/local_store.c:54` | `#define LS_ARGON2_M_KIB` |
| `LS_ARGON2_P` | macro | `src/local_store.c:55` | `#define LS_ARGON2_P` |
| `LS_ARGON2_T` | macro | `src/local_store.c:53` | `#define LS_ARGON2_T` |
| `LS_KDF_ARGON2ID` | macro | `src/local_store.c:50` | `#define LS_KDF_ARGON2ID` |
| `LS_KDF_NONE` | macro | `src/local_store.c:49` | `#define LS_KDF_NONE` |
| `LS_VERSION` | macro | `src/local_store.c:48` | `#define LS_VERSION` |
| `OFF_AEAD` | macro | `src/local_store.c:60` | `#define OFF_AEAD` |
| `OFF_KDF` | macro | `src/local_store.c:61` | `#define OFF_KDF` |
| `OFF_MAGIC` | macro | `src/local_store.c:58` | `#define OFF_MAGIC` |
| `OFF_NONCE` | macro | `src/local_store.c:63` | `#define OFF_NONCE` |
| `OFF_SALT` | macro | `src/local_store.c:62` | `#define OFF_SALT` |
| `OFF_VERSION` | macro | `src/local_store.c:59` | `#define OFF_VERSION` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:25` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:39` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:28` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:42` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:31` | `#define OSSL_KDF_PARAM_THREADS` |
| `OSSL_KDF_PARAM_THREADS` | macro | `src/local_store.c:45` | `#define OSSL_KDF_PARAM_THREADS` |
| `_GNU_SOURCE` | macro | `src/local_store.c:13` | `#define _GNU_SOURCE` |
| `aead_decrypt` | function | `src/local_store.c:143` | `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,                      ...` |
| `aead_encrypt` | function | `src/local_store.c:117` | `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,                      ...` |
| `argon2id_derive` | function | `src/local_store.c:79` | `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,                           ...` |
| `cipher_for` | function | `src/local_store.c:69` | `static const EVP_CIPHER *cipher_for(ls_aead aead)` |
| `decrypt_blob` | function | `src/local_store.c:208` | `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,          ...` |
| `ls_derive_key` | function | `src/local_store.c:108` | `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,                         const...` |
| `ls_free` | function | `src/local_store.c:304` | `void ls_free(uint8_t *buf, size_t len)` |
| `ls_open` | function | `src/local_store.c:252` | `ls_status ls_open(const uint8_t key[LS_KEY_LEN],                   const uint8_t *blob, size_t bl...` |
| `ls_open_passphrase` | function | `src/local_store.c:284` | `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,                         ...` |
| `ls_seal` | function | `src/local_store.c:239` | `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,                   const uint8_t *p...` |
| `ls_seal_passphrase` | function | `src/local_store.c:263` | `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,           ...` |
| `seal_core` | function | `src/local_store.c:171` | `static ls_status seal_core(const uint8_t *key, ls_aead aead, uint8_t kdf_id,                     ...` |
| `drop` | function | `src/mask_cache.c:28` | `static void drop(mkc_cache *c, mkc_entry *e)` |
| `find` | function | `src/mask_cache.c:36` | `static mkc_entry *find(mkc_cache *c, const mkc_key *k)` |
| `key` | type_alias | `src/mask_cache.c:7` | `typedef struct mkc_entry { mkc_key key;` |
| `key_eq` | function | `src/mask_cache.c:22` | `static int key_eq(const mkc_key *a, const mkc_key *b)` |
| `mkc_bytes` | function | `src/mask_cache.c:111` | `size_t mkc_bytes(const mkc_cache *c)` |
| `mkc_cache` | struct | `src/mask_cache.c:15` | `` |
| `mkc_clear` | function | `src/mask_cache.c:60` | `void mkc_clear(mkc_cache *c)` |
| `mkc_count` | function | `src/mask_cache.c:113` | `size_t mkc_count(const mkc_cache *c)` |
| `mkc_entry` | struct | `src/mask_cache.c:7` | `` |
| `mkc_free` | function | `src/mask_cache.c:65` | `void mkc_free(mkc_cache *c)` |
| `mkc_get` | function | `src/mask_cache.c:72` | `const unsigned char *mkc_get(mkc_cache *c, const mkc_key *k, int *stride)` |
| `mkc_new` | function | `src/mask_cache.c:49` | `mkc_cache *mkc_new(size_t byte_budget, size_t max_entries)` |
| `mkc_put` | function | `src/mask_cache.c:81` | `unsigned char *mkc_put(mkc_cache *c, const mkc_key *k, int stride)` |
| `oldest` | function | `src/mask_cache.c:42` | `static mkc_entry *oldest(mkc_cache *c)` |
| `_POSIX_C_SOURCE` | macro | `src/media_decoder.c:23` | `#define _POSIX_C_SOURCE` |
| `av_rescale_q` | function | `src/media_decoder.c:217` | `return av_rescale_q(f->pts, tb, (AVRational)` |
| `decode_segment` | function | `src/media_decoder.c:276` | `static int decode_segment(decoder_ctx *dc, const uint8_t *data, size_t len)` |
| `decoder_close` | function | `src/media_decoder.c:78` | `static void decoder_close(decoder_ctx *dc)` |
| `decoder_ctx` | struct | `src/media_decoder.c:54` | `` |
| `decoder_init` | function | `src/media_decoder.c:96` | `static int decoder_init(decoder_ctx *dc, const uint8_t *data, size_t len)` |
| `dropped` | function | `src/media_decoder.c:369` | `* the codec in permanent EOF state: every segment after the first decoded * one was silently dropped ("plays a...` |
| `fd` | function | `src/media_decoder.c:469` | `* prevent the Wayland display fd (inherited from the parent) from * surviving the exec. An inherited Wayland fd...` |
| `frame_pts_us` | function | `src/media_decoder.c:215` | `static int64_t frame_pts_us(const AVFrame *f, AVRational tb, int64_t fallback)` |
| `media_decoder_run` | function | `src/media_decoder.c:379` | `void media_decoder_run(int out_fd, int cmd_fd)` |
| `media_decoder_spawn` | function | `src/media_decoder.c:449` | `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd)` |
| `open` | function | `src/media_decoder.c:18` | `*  * Sandbox: the decoder needs open() for shared libraries (.so loading) and  * brk/mmap for FFm...` |
| `out_fd` | type_alias | `src/media_decoder.c:53` | `typedef struct decoder_ctx { int out_fd;` |
| `send_audio_frame` | function | `src/media_decoder.c:242` | `static void send_audio_frame(decoder_ctx *dc, int64_t pts_us)` |
| `send_video_frame` | function | `src/media_decoder.c:222` | `static void send_video_frame(decoder_ctx *dc, int64_t pts_us)` |
| `nt_cancel` | function | `src/nav_token.c:38` | `void nt_cancel(nt_token *t)` |
| `nt_cancelled` | function | `src/nav_token.c:42` | `int nt_cancelled(const nt_token *t)` |
| `nt_foreground` | function | `src/nav_token.c:51` | `int nt_foreground(const nt_token *t)` |
| `nt_id` | function | `src/nav_token.c:56` | `uint64_t nt_id(const nt_token *t)` |
| `nt_new` | function | `src/nav_token.c:16` | `nt_token *nt_new(void)` |
| `nt_ref` | function | `src/nav_token.c:26` | `nt_token *nt_ref(nt_token *t)` |
| `nt_route` | function | `src/nav_token.c:58` | `nt_route_kind nt_route(const nt_token *job, const nt_token *active, nt_token *const *parked,     ...` |
| `nt_set_foreground` | function | `src/nav_token.c:47` | `void nt_set_foreground(nt_token *t, int on)` |
| `nt_token` | struct | `src/nav_token.c:7` | `` |
| `nt_unref` | function | `src/nav_token.c:31` | `void nt_unref(nt_token **tp)` |
| `NG_TEXT_MAX` | macro | `src/net_guard.c:10` | `#define NG_TEXT_MAX` |
| `NG_V4_LEN` | macro | `src/net_guard.c:8` | `#define NG_V4_LEN` |
| `NG_V6_LEN` | macro | `src/net_guard.c:9` | `#define NG_V6_LEN` |
| `decides` | function | `src/net_guard.c:40` | `* IPv4 decides (:: and ::1 embed 0.0.0.0 and 0.0.0.1, both in 0/8). */ if (head_zero && (s[5] == 0 \|\| s[5] ==...` |
| `ng_addr_is_private` | function | `src/net_guard.c:63` | `int ng_addr_is_private(int family, const unsigned char *addr, size_t len)` |
| `ng_ci_eq` | function | `src/net_guard.c:97` | `static int ng_ci_eq(const char *a, const char *b, size_t n)` |
| `ng_decide` | function | `src/net_guard.c:121` | `ng_verdict ng_decide(const ng_request *r, int peer_private)` |
| `ng_host_is_ip` | function | `src/net_guard.c:91` | `int ng_host_is_ip(const char *host)` |
| `ng_host_is_local` | function | `src/net_guard.c:107` | `int ng_host_is_local(const char *host)` |
| `ng_parse` | function | `src/net_guard.c:71` | `static int ng_parse(const char *text, int *family, unsigned char out[NG_V6_LEN])` |
| `ng_seg` | function | `src/net_guard.c:29` | `static unsigned ng_seg(const unsigned char a[NG_V6_LEN], int i)` |
| `ng_text_is_private` | function | `src/net_guard.c:84` | `int ng_text_is_private(const char *ip_text)` |
| `ng_v4_is_private` | function | `src/net_guard.c:12` | `static int ng_v4_is_private(const unsigned char o[NG_V4_LEN])` |
| `ng_v6_is_private` | function | `src/net_guard.c:33` | `static int ng_v6_is_private(const unsigned char a[NG_V6_LEN])` |
| `NR_MAX_HOST` | macro | `src/net_realm.c:15` | `#define NR_MAX_HOST` |
| `ends_with_realm` | function | `src/net_realm.c:23` | `static int ends_with_realm(const char *host, size_t n, const char *suffix)` |
| `host_of` | function | `src/net_realm.c:52` | `static int host_of(const char *url, char *out, size_t out_size)` |
| `lower` | function | `src/net_realm.c:17` | `static char lower(char c)` |
| `nr_classify_host` | function | `src/net_realm.c:34` | `nr_realm nr_classify_host(const char *host)` |
| `nr_classify_url` | function | `src/net_realm.c:68` | `nr_realm nr_classify_url(const char *url)` |
| `nr_realm_allows_http` | function | `src/net_realm.c:88` | `int nr_realm_allows_http(nr_realm r)` |
| `nr_realm_name` | function | `src/net_realm.c:94` | `const char *nr_realm_name(nr_realm r)` |
| `nr_route_for` | function | `src/net_realm.c:74` | `nr_route nr_route_for(const char *url, nr_config cfg)` |
| `nr_route_name` | function | `src/net_realm.c:103` | `const char *nr_route_name(nr_route r)` |
| `LL_FS_BASE` | macro | `src/os_sandbox.c:254` | `#define LL_FS_BASE` |
| `OS_ALLOWED_N` | macro | `src/os_sandbox.c:50` | `#define OS_ALLOWED_N` |
| `OS_SECCOMP_ARCH` | macro | `src/os_sandbox.c:140` | `#  define OS_SECCOMP_ARCH` |
| `OS_SECCOMP_ARCH` | macro | `src/os_sandbox.c:142` | `#  define OS_SECCOMP_ARCH` |
| `_GNU_SOURCE` | macro | `src/os_sandbox.c:13` | `#define _GNU_SOURCE` |
| `excluded` | function | `src/os_sandbox.c:89` | `* intentionally excluded (they need /proc remounting and a post-unshare fork). */ int os_namespac...` |
| `fields` | function | `src/os_sandbox.c:303` | `* long as the unknown trailing fields (net/scoped) are zero, which they are. */ int rfd =...` |
| `headroom` | function | `src/os_sandbox.c:203` | `* wide headroom (room for ~125 allowed syscalls). */ prog[at_mmap].jt = (unsigned char)(prot_check - (at_mmap + 1));` |
| `ll_add_rule` | function | `src/os_sandbox.c:244` | `static long ll_add_rule(int fd, enum landlock_rule_type type,                         const void ...` |
| `ll_create_ruleset` | function | `src/os_sandbox.c:239` | `static long ll_create_ruleset(const struct landlock_ruleset_attr *attr,                          ...` |
| `ll_handled` | function | `src/os_sandbox.c:265` | `static uint64_t ll_handled(int abi)` |
| `ll_read_access` | function | `src/os_sandbox.c:279` | `static uint64_t ll_read_access(uint64_t handled)` |
| `ll_restrict_self` | function | `src/os_sandbox.c:249` | `static long ll_restrict_self(int fd, uint32_t flags)` |
| `number` | function | `src/os_sandbox.c:157` | `* number (x32/i386 on x86_64, AArch32 on aarch64). */ prog[n++] = (struct sock_filter)BPF_STMT(BPF_LD \| BPF_W \|...` |
| `os_harden` | function | `src/os_sandbox.c:113` | `os_status os_harden(os_violation action)` |
| `os_harden` | function | `src/os_sandbox.c:145` | `os_status os_harden(os_violation action)` |
| `os_isolate_namespaces` | function | `src/os_sandbox.c:94` | `os_status os_isolate_namespaces(void)` |
| `os_isolate_namespaces` | function | `src/os_sandbox.c:116` | `os_status os_isolate_namespaces(void)` |
| `os_landlock_abi` | function | `src/os_sandbox.c:285` | `int os_landlock_abi(void)` |
| `os_landlock_abi` | function | `src/os_sandbox.c:331` | `int os_landlock_abi(void)` |
| `os_landlock_restrict` | function | `src/os_sandbox.c:291` | `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)` |
| `os_landlock_restrict` | function | `src/os_sandbox.c:332` | `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)` |
| `os_namespace_flags` | function | `src/os_sandbox.c:115` | `int os_namespace_flags(void)` |
| `os_no_dump` | function | `src/os_sandbox.c:75` | `os_status os_no_dump(void)` |
| `os_no_dump` | function | `src/os_sandbox.c:111` | `os_status os_no_dump(void)` |
| `os_policy_allows` | function | `src/os_sandbox.c:52` | `int os_policy_allows(long syscall_nr)` |
| `os_policy_allows` | function | `src/os_sandbox.c:106` | `int os_policy_allows(long syscall_nr)` |
| `os_policy_size` | function | `src/os_sandbox.c:59` | `size_t os_policy_size(void)` |
| `os_policy_size` | function | `src/os_sandbox.c:107` | `size_t os_policy_size(void)` |
| `os_prot_allowed` | function | `src/os_sandbox.c:65` | `int os_prot_allowed(long syscall_nr, unsigned long prot)` |
| `os_prot_allowed` | function | `src/os_sandbox.c:108` | `int os_prot_allowed(long syscall_nr, unsigned long prot)` |
| `PV_ATOM_SPACE_MAX` | macro | `src/page_view.c:1376` | `#define PV_ATOM_SPACE_MAX` |
| `PV_CELL_NESTED` | macro | `src/page_view.c:5606` | `#define PV_CELL_NESTED` |
| `PV_CELL_RICH` | macro | `src/page_view.c:5607` | `#define PV_CELL_RICH` |
| `PV_COLOR_TOKEN_MAX` | macro | `src/page_view.c:1231` | `#define PV_COLOR_TOKEN_MAX` |
| `PV_CQ_NODES_MAX` | macro | `src/page_view.c:2457` | `#define PV_CQ_NODES_MAX` |
| `PV_FONT_CHAIN_MAX` | macro | `src/page_view.c:69` | `#define PV_FONT_CHAIN_MAX` |
| `PV_FONT_PCT_MAX` | macro | `src/page_view.c:71` | `#define PV_FONT_PCT_MAX` |
| `PV_FONT_PCT_MIN` | macro | `src/page_view.c:70` | `#define PV_FONT_PCT_MIN` |
| `PV_FONT_REL_MAX` | macro | `src/page_view.c:63` | `#define PV_FONT_REL_MAX` |
| `PV_FONT_REL_MIN` | macro | `src/page_view.c:62` | `#define PV_FONT_REL_MIN` |
| `PV_FRAME_DEF_H` | macro | `src/page_view.c:4697` | `#define PV_FRAME_DEF_H` |
| `PV_FRAME_DEF_W` | macro | `src/page_view.c:4696` | `#define PV_FRAME_DEF_W` |
| `PV_FRAME_URL_MAX` | macro | `src/page_view.c:4698` | `#define PV_FRAME_URL_MAX` |
| `PV_MAX_BOXES` | macro | `src/page_view.c:1271` | `#define PV_MAX_BOXES` |
| `PV_MAX_DIM` | macro | `src/page_view.c:57` | `#define PV_MAX_DIM` |
| `PV_MAX_GRID_COLS` | macro | `src/page_view.c:1263` | `#define PV_MAX_GRID_COLS` |
| `PV_MAX_INLINE_ROW_ITEMS` | macro | `src/page_view.c:3241` | `#define PV_MAX_INLINE_ROW_ITEMS` |
| `PV_MAX_STYLE_BYTES` | macro | `src/page_view.c:5686` | `#define PV_MAX_STYLE_BYTES` |
| `PV_NODE_MAP_INIT_CAP` | macro | `src/page_view.c:354` | `#define PV_NODE_MAP_INIT_CAP` |
| `PV_STYLE_RESERVE_MAX` | macro | `src/page_view.c:2479` | `#define PV_STYLE_RESERVE_MAX` |
| `PV_STYLE_RETIRE_MAX` | macro | `src/page_view.c:2413` | `#define PV_STYLE_RETIRE_MAX` |
| `PV_TEXTLESS_DEPTH_MAX` | macro | `src/page_view.c:3643` | `#define PV_TEXTLESS_DEPTH_MAX` |
| `URL` | function | `src/page_view.c:7056` | `* path resolves it against the page URL (ln_resolve). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `_POSIX_C_SOURCE` | macro | `src/page_view.c:10` | `#define _POSIX_C_SOURCE` |
| `acquire_page_sheet` | function | `src/page_view.c:4976` | `static shc_sheet *acquire_page_sheet(lxb_dom_node_t *root, const char *extern_css,               ...` |
| `address` | function | `src/page_view.c:1274` | `* registry accepts must be one the solver can address (include/box_tree.h). */ _Static_assert(PV_MAX_BOXES <=...` |
| `after_pending_emit` | function | `src/page_view.c:1973` | `static pv_status after_pending_emit(pv_view *v, pv_container_reg *reg, pv_item_track *items,     ...` |
| `annotate_flow_run` | function | `src/page_view.c:1924` | `static void annotate_flow_run(pv_view *v, pv_container_reg *reg, pv_item_track *items,           ...` |
| `annotate_replaced_run` | function | `src/page_view.c:5825` | `static void annotate_replaced_run(pv_view *v, pv_container_reg *reg,                             ...` |
| `ascii_ieq` | function | `src/page_view.c:5035` | `static int ascii_ieq(const char *s, const char *lit)` |
| `attr_dup` | function | `src/page_view.c:5047` | `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)` |
| `attributes` | function | `src/page_view.c:4926` | `* carries those attributes (spec/css.md, "Root matcher"). */ static int root_els_match(void *ctx,...` |
| `band` | function | `src/page_view.c:6730` | `* run: without its float annotation it cut the band (the icon row of a * `float:right` social list became one float...` |
| `block` | function | `src/page_view.c:7333` | `* block (Gecko): it never resolves as its own block here. */ int opens_line = block != n && (pending_break \|\| block...` |
| `block_id` | function | `src/page_view.c:6915` | `* box block_id (spec/float.md §7d, slashdot rail): without an * anchor the layout layer cannot position it and it...` |
| `border_side_cleared` | function | `src/page_view.c:1625` | `static int border_side_cleared(int width, int style)` |
| `box_reg_free` | function | `src/page_view.c:2040` | `static void box_reg_free(pv_box_reg *r)` |
| `box_reg_id` | function | `src/page_view.c:2300` | `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,            ...` |
| `box_reg_id_ex` | function | `src/page_view.c:3014` | `static int box_reg_id_ex(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs,         ...` |
| `boxdef_from_style` | function | `src/page_view.c:2049` | `static void boxdef_from_style(pv_box_def *d, const css_style *cs)` |
| `builder` | function | `src/page_view.c:3139` | `* unresolvable in this flat builder (no containing width in hand). box-sizing:border-box  * (the ...` |
| `cached_element_style` | function | `src/page_view.c:2910` | `static css_style cached_element_style(lxb_dom_element_t *el, const css_sheet *sheet,             ...` |
| `cached_element_style_ref` | function | `src/page_view.c:2825` | `static const css_style *cached_element_style_ref(lxb_dom_element_t *el, const css_sheet *sheet,  ...` |
| `cached_pseudo_style` | function | `src/page_view.c:3074` | `static css_style cached_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet,              ...` |
| `causes_block_break` | function | `src/page_view.c:1115` | `static int causes_block_break(lxb_tag_id_t t, css_display display)` |
| `cell_has_nested_table` | function | `src/page_view.c:5485` | `static int cell_has_nested_table(const lxb_dom_node_t *cell, const pv_flow_reg *fr)` |
| `cell_is_grid_item` | function | `src/page_view.c:5619` | `static int cell_is_grid_item(const lxb_dom_node_t *cell, const lxb_dom_node_t *base,             ...` |
| `cell_is_rich` | function | `src/page_view.c:5583` | `static int cell_is_rich(const lxb_dom_node_t *cell)` |
| `cell_kind` | function | `src/page_view.c:5610` | `static unsigned cell_kind(pv_flow_reg *fr, const lxb_dom_node_t *cell)` |
| `cell_span_attr` | function | `src/page_view.c:5509` | `static int cell_span_attr(const lxb_dom_node_t *cell, const char *name, size_t name_len,         ...` |
| `chain` | type_alias | `src/page_view.c:2392` | `typedef struct pv_var_node { cvr_chain chain;` |
| `child` | function | `src/page_view.c:1282` | `* child (NULL = anonymous item: text directly inside the container);` |
| `children_all_inline_block` | function | `src/page_view.c:3301` | `static int children_all_inline_block(const lxb_dom_node_t *p, const css_sheet *sheet,            ...` |
| `classify_input` | function | `src/page_view.c:5129` | `static pv_input_type classify_input(const char *type)` |
| `col_free_share` | function | `src/page_view.c:2971` | `static int col_free_share(const lxb_dom_node_t *el, const css_style *cs, const css_sheet *sheet, pv_style_cache...` |
| `col_has_free_space` | function | `src/page_view.c:3354` | `static int col_has_free_space(const css_style *cs)` |
| `collapse_ws` | function | `src/page_view.c:4670` | `static char *collapse_ws(const char *s, size_t n)` |
| `collect_page_css` | function | `src/page_view.c:5910` | `static char *collect_page_css(lxb_dom_node_t *root, const char *extern_css,                      ...` |
| `collect_text` | function | `src/page_view.c:5105` | `static char *collect_text(const lxb_dom_node_t *el)` |
| `cols` | type_alias | `src/page_view.c:1284` | `typedef struct pv_cont_info { int id, display, gap, justify, cols;` |
| `column_gap_candidate` | function | `src/page_view.c:3470` | `static int column_gap_candidate(const lxb_dom_node_t *el, const css_sheet *sheet,                ...` |
| `cont_def_reset` | function | `src/page_view.c:1797` | `static void cont_def_reset(pv_cont_def *d)` |
| `cont_reg_free` | function | `src/page_view.c:1830` | `static void cont_reg_free(pv_container_reg *reg)` |
| `cont_reg_init` | function | `src/page_view.c:1817` | `static int cont_reg_init(pv_container_reg *reg, size_t cap)` |
| `container` | function | `src/page_view.c:4320` | `* membership in this container (and none in any container further out,                  * since i...` |
| `container_id` | function | `src/page_view.c:1836` | `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)` |
| `content` | function | `src/page_view.c:1213` | `* a <noscript> ancestor also suppresses content (the script would run, so the * fallback is hidden);` |
| `control` | function | `src/page_view.c:6483` | `* caret_color tints the caret of the focused control (2026-07-10). */ pv_set_text_ext(v, &ctl_ext);` |
| `cp1252_to_ucs` | function | `src/page_view.c:95` | `static unsigned int cp1252_to_ucs(unsigned char c)` |
| `css_has_boxdeco` | function | `src/page_view.c:1650` | `static int css_has_boxdeco(const css_style *cs)` |
| `css_has_hbox` | function | `src/page_view.c:1544` | `static int css_has_hbox(const css_style *cs)` |
| `css_has_hmargin` | function | `src/page_view.c:3506` | `static int css_has_hmargin(const css_style *cs)` |
| `css_has_position` | function | `src/page_view.c:1618` | `static int css_has_position(const css_style *cs)` |
| `css_hbox_resolve` | function | `src/page_view.c:1565` | `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)` |
| `css_inline_boxdeco` | function | `src/page_view.c:4154` | `css_inline_boxdeco(cs) &&                            !is_layout_item(p, sheet, style_cache))` |
| `css_replaced_h_fixed` | function | `src/page_view.c:3121` | `static int css_replaced_h_fixed(lxb_dom_element_t *el, const css_sheet *sheet,                   ...` |
| `css_to_fx_justify` | function | `src/page_view.c:3168` | `static int css_to_fx_justify(css_justify j)` |
| `css_width_declared` | function | `src/page_view.c:2998` | `static int css_width_declared(const css_style *cs)` |
| `dimensions` | function | `src/page_view.c:4867` | `* viewport dimensions (data: inline detection, <picture> <source> scanning). */ static void srcse...` |
| `dup_n` | function | `src/page_view.c:156` | `static char *dup_n(const char *s, size_t n)` |
| `element_is_content_leaf` | function | `src/page_view.c:3734` | `static int element_is_content_leaf(const lxb_dom_node_t *n, const css_sheet *sheet,              ...` |
| `element_is_content_leaf_d` | function | `src/page_view.c:3694` | `static int element_is_content_leaf_d(const lxb_dom_node_t *n, const css_sheet *sheet,            ...` |
| `engine` | function | `src/page_view.c:7630` | `* layout engine (contiguous item gather) drops every cell onto its own row and          * a 2-col...` |
| `find_body` | function | `src/page_view.c:4899` | `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)` |
| `find_root_els` | function | `src/page_view.c:4912` | `static pv_root_els find_root_els(lxb_dom_node_t *root)` |
| `flex_column_flows_as_block` | function | `src/page_view.c:3368` | `static int flex_column_flows_as_block(const lxb_dom_node_t *el, const css_style *cs,             ...` |
| `flex_column_flows_as_block_uncached` | function | `src/page_view.c:3377` | `static int flex_column_flows_as_block_uncached(const lxb_dom_node_t *el, const css_style *cs,    ...` |
| `float` | function | `src/page_view.c:4582` | `* genuinely nested float (oid != id) takes the deferred-column path. */     if (cont->float_oid =...` |
| `flow` | function | `src/page_view.c:7513` | `* it is removed from flow (CSS 2.1 9.7), so neither a block change nor * a pending break may flush the band through...` |
| `fold_column_gap` | function | `src/page_view.c:3445` | `static void fold_column_gap(const lxb_dom_node_t *el, css_style *cs,                             ...` |
| `font_color_attr` | function | `src/page_view.c:1253` | `static int font_color_attr(lxb_dom_element_t *el)` |
| `form_for` | function | `src/page_view.c:5076` | `static int form_for(const form_table *ft, const lxb_dom_node_t *n,                     const lxb_...` |
| `form_rec` | struct | `src/page_view.c:5017` | `` |
| `form_table` | struct | `src/page_view.c:5023` | `` |
| `forms_add` | function | `src/page_view.c:5056` | `static int forms_add(form_table *ft, const lxb_dom_node_t *node)` |
| `forms_free` | function | `src/page_view.c:5028` | `static void forms_free(form_table *ft)` |
| `generates_box` | function | `src/page_view.c:1096` | `static int generates_box(lxb_tag_id_t t, css_display display)` |
| `generates_box_style` | function | `src/page_view.c:1108` | `static int generates_box_style(lxb_tag_id_t t, const css_style *cs)` |
| `glyphs` | function | `src/page_view.c:2202` | `* glyphs (the runs carry it as their fill source);` |
| `heading_level` | function | `src/page_view.c:1175` | `static int heading_level(lxb_tag_id_t t)` |
| `height` | function | `src/page_view.c:6757` | `* times its height (jkanime's donghuas/ovas panes). */ lxb_dom_element_t *el = lxb_dom_interface_element(n);` |
| `here` | function | `src/page_view.c:2151` | `* always 0 here (the engine sizes boxes by their content). An intrinsic * keyword on the block axis (CSS Sizing 3...` |
| `id` | function | `src/page_view.c:1306` | `* group id (-1 = the nearest IS the outermost: single-level float, the * painter's old path);` |

Next: [SYMBOLS_p11.md](SYMBOLS_p11.md)
