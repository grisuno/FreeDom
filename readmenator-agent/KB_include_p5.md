# Subsystem: include (page 5 of 5)
Previous: [KB_include_p4.md](KB_include_p4.md)

## include/text_case.h
- Doc: Case mapping for text-transform and synthesized small caps (spec/text_case.md).
- Layer: utility
- Language: h
- Symbols:
  - `tc_run` (struct, line 33)
  - `cp` (function, line 19) `* cp (identity otherwise), so a transformed text keeps its length. */ uint32_t tc_upper(uint32_t cp);`
  - `tc_lower` (function, line 21) `uint32_t tc_lower(uint32_t cp);`
  - `tc_is_lower` (function, line 24) `int tc_is_lower(uint32_t cp);`
  - `tc_transform` (function, line 29) `size_t tc_transform(const char *s, size_t n, int transform, int word_start, char *out, size_t cap);`
  - `tc_smallcaps_runs` (function, line 41) `size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap);`
  - `FREEDOM_TEXT_CASE_H` (macro, line 2) `#define FREEDOM_TEXT_CASE_H`
  - `TC_SMALLCAPS_SCALE` (macro, line 15) `#define TC_SMALLCAPS_SCALE`
- Imported by: `gui/browser_ui.c`, `src/text_case.c`, `tests/test_text_case.c`

