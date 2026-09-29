# include

*Community 8 | 4 files | cohesion 0.50*

## Definition

This community groups 4 file(s) rooted at `include` with dominant language c (cohesion 0.50). Central symbols: `FREEDOM_TEXT_SHAPE_H`, `FZ_CAP`, `LLVMFuzzerTestOneInput`, `TSH_CACHE_SLOTS`, `TSH_MAX_FONT_BYTES`, `TSH_MAX_GLYPHS`, `TSH_MAX_TEXT`, `_POSIX_C_SOURCE`. Core file: `src/text_shape.c` (15 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_text_shape.c` | c | utility | 2 | no |
| `include/text_shape.h` | h | utility | 11 | no |
| `src/text_shape.c` | c | utility | 15 | no |
| `tests/test_text_shape.c` | c | testing | 9 | no |

## Key Symbols

- `FZ_CAP` (macro, `fuzz/fuzz_text_shape.c:23`) `#define FZ_CAP`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_text_shape.c:25`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `content` (function, `include/text_shape.h:11`) `* TEXT is hostile remote content (sanitised UTF-8) and is fuzzed (make fuzz-tsh)`
- `FREEDOM_TEXT_SHAPE_H` (macro, `include/text_shape.h:19`) `#define FREEDOM_TEXT_SHAPE_H`
- `tsh_font` (struct, `include/text_shape.h:30`) - Font selector: a css_font_family bucket (CSS_FF_*) plus weight/slant flags. * The engine matches the
- `family` (type_alias, `include/text_shape.h:30`) `typedef struct tsh_font { int family;` - Font selector: a css_font_family bucket (CSS_FF_*) plus weight/slant flags. * The engine matches the
- `TSH_MAX_GLYPHS` (macro, `include/text_shape.h:36`) `#define TSH_MAX_GLYPHS`
- `TSH_MAX_TEXT` (macro, `include/text_shape.h:37`) `#define TSH_MAX_TEXT`
- `tsh_status` (enum, `include/text_shape.h:39`)
- `tsh_ready` (function, `include/text_shape.h:48`) `int tsh_ready(void);` - 1 once a fallback (sans) font resolves; lazily initialises on first call. * 0 means no font backend:
- `origin` (function, `include/text_shape.h:51`) `* glyphs are written with positions relative to origin (0,0) on the baseline, *`
- `tsh_measure` (function, `include/text_shape.h:60`) `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len);` - Total advance (px) of [text,len). Returns < 0.0 on any failure so the caller * can fall back to the
- `tsh_shutdown` (function, `include/text_shape.h:69`) `void tsh_shutdown(void);` - Shapes and paints [text,len) at (x, baseline) on cr (selects the FT font face matching f+px, uses th
- `_POSIX_C_SOURCE` (macro, `src/text_shape.c:12`) `#define _POSIX_C_SOURCE`
- `TSH_MAX_FONT_BYTES` (macro, `src/text_shape.c:28`) `#define TSH_MAX_FONT_BYTES`
- `TSH_CACHE_SLOTS` (macro, `src/text_shape.c:32`) `#define TSH_CACHE_SLOTS`
- `loaded` (type_alias, `src/text_shape.c:33`) `typedef struct tsh_entry { int loaded;` - One resolved face per (family, bold, italic). family is a CSS_FF_* bucket * (0..CSS_FF_FANTASY); idx
- `tsh_entry` (struct, `src/text_shape.c:34`)
- `generic_name` (function, `src/text_shape.c:54`) `static const char *generic_name(int family)`
- `backend_init` (function, `src/text_shape.c:64`) `static int backend_init(void)`
- `read_font_file` (function, `src/text_shape.c:81`) `static unsigned char *read_font_file(const char *path, long *out_n)`
- `load_entry` (function, `src/text_shape.c:97`) `static int load_entry(tsh_entry *e, int family, int bold, int italic)`
- `get_entry` (function, `src/text_shape.c:152`) `static tsh_entry *get_entry(int family, int bold, int italic)`
- `tsh_ready` (function, `src/text_shape.c:164`) `int tsh_ready(void)`
- `tsh_shape` (function, `src/text_shape.c:169`) `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,`
- `tsh_measure` (function, `src/text_shape.c:214`) `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)`
- `tsh_draw` (function, `src/text_shape.c:221`) `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,`
- `tsh_shutdown` (function, `src/text_shape.c:243`) `void tsh_shutdown(void)`
- `test_null_and_bad_inputs` (function, `tests/test_text_shape.c:27`) `static void test_null_and_bad_inputs(void **state)`
- `test_empty_slice_is_ok` (function, `tests/test_text_shape.c:57`) `static void test_empty_slice_is_ok(void **state)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 3
- Cross-boundary resolved imports (EXTRACTED): 3

## Connections

- [EXTRACTED] depends_on community 2 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/text_shape.h.
- [EXTRACTED] depends_on community 8 <-> 0 (strength 0.9): Extracted import edge crosses communities: src/text_shape.c imports include/css.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 4 file(s) lack file-level docs (e.g. `fuzz/fuzz_text_shape.c`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.50?

## Sources

- `fuzz/fuzz_text_shape.c`
- `include/text_shape.h`
- `src/text_shape.c`
- `tests/test_text_shape.c`
