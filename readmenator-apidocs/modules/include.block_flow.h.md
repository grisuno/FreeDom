# `include/block_flow.h`

> Source: [include/block_flow.h:1](../../include/block_flow.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

block_flow (bf_) -- vertical margin collapsing for block-level boxes.

## Contents

- **Functions:** [`ABSENT`](#absent), [`bf_collapse_n`](#bf_collapse_n), [`bf_margins_adjoin`](#bf_margins_adjoin)

## Functions

<a id="absent"></a>

### `ABSENT`

`function` | [include/block_flow.h:26](../../include/block_flow.h#L26)

```c
* as ABSENT (0) rather than propagated: a poisoned length must not spread into * the geometry of the rest of the page. */ double bf_collapse(double a, double b);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `0` |  |  |  |

**Returns:** `* as`

---

<a id="bf_collapse_n"></a>

### `bf_collapse_n`

`function` | [include/block_flow.h:33](../../include/block_flow.h#L33)

```c
* bf_collapse_n((double[])
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `double` |  |  |  |

**Returns:** `*`

---

<a id="bf_margins_adjoin"></a>

### `bf_margins_adjoin`

`function` | [include/block_flow.h:43](../../include/block_flow.h#L43)

```c
int bf_margins_adjoin(double border_px, double padding_px);
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

---
