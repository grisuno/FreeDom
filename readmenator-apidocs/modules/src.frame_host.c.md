# `src/frame_host.c`

> Source: [src/frame_host.c:1](../../src/frame_host.c#L1) | language `c` | coverage 70.0% | [API index](../index.md)

## Contents

- **Structs:** [`fh_slot`](#fh_slot), [`fh_host`](#fh_host)
- **Functions:** [`fh_new`](#fh_new), [`fh_free`](#fh_free), [`fh_count`](#fh_count), [`fh_apply_top`](#fh_apply_top), [`fh_tick`](#fh_tick), [`fh_generation`](#fh_generation), [`fh_frame_view`](#fh_frame_view)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class fh_slot
    <<struct>> fh_slot
    class fh_host
    <<struct>> fh_host
```

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_frame_host_c__fh_new(["fh_new"])
    n_include_frame_broker_h__fbk_init["frame_broker.fbk_init"]
    n_src_frame_host_c__fh_tick(["fh_tick"])
    n_include_frame_broker_h__fbk_origin["frame_broker.fbk_origin"]
    n_src_tab_c__tab_tick["tab.tab_tick"]
    n_src_frame_host_c__fh_frame_view(["fh_frame_view"])
    n_gui_browser_ui_c__strcmp["browser_ui.strcmp"]
    n_src_frame_host_c__fh_new -.-> n_include_frame_broker_h__fbk_init
    n_src_frame_host_c__fh_tick -.-> n_include_frame_broker_h__fbk_origin
    n_src_frame_host_c__fh_tick -.-> n_src_tab_c__tab_tick
    n_src_frame_host_c__fh_frame_view -.-> n_gui_browser_ui_c__strcmp
```

## Structs

<a id="fh_slot"></a>

### `fh_slot`

`struct` | [src/frame_host.c:14](../../src/frame_host.c#L14)

```c
typedef struct fh_slot
```

---

<a id="fh_host"></a>

### `fh_host`

`struct` | [src/frame_host.c:22](../../src/frame_host.c#L22)

```c
struct fh_host
```

---

## Functions

<a id="fh_new"></a>

### `fh_new`

`function` | [src/frame_host.c:35](../../src/frame_host.c#L35)

```c
fh_host *fh_new(const char *top_url, tab_fetch_fn fetch, void *fetch_ctx, fh_top_msg_fn top_msg, void *top_ctx)
```

top_url: the trusted top document; fetch/fetch_ctx: the page's policy-gated subresource fetcher (used for the frame document and handed to each frame worker for its own XHR/fetch).

NULL on OOM or bad args.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `top_url` | `char *` |  |  |
| `fetch` | `tab_fetch_fn` |  |  |
| `fetch_ctx` | `void *` |  |  |
| `top_msg` | `fh_top_msg_fn` |  |  |
| `top_ctx` | `void *` |  |  |

**Returns:** `fh_host *`

> **Inherited:** Documentation from [`fh_new`](#fh_new) (include/frame_host.h:28).

*Calls:* [`fbk_init`](include.frame_broker.h.md#fbk_init)

---

<a id="fh_free"></a>

### `fh_free`

`function` | [src/frame_host.c:67](../../src/frame_host.c#L67)

```c
void fh_free(fh_host *h)
```

Closes every frame worker and frees the host.

Idempotent on NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `fh_host *` |  |  |

> **Inherited:** Documentation from [`fh_free`](#fh_free) (include/frame_host.h:32).

---

<a id="fh_count"></a>

### `fh_count`

`function` | [src/frame_host.c:76](../../src/frame_host.c#L76)

```c
int fh_count(const fh_host *h)
```

Number of live frame workers (excludes the top).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `fh_host *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`fh_count`](#fh_count) (include/frame_host.h:43).

---

<a id="fh_apply_top"></a>

### `fh_apply_top`

`function` | [src/frame_host.c:221](../../src/frame_host.c#L221)

```c
void fh_apply_top(fh_host *h, const tab_page *page)
```

Processes the frame ops (kinds FRAME_OPEN/CLOSE/POST) among page->ws of the TOP document; other kinds are ignored.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `fh_host *` |  |  |
| `page` | `tab_page *` |  |  |

> **Inherited:** Documentation from [`fh_apply_top`](#fh_apply_top) (include/frame_host.h:36).

---

<a id="fh_tick"></a>

### `fh_tick`

`function` | [src/frame_host.c:226](../../src/frame_host.c#L226)

```c
int fh_tick(fh_host *h, int elapsed_ms)
```

Advances every frame's virtual clock by elapsed_ms and processes what they posted.

Returns the smallest pending frame timer in ms, or -1 when none.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `fh_host *` |  |  |
| `elapsed_ms` | `int` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`fh_tick`](#fh_tick) (include/frame_host.h:40).

*Calls:* [`fbk_origin`](include.frame_broker.h.md#fbk_origin), [`tab_tick`](src.tab.c.md#tab_tick)

---

<a id="fh_generation"></a>

### `fh_generation`

`function` | [src/frame_host.c:250](../../src/frame_host.c#L250)

```c
unsigned fh_generation(const fh_host *h)
```

Changes whenever any frame view appears, is replaced or goes away: repaint the frames then.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `fh_host *` |  |  |

**Returns:** `unsigned`

> **Inherited:** Documentation from [`fh_generation`](#fh_generation) (include/frame_host.h:52).

---

<a id="fh_frame_view"></a>

### `fh_frame_view`

`function` `const` | [src/frame_host.c:252](../../src/frame_host.c#L252)

```c
const pv_view *fh_frame_view(const fh_host *h, const char *url, tab **t_out)
```

Painting (spec/frame_broker.md section 5).

The document of the frame loaded from [`url`](include.url.h.md#url), as its confined worker last built it (NULL when no live frame has that URL); *t_out (optional) is that worker, which decodes the frame's own images. Both stay owned by the host and are valid until the next fh_apply_top/fh_tick/fh_free.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `fh_host *` |  |  |
| `url` | `char *` |  |  |
| `t_out` | `tab **` |  |  |

**Returns:** `pv_view *`

> **Inherited:** Documentation from [`fh_frame_view`](#fh_frame_view) (include/frame_host.h:49).

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp)

---
