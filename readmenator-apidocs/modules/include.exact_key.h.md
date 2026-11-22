# `include/exact_key.h`

> Source: [include/exact_key.h:1](../../include/exact_key.h#L1) | language `h` | coverage 88.9% | [API index](../index.md)

exact_key (ek_) -- a cache key built by OBSERVING every input of what is cached, compared

## Contents

- **Structs:** [`ek_key`](#ek_key)
- **Functions:** [`ek_init`](#ek_init), [`ek_reset`](#ek_reset), [`ek_put`](#ek_put), [`ek_equal`](#ek_equal), [`ek_swap`](#ek_swap), [`ek_free`](#ek_free)
- **Macros:** [`EK_MAX_BYTES`](#ek_max_bytes)

## Structs

<a id="ek_key"></a>

### `ek_key`

`struct` | [include/exact_key.h:17](../../include/exact_key.h#L17)

```c
typedef struct ek_key
```

---

## Functions

<a id="ek_init"></a>

### `ek_init`

`function` | [include/exact_key.h:24](../../include/exact_key.h#L24)

```c
void ek_init(ek_key *k);
```

An empty key with no memory.

NULL-safe.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `k` | `ek_key *` |  |  |

---

<a id="ek_reset"></a>

### `ek_reset`

`function` | [include/exact_key.h:27](../../include/exact_key.h#L27)

```c
void ek_reset(ek_key *k);
```

Empties the key (n = 0, bad = 0) and keeps its memory.

NULL-safe.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `k` | `ek_key *` |  |  |

---

<a id="ek_put"></a>

### `ek_put`

`function` | [include/exact_key.h:31](../../include/exact_key.h#L31)

```c
void ek_put(ek_key *k, const void *p, size_t len);
```

Appends len bytes of p.

A failed or oversized append, or p == NULL with len > 0, marks the key bad. NULL key is a no-op.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `k` | `ek_key *` |  |  |
| `p` | `void *` |  |  |
| `len` | `size_t` |  |  |

---

<a id="ek_equal"></a>

### `ek_equal`

`function` | [include/exact_key.h:34](../../include/exact_key.h#L34)

```c
int ek_equal(const ek_key *a, const ek_key *b);
```

1 when a and b hold the same byte sequence and neither is bad, else 0 (NULL = 0).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `ek_key *` |  |  |
| `b` | `ek_key *` |  |  |

**Returns:** `int`

---

<a id="ek_swap"></a>

### `ek_swap`

`function` | [include/exact_key.h:37](../../include/exact_key.h#L37)

```c
void ek_swap(ek_key *a, ek_key *b);
```

Exchanges the contents of a and b without copying.

NULL-safe.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `ek_key *` |  |  |
| `b` | `ek_key *` |  |  |

---

<a id="ek_free"></a>

### `ek_free`

`function` | [include/exact_key.h:40](../../include/exact_key.h#L40)

```c
void ek_free(ek_key *k);
```

Releases the key's memory and leaves it empty.

NULL-safe, idempotent.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `k` | `ek_key *` |  |  |

---

## Macros

<a id="ek_max_bytes"></a>

### `EK_MAX_BYTES`

`macro` | [include/exact_key.h:15](../../include/exact_key.h#L15)

```c
#define EK_MAX_BYTES
```

Largest key (anti-DoS); a bigger one is marked bad and never equals anything.

---
