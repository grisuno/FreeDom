# `include/pdf_export.h`

> Source: [include/pdf_export.h:1](../../include/pdf_export.h#L1) | language `h` | coverage 30.0% | [API index](../index.md)

## Contents

- **Enums:** [`pe_status`](#pe_status)
- **Functions:** [`fallback`](#fallback), [`trusted`](#trusted), [`literal`](#literal), [`pe_paginate`](#pe_paginate)
- **Macros:** [`PE_NAME_MAX`](#pe_name_max), [`PE_EXT`](#pe_ext), [`PE_EXT_PNG`](#pe_ext_png), [`PE_FALLBACK_NAME`](#pe_fallback_name)

## Enums

<a id="pe_status"></a>

### `pe_status`

`enum` | [include/pdf_export.h:33](../../include/pdf_export.h#L33)

```c
typedef enum pe_status
```

---

## Functions

<a id="fallback"></a>

### `fallback`

`function` | [include/pdf_export.h:46](../../include/pdf_export.h#L46)

```c
* fallback (PE_ERR_OVERFLOW, out left empty). title == NULL is treated as empty. * Does NOT append the extension (that is pe_build_path's job). */ pe_status pe_safe_basename(const char *title, char *o
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `empty` | `left` |  |  |

**Returns:** `*`

---

<a id="trusted"></a>

### `trusted`

`function` | [include/pdf_export.h:51](../../include/pdf_export.h#L51)

```c
* dir is trusted (chosen by the app from XDG/$HOME);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `$HOME` | `chosen by the app from XDG/` |  |  |

**Returns:** `* dir is`

---

<a id="literal"></a>

### `literal`

`function` | [include/pdf_export.h:52](../../include/pdf_export.h#L52)

```c
* trusted literal (e.g. PE_EXT / PE_EXT_PNG);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `PE_EXT_PNG` | `e.g. PE_EXT /` |  |  |

**Returns:** `* trusted`

---

<a id="pe_paginate"></a>

### `pe_paginate`

`function` | [include/pdf_export.h:70](../../include/pdf_export.h#L70)

```c
size_t pe_paginate(const double *tops, const double *heights, size_t n, double page_h, int *out_page, double *out_page_y);
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

---

## Macros

<a id="pe_name_max"></a>

### `PE_NAME_MAX`

`macro` | [include/pdf_export.h:28](../../include/pdf_export.h#L28)

```c
#define PE_NAME_MAX
```

---

<a id="pe_ext"></a>

### `PE_EXT`

`macro` | [include/pdf_export.h:29](../../include/pdf_export.h#L29)

```c
#define PE_EXT
```

max bytes of the sanitized basename (excl. extension)

---

<a id="pe_ext_png"></a>

### `PE_EXT_PNG`

`macro` | [include/pdf_export.h:30](../../include/pdf_export.h#L30)

```c
#define PE_EXT_PNG
```

---

<a id="pe_fallback_name"></a>

### `PE_FALLBACK_NAME`

`macro` | [include/pdf_export.h:31](../../include/pdf_export.h#L31)

```c
#define PE_FALLBACK_NAME
```

raster export (visual review): see ui_render_png

---