## include/text_shape.h
- Doc: tsh_font: Font selector: a css_font_family bucket (CSS_FF_*) plus weight/slant flags.
- Layer: utility
- Language: h
- Symbols:
  - `tsh_font` (struct, line 33)
  - `tsh_run` (struct, line 132)
  - `tsh_status` (enum, line 80)
  - `family` (type_alias, line 33) `typedef struct tsh_font { int family;`
  - `end` (type_alias, line 132) `typedef struct tsh_run { size_t start, end;`
  - `content` (function, line 11) `* TEXT is hostile remote content (sanitised UTF-8) and is fuzzed (make fuzz-tsh);`
  - `tsh_family_is_generic` (function, line 52) `int tsh_family_is_generic(const char *name);`
  - `wins` (function, line 58) `* the first name the resolver accepts wins (returns 1, family in out). Pure: the * resolver is injected (fontconfig...`
  - `tsh_pick_family` (function, line 68) `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong, size_t n, int...`
  - `tsh_local_handle` (function, line 75) `int tsh_local_handle(const char *list);`
  - `tsh_ready` (function, line 89) `int tsh_ready(void);`
  - `origin` (function, line 92) `* glyphs are written with positions relative to origin (0,0) on the baseline, * and *out_adv holds the total pen...`
  - `tsh_measure` (function, line 101) `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len);`
  - `tsh_webfont_register` (function, line 114) `int tsh_webfont_register(const char *name, const unsigned char *bytes, size_t nbytes, int bold, int italic);`
  - `tsh_webfont_clear` (function, line 120) `void tsh_webfont_clear(void);`
  - `tsh_face` (function, line 127) `cairo_font_face_t *tsh_face(const tsh_font *f);`
  - `own` (function, line 136) `* face of their own (controls, combining marks, variation selectors, ZWJ/ZWNJ) * stay in the run before them....`
  - `tsh_shutdown` (function, line 143) `void tsh_shutdown(void);`
  - `FREEDOM_TEXT_SHAPE_H` (macro, line 19) `#define FREEDOM_TEXT_SHAPE_H`
  - `TSH_LOCAL_LISTS` (macro, line 46) `#define TSH_LOCAL_LISTS`
  - `TSH_LOCAL_FAMILIES` (macro, line 47) `#define TSH_LOCAL_FAMILIES`
  - `TSH_FAMILY_MAX` (macro, line 48) `#define TSH_FAMILY_MAX`
  - `TSH_MAX_GLYPHS` (macro, line 77) `#define TSH_MAX_GLYPHS`
  - `TSH_MAX_TEXT` (macro, line 78) `#define TSH_MAX_TEXT`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/text_shape.c`, `src/webfont_load.c`, `tests/test_text_shape.c`, `tests/test_webfont_load.c`

## include/textfield.h
- Doc: tf_init: typedef struct tf_field { char   buf[TF_CAP]; /* content, always NUL-terminated at...
- Layer: utility
- Language: h
- Symbols:
  - `tf_field` (struct, line 25)
  - `tf_status` (enum, line 31)
  - `buf` (type_alias, line 24) `typedef struct tf_field { char buf[TF_CAP];`
  - `tf_init` (function, line 38) `void tf_init(tf_field *f);`
  - `tf_clear` (function, line 45) `void tf_clear(tf_field *f);`
  - `tf_backspace` (function, line 53) `void tf_backspace(tf_field *f);`
  - `tf_delete` (function, line 56) `void tf_delete(tf_field *f);`
  - `tf_move` (function, line 59) `void tf_move(tf_field *f, long delta);`
  - `tf_home` (function, line 62) `void tf_home(tf_field *f);`
  - `tf_end` (function, line 63) `void tf_end(tf_field *f);`
  - `tf_text` (function, line 66) `const char *tf_text(const tf_field *f);`
  - `tf_len` (function, line 67) `size_t tf_len(const tf_field *f);`
  - `tf_cursor` (function, line 68) `size_t tf_cursor(const tf_field *f);`
  - `FREEDOM_TEXTFIELD_H` (macro, line 2) `#define FREEDOM_TEXTFIELD_H`
  - `TF_CAP` (macro, line 23) `#define TF_CAP`
- Imported by: `gui/browser_ui.c`, `src/textfield.c`, `tests/test_textfield.c`

## include/tls_impersonate.h
- Doc: ti_req: Request: parent -> helper.
- Layer: utility
- Language: h
- Symbols:
  - `ti_req` (struct, line 72)
  - `ti_resp` (struct, line 82)
  - `ti_profile` (enum, line 41)
  - `status` (type_alias, line 82) `typedef struct ti_resp { long status;`
  - `path` (function, line 26) `* Zero Knowledge path (PQ-hybrid, VERIFYPEER). * * 2. ti_encode_x / ti_decode_x — the length-prefixed, fail-closed...`
  - `chain` (function, line 32) `* * The response carries the peer certificate chain (DER) and the negotiated group so * the TRUSTED PARENT...`
  - `ti_should_impersonate` (function, line 56) `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled, int user_opt_in);`
  - `success` (function, line 97) `* ti_decode_* returns 0 on success (out fully populated), <0 on any malformed, * truncated or over-cap input (out...`
  - `ti_decode_req` (function, line 101) `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out);`
  - `ti_req_free` (function, line 102) `void ti_req_free(ti_req *r);`
  - `ti_encode_resp` (function, line 104) `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap);`
  - `ti_decode_resp` (function, line 105) `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out);`
  - `ti_resp_free` (function, line 106) `void ti_resp_free(ti_resp *r);`
  - `FREEDOM_TLS_IMPERSONATE_H` (macro, line 2) `#define FREEDOM_TLS_IMPERSONATE_H`
  - `TI_MAGIC` (macro, line 60) `#define TI_MAGIC`
  - `TI_MAX_URL` (macro, line 61) `#define TI_MAX_URL`
  - `TI_MAX_METHOD` (macro, line 62) `#define TI_MAX_METHOD`
  - `TI_MAX_HEADERS` (macro, line 63) `#define TI_MAX_HEADERS`
  - `TI_MAX_BODY` (macro, line 64) `#define TI_MAX_BODY`
  - `TI_MAX_RESP_HDR` (macro, line 65) `#define TI_MAX_RESP_HDR`
  - `TI_MAX_RESP_BODY` (macro, line 66) `#define TI_MAX_RESP_BODY`
  - `TI_MAX_CHAIN` (macro, line 67) `#define TI_MAX_CHAIN`
  - `TI_MAX_GROUP` (macro, line 68) `#define TI_MAX_GROUP`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/tls_impersonate.c`, `tests/test_tls_impersonate.c`

## include/ui.h
- Doc: ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no...
- Layer: presentation
- Language: h
- Symbols:
  - `ui_line` (struct, line 30)
  - `ui_layout` (struct, line 35)
  - `rd_doc` (struct, line 69)
  - `jg_table` (struct, line 95)
  - `tab` (struct, line 105)
  - `ui_status` (enum, line 20)
  - `offset` (type_alias, line 30) `typedef struct ui_line { size_t offset;`
  - `space` (function, line 44) `* Breaks at the last fitting space (the break space is consumed), hard-breaks * words longer than max_cols, and...`
  - `ui_layout_free` (function, line 52) `void ui_layout_free(ui_layout *lay);`
  - `ui_clamp_scroll` (function, line 55) `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines);`
  - `available` (function, line 86) `* cheapest artifact to inspect a render where no display is available (CI, an AI * agent): export, then read the PNG...`
  - `out` (function, line 98) `* ui_render_png does and fills *out (jg_init'ed by the caller) with one rect per * element in document coordinates...`
  - `placeholders` (function, line 108) `* above always draw image placeholders (no worker to decode hostile bytes);`
  - `disk` (function, line 113) `* images are read from disk (confined to the document directory by render_doc). * top_url is the page origin (https...`
  - `images` (function, line 115) `* fetcher loads no images (placeholders, as before). Any image that fails falls back * to its placeholder...`
  - `ui_render_viewport_w` (function, line 142) `int ui_render_viewport_w(void);`
  - `ui_persisted_prefs` (function, line 147) `int ui_persisted_prefs(prefs_state *out);`
  - `FREEDOM_UI_H` (macro, line 2) `#define FREEDOM_UI_H`
- Depends on: `include/prefs.h`
- Imported by: `gui/browser_ui.c`, `gui/freedom_view.c`, `gui/ui_render.c`, `src/freedom.c`, `src/ui_layout.c`, `tests/test_ui.c`

## include/url.h
- Doc: url_parts: Components of a validated absolute https URL, sliced for a JS location object.
- Layer: utility
- Language: h
- Symbols:
  - `url_parts` (struct, line 129)
  - `url_status` (enum, line 32)
  - `url_omni_kind` (enum, line 78)
  - `url_is_https` (function, line 42) `int url_is_https(const char *s);`
  - `url_has_scheme` (function, line 46) `int url_has_scheme(const char *s);`
  - `url_authority_len` (function, line 51) `size_t url_authority_len(const char *url);`
  - `URL_ERR_NOT_HTTPS` (function, line 109) `* URL_ERR_NOT_HTTPS (out untouched);`
  - `path` (function, line 115) `* absolute path ("file:///..."). NULL => 0. */ int url_is_file(const char *s);`
  - `url_file_path` (function, line 121) `const char *url_file_path(const char *s);`
  - `url` (function, line 126) `* Every field ALIASES the input url (not owned, valid while url is alive);`
  - `password` (function, line 152) `* username and password (owned, must be freed) into *username_out and * *password_out, and returns URL_OK. When...`
  - `FREEDOM_URL_H` (macro, line 2) `#define FREEDOM_URL_H`
  - `URL_MAX_LEN` (macro, line 30) `#define URL_MAX_LEN`
  - `URL_SEARCH_ENDPOINT` (macro, line 76) `#define URL_SEARCH_ENDPOINT`
- Imported by: `gui/browser_ui.c`, `include/form.h`, `include/js_dom.h`, `include/js_location.h`, `src/freedom.c`, `src/js_location.c`, `src/link_nav.c`, `src/prefetch.c`, `src/render_doc.c`, `src/secure_fetch.c`, `src/tab.c`, `src/url.c`, `src/webfont_load.c`, `tests/test_js_dom.c`, `tests/test_tab.c`, `tests/test_url.c`

## include/util.h
- Doc: — shared pure helpers (no I/O except where noted).
- Layer: utility
- Language: h
- Symbols:
  - `write_full` (function, line 15) `static inline int write_full(int fd, const void *buf, size_t n)`
  - `read_full` (function, line 26) `static inline int read_full(int fd, void *buf, size_t n)`
  - `mem_contains_ci` (function, line 43) `static inline int mem_contains_ci(const void *hay, size_t hlen, const char *needle)`
  - `utf8_seq_len` (function, line 57) `static inline size_t utf8_seq_len(unsigned char c)`
  - `fnv1a` (function, line 67) `static inline uint64_t fnv1a(const char *s, size_t n)`
  - `UTIL_H` (macro, line 5) `#define UTIL_H`
- Imported by: `src/browser.c`, `src/disk_store.c`, `src/dom.c`, `src/hostblock.c`, `src/html_parse.c`, `src/media_decoder.c`, `src/page_view.c`, `src/render_doc.c`, `src/renderer.c`, `src/tab.c`

## include/web_storage.h
- Doc: wst_new: web_storage — in-MEMORY localStorage for trusted hosts (owner decision: nothing...
- Layer: data_access
- Language: h
- Symbols:
  - `wst_db` (type_alias, line 21) `typedef struct wst_db wst_db;`
  - `wst_new` (function, line 25) `wst_db *wst_new(void);`
  - `wst_free` (function, line 28) `void wst_free(wst_db *db);`
  - `wst_encode` (function, line 33) `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len);`
  - `wst_decode_check` (function, line 37) `int wst_decode_check(const char *blob, size_t len);`
  - `wst_replace` (function, line 42) `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len);`
  - `full` (function, line 45) `* validating it in full (wst_decode_check). Returns 0, or -1 when invalid (fn is then * never called). The one...`
  - `wst_origin_bytes` (function, line 59) `size_t wst_origin_bytes(const wst_db *db, const char *origin);`
  - `FREEDOM_WEB_STORAGE_H` (macro, line 2) `#define FREEDOM_WEB_STORAGE_H`
  - `WST_MAX_ORIGINS` (macro, line 17) `#define WST_MAX_ORIGINS`
  - `WST_MAX_KEYS` (macro, line 18) `#define WST_MAX_KEYS`
  - `WST_QUOTA` (macro, line 19) `#define WST_QUOTA`
  - `WST_ORIGIN_MAX` (macro, line 20) `#define WST_ORIGIN_MAX`
- Imported by: `gui/browser_ui.c`, `src/js_dom.c`, `src/js_trusted.c`, `src/tab.c`, `src/web_storage.c`, `tests/test_js_dom.c`, `tests/test_tab.c`, `tests/test_web_storage.c`

## include/webcaps.h
- Doc: wc_caps: Full capability table for one page.
- Layer: utility
- Language: h
- Symbols:
  - `wc_caps` (struct, line 38)
  - `wc_input` (struct, line 57)
  - `js` (type_alias, line 38) `typedef struct wc_caps { /* leak-free (global): granted by user toggle or allow.conf presentation-trust. */ bool js;`
  - `js_mode` (type_alias, line 57) `typedef struct wc_input { jsp_mode js_mode;`
  - `FREEDOM_WEBCAPS_H` (macro, line 2) `#define FREEDOM_WEBCAPS_H`
- Depends on: `include/js_policy.h`, `include/render_policy.h`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/webcaps.c`, `tests/test_webcaps.c`

## include/webfont.h
- Doc: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- Layer: utility
- Language: h
- Symbols:
  - `wf_ref` (struct, line 31)
  - `wf_list` (struct, line 46)
  - `family` (type_alias, line 30) `typedef struct wf_ref { char family[WF_FAMILY_MAX];`
  - `wf_name_hash` (function, line 69) `static inline unsigned wf_name_hash(const char *s, size_t n)`
  - `here` (function, line 38) `* set with the decoded bytes owned here (freed by wf_list_free);`
  - `wf_scan` (function, line 52) `int wf_scan(const char *css, size_t len, wf_list *out);`
  - `wf_list_free` (function, line 53) `void wf_list_free(wf_list *l);`
  - `boundaries` (function, line 57) `* boundaries (scan_inline accumulation, loader collection). */ void wf_ref_move(wf_ref *dst, wf_ref *src);`
  - `wf_supported_format` (function, line 60) `int wf_supported_format(const char *fmt);`
  - `FREEDOM_WEBFONT_H` (macro, line 2) `#define FREEDOM_WEBFONT_H`
  - `WF_FAMILY_MAX` (macro, line 20) `#define WF_FAMILY_MAX`
  - `WF_URL_MAX` (macro, line 21) `#define WF_URL_MAX`
  - `WF_FORMAT_MAX` (macro, line 22) `#define WF_FORMAT_MAX`
  - `WF_MAX_REFS` (macro, line 23) `#define WF_MAX_REFS`
  - `WF_MAX_FACE_BYTES` (macro, line 24) `#define WF_MAX_FACE_BYTES`
  - `WF_MAX_TOTAL_BYTES` (macro, line 25) `#define WF_MAX_TOTAL_BYTES`
  - `WF_DATA_URL_MAX` (macro, line 29) `#define WF_DATA_URL_MAX`
- Imported by: `gui/browser_ui.c`, `src/css.c`, `src/freedom.c`, `src/text_shape.c`, `src/webfont.c`, `src/webfont_load.c`, `tests/test_css.c`, `tests/test_page_view.c`, `tests/test_text_shape.c`, `tests/test_webfont.c`, `tests/test_webfont_load.c`

## include/webfont_load.h
- Doc: wf_sheet: One collected stylesheet: text plus the URL it was fetched from (the * resolution base...
- Layer: utility
- Language: h
- Symbols:
  - `wf_sheet` (struct, line 24)
  - `free` (function, line 31) `* free()), *out_status the HTTP status. Nonzero on refusal/error (fail-closed: * the face is skipped, never the...`
  - `skipped` (function, line 47) `* URLs are skipped (no base). Returns faces registered (>= 0) otherwise. */ int wf_load_document(wf_fetch_fn fetch...`
  - `FREEDOM_WEBFONT_LOAD_H` (macro, line 2) `#define FREEDOM_WEBFONT_LOAD_H`
  - `WF_LOAD_TRIES_PER_KEY` (macro, line 52) `#define WF_LOAD_TRIES_PER_KEY`
  - `WF_LOAD_MAX_KEYS` (macro, line 53) `#define WF_LOAD_MAX_KEYS`
  - `WF_LOAD_MAX_FETCHES` (macro, line 54) `#define WF_LOAD_MAX_FETCHES`
- Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/webfont_load.c`, `tests/test_webfont_load.c`

## include/wl_display.h
- Doc: wd_pick: Choose the lowest-numbered "wayland-N" (N = digits only) from names[0..n).
- Layer: utility
- Language: h
- Symbols:
  - `pure` (function, line 3) `* wd_pick is pure (no I/O);`
  - `wd_pick` (function, line 16) `int wd_pick(const char *const *names, size_t n, char *out, size_t cap);`
  - `wd_resolve_env` (function, line 20) `int wd_resolve_env(void);`
  - `FREEDOM_WL_DISPLAY_H` (macro, line 6) `#define FREEDOM_WL_DISPLAY_H`
  - `WD_OK` (macro, line 10) `#define WD_OK`
  - `WD_NONE` (macro, line 11) `#define WD_NONE`
- Imported by: `src/freedom.c`, `src/wl_display.c`, `tests/test_wl_display.c`

## include/wl_guard.h
- Doc: wlg_start: wl_guard -- keeps the Wayland connection drained while the GUI thread is busy.
- Layer: utility
- Language: h
- Symbols:
  - `wl_display` (struct, line 8)
  - `wl_guard` (type_alias, line 21) `typedef struct wl_guard wl_guard;`
  - `wlg_start` (function, line 25) `wl_guard *wlg_start(struct wl_display *display);`
  - `wlg_stop` (function, line 28) `void wlg_stop(wl_guard *g);`
  - `FREEDOM_WL_GUARD_H` (macro, line 2) `#define FREEDOM_WL_GUARD_H`
- Imported by: `gui/browser_ui.c`, `src/wl_guard.c`, `tests/test_wl_guard.c`

## include/ws_hub.h
- Doc: wh_new: #define WH_MAX 8   /* == JD_WS_MAX: sockets per page /* Event kinds delivered to the...
- Layer: utility
- Language: h
- Symbols:
  - `wh_hub` (type_alias, line 30) `typedef struct wh_hub wh_hub;`
  - `wh_new` (function, line 34) `wh_hub *wh_new(void);`
  - `wh_free` (function, line 38) `void wh_free(wh_hub *h);`
  - `wh_notify_fd` (function, line 41) `int wh_notify_fd(const wh_hub *h);`
  - `wh_open_async` (function, line 46) `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg);`
  - `generation` (function, line 50) `* previous generation (before wh_close_all) are closed and dropped silently. */ void wh_on_notify(wh_hub *h...`
  - `wh_send` (function, line 54) `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary);`
  - `wh_close` (function, line 58) `void wh_close(wh_hub *h, int id);`
  - `wh_close_all` (function, line 61) `void wh_close_all(wh_hub *h);`
  - `wh_poll_fds` (function, line 65) `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap);`
  - `wh_on_readable` (function, line 70) `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx);`
  - `wh_count` (function, line 73) `size_t wh_count(const wh_hub *h);`
  - `FREEDOM_WS_HUB_H` (macro, line 2) `#define FREEDOM_WS_HUB_H`
  - `WH_MAX` (macro, line 21) `#define WH_MAX`
  - `WH_CLOSE_ABNORMAL` (macro, line 27) `#define WH_CLOSE_ABNORMAL`
- Depends on: `include/secure_fetch.h`
- Imported by: `gui/browser_ui.c`, `src/ws_hub.c`, `tests/test_ws_hub.c`

## include/zoom.h
- Doc: zm_clamp: stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser.
- Layer: utility
- Language: h
- Symbols:
  - `zm_clamp` (function, line 26) `int zm_clamp(int pct);`
  - `zm_zoom_in` (function, line 29) `int zm_zoom_in(int pct);`
  - `zm_zoom_out` (function, line 32) `int zm_zoom_out(int pct);`
  - `zm_reset` (function, line 35) `int zm_reset(void);`
  - `zm_scale` (function, line 38) `double zm_scale(int pct);`
  - `zm_apply` (function, line 42) `double zm_apply(double base_px, int pct);`
  - `FREEDOM_ZOOM_H` (macro, line 2) `#define FREEDOM_ZOOM_H`
  - `ZM_MIN_PCT` (macro, line 21) `#define ZM_MIN_PCT`
  - `ZM_MAX_PCT` (macro, line 22) `#define ZM_MAX_PCT`
  - `ZM_DEFAULT_PCT` (macro, line 23) `#define ZM_DEFAULT_PCT`
- Imported by: `gui/browser_ui.c`, `src/prefs.c`, `src/zoom.c`, `tests/test_prefs.c`, `tests/test_zoom.c`

