# `include/text_case.h`

> Source: [include/text_case.h:1](../../include/text_case.h#L1) | language `h` | coverage 75.0% | [API index](../index.md)

Case mapping for text-transform and synthesized small caps (spec/text_case.md).

Pure: no I/O, no state, no allocation.

## Contents

- **Structs:** [`tc_run`](#tc_run)
- **Functions:** [`cp`](#cp), [`tc_lower`](#tc_lower), [`tc_is_lower`](#tc_is_lower), [`tc_transform`](#tc_transform), [`tc_smallcaps_runs`](#tc_smallcaps_runs)
- **Macros:** [`TC_SMALLCAPS_SCALE`](#tc_smallcaps_scale)

## Structs

<a id="tc_run"></a>

### `tc_run`

`struct` | [include/text_case.h:33](../../include/text_case.h#L33)

```c
typedef struct
```

One maximal run of tc_smallcaps_runs.

---

## Functions

<a id="cp"></a>

### `cp`

`function` | [include/text_case.h:19](../../include/text_case.h#L19)

```c
* cp (identity otherwise), so a transformed text keeps its length. */ uint32_t tc_upper(uint32_t cp);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `otherwise` | `identity` |  |  |

**Returns:** `*`

---

<a id="tc_lower"></a>

### `tc_lower`

`function` | [include/text_case.h:21](../../include/text_case.h#L21)

```c
uint32_t tc_lower(uint32_t cp);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cp` | `uint32_t` |  |  |

**Returns:** `uint32_t`

---

<a id="tc_is_lower"></a>

### `tc_is_lower`

`function` | [include/text_case.h:24](../../include/text_case.h#L24)

```c
int tc_is_lower(uint32_t cp);
```

1 when cp is a lowercase letter tc_upper maps to something else.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cp` | `uint32_t` |  |  |

**Returns:** `int`

---

<a id="tc_transform"></a>

### `tc_transform`

`function` | [include/text_case.h:29](../../include/text_case.h#L29)

```c
size_t tc_transform(const char *s, size_t n, int transform, int word_start, char *out, size_t cap);
```

Copies s[0,n) to out applying transform (CSS_TT_UPPERCASE / _LOWERCASE / _CAPITALIZE; any other value copies verbatim). word_start says s begins a word (for capitalize).

Returns n, or 0 (out untouched) when s/out is NULL or cap < n.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `n` | `size_t` |  |  |
| `transform` | `int` |  |  |
| `word_start` | `int` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

---

<a id="tc_smallcaps_runs"></a>

### `tc_smallcaps_runs`

`function` | [include/text_case.h:41](../../include/text_case.h#L41)

```c
size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap);
```

Splits s[0,n) into consecutive maximal runs of lowercase letters vs the rest, covering the whole text in order.

Returns the runs written; when cap is too small the last run absorbs the remainder. 0 for NULL/empty input or cap 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `n` | `size_t` |  |  |
| `out` | `tc_run *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

---

## Macros

<a id="tc_smallcaps_scale"></a>

### `TC_SMALLCAPS_SCALE`

`macro` | [include/text_case.h:15](../../include/text_case.h#L15)

```c
#define TC_SMALLCAPS_SCALE
```

Font-size factor of a synthesized small capital (Gecko's SMALL_CAPS_SCALE_FACTOR).

---
