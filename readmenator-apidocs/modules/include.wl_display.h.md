# `include/wl_display.h`

> Source: [include/wl_display.h:1](../../include/wl_display.h#L1) | language `h` | coverage 33.3% | [API index](../index.md)

## Contents

- **Functions:** [`pure`](#pure), [`wd_pick`](#wd_pick), [`wd_resolve_env`](#wd_resolve_env)
- **Macros:** [`WD_OK`](#wd_ok), [`WD_NONE`](#wd_none)

## Functions

<a id="pure"></a>

### `pure`

`function` | [include/wl_display.h:3](../../include/wl_display.h#L3)

```c
* wd_pick is pure (no I/O);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `O` | `no I/` |  |  |

**Returns:** `* wd_pick is`

---

<a id="wd_pick"></a>

### `wd_pick`

`function` | [include/wl_display.h:16](../../include/wl_display.h#L16)

```c
int wd_pick(const char *const *names, size_t n, char *out, size_t cap);
```

Choose the lowest-numbered "wayland-N" (N = digits only) from names[0..n).

Writes it NUL-terminated into out; returns WD_NONE (out untouched) if none qualifies or cap is too small.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `names` | `char *const *` |  |  |
| `n` | `size_t` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `int`

---

<a id="wd_resolve_env"></a>

### `wd_resolve_env`

`function` | [include/wl_display.h:20](../../include/wl_display.h#L20)

```c
int wd_resolve_env(void);
```

If WAYLAND_DISPLAY is unset/empty, set it from the sockets found in XDG_RUNTIME_DIR.

Returns WD_OK if the variable is set on return, WD_NONE otherwise.

**Returns:** `int`

*Called by:* [`main`](src.freedom.c.md#main)

---

## Macros

<a id="wd_ok"></a>

### `WD_OK`

`macro` | [include/wl_display.h:10](../../include/wl_display.h#L10)

```c
#define WD_OK
```

---

<a id="wd_none"></a>

### `WD_NONE`

`macro` | [include/wl_display.h:11](../../include/wl_display.h#L11)

```c
#define WD_NONE
```

---
