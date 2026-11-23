# `src/scroll_req.c`

> Source: [src/scroll_req.c:1](../../src/scroll_req.c#L1) | language `c` | coverage 80.0% | [API index](../index.md)

## Contents

- **Functions:** [`srq_encode`](#srq_encode), [`srq_decode`](#srq_decode), [`srq_target`](#srq_target), [`srq_smooth`](#srq_smooth)

## Functions

<a id="srq_encode"></a>

### `srq_encode`

`function` | [src/scroll_req.c:21](../../src/scroll_req.c#L21)

```c
void srq_encode(const srq_req *r, int32_t out[SRQ_WIRE_N])
```

Writes r as SRQ_WIRE_N int32: kind, behavior, block, y, margin_top, margin_bottom, n, nsub.

Doubles are rounded and clamped to [-SRQ_MAX_COORD, SRQ_MAX_COORD] (NaN => 0); a NULL argument writes nothing.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `r` | `srq_req *` |  |  |
| `SRQ_WIRE_N` | `int32_t out[ ]` |  |  |

> **Inherited:** Documentation from [`srq_encode`](#srq_encode) (include/scroll_req.h:58).

---

<a id="srq_decode"></a>

### `srq_decode`

`function` | [src/scroll_req.c:37](../../src/scroll_req.c#L37)

```c
int srq_decode(const int32_t in[SRQ_WIRE_N], size_t max_handles, srq_req *out)
```

Reads a record written by srq_encode, validating EVERY field: enums in range, |coords| <= SRQ_MAX_COORD, n <= max_handles, nsub <= n, handles only (and always) for SRQ_ELEMENT.

Returns 0 on success, -1 otherwise (*out is then SRQ_NONE when out is not NULL). A record of kind SRQ_NONE with every other field 0 is valid.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `SRQ_WIRE_N` | `int32_t in[ ]` |  |  |
| `max_handles` | `size_t` |  |  |
| `out` | `srq_req *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`srq_decode`](#srq_decode) (include/scroll_req.h:64).

---

<a id="srq_target"></a>

### `srq_target`

`function` | [src/scroll_req.c:80](../../src/scroll_req.c#L80)

```c
int srq_target(const srq_req *r, const srq_view *v, double el_top, double el_bottom, double *out)
```

The scroll offset r asks for, in [0, v->max_scroll]. el_top/el_bottom are the target's document box (SRQ_ELEMENT only; ignored otherwise).

The optimal viewing region is the viewport minus the root's scroll-padding (ignored when it would leave no room); the target's box grows by its scroll-margin. Returns 0 and *out; -1 (*out untouched) on NULL, SRQ_NONE, a non-finite input, view_h <= 0 or max_scroll < 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `r` | `srq_req *` |  |  |
| `v` | `srq_view *` |  |  |
| `el_top` | `double` |  |  |
| `el_bottom` | `double` |  |  |
| `out` | `double *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`srq_target`](#srq_target) (include/scroll_req.h:71).

---

<a id="srq_smooth"></a>

### `srq_smooth`

`function` | [src/scroll_req.c:110](../../src/scroll_req.c#L110)

```c
int srq_smooth(const srq_req *r, int root_smooth)
```

1 when the scroll should animate: SRQ_SMOOTH, or SRQ_AUTO with the root's computed scroll-behavior smooth (root_smooth != 0).

0 otherwise or on NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `r` | `srq_req *` |  |  |
| `root_smooth` | `int` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`srq_smooth`](#srq_smooth) (include/scroll_req.h:76).

---
