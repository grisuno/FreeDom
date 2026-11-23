# `include/anchor.h`

> Source: [include/anchor.h:1](../../include/anchor.h#L1) | language `h` | coverage 55.6% | [API index](../index.md)

## Contents

- **Enums:** [`anc_kind`](#anc_kind)
- **Functions:** [`fit`](#fit), [`anc_collect`](#anc_collect), [`anc_target_top`](#anc_target_top), [`anc_target_box`](#anc_target_box), [`anc_scroll_for`](#anc_scroll_for)
- **Macros:** [`ANC_MAX_FRAGMENT`](#anc_max_fragment), [`ANC_MAX_HANDLES`](#anc_max_handles)

## Enums

<a id="anc_kind"></a>

### `anc_kind`

`enum` | [include/anchor.h:26](../../include/anchor.h#L26)

```c
typedef enum anc_kind
```

---

## Functions

<a id="fit"></a>

### `fit`

`function` | [include/anchor.h:35](../../include/anchor.h#L35)

```c
* result does not fit (out is then "" when cap > 0). */ size_t anc_percent_decode(const char *in, char *out, size_t cap);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cap` | `is then "" when > 0` |  |  |

**Returns:** `* result does not`

*Called by:* [`lp_describe`](src.link_preview.c.md#lp_describe)

---

<a id="anc_collect"></a>

### `anc_collect`

`function` | [include/anchor.h:50](../../include/anchor.h#L50)

```c
size_t anc_collect(const dom_index *idx, dom_node_id target, dom_node_id *out, size_t cap, size_t *nsub);
```

Writes target and its element subtree in preorder (*nsub handles), then the elements that follow the subtree in tree order, up to cap handles in all (cap is clamped to ANC_MAX_HANDLES).

Returns the count written; 0 (and *nsub = 0) on NULL arguments, cap 0 or an invalid target.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `target` | `dom_node_id` |  |  |
| `out` | `dom_node_id *` |  |  |
| `cap` | `size_t` |  |  |
| `nsub` | `size_t *` |  |  |

**Returns:** `size_t`

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_anchor.c.md#llvmfuzzertestoneinput), [`navigation`](src.tab.c.md#navigation)

---

<a id="anc_target_top"></a>

### `anc_target_top`

`function` | [include/anchor.h:57](../../include/anchor.h#L57)

```c
int anc_target_top(const jg_table *g, const dom_node_id *h, size_t n, size_t nsub, double *top);
```

The document offset of the target from a FINISHED geometry table (jg_finish): the smallest y among the rects of h[0, nsub); when none of them painted, the y of the first of h[nsub, n) that did.

0 and *top on success; -1 (top untouched) when no handle has a rect or an argument is NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `g` | `jg_table *` |  |  |
| `h` | `dom_node_id *` |  |  |
| `n` | `size_t` |  |  |
| `nsub` | `size_t` |  |  |
| `top` | `double *` |  |  |

**Returns:** `int`

---

<a id="anc_target_box"></a>

### `anc_target_box`

`function` | [include/anchor.h:63](../../include/anchor.h#L63)

```c
int anc_target_box(const jg_table *g, const dom_node_id *h, size_t n, size_t nsub, double *top, double *bottom);
```

As anc_target_top, plus the target's bottom: the largest y + h among the subtree's rects (= *top when the position came from a following element: an empty target is a point).

0 and both outputs; -1 (outputs untouched) when nothing painted or on NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `g` | `jg_table *` |  |  |
| `h` | `dom_node_id *` |  |  |
| `n` | `size_t` |  |  |
| `nsub` | `size_t` |  |  |
| `top` | `double *` |  |  |
| `bottom` | `double *` |  |  |

**Returns:** `int`

---

<a id="anc_scroll_for"></a>

### `anc_scroll_for`

`function` | [include/anchor.h:68](../../include/anchor.h#L68)

```c
double anc_scroll_for(double top, double max_scroll);
```

The scroll offset that puts top at the top of the viewport, clamped to [0, max_scroll].

Non-finite arguments or max_scroll < 0 => 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `top` | `double` |  |  |
| `max_scroll` | `double` |  |  |

**Returns:** `double`

---

## Macros

<a id="anc_max_fragment"></a>

### `ANC_MAX_FRAGMENT`

`macro` | [include/anchor.h:23](../../include/anchor.h#L23)

```c
#define ANC_MAX_FRAGMENT
```

---

<a id="anc_max_handles"></a>

### `ANC_MAX_HANDLES`

`macro` | [include/anchor.h:24](../../include/anchor.h#L24)

```c
#define ANC_MAX_HANDLES
```

bytes including the NUL (= LN_MAX_FRAGMENT)

---
