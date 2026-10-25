# `include/request_policy.h`

> Source: [include/request_policy.h:1](../../include/request_policy.h#L1) | language `h` | coverage 54.5% | [API index](../index.md)

## Contents

- **Enums:** [`rp_decision`](#rp_decision)
- **Functions:** [`rp_host_of`](#rp_host_of), [`rp_site_of`](#rp_site_of), [`rp_same_site`](#rp_same_site), [`rp_sanitize_request_headers`](#rp_sanitize_request_headers), [`rp_headers_have`](#rp_headers_have)
- **Macros:** [`RP_HDR_MAX_COUNT`](#rp_hdr_max_count), [`RP_HDR_MAX_BYTES`](#rp_hdr_max_bytes), [`RP_HDR_NAME_MAX`](#rp_hdr_name_max), [`RP_HDR_VALUE_MAX`](#rp_hdr_value_max)

## Enums

<a id="rp_decision"></a>

### `rp_decision`

`enum` | [include/request_policy.h:21](../../include/request_policy.h#L21)

```c
typedef enum rp_decision
```

---

## Functions

<a id="rp_host_of"></a>

### `rp_host_of`

`function` | [include/request_policy.h:30](../../include/request_policy.h#L30)

```c
int rp_host_of(const char *url, char *out, size_t out_size);
```

Lowercased host of an absolute URL into out.

Returns 0 on success, -1 if no host can be parsed or it does not fit in out.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `url` | `char *` |  |  |
| `out` | `char *` |  |  |
| `out_size` | `size_t` |  |  |

**Returns:** `int`

*Called by:* [`arrives`](gui.browser_ui.c.md#arrives), [`HL_JS_NAV_MAX`](src.freedom.c.md#hl_js_nav_max), [`gets`](src.freedom.c.md#gets), [`run_js`](src.tab.c.md#run_js)

---

<a id="rp_site_of"></a>

### `rp_site_of`

`function` | [include/request_policy.h:34](../../include/request_policy.h#L34)

```c
int rp_site_of(const char *host, char *out, size_t out_size);
```

Registrable domain ("site") of a host into out (simplified public-suffix rule).

Returns 0 on success, -1 on empty host or insufficient buffer.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `host` | `char *` |  |  |
| `out` | `char *` |  |  |
| `out_size` | `size_t` |  |  |

**Returns:** `int`

*Called by:* [`run_js`](src.tab.c.md#run_js)

---

<a id="rp_same_site"></a>

### `rp_same_site`

`function` | [include/request_policy.h:37](../../include/request_policy.h#L37)

```c
int rp_same_site(const char *top_level_url, const char *request_url);
```

1 if both URLs share the same site, 0 otherwise (including parse failure).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `top_level_url` | `char *` |  |  |
| `request_url` | `char *` |  |  |

**Returns:** `int`

---

<a id="rp_sanitize_request_headers"></a>

### `rp_sanitize_request_headers`

`function` | [include/request_policy.h:57](../../include/request_policy.h#L57)

```c
int rp_sanitize_request_headers(const char *raw, char *out, size_t cap);
```

Filters the page-supplied header block `raw` ("Name: value" lines separated by '\n') into `out` (same format, '\n'-terminated lines, NUL-terminated) keeping ONLY headers a page may set: well-formed token name and a value free of control bytes, within the count/size caps, and not on the forbidden list (identity and framing headers the browser owns: Host, Cookie, Referer, User-Agent, Accept-Language, Accept-Encoding, Connection, Content-Length, Transfer-Encoding, TE, Upgrade, Expect, Date, DNT, Via, Origin, Sec-*, Proxy-*, X-HTTP-Method*, Access-Control-Request-*).

A repeated name keeps its first occurrence. Pure; fail-closed (anything doubtful is dropped, never rewritten). Returns the number of headers kept, or -1 on NULL/zero-capacity arguments.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `raw` | `char *` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `int`

*Called by:* [`answered`](src.tab.c.md#answered)

---

<a id="rp_headers_have"></a>

### `rp_headers_have`

`function` `inline` `static` | [include/request_policy.h:61](../../include/request_policy.h#L61)

```c
static inline int rp_headers_have(const char *lines, const char *name)
```

1 when the sanitized block `lines` carries a header called [`name`](src.text_shape.c.md#name) (case-insensitive).

Inline so secure_fetch can ask it without linking the policy module.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lines` | `char *` |  |  |
| `name` | `char *` |  |  |

**Returns:** `int`

*Called by:* [`rp_sanitize_request_headers`](src.request_policy.c.md#rp_sanitize_request_headers)

---

## Macros

<a id="rp_hdr_max_count"></a>

### `RP_HDR_MAX_COUNT`

`macro` | [include/request_policy.h:43](../../include/request_policy.h#L43)

```c
#define RP_HDR_MAX_COUNT
```

--- Request headers a page may attach to its XHR/fetch (spec/request_headers.md) ---

---

<a id="rp_hdr_max_bytes"></a>

### `RP_HDR_MAX_BYTES`

`macro` | [include/request_policy.h:44](../../include/request_policy.h#L44)

```c
#define RP_HDR_MAX_BYTES
```

---

<a id="rp_hdr_name_max"></a>

### `RP_HDR_NAME_MAX`

`macro` | [include/request_policy.h:45](../../include/request_policy.h#L45)

```c
#define RP_HDR_NAME_MAX
```

---

<a id="rp_hdr_value_max"></a>

### `RP_HDR_VALUE_MAX`

`macro` | [include/request_policy.h:46](../../include/request_policy.h#L46)

```c
#define RP_HDR_VALUE_MAX
```

---
