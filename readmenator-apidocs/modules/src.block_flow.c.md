# `src/block_flow.c`

> Source: [src/block_flow.c:1](../../src/block_flow.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

block_flow (bf_) -- vertical margin collapsing.

See spec/block_flow.md.

## Contents

- **Functions:** [`bf_collapse_n`](#bf_collapse_n), [`bf_collapse`](#bf_collapse), [`bf_margins_adjoin`](#bf_margins_adjoin)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_block_flow_c__bf_collapse(["bf_collapse"])
    n_src_block_flow_c__bf_collapse_n(["bf_collapse_n"])
    n_src_block_flow_c__bf_collapse --> n_src_block_flow_c__bf_collapse_n
```

## Functions

<a id="bf_collapse_n"></a>

### `bf_collapse_n`

`function` | [src/block_flow.c:15](../../src/block_flow.c#L15)

```c
double bf_collapse_n(const double *m, size_t n)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `m` | `double *` |  |  |
| `n` | `size_t` |  |  |

**Returns:** `double`

*Called by:* [`bf_collapse`](#bf_collapse)

---

<a id="bf_collapse"></a>

### `bf_collapse`

`function` | [src/block_flow.c:30](../../src/block_flow.c#L30)

```c
double bf_collapse(double a, double b)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `double` |  |  |
| `b` | `double` |  |  |

**Returns:** `double`

*Calls:* [`bf_collapse_n`](#bf_collapse_n)

---

<a id="bf_margins_adjoin"></a>

### `bf_margins_adjoin`

`function` | [src/block_flow.c:35](../../src/block_flow.c#L35)

```c
int bf_margins_adjoin(double border_px, double padding_px)
```

Whether two vertical margins separated by this much border and padding ADJOIN, i.e. whether they collapse at all (CSS 2.1 section 8.3.1): they do only when nothing separates them.

Returns 1 when both are exactly zero, 0 otherwise.

Fails CLOSED on non-finite input (returns 0, "does not collapse"): collapsing a
margin that should not collapse deletes space the author asked for and fuses two
blocks into one, which is the more destructive of the two errors.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `border_px` | `double` |  |  |
| `padding_px` | `double` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`bf_margins_adjoin`](#bf_margins_adjoin) (include/block_flow.h:43).

---
