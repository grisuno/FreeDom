# `src/dom_debug.c`

> Source: [src/dom_debug.c:1](../../src/dom_debug.c#L1) | language `c` | coverage 75.0% | [API index](../index.md)

## Contents

- **Structs:** [`dd_cursor`](#dd_cursor)
- **Functions:** [`dd_format`](#dd_format), [`dd_format_css`](#dd_format_css)

## Structs

<a id="dd_cursor"></a>

### `dd_cursor`

`struct` | [src/dom_debug.c:24](../../src/dom_debug.c#L24)

```c
typedef struct dd_cursor
```

Bounded write cursor: [`pos`](include.flex_layout.h.md#fx_result-pos) bytes are committed to `out` (always leaving room for the terminating NUL); `need` counts every byte that WOULD be written so the caller gets snprintf semantics even when truncated.

---

## Functions

<a id="dd_format"></a>

### `dd_format`

`function` | [src/dom_debug.c:399](../../src/dom_debug.c#L399)

```c
size_t dd_format(const rd_doc *doc, char *out, size_t cap)
```

Formats doc into out[0..cap) as a NUL-terminated, line-oriented dump (see the spec for the stable format).

Returns the number of bytes that WOULD be written excluding the NUL (snprintf semantics): a value >= cap means the output was truncated. Never writes past out[cap-1]; always NUL-terminates when cap > 0. doc == NULL formats a valid empty tree. out == NULL or cap == 0 only measures (writes nothing). Allocates nothing and cannot fail.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `doc` | `rd_doc *` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`dd_format`](#dd_format) (include/dom_debug.h:36).

---

<a id="dd_format_css"></a>

### `dd_format_css`

`function` | [src/dom_debug.c:431](../../src/dom_debug.c#L431)

```c
size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)
```

CSS inspector: dumps every element with its full CSS property set.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `doc` | `rd_doc *` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

---
