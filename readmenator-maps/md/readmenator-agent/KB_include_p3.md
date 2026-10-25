# Subsystem: include (page 3 of 5)
Previous: [KB_include_p2.md](KB_include_p2.md)

## include/html_parse.h
- Doc: hp_script: One executable <script>.
- Layer: utility
- Language: h
- Symbols:
  - `hp_config` (struct, line 32)
  - `hp_script` (struct, line 76)
  - `hp_status` (enum, line 22)
  - `max_bytes` (type_alias, line 31) `typedef struct hp_config { size_t max_bytes;`
  - `hp_document` (type_alias, line 39) `typedef struct hp_document hp_document;`
  - `dropped` (function, line 47) `* dropped (not executed). */ #define HP_MAX_SCRIPTS ((size_t)4096) /* Returns a configuration with the secure...`
  - `cfg` (function, line 57) `* policy in cfg (cfg == NULL => secure defaults). No script is ever executed. * html == NULL or out == NULL =>...`
  - `hp_element_count` (function, line 63) `size_t hp_element_count(const hp_document *doc);`
  - `hp_script_count` (function, line 64) `size_t hp_script_count(const hp_document *doc);`
  - `hp_event_handler_count` (function, line 65) `size_t hp_event_handler_count(const hp_document *doc);`
  - `hp_extract_text` (function, line 69) `char *hp_extract_text(const hp_document *doc, size_t *out_len);`
  - `hp_get_title` (function, line 70) `char *hp_get_title(const hp_document *doc, size_t *out_len);`
  - `src` (function, line 90) `* carry their raw src (a <script src> with an inline body lists ONLY the src -- * browser rule: when src is present...`
  - `modules` (function, line 94) `* ES modules (import/export cannot run as a classic script), and template blocks * (text/x-jquery-tmpl, text/html...`
  - `hp_free_scripts` (function, line 111) `void hp_free_scripts(hp_script *scripts, size_t count);`
  - `hp_extract_stylesheet_hrefs` (function, line 127) `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count);`
  - `hp_free_stylesheet_hrefs` (function, line 130) `void hp_free_stylesheet_hrefs(char **hrefs, size_t count);`
  - `hp_free` (function, line 133) `void hp_free(char *buf);`
  - `hp_document_free` (function, line 136) `void hp_document_free(hp_document *doc);`
  - `hp_document_root` (function, line 142) `const void *hp_document_root(const hp_document *doc);`
  - `FREEDOM_HTML_PARSE_H` (macro, line 2) `#define FREEDOM_HTML_PARSE_H`
  - `HP_DEFAULT_MAX_BYTES` (macro, line 41) `#define HP_DEFAULT_MAX_BYTES`
  - `HP_MAX_SCRIPTS` (macro, line 48) `#define HP_MAX_SCRIPTS`
  - `HP_MAX_STYLESHEETS` (macro, line 115) `#define HP_MAX_STYLESHEETS`
- Imported by: `gui/freedom_view.c`, `include/dom.h`, `include/page_view.h`, `src/dom.c`, `src/freedom.c`, `src/html_parse.c`, `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/page_view.c`, `src/renderer.c`, `src/tab.c`, `tests/test_dom.c`, `tests/test_html_parse.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_page_view.c`

