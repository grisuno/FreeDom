# `src/css_index.c`

> Source: [src/css_index.c:1](../../src/css_index.c#L1) | language `c` | coverage 75.0% | [API index](../index.md)

css_index -- see include/css_index.h and spec/css_index.md.

## Contents

- **Functions:** [`cix_free`](#cix_free), [`cix_build`](#cix_build), [`cix_candidates`](#cix_candidates)

## Functions

<a id="cix_free"></a>

### `cix_free`

`function` | [src/css_index.c:45](../../src/css_index.c#L45)

```c
void cix_free(cix_index *idx)
```

Releases the index; idempotent.

Leaves it invalid.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `cix_index *` |  |  |

> **Inherited:** Documentation from [`cix_free`](#cix_free) (include/css_index.h:37).

---

<a id="cix_build"></a>

### `cix_build`

`function` | [src/css_index.c:52](../../src/css_index.c#L52)

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

<a id="cix_candidates"></a>

### `cix_candidates`

`function` | [src/css_index.c:120](../../src/css_index.c#L120)

```c
size_t cix_candidates(const cix_index *idx, const css_element *el, uint32_t **buf, size_t *cap)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `cix_index *` |  |  |
| `el` | `css_element *` |  |  |
| `buf` | `uint32_t **` |  |  |
| `cap` | `size_t *` |  |  |

**Returns:** `size_t`

---
