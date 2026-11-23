# API (page 5 of 14)
Previous: [API_p4.md](API_p4.md)

## include/hostblock.h
Imported by: `gui/browser_ui.c`, `include/host_conf.h`, `src/freedom.c`, `src/hostblock.c`, `tests/test_hostblock.c`
- `hb_new` (function) `include/hostblock.h:49` `hb_set *hb_new(void);` -- } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on...
- `hb_free` (function) `include/hostblock.h:52` `void hb_free(hb_set *s);` -- HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) }...
- `walked` (function) `include/hostblock.h:65` `* walked (the host, then without its first label, ...): any suffix on the allowlist * => HB_ALLOW (allow wins...`
- `hb_is_allowlisted` (function) `include/hostblock.h:75` `int hb_is_allowlisted(const hb_set *s, const char *host);` -- 1 iff a domain suffix of host is explicitly on the allowlist (covers subdomains), else 0.
- `hb_count` (function) `include/hostblock.h:85` `size_t hb_count(const hb_set *s, hb_list list);` -- Number of unique domains on the given list (for tests/diagnostics).

## include/hostedit.h
Imported by: `fuzz/fuzz_identity.c`, `gui/browser_ui.c`, `src/hostedit.c`, `tests/test_hostedit.c`
- `he_text_has_host` (function) `include/hostedit.h:46` `int he_text_has_host(const char *text, const char *host);` -- Returns 1 if text (the body of a hosts-format file) already lists host as a domain token on a non-comment line...
- `he_suggest` (function) `include/hostedit.h:55` `int he_suggest(const char *text, const char *query, char results[][HE_MAX_HOST + 1], int max);` -- Omnibar autocomplete: treats allow.conf (a hosts-format text) as a favorites list.
- `he_cdn_kind` (function) `include/hostedit.h:62` `he_cdn_kind_t he_cdn_kind(const char *url);`

## include/html_parse.h
Imported by: `fuzz/fuzz_anchor.c`, `fuzz/fuzz_dom.c`, `fuzz/fuzz_dom_debug.c`, `fuzz/fuzz_html_parse.c`, `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_page_view.c`, `gui/freedom_view.c`, `include/dom.h`, `include/page_view.h`, `src/dom.c`, `src/freedom.c`, `src/html_parse.c`, `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/page_view.c`, `src/renderer.c`, `src/tab.c`, `tests/test_anchor.c`, `tests/test_dom.c`, `tests/test_html_parse.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_js_native.c`, `tests/test_page_view.c`
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

