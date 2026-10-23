# `src/pdf_export.c`

> Source: [src/pdf_export.c:1](../../src/pdf_export.c#L1) | language `c` | coverage 20.0% | [API index](../index.md)

## Contents

- **Functions:** [`pe_safe_basename`](#pe_safe_basename), [`pe_build_path_ext`](#pe_build_path_ext), [`pe_build_path`](#pe_build_path), [`pe_paginate`](#pe_paginate)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_pdf_export_c__pe_build_path_ext(["pe_build_path_ext"])
    n_src_pdf_export_c__pe_safe_basename(["pe_safe_basename"])
    n_src_pdf_export_c__pe_build_path(["pe_build_path"])
    n_src_pdf_export_c__pe_build_path_ext --> n_src_pdf_export_c__pe_safe_basename
    n_src_pdf_export_c__pe_build_path --> n_src_pdf_export_c__pe_build_path_ext
```

## Functions

<a id="pe_safe_basename"></a>

### `pe_safe_basename`

`function` | [src/pdf_export.c:25](../../src/pdf_export.c#L25)

```c
pe_status pe_safe_basename(const char *title, char *out, size_t outsz)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `title` | `char *` |  |  |
| `out` | `char *` |  |  |
| `outsz` | `size_t` |  |  |

**Returns:** `pe_status`

*Called by:* [`dl_pick_name`](src.download.c.md#dl_pick_name), [`pe_build_path_ext`](#pe_build_path_ext)

---

<a id="pe_build_path_ext"></a>

### `pe_build_path_ext`

`function` | [src/pdf_export.c:66](../../src/pdf_export.c#L66)

```c
pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext, char *out, size_t outsz)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dir` | `char *` |  |  |
| `title` | `char *` |  |  |
| `ext` | `char *` |  |  |
| `out` | `char *` |  |  |
| `outsz` | `size_t` |  |  |

**Returns:** `pe_status`

*Calls:* [`pe_safe_basename`](#pe_safe_basename)

*Called by:* [`pe_build_path`](#pe_build_path)

---

<a id="pe_build_path"></a>

### `pe_build_path`

`function` | [src/pdf_export.c:91](../../src/pdf_export.c#L91)

```c
pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dir` | `char *` |  |  |
| `title` | `char *` |  |  |
| `out` | `char *` |  |  |
| `outsz` | `size_t` |  |  |

**Returns:** `pe_status`

*Calls:* [`pe_build_path_ext`](#pe_build_path_ext)

---

<a id="pe_paginate"></a>

### `pe_paginate`

`function` | [src/pdf_export.c:95](../../src/pdf_export.c#L95)

```c
size_t pe_paginate(const double *tops, const double *heights, size_t n, double page_h, int *out_page, double *out_page_y)
```

Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h without ever splitting a row.

Writes out_page[i] (0-based page index) and out_page_y[i] (y within that page) for each of the n rows. Returns the page count (last page + 1), or 0 if n == 0, page_h <= 0, or any pointer is NULL. A row taller than page_h gets its own page starting at y == 0 and overflows (it is not split). Vertical gaps between rows are preserved within a page.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `tops` | `double *` |  |  |
| `heights` | `double *` |  |  |
| `n` | `size_t` |  |  |
| `page_h` | `double` |  |  |
| `out_page` | `int *` |  |  |
| `out_page_y` | `double *` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`pe_paginate`](#pe_paginate) (include/pdf_export.h:70).

---
