# Symbols (page 16 of 16)
Previous: [SYMBOLS_p15.md](SYMBOLS_p15.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `stub` | struct | `tests/test_webfont_load.c:30` | `` |
| `stub_fetch` | function | `tests/test_webfont_load.c:38` | `static int stub_fetch(void *ctx, const char *url,                       int *out_status, char **o...` |
| `teardown` | function | `tests/test_webfont_load.c:318` | `static int teardown(void **state)` |
| `test_b64` | function | `tests/test_webfont_load.c:92` | `static char *test_b64(const unsigned char *in, size_t n)` |
| `test_data_url_bad_bytes_skipped` | function | `tests/test_webfont_load.c:240` | `static void test_data_url_bad_bytes_skipped(void **state)` |
| `test_data_url_registers` | function | `tests/test_webfont_load.c:255` | `static void test_data_url_registers(void **state)` |
| `test_extern_sheet_relative_url` | function | `tests/test_webfont_load.c:217` | `static void test_extern_sheet_relative_url(void **state)` |
| `test_fallback_second_url` | function | `tests/test_webfont_load.c:170` | `static void test_fallback_second_url(void **state)` |
| `test_first_wins` | function | `tests/test_webfont_load.c:194` | `static void test_first_wins(void **state)` |
| `test_https_stub_registers` | function | `tests/test_webfont_load.c:126` | `static void test_https_stub_registers(void **state)` |
| `test_null_args` | function | `tests/test_webfont_load.c:113` | `static void test_null_args(void **state)` |
| `test_null_page_data_only` | function | `tests/test_webfont_load.c:288` | `static void test_null_page_data_only(void **state)` |
| `test_woff2_never_fetched` | function | `tests/test_webfont_load.c:152` | `static void test_woff2_never_fetched(void **state)` |
| `main` | function | `tests/test_wl_display.c:43` | `int main(void)` |
| `test_ignores_lock_and_garbage` | function | `tests/test_wl_display.c:19` | `static void test_ignores_lock_and_garbage(void **state)` |
| `test_null_entry` | function | `tests/test_wl_display.c:35` | `static void test_null_entry(void **state)` |
| `test_picks_lowest` | function | `tests/test_wl_display.c:11` | `static void test_picks_lowest(void **state)` |
| `test_small_cap_fails_closed` | function | `tests/test_wl_display.c:27` | `static void test_small_cap_fails_closed(void **state)` |
| `_DEFAULT_SOURCE` | macro | `tests/test_wl_guard.c:1` | `#define _DEFAULT_SOURCE` |
| `main` | function | `tests/test_wl_guard.c:55` | `int main(void)` |
| `ms_since` | function | `tests/test_wl_guard.c:13` | `static long ms_since(const struct timespec *a)` |
| `test_guard_starts_idles_and_stops_promptly` | function | `tests/test_wl_guard.c:21` | `static void test_guard_starts_idles_and_stops_promptly(void **state)` |
| `test_guard_survives_peer_hangup` | function | `tests/test_wl_guard.c:41` | `static void test_guard_survives_peer_hangup(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_ws_hub.c:7` | `#define _POSIX_C_SOURCE` |
| `emit` | function | `tests/test_ws_hub.c:21` | `static void emit(void *ctx, int id, int kind, int code, const char *data, size_t len)` |
| `main` | function | `tests/test_ws_hub.c:142` | `int main(void)` |
| `n` | type_alias | `tests/test_ws_hub.c:18` | `typedef struct rec { int n;` |
| `rec` | struct | `tests/test_ws_hub.c:19` | `` |
| `test_close_all_drops_late_results` | function | `tests/test_ws_hub.c:85` | `static void test_close_all_drops_late_results(void **state)` |
| `test_close_cancels_pending_open` | function | `tests/test_ws_hub.c:102` | `static void test_close_cancels_pending_open(void **state)` |
| `test_duplicate_and_capacity` | function | `tests/test_ws_hub.c:64` | `static void test_duplicate_and_capacity(void **state)` |
| `test_failed_open_reports_error_then_close` | function | `tests/test_ws_hub.c:47` | `static void test_failed_open_reports_error_then_close(void **state)` |
| `test_free_with_pending_open` | function | `tests/test_ws_hub.c:132` | `static void test_free_with_pending_open(void **state)` |
| `test_new_free` | function | `tests/test_ws_hub.c:34` | `static void test_new_free(void **state)` |
| `test_send_unknown_and_readable_unknown` | function | `tests/test_ws_hub.c:115` | `static void test_send_unknown_and_readable_unknown(void **state)` |
| `wait_notify` | function | `tests/test_ws_hub.c:28` | `static void wait_notify(wh_hub *h, rec *r)` |
| `main` | function | `tests/test_zoom.c:112` | `int main(void)` |
| `test_apply_scales_and_floors` | function | `tests/test_zoom.c:100` | `static void test_apply_scales_and_floors(void **state)` |
| `test_clamp_bounds` | function | `tests/test_zoom.c:17` | `static void test_clamp_bounds(void **state)` |
| `test_ends_are_idempotent` | function | `tests/test_zoom.c:59` | `static void test_ends_are_idempotent(void **state)` |
| `test_repeated_in_reaches_max` | function | `tests/test_zoom.c:67` | `static void test_repeated_in_reaches_max(void **state)` |
| `test_repeated_out_reaches_min` | function | `tests/test_zoom.c:79` | `static void test_repeated_out_reaches_min(void **state)` |
| `test_reset_is_default` | function | `tests/test_zoom.c:27` | `static void test_reset_is_default(void **state)` |
| `test_scale_factor` | function | `tests/test_zoom.c:91` | `static void test_scale_factor(void **state)` |
| `test_step_snaps_off_ladder` | function | `tests/test_zoom.c:49` | `static void test_step_snaps_off_ladder(void **state)` |
| `test_zoom_in_steps_ladder` | function | `tests/test_zoom.c:33` | `static void test_zoom_in_steps_ladder(void **state)` |
| `test_zoom_out_steps_ladder` | function | `tests/test_zoom.c:41` | `static void test_zoom_out_steps_ladder(void **state)` |
| `bands` | function | `tools/fbench.py:83` | `def bands(fd, ff, band)` |
| `load_baseline` | function | `tools/fbench.py:53` | `def load_baseline()` |
| `load_current` | function | `tools/fbench.py:66` | `def load_current()` |
| `load_timing_baseline` | function | `tools/fbench.py:158` | `def load_timing_baseline()` |
| `luma` | function | `tools/fbench.py:79` | `def luma(img)` |
| `main` | function | `tools/fbench.py:227` | `def main()` |
| `publish_readme` | function | `tools/fbench.py:114` | `def publish_readme(name, score)` |
| `publish_timing` | function | `tools/fbench.py:171` | `def publish_timing(rows)` |
| `run_timer` | function | `tools/fbench.py:140` | `def run_timer(tool, pages, runs)` |
| `sbs` | function | `tools/fbench.py:95` | `def sbs(name, start, nrows)` |
| `timing` | function | `tools/fbench.py:193` | `def timing(names, runs, readme)` |
| `_append_probe` | function | `tools/ffgeom.py:254` | `def _append_probe(src, script)` |
| `_word_reader` | function | `tools/ffgeom.py:173` | `def _word_reader(path)` |
| `bit` | function | `tools/ffgeom.py:206` | `def bit(grid_row, cell, origin)` |
| `decode` | function | `tools/ffgeom.py:239` | `def decode(path)` |
| `height` | function | `tools/ffgeom.py:292` | `def height(path)` |
| `height_probe` | function | `tools/ffgeom.py:279` | `def height_probe(page, out_html)` |
| `load_rows` | function | `tools/ffgeom.py:116` | `def load_rows(path)` |
| `lum` | function | `tools/ffgeom.py:169` | `def lum(p)` |
| `lum_at` | function | `tools/ffgeom.py:181` | `def lum_at(x, y)` |
| `main` | function | `tools/ffgeom.py:301` | `def main(argv)` |
| `probe` | function | `tools/ffgeom.py:265` | `def probe(page, selector, out_html)` |
| `word` | function | `tools/ffgeom.py:209` | `def word(grid_row, origin)` |
| `main` | function | `tools/ffq.py:22` | `def main()` |
| `main` | function | `tools/ffshot.py:24` | `def main()` |
| `main` | function | `tools/fftime.py:38` | `def main()` |
| `_POSIX_C_SOURCE` | macro | `tools/gen_psl.c:15` | `#define _POSIX_C_SOURCE` |
| `ascii_lower` | function | `tools/gen_psl.c:55` | `static void ascii_lower(char *s)` |
| `cmp_str` | function | `tools/gen_psl.c:38` | `static int cmp_str(const void *a, const void *b)` |
| `emit` | function | `tools/gen_psl.c:61` | `static void emit(const char *name, vec *v)` |
| `main` | function | `tools/gen_psl.c:67` | `int main(int argc, char **argv)` |
| `sort_unique` | function | `tools/gen_psl.c:43` | `static void sort_unique(vec *v)` |
| `vec` | struct | `tools/gen_psl.c:21` | `` |
| `vec_push` | function | `tools/gen_psl.c:27` | `static void vec_push(vec *v, const char *s)` |
| `main` | function | `tools/guitime.py:92` | `def main()` |
| `one_run` | function | `tools/guitime.py:65` | `def one_run(binary, page, env, hosts_dir, tmp)` |
| `start_display` | function | `tools/guitime.py:34` | `def start_display(workdir)` |
| `find_modules` | function | `tools/mutate.py:107` | `def find_modules(root)` |
| `line_sites` | function | `tools/mutate.py:41` | `def line_sites(text)` |
| `main` | function | `tools/mutate.py:137` | `def main(argv)` |
| `mutate_line` | function | `tools/mutate.py:75` | `def mutate_line(line, op)` |
| `run_bin` | function | `tools/mutate.py:125` | `def run_bin(path)` |
| `run_make` | function | `tools/mutate.py:116` | `def run_make(root, target)` |
| `PD_COLS` | macro | `tools/pngdiff.c:57` | `#define PD_COLS` |
| `PD_INK_DELTA` | macro | `tools/pngdiff.c:63` | `#define PD_INK_DELTA` |
| `PD_ROWS` | macro | `tools/pngdiff.c:58` | `#define PD_ROWS` |
| `height` | type_alias | `tools/pngdiff.c:64` | `typedef struct pd_profile { uint32_t width, height;` |
| `main` | function | `tools/pngdiff.c:233` | `int main(int argc, char **argv)` |
| `pd_background` | function | `tools/pngdiff.c:147` | `static int pd_background(const char *path, double *out_bg)` |
| `pd_lum` | function | `tools/pngdiff.c:141` | `static double pd_lum(const png_byte *p)` |
| `pd_mae` | function | `tools/pngdiff.c:227` | `static double pd_mae(const double *a, const double *b, size_t n)` |
| `pd_profile` | struct | `tools/pngdiff.c:65` | `` |
| `pd_profile_of` | function | `tools/pngdiff.c:175` | `static int pd_profile_of(const char *path, pd_profile *out)` |
| `pd_reader` | struct | `tools/pngdiff.c:71` | `` |
| `pd_reader_close` | function | `tools/pngdiff.c:79` | `static void pd_reader_close(pd_reader *r)` |
| `pd_reader_open` | function | `tools/pngdiff.c:88` | `static int pd_reader_open(pd_reader *r, const char *path)` |
| `png_set_background` | function | `tools/pngdiff.c:116` | `png_set_background(r->png, &(png_color_16)` |
| `load_rows` | function | `tools/pngprof.py:41` | `def load_rows(path)` |
| `lum` | function | `tools/pngprof.py:95` | `def lum(p)` |
| `main` | function | `tools/pngprof.py:109` | `def main(argv)` |
| `render_glyph` | function | `tools/pngprof.py:99` | `def render_glyph(v)` |
| `main` | function | `tools/prune.py:21` | `def main()` |
| `expand_imports` | function | `tools/snapshot.py:32` | `def expand_imports(css, base, depth)` |
| `fetch` | function | `tools/snapshot.py:18` | `def fetch(url)` |
| `inline_css` | function | `tools/snapshot.py:49` | `def inline_css(html, base)` |
| `main` | function | `tools/snapshot.py:70` | `def main()` |
| `repl` | function | `tools/snapshot.py:35` | `def repl(m)` |
| `repl` | function | `tools/snapshot.py:50` | `def repl(m)` |
| `main` | function | `tools/snapshot_age.py:16` | `def main()` |

