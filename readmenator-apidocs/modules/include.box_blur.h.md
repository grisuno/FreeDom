# `include/box_blur.h`

> Source: [include/box_blur.h:1](../../include/box_blur.h#L1) | language `h` | coverage 80.0% | [API index](../index.md)

Gaussian blur of an 8-bit alpha mask by three box passes per axis (spec/box_blur.md).

Pure: no I/O, one scratch allocation freed before return.

## Contents

- **Functions:** [`bb_box_sizes`](#bb_box_sizes), [`BB_MAX_PIXELS`](#bb_max_pixels), [`alpha`](#alpha)
- **Macros:** [`BB_MAX_PIXELS`](#bb_max_pixels)

## Functions

<a id="bb_box_sizes"></a>

### `bb_box_sizes`

`function` | [include/box_blur.h:16](../../include/box_blur.h#L16)

```c
int bb_box_sizes(double sigma, int sizes[3]);
```

The three odd box widths approximating a Gaussian of standard deviation sigma.

Returns 0 (sizes untouched) when sigma is not finite or <= 0, else 1.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sigma` | `double` |  |  |
| `sizes` | `int [3]` |  |  |

**Returns:** `int`

---

<a id="bb_max_pixels"></a>

### `BB_MAX_PIXELS`

`function` | [include/box_blur.h:20](../../include/box_blur.h#L20)

```c
* arguments or a mask larger than BB_MAX_PIXELS (buffer untouched). */ int bb_blur_a8(unsigned char *buf, int w, int h, int stride, double sigma);
```

Largest mask bb_blur_a8 accepts (anti-DoS).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `untouched` | `buffer` |  |  |

**Returns:** `* arguments or a mask larger than`

> **Inherited:** Documentation from [`BB_MAX_PIXELS`](#bb_max_pixels) (include/box_blur.h:12).

---

<a id="alpha"></a>

### `alpha`

`function` | [include/box_blur.h:26](../../include/box_blur.h#L26)

```c
* no pixel has alpha (nothing to blur), 1 otherwise. Everything outside rect stays 0 after the blur, * so blurring just rect is identical to blurring the whole surface. */ int bb_ink_rect(const unsign
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `blur` | `nothing to` |  |  |

**Returns:** `* no pixel has`

---

## Macros

<a id="bb_max_pixels"></a>

### `BB_MAX_PIXELS`

`macro` | [include/box_blur.h:12](../../include/box_blur.h#L12)

```c
#define BB_MAX_PIXELS
```

Largest mask bb_blur_a8 accepts (anti-DoS).

---