## include/http_cache.h
Depends on: `include/local_store.h`
Imported by: `include/cached_fetch.h`, `src/http_cache.c`, `tests/test_http_cache.c`
- `hc_parse_http_date` (function) `include/http_cache.h:56` `time_t hc_parse_http_date(const char *s);` -- } hc_class; typedef struct hc_meta { char   final_url[HC_URL_MAX]; char   content_type[HC_TYPE_MAX]; char...
- `by` (function) `include/http_cache.h:59` `* something to reuse it by (validator, max-age or Expires). */ int hc_storable(long http_code, const hc_meta *m...`
- `hc_lifetime` (function) `include/http_cache.h:63` `long hc_lifetime(const hc_meta *m);` -- True when a response may be stored: 200, no `no-store`, body within HC_MAX_ENTRY, and * something to reuse it by...
- `hc_close` (function) `include/http_cache.h:72` `void hc_close(hc_store *s);`
- `hc_body_free` (function) `include/http_cache.h:78` `void hc_body_free(uint8_t *body, size_t len);`
- `hc_clear` (function) `include/http_cache.h:84` `void hc_clear(hc_store *s);` -- ML-KEM keys and empties the directory when the sealed key cannot be opened. hc_status hc_open(hc_store **out, const...

## include/identity.h
Imported by: `fuzz/fuzz_identity.c`, `gui/browser_ui.c`, `src/freedom.c`, `src/identity.c`, `src/tab.c`, `tests/test_identity.c`
- `idn_defaults` (function) `include/identity.h:50` `void idn_defaults(idn_config *c);` -- typedef struct idn_config { char   user_agent[IDN_UA_MAX];  /* "" = FP_USER_AGENT char   languages[IDN_LANG_MAX]; /*...
- `idn_is_default` (function) `include/identity.h:53` `int idn_is_default(const idn_config *c);` -- char   languages[IDN_LANG_MAX]; /* "" = the anti_fp default; comma-separated tags int    geo_mode;                /*...
- `idn_set_user_agent` (function) `include/identity.h:56` `int idn_set_user_agent(idn_config *c, const char *ua);` -- unsigned auto_allow;            /* IDN_AA_* switches: hosts a page on allow.conf pulls CSS/JS/ resources from are...
- `idn_set_languages` (function) `include/identity.h:57` `int idn_set_languages(idn_config *c, const char *list);`
- `idn_set_geo` (function) `include/identity.h:58` `int idn_set_geo(idn_config *c, double lat, double lon, double accuracy_m);`
- `idn_clear_geo` (function) `include/identity.h:59` `void idn_clear_geo(idn_config *c);`
- `idn_user_agent` (function) `include/identity.h:62` `const char *idn_user_agent(const idn_config *c);` -- /* The anti_fp identity, geolocation off.
- `idn_accept_language` (function) `include/identity.h:63` `size_t idn_accept_language(const idn_config *c, char *out, size_t cap);`
- `idn_primary_language` (function) `include/identity.h:64` `size_t idn_primary_language(const idn_config *c, char *out, size_t cap);`
- `idn_serialize` (function) `include/identity.h:68` `size_t idn_serialize(const idn_config *c, char *out, size_t cap);` -- One-line text form for prefs and the worker IPC.
- `idn_parse` (function) `include/identity.h:72` `void idn_parse(idn_config *c, const char *text);` -- Parses idn_serialize output field by field; an invalid field keeps its default.
- `idn_apply_query` (function) `include/identity.h:75` `unsigned idn_apply_query(idn_config *c, const char *query);` -- Parses idn_serialize output field by field; an invalid field keeps its default.
- `idn_render_page` (function) `include/identity.h:78` `size_t idn_render_page(const idn_config *c, char *out, size_t cap);` -- Parses idn_serialize output field by field; an invalid field keeps its default.

## include/image_decode.h
Imported by: `fuzz/fuzz_image_decode.c`, `gui/browser_ui.c`, `include/svg_raster.h`, `src/image_decode.c`, `src/tab.c`, `tests/test_freedom.c`, `tests/test_image_decode.c`
- `guards` (function) `include/image_decode.h:25` `* guards (in-memory source only, longjmp error manager so a bad stream never * calls exit(), dimension caps before...`
- `img_dimensions_ok` (function) `include/image_decode.h:84` `int img_dimensions_ok(uint32_t w, uint32_t h);` -- 1 iff (w,h) is non-zero and fits the anti-DoS caps (per-side and area, no * overflow of width*height*4); 0 otherwise.
- `inputs` (function) `include/image_decode.h:87` `* Degenerate inputs (<= 0) yield (0,0). Pure. */ void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h...`
- `decode` (function) `include/image_decode.h:98` `* the declared dimensions BEFORE the full decode (anti-bomb), decodes to RGB and * expands to BGRA. Rejects non-JPEG...`
- `img_pixels_free` (function) `include/image_decode.h:127` `void img_pixels_free(img_pixels *p);` -- Releases data and zeroes the struct.
- `img_format_name` (function) `include/image_decode.h:130` `const char *img_format_name(img_format f);` -- Releases data and zeroes the struct.

## include/import_map.h
Imported by: `fuzz/fuzz_import_map.c`, `src/import_map.c`, `src/prefetch.c`, `src/tab.c`, `tests/test_import_map.c`
- `algorithm` (function) `include/import_map.h:13` `* resolution algorithm (scopes, exact and prefix matches). URL resolution is the * caller's (the same resolver the...`
- `map` (function) `include/import_map.h:28` `* map (fail closed = no mapping). NULL only on OOM. */ im_map *im_parse(const char *json, size_t len, const char...`
- `im_resolve` (function) `include/import_map.h:33` `int im_resolve(const im_map *m, const char *base, const char *specifier, im_url_fn resolve, void *ctx, char *out...` -- Resolves specifier as imported from base (the importing module's URL).
- `im_count` (function) `include/import_map.h:37` `size_t im_count(const im_map *m);` -- Resolves specifier as imported from base (the importing module's URL).
- `im_free` (function) `include/import_map.h:40` `void im_free(im_map *m);` -- Resolves specifier as imported from base (the importing module's URL).

## include/interp.h
Imported by: `gui/browser_ui.c`, `src/css.c`, `src/interp.c`, `tests/test_interp.c`
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
Imported by: `fuzz/fuzz_js_dom.c`, `include/js_location.h`, `include/js_trusted.h`, `src/js_dom.c`, `src/js_dom_ext.c`, `src/js_dom_internal.h`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/js_location.c`, `src/tab.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_js_native.c`
- `opaque` (function) `include/js_dom.h:73` `* the engine runtime opaque (unreachable from script);`
- `global` (function) `include/js_dom.h:80` `* globals: page scripts never see them and an existing page global (jQuery's `$`) is * never replaced. Read-only...`
- `jd_install_repl_api` (function) `include/js_dom.h:89` `* jd_install_repl_api (the shim reads and deletes the carrier global, so a page script never * sees it). css == NULL...`
- `place` (function) `include/js_dom.h:94` `* configured place (spec/identity.md), no sensor, no network. Call it ONLY for a trusted host * with geolocation set...`
- `getComputedStyle` (function) `include/js_dom.h:115` `* getComputedStyle (spec/js_computed_style.md). fn writes the computed value of the * kebab-case `prop` of element h...`
- `jd_click_state_free` (function) `include/js_dom.h:125` `* jd_click_state_free(). Bound to one context via jd_install_events(). */ jd_click_state *jd_click_state_new(void);`
- `run` (function) `include/js_dom.h:134` `* run (no handler registered, or handlers ran without calling preventDefault()), * and 0 if a handler called...`
- `preventDefault` (function) `include/js_dom.h:141` `* preventDefault() was called, 1 if the default (form submission) should proceed. * ctx == NULL or no form found =>...`
- `host` (function) `include/js_dom.h:170` `* for a trusted host (allow.conf AND js.conf);`
- `jd_get_cookies` (function) `include/js_dom.h:181` `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz);` -- Serialises the page's current cookie jar ("name=value; ...") into buf (bounded, NUL-terminated) and returns its...
- `out_status` (function) `include/js_dom.h:189` `* On success returns 0 and sets *out_status (HTTP status, 0 if unknown), *out_body / * *out_body_len (response...`
- `jd_process_iframes` (function) `include/js_dom.h:231` `* BEFORE jd_process_iframes() (so iframes are in the DOM for it to process). * ctx == NULL => JD_ERR_NULL_ARG. */...`
- `URLs` (function) `include/js_dom.h:238` `* video URLs (.m3u8 then .mp4 patterns), and creates <video> elements in the document for * any found. Does NOT...`
- `jd_video_from_scripts` (function) `include/js_dom.h:252` `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts, const size_t *script_lens, size_t...` -- Creates <iframe> elements in the DOM from video data (`video[N]` / `video_data`) found in inline script text...
- `jd_flush_custom_elements` (function) `include/js_dom.h:263` `void jd_flush_custom_elements(js_context *ctx);` -- Reconciles Custom Elements (spec/js_custom_elements.md): upgrades the elements whose tag was just defined and fires...

## include/js_env.h
Depends on: `include/js_sandbox.h`
Imported by: `src/js_env.c`, `src/tab.c`, `tests/test_js_env.c`, `tests/test_js_native.c`
- `poisoned` (function) `include/js_env.h:49` `* readback is poisoned (deterministic within an origin, unlinkable across * sessions and across origins) to defeat...`

## include/js_geom.h
Depends on: `include/dom.h`
Imported by: `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_js_geom.c`, `include/anchor.h`, `include/js_dom.h`, `include/tab.h`, `src/js_geom.c`, `tests/test_anchor.c`, `tests/test_js_dom.c`, `tests/test_js_geom.c`, `tests/test_tab.c`
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

## include/js_intl.h
Depends on: `include/js_sandbox.h`
Imported by: `src/js_dom.c`, `src/js_intl.c`, `tests/test_js_intl.c`
- `ji_install` (function) `include/js_intl.h:16` `int ji_install(js_context *ctx);` -- Installs `Intl` and the Number/BigInt/Date toLocale* methods that delegate to it. * Returns 0, or -1 on a NULL...

## include/js_location.h
Depends on: `include/js_dom.h`, `include/js_sandbox.h`, `include/url.h`
Imported by: `include/js_dom.h`
- `reads` (function) `include/js_location.h:25` `* reads (NULL => only href is known, the rest fall back to stub defaults). Call after * jd_install, on the page's...`
- `jd_take_history` (function) `include/js_location.h:38` `char *jd_take_history(js_context *ctx, int *go);` -- Drains the history operations page JS performed since the last call: an owned string of lines "P <url>\n"...
- `jd_pop_state` (function) `include/js_location.h:44` `int jd_pop_state(js_context *ctx, int index);` -- Moves the page's history to entry index (the parent went Back/Forward within the same document): updates location...
- `kind` (function) `include/js_location.h:48` `* kind (srq_kind), y, behavior (srq_behavior), block (srq_block), element handle. Returns * 1 when one was pending...`
- `url` (function) `include/js_location.h:55` `* pushes url (resolved by the page's own same-origin check, dom.histTarget) as a new * entry of the page's history...`
- `acting` (function) `include/js_location.h:66` `* The caller MUST gate the raw target with ln_resolve before acting (Zero Trust). */ int...`

## include/js_native.h
Depends on: `include/js_sandbox.h`
Imported by: `fuzz/fuzz_js_dom.c`, `src/js_native.c`, `src/tab.c`, `tests/test_js_dom.c`, `tests/test_js_native.c`
- `failure` (function) `include/js_native.h:22` `* engine failure (the page then simply runs with the unsealed surface). */ int jn_seal(js_context *ctx);`

## include/js_policy.h
Imported by: `gui/browser_ui.c`, `include/webcaps.h`, `src/freedom.c`, `src/js_policy.c`, `tests/test_js_policy.c`
- `membership` (function) `include/js_policy.h:16` `* membership (the allowlist itself is matched by the hostblock module, which * already covers subdomains). No I/O...`
- `allowlist` (function) `include/js_policy.h:34` `* allowlist (e.g. hb_is_allowlisted over js.conf). Fails closed: an unknown mode * yields false. */ bool...`
- `jsp_trusted` (function) `include/js_policy.h:45` `bool jsp_trusted(bool js_enabled, int host_allowlisted);` -- Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g....
- `jsp_present_trusted` (function) `include/js_policy.h:54` `bool jsp_present_trusted(int host_allowlisted);` -- Presentation-trust (2026-07-11): a host EXPLICITLY on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- `jsp_mode_str` (function) `include/js_policy.h:64` `const char *jsp_mode_str(jsp_mode mode);` -- Stable lowercase name of a mode ("off"/"allowlist"/"on"); an unknown value * yields "off" (fail closed).

## include/js_sandbox.h
Imported by: `fuzz/fuzz_js_dom.c`, `fuzz/fuzz_js_sandbox.c`, `include/js_dom.h`, `include/js_env.h`, `include/js_intl.h`, `include/js_location.h`, `include/js_native.h`, `include/js_trusted.h`, `src/js_dom.c`, `src/js_dom_ext.c`, `src/js_embed.c`, `src/js_env.c`, `src/js_events.c`, `src/js_fetch.c`, `src/js_sandbox.c`, `src/tab.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_js_intl.c`, `tests/test_js_native.c`, `tests/test_js_sandbox.c`
- `js_stack_limit_for` (function) `include/js_sandbox.h:75` `size_t js_stack_limit_for(size_t soft_stack);` -- Engine stack cap for a process whose soft stack limit is `soft_stack` bytes (0 = unknown): * 75 % of it (the rest is...
- `js_prime_stack_limit` (function) `include/js_sandbox.h:79` `void js_prime_stack_limit(void);` -- Reads the process stack limit now.
- `js_context_free` (function) `include/js_sandbox.h:96` `void js_context_free(js_context *ctx);` -- Creates an isolated, hardened sandbox (memory/stack/time limits armed; no I/O modules). lim == NULL =>...
- `loaded` (function) `include/js_sandbox.h:124` `* NULL when it cannot be loaded (policy refusal, network error, not JavaScript). */ typedef char...`
- `js_set_module_host` (function) `include/js_sandbox.h:129` `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve, js_module_fetch_fn fetch, void *host);` -- Installs the host every static import and dynamic import() goes through. host must * outlive ctx.
- `js_loc_from_stack` (function) `include/js_sandbox.h:150` `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap, int *line, int *col);` -- Pure parser: extracts the throw site (file, line, column) from the FIRST frame of a QuickJS .stack string.
- `js_set_time_budget` (function) `include/js_sandbox.h:158` `void js_set_time_budget(js_context *ctx, uint64_t budget_ms);` -- Adjusts the wall-clock budget armed on each subsequent js_eval.
- `out` (function) `include/js_sandbox.h:163` `* into out (NUL-terminated, truncated at cap);`
- `js_profile_enable` (function) `include/js_sandbox.h:166` `void js_profile_enable(js_context *ctx);` -- Sampling profiler (FREEDOM_JS_PROFILE=2).
- `js_profile_report` (function) `include/js_sandbox.h:167` `size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n);`
- `silently` (function) `include/js_sandbox.h:171` `* fails silently (an exception swallowed by a try/catch, a rejected promise nobody awaits) shows * its real first...`
- `js_throws_report` (function) `include/js_sandbox.h:176` `size_t js_throws_report(js_context *ctx, char *out, size_t cap, size_t top_n);`
- `global` (function) `include/js_sandbox.h:181` `* Freebug REPL installs: its shim takes them once and deletes them from the global (like * __netLog), because the...`
- `js_result_free` (function) `include/js_sandbox.h:187` `void js_result_free(js_result *res);` -- Devtools for a TRUSTED page. js_devtools_enable turns the profiler and the throw tracer on when the page loads...
- `js_pump_jobs` (function) `include/js_sandbox.h:195` `int js_pump_jobs(js_context *ctx, int max_jobs);` -- Runs up to max_jobs pending microtasks/jobs (promise reactions queued by the last eval), under the context's current...
- `handle` (function) `include/js_sandbox.h:198` `* as an opaque handle (so this header stays free of backend types), or NULL. * Valid only while ctx is alive....`
- `js_set_current_script` (function) `include/js_sandbox.h:207` `void js_set_current_script(js_context *ctx, const char *src, const char *type);` -- Sets document.currentScript on the global object so external scripts can read their own src / type / data-*...

## include/js_trusted.h
Depends on: `include/js_dom.h`, `include/js_sandbox.h`
Imported by: `fuzz/fuzz_js_dom.c`, `src/js_trusted.c`, `src/tab.c`, `tests/test_js_dom.c`
- `null` (function) `include/js_trusted.h:24` `* noopener semantics: it returns null (no cross-window reference, so no same-origin * channel) and only records up...`
- `jt_take_opens` (function) `include/js_trusted.h:42` `char *jt_take_opens(js_context *ctx);` -- The parent installed a new geometry table (layout or scroll changed): re-evaluates every observed target and fires a...
- `parent` (function) `include/js_trusted.h:80` `* socket: the object records operations for the parent (jt_take_ws). */ jd_status jt_enable_ws(js_context *ctx);`
- `jt_take_ws` (function) `include/js_trusted.h:86` `size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap);` -- Drains up to cap recorded operations into ops (each data owned; release with jt_ws_ops_free).
- `jt_ws_ops_free` (function) `include/js_trusted.h:87` `void jt_ws_ops_free(jt_ws_op *ops, size_t n);`
- `jt_ws_event` (function) `include/js_trusted.h:92` `int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len);` -- Delivers a socket event from the parent: data enters JS as a VALUE (a string for text, an ArrayBuffer for binary...
- `jt_take_storage` (function) `include/js_trusted.h:104` `int jt_take_storage(js_context *ctx, char **out, size_t *len);` -- When the store changed since the last call, returns 1 with an owned snapshot of * the whole store in *out (length...
- `realm` (function) `include/js_trusted.h:107` `* runs in its own realm (js_install_realms) of this context's runtime, inside the * same confined process and...`

## include/link_nav.h
Imported by: `fuzz/fuzz_link_preview.c`, `fuzz/fuzz_url.c`, `gui/browser_ui.c`, `src/freedom.c`, `src/link_nav.c`, `src/link_preview.c`, `src/tab.c`, `tests/test_link_nav.c`
- `dropped` (function) `include/link_nav.h:36` `* A longer fragment is dropped (stored as "");`
- `ln_block_reason_text` (function) `include/link_nav.h:85` `const char *ln_block_reason_text(ln_block_reason reason);` -- Stable, short English notice for a block reason (e.g. for a UI toast or agent * output).

## include/local_store.h
Imported by: `include/disk_store.h`, `include/http_cache.h`, `include/pq_seal.h`, `include/profile.h`, `src/disk_store.c`, `src/local_store.c`, `tests/test_disk_store.c`, `tests/test_local_store.c`
- `ls_free` (function) `include/local_store.h:80` `void ls_free(uint8_t *buf, size_t len);` -- Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container...

## include/mask_cache.h
Imported by: `fuzz/fuzz_mask_cache.c`, `gui/browser_ui.c`, `src/mask_cache.c`, `tests/test_mask_cache.c`
- `mkc_new` (function) `include/mask_cache.h:29` `mkc_cache *mkc_new(size_t byte_budget, size_t max_entries);` -- A cache holding at most byte_budget bytes of mask buffers in at most max_entries masks. * NULL when either bound is...
- `mkc_free` (function) `include/mask_cache.h:32` `void mkc_free(mkc_cache *c);` -- A cache holding at most byte_budget bytes of mask buffers in at most max_entries masks. * NULL when either bound is...
- `mkc_clear` (function) `include/mask_cache.h:35` `void mkc_clear(mkc_cache *c);` -- A cache holding at most byte_budget bytes of mask buffers in at most max_entries masks. * NULL when either bound is...
- `mkc_get` (function) `include/mask_cache.h:39` `const unsigned char *mkc_get(mkc_cache *c, const mkc_key *k, int *stride);` -- The buffer retained for k (stride bytes per row) and makes it the most recent, or NULL. * Valid until the next...
- `mkc_put` (function) `include/mask_cache.h:45` `unsigned char *mkc_put(mkc_cache *c, const mkc_key *k, int stride);` -- Reserves a zeroed buffer of stride * k->h bytes owned by the cache for k (replacing any entry for k), evicting...
- `mkc_bytes` (function) `include/mask_cache.h:48` `size_t mkc_bytes(const mkc_cache *c);` -- Reserves a zeroed buffer of stride * k->h bytes owned by the cache for k (replacing any entry for k), evicting...
- `mkc_count` (function) `include/mask_cache.h:49` `size_t mkc_count(const mkc_cache *c);`

## include/media_decoder.h
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/media_decoder.c`, `tests/test_media_decoder.c`
- `md_pace_due_ms` (function) `include/media_decoder.h:79` `static inline uint64_t md_pace_due_ms(md_pacer *p, uint64_t now_ms,
                             ...` -- Returns the wall-clock instant (ms) at which the frame carrying pts_us is due for display.
- `media_decoder_run` (function) `include/media_decoder.h:99` `void media_decoder_run(int out_fd, int cmd_fd);` -- Entry point for the decoder child process.
- `media_decoder_spawn` (function) `include/media_decoder.h:104` `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd);` -- Spawns a media decoder child via fork+exec.

## include/nav_token.h
Imported by: `fuzz/fuzz_nav_token.c`, `gui/browser_ui.c`, `src/nav_token.c`, `tests/test_nav_token.c`
- `nt_new` (function) `include/nav_token.h:20` `nt_token *nt_new(void);`
- `nt_ref` (function) `include/nav_token.h:21` `nt_token *nt_ref(nt_token *t);`
- `nt_unref` (function) `include/nav_token.h:22` `void nt_unref(nt_token **t);`
- `nt_cancel` (function) `include/nav_token.h:23` `void nt_cancel(nt_token *t);`
- `nt_cancelled` (function) `include/nav_token.h:24` `int nt_cancelled(const nt_token *t);`
- `nt_set_foreground` (function) `include/nav_token.h:25` `void nt_set_foreground(nt_token *t, int on);`
- `nt_foreground` (function) `include/nav_token.h:26` `int nt_foreground(const nt_token *t);`
- `nt_id` (function) `include/nav_token.h:27` `uint64_t nt_id(const nt_token *t);`

## include/net_guard.h
Imported by: `fuzz/fuzz_net_guard.c`, `src/net_guard.c`, `src/secure_fetch.c`, `tests/test_net_guard.c`
- `ng_addr_is_private` (function) `include/net_guard.h:38` `int ng_addr_is_private(int family, const unsigned char *addr, size_t len);` -- 1 when the address is not globally routable (loopback, RFC 1918, link-local, CGNAT, documentation, multicast...
- `ng_text_is_private` (function) `include/net_guard.h:42` `int ng_text_is_private(const char *ip_text);` -- As ng_addr_is_private over a textual IPv4/IPv6 address (optionally bracketed).
- `ng_host_is_ip` (function) `include/net_guard.h:46` `int ng_host_is_ip(const char *host);` -- 1 when host is an IPv4/IPv6 literal (optionally bracketed), 0 for a name or NULL.
- `ng_host_is_local` (function) `include/net_guard.h:50` `int ng_host_is_local(const char *host);` -- 1 when host names this machine or a private address without resolving anything: * "localhost", any "*.localhost", or...

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
Imported by: `fuzz/fuzz_box_tree.c`, `fuzz/fuzz_dom_debug.c`, `fuzz/fuzz_page_view.c`, `include/box_tree.h`, `include/frame_host.h`, `include/render_doc.h`, `include/tab.h`, `include/video_pick.h`, `src/dom_debug.c`, `src/freedom.c`, `src/page_view.c`, `src/tab.c`, `tests/test_box_tree.c`, `tests/test_dom_debug.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`
- `container` (function) `include/page_view.h:242` `* cont_id groups runs of one container (-1 = none);`
- `bx_display` (function) `include/page_view.h:243` `* bx_display (flex/grid);`
- `order` (function) `include/page_view.h:307` `* groups the runs of ONE floated element in document order (-1 = not in a float);`
- `itself` (function) `include/page_view.h:371` `* by itself (bx_width_cap2);`
- `CSS_LEN_UNSET` (function) `include/page_view.h:570` `* CSS_LEN_UNSET (unset) / CSS_LEN_AUTO. z_index is signed, or CSS_LEN_UNSET. v1 * paints only position:relative (an...`
- `scale` (function) `include/page_view.h:645` `* scale(1)) and rotate in whole degrees (transform_rotate);`
- `tree` (function) `include/page_view.h:690` `* box tree (a mask covers its whole subtree);`
- `declare` (function) `include/page_view.h:892` `* margin the author did not declare (px or %), 0 on a declared side (the body's * own box, or nothing for 0, owns...`
- `nonzero` (function) `include/page_view.h:904` `* when nonzero (JS allowed for this page) the <noscript> subtree is suppressed. */ pv_status pv_build_ex(const...`
- `resolved` (function) `include/page_view.h:911` `* author CSS is still resolved (the presentation layer decides whether to apply it). * pv_build_ex is pv_build_full...`
- `policy` (function) `include/page_view.h:919` `* TRUSTED parent under full network policy (spec/tab.md §8) -- page_view stays * pure and never fetches. The...`
- `pv_computed_new` (function) `include/page_view.h:988` `pv_computed *pv_computed_new(const hp_document *doc, int prefers_dark, const char *extern_css, size_t extern_len...`
- `pv_computed_new_cached` (function) `include/page_view.h:991` `pv_computed *pv_computed_new_cached(const hp_document *doc, int prefers_dark, const char *extern_css, size_t...` -- getComputedStyle bridge (spec/js_computed_style.md).
- `pv_computed_get` (function) `include/page_view.h:999` `int pv_computed_get(pv_computed *pc, const void *native_el, css_style *st, double *font_px, int *inherited_color);` -- Resolves native_el (a dom_native_node pointer of the SAME document) into *st; when non-NULL, *font_px receives its...
- `pv_computed_free` (function) `include/page_view.h:1002` `void pv_computed_free(pv_computed *pc);`
- `cause` (function) `include/page_view.h:1006` `* cause (spec/css_drops.md). Builds no view and changes nothing -- it exists so * "what is this page's CSS losing?"...`
- `pv_new` (function) `include/page_view.h:1018` `pv_view *pv_new(void);` -- Allocates an empty view (used by the IPC deserialiser to rebuild a view on the * receiving side).
- `form` (function) `include/page_view.h:1037` `* form (-1 if none);`
- `pv_set_emphasis` (function) `include/page_view.h:1069` `void pv_set_emphasis(pv_view *v, int bold, int italic);` -- Sets the inline emphasis flags (bold from <b>/<strong>/<th>, italic from <i>/<em>) on the most recently appended run.
- `default` (function) `include/page_view.h:1074` `* structure is carried by default (not gated by caps.css). */ void pv_set_indent(pv_view *v, int indent);`
- `pv_set_color` (function) `include/page_view.h:1077` `void pv_set_color(pv_view *v, int fg_rgb);`
- `pv_set_bgcolor` (function) `include/page_view.h:1084` `void pv_set_bgcolor(pv_view *v, int bg_rgb);` -- Sets the author background-color (packed 0xRRGGBB, or -1 for none) on the most recently appended run.
- `pv_set_text_style` (function) `include/page_view.h:1093` `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs, int line_scale, int text_decoration);` -- Sets the author text presentation (text_align as a css_align, font_scale as a font-size percent or 0, font_abs as 1...
- `pv_text_ext_reset` (function) `include/page_view.h:1156` `void pv_text_ext_reset(pv_text_ext *e);` -- Gradient text (2026-07-19). text_fill: -webkit-text-fill-color from the nearest ancestor that sets it (packed /...
- `ancestors` (function) `include/page_view.h:1161` `* itself by walking its ancestors (css_visibility, 0 = unset). * * An explicit value on the run WINS over the box...`
- `pv_set_text_ext` (function) `include/page_view.h:1171` `void pv_set_text_ext(pv_view *v, const pv_text_ext *e);`
- `pv_set_grad_text` (function) `include/page_view.h:1177` `void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4);` -- Sets the gradient-text fill (grad_text_*) verbatim on the most recently appended run. n < 2 is a no-op (no gradient).
- `run` (function) `include/page_view.h:1180` `* run (cont_id, the bx_display, the parsed gap/justify/cols, plus flex-wrap/ * row-gap/align-items). No-op on an...`
- `pv_set_row_span` (function) `include/page_view.h:1193` `void pv_set_row_span(pv_view *v, int row_span);` -- Sets the container's grid track sizes and this run's ITEM column span on the most recently appended run...
- `pv_set_grid_area` (function) `include/page_view.h:1197` `void pv_set_grid_area(pv_view *v, int row_start, int col_start);` -- Sets the last run's RESOLVED named-grid cell (-1, -1 = auto-placed).
- `pv_set_grid_rows` (function) `include/page_view.h:1198` `void pv_set_grid_rows(pv_view *v, int grid_rows);`
- `pv_set_ua_tag` (function) `include/page_view.h:1203` `void pv_set_ua_tag(pv_view *v, int ua_tag);` -- Sets the last run's ua_tag (a bx_ua_tag code: the user-agent box identity of its nearest block-level ancestor).
- `pv_set_cont_box` (function) `include/page_view.h:1207` `void pv_set_cont_box(pv_view *v, int cont_box_id);` -- Sets the last run's cont_box_id (the box enclosing its container's items; -1 = * none).
- `pv_set_grid` (function) `include/page_view.h:1208` `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span);`
- `pv_set_flex` (function) `include/page_view.h:1216` `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis, int flex_order, int flex_direction, int...` -- Stage 3: sets the flex per-item values on the most recently appended run — the ITEM's resolved grow/shrink (x100, -1...
- `pv_set_flex_mauto` (function) `include/page_view.h:1219` `void pv_set_flex_mauto(pv_view *v, int mauto);` -- Stage 3: sets the flex per-item values on the most recently appended run — the ITEM's resolved grow/shrink (x100, -1...
- `pv_set_cont_item` (function) `include/page_view.h:1223` `void pv_set_cont_item(pv_view *v, int cont_item);` -- Sets the container-item ordinal on the most recently appended run (-1 = none). * No-op on an empty or NULL view; the...
- `pv_set_float_w` (function) `include/page_view.h:1234` `void pv_set_float_w(pv_view *v, int float_w, int float_w_pct, int float_box, int float_ow, int float_ow_pct, int...` -- Stamps the float founder's own declared width halves (pv_run.float_w) on the * most recently appended run.
- `pv_set_float` (function) `include/page_view.h:1237` `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear, int float_ml, int float_ml_pct, int...`
- `pv_set_box` (function) `include/page_view.h:1247` `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w, int box_center, int box_mt, int box_mb);` -- Sets the author box model on the most recently appended run (left/right insets, width cap, centered flag, and...
- `pv_set_box_pct` (function) `include/page_view.h:1253` `void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct, int box_mt_pct, int box_mb_pct);` -- Sets the symbolic percentage width cap (per-mille, 0 = none; Hito 32) on the most recently appended run.
- `pv_set_box_maxw` (function) `include/page_view.h:1258` `void pv_set_box_maxw(pv_view *v, int box_mw, int box_mw_pct);` -- Sets the max-width cap (px half, 0 = none; per-mille half, 0 = none) on the most * recently appended run.
- `pv_set_node_id` (function) `include/page_view.h:1263` `void pv_set_node_id(pv_view *v, dom_node_id node_id);` -- Keystone (Stage 0) setter for the most recently appended run: the dom_node_id of the source element.
- `pv_set_block_id` (function) `include/page_view.h:1268` `void pv_set_block_id(pv_view *v, int block_id);` -- Box engine (Hito 23b-8) setter for the most recently appended run: the block_id of the box-carrying block it belongs...
- `pv_set_own_box` (function) `include/page_view.h:1272` `void pv_set_own_box(pv_view *v, int box_id);` -- Records the replaced element's own box def index on the last appended run.
- `pv_set_oof` (function) `include/page_view.h:1276` `void pv_set_oof(pv_view *v, int oof);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_justify_self` (function) `include/page_view.h:1279` `void pv_set_justify_self(pv_view *v, int justify_self);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_block_node` (function) `include/page_view.h:1282` `void pv_set_block_node(pv_view *v, dom_node_id id);` -- Records out-of-flow subtree membership on the last appended run (see * pv_run.oof_subtree).
- `pv_set_br_line` (function) `include/page_view.h:1294` `void pv_set_br_line(pv_view *v, int br_line);` -- Sets the last appended run's PV_BR_* flags (see pv_run.br_line); other bits * are dropped.
- `pv_cont_count` (function) `include/page_view.h:1309` `size_t pv_cont_count(const pv_view *v);` -- pv_cont_count is v->ncont (0 when v is NULL); pv_cont_at returns conts[i] * (i == a cont_id) or NULL when out of...
- `pv_cont_at` (function) `include/page_view.h:1310` `const pv_cont_def *pv_cont_at(const pv_view *v, size_t i);`
- `pv_set_input_checked` (function) `include/page_view.h:1314` `void pv_set_input_checked(pv_view *v, int checked);` -- Sets the input's checked state (-1 n/a, 0 unchecked, 1 checked) on the most * recently appended run.
- `pv_set_input_placeholder` (function) `include/page_view.h:1318` `void pv_set_input_placeholder(pv_view *v, int ph_color);` -- Sets the input's checked state (-1 n/a, 0 unchecked, 1 checked) on the most * recently appended run.
- `pv_svg_append_root_attrs` (function) `include/page_view.h:1324` `char *pv_svg_append_root_attrs(const char *markup, size_t len, const char *attrs, size_t *out_len);` -- Appends attrs (e.g.
- `pv_placeholder_color` (function) `include/page_view.h:1327` `int pv_placeholder_color(const css_style *ph);` -- Appends attrs (e.g.
- `pv_set_input_select_opts` (function) `include/page_view.h:1331` `void pv_set_input_select_opts(pv_view *v, const char *select_opts);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_free` (function) `include/page_view.h:1334` `void pv_free(pv_view *v);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_count` (function) `include/page_view.h:1337` `size_t pv_count(const pv_view *v);` -- Sets the <select> options string ("opt||label||opt||label") on the most recently * appended run, taking an owned copy.
- `pv_at` (function) `include/page_view.h:1338` `const pv_run *pv_at(const pv_view *v, size_t i);`
- `pv_box_count` (function) `include/page_view.h:1342` `size_t pv_box_count(const pv_view *v);` -- Box tree accessors (Step D). pv_box_count is the number of box definitions; * pv_box_at returns boxes[i] (i == a...
- `pv_box_at` (function) `include/page_view.h:1343` `const pv_box_def *pv_box_at(const pv_view *v, size_t i);`

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

## include/pq_seal.h
Depends on: `include/local_store.h`
Imported by: `src/http_cache.c`, `src/pq_seal.c`, `tests/test_pq_seal.c`
- `pqs_free` (function) `include/pq_seal.h:41` `void pqs_free(pqs_keys *k);`
- `pqs_buf_free` (function) `include/pq_seal.h:51` `void pqs_buf_free(uint8_t *buf, size_t len);` -- DER of the PRIVATE key: secret, the caller seals it before it touches disk. *der is owned * (release with...

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
Imported by: `fuzz/fuzz_prefs.c`, `gui/browser_ui.c`, `include/profile.h`, `include/ui.h`, `src/prefs.c`, `tests/test_prefs.c`, `tests/test_profile.c`
- `prefs_init` (function) `include/prefs.h:66` `void prefs_init(prefs_state *p);` -- Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `prefs_free` (function) `include/prefs.h:69` `void prefs_free(prefs_state *p);` -- Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `free` (function) `include/prefs.h:72` `* free(). */ prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len);`
- `prefs_bookmark_index` (function) `include/prefs.h:82` `int prefs_bookmark_index(const prefs_state *p, const char *url);` -- Parses text[0..len) over an out ALREADY initialised with prefs_init.
- `prefs_suggest` (function) `include/prefs.h:101` `int prefs_suggest(const prefs_state *p, const char *query, char *out, size_t row_len, int max_rows);` -- Omnibox autocomplete: up to max_rows distinct URLs matching query (case- insensitive) written to out (rows of...
- `anyway` (function) `include/prefs.h:106` `* page is rendered by the normal confined pipeline anyway (defence in depth). * *out is owned (free());`

## include/pres_hints.h
Depends on: `include/css.h`
Imported by: `fuzz/fuzz_table_layout.c`, `src/page_view.c`, `src/pres_hints.c`, `tests/test_pres_hints.c`
- `ph_parse_dimension` (function) `include/pres_hints.h:24` `int ph_parse_dimension(const char *s, size_t len, int *px, int *per_mille);` -- #ifdef __cplusplus #error "Freedom is pure C11 by policy; C++ is not supported." #endif #include <stddef.h> #include...
- `ph_apply` (function) `include/pres_hints.h:31` `void ph_apply(const char *tag, ph_attr_fn get, void *ctx, unsigned flags, css_style *cs);` -- Applies the hints of element `tag` (lower-case, NUL-terminated) to *cs; flags is a set of * PH_*.
- `ph_parse_nonneg` (function) `include/pres_hints.h:34` `int ph_parse_nonneg(const char *s, size_t len, int *out);` -- Applies the hints of element `tag` (lower-case, NUL-terminated) to *cs; flags is a set of * PH_*.
- `ph_table_cellpadding` (function) `include/pres_hints.h:37` `int ph_table_cellpadding(ph_attr_fn get, void *ctx);` -- Applies the hints of element `tag` (lower-case, NUL-terminated) to *cs; flags is a set of * PH_*.
- `ph_cell_padding` (function) `include/pres_hints.h:41` `void ph_cell_padding(int cellpad, css_style *cs);` -- A table cell's padding: every side the cascade left unset takes cellpad px, or the UA * sheet's 1px when cellpad < 0.

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
- `default` (function) `include/render_doc.h:153` `* default (layout is structure, not author styling, and leaks nothing to the * network) so the presentation layer...`
- `to` (function) `include/render_doc.h:253` `* belongs to (-1 = none);`
- `rdp_images_warning` (function) `include/render_doc.h:311` `* rdp_images_warning() is prepended so the user is always told. Each image * becomes an RD_IMAGE block whose...`
- `rd_free` (function) `include/render_doc.h:321` `void rd_free(rd_doc *d);` -- Builds the paint-ready document from an inert display list and the page's capabilities. view == NULL is treated as...
- `rd_count` (function) `include/render_doc.h:324` `size_t rd_count(const rd_doc *d);` -- images and caps.images is false, a single RD_NOTICE block carrying rdp_images_warning() is prepended so the user is...
- `rd_at` (function) `include/render_doc.h:325` `const rd_block *rd_at(const rd_doc *d, size_t i);`
- `rd_box_count` (function) `include/render_doc.h:329` `size_t rd_box_count(const rd_doc *d);` -- Box tree accessors (Step D). rd_box_count is the number of box definitions (0 when * caps.css is off); rd_box_at...
- `rd_box_at` (function) `include/render_doc.h:330` `const pv_box_def *rd_box_at(const rd_doc *d, size_t i);`
- `rd_cont_count` (function) `include/render_doc.h:334` `size_t rd_cont_count(const rd_doc *d);` -- Container table accessors. rd_cont_count is the number of containers; rd_cont_at * returns conts[i] (i == a run's...
- `rd_cont_at` (function) `include/render_doc.h:335` `const pv_cont_def *rd_cont_at(const rd_doc *d, size_t i);`
- `rd_kind_name` (function) `include/render_doc.h:339` `const char *rd_kind_name(rd_kind k);` -- Stable, short English name of a block kind for structured/agent output.
- `rd_block_tag` (function) `include/render_doc.h:347` `const char *rd_block_tag(const rd_block *b);` -- Canonical HTML tag name for a block, so the presentation layer can look up its user-agent box (box_style) without...
- `rd_block_heading_level` (function) `include/render_doc.h:354` `int rd_block_heading_level(const rd_block *b);` -- Effective heading level of a block, 0 when it is not heading content.
- `decision` (function) `include/render_doc.h:357` `* decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never * NULL. */ const char...`
- `IMG_FAIL_OK` (function) `include/render_doc.h:363` `* IMG_FAIL_OK (not a failure) or the reason is unknown. */ const char *rd_image_fail_label(img_fail_reason reason);`
- `rd_input_label` (function) `include/render_doc.h:368` `const char *rd_input_label(int input_type);` -- Stable, short English name of a form control type (a pv_input_type value), e.g. * "text" / "password" / "submit".
- `rd_input_invisible` (function) `include/render_doc.h:373` `int rd_input_invisible(int input_type);` -- Nonzero iff a control of this type has no face of its own and is therefore never laid out or painted: a hidden...

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
Imported by: `fuzz/fuzz_hls.c`, `fuzz/fuzz_request_headers.c`, `gui/browser_ui.c`, `src/freedom.c`, `src/hls.c`, `src/render_policy.c`, `src/request_policy.c`, `src/secure_fetch.c`, `src/tab.c`, `tests/test_request_policy.c`
- `rp_host_of` (function) `include/request_policy.h:30` `int rp_host_of(const char *url, char *out, size_t out_size);` -- Lowercased host of an absolute URL into out.
- `rp_site_of` (function) `include/request_policy.h:34` `int rp_site_of(const char *host, char *out, size_t out_size);` -- Registrable domain ("site") of a host into out (simplified public-suffix * rule).
- `rp_same_site` (function) `include/request_policy.h:37` `int rp_same_site(const char *top_level_url, const char *request_url);` -- Registrable domain ("site") of a host into out (simplified public-suffix * rule).
- `rp_sanitize_request_headers` (function) `include/request_policy.h:57` `int rp_sanitize_request_headers(const char *raw, char *out, size_t cap);` -- Filters the page-supplied header block `raw` ("Name: value" lines separated by '\n') into `out` (same format...
- `rp_headers_have` (function) `include/request_policy.h:61` `static inline int rp_headers_have(const char *lines, const char *name)` -- 1 when the sanitized block `lines` carries a header called `name` (case-insensitive).

## include/scroll_req.h
Imported by: `fuzz/fuzz_scroll_req.c`, `gui/browser_ui.c`, `include/tab.h`, `src/scroll_req.c`, `src/tab.c`, `tests/test_scroll_req.c`
- `srq_encode` (function) `include/scroll_req.h:58` `void srq_encode(const srq_req *r, int32_t out[SRQ_WIRE_N]);` -- Writes r as SRQ_WIRE_N int32: kind, behavior, block, y, margin_top, margin_bottom, n, nsub.
- `srq_decode` (function) `include/scroll_req.h:64` `int srq_decode(const int32_t in[SRQ_WIRE_N], size_t max_handles, srq_req *out);` -- Reads a record written by srq_encode, validating EVERY field: enums in range, |coords| <= SRQ_MAX_COORD, n <=...
- `srq_target` (function) `include/scroll_req.h:71` `int srq_target(const srq_req *r, const srq_view *v, double el_top, double el_bottom, double *out);` -- The scroll offset r asks for, in [0, v->max_scroll]. el_top/el_bottom are the target's document box (SRQ_ELEMENT...
- `srq_smooth` (function) `include/scroll_req.h:76` `int srq_smooth(const srq_req *r, int root_smooth);` -- 1 when the scroll should animate: SRQ_SMOOTH, or SRQ_AUTO with the root's computed * scroll-behavior smooth...

## include/secure_fetch.h
Depends on: `include/anti_fp.h`
Imported by: `gui/browser_ui.c`, `include/cached_fetch.h`, `include/ws_hub.h`, `src/freedom.c`, `src/secure_fetch.c`, `src/tab.c`, `tests/itest_secure_fetch.c`, `tests/test_secure_fetch.c`
- `validators` (function) `include/secure_fetch.h:18` `* The security logic lives in pure validators (no I/O);`
- `rp_sanitize_request_headers` (function) `include/secure_fetch.h:115` `* rp_sanitize_request_headers ("Name: value\n" lines);`
- `sf_global_init` (function) `include/secure_fetch.h:242` `void sf_global_init(void);` -- Initialises process-global transport state (libcurl/OpenSSL) once, from the main thread, before any concurrent...
- `EXCLUDED` (function) `include/secure_fetch.h:248` `* cookies are EXCLUDED (network-only, never exposed to JS) and expired cookies skipped. * Only for a TRUSTED host...`
- `sf_cookie_put` (function) `include/secure_fetch.h:255` `void sf_cookie_put(const char *url, const char *namevalue);` -- Injects a JS-set cookie ("name=value") into the shared jar, scoped to url's host, as if it arrived via Set-Cookie...
- `sf_cookie_line_matches` (function) `include/secure_fetch.h:260` `int sf_cookie_line_matches(const char *line, const char *host, const char *path, long now, char *out, size_t outsz);` -- Pure: parses one CURLINFO_COOKIELIST Netscape line ("domain\\tflag\\tpath\\tsecure\\t expiry\\tname\\tvalue"); if...
- `sf_user_agent_or_default` (function) `include/secure_fetch.h:269` `const char *sf_user_agent_or_default(const char *ua);` -- Returns ua when it is a non-empty string, else SF_DEFAULT_USER_AGENT.
- `sf_accept_language_or_default` (function) `include/secure_fetch.h:273` `const char *sf_accept_language_or_default(const char *lang);` -- As sf_user_agent_or_default for Accept-Language.
- `sf_impersonate_kex_groups` (function) `include/secure_fetch.h:277` `const char *sf_impersonate_kex_groups(void);` -- The interim impersonation ClientHello strings (pure; single source of truth so the * shaping is unit-testable...
- `sf_impersonate_tls13_ciphers` (function) `include/secure_fetch.h:278` `const char *sf_impersonate_tls13_ciphers(void);`
- `skipped` (function) `include/secure_fetch.h:298` `* skipped (a classical key exchange is accepted);`
- `sf_is_redirect_code` (function) `include/secure_fetch.h:309` `int sf_is_redirect_code(long http_code);` -- Enforces the full connection policy in order: TLS version, then KE group, then certificate chain.
- `sf_header_value` (function) `include/secure_fetch.h:320` `int sf_header_value(const char *header_line, const char *name, char *out, size_t outsz);` -- Generic header-line reader for the cache validators: when header_line is `name:` (matched case-insensitively, name...
- `bits` (function) `include/secure_fetch.h:357` `* *flags receives CURLWS_* bits (text/binary/close/cont);`
- `sf_ws_fd` (function) `include/secure_fetch.h:364` `int sf_ws_fd(const sf_ws *ws);` -- Non-blocking: reads one frame chunk into buf. *got == 0 when nothing is pending. *flags receives CURLWS_* bits...
- `sf_ws_close` (function) `include/secure_fetch.h:367` `void sf_ws_close(sf_ws *ws);` -- Non-blocking: reads one frame chunk into buf. *got == 0 when nothing is pending. *flags receives CURLWS_* bits...
- `connection` (function) `include/secure_fetch.h:371` `* on each connection (Zero Trust). Each target is re-validated and a downgrade * to http:// is refused. Exceeding...`
- `sf_get` (function) `include/secure_fetch.h:380` `* sf_get (Zero Trust): an insecure POST is not representable. Does not follow * redirects (the caller inspects...`
- `sf_response_free` (function) `include/secure_fetch.h:391` `void sf_response_free(sf_response *resp);` -- Performs an HTTPS POST under the given policy, sending body (body_len bytes) with the given Content-Type.
- `exhausted` (function) `include/secure_fetch.h:402` `* is exhausted (*next untouched). `allowlisted` enables the sovereignty rung. */ int sf_fallback_policy(sf_status...`
- `sf_rcache_put` (function) `include/secure_fetch.h:415` `int sf_rcache_put(const char *from, const char *to, time_t now);` -- Permanent-redirect memory: a 301/308 seen by sf_get_follow is remembered in RAM only (never on disk) for a day, so...
- `sf_rcache_get` (function) `include/secure_fetch.h:416` `int sf_rcache_get(const char *from, time_t now, char *out, size_t cap);`
- `sf_rcache_clear` (function) `include/secure_fetch.h:417` `void sf_rcache_clear(void);` -- Permanent-redirect memory: a 301/308 seen by sf_get_follow is remembered in RAM only (never on disk) for a day, so...
- `sf_rcache_set_backing` (function) `include/secure_fetch.h:426` `void sf_rcache_set_backing(sf_rcache_load_fn load, sf_rcache_save_fn save, void *ctx);`

## include/sha2.h
Imported by: `src/js_env.c`, `src/sha2.c`, `tests/test_sha2.c`
- `sha_digest_len` (function) `include/sha2.h:21` `size_t sha_digest_len(sha_alg alg);` -- sha2 -- one-shot SHA-1 / SHA-256 / SHA-384 / SHA-512 (FIPS 180-4), pure and allocation-free.
- `sha_alg_from_name` (function) `include/sha2.h:24` `int sha_alg_from_name(const char *name, sha_alg *out);` -- sha2 -- one-shot SHA-1 / SHA-256 / SHA-384 / SHA-512 (FIPS 180-4), pure and allocation-free.
- `sha_digest` (function) `include/sha2.h:28` `int sha_digest(sha_alg alg, const void *data, size_t len, uint8_t *out);` -- Hashes data[0..len) into out (>= sha_digest_len(alg) bytes).

## include/sheet_cache.h
Depends on: `include/css.h`
Imported by: `fuzz/fuzz_page_view.c`, `src/page_view.c`, `src/sheet_cache.c`, `src/tab.c`, `tests/test_page_view.c`, `tests/test_sheet_cache.c`
- `shc_new` (function) `include/sheet_cache.h:52` `shc_cache *shc_new(size_t max_text_bytes);` -- max_text_bytes: texts longer than this are parsed but never retained; 0 selects * FC_SHC_MAX_TEXT_BYTES.
- `shc_free` (function) `include/sheet_cache.h:55` `void shc_free(shc_cache *c);` -- max_text_bytes: texts longer than this are parsed but never retained; 0 selects * FC_SHC_MAX_TEXT_BYTES.
- `shc_acquire` (function) `include/sheet_cache.h:60` `shc_sheet *shc_acquire(shc_cache *cache, const shc_key *key);` -- The parsed sheet for *key: the retained one when every input matches, a fresh parse otherwise. cache == NULL parses...
- `shc_css` (function) `include/sheet_cache.h:64` `const css_sheet *shc_css(const shc_sheet *s);` -- The read-only sheet behind a handle; NULL when the parse itself failed (the css * module treats a NULL sheet as...
- `shc_release` (function) `include/sheet_cache.h:67` `void shc_release(shc_sheet *s);` -- The read-only sheet behind a handle; NULL when the parse itself failed (the css * module treats a NULL sheet as...
- `shc_stats_get` (function) `include/sheet_cache.h:70` `void shc_stats_get(const shc_cache *c, shc_stats *out);` -- The read-only sheet behind a handle; NULL when the parse itself failed (the css * module treats a NULL sheet as...

## include/shm_slots.h
Imported by: `gui/browser_ui.c`, `tests/test_shm_slots.c`
- `ss_init` (function) `include/shm_slots.h:24` `static inline void ss_init(ss_state *s)`
- `ss_committed` (function) `include/shm_slots.h:41` `static inline void ss_committed(ss_state *s, int i)` -- Chooses the slot to paint into: the current one if free, else the other free one.
- `ss_released` (function) `include/shm_slots.h:49` `static inline int ss_released(ss_state *s, int i)` -- if (!s->busy[i]) { s->back = i; return i; } } return -1; } /* The painted slot was attached and committed. static...

## include/smooth_scroll.h
Imported by: `fuzz/fuzz_smooth_scroll.c`, `gui/browser_ui.c`, `src/smooth_scroll.c`, `tests/test_smooth_scroll.c`
- `sms_init` (function) `include/smooth_scroll.h:27` `void sms_init(sms_state *s, double pos);`
- `sms_jump` (function) `include/smooth_scroll.h:28` `void sms_jump(sms_state *s, double pos);`
- `sms_retarget` (function) `include/smooth_scroll.h:29` `void sms_retarget(sms_state *s, double target, double now_ms, double dur_ms);`
- `sms_sample` (function) `include/smooth_scroll.h:30` `double sms_sample(sms_state *s, double now_ms);`
- `sms_goal` (function) `include/smooth_scroll.h:31` `double sms_goal(const sms_state *s);`
- `sms_active` (function) `include/smooth_scroll.h:32` `int sms_active(const sms_state *s);`


Next: [API_p6.md](API_p6.md)
