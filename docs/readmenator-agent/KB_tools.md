# Subsystem: tools

## tools/ffgeom.py
- Layer: utility
- Language: py
- Symbols:
  - `load_rows` (function, line 99) `def load_rows(path)`
  - `lum` (function, line 152) `def lum(p)`
  - `_word_reader` (function, line 156) `def _word_reader(path)`
  - `decode` (function, line 222) `def decode(path)`
  - `_append_probe` (function, line 237) `def _append_probe(src, script)`
  - `probe` (function, line 248) `def probe(page, selector, out_html)`
  - `height_probe` (function, line 262) `def height_probe(page, out_html)`
  - `height` (function, line 275) `def height(path)`
  - `main` (function, line 284) `def main(argv)`
  - `lum_at` (function, line 164) `def lum_at(x, y)`
  - `bit` (function, line 189) `def bit(grid_row, cell, origin)`
  - `word` (function, line 192) `def word(grid_row, origin)`

## tools/gen_psl.c
- Layer: utility
- Language: c
- Symbols:
  - `vec` (struct, line 21)
  - `vec_push` (function, line 26) `static void vec_push(vec *v, const char *s)`
  - `cmp_str` (function, line 37) `static int cmp_str(const void *a, const void *b)`
  - `sort_unique` (function, line 43) `static void sort_unique(vec *v)`
  - `ascii_lower` (function, line 55) `static void ascii_lower(char *s)`
  - `emit` (function, line 60) `static void emit(const char *name, vec *v)`
  - `main` (function, line 66) `int main(int argc, char **argv)`
  - `_POSIX_C_SOURCE` (macro, line 14)

## tools/mutate.py
- Layer: utility
- Language: py
- Symbols:
  - `line_sites` (function, line 41) `def line_sites(text)`
  - `mutate_line` (function, line 75) `def mutate_line(line, op)`
  - `find_modules` (function, line 107) `def find_modules(root)`
  - `run_make` (function, line 116) `def run_make(root, target)`
  - `run_bin` (function, line 122) `def run_bin(path)`
  - `main` (function, line 128) `def main(argv)`

## tools/pngdiff.c
- Layer: infrastructure
- Language: c
- Symbols:
  - `pd_profile` (struct, line 65)
  - `pd_reader` (struct, line 71)
  - `pd_reader_close` (function, line 78) `static void pd_reader_close(pd_reader *r)`
  - `pd_reader_open` (function, line 88) `static int pd_reader_open(pd_reader *r, const char *path)`
  - `png_set_background` (function, line 116) `png_set_background(r->png, &(png_color_16)`
  - `pd_lum` (function, line 140) `static double pd_lum(const png_byte *p)`
  - `pd_background` (function, line 147) `static int pd_background(const char *path, double *out_bg)`
  - `pd_profile_of` (function, line 175) `static int pd_profile_of(const char *path, pd_profile *out)`
  - `pd_mae` (function, line 226) `static double pd_mae(const double *a, const double *b, size_t n)`
  - `main` (function, line 232) `int main(int argc, char **argv)`
  - `PD_COLS` (macro, line 57)
  - `PD_ROWS` (macro, line 58)
  - `PD_INK_DELTA` (macro, line 63)

## tools/pngprof.py
- Layer: utility
- Language: py
- Symbols:
  - `load_rows` (function, line 41) `def load_rows(path)`
  - `lum` (function, line 95) `def lum(p)`
  - `render_glyph` (function, line 99) `def render_glyph(v)`
  - `main` (function, line 109) `def main(argv)`
