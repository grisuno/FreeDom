# `include/js_intl.h`

> Source: [include/js_intl.h:1](../../include/js_intl.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

## Contents

- **Functions:** [`ji_install`](#ji_install)

## Functions

<a id="ji_install"></a>

### `ji_install`

`function` | [include/js_intl.h:16](../../include/js_intl.h#L16)

```c
int ji_install(js_context *ctx);
```

Installs `Intl` and the Number/BigInt/Date toLocale* methods that delegate to it.

Returns 0, or -1 on a NULL context or an engine failure.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `int`

---
