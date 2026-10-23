# `include/css_computed.h`

> Source: [include/css_computed.h:1](../../include/css_computed.h#L1) | language `h` | coverage 33.3% | [API index](../index.md)

## Contents

- **Structs:** [`ccm_input`](#ccm_input)
- **Functions:** [`ccm_get`](#ccm_get), [`ccm_property_count`](#ccm_property_count), [`ccm_property_name`](#ccm_property_name)
- **Macros:** [`CCM_VALUE_MAX`](#ccm_value_max)

## Structs

<a id="ccm_input"></a>

### `ccm_input`

`struct` | [include/css_computed.h:19](../../include/css_computed.h#L19)

```c
typedef struct ccm_input
```

---

## Functions

<a id="ccm_get"></a>

### `ccm_get`

`function` | [include/css_computed.h:29](../../include/css_computed.h#L29)

```c
size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap);
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

---

<a id="ccm_property_count"></a>

### `ccm_property_count`

`function` | [include/css_computed.h:32](../../include/css_computed.h#L32)

```c
size_t ccm_property_count(void);
```

The properties ccm_get knows, for enumeration (length/item/cssText).

**Returns:** `size_t`

---

<a id="ccm_property_name"></a>

### `ccm_property_name`

`function` `const` | [include/css_computed.h:33](../../include/css_computed.h#L33)

```c
const char *ccm_property_name(size_t i);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `i` | `size_t` |  |  |

**Returns:** `char *`

---

## Macros

<a id="ccm_value_max"></a>

### `CCM_VALUE_MAX`

`macro` | [include/css_computed.h:17](../../include/css_computed.h#L17)

```c
#define CCM_VALUE_MAX
```

---
