# `src/css_atrule.c`

> Source: [src/css_atrule.c:1](../../src/css_atrule.c#L1) | language `c` | coverage 80.0% | [API index](../index.md)

## Contents

- **Functions:** [`car_supports`](#car_supports), [`car_layer_rank`](#car_layer_rank), [`car_effective_spec`](#car_effective_spec)
- **Macros:** [`CAR_TEXT_MAX`](#car_text_max)

## Functions

<a id="car_supports"></a>

### `car_supports`

`function` | [src/css_atrule.c:141](../../src/css_atrule.c#L141)

```c
int car_supports(const char *s, size_t a, size_t b, const car_ops *ops)
```

Evaluates the @supports prelude s[a,b).

1 = true, 0 = false or malformed.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |
| `a` | `size_t` |  |  |
| `b` | `size_t` |  |  |
| `ops` | `car_ops *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`car_supports`](#car_supports) (include/css_atrule.h:29).

---

<a id="car_layer_rank"></a>

### `car_layer_rank`

`function` | [src/css_atrule.c:148](../../src/css_atrule.c#L148)

```c
int car_layer_rank(car_layers *L, const char *name, size_t len)
```

Rank (1..CAR_MAX_LAYERS) of the layer whose full dotted name is name[0,len), registering it on first sight. len == 0 registers a fresh anonymous layer.

A name at/over CAR_LAYER_NAME_MAX, or a full registry, maps to CAR_MAX_LAYERS.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `L` | `car_layers *` |  |  |
| `name` | `char *` |  |  |
| `len` | `size_t` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`car_layer_rank`](#car_layer_rank) (include/css_atrule.h:40).

---

<a id="car_effective_spec"></a>

### `car_effective_spec`

`function` | [src/css_atrule.c:171](../../src/css_atrule.c#L171)

```c
int car_effective_spec(int spec, int layer, int important)
```

Folds layer rank and specificity into one comparable value (layer first). layer 0 = unlayered.

Important declarations reverse the layer order.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `spec` | `int` |  |  |
| `layer` | `int` |  |  |
| `important` | `int` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`car_effective_spec`](#car_effective_spec) (include/css_atrule.h:44).

---

## Macros

<a id="car_text_max"></a>

### `CAR_TEXT_MAX`

`macro` | [src/css_atrule.c:13](../../src/css_atrule.c#L13)

```c
#define CAR_TEXT_MAX
```

Scratch size for one declaration or selector handed to the caller.

Longer text cannot be a declaration this engine accepts (CSS_URL_MAX-sized values) and is answered false.

---
