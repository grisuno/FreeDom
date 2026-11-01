# `include/svg_paint.h`

> Source: [include/svg_paint.h:1](../../include/svg_paint.h#L1) | language `h` | coverage 33.3% | [API index](../index.md)

## Contents

- **Functions:** [`svp_draw`](#svp_draw), [`way`](#way)

## Functions

<a id="svp_draw"></a>

### `svp_draw`

`function` | [include/svg_paint.h:31](../../include/svg_paint.h#L31)

```c
void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, double h, int current_rgb);
```

Paints `img` into the rect [x, y, w, h] of `cr`, scaled uniformly and centred ("xMidYMid meet"). current_rgb is the inherited text colour, substituted wherever a shape asked for `currentColor` (packed 0xRRGGBB).

The Cairo state is saved and restored around the call, and painting is clipped to the rect, so a hostile transform can never draw outside the box the layout gave the image.

No-ops on a NULL argument or a non-positive rect.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cr` | `cairo_t *` |  |  |
| `img` | `sv_image *` |  |  |
| `x` | `double` |  |  |
| `y` | `double` |  |  |
| `w` | `double` |  |  |
| `h` | `double` |  |  |
| `current_rgb` | `int` |  |  |

---

<a id="way"></a>

### `way`

`function` | [include/svg_paint.h:35](../../include/svg_paint.h#L35)

```c
* worker rasterizes SVG images this way (spec/svg_raster.md section 3): drawing text * would open fontconfig, i.e. system files, from inside the sandbox. */ void svp_draw_ex(cairo_t *cr, const sv_imag
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `section` | `spec/svg_raster.md 3` |  |  |

**Returns:** `drawing text * would open fontconfig, i.e. system files, from inside the sandbox. */ void svp_draw_ex(cairo_t *cr, const sv_imag`

---
