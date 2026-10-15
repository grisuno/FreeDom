# `include/data_url.h`

> Source: [include/data_url.h:1](../../include/data_url.h#L1) | language `h` | coverage 33.3% | [API index](../index.md)

## Contents

- **Enums:** [`du_status`](#du_status)
- **Functions:** [`allocation`](#allocation), [`du_is_data_url`](#du_is_data_url), [`closed`](#closed)
- **Macros:** [`DU_MAX_ENCODED_LEN`](#du_max_encoded_len)

## Enums

<a id="du_status"></a>

### `du_status`

`enum` | [include/data_url.h:27](../../include/data_url.h#L27)

```c
typedef enum du_status
```

---

## Functions

<a id="allocation"></a>

### `allocation`

`function` | [include/data_url.h:21](../../include/data_url.h#L21)

```c
* * du_base64_payload does no allocation (it only slices the caller's url string);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `string` | `it only slices the caller's url` |  |  |

**Returns:** `* * du_base64_payload does no`

---

<a id="du_is_data_url"></a>

### `du_is_data_url`

`function` | [include/data_url.h:46](../../include/data_url.h#L46)

```c
int du_is_data_url(const char *url);
```

Nonzero iff url begins (case-insensitively) with "data:".

NULL => 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `url` | `char *` |  |  |

**Returns:** `int`

*Called by:* [`string`](gui.browser_ui.c.md#string), [`rdp_image_decision`](src.render_policy.c.md#rdp_image_decision)

---

<a id="closed"></a>

### `closed`

`function` | [include/data_url.h:59](../../include/data_url.h#L59)

```c
* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/out/out_len == NULL (with b64_len != 0) => DU_ERR_NULL_ARG. */ du_status du_base64_decode(const char *b64, size_t b64_len,
```

**Returns:** `* 4 fails`

---

## Macros

<a id="du_max_encoded_len"></a>

### `DU_MAX_ENCODED_LEN`

`macro` | [include/data_url.h:43](../../include/data_url.h#L43)

```c
#define DU_MAX_ENCODED_LEN
```

16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a remote, hostile document controls.

---
