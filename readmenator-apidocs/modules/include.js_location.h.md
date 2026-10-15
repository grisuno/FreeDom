# `include/js_location.h`

> Source: [include/js_location.h:1](../../include/js_location.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

## Contents

- **Functions:** [`reads`](#reads), [`jd_take_history`](#jd_take_history), [`jd_pop_state`](#jd_pop_state), [`acting`](#acting)
- **Macros:** [`JD_HIST_MAX`](#jd_hist_max)

## Functions

<a id="reads"></a>

### `reads`

`function` | [include/js_location.h:25](../../include/js_location.h#L25)

```c
* reads (NULL => only href is known, the rest fall back to stub defaults). Call after * jd_install, on the page's context. ctx == NULL => JD_ERR_NULL_ARG. */ jd_status jd_set_location(js_context *ctx,
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `known` | `NULL => only href is` |  |  |
| `defaults` | `the rest fall back to stub` |  |  |

**Returns:** `*`

---

<a id="jd_take_history"></a>

### `jd_take_history`

`function` | [include/js_location.h:38](../../include/js_location.h#L38)

```c
char *jd_take_history(js_context *ctx, int *go);
```

Drains the history operations page JS performed since the last call: an owned string of lines "P <url>\n" (pushState) / "R <url>\n" (replaceState), URLs absolute and already same-origin-checked by the worker (the parent re-checks), or NULL when there were none. *go (optional) receives the net history.back/forward/go delta, also cleared.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `go` | `int *` |  |  |

**Returns:** `char *`

---

<a id="jd_pop_state"></a>

### `jd_pop_state`

`function` | [include/js_location.h:44](../../include/js_location.h#L44)

```c
int jd_pop_state(js_context *ctx, int index);
```

Moves the page's history to entry index (the parent went Back/Forward within the same document): updates location and dispatches popstate (and hashchange when only the fragment changed) on window.

Returns 1 when applied, 0 when index is out of range or no location is installed.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `index` | `int` |  |  |

**Returns:** `int`

---

<a id="acting"></a>

### `acting`

`function` | [include/js_location.h:49](../../include/js_location.h#L49)

```c
* The caller MUST gate the raw target with ln_resolve before acting (Zero Trust). */ int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `Trust` | `Zero` |  |  |

**Returns:** `* The caller MUST gate the raw target with ln_resolve before`

---

## Macros

<a id="jd_hist_max"></a>

### `JD_HIST_MAX`

`macro` | [include/js_location.h:31](../../include/js_location.h#L31)

```c
#define JD_HIST_MAX
```

Bound on a document's history entries and on the operations one response carries (spec/js_dom.md 7e).

Past it pushState behaves as replaceState.

---
