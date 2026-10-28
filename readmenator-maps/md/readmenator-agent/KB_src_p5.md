# Subsystem: src (page 5 of 10)
Previous: [KB_src_p4.md](KB_src_p4.md)

## src/image_decode.c
- Doc: jpeg_err_ctx: libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG *...
- Layer: utility
- Language: c
- Symbols:
  - `jpeg_err_ctx` (struct, line 153)
  - `gif_reader` (struct, line 255)
  - `gif_bits` (struct, line 290)
  - `read_be32` (function, line 52) `static uint32_t read_be32(const uint8_t *p)`
  - `img_png_dimensions` (function, line 57) `img_status img_png_dimensions(const uint8_t *bytes, size_t len,
                              uin...`
  - `img_dimensions_ok` (function, line 68) `int img_dimensions_ok(uint32_t w, uint32_t h)`
  - `img_fit` (function, line 76) `void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,
             double *out_w, do...`
  - `premultiply` (function, line 90) `static void premultiply(uint8_t *data, size_t pixels)`
  - `img_decode_png` (function, line 102) `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `jpeg_error_longjmp` (function, line 158) `static void jpeg_error_longjmp(j_common_ptr cinfo)`
  - `jpeg_silence` (function, line 164) `static void jpeg_silence(j_common_ptr cinfo)`
  - `img_decode_jpeg` (function, line 166) `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `gr_u8` (function, line 260) `static int gr_u8(gif_reader *r, uint8_t *out)`
  - `gr_u16le` (function, line 266) `static int gr_u16le(gif_reader *r, uint16_t *out)`
  - `gr_skip` (function, line 273) `static int gr_skip(gif_reader *r, size_t n)`
  - `gr_skip_subblocks` (function, line 280) `static int gr_skip_subblocks(gif_reader *r)`
  - `gb_next_code` (function, line 298) `static int gb_next_code(gif_bits *b, unsigned width, unsigned *out)`
  - `gif_deinterlace_row` (function, line 319) `static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh)`
  - `gif_put_pixel` (function, line 334) `static void gif_put_pixel(uint32_t *canvas, uint32_t cw, uint32_t ch,
                          u...`
  - `img_decode_gif` (function, line 354) `img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `img_decode_webp` (function, line 520) `img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `img_decode` (function, line 553) `img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `img_pixels_free` (function, line 566) `void img_pixels_free(img_pixels *p)`
  - `img_format_name` (function, line 575) `const char *img_format_name(img_format f)`
  - `exit` (function, line 6) `* malformed stream fails closed instead of calling exit(). GIF uses an own pure-C * bounded LZW decoder (no giflib)....`
  - `PNG_IHDR_MIN` (macro, line 34) `#define PNG_IHDR_MIN`
  - `GIF_LZW_MAX_CODES` (macro, line 253) `#define GIF_LZW_MAX_CODES`
- Depends on: `include/image_decode.h`

