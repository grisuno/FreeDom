# Subsystem: src (page 5 of 10)
Previous: [KB_src_p4.md](KB_src_p4.md)

## src/html_parse.c
- Doc: node_next: }; /* --- helpers --- static char *dup_bytes(const lxb_char_t *src, size_t len) { if...
- Layer: utility
- Language: c
- Symbols:
  - `hp_document` (struct, line 21)
  - `dup_bytes` (function, line 27) `static char *dup_bytes(const lxb_char_t *src, size_t len)`
  - `node_next` (function, line 37) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)`
  - `attr_is_event_handler` (function, line 47) `static int attr_is_event_handler(const lxb_dom_attr_t *attr)`
  - `node_is_script` (function, line 54) `static int node_is_script(const lxb_dom_node_t *node)`
  - `strip_scripts` (function, line 60) `static void strip_scripts(lxb_html_document_t *document)`
  - `type_is` (function, line 100) `static int type_is(const lxb_char_t *t, size_t len, const char *word)`
  - `type_is_module` (function, line 117) `static int type_is_module(const lxb_char_t *t, size_t len)`
  - `script_classify` (function, line 121) `static int script_classify(const lxb_dom_node_t *n,
                           const lxb_char_t *...`
  - `hp_extract_script_list` (function, line 164) `hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count)`
  - `hp_free_scripts` (function, line 238) `void hp_free_scripts(hp_script *scripts, size_t count)`
  - `attr_has_token_ci` (function, line 251) `static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle)`
  - `link_is_active_stylesheet` (function, line 272) `static int link_is_active_stylesheet(lxb_dom_element_t *el,
                                     ...`
  - `hp_extract_stylesheet_hrefs` (function, line 294) `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count)`
  - `hp_free_stylesheet_hrefs` (function, line 328) `void hp_free_stylesheet_hrefs(char **hrefs, size_t count)`
  - `strip_event_handlers` (function, line 334) `static void strip_event_handlers(lxb_html_document_t *document)`
  - `hp_config_default` (function, line 357) `hp_config hp_config_default(void)`
  - `hp_validate_input` (function, line 365) `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg)`
  - `hp_parse` (function, line 375) `hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out)`
  - `hp_element_count` (function, line 409) `size_t hp_element_count(const hp_document *doc)`
  - `hp_script_count` (function, line 419) `size_t hp_script_count(const hp_document *doc)`
  - `hp_event_handler_count` (function, line 429) `size_t hp_event_handler_count(const hp_document *doc)`
  - `hp_extract_text` (function, line 445) `char *hp_extract_text(const hp_document *doc, size_t *out_len)`
  - `hp_get_title` (function, line 464) `char *hp_get_title(const hp_document *doc, size_t *out_len)`
  - `hp_free` (function, line 479) `void hp_free(char *buf)`
  - `hp_document_free` (function, line 483) `void hp_document_free(hp_document *doc)`
  - `hp_document_root` (function, line 489) `const void *hp_document_root(const hp_document *doc)`
  - `lxb_dom_element_has_attribute` (function, line 230) `&& lxb_dom_element_has_attribute(sel, (const lxb_char_t *)"nomodule", 8);`
  - `_POSIX_C_SOURCE` (macro, line 9) `#define _POSIX_C_SOURCE`
- Depends on: `include/dom.h`, `include/html_parse.h`, `include/util.h`

## src/http_cache.c
- Doc: days_from_civil: #define HC_MAGIC      "FHC1\n" #define HC_NAME_HEX   64u #define HC_EVICT_EVERY...
- Layer: presentation
- Language: c
- Symbols:
  - `hc_store` (struct, line 146)
  - `ent` (struct, line 397)
  - `days_in_month` (function, line 39) `static int days_in_month(int y, int m)`
  - `days_from_civil` (function, line 46) `static long days_from_civil(int y, int m, int d)`
  - `hc_parse_http_date` (function, line 55) `time_t hc_parse_http_date(const char *s)`
  - `cc_find` (function, line 74) `static int cc_find(const char *cc, const char *name, const char **val)`
  - `cc_max_age` (function, line 92) `static int cc_max_age(const char *cc, long *out)`
  - `hc_storable` (function, line 107) `int hc_storable(long http_code, const hc_meta *m, size_t body_len)`
  - `hc_lifetime` (function, line 115) `long hc_lifetime(const hc_meta *m)`
  - `hc_classify` (function, line 136) `hc_class hc_classify(const hc_meta *m, time_t now)`
  - `hex_of` (function, line 155) `static void hex_of(const uint8_t *b, size_t n, char *out)`
  - `entry_path` (function, line 162) `static int entry_path(const hc_store *s, char kind, const char *partition, const char *url,
     ...`
  - `remove_entries` (function, line 180) `static void remove_entries(const char *dir)`
  - `write_atomic` (function, line 192) `static int write_atomic(const char *path, const uint8_t *data, size_t len)`
  - `read_file` (function, line 208) `static uint8_t *read_file(const char *path, size_t max, size_t *len)`
  - `hc_open` (function, line 230) `hc_status hc_open(hc_store **out, const char *dir, const uint8_t wrap[LS_KEY_LEN])`
  - `hc_close` (function, line 279) `void hc_close(hc_store *s)`
  - `hc_body_free` (function, line 287) `void hc_body_free(uint8_t *body, size_t len)`
  - `has_nl` (function, line 293) `static int has_nl(const char *s)`
  - `meta_ok` (function, line 295) `static int meta_ok(const hc_meta *m)`
  - `store_entry` (function, line 302) `static hc_status store_entry(hc_store *s, const char *path, const hc_meta *m,
                   ...`
  - `load_entry` (function, line 327) `static hc_status load_entry(hc_store *s, const char *path, hc_meta *m, uint8_t **body,
          ...`
  - `get_locked` (function, line 385) `static hc_status get_locked(hc_store *s, const char *partition, const char *url, hc_meta *meta,
 ...`
  - `evict` (function, line 396) `static void evict(hc_store *s)`
  - `put_locked` (function, line 434) `static hc_status put_locked(hc_store *s, const char *partition, const char *url, const hc_meta *m...`
  - `redirect_put_locked` (function, line 446) `static hc_status redirect_put_locked(hc_store *s, const char *from, const char *to, time_t now)`
  - `redirect_get_locked` (function, line 459) `static hc_status redirect_get_locked(hc_store *s, const char *from, time_t now, char *out, size_t...`
  - `hc_clear` (function, line 473) `void hc_clear(hc_store *s)`
  - `hc_get` (function, line 480) `hc_status hc_get(hc_store *s, const char *partition, const char *url, hc_meta *meta,
            ...`
  - `hc_put` (function, line 489) `hc_status hc_put(hc_store *s, const char *partition, const char *url, const hc_meta *meta,
      ...`
  - `hc_redirect_put` (function, line 498) `hc_status hc_redirect_put(hc_store *s, const char *from, const char *to, time_t now)`
  - `hc_redirect_get` (function, line 506) `hc_status hc_redirect_get(hc_store *s, const char *from, time_t now, char *out, size_t cap)`
  - `_POSIX_C_SOURCE` (macro, line 7) `#define _POSIX_C_SOURCE`
  - `HC_KEY_FILE` (macro, line 31) `#define HC_KEY_FILE`
  - `HC_MAGIC` (macro, line 32) `#define HC_MAGIC`
  - `HC_NAME_HEX` (macro, line 33) `#define HC_NAME_HEX`
  - `HC_EVICT_EVERY` (macro, line 34) `#define HC_EVICT_EVERY`
  - `HC_MAX_AGE_CAP` (macro, line 35) `#define HC_MAX_AGE_CAP`
- Depends on: `include/disk_store.h`, `include/http_cache.h`, `include/pq_seal.h`

## src/identity.c
- Doc: tag_valid: size_t n = strlen(ua); if (n >= IDN_UA_MAX) return -1; int printable = 0; for (size_t...
- Layer: utility
- Language: c
- Symbols:
  - `is_alpha` (function, line 20) `static int is_alpha(char c)`
  - `is_alnum` (function, line 21) `static int is_alnum(char c)`
  - `idn_defaults` (function, line 23) `void idn_defaults(idn_config *c)`
  - `idn_is_default` (function, line 29) `int idn_is_default(const idn_config *c)`
  - `idn_set_user_agent` (function, line 35) `int idn_set_user_agent(idn_config *c, const char *ua)`
  - `tag_valid` (function, line 51) `static int tag_valid(const char *s, size_t n)`
  - `idn_set_languages` (function, line 64) `int idn_set_languages(idn_config *c, const char *list)`
  - `idn_set_geo` (function, line 92) `int idn_set_geo(idn_config *c, double lat, double lon, double accuracy_m)`
  - `idn_clear_geo` (function, line 104) `void idn_clear_geo(idn_config *c)`
  - `idn_user_agent` (function, line 110) `const char *idn_user_agent(const idn_config *c)`
  - `idn_accept_language` (function, line 114) `size_t idn_accept_language(const idn_config *c, char *out, size_t cap)`
  - `idn_primary_language` (function, line 144) `size_t idn_primary_language(const idn_config *c, char *out, size_t cap)`
  - `hexval` (function, line 158) `static int hexval(int ch)`
  - `pct_decode` (function, line 167) `static long pct_decode(const char *s, size_t n, char *out, size_t cap, int plus)`
  - `append` (function, line 187) `static int append(char *buf, size_t *n, size_t cap, const char *fmt, ...)`
  - `append_pct` (function, line 198) `static int append_pct(char *buf, size_t *n, size_t cap, const char *s)`
  - `idn_serialize` (function, line 207) `size_t idn_serialize(const idn_config *c, char *out, size_t cap)`
  - `parse_geo` (function, line 228) `static int parse_geo(const char *s, double *lat, double *lon, double *acc)`
  - `idn_parse` (function, line 241) `void idn_parse(idn_config *c, const char *text)`
  - `parse_number` (function, line 275) `static int parse_number(const char *s, double *out)`
  - `idn_apply_query` (function, line 282) `unsigned idn_apply_query(idn_config *c, const char *query)`
  - `esc_append` (function, line 361) `static int esc_append(char *buf, size_t *n, size_t cap, const char *s)`
  - `idn_render_page` (function, line 377) `size_t idn_render_page(const idn_config *c, char *out, size_t cap)`
  - `_GNU_SOURCE` (macro, line 7) `#define _GNU_SOURCE`
  - `IDN_QUERY_FIELD_MAX` (macro, line 18) `#define IDN_QUERY_FIELD_MAX`
- Depends on: `include/anti_fp.h`, `include/identity.h`

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
  - `jdce_install` (function, line 200) `int jdce_install(JSContext *ctx)`
- Depends on: `src/js_custom_elements.h`, `src/js_native_internal.h`

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
  - `jd_method` (struct, line 456)
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
  - `m_rect` (function, line 399) `static JSValue m_rect(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_computed` (function, line 420) `static JSValue m_computed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_query_selector` (function, line 465) `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_query_selector_all` (function, line 480) `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,
                      ...`
  - `m_matches` (function, line 514) `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,
                         int argc...`
  - `m_closest` (function, line 526) `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,
                         int argc...`
  - `m_attr_names` (function, line 538) `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `jd_is_mutator` (function, line 605) `static int jd_is_mutator(const char *name)`
  - `jd_freeze_mutators` (function, line 611) `static int jd_freeze_mutators(JSContext *jsctx)`
  - `attrNames` (function, line 697) `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so
     * a missing '...`
  - `js_env` (function, line 1421) `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the
 * document shim (uses...`
  - `jd_install` (function, line 1958) `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)`
  - `jd_rebind` (function, line 2042) `jd_status jd_rebind(js_context *ctx, dom_index *idx, jd_opaque *from, jd_opaque *to)`
  - `jd_flush_custom_elements` (function, line 2052) `void jd_flush_custom_elements(js_context *ctx)`
  - `fails` (function, line 2066) `* cap is reached or an allocation fails (caller stops), else 0. */
