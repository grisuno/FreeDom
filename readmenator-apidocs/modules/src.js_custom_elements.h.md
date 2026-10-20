# `src/js_custom_elements.h`

> Source: [src/js_custom_elements.h:1](../../src/js_custom_elements.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

Private to js_dom.c: installs Custom Elements v1 (spec/js_custom_elements.md) on top of the document facade.

Returns 0 or -1.

## Contents

- **Functions:** [`jdce_install`](#jdce_install)

## Functions

<a id="jdce_install"></a>

### `jdce_install`

`function` | [src/js_custom_elements.h:9](../../src/js_custom_elements.h#L9)

```c
int jdce_install(JSContext *ctx);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `JSContext *` |  |  |

**Returns:** `int`

---
