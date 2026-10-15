# `include/webfont_load.h`

> Source: [include/webfont_load.h:1](../../include/webfont_load.h#L1) | language `h` | coverage 14.3% | [API index](../index.md)

## Contents

- **Structs:** [`wf_sheet`](#wf_sheet)
- **Functions:** [`free`](#free), [`skipped`](#skipped)
- **Macros:** [`WF_LOAD_TRIES_PER_KEY`](#wf_load_tries_per_key), [`WF_LOAD_MAX_KEYS`](#wf_load_max_keys), [`WF_LOAD_MAX_FETCHES`](#wf_load_max_fetches)

## Structs

<a id="wf_sheet"></a>

### `wf_sheet`

`struct` | [include/webfont_load.h:24](../../include/webfont_load.h#L24)

```c
typedef struct wf_sheet
```

One collected stylesheet: text plus the URL it was fetched from (the resolution base for its relative font URLs; inline <style> uses page_url).

---

## Functions

<a id="free"></a>

### `free`

`function` | [include/webfont_load.h:31](../../include/webfont_load.h#L31)

```c
* free()), *out_status the HTTP status. Nonzero on refusal/error (fail-closed: * the face is skipped, never the page). Implemented by the parent around its * own policy-gated fetcher. */ typedef int (
```

**Returns:** `*`

*Called by:* [`elsewhere`](src.freedom.c.md#elsewhere), [`parent`](src.freedom.c.md#parent), [`WF_DATA_URL_MAX`](src.webfont_load.c.md#wf_data_url_max)

---

<a id="skipped"></a>

### `skipped`

`function` | [include/webfont_load.h:47](../../include/webfont_load.h#L47)

```c
* URLs are skipped (no base). Returns faces registered (>= 0) otherwise. */ int wf_load_document(wf_fetch_fn fetch, void *fctx, const char *page_url, const wf_sheet *extern_sheets, size_t nextern, con
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `base` | `no` |  |  |

**Returns:** `* URLs are`

---

## Macros

<a id="wf_load_tries_per_key"></a>

### `WF_LOAD_TRIES_PER_KEY`

`macro` | [include/webfont_load.h:52](../../include/webfont_load.h#L52)

```c
#define WF_LOAD_TRIES_PER_KEY
```

---

<a id="wf_load_max_keys"></a>

### `WF_LOAD_MAX_KEYS`

`macro` | [include/webfont_load.h:53](../../include/webfont_load.h#L53)

```c
#define WF_LOAD_MAX_KEYS
```

---

<a id="wf_load_max_fetches"></a>

### `WF_LOAD_MAX_FETCHES`

`macro` | [include/webfont_load.h:54](../../include/webfont_load.h#L54)

```c
#define WF_LOAD_MAX_FETCHES
```

---
