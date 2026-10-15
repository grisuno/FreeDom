# `include/ws_hub.h`

> Source: [include/ws_hub.h:1](../../include/ws_hub.h#L1) | language `h` | coverage 73.3% | [API index](../index.md)

## Contents

- **Type Aliases:** [`wh_hub`](#wh_hub)
- **Functions:** [`wh_new`](#wh_new), [`wh_free`](#wh_free), [`wh_notify_fd`](#wh_notify_fd), [`wh_open_async`](#wh_open_async), [`generation`](#generation), [`wh_send`](#wh_send), [`wh_close`](#wh_close), [`wh_close_all`](#wh_close_all), [`wh_poll_fds`](#wh_poll_fds), [`wh_on_readable`](#wh_on_readable), [`wh_count`](#wh_count)
- **Macros:** [`WH_MAX`](#wh_max), [`WH_CLOSE_ABNORMAL`](#wh_close_abnormal)

## Type Aliases

<a id="wh_hub"></a>

### `wh_hub`

`type_alias` | [include/ws_hub.h:30](../../include/ws_hub.h#L30)

```c
typedef struct wh_hub wh_hub;
```

---

## Functions

<a id="wh_new"></a>

### `wh_new`

`function` | [include/ws_hub.h:34](../../include/ws_hub.h#L34)

```c
wh_hub *wh_new(void);
```

New empty hub with its notify pipe, or NULL on OOM / pipe failure.

**Returns:** `wh_hub *`

---

<a id="wh_free"></a>

### `wh_free`

`function` | [include/ws_hub.h:38](../../include/ws_hub.h#L38)

```c
void wh_free(wh_hub *h);
```

Closes every connection and frees the hub.

Pending opens finish on their own threads and discard their result. NULL is a no-op.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `wh_hub *` |  |  |

---

<a id="wh_notify_fd"></a>

### `wh_notify_fd`

`function` | [include/ws_hub.h:41](../../include/ws_hub.h#L41)

```c
int wh_notify_fd(const wh_hub *h);
```

Read end of the notify channel (a socket pair): poll it for POLLIN and call wh_on_notify.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `wh_hub *` |  |  |

**Returns:** `int`

---

<a id="wh_open_async"></a>

### `wh_open_async`

`function` | [include/ws_hub.h:46](../../include/ws_hub.h#L46)

```c
int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg);
```

Starts opening url for page socket id on a thread (cfg and all its strings are copied).

Returns 0 when started; -1 (nothing started) on a duplicate id, a full hub, NULL args or OOM -- the caller then reports ERROR + CLOSE to the page.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `wh_hub *` |  |  |
| `id` | `int` |  |  |
| `url` | `char *` |  |  |
| `cfg` | `sf_config *` |  |  |

**Returns:** `int`

---

<a id="generation"></a>

### `generation`

`function` | [include/ws_hub.h:50](../../include/ws_hub.h#L50)

```c
* previous generation (before wh_close_all) are closed and dropped silently. */ void wh_on_notify(wh_hub *h, wh_emit_fn emit, void *ctx);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `wh_close_all` | `before` |  |  |

**Returns:** `* previous`

---

<a id="wh_send"></a>

### `wh_send`

`function` | [include/ws_hub.h:54](../../include/ws_hub.h#L54)

```c
int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary);
```

Sends one message on an OPEN connection.

0, or -1 (unknown id / broken link).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `wh_hub *` |  |  |
| `id` | `int` |  |  |
| `data` | `void *` |  |  |
| `len` | `size_t` |  |  |
| `binary` | `int` |  |  |

**Returns:** `int`

---

<a id="wh_close"></a>

### `wh_close`

`function` | [include/ws_hub.h:58](../../include/ws_hub.h#L58)

```c
void wh_close(wh_hub *h, int id);
```

The page closed socket id: sends a close frame and frees it (also cancels a pending open for that id: its result will be dropped).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `wh_hub *` |  |  |
| `id` | `int` |  |  |

---

<a id="wh_close_all"></a>

### `wh_close_all`

`function` | [include/ws_hub.h:61](../../include/ws_hub.h#L61)

```c
void wh_close_all(wh_hub *h);
```

The page is going away: closes everything and bumps the generation.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `wh_hub *` |  |  |

---

<a id="wh_poll_fds"></a>

### `wh_poll_fds`

`function` | [include/ws_hub.h:65](../../include/ws_hub.h#L65)

```c
size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap);
```

Fills up to cap pollfds (POLLIN) and the matching page ids for the open connections.

Returns the count.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `wh_hub *` |  |  |
| `out` | `struct pollfd *` |  |  |
| `ids` | `int *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

---

<a id="wh_on_readable"></a>

### `wh_on_readable`

`function` | [include/ws_hub.h:70](../../include/ws_hub.h#L70)

```c
void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx);
```

Reads everything pending on socket id without blocking, emitting each complete message; a close frame emits WH_EV_CLOSE; an error or an oversized message emits WH_EV_ERROR + WH_EV_CLOSE(WH_CLOSE_ABNORMAL).

The connection is freed on close.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `wh_hub *` |  |  |
| `id` | `int` |  |  |
| `emit` | `wh_emit_fn` |  |  |
| `ctx` | `void *` |  |  |

---

<a id="wh_count"></a>

### `wh_count`

`function` | [include/ws_hub.h:73](../../include/ws_hub.h#L73)

```c
size_t wh_count(const wh_hub *h);
```

Number of live (open) connections.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `h` | `wh_hub *` |  |  |

**Returns:** `size_t`

---

## Macros

<a id="wh_max"></a>

### `WH_MAX`

`macro` | [include/ws_hub.h:21](../../include/ws_hub.h#L21)

```c
#define WH_MAX
```

---

<a id="wh_close_abnormal"></a>

### `WH_CLOSE_ABNORMAL`

`macro` | [include/ws_hub.h:27](../../include/ws_hub.h#L27)

```c
#define WH_CLOSE_ABNORMAL
```

Abnormal closure code (RFC 6455 7.4.1) reported for a failed or broken socket.

---
