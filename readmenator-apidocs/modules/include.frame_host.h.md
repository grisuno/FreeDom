# `include/frame_host.h`

> Source: [include/frame_host.h:1](../../include/frame_host.h#L1) | language `h` | coverage 75.0% | [API index](../index.md)

## Contents

- **Type Aliases:** [`fh_host`](#fh_host)
- **Functions:** [`fh_new`](#fh_new), [`fh_free`](#fh_free), [`fh_apply_top`](#fh_apply_top), [`fh_tick`](#fh_tick), [`fh_count`](#fh_count)
- **Macros:** [`FH_MAX_DEPTH`](#fh_max_depth)

## Type Aliases

<a id="fh_host"></a>

### `fh_host`

`type_alias` | [include/frame_host.h:18](../../include/frame_host.h#L18)

```c
typedef struct fh_host fh_host;
```

nested deliveries handled inside one call; the rest waits for a tick

---

## Functions

<a id="fh_new"></a>

### `fh_new`

`function` | [include/frame_host.h:27](../../include/frame_host.h#L27)

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

`function` | [include/frame_host.h:31](../../include/frame_host.h#L31)

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

`function` | [include/frame_host.h:35](../../include/frame_host.h#L35)

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

`function` | [include/frame_host.h:39](../../include/frame_host.h#L39)

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

`function` | [include/frame_host.h:42](../../include/frame_host.h#L42)

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

## Macros

<a id="fh_max_depth"></a>

### `FH_MAX_DEPTH`

`macro` | [include/frame_host.h:17](../../include/frame_host.h#L17)

```c
#define FH_MAX_DEPTH
```

---
