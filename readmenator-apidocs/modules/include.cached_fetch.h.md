# `include/cached_fetch.h`

> Source: [include/cached_fetch.h:1](../../include/cached_fetch.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

## Contents

- **Functions:** [`cf_set_store`](#cf_set_store), [`cf_store`](#cf_store), [`cf_attach_redirect_memory`](#cf_attach_redirect_memory)

## Functions

<a id="cf_set_store"></a>

### `cf_set_store`

`function` | [include/cached_fetch.h:30](../../include/cached_fetch.h#L30)

```c
void cf_set_store(hc_store *store);
```

Process-wide store used by cf_get (NULL = caching off; set once at startup).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `store` | `hc_store *` |  |  |

---

<a id="cf_store"></a>

### `cf_store`

`function` | [include/cached_fetch.h:31](../../include/cached_fetch.h#L31)

```c
hc_store *cf_store(void);
```

**Returns:** `hc_store *`

---

<a id="cf_attach_redirect_memory"></a>

### `cf_attach_redirect_memory`

`function` | [include/cached_fetch.h:38](../../include/cached_fetch.h#L38)

```c
void cf_attach_redirect_memory(hc_store *store);
```

Persists permanent redirects (301/308) in the store and consults it on a RAM miss.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `store` | `hc_store *` |  |  |

---
