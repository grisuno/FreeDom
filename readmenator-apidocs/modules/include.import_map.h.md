# `include/import_map.h`

> Source: [include/import_map.h:1](../../include/import_map.h#L1) | language `h` | coverage 30.0% | [API index](../index.md)

## Contents

- **Type Aliases:** [`im_map`](#im_map)
- **Functions:** [`algorithm`](#algorithm), [`map`](#map), [`im_resolve`](#im_resolve), [`im_count`](#im_count), [`im_free`](#im_free)
- **Macros:** [`IM_MAX_TEXT`](#im_max_text), [`IM_MAX_ENTRIES`](#im_max_entries), [`IM_MAX_SCOPES`](#im_max_scopes)

## Type Aliases

<a id="im_map"></a>

### `im_map`

`type_alias` | [include/import_map.h:23](../../include/import_map.h#L23)

```c
typedef struct im_map im_map;
```

---

## Functions

<a id="algorithm"></a>

### `algorithm`

`function` | [include/import_map.h:13](../../include/import_map.h#L13)

```c
* resolution algorithm (scopes, exact and prefix matches). URL resolution is the * caller's (the same resolver the module loader uses). See spec/import_map.md. */ #define IM_MAX_TEXT ((size_t)(1u * 10
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `matches` | `exact and prefix` |  |  |

**Returns:** `* resolution`

---

<a id="map"></a>

### `map`

`function` | [include/import_map.h:28](../../include/import_map.h#L28)

```c
* map (fail closed = no mapping). NULL only on OOM. */ im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn resolve, void *ctx);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `closed` | `fail` | `no mapping` |  |

**Returns:** `*`

---

<a id="im_resolve"></a>

### `im_resolve`

`function` | [include/import_map.h:33](../../include/import_map.h#L33)

```c
int im_resolve(const im_map *m, const char *base, const char *specifier, im_url_fn resolve, void *ctx, char *out, size_t outsz);
```

Resolves specifier as imported from base (the importing module's URL).

0 with the absolute URL in out, or -1 (a bare specifier without a mapping, or overflow).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `m` | `im_map *` |  |  |
| `base` | `char *` |  |  |
| `specifier` | `char *` |  |  |
| `resolve` | `im_url_fn` |  |  |
| `ctx` | `void *` |  |  |
| `out` | `char *` |  |  |
| `outsz` | `size_t` |  |  |

**Returns:** `int`

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_import_map.c.md#llvmfuzzertestoneinput)

---

<a id="im_count"></a>

### `im_count`

`function` | [include/import_map.h:37](../../include/import_map.h#L37)

```c
size_t im_count(const im_map *m);
```

Total entries (imports + every scope's).

0 for NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `m` | `im_map *` |  |  |

**Returns:** `size_t`

---

<a id="im_free"></a>

### `im_free`

`function` | [include/import_map.h:40](../../include/import_map.h#L40)

```c
void im_free(im_map *m);
```

NULL is a no-op.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `m` | `im_map *` |  |  |

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_import_map.c.md#llvmfuzzertestoneinput), [`pf_pool_finish`](src.prefetch.c.md#pf_pool_finish), [`pf_pool_start_page`](src.prefetch.c.md#pf_pool_start_page)

---

## Macros

<a id="im_max_text"></a>

### `IM_MAX_TEXT`

`macro` | [include/import_map.h:17](../../include/import_map.h#L17)

```c
#define IM_MAX_TEXT
```

---

<a id="im_max_entries"></a>

### `IM_MAX_ENTRIES`

`macro` | [include/import_map.h:18](../../include/import_map.h#L18)

```c
#define IM_MAX_ENTRIES
```

---

<a id="im_max_scopes"></a>

### `IM_MAX_SCOPES`

`macro` | [include/import_map.h:19](../../include/import_map.h#L19)

```c
#define IM_MAX_SCOPES
```

---
