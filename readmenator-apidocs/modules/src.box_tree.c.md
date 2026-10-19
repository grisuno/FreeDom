# `src/box_tree.c`

> Source: [src/box_tree.c:1](../../src/box_tree.c#L1) | language `c` | coverage 33.3% | [API index](../index.md)

## Contents

- **Functions:** [`height`](#height), [`sized`](#sized), [`bt_layout`](#bt_layout), [`bt_containing_block`](#bt_containing_block), [`block`](#block), [`bt_resolve_positioning`](#bt_resolve_positioning), [`bt_resolve_positioning_ex`](#bt_resolve_positioning_ex), [`bt_oof_anchor`](#bt_oof_anchor), [`bt_oof_root`](#bt_oof_root), [`bt_box_hidden`](#bt_box_hidden), [`bt_oof_avail`](#bt_oof_avail), [`bt_defer_roots`](#bt_defer_roots)
- **Macros:** [`BT_LEN_AUTO`](#bt_len_auto), [`BT_WRAP_EPS`](#bt_wrap_eps)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_box_tree_c__bt_resolve_positioning(["bt_resolve_positioning"])
    n_src_box_tree_c__bt_resolve_positioning_ex(["bt_resolve_positioning_ex"])
    n_src_box_tree_c__bt_containing_block(["bt_containing_block"])
    n_src_box_tree_c__bt_defer_roots(["bt_defer_roots"])
    n_src_box_tree_c__bt_oof_root(["bt_oof_root"])
    n_src_box_tree_c__height(["height"])
    n_src_flex_layout_c__fx_auto_margins["flex_layout.fx_auto_margins"]
    n_include_compositor_h__cx_sort["compositor.cx_sort"]
    n_src_compositor_c__cx_box_layer["compositor.cx_box_layer"]
    n_src_box_tree_c__bt_resolve_positioning --> n_src_box_tree_c__bt_resolve_positioning_ex
    n_src_box_tree_c__bt_resolve_positioning_ex --> n_src_box_tree_c__bt_containing_block
    n_src_box_tree_c__bt_defer_roots --> n_src_box_tree_c__bt_oof_root
    n_src_box_tree_c__height -.-> n_src_flex_layout_c__fx_auto_margins
    n_src_box_tree_c__bt_resolve_positioning_ex -.-> n_include_compositor_h__cx_sort
    n_src_box_tree_c__bt_resolve_positioning_ex -.-> n_src_compositor_c__cx_box_layer
```

## Functions

<a id="height"></a>

### `height`

`function` | [src/box_tree.c:78](../../src/box_tree.c#L78)

```c
* exactly that height (Flexbox 9.4 step 15). * * wrap_reverse (node->wrap_reverse): when node->...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `step` | `Flexbox 9.4 15` |  |  |

**Returns:** `* exactly that`

*Calls:* [`fx_auto_margins`](src.flex_layout.c.md#fx_auto_margins)

---

<a id="sized"></a>

### `sized`

`function` | [src/box_tree.c:350](../../src/box_tree.c#L350)

```c
* the tracks are sized (CSS Grid 1 11.5, items spanning several tracks come * last);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `Grid` | `CSS 1 11.5` |  |  |
| `last` | `items spanning several tracks come *` |  |  |

**Returns:** `* the tracks are`

---

<a id="bt_layout"></a>

### `bt_layout`

`function` | [src/box_tree.c:465](../../src/box_tree.c#L465)

```c
bt_status bt_layout(bt_node *root, double avail_w)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `root` | `bt_node *` |  |  |
| `avail_w` | `double` |  |  |

**Returns:** `bt_status`

---

<a id="bt_containing_block"></a>

### `bt_containing_block`

`function` | [src/box_tree.c:555](../../src/box_tree.c#L555)

```c
void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i, const double *box_x, const double *box_y, const double *box_w, const double *box_h, const char *placed, double viewport_w, double viewport_h, double *cb_x, double *cb_y, double *cb_w, double *cb_h)
```

The containing block of box i as the positioning solver resolves it: the viewport for FIXED (and for ABSOLUTE with no positioned ancestor), else the geometry of the nearest positioned ancestor -- climbing to the nearest PLACED ancestor when [`placed`](include.box_tree.h.md#placed) (may be NULL) says it never got a rect.

Any non-absolute box answers the viewport. Pure; out pointers must be non-NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `boxes` | `pv_box_def *` |  |  |
| `nbox` | `size_t` |  |  |
| `i` | `size_t` |  |  |
| `box_x` | `double *` |  |  |
| `box_y` | `double *` |  |  |
| `box_w` | `double *` |  |  |
| `box_h` | `double *` |  |  |
| `placed` | `char *` |  |  |
| `viewport_w` | `double` |  |  |
| `viewport_h` | `double` |  |  |
| `cb_x` | `double *` |  |  |
| `cb_y` | `double *` |  |  |
| `cb_w` | `double *` |  |  |
| `cb_h` | `double *` |  |  |

> **Inherited:** Documentation from [`bt_containing_block`](#bt_containing_block) (include/box_tree.h:262).

*Called by:* [`bt_resolve_positioning_ex`](#bt_resolve_positioning_ex)

---

<a id="block"></a>

### `block`

`function` | [src/box_tree.c:566](../../src/box_tree.c#L566)

```c
* true block (same flow neighbourhood), strictly better than zeros. NULL * placed keeps lega...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `neighbourhood` | `same flow` |  |  |

**Returns:** `* true`

---

<a id="bt_resolve_positioning"></a>

### `bt_resolve_positioning`

`function` | [src/box_tree.c:585](../../src/box_tree.c#L585)

```c
bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox, const double *box_x, const double *box_y, const double *box_w, const double *box_h, double viewport_w, double viewport_h, bt_positioned *out, size_t out_cap, size_t *out_count)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `boxes` | `pv_box_def *` |  |  |
| `nbox` | `size_t` |  |  |
| `box_x` | `double *` |  |  |
| `box_y` | `double *` |  |  |
| `box_w` | `double *` |  |  |
| `box_h` | `double *` |  |  |
| `viewport_w` | `double` |  |  |
| `viewport_h` | `double` |  |  |
| `out` | `bt_positioned *` |  |  |
| `out_cap` | `size_t` |  |  |
| `out_count` | `size_t *` |  |  |

**Returns:** `bt_status`

*Calls:* [`bt_resolve_positioning_ex`](#bt_resolve_positioning_ex)

---

<a id="bt_resolve_positioning_ex"></a>

### `bt_resolve_positioning_ex`

`function` | [src/box_tree.c:596](../../src/box_tree.c#L596)

```c
bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox, const double *box_x, const double *box_y, const double *box_w, const double *box_h, const double *static_x, const double *static_y, const char *placed, double viewport_w, double viewport_h, bt_positioned *out, size_t out_cap, size_t *out_count)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `boxes` | `pv_box_def *` |  |  |
| `nbox` | `size_t` |  |  |
| `box_x` | `double *` |  |  |
| `box_y` | `double *` |  |  |
| `box_w` | `double *` |  |  |
| `box_h` | `double *` |  |  |
| `static_x` | `double *` |  |  |
| `static_y` | `double *` |  |  |
| `placed` | `char *` |  |  |
| `viewport_w` | `double` |  |  |
| `viewport_h` | `double` |  |  |
| `out` | `bt_positioned *` |  |  |
| `out_cap` | `size_t` |  |  |
| `out_count` | `size_t *` |  |  |

**Returns:** `bt_status`

*Calls:* [`cx_sort`](include.compositor.h.md#cx_sort), [`bt_containing_block`](#bt_containing_block), [`cx_box_layer`](src.compositor.c.md#cx_box_layer)

*Called by:* [`bt_resolve_positioning`](#bt_resolve_positioning)

---

<a id="bt_oof_anchor"></a>

### `bt_oof_anchor`

`function` | [src/box_tree.c:768](../../src/box_tree.c#L768)

```c
int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)
```

Stage 2d out-of-flow subtree classification (spec/box_engine.md).

Both walk the parent_id chain from `bid` (self first) looking for a box whose position is ABSOLUTE or FIXED: - bt_oof_anchor returns the NEAREST such box: the box a block's content belongs to for out-of-flow measurement and painting (a nested absolute box owns its own content). - bt_oof_root returns the OUTERMOST such box: the box whose static position the flow records when it skips the subtree. Both return -1 (in flow) when the chain has none, and FAIL OPEN to -1 on NULL boxes, out-of-range/negative bid, a dangling link or a parent cycle -- a misclassified hostile chain renders in flow (visible) rather than vanishing. Pure; bounded by nbox links; no allocation.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `boxes` | `pv_box_def *` |  |  |
| `nbox` | `size_t` |  |  |
| `bid` | `int` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`bt_oof_anchor`](#bt_oof_anchor) (include/box_tree.h:247).

---

<a id="bt_oof_root"></a>

### `bt_oof_root`

`function` | [src/box_tree.c:772](../../src/box_tree.c#L772)

```c
int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `boxes` | `pv_box_def *` |  |  |
| `nbox` | `size_t` |  |  |
| `bid` | `int` |  |  |

**Returns:** `int`

*Called by:* [`bt_defer_roots`](#bt_defer_roots)

---

<a id="bt_box_hidden"></a>

### `bt_box_hidden`

`function` | [src/box_tree.c:776](../../src/box_tree.c#L776)

```c
int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)
```

Stage 2b visibility gate: 1 when the box at `bid` or any ancestor on the parent_id chain has visibility HIDDEN/COLLAPSE (the same simplification the in-flow path makes -- a visible re-entry under a hidden ancestor stays hidden).

The walk is bounded by nbox links and fails closed (returns 1, hidden) on NULL boxes, an out-of-range bid, a dangling parent link or a parent cycle -- a hostile box tree can never make it loop or read out of bounds. Pure; no allocation.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `boxes` | `pv_box_def *` |  |  |
| `nbox` | `size_t` |  |  |
| `bid` | `size_t` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`bt_box_hidden`](#bt_box_hidden) (include/box_tree.h:233).

---

<a id="bt_oof_avail"></a>

### `bt_oof_avail`

`function` | [src/box_tree.c:789](../../src/box_tree.c#L789)

```c
double bt_oof_avail(int a, int a_pct, int b, int b_pct, double cb, int *both)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `int` |  |  |
| `a_pct` | `int` |  |  |
| `b` | `int` |  |  |
| `b_pct` | `int` |  |  |
| `cb` | `double` |  |  |
| `both` | `int *` |  |  |

**Returns:** `double`

---

<a id="bt_defer_roots"></a>

### `bt_defer_roots`

`function` | [src/box_tree.c:797](../../src/box_tree.c#L797)

```c
size_t bt_defer_roots(const pv_box_def *boxes, size_t nbox, const bt_positioned *pos, size_t npos, const char *in_flow, int *root_of, size_t *order_of)
```

CSS 2.1 Appendix E steps 8-9 (spec/box_engine.md, tanda 47): an in-flow position:relative|sticky box S paints its whole subtree in the POSITIONED layer, in tree order with the absolute/fixed boxes of z-index auto/0.

When one of those (an absolute backdrop, say) comes EARLIER in the tree than S, S must paint above it -- but the painter draws all in-flow content first. This names the subtrees the painter has to defer.

[`pos`](include.flex_layout.h.md#fx_result-pos) is the positioned list (out-of-flow boxes), `in_flow[i]` nonzero when box i
was laid out in flow. S is deferred iff it is RELATIVE/STICKY, in flow, and some
non-negative-z out-of-flow P with no out-of-flow ancestor has box_index < S and
z(P) <= z(S) (an unset z counts 0), "earlier" meaning TREE order (a depth-first
walk of the parent links: a child box can hold a lower id than its parent).
order_of (nbox entries, may be NULL) receives that tree order so the painter can
merge roots with the positioned list. root_of[i] (nbox entries, always written) gets
the OUTERMOST deferred root that contains box i (self included) or -1. Returns
the number of distinct roots. Pure; bounded by nbox links per box; NULL or
malformed input fails OPEN: every entry -1, nothing deferred (normal paint).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `boxes` | `pv_box_def *` |  |  |
| `nbox` | `size_t` |  |  |
| `pos` | `bt_positioned *` |  |  |
| `npos` | `size_t` |  |  |
| `in_flow` | `char *` |  |  |
| `root_of` | `int *` |  |  |
| `order_of` | `size_t *` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`bt_defer_roots`](#bt_defer_roots) (include/box_tree.h:285).

*Calls:* [`bt_oof_root`](#bt_oof_root)

---

## Macros

<a id="bt_len_auto"></a>

### `BT_LEN_AUTO`

`macro` | [src/box_tree.c:31](../../src/box_tree.c#L31)

```c
#define BT_LEN_AUTO
```

Inset sentinels.

PV_LEN_UNSET comes from page_view.h (= INT_MIN). CSS_LEN_AUTO is INT_MIN + 1 in css.h; we define it locally to keep box_tree.c free of the css.h dependency (the layout cares about the values, not their name).

---

<a id="bt_wrap_eps"></a>

### `BT_WRAP_EPS`

`macro` | [src/box_tree.c:62](../../src/box_tree.c#L62)

```c
#define BT_WRAP_EPS
```

---
