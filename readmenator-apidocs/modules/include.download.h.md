# `include/download.h`

> Source: [include/download.h:1](../../include/download.h#L1) | language `h` | coverage 11.1% | [API index](../index.md)

## Contents

- **Enums:** [`dl_status`](#dl_status)
- **Functions:** [`dl_should_download`](#dl_should_download), [`literal`](#literal), [`DL_ERR_OVERFLOW`](#dl_err_overflow), [`basename`](#basename)
- **Macros:** [`DL_NAME_MAX`](#dl_name_max), [`DL_FALLBACK_NAME`](#dl_fallback_name), [`DL_MAX_BYTES`](#dl_max_bytes)

## Enums

<a id="dl_status"></a>

### `dl_status`

`enum` | [include/download.h:33](../../include/download.h#L33)

```c
typedef enum dl_status
```

---

## Functions

<a id="dl_should_download"></a>

### `dl_should_download`

`function` | [include/download.h:43](../../include/download.h#L43)

```c
int dl_should_download(const char *content_type, const char *content_disposition);
```

1 if the response should be saved (attachment, or a non-renderable media type), 0 if it should be rendered.

NULL/empty content_type renders (preserves behavior for servers that omit it); an unknown/binary type downloads. See spec.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `content_type` | `char *` |  |  |
| `content_disposition` | `char *` |  |  |

**Returns:** `int`

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_download.c.md#llvmfuzzertestoneinput)

---

<a id="literal"></a>

### `literal`

`function` `static` | [include/download.h:47](../../include/download.h#L47)

```c
* a static string literal (never freed). */ const char *dl_ext_for_type(const char *content_type);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `freed` | `never` |  |  |

**Returns:** `* a string`

---

<a id="dl_err_overflow"></a>

### `DL_ERR_OVERFLOW`

`function` | [include/download.h:56](../../include/download.h#L56)

```c
* DL_ERR_OVERFLOW (out left empty). url/content_disposition NULL => absent. */ dl_status dl_pick_name(const char *url, const char *content_disposition, const char *content_type, char *out, size_t outs
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `empty` | `left` |  |  |

**Returns:** `*`

---

<a id="basename"></a>

### `basename`

`function` | [include/download.h:61](../../include/download.h#L61)

```c
* sanitized basename (a name still containing '/' is rejected => DL_ERR_OVERFLOW, * so the path can never escape dir). Trailing '/' on dir respected. Fails closed * on overflow. dir/name/out NULL or o
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `DL_ERR_OVERFLOW` | `a name still containing '/' is rejected =>` |  |  |
| `dir` | `* so the path can never escape` |  |  |

**Returns:** `* sanitized`

---

## Macros

<a id="dl_name_max"></a>

### `DL_NAME_MAX`

`macro` | [include/download.h:29](../../include/download.h#L29)

```c
#define DL_NAME_MAX
```

---

<a id="dl_fallback_name"></a>

### `DL_FALLBACK_NAME`

`macro` | [include/download.h:30](../../include/download.h#L30)

```c
#define DL_FALLBACK_NAME
```

---

<a id="dl_max_bytes"></a>

### `DL_MAX_BYTES`

`macro` | [include/download.h:31](../../include/download.h#L31)

```c
#define DL_MAX_BYTES
```

---
