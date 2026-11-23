# `src/js_dom_ext.c`

> Source: [src/js_dom_ext.c:1](../../src/js_dom_ext.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`identity`](#identity), [`registration`](#registration), [`cancels`](#cancels), [`order`](#order), [`jdx_install`](#jdx_install), [`jd_install_repl_api`](#jd_install_repl_api), [`jd_set_repl_css`](#jd_set_repl_css), [`jd_install_geolocation`](#jd_install_geolocation), [`jd_install_indexeddb`](#jd_install_indexeddb)

## Functions

<a id="identity"></a>

### `identity`

`function` | [src/js_dom_ext.c:105](../../src/js_dom_ext.c#L105)

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

`function` | [src/js_dom_ext.c:482](../../src/js_dom_ext.c#L482)

```c
* registration (options, attributeFilter, subtree) and delivered in one microtask. An * observer...
```

**Returns:** `*`

---

<a id="cancels"></a>

### `cancels`

`function` | [src/js_dom_ext.c:1001](../../src/js_dom_ext.c#L1001)

```c
* toggled BEFORE the dispatch and restored when a listener cancels (legacy pre-activation);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `activation` | `legacy pre-` |  |  |

**Returns:** `* toggled BEFORE the dispatch and restored when a listener`

---

<a id="order"></a>

### `order`

`function` | [src/js_dom_ext.c:1363](../../src/js_dom_ext.c#L1363)

```c
* run in insertion order (HTML's "list of scripts that will execute in order as soon as * possible"). Modules go through import(). A throw is reported like any uncaught * error and never propagates into the inserting script. Bounds: 4096 started scripts. */ static const char JDX_DYNSCRIPT_SHIM[] = "(function()
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `possible` | `HTML's "list of scripts that will execute in order as soon as * "` |  |  |

**Returns:** `* run in insertion`

---

<a id="jdx_install"></a>

### `jdx_install`

`function` | [src/js_dom_ext.c:1429](../../src/js_dom_ext.c#L1429)

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

`function` | [src/js_dom_ext.c:1438](../../src/js_dom_ext.c#L1438)

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

`function` | [src/js_dom_ext.c:1446](../../src/js_dom_ext.c#L1446)

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

`function` | [src/js_dom_ext.c:1459](../../src/js_dom_ext.c#L1459)

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

`function` | [src/js_dom_ext.c:1478](../../src/js_dom_ext.c#L1478)

```c
jd_status jd_install_indexeddb(js_context *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `jd_status`

---
