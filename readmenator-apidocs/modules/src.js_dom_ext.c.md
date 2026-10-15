# `src/js_dom_ext.c`

> Source: [src/js_dom_ext.c:1](../../src/js_dom_ext.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`identity`](#identity), [`jdx_install`](#jdx_install)

## Functions

<a id="identity"></a>

### `identity`

`function` | [src/js_dom_ext.c:96](../../src/js_dom_ext.c#L96)

```c
* identity (host/shadowRoot/mode preserved) but every mutation ALSO mirrors * into the host's light DOM via dom.*, so the next pv_build_styled paints it. * innerHTML/textContent append (never replace
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `preserved` | `host/shadowRoot/mode` |  |  |

**Returns:** `*`

---

<a id="jdx_install"></a>

### `jdx_install`

`function` | [src/js_dom_ext.c:374](../../src/js_dom_ext.c#L374)

```c
int jdx_install(JSContext *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `JSContext *` |  |  |

**Returns:** `int`

---
