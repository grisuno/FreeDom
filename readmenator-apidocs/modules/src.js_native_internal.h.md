# `src/js_native_internal.h`

> Source: [src/js_native_internal.h:1](../../src/js_native_internal.h#L1) | language `h` | coverage 33.3% | [API index](../index.md)

## Contents

- **Structs:** [`js_context`](#js_context)
- **Functions:** [`js_host_slot`](#js_host_slot)

## Structs

<a id="js_context"></a>

### `js_context`

`struct` | [src/js_native_internal.h:20](../../src/js_native_internal.h#L20)

```c
struct js_context;
```

One engine value the host keeps for the lifetime of a context, out of the page's reach (it is not a property of anything).

JS_UNDEFINED until set; the context frees it. Implemented in js_sandbox.c, which owns the context. NULL for a NULL context.

---

## Functions

<a id="js_host_slot"></a>

### `js_host_slot`

`function` | [src/js_native_internal.h:21](../../src/js_native_internal.h#L21)

```c
JSValue *js_host_slot(struct js_context *ctx);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `struct js_context *` |  |  |

**Returns:** `JSValue *`

*Called by:* [`jn_seal`](src.js_native.c.md#jn_seal)

---
