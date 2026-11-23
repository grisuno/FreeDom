# API (page 14 of 14)
Previous: [API_p13.md](API_p13.md)

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

## tools/guiscroll.py
Depends on: `tools/guitime.py`
- `phase_ms` (function) `tools/guiscroll.py:38` `def phase_ms(line, phase)`
- `one_page` (function) `tools/guiscroll.py:48` `def one_page(binary, page, env, prof, tmp, notches, hover)`
- `main` (function) `tools/guiscroll.py:95` `def main()`
- `procs_display` (function) `tools/guiscroll.py:149` `def procs_display(procs)` -- The X display guitime.start_display put Xvfb on (it is the second process's argv).

## tools/guitime.py
Imported by: `tools/guiscroll.py`
- `start_display` (function) `tools/guitime.py:34` `def start_display(workdir)` -- Starts Xvfb and a nested weston; returns (env, processes) or None when unavailable.
- `one_run` (function) `tools/guitime.py:67` `def one_run(binary, page, env, hosts_dir, tmp)`
- `main` (function) `tools/guitime.py:96` `def main()`

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

