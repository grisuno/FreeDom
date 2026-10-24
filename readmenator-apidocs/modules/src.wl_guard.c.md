# `src/wl_guard.c`

> Source: [src/wl_guard.c:1](../../src/wl_guard.c#L1) | language `c` | coverage 33.3% | [API index](../index.md)

## Contents

- **Structs:** [`wl_guard`](#wl_guard)
- **Functions:** [`wlg_start`](#wlg_start), [`wlg_stop`](#wlg_stop)
- **Macros:** [`_DEFAULT_SOURCE`](#_default_source), [`WLG_POLL_MS`](#wlg_poll_ms)

## Structs

<a id="wl_guard"></a>

### `wl_guard`

`struct` | [src/wl_guard.c:19](../../src/wl_guard.c#L19)

```c
struct wl_guard
```

---

## Functions

<a id="wlg_start"></a>

### `wlg_start`

`function` | [src/wl_guard.c:45](../../src/wl_guard.c#L45)

```c
wl_guard *wlg_start(struct wl_display *display)
```

Starts the helper for `display` (NULL on failure: the GUI then runs unguarded).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `display` | `struct wl_display *` |  |  |

**Returns:** `wl_guard *`

> **Inherited:** Documentation from [`wlg_start`](#wlg_start) (include/wl_guard.h:25).

---

<a id="wlg_stop"></a>

### `wlg_stop`

`function` | [src/wl_guard.c:61](../../src/wl_guard.c#L61)

```c
void wlg_stop(wl_guard *g)
```

Stops and joins the helper.

Call before wl_display_disconnect. NULL is a no-op.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `g` | `wl_guard *` |  |  |

> **Inherited:** Documentation from [`wlg_stop`](#wlg_stop) (include/wl_guard.h:28).

---

## Macros

<a id="_default_source"></a>

### `_DEFAULT_SOURCE`

`macro` | [src/wl_guard.c:5](../../src/wl_guard.c#L5)

```c
#define _DEFAULT_SOURCE
```

---

<a id="wlg_poll_ms"></a>

### `WLG_POLL_MS`

`macro` | [src/wl_guard.c:17](../../src/wl_guard.c#L17)

```c
#define WLG_POLL_MS
```

---
