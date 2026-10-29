# `src/js_dom_ext.c`

> Source: [src/js_dom_ext.c:1](../../src/js_dom_ext.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`identity`](#identity), [`registration`](#registration), [`jdx_install`](#jdx_install), [`jd_install_repl_api`](#jd_install_repl_api), [`jd_set_repl_css`](#jd_set_repl_css), [`jd_install_geolocation`](#jd_install_geolocation), [`jd_install_indexeddb`](#jd_install_indexeddb)

## Functions

<a id="identity"></a>

### `identity`

`function` | [src/js_dom_ext.c:104](../../src/js_dom_ext.c#L104)

```c
* identity (host/shadowRoot/mode preserved) but every mutation ALSO mirrors * into the host's light DOM via dom.*, so the next pv_build_styled paints it. * innerHTML/textContent append (never replace
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `preserved` | `host/shadowRoot/mode` |  |  |

**Returns:** `*`

---

<a id="registration"></a>

### `registration`

`function` | [src/js_dom_ext.c:481](../../src/js_dom_ext.c#L481)

```c
* registration (options, attributeFilter, subtree) and delivered in one microtask. An * observer...
```

**Returns:** `*`

---

<a id="jdx_install"></a>

### `jdx_install`

`function` | [src/js_dom_ext.c:1330](../../src/js_dom_ext.c#L1330)

```c
int jdx_install(JSContext *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `JSContext *` |  |  |

**Returns:** `int`

---

<a id="jd_install_repl_api"></a>

### `jd_install_repl_api`

`function` | [src/js_dom_ext.c:1339](../../src/js_dom_ext.c#L1339)

```c
jd_status jd_install_repl_api(js_context *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `jd_status`

---

<a id="jd_set_repl_css"></a>

### `jd_set_repl_css`

`function` | [src/js_dom_ext.c:1347](../../src/js_dom_ext.c#L1347)

```c
jd_status jd_set_repl_css(js_context *ctx, const char *css, size_t len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `css` | `char *` |  |  |
| `len` | `size_t` |  |  |

**Returns:** `jd_status`

---

<a id="jd_install_geolocation"></a>

### `jd_install_geolocation`

`function` | [src/js_dom_ext.c:1360](../../src/js_dom_ext.c#L1360)

```c
jd_status jd_install_geolocation(js_context *ctx, double lat, double lon, double accuracy_m)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `lat` | `double` |  |  |
| `lon` | `double` |  |  |
| `accuracy_m` | `double` |  |  |

**Returns:** `jd_status`

---

<a id="jd_install_indexeddb"></a>

### `jd_install_indexeddb`

`function` | [src/js_dom_ext.c:1379](../../src/js_dom_ext.c#L1379)

```c
jd_status jd_install_indexeddb(js_context *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `jd_status`

---
