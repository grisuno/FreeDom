# `src/freebug.c`

> Source: [src/freebug.c:1](../../src/freebug.c#L1) | language `c` | coverage 70.0% | [API index](../index.md)

## Contents

- **Functions:** [`whole`](#whole), [`fb_buffer_init`](#fb_buffer_init), [`fb_buffer_push`](#fb_buffer_push), [`fb_buffer_push_loc`](#fb_buffer_push_loc), [`fb_buffer_reset`](#fb_buffer_reset), [`fb_buffer_free`](#fb_buffer_free), [`fb_buffer_count`](#fb_buffer_count), [`fb_buffer_at`](#fb_buffer_at), [`fb_level_name`](#fb_level_name)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_freebug_c__fb_buffer_push(["fb_buffer_push"])
    n_src_freebug_c__fb_buffer_push_loc(["fb_buffer_push_loc"])
    n_src_freebug_c__fb_buffer_push --> n_src_freebug_c__fb_buffer_push_loc
```

## Functions

<a id="whole"></a>

### `whole`

`function` | [src/freebug.c:5](../../src/freebug.c#L5)

```c
* FB_MAX_TOTAL_BYTES is dropped whole (overflow flag raised, prior entries kept);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `raised` | `overflow flag` |  |  |
| `kept` | `prior entries` |  |  |

**Returns:** `* FB_MAX_TOTAL_BYTES is dropped`

---

<a id="fb_buffer_init"></a>

### `fb_buffer_init`

`function` | [src/freebug.c:15](../../src/freebug.c#L15)

```c
void fb_buffer_init(fb_buffer *b)
```

Zero-initialise b (no allocation).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `fb_buffer *` |  |  |

> **Inherited:** Documentation from [`fb_buffer_init`](#fb_buffer_init) (include/freebug.h:65).

---

<a id="fb_buffer_push"></a>

### `fb_buffer_push`

`function` | [src/freebug.c:19](../../src/freebug.c#L19)

```c
int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `fb_buffer *` |  |  |
| `level` | `int` |  |  |
| `text` | `char *` |  |  |
| `len` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`fb_buffer_push_loc`](#fb_buffer_push_loc)

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_freebug.c.md#llvmfuzzertestoneinput)

---

<a id="fb_buffer_push_loc"></a>

### `fb_buffer_push_loc`

`function` | [src/freebug.c:23](../../src/freebug.c#L23)

```c
int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len, const char *file, int line, int col)
```

As fb_buffer_push, but also records a source location. file (may be NULL) is copied (truncated to FB_MAX_FILE_BYTES); line/col are stored as given (0 == unknown).

Caps and fail-closed behaviour are identical to fb_buffer_push; the file copy is not counted against FB_MAX_TOTAL_BYTES.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `fb_buffer *` |  |  |
| `level` | `int` |  |  |
| `text` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `file` | `char *` |  |  |
| `line` | `int` |  |  |
| `col` | `int` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`fb_buffer_push_loc`](#fb_buffer_push_loc) (include/freebug.h:78).

*Called by:* [`fb_buffer_push`](#fb_buffer_push)

---

<a id="fb_buffer_reset"></a>

### `fb_buffer_reset`

`function` | [src/freebug.c:78](../../src/freebug.c#L78)

```c
void fb_buffer_reset(fb_buffer *b)
```

Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the entry array allocation for reuse.

Safe on NULL / a zeroed struct.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `fb_buffer *` |  |  |

> **Inherited:** Documentation from [`fb_buffer_reset`](#fb_buffer_reset) (include/freebug.h:83).

---

<a id="fb_buffer_free"></a>

### `fb_buffer_free`

`function` | [src/freebug.c:91](../../src/freebug.c#L91)

```c
void fb_buffer_free(fb_buffer *b)
```

Frees the entries and the array, then re-zeroes b.

Idempotent; safe on NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `fb_buffer *` |  |  |

> **Inherited:** Documentation from [`fb_buffer_free`](#fb_buffer_free) (include/freebug.h:86).

---

<a id="fb_buffer_count"></a>

### `fb_buffer_count`

`function` | [src/freebug.c:101](../../src/freebug.c#L101)

```c
size_t fb_buffer_count(const fb_buffer *b)
```

Number of stored entries (0 for NULL).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `fb_buffer *` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`fb_buffer_count`](#fb_buffer_count) (include/freebug.h:89).

---

<a id="fb_buffer_at"></a>

### `fb_buffer_at`

`function` `const` | [src/freebug.c:105](../../src/freebug.c#L105)

```c
const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)
```

The i-th entry, or NULL if out of range / NULL b.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `fb_buffer *` |  |  |
| `i` | `size_t` |  |  |

**Returns:** `fb_entry *`

> **Inherited:** Documentation from [`fb_buffer_at`](#fb_buffer_at) (include/freebug.h:92).

---

<a id="fb_level_name"></a>

### `fb_level_name`

`function` `const` | [src/freebug.c:110](../../src/freebug.c#L110)

```c
const char *fb_level_name(int level)
```

A stable lowercase level name ("log"/"info"/"warn"/"error"/"debug"); an out-of-range level clamps to "log".

Pure, no allocation.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `level` | `int` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`fb_level_name`](#fb_level_name) (include/freebug.h:96).

---
