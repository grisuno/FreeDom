# `src/js_dom_internal.h`

> Source: [src/js_dom_internal.h:1](../../src/js_dom_internal.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

Private to the js_dom family (js_dom.c, js_fetch.c, js_events.c, js_embed.c): the context accessors every native needs.

Engine types stay out of include/.

## Contents

- **Functions:** [`jd_opaque_get`](#jd_opaque_get), [`jd_idx`](#jd_idx), [`jd_handle`](#jd_handle)

## Functions

<a id="jd_opaque_get"></a>

### `jd_opaque_get`

`function` | [src/js_dom_internal.h:11](../../src/js_dom_internal.h#L11)

```c
jd_opaque *jd_opaque_get(JSContext *ctx);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `JSContext *` |  |  |

**Returns:** `jd_opaque *`

*Called by:* [`jd_install_events`](src.js_events.c.md#jd_install_events)

---

<a id="jd_idx"></a>

### `jd_idx`

`function` | [src/js_dom_internal.h:12](../../src/js_dom_internal.h#L12)

```c
dom_index *jd_idx(JSContext *ctx);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `JSContext *` |  |  |

**Returns:** `dom_index *`

---

<a id="jd_handle"></a>

### `jd_handle`

`function` | [src/js_dom_internal.h:14](../../src/js_dom_internal.h#L14)

```c
int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out);
```

Coerces a JS argument to a node handle; -1 with a pending exception if it threw.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `JSContext *` |  |  |
| `v` | `JSValueConst` |  |  |
| `out` | `dom_node_id *` |  |  |

**Returns:** `int`

---
