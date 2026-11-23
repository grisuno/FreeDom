# `src/doc_title.c`

> Source: [src/doc_title.c:1](../../src/doc_title.c#L1) | language `c` | coverage 33.3% | [API index](../index.md)

doc_title -- the <title> of a received document that has not been laid out yet.

Contract and rationale: spec/doc_title.md.

## Contents

- **Structs:** [`dt_writer`](#dt_writer)
- **Functions:** [`dt_scan`](#dt_scan)
- **Macros:** [`DT_REPLACEMENT`](#dt_replacement), [`DT_MAX_CP`](#dt_max_cp), [`DT_REF_DIGITS`](#dt_ref_digits)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_doc_title_c__dt_scan(["dt_scan"])
    n_gui_browser_ui_c__strcmp["browser_ui.strcmp"]
    n_src_doc_title_c__dt_scan -.-> n_gui_browser_ui_c__strcmp
```

## Structs

<a id="dt_writer"></a>

### `dt_writer`

`struct` | [src/doc_title.c:12](../../src/doc_title.c#L12)

```c
typedef struct dt_writer
```

---

## Functions

<a id="dt_scan"></a>

### `dt_scan`

`function` | [src/doc_title.c:131](../../src/doc_title.c#L131)

```c
int dt_scan(const char *html, size_t len, char *out, size_t cap)
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

> **Inherited:** Documentation from [`dt_scan`](#dt_scan) (include/doc_title.h:20).

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp)

---

## Macros

<a id="dt_replacement"></a>

### `DT_REPLACEMENT`

`macro` | [src/doc_title.c:8](../../src/doc_title.c#L8)

```c
#define DT_REPLACEMENT
```

---

<a id="dt_max_cp"></a>

### `DT_MAX_CP`

`macro` | [src/doc_title.c:9](../../src/doc_title.c#L9)

```c
#define DT_MAX_CP
```

---

<a id="dt_ref_digits"></a>

### `DT_REF_DIGITS`

`macro` | [src/doc_title.c:10](../../src/doc_title.c#L10)

```c
#define DT_REF_DIGITS
```

---
