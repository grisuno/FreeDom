# `src/js_location_internal.h`

> Source: [src/js_location_internal.h:1](../../src/js_location_internal.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

Private to js_dom.c / js_location.c: the dom.histTarget native lives with the

## Contents

- **Functions:** [`header`](#header)

## Functions

<a id="header"></a>

### `header`

`function` | [src/js_location_internal.h:6](../../src/js_location_internal.h#L6)

```c
* stay out of every public header (include/ never sees quickjs.h). */ #include "quickjs.h" JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `include/ never sees quickjs.` |  |  |

**Returns:** `* stay out of every`

---
