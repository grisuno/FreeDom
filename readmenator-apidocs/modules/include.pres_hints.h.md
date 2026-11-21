# `include/pres_hints.h`

> Source: [include/pres_hints.h:1](../../include/pres_hints.h#L1) | language `h` | coverage 80.0% | [API index](../index.md)

pres_hints (ph_) -- HTML presentational attributes as zero-specificity style.

## Contents

- **Functions:** [`ph_parse_dimension`](#ph_parse_dimension), [`ph_apply`](#ph_apply), [`ph_parse_nonneg`](#ph_parse_nonneg), [`ph_table_cellpadding`](#ph_table_cellpadding), [`ph_cell_padding`](#ph_cell_padding)
- **Macros:** [`PH_ATTR_MAX`](#ph_attr_max), [`PH_DIM_MAX_PX`](#ph_dim_max_px), [`PH_CENTERED`](#ph_centered), [`PH_QUIRKS`](#ph_quirks)

## Functions

<a id="ph_parse_dimension"></a>

### `ph_parse_dimension`

`function` | [include/pres_hints.h:24](../../include/pres_hints.h#L24)

```c
int ph_parse_dimension(const char *s, size_t len, int *px, int *per_mille);
```

Parses an HTML dimension: 1 with *px set (percent 0), 2 with *per_mille set, 0 = invalid.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `px` | `int *` |  |  |
| `per_mille` | `int *` |  |  |

**Returns:** `int`

---

<a id="ph_apply"></a>

### `ph_apply`

`function` | [include/pres_hints.h:31](../../include/pres_hints.h#L31)

```c
void ph_apply(const char *tag, ph_attr_fn get, void *ctx, unsigned flags, css_style *cs);
```

Applies the hints of element [`tag`](include.css_select.h.md#tag) (lower-case, NUL-terminated) to *cs; flags is a set of PH_*.

No-op on a NULL tag, getter or style.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `tag` | `char *` |  |  |
| `get` | `ph_attr_fn` |  |  |
| `ctx` | `void *` |  |  |
| `flags` | `unsigned` |  |  |
| `cs` | `css_style *` |  |  |

---

<a id="ph_parse_nonneg"></a>

### `ph_parse_nonneg`

`function` | [include/pres_hints.h:34](../../include/pres_hints.h#L34)

```c
int ph_parse_nonneg(const char *s, size_t len, int *out);
```

HTML "rules for parsing non-negative integers": 1 with *out set (0 is valid), 0 = invalid.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `out` | `int *` |  |  |

**Returns:** `int`

---

<a id="ph_table_cellpadding"></a>

### `ph_table_cellpadding`

`function` | [include/pres_hints.h:37](../../include/pres_hints.h#L37)

```c
int ph_table_cellpadding(ph_attr_fn get, void *ctx);
```

The cellpadding of a <table> whose attributes `get` reads: px, or -1 when absent/invalid.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `get` | `ph_attr_fn` |  |  |
| `ctx` | `void *` |  |  |

**Returns:** `int`

---

<a id="ph_cell_padding"></a>

### `ph_cell_padding`

`function` | [include/pres_hints.h:41](../../include/pres_hints.h#L41)

```c
void ph_cell_padding(int cellpad, css_style *cs);
```

A table cell's padding: every side the cascade left unset takes cellpad px, or the UA sheet's 1px when cellpad < 0.

No-op on a NULL style.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cellpad` | `int` |  |  |
| `cs` | `css_style *` |  |  |

---

## Macros

<a id="ph_attr_max"></a>

### `PH_ATTR_MAX`

`macro` | [include/pres_hints.h:17](../../include/pres_hints.h#L17)

```c
#define PH_ATTR_MAX
```

---

<a id="ph_dim_max_px"></a>

### `PH_DIM_MAX_PX`

`macro` | [include/pres_hints.h:18](../../include/pres_hints.h#L18)

```c
#define PH_DIM_MAX_PX
```

longest attribute value read; longer is ignored

---

<a id="ph_centered"></a>

### `PH_CENTERED`

`macro` | [include/pres_hints.h:26](../../include/pres_hints.h#L26)

```c
#define PH_CENTERED
```

---

<a id="ph_quirks"></a>

### `PH_QUIRKS`

`macro` | [include/pres_hints.h:27](../../include/pres_hints.h#L27)

```c
#define PH_QUIRKS
```

an ancestor centres its block children (<center>, align=center)

---
