# `src/group_index.c`

> Source: [src/group_index.c:1](../../src/group_index.c#L1) | language `c` | coverage 100.0% | [API index](../index.md)

group_index (gi_) -- spec/group_index.md.

## Contents

- **Functions:** [`gi_build`](#gi_build)

## Functions

<a id="gi_build"></a>

### `gi_build`

`function` | [src/group_index.c:10](../../src/group_index.c#L10)

```c
size_t gi_build(const int *keys, size_t n, size_t nkeys, size_t *offs, size_t *items)
```

Groups item i under keys[i] when 0 <= keys[i] < nkeys (other keys are left out).

Writes offs[0..nkeys] and items[0..m); group k is items[offs[k] .. offs[k+1]) in increasing index order. Returns m, or (size_t)-1 on invalid arguments (nothing written to items; offs untouched when NULL).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `keys` | `int *` |  |  |
| `n` | `size_t` |  |  |
| `nkeys` | `size_t` |  |  |
| `offs` | `size_t *` |  |  |
| `items` | `size_t *` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`gi_build`](#gi_build) (include/group_index.h:20).

---
