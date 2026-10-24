# Subsystem: include (page 5 of 5)
Previous: [KB_include_p4.md](KB_include_p4.md)

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

