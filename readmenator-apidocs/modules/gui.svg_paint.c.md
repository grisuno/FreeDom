# `gui/svg_paint.c`

> Source: [gui/svg_paint.c:1](../../gui/svg_paint.c#L1) | language `c` | coverage 100.0% | [API index](../index.md)

svg_paint — Cairo back end for the shapes svg_render extracted.

## Contents

- **Functions:** [`svp_draw`](#svp_draw)

## Functions

<a id="svp_draw"></a>

### `svp_draw`

`function` | [gui/svg_paint.c:139](../../gui/svg_paint.c#L139)

```c
void svp_draw(cairo_t *cr, const sv_image *img, double x, double y, double w, double h, int current_rgb)
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

> **Inherited:** Documentation from [`svp_draw`](#svp_draw) (include/svg_paint.h:31).

---