static int cb_append(char **bu...`
  - `jd_install_console` (function, line 2180) `jd_status jd_install_console(js_context *ctx, fb_buffer *log)`
  - `jd_set_cookies` (function, line 2217) `jd_status jd_set_cookies(js_context *ctx, const char *cookies)`
  - `jd_get_cookies` (function, line 2237) `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)`
  - `jd_set_computed` (function, line 2260) `jd_status jd_set_computed(js_context *ctx, jd_computed_fn fn, void *fn_ctx)`
  - `jd_set_geometry` (function, line 2271) `jd_status jd_set_geometry(js_context *ctx, const jg_table *geom)`
  - `table` (function, line 645) `* a table (dom.viewport() non-null);`
  - `scripts` (function, line 898) `* player scripts (canPlayType feature-detection, play/pause, muted/loop * reflection, buffered ranges) run without...`
  - `enough` (function, line 1071) `* enough (cloneNode/lastChild/removeChild/insertBefore) that library feature * detection does not throw: jQuery...`
  - `ms` (function, line 1212) `* due is the remaining virtual ms (the trusted parent advances the clock via * OP_TICK -> __tickTimers(elapsed);`
  - `empty` (function, line 1413) `* inert: DOM interface constructors are empty (instanceof yields false, harmless);`
  - `geometry` (function, line 1415) `* constant geometry (zero real leak);`
  - `size` (function, line 1418) `* the viewport reads a fixed normalized size (matches the 1920 width * anti_fp uses for @media, not the real window);`
  - `_GNU_SOURCE` (macro, line 10) `#define _GNU_SOURCE`
  - `JD_COMPUTED_VALUE_MAX` (macro, line 414) `#define JD_COMPUTED_VALUE_MAX`
  - `JD_QSA_INLINE` (macro, line 477) `#define JD_QSA_INLINE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_intl.h`, `include/js_sandbox.h`, `include/web_storage.h`, `src/js_custom_elements.h`, `src/js_dom_ext.h`, `src/js_dom_internal.h`, `src/js_location_internal.h`, `src/js_native_internal.h`

## src/js_dom_ext.c
- Layer: utility
- Language: c
- Symbols:
  - `registration` (function, line 482) `* registration (options, attributeFilter, subtree) and delivered in one microtask. An
 * observer...`
  - `run` (function, line 1301) `static int run(JSContext *ctx, const char *src, size_t len, const char *name)`
  - `jdx_install` (function, line 1366) `int jdx_install(JSContext *ctx)`
  - `jd_install_repl_api` (function, line 1375) `jd_status jd_install_repl_api(js_context *ctx)`
  - `jd_set_repl_css` (function, line 1383) `jd_status jd_set_repl_css(js_context *ctx, const char *css, size_t len)`
  - `jd_install_geolocation` (function, line 1396) `jd_status jd_install_geolocation(js_context *ctx, double lat, double lon, double accuracy_m)`
  - `jd_install_indexeddb` (function, line 1415) `jd_status jd_install_indexeddb(js_context *ctx)`
  - `identity` (function, line 105) `* identity (host/shadowRoot/mode preserved) but every mutation ALSO mirrors * into the host's light DOM via dom.*...`
  - `cancels` (function, line 954) `* toggled BEFORE the dispatch and restored when a listener cancels (legacy pre-activation);`
- Depends on: `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_ext.h`, `src/js_native_internal.h`

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
  - `try_create_iframe_from_script` (function, line 87) `static int try_create_iframe_from_script(dom_index *idx,
                                        ...`
  - `jd_video_from_scripts` (function, line 204) `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,
                   ...`
  - `jd_inject_video_shim` (function, line 243) `jd_status jd_inject_video_shim(js_context *ctx)`
  - `scan_video_url` (function, line 257) `static int scan_video_url(const char *body, size_t blen,
                           char *out, si...`
  - `jd_process_iframes` (function, line 295) `void jd_process_iframes(js_context *ctx, dom_index *idx,
                        jd_fetch_fn fn, ...`
  - `_GNU_SOURCE` (macro, line 6) `#define _GNU_SOURCE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`, `src/js_native_internal.h`

## src/js_env.c
- Doc: m_perf_now: performance.now: coarsened elapsed since the origin bound at install time, so * it...
- Layer: infrastructure
- Language: c
- Symbols:
  - `wall_clock_ms` (function, line 37) `static uint64_t wall_clock_ms(void)`
  - `monotonic_ms` (function, line 43) `static double monotonic_ms(void)`
  - `m_date_now` (function, line 51) `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_perf_now` (function, line 59) `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_date_now_exact` (function, line 73) `static JSValue m_date_now_exact(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_perf_now_exact` (function, line 79) `static JSValue m_perf_now_exact(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_empty_array` (function, line 99) `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_get_random_values` (function, line 117) `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,
                       ...`
  - `m_random_uuid` (function, line 147) `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_subtle_null` (function, line 164) `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `reject_named` (function, line 173) `static JSValue reject_named(JSContext *ctx, const char *name, const char *msg)`
  - `m_subtle_digest` (function, line 190) `static JSValue m_subtle_digest(JSContext *ctx, JSValueConst this_val,
                           ...`
  - `def_val` (function, line 243) `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)`
  - `def_str` (function, line 249) `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)`
  - `def_int` (function, line 253) `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)`
  - `def_fn` (function, line 257) `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,
                  JSCFuncti...`
  - `build_languages` (function, line 264) `static JSValue build_languages(JSContext *ctx, const char *langs)`
  - `m_captured` (function, line 299) `static JSValue m_captured(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv,
  ...`
  - `promote_to_getters` (function, line 307) `static int promote_to_getters(JSContext *ctx, JSValueConst vals, JSValueConst proto)`
  - `build_navigator` (function, line 332) `static int build_navigator(JSContext *ctx, JSValueConst global, const char *ua_override,
        ...`
  - `build_screen` (function, line 424) `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)`
  - `build_crypto` (function, line 468) `static int build_crypto(JSContext *ctx, JSValueConst global)`
  - `build_perf_timing` (function, line 496) `static int build_perf_timing(JSContext *ctx, JSValueConst perf)`
  - `build_perf_navigation` (function, line 510) `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)`
  - `build_performance` (function, line 522) `static int build_performance(JSContext *ctx, JSValueConst global, int exact)`
  - `override_date_now` (function, line 554) `static int override_date_now(JSContext *ctx, JSValueConst global, int exact)`
  - `make_readback` (function, line 598) `static JSValue make_readback(JSContext *ctx, uint64_t key)`
  - `build_readback_obj` (function, line 606) `static int build_readback_obj(JSContext *ctx, JSValueConst global,
                              ...`
  - `je_install` (function, line 619) `je_status je_install(js_context *ctx, int screen_w, int screen_h)`
  - `je_install_identity` (function, line 623) `je_status je_install_identity(js_context *ctx, int screen_w, int screen_h,
                      ...`
  - `je_install_identity_trusted` (function, line 628) `je_status je_install_identity_trusted(js_context *ctx, int screen_w, int screen_h,
              ...`
  - `je_install_canvas` (function, line 649) `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)`
  - `primitives` (function, line 6) `* the pure anti_fp primitives (one audited source of normalized constants);`
  - `_POSIX_C_SOURCE` (macro, line 17) `#define _POSIX_C_SOURCE`
  - `PERF_ORIGIN_EPOCH` (macro, line 466) `#define PERF_ORIGIN_EPOCH`
- Depends on: `include/anti_fp.h`, `include/js_env.h`, `include/js_sandbox.h`, `include/sha2.h`, `src/js_native_internal.h`

## src/js_events.c
- Doc: jd_eval_default_action: Runs one engine event-dispatch expression and maps its result to the C...
- Layer: infrastructure
- Language: c
- Symbols:
  - `jd_click_state` (struct, line 26)
  - `jd_click_state_new` (function, line 30) `jd_click_state *jd_click_state_new(void)`
  - `jd_click_state_free` (function, line 35) `void jd_click_state_free(jd_click_state *s)`
  - `jd_install_events` (function, line 39) `jd_status jd_install_events(js_context *ctx, jd_click_state *state)`
  - `jd_eval_default_action` (function, line 53) `static int jd_eval_default_action(JSContext *jsctx, const char *src, size_t n,
                  ...`
  - `jd_fire_click` (function, line 67) `int jd_fire_click(js_context *ctx, dom_node_id node_id)`
  - `jd_fire_submit` (function, line 79) `int jd_fire_submit(js_context *ctx, dom_node_id form_node_id)`
  - `jd_escape_js_str` (function, line 92) `static size_t jd_escape_js_str(const char *src, char *dst, size_t dstsz)`
  - `jd_fire_mouse_event` (function, line 164) `int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,
                        const char ...`
  - `_GNU_SOURCE` (macro, line 6) `#define _GNU_SOURCE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`, `src/js_native_internal.h`

## src/js_fetch.c
- Doc: jd_pack_ptr: Carry the host fetch fn + its ctx as a function's closure data, each split into...
- Layer: utility
- Language: c
- Symbols:
  - `jd_pack_ptr` (function, line 29) `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)`
  - `jd_unpack_ptr` (function, line 34) `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)`
  - `jd_reply_object` (function, line 44) `static JSValue jd_reply_object(JSContext *ctx, int rc, int status, const char *rbody,
           ...`
  - `m_host_fetch` (function, line 74) `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `m_host_fetch_async` (function, line 105) `static JSValue m_host_fetch_async(JSContext *ctx, JSValueConst this_val,
                        ...`
  - `jd_install_xhr` (function, line 336) `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)`
  - `jd_net_deliver` (function, line 340) `jd_status jd_net_deliver(js_context *ctx, int rc, int status, const char *body, size_t len,
     ...`
  - `jd_install_xhr_ex` (function, line 361) `jd_status jd_install_xhr_ex(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx,
                   ...`
  - `send` (function, line 128) `* callbacks fire right after send();`
  - `task` (function, line 312) `* current task (the page never waits on it);`
  - `_GNU_SOURCE` (macro, line 6) `#define _GNU_SOURCE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`, `src/js_native_internal.h`


Next: [KB_src_p6.md](KB_src_p6.md)
