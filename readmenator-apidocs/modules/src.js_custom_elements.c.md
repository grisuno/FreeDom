# `src/js_custom_elements.c`

> Source: [src/js_custom_elements.c:1](../../src/js_custom_elements.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`jdce_install`](#jdce_install)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_js_custom_elements_c__jdce_install(["jdce_install"])
    n_src_js_native_c__jn_host_eval["js_native.jn_host_eval"]
    n_src_js_custom_elements_c__jdce_install -.-> n_src_js_native_c__jn_host_eval
```

## Functions

<a id="jdce_install"></a>

### `jdce_install`

`function` | [src/js_custom_elements.c:200](../../src/js_custom_elements.c#L200)

```c
int jdce_install(JSContext *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `JSContext *` |  |  |

**Returns:** `int`

*Calls:* [`jn_host_eval`](src.js_native.c.md#jn_host_eval)

---
