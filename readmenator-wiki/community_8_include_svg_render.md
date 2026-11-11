# include: svg_render

*Community 8 | 12 files | cohesion 0.57*

## Definition

This community groups 12 file(s) rooted at `include` with dominant language c (cohesion 0.57). Central symbols: `ERR_FILE`, `FREEDOM_BIN`, `FREEDOM_IMAGE_DECODE_H`, `FREEDOM_SVG_PAINT_H`, `FREEDOM_SVG_RASTER_H`, `FREEDOM_SVG_RENDER_H`, `GIF_LZW_MAX_CODES`, `IMG_MAX_DIM`. Core file: `tests/test_freedom.c` (115 symbols). Documented purpose: svg_paint — Cairo back end for the shapes svg_render extracted..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/image_decode.h` | h | utility | 14 | no |
| `include/svg_paint.h` | h | utility | 3 | no |
| `include/svg_raster.h` | h | utility | 5 | no |
| `include/svg_render.h` | h | presentation | 19 | no |
| `src/image_decode.c` | c | utility | 27 | no |
| `src/svg_paint.c` | c | utility | 6 | yes |
| `src/svg_raster.c` | c | utility | 4 | yes |
| `src/svg_render.c` | c | presentation | 34 | yes |
| `tests/test_freedom.c` | c | testing | 115 | no |
| `tests/test_image_decode.c` | c | testing | 37 | no |
| `tests/test_svg_raster.c` | c | testing | 10 | yes |
| `tests/test_svg_render.c` | c | testing | 17 | yes |

## Key Symbols

- `FREEDOM_IMAGE_DECODE_H` (macro, `include/image_decode.h:2`) `#define FREEDOM_IMAGE_DECODE_H`
- `guards` (function, `include/image_decode.h:25`) `* guards (in-memory source only, longjmp error manager so a bad stream never * c`
- `img_format` (enum, `include/image_decode.h:33`)
- `img_status` (enum, `include/image_decode.h:41`)
- `img_pixels` (struct, `include/image_decode.h:56`) - A decoded bitmap that owns its pixel buffer. The pixel format is Cairo's native premultiplied ARGB32
- `width` (type_alias, `include/image_decode.h:56`) `typedef struct img_pixels { uint32_t width;` - A decoded bitmap that owns its pixel buffer. The pixel format is Cairo's native premultiplied ARGB32
- `IMG_MAX_SCALE` (macro, `include/image_decode.h:67`) `#define IMG_MAX_SCALE`
- `IMG_MAX_DIM` (macro, `include/image_decode.h:71`) `#define IMG_MAX_DIM`
- `IMG_MAX_PIXELS` (macro, `include/image_decode.h:72`) `#define IMG_MAX_PIXELS`
- `img_dimensions_ok` (function, `include/image_decode.h:84`) `int img_dimensions_ok(uint32_t w, uint32_t h);` - 1 iff (w,h) is non-zero and fits the anti-DoS caps (per-side and area, no * overflow of width*height
- `inputs` (function, `include/image_decode.h:87`) `* Degenerate inputs (<= 0) yield (0,0). Pure. */ void img_fit(uint32_t iw, uint3`
- `decode` (function, `include/image_decode.h:98`) `* the declared dimensions BEFORE the full decode (anti-bomb), decodes to RGB and`
- `img_pixels_free` (function, `include/image_decode.h:127`) `void img_pixels_free(img_pixels *p);` - Releases data and zeroes the struct. Idempotent; safe on NULL and on a zeroed * struct.
- `img_format_name` (function, `include/image_decode.h:130`) `const char *img_format_name(img_format f);` - Releases data and zeroes the struct. Idempotent; safe on NULL and on a zeroed * struct. void img_pix
- `FREEDOM_SVG_PAINT_H` (macro, `include/svg_paint.h:2`) `#define FREEDOM_SVG_PAINT_H`
- `svp_draw` (function, `include/svg_paint.h:31`) `void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, do` - Paints `img` into the rect [x, y, w, h] of `cr`, scaled uniformly and centred ("xMidYMid meet"). cur
- `way` (function, `include/svg_paint.h:35`) `* worker rasterizes SVG images this way (spec/svg_raster.md section 3): drawing`
- `FREEDOM_SVG_RASTER_H` (macro, `include/svg_raster.h:2`) `#define FREEDOM_SVG_RASTER_H`
- `SR_SNIFF_MAX` (macro, `include/svg_raster.h:23`) `#define SR_SNIFF_MAX`
- `SR_MAX_DIM` (macro, `include/svg_raster.h:24`) `#define SR_MAX_DIM`
- `SR_MIN_RASTER` (macro, `include/svg_raster.h:25`) `#define SR_MIN_RASTER`
- `sr_sniff` (function, `include/svg_raster.h:29`) `int sr_sniff(const uint8_t *bytes, size_t len);` - 1 when the first element of the document (after BOM, whitespace, the XML * declaration, comments and
- `FREEDOM_SVG_RENDER_H` (macro, `include/svg_render.h:2`) `#define FREEDOM_SVG_RENDER_H`
- `sv_status` (enum, `include/svg_render.h:25`)
- `SV_MAX_SHAPES` (macro, `include/svg_render.h:32`) `#define SV_MAX_SHAPES`
- `SV_MAX_POINTS` (macro, `include/svg_render.h:33`) `#define SV_MAX_POINTS`
- `SV_MAX_SEGS` (macro, `include/svg_render.h:34`) `#define SV_MAX_SEGS`
- `SV_MAX_DEPTH` (macro, `include/svg_render.h:35`) `#define SV_MAX_DEPTH`
- `SV_TEXT_MAX` (macro, `include/svg_render.h:36`) `#define SV_TEXT_MAX`
- `SV_MAX_INPUT` (macro, `include/svg_render.h:37`) `#define SV_MAX_INPUT`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 12
- Cross-boundary resolved imports (EXTRACTED): 9

## Connections

- [EXTRACTED] depends_on community 1 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/svg_paint.h.

## Risks

- [layer strict] `tests/test_svg_render.c` (testing) -> `include/svg_render.h` (presentation)
- [dataflow DEAD_STORE] `src/image_decode.c:224` `img_decode_jpeg` `dst`: `dst` assigned at line 224 but never read afterwards.

## Open Questions

- Why do 7 file(s) lack file-level docs (e.g. `include/image_decode.h`)? What purpose do they serve?
- What would break if the most connected file in include: svg_render changed?
- Should include: svg_render be split, given cohesion 0.57?

## Sources

- `include/image_decode.h`
- `include/svg_paint.h`
- `include/svg_raster.h`
- `include/svg_render.h`
- `src/image_decode.c`
- `src/svg_paint.c`
- `src/svg_raster.c`
- `src/svg_render.c`
- `tests/test_freedom.c`
- `tests/test_image_decode.c`
- `tests/test_svg_raster.c`
- `tests/test_svg_render.c`
