# `include/dom_debug.h`

> Source: [include/dom_debug.h:1](../../include/dom_debug.h#L1) | language `h` | coverage 75.0% | [API index](../index.md)

## Contents

- **Functions:** [`dd_format`](#dd_format), [`dd_format_css`](#dd_format_css)
- **Macros:** [`DD_FIELD_MAX`](#dd_field_max)

## Functions

<a id="dd_format"></a>

### `dd_format`

`function` | [include/dom_debug.h:36](../../include/dom_debug.h#L36)

```c
size_t dd_format(const rd_doc *doc, char *out, size_t cap);
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

---

<a id="dd_format_css"></a>

### `dd_format_css`

`function` | [include/dom_debug.h:41](../../include/dom_debug.h#L41)

```c
size_t dd_format_css(const rd_doc *doc, char *out, size_t cap);
```

CSS inspector: dumps every block with its FULL resolved css_style fields as a compact property list.

Designed for Freebug / --dump-css. Same contract as dd_format.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `doc` | `rd_doc *` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

---

## Macros

<a id="dd_field_max"></a>

### `DD_FIELD_MAX`

`macro` | [include/dom_debug.h:28](../../include/dom_debug.h#L28)

```c
#define DD_FIELD_MAX
```

Per-field cap for a variable-length value (block text / href) so one block stays one line and a hostile document cannot blow up the dump.

---