## src/import_map.c
- Doc: str: A JSON string into an owned UTF-8 buffer (escapes decoded; a lone surrogate or a * raw...
- Layer: utility
- Language: c
- Symbols:
  - `im_entry` (struct, line 19)
  - `im_map` (struct, line 25)
  - `jr` (struct, line 34)
  - `scope` (type_alias, line 18) `typedef struct im_entry { int scope;`
  - `ws` (function, line 39) `static void ws(jr *r)`
  - `eat` (function, line 44) `static int eat(jr *r, char c)`
  - `hex4` (function, line 50) `static int hex4(const char *s, uint32_t *out)`
  - `put_utf8` (function, line 64) `static size_t put_utf8(char *o, uint32_t cp)`
  - `str` (function, line 78) `static char *str(jr *r)`
  - `skip` (function, line 128) `static void skip(jr *r, int depth)`
  - `url_like` (function, line 156) `static int url_like(const char *s)`
  - `dup_s` (function, line 168) `static char *dup_s(const char *s)`
  - `clear` (function, line 175) `static void clear(im_map *m)`
  - `add` (function, line 185) `static int add(im_map *m, int scope, const char *key, const char *addr, const char *doc_url,
    ...`
  - `specifier_map` (function, line 209) `static void specifier_map(jr *r, im_map *m, int scope, const char *doc_url,
                     ...`
  - `im_parse` (function, line 225) `im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn resolve, void *ctx)`
  - `match` (function, line 272) `static int match(const im_map *m, int scope, const char *key, char *out, size_t outsz)`
  - `im_resolve` (function, line 301) `int im_resolve(const im_map *m, const char *base, const char *specifier,
               im_url_fn...`
  - `im_count` (function, line 339) `size_t im_count(const im_map *m)`
  - `im_free` (function, line 343) `void im_free(im_map *m)`
  - `IM_MAX_DEPTH` (macro, line 16) `#define IM_MAX_DEPTH`
  - `IM_URL_MAX` (macro, line 17) `#define IM_URL_MAX`
- Depends on: `include/import_map.h`

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
  - `jdce_install` (function, line 199) `int jdce_install(JSContext *ctx)`
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
  - `attrNames` (function, line 695) `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so
     * a missing '...`
  - `js_env` (function, line 1471) `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the
 * document shim (uses...`
  - `jd_install` (function, line 2008) `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)`
  - `jd_flush_custom_elements` (function, line 2090) `void jd_flush_custom_elements(js_context *ctx)`
  - `fails` (function, line 2104) `* cap is reached or an allocation fails (caller stops), else 0. */
static int cb_append(char **bu...`
  - `jd_install_console` (function, line 2218) `jd_status jd_install_console(js_context *ctx, fb_buffer *log)`
  - `jd_set_cookies` (function, line 2255) `jd_status jd_set_cookies(js_context *ctx, const char *cookies)`
  - `jd_get_cookies` (function, line 2275) `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)`
  - `jd_set_computed` (function, line 2298) `jd_status jd_set_computed(js_context *ctx, jd_computed_fn fn, void *fn_ctx)`
  - `jd_set_geometry` (function, line 2309) `jd_status jd_set_geometry(js_context *ctx, const jg_table *geom)`
  - `table` (function, line 643) `* a table (dom.viewport() non-null);`
  - `scripts` (function, line 894) `* player scripts (canPlayType feature-detection, play/pause, muted/loop * reflection, buffered ranges) run without...`
  - `enough` (function, line 1067) `* enough (cloneNode/lastChild/removeChild/insertBefore) that library feature * detection does not throw: jQuery...`
  - `ms` (function, line 1272) `* due is the remaining virtual ms (the trusted parent advances the clock via * OP_TICK -> __tickTimers(elapsed);`
  - `empty` (function, line 1463) `* inert: DOM interface constructors are empty (instanceof yields false, harmless);`
  - `geometry` (function, line 1465) `* constant geometry (zero real leak);`
  - `size` (function, line 1468) `* the viewport reads a fixed normalized size (matches the 1920 width * anti_fp uses for @media, not the real window);`
  - `_GNU_SOURCE` (macro, line 10) `#define _GNU_SOURCE`
  - `JD_COMPUTED_VALUE_MAX` (macro, line 412) `#define JD_COMPUTED_VALUE_MAX`
  - `JD_QSA_INLINE` (macro, line 475) `#define JD_QSA_INLINE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `include/web_storage.h`, `src/js_custom_elements.h`, `src/js_dom_ext.h`, `src/js_dom_internal.h`, `src/js_location_internal.h`

## src/js_dom_ext.c
- Layer: utility
- Language: c
- Symbols:
  - `registration` (function, line 481) `* registration (options, attributeFilter, subtree) and delivered in one microtask. An
 * observer...`
  - `run` (function, line 1265) `static int run(JSContext *ctx, const char *src, size_t len, const char *name)`
  - `jdx_install` (function, line 1330) `int jdx_install(JSContext *ctx)`
  - `jd_install_repl_api` (function, line 1339) `jd_status jd_install_repl_api(js_context *ctx)`
  - `jd_set_repl_css` (function, line 1347) `jd_status jd_set_repl_css(js_context *ctx, const char *css, size_t len)`
  - `jd_install_geolocation` (function, line 1360) `jd_status jd_install_geolocation(js_context *ctx, double lat, double lon, double accuracy_m)`
  - `jd_install_indexeddb` (function, line 1379) `jd_status jd_install_indexeddb(js_context *ctx)`
  - `identity` (function, line 104) `* identity (host/shadowRoot/mode preserved) but every mutation ALSO mirrors * into the host's light DOM via dom.*...`
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
  - `wall_clock_ms` (function, line 36) `static uint64_t wall_clock_ms(void)`
  - `monotonic_ms` (function, line 42) `static double monotonic_ms(void)`
  - `m_date_now` (function, line 50) `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_perf_now` (function, line 58) `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_date_now_exact` (function, line 72) `static JSValue m_date_now_exact(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_perf_now_exact` (function, line 78) `static JSValue m_perf_now_exact(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_empty_array` (function, line 98) `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_get_random_values` (function, line 116) `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,
                       ...`
  - `m_random_uuid` (function, line 146) `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_subtle_null` (function, line 163) `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `reject_named` (function, line 172) `static JSValue reject_named(JSContext *ctx, const char *name, const char *msg)`
  - `m_subtle_digest` (function, line 189) `static JSValue m_subtle_digest(JSContext *ctx, JSValueConst this_val,
                           ...`
  - `def_val` (function, line 242) `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)`
  - `def_str` (function, line 248) `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)`
  - `def_int` (function, line 252) `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)`
  - `def_fn` (function, line 256) `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,
                  JSCFuncti...`
  - `build_languages` (function, line 263) `static JSValue build_languages(JSContext *ctx, const char *langs)`
  - `build_navigator` (function, line 286) `static int build_navigator(JSContext *ctx, JSValueConst global, const char *ua_override,
        ...`
  - `build_screen` (function, line 397) `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)`
  - `build_crypto` (function, line 441) `static int build_crypto(JSContext *ctx, JSValueConst global)`
  - `build_perf_timing` (function, line 469) `static int build_perf_timing(JSContext *ctx, JSValueConst perf)`
  - `build_perf_navigation` (function, line 483) `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)`
  - `build_performance` (function, line 495) `static int build_performance(JSContext *ctx, JSValueConst global, int exact)`
  - `override_date_now` (function, line 527) `static int override_date_now(JSContext *ctx, JSValueConst global, int exact)`
  - `make_readback` (function, line 571) `static JSValue make_readback(JSContext *ctx, uint64_t key)`
  - `build_readback_obj` (function, line 579) `static int build_readback_obj(JSContext *ctx, JSValueConst global,
                              ...`
  - `je_install` (function, line 592) `je_status je_install(js_context *ctx, int screen_w, int screen_h)`
  - `je_install_identity` (function, line 596) `je_status je_install_identity(js_context *ctx, int screen_w, int screen_h,
                      ...`
  - `je_install_identity_trusted` (function, line 601) `je_status je_install_identity_trusted(js_context *ctx, int screen_w, int screen_h,
              ...`
  - `je_install_canvas` (function, line 622) `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)`
  - `primitives` (function, line 6) `* the pure anti_fp primitives (one audited source of normalized constants);`
  - `methods` (function, line 290) `* capability methods (sendBeacon, spec/js_dom.md 7h) without touching any * fingerprintable field. An untrusted...`
  - `_POSIX_C_SOURCE` (macro, line 17) `#define _POSIX_C_SOURCE`
  - `FP_MIME_COUNT` (macro, line 356) `#define FP_MIME_COUNT`
  - `PERF_ORIGIN_EPOCH` (macro, line 439) `#define PERF_ORIGIN_EPOCH`
- Depends on: `include/anti_fp.h`, `include/js_env.h`, `include/js_sandbox.h`, `include/sha2.h`

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
  - `jd_reply_object` (function, line 43) `static JSValue jd_reply_object(JSContext *ctx, int rc, int status, const char *rbody,
           ...`
  - `m_host_fetch` (function, line 73) `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `m_host_fetch_async` (function, line 104) `static JSValue m_host_fetch_async(JSContext *ctx, JSValueConst this_val,
                        ...`
  - `jd_install_xhr` (function, line 335) `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)`
  - `jd_net_deliver` (function, line 339) `jd_status jd_net_deliver(js_context *ctx, int rc, int status, const char *body, size_t len,
     ...`
  - `jd_install_xhr_ex` (function, line 360) `jd_status jd_install_xhr_ex(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx,
                   ...`
  - `send` (function, line 127) `* callbacks fire right after send();`
  - `task` (function, line 311) `* current task (the page never waits on it);`
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


Next: [KB_src_p6.md](KB_src_p6.md)
