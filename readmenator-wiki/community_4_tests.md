# tests

*Community 4 | 5 files | cohesion 0.67*

## Definition

This community groups 5 file(s) rooted at `tests` with dominant language c (cohesion 0.67). Central symbols: `ERR_FILE`, `FREEDOM_BIN`, `FREEDOM_IMAGE_DECODE_H`, `GIF_LZW_MAX_CODES`, `IMG_MAX_DIM`, `IMG_MAX_PIXELS`, `LLVMFuzzerTestOneInput`, `OUT_FILE`. Core file: `tests/test_freedom.c` (61 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_image_decode.c` | c | utility | 2 | no |
| `include/image_decode.h` | h | utility | 13 | no |
| `src/image_decode.c` | c | utility | 27 | no |
| `tests/test_freedom.c` | c | testing | 61 | no |
| `tests/test_image_decode.c` | c | testing | 37 | no |

## Key Symbols

- `poke_and_free` (function, `fuzz/fuzz_image_decode.c:21`) `static void poke_and_free(img_pixels *px)` - Touch every claimed pixel corner so the sanitizer flags an out-of-bounds extent, * then release. Saf
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_image_decode.c:32`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_IMAGE_DECODE_H` (macro, `include/image_decode.h:2`) `#define FREEDOM_IMAGE_DECODE_H`
- `guards` (function, `include/image_decode.h:25`) `* guards (in-memory source only, longjmp error manager so a bad stream never * c`
- `img_format` (enum, `include/image_decode.h:33`)
- `img_status` (enum, `include/image_decode.h:41`)
- `img_pixels` (struct, `include/image_decode.h:56`) - A decoded bitmap that owns its pixel buffer. The pixel format is Cairo's native premultiplied ARGB32
- `width` (type_alias, `include/image_decode.h:56`) `typedef struct img_pixels { uint32_t width;` - A decoded bitmap that owns its pixel buffer. The pixel format is Cairo's native premultiplied ARGB32
- `IMG_MAX_DIM` (macro, `include/image_decode.h:65`) `#define IMG_MAX_DIM`
- `IMG_MAX_PIXELS` (macro, `include/image_decode.h:66`) `#define IMG_MAX_PIXELS`
- `img_dimensions_ok` (function, `include/image_decode.h:78`) `int img_dimensions_ok(uint32_t w, uint32_t h);` - 1 iff (w,h) is non-zero and fits the anti-DoS caps (per-side and area, no * overflow of width*height
- `inputs` (function, `include/image_decode.h:81`) `* Degenerate inputs (<= 0) yield (0,0). Pure. */ void img_fit(uint32_t iw, uint3`
- `decode` (function, `include/image_decode.h:92`) `* the declared dimensions BEFORE the full decode (anti-bomb), decodes to RGB and`
- `img_pixels_free` (function, `include/image_decode.h:121`) `void img_pixels_free(img_pixels *p);` - Releases data and zeroes the struct. Idempotent; safe on NULL and on a zeroed * struct.
- `img_format_name` (function, `include/image_decode.h:124`) `const char *img_format_name(img_format f);` - Releases data and zeroes the struct. Idempotent; safe on NULL and on a zeroed * struct. void img_pix
- `exit` (function, `src/image_decode.c:6`) `* malformed stream fails closed instead of calling exit(). GIF uses an own pure-`
- `PNG_IHDR_MIN` (macro, `src/image_decode.c:34`) `#define PNG_IHDR_MIN`
- `read_be32` (function, `src/image_decode.c:52`) `static uint32_t read_be32(const uint8_t *p)`
- `img_png_dimensions` (function, `src/image_decode.c:57`) `img_status img_png_dimensions(const uint8_t *bytes, size_t len,`
- `img_dimensions_ok` (function, `src/image_decode.c:68`) `int img_dimensions_ok(uint32_t w, uint32_t h)`
- `img_fit` (function, `src/image_decode.c:76`) `void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,`
- `premultiply` (function, `src/image_decode.c:90`) `static void premultiply(uint8_t *data, size_t pixels)` - void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h, double *out_w, double *out_h) { i
- `img_decode_png` (function, `src/image_decode.c:102`) `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)`
- `jpeg_err_ctx` (struct, `src/image_decode.c:153`) - libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG * fails closed (IMG
- `jpeg_error_longjmp` (function, `src/image_decode.c:158`) `static void jpeg_error_longjmp(j_common_ptr cinfo)`
- `jpeg_silence` (function, `src/image_decode.c:164`) `static void jpeg_silence(j_common_ptr cinfo)` - libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG * fails closed (IMG
- `img_decode_jpeg` (function, `src/image_decode.c:166`) `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)`
- `GIF_LZW_MAX_CODES` (macro, `src/image_decode.c:253`) `#define GIF_LZW_MAX_CODES`
- `gif_reader` (struct, `src/image_decode.c:255`)
- `gr_u8` (function, `src/image_decode.c:260`) `static int gr_u8(gif_reader *r, uint8_t *out)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 4
- Cross-boundary resolved imports (EXTRACTED): 2

## Connections

- [EXTRACTED] depends_on community 2 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/image_decode.h.
- [INFERRED] shares_context community 0 <-> 4 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 0 (include) and community 4 (tests).

## Risks

- [dataflow DEAD_STORE] `src/image_decode.c:224` `img_decode_jpeg` `dst`: `dst` assigned at line 224 but never read afterwards.

## Open Questions

- Why do 5 file(s) lack file-level docs (e.g. `fuzz/fuzz_image_decode.c`)? What purpose do they serve?
- What would break if the most connected file in tests changed?
- Should tests be split, given cohesion 0.67?

## Sources

- `fuzz/fuzz_image_decode.c`
- `include/image_decode.h`
- `src/image_decode.c`
- `tests/test_freedom.c`
- `tests/test_image_decode.c`
