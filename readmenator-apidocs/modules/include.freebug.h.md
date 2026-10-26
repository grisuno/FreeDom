# `include/freebug.h`

> Source: [include/freebug.h:1](../../include/freebug.h#L1) | language `h` | coverage 72.2% | [API index](../index.md)

## Contents

- **Structs:** [`fb_entry`](#fb_entry), [`fb_buffer`](#fb_buffer)
- **Enums:** [`fb_level`](#fb_level)
- **Functions:** [`fb_buffer_init`](#fb_buffer_init), [`truncated`](#truncated), [`copied`](#copied), [`fb_buffer_push_loc`](#fb_buffer_push_loc), [`fb_buffer_reset`](#fb_buffer_reset), [`fb_buffer_free`](#fb_buffer_free), [`fb_buffer_count`](#fb_buffer_count), [`fb_buffer_at`](#fb_buffer_at), [`fb_level_name`](#fb_level_name)
- **Macros:** [`FB_MAX_ENTRIES`](#fb_max_entries), [`FB_MAX_ENTRY_BYTES`](#fb_max_entry_bytes), [`FB_MAX_TOTAL_BYTES`](#fb_max_total_bytes), [`FB_MAX_FILE_BYTES`](#fb_max_file_bytes)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class fb_level
    <<enum>> fb_level
    class fb_entry
    <<struct>> fb_entry
    class fb_entry_level
    <<type_alias>> fb_entry_level
    class fb_buffer
    <<struct>> fb_buffer
```

## Structs

<a id="fb_entry"></a>

### `fb_entry`

`struct` | [include/freebug.h:36](../../include/freebug.h#L36)

```c
typedef struct fb_entry
```

One captured console message. text and file are owned by the buffer (NUL-terminated). file/line/col are an optional source location (developer aid): file is NULL and line/col 0 when the location is unknown (e.g. a plain console.log, whose call site is not tracked).

**Members**

| Member | Kind | Summary |
|---|---|---|
| [`level`](#fb_entry-level) | type_alias | One captured console message. text and file are owned by the buffer (NUL-terminated). file/line/col are an optional source location (developer aid): file is... |

<a id="fb_entry-level"></a>

#### `fb_entry.level`

`type_alias` | [include/freebug.h:36](../../include/freebug.h#L36)

```c
typedef struct fb_entry { int level;
```

One captured console message. text and file are owned by the buffer (NUL-terminated). file/line/col are an optional source location (developer aid): file is NULL and line/col 0 when the location is unknown (e.g. a plain console.log, whose call site is not tracked).

---

<a id="fb_buffer"></a>

### `fb_buffer`

`struct` | [include/freebug.h:46](../../include/freebug.h#L46)

```c
typedef struct fb_buffer
```

An ordered, bounded list of entries.

Zero-initialise with fb_buffer_init.

---

## Enums

<a id="fb_level"></a>

### `fb_level`

`enum` | [include/freebug.h:24](../../include/freebug.h#L24)

```c
typedef enum fb_level
```

Severity of a console entry.

Out-of-range integers clamp to FB_LOG.

---

## Functions

<a id="fb_buffer_init"></a>

### `fb_buffer_init`

`function` | [include/freebug.h:65](../../include/freebug.h#L65)

```c
void fb_buffer_init(fb_buffer *b);
```

Zero-initialise b (no allocation).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `fb_buffer *` |  |  |

*Called by:* [`tab_eval`](src.tab.c.md#tab_eval), [`tab_load_full`](src.tab.c.md#tab_load_full)

---

<a id="truncated"></a>

### `truncated`

`function` | [include/freebug.h:69](../../include/freebug.h#L69)

```c
* A message longer than FB_MAX_ENTRY_BYTES is stored truncated (not dropped). A * dropped push raises b->overflow and leaves prior entries intact. The stored * entry has no source location (file == NU
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dropped` | `not` |  |  |

**Returns:** `* A message longer than FB_MAX_ENTRY_BYTES is stored`

---

<a id="copied"></a>

### `copied`

`function` | [include/freebug.h:75](../../include/freebug.h#L75)

```c
* copied (truncated to FB_MAX_FILE_BYTES);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `FB_MAX_FILE_BYTES` | `truncated to` |  |  |

**Returns:** `*`

---

<a id="fb_buffer_push_loc"></a>

### `fb_buffer_push_loc`

`function` | [include/freebug.h:78](../../include/freebug.h#L78)

```c
int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len, const char *file, int line, int col);
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

---

<a id="fb_buffer_reset"></a>

### `fb_buffer_reset`

`function` | [include/freebug.h:83](../../include/freebug.h#L83)

```c
void fb_buffer_reset(fb_buffer *b);
```

Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the entry array allocation for reuse.

Safe on NULL / a zeroed struct.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `fb_buffer *` |  |  |

*Called by:* [`run_js`](src.tab.c.md#run_js)

---

<a id="fb_buffer_free"></a>

### `fb_buffer_free`

`function` | [include/freebug.h:86](../../include/freebug.h#L86)

```c
void fb_buffer_free(fb_buffer *b);
```

Frees the entries and the array, then re-zeroes b.

Idempotent; safe on NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `fb_buffer *` |  |  |

*Called by:* [`tab_eval`](src.tab.c.md#tab_eval), [`tab_load_full`](src.tab.c.md#tab_load_full)

---

<a id="fb_buffer_count"></a>

### `fb_buffer_count`

`function` | [include/freebug.h:89](../../include/freebug.h#L89)

```c
size_t fb_buffer_count(const fb_buffer *b);
```

Number of stored entries (0 for NULL).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `fb_buffer *` |  |  |

**Returns:** `size_t`

*Called by:* [`FB_MAX_FILE_BYTES`](src.tab.c.md#fb_max_file_bytes)

---

<a id="fb_buffer_at"></a>

### `fb_buffer_at`

`function` `const` | [include/freebug.h:92](../../include/freebug.h#L92)

```c
const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i);
```

The i-th entry, or NULL if out of range / NULL b.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `fb_buffer *` |  |  |
| `i` | `size_t` |  |  |

**Returns:** `fb_entry *`

*Called by:* [`FB_MAX_FILE_BYTES`](src.tab.c.md#fb_max_file_bytes)

---

<a id="fb_level_name"></a>

### `fb_level_name`

`function` `const` | [include/freebug.h:96](../../include/freebug.h#L96)

```c
const char *fb_level_name(int level);
```

A stable lowercase level name ("log"/"info"/"warn"/"error"/"debug"); an out-of-range level clamps to "log".

Pure, no allocation.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `level` | `int` |  |  |

**Returns:** `char *`

---

## Macros

<a id="fb_max_entries"></a>

### `FB_MAX_ENTRIES`

`macro` | [include/freebug.h:56](../../include/freebug.h#L56)

```c
#define FB_MAX_ENTRIES
```

Caps (Secure by Default: unbounded is not representable).

Large enough that a real page's JS console flood is captured without truncation in normal use.

---

<a id="fb_max_entry_bytes"></a>

### `FB_MAX_ENTRY_BYTES`

`macro` | [include/freebug.h:57](../../include/freebug.h#L57)

```c
#define FB_MAX_ENTRY_BYTES
```

---

<a id="fb_max_total_bytes"></a>

### `FB_MAX_TOTAL_BYTES`

`macro` | [include/freebug.h:58](../../include/freebug.h#L58)

```c
#define FB_MAX_TOTAL_BYTES
```

---

<a id="fb_max_file_bytes"></a>

### `FB_MAX_FILE_BYTES`

`macro` | [include/freebug.h:62](../../include/freebug.h#L62)

```c
#define FB_MAX_FILE_BYTES
```

A stored source name is truncated to this many bytes (NUL excluded).

It is not counted against FB_MAX_TOTAL_BYTES: entries are capped, so total file memory is bounded at FB_MAX_ENTRIES * FB_MAX_FILE_BYTES regardless.

---
