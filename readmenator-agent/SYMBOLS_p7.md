# Symbols (page 7 of 14)
Previous: [SYMBOLS_p6.md](SYMBOLS_p6.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `_POSIX_C_SOURCE` | macro | `src/hls.c:22` | `#define _POSIX_C_SOURCE` |
| `hls_parse` | function | `src/hls.c:80` | `hls_status hls_parse(const char *text, size_t len, hls_playlist **out)` |
| `hls_playlist_free` | function | `src/hls.c:253` | `void hls_playlist_free(hls_playlist *pl)` |
| `hls_resolve_url` | function | `src/hls.c:223` | `size_t hls_resolve_url(const char *base_url, const char *segment_url,                        char...` |
| `hls_select_variant` | function | `src/hls.c:202` | `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h)` |
| `last_char` | function | `src/hls.c:38` | `static const char *last_char(const char *s, size_t n, int c)` |
| `name` | function | `src/hls.c:46` | `* attr is the attribute name (e.g. "BANDWIDTH=");` |
| `parse_attr_long` | function | `src/hls.c:48` | `static int parse_attr_long(const char *attrs, const char *end,                            const c...` |
| `parse_attr_resolution` | function | `src/hls.c:62` | `static void parse_attr_resolution(const char *attrs, const char *end,                            ...` |
| `HCF_REPO_DIR` | macro | `src/host_conf.c:8` | `#define HCF_REPO_DIR` |
| `HCF_USER_SUBDIR` | macro | `src/host_conf.c:7` | `#define HCF_USER_SUBDIR` |
| `add_dir` | function | `src/host_conf.c:10` | `static void add_dir(hcf_dirs *out, const char *path)` |
| `hcf_load_allowlist` | function | `src/host_conf.c:76` | `hb_set *hcf_load_allowlist(const hcf_dirs *dirs, const char *fname)` |
| `hcf_load_filter` | function | `src/host_conf.c:65` | `hb_set *hcf_load_filter(const hcf_dirs *dirs)` |
| `hcf_search_dirs` | function | `src/host_conf.c:20` | `void hcf_search_dirs(const char *env, const char *home, hcf_dirs *out)` |
| `hcf_search_dirs_from_env` | function | `src/host_conf.c:32` | `void hcf_search_dirs_from_env(hcf_dirs *out)` |
| `load_into` | function | `src/host_conf.c:58` | `static void load_into(hb_set *s, const char *dir, const char *name, hb_list list)` |
| `read_conf` | function | `src/host_conf.c:37` | `static char *read_conf(const char *dir, const char *name)` |
| `HB_INIT_CAP` | macro | `src/hostblock.c:20` | `#define HB_INIT_CAP` |
| `HB_MAX_HOST` | macro | `src/hostblock.c:19` | `#define HB_MAX_HOST` |
| `hb_check` | function | `src/hostblock.c:193` | `hb_decision hb_check(const hb_set *s, const char *host)` |
| `hb_count` | function | `src/hostblock.c:238` | `size_t hb_count(const hb_set *s, hb_list list)` |
| `hb_free` | function | `src/hostblock.c:149` | `void hb_free(hb_set *s)` |
| `hb_is_allowlisted` | function | `src/hostblock.c:218` | `int hb_is_allowlisted(const hb_set *s, const char *host)` |
| `hb_load` | function | `src/hostblock.c:156` | `hb_status hb_load(hb_set *s, const char *text, hb_list list)` |
| `hb_new` | function | `src/hostblock.c:144` | `hb_set *hb_new(void)` |
| `hb_set` | struct | `src/hostblock.c:30` | `` |
| `hb_table` | struct | `src/hostblock.c:24` | `` |
| `is_domain_char` | function | `src/hostblock.c:122` | `static int is_domain_char(char c)` |
| `is_ip_token` | function | `src/hostblock.c:113` | `static int is_ip_token(const char *s, size_t n)` |
| `lower` | function | `src/hostblock.c:107` | `static char lower(char c)` |
| `table_contains` | function | `src/hostblock.c:92` | `static int table_contains(const hb_table *t, const char *key)` |
| `table_free` | function | `src/hostblock.c:98` | `static void table_free(hb_table *t)` |
| `table_grow` | function | `src/hostblock.c:49` | `static int table_grow(hb_table *t, size_t newcap)` |
| `table_insert` | function | `src/hostblock.c:71` | `static int table_insert(hb_table *t, const char *key, size_t klen)` |
| `table_probe` | function | `src/hostblock.c:38` | `static size_t table_probe(const hb_table *t, const char *key, size_t klen)` |
| `contains_ci` | function | `src/hostedit.c:115` | `static int contains_ci(const char *hs, size_t hl, const char *needle)` |
| `has_host_cb` | function | `src/hostedit.c:105` | `static int has_host_cb(const char *ts, size_t tl, void *ctx)` |
| `he_lower` | function | `src/hostedit.c:12` | `static char he_lower(char c)` |
| `he_make_line` | function | `src/hostedit.c:41` | `he_status he_make_line(const char *host, char *out, size_t cap)` |
| `he_scan` | function | `src/hostedit.c:80` | `static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), void *ctx)` |
| `he_suggest` | function | `src/hostedit.c:164` | `int he_suggest(const char *text, const char *query,                char results[][HE_MAX_HOST + 1...` |
| `he_text_has_host` | function | `src/hostedit.c:109` | `int he_text_has_host(const char *text, const char *host)` |
| `is_ip_token` | function | `src/hostedit.c:67` | `static int is_ip_token(const char *ts, const char *te)` |
| `is_label_char` | function | `src/hostedit.c:16` | `static int is_label_char(char c)` |
| `starts_with_ci` | function | `src/hostedit.c:128` | `static int starts_with_ci(const char *hs, size_t hl, const char *pfx)` |
| `suggest_cb` | function | `src/hostedit.c:144` | `static int suggest_cb(const char *ts, size_t tl, void *vctx)` |
| `suggest_ctx` | struct | `src/hostedit.c:136` | `` |
| `valid_host` | function | `src/hostedit.c:22` | `static int valid_host(const char *host, size_t n)` |
| `_POSIX_C_SOURCE` | macro | `src/html_parse.c:9` | `#define _POSIX_C_SOURCE` |
| `attr_has_token_ci` | function | `src/html_parse.c:251` | `static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle)` |
| `attr_is_event_handler` | function | `src/html_parse.c:47` | `static int attr_is_event_handler(const lxb_dom_attr_t *attr)` |
| `dup_bytes` | function | `src/html_parse.c:27` | `static char *dup_bytes(const lxb_char_t *src, size_t len)` |
| `hp_config_default` | function | `src/html_parse.c:357` | `hp_config hp_config_default(void)` |
| `hp_document` | struct | `src/html_parse.c:21` | `` |
| `hp_document_free` | function | `src/html_parse.c:483` | `void hp_document_free(hp_document *doc)` |
| `hp_document_root` | function | `src/html_parse.c:489` | `const void *hp_document_root(const hp_document *doc)` |
| `hp_element_count` | function | `src/html_parse.c:409` | `size_t hp_element_count(const hp_document *doc)` |
| `hp_event_handler_count` | function | `src/html_parse.c:429` | `size_t hp_event_handler_count(const hp_document *doc)` |
| `hp_extract_script_list` | function | `src/html_parse.c:164` | `hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count)` |
| `hp_extract_stylesheet_hrefs` | function | `src/html_parse.c:294` | `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count)` |
| `hp_extract_text` | function | `src/html_parse.c:445` | `char *hp_extract_text(const hp_document *doc, size_t *out_len)` |
| `hp_free` | function | `src/html_parse.c:479` | `void hp_free(char *buf)` |
| `hp_free_scripts` | function | `src/html_parse.c:238` | `void hp_free_scripts(hp_script *scripts, size_t count)` |
| `hp_free_stylesheet_hrefs` | function | `src/html_parse.c:328` | `void hp_free_stylesheet_hrefs(char **hrefs, size_t count)` |
| `hp_get_title` | function | `src/html_parse.c:464` | `char *hp_get_title(const hp_document *doc, size_t *out_len)` |
| `hp_parse` | function | `src/html_parse.c:375` | `hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out)` |
| `hp_script_count` | function | `src/html_parse.c:419` | `size_t hp_script_count(const hp_document *doc)` |
| `hp_validate_input` | function | `src/html_parse.c:365` | `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg)` |
| `link_is_active_stylesheet` | function | `src/html_parse.c:272` | `static int link_is_active_stylesheet(lxb_dom_element_t *el,                                      ...` |
| `lxb_dom_element_has_attribute` | function | `src/html_parse.c:230` | `&& lxb_dom_element_has_attribute(sel, (const lxb_char_t *)"nomodule", 8);` |
| `node_is_script` | function | `src/html_parse.c:54` | `static int node_is_script(const lxb_dom_node_t *node)` |
| `node_next` | function | `src/html_parse.c:37` | `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` |
| `script_classify` | function | `src/html_parse.c:121` | `static int script_classify(const lxb_dom_node_t *n,                            const lxb_char_t *...` |
| `strip_event_handlers` | function | `src/html_parse.c:334` | `static void strip_event_handlers(lxb_html_document_t *document)` |
| `strip_scripts` | function | `src/html_parse.c:60` | `static void strip_scripts(lxb_html_document_t *document)` |
| `type_is` | function | `src/html_parse.c:100` | `static int type_is(const lxb_char_t *t, size_t len, const char *word)` |
| `type_is_module` | function | `src/html_parse.c:117` | `static int type_is_module(const lxb_char_t *t, size_t len)` |
| `GIF_LZW_MAX_CODES` | macro | `src/image_decode.c:253` | `#define GIF_LZW_MAX_CODES` |
| `PNG_IHDR_MIN` | macro | `src/image_decode.c:34` | `#define PNG_IHDR_MIN` |
| `exit` | function | `src/image_decode.c:6` | `* malformed stream fails closed instead of calling exit(). GIF uses an own pure-C * bounded LZW decoder (no giflib)....` |
| `gb_next_code` | function | `src/image_decode.c:298` | `static int gb_next_code(gif_bits *b, unsigned width, unsigned *out)` |
| `gif_bits` | struct | `src/image_decode.c:290` | `` |
| `gif_deinterlace_row` | function | `src/image_decode.c:319` | `static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh)` |
| `gif_put_pixel` | function | `src/image_decode.c:334` | `static void gif_put_pixel(uint32_t *canvas, uint32_t cw, uint32_t ch,                           u...` |
| `gif_reader` | struct | `src/image_decode.c:255` | `` |
| `gr_skip` | function | `src/image_decode.c:273` | `static int gr_skip(gif_reader *r, size_t n)` |
| `gr_skip_subblocks` | function | `src/image_decode.c:280` | `static int gr_skip_subblocks(gif_reader *r)` |
| `gr_u16le` | function | `src/image_decode.c:266` | `static int gr_u16le(gif_reader *r, uint16_t *out)` |
| `gr_u8` | function | `src/image_decode.c:260` | `static int gr_u8(gif_reader *r, uint8_t *out)` |
| `img_decode` | function | `src/image_decode.c:553` | `img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_gif` | function | `src/image_decode.c:354` | `img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_jpeg` | function | `src/image_decode.c:166` | `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_png` | function | `src/image_decode.c:102` | `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_decode_webp` | function | `src/image_decode.c:520` | `img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out)` |
| `img_dimensions_ok` | function | `src/image_decode.c:68` | `int img_dimensions_ok(uint32_t w, uint32_t h)` |
| `img_fit` | function | `src/image_decode.c:76` | `void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,              double *out_w, do...` |
| `img_format_name` | function | `src/image_decode.c:575` | `const char *img_format_name(img_format f)` |
| `img_pixels_free` | function | `src/image_decode.c:566` | `void img_pixels_free(img_pixels *p)` |
| `img_png_dimensions` | function | `src/image_decode.c:57` | `img_status img_png_dimensions(const uint8_t *bytes, size_t len,                               uin...` |
| `jpeg_err_ctx` | struct | `src/image_decode.c:153` | `` |
| `jpeg_error_longjmp` | function | `src/image_decode.c:158` | `static void jpeg_error_longjmp(j_common_ptr cinfo)` |
| `jpeg_silence` | function | `src/image_decode.c:164` | `static void jpeg_silence(j_common_ptr cinfo)` |
| `premultiply` | function | `src/image_decode.c:90` | `static void premultiply(uint8_t *data, size_t pixels)` |
| `read_be32` | function | `src/image_decode.c:52` | `static uint32_t read_be32(const uint8_t *p)` |
| `IM_MAX_DEPTH` | macro | `src/import_map.c:16` | `#define IM_MAX_DEPTH` |
| `IM_URL_MAX` | macro | `src/import_map.c:17` | `#define IM_URL_MAX` |
| `add` | function | `src/import_map.c:185` | `static int add(im_map *m, int scope, const char *key, const char *addr, const char *doc_url,     ...` |
| `clear` | function | `src/import_map.c:175` | `static void clear(im_map *m)` |
| `dup_s` | function | `src/import_map.c:168` | `static char *dup_s(const char *s)` |
| `eat` | function | `src/import_map.c:44` | `static int eat(jr *r, char c)` |
| `hex4` | function | `src/import_map.c:50` | `static int hex4(const char *s, uint32_t *out)` |
| `im_count` | function | `src/import_map.c:339` | `size_t im_count(const im_map *m)` |
| `im_entry` | struct | `src/import_map.c:19` | `` |
| `im_free` | function | `src/import_map.c:343` | `void im_free(im_map *m)` |
| `im_map` | struct | `src/import_map.c:25` | `` |
| `im_parse` | function | `src/import_map.c:225` | `im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn resolve, void *ctx)` |
| `im_resolve` | function | `src/import_map.c:301` | `int im_resolve(const im_map *m, const char *base, const char *specifier,                im_url_fn...` |
| `jr` | struct | `src/import_map.c:34` | `` |
| `match` | function | `src/import_map.c:272` | `static int match(const im_map *m, int scope, const char *key, char *out, size_t outsz)` |
| `put_utf8` | function | `src/import_map.c:64` | `static size_t put_utf8(char *o, uint32_t cp)` |
| `scope` | type_alias | `src/import_map.c:18` | `typedef struct im_entry { int scope;` |
| `skip` | function | `src/import_map.c:128` | `static void skip(jr *r, int depth)` |
| `specifier_map` | function | `src/import_map.c:209` | `static void specifier_map(jr *r, im_map *m, int scope, const char *doc_url,                      ...` |
| `str` | function | `src/import_map.c:78` | `static char *str(jr *r)` |
| `url_like` | function | `src/import_map.c:156` | `static int url_like(const char *s)` |
| `ws` | function | `src/import_map.c:39` | `static void ws(jr *r)` |
| `anim_effective_dir` | function | `src/interp.c:232` | `static int anim_effective_dir(const ip_anim *a)` |
| `anim_effective_dir_for` | function | `src/interp.c:222` | `static int anim_effective_dir_for(const ip_anim *a, int iter)` |
| `ip_anim_current` | function | `src/interp.c:282` | `double ip_anim_current(const ip_anim *a)` |
| `ip_anim_done` | function | `src/interp.c:320` | `int ip_anim_done(const ip_anim *a)` |
| `ip_anim_init` | function | `src/interp.c:196` | `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease,                   const ip_...` |
| `ip_anim_tick` | function | `src/interp.c:236` | `int ip_anim_tick(ip_anim *a, double dt_ms)` |
| `ip_ease` | function | `src/interp.c:55` | `double ip_ease(double t, const ip_ease_fn *fn)` |
| `ip_ease` | function | `src/interp.c:64` | `case IP_EASE_EASE:         return ip_ease(t, &(ip_ease_fn)` |
| `ip_ease` | function | `src/interp.c:70` | `case IP_EASE_EASE_IN:         return ip_ease(t, &(ip_ease_fn)` |
| `ip_ease` | function | `src/interp.c:76` | `case IP_EASE_EASE_OUT:         return ip_ease(t, &(ip_ease_fn)` |
| `ip_ease` | function | `src/interp.c:82` | `case IP_EASE_EASE_IN_OUT:         return ip_ease(t, &(ip_ease_fn)` |
| `ip_interp` | function | `src/interp.c:162` | `double ip_interp(ip_val_kind kind, double a, double b, double t)` |
| `ip_kf_interp` | function | `src/interp.c:175` | `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf,                     int n_kf, do...` |
| `ip_lerp` | function | `src/interp.c:134` | `double ip_lerp(double a, double b, double t)` |
| `ip_lerp_color` | function | `src/interp.c:139` | `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t)` |
| `sample_bezier_dx` | function | `src/interp.c:23` | `static double sample_bezier_dx(double t, double cx1, double cx2)` |
| `sample_bezier_x` | function | `src/interp.c:18` | `static double sample_bezier_x(double t, double cx1, double cx2)` |
| `sample_bezier_y` | function | `src/interp.c:29` | `static double sample_bezier_y(double t, double cy1, double cy2)` |
| `solve_bezier_t` | function | `src/interp.c:35` | `static double solve_bezier_t(double x, double cx1, double cx2)` |
| `jdce_install` | function | `src/js_custom_elements.c:179` | `int jdce_install(JSContext *ctx)` |
| `FREEDOM_JS_CUSTOM_ELEMENTS_H` | macro | `src/js_custom_elements.h:2` | `#define FREEDOM_JS_CUSTOM_ELEMENTS_H` |
| `jdce_install` | function | `src/js_custom_elements.h:9` | `int jdce_install(JSContext *ctx);` |
| `_GNU_SOURCE` | macro | `src/js_dom.c:10` | `#define _GNU_SOURCE` |
| `attrNames` | function | `src/js_dom.c:612` | `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so      * a missing '...` |
| `empty` | function | `src/js_dom.c:1219` | `* inert: DOM interface constructors are empty (instanceof yields false, harmless);` |
| `enough` | function | `src/js_dom.c:935` | `* enough (cloneNode/lastChild/removeChild/insertBefore) that library feature * detection does not throw: jQuery...` |
| `fails` | function | `src/js_dom.c:1867` | `* cap is reached or an allocation fails (caller stops), else 0. */ static int cb_append(char **bu...` |
| `geometry` | function | `src/js_dom.c:1221` | `* constant geometry (zero real leak);` |
| `jd_flush_custom_elements` | function | `src/js_dom.c:1853` | `void jd_flush_custom_elements(js_context *ctx)` |
| `jd_get_cookies` | function | `src/js_dom.c:2038` | `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)` |
| `jd_handle` | function | `src/js_dom.c:40` | `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out)` |
| `jd_handle_or_null` | function | `src/js_dom.c:47` | `JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h)` |
| `jd_idx` | function | `src/js_dom.c:31` | `dom_index *jd_idx(JSContext *ctx)` |
| `jd_install` | function | `src/js_dom.c:1779` | `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)` |
| `jd_install_console` | function | `src/js_dom.c:1981` | `jd_status jd_install_console(js_context *ctx, fb_buffer *log)` |
| `jd_method` | struct | `src/js_dom.c:429` | `` |
| `jd_opaque_get` | function | `src/js_dom.c:27` | `jd_opaque *jd_opaque_get(JSContext *ctx)` |
| `jd_query_list` | function | `src/js_dom.c:70` | `static JSValue jd_query_list(JSContext *ctx, JSValueConst arg, int by_class)` |
| `jd_set_cookies` | function | `src/js_dom.c:2018` | `jd_status jd_set_cookies(js_context *ctx, const char *cookies)` |
| `jd_set_geometry` | function | `src/js_dom.c:2061` | `jd_status jd_set_geometry(js_context *ctx, const jg_table *geom)` |
| `js_env` | function | `src/js_dom.c:1227` | `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the  * document shim (uses...` |
| `m_append_child` | function | `src/js_dom.c:264` | `static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,                             ...` |
| `m_attr_names` | function | `src/js_dom.c:504` | `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,                             in...` |
| `m_child_node` | function | `src/js_dom.c:159` | `static JSValue m_child_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_clone_node` | function | `src/js_dom.c:289` | `static JSValue m_clone_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_closest` | function | `src/js_dom.c:492` | `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,                          int argc...` |
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
| `m_matches` | function | `src/js_dom.c:480` | `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,                          int argc...` |
| `m_move_children` | function | `src/js_dom.c:275` | `static JSValue m_move_children(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_next_sibling` | function | `src/js_dom.c:188` | `static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,                             ...` |
| `m_node_count` | function | `src/js_dom.c:53` | `static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,                             in...` |
| `m_node_kind` | function | `src/js_dom.c:152` | `static JSValue m_node_kind(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_parent` | function | `src/js_dom.c:135` | `static JSValue m_parent(JSContext *ctx, JSValueConst this_val,                         int argc, ...` |
| `m_precedes` | function | `src/js_dom.c:196` | `static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_query_selector` | function | `src/js_dom.c:438` | `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,                           ...` |
| `m_query_selector_all` | function | `src/js_dom.c:451` | `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,                       ...` |
| `m_rect` | function | `src/js_dom.c:397` | `static JSValue m_rect(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_remove_attribute` | function | `src/js_dom.c:336` | `static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,                         ...` |
| `m_remove_child` | function | `src/js_dom.c:311` | `static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,                             ...` |
| `m_set_attribute` | function | `src/js_dom.c:320` | `static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,                            ...` |
| `m_set_inner_html` | function | `src/js_dom.c:348` | `static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,                           ...` |
| `m_set_text` | function | `src/js_dom.c:217` | `static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_set_title` | function | `src/js_dom.c:239` | `static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,                            int ...` |
| `m_sibling_node` | function | `src/js_dom.c:166` | `static JSValue m_sibling_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `m_tag_name` | function | `src/js_dom.c:112` | `static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_text_content` | function | `src/js_dom.c:207` | `static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,                             ...` |
| `ms` | function | `src/js_dom.c:1071` | `* due is the remaining virtual ms (the trusted parent advances the clock via * OP_TICK -> __tickTimers(elapsed);` |
| `scripts` | function | `src/js_dom.c:772` | `* player scripts (canPlayType feature-detection, play/pause, muted/loop * reflection, buffered ranges) run without...` |
| `size` | function | `src/js_dom.c:1224` | `* the viewport reads a fixed normalized size (matches the 1920 width * anti_fp uses for @media, not the real window);` |
| `table` | function | `src/js_dom.c:572` | `* a table (dom.viewport() non-null);` |
| `identity` | function | `src/js_dom_ext.c:96` | `* identity (host/shadowRoot/mode preserved) but every mutation ALSO mirrors * into the host's light DOM via dom.*...` |
| `jdx_install` | function | `src/js_dom_ext.c:374` | `int jdx_install(JSContext *ctx)` |
| `run` | function | `src/js_dom_ext.c:366` | `static int run(JSContext *ctx, const char *src, size_t len, const char *name)` |
| `FREEDOM_JS_DOM_EXT_H` | macro | `src/js_dom_ext.h:2` | `#define FREEDOM_JS_DOM_EXT_H` |
| `jdx_install` | function | `src/js_dom_ext.h:10` | `int jdx_install(JSContext *ctx);` |
| `FREEDOM_JS_DOM_INTERNAL_H` | macro | `src/js_dom_internal.h:2` | `#define FREEDOM_JS_DOM_INTERNAL_H` |
| `jd_handle` | function | `src/js_dom_internal.h:14` | `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out);` |
| `jd_idx` | function | `src/js_dom_internal.h:12` | `dom_index *jd_idx(JSContext *ctx);` |
| `jd_opaque_get` | function | `src/js_dom_internal.h:11` | `jd_opaque *jd_opaque_get(JSContext *ctx);` |
| `_GNU_SOURCE` | macro | `src/js_embed.c:6` | `#define _GNU_SOURCE` |
| `jd_inject_video_shim` | function | `src/js_embed.c:242` | `jd_status jd_inject_video_shim(js_context *ctx)` |
| `jd_process_iframes` | function | `src/js_embed.c:294` | `void jd_process_iframes(js_context *ctx, dom_index *idx,                         jd_fetch_fn fn, ...` |
| `jd_video_from_scripts` | function | `src/js_embed.c:203` | `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,                    ...` |
| `scan_video_url` | function | `src/js_embed.c:256` | `static int scan_video_url(const char *body, size_t blen,                            char *out, si...` |
| `try_create_iframe_from_script` | function | `src/js_embed.c:86` | `static int try_create_iframe_from_script(dom_index *idx,                                         ...` |
| `FP_MIME_COUNT` | macro | `src/js_env.c:260` | `#define FP_MIME_COUNT` |
| `PERF_ORIGIN_EPOCH` | macro | `src/js_env.c:344` | `#define PERF_ORIGIN_EPOCH` |
| `_POSIX_C_SOURCE` | macro | `src/js_env.c:17` | `#define _POSIX_C_SOURCE` |
| `build_crypto` | function | `src/js_env.c:346` | `static int build_crypto(JSContext *ctx, JSValueConst global)` |
| `build_languages` | function | `src/js_env.c:174` | `static JSValue build_languages(JSContext *ctx)` |
| `build_navigator` | function | `src/js_env.c:198` | `static int build_navigator(JSContext *ctx, JSValueConst global)` |
| `build_perf_navigation` | function | `src/js_env.c:388` | `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)` |
| `build_perf_timing` | function | `src/js_env.c:374` | `static int build_perf_timing(JSContext *ctx, JSValueConst perf)` |
| `build_performance` | function | `src/js_env.c:400` | `static int build_performance(JSContext *ctx, JSValueConst global)` |
| `build_readback_obj` | function | `src/js_env.c:484` | `static int build_readback_obj(JSContext *ctx, JSValueConst global,                               ...` |
| `build_screen` | function | `src/js_env.c:302` | `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)` |
| `def_fn` | function | `src/js_env.c:167` | `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,                   JSCFuncti...` |
| `def_int` | function | `src/js_env.c:163` | `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)` |
| `def_str` | function | `src/js_env.c:159` | `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)` |
| `def_val` | function | `src/js_env.c:153` | `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)` |
| `je_install` | function | `src/js_env.c:497` | `je_status je_install(js_context *ctx, int screen_w, int screen_h)` |
| `je_install_canvas` | function | `src/js_env.c:516` | `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)` |
| `m_date_now` | function | `src/js_env.c:49` | `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_empty_array` | function | `src/js_env.c:77` | `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,                              ...` |
| `m_get_random_values` | function | `src/js_env.c:85` | `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,                        ...` |
| `m_perf_now` | function | `src/js_env.c:57` | `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,                           int ar...` |
| `m_random_uuid` | function | `src/js_env.c:125` | `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,                              ...` |
| `m_subtle_null` | function | `src/js_env.c:142` | `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,                              ...` |
| `make_readback` | function | `src/js_env.c:476` | `static JSValue make_readback(JSContext *ctx, uint64_t key)` |
| `methods` | function | `src/js_env.c:201` | `* capability methods (sendBeacon, spec/js_dom.md 7h) without touching any * fingerprintable field. An untrusted...` |
| `monotonic_ms` | function | `src/js_env.c:41` | `static double monotonic_ms(void)` |
| `override_date_now` | function | `src/js_env.c:432` | `static int override_date_now(JSContext *ctx, JSValueConst global)` |
| `primitives` | function | `src/js_env.c:6` | `* the pure anti_fp primitives (one audited source of normalized constants);` |
| `wall_clock_ms` | function | `src/js_env.c:35` | `static uint64_t wall_clock_ms(void)` |
| `_GNU_SOURCE` | macro | `src/js_events.c:6` | `#define _GNU_SOURCE` |
| `jd_click_state` | struct | `src/js_events.c:25` | `` |
| `jd_click_state_free` | function | `src/js_events.c:34` | `void jd_click_state_free(jd_click_state *s)` |
| `jd_click_state_new` | function | `src/js_events.c:29` | `jd_click_state *jd_click_state_new(void)` |
| `jd_escape_js_str` | function | `src/js_events.c:91` | `static size_t jd_escape_js_str(const char *src, char *dst, size_t dstsz)` |
| `jd_eval_default_action` | function | `src/js_events.c:52` | `static int jd_eval_default_action(JSContext *jsctx, const char *src, size_t n,                   ...` |
| `jd_fire_click` | function | `src/js_events.c:66` | `int jd_fire_click(js_context *ctx, dom_node_id node_id)` |
| `jd_fire_mouse_event` | function | `src/js_events.c:163` | `int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,                         const char ...` |
| `jd_fire_submit` | function | `src/js_events.c:78` | `int jd_fire_submit(js_context *ctx, dom_node_id form_node_id)` |
| `jd_install_events` | function | `src/js_events.c:38` | `jd_status jd_install_events(js_context *ctx, jd_click_state *state)` |
| `_GNU_SOURCE` | macro | `src/js_fetch.c:6` | `#define _GNU_SOURCE` |
| `jd_install_xhr` | function | `src/js_fetch.c:203` | `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)` |
| `jd_pack_ptr` | function | `src/js_fetch.c:28` | `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)` |
| `jd_unpack_ptr` | function | `src/js_fetch.c:33` | `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)` |
| `m_host_fetch` | function | `src/js_fetch.c:46` | `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,                             in...` |
| `send` | function | `src/js_fetch.c:92` | `* callbacks fire right after send();` |
| `task` | function | `src/js_fetch.c:179` | `* current task (the page never waits on it);` |
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
| `jd_lp_set` | function | `src/js_location.c:24` | `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,                       const ...` |
| `jd_pop_state` | function | `src/js_location.c:250` | `int jd_pop_state(js_context *ctx, int index)` |
| `jd_set_location` | function | `src/js_location.c:139` | `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)` |
| `jd_take_history` | function | `src/js_location.c:219` | `char *jd_take_history(js_context *ctx, int *go)` |
| `jd_take_nav_request` | function | `src/js_location.c:173` | `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)` |
| `jl_m_hist_target` | function | `src/js_location.c:35` | `JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` |
| `FREEDOM_JS_LOCATION_INTERNAL_H` | macro | `src/js_location_internal.h:2` | `#define FREEDOM_JS_LOCATION_INTERNAL_H` |
| `header` | function | `src/js_location_internal.h:6` | `* stay out of every public header (include/ never sees quickjs.h). */ #include "quickjs.h" JSValue...` |
| `eq_ci` | function | `src/js_policy.c:12` | `static int eq_ci(const char *a, const char *b)` |
| `jsp_enabled` | function | `src/js_policy.c:22` | `bool jsp_enabled(jsp_mode mode, int host_allowlisted)` |
| `jsp_mode_from_str` | function | `src/js_policy.c:39` | `jsp_mode jsp_mode_from_str(const char *s)` |
| `jsp_mode_str` | function | `src/js_policy.c:51` | `const char *jsp_mode_str(jsp_mode mode)` |
| `jsp_present_trusted` | function | `src/js_policy.c:35` | `bool jsp_present_trusted(int host_allowlisted)` |
| `jsp_trusted` | function | `src/js_policy.c:31` | `bool jsp_trusted(bool js_enabled, int host_allowlisted)` |
| `JS_MODULE_URL_MAX` | macro | `src/js_sandbox.c:527` | `#define JS_MODULE_URL_MAX` |
| `_POSIX_C_SOURCE` | macro | `src/js_sandbox.c:12` | `#define _POSIX_C_SOURCE` |
| `arm_deadline` | function | `src/js_sandbox.c:327` | `static void arm_deadline(js_context *ctx, uint64_t budget_ms)` |
| `host_dup` | function | `src/js_sandbox.c:99` | `static char *host_dup(const char *src, size_t len)` |
| `is_ascii_digit` | function | `src/js_sandbox.c:127` | `static int is_ascii_digit(char c)` |
| `jm_calloc` | function | `src/js_sandbox.c:63` | `static void *jm_calloc(void *opaque, size_t count, size_t size)` |
| `jm_free` | function | `src/js_sandbox.c:73` | `static void jm_free(void *opaque, void *ptr)` |
| `jm_malloc` | function | `src/js_sandbox.c:55` | `static void *jm_malloc(void *opaque, size_t size)` |
| `jm_realloc` | function | `src/js_sandbox.c:79` | `static void *jm_realloc(void *opaque, void *ptr, size_t size)` |
| `jm_usable_size` | function | `src/js_sandbox.c:89` | `static size_t jm_usable_size(const void *ptr)` |
| `js_context` | struct | `src/js_sandbox.c:33` | `` |
| `js_context_free` | function | `src/js_sandbox.c:316` | `void js_context_free(js_context *ctx)` |
| `js_context_new` | function | `src/js_sandbox.c:277` | `js_status js_context_new(const js_limits *lim, js_context **out)` |
| `js_context_raw` | function | `src/js_sandbox.c:522` | `void *js_context_raw(js_context *ctx)` |
| `js_eval` | function | `src/js_sandbox.c:347` | `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)` |
| `js_eval_module` | function | `src/js_sandbox.c:621` | `js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,         ...` |
| `js_eval_named` | function | `src/js_sandbox.c:351` | `js_status js_eval_named(js_context *ctx, const char *src, size_t len,                         con...` |
| `js_eval_once` | function | `src/js_sandbox.c:452` | `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)` |
| `js_install_realms` | function | `src/js_sandbox.c:783` | `js_status js_install_realms(js_context *ctx)` |
| `js_interrupt_cb` | function | `src/js_sandbox.c:114` | `static int js_interrupt_cb(JSRuntime *rt, void *opaque)` |
| `js_limits_default` | function | `src/js_sandbox.c:248` | `js_limits js_limits_default(void)` |
| `js_loc_from_stack` | function | `src/js_sandbox.c:129` | `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,                       i...` |
| `js_mem_state` | struct | `src/js_sandbox.c:27` | `` |
| `js_pump_jobs` | function | `src/js_sandbox.c:434` | `int js_pump_jobs(js_context *ctx, int max_jobs)` |
| `js_result_free` | function | `src/js_sandbox.c:465` | `void js_result_free(js_result *res)` |
| `js_set_current_script` | function | `src/js_sandbox.c:489` | `void js_set_current_script(js_context *ctx, const char *src, const char *type)` |
| `js_set_module_host` | function | `src/js_sandbox.c:591` | `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,                         js...` |
| `js_set_time_budget` | function | `src/js_sandbox.c:342` | `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)` |
| `js_validate_source` | function | `src/js_sandbox.c:266` | `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)` |
| `limit` | type_alias | `src/js_sandbox.c:27` | `typedef struct js_mem_state { size_t limit;` |
| `limits_resolve` | function | `src/js_sandbox.c:257` | `static js_limits limits_resolve(const js_limits *lim)` |
| `m_realm_clone` | function | `src/js_sandbox.c:761` | `static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,                    ...` |
| `m_realm_eval` | function | `src/js_sandbox.c:725` | `static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,                     ...` |
| `m_realm_new` | function | `src/js_sandbox.c:711` | `static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,                      ...` |
| `mod_fail` | function | `src/js_sandbox.c:606` | `static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,       ...` |
| `mod_loader` | function | `src/js_sandbox.c:552` | `static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque)` |
| `mod_normalize` | function | `src/js_sandbox.c:588` | `static char *mod_normalize(JSContext *jc, const char *base, const char *name, void *opaque);` |
| `mod_set_meta` | function | `src/js_sandbox.c:543` | `static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url)` |
| `realm_of` | function | `src/js_sandbox.c:688` | `static JSContext *realm_of(js_context *c, JSValueConst g)` |
| `throw_named` | function | `src/js_sandbox.c:701` | `static JSValue throw_named(JSContext *ctx, const char *name, const char *msg)` |
| `timespec_reached` | function | `src/js_sandbox.c:108` | `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)` |
| `undefined` | function | `src/js_sandbox.c:221` | `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx...` |
| `explicitly` | function | `src/js_trusted.c:344` | `* explicitly (no window, no document). Delivery is always a timer task. */ static const char JT_W...` |
| `hex_nibble` | function | `src/js_trusted.c:137` | `static int hex_nibble(char c)` |
| `jt_enable_open` | function | `src/js_trusted.c:26` | `jd_status jt_enable_open(js_context *ctx)` |
| `jt_enable_storage` | function | `src/js_trusted.c:275` | `jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len)` |
| `jt_enable_worker` | function | `src/js_trusted.c:425` | `jd_status jt_enable_worker(js_context *ctx)` |
| `jt_enable_ws` | function | `src/js_trusted.c:120` | `jd_status jt_enable_ws(js_context *ctx)` |
| `jt_seed_ctx` | struct | `src/js_trusted.c:263` | `` |
| `jt_seed_pair` | function | `src/js_trusted.c:265` | `static void jt_seed_pair(void *vctx, const char *k, size_t kl, const char *v, size_t vl)` |
| `jt_take_opens` | function | `src/js_trusted.c:42` | `char *jt_take_opens(js_context *ctx)` |
| `jt_take_storage` | function | `src/js_trusted.c:296` | `int jt_take_storage(js_context *ctx, char **out, size_t *len)` |
| `jt_take_ws` | function | `src/js_trusted.c:168` | `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap)` |
| `jt_ws_event` | function | `src/js_trusted.c:210` | `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len)` |
| `jt_ws_ops_free` | function | `src/js_trusted.c:132` | `void jt_ws_ops_free(jt_ws_op *ops, size_t n)` |
| `ws_payload` | function | `src/js_trusted.c:144` | `static char *ws_payload(int kind, const char *s, size_t n, size_t *out_len)` |
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
| `LS_ARGON2_M_KIB` | macro | `src/local_store.c:724` | `#define LS_ARGON2_M_KIB` |
| `LS_ARGON2_P` | macro | `src/local_store.c:725` | `#define LS_ARGON2_P` |
| `LS_ARGON2_T` | macro | `src/local_store.c:723` | `#define LS_ARGON2_T` |
| `LS_KDF_ARGON2ID` | macro | `src/local_store.c:720` | `#define LS_KDF_ARGON2ID` |
| `LS_KDF_NONE` | macro | `src/local_store.c:719` | `#define LS_KDF_NONE` |
| `LS_VERSION` | macro | `src/local_store.c:718` | `#define LS_VERSION` |
| `OFF_AEAD` | macro | `src/local_store.c:730` | `#define OFF_AEAD` |
| `OFF_KDF` | macro | `src/local_store.c:731` | `#define OFF_KDF` |
| `OFF_MAGIC` | macro | `src/local_store.c:728` | `#define OFF_MAGIC` |
| `OFF_NONCE` | macro | `src/local_store.c:733` | `#define OFF_NONCE` |
| `OFF_SALT` | macro | `src/local_store.c:732` | `#define OFF_SALT` |
| `OFF_VERSION` | macro | `src/local_store.c:729` | `#define OFF_VERSION` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:3` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:14` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:25` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:36` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:47` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:58` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:69` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:80` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:91` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:102` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:113` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:124` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:135` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:146` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:157` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:168` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:179` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:190` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:201` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:212` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:223` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:234` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:245` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:256` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:267` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:278` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:289` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:300` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:311` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:322` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:333` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:344` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:355` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:366` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:377` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:388` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:399` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:410` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:421` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:432` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:443` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:454` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:465` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:476` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:487` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:498` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:509` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:520` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:531` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:542` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:553` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:564` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:575` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:586` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:597` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:608` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:619` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:630` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:641` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:652` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:663` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:674` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_LANES` | macro | `src/local_store.c:709` | `#define OSSL_KDF_PARAM_ARGON2_LANES` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:6` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:17` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:28` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:39` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:50` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:61` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:72` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:83` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:94` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:105` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:116` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:127` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:138` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:149` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:160` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:171` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:182` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:193` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:204` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:215` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:226` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:237` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:248` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:259` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:270` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:281` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:292` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:303` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:314` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:325` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:336` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:347` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:358` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:369` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:380` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:391` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:402` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:413` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:424` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:435` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:446` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:457` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:468` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:479` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:490` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:501` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:512` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:523` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:534` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |
| `OSSL_KDF_PARAM_ARGON2_MEMCOST` | macro | `src/local_store.c:545` | `#define OSSL_KDF_PARAM_ARGON2_MEMCOST` |

Next: [SYMBOLS_p8.md](SYMBOLS_p8.md)
