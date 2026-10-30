# `src/local_store.c`

> Source: [src/local_store.c:1](../../src/local_store.c#L1) | language `c` | coverage 19.2% | [API index](../index.md)

## Contents

- **Functions:** [`ls_derive_key`](#ls_derive_key), [`ls_seal`](#ls_seal), [`ls_open`](#ls_open), [`ls_seal_passphrase`](#ls_seal_passphrase), [`ls_open_passphrase`](#ls_open_passphrase), [`ls_free`](#ls_free)
- **Macros:** [`_GNU_SOURCE`](#_gnu_source), [`OSSL_KDF_PARAM_ARGON2_LANES`](#ossl_kdf_param_argon2_lanes), [`OSSL_KDF_PARAM_ARGON2_MEMCOST`](#ossl_kdf_param_argon2_memcost), [`OSSL_KDF_PARAM_THREADS`](#ossl_kdf_param_threads), [`OSSL_KDF_PARAM_ARGON2_LANES`](#ossl_kdf_param_argon2_lanes), [`OSSL_KDF_PARAM_ARGON2_MEMCOST`](#ossl_kdf_param_argon2_memcost), [`OSSL_KDF_PARAM_THREADS`](#ossl_kdf_param_threads), [`LS_VERSION`](#ls_version), [`LS_KDF_NONE`](#ls_kdf_none), [`LS_KDF_ARGON2ID`](#ls_kdf_argon2id), [`LS_ARGON2_T`](#ls_argon2_t), [`LS_ARGON2_M_KIB`](#ls_argon2_m_kib), [`LS_ARGON2_P`](#ls_argon2_p), [`OFF_MAGIC`](#off_magic), [`OFF_VERSION`](#off_version), [`OFF_AEAD`](#off_aead), [`OFF_KDF`](#off_kdf), [`OFF_SALT`](#off_salt), [`OFF_NONCE`](#off_nonce)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_local_store_c__ls_seal_passphrase(["ls_seal_passphrase"])
    n_src_local_store_c__ls_derive_key(["ls_derive_key"])
    n_src_local_store_c__ls_open_passphrase(["ls_open_passphrase"])
    n_src_local_store_c__ls_seal_passphrase --> n_src_local_store_c__ls_derive_key
    n_src_local_store_c__ls_open_passphrase --> n_src_local_store_c__ls_derive_key
```

## Functions

<a id="ls_derive_key"></a>

### `ls_derive_key`

`function` | [src/local_store.c:108](../../src/local_store.c#L108)

```c
ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len, const uint8_t *salt, size_t salt_len, uint8_t out_key[LS_KEY_LEN])
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `passphrase` | `uint8_t *` |  |  |
| `pass_len` | `size_t` |  |  |
| `salt` | `uint8_t *` |  |  |
| `salt_len` | `size_t` |  |  |
| `LS_KEY_LEN` | `uint8_t out_key[ ]` |  |  |

**Returns:** `ls_status`

*Called by:* [`ls_open_passphrase`](#ls_open_passphrase), [`ls_seal_passphrase`](#ls_seal_passphrase), [`profile_open`](src.profile.c.md#profile_open)

---

<a id="ls_seal"></a>

### `ls_seal`

`function` | [src/local_store.c:239](../../src/local_store.c#L239)

```c
ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead, const uint8_t *plaintext, size_t pt_len, uint8_t **out, size_t *out_len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `LS_KEY_LEN` | `uint8_t key[ ]` |  |  |
| `aead` | `ls_aead` |  |  |
| `plaintext` | `uint8_t *` |  |  |
| `pt_len` | `size_t` |  |  |
| `out` | `uint8_t **` |  |  |
| `out_len` | `size_t *` |  |  |

**Returns:** `ls_status`

*Called by:* [`ds_write`](src.disk_store.c.md#ds_write), [`pqs_seal`](src.pq_seal.c.md#pqs_seal)

---

<a id="ls_open"></a>

### `ls_open`

`function` | [src/local_store.c:252](../../src/local_store.c#L252)

```c
ls_status ls_open(const uint8_t key[LS_KEY_LEN], const uint8_t *blob, size_t blob_len, uint8_t **out, size_t *out_len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `LS_KEY_LEN` | `uint8_t key[ ]` |  |  |
| `blob` | `uint8_t *` |  |  |
| `blob_len` | `size_t` |  |  |
| `out` | `uint8_t **` |  |  |
| `out_len` | `size_t *` |  |  |

**Returns:** `ls_status`

*Called by:* [`ds_read`](src.disk_store.c.md#ds_read), [`pqs_open`](src.pq_seal.c.md#pqs_open)

---

<a id="ls_seal_passphrase"></a>

### `ls_seal_passphrase`

`function` | [src/local_store.c:263](../../src/local_store.c#L263)

```c
ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead, const uint8_t *plaintext, size_t pt_len, uint8_t **out, size_t *out_len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `passphrase` | `uint8_t *` |  |  |
| `pass_len` | `size_t` |  |  |
| `aead` | `ls_aead` |  |  |
| `plaintext` | `uint8_t *` |  |  |
| `pt_len` | `size_t` |  |  |
| `out` | `uint8_t **` |  |  |
| `out_len` | `size_t *` |  |  |

**Returns:** `ls_status`

*Calls:* [`ls_derive_key`](#ls_derive_key)

---

<a id="ls_open_passphrase"></a>

### `ls_open_passphrase`

`function` | [src/local_store.c:284](../../src/local_store.c#L284)

```c
ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len, const uint8_t *blob, size_t blob_len, uint8_t **out, size_t *out_len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `passphrase` | `uint8_t *` |  |  |
| `pass_len` | `size_t` |  |  |
| `blob` | `uint8_t *` |  |  |
| `blob_len` | `size_t` |  |  |
| `out` | `uint8_t **` |  |  |
| `out_len` | `size_t *` |  |  |

**Returns:** `ls_status`

*Calls:* [`ls_derive_key`](#ls_derive_key)

---

<a id="ls_free"></a>

### `ls_free`

`function` | [src/local_store.c:304](../../src/local_store.c#L304)

```c
void ls_free(uint8_t *buf, size_t len)
```

Secure free: OPENSSL_cleanse(buf, len) then free.

Safe on NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `uint8_t *` |  |  |
| `len` | `size_t` |  |  |

> **Inherited:** Documentation from [`ls_free`](#ls_free) (include/local_store.h:80).

---

## Macros

<a id="_gnu_source"></a>

### `_GNU_SOURCE`

`macro` | [src/local_store.c:13](../../src/local_store.c#L13)

```c
#define _GNU_SOURCE
```

---

<a id="ossl_kdf_param_argon2_lanes"></a>

### `OSSL_KDF_PARAM_ARGON2_LANES`

`macro` | [src/local_store.c:25](../../src/local_store.c#L25)

```c
#define OSSL_KDF_PARAM_ARGON2_LANES
```

---

<a id="ossl_kdf_param_argon2_memcost"></a>

### `OSSL_KDF_PARAM_ARGON2_MEMCOST`

`macro` | [src/local_store.c:28](../../src/local_store.c#L28)

```c
#define OSSL_KDF_PARAM_ARGON2_MEMCOST
```

---

<a id="ossl_kdf_param_threads"></a>

### `OSSL_KDF_PARAM_THREADS`

`macro` | [src/local_store.c:31](../../src/local_store.c#L31)

```c
#define OSSL_KDF_PARAM_THREADS
```

---

<a id="ossl_kdf_param_argon2_lanes"></a>

### `OSSL_KDF_PARAM_ARGON2_LANES`

`macro` | [src/local_store.c:39](../../src/local_store.c#L39)

```c
#define OSSL_KDF_PARAM_ARGON2_LANES
```

---

<a id="ossl_kdf_param_argon2_memcost"></a>

### `OSSL_KDF_PARAM_ARGON2_MEMCOST`

`macro` | [src/local_store.c:42](../../src/local_store.c#L42)

```c
#define OSSL_KDF_PARAM_ARGON2_MEMCOST
```

---

<a id="ossl_kdf_param_threads"></a>

### `OSSL_KDF_PARAM_THREADS`

`macro` | [src/local_store.c:45](../../src/local_store.c#L45)

```c
#define OSSL_KDF_PARAM_THREADS
```

---

<a id="ls_version"></a>

### `LS_VERSION`

`macro` | [src/local_store.c:48](../../src/local_store.c#L48)

```c
#define LS_VERSION
```

---

<a id="ls_kdf_none"></a>

### `LS_KDF_NONE`

`macro` | [src/local_store.c:49](../../src/local_store.c#L49)

```c
#define LS_KDF_NONE
```

---

<a id="ls_kdf_argon2id"></a>

### `LS_KDF_ARGON2ID`

`macro` | [src/local_store.c:50](../../src/local_store.c#L50)

```c
#define LS_KDF_ARGON2ID
```

---

<a id="ls_argon2_t"></a>

### `LS_ARGON2_T`

`macro` | [src/local_store.c:53](../../src/local_store.c#L53)

```c
#define LS_ARGON2_T
```

Argon2id v1 parameters (OWASP interactive minimums).

---

<a id="ls_argon2_m_kib"></a>

### `LS_ARGON2_M_KIB`

`macro` | [src/local_store.c:54](../../src/local_store.c#L54)

```c
#define LS_ARGON2_M_KIB
```

passes (t_cost)

---

<a id="ls_argon2_p"></a>

### `LS_ARGON2_P`

`macro` | [src/local_store.c:55](../../src/local_store.c#L55)

```c
#define LS_ARGON2_P
```

memory cost in KiB (19 MiB)

---

<a id="off_magic"></a>

### `OFF_MAGIC`

`macro` | [src/local_store.c:58](../../src/local_store.c#L58)

```c
#define OFF_MAGIC
```

Container field offsets.

---

<a id="off_version"></a>

### `OFF_VERSION`

`macro` | [src/local_store.c:59](../../src/local_store.c#L59)

```c
#define OFF_VERSION
```

---

<a id="off_aead"></a>

### `OFF_AEAD`

`macro` | [src/local_store.c:60](../../src/local_store.c#L60)

```c
#define OFF_AEAD
```

---

<a id="off_kdf"></a>

### `OFF_KDF`

`macro` | [src/local_store.c:61](../../src/local_store.c#L61)

```c
#define OFF_KDF
```

---

<a id="off_salt"></a>

### `OFF_SALT`

`macro` | [src/local_store.c:62](../../src/local_store.c#L62)

```c
#define OFF_SALT
```

---

<a id="off_nonce"></a>

### `OFF_NONCE`

`macro` | [src/local_store.c:63](../../src/local_store.c#L63)

```c
#define OFF_NONCE
```

---
