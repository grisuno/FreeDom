# `src/css_mq.c`

> Source: [src/css_mq.c:1](../../src/css_mq.c#L1) | language `c` | coverage 18.2% | [API index](../index.md)

## Contents

- **Structs:** [`mq_cur`](#mq_cur), [`fval`](#fval)
- **Type Aliases:** [`kind`](#kind)
- **Functions:** [`cmq_matches`](#cmq_matches)
- **Macros:** [`CMQ_DEVICE_W`](#cmq_device_w), [`CMQ_DPPX`](#cmq_dppx), [`CMQ_COLOR_BITS`](#cmq_color_bits), [`CMQ_DPI_PER_DPPX`](#cmq_dpi_per_dppx), [`CMQ_CM_PER_IN`](#cmq_cm_per_in), [`MQ_EPS`](#mq_eps)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class mq_cur
    <<struct>> mq_cur
    class kind
    <<type_alias>> kind
    class fval
    <<struct>> fval
```

## Structs

<a id="mq_cur"></a>

### `mq_cur`

`struct` | [src/css_mq.c:25](../../src/css_mq.c#L25)

```c
typedef struct mq_cur
```

---

<a id="fval"></a>

### `fval`

`struct` | [src/css_mq.c:96](../../src/css_mq.c#L96)

```c
typedef struct fval
```

---

## Type Aliases

<a id="kind"></a>

### `kind`

`type_alias` | [src/css_mq.c:95](../../src/css_mq.c#L95)

```c
typedef struct fval { fv_kind kind;
```

---

## Functions

<a id="cmq_matches"></a>

### `cmq_matches`

`function` | [src/css_mq.c:458](../../src/css_mq.c#L458)

```c
int cmq_matches(const char *s, size_t len, const cmq_env *env)
```

1 iff the media query list s[0,len) matches env; malformed/unknown parts fail closed.

An empty list matches (all). NULL s or env -> 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `env` | `cmq_env *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`cmq_matches`](#cmq_matches) (include/css_mq.h:28).

---

## Macros

<a id="cmq_device_w"></a>

### `CMQ_DEVICE_W`

`macro` | [src/css_mq.c:18](../../src/css_mq.c#L18)

```c
#define CMQ_DEVICE_W
```

The device the engine claims to be (anti-fingerprinting): never measured.

---

<a id="cmq_dppx"></a>

### `CMQ_DPPX`

`macro` | [src/css_mq.c:20](../../src/css_mq.c#L20)

```c
#define CMQ_DPPX
```

---

<a id="cmq_color_bits"></a>

### `CMQ_COLOR_BITS`

`macro` | [src/css_mq.c:21](../../src/css_mq.c#L21)

```c
#define CMQ_COLOR_BITS
```

---

<a id="cmq_dpi_per_dppx"></a>

### `CMQ_DPI_PER_DPPX`

`macro` | [src/css_mq.c:22](../../src/css_mq.c#L22)

```c
#define CMQ_DPI_PER_DPPX
```

---

<a id="cmq_cm_per_in"></a>

### `CMQ_CM_PER_IN`

`macro` | [src/css_mq.c:23](../../src/css_mq.c#L23)

```c
#define CMQ_CM_PER_IN
```

---

<a id="mq_eps"></a>

### `MQ_EPS`

`macro` | [src/css_mq.c:203](../../src/css_mq.c#L203)

```c
#define MQ_EPS
```

---
