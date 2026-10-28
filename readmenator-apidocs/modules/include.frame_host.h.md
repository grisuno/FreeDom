# `include/frame_host.h`

> Source: [include/frame_host.h:1](../../include/frame_host.h#L1) | language `h` | coverage 72.7% | [API index](../index.md)

## Contents

- **Type Aliases:** [`fh_host`](#fh_host)
- **Functions:** [`fh_new`](#fh_new), [`fh_free`](#fh_free), [`fh_apply_top`](#fh_apply_top), [`fh_tick`](#fh_tick), [`fh_count`](#fh_count), [`it`](#it), [`fh_frame_view`](#fh_frame_view), [`fh_generation`](#fh_generation)
- **Macros:** [`FH_MAX_DEPTH`](#fh_max_depth)

## Type Aliases

<a id="fh_host"></a>

### `fh_host`

`type_alias` | [include/frame_host.h:19](../../include/frame_host.h#L19)

```c
typedef struct fh_host fh_host;
```

nested deliveries handled inside one call; the rest waits for a tick

---

## Functions

<a id="fh_new"></a>

### `fh_new`

`function` | [include/frame_host.h:28](../../include/frame_host.h#L28)

```c
fh_host *fh_new(const char *top_url, tab_fetch_fn fetch, void *fetch_ctx, fh_top_msg_fn top_msg, void *top_ctx);
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

---

<a id="fh_free"></a>

### `fh_free`

`function` | [include/frame_host.h:32](../../include/frame_host.h#L32)

```c
void fh_free(fh_host *h);
```

Closes every frame worker and frees the host.

Idempotent on NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `fh_host *` |  |  |

---

<a id="fh_apply_top"></a>

### `fh_apply_top`

`function` | [include/frame_host.h:36](../../include/frame_host.h#L36)

```c
void fh_apply_top(fh_host *h, const tab_page *page);
```

Processes the frame ops (kinds FRAME_OPEN/CLOSE/POST) among page->ws of the TOP document; other kinds are ignored.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `fh_host *` |  |  |
| `page` | `tab_page *` |  |  |

---

<a id="fh_tick"></a>

### `fh_tick`

`function` | [include/frame_host.h:40](../../include/frame_host.h#L40)

```c
int fh_tick(fh_host *h, int elapsed_ms);
```

Advances every frame's virtual clock by elapsed_ms and processes what they posted.

Returns the smallest pending frame timer in ms, or -1 when none.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `fh_host *` |  |  |
| `elapsed_ms` | `int` |  |  |

**Returns:** `int`

---

<a id="fh_count"></a>

### `fh_count`

`function` | [include/frame_host.h:43](../../include/frame_host.h#L43)

```c
int fh_count(const fh_host *h);
```

Number of live frame workers (excludes the top).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `fh_host *` |  |  |

**Returns:** `int`

---

<a id="it"></a>

### `it`

`function` | [include/frame_host.h:46](../../include/frame_host.h#L46)

```c
* confined worker last built it (NULL when no live frame has that URL);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `URL` | `NULL when no live frame has that` |  |  |

**Returns:** `* confined worker last built`

---

<a id="fh_frame_view"></a>

### `fh_frame_view`

`function` `const` | [include/frame_host.h:49](../../include/frame_host.h#L49)

```c
const pv_view *fh_frame_view(const fh_host *h, const char *url, tab **t_out);
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

---

<a id="fh_generation"></a>

### `fh_generation`

`function` | [include/frame_host.h:52](../../include/frame_host.h#L52)

```c
unsigned fh_generation(const fh_host *h);
```

Changes whenever any frame view appears, is replaced or goes away: repaint the frames then.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `fh_host *` |  |  |

**Returns:** `unsigned`

---

## Macros

<a id="fh_max_depth"></a>

### `FH_MAX_DEPTH`

`macro` | [include/frame_host.h:18](../../include/frame_host.h#L18)

```c
#define FH_MAX_DEPTH
```

---
