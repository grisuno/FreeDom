# `include/request_policy.h`

> Source: [include/request_policy.h:1](../../include/request_policy.h#L1) | language `h` | coverage 60.0% | [API index](../index.md)

## Contents

- **Enums:** [`rp_decision`](#rp_decision)
- **Functions:** [`rp_host_of`](#rp_host_of), [`rp_site_of`](#rp_site_of), [`rp_same_site`](#rp_same_site)

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
