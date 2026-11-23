# `include/doc_title.h`

> Source: [include/doc_title.h:1](../../include/doc_title.h#L1) | language `h` | coverage 100.0% | [API index](../index.md)

doc_title -- the <title> of a received document that has not been laid out yet

## Contents

- **Functions:** [`dt_scan`](#dt_scan)
- **Macros:** [`DT_SCAN_MAX`](#dt_scan_max)

## Functions

<a id="dt_scan"></a>

### `dt_scan`

`function` | [include/doc_title.h:20](../../include/doc_title.h#L20)

```c
int dt_scan(const char *html, size_t len, char *out, size_t cap);
```

Writes the text of the document's first <title> into out (NUL-terminated, valid UTF-8, whitespace collapsed and trimmed, bidi controls removed, truncated on a code point boundary).

Returns 1 when a non-empty title was written, 0 otherwise (out is "" whenever cap > 0).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `html` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `int`

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_doc_title.c.md#llvmfuzzertestoneinput)

---

## Macros

<a id="dt_scan_max"></a>

### `DT_SCAN_MAX`

`macro` | [include/doc_title.h:14](../../include/doc_title.h#L14)

```c
#define DT_SCAN_MAX
```

Only this many leading bytes are scanned: a real title lives in <head>.

---
