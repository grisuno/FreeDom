# Subsystem: src (page 10 of 10)
Previous: [KB_src_p9.md](KB_src_p9.md)

## src/webfont_load.c
- Doc: wf_key: size_t k = 0; while (PREF[i][k] != '\0') ++k; size_t j = 0; for (; j < k; ++j) { char a...
- Layer: utility
- Language: c
- Symbols:
  - `wf_key` (struct, line 46)
  - `wf_cursor` (struct, line 56)
  - `hash` (type_alias, line 46) `typedef struct wf_key { unsigned hash;`
  - `fetch` (type_alias, line 56) `typedef struct wf_cursor { wf_fetch_fn fetch;`
  - `ctype_ok` (function, line 24) `static int ctype_ok(const char *ct)`
  - `key_find` (function, line 66) `static int key_find(wf_key *keys, size_t nkeys, unsigned h, int b, int i)`
  - `scan_inline` (function, line 178) `static void scan_inline(const char *html, size_t len, const char *page_url,
                     ...`
  - `wf_load_document` (function, line 229) `int wf_load_document(wf_fetch_fn fetch, void *fctx, const char *page_url,
                     co...`
  - `here` (function, line 22) `* filtered here (a "" hint may still name one);`
  - `ref` (function, line 167) `* their ref (the register call copies what it keeps). */ if (!is_data) free(fbytes);`
  - `WF_DATA_URL_MAX` (macro, line 91) `#define WF_DATA_URL_MAX`
- Depends on: `include/data_url.h`, `include/text_shape.h`, `include/url.h`, `include/webfont.h`, `include/webfont_load.h`

## src/wl_display.c
- Layer: utility
- Language: c
- Symbols:
  - `wd_index` (function, line 13) `static int wd_index(const char *name, unsigned long *idx)`
  - `wd_pick` (function, line 27) `int wd_pick(const char *const *names, size_t n, char *out, size_t cap)`
  - `wd_resolve_env` (function, line 42) `int wd_resolve_env(void)`
  - `_POSIX_C_SOURCE` (macro, line 1) `#define _POSIX_C_SOURCE`
  - `WD_PREFIX` (macro, line 8) `#define WD_PREFIX`
  - `WD_PREFIX_LEN` (macro, line 9) `#define WD_PREFIX_LEN`
  - `WD_MAX_NAMES` (macro, line 10) `#define WD_MAX_NAMES`
  - `WD_NAME_MAX` (macro, line 11) `#define WD_NAME_MAX`
- Depends on: `include/wl_display.h`

## src/wl_guard.c
- Layer: utility
- Language: c
- Symbols:
  - `wl_guard` (struct, line 19)
  - `guard_main` (function, line 26) `static void *guard_main(void *arg)`
  - `wlg_start` (function, line 45) `wl_guard *wlg_start(struct wl_display *display)`
  - `wlg_stop` (function, line 61) `void wlg_stop(wl_guard *g)`
  - `_DEFAULT_SOURCE` (macro, line 5) `#define _DEFAULT_SOURCE`
  - `WLG_POLL_MS` (macro, line 17) `#define WLG_POLL_MS`
- Depends on: `include/wl_guard.h`

## src/ws_hub.c
- Doc: wh_job: One open, owned by its thread until handed over through the pipe.
- Layer: utility
- Language: c
- Symbols:
  - `wh_conn` (struct, line 24)
  - `wh_hub` (struct, line 35)
  - `wh_job` (struct, line 43)
  - `used` (type_alias, line 23) `typedef struct wh_conn { int used;`
  - `wfd` (type_alias, line 43) `typedef struct wh_job { int wfd;`
  - `dup_str` (function, line 54) `static char *dup_str(const char *s)`
  - `job_free` (function, line 63) `static void job_free(wh_job *j)`
  - `job_str` (function, line 71) `static int job_str(wh_job *j, size_t slot, const char **field)`
  - `open_thread` (function, line 79) `static void *open_thread(void *arg)`
  - `conn_clear` (function, line 98) `static void conn_clear(wh_conn *c)`
  - `find_id` (function, line 104) `static wh_conn *find_id(wh_hub *h, int id)`
  - `find_token` (function, line 110) `static wh_conn *find_token(wh_hub *h, uint64_t token)`
  - `wh_new` (function, line 116) `wh_hub *wh_new(void)`
  - `wh_free` (function, line 129) `void wh_free(wh_hub *h)`
  - `wh_notify_fd` (function, line 144) `int wh_notify_fd(const wh_hub *h)`
  - `wh_open_async` (function, line 148) `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg)`
  - `wh_on_notify` (function, line 192) `void wh_on_notify(wh_hub *h, wh_emit_fn emit, void *ctx)`
  - `wh_send` (function, line 221) `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary)`
  - `wh_close` (function, line 228) `void wh_close(wh_hub *h, int id)`
  - `wh_close_all` (function, line 234) `void wh_close_all(wh_hub *h)`
  - `wh_poll_fds` (function, line 240) `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap)`
  - `fail_conn` (function, line 258) `static void fail_conn(wh_conn *c, int id, wh_emit_fn emit, void *ctx)`
  - `wh_on_readable` (function, line 266) `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx)`
  - `wh_count` (function, line 314) `size_t wh_count(const wh_hub *h)`
  - `_POSIX_C_SOURCE` (macro, line 6) `#define _POSIX_C_SOURCE`
  - `WH_READS_PER_PUMP` (macro, line 21) `#define WH_READS_PER_PUMP`
  - `WH_RECV_CHUNK` (macro, line 22) `#define WH_RECV_CHUNK`
- Depends on: `include/ws_hub.h`

## src/zoom.c
- Layer: utility
- Language: c
- Symbols:
  - `zm_clamp` (function, line 14) `int zm_clamp(int pct)`
  - `zm_zoom_in` (function, line 20) `int zm_zoom_in(int pct)`
  - `zm_zoom_out` (function, line 28) `int zm_zoom_out(int pct)`
  - `zm_reset` (function, line 36) `int zm_reset(void)`
  - `zm_scale` (function, line 40) `double zm_scale(int pct)`
  - `zm_apply` (function, line 44) `double zm_apply(double base_px, int pct)`
  - `ZM_LADDER_N` (macro, line 12) `#define ZM_LADDER_N`
- Depends on: `include/zoom.h`

