# `include/zoom.h`

> Source: [include/zoom.h:1](../../include/zoom.h#L1) | language `h` | coverage 60.0% | [API index](../index.md)

## Contents

- **Functions:** [`zm_clamp`](#zm_clamp), [`zm_zoom_in`](#zm_zoom_in), [`zm_zoom_out`](#zm_zoom_out), [`zm_reset`](#zm_reset), [`zm_scale`](#zm_scale), [`zm_apply`](#zm_apply)
- **Macros:** [`ZM_MIN_PCT`](#zm_min_pct), [`ZM_MAX_PCT`](#zm_max_pct), [`ZM_DEFAULT_PCT`](#zm_default_pct)

## Functions

<a id="zm_clamp"></a>

### `zm_clamp`

`function` | [include/zoom.h:26](../../include/zoom.h#L26)

```c
int zm_clamp(int pct);
```

Clamp pct to [ZM_MIN_PCT, ZM_MAX_PCT].

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pct` | `int` |  |  |

**Returns:** `int`

---

<a id="zm_zoom_in"></a>

### `zm_zoom_in`

`function` | [include/zoom.h:29](../../include/zoom.h#L29)

```c
int zm_zoom_in(int pct);
```

Smallest ladder stop strictly greater than zm_clamp(pct); ZM_MAX_PCT if none.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pct` | `int` |  |  |

**Returns:** `int`

---

<a id="zm_zoom_out"></a>

### `zm_zoom_out`

`function` | [include/zoom.h:32](../../include/zoom.h#L32)

```c
int zm_zoom_out(int pct);
```

Largest ladder stop strictly less than zm_clamp(pct); ZM_MIN_PCT if none.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pct` | `int` |  |  |

**Returns:** `int`

---

<a id="zm_reset"></a>

### `zm_reset`

`function` | [include/zoom.h:35](../../include/zoom.h#L35)

```c
int zm_reset(void);
```

The default zoom level (100).

**Returns:** `int`

*Called by:* [`prefs_init`](src.prefs.c.md#prefs_init)

---

<a id="zm_scale"></a>

### `zm_scale`

`function` | [include/zoom.h:38](../../include/zoom.h#L38)

```c
double zm_scale(int pct);
```

Multiplicative factor: zm_clamp(pct) / 100.0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pct` | `int` |  |  |

**Returns:** `double`

*Called by:* [`UI_READER_COLUMN_W`](gui.browser_ui.c.md#ui_reader_column_w)

---

<a id="zm_apply"></a>

### `zm_apply`

`function` | [include/zoom.h:42](../../include/zoom.h#L42)

```c
double zm_apply(double base_px, int pct);
```

base_px * zm_scale(pct), floored to 1.0 when base_px > 0 so a font can never scale away to nothing. base_px <= 0 returns base_px * scale unfloored.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `base_px` | `double` |  |  |
| `pct` | `int` |  |  |

**Returns:** `double`

*Called by:* [`UI_READER_COLUMN_W`](gui.browser_ui.c.md#ui_reader_column_w)

---

## Macros

<a id="zm_min_pct"></a>

### `ZM_MIN_PCT`

`macro` | [include/zoom.h:21](../../include/zoom.h#L21)

```c
#define ZM_MIN_PCT
```

---

<a id="zm_max_pct"></a>

### `ZM_MAX_PCT`

`macro` | [include/zoom.h:22](../../include/zoom.h#L22)

```c
#define ZM_MAX_PCT
```

---

<a id="zm_default_pct"></a>

### `ZM_DEFAULT_PCT`

`macro` | [include/zoom.h:23](../../include/zoom.h#L23)

```c
#define ZM_DEFAULT_PCT
```

---
