# `include/util.h`

> Source: [include/util.h:1](../../include/util.h#L1) | language `h` | coverage 33.3% | [API index](../index.md)

util.h — shared pure helpers (no I/O except where noted).

Static inline so each compilation unit gets its own copy without adding link dependencies.

## Contents

- **Functions:** [`write_full`](#write_full), [`read_full`](#read_full), [`mem_contains_ci`](#mem_contains_ci), [`utf8_seq_len`](#utf8_seq_len), [`fnv1a`](#fnv1a)

## Functions

<a id="write_full"></a>

### `write_full`

`function` `inline` `static` | [include/util.h:15](../../include/util.h#L15)

```c
static inline int write_full(int fd, const void *buf, size_t n)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |
| `buf` | `void *` |  |  |
| `n` | `size_t` |  |  |

**Returns:** `int`

*Called by:* [`ds_write`](src.disk_store.c.md#ds_write), [`media_decoder_run`](src.media_decoder.c.md#media_decoder_run)

---

<a id="read_full"></a>

### `read_full`

`function` `inline` `static` | [include/util.h:26](../../include/util.h#L26)

```c
static inline int read_full(int fd, void *buf, size_t n)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |
| `buf` | `void *` |  |  |
| `n` | `size_t` |  |  |

**Returns:** `int`

*Called by:* [`ds_read`](src.disk_store.c.md#ds_read), [`media_decoder_run`](src.media_decoder.c.md#media_decoder_run)

---

<a id="mem_contains_ci"></a>

### `mem_contains_ci`

`function` `inline` `static` | [include/util.h:43](../../include/util.h#L43)

```c
static inline int mem_contains_ci(const void *hay, size_t hlen, const char *needle)
```

Returns 1 when the trusted lowercase-ASCII needle (letters/digits) occurs in the hostile, length-delimited haystack, matching case-insensitively.

The `| 0x20` fold maps A-Z to a-z and leaves digits unchanged.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `hay` | `void *` |  |  |
| `hlen` | `size_t` |  |  |
| `needle` | `char *` |  |  |

**Returns:** `int`

---

<a id="utf8_seq_len"></a>

### `utf8_seq_len`

`function` `inline` `static` | [include/util.h:57](../../include/util.h#L57)

```c
static inline size_t utf8_seq_len(unsigned char c)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `unsigned char` |  |  |

**Returns:** `size_t`

---

<a id="fnv1a"></a>

### `fnv1a`

`function` `inline` `static` | [include/util.h:67](../../include/util.h#L67)

```c
static inline uint64_t fnv1a(const char *s, size_t n)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `n` | `size_t` |  |  |

**Returns:** `uint64_t`

---
