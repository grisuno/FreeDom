# `src/table_layout.c`

> Source: [src/table_layout.c:1](../../src/table_layout.c#L1) | language `c` | coverage 66.7% | [API index](../index.md)

table_layout (tl_) -- see include/table_layout.h and spec/table_layout.md.

## Contents

- **Functions:** [`tl_intrinsic`](#tl_intrinsic), [`tl_columns`](#tl_columns)

## Functions

<a id="tl_intrinsic"></a>

### `tl_intrinsic`

`function` | [src/table_layout.c:78](../../src/table_layout.c#L78)

```c
void tl_intrinsic(const tl_cell *cells, size_t n, size_t ncols, double gap, double *min_total, double *max_total)
```

The table's min-content and max-content widths (columns plus gaps): what it contributes when it is itself a cell of an outer table.

Either output may be NULL. Both are 0 for an invalid ncols.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cells` | `tl_cell *` |  |  |
| `n` | `size_t` |  |  |
| `ncols` | `size_t` |  |  |
| `gap` | `double` |  |  |
| `min_total` | `double *` |  |  |
| `max_total` | `double *` |  |  |

> **Inherited:** Documentation from [`tl_intrinsic`](#tl_intrinsic) (include/table_layout.h:53).

---

<a id="tl_columns"></a>

### `tl_columns`

`function` | [src/table_layout.c:134](../../src/table_layout.c#L134)

```c
double tl_columns(const tl_cell *cells, size_t n, size_t ncols, double gap, double avail, double table_w, double *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cells` | `tl_cell *` |  |  |
| `n` | `size_t` |  |  |
| `ncols` | `size_t` |  |  |
| `gap` | `double` |  |  |
| `avail` | `double` |  |  |
| `table_w` | `double` |  |  |
| `out` | `double *` |  |  |

**Returns:** `double`

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_table_layout.c.md#llvmfuzzertestoneinput)

---
