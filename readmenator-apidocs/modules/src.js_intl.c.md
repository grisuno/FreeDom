# `src/js_intl.c`

> Source: [src/js_intl.c:1](../../src/js_intl.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

## Contents

- **Functions:** [`ji_install`](#ji_install)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_js_intl_c__ji_install(["ji_install"])
    n_src_js_sandbox_c__js_context_raw["js_sandbox.js_context_raw"]
    n_src_js_intl_c__ji_install -.-> n_src_js_sandbox_c__js_context_raw
```

## Functions

<a id="ji_install"></a>

### `ji_install`

`function` | [src/js_intl.c:423](../../src/js_intl.c#L423)

```c
int ji_install(js_context *ctx)
```

Installs `Intl` and the Number/BigInt/Date toLocale* methods that delegate to it.

Returns 0, or -1 on a NULL context or an engine failure.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`ji_install`](#ji_install) (include/js_intl.h:16).

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

---
