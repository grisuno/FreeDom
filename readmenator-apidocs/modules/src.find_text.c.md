# `src/find_text.c`

> Source: [src/find_text.c:1](../../src/find_text.c#L1) | language `c` | coverage 71.4% | [API index](../index.md)

find_text (ft_) -- find in page over the rendered text. spec/find_text.md.

## Contents

- **Functions:** [`ft_fold`](#ft_fold), [`ft_compile`](#ft_compile), [`ft_search`](#ft_search), [`ft_spans`](#ft_spans), [`ft_step`](#ft_step)
- **Macros:** [`FT_INVALID`](#ft_invalid)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_find_text_c__ft_compile(["ft_compile"])
    n_src_find_text_c__ft_fold(["ft_fold"])
    n_src_find_text_c__ft_compile --> n_src_find_text_c__ft_fold
```

## Functions

<a id="ft_fold"></a>

### `ft_fold`

`function` | [src/find_text.c:13](../../src/find_text.c#L13)

```c
uint32_t ft_fold(uint32_t cp)
```

Case- and (Latin) diacritic-insensitive fold of one code point.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cp` | `uint32_t` |  |  |

**Returns:** `uint32_t`

> **Inherited:** Documentation from [`ft_fold`](#ft_fold) (include/find_text.h:35).

*Called by:* [`ft_compile`](#ft_compile)

---

<a id="ft_compile"></a>

### `ft_compile`

`function` | [src/find_text.c:59](../../src/find_text.c#L59)

```c
size_t ft_compile(const char *q, size_t qlen, uint32_t *out, size_t cap)
```

Folds the query, trims it and collapses white space to one ' ' (U+0020).

Returns the number of code points written (<= cap, <= FT_QUERY_MAX); 0 for an empty query.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `q` | `char *` |  |  |
| `qlen` | `size_t` |  |  |
| `out` | `uint32_t *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`ft_compile`](#ft_compile) (include/find_text.h:39).

*Calls:* [`ft_fold`](#ft_fold)

---

<a id="ft_search"></a>

### `ft_search`

`function` | [src/find_text.c:127](../../src/find_text.c#L127)

```c
ft_status ft_search(const ft_piece *pieces, size_t n, const uint32_t *q, size_t qn, ft_match *out, size_t cap, size_t *nout, int *truncated)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pieces` | `ft_piece *` |  |  |
| `n` | `size_t` |  |  |
| `q` | `uint32_t *` |  |  |
| `qn` | `size_t` |  |  |
| `out` | `ft_match *` |  |  |
| `cap` | `size_t` |  |  |
| `nout` | `size_t *` |  |  |
| `truncated` | `int *` |  |  |

**Returns:** `ft_status`

---

<a id="ft_spans"></a>

### `ft_spans`

`function` | [src/find_text.c:158](../../src/find_text.c#L158)

```c
size_t ft_spans(const ft_piece *pieces, size_t n, const ft_match *m, size_t nm, ft_span *out, size_t cap)
```

Splits matches into per-piece spans (one per piece a match touches, empty spans dropped), in order.

Returns the number written (<= cap).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pieces` | `ft_piece *` |  |  |
| `n` | `size_t` |  |  |
| `m` | `ft_match *` |  |  |
| `nm` | `size_t` |  |  |
| `out` | `ft_span *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`ft_spans`](#ft_spans) (include/find_text.h:48).

---

<a id="ft_step"></a>

### `ft_step`

`function` | [src/find_text.c:180](../../src/find_text.c#L180)

```c
long ft_step(long cur, size_t n, int dir)
```

Next (dir > 0) or previous (dir < 0) match index with wrap-around; -1 when n == 0.

A cur outside [0, n) starts at the first (dir > 0) or last (dir < 0) match.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cur` | `long` |  |  |
| `n` | `size_t` |  |  |
| `dir` | `int` |  |  |

**Returns:** `long`

> **Inherited:** Documentation from [`ft_step`](#ft_step) (include/find_text.h:53).

---

## Macros

<a id="ft_invalid"></a>

### `FT_INVALID`

`macro` | [src/find_text.c:4](../../src/find_text.c#L4)

```c
#define FT_INVALID
```

---
