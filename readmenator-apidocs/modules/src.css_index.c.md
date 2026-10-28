# `src/css_index.c`

> Source: [src/css_index.c:1](../../src/css_index.c#L1) | language `c` | coverage 100.0% | [API index](../index.md)

css_index -- see include/css_index.h and spec/css_index.md.

## Contents

- **Structs:** [`cix_run`](#cix_run)
- **Functions:** [`cix_free`](#cix_free), [`cix_candidates`](#cix_candidates), [`cix_build`](#cix_build), [`cix_build_ptrs`](#cix_build_ptrs)

## Structs

<a id="cix_run"></a>

### `cix_run`

`struct` | [src/css_index.c:98](../../src/css_index.c#L98)

```c
typedef struct
```

One sorted run of selector ordinals: the universal list, or the bucket of one key (entries with equal keys are stored in ascending selector order, see entry_cmp).

---

## Functions

<a id="cix_free"></a>

### `cix_free`

`function` | [src/css_index.c:40](../../src/css_index.c#L40)

```c
void cix_free(cix_index *idx)
```

Releases the index; idempotent.

Leaves it invalid.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `cix_index *` |  |  |

> **Inherited:** Documentation from [`cix_free`](#cix_free) (include/css_index.h:40).

---

<a id="cix_candidates"></a>

### `cix_candidates`

`function` | [src/css_index.c:129](../../src/css_index.c#L129)

```c
size_t cix_candidates(const cix_index *idx, const css_element *el, uint32_t **buf, size_t *cap)
```

Candidates in ascending selector order without duplicates: a k-way merge of the (already sorted) universal list and the id, tag and class buckets, so no sort is needed.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `cix_index *` |  |  |
| `el` | `css_element *` |  |  |
| `buf` | `uint32_t **` |  |  |
| `cap` | `size_t *` |  |  |

**Returns:** `size_t`

---

<a id="cix_build"></a>

### `cix_build`

`function` | [src/css_index.c:166](../../src/css_index.c#L166)

```c
void cix_build(const css_sel *sels, size_t n, cix_index *idx)
```

Builds the index over sels[0,n) into *idx, overwriting it (a built index must be cix_free'd first).

On OOM leaves *idx invalid (valid == 0).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sels` | `css_sel *` |  |  |
| `n` | `size_t` |  |  |
| `idx` | `cix_index *` |  |  |

> **Inherited:** Documentation from [`cix_build`](#cix_build) (include/css_index.h:34).

---

<a id="cix_build_ptrs"></a>

### `cix_build_ptrs`

`function` | [src/css_index.c:168](../../src/css_index.c#L168)

```c
void cix_build_ptrs(css_sel *const *sels, size_t n, cix_index *idx)
```

Same over a table of pointers (a sheet keeps its selectors compact, one allocation each).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sels` | `css_sel *const *` |  |  |
| `n` | `size_t` |  |  |
| `idx` | `cix_index *` |  |  |

> **Inherited:** Documentation from [`cix_build_ptrs`](#cix_build_ptrs) (include/css_index.h:37).

---
