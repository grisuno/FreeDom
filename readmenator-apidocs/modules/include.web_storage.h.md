# `include/web_storage.h`

> Source: [include/web_storage.h:1](../../include/web_storage.h#L1) | language `h` | coverage 61.5% | [API index](../index.md)

## Contents

- **Type Aliases:** [`wst_db`](#wst_db)
- **Functions:** [`wst_new`](#wst_new), [`wst_free`](#wst_free), [`wst_encode`](#wst_encode), [`wst_decode_check`](#wst_decode_check), [`wst_replace`](#wst_replace), [`full`](#full), [`wst_origin_bytes`](#wst_origin_bytes)
- **Macros:** [`WST_MAX_ORIGINS`](#wst_max_origins), [`WST_MAX_KEYS`](#wst_max_keys), [`WST_QUOTA`](#wst_quota), [`WST_ORIGIN_MAX`](#wst_origin_max)

## Type Aliases

<a id="wst_db"></a>

### `wst_db`

`type_alias` | [include/web_storage.h:21](../../include/web_storage.h#L21)

```c
typedef struct wst_db wst_db;
```

web_storage — in-MEMORY localStorage for trusted hosts (owner decision: nothing persists to disk).

Pure, I/O-free: a per-origin key/value database with a quota, plus the bounded wire snapshot the confined worker sends back, validated in full before it may touch the database. See spec/web_storage.md.  #define WST_MAX_ORIGINS 256u #define WST_MAX_KEYS    65536u #define WST_QUOTA       ((size_t)(5u * 1024u * 1024u))   /* key + value bytes per origin define WST_ORIGIN_MAX  512u

---

## Functions

<a id="wst_new"></a>

### `wst_new`

`function` | [include/web_storage.h:25](../../include/web_storage.h#L25)

```c
wst_db *wst_new(void);
```

Empty database, or NULL on OOM.

**Returns:** `wst_db *`

---

<a id="wst_free"></a>

### `wst_free`

`function` | [include/web_storage.h:28](../../include/web_storage.h#L28)

```c
void wst_free(wst_db *db);
```

Frees everything.

NULL is a no-op.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `db` | `wst_db *` |  |  |

---

<a id="wst_encode"></a>

### `wst_encode`

`function` | [include/web_storage.h:33](../../include/web_storage.h#L33)

```c
int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len);
```

Snapshot of origin's pairs ([n:u32]([klen:u32][key][vlen:u32][val])*, little-endian) into an owned *out of *len bytes.

An unknown origin yields a valid empty snapshot. 0, or -1 on NULL args / OOM.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `db` | `wst_db *` |  |  |
| `origin` | `char *` |  |  |
| `out` | `char **` |  |  |
| `len` | `size_t *` |  |  |

**Returns:** `int`

---

<a id="wst_decode_check"></a>

### `wst_decode_check`

`function` | [include/web_storage.h:37](../../include/web_storage.h#L37)

```c
int wst_decode_check(const char *blob, size_t len);
```

Pure validation of a snapshot: 0 when it is complete and well-formed (counts and lengths fit, total <= WST_QUOTA, keys unique, UTF-8 well-formed), else -1.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `blob` | `char *` |  |  |
| `len` | `size_t` |  |  |

**Returns:** `int`

---

<a id="wst_replace"></a>

### `wst_replace`

`function` | [include/web_storage.h:42](../../include/web_storage.h#L42)

```c
int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len);
```

Replaces origin's contents with the snapshot after wst_decode_check.

On any failure returns -1 and the database is unchanged. A full origin table evicts the least recently used origin.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `db` | `wst_db *` |  |  |
| `origin` | `char *` |  |  |
| `blob` | `char *` |  |  |
| `len` | `size_t` |  |  |

**Returns:** `int`

---

<a id="full"></a>

### `full`

`function` | [include/web_storage.h:45](../../include/web_storage.h#L45)

```c
* validating it in full (wst_decode_check). Returns 0, or -1 when invalid (fn is then * never called). The one parser of the format, shared by the worker. */ int wst_foreach(const char *blob, size_t l
```

**Returns:** `* validating it in`

---

<a id="wst_origin_bytes"></a>

### `wst_origin_bytes`

`function` | [include/web_storage.h:59](../../include/web_storage.h#L59)

```c
size_t wst_origin_bytes(const wst_db *db, const char *origin);
```

Key + value bytes stored for origin (0 if unknown).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `db` | `wst_db *` |  |  |
| `origin` | `char *` |  |  |

**Returns:** `size_t`

---

## Macros

<a id="wst_max_origins"></a>

### `WST_MAX_ORIGINS`

`macro` | [include/web_storage.h:17](../../include/web_storage.h#L17)

```c
#define WST_MAX_ORIGINS
```

---

<a id="wst_max_keys"></a>

### `WST_MAX_KEYS`

`macro` | [include/web_storage.h:18](../../include/web_storage.h#L18)

```c
#define WST_MAX_KEYS
```

---

<a id="wst_quota"></a>

### `WST_QUOTA`

`macro` | [include/web_storage.h:19](../../include/web_storage.h#L19)

```c
#define WST_QUOTA
```

---

<a id="wst_origin_max"></a>

### `WST_ORIGIN_MAX`

`macro` | [include/web_storage.h:20](../../include/web_storage.h#L20)

```c
#define WST_ORIGIN_MAX
```

key + value bytes per origin

---
