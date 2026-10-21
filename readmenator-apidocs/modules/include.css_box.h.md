# `include/css_box.h`

> Source: [include/css_box.h:1](../../include/css_box.h#L1) | language `h` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`cb_length_px`](#cb_length_px), [`cb_interp_len`](#cb_interp_len), [`cb_emit_len`](#cb_emit_len), [`cb_expand_box4`](#cb_expand_box4), [`cb_expand_box2`](#cb_expand_box2), [`cb_interp_lp`](#cb_interp_lp), [`cb_value_em_milli`](#cb_value_em_milli), [`rectangle`](#rectangle), [`cb_lp_can_be_nonneg`](#cb_lp_can_be_nonneg), [`cb_next_ws_token`](#cb_next_ws_token), [`cb_interp_align`](#cb_interp_align), [`cb_interp_fontsize_ex`](#cb_interp_fontsize_ex), [`cb_interp_lineheight`](#cb_interp_lineheight), [`cb_interp_weight`](#cb_interp_weight), [`cb_interp_style`](#cb_interp_style), [`cb_interp_textdeco`](#cb_interp_textdeco), [`cb_interp_display`](#cb_interp_display), [`cb_interp_gap`](#cb_interp_gap), [`cb_interp_justify`](#cb_interp_justify), [`cb_interp_gridcols`](#cb_interp_gridcols), [`cb_expand_grid_template_cols`](#cb_expand_grid_template_cols), [`strings`](#strings)
- **Macros:** [`CB_AUTO_REJECT`](#cb_auto_reject), [`CB_AUTO_VALUE`](#cb_auto_value), [`CB_AUTO_RESET`](#cb_auto_reset), [`CB_AUTO_RESET_NONE`](#cb_auto_reset_none)

## Functions

<a id="cb_length_px"></a>

### `cb_length_px`

`function` | [include/css_box.h:15](../../include/css_box.h#L15)

```c
int cb_length_px(const char *v, double *px);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |
| `px` | `double *` |  |  |

**Returns:** `int`

---

<a id="cb_interp_len"></a>

### `cb_interp_len`

`function` | [include/css_box.h:16](../../include/css_box.h#L16)

```c
int cb_interp_len(const char *v, int allow_auto, int *out);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |
| `allow_auto` | `int` |  |  |
| `out` | `int *` |  |  |

**Returns:** `int`

*Called by:* [`ct_expand_shadow`](src.css_text.c.md#ct_expand_shadow), [`ct_interp_textdeco_thickness`](src.css_text.c.md#ct_interp_textdeco_thickness)

---

<a id="cb_emit_len"></a>

### `cb_emit_len`

`function` | [include/css_box.h:17](../../include/css_box.h#L17)

```c
int cb_emit_len(css_decl *dst, int cap, int slot, const char *val, int allow_auto, int allow_neg);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dst` | `css_decl *` |  |  |
| `cap` | `int` |  |  |
| `slot` | `int` |  |  |
| `val` | `char *` |  |  |
| `allow_auto` | `int` |  |  |
| `allow_neg` | `int` |  |  |

**Returns:** `int`

*Called by:* [`AUTO_RESET_NONE`](src.css.c.md#auto_reset_none), [`AUTO_RESET_NONE`](src.css_box.c.md#auto_reset_none), [`cb_expand_box2`](src.css_box.c.md#cb_expand_box2)

---

<a id="cb_expand_box4"></a>

### `cb_expand_box4`

`function` | [include/css_box.h:19](../../include/css_box.h#L19)

```c
int cb_expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg, css_decl *dst, int cap);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `val` | `char *` |  |  |
| `slot_top` | `int` |  |  |
| `allow_auto` | `int` |  |  |
| `allow_neg` | `int` |  |  |
| `dst` | `css_decl *` |  |  |
| `cap` | `int` |  |  |

**Returns:** `int`

---

<a id="cb_expand_box2"></a>

### `cb_expand_box2`

`function` | [include/css_box.h:21](../../include/css_box.h#L21)

```c
int cb_expand_box2(const char *val, int slot_start, int slot_end, int allow_auto, int allow_neg, css_decl *dst, int cap);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `val` | `char *` |  |  |
| `slot_start` | `int` |  |  |
| `slot_end` | `int` |  |  |
| `allow_auto` | `int` |  |  |
| `allow_neg` | `int` |  |  |
| `dst` | `css_decl *` |  |  |
| `cap` | `int` |  |  |

**Returns:** `int`

---

<a id="cb_interp_lp"></a>

### `cb_interp_lp`

`function` | [include/css_box.h:23](../../include/css_box.h#L23)

```c
int cb_interp_lp(const char *v, int allow_auto, int allow_pct, int *out_px, int *out_pm);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |
| `allow_auto` | `int` |  |  |
| `allow_pct` | `int` |  |  |
| `out_px` | `int *` |  |  |
| `out_pm` | `int *` |  |  |

**Returns:** `int`

*Called by:* [`ct_expand_valign`](src.css_text.c.md#ct_expand_valign)

---

<a id="cb_value_em_milli"></a>

### `cb_value_em_milli`

`function` | [include/css_box.h:25](../../include/css_box.h#L25)

```c
int cb_value_em_milli(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

*Called by:* [`ct_expand_valign`](src.css_text.c.md#ct_expand_valign)

---

<a id="rectangle"></a>

### `rectangle`

`function` | [include/css_box.h:27](../../include/css_box.h#L27)

```c
* rectangle (top, right, bottom, left): px[i] + pm[i]/1000 of the border box (height for * top/bottom, width for left/right). A right/bottom inset r is the edge at 100% - r. The * `round` radii are ig
```

**Returns:** `` px[i] + pm[i]/1000 of the border box (height for * top/bottom, width for left/right). A right/bottom inset r is the edge at 100% - r. The * `round` radii are ig ``

---

<a id="cb_lp_can_be_nonneg"></a>

### `cb_lp_can_be_nonneg`

`function` | [include/css_box.h:31](../../include/css_box.h#L31)

```c
int cb_lp_can_be_nonneg(int px_val, int pct_pm);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `px_val` | `int` |  |  |
| `pct_pm` | `int` |  |  |

**Returns:** `int`

*Called by:* [`AUTO_RESET_NONE`](src.css_box.c.md#auto_reset_none)

---

<a id="cb_next_ws_token"></a>

### `cb_next_ws_token`

`function` | [include/css_box.h:32](../../include/css_box.h#L32)

```c
int cb_next_ws_token(const char **p, char *tok, size_t cap);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `p` | `char **` |  |  |
| `tok` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `int`

*Called by:* [`cb_clip_inset`](src.css_box.c.md#cb_clip_inset), [`cb_expand_box2`](src.css_box.c.md#cb_expand_box2), [`interp_len`](src.css_box.c.md#interp_len), [`ct_expand_shadow`](src.css_text.c.md#ct_expand_shadow)

---

<a id="cb_interp_align"></a>

### `cb_interp_align`

`function` | [include/css_box.h:33](../../include/css_box.h#L33)

```c
int cb_interp_align(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="cb_interp_fontsize_ex"></a>

### `cb_interp_fontsize_ex`

`function` | [include/css_box.h:34](../../include/css_box.h#L34)

```c
int cb_interp_fontsize_ex(const char *v, int *abs_out);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |
| `abs_out` | `int *` |  |  |

**Returns:** `int`

---

<a id="cb_interp_lineheight"></a>

### `cb_interp_lineheight`

`function` | [include/css_box.h:35](../../include/css_box.h#L35)

```c
int cb_interp_lineheight(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="cb_interp_weight"></a>

### `cb_interp_weight`

`function` | [include/css_box.h:36](../../include/css_box.h#L36)

```c
int cb_interp_weight(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="cb_interp_style"></a>

### `cb_interp_style`

`function` | [include/css_box.h:37](../../include/css_box.h#L37)

```c
int cb_interp_style(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="cb_interp_textdeco"></a>

### `cb_interp_textdeco`

`function` | [include/css_box.h:38](../../include/css_box.h#L38)

```c
int cb_interp_textdeco(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="cb_interp_display"></a>

### `cb_interp_display`

`function` | [include/css_box.h:39](../../include/css_box.h#L39)

```c
int cb_interp_display(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="cb_interp_gap"></a>

### `cb_interp_gap`

`function` | [include/css_box.h:40](../../include/css_box.h#L40)

```c
int cb_interp_gap(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="cb_interp_justify"></a>

### `cb_interp_justify`

`function` | [include/css_box.h:41](../../include/css_box.h#L41)

```c
int cb_interp_justify(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="cb_interp_gridcols"></a>

### `cb_interp_gridcols`

`function` | [include/css_box.h:42](../../include/css_box.h#L42)

```c
int cb_interp_gridcols(const char *v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `char *` |  |  |

**Returns:** `int`

---

<a id="cb_expand_grid_template_cols"></a>

### `cb_expand_grid_template_cols`

`function` | [include/css_box.h:43](../../include/css_box.h#L43)

```c
int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `val` | `char *` |  |  |
| `dst` | `css_decl *` |  |  |
| `cap` | `int` |  |  |

**Returns:** `int`

---

<a id="strings"></a>

### `strings`

`function` | [include/css_box.h:45](../../include/css_box.h#L45)

```c
* Quoted area strings (the grid-template shorthand's row half) are skipped. */ int cb_expand_grid_template_rows(const char *val, css_decl *dst, int cap);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `half` | `the grid-template shorthand's row` |  |  |

**Returns:** `* Quoted area`

---

## Macros

<a id="cb_auto_reject"></a>

### `CB_AUTO_REJECT`

`macro` | [include/css_box.h:10](../../include/css_box.h#L10)

```c
#define CB_AUTO_REJECT
```

---

<a id="cb_auto_value"></a>

### `CB_AUTO_VALUE`

`macro` | [include/css_box.h:11](../../include/css_box.h#L11)

```c
#define CB_AUTO_VALUE
```

---

<a id="cb_auto_reset"></a>

### `CB_AUTO_RESET`

`macro` | [include/css_box.h:12](../../include/css_box.h#L12)

```c
#define CB_AUTO_RESET
```

---

<a id="cb_auto_reset_none"></a>

### `CB_AUTO_RESET_NONE`

`macro` | [include/css_box.h:13](../../include/css_box.h#L13)

```c
#define CB_AUTO_RESET_NONE
```

---
