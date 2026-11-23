# `src/smooth_scroll.c`

> Source: [src/smooth_scroll.c:1](../../src/smooth_scroll.c#L1) | language `c` | coverage 14.3% | [API index](../index.md)

smooth_scroll (sms_) -- spec/smooth_scroll.md.

## Contents

- **Functions:** [`sms_init`](#sms_init), [`sms_jump`](#sms_jump), [`sms_retarget`](#sms_retarget), [`sms_sample`](#sms_sample), [`sms_goal`](#sms_goal), [`sms_active`](#sms_active)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_smooth_scroll_c__sms_retarget(["sms_retarget"])
    n_src_smooth_scroll_c__sms_jump(["sms_jump"])
    n_src_smooth_scroll_c__sms_retarget --> n_src_smooth_scroll_c__sms_jump
```

## Functions

<a id="sms_init"></a>

### `sms_init`

`function` | [src/smooth_scroll.c:7](../../src/smooth_scroll.c#L7)

```c
void sms_init(sms_state *s, double pos)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `sms_state *` |  |  |
| `pos` | `double` |  |  |

---

<a id="sms_jump"></a>

### `sms_jump`

`function` | [src/smooth_scroll.c:15](../../src/smooth_scroll.c#L15)

```c
void sms_jump(sms_state *s, double pos)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `sms_state *` |  |  |
| `pos` | `double` |  |  |

*Called by:* [`sms_retarget`](#sms_retarget)

---

<a id="sms_retarget"></a>

### `sms_retarget`

`function` | [src/smooth_scroll.c:21](../../src/smooth_scroll.c#L21)

```c
void sms_retarget(sms_state *s, double target, double now_ms, double dur_ms)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `sms_state *` |  |  |
| `target` | `double` |  |  |
| `now_ms` | `double` |  |  |
| `dur_ms` | `double` |  |  |

*Calls:* [`sms_jump`](#sms_jump)

---

<a id="sms_sample"></a>

### `sms_sample`

`function` | [src/smooth_scroll.c:35](../../src/smooth_scroll.c#L35)

```c
double sms_sample(sms_state *s, double now_ms)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `sms_state *` |  |  |
| `now_ms` | `double` |  |  |

**Returns:** `double`

---

<a id="sms_goal"></a>

### `sms_goal`

`function` | [src/smooth_scroll.c:59](../../src/smooth_scroll.c#L59)

```c
double sms_goal(const sms_state *s)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `sms_state *` |  |  |

**Returns:** `double`

---

<a id="sms_active"></a>

### `sms_active`

`function` | [src/smooth_scroll.c:64](../../src/smooth_scroll.c#L64)

```c
int sms_active(const sms_state *s)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `sms_state *` |  |  |

**Returns:** `int`

---
