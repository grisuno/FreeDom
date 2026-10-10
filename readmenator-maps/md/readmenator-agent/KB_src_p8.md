# Subsystem: src (page 8 of 8)
Previous: [KB_src_p7.md](KB_src_p7.md)

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