## include/http_cache.h
- Doc: hc_parse_http_date: } hc_class; typedef struct hc_meta { char   final_url[HC_URL_MAX]; char...
- Layer: presentation
- Language: h
- Symbols:
  - `hc_meta` (struct, line 44)
  - `hc_status` (enum, line 28)
  - `hc_class` (enum, line 38)
  - `final_url` (type_alias, line 43) `typedef struct hc_meta { char final_url[HC_URL_MAX];`
  - `hc_store` (type_alias, line 66) `typedef struct hc_store hc_store;`
  - `hc_parse_http_date` (function, line 56) `time_t hc_parse_http_date(const char *s);`
  - `by` (function, line 59) `* something to reuse it by (validator, max-age or Expires). */ int hc_storable(long http_code, const hc_meta *m...`
  - `hc_lifetime` (function, line 63) `long hc_lifetime(const hc_meta *m);`
  - `hc_close` (function, line 72) `void hc_close(hc_store *s);`
  - `hc_body_free` (function, line 78) `void hc_body_free(uint8_t *body, size_t len);`
  - `hc_clear` (function, line 84) `void hc_clear(hc_store *s);`
  - `FREEDOM_HTTP_CACHE_H` (macro, line 2) `#define FREEDOM_HTTP_CACHE_H`
  - `HC_VAL_MAX` (macro, line 20) `#define HC_VAL_MAX`
  - `HC_URL_MAX` (macro, line 21) `#define HC_URL_MAX`
  - `HC_TYPE_MAX` (macro, line 22) `#define HC_TYPE_MAX`
  - `HC_MAX_ENTRY` (macro, line 23) `#define HC_MAX_ENTRY`
  - `HC_MAX_TOTAL` (macro, line 24) `#define HC_MAX_TOTAL`
  - `HC_REDIRECT_TTL` (macro, line 25) `#define HC_REDIRECT_TTL`
  - `HC_HEURISTIC_CAP` (macro, line 26) `#define HC_HEURISTIC_CAP`
- Depends on: `include/local_store.h`
- Imported by: `include/cached_fetch.h`, `src/http_cache.c`, `tests/test_http_cache.c`

## include/identity.h
- Doc: idn_defaults: enum { IDN_REJ_UA   = 1 << 0, IDN_REJ_LANG = 1 << 1, IDN_REJ_GEO  = 1 << 2 }...
- Layer: utility
- Language: h
- Symbols:
  - `idn_config` (struct, line 37)
  - `idn_geo_mode` (enum, line 25)
  - `user_agent` (type_alias, line 36) `typedef struct idn_config { char user_agent[IDN_UA_MAX];`
  - `idn_defaults` (function, line 45) `void idn_defaults(idn_config *c);`
  - `idn_is_default` (function, line 48) `int idn_is_default(const idn_config *c);`
  - `idn_set_user_agent` (function, line 51) `int idn_set_user_agent(idn_config *c, const char *ua);`
  - `idn_set_languages` (function, line 52) `int idn_set_languages(idn_config *c, const char *list);`
  - `idn_set_geo` (function, line 53) `int idn_set_geo(idn_config *c, double lat, double lon, double accuracy_m);`
  - `idn_clear_geo` (function, line 54) `void idn_clear_geo(idn_config *c);`
  - `idn_user_agent` (function, line 57) `const char *idn_user_agent(const idn_config *c);`
  - `idn_accept_language` (function, line 58) `size_t idn_accept_language(const idn_config *c, char *out, size_t cap);`
  - `idn_primary_language` (function, line 59) `size_t idn_primary_language(const idn_config *c, char *out, size_t cap);`
  - `idn_serialize` (function, line 63) `size_t idn_serialize(const idn_config *c, char *out, size_t cap);`
  - `idn_parse` (function, line 67) `void idn_parse(idn_config *c, const char *text);`
  - `idn_apply_query` (function, line 70) `unsigned idn_apply_query(idn_config *c, const char *query);`
  - `idn_render_page` (function, line 73) `size_t idn_render_page(const idn_config *c, char *out, size_t cap);`
  - `FREEDOM_IDENTITY_H` (macro, line 2) `#define FREEDOM_IDENTITY_H`
  - `IDN_UA_MAX` (macro, line 16) `#define IDN_UA_MAX`
  - `IDN_LANG_MAX` (macro, line 17) `#define IDN_LANG_MAX`
  - `IDN_LANG_TAGS_MAX` (macro, line 18) `#define IDN_LANG_TAGS_MAX`
  - `IDN_SERIAL_MAX` (macro, line 19) `#define IDN_SERIAL_MAX`
  - `IDN_PAGE_MAX` (macro, line 20) `#define IDN_PAGE_MAX`
  - `IDN_GEO_ACC_MIN` (macro, line 22) `#define IDN_GEO_ACC_MIN`
  - `IDN_GEO_ACC_MAX` (macro, line 23) `#define IDN_GEO_ACC_MAX`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/identity.c`, `src/tab.c`, `tests/test_identity.c`

## include/image_decode.h
- Doc: img_pixels: A decoded bitmap that owns its pixel buffer.
- Layer: utility
- Language: h
- Symbols:
  - `img_pixels` (struct, line 56)
  - `img_format` (enum, line 33)
  - `img_status` (enum, line 41)
  - `width` (type_alias, line 56) `typedef struct img_pixels { uint32_t width;`
  - `guards` (function, line 25) `* guards (in-memory source only, longjmp error manager so a bad stream never * calls exit(), dimension caps before...`
  - `img_dimensions_ok` (function, line 78) `int img_dimensions_ok(uint32_t w, uint32_t h);`
  - `inputs` (function, line 81) `* Degenerate inputs (<= 0) yield (0,0). Pure. */ void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h...`
  - `decode` (function, line 92) `* the declared dimensions BEFORE the full decode (anti-bomb), decodes to RGB and * expands to BGRA. Rejects non-JPEG...`
  - `img_pixels_free` (function, line 121) `void img_pixels_free(img_pixels *p);`
  - `img_format_name` (function, line 124) `const char *img_format_name(img_format f);`
  - `FREEDOM_IMAGE_DECODE_H` (macro, line 2) `#define FREEDOM_IMAGE_DECODE_H`
  - `IMG_MAX_DIM` (macro, line 65) `#define IMG_MAX_DIM`
  - `IMG_MAX_PIXELS` (macro, line 66) `#define IMG_MAX_PIXELS`
- Imported by: `gui/browser_ui.c`, `src/image_decode.c`, `src/tab.c`, `tests/test_freedom.c`, `tests/test_image_decode.c`

## include/import_map.h
- Doc: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- Layer: utility
- Language: h
- Symbols:
  - `im_map` (type_alias, line 23) `typedef struct im_map im_map;`
  - `algorithm` (function, line 13) `* resolution algorithm (scopes, exact and prefix matches). URL resolution is the * caller's (the same resolver the...`
  - `map` (function, line 28) `* map (fail closed = no mapping). NULL only on OOM. */ im_map *im_parse(const char *json, size_t len, const char...`
  - `im_resolve` (function, line 33) `int im_resolve(const im_map *m, const char *base, const char *specifier, im_url_fn resolve, void *ctx, char *out...`
  - `im_count` (function, line 37) `size_t im_count(const im_map *m);`
  - `im_free` (function, line 40) `void im_free(im_map *m);`
  - `FREEDOM_IMPORT_MAP_H` (macro, line 2) `#define FREEDOM_IMPORT_MAP_H`
  - `IM_MAX_TEXT` (macro, line 17) `#define IM_MAX_TEXT`
  - `IM_MAX_ENTRIES` (macro, line 18) `#define IM_MAX_ENTRIES`
  - `IM_MAX_SCOPES` (macro, line 19) `#define IM_MAX_SCOPES`
- Imported by: `src/import_map.c`, `src/prefetch.c`, `src/tab.c`, `tests/test_import_map.c`

## include/interp.h
- Doc: ip_ease: Compute eased t for normalized t ∈ [0,1].
- Layer: utility
- Language: h
- Symbols:
  - `ip_ease_fn` (struct, line 38)
  - `ip_keyframe` (struct, line 70)
  - `ip_anim` (struct, line 101)
  - `ip_easing` (enum, line 25)
  - `ip_val_kind` (enum, line 54)
  - `ip_direction` (enum, line 87)
  - `ip_fill_mode` (enum, line 94)
  - `kind` (type_alias, line 37) `typedef struct ip_ease_fn { ip_easing kind;`
  - `pct` (type_alias, line 69) `typedef struct ip_keyframe { double pct;`
  - `val_kind` (type_alias, line 100) `typedef struct ip_anim { ip_val_kind val_kind;`
  - `ip_ease` (function, line 48) `double ip_ease(double t, const ip_ease_fn *fn);`
  - `ip_lerp` (function, line 60) `double ip_lerp(double a, double b, double t);`
  - `ip_lerp_color` (function, line 61) `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t);`
  - `ip_interp` (function, line 62) `double ip_interp(ip_val_kind kind, double a, double b, double t);`
  - `ip_kf_interp` (function, line 78) `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf, int n_kf, double pct);`
  - `ip_anim_init` (function, line 121) `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease, const ip_keyframe *kf, int n_kf, double...`
  - `ip_anim_tick` (function, line 128) `int ip_anim_tick(ip_anim *a, double dt_ms);`
  - `ip_anim_current` (function, line 131) `double ip_anim_current(const ip_anim *a);`
  - `ip_anim_done` (function, line 134) `int ip_anim_done(const ip_anim *a);`
  - `FREEDOM_INTERP_H` (macro, line 2) `#define FREEDOM_INTERP_H`
  - `IP_MAX_KEYFRAMES` (macro, line 68) `#define IP_MAX_KEYFRAMES`
  - `IP_ITERATION_INFINITE` (macro, line 85) `#define IP_ITERATION_INFINITE`
- Imported by: `gui/browser_ui.c`, `src/interp.c`, `tests/test_interp.c`

## include/js_dom.h
- Doc: jd_iframe_track: Tracks iframes already processed by jd_process_iframes, to avoid re-fetching...
- Layer: utility
- Language: h
- Symbols:
  - `jd_iframe_track` (struct, line 41)
  - `jd_opaque` (struct, line 46)
  - `jd_status` (enum, line 25)
  - `jd_click_state` (type_alias, line 35) `typedef struct jd_click_state jd_click_state;`
  - `processed` (type_alias, line 41) `typedef struct jd_iframe_track { dom_node_id processed[JD_IFRAME_TRACK_MAX];`
  - `opaque` (function, line 66) `* the engine runtime opaque (unreachable from script);`
  - `global` (function, line 73) `* globals: page scripts never see them and an existing page global (jQuery's `$`) is * never replaced. Read-only...`
  - `jd_install_repl_api` (function, line 82) `* jd_install_repl_api (the shim reads and deletes the carrier global, so a page script never * sees it). css == NULL...`
  - `place` (function, line 87) `* configured place (spec/identity.md), no sensor, no network. Call it ONLY for a trusted host * with geolocation set...`
  - `getComputedStyle` (function, line 108) `* getComputedStyle (spec/js_computed_style.md). fn writes the computed value of the * kebab-case `prop` of element h...`
  - `jd_click_state_free` (function, line 118) `* jd_click_state_free(). Bound to one context via jd_install_events(). */ jd_click_state *jd_click_state_new(void);`
  - `run` (function, line 127) `* run (no handler registered, or handlers ran without calling preventDefault()), * and 0 if a handler called...`
  - `preventDefault` (function, line 134) `* preventDefault() was called, 1 if the default (form submission) should proceed. * ctx == NULL or no form found =>...`
  - `host` (function, line 163) `* for a trusted host (allow.conf AND js.conf);`
  - `jd_get_cookies` (function, line 174) `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz);`
  - `out_status` (function, line 182) `* On success returns 0 and sets *out_status (HTTP status, 0 if unknown), *out_body / * *out_body_len (response...`
  - `jd_process_iframes` (function, line 203) `* BEFORE jd_process_iframes() (so iframes are in the DOM for it to process). * ctx == NULL => JD_ERR_NULL_ARG. */...`
  - `URLs` (function, line 210) `* video URLs (.m3u8 then .mp4 patterns), and creates <video> elements in the document for * any found. Does NOT...`
  - `jd_video_from_scripts` (function, line 224) `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts, const size_t *script_lens, size_t...`
  - `jd_flush_custom_elements` (function, line 235) `void jd_flush_custom_elements(js_context *ctx);`
  - `FREEDOM_JS_DOM_H` (macro, line 2) `#define FREEDOM_JS_DOM_H`
  - `JD_IFRAME_TRACK_MAX` (macro, line 40) `#define JD_IFRAME_TRACK_MAX`
  - `JD_REPL_CSS_MAX` (macro, line 79) `#define JD_REPL_CSS_MAX`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/js_geom.h`, `include/js_location.h`, `include/js_sandbox.h`, `include/url.h`
- Imported by: `include/js_location.h`, `include/js_trusted.h`, `src/js_dom.c`, `src/js_dom_ext.c`, `src/js_dom_internal.h`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/js_location.c`, `src/tab.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`

## include/js_env.h
- Layer: infrastructure
- Language: h
- Symbols:
  - `je_status` (enum, line 27)
  - `poisoned` (function, line 49) `* readback is poisoned (deterministic within an origin, unlinkable across * sessions and across origins) to defeat...`
  - `FREEDOM_JS_ENV_H` (macro, line 2) `#define FREEDOM_JS_ENV_H`
- Depends on: `include/js_sandbox.h`
- Imported by: `src/js_env.c`, `src/tab.c`, `tests/test_js_env.c`

## include/js_geom.h
- Doc: jg_init: typedef struct jg_rect { dom_node_id node; int32_t     x, y, w, h;       /* document...
- Layer: utility
- Language: h
- Symbols:
  - `jg_rect` (struct, line 30)
  - `jg_table` (struct, line 35)
  - `node` (type_alias, line 29) `typedef struct jg_rect { dom_node_id node;`
  - `jg_init` (function, line 44) `void jg_init(jg_table *t);`
  - `jg_free` (function, line 47) `void jg_free(jg_table *t);`
  - `jg_add` (function, line 52) `int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h);`
  - `jg_finish` (function, line 56) `int jg_finish(jg_table *t);`
  - `jg_find` (function, line 59) `const jg_rect *jg_find(const jg_table *t, dom_node_id node);`
  - `jg_aggregate` (function, line 65) `int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx);`
  - `jg_wire_len` (function, line 68) `size_t jg_wire_len(const jg_table *t);`
  - `jg_encode` (function, line 71) `int jg_encode(const jg_table *t, int32_t *out, size_t cap);`
  - `jg_decode` (function, line 77) `int jg_decode(const int32_t *in, size_t n, jg_table *out);`
  - `jg_hash` (function, line 80) `uint64_t jg_hash(const jg_table *t);`
  - `FREEDOM_JS_GEOM_H` (macro, line 2) `#define FREEDOM_JS_GEOM_H`
  - `JG_MAX_RECTS` (macro, line 24) `#define JG_MAX_RECTS`
  - `JG_MAX_DEPTH` (macro, line 25) `#define JG_MAX_DEPTH`
  - `JG_COORD_MAX` (macro, line 26) `#define JG_COORD_MAX`
  - `JG_HEADER_N` (macro, line 27) `#define JG_HEADER_N`
  - `JG_RECT_N` (macro, line 28) `#define JG_RECT_N`
- Depends on: `include/dom.h`
- Imported by: `include/js_dom.h`, `include/tab.h`, `src/js_geom.c`, `tests/test_js_dom.c`, `tests/test_js_geom.c`, `tests/test_tab.c`

## include/js_location.h
- Doc: jd_take_history: Drains the history operations page JS performed since the last call: an owned...
- Layer: utility
- Language: h
- Symbols:
  - `reads` (function, line 25) `* reads (NULL => only href is known, the rest fall back to stub defaults). Call after * jd_install, on the page's...`
  - `jd_take_history` (function, line 38) `char *jd_take_history(js_context *ctx, int *go);`
  - `jd_pop_state` (function, line 44) `int jd_pop_state(js_context *ctx, int index);`
  - `acting` (function, line 49) `* The caller MUST gate the raw target with ln_resolve before acting (Zero Trust). */ int...`
  - `FREEDOM_JS_LOCATION_H` (macro, line 2) `#define FREEDOM_JS_LOCATION_H`
  - `JD_HIST_MAX` (macro, line 31) `#define JD_HIST_MAX`
- Depends on: `include/js_dom.h`, `include/js_sandbox.h`, `include/url.h`
- Imported by: `include/js_dom.h`

## include/js_policy.h
- Doc: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its...
- Layer: business_logic
- Language: h
- Symbols:
  - `jsp_mode` (enum, line 27)
  - `membership` (function, line 16) `* membership (the allowlist itself is matched by the hostblock module, which * already covers subdomains). No I/O...`
  - `allowlist` (function, line 34) `* allowlist (e.g. hb_is_allowlisted over js.conf). Fails closed: an unknown mode * yields false. */ bool...`
  - `jsp_trusted` (function, line 45) `bool jsp_trusted(bool js_enabled, int host_allowlisted);`
  - `jsp_present_trusted` (function, line 54) `bool jsp_present_trusted(int host_allowlisted);`
  - `jsp_mode_str` (function, line 64) `const char *jsp_mode_str(jsp_mode mode);`
  - `FREEDOM_JS_POLICY_H` (macro, line 2) `#define FREEDOM_JS_POLICY_H`
- Imported by: `gui/browser_ui.c`, `include/webcaps.h`, `src/freedom.c`, `src/js_policy.c`, `tests/test_js_policy.c`

## include/js_sandbox.h
- Doc: js_limits: Per-evaluation resource limits.
- Layer: utility
- Language: h
- Symbols:
  - `js_limits` (struct, line 39)
  - `js_result` (struct, line 49)
  - `js_status` (enum, line 24)
  - `max_source_bytes` (type_alias, line 39) `typedef struct js_limits { size_t max_source_bytes;`
  - `js_context` (type_alias, line 47) `typedef struct js_context js_context;`
  - `status` (type_alias, line 48) `typedef struct js_result { js_status status;`
  - `js_stack_limit_for` (function, line 75) `size_t js_stack_limit_for(size_t soft_stack);`
  - `js_prime_stack_limit` (function, line 79) `void js_prime_stack_limit(void);`
  - `js_context_free` (function, line 96) `void js_context_free(js_context *ctx);`
  - `loaded` (function, line 124) `* NULL when it cannot be loaded (policy refusal, network error, not JavaScript). */ typedef char...`
  - `js_set_module_host` (function, line 129) `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve, js_module_fetch_fn fetch, void *host);`
  - `js_loc_from_stack` (function, line 150) `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap, int *line, int *col);`
  - `js_set_time_budget` (function, line 158) `void js_set_time_budget(js_context *ctx, uint64_t budget_ms);`
  - `out` (function, line 163) `* into out (NUL-terminated, truncated at cap);`
  - `js_profile_enable` (function, line 166) `void js_profile_enable(js_context *ctx);`
  - `js_profile_report` (function, line 167) `size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n);`
  - `js_result_free` (function, line 170) `void js_result_free(js_result *res);`
  - `js_pump_jobs` (function, line 178) `int js_pump_jobs(js_context *ctx, int max_jobs);`
  - `handle` (function, line 181) `* as an opaque handle (so this header stays free of backend types), or NULL. * Valid only while ctx is alive....`
  - `js_set_current_script` (function, line 190) `void js_set_current_script(js_context *ctx, const char *src, const char *type);`
  - `FREEDOM_JS_SANDBOX_H` (macro, line 2) `#define FREEDOM_JS_SANDBOX_H`
  - `JS_LOC_FILE_MAX` (macro, line 64) `#define JS_LOC_FILE_MAX`
  - `JS_DEFAULT_MAX_SOURCE` (macro, line 66) `#define JS_DEFAULT_MAX_SOURCE`
  - `JS_DEFAULT_MEM_LIMIT` (macro, line 67) `#define JS_DEFAULT_MEM_LIMIT`
  - `JS_MIN_STACK_LIMIT` (macro, line 68) `#define JS_MIN_STACK_LIMIT`
  - `JS_MAX_STACK_LIMIT` (macro, line 69) `#define JS_MAX_STACK_LIMIT`
  - `JS_DEFAULT_STACK_LIMIT` (macro, line 70) `#define JS_DEFAULT_STACK_LIMIT`
  - `JS_DEFAULT_TIME_BUDGET` (macro, line 71) `#define JS_DEFAULT_TIME_BUDGET`
  - `JS_MODULE_MAX` (macro, line 115) `#define JS_MODULE_MAX`
  - `JS_MODULE_BYTES_MAX` (macro, line 116) `#define JS_MODULE_BYTES_MAX`
  - `JS_PROFILE_PERIOD_MS` (macro, line 165) `#define JS_PROFILE_PERIOD_MS`
  - `JS_REALM_MAX` (macro, line 198) `#define JS_REALM_MAX`
  - `JS_REJECT_MAX` (macro, line 201) `#define JS_REJECT_MAX`
- Imported by: `include/js_dom.h`, `include/js_env.h`, `include/js_location.h`, `include/js_trusted.h`, `src/js_dom.c`, `src/js_dom_ext.c`, `src/js_embed.c`, `src/js_env.c`, `src/js_events.c`, `src/js_fetch.c`, `src/js_sandbox.c`, `src/tab.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_js_sandbox.c`

## include/js_trusted.h
- Doc: jt_take_opens: The parent installed a new geometry table (layout or scroll changed)...
- Layer: utility
- Language: h
- Symbols:
  - `jt_ws_op` (struct, line 57)
  - `jt_ws_kind` (enum, line 50)
  - `jt_ws_event_kind` (enum, line 64)
  - `kind` (type_alias, line 56) `typedef struct jt_ws_op { int kind;`
  - `null` (function, line 24) `* noopener semantics: it returns null (no cross-window reference, so no same-origin * channel) and only records up...`
  - `jt_take_opens` (function, line 42) `char *jt_take_opens(js_context *ctx);`
  - `parent` (function, line 69) `* socket: the object records operations for the parent (jt_take_ws). */ jd_status jt_enable_ws(js_context *ctx);`
  - `jt_take_ws` (function, line 75) `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap);`
  - `jt_ws_ops_free` (function, line 76) `void jt_ws_ops_free(jt_ws_op *ops, size_t n);`
  - `jt_ws_event` (function, line 81) `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len);`
  - `jt_take_storage` (function, line 93) `int jt_take_storage(js_context *ctx, char **out, size_t *len);`
  - `realm` (function, line 96) `* runs in its own realm (js_install_realms) of this context's runtime, inside the * same confined process and...`
  - `FREEDOM_JS_TRUSTED_H` (macro, line 2) `#define FREEDOM_JS_TRUSTED_H`
  - `JT_WS_MAX` (macro, line 46) `#define JT_WS_MAX`
  - `JT_WS_MAX_OPS` (macro, line 47) `#define JT_WS_MAX_OPS`
  - `JT_WS_MAX_BYTES` (macro, line 48) `#define JT_WS_MAX_BYTES`
- Depends on: `include/js_dom.h`, `include/js_sandbox.h`
- Imported by: `src/js_trusted.c`, `src/tab.c`, `tests/test_js_dom.c`

## include/link_nav.h
- Doc: ln_block_reason: Why a reference was blocked, for a precise user-facing notice and for *...
- Layer: utility
- Language: h
- Symbols:
  - `ln_result` (struct, line 62)
  - `ln_action` (enum, line 40)
  - `ln_target_kind` (enum, line 46)
  - `ln_block_reason` (enum, line 54)
  - `ln_status` (enum, line 70)
  - `action` (type_alias, line 61) `typedef struct ln_result { ln_action action;`
  - `dropped` (function, line 36) `* A longer fragment is dropped (stored as "");`
  - `ln_block_reason_text` (function, line 85) `const char *ln_block_reason_text(ln_block_reason reason);`
  - `FREEDOM_LINK_NAV_H` (macro, line 2) `#define FREEDOM_LINK_NAV_H`
  - `LN_MAX_TARGET` (macro, line 33) `#define LN_MAX_TARGET`
  - `LN_MAX_FRAGMENT` (macro, line 38) `#define LN_MAX_FRAGMENT`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/link_nav.c`, `src/tab.c`, `tests/test_link_nav.c`

## include/local_store.h
- Doc: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and...
- Layer: data_access
- Language: h
- Symbols:
  - `ls_aead` (enum, line 34)
  - `ls_status` (enum, line 39)
  - `ls_free` (function, line 80) `void ls_free(uint8_t *buf, size_t len);`
  - `FREEDOM_LOCAL_STORE_H` (macro, line 2) `#define FREEDOM_LOCAL_STORE_H`
  - `LS_KEY_LEN` (macro, line 26) `#define LS_KEY_LEN`
  - `LS_SALT_LEN` (macro, line 27) `#define LS_SALT_LEN`
  - `LS_NONCE_LEN` (macro, line 28) `#define LS_NONCE_LEN`
  - `LS_TAG_LEN` (macro, line 29) `#define LS_TAG_LEN`
  - `LS_HEADER_LEN` (macro, line 30) `#define LS_HEADER_LEN`
  - `LS_OVERHEAD` (macro, line 31) `#define LS_OVERHEAD`
  - `LS_MAX_PLAINTEXT` (macro, line 32) `#define LS_MAX_PLAINTEXT`
- Imported by: `include/disk_store.h`, `include/http_cache.h`, `include/pq_seal.h`, `include/profile.h`, `src/disk_store.c`, `src/local_store.c`, `tests/test_disk_store.c`, `tests/test_local_store.c`

## include/media_decoder.h
- Doc: md_cmd: Communicates with the parent over two pipes: out_fd: decoder → parent (frames, stream...
- Layer: utility
- Language: h
- Symbols:
  - `md_pacer` (struct, line 67)
  - `md_cmd` (enum, line 29)
  - `md_resp` (enum, line 38)
  - `epoch_ms` (type_alias, line 66) `typedef struct md_pacer { uint64_t epoch_ms;`
  - `md_pace_due_ms` (function, line 79) `static inline uint64_t md_pace_due_ms(md_pacer *p, uint64_t now_ms,
                             ...`
  - `media_decoder_run` (function, line 99) `void media_decoder_run(int out_fd, int cmd_fd);`
  - `media_decoder_spawn` (function, line 104) `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd);`
  - `FREEDOM_MEDIA_DECODER_H` (macro, line 2) `#define FREEDOM_MEDIA_DECODER_H`
  - `MD_MAX_SEGMENT_BYTES` (macro, line 46) `#define MD_MAX_SEGMENT_BYTES`
  - `MD_PACE_MAX_LAG_MS` (macro, line 58) `#define MD_PACE_MAX_LAG_MS`
  - `MD_PACE_MAX_STEP_MS` (macro, line 62) `#define MD_PACE_MAX_STEP_MS`
  - `MD_MAX_CATCHUP_READS` (macro, line 65) `#define MD_MAX_CATCHUP_READS`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/media_decoder.c`, `tests/test_media_decoder.c`

## include/net_realm.h
- Doc: nr_realm_allows_http: 1 iff plain http:// is acceptable for this realm.
- Layer: utility
- Language: h
- Symbols:
  - `nr_config` (struct, line 42)
  - `nr_realm` (enum, line 29)
  - `nr_route` (enum, line 35)
  - `tor_enabled` (type_alias, line 41) `typedef struct nr_config { int tor_enabled;`
  - `NR_ROUTE_BLOCKED` (function, line 57) `* NR_ROUTE_BLOCKED (fail closed: never route what cannot be classified). A realm * whose proxy is not enabled =>...`
  - `address` (function, line 62) `* and encrypts by its address (the I2P destination / onion key), so http over it is * not a downgrade. Currently...`
  - `nr_realm_allows_http` (function, line 66) `int nr_realm_allows_http(nr_realm r);`
  - `nr_realm_name` (function, line 69) `const char *nr_realm_name(nr_realm r);`
  - `nr_route_name` (function, line 70) `const char *nr_route_name(nr_route r);`
  - `FREEDOM_NET_REALM_H` (macro, line 2) `#define FREEDOM_NET_REALM_H`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/net_realm.c`, `tests/test_net_realm.c`

## include/os_sandbox.h
- Doc: os_violation: function (os_policy_allows) that mirrors the installed BPF program.
- Layer: utility
- Language: h
- Symbols:
  - `os_fs_rule` (struct, line 108)
  - `os_status` (enum, line 21)
  - `os_violation` (enum, line 30)
  - `os_fs_access` (enum, line 102)
  - `flags` (function, line 39) `* permission also depends on the protection flags (see os_prot_allowed / W^X). */ int os_policy_allows(long syscall_nr);`
  - `os_policy_size` (function, line 43) `size_t os_policy_size(void);`
  - `os_prot_allowed` (function, line 52) `int os_prot_allowed(long syscall_nr, unsigned long prot);`
  - `denied` (function, line 59) `* request PROT_EXEC are denied (see os_prot_allowed). * Returns OS_ERR_UNSUPPORTED on platforms without seccomp-bpf...`
  - `namespace` (function, line 75) `* namespace (the unprivileged enabler), network (the worker never needs the * network -- the parent fetches and...`
  - `os_namespace_flags` (function, line 81) `int os_namespace_flags(void);`
  - `os_landlock_abi` (function, line 114) `int os_landlock_abi(void);`
  - `FREEDOM_OS_SANDBOX_H` (macro, line 2) `#define FREEDOM_OS_SANDBOX_H`
- Imported by: `src/os_sandbox.c`, `src/renderer.c`, `src/tab.c`, `tests/test_os_sandbox.c`


Next: [KB_include_p4.md](KB_include_p4.md)
