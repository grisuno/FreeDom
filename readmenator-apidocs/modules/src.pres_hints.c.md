# `src/pres_hints.c`

> Source: [src/pres_hints.c:1](../../src/pres_hints.c#L1) | language `c` | coverage 75.0% | [API index](../index.md)

pres_hints (ph_) -- see include/pres_hints.h and spec/pres_hints.md.

## Contents

- **Functions:** [`ph_parse_dimension`](#ph_parse_dimension), [`ph_apply`](#ph_apply)
- **Macros:** [`PH_PER_MILLE_MAX`](#ph_per_mille_max)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_pres_hints_c__ph_apply(["ph_apply"])
    n_gui_browser_ui_c__strcmp["browser_ui.strcmp"]
    n_src_pres_hints_c__ph_apply -.-> n_gui_browser_ui_c__strcmp
```

## Functions

<a id="ph_parse_dimension"></a>

### `ph_parse_dimension`

`function` | [src/pres_hints.c:14](../../src/pres_hints.c#L14)

```c
int ph_parse_dimension(const char *s, size_t len, int *px, int *per_mille)
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

> **Inherited:** Documentation from [`ph_parse_dimension`](#ph_parse_dimension) (include/pres_hints.h:24).

---

<a id="ph_apply"></a>

### `ph_apply`

`function` | [src/pres_hints.c:93](../../src/pres_hints.c#L93)

```c
void ph_apply(const char *tag, ph_attr_fn get, void *ctx, unsigned flags, css_style *cs)
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

> **Inherited:** Documentation from [`ph_apply`](#ph_apply) (include/pres_hints.h:31).

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp)

---

## Macros

<a id="ph_per_mille_max"></a>

### `PH_PER_MILLE_MAX`

`macro` | [src/pres_hints.c:8](../../src/pres_hints.c#L8)

```c
#define PH_PER_MILLE_MAX
```

---
