# Subsystem: src (page 5 of 9)
Previous: [KB_src_p4.md](KB_src_p4.md)

## src/interp.c
- Doc: solve_bezier_t: } static double sample_bezier_dx(double t, double cx1, double cx2) { return 3.0...
- Layer: utility
- Language: c
- Symbols:
  - `sample_bezier_x` (function, line 18) `static double sample_bezier_x(double t, double cx1, double cx2)`
  - `sample_bezier_dx` (function, line 23) `static double sample_bezier_dx(double t, double cx1, double cx2)`
  - `sample_bezier_y` (function, line 29) `static double sample_bezier_y(double t, double cy1, double cy2)`
  - `solve_bezier_t` (function, line 35) `static double solve_bezier_t(double x, double cx1, double cx2)`
  - `ip_ease` (function, line 55) `double ip_ease(double t, const ip_ease_fn *fn)`
  - `ip_ease` (function, line 64) `case IP_EASE_EASE:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_ease` (function, line 70) `case IP_EASE_EASE_IN:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_ease` (function, line 76) `case IP_EASE_EASE_OUT:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_ease` (function, line 82) `case IP_EASE_EASE_IN_OUT:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_lerp` (function, line 134) `double ip_lerp(double a, double b, double t)`
  - `ip_lerp_color` (function, line 139) `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t)`
  - `ip_interp` (function, line 162) `double ip_interp(ip_val_kind kind, double a, double b, double t)`
  - `ip_kf_interp` (function, line 175) `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf,
                    int n_kf, do...`
  - `ip_anim_init` (function, line 196) `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease,
                  const ip_...`
  - `anim_effective_dir_for` (function, line 222) `static int anim_effective_dir_for(const ip_anim *a, int iter)`
  - `anim_effective_dir` (function, line 232) `static int anim_effective_dir(const ip_anim *a)`
  - `ip_anim_tick` (function, line 236) `int ip_anim_tick(ip_anim *a, double dt_ms)`
  - `ip_anim_current` (function, line 282) `double ip_anim_current(const ip_anim *a)`
  - `ip_anim_done` (function, line 320) `int ip_anim_done(const ip_anim *a)`
- Depends on: `include/interp.h`

## src/js_custom_elements.c
- Layer: utility
- Language: c
- Symbols:
  - `jdce_install` (function, line 190) `int jdce_install(JSContext *ctx)`
- Depends on: `src/js_custom_elements.h`

## src/js_custom_elements.h
- Doc: Private to js_dom.c: installs Custom Elements v1 (spec/js_custom_elements.md) on top of the...
- Layer: utility
- Language: h
- Symbols:
  - `jdce_install` (function, line 9) `int jdce_install(JSContext *ctx);`
  - `FREEDOM_JS_CUSTOM_ELEMENTS_H` (macro, line 2) `#define FREEDOM_JS_CUSTOM_ELEMENTS_H`
- Imported by: `src/js_custom_elements.c`, `src/js_dom.c`

## src/js_dom.c
- Doc: jd_handle: Coerces a JS argument to a node handle.
- Layer: utility
- Language: c
- Symbols:
  - `jd_method` (struct, line 454)
  - `jd_opaque_get` (function, line 27) `jd_opaque *jd_opaque_get(JSContext *ctx)`
  - `jd_idx` (function, line 31) `dom_index *jd_idx(JSContext *ctx)`
  - `jd_handle` (function, line 40) `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out)`
  - `jd_handle_or_null` (function, line 47) `JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h)`
  - `m_node_count` (function, line 53) `static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `m_get_element_by_id` (function, line 59) `static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val,
                       ...`
  - `jd_query_list` (function, line 70) `static JSValue jd_query_list(JSContext *ctx, JSValueConst arg, int by_class)`
  - `m_get_by_tag` (function, line 100) `static JSValue m_get_by_tag(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `m_get_by_class` (function, line 106) `static JSValue m_get_by_class(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_tag_name` (function, line 112) `static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_get_attribute` (function, line 122) `static JSValue m_get_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
  - `m_parent` (function, line 135) `static JSValue m_parent(JSContext *ctx, JSValueConst this_val,
                        int argc, ...`
  - `m_first_child` (function, line 143) `static JSValue m_first_child(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_node_kind` (function, line 152) `static JSValue m_node_kind(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_child_node` (function, line 159) `static JSValue m_child_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_sibling_node` (function, line 166) `static JSValue m_sibling_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_create_char` (function, line 174) `static JSValue m_create_char(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_next_sibling` (function, line 188) `static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_precedes` (function, line 196) `static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_text_content` (function, line 207) `static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_set_text` (function, line 217) `static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_get_title` (function, line 231) `static JSValue m_get_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
  - `m_set_title` (function, line 239) `static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
  - `m_create_element` (function, line 252) `static JSValue m_create_element(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_append_child` (function, line 264) `static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_move_children` (function, line 275) `static JSValue m_move_children(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_clone_node` (function, line 289) `static JSValue m_clone_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_insert_before` (function, line 299) `static JSValue m_insert_before(JSContext *ctx, JSValueConst this_val,
                           ...`
  - `m_remove_child` (function, line 311) `static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_set_attribute` (function, line 320) `static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
  - `m_remove_attribute` (function, line 336) `static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,
                        ...`
  - `m_set_inner_html` (function, line 348) `static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_get_inner_html` (function, line 364) `static JSValue m_get_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_rect` (function, line 397) `static JSValue m_rect(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_computed` (function, line 418) `static JSValue m_computed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_query_selector` (function, line 463) `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_query_selector_all` (function, line 478) `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,
                      ...`
  - `m_matches` (function, line 512) `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,
                         int argc...`
  - `m_closest` (function, line 524) `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,
                         int argc...`
  - `m_attr_names` (function, line 536) `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `jd_is_mutator` (function, line 603) `static int jd_is_mutator(const char *name)`
  - `jd_freeze_mutators` (function, line 609) `static int jd_freeze_mutators(JSContext *jsctx)`
  - `attrNames` (function, line 686) `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so
     * a missing '...`
  - `js_env` (function, line 1415) `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the
 * document shim (uses...`
  - `jd_install` (function, line 1950) `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)`
  - `jd_flush_custom_elements` (function, line 2032) `void jd_flush_custom_elements(js_context *ctx)`
  - `fails` (function, line 2046) `* cap is reached or an allocation fails (caller stops), else 0. */
static int cb_append(char **bu...`
  - `jd_install_console` (function, line 2160) `jd_status jd_install_console(js_context *ctx, fb_buffer *log)`
  - `jd_set_cookies` (function, line 2197) `jd_status jd_set_cookies(js_context *ctx, const char *cookies)`
  - `jd_get_cookies` (function, line 2217) `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)`
  - `jd_set_computed` (function, line 2240) `jd_status jd_set_computed(js_context *ctx, jd_computed_fn fn, void *fn_ctx)`
  - `jd_set_geometry` (function, line 2251) `jd_status jd_set_geometry(js_context *ctx, const jg_table *geom)`
  - `table` (function, line 639) `* a table (dom.viewport() non-null);`
  - `scripts` (function, line 868) `* player scripts (canPlayType feature-detection, play/pause, muted/loop * reflection, buffered ranges) run without...`
  - `enough` (function, line 1041) `* enough (cloneNode/lastChild/removeChild/insertBefore) that library feature * detection does not throw: jQuery...`
  - `ms` (function, line 1216) `* due is the remaining virtual ms (the trusted parent advances the clock via * OP_TICK -> __tickTimers(elapsed);`
  - `empty` (function, line 1407) `* inert: DOM interface constructors are empty (instanceof yields false, harmless);`
  - `geometry` (function, line 1409) `* constant geometry (zero real leak);`
  - `size` (function, line 1412) `* the viewport reads a fixed normalized size (matches the 1920 width * anti_fp uses for @media, not the real window);`
  - `_GNU_SOURCE` (macro, line 10) `#define _GNU_SOURCE`
  - `JD_COMPUTED_VALUE_MAX` (macro, line 412) `#define JD_COMPUTED_VALUE_MAX`
  - `JD_QSA_INLINE` (macro, line 475) `#define JD_QSA_INLINE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `include/web_storage.h`, `src/js_custom_elements.h`, `src/js_dom_ext.h`, `src/js_dom_internal.h`, `src/js_location_internal.h`

## src/js_dom_ext.c
- Layer: utility
- Language: c
- Symbols:
  - `registration` (function, line 439) `* registration (options, attributeFilter, subtree) and delivered in one microtask. An
 * observer...`
  - `run` (function, line 1221) `static int run(JSContext *ctx, const char *src, size_t len, const char *name)`
  - `jdx_install` (function, line 1286) `int jdx_install(JSContext *ctx)`
  - `jd_install_repl_api` (function, line 1295) `jd_status jd_install_repl_api(js_context *ctx)`
  - `jd_set_repl_css` (function, line 1303) `jd_status jd_set_repl_css(js_context *ctx, const char *css, size_t len)`
  - `jd_install_geolocation` (function, line 1316) `jd_status jd_install_geolocation(js_context *ctx, double lat, double lon, double accuracy_m)`
  - `jd_install_indexeddb` (function, line 1335) `jd_status jd_install_indexeddb(js_context *ctx)`
  - `identity` (function, line 102) `* identity (host/shadowRoot/mode preserved) but every mutation ALSO mirrors * into the host's light DOM via dom.*...`
- Depends on: `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_ext.h`

## src/js_dom_ext.h
- Doc: Private to js_dom.c / js_dom_ext.c: installs the DOM Standard extras (tree
- Layer: utility
- Language: h
- Symbols:
  - `jdx_install` (function, line 10) `int jdx_install(JSContext *ctx);`
  - `FREEDOM_JS_DOM_EXT_H` (macro, line 2) `#define FREEDOM_JS_DOM_EXT_H`
- Imported by: `src/js_dom.c`, `src/js_dom_ext.c`

## src/js_dom_internal.h
- Doc: Private to the js_dom family (js_dom.c, js_fetch.c, js_events.c, js_embed.c): the context...
- Layer: utility
- Language: h
- Symbols:
  - `jd_opaque_get` (function, line 11) `jd_opaque *jd_opaque_get(JSContext *ctx);`
  - `jd_idx` (function, line 12) `dom_index *jd_idx(JSContext *ctx);`
  - `jd_handle` (function, line 14) `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out);`
  - `FREEDOM_JS_DOM_INTERNAL_H` (macro, line 2) `#define FREEDOM_JS_DOM_INTERNAL_H`
- Depends on: `include/dom.h`, `include/js_dom.h`
- Imported by: `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`

## src/js_embed.c
- Doc: try_create_iframe_from_script: Scans an inline script body for `video[N]` or `video_data`...
- Layer: utility
- Language: c
- Symbols:
  - `try_create_iframe_from_script` (function, line 86) `static int try_create_iframe_from_script(dom_index *idx,
                                        ...`
  - `jd_video_from_scripts` (function, line 203) `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,
                   ...`
  - `jd_inject_video_shim` (function, line 242) `jd_status jd_inject_video_shim(js_context *ctx)`
  - `scan_video_url` (function, line 256) `static int scan_video_url(const char *body, size_t blen,
                           char *out, si...`
  - `jd_process_iframes` (function, line 294) `void jd_process_iframes(js_context *ctx, dom_index *idx,
                        jd_fetch_fn fn, ...`
  - `_GNU_SOURCE` (macro, line 6) `#define _GNU_SOURCE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`

## src/js_env.c
- Doc: m_perf_now: performance.now: coarsened elapsed since the origin bound at install time, so * it...
- Layer: infrastructure
- Language: c
- Symbols:
  - `wall_clock_ms` (function, line 35) `static uint64_t wall_clock_ms(void)`
  - `monotonic_ms` (function, line 41) `static double monotonic_ms(void)`
  - `m_date_now` (function, line 49) `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_perf_now` (function, line 57) `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_empty_array` (function, line 77) `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_get_random_values` (function, line 95) `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,
                       ...`
  - `m_random_uuid` (function, line 125) `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_subtle_null` (function, line 142) `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `def_val` (function, line 153) `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)`
  - `def_str` (function, line 159) `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)`
  - `def_int` (function, line 163) `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)`
  - `def_fn` (function, line 167) `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,
                  JSCFuncti...`
  - `build_languages` (function, line 174) `static JSValue build_languages(JSContext *ctx, const char *langs)`
  - `build_navigator` (function, line 197) `static int build_navigator(JSContext *ctx, JSValueConst global, const char *ua_override,
        ...`
  - `build_screen` (function, line 309) `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)`
  - `build_crypto` (function, line 353) `static int build_crypto(JSContext *ctx, JSValueConst global)`
  - `build_perf_timing` (function, line 381) `static int build_perf_timing(JSContext *ctx, JSValueConst perf)`
  - `build_perf_navigation` (function, line 395) `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)`
  - `build_performance` (function, line 407) `static int build_performance(JSContext *ctx, JSValueConst global)`
  - `override_date_now` (function, line 439) `static int override_date_now(JSContext *ctx, JSValueConst global)`
  - `make_readback` (function, line 483) `static JSValue make_readback(JSContext *ctx, uint64_t key)`
  - `build_readback_obj` (function, line 491) `static int build_readback_obj(JSContext *ctx, JSValueConst global,
                              ...`
  - `je_install` (function, line 504) `je_status je_install(js_context *ctx, int screen_w, int screen_h)`
  - `je_install_identity` (function, line 508) `je_status je_install_identity(js_context *ctx, int screen_w, int screen_h,
                      ...`
  - `je_install_canvas` (function, line 528) `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)`
  - `primitives` (function, line 6) `* the pure anti_fp primitives (one audited source of normalized constants);`
  - `methods` (function, line 201) `* capability methods (sendBeacon, spec/js_dom.md 7h) without touching any * fingerprintable field. An untrusted...`
  - `_POSIX_C_SOURCE` (macro, line 17) `#define _POSIX_C_SOURCE`
  - `FP_MIME_COUNT` (macro, line 267) `#define FP_MIME_COUNT`
  - `PERF_ORIGIN_EPOCH` (macro, line 351) `#define PERF_ORIGIN_EPOCH`
- Depends on: `include/anti_fp.h`, `include/js_env.h`, `include/js_sandbox.h`

## src/js_events.c
- Doc: jd_eval_default_action: Runs one engine event-dispatch expression and maps its result to the C...
- Layer: infrastructure
- Language: c
- Symbols:
  - `jd_click_state` (struct, line 25)
  - `jd_click_state_new` (function, line 29) `jd_click_state *jd_click_state_new(void)`
  - `jd_click_state_free` (function, line 34) `void jd_click_state_free(jd_click_state *s)`
  - `jd_install_events` (function, line 38) `jd_status jd_install_events(js_context *ctx, jd_click_state *state)`
  - `jd_eval_default_action` (function, line 52) `static int jd_eval_default_action(JSContext *jsctx, const char *src, size_t n,
                  ...`
  - `jd_fire_click` (function, line 66) `int jd_fire_click(js_context *ctx, dom_node_id node_id)`
  - `jd_fire_submit` (function, line 78) `int jd_fire_submit(js_context *ctx, dom_node_id form_node_id)`
  - `jd_escape_js_str` (function, line 91) `static size_t jd_escape_js_str(const char *src, char *dst, size_t dstsz)`
  - `jd_fire_mouse_event` (function, line 163) `int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,
                        const char ...`
  - `_GNU_SOURCE` (macro, line 6) `#define _GNU_SOURCE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`

## src/js_fetch.c
- Doc: jd_pack_ptr: Carry the host fetch fn + its ctx as a function's closure data, each split into...
- Layer: utility
- Language: c
- Symbols:
  - `jd_pack_ptr` (function, line 28) `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)`
  - `jd_unpack_ptr` (function, line 33) `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)`
  - `m_host_fetch` (function, line 46) `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `jd_install_xhr` (function, line 281) `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)`
  - `send` (function, line 96) `* callbacks fire right after send();`
  - `task` (function, line 257) `* current task (the page never waits on it);`
  - `_GNU_SOURCE` (macro, line 6) `#define _GNU_SOURCE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`

## src/js_geom.c
- Doc: unite: Bounding box of a and b into a; returns 1 if a changed.
- Layer: utility
- Language: c
- Symbols:
  - `jg_init` (function, line 17) `void jg_init(jg_table *t)`
  - `jg_free` (function, line 21) `void jg_free(jg_table *t)`
  - `clamp_coord` (function, line 27) `static int32_t clamp_coord(double v, double lo)`
  - `grow` (function, line 33) `static int grow(jg_table *t)`
  - `push` (function, line 45) `static int push(jg_table *t, dom_node_id node, int32_t x, int32_t y, int32_t w, int32_t h)`
  - `jg_add` (function, line 52) `int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h)`
  - `unite` (function, line 63) `static int unite(jg_rect *a, const jg_rect *b)`
  - `cmp_node` (function, line 78) `static int cmp_node(const void *pa, const void *pb)`
  - `jg_finish` (function, line 83) `int jg_finish(jg_table *t)`
  - `jg_find` (function, line 96) `const jg_rect *jg_find(const jg_table *t, dom_node_id node)`
  - `slot_of` (function, line 102) `static uint32_t slot_of(dom_node_id n)`
  - `index_of` (function, line 109) `static size_t index_of(jg_table *t, uint32_t *slots, dom_node_id node, const jg_rect *seed,
     ...`
  - `jg_aggregate` (function, line 124) `int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx)`
  - `jg_wire_len` (function, line 163) `size_t jg_wire_len(const jg_table *t)`
  - `jg_encode` (function, line 167) `int jg_encode(const jg_table *t, int32_t *out, size_t cap)`
  - `in_range` (function, line 182) `static int in_range(int32_t v, int32_t lo)`
  - `jg_decode` (function, line 186) `int jg_decode(const int32_t *in, size_t n, jg_table *out)`
  - `fnv` (function, line 212) `static uint64_t fnv(uint64_t h, int32_t v)`
  - `jg_hash` (function, line 221) `uint64_t jg_hash(const jg_table *t)`
  - `JG_INDEX_SLOTS` (macro, line 14) `#define JG_INDEX_SLOTS`
  - `JG_SLOT_EMPTY` (macro, line 15) `#define JG_SLOT_EMPTY`
- Depends on: `include/js_geom.h`

## src/js_location.c
- Doc: jd_lp_set: Defines a string property on the __locParts data object from a (ptr,len) span. * The...
- Layer: utility
- Language: c
- Symbols:
  - `jd_lp_set` (function, line 24) `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,
                      const ...`
  - `jl_m_hist_target` (function, line 35) `JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `jd_set_location` (function, line 139) `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)`
  - `jd_take_nav_request` (function, line 173) `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)`
  - `jd_take_history` (function, line 219) `char *jd_take_history(js_context *ctx, int *go)`
  - `jd_pop_state` (function, line 250) `int jd_pop_state(js_context *ctx, int index)`
- Depends on: `include/js_dom.h`, `include/url.h`, `src/js_location_internal.h`

## src/js_location_internal.h
- Doc: Private to js_dom.c / js_location.c: the dom.histTarget native lives with the
- Layer: utility
- Language: h
- Symbols:
  - `header` (function, line 6) `* stay out of every public header (include/ never sees quickjs.h). */ #include "quickjs.h" JSValue...`
  - `FREEDOM_JS_LOCATION_INTERNAL_H` (macro, line 2) `#define FREEDOM_JS_LOCATION_INTERNAL_H`
- Imported by: `src/js_dom.c`, `src/js_location.c`

## src/js_policy.c
- Doc: eq_ci: js_policy — implementation: pure per-host JavaScript policy decision.
- Layer: business_logic
- Language: c
- Symbols:
  - `eq_ci` (function, line 12) `static int eq_ci(const char *a, const char *b)`
  - `jsp_enabled` (function, line 22) `bool jsp_enabled(jsp_mode mode, int host_allowlisted)`
  - `jsp_trusted` (function, line 31) `bool jsp_trusted(bool js_enabled, int host_allowlisted)`
  - `jsp_present_trusted` (function, line 35) `bool jsp_present_trusted(int host_allowlisted)`
  - `jsp_mode_from_str` (function, line 39) `jsp_mode jsp_mode_from_str(const char *s)`
  - `jsp_mode_str` (function, line 51) `const char *jsp_mode_str(jsp_mode mode)`
- Depends on: `include/js_policy.h`

## src/js_sandbox.c
- Doc: js_mem_state: We enforce the heap cap ourselves (not via JS_SetMemoryLimit, whose check runs...
- Layer: utility
- Language: c
- Symbols:
  - `js_mem_state` (struct, line 29)
  - `js_context` (struct, line 38)
  - `limit` (type_alias, line 29) `typedef struct js_mem_state { size_t limit;`
  - `rej_remove` (function, line 75) `static void rej_remove(js_context *c, size_t i)`
  - `js_rejection_cb` (function, line 83) `static void js_rejection_cb(JSContext *jc, JSValueConst promise, JSValueConst reason,
           ...`
  - `rej_report` (function, line 102) `static void rej_report(js_context *c)`
  - `jm_malloc` (function, line 127) `static void *jm_malloc(void *opaque, size_t size)`
  - `jm_calloc` (function, line 135) `static void *jm_calloc(void *opaque, size_t count, size_t size)`
  - `jm_free` (function, line 145) `static void jm_free(void *opaque, void *ptr)`
  - `jm_realloc` (function, line 151) `static void *jm_realloc(void *opaque, void *ptr, size_t size)`
  - `jm_usable_size` (function, line 161) `static size_t jm_usable_size(const void *ptr)`
  - `host_dup` (function, line 171) `static char *host_dup(const char *src, size_t len)`
  - `timespec_reached` (function, line 180) `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)`
  - `timespec_diff_ms` (function, line 185) `static long timespec_diff_ms(const struct timespec *a, const struct timespec *b)`
  - `profile_sample` (function, line 190) `static void profile_sample(js_context *c, unsigned weight_ms)`
  - `js_profile_enable` (function, line 222) `void js_profile_enable(js_context *ctx)`
  - `js_profile_report` (function, line 228) `size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n)`
  - `throw_key` (function, line 251) `static void throw_key(JSContext *ctx, JSValueConst obj, char *key, size_t cap)`
  - `throw_hook_cb` (function, line 308) `static void throw_hook_cb(JSContext *ctx, JSValueConst obj, void *opaque)`
  - `js_throws_enable` (function, line 328) `void js_throws_enable(js_context *ctx)`
  - `js_throws_report` (function, line 334) `size_t js_throws_report(js_context *ctx, char *out, size_t cap, size_t top_n)`
  - `m_fb_report` (function, line 356) `static JSValue m_fb_report(JSContext *jsctx, JSValueConst this_val, int argc, JSValueConst *argv,...`
  - `js_devtools_enable` (function, line 372) `void js_devtools_enable(js_context *ctx)`
  - `js_devtools_expose` (function, line 378) `js_status js_devtools_expose(js_context *ctx)`
  - `js_interrupt_cb` (function, line 394) `static int js_interrupt_cb(JSRuntime *rt, void *opaque)`
  - `is_ascii_digit` (function, line 418) `static int is_ascii_digit(char c)`
  - `js_loc_from_stack` (function, line 420) `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      i...`
  - `js_stack_limit_for` (function, line 539) `size_t js_stack_limit_for(size_t soft_stack)`
  - `process_soft_stack` (function, line 550) `static size_t process_soft_stack(void)`
  - `js_prime_stack_limit` (function, line 560) `void js_prime_stack_limit(void)`
  - `js_limits_default` (function, line 562) `js_limits js_limits_default(void)`
  - `limits_resolve` (function, line 571) `static js_limits limits_resolve(const js_limits *lim)`
  - `js_validate_source` (function, line 580) `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)`
  - `js_context_new` (function, line 591) `js_status js_context_new(const js_limits *lim, js_context **out)`
  - `js_context_free` (function, line 631) `void js_context_free(js_context *ctx)`
  - `arm_deadline` (function, line 643) `static void arm_deadline(js_context *ctx, uint64_t budget_ms)`
  - `js_set_time_budget` (function, line 658) `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)`
  - `js_eval` (function, line 663) `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)`
  - `js_eval_named` (function, line 667) `js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        con...`
  - `js_pump_jobs` (function, line 750) `int js_pump_jobs(js_context *ctx, int max_jobs)`
  - `js_eval_once` (function, line 769) `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)`
  - `js_result_free` (function, line 782) `void js_result_free(js_result *res)`
  - `js_set_current_script` (function, line 810) `void js_set_current_script(js_context *ctx, const char *src, const char *type)`
  - `js_context_raw` (function, line 843) `void *js_context_raw(js_context *ctx)`
  - `mod_set_meta` (function, line 875) `static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url)`
  - `mod_loader` (function, line 884) `static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque)`
  - `js_set_module_host` (function, line 923) `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,
                        js...`
  - `mod_fail` (function, line 938) `static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,
      ...`
  - `js_eval_module` (function, line 953) `js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,
        ...`
  - `realm_of` (function, line 1020) `static JSContext *realm_of(js_context *c, JSValueConst g)`
  - `throw_named` (function, line 1033) `static JSValue throw_named(JSContext *ctx, const char *name, const char *msg)`
  - `m_realm_new` (function, line 1043) `static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,
                     ...`
  - `m_realm_eval` (function, line 1057) `static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,
                    ...`
  - `m_realm_clone` (function, line 1093) `static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,
                   ...`
  - `js_install_realms` (function, line 1115) `js_status js_install_realms(js_context *ctx)`
  - `undefined` (function, line 512) `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx...`
  - `mod_normalize` (function, line 920) `static char *mod_normalize(JSContext *jc, const char *base, const char *name, void *opaque);`
  - `_POSIX_C_SOURCE` (macro, line 12) `#define _POSIX_C_SOURCE`
  - `JS_PROFILE_SLOTS` (macro, line 35) `#define JS_PROFILE_SLOTS`
  - `JS_PROFILE_KEY_MAX` (macro, line 36) `#define JS_PROFILE_KEY_MAX`
  - `JS_MODULE_URL_MAX` (macro, line 848) `#define JS_MODULE_URL_MAX`
- Depends on: `include/js_sandbox.h`

## src/js_trusted.c
- Doc: ws_payload: } void jt_ws_ops_free(jt_ws_op *ops, size_t n) { if (ops == NULL) return; for...
- Layer: utility
- Language: c
- Symbols:
  - `jt_seed_ctx` (struct, line 380)
  - `jt_enable_open` (function, line 48) `jd_status jt_enable_open(js_context *ctx)`
  - `jt_enable_observers` (function, line 129) `jd_status jt_enable_observers(js_context *ctx)`
  - `jt_geometry_changed` (function, line 143) `jd_status jt_geometry_changed(js_context *ctx)`
  - `jt_take_opens` (function, line 159) `char *jt_take_opens(js_context *ctx)`
  - `jt_enable_ws` (function, line 237) `jd_status jt_enable_ws(js_context *ctx)`
  - `jt_ws_ops_free` (function, line 249) `void jt_ws_ops_free(jt_ws_op *ops, size_t n)`
  - `hex_nibble` (function, line 254) `static int hex_nibble(char c)`
  - `ws_payload` (function, line 261) `static char *ws_payload(int kind, const char *s, size_t n, size_t *out_len)`
  - `jt_take_ws` (function, line 285) `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap)`
  - `jt_ws_event` (function, line 327) `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len)`
  - `jt_seed_pair` (function, line 382) `static void jt_seed_pair(void *vctx, const char *k, size_t kl, const char *v, size_t vl)`
  - `jt_enable_storage` (function, line 392) `jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len)`
  - `jt_take_storage` (function, line 413) `int jt_take_storage(js_context *ctx, char **out, size_t *len)`
  - `explicitly` (function, line 461) `* explicitly (no window, no document). Delivery is always a timer task. */
static const char JT_W...`
  - `jt_enable_worker` (function, line 542) `jd_status jt_enable_worker(js_context *ctx)`
  - `JT_IO_MAX_STR` (macro, line 62) `#define JT_IO_MAX_STR`
- Depends on: `include/js_trusted.h`, `include/web_storage.h`

## src/link_nav.c
- Doc: clean_href: Removes tab/newline/CR anywhere and trims leading/trailing spaces, in place * into out.
- Layer: utility
- Language: c
- Symbols:
  - `clean_href` (function, line 19) `static int clean_href(const char *href, char *out, size_t outsz)`
  - `ci_prefix` (function, line 38) `static int ci_prefix(const char *s, const char *prefix)`
  - `classify_block` (function, line 62) `static ln_block_reason classify_block(const char *ref)`
  - `file_dir_len` (function, line 69) `static size_t file_dir_len(const char *base)`
  - `last_seg_is_dotdot` (function, line 79) `static int last_seg_is_dotdot(const char *body, size_t blen)`
  - `append_seg` (function, line 86) `static int append_seg(char *body, size_t bodysz, size_t *blen,
                      const char *...`
  - `pop_seg` (function, line 98) `static void pop_seg(char *body, size_t *blen)`
  - `resolve_file` (function, line 149) `static int resolve_file(const char *base, const char *ref, char *out, size_t outsz)`
  - `ln_resolve` (function, line 172) `ln_status ln_resolve(const char *base, const char *href, ln_result *out)`
  - `ln_block_reason_text` (function, line 241) `const char *ln_block_reason_text(ln_block_reason reason)`
- Depends on: `include/link_nav.h`, `include/url.h`


Next: [KB_src_p6.md](KB_src_p6.md)
