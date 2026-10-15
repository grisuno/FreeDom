# `include/css_text.h`

> Source: [include/css_text.h:1](../../include/css_text.h#L1) | language `h` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`ct_interp_fontfamily`](#ct_interp_fontfamily), [`ct_interp_texttransform`](#ct_interp_texttransform), [`ct_interp_opacity`](#ct_interp_opacity), [`ct_interp_valign`](#ct_interp_valign), [`ct_expand_valign`](#ct_expand_valign), [`ct_interp_transition_property`](#ct_interp_transition_property), [`ct_interp_whitespace`](#ct_interp_whitespace), [`ct_interp_tabsize`](#ct_interp_tabsize), [`ct_interp_textdeco_style`](#ct_interp_textdeco_style), [`ct_interp_textdeco_thickness`](#ct_interp_textdeco_thickness), [`ct_interp_aspect_ratio`](#ct_interp_aspect_ratio), [`ct_interp_direction`](#ct_interp_direction), [`ct_interp_liststyle`](#ct_interp_liststyle), [`ct_interp_spacing`](#ct_interp_spacing), [`ct_emit_spacing`](#ct_emit_spacing), [`ct_expand_shadow`](#ct_expand_shadow)

## Functions

<a id="ct_interp_fontfamily"></a>

### `ct_interp_fontfamily`

`function` | [include/css_text.h:10](../../include/css_text.h#L10)

```c
int ct_interp_fontfamily(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="ct_interp_texttransform"></a>

### `ct_interp_texttransform`

`function` | [include/css_text.h:11](../../include/css_text.h#L11)

```c
int ct_interp_texttransform(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="ct_interp_opacity"></a>

### `ct_interp_opacity`

`function` | [include/css_text.h:12](../../include/css_text.h#L12)

```c
int ct_interp_opacity(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="ct_interp_valign"></a>

### `ct_interp_valign`

`function` | [include/css_text.h:13](../../include/css_text.h#L13)

```c
int ct_interp_valign(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="ct_expand_valign"></a>

### `ct_expand_valign`

`function` | [include/css_text.h:14](../../include/css_text.h#L14)

```c
int ct_expand_valign(const char *val, css_decl *dst, int cap);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `val` | `char *` |  |  |
| `dst` | `css_decl *` |  |  |
| `cap` | `int` |  |  |

**Returns:** `int`

---

<a id="ct_interp_transition_property"></a>

### `ct_interp_transition_property`

`function` | [include/css_text.h:15](../../include/css_text.h#L15)

```c
int ct_interp_transition_property(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="ct_interp_whitespace"></a>

### `ct_interp_whitespace`

`function` | [include/css_text.h:16](../../include/css_text.h#L16)

```c
int ct_interp_whitespace(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="ct_interp_tabsize"></a>

### `ct_interp_tabsize`

`function` | [include/css_text.h:17](../../include/css_text.h#L17)

```c
int ct_interp_tabsize(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="ct_interp_textdeco_style"></a>

### `ct_interp_textdeco_style`

`function` | [include/css_text.h:18](../../include/css_text.h#L18)

```c
int ct_interp_textdeco_style(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="ct_interp_textdeco_thickness"></a>

### `ct_interp_textdeco_thickness`

`function` | [include/css_text.h:19](../../include/css_text.h#L19)

```c
int ct_interp_textdeco_thickness(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="ct_interp_aspect_ratio"></a>

### `ct_interp_aspect_ratio`

`function` | [include/css_text.h:20](../../include/css_text.h#L20)

```c
int ct_interp_aspect_ratio(const char *v, int *num, int *den);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |
| `num` | `int *` |  |  |
| `den` | `int *` |  |  |

**Returns:** `int`

---

<a id="ct_interp_direction"></a>

### `ct_interp_direction`

`function` | [include/css_text.h:21](../../include/css_text.h#L21)

```c
int ct_interp_direction(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="ct_interp_liststyle"></a>

### `ct_interp_liststyle`

`function` | [include/css_text.h:22](../../include/css_text.h#L22)

```c
int ct_interp_liststyle(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="ct_interp_spacing"></a>

### `ct_interp_spacing`

`function` | [include/css_text.h:23](../../include/css_text.h#L23)

```c
int ct_interp_spacing(const char *v, int *out);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |
| `out` | `int *` |  |  |

**Returns:** `int`

*Called by:* [`ct_emit_spacing`](src.css_text.c.md#ct_emit_spacing)

---

<a id="ct_emit_spacing"></a>

### `ct_emit_spacing`

`function` | [include/css_text.h:24](../../include/css_text.h#L24)

```c
int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dst` | `css_decl *` |  |  |
| `cap` | `int` |  |  |
| `slot` | `int` |  |  |
| `val` | `char *` |  |  |

**Returns:** `int`

---

<a id="ct_expand_shadow"></a>

### `ct_expand_shadow`

`function` | [include/css_text.h:25](../../include/css_text.h#L25)

```c
int ct_expand_shadow(const char *val, css_decl *dst, int cap);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `val` | `char *` |  |  |
| `dst` | `css_decl *` |  |  |
| `cap` | `int` |  |  |

**Returns:** `int`

---
