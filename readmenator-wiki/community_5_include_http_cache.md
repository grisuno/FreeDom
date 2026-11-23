# include: http_cache

*Community 5 | 28 files | cohesion 0.77*

## Definition

This community groups 28 file(s) rooted at `include` with dominant language c (cohesion 0.77). Central symbols: `FREEDOM_DISK_STORE_H`, `FREEDOM_HTTP_CACHE_H`, `FREEDOM_LAZY_LOAD_H`, `FREEDOM_LOCAL_STORE_H`, `FREEDOM_PQ_SEAL_H`, `FREEDOM_PREFS_H`, `FREEDOM_PROFILE_H`, `FREEDOM_UI_H`. Core file: `src/http_cache.c` (38 symbols).

## Files

### `include` (9 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/disk_store.h` | h | data_access | 3 | no |
| `include/http_cache.h` | h | presentation | 19 | no |
| `include/lazy_load.h` | h | utility | 1 | no |
| `include/local_store.h` | h | data_access | 11 | no |
| `include/pq_seal.h` | h | utility | 8 | no |
| `include/prefs.h` | h | utility | 18 | no |

### `src` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/disk_store.c` | c | data_access | 6 | no |
| `src/http_cache.c` | c | presentation | 38 | no |
| `src/local_store.c` | c | data_access | 31 | no |
| `src/pq_seal.c` | c | utility | 11 | no |
| `src/prefs.c` | c | utility | 26 | no |
| `src/profile.c` | c | utility | 9 | no |

### `tests` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_disk_store.c` | c | testing | 16 | no |
| `tests/test_http_cache.c` | c | testing | 17 | no |
| `tests/test_local_store.c` | c | testing | 18 | no |
| `tests/test_pq_seal.c` | c | testing | 7 | no |
| `tests/test_prefs.c` | c | testing | 15 | no |

### `gui` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `gui/freedom_view.c` | c | presentation | 2 | no |
| `gui/ui_render.c` | c | presentation | 29 | no |

### `fuzz` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_prefs.c` | c | utility | 1 | no |

*... and 8 more files in this community.*


## Key Symbols

- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_prefs.c:21`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `_POSIX_C_SOURCE` (macro, `gui/freedom_view.c:10`) `#define _POSIX_C_SOURCE`
- `main` (function, `gui/freedom_view.c:37`) `int main(int argc, char **argv)`
- `_GNU_SOURCE` (macro, `gui/ui_render.c:10`) `#define _GNU_SOURCE`
- `UI_FONT_SIZE` (macro, `gui/ui_render.c:28`) `#define UI_FONT_SIZE`
- `UI_MARGIN` (macro, `gui/ui_render.c:29`) `#define UI_MARGIN`
- `UI_TITLEBAR_H` (macro, `gui/ui_render.c:30`) `#define UI_TITLEBAR_H`
- `UI_BTN_W` (macro, `gui/ui_render.c:31`) `#define UI_BTN_W`
- `UI_BTN_LEFT` (macro, `gui/ui_render.c:32`) `#define UI_BTN_LEFT`
- `sanitize_utf8_inplace` (function, `gui/ui_render.c:39`) `static void sanitize_utf8_inplace(char *s)` - Rewrites s in place to well-formed UTF-8, replacing any byte that is not part of a valid sequence wi
- `ui_window` (struct, `gui/ui_render.c:67`)
- `button_rects` (function, `gui/ui_render.c:107`) `static void button_rects(const ui_window *w, double *min_x, double *max_x, doubl` - int    use_csd;    /* draw our own titlebar/controls (compositor has no SSD) int    maximized; doubl
- `buffer_release` (function, `gui/ui_render.c:115`) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
- `destroy_buffer` (function, `gui/ui_render.c:122`) `static void destroy_buffer(ui_window *w)`
- `ensure_buffer` (function, `gui/ui_render.c:128`) `static int ensure_buffer(ui_window *w)`
- `paint` (function, `gui/ui_render.c:159`) `static void paint(ui_window *w)`
- `redraw` (function, `gui/ui_render.c:245`) `static void redraw(ui_window *w)`
- `wm_base_ping` (function, `gui/ui_render.c:260`) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
- `xdg_surface_configure` (function, `gui/ui_render.c:266`) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t se`
- `toplevel_configure` (function, `gui/ui_render.c:274`) `static void toplevel_configure(void *data, struct xdg_toplevel *t,`
- `toplevel_close` (function, `gui/ui_render.c:283`) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
- `deco_configure` (function, `gui/ui_render.c:294`) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, ui` - The compositor tells us the actual decoration mode it granted. If it insists * on client-side, we dr
- `ptr_enter` (function, `gui/ui_render.c:305`) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,`
- `ptr_leave` (function, `gui/ui_render.c:312`) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surfa`
- `ptr_motion` (function, `gui/ui_render.c:315`) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x,`
- `ptr_button` (function, `gui/ui_render.c:322`) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t` - ui_window *w = (ui_window *)d; w->ptr_x = wl_fixed_to_double(x); w->ptr_y = wl_fixed_to_double(y); }
- `ptr_axis` (function, `gui/ui_render.c:344`) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,`
- `seat_caps` (function, `gui/ui_render.c:367`) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
- `seat_name` (function, `gui/ui_render.c:376`) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
- `registry_global` (function, `gui/ui_render.c:383`) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 34
- Cross-boundary resolved imports (EXTRACTED): 10

## Connections

- [EXTRACTED] depends_on community 1 <-> 5 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefs.h.
- [EXTRACTED] depends_on community 5 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/freedom_view.c imports include/html_parse.h.
- [EXTRACTED] depends_on community 5 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/ui_render.c imports include/freedom_config.h.
- [EXTRACTED] depends_on community 6 <-> 5 (strength 0.9): Extracted import edge crosses communities: include/cached_fetch.h imports include/http_cache.h.

## Risks

- [layer strict] `include/http_cache.h` (presentation) -> `include/local_store.h` (data_access)
- [layer strict] `src/http_cache.c` (presentation) -> `include/disk_store.h` (data_access)
- [layer strict] `tests/test_http_cache.c` (testing) -> `include/http_cache.h` (presentation)
- [layer strict] `tests/test_ui.c` (testing) -> `include/ui.h` (presentation)

## Open Questions

- Why do 28 file(s) lack file-level docs (e.g. `fuzz/fuzz_prefs.c`)? What purpose do they serve?
- What would break if the most connected file in include: http_cache changed?
- Should include: http_cache be split, given cohesion 0.77?

## Sources

- `fuzz/fuzz_prefs.c`
- `gui/freedom_view.c`
- `gui/ui_render.c`
- `include/disk_store.h`
- `include/http_cache.h`
- `include/lazy_load.h`
- `include/local_store.h`
- `include/pq_seal.h`
- `include/prefs.h`
- `include/profile.h`
- `include/ui.h`
- `include/zoom.h`
- `src/disk_store.c`
- `src/http_cache.c`
- `src/local_store.c`
- `src/pq_seal.c`
- `src/prefs.c`
- `src/profile.c`
- `src/ui_layout.c`
- `src/zoom.c`
- *... and 8 more*
