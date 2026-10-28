# API (page 12 of 12)
Previous: [API_p11.md](API_p11.md)

## src/web_storage.c
Depends on: `include/web_storage.h`
- `get_u32` (function) `src/web_storage.c:25` `static uint32_t get_u32(const unsigned char *p)`
- `utf8_ok` (function) `src/web_storage.c:32` `static int utf8_ok(const unsigned char *s, size_t n)` -- Well-formed UTF-8, allowing encoded surrogates (WTF-8): a JS string may hold a lone surrogate and rejecting it would...
- `key_cmp` (function) `src/web_storage.c:56` `static int key_cmp(const void *a, const void *b)`
- `check` (function) `src/web_storage.c:65` `static int check(const char *blob, size_t len, size_t *bytes_out)` -- return 1; } typedef struct key_ref { const unsigned char *p; uint32_t n; } key_ref; static int key_cmp(const void...
- `wst_decode_check` (function) `src/web_storage.c:101` `int wst_decode_check(const char *blob, size_t len)`
- `wst_new` (function) `src/web_storage.c:105` `wst_db *wst_new(void)`
- `wst_free` (function) `src/web_storage.c:109` `void wst_free(wst_db *db)`
- `find` (function) `src/web_storage.c:118` `static wst_origin *find(const wst_db *db, const char *origin)`
- `wst_encode` (function) `src/web_storage.c:125` `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len)`
- `wst_replace` (function) `src/web_storage.c:140` `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len)`
- `wst_origin_bytes` (function) `src/web_storage.c:175` `size_t wst_origin_bytes(const wst_db *db, const char *origin)`
- `wst_foreach` (function) `src/web_storage.c:181` `int wst_foreach(const char *blob, size_t len,
                void (*fn)(void *ctx, const char *k...`
- `put_u32` (function) `src/web_storage.c:201` `static void put_u32(char *b, uint32_t v)`
- `wst_pack` (function) `src/web_storage.c:206` `int wst_pack(const char *const *keys, const size_t *klens,
             const char *const *vals, ...`

## src/webcaps.c
Depends on: `include/webcaps.h`
- `wc_safe` (function) `src/webcaps.c:10` `wc_caps wc_safe(void)`
- `wc_derive` (function) `src/webcaps.c:15` `wc_caps wc_derive(wc_input in)`
- `wc_from_flags` (function) `src/webcaps.c:35` `wc_caps wc_from_flags(bool js, bool css, bool images)`
- `wc_render_caps` (function) `src/webcaps.c:46` `rdp_caps wc_render_caps(wc_caps c)`

## src/webfont.c
Depends on: `include/data_url.h`, `include/webfont.h`
- `candidates` (function) `src/webfont.c:7` `* understanding just far enough to find candidates (family + first url() per * src entry + weight/style descriptors);`
- `is_ws` (function) `src/webfont.c:19` `static int is_ws(char c)`
- `lower_ch` (function) `src/webfont.c:23` `static int lower_ch(char c)`
- `ci_eq_span` (function) `src/webfont.c:28` `static int ci_eq_span(const char *s, size_t n, const char *kw)` -- #include <stdint.h> #include <stdlib.h> #include <string.h> static int is_ws(char c) { return c == ' ' || c == '\t'...
- `wf_list_free` (function) `src/webfont.c:49` `void wf_list_free(wf_list *l)`
- `wf_ref_move` (function) `src/webfont.c:64` `void wf_ref_move(wf_ref *dst, wf_ref *src)`
- `wf_supported_format` (function) `src/webfont.c:74` `int wf_supported_format(const char *fmt)`
- `emit_slot` (function) `src/webfont.c:83` `static wf_ref *emit_slot(wf_list *out)` -- src->is_data = 0; } int wf_supported_format(const char *fmt) { if (fmt == NULL) return 0; if (fmt[0] == '\0') return...
- `emit_family_format` (function) `src/webfont.c:98` `static void emit_family_format(wf_ref *r, const char *family, const char *format)`
- `span_is_data` (function) `src/webfont.c:114` `static int span_is_data(const char *span, size_t slen)` -- if (fl >= WF_FAMILY_MAX) fl = WF_FAMILY_MAX - 1; memcpy(r->family, family, fl); r->family[fl] = '\0'; if (format !=...
- `emit` (function) `src/webfont.c:126` `static void emit(wf_list *out, const char *family,
                 const char *url, size_t ulen,...` -- /* True when span[0,slen) is a data: URL (case-insensitive scheme). static int span_is_data(const char *span, size_t...
- `emit_data` (function) `src/webfont.c:142` `static void emit_data(wf_list *out, const char *family,
                      const char *span, s...` -- Appends one data: ref, decoding the bytes NOW (a data: URL never fits url[]; * the bytes ride the ref instead).
- `scan_face_block` (function) `src/webfont.c:179` `static void scan_face_block(const char *s, size_t bstart, size_t bend,
                          ...` -- Parses one @font-face {...} body (bstart..bend, braces excluded) into the block's family/weight/style, then emits...
- `lower_ch` (function) `src/webfont.c:306` `&& lower_ch(s[k]) == 's' && k + 3 < bend
                && lower_ch(s[k + 1]) == 'r' && lower_ch...`
- `wf_scan` (function) `src/webfont.c:422` `int wf_scan(const char *css, size_t len, wf_list *out)`

## src/webfont_load.c
Depends on: `include/data_url.h`, `include/text_shape.h`, `include/url.h`, `include/webfont.h`, `include/webfont_load.h`
- `here` (function) `src/webfont_load.c:22` `* filtered here (a "" hint may still name one);`
- `ctype_ok` (function) `src/webfont_load.c:24` `static int ctype_ok(const char *ct)` -- Content types worth downloading as fonts.
- `key_find` (function) `src/webfont_load.c:66` `static int key_find(wf_key *keys, size_t nkeys, unsigned h, int b, int i)`
- `ref` (function) `src/webfont_load.c:167` `* their ref (the register call copies what it keeps). */ if (!is_data) free(fbytes);`
- `scan_inline` (function) `src/webfont_load.c:178` `static void scan_inline(const char *html, size_t len, const char *page_url,
                     ...` -- Finds inline <style>...</style> bodies in html (case-insensitive tags) and processes each sheet's refs against the...
- `wf_load_document` (function) `src/webfont_load.c:229` `int wf_load_document(wf_fetch_fn fetch, void *fctx, const char *page_url,
                     co...`

## src/wl_display.c
Depends on: `include/wl_display.h`
- `wd_index` (function) `src/wl_display.c:13` `static int wd_index(const char *name, unsigned long *idx)`
- `wd_pick` (function) `src/wl_display.c:27` `int wd_pick(const char *const *names, size_t n, char *out, size_t cap)`
- `wd_resolve_env` (function) `src/wl_display.c:42` `int wd_resolve_env(void)`

## src/wl_guard.c
Depends on: `include/wl_guard.h`
- `guard_main` (function) `src/wl_guard.c:26` `static void *guard_main(void *arg)`
- `wlg_start` (function) `src/wl_guard.c:45` `wl_guard *wlg_start(struct wl_display *display)`
- `wlg_stop` (function) `src/wl_guard.c:61` `void wlg_stop(wl_guard *g)`

## src/ws_hub.c
Depends on: `include/ws_hub.h`
- `dup_str` (function) `src/ws_hub.c:54` `static char *dup_str(const char *s)`
- `job_free` (function) `src/ws_hub.c:63` `static void job_free(wh_job *j)`
- `job_str` (function) `src/ws_hub.c:71` `static int job_str(wh_job *j, size_t slot, const char **field)` -- if (n == (size_t)-1) return NULL; char *d = (char *)malloc(n + 1); if (d != NULL) memcpy(d, s, n + 1); return d; }...
- `open_thread` (function) `src/ws_hub.c:79` `static void *open_thread(void *arg)`
- `conn_clear` (function) `src/ws_hub.c:98` `static void conn_clear(wh_conn *c)`
- `find_id` (function) `src/ws_hub.c:104` `static wh_conn *find_id(wh_hub *h, int id)`
- `find_token` (function) `src/ws_hub.c:110` `static wh_conn *find_token(wh_hub *h, uint64_t token)`
- `wh_new` (function) `src/ws_hub.c:116` `wh_hub *wh_new(void)`
- `wh_free` (function) `src/ws_hub.c:129` `void wh_free(wh_hub *h)`
- `wh_notify_fd` (function) `src/ws_hub.c:144` `int wh_notify_fd(const wh_hub *h)`
- `wh_open_async` (function) `src/ws_hub.c:148` `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg)`
- `wh_on_notify` (function) `src/ws_hub.c:192` `void wh_on_notify(wh_hub *h, wh_emit_fn emit, void *ctx)`
- `wh_send` (function) `src/ws_hub.c:221` `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary)`
- `wh_close` (function) `src/ws_hub.c:228` `void wh_close(wh_hub *h, int id)`
- `wh_close_all` (function) `src/ws_hub.c:234` `void wh_close_all(wh_hub *h)`
- `wh_poll_fds` (function) `src/ws_hub.c:240` `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap)`
- `fail_conn` (function) `src/ws_hub.c:258` `static void fail_conn(wh_conn *c, int id, wh_emit_fn emit, void *ctx)` -- const wh_conn *c = &h->c[i]; if (!c->used || c->pending || c->ws == NULL) continue; int fd = sf_ws_fd(c->ws); if (fd...
- `wh_on_readable` (function) `src/ws_hub.c:266` `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx)`
- `wh_count` (function) `src/ws_hub.c:314` `size_t wh_count(const wh_hub *h)`

## src/zoom.c
Depends on: `include/zoom.h`
- `zm_clamp` (function) `src/zoom.c:14` `int zm_clamp(int pct)`
- `zm_zoom_in` (function) `src/zoom.c:20` `int zm_zoom_in(int pct)`
- `zm_zoom_out` (function) `src/zoom.c:28` `int zm_zoom_out(int pct)`
- `zm_reset` (function) `src/zoom.c:36` `int zm_reset(void)`
- `zm_scale` (function) `src/zoom.c:40` `double zm_scale(int pct)`
- `zm_apply` (function) `src/zoom.c:44` `double zm_apply(double base_px, int pct)`

## tools/fbench.py
- `load_baseline` (function) `tools/fbench.py:53` `def load_baseline()`
- `load_current` (function) `tools/fbench.py:66` `def load_current()`
- `luma` (function) `tools/fbench.py:79` `def luma(img)`
- `bands` (function) `tools/fbench.py:83` `def bands(fd, ff, band)`
- `sbs` (function) `tools/fbench.py:95` `def sbs(name, start, nrows)`
- `publish_readme` (function) `tools/fbench.py:114` `def publish_readme(name, score)` -- Rewrite the README picture of `name` and the score printed beside its label.
- `run_timer` (function) `tools/fbench.py:140` `def run_timer(tool, pages, runs)` -- Runs a timing tool over the pages; returns ({name: median ms}, exit code).
- `load_timing_baseline` (function) `tools/fbench.py:158` `def load_timing_baseline()`
- `publish_timing` (function) `tools/fbench.py:171` `def publish_timing(rows)` -- Rewrites the README timing table (between the markers) for the README pages timed.
- `timing` (function) `tools/fbench.py:193` `def timing(names, runs, readme)`
- `main` (function) `tools/fbench.py:227` `def main()`

## tools/ffgeom.py
- `load_rows` (function) `tools/ffgeom.py:116` `def load_rows(path)`
- `lum` (function) `tools/ffgeom.py:169` `def lum(p)`
- `lum_at` (function) `tools/ffgeom.py:181` `def lum_at(x, y)`
- `bit` (function) `tools/ffgeom.py:206` `def bit(grid_row, cell, origin)`
- `word` (function) `tools/ffgeom.py:209` `def word(grid_row, origin)`
- `decode` (function) `tools/ffgeom.py:239` `def decode(path)`
- `probe` (function) `tools/ffgeom.py:265` `def probe(page, selector, out_html)`
- `height_probe` (function) `tools/ffgeom.py:279` `def height_probe(page, out_html)`
- `height` (function) `tools/ffgeom.py:292` `def height(path)` -- Decodes the scrollHeight carried by the #__ffh sentinel: the probe encodes one rect (its height), which decode()...
- `main` (function) `tools/ffgeom.py:301` `def main(argv)`

## tools/ffq.py
- `main` (function) `tools/ffq.py:22` `def main()`

## tools/ffshot.py
- `main` (function) `tools/ffshot.py:24` `def main()`

## tools/fftime.py
- `main` (function) `tools/fftime.py:38` `def main()`

## tools/gen_psl.c
- `vec_push` (function) `tools/gen_psl.c:27` `static void vec_push(vec *v, const char *s)`
- `cmp_str` (function) `tools/gen_psl.c:38` `static int cmp_str(const void *a, const void *b)`
- `sort_unique` (function) `tools/gen_psl.c:43` `static void sort_unique(vec *v)` -- v->cap = v->cap ? v->cap * 2 : 1024; v->items = (char **)realloc(v->items, v->cap * sizeof *v->items); if (v->items...
- `ascii_lower` (function) `tools/gen_psl.c:55` `static void ascii_lower(char *s)` -- /* Sorts then drops adjacent duplicates in place. static void sort_unique(vec *v) { qsort(v->items, v->len, sizeof...
- `emit` (function) `tools/gen_psl.c:61` `static void emit(const char *name, vec *v)`
- `main` (function) `tools/gen_psl.c:67` `int main(int argc, char **argv)`

## tools/guitime.py
- `start_display` (function) `tools/guitime.py:34` `def start_display(workdir)` -- Starts Xvfb and a nested weston; returns (env, processes) or None when unavailable.
- `one_run` (function) `tools/guitime.py:65` `def one_run(binary, page, env, hosts_dir, tmp)`
- `main` (function) `tools/guitime.py:92` `def main()`

## tools/mutate.py
- `line_sites` (function) `tools/mutate.py:41` `def line_sites(text)`
- `mutate_line` (function) `tools/mutate.py:75` `def mutate_line(line, op)`
- `find_modules` (function) `tools/mutate.py:107` `def find_modules(root)`
- `run_make` (function) `tools/mutate.py:116` `def run_make(root, target)`
- `run_bin` (function) `tools/mutate.py:125` `def run_bin(path)`
- `main` (function) `tools/mutate.py:137` `def main(argv)`

## tools/pngdiff.c
- `pd_reader_close` (function) `tools/pngdiff.c:79` `static void pd_reader_close(pd_reader *r)`
- `pd_reader_open` (function) `tools/pngdiff.c:88` `static int pd_reader_open(pd_reader *r, const char *path)` -- Opens `path` and normalises whatever colour type it carries into 8-bit RGB, so * the two passes below can assume...
- `png_set_background` (function) `tools/pngdiff.c:116` `png_set_background(r->png, &(png_color_16)` -- Compose against white rather than dropping alpha: a transparent region of a screenshot is what the viewer would see...
- `pd_lum` (function) `tools/pngdiff.c:141` `static double pd_lum(const png_byte *p)`
- `pd_background` (function) `tools/pngdiff.c:147` `static int pd_background(const char *path, double *out_bg)` -- Pass 1: the modal luminance IS the page background.
- `pd_profile_of` (function) `tools/pngdiff.c:175` `static int pd_profile_of(const char *path, pd_profile *out)` -- int b = (int)(pd_lum(&r.row[(size_t)x * 3u]) + 0.5); if (b < 0) b = 0; if (b > 255) b = 255; hist[b]++; } } int best...
- `pd_mae` (function) `tools/pngdiff.c:227` `static double pd_mae(const double *a, const double *b, size_t n)`
- `main` (function) `tools/pngdiff.c:233` `int main(int argc, char **argv)`

## tools/pngprof.py
- `load_rows` (function) `tools/pngprof.py:41` `def load_rows(path)`
- `lum` (function) `tools/pngprof.py:95` `def lum(p)`
- `render_glyph` (function) `tools/pngprof.py:99` `def render_glyph(v)`
- `main` (function) `tools/pngprof.py:109` `def main(argv)`

## tools/prune.py
- `main` (function) `tools/prune.py:21` `def main()`

## tools/snapshot.py
- `fetch` (function) `tools/snapshot.py:18` `def fetch(url)`
- `expand_imports` (function) `tools/snapshot.py:32` `def expand_imports(css, base, depth)` -- Replace each @import with the imported text (wrapped in @media when the import carries a media condition), resolved...
- `repl` (function) `tools/snapshot.py:35` `def repl(m)`
- `inline_css` (function) `tools/snapshot.py:49` `def inline_css(html, base)`
- `repl` (function) `tools/snapshot.py:50` `def repl(m)`
- `main` (function) `tools/snapshot.py:70` `def main()`

## tools/snapshot_age.py
- `main` (function) `tools/snapshot_age.py:16` `def main()`

