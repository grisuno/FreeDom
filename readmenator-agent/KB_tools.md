# Subsystem: tools

## tools/fbench.py
- Doc: fbench -- turn the PNG pairs `make parity` leaves behind into something you can act on.
- Layer: utility
- Language: py
- Symbols:
  - `load_baseline` (function, line 29) `def load_baseline()`
  - `load_current` (function, line 42) `def load_current()`
  - `luma` (function, line 55) `def luma(img)`
  - `bands` (function, line 59) `def bands(fd, ff, band)`
  - `sbs` (function, line 70) `def sbs(name, start, nrows)`
  - `main` (function, line 89) `def main()`

## tools/ffgeom.py
- Doc: ffgeom -- Firefox geometry as TEXT, no image reading.
- Layer: utility
- Language: py
- Symbols:
  - `load_rows` (function, line 116) `def load_rows(path)`
  - `lum` (function, line 169) `def lum(p)`
  - `_word_reader` (function, line 173) `def _word_reader(path)`
  - `decode` (function, line 239) `def decode(path)`
  - `_append_probe` (function, line 254) `def _append_probe(src, script)`
  - `probe` (function, line 265) `def probe(page, selector, out_html)`
  - `height_probe` (function, line 279) `def height_probe(page, out_html)`
  - `height` (function, line 292) `def height(path)`
  - `main` (function, line 301) `def main(argv)`
  - `lum_at` (function, line 181) `def lum_at(x, y)`
  - `bit` (function, line 206) `def bit(grid_row, cell, origin)`
  - `word` (function, line 209) `def word(grid_row, origin)`

## tools/ffq.py
- Doc: ffq -- ask Firefox what it computed, as TEXT.
- Layer: utility
- Language: py
- Symbols:
  - `main` (function, line 22) `def main()`

## tools/ffshot.py
- Doc: ffshot -- full-page Firefox screenshot at a FIXED viewport, for `make parity`/`make wpt`.
- Layer: utility
- Language: py
- Symbols:
  - `main` (function, line 24) `def main()`

## tools/gen_psl.c
- Doc: sort_unique: v->cap = v->cap ? v->cap * 2 : 1024; v->items = (char **)realloc(v->items, v->cap *...
- Layer: utility
- Language: c
- Symbols:
  - `vec` (struct, line 21)
  - `vec_push` (function, line 27) `static void vec_push(vec *v, const char *s)`
  - `cmp_str` (function, line 38) `static int cmp_str(const void *a, const void *b)`
  - `sort_unique` (function, line 43) `static void sort_unique(vec *v)`
  - `ascii_lower` (function, line 55) `static void ascii_lower(char *s)`
  - `emit` (function, line 61) `static void emit(const char *name, vec *v)`
  - `main` (function, line 67) `int main(int argc, char **argv)`
  - `_POSIX_C_SOURCE` (macro, line 15) `#define _POSIX_C_SOURCE`

## tools/mutate.py
- Doc: mutate -- compile-time mutation testing for the CMocka suites.
- Layer: utility
- Language: py
- Symbols:
  - `line_sites` (function, line 41) `def line_sites(text)`
  - `mutate_line` (function, line 75) `def mutate_line(line, op)`
  - `find_modules` (function, line 107) `def find_modules(root)`
  - `run_make` (function, line 116) `def run_make(root, target)`
  - `run_bin` (function, line 125) `def run_bin(path)`
  - `main` (function, line 137) `def main(argv)`

## tools/pngdiff.c
- Doc: pd_reader_open: Opens `path` and normalises whatever colour type it carries into 8-bit RGB, so *...
- Layer: utility
- Language: c
- Symbols:
  - `pd_profile` (struct, line 65)
  - `pd_reader` (struct, line 71)
  - `height` (type_alias, line 64) `typedef struct pd_profile { uint32_t width, height;`
  - `pd_reader_close` (function, line 79) `static void pd_reader_close(pd_reader *r)`
  - `pd_reader_open` (function, line 88) `static int pd_reader_open(pd_reader *r, const char *path)`
  - `png_set_background` (function, line 116) `png_set_background(r->png, &(png_color_16)`
  - `pd_lum` (function, line 141) `static double pd_lum(const png_byte *p)`
  - `pd_background` (function, line 147) `static int pd_background(const char *path, double *out_bg)`
  - `pd_profile_of` (function, line 175) `static int pd_profile_of(const char *path, pd_profile *out)`
  - `pd_mae` (function, line 227) `static double pd_mae(const double *a, const double *b, size_t n)`
  - `main` (function, line 233) `int main(int argc, char **argv)`
  - `PD_COLS` (macro, line 57) `#define PD_COLS`
  - `PD_ROWS` (macro, line 58) `#define PD_ROWS`
  - `PD_INK_DELTA` (macro, line 63) `#define PD_INK_DELTA`

## tools/pngprof.py
- Doc: pngprof -- structural ink-profile dump for page screenshots.
- Layer: utility
- Language: py
- Symbols:
  - `load_rows` (function, line 41) `def load_rows(path)`
  - `lum` (function, line 95) `def lum(p)`
  - `render_glyph` (function, line 99) `def render_glyph(v)`
  - `main` (function, line 109) `def main(argv)`

## tools/prune.py
- Doc: prune -- cut a corpus page down to ONE subtree, keeping its whole ancestor chain.
- Layer: utility
- Language: py
- Symbols:
  - `main` (function, line 21) `def main()`

## tools/snapshot.py
- Doc: Freeze a live page into one self-contained HTML file for `make parity`.
- Layer: utility
- Language: py
- Symbols:
  - `fetch` (function, line 17) `def fetch(url)`
  - `expand_imports` (function, line 31) `def expand_imports(css, base, depth)`
  - `inline_css` (function, line 48) `def inline_css(html, base)`
  - `main` (function, line 69) `def main()`
  - `repl` (function, line 34) `def repl(m)`
  - `repl` (function, line 49) `def repl(m)`
