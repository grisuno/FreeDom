# `include/group_index.h`

> Source: [include/group_index.h:1](../../include/group_index.h#L1) | language `h` | coverage 33.3% | [API index](../index.md)

## Contents

- **Functions:** [`group_index`](#group_index), [`gi_build`](#gi_build)

## Functions

<a id="group_index"></a>

### `group_index`

`function` | [include/group_index.h:9](../../include/group_index.h#L9)

```c
* group_index (gi_) -- stable group-by of n items by an integer key, in CSR form, so a * per-group pass visits only its own items in their original order. Pure, no allocation, * O(n + nkeys). Contract
```

**Returns:** `*`

---

<a id="gi_build"></a>

### `gi_build`

`function` | [include/group_index.h:20](../../include/group_index.h#L20)

```c
size_t gi_build(const int *keys, size_t n, size_t nkeys, size_t *offs, size_t *items);
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

*Called by:* [`LLVMFuzzerTestOneInput`](fuzz.fuzz_group_index.c.md#llvmfuzzertestoneinput)

---
