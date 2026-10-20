# Subsystem: include (page 5 of 5)
Previous: [KB_include_p4.md](KB_include_p4.md)

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

