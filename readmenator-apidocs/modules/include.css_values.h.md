# `include/css_values.h`

> Source: [include/css_values.h:1](../../include/css_values.h#L1) | language `h` | coverage 16.7% | [API index](../index.md)

Single owner of CSS value interpretation for colors and backgrounds.

## Contents

- **Functions:** [`cv_parse_color`](#cv_parse_color), [`cv_interp_color`](#cv_interp_color), [`cv_color_ok`](#cv_color_ok), [`cv_bg_alpha_of`](#cv_bg_alpha_of), [`cv_interp_bg`](#cv_interp_bg)

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

*Called by:* [`CSS_GRAD_STOPS_MAX`](src.css_gradient.c.md#css_grad_stops_max), [`ct_expand_shadow`](src.css_text.c.md#ct_expand_shadow)

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

*Called by:* [`CSS_GRAD_STOPS_MAX`](src.css_gradient.c.md#css_grad_stops_max), [`cg_expand_background`](src.css_gradient.c.md#cg_expand_background)

---

<a id="cv_interp_bg"></a>

### `cv_interp_bg`

`function` | [include/css_values.h:16](../../include/css_values.h#L16)

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
