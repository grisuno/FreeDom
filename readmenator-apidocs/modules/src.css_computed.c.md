# `src/css_computed.c`

> Source: [src/css_computed.c:1](../../src/css_computed.c#L1) | language `c` | coverage 28.6% | [API index](../index.md)

## Contents

- **Structs:** [`ccm_prop`](#ccm_prop)
- **Functions:** [`ccm_get`](#ccm_get), [`ccm_property_count`](#ccm_property_count), [`ccm_property_name`](#ccm_property_name)
- **Macros:** [`LEN_FIELD`](#len_field), [`CCM_NPROPS`](#ccm_nprops)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_css_computed_c__ccm_get(["ccm_get"])
    n_gui_browser_ui_c__strcmp["browser_ui.strcmp"]
    n_src_css_computed_c__ccm_get -.-> n_gui_browser_ui_c__strcmp
```

## Structs

<a id="ccm_prop"></a>

### `ccm_prop`

`struct` `const` | [src/css_computed.c:276](../../src/css_computed.c#L276)

```c
typedef struct ccm_prop { const char *name; ccm_fn fn; } ccm_prop;
```

---

## Functions

<a id="ccm_get"></a>

### `ccm_get`

`function` | [src/css_computed.c:310](../../src/css_computed.c#L310)

```c
size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap)
```

Writes the computed value of the kebab-case property [`prop`](include.css_decl.h.md#prop) into out (cap bytes, NUL terminated).

Returns its length, or 0 when the property is unknown, in which case out is "". in == NULL or cap == 0 => 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `in` | `ccm_input *` |  |  |
| `prop` | `char *` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`ccm_get`](#ccm_get) (include/css_computed.h:29).

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp)

---

<a id="ccm_property_count"></a>

### `ccm_property_count`

`function` | [src/css_computed.c:323](../../src/css_computed.c#L323)

```c
size_t ccm_property_count(void)
```

The properties ccm_get knows, for enumeration (length/item/cssText).

**Returns:** `size_t`

> **Inherited:** Documentation from [`ccm_property_count`](#ccm_property_count) (include/css_computed.h:32).

---

<a id="ccm_property_name"></a>

### `ccm_property_name`

`function` `const` | [src/css_computed.c:325](../../src/css_computed.c#L325)

```c
const char *ccm_property_name(size_t i)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `i` | `size_t` |  |  |

**Returns:** `char *`

---

## Macros

<a id="len_field"></a>

### `LEN_FIELD`

`macro` | [src/css_computed.c:223](../../src/css_computed.c#L223)

```c
#define LEN_FIELD(NAME, FIELD, UNSET)
```

---

<a id="ccm_nprops"></a>

### `CCM_NPROPS`

`macro` | [src/css_computed.c:308](../../src/css_computed.c#L308)

```c
#define CCM_NPROPS
```

---
