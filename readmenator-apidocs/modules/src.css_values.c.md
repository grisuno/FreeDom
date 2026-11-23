# `src/css_values.c`

> Source: [src/css_values.c:1](../../src/css_values.c#L1) | language `c` | coverage 22.2% | [API index](../index.md)

## Contents

- **Functions:** [`cv_parse_color`](#cv_parse_color), [`cv_interp_color`](#cv_interp_color), [`cv_color_ok`](#cv_color_ok), [`cv_bg_alpha_of`](#cv_bg_alpha_of), [`cv_interp_bg`](#cv_interp_bg), [`cv_parse_color_t7`](#cv_parse_color_t7), [`cv_text_color`](#cv_text_color), [`cv_filter_scale`](#cv_filter_scale)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_css_values_c__cv_interp_color(["cv_interp_color"])
    n_src_css_values_c__cv_parse_color(["cv_parse_color"])
    n_src_css_values_c__cv_interp_bg(["cv_interp_bg"])
    n_src_css_values_c__cv_parse_color_t7(["cv_parse_color_t7"])
    n_src_css_values_c__cv_bg_alpha_of(["cv_bg_alpha_of"])
    n_src_css_values_c__cv_text_color(["cv_text_color"])
    n_src_css_values_c__cv_interp_color --> n_src_css_values_c__cv_parse_color
    n_src_css_values_c__cv_interp_bg --> n_src_css_values_c__cv_parse_color
    n_src_css_values_c__cv_parse_color_t7 --> n_src_css_values_c__cv_bg_alpha_of
    n_src_css_values_c__cv_parse_color_t7 --> n_src_css_values_c__cv_parse_color
    n_src_css_values_c__cv_text_color --> n_src_css_values_c__cv_parse_color_t7
```

## Functions

<a id="cv_parse_color"></a>

### `cv_parse_color`

`function` | [src/css_values.c:42](../../src/css_values.c#L42)

```c
int cv_parse_color(const char *v)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

*Called by:* [`cv_interp_bg`](#cv_interp_bg), [`cv_interp_color`](#cv_interp_color), [`cv_parse_color_t7`](#cv_parse_color_t7)

---

<a id="cv_interp_color"></a>

### `cv_interp_color`

`function` | [src/css_values.c:47](../../src/css_values.c#L47)

```c
int cv_interp_color(const char *v)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

*Calls:* [`cv_parse_color`](#cv_parse_color)

---

<a id="cv_color_ok"></a>

### `cv_color_ok`

`function` | [src/css_values.c:52](../../src/css_values.c#L52)

```c
int cv_color_ok(int c)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `int` |  |  |

**Returns:** `int`

---

<a id="cv_bg_alpha_of"></a>

### `cv_bg_alpha_of`

`function` | [src/css_values.c:199](../../src/css_values.c#L199)

```c
int cv_bg_alpha_of(const char *v)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

*Called by:* [`cv_parse_color_t7`](#cv_parse_color_t7)

---

<a id="cv_interp_bg"></a>

### `cv_interp_bg`

`function` | [src/css_values.c:324](../../src/css_values.c#L324)

```c
int cv_interp_bg(const char *v)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

*Calls:* [`cv_parse_color`](#cv_parse_color)

---

<a id="cv_parse_color_t7"></a>

### `cv_parse_color_t7`

`function` | [src/css_values.c:369](../../src/css_values.c#L369)

```c
int cv_parse_color_t7(const char *v)
```

cv_parse_color with the color's alpha as TRANSPARENCY in bits 24..30 (0 opaque, 127 clear): an opaque color is exactly cv_parse_color's 0xRRGGBB.

Sentinels (-1 invalid, CC_COLOR_CURRENT, CC_COLOR_TRANSPARENT) pass through unchanged.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`cv_parse_color_t7`](#cv_parse_color_t7) (include/css_values.h:24).

*Calls:* [`cv_bg_alpha_of`](#cv_bg_alpha_of), [`cv_parse_color`](#cv_parse_color)

*Called by:* [`cv_text_color`](#cv_text_color)

---

<a id="cv_text_color"></a>

### `cv_text_color`

`function` | [src/css_values.c:386](../../src/css_values.c#L386)

```c
int cv_text_color(const char *v)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

*Calls:* [`cv_parse_color_t7`](#cv_parse_color_t7)

---

<a id="cv_filter_scale"></a>

### `cv_filter_scale`

`function` | [src/css_values.c:395](../../src/css_values.c#L395)

```c
double cv_filter_scale(int pct)
```

The multiplier a filter() brightness/contrast/saturate percentage means (150 -> 1.5).

The style stores 0 for "not declared" and 100 is the identity: both are exactly 1.0 -- the old `!= 100 ? pct/100 : 1` multiplied by ZERO for every undeclared one. Pure.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pct` | `int` |  |  |

**Returns:** `double`

> **Inherited:** Documentation from [`cv_filter_scale`](#cv_filter_scale) (include/css_values.h:20).

---
