# `include/pres_hints.h`

> Source: [include/pres_hints.h:1](../../include/pres_hints.h#L1) | language `h` | coverage 71.4% | [API index](../index.md)

pres_hints (ph_) -- HTML presentational attributes as zero-specificity style.

## Contents

- **Functions:** [`ph_parse_dimension`](#ph_parse_dimension), [`ph_apply`](#ph_apply)
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
