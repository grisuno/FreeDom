# `src/js_location.c`

> Source: [src/js_location.c:1](../../src/js_location.c#L1) | language `c` | coverage 33.3% | [API index](../index.md)

## Contents

- **Functions:** [`jl_m_hist_target`](#jl_m_hist_target), [`jd_set_location`](#jd_set_location), [`jd_take_nav_request`](#jd_take_nav_request), [`numbers`](#numbers), [`jd_take_scroll`](#jd_take_scroll), [`jd_take_history`](#jd_take_history), [`jd_frag_push`](#jd_frag_push), [`jd_pop_state`](#jd_pop_state)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_js_location_c__jl_m_hist_target(["jl_m_hist_target"])
    n_src_url_c__url_history_target["url.url_history_target"]
    n_src_url_c__url_split_location["url.url_split_location"]
    n_src_js_location_c__jd_set_location(["jd_set_location"])
    n_src_js_native_c__jn_host_eval["js_native.jn_host_eval"]
    n_src_js_sandbox_c__js_context_raw["js_sandbox.js_context_raw"]
    n_src_js_location_c__jd_take_nav_request(["jd_take_nav_request"])
    n_src_js_location_c__jd_take_scroll(["jd_take_scroll"])
    n_src_js_location_c__jd_take_history(["jd_take_history"])
    n_src_js_location_c__jd_frag_push(["jd_frag_push"])
    n_src_js_location_c__jd_pop_state(["jd_pop_state"])
    n_src_js_location_c__jl_m_hist_target -.-> n_src_url_c__url_history_target
    n_src_js_location_c__jl_m_hist_target -.-> n_src_url_c__url_split_location
    n_src_js_location_c__jd_set_location -.-> n_src_js_native_c__jn_host_eval
    n_src_js_location_c__jd_set_location -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_location_c__jd_take_nav_request -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_location_c__jd_take_scroll -.-> n_src_js_native_c__jn_host_eval
    n_src_js_location_c__jd_take_scroll -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_location_c__jd_take_history -.-> n_src_js_native_c__jn_host_eval
    n_src_js_location_c__jd_take_history -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_location_c__jd_frag_push -.-> n_src_js_sandbox_c__js_context_raw
    n_src_js_location_c__jd_pop_state -.-> n_src_js_native_c__jn_host_eval
    n_src_js_location_c__jd_pop_state -.-> n_src_js_sandbox_c__js_context_raw
```

## Functions

<a id="jl_m_hist_target"></a>

### `jl_m_hist_target`

`function` | [src/js_location.c:36](../../src/js_location.c#L36)

```c
JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
```

dom.histTarget(base, ref): the same-origin target of history.pushState/replaceState (url_history_target) as a location-parts object {href, protocol, origin, host, hostname, port, pathname, search, hash}, or null when ref is cross-origin, not resolvable, or carries a control character (it will travel as one line to the parent).

A file:// target yields {href} only, like the location it replaces.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `JSContext *` |  |  |
| `this_val` | `JSValueConst` |  |  |
| `argc` | `int` |  |  |
| `argv` | `JSValueConst *` |  |  |

**Returns:** `JSValue`

*Calls:* [`url_history_target`](src.url.c.md#url_history_target), [`url_split_location`](src.url.c.md#url_split_location)

---

<a id="jd_set_location"></a>

### `jd_set_location`

`function` | [src/js_location.c:160](../../src/js_location.c#L160)

```c
jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `href` | `char *` |  |  |
| `parts` | `url_parts *` |  |  |

**Returns:** `jd_status`

*Calls:* [`jn_host_eval`](src.js_native.c.md#jn_host_eval), [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_js_dom.c.md#llvmfuzzertestoneinput)

---

<a id="jd_take_nav_request"></a>

### `jd_take_nav_request`

`function` | [src/js_location.c:194](../../src/js_location.c#L194)

```c
int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `buf` | `char *` |  |  |
| `bufsz` | `size_t` |  |  |
| `replace` | `int *` |  |  |

**Returns:** `int`

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

---

<a id="numbers"></a>

### `numbers`

`function` | [src/js_location.c:233](../../src/js_location.c#L233)

```c
* numbers (never as source);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `source` | `never as` |  |  |

**Returns:** `*`

---

<a id="jd_take_scroll"></a>

### `jd_take_scroll`

`function` | [src/js_location.c:237](../../src/js_location.c#L237)

```c
int jd_take_scroll(js_context *ctx, double out[JD_SCROLL_N])
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `JD_SCROLL_N` | `double out[ ]` |  |  |

**Returns:** `int`

*Calls:* [`jn_host_eval`](src.js_native.c.md#jn_host_eval), [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

---

<a id="jd_take_history"></a>

### `jd_take_history`

`function` | [src/js_location.c:272](../../src/js_location.c#L272)

```c
char *jd_take_history(js_context *ctx, int *go)
```

Drains the history operations page JS performed since the last call: an owned string of lines "P <url>\n" (pushState) / "R <url>\n" (replaceState), URLs absolute and already same-origin-checked by the worker (the parent re-checks), or NULL when there were none. *go (optional) receives the net history.back/forward/go delta, also cleared.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `go` | `int *` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`jd_take_history`](#jd_take_history) (include/js_location.h:38).

*Calls:* [`jn_host_eval`](src.js_native.c.md#jn_host_eval), [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

---

<a id="jd_frag_push"></a>

### `jd_frag_push`

`function` | [src/js_location.c:303](../../src/js_location.c#L303)

```c
int jd_frag_push(js_context *ctx, const char *url, int replace)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `url` | `char *` |  |  |
| `replace` | `int` |  |  |

**Returns:** `int`

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

*Called by:* [`navigation`](src.tab.c.md#navigation)

---

<a id="jd_pop_state"></a>

### `jd_pop_state`

`function` | [src/js_location.c:327](../../src/js_location.c#L327)

```c
int jd_pop_state(js_context *ctx, int index)
```

Moves the page's history to entry index (the parent went Back/Forward within the same document): updates location and dispatches popstate (and hashchange when only the fragment changed) on window.

Returns 1 when applied, 0 when index is out of range or no location is installed.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `index` | `int` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`jd_pop_state`](#jd_pop_state) (include/js_location.h:44).

*Calls:* [`jn_host_eval`](src.js_native.c.md#jn_host_eval), [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

---
