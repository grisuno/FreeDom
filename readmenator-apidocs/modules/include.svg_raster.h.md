# `include/svg_raster.h`

> Source: [include/svg_raster.h:1](../../include/svg_raster.h#L1) | language `h` | coverage 60.0% | [API index](../index.md)

## Contents

- **Functions:** [`sr_sniff`](#sr_sniff)
- **Macros:** [`SR_SNIFF_MAX`](#sr_sniff_max), [`SR_MAX_DIM`](#sr_max_dim), [`SR_MIN_RASTER`](#sr_min_raster)

## Functions

<a id="sr_sniff"></a>

### `sr_sniff`

`function` | [include/svg_raster.h:29](../../include/svg_raster.h#L29)

```c
int sr_sniff(const uint8_t *bytes, size_t len);
```

1 when the first element of the document (after BOM, whitespace, the XML declaration, comments and a doctype) is <svg; 0 otherwise.

Pure.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bytes` | `uint8_t *` |  |  |
| `len` | `size_t` |  |  |

**Returns:** `int`

---

## Macros

<a id="sr_sniff_max"></a>

### `SR_SNIFF_MAX`

`macro` | [include/svg_raster.h:23](../../include/svg_raster.h#L23)

```c
#define SR_SNIFF_MAX
```

---

<a id="sr_max_dim"></a>

### `SR_MAX_DIM`

`macro` | [include/svg_raster.h:24](../../include/svg_raster.h#L24)

```c
#define SR_MAX_DIM
```

bytes inspected by sr_sniff

---

<a id="sr_min_raster"></a>

### `SR_MIN_RASTER`

`macro` | [include/svg_raster.h:25](../../include/svg_raster.h#L25)

```c
#define SR_MIN_RASTER
```

longest side of the raster; larger scales down

---
