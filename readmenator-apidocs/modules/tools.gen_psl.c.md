# `tools/gen_psl.c`

> Source: [tools/gen_psl.c:1](../../tools/gen_psl.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Structs:** [`vec`](#vec)
- **Functions:** [`main`](#main)
- **Macros:** [`_POSIX_C_SOURCE`](#_posix_c_source)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_tools_gen_psl_c__main(["main"])
    n_src_css_c__emit["css.emit"]
    n_tools_gen_psl_c__main -.-> n_src_css_c__emit
```

## Structs

<a id="vec"></a>

### `vec`

`struct` | [tools/gen_psl.c:21](../../tools/gen_psl.c#L21)

```c
typedef struct vec
```

---

## Functions

<a id="main"></a>

### `main`

`function` | [tools/gen_psl.c:67](../../tools/gen_psl.c#L67)

```c
int main(int argc, char **argv)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

**Returns:** `int`

*Calls:* [`emit`](src.css.c.md#emit)

---

## Macros

<a id="_posix_c_source"></a>

### `_POSIX_C_SOURCE`

`macro` | [tools/gen_psl.c:15](../../tools/gen_psl.c#L15)

```c
#define _POSIX_C_SOURCE
```

---
