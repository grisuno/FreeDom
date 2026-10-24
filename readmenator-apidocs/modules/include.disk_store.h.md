# `include/disk_store.h`

> Source: [include/disk_store.h:1](../../include/disk_store.h#L1) | language `h` | coverage 33.3% | [API index](../index.md)

## Contents

- **Enums:** [`ds_status`](#ds_status)
- **Functions:** [`ds_free`](#ds_free)

## Enums

<a id="ds_status"></a>

### `ds_status`

`enum` | [include/disk_store.h:25](../../include/disk_store.h#L25)

```c
typedef enum ds_status
```

---

## Functions

<a id="ds_free"></a>

### `ds_free`

`function` | [include/disk_store.h:47](../../include/disk_store.h#L47)

```c
void ds_free(uint8_t *buf, size_t len);
```

Secure free of a buffer returned by ds_read (delegates to ls_free).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `uint8_t *` |  |  |
| `len` | `size_t` |  |  |

*Called by:* [`hc_open`](src.http_cache.c.md#hc_open), [`profile_load`](src.profile.c.md#profile_load)

---
