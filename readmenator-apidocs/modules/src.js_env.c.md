# `src/js_env.c`

> Source: [src/js_env.c:1](../../src/js_env.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`primitives`](#primitives), [`methods`](#methods), [`je_install`](#je_install), [`je_install_canvas`](#je_install_canvas)
- **Macros:** [`_POSIX_C_SOURCE`](#_posix_c_source), [`FP_MIME_COUNT`](#fp_mime_count), [`PERF_ORIGIN_EPOCH`](#perf_origin_epoch)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_js_env_c__je_install(["je_install"])
    n_src_js_sandbox_c__js_context_raw["js_sandbox.js_context_raw"]
    n_src_js_env_c__je_install_canvas(["je_install_canvas"])
    n_src_js_env_c__je_install -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_env_c__je_install_canvas -.-> n_src_js_sandbox_c__js_context_raw
```

## Functions

<a id="primitives"></a>

### `primitives`

`function` | [src/js_env.c:6](../../src/js_env.c#L6)

```c
* the pure anti_fp primitives (one audited source of normalized constants);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `constants` | `one audited source of normalized` |  |  |

**Returns:** `* the pure anti_fp`

---

<a id="methods"></a>

### `methods`

`function` | [src/js_env.c:201](../../src/js_env.c#L201)

```c
* capability methods (sendBeacon, spec/js_dom.md 7h) without touching any * fingerprintable field. An untrusted page's prototype stays empty. */ JSValue proto = JS_NewObject(ctx);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `spec/js_dom.md 7` |  |  |

**Returns:** `* capability`

---

<a id="je_install"></a>

### `je_install`

`function` | [src/js_env.c:497](../../src/js_env.c#L497)

```c
je_status je_install(js_context *ctx, int screen_w, int screen_h)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `screen_w` | `int` |  |  |
| `screen_h` | `int` |  |  |

**Returns:** `je_status`

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

*Called by:* [`run_js`](src.tab.c.md#run_js)

---

<a id="je_install_canvas"></a>

### `je_install_canvas`

`function` | [src/js_env.c:516](../../src/js_env.c#L516)

```c
je_status je_install_canvas(js_context *ctx, uint64_t readback_key)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `readback_key` | `uint64_t` |  |  |

**Returns:** `je_status`

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

*Called by:* [`run_js`](src.tab.c.md#run_js)

---

## Macros

<a id="_posix_c_source"></a>

### `_POSIX_C_SOURCE`

`macro` | [src/js_env.c:17](../../src/js_env.c#L17)

```c
#define _POSIX_C_SOURCE
```

---

<a id="fp_mime_count"></a>

### `FP_MIME_COUNT`

`macro` | [src/js_env.c:260](../../src/js_env.c#L260)

```c
#define FP_MIME_COUNT
```

---

<a id="perf_origin_epoch"></a>

### `PERF_ORIGIN_EPOCH`

`macro` | [src/js_env.c:344](../../src/js_env.c#L344)

```c
#define PERF_ORIGIN_EPOCH
```

---
