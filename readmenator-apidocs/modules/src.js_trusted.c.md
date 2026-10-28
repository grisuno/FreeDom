# `src/js_trusted.c`

> Source: [src/js_trusted.c:1](../../src/js_trusted.c#L1) | language `c` | coverage 31.2% | [API index](../index.md)

## Contents

- **Structs:** [`jt_seed_ctx`](#jt_seed_ctx)
- **Functions:** [`jt_enable_open`](#jt_enable_open), [`jt_enable_observers`](#jt_enable_observers), [`jt_geometry_changed`](#jt_geometry_changed), [`jt_take_opens`](#jt_take_opens), [`jt_enable_ws`](#jt_enable_ws), [`jt_ws_ops_free`](#jt_ws_ops_free), [`jt_take_ws`](#jt_take_ws), [`jt_ws_event`](#jt_ws_event), [`jt_enable_frames`](#jt_enable_frames), [`jt_enable_storage`](#jt_enable_storage), [`jt_take_storage`](#jt_take_storage), [`explicitly`](#explicitly), [`jt_enable_worker`](#jt_enable_worker)
- **Macros:** [`JT_IO_MAX_STR`](#jt_io_max_str)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_js_trusted_c__jt_enable_open(["jt_enable_open"])
    n_src_js_sandbox_c__js_context_raw["js_sandbox.js_context_raw"]
    n_src_js_trusted_c__jt_enable_observers(["jt_enable_observers"])
    n_src_js_trusted_c__jt_geometry_changed(["jt_geometry_changed"])
    n_src_js_trusted_c__jt_take_opens(["jt_take_opens"])
    n_src_js_trusted_c__jt_enable_ws(["jt_enable_ws"])
    n_src_js_trusted_c__jt_take_ws(["jt_take_ws"])
    n_src_box_style_c__take["box_style.take"]
    n_src_js_trusted_c__jt_ws_event(["jt_ws_event"])
    n_src_js_trusted_c__jt_enable_frames(["jt_enable_frames"])
    n_src_css_c__function["css.function"]
    n_src_js_trusted_c__jt_enable_storage(["jt_enable_storage"])
    n_src_web_storage_c__wst_foreach["web_storage.wst_foreach"]
    n_src_js_trusted_c__jt_take_storage(["jt_take_storage"])
    n_src_web_storage_c__wst_pack["web_storage.wst_pack"]
    n_src_js_trusted_c__jt_enable_worker(["jt_enable_worker"])
    n_src_js_sandbox_c__js_install_realms["js_sandbox.js_install_realms"]
    n_src_js_trusted_c__jt_enable_open -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_trusted_c__jt_enable_observers -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_trusted_c__jt_geometry_changed -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_trusted_c__jt_take_opens -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_trusted_c__jt_enable_ws -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_trusted_c__jt_take_ws -.-> n_src_box_style_c__take
    n_src_js_trusted_c__jt_take_ws -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_trusted_c__jt_ws_event -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_trusted_c__jt_enable_frames -.-> n_src_css_c__function
    n_src_js_trusted_c__jt_enable_frames -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_trusted_c__jt_enable_storage -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_trusted_c__jt_enable_storage -.-> n_src_web_storage_c__wst_foreach
    n_src_js_trusted_c__jt_take_storage -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_trusted_c__jt_take_storage -.-> n_src_web_storage_c__wst_pack
    n_src_js_trusted_c__jt_enable_worker -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_trusted_c__jt_enable_worker -.-> n_src_js_sandbox_c__js_install_realms
```

## Structs

<a id="jt_seed_ctx"></a>

### `jt_seed_ctx`

`struct` | [src/js_trusted.c:476](../../src/js_trusted.c#L476)

```c
typedef struct jt_seed_ctx { JSContext *js; JSValue fn; JSValue global; } jt_seed_ctx;
```

---

## Functions

<a id="jt_enable_open"></a>

### `jt_enable_open`

`function` | [src/js_trusted.c:48](../../src/js_trusted.c#L48)

```c
jd_status jt_enable_open(js_context *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `jd_status`

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

---

<a id="jt_enable_observers"></a>

### `jt_enable_observers`

`function` | [src/js_trusted.c:129](../../src/js_trusted.c#L129)

```c
jd_status jt_enable_observers(js_context *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `jd_status`

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

---

<a id="jt_geometry_changed"></a>

### `jt_geometry_changed`

`function` | [src/js_trusted.c:143](../../src/js_trusted.c#L143)

```c
jd_status jt_geometry_changed(js_context *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `jd_status`

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

---

<a id="jt_take_opens"></a>

### `jt_take_opens`

`function` | [src/js_trusted.c:159](../../src/js_trusted.c#L159)

```c
char *jt_take_opens(js_context *ctx)
```

Drains the recorded window.open targets as "url\n" lines, or NULL when none.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`jt_take_opens`](#jt_take_opens) (include/js_trusted.h:42).

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

---

<a id="jt_enable_ws"></a>

### `jt_enable_ws`

`function` | [src/js_trusted.c:237](../../src/js_trusted.c#L237)

```c
jd_status jt_enable_ws(js_context *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `jd_status`

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

---

<a id="jt_ws_ops_free"></a>

### `jt_ws_ops_free`

`function` | [src/js_trusted.c:249](../../src/js_trusted.c#L249)

```c
void jt_ws_ops_free(jt_ws_op *ops, size_t n)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ops` | `jt_ws_op *` |  |  |
| `n` | `size_t` |  |  |

---

<a id="jt_take_ws"></a>

### `jt_take_ws`

`function` | [src/js_trusted.c:285](../../src/js_trusted.c#L285)

```c
size_t jt_take_ws(js_context *ctx, jt_ws_op *ops, size_t cap)
```

Drains up to cap recorded operations into ops (each data owned; release with jt_ws_ops_free).

Returns the count. Operations past JT_WS_MAX_OPS/JT_WS_MAX_BYTES are dropped and their socket is errored+closed on the page side.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `ops` | `jt_ws_op *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`jt_take_ws`](#jt_take_ws) (include/js_trusted.h:86).

*Calls:* [`take`](src.box_style.c.md#take), [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

---

<a id="jt_ws_event"></a>

### `jt_ws_event`

`function` | [src/js_trusted.c:336](../../src/js_trusted.c#L336)

```c
int jt_ws_event(js_context *ctx, int id, int kind, int code, const char *data, size_t len)
```

Delivers a socket event from the parent: data enters JS as a VALUE (a string for text, an ArrayBuffer for binary, the reason for close), never as source.

Returns 1 when a live socket with that id received it.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `id` | `int` |  |  |
| `kind` | `int` |  |  |
| `code` | `int` |  |  |
| `data` | `char *` |  |  |
| `len` | `size_t` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`jt_ws_event`](#jt_ws_event) (include/js_trusted.h:92).

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

---

<a id="jt_enable_frames"></a>

### `jt_enable_frames`

`function` | [src/js_trusted.c:432](../../src/js_trusted.c#L432)

```c
jd_status jt_enable_frames(js_context *ctx, int frame_id)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `frame_id` | `int` |  |  |

**Returns:** `jd_status`

*Calls:* [`function`](src.css.c.md#function), [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

---

<a id="jt_enable_storage"></a>

### `jt_enable_storage`

`function` | [src/js_trusted.c:488](../../src/js_trusted.c#L488)

```c
jd_status jt_enable_storage(js_context *ctx, const char *blob, size_t len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `blob` | `char *` |  |  |
| `len` | `size_t` |  |  |

**Returns:** `jd_status`

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw), [`wst_foreach`](src.web_storage.c.md#wst_foreach)

---

<a id="jt_take_storage"></a>

### `jt_take_storage`

`function` | [src/js_trusted.c:509](../../src/js_trusted.c#L509)

```c
int jt_take_storage(js_context *ctx, char **out, size_t *len)
```

When the store changed since the last call, returns 1 with an owned snapshot of the whole store in *out (length *len) and clears the dirty bit; 0 otherwise.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `out` | `char **` |  |  |
| `len` | `size_t *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`jt_take_storage`](#jt_take_storage) (include/js_trusted.h:104).

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw), [`wst_pack`](src.web_storage.c.md#wst_pack)

---

<a id="explicitly"></a>

### `explicitly`

`function` | [src/js_trusted.c:557](../../src/js_trusted.c#L557)

```c
* explicitly (no window, no document). Delivery is always a timer task. */ static const char JT_W...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `window` | `no` |  |  |
| `document` | `no` |  |  |

**Returns:** `*`

---

<a id="jt_enable_worker"></a>

### `jt_enable_worker`

`function` | [src/js_trusted.c:638](../../src/js_trusted.c#L638)

```c
jd_status jt_enable_worker(js_context *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `jd_status`

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw), [`js_install_realms`](src.js_sandbox.c.md#js_install_realms)

---

## Macros

<a id="jt_io_max_str"></a>

### `JT_IO_MAX_STR`

`macro` | [src/js_trusted.c:62](../../src/js_trusted.c#L62)

```c
#define JT_IO_MAX_STR
```

Real IntersectionObserver (spec/js_observers.md).

Entry state: -1 never reported, 0 outside, k>0 inside with k-1 = highest satisfied threshold index. Bounded.

---
