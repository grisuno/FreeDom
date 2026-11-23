# `include/link_preview.h`

> Source: [include/link_preview.h:1](../../include/link_preview.h#L1) | language `h` | coverage 16.7% | [API index](../index.md)

## Contents

- **Structs:** [`lp_preview`](#lp_preview)
- **Enums:** [`lp_kind`](#lp_kind), [`lp_status`](#lp_status)
- **Type Aliases:** [`kind`](#kind)
- **Macros:** [`LP_TEXT_MAX`](#lp_text_max)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class lp_kind
    <<enum>> lp_kind
    class kind
    <<type_alias>> kind
    class lp_preview
    <<struct>> lp_preview
    class lp_status
    <<enum>> lp_status
```

## Structs

<a id="lp_preview"></a>

### `lp_preview`

`struct` | [include/link_preview.h:29](../../include/link_preview.h#L29)

```c
typedef struct lp_preview
```

---

## Enums

<a id="lp_kind"></a>

### `lp_kind`

`enum` | [include/link_preview.h:23](../../include/link_preview.h#L23)

```c
typedef enum lp_kind
```

---

<a id="lp_status"></a>

### `lp_status`

`enum` | [include/link_preview.h:36](../../include/link_preview.h#L36)

```c
typedef enum lp_status
```

---

## Type Aliases

<a id="kind"></a>

### `kind`

`type_alias` | [include/link_preview.h:28](../../include/link_preview.h#L28)

```c
typedef struct lp_preview { lp_kind kind;
```

---

## Macros

<a id="lp_text_max"></a>

### `LP_TEXT_MAX`

`macro` | [include/link_preview.h:21](../../include/link_preview.h#L21)

```c
#define LP_TEXT_MAX
```

Upper bound of lp_preview.text including its NUL: what a one-line strip can show.

---
