# `src/prefetch.c`

> Source: [src/prefetch.c:1](../../src/prefetch.c#L1) | language `c` | coverage 42.9% | [API index](../index.md)

## Contents

- **Structs:** [`attr_span`](#attr_span)
- **Functions:** [`pf_scan`](#pf_scan), [`pf_list_free`](#pf_list_free), [`pf_scan_imports`](#pf_scan_imports), [`pf_pool_add`](#pf_pool_add), [`pf_pool_start`](#pf_pool_start), [`pf_pool_take`](#pf_pool_take), [`pf_find_importmap`](#pf_find_importmap), [`pf_pool_start_page`](#pf_pool_start_page), [`pf_pool_finish`](#pf_pool_finish), [`pf_pooled_fetch`](#pf_pooled_fetch)
- **Macros:** [`_POSIX_C_SOURCE`](#_posix_c_source), [`PF_MAX_URL`](#pf_max_url)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_prefetch_c__pf_pool_start_page(["pf_pool_start_page"])
    n_src_prefetch_c__pf_find_importmap(["pf_find_importmap"])
    n_src_prefetch_c__pf_list_free(["pf_list_free"])
    n_src_prefetch_c__pf_scan(["pf_scan"])
    n_src_prefetch_c__pf_pooled_fetch(["pf_pooled_fetch"])
    n_src_prefetch_c__pf_pool_take(["pf_pool_take"])
    n_src_css_c__emit["css.emit"]
    n_src_prefetch_c__pf_pool_add(["pf_pool_add"])
    n_gui_browser_ui_c__strcmp["browser_ui.strcmp"]
    n_include_import_map_h__im_free["import_map.im_free"]
    n_src_import_map_c__im_parse["import_map.im_parse"]
    n_src_prefetch_c__pf_pool_finish(["pf_pool_finish"])
    n_src_prefetch_c__pf_pool_start_page --> n_src_prefetch_c__pf_find_importmap
    n_src_prefetch_c__pf_pool_start_page --> n_src_prefetch_c__pf_list_free
    n_src_prefetch_c__pf_pool_start_page --> n_src_prefetch_c__pf_scan
    n_src_prefetch_c__pf_pooled_fetch --> n_src_prefetch_c__pf_pool_take
    n_src_prefetch_c__pf_scan -.-> n_src_css_c__emit
    n_src_prefetch_c__pf_pool_add -.-> n_gui_browser_ui_c__strcmp
    n_src_prefetch_c__pf_pool_take -.-> n_gui_browser_ui_c__strcmp
    n_src_prefetch_c__pf_pool_start_page -.-> n_include_import_map_h__im_free
    n_src_prefetch_c__pf_pool_start_page -.-> n_src_import_map_c__im_parse
    n_src_prefetch_c__pf_pool_finish -.-> n_include_import_map_h__im_free
    n_src_prefetch_c__pf_pooled_fetch -.-> n_gui_browser_ui_c__strcmp
```

## Structs

<a id="attr_span"></a>

### `attr_span`

`struct` | [src/prefetch.c:65](../../src/prefetch.c#L65)

```c
typedef struct attr_span
```

---

## Functions

<a id="pf_scan"></a>

### `pf_scan`

`function` | [src/prefetch.c:133](../../src/prefetch.c#L133)

```c
int pf_scan(const char *html, size_t len, pf_list *out)
```

Lookahead scan of hostile HTML.

Fills out (owns the URLs; free with pf_list_free). Comment, <script> and <style> contents are opaque; a <link> whose rel list lacks the "stylesheet" token is ignored (fail closed). Returns 0 (even with zero refs) or -1 on NULL arguments. Never performs I/O.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `html` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `out` | `pf_list *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`pf_scan`](#pf_scan) (include/prefetch.h:62).

*Calls:* [`emit`](src.css.c.md#emit)

*Called by:* [`pf_pool_start_page`](#pf_pool_start_page)

---

<a id="pf_list_free"></a>

### `pf_list_free`

`function` | [src/prefetch.c:196](../../src/prefetch.c#L196)

```c
void pf_list_free(pf_list *l)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `l` | `pf_list *` |  |  |

*Called by:* [`pf_pool_start_page`](#pf_pool_start_page)

---

<a id="pf_scan_imports"></a>

### `pf_scan_imports`

`function` | [src/prefetch.c:241](../../src/prefetch.c#L241)

```c
size_t pf_scan_imports(const char *js, size_t len, char (*out)[PF_SPEC_MAX], size_t cap)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `js` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `PF_SPEC_MAX` | `char (*out)[ ]` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

---

<a id="pf_pool_add"></a>

### `pf_pool_add`

`function` | [src/prefetch.c:288](../../src/prefetch.c#L288)

```c
int pf_pool_add(pf_pool *p, const char *url)
```

Queues one more URL on a started pool (deduplicated, bounded by PF_MAX_JOBS).

Returns 1 when added, 0 when already known, full, or the pool is not running.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `p` | `pf_pool *` |  |  |
| `url` | `char *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`pf_pool_add`](#pf_pool_add) (include/prefetch.h:127).

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp)

---

<a id="pf_pool_start"></a>

### `pf_pool_start`

`function` | [src/prefetch.c:387](../../src/prefetch.c#L387)

```c
int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls, pf_fetch_fn fetch, void *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `p` | `pf_pool *` |  |  |
| `urls` | `char *const *` |  |  |
| `nurls` | `size_t` |  |  |
| `fetch` | `pf_fetch_fn` |  |  |
| `ctx` | `void *` |  |  |

**Returns:** `int`

---

<a id="pf_pool_take"></a>

### `pf_pool_take`

`function` | [src/prefetch.c:444](../../src/prefetch.c#L444)

```c
int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status, char **body, size_t *len, char **ctype)
```

Cache-first take.

On a hit (url matches an unconsumed job) WAITS for that job and MOVES the result to the caller: *rc is the callback's return value and, when *rc == 0, the caller owns the returned body and ctype. Returns 1 on hit, 0 on miss (unknown or already-consumed URL, pool not started): the caller then fetches directly. A fetch failure is a hit with *rc != 0 -- the caller must NOT retry (same outcome as the serial path, without duplicating requests). Single owner: a second take of the same URL is a miss.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `p` | `pf_pool *` |  |  |
| `url` | `char *` |  |  |
| `rc` | `int *` |  |  |
| `status` | `int *` |  |  |
| `body` | `char **` |  |  |
| `len` | `size_t *` |  |  |
| `ctype` | `char **` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`pf_pool_take`](#pf_pool_take) (include/prefetch.h:145).

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp)

*Called by:* [`pf_pooled_fetch`](#pf_pooled_fetch)

---

<a id="pf_find_importmap"></a>

### `pf_find_importmap`

`function` | [src/prefetch.c:483](../../src/prefetch.c#L483)

```c
int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n)
```

Span of the first <script type=importmap> body in html (pure, bounded): 1 with [*start, *start + *n) set, or 0 when there is none.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `html` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `start` | `size_t *` |  |  |
| `n` | `size_t *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`pf_find_importmap`](#pf_find_importmap) (include/prefetch.h:115).

*Called by:* [`pf_pool_start_page`](#pf_pool_start_page)

---

<a id="pf_pool_start_page"></a>

### `pf_pool_start_page`

`function` | [src/prefetch.c:504](../../src/prefetch.c#L504)

```c
int pf_pool_start_page(pf_pool *p, const char *html, size_t len, const char *page_url, int css_grant, int js_grant, pf_fetch_fn fetch, void *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `p` | `pf_pool *` |  |  |
| `html` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `page_url` | `char *` |  |  |
| `css_grant` | `int` |  |  |
| `js_grant` | `int` |  |  |
| `fetch` | `pf_fetch_fn` |  |  |
| `ctx` | `void *` |  |  |

**Returns:** `int`

*Calls:* [`im_free`](include.import_map.h.md#im_free), [`im_parse`](src.import_map.c.md#im_parse), [`pf_find_importmap`](#pf_find_importmap), [`pf_list_free`](#pf_list_free), [`pf_scan`](#pf_scan)

---

<a id="pf_pool_finish"></a>

### `pf_pool_finish`

`function` | [src/prefetch.c:540](../../src/prefetch.c#L540)

```c
void pf_pool_finish(pf_pool *p)
```

Joins the worker threads and frees every unconsumed result.

Blocks until in-flight fetches end (bounded by the fetcher's timeouts). Idempotent; after finish, take always misses.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `p` | `pf_pool *` |  |  |

> **Inherited:** Documentation from [`pf_pool_finish`](#pf_pool_finish) (include/prefetch.h:151).

*Calls:* [`im_free`](include.import_map.h.md#im_free)

---

<a id="pf_pooled_fetch"></a>

### `pf_pooled_fetch`

`function` | [src/prefetch.c:561](../../src/prefetch.c#L561)

```c
int pf_pooled_fetch(void *vctx, const char *method, const char *url, const char *body, size_t body_len, int *out_status, char **out_body, size_t *out_len, char **out_ctype)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vctx` | `void *` |  |  |
| `method` | `char *` |  |  |
| `url` | `char *` |  |  |
| `body` | `char *` |  |  |
| `body_len` | `size_t` |  |  |
| `out_status` | `int *` |  |  |
| `out_body` | `char **` |  |  |
| `out_len` | `size_t *` |  |  |
| `out_ctype` | `char **` |  |  |

**Returns:** `int`

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp), [`pf_pool_take`](#pf_pool_take)

---

## Macros

<a id="_posix_c_source"></a>

### `_POSIX_C_SOURCE`

`macro` | [src/prefetch.c:12](../../src/prefetch.c#L12)

```c
#define _POSIX_C_SOURCE
```

---

<a id="pf_max_url"></a>

### `PF_MAX_URL`

`macro` | [src/prefetch.c:24](../../src/prefetch.c#L24)

```c
#define PF_MAX_URL
```

Longest raw reference the scanner keeps; matches URL_MAX_LEN (url.h) so a ref the fetch path would reject on length is never even queued.

---
