# `include/sha2.h`

> Source: [include/sha2.h:1](../../include/sha2.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

## Contents

- **Enums:** [`sha_alg`](#sha_alg)
- **Functions:** [`sha_digest_len`](#sha_digest_len), [`sha_alg_from_name`](#sha_alg_from_name), [`sha_digest`](#sha_digest)
- **Macros:** [`SHA_MAX_DIGEST`](#sha_max_digest)

## Enums

<a id="sha_alg"></a>

### `sha_alg`

`enum` | [include/sha2.h:16](../../include/sha2.h#L16)

```c
typedef enum sha_alg { SHA_1 = 0, SHA_256, SHA_384, SHA_512 } sha_alg;
```

---

## Functions

<a id="sha_digest_len"></a>

### `sha_digest_len`

`function` | [include/sha2.h:21](../../include/sha2.h#L21)

```c
size_t sha_digest_len(sha_alg alg);
```

Digest length in bytes of alg (20/32/48/64), or 0 for an unknown alg.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `alg` | `sha_alg` |  |  |

**Returns:** `size_t`

---

<a id="sha_alg_from_name"></a>

### `sha_alg_from_name`

`function` | [include/sha2.h:24](../../include/sha2.h#L24)

```c
int sha_alg_from_name(const char *name, sha_alg *out);
```

Maps a WebCrypto algorithm name ("SHA-256", case-insensitive) to alg.

0 on success, -1 unknown.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |
| `out` | `sha_alg *` |  |  |

**Returns:** `int`

---

<a id="sha_digest"></a>

### `sha_digest`

`function` | [include/sha2.h:28](../../include/sha2.h#L28)

```c
int sha_digest(sha_alg alg, const void *data, size_t len, uint8_t *out);
```

Hashes data[0..len) into out (>= sha_digest_len(alg) bytes).

0 on success, -1 on a bad argument. data may be NULL only when len == 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `alg` | `sha_alg` |  |  |
| `data` | `void *` |  |  |
| `len` | `size_t` |  |  |
| `out` | `uint8_t *` |  |  |

**Returns:** `int`

---

## Macros

<a id="sha_max_digest"></a>

### `SHA_MAX_DIGEST`

`macro` | [include/sha2.h:18](../../include/sha2.h#L18)

```c
#define SHA_MAX_DIGEST
```

---
