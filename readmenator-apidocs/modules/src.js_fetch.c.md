# `src/js_fetch.c`

> Source: [src/js_fetch.c:1](../../src/js_fetch.c#L1) | language `c` | coverage 20.0% | [API index](../index.md)

## Contents

- **Functions:** [`send`](#send), [`task`](#task), [`jd_install_xhr`](#jd_install_xhr)
- **Macros:** [`_GNU_SOURCE`](#_gnu_source)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_js_fetch_c__jd_install_xhr(["jd_install_xhr"])
    n_src_js_sandbox_c__js_context_raw["js_sandbox.js_context_raw"]
    n_src_js_fetch_c__jd_install_xhr -.-> n_src_js_sandbox_c__js_context_raw
```

## Functions

<a id="send"></a>

### `send`

`function` | [src/js_fetch.c:92](../../src/js_fetch.c#L92)

```c
* callbacks fire right after send();
```

**Returns:** `* callbacks fire right after`

---

<a id="task"></a>

### `task`

`function` | [src/js_fetch.c:179](../../src/js_fetch.c#L179)

```c
* current task (the page never waits on it);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `it` | `the page never waits on` |  |  |

**Returns:** `* current`

---

<a id="jd_install_xhr"></a>

### `jd_install_xhr`

`function` | [src/js_fetch.c:197](../../src/js_fetch.c#L197)

```c
jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `fn` | `jd_fetch_fn` |  |  |
| `fetch_ctx` | `void *` |  |  |

**Returns:** `jd_status`

*Calls:* [`js_context_raw`](src.js_sandbox.c.md#js_context_raw)

*Called by:* [`run_js`](src.tab.c.md#run_js)

---

## Macros

<a id="_gnu_source"></a>

### `_GNU_SOURCE`

`macro` | [src/js_fetch.c:6](../../src/js_fetch.c#L6)

```c
#define _GNU_SOURCE
```

js_fetch.c -- XMLHttpRequest / fetch over the parent-gated host call (allow∩js only).

Split out of js_dom.c (anti-monolith clause, CLAUDE.md 3.4); contract in include/js_dom.h and spec/js_dom.md.

---
