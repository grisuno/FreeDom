# `include/interp.h`

> Source: [include/interp.h:1](../../include/interp.h#L1) | language `h` | coverage 31.8% | [API index](../index.md)

## Contents

- **Structs:** [`ip_ease_fn`](#ip_ease_fn), [`ip_keyframe`](#ip_keyframe), [`ip_anim`](#ip_anim)
- **Enums:** [`ip_easing`](#ip_easing), [`ip_val_kind`](#ip_val_kind), [`ip_direction`](#ip_direction), [`ip_fill_mode`](#ip_fill_mode)
- **Type Aliases:** [`kind`](#kind), [`pct`](#pct), [`val_kind`](#val_kind)
- **Functions:** [`ip_ease`](#ip_ease), [`ip_lerp`](#ip_lerp), [`ip_lerp_color`](#ip_lerp_color), [`ip_interp`](#ip_interp), [`ip_kf_interp`](#ip_kf_interp), [`ip_anim_init`](#ip_anim_init), [`ip_anim_tick`](#ip_anim_tick), [`ip_anim_current`](#ip_anim_current), [`ip_anim_done`](#ip_anim_done)
- **Macros:** [`IP_MAX_KEYFRAMES`](#ip_max_keyframes), [`IP_ITERATION_INFINITE`](#ip_iteration_infinite)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class ip_easing
    <<enum>> ip_easing
    class kind
    <<type_alias>> kind
    class ip_ease_fn
    <<struct>> ip_ease_fn
    class ip_val_kind
    <<enum>> ip_val_kind
    class pct
    <<type_alias>> pct
    class ip_keyframe
    <<struct>> ip_keyframe
    class ip_direction
    <<enum>> ip_direction
    class ip_fill_mode
    <<enum>> ip_fill_mode
    class val_kind
    <<type_alias>> val_kind
    class ip_anim
    <<struct>> ip_anim
```

## Structs

<a id="ip_ease_fn"></a>

### `ip_ease_fn`

`struct` | [include/interp.h:38](../../include/interp.h#L38)

```c
typedef struct ip_ease_fn
```

---

<a id="ip_keyframe"></a>

### `ip_keyframe`

`struct` | [include/interp.h:70](../../include/interp.h#L70)

```c
typedef struct ip_keyframe
```

---

<a id="ip_anim"></a>

### `ip_anim`

`struct` | [include/interp.h:101](../../include/interp.h#L101)

```c
typedef struct ip_anim
```

---

## Enums

<a id="ip_easing"></a>

### `ip_easing`

`enum` | [include/interp.h:25](../../include/interp.h#L25)

```c
typedef enum ip_easing
```

---

<a id="ip_val_kind"></a>

### `ip_val_kind`

`enum` | [include/interp.h:54](../../include/interp.h#L54)

```c
typedef enum ip_val_kind
```

---

<a id="ip_direction"></a>

### `ip_direction`

`enum` | [include/interp.h:87](../../include/interp.h#L87)

```c
typedef enum ip_direction
```

---

<a id="ip_fill_mode"></a>

### `ip_fill_mode`

`enum` | [include/interp.h:94](../../include/interp.h#L94)

```c
typedef enum ip_fill_mode
```

---

## Type Aliases

<a id="kind"></a>

### `kind`

`type_alias` | [include/interp.h:37](../../include/interp.h#L37)

```c
typedef struct ip_ease_fn { ip_easing kind;
```

---

<a id="pct"></a>

### `pct`

`type_alias` | [include/interp.h:69](../../include/interp.h#L69)

```c
typedef struct ip_keyframe { double pct;
```

define IP_MAX_KEYFRAMES 16

---

<a id="val_kind"></a>

### `val_kind`

`type_alias` | [include/interp.h:100](../../include/interp.h#L100)

```c
typedef struct ip_anim { ip_val_kind val_kind;
```

---

## Functions

<a id="ip_ease"></a>

### `ip_ease`

`function` | [include/interp.h:48](../../include/interp.h#L48)

```c
double ip_ease(double t, const ip_ease_fn *fn);
```

Compute eased t for normalized t ∈ [0,1].

Returns value ∈ [0,1]. Clamped: t < 0 → 0, t > 1 → 1. NULL-safe: returns t.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `double` |  |  |
| `fn` | `ip_ease_fn *` |  |  |

**Returns:** `double`

---

<a id="ip_lerp"></a>

### `ip_lerp`

`function` | [include/interp.h:60](../../include/interp.h#L60)

```c
double ip_lerp(double a, double b, double t);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `double` |  |  |
| `b` | `double` |  |  |
| `t` | `double` |  |  |

**Returns:** `double`

---

<a id="ip_lerp_color"></a>

### `ip_lerp_color`

`function` | [include/interp.h:61](../../include/interp.h#L61)

```c
uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c1` | `uint32_t` |  |  |
| `c2` | `uint32_t` |  |  |
| `t` | `double` |  |  |

**Returns:** `uint32_t`

---

<a id="ip_interp"></a>

### `ip_interp`

`function` | [include/interp.h:62](../../include/interp.h#L62)

```c
double ip_interp(ip_val_kind kind, double a, double b, double t);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `kind` | `ip_val_kind` |  |  |
| `a` | `double` |  |  |
| `b` | `double` |  |  |
| `t` | `double` |  |  |

**Returns:** `double`

---

<a id="ip_kf_interp"></a>

### `ip_kf_interp`

`function` | [include/interp.h:78](../../include/interp.h#L78)

```c
double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf, int n_kf, double pct);
```

Interpolate between the two keyframes bracketing [`pct`](#pct) (0..100).

Exact match → that keyframe's value. Before first / after last → clamped to first / last. NULL/empty → 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `val_kind` | `ip_val_kind` |  |  |
| `kf` | `ip_keyframe *` |  |  |
| `n_kf` | `int` |  |  |
| `pct` | `double` |  |  |

**Returns:** `double`

---

<a id="ip_anim_init"></a>

### `ip_anim_init`

`function` | [include/interp.h:121](../../include/interp.h#L121)

```c
void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease, const ip_keyframe *kf, int n_kf, double duration_ms, double delay_ms, int iteration_count, int direction, int fill_mode);
```

Initialize. kf must outlive the animation.

NULL-safe on a.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `ip_anim *` |  |  |
| `vk` | `ip_val_kind` |  |  |
| `ease` | `ip_ease_fn *` |  |  |
| `kf` | `ip_keyframe *` |  |  |
| `n_kf` | `int` |  |  |
| `duration_ms` | `double` |  |  |
| `delay_ms` | `double` |  |  |
| `iteration_count` | `int` |  |  |
| `direction` | `int` |  |  |
| `fill_mode` | `int` |  |  |

---

<a id="ip_anim_tick"></a>

### `ip_anim_tick`

`function` | [include/interp.h:128](../../include/interp.h#L128)

```c
int ip_anim_tick(ip_anim *a, double dt_ms);
```

Advance time by dt_ms.

Returns 1 if the value changed, 0 if unchanged. Negative dt ignored. NULL-safe.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `ip_anim *` |  |  |
| `dt_ms` | `double` |  |  |

**Returns:** `int`

---

<a id="ip_anim_current"></a>

### `ip_anim_current`

`function` | [include/interp.h:131](../../include/interp.h#L131)

```c
double ip_anim_current(const ip_anim *a);
```

Current interpolated value.

0 if no keyframes or fill=none + done.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `ip_anim *` |  |  |

**Returns:** `double`

---

<a id="ip_anim_done"></a>

### `ip_anim_done`

`function` | [include/interp.h:134](../../include/interp.h#L134)

```c
int ip_anim_done(const ip_anim *a);
```

1 if animation has finished (all iterations, no forwards fill).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `ip_anim *` |  |  |

**Returns:** `int`

---

## Macros

<a id="ip_max_keyframes"></a>

### `IP_MAX_KEYFRAMES`

`macro` | [include/interp.h:68](../../include/interp.h#L68)

```c
#define IP_MAX_KEYFRAMES
```

---

<a id="ip_iteration_infinite"></a>

### `IP_ITERATION_INFINITE`

`macro` | [include/interp.h:85](../../include/interp.h#L85)

```c
#define IP_ITERATION_INFINITE
```

---
