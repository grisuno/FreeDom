# `include/css_values.h`

> Source: [include/css_values.h:1](../../include/css_values.h#L1) | language `h` | coverage 25.0% | [API index](../index.md)

Single owner of CSS value interpretation for colors and backgrounds.

## Contents

- **Functions:** [`cv_parse_color`](#cv_parse_color), [`cv_interp_color`](#cv_interp_color), [`cv_color_ok`](#cv_color_ok), [`cv_bg_alpha_of`](#cv_bg_alpha_of), [`cv_parse_color_t7`](#cv_parse_color_t7), [`black`](#black), [`cv_interp_bg`](#cv_interp_bg)

## Functions

<a id="cv_parse_color"></a>

### `cv_parse_color`

`function` | [include/css_values.h:12](../../include/css_values.h#L12)

```c
int cv_parse_color(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

*Called by:* [`ct_expand_shadow`](src.css_text.c.md#ct_expand_shadow)

---

<a id="cv_interp_color"></a>

### `cv_interp_color`

`function` | [include/css_values.h:13](../../include/css_values.h#L13)

```c
int cv_interp_color(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="cv_color_ok"></a>

### `cv_color_ok`

`function` | [include/css_values.h:14](../../include/css_values.h#L14)

```c
int cv_color_ok(int c);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `int` |  |  |

**Returns:** `int`

*Called by:* [`cg_expand_background`](src.css_gradient.c.md#cg_expand_background)

---

<a id="cv_bg_alpha_of"></a>

### `cv_bg_alpha_of`

`function` | [include/css_values.h:15](../../include/css_values.h#L15)

```c
int cv_bg_alpha_of(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

*Called by:* [`cg_expand_background`](src.css_gradient.c.md#cg_expand_background)

---

<a id="cv_parse_color_t7"></a>

### `cv_parse_color_t7`

`function` | [include/css_values.h:19](../../include/css_values.h#L19)

```c
int cv_parse_color_t7(const char *v);
```

cv_parse_color with the color's alpha as TRANSPARENCY in bits 24..30 (0 opaque, 127 clear): an opaque color is exactly cv_parse_color's 0xRRGGBB.

Sentinels (-1 invalid, CC_COLOR_CURRENT, CC_COLOR_TRANSPARENT) pass through unchanged.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

*Called by:* [`CSS_GRAD_STOPS_MAX`](src.css_gradient.c.md#css_grad_stops_max)

---

<a id="black"></a>

### `black`

`function` | [include/css_values.h:22](../../include/css_values.h#L22)

```c
* transparent black (127 << 24) -- text that paints nothing, not an absent * value. CC_COLOR_CURRENT and -1 (invalid) pass through. */ int cv_text_color(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `127 << 24` |  |  |  |

**Returns:** `* transparent`

---

<a id="cv_interp_bg"></a>

### `cv_interp_bg`

`function` | [include/css_values.h:25](../../include/css_values.h#L25)

```c
int cv_interp_bg(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

*Called by:* [`cg_expand_background`](src.css_gradient.c.md#cg_expand_background)

---
