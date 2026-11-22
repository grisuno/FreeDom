# `src/compositor.c`

> Source: [src/compositor.c:1](../../src/compositor.c#L1) | language `c` | coverage 71.4% | [API index](../index.md)

## Contents

- **Functions:** [`cx_forms_stacking_context`](#cx_forms_stacking_context), [`cx_box_layer`](#cx_box_layer), [`cx_item_compare`](#cx_item_compare), [`cx_sort`](#cx_sort), [`cx_ink_reach`](#cx_ink_reach), [`cx_span_visible`](#cx_span_visible)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_compositor_c__cx_box_layer(["cx_box_layer"])
    n_src_compositor_c__cx_forms_stacking_context(["cx_forms_stacking_context"])
    n_src_compositor_c__cx_sort(["cx_sort"])
    n_src_compositor_c__cx_item_compare(["cx_item_compare"])
    n_src_compositor_c__cx_box_layer --> n_src_compositor_c__cx_forms_stacking_context
    n_src_compositor_c__cx_sort --> n_src_compositor_c__cx_item_compare
```

## Functions

<a id="cx_forms_stacking_context"></a>

### `cx_forms_stacking_context`

`function` | [src/compositor.c:18](../../src/compositor.c#L18)

```c
int cx_forms_stacking_context(const cx_style *s)
```

Does this box establish a stacking context?

(The root context is the caller's.) NULL-safe: returns 0. See spec/compositor.md section 2 for the rule set.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `cx_style *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`cx_forms_stacking_context`](#cx_forms_stacking_context) (include/compositor.h:60).

*Called by:* [`cx_box_layer`](#cx_box_layer)

---

<a id="cx_box_layer"></a>

### `cx_box_layer`

`function` | [src/compositor.c:36](../../src/compositor.c#L36)

```c
cx_layer cx_box_layer(const cx_style *s)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `cx_style *` |  |  |

**Returns:** `cx_layer`

*Calls:* [`cx_forms_stacking_context`](#cx_forms_stacking_context)

*Called by:* [`bt_resolve_positioning_ex`](src.box_tree.c.md#bt_resolve_positioning_ex)

---

<a id="cx_item_compare"></a>

### `cx_item_compare`

`function` | [src/compositor.c:56](../../src/compositor.c#L56)

```c
int cx_item_compare(const cx_item *a, const cx_item *b)
```

Total paint order: layer ascending, then z-index ascending (auto == 0), then document order ascending.

Returns <0, 0 or >0 like a qsort comparator. NULL-safe (a NULL operand sorts first, defensively).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `cx_item *` |  |  |
| `b` | `cx_item *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`cx_item_compare`](#cx_item_compare) (include/compositor.h:80).

*Called by:* [`cx_sort`](#cx_sort)

---

<a id="cx_sort"></a>

### `cx_sort`

`function` | [src/compositor.c:72](../../src/compositor.c#L72)

```c
void cx_sort(cx_item *items, size_t n)
```

Stable insertion sort: n is bounded by the caller (BT_MAX_POSITIONED), so O(n^2) is fine, and stability keeps equal-key boxes in their original relative order (document order is already the final tie-break, so this only matters on true key collisions).

No allocation.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `items` | `cx_item *` |  |  |
| `n` | `size_t` |  |  |

*Calls:* [`cx_item_compare`](#cx_item_compare)

---

<a id="cx_ink_reach"></a>

### `cx_ink_reach`

`function` | [src/compositor.c:87](../../src/compositor.c#L87)

```c
double cx_ink_reach(const int (*layers)[6], int n, int outline_w, int outline_offset)
```

How far (px, >= 0) a box's paint may reach beyond its border box (spec/compositor.md, tanda 95): each outset box-shadow layer {dx, dy, blur, spread, color, inset} with color != -1 reaches max(|dx|,|dy|) + max(spread,0) + ceil(1.5*blur) + 1; an inset layer stays inside; an outline reaches outline_w + max(offset,0) when outline_w > 0.

The max. layers NULL or n <= 0 counts only the outline.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `layers` | `int (* )[6]` |  |  |
| `n` | `int` |  |  |
| `outline_w` | `int` |  |  |
| `outline_offset` | `int` |  |  |

**Returns:** `double`

> **Inherited:** Documentation from [`cx_ink_reach`](#cx_ink_reach) (include/compositor.h:91).

---

<a id="cx_span_visible"></a>

### `cx_span_visible`

`function` | [src/compositor.c:104](../../src/compositor.c#L104)

```c
int cx_span_visible(double top, double h, double reach, double view_top, double view_h)
```

1 when [top - reach, top + h + reach] touches [view_top, view_top + view_h] (edges included), else 0.

Any non-finite input is visible (fail-open: content never vanishes).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `top` | `double` |  |  |
| `h` | `double` |  |  |
| `reach` | `double` |  |  |
| `view_top` | `double` |  |  |
| `view_h` | `double` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`cx_span_visible`](#cx_span_visible) (include/compositor.h:95).

---
